#ifndef __ROBOTMAP_H__
#define __ROBOTMAP_H__

//
// Solenoid Breakout Ports
//
#define SOL_1                  1
#define SOL_2                  2
#define SOL_3                  3
#define SOL_4                  4
#define SOL_5                  5
#define SOL_6                  6
#define SOL_7                  7
#define SOL_8                  8

//
// Analog Breakout Ports
//
#define AIO_1                  1
#define AIO_2                  2
#define AIO_3                  3
#define AIO_4                  4
#define AIO_5                  5
#define AIO_6                  6
#define AIO_7                  7
#define AIO_8                  8

//
// Digitial Sidecar Ports
//
#define PWM_1                  1
#define PWM_2                  2
#define PWM_3                  3
#define PWM_4                  4
#define PWM_5                  5
#define PWM_6                  6
#define PWM_7                  7
#define PWM_8                  8
#define PWM_9                  9
#define PWM_10                 10

#define DIO_1                  1
#define DIO_2                  2
#define DIO_3                  3
#define DIO_4                  4
#define DIO_5                  5
#define DIO_6                  6
#define DIO_7                  7
#define DIO_8                  8
#define DIO_9                  9
#define DIO_10                 10
#define DIO_11                 11
#define DIO_12                 12
#define DIO_13                 13
#define DIO_14                 14

#define RELAY_1                1
#define RELAY_2                2
#define RELAY_3                3
#define RELAY_4                4
#define RELAY_5                5
#define RELAY_6                6
#define RELAY_7                7
#define RELAY_8                8

//
// Robot Subsystems
//

// Ball Detector -- IR Proximity Detector
#define BALL_DETECTOR_CHANNEL             DIO_5

// Compressor
#define COMPRESSOR_CHANNEL                RELAY_2
#define PRESSURE_SWITCH_CHANNEL           DIO_2

// Gripper
#define GRIPPER_TILT_CAN_ID               63
#define GRIPPER_OPEN_CHANNEL              SOL_6
#define GRIPPER_CLOSE_CHANNEL             SOL_7

// Shooter
#define SHOOTER_UPPER_LEFT_CHANNEL        SOL_1
#define SHOOTER_UPPER_RIGHT_CHANNEL       SOL_2
#define SHOOTER_CENTER_CHANNEL            SOL_3
#define SHOOTER_LOWER_LEFT_CHANNEL        SOL_4
#define SHOOTER_LOWER_RIGHT_CHANNEL       SOL_5

// Passer
#define PASSER_CHANNEL                    SHOOTER_CENTER_CHANNEL

#endif /* __ROBOTMAP_H__ */
