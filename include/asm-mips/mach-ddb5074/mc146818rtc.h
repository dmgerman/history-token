multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998, 2001, 03 by Ralf Baechle&n; *&n; * RTC routines for PC style attached Dallas chip.&n; */
macro_line|#ifndef __ASM_MACH_DDB5074_MC146818RTC_H
DECL|macro|__ASM_MACH_DDB5074_MC146818RTC_H
mdefine_line|#define __ASM_MACH_DDB5074_MC146818RTC_H
macro_line|#include &lt;asm/ddb5xxx/ddb5074.h&gt;
macro_line|#include &lt;asm/ddb5xxx/ddb5xxx.h&gt;
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(0x70 + (x))
DECL|macro|RTC_IRQ
mdefine_line|#define RTC_IRQ&t;&t;8
DECL|function|CMOS_READ
r_static
r_inline
r_int
r_char
id|CMOS_READ
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|KSEG1ADDR
c_func
(paren
id|DDB_PCI_MEM_BASE
)paren
op_plus
id|addr
)paren
suffix:semicolon
)brace
DECL|function|CMOS_WRITE
r_static
r_inline
r_void
id|CMOS_WRITE
c_func
(paren
r_int
r_char
id|data
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|KSEG1ADDR
c_func
(paren
id|DDB_PCI_MEM_BASE
)paren
op_plus
id|addr
)paren
op_assign
id|data
suffix:semicolon
)brace
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;1
macro_line|#endif /* __ASM_MACH_DDB5074_MC146818RTC_H */
eof
