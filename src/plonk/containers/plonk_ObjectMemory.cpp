/*
 -------------------------------------------------------------------------------
 This file is part of the Plink, Plonk, Plank libraries
  by Martin Robinson
 
 http://code.google.com/p/pl-nk/
 
 Copyright University of the West of England, Bristol 2011-12
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
 * Neither the name of University of the West of England, Bristol nor 
   the names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 DISCLAIMED. IN NO EVENT SHALL UNIVERSITY OF THE WEST OF ENGLAND, BRISTOL BE 
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 
 This software makes use of third party libraries. For more information see:
 doc/license.txt included in the distribution.
 -------------------------------------------------------------------------------
 */

#include "../core/plonk_StandardHeader.h"

BEGIN_PLONK_NAMESPACE

#include "../core/plonk_Headers.h"

#define PLONK_OBJECTMEMORY_DEBUG 1

#if PLONK_OBJECTMEMORY_DEBUG
AtomicLong largestSize;
AtomicInt blockCounts[64];
#endif

void* ObjectMemory::staticAlloc (PlankUL size)
{
    return ObjectMemory::global().allocateBytes (size);
}

void ObjectMemory::staticFree (void* ptr)
{
    ObjectMemory::global().free (ptr);
}

static inline void staticDoFree (void* ptr) throw()
{
#if PLONK_OBJECTMEMORY_DEBUG
    plonk_assert (!Threading::currentThreadIsAudioThread());
#endif
    ::free (ptr);
}

ObjectMemory& ObjectMemory::global() throw()
{
    static ObjectMemory* om = new ObjectMemory (Memory::global()); // just leak
    
    if (!om->isRunning())
        om->start();
    
    return *om;
}

ObjectMemory::ObjectMemory (Memory& m) throw()
:   memory (m)
{
    memory.setFunctions (staticAlloc, staticFree);    
}

ObjectMemory::~ObjectMemory()
{
    memory.setFunctions (malloc, ::free);
    setShouldExitAndWait();
}

void* ObjectMemory::allocateBytes (PlankUL requestedSize)
{
#if PLONK_OBJECTMEMORY_DEBUG
    plonk_assert (!Threading::currentThreadIsAudioThread());
#endif
    
    const PlankUL align = PLONK_WORDSIZE * 2;
    const PlankUL size = Bits<PlankUL>::nextPowerOf2 (requestedSize + align);
    
#if PLONK_OBJECTMEMORY_DEBUG
    const PlankUL sizeLog2 = Bits<PlankUL>::countTrailingZeroes (size);
    plonk_assert (sizeLog2 > 0 && sizeLog2 < 64);
    blockCounts[sizeLog2]++;
    
    largestSize.setIfLarger (size);
#endif
    
    PlankUC* const raw = static_cast<PlankUC*> (malloc (size));
    *reinterpret_cast<PlankUL*> (raw) = size;
    
    return raw + align;
}

void ObjectMemory::free (void* ptr)
{
    if (ptr != 0)
    {
        const PlankUL align = PLONK_WORDSIZE * 2;
        PlankUC* const raw = static_cast<PlankUC*> (ptr) - align;
        const PlankUL size = *reinterpret_cast<PlankUL*> (raw);
        
#if PLONK_OBJECTMEMORY_DEBUG
        const PlankUL sizeLog2 = Bits<PlankUL>::countTrailingZeroes (size);
        plonk_assert (sizeLog2 > 0 && sizeLog2 < 64);
        blockCounts[sizeLog2]--; 
#endif
        
        if (Threading::getCurrentThreadID() == getID())
        {
            staticDoFree (raw); // already triggered by a call on the background thread.
        }
        else if (ptr != 0)
        {
            Deletee d (raw);
            queue.push (d);
        }
    }
}

void ObjectMemory::increaseQueueCache (const int count) throw()
{
    queue.increaseCache (count);
}

ResultCode ObjectMemory::run() throw()
{
    const double minDuration = 0.000001;
    const double maxDuration = 0.1;
    double duration = minDuration;
    
    while (!getShouldExit())
    {
        Deletee d = queue.pop();
        
        if (d.ptr != 0)
        {
            duration = minDuration; // reset back to high speed
            staticDoFree (d.ptr);
        }
        else 
        {
            // gradually increase the amount of sleep if the queue is empty
            duration = plonk::min (duration * 2.0, maxDuration);
        }
        
        Threading::sleep (duration);
    }
    
    queue.clearAll();
    
    return 0;
}

END_PLONK_NAMESPACE
