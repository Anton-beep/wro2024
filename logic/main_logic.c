#include "logic_vars.c"
#include "tools.c"

void startFromLower() {
    waitInitManip();
    setDegManipD(nMotorEncoder[motorD] - constsManipD.prepareToTakeFromLine, -70, 0);
    waitForManipD();
    setDegManipC(constsManipC.takeFromLineCube, 90, 0);
    waitForManipC();
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 20, 0);

    arcEnc(-23, 0, -70, -23, 380);
    arcEnc(0, 23, 70, 23, 380);
    setMotorB(45);
    sleep(250);
    stopMove(100, true);

    arcEnc(25, -24, 60, 30, 300);
    setMotorA(32);
    setMotorB(-30);
    getCDValues(&CDSensor1);
    while (true)
    {
        if (CDSensor1.normRed > 200 && CDSensor1.normGreen < 200 && CDSensor1.normBlue < 200)
        {
            break;
        }
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(25, -24, 40, 14, 255);
    // робот слегка пнул кубик
}

void startFromUpper() {
    waitInitManip();
    setDegManipD(nMotorEncoder[motorD] - constsManipD.prepareToTakeFromLine, -70, 0);
    waitForManipD();
    setDegManipC(constsManipC.takeFromLineCube, 90, 0);
    waitForManipC();
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 20, 0);

    arcEnc(-23, 0, -70, -23, 380);
    arcEnc(0, 23, 70, 23, 380);
    setMotorB(45);
    sleep(250);
    stopMove(100, true);

    arcEnc(25, -24, 60, 30, 300);
    setMotorA(32);
    setMotorB(-30);
    getCDValues(&CDSensor1);
    while (true)
    {
        if (CDSensor1.normRed > 200 && CDSensor1.normGreen < 200 && CDSensor1.normBlue < 200)
        {
            break;
        }
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    

    arcEnc(25, -24, 40, 14, 270);
    // робот слегка пнул кубик
}

void landCube() {
    setPowerAdjustBatteryManipD(4, 8);
    int lastEncoderD = nMotorEncoder[motorD];
    sleep(120);
    while (nMotorEncoder[motorD] - lastEncoderD > 3)
    {
        lastEncoderD = nMotorEncoder[motorD];
        sleep(70);
    }
    setPowerAdjustBatteryManipD(-15, 8);
    sleep(400);
    setPowerAdjustBatteryManipD(0, 8);
}

void takeRedAndYellowCubes()
{
    arcEnc(24, -23, 24, 12, 140);
    arcEnc(-17, 17, 17, 17, 5);
    stopMove(500, true);
    setTimeManipC(600, 30, 0);
    waitForManipC();
    setPositionManipD(constsManipD.put1Cube, 60, 0);
    waitForManipD();
    sleep(300);
    arcEnc(24, -23, 20, 12, 115);
    stopMove(1, true);
    landCube();
    setDegManipC(nMotorEncoder[motorC] - constsManipC.goOverTwoCubesOnLine, -70, 0);
    waitForManipC();
    setPositionManipD(constsManipD.hideWall, 50, 0);
    waitForManipD();
    setPositionManipD(constsManipD.goOverTwoCubes, 100, 0);
    waitForManipD();
    sleep(300);

    arcEnc(24, -23, 40, 24, 140);
    stopMove(300, true);
    setPositionManipC(constsManipC.takeFromLineCube, 70, 0);
    setPositionManipD(constsManipD.takeCube, 30, 0);
    waitForManipC();
    waitForManipD();
    arcEnc(24, -23, 15, 11, 175);

    arcEnc(-17, 17, 17, 17, 5);
    stopMove(500, true);
    setTimeManipC(600, 30, 0);
    waitForManipC();
    setPositionManipD(constsManipD.put1Cube, 60, 0);
    waitForManipD();
    sleep(300);
    arcEnc(24, -23, 20, 12, 113);
    stopMove(1, true);
    landCube();
    setDegManipC(nMotorEncoder[motorC] - constsManipC.goOverTwoCubesOnLine, -70, 0);
    waitForManipC();
    sleep(300);
    setPositionManipD(constsManipD.takeCube, 50, 0);
    waitForManipD();
    sleep(300);
    setTimeManipC(600, 30, 80);
    waitForManipC();
    setPositionManipD(constsManipD.carryCubes, 60, 0);
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

}

