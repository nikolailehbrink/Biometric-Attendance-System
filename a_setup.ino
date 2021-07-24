void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  // set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
    //Serial.println("Found fingerprint sensor!");
  } else {
    //Serial.println("Did not find fingerprint sensor :(");
  }

  //How many fingerprints are stored inside sensor
  finger.getTemplateCount();
  if (finger.templateCount == 0) {
    //Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    //Serial.println("Waiting for valid finger...");
    //Serial.print("Sensor contains "); //Serial.print(finger.templateCount); //Serial.println(" templates");
  }
}
