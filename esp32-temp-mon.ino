#define TEMP_PIN   34
#define LED_PIN    2
#define BUTTON_PIN 0

hw_timer_t *timer = NULL;

volatile bool sampleFlag = false;
volatile int sampleIndex = 0;

const uint32_t sampleIntervals[] = {
  1000000,  // 1 second
  500000,   // 500 ms
  200000    // 200 ms
};

void IRAM_ATTR onTimer() {
  sampleFlag = true;   // ISR only sets flag
}

void IRAM_ATTR onButtonPress() {
  sampleIndex = (sampleIndex + 1) % 3;
  timerAlarmWrite(timer, sampleIntervals[sampleIndex], true);
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  timer = timerBegin(0, 80, true);            // 1 µs tick
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, sampleIntervals[0], true);
  timerAlarmEnable(timer);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),
                  onButtonPress, FALLING);
}

void loop() {
  if (sampleFlag) {
    sampleFlag = false;

    int adcValue = analogRead(TEMP_PIN);
    float voltage = (adcValue * 3.3f) / 4095.0f;
    float temperatureC = voltage * 100.0f;

    Serial.print("Temp: ");
    Serial.print(temperatureC);
    Serial.print(" C | Interval: ");
    Serial.print(sampleIntervals[sampleIndex] / 1000);
    Serial.println(" ms");

    digitalWrite(LED_PIN, temperatureC > 30.0);
  }
}
