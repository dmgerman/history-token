multiline_comment|/*&n; * Ported from IRIX to Linux by Kanoj Sarcar, 06/08/00.&n; * Copyright 2000 - 2001 Silicon Graphics, Inc.&n; * Copyright 2000 - 2001 Kanoj Sarcar (kanoj@sgi.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/gda.h&gt;
macro_line|#include &lt;asm/sn/hub.h&gt;
macro_line|#include &lt;asm/sn/mapped_kernel.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
r_extern
r_char
id|_end
suffix:semicolon
DECL|variable|ktext_repmask
r_static
id|cpumask_t
id|ktext_repmask
suffix:semicolon
multiline_comment|/*&n; * XXX - This needs to be much smarter about where it puts copies of the&n; * kernel.  For example, we should never put a copy on a headless node,&n; * and we should respect the topology of the machine.&n; */
DECL|function|setup_replication_mask
r_void
id|__init
id|setup_replication_mask
c_func
(paren
r_int
id|maxnodes
)paren
(brace
r_static
r_int
id|numa_kernel_replication_ratio
suffix:semicolon
id|cnodeid_t
id|cnode
suffix:semicolon
multiline_comment|/* Set only the master cnode&squot;s bit.  The master cnode is always 0. */
id|cpus_clear
c_func
(paren
id|ktext_repmask
)paren
suffix:semicolon
id|cpu_set
c_func
(paren
l_int|0
comma
id|ktext_repmask
)paren
suffix:semicolon
id|numa_kernel_replication_ratio
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_REPLICATE_KTEXT
macro_line|#ifndef CONFIG_MAPPED_KERNEL
macro_line|#error Kernel replication works with mapped kernel support. No calias support.
macro_line|#endif
id|numa_kernel_replication_ratio
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|cnode
op_assign
l_int|1
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
multiline_comment|/* See if this node should get a copy of the kernel */
r_if
c_cond
(paren
id|numa_kernel_replication_ratio
op_logical_and
op_logical_neg
(paren
id|cnode
op_mod
id|numa_kernel_replication_ratio
)paren
)paren
(brace
multiline_comment|/* Advertise that we have a copy of the kernel */
id|cpu_set
c_func
(paren
id|cnode
comma
id|ktext_repmask
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Set up a GDA pointer to the replication mask. */
id|GDA-&gt;g_ktext_repmask
op_assign
op_amp
id|ktext_repmask
suffix:semicolon
)brace
DECL|function|set_ktext_source
r_static
id|__init
r_void
id|set_ktext_source
c_func
(paren
id|nasid_t
id|client_nasid
comma
id|nasid_t
id|server_nasid
)paren
(brace
id|cnodeid_t
id|client_cnode
suffix:semicolon
id|kern_vars_t
op_star
id|kvp
suffix:semicolon
id|client_cnode
op_assign
id|NASID_TO_COMPACT_NODEID
c_func
(paren
id|client_nasid
)paren
suffix:semicolon
id|kvp
op_assign
op_amp
id|hub_data
c_func
(paren
id|client_nasid
)paren
op_member_access_from_pointer
id|kern_vars
suffix:semicolon
id|KERN_VARS_ADDR
c_func
(paren
id|client_nasid
)paren
op_assign
(paren
r_int
r_int
)paren
id|kvp
suffix:semicolon
id|kvp-&gt;kv_magic
op_assign
id|KV_MAGIC
suffix:semicolon
id|kvp-&gt;kv_ro_nasid
op_assign
id|server_nasid
suffix:semicolon
id|kvp-&gt;kv_rw_nasid
op_assign
id|master_nasid
suffix:semicolon
id|kvp-&gt;kv_ro_baseaddr
op_assign
id|NODE_CAC_BASE
c_func
(paren
id|server_nasid
)paren
suffix:semicolon
id|kvp-&gt;kv_rw_baseaddr
op_assign
id|NODE_CAC_BASE
c_func
(paren
id|master_nasid
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;REPLICATION: ON nasid %d, ktext from nasid %d, kdata from nasid %d&bslash;n&quot;
comma
id|client_nasid
comma
id|server_nasid
comma
id|master_nasid
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX - When the BTE works, we should use it instead of this. */
DECL|function|copy_kernel
r_static
id|__init
r_void
id|copy_kernel
c_func
(paren
id|nasid_t
id|dest_nasid
)paren
(brace
r_int
r_int
id|dest_kern_start
comma
id|source_start
comma
id|source_end
comma
id|kern_size
suffix:semicolon
id|source_start
op_assign
(paren
r_int
r_int
)paren
id|_stext
suffix:semicolon
id|source_end
op_assign
(paren
r_int
r_int
)paren
id|_etext
suffix:semicolon
id|kern_size
op_assign
id|source_end
op_minus
id|source_start
suffix:semicolon
id|dest_kern_start
op_assign
id|CHANGE_ADDR_NASID
c_func
(paren
id|MAPPED_KERN_RO_TO_K0
c_func
(paren
id|source_start
)paren
comma
id|dest_nasid
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|dest_kern_start
comma
(paren
r_void
op_star
)paren
id|source_start
comma
id|kern_size
)paren
suffix:semicolon
)brace
DECL|function|replicate_kernel_text
r_void
id|__init
id|replicate_kernel_text
c_func
(paren
r_int
id|maxnodes
)paren
(brace
id|cnodeid_t
id|cnode
suffix:semicolon
id|nasid_t
id|client_nasid
suffix:semicolon
id|nasid_t
id|server_nasid
suffix:semicolon
id|server_nasid
op_assign
id|master_nasid
suffix:semicolon
multiline_comment|/* Record where the master node should get its kernel text */
id|set_ktext_source
c_func
(paren
id|master_nasid
comma
id|master_nasid
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cnode
op_assign
l_int|1
suffix:semicolon
id|cnode
OL
id|maxnodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
id|client_nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
suffix:semicolon
multiline_comment|/* Check if this node should get a copy of the kernel */
r_if
c_cond
(paren
id|cpu_isset
c_func
(paren
id|cnode
comma
id|ktext_repmask
)paren
)paren
(brace
id|server_nasid
op_assign
id|client_nasid
suffix:semicolon
id|copy_kernel
c_func
(paren
id|server_nasid
)paren
suffix:semicolon
)brace
multiline_comment|/* Record where this node should get its kernel text */
id|set_ktext_source
c_func
(paren
id|client_nasid
comma
id|server_nasid
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Return pfn of first free page of memory on a node. PROM may allocate&n; * data structures on the first couple of pages of the first slot of each&n; * node. If this is the case, getfirstfree(node) &gt; getslotstart(node, 0).&n; */
DECL|function|node_getfirstfree
id|pfn_t
id|node_getfirstfree
c_func
(paren
id|cnodeid_t
id|cnode
)paren
(brace
r_int
r_int
id|loadbase
op_assign
id|CKSEG0
suffix:semicolon
id|nasid_t
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
macro_line|#ifdef CONFIG_MAPPED_KERNEL
id|loadbase
op_assign
id|CKSSEG
op_plus
l_int|16777216
suffix:semicolon
macro_line|#endif
id|offset
op_assign
id|PAGE_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|_end
)paren
)paren
op_minus
id|loadbase
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cnode
op_eq
l_int|0
)paren
op_logical_or
(paren
id|cpu_isset
c_func
(paren
id|cnode
comma
id|ktext_repmask
)paren
)paren
)paren
r_return
(paren
id|TO_NODE
c_func
(paren
id|nasid
comma
id|offset
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_else
r_return
(paren
id|KDM_TO_PHYS
c_func
(paren
id|PAGE_ALIGN
c_func
(paren
id|SYMMON_STK_ADDR
c_func
(paren
id|nasid
comma
l_int|0
)paren
)paren
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
eof
