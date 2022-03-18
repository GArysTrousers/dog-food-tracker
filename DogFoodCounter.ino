#define SWITCH_PINS 14

int switchPins [SWITCH_PINS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16};
int state = 0;

int latchPin = 17;
int clockPin = 18;
int dataPin = 19;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  for (int i = 0; i < SWITCH_PINS; i++) {
    pinMode(switchPins[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
}

void loop() {
  Serial.println(HIGH);
  updateState();
  updateLights();
  delay(500);
  Serial.println(state, BIN);
}

int updateState() {
  state = getSwitchState(0);
  for (int i = 1; i < 7; i++) {
    state = state << 2;
    state += getSwitchState(i);
  }
}


int getSwitchState(int dayIndex) {
  if (digitalRead(switchPins[dayIndex * 2]) == 0) {
    return 0;
  }
  else if (digitalRead(switchPins[dayIndex * 2 + 1]) == 0) {
    return 3;
  }
  else {
    return 1;
  }
}

void updateLights() {
  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, LSBFIRST, state);
  shiftOut(dataPin, clockPin, LSBFIRST, state >> 8);
  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);
  // pause before next value:
}
