singleline_comment|// include/asm-arm/mach-omap/usb.h
macro_line|#ifndef&t;__ASM_ARCH_OMAP_USB_H
DECL|macro|__ASM_ARCH_OMAP_USB_H
mdefine_line|#define&t;__ASM_ARCH_OMAP_USB_H
macro_line|#include &lt;asm/arch/board.h&gt;
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|macro|OTG_BASE
mdefine_line|#define OTG_BASE&t;&t;&t;0xfffb0400
DECL|macro|UDC_BASE
mdefine_line|#define UDC_BASE&t;&t;&t;0xfffb4000
DECL|macro|OMAP_OHCI_BASE
mdefine_line|#define OMAP_OHCI_BASE&t;&t;&t;0xfffba000
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * OTG and transceiver registers, for OMAPs starting with ARM926&n; */
DECL|macro|OTG_REG32
mdefine_line|#define OTG_REG32(offset)&t;&t;__REG32(OTG_BASE + (offset))
DECL|macro|OTG_REG16
mdefine_line|#define OTG_REG16(offset)&t;&t;__REG16(OTG_BASE + (offset))
DECL|macro|OTG_REV_REG
mdefine_line|#define OTG_REV_REG&t;&t;&t;OTG_REG32(0x00)
DECL|macro|OTG_SYSCON_1_REG
mdefine_line|#define OTG_SYSCON_1_REG&t;&t;OTG_REG32(0x04)
DECL|macro|USB2_TRX_MODE
macro_line|#&t;define&t; USB2_TRX_MODE(w)&t;(((w)&gt;&gt;24)&amp;0x07)
DECL|macro|USB1_TRX_MODE
macro_line|#&t;define&t; USB1_TRX_MODE(w)&t;(((w)&gt;&gt;20)&amp;0x07)
DECL|macro|USB0_TRX_MODE
macro_line|#&t;define&t; USB0_TRX_MODE(w)&t;(((w)&gt;&gt;16)&amp;0x07)
DECL|macro|OTG_IDLE_EN
macro_line|#&t;define&t; OTG_IDLE_EN&t;&t;(1 &lt;&lt; 15)
DECL|macro|HST_IDLE_EN
macro_line|#&t;define&t; HST_IDLE_EN&t;&t;(1 &lt;&lt; 14)
DECL|macro|DEV_IDLE_EN
macro_line|#&t;define&t; DEV_IDLE_EN&t;&t;(1 &lt;&lt; 13)
DECL|macro|OTG_RESET_DONE
macro_line|#&t;define&t; OTG_RESET_DONE&t;&t;(1 &lt;&lt; 2)
DECL|macro|OTG_SYSCON_2_REG
mdefine_line|#define OTG_SYSCON_2_REG&t;&t;OTG_REG32(0x08)
DECL|macro|OTG_EN
macro_line|#&t;define&t; OTG_EN&t;&t;&t;(1 &lt;&lt; 31)
DECL|macro|USBX_SYNCHRO
macro_line|#&t;define&t; USBX_SYNCHRO&t;&t;(1 &lt;&lt; 30)
DECL|macro|OTG_MST16
macro_line|#&t;define&t; OTG_MST16&t;&t;(1 &lt;&lt; 29)
DECL|macro|SRP_GPDATA
macro_line|#&t;define&t; SRP_GPDATA&t;&t;(1 &lt;&lt; 28)
DECL|macro|SRP_GPDVBUS
macro_line|#&t;define&t; SRP_GPDVBUS&t;&t;(1 &lt;&lt; 27)
DECL|macro|SRP_GPUVBUS
macro_line|#&t;define&t; SRP_GPUVBUS(w)&t;&t;(((w)&gt;&gt;24)&amp;0x07)
DECL|macro|A_WAIT_VRISE
macro_line|#&t;define&t; A_WAIT_VRISE(w)&t;(((w)&gt;&gt;20)&amp;0x07)
DECL|macro|B_ASE_BRST
macro_line|#&t;define&t; B_ASE_BRST(w)&t;&t;(((w)&gt;&gt;16)&amp;0x07)
DECL|macro|SRP_DPW
macro_line|#&t;define&t; SRP_DPW&t;&t;(1 &lt;&lt; 14)
DECL|macro|SRP_DATA
macro_line|#&t;define&t; SRP_DATA&t;&t;(1 &lt;&lt; 13)
DECL|macro|SRP_VBUS
macro_line|#&t;define&t; SRP_VBUS&t;&t;(1 &lt;&lt; 12)
DECL|macro|OTG_PADEN
macro_line|#&t;define&t; OTG_PADEN&t;&t;(1 &lt;&lt; 10)
DECL|macro|HMC_PADEN
macro_line|#&t;define&t; HMC_PADEN&t;&t;(1 &lt;&lt; 9)
DECL|macro|UHOST_EN
macro_line|#&t;define&t; UHOST_EN&t;&t;(1 &lt;&lt; 8)
DECL|macro|HMC_TLLSPEED
macro_line|#&t;define&t; HMC_TLLSPEED&t;&t;(1 &lt;&lt; 7)
DECL|macro|HMC_TLLATTACH
macro_line|#&t;define&t; HMC_TLLATTACH&t;&t;(1 &lt;&lt; 6)
DECL|macro|OTG_HMC
macro_line|#&t;define&t; OTG_HMC(w)&t;&t;(((w)&gt;&gt;0)&amp;0x3f)
DECL|macro|OTG_CTRL_REG
mdefine_line|#define OTG_CTRL_REG&t;&t;&t;OTG_REG32(0x0c)
DECL|macro|OTG_ASESSVLD
macro_line|#&t;define&t; OTG_ASESSVLD&t;&t;(1 &lt;&lt; 20)
DECL|macro|OTG_BSESSEND
macro_line|#&t;define&t; OTG_BSESSEND&t;&t;(1 &lt;&lt; 19)
DECL|macro|OTG_BSESSVLD
macro_line|#&t;define&t; OTG_BSESSVLD&t;&t;(1 &lt;&lt; 18)
DECL|macro|OTG_VBUSVLD
macro_line|#&t;define&t; OTG_VBUSVLD&t;&t;(1 &lt;&lt; 17)
DECL|macro|OTG_ID
macro_line|#&t;define&t; OTG_ID&t;&t;&t;(1 &lt;&lt; 16)
DECL|macro|OTG_DRIVER_SEL
macro_line|#&t;define&t; OTG_DRIVER_SEL&t;&t;(1 &lt;&lt; 15)
DECL|macro|OTG_A_SETB_HNPEN
macro_line|#&t;define&t; OTG_A_SETB_HNPEN&t;(1 &lt;&lt; 12)
DECL|macro|OTG_A_BUSREQ
macro_line|#&t;define&t; OTG_A_BUSREQ&t;&t;(1 &lt;&lt; 11)
DECL|macro|OTG_B_HNPEN
macro_line|#&t;define&t; OTG_B_HNPEN&t;&t;(1 &lt;&lt; 9)
DECL|macro|OTG_B_BUSREQ
macro_line|#&t;define&t; OTG_B_BUSREQ&t;&t;(1 &lt;&lt; 8)
DECL|macro|OTG_BUSDROP
macro_line|#&t;define&t; OTG_BUSDROP&t;&t;(1 &lt;&lt; 7)
DECL|macro|OTG_PULLDOWN
macro_line|#&t;define&t; OTG_PULLDOWN&t;&t;(1 &lt;&lt; 5)
DECL|macro|OTG_PULLUP
macro_line|#&t;define&t; OTG_PULLUP&t;&t;(1 &lt;&lt; 4)
DECL|macro|OTG_DRV_VBUS
macro_line|#&t;define&t; OTG_DRV_VBUS&t;&t;(1 &lt;&lt; 3)
DECL|macro|OTG_PD_VBUS
macro_line|#&t;define&t; OTG_PD_VBUS&t;&t;(1 &lt;&lt; 2)
DECL|macro|OTG_PU_VBUS
macro_line|#&t;define&t; OTG_PU_VBUS&t;&t;(1 &lt;&lt; 1)
DECL|macro|OTG_PU_ID
macro_line|#&t;define&t; OTG_PU_ID&t;&t;(1 &lt;&lt; 0)
DECL|macro|OTG_IRQ_EN_REG
mdefine_line|#define OTG_IRQ_EN_REG&t;&t;&t;OTG_REG16(0x10)
DECL|macro|DRIVER_SWITCH
macro_line|#&t;define&t; DRIVER_SWITCH&t;&t;(1 &lt;&lt; 15)
DECL|macro|A_VBUS_ERR
macro_line|#&t;define&t; A_VBUS_ERR&t;&t;(1 &lt;&lt; 13)
DECL|macro|A_REQ_TMROUT
macro_line|#&t;define&t; A_REQ_TMROUT&t;&t;(1 &lt;&lt; 12)
DECL|macro|A_SRP_DETECT
macro_line|#&t;define&t; A_SRP_DETECT&t;&t;(1 &lt;&lt; 11)
DECL|macro|B_HNP_FAIL
macro_line|#&t;define&t; B_HNP_FAIL&t;&t;(1 &lt;&lt; 10)
DECL|macro|B_SRP_TMROUT
macro_line|#&t;define&t; B_SRP_TMROUT&t;&t;(1 &lt;&lt; 9)
DECL|macro|B_SRP_DONE
macro_line|#&t;define&t; B_SRP_DONE&t;&t;(1 &lt;&lt; 8)
DECL|macro|B_SRP_STARTED
macro_line|#&t;define&t; B_SRP_STARTED&t;&t;(1 &lt;&lt; 7)
DECL|macro|OPRT_CHG
macro_line|#&t;define&t; OPRT_CHG&t;&t;(1 &lt;&lt; 0)
DECL|macro|OTG_IRQ_SRC_REG
mdefine_line|#define OTG_IRQ_SRC_REG&t;&t;&t;OTG_REG16(0x14)
singleline_comment|// same bits as in IRQ_EN
DECL|macro|OTG_OUTCTRL_REG
mdefine_line|#define OTG_OUTCTRL_REG&t;&t;&t;OTG_REG16(0x18)
DECL|macro|OTGVPD
macro_line|#&t;define&t; OTGVPD&t;&t;&t;(1 &lt;&lt; 14)
DECL|macro|OTGVPU
macro_line|#&t;define&t; OTGVPU&t;&t;&t;(1 &lt;&lt; 13)
DECL|macro|OTGPUID
macro_line|#&t;define&t; OTGPUID&t;&t;(1 &lt;&lt; 12)
DECL|macro|USB2VDR
macro_line|#&t;define&t; USB2VDR&t;&t;(1 &lt;&lt; 10)
DECL|macro|USB2PDEN
macro_line|#&t;define&t; USB2PDEN&t;&t;(1 &lt;&lt; 9)
DECL|macro|USB2PUEN
macro_line|#&t;define&t; USB2PUEN&t;&t;(1 &lt;&lt; 8)
DECL|macro|USB1VDR
macro_line|#&t;define&t; USB1VDR&t;&t;(1 &lt;&lt; 6)
DECL|macro|USB1PDEN
macro_line|#&t;define&t; USB1PDEN&t;&t;(1 &lt;&lt; 5)
DECL|macro|USB1PUEN
macro_line|#&t;define&t; USB1PUEN&t;&t;(1 &lt;&lt; 4)
DECL|macro|USB0VDR
macro_line|#&t;define&t; USB0VDR&t;&t;(1 &lt;&lt; 2)
DECL|macro|USB0PDEN
macro_line|#&t;define&t; USB0PDEN&t;&t;(1 &lt;&lt; 1)
DECL|macro|USB0PUEN
macro_line|#&t;define&t; USB0PUEN&t;&t;(1 &lt;&lt; 0)
DECL|macro|OTG_TEST_REG
mdefine_line|#define OTG_TEST_REG&t;&t;&t;OTG_REG16(0x20)
DECL|macro|OTG_VENDOR_CODE_REG
mdefine_line|#define OTG_VENDOR_CODE_REG&t;&t;OTG_REG32(0xfc)
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|macro|USB_TRANSCEIVER_CTRL_REG
mdefine_line|#define&t;USB_TRANSCEIVER_CTRL_REG&t;__REG32(0xfffe1000 + 0x0064)
DECL|macro|CONF_USB2_UNI_R
macro_line|#&t;define&t;CONF_USB2_UNI_R&t;&t;(1 &lt;&lt; 8)
DECL|macro|CONF_USB1_UNI_R
macro_line|#&t;define&t;CONF_USB1_UNI_R&t;&t;(1 &lt;&lt; 7)
DECL|macro|CONF_USB_PORT0_R
macro_line|#&t;define&t;CONF_USB_PORT0_R(x)&t;(((x)&gt;&gt;4)&amp;0x7)
DECL|macro|CONF_USB0_ISOLATE_R
macro_line|#&t;define&t;CONF_USB0_ISOLATE_R&t;(1 &lt;&lt; 3)
DECL|macro|CONF_USB_PWRDN_DM_R
macro_line|#&t;define&t;CONF_USB_PWRDN_DM_R&t;(1 &lt;&lt; 2)
DECL|macro|CONF_USB_PWRDN_DP_R
macro_line|#&t;define&t;CONF_USB_PWRDN_DP_R&t;(1 &lt;&lt; 1)
macro_line|#endif&t;/* __ASM_ARCH_OMAP_USB_H */
eof
