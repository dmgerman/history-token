multiline_comment|/*  Kernel module help for PPC64.&n;    Copyright (C) 2001, 2003 Rusty Russell IBM Corporation.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/moduleloader.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
multiline_comment|/* FIXME: We don&squot;t do .init separately.  To do this, we&squot;d need to have&n;   a separate r2 value in the init and core section, and stub between&n;   them, too.&n;&n;   Using a magic allocator which places modules within 32MB solves&n;   this, and makes other things simpler.  Anton?&n;   --RR.  */
macro_line|#if 0
mdefine_line|#define DEBUGP printk
macro_line|#else
DECL|macro|DEBUGP
mdefine_line|#define DEBUGP(fmt , ...)
macro_line|#endif
multiline_comment|/* There&squot;s actually a third entry here, but it&squot;s unused */
DECL|struct|ppc64_opd_entry
r_struct
id|ppc64_opd_entry
(brace
DECL|member|funcaddr
r_int
r_int
id|funcaddr
suffix:semicolon
DECL|member|r2
r_int
r_int
id|r2
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Like PPC32, we need little trampolines to do &gt; 24-bit jumps (into&n;   the kernel itself).  But on PPC64, these need to be used for every&n;   jump, actually, to reset r2 (TOC+0x8000). */
DECL|struct|ppc64_stub_entry
r_struct
id|ppc64_stub_entry
(brace
multiline_comment|/* 28 byte jump instruction sequence (7 instructions) */
DECL|member|jump
r_int
r_char
id|jump
(braket
l_int|28
)braket
suffix:semicolon
DECL|member|unused
r_int
r_char
id|unused
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Data for the above code */
DECL|member|opd
r_struct
id|ppc64_opd_entry
id|opd
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* We use a stub to fix up r2 (TOC ptr) and to jump to the (external)&n;   function which may be more than 24-bits away.  We could simply&n;   patch the new r2 value and function pointer into the stub, but it&squot;s&n;   significantly shorter to put these values at the end of the stub&n;   code, and patch the stub address (32-bits relative to the TOC ptr,&n;   r2) into the stub. */
DECL|variable|ppc64_stub
r_static
r_struct
id|ppc64_stub_entry
id|ppc64_stub
op_assign
(brace
dot
id|jump
op_assign
(brace
l_int|0x3d
comma
l_int|0x82
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* addis   r12,r2, &lt;high&gt; */
l_int|0x39
comma
l_int|0x8c
comma
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* addi    r12,r12, &lt;low&gt; */
multiline_comment|/* Save current r2 value in magic place on the stack. */
l_int|0xf8
comma
l_int|0x41
comma
l_int|0x00
comma
l_int|0x28
comma
multiline_comment|/* std     r2,40(r1) */
l_int|0xe9
comma
l_int|0x6c
comma
l_int|0x00
comma
l_int|0x20
comma
multiline_comment|/* ld      r11,32(r12) */
l_int|0xe8
comma
l_int|0x4c
comma
l_int|0x00
comma
l_int|0x28
comma
multiline_comment|/* ld      r2,40(r12) */
l_int|0x7d
comma
l_int|0x69
comma
l_int|0x03
comma
l_int|0xa6
comma
multiline_comment|/* mtctr   r11 */
l_int|0x4e
comma
l_int|0x80
comma
l_int|0x04
comma
l_int|0x20
multiline_comment|/* bctr */
)brace
)brace
suffix:semicolon
multiline_comment|/* Count how many different 24-bit relocations (different symbol,&n;   different addend) */
DECL|function|count_relocs
r_static
r_int
r_int
id|count_relocs
c_func
(paren
r_const
id|Elf64_Rela
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
multiline_comment|/* FIXME: Only count external ones --RR */
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
multiline_comment|/* Only count 24-bit relocs, others don&squot;t need stubs */
r_if
c_cond
(paren
id|ELF64_R_TYPE
c_func
(paren
id|rela
(braket
id|i
)braket
dot
id|r_info
)paren
op_ne
id|R_PPC_REL24
)paren
r_continue
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
id|rela
(braket
id|i
)braket
dot
id|r_info
op_eq
id|rela
(braket
id|j
)braket
dot
id|r_info
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
multiline_comment|/* Get size of potential trampolines required. */
DECL|function|get_stubs_size
r_static
r_int
r_int
id|get_stubs_size
c_func
(paren
r_const
id|Elf64_Ehdr
op_star
id|hdr
comma
r_const
id|Elf64_Shdr
op_star
id|sechdrs
)paren
(brace
multiline_comment|/* One extra reloc so it&squot;s always 0-funcaddr terminated */
r_int
r_int
id|relocs
op_assign
l_int|1
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Every relocated section... */
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
l_string|&quot;Ptr: %p.  Number: %lu&bslash;n&quot;
comma
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
id|Elf64_Rela
)paren
)paren
suffix:semicolon
id|relocs
op_add_assign
id|count_relocs
c_func
(paren
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
id|Elf64_Rela
)paren
)paren
suffix:semicolon
)brace
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;Looks like a total of %lu stubs, max&bslash;n&quot;
comma
id|relocs
)paren
suffix:semicolon
r_return
id|relocs
op_star
r_sizeof
(paren
r_struct
id|ppc64_stub_entry
)paren
suffix:semicolon
)brace
DECL|function|module_frob_arch_sections
r_int
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
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* Find .toc and .stubs sections */
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
r_char
op_star
id|p
suffix:semicolon
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
l_string|&quot;.stubs&quot;
)paren
op_eq
l_int|0
)paren
id|me-&gt;arch.stubs_section
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
l_string|&quot;.toc&quot;
)paren
op_eq
l_int|0
)paren
id|me-&gt;arch.toc_section
op_assign
id|i
suffix:semicolon
multiline_comment|/* We don&squot;t handle .init for the moment: rename to _init */
r_while
c_loop
(paren
(paren
id|p
op_assign
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
)paren
)paren
id|p
(braket
l_int|0
)braket
op_assign
l_char|&squot;_&squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|me-&gt;arch.stubs_section
op_logical_or
op_logical_neg
id|me-&gt;arch.toc_section
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: doesn&squot;t contain .toc or .stubs.&bslash;n&quot;
comma
id|me-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
multiline_comment|/* Override the stubs size */
id|sechdrs
(braket
id|me-&gt;arch.stubs_section
)braket
dot
id|sh_size
op_assign
id|get_stubs_size
c_func
(paren
id|hdr
comma
id|sechdrs
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
l_string|&quot;%s: Non-ADD RELOCATION unsupported&bslash;n&quot;
comma
id|me-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
multiline_comment|/* Both low and high 16 bits are added as SIGNED additions, so if low&n;   16 bits has high bit set, high 16 bits must be adjusted.  These&n;   macros do that (stolen from binutils). */
DECL|macro|PPC_LO
mdefine_line|#define PPC_LO(v) ((v) &amp; 0xffff)
DECL|macro|PPC_HI
mdefine_line|#define PPC_HI(v) (((v) &gt;&gt; 16) &amp; 0xffff)
DECL|macro|PPC_HA
mdefine_line|#define PPC_HA(v) PPC_HI ((v) + 0x8000)
multiline_comment|/* Patch stub to reference function and correct r2 value. */
DECL|function|create_stub
r_static
r_inline
r_int
id|create_stub
c_func
(paren
r_struct
id|ppc64_stub_entry
op_star
id|entry
comma
r_int
r_int
id|my_r2
comma
r_int
r_int
id|func
comma
r_int
r_int
id|r2
)paren
(brace
id|Elf64_Half
op_star
id|loc1
comma
op_star
id|loc2
suffix:semicolon
r_int
id|reladdr
suffix:semicolon
op_star
id|entry
op_assign
id|ppc64_stub
suffix:semicolon
id|loc1
op_assign
(paren
id|Elf64_Half
op_star
)paren
op_amp
id|entry-&gt;jump
(braket
l_int|2
)braket
suffix:semicolon
id|loc2
op_assign
(paren
id|Elf64_Half
op_star
)paren
op_amp
id|entry-&gt;jump
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Stub uses address relative to r2, which is set to the TOC +&n;           0x8000. */
id|reladdr
op_assign
(paren
r_int
r_int
)paren
id|entry
op_minus
id|my_r2
suffix:semicolon
r_if
c_cond
(paren
id|reladdr
OG
l_int|0x7FFFFFFF
op_logical_or
id|reladdr
OL
op_minus
(paren
l_int|0x80000000L
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Address %p of stub out of range of %p.&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|reladdr
comma
(paren
r_void
op_star
)paren
id|my_r2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;Stub %p get data from reladdr %li&bslash;n&quot;
comma
id|entry
comma
id|reladdr
)paren
suffix:semicolon
op_star
id|loc1
op_assign
id|PPC_HA
c_func
(paren
id|reladdr
)paren
suffix:semicolon
op_star
id|loc2
op_assign
id|PPC_LO
c_func
(paren
id|reladdr
)paren
suffix:semicolon
id|entry-&gt;opd.funcaddr
op_assign
id|func
suffix:semicolon
id|entry-&gt;opd.r2
op_assign
id|r2
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Stub: %08X %08X %08X %08X %08X %08X %08X: %p %p&bslash;n&quot;
comma
(paren
(paren
r_int
r_int
op_star
)paren
id|entry-&gt;jump
)paren
(braket
l_int|0
)braket
comma
(paren
(paren
r_int
r_int
op_star
)paren
id|entry-&gt;jump
)paren
(braket
l_int|1
)braket
comma
(paren
(paren
r_int
r_int
op_star
)paren
id|entry-&gt;jump
)paren
(braket
l_int|2
)braket
comma
(paren
(paren
r_int
r_int
op_star
)paren
id|entry-&gt;jump
)paren
(braket
l_int|3
)braket
comma
(paren
(paren
r_int
r_int
op_star
)paren
id|entry-&gt;jump
)paren
(braket
l_int|4
)braket
comma
(paren
(paren
r_int
r_int
op_star
)paren
id|entry-&gt;jump
)paren
(braket
l_int|5
)braket
comma
(paren
(paren
r_int
r_int
op_star
)paren
id|entry-&gt;jump
)paren
(braket
l_int|6
)braket
comma
(paren
r_void
op_star
)paren
id|entry-&gt;opd.funcaddr
comma
(paren
r_void
op_star
)paren
id|entry-&gt;opd.r2
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Given &quot;.function&quot; reference, return address of &quot;function&quot; opd entry */
DECL|function|find_function
r_static
r_struct
id|ppc64_opd_entry
op_star
id|find_function
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|Elf64_Shdr
op_star
id|sechdrs
comma
r_int
r_int
id|symindex
comma
r_const
r_char
op_star
id|strtab
comma
r_struct
id|module
op_star
id|me
comma
r_struct
id|kernel_symbol_group
op_star
op_star
id|ksg
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
id|name
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
r_return
l_int|0
suffix:semicolon
id|val
op_assign
id|find_symbol_internal
c_func
(paren
id|sechdrs
comma
id|symindex
comma
id|strtab
comma
id|name
op_plus
l_int|1
comma
id|me
comma
id|ksg
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Function %s is at %p&bslash;n&quot;
comma
id|name
op_plus
l_int|1
comma
(paren
r_void
op_star
)paren
id|val
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|val
suffix:semicolon
)brace
multiline_comment|/* r2 is the TOC pointer: it actually points 0x8000 into the TOC (this&n;   gives the value maximum span in an instruction which uses a signed&n;   offset) */
DECL|function|my_r2
r_static
r_inline
r_int
r_int
id|my_r2
c_func
(paren
id|Elf64_Shdr
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
id|sechdrs
(braket
id|me-&gt;arch.toc_section
)braket
dot
id|sh_addr
op_plus
l_int|0x8000
suffix:semicolon
)brace
multiline_comment|/* Create stub for this OPD address */
DECL|function|stub_for_addr
r_static
r_int
r_int
id|stub_for_addr
c_func
(paren
id|Elf64_Shdr
op_star
id|sechdrs
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|r2
comma
r_struct
id|module
op_star
id|me
)paren
(brace
r_struct
id|ppc64_stub_entry
op_star
id|stubs
suffix:semicolon
r_int
r_int
id|i
comma
id|num_stubs
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Looking for stub for %p&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
id|num_stubs
op_assign
id|sechdrs
(braket
id|me-&gt;arch.stubs_section
)braket
dot
id|sh_size
op_div
r_sizeof
(paren
op_star
id|stubs
)paren
suffix:semicolon
multiline_comment|/* Find this stub, or if that fails, the next avail. entry */
id|stubs
op_assign
(paren
r_void
op_star
)paren
id|sechdrs
(braket
id|me-&gt;arch.stubs_section
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
id|stubs
(braket
id|i
)braket
dot
id|opd.funcaddr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|BUG_ON
c_func
(paren
id|i
op_ge
id|num_stubs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stubs
(braket
id|i
)braket
dot
id|opd.funcaddr
op_eq
id|addr
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;Reusing stub %u (%p) for %p&bslash;n&quot;
comma
id|i
comma
op_amp
id|stubs
(braket
id|i
)braket
comma
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
op_amp
id|stubs
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
id|DEBUGP
c_func
(paren
l_string|&quot;Here for %p&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|create_stub
c_func
(paren
op_amp
id|stubs
(braket
id|i
)braket
comma
id|my_r2
c_func
(paren
id|sechdrs
comma
id|me
)paren
comma
id|addr
comma
id|r2
)paren
)paren
r_return
(paren
r_int
r_int
)paren
op_minus
id|EINVAL
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;CREATED stub %u for %p&bslash;n&quot;
comma
id|i
comma
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
op_amp
id|stubs
(braket
id|i
)braket
suffix:semicolon
)brace
multiline_comment|/* We need a stub to set the toc ptr when we make external calls. */
DECL|function|do_stub_call
r_static
r_int
r_int
id|do_stub_call
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
r_void
op_star
id|location
comma
r_const
r_char
op_star
id|funcname
comma
r_struct
id|module
op_star
id|me
)paren
(brace
r_struct
id|ppc64_opd_entry
op_star
id|opd
suffix:semicolon
r_struct
id|kernel_symbol_group
op_star
id|ksg
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Doing stub for %lu (%s)&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|location
comma
id|funcname
)paren
suffix:semicolon
id|opd
op_assign
id|find_function
c_func
(paren
id|funcname
comma
id|sechdrs
comma
id|symindex
comma
id|strtab
comma
id|me
comma
op_amp
id|ksg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Can&squot;t find function `%s&squot;&bslash;n&quot;
comma
id|me-&gt;name
comma
id|funcname
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
op_minus
id|ENOENT
suffix:semicolon
)brace
r_return
id|stub_for_addr
c_func
(paren
id|sechdrs
comma
id|opd-&gt;funcaddr
comma
id|opd-&gt;r2
comma
id|me
)paren
suffix:semicolon
)brace
multiline_comment|/* We expect a noop next: if it is, replace it with instruction to&n;   restore r2. */
DECL|function|restore_r2
r_static
r_int
id|restore_r2
c_func
(paren
id|u32
op_star
id|instruction
)paren
(brace
r_if
c_cond
(paren
op_star
id|instruction
op_ne
l_int|0x60000000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Expect noop after relocate, got %08x&bslash;n&quot;
comma
op_star
id|instruction
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|instruction
op_assign
l_int|0xe8410028
suffix:semicolon
multiline_comment|/* ld r2,40(r1) */
r_return
l_int|1
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
id|Elf64_Sym
op_star
id|sym
suffix:semicolon
r_int
r_int
op_star
id|location
suffix:semicolon
r_int
r_int
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
id|rela
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
l_string|&quot;RELOC at %p: %li-type as %s (%lu) + %li&bslash;n&quot;
comma
id|location
comma
(paren
r_int
)paren
id|ELF64_R_TYPE
c_func
(paren
id|rela
(braket
id|i
)braket
dot
id|r_info
)paren
comma
id|strtab
op_plus
id|sym-&gt;st_name
comma
(paren
r_int
r_int
)paren
id|sym-&gt;st_value
comma
(paren
r_int
)paren
id|rela
(braket
id|i
)braket
dot
id|r_addend
)paren
suffix:semicolon
multiline_comment|/* REL24 references to (external) .function won&squot;t&n;                   resolve; deal with that below */
r_if
c_cond
(paren
op_logical_neg
id|sym-&gt;st_value
op_logical_and
id|ELF64_R_TYPE
c_func
(paren
id|rela
(braket
id|i
)braket
dot
id|r_info
)paren
op_ne
id|R_PPC_REL24
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Unknown symbol %s (index %u)&bslash;n&quot;
comma
id|me-&gt;name
comma
id|strtab
op_plus
id|sym-&gt;st_name
comma
id|sym-&gt;st_shndx
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
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
id|ELF64_R_TYPE
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
id|R_PPC64_ADDR32
suffix:colon
multiline_comment|/* Simply set it */
id|DEBUGP
c_func
(paren
l_string|&quot;Setting location %p to 32-bit value %u&bslash;n&quot;
comma
id|location
comma
(paren
r_int
r_int
)paren
id|value
)paren
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
id|R_PPC64_ADDR64
suffix:colon
multiline_comment|/* Simply set it */
op_star
(paren
r_int
r_int
op_star
)paren
id|location
op_assign
id|value
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Setting location %p to 64-bit value %p&bslash;n&quot;
comma
id|location
comma
(paren
r_void
op_star
)paren
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PPC64_TOC
suffix:colon
op_star
(paren
r_int
r_int
op_star
)paren
id|location
op_assign
id|my_r2
c_func
(paren
id|sechdrs
comma
id|me
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PPC64_TOC16_DS
suffix:colon
multiline_comment|/* Subtact TOC pointer */
id|value
op_sub_assign
id|my_r2
c_func
(paren
id|sechdrs
comma
id|me
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|0
op_logical_or
id|value
op_plus
l_int|0x8000
OG
l_int|0xffff
)paren
(brace
id|DEBUGP
c_func
(paren
l_string|&quot;%s: bad TOC16_DS relocation (%lu)&bslash;n&quot;
comma
id|me-&gt;name
comma
id|value
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
op_star
(paren
(paren
r_uint16
op_star
)paren
id|location
)paren
op_assign
(paren
op_star
(paren
(paren
r_uint16
op_star
)paren
id|location
)paren
op_amp
op_complement
l_int|0xfffc
)paren
op_or
(paren
id|value
op_amp
l_int|0xfffc
)paren
suffix:semicolon
id|DEBUGP
c_func
(paren
l_string|&quot;Modifying location %p by TOC (%p) =&gt; %i&bslash;n&quot;
comma
id|location
comma
(paren
r_void
op_star
)paren
id|my_r2
c_func
(paren
id|sechdrs
comma
id|me
)paren
comma
op_star
(paren
r_uint16
op_star
)paren
id|location
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|R_PPC_REL24
suffix:colon
multiline_comment|/* FIXME: Handle weak symbols here --RR */
r_if
c_cond
(paren
id|sym-&gt;st_shndx
op_eq
id|SHN_UNDEF
)paren
(brace
id|value
op_assign
id|do_stub_call
c_func
(paren
id|sechdrs
comma
id|strtab
comma
id|symindex
comma
id|location
comma
id|strtab
op_plus
id|sym-&gt;st_name
comma
id|me
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
(paren
r_void
op_star
)paren
id|value
)paren
)paren
r_return
id|value
suffix:semicolon
id|value
op_add_assign
id|rela
(braket
id|i
)braket
dot
id|r_addend
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|restore_r2
c_func
(paren
(paren
id|u32
op_star
)paren
id|location
op_plus
l_int|1
)paren
)paren
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
multiline_comment|/* Convert value to relative */
id|value
op_sub_assign
(paren
r_int
r_int
)paren
id|location
suffix:semicolon
r_if
c_cond
(paren
id|value
op_plus
l_int|0x2000000
OG
l_int|0x3ffffff
op_logical_or
(paren
id|value
op_amp
l_int|3
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;REL24 relocation %li out of range!&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|value
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
multiline_comment|/* Only replace bits 2 through 26 */
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
id|value
op_amp
l_int|0x03fffffc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unknown ADD relocation: %lu&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|ELF64_R_TYPE
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
multiline_comment|/* In arch/ppc64/mm/extable.c */
r_extern
r_void
id|sort_ex_table
c_func
(paren
r_struct
id|exception_table_entry
op_star
id|start
comma
r_struct
id|exception_table_entry
op_star
id|finish
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
r_struct
id|ppc64_stub_entry
op_star
id|stubs
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* Here is where we copy the OPD entry into the stub: we don&squot;t&n;           do it ealier in case it&squot;s actually in the same module, and&n;           hasn&squot;t been relocated yet. */
id|stubs
op_assign
(paren
r_void
op_star
)paren
id|sechdrs
(braket
id|me-&gt;arch.stubs_section
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
id|stubs
(braket
id|i
)braket
dot
id|opd.funcaddr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|ppc64_opd_entry
op_star
id|opd
suffix:semicolon
multiline_comment|/* We mark opd pointers by setting r2 to 0: otherwise&n;                   it&squot;s a function pointer already. */
r_if
c_cond
(paren
id|stubs
(braket
id|i
)braket
dot
id|opd.r2
op_eq
l_int|0
)paren
(brace
multiline_comment|/* We put the opd entry ptr in the funcaddr member. */
id|opd
op_assign
(paren
r_void
op_star
)paren
id|stubs
(braket
id|i
)braket
dot
id|opd.funcaddr
suffix:semicolon
id|stubs
(braket
id|i
)braket
dot
id|opd
op_assign
op_star
id|opd
suffix:semicolon
)brace
)brace
id|sort_ex_table
c_func
(paren
id|me-&gt;extable.entry
comma
id|me-&gt;extable.entry
op_plus
id|me-&gt;extable.num_entries
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
