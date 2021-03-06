multiline_comment|/*&n; *  arch/s390/kernel/module.c - Kernel module help for s390.&n; *&n; *  S390 version&n; *    Copyright (C) 2002, 2003 IBM Deutschland Entwicklung GmbH,&n; *&t;&t;&t;       IBM Corporation&n; *    Author(s): Arnd Bergmann (arndb@de.ibm.com)&n; *&t;&t; Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; *  based on i386 version&n; *    Copyright (C) 2001 Rusty Russell.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(fmt , ...)
macro_line|#endif
macro_line|#ifndef CONFIG_ARCH_S390X
DECL|macro|PLT_ENTRY_SIZE
mdefine_line|#define PLT_ENTRY_SIZE 12
macro_line|#else /* CONFIG_ARCH_S390X */
DECL|macro|PLT_ENTRY_SIZE
mdefine_line|#define PLT_ENTRY_SIZE 20
macro_line|#endif /* CONFIG_ARCH_S390X */
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
r_static
r_inline
r_void
DECL|function|check_rela
id|check_rela
c_func
(paren
id|Elf_Rela
op_star
id|rela
comma
r_struct
id|module
op_star
id|me
)paren
(brace
r_struct
id|mod_arch_syminfo
op_star
id|info
suffix:semicolon
id|info
op_assign
id|me-&gt;arch.syminfo
op_plus
id|ELF_R_SYM
(paren
id|rela-&gt;r_info
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ELF_R_TYPE
(paren
id|rela-&gt;r_info
)paren
)paren
(brace
r_case
id|R_390_GOT12
suffix:colon
multiline_comment|/* 12 bit GOT offset.  */
r_case
id|R_390_GOT16
suffix:colon
multiline_comment|/* 16 bit GOT offset.  */
r_case
id|R_390_GOT20
suffix:colon
multiline_comment|/* 20 bit GOT offset.  */
r_case
id|R_390_GOT32
suffix:colon
multiline_comment|/* 32 bit GOT offset.  */
r_case
id|R_390_GOT64
suffix:colon
multiline_comment|/* 64 bit GOT offset.  */
r_case
id|R_390_GOTENT
suffix:colon
multiline_comment|/* 32 bit PC rel. to GOT entry shifted by 1. */
r_case
id|R_390_GOTPLT12
suffix:colon
multiline_comment|/* 12 bit offset to jump slot.&t;*/
r_case
id|R_390_GOTPLT16
suffix:colon
multiline_comment|/* 16 bit offset to jump slot.  */
r_case
id|R_390_GOTPLT20
suffix:colon
multiline_comment|/* 20 bit offset to jump slot.  */
r_case
id|R_390_GOTPLT32
suffix:colon
multiline_comment|/* 32 bit offset to jump slot.  */
r_case
id|R_390_GOTPLT64
suffix:colon
multiline_comment|/* 64 bit offset to jump slot.&t;*/
r_case
id|R_390_GOTPLTENT
suffix:colon
multiline_comment|/* 32 bit rel. offset to jump slot &gt;&gt; 1. */
r_if
c_cond
(paren
id|info-&gt;got_offset
op_eq
op_minus
l_int|1UL
)paren
(brace
id|info-&gt;got_offset
op_assign
id|me-&gt;arch.got_size
suffix:semicolon
id|me-&gt;arch.got_size
op_add_assign
r_sizeof
(paren
r_void
op_star
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|R_390_PLT16DBL
suffix:colon
multiline_comment|/* 16 bit PC rel. PLT shifted by 1.  */
r_case
id|R_390_PLT32DBL
suffix:colon
multiline_comment|/* 32 bit PC rel. PLT shifted by 1.  */
r_case
id|R_390_PLT32
suffix:colon
multiline_comment|/* 32 bit PC relative PLT address.  */
r_case
id|R_390_PLT64
suffix:colon
multiline_comment|/* 64 bit PC relative PLT address.  */
r_case
id|R_390_PLTOFF16
suffix:colon
multiline_comment|/* 16 bit offset from GOT to PLT. */
r_case
id|R_390_PLTOFF32
suffix:colon
multiline_comment|/* 32 bit offset from GOT to PLT. */
r_case
id|R_390_PLTOFF64
suffix:colon
multiline_comment|/* 16 bit offset from GOT to PLT. */
r_if
c_cond
(paren
id|info-&gt;plt_offset
op_eq
op_minus
l_int|1UL
)paren
(brace
id|info-&gt;plt_offset
op_assign
id|me-&gt;arch.plt_size
suffix:semicolon
id|me-&gt;arch.plt_size
op_add_assign
id|PLT_ENTRY_SIZE
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|R_390_COPY
suffix:colon
r_case
id|R_390_GLOB_DAT
suffix:colon
r_case
id|R_390_JMP_SLOT
suffix:colon
r_case
id|R_390_RELATIVE
suffix:colon
multiline_comment|/* Only needed if we want to support loading of &n;&t;&t;   modules linked with -shared. */
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Account for GOT and PLT relocations. We can&squot;t add sections for&n; * got and plt but we can increase the core module size.&n; */
r_int
DECL|function|module_frob_arch_sections
id|module_frob_arch_sections
c_func
(paren
id|Elf_Ehdr
op_star
id|hdr
comma
id|Elf_Shdr
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
id|Elf_Shdr
op_star
id|symtab
suffix:semicolon
id|Elf_Sym
op_star
id|symbols
suffix:semicolon
id|Elf_Rela
op_star
id|rela
suffix:semicolon
r_char
op_star
id|strings
suffix:semicolon
r_int
id|nrela
comma
id|i
comma
id|j
suffix:semicolon
multiline_comment|/* Find symbol table and string table. */
id|symtab
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
id|hdr-&gt;e_shnum
suffix:semicolon
id|i
op_increment
)paren
r_switch
c_cond
(paren
id|sechdrs
(braket
id|i
)braket
dot
id|sh_type
)paren
(brace
r_case
id|SHT_SYMTAB
suffix:colon
id|symtab
op_assign
id|sechdrs
op_plus
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|symtab
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: no symbol table&bslash;n&quot;
comma
id|me-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
multiline_comment|/* Allocate one syminfo structure per symbol. */
id|me-&gt;arch.nsyms
op_assign
id|symtab-&gt;sh_size
op_div
r_sizeof
(paren
id|Elf_Sym
)paren
suffix:semicolon
id|me-&gt;arch.syminfo
op_assign
id|vmalloc
c_func
(paren
id|me-&gt;arch.nsyms
op_star
r_sizeof
(paren
r_struct
id|mod_arch_syminfo
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|me-&gt;arch.syminfo
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|symbols
op_assign
(paren
r_void
op_star
)paren
id|hdr
op_plus
id|symtab-&gt;sh_offset
suffix:semicolon
id|strings
op_assign
(paren
r_void
op_star
)paren
id|hdr
op_plus
id|sechdrs
(braket
id|symtab-&gt;sh_link
)braket
dot
id|sh_offset
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
id|me-&gt;arch.nsyms
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|symbols
(braket
id|i
)braket
dot
id|st_shndx
op_eq
id|SHN_UNDEF
op_logical_and
id|strcmp
c_func
(paren
id|strings
op_plus
id|symbols
(braket
id|i
)braket
dot
id|st_name
comma
l_string|&quot;_GLOBAL_OFFSET_TABLE_&quot;
)paren
op_eq
l_int|0
)paren
multiline_comment|/* &quot;Define&quot; it as absolute. */
id|symbols
(braket
id|i
)braket
dot
id|st_shndx
op_assign
id|SHN_ABS
suffix:semicolon
id|me-&gt;arch.syminfo
(braket
id|i
)braket
dot
id|got_offset
op_assign
op_minus
l_int|1UL
suffix:semicolon
id|me-&gt;arch.syminfo
(braket
id|i
)braket
dot
id|plt_offset
op_assign
op_minus
l_int|1UL
suffix:semicolon
id|me-&gt;arch.syminfo
(braket
id|i
)braket
dot
id|got_initialized
op_assign
l_int|0
suffix:semicolon
id|me-&gt;arch.syminfo
(braket
id|i
)braket
dot
id|plt_initialized
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Search for got/plt relocations. */
id|me-&gt;arch.got_size
op_assign
id|me-&gt;arch.plt_size
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
id|hdr-&gt;e_shnum
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sechdrs
(braket
id|i
)braket
dot
id|sh_type
op_ne
id|SHT_RELA
)paren
r_continue
suffix:semicolon
id|nrela
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
id|Elf_Rela
)paren
suffix:semicolon
id|rela
op_assign
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
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|nrela
suffix:semicolon
id|j
op_increment
)paren
id|check_rela
c_func
(paren
id|rela
op_plus
id|j
comma
id|me
)paren
suffix:semicolon
)brace
multiline_comment|/* Increase core size by size of got &amp; plt and set start&n;&t;   offsets for got and plt. */
id|me-&gt;core_size
op_assign
id|ALIGN
c_func
(paren
id|me-&gt;core_size
comma
l_int|4
)paren
suffix:semicolon
id|me-&gt;arch.got_offset
op_assign
id|me-&gt;core_size
suffix:semicolon
id|me-&gt;core_size
op_add_assign
id|me-&gt;arch.got_size
suffix:semicolon
id|me-&gt;arch.plt_offset
op_assign
id|me-&gt;core_size
suffix:semicolon
id|me-&gt;core_size
op_add_assign
id|me-&gt;arch.plt_size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|apply_relocate
id|apply_relocate
c_func
(paren
id|Elf_Shdr
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
id|me
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: RELOCATION unsupported&bslash;n&quot;
comma
id|me-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|apply_rela
id|apply_rela
c_func
(paren
id|Elf_Rela
op_star
id|rela
comma
id|Elf_Addr
id|base
comma
id|Elf_Sym
op_star
id|symtab
comma
r_struct
id|module
op_star
id|me
)paren
(brace
r_struct
id|mod_arch_syminfo
op_star
id|info
suffix:semicolon
id|Elf_Addr
id|loc
comma
id|val
suffix:semicolon
r_int
id|r_type
comma
id|r_sym
suffix:semicolon
multiline_comment|/* This is where to make the change */
id|loc
op_assign
id|base
op_plus
id|rela-&gt;r_offset
suffix:semicolon
multiline_comment|/* This is the symbol it is referring to.  Note that all&n;&t;   undefined symbols have been resolved.  */
id|r_sym
op_assign
id|ELF_R_SYM
c_func
(paren
id|rela-&gt;r_info
)paren
suffix:semicolon
id|r_type
op_assign
id|ELF_R_TYPE
c_func
(paren
id|rela-&gt;r_info
)paren
suffix:semicolon
id|info
op_assign
id|me-&gt;arch.syminfo
op_plus
id|r_sym
suffix:semicolon
id|val
op_assign
id|symtab
(braket
id|r_sym
)braket
dot
id|st_value
suffix:semicolon
r_switch
c_cond
(paren
id|r_type
)paren
(brace
r_case
id|R_390_8
suffix:colon
multiline_comment|/* Direct 8 bit.   */
r_case
id|R_390_12
suffix:colon
multiline_comment|/* Direct 12 bit.  */
r_case
id|R_390_16
suffix:colon
multiline_comment|/* Direct 16 bit.  */
r_case
id|R_390_20
suffix:colon
multiline_comment|/* Direct 20 bit.  */
r_case
id|R_390_32
suffix:colon
multiline_comment|/* Direct 32 bit.  */
r_case
id|R_390_64
suffix:colon
multiline_comment|/* Direct 64 bit.  */
id|val
op_add_assign
id|rela-&gt;r_addend
suffix:semicolon
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_8
)paren
op_star
(paren
r_int
r_char
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_12
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
(paren
id|val
op_amp
l_int|0xfff
)paren
op_or
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_amp
l_int|0xf000
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_16
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_20
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_amp
l_int|0xf00000ff
)paren
op_or
(paren
id|val
op_amp
l_int|0xfff
)paren
op_lshift
l_int|16
op_or
(paren
id|val
op_amp
l_int|0xff000
)paren
op_rshift
l_int|4
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_32
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_64
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_390_PC16
suffix:colon
multiline_comment|/* PC relative 16 bit.  */
r_case
id|R_390_PC16DBL
suffix:colon
multiline_comment|/* PC relative 16 bit shifted by 1.  */
r_case
id|R_390_PC32DBL
suffix:colon
multiline_comment|/* PC relative 32 bit shifted by 1.  */
r_case
id|R_390_PC32
suffix:colon
multiline_comment|/* PC relative 32 bit.  */
r_case
id|R_390_PC64
suffix:colon
multiline_comment|/* PC relative 64 bit.&t;*/
id|val
op_add_assign
id|rela-&gt;r_addend
op_minus
id|loc
suffix:semicolon
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_PC16
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_PC16DBL
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
op_rshift
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_PC32DBL
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
op_rshift
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_PC32
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_PC64
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_390_GOT12
suffix:colon
multiline_comment|/* 12 bit GOT offset.  */
r_case
id|R_390_GOT16
suffix:colon
multiline_comment|/* 16 bit GOT offset.  */
r_case
id|R_390_GOT20
suffix:colon
multiline_comment|/* 20 bit GOT offset.  */
r_case
id|R_390_GOT32
suffix:colon
multiline_comment|/* 32 bit GOT offset.  */
r_case
id|R_390_GOT64
suffix:colon
multiline_comment|/* 64 bit GOT offset.  */
r_case
id|R_390_GOTENT
suffix:colon
multiline_comment|/* 32 bit PC rel. to GOT entry shifted by 1. */
r_case
id|R_390_GOTPLT12
suffix:colon
multiline_comment|/* 12 bit offset to jump slot.&t;*/
r_case
id|R_390_GOTPLT20
suffix:colon
multiline_comment|/* 20 bit offset to jump slot.  */
r_case
id|R_390_GOTPLT16
suffix:colon
multiline_comment|/* 16 bit offset to jump slot.  */
r_case
id|R_390_GOTPLT32
suffix:colon
multiline_comment|/* 32 bit offset to jump slot.  */
r_case
id|R_390_GOTPLT64
suffix:colon
multiline_comment|/* 64 bit offset to jump slot.&t;*/
r_case
id|R_390_GOTPLTENT
suffix:colon
multiline_comment|/* 32 bit rel. offset to jump slot &gt;&gt; 1. */
r_if
c_cond
(paren
id|info-&gt;got_initialized
op_eq
l_int|0
)paren
(brace
id|Elf_Addr
op_star
id|gotent
suffix:semicolon
id|gotent
op_assign
id|me-&gt;module_core
op_plus
id|me-&gt;arch.got_offset
op_plus
id|info-&gt;got_offset
suffix:semicolon
op_star
id|gotent
op_assign
id|val
suffix:semicolon
id|info-&gt;got_initialized
op_assign
l_int|1
suffix:semicolon
)brace
id|val
op_assign
id|info-&gt;got_offset
op_plus
id|rela-&gt;r_addend
suffix:semicolon
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_GOT12
op_logical_or
id|r_type
op_eq
id|R_390_GOTPLT12
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
(paren
id|val
op_amp
l_int|0xfff
)paren
op_or
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_amp
l_int|0xf000
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_GOT16
op_logical_or
id|r_type
op_eq
id|R_390_GOTPLT16
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_GOT20
op_logical_or
id|r_type
op_eq
id|R_390_GOTPLT20
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_amp
l_int|0xf00000ff
)paren
op_or
(paren
id|val
op_amp
l_int|0xfff
)paren
op_lshift
l_int|16
op_or
(paren
id|val
op_amp
l_int|0xff000
)paren
op_rshift
l_int|4
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_GOT32
op_logical_or
id|r_type
op_eq
id|R_390_GOTPLT32
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_GOTENT
op_logical_or
id|r_type
op_eq
id|R_390_GOTPLTENT
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
(paren
id|val
op_plus
(paren
id|Elf_Addr
)paren
id|me-&gt;module_core
op_minus
id|loc
)paren
op_rshift
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_GOT64
op_logical_or
id|r_type
op_eq
id|R_390_GOTPLT64
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_390_PLT16DBL
suffix:colon
multiline_comment|/* 16 bit PC rel. PLT shifted by 1.  */
r_case
id|R_390_PLT32DBL
suffix:colon
multiline_comment|/* 32 bit PC rel. PLT shifted by 1.  */
r_case
id|R_390_PLT32
suffix:colon
multiline_comment|/* 32 bit PC relative PLT address.  */
r_case
id|R_390_PLT64
suffix:colon
multiline_comment|/* 64 bit PC relative PLT address.  */
r_case
id|R_390_PLTOFF16
suffix:colon
multiline_comment|/* 16 bit offset from GOT to PLT. */
r_case
id|R_390_PLTOFF32
suffix:colon
multiline_comment|/* 32 bit offset from GOT to PLT. */
r_case
id|R_390_PLTOFF64
suffix:colon
multiline_comment|/* 16 bit offset from GOT to PLT. */
r_if
c_cond
(paren
id|info-&gt;plt_initialized
op_eq
l_int|0
)paren
(brace
r_int
r_int
op_star
id|ip
suffix:semicolon
id|ip
op_assign
id|me-&gt;module_core
op_plus
id|me-&gt;arch.plt_offset
op_plus
id|info-&gt;plt_offset
suffix:semicolon
macro_line|#ifndef CONFIG_ARCH_S390X
id|ip
(braket
l_int|0
)braket
op_assign
l_int|0x0d105810
suffix:semicolon
multiline_comment|/* basr 1,0; l 1,6(1); br 1 */
id|ip
(braket
l_int|1
)braket
op_assign
l_int|0x100607f1
suffix:semicolon
id|ip
(braket
l_int|2
)braket
op_assign
id|val
suffix:semicolon
macro_line|#else /* CONFIG_ARCH_S390X */
id|ip
(braket
l_int|0
)braket
op_assign
l_int|0x0d10e310
suffix:semicolon
multiline_comment|/* basr 1,0; lg 1,10(1); br 1 */
id|ip
(braket
l_int|1
)braket
op_assign
l_int|0x100a0004
suffix:semicolon
id|ip
(braket
l_int|2
)braket
op_assign
l_int|0x07f10000
suffix:semicolon
id|ip
(braket
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
(paren
id|val
op_rshift
l_int|32
)paren
suffix:semicolon
id|ip
(braket
l_int|4
)braket
op_assign
(paren
r_int
r_int
)paren
id|val
suffix:semicolon
macro_line|#endif /* CONFIG_ARCH_S390X */
id|info-&gt;plt_initialized
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_PLTOFF16
op_logical_or
id|r_type
op_eq
id|R_390_PLTOFF32
op_logical_or
id|r_type
op_eq
id|R_390_PLTOFF64
)paren
id|val
op_assign
id|me-&gt;arch.plt_offset
op_minus
id|me-&gt;arch.got_offset
op_plus
id|info-&gt;plt_offset
op_plus
id|rela-&gt;r_addend
suffix:semicolon
r_else
id|val
op_assign
(paren
id|Elf_Addr
)paren
id|me-&gt;module_core
op_plus
id|me-&gt;arch.plt_offset
op_plus
id|info-&gt;plt_offset
op_plus
id|rela-&gt;r_addend
op_minus
id|loc
suffix:semicolon
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_PLT16DBL
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
op_rshift
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_PLTOFF16
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_PLT32DBL
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
op_rshift
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_PLT32
op_logical_or
id|r_type
op_eq
id|R_390_PLTOFF32
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_PLT64
op_logical_or
id|r_type
op_eq
id|R_390_PLTOFF64
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_390_GOTOFF16
suffix:colon
multiline_comment|/* 16 bit offset to GOT.  */
r_case
id|R_390_GOTOFF32
suffix:colon
multiline_comment|/* 32 bit offset to GOT.  */
r_case
id|R_390_GOTOFF64
suffix:colon
multiline_comment|/* 64 bit offset to GOT. */
id|val
op_assign
id|val
op_plus
id|rela-&gt;r_addend
op_minus
(paren
(paren
id|Elf_Addr
)paren
id|me-&gt;module_core
op_plus
id|me-&gt;arch.got_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_GOTOFF16
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_GOTOFF32
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_GOTOFF64
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_390_GOTPC
suffix:colon
multiline_comment|/* 32 bit PC relative offset to GOT. */
r_case
id|R_390_GOTPCDBL
suffix:colon
multiline_comment|/* 32 bit PC rel. off. to GOT shifted by 1. */
id|val
op_assign
(paren
id|Elf_Addr
)paren
id|me-&gt;module_core
op_plus
id|me-&gt;arch.got_offset
op_plus
id|rela-&gt;r_addend
op_minus
id|loc
suffix:semicolon
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_GOTPC
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r_type
op_eq
id|R_390_GOTPCDBL
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|loc
op_assign
id|val
op_rshift
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_390_COPY
suffix:colon
r_case
id|R_390_GLOB_DAT
suffix:colon
multiline_comment|/* Create GOT entry.  */
r_case
id|R_390_JMP_SLOT
suffix:colon
multiline_comment|/* Create PLT entry.  */
r_case
id|R_390_RELATIVE
suffix:colon
multiline_comment|/* Adjust by program base.  */
multiline_comment|/* Only needed if we want to support loading of &n;&t;&t;   modules linked with -shared. */
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: Unknown relocation: %u&bslash;n&quot;
comma
id|me-&gt;name
comma
id|r_type
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|apply_relocate_add
id|apply_relocate_add
c_func
(paren
id|Elf_Shdr
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
id|me
)paren
(brace
id|Elf_Addr
id|base
suffix:semicolon
id|Elf_Sym
op_star
id|symtab
suffix:semicolon
id|Elf_Rela
op_star
id|rela
suffix:semicolon
r_int
r_int
id|i
comma
id|n
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Applying relocate section %u to %u&bslash;n&quot;
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
id|base
op_assign
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
suffix:semicolon
id|symtab
op_assign
(paren
id|Elf_Sym
op_star
)paren
id|sechdrs
(braket
id|symindex
)braket
dot
id|sh_addr
suffix:semicolon
id|rela
op_assign
(paren
id|Elf_Rela
op_star
)paren
id|sechdrs
(braket
id|relsec
)braket
dot
id|sh_addr
suffix:semicolon
id|n
op_assign
id|sechdrs
(braket
id|relsec
)braket
dot
id|sh_size
op_div
r_sizeof
(paren
id|Elf_Rela
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
id|n
suffix:semicolon
id|i
op_increment
comma
id|rela
op_increment
)paren
(brace
id|rc
op_assign
id|apply_rela
c_func
(paren
id|rela
comma
id|base
comma
id|symtab
comma
id|me
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
id|rc
suffix:semicolon
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
id|vfree
c_func
(paren
id|me-&gt;arch.syminfo
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
)brace
eof
