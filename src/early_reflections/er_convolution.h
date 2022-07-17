#ifndef ER_CONV_H
#define ER_CONV_H

#include <juce_audio_processors/juce_audio_processors.h>

namespace gv
{
namespace EarlyReflections
{
    class Convolution
    {
      public:
        void setReverbAmount( float inReverbAmount ){};

        void prepareToPlay( double inSampleRate, int inSamplesPerBlock ){};

        void processBlock( juce::AudioBuffer<float>& inOutBuffer ){};
        void reset(){};

      private:
        // JUCE convolver
    };
} // namespace EarlyReflections

} // namespace gv

#endif
