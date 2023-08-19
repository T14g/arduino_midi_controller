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

const int joystickButtonPin = 13;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // Adjust this value as needed
int joystickPinX = A0;
int joystickThreshold = 512;
int prevJoyXValue = 0;   // Previous joystick x-axis value
int currentOctave = 0;


#define NOTE_C0 0x00
#define NOTE_CS0 0x01
#define NOTE_D0 0x02
#define NOTE_DS0 0x03
#define NOTE_E0 0x04
#define NOTE_F0 0x05
#define NOTE_FS0 0x06
#define NOTE_G0 0x07
#define NOTE_GS0 0x08
#define NOTE_A0 0x09
#define NOTE_AS0 0x0A
#define NOTE_B0 0x0B

#define NOTE_C1 0x0C
#define NOTE_CS1 0x0D
#define NOTE_D1 0x0E
#define NOTE_DS1 0x0F
#define NOTE_E1 0x10
#define NOTE_F1 0x11
#define NOTE_FS1 0x12
#define NOTE_G1 0x13
#define NOTE_GS1 0x14
#define NOTE_A1 0x15
#define NOTE_AS1 0x16
#define NOTE_B1 0x17

#define NOTE_C2 0x18
#define NOTE_CS2 0x19
#define NOTE_D2 0x1A
#define NOTE_DS2 0x1B
#define NOTE_E2 0x1C
#define NOTE_F2 0x1D
#define NOTE_FS2 0x1E
#define NOTE_G2 0x1F
#define NOTE_GS2 0x20
#define NOTE_A2 0x21
#define NOTE_AS2 0x22
#define NOTE_B2 0x23

#define NOTE_C3 0x24
#define NOTE_CS3 0x25
#define NOTE_D3 0x26
#define NOTE_DS3 0x27
#define NOTE_E3 0x28
#define NOTE_F3 0x29
#define NOTE_FS3 0x2A
#define NOTE_G3 0x2B
#define NOTE_GS3 0x2C
#define NOTE_A3 0x2D
#define NOTE_AS3 0x2E
#define NOTE_B3 0x2F

#define NOTE_C4 0x30
#define NOTE_CS4 0x31
#define NOTE_D4 0x32
#define NOTE_DS4 0x33
#define NOTE_E4 0x34
#define NOTE_F4 0x35
#define NOTE_FS4 0x36
#define NOTE_G4 0x37
#define NOTE_GS4 0x38
#define NOTE_A4 0x39
#define NOTE_AS4 0x3A
#define NOTE_B4 0x3B

#define NOTE_C5 0x3C
#define NOTE_CS5 0x3D
#define NOTE_D5 0x3E
#define NOTE_DS5 0x3F
#define NOTE_E5 0x40
#define NOTE_F5 0x41
#define NOTE_FS5 0x42
#define NOTE_G5 0x43
#define NOTE_GS5 0x44
#define NOTE_A5 0x45
#define NOTE_AS5 0x46
#define NOTE_B5 0x47

#define NOTE_C6 0x48
#define NOTE_CS6 0x49
#define NOTE_D6 0x4A
#define NOTE_DS6 0x4B
#define NOTE_E6 0x4C
#define NOTE_F6 0x4D
#define NOTE_FS6 0x4E
#define NOTE_G6 0x4F
#define NOTE_GS6 0x50
#define NOTE_A6 0x51
#define NOTE_AS6 0x52
#define NOTE_B6 0x53

#define NOTE_C7 0x54
#define NOTE_D7 0x55
#define NOTE_DS7 0x56
#define NOTE_E7 0x57
#define NOTE_F7 0x58
#define NOTE_FS7 0x59
#define NOTE_G7 0x5A
#define NOTE_GS7 0x5B
#define NOTE_A7 0x5C
#define NOTE_AS7 0x5D
#define NOTE_B7 0x5E

const int numNotes = 8;

