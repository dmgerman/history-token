multiline_comment|/* Rewritten and vastly simplified by Rusty Russell for in-kernel&n; * module loader:&n; *   Copyright 2002 Rusty Russell &lt;rusty@rustcorp.com.au&gt; IBM Corporation&n; */
macro_line|#ifndef _LINUX_KALLSYMS_H
DECL|macro|_LINUX_KALLSYMS_H
mdefine_line|#define _LINUX_KALLSYMS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_KALLSYMS
multiline_comment|/* Lookup an address.  modname is set to NULL if it&squot;s in the kernel. */
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
suffix:semicolon
multiline_comment|/* Replace &quot;%s&quot; in format with address, if found */
r_extern
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
suffix:semicolon
macro_line|#else /* !CONFIG_KALLSYMS */
DECL|function|kallsyms_lookup
r_static
r_inline
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
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Stupid that this does nothing, but I didn&squot;t create this mess. */
DECL|macro|__print_symbol
mdefine_line|#define __print_symbol(fmt, addr)
macro_line|#endif /*CONFIG_KALLSYMS*/
multiline_comment|/* This macro allows us to keep printk typechecking */
r_static
r_void
id|__check_printsym_format
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
c_func
(paren
(paren
id|format
c_func
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
suffix:semicolon
DECL|function|__check_printsym_format
r_static
r_inline
r_void
id|__check_printsym_format
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
)brace
DECL|macro|print_symbol
mdefine_line|#define print_symbol(fmt, addr)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__check_printsym_format(fmt, &quot;&quot;);&t;&bslash;&n;&t;__print_symbol(fmt, addr);&t;&t;&bslash;&n;} while(0)
macro_line|#endif /*_LINUX_KALLSYMS_H*/
eof
