#include "lr_costello.h"
using namespace gv::LateReflections;

void Costello::setReverbAmount( float inReverbAmount )
{
    mReverb.SetFeedback( inReverbAmount );
}

void Costello::prepareToPlay( double inSampleRate, int /*inSamplesPerBlock*/ )
{
    mSampleRate = static_cast<float>( inSampleRate );
    mReverb.Init( mSampleRate );
    mReverb.SetLpFreq( 5000.0 ); // maybe could make this settable, but this is
                                 // the one I like right now :)
}

void Costello::processBlock( juce::AudioBuffer<float>& inOutBuffer )
{
    auto numSamples = inOutBuffer.getNumSamples();
    auto numChannels = inOutBuffer.getNumChannels();
    jassert( numChannels > 0 );
    const auto* inDataL = inOutBuffer.getReadPointer( 0 );
    const auto* inDataR =
        numChannels > 1 ? inOutBuffer.getReadPointer( 1 ) : inDataL;
    auto* outDataL = inOutBuffer.getWritePointer( 0 );
    auto* outDataR =
        numChannels > 1 ? inOutBuffer.getWritePointer( 1 ) : outDataL;
    for ( auto sample = 0; sample < numSamples; sample++ )
    {
        mReverb.Process( inDataL[ sample ], inDataR[ sample ],
                         outDataL + sample, outDataR + sample );
    }
}

void Costello::reset()
{
    mReverb.Init( mSampleRate );
}
