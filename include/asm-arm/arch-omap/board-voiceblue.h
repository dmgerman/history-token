multiline_comment|/*&n; * Copyright (C) 2004 2N Telekomunikace, Ladislav Michl &lt;michl@2n.cz&gt;&n; *&n; * Hardware definitions for OMAP5910 based VoiceBlue board.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARCH_VOICEBLUE_H
DECL|macro|__ASM_ARCH_VOICEBLUE_H
mdefine_line|#define __ASM_ARCH_VOICEBLUE_H
macro_line|#if (EXTERNAL_MAX_NR_PORTS &lt; 4)
DECL|macro|EXTERNAL_MAX_NR_PORTS
macro_line|#undef EXTERNAL_MAX_NR_PORTS
DECL|macro|EXTERNAL_MAX_NR_PORTS
mdefine_line|#define EXTERNAL_MAX_NR_PORTS&t;4
macro_line|#endif
r_extern
r_void
id|voiceblue_wdt_enable
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|voiceblue_wdt_disable
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|voiceblue_wdt_ping
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|voiceblue_reset
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /*  __ASM_ARCH_VOICEBLUE_H */
eof
