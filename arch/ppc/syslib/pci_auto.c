multiline_comment|/*&n; * arch/ppc/syslib/pci_auto.c&n; * &n; * PCI autoconfiguration library&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.1.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/*&n; * The CardBus support is very preliminary.  Preallocating space is&n; * the way to go but will require some change in card services to&n; * make it useful.  Eventually this will ensure that we can put&n; * multiple CB bridges behind multiple P2P bridges.  For now, at&n; * least it ensures that we place the CB bridge BAR and assigned&n; * initial bus numbers.  I definitely need to do something about&n; * the lack of 16-bit I/O support. -MDP&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
DECL|macro|PCIAUTO_IDE_MODE_MASK
mdefine_line|#define&t;PCIAUTO_IDE_MODE_MASK&t;&t;0x05
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif /* DEBUG */
DECL|variable|pciauto_upper_iospc
r_static
r_int
id|pciauto_upper_iospc
suffix:semicolon
DECL|variable|pciauto_upper_memspc
r_static
r_int
id|pciauto_upper_memspc
suffix:semicolon
DECL|function|pciauto_setup_bars
r_void
id|__init
id|pciauto_setup_bars
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
r_int
id|current_bus
comma
r_int
id|pci_devfn
comma
r_int
id|bar_limit
)paren
(brace
r_int
id|bar_response
comma
id|bar_size
comma
id|bar_value
suffix:semicolon
r_int
id|bar
comma
id|addr_mask
suffix:semicolon
r_int
op_star
id|upper_limit
suffix:semicolon
r_int
id|found_mem64
op_assign
l_int|0
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI Autoconfig: Found Bus %d, Device %d, Function %d&bslash;n&quot;
comma
id|current_bus
comma
id|PCI_SLOT
c_func
(paren
id|pci_devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|pci_devfn
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|bar
op_assign
id|PCI_BASE_ADDRESS_0
suffix:semicolon
id|bar
op_le
id|bar_limit
suffix:semicolon
id|bar
op_add_assign
l_int|4
)paren
(brace
multiline_comment|/* Tickle the BAR and get the response */
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|bar
comma
l_int|0xffffffff
)paren
suffix:semicolon
id|early_read_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|bar
comma
op_amp
id|bar_response
)paren
suffix:semicolon
multiline_comment|/* If BAR is not implemented go to the next BAR */
r_if
c_cond
(paren
op_logical_neg
id|bar_response
)paren
r_continue
suffix:semicolon
multiline_comment|/* Check the BAR type and set our address mask */
r_if
c_cond
(paren
id|bar_response
op_amp
id|PCI_BASE_ADDRESS_SPACE
)paren
(brace
id|addr_mask
op_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|upper_limit
op_assign
op_amp
id|pciauto_upper_iospc
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI Autoconfig: BAR 0x%x, I/O, &quot;
comma
id|bar
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|bar_response
op_amp
id|PCI_BASE_ADDRESS_MEM_TYPE_MASK
)paren
op_eq
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
id|found_mem64
op_assign
l_int|1
suffix:semicolon
id|addr_mask
op_assign
id|PCI_BASE_ADDRESS_MEM_MASK
suffix:semicolon
id|upper_limit
op_assign
op_amp
id|pciauto_upper_memspc
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI Autoconfig: BAR 0x%x, Mem &quot;
comma
id|bar
)paren
suffix:semicolon
)brace
multiline_comment|/* Calculate requested size */
id|bar_size
op_assign
op_complement
(paren
id|bar_response
op_amp
id|addr_mask
)paren
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Allocate a base address */
id|bar_value
op_assign
(paren
op_star
id|upper_limit
op_minus
id|bar_size
)paren
op_amp
op_complement
(paren
id|bar_size
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Write it out and update our limit */
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|bar
comma
id|bar_value
)paren
suffix:semicolon
op_star
id|upper_limit
op_assign
id|bar_value
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we are a 64-bit decoder then increment to the&n;&t;&t; * upper 32 bits of the bar and force it to locate&n;&t;&t; * in the lower 4GB of memory.&n;&t;&t; */
r_if
c_cond
(paren
id|found_mem64
)paren
(brace
id|bar
op_add_assign
l_int|4
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|bar
comma
l_int|0x00000000
)paren
suffix:semicolon
id|found_mem64
op_assign
l_int|0
suffix:semicolon
)brace
id|DBG
c_func
(paren
l_string|&quot;size=0x%x, address=0x%x&bslash;n&quot;
comma
id|bar_size
comma
id|bar_value
)paren
suffix:semicolon
)brace
)brace
DECL|function|pciauto_prescan_setup_bridge
r_void
id|__init
id|pciauto_prescan_setup_bridge
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
r_int
id|current_bus
comma
r_int
id|pci_devfn
comma
r_int
id|sub_bus
comma
r_int
op_star
id|iosave
comma
r_int
op_star
id|memsave
)paren
(brace
multiline_comment|/* Configure bus number registers */
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_PRIMARY_BUS
comma
id|current_bus
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_SECONDARY_BUS
comma
id|sub_bus
op_plus
l_int|1
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_SUBORDINATE_BUS
comma
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* Round memory allocator to 1MB boundary */
id|pciauto_upper_memspc
op_and_assign
op_complement
(paren
l_int|0x100000
op_minus
l_int|1
)paren
suffix:semicolon
op_star
id|memsave
op_assign
id|pciauto_upper_memspc
suffix:semicolon
multiline_comment|/* Round I/O allocator to 4KB boundary */
id|pciauto_upper_iospc
op_and_assign
op_complement
(paren
l_int|0x1000
op_minus
l_int|1
)paren
suffix:semicolon
op_star
id|iosave
op_assign
id|pciauto_upper_iospc
suffix:semicolon
multiline_comment|/* Set up memory and I/O filter limits, assume 32-bit I/O space */
id|early_write_config_word
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_MEMORY_LIMIT
comma
(paren
(paren
id|pciauto_upper_memspc
op_minus
l_int|1
)paren
op_amp
l_int|0xfff00000
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_IO_LIMIT
comma
(paren
(paren
id|pciauto_upper_iospc
op_minus
l_int|1
)paren
op_amp
l_int|0x0000f000
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|early_write_config_word
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_IO_LIMIT_UPPER16
comma
(paren
(paren
id|pciauto_upper_iospc
op_minus
l_int|1
)paren
op_amp
l_int|0xffff0000
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* Zero upper 32 bits of prefetchable base/limit */
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_PREF_BASE_UPPER32
comma
l_int|0
)paren
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_PREF_LIMIT_UPPER32
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|pciauto_postscan_setup_bridge
r_void
id|__init
id|pciauto_postscan_setup_bridge
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
r_int
id|current_bus
comma
r_int
id|pci_devfn
comma
r_int
id|sub_bus
comma
r_int
op_star
id|iosave
comma
r_int
op_star
id|memsave
)paren
(brace
r_int
id|cmdstat
suffix:semicolon
multiline_comment|/* Configure bus number registers */
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_SUBORDINATE_BUS
comma
id|sub_bus
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Round memory allocator to 1MB boundary.&n;&t; * If no space used, allocate minimum.&n;&t; */
id|pciauto_upper_memspc
op_and_assign
op_complement
(paren
l_int|0x100000
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|memsave
op_eq
id|pciauto_upper_memspc
)paren
id|pciauto_upper_memspc
op_sub_assign
l_int|0x00100000
suffix:semicolon
id|early_write_config_word
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_MEMORY_BASE
comma
id|pciauto_upper_memspc
op_rshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* Allocate 1MB for pre-fretch */
id|early_write_config_word
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_PREF_MEMORY_LIMIT
comma
(paren
(paren
id|pciauto_upper_memspc
op_minus
l_int|1
)paren
op_amp
l_int|0xfff00000
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
id|pciauto_upper_memspc
op_sub_assign
l_int|0x100000
suffix:semicolon
id|early_write_config_word
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_PREF_MEMORY_BASE
comma
id|pciauto_upper_memspc
op_rshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* Round I/O allocator to 4KB boundary */
id|pciauto_upper_iospc
op_and_assign
op_complement
(paren
l_int|0x1000
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|iosave
op_eq
id|pciauto_upper_iospc
)paren
id|pciauto_upper_iospc
op_sub_assign
l_int|0x1000
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_IO_BASE
comma
(paren
id|pciauto_upper_iospc
op_amp
l_int|0x0000f000
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|early_write_config_word
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_IO_BASE_UPPER16
comma
id|pciauto_upper_iospc
op_rshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* Enable memory and I/O accesses, enable bus master */
id|early_read_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_COMMAND
comma
op_amp
id|cmdstat
)paren
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_COMMAND
comma
id|cmdstat
op_or
id|PCI_COMMAND_IO
op_or
id|PCI_COMMAND_MEMORY
op_or
id|PCI_COMMAND_MASTER
)paren
suffix:semicolon
)brace
DECL|function|pciauto_prescan_setup_cardbus_bridge
r_void
id|__init
id|pciauto_prescan_setup_cardbus_bridge
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
r_int
id|current_bus
comma
r_int
id|pci_devfn
comma
r_int
id|sub_bus
comma
r_int
op_star
id|iosave
comma
r_int
op_star
id|memsave
)paren
(brace
multiline_comment|/* Configure bus number registers */
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_PRIMARY_BUS
comma
id|current_bus
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_SECONDARY_BUS
comma
id|sub_bus
op_plus
l_int|1
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_SUBORDINATE_BUS
comma
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* Round memory allocator to 4KB boundary */
id|pciauto_upper_memspc
op_and_assign
op_complement
(paren
l_int|0x1000
op_minus
l_int|1
)paren
suffix:semicolon
op_star
id|memsave
op_assign
id|pciauto_upper_memspc
suffix:semicolon
multiline_comment|/* Round I/O allocator to 4 byte boundary */
id|pciauto_upper_iospc
op_and_assign
op_complement
(paren
l_int|0x4
op_minus
l_int|1
)paren
suffix:semicolon
op_star
id|iosave
op_assign
id|pciauto_upper_iospc
suffix:semicolon
multiline_comment|/* Set up memory and I/O filter limits, assume 32-bit I/O space */
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
l_int|0x20
comma
id|pciauto_upper_memspc
op_minus
l_int|1
)paren
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
l_int|0x30
comma
id|pciauto_upper_iospc
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|pciauto_postscan_setup_cardbus_bridge
r_void
id|__init
id|pciauto_postscan_setup_cardbus_bridge
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
r_int
id|current_bus
comma
r_int
id|pci_devfn
comma
r_int
id|sub_bus
comma
r_int
op_star
id|iosave
comma
r_int
op_star
id|memsave
)paren
(brace
r_int
id|cmdstat
suffix:semicolon
multiline_comment|/*&n;&t; * Configure subordinate bus number.  The PCI subsystem&n;&t; * bus scan will renumber buses (reserving three additional&n;&t; * for this PCI&lt;-&gt;CardBus bridge for the case where a CardBus&n;&t; * adapter contains a P2P or CB2CB bridge.&n;&t; */
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_SUBORDINATE_BUS
comma
id|sub_bus
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Reserve an additional 4MB for mem space and 16KB for&n;&t; * I/O space.  This should cover any additional space&n;&t; * requirement of unusual CardBus devices with &n;&t; * additional bridges that can consume more address space.&n;&t; * &n;&t; * Although pcmcia-cs currently will reprogram bridge&n;&t; * windows, the goal is to add an option to leave them&n;&t; * alone and use the bridge window ranges as the regions&n;&t; * that are searched for free resources upon hot-insertion&n;&t; * of a device.  This will allow a PCI&lt;-&gt;CardBus bridge&n;&t; * configured by this routine to happily live behind a&n;&t; * P2P bridge in a system.&n;&t; */
id|pciauto_upper_memspc
op_sub_assign
l_int|0x00400000
suffix:semicolon
id|pciauto_upper_iospc
op_sub_assign
l_int|0x00004000
suffix:semicolon
multiline_comment|/* Round memory allocator to 4KB boundary */
id|pciauto_upper_memspc
op_and_assign
op_complement
(paren
l_int|0x1000
op_minus
l_int|1
)paren
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
l_int|0x1c
comma
id|pciauto_upper_memspc
)paren
suffix:semicolon
multiline_comment|/* Round I/O allocator to 4 byte boundary */
id|pciauto_upper_iospc
op_and_assign
op_complement
(paren
l_int|0x4
op_minus
l_int|1
)paren
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
l_int|0x2c
comma
id|pciauto_upper_iospc
)paren
suffix:semicolon
multiline_comment|/* Enable memory and I/O accesses, enable bus master */
id|early_read_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_COMMAND
comma
op_amp
id|cmdstat
)paren
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_COMMAND
comma
id|cmdstat
op_or
id|PCI_COMMAND_IO
op_or
id|PCI_COMMAND_MEMORY
op_or
id|PCI_COMMAND_MASTER
)paren
suffix:semicolon
)brace
DECL|function|pciauto_bus_scan
r_int
id|__init
id|pciauto_bus_scan
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
r_int
id|current_bus
)paren
(brace
r_int
id|sub_bus
comma
id|pci_devfn
comma
id|pci_class
comma
id|cmdstat
comma
id|found_multi
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|vid
suffix:semicolon
r_int
r_char
id|header_type
suffix:semicolon
multiline_comment|/*&n;&t; * Fetch our I/O and memory space upper boundaries used&n;&t; * to allocated base addresses on this hose.&n;&t; */
r_if
c_cond
(paren
id|current_bus
op_eq
id|hose-&gt;first_busno
)paren
(brace
id|pciauto_upper_iospc
op_assign
id|hose-&gt;io_space.end
op_plus
l_int|1
suffix:semicolon
id|pciauto_upper_memspc
op_assign
id|hose-&gt;mem_space.end
op_plus
l_int|1
suffix:semicolon
)brace
id|sub_bus
op_assign
id|current_bus
suffix:semicolon
r_for
c_loop
(paren
id|pci_devfn
op_assign
l_int|0
suffix:semicolon
id|pci_devfn
OL
l_int|0xff
suffix:semicolon
id|pci_devfn
op_increment
)paren
(brace
multiline_comment|/* Skip our host bridge */
r_if
c_cond
(paren
(paren
id|current_bus
op_eq
id|hose-&gt;first_busno
)paren
op_logical_and
(paren
id|pci_devfn
op_eq
l_int|0
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|PCI_FUNC
c_func
(paren
id|pci_devfn
)paren
op_logical_and
op_logical_neg
id|found_multi
)paren
r_continue
suffix:semicolon
multiline_comment|/* If config space read fails from this device, move on */
r_if
c_cond
(paren
id|early_read_config_byte
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_HEADER_TYPE
comma
op_amp
id|header_type
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PCI_FUNC
c_func
(paren
id|pci_devfn
)paren
)paren
id|found_multi
op_assign
id|header_type
op_amp
l_int|0x80
suffix:semicolon
id|early_read_config_word
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_VENDOR_ID
comma
op_amp
id|vid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vid
op_ne
l_int|0xffff
)paren
(brace
id|early_read_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_CLASS_REVISION
comma
op_amp
id|pci_class
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pci_class
op_rshift
l_int|16
)paren
op_eq
id|PCI_CLASS_BRIDGE_PCI
)paren
(brace
r_int
id|iosave
comma
id|memsave
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI Autoconfig: Found P2P bridge, device %d&bslash;n&quot;
comma
id|PCI_SLOT
c_func
(paren
id|pci_devfn
)paren
)paren
suffix:semicolon
multiline_comment|/* Allocate PCI I/O and/or memory space */
id|pciauto_setup_bars
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_BASE_ADDRESS_1
)paren
suffix:semicolon
id|pciauto_prescan_setup_bridge
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|sub_bus
comma
op_amp
id|iosave
comma
op_amp
id|memsave
)paren
suffix:semicolon
id|sub_bus
op_assign
id|pciauto_bus_scan
c_func
(paren
id|hose
comma
id|sub_bus
op_plus
l_int|1
)paren
suffix:semicolon
id|pciauto_postscan_setup_bridge
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|sub_bus
comma
op_amp
id|iosave
comma
op_amp
id|memsave
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|pci_class
op_rshift
l_int|16
)paren
op_eq
id|PCI_CLASS_BRIDGE_CARDBUS
)paren
(brace
r_int
id|iosave
comma
id|memsave
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI Autoconfig: Found CardBus bridge, device %d function %d&bslash;n&quot;
comma
id|PCI_SLOT
c_func
(paren
id|pci_devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|pci_devfn
)paren
)paren
suffix:semicolon
multiline_comment|/* Place CardBus Socket/ExCA registers */
id|pciauto_setup_bars
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_BASE_ADDRESS_0
)paren
suffix:semicolon
id|pciauto_prescan_setup_cardbus_bridge
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|sub_bus
comma
op_amp
id|iosave
comma
op_amp
id|memsave
)paren
suffix:semicolon
id|sub_bus
op_assign
id|pciauto_bus_scan
c_func
(paren
id|hose
comma
id|sub_bus
op_plus
l_int|1
)paren
suffix:semicolon
id|pciauto_postscan_setup_cardbus_bridge
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|sub_bus
comma
op_amp
id|iosave
comma
op_amp
id|memsave
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|pci_class
op_rshift
l_int|16
)paren
op_eq
id|PCI_CLASS_STORAGE_IDE
)paren
(brace
r_int
r_char
id|prg_iface
suffix:semicolon
id|early_read_config_byte
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_CLASS_PROG
comma
op_amp
id|prg_iface
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|prg_iface
op_amp
id|PCIAUTO_IDE_MODE_MASK
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;PCI Autoconfig: Skipping legacy mode IDE controller&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
multiline_comment|/* Allocate PCI I/O and/or memory space */
id|pciauto_setup_bars
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_BASE_ADDRESS_5
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Enable some standard settings&n;&t;&t;&t;&t; */
id|early_read_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_COMMAND
comma
op_amp
id|cmdstat
)paren
suffix:semicolon
id|early_write_config_dword
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_COMMAND
comma
id|cmdstat
op_or
id|PCI_COMMAND_IO
op_or
id|PCI_COMMAND_MEMORY
op_or
id|PCI_COMMAND_MASTER
)paren
suffix:semicolon
id|early_write_config_byte
c_func
(paren
id|hose
comma
id|current_bus
comma
id|pci_devfn
comma
id|PCI_LATENCY_TIMER
comma
l_int|0x80
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|sub_bus
suffix:semicolon
)brace
eof
