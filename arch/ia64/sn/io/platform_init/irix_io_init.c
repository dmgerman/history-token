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
macro_line|#include &lt;asm/sn/simulator.h&gt;
r_extern
r_void
id|init_all_devices
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
id|vertex_hdl_t
)paren
suffix:semicolon
r_extern
r_void
id|klhwg_add_all_nodes
c_func
(paren
id|vertex_hdl_t
)paren
suffix:semicolon
r_extern
id|vertex_hdl_t
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
r_int
id|pci_bus_to_hcl_cvlink
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mlreset
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
multiline_comment|/*&n; * This routine is responsible for the setup of all the IRIX hwgraph style&n; * stuff that&squot;s been pulled into linux.  It&squot;s called by sn_pci_find_bios which&n; * is called just before the generic Linux PCI layer does its probing (by &n; * platform_pci_fixup aka sn_pci_fixup).&n; *&n; * It is very IMPORTANT that this call is only made by the Master CPU!&n; *&n; */
r_void
DECL|function|irix_io_init
id|irix_io_init
c_func
(paren
r_void
)paren
(brace
id|cnodeid_t
id|cnode
suffix:semicolon
multiline_comment|/*&n;&t; * This is the Master CPU.  Emulate mlsetup and main.c in Irix.&n;&t; */
id|mlreset
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;         * Initialize platform-dependent vertices in the hwgraph:&n;         *      module&n;         *      node&n;         *      cpu&n;         *      memory&n;         *      slot&n;         *      hub&n;         *      router&n;         *      xbow&n;         */
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
r_extern
r_void
id|per_hub_init
c_func
(paren
id|cnodeid_t
)paren
suffix:semicolon
id|per_hub_init
c_func
(paren
id|cnode
)paren
suffix:semicolon
)brace
multiline_comment|/* We can do headless hub cnodes here .. */
multiline_comment|/*&n;&t; *&n;&t; * Our IO Infrastructure drivers are in place .. &n;&t; * Initialize the whole IO Infrastructure .. xwidget/device probes.&n;&t; *&n;&t; */
id|init_all_devices
c_func
(paren
)paren
suffix:semicolon
id|pci_bus_to_hcl_cvlink
c_func
(paren
)paren
suffix:semicolon
)brace
eof
