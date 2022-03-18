#define SWITCH_PINS 14

int switchPins [SWITCH_PINS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16};
uint16_t state = 0;

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
}

void loop() {
  updateState();
  updateLights();
  delay(500);
}

void updateState() {
  state = getSwitchState(0);
  for (int i = 1; i < 7; i++) {
    state = state << 2;
    state += getSwitchState(i);
  }
}

uint16_t getSwitchState(int dayIndex) {
  if (digitalRead(switchPins[dayIndex * 2]) == 0) {
    return 0;
  }
  else if (digitalRead(switchPins[dayIndex * 2 + 1]) == 0) {
    return 3;
  }
  else {
    return 2;
  }
}

void updateLights() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, state);
  shiftOut(dataPin, clockPin, LSBFIRST, state >> 8);
  digitalWrite(latchPin, HIGH);
}
