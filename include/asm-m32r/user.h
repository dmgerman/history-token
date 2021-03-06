macro_line|#ifndef _ASM_M32R_USER_H
DECL|macro|_ASM_M32R_USER_H
mdefine_line|#define _ASM_M32R_USER_H
multiline_comment|/* $Id$ */
multiline_comment|/* orig : sh 2.4.18&n; * mod  : remove fpu registers&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * Core file format: The core file is written in such a way that gdb&n; * can understand it and provide useful information to the user (under&n; * linux we use the `trad-core&squot; bfd).&n; *&n; * The actual file contents are as follows:&n; * UPAGE: 1 page consisting of a user struct that tells gdb&n; *&t;what is present in the file.  Directly after this is a&n; *&t;copy of the task_struct, which is currently not used by gdb,&n; *&t;but it may come in handy at some point.  All of the registers&n; *&t;are stored as part of the upage.  The upage should always be&n; *&t;only one page.&n; * DATA: The data area is stored.  We use current-&gt;end_text to&n; *&t;current-&gt;brk to pick up all of the user variables, plus any memory&n; *&t;that may have been sbrk&squot;ed.  No attempt is made to determine if a&n; *&t;page is demand-zero or if a page is totally unused, we just cover&n; *&t;the entire range.  All of the addresses are rounded in such a way&n; *&t;that an integral number of pages is written.&n; * STACK: We need the stack information in order to get a meaningful&n; *&t;backtrace.  We need to write the data from usp to&n; *&t;current-&gt;start_stack, so we round each of these off in order to be&n; *&t;able to write an integer number of pages.&n; */
DECL|struct|user
r_struct
id|user
(brace
DECL|member|regs
r_struct
id|pt_regs
id|regs
suffix:semicolon
multiline_comment|/* entire machine state */
DECL|member|u_tsize
r_int
id|u_tsize
suffix:semicolon
multiline_comment|/* text size (pages) */
DECL|member|u_dsize
r_int
id|u_dsize
suffix:semicolon
multiline_comment|/* data size (pages) */
DECL|member|u_ssize
r_int
id|u_ssize
suffix:semicolon
multiline_comment|/* stack size (pages) */
DECL|member|start_code
r_int
r_int
id|start_code
suffix:semicolon
multiline_comment|/* text starting address */
DECL|member|start_data
r_int
r_int
id|start_data
suffix:semicolon
multiline_comment|/* data starting address */
DECL|member|start_stack
r_int
r_int
id|start_stack
suffix:semicolon
multiline_comment|/* stack starting address */
DECL|member|signal
r_int
r_int
id|signal
suffix:semicolon
multiline_comment|/* signal causing core dump */
DECL|member|u_ar0
r_struct
id|regs
op_star
id|u_ar0
suffix:semicolon
multiline_comment|/* help gdb find registers */
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* identifies a core file */
DECL|member|u_comm
r_char
id|u_comm
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* user command name */
)brace
suffix:semicolon
DECL|macro|NBPG
mdefine_line|#define NBPG&t;&t;&t;PAGE_SIZE
DECL|macro|UPAGES
mdefine_line|#define UPAGES&t;&t;&t;1
DECL|macro|HOST_TEXT_START_ADDR
mdefine_line|#define HOST_TEXT_START_ADDR&t;(u.start_code)
DECL|macro|HOST_DATA_START_ADDR
mdefine_line|#define HOST_DATA_START_ADDR&t;(u.start_data)
DECL|macro|HOST_STACK_END_ADDR
mdefine_line|#define HOST_STACK_END_ADDR&t;(u.start_stack + u.u_ssize * NBPG)
macro_line|#endif /* _ASM_M32R_USER_H */
eof
