#ifndef REVERB_INTERFACE_H
#define REVERB_INTERFACE_H

#include <juce_audio_processors/juce_audio_processors.h>

namespace gv
{
template <typename EarlyReflections, typename LateReflections> class Reverb
{
  public:
    void setReverbAmount( float inReverbAmount )
    {
        mEarlyReflections.setReverbAmount( inReverbAmount );
        mLateReflections.setReverbAmount( inReverbAmount );
    }

    void prepareToPlay( double inSampleRate, int inSamplesPerBlock )
    {
        mEarlyReflections.prepareToPlay( inSampleRate, inSamplesPerBlock );
        mLateReflections.prepareToPlay( inSampleRate, inSamplesPerBlock );
    }

    void processBlock( juce::AudioBuffer<float>& inOutBuffer )
    {
        mEarlyReflections.processBlock( inOutBuffer );
        mLateReflections.processBlock( inOutBuffer );
    }

    void reset()
    {
        mEarlyReflections.reset();
        mLateReflections.reset();
    }

  private:
    EarlyReflections mEarlyReflections;
    LateReflections mLateReflections;
};
} // namespace gv

#endif
