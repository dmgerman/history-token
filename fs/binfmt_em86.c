multiline_comment|/*&n; *  linux/fs/binfmt_em86.c&n; *&n; *  Based on linux/fs/binfmt_script.c&n; *  Copyright (C) 1996  Martin von L&#xfffd;wis&n; *  original #!-checking implemented by tytso.&n; *&n; *  em86 changes Copyright (C) 1997  Jim Paradis&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
DECL|macro|EM86_INTERP
mdefine_line|#define EM86_INTERP&t;&quot;/usr/bin/em86&quot;
DECL|macro|EM86_I_NAME
mdefine_line|#define EM86_I_NAME&t;&quot;em86&quot;
DECL|function|load_em86
r_static
r_int
id|load_em86
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
r_char
op_star
id|interp
comma
op_star
id|i_name
comma
op_star
id|i_arg
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_struct
id|elfhdr
id|elf_ex
suffix:semicolon
multiline_comment|/* Make sure this is a Linux/Intel ELF executable... */
id|elf_ex
op_assign
op_star
(paren
(paren
r_struct
id|elfhdr
op_star
)paren
id|bprm-&gt;buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|elf_ex.e_ident
comma
id|ELFMAG
comma
id|SELFMAG
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|ENOEXEC
suffix:semicolon
multiline_comment|/* First of all, some simple consistency checks */
r_if
c_cond
(paren
(paren
id|elf_ex.e_type
op_ne
id|ET_EXEC
op_logical_and
id|elf_ex.e_type
op_ne
id|ET_DYN
)paren
op_logical_or
(paren
op_logical_neg
(paren
(paren
id|elf_ex.e_machine
op_eq
id|EM_386
)paren
op_logical_or
(paren
id|elf_ex.e_machine
op_eq
id|EM_486
)paren
)paren
)paren
op_logical_or
(paren
op_logical_neg
id|bprm-&gt;file-&gt;f_op
op_logical_or
op_logical_neg
id|bprm-&gt;file-&gt;f_op-&gt;mmap
)paren
)paren
(brace
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
id|bprm-&gt;sh_bang
op_increment
suffix:semicolon
multiline_comment|/* Well, the bang-shell is implicit... */
id|allow_write_access
c_func
(paren
id|bprm-&gt;file
)paren
suffix:semicolon
id|fput
c_func
(paren
id|bprm-&gt;file
)paren
suffix:semicolon
id|bprm-&gt;file
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Unlike in the script case, we don&squot;t have to do any hairy&n;&t; * parsing to find our interpreter... it&squot;s hardcoded!&n;&t; */
id|interp
op_assign
id|EM86_INTERP
suffix:semicolon
id|i_name
op_assign
id|EM86_I_NAME
suffix:semicolon
id|i_arg
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* We reserve the right to add an arg later */
multiline_comment|/*&n;&t; * Splice in (1) the interpreter&squot;s name for argv[0]&n;&t; *           (2) (optional) argument to interpreter&n;&t; *           (3) filename of emulated file (replace argv[0])&n;&t; *&n;&t; * This is done in reverse order, because of how the&n;&t; * user environment and arguments are stored.&n;&t; */
id|remove_arg_zero
c_func
(paren
id|bprm
)paren
suffix:semicolon
id|retval
op_assign
id|copy_strings_kernel
c_func
(paren
l_int|1
comma
op_amp
id|bprm-&gt;filename
comma
id|bprm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
id|bprm-&gt;argc
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i_arg
)paren
(brace
id|retval
op_assign
id|copy_strings_kernel
c_func
(paren
l_int|1
comma
op_amp
id|i_arg
comma
id|bprm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
id|bprm-&gt;argc
op_increment
suffix:semicolon
)brace
id|retval
op_assign
id|copy_strings_kernel
c_func
(paren
l_int|1
comma
op_amp
id|i_name
comma
id|bprm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
id|bprm-&gt;argc
op_increment
suffix:semicolon
multiline_comment|/*&n;&t; * OK, now restart the process with the interpreter&squot;s inode.&n;&t; * Note that we use open_exec() as the name is now in kernel&n;&t; * space, and we don&squot;t need to copy it.&n;&t; */
id|file
op_assign
id|open_exec
c_func
(paren
id|interp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|file
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|file
)paren
suffix:semicolon
id|bprm-&gt;file
op_assign
id|file
suffix:semicolon
id|retval
op_assign
id|prepare_binprm
c_func
(paren
id|bprm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
r_return
id|search_binary_handler
c_func
(paren
id|bprm
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|variable|em86_format
r_static
r_struct
id|linux_binfmt
id|em86_format
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
id|load_em86
comma
)brace
suffix:semicolon
DECL|function|init_em86_binfmt
r_static
r_int
id|__init
id|init_em86_binfmt
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
id|em86_format
)paren
suffix:semicolon
)brace
DECL|function|exit_em86_binfmt
r_static
r_void
id|__exit
id|exit_em86_binfmt
c_func
(paren
r_void
)paren
(brace
id|unregister_binfmt
c_func
(paren
op_amp
id|em86_format
)paren
suffix:semicolon
)brace
DECL|variable|init_em86_binfmt
id|core_initcall
c_func
(paren
id|init_em86_binfmt
)paren
suffix:semicolon
DECL|variable|exit_em86_binfmt
id|module_exit
c_func
(paren
id|exit_em86_binfmt
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
