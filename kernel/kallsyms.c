multiline_comment|/*&n; * kallsyms.c: in-kernel printing of symbolic oopses and stack traces.&n; *&n; * Rewritten and vastly simplified by Rusty Russell for in-kernel&n; * module loader:&n; *   Copyright 2002 Rusty Russell &lt;rusty@rustcorp.com.au&gt; IBM Corporation&n; * Stem compression by Andi Kleen.&n; */
macro_line|#include &lt;linux/kallsyms.h&gt;
macro_line|#include &lt;linux/module.h&gt;
DECL|variable|kallsyms_dummy
r_static
r_char
id|kallsyms_dummy
suffix:semicolon
multiline_comment|/* These will be re-linked against their real values during the second link stage */
r_extern
r_int
r_int
id|kallsyms_addresses
(braket
l_int|1
)braket
id|__attribute__
c_func
(paren
(paren
id|weak
comma
id|alias
c_func
(paren
l_string|&quot;kallsyms_dummy&quot;
)paren
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
comma
id|alias
c_func
(paren
l_string|&quot;kallsyms_dummy&quot;
)paren
)paren
)paren
suffix:semicolon
r_extern
r_char
id|kallsyms_names
(braket
l_int|1
)braket
id|__attribute__
c_func
(paren
(paren
id|weak
comma
id|alias
c_func
(paren
l_string|&quot;kallsyms_dummy&quot;
)paren
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
suffix:semicolon
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
r_if
c_cond
(paren
(paren
r_void
op_star
)paren
id|kallsyms_addresses
op_eq
op_amp
id|kallsyms_dummy
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|namebuf
(braket
l_int|127
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
OL
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
l_int|127
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
multiline_comment|/* Base symbol size on next symbol. */
r_if
c_cond
(paren
id|best
op_plus
l_int|1
OL
id|kallsyms_num_syms
)paren
id|symbol_end
op_assign
id|kallsyms_addresses
(braket
id|best
op_plus
l_int|1
)braket
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
l_int|128
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
(brace
r_char
id|addrstr
(braket
r_sizeof
(paren
l_string|&quot;0x%lx&quot;
)paren
op_plus
(paren
id|BITS_PER_LONG
op_star
l_int|3
op_div
l_int|10
)paren
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|addrstr
comma
l_string|&quot;0x%lx&quot;
comma
id|address
)paren
suffix:semicolon
id|printk
c_func
(paren
id|fmt
comma
id|addrstr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|modname
)paren
(brace
multiline_comment|/* This is pretty small. */
r_char
id|buffer
(braket
r_sizeof
(paren
l_string|&quot;%s+%#lx/%#lx [%s]&quot;
)paren
op_plus
id|strlen
c_func
(paren
id|name
)paren
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
id|strlen
c_func
(paren
id|modname
)paren
)braket
suffix:semicolon
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
id|printk
c_func
(paren
id|fmt
comma
id|buffer
)paren
suffix:semicolon
)brace
r_else
(brace
r_char
id|buffer
(braket
r_sizeof
(paren
l_string|&quot;%s+%#lx/%#lx&quot;
)paren
op_plus
id|strlen
c_func
(paren
id|name
)paren
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
)braket
suffix:semicolon
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
id|printk
c_func
(paren
id|fmt
comma
id|buffer
)paren
suffix:semicolon
)brace
)brace
DECL|variable|kallsyms_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|kallsyms_lookup
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
