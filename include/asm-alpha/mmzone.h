multiline_comment|/*&n; * Written by Kanoj Sarcar (kanoj@sgi.com) Aug 99&n; * Adapted for the alpha wildfire architecture Jan 2001.&n; */
macro_line|#ifndef _ASM_MMZONE_H_
DECL|macro|_ASM_MMZONE_H_
mdefine_line|#define _ASM_MMZONE_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
r_struct
id|bootmem_data_t
suffix:semicolon
multiline_comment|/* stupid forward decl. */
multiline_comment|/*&n; * Following are macros that are specific to this numa platform.&n; */
r_extern
id|pg_data_t
id|node_data
(braket
)braket
suffix:semicolon
DECL|macro|alpha_pa_to_nid
mdefine_line|#define alpha_pa_to_nid(pa)&t;&t;&bslash;&n;        (alpha_mv.pa_to_nid &t;&t;&bslash;&n;&t; ? alpha_mv.pa_to_nid(pa)&t;&bslash;&n;&t; : (0))
DECL|macro|node_mem_start
mdefine_line|#define node_mem_start(nid)&t;&t;&bslash;&n;        (alpha_mv.node_mem_start &t;&bslash;&n;&t; ? alpha_mv.node_mem_start(nid) &bslash;&n;&t; : (0UL))
DECL|macro|node_mem_size
mdefine_line|#define node_mem_size(nid)&t;&t;&bslash;&n;        (alpha_mv.node_mem_size &t;&bslash;&n;&t; ? alpha_mv.node_mem_size(nid) &t;&bslash;&n;&t; : ((nid) ? (0UL) : (~0UL)))
DECL|macro|pa_to_nid
mdefine_line|#define pa_to_nid(pa)&t;&t;alpha_pa_to_nid(pa)
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;&t;(&amp;node_data[(nid)])
DECL|macro|node_localnr
mdefine_line|#define node_localnr(pfn, nid)&t;((pfn) - NODE_DATA(nid)-&gt;node_start_pfn)
macro_line|#if 1
DECL|macro|PLAT_NODE_DATA_LOCALNR
mdefine_line|#define PLAT_NODE_DATA_LOCALNR(p, n)&t;&bslash;&n;&t;(((p) &gt;&gt; PAGE_SHIFT) - PLAT_NODE_DATA(n)-&gt;gendata.node_start_pfn)
macro_line|#else
r_static
r_inline
r_int
r_int
DECL|function|PLAT_NODE_DATA_LOCALNR
id|PLAT_NODE_DATA_LOCALNR
c_func
(paren
r_int
r_int
id|p
comma
r_int
id|n
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|temp
op_assign
id|p
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_return
id|temp
op_minus
id|PLAT_NODE_DATA
c_func
(paren
id|n
)paren
op_member_access_from_pointer
id|gendata.node_start_pfn
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_DISCONTIGMEM
multiline_comment|/*&n; * Following are macros that each numa implementation must define.&n; */
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; */
DECL|macro|kvaddr_to_nid
mdefine_line|#define kvaddr_to_nid(kaddr)&t;pa_to_nid(__pa(kaddr))
DECL|macro|node_mem_map
mdefine_line|#define node_mem_map(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
DECL|macro|node_start_pfn
mdefine_line|#define node_start_pfn(nid)&t;(NODE_DATA(nid)-&gt;node_start_pfn)
DECL|macro|local_mapnr
mdefine_line|#define local_mapnr(kvaddr) &bslash;&n;      ((__pa(kvaddr) &gt;&gt; PAGE_SHIFT) - node_start_pfn(kvaddr_to_nid(kvaddr)))
multiline_comment|/*&n; * Given a kaddr, LOCAL_BASE_ADDR finds the owning node of the memory&n; * and returns the kaddr corresponding to first physical page in the&n; * node&squot;s mem_map.&n; */
DECL|macro|LOCAL_BASE_ADDR
mdefine_line|#define LOCAL_BASE_ADDR(kaddr)&t;&t;&t;&t;&t;&t;  &bslash;&n;    ((unsigned long)__va(NODE_DATA(kvaddr_to_nid(kaddr))-&gt;node_start_pfn  &bslash;&n;&t;&t;&t; &lt;&lt; PAGE_SHIFT))
multiline_comment|/* XXX: FIXME -- wli */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(kaddr)&t;(0)
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;pfn_to_page(__pa(kaddr) &gt;&gt; PAGE_SHIFT)
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;(((page) - mem_map) &lt; max_mapnr)
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;(pfn_to_page(pmd_val(pmd) &gt;&gt; 32))
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(pte)&t;&t;(pte_val(pte) &gt;&gt; 32)
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;&t;&t;&t;&t;&t;     &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t; &t;     &bslash;&n;&t;pte_t pte;                                                           &bslash;&n;&t;unsigned long pfn;                                                   &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;pfn = ((unsigned long)((page)-page_zone(page)-&gt;zone_mem_map)) &lt;&lt; 32; &bslash;&n;&t;pfn += page_zone(page)-&gt;zone_start_pfn &lt;&lt; 32;&t;&t;&t;     &bslash;&n;&t;pte_val(pte) = pfn | pgprot_val(pgprot);&t;&t;&t;     &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;&t;pte;&t;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;})
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;       &t;unsigned long kvirt;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct page * __xx;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;kvirt = (unsigned long)__va(pte_val(x) &gt;&gt; (32-PAGE_SHIFT));&t;&bslash;&n;&t;__xx = virt_to_page(kvirt);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__xx;                                                           &bslash;&n;})
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; &t;unsigned long kaddr = (unsigned long)__va((pfn) &lt;&lt; PAGE_SHIFT);&t;&bslash;&n;&t;(node_mem_map(kvaddr_to_nid(kaddr)) + local_mapnr(kaddr));&t;&bslash;&n;})
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((page) - page_zone(page)-&gt;zone_mem_map +&t;&t;&t;&bslash;&n;&t; (page_zone(page)-&gt;zone_start_pfn))
DECL|macro|page_to_pa
mdefine_line|#define page_to_pa(page)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;((( (page) - page_zone(page)-&gt;zone_mem_map )&t;&t;&t;&bslash;&n;&t;+ page_zone(page)-&gt;zone_start_pfn) &lt;&lt; PAGE_SHIFT)
DECL|macro|pfn_to_nid
mdefine_line|#define pfn_to_nid(pfn)&t;&t;pa_to_nid(((u64)(pfn) &lt;&lt; PAGE_SHIFT))
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(((pfn) - node_start_pfn(pfn_to_nid(pfn))) &lt;&t;&t;&t;&bslash;&n;&t; node_spanned_pages(pfn_to_nid(pfn)))&t;&t;&t;&t;&t;&bslash;&n;
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(kaddr)&t;pfn_valid((__pa(kaddr) &gt;&gt; PAGE_SHIFT))
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /* _ASM_MMZONE_H_ */
eof
