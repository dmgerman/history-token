multiline_comment|/*&n; *  pci_link.c - ACPI PCI Interrupt Link Device Driver ($Revision: 33 $)&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *  Copyright (C) 2002       Dominik Brodowski &lt;devel@brodo.de&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; * TBD: &n; *      1. Support more than one IRQ resource entry per link device (index).&n; *&t;2. Implement start/stop mechanism and use ACPI Bus Driver facilities&n; *&t;   for IRQ management (e.g. start()-&gt;_SRS).&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;acpi_bus.h&quot;
macro_line|#include &quot;acpi_drivers.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_PCI_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;pci_link&quot;
)paren
DECL|macro|PREFIX
mdefine_line|#define PREFIX&t;&t;&t;&quot;ACPI: &quot;
DECL|macro|ACPI_PCI_LINK_MAX_POSSIBLE
mdefine_line|#define ACPI_PCI_LINK_MAX_POSSIBLE 16
r_static
r_int
id|acpi_pci_link_add
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
r_static
r_int
id|acpi_pci_link_remove
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|type
)paren
suffix:semicolon
DECL|variable|acpi_pci_link_driver
r_static
r_struct
id|acpi_driver
id|acpi_pci_link_driver
op_assign
(brace
id|name
suffix:colon
id|ACPI_PCI_LINK_DRIVER_NAME
comma
r_class
suffix:colon
id|ACPI_PCI_LINK_CLASS
comma
id|ids
suffix:colon
id|ACPI_PCI_LINK_HID
comma
id|ops
suffix:colon
(brace
id|add
suffix:colon
id|acpi_pci_link_add
comma
id|remove
suffix:colon
id|acpi_pci_link_remove
comma
)brace
comma
)brace
suffix:semicolon
DECL|struct|acpi_pci_link_irq
r_struct
id|acpi_pci_link_irq
(brace
DECL|member|active
id|u8
id|active
suffix:semicolon
multiline_comment|/* Current IRQ */
DECL|member|possible_count
id|u8
id|possible_count
suffix:semicolon
DECL|member|possible
id|u8
id|possible
(braket
id|ACPI_PCI_LINK_MAX_POSSIBLE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_pci_link
r_struct
id|acpi_pci_link
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|device
r_struct
id|acpi_device
op_star
id|device
suffix:semicolon
DECL|member|handle
id|acpi_handle
id|handle
suffix:semicolon
DECL|member|irq
r_struct
id|acpi_pci_link_irq
id|irq
suffix:semicolon
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|entries
r_struct
id|list_head
id|entries
suffix:semicolon
DECL|variable|acpi_link
)brace
id|acpi_link
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;                            PCI Link Device Management&n;   -------------------------------------------------------------------------- */
r_static
r_int
DECL|function|acpi_pci_link_get_possible
id|acpi_pci_link_get_possible
(paren
r_struct
id|acpi_pci_link
op_star
id|link
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|acpi_buffer
id|buffer
op_assign
(brace
id|ACPI_ALLOCATE_BUFFER
comma
l_int|NULL
)brace
suffix:semicolon
id|acpi_resource
op_star
id|resource
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_link_get_possible&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|status
op_assign
id|acpi_get_possible_resources
c_func
(paren
id|link-&gt;handle
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
op_logical_or
op_logical_neg
id|buffer.pointer
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Error evaluating _PRS&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|resource
op_assign
(paren
id|acpi_resource
op_star
)paren
id|buffer.pointer
suffix:semicolon
multiline_comment|/* skip past dependent function resource (if present) */
r_if
c_cond
(paren
id|resource-&gt;id
op_eq
id|ACPI_RSTYPE_START_DPF
)paren
id|resource
op_assign
id|ACPI_NEXT_RESOURCE
c_func
(paren
id|resource
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|resource-&gt;id
)paren
(brace
r_case
id|ACPI_RSTYPE_IRQ
suffix:colon
(brace
id|acpi_resource_irq
op_star
id|p
op_assign
op_amp
id|resource-&gt;data.irq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
id|p-&gt;number_of_interrupts
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Blank IRQ resource&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|p-&gt;number_of_interrupts
op_logical_and
id|i
OL
id|ACPI_PCI_LINK_MAX_POSSIBLE
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;interrupts
(braket
id|i
)braket
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Invalid IRQ %d&bslash;n&quot;
comma
id|p-&gt;interrupts
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|link-&gt;irq.possible
(braket
id|i
)braket
op_assign
id|p-&gt;interrupts
(braket
id|i
)braket
suffix:semicolon
id|link-&gt;irq.possible_count
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|ACPI_RSTYPE_EXT_IRQ
suffix:colon
(brace
id|acpi_resource_ext_irq
op_star
id|p
op_assign
op_amp
id|resource-&gt;data.extended_irq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
id|p-&gt;number_of_interrupts
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Blank IRQ resource&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|p-&gt;number_of_interrupts
op_logical_and
id|i
OL
id|ACPI_PCI_LINK_MAX_POSSIBLE
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;interrupts
(braket
id|i
)braket
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Invalid IRQ %d&bslash;n&quot;
comma
id|p-&gt;interrupts
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|link-&gt;irq.possible
(braket
id|i
)braket
op_assign
id|p-&gt;interrupts
(braket
id|i
)braket
suffix:semicolon
id|link-&gt;irq.possible_count
op_increment
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Resource is not an IRQ entry&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Found %d possible IRQs&bslash;n&quot;
comma
id|link-&gt;irq.possible_count
)paren
)paren
suffix:semicolon
id|end
suffix:colon
id|acpi_os_free
c_func
(paren
id|buffer.pointer
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_pci_link_get_current
id|acpi_pci_link_get_current
(paren
r_struct
id|acpi_pci_link
op_star
id|link
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|acpi_buffer
id|buffer
op_assign
(brace
id|ACPI_ALLOCATE_BUFFER
comma
l_int|NULL
)brace
suffix:semicolon
id|acpi_resource
op_star
id|resource
op_assign
l_int|NULL
suffix:semicolon
r_int
id|irq
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_link_get_current&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link
op_logical_or
op_logical_neg
id|link-&gt;handle
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|link-&gt;irq.active
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Make sure the link is enabled (no use querying if it isn&squot;t). */
id|result
op_assign
id|acpi_bus_get_status
c_func
(paren
id|link-&gt;device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unable to read status&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|link-&gt;device-&gt;status.enabled
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Link disabled&bslash;n&quot;
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
multiline_comment|/* &n;&t; * Query and parse _CRS to get the current IRQ assignment. &n;&t; */
id|status
op_assign
id|acpi_get_current_resources
c_func
(paren
id|link-&gt;handle
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
l_string|&quot;Error evaluating _CRS&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|resource
op_assign
(paren
id|acpi_resource
op_star
)paren
id|buffer.pointer
suffix:semicolon
r_switch
c_cond
(paren
id|resource-&gt;id
)paren
(brace
r_case
id|ACPI_RSTYPE_IRQ
suffix:colon
(brace
id|acpi_resource_irq
op_star
id|p
op_assign
op_amp
id|resource-&gt;data.irq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
id|p-&gt;number_of_interrupts
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Blank IRQ resource&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|irq
op_assign
id|p-&gt;interrupts
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|ACPI_RSTYPE_EXT_IRQ
suffix:colon
(brace
id|acpi_resource_ext_irq
op_star
id|p
op_assign
op_amp
id|resource-&gt;data.extended_irq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
id|p-&gt;number_of_interrupts
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Blank IRQ resource&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|irq
op_assign
id|p-&gt;interrupts
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Resource isn&squot;t an IRQ&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|irq
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid use of IRQ 0&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Note that we don&squot;t validate that the current IRQ (_CRS) exists&n;&t; * within the possible IRQs (_PRS): we blindly assume that whatever&n;&t; * IRQ a boot-enabled Link device is set to is the correct one.&n;&t; * (Required to support systems such as the Toshiba 5005-S504.)&n;&t; */
id|link-&gt;irq.active
op_assign
id|irq
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Link at IRQ %d &bslash;n&quot;
comma
id|link-&gt;irq.active
)paren
)paren
suffix:semicolon
id|end
suffix:colon
id|acpi_os_free
c_func
(paren
id|buffer.pointer
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_pci_link_set
id|acpi_pci_link_set
(paren
r_struct
id|acpi_pci_link
op_star
id|link
comma
r_int
id|irq
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
(brace
id|acpi_resource
id|res
suffix:semicolon
id|acpi_resource
id|end
suffix:semicolon
)brace
id|resource
suffix:semicolon
id|acpi_buffer
id|buffer
op_assign
(brace
r_sizeof
(paren
id|resource
)paren
op_plus
l_int|1
comma
op_amp
id|resource
)brace
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|valid
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_link_set&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link
op_logical_or
op_logical_neg
id|irq
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* See if we&squot;re already at the target IRQ. */
r_if
c_cond
(paren
id|irq
op_eq
id|link-&gt;irq.active
)paren
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Make sure the target IRQ in the list of possible IRQs. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|link-&gt;irq.possible_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|irq
op_eq
id|link-&gt;irq.possible
(braket
id|i
)braket
)paren
id|valid
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|valid
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Target IRQ %d invalid&bslash;n&quot;
comma
id|irq
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|resource
comma
l_int|0
comma
r_sizeof
(paren
id|resource
)paren
)paren
suffix:semicolon
multiline_comment|/* NOTE: PCI interrupts are always level / active_low / shared. */
id|resource.res.id
op_assign
id|ACPI_RSTYPE_IRQ
suffix:semicolon
id|resource.res.length
op_assign
r_sizeof
(paren
id|acpi_resource
)paren
suffix:semicolon
id|resource.res.data.irq.edge_level
op_assign
id|ACPI_LEVEL_SENSITIVE
suffix:semicolon
id|resource.res.data.irq.active_high_low
op_assign
id|ACPI_ACTIVE_LOW
suffix:semicolon
id|resource.res.data.irq.shared_exclusive
op_assign
id|ACPI_SHARED
suffix:semicolon
id|resource.res.data.irq.number_of_interrupts
op_assign
l_int|1
suffix:semicolon
id|resource.res.data.irq.interrupts
(braket
l_int|0
)braket
op_assign
id|irq
suffix:semicolon
id|resource.end.id
op_assign
id|ACPI_RSTYPE_END_TAG
suffix:semicolon
id|status
op_assign
id|acpi_set_current_resources
c_func
(paren
id|link-&gt;handle
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
l_string|&quot;Error evaluating _SRS&bslash;n&quot;
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
multiline_comment|/* Make sure the device is enabled. */
id|result
op_assign
id|acpi_bus_get_status
c_func
(paren
id|link-&gt;device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unable to read status&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|link-&gt;device-&gt;status.enabled
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Link disabled&bslash;n&quot;
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
multiline_comment|/* Make sure the active IRQ is the one we requested. */
id|result
op_assign
id|acpi_pci_link_get_current
c_func
(paren
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|link-&gt;irq.active
op_ne
id|irq
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Attempt to enable at IRQ %d resulted in IRQ %d&bslash;n&quot;
comma
id|irq
comma
id|link-&gt;irq.active
)paren
)paren
suffix:semicolon
id|link-&gt;irq.active
op_assign
l_int|0
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Set IRQ %d&bslash;n&quot;
comma
id|link-&gt;irq.active
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
multiline_comment|/* --------------------------------------------------------------------------&n;                            PCI Link IRQ Management&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_MAX_IRQS
mdefine_line|#define ACPI_MAX_IRQS&t;&t;256
DECL|macro|ACPI_MAX_ISA_IRQ
mdefine_line|#define ACPI_MAX_ISA_IRQ&t;16
multiline_comment|/*&n; * IRQ penalties are used to promote PCI IRQ balancing.  We set each ISA-&n; * possible IRQ (0-15) with a default penalty relative to its feasibility&n; * for PCI&squot;s use:&n; *&n; *   Never use:&t;&t;0, 1, 2 (timer, keyboard, and cascade)&n; *   Avoid using:&t;13, 14, and 15 (FP error and IDE)&n; *   Penalize:&t;&t;3, 4, 6, 7, 12 (known ISA uses)&n; *&n; * Thus we&squot;re left with IRQs 5, 9, 10, 11, and everything above 15 (IO[S]APIC)&n; * as &squot;best bets&squot; for PCI use.&n; */
DECL|variable|acpi_irq_penalty
r_static
r_int
id|acpi_irq_penalty
(braket
id|ACPI_MAX_IRQS
)braket
op_assign
(brace
l_int|1000000
comma
l_int|1000000
comma
l_int|1000000
comma
l_int|10000
comma
l_int|10000
comma
l_int|0
comma
l_int|10000
comma
l_int|10000
comma
l_int|10000
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|10000
comma
l_int|100000
comma
l_int|100000
comma
l_int|100000
comma
)brace
suffix:semicolon
r_int
DECL|function|acpi_pci_link_check
id|acpi_pci_link_check
(paren
r_void
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
id|acpi_pci_link
op_star
id|link
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_link_check&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Pass #1: Update penalties to facilitate IRQ balancing.&n;&t; */
id|list_for_each
c_func
(paren
id|node
comma
op_amp
id|acpi_link.entries
)paren
(brace
id|link
op_assign
id|list_entry
c_func
(paren
id|node
comma
r_struct
id|acpi_pci_link
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid link context&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|link-&gt;irq.active
)paren
id|acpi_irq_penalty
(braket
id|link-&gt;irq.active
)braket
op_add_assign
l_int|100
suffix:semicolon
r_else
r_if
c_cond
(paren
id|link-&gt;irq.possible_count
)paren
(brace
r_int
id|penalty
op_assign
l_int|100
op_div
id|link-&gt;irq.possible_count
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
id|link-&gt;irq.possible_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|link-&gt;irq.possible
(braket
id|i
)braket
OL
id|ACPI_MAX_ISA_IRQ
)paren
id|acpi_irq_penalty
(braket
id|link-&gt;irq.possible
(braket
id|i
)braket
)braket
op_add_assign
id|penalty
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;&t; * Pass #2: Enable boot-disabled Links at &squot;best&squot; IRQ.&n;&t; */
id|list_for_each
c_func
(paren
id|node
comma
op_amp
id|acpi_link.entries
)paren
(brace
r_int
id|irq
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|link
op_assign
id|list_entry
c_func
(paren
id|node
comma
r_struct
id|acpi_pci_link
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link
op_logical_or
op_logical_neg
id|link-&gt;irq.possible_count
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid link context&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|link-&gt;irq.active
)paren
r_continue
suffix:semicolon
id|irq
op_assign
id|link-&gt;irq.possible
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* &n;&t;&t; * Select the best IRQ.  This is done in reverse to promote &n;&t;&t; * the use of IRQs 9, 10, 11, and &gt;15.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
(paren
id|link-&gt;irq.possible_count
op_minus
l_int|1
)paren
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|acpi_irq_penalty
(braket
id|irq
)braket
OG
id|acpi_irq_penalty
(braket
id|link-&gt;irq.possible
(braket
id|i
)braket
)braket
)paren
id|irq
op_assign
id|link-&gt;irq.possible
(braket
id|i
)braket
suffix:semicolon
)brace
multiline_comment|/* Enable the link device at this IRQ. */
id|acpi_pci_link_set
c_func
(paren
id|link
comma
id|irq
)paren
suffix:semicolon
id|acpi_irq_penalty
(braket
id|link-&gt;irq.active
)braket
op_add_assign
l_int|100
suffix:semicolon
id|printk
c_func
(paren
id|PREFIX
l_string|&quot;%s [%s] enabled at IRQ %d&bslash;n&quot;
comma
id|acpi_device_name
c_func
(paren
id|link-&gt;device
)paren
comma
id|acpi_device_bid
c_func
(paren
id|link-&gt;device
)paren
comma
id|link-&gt;irq.active
)paren
suffix:semicolon
)brace
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|acpi_pci_link_get_irq
id|acpi_pci_link_get_irq
(paren
id|acpi_handle
id|handle
comma
r_int
id|index
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_device
op_star
id|device
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_pci_link
op_star
id|link
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_link_get_irq&quot;
)paren
suffix:semicolon
id|result
op_assign
id|acpi_bus_get_device
c_func
(paren
id|handle
comma
op_amp
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid link device&bslash;n&quot;
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
id|link
op_assign
(paren
r_struct
id|acpi_pci_link
op_star
)paren
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid link context&bslash;n&quot;
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
multiline_comment|/* TBD: Support multiple index (IRQ) entries per Link Device */
r_if
c_cond
(paren
id|index
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid index %d&bslash;n&quot;
comma
id|index
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
r_if
c_cond
(paren
op_logical_neg
id|link-&gt;irq.active
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Link disabled&bslash;n&quot;
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
id|return_VALUE
c_func
(paren
id|link-&gt;irq.active
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;                                 Driver Interface&n;   -------------------------------------------------------------------------- */
r_static
r_int
DECL|function|acpi_pci_link_add
id|acpi_pci_link_add
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_pci_link
op_star
id|link
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_link_add&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|link
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|acpi_pci_link
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|link
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
id|link
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|acpi_pci_link
)paren
)paren
suffix:semicolon
id|link-&gt;device
op_assign
id|device
suffix:semicolon
id|link-&gt;handle
op_assign
id|device-&gt;handle
suffix:semicolon
id|sprintf
c_func
(paren
id|acpi_device_name
c_func
(paren
id|device
)paren
comma
l_string|&quot;%s&quot;
comma
id|ACPI_PCI_LINK_DEVICE_NAME
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|acpi_device_class
c_func
(paren
id|device
)paren
comma
l_string|&quot;%s&quot;
comma
id|ACPI_PCI_LINK_CLASS
)paren
suffix:semicolon
id|acpi_driver_data
c_func
(paren
id|device
)paren
op_assign
id|link
suffix:semicolon
id|result
op_assign
id|acpi_pci_link_get_possible
c_func
(paren
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|end
suffix:semicolon
id|acpi_pci_link_get_current
c_func
(paren
id|link
)paren
suffix:semicolon
id|printk
c_func
(paren
id|PREFIX
l_string|&quot;%s [%s] (IRQs&quot;
comma
id|acpi_device_name
c_func
(paren
id|device
)paren
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
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
id|link-&gt;irq.possible_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|link-&gt;irq.active
op_eq
id|link-&gt;irq.possible
(braket
id|i
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; *%d&quot;
comma
id|link-&gt;irq.possible
(braket
id|i
)braket
)paren
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot; %d&quot;
comma
id|link-&gt;irq.possible
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|link-&gt;irq.active
)paren
id|printk
c_func
(paren
l_string|&quot;, disabled&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
id|printk
c_func
(paren
l_string|&quot;, enabled at IRQ %d&quot;
comma
id|link-&gt;irq.active
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;)&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* TBD: Acquire/release lock */
id|list_add_tail
c_func
(paren
op_amp
id|link-&gt;node
comma
op_amp
id|acpi_link.entries
)paren
suffix:semicolon
id|acpi_link.count
op_increment
suffix:semicolon
id|end
suffix:colon
r_if
c_cond
(paren
id|result
)paren
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_pci_link_remove
id|acpi_pci_link_remove
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|type
)paren
(brace
r_struct
id|acpi_pci_link
op_star
id|link
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_link_remove&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
op_logical_or
op_logical_neg
id|acpi_driver_data
c_func
(paren
id|device
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|link
op_assign
(paren
r_struct
id|acpi_pci_link
op_star
)paren
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
multiline_comment|/* TBD: Acquire/release lock */
id|list_del
c_func
(paren
op_amp
id|link-&gt;node
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|acpi_pci_link_init
id|acpi_pci_link_init
(paren
r_void
)paren
(brace
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_link_init&quot;
)paren
suffix:semicolon
id|acpi_link.count
op_assign
l_int|0
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|acpi_link.entries
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_bus_register_driver
c_func
(paren
op_amp
id|acpi_pci_link_driver
)paren
OL
l_int|0
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
