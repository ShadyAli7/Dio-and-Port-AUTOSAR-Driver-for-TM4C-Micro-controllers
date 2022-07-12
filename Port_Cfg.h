 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Shady Ali
 ******************************************************************************/


#ifndef PORT_CFG_H_
#define PORT_CFG_H_


/*
 * SoftWare Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_OFF)

/* Pre-compile option for Port Set Pin Direction API */
#define PORT_SET_PIN_DIRECTION_API           (STD_ON)

/* Number of the configured Port Pins */
#define PORT_CONFIGURED_PINS              (2U)

/* Number of the pins in TM4C123GH6PM*/
#define TM4C123GH6PM_pinNums			  (43U)

/* Definition for Port ID's Numbers  */
#define Port_portA                (Port_PortNumType)0  /* PORT A */
#define Port_portB                (Port_PortNumType)1   /* PORT B */
#define Port_portC                (Port_PortNumType)2   /* PORT C */
#define Port_portD                (Port_PortNumType)3   /* PORT D */
#define Port_portE                (Port_PortNumType)4   /* PORT E */
#define Port_portF                (Port_PortNumType)5   /* PORT F */

/* Default Pin Numbers */
#define Pin0                 (Port_PinType)0 /* Pin 0 */
#define Pin1                 (Port_PinType)1 /* Pin 1 */
#define Pin2                 (Port_PinType)2 /* Pin 2 */
#define Pin3                 (Port_PinType)3 /* Pin 3 */
#define Pin4                 (Port_PinType)4 /* Pin 4 */
#define Pin5                 (Port_PinType)5 /* Pin 5 */
#define Pin6                 (Port_PinType)6 /* Pin 6 */
#define Pin7                 (Port_PinType)7 /* Pin 7 */

/* PORT Default Pin ID's Indexes */
#define PortA_Pin0_INDEX                (uint8)2  /* PA0 */
#define PortA_Pin1_INDEX                (uint8)3  /* PA1 */
#define PortA_Pin2_INDEX                (uint8)4  /* PA2 */
#define PortA_Pin3_INDEX                (uint8)5  /* PA3 */
#define PortA_Pin4_INDEX                (uint8)6  /* PA4 */
#define PortA_Pin5_INDEX                (uint8)7  /* PA5 */
#define PortA_Pin6_INDEX                (uint8)8  /* PA6 */
#define PortA_Pin7_INDEX                (uint8)9  /* PA7 */
#define PortB_Pin0_INDEX                (uint8)10 /* PB0 */
#define PortB_Pin1_INDEX                (uint8)11 /* PB1 */
#define PortB_Pin2_INDEX                (uint8)12 /* PB2 */
#define PortB_Pin3_INDEX                (uint8)13 /* PB3 */
#define PortB_Pin4_INDEX                (uint8)14 /* PB4 */
#define PortB_Pin5_INDEX                (uint8)15 /* PB5 */
#define PortB_Pin6_INDEX                (uint8)16 /* PB6 */
#define PortB_Pin7_INDEX                (uint8)17 /* PB7 */
#define PortC_Pin0_INDEX                (uint8)18 /* PC0 */
#define PortC_Pin1_INDEX                (uint8)19 /* PC1 */
#define PortC_Pin2_INDEX                (uint8)20 /* PC2 */
#define PortC_Pin3_INDEX                (uint8)21 /* PC3 */
#define PortC_Pin4_INDEX                (uint8)22 /* PC4 */
#define PortC_Pin5_INDEX                (uint8)23 /* PC5 */
#define PortC_Pin6_INDEX                (uint8)24 /* PC6 */
#define PortC_Pin7_INDEX                (uint8)25 /* PC7 */
#define PortD_Pin0_INDEX                (uint8)26 /* PD0 */
#define PortD_Pin1_INDEX                (uint8)27 /* PD1 */
#define PortD_Pin2_INDEX                (uint8)28 /* PD2 */
#define PortD_Pin3_INDEX                (uint8)29 /* PD3 */
#define PortD_Pin4_INDEX                (uint8)30 /* PD4 */
#define PortD_Pin5_INDEX                (uint8)31 /* PD5 */
#define PortD_Pin6_INDEX                (uint8)32 /* PD6 */
#define PortD_Pin7_INDEX                (uint8)33 /* PD7 */
#define PortE_Pin0_INDEX                (uint8)34 /* PE0 */
#define PortE_Pin1_INDEX                (uint8)35 /* PE1 */
#define PortE_Pin2_INDEX                (uint8)36 /* PE2 */
#define PortE_Pin3_INDEX                (uint8)37 /* PE3 */
#define PortE_Pin4_INDEX                (uint8)38 /* PE4 */
#define PortE_Pin5_INDEX                (uint8)39 /* PE5 */
#define PortF_Pin0_INDEX                (uint8)40 /* PF0 */
#define PortF_Pin2_INDEX                (uint8)41 /* PPF2 */
#define PortF_Pin3_INDEX                (uint8)42 /* PPF3 */


