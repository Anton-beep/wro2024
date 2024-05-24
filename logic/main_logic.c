#include "logic_vars.c"
#include "tools.c"

void startFromLower() {
    waitInitManip();
    setDegManipD(nMotorEncoder[motorD] - constsManipD.prepareToTakeFromLine, -90, 0);
    waitForManipD();
    setPositionManipC(constsManipC.takeFromLineCube, 90, 0);
    waitForManipC();
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 20, 0);

    arcEnc(-36, 0, -100, -35, 377);
    arcEnc(0, 36, 100, 35, 377);
    setMotorB(45);
    sleep(250);
    stopMove(100, true);

    arcEnc(25, -24, 60, 30, 300);
    setMotorA(45);
    setMotorB(-30);
    getCDValues(&CDSensor1);
    while (true)
    {
        if (CDSensor1.normRed > 200 && CDSensor1.normGreen < 100 && CDSensor1.normBlue < 100)
        {
            break;
        }
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    

    arcEnc(25, -24, 40, 16, 234);
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    // робот слегка пнул кубик
}

void startFromUpper() {
    waitInitManip();
    setDegManipD(nMotorEncoder[motorD] - constsManipD.prepareToTakeFromLine, -70, 0);
    waitForManipD();
    setPositionManipC(constsManipC.takeFromLineCube, 90, 0);
    waitForManipC();
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 20, 0);

    arcEnc(-26, 0, -70, -26, 377);
    arcEnc(0, 26, 70, 26, 377);
    setMotorB(45);
    sleep(250);
    stopMove(100, true);

    arcEnc(25, -24, 60, 30, 300);
    setMotorA(45);
    setMotorB(-30);
    getCDValues(&CDSensor1);
    while (true)
    {
        if (CDSensor1.normRed > 200 && CDSensor1.normGreen < 100 && CDSensor1.normBlue < 100)
        {
            break;
        }
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    

    arcEnc(25, -24, 40, 16, 215);
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    // робот слегка пнул кубик
}

void landCube() {
    setPowerAdjustBatteryManipD(8, 8);
    int lastEncoderD = nMotorEncoder[motorD];
    sleep(100);
    setPowerAdjustBatteryManipD(5, 8);
    while (nMotorEncoder[motorD] - lastEncoderD > 5)
    {
        lastEncoderD = nMotorEncoder[motorD];
        sleep(90);
    }
    setPowerAdjustBatteryManipD(-20, 8);
    sleep(200);
    setPowerAdjustBatteryManipD(0, 8);
}

void takeRedAndYellowCubes()
{
    arcEnc(24, -23, 24, 12, 139);
    arcEnc(-17, 17, 17, 17, 7);
    stopMove(300, true);
    setTimeManipC(400, 25, 50);
    waitForManipC();
    setPositionManipD(constsManipD.put1Cube, 80, 0);
    waitForManipD();
    sleep(100);
    arcEnc(24, -23, 20, 14, 120);
    arcEnc(-19, 19, 19, 19, 8);
    stopMove(1, true);
    landCube();
    setDegManipC(nMotorEncoder[motorC] - constsManipC.goOverTwoCubesOnLine, -35, 0);
    setPositionManipD(constsManipD.hideWall, 70, 0);
    waitForManipD();
    setPositionManipD(constsManipD.goOverTwoCubes, 70, 0);
    waitForManipD();
    sleep(300);

    setPositionManipC(constsManipC.takeFromLineCube, 70, 0);
    arcEnc(24, -23, 40, 24, 140);
    stopMove(100, true);
    setPositionManipD(constsManipD.takeCube, 80, 0);
    waitForManipD();
    arcEnc(24, -23, 15, 14, 188);

    arcEnc(-19, 19, 19, 19, 9);
    stopMove(300, true);
    setTimeManipC(500, 20, 50);
    waitForManipC();
    setPositionManipD(constsManipD.put1Cube, 80, 0);
    waitForManipD();
    sleep(100);
    arcEnc(24, -23, 14, 14, 130);
    arcEnc(-19, 19, 19, 19, 9);
    stopMove(1, true);
    landCube();
    setDegManipC(nMotorEncoder[motorC] - constsManipC.goOverTwoCubesOnLine, -35, 0);
    waitForManipC();
    sleep(300);
    setPositionManipD(constsManipD.takeCube, 50, 0);
    waitForManipD();
    sleep(300);
    setTimeManipC(500, 20, 80);
    waitForManipC();
    setPositionManipD(constsManipD.carryCubes, 70, 0);
}

