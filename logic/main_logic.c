#include "logic_vars.c"
#include "tools.c"

void mainLogic() {

}

void goOverBridge() {
    setDegManipD(constsManipD.startSuspension, 62, 0, 7.96);
    lineFollowCross(25, 25, 1);
    stopMove(1);
    waitForManipD();
    setDegManipD(constsManipD.suspensionForStartBridge - constsManipD.startSuspension, 62, 0, 7.96);
    stopMove(500);
    arcEnc(-30, -29, -32, -30, 260);
    stopMove(1);
    setDegManipD(constsManipD.suspensionForStartBridge, -45, 0, 7.89);
    sleep(600);
    arcEnc(-36.5, -35, -40, -30, 383);
    stopMove(900, true);
    sleep(800);
    arcEnc(-30, -30, -30, -30, 200);
    setDegManipC(constsManipC.closed, 40, 80, 8);
    arcEnc(-18, -18, -18, -17, 20);
    stopMove(500);
    motor[motorA] = 15;
    motor[motorB] = 15;
    sleep(1000);
    stopMove(1500, true);

    waitForManipC();
    sleep(500);
    setDegManipD(constsManipD.suspensionGoBackFromBridge, 75, 0, 8);
    waitForManipD();
    arcEnc(50, 50, 100, 80, 215);
    arcEnc(80, 80, 40, 27, 210);
    stopMove(1000);
    setDegManipD(constsManipD.suspensionGoBackFromBridge - constsManipD.suspenionPeakGoBack, -50, 0, 8);
    arcEnc(40, 40, 45, 30, 130);
    stopMove(1000);
}

void goOverObstacles(){
    setDegManipD(constsManipD.startSuspension, 50, 0, 7.96);
    lineFollowCross(25, 25, 1);
    stopMove(100);
    setDegManipD(constsManipD.suspensionOverObstacles1Part - constsManipD.startSuspension, 65, 0, 7.96);
    waitForManipD();
    setDegManipD(constsManipD.suspensionOverObstacles - constsManipD.suspensionOverObstacles1Part, 35, 0, 7.96);
    waitForManipD();
    arcEnc(30, -30, -50, -30, 60);
    arcEnc(-30, -30, -50, -30, 650); 
    arcEnc(-30, 33, -60, -30, 180);
    stopMove(1000);


    // setDegManipD(constsManipD.startSuspension, 50, 0, 7.96);
    // lineFollowCross(25, 25, 1);
    // stopMove(100); 
    // setDegManipD(constsManipD.suspensionOverObstacles1Part - constsManipD.startSuspension, 65, 0, 7.96);
    // waitForManipD();
    // setDegManipD(constsManipD.suspensionOverObstacles - constsManipD.suspensionOverObstacles1Part, 35, 0, 7.96);
    // sleep(200);
    // arcEnc(-30, 0, -100, -30, 380);
    // stopMove(500);
    // arcEnc(0, -30, -100, -30, 380);
    // arcEnc(-30, -30, -30, -30, 130);
    // arcEnc(0, -40, -80, -40, 171);
    // arcEnc(-50, -50, -80, -40, 190);
    // arcEnc(-50, -10, -50, -50, 139);
    // stopMove(2000, true);
    // setDegManipD(constsManipD.suspensionOverObstacles, -40, 0, 8);
    // waitForManipD();
    // sleep(100);
    // arcEnc(-25, -25, -25, -25, 150);
    // stopMove(1)
    // setDegManipC(constsManipC.closed, 50, 80, 8);
    // waitForManipC();
    // sleep(100);
    // setDegManipD(constsManipD.suspensionOverObstacles1Part, 75, 0, 7.96);
    // waitForManipD();
    // setDegManipD(constsManipD.suspensionOverObstaclesBack - constsManipD.suspensionOverObstacles1Part, 55, 0, 7.96);
    // waitForManipD();
    // arcEnc(58, 58, 80, 50, 245);
    // arcEnc(50, -20, 50, 50, 160);
    // arcEnc(25, 25, 50, 25, 310);
    // stopMove(2000);
    // arcEnc(0, -60, -90, -50, 400);
    // setDegManipD(constsManipD.suspensionOverObstaclesBack, -20, 0, 8);
    // stopMove(1000);
}

void testFunc() {


    // goOverObstacles();

    // setDegManipC(constsManipC.closed, 40, 80, 7.9);
    // waitForManipC();
    // sleep(2000);
    // setDegManipD(constsManipD.suspensionGoBackFromBridge, 68, 0, 8);
    // waitForManipD();
    // stopD();
    // sleep(3000);
    // setDegManipD(constsManipD.suspensionGoBackFromBridge, -25, 0, 8);
    // waitForManipD();

    // setDegManipD(constsManipD.suspensionGoBackFromBridge, 60, 0, 8);
    // waitForManipD();
    // sleep(1000);
    // setDegManipD(constsManipD.suspensionGoBackFromBridge, -30, 0, 8);

    // lineFollowEncoder(20, 70, 70, 300);
    // playSound(soundBlip);
    // arcEnc(-70, -70, -70, -20, 1200);
    // stopMove(1000);
}