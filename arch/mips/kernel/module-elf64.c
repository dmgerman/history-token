multiline_comment|/*  Kernel module help for MIPS.&n;    Copyright (C) 2001 Rusty Russell.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#include &lt;linux/moduleloader.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
DECL|struct|mips_hi16
r_struct
id|mips_hi16
(brace
DECL|member|next
r_struct
id|mips_hi16
op_star
id|next
suffix:semicolon
DECL|member|addr
id|Elf32_Addr
op_star
id|addr
suffix:semicolon
DECL|member|value
id|Elf32_Addr
id|value
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|mips_hi16_list
r_static
r_struct
id|mips_hi16
op_star
id|mips_hi16_list
suffix:semicolon
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(fmt , ...)
macro_line|#endif
DECL|variable|modvmlist
r_static
r_struct
id|vm_struct
op_star
id|modvmlist
op_assign
l_int|NULL
suffix:semicolon
DECL|function|module_unmap
r_void
id|module_unmap
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_struct
id|vm_struct
op_star
op_star
id|p
comma
op_star
id|tmp
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
(paren
r_int
r_int
)paren
id|addr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to unmap module with bad address (%p)&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|modvmlist
suffix:semicolon
(paren
id|tmp
op_assign
op_star
id|p
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|tmp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|tmp-&gt;addr
op_eq
id|addr
)paren
(brace
op_star
id|p
op_assign
id|tmp-&gt;next
suffix:semicolon
r_goto
id|found
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;Trying to unmap nonexistent module vm area (%p)&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_return
suffix:semicolon
id|found
suffix:colon
id|unmap_vm_area
c_func
(paren
id|tmp
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
id|tmp-&gt;nr_pages
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|tmp-&gt;pages
(braket
id|i
)braket
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|tmp-&gt;pages
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|tmp-&gt;pages
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
DECL|macro|MODULES_LEN
mdefine_line|#define MODULES_LEN&t;(512*1024*1024)&t;&t;/* Random silly large number */
DECL|macro|MODULES_END
mdefine_line|#define MODULES_END&t;(512*1024*1024)&t;&t;/* Random silly large number */
DECL|macro|MODULES_VADDR
mdefine_line|#define MODULES_VADDR&t;(512*1024*1024)&t;&t;/* Random silly large number */
DECL|function|module_map
r_void
op_star
id|module_map
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_struct
id|vm_struct
op_star
op_star
id|p
comma
op_star
id|tmp
comma
op_star
id|area
suffix:semicolon
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
r_void
op_star
id|addr
suffix:semicolon
r_int
r_int
id|nr_pages
comma
id|array_size
comma
id|i
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_or
id|size
OG
id|MODULES_LEN
)paren
r_return
l_int|NULL
suffix:semicolon
id|addr
op_assign
(paren
r_void
op_star
)paren
id|MODULES_VADDR
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|modvmlist
suffix:semicolon
(paren
id|tmp
op_assign
op_star
id|p
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|tmp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|size
op_plus
(paren
r_int
r_int
)paren
id|addr
OL
(paren
r_int
r_int
)paren
id|tmp-&gt;addr
)paren
r_break
suffix:semicolon
id|addr
op_assign
(paren
r_void
op_star
)paren
(paren
id|tmp-&gt;size
op_plus
(paren
r_int
r_int
)paren
id|tmp-&gt;addr
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|addr
op_plus
id|size
op_ge
id|MODULES_END
)paren
r_return
l_int|NULL
suffix:semicolon
id|area
op_assign
(paren
r_struct
id|vm_struct
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|area
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area
)paren
r_return
l_int|NULL
suffix:semicolon
id|area-&gt;size
op_assign
id|size
op_plus
id|PAGE_SIZE
suffix:semicolon
id|area-&gt;addr
op_assign
id|addr
suffix:semicolon
id|area-&gt;next
op_assign
op_star
id|p
suffix:semicolon
id|area-&gt;pages
op_assign
l_int|NULL
suffix:semicolon
id|area-&gt;nr_pages
op_assign
l_int|0
suffix:semicolon
id|area-&gt;phys_addr
op_assign
l_int|0
suffix:semicolon
op_star
id|p
op_assign
id|area
suffix:semicolon
id|nr_pages
op_assign
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|array_size
op_assign
(paren
id|nr_pages
op_star
r_sizeof
(paren
r_struct
id|page
op_star
)paren
)paren
suffix:semicolon
id|area-&gt;nr_pages
op_assign
id|nr_pages
suffix:semicolon
id|area-&gt;pages
op_assign
id|pages
op_assign
id|kmalloc
c_func
(paren
id|array_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area-&gt;pages
)paren
r_goto
id|fail
suffix:semicolon
id|memset
c_func
(paren
id|area-&gt;pages
comma
l_int|0
comma
id|array_size
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
id|area-&gt;nr_pages
suffix:semicolon
id|i
op_increment
)paren
(brace
id|area-&gt;pages
(braket
id|i
)braket
op_assign
id|alloc_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|area-&gt;pages
(braket
id|i
)braket
)paren
)paren
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|map_vm_area
c_func
(paren
id|area
comma
id|PAGE_KERNEL
comma
op_amp
id|pages
)paren
)paren
(brace
id|unmap_vm_area
c_func
(paren
id|area
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
r_return
id|area-&gt;addr
suffix:semicolon
id|fail
suffix:colon
r_if
c_cond
(paren
id|area-&gt;pages
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|area-&gt;nr_pages
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|area-&gt;pages
(braket
id|i
)braket
)paren
id|__free_page
c_func
(paren
id|area-&gt;pages
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|area-&gt;pages
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|area
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
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
DECL|function|module_frob_arch_sections
r_int
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
id|mod
)paren
(brace
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
id|me
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
id|Elf32_Rel
op_star
id|rel
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
id|sh_offset
suffix:semicolon
id|Elf32_Sym
op_star
id|sym
suffix:semicolon
r_uint32
op_star
id|location
suffix:semicolon
id|Elf32_Addr
id|v
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
id|rel
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
id|sh_offset
op_plus
id|rel
(braket
id|i
)braket
dot
id|r_offset
suffix:semicolon
multiline_comment|/* This is the symbol it is referring to */
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
id|sh_offset
op_plus
id|ELF32_R_SYM
c_func
(paren
id|rel
(braket
id|i
)braket
dot
id|r_info
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sym-&gt;st_value
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Unknown symbol %s&bslash;n&quot;
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
id|v
op_assign
id|sym-&gt;st_value
suffix:semicolon
r_switch
c_cond
(paren
id|ELF32_R_TYPE
c_func
(paren
id|rel
(braket
id|i
)braket
dot
id|r_info
)paren
)paren
(brace
r_case
id|R_MIPS_NONE
suffix:colon
r_break
suffix:semicolon
r_case
id|R_MIPS_32
suffix:colon
op_star
id|location
op_add_assign
id|v
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_MIPS_26
suffix:colon
r_if
c_cond
(paren
id|v
op_mod
l_int|4
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: dangerous relocation&bslash;n&quot;
comma
id|me-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
r_if
c_cond
(paren
(paren
id|v
op_amp
l_int|0xf0000000
)paren
op_ne
(paren
(paren
(paren
r_int
r_int
)paren
id|location
op_plus
l_int|4
)paren
op_amp
l_int|0xf0000000
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: relocation overflow&bslash;n&quot;
comma
id|me-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
op_star
id|location
op_assign
(paren
op_star
id|location
op_amp
op_complement
l_int|0x03ffffff
)paren
op_or
(paren
(paren
op_star
id|location
op_plus
(paren
id|v
op_rshift
l_int|2
)paren
)paren
op_amp
l_int|0x03ffffff
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_MIPS_HI16
suffix:colon
(brace
r_struct
id|mips_hi16
op_star
id|n
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * We cannot relocate this one now because we don&squot;t&n;&t;&t;&t; * know the value of the carry we need to add.  Save&n;&t;&t;&t; * the information, and let LO16 do the actual&n;&t;&t;&t; * relocation.&n;&t;&t;&t; */
id|n
op_assign
(paren
r_struct
id|mips_hi16
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|n
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|n-&gt;addr
op_assign
id|location
suffix:semicolon
id|n-&gt;value
op_assign
id|v
suffix:semicolon
id|n-&gt;next
op_assign
id|mips_hi16_list
suffix:semicolon
id|mips_hi16_list
op_assign
id|n
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|R_MIPS_LO16
suffix:colon
(brace
r_int
r_int
id|insnlo
op_assign
op_star
id|location
suffix:semicolon
id|Elf32_Addr
id|val
comma
id|vallo
suffix:semicolon
multiline_comment|/* Sign extend the addend we extract from the lo insn.  */
id|vallo
op_assign
(paren
(paren
id|insnlo
op_amp
l_int|0xffff
)paren
op_xor
l_int|0x8000
)paren
op_minus
l_int|0x8000
suffix:semicolon
r_if
c_cond
(paren
id|mips_hi16_list
op_ne
l_int|NULL
)paren
(brace
r_struct
id|mips_hi16
op_star
id|l
suffix:semicolon
id|l
op_assign
id|mips_hi16_list
suffix:semicolon
r_while
c_loop
(paren
id|l
op_ne
l_int|NULL
)paren
(brace
r_struct
id|mips_hi16
op_star
id|next
suffix:semicolon
r_int
r_int
id|insn
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t; * The value for the HI16 had best be&n;&t;&t;&t;&t;&t; * the same.&n;&t;&t;&t;&t;&t; */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: dangerous &quot;
l_string|&quot;relocation&bslash;n&quot;
comma
id|me-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Do the HI16 relocation.  Note that&n;&t;&t;&t;&t;&t; * we actually don&squot;t need to know&n;&t;&t;&t;&t;&t; * anything about the LO16 itself,&n;&t;&t;&t;&t;&t; * except where to find the low 16 bits&n;&t;&t;&t;&t;&t; * of the addend needed by the LO16.&n;&t;&t;&t;&t;&t; */
id|insn
op_assign
op_star
id|l-&gt;addr
suffix:semicolon
id|val
op_assign
(paren
(paren
id|insn
op_amp
l_int|0xffff
)paren
op_lshift
l_int|16
)paren
op_plus
id|vallo
suffix:semicolon
id|val
op_add_assign
id|v
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Account for the sign extension that&n;&t;&t;&t;&t;&t; * will happen in the low bits.&n;&t;&t;&t;&t;&t; */
id|val
op_assign
(paren
(paren
id|val
op_rshift
l_int|16
)paren
op_plus
(paren
(paren
id|val
op_amp
l_int|0x8000
)paren
op_ne
l_int|0
)paren
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|insn
op_assign
(paren
id|insn
op_amp
op_complement
l_int|0xffff
)paren
op_or
id|val
suffix:semicolon
op_star
id|l-&gt;addr
op_assign
id|insn
suffix:semicolon
id|next
op_assign
id|l-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|l
)paren
suffix:semicolon
id|l
op_assign
id|next
suffix:semicolon
)brace
id|mips_hi16_list
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Ok, we&squot;re done with the HI16 relocs.  Now deal with&n;&t;&t;&t; * the LO16.&n;&t;&t;&t; */
id|val
op_assign
id|v
op_plus
id|vallo
suffix:semicolon
id|insnlo
op_assign
(paren
id|insnlo
op_amp
op_complement
l_int|0xffff
)paren
op_or
(paren
id|val
op_amp
l_int|0xffff
)paren
suffix:semicolon
op_star
id|location
op_assign
id|insnlo
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|ELF32_R_TYPE
c_func
(paren
id|rel
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
id|me
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: ADD RELOCATION unsupported&bslash;n&quot;
comma
id|me-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
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
