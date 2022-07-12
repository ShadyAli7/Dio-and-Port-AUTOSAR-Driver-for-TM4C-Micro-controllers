 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Shady Ali
 ******************************************************************************/
#include "Port.h"

/*
 * SoftWare Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_PBcfg.c does not match the expected version"
#endif

/* Post Build Array of structures used in Port_Init Function */
const Port_ConfigType Port_Configuration = {

/*********************** Configured Pins *****************/
											/*** LED 1 ***/
								PortConf_LED1_Port_Num,
								PortConf_LED1_Pin_Num,
								PortConf_LED1_PinDirection,
								PortConf_LED1_PinResistor,
								PortConf_LED1_PinInitialValue,
								PortConf_LED1_PinDirection_Changeability,
								PortConf_LED1_PinMode,
								PortConf_LED1_PinMode_changeability,
											/*** SW1 ***/
								PortConf_SW1_Port_Num,
								PortConf_SW1_Pin_Num,
								PortConf_SW1_PinDirection,
								PortConf_SW1_PinResistor,
								PortConf_LED1_PinInitialValue,
								PortConf_SW1_PinDirection_Changeability,
								PortConf_SW1_PinMode,
								PortConf_SW1_PinMode_Changeability,
/************************ Default Configurations *************/
								/************* Port A *****************/
								/* PA0*/
								Port_portA ,
								Pin0,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PA1*/
								Port_portA,
								Pin1,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PA2*/
								Port_portA,
								Pin2,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PA3*/
								Port_portA,
								Pin3,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PA4*/
								Port_portA,
								Pin4,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PA5*/
								Port_portA,
								Pin5,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PA6*/
								Port_portA,
								Pin6,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PA7*/
								Port_portA,
								Pin7,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,
								/****************** Port B *******************/
								/* PB0*/
								Port_portB ,
								Pin0,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PB1*/
								Port_portB ,
								Pin1,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PB2*/
								Port_portB ,
								Pin2,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PB3*/
								Port_portB ,
								Pin3,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PB4*/
								Port_portB ,
								Pin4,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PB5*/
								Port_portB ,
								Pin5,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PB6*/
								Port_portB ,
								Pin6,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PB7*/
								Port_portB ,
								Pin7,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,
								/******************* Port C *********************/
								/* PC0*/
								Port_portC ,
								Pin0,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PC1*/
								Port_portC ,
								Pin1,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PC2*/
								Port_portC ,
								Pin2,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PC3*/
								Port_portC ,
								Pin3,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PC4*/
								Port_portC ,
								Pin4,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PC5*/
								Port_portC ,
								Pin5,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PC6*/
								Port_portC ,
								Pin6,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PC7*/
								Port_portC ,
								Pin7,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,
								/*********************** Port D *******************/
								/* PD0*/
								Port_portD ,
								Pin0,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PD1*/
								Port_portD ,
								Pin1,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PD2*/
								Port_portD ,
								Pin2,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PD3*/
								Port_portD ,
								Pin3,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PD4*/
								Port_portD ,
								Pin4,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PD5*/
								Port_portD ,
								Pin5,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PD6*/
								Port_portD ,
								Pin6,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PD7*/
								Port_portD ,
								Pin7,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,
								/****************** Port E ***************/
								/* PE0*/
								Port_portE ,
								Pin0,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PE1*/
								Port_portE ,
								Pin1,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PE2*/
								Port_portE ,
								Pin2,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PE3*/
								Port_portE ,
								Pin3,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PE4*/
								Port_portE ,
								Pin4,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PE5*/
								Port_portE ,
								Pin5,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,
								/********************* Port F ********************/
								/* PF0*/
								Port_portF ,
								Pin0,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PF2*/
								Port_portF ,
								Pin2,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

								/* PF3*/
								Port_portF ,
								Pin3,
								Port_Default_PinDirection,
								Port_Default_PinResistor,
								Port_Default_PinInitialValue,
								Port_Default_PinDirection_Changeability,
								Port_Default_PinMode,
								Port_Default_PinMode_Changeability,

};
