multiline_comment|/*&n; * Copyright 2003 PMC-Sierra&n; * Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; *&n; * Board specific definititions for the PMC-Sierra Yosemite&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __SETUP_H__
DECL|macro|__SETUP_H__
mdefine_line|#define __SETUP_H__
multiline_comment|/* NVRAM Base */
DECL|macro|YOSEMITE_NVRAM_BASE_ADDR
mdefine_line|#define&t;YOSEMITE_NVRAM_BASE_ADDR&t;0xbb000678&t;/* XXX Need change */
DECL|macro|YOSEMITE_RTC_BASE
mdefine_line|#define&t;YOSEMITE_RTC_BASE&t;&t;0xbb000679&t;/* XXX Need change */
DECL|macro|HYPERTRANSPORT_BAR0_ADDR
mdefine_line|#define HYPERTRANSPORT_BAR0_ADDR        0x00000006
DECL|macro|HYPERTRANSPORT_SIZE0
mdefine_line|#define HYPERTRANSPORT_SIZE0            0x0fffffff
DECL|macro|HYPERTRANSPORT_BAR0_ATTR
mdefine_line|#define HYPERTRANSPORT_BAR0_ATTR        0x00002000
DECL|macro|HYPERTRANSPORT_ENABLE
mdefine_line|#define HYPERTRANSPORT_ENABLE           0x6
multiline_comment|/*&n; * EEPROM Size&n; */
DECL|macro|TITAN_ATMEL_24C32_SIZE
mdefine_line|#define&t;TITAN_ATMEL_24C32_SIZE&t;&t;32768
DECL|macro|TITAN_ATMEL_24C64_SIZE
mdefine_line|#define&t;TITAN_ATMEL_24C64_SIZE&t;&t;65536
macro_line|#endif /* __SETUP_H__ */
eof
