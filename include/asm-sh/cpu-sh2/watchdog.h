multiline_comment|/*&n; * include/asm-sh/cpu-sh2/watchdog.h&n; *&n; * Copyright (C) 2002, 2003 Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH2_WATCHDOG_H
DECL|macro|__ASM_CPU_SH2_WATCHDOG_H
mdefine_line|#define __ASM_CPU_SH2_WATCHDOG_H
multiline_comment|/*&n; * More SH-2 brilliance .. its not good enough that we can&squot;t read&n; * and write the same sizes to WTCNT, now we have to read and write&n; * with different sizes at different addresses for WTCNT _and_ RSTCSR.&n; *&n; * At least on the bright side no one has managed to screw over WTCSR&n; * in this fashion .. yet.&n; */
multiline_comment|/* Register definitions */
DECL|macro|WTCNT
mdefine_line|#define WTCNT&t;&t;0xfffffe80
DECL|macro|WTCSR
mdefine_line|#define WTCSR&t;&t;0xfffffe80
DECL|macro|RSTCSR
mdefine_line|#define RSTCSR&t;&t;0xfffffe82
DECL|macro|WTCNT_R
mdefine_line|#define WTCNT_R&t;&t;(WTCNT + 1)
DECL|macro|RSTCSR_R
mdefine_line|#define RSTCSR_R&t;(RSTCSR + 1)
multiline_comment|/* Bit definitions */
DECL|macro|WTCSR_IOVF
mdefine_line|#define WTCSR_IOVF&t;0x80
DECL|macro|WTCSR_WT
mdefine_line|#define WTCSR_WT&t;0x40
DECL|macro|WTCSR_TME
mdefine_line|#define WTCSR_TME&t;0x20
DECL|macro|WTCSR_RSTS
mdefine_line|#define WTCSR_RSTS&t;0x00
DECL|macro|RSTCSR_RSTS
mdefine_line|#define RSTCSR_RSTS&t;0x20
multiline_comment|/**&n; * &t;sh_wdt_read_rstcsr - Read from Reset Control/Status Register&n; *&n; *&t;Reads back the RSTCSR value.&n; */
DECL|function|sh_wdt_read_rstcsr
r_static
r_inline
id|__u8
id|sh_wdt_read_rstcsr
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Same read/write brain-damage as for WTCNT here..&n;&t; */
r_return
id|ctrl_inb
c_func
(paren
id|RSTCSR_R
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * &t;sh_wdt_write_csr - Write to Reset Control/Status Register&n; *&n; * &t;@val: Value to write&n; *&n; * &t;Writes the given value @val to the lower byte of the control/status&n; * &t;register. The upper byte is set manually on each write.&n; */
DECL|function|sh_wdt_write_rstcsr
r_static
r_inline
r_void
id|sh_wdt_write_rstcsr
c_func
(paren
id|__u8
id|val
)paren
(brace
multiline_comment|/*&n;&t; * Note: Due to the brain-damaged nature of this register,&n;&t; * we can&squot;t presently touch the WOVF bit, since the upper byte&n;&t; * has to be swapped for this. So just leave it alone..&n;&t; */
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
id|RSTCSR
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASM_CPU_SH2_WATCHDOG_H */
eof
