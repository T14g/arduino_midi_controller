#define MIDI_CHANNEL 1

// Big Arcade buttons with led
const int buttonPin1 = 2;  
const int ledPin1 = 3;    
const int buttonPin2 = 4;
const int ledPin2 = 5;
const int buttonPin3 = 6;
const int ledPin3 = 7;
const int buttonPin4 = 8;
const int ledPin4 = 9;

// Smaller Arcade buttons without led
const int buttonPin5 = 10;
const int buttonPin6 = 11;
const int buttonPin7 = 12;

// Some Notes that can be used
#define NOTE_C0 0x00 // 0
#define NOTE_C1 0x12 // 18
#define NOTE_C2 0x24 // 36
#define NOTE_E0 0x0B // 11
#define NOTE_A0 0x1A // 26
#define NOTE_D0 0x29 // 41
#define NOTE_B0 0x38 // 56
#define NOTE_D1 0x4B // 75
#define NOTE_G0 0x5C // 92
#define NOTE_E1 0x65 // 101
#define NOTE_C4 0x3C
#define NOTE_D4 0x3E
#define NOTE_E4 0x40
#define NOTE_F4 0x41
#define NOTE_G4 0x43
#define NOTE_A4 0x45
#define NOTE_B4 0x47

const int noteDelay = 400;

// Send a MIDI note on message
void noteOn(byte channel, byte pitch, byte velocity)
{
  // 0x90 is the first of 16 note on channels. Subtract one to go from MIDI's 1-16 channels to 0-15
  channel += 0x90 - 1;
  
  // Ensure we're between channels 1 and 16 for a note on message
  if (channel >= 0x90 && channel <= 0x9F)
  {
    // Serial.println("entrou");
    Serial.write(channel);
    Serial.write(pitch);
    Serial.write(velocity);
  }
}

// Send a MIDI note off message
void noteOff(byte channel, byte pitch)
{
  // 0x80 is the first of 16 note off channels. Subtract one to go from MIDI's 1-16 channels to 0-15
  channel += 0x80 - 1;
  
  // Ensure we're between channels 1 and 16 for a note off message
  if (channel >= 0x80 && channel <= 0x8F)
  {
    Serial.write(channel);
    Serial.write(pitch);
    Serial.write((byte)0x00);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT_PULLUP);  // Use internal pull-up resistor
  pinMode(ledPin1, OUTPUT);
  pinMode(buttonPin2, INPUT_PULLUP);  // Use internal pull-up resistor
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin3, INPUT_PULLUP);  // Use internal pull-up resistor
  pinMode(ledPin3, OUTPUT);
  pinMode(buttonPin4, INPUT_PULLUP);  // Use internal pull-up resistor
  pinMode(ledPin4, OUTPUT);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin7, INPUT_PULLUP);
}

void loop() {
  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);
  int buttonState3 = digitalRead(buttonPin3);
  int buttonState4 = digitalRead(buttonPin4);
  int buttonState5 = digitalRead(buttonPin5);
  int buttonState6 = digitalRead(buttonPin6);
  int buttonState7 = digitalRead(buttonPin7);
  
  if (buttonState1 == HIGH) {  
    digitalWrite(ledPin1, HIGH); 
    noteOn(MIDI_CHANNEL, NOTE_F4 , 0x7F); 
    delay(noteDelay);
    noteOff(MIDI_CHANNEL,NOTE_F4);
  } else {
    digitalWrite(ledPin1, LOW); 
  }

  if (buttonState2 == HIGH) {  
    digitalWrite(ledPin2, HIGH); 
    noteOn(MIDI_CHANNEL,  NOTE_D0 , 0x7F); 
    delay(noteDelay);
    noteOff(MIDI_CHANNEL, NOTE_D0);
  } else {
    digitalWrite(ledPin2, LOW);  
  }

  if (buttonState3 == HIGH) { 
    digitalWrite(ledPin3, HIGH);  
    noteOn(MIDI_CHANNEL, NOTE_G0 , 0x7F);
    delay(noteDelay);
    noteOff(MIDI_CHANNEL,NOTE_G0);
  } else {
    digitalWrite(ledPin3, LOW); 
  }

  if (buttonState4 == HIGH) {
    digitalWrite(ledPin4, HIGH);  
    noteOn(MIDI_CHANNEL, NOTE_B0 , 0x7F); // Channel 1,NOTE, maximum velocity
    delay(noteDelay);
    noteOff(MIDI_CHANNEL,NOTE_B0);
  } else {
    digitalWrite(ledPin4, LOW); 
  }

  if (buttonState5 == LOW) { 
    noteOn(MIDI_CHANNEL, NOTE_G4  , 0x7F);
    delay(noteDelay);
    noteOff(MIDI_CHANNEL,NOTE_G4);
  }

  
  if (buttonState6 == LOW) {  // Button is pressed when the pin reads LOW due to the pull-up resistor
    noteOn(MIDI_CHANNEL, NOTE_A4  , 0x7F); 
    delay(noteDelay);
    noteOff(MIDI_CHANNEL,NOTE_A4);
  }

  if (buttonState7 == LOW) {
    noteOn(MIDI_CHANNEL, NOTE_B4 , 0x7F); 
    delay(noteDelay);
    noteOff(MIDI_CHANNEL,NOTE_B4);
  }
}
