multiline_comment|/*&n; *  pci_root.c - ACPI PCI Root Bridge Driver ($Revision: 40 $)&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &quot;acpi_bus.h&quot;
macro_line|#include &quot;acpi_drivers.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_PCI_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;pci_root&quot;
)paren
r_extern
r_struct
id|pci_ops
op_star
id|pci_root_ops
suffix:semicolon
r_static
r_int
id|acpi_pci_root_add
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
r_static
r_int
id|acpi_pci_root_remove
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
DECL|variable|acpi_pci_root_driver
r_static
r_struct
id|acpi_driver
id|acpi_pci_root_driver
op_assign
(brace
dot
id|name
op_assign
id|ACPI_PCI_ROOT_DRIVER_NAME
comma
dot
r_class
op_assign
id|ACPI_PCI_ROOT_CLASS
comma
dot
id|ids
op_assign
id|ACPI_PCI_ROOT_HID
comma
dot
id|ops
op_assign
(brace
dot
id|add
op_assign
id|acpi_pci_root_add
comma
dot
id|remove
op_assign
id|acpi_pci_root_remove
comma
)brace
comma
)brace
suffix:semicolon
DECL|struct|acpi_pci_root
r_struct
id|acpi_pci_root
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|handle
id|acpi_handle
id|handle
suffix:semicolon
DECL|member|id
id|acpi_pci_id
id|id
suffix:semicolon
DECL|member|bus
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
DECL|member|mem_tra
id|u64
id|mem_tra
suffix:semicolon
DECL|member|io_tra
id|u64
id|io_tra
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|acpi_pci_roots
r_struct
id|list_head
id|acpi_pci_roots
suffix:semicolon
r_void
DECL|function|acpi_pci_get_translations
id|acpi_pci_get_translations
(paren
id|acpi_pci_id
op_star
id|id
comma
id|u64
op_star
id|mem_tra
comma
id|u64
op_star
id|io_tra
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
id|acpi_pci_root
op_star
id|entry
suffix:semicolon
multiline_comment|/* TBD: Locking */
id|list_for_each
c_func
(paren
id|node
comma
op_amp
id|acpi_pci_roots
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
id|acpi_pci_root
comma
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id-&gt;segment
op_eq
id|entry-&gt;id.segment
)paren
op_logical_and
(paren
id|id-&gt;bus
op_eq
id|entry-&gt;id.bus
)paren
)paren
(brace
op_star
id|mem_tra
op_assign
id|entry-&gt;mem_tra
suffix:semicolon
op_star
id|io_tra
op_assign
id|entry-&gt;io_tra
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
op_star
id|mem_tra
op_assign
l_int|0
suffix:semicolon
op_star
id|io_tra
op_assign
l_int|0
suffix:semicolon
)brace
r_static
id|u64
DECL|function|acpi_pci_root_bus_tra
id|acpi_pci_root_bus_tra
(paren
id|acpi_resource
op_star
id|resource
comma
r_int
id|type
)paren
(brace
id|acpi_resource_address16
op_star
id|address16
suffix:semicolon
id|acpi_resource_address32
op_star
id|address32
suffix:semicolon
id|acpi_resource_address64
op_star
id|address64
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_switch
c_cond
(paren
id|resource-&gt;id
)paren
(brace
r_case
id|ACPI_RSTYPE_END_TAG
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|ACPI_RSTYPE_ADDRESS16
suffix:colon
id|address16
op_assign
(paren
id|acpi_resource_address16
op_star
)paren
op_amp
id|resource-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|address16-&gt;resource_type
)paren
(brace
r_return
id|address16-&gt;address_translation_offset
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_ADDRESS32
suffix:colon
id|address32
op_assign
(paren
id|acpi_resource_address32
op_star
)paren
op_amp
id|resource-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|address32-&gt;resource_type
)paren
(brace
r_return
id|address32-&gt;address_translation_offset
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_ADDRESS64
suffix:colon
id|address64
op_assign
(paren
id|acpi_resource_address64
op_star
)paren
op_amp
id|resource-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|address64-&gt;resource_type
)paren
(brace
r_return
id|address64-&gt;address_translation_offset
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|resource
op_assign
id|ACPI_PTR_ADD
(paren
id|acpi_resource
comma
id|resource
comma
id|resource-&gt;length
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_pci_evaluate_crs
id|acpi_pci_evaluate_crs
(paren
r_struct
id|acpi_pci_root
op_star
id|root
)paren
(brace
id|acpi_status
id|status
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
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_evaluate_crs&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_get_current_resources
(paren
id|root-&gt;handle
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
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|root-&gt;io_tra
op_assign
id|acpi_pci_root_bus_tra
(paren
(paren
id|acpi_resource
op_star
)paren
id|buffer.pointer
comma
id|ACPI_IO_RANGE
)paren
suffix:semicolon
id|root-&gt;mem_tra
op_assign
id|acpi_pci_root_bus_tra
(paren
(paren
id|acpi_resource
op_star
)paren
id|buffer.pointer
comma
id|ACPI_MEMORY_RANGE
)paren
suffix:semicolon
id|acpi_os_free
c_func
(paren
id|buffer.pointer
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
r_int
DECL|function|acpi_pci_root_add
id|acpi_pci_root_add
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
id|acpi_pci_root
op_star
id|root
op_assign
l_int|NULL
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_int
r_int
id|value
op_assign
l_int|0
suffix:semicolon
id|acpi_handle
id|handle
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_root_add&quot;
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
id|root
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|acpi_pci_root
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root
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
id|root
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|acpi_pci_root
)paren
)paren
suffix:semicolon
id|root-&gt;handle
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
id|ACPI_PCI_ROOT_DEVICE_NAME
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
id|ACPI_PCI_ROOT_CLASS
)paren
suffix:semicolon
id|acpi_driver_data
c_func
(paren
id|device
)paren
op_assign
id|root
suffix:semicolon
multiline_comment|/*&n;&t; * TBD: Doesn&squot;t the bus driver automatically set this?&n;&t; */
id|device-&gt;ops.bind
op_assign
id|acpi_pci_bind
suffix:semicolon
multiline_comment|/* &n;&t; * Segment&n;&t; * -------&n;&t; * Obtained via _SEG, if exists, otherwise assumed to be zero (0).&n;&t; */
id|status
op_assign
id|acpi_evaluate_integer
c_func
(paren
id|root-&gt;handle
comma
id|METHOD_NAME__SEG
comma
l_int|NULL
comma
op_amp
id|value
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|AE_OK
suffix:colon
id|root-&gt;id.segment
op_assign
(paren
id|u16
)paren
id|value
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;_SEG exists! Unsupported. Abort.&bslash;n&quot;
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AE_NOT_FOUND
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Assuming segment 0 (no _SEG)&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|root-&gt;id.segment
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Error evaluating _SEG&bslash;n&quot;
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
multiline_comment|/* &n;&t; * Bus&n;&t; * ---&n;&t; * Obtained via _BBN, if exists, otherwise assumed to be zero (0).&n;&t; */
id|status
op_assign
id|acpi_evaluate_integer
c_func
(paren
id|root-&gt;handle
comma
id|METHOD_NAME__BBN
comma
l_int|NULL
comma
op_amp
id|value
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|AE_OK
suffix:colon
id|root-&gt;id.bus
op_assign
(paren
id|u16
)paren
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AE_NOT_FOUND
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Assuming bus 0 (no _BBN)&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|root-&gt;id.bus
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Error evaluating _BBN&bslash;n&quot;
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
multiline_comment|/*&n;&t; * Device &amp; Function&n;&t; * -----------------&n;&t; * Obtained from _ADR (which has already been evaluated for us).&n;&t; */
id|root-&gt;id.device
op_assign
id|device-&gt;pnp.bus_address
op_rshift
l_int|16
suffix:semicolon
id|root-&gt;id.function
op_assign
id|device-&gt;pnp.bus_address
op_amp
l_int|0xFFFF
suffix:semicolon
multiline_comment|/*&n;&t; * Evaluate _CRS to get root bridge resources&n;&t; * TBD: Need PCI interface for enumeration/configuration of roots.&n;&t; */
id|acpi_pci_evaluate_crs
c_func
(paren
id|root
)paren
suffix:semicolon
multiline_comment|/* TBD: Locking */
id|list_add_tail
c_func
(paren
op_amp
id|root-&gt;node
comma
op_amp
id|acpi_pci_roots
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;%s [%s] (%02x:%02x)&bslash;n&quot;
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
comma
id|root-&gt;id.segment
comma
id|root-&gt;id.bus
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Scan the Root Bridge&n;&t; * --------------------&n;&t; * Must do this prior to any attempt to bind the root device, as the&n;&t; * PCI namespace does not get created until this call is made (and &n;&t; * thus the root bridge&squot;s pci_dev does not exist).&n;&t; */
id|root-&gt;bus
op_assign
id|pcibios_scan_root
c_func
(paren
id|root-&gt;id.bus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root-&gt;bus
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Bus %02x:%02x not present in PCI namespace&bslash;n&quot;
comma
id|root-&gt;id.segment
comma
id|root-&gt;id.bus
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
multiline_comment|/*&n;&t; * Attach ACPI-PCI Context&n;&t; * -----------------------&n;&t; * Thus binding the ACPI and PCI devices.&n;&t; */
id|result
op_assign
id|acpi_pci_bind_root
c_func
(paren
id|device
comma
op_amp
id|root-&gt;id
comma
id|root-&gt;bus
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
multiline_comment|/*&n;&t; * PCI Routing Table&n;&t; * -----------------&n;&t; * Evaluate and parse _PRT, if exists.&n;&t; */
id|status
op_assign
id|acpi_get_handle
c_func
(paren
id|root-&gt;handle
comma
id|METHOD_NAME__PRT
comma
op_amp
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
)paren
id|result
op_assign
id|acpi_pci_irq_add_prt
c_func
(paren
id|root-&gt;handle
comma
id|root-&gt;id.segment
comma
id|root-&gt;id.bus
)paren
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
id|root
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
DECL|function|acpi_pci_root_remove
id|acpi_pci_root_remove
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
id|acpi_pci_root
op_star
id|root
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_root_remove&quot;
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
id|root
op_assign
(paren
r_struct
id|acpi_pci_root
op_star
)paren
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|root
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
DECL|function|acpi_pci_root_init
id|acpi_pci_root_init
(paren
r_void
)paren
(brace
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_root_init&quot;
)paren
suffix:semicolon
multiline_comment|/* DEBUG:&n;&t;acpi_dbg_layer = ACPI_PCI_COMPONENT;&n;&t;acpi_dbg_level = 0xFFFFFFFF;&n;&t; */
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|acpi_pci_roots
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_bus_register_driver
c_func
(paren
op_amp
id|acpi_pci_root_driver
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
r_void
id|__exit
DECL|function|acpi_pci_root_exit
id|acpi_pci_root_exit
(paren
r_void
)paren
(brace
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_root_exit&quot;
)paren
suffix:semicolon
id|acpi_bus_unregister_driver
c_func
(paren
op_amp
id|acpi_pci_root_driver
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
eof
