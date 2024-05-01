#include <AnalogSensor.h>
#include <EasyButton.h>
#include <LiquidCrystalI2C.h>
// #include <Wire.h>

#define BUTTON1_PIN 3
#define BUTTON2_PIN 4

#define LONG_PRESS_DURATION 1000

AnalogSensor analogSensor(A0); // Create an instance of the AnalogSensor on pin A0
EasyButton button1(BUTTON1_PIN);
EasyButton button2(BUTTON2_PIN);

LiquidCrystalI2C lcd(0x27,16,2);

long lastDisplayDataTime = 0;
long displayDataIntervalInSeconds = 1;


void onPressedCalibrateLow() {
    Serial.println("Calibrated low");

    analogSensor.setCalibrationLow(analogSensor.readRaw());

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Calibrated low");

    delay(1000);
}

void onPressedCalibrateHigh() {
    Serial.println("Calibrated high");

    analogSensor.setCalibrationHigh(analogSensor.readRaw());

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Calibrated high");

    delay(1000);
}

void handleSensorData(int value) {
  int rawValue = analogSensor.readRaw();
  Serial.print("Raw: ");
  Serial.print(rawValue);
  Serial.print(", Calibrated: ");
  Serial.print(value);
  Serial.print(", Low: ");
  Serial.print(analogSensor.readCalibrationLow());
  Serial.print(", High: ");
  Serial.print(analogSensor.readCalibrationHigh());
  Serial.println();

  displayData(value);
}

void displayData(int reading)
{
  bool displayDataIsDue = millis() - lastDisplayDataTime >= displayDataIntervalInSeconds*1000//secondsToMilliseconds(displayDataIntervalInSeconds)
    || lastDisplayDataTime == 0;

    if (displayDataIsDue)
    {
      lastDisplayDataTime = millis();
  
      lcd.setCursor(0, 1);
      
      lcd.print("             ");
      lcd.setCursor(0, 1);
      lcd.print("       ");
      lcd.print(analogSensor.readCalibrated());
      lcd.print("%");
    }
}

void setup() {
  Serial.begin(115200);
  
  // Set the interval at which sensor readings and calibration are processed
  analogSensor.setInterval(1000); // Set to 5000 milliseconds (5 seconds)
  
  // Set initial calibration values
  // analogSensor.setCalibrationLow(100);  // Example low calibration value
  // analogSensor.setCalibrationHigh(900); // Example high calibration value
  
  // Optionally load calibration from EEPROM if it's already set previously
  analogSensor.loadCalibration();

  analogSensor.setCallback(handleSensorData); // Assign the callback function

  button1.begin();
  button2.begin();

  button1.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateLow);
  button2.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateHigh);


  lcd.init();
  lcd.backlight();
  lcd.print("Starting...");

  Serial.println("Sensor initialized and calibrated. Reading values...");

  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Soil Moisture");
}

void loop() {
  button1.read();
  button2.read();

  // Handle sensor via loop
  analogSensor.loop();

  delay(1000);
}
