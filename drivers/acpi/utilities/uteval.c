multiline_comment|/******************************************************************************&n; *&n; * Module Name: uteval - Object evaluation&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2003, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_UTILITIES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;uteval&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_evaluate_object&n; *&n; * PARAMETERS:  prefix_node         - Starting node&n; *              Path                - Path to object from starting node&n; *              expected_return_types - Bitmap of allowed return types&n; *              return_desc         - Where a return value is stored&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Evaluates a namespace object and verifies the type of the&n; *              return object.  Common code that simplifies accessing objects&n; *              that have required return objects of fixed types.&n; *&n; *              NOTE: Internal function, no parameter validation&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_evaluate_object
id|acpi_ut_evaluate_object
(paren
r_struct
id|acpi_namespace_node
op_star
id|prefix_node
comma
r_char
op_star
id|path
comma
id|u32
id|expected_return_btypes
comma
r_union
id|acpi_operand_object
op_star
op_star
id|return_desc
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|u32
id|return_btype
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_evaluate_object&quot;
)paren
suffix:semicolon
multiline_comment|/* Evaluate the object/method */
id|status
op_assign
id|acpi_ns_evaluate_relative
(paren
id|prefix_node
comma
id|path
comma
l_int|NULL
comma
op_amp
id|obj_desc
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
r_if
c_cond
(paren
id|status
op_eq
id|AE_NOT_FOUND
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[%4.4s.%s] was not found&bslash;n&quot;
comma
id|prefix_node-&gt;name.ascii
comma
id|path
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|ACPI_REPORT_METHOD_ERROR
(paren
l_string|&quot;Method execution failed&quot;
comma
id|prefix_node
comma
id|path
comma
id|status
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Did we get a return object? */
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
r_if
c_cond
(paren
id|expected_return_btypes
)paren
(brace
id|ACPI_REPORT_METHOD_ERROR
(paren
l_string|&quot;No object was returned from&quot;
comma
id|prefix_node
comma
id|path
comma
id|AE_NOT_EXIST
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NOT_EXIST
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Map the return object type to the bitmapped type */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
id|return_btype
op_assign
id|ACPI_BTYPE_INTEGER
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|return_btype
op_assign
id|ACPI_BTYPE_BUFFER
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|return_btype
op_assign
id|ACPI_BTYPE_STRING
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
id|return_btype
op_assign
id|ACPI_BTYPE_PACKAGE
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|return_btype
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Is the return object one of the expected types? */
r_if
c_cond
(paren
op_logical_neg
(paren
id|expected_return_btypes
op_amp
id|return_btype
)paren
)paren
(brace
id|ACPI_REPORT_METHOD_ERROR
(paren
l_string|&quot;Return object type is incorrect&quot;
comma
id|prefix_node
comma
id|path
comma
id|AE_TYPE
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Type returned from %s was incorrect: %X&bslash;n&quot;
comma
id|path
comma
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* On error exit, we must delete the return object */
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/* Object type is OK, return it */
op_star
id|return_desc
op_assign
id|obj_desc
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_evaluate_numeric_object&n; *&n; * PARAMETERS:  *object_name        - Object name to be evaluated&n; *              device_node         - Node for the device&n; *              *Address            - Where the value is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Evaluates a numeric namespace object for a selected device&n; *              and stores result in *Address.&n; *&n; *              NOTE: Internal function, no parameter validation&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_evaluate_numeric_object
id|acpi_ut_evaluate_numeric_object
(paren
r_char
op_star
id|object_name
comma
r_struct
id|acpi_namespace_node
op_star
id|device_node
comma
id|acpi_integer
op_star
id|address
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_evaluate_numeric_object&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_evaluate_object
(paren
id|device_node
comma
id|object_name
comma
id|ACPI_BTYPE_INTEGER
comma
op_amp
id|obj_desc
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the returned Integer */
op_star
id|address
op_assign
id|obj_desc-&gt;integer.value
suffix:semicolon
multiline_comment|/* On exit, we must delete the return object */
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_execute_HID&n; *&n; * PARAMETERS:  device_node         - Node for the device&n; *              *Hid                - Where the HID is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Executes the _HID control method that returns the hardware&n; *              ID of the device.&n; *&n; *              NOTE: Internal function, no parameter validation&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_execute_HID
id|acpi_ut_execute_HID
(paren
r_struct
id|acpi_namespace_node
op_star
id|device_node
comma
r_struct
id|acpi_device_id
op_star
id|hid
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_execute_HID&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_evaluate_object
(paren
id|device_node
comma
id|METHOD_NAME__HID
comma
id|ACPI_BTYPE_INTEGER
op_or
id|ACPI_BTYPE_STRING
comma
op_amp
id|obj_desc
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_INTEGER
)paren
(brace
multiline_comment|/* Convert the Numeric HID to string */
id|acpi_ex_eisa_id_to_string
(paren
(paren
id|u32
)paren
id|obj_desc-&gt;integer.value
comma
id|hid-&gt;buffer
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Copy the String HID from the returned object */
id|ACPI_STRNCPY
(paren
id|hid-&gt;buffer
comma
id|obj_desc-&gt;string.pointer
comma
r_sizeof
(paren
id|hid-&gt;buffer
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* On exit, we must delete the return object */
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_execute_CID&n; *&n; * PARAMETERS:  device_node         - Node for the device&n; *              *Cid                - Where the CID is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Executes the _CID control method that returns one or more&n; *              compatible hardware IDs for the device.&n; *&n; *              NOTE: Internal function, no parameter validation&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_execute_CID
id|acpi_ut_execute_CID
(paren
r_struct
id|acpi_namespace_node
op_star
id|device_node
comma
r_struct
id|acpi_device_id
op_star
id|cid
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_execute_CID&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_evaluate_object
(paren
id|device_node
comma
id|METHOD_NAME__CID
comma
id|ACPI_BTYPE_INTEGER
op_or
id|ACPI_BTYPE_STRING
op_or
id|ACPI_BTYPE_PACKAGE
comma
op_amp
id|obj_desc
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  A _CID can return either a single compatible ID or a package of compatible&n;&t; *  IDs.  Each compatible ID can be a Number (32 bit compressed EISA ID) or&n;&t; *  string (PCI ID format, e.g. &quot;PCI&bslash;VEN_vvvv&amp;DEV_dddd&amp;SUBSYS_ssssssss&quot;).&n;&t; */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
multiline_comment|/* Convert the Numeric CID to string */
id|acpi_ex_eisa_id_to_string
(paren
(paren
id|u32
)paren
id|obj_desc-&gt;integer.value
comma
id|cid-&gt;buffer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
multiline_comment|/* Copy the String CID from the returned object */
id|ACPI_STRNCPY
(paren
id|cid-&gt;buffer
comma
id|obj_desc-&gt;string.pointer
comma
r_sizeof
(paren
id|cid-&gt;buffer
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
multiline_comment|/* TBD: Parse package elements; need different return struct, etc. */
id|status
op_assign
id|AE_SUPPORT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|AE_TYPE
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* On exit, we must delete the return object */
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_execute_UID&n; *&n; * PARAMETERS:  device_node         - Node for the device&n; *              *Uid                - Where the UID is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Executes the _UID control method that returns the hardware&n; *              ID of the device.&n; *&n; *              NOTE: Internal function, no parameter validation&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_execute_UID
id|acpi_ut_execute_UID
(paren
r_struct
id|acpi_namespace_node
op_star
id|device_node
comma
r_struct
id|acpi_device_id
op_star
id|uid
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_execute_UID&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_evaluate_object
(paren
id|device_node
comma
id|METHOD_NAME__UID
comma
id|ACPI_BTYPE_INTEGER
op_or
id|ACPI_BTYPE_STRING
comma
op_amp
id|obj_desc
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_INTEGER
)paren
(brace
multiline_comment|/* Convert the Numeric UID to string */
id|acpi_ex_unsigned_integer_to_string
(paren
id|obj_desc-&gt;integer.value
comma
id|uid-&gt;buffer
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Copy the String UID from the returned object */
id|ACPI_STRNCPY
(paren
id|uid-&gt;buffer
comma
id|obj_desc-&gt;string.pointer
comma
r_sizeof
(paren
id|uid-&gt;buffer
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* On exit, we must delete the return object */
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_execute_STA&n; *&n; * PARAMETERS:  device_node         - Node for the device&n; *              *Flags              - Where the status flags are returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Executes _STA for selected device and stores results in&n; *              *Flags.&n; *&n; *              NOTE: Internal function, no parameter validation&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_execute_STA
id|acpi_ut_execute_STA
(paren
r_struct
id|acpi_namespace_node
op_star
id|device_node
comma
id|u32
op_star
id|flags
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_execute_STA&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_evaluate_object
(paren
id|device_node
comma
id|METHOD_NAME__STA
comma
id|ACPI_BTYPE_INTEGER
comma
op_amp
id|obj_desc
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
r_if
c_cond
(paren
id|AE_NOT_FOUND
op_eq
id|status
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;_STA on %4.4s was not found, assuming device is present&bslash;n&quot;
comma
id|device_node-&gt;name.ascii
)paren
)paren
suffix:semicolon
op_star
id|flags
op_assign
l_int|0x0F
suffix:semicolon
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Extract the status flags */
op_star
id|flags
op_assign
(paren
id|u32
)paren
id|obj_desc-&gt;integer.value
suffix:semicolon
multiline_comment|/* On exit, we must delete the return object */
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
