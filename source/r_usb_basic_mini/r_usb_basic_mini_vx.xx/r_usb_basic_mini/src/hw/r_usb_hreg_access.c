/*
* Copyright (c) 2014(2025) Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_usb_hreg_access.c
 * Description  : USB IP Host control register access code
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 31.11.2018 1.10 Supporting Smart Configurator
 *         : 31.05.2019 1.11 Added support for GNUC and ICCRX.
 *         : 30.06.2020 1.20 Added support for RTOS.
 *         : 20.03.2025 1.31 Changed the disclaimer..
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_mini_if.h"
#include "r_usb_typedef.h"
#include "r_usb_bitdefine.h"
#include "r_usb_reg_access.h"
#include "r_usb_extern.h"

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
/*******************************************************************************
 Macro definitions
 ******************************************************************************/

/*******************************************************************************
 Typedef definitions
 ******************************************************************************/

/*******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

/*******************************************************************************
 Private global variables and functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_rwupe
 Description     : Set the RWUPE-bit specified port's DVSTCTR0 reg-
                 : ister. When host. To allow detection of remote wake-up from 
                 : a USB Function.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_rwupe (void)
{
    USB0.DVSTCTR0.WORD |= USB_RWUPE;
}
/******************************************************************************
 End of function hw_usb_hset_rwupe
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_uact
 Description     : Clear UACT-bit (USB Bus Enable) specified port's DVSTCTR0 
                 : register. When Host, to prohibit output SOF.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_uact (void)
{
    USB0.DVSTCTR0.WORD &= (~USB_UACT);
}
/******************************************************************************
 End of function hw_usb_hclear_uact
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_enb_ovrcre
 Description     : Clear the OVRCRE-bit of the specified port's INTENB1 register,
                 : to prohibit VBUS interrupts.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_enb_ovrcre (void)
{
    USB0.INTENB1.WORD &= (~USB_OVRCRE);
}
/******************************************************************************
 End of function hw_usb_hclear_enb_ovrcre
 ******************************************************************************/
 
/******************************************************************************
 Function Name   : hw_usb_hset_enb_bchge
 Description     : The BCHGE-bit (USB Bus Change Interrupt Enable) is set in the 
                 : specified port's INTENB1 register. This will cause a BCHG 
                 : interrupt when a change of USB bus state has been detected.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_bchge (void)
{
    USB0.INTENB1.WORD |= USB_BCHGE;
}
/******************************************************************************
 End of function hw_usb_hset_enb_bchge
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_enb_bchge
 Description     : The BCHGE-bit (USB Bus Change Interrupt Enable) is cleared in 
                 : the specified port's INTENB1 register.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_enb_bchge (void)
{
    USB0.INTENB1.WORD &= (~USB_BCHGE);
}
/******************************************************************************
 End of function hw_usb_hclear_enb_bchge
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_enb_dtche
 Description     : Enable the specified port's DTCHE-interrupt "Disconnection 
                 : Detection" by setting the DTCHE-bit.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_dtche (void)
{
    USB0.INTENB1.WORD |= USB_DTCHE;
}
/******************************************************************************
 End of function hw_usb_hset_enb_dtche
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_enb_dtche
 Description     : Disable the specified port's DTCHE-interrupt "Disconnection 
                 : Detection" by clearing the DTCHE-bit.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_enb_dtche (void)
{
    USB0.INTENB1.WORD &= (~USB_DTCHE);
}
/******************************************************************************
 End of function hw_usb_hclear_enb_dtche
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_enb_attche
 Description     : Disable the specified port's ATTCHE-interrupt "Disconnection 
                 : Detection" by clearing the ATTCHE-bit.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_enb_attche (void)
{
    USB0.INTENB1.WORD &= (~USB_ATTCHE);
}
/******************************************************************************
 End of function hw_usb_hclear_enb_attche
 ******************************************************************************/
 
