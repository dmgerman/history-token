multiline_comment|/*&n; *  include/asm-s390/user.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/usr.h&quot;&n; */
macro_line|#ifndef _S390_USER_H
DECL|macro|_S390_USER_H
mdefine_line|#define _S390_USER_H
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
multiline_comment|/* Core file format: The core file is written in such a way that gdb&n;   can understand it and provide useful information to the user (under&n;   linux we use the &squot;trad-core&squot; bfd).  There are quite a number of&n;   obstacles to being able to view the contents of the floating point&n;   registers, and until these are solved you will not be able to view the&n;   contents of them.  Actually, you can read in the core file and look at&n;   the contents of the user struct to find out what the floating point&n;   registers contain.&n;   The actual file contents are as follows:&n;   UPAGE: 1 page consisting of a user struct that tells gdb what is present&n;   in the file.  Directly after this is a copy of the task_struct, which&n;   is currently not used by gdb, but it may come in useful at some point.&n;   All of the registers are stored as part of the upage.  The upage should&n;   always be only one page.&n;   DATA: The data area is stored.  We use current-&gt;end_text to&n;   current-&gt;brk to pick up all of the user variables, plus any memory&n;   that may have been malloced.  No attempt is made to determine if a page&n;   is demand-zero or if a page is totally unused, we just cover the entire&n;   range.  All of the addresses are rounded in such a way that an integral&n;   number of pages is written.&n;   STACK: We need the stack information in order to get a meaningful&n;   backtrace.  We need to write the data from (esp) to&n;   current-&gt;start_stack, so we round each of these off in order to be able&n;   to write an integer number of pages.&n;   The minimum core file size is 3 pages, or 12288 bytes.&n;*/
multiline_comment|/*&n; * This is the old layout of &quot;struct pt_regs&quot;, and&n; * is still the layout used by user mode (the new&n; * pt_regs doesn&squot;t have all registers as the kernel&n; * doesn&squot;t use the extra segment registers)&n; */
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
multiline_comment|/* The rest of this junk is to help gdb figure out what goes where */
DECL|member|u_tsize
r_int
id|u_tsize
suffix:semicolon
multiline_comment|/* Text segment size (pages). */
DECL|member|u_dsize
r_int
id|u_dsize
suffix:semicolon
multiline_comment|/* Data segment size (pages). */
DECL|member|u_ssize
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
multiline_comment|/* Starting virtual address of stack area.&n;&t;&t;&t;        This is actually the bottom of the stack,&n;&t;&t;&t;&t;the top of the stack is always found in the&n;&t;&t;&t;&t;gprs[15] register.  */
DECL|member|signal
r_int
r_int
id|signal
suffix:semicolon
multiline_comment|/* Signal that caused the core dump. */
DECL|member|u_ar0
r_struct
id|user_regs_struct
op_star
id|u_ar0
suffix:semicolon
multiline_comment|/* Used by gdb to help find the values for */
multiline_comment|/* the registers. */
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
macro_line|#endif /* _S390_USER_H */
eof