/* PORT Default Pin Directions */
#define Port_Default_PinDirection                    (Port_PinDirectionType)0 /* The Default is Input  */

/* PORT Default Pin Initial Value */
#define Port_Default_PinInitialValue                    (Port_PinInitialValue)0 /* The Default is Low*/

/* PORT Default Pin Internal resistor */
#define Port_Default_PinResistor                        (Port_PinInternalResistor)0 /* turn off internal resistor by default */

/* PORT Default Pin Direction Changeability */
#define Port_Default_PinDirection_Changeability          (Port_PinDirectionChangeability)1 /* Changeable for default pins   */

/* PORT Default Pin Mode */
#define Port_Default_PinMode                      (Port_PinModeType)0  /* GPIO Mode for Default Pins    */


/* PORT Default Pin Mode Changeable */
#define Port_Default_PinMode_Changeability        (Port_PinModeChangeability)1 /* Changeable for default pins */

/*********** Configured Pins Settings******************/

/* Port Configured Port Number  */
#define PortConf_LED1_Port_Num                (Port_PortNumType)5   /* PORT F */
#define PortConf_SW1_Port_Num                (Port_PortNumType)5   /* PORT F */

/* Port Configured pins number */
#define PortConf_LED1_Pin_Num                 (Port_PinType)1 /* Pin 1 */
#define PortConf_SW1_Pin_Num                 (Port_PinType)4 /* Pin 4 */

/* Channel Index in the array of structures in Port_PBcfg.c */
#define PortConf_LED1_CHANNEL_ID_INDEX        (uint8)0x00
#define PortConf_SW1_CHANNEL_ID_INDEX         (uint8)0x01

/* PORT Configured Pin Directions */
#define PortConf_LED1_PinDirection                    (Port_PinDirectionType)1 /* output pin    */
#define PortConf_SW1_PinDirection                   (Port_PinDirectionType)0 /* input pin  */

/* PORT Configured Pin Initial Value */
#define PortConf_LED1_PinInitialValue                    (Port_PinInitialValue)0 /* low */
#define PortConf_SW1_PinInitialValue                   (Port_PinInitialValue)1 /* high */

/* PORT Configured Pin Internal resistor */
#define PortConf_LED1_PinResistor                        (Port_PinInternalResistor)2 /* Pull Down resistor */
#define PortConf_SW1_PinResistor                     (Port_PinInternalResistor)1 /* Pull Up resistor */

/* PORT Configured Pin Direction Changeability */
#define PortConf_LED1_PinDirection_Changeability               (Port_PinDirectionChangeability)1 /* Changeable     */
#define PortConf_SW1_PinDirection_Changeability                  (Port_PinDirectionChangeability)1 /* Changeable     */

/* PORT Configured Pin Mode in the TM4C123GH6PM Microcontroller */
#define PortConf_LED1_PinMode                      (Port_PinModeType)0  /* GPIO Mode     */
#define PortConf_SW1_PinMode                       (Port_PinModeType)0  /* GPIO Mode */
/* Other Pin Modes Which Can Be Used For other Pins */
#define PortConf_PinMode_GPIO                      (Port_PinModeType)0  /* GPIO Mode     */
/* Analog Mode  dosen't need any Specific number because analog modes don't use GPIOCTL */
#define PortConf_PinMode_Analog                       (Port_PinModeType)33
#define PortConf_PinMode_NUM_1                     (Port_PinModeType)1  /* Mode number 1 */
#define PortConf_PinMode_NUM_2                     (Port_PinModeType)2  /* Mode number 2 */
#define PortConf_PinMode_NUM_3                     (Port_PinModeType)3  /* Mode number 3 */
#define PortConf_PinMode_NUM_4                     (Port_PinModeType)4  /* Mode number 4 */
#define PortConf_PinMode_NUM_5                     (Port_PinModeType)5  /* Mode number 5 */
#define PortConf_PinMode_NUM_6                     (Port_PinModeType)6  /* Mode number 6 */
#define PortConf_PinMode_NUM_7                     (Port_PinModeType)7  /* Mode number 7 */
#define PortConf_PinMode_NUM_8                     (Port_PinModeType)8  /* Mode number 8 */
#define PortConf_PinMode_NUM_9                     (Port_PinModeType)9  /* Mode number 9 */
#define PortConf_PinMode_NUM_14                    (Port_PinModeType)14 /* Mode number 14*/


/* PORT Configured Pin Mode Changeability */
#define PortConf_LED1_PinMode_changeability              (Port_PinModeChangeability)1 /* Changeable  */
#define PortConf_SW1_PinMode_Changeability                (Port_PinModeChangeability)1 /* Changeable  */





#endif /* PORT_CFG_H_ */