void put2CubesAndTakeFromStorage() {
    setTimeManipD(400, 10, 0);
    waitForManipD();
    setDegManipC(nMotorEncoder[motorC] - constsManipC.almostClose, -40, 0);
    waitForManipC();
    sleep(300);
    arcEnc(-18, 18, 18, 14, 15);
    stopMove(300);
    setPositionManipC(constsManipC.openToTakeFromStorage, 100, 0);
    waitForManipC();
    setPositionManipD(constsManipD.goOverTwoCubes, 100, 0);
    waitForManipD();
    sleep(300);

    arcEnc(-30, 30, 50, 12, 230);
    stopMove(300);

    // захват башни
    setDegManipC(constsManipC.takeFromStorage - nMotorEncoder[motorC], 40, 0);
    waitForManipC();
    sleep(300);
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 30, 0);
    waitForManipD();
    sleep(300);
    arcEnc(14, -14, 10, 9, 100);
    stopMove(1);
    setTimeManipC(300, 40, 70);
    waitForManipC();
    sleep(3000);
    setDegManipD(nMotorEncoder[motorD] - constsManipD.carryCubes, -60, 0);
    waitForManipD();
    sleep(3000);
}

void lowerToUpper()
{
    arcEnc(0, -50, -90, -50, 400);
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    gBoost = 15;
    arcEnc(50, -50, 120, 65, 630);
    gBoost = 10;
    arcEnc(65, -65, 50, 35, 450);

    setMotorA(35);
    setMotorB(-35);

    getCDValues(&CDSensor1);
    while (CDSensor1.normRed < 190)
    {
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(0, -50, -90, -50, 540);

    setMotorBrakeMode(motorA, motorBrake);
    motor[motorA] = 0;

    setMotorB(-50);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 50)
    {
        getCDValues(&CDSensor2);
    }

    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    setRightSensorOut();
    lineFollowEncoder(35, 45, 30, 190);

    setMotorA(27);
    setMotorB(-24);
    // ехать до коричневого
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 70)
    {
        getCDValues(&CDSensor1);
    }
    setMotorA(24);
    setMotorB(-22);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue < 690)
    {
        getCDValues(&CDSensor1);
    }
    setMotorA(22);
    setMotorB(-22);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 500)
    {
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(22, -22, 20, 20, 32);

    // доворот одним колесом до зоны разгрузки


    arcEnc(0, -40, -80, -34, 500);

    setMotorBrakeMode(motorA, motorBrake);
    motor[motorA] = 0;

    setMotorB(-34);
    while (true) {
        getCDValues(&CDSensor1);
        if (CDSensor1.normRed > 100 && CDSensor1.normGreen < 60 && CDSensor1.normBlue < 60) {
            break;
        }
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];


    arcEnc(-18, 18, 19, 15, 110);
    stopMove(300);

    setTimeManipD(400, 10, 0);
    waitForManipD();
    setDegManipC(nMotorEncoder[motorC] - constsManipC.almostClose, -40, 0);
    waitForManipC();
    sleep(300);
    arcEnc(-18, 18, 18, 14, 11);
    stopMove(300);
    setPositionManipD(constsManipD.goFromStorageCubes, 100, 0);
    waitForManipD();
    sleep(300);

    // перевозим башню в красную зону
    setPositionManipC(constsManipC.openToNotBrakeSomething, 50, 0);
    arcEnc(-30, 30, 30, 12, 40);
    arcEnc(25, 40, 70, 40, 200);

    setMotorBrakeMode(motorA, motorBrake);
    motor[motorA] = 0;

    setMotorB(40);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 50)
    {
        getCDValues(&CDSensor2);
    }
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    setRightSensorIn();
    lineFollowEncoder(25, 35, 20, 550);
    setMotorA(24);
    setMotorB(-19);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 50)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    stopMove(300);

    arcEnc(-26, 26, 25, 15, 340);
    arcEnc(0, -30, -90, -35, 400);

    setMotorBrakeMode(motorA, motorBrake);
    motor[motorA] = 0;

    setMotorB(-35);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed < 180)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    stopMove(100);

    arcEnc(19, -19, 16, 10, 280);
    stopMove(500);
    
    arcEnc(-20, 20, 16, 16, 185);
    stopMove(1);
    setPositionManipD(constsManipD.goOverTwoCubes, 85, 0);
    waitForManipD();
    arcEnc(-20, 20, 50, 40, 190);

    setMotorA(-35);
    setMotorB(35);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue < 690)
    {
        getCDValues(&CDSensor1);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    stopMove(300);

    arcEnc(20, -20, 50, 30, 100);

    arcEnc(-30, -30, -90, -40, 200);
    
    setMotorBrakeMode(motorB, motorBrake);
    motor[motorB] = 0;
    setMotorA(-60);

    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 50)
    {
        getCDValues(&CDSensor2);
    }

    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    stopMove(1);
    setPositionManipC(constsManipC.takeFromLineCube, 90, 0);
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 20, 0);

    setRightSensorOut();
    lineFollowEncoder(30, 100, 50, 660);

    setMotorA(50);
    setMotorB(-50);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed < 190)
    {
        getCDValues(&CDSensor1);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(50, -50, 120, 20, 900);
    stopMove(300);
    arcEnc(6, 60, 120, 60, 540);

    setMotorBrakeMode(motorA, motorBrake);
    motor[motorA] = 0;

    setMotorB(30);
    sleep(400);

    setMotorA(70);
    setMotorB(-30);
    getCDValues(&CDSensor1);
    while (true)
    {
        if (CDSensor1.normRed > 200 && CDSensor1.normGreen < 100 && CDSensor1.normBlue < 100)
        {
            break;
        }
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    

    arcEnc(25, -24, 40, 16, 230);
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
}

void upperToLower()
{
    arcEnc(0, -50, -70, -50, 720);
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    gBoost = 10;
    arcEnc(40, -40, 80, 65, 630);
    gBoost = 10;
    arcEnc(65, -65, 50, 30, 400);

    setMotorA(30);
    setMotorB(-30);

    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(45, 0, 80, 40, 540);
    setMotorA(40);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 50)
    {
        getCDValues(&CDSensor1);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    setLeftSensorOut();
    lineFollowEncoder(35, 30, 30, 150);
    setMotorA(27);
    setMotorB(-24);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    setMotorA(27);
    setMotorB(-24);
    // ехать до коричневого
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 70)
    {
        getCDValues(&CDSensor2);
    }
    setMotorA(24);
    setMotorB(-22);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    setMotorA(22);
    setMotorB(-22);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 500)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(22, -22, 20, 20, 32);

    // доворот одним колесом до зоны разгрузки
    arcEnc(40, 0, 80, 34, 500);
    setMotorA(34);
    while (true) {
        getCDValues(&CDSensor2);
        if (CDSensor2.normRed > 100 && CDSensor2.normGreen < 60 && CDSensor2.normBlue < 60) {
            break;
        }
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(-18, 18, 20, 15, 90);
    stopMove(300);

    setTimeManipD(400, 10, 0);
    waitForManipD();
    setDegManipC(nMotorEncoder[motorC] - constsManipC.almostClose, -40, 0);
    waitForManipC();
    sleep(300);
    arcEnc(-18, 18, 18, 14, 11);
    stopMove(300);
    setPositionManipD(constsManipD.goFromStorageCubes, 100, 0);
    waitForManipD();
    sleep(300);

    // перевозим башню в красную зону
    setPositionManipC(constsManipC.openToNotBrakeSomething, 50, 0);
    arcEnc(-30, 30, 30, 12, 60);
    arcEnc(-40, -25, -70, -40, 200);

    setMotorBrakeMode(motorB, motorBrake);
    motor[motorB] = 0;

    setMotorA(-40);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 50)
    {
        getCDValues(&CDSensor1);
    }
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue < 690)
    {
        getCDValues(&CDSensor1);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(-20, 20, 20, 20, 300);

    setLeftSensorIn();
    lineFollowEncoder(19, 16, 16, 400);
    setMotorA(22);
    setMotorB(-19);
    getCDValues(&CDSensor1);
    while (true)
    {
        if (CDSensor1.normRed > 200 && CDSensor1.normGreen < 100 && CDSensor1.normBlue < 100)
        {
            break;
        }
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(25, -25, 30, 25, 75);
    //arcEnc(30, 0, 60, 30, 515);
    arcEnc(30, 0, 60, 40, 400);

    setMotorBrakeMode(motorB, motorBrake);
    motor[motorB] = 0;

    setMotorA(40);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed < 180)
    {
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(19, -19, 16, 10, 250);
    stopMove(500);
    
    arcEnc(-20, 20, 16, 16, 170);
    stopMove(1);
    setPositionManipD(constsManipD.goOverTwoCubes, 85, 0);
    waitForManipD();
    arcEnc(-20, 20, 30, 20, 190);

    arcEnc(20, 30, 50, 40, 200);
    arcEnc(-25, 25, 30, 25, 180);

    setMotorBrakeMode(motorB, motorBrake);
    motor[motorB] = 0;
    
    setMotorA(-40);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed < 190)
    {
        getCDValues(&CDSensor1);
    }

    setMotorBrakeMode(motorA, motorBrake);
    motor[motorA] = 0;

    setMotorB(25);

    getCDValues(&CDSensor2);
    while (CDSensor2.normRed < 190)
    {
        getCDValues(&CDSensor2);
    }

    setMotorBrakeMode(motorB, motorBrake);
    motor[motorB] = 0;
    
    setMotorA(-25);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed < 190)
    {
        getCDValues(&CDSensor1);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(20, -20, 20, 20, 20);

    stopMove(300, true);
    setDegManipD(nMotorEncoder[motorD] - constsManipD.prepareToTakeFromLine, -70, 0);
    waitForManipD();
    setPositionManipC(constsManipC.takeFromLineCube, 90, 0);
    waitForManipC();
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 20, 0);

    arcEnc(0, 25, 50, 20, 520);
    arcEnc(-20, 20, -20, -20, 300);
    // робот должен быть параллелен стенке, расстояние между роботом и стенкой должно быть, но не большое. Первый датчик должен быть до красной полосы старта
    setMotorA(70);
    setMotorB(-15);
    getCDValues(&CDSensor1);
    while (true)
    {
        if (CDSensor1.normRed > 200 && CDSensor1.normGreen < 100 && CDSensor1.normBlue < 100)
        {
            break;
        }
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(25, -24, 40, 14, 215);
}

