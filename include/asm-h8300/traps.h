multiline_comment|/*&n; *  linux/include/asm-h8300/traps.h&n; *&n; *  Copyright (C) 2003 Yoshinori Sato &lt;ysato@users.sourceforge.jp&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _H8300_TRAPS_H
DECL|macro|_H8300_TRAPS_H
mdefine_line|#define _H8300_TRAPS_H
r_extern
r_void
id|system_call
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|interrupt_entry
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|trace_break
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|JMP_OP
mdefine_line|#define JMP_OP 0x5a000000
DECL|macro|JSR_OP
mdefine_line|#define JSR_OP 0x5e000000
DECL|macro|VECTOR
mdefine_line|#define VECTOR(address) ((JMP_OP)|((unsigned long)address))
DECL|macro|REDIRECT
mdefine_line|#define REDIRECT(address) ((JSR_OP)|((unsigned long)address))
DECL|macro|TRACE_VEC
mdefine_line|#define TRACE_VEC 5
DECL|macro|TRAP0_VEC
mdefine_line|#define TRAP0_VEC 8
DECL|macro|TRAP1_VEC
mdefine_line|#define TRAP1_VEC 9
DECL|macro|TRAP2_VEC
mdefine_line|#define TRAP2_VEC 10
DECL|macro|TRAP3_VEC
mdefine_line|#define TRAP3_VEC 11
macro_line|#if defined(__H8300H__)
DECL|macro|NR_TRAPS
mdefine_line|#define NR_TRAPS 12
macro_line|#endif
macro_line|#if defined(__H8300S__)
DECL|macro|NR_TRAPS
mdefine_line|#define NR_TRAPS 16
macro_line|#endif
macro_line|#endif /* _H8300_TRAPS_H */
eof
