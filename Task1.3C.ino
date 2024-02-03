#define TEMP_SENSOR_PIN A0  
#define PIR_PIN 2           
#define LED_PIN 13          

volatile bool motionDetected = false;
volatile bool led_state = LOW;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(PIR_PIN), toggle, CHANGE);
}

void loop() {
  delay(1000);  

  int sensorValue = analogRead(TEMP_SENSOR_PIN);

  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;

  Serial.print("Temperature: ");
  Serial.println(temperature);

  if (temperature > 10.0) {
    Serial.println("Temperature is more than 10 degrees Celsius");
    digitalWrite(LED_PIN, HIGH);
  } else {
    Serial.println("Temperature is 10 degrees Celsius or lower");
    digitalWrite(LED_PIN, LOW);   
  }

  if (motionDetected) {
    Serial.println("Motion Detected");
  } else {
    Serial.println("Motion Not Detected");
  }
}

void toggle() {
  motionDetected = !motionDetected;
  digitalWrite(LED_PIN, motionDetected);
}
