multiline_comment|/*&n; * include/asm-ppc/immap_85xx.h&n; *&n; * MPC85xx Internal Memory Map&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2004 Freescale Semiconductor, Inc&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IMMAP_85XX_H__
DECL|macro|__ASM_IMMAP_85XX_H__
mdefine_line|#define __ASM_IMMAP_85XX_H__
multiline_comment|/* Eventually this should define all the IO block registers in 85xx */
multiline_comment|/* PCI Registers */
DECL|struct|ccsr_pci
r_typedef
r_struct
id|ccsr_pci
(brace
DECL|member|cfg_addr
id|uint
id|cfg_addr
suffix:semicolon
multiline_comment|/* 0x.000 - PCI Configuration Address Register */
DECL|member|cfg_data
id|uint
id|cfg_data
suffix:semicolon
multiline_comment|/* 0x.004 - PCI Configuration Data Register */
DECL|member|int_ack
id|uint
id|int_ack
suffix:semicolon
multiline_comment|/* 0x.008 - PCI Interrupt Acknowledge Register */
DECL|member|res1
r_char
id|res1
(braket
l_int|3060
)braket
suffix:semicolon
DECL|member|potar0
id|uint
id|potar0
suffix:semicolon
multiline_comment|/* 0x.c00 - PCI Outbound Transaction Address Register 0 */
DECL|member|potear0
id|uint
id|potear0
suffix:semicolon
multiline_comment|/* 0x.c04 - PCI Outbound Translation Extended Address Register 0 */
DECL|member|powbar0
id|uint
id|powbar0
suffix:semicolon
multiline_comment|/* 0x.c08 - PCI Outbound Window Base Address Register 0 */
DECL|member|res2
r_char
id|res2
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|powar0
id|uint
id|powar0
suffix:semicolon
multiline_comment|/* 0x.c10 - PCI Outbound Window Attributes Register 0 */
DECL|member|res3
r_char
id|res3
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|potar1
id|uint
id|potar1
suffix:semicolon
multiline_comment|/* 0x.c20 - PCI Outbound Transaction Address Register 1 */
DECL|member|potear1
id|uint
id|potear1
suffix:semicolon
multiline_comment|/* 0x.c24 - PCI Outbound Translation Extended Address Register 1 */
DECL|member|powbar1
id|uint
id|powbar1
suffix:semicolon
multiline_comment|/* 0x.c28 - PCI Outbound Window Base Address Register 1 */
DECL|member|res4
r_char
id|res4
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|powar1
id|uint
id|powar1
suffix:semicolon
multiline_comment|/* 0x.c30 - PCI Outbound Window Attributes Register 1 */
DECL|member|res5
r_char
id|res5
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|potar2
id|uint
id|potar2
suffix:semicolon
multiline_comment|/* 0x.c40 - PCI Outbound Transaction Address Register 2 */
DECL|member|potear2
id|uint
id|potear2
suffix:semicolon
multiline_comment|/* 0x.c44 - PCI Outbound Translation Extended Address Register 2 */
DECL|member|powbar2
id|uint
id|powbar2
suffix:semicolon
multiline_comment|/* 0x.c48 - PCI Outbound Window Base Address Register 2 */
DECL|member|res6
r_char
id|res6
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|powar2
id|uint
id|powar2
suffix:semicolon
multiline_comment|/* 0x.c50 - PCI Outbound Window Attributes Register 2 */
DECL|member|res7
r_char
id|res7
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|potar3
id|uint
id|potar3
suffix:semicolon
multiline_comment|/* 0x.c60 - PCI Outbound Transaction Address Register 3 */
DECL|member|potear3
id|uint
id|potear3
suffix:semicolon
multiline_comment|/* 0x.c64 - PCI Outbound Translation Extended Address Register 3 */
DECL|member|powbar3
id|uint
id|powbar3
suffix:semicolon
multiline_comment|/* 0x.c68 - PCI Outbound Window Base Address Register 3 */
DECL|member|res8
r_char
id|res8
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|powar3
id|uint
id|powar3
suffix:semicolon
multiline_comment|/* 0x.c70 - PCI Outbound Window Attributes Register 3 */
DECL|member|res9
r_char
id|res9
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|potar4
id|uint
id|potar4
suffix:semicolon
multiline_comment|/* 0x.c80 - PCI Outbound Transaction Address Register 4 */
DECL|member|potear4
id|uint
id|potear4
suffix:semicolon
multiline_comment|/* 0x.c84 - PCI Outbound Translation Extended Address Register 4 */
DECL|member|powbar4
id|uint
id|powbar4
suffix:semicolon
multiline_comment|/* 0x.c88 - PCI Outbound Window Base Address Register 4 */
DECL|member|res10
r_char
id|res10
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|powar4
id|uint
id|powar4
suffix:semicolon
multiline_comment|/* 0x.c90 - PCI Outbound Window Attributes Register 4 */
DECL|member|res11
r_char
id|res11
(braket
l_int|268
)braket
suffix:semicolon
DECL|member|pitar3
id|uint
id|pitar3
suffix:semicolon
multiline_comment|/* 0x.da0 - PCI Inbound Translation Address Register 3  */
DECL|member|res12
r_char
id|res12
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|piwbar3
id|uint
id|piwbar3
suffix:semicolon
multiline_comment|/* 0x.da8 - PCI Inbound Window Base Address Register 3 */
DECL|member|piwbear3
id|uint
id|piwbear3
suffix:semicolon
multiline_comment|/* 0x.dac - PCI Inbound Window Base Extended Address Register 3 */
DECL|member|piwar3
id|uint
id|piwar3
suffix:semicolon
multiline_comment|/* 0x.db0 - PCI Inbound Window Attributes Register 3 */
DECL|member|res13
r_char
id|res13
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|pitar2
id|uint
id|pitar2
suffix:semicolon
multiline_comment|/* 0x.dc0 - PCI Inbound Translation Address Register 2  */
DECL|member|res14
r_char
id|res14
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|piwbar2
id|uint
id|piwbar2
suffix:semicolon
multiline_comment|/* 0x.dc8 - PCI Inbound Window Base Address Register 2 */
DECL|member|piwbear2
id|uint
id|piwbear2
suffix:semicolon
multiline_comment|/* 0x.dcc - PCI Inbound Window Base Extended Address Register 2 */
DECL|member|piwar2
id|uint
id|piwar2
suffix:semicolon
multiline_comment|/* 0x.dd0 - PCI Inbound Window Attributes Register 2 */
DECL|member|res15
r_char
id|res15
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|pitar1
id|uint
id|pitar1
suffix:semicolon
multiline_comment|/* 0x.de0 - PCI Inbound Translation Address Register 1  */
DECL|member|res16
r_char
id|res16
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|piwbar1
id|uint
id|piwbar1
suffix:semicolon
multiline_comment|/* 0x.de8 - PCI Inbound Window Base Address Register 1 */
DECL|member|res17
r_char
id|res17
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|piwar1
id|uint
id|piwar1
suffix:semicolon
multiline_comment|/* 0x.df0 - PCI Inbound Window Attributes Register 1 */
DECL|member|res18
r_char
id|res18
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|err_dr
id|uint
id|err_dr
suffix:semicolon
multiline_comment|/* 0x.e00 - PCI Error Detect Register */
DECL|member|err_cap_dr
id|uint
id|err_cap_dr
suffix:semicolon
multiline_comment|/* 0x.e04 - PCI Error Capture Disable Register */
DECL|member|err_en
id|uint
id|err_en
suffix:semicolon
multiline_comment|/* 0x.e08 - PCI Error Enable Register */
DECL|member|err_attrib
id|uint
id|err_attrib
suffix:semicolon
multiline_comment|/* 0x.e0c - PCI Error Attributes Capture Register */
DECL|member|err_addr
id|uint
id|err_addr
suffix:semicolon
multiline_comment|/* 0x.e10 - PCI Error Address Capture Register */
DECL|member|err_ext_addr
id|uint
id|err_ext_addr
suffix:semicolon
multiline_comment|/* 0x.e14 - PCI Error Extended Address Capture Register */
DECL|member|err_dl
id|uint
id|err_dl
suffix:semicolon
multiline_comment|/* 0x.e18 - PCI Error Data Low Capture Register */
DECL|member|err_dh
id|uint
id|err_dh
suffix:semicolon
multiline_comment|/* 0x.e1c - PCI Error Data High Capture Register */
DECL|member|gas_timr
id|uint
id|gas_timr
suffix:semicolon
multiline_comment|/* 0x.e20 - PCI Gasket Timer Register */
DECL|member|pci_timr
id|uint
id|pci_timr
suffix:semicolon
multiline_comment|/* 0x.e24 - PCI Timer Register */
DECL|member|res19
r_char
id|res19
(braket
l_int|472
)braket
suffix:semicolon
DECL|typedef|ccsr_pci_t
)brace
id|ccsr_pci_t
suffix:semicolon
multiline_comment|/* Global Utility Registers */
DECL|struct|ccsr_guts
r_typedef
r_struct
id|ccsr_guts
(brace
DECL|member|porpllsr
id|uint
id|porpllsr
suffix:semicolon
multiline_comment|/* 0x.0000 - POR PLL Ratio Status Register */
DECL|member|porbmsr
id|uint
id|porbmsr
suffix:semicolon
multiline_comment|/* 0x.0004 - POR Boot Mode Status Register */
DECL|member|porimpscr
id|uint
id|porimpscr
suffix:semicolon
multiline_comment|/* 0x.0008 - POR I/O Impedance Status and Control Register */
DECL|member|pordevsr
id|uint
id|pordevsr
suffix:semicolon
multiline_comment|/* 0x.000c - POR I/O Device Status Register */
DECL|member|pordbgmsr
id|uint
id|pordbgmsr
suffix:semicolon
multiline_comment|/* 0x.0010 - POR Debug Mode Status Register */
DECL|member|res1
r_char
id|res1
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|gpporcr
id|uint
id|gpporcr
suffix:semicolon
multiline_comment|/* 0x.0020 - General-Purpose POR Configuration Register */
DECL|member|res2
r_char
id|res2
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|gpiocr
id|uint
id|gpiocr
suffix:semicolon
multiline_comment|/* 0x.0030 - GPIO Control Register */
DECL|member|res3
r_char
id|res3
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|gpoutdr
id|uint
id|gpoutdr
suffix:semicolon
multiline_comment|/* 0x.0040 - General-Purpose Output Data Register */
DECL|member|res4
r_char
id|res4
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|gpindr
id|uint
id|gpindr
suffix:semicolon
multiline_comment|/* 0x.0050 - General-Purpose Input Data Register */
DECL|member|res5
r_char
id|res5
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|pmuxcr
id|uint
id|pmuxcr
suffix:semicolon
multiline_comment|/* 0x.0060 - Alternate Function Signal Multiplex Control */
DECL|member|res6
r_char
id|res6
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|devdisr
id|uint
id|devdisr
suffix:semicolon
multiline_comment|/* 0x.0070 - Device Disable Control */
DECL|member|res7
r_char
id|res7
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|powmgtcsr
id|uint
id|powmgtcsr
suffix:semicolon
multiline_comment|/* 0x.0080 - Power Management Status and Control Register */
DECL|member|res8
r_char
id|res8
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|mcpsumr
id|uint
id|mcpsumr
suffix:semicolon
multiline_comment|/* 0x.0090 - Machine Check Summary Register */
DECL|member|res9
r_char
id|res9
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|pvr
id|uint
id|pvr
suffix:semicolon
multiline_comment|/* 0x.00a0 - Processor Version Register */
DECL|member|svr
id|uint
id|svr
suffix:semicolon
multiline_comment|/* 0x.00a4 - System Version Register */
DECL|member|res10
r_char
id|res10
(braket
l_int|3416
)braket
suffix:semicolon
DECL|member|clkocr
id|uint
id|clkocr
suffix:semicolon
multiline_comment|/* 0x.0e00 - Clock Out Select Register */
DECL|member|res11
r_char
id|res11
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|ddrdllcr
id|uint
id|ddrdllcr
suffix:semicolon
multiline_comment|/* 0x.0e10 - DDR DLL Control Register */
DECL|member|res12
r_char
id|res12
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|lbcdllcr
id|uint
id|lbcdllcr
suffix:semicolon
multiline_comment|/* 0x.0e20 - LBC DLL Control Register */
DECL|member|res13
r_char
id|res13
(braket
l_int|61916
)braket
suffix:semicolon
DECL|typedef|ccsr_guts_t
)brace
id|ccsr_guts_t
suffix:semicolon
macro_line|#endif /* __ASM_IMMAP_85XX_H__ */
macro_line|#endif /* __KERNEL__ */
eof
