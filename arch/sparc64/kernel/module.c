multiline_comment|/* Kernel module help for sparc64.&n; *&n; * Copyright (C) 2001 Rusty Russell.&n; * Copyright (C) 2002 David S. Miller.&n; */
macro_line|#include &lt;linux/moduleloader.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
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
r_static
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
DECL|function|module_map
r_static
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
r_void
op_star
id|ret
suffix:semicolon
multiline_comment|/* We handle the zero case fine, unlike vmalloc */
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
id|ret
op_assign
id|module_map
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|ret
op_assign
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
r_else
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Free memory returned from module_core_alloc/module_init_alloc */
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
id|module_unmap
c_func
(paren
id|module_region
)paren
suffix:semicolon
multiline_comment|/* FIXME: If module_region == mod-&gt;init_region, trim exception&n;           table entries. */
)brace
multiline_comment|/* Make generic code ignore STT_REGISTER dummy undefined symbols.  */
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
r_int
r_int
id|symidx
suffix:semicolon
id|Elf64_Sym
op_star
id|sym
suffix:semicolon
r_const
r_char
op_star
id|strtab
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|symidx
op_assign
l_int|0
suffix:semicolon
id|sechdrs
(braket
id|symidx
)braket
dot
id|sh_type
op_ne
id|SHT_SYMTAB
suffix:semicolon
id|symidx
op_increment
)paren
(brace
r_if
c_cond
(paren
id|symidx
op_eq
id|hdr-&gt;e_shnum
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: no symtab found.&bslash;n&quot;
comma
id|mod-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
)brace
id|sym
op_assign
(paren
id|Elf64_Sym
op_star
)paren
id|sechdrs
(braket
id|symidx
)braket
dot
id|sh_addr
suffix:semicolon
id|strtab
op_assign
(paren
r_char
op_star
)paren
id|sechdrs
(braket
id|sechdrs
(braket
id|symidx
)braket
dot
id|sh_link
)braket
dot
id|sh_addr
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
id|sechdrs
(braket
id|symidx
)braket
dot
id|sh_size
op_div
r_sizeof
(paren
id|Elf_Sym
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sym
(braket
id|i
)braket
dot
id|st_shndx
op_eq
id|SHN_UNDEF
op_logical_and
id|ELF64_ST_TYPE
c_func
(paren
id|sym
(braket
id|i
)braket
dot
id|st_info
)paren
op_eq
id|STT_REGISTER
)paren
id|sym
(braket
id|i
)braket
dot
id|st_shndx
op_assign
id|SHN_ABS
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|apply_relocate
r_int
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
l_string|&quot;module %s: non-ADD RELOCATION unsupported&bslash;n&quot;
comma
id|me-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
DECL|function|apply_relocate_add
r_int
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
r_int
r_int
id|i
suffix:semicolon
id|Elf64_Rela
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
id|sh_addr
suffix:semicolon
id|Elf64_Sym
op_star
id|sym
suffix:semicolon
id|u8
op_star
id|location
suffix:semicolon
id|u32
op_star
id|loc32
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
id|Elf64_Addr
id|v
suffix:semicolon
multiline_comment|/* This is where to make the change */
id|location
op_assign
(paren
id|u8
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
id|rel
(braket
id|i
)braket
dot
id|r_offset
suffix:semicolon
id|loc32
op_assign
(paren
id|u32
op_star
)paren
id|location
suffix:semicolon
id|BUG_ON
c_func
(paren
(paren
(paren
id|u64
)paren
id|location
op_rshift
(paren
id|u64
)paren
l_int|32
)paren
op_ne
(paren
id|u64
)paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* This is the symbol it is referring to.  Note that all&n;&t;&t;   undefined symbols have been resolved.  */
id|sym
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
op_plus
id|ELF64_R_SYM
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
id|v
op_assign
id|sym-&gt;st_value
op_plus
id|rel
(braket
id|i
)braket
dot
id|r_addend
suffix:semicolon
r_switch
c_cond
(paren
id|ELF64_R_TYPE
c_func
(paren
id|rel
(braket
id|i
)braket
dot
id|r_info
)paren
op_amp
l_int|0xff
)paren
(brace
r_case
id|R_SPARC_64
suffix:colon
id|location
(braket
l_int|0
)braket
op_assign
id|v
op_rshift
l_int|56
suffix:semicolon
id|location
(braket
l_int|1
)braket
op_assign
id|v
op_rshift
l_int|48
suffix:semicolon
id|location
(braket
l_int|2
)braket
op_assign
id|v
op_rshift
l_int|40
suffix:semicolon
id|location
(braket
l_int|3
)braket
op_assign
id|v
op_rshift
l_int|32
suffix:semicolon
id|location
(braket
l_int|4
)braket
op_assign
id|v
op_rshift
l_int|24
suffix:semicolon
id|location
(braket
l_int|5
)braket
op_assign
id|v
op_rshift
l_int|16
suffix:semicolon
id|location
(braket
l_int|6
)braket
op_assign
id|v
op_rshift
l_int|8
suffix:semicolon
id|location
(braket
l_int|7
)braket
op_assign
id|v
op_rshift
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_SPARC_32
suffix:colon
id|location
(braket
l_int|0
)braket
op_assign
id|v
op_rshift
l_int|24
suffix:semicolon
id|location
(braket
l_int|1
)braket
op_assign
id|v
op_rshift
l_int|16
suffix:semicolon
id|location
(braket
l_int|2
)braket
op_assign
id|v
op_rshift
l_int|8
suffix:semicolon
id|location
(braket
l_int|3
)braket
op_assign
id|v
op_rshift
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_SPARC_WDISP30
suffix:colon
id|v
op_sub_assign
(paren
id|Elf64_Addr
)paren
id|location
suffix:semicolon
op_star
id|loc32
op_assign
(paren
op_star
id|loc32
op_amp
op_complement
l_int|0x3fffffff
)paren
op_or
(paren
(paren
id|v
op_rshift
l_int|2
)paren
op_amp
l_int|0x3fffffff
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_SPARC_WDISP22
suffix:colon
id|v
op_sub_assign
(paren
id|Elf64_Addr
)paren
id|location
suffix:semicolon
op_star
id|loc32
op_assign
(paren
op_star
id|loc32
op_amp
op_complement
l_int|0x3fffff
)paren
op_or
(paren
(paren
id|v
op_rshift
l_int|2
)paren
op_amp
l_int|0x3fffff
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_SPARC_LO10
suffix:colon
op_star
id|loc32
op_assign
(paren
op_star
id|loc32
op_amp
op_complement
l_int|0x3ff
)paren
op_or
(paren
id|v
op_amp
l_int|0x3ff
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_SPARC_HI22
suffix:colon
op_star
id|loc32
op_assign
(paren
op_star
id|loc32
op_amp
op_complement
l_int|0x3fffff
)paren
op_or
(paren
(paren
id|v
op_rshift
l_int|10
)paren
op_amp
l_int|0x3fffff
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_SPARC_OLO10
suffix:colon
op_star
id|loc32
op_assign
(paren
op_star
id|loc32
op_amp
op_complement
l_int|0x1fff
)paren
op_or
(paren
(paren
(paren
id|v
op_amp
l_int|0x3ff
)paren
op_plus
(paren
id|ELF64_R_TYPE
c_func
(paren
id|rel
(braket
id|i
)braket
dot
id|r_info
)paren
op_rshift
l_int|8
)paren
)paren
op_amp
l_int|0x1fff
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: Unknown relocation: %x&bslash;n&quot;
comma
id|me-&gt;name
comma
(paren
r_int
)paren
(paren
id|ELF64_R_TYPE
c_func
(paren
id|rel
(braket
id|i
)braket
dot
id|r_info
)paren
op_amp
l_int|0xff
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
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
r_return
l_int|0
suffix:semicolon
)brace
eof
