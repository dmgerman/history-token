multiline_comment|/*&n; * Written by Kanoj Sarcar (kanoj@sgi.com) Jan 2000&n; * Copyright, 2000, Silicon Graphics, sprasad@engr.sgi.com&n; */
macro_line|#ifndef _LINUX_ASM_SN_MMZONE_H
DECL|macro|_LINUX_ASM_SN_MMZONE_H
mdefine_line|#define _LINUX_ASM_SN_MMZONE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/mmzone_sn1.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
multiline_comment|/*&n; * Memory is conceptually divided into chunks. A chunk is either&n; * completely present, or else the kernel assumes it is completely&n; * absent. Each node consists of a number of contiguous chunks.&n; */
DECL|macro|CHUNKMASK
mdefine_line|#define CHUNKMASK       &t;(~(CHUNKSZ - 1))
DECL|macro|CHUNKNUM
mdefine_line|#define CHUNKNUM(vaddr)        &t;(__pa(vaddr) &gt;&gt; CHUNKSHIFT)
DECL|macro|PCHUNKNUM
mdefine_line|#define PCHUNKNUM(paddr)        ((paddr) &gt;&gt; CHUNKSHIFT)
DECL|macro|MAXCHUNKS
mdefine_line|#define MAXCHUNKS      &t;&t;(MAXNODES * MAX_CHUNKS_PER_NODE)
r_extern
r_int
id|chunktonid
(braket
)braket
suffix:semicolon
DECL|macro|CHUNKTONID
mdefine_line|#define CHUNKTONID(cnum)       (chunktonid[cnum])
DECL|struct|plat_pglist_data
r_typedef
r_struct
id|plat_pglist_data
(brace
DECL|member|gendata
id|pg_data_t
id|gendata
suffix:semicolon
multiline_comment|/* try to keep this first. */
DECL|member|virtstart
r_int
r_int
id|virtstart
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|typedef|plat_pg_data_t
)brace
id|plat_pg_data_t
suffix:semicolon
r_extern
id|plat_pg_data_t
id|plat_node_data
(braket
)braket
suffix:semicolon
r_extern
r_int
id|numa_debug
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * The foll two will move into linux/mmzone.h RSN.&n; */
DECL|macro|NODE_START
mdefine_line|#define NODE_START(n)  plat_node_data[(n)].virtstart
DECL|macro|NODE_SIZE
mdefine_line|#define NODE_SIZE(n)   plat_node_data[(n)].size
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(kaddr) &bslash;&n;       ((CHUNKTONID(CHUNKNUM((kaddr))) != -1) ? (CHUNKTONID(CHUNKNUM((kaddr)))) : &bslash;&n;       (printk(&quot;DISCONTIGBUG: %s line %d addr 0x%lx&quot;, __FILE__, __LINE__, &bslash;&n;       (unsigned long)(kaddr)), numa_debug()))
macro_line|#if 0
mdefine_line|#define KVADDR_TO_NID(kaddr) CHUNKTONID(CHUNKNUM((kaddr)))
macro_line|#endif
multiline_comment|/* These 2 macros should never be used if KVADDR_TO_NID(kaddr) is -1 */
multiline_comment|/*&n; * Given a kaddr, ADDR_TO_MAPBASE finds the owning node of the memory&n; * and returns the mem_map of that node.&n; */
DECL|macro|ADDR_TO_MAPBASE
mdefine_line|#define ADDR_TO_MAPBASE(kaddr) &bslash;&n;                       NODE_MEM_MAP(KVADDR_TO_NID((unsigned long)(kaddr)))
multiline_comment|/*&n; * Given a kaddr, LOCAL_BASE_ADDR finds the owning node of the memory&n; * and returns the kaddr corresponding to first physical page in the&n; * node&squot;s mem_map.&n; */
DECL|macro|LOCAL_BASE_ADDR
mdefine_line|#define LOCAL_BASE_ADDR(kaddr) NODE_START(KVADDR_TO_NID(kaddr))
macro_line|#ifdef CONFIG_DISCONTIGMEM
multiline_comment|/*&n; * Return a pointer to the node data for node n.&n; * Assume that n is the compact node id.&n; */
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(n)   (&amp;((plat_node_data + (n))-&gt;gendata))
multiline_comment|/*&n; * NODE_MEM_MAP gives the kaddr for the mem_map of the node.&n; */
DECL|macro|NODE_MEM_MAP
mdefine_line|#define NODE_MEM_MAP(nid)      (NODE_DATA((nid))-&gt;node_mem_map)
multiline_comment|/* This macro should never be used if KVADDR_TO_NID(kaddr) is -1 */
DECL|macro|LOCAL_MAP_NR
mdefine_line|#define LOCAL_MAP_NR(kvaddr) &bslash;&n;        (((unsigned long)(kvaddr)-LOCAL_BASE_ADDR((kvaddr))) &gt;&gt; PAGE_SHIFT)
DECL|macro|MAP_NR_SN1
mdefine_line|#define MAP_NR_SN1(kaddr)   (LOCAL_MAP_NR((kaddr)) + &bslash;&n;                (((unsigned long)ADDR_TO_MAPBASE((kaddr)) - PAGE_OFFSET) / &bslash;&n;                sizeof(mem_map_t)))
macro_line|#if 0
mdefine_line|#define MAP_NR_VALID(kaddr)   (LOCAL_MAP_NR((kaddr)) + &bslash;&n;                (((unsigned long)ADDR_TO_MAPBASE((kaddr)) - PAGE_OFFSET) / &bslash;&n;                sizeof(mem_map_t)))
mdefine_line|#define MAP_NR_SN1(kaddr)&t;((KVADDR_TO_NID(kaddr) == -1) ? (max_mapnr + 1) :&bslash;&n;&t;&t;&t;&t;MAP_NR_VALID(kaddr))
macro_line|#endif
multiline_comment|/* FIXME */
DECL|macro|sn1_pte_pagenr
mdefine_line|#define sn1_pte_pagenr(x)&t;&t;MAP_NR_SN1(PAGE_OFFSET + (unsigned long)((pte_val(x)&amp;_PFN_MASK) &amp; PAGE_MASK))
DECL|macro|pte_page
mdefine_line|#define pte_page(pte)&t;&t;&t;(mem_map + sn1_pte_pagenr(pte))
multiline_comment|/* FIXME */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)   ((KVADDR_TO_NID((unsigned long)addr) &gt;= &bslash;&n;        numnodes) ? 0 : (test_bit(LOCAL_MAP_NR((addr)), &bslash;&n;        NODE_DATA(KVADDR_TO_NID((unsigned long)addr))-&gt;valid_addr_bitmap)))
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;(mem_map + MAP_NR_SN1(kaddr))
macro_line|#else /* CONFIG_DISCONTIGMEM */
DECL|macro|MAP_NR_SN1
mdefine_line|#define MAP_NR_SN1(addr)&t;(((unsigned long) (addr) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT)
macro_line|#endif /* CONFIG_DISCONTIGMEM */
DECL|macro|numa_node_id
mdefine_line|#define numa_node_id()&t;&t;cpuid_to_cnodeid(smp_processor_id())
macro_line|#endif /* !_LINUX_ASM_SN_MMZONE_H */
eof
