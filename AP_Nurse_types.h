#ifndef AP_Nurse_types_h
#define AP_Nurse_types_h

/** Custom print pattern
 * 
 *  @note 8c for each b of a uint8_t
 */ 
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"

/** Binary print format macro
 * 
 *  @returns 8b long binary string
 */ 
#define BYTE_TO_BINARY(byte)  \
(byte & 0x80 ? '1' : '0'), \
(byte & 0x40 ? '1' : '0'), \
(byte & 0x20 ? '1' : '0'), \
(byte & 0x10 ? '1' : '0'), \
(byte & 0x08 ? '1' : '0'), \
(byte & 0x04 ? '1' : '0'), \
(byte & 0x02 ? '1' : '0'), \
(byte & 0x01 ? '1' : '0')

/** BME280 Configuration
 */
#define BME280_ADDR         (0x77) 
#define SEALEVELPRESSURe    (1013.25)

/** ADC Extender I2C address
 */
#define EXTENDER_ADDR   (0x48)

/** AP Alert macros
 */
#define ENABLE      1
#define DISABLE     0

/** AP Nurse Alert type
 * 
 *  @note each alert uses a dedicated bit of the status code allowing multiple simultanious alert triggers
 */
#ifndef ap_alert_type_enum
#define ap_alert_type_enum
typedef enum ap_alert{
    STATUS_OK = 0,      
    MOTION_ALERT = 1,       //0b00000001 LSB
    NOISE_ALERT = 2,        //0b00000010 LSB
    SMOKE_ALERT = 4,        //0b00000100 LSB
    GAS_ALERT = 8,          //0b00001000 LSB
    LIGHT_ALERT = 16,       //0b00010000 LSB
    PRESSURE_ALERT = 32,    //0b00100000 LSB
    TEMPERATURE_ALERT = 64, //0b01000000 LSB
    HUMIDITY_ALERT = 128,   //0b10000000 LSB
    TIMER1_ARMED = 256,     //0b00000001 MSB
    STUCK_ALERT = 512,      //0b00000010 MSB
    GENERAL_ALERT = -1000,
    I2C_NO_DATA = -1001
}status_t;
#endif

/** AP Nurse Alert Level type
 */
#ifndef ap_alert_level_enum
#define ap_alert_level_enum
typedef enum ap_alert_level{
    NO_ALERT = 0,
    ABNORMAL = 1,
    CRITICAL = 2
}level_t;
#endif

/** AP Nurse sensor node data structure
 */
#ifndef ap_sensor_node_struct
#define ap_sensor_node_struct
typedef struct ap_sensor_node{
    int lastAlert;
    bool lastMotion = false;
    unsigned long lastEcheck;
    union{
        uint8_t lastVal[4];
        struct{
            uint8_t lastNoise, lastSmoke, lastGas, lastLight;
            float  lastPressure, lastTemperature, lastHumidity, lastAPressure;
        };
    };
    bool isTimer_a = false;
    long timerStart;
    bool isMotionCheck_n = true;
}ap_node_t;
#endif

/** AP Nurse sensor node alert threshold structure
 */
#ifndef ap_node_threshold_type
#define ap_node_threshold_type
typedef union ap_node_thresholds{
    uint8_t TH[8];
    struct{
        uint8_t noiseTH, smokeTH, gasTH, lightTH, pressureTH, tempTH, humTH, ApressureTH;
    };
}ap_threshold_t;
#endif

/** AP Nurse config structure
 */
#ifndef ap_node_conf_struct
#define ap_node_conf_struct
typedef struct ap_node_config{
float noiseTH;
uint8_t smokeTH;
uint8_t gasTH;
uint8_t lightTH;
uint8_t pressureTH;
float tempTH;
float humTH;
bool enable_pir, enable_noise, enable_bme, enable_smoke, enable_light, enable_fsr;
}ap_config_t;
#endif

#endif
