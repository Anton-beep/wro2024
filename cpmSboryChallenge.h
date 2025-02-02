void fromStart() {
    arcEnc(-40, 40, 40, 40, 200);
    setLeftSensorBlackLineBlackStop(1, 1);
    lineFollowCross(40, 60, 1);
    lineBase(60, 40);
    stopMove(200);
    arcAngle(-40, -40, -40, -40, 90);
    stopMove(200);
}

int posShip;

void ofship() {
    setDefaultLine();
    lineFollowEncoder(30, 30, 30, 565);
    stopMove(250);
    arcAngle(0, -40, -100, -30, 80);
    arcAngle(0, -30, -30, -30, 11);
    stopMove(200);
    arcEnc(20, -20, 100, 20, 400);
    arcEnc(20, -20, 20, 20, 100);
    stopMove(200);
    getCDValues(&CDSensor3);
    changePosGrabberC(60, grabberC.maxUpWithoutShip);
    if (CDSensor3.val >= 15) {
        posShip = 0;
        arcEnc(-25, 25, 40, 25, 230);
        stopMove(200);
        arcAngle(35, 0, 60, 30, 90);
        stopMove(200);
        changePosGrabberD(60, grabberD.openMin);
        stopMove(400);
        
        arcEnc(-25, 25, 60, 25, 160);
        changePosGrabberC(60, grabberC.upForDrop - 50);
        stopMove(500);
        changePosGrabberD(100, grabberD.close);
        arcEnc(-25, 25, 25, 25, 50);
        changePosGrabberC(70, grabberC.maxUp);
        arcEnc(-25, 25, 25, 25, 220);
        stopMove(400);
        arcEnc(40, -40, 60, 40, 200);
        arcAngle(0, -40, -60, -40, 90);
        stopMove(200);
        arcEnc(-50, 50, 60, 40, 740);
        smartTurnLeft_angle(50, 60, 50);
        stopMove(100);
    } else {
        posShip = 1;
        arcEnc(-25, 25, 100, 25, 1400);
        stopMove(200);
        arcAngle(35, 0, 100, 30, 90);
        stopMove(200);
        
        changePosGrabberD(60, grabberD.openMin);
        stopMove(400);
        arcEnc(-25, 25, 40, 25, 160);
        changePosGrabberC(60, grabberC.upForDrop - 50);
        stopMove(500);
        changePosGrabberD(100, grabberD.close);
        arcEnc(-25, 25, 25, 25, 50);
        changePosGrabberC(70, grabberC.maxUp);
        arcEnc(-25, 25, 25, 25, 220);
        stopMove(400);
        arcEnc(40, -40, 60, 40, 300);
        arcAngle(50, 0, 60, 40, 90);
        stopMove(200);
        arcEnc(-50, 50, 60, 40, 800);
        smartTurnRight_angle(50, 60, 50);
        stopMove(100);
    }

}

void nop() {
    lineFollowCross(40, 100, 1);
    lineBase(100, 20);
    stopMove(200);
    smartTurnLeft_angle(50, 100, 50);
    lineFollowEncoder(40, 100, 40, 400);
    stopMove(200);
}

void pr() {
    arcEnc(50, -50, 100, 40, 400);
    stopMove(100);
    smartTurnRight_angle(50, 60, 40);
    lineFollowCross(40, 100, 1);
    lineFollowEncoder(100, 100, 100, 300);
    lineFollowCross(100, 50, 1);
    arcAngle(-50, 0, -100, -50, 90);
    arcEnc(-50, 50, 100, 50, 100);
    changePosGrabberC(60, grabberC.maxUpWithoutShip);
    stopMove(500);
    arcEnc(50, -50, 100, 30, 500);
    stopMove(150);

    arcAngle(40, 40, 100, 40, 180);
    changePosGrabberC(100, grabberC.maxDown);
    stopMove(650);
    changePosGrabberD(60, grabberD.openMax);
    stopMove(200);
    changePosGrabberC(60, grabberC.maxUpWithoutShip);
    arcEnc(50, -50, 50, 50, 225);
    stopMove(100);
    smartTurnLeft_angle(50, 100, 50);
    changePosGrabberD(60, grabberD.openMin);
    lineFollowCross(70, 70, 1);
    arcAngle(-70, -70, -70, -70, 90);
    smartTurnRight_angle(70, 100, 100);
    lineFollowCross(100, 40, 1);
    changePosGrabberC(60, grabberC.upForDrop - 50);
    stopMove(250);
    if (posShip == 1) {
        arcAngle(-50, -50, -50, -50, 90);
        stopMove(250);
        arcEnc(-40, 40, 40, 40, 250);
        changePosGrabberD(60, grabberD.close);
        stopMove(300);
        changePosGrabberC(100, grabberC.upForDrop);
        arcEnc(40, -40, -40, -40, 250);
        stopMove(300);
        arcAngle(50, 50, 50, 50, 90);
        stopMove(250);
    } else {
        arcEnc(-50, 0, -100, -50, 360);
        arcEnc(-50, 50, 100, 30, 150);
        changePosGrabberD(60, grabberD.close);
        stopMove(300);
        changePosGrabberC(100, grabberC.upForDrop);
        arcEnc(50, -50, 100, 50, 150);
         arcEnc(50, 0, 100, 50, 360);
         stopMove(250);
    }
    changePosGrabberC(100, grabberC.maxDown);
    arcEnc(0, 50, 100, 50, 410);
    arcEnc(-40, 40, 40, 40, 70);
    changePosGrabberD(100, grabberD.openMin);
    stopMove(200);
    changePosGrabberC(100, grabberC.maxUpWithoutShip);
    stopMove(100)
    arcEnc(40, -40, 40, 40, 70);
    arcEnc(0, -50, -100, -50, 410);
    stopMove(200);
    arcAngle(50, 50, 100, 50, 180);
    stopMove(250);
}

