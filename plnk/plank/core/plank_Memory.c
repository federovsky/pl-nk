/*
 -------------------------------------------------------------------------------
 This file is part of the Plink, Plonk, Plank libraries
  by Martin Robinson
 
 http://code.google.com/p/pl-nk/
 
 Copyright University of the West of England, Bristol 2011-15
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

#include "plank_StandardHeader.h"
#include "plank_Memory.h"

void* pl_MemoryDefaultAllocateBytes (PlankP p, PlankUL size)
{
    (void)p;
    return malloc (size);
}

void pl_MemoryDefaultFree (PlankP p, void* ptr)
{
    (void)p;
    free (ptr);
}

PlankMemoryRef pl_Memory_CreateAndInit()
{
    PlankMemoryRef p;
    p = pl_Memory_Create();
    
    if (p != PLANK_NULL)
    {
        if (pl_Memory_Init (p) != PlankResult_OK)
            pl_Memory_Destroy (p);
        else
            return p;
    }
    
    return (PlankMemoryRef)PLANK_NULL;
}

PlankMemoryRef pl_Memory_Create()
{
    PlankMemoryRef p = (PlankMemoryRef)pl_MemoryDefaultAllocateBytes (0, sizeof (PlankMemory));
    
    if (p != PLANK_NULL)
        pl_MemoryZero (p, sizeof (PlankMemory));
        
    return p;
}

PlankResult pl_Memory_Init (PlankMemoryRef p)
{
    if (p == PLANK_NULL)
        return PlankResult_MemoryError;

    p->userData = p;
    pl_Lock_Init (&p->lock);
    
    return pl_Memory_SetFunctions (p, PLANK_NULL, PLANK_NULL);
}

PlankResult pl_Memory_DeInit (PlankMemoryRef p)
{
    if (p == PLANK_NULL)
        return PlankResult_MemoryError;
    
    pl_Lock_Lock (&p->lock);
    pl_MemoryZero (p, sizeof (PlankMemory));
    pl_Lock_Unlock (&p->lock);
    
    return PlankResult_OK;
}

PlankResult pl_Memory_Destroy (PlankMemoryRef p)
{
    PlankResult result = PlankResult_OK;
    
    if (p != PLANK_NULL)
    {
        if ((result = pl_Memory_DeInit (p)) != PlankResult_OK)
            goto exit;
    }
    
    pl_MemoryDefaultFree (0, p);
    
exit:
    return result;
}

PlankResult pl_Memory_SetUserData (PlankMemoryRef p, PlankP userData)
{
    pl_Lock_Lock (&p->lock);
    p->userData = userData;
    pl_Lock_Unlock (&p->lock);

    return PlankResult_OK;
}

PlankP pl_Memory_GetUserData (PlankMemoryRef p)
{
    PlankP ptr;
    pl_Lock_Lock (&p->lock);
    ptr = p->userData;
    pl_Lock_Unlock (&p->lock);
    
    return ptr;
}

PlankResult pl_Memory_SetFunctions (PlankMemoryRef p, 
                                    PlankMemoryAllocateBytesFunction allocateBytesFunction, 
                                    PlankMemoryFreeFunction freeFunction)
{

    if (allocateBytesFunction == PLANK_NULL)
        allocateBytesFunction = pl_MemoryDefaultAllocateBytes;
    
    if (freeFunction == PLANK_NULL)
        freeFunction = pl_MemoryDefaultFree;
    
    pl_Lock_Lock (&p->lock);
    p->allocFunction = allocateBytesFunction;
    p->freeFunction = freeFunction;
    pl_Lock_Unlock (&p->lock);
    
    return PlankResult_OK;
}

PlankMemoryRef pl_MemoryGlobal()
{
    static PlankMemory global;
    static PlankB firstTime = PLANK_TRUE;
    
    if (firstTime)
    {
        pl_Memory_Init (&global);
        firstTime = PLANK_FALSE;
    }
    
    return &global;
}