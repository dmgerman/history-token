multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
r_extern
id|cpuid_t
id|master_procid
suffix:semicolon
DECL|variable|maxcpus
r_int
id|maxcpus
suffix:semicolon
r_extern
id|xwidgetnum_t
id|hub_widget_id
c_func
(paren
id|nasid_t
)paren
suffix:semicolon
r_extern
r_void
id|iograph_early_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|master_nasid
id|nasid_t
id|master_nasid
op_assign
id|INVALID_NASID
suffix:semicolon
multiline_comment|/* This is the partition master nasid */
DECL|variable|master_baseio_nasid
id|nasid_t
id|master_baseio_nasid
op_assign
id|INVALID_NASID
suffix:semicolon
multiline_comment|/* This is the master base I/O nasid */
multiline_comment|/*&n; * mlreset(void)&n; * &t;very early machine reset - at this point NO interrupts have been&n; * &t;enabled; nor is memory, tlb, p0, etc setup.&n; *&n; * &t;slave is zero when mlreset is called for the master processor and&n; *&t;is nonzero thereafter.&n; */
r_void
DECL|function|mlreset
id|mlreset
c_func
(paren
r_int
id|slave
)paren
(brace
multiline_comment|/*&n;&t; * We are the master cpu and node.&n;&t; */
id|master_nasid
op_assign
id|get_nasid
c_func
(paren
)paren
suffix:semicolon
id|set_master_bridge_base
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We&squot;re the master processor */
id|master_procid
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|master_nasid
op_assign
id|cpuid_to_nasid
c_func
(paren
id|master_procid
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * master_nasid we get back better be same as one from&n;&t; * get_nasid()&n;&t; */
id|ASSERT_ALWAYS
c_func
(paren
id|master_nasid
op_eq
id|get_nasid
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* early initialization of iograph */
id|iograph_early_init
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* XXX - Move the meat of this to intr.c ? */
multiline_comment|/*&n; * Set up the platform-dependent fields in the nodepda.&n; */
DECL|function|init_platform_nodepda
r_void
id|init_platform_nodepda
c_func
(paren
id|nodepda_t
op_star
id|npda
comma
id|cnodeid_t
id|node
)paren
(brace
id|hubinfo_t
id|hubinfo
suffix:semicolon
r_extern
r_void
id|router_map_init
c_func
(paren
id|nodepda_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|router_queue_init
c_func
(paren
id|nodepda_t
op_star
comma
id|cnodeid_t
)paren
suffix:semicolon
r_extern
r_void
id|intr_init_vecblk
c_func
(paren
id|nodepda_t
op_star
comma
id|cnodeid_t
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Allocate per-node platform-dependent data */
id|hubinfo
op_assign
(paren
id|hubinfo_t
)paren
id|alloc_bootmem_node
c_func
(paren
id|NODE_DATA
c_func
(paren
id|node
)paren
comma
r_sizeof
(paren
r_struct
id|hubinfo_s
)paren
)paren
suffix:semicolon
id|npda-&gt;pdinfo
op_assign
(paren
r_void
op_star
)paren
id|hubinfo
suffix:semicolon
id|hubinfo-&gt;h_nodepda
op_assign
id|npda
suffix:semicolon
id|hubinfo-&gt;h_cnodeid
op_assign
id|node
suffix:semicolon
id|hubinfo-&gt;h_nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|node
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|hubinfo-&gt;h_crblock
)paren
suffix:semicolon
id|hubinfo-&gt;h_widgetid
op_assign
id|hub_widget_id
c_func
(paren
id|hubinfo-&gt;h_nasid
)paren
suffix:semicolon
id|npda-&gt;xbow_peer
op_assign
id|INVALID_NASID
suffix:semicolon
multiline_comment|/* &n;&t; * Initialize the linked list of&n;&t; * router info pointers to the dependent routers&n;&t; */
id|npda-&gt;npda_rip_first
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * npda_rip_last always points to the place&n;&t; * where the next element is to be inserted&n;&t; * into the list &n;&t; */
id|npda-&gt;npda_rip_last
op_assign
op_amp
id|npda-&gt;npda_rip_first
suffix:semicolon
id|npda-&gt;geoid.any.type
op_assign
id|GEO_TYPE_INVALID
suffix:semicolon
id|mutex_init_locked
c_func
(paren
op_amp
id|npda-&gt;xbow_sema
)paren
suffix:semicolon
multiline_comment|/* init it locked? */
)brace
r_void
DECL|function|update_node_information
id|update_node_information
c_func
(paren
id|cnodeid_t
id|cnodeid
)paren
(brace
id|nodepda_t
op_star
id|npda
op_assign
id|NODEPDA
c_func
(paren
id|cnodeid
)paren
suffix:semicolon
id|nodepda_router_info_t
op_star
id|npda_rip
suffix:semicolon
multiline_comment|/* Go through the list of router info &n;&t; * structures and copy some frequently&n;&t; * accessed info from the info hanging&n;&t; * off the corresponding router vertices&n;&t; */
id|npda_rip
op_assign
id|npda-&gt;npda_rip_first
suffix:semicolon
r_while
c_loop
(paren
id|npda_rip
)paren
(brace
r_if
c_cond
(paren
id|npda_rip-&gt;router_infop
)paren
(brace
id|npda_rip-&gt;router_portmask
op_assign
id|npda_rip-&gt;router_infop-&gt;ri_portmask
suffix:semicolon
id|npda_rip-&gt;router_slot
op_assign
id|npda_rip-&gt;router_infop-&gt;ri_slotnum
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* No router, no ports. */
id|npda_rip-&gt;router_portmask
op_assign
l_int|0
suffix:semicolon
)brace
id|npda_rip
op_assign
id|npda_rip-&gt;router_next
suffix:semicolon
)brace
)brace
eof
