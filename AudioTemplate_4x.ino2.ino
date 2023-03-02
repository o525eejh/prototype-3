#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=93,106
AudioSynthWaveform       waveform2;      //xy=97,168
AudioSynthWaveformDc     dc1;            //xy=212,277
AudioMixer4              mixer1;         //xy=324,143
AudioEffectEnvelope      envelope2;      //xy=337,286
AudioFilterStateVariable filter1;        //xy=525,133
AudioEffectEnvelope      envelope1;      //xy=688,106
AudioOutputI2S           i2s1;           //xy=851,105
AudioConnection          patchCord1(waveform1, 0, mixer1, 0);
AudioConnection          patchCord2(waveform2, 0, mixer1, 1);
AudioConnection          patchCord3(dc1, envelope2);
AudioConnection          patchCord4(mixer1, 0, filter1, 0);
AudioConnection          patchCord5(envelope2, 0, filter1, 1);
AudioConnection          patchCord6(filter1, 0, envelope1, 0);
AudioConnection          patchCord7(envelope1, 0, i2s1, 0);
AudioConnection          patchCord8(envelope1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=401,59
// GUItool: end automatically generated code


int potPin = A0; 
Bounce button1 = Bounce (0, 

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13

void setup() {
  Serial.begin(9600);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.75);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  delay(1000);
  
 pinMode (0, INPUT_PULLUP); 
 waveform1.begin (1, 200, WAVEFORM_BANDLIMIT_SQUARE);
 waveform2.begin (1, 200, WAVEFORM_BANDLIMIT_SQUARE);

 mixer1.gain (0, .75); 
 mixer1.gain (1, .75); 
 

 envelope1.attack (40); 
 envelope1.decay (30);
 envelope1.sustain (.75);
 envelope1.release (1000); 

 filter1.frequency (100);
 filter1.resonance (.8); 
 filter1.octaveControl (6); 

 envelope2.attack (150); 
 envelope2.decay (120);
 envelope2.sustain (.75);
 envelope2.release (1000); 
 
 dc1.amplitude(1);
}

void loop() {

  int knob = analogRead(A1);
  float vol = knob / 1023.0;
  sgtl5000_1.volume(vol);
  
  button1.update (); 
  
  int wave1freq = analogRead (potPin) *2
  waveform1.frequency (wave1freq);

  float wave1freq = analogRead (potPin) /2 + .2 ;
  waveform2.frequency (wave2freq);   

  if (button1.fallingEdge()){ 
    envelope1.noteOn();
    envelope2.noteOn(); 
  }

  if (button1.risingEdge()) { 
    envelope1.noteOff();
    envelope2.noteOff();
    
  }
}
