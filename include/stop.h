#include "syncVoltage.c"

const float stopKP = 4;
const float stopKI = 0.06;
const float stopKD = 6;

task stopA_task {
    float u, e, ee = 0, isum = 0;
    int errSz = 20;
    int err[20];
    for (int i = 0; i < errSz; ++i) {
        err[i] = 0;
    }
    int curErrIdx = 0;
    int nwErrIdx;
    setMotorBrakeMode(motorA, motorCoast);
    motorAstop = true;
    while (motorAstop) {
        e = nMotorEncoder[motorA] - MTVarsA.targetEnc;

        nwErrIdx = (curErrIdx + errSz - 1) % errSz;
        err[nwErrIdx] = e;
        isum -= err[curErrIdx];
        isum += err[nwErrIdx];
        curErrIdx = (curErrIdx + 1) % errSz;

        u = e * stopKP + isum * stopKI + (e - ee) * stopKD;
        setMotorA(-u);
        ee = e;
        sleep(1);
    }
    
    stopTask(stopA_task);
}

task stopB_task {
    float u, e, ee = 0, isum = 0;
    int errSz = 20;
    int err[20];
    for (int i = 0; i < errSz; ++i) {
        err[i] = 0;
    }
    int curErrIdx = 0;
    int nwErrIdx;
    setMotorBrakeMode(motorB, motorCoast);
    motorBstop = true;
    while (motorBstop) {
        e = nMotorEncoder[motorB] - MTVarsB.targetEnc;
        nwErrIdx = (curErrIdx + errSz - 1) % errSz;
        err[nwErrIdx] = e;
        isum -= err[curErrIdx];
        isum += err[nwErrIdx];
        curErrIdx = (curErrIdx + 1) % errSz;
        u = e * stopKP + isum * stopKI + (e - ee) * stopKD;
        setMotorB(-u);
        ee = e;
        sleep(1);
    }

    stopTask(stopB_task);
}

void stopMove(int delayMsec = 0, bool reset = false, bool mode = true) {
    if (reset) {
        resetMotorEncoder(motorA);
        resetMotorEncoder(motorB);
        nMotorEncoder[motorA] = 0;
        nMotorEncoder[motorB] = 0;
        MTVarsA.targetEnc = 0;
        MTVarsB.targetEnc = 0;
        MTVarsA.targetV = 0;
        MTVarsB.targetV = 0;
    }
    startTask(stopA_task, kLowPriority);
    startTask(stopB_task, kLowPriority);

    sleep(delayMsec);
}
