multiline_comment|/*&n; * linux/include/asm-arm/arch-h720x/h7202-regs.h&n; *&n; * Copyright (C) 2000 Jungjun Kim, Hynix Semiconductor Inc.&n; *           (C) 2003 Thomas Gleixner &lt;tglx@linutronix.de&gt;&n; *           (C) 2003 Robert Schwebel &lt;r.schwebel@pengutronix.de&gt;&n; *           (C) 2004 Sascha Hauer    &lt;s.hauer@pengutronix.de&gt;&n; *&n; * This file contains the hardware definitions of the h720x processors&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Do not add implementations specific defines here. This files contains&n; * only defines of the onchip peripherals. Add those defines to boards.h,&n; * which is included by this file.&n; */
DECL|macro|SERIAL2_OFS
mdefine_line|#define SERIAL2_OFS&t;&t;0x2d000
DECL|macro|SERIAL2_BASE
mdefine_line|#define SERIAL2_BASE&t;&t;(IO_PHYS + SERIAL2_OFS)
DECL|macro|SERIAL2_VIRT
mdefine_line|#define SERIAL2_VIRT &t;&t;(IO_VIRT + SERIAL2_OFS)
DECL|macro|SERIAL3_OFS
mdefine_line|#define SERIAL3_OFS&t;&t;0x2e000
DECL|macro|SERIAL3_BASE
mdefine_line|#define SERIAL3_BASE&t;&t;(IO_PHYS + SERIAL3_OFS)
DECL|macro|SERIAL3_VIRT
mdefine_line|#define SERIAL3_VIRT &t;&t;(IO_VIRT + SERIAL3_OFS)
multiline_comment|/* Matrix Keyboard Controller */
DECL|macro|KBD_VIRT
mdefine_line|#define KBD_VIRT&t;&t;(IO_VIRT + 0x22000)
DECL|macro|KBD_KBCR
mdefine_line|#define KBD_KBCR&t;&t;0x00
DECL|macro|KBD_KBSC
mdefine_line|#define KBD_KBSC&t;&t;0x04
DECL|macro|KBD_KBTR
mdefine_line|#define KBD_KBTR&t;&t;0x08
DECL|macro|KBD_KBVR0
mdefine_line|#define KBD_KBVR0&t;&t;0x0C
DECL|macro|KBD_KBVR1
mdefine_line|#define KBD_KBVR1&t;&t;0x10
DECL|macro|KBD_KBSR
mdefine_line|#define KBD_KBSR&t;&t;0x18
DECL|macro|KBD_KBCR_SCANENABLE
mdefine_line|#define KBD_KBCR_SCANENABLE&t;(1 &lt;&lt; 7)
DECL|macro|KBD_KBCR_NPOWERDOWN
mdefine_line|#define KBD_KBCR_NPOWERDOWN&t;(1 &lt;&lt; 2)
DECL|macro|KBD_KBCR_CLKSEL_MASK
mdefine_line|#define KBD_KBCR_CLKSEL_MASK&t;(3)
DECL|macro|KBD_KBCR_CLKSEL_PCLK2
mdefine_line|#define KBD_KBCR_CLKSEL_PCLK2&t;0x0
DECL|macro|KBD_KBCR_CLKSEL_PCLK128
mdefine_line|#define KBD_KBCR_CLKSEL_PCLK128&t;0x1
DECL|macro|KBD_KBCR_CLKSEL_PCLK256
mdefine_line|#define KBD_KBCR_CLKSEL_PCLK256&t;0x2
DECL|macro|KBD_KBCR_CLKSEL_PCLK512
mdefine_line|#define KBD_KBCR_CLKSEL_PCLK512&t;0x3
DECL|macro|KBD_KBSR_INTR
mdefine_line|#define KBD_KBSR_INTR&t;&t;(1 &lt;&lt; 0)
DECL|macro|KBD_KBSR_WAKEUP
mdefine_line|#define KBD_KBSR_WAKEUP&t;&t;(1 &lt;&lt; 1)
multiline_comment|/* USB device controller */
DECL|macro|USBD_BASE
mdefine_line|#define USBD_BASE&t;&t;(IO_VIRT + 0x12000)
DECL|macro|USBD_LENGTH
mdefine_line|#define USBD_LENGTH&t;&t;0x3C
DECL|macro|USBD_GCTRL
mdefine_line|#define USBD_GCTRL&t;&t;0x00
DECL|macro|USBD_EPCTRL
mdefine_line|#define USBD_EPCTRL&t;&t;0x04
DECL|macro|USBD_INTMASK
mdefine_line|#define USBD_INTMASK&t;&t;0x08
DECL|macro|USBD_INTSTAT
mdefine_line|#define USBD_INTSTAT&t;&t;0x0C
DECL|macro|USBD_PWR
mdefine_line|#define USBD_PWR&t;&t;0x10
DECL|macro|USBD_DMARXTX
mdefine_line|#define USBD_DMARXTX&t;&t;0x14
DECL|macro|USBD_DEVID
mdefine_line|#define USBD_DEVID&t;&t;0x18
DECL|macro|USBD_DEVCLASS
mdefine_line|#define USBD_DEVCLASS&t;&t;0x1C
DECL|macro|USBD_INTCLASS
mdefine_line|#define USBD_INTCLASS&t;&t;0x20
DECL|macro|USBD_SETUP0
mdefine_line|#define USBD_SETUP0&t;&t;0x24
DECL|macro|USBD_SETUP1
mdefine_line|#define USBD_SETUP1&t;&t;0x28
DECL|macro|USBD_ENDP0RD
mdefine_line|#define USBD_ENDP0RD&t;&t;0x2C
DECL|macro|USBD_ENDP0WT
mdefine_line|#define USBD_ENDP0WT&t;&t;0x30
DECL|macro|USBD_ENDP1RD
mdefine_line|#define USBD_ENDP1RD&t;&t;0x34
DECL|macro|USBD_ENDP2WT
mdefine_line|#define USBD_ENDP2WT&t;&t;0x38
multiline_comment|/* PS/2 port */
DECL|macro|PSDATA
mdefine_line|#define PSDATA 0x00
DECL|macro|PSSTAT
mdefine_line|#define PSSTAT 0x04
DECL|macro|PSSTAT_TXEMPTY
mdefine_line|#define PSSTAT_TXEMPTY (1&lt;&lt;0)
DECL|macro|PSSTAT_TXBUSY
mdefine_line|#define PSSTAT_TXBUSY (1&lt;&lt;1)
DECL|macro|PSSTAT_RXFULL
mdefine_line|#define PSSTAT_RXFULL (1&lt;&lt;2)
DECL|macro|PSSTAT_RXBUSY
mdefine_line|#define PSSTAT_RXBUSY (1&lt;&lt;3)
DECL|macro|PSSTAT_CLKIN
mdefine_line|#define PSSTAT_CLKIN (1&lt;&lt;4)
DECL|macro|PSSTAT_DATAIN
mdefine_line|#define PSSTAT_DATAIN (1&lt;&lt;5)
DECL|macro|PSSTAT_PARITY
mdefine_line|#define PSSTAT_PARITY (1&lt;&lt;6)
DECL|macro|PSCONF
mdefine_line|#define PSCONF 0x08
DECL|macro|PSCONF_ENABLE
mdefine_line|#define PSCONF_ENABLE (1&lt;&lt;0)
DECL|macro|PSCONF_TXINTEN
mdefine_line|#define PSCONF_TXINTEN (1&lt;&lt;2)
DECL|macro|PSCONF_RXINTEN
mdefine_line|#define PSCONF_RXINTEN (1&lt;&lt;3)
DECL|macro|PSCONF_FORCECLKLOW
mdefine_line|#define PSCONF_FORCECLKLOW (1&lt;&lt;4)
DECL|macro|PSCONF_FORCEDATLOW
mdefine_line|#define PSCONF_FORCEDATLOW (1&lt;&lt;5)
DECL|macro|PSCONF_LCE
mdefine_line|#define PSCONF_LCE (1&lt;&lt;6)
DECL|macro|PSINTR
mdefine_line|#define PSINTR 0x0C
DECL|macro|PSINTR_TXINT
mdefine_line|#define PSINTR_TXINT (1&lt;&lt;0)
DECL|macro|PSINTR_RXINT
mdefine_line|#define PSINTR_RXINT (1&lt;&lt;1)
DECL|macro|PSINTR_PAR
mdefine_line|#define PSINTR_PAR (1&lt;&lt;2)
DECL|macro|PSINTR_RXTO
mdefine_line|#define PSINTR_RXTO (1&lt;&lt;3)
DECL|macro|PSINTR_TXTO
mdefine_line|#define PSINTR_TXTO (1&lt;&lt;4)
DECL|macro|PSTDLO
mdefine_line|#define PSTDLO 0x10 /* clk low before start transmission */
DECL|macro|PSTPRI
mdefine_line|#define PSTPRI 0x14 /* PRI clock */
DECL|macro|PSTXMT
mdefine_line|#define PSTXMT 0x18 /* maximum transmission time */
DECL|macro|PSTREC
mdefine_line|#define PSTREC 0x20 /* maximum receive time */
DECL|macro|PSPWDN
mdefine_line|#define PSPWDN 0x3c
multiline_comment|/* ADC converter */
DECL|macro|ADC_BASE
mdefine_line|#define ADC_BASE &t;&t;(IO_VIRT + 0x29000)
DECL|macro|ADC_CR
mdefine_line|#define ADC_CR &t;&t;&t;0x00
DECL|macro|ADC_TSCTRL
mdefine_line|#define ADC_TSCTRL &t;&t;0x04
DECL|macro|ADC_BT_CTRL
mdefine_line|#define ADC_BT_CTRL &t;&t;0x08
DECL|macro|ADC_MC_CTRL
mdefine_line|#define ADC_MC_CTRL&t;&t;0x0C
DECL|macro|ADC_STATUS
mdefine_line|#define ADC_STATUS&t;&t;0x10
multiline_comment|/* ADC control register bits */
DECL|macro|ADC_CR_PW_CTRL
mdefine_line|#define ADC_CR_PW_CTRL &t;&t;0x80
DECL|macro|ADC_CR_DIRECTC
mdefine_line|#define ADC_CR_DIRECTC&t;&t;0x04
DECL|macro|ADC_CR_CONTIME_NO
mdefine_line|#define ADC_CR_CONTIME_NO&t;0x00
DECL|macro|ADC_CR_CONTIME_2
mdefine_line|#define ADC_CR_CONTIME_2&t;0x04
DECL|macro|ADC_CR_CONTIME_4
mdefine_line|#define ADC_CR_CONTIME_4&t;0x08
DECL|macro|ADC_CR_CONTIME_ADE
mdefine_line|#define ADC_CR_CONTIME_ADE&t;0x0c
DECL|macro|ADC_CR_LONGCALTIME
mdefine_line|#define ADC_CR_LONGCALTIME&t;0x01
multiline_comment|/* ADC touch panel register bits */
DECL|macro|ADC_TSCTRL_ENABLE
mdefine_line|#define ADC_TSCTRL_ENABLE &t;0x80
DECL|macro|ADC_TSCTRL_INTR
mdefine_line|#define ADC_TSCTRL_INTR   &t;0x40
DECL|macro|ADC_TSCTRL_SWBYPSS
mdefine_line|#define&t;ADC_TSCTRL_SWBYPSS&t;0x20
DECL|macro|ADC_TSCTRL_SWINVT
mdefine_line|#define ADC_TSCTRL_SWINVT&t;0x10
DECL|macro|ADC_TSCTRL_S400
mdefine_line|#define ADC_TSCTRL_S400   &t;0x03
DECL|macro|ADC_TSCTRL_S200
mdefine_line|#define ADC_TSCTRL_S200   &t;0x02
DECL|macro|ADC_TSCTRL_S100
mdefine_line|#define ADC_TSCTRL_S100   &t;0x01
DECL|macro|ADC_TSCTRL_S50
mdefine_line|#define ADC_TSCTRL_S50    &t;0x00
multiline_comment|/* ADC Interrupt Status Register bits */
DECL|macro|ADC_STATUS_TS_BIT
mdefine_line|#define ADC_STATUS_TS_BIT&t;0x80
DECL|macro|ADC_STATUS_MBT_BIT
mdefine_line|#define ADC_STATUS_MBT_BIT&t;0x40
DECL|macro|ADC_STATUS_BBT_BIT
mdefine_line|#define ADC_STATUS_BBT_BIT&t;0x20
DECL|macro|ADC_STATUS_MIC_BIT
mdefine_line|#define ADC_STATUS_MIC_BIT&t;0x10
multiline_comment|/* Touch data registers */
DECL|macro|ADC_TS_X0X1
mdefine_line|#define ADC_TS_X0X1  &t;&t;0x30
DECL|macro|ADC_TS_X2X3
mdefine_line|#define ADC_TS_X2X3&t;&t;0x34
DECL|macro|ADC_TS_Y0Y1
mdefine_line|#define ADC_TS_Y0Y1&t;&t;0x38
DECL|macro|ADC_TS_Y2Y3
mdefine_line|#define ADC_TS_Y2Y3  &t;&t;0x3c
DECL|macro|ADC_TS_X4X5
mdefine_line|#define ADC_TS_X4X5  &t;&t;0x40
DECL|macro|ADC_TS_X6X7
mdefine_line|#define ADC_TS_X6X7  &t;&t;0x44
DECL|macro|ADC_TS_Y4Y5
mdefine_line|#define ADC_TS_Y4Y5&t;&t;0x48
DECL|macro|ADC_TS_Y6Y7
mdefine_line|#define ADC_TS_Y6Y7&t;&t;0x50
multiline_comment|/* battery data */
DECL|macro|ADC_MB_DATA
mdefine_line|#define ADC_MB_DATA&t;&t;0x54
DECL|macro|ADC_BB_DATA
mdefine_line|#define ADC_BB_DATA&t;&t;0x58
multiline_comment|/* Sound data register */
DECL|macro|ADC_SD_DAT0
mdefine_line|#define ADC_SD_DAT0 &t;&t;0x60
DECL|macro|ADC_SD_DAT1
mdefine_line|#define ADC_SD_DAT1&t;&t;0x64
DECL|macro|ADC_SD_DAT2
mdefine_line|#define ADC_SD_DAT2&t;&t;0x68
DECL|macro|ADC_SD_DAT3
mdefine_line|#define ADC_SD_DAT3&t;&t;0x6c
DECL|macro|ADC_SD_DAT4
mdefine_line|#define ADC_SD_DAT4&t;&t;0x70
DECL|macro|ADC_SD_DAT5
mdefine_line|#define ADC_SD_DAT5&t;&t;0x74
DECL|macro|ADC_SD_DAT6
mdefine_line|#define ADC_SD_DAT6&t;&t;0x78
DECL|macro|ADC_SD_DAT7
mdefine_line|#define ADC_SD_DAT7&t;&t;0x7c
eof