void buildLower() {
    arcEnc(60, -60, -40, -30, 650);
    arcEnc(0, -33, -50, -33, 330);
    arcEnc(30, -30, 40, 30, 100);
    setMotorA(30);
    setMotorB(-30);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(0, -30, -50, -50, 500);

    setMotorB(-45);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue < 690)
    {
        getCDValues(&CDSensor1);
    }
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 50)
    {
        getCDValues(&CDSensor1);
    }
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue < 690)
    {
        getCDValues(&CDSensor1);
    }
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 500)
    {
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    setLeftSensorOutBrown();
    lineFollowEncoder(40, 30, 26, 380);

    setMotorA(26);
    setMotorB(-26);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    setMotorA(24);
    setMotorB(-24);
    // ехать до коричневого
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 70)
    {
        getCDValues(&CDSensor2);
    }
    setMotorA(22);
    setMotorB(-22);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    setMotorA(22);
    setMotorB(-22);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 500)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    // arcEnc(22, -22, 20, 20, 30);
    stopMove(300);

    setPositionManipD(constsManipD.put2Cube, 85, 0);
    waitForManipD();

    // доворот одним колесом до зоны разгрузки
    arcEnc(36, 0, 50, 36, 450);
    setMotorA(32);
    setMotorBrakeMode(motorB, motorBrake);
    motor[motorB] = 0;
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue < 400)
    {
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(17, -17, 17, 11, 50);
    arcEnc(0, -29, -29, -29, 55);
    stopMove(300);

    landCube();
    sleep(300);
    setPositionManipC(constsManipC.openToNotBrakeSomething, 50, 0);
    waitForManipC();
    setPositionManipD(constsManipD.goFromBuiltTower, 100, 0);
    waitForManipD();

    // перевозим башню в красную зону
    arcEnc(-30, 30, 30, 12, 90);
    arcEnc(-40, 0, -60, -40, 400);

    setMotorBrakeMode(motorB, motorBrake);
    motor[motorB] = 0;

    setMotorA(-40);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 50)
    {
        getCDValues(&CDSensor1);
    }
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue < 690)
    {
        getCDValues(&CDSensor1);
    }
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 300)
    {
        getCDValues(&CDSensor1);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    arcEnc(20, -20, 20, 20, 100);
    stopMove(1);
    setPositionManipD(constsManipD.hideWall, 100, 0);
    waitForManipD();
    setPositionManipD(constsManipD.takeCube, 100, 0);
    waitForManipD();

    arcEnc(-20, 20, 20, 20, 250);
    stopMove(300);
    setPositionManipD(constsManipD.goOverTwoCubes, 100, 0);
    waitForManipD();
    arcEnc(-20, 20, 40, 12, 200);
    stopMove(300);
    setPositionManipD(constsManipD.takeCube, 20, 0);
    waitForManipD();
    arcEnc(20, -20, 14, 11, 120);
    stopMove(1);
    setPositionManipC(constsManipC.takeFromLineCube, 40, 0);
    waitForManipC();
    setTimeManipC(400, 40, 70);
    waitForManipC();
    setPositionManipD(constsManipD.carryCubes, 60, 0);
    waitForManipD();
    stopMove(300);

    kpConstOne = 0.6;
    kdConstOne = 7;
    kiConstOne = 0.001;

    setLeftSensorOutBrown();
    lineFollowEncoder(30, 30, 20, 400);
    setMotorA(25);
    setMotorB(-19);
    getCDValues(&CDSensor1);
    while (true)
    {
        if (CDSensor1.normRed > 200 && CDSensor1.normGreen < 100 && CDSensor1.normBlue < 100)
        {
            break;
        }
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(25, -25, 30, 25, 105);
    stopMove(300);
    setPositionManipD(constsManipD.put2Cube, 85, 0);
    waitForManipD();
    arcEnc(30, 0, 60, 30, 470);

    setMotorA(30);
    setMotorBrakeMode(motorB, motorBrake);
    motor[motorB] = 0;

    getCDValues(&CDSensor1);
    while (CDSensor1.normRed < 190)
    {
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(16, -16, 16, 10, 30);
    arcEnc(0, -28, -28, -28, 55);
    stopMove(300);

    landCube();
    sleep(300);
    setPositionManipC(constsManipC.openToNotBrakeSomething, 50, 0);
    waitForManipC();
    setPositionManipD(constsManipD.goFromBuiltTower, 100, 0);
    waitForManipD();
}

void buildUpper() {
    arcEnc(60, -60, -40, -30, 500);
    arcEnc(0, -33, -50, -33, 400);
    arcEnc(30, -30, 40, 30, 100);
    setMotorA(30);
    setMotorB(-30);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(0, -30, -50, -50, 500);

    setMotorBrakeMode(motorA, motorBrake);
    motor[motorA] = 0;

    setMotorB(-45);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue < 690)
    {
        getCDValues(&CDSensor1);
    }
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 50)
    {
        getCDValues(&CDSensor1);
    }
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue < 690)
    {
        getCDValues(&CDSensor1);
    }
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 500)
    {
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(-24, 24, 24, 16, 500);
    stopMove(300);

    kpConstOne = 0.75;
    kdConstOne = 9;
    kiConstOne = 0.001;

    setLeftSensorOutBrown();
    lineFollowEncoder(25, 25, 26, 400);

    setMotorA(26);
    setMotorB(-26);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    setMotorA(24);
    setMotorB(-24);
    // ехать до коричневого
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 70)
    {
        getCDValues(&CDSensor2);
    }
    setMotorA(22);
    setMotorB(-22);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    setMotorA(22);
    setMotorB(-22);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 500)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    // arcEnc(22, -22, 20, 20, 30);
    stopMove(300);

    setPositionManipD(constsManipD.put2Cube, 85, 0);
    waitForManipD();

    // доворот одним колесом до зоны разгрузки
    arcEnc(36, 0, 50, 38, 450);
    setMotorA(34);
    setMotorBrakeMode(motorB, motorBrake);
    motor[motorB] = 0;
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue < 400)
    {
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(0, -35, -35, -35, 105);

    stopMove(500);

    landCube();
    sleep(300);
    setPositionManipC(constsManipC.openToNotBrakeSomething, 50, 0);
    waitForManipC();
    setPositionManipD(constsManipD.goFromBuiltTower, 90, 0);
    waitForManipD();

    // перевозим башню в красную зону
    arcEnc(-30, 30, 30, 12, 90);
    arcEnc(-40, 0, -60, -40, 400);

    setMotorBrakeMode(motorB, motorBrake);
    motor[motorB] = 0;

    setMotorA(-40);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 50)
    {
        getCDValues(&CDSensor1);
    }
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue < 690)
    {
        getCDValues(&CDSensor1);
    }
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 300)
    {
        getCDValues(&CDSensor1);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    kpConstOne = 0.65;
    kdConstOne = 7;
    kiConstOne = 0.001;

    setLeftSensorOutBrown();
    lineFollowEncoder(25, 25, 25, 300);
    lineFollowEncoder(25, 40, 20, 450);
    arcEnc(30, -30, 30, 25, 100);

    stopMove(1);
    setPositionManipD(constsManipD.hideWall, 100, 0);
    waitForManipD();
    setPositionManipD(constsManipD.takeCube, 100, 0);
    waitForManipD();

    arcEnc(-20, 20, 20, 20, 250);
    stopMove(300);
    setPositionManipD(constsManipD.goOverTwoCubes, 100, 0);
    waitForManipD();
    arcEnc(-20, 20, 40, 12, 200);
    stopMove(300);
    setPositionManipD(constsManipD.takeCube, 20, 0);
    waitForManipD();
    arcEnc(20, -20, 14, 11, 400);
    stopMove(1);
    setPositionManipC(constsManipC.takeFromLineCube, 40, 0);
    waitForManipC();
    setTimeManipC(400, 40, 70);
    waitForManipC();
    setPositionManipD(constsManipD.carryCubes, 60, 0);
    waitForManipD();

    arcEnc(30, 30, 60, 40, 450);
    

    setMotorA(40);
    setMotorB(40);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 50)
    {
        getCDValues(&CDSensor2);
    }
    setMotorA(35);
    setMotorB(35);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 500)
    {
        getCDValues(&CDSensor2);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    setRightSensorOutBrown();
    lineFollowEncoder(25, 60, 20, 700);

    setMotorA(32);
    setMotorB(-30);

    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 50)
    {
        getCDValues(&CDSensor2);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    stopMove(500);

    arcEnc(-25, 25, 30, 20, 340);

    stopMove(300);
    setPositionManipD(constsManipD.put2Cube, 85, 0);
    waitForManipD();
    arcEnc(0, -30, -60, -30, 400);

    setMotorBrakeMode(motorA, motorBrake);
    motor[motorA] = 0;
    setMotorB(-30);

    getCDValues(&CDSensor2);
    while (CDSensor2.normRed < 180)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(31, 0, 31, 30, 55);
    arcEnc(-30, 30, 30, 30, 10);
    stopMove(500);

    landCube();
    sleep(300);
    setPositionManipC(constsManipC.openToNotBrakeSomething, 50, 0);
    waitForManipC();
    setPositionManipD(constsManipD.goFromBuiltTower, 90, 0);
    waitForManipD();
}

