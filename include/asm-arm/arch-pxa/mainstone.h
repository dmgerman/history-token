multiline_comment|/*&n; *  linux/include/asm-arm/arch-pxa/mainstone.h&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Nov 14, 2002&n; *  Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef ASM_ARCH_MAINSTONE_H
DECL|macro|ASM_ARCH_MAINSTONE_H
mdefine_line|#define ASM_ARCH_MAINSTONE_H
DECL|macro|MST_ETH_PHYS
mdefine_line|#define MST_ETH_PHYS&t;&t;PXA_CS4_PHYS
DECL|macro|MST_FPGA_PHYS
mdefine_line|#define MST_FPGA_PHYS&t;&t;PXA_CS2_PHYS
DECL|macro|MST_FPGA_VIRT
mdefine_line|#define MST_FPGA_VIRT&t;&t;(0xf0000000)
DECL|macro|MST_P2V
mdefine_line|#define MST_P2V(x)&t;&t;((x) - MST_FPGA_PHYS + MST_FPGA_VIRT)
DECL|macro|MST_V2P
mdefine_line|#define MST_V2P(x)&t;&t;((x) - MST_FPGA_VIRT + MST_FPGA_PHYS)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|__MST_REG
macro_line|# define __MST_REG(x)&t;&t;(*((volatile unsigned long *)MST_P2V(x)))
macro_line|#else
DECL|macro|__MST_REG
macro_line|# define __MST_REG(x)&t;&t;MST_P2V(x)
macro_line|#endif
multiline_comment|/* board level registers in the FPGA */
DECL|macro|MST_LEDDAT1
mdefine_line|#define MST_LEDDAT1&t;&t;__MST_REG(0x08000010)
DECL|macro|MST_LEDDAT2
mdefine_line|#define MST_LEDDAT2&t;&t;__MST_REG(0x08000014)
DECL|macro|MST_LEDCTRL
mdefine_line|#define MST_LEDCTRL&t;&t;__MST_REG(0x08000040)
DECL|macro|MST_GPSWR
mdefine_line|#define MST_GPSWR&t;&t;__MST_REG(0x08000060)
DECL|macro|MST_MSCWR1
mdefine_line|#define MST_MSCWR1&t;&t;__MST_REG(0x08000080)
DECL|macro|MST_MSCWR2
mdefine_line|#define MST_MSCWR2&t;&t;__MST_REG(0x08000084)
DECL|macro|MST_MSCWR3
mdefine_line|#define MST_MSCWR3&t;&t;__MST_REG(0x08000088)
DECL|macro|MST_MSCRD
mdefine_line|#define MST_MSCRD&t;&t;__MST_REG(0x08000090)
DECL|macro|MST_INTMSKENA
mdefine_line|#define MST_INTMSKENA&t;&t;__MST_REG(0x080000c0)
DECL|macro|MST_INTSETCLR
mdefine_line|#define MST_INTSETCLR&t;&t;__MST_REG(0x080000d0)
DECL|macro|MST_PCMCIA0
mdefine_line|#define MST_PCMCIA0&t;&t;__MST_REG(0x080000e0)
DECL|macro|MST_PCMCIA1
mdefine_line|#define MST_PCMCIA1&t;&t;__MST_REG(0x080000e4)
DECL|macro|MST_MSCWR1_CAMERA_ON
mdefine_line|#define MST_MSCWR1_CAMERA_ON&t;(1 &lt;&lt; 15)  /* Camera interface power control */
DECL|macro|MST_MSCWR1_CAMERA_SEL
mdefine_line|#define MST_MSCWR1_CAMERA_SEL&t;(1 &lt;&lt; 14)  /* Camera interface mux control */
DECL|macro|MST_MSCWR1_LCD_CTL
mdefine_line|#define MST_MSCWR1_LCD_CTL&t;(1 &lt;&lt; 13)  /* General-purpose LCD control */
DECL|macro|MST_MSCWR1_MS_ON
mdefine_line|#define MST_MSCWR1_MS_ON&t;(1 &lt;&lt; 12)  /* Memory Stick power control */
DECL|macro|MST_MSCWR1_MMC_ON
mdefine_line|#define MST_MSCWR1_MMC_ON&t;(1 &lt;&lt; 11)  /* MultiMediaCard* power control */
DECL|macro|MST_MSCWR1_MS_SEL
mdefine_line|#define MST_MSCWR1_MS_SEL&t;(1 &lt;&lt; 10)  /* SD/MS multiplexer control */
DECL|macro|MST_MSCWR1_BB_SEL
mdefine_line|#define MST_MSCWR1_BB_SEL&t;(1 &lt;&lt; 9)   /* PCMCIA/Baseband multiplexer */
DECL|macro|MST_MSCWR1_BT_ON
mdefine_line|#define MST_MSCWR1_BT_ON&t;(1 &lt;&lt; 8)   /* Bluetooth UART transceiver */
DECL|macro|MST_MSCWR1_BTDTR
mdefine_line|#define MST_MSCWR1_BTDTR&t;(1 &lt;&lt; 7)   /* Bluetooth UART DTR */
DECL|macro|MST_MSCWR1_IRDA_MASK
mdefine_line|#define MST_MSCWR1_IRDA_MASK&t;(3 &lt;&lt; 5)   /* IrDA transceiver mode */
DECL|macro|MST_MSCWR1_IRDA_FULL
mdefine_line|#define MST_MSCWR1_IRDA_FULL&t;(0 &lt;&lt; 5)   /* full distance power */
DECL|macro|MST_MSCWR1_IRDA_OFF
mdefine_line|#define MST_MSCWR1_IRDA_OFF&t;(1 &lt;&lt; 5)   /* shutdown */
DECL|macro|MST_MSCWR1_IRDA_MED
mdefine_line|#define MST_MSCWR1_IRDA_MED&t;(2 &lt;&lt; 5)   /* 2/3 distance power */
DECL|macro|MST_MSCWR1_IRDA_LOW
mdefine_line|#define MST_MSCWR1_IRDA_LOW&t;(3 &lt;&lt; 5)   /* 1/3 distance power */
DECL|macro|MST_MSCWR1_IRDA_FIR
mdefine_line|#define MST_MSCWR1_IRDA_FIR&t;(1 &lt;&lt; 4)   /* IrDA transceiver SIR/FIR */
DECL|macro|MST_MSCWR1_GREENLED
mdefine_line|#define MST_MSCWR1_GREENLED&t;(1 &lt;&lt; 3)   /* LED D1 control */
DECL|macro|MST_MSCWR1_PDC_CTL
mdefine_line|#define MST_MSCWR1_PDC_CTL&t;(1 &lt;&lt; 2)   /* reserved */
DECL|macro|MST_MSCWR1_MTR_ON
mdefine_line|#define MST_MSCWR1_MTR_ON&t;(1 &lt;&lt; 1)   /* Silent alert motor */
DECL|macro|MST_MSCWR1_SYSRESET
mdefine_line|#define MST_MSCWR1_SYSRESET&t;(1 &lt;&lt; 0)   /* System reset */
DECL|macro|MST_MSCWR2_USB_OTG_RST
mdefine_line|#define MST_MSCWR2_USB_OTG_RST&t;(1 &lt;&lt; 6)   /* USB On The Go reset */
DECL|macro|MST_MSCWR2_USB_OTG_SEL
mdefine_line|#define MST_MSCWR2_USB_OTG_SEL&t;(1 &lt;&lt; 5)   /* USB On The Go control */
DECL|macro|MST_MSCWR2_nUSBC_SC
mdefine_line|#define MST_MSCWR2_nUSBC_SC&t;(1 &lt;&lt; 4)   /* USB client soft connect control */
DECL|macro|MST_MSCWR2_I2S_SPKROFF
mdefine_line|#define MST_MSCWR2_I2S_SPKROFF&t;(1 &lt;&lt; 3)   /* I2S CODEC amplifier control */
DECL|macro|MST_MSCWR2_AC97_SPKROFF
mdefine_line|#define MST_MSCWR2_AC97_SPKROFF&t;(1 &lt;&lt; 2)   /* AC97 CODEC amplifier control */
DECL|macro|MST_MSCWR2_RADIO_PWR
mdefine_line|#define MST_MSCWR2_RADIO_PWR&t;(1 &lt;&lt; 1)   /* Radio module power control */
DECL|macro|MST_MSCWR2_RADIO_WAKE
mdefine_line|#define MST_MSCWR2_RADIO_WAKE&t;(1 &lt;&lt; 0)   /* Radio module wake-up signal */
DECL|macro|MST_MSCWR3_GPIO_RESET_EN
mdefine_line|#define MST_MSCWR3_GPIO_RESET_EN&t;(1 &lt;&lt; 2) /* Enable GPIO Reset */
DECL|macro|MST_MSCWR3_GPIO_RESET
mdefine_line|#define MST_MSCWR3_GPIO_RESET&t;&t;(1 &lt;&lt; 1) /* Initiate a GPIO Reset */
DECL|macro|MST_MSCWR3_COMMS_SW_RESET
mdefine_line|#define MST_MSCWR3_COMMS_SW_RESET&t;(1 &lt;&lt; 0) /* Communications Processor Reset Control */
DECL|macro|MST_MSCRD_nPENIRQ
mdefine_line|#define MST_MSCRD_nPENIRQ&t;(1 &lt;&lt; 9)   /* ADI7873* nPENIRQ signal */
DECL|macro|MST_MSCRD_nMEMSTK_CD
mdefine_line|#define MST_MSCRD_nMEMSTK_CD&t;(1 &lt;&lt; 8)   /* Memory Stick detection signal */
DECL|macro|MST_MSCRD_nMMC_CD
mdefine_line|#define MST_MSCRD_nMMC_CD&t;(1 &lt;&lt; 7)   /* SD/MMC card detection signal */
DECL|macro|MST_MSCRD_nUSIM_CD
mdefine_line|#define MST_MSCRD_nUSIM_CD&t;(1 &lt;&lt; 6)   /* USIM card detection signal */
DECL|macro|MST_MSCRD_USB_CBL
mdefine_line|#define MST_MSCRD_USB_CBL&t;(1 &lt;&lt; 5)   /* USB client cable status */
DECL|macro|MST_MSCRD_TS_BUSY
mdefine_line|#define MST_MSCRD_TS_BUSY&t;(1 &lt;&lt; 4)   /* ADI7873 busy */
DECL|macro|MST_MSCRD_BTDSR
mdefine_line|#define MST_MSCRD_BTDSR&t;&t;(1 &lt;&lt; 3)   /* Bluetooth UART DSR */
DECL|macro|MST_MSCRD_BTRI
mdefine_line|#define MST_MSCRD_BTRI&t;&t;(1 &lt;&lt; 2)   /* Bluetooth UART Ring Indicator */
DECL|macro|MST_MSCRD_BTDCD
mdefine_line|#define MST_MSCRD_BTDCD&t;&t;(1 &lt;&lt; 1)   /* Bluetooth UART DCD */
DECL|macro|MST_MSCRD_nMMC_WP
mdefine_line|#define MST_MSCRD_nMMC_WP&t;(1 &lt;&lt; 0)   /* SD/MMC write-protect status */
DECL|macro|MST_INT_S1_IRQ
mdefine_line|#define MST_INT_S1_IRQ&t;&t;(1 &lt;&lt; 15)  /* PCMCIA socket 1 IRQ */
DECL|macro|MST_INT_S1_STSCHG
mdefine_line|#define MST_INT_S1_STSCHG&t;(1 &lt;&lt; 14)  /* PCMCIA socket 1 status changed */
DECL|macro|MST_INT_S1_CD
mdefine_line|#define MST_INT_S1_CD&t;&t;(1 &lt;&lt; 13)  /* PCMCIA socket 1 card detection */
DECL|macro|MST_INT_S0_IRQ
mdefine_line|#define MST_INT_S0_IRQ&t;&t;(1 &lt;&lt; 11)  /* PCMCIA socket 0 IRQ */
DECL|macro|MST_INT_S0_STSCHG
mdefine_line|#define MST_INT_S0_STSCHG&t;(1 &lt;&lt; 10)  /* PCMCIA socket 0 status changed */
DECL|macro|MST_INT_S0_CD
mdefine_line|#define MST_INT_S0_CD&t;&t;(1 &lt;&lt; 9)   /* PCMCIA socket 0 card detection */
DECL|macro|MST_INT_nEXBRD_INT
mdefine_line|#define MST_INT_nEXBRD_INT&t;(1 &lt;&lt; 7)   /* Expansion board IRQ */
DECL|macro|MST_INT_MSINS
mdefine_line|#define MST_INT_MSINS&t;&t;(1 &lt;&lt; 6)   /* Memory Stick* detection */
DECL|macro|MST_INT_PENIRQ
mdefine_line|#define MST_INT_PENIRQ&t;&t;(1 &lt;&lt; 5)   /* ADI7873* touch-screen IRQ */
DECL|macro|MST_INT_AC97
mdefine_line|#define MST_INT_AC97&t;&t;(1 &lt;&lt; 4)   /* AC&squot;97 CODEC IRQ */
DECL|macro|MST_INT_ETHERNET
mdefine_line|#define MST_INT_ETHERNET&t;(1 &lt;&lt; 3)   /* Ethernet controller IRQ */
DECL|macro|MST_INT_USBC
mdefine_line|#define MST_INT_USBC&t;&t;(1 &lt;&lt; 2)   /* USB client cable detection IRQ */
DECL|macro|MST_INT_USIM
mdefine_line|#define MST_INT_USIM&t;&t;(1 &lt;&lt; 1)   /* USIM card detection IRQ */
DECL|macro|MST_INT_MMC
mdefine_line|#define MST_INT_MMC&t;&t;(1 &lt;&lt; 0)   /* MMC/SD card detection IRQ */
DECL|macro|MST_PCMCIA_nIRQ
mdefine_line|#define MST_PCMCIA_nIRQ&t;&t;(1 &lt;&lt; 10)  /* IRQ / ready signal */
DECL|macro|MST_PCMCIA_nSPKR_BVD2
mdefine_line|#define MST_PCMCIA_nSPKR_BVD2&t;(1 &lt;&lt; 9)   /* VDD sense / digital speaker */
DECL|macro|MST_PCMCIA_nSTSCHG_BVD1
mdefine_line|#define MST_PCMCIA_nSTSCHG_BVD1&t;(1 &lt;&lt; 8)   /* VDD sense / card status changed */
DECL|macro|MST_PCMCIA_nVS2
mdefine_line|#define MST_PCMCIA_nVS2&t;&t;(1 &lt;&lt; 7)   /* VSS voltage sense */
DECL|macro|MST_PCMCIA_nVS1
mdefine_line|#define MST_PCMCIA_nVS1&t;&t;(1 &lt;&lt; 6)   /* VSS voltage sense */
DECL|macro|MST_PCMCIA_nCD
mdefine_line|#define MST_PCMCIA_nCD&t;&t;(1 &lt;&lt; 5)   /* Card detection signal */
DECL|macro|MST_PCMCIA_RESET
mdefine_line|#define MST_PCMCIA_RESET&t;(1 &lt;&lt; 4)   /* Card reset signal */
DECL|macro|MST_PCMCIA_PWR_MASK
mdefine_line|#define MST_PCMCIA_PWR_MASK&t;(0x000f)   /* MAX1602 power-supply controls */
DECL|macro|MST_PCMCIA_PWR_VPP_0
mdefine_line|#define MST_PCMCIA_PWR_VPP_0    0x0&t;   /* voltage VPP = 0V */
DECL|macro|MST_PCMCIA_PWR_VPP_120
mdefine_line|#define MST_PCMCIA_PWR_VPP_120  0x2 &t;   /* voltage VPP = 12V*/
DECL|macro|MST_PCMCIA_PWR_VPP_VCC
mdefine_line|#define MST_PCMCIA_PWR_VPP_VCC  0x1&t;   /* voltage VPP = VCC */
DECL|macro|MST_PCMCIA_PWR_VCC_0
mdefine_line|#define MST_PCMCIA_PWR_VCC_0    0x0&t;   /* voltage VCC = 0V */
DECL|macro|MST_PCMCIA_PWR_VCC_33
mdefine_line|#define MST_PCMCIA_PWR_VCC_33   0x8&t;   /* voltage VCC = 3.3V */
DECL|macro|MST_PCMCIA_PWR_VCC_50
mdefine_line|#define MST_PCMCIA_PWR_VCC_50   0x4&t;   /* voltage VCC = 5.0V */
macro_line|#endif
eof
