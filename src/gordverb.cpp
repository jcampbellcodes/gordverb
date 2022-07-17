#include "gordverb.h"

//==============================================================================
GordverbProcessor::GordverbProcessor()
    : AudioProcessor(
          BusesProperties()
              .withInput( "Input", juce::AudioChannelSet::stereo(), true )
              .withOutput( "Output", juce::AudioChannelSet::stereo(), true ) )
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
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused( sampleRate, samplesPerBlock );
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
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for ( auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i )
        buffer.clear( i, 0, buffer.getNumSamples() );

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for ( int channel = 0; channel < totalNumInputChannels; ++channel )
    {
        auto* channelData = buffer.getWritePointer( channel );
        juce::ignoreUnused( channelData );
        // ..do something to the data...
    }
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
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused( destData );
}

void GordverbProcessor::setStateInformation( const void* data, int sizeInBytes )
{
    // You should use this method to restore your parameters from this memory
    // block, whose contents will have been created by the getStateInformation()
    // call.
    juce::ignoreUnused( data, sizeInBytes );
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GordverbProcessor();
}
