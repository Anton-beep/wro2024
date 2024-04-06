#include "syncVoltage.c"

// Вроде как не имеет смысла, просто перменные 
float kpNow = 0.55;
float kdNow = 6;
float kiNow = 0.002;

// Обычное движение по двум датчикам
const float kpConstBase = 0.75;
const float kdConstBase = 16;
const float kiConstBase = 0.001;

// Движение по одному датчику
const float kpConstOne = 0.55;
const float kdConstOne = 11;
const float kiConstOne = 0.001;

float calibrationPower = 50;

typedef struct
{
    float minLine;
    float maxLine;
    float crossRoadMin;
    float crossRoadMax;
    short sensorsIndError; // 0, 1, 2
    short sensorsIndCross; // 0, 1, 2
    bool rgb[3];           // 1, 1, 1
    bool rgbCross[3];
    short inverse;
} tLFConfig, *tLFConfigPtr;

typedef struct
{
    float error;
    bool cross;
    float firstValue;
    float secondValue;
} tPIDvalues, *tPIDvaluesPtr;

tLFConfig lineCFG;

void countValues(tCDValues *firstCD, tCDValues *secondCD,
                 tPIDvaluesPtr PIDValues)
{
    getCDValues(firstCD);
    getCDValues(secondCD);

    float firstValue = firstCD->normAmbient;
    float secondValue = secondCD->normAmbient;

    firstValue = mapping(firstValue, lineCFG.minLine, lineCFG.maxLine, 0, 100);
    secondValue = mapping(secondValue, lineCFG.minLine, lineCFG.maxLine, 0, 100);

    float error;
    bool cross;

    if (lineCFG.sensorsIndError == 0)
    {
        error = (firstValue - 50) * lineCFG.inverse;
    }
    else if (lineCFG.sensorsIndError == 1)
    {
        error = (secondValue - 50) * lineCFG.inverse;
    }
    else
    {
        error = (-firstValue + secondValue) * lineCFG.inverse;
    }

    bool firstCrossCheck = ((lineCFG.crossRoadMin <= firstValue) &&
                        (firstValue <= lineCFG.crossRoadMax));
    bool secondCrossCheck = ((lineCFG.crossRoadMin <= secondValue) &&
                            (secondValue <= lineCFG.crossRoadMax));

    if (lineCFG.sensorsIndCross == 0)
    {
        cross = firstCrossCheck;
    }
    else if (lineCFG.sensorsIndCross == 1)
    {
        cross = secondCrossCheck;
    }
    else
    {
        cross = firstCrossCheck && secondCrossCheck;
    }

    PIDValues->cross = cross;
    PIDValues->error = error;
}

void setBaseCoef()
{
    kpNow = kpConstBase;
    kdNow = kdConstBase;
    kiNow = kiConstBase;
}

void setOneSensorCoef()
{
    kpNow = kpConstOne;
    kdNow = kdConstOne;
    kiNow = kiConstOne;
}

void setDefaultLine()
{
    setBaseCoef();
    lineCFG.maxLine = 100;
    lineCFG.minLine = 0;
    lineCFG.inverse = 1;
    lineCFG.crossRoadMax = 50;
    lineCFG.crossRoadMin = -100;
    lineCFG.sensorsIndError = 2;
    lineCFG.sensorsIndCross = 2;
    lineCFG.rgb[0] = true;
    lineCFG.rgb[1] = true;
    lineCFG.rgb[2] = true;
    lineCFG.rgbCross[0] = true;
    lineCFG.rgbCross[1] = true;
    lineCFG.rgbCross[2] = true;
}

void setLeftSensorDefault()
{
    setOneSensorCoef();
    lineCFG.maxLine = 100;
    lineCFG.minLine = 0;
    lineCFG.inverse = 1;
    lineCFG.crossRoadMax = 50;
    lineCFG.crossRoadMin = -100;
    lineCFG.sensorsIndError = 0;
    lineCFG.sensorsIndCross = 2;
    lineCFG.rgb[0] = true;
    lineCFG.rgb[1] = true;
    lineCFG.rgb[2] = true;
    lineCFG.rgbCross[0] = true;
    lineCFG.rgbCross[1] = true;
    lineCFG.rgbCross[2] = true;
}

void setRightSensorDefault()
{
    setOneSensorCoef();
    lineCFG.maxLine = 100;
    lineCFG.minLine = 0;
    lineCFG.inverse = 1;
    lineCFG.crossRoadMax = 50;
    lineCFG.crossRoadMin = -100;
    lineCFG.sensorsIndError = 1;
    lineCFG.sensorsIndCross = 2;
    lineCFG.rgb[0] = true;
    lineCFG.rgb[1] = true;
    lineCFG.rgb[2] = true;
    lineCFG.rgbCross[0] = true;
    lineCFG.rgbCross[1] = true;
    lineCFG.rgbCross[2] = true;
}