void upperToLower()
{
    arcEnc(0, -50, -70, -50, 750);
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    gBoost = 10;
    arcEnc(40, -40, 80, 65, 680);
    gBoost = 10;
    arcEnc(65, -65, 50, 30, 400);
    playSound(soundBlip);

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
    lineFollowEncoder(35, 50, 30, 550);
    setMotorA(28);
    setMotorB(-28);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 100)
    {
        getCDValues(&CDSensor2);
    }
    setMotorA(26);
    setMotorB(-26);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    setMotorA(24);
    setMotorB(-24);
    // ехать до коричневого
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 400)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(22, -22, 20, 20, 40);

    // доворот одним колесом до зоны разгрузки
    arcEnc(40, 0, 80, 26, 500);
    setMotorA(24);
    while (true) {
        getCDValues(&CDSensor2);
        if (CDSensor2.normRed > 100 && CDSensor2.normGreen < 60 && CDSensor2.normBlue < 60) {
            break;
        }
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(-18, 18, 20, 15, 100);
    stopMove(300);

    setTimeManipD(400, 10, 0);
    waitForManipD();
    setDegManipC(nMotorEncoder[motorC] - constsManipC.almostClose, -40, 0);
    waitForManipC();
    sleep(300);
    arcEnc(-18, 18, 18, 14, 15);
    stopMove(300);
    setPositionManipD(constsManipD.goFromStorageCubes, 100, 0);
    waitForManipD();
    sleep(300);

    arcEnc(-30, 30, 50, 12, 220);
    stopMove(300);
    setPositionManipC(constsManipC.openToNotBrakeSomething, 50, 0);
    
    // перевозим башню в красную зону

    // можно попробовать доезд 2 датчиком до границы красной зоны, а потом доворот левым колесом до того момента, как первый датчик достигнет границы зоны. Робот должен встать параллельно зоне.
    arcEnc(-30, 0, -40, -30, 240);
    arcEnc(20, -20, 40, 25, 300);

    setMotorA(25);
    setMotorB(-25);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed < 190)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    arcEnc(40, -30, 40, 20, 480);
    stopMove(300);
    arcEnc(-20, 20, 20, 10, 400);
    stopMove(300);
    setPositionManipD(constsManipD.goOverTwoCubes, 85, 0);
    waitForManipD();

    arcEnc(-20, 20, 40, 20, 100);
    arcEnc(0, 20, 80, 20, 320);
    arcEnc(-20, 0, -80, -20, 320);
    stopMove(300);
    setDegManipD(nMotorEncoder[motorD] - constsManipD.prepareToTakeFromLine, -70, 0);
    waitForManipD();
    setDegManipC(constsManipC.takeFromLineCube, 90, 0);
    waitForManipC();
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 20, 0);
    // проверить: при движении робота назад второй датчик увидит белую линию
    
    setMotorA(-25);
    setMotorB(25);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 50)
    {
        getCDValues(&CDSensor2);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    setMotorA(-25);
    setMotorB(25);

    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    //arcEnc(-25, 25, 35, 20, 200);
    arcEnc(0, 25, 50, 20, 300);
    stopMove(3000)
    // робот должен быть параллелен стенке, расстояние между роботом и стенкой должно быть, но не большое. Первый датчик должен быть до красной полосы старта
    setMotorA(32);
    setMotorB(-30);
    getCDValues(&CDSensor1);
    while (true)
    {
        if (CDSensor1.normRed > 200 && CDSensor1.normGreen < 200 && CDSensor1.normBlue < 200)
        {
            break;
        }
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(25, -24, 40, 14, 255);
}

void buildLower() {
    arcEnc(0, 50, 70, 50, 500);
    stopMove(3000);

    // 2 датчик будет на линии белый-коричневый, когда робот проедет вперед
    arcEnc(50, -50, 60, 40, 200);
    setMotorA(40);
    setMotorB(-40);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    setLeftSensorOutBrown()
    lineFollowEncoder(40, 50, 30, 200);
    stopMove(3000);

    getCDValues(&CDSensor2);
    while (true)
    {
        if (CDSensor2.normRed > 200 && CDSensor2.normGreen > 200 && CDSensor2.normBlue < 130) {
            break;
        }
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    stopMove(3000);
    //стоим перед желтой зоной

    arcEnc(30, 10, 30, 30, 20);
    arcEnc(-10, -30, -30, -30, 20);
    stopMove(3000);
    // стоим перед башней или уже уперлись в башню, готов достроить башню

    arcEnc(-15, 15, -15, -15, 10);
    stopMove(300);
    setPositionManipD(constsManipD.put2Cube, 85, 0);
    arcEnc(18, -18, 25, 15, 120);
    stopMove(3000);
    setTimeManipD(400, 10, 0);
    waitForManipD();
    setDegManipC(nMotorEncoder[motorC] - constsManipC.almostClose, -40, 0);
    waitForManipC();
    sleep(300);
    arcEnc(-18, 18, 18, 14, 20);
    stopMove(300);
    setDegManipD(nMotorEncoder[motorD] - constsManipD.takeFromStorage, -70, 0);
    waitForManipD();
    sleep(300);
    setDegManipC(nMotorEncoder[motorC] - constsManipC.openToTakeFromStorage, -70, 0);
    waitForManipC();
    sleep(300);

    arcEnc(-30, 30, 30, 12, 230);
    stopMove(300);

    // захват башни
    setDegManipC(constsManipC.almostClose - nMotorEncoder[motorC], 40, 0);
    waitForManipC();
    sleep(300);
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 30, 0);
    waitForManipD();
    sleep(300);
    arcEnc(14, -14, 12, 11, 100);
    stopMove(300);
    setTimeManipC(300, 40, 30);
    waitForManipC();
    sleep(300);
    setDegManipD(nMotorEncoder[motorD] - constsManipD.carryCubes, -60, 0);
    waitForManipD();
}

void buildUpper() {

}

void goFromLowerToSyncPoint() {
    // начинаем со красной зоны
    // огибаем башни оказываемся в upper
    gBoost = 25;
    arcEnc(-25, 25, 50, 60, 100);
    arcEnc(-50, 70, -50, -20, 400);
    stopMove(3000);
    // робот может проехать вперед и встать в зеленую/синию зону
    arcEnc(150, -150, 150, 150, 500);
    stopMove(3000);
    // желтая и красная башня пройдены, дальше съезд
    arcEnc(0, -150, -100, -50, 400);
    stopMove(3000);
    // проезд вперед, чтобы достичь upper линии
    arcEnc(60, -60, 200, 60, 400);
    setMotorA(55);
    setMotorB(-55);

    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue < 690)
    {
        getCDValues(&CDSensor2);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    setMotorA(40);
    setMotorB(-40);
    getCDValues(&CDSensor2);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 50)
    {
        getCDValues(&CDSensor2);
    }

    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    arcEnc(70, 0, 200, 60, 540);
    setLeftSensorIn();
    lineFollowEncoder(60, 70, 50, 500);
    setMotorA(45);
    setMotorB(-45);
    
    getCDValues(&CDSensor1);
    while (true)
    {
        if (CDSensor1.normRed > 200 && CDSensor1.normGreen < 200 && CDSensor1.normBlue < 200)
        {
            break;
        }
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    gBoost = 10;
}

void goFromUpperToSyncPoint() {

}

void doRightWater() {
    arcEnc(45, -15, 45, 45, 30);
    setRightSensorOutRed();
    lineFollowEncoder(45, 60, 50, 300);

    setMotorA(45);
    setMotorB(-45);
    
    getCDValues(&CDSensor1);
    while (true)
    {
        if (CDSensor1.normRed > 200 && CDSensor1.normGreen < 200 && CDSensor1.normBlue < 200)
        {
            break;
        }
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];

    setPositionManipD(constsManipD.prepareToTakeFromLine, 40, 0);
    setPositionManipC(constsManipC.takeFromLineCube, 40, 0);

    arcEnc(60, 0, 40, 30, 200);
    stopMove(3000);
    // робот может забрать элемент, если проедет вперед

    arcEnc(30, -30, 50, 11, 400);
    stopMove(3000);
    //элемент можно захватить

    setTimeManipC(500, 60, 20);
    waitForManipC();

    arcEnc(30, 30, 50, 30, 150);
    stopMove(3000);
    // робот смотрит на кран

    setTimeManipC(200, -70, -70);
    waitForManipC();
    setPositionManipC(constsManipC.prepareWater, 80, 0);
    setPositionManipD(constsManipD.prepareWater, 70, 0);

    arcEnc(30, -30, 40, 30, 150);
    setMotorA(26);
    setMotorB(-26);
    getCDValues(&CDSensor1);
    while (CDSensor2.normRed + CDSensor2.normGreen + CDSensor2.normBlue > 100)
    {
        getCDValues(&CDSensor1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
    stopMove(3000);
    // робот подцепил кран и готов поднять его
}

void doLeftWater() {

}

void testFunc()
{
    waitInitManip();
    playSound(soundBlip);
    setDegManipD(nMotorEncoder[motorD] - constsManipD.prepareToTakeFromLine, -60, 0);
    waitForManipD();
    setDegManipC(constsManipC.takeFromLineCube, 90, 0);
    waitForManipC();
    setDegManipD(constsManipD.takeCube - nMotorEncoder[motorD], 25, 0);
    waitForManipD();
    sleep(5000);
    setTimeManipC(800, 40, 80);
    waitForManipC();
    sleep(300);
    setDegManipD(nMotorEncoder[motorD] - constsManipD.put2Cube, -80, 0);
    waitForManipD();
    sleep(3000000);

    // setLeftSensorOut();
    // lineFollowEncoder(35, 60, 30, 5000);
}

void mainLogic()
{
    if (UPPER_START)
    {
        startFromUpper();
    }
    else
    {
        startFromLower();
    }

    takeRedAndYellowCubes();

    if (UPPER_START)
    {
        upperToLower();
    }
    else
    {
        lowerToUpper();
    }

    takeRedAndYellowCubes();

    if (UPPER_START)
    {
        buildLower();
        goFromLowerToSyncPoint();
    }
    else
    {
        buildUpper();
        goFromUpperToSyncPoint();
    }

    doRightWater();
    doLeftWater();
}