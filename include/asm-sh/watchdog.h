multiline_comment|/*&n; * include/asm-sh/watchdog.h&n; *&n; * Copyright (C) 2002, 2003 Paul Mundt&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __ASM_SH_WATCHDOG_H
DECL|macro|__ASM_SH_WATCHDOG_H
mdefine_line|#define __ASM_SH_WATCHDOG_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/cpu/watchdog.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* &n; * See asm/cpu-sh2/watchdog.h for explanation of this stupidity..&n; */
macro_line|#ifndef WTCNT_R
DECL|macro|WTCNT_R
macro_line|#  define WTCNT_R&t;WTCNT
macro_line|#endif
macro_line|#ifndef WTCSR_R
DECL|macro|WTCSR_R
macro_line|#  define WTCSR_R&t;WTCSR
macro_line|#endif
DECL|macro|WTCNT_HIGH
mdefine_line|#define WTCNT_HIGH&t;0x5a
DECL|macro|WTCSR_HIGH
mdefine_line|#define WTCSR_HIGH&t;0xa5
DECL|macro|WTCSR_CKS2
mdefine_line|#define WTCSR_CKS2&t;0x04
DECL|macro|WTCSR_CKS1
mdefine_line|#define WTCSR_CKS1&t;0x02
DECL|macro|WTCSR_CKS0
mdefine_line|#define WTCSR_CKS0&t;0x01
multiline_comment|/*&n; * CKS0-2 supports a number of clock division ratios. At the time the watchdog&n; * is enabled, it defaults to a 41 usec overflow period .. we overload this to&n; * something a little more reasonable, and really can&squot;t deal with anything&n; * lower than WTCSR_CKS_1024, else we drop back into the usec range.&n; *&n; * Clock Division Ratio         Overflow Period&n; * --------------------------------------------&n; *     1/32 (initial value)       41 usecs&n; *     1/64                       82 usecs&n; *     1/128                     164 usecs&n; *     1/256                     328 usecs&n; *     1/512                     656 usecs&n; *     1/1024                   1.31 msecs&n; *     1/2048                   2.62 msecs&n; *     1/4096                   5.25 msecs&n; */
DECL|macro|WTCSR_CKS_32
mdefine_line|#define WTCSR_CKS_32&t;0x00
DECL|macro|WTCSR_CKS_64
mdefine_line|#define WTCSR_CKS_64&t;0x01
DECL|macro|WTCSR_CKS_128
mdefine_line|#define WTCSR_CKS_128&t;0x02
DECL|macro|WTCSR_CKS_256
mdefine_line|#define WTCSR_CKS_256&t;0x03
DECL|macro|WTCSR_CKS_512
mdefine_line|#define WTCSR_CKS_512&t;0x04
DECL|macro|WTCSR_CKS_1024
mdefine_line|#define WTCSR_CKS_1024&t;0x05
DECL|macro|WTCSR_CKS_2048
mdefine_line|#define WTCSR_CKS_2048&t;0x06
DECL|macro|WTCSR_CKS_4096
mdefine_line|#define WTCSR_CKS_4096&t;0x07
multiline_comment|/**&n; * &t;sh_wdt_read_cnt - Read from Counter&n; *&n; * &t;Reads back the WTCNT value.&n; */
DECL|function|sh_wdt_read_cnt
r_static
r_inline
id|__u8
id|sh_wdt_read_cnt
c_func
(paren
r_void
)paren
(brace
r_return
id|ctrl_inb
c_func
(paren
id|WTCNT_R
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;sh_wdt_write_cnt - Write to Counter&n; *&n; *&t;@val: Value to write&n; *&n; *&t;Writes the given value @val to the lower byte of the timer counter.&n; *&t;The upper byte is set manually on each write.&n; */
DECL|function|sh_wdt_write_cnt
r_static
r_inline
r_void
id|sh_wdt_write_cnt
c_func
(paren
id|__u8
id|val
)paren
(brace
id|ctrl_outw
c_func
(paren
(paren
id|WTCNT_HIGH
op_lshift
l_int|8
)paren
op_or
(paren
id|__u16
)paren
id|val
comma
id|WTCNT
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;sh_wdt_read_csr - Read from Control/Status Register&n; *&n; *&t;Reads back the WTCSR value.&n; */
DECL|function|sh_wdt_read_csr
r_static
r_inline
id|__u8
id|sh_wdt_read_csr
c_func
(paren
r_void
)paren
(brace
r_return
id|ctrl_inb
c_func
(paren
id|WTCSR_R
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;sh_wdt_write_csr - Write to Control/Status Register&n; *&n; * &t;@val: Value to write&n; *&n; * &t;Writes the given value @val to the lower byte of the control/status&n; * &t;register. The upper byte is set manually on each write.&n; */
DECL|function|sh_wdt_write_csr
r_static
r_inline
r_void
id|sh_wdt_write_csr
c_func
(paren
id|__u8
id|val
)paren
(brace
id|ctrl_outw
c_func
(paren
(paren
id|WTCSR_HIGH
op_lshift
l_int|8
)paren
op_or
(paren
id|__u16
)paren
id|val
comma
id|WTCSR
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASM_SH_WATCHDOG_H */
eof