void setDefaultLineGreyCross()
{
    setBaseCoef();
    lineCFG.maxLine = 255;
    lineCFG.minLine = 0;
    lineCFG.inverse = 1;
    lineCFG.crossRoadMax = 210;
    lineCFG.crossRoadMin = 180;
    lineCFG.sensorsIndError = 2;
    lineCFG.sensorsIndCross = 2;
    lineCFG.rgb[0] = true;
    lineCFG.rgb[1] = true;
    lineCFG.rgb[2] = true;
    lineCFG.rgbCross[0] = true;
    lineCFG.rgbCross[1] = true;
    lineCFG.rgbCross[2] = true;
}

void setLeftSensorBlackLineBlackStop(short side, short stopType)
{
    // 1 - in -1 - out ||| stop - 0(left) 1(right) 2(both)
    setOneSensorCoef();
    lineCFG.maxLine = 255;
    lineCFG.minLine = 0;
    lineCFG.inverse = side;
    lineCFG.crossRoadMax = 40;
    lineCFG.crossRoadMin = -100;
    lineCFG.sensorsIndError = 0;
    lineCFG.sensorsIndCross = stopType;
    lineCFG.rgb[0] = true;
    lineCFG.rgb[1] = true;
    lineCFG.rgb[2] = true;
    lineCFG.rgbCross[0] = false;
    lineCFG.rgbCross[1] = false;
    lineCFG.rgbCross[2] = true;
}

void setDefaultLineWhiteCross()
{
    setBaseCoef();
    lineCFG.maxLine = 255;
    lineCFG.minLine = 0;
    lineCFG.inverse = 1;
    lineCFG.crossRoadMax = 255;
    lineCFG.crossRoadMin = 230;
    lineCFG.sensorsIndError = 2;
    lineCFG.sensorsIndCross = 2;
    lineCFG.rgb[0] = true;
    lineCFG.rgb[1] = true;
    lineCFG.rgb[2] = true;
    lineCFG.rgbCross[0] = true;
    lineCFG.rgbCross[1] = false;
    lineCFG.rgbCross[2] = false;
}

void setLeftSensorBlueLineBlackStop(short side,
                                    short stopType)
{ // 1 - in -1 - out
    setOneSensorCoef();
    lineCFG.maxLine = 255;
    lineCFG.minLine = 0;
    lineCFG.inverse = side;
    lineCFG.crossRoadMax = 50;
    lineCFG.crossRoadMin = -100;
    lineCFG.sensorsIndError = 0;
    lineCFG.sensorsIndCross = stopType;
    lineCFG.rgb[0] = true;
    lineCFG.rgb[1] = true;
    lineCFG.rgb[2] = false;
    lineCFG.rgbCross[0] = false;
    lineCFG.rgbCross[1] = false;
    lineCFG.rgbCross[2] = true;
}

void setRightSensorBlueLineBlackStop(short side,
                                     short stopType)
{ // 1 - in -1 - out
    setOneSensorCoef();
    lineCFG.maxLine = 255;
    lineCFG.minLine = 0;
    lineCFG.inverse = side;
    lineCFG.crossRoadMax = 50;
    lineCFG.crossRoadMin = -100;
    lineCFG.sensorsIndError = 1;
    lineCFG.sensorsIndCross = stopType;
    lineCFG.rgb[0] = true;
    lineCFG.rgb[1] = true;
    lineCFG.rgb[2] = false;
    lineCFG.rgbCross[0] = false;
    lineCFG.rgbCross[1] = false;
    lineCFG.rgbCross[2] = true;
}

void setRightSensorBlueGrayLineWhiteStop(short side, short stopType)
{ // 1 - in -1 - out
    setOneSensorCoef();
    lineCFG.maxLine = 170;
    lineCFG.minLine = 45;
    lineCFG.inverse = side;
    lineCFG.crossRoadMax = 255;
    lineCFG.crossRoadMin = 50;

    lineCFG.sensorsIndError = 1;

    lineCFG.sensorsIndCross = stopType;

    lineCFG.rgb[0] = true;
    lineCFG.rgb[1] = true;
    lineCFG.rgb[2] = true;

    lineCFG.rgbCross[0] = true;
    lineCFG.rgbCross[1] = true;
    lineCFG.rgbCross[2] = true;
}

void setRightSensorBlueGrayLineBlueStop(short side, short stopType)
{ // 1 - in -1 - out
    setOneSensorCoef();
    lineCFG.maxLine = 170;
    lineCFG.minLine = 45;
    lineCFG.inverse = side;
    lineCFG.crossRoadMax = 70;
    lineCFG.crossRoadMin = 10;

    lineCFG.sensorsIndError = 1;

    lineCFG.sensorsIndCross = stopType;

    lineCFG.rgb[0] = true;
    lineCFG.rgb[1] = true;
    lineCFG.rgb[2] = true;

    lineCFG.rgbCross[0] = false;
    lineCFG.rgbCross[1] = true;
    lineCFG.rgbCross[2] = false;
}

