multiline_comment|/*&n; * TQM8260 board specific definitions&n; *&n; * Copyright (c) 2001 Wolfgang Denk (wd@denx.de)&n; */
macro_line|#ifndef __TQM8260_PLATFORM
DECL|macro|__TQM8260_PLATFORM
mdefine_line|#define __TQM8260_PLATFORM
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
DECL|macro|CPM_MAP_ADDR
mdefine_line|#define CPM_MAP_ADDR&t;&t;((uint)0xFFF00000)
DECL|macro|PHY_INTERRUPT
mdefine_line|#define PHY_INTERRUPT&t;&t;25
multiline_comment|/* For our show_cpuinfo hooks. */
DECL|macro|CPUINFO_VENDOR
mdefine_line|#define CPUINFO_VENDOR&t;&t;&quot;IN2 Systems&quot;
DECL|macro|CPUINFO_MACHINE
mdefine_line|#define CPUINFO_MACHINE&t;&t;&quot;TQM8260 PowerPC&quot;
DECL|macro|BOOTROM_RESTART_ADDR
mdefine_line|#define BOOTROM_RESTART_ADDR&t;((uint)0x40000104)
macro_line|#endif&t;/* __TQM8260_PLATFORM */
eof
