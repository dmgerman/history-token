multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MACH_JMR3927_ASM_DS1742_H
DECL|macro|__ASM_MACH_JMR3927_ASM_DS1742_H
mdefine_line|#define __ASM_MACH_JMR3927_ASM_DS1742_H
macro_line|#include &lt;asm/jmr3927/jmr3927.h&gt;
DECL|macro|rtc_read
mdefine_line|#define rtc_read(reg)&t;&t;(jmr3927_nvram_in(addr))
DECL|macro|rtc_write
mdefine_line|#define rtc_write(data, reg)&t;(jmr3927_nvram_out((data),(reg)))
macro_line|#endif /* __ASM_MACH_JMR3927_ASM_DS1742_H */
eof
