multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/pci.c&n; *&n; * Extruded from code written by&n; *&t;Dave Rusling (david.rusling@reo.mts.dec.com)&n; *&t;David Mosberger (davidm@cs.arizona.edu)&n; */
multiline_comment|/* 2.3.x PCI/resources, 1999 Andrea Arcangeli &lt;andrea@suse.de&gt; */
multiline_comment|/*&n; * Nov 2000, Ivan Kokshaysky &lt;ink@jurassic.park.msu.ru&gt;&n; *&t;     PCI-PCI bridges cleanup&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
multiline_comment|/*&n; * Some string constants used by the various core logics. &n; */
DECL|variable|pci_io_names
r_const
r_char
op_star
r_const
id|pci_io_names
(braket
)braket
op_assign
(brace
l_string|&quot;PCI IO bus 0&quot;
comma
l_string|&quot;PCI IO bus 1&quot;
comma
l_string|&quot;PCI IO bus 2&quot;
comma
l_string|&quot;PCI IO bus 3&quot;
comma
l_string|&quot;PCI IO bus 4&quot;
comma
l_string|&quot;PCI IO bus 5&quot;
comma
l_string|&quot;PCI IO bus 6&quot;
comma
l_string|&quot;PCI IO bus 7&quot;
)brace
suffix:semicolon
DECL|variable|pci_mem_names
r_const
r_char
op_star
r_const
id|pci_mem_names
(braket
)braket
op_assign
(brace
l_string|&quot;PCI mem bus 0&quot;
comma
l_string|&quot;PCI mem bus 1&quot;
comma
l_string|&quot;PCI mem bus 2&quot;
comma
l_string|&quot;PCI mem bus 3&quot;
comma
l_string|&quot;PCI mem bus 4&quot;
comma
l_string|&quot;PCI mem bus 5&quot;
comma
l_string|&quot;PCI mem bus 6&quot;
comma
l_string|&quot;PCI mem bus 7&quot;
)brace
suffix:semicolon
DECL|variable|pci_hae0_name
r_const
r_char
id|pci_hae0_name
(braket
)braket
op_assign
l_string|&quot;HAE0&quot;
suffix:semicolon
multiline_comment|/*&n; * The PCI controller list.&n; */
DECL|variable|hose_head
DECL|variable|hose_tail
r_struct
id|pci_controller
op_star
id|hose_head
comma
op_star
op_star
id|hose_tail
op_assign
op_amp
id|hose_head
suffix:semicolon
DECL|variable|pci_isa_hose
r_struct
id|pci_controller
op_star
id|pci_isa_hose
suffix:semicolon
multiline_comment|/*&n; * Quirks.&n; */
r_static
r_void
id|__init
DECL|function|quirk_eisa_bridge
id|quirk_eisa_bridge
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|dev
op_member_access_from_pointer
r_class
op_assign
id|PCI_CLASS_BRIDGE_EISA
op_lshift
l_int|8
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|quirk_isa_bridge
id|quirk_isa_bridge
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|dev
op_member_access_from_pointer
r_class
op_assign
id|PCI_CLASS_BRIDGE_ISA
op_lshift
l_int|8
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|quirk_ali_ide_ports
id|quirk_ali_ide_ports
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_eq
l_int|0xffff
)paren
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_assign
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_plus
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
l_int|2
)braket
dot
id|end
op_eq
l_int|0xffff
)paren
id|dev-&gt;resource
(braket
l_int|2
)braket
dot
id|end
op_assign
id|dev-&gt;resource
(braket
l_int|2
)braket
dot
id|start
op_plus
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
l_int|3
)braket
dot
id|end
op_eq
l_int|0xffff
)paren
id|dev-&gt;resource
(braket
l_int|3
)braket
dot
id|end
op_assign
id|dev-&gt;resource
(braket
l_int|3
)braket
dot
id|start
op_plus
l_int|7
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|quirk_cypress
id|quirk_cypress
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* The Notorious Cy82C693 chip.  */
multiline_comment|/* The Cypress IDE controller doesn&squot;t support native mode, but it&n;&t;   has programmable addresses of IDE command/control registers.&n;&t;   This violates PCI specifications, confuses the IDE subsystem and&n;&t;   causes resource conflicts between the primary HD_CMD register and&n;&t;   the floppy controller.  Ugh.  Fix that.  */
r_if
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
op_eq
id|PCI_CLASS_STORAGE_IDE
)paren
(brace
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|flags
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|1
)braket
dot
id|flags
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* The Cypress bridge responds on the PCI bus in the address range&n;&t;   0xffff0000-0xffffffff (conventional x86 BIOS ROM).  There is no&n;&t;   way to turn this off.  The bridge also supports several extended&n;&t;   BIOS ranges (disabled after power-up), and some consoles do turn&n;&t;   them on.  So if we use a large direct-map window, or a large SG&n;&t;   window, we must avoid entire 0xfff00000-0xffffffff region.  */
r_else
r_if
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
op_eq
id|PCI_CLASS_BRIDGE_ISA
)paren
(brace
r_if
c_cond
(paren
id|__direct_map_base
op_plus
id|__direct_map_size
op_ge
l_int|0xfff00000
)paren
id|__direct_map_size
op_assign
l_int|0xfff00000
op_minus
id|__direct_map_base
suffix:semicolon
r_else
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|dev-&gt;sysdata
suffix:semicolon
r_struct
id|pci_iommu_arena
op_star
id|pci
op_assign
id|hose-&gt;sg_pci
suffix:semicolon
r_if
c_cond
(paren
id|pci
op_logical_and
id|pci-&gt;dma_base
op_plus
id|pci-&gt;size
op_ge
l_int|0xfff00000
)paren
id|pci-&gt;size
op_assign
l_int|0xfff00000
op_minus
id|pci-&gt;dma_base
suffix:semicolon
)brace
)brace
)brace
DECL|variable|__initdata
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82375
comma
id|quirk_eisa_bridge
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82378
comma
id|quirk_isa_bridge
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_AL
comma
id|PCI_DEVICE_ID_AL_M5229
comma
id|quirk_ali_ide_ports
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_CONTAQ
comma
id|PCI_DEVICE_ID_CONTAQ_82C693
comma
id|quirk_cypress
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|MAX
mdefine_line|#define MAX(val1, val2)&t;&t;((val1) &gt; (val2) ? (val1) : (val2))
DECL|macro|ALIGN
mdefine_line|#define ALIGN(val,align)&t;(((val) + ((align) - 1)) &amp; ~((align) - 1))
DECL|macro|KB
mdefine_line|#define KB&t;&t;&t;1024
DECL|macro|MB
mdefine_line|#define MB&t;&t;&t;(1024*KB)
DECL|macro|GB
mdefine_line|#define GB&t;&t;&t;(1024*MB)
r_void
DECL|function|pcibios_align_resource
id|pcibios_align_resource
c_func
(paren
r_void
op_star
id|data
comma
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|size
comma
r_int
r_int
id|align
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|data
suffix:semicolon
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|dev-&gt;sysdata
suffix:semicolon
r_int
r_int
id|alignto
suffix:semicolon
r_int
r_int
id|start
op_assign
id|res-&gt;start
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
(brace
multiline_comment|/* Make sure we start at our min on all hoses */
r_if
c_cond
(paren
id|start
op_minus
id|hose-&gt;io_space-&gt;start
OL
id|PCIBIOS_MIN_IO
)paren
id|start
op_assign
id|PCIBIOS_MIN_IO
op_plus
id|hose-&gt;io_space-&gt;start
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Put everything into 0x00-0xff region modulo 0x400&n;&t;&t; */
r_if
c_cond
(paren
id|start
op_amp
l_int|0x300
)paren
id|start
op_assign
(paren
id|start
op_plus
l_int|0x3ff
)paren
op_amp
op_complement
l_int|0x3ff
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
(brace
multiline_comment|/* Make sure we start at our min on all hoses */
r_if
c_cond
(paren
id|start
op_minus
id|hose-&gt;mem_space-&gt;start
OL
id|PCIBIOS_MIN_MEM
)paren
id|start
op_assign
id|PCIBIOS_MIN_MEM
op_plus
id|hose-&gt;mem_space-&gt;start
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The following holds at least for the Low Cost&n;&t;&t; * Alpha implementation of the PCI interface:&n;&t;&t; *&n;&t;&t; * In sparse memory address space, the first&n;&t;&t; * octant (16MB) of every 128MB segment is&n;&t;&t; * aliased to the very first 16 MB of the&n;&t;&t; * address space (i.e., it aliases the ISA&n;&t;&t; * memory address space).  Thus, we try to&n;&t;&t; * avoid allocating PCI devices in that range.&n;&t;&t; * Can be allocated in 2nd-7th octant only.&n;&t;&t; * Devices that need more than 112MB of&n;&t;&t; * address space must be accessed through&n;&t;&t; * dense memory space only!&n;&t;&t; */
multiline_comment|/* Align to multiple of size of minimum base.  */
id|alignto
op_assign
id|MAX
c_func
(paren
l_int|0x1000
comma
id|align
)paren
suffix:semicolon
id|start
op_assign
id|ALIGN
c_func
(paren
id|start
comma
id|alignto
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hose-&gt;sparse_mem_base
op_logical_and
id|size
op_le
l_int|7
op_star
l_int|16
op_star
id|MB
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|start
op_div
(paren
l_int|16
op_star
id|MB
)paren
)paren
op_amp
l_int|0x7
)paren
op_eq
l_int|0
)paren
(brace
id|start
op_and_assign
op_complement
(paren
l_int|128
op_star
id|MB
op_minus
l_int|1
)paren
suffix:semicolon
id|start
op_add_assign
l_int|16
op_star
id|MB
suffix:semicolon
id|start
op_assign
id|ALIGN
c_func
(paren
id|start
comma
id|alignto
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|start
op_div
(paren
l_int|128
op_star
id|MB
)paren
op_ne
(paren
id|start
op_plus
id|size
op_minus
l_int|1
)paren
op_div
(paren
l_int|128
op_star
id|MB
)paren
)paren
(brace
id|start
op_and_assign
op_complement
(paren
l_int|128
op_star
id|MB
op_minus
l_int|1
)paren
suffix:semicolon
id|start
op_add_assign
(paren
l_int|128
op_plus
l_int|16
)paren
op_star
id|MB
suffix:semicolon
id|start
op_assign
id|ALIGN
c_func
(paren
id|start
comma
id|alignto
)paren
suffix:semicolon
)brace
)brace
)brace
id|res-&gt;start
op_assign
id|start
suffix:semicolon
)brace
DECL|macro|MAX
macro_line|#undef MAX
DECL|macro|ALIGN
macro_line|#undef ALIGN
DECL|macro|KB
macro_line|#undef KB
DECL|macro|MB
macro_line|#undef MB
DECL|macro|GB
macro_line|#undef GB
r_static
r_void
id|__init
DECL|function|pcibios_init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|alpha_mv.init_pci
)paren
r_return
suffix:semicolon
id|alpha_mv
dot
id|init_pci
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|pcibios_init
id|subsys_initcall
c_func
(paren
id|pcibios_init
)paren
suffix:semicolon
r_char
op_star
id|__init
DECL|function|pcibios_setup
id|pcibios_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_return
id|str
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pcibios_fixup_resource
id|pcibios_fixup_resource
c_func
(paren
r_struct
id|resource
op_star
id|res
comma
r_struct
id|resource
op_star
id|root
)paren
(brace
id|res-&gt;start
op_add_assign
id|root-&gt;start
suffix:semicolon
id|res-&gt;end
op_add_assign
id|root-&gt;start
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pcibios_fixup_device_resources
id|pcibios_fixup_device_resources
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
multiline_comment|/* Update device resources.  */
r_struct
id|pci_controller
op_star
id|hose
op_assign
(paren
r_struct
id|pci_controller
op_star
)paren
id|bus-&gt;sysdata
suffix:semicolon
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
id|PCI_NUM_RESOURCES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_amp
id|IORESOURCE_IO
)paren
id|pcibios_fixup_resource
c_func
(paren
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
comma
id|hose-&gt;io_space
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_amp
id|IORESOURCE_MEM
)paren
id|pcibios_fixup_resource
c_func
(paren
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
comma
id|hose-&gt;mem_space
)paren
suffix:semicolon
)brace
)brace
r_void
id|__init
DECL|function|pcibios_fixup_bus
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
multiline_comment|/* Propogate hose info into the subordinate devices.  */
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|bus-&gt;sysdata
suffix:semicolon
r_struct
id|list_head
op_star
id|ln
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|bus-&gt;self
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
multiline_comment|/* Root bus */
id|bus-&gt;resource
(braket
l_int|0
)braket
op_assign
id|hose-&gt;io_space
suffix:semicolon
id|bus-&gt;resource
(braket
l_int|1
)braket
op_assign
id|hose-&gt;mem_space
suffix:semicolon
)brace
r_for
c_loop
(paren
id|ln
op_assign
id|bus-&gt;devices.next
suffix:semicolon
id|ln
op_ne
op_amp
id|bus-&gt;devices
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|pci_dev_b
c_func
(paren
id|ln
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_ne
id|PCI_CLASS_BRIDGE_PCI
)paren
id|pcibios_fixup_device_resources
c_func
(paren
id|dev
comma
id|bus
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|pcibios_update_resource
id|pcibios_update_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
id|res
comma
r_int
id|resource
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|dev-&gt;sysdata
suffix:semicolon
r_int
id|where
suffix:semicolon
id|u32
id|reg
suffix:semicolon
r_if
c_cond
(paren
id|resource
OL
id|PCI_ROM_RESOURCE
)paren
id|where
op_assign
id|PCI_BASE_ADDRESS_0
op_plus
(paren
id|resource
op_star
l_int|4
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|resource
op_eq
id|PCI_ROM_RESOURCE
)paren
id|where
op_assign
id|dev-&gt;rom_base_reg
suffix:semicolon
r_else
(brace
r_return
suffix:semicolon
multiline_comment|/* Don&squot;t update non-standard resources here. */
)brace
multiline_comment|/* Point root at the hose root. */
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|root
op_assign
id|hose-&gt;io_space
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
id|root
op_assign
id|hose-&gt;mem_space
suffix:semicolon
id|reg
op_assign
(paren
id|res-&gt;start
op_minus
id|root-&gt;start
)paren
op_or
(paren
id|res-&gt;flags
op_amp
l_int|0xf
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|where
comma
id|reg
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|res-&gt;flags
op_amp
(paren
id|PCI_BASE_ADDRESS_SPACE
op_or
id|PCI_BASE_ADDRESS_MEM_TYPE_MASK
)paren
)paren
op_eq
(paren
id|PCI_BASE_ADDRESS_SPACE_MEMORY
op_or
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
)paren
(brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|where
op_plus
l_int|4
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: dev %s type 64-bit&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/* ??? FIXME -- record old value for shutdown.  */
)brace
r_void
id|__init
DECL|function|pcibios_update_irq
id|pcibios_update_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|irq
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* ??? FIXME -- record old value for shutdown.  */
)brace
multiline_comment|/* Most Alphas have straight-forward swizzling needs.  */
id|u8
id|__init
DECL|function|common_swizzle
id|common_swizzle
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
op_star
id|pinp
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|dev-&gt;sysdata
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_ne
id|hose-&gt;first_busno
)paren
(brace
id|u8
id|pin
op_assign
op_star
id|pinp
suffix:semicolon
r_do
(brace
id|pin
op_assign
id|bridge_swizzle
c_func
(paren
id|pin
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
multiline_comment|/* Move up the chain of bridges. */
id|dev
op_assign
id|dev-&gt;bus-&gt;self
suffix:semicolon
)brace
r_while
c_loop
(paren
id|dev-&gt;bus-&gt;self
)paren
suffix:semicolon
op_star
id|pinp
op_assign
id|pin
suffix:semicolon
multiline_comment|/* The slot is the slot of the last bridge. */
)brace
r_return
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|pcibios_fixup_pbus_ranges
id|pcibios_fixup_pbus_ranges
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_struct
id|pbus_set_ranges_data
op_star
id|ranges
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
(paren
r_struct
id|pci_controller
op_star
)paren
id|bus-&gt;sysdata
suffix:semicolon
id|ranges-&gt;io_start
op_sub_assign
id|hose-&gt;io_space-&gt;start
suffix:semicolon
id|ranges-&gt;io_end
op_sub_assign
id|hose-&gt;io_space-&gt;start
suffix:semicolon
id|ranges-&gt;mem_start
op_sub_assign
id|hose-&gt;mem_space-&gt;start
suffix:semicolon
id|ranges-&gt;mem_end
op_sub_assign
id|hose-&gt;mem_space-&gt;start
suffix:semicolon
multiline_comment|/* FIXME: On older alphas we could use dense memory space&n;&t;  to access prefetchable resources. */
id|ranges-&gt;prefetch_start
op_sub_assign
id|hose-&gt;mem_space-&gt;start
suffix:semicolon
id|ranges-&gt;prefetch_end
op_sub_assign
id|hose-&gt;mem_space-&gt;start
suffix:semicolon
)brace
r_int
DECL|function|pcibios_enable_device
id|pcibios_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* Nothing to do, since we enable all devices at startup.  */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  If we set up a device for bus mastering, we need to check the latency&n; *  timer as certain firmware forgets to set it properly, as seen&n; *  on SX164 and LX164 with SRM.&n; */
r_void
DECL|function|pcibios_set_master
id|pcibios_set_master
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u8
id|lat
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
op_amp
id|lat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lat
op_ge
l_int|16
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: Setting latency timer of device %s to 64&bslash;n&quot;
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
l_int|64
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|common_init_pci
id|common_init_pci
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
r_int
id|next_busno
suffix:semicolon
multiline_comment|/* Scan all of the recorded PCI controllers.  */
r_for
c_loop
(paren
id|next_busno
op_assign
l_int|0
comma
id|hose
op_assign
id|hose_head
suffix:semicolon
id|hose
suffix:semicolon
id|hose
op_assign
id|hose-&gt;next
)paren
(brace
id|hose-&gt;first_busno
op_assign
id|next_busno
suffix:semicolon
id|hose-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
id|bus
op_assign
id|pci_scan_bus
c_func
(paren
id|next_busno
comma
id|alpha_mv.pci_ops
comma
id|hose
)paren
suffix:semicolon
id|hose-&gt;bus
op_assign
id|bus
suffix:semicolon
id|next_busno
op_assign
id|hose-&gt;last_busno
op_assign
id|bus-&gt;subordinate
suffix:semicolon
id|next_busno
op_add_assign
l_int|1
suffix:semicolon
)brace
id|pci_assign_unassigned_resources
c_func
(paren
)paren
suffix:semicolon
id|pci_fixup_irqs
c_func
(paren
id|alpha_mv.pci_swizzle
comma
id|alpha_mv.pci_map_irq
)paren
suffix:semicolon
)brace
r_struct
id|pci_controller
op_star
id|__init
DECL|function|alloc_pci_controller
id|alloc_pci_controller
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
id|hose
op_assign
id|alloc_bootmem
c_func
(paren
r_sizeof
(paren
op_star
id|hose
)paren
)paren
suffix:semicolon
op_star
id|hose_tail
op_assign
id|hose
suffix:semicolon
id|hose_tail
op_assign
op_amp
id|hose-&gt;next
suffix:semicolon
r_return
id|hose
suffix:semicolon
)brace
r_struct
id|resource
op_star
id|__init
DECL|function|alloc_resource
id|alloc_resource
c_func
(paren
r_void
)paren
(brace
r_struct
id|resource
op_star
id|res
suffix:semicolon
id|res
op_assign
id|alloc_bootmem
c_func
(paren
r_sizeof
(paren
op_star
id|res
)paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* Provide information on locations of various I/O regions in physical&n;   memory.  Do this on a per-card basis so that we choose the right hose.  */
id|asmlinkage
r_int
DECL|function|sys_pciconfig_iobase
id|sys_pciconfig_iobase
c_func
(paren
r_int
id|which
comma
r_int
r_int
id|bus
comma
r_int
r_int
id|dfn
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* from hose or from bus.devfn */
r_if
c_cond
(paren
id|which
op_amp
id|IOBASE_FROM_HOSE
)paren
(brace
r_for
c_loop
(paren
id|hose
op_assign
id|hose_head
suffix:semicolon
id|hose
suffix:semicolon
id|hose
op_assign
id|hose-&gt;next
)paren
r_if
c_cond
(paren
id|hose-&gt;index
op_eq
id|bus
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hose
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Special hook for ISA access.  */
r_if
c_cond
(paren
id|bus
op_eq
l_int|0
op_logical_and
id|dfn
op_eq
l_int|0
)paren
(brace
id|hose
op_assign
id|pci_isa_hose
suffix:semicolon
)brace
r_else
(brace
id|dev
op_assign
id|pci_find_slot
c_func
(paren
id|bus
comma
id|dfn
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|hose
op_assign
id|dev-&gt;sysdata
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|which
op_amp
op_complement
id|IOBASE_FROM_HOSE
)paren
(brace
r_case
id|IOBASE_HOSE
suffix:colon
r_return
id|hose-&gt;index
suffix:semicolon
r_case
id|IOBASE_SPARSE_MEM
suffix:colon
r_return
id|hose-&gt;sparse_mem_base
suffix:semicolon
r_case
id|IOBASE_DENSE_MEM
suffix:colon
r_return
id|hose-&gt;dense_mem_base
suffix:semicolon
r_case
id|IOBASE_SPARSE_IO
suffix:colon
r_return
id|hose-&gt;sparse_io_base
suffix:semicolon
r_case
id|IOBASE_DENSE_IO
suffix:colon
r_return
id|hose-&gt;dense_io_base
suffix:semicolon
r_case
id|IOBASE_ROOT_BUS
suffix:colon
r_return
id|hose-&gt;bus-&gt;number
suffix:semicolon
)brace
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
multiline_comment|/* Return the index of the PCI controller for device PDEV. */
r_int
DECL|function|pci_controller_num
id|pci_controller_num
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|pdev-&gt;sysdata
suffix:semicolon
r_return
(paren
id|hose
ques
c_cond
id|hose-&gt;index
suffix:colon
op_minus
id|ENXIO
)paren
suffix:semicolon
)brace
eof
