multiline_comment|/*  Kernel module help for x86-64&n;    Copyright (C) 2001 Rusty Russell.&n;    Copyright (C) 2002,2003 Andi Kleen, SuSE Labs.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#include &lt;linux/moduleloader.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(fmt...) 
DECL|variable|mod_vmlist
r_static
r_struct
id|vm_struct
op_star
id|mod_vmlist
suffix:semicolon
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
r_struct
id|vm_struct
op_star
op_star
id|prevp
comma
op_star
id|map
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|module_region
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
r_return
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|prevp
op_assign
op_amp
id|mod_vmlist
suffix:semicolon
(paren
id|map
op_assign
op_star
id|prevp
)paren
suffix:semicolon
id|prevp
op_assign
op_amp
id|map-&gt;next
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|map-&gt;addr
op_eq
id|addr
)paren
(brace
op_star
id|prevp
op_assign
id|map-&gt;next
suffix:semicolon
r_goto
id|found
suffix:semicolon
)brace
)brace
id|write_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Trying to unmap nonexistent module vm area (%lx)&bslash;n&quot;
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
id|map
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;pages
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
id|map-&gt;nr_pages
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|map-&gt;pages
(braket
id|i
)braket
)paren
id|__free_page
c_func
(paren
id|map-&gt;pages
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|map-&gt;pages
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|map
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_return
l_int|NULL
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
id|size
OG
id|MODULES_LEN
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
id|memset
c_func
(paren
id|area
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|vm_struct
)paren
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|vmlist_lock
)paren
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
id|mod_vmlist
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
r_void
op_star
id|next
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;vmlist %p %lu addr %p&bslash;n&quot;
comma
id|tmp-&gt;addr
comma
id|tmp-&gt;size
comma
id|addr
)paren
suffix:semicolon
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
op_plus
id|PAGE_SIZE
OL
(paren
r_int
r_int
)paren
id|tmp-&gt;addr
)paren
r_break
suffix:semicolon
id|next
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
r_if
c_cond
(paren
id|next
OG
id|addr
)paren
id|addr
op_assign
id|next
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
(brace
id|write_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
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
id|DEBUGP
c_func
(paren
l_string|&quot;addr %p&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
id|area-&gt;next
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
id|area
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
id|write_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
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
id|nr_pages
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
id|area-&gt;pages
(braket
id|i
)braket
op_eq
l_int|NULL
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
id|PAGE_KERNEL_EXEC
comma
op_amp
id|pages
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|memset
c_func
(paren
id|addr
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;module_alloc size %lu = %p&bslash;n&quot;
comma
id|size
comma
id|addr
)paren
suffix:semicolon
r_return
id|addr
suffix:semicolon
id|fail
suffix:colon
id|module_free
c_func
(paren
l_int|NULL
comma
id|addr
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* We don&squot;t need anything special. */
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
r_void
op_star
id|loc
suffix:semicolon
id|u64
id|val
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
id|loc
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
id|rel
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
id|DEBUGP
c_func
(paren
l_string|&quot;type %d st_value %Lx r_addend %Lx loc %Lx&bslash;n&quot;
comma
(paren
r_int
)paren
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
comma
id|sym-&gt;st_value
comma
id|rel
(braket
id|i
)braket
dot
id|r_addend
comma
(paren
id|u64
)paren
id|loc
)paren
suffix:semicolon
id|val
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
)paren
(brace
r_case
id|R_X86_64_NONE
suffix:colon
r_break
suffix:semicolon
r_case
id|R_X86_64_64
suffix:colon
op_star
(paren
id|u64
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_X86_64_32
suffix:colon
op_star
(paren
id|u32
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
id|val
op_ne
op_star
(paren
id|u32
op_star
)paren
id|loc
)paren
r_goto
id|overflow
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_X86_64_32S
suffix:colon
op_star
(paren
id|s32
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
(paren
id|s64
)paren
id|val
op_ne
op_star
(paren
id|s32
op_star
)paren
id|loc
)paren
r_goto
id|overflow
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_X86_64_PC32
suffix:colon
id|val
op_sub_assign
(paren
id|u64
)paren
id|loc
suffix:semicolon
op_star
(paren
id|u32
op_star
)paren
id|loc
op_assign
id|val
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
(paren
id|s64
)paren
id|val
op_ne
op_star
(paren
id|s32
op_star
)paren
id|loc
)paren
r_goto
id|overflow
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;module %s: Unknown rela relocation: %Lu&bslash;n&quot;
comma
id|me-&gt;name
comma
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
id|overflow
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;overflow in relocation type %d val %Lx&bslash;n&quot;
comma
(paren
r_int
)paren
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
comma
id|val
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;`%s&squot; likely not compiled with -mcmodel=kernel&bslash;n&quot;
comma
id|me-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
DECL|function|apply_relocate
r_int
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
l_string|&quot;non add relocation not supported&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
r_extern
r_void
id|apply_alternatives
c_func
(paren
r_void
op_star
id|start
comma
r_void
op_star
id|end
)paren
suffix:semicolon
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
r_const
id|Elf_Shdr
op_star
id|s
suffix:semicolon
r_char
op_star
id|secstrings
op_assign
(paren
r_void
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
multiline_comment|/* look for .altinstructions to patch */
r_for
c_loop
(paren
id|s
op_assign
id|sechdrs
suffix:semicolon
id|s
OL
id|sechdrs
op_plus
id|hdr-&gt;e_shnum
suffix:semicolon
id|s
op_increment
)paren
(brace
r_void
op_star
id|seg
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
l_string|&quot;.altinstructions&quot;
comma
id|secstrings
op_plus
id|s-&gt;sh_name
)paren
)paren
r_continue
suffix:semicolon
id|seg
op_assign
(paren
r_void
op_star
)paren
id|s-&gt;sh_addr
suffix:semicolon
id|apply_alternatives
c_func
(paren
id|seg
comma
id|seg
op_plus
id|s-&gt;sh_size
)paren
suffix:semicolon
)brace
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