const int C_NOTES[numNotes] = { 0x00, 0x0C, 0x18, 0x24, 0x30, 0x3C, 0x48, 0x54 };
const int D_NOTES[numNotes] = { 0x0C, 0x1C, 0x2C, 0x3C, 0x4C, 0x5C, 0x6C, 0x7C };
const int E_NOTES[numNotes] = { 0x0D, 0x1D, 0x2D, 0x3D, 0x4D, 0x5D, 0x6D, 0x7D };
const int F_NOTES[numNotes] = { 0x0E, 0x1E, 0x2E, 0x3E, 0x4E, 0x5E, 0x6E, 0x7E };
const int G_NOTES[numNotes] = { 0x0F, 0x1F, 0x2F, 0x3F, 0x4F, 0x5F, 0x6F, 0x7F };
const int A_NOTES[numNotes] = { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80 };
const int B_NOTES[numNotes] = { 0x11, 0x21, 0x31, 0x41, 0x51, 0x61, 0x71, 0x81 };

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

  pinMode(joystickButtonPin, INPUT_PULLUP);
  pinMode(joystickPinX, INPUT);
}

void loop() {
  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);
  int buttonState3 = digitalRead(buttonPin3);
  int buttonState4 = digitalRead(buttonPin4);
  int buttonState5 = digitalRead(buttonPin5);
  int buttonState6 = digitalRead(buttonPin6);
  int buttonState7 = digitalRead(buttonPin7);

  int joystickValueX = analogRead(joystickPinX);
  unsigned long currentMillis = millis();



  if (joystickValueX < (joystickThreshold - 100)) {
    if(currentOctave < 7) {
     currentOctave++;
   }
    delay(500);
  } else if (joystickValueX > (joystickThreshold + 100)) {
   if(currentOctave > 0) {
     currentOctave--;
   }
   delay(500);
  }
  
  if (buttonState1 == HIGH) {  
    // Serial.println("botao 1");
    digitalWrite(ledPin1, HIGH); 
    noteOn(MIDI_CHANNEL, C_NOTES[currentOctave] , 0x7F); 
    delay(noteDelay);
    noteOff(MIDI_CHANNEL, C_NOTES[currentOctave]);
  } else {
    digitalWrite(ledPin1, LOW); 
  }

  if (buttonState2 == HIGH) {  
    // Serial.println("botao 2");
    digitalWrite(ledPin2, HIGH); 
    noteOn(MIDI_CHANNEL,  D_NOTES[currentOctave] , 0x7F); 
    delay(noteDelay);
    noteOff(MIDI_CHANNEL, D_NOTES[currentOctave]);
  } else {
    digitalWrite(ledPin2, LOW);  
  }

  if (buttonState3 == HIGH) { 
    // Serial.println("botao 3");
    digitalWrite(ledPin3, HIGH);  
    noteOn(MIDI_CHANNEL,  E_NOTES[currentOctave] , 0x7F);
    delay(noteDelay);
    noteOff(MIDI_CHANNEL, E_NOTES[currentOctave]);
  } else {
    digitalWrite(ledPin3, LOW); 
  }

  if (buttonState4 == HIGH) {
    // Serial.println("botao 4");
    digitalWrite(ledPin4, HIGH);  
    noteOn(MIDI_CHANNEL,  F_NOTES[currentOctave] , 0x7F); // Channel 1,NOTE, maximum velocity
    delay(noteDelay);
    noteOff(MIDI_CHANNEL, F_NOTES[currentOctave]);
  } else {
    digitalWrite(ledPin4, LOW); 
  }

  if (buttonState5 == LOW) { 
    noteOn(MIDI_CHANNEL,  G_NOTES[currentOctave]  , 0x7F);
    delay(noteDelay);
    noteOff(MIDI_CHANNEL, G_NOTES[currentOctave]);
  }

  
  if (buttonState6 == LOW) {  // Button is pressed when the pin reads LOW due to the pull-up resistor
    noteOn(MIDI_CHANNEL,  A_NOTES[currentOctave]  , 0x7F); 
    delay(noteDelay);
    noteOff(MIDI_CHANNEL, A_NOTES[currentOctave]);
  }

  if (buttonState7 == LOW) {
    noteOn(MIDI_CHANNEL,  B_NOTES[currentOctave] , 0x7F); 
    delay(noteDelay);
    noteOff(MIDI_CHANNEL, B_NOTES[currentOctave]);
  }
}
