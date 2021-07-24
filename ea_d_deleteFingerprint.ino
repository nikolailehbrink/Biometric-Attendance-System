void deleteFingerprint() {
  lcdPrinter("Loesche ID:");
  lcd.setCursor(0, 1);
  getAllStoredModelIds();
  int idToBeDeleted = getNumber();
  if (abgebrochen == true) {
    mainloopOutput = true;
    globalState = 0;
    abgebrochen = false;
    return;
  }
  if (idToBeDeleted == 1) {
    lcdPrinter("Admin nicht", "loeschbar!");
    delay(2000);
    deleteFingerprint();
  } else if (compareStoredToInputId(idToBeDeleted)) {
    finger.deleteModel(idToBeDeleted);
    lcdPrinter("Fingerabdruck", "geloescht!");
    delay(2000);
    mainloopOutput = true;
    globalState = 0;
  } else {
    lcdPrinter("ID ungueltig!");
    delay(2000);
    deleteFingerprint();
  }
}

int getNumber() {
  int num = 0;
  char key = customKeypad.getKey();
  while (key != '*') {
    switch (key) {
      case NO_KEY:
        break;

      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        lcd.print(key);
        num = num * 10 + (key - '0');
        break;

      case 'C':
        num = 0;
        lcd.clear();
        lcdPrinter("Loesche ID:");
        lcd.setCursor(0, 1);
        break;

      case '#':
        abgebrochen = true;
        return;
    }
    key = customKeypad.getKey();
  }

  return num;
}








//    char fingerprintIdKey = customKeypad.waitForKey();
//
//    if (fingerprintIdKey) {
//      //check if a number is pressed
//      if (isDigit(fingerprintIdKey)) {
//        lcd.print(fingerprintIdKey);
//        addToIdBuffer(passwordKey);
//      }
//      // oder Code überprüfen, falls Raute gedrückt wurde
//      else if (fingerprintIdKey == '*') {
//        checkFingerprintId();
//      }
//      else if (fingerprintIdKey == '#') {
//        mainloopOutput = true;
//        globalState = 0;
//      }
//    }
//  }
//}





//
//void addToIdBuffer(char inkey) {
//  //Serial.print(inkey);
//  //Serial.print(" > ");
//  // Von links nach rechts Zeichen um eins weiterkopieren = ältestes Zeichen vergessen
//  for (int i = 1; i < 3; i++) {
//    idBuffer[i - 1] = idBuffer[i];
//  }
//  // in ganz rechter Stelle die letzte Ziffer speichern
//  idBuffer[] = inkey;
//  //Serial.println(keyBuffer);
//}
