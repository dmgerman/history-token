multiline_comment|/*&n; * kallsyms.c: in-kernel printing of symbolic oopses and stack traces.&n; *&n; * Rewritten and vastly simplified by Rusty Russell for in-kernel&n; * module loader:&n; *   Copyright 2002 Rusty Russell &lt;rusty@rustcorp.com.au&gt; IBM Corporation&n; * Stem compression by Andi Kleen.&n; */
macro_line|#include &lt;linux/kallsyms.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
multiline_comment|/* These will be re-linked against their real values during the second link stage */
r_extern
r_int
r_int
id|kallsyms_addresses
(braket
)braket
id|__attribute__
c_func
(paren
(paren
id|weak
)paren
)paren
suffix:semicolon
r_extern
r_int
r_int
id|kallsyms_num_syms
id|__attribute__
c_func
(paren
(paren
id|weak
)paren
)paren
suffix:semicolon
r_extern
r_char
id|kallsyms_names
(braket
)braket
id|__attribute__
c_func
(paren
(paren
id|weak
)paren
)paren
suffix:semicolon
multiline_comment|/* Defined by the linker script. */
r_extern
r_char
id|_stext
(braket
)braket
comma
id|_etext
(braket
)braket
comma
id|_sinittext
(braket
)braket
comma
id|_einittext
(braket
)braket
suffix:semicolon
DECL|function|is_kernel_inittext
r_static
r_inline
r_int
id|is_kernel_inittext
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|addr
op_ge
(paren
r_int
r_int
)paren
id|_sinittext
op_logical_and
id|addr
op_le
(paren
r_int
r_int
)paren
id|_einittext
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|is_kernel_text
r_static
r_inline
r_int
id|is_kernel_text
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|addr
op_ge
(paren
r_int
r_int
)paren
id|_stext
op_logical_and
id|addr
op_le
(paren
r_int
r_int
)paren
id|_etext
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Lookup the address for this symbol. Returns 0 if not found. */
DECL|function|kallsyms_lookup_name
r_int
r_int
id|kallsyms_lookup_name
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_char
id|namebuf
(braket
id|KSYM_NAME_LEN
op_plus
l_int|1
)braket
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_char
op_star
id|knames
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|knames
op_assign
id|kallsyms_names
suffix:semicolon
id|i
OL
id|kallsyms_num_syms
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|prefix
op_assign
op_star
id|knames
op_increment
suffix:semicolon
id|strlcpy
c_func
(paren
id|namebuf
op_plus
id|prefix
comma
id|knames
comma
id|KSYM_NAME_LEN
op_minus
id|prefix
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|namebuf
comma
id|name
)paren
op_eq
l_int|0
)paren
r_return
id|kallsyms_addresses
(braket
id|i
)braket
suffix:semicolon
id|knames
op_add_assign
id|strlen
c_func
(paren
id|knames
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_return
id|module_kallsyms_lookup_name
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
multiline_comment|/* Lookup an address.  modname is set to NULL if it&squot;s in the kernel. */
DECL|function|kallsyms_lookup
r_const
r_char
op_star
id|kallsyms_lookup
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
op_star
id|symbolsize
comma
r_int
r_int
op_star
id|offset
comma
r_char
op_star
op_star
id|modname
comma
r_char
op_star
id|namebuf
)paren
(brace
r_int
r_int
id|i
comma
id|best
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This kernel should never had been booted. */
id|BUG_ON
c_func
(paren
op_logical_neg
id|kallsyms_addresses
)paren
suffix:semicolon
id|namebuf
(braket
id|KSYM_NAME_LEN
)braket
op_assign
l_int|0
suffix:semicolon
id|namebuf
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|is_kernel_text
c_func
(paren
id|addr
)paren
op_logical_or
id|is_kernel_inittext
c_func
(paren
id|addr
)paren
)paren
(brace
r_int
r_int
id|symbol_end
suffix:semicolon
r_char
op_star
id|name
op_assign
id|kallsyms_names
suffix:semicolon
multiline_comment|/* They&squot;re sorted, we could be clever here, but who cares? */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|kallsyms_num_syms
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|kallsyms_addresses
(braket
id|i
)braket
OG
id|kallsyms_addresses
(braket
id|best
)braket
op_logical_and
id|kallsyms_addresses
(braket
id|i
)braket
op_le
id|addr
)paren
id|best
op_assign
id|i
suffix:semicolon
)brace
multiline_comment|/* Grab name */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|best
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|prefix
op_assign
op_star
id|name
op_increment
suffix:semicolon
id|strncpy
c_func
(paren
id|namebuf
op_plus
id|prefix
comma
id|name
comma
id|KSYM_NAME_LEN
op_minus
id|prefix
)paren
suffix:semicolon
id|name
op_add_assign
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* At worst, symbol ends at end of section. */
r_if
c_cond
(paren
id|is_kernel_inittext
c_func
(paren
id|addr
)paren
)paren
id|symbol_end
op_assign
(paren
r_int
r_int
)paren
id|_einittext
suffix:semicolon
r_else
id|symbol_end
op_assign
(paren
r_int
r_int
)paren
id|_etext
suffix:semicolon
multiline_comment|/* Search for next non-aliased symbol */
r_for
c_loop
(paren
id|i
op_assign
id|best
op_plus
l_int|1
suffix:semicolon
id|i
OL
id|kallsyms_num_syms
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|kallsyms_addresses
(braket
id|i
)braket
OG
id|kallsyms_addresses
(braket
id|best
)braket
)paren
(brace
id|symbol_end
op_assign
id|kallsyms_addresses
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
op_star
id|symbolsize
op_assign
id|symbol_end
op_minus
id|kallsyms_addresses
(braket
id|best
)braket
suffix:semicolon
op_star
id|modname
op_assign
l_int|NULL
suffix:semicolon
op_star
id|offset
op_assign
id|addr
op_minus
id|kallsyms_addresses
(braket
id|best
)braket
suffix:semicolon
r_return
id|namebuf
suffix:semicolon
)brace
r_return
id|module_address_lookup
c_func
(paren
id|addr
comma
id|symbolsize
comma
id|offset
comma
id|modname
)paren
suffix:semicolon
)brace
multiline_comment|/* Replace &quot;%s&quot; in format with address, or returns -errno. */
DECL|function|__print_symbol
r_void
id|__print_symbol
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
r_int
r_int
id|address
)paren
(brace
r_char
op_star
id|modname
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_int
r_int
id|offset
comma
id|size
suffix:semicolon
r_char
id|namebuf
(braket
id|KSYM_NAME_LEN
op_plus
l_int|1
)braket
suffix:semicolon
r_char
id|buffer
(braket
r_sizeof
(paren
l_string|&quot;%s+%#lx/%#lx [%s]&quot;
)paren
op_plus
id|KSYM_NAME_LEN
op_plus
l_int|2
op_star
(paren
id|BITS_PER_LONG
op_star
l_int|3
op_div
l_int|10
)paren
op_plus
id|MODULE_NAME_LEN
op_plus
l_int|1
)braket
suffix:semicolon
id|name
op_assign
id|kallsyms_lookup
c_func
(paren
id|address
comma
op_amp
id|size
comma
op_amp
id|offset
comma
op_amp
id|modname
comma
id|namebuf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;0x%lx&quot;
comma
id|address
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|modname
)paren
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s+%#lx/%#lx [%s]&quot;
comma
id|name
comma
id|offset
comma
id|size
comma
id|modname
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s+%#lx/%#lx&quot;
comma
id|name
comma
id|offset
comma
id|size
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|fmt
comma
id|buffer
)paren
suffix:semicolon
)brace
multiline_comment|/* To avoid O(n^2) iteration, we carry prefix along. */
DECL|struct|kallsym_iter
r_struct
id|kallsym_iter
(brace
DECL|member|pos
id|loff_t
id|pos
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
DECL|member|nameoff
r_int
r_int
id|nameoff
suffix:semicolon
multiline_comment|/* If iterating in core kernel symbols */
DECL|member|type
r_char
id|type
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|KSYM_NAME_LEN
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Only label it &quot;global&quot; if it is exported. */
DECL|function|upcase_if_global
r_static
r_void
id|upcase_if_global
c_func
(paren
r_struct
id|kallsym_iter
op_star
id|iter
)paren
(brace
r_if
c_cond
(paren
id|is_exported
c_func
(paren
id|iter-&gt;name
comma
id|iter-&gt;owner
)paren
)paren
id|iter-&gt;type
op_add_assign
l_char|&squot;A&squot;
op_minus
l_char|&squot;a&squot;
suffix:semicolon
)brace
DECL|function|get_ksymbol_mod
r_static
r_int
id|get_ksymbol_mod
c_func
(paren
r_struct
id|kallsym_iter
op_star
id|iter
)paren
(brace
id|iter-&gt;owner
op_assign
id|module_get_kallsym
c_func
(paren
id|iter-&gt;pos
op_minus
id|kallsyms_num_syms
comma
op_amp
id|iter-&gt;value
comma
op_amp
id|iter-&gt;type
comma
id|iter-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iter-&gt;owner
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|upcase_if_global
c_func
(paren
id|iter
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Returns space to next name. */
DECL|function|get_ksymbol_core
r_static
r_int
r_int
id|get_ksymbol_core
c_func
(paren
r_struct
id|kallsym_iter
op_star
id|iter
)paren
(brace
r_int
id|stemlen
comma
id|off
op_assign
id|iter-&gt;nameoff
suffix:semicolon
multiline_comment|/* First char of each symbol name indicates prefix length&n;&t;   shared with previous name (stem compression). */
id|stemlen
op_assign
id|kallsyms_names
(braket
id|off
op_increment
)braket
suffix:semicolon
id|strlcpy
c_func
(paren
id|iter-&gt;name
op_plus
id|stemlen
comma
id|kallsyms_names
op_plus
id|off
comma
id|KSYM_NAME_LEN
op_plus
l_int|1
op_minus
id|stemlen
)paren
suffix:semicolon
id|off
op_add_assign
id|strlen
c_func
(paren
id|kallsyms_names
op_plus
id|off
)paren
op_plus
l_int|1
suffix:semicolon
id|iter-&gt;owner
op_assign
l_int|NULL
suffix:semicolon
id|iter-&gt;value
op_assign
id|kallsyms_addresses
(braket
id|iter-&gt;pos
)braket
suffix:semicolon
r_if
c_cond
(paren
id|is_kernel_text
c_func
(paren
id|iter-&gt;value
)paren
op_logical_or
id|is_kernel_inittext
c_func
(paren
id|iter-&gt;value
)paren
)paren
id|iter-&gt;type
op_assign
l_char|&squot;t&squot;
suffix:semicolon
r_else
id|iter-&gt;type
op_assign
l_char|&squot;d&squot;
suffix:semicolon
id|upcase_if_global
c_func
(paren
id|iter
)paren
suffix:semicolon
r_return
id|off
op_minus
id|iter-&gt;nameoff
suffix:semicolon
)brace
DECL|function|reset_iter
r_static
r_void
id|reset_iter
c_func
(paren
r_struct
id|kallsym_iter
op_star
id|iter
)paren
(brace
id|iter-&gt;name
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|iter-&gt;nameoff
op_assign
l_int|0
suffix:semicolon
id|iter-&gt;pos
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Returns false if pos at or past end of file. */
DECL|function|update_iter
r_static
r_int
id|update_iter
c_func
(paren
r_struct
id|kallsym_iter
op_star
id|iter
comma
id|loff_t
id|pos
)paren
(brace
multiline_comment|/* Module symbols can be accessed randomly. */
r_if
c_cond
(paren
id|pos
op_ge
id|kallsyms_num_syms
)paren
(brace
id|iter-&gt;pos
op_assign
id|pos
suffix:semicolon
r_return
id|get_ksymbol_mod
c_func
(paren
id|iter
)paren
suffix:semicolon
)brace
multiline_comment|/* If we&squot;re past the desired position, reset to start. */
r_if
c_cond
(paren
id|pos
OL
id|iter-&gt;pos
)paren
id|reset_iter
c_func
(paren
id|iter
)paren
suffix:semicolon
multiline_comment|/* We need to iterate through the previous symbols: can be slow */
r_for
c_loop
(paren
suffix:semicolon
id|iter-&gt;pos
op_ne
id|pos
suffix:semicolon
id|iter-&gt;pos
op_increment
)paren
(brace
id|iter-&gt;nameoff
op_add_assign
id|get_ksymbol_core
c_func
(paren
id|iter
)paren
suffix:semicolon
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
id|get_ksymbol_core
c_func
(paren
id|iter
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|s_next
r_static
r_void
op_star
id|s_next
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|p
comma
id|loff_t
op_star
id|pos
)paren
(brace
(paren
op_star
id|pos
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|update_iter
c_func
(paren
id|m
op_member_access_from_pointer
r_private
comma
op_star
id|pos
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|s_start
r_static
r_void
op_star
id|s_start
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|update_iter
c_func
(paren
id|m
op_member_access_from_pointer
r_private
comma
op_star
id|pos
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|m
op_member_access_from_pointer
r_private
suffix:semicolon
)brace
DECL|function|s_stop
r_static
r_void
id|s_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|p
)paren
(brace
)brace
DECL|function|s_show
r_static
r_int
id|s_show
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|p
)paren
(brace
r_struct
id|kallsym_iter
op_star
id|iter
op_assign
id|m
op_member_access_from_pointer
r_private
suffix:semicolon
multiline_comment|/* Some debugging symbols have no name.  Ignore them. */
r_if
c_cond
(paren
op_logical_neg
id|iter-&gt;name
(braket
l_int|0
)braket
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|iter-&gt;owner
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%0*lx %c %s&bslash;t[%s]&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
l_int|2
op_star
r_sizeof
(paren
r_void
op_star
)paren
)paren
comma
id|iter-&gt;value
comma
id|iter-&gt;type
comma
id|iter-&gt;name
comma
id|module_name
c_func
(paren
id|iter-&gt;owner
)paren
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%0*lx %c %s&bslash;n&quot;
comma
(paren
r_int
)paren
(paren
l_int|2
op_star
r_sizeof
(paren
r_void
op_star
)paren
)paren
comma
id|iter-&gt;value
comma
id|iter-&gt;type
comma
id|iter-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|kallsyms_op
r_struct
id|seq_operations
id|kallsyms_op
op_assign
(brace
dot
id|start
op_assign
id|s_start
comma
dot
id|next
op_assign
id|s_next
comma
dot
id|stop
op_assign
id|s_stop
comma
dot
id|show
op_assign
id|s_show
)brace
suffix:semicolon
DECL|function|kallsyms_open
r_static
r_int
id|kallsyms_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
multiline_comment|/* We keep iterator in m-&gt;private, since normal case is to&n;&t; * s_start from where we left off, so we avoid O(N^2). */
r_struct
id|kallsym_iter
op_star
id|iter
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|iter
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|iter
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iter
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|reset_iter
c_func
(paren
id|iter
)paren
suffix:semicolon
id|ret
op_assign
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|kallsyms_op
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
(paren
(paren
r_struct
id|seq_file
op_star
)paren
id|file-&gt;private_data
)paren
op_member_access_from_pointer
r_private
op_assign
id|iter
suffix:semicolon
r_else
id|kfree
c_func
(paren
id|iter
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|kallsyms_release
r_static
r_int
id|kallsyms_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|seq_file
op_star
id|m
op_assign
(paren
r_struct
id|seq_file
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
id|kfree
c_func
(paren
id|m
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
r_return
id|seq_release
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
DECL|variable|kallsyms_operations
r_static
r_struct
id|file_operations
id|kallsyms_operations
op_assign
(brace
dot
id|open
op_assign
id|kallsyms_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|kallsyms_release
comma
)brace
suffix:semicolon
DECL|function|kallsyms_init
r_int
id|__init
id|kallsyms_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;kallsyms&quot;
comma
l_int|0444
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|entry-&gt;proc_fops
op_assign
op_amp
id|kallsyms_operations
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|kallsyms_init
id|__initcall
c_func
(paren
id|kallsyms_init
)paren
suffix:semicolon
DECL|variable|__print_symbol
id|EXPORT_SYMBOL
c_func
(paren
id|__print_symbol
)paren
suffix:semicolon
eof
