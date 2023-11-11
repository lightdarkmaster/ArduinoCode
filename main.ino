//library here
#include <DHT.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>   
#include <SoftwareSerial.h>
Servo myservoWindow;
//declare pins of the following sensors
const int fan = 4; //fan pin to pin 4
const int humiditySensor = 2; //Dht22 to pin 2
const int rainSensor = A1; //rainsensor to A1
//const int servoMotor = 12;//Servo motor to pin 12
const int pump = 7; //pump to pin 7
const int photoresistor = A0; //photoresistor to A0
//NPK Sensor
const int soilMoisturePin = A0; // Analog pin for the soil moisture sensor
const int pHSensorPin = A1;    // Analog pin for the pH sensor
const int nitrogenSensorPin = A2; // Analog pin for the nitrogen sensor
const int potassiumSensorPin = A3; 


#define DHTTYPE DHT22   // DHT 11 or DHT 22
DHT dht(humiditySensor, DHTTYPE);
const char* deviceName = "MyArduino";
//initial value of the following data
int temperatureVal;
int humidityVal;
int photoVal;
int rainVal;


LiquidCrystal_I2C lcd(0x27, 16, 2); 
SoftwareSerial BLEserial(10, 11); // RX, TX pins for Bluetooth communication
//bluetooth ---->> rx=11   tx=10
void setup() {
  Serial.begin(9600);
  BLEserial.begin(9600);
  while (!Serial);
  // put your setup code here, to run once:
  pinMode(fan, OUTPUT);
  pinMode(humiditySensor, INPUT);
  pinMode(rainSensor, INPUT);
  //pinMode(servoMotor, 12);
  pinMode(pump, OUTPUT);
  pinMode(photoVal, INPUT);
  myservoWindow.attach(9);

  dht.begin();
  lcd.init();                          // initialize the LCD
  lcd.backlight();   


  //digitalWrite(pump, HIGH);
  //delay(10000);
 //digitalWrite(pump, LOW);
}

void loop() {

//declaration of Variables here..


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


  if (BLEserial.available()) {
    char receivedChar = BLEserial.read();

    if (receivedChar == '1') {
      Serial.println("Fan ON");
      digitalWrite(fan, HIGH);  // Turn on the fan
    } else if (receivedChar == '2') {
      Serial.println("Fan OFF");
      digitalWrite(fan, LOW);   // Turn off the fan
    } else if (receivedChar == 'C') {
      Serial.println("Servo 0 degrees");
       myservoWindow.write(0);         // Set servo to 0 degrees
    } else if (receivedChar == 'E') {
      Serial.println("Servo 90 degrees");
       myservoWindow.write(90);        // Set servo to 90 degrees
    } else if (receivedChar == 'O') {
      Serial.println("Servo 180 degrees");
       myservoWindow.write(180);       // Set servo to 180 degrees
    } else if (receivedChar == 'W') {
      Serial.println("Watering");
      digitalWrite(pump,HIGH);
    }else if (receivedChar == 'S') {
      Serial.println("Stop Watering");
      digitalWrite(pump,LOW);
    }
    delay(1000);
  }


//if dire nauran {readDHT} else{rainsensor}
areadDHT();
areadRainsensor();//add automatic

}

void readRainsensor(){
  rainVal = analogRead(rainSensor);  // Read the sensor value
  Serial.print("Sensor value: ");
  Serial.println(rainVal);

  if (rainVal < 500) {  // If the sensor value is less than 500, it's raining
    Serial.println("It's raining!");
     //myservoWindow.write(90);
  }else{
    Serial.println("Not Raining");
     //myservoWindow.write(180);
  }
  delay(10);  
           // Delay for 500ms before taking another reading
}

void readDHT(){
    delay(10);  // Wait 2 seconds between measurements
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float foreignheight = temperature*9/5 +32;

  if(temperature >= 15){ //if temperature is equal or greater than 15
    //digitalWrite(fan, HIGH);
   //s180
  }else{
    //digitalWrite(fan, LOW);
    //s90
  }

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
//Serial
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print(foreignheight);  
  
  //LCD
  lcd.setCursor(0, 0);                       // set the cursor to the first column, first row
  lcd.print("T: ");                       // print the temperature label
  lcd.print(temperature);                    // print the temperature value
  lcd.print("C "); 
  lcd.print(foreignheight);
  lcd.print("F"); 


  lcd.setCursor(0, 1);                       // set the cursor to the first column, first row
  lcd.print("Humid: ");                       // print the temperature label
  lcd.print(humidity);                    // print the temperature value
  lcd.print(" %"); 
  delay(10);
 
}



///automatic



void areadRainsensor(){
  rainVal = analogRead(rainSensor);  // Read the sensor value
  Serial.print("Sensor value: ");
  Serial.println(rainVal);

  if (rainVal < 500) {  // If the sensor value is less than 500, it's raining
    Serial.println("It's raining!");
     myservoWindow.write(90);
  }else{
    Serial.println("Not Raining");
     myservoWindow.write(180);
  }
  delay(10);  
           // Delay for 500ms before taking another reading
}



void areadDHT(){
    delay(10);  // Wait 2 seconds between measurements
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float foreignheight = temperature*9/5 +32;

  if(temperature >= 15){ //if temperature is equal or greater than 15 deg condition
    digitalWrite(fan, HIGH);
    myservoWindow.write(180);
   //s180
  }else{
    //digitalWrite(fan, LOW);
    //s90
  }

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
//Serial
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print(foreignheight);  
  
  //LCD
  lcd.setCursor(0, 0);                       // set the cursor to the first column, first row
  lcd.print("T: ");                       // print the temperature label
  lcd.print(temperature);                    // print the temperature value
  lcd.print("C "); 
  lcd.print(foreignheight);
  lcd.print("F"); 


  lcd.setCursor(0, 1);                       // set the cursor to the first column, first row
  lcd.print("Humid: ");                       // print the temperature label
  lcd.print(humidity);                    // print the temperature value
  lcd.print(" %"); 
  delay(10);
 
}


