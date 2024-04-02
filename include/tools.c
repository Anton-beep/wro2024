void updateMotorSpeed(int *powers){
    motor[motorA] = powers[0];
    motor[motorB] = powers[1];
    motor[motorC] = powers[2];
    motor[motorD] = powers[3];
}


void manualMotors() {
    sleep(200);
    flushButtonMessages();

    int curentMotorPower[4] = {0, 0, 0, 0};
    int zeroMotorPower[4] = {0, 0, 0, 0};
    int selectedMotor = 0;

    while (true) {
        if (getButtonPress(buttonUp)) {
            curentMotorPower[selectedMotor] = min2(100, curentMotorPower[selectedMotor] + 1);
        } else if (getButtonPress(buttonDown)) {
            curentMotorPower[selectedMotor] = max2(-100, curentMotorPower[selectedMotor] - 1);
        } else if (getButtonPress(buttonLeft)) {
            selectedMotor = (selectedMotor - 1) % 4;
        } else if (getButtonPress(buttonRight)) {
            selectedMotor = (selectedMotor + 1) % 4;
        }

        if (getButtonPress(buttonEnter)) {
            updateMotorSpeed(curentMotorPower);
        } else {
            updateMotorSpeed(zeroMotorPower);
        }

        eraseDisplay();
        displayCenteredTextLine(1, "selected motor %d", selectedMotor);
        displayCenteredTextLine(2, "motor A %d", curentMotorPower[0]);
        displayCenteredTextLine(3, "motor B %d", curentMotorPower[1]);
        displayCenteredTextLine(4, "motor C %d", curentMotorPower[2]);
        displayCenteredTextLine(5, "motor D %d", curentMotorPower[3]);

        sleep(150);
        flushButtonMessages();
    }
}

void topSpeedAndEncoderTest(int mot) {
    for (int sp = 0; sp < 100; sp++) {
        motor[mot] = sp;
        sleep(50);
    }
    sleep(500);
    float startEnc = nMotorEncoder[mot];
    float startTime = nPgmTime;
    sleep(10000);
    float endEnc = nMotorEncoder[mot];
    float endTime = nPgmTime;
    motor[mot] = 0;

    eraseDisplay();
    displayCenteredTextLine(1, "Enc: %f deg", endEnc - startEnc);
    displayCenteredTextLine(3, "Time: %f mS", endTime - startTime);
    displayCenteredTextLine(5, "Speed: %f deg/s", (endEnc - startEnc) / (endTime - startTime) * 1000);
    displayCenteredTextLine(7, "Voltage: %f", getBatteryVoltage());
    flushButtonMessages();
	waitForButtonPress();
}