multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/mmzone.h&n; *&n; * (C) 1999-2000, Nicolas Pitre &lt;nico@cam.org&gt;&n; * (inspired by Kanoj Sarcar&squot;s code)&n; *&n; * Because of the wide memory address space between physical RAM banks on the &n; * SA1100, it&squot;s much convenient to use Linux&squot;s NUMA support to implement our &n; * memory map representation.  Assuming all memory nodes have equal access &n; * characteristics, we then have generic discontigous memory support.&n; *&n; * Of course, all this isn&squot;t mandatory for SA1100 implementations with only&n; * one used memory bank.  For those, simply undefine CONFIG_DISCONTIGMEM.&n; *&n; * The nodes are matched with the physical memory bank addresses which are &n; * incidentally the same as virtual addresses.&n; * &n; * &t;node 0:  0xc0000000 - 0xc7ffffff&n; * &t;node 1:  0xc8000000 - 0xcfffffff&n; * &t;node 2:  0xd0000000 - 0xd7ffffff&n; * &t;node 3:  0xd8000000 - 0xdfffffff&n; */
multiline_comment|/*&n; * Currently defined in arch/arm/mm/mm-sa1100.c&n; */
r_extern
id|pg_data_t
id|sa1100_node_data
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * Return a pointer to the node data for node n.&n; */
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;(&amp;sa1100_node_data[nid])
multiline_comment|/*&n; * NODE_MEM_MAP gives the kaddr for the mem_map of the node.&n; */
DECL|macro|NODE_MEM_MAP
mdefine_line|#define NODE_MEM_MAP(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; */
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(addr) &bslash;&n;&t;&t;(((unsigned long)(addr) &amp; 0x18000000) &gt;&gt; 27)
multiline_comment|/*&n; * Given a kaddr, ADDR_TO_MAPBASE finds the owning node of the memory&n; * and returns the the mem_map of that node.&n; */
DECL|macro|ADDR_TO_MAPBASE
mdefine_line|#define ADDR_TO_MAPBASE(kaddr) &bslash;&n;&t;&t;&t;NODE_MEM_MAP(KVADDR_TO_NID((unsigned long)(kaddr)))
multiline_comment|/*&n; * Given a kaddr, LOCAL_MEM_MAP finds the owning node of the memory&n; * and returns the index corresponding to the appropriate page in the&n; * node&squot;s mem_map.&n; */
DECL|macro|LOCAL_MAP_NR
mdefine_line|#define LOCAL_MAP_NR(kvaddr) &bslash;&n;&t;(((unsigned long)(kvaddr) &amp; 0x07ffffff) &gt;&gt; PAGE_SHIFT)
multiline_comment|/*&n; * Given a kaddr, virt_to_page returns a pointer to the corresponding &n; * mem_map entry.&n; */
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr) &bslash;&n;&t;(ADDR_TO_MAPBASE(kaddr) + LOCAL_MAP_NR(kaddr))
multiline_comment|/*&n; * Didn&squot;t find the best way to validate a page pointer yet...&n; */
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;(1)
eof
