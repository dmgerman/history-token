multiline_comment|/*  Kernel module help for parisc.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;&n;    (c) 2003 Randolph Chung &lt;tausq@debian.org&gt;&n;&n;    The best reference for this stuff is probably the Processor-&n;    Specific ELF Supplement for PA-RISC:&n;&t;http://ftp.parisc-linux.org/docs/elf-pa-hp.pdf&n;*/
macro_line|#include &lt;linux/moduleloader.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#if 1
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(fmt...)
macro_line|#endif
macro_line|#ifndef __LP64__
DECL|struct|got_entry
r_struct
id|got_entry
(brace
DECL|member|addr
id|Elf32_Addr
id|addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fdesc_entry
r_struct
id|fdesc_entry
(brace
DECL|member|gp
id|Elf32_Addr
id|gp
suffix:semicolon
DECL|member|addr
id|Elf32_Addr
id|addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|stub_entry
r_struct
id|stub_entry
(brace
DECL|member|insns
id|Elf32_Word
id|insns
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* each stub entry has two insns */
)brace
suffix:semicolon
macro_line|#else
DECL|struct|got_entry
r_struct
id|got_entry
(brace
DECL|member|addr
id|Elf64_Addr
id|addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fdesc_entry
r_struct
id|fdesc_entry
(brace
DECL|member|dummy
id|Elf64_Addr
id|dummy
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|gp
id|Elf64_Addr
id|gp
suffix:semicolon
DECL|member|addr
id|Elf64_Addr
id|addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|stub_entry
r_struct
id|stub_entry
(brace
DECL|member|insns
id|Elf64_Word
id|insns
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* each stub entry has four insns */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* Field selection types defined by hppa */
DECL|macro|rnd
mdefine_line|#define rnd(x)&t;&t;&t;(((x)+0x1000)&amp;~0x1fff)
multiline_comment|/* fsel: full 32 bits */
DECL|macro|fsel
mdefine_line|#define fsel(v,a)&t;&t;((v)+(a))
multiline_comment|/* lsel: select left 21 bits */
DECL|macro|lsel
mdefine_line|#define lsel(v,a)&t;&t;(((v)+(a))&gt;&gt;11)
multiline_comment|/* rsel: select right 11 bits */
DECL|macro|rsel
mdefine_line|#define rsel(v,a)&t;&t;(((v)+(a))&amp;0x7ff)
multiline_comment|/* lrsel with rounding of addend to nearest 8k */
DECL|macro|lrsel
mdefine_line|#define lrsel(v,a)&t;&t;(((v)+rnd(a))&gt;&gt;11)
multiline_comment|/* rrsel with rounding of addend to nearest 8k */
DECL|macro|rrsel
mdefine_line|#define rrsel(v,a)&t;&t;((((v)+rnd(a))&amp;0x7ff)+((a)-rnd(a)))
DECL|macro|mask
mdefine_line|#define mask(x,sz)&t;&t;((x) &amp; ~((1&lt;&lt;(sz))-1))
multiline_comment|/* The reassemble_* functions prepare an immediate value for&n;   insertion into an opcode. pa-risc uses all sorts of weird bitfields&n;   in the instruction to hold the value.  */
DECL|function|reassemble_14
r_static
r_inline
r_int
id|reassemble_14
c_func
(paren
r_int
id|as14
)paren
(brace
r_return
(paren
(paren
(paren
id|as14
op_amp
l_int|0x1fff
)paren
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|as14
op_amp
l_int|0x2000
)paren
op_rshift
l_int|13
)paren
)paren
suffix:semicolon
)brace
DECL|function|reassemble_17
r_static
r_inline
r_int
id|reassemble_17
c_func
(paren
r_int
id|as17
)paren
(brace
r_return
(paren
(paren
(paren
id|as17
op_amp
l_int|0x10000
)paren
op_rshift
l_int|16
)paren
op_or
(paren
(paren
id|as17
op_amp
l_int|0x0f800
)paren
op_lshift
l_int|5
)paren
op_or
(paren
(paren
id|as17
op_amp
l_int|0x00400
)paren
op_rshift
l_int|8
)paren
op_or
(paren
(paren
id|as17
op_amp
l_int|0x003ff
)paren
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
)brace
DECL|function|reassemble_21
r_static
r_inline
r_int
id|reassemble_21
c_func
(paren
r_int
id|as21
)paren
(brace
r_return
(paren
(paren
(paren
id|as21
op_amp
l_int|0x100000
)paren
op_rshift
l_int|20
)paren
op_or
(paren
(paren
id|as21
op_amp
l_int|0x0ffe00
)paren
op_rshift
l_int|8
)paren
op_or
(paren
(paren
id|as21
op_amp
l_int|0x000180
)paren
op_lshift
l_int|7
)paren
op_or
(paren
(paren
id|as21
op_amp
l_int|0x00007c
)paren
op_lshift
l_int|14
)paren
op_or
(paren
(paren
id|as21
op_amp
l_int|0x000003
)paren
op_lshift
l_int|12
)paren
)paren
suffix:semicolon
)brace
DECL|function|reassemble_22
r_static
r_inline
r_int
id|reassemble_22
c_func
(paren
r_int
id|as22
)paren
(brace
r_return
(paren
(paren
(paren
id|as22
op_amp
l_int|0x200000
)paren
op_rshift
l_int|21
)paren
op_or
(paren
(paren
id|as22
op_amp
l_int|0x1f0000
)paren
op_lshift
l_int|5
)paren
op_or
(paren
(paren
id|as22
op_amp
l_int|0x00f800
)paren
op_lshift
l_int|5
)paren
op_or
(paren
(paren
id|as22
op_amp
l_int|0x000400
)paren
op_rshift
l_int|8
)paren
op_or
(paren
(paren
id|as22
op_amp
l_int|0x0003ff
)paren
op_lshift
l_int|3
)paren
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
macro_line|#ifndef __LP64__
DECL|function|count_gots
r_static
r_inline
r_int
r_int
id|count_gots
c_func
(paren
r_const
id|Elf_Rela
op_star
id|rela
comma
r_int
r_int
id|n
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|count_fdescs
r_static
r_inline
r_int
r_int
id|count_fdescs
c_func
(paren
r_const
id|Elf_Rela
op_star
id|rela
comma
r_int
r_int
id|n
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|count_stubs
r_static
r_inline
r_int
r_int
id|count_stubs
c_func
(paren
r_const
id|Elf_Rela
op_star
id|rela
comma
r_int
r_int
id|n
)paren
(brace
r_int
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|n
OG
l_int|0
suffix:semicolon
id|n
op_decrement
comma
id|rela
op_increment
)paren
(brace
r_switch
c_cond
(paren
id|ELF32_R_TYPE
c_func
(paren
id|rela-&gt;r_info
)paren
)paren
(brace
r_case
id|R_PARISC_PCREL17F
suffix:colon
r_case
id|R_PARISC_PCREL22F
suffix:colon
id|cnt
op_increment
suffix:semicolon
)brace
)brace
r_return
id|cnt
suffix:semicolon
)brace
macro_line|#else
DECL|function|count_gots
r_static
r_inline
r_int
r_int
id|count_gots
c_func
(paren
r_const
id|Elf_Rela
op_star
id|rela
comma
r_int
r_int
id|n
)paren
(brace
r_int
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|n
OG
l_int|0
suffix:semicolon
id|n
op_decrement
comma
id|rela
op_increment
)paren
(brace
r_switch
c_cond
(paren
id|ELF64_R_TYPE
c_func
(paren
id|rela-&gt;r_info
)paren
)paren
(brace
r_case
id|R_PARISC_LTOFF21L
suffix:colon
r_case
id|R_PARISC_LTOFF14R
suffix:colon
r_case
id|R_PARISC_PCREL22F
suffix:colon
id|cnt
op_increment
suffix:semicolon
)brace
)brace
r_return
id|cnt
suffix:semicolon
)brace
DECL|function|count_fdescs
r_static
r_inline
r_int
r_int
id|count_fdescs
c_func
(paren
r_const
id|Elf_Rela
op_star
id|rela
comma
r_int
r_int
id|n
)paren
(brace
r_int
r_int
id|cnt
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* 3 for finalize */
r_for
c_loop
(paren
suffix:semicolon
id|n
OG
l_int|0
suffix:semicolon
id|n
op_decrement
comma
id|rela
op_increment
)paren
(brace
r_switch
c_cond
(paren
id|ELF64_R_TYPE
c_func
(paren
id|rela-&gt;r_info
)paren
)paren
(brace
r_case
id|R_PARISC_FPTR64
suffix:colon
id|cnt
op_increment
suffix:semicolon
)brace
)brace
r_return
id|cnt
suffix:semicolon
)brace
DECL|function|count_stubs
r_static
r_inline
r_int
r_int
id|count_stubs
c_func
(paren
r_const
id|Elf_Rela
op_star
id|rela
comma
r_int
r_int
id|n
)paren
(brace
r_int
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|n
OG
l_int|0
suffix:semicolon
id|n
op_decrement
comma
id|rela
op_increment
)paren
(brace
r_switch
c_cond
(paren
id|ELF64_R_TYPE
c_func
(paren
id|rela-&gt;r_info
)paren
)paren
(brace
r_case
id|R_PARISC_PCREL22F
suffix:colon
id|cnt
op_increment
suffix:semicolon
)brace
)brace
r_return
id|cnt
suffix:semicolon
)brace
macro_line|#endif
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
DECL|macro|CONST
mdefine_line|#define CONST 
DECL|function|module_frob_arch_sections
r_int
id|module_frob_arch_sections
c_func
(paren
id|CONST
id|Elf_Ehdr
op_star
id|hdr
comma
id|CONST
id|Elf_Shdr
op_star
id|sechdrs
comma
id|CONST
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
id|gots
op_assign
l_int|0
comma
id|fdescs
op_assign
l_int|0
comma
id|stubs
op_assign
l_int|0
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
r_const
id|Elf_Rela
op_star
id|rels
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
r_int
r_int
id|nrels
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
op_star
id|rels
)paren
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
op_ne
id|SHT_RELA
)paren
r_continue
suffix:semicolon
multiline_comment|/* some of these are not relevant for 32-bit/64-bit&n;&t;&t; * we leave them here to make the code common. the&n;&t;&t; * compiler will do its thing and optimize out the&n;&t;&t; * stuff we don&squot;t need&n;&t;&t; */
id|gots
op_add_assign
id|count_gots
c_func
(paren
id|rels
comma
id|nrels
)paren
suffix:semicolon
id|fdescs
op_add_assign
id|count_fdescs
c_func
(paren
id|rels
comma
id|nrels
)paren
suffix:semicolon
id|stubs
op_add_assign
id|count_stubs
c_func
(paren
id|rels
comma
id|nrels
)paren
suffix:semicolon
)brace
multiline_comment|/* align things a bit */
id|me-&gt;core_size
op_assign
id|ALIGN
c_func
(paren
id|me-&gt;core_size
comma
l_int|16
)paren
suffix:semicolon
id|me-&gt;arch.got_offset
op_assign
id|me-&gt;core_size
suffix:semicolon
id|me-&gt;core_size
op_add_assign
id|gots
op_star
r_sizeof
(paren
r_struct
id|got_entry
)paren
suffix:semicolon
id|me-&gt;core_size
op_assign
id|ALIGN
c_func
(paren
id|me-&gt;core_size
comma
l_int|16
)paren
suffix:semicolon
id|me-&gt;arch.fdesc_offset
op_assign
id|me-&gt;core_size
suffix:semicolon
id|me-&gt;core_size
op_add_assign
id|stubs
op_star
r_sizeof
(paren
r_struct
id|fdesc_entry
)paren
suffix:semicolon
id|me-&gt;core_size
op_assign
id|ALIGN
c_func
(paren
id|me-&gt;core_size
comma
l_int|16
)paren
suffix:semicolon
id|me-&gt;arch.stub_offset
op_assign
id|me-&gt;core_size
suffix:semicolon
id|me-&gt;core_size
op_add_assign
id|stubs
op_star
r_sizeof
(paren
r_struct
id|stub_entry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_got
r_static
id|Elf_Addr
id|get_got
c_func
(paren
r_struct
id|module
op_star
id|me
comma
r_int
r_int
id|value
comma
r_int
id|addend
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_struct
id|got_entry
op_star
id|got
suffix:semicolon
id|value
op_add_assign
id|addend
suffix:semicolon
id|BUG_ON
c_func
(paren
id|value
op_eq
l_int|0
)paren
suffix:semicolon
id|got
op_assign
id|me-&gt;module_core
op_plus
id|me-&gt;arch.got_offset
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|got
(braket
id|i
)braket
dot
id|addr
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|got
(braket
id|i
)braket
dot
id|addr
op_eq
id|value
)paren
r_return
id|i
op_star
r_sizeof
(paren
r_struct
id|got_entry
)paren
suffix:semicolon
id|got
(braket
id|i
)braket
dot
id|addr
op_assign
id|value
suffix:semicolon
r_return
id|i
op_star
r_sizeof
(paren
r_struct
id|got_entry
)paren
suffix:semicolon
)brace
DECL|function|get_fdesc
r_static
id|Elf_Addr
id|get_fdesc
c_func
(paren
r_struct
id|module
op_star
id|me
comma
r_int
r_int
id|value
)paren
(brace
r_struct
id|fdesc_entry
op_star
id|fdesc
op_assign
id|me-&gt;module_core
op_plus
id|me-&gt;arch.fdesc_offset
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
l_string|&quot;%s: zero OPD requested!&bslash;n&quot;
comma
id|me-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Look for existing fdesc entry. */
r_while
c_loop
(paren
id|fdesc-&gt;addr
)paren
(brace
r_if
c_cond
(paren
id|fdesc-&gt;addr
op_eq
id|value
)paren
r_return
(paren
id|Elf_Addr
)paren
id|fdesc
suffix:semicolon
id|fdesc
op_increment
suffix:semicolon
)brace
multiline_comment|/* Create new one */
id|fdesc-&gt;addr
op_assign
id|value
suffix:semicolon
id|fdesc-&gt;gp
op_assign
(paren
id|Elf_Addr
)paren
id|me-&gt;module_core
op_plus
id|me-&gt;arch.got_offset
suffix:semicolon
r_return
(paren
id|Elf_Addr
)paren
id|fdesc
suffix:semicolon
)brace
DECL|function|get_stub
r_static
id|Elf_Addr
id|get_stub
c_func
(paren
r_struct
id|module
op_star
id|me
comma
r_int
r_int
id|value
comma
r_int
id|addend
comma
r_int
id|millicode
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_struct
id|stub_entry
op_star
id|stub
suffix:semicolon
id|i
op_assign
id|me-&gt;arch.stub_count
op_increment
suffix:semicolon
id|stub
op_assign
id|me-&gt;module_core
op_plus
id|me-&gt;arch.stub_offset
op_plus
id|i
op_star
r_sizeof
(paren
r_struct
id|stub_entry
)paren
suffix:semicolon
macro_line|#ifndef __LP64__
multiline_comment|/* for 32-bit the stub looks like this:&n; * &t;ldil L&squot;XXX,%r1&n; * &t;be,n R&squot;XXX(%sr4,%r1)&n; */
id|stub-&gt;insns
(braket
l_int|0
)braket
op_assign
l_int|0x20200000
suffix:semicolon
multiline_comment|/* ldil L&squot;XXX,%r1&t;*/
id|stub-&gt;insns
(braket
l_int|1
)braket
op_assign
l_int|0xe0202002
suffix:semicolon
multiline_comment|/* be,n R&squot;XXX(%sr4,%r1)&t;*/
id|stub-&gt;insns
(braket
l_int|0
)braket
op_or_assign
id|reassemble_21
c_func
(paren
id|lrsel
c_func
(paren
id|value
comma
id|addend
)paren
)paren
suffix:semicolon
id|stub-&gt;insns
(braket
l_int|1
)braket
op_or_assign
id|reassemble_17
c_func
(paren
id|rrsel
c_func
(paren
id|value
comma
id|addend
)paren
op_div
l_int|4
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* for 64-bit we have two kinds of stubs:&n; * for normal function calls:&n; * &t;ldd 0(%dp),%dp&n; * &t;ldd 10(%dp), %r1&n; * &t;bve (%r1)&n; * &t;ldd 18(%dp), %dp&n; *&n; * for millicode:&n; * &t;ldil 0, %r1&n; * &t;ldo 0(%r1), %r1&n; * &t;ldd 10(%r1), %r1&n; * &t;bve,n (%r1)&n; */
r_if
c_cond
(paren
op_logical_neg
id|millicode
)paren
(brace
id|stub-&gt;insns
(braket
l_int|0
)braket
op_assign
l_int|0x537b0000
suffix:semicolon
multiline_comment|/* ldd 0(%dp),%dp&t;*/
id|stub-&gt;insns
(braket
l_int|1
)braket
op_assign
l_int|0x53610020
suffix:semicolon
multiline_comment|/* ldd 10(%dp),%r1&t;*/
id|stub-&gt;insns
(braket
l_int|2
)braket
op_assign
l_int|0xe820d000
suffix:semicolon
multiline_comment|/* bve (%r1)&t;&t;*/
id|stub-&gt;insns
(braket
l_int|3
)braket
op_assign
l_int|0x537b0030
suffix:semicolon
multiline_comment|/* ldd 18(%dp),%dp&t;*/
id|stub-&gt;insns
(braket
l_int|0
)braket
op_or_assign
id|reassemble_21
c_func
(paren
id|get_got
c_func
(paren
id|me
comma
id|value
comma
id|addend
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|stub-&gt;insns
(braket
l_int|0
)braket
op_assign
l_int|0x20200000
suffix:semicolon
multiline_comment|/* ldil 0,%r1&t;&t;*/
id|stub-&gt;insns
(braket
l_int|1
)braket
op_assign
l_int|0x34210000
suffix:semicolon
multiline_comment|/* ldo 0(%r1), %r1&t;*/
id|stub-&gt;insns
(braket
l_int|2
)braket
op_assign
l_int|0x50210020
suffix:semicolon
multiline_comment|/* ldd 10(%r1),%r1&t;*/
id|stub-&gt;insns
(braket
l_int|3
)braket
op_assign
l_int|0xe820d002
suffix:semicolon
multiline_comment|/* bve,n (%r1)&t;&t;*/
id|stub-&gt;insns
(braket
l_int|0
)braket
op_or_assign
id|reassemble_21
c_func
(paren
id|lrsel
c_func
(paren
id|value
comma
id|addend
)paren
)paren
suffix:semicolon
id|stub-&gt;insns
(braket
l_int|1
)braket
op_or_assign
id|reassemble_14
c_func
(paren
id|rrsel
c_func
(paren
id|value
comma
id|addend
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
(paren
id|Elf_Addr
)paren
id|stub
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
multiline_comment|/* parisc should not need this ... */
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
macro_line|#ifndef __LP64__
DECL|function|apply_relocate_add
r_int
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
id|Elf32_Word
op_star
id|loc
suffix:semicolon
id|Elf32_Addr
id|val
suffix:semicolon
id|Elf32_Sword
id|addend
suffix:semicolon
id|Elf32_Addr
id|dot
suffix:semicolon
r_register
r_int
r_int
id|dp
id|asm
(paren
l_string|&quot;r27&quot;
)paren
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
id|dot
op_assign
(paren
id|sechdrs
(braket
id|relsec
)braket
dot
id|sh_addr
op_plus
id|rel-&gt;r_offset
)paren
op_amp
op_complement
l_int|0x03
suffix:semicolon
id|val
op_assign
id|sym-&gt;st_value
suffix:semicolon
id|addend
op_assign
id|rel
(braket
id|i
)braket
dot
id|r_addend
suffix:semicolon
macro_line|#if 0
mdefine_line|#define r(t) ELF32_R_TYPE(rel[i].r_info)==t ? #t :
id|DEBUGP
c_func
(paren
l_string|&quot;Symbol %s loc 0x%x val 0x%x addend 0x%x: %s&bslash;n&quot;
comma
id|strtab
op_plus
id|sym-&gt;st_name
comma
(paren
r_uint32
)paren
id|loc
comma
id|val
comma
id|addend
comma
id|r
c_func
(paren
id|R_PARISC_PLABEL32
)paren
id|r
c_func
(paren
id|R_PARISC_DIR32
)paren
id|r
c_func
(paren
id|R_PARISC_DIR21L
)paren
id|r
c_func
(paren
id|R_PARISC_DIR14R
)paren
id|r
c_func
(paren
id|R_PARISC_SEGREL32
)paren
id|r
c_func
(paren
id|R_PARISC_DPREL21L
)paren
id|r
c_func
(paren
id|R_PARISC_DPREL14R
)paren
id|r
c_func
(paren
id|R_PARISC_PCREL17F
)paren
id|r
c_func
(paren
id|R_PARISC_PCREL22F
)paren
l_string|&quot;UNKNOWN&quot;
)paren
suffix:semicolon
macro_line|#undef r
macro_line|#endif
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
id|R_PARISC_PLABEL32
suffix:colon
multiline_comment|/* 32-bit function address */
multiline_comment|/* no function descriptors... */
op_star
id|loc
op_assign
id|fsel
c_func
(paren
id|val
comma
id|addend
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PARISC_DIR32
suffix:colon
multiline_comment|/* direct 32-bit ref */
op_star
id|loc
op_assign
id|fsel
c_func
(paren
id|val
comma
id|addend
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PARISC_DIR21L
suffix:colon
multiline_comment|/* left 21 bits of effective address */
op_star
id|loc
op_assign
id|mask
c_func
(paren
op_star
id|loc
comma
l_int|21
)paren
op_or
id|reassemble_21
c_func
(paren
id|lrsel
c_func
(paren
id|val
comma
id|addend
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PARISC_DIR14R
suffix:colon
multiline_comment|/* right 14 bits of effective address */
op_star
id|loc
op_assign
id|mask
c_func
(paren
op_star
id|loc
comma
l_int|14
)paren
op_or
id|reassemble_14
c_func
(paren
id|rrsel
c_func
(paren
id|val
comma
id|addend
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PARISC_SEGREL32
suffix:colon
multiline_comment|/* 32-bit segment relative address */
id|val
op_sub_assign
(paren
r_uint32
)paren
id|me-&gt;module_core
suffix:semicolon
op_star
id|loc
op_assign
id|fsel
c_func
(paren
id|val
comma
id|addend
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PARISC_DPREL21L
suffix:colon
multiline_comment|/* left 21 bit of relative address */
id|val
op_sub_assign
id|dp
suffix:semicolon
op_star
id|loc
op_assign
id|mask
c_func
(paren
op_star
id|loc
comma
l_int|21
)paren
op_or
id|reassemble_21
c_func
(paren
id|lrsel
c_func
(paren
id|val
comma
id|addend
)paren
op_minus
id|dp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PARISC_DPREL14R
suffix:colon
multiline_comment|/* right 14 bit of relative address */
id|val
op_sub_assign
id|dp
suffix:semicolon
op_star
id|loc
op_assign
id|mask
c_func
(paren
op_star
id|loc
comma
l_int|14
)paren
op_or
id|reassemble_14
c_func
(paren
id|rrsel
c_func
(paren
id|val
comma
id|addend
)paren
op_minus
id|dp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PARISC_PCREL17F
suffix:colon
multiline_comment|/* 17-bit PC relative address */
id|val
op_assign
id|get_stub
c_func
(paren
id|me
comma
id|val
comma
id|addend
comma
l_int|0
)paren
op_minus
id|dot
op_minus
l_int|8
suffix:semicolon
op_star
id|loc
op_assign
(paren
op_star
id|loc
op_amp
l_int|0x1f1ffd
)paren
op_or
id|reassemble_17
c_func
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PARISC_PCREL22F
suffix:colon
multiline_comment|/* 22-bit PC relative address; only defined for pa20 */
id|val
op_assign
id|get_stub
c_func
(paren
id|me
comma
id|val
comma
id|addend
comma
l_int|0
)paren
op_minus
id|dot
op_minus
l_int|8
suffix:semicolon
op_star
id|loc
op_assign
(paren
op_star
id|loc
op_amp
l_int|0x3ff1ffd
)paren
op_or
id|reassemble_22
c_func
(paren
id|val
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
macro_line|#else
DECL|function|apply_relocate_add
r_int
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
id|Elf64_Word
op_star
id|loc
suffix:semicolon
id|Elf64_Addr
id|val
suffix:semicolon
id|Elf64_Sxword
id|addend
suffix:semicolon
id|Elf64_Addr
id|dot
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
multiline_comment|/* This is the symbol it is referring to */
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
id|dot
op_assign
(paren
id|sechdrs
(braket
id|relsec
)braket
dot
id|sh_addr
op_plus
id|rel-&gt;r_offset
)paren
op_amp
op_complement
l_int|0x03
suffix:semicolon
id|val
op_assign
id|sym-&gt;st_value
suffix:semicolon
id|addend
op_assign
id|rel
(braket
id|i
)braket
dot
id|r_addend
suffix:semicolon
macro_line|#if 1
DECL|macro|r
mdefine_line|#define r(t) ELF64_R_TYPE(rel[i].r_info)==t ? #t :
id|DEBUGP
c_func
(paren
l_string|&quot;Symbol %s loc %p val 0x%Lx addend 0x%Lx: %s&bslash;n&quot;
comma
id|strtab
op_plus
id|sym-&gt;st_name
comma
id|loc
comma
id|val
comma
id|addend
comma
id|r
c_func
(paren
id|R_PARISC_LTOFF14R
)paren
id|r
c_func
(paren
id|R_PARISC_LTOFF21L
)paren
id|r
c_func
(paren
id|R_PARISC_PCREL22F
)paren
id|r
c_func
(paren
id|R_PARISC_DIR64
)paren
id|r
c_func
(paren
id|R_PARISC_SEGREL32
)paren
id|r
c_func
(paren
id|R_PARISC_FPTR64
)paren
l_string|&quot;UNKNOWN&quot;
)paren
suffix:semicolon
DECL|macro|r
macro_line|#undef r
macro_line|#endif
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
id|R_PARISC_LTOFF21L
suffix:colon
multiline_comment|/* LT-relative; left 21 bits */
op_star
id|loc
op_assign
id|mask
c_func
(paren
op_star
id|loc
comma
l_int|21
)paren
op_or
id|reassemble_21
c_func
(paren
id|get_got
c_func
(paren
id|me
comma
id|val
comma
id|addend
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PARISC_LTOFF14R
suffix:colon
multiline_comment|/* L(ltoff(val+addend)) */
multiline_comment|/* LT-relative; right 14 bits */
op_star
id|loc
op_assign
id|mask
c_func
(paren
op_star
id|loc
comma
l_int|14
)paren
op_or
id|reassemble_14
c_func
(paren
id|get_got
c_func
(paren
id|me
comma
id|val
comma
id|addend
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PARISC_PCREL22F
suffix:colon
multiline_comment|/* PC-relative; 22 bits */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|strtab
op_plus
id|sym-&gt;st_name
comma
l_string|&quot;$$&quot;
comma
l_int|2
)paren
op_eq
l_int|0
)paren
id|val
op_assign
id|get_stub
c_func
(paren
id|me
comma
id|val
comma
id|addend
comma
l_int|1
)paren
op_minus
id|dot
op_minus
l_int|8
suffix:semicolon
r_else
id|val
op_assign
id|get_stub
c_func
(paren
id|me
comma
id|val
comma
id|addend
comma
l_int|0
)paren
op_minus
id|dot
op_minus
l_int|8
suffix:semicolon
op_star
id|loc
op_assign
(paren
op_star
id|loc
op_amp
l_int|0x3ff1ffd
)paren
op_or
id|reassemble_22
c_func
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PARISC_DIR64
suffix:colon
multiline_comment|/* 64-bit effective address */
op_star
id|loc
op_assign
id|fsel
c_func
(paren
id|val
comma
id|addend
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PARISC_SEGREL32
suffix:colon
multiline_comment|/* 32-bit segment relative address */
id|val
op_sub_assign
(paren
r_uint64
)paren
id|me-&gt;module_core
suffix:semicolon
op_star
id|loc
op_assign
id|fsel
c_func
(paren
id|val
comma
id|addend
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PARISC_FPTR64
suffix:colon
multiline_comment|/* 64-bit function address */
op_star
id|loc
op_assign
id|get_fdesc
c_func
(paren
id|me
comma
id|val
op_plus
id|addend
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
l_string|&quot;module %s: Unknown relocation: %Lu&bslash;n&quot;
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
)brace
macro_line|#endif
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
macro_line|#ifdef __LP64__
id|me-&gt;init
op_assign
(paren
r_void
op_star
)paren
id|get_fdesc
c_func
(paren
id|me
comma
(paren
id|Elf_Addr
)paren
id|me-&gt;init
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MODULE_UNLOAD
r_if
c_cond
(paren
id|me-&gt;cleanup
)paren
id|me-&gt;cleanup
op_assign
(paren
r_void
op_star
)paren
id|get_fdesc
c_func
(paren
id|me
comma
(paren
id|Elf_Addr
)paren
id|me-&gt;cleanup
)paren
suffix:semicolon
r_if
c_cond
(paren
id|me-&gt;destroy
)paren
id|me-&gt;destroy
op_assign
(paren
r_void
op_star
)paren
id|get_fdesc
c_func
(paren
id|me
comma
(paren
id|Elf_Addr
)paren
id|me-&gt;destroy
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
