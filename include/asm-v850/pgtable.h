macro_line|#ifndef __V850_PGTABLE_H__
DECL|macro|__V850_PGTABLE_H__
mdefine_line|#define __V850_PGTABLE_H__
macro_line|#include &lt;asm-generic/4level-fixup.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd)&t;(1) /* pages are always present on NO_MM */
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd)&t;&t;(0)
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;(0)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgdp)&t;&t;((void)0)
DECL|macro|pmd_offset
mdefine_line|#define&t;pmd_offset(a, b)&t;((void *)0)
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;(0)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;(0)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(typ,off)&t;((swp_entry_t) { ((typ) | ((off) &lt;&lt; 7)) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;((pte_t) { (x).val })
multiline_comment|/* These mean nothing to !CONFIG_MMU.  */
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;&t;__pgprot(0)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;&t;__pgprot(0)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;&t;__pgprot(0)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;&t;__pgprot(0)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;&t;__pgprot(0)
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc.  When CONFIG_MMU is not defined, this&n; * should never actually be used, so just define it to something that&squot;s&n; * will hopefully cause a bus error if it is.&n; */
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr)&t;((void *)0x87654321)
multiline_comment|/* Some bogus code in procfs uses these; whatever.  */
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;0
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;(~0)
r_extern
r_void
id|paging_init
(paren
r_void
)paren
suffix:semicolon
DECL|macro|swapper_pg_dir
mdefine_line|#define swapper_pg_dir ((pgd_t *) 0)
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()   ((void)0)
r_extern
r_int
r_int
id|kobjsize
c_func
(paren
r_const
r_void
op_star
id|objp
)paren
suffix:semicolon
macro_line|#endif /* __V850_PGTABLE_H__ */
eof
