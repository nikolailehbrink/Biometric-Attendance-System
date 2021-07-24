void fingerprintDetection() {
  int fingerID = getFingerprintID();

  if (fingerID == -3) {
    startMillis = millis();
  } else if (fingerID > 0 && fingerID <= 127 ) {
    lcd.clear();
    if (fingerID == 1) {
      //When Admin-Finger is pressed on sensor
      lcd.print("Hi Goldfinger!");
    } else {
      lcd.print("Hi, deine ID:");
      lcd.print(fingerID);
    }
    delay(2500);
    lcd.clear();
    mainloopOutput = true;
  } else if (fingerID == -2) {
    //When no finger is currently detected
    currentMillis = millis();
    lcd.setCursor(0, 1);
    lcd.print("Warte...");
    delay(500);
    if (currentMillis - startMillis >= period) {
      lcdPrinter("Finger nicht", "erkannt!");
      startMillis = currentMillis;
      delay(2500);
      lcd.clear();
      mainloopOutput = true;
    }
  }
  return;
}
