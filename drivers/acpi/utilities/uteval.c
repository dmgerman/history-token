multiline_comment|/******************************************************************************&n; *&n; * Module Name: uteval - Object evaluation&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_copy_id_string&n; *&n; * PARAMETERS:  Destination         - Where to copy the string&n; *              Source              - Source string&n; *              max_length          - Length of the destination buffer&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Copies an ID string for the _HID, _CID, and _UID methods.&n; *              Performs removal of a leading asterisk if present -- workaround&n; *              for a known issue on a bunch of machines.&n; *&n; ******************************************************************************/
r_static
r_void
DECL|function|acpi_ut_copy_id_string
id|acpi_ut_copy_id_string
(paren
r_char
op_star
id|destination
comma
r_char
op_star
id|source
comma
id|acpi_size
id|max_length
)paren
(brace
multiline_comment|/*&n;&t; * Workaround for ID strings that have a leading asterisk. This construct&n;&t; * is not allowed by the ACPI specification  (ID strings must be&n;&t; * alphanumeric), but enough existing machines have this embedded in their&n;&t; * ID strings that the following code is useful.&n;&t; */
r_if
c_cond
(paren
op_star
id|source
op_eq
l_char|&squot;*&squot;
)paren
(brace
id|source
op_increment
suffix:semicolon
)brace
multiline_comment|/* Do the actual copy */
id|ACPI_STRNCPY
(paren
id|destination
comma
id|source
comma
id|max_length
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
id|hid-&gt;value
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Copy the String HID from the returned object */
id|acpi_ut_copy_id_string
(paren
id|hid-&gt;value
comma
id|obj_desc-&gt;string.pointer
comma
r_sizeof
(paren
id|hid-&gt;value
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_translate_one_cid&n; *&n; * PARAMETERS:  obj_desc            - _CID object, must be integer or string&n; *              one_cid             - Where the CID string is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Return a numeric or string _CID value as a string.&n; *              (Compatible ID)&n; *&n; *              NOTE:  Assumes a maximum _CID string length of&n; *                     ACPI_MAX_CID_LENGTH.&n; *&n; ******************************************************************************/
r_static
id|acpi_status
DECL|function|acpi_ut_translate_one_cid
id|acpi_ut_translate_one_cid
(paren
r_union
id|acpi_operand_object
op_star
id|obj_desc
comma
r_struct
id|acpi_compatible_id
op_star
id|one_cid
)paren
(brace
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
id|one_cid-&gt;value
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
r_if
c_cond
(paren
id|obj_desc-&gt;string.length
OG
id|ACPI_MAX_CID_LENGTH
)paren
(brace
r_return
(paren
id|AE_AML_STRING_LIMIT
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the String CID from the returned object */
id|acpi_ut_copy_id_string
(paren
id|one_cid-&gt;value
comma
id|obj_desc-&gt;string.pointer
comma
id|ACPI_MAX_CID_LENGTH
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
r_default
suffix:colon
r_return
(paren
id|AE_TYPE
)paren
suffix:semicolon
)brace
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
id|acpi_compatible_id_list
op_star
op_star
id|return_cid_list
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
id|count
suffix:semicolon
id|u32
id|size
suffix:semicolon
r_struct
id|acpi_compatible_id_list
op_star
id|cid_list
suffix:semicolon
id|acpi_native_uint
id|i
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_execute_CID&quot;
)paren
suffix:semicolon
multiline_comment|/* Evaluate the _CID method for this device */
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
multiline_comment|/* Get the number of _CIDs returned */
id|count
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_PACKAGE
)paren
(brace
id|count
op_assign
id|obj_desc-&gt;package.count
suffix:semicolon
)brace
multiline_comment|/* Allocate a worst-case buffer for the _CIDs */
id|size
op_assign
(paren
(paren
(paren
id|count
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
r_struct
id|acpi_compatible_id
)paren
)paren
op_plus
r_sizeof
(paren
r_struct
id|acpi_compatible_id_list
)paren
)paren
suffix:semicolon
id|cid_list
op_assign
id|ACPI_MEM_CALLOCATE
(paren
(paren
id|acpi_size
)paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cid_list
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Init CID list */
id|cid_list-&gt;count
op_assign
id|count
suffix:semicolon
id|cid_list-&gt;size
op_assign
id|size
suffix:semicolon
multiline_comment|/*&n;&t; *  A _CID can return either a single compatible ID or a package of compatible&n;&t; *  IDs.  Each compatible ID can be one of the following:&n;&t; *  -- Number (32 bit compressed EISA ID) or&n;&t; *  -- String (PCI ID format, e.g. &quot;PCI&bslash;VEN_vvvv&amp;DEV_dddd&amp;SUBSYS_ssssssss&quot;).&n;&t; */
multiline_comment|/* The _CID object can be either a single CID or a package (list) of CIDs */
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_PACKAGE
)paren
(brace
multiline_comment|/* Translate each package element */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|acpi_ut_translate_one_cid
(paren
id|obj_desc-&gt;package.elements
(braket
id|i
)braket
comma
op_amp
id|cid_list-&gt;id
(braket
id|i
)braket
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
r_break
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
multiline_comment|/* Only one CID, translate to a string */
id|status
op_assign
id|acpi_ut_translate_one_cid
(paren
id|obj_desc
comma
id|cid_list-&gt;id
)paren
suffix:semicolon
)brace
multiline_comment|/* Cleanup on error */
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|ACPI_MEM_FREE
(paren
id|cid_list
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|return_cid_list
op_assign
id|cid_list
suffix:semicolon
)brace
multiline_comment|/* On exit, we must delete the _CID return object */
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
id|uid-&gt;value
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Copy the String UID from the returned object */
id|acpi_ut_copy_id_string
(paren
id|uid-&gt;value
comma
id|obj_desc-&gt;string.pointer
comma
r_sizeof
(paren
id|uid-&gt;value
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