/******************************************************************************
 Function Name   : hw_usb_hset_enb_signe
 Description     : Enable the SIGNE-interrupt "Setup Transaction
                 : Error" by setting the SIGNE-bit.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_signe (void)
{
    USB0.INTENB1.WORD |= USB_SIGNE;
}
/******************************************************************************
 End of function hw_usb_hset_enb_signe
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_enb_sacke
 Description     : Enable the SACKE-interrupt "Setup Transaction 
                 : Normal Response" by setting the SACKE-bit.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_sacke (void)
{
    USB0.INTENB1.WORD |= USB_SACKE;
}
/******************************************************************************
 End of function hw_usb_hset_enb_sacke
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_enb_pddetinte
 Description     : Enable the PDDETINT-interrupt "Connection Detection for 
                 : Battery Charging Supporting Device" by setting 
                 : the PDDETINTE-bit.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_pddetinte (void)
{
    USB0.INTENB1.WORD |= USB_PDDETINTE;
}
/******************************************************************************
 End of function hw_usb_hset_enb_pddetinte
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_sts_ovrcr
 Description     : Clear the specified port's OVRCR-bit; "Overcurrent 
                 : Input Change Interrupt Status".
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_ovrcr (void)
{
    USB0.INTSTS1.WORD = (uint16_t) ((~USB_OVRCR) & USB_INTSTS1_MASK);
}
/******************************************************************************
 End of function hw_usb_hclear_sts_ovrcr
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_sts_bchg
 Description     : Clear the specified port's BCHG-bit; "USB Bus Change Interrupt 
                 : Status".
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_bchg (void)
{
    USB0.INTSTS1.WORD = (uint16_t) ((~USB_BCHG) & USB_INTSTS1_MASK);
}
/******************************************************************************
 End of function hw_usb_hclear_sts_bchg
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_sts_dtch
 Description     : Clear the specified port's DTCH-bit; "USB Disconnection Detec-
                 : tion Interrupt Status".
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_dtch (void)
{
    USB0.INTSTS1.WORD = (uint16_t) ((~USB_DTCH) & USB_INTSTS1_MASK);
}
/******************************************************************************
 End of function hw_usb_hclear_sts_dtch
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_sts_attch
 Description     : Clear the specified port's ATTCH-bit; "ATTCH Interrupt Status".
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_attch (void)
{
    USB0.INTSTS1.WORD = (uint16_t) ((~USB_ATTCH) & USB_INTSTS1_MASK);
}
/******************************************************************************
 End of function hw_usb_hclear_sts_attch
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_sts_sign
 Description     : Clear the SIGN-bit; "Setup Transaction Error
                 : Interrupt Status".
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_sign (void)
{
    USB0.INTSTS1.WORD = (uint16_t) ((~USB_SIGN) & USB_INTSTS1_MASK);
}
/******************************************************************************
 End of function hw_usb_hclear_sts_sign
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_sts_sack
 Description     : Clear the SACK-bit; "Setup Transaction Normal
                 : Response Interrupt Status".
                 : Interrupt Status".
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_sack (void)
{
    USB0.INTSTS1.WORD = (uint16_t) ((~USB_SACK) & USB_INTSTS1_MASK);
}
/******************************************************************************
 End of function hw_usb_hclear_sts_sack
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_sts_pddetint
 Description     : Clear the PDDETINT-bit; "
                 : ".
                 : Interrupt Status".
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_pddetint (void)
{
    USB0.INTSTS1.WORD = (uint16_t) ((~USB_PDDETINT) & USB_INTSTS1_MASK);
}
/******************************************************************************
 End of function hw_usb_hclear_sts_pddetint
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hwrite_usbreq
 Description     : Write bRequest and bmRequestType to USBREQ register.
                 : When Host, the values of bRequest and bmRequestType 
                 : to be transmitted are written. (When Function, the received 
                 : values of bRequest and bmRequestType are stored in USBREQ).
 Arguments       : uint16_t  data   : Setting value
 Return value    : none
 ******************************************************************************/
void hw_usb_hwrite_usbreq (uint16_t data)
{
    USB0.USBREQ.WORD = data;
}
/******************************************************************************
 End of function hw_usb_hwrite_usbreq
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_usbval
 Description     : Write the specified 'wValue' to USBVAL register,
                 : to write the USB request. When Host, the value of 
                 : wValue to be transmitted is set. (When Function, the value of 
                 : wValue that has been received is stored in USBREQ.)
 Arguments       : uint16_t  data   : Setting value
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_usbval (uint16_t data)
{
    USB0.USBVAL = data;
}
/******************************************************************************
 End of function hw_usb_hset_usbval
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_usbindx
 Description     : Write the specified 'wIndex', the USB request, to USBINDX
                 : register, for host setup requests for control 
                 : transfers.
 Arguments       : uint16_t  data   : Setting value
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_usbindx (uint16_t data)
{
    USB0.USBINDX = data;
}
/******************************************************************************
 End of function hw_usb_hset_usbindx
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_usbleng
 Description     : Write the specified 'wLength' value to USBINDX register, 
                 : for host setup requests for control.
 Arguments       : uint16_t  data   : Setting value
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_usbleng (uint16_t data)
{
    USB0.USBLENG = data;
}
/******************************************************************************
 End of function hw_usb_hset_usbleng
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hwrite_dcpctr
 Description     : Write the specified data value to the DCPCTR register.
 Arguments       : uint16_t  data   : Setting value
 Return value    : none
 ******************************************************************************/
void hw_usb_hwrite_dcpctr (uint16_t data)
{
    USB0.DCPCTR.WORD = data;
}
/******************************************************************************
 End of function hw_usb_hwrite_dcpctr
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_sureq
 Description     : Set te SUREQ-bit in the DCPCTR register 
                 : (Set SETUP packet send when HostController function is selected)
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_sureq (void)
{
    USB0.DCPCTR.WORD |= USB_SUREQ;
}
/******************************************************************************
 End of function hw_usb_hset_sureq
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hread_devadd
 Description     : Return the DEVADD register value for the specified USB device 
                 ; address.
 Arguments       : uint16_t  devsel : USB device address value 
 Return value    : DEVADDx content
 ******************************************************************************/
