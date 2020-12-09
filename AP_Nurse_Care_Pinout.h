#ifndef AP_Nurse_Home_Pinout_h
#define AP_Nurse_Home_Pinout_h

/** AP Nurse Home edition sensor node pinout
 * 
 * @note version 1.0
 */

/** Communication Interfaces pinout
 */
#define I2C_SCL     (5)
#define I2C_SDA     (4)

/** Node sensor pinout  
 */
#define NOISE_PIN   (A0) //KY038
#define PIR_PIN     (0) //SR505
#define GAS_PIN     (0)
#define SMOKE_PIN   (36)
#define LIGHT_PIN   (36)
#define FSR_PIN     (0)

/** ADC extender channels 
 */
#define GAS     (0)
#define SMOKE   (1)
#define LIGHT   (2)
#define FSR     (3)



#endif