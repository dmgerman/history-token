multiline_comment|/*&n; *  binfmt_misc.c&n; *&n; *  Copyright (C) 1997 Richard G&#xfffd;nther&n; *&n; *  binfmt_misc detects binaries via a magic or filename extension and invokes&n; *  a specified wrapper. This should obsolete binfmt_java, binfmt_em86 and&n; *  binfmt_mz.&n; *&n; *  1997-04-25 first version&n; *  [...]&n; *  1997-05-19 cleanup&n; *  1997-06-26 hpa: pass the real filename rather than argv[0]&n; *  1997-06-30 minor cleanup&n; *  1997-08-09 removed extension stripping, locking cleanup&n; *  2001-02-28 AV: rewritten into something that resembles C. Original didn&squot;t.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_enum
(brace
DECL|enumerator|VERBOSE_STATUS
id|VERBOSE_STATUS
op_assign
l_int|1
multiline_comment|/* make it zero to save 400 bytes kernel memory */
)brace
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|entries
)paren
suffix:semicolon
DECL|variable|enabled
r_static
r_int
id|enabled
op_assign
l_int|1
suffix:semicolon
DECL|enumerator|Enabled
DECL|enumerator|Magic
r_enum
(brace
id|Enabled
comma
id|Magic
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* type, status, etc. */
DECL|member|offset
r_int
id|offset
suffix:semicolon
multiline_comment|/* offset of magic */
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* size of magic/mask */
DECL|member|magic
r_char
op_star
id|magic
suffix:semicolon
multiline_comment|/* magic or filename extension */
DECL|member|mask
r_char
op_star
id|mask
suffix:semicolon
multiline_comment|/* mask, NULL for exact match */
DECL|member|interpreter
r_char
op_star
id|interpreter
suffix:semicolon
multiline_comment|/* filename of interpreter */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|dentry
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
DECL|typedef|Node
)brace
id|Node
suffix:semicolon
DECL|variable|entries_lock
r_static
id|rwlock_t
id|entries_lock
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|bm_mnt
r_static
r_struct
id|vfsmount
op_star
id|bm_mnt
suffix:semicolon
DECL|variable|entry_count
r_static
r_int
id|entry_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &n; * Check if we support the binfmt&n; * if we do, return the node, else NULL&n; * locking is done in load_misc_binary&n; */
DECL|function|check_file
r_static
id|Node
op_star
id|check_file
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
id|p
op_assign
id|strrchr
c_func
(paren
id|bprm-&gt;filename
comma
l_char|&squot;.&squot;
)paren
suffix:semicolon
r_struct
id|list_head
op_star
id|l
suffix:semicolon
id|list_for_each
c_func
(paren
id|l
comma
op_amp
id|entries
)paren
(brace
id|Node
op_star
id|e
op_assign
id|list_entry
c_func
(paren
id|l
comma
id|Node
comma
id|list
)paren
suffix:semicolon
r_char
op_star
id|s
suffix:semicolon
r_int
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|Enabled
comma
op_amp
id|e-&gt;flags
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|Magic
comma
op_amp
id|e-&gt;flags
)paren
)paren
(brace
r_if
c_cond
(paren
id|p
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|e-&gt;magic
comma
id|p
op_plus
l_int|1
)paren
)paren
r_return
id|e
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|s
op_assign
id|bprm-&gt;buf
op_plus
id|e-&gt;offset
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;mask
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|e-&gt;size
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
(paren
op_star
id|s
op_increment
op_xor
id|e-&gt;magic
(braket
id|j
)braket
)paren
op_amp
id|e-&gt;mask
(braket
id|j
)braket
)paren
r_break
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|e-&gt;size
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
(paren
op_star
id|s
op_increment
op_xor
id|e-&gt;magic
(braket
id|j
)braket
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|j
op_eq
id|e-&gt;size
)paren
r_return
id|e
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * the loader itself&n; */
DECL|function|load_misc_binary
r_static
r_int
id|load_misc_binary
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
id|Node
op_star
id|fmt
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_char
id|iname
(braket
id|BINPRM_BUF_SIZE
)braket
suffix:semicolon
r_char
op_star
id|iname_addr
op_assign
id|iname
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|enabled
)paren
r_goto
id|_ret
suffix:semicolon
multiline_comment|/* to keep locking time low, we copy the interpreter string */
id|read_lock
c_func
(paren
op_amp
id|entries_lock
)paren
suffix:semicolon
id|fmt
op_assign
id|check_file
c_func
(paren
id|bprm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fmt
)paren
(brace
id|strncpy
c_func
(paren
id|iname
comma
id|fmt-&gt;interpreter
comma
id|BINPRM_BUF_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|iname
(braket
id|BINPRM_BUF_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|entries_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fmt
)paren
r_goto
id|_ret
suffix:semicolon
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
multiline_comment|/* Build args for interpreter */
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
r_goto
id|_ret
suffix:semicolon
id|bprm-&gt;argc
op_increment
suffix:semicolon
id|retval
op_assign
id|copy_strings_kernel
c_func
(paren
l_int|1
comma
op_amp
id|iname_addr
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
r_goto
id|_ret
suffix:semicolon
id|bprm-&gt;argc
op_increment
suffix:semicolon
id|bprm-&gt;filename
op_assign
id|iname
suffix:semicolon
multiline_comment|/* for binfmt_script */
id|file
op_assign
id|open_exec
c_func
(paren
id|iname
)paren
suffix:semicolon
id|retval
op_assign
id|PTR_ERR
c_func
(paren
id|file
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
r_goto
id|_ret
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
op_ge
l_int|0
)paren
id|retval
op_assign
id|search_binary_handler
c_func
(paren
id|bprm
comma
id|regs
)paren
suffix:semicolon
id|_ret
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Command parsers */
multiline_comment|/*&n; * parses and copies one argument enclosed in del from *sp to *dp,&n; * recognising the &bslash;x special.&n; * returns pointer to the copied argument or NULL in case of an&n; * error (and sets err) or null argument length.&n; */
DECL|function|scanarg
r_static
r_char
op_star
id|scanarg
c_func
(paren
r_char
op_star
id|s
comma
r_char
id|del
)paren
(brace
r_char
id|c
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
op_ne
id|del
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
op_logical_and
op_star
id|s
op_eq
l_char|&squot;x&squot;
)paren
(brace
id|s
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isxdigit
c_func
(paren
op_star
id|s
op_increment
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isxdigit
c_func
(paren
op_star
id|s
op_increment
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
id|s
suffix:semicolon
)brace
DECL|function|unquote
r_static
r_int
id|unquote
c_func
(paren
r_char
op_star
id|from
)paren
(brace
r_char
id|c
op_assign
l_int|0
comma
op_star
id|s
op_assign
id|from
comma
op_star
id|p
op_assign
id|from
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;&bslash;&squot;
op_logical_and
op_star
id|s
op_eq
l_char|&squot;x&squot;
)paren
(brace
id|s
op_increment
suffix:semicolon
id|c
op_assign
id|toupper
c_func
(paren
op_star
id|s
op_increment
)paren
suffix:semicolon
op_star
id|p
op_assign
(paren
id|c
op_minus
(paren
id|isdigit
c_func
(paren
id|c
)paren
ques
c_cond
l_char|&squot;0&squot;
suffix:colon
l_char|&squot;A&squot;
op_minus
l_int|10
)paren
)paren
op_lshift
l_int|4
suffix:semicolon
id|c
op_assign
id|toupper
c_func
(paren
op_star
id|s
op_increment
)paren
suffix:semicolon
op_star
id|p
op_increment
op_or_assign
id|c
op_minus
(paren
id|isdigit
c_func
(paren
id|c
)paren
ques
c_cond
l_char|&squot;0&squot;
suffix:colon
l_char|&squot;A&squot;
op_minus
l_int|10
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
id|c
suffix:semicolon
)brace
r_return
id|p
op_minus
id|from
suffix:semicolon
)brace
multiline_comment|/*&n; * This registers a new binary format, it recognises the syntax&n; * &squot;:name:type:offset:magic:mask:interpreter:&squot;&n; * where the &squot;:&squot; is the IFS, that can be chosen with the first char&n; */
DECL|function|create_entry
r_static
id|Node
op_star
id|create_entry
c_func
(paren
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
)paren
(brace
id|Node
op_star
id|e
suffix:semicolon
r_int
id|memsize
comma
id|err
suffix:semicolon
r_char
op_star
id|buf
comma
op_star
id|p
suffix:semicolon
r_char
id|del
suffix:semicolon
multiline_comment|/* some sanity checks */
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
OL
l_int|11
)paren
op_logical_or
(paren
id|count
OG
l_int|256
)paren
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|memsize
op_assign
r_sizeof
(paren
id|Node
)paren
op_plus
id|count
op_plus
l_int|8
suffix:semicolon
id|e
op_assign
(paren
id|Node
op_star
)paren
id|kmalloc
c_func
(paren
id|memsize
comma
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e
)paren
r_goto
id|out
suffix:semicolon
id|p
op_assign
id|buf
op_assign
(paren
r_char
op_star
)paren
id|e
op_plus
r_sizeof
(paren
id|Node
)paren
suffix:semicolon
id|memset
c_func
(paren
id|e
comma
l_int|0
comma
r_sizeof
(paren
id|Node
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|buffer
comma
id|count
)paren
)paren
r_goto
id|Efault
suffix:semicolon
id|del
op_assign
op_star
id|p
op_increment
suffix:semicolon
multiline_comment|/* delimeter */
id|memset
c_func
(paren
id|buf
op_plus
id|count
comma
id|del
comma
l_int|8
)paren
suffix:semicolon
id|e-&gt;name
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|p
comma
id|del
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|Einval
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e-&gt;name
(braket
l_int|0
)braket
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|e-&gt;name
comma
l_string|&quot;.&quot;
)paren
op_logical_or
op_logical_neg
id|strcmp
c_func
(paren
id|e-&gt;name
comma
l_string|&quot;..&quot;
)paren
op_logical_or
id|strchr
c_func
(paren
id|e-&gt;name
comma
l_char|&squot;/&squot;
)paren
)paren
r_goto
id|Einval
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|p
op_increment
)paren
(brace
r_case
l_char|&squot;E&squot;
suffix:colon
id|e-&gt;flags
op_assign
l_int|1
op_lshift
id|Enabled
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;M&squot;
suffix:colon
id|e-&gt;flags
op_assign
(paren
l_int|1
op_lshift
id|Enabled
)paren
op_or
(paren
l_int|1
op_lshift
id|Magic
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|Einval
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|p
op_increment
op_ne
id|del
)paren
r_goto
id|Einval
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|Magic
comma
op_amp
id|e-&gt;flags
)paren
)paren
(brace
r_char
op_star
id|s
op_assign
id|strchr
c_func
(paren
id|p
comma
id|del
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_goto
id|Einval
suffix:semicolon
op_star
id|s
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|e-&gt;offset
op_assign
id|simple_strtoul
c_func
(paren
id|p
comma
op_amp
id|p
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_increment
)paren
r_goto
id|Einval
suffix:semicolon
id|e-&gt;magic
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|scanarg
c_func
(paren
id|p
comma
id|del
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|Einval
suffix:semicolon
id|p
(braket
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e-&gt;magic
(braket
l_int|0
)braket
)paren
r_goto
id|Einval
suffix:semicolon
id|e-&gt;mask
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|scanarg
c_func
(paren
id|p
comma
id|del
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|Einval
suffix:semicolon
id|p
(braket
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e-&gt;mask
(braket
l_int|0
)braket
)paren
id|e-&gt;mask
op_assign
l_int|NULL
suffix:semicolon
id|e-&gt;size
op_assign
id|unquote
c_func
(paren
id|e-&gt;magic
)paren
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;mask
op_logical_and
id|unquote
c_func
(paren
id|e-&gt;mask
)paren
op_ne
id|e-&gt;size
)paren
r_goto
id|Einval
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;size
op_plus
id|e-&gt;offset
OG
id|BINPRM_BUF_SIZE
)paren
r_goto
id|Einval
suffix:semicolon
)brace
r_else
(brace
id|p
op_assign
id|strchr
c_func
(paren
id|p
comma
id|del
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|Einval
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|e-&gt;magic
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|p
comma
id|del
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|Einval
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e-&gt;magic
(braket
l_int|0
)braket
op_logical_or
id|strchr
c_func
(paren
id|e-&gt;magic
comma
l_char|&squot;/&squot;
)paren
)paren
r_goto
id|Einval
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|p
comma
id|del
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|Einval
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
id|e-&gt;interpreter
op_assign
id|p
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|p
comma
id|del
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|Einval
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e-&gt;interpreter
(braket
l_int|0
)braket
)paren
r_goto
id|Einval
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|p
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
id|buf
op_plus
id|count
)paren
r_goto
id|Einval
suffix:semicolon
r_return
id|e
suffix:semicolon
id|out
suffix:colon
r_return
id|ERR_PTR
c_func
(paren
id|err
)paren
suffix:semicolon
id|Efault
suffix:colon
id|kfree
c_func
(paren
id|e
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
id|Einval
suffix:colon
id|kfree
c_func
(paren
id|e
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set status of entry/binfmt_misc:&n; * &squot;1&squot; enables, &squot;0&squot; disables and &squot;-1&squot; clears entry/binfmt_misc&n; */
DECL|function|parse_command
r_static
r_int
id|parse_command
c_func
(paren
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
)paren
(brace
r_char
id|s
(braket
l_int|4
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|3
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|s
comma
id|buffer
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|s
(braket
id|count
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|1
op_logical_and
id|s
(braket
l_int|0
)braket
op_eq
l_char|&squot;0&squot;
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|1
op_logical_and
id|s
(braket
l_int|0
)braket
op_eq
l_char|&squot;1&squot;
)paren
r_return
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|2
op_logical_and
id|s
(braket
l_int|0
)braket
op_eq
l_char|&squot;-&squot;
op_logical_and
id|s
(braket
l_int|1
)braket
op_eq
l_char|&squot;1&squot;
)paren
r_return
l_int|3
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* generic stuff */
DECL|function|entry_status
r_static
r_void
id|entry_status
c_func
(paren
id|Node
op_star
id|e
comma
r_char
op_star
id|page
)paren
(brace
r_char
op_star
id|dp
suffix:semicolon
r_char
op_star
id|status
op_assign
l_string|&quot;disabled&quot;
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|Enabled
comma
op_amp
id|e-&gt;flags
)paren
)paren
id|status
op_assign
l_string|&quot;enabled&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|VERBOSE_STATUS
)paren
(brace
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%s&bslash;ninterpreter %s&bslash;n&quot;
comma
id|status
comma
id|e-&gt;interpreter
)paren
suffix:semicolon
id|dp
op_assign
id|page
op_plus
id|strlen
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|Magic
comma
op_amp
id|e-&gt;flags
)paren
)paren
(brace
id|sprintf
c_func
(paren
id|dp
comma
l_string|&quot;extension .%s&bslash;n&quot;
comma
id|e-&gt;magic
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|i
suffix:semicolon
id|sprintf
c_func
(paren
id|dp
comma
l_string|&quot;offset %i&bslash;nmagic &quot;
comma
id|e-&gt;offset
)paren
suffix:semicolon
id|dp
op_assign
id|page
op_plus
id|strlen
c_func
(paren
id|page
)paren
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
id|e-&gt;size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sprintf
c_func
(paren
id|dp
comma
l_string|&quot;%02x&quot;
comma
l_int|0xff
op_amp
(paren
r_int
)paren
(paren
id|e-&gt;magic
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
id|dp
op_add_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|e-&gt;mask
)paren
(brace
id|sprintf
c_func
(paren
id|dp
comma
l_string|&quot;&bslash;nmask &quot;
)paren
suffix:semicolon
id|dp
op_add_assign
l_int|6
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
id|e-&gt;size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sprintf
c_func
(paren
id|dp
comma
l_string|&quot;%02x&quot;
comma
l_int|0xff
op_amp
(paren
r_int
)paren
(paren
id|e-&gt;mask
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
id|dp
op_add_assign
l_int|2
suffix:semicolon
)brace
)brace
op_star
id|dp
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
op_star
id|dp
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
)brace
DECL|function|bm_get_inode
r_static
r_struct
id|inode
op_star
id|bm_get_inode
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|mode
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|new_inode
c_func
(paren
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode
)paren
(brace
id|inode-&gt;i_mode
op_assign
id|mode
suffix:semicolon
id|inode-&gt;i_uid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_gid
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_blksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|inode-&gt;i_blocks
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
)brace
r_return
id|inode
suffix:semicolon
)brace
DECL|function|bm_clear_inode
r_static
r_void
id|bm_clear_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|Node
op_star
id|e
op_assign
id|inode-&gt;u.generic_ip
suffix:semicolon
r_if
c_cond
(paren
id|e
)paren
(brace
r_struct
id|vfsmount
op_star
id|mnt
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|entries_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|e-&gt;list
)paren
suffix:semicolon
id|mnt
op_assign
id|bm_mnt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|entry_count
)paren
id|bm_mnt
op_assign
l_int|NULL
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|entries_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|e
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|mnt
)paren
suffix:semicolon
)brace
)brace
DECL|function|kill_node
r_static
r_void
id|kill_node
c_func
(paren
id|Node
op_star
id|e
)paren
(brace
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|entries_lock
)paren
suffix:semicolon
id|dentry
op_assign
id|e-&gt;dentry
suffix:semicolon
r_if
c_cond
(paren
id|dentry
)paren
(brace
id|list_del_init
c_func
(paren
op_amp
id|e-&gt;list
)paren
suffix:semicolon
id|e-&gt;dentry
op_assign
l_int|NULL
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|entries_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry
)paren
(brace
id|dentry-&gt;d_inode-&gt;i_nlink
op_decrement
suffix:semicolon
id|d_drop
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* /&lt;entry&gt; */
r_static
id|ssize_t
DECL|function|bm_entry_read
id|bm_entry_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|nbytes
comma
id|loff_t
op_star
id|ppos
)paren
(brace
id|Node
op_star
id|e
op_assign
id|file-&gt;f_dentry-&gt;d_inode-&gt;u.generic_ip
suffix:semicolon
id|loff_t
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
id|ssize_t
id|res
suffix:semicolon
r_char
op_star
id|page
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|entry_status
c_func
(paren
id|e
comma
id|page
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|page
)paren
suffix:semicolon
id|res
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|len
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|pos
op_plus
id|nbytes
)paren
id|nbytes
op_assign
id|len
op_minus
id|pos
suffix:semicolon
id|res
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|page
op_plus
id|pos
comma
id|nbytes
)paren
)paren
r_goto
id|out
suffix:semicolon
op_star
id|ppos
op_assign
id|pos
op_plus
id|nbytes
suffix:semicolon
id|res
op_assign
id|nbytes
suffix:semicolon
id|out
suffix:colon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|bm_entry_write
r_static
id|ssize_t
id|bm_entry_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|dentry
op_star
id|root
suffix:semicolon
id|Node
op_star
id|e
op_assign
id|file-&gt;f_dentry-&gt;d_inode-&gt;u.generic_ip
suffix:semicolon
r_int
id|res
op_assign
id|parse_command
c_func
(paren
id|buffer
comma
id|count
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|res
)paren
(brace
r_case
l_int|1
suffix:colon
id|clear_bit
c_func
(paren
id|Enabled
comma
op_amp
id|e-&gt;flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|set_bit
c_func
(paren
id|Enabled
comma
op_amp
id|e-&gt;flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|root
op_assign
id|dget
c_func
(paren
id|file-&gt;f_vfsmnt-&gt;mnt_sb-&gt;s_root
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|root-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|kill_node
c_func
(paren
id|e
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|root-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|dput
c_func
(paren
id|root
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|res
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|variable|bm_entry_operations
r_static
r_struct
id|file_operations
id|bm_entry_operations
op_assign
(brace
id|read
suffix:colon
id|bm_entry_read
comma
id|write
suffix:colon
id|bm_entry_write
comma
)brace
suffix:semicolon
DECL|variable|bm_fs_type
r_static
r_struct
id|file_system_type
id|bm_fs_type
suffix:semicolon
multiline_comment|/* /register */
DECL|function|bm_register_write
r_static
id|ssize_t
id|bm_register_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
id|Node
op_star
id|e
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|vfsmount
op_star
id|mnt
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|dentry
op_star
id|root
comma
op_star
id|dentry
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
op_assign
id|file-&gt;f_vfsmnt-&gt;mnt_sb
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|e
op_assign
id|create_entry
c_func
(paren
id|buffer
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|e
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|e
)paren
suffix:semicolon
id|root
op_assign
id|dget
c_func
(paren
id|sb-&gt;s_root
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|root-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|dentry
op_assign
id|lookup_one_len
c_func
(paren
id|e-&gt;name
comma
id|root
comma
id|strlen
c_func
(paren
id|e-&gt;name
)paren
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|EEXIST
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_inode
)paren
r_goto
id|out2
suffix:semicolon
id|inode
op_assign
id|bm_get_inode
c_func
(paren
id|sb
comma
id|S_IFREG
op_or
l_int|0644
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out2
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|entries_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bm_mnt
)paren
(brace
id|write_unlock
c_func
(paren
op_amp
id|entries_lock
)paren
suffix:semicolon
id|mnt
op_assign
id|kern_mount
c_func
(paren
op_amp
id|bm_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|mnt
)paren
)paren
(brace
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|mnt
)paren
suffix:semicolon
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|out2
suffix:semicolon
)brace
id|write_lock
c_func
(paren
op_amp
id|entries_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bm_mnt
)paren
id|bm_mnt
op_assign
id|mnt
suffix:semicolon
)brace
id|mntget
c_func
(paren
id|bm_mnt
)paren
suffix:semicolon
id|entry_count
op_increment
suffix:semicolon
id|e-&gt;dentry
op_assign
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|inode-&gt;u.generic_ip
op_assign
id|e
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|bm_entry_operations
suffix:semicolon
id|d_instantiate
c_func
(paren
id|dentry
comma
id|inode
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|e-&gt;list
comma
op_amp
id|entries
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|entries_lock
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|mnt
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|out2
suffix:colon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|root-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|dput
c_func
(paren
id|root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|kfree
c_func
(paren
id|e
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|variable|bm_register_operations
r_static
r_struct
id|file_operations
id|bm_register_operations
op_assign
(brace
id|write
suffix:colon
id|bm_register_write
comma
)brace
suffix:semicolon
multiline_comment|/* /status */
r_static
id|ssize_t
DECL|function|bm_status_read
id|bm_status_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|nbytes
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_char
op_star
id|s
op_assign
id|enabled
ques
c_cond
l_string|&quot;enabled&quot;
suffix:colon
l_string|&quot;disabled&quot;
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
id|loff_t
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|len
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|pos
op_plus
id|nbytes
)paren
id|nbytes
op_assign
id|len
op_minus
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|s
op_plus
id|pos
comma
id|nbytes
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|ppos
op_assign
id|pos
op_plus
id|nbytes
suffix:semicolon
r_return
id|nbytes
suffix:semicolon
)brace
DECL|function|bm_status_write
r_static
id|ssize_t
id|bm_status_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
id|res
op_assign
id|parse_command
c_func
(paren
id|buffer
comma
id|count
)paren
suffix:semicolon
r_struct
id|dentry
op_star
id|root
suffix:semicolon
r_switch
c_cond
(paren
id|res
)paren
(brace
r_case
l_int|1
suffix:colon
id|enabled
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|enabled
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|root
op_assign
id|dget
c_func
(paren
id|file-&gt;f_vfsmnt-&gt;mnt_sb-&gt;s_root
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|root-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|entries
)paren
)paren
id|kill_node
c_func
(paren
id|list_entry
c_func
(paren
id|entries.next
comma
id|Node
comma
id|list
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|root-&gt;d_inode-&gt;i_sem
)paren
suffix:semicolon
id|dput
c_func
(paren
id|root
)paren
suffix:semicolon
r_default
suffix:colon
r_return
id|res
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|variable|bm_status_operations
r_static
r_struct
id|file_operations
id|bm_status_operations
op_assign
(brace
id|read
suffix:colon
id|bm_status_read
comma
id|write
suffix:colon
id|bm_status_write
comma
)brace
suffix:semicolon
multiline_comment|/* Superblock handling */
DECL|variable|s_ops
r_static
r_struct
id|super_operations
id|s_ops
op_assign
(brace
id|statfs
suffix:colon
id|simple_statfs
comma
id|put_inode
suffix:colon
id|force_delete
comma
id|clear_inode
suffix:colon
id|bm_clear_inode
comma
)brace
suffix:semicolon
DECL|function|bm_fill_super
r_static
r_int
id|bm_fill_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|qstr
id|names
(braket
l_int|2
)braket
op_assign
(brace
(brace
id|name
suffix:colon
l_string|&quot;status&quot;
)brace
comma
(brace
id|name
suffix:colon
l_string|&quot;register&quot;
)brace
)brace
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
(braket
l_int|3
)braket
suffix:semicolon
r_int
id|i
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
r_sizeof
(paren
id|names
)paren
op_div
r_sizeof
(paren
id|names
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|names
(braket
id|i
)braket
dot
id|len
op_assign
id|strlen
c_func
(paren
id|names
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|names
(braket
id|i
)braket
dot
id|hash
op_assign
id|full_name_hash
c_func
(paren
id|names
(braket
id|i
)braket
dot
id|name
comma
id|names
(braket
id|i
)braket
dot
id|len
)paren
suffix:semicolon
)brace
id|sb-&gt;s_blocksize
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
id|PAGE_CACHE_SHIFT
suffix:semicolon
id|sb-&gt;s_magic
op_assign
l_int|0x42494e4d
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|s_ops
suffix:semicolon
id|inode
op_assign
id|bm_get_inode
c_func
(paren
id|sb
comma
id|S_IFDIR
op_or
l_int|0755
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|inode-&gt;i_op
op_assign
op_amp
id|simple_dir_inode_operations
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|simple_dir_operations
suffix:semicolon
id|dentry
(braket
l_int|0
)braket
op_assign
id|d_alloc_root
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry
(braket
l_int|0
)braket
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|dentry
(braket
l_int|1
)braket
op_assign
id|d_alloc
c_func
(paren
id|dentry
(braket
l_int|0
)braket
comma
op_amp
id|names
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry
(braket
l_int|1
)braket
)paren
r_goto
id|out1
suffix:semicolon
id|dentry
(braket
l_int|2
)braket
op_assign
id|d_alloc
c_func
(paren
id|dentry
(braket
l_int|0
)braket
comma
op_amp
id|names
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dentry
(braket
l_int|2
)braket
)paren
r_goto
id|out2
suffix:semicolon
id|inode
op_assign
id|bm_get_inode
c_func
(paren
id|sb
comma
id|S_IFREG
op_or
l_int|0644
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out3
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|bm_status_operations
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
(braket
l_int|1
)braket
comma
id|inode
)paren
suffix:semicolon
id|inode
op_assign
id|bm_get_inode
c_func
(paren
id|sb
comma
id|S_IFREG
op_or
l_int|0400
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_goto
id|out3
suffix:semicolon
id|inode-&gt;i_fop
op_assign
op_amp
id|bm_register_operations
suffix:semicolon
id|d_add
c_func
(paren
id|dentry
(braket
l_int|2
)braket
comma
id|inode
)paren
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|dentry
(braket
l_int|0
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out3
suffix:colon
id|dput
c_func
(paren
id|dentry
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|out2
suffix:colon
id|dput
c_func
(paren
id|dentry
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|out1
suffix:colon
id|dput
c_func
(paren
id|dentry
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|bm_get_sb
r_static
r_struct
id|super_block
op_star
id|bm_get_sb
c_func
(paren
r_struct
id|file_system_type
op_star
id|fs_type
comma
r_int
id|flags
comma
r_char
op_star
id|dev_name
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|get_sb_single
c_func
(paren
id|fs_type
comma
id|flags
comma
id|data
comma
id|bm_fill_super
)paren
suffix:semicolon
)brace
DECL|variable|misc_format
r_static
r_struct
id|linux_binfmt
id|misc_format
op_assign
(brace
id|module
suffix:colon
id|THIS_MODULE
comma
id|load_binary
suffix:colon
id|load_misc_binary
comma
)brace
suffix:semicolon
DECL|variable|bm_fs_type
r_static
r_struct
id|file_system_type
id|bm_fs_type
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|name
suffix:colon
l_string|&quot;binfmt_misc&quot;
comma
id|get_sb
suffix:colon
id|bm_get_sb
comma
id|kill_sb
suffix:colon
id|kill_litter_super
comma
)brace
suffix:semicolon
DECL|function|init_misc_binfmt
r_static
r_int
id|__init
id|init_misc_binfmt
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
id|register_filesystem
c_func
(paren
op_amp
id|bm_fs_type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|err
op_assign
id|register_binfmt
c_func
(paren
op_amp
id|misc_format
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|unregister_filesystem
c_func
(paren
op_amp
id|bm_fs_type
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|exit_misc_binfmt
r_static
r_void
id|__exit
id|exit_misc_binfmt
c_func
(paren
r_void
)paren
(brace
id|unregister_binfmt
c_func
(paren
op_amp
id|misc_format
)paren
suffix:semicolon
id|unregister_filesystem
c_func
(paren
op_amp
id|bm_fs_type
)paren
suffix:semicolon
)brace
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|variable|init_misc_binfmt
id|module_init
c_func
(paren
id|init_misc_binfmt
)paren
suffix:semicolon
DECL|variable|exit_misc_binfmt
id|module_exit
c_func
(paren
id|exit_misc_binfmt
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
