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

#ifndef PLONK_PATCHCHANNEL_H
#define PLONK_PATCHCHANNEL_H

#include "../channel/plonk_ChannelInternalCore.h"
#include "../plonk_GraphForwardDeclarations.h"

template<class Type>
class PatchSource
{
public:
    PatchSource() throw()
    {
        this->setSourceInternal (Type::getNull());
    }
    
    PatchSource (Type const& source) throw()
    {
        this->setSourceInternal (source);
    }
    
    PatchSource (AtomicDynamicPointerVariable const& atomic) throw()
    :   atom (atomic)
    {
    }
    
    PatchSource (PatchSource const& other) throw()
    :   atom (other.getAtom())
    {
    }

    PatchSource& operator= (PatchSource const& other) throw()
	{
		if (this != &other)
            this->atom = other.getAtom();
        
        return *this;
	}

    ~PatchSource()
    {
        Dynamic* const oldPtr = this->atom.getValue().getPtr();
        delete oldPtr;
    }
    
    // this isn't thread safe yet... but sorting out the architecture first...
        
    inline void setSource (Type const& source) throw()
    {
        Dynamic* const oldPtr = this->atom.getValue().getPtr();
        this->setSourceInternal (source);
        delete oldPtr;
    }
    
    inline AtomicDynamicPointerVariable& getAtom() throw() { return atom; }
    inline const AtomicDynamicPointerVariable& getAtom() const throw() { return atom; }
    
private:
    AtomicDynamicPointerVariable atom;
    
    inline void setSourceInternal (Type const& source) throw()
    {
        Dynamic* const newPtr = new Dynamic (source);
        this->atom.getValue().setPtr (newPtr);
    }
};

/** Patch channel.
 Safe repatching of signals. */
template<class SampleType>
class PatchChannelInternal 
:   public ChannelInternal<SampleType, ChannelInternalCore::Data> // will need to be a proxyowner...
{
public:
    typedef ChannelInternalCore::Data                           Data;
    typedef ChannelBase<SampleType>                             ChannelType;
    typedef PatchChannelInternal<SampleType>                    PatchChannelInternalType;
    typedef ChannelInternal<SampleType,Data>                    Internal;
    typedef ChannelInternalBase<SampleType>                     InternalBase;
    typedef UnitBase<SampleType>                                UnitType;
    typedef InputDictionary                                     Inputs;
    typedef NumericalArray<SampleType>                          Buffer;
    
    PatchChannelInternal (Inputs const& inputs, 
                          Data const& data, 
                          BlockSize const& blockSize,
                          SampleRate const& sampleRate) throw()
    :   Internal (inputs, data, blockSize, sampleRate)
    {
    }
    
    Text getName() const throw()
    {        
        return "Patch";
    }        
    
    IntArray getInputKeys() const throw()
    {
        const IntArray keys (IOKey::AtomicVariable);
        return keys;
    }    
    
    InternalBase* getChannel (const int /*index*/) throw()
    {
        return this;
    }        
    
    void initChannel (const int /*channel*/) throw()
    {
//        AtomicVariableType& atomicVariable = ChannelInternalCore::getInputAs<AtomicVariableType> (IOKey::AtomicVariable);
//        AtomicType& atomicValue = atomicVariable.getValue();

        this->initValue (0); // should get real value
    }    
    
    void process (ProcessInfo& info, const int /*channel*/) throw()
    {        
        SampleType* const outputSamples = this->getOutputSamples();
        const int outputBufferLength = this->getOutputBuffer().length();        

        AtomicDynamicPointerVariable& atom = ChannelInternalCore::getInputAs<AtomicDynamicPointerVariable> (IOKey::AtomicVariable);
        Dynamic& dynamic = atom.getValue().getObject();
        UnitType& source = dynamic.asUnchecked<UnitType>();
        const Buffer sourceBuffer (source.process (info, 0)); // channel 0...!?
        const SampleType* const sourceSamples = sourceBuffer.getArray();
        const int sourceBufferLength = sourceBuffer.length();

        int i;
        
        if (sourceBufferLength == outputBufferLength)
        {
            for (i = 0; i < outputBufferLength; ++i) 
                outputSamples[i] = sourceSamples[i];
        }
        else if (sourceBufferLength == 1)
        {
            const SampleType value (sourceSamples[0]);
            
            for (i = 0; i < outputBufferLength; ++i) 
                outputSamples[i] = value;
        }
        else
        {
            double sourcePosition = 0.0;
            const double sourceIncrement = double (sourceBufferLength) / double (outputBufferLength);
            
            for (i = 0; i < outputBufferLength; ++i) 
            {
                outputSamples[i] = sourceSamples[int (sourcePosition)];
                sourcePosition += sourceIncrement;
            }        
        }
    }

private:
};



//------------------------------------------------------------------------------

/** Patch channel.
 Safe repatching of signals. 
 @ingroup ControlUnits */
template<class SampleType>
class PatchUnit
{
public:    
    typedef PatchChannelInternal<SampleType>                        PatchChannelInternalType;
    typedef typename PatchChannelInternalType::Data                 Data;
    typedef ChannelBase<SampleType>                                 ChannelType;
    typedef ChannelInternal<SampleType,Data>                        Internal;
    typedef ChannelInternalBase<SampleType>                         InternaBase;
    typedef UnitBase<SampleType>                                    UnitType;
    typedef InputDictionary                                         Inputs;
    typedef NumericalArray<SampleType>                              Buffer;
    typedef PatchSource<UnitType>                                   UnitPatchSource;
    
    static inline UnitInfos getInfo() throw()
    {
        const double blockSize = (double)BlockSize::getDefault().getValue();
        const double sampleRate = SampleRate::getDefault().getValue();

        return UnitInfo ("Patch", "Safe repatching of signals.",
                         
                         // output
                         1, 
                         IOKey::Generic,            Measure::None,      IOInfo::NoDefault,      IOLimit::None, 
                         IOKey::End,
                         
                         // inputs
                         IOKey::AtomicVariable,     Measure::None,      IOInfo::NoDefault,      IOLimit::None,
                         IOKey::BlockSize,          Measure::Samples,   blockSize,              IOLimit::Minimum, Measure::Samples,             1.0,
                         IOKey::SampleRate,         Measure::Hertz,     sampleRate,             IOLimit::Minimum, Measure::Hertz,               0.0,
                         IOKey::End);
    }    
    
    /** Create control rate variable. */
    static UnitType ar (UnitPatchSource const& source,
                        BlockSize const& preferredBlockSize = BlockSize::getDefault(),
                        SampleRate const& preferredSampleRate = SampleRate::getDefault()) throw()
    {        
        Inputs inputs;
        inputs.put (IOKey::AtomicVariable, source.getAtom());
        
        Data data = { -1.0, -1.0 };
                
        return UnitType::template createFromInputs<PatchChannelInternalType> (inputs, 
                                                                              data, 
                                                                              preferredBlockSize, 
                                                                              preferredSampleRate);
    }   
};

typedef PatchUnit<PLONK_TYPE_DEFAULT> Patch;


#endif // PLONK_PATCHCHANNEL_H


