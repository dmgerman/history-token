multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/pci_ids.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/hack.h&gt;
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
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xtalkaddrs.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/nodepda.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
macro_line|#include &lt;asm/sn/pci/pci_bus_cvlink.h&gt;
macro_line|#include &lt;asm/sn/simulator.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
r_extern
r_int
id|bridge_rev_b_data_check_disable
suffix:semicolon
DECL|variable|busnum_to_pcibr_vhdl
id|devfs_handle_t
id|busnum_to_pcibr_vhdl
(braket
id|MAX_PCI_XWIDGET
)braket
suffix:semicolon
DECL|variable|busnum_to_nid
id|nasid_t
id|busnum_to_nid
(braket
id|MAX_PCI_XWIDGET
)braket
suffix:semicolon
DECL|variable|busnum_to_atedmamaps
r_void
op_star
id|busnum_to_atedmamaps
(braket
id|MAX_PCI_XWIDGET
)braket
suffix:semicolon
DECL|variable|num_bridges
r_int
r_char
id|num_bridges
suffix:semicolon
DECL|variable|done_probing
r_static
r_int
id|done_probing
op_assign
l_int|0
suffix:semicolon
r_static
r_int
id|pci_bus_map_create
c_func
(paren
id|devfs_handle_t
id|xtalk
comma
r_char
op_star
id|io_moduleid
)paren
suffix:semicolon
id|devfs_handle_t
id|devfn_to_vertex
c_func
(paren
r_int
r_char
id|busnum
comma
r_int
r_int
id|devfn
)paren
suffix:semicolon
r_extern
r_int
r_char
id|Is_pic_on_this_nasid
(braket
l_int|512
)braket
suffix:semicolon
r_extern
r_void
id|sn_init_irq_desc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|register_pcibr_intr
c_func
(paren
r_int
id|irq
comma
id|pcibr_intr_t
id|intr
)paren
suffix:semicolon
multiline_comment|/*&n; * For the given device, initialize whether it is a PIC device.&n; */
r_static
r_void
DECL|function|set_isPIC
id|set_isPIC
c_func
(paren
r_struct
id|sn_device_sysdata
op_star
id|device_sysdata
)paren
(brace
id|pciio_info_t
id|pciio_info
op_assign
id|pciio_info_get
c_func
(paren
id|device_sysdata-&gt;vhdl
)paren
suffix:semicolon
id|pcibr_soft_t
id|pcibr_soft
op_assign
(paren
id|pcibr_soft_t
)paren
id|pciio_info_mfast_get
c_func
(paren
id|pciio_info
)paren
suffix:semicolon
id|device_sysdata-&gt;isPIC
op_assign
id|IS_PIC_SOFT
c_func
(paren
id|pcibr_soft
)paren
suffix:semicolon
suffix:semicolon
)brace
multiline_comment|/*&n; * pci_bus_cvlink_init() - To be called once during initialization before &n; *&t;SGI IO Infrastructure init is called.&n; */
r_void
DECL|function|pci_bus_cvlink_init
id|pci_bus_cvlink_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|ioconfig_bus_init
c_func
(paren
r_void
)paren
suffix:semicolon
id|memset
c_func
(paren
id|busnum_to_pcibr_vhdl
comma
l_int|0x0
comma
r_sizeof
(paren
id|devfs_handle_t
)paren
op_star
id|MAX_PCI_XWIDGET
)paren
suffix:semicolon
id|memset
c_func
(paren
id|busnum_to_nid
comma
l_int|0x0
comma
r_sizeof
(paren
id|nasid_t
)paren
op_star
id|MAX_PCI_XWIDGET
)paren
suffix:semicolon
id|memset
c_func
(paren
id|busnum_to_atedmamaps
comma
l_int|0x0
comma
r_sizeof
(paren
r_void
op_star
)paren
op_star
id|MAX_PCI_XWIDGET
)paren
suffix:semicolon
id|num_bridges
op_assign
l_int|0
suffix:semicolon
id|ioconfig_bus_init
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * pci_bus_to_vertex() - Given a logical Linux Bus Number returns the associated &n; *&t;pci bus vertex from the SGI IO Infrastructure.&n; */
id|devfs_handle_t
DECL|function|pci_bus_to_vertex
id|pci_bus_to_vertex
c_func
(paren
r_int
r_char
id|busnum
)paren
(brace
id|devfs_handle_t
id|pci_bus
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * First get the xwidget vertex.&n;&t; */
id|pci_bus
op_assign
id|busnum_to_pcibr_vhdl
(braket
id|busnum
)braket
suffix:semicolon
r_return
id|pci_bus
suffix:semicolon
)brace
multiline_comment|/*&n; * devfn_to_vertex() - returns the vertex of the device given the bus, slot, &n; *&t;and function numbers.&n; */
id|devfs_handle_t
DECL|function|devfn_to_vertex
id|devfn_to_vertex
c_func
(paren
r_int
r_char
id|busnum
comma
r_int
r_int
id|devfn
)paren
(brace
r_int
id|slot
op_assign
l_int|0
suffix:semicolon
r_int
id|func
op_assign
l_int|0
suffix:semicolon
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
id|devfs_handle_t
id|pci_bus
op_assign
l_int|NULL
suffix:semicolon
id|devfs_handle_t
id|device_vertex
op_assign
(paren
id|devfs_handle_t
)paren
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Go get the pci bus vertex.&n;&t; */
id|pci_bus
op_assign
id|pci_bus_to_vertex
c_func
(paren
id|busnum
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_bus
)paren
(brace
multiline_comment|/*&n;&t;&t; * During probing, the Linux pci code invents non existant&n;&t;&t; * bus numbers and pci_dev structures and tries to access&n;&t;&t; * them to determine existance. Don&squot;t crib during probing.&n;&t;&t; */
r_if
c_cond
(paren
id|done_probing
)paren
id|printk
c_func
(paren
l_string|&quot;devfn_to_vertex: Invalid bus number %d given.&bslash;n&quot;
comma
id|busnum
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Go get the slot&amp;function vertex.&n;&t; * Should call pciio_slot_func_to_name() when ready.&n;&t; */
id|slot
op_assign
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
suffix:semicolon
id|func
op_assign
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * For a NON Multi-function card the name of the device looks like:&n;&t; * ../pci/1, ../pci/2 ..&n;&t; */
r_if
c_cond
(paren
id|func
op_eq
l_int|0
)paren
(brace
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%d&quot;
comma
id|slot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwgraph_traverse
c_func
(paren
id|pci_bus
comma
id|name
comma
op_amp
id|device_vertex
)paren
op_eq
id|GRAPH_SUCCESS
)paren
(brace
r_if
c_cond
(paren
id|device_vertex
)paren
(brace
r_return
id|device_vertex
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;&t; * This maybe a multifunction card.  It&squot;s names look like:&n;&t; * ../pci/1a, ../pci/1b, etc.&n;&t; */
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%d%c&quot;
comma
id|slot
comma
l_char|&squot;a&squot;
op_plus
id|func
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwgraph_traverse
c_func
(paren
id|pci_bus
comma
id|name
comma
op_amp
id|device_vertex
)paren
op_ne
id|GRAPH_SUCCESS
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|device_vertex
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
id|device_vertex
suffix:semicolon
)brace
multiline_comment|/*&n; * For the given device, initialize the addresses for both the Device(x) Flush &n; * Write Buffer register and the Xbow Flush Register for the port the PCI bus &n; * is connected.&n; */
r_static
r_void
DECL|function|set_flush_addresses
id|set_flush_addresses
c_func
(paren
r_struct
id|pci_dev
op_star
id|device_dev
comma
r_struct
id|sn_device_sysdata
op_star
id|device_sysdata
)paren
(brace
id|pciio_info_t
id|pciio_info
op_assign
id|pciio_info_get
c_func
(paren
id|device_sysdata-&gt;vhdl
)paren
suffix:semicolon
id|pciio_slot_t
id|pciio_slot
op_assign
id|pciio_info_slot_get
c_func
(paren
id|pciio_info
)paren
suffix:semicolon
id|pcibr_soft_t
id|pcibr_soft
op_assign
(paren
id|pcibr_soft_t
)paren
id|pciio_info_mfast_get
c_func
(paren
id|pciio_info
)paren
suffix:semicolon
id|bridge_t
op_star
id|bridge
op_assign
id|pcibr_soft-&gt;bs_base
suffix:semicolon
id|nasid_t
id|nasid
suffix:semicolon
multiline_comment|/*&n;&t; * Get the nasid from the bridge.&n;&t; */
id|nasid
op_assign
id|NASID_GET
c_func
(paren
id|device_sysdata-&gt;dma_buf_sync
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_PIC_DEVICE
c_func
(paren
id|device_dev
)paren
)paren
(brace
id|device_sysdata-&gt;dma_buf_sync
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
op_amp
id|bridge-&gt;b_wr_req_buf
(braket
id|pciio_slot
)braket
dot
id|reg
suffix:semicolon
id|device_sysdata-&gt;xbow_buf_sync
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|XBOW_PRIO_LINKREGS_PTR
c_func
(paren
id|NODE_SWIN_BASE
c_func
(paren
id|nasid
comma
l_int|0
)paren
comma
id|pcibr_soft-&gt;bs_xid
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Accessing Xbridge and Xbow register when SHUB swapoper is on!.&n;&t;&t; */
id|device_sysdata-&gt;dma_buf_sync
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
(paren
r_uint64
)paren
op_amp
(paren
id|bridge-&gt;b_wr_req_buf
(braket
id|pciio_slot
)braket
dot
id|reg
)paren
op_xor
l_int|4
)paren
suffix:semicolon
id|device_sysdata-&gt;xbow_buf_sync
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
(paren
r_uint64
)paren
(paren
id|XBOW_PRIO_LINKREGS_PTR
c_func
(paren
id|NODE_SWIN_BASE
c_func
(paren
id|nasid
comma
l_int|0
)paren
comma
id|pcibr_soft-&gt;bs_xid
)paren
)paren
op_xor
l_int|4
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;set_flush_addresses: dma_buf_sync %p xbow_buf_sync %p&bslash;n&quot;
comma
id|device_sysdata-&gt;dma_buf_sync
comma
id|device_sysdata-&gt;xbow_buf_sync
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;set_flush_addresses: dma_buf_sync&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
r_volatile
r_int
r_int
)paren
op_star
id|device_sysdata-&gt;dma_buf_sync
)paren
(brace
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;set_flush_addresses: xbow_buf_sync&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
r_volatile
r_int
r_int
)paren
op_star
id|device_sysdata-&gt;xbow_buf_sync
)paren
(brace
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/*&n; * Most drivers currently do not properly tell the arch specific pci dma&n; * interfaces whether they can handle A64. Here is where we privately&n; * keep track of this.&n; */
r_static
r_void
id|__init
DECL|function|set_sn_pci64
id|set_sn_pci64
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|vendor
op_assign
id|dev-&gt;vendor
suffix:semicolon
r_int
r_int
id|device
op_assign
id|dev-&gt;device
suffix:semicolon
r_if
c_cond
(paren
id|vendor
op_eq
id|PCI_VENDOR_ID_QLOGIC
)paren
(brace
r_if
c_cond
(paren
(paren
id|device
op_eq
id|PCI_DEVICE_ID_QLOGIC_ISP2100
)paren
op_logical_or
(paren
id|device
op_eq
id|PCI_DEVICE_ID_QLOGIC_ISP2200
)paren
)paren
(brace
id|SET_PCIA64
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|vendor
op_eq
id|PCI_VENDOR_ID_SGI
)paren
(brace
r_if
c_cond
(paren
id|device
op_eq
id|PCI_DEVICE_ID_SGI_IOC3
)paren
(brace
id|SET_PCIA64
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * sn_pci_fixup() - This routine is called when platform_pci_fixup() is &n; *&t;invoked at the end of pcibios_init() to link the Linux pci &n; *&t;infrastructure to SGI IO Infrasturcture - ia64/kernel/pci.c&n; *&n; *&t;Other platform specific fixup can also be done here.&n; */
r_void
DECL|function|sn_pci_fixup
id|sn_pci_fixup
c_func
(paren
r_int
id|arg
)paren
(brace
r_struct
id|list_head
op_star
id|ln
suffix:semicolon
r_struct
id|pci_bus
op_star
id|pci_bus
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|pci_dev
op_star
id|device_dev
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|sn_widget_sysdata
op_star
id|widget_sysdata
suffix:semicolon
r_struct
id|sn_device_sysdata
op_star
id|device_sysdata
suffix:semicolon
id|pciio_intr_t
id|intr_handle
suffix:semicolon
r_int
id|cpuid
comma
id|bit
suffix:semicolon
id|devfs_handle_t
id|device_vertex
suffix:semicolon
id|pciio_intr_line_t
id|lines
suffix:semicolon
r_extern
r_void
id|sn_pci_find_bios
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|numnodes
suffix:semicolon
r_int
id|cnode
suffix:semicolon
r_extern
r_void
id|io_sh_swapper
c_func
(paren
r_int
comma
r_int
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
r_if
c_cond
(paren
op_logical_neg
id|Is_pic_on_this_nasid
(braket
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
)braket
)paren
id|io_sh_swapper
c_func
(paren
(paren
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arg
op_eq
l_int|0
)paren
(brace
macro_line|#ifdef CONFIG_PROC_FS
r_extern
r_void
id|register_sn_procfs
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
id|sn_init_irq_desc
c_func
(paren
)paren
suffix:semicolon
id|sn_pci_find_bios
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
r_extern
r_void
id|intr_init_vecblk
c_func
(paren
id|nodepda_t
op_star
id|npda
comma
id|cnodeid_t
comma
r_int
)paren
suffix:semicolon
id|intr_init_vecblk
c_func
(paren
id|NODEPDA
c_func
(paren
id|cnode
)paren
comma
id|cnode
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * When we return to generic Linux, Swapper is always on ..&n;&t;&t; */
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
r_if
c_cond
(paren
op_logical_neg
id|Is_pic_on_this_nasid
(braket
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
)braket
)paren
id|io_sh_swapper
c_func
(paren
(paren
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
id|register_sn_procfs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
)brace
id|done_probing
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the pci bus vertex in the pci_bus struct.&n;&t; */
r_for
c_loop
(paren
id|ln
op_assign
id|pci_root_buses.next
suffix:semicolon
id|ln
op_ne
op_amp
id|pci_root_buses
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
)paren
(brace
id|pci_bus
op_assign
id|pci_bus_b
c_func
(paren
id|ln
)paren
suffix:semicolon
id|widget_sysdata
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sn_widget_sysdata
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|widget_sysdata-&gt;vhdl
op_assign
id|pci_bus_to_vertex
c_func
(paren
id|pci_bus-&gt;number
)paren
suffix:semicolon
id|pci_bus-&gt;sysdata
op_assign
(paren
r_void
op_star
)paren
id|widget_sysdata
suffix:semicolon
)brace
multiline_comment|/*&n; &t; * set the root start and end so that drivers calling check_region()&n;&t; * won&squot;t see a conflict&n;&t; */
id|ioport_resource.start
op_assign
l_int|0xc000000000000000
suffix:semicolon
id|ioport_resource.end
op_assign
l_int|0xcfffffffffffffff
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the device vertex in the pci_dev struct.&n;&t; */
id|pci_for_each_dev
c_func
(paren
id|device_dev
)paren
(brace
r_int
r_int
id|irq
suffix:semicolon
r_int
id|idx
suffix:semicolon
id|u16
id|cmd
suffix:semicolon
id|devfs_handle_t
id|vhdl
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_extern
r_int
id|bit_pos_to_irq
c_func
(paren
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|device_dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_SGI
op_logical_and
id|device_dev-&gt;device
op_eq
id|PCI_DEVICE_ID_SGI_IOC3
)paren
(brace
r_extern
r_void
id|pci_fixup_ioc3
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
suffix:semicolon
id|pci_fixup_ioc3
c_func
(paren
id|device_dev
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the device vertex */
id|device_sysdata
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sn_device_sysdata
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|device_sysdata-&gt;vhdl
op_assign
id|devfn_to_vertex
c_func
(paren
id|device_dev-&gt;bus-&gt;number
comma
id|device_dev-&gt;devfn
)paren
suffix:semicolon
id|device_sysdata-&gt;isa64
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set the xbridge Device(X) Write Buffer Flush and Xbow Flush &n;&t;&t; * register addresses.&n;&t;&t; */
(paren
r_void
)paren
id|set_flush_addresses
c_func
(paren
id|device_dev
comma
id|device_sysdata
)paren
suffix:semicolon
id|device_dev-&gt;sysdata
op_assign
(paren
r_void
op_star
)paren
id|device_sysdata
suffix:semicolon
id|set_sn_pci64
c_func
(paren
id|device_dev
)paren
suffix:semicolon
id|set_isPIC
c_func
(paren
id|device_sysdata
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|device_dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set the resources address correctly.  The assumption here &n;&t;&t; * is that the addresses in the resource structure has been&n;&t;&t; * read from the card and it was set in the card by our&n;&t;&t; * Infrastructure ..&n;&t;&t; */
id|vhdl
op_assign
id|device_sysdata-&gt;vhdl
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|PCI_ROM_RESOURCE
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|size
op_assign
l_int|0
suffix:semicolon
id|size
op_assign
id|device_dev-&gt;resource
(braket
id|idx
)braket
dot
id|end
op_minus
id|device_dev-&gt;resource
(braket
id|idx
)braket
dot
id|start
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
id|device_dev-&gt;resource
(braket
id|idx
)braket
dot
id|start
op_assign
(paren
r_int
r_int
)paren
id|pciio_pio_addr
c_func
(paren
id|vhdl
comma
l_int|0
comma
id|PCIIO_SPACE_WIN
c_func
(paren
id|idx
)paren
comma
l_int|0
comma
id|size
comma
l_int|0
comma
(paren
id|IS_PIC_DEVICE
c_func
(paren
id|device_dev
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
id|PCIIO_BYTE_STREAM
)paren
suffix:semicolon
id|device_dev-&gt;resource
(braket
id|idx
)braket
dot
id|start
op_or_assign
id|__IA64_UNCACHED_OFFSET
suffix:semicolon
)brace
r_else
r_continue
suffix:semicolon
id|device_dev-&gt;resource
(braket
id|idx
)braket
dot
id|end
op_assign
id|device_dev-&gt;resource
(braket
id|idx
)braket
dot
id|start
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|device_dev-&gt;resource
(braket
id|idx
)braket
dot
id|flags
op_amp
id|IORESOURCE_IO
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_IO
suffix:semicolon
r_if
c_cond
(paren
id|device_dev-&gt;resource
(braket
id|idx
)braket
dot
id|flags
op_amp
id|IORESOURCE_MEM
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_MEMORY
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/*&n;&t; * Software WAR for a Software BUG.&n;&t; * This is only temporary.&n;&t; * See PV 872791&n;&t; */
multiline_comment|/*&n;&t;&t; * Now handle the ROM resource ..&n;&t;&t; */
id|size
op_assign
id|device_dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|end
op_minus
id|device_dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
id|device_dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
op_assign
(paren
r_int
r_int
)paren
id|pciio_pio_addr
c_func
(paren
id|vhdl
comma
l_int|0
comma
id|PCIIO_SPACE_ROM
comma
l_int|0
comma
id|size
comma
l_int|0
comma
(paren
id|IS_PIC_DEVICE
c_func
(paren
id|device_dev
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
id|PCIIO_BYTE_STREAM
)paren
suffix:semicolon
id|device_dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
op_or_assign
id|__IA64_UNCACHED_OFFSET
suffix:semicolon
id|device_dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|end
op_assign
id|device_dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
op_plus
id|size
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t;&t; * Update the Command Word on the Card.&n;&t;&t; */
id|cmd
op_or_assign
id|PCI_COMMAND_MASTER
suffix:semicolon
multiline_comment|/* If the device doesn&squot;t support */
multiline_comment|/* bit gets dropped .. no harm */
id|pci_write_config_word
c_func
(paren
id|device_dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|device_dev
comma
id|PCI_INTERRUPT_PIN
comma
(paren
r_int
r_char
op_star
)paren
op_amp
id|lines
)paren
suffix:semicolon
r_if
c_cond
(paren
id|device_dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_SGI
op_logical_and
id|device_dev-&gt;device
op_eq
id|PCI_DEVICE_ID_SGI_IOC3
)paren
(brace
id|lines
op_assign
l_int|1
suffix:semicolon
)brace
id|device_sysdata
op_assign
(paren
r_struct
id|sn_device_sysdata
op_star
)paren
id|device_dev-&gt;sysdata
suffix:semicolon
id|device_vertex
op_assign
id|device_sysdata-&gt;vhdl
suffix:semicolon
id|intr_handle
op_assign
id|pciio_intr_alloc
c_func
(paren
id|device_vertex
comma
l_int|NULL
comma
id|lines
comma
id|device_vertex
)paren
suffix:semicolon
id|bit
op_assign
id|intr_handle-&gt;pi_irq
suffix:semicolon
id|cpuid
op_assign
id|intr_handle-&gt;pi_cpu
suffix:semicolon
id|irq
op_assign
id|bit
suffix:semicolon
id|irq
op_assign
id|irq
op_plus
(paren
id|cpuid
op_lshift
l_int|8
)paren
suffix:semicolon
id|pciio_intr_connect
c_func
(paren
id|intr_handle
comma
(paren
id|intr_func_t
)paren
l_int|0
comma
(paren
id|intr_arg_t
)paren
l_int|0
)paren
suffix:semicolon
id|device_dev-&gt;irq
op_assign
id|irq
suffix:semicolon
id|register_pcibr_intr
c_func
(paren
id|irq
comma
(paren
id|pcibr_intr_t
)paren
id|intr_handle
)paren
suffix:semicolon
macro_line|#ifdef ajmtestintr
(brace
r_int
id|slot
op_assign
id|PCI_SLOT
c_func
(paren
id|device_dev-&gt;devfn
)paren
suffix:semicolon
r_static
r_int
id|timer_set
op_assign
l_int|0
suffix:semicolon
id|pcibr_intr_t
id|pcibr_intr
op_assign
(paren
id|pcibr_intr_t
)paren
id|intr_handle
suffix:semicolon
id|pcibr_soft_t
id|pcibr_soft
op_assign
id|pcibr_intr-&gt;bi_soft
suffix:semicolon
r_extern
r_void
id|intr_test_handle_intr
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|timer_set
)paren
(brace
id|intr_test_set_timer
c_func
(paren
)paren
suffix:semicolon
id|timer_set
op_assign
l_int|1
suffix:semicolon
)brace
id|intr_test_register_irq
c_func
(paren
id|irq
comma
id|pcibr_soft
comma
id|slot
)paren
suffix:semicolon
id|request_irq
c_func
(paren
id|irq
comma
id|intr_test_handle_intr
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
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
r_if
c_cond
(paren
op_logical_neg
id|Is_pic_on_this_nasid
(braket
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
)braket
)paren
id|io_sh_swapper
c_func
(paren
(paren
id|cnodeid_to_nasid
c_func
(paren
id|cnode
)paren
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * linux_bus_cvlink() Creates a link between the Linux PCI Bus number &n; *&t;to the actual hardware component that it represents:&n; *&t;/dev/hw/linux/busnum/0 -&gt; ../../../hw/module/001c01/slab/0/Ibrick/xtalk/15/pci&n; *&n; *&t;The bus vertex, when called to devfs_generate_path() returns:&n; *&t;&t;hw/module/001c01/slab/0/Ibrick/xtalk/15/pci&n; *&t;&t;hw/module/001c01/slab/1/Pbrick/xtalk/12/pci-x/0&n; *&t;&t;hw/module/001c01/slab/1/Pbrick/xtalk/12/pci-x/1&n; */
r_void
DECL|function|linux_bus_cvlink
id|linux_bus_cvlink
c_func
(paren
r_void
)paren
(brace
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
r_int
id|index
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|MAX_PCI_XWIDGET
suffix:semicolon
id|index
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|busnum_to_pcibr_vhdl
(braket
id|index
)braket
)paren
r_continue
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%x&quot;
comma
id|index
)paren
suffix:semicolon
(paren
r_void
)paren
id|hwgraph_edge_add
c_func
(paren
id|linux_busnum
comma
id|busnum_to_pcibr_vhdl
(braket
id|index
)braket
comma
id|name
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * pci_bus_map_create() - Called by pci_bus_to_hcl_cvlink() to finish the job.&n; *&n; *&t;Linux PCI Bus numbers are assigned from lowest module_id numbers&n; *&t;(rack/slot etc.) starting from HUB_WIDGET_ID_MAX down to &n; *&t;HUB_WIDGET_ID_MIN:&n; *&t;&t;widgetnum 15 gets lower Bus Number than widgetnum 14 etc.&n; *&n; *&t;Given 2 modules 001c01 and 001c02 we get the following mappings:&n; *&t;&t;001c01, widgetnum 15 = Bus number 0&n; *&t;&t;001c01, widgetnum 14 = Bus number 1&n; *&t;&t;001c02, widgetnum 15 = Bus number 3&n; *&t;&t;001c02, widgetnum 14 = Bus number 4&n; *&t;&t;etc.&n; *&n; * The rational for starting Bus Number 0 with Widget number 15 is because &n; * the system boot disks are always connected via Widget 15 Slot 0 of the &n; * I-brick.  Linux creates /dev/sd* devices(naming) strating from Bus Number 0 &n; * Therefore, /dev/sda1 will be the first disk, on Widget 15 of the lowest &n; * module id(Master Cnode) of the system.&n; *&t;&n; */
r_static
r_int
DECL|function|pci_bus_map_create
id|pci_bus_map_create
c_func
(paren
id|devfs_handle_t
id|xtalk
comma
r_char
op_star
id|io_moduleid
)paren
(brace
id|devfs_handle_t
id|master_node_vertex
op_assign
l_int|NULL
suffix:semicolon
id|devfs_handle_t
id|xwidget
op_assign
l_int|NULL
suffix:semicolon
id|devfs_handle_t
id|pci_bus
op_assign
l_int|NULL
suffix:semicolon
id|hubinfo_t
id|hubinfo
op_assign
l_int|NULL
suffix:semicolon
id|xwidgetnum_t
id|widgetnum
suffix:semicolon
r_char
id|pathname
(braket
l_int|128
)braket
suffix:semicolon
id|graph_error_t
id|rv
suffix:semicolon
r_int
id|bus
suffix:semicolon
r_int
id|basebus_num
suffix:semicolon
r_int
id|bus_number
suffix:semicolon
multiline_comment|/*&n;&t; * Loop throught this vertex and get the Xwidgets ..&n;&t; */
multiline_comment|/* PCI devices */
r_for
c_loop
(paren
id|widgetnum
op_assign
id|HUB_WIDGET_ID_MAX
suffix:semicolon
id|widgetnum
op_ge
id|HUB_WIDGET_ID_MIN
suffix:semicolon
id|widgetnum
op_decrement
)paren
(brace
id|sprintf
c_func
(paren
id|pathname
comma
l_string|&quot;%d&quot;
comma
id|widgetnum
)paren
suffix:semicolon
id|xwidget
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Example - /hw/module/001c16/Pbrick/xtalk/8 is the xwidget&n;&t;&t; *&t;     /hw/module/001c16/Pbrick/xtalk/8/pci/1 is device&n;&t;&t; */
id|rv
op_assign
id|hwgraph_traverse
c_func
(paren
id|xtalk
comma
id|pathname
comma
op_amp
id|xwidget
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rv
op_ne
id|GRAPH_SUCCESS
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|xwidget
)paren
(brace
r_continue
suffix:semicolon
)brace
)brace
id|sprintf
c_func
(paren
id|pathname
comma
l_string|&quot;%d/&quot;
id|EDGE_LBL_PCI
comma
id|widgetnum
)paren
suffix:semicolon
id|pci_bus
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|hwgraph_traverse
c_func
(paren
id|xtalk
comma
id|pathname
comma
op_amp
id|pci_bus
)paren
op_ne
id|GRAPH_SUCCESS
)paren
r_if
c_cond
(paren
op_logical_neg
id|pci_bus
)paren
(brace
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Assign the correct bus number and also the nasid of this &n;&t;&t; * pci Xwidget.&n;&t;&t; * &n;&t;&t; * Should not be any race here ...&n;&t;&t; */
id|num_bridges
op_increment
suffix:semicolon
id|busnum_to_pcibr_vhdl
(braket
id|num_bridges
op_minus
l_int|1
)braket
op_assign
id|pci_bus
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Get the master node and from there get the NASID.&n;&t;&t; */
id|master_node_vertex
op_assign
id|device_master_get
c_func
(paren
id|xwidget
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|master_node_vertex
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WARNING: pci_bus_map_create: Unable to get .master for vertex 0x%p&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|xwidget
)paren
suffix:semicolon
)brace
id|hubinfo_get
c_func
(paren
id|master_node_vertex
comma
op_amp
id|hubinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hubinfo
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WARNING: pci_bus_map_create: Unable to get hubinfo for master node vertex 0x%p&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|master_node_vertex
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|busnum_to_nid
(braket
id|num_bridges
op_minus
l_int|1
)braket
op_assign
id|hubinfo-&gt;h_nasid
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Pre assign DMA maps needed for 32 Bits Page Map DMA.&n;&t;&t; */
id|busnum_to_atedmamaps
(braket
id|num_bridges
op_minus
l_int|1
)braket
op_assign
(paren
r_void
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sn_dma_maps_s
)paren
op_star
id|MAX_ATE_MAPS
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|busnum_to_atedmamaps
(braket
id|num_bridges
op_minus
l_int|1
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;WARNING: pci_bus_map_create: Unable to precreate ATE DMA Maps for busnum %d vertex 0x%p&bslash;n&quot;
comma
id|num_bridges
op_minus
l_int|1
comma
(paren
r_void
op_star
)paren
id|xwidget
)paren
suffix:semicolon
id|memset
c_func
(paren
id|busnum_to_atedmamaps
(braket
id|num_bridges
op_minus
l_int|1
)braket
comma
l_int|0x0
comma
r_sizeof
(paren
r_struct
id|sn_dma_maps_s
)paren
op_star
id|MAX_ATE_MAPS
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * PCIX devices&n;&t; * We number busses differently for PCI-X devices.&n;&t; * We start from Lowest Widget on up ..&n;&t; */
(paren
r_void
)paren
id|ioconfig_get_busnum
c_func
(paren
(paren
r_char
op_star
)paren
id|io_moduleid
comma
op_amp
id|basebus_num
)paren
suffix:semicolon
r_for
c_loop
(paren
id|widgetnum
op_assign
id|HUB_WIDGET_ID_MIN
suffix:semicolon
id|widgetnum
op_le
id|HUB_WIDGET_ID_MAX
suffix:semicolon
id|widgetnum
op_increment
)paren
(brace
multiline_comment|/* Do both buses */
r_for
c_loop
(paren
id|bus
op_assign
l_int|0
suffix:semicolon
id|bus
OL
l_int|2
suffix:semicolon
id|bus
op_increment
)paren
(brace
id|sprintf
c_func
(paren
id|pathname
comma
l_string|&quot;%d&quot;
comma
id|widgetnum
)paren
suffix:semicolon
id|xwidget
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Example - /hw/module/001c16/Pbrick/xtalk/8 is the xwidget&n;&t;&t;&t; *&t;     /hw/module/001c16/Pbrick/xtalk/8/pci-x/0 is the bus&n;&t;&t;&t; *&t;     /hw/module/001c16/Pbrick/xtalk/8/pci-x/0/1 is device&n;&t;&t;&t; */
id|rv
op_assign
id|hwgraph_traverse
c_func
(paren
id|xtalk
comma
id|pathname
comma
op_amp
id|xwidget
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rv
op_ne
id|GRAPH_SUCCESS
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|xwidget
)paren
(brace
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|bus
op_eq
l_int|0
)paren
id|sprintf
c_func
(paren
id|pathname
comma
l_string|&quot;%d/&quot;
id|EDGE_LBL_PCIX_0
comma
id|widgetnum
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|pathname
comma
l_string|&quot;%d/&quot;
id|EDGE_LBL_PCIX_1
comma
id|widgetnum
)paren
suffix:semicolon
id|pci_bus
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|hwgraph_traverse
c_func
(paren
id|xtalk
comma
id|pathname
comma
op_amp
id|pci_bus
)paren
op_ne
id|GRAPH_SUCCESS
)paren
r_if
c_cond
(paren
op_logical_neg
id|pci_bus
)paren
(brace
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Assign the correct bus number and also the nasid of this &n;&t;&t;&t; * pci Xwidget.&n;&t;&t;&t; * &n;&t;&t;&t; * Should not be any race here ...&n;&t;&t;&t; */
id|bus_number
op_assign
id|basebus_num
op_plus
id|bus
op_plus
id|io_brick_map_widget
c_func
(paren
id|MODULE_PXBRICK
comma
id|widgetnum
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;bus_number %d basebus_num %d bus %d io %d&bslash;n&quot;
comma
id|bus_number
comma
id|basebus_num
comma
id|bus
comma
id|io_brick_map_widget
c_func
(paren
id|MODULE_PXBRICK
comma
id|widgetnum
)paren
)paren
suffix:semicolon
macro_line|#endif
id|busnum_to_pcibr_vhdl
(braket
id|bus_number
)braket
op_assign
id|pci_bus
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Pre assign DMA maps needed for 32 Bits Page Map DMA.&n;&t;&t;&t; */
id|busnum_to_atedmamaps
(braket
id|bus_number
)braket
op_assign
(paren
r_void
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sn_dma_maps_s
)paren
op_star
id|MAX_ATE_MAPS
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|busnum_to_atedmamaps
(braket
id|bus_number
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;WARNING: pci_bus_map_create: Unable to precreate ATE DMA Maps for busnum %d vertex 0x%p&bslash;n&quot;
comma
id|num_bridges
op_minus
l_int|1
comma
(paren
r_void
op_star
)paren
id|xwidget
)paren
suffix:semicolon
id|memset
c_func
(paren
id|busnum_to_atedmamaps
(braket
id|bus_number
)braket
comma
l_int|0x0
comma
r_sizeof
(paren
r_struct
id|sn_dma_maps_s
)paren
op_star
id|MAX_ATE_MAPS
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * pci_bus_to_hcl_cvlink() - This routine is called after SGI IO Infrastructure   &n; *      initialization has completed to set up the mappings between Xbridge&n; *      and logical pci bus numbers.  We also set up the NASID for each of these&n; *      xbridges.&n; *&n; *      Must be called before pci_init() is invoked.&n; */
r_int
DECL|function|pci_bus_to_hcl_cvlink
id|pci_bus_to_hcl_cvlink
c_func
(paren
r_void
)paren
(brace
id|devfs_handle_t
id|devfs_hdl
op_assign
l_int|NULL
suffix:semicolon
id|devfs_handle_t
id|xtalk
op_assign
l_int|NULL
suffix:semicolon
r_int
id|rv
op_assign
l_int|0
suffix:semicolon
r_char
id|name
(braket
l_int|256
)braket
suffix:semicolon
r_char
id|tmp_name
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|i
comma
id|ii
suffix:semicolon
multiline_comment|/*&n;&t; * Figure out which IO Brick is connected to the Compute Bricks.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nummodules
suffix:semicolon
id|i
op_increment
)paren
(brace
r_extern
r_int
id|iomoduleid_get
c_func
(paren
id|nasid_t
)paren
suffix:semicolon
id|moduleid_t
id|iobrick_id
suffix:semicolon
id|nasid_t
id|nasid
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|nodecnt
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
id|nodecnt
op_assign
id|modules
(braket
id|i
)braket
op_member_access_from_pointer
id|nodecnt
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|nodecnt
suffix:semicolon
id|n
op_increment
)paren
(brace
id|nasid
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|modules
(braket
id|i
)braket
op_member_access_from_pointer
id|nodes
(braket
id|n
)braket
)paren
suffix:semicolon
id|iobrick_id
op_assign
id|iomoduleid_get
c_func
(paren
id|nasid
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|iobrick_id
OG
l_int|0
)paren
(brace
multiline_comment|/* Valid module id */
r_char
id|name
(braket
l_int|12
)braket
suffix:semicolon
id|memset
c_func
(paren
id|name
comma
l_int|0
comma
l_int|12
)paren
suffix:semicolon
id|format_module_id
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
(paren
id|modules
(braket
id|i
)braket
op_member_access_from_pointer
id|io
(braket
id|n
)braket
dot
id|moduleid
)paren
comma
id|iobrick_id
comma
id|MODULE_FORMAT_BRIEF
)paren
suffix:semicolon
)brace
)brace
)brace
id|devfs_hdl
op_assign
id|hwgraph_path_to_vertex
c_func
(paren
l_string|&quot;/dev/hw/module&quot;
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
id|nummodules
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|ii
op_assign
l_int|0
suffix:semicolon
id|ii
OL
l_int|2
suffix:semicolon
id|ii
op_increment
)paren
(brace
id|memset
c_func
(paren
id|name
comma
l_int|0
comma
l_int|256
)paren
suffix:semicolon
id|memset
c_func
(paren
id|tmp_name
comma
l_int|0
comma
l_int|256
)paren
suffix:semicolon
id|format_module_id
c_func
(paren
id|name
comma
id|modules
(braket
id|i
)braket
op_member_access_from_pointer
id|id
comma
id|MODULE_FORMAT_BRIEF
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|tmp_name
comma
l_string|&quot;/slab/%d/Pbrick/xtalk&quot;
comma
id|geo_slab
c_func
(paren
id|modules
(braket
id|i
)braket
op_member_access_from_pointer
id|geoid
(braket
id|ii
)braket
)paren
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|name
comma
id|tmp_name
)paren
suffix:semicolon
id|xtalk
op_assign
l_int|NULL
suffix:semicolon
id|rv
op_assign
id|hwgraph_edge_get
c_func
(paren
id|devfs_hdl
comma
id|name
comma
op_amp
id|xtalk
)paren
suffix:semicolon
id|pci_bus_map_create
c_func
(paren
id|xtalk
comma
(paren
r_char
op_star
)paren
op_amp
(paren
id|modules
(braket
id|i
)braket
op_member_access_from_pointer
id|io
(braket
id|ii
)braket
dot
id|moduleid
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Create the Linux PCI bus number vertex link.&n;&t; */
(paren
r_void
)paren
id|linux_bus_cvlink
c_func
(paren
)paren
suffix:semicolon
(paren
r_void
)paren
id|ioconfig_bus_new_entries
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
