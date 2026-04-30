// Volumix Open Firmware

const int NUM_SLIDERS = 5;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A4};

int analogSliderValues[NUM_SLIDERS];
int lastStableValues[NUM_SLIDERS];   // last value that passed the noise gate

// ==================== NOISE GATE ====================
// Ignores pot changes smaller than this to prevent jitter when pots are idle.
// Raise to 8-12 if you still see flickering.
const int NOISE_GATE = 4;

// ==================== BUTTON CONFIGURATION ====================
const int NUM_BUTTONS = 5;
const int buttonPins[NUM_BUTTONS] = {2, 3, 4, 5, 6};

// Button types: false = momentary, true = toggle
const bool buttonIsToggle[NUM_BUTTONS] = {false, false, false, false, false};

// ==================== BUTTON STATE VARIABLES ====================
const int BUTTON_OFF = 10000;
const int BUTTON_ON  = 10001;

const unsigned long DEBOUNCE_DELAY = 25; // milliseconds

int  buttonStates[NUM_BUTTONS];
int  lastButtonReading[NUM_BUTTONS];
unsigned long lastDebounceTime[NUM_BUTTONS];

bool buttonDebouncedState[NUM_BUTTONS];
bool buttonToggleState[NUM_BUTTONS];

void setup() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
    analogSliderValues[i] = analogRead(analogInputs[i]);
    lastStableValues[i]   = analogSliderValues[i];
  }

  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    buttonStates[i]         = BUTTON_OFF;
    lastButtonReading[i]    = HIGH;
    lastDebounceTime[i]     = 0;
    buttonDebouncedState[i] = false;
    buttonToggleState[i]    = false;
  }

  Serial.begin(9600);
}

void loop() {
  updateSliderValues();
  updateButtonStates();
  sendSliderValues();
  delay(10);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    int newVal = analogRead(analogInputs[i]);

    // Only accept the new reading if it moved more than NOISE_GATE counts.
    // This prevents tiny fluctuations from a resting pot causing volume jumps.
    if (abs(newVal - lastStableValues[i]) >= NOISE_GATE) {
      lastStableValues[i]   = newVal;
      analogSliderValues[i] = newVal;
    }
    // If change is smaller than the gate, keep the last stable value.
  }
}

void updateButtonStates() {
  unsigned long currentTime = millis();

  for (int i = 0; i < NUM_BUTTONS; i++) {
    int reading = digitalRead(buttonPins[i]);

    if (reading != lastButtonReading[i]) {
      lastDebounceTime[i] = currentTime;
    }

    if ((currentTime - lastDebounceTime[i]) > DEBOUNCE_DELAY) {
      bool isPressed = (reading == LOW);

      if (buttonIsToggle[i]) {
        if (isPressed && !buttonDebouncedState[i]) {
          buttonToggleState[i] = !buttonToggleState[i];
        }
        buttonDebouncedState[i] = isPressed;
        buttonStates[i] = buttonToggleState[i] ? BUTTON_ON : BUTTON_OFF;
      } else {
        buttonStates[i] = isPressed ? BUTTON_ON : BUTTON_OFF;
      }
    }

    lastButtonReading[i] = reading;
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);
    builtString += String("|");
  }

  for (int i = 0; i < NUM_BUTTONS; i++) {
    builtString += String(buttonStates[i]);
    if (i < NUM_BUTTONS - 1) {
      builtString += String("|");
    }
  }

  Serial.println(builtString);
}
