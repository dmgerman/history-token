multiline_comment|/* Kernel module help for sparc32.&n; *&n; * Copyright (C) 2001 Rusty Russell.&n; * Copyright (C) 2002 David S. Miller.&n; */
macro_line|#include &lt;linux/moduleloader.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
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
id|vmalloc
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
id|vfree
c_func
(paren
id|module_region
)paren
suffix:semicolon
multiline_comment|/* FIXME: If module_region == mod-&gt;init_region, trim exception&n;           table entries. */
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
id|Elf32_Rela
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
id|Elf32_Sym
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
id|Elf32_Addr
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
id|sh_addr
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
(paren
id|v
op_assign
id|sym-&gt;st_value
)paren
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
op_add_assign
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
id|Elf32_Addr
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
id|Elf32_Addr
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
