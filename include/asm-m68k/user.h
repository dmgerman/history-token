macro_line|#ifndef _M68K_USER_H
DECL|macro|_M68K_USER_H
mdefine_line|#define _M68K_USER_H
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* Core file format: The core file is written in such a way that gdb&n;   can understand it and provide useful information to the user (under&n;   linux we use the &squot;trad-core&squot; bfd).  There are quite a number of&n;   obstacles to being able to view the contents of the floating point&n;   registers, and until these are solved you will not be able to view the&n;   contents of them.  Actually, you can read in the core file and look at&n;   the contents of the user struct to find out what the floating point&n;   registers contain.&n;   The actual file contents are as follows:&n;   UPAGE: 1 page consisting of a user struct that tells gdb what is present&n;   in the file.  Directly after this is a copy of the task_struct, which&n;   is currently not used by gdb, but it may come in useful at some point.&n;   All of the registers are stored as part of the upage.  The upage should&n;   always be only one page.&n;   DATA: The data area is stored.  We use current-&gt;end_text to&n;   current-&gt;brk to pick up all of the user variables, plus any memory&n;   that may have been malloced.  No attempt is made to determine if a page&n;   is demand-zero or if a page is totally unused, we just cover the entire&n;   range.  All of the addresses are rounded in such a way that an integral&n;   number of pages is written.&n;   STACK: We need the stack information in order to get a meaningful&n;   backtrace.  We need to write the data from (esp) to&n;   current-&gt;start_stack, so we round each of these off in order to be able&n;   to write an integer number of pages.&n;   The minimum core file size is 3 pages, or 12288 bytes.&n;*/
DECL|struct|user_m68kfp_struct
r_struct
id|user_m68kfp_struct
(brace
DECL|member|fpregs
r_int
r_int
id|fpregs
(braket
l_int|8
op_star
l_int|3
)braket
suffix:semicolon
multiline_comment|/* fp0-fp7 registers */
DECL|member|fpcntl
r_int
r_int
id|fpcntl
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* fp control regs */
)brace
suffix:semicolon
multiline_comment|/* This is the old layout of &quot;struct pt_regs&quot; as of Linux 1.x, and&n;   is still the layout used by user (the new pt_regs doesn&squot;t have&n;   all registers). */
DECL|struct|user_regs_struct
r_struct
id|user_regs_struct
(brace
DECL|member|d1
DECL|member|d2
DECL|member|d3
DECL|member|d4
DECL|member|d5
DECL|member|d6
DECL|member|d7
r_int
id|d1
comma
id|d2
comma
id|d3
comma
id|d4
comma
id|d5
comma
id|d6
comma
id|d7
suffix:semicolon
DECL|member|a0
DECL|member|a1
DECL|member|a2
DECL|member|a3
DECL|member|a4
DECL|member|a5
DECL|member|a6
r_int
id|a0
comma
id|a1
comma
id|a2
comma
id|a3
comma
id|a4
comma
id|a5
comma
id|a6
suffix:semicolon
DECL|member|d0
r_int
id|d0
suffix:semicolon
DECL|member|usp
r_int
id|usp
suffix:semicolon
DECL|member|orig_d0
r_int
id|orig_d0
suffix:semicolon
DECL|member|stkadj
r_int
id|stkadj
suffix:semicolon
DECL|member|sr
r_int
id|sr
suffix:semicolon
DECL|member|pc
r_int
id|pc
suffix:semicolon
DECL|member|fmtvec
r_int
id|fmtvec
suffix:semicolon
DECL|member|__fill
r_int
id|__fill
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* When the kernel dumps core, it starts by dumping the user struct -&n;   this will be used by gdb to figure out where the data and stack segments&n;   are within the file, and what virtual addresses to use. */
DECL|struct|user
r_struct
id|user
(brace
multiline_comment|/* We start with the registers, to mimic the way that &quot;memory&quot; is returned&n;   from the ptrace(3,...) function.  */
DECL|member|regs
r_struct
id|user_regs_struct
id|regs
suffix:semicolon
multiline_comment|/* Where the registers are actually stored */
multiline_comment|/* ptrace does not yet supply these.  Someday.... */
DECL|member|u_fpvalid
r_int
id|u_fpvalid
suffix:semicolon
multiline_comment|/* True if math co-processor being used. */
multiline_comment|/* for this mess. Not yet used. */
DECL|member|m68kfp
r_struct
id|user_m68kfp_struct
id|m68kfp
suffix:semicolon
multiline_comment|/* Math Co-processor registers. */
multiline_comment|/* The rest of this junk is to help gdb figure out what goes where */
DECL|member|u_tsize
r_int
r_int
r_int
id|u_tsize
suffix:semicolon
multiline_comment|/* Text segment size (pages). */
DECL|member|u_dsize
r_int
r_int
r_int
id|u_dsize
suffix:semicolon
multiline_comment|/* Data segment size (pages). */
DECL|member|u_ssize
r_int
r_int
r_int
id|u_ssize
suffix:semicolon
multiline_comment|/* Stack segment size (pages). */
DECL|member|start_code
r_int
r_int
id|start_code
suffix:semicolon
multiline_comment|/* Starting virtual address of text. */
DECL|member|start_stack
r_int
r_int
id|start_stack
suffix:semicolon
multiline_comment|/* Starting virtual address of stack area.&n;&t;&t;&t;&t;   This is actually the bottom of the stack,&n;&t;&t;&t;&t;   the top of the stack is always found in the&n;&t;&t;&t;&t;   esp register.  */
DECL|member|signal
r_int
r_int
id|signal
suffix:semicolon
multiline_comment|/* Signal that caused the core dump. */
DECL|member|reserved
r_int
id|reserved
suffix:semicolon
multiline_comment|/* No longer used */
DECL|member|u_ar0
r_struct
id|user_regs_struct
op_star
id|u_ar0
suffix:semicolon
multiline_comment|/* Used by gdb to help find the values for */
multiline_comment|/* the registers. */
DECL|member|u_fpstate
r_struct
id|user_m68kfp_struct
op_star
id|u_fpstate
suffix:semicolon
multiline_comment|/* Math Co-processor pointer. */
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
multiline_comment|/* To uniquely identify a core file */
DECL|member|u_comm
r_char
id|u_comm
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* User command that was responsible */
)brace
suffix:semicolon
DECL|macro|NBPG
mdefine_line|#define NBPG PAGE_SIZE
DECL|macro|UPAGES
mdefine_line|#define UPAGES 1
DECL|macro|HOST_TEXT_START_ADDR
mdefine_line|#define HOST_TEXT_START_ADDR (u.start_code)
DECL|macro|HOST_STACK_END_ADDR
mdefine_line|#define HOST_STACK_END_ADDR (u.start_stack + u.u_ssize * NBPG)
macro_line|#endif
eof
