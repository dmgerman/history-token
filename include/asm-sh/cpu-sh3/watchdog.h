multiline_comment|/*&n; * include/asm-sh/cpu-sh3/watchdog.h&n; *&n; * Copyright (C) 2002, 2003 Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH3_WATCHDOG_H
DECL|macro|__ASM_CPU_SH3_WATCHDOG_H
mdefine_line|#define __ASM_CPU_SH3_WATCHDOG_H
multiline_comment|/* Register definitions */
DECL|macro|WTCNT
mdefine_line|#define WTCNT&t;&t;0xffffff84
DECL|macro|WTCSR
mdefine_line|#define WTCSR&t;&t;0xffffff86
multiline_comment|/* Bit definitions */
DECL|macro|WTCSR_TME
mdefine_line|#define WTCSR_TME&t;0x80
DECL|macro|WTCSR_WT
mdefine_line|#define WTCSR_WT&t;0x40
DECL|macro|WTCSR_RSTS
mdefine_line|#define WTCSR_RSTS&t;0x20
DECL|macro|WTCSR_WOVF
mdefine_line|#define WTCSR_WOVF&t;0x10
DECL|macro|WTCSR_IOVF
mdefine_line|#define WTCSR_IOVF&t;0x08
macro_line|#endif /* __ASM_CPU_SH3_WATCHDOG_H */
eof
