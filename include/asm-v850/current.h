multiline_comment|/*&n; * include/asm-v850/current.h -- Current task&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_CURRENT_H__
DECL|macro|__V850_CURRENT_H__
mdefine_line|#define __V850_CURRENT_H__
macro_line|#include &lt;asm/macrology.h&gt;
macro_line|#include &lt;asm/thread_info.h&gt;
multiline_comment|/* Register used to hold the current task pointer while in the kernel.&n;   Any `call clobbered&squot; register without a special meaning should be OK,&n;   but check asm/v850/kernel/entry.S to be sure.  */
DECL|macro|CURRENT_TASK_REGNUM
mdefine_line|#define CURRENT_TASK_REGNUM&t;16
DECL|macro|CURRENT_TASK
mdefine_line|#define CURRENT_TASK &t;&t;macrology_paste (r, CURRENT_TASK_REGNUM)
macro_line|#ifdef __ASSEMBLY__
multiline_comment|/* Put a pointer to the current task structure into REG.  */
DECL|macro|GET_CURRENT_TASK
mdefine_line|#define GET_CURRENT_TASK(reg)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;GET_CURRENT_THREAD(reg);&t;&t;&t;&t;&t;&bslash;&n;&t;ld.w&t;TI_TASK[reg], reg
macro_line|#else /* !__ASSEMBLY__ */
multiline_comment|/* A pointer to the current task.  */
r_register
r_struct
id|task_struct
op_star
id|current
"&bslash;"
id|__asm__
(paren
id|macrology_stringify
(paren
id|CURRENT_TASK
)paren
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _V850_CURRENT_H */
eof
