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
macro_line|#ifdef DEBUG_CONFIG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
macro_line|#ifdef CONFIG_PCI
r_extern
id|vertex_hdl_t
id|pci_bus_to_vertex
c_func
(paren
r_int
r_char
)paren
suffix:semicolon
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
r_int
r_int
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
)brace
suffix:semicolon
multiline_comment|/*&n; * sn_pci_find_bios - SNIA64 pci_find_bios() platform specific code.&n; */
r_void
id|__init
DECL|function|sn_pci_find_bios
id|sn_pci_find_bios
c_func
(paren
r_void
)paren
(brace
r_extern
r_struct
id|pci_ops
op_star
id|pci_root_ops
suffix:semicolon
multiline_comment|/*&n;&t; * Go initialize our IO Infrastructure ..&n;&t; */
r_extern
r_void
id|sgi_master_io_infr_init
c_func
(paren
r_void
)paren
suffix:semicolon
id|sgi_master_io_infr_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* sn_io_infrastructure_init(); */
id|pci_root_ops
op_assign
op_amp
id|sn_pci_ops
suffix:semicolon
)brace
r_void
DECL|function|pci_fixup_ioc3
id|pci_fixup_ioc3
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* IOC3 only decodes 0x20 bytes of the config space, reading&n;&t; * beyond that is relatively benign but writing beyond that&n;&t; * (especially the base address registers) will shut down the&n;&t; * pci bus...so avoid doing so.&n;&t; * NOTE: this means we can&squot;t program the intr_pin into the device,&n;&t; *       currently we hack this with special code in &n;&t; *&t; sgi_pci_intr_support()&n;&t; */
id|DBG
c_func
(paren
l_string|&quot;pci_fixup_ioc3: Fixing base addresses for ioc3 device %s&bslash;n&quot;
comma
id|d-&gt;slot_name
)paren
suffix:semicolon
multiline_comment|/* I happen to know from the spec that the ioc3 needs only 0xfffff &n;&t; * The standard pci trick of writing ~0 to the baddr and seeing&n;&t; * what comes back doesn&squot;t work with the ioc3&n;&t; */
id|size
op_assign
l_int|0xfffff
suffix:semicolon
id|d-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_assign
(paren
r_int
r_int
)paren
id|d-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_plus
(paren
r_int
r_int
)paren
id|size
suffix:semicolon
multiline_comment|/*&n;&t; * Zero out the resource structure .. because we did not go through &n;&t; * the normal PCI Infrastructure Init, garbbage are left in these &n;&t; * fileds.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|PCI_ROM_RESOURCE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|d-&gt;resource
(braket
id|i
)braket
dot
id|start
op_assign
l_int|0UL
suffix:semicolon
id|d-&gt;resource
(braket
id|i
)braket
dot
id|end
op_assign
l_int|0UL
suffix:semicolon
id|d-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_assign
l_int|0UL
suffix:semicolon
)brace
id|d-&gt;subsystem_vendor
op_assign
l_int|0
suffix:semicolon
id|d-&gt;subsystem_device
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|function|sn_pci_find_bios
r_void
id|sn_pci_find_bios
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|pci_fixup_ioc3
r_void
id|pci_fixup_ioc3
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
)brace
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
