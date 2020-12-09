#ifndef AP_Nurse_h
#define AP_Nurse_h

#include <Arduino.h>
#include <Wire.h>
#include "AP_Nurse_types.h"
#include "AP_Nurse_Care_Pinout.h"
#include "AP_Nurse_config.h"
#include "Sensor_enable.h"
#include "PCF8591.h"
#include <Adafruit_BME680.h>

class AP_Nurse{
public:
    explicit AP_Nurse();
    uint8_t getLastAlert();
    bool getLastMotion();
    uint8_t getLastNoise();
    uint8_t getLastSmoke();
    uint8_t getLastGas();
    uint8_t getLastLight();
    uint8_t getLastPressure();
    float getLastTemperature();
    float getLastHumidity();
    float getLastAPressure();
    void printData();
    void clearAlert();

protected:
    status_t checkMotion();
    status_t checkNoise();
    status_t checkExtender();
    status_t checkBme();
    status_t checkGas();
    status_t checkLight();
    status_t checkFSR();
    void startTimer();
    void checkTimer();
    void disableTimer();
    void timerISR(void *pArg);

    Adafruit_BME680 bme;

    ap_node_t ap_node;
    ap_threshold_t ap_th;
    ap_config_t ap_config;
};

class AP_Nurse_Universal : public AP_Nurse{
public:
    explicit AP_Nurse_Universal(float noiseTH, float smokeTH, float gasTH, float lightTH, float pressTH, float tempTH) : AP_Nurse() {
        this -> ap_th.noiseTH = noiseTH;
        this -> ap_th.smokeTH = smokeTH;
        this -> ap_th.gasTH = gasTH;
        this -> ap_th.lightTH = lightTH;
        this -> ap_th.pressureTH = pressTH;
        this -> ap_th.tempTH = tempTH;
    }

    explicit AP_Nurse_Universal(ap_config_t config) : AP_Nurse() {
        this -> ap_th.noiseTH = config.noiseTH;
        this -> ap_th.smokeTH = config.smokeTH;
        this -> ap_th.gasTH = config.gasTH;
        this -> ap_th.lightTH = config.lightTH;
        this -> ap_th.pressureTH = config.pressureTH;
        this -> ap_th.tempTH = config.tempTH;

        this -> ap_config = config;
    }
    uint8_t update();
private:
};

void timerISR(int &alert);

#endif