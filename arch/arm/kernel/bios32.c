multiline_comment|/*&n; *  linux/arch/arm/kernel/bios32.c&n; *&n; *  PCI bios-type initialisation for PCI machines&n; *&n; *  Bits taken from various places.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/page.h&gt; /* for BUG() */
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/pci.h&gt;
DECL|variable|debug_pci
r_static
r_int
id|debug_pci
suffix:semicolon
DECL|variable|have_isa_bridge
r_int
id|have_isa_bridge
suffix:semicolon
DECL|function|pcibios_report_status
r_void
id|pcibios_report_status
c_func
(paren
id|u_int
id|status_mask
comma
r_int
id|warn
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
id|u16
id|status
suffix:semicolon
multiline_comment|/*&n;&t;&t; * ignore host bridge - we handle&n;&t;&t; * that separately&n;&t;&t; */
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_eq
l_int|0
op_logical_and
id|dev-&gt;devfn
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_STATUS
comma
op_amp
id|status
)paren
suffix:semicolon
id|status
op_and_assign
id|status_mask
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/* clear the status errors */
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_STATUS
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|warn
)paren
id|printk
c_func
(paren
l_string|&quot;(%02x:%02x.%d: %04X) &quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * We don&squot;t use this to fix the device, but initialisation of it.&n; * It&squot;s not the correct use for this, but it works.&n; * Note that the arbiter/ISA bridge appears to be buggy, specifically in&n; * the following area:&n; * 1. park on CPU&n; * 2. ISA bridge ping-pong&n; * 3. ISA bridge master handling of target RETRY&n; *&n; * Bug 3 is responsible for the sound DMA grinding to a halt.  We now&n; * live with bug 2.&n; */
DECL|function|pci_fixup_83c553
r_static
r_void
id|__init
id|pci_fixup_83c553
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/*&n;&t; * Set memory region to start at address 0, and enable IO&n;&t; */
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_0
comma
id|PCI_BASE_ADDRESS_SPACE_MEMORY
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|PCI_COMMAND_IO
)paren
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_sub_assign
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * All memory requests from ISA to be channelled to PCI&n;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x48
comma
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Enable ping-pong on bus master to ISA bridge transactions.&n;&t; * This improves the sound DMA substantially.  The fixed&n;&t; * priority arbiter also helps (see below).&n;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x42
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Enable PCI retry&n;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x40
comma
l_int|0x22
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We used to set the arbiter to &quot;park on last master&quot; (bit&n;&t; * 1 set), but unfortunately the CyberPro does not park the&n;&t; * bus.  We must therefore park on CPU.  Unfortunately, this&n;&t; * may trigger yet another bug in the 553.&n;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x83
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Make the ISA DMA request lowest priority, and disable&n;&t; * rotating priorities completely.&n;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x80
comma
l_int|0x11
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x81
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Route INTA input to IRQ 11, and set IRQ11 to be level&n;&t; * sensitive.&n;&t; */
id|pci_write_config_word
c_func
(paren
id|dev
comma
l_int|0x44
comma
l_int|0xb000
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x08
comma
l_int|0x4d1
)paren
suffix:semicolon
)brace
DECL|function|pci_fixup_unassign
r_static
r_void
id|__init
id|pci_fixup_unassign
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_sub_assign
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Prevent the PCI layer from seeing the resources allocated to this device&n; * if it is the host bridge by marking it as such.  These resources are of&n; * no consequence to the PCI layer (they are handled elsewhere).&n; */
DECL|function|pci_fixup_dec21285
r_static
r_void
id|__init
id|pci_fixup_dec21285
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;devfn
op_eq
l_int|0
)paren
(brace
id|dev
op_member_access_from_pointer
r_class
op_and_assign
l_int|0xff
suffix:semicolon
id|dev
op_member_access_from_pointer
r_class
op_or_assign
id|PCI_CLASS_BRIDGE_HOST
op_lshift
l_int|8
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
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * PCI IDE controllers use non-standard I/O port decoding, respect it.&n; */
DECL|function|pci_fixup_ide_bases
r_static
r_void
id|__init
id|pci_fixup_ide_bases
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|resource
op_star
id|r
suffix:semicolon
r_int
id|i
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
id|PCI_CLASS_STORAGE_IDE
)paren
r_return
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
id|r
op_assign
id|dev-&gt;resource
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r-&gt;start
op_amp
op_complement
l_int|0x80
)paren
op_eq
l_int|0x374
)paren
(brace
id|r-&gt;start
op_or_assign
l_int|2
suffix:semicolon
id|r-&gt;end
op_assign
id|r-&gt;start
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Put the DEC21142 to sleep&n; */
DECL|function|pci_fixup_dec21142
r_static
r_void
id|__init
id|pci_fixup_dec21142
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
l_int|0x80000000
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The CY82C693 needs some rather major fixups to ensure that it does&n; * the right thing.  Idea from the Alpha people, with a few additions.&n; *&n; * We ensure that the IDE base registers are set to 1f0/3f4 for the&n; * primary bus, and 170/374 for the secondary bus.  Also, hide them&n; * from the PCI subsystem view as well so we won&squot;t try to perform&n; * our own auto-configuration on them.&n; *&n; * In addition, we ensure that the PCI IDE interrupts are routed to&n; * IRQ 14 and IRQ 15 respectively.&n; *&n; * The above gets us to a point where the IDE on this device is&n; * functional.  However, The CY82C693U _does not work_ in bus&n; * master mode without locking the PCI bus solid.&n; */
DECL|function|pci_fixup_cy82c693
r_static
r_void
id|__init
id|pci_fixup_cy82c693
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
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_eq
id|PCI_CLASS_STORAGE_IDE
)paren
(brace
id|u32
id|base0
comma
id|base1
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_amp
l_int|0x80
)paren
(brace
multiline_comment|/* primary */
id|base0
op_assign
l_int|0x1f0
suffix:semicolon
id|base1
op_assign
l_int|0x3f4
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* secondary */
id|base0
op_assign
l_int|0x170
suffix:semicolon
id|base1
op_assign
l_int|0x374
suffix:semicolon
)brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_0
comma
id|base0
op_or
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_1
comma
id|base1
op_or
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_assign
l_int|0
suffix:semicolon
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
id|start
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|1
)braket
dot
id|end
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
r_else
r_if
c_cond
(paren
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Setup IDE IRQ routing.&n;&t;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x4b
comma
l_int|14
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x4c
comma
l_int|15
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Disable FREQACK handshake, enable USB.&n;&t;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x4d
comma
l_int|0x41
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Enable PCI retry, and PCI post-write buffer.&n;&t;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x44
comma
l_int|0x17
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Enable ISA master and DMA post write buffering.&n;&t;&t; */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x45
comma
l_int|0x03
)paren
suffix:semicolon
)brace
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
id|PCI_VENDOR_ID_CONTAQ
comma
id|PCI_DEVICE_ID_CONTAQ_82C693
comma
id|pci_fixup_cy82c693
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_DEC
comma
id|PCI_DEVICE_ID_DEC_21142
comma
id|pci_fixup_dec21142
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_DEC
comma
id|PCI_DEVICE_ID_DEC_21285
comma
id|pci_fixup_dec21285
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_WINBOND
comma
id|PCI_DEVICE_ID_WINBOND_83C553
comma
id|pci_fixup_83c553
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_WINBOND2
comma
id|PCI_DEVICE_ID_WINBOND2_89C940F
comma
id|pci_fixup_unassign
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|pci_fixup_ide_bases
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
r_void
id|__init
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
id|pci_sys_data
op_star
id|sys
op_assign
id|dev-&gt;sysdata
suffix:semicolon
id|u32
id|val
comma
id|check
suffix:semicolon
r_int
id|reg
suffix:semicolon
r_if
c_cond
(paren
id|debug_pci
)paren
id|printk
c_func
(paren
l_string|&quot;PCI: Assigning %3s %08lx to %s&bslash;n&quot;
comma
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
ques
c_cond
l_string|&quot;IO&quot;
suffix:colon
l_string|&quot;MEM&quot;
comma
id|res-&gt;start
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resource
OL
l_int|6
)paren
(brace
id|reg
op_assign
id|PCI_BASE_ADDRESS_0
op_plus
l_int|4
op_star
id|resource
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|resource
op_eq
id|PCI_ROM_RESOURCE
)paren
(brace
id|reg
op_assign
id|dev-&gt;rom_base_reg
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Somebody might have asked allocation of a&n;&t;&t; * non-standard resource.&n;&t;&t; */
r_return
suffix:semicolon
)brace
id|val
op_assign
id|res-&gt;start
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
id|val
op_sub_assign
id|sys-&gt;mem_offset
suffix:semicolon
r_else
id|val
op_sub_assign
id|sys-&gt;io_offset
suffix:semicolon
id|val
op_or_assign
id|res-&gt;flags
op_amp
id|PCI_REGION_FLAG_MASK
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
id|val
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
op_amp
id|check
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|val
op_xor
id|check
)paren
op_amp
(paren
(paren
id|val
op_amp
id|PCI_BASE_ADDRESS_SPACE_IO
)paren
ques
c_cond
id|PCI_BASE_ADDRESS_IO_MASK
suffix:colon
id|PCI_BASE_ADDRESS_MEM_MASK
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Error while updating region &quot;
l_string|&quot;%s/%d (%08x != %08x)&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|resource
comma
id|val
comma
id|check
)paren
suffix:semicolon
)brace
)brace
DECL|function|pcibios_update_irq
r_void
id|__init
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
r_if
c_cond
(paren
id|debug_pci
)paren
id|printk
c_func
(paren
l_string|&quot;PCI: Assigning IRQ %02d to %s&bslash;n&quot;
comma
id|irq
comma
id|dev-&gt;name
)paren
suffix:semicolon
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
multiline_comment|/*&n; * If the bus contains any of these devices, then we must not turn on&n; * parity checking of any kind.  Currently this is CyberPro 20x0 only.&n; */
DECL|function|pdev_bad_for_parity
r_static
r_inline
r_int
id|pdev_bad_for_parity
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
(paren
id|dev-&gt;vendor
op_eq
id|PCI_VENDOR_ID_INTERG
op_logical_and
(paren
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_INTERG_2000
op_logical_or
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_INTERG_2010
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Adjust the device resources from bus-centric to Linux-centric.&n; */
r_static
r_void
id|__init
DECL|function|pdev_fixup_device_resources
id|pdev_fixup_device_resources
c_func
(paren
r_struct
id|pci_sys_data
op_star
id|root
comma
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|offset
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
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_eq
l_int|0
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
id|IORESOURCE_MEM
)paren
id|offset
op_assign
id|root-&gt;mem_offset
suffix:semicolon
r_else
id|offset
op_assign
id|root-&gt;io_offset
suffix:semicolon
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_add_assign
id|offset
suffix:semicolon
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
op_add_assign
id|offset
suffix:semicolon
)brace
)brace
r_static
r_void
id|__init
DECL|function|pbus_assign_bus_resources
id|pbus_assign_bus_resources
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_struct
id|pci_sys_data
op_star
id|root
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|bus-&gt;self
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
multiline_comment|/*&n;&t;&t; * Assign root bus resources.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
id|bus-&gt;resource
(braket
id|i
)braket
op_assign
id|root-&gt;resource
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * pcibios_fixup_bus - Called after each bus is probed,&n; * but before its children are examined.&n; */
DECL|function|pcibios_fixup_bus
r_void
id|__init
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|pci_sys_data
op_star
id|root
op_assign
id|bus-&gt;sysdata
suffix:semicolon
r_struct
id|list_head
op_star
id|walk
suffix:semicolon
id|u16
id|features
op_assign
id|PCI_COMMAND_SERR
op_or
id|PCI_COMMAND_PARITY
suffix:semicolon
id|u16
id|all_status
op_assign
op_minus
l_int|1
suffix:semicolon
id|pbus_assign_bus_resources
c_func
(paren
id|bus
comma
id|root
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Walk the devices on this bus, working out what we can&n;&t; * and can&squot;t support.&n;&t; */
r_for
c_loop
(paren
id|walk
op_assign
id|bus-&gt;devices.next
suffix:semicolon
id|walk
op_ne
op_amp
id|bus-&gt;devices
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
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
id|walk
)paren
suffix:semicolon
id|u16
id|status
suffix:semicolon
id|pdev_fixup_device_resources
c_func
(paren
id|root
comma
id|dev
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_STATUS
comma
op_amp
id|status
)paren
suffix:semicolon
id|all_status
op_and_assign
id|status
suffix:semicolon
r_if
c_cond
(paren
id|pdev_bad_for_parity
c_func
(paren
id|dev
)paren
)paren
id|features
op_and_assign
op_complement
(paren
id|PCI_COMMAND_SERR
op_or
id|PCI_COMMAND_PARITY
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If this device is an ISA bridge, set the have_isa_bridge&n;&t;&t; * flag.  We will then go looking for things like keyboard,&n;&t;&t; * etc&n;&t;&t; */
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
op_logical_or
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
op_eq
id|PCI_CLASS_BRIDGE_EISA
)paren
id|have_isa_bridge
op_assign
op_logical_neg
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If any device on this bus does not support fast back to back&n;&t; * transfers, then the bus as a whole is not able to support them.&n;&t; * Having fast back to back transfers on saves us one PCI cycle&n;&t; * per transaction.&n;&t; */
r_if
c_cond
(paren
id|all_status
op_amp
id|PCI_STATUS_FAST_BACK
)paren
id|features
op_or_assign
id|PCI_COMMAND_FAST_BACK
suffix:semicolon
multiline_comment|/*&n;&t; * Now walk the devices again, this time setting them up.&n;&t; */
r_for
c_loop
(paren
id|walk
op_assign
id|bus-&gt;devices.next
suffix:semicolon
id|walk
op_ne
op_amp
id|bus-&gt;devices
suffix:semicolon
id|walk
op_assign
id|walk-&gt;next
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
id|walk
)paren
suffix:semicolon
id|u16
id|cmd
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
id|cmd
op_or_assign
id|features
suffix:semicolon
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
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_CACHE_LINE_SIZE
comma
id|SMP_CACHE_BYTES
op_rshift
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Report what we did for this bus&n;&t; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: bus%d: Fast back to back transfers %sabled&bslash;n&quot;
comma
id|bus-&gt;number
comma
(paren
id|features
op_amp
id|PCI_COMMAND_FAST_BACK
)paren
ques
c_cond
l_string|&quot;en&quot;
suffix:colon
l_string|&quot;dis&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert from Linux-centric to bus-centric addresses for bridge devices.&n; */
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
id|pci_sys_data
op_star
id|root
op_assign
id|bus-&gt;sysdata
suffix:semicolon
id|ranges-&gt;io_start
op_sub_assign
id|root-&gt;io_offset
suffix:semicolon
id|ranges-&gt;io_end
op_sub_assign
id|root-&gt;io_offset
suffix:semicolon
id|ranges-&gt;mem_start
op_sub_assign
id|root-&gt;mem_offset
suffix:semicolon
id|ranges-&gt;mem_end
op_sub_assign
id|root-&gt;mem_offset
suffix:semicolon
id|ranges-&gt;prefetch_start
op_sub_assign
id|root-&gt;mem_offset
suffix:semicolon
id|ranges-&gt;prefetch_end
op_sub_assign
id|root-&gt;mem_offset
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the standard PCI-PCI bridge swizzling algorithm:&n; *&n; *   Dev: 0  1  2  3&n; *    A   A  B  C  D&n; *    B   B  C  D  A&n; *    C   C  D  A  B&n; *    D   D  A  B  C&n; *        ^^^^^^^^^^ irq pin on bridge&n; */
DECL|function|pci_std_swizzle
id|u8
id|__devinit
id|pci_std_swizzle
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
r_int
id|pin
op_assign
op_star
id|pinp
suffix:semicolon
r_if
c_cond
(paren
id|pin
op_ne
l_int|0
)paren
(brace
id|pin
op_sub_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;bus-&gt;self
)paren
(brace
id|pin
op_assign
(paren
id|pin
op_plus
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
op_amp
l_int|3
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * move up the chain of bridges,&n;&t;&t;&t; * swizzling as we go.&n;&t;&t;&t; */
id|dev
op_assign
id|dev-&gt;bus-&gt;self
suffix:semicolon
)brace
op_star
id|pinp
op_assign
id|pin
op_plus
l_int|1
suffix:semicolon
)brace
r_return
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Swizzle the device pin each time we cross a bridge.&n; * This might update pin and returns the slot number.&n; */
DECL|function|pcibios_swizzle
r_static
id|u8
id|__devinit
id|pcibios_swizzle
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
op_star
id|pin
)paren
(brace
r_struct
id|pci_sys_data
op_star
id|sys
op_assign
id|dev-&gt;sysdata
suffix:semicolon
r_int
id|slot
op_assign
l_int|0
comma
id|oldpin
op_assign
op_star
id|pin
suffix:semicolon
r_if
c_cond
(paren
id|sys-&gt;swizzle
)paren
id|slot
op_assign
id|sys
op_member_access_from_pointer
id|swizzle
c_func
(paren
id|dev
comma
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug_pci
)paren
id|printk
c_func
(paren
l_string|&quot;PCI: %s swizzling pin %d =&gt; pin %d slot %d&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|oldpin
comma
op_star
id|pin
comma
id|slot
)paren
suffix:semicolon
r_return
id|slot
suffix:semicolon
)brace
multiline_comment|/*&n; * Map a slot/pin to an IRQ.&n; */
DECL|function|pcibios_map_irq
r_static
r_int
id|pcibios_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_struct
id|pci_sys_data
op_star
id|sys
op_assign
id|dev-&gt;sysdata
suffix:semicolon
r_int
id|irq
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sys-&gt;map_irq
)paren
id|irq
op_assign
id|sys
op_member_access_from_pointer
id|map_irq
c_func
(paren
id|dev
comma
id|slot
comma
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug_pci
)paren
id|printk
c_func
(paren
l_string|&quot;PCI: %s mapping slot %d pin %d =&gt; irq %d&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|slot
comma
id|pin
comma
id|irq
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
DECL|function|pcibios_init_hw
r_static
r_void
id|__init
id|pcibios_init_hw
c_func
(paren
r_struct
id|hw_pci
op_star
id|hw
)paren
(brace
r_struct
id|pci_sys_data
op_star
id|sys
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|nr
comma
id|busnr
suffix:semicolon
r_for
c_loop
(paren
id|nr
op_assign
id|busnr
op_assign
l_int|0
suffix:semicolon
id|nr
OL
id|hw-&gt;nr_controllers
suffix:semicolon
id|nr
op_increment
)paren
(brace
id|sys
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_sys_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sys
)paren
id|panic
c_func
(paren
l_string|&quot;PCI: unable to allocate sys data!&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|sys
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pci_sys_data
)paren
)paren
suffix:semicolon
id|sys-&gt;hw
op_assign
id|hw
suffix:semicolon
id|sys-&gt;busnr
op_assign
id|busnr
suffix:semicolon
id|sys-&gt;swizzle
op_assign
id|hw-&gt;swizzle
suffix:semicolon
id|sys-&gt;map_irq
op_assign
id|hw-&gt;map_irq
suffix:semicolon
id|sys-&gt;resource
(braket
l_int|0
)braket
op_assign
op_amp
id|ioport_resource
suffix:semicolon
id|sys-&gt;resource
(braket
l_int|1
)braket
op_assign
op_amp
id|iomem_resource
suffix:semicolon
id|ret
op_assign
id|hw
op_member_access_from_pointer
id|setup
c_func
(paren
id|nr
comma
id|sys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OG
l_int|0
)paren
(brace
id|sys-&gt;bus
op_assign
id|hw
op_member_access_from_pointer
id|scan
c_func
(paren
id|nr
comma
id|sys
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sys-&gt;bus
)paren
id|panic
c_func
(paren
l_string|&quot;PCI: unable to scan bus!&quot;
)paren
suffix:semicolon
id|busnr
op_assign
id|sys-&gt;bus-&gt;subordinate
op_plus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|kfree
c_func
(paren
id|sys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|function|pci_common_init
r_void
id|__init
id|pci_common_init
c_func
(paren
r_struct
id|hw_pci
op_star
id|hw
)paren
(brace
r_if
c_cond
(paren
id|hw-&gt;preinit
)paren
id|hw
op_member_access_from_pointer
id|preinit
c_func
(paren
)paren
suffix:semicolon
id|pcibios_init_hw
c_func
(paren
id|hw
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;postinit
)paren
id|hw
op_member_access_from_pointer
id|postinit
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Assign any unassigned resources.&n;&t; */
id|pci_assign_unassigned_resources
c_func
(paren
)paren
suffix:semicolon
id|pci_fixup_irqs
c_func
(paren
id|pcibios_swizzle
comma
id|pcibios_map_irq
)paren
suffix:semicolon
)brace
DECL|function|pcibios_setup
r_char
op_star
id|__init
id|pcibios_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;debug&quot;
)paren
)paren
(brace
id|debug_pci
op_assign
l_int|1
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|str
suffix:semicolon
)brace
multiline_comment|/*&n; * From arch/i386/kernel/pci-i386.c:&n; *&n; * We need to avoid collisions with `mirrored&squot; VGA ports&n; * and other strange ISA hardware, so we always want the&n; * addresses to be allocated in the 0x000-0x0ff region&n; * modulo 0x400.&n; *&n; * Why? Because some silly external IO cards only decode&n; * the low 10 bits of the IO address. The 0x00-0xff region&n; * is reserved for motherboard devices that decode all 16&n; * bits, so it&squot;s ok to allocate at, say, 0x2800-0x28ff,&n; * but we want to try to avoid allocating at 0x2900-0x2bff&n; * which might be mirrored at 0x0100-0x03ff..&n; */
DECL|function|pcibios_align_resource
r_void
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
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
(brace
r_int
r_int
id|start
op_assign
id|res-&gt;start
suffix:semicolon
r_if
c_cond
(paren
id|start
op_amp
l_int|0x300
)paren
id|res-&gt;start
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
)brace
multiline_comment|/**&n; * pcibios_enable_device - Enable I/O and memory.&n; * @dev: PCI device to be enabled&n; */
DECL|function|pcibios_enable_device
r_int
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
id|old_cmd
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_struct
id|resource
op_star
id|r
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
id|old_cmd
op_assign
id|cmd
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
l_int|6
suffix:semicolon
id|idx
op_increment
)paren
(brace
multiline_comment|/* Only set up the requested stuff */
r_if
c_cond
(paren
op_logical_neg
(paren
id|mask
op_amp
(paren
l_int|1
op_lshift
id|idx
)paren
)paren
)paren
r_continue
suffix:semicolon
id|r
op_assign
id|dev-&gt;resource
op_plus
id|idx
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
op_logical_and
id|r-&gt;end
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Device %s not available because&quot;
l_string|&quot; of resource collisions&bslash;n&quot;
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r-&gt;flags
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
id|r-&gt;flags
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
id|old_cmd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: enabling device %s (%04x -&gt; %04x)&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|old_cmd
comma
id|cmd
)paren
suffix:semicolon
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
DECL|function|pci_mmap_page_range
r_int
id|pci_mmap_page_range
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_enum
id|pci_mmap_state
id|mmap_state
comma
r_int
id|write_combine
)paren
(brace
r_struct
id|pci_sys_data
op_star
id|root
op_assign
id|dev-&gt;sysdata
suffix:semicolon
r_int
r_int
id|prot
comma
id|phys
suffix:semicolon
r_if
c_cond
(paren
id|mmap_state
op_eq
id|pci_mmap_io
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
id|phys
op_assign
id|root-&gt;mem_offset
op_plus
(paren
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Mark this as IO&n;&t; */
id|vma-&gt;vm_flags
op_or_assign
id|VM_SHM
op_or
id|VM_LOCKED
op_or
id|VM_IO
suffix:semicolon
id|vma-&gt;vm_page_prot
op_assign
id|pgprot_noncached
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remap_page_range
c_func
(paren
id|vma
comma
id|vma-&gt;vm_start
comma
id|phys
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_page_prot
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