void tk() {
    lineFollowCross(50, 100, 2);
    reactiveTurnLeft();


    setDefaultLineGreyCross();
    lineFollowEncoder(100, 100, 30, 450);
    lineFollowCross(30, 20, 1);

    stopMove(200);
    changePosGrabberC(30, grabberC.maxDown);
    arcEnc(30, -30, 100, 25, 190);
    stopMove(300);
    arcEnc(30, 30, 100, 30, 35);
    stopMove(200);
    changePosGrabberD(100, grabberD.openMin);
    stopMove(200);
    arcEnc(-30, 30, 100, 30, 130);
    changePosGrabberD(100, grabberD.close);
    arcEnc(-30, 30, 30, 30, 30);
    stopMove(200);
    // changePosGrabberC(60, grabberC.maxUpWithoutShip);
    arcEnc(30, -30, 100, 30, 160);
    stopMove(200);

    arcEnc(-30, -30, -100, -30, 70);
    stopMove(300);
    changePosGrabberD(100, grabberD.openMin);
    stopMove(200);
    arcEnc(-30, 30, 100, 30, 130);
    changePosGrabberD(100, grabberD.close);
    arcEnc(-30, 30, 30, 30, 30);
    stopMove(200);
    changePosGrabberC(60, grabberC.maxUpWithoutShip);
    arcEnc(30, -30, 100, 30, 160);
    smartTurnRight_angle(60, 100, 80, 170);
    setDefaultLine();
    lineFollowCross(80, 100, 1);
    reactiveTurnLeft();
    lineFollowCross(100, 100, 1);
    reactiveTurnRight();
    lineFollowEncoder(100, 100, 30, 440);
    lineFollowEncoder(30, 30, 30, 100);
    stopMove(200);
    changePosGrabberC(100, grabberC.maxUp);
    stopMove(250);
    arcEnc(40, -40, 100, 60, 600);
    stopMove(100);
    smartTurnRight_angle(50, 100, 80);
    lineFollowCross(80, 100, 2);
    reactiveTurnLeft();
    lineFollowEncoder(100, 100, 100, 400);
    lineFollowCross(100, 20, 1);
    changePosGrabberC(60, grabberC.upForDrop);
    stopMove(200);

    arcEnc(30, -30, 30, 30, 25);
    stopMove(450);
    changePosGrabberD(100, grabberD.openMin);
    stopMove(200);
    changePosGrabberC(100, grabberC.maxUpWithoutShip);
    stopMove(200);
}

void huyy() {
    arcEnc(40, -40, 40, 40, 100);
    smartTurnLeft_angle(50, 100, 60);
    lineFollowCross(60, 100, 1);
    changePosGrabberC(50, grabberC.maxUpWithoutShip);
    setDefaultLineGreyCross();
    lineFollowEncoder(100, 100, 30, 550);
    lineFollowCross(30, 25, 1);
    stopMove(150);
    readingElements();
    getElements_forhuy(3, 3, 2);
    changePosGrabberC(50, grabberC.maxUpWithoutShip);
    setDefaultLine();
    lineFollowCross(80, 100, 1);
    reactiveTurnLeft();

}

