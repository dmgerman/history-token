multiline_comment|/*&n; *  linux/fs/binfmt_aout.c&n; *&n; *  Copyright (C) 1991, 1992, 1996  Linus Torvalds&n; *&n; *  Hacked a bit by DaveM to make it work with 32-bit SunOS&n; *  binaries on the sparc64 port.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
r_static
r_int
id|load_aout32_binary
c_func
(paren
r_struct
id|linux_binprm
op_star
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_int
id|load_aout32_library
c_func
(paren
r_struct
id|file
op_star
)paren
suffix:semicolon
r_static
r_int
id|aout32_core_dump
c_func
(paren
r_int
id|signr
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_extern
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_struct
id|user
op_star
)paren
suffix:semicolon
DECL|variable|aout32_format
r_static
r_struct
id|linux_binfmt
id|aout32_format
op_assign
(brace
l_int|NULL
comma
id|THIS_MODULE
comma
id|load_aout32_binary
comma
id|load_aout32_library
comma
id|aout32_core_dump
comma
id|PAGE_SIZE
)brace
suffix:semicolon
DECL|function|set_brk
r_static
r_void
id|set_brk
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
id|start
op_assign
id|PAGE_ALIGN
c_func
(paren
id|start
)paren
suffix:semicolon
id|end
op_assign
id|PAGE_ALIGN
c_func
(paren
id|end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|end
op_le
id|start
)paren
r_return
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|do_brk
c_func
(paren
id|start
comma
id|end
op_minus
id|start
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the only things you should do on a core-file: use only these&n; * macros to write out all the necessary info.&n; */
DECL|function|dump_write
r_static
r_int
id|dump_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_void
op_star
id|addr
comma
r_int
id|nr
)paren
(brace
r_return
id|file-&gt;f_op
op_member_access_from_pointer
id|write
c_func
(paren
id|file
comma
id|addr
comma
id|nr
comma
op_amp
id|file-&gt;f_pos
)paren
op_eq
id|nr
suffix:semicolon
)brace
DECL|macro|DUMP_WRITE
mdefine_line|#define DUMP_WRITE(addr, nr)&t;&bslash;&n;&t;if (!dump_write(file, (void *)(addr), (nr))) &bslash;&n;&t;&t;goto end_coredump;
DECL|macro|DUMP_SEEK
mdefine_line|#define DUMP_SEEK(offset) &bslash;&n;if (file-&gt;f_op-&gt;llseek) { &bslash;&n;&t;if (file-&gt;f_op-&gt;llseek(file,(offset),0) != (offset)) &bslash;&n; &t;&t;goto end_coredump; &bslash;&n;} else file-&gt;f_pos = (offset)
multiline_comment|/*&n; * Routine writes a core dump image in the current directory.&n; * Currently only a stub-function.&n; *&n; * Note that setuid/setgid files won&squot;t make a core-dump if the uid/gid&n; * changed due to the set[u|g]id. It&squot;s enforced by the &quot;current-&gt;mm-&gt;dumpable&quot;&n; * field, which also makes sure the core-dumps won&squot;t be recursive if the&n; * dumping of the process results in another error..&n; */
DECL|function|aout32_core_dump
r_static
r_int
id|aout32_core_dump
c_func
(paren
r_int
id|signr
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|file
op_star
id|file
)paren
(brace
id|mm_segment_t
id|fs
suffix:semicolon
r_int
id|has_dumped
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|dump_start
comma
id|dump_size
suffix:semicolon
r_struct
id|user
id|dump
suffix:semicolon
DECL|macro|START_DATA
macro_line|#       define START_DATA(u)    (u.u_tsize)
DECL|macro|START_STACK
macro_line|#       define START_STACK(u)   ((regs-&gt;u_regs[UREG_FP]) &amp; ~(PAGE_SIZE - 1))
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|has_dumped
op_assign
l_int|1
suffix:semicolon
id|current-&gt;flags
op_or_assign
id|PF_DUMPCORE
suffix:semicolon
id|strncpy
c_func
(paren
id|dump.u_comm
comma
id|current-&gt;comm
comma
r_sizeof
(paren
id|dump.u_comm
)paren
)paren
suffix:semicolon
id|dump.signal
op_assign
id|signr
suffix:semicolon
id|dump_thread
c_func
(paren
id|regs
comma
op_amp
id|dump
)paren
suffix:semicolon
multiline_comment|/* If the size of the dump file exceeds the rlimit, then see what would happen&n;   if we wrote the stack, but not the data area.  */
r_if
c_cond
(paren
(paren
id|dump.u_dsize
op_plus
id|dump.u_ssize
)paren
OG
id|current-&gt;signal-&gt;rlim
(braket
id|RLIMIT_CORE
)braket
dot
id|rlim_cur
)paren
id|dump.u_dsize
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Make sure we have enough room to write the stack and data areas. */
r_if
c_cond
(paren
(paren
id|dump.u_ssize
)paren
OG
id|current-&gt;signal-&gt;rlim
(braket
id|RLIMIT_CORE
)braket
dot
id|rlim_cur
)paren
id|dump.u_ssize
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* make sure we actually have a data and stack area to dump */
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
id|__user
op_star
)paren
id|START_DATA
c_func
(paren
id|dump
)paren
comma
id|dump.u_dsize
)paren
)paren
id|dump.u_dsize
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
id|__user
op_star
)paren
id|START_STACK
c_func
(paren
id|dump
)paren
comma
id|dump.u_ssize
)paren
)paren
id|dump.u_ssize
op_assign
l_int|0
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
multiline_comment|/* struct user */
id|DUMP_WRITE
c_func
(paren
op_amp
id|dump
comma
r_sizeof
(paren
id|dump
)paren
)paren
suffix:semicolon
multiline_comment|/* now we start writing out the user space info */
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
multiline_comment|/* Dump the data area */
r_if
c_cond
(paren
id|dump.u_dsize
op_ne
l_int|0
)paren
(brace
id|dump_start
op_assign
id|START_DATA
c_func
(paren
id|dump
)paren
suffix:semicolon
id|dump_size
op_assign
id|dump.u_dsize
suffix:semicolon
id|DUMP_WRITE
c_func
(paren
id|dump_start
comma
id|dump_size
)paren
suffix:semicolon
)brace
multiline_comment|/* Now prepare to dump the stack area */
r_if
c_cond
(paren
id|dump.u_ssize
op_ne
l_int|0
)paren
(brace
id|dump_start
op_assign
id|START_STACK
c_func
(paren
id|dump
)paren
suffix:semicolon
id|dump_size
op_assign
id|dump.u_ssize
suffix:semicolon
id|DUMP_WRITE
c_func
(paren
id|dump_start
comma
id|dump_size
)paren
suffix:semicolon
)brace
multiline_comment|/* Finally dump the task struct.  Not be used by gdb, but could be useful */
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|DUMP_WRITE
c_func
(paren
id|current
comma
r_sizeof
(paren
op_star
id|current
)paren
)paren
suffix:semicolon
id|end_coredump
suffix:colon
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
r_return
id|has_dumped
suffix:semicolon
)brace
multiline_comment|/*&n; * create_aout32_tables() parses the env- and arg-strings in new user&n; * memory and creates the pointer tables from them, and puts their&n; * addresses on the &quot;stack&quot;, returning the new stack pointer value.&n; */
DECL|function|create_aout32_tables
r_static
id|u32
id|__user
op_star
id|create_aout32_tables
c_func
(paren
r_char
id|__user
op_star
id|p
comma
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
id|u32
id|__user
op_star
id|argv
suffix:semicolon
id|u32
id|__user
op_star
id|envp
suffix:semicolon
id|u32
id|__user
op_star
id|sp
suffix:semicolon
r_int
id|argc
op_assign
id|bprm-&gt;argc
suffix:semicolon
r_int
id|envc
op_assign
id|bprm-&gt;envc
suffix:semicolon
id|sp
op_assign
(paren
id|u32
id|__user
op_star
)paren
(paren
(paren
op_minus
(paren
r_int
r_int
)paren
r_sizeof
(paren
r_char
op_star
)paren
)paren
op_amp
(paren
r_int
r_int
)paren
id|p
)paren
suffix:semicolon
multiline_comment|/* This imposes the proper stack alignment for a new process. */
id|sp
op_assign
(paren
id|u32
id|__user
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|sp
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|envc
op_plus
id|argc
op_plus
l_int|3
)paren
op_amp
l_int|1
)paren
op_decrement
id|sp
suffix:semicolon
id|sp
op_sub_assign
id|envc
op_plus
l_int|1
suffix:semicolon
id|envp
op_assign
id|sp
suffix:semicolon
id|sp
op_sub_assign
id|argc
op_plus
l_int|1
suffix:semicolon
id|argv
op_assign
id|sp
suffix:semicolon
id|put_user
c_func
(paren
id|argc
comma
op_decrement
id|sp
)paren
suffix:semicolon
id|current-&gt;mm-&gt;arg_start
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
r_while
c_loop
(paren
id|argc
op_decrement
OG
l_int|0
)paren
(brace
r_char
id|c
suffix:semicolon
id|put_user
c_func
(paren
(paren
(paren
id|u32
)paren
(paren
r_int
r_int
)paren
(paren
id|p
)paren
)paren
comma
id|argv
op_increment
)paren
suffix:semicolon
r_do
(brace
id|get_user
c_func
(paren
id|c
comma
id|p
op_increment
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|c
)paren
suffix:semicolon
)brace
id|put_user
c_func
(paren
l_int|NULL
comma
id|argv
)paren
suffix:semicolon
id|current-&gt;mm-&gt;arg_end
op_assign
id|current-&gt;mm-&gt;env_start
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
r_while
c_loop
(paren
id|envc
op_decrement
OG
l_int|0
)paren
(brace
r_char
id|c
suffix:semicolon
id|put_user
c_func
(paren
(paren
(paren
id|u32
)paren
(paren
r_int
r_int
)paren
(paren
id|p
)paren
)paren
comma
id|envp
op_increment
)paren
suffix:semicolon
r_do
(brace
id|get_user
c_func
(paren
id|c
comma
id|p
op_increment
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|c
)paren
suffix:semicolon
)brace
id|put_user
c_func
(paren
l_int|NULL
comma
id|envp
)paren
suffix:semicolon
id|current-&gt;mm-&gt;env_end
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
r_return
id|sp
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the functions used to load a.out style executables and shared&n; * libraries.  There is no binary dependent code anywhere else.&n; */
DECL|function|load_aout32_binary
r_static
r_int
id|load_aout32_binary
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|exec
id|ex
suffix:semicolon
r_int
r_int
id|error
suffix:semicolon
r_int
r_int
id|fd_offset
suffix:semicolon
r_int
r_int
id|rlim
suffix:semicolon
r_int
r_int
id|orig_thr_flags
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|ex
op_assign
op_star
(paren
(paren
r_struct
id|exec
op_star
)paren
id|bprm-&gt;buf
)paren
suffix:semicolon
multiline_comment|/* exec-header */
r_if
c_cond
(paren
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|ZMAGIC
op_logical_and
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|OMAGIC
op_logical_and
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|QMAGIC
op_logical_and
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|NMAGIC
)paren
op_logical_or
id|N_TRSIZE
c_func
(paren
id|ex
)paren
op_logical_or
id|N_DRSIZE
c_func
(paren
id|ex
)paren
op_logical_or
id|bprm-&gt;file-&gt;f_dentry-&gt;d_inode-&gt;i_size
OL
id|ex.a_text
op_plus
id|ex.a_data
op_plus
id|N_SYMSIZE
c_func
(paren
id|ex
)paren
op_plus
id|N_TXTOFF
c_func
(paren
id|ex
)paren
)paren
(brace
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
id|fd_offset
op_assign
id|N_TXTOFF
c_func
(paren
id|ex
)paren
suffix:semicolon
multiline_comment|/* Check initial limits. This avoids letting people circumvent&n;&t; * size limits imposed on them by creating programs with large&n;&t; * arrays in the data or bss.&n;&t; */
id|rlim
op_assign
id|current-&gt;signal-&gt;rlim
(braket
id|RLIMIT_DATA
)braket
dot
id|rlim_cur
suffix:semicolon
r_if
c_cond
(paren
id|rlim
op_ge
id|RLIM_INFINITY
)paren
id|rlim
op_assign
op_complement
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ex.a_data
op_plus
id|ex.a_bss
OG
id|rlim
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Flush all traces of the currently running executable */
id|retval
op_assign
id|flush_old_exec
c_func
(paren
id|bprm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
multiline_comment|/* OK, This is the point of no return */
id|set_personality
c_func
(paren
id|PER_SUNOS
)paren
suffix:semicolon
id|current-&gt;mm-&gt;end_code
op_assign
id|ex.a_text
op_plus
(paren
id|current-&gt;mm-&gt;start_code
op_assign
id|N_TXTADDR
c_func
(paren
id|ex
)paren
)paren
suffix:semicolon
id|current-&gt;mm-&gt;end_data
op_assign
id|ex.a_data
op_plus
(paren
id|current-&gt;mm-&gt;start_data
op_assign
id|N_DATADDR
c_func
(paren
id|ex
)paren
)paren
suffix:semicolon
id|current-&gt;mm-&gt;brk
op_assign
id|ex.a_bss
op_plus
(paren
id|current-&gt;mm-&gt;start_brk
op_assign
id|N_BSSADDR
c_func
(paren
id|ex
)paren
)paren
suffix:semicolon
id|set_mm_counter
c_func
(paren
id|current-&gt;mm
comma
id|rss
comma
l_int|0
)paren
suffix:semicolon
id|current-&gt;mm-&gt;mmap
op_assign
l_int|NULL
suffix:semicolon
id|compute_creds
c_func
(paren
id|bprm
)paren
suffix:semicolon
id|current-&gt;flags
op_and_assign
op_complement
id|PF_FORKNOEXEC
suffix:semicolon
r_if
c_cond
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_eq
id|NMAGIC
)paren
(brace
id|loff_t
id|pos
op_assign
id|fd_offset
suffix:semicolon
multiline_comment|/* Fuck me plenty... */
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|error
op_assign
id|do_brk
c_func
(paren
id|N_TXTADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_text
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|bprm-&gt;file-&gt;f_op
op_member_access_from_pointer
id|read
c_func
(paren
id|bprm-&gt;file
comma
(paren
r_char
id|__user
op_star
)paren
id|N_TXTADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_text
comma
op_amp
id|pos
)paren
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|error
op_assign
id|do_brk
c_func
(paren
id|N_DATADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_data
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|bprm-&gt;file-&gt;f_op
op_member_access_from_pointer
id|read
c_func
(paren
id|bprm-&gt;file
comma
(paren
r_char
id|__user
op_star
)paren
id|N_DATADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_data
comma
op_amp
id|pos
)paren
suffix:semicolon
r_goto
id|beyond_if
suffix:semicolon
)brace
r_if
c_cond
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_eq
id|OMAGIC
)paren
(brace
id|loff_t
id|pos
op_assign
id|fd_offset
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|do_brk
c_func
(paren
id|N_TXTADDR
c_func
(paren
id|ex
)paren
op_amp
id|PAGE_MASK
comma
id|ex.a_text
op_plus
id|ex.a_data
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|bprm-&gt;file-&gt;f_op
op_member_access_from_pointer
id|read
c_func
(paren
id|bprm-&gt;file
comma
(paren
r_char
id|__user
op_star
)paren
id|N_TXTADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_text
op_plus
id|ex.a_data
comma
op_amp
id|pos
)paren
suffix:semicolon
)brace
r_else
(brace
r_static
r_int
r_int
id|error_time
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ex.a_text
op_amp
l_int|0xfff
op_logical_or
id|ex.a_data
op_amp
l_int|0xfff
)paren
op_logical_and
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|NMAGIC
)paren
op_logical_and
(paren
id|jiffies
op_minus
id|error_time
)paren
OG
l_int|5
op_star
id|HZ
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;executable not page aligned&bslash;n&quot;
)paren
suffix:semicolon
id|error_time
op_assign
id|jiffies
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|bprm-&gt;file-&gt;f_op-&gt;mmap
)paren
(brace
id|loff_t
id|pos
op_assign
id|fd_offset
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|do_brk
c_func
(paren
l_int|0
comma
id|ex.a_text
op_plus
id|ex.a_data
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|bprm-&gt;file-&gt;f_op
op_member_access_from_pointer
id|read
c_func
(paren
id|bprm-&gt;file
comma
(paren
r_char
id|__user
op_star
)paren
id|N_TXTADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_text
op_plus
id|ex.a_data
comma
op_amp
id|pos
)paren
suffix:semicolon
r_goto
id|beyond_if
suffix:semicolon
)brace
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|error
op_assign
id|do_mmap
c_func
(paren
id|bprm-&gt;file
comma
id|N_TXTADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_text
comma
id|PROT_READ
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
op_or
id|MAP_DENYWRITE
op_or
id|MAP_EXECUTABLE
comma
id|fd_offset
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
id|N_TXTADDR
c_func
(paren
id|ex
)paren
)paren
(brace
id|send_sig
c_func
(paren
id|SIGKILL
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|error
op_assign
id|do_mmap
c_func
(paren
id|bprm-&gt;file
comma
id|N_DATADDR
c_func
(paren
id|ex
)paren
comma
id|ex.a_data
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
op_or
id|MAP_DENYWRITE
op_or
id|MAP_EXECUTABLE
comma
id|fd_offset
op_plus
id|ex.a_text
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
id|N_DATADDR
c_func
(paren
id|ex
)paren
)paren
(brace
id|send_sig
c_func
(paren
id|SIGKILL
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
)brace
id|beyond_if
suffix:colon
id|set_binfmt
c_func
(paren
op_amp
id|aout32_format
)paren
suffix:semicolon
id|set_brk
c_func
(paren
id|current-&gt;mm-&gt;start_brk
comma
id|current-&gt;mm-&gt;brk
)paren
suffix:semicolon
multiline_comment|/* Make sure STACK_TOP returns the right thing.  */
id|orig_thr_flags
op_assign
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
suffix:semicolon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
op_or_assign
id|_TIF_32BIT
suffix:semicolon
id|retval
op_assign
id|setup_arg_pages
c_func
(paren
id|bprm
comma
id|STACK_TOP
comma
id|EXSTACK_DEFAULT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
op_assign
id|orig_thr_flags
suffix:semicolon
multiline_comment|/* Someone check-me: is this error path enough? */
id|send_sig
c_func
(paren
id|SIGKILL
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
id|current-&gt;mm-&gt;start_stack
op_assign
(paren
r_int
r_int
)paren
id|create_aout32_tables
c_func
(paren
(paren
r_char
id|__user
op_star
)paren
id|bprm-&gt;p
comma
id|bprm
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|orig_thr_flags
op_amp
id|_TIF_32BIT
)paren
)paren
(brace
r_int
r_int
id|pgd_cache
op_assign
id|get_pgd_cache
c_func
(paren
id|current-&gt;mm-&gt;pgd
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stxa&bslash;t%0, [%1] %2&bslash;n&bslash;t&quot;
l_string|&quot;membar #Sync&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|pgd_cache
)paren
comma
l_string|&quot;r&quot;
(paren
id|TSB_REG
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_DMMU
)paren
)paren
suffix:semicolon
)brace
id|start_thread32
c_func
(paren
id|regs
comma
id|ex.a_entry
comma
id|current-&gt;mm-&gt;start_stack
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
id|send_sig
c_func
(paren
id|SIGTRAP
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* N.B. Move to .h file and use code in fs/binfmt_aout.c? */
DECL|function|load_aout32_library
r_static
r_int
id|load_aout32_library
c_func
(paren
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
r_int
id|bss
comma
id|start_addr
comma
id|len
suffix:semicolon
r_int
r_int
id|error
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_struct
id|exec
id|ex
suffix:semicolon
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
id|error
op_assign
id|kernel_read
c_func
(paren
id|file
comma
l_int|0
comma
(paren
r_char
op_star
)paren
op_amp
id|ex
comma
r_sizeof
(paren
id|ex
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
r_sizeof
(paren
id|ex
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* We come in here for the regular a.out style of shared libraries */
r_if
c_cond
(paren
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|ZMAGIC
op_logical_and
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_ne
id|QMAGIC
)paren
op_logical_or
id|N_TRSIZE
c_func
(paren
id|ex
)paren
op_logical_or
id|N_DRSIZE
c_func
(paren
id|ex
)paren
op_logical_or
(paren
(paren
id|ex.a_entry
op_amp
l_int|0xfff
)paren
op_logical_and
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_eq
id|ZMAGIC
)paren
op_logical_or
id|inode-&gt;i_size
OL
id|ex.a_text
op_plus
id|ex.a_data
op_plus
id|N_SYMSIZE
c_func
(paren
id|ex
)paren
op_plus
id|N_TXTOFF
c_func
(paren
id|ex
)paren
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|N_MAGIC
c_func
(paren
id|ex
)paren
op_eq
id|ZMAGIC
op_logical_and
id|N_TXTOFF
c_func
(paren
id|ex
)paren
op_logical_and
(paren
id|N_TXTOFF
c_func
(paren
id|ex
)paren
OL
id|inode-&gt;i_sb-&gt;s_blocksize
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;N_TXTOFF &lt; BLOCK_SIZE. Please convert library&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|N_FLAGS
c_func
(paren
id|ex
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* For  QMAGIC, the starting address is 0x20 into the page.  We mask&n;&t;   this off to get the starting address for the page */
id|start_addr
op_assign
id|ex.a_entry
op_amp
l_int|0xfffff000
suffix:semicolon
multiline_comment|/* Now use mmap to map the library into memory. */
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|error
op_assign
id|do_mmap
c_func
(paren
id|file
comma
id|start_addr
comma
id|ex.a_text
op_plus
id|ex.a_data
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
op_or
id|MAP_DENYWRITE
comma
id|N_TXTOFF
c_func
(paren
id|ex
)paren
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|retval
op_assign
id|error
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
id|start_addr
)paren
r_goto
id|out
suffix:semicolon
id|len
op_assign
id|PAGE_ALIGN
c_func
(paren
id|ex.a_text
op_plus
id|ex.a_data
)paren
suffix:semicolon
id|bss
op_assign
id|ex.a_text
op_plus
id|ex.a_data
op_plus
id|ex.a_bss
suffix:semicolon
r_if
c_cond
(paren
id|bss
OG
id|len
)paren
(brace
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|error
op_assign
id|do_brk
c_func
(paren
id|start_addr
op_plus
id|len
comma
id|bss
op_minus
id|len
)paren
suffix:semicolon
id|up_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|retval
op_assign
id|error
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
id|start_addr
op_plus
id|len
)paren
r_goto
id|out
suffix:semicolon
)brace
id|retval
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|init_aout32_binfmt
r_static
r_int
id|__init
id|init_aout32_binfmt
c_func
(paren
r_void
)paren
(brace
r_return
id|register_binfmt
c_func
(paren
op_amp
id|aout32_format
)paren
suffix:semicolon
)brace
DECL|function|exit_aout32_binfmt
r_static
r_void
id|__exit
id|exit_aout32_binfmt
c_func
(paren
r_void
)paren
(brace
id|unregister_binfmt
c_func
(paren
op_amp
id|aout32_format
)paren
suffix:semicolon
)brace
DECL|variable|init_aout32_binfmt
id|module_init
c_func
(paren
id|init_aout32_binfmt
)paren
suffix:semicolon
DECL|variable|exit_aout32_binfmt
id|module_exit
c_func
(paren
id|exit_aout32_binfmt
)paren
suffix:semicolon
eof
