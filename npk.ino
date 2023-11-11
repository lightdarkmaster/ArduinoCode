const int soilMoisturePin = A0; // Analog pin for the soil moisture sensor
const int pHSensorPin = A1;    // Analog pin for the pH sensor
const int nitrogenSensorPin = A2; // Analog pin for the nitrogen sensor
const int potassiumSensorPin = A3; // Analog pin for the potassium sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read soil moisture level
  int soilMoistureValue = analogRead(soilMoisturePin);
  int soilMoisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);

  // Read pH level
  int pHValue = analogRead(pHSensorPin);
  float pH = map(pHValue, 0, 1023, 0, 14); // Assuming pH values are in the range of 0-14

  // Read nitrogen level
  int nitrogenValue = analogRead(nitrogenSensorPin);
  // Map the nitrogen reading to a suitable range (adjust mapping as needed)
  float nitrogenLevel = map(nitrogenValue, 0, 1023, 0, 100);

  // Read potassium level
  int potassiumValue = analogRead(potassiumSensorPin);
  // Map the potassium reading to a suitable range (adjust mapping as needed)
  float potassiumLevel = map(potassiumValue, 0, 1023, 0, 100);

  // Print the sensor values
  Serial.print("Soil Moisture: ");
  Serial.print(soilMoisturePercentage);
  Serial.println(" %");

  Serial.print("pH Level: ");
  Serial.println(pH);

  Serial.print("Nitrogen Level: ");
  Serial.println(nitrogenLevel);

  Serial.print("Potassium Level: ");
  Serial.println(potassiumLevel);

  // Add a delay to control the frequency of readings
  delay(1000); // Read data every 1 second (adjust as needed)
}
