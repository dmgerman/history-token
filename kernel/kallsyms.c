multiline_comment|/*&n; * kksymoops.c: in-kernel printing of symbolic oopses and stack traces.&n; *&n; *  Copyright 2000 Keith Owens &lt;kaos@ocs.com.au&gt; April 2000&n; *  Copyright 2002 Arjan van de Ven &lt;arjanv@redhat.com&gt;&n; *&n;   This code uses the list of all kernel and module symbols to :-&n;&n;   * Find any non-stack symbol in a kernel or module.  Symbols do&n;     not have to be exported for debugging.&n;&n;   * Convert an address to the module (or kernel) that owns it, the&n;     section it is in and the nearest symbol.  This finds all non-stack&n;     symbols, not just exported ones.&n;&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kallsyms.h&gt;
multiline_comment|/* A symbol can appear in more than one module.  A token is used to&n; * restart the scan at the next module, set the token to 0 for the&n; * first scan of each symbol.&n; */
DECL|function|kallsyms_symbol_to_address
r_int
id|kallsyms_symbol_to_address
c_func
(paren
r_const
r_char
op_star
id|name
comma
multiline_comment|/* Name to lookup */
r_int
r_int
op_star
id|token
comma
multiline_comment|/* Which module to start at */
r_const
r_char
op_star
op_star
id|mod_name
comma
multiline_comment|/* Set to module name */
r_int
r_int
op_star
id|mod_start
comma
multiline_comment|/* Set to start address of module */
r_int
r_int
op_star
id|mod_end
comma
multiline_comment|/* Set to end address of module */
r_const
r_char
op_star
op_star
id|sec_name
comma
multiline_comment|/* Set to section name */
r_int
r_int
op_star
id|sec_start
comma
multiline_comment|/* Set to start address of section */
r_int
r_int
op_star
id|sec_end
comma
multiline_comment|/* Set to end address of section */
r_const
r_char
op_star
op_star
id|sym_name
comma
multiline_comment|/* Set to full symbol name */
r_int
r_int
op_star
id|sym_start
comma
multiline_comment|/* Set to start address of symbol */
r_int
r_int
op_star
id|sym_end
multiline_comment|/* Set to end address of symbol */
)paren
(brace
r_const
r_struct
id|kallsyms_header
op_star
id|ka_hdr
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* stupid gcc */
r_const
r_struct
id|kallsyms_section
op_star
id|ka_sec
suffix:semicolon
r_const
r_struct
id|kallsyms_symbol
op_star
id|ka_sym
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|ka_str
op_assign
l_int|NULL
suffix:semicolon
r_const
r_struct
id|module
op_star
id|m
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|l
suffix:semicolon
r_const
r_char
op_star
id|p
comma
op_star
id|pt_R
suffix:semicolon
r_char
op_star
id|p2
suffix:semicolon
multiline_comment|/* Restart? */
id|m
op_assign
id|module_list
suffix:semicolon
r_if
c_cond
(paren
id|token
op_logical_and
op_star
id|token
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|m
suffix:semicolon
id|m
op_assign
id|m-&gt;next
)paren
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|m
op_eq
op_star
id|token
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|m
)paren
id|m
op_assign
id|m-&gt;next
suffix:semicolon
)brace
r_for
c_loop
(paren
suffix:semicolon
id|m
suffix:semicolon
id|m
op_assign
id|m-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mod_member_present
c_func
(paren
id|m
comma
id|kallsyms_start
)paren
op_logical_or
op_logical_neg
id|mod_member_present
c_func
(paren
id|m
comma
id|kallsyms_end
)paren
op_logical_or
id|m-&gt;kallsyms_start
op_ge
id|m-&gt;kallsyms_end
)paren
r_continue
suffix:semicolon
id|ka_hdr
op_assign
(paren
r_struct
id|kallsyms_header
op_star
)paren
id|m-&gt;kallsyms_start
suffix:semicolon
id|ka_sym
op_assign
(paren
r_struct
id|kallsyms_symbol
op_star
)paren
(paren
(paren
r_char
op_star
)paren
(paren
id|ka_hdr
)paren
op_plus
id|ka_hdr-&gt;symbol_off
)paren
suffix:semicolon
id|ka_str
op_assign
(paren
(paren
r_char
op_star
)paren
(paren
id|ka_hdr
)paren
op_plus
id|ka_hdr-&gt;string_off
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
id|ka_hdr-&gt;symbols
suffix:semicolon
op_increment
id|i
comma
id|kallsyms_next_sym
c_func
(paren
id|ka_hdr
comma
id|ka_sym
)paren
)paren
(brace
id|p
op_assign
id|ka_str
op_plus
id|ka_sym-&gt;name_off
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|p
comma
id|name
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* Unversioned requests match versioned names */
r_if
c_cond
(paren
op_logical_neg
(paren
id|pt_R
op_assign
id|strstr
c_func
(paren
id|p
comma
l_string|&quot;_R&quot;
)paren
)paren
)paren
r_continue
suffix:semicolon
id|l
op_assign
id|strlen
c_func
(paren
id|pt_R
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l
OL
l_int|10
)paren
r_continue
suffix:semicolon
multiline_comment|/* Not _R.*xxxxxxxx */
(paren
r_void
)paren
id|simple_strtoul
c_func
(paren
id|pt_R
op_plus
id|l
op_minus
l_int|8
comma
op_amp
id|p2
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p2
)paren
r_continue
suffix:semicolon
multiline_comment|/* Not _R.*xxxxxxxx */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|p
comma
id|name
comma
id|pt_R
op_minus
id|p
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* Match with version */
)brace
r_if
c_cond
(paren
id|i
OL
id|ka_hdr-&gt;symbols
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|token
)paren
op_star
id|token
op_assign
(paren
r_int
r_int
)paren
id|m
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|m
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* not found */
id|ka_sec
op_assign
(paren
r_const
r_struct
id|kallsyms_section
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|ka_hdr
op_plus
id|ka_hdr-&gt;section_off
op_plus
id|ka_sym-&gt;section_off
)paren
suffix:semicolon
op_star
id|mod_name
op_assign
id|m-&gt;name
suffix:semicolon
op_star
id|mod_start
op_assign
id|ka_hdr-&gt;start
suffix:semicolon
op_star
id|mod_end
op_assign
id|ka_hdr-&gt;end
suffix:semicolon
op_star
id|sec_name
op_assign
id|ka_sec-&gt;name_off
op_plus
id|ka_str
suffix:semicolon
op_star
id|sec_start
op_assign
id|ka_sec-&gt;start
suffix:semicolon
op_star
id|sec_end
op_assign
id|ka_sec-&gt;start
op_plus
id|ka_sec-&gt;size
suffix:semicolon
op_star
id|sym_name
op_assign
id|ka_sym-&gt;name_off
op_plus
id|ka_str
suffix:semicolon
op_star
id|sym_start
op_assign
id|ka_sym-&gt;symbol_addr
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|ka_hdr-&gt;symbols
op_minus
l_int|1
)paren
(brace
r_const
r_struct
id|kallsyms_symbol
op_star
id|ka_symn
op_assign
id|ka_sym
suffix:semicolon
id|kallsyms_next_sym
c_func
(paren
id|ka_hdr
comma
id|ka_symn
)paren
suffix:semicolon
op_star
id|sym_end
op_assign
id|ka_symn-&gt;symbol_addr
suffix:semicolon
)brace
r_else
op_star
id|sym_end
op_assign
op_star
id|sec_end
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|kallsyms_address_to_symbol
r_int
id|kallsyms_address_to_symbol
c_func
(paren
r_int
r_int
id|address
comma
multiline_comment|/* Address to lookup */
r_const
r_char
op_star
op_star
id|mod_name
comma
multiline_comment|/* Set to module name */
r_int
r_int
op_star
id|mod_start
comma
multiline_comment|/* Set to start address of module */
r_int
r_int
op_star
id|mod_end
comma
multiline_comment|/* Set to end address of module */
r_const
r_char
op_star
op_star
id|sec_name
comma
multiline_comment|/* Set to section name */
r_int
r_int
op_star
id|sec_start
comma
multiline_comment|/* Set to start address of section */
r_int
r_int
op_star
id|sec_end
comma
multiline_comment|/* Set to end address of section */
r_const
r_char
op_star
op_star
id|sym_name
comma
multiline_comment|/* Set to full symbol name */
r_int
r_int
op_star
id|sym_start
comma
multiline_comment|/* Set to start address of symbol */
r_int
r_int
op_star
id|sym_end
multiline_comment|/* Set to end address of symbol */
)paren
(brace
r_const
r_struct
id|kallsyms_header
op_star
id|ka_hdr
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* stupid gcc */
r_const
r_struct
id|kallsyms_section
op_star
id|ka_sec
op_assign
l_int|NULL
suffix:semicolon
r_const
r_struct
id|kallsyms_symbol
op_star
id|ka_sym
suffix:semicolon
r_const
r_char
op_star
id|ka_str
suffix:semicolon
r_const
r_struct
id|module
op_star
id|m
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
r_for
c_loop
(paren
id|m
op_assign
id|module_list
suffix:semicolon
id|m
suffix:semicolon
id|m
op_assign
id|m-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mod_member_present
c_func
(paren
id|m
comma
id|kallsyms_start
)paren
op_logical_or
op_logical_neg
id|mod_member_present
c_func
(paren
id|m
comma
id|kallsyms_end
)paren
op_logical_or
id|m-&gt;kallsyms_start
op_ge
id|m-&gt;kallsyms_end
)paren
r_continue
suffix:semicolon
id|ka_hdr
op_assign
(paren
r_struct
id|kallsyms_header
op_star
)paren
id|m-&gt;kallsyms_start
suffix:semicolon
id|ka_sec
op_assign
(paren
r_const
r_struct
id|kallsyms_section
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|ka_hdr
op_plus
id|ka_hdr-&gt;section_off
)paren
suffix:semicolon
multiline_comment|/* Is the address in any section in this module? */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ka_hdr-&gt;sections
suffix:semicolon
op_increment
id|i
comma
id|kallsyms_next_sec
c_func
(paren
id|ka_hdr
comma
id|ka_sec
)paren
)paren
(brace
r_if
c_cond
(paren
id|ka_sec-&gt;start
op_le
id|address
op_logical_and
(paren
id|ka_sec-&gt;start
op_plus
id|ka_sec-&gt;size
)paren
OG
id|address
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|ka_hdr-&gt;sections
)paren
r_break
suffix:semicolon
multiline_comment|/* Found a matching section */
)brace
r_if
c_cond
(paren
op_logical_neg
id|m
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* not found */
id|ka_sym
op_assign
(paren
r_struct
id|kallsyms_symbol
op_star
)paren
(paren
(paren
r_char
op_star
)paren
(paren
id|ka_hdr
)paren
op_plus
id|ka_hdr-&gt;symbol_off
)paren
suffix:semicolon
id|ka_str
op_assign
(paren
(paren
r_char
op_star
)paren
(paren
id|ka_hdr
)paren
op_plus
id|ka_hdr-&gt;string_off
)paren
suffix:semicolon
op_star
id|mod_name
op_assign
id|m-&gt;name
suffix:semicolon
op_star
id|mod_start
op_assign
id|ka_hdr-&gt;start
suffix:semicolon
op_star
id|mod_end
op_assign
id|ka_hdr-&gt;end
suffix:semicolon
op_star
id|sec_name
op_assign
id|ka_sec-&gt;name_off
op_plus
id|ka_str
suffix:semicolon
op_star
id|sec_start
op_assign
id|ka_sec-&gt;start
suffix:semicolon
op_star
id|sec_end
op_assign
id|ka_sec-&gt;start
op_plus
id|ka_sec-&gt;size
suffix:semicolon
op_star
id|sym_name
op_assign
op_star
id|sec_name
suffix:semicolon
multiline_comment|/* In case we find no matching symbol */
op_star
id|sym_start
op_assign
op_star
id|sec_start
suffix:semicolon
op_star
id|sym_end
op_assign
op_star
id|sec_end
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
id|ka_hdr-&gt;symbols
suffix:semicolon
op_increment
id|i
comma
id|kallsyms_next_sym
c_func
(paren
id|ka_hdr
comma
id|ka_sym
)paren
)paren
(brace
r_if
c_cond
(paren
id|ka_sym-&gt;symbol_addr
OG
id|address
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|ka_hdr-&gt;symbols
op_minus
l_int|1
)paren
(brace
r_const
r_struct
id|kallsyms_symbol
op_star
id|ka_symn
op_assign
id|ka_sym
suffix:semicolon
id|kallsyms_next_sym
c_func
(paren
id|ka_hdr
comma
id|ka_symn
)paren
suffix:semicolon
id|end
op_assign
id|ka_symn-&gt;symbol_addr
suffix:semicolon
)brace
r_else
id|end
op_assign
op_star
id|sec_end
suffix:semicolon
r_if
c_cond
(paren
id|end
op_le
id|address
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
id|ka_hdr
op_plus
id|ka_hdr-&gt;section_off
op_plus
id|ka_sym-&gt;section_off
op_ne
(paren
r_char
op_star
)paren
id|ka_sec
)paren
r_continue
suffix:semicolon
multiline_comment|/* wrong section */
op_star
id|sym_name
op_assign
id|ka_str
op_plus
id|ka_sym-&gt;name_off
suffix:semicolon
op_star
id|sym_start
op_assign
id|ka_sym-&gt;symbol_addr
suffix:semicolon
op_star
id|sym_end
op_assign
id|end
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* List all sections in all modules.  The callback routine is invoked with&n; * token, module name, section name, section start, section end, section flags.&n; */
DECL|function|kallsyms_sections
r_int
id|kallsyms_sections
c_func
(paren
r_void
op_star
id|token
comma
r_int
(paren
op_star
id|callback
)paren
(paren
r_void
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
id|ElfW
c_func
(paren
id|Addr
)paren
comma
id|ElfW
c_func
(paren
id|Addr
)paren
comma
id|ElfW
c_func
(paren
id|Word
)paren
)paren
)paren
(brace
r_const
r_struct
id|kallsyms_header
op_star
id|ka_hdr
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* stupid gcc */
r_const
r_struct
id|kallsyms_section
op_star
id|ka_sec
op_assign
l_int|NULL
suffix:semicolon
r_const
r_char
op_star
id|ka_str
suffix:semicolon
r_const
r_struct
id|module
op_star
id|m
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|m
op_assign
id|module_list
suffix:semicolon
id|m
suffix:semicolon
id|m
op_assign
id|m-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mod_member_present
c_func
(paren
id|m
comma
id|kallsyms_start
)paren
op_logical_or
op_logical_neg
id|mod_member_present
c_func
(paren
id|m
comma
id|kallsyms_end
)paren
op_logical_or
id|m-&gt;kallsyms_start
op_ge
id|m-&gt;kallsyms_end
)paren
r_continue
suffix:semicolon
id|ka_hdr
op_assign
(paren
r_struct
id|kallsyms_header
op_star
)paren
id|m-&gt;kallsyms_start
suffix:semicolon
id|ka_sec
op_assign
(paren
r_const
r_struct
id|kallsyms_section
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|ka_hdr
op_plus
id|ka_hdr-&gt;section_off
)paren
suffix:semicolon
id|ka_str
op_assign
(paren
(paren
r_char
op_star
)paren
(paren
id|ka_hdr
)paren
op_plus
id|ka_hdr-&gt;string_off
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
id|ka_hdr-&gt;sections
suffix:semicolon
op_increment
id|i
comma
id|kallsyms_next_sec
c_func
(paren
id|ka_hdr
comma
id|ka_sec
)paren
)paren
(brace
r_if
c_cond
(paren
id|callback
c_func
(paren
id|token
comma
op_star
(paren
id|m-&gt;name
)paren
ques
c_cond
id|m-&gt;name
suffix:colon
l_string|&quot;kernel&quot;
comma
id|ka_sec-&gt;name_off
op_plus
id|ka_str
comma
id|ka_sec-&gt;start
comma
id|ka_sec-&gt;start
op_plus
id|ka_sec-&gt;size
comma
id|ka_sec-&gt;flags
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
eof
