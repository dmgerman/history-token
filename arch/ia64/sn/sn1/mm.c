multiline_comment|/*&n; * Copyright, 2000-2001, Silicon Graphics.&n; * Copyright Srinivasa Thirumalachar (sprasad@engr.sgi.com)&n; * Copyright 2000-2001 Kanoj Sarcar (kanoj@sgi.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/efi.h&gt;
macro_line|#include &lt;asm/sn/mmzone_sn1.h&gt;
DECL|macro|MIN
mdefine_line|#define MIN(a,b)&t;((a) &lt; (b) ? (a) : (b))
DECL|macro|MAX
mdefine_line|#define MAX(a,b)&t;((a) &gt; (b) ? (a) : (b))
DECL|macro|DONE_NOTHING
mdefine_line|#define DONE_NOTHING&t;0
DECL|macro|DONE_FINDING
mdefine_line|#define DONE_FINDING&t;1
DECL|macro|DONE_BUILDING
mdefine_line|#define DONE_BUILDING&t;2
DECL|struct|nodemem_s
r_struct
id|nodemem_s
(brace
DECL|member|start
id|u64
id|start
suffix:semicolon
multiline_comment|/* start of kernel usable memory */
DECL|member|end
id|u64
id|end
suffix:semicolon
multiline_comment|/* end of kernel usable memory */
DECL|member|mtot
id|u64
id|mtot
suffix:semicolon
multiline_comment|/* total kernel usable memory */
DECL|member|done
id|u64
id|done
suffix:semicolon
multiline_comment|/* state of bootmem initialization */
DECL|member|bstart
id|u64
id|bstart
suffix:semicolon
multiline_comment|/* where should the bootmem area be */
DECL|member|bsize
id|u64
id|bsize
suffix:semicolon
multiline_comment|/* bootmap size */
DECL|member|hole
id|u64
id|hole
(braket
id|SN1_MAX_BANK_PER_NODE
)braket
suffix:semicolon
DECL|variable|nodemem
)brace
id|nodemem
(braket
id|MAXNODES
)braket
suffix:semicolon
DECL|variable|nodemem_valid
r_static
r_int
id|nodemem_valid
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|__init
DECL|function|free_unused_memmap_hole
id|free_unused_memmap_hole
c_func
(paren
r_int
id|nid
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_struct
id|page
op_star
id|page
comma
op_star
id|pageend
suffix:semicolon
r_int
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|end
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Get the memmap ptrs to the start and end of the holes.&n;&t; * virt_to_page(start) will panic, if start is in hole.&n;&t; * Can we do virt_to_page(end), if end is on the next node?&n;&t; */
id|page
op_assign
id|virt_to_page
c_func
(paren
id|start
op_minus
l_int|1
)paren
suffix:semicolon
id|page
op_increment
suffix:semicolon
id|pageend
op_assign
id|virt_to_page
c_func
(paren
id|end
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;hpage=0x%lx, hpageend=0x%lx&bslash;n&quot;
comma
(paren
id|u64
)paren
id|page
comma
(paren
id|u64
)paren
id|pageend
)paren
suffix:semicolon
id|free_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|nid
)paren
comma
id|__pa
c_func
(paren
id|page
)paren
comma
(paren
id|u64
)paren
id|pageend
op_minus
(paren
id|u64
)paren
id|page
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|free_unused_memmap_node
id|free_unused_memmap_node
c_func
(paren
r_int
id|nid
)paren
(brace
id|u64
id|i
op_assign
l_int|0
suffix:semicolon
id|u64
id|holestart
op_assign
op_minus
l_int|1
suffix:semicolon
id|u64
id|start
op_assign
id|nodemem
(braket
id|nid
)braket
dot
id|start
suffix:semicolon
id|start
op_assign
(paren
(paren
id|start
op_rshift
id|SN1_NODE_ADDR_SHIFT
)paren
op_lshift
id|SN1_NODE_ADDR_SHIFT
)paren
suffix:semicolon
r_do
(brace
id|holestart
op_assign
id|nodemem
(braket
id|nid
)braket
dot
id|hole
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_while
c_loop
(paren
(paren
id|i
OL
id|SN1_MAX_BANK_PER_NODE
)paren
op_logical_and
(paren
id|nodemem
(braket
id|nid
)braket
dot
id|hole
(braket
id|i
)braket
op_eq
(paren
id|u64
)paren
op_minus
l_int|1
)paren
)paren
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|SN1_MAX_BANK_PER_NODE
)paren
id|free_unused_memmap_hole
c_func
(paren
id|nid
comma
id|holestart
comma
id|start
op_plus
(paren
id|i
op_lshift
id|SN1_BANK_ADDR_SHIFT
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OL
id|SN1_MAX_BANK_PER_NODE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Since efi_memmap_walk merges contiguous banks, this code will need&n; * to find all the nasid/banks covered by the input memory descriptor.&n; */
r_static
r_int
id|__init
DECL|function|build_nodemem_map
id|build_nodemem_map
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_void
op_star
id|arg
)paren
(brace
r_int
r_int
id|vaddr
op_assign
id|start
suffix:semicolon
r_int
r_int
id|nvaddr
suffix:semicolon
r_int
id|nasid
op_assign
id|GetNasId
c_func
(paren
id|__pa
c_func
(paren
id|vaddr
)paren
)paren
suffix:semicolon
r_int
id|cnodeid
comma
id|bankid
suffix:semicolon
r_while
c_loop
(paren
id|vaddr
OL
id|end
)paren
(brace
id|cnodeid
op_assign
id|NASID_TO_CNODEID
c_func
(paren
id|nasid
)paren
suffix:semicolon
id|bankid
op_assign
id|GetBankId
c_func
(paren
id|__pa
c_func
(paren
id|vaddr
)paren
)paren
suffix:semicolon
id|nodemem
(braket
id|cnodeid
)braket
dot
id|start
op_assign
id|MIN
c_func
(paren
id|nodemem
(braket
id|cnodeid
)braket
dot
id|start
comma
id|vaddr
)paren
suffix:semicolon
id|nvaddr
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
(paren
r_int
r_int
)paren
(paren
op_increment
id|nasid
)paren
op_lshift
id|SN1_NODE_ADDR_SHIFT
)paren
suffix:semicolon
id|nodemem
(braket
id|cnodeid
)braket
dot
id|end
op_assign
id|MAX
c_func
(paren
id|nodemem
(braket
id|cnodeid
)braket
dot
id|end
comma
id|MIN
c_func
(paren
id|end
comma
id|nvaddr
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|bankid
OL
id|SN1_MAX_BANK_PER_NODE
)paren
op_logical_and
(paren
id|vaddr
OL
id|nodemem
(braket
id|cnodeid
)braket
dot
id|end
)paren
)paren
(brace
id|nvaddr
op_assign
id|nodemem
(braket
id|cnodeid
)braket
dot
id|start
op_plus
(paren
(paren
r_int
r_int
)paren
(paren
id|bankid
op_plus
l_int|1
)paren
op_lshift
id|SN1_BANK_ADDR_SHIFT
)paren
suffix:semicolon
id|nodemem
(braket
id|cnodeid
)braket
dot
id|hole
(braket
id|bankid
op_increment
)braket
op_assign
id|MIN
c_func
(paren
id|nvaddr
comma
id|end
)paren
suffix:semicolon
id|vaddr
op_assign
id|nvaddr
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|pgtbl_size_ok
id|pgtbl_size_ok
c_func
(paren
r_int
id|nid
)paren
(brace
r_int
r_int
id|numpfn
comma
id|bank0size
comma
id|nodesize
suffix:semicolon
r_int
r_int
id|start
op_assign
id|nodemem
(braket
id|nid
)braket
dot
id|start
suffix:semicolon
id|start
op_assign
(paren
(paren
id|start
op_rshift
id|SN1_NODE_ADDR_SHIFT
)paren
op_lshift
id|SN1_NODE_ADDR_SHIFT
)paren
suffix:semicolon
id|nodesize
op_assign
id|nodemem
(braket
id|nid
)braket
dot
id|end
op_minus
id|start
suffix:semicolon
id|numpfn
op_assign
id|nodesize
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|bank0size
op_assign
id|nodemem
(braket
id|nid
)braket
dot
id|hole
(braket
l_int|0
)braket
op_minus
id|start
suffix:semicolon
multiline_comment|/* If nid == master node &amp;&amp; no kernel text replication */
id|bank0size
op_sub_assign
l_int|0xA00000
suffix:semicolon
multiline_comment|/* Kernel text + stuff */
id|bank0size
op_sub_assign
(paren
(paren
id|numpfn
op_plus
l_int|7
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|numpfn
op_star
r_sizeof
(paren
id|mem_map_t
)paren
)paren
OG
id|bank0size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nid = %d, ns=0x%lx, npfn=0x%lx, bank0size=0x%lx&bslash;n&quot;
comma
id|nid
comma
id|nodesize
comma
id|numpfn
comma
id|bank0size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|check_pgtbl_size
id|check_pgtbl_size
c_func
(paren
r_int
id|nid
)paren
(brace
r_int
id|bank
op_assign
id|SN1_MAX_BANK_PER_NODE
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Find highest bank with valid memory */
r_while
c_loop
(paren
(paren
id|nodemem
(braket
id|nid
)braket
dot
id|hole
(braket
id|bank
)braket
op_eq
op_minus
l_int|1
)paren
op_logical_and
(paren
id|bank
)paren
)paren
id|bank
op_decrement
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|pgtbl_size_ok
c_func
(paren
id|nid
)paren
)paren
(brace
multiline_comment|/* Remove that bank of memory */
multiline_comment|/* Collect some numbers later */
id|printk
c_func
(paren
l_string|&quot;Ignoring node %d bank %d&bslash;n&quot;
comma
id|nid
comma
id|bank
)paren
suffix:semicolon
id|nodemem
(braket
id|nid
)braket
dot
id|hole
(braket
id|bank
op_decrement
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Get to the next populated bank */
r_while
c_loop
(paren
(paren
id|nodemem
(braket
id|nid
)braket
dot
id|hole
(braket
id|bank
)braket
op_eq
op_minus
l_int|1
)paren
op_logical_and
(paren
id|bank
)paren
)paren
id|bank
op_decrement
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Using only upto bank %d on node %d&bslash;n&quot;
comma
id|bank
comma
id|nid
)paren
suffix:semicolon
id|nodemem
(braket
id|nid
)braket
dot
id|end
op_assign
id|nodemem
(braket
id|nid
)braket
dot
id|hole
(braket
id|bank
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bank
)paren
r_break
suffix:semicolon
)brace
)brace
r_void
id|dump_nodemem_map
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DISCONTIGMEM
r_extern
id|bootmem_data_t
id|bdata
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * This assumes there will be a hole in kernel-usable memory between nodes&n; * (due to prom). The memory descriptors invoked via efi_memmap_walk are &n; * in increasing order. It tries to identify first suitable free area to &n; * put the bootmem for the node in. When presented with the md holding&n; * the kernel, it only searches at the end of the kernel area.&n; */
r_static
r_int
id|__init
DECL|function|find_node_bootmem
id|find_node_bootmem
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_void
op_star
id|arg
)paren
(brace
r_int
id|nasid
op_assign
id|GetNasId
c_func
(paren
id|__pa
c_func
(paren
id|start
)paren
)paren
suffix:semicolon
r_int
id|cnodeid
op_assign
id|NASID_TO_CNODEID
c_func
(paren
id|nasid
)paren
suffix:semicolon
r_int
r_int
id|nodesize
suffix:semicolon
r_extern
r_char
id|_end
suffix:semicolon
r_int
r_int
id|kaddr
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_end
suffix:semicolon
multiline_comment|/*&n;&t; * Track memory available to kernel.&n;&t; */
id|nodemem
(braket
id|cnodeid
)braket
dot
id|mtot
op_add_assign
(paren
(paren
id|end
op_minus
id|start
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nodemem
(braket
id|cnodeid
)braket
dot
id|done
op_ne
id|DONE_NOTHING
)paren
r_return
l_int|0
suffix:semicolon
id|nodesize
op_assign
id|nodemem
(braket
id|cnodeid
)braket
dot
id|end
op_minus
(paren
(paren
id|nodemem
(braket
id|cnodeid
)braket
dot
id|start
op_rshift
id|SN1_NODE_ADDR_SHIFT
)paren
op_lshift
id|SN1_NODE_ADDR_SHIFT
)paren
suffix:semicolon
id|nodesize
op_rshift_assign
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/*&n;&t; * Adjust limits for the md holding the kernel.&n;&t; */
r_if
c_cond
(paren
(paren
id|start
OL
id|kaddr
)paren
op_logical_and
(paren
id|end
OG
id|kaddr
)paren
)paren
id|start
op_assign
id|PAGE_ALIGN
c_func
(paren
id|kaddr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We need space for mem_map, bootmem map plus a few more pages&n;&t; * to satisfy alloc_bootmems out of node 0.&n;&t; */
r_if
c_cond
(paren
(paren
id|end
op_minus
id|start
)paren
OG
(paren
(paren
id|nodesize
op_star
r_sizeof
(paren
r_struct
id|page
)paren
)paren
op_plus
(paren
id|nodesize
op_div
l_int|8
)paren
op_plus
(paren
l_int|10
op_star
id|PAGE_SIZE
)paren
)paren
)paren
(brace
id|nodemem
(braket
id|cnodeid
)braket
dot
id|bstart
op_assign
id|start
suffix:semicolon
id|nodemem
(braket
id|cnodeid
)braket
dot
id|done
op_assign
id|DONE_FINDING
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This assumes there will be a hole in kernel-usable memory between nodes&n; * (due to prom). The memory descriptors invoked via efi_memmap_walk are &n; * in increasing order.&n; */
r_static
r_int
id|__init
DECL|function|build_node_bootmem
id|build_node_bootmem
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_void
op_star
id|arg
)paren
(brace
r_int
id|nasid
op_assign
id|GetNasId
c_func
(paren
id|__pa
c_func
(paren
id|start
)paren
)paren
suffix:semicolon
r_int
id|curnodeid
op_assign
id|NASID_TO_CNODEID
c_func
(paren
id|nasid
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|pstart
comma
id|pend
suffix:semicolon
r_extern
r_char
id|_end
comma
id|_stext
suffix:semicolon
r_int
r_int
id|kaddr
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_end
suffix:semicolon
r_if
c_cond
(paren
id|nodemem
(braket
id|curnodeid
)braket
dot
id|done
op_eq
id|DONE_FINDING
)paren
(brace
multiline_comment|/*&n;&t;&t; * This is where we come to know the node is present.&n;&t;&t; * Do node wide tasks.&n;&t;&t; */
id|nodemem
(braket
id|curnodeid
)braket
dot
id|done
op_assign
id|DONE_BUILDING
suffix:semicolon
id|NODE_DATA
c_func
(paren
id|curnodeid
)paren
op_member_access_from_pointer
id|bdata
op_assign
op_amp
(paren
id|bdata
(braket
id|curnodeid
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; &t; * Update the chunktonid array as a node wide task. There&n;&t;&t; * are too many smalls mds on first node to do this per md.&n;&t; &t; */
id|pstart
op_assign
id|__pa
c_func
(paren
id|nodemem
(braket
id|curnodeid
)braket
dot
id|start
)paren
suffix:semicolon
id|pend
op_assign
id|__pa
c_func
(paren
id|nodemem
(braket
id|curnodeid
)braket
dot
id|end
)paren
suffix:semicolon
id|pstart
op_and_assign
id|CHUNKMASK
suffix:semicolon
id|pend
op_assign
(paren
id|pend
op_plus
id|CHUNKSZ
op_minus
l_int|1
)paren
op_amp
id|CHUNKMASK
suffix:semicolon
multiline_comment|/* Possible check point to enforce minimum node size */
r_if
c_cond
(paren
id|nodemem
(braket
id|curnodeid
)braket
dot
id|bstart
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No valid bootmem area on node %d&bslash;n&quot;
comma
id|curnodeid
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
id|PCHUNKNUM
c_func
(paren
id|pstart
)paren
suffix:semicolon
id|i
op_le
id|PCHUNKNUM
c_func
(paren
id|pend
op_minus
l_int|1
)paren
suffix:semicolon
id|i
op_increment
)paren
id|chunktonid
(braket
id|i
)braket
op_assign
id|curnodeid
suffix:semicolon
r_if
c_cond
(paren
(paren
id|CHUNKTONID
c_func
(paren
id|PCHUNKNUM
c_func
(paren
id|pend
)paren
)paren
OG
id|MAXCHUNKS
)paren
op_logical_or
(paren
id|PCHUNKNUM
c_func
(paren
id|pstart
)paren
op_ge
id|PCHUNKNUM
c_func
(paren
id|pend
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Ign 0x%lx-0x%lx, &quot;
comma
id|__pa
c_func
(paren
id|start
)paren
comma
id|__pa
c_func
(paren
id|end
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * NODE_START and NODE_SIZE determine the physical range&n;&t;&t; * on the node that mem_map array needs to be set up for.&n;&t;&t; */
id|NODE_START
c_func
(paren
id|curnodeid
)paren
op_assign
(paren
(paren
id|nodemem
(braket
id|curnodeid
)braket
dot
id|start
op_rshift
id|SN1_NODE_ADDR_SHIFT
)paren
op_lshift
id|SN1_NODE_ADDR_SHIFT
)paren
suffix:semicolon
id|NODE_SIZE
c_func
(paren
id|curnodeid
)paren
op_assign
(paren
id|nodemem
(braket
id|curnodeid
)braket
dot
id|end
op_minus
id|NODE_START
c_func
(paren
id|curnodeid
)paren
)paren
suffix:semicolon
id|nodemem
(braket
id|curnodeid
)braket
dot
id|bsize
op_assign
id|init_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|curnodeid
)paren
comma
(paren
id|__pa
c_func
(paren
id|nodemem
(braket
id|curnodeid
)braket
dot
id|bstart
)paren
op_rshift
id|PAGE_SHIFT
)paren
comma
(paren
id|__pa
c_func
(paren
(paren
id|nodemem
(braket
id|curnodeid
)braket
dot
id|start
op_rshift
id|SN1_NODE_ADDR_SHIFT
)paren
op_lshift
id|SN1_NODE_ADDR_SHIFT
)paren
op_rshift
id|PAGE_SHIFT
)paren
comma
(paren
id|__pa
c_func
(paren
id|nodemem
(braket
id|curnodeid
)braket
dot
id|end
)paren
op_rshift
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nodemem
(braket
id|curnodeid
)braket
dot
id|done
op_eq
id|DONE_NOTHING
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;build_node_bootmem: node %d weirdness&bslash;n&quot;
comma
id|curnodeid
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Paranoia */
)brace
multiline_comment|/*&n;&t; * Free the entire md.&n;&t; */
id|free_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|curnodeid
)paren
comma
id|__pa
c_func
(paren
id|start
)paren
comma
(paren
id|end
op_minus
id|start
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Reclaim back the bootmap and kernel areas.&n;&t; */
r_if
c_cond
(paren
(paren
id|start
op_le
id|nodemem
(braket
id|curnodeid
)braket
dot
id|bstart
)paren
op_logical_and
(paren
id|end
OG
id|nodemem
(braket
id|curnodeid
)braket
dot
id|bstart
)paren
)paren
id|reserve_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|curnodeid
)paren
comma
id|__pa
c_func
(paren
id|nodemem
(braket
id|curnodeid
)braket
dot
id|bstart
)paren
comma
id|nodemem
(braket
id|curnodeid
)braket
dot
id|bsize
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|start
op_le
id|kaddr
)paren
op_logical_and
(paren
id|end
OG
id|kaddr
)paren
)paren
id|reserve_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|curnodeid
)paren
comma
id|__pa
c_func
(paren
op_amp
id|_stext
)paren
comma
(paren
op_amp
id|_end
op_minus
op_amp
id|_stext
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|__init
DECL|function|setup_sn1_bootmem
id|setup_sn1_bootmem
c_func
(paren
r_int
id|maxnodes
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAXNODES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|nodemem
(braket
id|i
)braket
dot
id|start
op_assign
id|nodemem
(braket
id|i
)braket
dot
id|bstart
op_assign
op_minus
l_int|1
suffix:semicolon
id|nodemem
(braket
id|i
)braket
dot
id|end
op_assign
id|nodemem
(braket
id|i
)braket
dot
id|bsize
op_assign
id|nodemem
(braket
id|i
)braket
dot
id|mtot
op_assign
l_int|0
suffix:semicolon
id|nodemem
(braket
id|i
)braket
dot
id|done
op_assign
id|DONE_NOTHING
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|nodemem
(braket
id|i
)braket
dot
id|hole
comma
op_minus
l_int|1
comma
r_sizeof
(paren
id|nodemem
(braket
id|i
)braket
dot
id|hole
)paren
)paren
suffix:semicolon
)brace
id|efi_memmap_walk
c_func
(paren
id|build_nodemem_map
comma
l_int|0
)paren
suffix:semicolon
id|nodemem_valid
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* &n;&t; * After building the nodemem map, check if the node memmap&n;&t; * will fit in the first bank of each node. If not change&n;&t; * the node end addr till it fits.&n; &t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|maxnodes
suffix:semicolon
id|i
op_increment
)paren
id|check_pgtbl_size
c_func
(paren
id|i
)paren
suffix:semicolon
id|dump_nodemem_map
c_func
(paren
id|maxnodes
)paren
suffix:semicolon
id|efi_memmap_walk
c_func
(paren
id|find_node_bootmem
comma
l_int|0
)paren
suffix:semicolon
id|efi_memmap_walk
c_func
(paren
id|build_node_bootmem
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
r_void
id|__init
DECL|function|discontig_paging_init
id|discontig_paging_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|max_dma
comma
id|zones_size
(braket
id|MAX_NR_ZONES
)braket
comma
id|holes_size
(braket
id|MAX_NR_ZONES
)braket
suffix:semicolon
r_extern
r_void
id|dump_node_data
c_func
(paren
r_void
)paren
suffix:semicolon
id|max_dma
op_assign
id|virt_to_phys
c_func
(paren
(paren
r_void
op_star
)paren
id|MAX_DMA_ADDRESS
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|numnodes
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|startpfn
op_assign
id|__pa
c_func
(paren
(paren
r_void
op_star
)paren
id|NODE_START
c_func
(paren
id|i
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_int
r_int
id|numpfn
op_assign
id|NODE_SIZE
c_func
(paren
id|i
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|memset
c_func
(paren
id|zones_size
comma
l_int|0
comma
r_sizeof
(paren
id|zones_size
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|holes_size
comma
l_int|0
comma
r_sizeof
(paren
id|holes_size
)paren
)paren
suffix:semicolon
id|holes_size
(braket
id|ZONE_DMA
)braket
op_assign
id|numpfn
op_minus
id|nodemem
(braket
id|i
)braket
dot
id|mtot
suffix:semicolon
r_if
c_cond
(paren
(paren
id|startpfn
op_plus
id|numpfn
)paren
OL
id|max_dma
)paren
(brace
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
id|numpfn
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|startpfn
OG
id|max_dma
)paren
(brace
id|zones_size
(braket
id|ZONE_NORMAL
)braket
op_assign
id|numpfn
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;discontig_paging_init: %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
r_else
(brace
id|zones_size
(braket
id|ZONE_DMA
)braket
op_assign
(paren
id|max_dma
op_minus
id|startpfn
)paren
suffix:semicolon
id|zones_size
(braket
id|ZONE_NORMAL
)braket
op_assign
id|numpfn
op_minus
id|zones_size
(braket
id|ZONE_DMA
)braket
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;discontig_paging_init: %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
id|free_area_init_node
c_func
(paren
id|i
comma
id|NODE_DATA
c_func
(paren
id|i
)paren
comma
l_int|NULL
comma
id|zones_size
comma
id|startpfn
op_lshift
id|PAGE_SHIFT
comma
id|holes_size
)paren
suffix:semicolon
id|free_unused_memmap_node
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|dump_node_data
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This used to be invoked from an SN1 specific hack in efi_memmap_walk.&n; * It tries to ignore banks which the kernel is ignoring because bank 0 &n; * is too small to hold the memmap entries for this bank.&n; * The current SN1 efi_memmap_walk callbacks do not need this. That &n; * leaves the generic ia64 callbacks find_max_pfn, count_pages and&n; * count_reserved_pages, of which the first can probably get by without&n; * this, the last two probably need this, although they also can probably&n; * get by. &n; */
r_int
DECL|function|sn1_bank_ignore
id|sn1_bank_ignore
c_func
(paren
id|u64
id|start
comma
id|u64
id|end
)paren
(brace
r_int
id|nid
op_assign
id|NASID_TO_CNODEID
c_func
(paren
id|GetNasId
c_func
(paren
id|__pa
c_func
(paren
id|end
)paren
)paren
)paren
suffix:semicolon
r_int
id|bank
op_assign
id|GetBankId
c_func
(paren
id|__pa
c_func
(paren
id|end
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nodemem_valid
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nodemem
(braket
id|nid
)braket
dot
id|hole
(braket
id|bank
)braket
op_eq
op_minus
l_int|1
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|dump_nodemem_map
id|dump_nodemem_map
c_func
(paren
r_int
id|maxnodes
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;NODEMEM_S info ....&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Node         start                end&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|maxnodes
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%d      0x%lx   0x%lx&bslash;n&quot;
comma
id|i
comma
id|nodemem
(braket
id|i
)braket
dot
id|start
comma
id|nodemem
(braket
id|i
)braket
dot
id|end
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Holes -&gt; &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|SN1_MAX_BANK_PER_NODE
suffix:semicolon
id|j
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;0x%lx &quot;
comma
id|nodemem
(braket
id|i
)braket
dot
id|hole
(braket
id|j
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
eof
