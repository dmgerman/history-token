multiline_comment|/*&n; * fixmap.h: compile-time virtual memory allocation&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998 Ingo Molnar&n; */
macro_line|#ifndef _ASM_FIXMAP_H
DECL|macro|_ASM_FIXMAP_H
mdefine_line|#define _ASM_FIXMAP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/apicdef.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/vsyscall.h&gt;
multiline_comment|/*&n; * Here we define all the compile-time &squot;special&squot; virtual&n; * addresses. The point is to have a constant address at&n; * compile time, but to set the physical address only&n; * in the boot process.&n; *&n; * these &squot;compile-time allocated&squot; memory buffers are&n; * fixed-size 4k pages. (or larger if used with an increment&n; * highger than 1) use fixmap_set(idx,phys) to associate&n; * physical memory with fixmap indices.&n; *&n; * TLB entries of such buffers will not be flushed across&n; * task switches.&n; */
DECL|enum|fixed_addresses
r_enum
id|fixed_addresses
(brace
DECL|enumerator|VSYSCALL_LAST_PAGE
id|VSYSCALL_LAST_PAGE
comma
DECL|enumerator|VSYSCALL_FIRST_PAGE
id|VSYSCALL_FIRST_PAGE
op_assign
id|VSYSCALL_LAST_PAGE
op_plus
(paren
(paren
id|VSYSCALL_END
op_minus
id|VSYSCALL_START
)paren
op_rshift
id|PAGE_SHIFT
)paren
op_minus
l_int|1
comma
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
DECL|enumerator|FIX_APIC_BASE
id|FIX_APIC_BASE
comma
multiline_comment|/* local (CPU) APIC) -- required for SMP or not */
macro_line|#endif
macro_line|#ifdef CONFIG_X86_IO_APIC
DECL|enumerator|FIX_IO_APIC_BASE_0
id|FIX_IO_APIC_BASE_0
comma
DECL|enumerator|FIX_IO_APIC_BASE_END
id|FIX_IO_APIC_BASE_END
op_assign
id|FIX_IO_APIC_BASE_0
op_plus
id|MAX_IO_APICS
op_minus
l_int|1
comma
macro_line|#endif
DECL|enumerator|__end_of_fixed_addresses
id|__end_of_fixed_addresses
)brace
suffix:semicolon
r_extern
r_void
id|__set_fixmap
(paren
r_enum
id|fixed_addresses
id|idx
comma
r_int
r_int
id|phys
comma
id|pgprot_t
id|flags
)paren
suffix:semicolon
DECL|macro|set_fixmap
mdefine_line|#define set_fixmap(idx, phys) &bslash;&n;&t;&t;__set_fixmap(idx, phys, PAGE_KERNEL)
multiline_comment|/*&n; * Some hardware wants to get fixmapped without caching.&n; */
DECL|macro|set_fixmap_nocache
mdefine_line|#define set_fixmap_nocache(idx, phys) &bslash;&n;&t;&t;__set_fixmap(idx, phys, PAGE_KERNEL_NOCACHE)
DECL|macro|FIXADDR_TOP
mdefine_line|#define FIXADDR_TOP&t;(VSYSCALL_END-PAGE_SIZE)
DECL|macro|FIXADDR_SIZE
mdefine_line|#define FIXADDR_SIZE&t;(__end_of_fixed_addresses &lt;&lt; PAGE_SHIFT)
DECL|macro|FIXADDR_START
mdefine_line|#define FIXADDR_START&t;(FIXADDR_TOP - FIXADDR_SIZE)
DECL|macro|__fix_to_virt
mdefine_line|#define __fix_to_virt(x)&t;(FIXADDR_TOP - ((x) &lt;&lt; PAGE_SHIFT))
r_extern
r_void
id|__this_fixmap_does_not_exist
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * &squot;index to address&squot; translation. If anyone tries to use the idx&n; * directly without tranlation, we catch the bug with a NULL-deference&n; * kernel oops. Illegal ranges of incoming indices are caught too.&n; */
DECL|function|fix_to_virt
r_extern
r_inline
r_int
r_int
id|fix_to_virt
c_func
(paren
r_const
r_int
r_int
id|idx
)paren
(brace
multiline_comment|/*&n;&t; * this branch gets completely eliminated after inlining,&n;&t; * except when someone tries to use fixaddr indices in an&n;&t; * illegal way. (such as mixing up address types or using&n;&t; * out-of-range indices).&n;&t; *&n;&t; * If it doesn&squot;t get removed, the linker will complain&n;&t; * loudly with a reasonably clear error message..&n;&t; */
r_if
c_cond
(paren
id|idx
op_ge
id|__end_of_fixed_addresses
)paren
id|__this_fixmap_does_not_exist
c_func
(paren
)paren
suffix:semicolon
r_return
id|__fix_to_virt
c_func
(paren
id|idx
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
