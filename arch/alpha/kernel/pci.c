multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/pci.c&n; *&n; * Extruded from code written by&n; *&t;Dave Rusling (david.rusling@reo.mts.dec.com)&n; *&t;David Mosberger (davidm@cs.arizona.edu)&n; */
multiline_comment|/* 2.3.x PCI/resources, 1999 Andrea Arcangeli &lt;andrea@suse.de&gt; */
multiline_comment|/*&n; * Nov 2000, Ivan Kokshaysky &lt;ink@jurassic.park.msu.ru&gt;&n; *&t;     PCI-PCI bridges cleanup&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
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
multiline_comment|/* Indicate whether we respect the PCI setup left by console. */
multiline_comment|/*&n; * Make this long-lived  so that we know when shutting down&n; * whether we probed only or not.&n; */
DECL|variable|pci_probe_only
r_int
id|pci_probe_only
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
multiline_comment|/* The Cypress bridge responds on the PCI bus in the address range&n;&t;   0xffff0000-0xffffffff (conventional x86 BIOS ROM).  There is no&n;&t;   way to turn this off.  The bridge also supports several extended&n;&t;   BIOS ranges (disabled after power-up), and some consoles do turn&n;&t;   them on.  So if we use a large direct-map window, or a large SG&n;&t;   window, we must avoid the entire 0xfff00000-0xffffffff region.  */
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
l_int|0xfff00000UL
)paren
id|__direct_map_size
op_assign
l_int|0xfff00000UL
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
l_int|0xfff00000UL
)paren
id|pci-&gt;size
op_assign
l_int|0xfff00000UL
op_minus
id|pci-&gt;dma_base
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Called for each device after PCI setup is done. */
r_static
r_void
id|__init
DECL|function|pcibios_fixup_final
id|pcibios_fixup_final
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
r_class
op_assign
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
suffix:semicolon
r_if
c_cond
(paren
r_class
op_eq
id|PCI_CLASS_BRIDGE_ISA
op_logical_or
r_class
op_eq
id|PCI_CLASS_BRIDGE_EISA
)paren
(brace
id|dev-&gt;dma_mask
op_assign
id|MAX_ISA_DMA_ADDRESS
op_minus
l_int|1
suffix:semicolon
id|isa_bridge
op_assign
id|dev
suffix:semicolon
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
id|PCI_DEVICE_ID_INTEL_82378
comma
id|quirk_isa_bridge
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
id|PCI_FIXUP_FINAL
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|pcibios_fixup_final
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
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
id|max
c_func
(paren
l_int|0x1000UL
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
DECL|macro|KB
macro_line|#undef KB
DECL|macro|MB
macro_line|#undef MB
DECL|macro|GB
macro_line|#undef GB
r_static
r_int
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
id|alpha_mv.init_pci
)paren
id|alpha_mv
dot
id|init_pci
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
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
macro_line|#ifdef ALPHA_RESTORE_SRM_SETUP
DECL|variable|srm_saved_configs
r_static
r_struct
id|pdev_srm_saved_conf
op_star
id|srm_saved_configs
suffix:semicolon
r_void
id|__init
DECL|function|pdev_save_srm_config
id|pdev_save_srm_config
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|pdev_srm_saved_conf
op_star
id|tmp
suffix:semicolon
r_static
r_int
id|printed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|alpha_using_srm
op_logical_or
id|pci_probe_only
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|printed
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;pci: enabling save/restore of SRM state&bslash;n&quot;
)paren
suffix:semicolon
id|printed
op_assign
l_int|1
suffix:semicolon
)brace
id|tmp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|tmp
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: kmalloc() failed!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|tmp-&gt;next
op_assign
id|srm_saved_configs
suffix:semicolon
id|tmp-&gt;dev
op_assign
id|dev
suffix:semicolon
id|pci_save_state
c_func
(paren
id|dev
comma
id|tmp-&gt;regs
)paren
suffix:semicolon
id|srm_saved_configs
op_assign
id|tmp
suffix:semicolon
)brace
r_void
DECL|function|pci_restore_srm_config
id|pci_restore_srm_config
c_func
(paren
r_void
)paren
(brace
r_struct
id|pdev_srm_saved_conf
op_star
id|tmp
suffix:semicolon
multiline_comment|/* No need to restore if probed only. */
r_if
c_cond
(paren
id|pci_probe_only
)paren
r_return
suffix:semicolon
multiline_comment|/* Restore SRM config. */
r_for
c_loop
(paren
id|tmp
op_assign
id|srm_saved_configs
suffix:semicolon
id|tmp
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
)paren
(brace
id|pci_restore_state
c_func
(paren
id|tmp-&gt;dev
comma
id|tmp-&gt;regs
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
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
multiline_comment|/* Propagate hose info into the subordinate devices.  */
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
multiline_comment|/* Root bus. */
id|u32
id|pci_mem_end
suffix:semicolon
id|u32
id|sg_base
op_assign
id|hose-&gt;sg_pci
ques
c_cond
id|hose-&gt;sg_pci-&gt;dma_base
suffix:colon
op_complement
l_int|0
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
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
multiline_comment|/* Adjust hose mem_space limit to prevent PCI allocations&n;&t;&t;   in the iommu windows. */
id|pci_mem_end
op_assign
id|min
c_func
(paren
(paren
id|u32
)paren
id|__direct_map_base
comma
id|sg_base
)paren
op_minus
l_int|1
suffix:semicolon
id|end
op_assign
id|hose-&gt;mem_space-&gt;start
op_plus
id|pci_mem_end
suffix:semicolon
r_if
c_cond
(paren
id|hose-&gt;mem_space-&gt;end
OG
id|end
)paren
id|hose-&gt;mem_space-&gt;end
op_assign
id|end
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pci_probe_only
op_logical_and
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_eq
id|PCI_CLASS_BRIDGE_PCI
)paren
(brace
id|pci_read_bridge_bases
c_func
(paren
id|bus
)paren
suffix:semicolon
id|pcibios_fixup_device_resources
c_func
(paren
id|dev
comma
id|bus
)paren
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
id|pdev_save_srm_config
c_func
(paren
id|dev
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
id|u8
id|pin
op_assign
op_star
id|pinp
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;bus-&gt;parent
)paren
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
op_star
id|pinp
op_assign
id|pin
suffix:semicolon
multiline_comment|/* The slot is the slot of the last bridge. */
r_return
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
)brace
r_void
id|__devinit
DECL|function|pcibios_resource_to_bus
id|pcibios_resource_to_bus
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|pci_bus_region
op_star
id|region
comma
r_struct
id|resource
op_star
id|res
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
id|dev-&gt;sysdata
suffix:semicolon
r_int
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|offset
op_assign
id|hose-&gt;io_space-&gt;start
suffix:semicolon
r_else
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
id|offset
op_assign
id|hose-&gt;mem_space-&gt;start
suffix:semicolon
id|region-&gt;start
op_assign
id|res-&gt;start
op_minus
id|offset
suffix:semicolon
id|region-&gt;end
op_assign
id|res-&gt;end
op_minus
id|offset
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HOTPLUG
DECL|variable|pcibios_resource_to_bus
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_resource_to_bus
)paren
suffix:semicolon
macro_line|#endif
r_int
DECL|function|pcibios_enable_device
id|pcibios_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|mask
)paren
(brace
id|u16
id|cmd
comma
id|oldcmd
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
id|oldcmd
op_assign
id|cmd
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
r_struct
id|resource
op_star
id|res
op_assign
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_IO
suffix:semicolon
r_else
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_MEMORY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
op_ne
id|oldcmd
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PCI: Enabling device: (%s), cmd %x&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|cmd
)paren
suffix:semicolon
multiline_comment|/* Enable the appropriate bits in the PCI command register.  */
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
)brace
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
id|pci_name
c_func
(paren
id|dev
)paren
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
r_static
r_void
id|__init
DECL|function|pcibios_claim_one_bus
id|pcibios_claim_one_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|b
)paren
(brace
r_struct
id|list_head
op_star
id|ld
suffix:semicolon
r_struct
id|pci_bus
op_star
id|child_bus
suffix:semicolon
r_for
c_loop
(paren
id|ld
op_assign
id|b-&gt;devices.next
suffix:semicolon
id|ld
op_ne
op_amp
id|b-&gt;devices
suffix:semicolon
id|ld
op_assign
id|ld-&gt;next
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
id|ld
)paren
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
r_struct
id|resource
op_star
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;parent
op_logical_or
op_logical_neg
id|r-&gt;start
op_logical_or
op_logical_neg
id|r-&gt;flags
)paren
r_continue
suffix:semicolon
id|pci_claim_resource
c_func
(paren
id|dev
comma
id|i
)paren
suffix:semicolon
)brace
)brace
id|list_for_each_entry
c_func
(paren
id|child_bus
comma
op_amp
id|b-&gt;children
comma
id|node
)paren
id|pcibios_claim_one_bus
c_func
(paren
id|child_bus
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|pcibios_claim_console_setup
id|pcibios_claim_console_setup
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|lb
suffix:semicolon
r_for
c_loop
(paren
id|lb
op_assign
id|pci_root_buses.next
suffix:semicolon
id|lb
op_ne
op_amp
id|pci_root_buses
suffix:semicolon
id|lb
op_assign
id|lb-&gt;next
)paren
(brace
r_struct
id|pci_bus
op_star
id|b
op_assign
id|pci_bus_b
c_func
(paren
id|lb
)paren
suffix:semicolon
id|pcibios_claim_one_bus
c_func
(paren
id|b
)paren
suffix:semicolon
)brace
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
r_int
id|need_domain_info
op_assign
l_int|0
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
id|hose-&gt;need_domain_info
op_assign
id|need_domain_info
suffix:semicolon
id|next_busno
op_assign
id|bus-&gt;subordinate
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Don&squot;t allow 8-bit bus number overflow inside the hose -&n;&t;&t;   reserve some space for bridges. */
r_if
c_cond
(paren
id|next_busno
OG
l_int|224
)paren
(brace
id|next_busno
op_assign
l_int|0
suffix:semicolon
id|need_domain_info
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|pci_probe_only
)paren
id|pcibios_claim_console_setup
c_func
(paren
)paren
suffix:semicolon
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
eof