void calcKF(float power, float *kp, float *kd, float *ki)
{
    float temp = sqrt(power / calibrationPower);
    *kp = temp * kpNow;
    *kd = temp * kdNow;
    *ki = temp * kiNow;
}

void lineFollowCross(float startPower, float endPower, short crossCount,
                     float boost = gBoost)
{
    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);

    tPIDvalues PIDValues;
    PIDValues.cross = false;
    float e, ee = 0, U, P, I, D;
    float kp, kd, ki;
    float curPower = startPower, curPowerA, curPowerB;
    float oldAveEnc = (-nMotorEncoder[motorB] - nMotorEncoder[motorA]) / 2;
    short curCnt = 0;
    bool flag = false;

    int errSz = 20;
    int err[20];
    for (int i = 0; i < errSz; ++i)
    {
        err[i] = 0;
    }
    int curErrIdx = 0;
    int nwErrIdx;
    I = 0;
    while (curCnt < crossCount)
    {
        curPower = smooth(
            startPower, endPower,
            (-nMotorEncoder[motorB] - nMotorEncoder[motorA]) / 2 - oldAveEnc,
            boost);

        motorAstop = false;
        motorBstop = false;

        MTVarsA.targetV = -curPower;
        MTVarsB.targetV = -curPower;

        calcKF(curPower, &kp, &kd, &ki);
        countValues(&CDSensor1, &CDSensor2, &PIDValues);
        if (PIDValues.cross)
        {
            if (!flag)
            {
                ++curCnt;
            }
            flag = true;
        }
        else
        {
            flag = false;
        }
        e = PIDValues.error;
        P = e * kp;

        nwErrIdx = (curErrIdx + errSz - 1) % errSz;
        err[nwErrIdx] = e;
        I -= err[curErrIdx];
        I += err[nwErrIdx];
        curErrIdx = (curErrIdx + 1) % errSz;

        D = (e - ee) * kd;
        U = P + I * ki + D;
        curPowerA = -curPower + U;
        curPowerB = -curPower - U;

        saveRatioPID(&curPowerA, &curPowerB);

        setMotorA(curPowerA);
        setMotorB(curPowerB);
        ee = e;
        sleep(1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
}

void lineFollowEncoder(float startPower, float topPower, float endPower,
                       int encoder, float boost = gBoost)
{
    setMotorBrakeMode(motorA, motorCoast);
    setMotorBrakeMode(motorB, motorCoast);

    tPIDvalues PIDValues;
    PIDValues.cross = false;
    float e, ee = 0, U, P, I, D;
    float kp, kd, ki;
    float curPower = startPower, curPowerA, curPowerB;
    float oldAveEnc = (-nMotorEncoder[motorB] - nMotorEncoder[motorA]) / 2;
    short curEnc = 0;

    int errSz = 20;
    int err[20];
    for (int i = 0; i < errSz; ++i)
    {
        err[i] = 0;
    }
    int curErrIdx = 0;
    int nwErrIdx;
    I = 0;

    float excess = encoder - (2 * topPower * topPower -
                              startPower * startPower - endPower * endPower) /
                                 2 / boost;
    float maxPower = min2(sqrt(encoder * boost + startPower * startPower / 2 +
                               endPower * endPower / 2),
                          topPower);
    float smoothStartEnc =
        (maxPower * maxPower - startPower * startPower) / 2 / boost +
        max2(excess, 0);
    while ((curEnc = -(nMotorEncoder[motorB] + nMotorEncoder[motorA]) / 2 -
                     oldAveEnc) < encoder)
    {
        if (curEnc < smoothStartEnc)
        {
            curPower = smooth(startPower, maxPower, curEnc, boost);
        }
        else
        {
            curPower =
                smooth(maxPower, endPower, curEnc - smoothStartEnc, boost);
        }

        motorAstop = false;
        motorBstop = false;

        MTVarsA.targetV = -curPower;
        MTVarsB.targetV = -curPower;

        calcKF(curPower, &kp, &kd, &ki);
        countValues(&CDSensor1, &CDSensor2, &PIDValues);
        e = PIDValues.error;
        P = e * kp;

        nwErrIdx = (curErrIdx + errSz - 1) % errSz;
        err[nwErrIdx] = e;
        I -= err[curErrIdx];
        I += err[nwErrIdx];
        curErrIdx = (curErrIdx + 1) % errSz;

        D = (e - ee) * kd;
        U = P + I * ki + D;
        curPowerA = -curPower + U;
        curPowerB = -curPower - U;

        saveRatioPID(&curPowerA, &curPowerB);

        setMotorA(curPowerA);
        setMotorB(curPowerB);
        ee = e;
        sleep(1);
    }
    MTVarsA.targetEnc = nMotorEncoder[motorA];
    MTVarsB.targetEnc = nMotorEncoder[motorB];
}

void lineBase(float startV, float endV, float boost = gBoost)
{
    lineFollowEncoder(startV, startV, endV, g_distBetweenSensorsAndWheelBase, boost);
}