multiline_comment|/*&n; *  pci_irq.c - ACPI PCI Interrupt Routing ($Revision: 11 $)&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *  Copyright (C) 2002       Dominik Brodowski &lt;devel@brodo.de&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;acpi/acpi_bus.h&gt;
macro_line|#include &lt;acpi/acpi_drivers.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_PCI_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;pci_irq&quot;
)paren
DECL|variable|acpi_prt
r_struct
id|acpi_prt_list
id|acpi_prt
suffix:semicolon
DECL|variable|acpi_prt_lock
id|spinlock_t
id|acpi_prt_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;                         PCI IRQ Routing Table (PRT) Support&n;   -------------------------------------------------------------------------- */
r_static
r_struct
id|acpi_prt_entry
op_star
DECL|function|acpi_pci_irq_find_prt_entry
id|acpi_pci_irq_find_prt_entry
(paren
r_int
id|segment
comma
r_int
id|bus
comma
r_int
id|device
comma
r_int
id|pin
)paren
(brace
r_struct
id|list_head
op_star
id|node
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_prt_entry
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_irq_find_prt_entry&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_prt.count
)paren
id|return_PTR
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Parse through all PRT entries looking for a match on the specified&n;&t; * PCI device&squot;s segment, bus, device, and pin (don&squot;t care about func).&n;&t; *&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|acpi_prt_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|node
comma
op_amp
id|acpi_prt.entries
)paren
(brace
id|entry
op_assign
id|list_entry
c_func
(paren
id|node
comma
r_struct
id|acpi_prt_entry
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|segment
op_eq
id|entry-&gt;id.segment
)paren
op_logical_and
(paren
id|bus
op_eq
id|entry-&gt;id.bus
)paren
op_logical_and
(paren
id|device
op_eq
id|entry-&gt;id.device
)paren
op_logical_and
(paren
id|pin
op_eq
id|entry-&gt;pin
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|acpi_prt_lock
)paren
suffix:semicolon
id|return_PTR
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|acpi_prt_lock
)paren
suffix:semicolon
id|return_PTR
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_pci_irq_add_entry
id|acpi_pci_irq_add_entry
(paren
id|acpi_handle
id|handle
comma
r_int
id|segment
comma
r_int
id|bus
comma
r_struct
id|acpi_pci_routing_table
op_star
id|prt
)paren
(brace
r_struct
id|acpi_prt_entry
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_irq_add_entry&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prt
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|entry
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|acpi_prt_entry
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|memset
c_func
(paren
id|entry
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|acpi_prt_entry
)paren
)paren
suffix:semicolon
id|entry-&gt;id.segment
op_assign
id|segment
suffix:semicolon
id|entry-&gt;id.bus
op_assign
id|bus
suffix:semicolon
id|entry-&gt;id.device
op_assign
(paren
id|prt-&gt;address
op_rshift
l_int|16
)paren
op_amp
l_int|0xFFFF
suffix:semicolon
id|entry-&gt;id.function
op_assign
id|prt-&gt;address
op_amp
l_int|0xFFFF
suffix:semicolon
id|entry-&gt;pin
op_assign
id|prt-&gt;pin
suffix:semicolon
multiline_comment|/*&n;&t; * Type 1: Dynamic&n;&t; * ---------------&n;&t; * The &squot;source&squot; field specifies the PCI interrupt link device used to&n;&t; * configure the IRQ assigned to this slot|dev|pin.  The &squot;source_index&squot;&n;&t; * indicates which resource descriptor in the resource template (of&n;&t; * the link device) this interrupt is allocated from.&n;&t; * &n;&t; * NOTE: Don&squot;t query the Link Device for IRQ information at this time&n;&t; *       because Link Device enumeration may not have occurred yet&n;&t; *       (e.g. exists somewhere &squot;below&squot; this _PRT entry in the ACPI&n;&t; *       namespace).&n;&t; */
r_if
c_cond
(paren
id|prt-&gt;source
(braket
l_int|0
)braket
)paren
(brace
id|acpi_get_handle
c_func
(paren
id|handle
comma
id|prt-&gt;source
comma
op_amp
id|entry-&gt;link.handle
)paren
suffix:semicolon
id|entry-&gt;link.index
op_assign
id|prt-&gt;source_index
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Type 2: Static&n;&t; * --------------&n;&t; * The &squot;source&squot; field is NULL, and the &squot;source_index&squot; field specifies&n;&t; * the IRQ value, which is hardwired to specific interrupt inputs on&n;&t; * the interrupt controller.&n;&t; */
r_else
id|entry-&gt;link.index
op_assign
id|prt-&gt;source_index
suffix:semicolon
id|ACPI_DEBUG_PRINT_RAW
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;      %02X:%02X:%02X[%c] -&gt; %s[%d]&bslash;n&quot;
comma
id|entry-&gt;id.segment
comma
id|entry-&gt;id.bus
comma
id|entry-&gt;id.device
comma
(paren
l_char|&squot;A&squot;
op_plus
id|entry-&gt;pin
)paren
comma
id|prt-&gt;source
comma
id|entry-&gt;link.index
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acpi_prt_lock
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|entry-&gt;node
comma
op_amp
id|acpi_prt.entries
)paren
suffix:semicolon
id|acpi_prt.count
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|acpi_prt_lock
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|acpi_pci_irq_del_entry
id|acpi_pci_irq_del_entry
(paren
r_int
id|segment
comma
r_int
id|bus
comma
r_struct
id|acpi_prt_entry
op_star
id|entry
)paren
(brace
r_if
c_cond
(paren
id|segment
op_eq
id|entry-&gt;id.segment
op_logical_and
id|bus
op_eq
id|entry-&gt;id.bus
)paren
(brace
id|acpi_prt.count
op_decrement
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|entry-&gt;node
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
)brace
r_int
DECL|function|acpi_pci_irq_add_prt
id|acpi_pci_irq_add_prt
(paren
id|acpi_handle
id|handle
comma
r_int
id|segment
comma
r_int
id|bus
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_char
op_star
id|pathname
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_buffer
id|buffer
op_assign
(brace
l_int|0
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|acpi_pci_routing_table
op_star
id|prt
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_pci_routing_table
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
id|first_time
op_assign
l_int|1
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_irq_add_prt&quot;
)paren
suffix:semicolon
id|pathname
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|ACPI_PATHNAME_MAX
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pathname
)paren
(brace
id|return_VALUE
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|pathname
comma
l_int|0
comma
id|ACPI_PATHNAME_MAX
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first_time
)paren
(brace
id|acpi_prt.count
op_assign
l_int|0
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|acpi_prt.entries
)paren
suffix:semicolon
id|first_time
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * NOTE: We&squot;re given a &squot;handle&squot; to the _PRT object&squot;s parent device&n;&t; *       (either a PCI root bridge or PCI-PCI bridge).&n;&t; */
id|buffer.length
op_assign
id|ACPI_PATHNAME_MAX
suffix:semicolon
id|buffer.pointer
op_assign
id|pathname
suffix:semicolon
id|acpi_get_name
c_func
(paren
id|handle
comma
id|ACPI_FULL_PATHNAME
comma
op_amp
id|buffer
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ACPI: PCI Interrupt Routing Table [%s._PRT]&bslash;n&quot;
comma
id|pathname
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Evaluate this _PRT and add its entries to our global list (acpi_prt).&n;&t; */
id|buffer.length
op_assign
l_int|0
suffix:semicolon
id|buffer.pointer
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|pathname
)paren
suffix:semicolon
id|status
op_assign
id|acpi_get_irq_routing_table
c_func
(paren
id|handle
comma
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|AE_BUFFER_OVERFLOW
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Error evaluating _PRT [%s]&bslash;n&quot;
comma
id|acpi_format_exception
c_func
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|prt
op_assign
id|kmalloc
c_func
(paren
id|buffer.length
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prt
)paren
(brace
id|return_VALUE
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|prt
comma
l_int|0
comma
id|buffer.length
)paren
suffix:semicolon
id|buffer.pointer
op_assign
id|prt
suffix:semicolon
id|status
op_assign
id|acpi_get_irq_routing_table
c_func
(paren
id|handle
comma
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Error evaluating _PRT [%s]&bslash;n&quot;
comma
id|acpi_format_exception
c_func
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer.pointer
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|entry
op_assign
id|prt
suffix:semicolon
r_while
c_loop
(paren
id|entry
op_logical_and
(paren
id|entry-&gt;length
OG
l_int|0
)paren
)paren
(brace
id|acpi_pci_irq_add_entry
c_func
(paren
id|handle
comma
id|segment
comma
id|bus
comma
id|entry
)paren
suffix:semicolon
id|entry
op_assign
(paren
r_struct
id|acpi_pci_routing_table
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|entry
op_plus
id|entry-&gt;length
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|prt
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|acpi_pci_irq_del_prt
id|acpi_pci_irq_del_prt
(paren
r_int
id|segment
comma
r_int
id|bus
)paren
(brace
r_struct
id|list_head
op_star
id|node
op_assign
l_int|NULL
comma
op_star
id|n
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_prt_entry
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_prt.count
)paren
(brace
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ACPI: Delete PCI Interrupt Routing Table for %x:%x&bslash;n&quot;
comma
id|segment
comma
id|bus
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|acpi_prt_lock
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|node
comma
id|n
comma
op_amp
id|acpi_prt.entries
)paren
(brace
id|entry
op_assign
id|list_entry
c_func
(paren
id|node
comma
r_struct
id|acpi_prt_entry
comma
id|node
)paren
suffix:semicolon
id|acpi_pci_irq_del_entry
c_func
(paren
id|segment
comma
id|bus
comma
id|entry
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|acpi_prt_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;                          PCI Interrupt Routing Support&n;   -------------------------------------------------------------------------- */
multiline_comment|/*&n; * acpi_pci_irq_lookup&n; * success: return IRQ &gt;= 0&n; * failure: return -1&n; */
r_static
r_int
DECL|function|acpi_pci_irq_lookup
id|acpi_pci_irq_lookup
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
id|device
comma
r_int
id|pin
comma
r_int
op_star
id|edge_level
comma
r_int
op_star
id|active_high_low
comma
r_char
op_star
op_star
id|link
)paren
(brace
r_struct
id|acpi_prt_entry
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
r_int
id|segment
op_assign
id|pci_domain_nr
c_func
(paren
id|bus
)paren
suffix:semicolon
r_int
id|bus_nr
op_assign
id|bus-&gt;number
suffix:semicolon
r_int
id|irq
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_irq_lookup&quot;
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Searching for PRT entry for %02x:%02x:%02x[%c]&bslash;n&quot;
comma
id|segment
comma
id|bus_nr
comma
id|device
comma
(paren
l_char|&squot;A&squot;
op_plus
id|pin
)paren
)paren
)paren
suffix:semicolon
id|entry
op_assign
id|acpi_pci_irq_find_prt_entry
c_func
(paren
id|segment
comma
id|bus_nr
comma
id|device
comma
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;PRT entry not found&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|entry-&gt;link.handle
)paren
(brace
id|irq
op_assign
id|acpi_pci_link_get_irq
c_func
(paren
id|entry-&gt;link.handle
comma
id|entry-&gt;link.index
comma
id|edge_level
comma
id|active_high_low
comma
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
l_int|0
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Invalid IRQ link routing entry&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|irq
op_assign
id|entry-&gt;link.index
suffix:semicolon
op_star
id|edge_level
op_assign
id|ACPI_LEVEL_SENSITIVE
suffix:semicolon
op_star
id|active_high_low
op_assign
id|ACPI_ACTIVE_LOW
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Found IRQ %d&bslash;n&quot;
comma
id|irq
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * acpi_pci_irq_derive&n; * success: return IRQ &gt;= 0&n; * failure: return &lt; 0&n; */
r_static
r_int
DECL|function|acpi_pci_irq_derive
id|acpi_pci_irq_derive
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|pin
comma
r_int
op_star
id|edge_level
comma
r_int
op_star
id|active_high_low
comma
r_char
op_star
op_star
id|link
)paren
(brace
r_struct
id|pci_dev
op_star
id|bridge
op_assign
id|dev
suffix:semicolon
r_int
id|irq
op_assign
op_minus
l_int|1
suffix:semicolon
id|u8
id|bridge_pin
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_irq_derive&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Attempt to derive an IRQ for this device from a parent bridge&squot;s&n;&t; * PCI interrupt routing entry (eg. yenta bridge and add-in card bridge).&n;&t; */
r_while
c_loop
(paren
id|irq
OL
l_int|0
op_logical_and
id|bridge-&gt;bus-&gt;self
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
id|bridge-&gt;devfn
)paren
)paren
op_mod
l_int|4
suffix:semicolon
id|bridge
op_assign
id|bridge-&gt;bus-&gt;self
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bridge
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_eq
id|PCI_CLASS_BRIDGE_CARDBUS
)paren
(brace
multiline_comment|/* PC card has the same IRQ as its cardbridge */
id|pci_read_config_byte
c_func
(paren
id|bridge
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|bridge_pin
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bridge_pin
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;No interrupt pin configured for device %s&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|bridge
)paren
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Pin is from 0 to 3 */
id|bridge_pin
op_decrement
suffix:semicolon
id|pin
op_assign
id|bridge_pin
suffix:semicolon
)brace
id|irq
op_assign
id|acpi_pci_irq_lookup
c_func
(paren
id|bridge-&gt;bus
comma
id|PCI_SLOT
c_func
(paren
id|bridge-&gt;devfn
)paren
comma
id|pin
comma
id|edge_level
comma
id|active_high_low
comma
id|link
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
OL
l_int|0
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Unable to derive IRQ for device %s&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Derive IRQ %d for device %s from %s&bslash;n&quot;
comma
id|irq
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|pci_name
c_func
(paren
id|bridge
)paren
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * acpi_pci_irq_enable&n; * success: return 0&n; * failure: return &lt; 0&n; */
r_int
DECL|function|acpi_pci_irq_enable
id|acpi_pci_irq_enable
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|irq
op_assign
l_int|0
suffix:semicolon
id|u8
id|pin
op_assign
l_int|0
suffix:semicolon
r_int
id|edge_level
op_assign
id|ACPI_LEVEL_SENSITIVE
suffix:semicolon
r_int
id|active_high_low
op_assign
id|ACPI_ACTIVE_LOW
suffix:semicolon
r_extern
r_int
id|via_interrupt_line_quirk
suffix:semicolon
r_char
op_star
id|link
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_irq_enable&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pin
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;No interrupt pin configured for device %s&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|pin
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;bus
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid (NULL) &squot;bus&squot; field&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * First we check the PCI IRQ routing table (PRT) for an IRQ.  PRT&n;&t; * values override any BIOS-assigned IRQs set during boot.&n;&t; */
id|irq
op_assign
id|acpi_pci_irq_lookup
c_func
(paren
id|dev-&gt;bus
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|pin
comma
op_amp
id|edge_level
comma
op_amp
id|active_high_low
comma
op_amp
id|link
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If no PRT entry was found, we&squot;ll try to derive an IRQ from the&n;&t; * device&squot;s parent bridge.&n;&t; */
r_if
c_cond
(paren
id|irq
OL
l_int|0
)paren
id|irq
op_assign
id|acpi_pci_irq_derive
c_func
(paren
id|dev
comma
id|pin
comma
op_amp
id|edge_level
comma
op_amp
id|active_high_low
comma
op_amp
id|link
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * No IRQ known to the ACPI subsystem - maybe the BIOS / &n;&t; * driver reported one, then use it. Exit in any case.&n;&t; */
r_if
c_cond
(paren
id|irq
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;PCI Interrupt %s[%c]: no GSI&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
(paren
l_char|&squot;A&squot;
op_plus
id|pin
)paren
)paren
suffix:semicolon
multiline_comment|/* Interrupt Line values above 0xF are forbidden */
r_if
c_cond
(paren
id|dev-&gt;irq
op_ge
l_int|0
op_logical_and
(paren
id|dev-&gt;irq
op_le
l_int|0xF
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; - using IRQ %d&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|via_interrupt_line_quirk
)paren
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|irq
op_amp
l_int|15
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|acpi_register_gsi
c_func
(paren
id|irq
comma
id|edge_level
comma
id|active_high_low
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;PCI Interrupt %s[%c] -&gt; &quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
l_char|&squot;A&squot;
op_plus
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link
)paren
id|printk
c_func
(paren
l_string|&quot;Link [%s] -&gt; &quot;
comma
id|link
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;GSI %u (%s, %s) -&gt; IRQ %d&bslash;n&quot;
comma
id|irq
comma
(paren
id|edge_level
op_eq
id|ACPI_LEVEL_SENSITIVE
)paren
ques
c_cond
l_string|&quot;level&quot;
suffix:colon
l_string|&quot;edge&quot;
comma
(paren
id|active_high_low
op_eq
id|ACPI_ACTIVE_LOW
)paren
ques
c_cond
l_string|&quot;low&quot;
suffix:colon
l_string|&quot;high&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|acpi_pci_irq_enable
id|EXPORT_SYMBOL
c_func
(paren
id|acpi_pci_irq_enable
)paren
suffix:semicolon
eof
