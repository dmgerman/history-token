multiline_comment|/******************************************************************************&n; *&n; * Module Name: nsdump - table dumping routines for debug&n; *              $Revision: 1 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acparser.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_NAMESPACE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;nsdumpdv&quot;
)paren
macro_line|#if defined(ACPI_DEBUG) || defined(ENABLE_DEBUGGER)
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_dump_one_device&n; *&n; * PARAMETERS:  Handle              - Node to be dumped&n; *              Level               - Nesting level of the handle&n; *              Context             - Passed into Walk_namespace&n; *&n; * DESCRIPTION: Dump a single Node that represents a device&n; *              This procedure is a User_function called by Acpi_ns_walk_namespace.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ns_dump_one_device
id|acpi_ns_dump_one_device
(paren
id|acpi_handle
id|obj_handle
comma
id|u32
id|level
comma
r_void
op_star
id|context
comma
r_void
op_star
op_star
id|return_value
)paren
(brace
id|acpi_device_info
id|info
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Ns_dump_one_device&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ns_dump_one_object
(paren
id|obj_handle
comma
id|level
comma
id|context
comma
id|return_value
)paren
suffix:semicolon
id|status
op_assign
id|acpi_get_object_info
(paren
id|obj_handle
comma
op_amp
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|level
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_TABLES
comma
l_string|&quot; &quot;
)paren
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_TABLES
comma
l_string|&quot;    HID: %s, ADR: %8.8X%8.8X, Status: %X&bslash;n&quot;
comma
id|info.hardware_id
comma
id|ACPI_HIDWORD
(paren
id|info.address
)paren
comma
id|ACPI_LODWORD
(paren
id|info.address
)paren
comma
id|info.current_status
)paren
)paren
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_dump_root_devices&n; *&n; * PARAMETERS:  None&n; *&n; * DESCRIPTION: Dump all objects of type &quot;device&quot;&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ns_dump_root_devices
id|acpi_ns_dump_root_devices
(paren
r_void
)paren
(brace
id|acpi_handle
id|sys_bus_handle
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;Ns_dump_root_devices&quot;
)paren
suffix:semicolon
multiline_comment|/* Only dump the table if tracing is enabled */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ACPI_LV_TABLES
op_amp
id|acpi_dbg_level
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|status
op_assign
id|acpi_get_handle
(paren
l_int|0
comma
id|ACPI_NS_SYSTEM_BUS
comma
op_amp
id|sys_bus_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_TABLES
comma
l_string|&quot;Display of all devices in the namespace:&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ns_walk_namespace
(paren
id|ACPI_TYPE_DEVICE
comma
id|sys_bus_handle
comma
id|ACPI_UINT32_MAX
comma
id|ACPI_NS_WALK_NO_UNLOCK
comma
id|acpi_ns_dump_one_device
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
