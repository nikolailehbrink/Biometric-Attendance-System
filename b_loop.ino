void loop() {
  if (mainloopOutput == true || currentMillis - startMillis <= 10000) {
    lcdPrinter("Finger auflegen");
    mainloopOutput = false;
  }

  //first detect finger
  fingerprintDetection();
  //then detect keypad inputs
  keypadDetector();
}
