multiline_comment|/*&n; * Written by Kanoj Sarcar (kanoj@sgi.com) Aug 99&n; * Rewritten for Linux 2.6 by Christoph Hellwig (hch@lst.de) Jan 2004&n; */
macro_line|#ifndef _ASM_MMZONE_H_
DECL|macro|_ASM_MMZONE_H_
mdefine_line|#define _ASM_MMZONE_H_
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;mmzone.h&gt;
DECL|macro|kvaddr_to_nid
mdefine_line|#define kvaddr_to_nid(kvaddr)&t;pa_to_nid(__pa(kvaddr))
DECL|macro|pfn_to_nid
mdefine_line|#define pfn_to_nid(pfn)&t;&t;pa_to_nid((pfn) &lt;&lt; PAGE_SHIFT)
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; &t;unsigned long __pfn = (pfn);&t;&t;&t;&t;&bslash;&n; &t;int __n = pfn_to_nid(__pfn);&t;&t;&t;&t;&bslash;&n;&t;((__n &gt;= 0) ? (__pfn &lt; NODE_DATA(__n)-&gt;node_start_pfn +&t;&bslash;&n;&t;&t;       NODE_DATA(__n)-&gt;node_spanned_pages) : 0);&bslash;&n;})
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; &t;unsigned long __pfn = (pfn);&t;&t;&t;&t;&bslash;&n;&t;pg_data_t *__pg = NODE_DATA(pfn_to_nid(__pfn));&t;&t;&bslash;&n;&t;__pg-&gt;node_mem_map + (__pfn - __pg-&gt;node_start_pfn);&t;&bslash;&n;})
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(p)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct page *__p = (p);&t;&t;&t;&t;&t;&bslash;&n;&t;struct zone *__z = page_zone(__p);&t;&t;&t;&bslash;&n;&t;((__p - __z-&gt;zone_mem_map) + __z-&gt;zone_start_pfn);&t;&bslash;&n;})
multiline_comment|/* XXX: FIXME -- wli */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(0)
macro_line|#endif /* _ASM_MMZONE_H_ */
eof
