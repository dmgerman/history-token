multiline_comment|/*&n; * numa.c - Low-level PCI access for NUMA-Q machines&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|macro|BUS2QUAD
mdefine_line|#define BUS2QUAD(global) (mp_bus_id_to_node[global])
DECL|macro|BUS2LOCAL
mdefine_line|#define BUS2LOCAL(global) (mp_bus_id_to_local[global])
DECL|macro|QUADLOCAL2BUS
mdefine_line|#define QUADLOCAL2BUS(quad,local) (quad_local_to_mp_bus_id[quad][local])
DECL|macro|PCI_CONF1_MQ_ADDRESS
mdefine_line|#define PCI_CONF1_MQ_ADDRESS(bus, dev, fn, reg) &bslash;&n;&t;(0x80000000 | (BUS2LOCAL(bus) &lt;&lt; 16) | (dev &lt;&lt; 11) | (fn &lt;&lt; 8) | (reg &amp; ~3))
DECL|function|__pci_conf1_mq_read
r_static
r_int
id|__pci_conf1_mq_read
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|dev
comma
r_int
id|fn
comma
r_int
id|reg
comma
r_int
id|len
comma
id|u32
op_star
id|value
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|value
op_logical_or
(paren
id|bus
OG
l_int|255
)paren
op_logical_or
(paren
id|dev
OG
l_int|31
)paren
op_logical_or
(paren
id|fn
OG
l_int|7
)paren
op_logical_or
(paren
id|reg
OG
l_int|255
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
id|outl_quad
c_func
(paren
id|PCI_CONF1_MQ_ADDRESS
c_func
(paren
id|bus
comma
id|dev
comma
id|fn
comma
id|reg
)paren
comma
l_int|0xCF8
comma
id|BUS2QUAD
c_func
(paren
id|bus
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
id|value
op_assign
id|inb_quad
c_func
(paren
l_int|0xCFC
op_plus
(paren
id|reg
op_amp
l_int|3
)paren
comma
id|BUS2QUAD
c_func
(paren
id|bus
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|value
op_assign
id|inw_quad
c_func
(paren
l_int|0xCFC
op_plus
(paren
id|reg
op_amp
l_int|2
)paren
comma
id|BUS2QUAD
c_func
(paren
id|bus
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
id|value
op_assign
id|inl_quad
c_func
(paren
l_int|0xCFC
comma
id|BUS2QUAD
c_func
(paren
id|bus
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__pci_conf1_mq_write
r_static
r_int
id|__pci_conf1_mq_write
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|dev
comma
r_int
id|fn
comma
r_int
id|reg
comma
r_int
id|len
comma
id|u32
id|value
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
OG
l_int|255
)paren
op_logical_or
(paren
id|dev
OG
l_int|31
)paren
op_logical_or
(paren
id|fn
OG
l_int|7
)paren
op_logical_or
(paren
id|reg
OG
l_int|255
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
id|outl_quad
c_func
(paren
id|PCI_CONF1_MQ_ADDRESS
c_func
(paren
id|bus
comma
id|dev
comma
id|fn
comma
id|reg
)paren
comma
l_int|0xCF8
comma
id|BUS2QUAD
c_func
(paren
id|bus
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
id|outb_quad
c_func
(paren
(paren
id|u8
)paren
id|value
comma
l_int|0xCFC
op_plus
(paren
id|reg
op_amp
l_int|3
)paren
comma
id|BUS2QUAD
c_func
(paren
id|bus
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|outw_quad
c_func
(paren
(paren
id|u16
)paren
id|value
comma
l_int|0xCFC
op_plus
(paren
id|reg
op_amp
l_int|2
)paren
comma
id|BUS2QUAD
c_func
(paren
id|bus
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|outl_quad
c_func
(paren
(paren
id|u32
)paren
id|value
comma
l_int|0xCFC
comma
id|BUS2QUAD
c_func
(paren
id|bus
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pci_config_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|PCI_CONF1_MQ_ADDRESS
macro_line|#undef PCI_CONF1_MQ_ADDRESS
DECL|function|pci_conf1_mq_read
r_static
r_int
id|pci_conf1_mq_read
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
id|value
)paren
(brace
r_return
id|__pci_conf1_mq_read
c_func
(paren
l_int|0
comma
id|bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
comma
id|where
comma
id|size
comma
id|value
)paren
suffix:semicolon
)brace
DECL|function|pci_conf1_mq_write
r_static
r_int
id|pci_conf1_mq_write
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
id|value
)paren
(brace
r_return
id|__pci_conf1_mq_write
c_func
(paren
l_int|0
comma
id|bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
comma
id|where
comma
id|size
comma
id|value
)paren
suffix:semicolon
)brace
DECL|variable|pci_direct_conf1_mq
r_static
r_struct
id|pci_ops
id|pci_direct_conf1_mq
op_assign
(brace
dot
id|read
op_assign
id|pci_conf1_mq_read
comma
dot
id|write
op_assign
id|pci_conf1_mq_write
)brace
suffix:semicolon
DECL|function|pci_fixup_i450nx
r_static
r_void
id|__devinit
id|pci_fixup_i450nx
c_func
(paren
r_struct
id|pci_dev
op_star
id|d
)paren
(brace
multiline_comment|/*&n;&t; * i450NX -- Find and scan all secondary buses on all PXB&squot;s.&n;&t; */
r_int
id|pxb
comma
id|reg
suffix:semicolon
id|u8
id|busno
comma
id|suba
comma
id|subb
suffix:semicolon
r_int
id|quad
op_assign
id|BUS2QUAD
c_func
(paren
id|d-&gt;bus-&gt;number
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: Searching for i450NX host bridges on %s&bslash;n&quot;
comma
id|d-&gt;slot_name
)paren
suffix:semicolon
id|reg
op_assign
l_int|0xd0
suffix:semicolon
r_for
c_loop
(paren
id|pxb
op_assign
l_int|0
suffix:semicolon
id|pxb
OL
l_int|2
suffix:semicolon
id|pxb
op_increment
)paren
(brace
id|pci_read_config_byte
c_func
(paren
id|d
comma
id|reg
op_increment
comma
op_amp
id|busno
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|d
comma
id|reg
op_increment
comma
op_amp
id|suba
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|d
comma
id|reg
op_increment
comma
op_amp
id|subb
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;i450NX PXB %d: %02x/%02x/%02x&bslash;n&quot;
comma
id|pxb
comma
id|busno
comma
id|suba
comma
id|subb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|busno
)paren
id|pci_scan_bus
c_func
(paren
id|QUADLOCAL2BUS
c_func
(paren
id|quad
comma
id|busno
)paren
comma
id|pci_root_ops
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Bus A */
r_if
c_cond
(paren
id|suba
OL
id|subb
)paren
id|pci_scan_bus
c_func
(paren
id|QUADLOCAL2BUS
c_func
(paren
id|quad
comma
id|suba
op_plus
l_int|1
)paren
comma
id|pci_root_ops
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Bus B */
)brace
id|pcibios_last_bus
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82451NX
comma
id|pci_fixup_i450nx
)brace
comma
)brace
suffix:semicolon
DECL|function|pci_numa_init
r_static
r_int
id|__init
id|pci_numa_init
c_func
(paren
r_void
)paren
(brace
r_int
id|quad
suffix:semicolon
id|pci_root_ops
op_assign
op_amp
id|pci_direct_conf1_mq
suffix:semicolon
r_if
c_cond
(paren
id|pcibios_scanned
op_increment
)paren
r_return
l_int|0
suffix:semicolon
id|pci_root_bus
op_assign
id|pcibios_scan_root
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clustered_apic_mode
op_logical_and
(paren
id|numnodes
OG
l_int|1
)paren
)paren
(brace
r_for
c_loop
(paren
id|quad
op_assign
l_int|1
suffix:semicolon
id|quad
OL
id|numnodes
suffix:semicolon
op_increment
id|quad
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Scanning PCI bus %d for quad %d&bslash;n&quot;
comma
id|QUADLOCAL2BUS
c_func
(paren
id|quad
comma
l_int|0
)paren
comma
id|quad
)paren
suffix:semicolon
id|pci_scan_bus
c_func
(paren
id|QUADLOCAL2BUS
c_func
(paren
id|quad
comma
l_int|0
)paren
comma
id|pci_root_ops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pci_numa_init
id|subsys_initcall
c_func
(paren
id|pci_numa_init
)paren
suffix:semicolon
eof
