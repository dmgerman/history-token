multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MACH_GENERIC_TIMEX_H
DECL|macro|__ASM_MACH_GENERIC_TIMEX_H
mdefine_line|#define __ASM_MACH_GENERIC_TIMEX_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Last remaining user of the i8254 PIC, will be converted, too ...&n; */
macro_line|#ifdef CONFIG_SNI_RM200_PCI
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;1193182
macro_line|#else
DECL|macro|CLOCK_TICK_RATE
mdefine_line|#define CLOCK_TICK_RATE&t;&t;500000
macro_line|#endif
macro_line|#endif /* __ASM_MACH_GENERIC_TIMEX_H */
eof
