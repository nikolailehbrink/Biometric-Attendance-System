void keypadDetector() {
  char customKey = customKeypad.getKey();

  switch (customKey) {
    case 'A':
      globalState = 1;
      newAdminFingerprint();
      break;
    case 'B':
      globalState = 2;
      enrollNewUser();
      break;
    case 'C':
      globalState = 3;
      newAdminPassword();
      break;
    case 'D':
      globalState = 4;
      deleteFingerprint();
      break;
    default: break;
  }
}

//Handles lcd outputs which go outside of viewport
void lcdScroller(String messageToDisplay) {
  lcd.clear();
  lcd.print(messageToDisplay);
  //wartet erstmal damit Nutzer den Anfang der Message lesen kann
  lcd.home();
  delay(1500);
  //Scrollt nur soweit bis nötig
  for (int positionCounter = 0; positionCounter < messageToDisplay.length() - 16; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(250);
  }
  //Kommt zum Anfang
  delay(750);
  lcd.home();
}


void lcdPrinter(String rowOne, String rowTwo) {
  lcd.clear();
  lcd.print(rowOne);
  lcd.setCursor(0, 1);
  lcd.print(rowTwo);
  if (rowOne.length() > 16 || rowTwo.length() > 16) {
    delay(1500);
    for (byte positionCounter = 0; positionCounter < longerMessage(rowOne, rowTwo) - 16; positionCounter++) {
      lcd.scrollDisplayLeft();
      delay(300);
    }
    delay(1000);
    lcd.home();
    delay(500);
  }
}

void lcdPrinter(String rowOne) {
  lcd.clear();
  lcd.print(rowOne);
  lcd.home();
  if (rowOne.length() > 16) {
    delay(1500);
    for (byte positionCounter = 0; positionCounter < rowOne.length() - 16; positionCounter++) {
      lcd.scrollDisplayLeft();
      delay(250);
    }
    delay(750);
    lcd.home();
  }
}
byte longerMessage(String rowOne, String rowTwo) {
  if (rowOne.length() >= rowTwo.length()) {
    return rowOne.length();
  } else {
    return rowTwo.length();
  }
}


boolean fingerPressedOnScanner() {
  int8_t p = finger.getImage();
  if (p == FINGERPRINT_OK) {
    return true;
  }
  else {
    return false;
  }
}

uint8_t getNextAvailableModelId() {
  for (int i = 2; i <= 127; i++) {
    if (finger.loadModel(i) != FINGERPRINT_OK) {
      //get the next available id inside fingerprint sensor
      id = i;
      return id;
    }
  }
  return -1;
}

boolean compareStoredToInputId(int idToBeDeleted) {
  //Serial.print("Alle gespeicherten IDs: ");
  for (int i = 1; i <= 127; i++) {
    if (finger.loadModel(i) == FINGERPRINT_OK && i == idToBeDeleted) {
      return true;
    }
  }
  return false;
}

void getAllStoredModelIds() {
  Serial.print("Alle gespeicherten IDs: ");
  for (int i = 1; i <= 127; i++) {
    if (finger.loadModel(i) == FINGERPRINT_OK) {
      //get the next available id inside fingerprint sensor
      Serial.print(i);
      Serial.print(", ");
    }
  }
}

uint8_t getFingerprintEnroll() {
  int p = -1;

  ////Serial.print("Waiting for valid finger to enroll as #"); ////Serial.println(id);
  while (p != FINGERPRINT_OK) {
    //    if (customKeypad.getKey() == '#') {
    //      return 4;
    //    }
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        //Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        //Serial.println(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        ////Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        ////Serial.println("Imaging error");
        break;
      default:
        ////Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      ////Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      ////Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      ////Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      ////Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      ////Serial.println("Could not find fingerprint features");
      return p;
    default:
      ////Serial.println("Unknown error");
      return p;
  }
  lcd.clear();
  ////Serial.println("Remove finger");
  lcd.print("Finger anheben");
  delay(2000);

  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    //    if (customKeypad.getKey() == '#') {
    //      return 4;
    //    }
    p = finger.getImage();
  }
  ////Serial.print("ID "); ////Serial.println(id);
  p = -1;
  ////Serial.println("Place same finger again");
  lcd.clear();
  lcdPrinter("Finger nochmal", "auflegen!");
  ////Serial.println("Hallo");
  while (p != FINGERPRINT_OK) {
    //    if (customKeypad.getKey() == '#') {
    //      return 4;
    //    }
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        ////Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        ////Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        ////Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        ////Serial.println("Imaging error");
        break;
      default:
        ////Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      ////Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      ////Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      ////Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      ////Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      ////Serial.println("Could not find fingerprint features");
      return p;
    default:
      ////Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  ////Serial.print("Creating model for #");  ////Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    ////Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    ////Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    ////Serial.println("Fingerprints did not match");
    lcd.clear();
    lcdPrinter("Abdruecke", "ungleich!");
    delay(1000);
    return p;
  } else {
    ////Serial.println("Unknown error");
    return p;
  }

  ////Serial.print("ID "); ////Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    ////Serial.println("Stored!");
    lcd.clear();

    lcdPrinter("Abdruck", "gespeichert!");
    delay(1000);
    return p;
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    ////Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    ////Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    ////Serial.println("Error writing to flash");
    return p;
  } else {
    ////Serial.println("Unknown error");
    return p;
  }
}

int8_t getFingerprintID() {
  int8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      ////Serial.println("Finger detected - Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      ////Serial.println("No finger detected");
      return -3;
    case FINGERPRINT_PACKETRECIEVEERR:
      ////Serial.println("Communication error");
      return -1;
    case FINGERPRINT_IMAGEFAIL:
      ////Serial.println("Imaging error");
      return -1;
    default:
      ////Serial.println("Unknown error");
      return -1;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      ////Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      ////Serial.println("Image too messy");
      return -1;
    case FINGERPRINT_PACKETRECIEVEERR:
      ////Serial.println("Communication error");
      return -1;
    case FINGERPRINT_FEATUREFAIL:
      ////Serial.println("Could not find fingerprint features");
      return -1;
    case FINGERPRINT_INVALIDIMAGE:
      ////Serial.println("Could not find fingerprint features");
      return -1;
    default:
      ////Serial.println("Unknown error");
      return -1;
  }

  // Compares fingerprint with own database
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    ////Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    ////Serial.println("Communication error");
    return -1;
  } else if (p == FINGERPRINT_NOTFOUND) {
    ////Serial.println("Did not find a match");
    return -2;
  } else {
    ////Serial.println("Unknown error");
    return -1;
  }

  // found a match!
  ////Serial.print("Found ID #"); ////Serial.print(finger.fingerID);
  ////Serial.print(" with confidence of "); ////Serial.println(finger.confidence);

  return finger.fingerID;
}
