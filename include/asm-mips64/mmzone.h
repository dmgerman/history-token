multiline_comment|/*&n; * Written by Kanoj Sarcar (kanoj@sgi.com) Aug 99&n; */
macro_line|#ifndef _ASM_MMZONE_H_
DECL|macro|_ASM_MMZONE_H_
mdefine_line|#define _ASM_MMZONE_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/klkernvars.h&gt;
DECL|struct|plat_pglist_data
r_typedef
r_struct
id|plat_pglist_data
(brace
DECL|member|gendata
id|pg_data_t
id|gendata
suffix:semicolon
DECL|member|kern_vars
id|kern_vars_t
id|kern_vars
suffix:semicolon
DECL|typedef|plat_pg_data_t
)brace
id|plat_pg_data_t
suffix:semicolon
multiline_comment|/*&n; * Following are macros that are specific to this numa platform.&n; */
r_extern
r_int
id|numa_debug
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|plat_pg_data_t
op_star
id|plat_node_data
(braket
)braket
suffix:semicolon
DECL|macro|PHYSADDR_TO_NID
mdefine_line|#define PHYSADDR_TO_NID(pa)&t;&t;NASID_TO_COMPACT_NODEID(NASID_GET(pa))
DECL|macro|PLAT_NODE_DATA
mdefine_line|#define PLAT_NODE_DATA(n)&t;&t;(plat_node_data[n])
DECL|macro|PLAT_NODE_DATA_STARTNR
mdefine_line|#define PLAT_NODE_DATA_STARTNR(n)    (PLAT_NODE_DATA(n)-&gt;gendata.node_start_mapnr)
DECL|macro|PLAT_NODE_DATA_SIZE
mdefine_line|#define PLAT_NODE_DATA_SIZE(n)&t;     (PLAT_NODE_DATA(n)-&gt;gendata.node_size)
DECL|macro|PLAT_NODE_DATA_LOCALNR
mdefine_line|#define PLAT_NODE_DATA_LOCALNR(p, n) &bslash;&n;&t;&t;(((p) - PLAT_NODE_DATA(n)-&gt;gendata.node_start_paddr) &gt;&gt; PAGE_SHIFT)
DECL|macro|numa_node_id
mdefine_line|#define numa_node_id()&t;cputocnode(current-&gt;processor)
macro_line|#ifdef CONFIG_DISCONTIGMEM
multiline_comment|/*&n; * Following are macros that each numa implmentation must define.&n; */
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; */
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(kaddr) &bslash;&n;&t;((NASID_TO_COMPACT_NODEID(NASID_GET(__pa(kaddr))) != -1) ? &bslash;&n;&t;(NASID_TO_COMPACT_NODEID(NASID_GET(__pa(kaddr)))) : &bslash;&n;&t;(printk(&quot;NUMABUG: %s line %d addr 0x%lx&quot;, __FILE__, __LINE__, kaddr), &bslash;&n;&t;numa_debug(), -1))
multiline_comment|/*&n; * Return a pointer to the node data for node n.&n; */
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(n)&t;(&amp;((PLAT_NODE_DATA(n))-&gt;gendata))
multiline_comment|/*&n; * NODE_MEM_MAP gives the kaddr for the mem_map of the node.&n; */
DECL|macro|NODE_MEM_MAP
mdefine_line|#define NODE_MEM_MAP(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
multiline_comment|/*&n; * Given a kaddr, ADDR_TO_MAPBASE finds the owning node of the memory&n; * and returns the the mem_map of that node.&n; */
DECL|macro|ADDR_TO_MAPBASE
mdefine_line|#define ADDR_TO_MAPBASE(kaddr) &bslash;&n;&t;&t;&t;NODE_MEM_MAP(KVADDR_TO_NID((unsigned long)(kaddr)))
multiline_comment|/*&n; * Given a kaddr, LOCAL_BASE_ADDR finds the owning node of the memory&n; * and returns the kaddr corresponding to first physical page in the&n; * node&squot;s mem_map.&n; */
DECL|macro|LOCAL_BASE_ADDR
mdefine_line|#define LOCAL_BASE_ADDR(kaddr)&t;((unsigned long)(kaddr) &amp; ~(NODE_MAX_MEM_SIZE-1))
DECL|macro|LOCAL_MAP_NR
mdefine_line|#define LOCAL_MAP_NR(kvaddr) &bslash;&n;&t;(((unsigned long)(kvaddr)-LOCAL_BASE_ADDR((kvaddr))) &gt;&gt; PAGE_SHIFT)
DECL|macro|MIPS64_NR
mdefine_line|#define MIPS64_NR(kaddr) (((unsigned long)(kaddr) &gt; (unsigned long)high_memory)&bslash;&n;&t;&t;? (max_mapnr + 1) : (LOCAL_MAP_NR((kaddr)) + &bslash;&n;&t;&t;(((unsigned long)ADDR_TO_MAPBASE((kaddr)) - PAGE_OFFSET) / &bslash;&n;&t;&t;sizeof(mem_map_t))))
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;((KVADDR_TO_NID((unsigned long)addr) &gt; &bslash;&n;&t;-1) ? 0 : (test_bit(LOCAL_MAP_NR((addr)), &bslash;&n;&t;NODE_DATA(KVADDR_TO_NID((unsigned long)addr))-&gt;valid_addr_bitmap)))
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;(mem_map + MIPS64_NR(kaddr))
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;((page - mem_map) &lt; max_mapnr)
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /* _ASM_MMZONE_H_ */
eof
