macro_line|#ifndef __UM_FIXMAP_H
DECL|macro|__UM_FIXMAP_H
mdefine_line|#define __UM_FIXMAP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/kmap_types.h&gt;
macro_line|#include &lt;asm/archparam.h&gt;
multiline_comment|/*&n; * Here we define all the compile-time &squot;special&squot; virtual&n; * addresses. The point is to have a constant address at&n; * compile time, but to set the physical address only&n; * in the boot process. We allocate these special  addresses&n; * from the end of virtual memory (0xfffff000) backwards.&n; * Also this lets us do fail-safe vmalloc(), we&n; * can guarantee that these special addresses and&n; * vmalloc()-ed addresses never overlap.&n; *&n; * these &squot;compile-time allocated&squot; memory buffers are&n; * fixed-size 4k pages. (or larger if used with an increment&n; * highger than 1) use fixmap_set(idx,phys) to associate&n; * physical memory with fixmap indices.&n; *&n; * TLB entries of such buffers will not be flushed across&n; * task switches.&n; */
multiline_comment|/*&n; * on UP currently we will have no trace of the fixmap mechanizm,&n; * no page table allocations, etc. This might change in the&n; * future, say framebuffers for the console driver(s) could be&n; * fix-mapped?&n; */
DECL|enum|fixed_addresses
r_enum
id|fixed_addresses
(brace
macro_line|#ifdef CONFIG_HIGHMEM
DECL|enumerator|FIX_KMAP_BEGIN
id|FIX_KMAP_BEGIN
comma
multiline_comment|/* reserved pte&squot;s for temporary kernel mappings */
DECL|enumerator|FIX_KMAP_END
id|FIX_KMAP_END
op_assign
id|FIX_KMAP_BEGIN
op_plus
(paren
id|KM_TYPE_NR
op_star
id|NR_CPUS
)paren
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
multiline_comment|/*&n; * used by vmalloc.c.&n; *&n; * Leave one empty page between vmalloc&squot;ed areas and&n; * the start of the fixmap, and leave one page empty&n; * at the top of mem..&n; */
r_extern
r_int
r_int
id|get_kmem_end
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|FIXADDR_TOP
mdefine_line|#define FIXADDR_TOP&t;(get_kmem_end() - 0x2000)
DECL|macro|FIXADDR_SIZE
mdefine_line|#define FIXADDR_SIZE&t;(__end_of_fixed_addresses &lt;&lt; PAGE_SHIFT)
DECL|macro|FIXADDR_START
mdefine_line|#define FIXADDR_START&t;(FIXADDR_TOP - FIXADDR_SIZE)
DECL|macro|__fix_to_virt
mdefine_line|#define __fix_to_virt(x)&t;(FIXADDR_TOP - ((x) &lt;&lt; PAGE_SHIFT))
DECL|macro|__virt_to_fix
mdefine_line|#define __virt_to_fix(x)      ((FIXADDR_TOP - ((x)&amp;PAGE_MASK)) &gt;&gt; PAGE_SHIFT)
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
r_static
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
DECL|function|virt_to_fix
r_static
r_inline
r_int
r_int
id|virt_to_fix
c_func
(paren
r_const
r_int
r_int
id|vaddr
)paren
(brace
id|BUG_ON
c_func
(paren
id|vaddr
op_ge
id|FIXADDR_TOP
op_logical_or
id|vaddr
OL
id|FIXADDR_START
)paren
suffix:semicolon
r_return
id|__virt_to_fix
c_func
(paren
id|vaddr
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
