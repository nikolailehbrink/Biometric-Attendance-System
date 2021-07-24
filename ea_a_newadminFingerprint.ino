void newAdminFingerprint() {
  lcdPrinter("Neuer Admin!", "Pin-Code: ");

  while (globalState == 1) {
    char passwordKey = customKeypad.waitForKey();

    if (passwordKey) {
      //check if a number is pressed
      if (isDigit(passwordKey)) {
        lcd.print('*');
        addToKeyBuffer(passwordKey);
      }
      // oder Code überprüfen, falls Raute gedrückt wurde
      else if (passwordKey == '*') {
        checkKey();
      }
      else if (passwordKey == '#') {
        mainloopOutput = true;
        globalState = 0;
      }
    }
  }
}

void addToKeyBuffer(char inkey) {
  //Serial.print(inkey);
  //Serial.print(" > ");
  // Von links nach rechts Zeichen um eins weiterkopieren = ältestes Zeichen vergessen
  for (int i = 1; i < PINLENGTH; i++) {
    keyBuffer[i - 1] = keyBuffer[i];
  }
  // in ganz rechter Stelle die letzte Ziffer speichern
  keyBuffer[PINLENGTH - 1] = inkey;
  //Serial.println(keyBuffer);
}

void checkKey() {
  // Eingabe mit festgelegtem Pincode vergleichen
  //strcmp = String compare Funktion
  if (strcmp(keyBuffer, pinCode) == 0) {
    // Aktion für richtigen Pin ausführen
    pinCorrect();
    return;
  }
  else {
    // Aktion für falschen Pin ausführen
    pinWrong();
  }
  // Nach Überprüfung Eingabe leeren
  for (int i = 0; i < PINLENGTH; i++) {
    keyBuffer[i] = '-';
  }
}

// Aktion für korrekten Pincode
void pinCorrect() {
  lcd.clear();
  delay(100);
  lcd.print("Richtig!");
  delay(500);
  lcdPrinter("Neuen Finger", "auflegen!");
  delay(2000);
  id = 1;
  //Serial.print(FINGERPRINT_OK);
  while ((getFingerprintEnroll() != FINGERPRINT_OK));
  globalState = 0;
  mainloopOutput = true;
}

// Aktion für falschen Pincode
void pinWrong() {
  if (pinCodeWrongCounter >= 2) {
    lcdPrinter("Falscher Pin! ", "Zu oft falsch.");
    delay(2500);
    globalState = 0;
    mainloopOutput = true;
    pinCodeWrongCounter = 0;
    return;
  }
  pinCodeWrongCounter++;
  lcdPrinter("Falscher Pin!", "Versuche erneut!");
  delay(1000);
  lcdPrinter("Neuer Admin!", "Pin-Code: ");
}
