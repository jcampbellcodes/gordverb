#ifndef LR_COST_H
#define LR_COST_H

#include "reverbsc.h"
#include <juce_audio_processors/juce_audio_processors.h>

namespace gv
{
namespace LateReflections
{
    /**
     * @brief A wrapper around the DaisySP ReverbSC from CSound. (originally
     * written by Sean Costello in the 90s)
     */
    class Costello
    {
      public:
        void setReverbAmount( float inReverbAmount );

        void prepareToPlay( double inSampleRate, int inSamplesPerBlock );

        void processBlock( juce::AudioBuffer<float>& inOutBuffer );
        void reset();

        int getLatency()
        {
            return 0;
        }

      private:
        daisysp::ReverbSc mReverb;
        float mSampleRate = 44100.0;
    };
} // namespace LateReflections

} // namespace gv

#endif
