multiline_comment|/* kallsyms headers&n;   Copyright 2000 Keith Owens &lt;kaos@ocs.com.au&gt;&n;&n;   This file is part of the Linux modutils.  It is exported to kernel&n;   space so debuggers can access the kallsyms data.&n;&n;   The kallsyms data contains all the non-stack symbols from a kernel&n;   or a module.  The kernel symbols are held between __start___kallsyms&n;   and __stop___kallsyms.  The symbols for a module are accessed via&n;   the struct module chain which is based at module_list.&n;&n;   This program is free software; you can redistribute it and/or modify it&n;   under the terms of the GNU General Public License as published by the&n;   Free Software Foundation; either version 2 of the License, or (at your&n;   option) any later version.&n;&n;   This program is distributed in the hope that it will be useful, but&n;   WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;   General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software Foundation,&n;   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; */
macro_line|#ident &quot;$Id: linux-2.4.9-kallsyms.patch,v 1.8 2002/02/11 18:34:53 arjanv Exp $&quot;
macro_line|#ifndef MODUTILS_KALLSYMS_H
DECL|macro|MODUTILS_KALLSYMS_H
mdefine_line|#define MODUTILS_KALLSYMS_H 1
multiline_comment|/* Have to (re)define these ElfW entries here because external kallsyms&n; * code does not have access to modutils/include/obj.h.  This code is&n; * included from user spaces tools (modutils) and kernel, they need&n; * different includes.&n; */
macro_line|#ifndef ELFCLASS32
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#else&t;/* __KERNEL__ */
macro_line|#include &lt;elf.h&gt;
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif&t;/* ELFCLASS32 */
macro_line|#ifndef ELFCLASSM
DECL|macro|ELFCLASSM
mdefine_line|#define ELFCLASSM ELF_CLASS
macro_line|#endif
macro_line|#ifndef ElfW
macro_line|# if ELFCLASSM == ELFCLASS32
DECL|macro|ElfW
macro_line|#  define ElfW(x)  Elf32_ ## x
DECL|macro|ELFW
macro_line|#  define ELFW(x)  ELF32_ ## x
macro_line|# else
DECL|macro|ElfW
macro_line|#  define ElfW(x)  Elf64_ ## x
DECL|macro|ELFW
macro_line|#  define ELFW(x)  ELF64_ ## x
macro_line|# endif
macro_line|#endif
multiline_comment|/* Format of data in the kallsyms section.&n; * Most of the fields are small numbers but the total size and all&n; * offsets can be large so use the 32/64 bit types for these fields.&n; *&n; * Do not use sizeof() on these structures, modutils may be using extra&n; * fields.  Instead use the size fields in the header to access the&n; * other bits of data.&n; */
DECL|struct|kallsyms_header
r_struct
id|kallsyms_header
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* Size of this header */
id|ElfW
c_func
(paren
id|Word
)paren
id|total_size
suffix:semicolon
multiline_comment|/* Total size of kallsyms data */
DECL|member|sections
r_int
id|sections
suffix:semicolon
multiline_comment|/* Number of section entries */
id|ElfW
c_func
(paren
id|Off
)paren
id|section_off
suffix:semicolon
multiline_comment|/* Offset to first section entry */
DECL|member|section_size
r_int
id|section_size
suffix:semicolon
multiline_comment|/* Size of one section entry */
DECL|member|symbols
r_int
id|symbols
suffix:semicolon
multiline_comment|/* Number of symbol entries */
id|ElfW
c_func
(paren
id|Off
)paren
id|symbol_off
suffix:semicolon
multiline_comment|/* Offset to first symbol entry */
DECL|member|symbol_size
r_int
id|symbol_size
suffix:semicolon
multiline_comment|/* Size of one symbol entry */
id|ElfW
c_func
(paren
id|Off
)paren
id|string_off
suffix:semicolon
multiline_comment|/* Offset to first string */
id|ElfW
c_func
(paren
id|Addr
)paren
id|start
suffix:semicolon
multiline_comment|/* Start address of first section */
id|ElfW
c_func
(paren
id|Addr
)paren
id|end
suffix:semicolon
multiline_comment|/* End address of last section */
)brace
suffix:semicolon
DECL|struct|kallsyms_section
r_struct
id|kallsyms_section
(brace
id|ElfW
c_func
(paren
id|Addr
)paren
id|start
suffix:semicolon
multiline_comment|/* Start address of section */
id|ElfW
c_func
(paren
id|Word
)paren
id|size
suffix:semicolon
multiline_comment|/* Size of this section */
id|ElfW
c_func
(paren
id|Off
)paren
id|name_off
suffix:semicolon
multiline_comment|/* Offset to section name */
id|ElfW
c_func
(paren
id|Word
)paren
id|flags
suffix:semicolon
multiline_comment|/* Flags from section */
)brace
suffix:semicolon
DECL|struct|kallsyms_symbol
r_struct
id|kallsyms_symbol
(brace
id|ElfW
c_func
(paren
id|Off
)paren
id|section_off
suffix:semicolon
multiline_comment|/* Offset to section that owns this symbol */
id|ElfW
c_func
(paren
id|Addr
)paren
id|symbol_addr
suffix:semicolon
multiline_comment|/* Address of symbol */
id|ElfW
c_func
(paren
id|Off
)paren
id|name_off
suffix:semicolon
multiline_comment|/* Offset to symbol name */
)brace
suffix:semicolon
DECL|macro|KALLSYMS_SEC_NAME
mdefine_line|#define KALLSYMS_SEC_NAME &quot;__kallsyms&quot;
DECL|macro|KALLSYMS_IDX
mdefine_line|#define KALLSYMS_IDX 2&t;&t;&t;/* obj_kallsyms creates kallsyms as section 2 */
DECL|macro|kallsyms_next_sec
mdefine_line|#define kallsyms_next_sec(h,s) &bslash;&n;&t;((s) = (struct kallsyms_section *)((char *)(s) + (h)-&gt;section_size))
DECL|macro|kallsyms_next_sym
mdefine_line|#define kallsyms_next_sym(h,s) &bslash;&n;&t;((s) = (struct kallsyms_symbol *)((char *)(s) + (h)-&gt;symbol_size))
macro_line|#ifdef CONFIG_KALLSYMS
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
multiline_comment|/* Which module to start with */
r_const
r_char
op_star
op_star
id|mod_name
comma
multiline_comment|/* Set to module name or &quot;kernel&quot; */
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
suffix:semicolon
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
suffix:semicolon
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
multiline_comment|/* token */
r_const
r_char
op_star
comma
multiline_comment|/* module name */
r_const
r_char
op_star
comma
multiline_comment|/* section name */
id|ElfW
c_func
(paren
id|Addr
)paren
comma
multiline_comment|/* Section start */
id|ElfW
c_func
(paren
id|Addr
)paren
comma
multiline_comment|/* Section end */
id|ElfW
c_func
(paren
id|Word
)paren
multiline_comment|/* Section flags */
)paren
)paren
suffix:semicolon
macro_line|#else
DECL|function|kallsyms_address_to_symbol
r_static
r_inline
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
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* kallsyms.h */
eof