void pol() {
    lineFollowCross(100, 100, 1);
    lineFollowEncoder(100, 100, 30, 710);
    lineFollowEncoder(30, 30, 30, 80);
    stopMove(200);
    changePosGrabberD(100, grabberD.openMax);
    if (posShip == 0) {
        arcAngle(30, 30, 60, 30, 80);
        arcAngle(30, 30, 30, 30, 10);
        stopMove(200);
        arcEnc(-30, 30, 30, 30, 50);
        stopMove(200);
        changePosGrabberC(70, grabberC.maxDown);
        stopMove(600);
        changePosGrabberD(100, grabberD.close);
        stopMove(200);
        changePosGrabberC(70, grabberC.upForDrop);
        stopMove(200);
        arcEnc(-30, 30, 30, 30, 50);
        stopMove(200);
        arcAngle(30, 30, 60, 30, 170);
        arcAngle(30, 30, 30, 30, 12);
        stopMove(200);
        arcEnc(-30, 30, 30, 30, 170);
        changePosGrabberC(70, grabberC.maxDown);
        stopMove(400);
        changePosGrabberD(100, grabberD.openMin);
        stopMove(200);
        changePosGrabberC(100, grabberC.maxUpWithoutShip);
        stopMove(300);
        arcEnc(30, -30, 100, 30, 800);
        stopMove(200);
    } else {
        arcAngle(-30, -30, -60, -30, 80);
        arcAngle(-30, -30, -30, -30, 10);
        stopMove(200);
        arcEnc(-30, 30, 30, 30, 50);
        stopMove(200);
        changePosGrabberC(70, grabberC.maxDown);
        stopMove(600);
        changePosGrabberD(100, grabberD.close);
        stopMove(200);
        changePosGrabberC(70, grabberC.upForDrop);
        stopMove(200);
        arcEnc(-30, 30, 30, 30, 50);
        stopMove(200);
        arcAngle(30, 30, 60, 30, 170);
        arcAngle(30, 30, 30, 30, 12);
        stopMove(200);
        arcEnc(-30, 30, 30, 30, 170);
        changePosGrabberC(70, grabberC.maxDown);
        stopMove(400);
        changePosGrabberD(100, grabberD.openMin);
        stopMove(200);
        changePosGrabberC(100, grabberC.maxUpWithoutShip);
        stopMove(300);
        arcEnc(30, -30, 100, 30, 800);
        stopMove(200);
    }
}

void getElements_forhuy(short firstColor, short secondColor, short amount=2, short finalPos=0, short getLast=0){
    short turnsEncElements[4] = {70, 25, -25, -70};
    short degreesElements[4] = {130, 100, 100, 130};
    bool markersFound[2] = {false, false};
    short nowPosition = 0;
    short indexesNeed[2] = {0, 1};
    if (getLast){
    	for(short i = 0; i < 4; i++){
    		if ((!gotElements[i]) && (!markersFound[0])){
    			indexesNeed[0] = i;
    			gotElements[i] = 1;
    			markersFound[0] = true;
    		}
    		else if ((!gotElements[i]) && (!markersFound[1])){
    			indexesNeed[1] = i;
    			gotElements[i] = 1;
    			markersFound[1] = true;
    		}
    	}
    }
    else{
	    for (short i = 0; i < 4; i++){
	        if ((firstColor == elementsColors[i]) && (!markersFound[0])){
	            markersFound[0] = true;
	            indexesNeed[0] = i;
	        }
	        else if ((secondColor == elementsColors[i]) && (!markersFound[1])){
	            markersFound[1] = true;
	            indexesNeed[1] = i;
	        }
	    }
	}

    gotElements[indexesNeed[0]] = 1;
    gotElements[indexesNeed[1]] = 1;

    for (short i = 0; i < amount; i++){
        short angle = turnsEncElements[indexesNeed[i]] - nowPosition;
        short way = sgn(angle);
        arcEnc(way * 20, way * 20, way * 40, way * 20, fabs(angle));


        stopMove(150);
        arcEnc(-25, 25, 25, 25, 20);
        // changePosGrabberD(100, grabberD.openMin);
        changePosGrabberD(100, grabberD.close);
        stopMove(100);
        arcEnc(-25, 25, 40, 25, degreesElements[indexesNeed[i]] - 60);
        changePosGrabberD(100, grabberD.close);
        arcEnc(-25, 25, 25, 25, 40);
        stopMove(150);
        arcEnc(25, -25, 40, 25, degreesElements[indexesNeed[i]] - 20);
        arcEnc(25, -25, 25, 25, 20);
        stopMove(150);
        nowPosition = turnsEncElements[indexesNeed[i]];
        elementsColors[indexesNeed[i]] = -1;
    }

    if (finalPos == 0) {
        short signPos = sgn(nowPosition);
        short angle = angleToEnc(20, 20, 180) - fabs(nowPosition);
        if (signPos > 0){
            smartTurnLeft_enc(40, 80, 60, fabs(angle));
        }
        else{
            smartTurnRight_enc(40, 80, 60, fabs(angle));
        }
    } else {
        short signPos = sgn(nowPosition);
        short angle = fabs(nowPosition);
        if (signPos > 0) {
            arcEnc(-30, -30, -40, -30, fabs(angle));
        } else {
            arcEnc(30, 30, 40, 30, fabs(angle));
        }
    }
}