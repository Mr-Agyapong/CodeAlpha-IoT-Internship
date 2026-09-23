// CodeAlpha IoT Internship - Task 2
// LDR-Based Automatic Light System

const int LDR_PIN = A0;
const int LED_PIN = 7;

int lightValue = 0;

const int THRESHOLD = 500;

void setup() {
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);

  Serial.println("LDR Automatic Light System");
  Serial.println("--------------------------");
}

void loop() {

  // Read the LDR sensor
  lightValue = analogRead(LDR_PIN);

  // Display the sensor value
  Serial.print("LDR Value: ");
  Serial.print(lightValue);

  // Turn LED ON when it is dark
  if (lightValue < THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println(" -> DARK - LED ON");
  }

  // Turn LED OFF when it is bright
  else {
    digitalWrite(LED_PIN, LOW);
    Serial.println(" -> BRIGHT - LED OFF");
  }

  delay(500);
}
