multiline_comment|/*&n; * Copyright 2003 PMC-Sierra&n; * Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; *&n; * Board specific definititions for the PMC-Sierra Yosemite&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __SETUP_H__
DECL|macro|__SETUP_H__
mdefine_line|#define __SETUP_H__
multiline_comment|/* Real Time Clock base */
DECL|macro|YOSEMITE_RTC_BASE
mdefine_line|#define&t;YOSEMITE_RTC_BASE
DECL|macro|CONV_BCD_TO_BIN
mdefine_line|#define CONV_BCD_TO_BIN(val)    (((val) &amp; 0xf) + (((val) &gt;&gt; 4) * 10))
DECL|macro|CONV_BIN_TO_BCD
mdefine_line|#define CONV_BIN_TO_BCD(val)    (((val) % 10) + (((val) / 10) &lt;&lt; 4))
multiline_comment|/* NVRAM Base */
DECL|macro|YOSEMITE_NVRAM_BASE_ADDR
mdefine_line|#define&t;YOSEMITE_NVRAM_BASE_ADDR&t;0xbb000678&t;/* XXX Need change */
DECL|macro|YOSEMITE_RTC_BASE
mdefine_line|#define&t;YOSEMITE_RTC_BASE&t;&t;0xbb000679&t;/* XXX Need change */
multiline_comment|/*&n; * Hypertransport Specific &n; */
DECL|macro|HYPERTRANSPORT_CONFIG_REG
mdefine_line|#define HYPERTRANSPORT_CONFIG_REG       0xbb000604
DECL|macro|HYPERTRANSPORT_BAR0_REG
mdefine_line|#define HYPERTRANSPORT_BAR0_REG         0xbb000610
DECL|macro|HYPERTRANSPORT_SIZE0_REG
mdefine_line|#define HYPERTRANSPORT_SIZE0_REG        0xbb000688
DECL|macro|HYPERTRANSPORT_BAR0_ATTR_REG
mdefine_line|#define HYPERTRANSPORT_BAR0_ATTR_REG    0xbb000680
DECL|macro|HYPERTRANSPORT_BAR0_ADDR
mdefine_line|#define HYPERTRANSPORT_BAR0_ADDR        0x00000006
DECL|macro|HYPERTRANSPORT_SIZE0
mdefine_line|#define HYPERTRANSPORT_SIZE0            0x0fffffff
DECL|macro|HYPERTRANSPORT_BAR0_ATTR
mdefine_line|#define HYPERTRANSPORT_BAR0_ATTR        0x00002000
DECL|macro|HYPERTRANSPORT_ENABLE
mdefine_line|#define HYPERTRANSPORT_ENABLE           0x6
multiline_comment|/*&n; * EEPROM Size &n; */
DECL|macro|TITAN_ATMEL_24C32_SIZE
mdefine_line|#define&t;TITAN_ATMEL_24C32_SIZE&t;&t;32768
DECL|macro|TITAN_ATMEL_24C64_SIZE
mdefine_line|#define&t;TITAN_ATMEL_24C64_SIZE&t;&t;65536
macro_line|#endif /* __SETUP_H__ */
eof
