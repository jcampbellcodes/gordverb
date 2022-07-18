#ifndef ER_CONV_H
#define ER_CONV_H

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

namespace gv
{
namespace EarlyReflections
{
    /**
     * @brief Small wrapper around JUCE Convolver.
     * @details Allows us to load IRs for processing the early reflections of a
     * space. We can then leave the long tail to the plate portion of the
     * reverb.
     */
    class Convolution
    {
      public:
        void setReverbAmount( float inReverbAmount );

        void prepareToPlay( double inSampleRate, int inSamplesPerBlock );

        void processBlock( juce::AudioBuffer<float>& inOutBuffer );
        void reset();

        int getLatency();

      private:
        juce::dsp::Convolution mConvolver;
    };
} // namespace EarlyReflections

} // namespace gv

#endif
