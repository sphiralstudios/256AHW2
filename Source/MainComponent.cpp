// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple Faust-based sawtooth synthesizer.

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED
#define pi M_PI

#include "../JuceLibraryCode/JuceHeader.h"
//#include "faust/Saw.h" // the Faust module
#include "MySynth.h"
#include "FaustReverb.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent :
    public AudioAppComponent,
    private Slider::Listener

{
public:
    //==============================================================================
    MainContentComponent() : currentSampleRate(0.0)
    {
//        addAndMakeVisible (frequencySlider);
//        frequencySlider.setRange (50.0, 5000.0);
//        frequencySlider.setSkewFactorFromMidPoint (500.0); // [4]
//        frequencySlider.setValue(1000);
//        frequencySlider.addListener (this);
        
//        addAndMakeVisible(frequencyLabel);
//        frequencyLabel.setText ("Frequency", dontSendNotification);
//        frequencyLabel.attachToComponent (&frequencySlider, true);
        
        addAndMakeVisible (gainSlider);
        gainSlider.setRange (0.0, 1.0);
        gainSlider.setValue(0.5);
        gainSlider.addListener (this);
        
        addAndMakeVisible(gainLabel);
        gainLabel.setText ("Master Volume", dontSendNotification);
        gainLabel.attachToComponent (&gainSlider, true);
        
//        addAndMakeVisible(onOffButton);
//        onOffButton.addListener(this);
//        
//        addAndMakeVisible(onOffLabel);
//        onOffLabel.setText ("On/Off", dontSendNotification);
//        onOffLabel.attachToComponent (&onOffButton, true);
        
        setSize (600, 700);
        
        nChans = 2; // number of output audio channels
        
        setAudioChannels (0, nChans);
        
        audioBuffer = new float*[nChans];
    }

    ~MainContentComponent()
    {
        shutdownAudio();
        delete [] audioBuffer;
    }

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        currentSampleRate = sampleRate;
        blockSize = samplesPerBlockExpected;
        
        synth.init(sampleRate); // initializing the Faust module
        synth.buildUserInterface(&synthControl); // linking the Faust module to the controler
        
        reverb.init(sampleRate);
        reverb.buildUserInterface(&reverbControl);
        

    }
    
    // Case where the buffer loop is implemented in Faust (faustSample is not needed in that case)
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        for(int channel = 0; channel < nChans; ++channel){
            audioBuffer[channel] = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);
        }
        // any processing before going to "saw" could be done here in a dedicated buffer loop
        
        synth.compute(blockSize, NULL, audioBuffer); // computing one block with Faust
        
        reverb.compute(blockSize, audioBuffer, audioBuffer);
        // any processing before going to "saw" could be done here in a dedicated buffer loop
        // An alternative solution could be to use only one buffer loop and to set the blockSize
        // of "reverb.compute" to 1...
    }
    
    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()
    }

    void resized() override
    {
        const int sliderLeft = 120;
        gainSlider.setBounds (sliderLeft, 10, getWidth() - sliderLeft - 20, 20);
    }
    
    void mouseDrag (const MouseEvent& e) override
    {
        if(e.position.x > 0 && e.position.x < getWidth() && e.position.y > 0 && e.position.y < getHeight()) {
            double xo = e.position.x - getWidth()/2;
            double yo = -(e.position.y - getHeight()/2);
            double r = pow((pow(xo,2)+pow(yo,2)),0.5);
            double rmax = pow((pow(getWidth()/2,2) + pow(getHeight()/2,2)),0.5);
            double cutoff = r/rmax * 5000;
            double theta;
            double spiral, ratio;
            
            if (xo<0 && yo<0) {
                theta=pi+atan(yo/xo);
            } else if (xo>0 && yo<0)
                theta=(2*pi)+atan(yo/xo);
            else if (xo<0 && yo>0)
                theta = pi + atan(yo/xo);
                
                else {
                    theta=atan(yo/xo);
            
                }
//            
//            DBG("X = " << xo);
//            DBG("Y = " << yo);
//            DBG("Theta = " << theta);
            double freq1, freq2, gain1, gain2;
            spiral = (log(r)/log(2.0));
            ratio = ((2 * pi * spiral)-theta)/(2* pi);
            if((ratio-floor(ratio))>=0.5) {
                freq1 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)+1) + 1);
                freq2 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)) + 1);
                gain1 = (ratio - floor(ratio)) * gainSlider.getValue();
                gain2 = (1 - (ratio-floor(ratio))) * gainSlider.getValue();
            } else {
                freq2 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)+1) + 1);
                freq1 = pow(2.0, (theta/(2*pi)) + 0.55 + (floor(ratio)) + 1);
                gain2 = (ratio - floor(ratio)) * gainSlider.getValue();
                gain1 = (1 - (ratio-floor(ratio))) * gainSlider.getValue();
            }
            
            background = Colour (theta/(2* pi),0.8f,0.8f,1.0f);
            repaint();
            
            
            synthControl.setParamValue("/synth/freq1", freq1);
            synthControl.setParamValue("/synth/freq2", freq2);
            synthControl.setParamValue("/synth/gain1", gain1);
            synthControl.setParamValue("/synth/gain2", gain2);
            
            synthControl.setParamValue("/synth/cutoff", cutoff);
            synthControl.setParamValue("/synth/gate", 1);
        
        } else {
            synthControl.setParamValue("/synth/gate", 0);
            background = juce::Colour::greyLevel(0.8);
            repaint();
        }
        
        
    }
    
    void paint( Graphics& g ) override
    {
        g.fillAll(background);
        g.setFont(48.0f);
        g.drawText("+", getLocalBounds(), Justification::centred, true);
        
//        Image background = ImageCache.getFromFile(spiralbackground2.png);
        //Image::BitmapData::BitmapData("spiralbackground2.png", juce::MemoryMappedFile::readOnly);
//        g.drawImage( "spiralbackground2.png", 0, 0, getWidth(), getHeight(), 0, 0, "spiralbackground2.png".getWidth(), "spiralbackground2.png".getHeight(), false );
    }
    
    void mouseUp (const MouseEvent& e) override
    {
        synthControl.setParamValue("/synth/gate",0);
        background = juce::Colour::greyLevel(0.8);
        repaint();
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        if (currentSampleRate > 0.0){
            if (slider == &gainSlider)
            {
//                synthControl.setParamValue("/synth/gain", gainSlider.getValue());
            }
        }
    }
    
    
private:
//    Saw saw; // the Faust module (Saw.h)
    MySynth synth;
    FaustReverb reverb;
    MapUI synthControl, reverbControl; // used to easily control the Faust module (Saw.h)
    Colour background;
    
    Slider gainSlider;

    Label gainLabel;
    
    int blockSize, nChans;
    double currentSampleRate;
    
    float** audioBuffer; // multichannel audio buffer used both for input and output

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
