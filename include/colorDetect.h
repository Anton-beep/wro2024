// 0 - White
// 1 - Black
// 2 - Red
// 3 - Green
// 4 - Blue
// 5 - Yellow

tCDValues CDSensor4, CDSensor3, CDSensor1, CDSensor2;

void colorDetectInit() {
    CDSensor1.nDeviceIndex = S1;
    CDSensor1.minAmbient = 2480;
    CDSensor1.maxAmbient = 1640;

    CDSensor2.nDeviceIndex = S2;
    CDSensor2.minAmbient = 2504;
    CDSensor2.maxAmbient = 1740;

    CDSensor3.nDeviceIndex = S3;
    CDSensor3.minRed = 0;
    CDSensor3.maxRed = 255;
    CDSensor3.minGreen = 0;
    CDSensor3.maxGreen = 255;
    CDSensor3.minBlue = 0;
    CDSensor3.maxBlue = 255;


    CDSensor4.nDeviceIndex = S4;
    CDSensor4.minRed = 0;
    CDSensor4.maxRed = 255;
    CDSensor4.minGreen = 0;
    CDSensor4.maxGreen = 255;
    CDSensor4.minBlue = 0;
    CDSensor4.maxBlue = 255;
}

void getCDValues(tCDValues *CDSensor) {
    if (SensorType[CDSensor->nDeviceIndex] == 93) {
        // this is ev3 color sensor
        getColorRawRGB(CDSensor->nDeviceIndex, CDSensor->rawRed, CDSensor->rawGreen,
                   CDSensor->rawBlue);
    }
    else {
        // this is nxt ambient light sensor
        CDSensor->ambient = sensorRaw[CDSensor->nDeviceIndex];
    }

    #ifdef CALIBRATION
    if (SensorType[CDSensor->nDeviceIndex] == 93) {
        CDSensor->normRed = 1;
        CDSensor->normGreen = 1;
        CDSensor->normBlue = 1;

        if ((CDSensor->maxRed - CDSensor->minRed) != 0){
            CDSensor->normRed = (float)(CDSensor->rawRed - CDSensor->minRed) /
                                (CDSensor->maxRed - CDSensor->minRed) * 255;
        }

        if ((CDSensor->maxGreen - CDSensor->minGreen) != 0){
            CDSensor->normGreen = (float)(CDSensor->rawGreen - CDSensor->minGreen) /
                                (CDSensor->maxGreen - CDSensor->minGreen) * 255;
        }

        if ((CDSensor->maxBlue - CDSensor->minBlue) != 0){
        CDSensor->normBlue = (float)(CDSensor->rawBlue - CDSensor->minBlue) /
                            (CDSensor->maxBlue - CDSensor->minBlue) * 255;
        }
    }
    // calibration mode for nxt light sensor is need to be added
    #endif
    
    #ifndef CALIBRATION
    if (SensorType[CDSensor->nDeviceIndex] == 93) {
        CDSensor->normRed = (float)(CDSensor->rawRed - CDSensor->minRed) /
                            (CDSensor->maxRed - CDSensor->minRed) * 255;
        CDSensor->normGreen = (float)(CDSensor->rawGreen - CDSensor->minGreen) /
                            (CDSensor->maxGreen - CDSensor->minGreen) * 255;
        CDSensor->normBlue = (float)(CDSensor->rawBlue - CDSensor->minBlue) /
                            (CDSensor->maxBlue - CDSensor->minBlue) * 255;
    } else {
        CDSensor->normAmbient = (float)(CDSensor->ambient - CDSensor->minAmbient) /
                            (CDSensor->maxAmbient - CDSensor->minAmbient) * 100;
    }
    #endif

    RGBtoHSV(CDSensor->normRed, CDSensor->normGreen, CDSensor->normBlue,
             &(CDSensor->hue), &(CDSensor->sat), &(CDSensor->val));

    if (SensorType[CDSensor->nDeviceIndex] != 93) {
        return;
    }
    #ifdef DEBUG_HSV
        displayCenteredTextLine(2, "hue: %f", CDSensor->hue);
        displayCenteredTextLine(4, "sat: %f", CDSensor->sat);
        displayCenteredTextLine(6, "val: %f", CDSensor->val);
    #endif

    // 0 - White
    // 1 - Black
    // 2 - Red
    // 3 - Green
    // 4 - Blue
    // 5 - Yellow


    // [hue_min; hue_max)


    if (SensorType[CDSensor->nDeviceIndex] != 40) {
        if (CDSensor->val <= 30) {
            CDSensor->color = 1;
        } else if (CDSensor->sat <= 0.15 && CDSensor->val >= 150) {
            CDSensor->color = 0;
        }
        else {
            if (CDSensor->hue < 15 || CDSensor->hue >= 300) {
                CDSensor->color = 2;
            } else if (CDSensor->hue >= 15 && CDSensor->hue < 90) {
                CDSensor->color = 5;
            } else if (CDSensor->hue >= 90 && CDSensor->hue < 170) {
                CDSensor->color = 3;
            } else {
                CDSensor->color = 4;
            }
        }
    }
    else {
        if (CDSensor->normRed + CDSensor->normGreen + CDSensor->normBlue < 10) {
            CDSensor->color = -1;
        }
        else if (CDSensor->sat <= 0.04) {
            if (CDSensor->val < 10) {
                CDSensor->color = 1;
            } else {
                CDSensor->color = 0;
            }
        }
        else {
            if (CDSensor->hue < 20 || CDSensor->hue >= 300) {
                CDSensor->color = 2;
            } else if (CDSensor->hue >= 20 && CDSensor->hue < 70) {
                CDSensor->color = 5;
            } else if (CDSensor->hue >= 70 && CDSensor->hue <= 185) {
                CDSensor->color = 3;
            } else {
                CDSensor->color = 4;
            }
        }
    }
}

