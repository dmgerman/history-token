multiline_comment|/*&n; * Written by Kanoj Sarcar (kanoj@sgi.com) Aug 99&n; * Adapted for the alpha wildfire architecture Jan 2001.&n; */
macro_line|#ifndef _ASM_MMZONE_H_
DECL|macro|_ASM_MMZONE_H_
mdefine_line|#define _ASM_MMZONE_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_NUMA_SCHED
macro_line|#include &lt;linux/numa_sched.h&gt;
macro_line|#endif
macro_line|#ifdef NOTYET
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/klkernvars.h&gt;
macro_line|#endif /* NOTYET */
DECL|struct|plat_pglist_data
r_typedef
r_struct
id|plat_pglist_data
(brace
DECL|member|gendata
id|pg_data_t
id|gendata
suffix:semicolon
macro_line|#ifdef NOTYET
DECL|member|kern_vars
id|kern_vars_t
id|kern_vars
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_NUMA) &amp;&amp; defined(CONFIG_NUMA_SCHED)
DECL|member|schedule_data
r_struct
id|numa_schedule_data
id|schedule_data
suffix:semicolon
macro_line|#endif
DECL|typedef|plat_pg_data_t
)brace
id|plat_pg_data_t
suffix:semicolon
r_struct
id|bootmem_data_t
suffix:semicolon
multiline_comment|/* stupid forward decl. */
multiline_comment|/*&n; * Following are macros that are specific to this numa platform.&n; */
r_extern
id|plat_pg_data_t
op_star
id|plat_node_data
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_ALPHA_WILDFIRE
DECL|macro|ALPHA_PA_TO_NID
macro_line|# define ALPHA_PA_TO_NID(pa)&t;((pa) &gt;&gt; 36)&t;/* 16 nodes max due 43bit kseg */
DECL|macro|NODE_MAX_MEM_SIZE
mdefine_line|#define NODE_MAX_MEM_SIZE&t;(64L * 1024L * 1024L * 1024L) /* 64 GB */
DECL|macro|MAX_NUMNODES
mdefine_line|#define MAX_NUMNODES&t;&t;WILDFIRE_MAX_QBB
macro_line|#else
DECL|macro|ALPHA_PA_TO_NID
macro_line|# define ALPHA_PA_TO_NID(pa)&t;(0)
DECL|macro|NODE_MAX_MEM_SIZE
mdefine_line|#define NODE_MAX_MEM_SIZE&t;(~0UL)
DECL|macro|MAX_NUMNODES
mdefine_line|#define MAX_NUMNODES&t;&t;1
macro_line|#endif
DECL|macro|PHYSADDR_TO_NID
mdefine_line|#define PHYSADDR_TO_NID(pa)&t;&t;ALPHA_PA_TO_NID(pa)
DECL|macro|PLAT_NODE_DATA
mdefine_line|#define PLAT_NODE_DATA(n)&t;&t;(plat_node_data[(n)])
DECL|macro|PLAT_NODE_DATA_STARTNR
mdefine_line|#define PLAT_NODE_DATA_STARTNR(n)&t;&bslash;&n;&t;(PLAT_NODE_DATA(n)-&gt;gendata.node_start_mapnr)
DECL|macro|PLAT_NODE_DATA_SIZE
mdefine_line|#define PLAT_NODE_DATA_SIZE(n)&t;&t;(PLAT_NODE_DATA(n)-&gt;gendata.node_size)
macro_line|#if 1
DECL|macro|PLAT_NODE_DATA_LOCALNR
mdefine_line|#define PLAT_NODE_DATA_LOCALNR(p, n)&t;&bslash;&n;&t;(((p) - PLAT_NODE_DATA(n)-&gt;gendata.node_start_paddr) &gt;&gt; PAGE_SHIFT)
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
op_minus
id|PLAT_NODE_DATA
c_func
(paren
id|n
)paren
op_member_access_from_pointer
id|gendata.node_start_paddr
suffix:semicolon
r_return
(paren
id|temp
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_DISCONTIGMEM
multiline_comment|/*&n; * Following are macros that each numa implmentation must define.&n; */
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; */
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(kaddr)&t;PHYSADDR_TO_NID(__pa(kaddr))
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
mdefine_line|#define LOCAL_BASE_ADDR(kaddr)&t;((unsigned long)__va(NODE_DATA(KVADDR_TO_NID(kaddr))-&gt;node_start_paddr))
DECL|macro|LOCAL_MAP_NR
mdefine_line|#define LOCAL_MAP_NR(kvaddr) &bslash;&n;&t;(((unsigned long)(kvaddr)-LOCAL_BASE_ADDR(kvaddr)) &gt;&gt; PAGE_SHIFT)
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(kaddr)&t;test_bit(LOCAL_MAP_NR(kaddr), &bslash;&n;&t;&t;&t;&t;&t; NODE_DATA(KVADDR_TO_NID(kaddr))-&gt;valid_addr_bitmap)
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;(ADDR_TO_MAPBASE(kaddr) + LOCAL_MAP_NR(kaddr))
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;(((page) - mem_map) &lt; max_mapnr)
macro_line|#ifdef CONFIG_NUMA
macro_line|#ifdef CONFIG_NUMA_SCHED
DECL|macro|NODE_SCHEDULE_DATA
mdefine_line|#define NODE_SCHEDULE_DATA(nid)&t;(&amp;((PLAT_NODE_DATA(nid))-&gt;schedule_data))
macro_line|#endif
macro_line|#ifdef CONFIG_ALPHA_WILDFIRE
multiline_comment|/* With wildfire assume 4 CPUs per node */
DECL|macro|cputonode
mdefine_line|#define cputonode(cpu)&t;((cpu) &gt;&gt; 2)
macro_line|#else
DECL|macro|cputonode
mdefine_line|#define cputonode(cpu)&t;0
macro_line|#endif /* CONFIG_ALPHA_WILDFIRE */
DECL|macro|numa_node_id
mdefine_line|#define numa_node_id()&t;cputonode(smp_processor_id())
macro_line|#endif /* CONFIG_NUMA */
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /* _ASM_MMZONE_H_ */
eof
