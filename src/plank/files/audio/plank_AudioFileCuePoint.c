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

#include "../../core/plank_StandardHeader.h"
#include "plank_AudioFileCuePoint.h"

PlankAudioFileCuePointRef pl_AudioFileCuePoint_Create()
{
    return (PlankAudioFileCuePointRef)PLANK_NULL;
}

PlankResult pl_AudioFileCuePoint_Destroy (PlankAudioFileCuePointRef p)
{
	(void)p;
    return PlankResult_OK;
}

PlankResult pl_AudioFileCuePoint_Init (PlankAudioFileCuePointRef p)
{
    PlankResult result = PlankResult_OK;
    
    if (p == PLANK_NULL)
    {
        result = PlankResult_MemoryError;
        goto exit;
    }
    
    pl_MemoryZero (p, sizeof (PlankAudioFileCuePoint));
    
exit:
    return result;
}

PlankResult pl_AudioFileCuePoint_DeInit (PlankAudioFileCuePointRef p)
{
    PlankResult result = PlankResult_OK;
    PlankMemoryRef m;

    if (p == PLANK_NULL)
    {
        result = PlankResult_MemoryError;
        goto exit;
    }
    
    if ((result = pl_DynamicArray_DeInit (&p->label)) != PlankResult_OK) goto exit;
    if ((result = pl_DynamicArray_DeInit (&p->comment)) != PlankResult_OK) goto exit;
    
    if (p->extra != PLANK_NULL)
    {
        m = pl_MemoryGlobal();
        
        if ((result = pl_Memory_Free (m, p->extra)) != PlankResult_OK)
            goto exit;
    }
    
    pl_MemoryZero (p, sizeof (PlankAudioFileCuePoint));
        
exit:
    return result;
}

PlankResult pl_AudioFileCuePoint_SetPosition (PlankAudioFileCuePointRef p, const PlankLL position)
{
    p->position = position;
    return PlankResult_OK;
}

PlankResult pl_AudioFileCuePoint_SetID (PlankAudioFileCuePointRef p, const PlankUI cueID)
{
    p->cueID = cueID;
    return PlankResult_OK;
}

PlankResult pl_AudioFileCuePoint_SetLabel (PlankAudioFileCuePointRef p, const char* label)
{
    return pl_DynamicArray_SetAsText (&p->label, label);
}


PlankResult pl_AudioFileCuePoint_SetComment (PlankAudioFileCuePointRef p, const char* comment)
{
    return pl_DynamicArray_SetAsText (&p->comment, comment);
}

PlankResult pl_AudioFileCuePoint_SetLabelLengthClear (PlankAudioFileCuePointRef p, const PlankL length)
{
    return pl_DynamicArray_SetAsClearText (&p->label, length);
}

PlankResult pl_AudioFileCuePoint_SetCommentLengthClear (PlankAudioFileCuePointRef p, const PlankL length)
{
    return pl_DynamicArray_SetAsClearText (&p->comment, length);
}

PlankResult pl_AudioFileCuePoint_SetType (PlankAudioFileCuePointRef p, const int type)
{
    p->type = type;
    return PlankResult_OK;
}

PlankResult pl_AudioFileCuePoint_SetExtra (PlankAudioFileCuePointRef p, PlankUI purpose, PlankUS country, PlankUS language, PlankUS dialect, PlankUS codePage)
{
    PlankResult result = PlankResult_OK;
    PlankMemoryRef m;
    
    if (p->extra == PLANK_NULL)
    {
        m = pl_MemoryGlobal();
        p->extra = pl_Memory_AllocateBytes (m, sizeof (PlankAudioFileCuePointExtra));
        
        if (p->extra == PLANK_NULL)
        {
            result = PlankResult_MemoryError;
            goto exit;
        }
        
        pl_MemoryZero (p->extra, sizeof (PlankAudioFileCuePointExtra));
    }
    
    p->extra->purpose  = purpose;
    p->extra->country  = country;
    p->extra->language = language;
    p->extra->dialect  = dialect;
    p->extra->codePage = codePage;

exit:
    return result;
}

PlankLL pl_AudioFileCuePoint_GetPosition (PlankAudioFileCuePointRef p)
{
    return p->position;
}

PlankUI pl_AudioFileCuePoint_GetID (PlankAudioFileCuePointRef p)
{
    return p->cueID;
}

const char* pl_AudioFileCuePoint_GetLabel (PlankAudioFileCuePointRef p)
{
    return pl_DynamicArray_GetArray (&p->label);
}

char* pl_AudioFileCuePoint_GetLabelWritable (PlankAudioFileCuePointRef p)
{
    return pl_DynamicArray_GetArray (&p->label);
}

const char* pl_AudioFileCuePoint_GetComment (PlankAudioFileCuePointRef p)
{
    return pl_DynamicArray_GetArray (&p->comment);
}

char* pl_AudioFileCuePoint_GetCommentWritable (PlankAudioFileCuePointRef p)
{
    return pl_DynamicArray_GetArray (&p->comment);
}

int pl_AudioFileCuePoint_GetType (PlankAudioFileCuePointRef p)
{
    return p->type;
}

PlankResult pl_AudioFileCuePoint_OffsetPosition (PlankAudioFileCuePointRef p, const PlankLL offset)
{
    p->position += offset;
    return PlankResult_OK;
}
