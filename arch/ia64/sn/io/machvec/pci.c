multiline_comment|/* &n; *&n; * SNI64 specific PCI support for SNI IO.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1997, 1998, 2000-2003 Silicon Graphics, Inc.  All rights reserved.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/driver.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/sn/pio.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xwidget.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/hcl_util.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
macro_line|#include &lt;asm/sn/pci/bridge.h&gt;
multiline_comment|/*&n; * These routines are only used during sn_pci_init for probing each bus, and&n; * can probably be removed with a little more cleanup now that the SAL routines&n; * work on sn2.&n; */
macro_line|#ifdef CONFIG_PCI
r_extern
id|vertex_hdl_t
id|devfn_to_vertex
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|devfn
)paren
suffix:semicolon
DECL|function|sn_read_config
r_int
id|sn_read_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
op_star
id|val
)paren
(brace
r_int
r_int
id|res
op_assign
l_int|0
suffix:semicolon
id|vertex_hdl_t
id|device_vertex
suffix:semicolon
id|device_vertex
op_assign
id|devfn_to_vertex
c_func
(paren
id|bus-&gt;number
comma
id|devfn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device_vertex
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|res
op_assign
id|pciio_config_get
c_func
(paren
id|device_vertex
comma
(paren
r_int
)paren
id|where
comma
id|size
)paren
suffix:semicolon
op_star
id|val
op_assign
(paren
id|u32
)paren
id|res
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|sn_write_config
r_int
id|sn_write_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
id|val
)paren
(brace
id|vertex_hdl_t
id|device_vertex
suffix:semicolon
id|device_vertex
op_assign
id|devfn_to_vertex
c_func
(paren
id|bus-&gt;number
comma
id|devfn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device_vertex
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|pciio_config_set
c_func
(paren
id|device_vertex
comma
(paren
r_int
)paren
id|where
comma
id|size
comma
(paren
r_uint64
)paren
id|val
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|sn_pci_ops
r_struct
id|pci_ops
id|sn_pci_ops
op_assign
(brace
dot
id|read
op_assign
id|sn_read_config
comma
dot
id|write
op_assign
id|sn_write_config
comma
)brace
suffix:semicolon
macro_line|#else
DECL|variable|pci_root_buses
r_struct
id|list_head
id|pci_root_buses
suffix:semicolon
DECL|variable|pci_root_buses
r_struct
id|list_head
id|pci_root_buses
suffix:semicolon
DECL|variable|pci_devices
r_struct
id|list_head
id|pci_devices
suffix:semicolon
macro_line|#endif /* CONFIG_PCI */
eof
