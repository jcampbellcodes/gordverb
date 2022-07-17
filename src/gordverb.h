#pragma once

#include "er_convolution.h"
#include "lr_costello.h"
#include "reverb_interface.h"
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>

//==============================================================================
class GordverbProcessor : public juce::AudioProcessor
{
  public:
    //==============================================================================
    GordverbProcessor();
    ~GordverbProcessor() override;

    //==============================================================================
    void prepareToPlay( double sampleRate, int samplesPerBlock ) override;
    void releaseResources() override;

    bool isBusesLayoutSupported( const BusesLayout& layouts ) const override;

    void processBlock( juce::AudioBuffer<float>&, juce::MidiBuffer& ) override;
    using AudioProcessor::processBlock;

    void reset() override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram( int index ) override;
    const juce::String getProgramName( int index ) override;
    void changeProgramName( int index, const juce::String& newName ) override;

    //==============================================================================
    void getStateInformation( juce::MemoryBlock& destData ) override;
    void setStateInformation( const void* data, int sizeInBytes ) override;

  private:
    gv::Reverb<gv::EarlyReflections::Convolution, gv::LateReflections::Costello>
        mReverb;
    juce::AudioProcessorValueTreeState mState;
    juce::dsp::DryWetMixer<float> mDryWetMixer{ 10 };
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( GordverbProcessor )
};
