#include "gordverb.h"
using namespace juce;
//==============================================================================
GordverbProcessor::GordverbProcessor()
    : AudioProcessor(
          BusesProperties()
              .withInput( "Input", juce::AudioChannelSet::stereo(), true )
              .withOutput( "Output", juce::AudioChannelSet::stereo(), true ) )
    , mState( *this, nullptr, "state",
              { std::make_unique<AudioParameterFloat>(
                    ParameterID{ "reverb_amt", 1 }, "Reverb Time",
                    NormalisableRange<float>( 0.0f, 1.0f ), 0.9f ),
                std::make_unique<AudioParameterFloat>(
                    ParameterID{ "wet_dry", 1 }, "Wet/Dry",
                    NormalisableRange<float>( 0.0f, 1.0f ), 0.5f ),
                std::make_unique<AudioParameterBool>(
                    ParameterID{ "enable_er", 1 }, "Enable Early Reflections",
                    true ),
                std::make_unique<AudioParameterBool>(
                    ParameterID{ "enable_lr", 1 }, "Enable Late Reflections",
                    true ) } )
{
}

GordverbProcessor::~GordverbProcessor()
{
}

//==============================================================================
const juce::String GordverbProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GordverbProcessor::acceptsMidi() const
{
    return false;
}

bool GordverbProcessor::producesMidi() const
{
    return false;
}

bool GordverbProcessor::isMidiEffect() const
{
    return false;
}

double GordverbProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GordverbProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are
              // 0 programs, so this should be at least 1, even if you're not
              // really implementing programs.
}

int GordverbProcessor::getCurrentProgram()
{
    return 0;
}

void GordverbProcessor::setCurrentProgram( int index )
{
    juce::ignoreUnused( index );
}

const juce::String GordverbProcessor::getProgramName( int index )
{
    juce::ignoreUnused( index );
    return {};
}

void GordverbProcessor::changeProgramName( int index,
                                           const juce::String& newName )
{
    juce::ignoreUnused( index, newName );
}

//==============================================================================
void GordverbProcessor::prepareToPlay( double sampleRate, int samplesPerBlock )
{
    mReverb.prepareToPlay( sampleRate, samplesPerBlock );

    const auto channels =
        juce::jmax( getTotalNumInputChannels(), getTotalNumOutputChannels() );
    mDryWetMixer.prepare(
        { sampleRate, (juce::uint32)samplesPerBlock, (juce::uint32)channels } );

    this->setLatencySamples( mReverb.getLatency() );
}

void GordverbProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool GordverbProcessor::isBusesLayoutSupported(
    const BusesLayout& layouts ) const
{
    if ( layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
         layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo() )
        return false;

    // TODO: Support MISO
    if ( layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet() )
        return false;

    return true;
}

void GordverbProcessor::processBlock( juce::AudioBuffer<float>& buffer,
                                      juce::MidiBuffer& midiMessages )
{
    juce::ignoreUnused( midiMessages );
    juce::ScopedNoDenormals noDenormals;

    // todo: add flag to not do this unless needed
    auto wetParamValue = mState.getParameter( "wet_dry" )->getValue();
    mDryWetMixer.setWetMixProportion( wetParamValue );

    auto enableER = mState.getParameter( "enable_er" )->getValue();
    mReverb.enableEarlyReflections( enableER );
    auto enableLR = mState.getParameter( "enable_lr" )->getValue();
    mReverb.enableLateReflections( enableLR );

    auto reverbAmtValue = mState.getParameter( "reverb_amt" )->getValue();
    mReverb.setReverbAmount( reverbAmtValue );
    mDryWetMixer.setWetLatency( mReverb.getLatency() );
    auto inputBlock = this->getBusBuffer( buffer, true, 0 );
    mDryWetMixer.pushDrySamples( inputBlock );

    mReverb.processBlock( buffer );

    auto outputBlock = this->getBusBuffer( buffer, false, 0 );
    mDryWetMixer.mixWetSamples( outputBlock );
}

void GordverbProcessor::reset()
{
    mReverb.reset();
    mDryWetMixer.reset();
}

//==============================================================================
bool GordverbProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GordverbProcessor::createEditor()
{
    // TODO: Custom GUI
    return new juce::GenericAudioProcessorEditor( *this );
}

//==============================================================================
void GordverbProcessor::getStateInformation( juce::MemoryBlock& destData )
{
    // Store an xml representation of our state.
    if ( auto xmlState = mState.copyState().createXml() )
        copyXmlToBinary( *xmlState, destData );
}

void GordverbProcessor::setStateInformation( const void* data, int sizeInBytes )
{
    // Restore our plug-in's state from the xml representation stored in the
    // above method.
    if ( auto xmlState = getXmlFromBinary( data, sizeInBytes ) )
        mState.replaceState( juce::ValueTree::fromXml( *xmlState ) );
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GordverbProcessor();
}