void displayValues(tCDValues *CDSensor) {
    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);
    setMotorBrakeMode(motorC, motorCoast);
    setMotorBrakeMode(motorD, motorCoast);
    setSoundVolume(5);

    getCDValues(CDSensor);
    int minAmbient = CDSensor->ambient;
    int maxAmbient = CDSensor->ambient;
    while (1){
        getCDValues(CDSensor);
        if (SensorType[CDSensor->nDeviceIndex] != 93) {
            // this is nxt light sensor
            displayCenteredTextLine(1, "Ambient: %d", CDSensor->ambient);
            displayCenteredTextLine(3, "Norm Ambient: %f", CDSensor->normAmbient);
            if (CDSensor->ambient < minAmbient) {
                minAmbient = CDSensor->ambient;
            }
            if (CDSensor->ambient > maxAmbient) {
                maxAmbient = CDSensor->ambient;
            }
            displayCenteredTextLine(5, "Min Ambient: %d", minAmbient);
            displayCenteredTextLine(7, "Max Ambient: %d", maxAmbient);
        } else {
            displayCenteredTextLine(1, "RGB_raw: %d %d %d", CDSensor->rawRed,
                                    CDSensor->rawGreen, CDSensor->rawBlue);
            displayCenteredTextLine(3, "RGB_norm: %d %d %d", CDSensor->normRed,
                                    CDSensor->normGreen, CDSensor->normBlue);
            displayCenteredTextLine(5, "HSV: %f %f %f", CDSensor->hue,
                                    CDSensor->sat, CDSensor->val);
            displayBigStringAt(125, 20, "%d", CDSensor->color);
            clearSounds();
            if (CDSensor->color == 1) {
                playSoundFile("Right");
            } else if (CDSensor->color == 2) {
                playSoundFile("Yellow");
            } else if (CDSensor->color == 3) {
                playSoundFile("Green");
            } else if (CDSensor->color == 4) {
                playSoundFile("Blue");
            } else if (CDSensor->color == 5) {
                playSoundFile("Black");
            } else if (CDSensor->color == 6) {
                playSoundFile("White");
            } else {
                playSoundFile("Uh-oh");
            }
        }
        sleep(400);
        eraseDisplay();
    }
}
