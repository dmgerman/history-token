multiline_comment|/******************************************************************************&n; *&n; * Module Name: exstorob - AML Interpreter object store support, store to object&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exstorob&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_store_buffer_to_buffer&n; *&n; * PARAMETERS:  source_desc         - Source object to copy&n; *              target_desc         - Destination object of the copy&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Copy a buffer object to another buffer object.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_store_buffer_to_buffer
id|acpi_ex_store_buffer_to_buffer
(paren
r_union
id|acpi_operand_object
op_star
id|source_desc
comma
r_union
id|acpi_operand_object
op_star
id|target_desc
)paren
(brace
id|u32
id|length
suffix:semicolon
id|u8
op_star
id|buffer
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ex_store_buffer_to_buffer&quot;
comma
id|source_desc
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We know that source_desc is a buffer by now&n;&t; */
id|buffer
op_assign
(paren
id|u8
op_star
)paren
id|source_desc-&gt;buffer.pointer
suffix:semicolon
id|length
op_assign
id|source_desc-&gt;buffer.length
suffix:semicolon
multiline_comment|/*&n;&t; * If target is a buffer of length zero or is a static buffer,&n;&t; * allocate a new buffer of the proper length&n;&t; */
r_if
c_cond
(paren
(paren
id|target_desc-&gt;buffer.length
op_eq
l_int|0
)paren
op_logical_or
(paren
id|target_desc-&gt;common.flags
op_amp
id|AOPOBJ_STATIC_POINTER
)paren
)paren
(brace
id|target_desc-&gt;buffer.pointer
op_assign
id|ACPI_MEM_ALLOCATE
(paren
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|target_desc-&gt;buffer.pointer
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|target_desc-&gt;buffer.length
op_assign
id|length
suffix:semicolon
)brace
multiline_comment|/* Copy source buffer to target buffer */
r_if
c_cond
(paren
id|length
op_le
id|target_desc-&gt;buffer.length
)paren
(brace
multiline_comment|/* Clear existing buffer and copy in the new one */
id|ACPI_MEMSET
(paren
id|target_desc-&gt;buffer.pointer
comma
l_int|0
comma
id|target_desc-&gt;buffer.length
)paren
suffix:semicolon
id|ACPI_MEMCPY
(paren
id|target_desc-&gt;buffer.pointer
comma
id|buffer
comma
id|length
)paren
suffix:semicolon
multiline_comment|/* Set the new length of the target */
id|target_desc-&gt;buffer.length
op_assign
id|length
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Truncate the source, copy only what will fit */
id|ACPI_MEMCPY
(paren
id|target_desc-&gt;buffer.pointer
comma
id|buffer
comma
id|target_desc-&gt;buffer.length
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Truncating source buffer from %X to %X&bslash;n&quot;
comma
id|length
comma
id|target_desc-&gt;buffer.length
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy flags */
id|target_desc-&gt;buffer.flags
op_assign
id|source_desc-&gt;buffer.flags
suffix:semicolon
id|target_desc-&gt;common.flags
op_and_assign
op_complement
id|AOPOBJ_STATIC_POINTER
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_store_string_to_string&n; *&n; * PARAMETERS:  source_desc         - Source object to copy&n; *              target_desc         - Destination object of the copy&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Copy a String object to another String object&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_store_string_to_string
id|acpi_ex_store_string_to_string
(paren
r_union
id|acpi_operand_object
op_star
id|source_desc
comma
r_union
id|acpi_operand_object
op_star
id|target_desc
)paren
(brace
id|u32
id|length
suffix:semicolon
id|u8
op_star
id|buffer
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ex_store_string_to_string&quot;
comma
id|source_desc
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We know that source_desc is a string by now.&n;&t; */
id|buffer
op_assign
(paren
id|u8
op_star
)paren
id|source_desc-&gt;string.pointer
suffix:semicolon
id|length
op_assign
id|source_desc-&gt;string.length
suffix:semicolon
multiline_comment|/*&n;&t; * Replace existing string value if it will fit and the string&n;&t; * pointer is not a static pointer (part of an ACPI table)&n;&t; */
r_if
c_cond
(paren
(paren
id|length
OL
id|target_desc-&gt;string.length
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|target_desc-&gt;common.flags
op_amp
id|AOPOBJ_STATIC_POINTER
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * String will fit in existing non-static buffer.&n;&t;&t; * Clear old string and copy in the new one&n;&t;&t; */
id|ACPI_MEMSET
(paren
id|target_desc-&gt;string.pointer
comma
l_int|0
comma
(paren
id|acpi_size
)paren
id|target_desc-&gt;string.length
op_plus
l_int|1
)paren
suffix:semicolon
id|ACPI_MEMCPY
(paren
id|target_desc-&gt;string.pointer
comma
id|buffer
comma
id|length
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Free the current buffer, then allocate a new buffer&n;&t;&t; * large enough to hold the value&n;&t;&t; */
r_if
c_cond
(paren
id|target_desc-&gt;string.pointer
op_logical_and
(paren
op_logical_neg
(paren
id|target_desc-&gt;common.flags
op_amp
id|AOPOBJ_STATIC_POINTER
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Only free if not a pointer into the DSDT&n;&t;&t;&t; */
id|ACPI_MEM_FREE
(paren
id|target_desc-&gt;string.pointer
)paren
suffix:semicolon
)brace
id|target_desc-&gt;string.pointer
op_assign
id|ACPI_MEM_CALLOCATE
(paren
(paren
id|acpi_size
)paren
id|length
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|target_desc-&gt;string.pointer
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|target_desc-&gt;common.flags
op_and_assign
op_complement
id|AOPOBJ_STATIC_POINTER
suffix:semicolon
id|ACPI_MEMCPY
(paren
id|target_desc-&gt;string.pointer
comma
id|buffer
comma
id|length
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the new target length */
id|target_desc-&gt;string.length
op_assign
id|length
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
