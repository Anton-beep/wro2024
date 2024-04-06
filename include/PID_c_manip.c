/*
TODO:
- тест waitForManip (wait может срботать до активации функции)
- попробовать управлять не просто мощностью, а скоростью моторов, чтобы держать стабильную скорость движения
захватов (ПИД регулятор на RPM)
*/


typedef struct {
    int opened;
    int closed;
} ConstsManipC;

typedef struct {
    int holdCubes;
    int readyFor2;
    int takeSecondCube;
    int liftSecondCube;
    int readyFor4;
    int startSuspension;
    int suspensionForStartBridge;
    int suspensionMovingBridge;
    int suspensionBridgePeak;
    int suspensionMovingFromPeak;
    int suspensionGoBackFromBridge;
    int suspenionPeakGoBack;
    int suspenionGoBackAfterPeak;
    int endSuspension;

    int suspensionOverObstacles1Part;
    int suspensionOverObstacles;
    int suspensionOverObstaclesBack;
} ConstsManipD;

ConstsManipC constsManipC;
ConstsManipD constsManipD;

task initManip() {
    motor[motorC] = -40;
    motor[motorD] = -40;
    sleep(400);

    motor[motorC] = 0;
    motor[motorD] = 0;
    setMotorBrakeMode(motorC, motorCoast);
    setMotorBrakeMode(motorD, motorCoast);
    sleep(500);
    setMotorBrakeMode(motorC, motorBrake);
    setMotorBrakeMode(motorD, motorBrake);

    // consts

    constsManipC.opened = 0;
    constsManipC.closed = 373;

    constsManipD.holdCubes = 100;
    constsManipD.readyFor2 = 120;
    constsManipD.takeSecondCube = 100;
    constsManipD.liftSecondCube = 130;
    constsManipD.readyFor4 = 188;
    constsManipD.startSuspension = 190;
    constsManipD.suspensionForStartBridge = 250;
    constsManipD.suspensionBridgePeak = 250;
    constsManipD.suspensionMovingFromPeak = 110;
    constsManipD.suspensionGoBackFromBridge = 440;
    constsManipD.suspenionPeakGoBack = 170;
    constsManipD.suspenionGoBackAfterPeak = 80;
    constsManipD.endSuspension = 520;

    constsManipD.suspensionOverObstacles1Part = 280;
    constsManipD.suspensionOverObstacles = 345;
    constsManipD.suspensionOverObstaclesBack = 290;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int getSignedRPM(short mot)
{
    if (motor[mot] > 0)
    {
        return getMotorRPM(mot);
    }
    else
    {
        return -getMotorRPM(mot);
    }
}

void stopC()
{
    motor[motorC] = 0;
    setMotorBrakeMode(motorC, motorBrake);
}

void stopD()
{
    motor[motorD] = 0;
    setMotorBrakeMode(motorD, motorBrake);
}

void setPowerAdjustBatteryManipC(short pow, float batVoltage)
{
    if (pow == 0)
    {
        motor[motorC] = 0;
    }
    else
    {
        float val = pow * batVoltage / getBatteryVoltage();
        if (val < 0)
        {
            motor[motorC] = min(-1, val);
        }
        else
        {
            motor[motorC] = max(1, val);
        }
    }
}

void setPowerAdjustBatteryManipD(short pow, float batVoltage)
{
    if (pow == 0)
    {
        motor[motorD] = 0;
    }
    else
    {
        float val = pow * batVoltage / getBatteryVoltage();
        if (val < 0)
        {
            motor[motorD] = min(-1, val);
        }
        else
        {
            motor[motorD] = max(1, val);
        }
    }
}

void keepMovingManipC(short pow, float voltage)
{
    if (fabs(getMotorRPM(motorC)) < 6) {
        setPowerAdjustBatteryManipC(min(100, motor[motorC] + pow * 0.1), voltage);
    } else {
        setPowerAdjustBatteryManipC(max(pow, motor[motorC] - pow * 0.1), voltage);
    }
}

void keepMovingManipD(short pow, float voltage)
{
    if (fabs(getMotorRPM(motorD)) < 6) {
        setPowerAdjustBatteryManipD(min(100, motor[motorD] + pow * 0.1), voltage);
    } else {
        // int tempSpeed = motor[motorD] - pow * 0.1;
        // if (fabs(tempSpeed) > pow) {
        //     setPowerAdjustBatteryManipD(tempSpeed, voltage)  ; 
        // } else {
        //     setPowerAdjustBatteryManipD(pow, voltage);
        // }
    }
    eraseDisplay();
    displayTextLine(1, "rpm: %f", getMotorRPM(motorD));
    displayTextLine(2, "pow: %d", motor[motorD]);
}

void testAdjust()
{
    setPowerAdjustBatteryManipC(80, 7.6);
    while (true)
    {
        writeDebugStreamLine("%f; %d", getBatteryVoltage(), getSignedRPM(motorA));
        sleep(1);
    }
}

bool MANIP_C_READY = true;
bool MANIP_D_READY = true;

void waitForManipC()
{
    while (!MANIP_C_READY)
    {
        sleep(1);
    }
}

void waitForManipD()
{
    while (!MANIP_D_READY)
    {
        sleep(1);
    }
}

short TIME_MANIP_C_START_POW;
short TIME_MANIP_C_AFTER_POW;
float TIME_MANIP_C_VOLTAGE;
int TIME_MANIP_C_TIME;

task moveTimeManipC()
{
    setPowerAdjustBatteryManipC(TIME_MANIP_C_START_POW, TIME_MANIP_C_VOLTAGE);
    sleep(TIME_MANIP_C_TIME);
    setPowerAdjustBatteryManipC(TIME_MANIP_C_AFTER_POW, TIME_MANIP_C_VOLTAGE);
    MANIP_C_READY = true;
}

short TIME_MANIP_D_START_POW;
short TIME_MANIP_D_AFTER_POW;
float TIME_MANIP_D_VOLTAGE;
int TIME_MANIP_D_TIME;

task moveTimeManipD()
{
    setPowerAdjustBatteryManipD(TIME_MANIP_D_START_POW, TIME_MANIP_D_VOLTAGE);
    sleep(TIME_MANIP_D_TIME);
    setPowerAdjustBatteryManipD(TIME_MANIP_D_AFTER_POW, TIME_MANIP_D_VOLTAGE);
    MANIP_D_READY = true;
}

int DEG_MANIP_C_DEG;
short DEG_MANIP_C_START_POW;
short DEG_MANIP_C_AFTER_POW;
float DEG_MANIP_C_VOLTAGE;

task moveDegManipC()
{
    setPowerAdjustBatteryManipC(DEG_MANIP_C_START_POW, DEG_MANIP_C_VOLTAGE);
    int endDeg;
    if (DEG_MANIP_C_START_POW >= 0)
    {
        endDeg = nMotorEncoder[motorC] + DEG_MANIP_C_DEG;
        while (nMotorEncoder[motorC] < endDeg)
        {
            sleep(1);
        }
    }
    else
    {
        endDeg = nMotorEncoder[motorC] - DEG_MANIP_C_DEG;
        while (nMotorEncoder[motorC] > endDeg)
        {
            sleep(1);
        }
    }
    setPowerAdjustBatteryManipC(DEG_MANIP_C_AFTER_POW, DEG_MANIP_C_VOLTAGE);
    MANIP_C_READY = true;
}

int DEG_MANIP_D_DEG;
short DEG_MANIP_D_START_POW;
short DEG_MANIP_D_AFTER_POW;
float DEG_MANIP_D_VOLTAGE;

task moveDegManipD()
{
    setPowerAdjustBatteryManipD(DEG_MANIP_D_START_POW, DEG_MANIP_D_VOLTAGE);
    int endDeg;
    if (DEG_MANIP_D_START_POW >= 0)
    {
        endDeg = nMotorEncoder[motorD] + DEG_MANIP_D_DEG;
        while (nMotorEncoder[motorD] < endDeg)
        {
            sleep(1);
        }
    }
    else
    {
        endDeg = nMotorEncoder[motorD] - DEG_MANIP_D_DEG;
        while (nMotorEncoder[motorD] > endDeg)
        {
            sleep(1);
        }
    }
    setPowerAdjustBatteryManipD(DEG_MANIP_D_AFTER_POW, DEG_MANIP_D_VOLTAGE);
    MANIP_D_READY = true;
}

bool *setTimeManipC(int time, short powStart, short powAfter, float voltage = 8)
{
    stopTask(moveTimeManipC);
    stopTask(moveDegManipC);
    TIME_MANIP_C_START_POW = powStart;
    TIME_MANIP_C_AFTER_POW = powAfter;
    TIME_MANIP_C_VOLTAGE = voltage;
    TIME_MANIP_C_TIME = time;
    MANIP_C_READY = false;
    startTask(moveTimeManipC);
    return &MANIP_C_READY;
}

bool *setTimeManipD(int time, short powStart, short powAfter, float voltage = 8)
{
    stopTask(moveTimeManipD);
    stopTask(moveDegManipD);
    TIME_MANIP_D_START_POW = powStart;
    TIME_MANIP_D_AFTER_POW = powAfter;
    TIME_MANIP_D_VOLTAGE = voltage;
    TIME_MANIP_D_TIME = time;
    MANIP_D_READY = false;
    startTask(moveTimeManipD);
    return &MANIP_D_READY;
}

bool *setDegManipC(int deg, short powStart, short powAfter, float voltage = 8)
{
    stopTask(moveDegManipC);
    stopTask(moveTimeManipC);
    DEG_MANIP_C_DEG = deg;
    DEG_MANIP_C_START_POW = powStart;
    DEG_MANIP_C_AFTER_POW = powAfter;
    DEG_MANIP_C_VOLTAGE = voltage;
    MANIP_C_READY = false;
    startTask(moveDegManipC);
    return &MANIP_C_READY;
}

bool *setDegManipD(int deg, short powStart, short powAfter, float voltage = 8)
{
    stopTask(moveDegManipD);
    stopTask(moveTimeManipD);
    DEG_MANIP_D_DEG = deg;
    DEG_MANIP_D_START_POW = powStart;
    DEG_MANIP_D_AFTER_POW = powAfter;
    DEG_MANIP_D_VOLTAGE = voltage;
    MANIP_D_READY = false;
    startTask(moveDegManipD);
    return &MANIP_D_READY;
}

void runMot(short mot)
{
    int pow = 0;
    bool pressedUp = false;
    bool pressedDown = false;
    while (getButtonPress(buttonEnter) == false)
    {
        if (getButtonPress(buttonLeft))
            motor[mot] = -1 * pow;
        else if (getButtonPress(buttonRight))
            motor[mot] = pow;
        else
            motor[mot] = 0;

        if (getButtonPress(buttonUp))
            pressedUp = true;
        else if (getButtonPress(buttonDown))
            pressedDown = true;

        if (getButtonPress(buttonUp) == false && pressedUp == true)
        {
            pressedUp = false;
            pow++;
        }
        else if (getButtonPress(buttonDown) == false && pressedDown == true)
        {
            pressedDown = false;
            pow--;
        }
        eraseDisplay();
        displayTextLine(1, "Pow: %d", pow);
        sleep(100);
    }
}