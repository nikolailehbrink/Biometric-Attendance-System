void enrollNewUser() {
  lcd.clear();
  lcdPrinter("Adminfinger", "auflegen!");
  while (globalState == 2) {
    char customKey_1 = customKeypad.getKey();
    switch (customKey_1) {
      case 0:
        b_ereignis_eintragen();
        b_automat_updaten();
        break;
      case '#':
        mainloopOutput = true;
        b_ereignis = E_INITIAL;
        b_zustand = 0;
        globalState = 0;
    }
  }
}

void b_ereignis_eintragen() {
  ////Serial.println("B_ereginis eintragen()");
  if (b_ereignis == E_ADMIN_VALID || b_ereignis == E_ADMIN_INVALID) {
    if (b_ereignis == E_ADMIN_INVALID && b_zustand == 0) {
      b_ereignis = E_INITIAL;
    }
    return;
  }
  if (fingerPressedOnScanner()) {
    b_ereignis = E_FINGER_ON_SCANNER;
    return;
  }
  b_ereignis = E_INITIAL;
}


void b_automat_updaten() {
  ////Serial.println("automat_updaten()");
  switch (b_ereignis) {
    case E_INITIAL:
      ////Serial.println("Automat updaten -> Case 0");
      break;
    case E_FINGER_ON_SCANNER:
      ////Serial.println("Automat updaten -> Case 1");
      if (b_zustand == Z_WAIT_FOR_ADMIN_FINGER) {
        ////Serial.println("b_z(1)");
        b_z(Z_CHECK_ADMIN_FINGER);
      } else {
        ////Serial.println("b_z(0)");
        b_z(Z_WAIT_FOR_ADMIN_FINGER);
      }
      break;
    case E_ADMIN_INVALID:
      ////Serial.println("Automat updaten -> Case 2");

      if (b_zustand == Z_CHECK_ADMIN_FINGER) {
        ////Serial.println("b_z(2)");
        b_z(Z_ADMIN_CHECK_FAILED);
      } else {
        ////Serial.println("b_z(0)");
        b_z(Z_WAIT_FOR_ADMIN_FINGER);
      }
      break;
    case E_ADMIN_VALID: ////Serial.println("Automat updaten -> Case 3");
      if (b_zustand == Z_CHECK_ADMIN_FINGER) {
        ////Serial.println("b_z(3)");
        b_z(Z_ADMIN_CHECK_SUCCEEDED);
      } else {
        ////Serial.println("b_z(0)");
        b_z(Z_WAIT_FOR_ADMIN_FINGER);
      }
      break;
    case 4: ////Serial.println("Automat updaten -> Case 4");

      if (b_zustand == Z_ADMIN_CHECK_SUCCEEDED) {
        ////Serial.println("b_z(4)");
        //TODO: DEFINE 4
        b_z(4);
      } else {
        ////Serial.println("b_z(0)");
        b_z(Z_WAIT_FOR_ADMIN_FINGER);
      }
  }
}




void b_z(int neuerZustand) {
  switch (neuerZustand) {
    case Z_WAIT_FOR_ADMIN_FINGER:
      b_zustand = Z_WAIT_FOR_ADMIN_FINGER;
      break;
    case Z_CHECK_ADMIN_FINGER:
      b_zustand = Z_CHECK_ADMIN_FINGER;
      lcd.print("Pruefe Finger..");
      getAdminFingerprint();
      break;
    case Z_ADMIN_CHECK_FAILED:
      b_zustand = Z_ADMIN_CHECK_FAILED;
      lcdPrinter("Nicht erfolgreich!", "Versuche erneut.");
      delay(500);
      break;
    case Z_ADMIN_CHECK_SUCCEEDED:
      b_zustand = Z_ADMIN_CHECK_SUCCEEDED;
      lcd.clear();
      lcd.print("Erfolgreich!");
      lcd.setCursor(0, 1);
      delay(2000);
      lcdPrinter("Neuen Finger", "auflegen!");
      delay(500);
      id = getNextAvailableModelId();
      while (getFingerprintEnroll() != FINGERPRINT_OK);
      globalState = 0;
      mainloopOutput = true;
      break;
  }
}

void getAdminFingerprint() {

  adminFingerID = getFingerprintID();
  if (adminFingerID == 1) {
    b_ereignis = E_ADMIN_VALID;
  } else {
    b_ereignis = E_ADMIN_INVALID;
  }
}
