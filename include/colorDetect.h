// 0 - White
// 1 - Black
// 2 - Red
// 3 - Green
// 4 - Blue
// 5 - Yellow

tCDValues CDSensor4, CDSensor3, CDSensor1, CDSensor2;

void colorDetectInit() {
    CDSensor1.nDeviceIndex = S1;
    CDSensor1.minRed = 27;
    CDSensor1.maxRed = 321;
    CDSensor1.minGreen = 32;
    CDSensor1.maxGreen = 320;
    CDSensor1.minBlue = 24;
    CDSensor1.maxBlue = 283;

    CDSensor2.nDeviceIndex = S2;
    CDSensor2.minRed = 27;
    CDSensor2.maxRed = 309;
    CDSensor2.minGreen = 37;
    CDSensor2.maxGreen = 340;
    CDSensor2.minBlue = 17;
    CDSensor2.maxBlue = 185;

    CDSensor3.nDeviceIndex = S3;
    CDSensor3.minRed = 12;
    CDSensor3.maxRed = 290;
    CDSensor3.minGreen = 10;
    CDSensor3.maxGreen = 224;
    CDSensor3.minBlue = 5;
    CDSensor3.maxBlue = 129;


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

    int minRed = CDSensor->rawRed;
    int maxRed = CDSensor->rawRed;
    int minGreen = CDSensor->rawGreen;
    int maxGreen = CDSensor->rawGreen;
    int minBlue = CDSensor->rawBlue;
    int maxBlue = CDSensor->rawBlue;
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
            if (CDSensor->rawRed < minRed) {
                minRed = CDSensor->rawRed;
            }
            if (CDSensor->rawRed > maxRed) {
                maxRed = CDSensor->rawRed;
            }
            if (CDSensor->rawGreen < minGreen) {
                minGreen = CDSensor->rawGreen;
            }
            if (CDSensor->rawGreen > maxGreen) {
                maxGreen = CDSensor->rawGreen;
            }
            if (CDSensor->rawBlue < minBlue) {
                minBlue = CDSensor->rawBlue;
            }
            if (CDSensor->rawBlue > maxBlue) {
                maxBlue = CDSensor->rawBlue;
            }
            displayCenteredTextLine(7, "Min RGB: %d %d %d", minRed, minGreen, minBlue);
            displayCenteredTextLine(9, "Max RGB: %d %d %d", maxRed, maxGreen, maxBlue);
            displayCenteredTextLine(11, "SumNorm: %d", CDSensor->normRed + CDSensor->normGreen + CDSensor->normBlue);
            // clearSounds();
            // if (CDSensor->color == 1) {
            //     playSoundFile("Right");
            // } else if (CDSensor->color == 2) {
            //     playSoundFile("Yellow");
            // } else if (CDSensor->color == 3) {
            //     playSoundFile("Green");
            // } else if (CDSensor->color == 4) {
            //     playSoundFile("Blue");
            // } else if (CDSensor->color == 5) {
            //     playSoundFile("Black");
            // } else if (CDSensor->color == 6) {
            //     playSoundFile("White");
            // } else {
            //     playSoundFile("Uh-oh");
            // }
        }
        sleep(400);
        eraseDisplay();
    }
}

void myCalibration() {
    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);
    setMotorBrakeMode(motorC, motorCoast);
    setMotorBrakeMode(motorD, motorCoast);

    getCDValues(&CDSensor1);
    getCDValues(&CDSensor2);
    int minAmbient1 = CDSensor1.ambient;
    int maxAmbient1 = CDSensor1.ambient;
    int minAmbient2 = CDSensor2.ambient;
    int maxAmbient2 = CDSensor2.ambient;

    while (true) {
        getCDValues(&CDSensor1);
        getCDValues(&CDSensor2);
        if (CDSensor1.ambient < minAmbient1) {
            minAmbient1 = CDSensor1.ambient;
        }
        if (CDSensor1.ambient > maxAmbient1) {
            maxAmbient1 = CDSensor1.ambient;
        }
        if (CDSensor2.ambient < minAmbient2) {
            minAmbient2 = CDSensor2.ambient;
        }
        if (CDSensor2.ambient > maxAmbient2) {
            maxAmbient2 = CDSensor2.ambient;
        }
        eraseDisplay();
        displayCenteredTextLine(1, "MaxAmbient1: %d", maxAmbient1);
        displayCenteredTextLine(3, "MinAmbient1: %d", minAmbient1);
        displayCenteredTextLine(5, "MaxAmbient2: %d", maxAmbient2);
        displayCenteredTextLine(7, "MinAmbient2: %d", minAmbient2);
        displayCenteredTextLine(9, "NormAmbient1: %d", CDSensor1.normAmbient);
        displayCenteredTextLine(11, "NormAmbient2: %d", CDSensor2.normAmbient);
    }
}
