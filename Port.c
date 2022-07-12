 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Shady Ali
 ******************************************************************************/
#include "Port.h"
#include "tm4c123gh6pm_registers.h"
#include "Port_Regs.h"


#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

/* Global Pointer to hold the Address of the Configuration Pointer */
STATIC const Port_PinConfig * Port_ConfPtr = NULL_PTR;

/* global variable to hold the Status of the Port Driver */
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/* point to the required Port Registers base address */
volatile uint32 * Port_addressPtr = NULL_PTR;

/* saving initial direction of the port pins to be used at Port_RefreshPortDirection */
volatile Port_PinDirectionType Port_initialDirection[PORT_CONFIGURED_PINS];

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): - ConfigPtr : Pointer to configuration set.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pins configuration:
*              - Setup the pins Direction
*              - Provide initial value for o/p pin
*              - Setup the internal resistor for i/p pins
*              - Setup the Pins Mode
*              - Setup the Changeability of pin's Direction
*              - Setup the Changeability of pin's Mode
*************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr )
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
		     PORT_E_PARAM_CONFIG);
	}
	else
#endif
        {
  uint8 index = 0;    /* index to to access the port pins  */
  volatile uint32 delay = 0;
  for(index=0 ; index < TM4C123GH6PM_pinNums ; index++)
  {
	    switch(ConfigPtr->Port_Pins[index].port_num)
	    {
	        case  0: Port_addressPtr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
	        	break;
	        case  1: Port_addressPtr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
	        	break;
	        case  2: Port_addressPtr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
	        	break;
	        case  3: Port_addressPtr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
	        	break;
	        case  4: Port_addressPtr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
	        	break;
	        case  5: Port_addressPtr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
	        	break;
	    }

	    /* Enable clock for PORT and allow time for clock to start*/
	    SYSCTL_REGCGC2_REG |= (1<<ConfigPtr->Port_Pins[index].port_num);
	    delay = SYSCTL_REGCGC2_REG;

	    /* Unlock the commit register for the pins PF0 , PD7 */
	    if( (ConfigPtr->Port_Pins[index].port_num == Port_portC) && (ConfigPtr->Port_Pins[index].pin_num <= Pin3 ) )
	    {
	      continue;                     /* From PC0 to PC3 are JTAG pins which are not allowed to be used */
	    }
	    /* check if the pin one of: PD7 or PF0 */
	    else if(((ConfigPtr->Port_Pins[index].port_num == Port_portD) && (ConfigPtr->Port_Pins[index].pin_num == Pin7))
	            || ((ConfigPtr->Port_Pins[index].port_num == Port_portF) && (ConfigPtr->Port_Pins[index].pin_num == Pin0)) )
	    {
	    	/* Unlock the GPIOCR register */
	       *(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;
	       /* Set the corresponding bit in GPIOCR register to allow changes for this pin */
	        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_COMMIT_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);
	    }
	    else
	    {
	        /* Do Nothing ... No need to unlock the commit register for this pin */
	    }

	    /* Setting up the Pin Mode */
	    /* First Check if it's Analog Mode */
	    if( ConfigPtr->Port_Pins[index].pin_modeNum == PortConf_PinMode_Analog )
	    {
	      /*Clear the corresponding bit in GPIODEN register because it's Analog Mode */
	      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);
	      /*Set the corresponding bit in GPIOAMSEL register which is responsible foR Analog Mode*/
	      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);
	      /*Set the corresponding bit in GPIOAFSEL register to enable the Alternative Function */
	      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);
	    }
	    /* The Mode is not Analog So it is Digital */
	    else
	    {
	      /*Set the corresponding bit in GPIODEN register to enable Digital */
	      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);
	      /*Clear the corresponding bit in GPIOAMSEL register to disable the Analog Mode*/
	      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);
	      /* Check for the Mode if it is GPIO then the Alternative function wont be Enabled */
	      if(ConfigPtr->Port_Pins[index].pin_modeNum == PortConf_PinMode_GPIO )
	      {
	        /*clear the corresponding bit in GPIOAFSEL register to disable Alternative Function */
	        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);
	        /* Clear the PMCx bits  */
	        *(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr->Port_Pins[index].pin_num * 4));
	      }
	      /* any other mode except GPIO mode in the Digital Mode Needs to enable the Alternative Function */
	      else
	      {
	        /*Set the corresponding bit in GPIOAFSEL register to enable the Alternative Function */
	        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);
	        /* Set the PMCx bits for the pin by entering the Mode Number */
	        /* First Clear The Corresponding Bits then Enter the Mode Number */
	        *(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr->Port_Pins[index].pin_num * 4));
	        *(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_CTL_REG_OFFSET) |= ((0x0000000F & ConfigPtr->Port_Pins[index].pin_modeNum) << (ConfigPtr->Port_Pins[index].pin_num * 4));
	      }
	    }
	    /* Setting Up the Pin Direction */

	    /* the Pin Direction Is Output */
	    if((ConfigPtr->Port_Pins[index].pin_direction) == OUTPUT)
	    {
	        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_DIR_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

	        if(ConfigPtr->Port_Pins[index].pin_initial_value == STD_HIGH)
	        {
	            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_DATA_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
	        }
	        else
	        {
	           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_DATA_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
	        }

	    /* store the Initial Direction */
	    Port_initialDirection[index] = ConfigPtr->Port_Pins[index].pin_direction;
	    }
	    /* the Pin Direction Is Input */
	    else if((ConfigPtr->Port_Pins[index].pin_direction) == INPUT)
	    {
	        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_DIR_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);   /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
	        /* the internal resistor is PullUp */
	        if(ConfigPtr->Port_Pins[index].pin_resistor == PULL_UP)
	        {
	           SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
	           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);
	        }
	        /* the internal resistor is PullUp */
	        else if(ConfigPtr->Port_Pins[index].pin_resistor == PULL_DOWN)
	        {
	          SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);   /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
	          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);
	        }
	        else
	        {
	         CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
	         CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr->Port_Pins[index].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
	        }

	    }
	    else
	    {
	        /* Do Nothing */
	    }
  }
  /* Set the Module Status to be Initialized */
   Port_Status = PORT_INITIALIZED;
   /* Store the Address of the Configuration Pointer to be used by the other Module Functions */
   Port_ConfPtr = ConfigPtr->Port_Pins;
        }
}

