multiline_comment|/*&n; * Copyright 2003, 04 PMC-Sierra&n; * Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; * Copyright 2004 Ralf Baechle &lt;ralf@linux-mips.org&gt;&n; *&n; * Board specific definititions for the PMC-Sierra Yosemite&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __SETUP_H__
DECL|macro|__SETUP_H__
mdefine_line|#define __SETUP_H__
multiline_comment|/* M48T37 RTC + NVRAM */
DECL|macro|YOSEMITE_RTC_BASE
mdefine_line|#define&t;YOSEMITE_RTC_BASE&t;&t;0xfc800000
DECL|macro|YOSEMITE_RTC_SIZE
mdefine_line|#define&t;YOSEMITE_RTC_SIZE&t;&t;0x00800000
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
