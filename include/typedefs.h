typedef struct {
  tI2CData I2CData;
  ubyte _cmd;
} tHTCS2, *tHTCS2Ptr;

typedef struct {
    tSensors nDeviceIndex;
    tHTCS2 HTStruct;

    int minAmbient;
    int maxAmbient;
    int ambient;
    float normAmbient;

    long rawRed;
    long rawGreen;
    long rawBlue;

    float normRed;
    float normGreen;
    float normBlue;

    float hue;
    float sat;
    float val;

    short minRed;
    short minGreen;
    short minBlue;

    short maxRed;
    short maxGreen;
    short maxBlue;

    short color;
} tCDValues;
