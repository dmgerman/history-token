multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/pci/pciba.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
r_extern
r_void
id|mlreset
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|init_hcl
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|klgraph_hack_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|hubspc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pciio_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pcibr_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|xtalk_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|xbow_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|xbmon_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pciiox_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pic_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|usrpci_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ioc3_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|initialize_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|klhwg_add_all_modules
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
r_extern
r_void
id|klhwg_add_all_nodes
c_func
(paren
id|devfs_handle_t
)paren
suffix:semicolon
r_void
id|sn_mp_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|devfs_handle_t
id|hwgraph_root
suffix:semicolon
r_extern
r_void
id|io_module_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pci_bus_cvlink_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|temp_hack
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pci_bus_to_hcl_cvlink
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* #define DEBUG_IO_INIT 1 */
macro_line|#ifdef DEBUG_IO_INIT
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif /* DEBUG_IO_INIT */
multiline_comment|/*&n; * per_hub_init&n; *&n; * &t;This code is executed once for each Hub chip.&n; */
r_static
r_void
DECL|function|per_hub_init
id|per_hub_init
c_func
(paren
id|cnodeid_t
id|cnode
)paren
(brace
id|nasid_t
id|nasid
suffix:semicolon
id|nodepda_t
op_star
id|npdap
suffix:semicolon
id|ii_icmr_u_t
id|ii_icmr
suffix:semicolon
id|ii_ibcr_u_t
id|ii_ibcr
suffix:semicolon
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|nasid
op_ne
id|INVALID_NASID
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|NASID_TO_COMPACT_NODEID
c_func
(paren
id|nasid
)paren
op_eq
id|cnode
)paren
suffix:semicolon
id|npdap
op_assign
id|NODEPDA
c_func
(paren
id|cnode
)paren
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_IWEIM
comma
l_int|0x8000
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the total number of CRBs that can be used.&n;&t; */
id|ii_icmr.ii_icmr_regval
op_assign
l_int|0x0
suffix:semicolon
id|ii_icmr.ii_icmr_fld_s.i_c_cnt
op_assign
l_int|0xf
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_ICMR
comma
id|ii_icmr.ii_icmr_regval
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the number of CRBs that both of the BTEs combined&n;&t; * can use minus 1.&n;&t; */
id|ii_ibcr.ii_ibcr_regval
op_assign
l_int|0x0
suffix:semicolon
id|ii_ibcr.ii_ibcr_fld_s.i_count
op_assign
l_int|0x8
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_IBCR
comma
id|ii_ibcr.ii_ibcr_regval
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set CRB timeout to be 10ms.&n;&t; */
macro_line|#ifdef BRINGUP2
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_ICTP
comma
l_int|0xffffff
)paren
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_ICTO
comma
l_int|0xff
)paren
suffix:semicolon
singleline_comment|//REMOTE_HUB_S(nasid, IIO_IWI, 0x00FF00FF00FFFFFF);
macro_line|#endif
multiline_comment|/* Initialize error interrupts for this hub. */
id|hub_error_init
c_func
(paren
id|cnode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine is responsible for the setup of all the IRIX hwgraph style&n; * stuff that&squot;s been pulled into linux.  It&squot;s called by sn_pci_find_bios which&n; * is called just before the generic Linux PCI layer does its probing (by &n; * platform_pci_fixup aka sn_pci_fixup).&n; *&n; * It is very IMPORTANT that this call is only made by the Master CPU!&n; *&n; */
r_void
DECL|function|sgi_master_io_infr_init
id|sgi_master_io_infr_init
c_func
(paren
r_void
)paren
(brace
r_int
id|cnode
suffix:semicolon
r_extern
r_void
id|kdba_io_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Do any early init stuff .. einit_tbl[] etc.&n;&t; */
id|init_hcl
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Sets up the hwgraph compatibility layer with devfs */
multiline_comment|/*&n;&t; * initialize the Linux PCI to xwidget vertexes ..&n;&t; */
id|pci_bus_cvlink_init
c_func
(paren
)paren
suffix:semicolon
id|kdba_io_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef BRINGUP
multiline_comment|/*&n;&t; * Hack to provide statically initialzed klgraph entries.&n;&t; */
id|DBG
c_func
(paren
l_string|&quot;--&gt; sgi_master_io_infr_init: calling klgraph_hack_init()&bslash;n&quot;
)paren
suffix:semicolon
id|klgraph_hack_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif /* BRINGUP */
multiline_comment|/*&n;&t; * This is the Master CPU.  Emulate mlsetup and main.c in Irix.&n;&t; */
id|mlreset
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * allowboot() is called by kern/os/main.c in main()&n;&t; * Emulate allowboot() ...&n;&t; *   per_cpu_init() - only need per_hub_init()&n;&t; *   cpu_io_setup() - Nothing to do.&n;&t; * &n;&t; */
id|sn_mp_setup
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
id|per_hub_init
c_func
(paren
id|cnode
)paren
suffix:semicolon
)brace
multiline_comment|/* We can do headless hub cnodes here .. */
multiline_comment|/*&n;&t; * io_init[] stuff.&n;&t; *&n;&t; * Get SGI IO Infrastructure drivers to init and register with &n;&t; * each other etc.&n;&t; */
id|hubspc_init
c_func
(paren
)paren
suffix:semicolon
id|pciio_init
c_func
(paren
)paren
suffix:semicolon
id|pcibr_init
c_func
(paren
)paren
suffix:semicolon
id|pic_init
c_func
(paren
)paren
suffix:semicolon
id|xtalk_init
c_func
(paren
)paren
suffix:semicolon
id|xbow_init
c_func
(paren
)paren
suffix:semicolon
id|xbmon_init
c_func
(paren
)paren
suffix:semicolon
id|pciiox_init
c_func
(paren
)paren
suffix:semicolon
id|usrpci_init
c_func
(paren
)paren
suffix:semicolon
id|ioc3_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&n;&t; * Our IO Infrastructure drivers are in place .. &n;&t; * Initialize the whole IO Infrastructure .. xwidget/device probes.&n;&t; *&n;&t; */
id|initialize_io
c_func
(paren
)paren
suffix:semicolon
id|pci_bus_to_hcl_cvlink
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCIBA
id|DBG
c_func
(paren
l_string|&quot;--&gt; sgi_master_io_infr_init: calling pciba_init()&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifndef BRINGUP2
id|pciba_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
)brace
multiline_comment|/*&n; * One-time setup for MP SN.&n; * Allocate per-node data, slurp prom klconfig information and&n; * convert it to hwgraph information.&n; */
r_void
DECL|function|sn_mp_setup
id|sn_mp_setup
c_func
(paren
r_void
)paren
(brace
id|cpuid_t
id|cpu
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
(brace
multiline_comment|/* Skip holes in CPU space */
r_if
c_cond
(paren
id|cpu_enabled
c_func
(paren
id|cpu
)paren
)paren
(brace
id|init_platform_pda
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Initialize platform-dependent vertices in the hwgraph:&n;&t; *&t;module&n;&t; *&t;node&n;&t; *&t;cpu&n;&t; *&t;memory&n;&t; *&t;slot&n;&t; *&t;hub&n;&t; *&t;router&n;&t; *&t;xbow&n;&t; */
id|io_module_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Use to be called module_init() .. */
id|klhwg_add_all_modules
c_func
(paren
id|hwgraph_root
)paren
suffix:semicolon
id|klhwg_add_all_nodes
c_func
(paren
id|hwgraph_root
)paren
suffix:semicolon
)brace
eof
