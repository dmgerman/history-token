multiline_comment|/*  Kernel module help for PPC.&n;    Copyright (C) 2001 Rusty Russell.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleloader.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(fmt , ...)
macro_line|#endif
DECL|variable|module_bug_list
id|LIST_HEAD
c_func
(paren
id|module_bug_list
)paren
suffix:semicolon
DECL|function|module_alloc
r_void
op_star
id|module_alloc
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|vmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
)brace
multiline_comment|/* Free memory returned from module_alloc */
DECL|function|module_free
r_void
id|module_free
c_func
(paren
r_struct
id|module
op_star
id|mod
comma
r_void
op_star
id|module_region
)paren
(brace
id|vfree
c_func
(paren
id|module_region
)paren
suffix:semicolon
multiline_comment|/* FIXME: If module_region == mod-&gt;init_region, trim exception&n;           table entries. */
)brace
multiline_comment|/* Count how many different relocations (different symbol, different&n;   addend) */
DECL|function|count_relocs
r_static
r_int
r_int
id|count_relocs
c_func
(paren
r_const
id|Elf32_Rela
op_star
id|rela
comma
r_int
r_int
id|num
)paren
(brace
r_int
r_int
id|i
comma
id|j
comma
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Sure, this is order(n^2), but it&squot;s usually short, and not&n;           time critical */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
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
id|i
suffix:semicolon
id|j
op_increment
)paren
(brace
multiline_comment|/* If this addend appeared before, it&squot;s&n;                           already been counted */
r_if
c_cond
(paren
id|ELF32_R_SYM
c_func
(paren
id|rela
(braket
id|i
)braket
dot
id|r_info
)paren
op_eq
id|ELF32_R_SYM
c_func
(paren
id|rela
(braket
id|j
)braket
dot
id|r_info
)paren
op_logical_and
id|rela
(braket
id|i
)braket
dot
id|r_addend
op_eq
id|rela
(braket
id|j
)braket
dot
id|r_addend
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|j
op_eq
id|i
)paren
id|ret
op_increment
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Get the potential trampolines size required of the init and&n;   non-init sections */
DECL|function|get_plt_size
r_static
r_int
r_int
id|get_plt_size
c_func
(paren
r_const
id|Elf32_Ehdr
op_star
id|hdr
comma
r_const
id|Elf32_Shdr
op_star
id|sechdrs
comma
r_const
r_char
op_star
id|secstrings
comma
r_int
id|is_init
)paren
(brace
r_int
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Everything marked ALLOC (this includes the exported&n;           symbols) */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|hdr-&gt;e_shnum
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* If it&squot;s called *.init*, and we&squot;re not init, we&squot;re&n;                   not interested */
r_if
c_cond
(paren
(paren
id|strstr
c_func
(paren
id|secstrings
op_plus
id|sechdrs
(braket
id|i
)braket
dot
id|sh_name
comma
l_string|&quot;.init&quot;
)paren
op_ne
l_int|0
)paren
op_ne
id|is_init
)paren
r_continue
suffix:semicolon
multiline_comment|/* We don&squot;t want to look at debug sections. */
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|secstrings
op_plus
id|sechdrs
(braket
id|i
)braket
dot
id|sh_name
comma
l_string|&quot;.debug&quot;
)paren
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|sechdrs
(braket
id|i
)braket
dot
id|sh_type
op_eq
id|SHT_RELA
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Found relocations in section %u&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Ptr: %p.  Number: %u&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|hdr
op_plus
id|sechdrs
(braket
id|i
)braket
dot
id|sh_offset
comma
id|sechdrs
(braket
id|i
)braket
dot
id|sh_size
op_div
r_sizeof
(paren
id|Elf32_Rela
)paren
)paren
suffix:semicolon
id|ret
op_add_assign
id|count_relocs
c_func
(paren
(paren
r_void
op_star
)paren
id|hdr
op_plus
id|sechdrs
(braket
id|i
)braket
dot
id|sh_offset
comma
id|sechdrs
(braket
id|i
)braket
dot
id|sh_size
op_div
r_sizeof
(paren
id|Elf32_Rela
)paren
)paren
op_star
r_sizeof
(paren
r_struct
id|ppc_plt_entry
)paren
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|module_frob_arch_sections
r_int
id|module_frob_arch_sections
c_func
(paren
id|Elf32_Ehdr
op_star
id|hdr
comma
id|Elf32_Shdr
op_star
id|sechdrs
comma
r_char
op_star
id|secstrings
comma
r_struct
id|module
op_star
id|me
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* Find .plt and .init.plt sections */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|hdr-&gt;e_shnum
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|secstrings
op_plus
id|sechdrs
(braket
id|i
)braket
dot
id|sh_name
comma
l_string|&quot;.init.plt&quot;
)paren
op_eq
l_int|0
)paren
id|me-&gt;arch.init_plt_section
op_assign
id|i
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|secstrings
op_plus
id|sechdrs
(braket
id|i
)braket
dot
id|sh_name
comma
l_string|&quot;.plt&quot;
)paren
op_eq
l_int|0
)paren
id|me-&gt;arch.core_plt_section
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|me-&gt;arch.core_plt_section
op_logical_or
op_logical_neg
id|me-&gt;arch.init_plt_section
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Module doesn&squot;t contain .plt or .init.plt sections.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
multiline_comment|/* Override their sizes */
id|sechdrs
(braket
id|me-&gt;arch.core_plt_section
)braket
dot
id|sh_size
op_assign
id|get_plt_size
c_func
(paren
id|hdr
comma
id|sechdrs
comma
id|secstrings
comma
l_int|0
)paren
suffix:semicolon
id|sechdrs
(braket
id|me-&gt;arch.init_plt_section
)braket
dot
id|sh_size
op_assign
id|get_plt_size
c_func
(paren
id|hdr
comma
id|sechdrs
comma
id|secstrings
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|apply_relocate
r_int
id|apply_relocate
c_func
(paren
id|Elf32_Shdr
op_star
id|sechdrs
comma
r_const
r_char
op_star
id|strtab
comma
r_int
r_int
id|symindex
comma
r_int
r_int
id|relsec
comma
r_struct
id|module
op_star
id|module
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Non-ADD RELOCATION unsupported&bslash;n&quot;
comma
id|module-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
DECL|function|entry_matches
r_static
r_inline
r_int
id|entry_matches
c_func
(paren
r_struct
id|ppc_plt_entry
op_star
id|entry
comma
id|Elf32_Addr
id|val
)paren
(brace
r_if
c_cond
(paren
id|entry-&gt;jump
(braket
l_int|0
)braket
op_eq
l_int|0x3d600000
op_plus
(paren
(paren
id|val
op_plus
l_int|0x8000
)paren
op_rshift
l_int|16
)paren
op_logical_and
id|entry-&gt;jump
(braket
l_int|1
)braket
op_eq
l_int|0x396b0000
op_plus
(paren
id|val
op_amp
l_int|0xffff
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Set up a trampoline in the PLT to bounce us to the distant function */
DECL|function|do_plt_call
r_static
r_uint32
id|do_plt_call
c_func
(paren
r_void
op_star
id|location
comma
id|Elf32_Addr
id|val
comma
id|Elf32_Shdr
op_star
id|sechdrs
comma
r_struct
id|module
op_star
id|mod
)paren
(brace
r_struct
id|ppc_plt_entry
op_star
id|entry
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Doing plt for call to 0x%x at 0x%x&bslash;n&quot;
comma
id|val
comma
(paren
r_int
r_int
)paren
id|location
)paren
suffix:semicolon
multiline_comment|/* Init, or core PLT? */
r_if
c_cond
(paren
id|location
op_ge
id|mod-&gt;module_core
op_logical_and
id|location
OL
id|mod-&gt;module_core
op_plus
id|mod-&gt;core_size
)paren
id|entry
op_assign
(paren
r_void
op_star
)paren
id|sechdrs
(braket
id|mod-&gt;arch.core_plt_section
)braket
dot
id|sh_addr
suffix:semicolon
r_else
id|entry
op_assign
(paren
r_void
op_star
)paren
id|sechdrs
(braket
id|mod-&gt;arch.init_plt_section
)braket
dot
id|sh_addr
suffix:semicolon
multiline_comment|/* Find this entry, or if that fails, the next avail. entry */
r_while
c_loop
(paren
id|entry-&gt;jump
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
id|entry_matches
c_func
(paren
id|entry
comma
id|val
)paren
)paren
r_return
(paren
r_uint32
)paren
id|entry
suffix:semicolon
id|entry
op_increment
suffix:semicolon
)brace
multiline_comment|/* Stolen from Paul Mackerras as well... */
id|entry-&gt;jump
(braket
l_int|0
)braket
op_assign
l_int|0x3d600000
op_plus
(paren
(paren
id|val
op_plus
l_int|0x8000
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* lis r11,sym@ha */
id|entry-&gt;jump
(braket
l_int|1
)braket
op_assign
l_int|0x396b0000
op_plus
(paren
id|val
op_amp
l_int|0xffff
)paren
suffix:semicolon
multiline_comment|/* addi r11,r11,sym@l*/
id|entry-&gt;jump
(braket
l_int|2
)braket
op_assign
l_int|0x7d6903a6
suffix:semicolon
multiline_comment|/* mtctr r11 */
id|entry-&gt;jump
(braket
l_int|3
)braket
op_assign
l_int|0x4e800420
suffix:semicolon
multiline_comment|/* bctr */
id|DEBUGP
c_func
(paren
l_string|&quot;Initialized plt for 0x%x at %p&bslash;n&quot;
comma
id|val
comma
id|entry
)paren
suffix:semicolon
r_return
(paren
r_uint32
)paren
id|entry
suffix:semicolon
)brace
DECL|function|apply_relocate_add
r_int
id|apply_relocate_add
c_func
(paren
id|Elf32_Shdr
op_star
id|sechdrs
comma
r_const
r_char
op_star
id|strtab
comma
r_int
r_int
id|symindex
comma
r_int
r_int
id|relsec
comma
r_struct
id|module
op_star
id|module
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|Elf32_Rela
op_star
id|rela
op_assign
(paren
r_void
op_star
)paren
id|sechdrs
(braket
id|relsec
)braket
dot
id|sh_addr
suffix:semicolon
id|Elf32_Sym
op_star
id|sym
suffix:semicolon
r_uint32
op_star
id|location
suffix:semicolon
r_uint32
id|value
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Applying ADD relocate section %u to %u&bslash;n&quot;
comma
id|relsec
comma
id|sechdrs
(braket
id|relsec
)braket
dot
id|sh_info
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
id|sechdrs
(braket
id|relsec
)braket
dot
id|sh_size
op_div
r_sizeof
(paren
op_star
id|rela
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* This is where to make the change */
id|location
op_assign
(paren
r_void
op_star
)paren
id|sechdrs
(braket
id|sechdrs
(braket
id|relsec
)braket
dot
id|sh_info
)braket
dot
id|sh_addr
op_plus
id|rela
(braket
id|i
)braket
dot
id|r_offset
suffix:semicolon
multiline_comment|/* This is the symbol it is referring to.  Note that all&n;&t;&t;   undefined symbols have been resolved.  */
id|sym
op_assign
(paren
id|Elf32_Sym
op_star
)paren
id|sechdrs
(braket
id|symindex
)braket
dot
id|sh_addr
op_plus
id|ELF32_R_SYM
c_func
(paren
id|rela
(braket
id|i
)braket
dot
id|r_info
)paren
suffix:semicolon
multiline_comment|/* `Everything is relative&squot;. */
id|value
op_assign
id|sym-&gt;st_value
op_plus
id|rela
(braket
id|i
)braket
dot
id|r_addend
suffix:semicolon
r_switch
c_cond
(paren
id|ELF32_R_TYPE
c_func
(paren
id|rela
(braket
id|i
)braket
dot
id|r_info
)paren
)paren
(brace
r_case
id|R_PPC_ADDR32
suffix:colon
multiline_comment|/* Simply set it */
op_star
(paren
r_uint32
op_star
)paren
id|location
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PPC_ADDR16_LO
suffix:colon
multiline_comment|/* Low half of the symbol */
op_star
(paren
r_uint16
op_star
)paren
id|location
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PPC_ADDR16_HA
suffix:colon
multiline_comment|/* Sign-adjusted lower 16 bits: PPC ELF ABI says:&n;&t;&t;&t;   (((x &gt;&gt; 16) + ((x &amp; 0x8000) ? 1 : 0))) &amp; 0xFFFF.&n;&t;&t;&t;   This is the same, only sane.&n;&t;&t;&t; */
op_star
(paren
r_uint16
op_star
)paren
id|location
op_assign
(paren
id|value
op_plus
l_int|0x8000
)paren
op_rshift
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PPC_REL24
suffix:colon
r_if
c_cond
(paren
(paren
r_int
)paren
(paren
id|value
op_minus
(paren
r_uint32
)paren
id|location
)paren
OL
op_minus
l_int|0x02000000
op_logical_or
(paren
r_int
)paren
(paren
id|value
op_minus
(paren
r_uint32
)paren
id|location
)paren
op_ge
l_int|0x02000000
)paren
id|value
op_assign
id|do_plt_call
c_func
(paren
id|location
comma
id|value
comma
id|sechdrs
comma
id|module
)paren
suffix:semicolon
multiline_comment|/* Only replace bits 2 through 26 */
id|DEBUGP
c_func
(paren
l_string|&quot;REL24 value = %08X. location = %08X&bslash;n&quot;
comma
id|value
comma
(paren
r_uint32
)paren
id|location
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Location before: %08X.&bslash;n&quot;
comma
op_star
(paren
r_uint32
op_star
)paren
id|location
)paren
suffix:semicolon
op_star
(paren
r_uint32
op_star
)paren
id|location
op_assign
(paren
op_star
(paren
r_uint32
op_star
)paren
id|location
op_amp
op_complement
l_int|0x03fffffc
)paren
op_or
(paren
(paren
id|value
op_minus
(paren
r_uint32
)paren
id|location
)paren
op_amp
l_int|0x03fffffc
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Location after: %08X.&bslash;n&quot;
comma
op_star
(paren
r_uint32
op_star
)paren
id|location
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;ie. jump to %08X+%08X = %08X&bslash;n&quot;
comma
op_star
(paren
r_uint32
op_star
)paren
id|location
op_amp
l_int|0x03fffffc
comma
(paren
r_uint32
)paren
id|location
comma
(paren
op_star
(paren
r_uint32
op_star
)paren
id|location
op_amp
l_int|0x03fffffc
)paren
op_plus
(paren
r_uint32
)paren
id|location
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PPC_REL32
suffix:colon
multiline_comment|/* 32-bit relative jump. */
op_star
(paren
r_uint32
op_star
)paren
id|location
op_assign
id|value
op_minus
(paren
r_uint32
)paren
id|location
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s: unknown ADD relocation: %u&bslash;n&quot;
comma
id|module-&gt;name
comma
id|ELF32_R_TYPE
c_func
(paren
id|rela
(braket
id|i
)braket
dot
id|r_info
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|module_finalize
r_int
id|module_finalize
c_func
(paren
r_const
id|Elf_Ehdr
op_star
id|hdr
comma
r_const
id|Elf_Shdr
op_star
id|sechdrs
comma
r_struct
id|module
op_star
id|me
)paren
(brace
r_char
op_star
id|secstrings
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|me-&gt;arch.bug_table
op_assign
l_int|NULL
suffix:semicolon
id|me-&gt;arch.num_bugs
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Find the __bug_table section, if present */
id|secstrings
op_assign
(paren
r_char
op_star
)paren
id|hdr
op_plus
id|sechdrs
(braket
id|hdr-&gt;e_shstrndx
)braket
dot
id|sh_offset
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|hdr-&gt;e_shnum
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|secstrings
op_plus
id|sechdrs
(braket
id|i
)braket
dot
id|sh_name
comma
l_string|&quot;__bug_table&quot;
)paren
)paren
r_continue
suffix:semicolon
id|me-&gt;arch.bug_table
op_assign
(paren
r_void
op_star
)paren
id|sechdrs
(braket
id|i
)braket
dot
id|sh_addr
suffix:semicolon
id|me-&gt;arch.num_bugs
op_assign
id|sechdrs
(braket
id|i
)braket
dot
id|sh_size
op_div
r_sizeof
(paren
r_struct
id|bug_entry
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Strictly speaking this should have a spinlock to protect against&n;&t; * traversals, but since we only traverse on BUG()s, a spinlock&n;&t; * could potentially lead to deadlock and thus be counter-productive.&n;&t; */
id|list_add
c_func
(paren
op_amp
id|me-&gt;arch.bug_list
comma
op_amp
id|module_bug_list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|module_arch_cleanup
r_void
id|module_arch_cleanup
c_func
(paren
r_struct
id|module
op_star
id|mod
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|mod-&gt;arch.bug_list
)paren
suffix:semicolon
)brace
DECL|function|module_find_bug
r_struct
id|bug_entry
op_star
id|module_find_bug
c_func
(paren
r_int
r_int
id|bugaddr
)paren
(brace
r_struct
id|mod_arch_specific
op_star
id|mod
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_struct
id|bug_entry
op_star
id|bug
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|mod
comma
op_amp
id|module_bug_list
comma
id|bug_list
)paren
(brace
id|bug
op_assign
id|mod-&gt;bug_table
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
id|mod-&gt;num_bugs
suffix:semicolon
op_increment
id|i
comma
op_increment
id|bug
)paren
r_if
c_cond
(paren
id|bugaddr
op_eq
id|bug-&gt;bug_addr
)paren
r_return
id|bug
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
eof
