macro_line|#ifndef __ASM_CRIS_USER_H
DECL|macro|__ASM_CRIS_USER_H
mdefine_line|#define __ASM_CRIS_USER_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * Core file format: The core file is written in such a way that gdb&n; * can understand it and provide useful information to the user (under&n; * linux we use the `trad-core&squot; bfd).  The file contents are as follows:&n; *&n; *  upage: 1 page consisting of a user struct that tells gdb&n; *&t;what is present in the file.  Directly after this is a&n; *&t;copy of the task_struct, which is currently not used by gdb,&n; *&t;but it may come in handy at some point.  All of the registers&n; *&t;are stored as part of the upage.  The upage should always be&n; *&t;only one page long.&n; *  data: The data segment follows next.  We use current-&gt;end_text to&n; *&t;current-&gt;brk to pick up all of the user variables, plus any memory&n; *&t;that may have been sbrk&squot;ed.  No attempt is made to determine if a&n; *&t;page is demand-zero or if a page is totally unused, we just cover&n; *&t;the entire range.  All of the addresses are rounded in such a way&n; *&t;that an integral number of pages is written.&n; *  stack: We need the stack information in order to get a meaningful&n; *&t;backtrace.  We need to write the data from usp to&n; *&t;current-&gt;start_stack, so we round each of these in order to be able&n; *&t;to write an integer number of pages.&n; */
multiline_comment|/* User mode registers, used for core dumps. In order to keep ELF_NGREG&n;   sensible we let all registers be 32 bits. The csr registers are included&n;   for future use. */
DECL|struct|user_regs_struct
r_struct
id|user_regs_struct
(brace
DECL|member|r0
r_int
r_int
id|r0
suffix:semicolon
multiline_comment|/* General registers. */
DECL|member|r1
r_int
r_int
id|r1
suffix:semicolon
DECL|member|r2
r_int
r_int
id|r2
suffix:semicolon
DECL|member|r3
r_int
r_int
id|r3
suffix:semicolon
DECL|member|r4
r_int
r_int
id|r4
suffix:semicolon
DECL|member|r5
r_int
r_int
id|r5
suffix:semicolon
DECL|member|r6
r_int
r_int
id|r6
suffix:semicolon
DECL|member|r7
r_int
r_int
id|r7
suffix:semicolon
DECL|member|r8
r_int
r_int
id|r8
suffix:semicolon
DECL|member|r9
r_int
r_int
id|r9
suffix:semicolon
DECL|member|r10
r_int
r_int
id|r10
suffix:semicolon
DECL|member|r11
r_int
r_int
id|r11
suffix:semicolon
DECL|member|r12
r_int
r_int
id|r12
suffix:semicolon
DECL|member|r13
r_int
r_int
id|r13
suffix:semicolon
DECL|member|sp
r_int
r_int
id|sp
suffix:semicolon
multiline_comment|/* Stack pointer. */
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
multiline_comment|/* Program counter. */
DECL|member|p0
r_int
r_int
id|p0
suffix:semicolon
multiline_comment|/* Constant zero (only 8 bits). */
DECL|member|vr
r_int
r_int
id|vr
suffix:semicolon
multiline_comment|/* Version register (only 8 bits). */
DECL|member|p2
r_int
r_int
id|p2
suffix:semicolon
multiline_comment|/* Reserved. */
DECL|member|p3
r_int
r_int
id|p3
suffix:semicolon
multiline_comment|/* Reserved. */
DECL|member|p4
r_int
r_int
id|p4
suffix:semicolon
multiline_comment|/* Constant zero (only 16 bits). */
DECL|member|ccr
r_int
r_int
id|ccr
suffix:semicolon
multiline_comment|/* Condition code register (only 16 bits). */
DECL|member|p6
r_int
r_int
id|p6
suffix:semicolon
multiline_comment|/* Reserved. */
DECL|member|mof
r_int
r_int
id|mof
suffix:semicolon
multiline_comment|/* Multiply overflow register. */
DECL|member|p8
r_int
r_int
id|p8
suffix:semicolon
multiline_comment|/* Constant zero. */
DECL|member|ibr
r_int
r_int
id|ibr
suffix:semicolon
multiline_comment|/* Not accessible. */
DECL|member|irp
r_int
r_int
id|irp
suffix:semicolon
multiline_comment|/* Not accessible. */
DECL|member|srp
r_int
r_int
id|srp
suffix:semicolon
multiline_comment|/* Subroutine return pointer. */
DECL|member|bar
r_int
r_int
id|bar
suffix:semicolon
multiline_comment|/* Not accessible. */
DECL|member|dccr
r_int
r_int
id|dccr
suffix:semicolon
multiline_comment|/* Dword condition code register. */
DECL|member|brp
r_int
r_int
id|brp
suffix:semicolon
multiline_comment|/* Not accessible. */
DECL|member|usp
r_int
r_int
id|usp
suffix:semicolon
multiline_comment|/* User-mode stack pointer. Same as sp when &n;                                   in user mode. */
DECL|member|csrinstr
r_int
r_int
id|csrinstr
suffix:semicolon
multiline_comment|/* Internal status registers. */
DECL|member|csraddr
r_int
r_int
id|csraddr
suffix:semicolon
DECL|member|csrdata
r_int
r_int
id|csrdata
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|user
r_struct
id|user
(brace
DECL|member|regs
r_struct
id|user_regs_struct
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
macro_line|#endif /* __ASM_CRIS_USER_H */
eof
