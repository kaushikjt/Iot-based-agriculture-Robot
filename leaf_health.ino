#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

#define BUZZER_HEALTHY 9
#define BUZZER_UNHEALTHY 10

void setup() {
  Serial.begin(9600);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  pinMode(BUZZER_HEALTHY, OUTPUT);
  pinMode(BUZZER_UNHEALTHY, OUTPUT);

  digitalWrite(S0, HIGH); // Frequency scaling to 100%
  digitalWrite(S1, LOW);
}

void loop() {
  int redValue = readColor(LOW, LOW); // Red
  int greenValue = readColor(HIGH, HIGH); // Green
  int blueValue = readColor(LOW, HIGH); // Blue

  Serial.print("R: "); Serial.print(redValue);
  Serial.print(" G: "); Serial.print(greenValue);
  Serial.print(" B: "); Serial.println(blueValue);

  if (isGreenLeaf(redValue, greenValue, blueValue)) {
    Serial.println("Leaf is Healthy (Green)");
    digitalWrite(BUZZER_HEALTHY, HIGH);
    delay(1000);
    digitalWrite(BUZZER_HEALTHY, LOW);
  } else if (isYellowLeaf(redValue, greenValue, blueValue)) {
    Serial.println("Leaf is Unhealthy (Yellow)");
    digitalWrite(BUZZER_UNHEALTHY, HIGH);
    delay(1000);
    digitalWrite(BUZZER_UNHEALTHY, LOW);
  } else {
    Serial.println("Unable to determine leaf health.");
  }

  delay(1000); // Delay for 1 second before next reading
}

int readColor(bool s2, bool s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);
  delay(100); // Wait for sensor to stabilize

  // Read frequency from sensor output pin
  int frequency = pulseIn(sensorOut, LOW);
  return frequency;
}

bool isGreenLeaf(int red, int green, int blue) {
  // Adjust these values based on your specific sensor and leaf conditions
  bool isGreen = (green < red) && (green < blue);
  if (isGreen) {
    Serial.print("Green Threshold - R: "); Serial.print(red);
    Serial.print(" G: "); Serial.print(green);
    Serial.print(" B: "); Serial.println(blue);
  }
  return isGreen;
}

bool isYellowLeaf(int red, int green, int blue) {
  // Adjust these values based on your specific sensor and leaf conditions
  bool isYellow = (red < green) && (green < blue);
  if (isYellow) {
    Serial.print("Yellow Threshold - R: "); Serial.print(red);
    Serial.print(" G: "); Serial.print(green);
    Serial.print(" B: "); Serial.println(blue);
  }
  return isYellow;
}