void goFromLowerToSyncPoint() {
    // начинаем со красной зоны

    arcEnc(-25, 25, 40, 25, 300);
    setMotorA(-25);
    setMotorB(25);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed < 190)
    {
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    stopMove(1);

    setPositionManipC(constsManipC.takeFromLineCube, 40, 0);
    setPositionManipD(constsManipD.prepareToTakeFromLine, 40, 0);

    arcEnc(45, 0, 60, 45, 300);
    setMotorA(45);

    setMotorBrakeMode(motorB, motorBrake);
    motor[motorB] = 0;

    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 50)
    {
        getCDValues(&CDSensor2);
    }
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 500)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    kpConstOne = 0.55;
    kdConstOne = 6;
    kiConstOne = 0.001;

    setRightSensorOutBrown();
    lineFollowEncoder(30, 40, 30, 1200);

    setMotorA(33);
    setMotorB(-30);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 50)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    arcEnc(30, -30, 24, 18, 40);
    stopMove(500, true);


    setPositionManipD(constsManipD.hideWall, 70, 0);
    waitForManipD();
    setPositionManipD(constsManipD.elementsGoIn, 70, 0);
    waitForManipD();
    sleep(500);

    arcEnc(-29, -29, -35, -27, 260);
    stopMove(500);
    arcEnc(27, -27, 30, 27, 400);

    setMotorA(27);
    setMotorB(-27);

    getCDValues(&CDSensor1);
    while (CDSensor1.normRed < 190)
    {
        getCDValues(&CDSensor1);
    }

    setMotorBrakeMode(motorA, motorBrake);
    motor[motorA] = 0;

    setMotorB(-27);

    getCDValues(&CDSensor2);
    while (CDSensor2.normRed < 190)
    {
        getCDValues(&CDSensor2);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(27, -27, 25, 20, 158);
    stopMove(500);

    setPositionManipC(constsManipC.prepareWater, 30, 0);
    waitForManipC();
    setPositionManipD(constsManipD.prepareWater, 40, 0);
    waitForManipD();
    sleep(500);

    arcEnc(29, 29, 35, 27, 265);
    stopMove(500);
    arcEnc(25, -25, 30, 20, 695);

    setMotorA(30);
    setMotorBrakeMode(motorB, motorBrake);
    motor[motorB] = 0;
    int last = nMotorEncoder[motorA];
    sleep(500);
    while (nMotorEncoder[motorA] - last > 2)
    {
        last = nMotorEncoder[motorA];
        sleep(200);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    stopMove(300);

    arcEnc(-25, 0, -30, -25, 48);
    stopMove(300);

    setPositionManipC(constsManipC.waterUp, 200, 0);
    waitForManipC();
    sleep(500);
    setPositionManipD(constsManipD.takeCube, 70, 0);
    waitForManipD();
    setTimeManipC(800, 50, 20);
    waitForManipC();

    arcEnc(-32, 32, 80, 30, 800);
    arcEnc(-20, -54, -80, -45, 400);

    setMotorBrakeMode(motorA, motorBrake);
    motor[motorA] = 0;
    setMotorB(-45);

    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 50)
    {
        getCDValues(&CDSensor2);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(30, 0, 30, 30, 70);

    kpConstOne = 0.8;
    kdConstOne = 9;
    kiConstOne = 0.001;

    setRightSensorIn();
    lineFollowEncoder(30, 30, 30, 700);
    setMotorA(30);
    setMotorB(-30);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 50)
    {
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    stopMove(30000);
}

void goFromUpperToSyncPoint() {
    arcEnc(-25, 25, 60, 35, 250);
    setMotorA(-35);
    setMotorB(35);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue < 690)
    {
        getCDValues(&CDSensor1);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    stopMove(300);

    arcEnc(25, -25, 35, 20, 130);

    arcEnc(-10, -30, -80, -60, 190);
    
    setMotorBrakeMode(motorA, motorBrake);
    motor[motorA] = 0;
    setMotorB(-60);

    getCDValues(&CDSensor1);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue > 50)
    {
        getCDValues(&CDSensor1);
    }

    setMotorB(-30);
    while (CDSensor1.normRed + CDSensor1.normGreen + CDSensor1.normBlue < 690)
    {
        getCDValues(&CDSensor1);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    setPositionManipC(constsManipC.prepareWater, 30, 0);
    setPositionManipD(constsManipD.prepareWater, 40, 0);

    setLeftSensorIn();
    lineFollowEncoder(30, 90, 45, 800);

    setMotorA(37);
    setMotorB(-35);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed < 190)
    {
        getCDValues(&CDSensor1);
    }
    
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(50, 0, 70, 50, 260);
    arcEnc(0, -50, -70, -50, 260);

    setLeftSensorInRed();
    lineFollowEncoder(30, 50, 45, 300);

    setMotorA(42);
    setMotorB(-40);
    getCDValues(&CDSensor1);
    while (CDSensor1.normRed < 190)
    {
        getCDValues(&CDSensor1);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(40, -47, 60, 30, 500);

    arcEnc(34, -30, 20, 10, 320);

    setMotorA(30);
    setMotorBrakeMode(motorB, motorBrake);
    motor[motorB] = 0;
    int last = nMotorEncoder[motorA];
    sleep(500);
    while (nMotorEncoder[motorA] - last > 2)
    {
        last = nMotorEncoder[motorA];
        sleep(200);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    stopMove(300);

    arcEnc(-25, 0, -30, -25, 48);
    stopMove(300);

    setPositionManipC(constsManipC.waterUp, 200, 0);
    waitForManipC();
    sleep(500);
    setPositionManipD(constsManipD.takeCube, 70, 0);
    waitForManipD();
    setTimeManipC(800, 50, 20);
    waitForManipC();

    arcEnc(-32, 32, 45, 30, 570);

    arcEnc(0, 29, 40, 25, 550);

    stopMove(300);
    setPositionManipD(constsManipD.elementsGoIn, 70, 0);
    setPositionManipC(constsManipC.openToNotBrakeSomething, 70, 0);

    arcEnc(29, -29, 50, 23, 700);

    stopMove(300);

    setPositionManipD(constsManipD.carryElements, 70, 0);
    waitForManipD();

    arcEnc(-40, 40, 90, 40, 900);

    setMotorA(-41);
    setMotorB(40);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed < 190)
    {
        getCDValues(&CDSensor2);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    stopMove(3000);

    
    stopMove(30000);
}

void doRightWater() {

}

void doLeftWater() {

}

void testFunc()
{
    // waitInitManip();
    // playSound(soundBlip);
    // setDegManipD(nMotorEncoder[motorD] - constsManipD.prepareToTakeFromLine, -60, 0);
    // waitForManipD();
    // setDegManipC(constsManipC.takeFromLineCube, 90, 0);
    // waitForManipC();
    // setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 25, 0);
    // waitForManipD();
    // sleep(5000);
    // setTimeManipC(800, 40, 80);
    // waitForManipC();
    // sleep(300);
    // setDegManipD(nMotorEncoder[motorD] - constsManipD.put2Cube, -80, 0);
    // waitForManipD();
    // sleep(3000000);

    // setLeftSensorOutBrown();
    // lineFollowEncoder(35, 40, 30, 295);
    // startTask(initManip, kLowPriority);
    // waitInitManip();

    // goFromUpperToSyncPoint();

    buildUpper();
}

void mainLogic()
{
    startTask(initManip, kLowPriority);

    #if UPPER_START == 1
    startFromUpper();
    #else
    startFromLower();
    #endif

    takeRedAndYellowCubes();

    #if UPPER_START == 1
    upperToLower();
    #else
    lowerToUpper();
    #endif

    takeRedAndYellowCubes();

    #if UPPER_START == 1
    buildLower();
    goFromLowerToSyncPoint();
    #else
    buildUpper();
    goFromUpperToSyncPoint();
    #endif

    doRightWater();
    doLeftWater();
}