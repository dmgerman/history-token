multiline_comment|/******************************************************************************&n; *&n; * Module Name: bn_osl.c&n; *   $Revision: 10 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;acpi.h&gt;
macro_line|#include &quot;bn.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andrew Grover&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ACPI Component Architecture (CA) - Button Driver&quot;
)paren
suffix:semicolon
DECL|macro|BN_PROC_ROOT
mdefine_line|#define BN_PROC_ROOT&t;&t;&quot;button&quot;
DECL|macro|BN_PROC_POWER_BUTTON
mdefine_line|#define BN_PROC_POWER_BUTTON&t;&quot;power&quot;
DECL|macro|BN_PROC_SLEEP_BUTTON
mdefine_line|#define BN_PROC_SLEEP_BUTTON&t;&quot;sleep&quot;
DECL|macro|BN_PROC_LID_SWITCH
mdefine_line|#define BN_PROC_LID_SWITCH&t;&quot;lid&quot;
r_extern
r_struct
id|proc_dir_entry
op_star
id|bm_proc_root
suffix:semicolon
DECL|variable|bn_proc_root
r_static
r_struct
id|proc_dir_entry
op_star
id|bn_proc_root
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:&t;bn_osl_add_device&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|bn_osl_add_device
id|bn_osl_add_device
c_func
(paren
id|BN_CONTEXT
op_star
id|button
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|button
)paren
(brace
r_return
id|AE_BAD_PARAMETER
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|button-&gt;type
)paren
(brace
r_case
id|BN_TYPE_POWER_BUTTON
suffix:colon
r_case
id|BN_TYPE_POWER_BUTTON_FIXED
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Power Button: found&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_mkdir
c_func
(paren
id|BN_PROC_POWER_BUTTON
comma
id|bn_proc_root
)paren
)paren
(brace
id|status
op_assign
id|AE_ERROR
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|BN_TYPE_SLEEP_BUTTON
suffix:colon
r_case
id|BN_TYPE_SLEEP_BUTTON_FIXED
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Sleep Button: found&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_mkdir
c_func
(paren
id|BN_PROC_SLEEP_BUTTON
comma
id|bn_proc_root
)paren
)paren
(brace
id|status
op_assign
id|AE_ERROR
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|BN_TYPE_LID_SWITCH
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Lid Switch: found&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_mkdir
c_func
(paren
id|BN_PROC_LID_SWITCH
comma
id|bn_proc_root
)paren
)paren
(brace
id|status
op_assign
id|AE_ERROR
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:&t;bn_osl_remove_device&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|bn_osl_remove_device
id|bn_osl_remove_device
(paren
id|BN_CONTEXT
op_star
id|button
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|button
)paren
(brace
r_return
id|AE_BAD_PARAMETER
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|button-&gt;type
)paren
(brace
r_case
id|BN_TYPE_POWER_BUTTON
suffix:colon
r_case
id|BN_TYPE_POWER_BUTTON_FIXED
suffix:colon
id|remove_proc_entry
c_func
(paren
id|BN_PROC_POWER_BUTTON
comma
id|bn_proc_root
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BN_TYPE_SLEEP_BUTTON
suffix:colon
r_case
id|BN_TYPE_SLEEP_BUTTON_FIXED
suffix:colon
id|remove_proc_entry
c_func
(paren
id|BN_PROC_SLEEP_BUTTON
comma
id|bn_proc_root
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BN_TYPE_LID_SWITCH
suffix:colon
id|remove_proc_entry
c_func
(paren
id|BN_PROC_LID_SWITCH
comma
id|bn_proc_root
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|AE_OK
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:&t;bn_osl_generate_event&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|bn_osl_generate_event
id|bn_osl_generate_event
(paren
id|u32
id|event
comma
id|BN_CONTEXT
op_star
id|button
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|button
)paren
(brace
r_return
id|AE_BAD_PARAMETER
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|BN_NOTIFY_STATUS_CHANGE
suffix:colon
r_switch
c_cond
(paren
id|button-&gt;type
)paren
(brace
r_case
id|BN_TYPE_POWER_BUTTON
suffix:colon
r_case
id|BN_TYPE_POWER_BUTTON_FIXED
suffix:colon
id|status
op_assign
id|bm_osl_generate_event
c_func
(paren
id|button-&gt;device_handle
comma
id|BN_PROC_ROOT
comma
id|BN_PROC_POWER_BUTTON
comma
id|event
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BN_TYPE_SLEEP_BUTTON
suffix:colon
r_case
id|BN_TYPE_SLEEP_BUTTON_FIXED
suffix:colon
id|status
op_assign
id|bm_osl_generate_event
c_func
(paren
id|button-&gt;device_handle
comma
id|BN_PROC_ROOT
comma
id|BN_PROC_SLEEP_BUTTON
comma
id|event
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BN_TYPE_LID_SWITCH
suffix:colon
id|status
op_assign
id|bm_osl_generate_event
c_func
(paren
id|button-&gt;device_handle
comma
id|BN_PROC_ROOT
comma
id|BN_PROC_LID_SWITCH
comma
id|event
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|AE_SUPPORT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|AE_BAD_PARAMETER
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    bn_osl_init&n; *&n; * PARAMETERS:&t;&lt;none&gt;&n; *&n; * RETURN:&t;0: Success&n; *&n; * DESCRIPTION: Module initialization.&n; *&n; ****************************************************************************/
r_static
r_int
id|__init
DECL|function|bn_osl_init
id|bn_osl_init
(paren
r_void
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
id|bn_proc_root
op_assign
id|proc_mkdir
c_func
(paren
id|BN_PROC_ROOT
comma
id|bm_proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bn_proc_root
)paren
(brace
id|status
op_assign
id|AE_ERROR
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|bn_initialize
c_func
(paren
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
id|remove_proc_entry
c_func
(paren
id|BN_PROC_ROOT
comma
id|bm_proc_root
)paren
suffix:semicolon
)brace
)brace
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
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    bn_osl_cleanup&n; *&n; * PARAMETERS:&t;&lt;none&gt;&n; *&n; * RETURN:&t;&lt;none&gt;&n; *&n; * DESCRIPTION: Module cleanup.&n; *&n; ****************************************************************************/
r_static
r_void
id|__exit
DECL|function|bn_osl_cleanup
id|bn_osl_cleanup
(paren
r_void
)paren
(brace
id|bn_terminate
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bn_proc_root
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|BN_PROC_ROOT
comma
id|bm_proc_root
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|variable|bn_osl_init
id|module_init
c_func
(paren
id|bn_osl_init
)paren
suffix:semicolon
DECL|variable|bn_osl_cleanup
id|module_exit
c_func
(paren
id|bn_osl_cleanup
)paren
suffix:semicolon
eof
