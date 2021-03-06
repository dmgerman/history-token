multiline_comment|/*&n; * linux/fs/binfmt_som.c&n; *&n; * These are the functions used to load SOM format executables as used&n; * by HP-UX.  &n; *&n; * Copyright 1999 Matthew Wilcox &lt;willy@bofh.ai&gt;&n; * based on binfmt_elf which is&n; * Copyright 1993, 1994: Eric Youngdale (ericy@cais.com).&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/som.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
r_static
r_int
id|load_som_binary
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
suffix:semicolon
r_static
r_int
id|load_som_library
c_func
(paren
r_struct
id|file
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * If we don&squot;t support core dumping, then supply a NULL so we&n; * don&squot;t even try.&n; */
macro_line|#if 0
r_static
r_int
id|som_core_dump
c_func
(paren
r_int
id|signr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#else
DECL|macro|som_core_dump
mdefine_line|#define som_core_dump&t;NULL
macro_line|#endif
DECL|macro|SOM_PAGESTART
mdefine_line|#define SOM_PAGESTART(_v) ((_v) &amp; ~(unsigned long)(SOM_PAGESIZE-1))
DECL|macro|SOM_PAGEOFFSET
mdefine_line|#define SOM_PAGEOFFSET(_v) ((_v) &amp; (SOM_PAGESIZE-1))
DECL|macro|SOM_PAGEALIGN
mdefine_line|#define SOM_PAGEALIGN(_v) (((_v) + SOM_PAGESIZE - 1) &amp; ~(SOM_PAGESIZE - 1))
DECL|variable|som_format
r_static
r_struct
id|linux_binfmt
id|som_format
op_assign
(brace
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|load_binary
op_assign
id|load_som_binary
comma
dot
id|load_shlib
op_assign
id|load_som_library
comma
dot
id|core_dump
op_assign
id|som_core_dump
comma
dot
id|min_coredump
op_assign
id|SOM_PAGESIZE
)brace
suffix:semicolon
multiline_comment|/*&n; * create_som_tables() parses the env- and arg-strings in new user&n; * memory and creates the pointer tables from them, and puts their&n; * addresses on the &quot;stack&quot;, returning the new stack pointer value.&n; */
DECL|function|create_som_tables
r_static
r_void
id|create_som_tables
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
r_char
op_star
op_star
id|argv
comma
op_star
op_star
id|envp
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
r_int
r_int
id|p
suffix:semicolon
r_int
r_int
op_star
id|sp
suffix:semicolon
multiline_comment|/* Word-align the stack pointer */
id|sp
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
(paren
id|bprm-&gt;p
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
)paren
suffix:semicolon
id|envp
op_assign
(paren
r_char
op_star
op_star
)paren
id|sp
suffix:semicolon
id|sp
op_add_assign
id|envc
op_plus
l_int|1
suffix:semicolon
id|argv
op_assign
(paren
r_char
op_star
op_star
)paren
id|sp
suffix:semicolon
id|sp
op_add_assign
id|argc
op_plus
l_int|1
suffix:semicolon
id|__put_user
c_func
(paren
(paren
r_int
r_int
)paren
id|envp
comma
op_increment
id|sp
)paren
suffix:semicolon
id|__put_user
c_func
(paren
(paren
r_int
r_int
)paren
id|argv
comma
op_increment
id|sp
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|argc
comma
op_increment
id|sp
)paren
suffix:semicolon
id|bprm-&gt;p
op_assign
(paren
r_int
r_int
)paren
id|sp
suffix:semicolon
id|p
op_assign
id|current-&gt;mm-&gt;arg_start
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
id|__put_user
c_func
(paren
(paren
r_char
op_star
)paren
id|p
comma
id|argv
op_increment
)paren
suffix:semicolon
id|p
op_add_assign
id|strlen_user
c_func
(paren
(paren
r_char
op_star
)paren
id|p
)paren
suffix:semicolon
)brace
id|__put_user
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
id|__put_user
c_func
(paren
(paren
r_char
op_star
)paren
id|p
comma
id|envp
op_increment
)paren
suffix:semicolon
id|p
op_add_assign
id|strlen_user
c_func
(paren
(paren
r_char
op_star
)paren
id|p
)paren
suffix:semicolon
)brace
id|__put_user
c_func
(paren
l_int|NULL
comma
id|envp
)paren
suffix:semicolon
id|current-&gt;mm-&gt;env_end
op_assign
id|p
suffix:semicolon
)brace
DECL|function|check_som_header
r_static
r_int
id|check_som_header
c_func
(paren
r_struct
id|som_hdr
op_star
id|som_ex
)paren
(brace
r_int
op_star
id|buf
op_assign
(paren
r_int
op_star
)paren
id|som_ex
suffix:semicolon
r_int
id|i
comma
id|ck
suffix:semicolon
r_if
c_cond
(paren
id|som_ex-&gt;system_id
op_ne
id|SOM_SID_PARISC_1_0
op_logical_and
id|som_ex-&gt;system_id
op_ne
id|SOM_SID_PARISC_1_1
op_logical_and
id|som_ex-&gt;system_id
op_ne
id|SOM_SID_PARISC_2_0
)paren
r_return
op_minus
id|ENOEXEC
suffix:semicolon
r_if
c_cond
(paren
id|som_ex-&gt;a_magic
op_ne
id|SOM_EXEC_NONSHARE
op_logical_and
id|som_ex-&gt;a_magic
op_ne
id|SOM_EXEC_SHARE
op_logical_and
id|som_ex-&gt;a_magic
op_ne
id|SOM_EXEC_DEMAND
)paren
r_return
op_minus
id|ENOEXEC
suffix:semicolon
r_if
c_cond
(paren
id|som_ex-&gt;version_id
op_ne
id|SOM_ID_OLD
op_logical_and
id|som_ex-&gt;version_id
op_ne
id|SOM_ID_NEW
)paren
r_return
op_minus
id|ENOEXEC
suffix:semicolon
id|ck
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
id|i
op_increment
)paren
id|ck
op_xor_assign
id|buf
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ck
op_ne
l_int|0
)paren
r_return
op_minus
id|ENOEXEC
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|map_som_binary
r_static
r_int
id|map_som_binary
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_struct
id|som_exec_auxhdr
op_star
id|hpuxhdr
)paren
(brace
r_int
r_int
id|code_start
comma
id|code_size
comma
id|data_start
comma
id|data_size
suffix:semicolon
r_int
r_int
id|bss_start
comma
id|som_brk
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
id|prot
op_assign
id|PROT_READ
op_or
id|PROT_EXEC
suffix:semicolon
r_int
id|flags
op_assign
id|MAP_FIXED
op_or
id|MAP_PRIVATE
op_or
id|MAP_DENYWRITE
op_or
id|MAP_EXECUTABLE
suffix:semicolon
id|mm_segment_t
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|code_start
op_assign
id|SOM_PAGESTART
c_func
(paren
id|hpuxhdr-&gt;exec_tmem
)paren
suffix:semicolon
id|code_size
op_assign
id|SOM_PAGEALIGN
c_func
(paren
id|hpuxhdr-&gt;exec_tsize
)paren
suffix:semicolon
id|current-&gt;mm-&gt;start_code
op_assign
id|code_start
suffix:semicolon
id|current-&gt;mm-&gt;end_code
op_assign
id|code_start
op_plus
id|code_size
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|retval
op_assign
id|do_mmap
c_func
(paren
id|file
comma
id|code_start
comma
id|code_size
comma
id|prot
comma
id|flags
comma
id|SOM_PAGESTART
c_func
(paren
id|hpuxhdr-&gt;exec_tfile
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
r_if
c_cond
(paren
id|retval
template_param
op_minus
l_int|1024
)paren
r_goto
id|out
suffix:semicolon
id|data_start
op_assign
id|SOM_PAGESTART
c_func
(paren
id|hpuxhdr-&gt;exec_dmem
)paren
suffix:semicolon
id|data_size
op_assign
id|SOM_PAGEALIGN
c_func
(paren
id|hpuxhdr-&gt;exec_dsize
)paren
suffix:semicolon
id|current-&gt;mm-&gt;start_data
op_assign
id|data_start
suffix:semicolon
id|current-&gt;mm-&gt;end_data
op_assign
id|bss_start
op_assign
id|data_start
op_plus
id|data_size
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|retval
op_assign
id|do_mmap
c_func
(paren
id|file
comma
id|data_start
comma
id|data_size
comma
id|prot
op_or
id|PROT_WRITE
comma
id|flags
comma
id|SOM_PAGESTART
c_func
(paren
id|hpuxhdr-&gt;exec_dfile
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
r_if
c_cond
(paren
id|retval
template_param
op_minus
l_int|1024
)paren
r_goto
id|out
suffix:semicolon
id|som_brk
op_assign
id|bss_start
op_plus
id|SOM_PAGEALIGN
c_func
(paren
id|hpuxhdr-&gt;exec_bsize
)paren
suffix:semicolon
id|current-&gt;mm-&gt;start_brk
op_assign
id|current-&gt;mm-&gt;brk
op_assign
id|som_brk
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|retval
op_assign
id|do_mmap
c_func
(paren
l_int|NULL
comma
id|bss_start
comma
id|som_brk
op_minus
id|bss_start
comma
id|prot
op_or
id|PROT_WRITE
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
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
id|retval
OG
l_int|0
op_logical_or
id|retval
OL
op_minus
l_int|1024
)paren
id|retval
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the functions used to load SOM executables and shared&n; * libraries.  There is no binary dependent code anywhere else.&n; */
r_static
r_int
DECL|function|load_som_binary
id|load_som_binary
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
r_int
id|som_exec_fileno
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
r_int
id|som_entry
suffix:semicolon
r_struct
id|som_hdr
op_star
id|som_ex
suffix:semicolon
r_struct
id|som_exec_auxhdr
op_star
id|hpuxhdr
suffix:semicolon
multiline_comment|/* Get the exec-header */
id|som_ex
op_assign
(paren
r_struct
id|som_hdr
op_star
)paren
id|bprm-&gt;buf
suffix:semicolon
id|retval
op_assign
id|check_som_header
c_func
(paren
id|som_ex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Now read in the auxiliary header information */
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|size
op_assign
id|som_ex-&gt;aux_header_size
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|SOM_PAGESIZE
)paren
r_goto
id|out
suffix:semicolon
id|hpuxhdr
op_assign
(paren
r_struct
id|som_exec_auxhdr
op_star
)paren
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hpuxhdr
)paren
r_goto
id|out
suffix:semicolon
id|retval
op_assign
id|kernel_read
c_func
(paren
id|bprm-&gt;file
comma
id|som_ex-&gt;aux_header_location
comma
(paren
r_char
op_star
)paren
id|hpuxhdr
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|out_free
suffix:semicolon
macro_line|#error &quot;Fix security hole before enabling me&quot;
id|retval
op_assign
id|get_unused_fd
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|out_free
suffix:semicolon
id|get_file
c_func
(paren
id|bprm-&gt;file
)paren
suffix:semicolon
id|fd_install
c_func
(paren
id|som_exec_fileno
op_assign
id|retval
comma
id|bprm-&gt;file
)paren
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
r_goto
id|out_free
suffix:semicolon
multiline_comment|/* OK, This is the point of no return */
id|current-&gt;flags
op_and_assign
op_complement
id|PF_FORKNOEXEC
suffix:semicolon
id|current-&gt;personality
op_assign
id|PER_HPUX
suffix:semicolon
multiline_comment|/* Set the task size for HP-UX processes such that&n;&t; * the gateway page is outside the address space.&n;&t; * This can be fixed later, but for now, this is much&n;&t; * easier.&n;&t; */
id|current-&gt;thread.task_size
op_assign
l_int|0xc0000000
suffix:semicolon
multiline_comment|/* Set map base to allow enough room for hp-ux heap growth */
id|current-&gt;thread.map_base
op_assign
l_int|0x80000000
suffix:semicolon
id|retval
op_assign
id|map_som_binary
c_func
(paren
id|bprm-&gt;file
comma
id|hpuxhdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|out_free
suffix:semicolon
id|som_entry
op_assign
id|hpuxhdr-&gt;exec_entry
suffix:semicolon
id|kfree
c_func
(paren
id|hpuxhdr
)paren
suffix:semicolon
id|set_binfmt
c_func
(paren
op_amp
id|som_format
)paren
suffix:semicolon
id|compute_creds
c_func
(paren
id|bprm
)paren
suffix:semicolon
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
id|create_som_tables
c_func
(paren
id|bprm
)paren
suffix:semicolon
id|current-&gt;mm-&gt;start_stack
op_assign
id|bprm-&gt;p
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
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;(start_brk) %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|current-&gt;mm-&gt;start_brk
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;(end_code) %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|current-&gt;mm-&gt;end_code
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;(start_code) %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|current-&gt;mm-&gt;start_code
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;(end_data) %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|current-&gt;mm-&gt;end_data
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;(start_stack) %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|current-&gt;mm-&gt;start_stack
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;(brk) %08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|current-&gt;mm-&gt;brk
)paren
suffix:semicolon
macro_line|#endif
id|map_hpux_gateway_page
c_func
(paren
id|current
comma
id|current-&gt;mm
)paren
suffix:semicolon
id|start_thread_som
c_func
(paren
id|regs
comma
id|som_entry
comma
id|bprm-&gt;p
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
multiline_comment|/* error cleanup */
id|out_free
suffix:colon
id|kfree
c_func
(paren
id|hpuxhdr
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|load_som_library
r_static
r_int
id|load_som_library
c_func
(paren
r_struct
id|file
op_star
id|f
)paren
(brace
multiline_comment|/* No lib support in SOM yet.  gizza chance.. */
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
multiline_comment|/* Install the SOM loader.&n;&t; * N.B. We *rely* on the table being the right size with the&n;&t; * right number of free slots...&n;&t; */
DECL|function|init_som_binfmt
r_static
r_int
id|__init
id|init_som_binfmt
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
id|som_format
)paren
suffix:semicolon
)brace
DECL|function|exit_som_binfmt
r_static
r_void
id|__exit
id|exit_som_binfmt
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Remove the SOM loader. */
id|unregister_binfmt
c_func
(paren
op_amp
id|som_format
)paren
suffix:semicolon
)brace
DECL|variable|init_som_binfmt
id|core_initcall
c_func
(paren
id|init_som_binfmt
)paren
suffix:semicolon
DECL|variable|exit_som_binfmt
id|module_exit
c_func
(paren
id|exit_som_binfmt
)paren
suffix:semicolon
eof
