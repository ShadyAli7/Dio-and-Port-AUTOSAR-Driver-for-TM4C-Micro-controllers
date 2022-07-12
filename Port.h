 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Shady Ali
 ******************************************************************************/


#ifndef PORT_H_
#define PORT_H_

/* Id for the company in the AUTOSAR
 * for example Mohamed Tarek's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/* Port Registers for TM4C123GH6PM Microcontroller */
#include "Port_Regs.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/

/* Service ID for PORT INIT */
#define PORT_INIT_SID                        (uint8)0x00

/* Service ID for PORT INIT */
#define PORT_SET_PIN_DIRECTION_SID           (uint8)0x01

/* Service ID for Port_RefreshPortDirection */
#define PORT_REFRESH_PORT_DIRECTION_SID      (uint8)0x02

/* Service ID for Port_GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID            (uint8)0x03

/* Service ID for Port_SetPinMode */
#define PORT_SET_PIN_MODE_SID                (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/

/* DET code to report Invalid Port Pin ID  */
#define PORT_E_PARAM_PIN                       (uint8)0x0A

/* DET code to report Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE          (uint8)0x0B

/* DET code to report API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG                    (uint8)0x0C

/* DET code to report API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_PARAM_INVALID_MODE              (uint8)0x0D

/* DET code to report API Port_SetPinMode service called when mode is unchangeable. */
#define PORT_E_MODE_UNCHANGEABLE               (uint8)0x0E

/* DET code to report API service called without initializing the module */
#define PORT_E_UNINIT                          (uint8)0x0F

/* DET code to report APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER                   (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Declaring new type for Port_PinType to be used as the PORT APIs */
typedef uint8 Port_PinType;

/* Declaring new type for Port_PinModeType to hold Different port pin modes */
typedef uint8 Port_PinModeType;

/* Declaring new type for Port_PortNumType to hold PORT number */
typedef uint8 Port_PortNumType;

/* Declaring new type for Port_PinInitialValue to hold PIN initial value */
typedef uint8 Port_PinInitialValue; /* STD_HIGH , STD_LOW */

/* Description: Enum to hold PIN direction changeability */
typedef enum
{
    DIR_NON_CHANGEABLE,DIR_CHANGEABLE
}Port_PinDirectionChangeability;

/* Description: Enum to hold the PIN mode if it is changeable or not */
typedef enum
{
    NON_CHANGEABLE,CHANGEABLE
}Port_PinModeChangeability;

/* Description: Enum to hold PIN direction */
typedef enum
{
    INPUT,OUTPUT
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_PinInternalResistor;

/* Description: Structure to hold configuration for each individual PIN:
 *	1. the number of port for the pin it's one of: 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin : INPUT or OUTPUT
 *      4. the internal resistor : Disable, Pull up or Pull down
 *      5. the initial  value : HIGH or LOW
 *      6. the pin direction changeability during runtime :  DIR_NON_CHANGEABLE,DIR_CHANGEABLE
 *      7. the pin mode number : 1, 2, 3, 4, 5, 6, 7, 8, 9, 14, 15
 *      8. the pin mode changeability during runtime : NON_CHANGEABLE or CHANGEABLE
 */
typedef struct Port_PinConfig
{
	Port_PortNumType port_num;
    Port_PinType pin_num;
    Port_PinDirectionType pin_direction;
    Port_PinInternalResistor pin_resistor;
    Port_PinInitialValue pin_initial_value;
    Port_PinDirectionChangeability direction_changeability;
    Port_PinModeType pin_modeNum;
    Port_PinModeChangeability mode_changeability;
}Port_PinConfig;

/* Data Structure required for initializing the PORT Driver */
typedef struct Port_ConfigType
{
	Port_PinConfig Port_Pins[TM4C123GH6PM_pinNums];
} Port_ConfigType;


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Description: Function Prototype for Initialization of the Port Driver module */
void Port_Init( const Port_ConfigType* ConfigPtr );

/* Description: Function Prototype to Set the port pin direction during runtime */
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)/* condition to check if the direction Function is enabled */
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif

/* Description: Function Prototype to Refresh port direction */
void Port_RefreshPortDirection( void );

/* Description: Function Prototype to Return the version information of this module */
#if (PORT_VERSION_INFO_API == STD_ON)/* condition to check if the Version Info Function is enabled */
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif

/* Description: Function Prototype to Set the port pin mode */
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern for Post Build structures to be used by other modules */
extern const Port_ConfigType Port_Configuration;




#endif /* PORT_H_ */
