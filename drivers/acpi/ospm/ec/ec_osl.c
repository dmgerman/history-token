multiline_comment|/*****************************************************************************&n; *&n; * Module Name: ec_osl.c&n; *   $Revision: 6 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;acpi.h&gt;
macro_line|#include &lt;bm.h&gt;
macro_line|#include &quot;ec.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andrew Grover&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ACPI Component Architecture (CA) - Embedded Controller Driver&quot;
)paren
suffix:semicolon
macro_line|#ifdef ACPI_DEBUG
DECL|variable|dbg_layer
r_static
r_int
id|dbg_layer
op_assign
id|ACPI_COMPONENT_DEFAULT
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|dbg_layer
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|dbg_layer
comma
l_string|&quot;Controls debug output (see acpi_dbg_layer).&bslash;n&quot;
)paren
suffix:semicolon
DECL|variable|dbg_level
r_static
r_int
id|dbg_level
op_assign
id|DEBUG_DEFAULT
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|dbg_level
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|dbg_level
comma
l_string|&quot;Controls debug output (see acpi_dbg_level).&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif /*ACPI_DEBUG*/
macro_line|#ifdef ACPI_DEBUG
DECL|variable|save_dbg_layer
r_static
id|u32
id|save_dbg_layer
suffix:semicolon
DECL|variable|save_dbg_level
r_static
id|u32
id|save_dbg_level
suffix:semicolon
macro_line|#endif /*ACPI_DEBUG*/
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    ec_osl_init&n; *&n; * PARAMETERS:&t;&lt;none&gt;&n; *&n; * RETURN:&t;0: Success&n; *&n; * DESCRIPTION: Module initialization.&n; *&n; ****************************************************************************/
r_static
r_int
id|__init
DECL|function|ec_osl_init
id|ec_osl_init
(paren
r_void
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
macro_line|#ifdef ACPI_DEBUG
id|save_dbg_layer
op_assign
id|acpi_dbg_layer
suffix:semicolon
id|acpi_dbg_layer
op_assign
id|dbg_layer
suffix:semicolon
id|save_dbg_level
op_assign
id|acpi_dbg_level
suffix:semicolon
id|acpi_dbg_level
op_assign
id|dbg_level
suffix:semicolon
macro_line|#endif /*ACPI_DEBUG*/
id|status
op_assign
id|ec_initialize
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    ec_osl_cleanup&n; *&n; * PARAMETERS:&t;&lt;none&gt;&n; *&n; * RETURN:&t;&lt;none&gt;&n; *&n; * DESCRIPTION: Module cleanup.&n; *&n; ****************************************************************************/
r_static
r_void
id|__exit
DECL|function|ec_osl_cleanup
id|ec_osl_cleanup
c_func
(paren
r_void
)paren
(brace
id|ec_terminate
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef ACPI_DEBUG
id|acpi_dbg_layer
op_assign
id|save_dbg_layer
suffix:semicolon
id|acpi_dbg_level
op_assign
id|save_dbg_level
suffix:semicolon
macro_line|#endif /*ACPI_DEBUG*/
r_return
suffix:semicolon
)brace
DECL|variable|ec_osl_init
id|module_init
c_func
(paren
id|ec_osl_init
)paren
suffix:semicolon
DECL|variable|ec_osl_cleanup
id|module_exit
c_func
(paren
id|ec_osl_cleanup
)paren
suffix:semicolon
eof
