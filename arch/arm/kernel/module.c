multiline_comment|/*&n; *  linux/arch/arm/kernel/module.c&n; *&n; *  Copyright (C) 2002 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Module allocation method suggested by Andi Kleen.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
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
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
r_struct
id|page
op_star
op_star
id|pages
suffix:semicolon
r_int
r_int
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
)paren
r_goto
id|out_null
suffix:semicolon
id|area
op_assign
id|__get_vm_area
c_func
(paren
id|size
comma
id|VM_ALLOC
comma
id|MODULE_START
comma
id|MODULE_END
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area
)paren
r_goto
id|out_null
suffix:semicolon
id|area-&gt;nr_pages
op_assign
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|array_size
op_assign
id|area-&gt;nr_pages
op_star
r_sizeof
(paren
r_struct
id|page
op_star
)paren
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
(brace
id|remove_vm_area
c_func
(paren
id|area-&gt;addr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|area
)paren
suffix:semicolon
r_goto
id|out_null
suffix:semicolon
)brace
id|memset
c_func
(paren
id|pages
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
id|pages
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
id|pages
(braket
id|i
)braket
)paren
)paren
(brace
id|area-&gt;nr_pages
op_assign
id|i
suffix:semicolon
r_goto
id|out_no_pages
suffix:semicolon
)brace
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
r_goto
id|out_no_pages
suffix:semicolon
r_return
id|area-&gt;addr
suffix:semicolon
id|out_no_pages
suffix:colon
id|vfree
c_func
(paren
id|area-&gt;addr
)paren
suffix:semicolon
id|out_null
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|module_free
r_void
id|module_free
c_func
(paren
r_struct
id|module
op_star
id|module
comma
r_void
op_star
id|region
)paren
(brace
id|vfree
c_func
(paren
id|region
)paren
suffix:semicolon
)brace
r_int
DECL|function|module_core_size
id|module_core_size
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
r_struct
id|module
op_star
id|module
)paren
(brace
r_return
id|module-&gt;core_size
suffix:semicolon
)brace
r_int
DECL|function|module_init_size
id|module_init_size
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
r_struct
id|module
op_star
id|module
)paren
(brace
r_return
id|module-&gt;init_size
suffix:semicolon
)brace
r_int
DECL|function|apply_relocate
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
id|relindex
comma
r_struct
id|module
op_star
id|module
)paren
(brace
id|Elf32_Shdr
op_star
id|symsec
op_assign
id|sechdrs
op_plus
id|symindex
suffix:semicolon
id|Elf32_Shdr
op_star
id|relsec
op_assign
id|sechdrs
op_plus
id|relindex
suffix:semicolon
id|Elf32_Shdr
op_star
id|dstsec
op_assign
id|sechdrs
op_plus
id|relsec-&gt;sh_info
suffix:semicolon
id|Elf32_Rel
op_star
id|rel
op_assign
(paren
r_void
op_star
)paren
id|relsec-&gt;sh_offset
suffix:semicolon
r_int
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
id|relsec-&gt;sh_size
op_div
r_sizeof
(paren
id|Elf32_Rel
)paren
suffix:semicolon
id|i
op_increment
comma
id|rel
op_increment
)paren
(brace
r_int
r_int
id|loc
suffix:semicolon
id|Elf32_Sym
op_star
id|sym
suffix:semicolon
id|s32
id|offset
suffix:semicolon
id|offset
op_assign
id|ELF32_R_SYM
c_func
(paren
id|rel-&gt;r_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
template_param
(paren
id|symsec-&gt;sh_size
op_div
r_sizeof
(paren
id|Elf32_Sym
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: bad relocation, section %d reloc %d&bslash;n&quot;
comma
id|module-&gt;name
comma
id|relindex
comma
id|i
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
id|sym
op_assign
(paren
(paren
id|Elf32_Sym
op_star
)paren
id|symsec-&gt;sh_offset
)paren
op_plus
id|offset
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
l_string|&quot;%s: unknown symbol %s&bslash;n&quot;
comma
id|module-&gt;name
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
r_if
c_cond
(paren
id|rel-&gt;r_offset
template_param
id|dstsec-&gt;sh_size
op_minus
r_sizeof
(paren
id|u32
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: out of bounds relocation, &quot;
l_string|&quot;section %d reloc %d offset %d size %d&bslash;n&quot;
comma
id|module-&gt;name
comma
id|relindex
comma
id|i
comma
id|rel-&gt;r_offset
comma
id|dstsec-&gt;sh_size
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
id|loc
op_assign
id|dstsec-&gt;sh_offset
op_plus
id|rel-&gt;r_offset
suffix:semicolon
r_switch
c_cond
(paren
id|ELF32_R_TYPE
c_func
(paren
id|rel-&gt;r_info
)paren
)paren
(brace
r_case
id|R_ARM_ABS32
suffix:colon
op_star
(paren
id|u32
op_star
)paren
id|loc
op_add_assign
id|sym-&gt;st_value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_ARM_PC24
suffix:colon
id|offset
op_assign
(paren
op_star
(paren
id|u32
op_star
)paren
id|loc
op_amp
l_int|0x00ffffff
)paren
op_lshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_amp
l_int|0x02000000
)paren
id|offset
op_sub_assign
l_int|0x04000000
suffix:semicolon
id|offset
op_add_assign
id|sym-&gt;st_value
op_minus
id|loc
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_amp
l_int|3
op_logical_or
id|offset
op_le
(paren
id|s32
)paren
l_int|0xfc000000
op_logical_or
id|offset
op_ge
(paren
id|s32
)paren
l_int|0x04000000
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unable to fixup &quot;
l_string|&quot;relocation: out of range&bslash;n&quot;
comma
id|module-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
id|offset
op_rshift_assign
l_int|2
suffix:semicolon
op_star
(paren
id|u32
op_star
)paren
id|loc
op_and_assign
l_int|0xff000000
suffix:semicolon
op_star
(paren
id|u32
op_star
)paren
id|loc
op_or_assign
id|offset
op_amp
l_int|0x00ffffff
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: unknown relocation: %u&bslash;n&quot;
comma
id|module-&gt;name
comma
id|ELF32_R_TYPE
c_func
(paren
id|rel-&gt;r_info
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
r_int
DECL|function|apply_relocate_add
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
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: ADD RELOCATION unsupported&bslash;n&quot;
comma
id|module-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
r_int
DECL|function|module_finalize
id|module_finalize
c_func
(paren
r_const
id|Elf32_Ehdr
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
id|module
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