uint16_t hw_usb_hread_devadd (uint16_t devsel)
{
    R_BSP_VOLATILE_EVENACCESS uint16_t *preg;
    uint16_t return_value;
    uint16_t devadr;

    devadr = devsel >> USB_DEVADDRBIT;
    if (devadr > USB_MAXDEVADDR)
    {
        return_value = USB_ERROR;
    }
    else
    {
        preg = (uint16_t *) &(USB0.DEVADD0) + devadr;
        return_value = ((*preg) & USB_USBSPD);
    }
    return return_value;
}
/******************************************************************************
 End of function hw_usb_hread_devadd
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_usbspd
 Description     : Set the DEVADD register's USBSPD for the specified device add-
                 : ress.
 Arguments       : uint16_t  devsel : USB device address value 
                 : uint16_t  data   : The value to write.
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_usbspd (uint16_t devsel, uint8_t data)
{
    R_BSP_VOLATILE_EVENACCESS uint16_t *preg;
    uint16_t devadr;

    devadr = devsel >> USB_DEVADDRBIT;

    preg = (uint16_t *) &(USB0.DEVADD0) + devadr;

    (*preg) &= (~USB_USBSPD);
    (*preg) |= data;
}
/******************************************************************************
 End of function hw_usb_hset_usbspd
 ******************************************************************************/

#if USB_CFG_BC == USB_CFG_ENABLE
/******************************************************************************
 Function Name   : hw_usb_hset_dcpmode
 Description     : Set DCPMODE bit.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_dcpmode (void)
{
    USB0.USBBCCTRL0.WORD |= USB_DCPMODE;
}
/******************************************************************************
 End of function hw_usb_hset_dcpmode
 ******************************************************************************/
#endif /* USB_CFG_BC == USB_CFG_ENABLE */

/******************************************************************************
 Function Name   : hw_usb_hmodule_init
 Description     : USB module initialization for USB Host mode
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hmodule_init (void)
{
    uint16_t sts;

    USB0.SYSCFG.WORD |= USB_SCKE;
    /* WAIT_LOOP */
    while ( USB_SCKE != (USB0.SYSCFG.WORD & USB_SCKE))
    {
        /* none */
    }

    USB0.SYSCFG.WORD |= USB_DCFM;

    USB0.SYSCFG.WORD |= USB_DRPD;

    sts = usb_chattaring((uint16_t *) &USB0.SYSSTS0.WORD);

    USB0.SYSCFG.WORD |= USB_USBE;

    USB0.CFIFOSEL.WORD  = USB_MBW_16;
    USB0.D0FIFOSEL.WORD = USB_MBW_16;
    USB0.D1FIFOSEL.WORD = USB_MBW_16;

#if USB_CFG_ENDIAN == USB_CFG_BIG
    USB0.CFIFOSEL.WORD |= USB_BIGEND;
    USB0.D0FIFOSEL.WORD |= USB_BIGEND;
    USB0.D1FIFOSEL.WORD |= USB_BIGEND;

#endif  /* USB_CFG_ENDIAN == USB_CFG_BIG */

    switch (sts)
    {
        case USB_FS_JSTS : /* USB device already connected */
        case USB_LS_JSTS :
            USB0.DVSTCTR0.WORD |= USB_USBRST;
            usb_cpu_delay_xms((uint16_t) 50); /* Need to wait greater equal 10ms in USB spec */
            USB0.DVSTCTR0.WORD &= (~USB_USBRST);
            /* WAIT_LOOP */
            while ( USB_HSPROC == (USB0.DVSTCTR0.WORD & USB_HSPROC))
            {
                /* HSPROC = 0100b */
            }

            if ( USB_LSMODE == (USB0.DVSTCTR0.WORD & USB_RHST))
            {
                USB0.SOFCFG.WORD |= USB_TRNENSEL;
            }

            USB0.DVSTCTR0.WORD |= USB_UACT;
        break;

        case USB_SE0 : /* USB device no connected */
            USB0.INTENB1.WORD = USB_ATTCH;
        break;

        default :
        break;
    }
    USB0.INTSTS1.WORD &= ((~USB_OVRCRE) & USB_INTSTS1_MASK);
    USB0.INTENB0.WORD = ((USB_BEMPE | USB_NRDYE) | USB_BRDYE);
    USB0.INTENB1.WORD = (USB_OVRCRE | USB_ATTCH);
}
/******************************************************************************
 End of function hw_usb_hmodule_init
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_trnensel
 Description     : When host, set the TRNENSEL-bit; "Transac-
                 : tion-Enabled Time Select" for low-speed USB communication.
                 : This bit should be set to 0 if USB Function.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_trnensel (void)
{
    USB0.SOFCFG.WORD |= USB_TRNENSEL;
}
/******************************************************************************
 End of function hw_usb_hset_trnensel
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_trnensel
 Description     : When host, set the TRNENSEL-bit; "Transac-
                 : tion-Enabled Time Select" for low-speed USB communication.
                 : This bit should be set to 0 if USB Function.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_trnensel (void)
{
    USB0.SOFCFG.WORD &= (~USB_TRNENSEL);
} /* End of function hw_usb_hclear_trnensel */

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 End of file
 ******************************************************************************/
