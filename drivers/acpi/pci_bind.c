multiline_comment|/*&n; *  pci_bind.c - ACPI PCI Device Binding ($Revision: 2 $)&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
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
l_string|&quot;pci_bind&quot;
)paren
DECL|struct|acpi_pci_data
r_struct
id|acpi_pci_data
(brace
DECL|member|id
r_struct
id|acpi_pci_id
id|id
suffix:semicolon
DECL|member|bus
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
r_void
DECL|function|acpi_pci_data_handler
id|acpi_pci_data_handler
(paren
id|acpi_handle
id|handle
comma
id|u32
id|function
comma
r_void
op_star
id|context
)paren
(brace
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_data_handler&quot;
)paren
suffix:semicolon
multiline_comment|/* TBD: Anything we need to do here? */
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/**&n; * acpi_os_get_pci_id&n; * ------------------&n; * This function is used by the ACPI Interpreter (a.k.a. Core Subsystem)&n; * to resolve PCI information for ACPI-PCI devices defined in the namespace.&n; * This typically occurs when resolving PCI operation region information.&n; */
id|acpi_status
DECL|function|acpi_os_get_pci_id
id|acpi_os_get_pci_id
(paren
id|acpi_handle
id|handle
comma
r_struct
id|acpi_pci_id
op_star
id|id
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
id|acpi_device
op_star
id|device
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_pci_data
op_star
id|data
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_os_get_pci_id&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|id
)paren
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_PARAMETER
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
l_string|&quot;Invalid ACPI Bus context for device %s&bslash;n&quot;
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|AE_NOT_EXIST
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_get_data
c_func
(paren
id|handle
comma
id|acpi_pci_data_handler
comma
(paren
r_void
op_star
op_star
)paren
op_amp
id|data
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
id|data
op_logical_or
op_logical_neg
id|data-&gt;dev
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid ACPI-PCI context for device %s&bslash;n&quot;
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
op_star
id|id
op_assign
id|data-&gt;id
suffix:semicolon
multiline_comment|/*&n;&t;id-&gt;segment = data-&gt;id.segment;&n;&t;id-&gt;bus = data-&gt;id.bus;&n;&t;id-&gt;device = data-&gt;id.device;&n;&t;id-&gt;function = data-&gt;id.function;&n;&t;*/
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Device %s has PCI address %02x:%02x:%02x.%02x&bslash;n&quot;
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
id|id-&gt;segment
comma
id|id-&gt;bus
comma
id|id-&gt;device
comma
id|id-&gt;function
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
r_int
DECL|function|acpi_pci_bind
id|acpi_pci_bind
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
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_pci_data
op_star
id|data
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_pci_data
op_star
id|pdata
op_assign
l_int|NULL
suffix:semicolon
r_char
id|pathname
(braket
id|ACPI_PATHNAME_MAX
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_struct
id|acpi_buffer
id|buffer
op_assign
(brace
id|ACPI_PATHNAME_MAX
comma
id|pathname
)brace
suffix:semicolon
id|acpi_handle
id|handle
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_bind&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
op_logical_or
op_logical_neg
id|device-&gt;parent
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|data
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|acpi_pci_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
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
id|data
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|acpi_pci_data
)paren
)paren
suffix:semicolon
id|acpi_get_name
c_func
(paren
id|device-&gt;handle
comma
id|ACPI_FULL_PATHNAME
comma
op_amp
id|buffer
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Binding PCI device [%s]...&bslash;n&quot;
comma
id|pathname
)paren
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Segment &amp; Bus&n;&t; * -------------&n;&t; * These are obtained via the parent device&squot;s ACPI-PCI context.&n;&t; */
id|status
op_assign
id|acpi_get_data
c_func
(paren
id|device-&gt;parent-&gt;handle
comma
id|acpi_pci_data_handler
comma
(paren
r_void
op_star
op_star
)paren
op_amp
id|pdata
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
id|pdata
op_logical_or
op_logical_neg
id|pdata-&gt;bus
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid ACPI-PCI context for parent device %s&bslash;n&quot;
comma
id|acpi_device_bid
c_func
(paren
id|device-&gt;parent
)paren
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
id|data-&gt;id.segment
op_assign
id|pdata-&gt;id.segment
suffix:semicolon
id|data-&gt;id.bus
op_assign
id|pdata-&gt;bus-&gt;number
suffix:semicolon
multiline_comment|/*&n;&t; * Device &amp; Function&n;&t; * -----------------&n;&t; * These are simply obtained from the device&squot;s _ADR method.  Note&n;&t; * that a value of zero is valid.&n;&t; */
id|data-&gt;id.device
op_assign
id|device-&gt;pnp.bus_address
op_rshift
l_int|16
suffix:semicolon
id|data-&gt;id.function
op_assign
id|device-&gt;pnp.bus_address
op_amp
l_int|0xFFFF
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;...to %02x:%02x:%02x.%02x&bslash;n&quot;
comma
id|data-&gt;id.segment
comma
id|data-&gt;id.bus
comma
id|data-&gt;id.device
comma
id|data-&gt;id.function
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * TBD: Support slot devices (e.g. function=0xFFFF).&n;&t; */
multiline_comment|/* &n;&t; * Locate PCI Device&n;&t; * -----------------&n;&t; * Locate matching device in PCI namespace.  If it doesn&squot;t exist&n;&t; * this typically means that the device isn&squot;t currently inserted&n;&t; * (e.g. docking station, port replicator, etc.).&n;&t; */
id|data-&gt;dev
op_assign
id|pci_find_slot
c_func
(paren
id|data-&gt;id.bus
comma
id|PCI_DEVFN
c_func
(paren
id|data-&gt;id.device
comma
id|data-&gt;id.function
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;dev
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Device %02x:%02x:%02x.%02x not present in PCI namespace&bslash;n&quot;
comma
id|data-&gt;id.segment
comma
id|data-&gt;id.bus
comma
id|data-&gt;id.device
comma
id|data-&gt;id.function
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
id|data-&gt;dev-&gt;bus
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Device %02x:%02x:%02x.%02x has invalid &squot;bus&squot; field&bslash;n&quot;
comma
id|data-&gt;id.segment
comma
id|data-&gt;id.bus
comma
id|data-&gt;id.device
comma
id|data-&gt;id.function
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
multiline_comment|/*&n;&t; * PCI Bridge?&n;&t; * -----------&n;&t; * If so, set the &squot;bus&squot; field and install the &squot;bind&squot; function to &n;&t; * facilitate callbacks for all of its children.&n;&t; */
r_if
c_cond
(paren
id|data-&gt;dev-&gt;subordinate
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Device %02x:%02x:%02x.%02x is a PCI bridge&bslash;n&quot;
comma
id|data-&gt;id.segment
comma
id|data-&gt;id.bus
comma
id|data-&gt;id.device
comma
id|data-&gt;id.function
)paren
)paren
suffix:semicolon
id|data-&gt;bus
op_assign
id|data-&gt;dev-&gt;subordinate
suffix:semicolon
id|device-&gt;ops.bind
op_assign
id|acpi_pci_bind
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Attach ACPI-PCI Context&n;&t; * -----------------------&n;&t; * Thus binding the ACPI and PCI devices.&n;&t; */
id|status
op_assign
id|acpi_attach_data
c_func
(paren
id|device-&gt;handle
comma
id|acpi_pci_data_handler
comma
id|data
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
l_string|&quot;Unable to attach ACPI-PCI context to device %s&bslash;n&quot;
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
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
multiline_comment|/*&n;&t; * PCI Routing Table&n;&t; * -----------------&n;&t; * Evaluate and parse _PRT, if exists.  This code is independent of &n;&t; * PCI bridges (above) to allow parsing of _PRT objects within the&n;&t; * scope of non-bridge devices.  Note that _PRTs within the scope of&n;&t; * a PCI bridge assume the bridge&squot;s subordinate bus number.&n;&t; *&n;&t; * TBD: Can _PRTs exist within the scope of non-bridge PCI devices?&n;&t; */
id|status
op_assign
id|acpi_get_handle
c_func
(paren
id|device-&gt;handle
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
(brace
r_if
c_cond
(paren
id|data-&gt;bus
)paren
multiline_comment|/* PCI-PCI bridge */
id|acpi_pci_irq_add_prt
c_func
(paren
id|device-&gt;handle
comma
id|data-&gt;id.segment
comma
id|data-&gt;bus-&gt;number
)paren
suffix:semicolon
r_else
multiline_comment|/* non-bridge PCI device */
id|acpi_pci_irq_add_prt
c_func
(paren
id|device-&gt;handle
comma
id|data-&gt;id.segment
comma
id|data-&gt;id.bus
)paren
suffix:semicolon
)brace
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
id|data
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_int
DECL|function|acpi_pci_bind_root
id|acpi_pci_bind_root
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_struct
id|acpi_pci_id
op_star
id|id
comma
r_struct
id|pci_bus
op_star
id|bus
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
id|acpi_pci_data
op_star
id|data
op_assign
l_int|NULL
suffix:semicolon
r_char
id|pathname
(braket
id|ACPI_PATHNAME_MAX
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_struct
id|acpi_buffer
id|buffer
op_assign
(brace
id|ACPI_PATHNAME_MAX
comma
id|pathname
)brace
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_pci_bind_root&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
op_logical_or
op_logical_neg
id|id
op_logical_or
op_logical_neg
id|bus
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|data
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|acpi_pci_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
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
id|data
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|acpi_pci_data
)paren
)paren
suffix:semicolon
id|data-&gt;id
op_assign
op_star
id|id
suffix:semicolon
id|data-&gt;bus
op_assign
id|bus
suffix:semicolon
id|device-&gt;ops.bind
op_assign
id|acpi_pci_bind
suffix:semicolon
id|acpi_get_name
c_func
(paren
id|device-&gt;handle
comma
id|ACPI_FULL_PATHNAME
comma
op_amp
id|buffer
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Binding PCI root bridge [%s] to &quot;
l_string|&quot;%02x:%02x&bslash;n&quot;
comma
id|pathname
comma
id|id-&gt;segment
comma
id|id-&gt;bus
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_attach_data
c_func
(paren
id|device-&gt;handle
comma
id|acpi_pci_data_handler
comma
id|data
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
l_string|&quot;Unable to attach ACPI-PCI context to device %s&bslash;n&quot;
comma
id|pathname
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
id|end
suffix:colon
r_if
c_cond
(paren
id|result
op_ne
l_int|0
)paren
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
eof
