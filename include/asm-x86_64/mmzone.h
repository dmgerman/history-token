multiline_comment|/* K8 NUMA support */
multiline_comment|/* Copyright 2002,2003 by Andi Kleen, SuSE Labs */
multiline_comment|/* 2.5 Version loosely based on the NUMAQ Code by Pat Gaughen. */
macro_line|#ifndef _ASM_X86_64_MMZONE_H
DECL|macro|_ASM_X86_64_MMZONE_H
mdefine_line|#define _ASM_X86_64_MMZONE_H 1
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DISCONTIGMEM
DECL|macro|VIRTUAL_BUG_ON
mdefine_line|#define VIRTUAL_BUG_ON(x) 
macro_line|#include &lt;asm/smp.h&gt;
DECL|macro|MAXNODE
mdefine_line|#define MAXNODE 8 
DECL|macro|NODEMAPSIZE
mdefine_line|#define NODEMAPSIZE 0xff
multiline_comment|/* Simple perfect hash to map physical addresses to node numbers */
r_extern
r_int
id|memnode_shift
suffix:semicolon
r_extern
id|u8
id|memnodemap
(braket
id|NODEMAPSIZE
)braket
suffix:semicolon
r_extern
r_int
id|maxnode
suffix:semicolon
r_extern
r_struct
id|pglist_data
op_star
id|node_data
(braket
)braket
suffix:semicolon
DECL|function|phys_to_nid
r_static
r_inline
id|__attribute__
c_func
(paren
(paren
id|pure
)paren
)paren
r_int
id|phys_to_nid
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|nid
suffix:semicolon
id|VIRTUAL_BUG_ON
c_func
(paren
(paren
id|addr
op_rshift
id|memnode_shift
)paren
op_ge
id|NODEMAPSIZE
)paren
suffix:semicolon
id|nid
op_assign
id|memnodemap
(braket
id|addr
op_rshift
id|memnode_shift
)braket
suffix:semicolon
id|VIRTUAL_BUG_ON
c_func
(paren
id|nid
OG
id|maxnode
)paren
suffix:semicolon
r_return
id|nid
suffix:semicolon
)brace
DECL|macro|pfn_to_nid
mdefine_line|#define pfn_to_nid(pfn) phys_to_nid((unsigned long)(pfn) &lt;&lt; PAGE_SHIFT)
DECL|macro|kvaddr_to_nid
mdefine_line|#define kvaddr_to_nid(kaddr)&t;phys_to_nid(__pa(kaddr))
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;&t;(node_data[nid])
DECL|macro|node_mem_map
mdefine_line|#define node_mem_map(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
DECL|macro|node_mem_map
mdefine_line|#define node_mem_map(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
DECL|macro|node_start_pfn
mdefine_line|#define node_start_pfn(nid)&t;(NODE_DATA(nid)-&gt;node_start_pfn)
DECL|macro|node_end_pfn
mdefine_line|#define node_end_pfn(nid)       (NODE_DATA(nid)-&gt;node_start_pfn + &bslash;&n;&t;&t;&t;&t; NODE_DATA(nid)-&gt;node_spanned_pages)
DECL|macro|local_mapnr
mdefine_line|#define local_mapnr(kvaddr) &bslash;&n;&t;( (__pa(kvaddr) &gt;&gt; PAGE_SHIFT) - node_start_pfn(kvaddr_to_nid(kvaddr)) )
multiline_comment|/* AK: this currently doesn&squot;t deal with invalid addresses. We&squot;ll see &n;   if the 2.5 kernel doesn&squot;t pass them&n;   (2.4 used to). */
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn) ({ &bslash;&n;&t;int nid = phys_to_nid(((unsigned long)(pfn)) &lt;&lt; PAGE_SHIFT); &t;&bslash;&n;&t;((pfn) - node_start_pfn(nid)) + node_mem_map(nid);&t;&t;&bslash;&n;})
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page) &bslash;&n;&t;(long)(((page) - page_zone(page)-&gt;zone_mem_map) + page_zone(page)-&gt;zone_start_pfn)
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn) ((pfn) &gt;= num_physpages ? 0 : &bslash;&n;&t;&t;&t;({ u8 nid__ = pfn_to_nid(pfn); &bslash;&n;&t;&t;&t;   nid__ != 0xff &amp;&amp; (pfn) &gt;= node_start_pfn(nid__) &amp;&amp; (pfn) &lt;= node_end_pfn(nid__); }))
macro_line|#endif
macro_line|#endif
eof