/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): - Pin: Port Pin ID number.
*                  - Direction: Port Pin Direction.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: set the port pin direction during runtime.
************************************************************************************/
/* Check if the Function API is Enabled */
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{
	/* Local Variable to hold the Status of the Error */
  boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  if (PORT_NOT_INITIALIZED == Port_Status)
  {
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		     PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
    error = TRUE;
  }
  else
  {
      /* Do Nothing */
  }
  if (TM4C123GH6PM_pinNums <= Pin)
  {
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		     PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
    error = TRUE;
  }
  else
  {
      /* Do Nothing */
  }
   if (Port_ConfPtr[Pin].direction_changeability == DIR_NON_CHANGEABLE)
  {
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		     PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
    error = TRUE;
  }
  else
  {
      /* Do Nothing */
  }
#endif
   /* if there is no errors continue */
  if(FALSE == error)
  {
	/* Conditions to determine the Port Address of the Pin */
	if ((Pin == PortConf_LED1_CHANNEL_ID_INDEX) || (Pin == PortConf_SW1_CHANNEL_ID_INDEX))
	{
	      Port_addressPtr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
	}
	else if ((Pin > PortConf_SW1_CHANNEL_ID_INDEX) && (Pin <= PortB_Pin0_INDEX))
    {
      Port_addressPtr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
    }
    else if ((Pin > PortConf_SW1_CHANNEL_ID_INDEX) && (Pin <= PortC_Pin0_INDEX))
    {
      Port_addressPtr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
    }
     else if ((Pin > PortConf_SW1_CHANNEL_ID_INDEX) && (Pin <= PortD_Pin0_INDEX))
    {
      Port_addressPtr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
    }
     else if ((Pin > PortConf_SW1_CHANNEL_ID_INDEX) && (Pin <= PortE_Pin0_INDEX))
    {
      Port_addressPtr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
    }
     else if ((Pin > PortConf_SW1_CHANNEL_ID_INDEX) && (Pin <= PortF_Pin0_INDEX))
    {
      Port_addressPtr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
    }
     else
    {
      Port_addressPtr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
    }
    /* The Pin Direction is Output */
    if(Direction == OUTPUT)
    {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_DIR_REG_OFFSET) , Port_ConfPtr[Pin].pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */


    }
    /* the Pin Direction Is Input */
    else if(Direction == INPUT)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_DIR_REG_OFFSET) , Port_ConfPtr[Pin].pin_num);   /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

    }
    else
    {
        /* Do Nothing */
    }
  }
}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: refresh the direction of all configured ports to the configured direction.
*************************************************************************************/
void Port_RefreshPortDirection( void ){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  if (PORT_NOT_INITIALIZED == Port_Status)
  {
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		     PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
  }
  else
#endif
  {
	  /* Variable to hold the index of the Pins */
    uint8 index=0;
    /* Looping through all the Port Pins */
    for(index=0 ; index < TM4C123GH6PM_pinNums ; index++ )
    {
    	/* Conditions to determine the Port Address of the Pin */
    	if ((index == PortConf_LED1_CHANNEL_ID_INDEX) || (index == PortConf_SW1_CHANNEL_ID_INDEX))
    	{
    	      Port_addressPtr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
    	}
    	else if ((index > PortConf_SW1_CHANNEL_ID_INDEX) && (index <= PortB_Pin0_INDEX))
        {
          Port_addressPtr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
        }
        else if ((index > PortConf_SW1_CHANNEL_ID_INDEX) && (index <= PortC_Pin0_INDEX))
        {
          Port_addressPtr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
        }
         else if ((index > PortConf_SW1_CHANNEL_ID_INDEX) && (index <= PortD_Pin0_INDEX))
        {
          Port_addressPtr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
        }
         else if ((index > PortConf_SW1_CHANNEL_ID_INDEX) && (index <= PortE_Pin0_INDEX))
        {
          Port_addressPtr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        }
         else if ((index > PortConf_SW1_CHANNEL_ID_INDEX) && (index <= PortF_Pin0_INDEX))
        {
          Port_addressPtr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        }
         else
        {
          Port_addressPtr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
        }

    	/* For All Pins configured as changeable during run time Do Nothing */
    	if (Port_ConfPtr[index].direction_changeability == DIR_CHANGEABLE)
		 {
			   continue ;
		 }
		 else if ( Port_initialDirection[index] == INPUT )
		 {
			 /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
			 CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_DIR_REG_OFFSET) , Port_ConfPtr[index].pin_num);
		 }
		 else if ( Port_initialDirection[index] == OUTPUT )
		 {
			 SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_DIR_REG_OFFSET) , Port_ConfPtr[index].pin_num);
		 }
		 else
		 {
		   /* Do Nothing */
		 }
   }
 }
}

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo: Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
*************************************************************************************/
/* Check if the Function API is Enabled */
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
	/* Local Variable to hold the Status of the Error */
  boolean error = FALSE;
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* if the Status of the Module is not initialized Report an Error */
        if (PORT_NOT_INITIALIZED == Port_Status)
        {
          Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
	        	     PORT_GET_VERSION_INFO_SID, PORT_E_UNINIT);
          error = TRUE;
        }
        else
        {
         /* Do Nothing */
        }
	/* if the input pointer is Null pointer Report an Error */
	if(NULL_PTR == versioninfo)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
                 error = TRUE;
	}
	else
        {
           /* Do Nothing */
        }
