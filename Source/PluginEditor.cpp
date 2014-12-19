/*
 ==============================================================================
 
 This file was auto-generated by the Jucer!
 
 It contains the basic startup code for a Juce application.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
// setting up all of the labels and sliders
JuceDemoPluginAudioProcessorEditor::JuceDemoPluginAudioProcessorEditor (JuceDemoPluginAudioProcessor& owner)
: AudioProcessorEditor (owner),
midiKeyboard (owner.keyboardState, MidiKeyboardComponent::horizontalKeyboard),
infoLabel (String::empty),
waveLabel1("", "Wave"),
freqLabel1("", "Freq"),
filterType1("", "Filter"),
filtFLabel1("", "Freq"),
filtRLabel1("", "Res"),
aLabel("", "Attack"),
dLabel("", "Decay"),
sLabel("", "Sustain"),
rLabel("", "Release"),
oscFreq("Freq"),
filtFreq1("Freq"),
filtRes1("Resonance"),
sAttack("Attack"),
sDecay("Decay"),
sSustain("Sustain"),
sRelease("Release"),
comboWaves("Waves"),
comboFilter("Filter")
{

    
    // testing out comboBox
    addAndMakeVisible(comboWaves);
    comboWaves.setEditableText(false);
    comboWaves.setJustificationType(Justification::centred);
    comboWaves.addItem("Sine", 1);
    comboWaves.addItem("Saw", 2);
    comboWaves.addItem("Tri", 3);
    comboWaves.addItem("Square", 4);
    //comboWaves.addListener(this);
    comboWaves.setSelectedId(1);
    
    // oscillator waveform select label
    addAndMakeVisible(waveLabel1);
    
    // oscillator frequency slider box
    addAndMakeVisible(oscFreq);
    oscFreq.setSliderStyle(Slider::LinearBar);
    oscFreq.addListener(this);
    oscFreq.setRange(-24.0, 24.0, 0.1);
    
    // filter parameters
    addAndMakeVisible(comboFilter);
    comboFilter.setEditableText(false);
    comboFilter.setJustificationType(Justification::centred);
    comboFilter.addItem("LPF", 1);
    comboFilter.addItem("HPF", 2);
    comboFilter.setSelectedId(1);
    
    addAndMakeVisible(filtFreq1);
    filtFreq1.setSliderStyle(Slider::Rotary);
    filtFreq1.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    filtFreq1.addListener(this);
    filtFreq1.setRange(0.0, 20000.0);
    
    addAndMakeVisible(filtRes1);
    filtRes1.setSliderStyle(Slider::Rotary);
    filtRes1.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    filtRes1.addListener(this);
    filtRes1.setRange(0.0, 1.0);
    
    // ADSR parameters
    addAndMakeVisible(sAttack);
    sAttack.setSliderStyle(Slider::Rotary);
    sAttack.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    sAttack.addListener(this);
    sAttack.setRange(0.0, 1.0, 0.01);
    
    addAndMakeVisible(sDecay);
    sDecay.setSliderStyle(Slider::Rotary);
    sDecay.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    sDecay.addListener(this);
    sDecay.setRange(0.0, 1.0, 0.01);
    
    addAndMakeVisible(sSustain);
    sSustain.setSliderStyle(Slider::Rotary);
    sSustain.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    sSustain.addListener(this);
    sSustain.setRange(0.0, 1.0, 0.01);
    
    addAndMakeVisible(sRelease);
    sRelease.setSliderStyle(Slider::Rotary);
    sRelease.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    sRelease.addListener(this);
    sRelease.setRange(0.0, 1.0, 0.01);

    
    // add some labels for the sliders..
    waveLabel1.attachToComponent(&comboWaves, false);
    waveLabel1.setFont(Font (11.0f));
    
    freqLabel1.attachToComponent(&oscFreq, false);
    freqLabel1.setFont(Font (11.0f));
    
    filterType1.attachToComponent(&comboFilter, false);
    filterType1.setFont(Font (11.0f));
    
    filtFLabel1.attachToComponent(&filtFreq1, false);
    filtFLabel1.setFont(Font (11.0f));
    
    filtRLabel1.attachToComponent(&filtRes1, false);
    filtRLabel1.setFont(Font (11.0f));
    
    aLabel.attachToComponent(&sAttack, false);
    aLabel.setFont(Font (11.0f));
    
    dLabel.attachToComponent(&sDecay, false);
    dLabel.setFont(Font (11.0f));
    
    sLabel.attachToComponent(&sSustain, false);
    sLabel.setFont(Font (11.0f));
    
    rLabel.attachToComponent(&sRelease, false);
    rLabel.setFont(Font (11.0f));
    
    
    
    // add the midi keyboard component..
    addAndMakeVisible (midiKeyboard);
    
    // add a label that will display the current timecode and status..
    addAndMakeVisible (infoLabel);
    infoLabel.setColour (Label::textColourId, Colours::blue);
    
    // add the triangular resizer component for the bottom-right of the UI
    addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
    resizeLimits.setSizeLimits (150, 150, 800, 300);
    
    // set our component's initial size to be the last one that was stored in the filter's settings
    //setSize (owner.lastUIWidth,
    //         owner.lastUIHeight);
    setSize(800, 400);
    
    startTimer (50);
}


JuceDemoPluginAudioProcessorEditor::~JuceDemoPluginAudioProcessorEditor()
{
}

//==============================================================================
void JuceDemoPluginAudioProcessorEditor::paint (Graphics& g)
{
    g.setGradientFill (ColourGradient (Colours::white, 0, 0,
                                       Colours::grey, 0, (float) getHeight(), false));
    g.fillAll();
}

void JuceDemoPluginAudioProcessorEditor::resized()
{
    // placing the parameters on screen
    infoLabel.setBounds (10, 4, 400, 25);
    waveLabel1.setBounds(20, 50, 80, 20);
    comboWaves.setBounds(20, 60, 80, 20);
    oscFreq.setBounds(20, 100, 80, 20);
    comboFilter.setBounds(120, 60, 100, 20);
    // 200 was filt1 original
    filtFreq1.setBounds(120, 100, 40, 40);
    filtRes1.setBounds(170, 100, 40, 40);
    sAttack.setBounds(250, 60, 40, 40);
    sDecay.setBounds(300, 60, 40, 40);
    sSustain.setBounds(350, 60, 40, 40);
    sRelease.setBounds(400, 60, 40, 40);
    
    const int keyboardHeight = 70;
    midiKeyboard.setBounds (4, getHeight() - keyboardHeight - 4, getWidth() - 8, keyboardHeight);
    
    resizer->setBounds (getWidth() - 16, getHeight() - 16, 16, 16);
    
    getProcessor().lastUIWidth = getWidth();
    getProcessor().lastUIHeight = getHeight();
}

//==============================================================================
// This timer periodically checks whether any of the filter's parameters have changed...
void JuceDemoPluginAudioProcessorEditor::timerCallback()
{
    JuceDemoPluginAudioProcessor& ourProcessor = getProcessor();
    
    AudioPlayHead::CurrentPositionInfo newPos (ourProcessor.lastPosInfo);
    
    if (lastDisplayedPosition != newPos)
        displayPositionInfo (newPos);
    
//    gainSlider.setValue (ourProcessor.gain, dontSendNotification);
//    delaySlider.setValue (ourProcessor.delay, dontSendNotification);
}

// Tried implementing a comboBox listener, but just couldn't understand how

// This is our Slider::Listener callback, when the user drags a slider.
void JuceDemoPluginAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
        //processor.lpFreq = filtFreq1.getValue();
    if (slider == &filtFreq1) { // checks for filter knob
        getProcessor().setParameterNotifyingHost(JuceDemoPluginAudioProcessor::lpFreq, (double) filtFreq1.getValue());
    }

}

//==============================================================================
// Old stuff that's part of the demo, but was thinking of keepign in.
// quick-and-dirty function to format a timecode string
static String timeToTimecodeString (const double seconds)
{
    const double absSecs = std::abs (seconds);
    
    const int hours =  (int) (absSecs / (60.0 * 60.0));
    const int mins  = ((int) (absSecs / 60.0)) % 60;
    const int secs  = ((int) absSecs) % 60;
    
    String s (seconds < 0 ? "-" : "");
    
    s << String (hours).paddedLeft ('0', 2) << ":"
    << String (mins) .paddedLeft ('0', 2) << ":"
    << String (secs) .paddedLeft ('0', 2) << ":"
    << String (roundToInt (absSecs * 1000) % 1000).paddedLeft ('0', 3);
    
    return s;
}

// quick-and-dirty function to format a bars/beats string
static String ppqToBarsBeatsString (double ppq, double /*lastBarPPQ*/, int numerator, int denominator)
{
    if (numerator == 0 || denominator == 0)
        return "1|1|0";
    
    const int ppqPerBar = (numerator * 4 / denominator);
    const double beats  = (fmod (ppq, ppqPerBar) / ppqPerBar) * numerator;
    
    const int bar    = ((int) ppq) / ppqPerBar + 1;
    const int beat   = ((int) beats) + 1;
    const int ticks  = ((int) (fmod (beats, 1.0) * 960.0 + 0.5));
    
    String s;
    s << bar << '|' << beat << '|' << ticks;
    return s;
}

// Updates the text in our position label.
void JuceDemoPluginAudioProcessorEditor::displayPositionInfo (const AudioPlayHead::CurrentPositionInfo& pos)
{
    lastDisplayedPosition = pos;
    String displayText;
    displayText.preallocateBytes (128);
    
    displayText << String (pos.bpm, 2) << " bpm, "
    << pos.timeSigNumerator << '/' << pos.timeSigDenominator
    << "  -  " << timeToTimecodeString (pos.timeInSeconds)
    << "  -  " << ppqToBarsBeatsString (pos.ppqPosition, pos.ppqPositionOfLastBarStart,
                                        pos.timeSigNumerator, pos.timeSigDenominator);
    
    if (pos.isRecording)
        displayText << "  (recording)";
    else if (pos.isPlaying)
        displayText << "  (playing)";
    
    infoLabel.setText ("[" + SystemStats::getJUCEVersion() + "]   " + displayText, dontSendNotification);
}
