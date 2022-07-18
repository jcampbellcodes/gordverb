#include "er_convolution.h"
#include "gv_data.h"

using namespace gv::EarlyReflections;
using namespace juce;

void Convolution::setReverbAmount( float inReverbAmount )
{
    // TODO: simple gain
}

void Convolution::prepareToPlay( double inSampleRate, int inSamplesPerBlock )
{
    dsp::ProcessSpec spec{ inSampleRate,
                           static_cast<uint32>( inSamplesPerBlock ), 2 };
    mConvolver.prepare( spec );

    // TODO allow different IRs
    int data_size = 0;
    auto data = BinaryData::getNamedResource( "r1_rir_bformat_wav", data_size );
    mConvolver.loadImpulseResponse(
        data, data_size, dsp::Convolution::Stereo::yes,
        dsp::Convolution::Trim::no, 0 /*use data size*/ );
}

int Convolution::getLatency()
{
    return mConvolver.getLatency();
}

void Convolution::processBlock( juce::AudioBuffer<float>& inOutBuffer )
{
    auto block =
        juce::dsp::AudioBlock<float>( inOutBuffer )
            .getSubsetChannelBlock( 0, (size_t)inOutBuffer.getNumChannels() );
    mConvolver.process( dsp::ProcessContextReplacing<float>( block ) );
}

void Convolution::reset()
{
    mConvolver.reset();
}