#endif
	if ( FALSE == error )
        {
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
        else
        {
           /* Do Nothing */
        }
}
#endif


/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): - Pin: Port Pin ID number.
*                  - Mode: New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:set the port pin mode of the referenced pin during runtime.
************************************************************************************/
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{
	/* Local Variable to hold the Status of the Error */
  boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  if (PORT_NOT_INITIALIZED == Port_Status)
  {
	  /* if the Status of the Module is not initialized Report an Error */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		     PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
    error = TRUE;
  }
  else
  {
    /* Do Nothing */
  }
  if (TM4C123GH6PM_pinNums <= Pin)
  {
	  /* check if the Pin index is out of range */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		     PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
    error = TRUE;
  }
  else
  {
    /* Do Nothing */
  }
  /* check if the pin changeability is Not Changeable */
   if (Port_ConfPtr[Pin].direction_changeability == DIR_NON_CHANGEABLE)
  {
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		     PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
    error = TRUE;
  }
  else
  {
    /* Do Nothing */
  }
   /* Check for invalid Modes of the Pin Configuration that can not be changed*/
  if ( (Port_ConfPtr[Pin].pin_modeNum != PortConf_PinMode_Analog) ||
		  ( (Port_ConfPtr[Pin].pin_modeNum > PortConf_PinMode_NUM_9) && (Port_ConfPtr[Pin].pin_modeNum < PortConf_PinMode_NUM_14) ))
  {
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
		     PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
    error = TRUE;
  }
  else
  {
    /* Do Nothing */
  }
#endif
  if(FALSE == error)
  {
		/* Conditions to determine the Port Address of the Pin */
		if ((Pin == PortConf_LED1_CHANNEL_ID_INDEX) || (Pin == PortConf_SW1_CHANNEL_ID_INDEX))
		{
		      Port_addressPtr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		}
		else if ((Pin > PortConf_SW1_CHANNEL_ID_INDEX) && (Pin <= PortB_Pin0_INDEX))
	    {
	      Port_addressPtr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
	    }
	    else if ((Pin > PortConf_SW1_CHANNEL_ID_INDEX) && (Pin <= PortC_Pin0_INDEX))
	    {
	      Port_addressPtr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
	    }
	     else if ((Pin > PortConf_SW1_CHANNEL_ID_INDEX) && (Pin <= PortD_Pin0_INDEX))
	    {
	      Port_addressPtr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
	    }
	     else if ((Pin > PortConf_SW1_CHANNEL_ID_INDEX) && (Pin <= PortE_Pin0_INDEX))
	    {
	      Port_addressPtr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
	    }
	     else if ((Pin > PortConf_SW1_CHANNEL_ID_INDEX) && (Pin <= PortF_Pin0_INDEX))
	    {
	      Port_addressPtr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
	    }
	     else
	    {
	      Port_addressPtr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
	    }

		/* if the required Mode Is Analog */
    if( Mode == PortConf_PinMode_Analog )  /* setup the pin as Analog Pin (ADC)  */
    {
      /*Clear the corresponding bit in GPIODEN register to disable the digital Mode */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_ConfPtr[Pin].pin_num);
      /*Set the corresponding bit in GPIOAMSEL register to enable Analog Mode*/
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_ConfPtr[Pin].pin_num);
      /*Set the corresponding bit in GPIOAFSEL register .. it is not GPIO mode*/
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_ALT_FUNC_REG_OFFSET) , Port_ConfPtr[Pin].pin_num);
    }
    /* if the required Mode is not Analoge then it's Digital */
   else
   {
     /*Set the corresponding bit in GPIODEN register to enable Digital Mode */
     SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_ConfPtr[Pin].pin_num);
     /*Clear the corresponding bit in GPIOAMSEL register to disable Analog Mode*/
     CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_ConfPtr[Pin].pin_num);

     /* in case the required mode is GPIO  */
     if( Mode == PortConf_PinMode_GPIO )
     {
       /*clear the corresponding bit in GPIOAFSEL register to disable the Alternative Function*/
       CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_ALT_FUNC_REG_OFFSET) , Port_ConfPtr[Pin].pin_num);
       /* Clear the PMCx bits corresponding to the pin */
       *(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_ConfPtr[Pin].pin_num * 4));
     }
     /* for other Digital Modes rather than GPIO */
     else
     {
       /*Set the corresponding bit in GPIOAFSEL register to enable the Alternative Function*/
       SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_ALT_FUNC_REG_OFFSET) , Port_ConfPtr[Pin].pin_num);
       /* Set the PMCx bits for the pin by entering the Mode Number */
       /* First Clear The Corresponding Bits then Enter the Mode Number */
       *(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_ConfPtr[Pin].pin_num * 4));
       *(volatile uint32 *)((volatile uint8 *)Port_addressPtr + PORT_CTL_REG_OFFSET) |= ((0x0000000F & Mode ) << (Port_ConfPtr[Pin].pin_num * 4));
     }
   }
  }
  else
  {
    /* Do Nothing */
  }
}













