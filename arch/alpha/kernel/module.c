multiline_comment|/*  Kernel module help for Alpha.&n;    Copyright (C) 2002 Richard Henderson.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#include &lt;linux/moduleloader.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(fmt...)
macro_line|#endif
r_void
op_star
DECL|function|module_alloc
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
r_void
DECL|function|module_free
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
)brace
multiline_comment|/* Allocate the GOT at the end of the core sections.  */
DECL|struct|got_entry
r_struct
id|got_entry
(brace
DECL|member|next
r_struct
id|got_entry
op_star
id|next
suffix:semicolon
DECL|member|r_offset
id|Elf64_Addr
id|r_offset
suffix:semicolon
DECL|member|got_offset
r_int
id|got_offset
suffix:semicolon
)brace
suffix:semicolon
r_static
r_inline
r_void
DECL|function|process_reloc_for_got
id|process_reloc_for_got
c_func
(paren
id|Elf64_Rela
op_star
id|rela
comma
r_struct
id|got_entry
op_star
id|chains
comma
id|Elf64_Xword
op_star
id|poffset
)paren
(brace
r_int
r_int
id|r_sym
op_assign
id|ELF64_R_SYM
(paren
id|rela-&gt;r_info
)paren
suffix:semicolon
r_int
r_int
id|r_type
op_assign
id|ELF64_R_TYPE
(paren
id|rela-&gt;r_info
)paren
suffix:semicolon
id|Elf64_Addr
id|r_offset
op_assign
id|rela-&gt;r_offset
suffix:semicolon
r_struct
id|got_entry
op_star
id|g
suffix:semicolon
r_if
c_cond
(paren
id|r_type
op_ne
id|R_ALPHA_LITERAL
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|g
op_assign
id|chains
op_plus
id|r_sym
suffix:semicolon
id|g
suffix:semicolon
id|g
op_assign
id|g-&gt;next
)paren
r_if
c_cond
(paren
id|g-&gt;r_offset
op_eq
id|r_offset
)paren
(brace
r_if
c_cond
(paren
id|g-&gt;got_offset
op_eq
l_int|0
)paren
(brace
id|g-&gt;got_offset
op_assign
op_star
id|poffset
suffix:semicolon
op_star
id|poffset
op_add_assign
l_int|8
suffix:semicolon
)brace
r_goto
id|found_entry
suffix:semicolon
)brace
id|g
op_assign
id|kmalloc
(paren
r_sizeof
(paren
op_star
id|g
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|g-&gt;next
op_assign
id|chains
(braket
id|r_sym
)braket
dot
id|next
suffix:semicolon
id|g-&gt;r_offset
op_assign
id|r_offset
suffix:semicolon
id|g-&gt;got_offset
op_assign
op_star
id|poffset
suffix:semicolon
op_star
id|poffset
op_add_assign
l_int|8
suffix:semicolon
id|chains
(braket
id|r_sym
)braket
dot
id|next
op_assign
id|g
suffix:semicolon
id|found_entry
suffix:colon
multiline_comment|/* Trick: most of the ELF64_R_TYPE field is unused.  There are&n;&t;   42 valid relocation types, and a 32-bit field.  Co-opt the&n;&t;   bits above 256 to store the got offset for this reloc.  */
id|rela-&gt;r_info
op_or_assign
id|g-&gt;got_offset
op_lshift
l_int|8
suffix:semicolon
)brace
r_int
DECL|function|module_frob_arch_sections
id|module_frob_arch_sections
c_func
(paren
id|Elf64_Ehdr
op_star
id|hdr
comma
id|Elf64_Shdr
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
r_struct
id|got_entry
op_star
id|chains
suffix:semicolon
id|Elf64_Rela
op_star
id|rela
suffix:semicolon
id|Elf64_Shdr
op_star
id|esechdrs
comma
op_star
id|symtab
comma
op_star
id|s
comma
op_star
id|got
suffix:semicolon
r_int
r_int
id|nsyms
comma
id|nrela
comma
id|i
suffix:semicolon
id|esechdrs
op_assign
id|sechdrs
op_plus
id|hdr-&gt;e_shnum
suffix:semicolon
id|symtab
op_assign
id|got
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Find out how large the symbol table is.  Allocate one got_entry&n;&t;   head per symbol.  Normally this will be enough, but not always.&n;&t;   We&squot;ll chain different offsets for the symbol down each head.  */
r_for
c_loop
(paren
id|s
op_assign
id|sechdrs
suffix:semicolon
id|s
OL
id|esechdrs
suffix:semicolon
op_increment
id|s
)paren
r_if
c_cond
(paren
id|s-&gt;sh_type
op_eq
id|SHT_SYMTAB
)paren
id|symtab
op_assign
id|s
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
l_string|&quot;.got&quot;
comma
id|secstrings
op_plus
id|s-&gt;sh_name
)paren
)paren
(brace
id|got
op_assign
id|s
suffix:semicolon
id|me-&gt;arch.gotsecindex
op_assign
id|s
op_minus
id|sechdrs
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
r_if
c_cond
(paren
op_logical_neg
id|got
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: no got section&bslash;n&quot;
comma
id|me-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
id|nsyms
op_assign
id|symtab-&gt;sh_size
op_div
r_sizeof
(paren
id|Elf64_Sym
)paren
suffix:semicolon
id|chains
op_assign
id|kmalloc
c_func
(paren
id|nsyms
op_star
r_sizeof
(paren
r_struct
id|got_entry
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|chains
comma
l_int|0
comma
id|nsyms
op_star
r_sizeof
(paren
r_struct
id|got_entry
)paren
)paren
suffix:semicolon
id|got-&gt;sh_size
op_assign
l_int|0
suffix:semicolon
id|got-&gt;sh_addralign
op_assign
l_int|8
suffix:semicolon
id|got-&gt;sh_type
op_assign
id|SHT_NOBITS
suffix:semicolon
multiline_comment|/* Examine all LITERAL relocations to find out what GOT entries&n;&t;   are required.  This sizes the GOT section as well.  */
r_for
c_loop
(paren
id|s
op_assign
id|sechdrs
suffix:semicolon
id|s
OL
id|esechdrs
suffix:semicolon
op_increment
id|s
)paren
r_if
c_cond
(paren
id|s-&gt;sh_type
op_eq
id|SHT_RELA
)paren
(brace
id|nrela
op_assign
id|s-&gt;sh_size
op_div
r_sizeof
(paren
id|Elf64_Rela
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
id|s-&gt;sh_offset
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
id|nrela
suffix:semicolon
op_increment
id|i
)paren
id|process_reloc_for_got
c_func
(paren
id|rela
op_plus
id|i
comma
id|chains
comma
op_amp
id|got-&gt;sh_size
)paren
suffix:semicolon
)brace
multiline_comment|/* Free the memory we allocated.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nsyms
suffix:semicolon
op_increment
id|i
)paren
(brace
r_struct
id|got_entry
op_star
id|g
comma
op_star
id|n
suffix:semicolon
r_for
c_loop
(paren
id|g
op_assign
id|chains
(braket
id|i
)braket
dot
id|next
suffix:semicolon
id|g
suffix:semicolon
id|g
op_assign
id|n
)paren
(brace
id|n
op_assign
id|g-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|g
)paren
suffix:semicolon
)brace
)brace
id|kfree
c_func
(paren
id|chains
)paren
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
id|Elf64_Shdr
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
l_string|&quot;module %s: REL relocation unsupported&bslash;n&quot;
comma
id|me-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
r_int
DECL|function|apply_relocate_add
id|apply_relocate_add
c_func
(paren
id|Elf64_Shdr
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
id|Elf64_Rela
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
r_int
r_int
id|i
comma
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
op_star
id|rela
)paren
suffix:semicolon
id|Elf64_Sym
op_star
id|symtab
comma
op_star
id|sym
suffix:semicolon
r_void
op_star
id|base
comma
op_star
id|location
suffix:semicolon
r_int
r_int
id|got
comma
id|gp
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
suffix:semicolon
id|symtab
op_assign
(paren
id|Elf64_Sym
op_star
)paren
id|sechdrs
(braket
id|symindex
)braket
dot
id|sh_addr
suffix:semicolon
multiline_comment|/* The small sections were sorted to the end of the segment.&n;&t;   The following should definitely cover them.  */
id|gp
op_assign
(paren
id|u64
)paren
id|me-&gt;module_core
op_plus
id|me-&gt;core_size
op_minus
l_int|0x8000
suffix:semicolon
id|got
op_assign
id|sechdrs
(braket
id|me-&gt;arch.gotsecindex
)braket
dot
id|sh_addr
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
)paren
(brace
r_int
r_int
id|r_sym
op_assign
id|ELF64_R_SYM
(paren
id|rela
(braket
id|i
)braket
dot
id|r_info
)paren
suffix:semicolon
r_int
r_int
id|r_type
op_assign
id|ELF64_R_TYPE
(paren
id|rela
(braket
id|i
)braket
dot
id|r_info
)paren
suffix:semicolon
r_int
r_int
id|r_got_offset
op_assign
id|r_type
op_rshift
l_int|8
suffix:semicolon
r_int
r_int
id|value
comma
id|hi
comma
id|lo
suffix:semicolon
id|r_type
op_and_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* This is where to make the change.  */
id|location
op_assign
id|base
op_plus
id|rela
(braket
id|i
)braket
dot
id|r_offset
suffix:semicolon
multiline_comment|/* This is the symbol it is referring to.  */
id|sym
op_assign
id|symtab
op_plus
id|r_sym
suffix:semicolon
id|value
op_assign
id|sym-&gt;st_value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: Unknown symbol %s&bslash;n&quot;
comma
id|me-&gt;name
comma
id|strtab
op_plus
id|sym-&gt;st_name
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|value
op_add_assign
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
id|r_type
)paren
(brace
r_case
id|R_ALPHA_NONE
suffix:colon
r_break
suffix:semicolon
r_case
id|R_ALPHA_REFQUAD
suffix:colon
op_star
(paren
id|u64
op_star
)paren
id|location
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_ALPHA_GPREL32
suffix:colon
id|value
op_sub_assign
id|gp
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|value
op_ne
id|value
)paren
r_goto
id|reloc_overflow
suffix:semicolon
op_star
(paren
id|u32
op_star
)paren
id|location
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_ALPHA_LITERAL
suffix:colon
id|hi
op_assign
id|got
op_plus
id|r_got_offset
suffix:semicolon
id|lo
op_assign
id|hi
op_minus
id|gp
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|lo
op_ne
id|lo
)paren
r_goto
id|reloc_overflow
suffix:semicolon
op_star
(paren
id|u16
op_star
)paren
id|location
op_assign
id|lo
suffix:semicolon
op_star
(paren
id|u64
op_star
)paren
id|hi
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_ALPHA_LITUSE
suffix:colon
r_break
suffix:semicolon
r_case
id|R_ALPHA_GPDISP
suffix:colon
id|value
op_assign
id|gp
op_minus
(paren
id|u64
)paren
id|location
suffix:semicolon
id|lo
op_assign
(paren
r_int
)paren
id|value
suffix:semicolon
id|hi
op_assign
(paren
r_int
)paren
(paren
id|value
op_minus
id|lo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hi
op_plus
id|lo
op_ne
id|value
)paren
r_goto
id|reloc_overflow
suffix:semicolon
op_star
(paren
id|u16
op_star
)paren
id|location
op_assign
id|hi
op_rshift
l_int|16
suffix:semicolon
op_star
(paren
id|u16
op_star
)paren
(paren
id|location
op_plus
id|rela
(braket
id|i
)braket
dot
id|r_addend
)paren
op_assign
id|lo
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_ALPHA_BRSGP
suffix:colon
multiline_comment|/* BRSGP is only allowed to bind to local symbols.&n;&t;&t;&t;   If the section is undef, this means that the&n;&t;&t;&t;   value was resolved from somewhere else.  */
r_if
c_cond
(paren
id|sym-&gt;st_shndx
op_eq
id|SHN_UNDEF
)paren
r_goto
id|reloc_overflow
suffix:semicolon
multiline_comment|/* FALLTHRU */
r_case
id|R_ALPHA_BRADDR
suffix:colon
id|value
op_sub_assign
(paren
id|u64
)paren
id|location
op_plus
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|3
)paren
r_goto
id|reloc_overflow
suffix:semicolon
id|value
op_assign
(paren
r_int
)paren
id|value
op_rshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|value
op_plus
(paren
l_int|1
op_lshift
l_int|21
)paren
op_ge
l_int|1
op_lshift
l_int|22
)paren
r_goto
id|reloc_overflow
suffix:semicolon
id|value
op_and_assign
l_int|0x1fffff
suffix:semicolon
id|value
op_or_assign
op_star
(paren
id|u32
op_star
)paren
id|location
op_amp
op_complement
l_int|0x1fffff
suffix:semicolon
op_star
(paren
id|u32
op_star
)paren
id|location
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_ALPHA_HINT
suffix:colon
r_break
suffix:semicolon
r_case
id|R_ALPHA_SREL32
suffix:colon
id|value
op_sub_assign
(paren
id|u64
)paren
id|location
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|value
op_ne
id|value
)paren
r_goto
id|reloc_overflow
suffix:semicolon
op_star
(paren
id|u32
op_star
)paren
id|location
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_ALPHA_SREL64
suffix:colon
id|value
op_sub_assign
(paren
id|u64
)paren
id|location
suffix:semicolon
op_star
(paren
id|u64
op_star
)paren
id|location
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_ALPHA_GPRELHIGH
suffix:colon
id|value
op_assign
(paren
id|value
op_minus
id|gp
op_plus
l_int|0x8000
)paren
op_rshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|value
op_ne
id|value
)paren
r_goto
id|reloc_overflow
suffix:semicolon
op_star
(paren
id|u16
op_star
)paren
id|location
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_ALPHA_GPRELLOW
suffix:colon
id|value
op_sub_assign
id|gp
suffix:semicolon
op_star
(paren
id|u16
op_star
)paren
id|location
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_ALPHA_GPREL16
suffix:colon
id|value
op_sub_assign
id|gp
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|value
op_ne
id|value
)paren
r_goto
id|reloc_overflow
suffix:semicolon
op_star
(paren
id|u16
op_star
)paren
id|location
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: Unknown relocation: %lu&bslash;n&quot;
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
id|reloc_overflow
suffix:colon
r_if
c_cond
(paren
id|ELF64_ST_TYPE
(paren
id|sym-&gt;st_info
)paren
op_eq
id|STT_SECTION
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: Relocation overflow vs section %d&bslash;n&quot;
comma
id|me-&gt;name
comma
id|sym-&gt;st_shndx
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: Relocation overflow vs %s&bslash;n&quot;
comma
id|me-&gt;name
comma
id|strtab
op_plus
id|sym-&gt;st_name
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
r_int
DECL|function|module_finalize
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
r_return
l_int|0
suffix:semicolon
)brace
eof
