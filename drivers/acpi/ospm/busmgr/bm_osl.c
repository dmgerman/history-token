multiline_comment|/*****************************************************************************&n; *&n; * Module Name: bm_osl.c&n; *   $Revision: 11 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;acpi.h&gt;
macro_line|#include &quot;bm.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andrew Grover&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ACPI Component Architecture (CA) - ACPI Bus Manager&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
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
multiline_comment|/*****************************************************************************&n; *                               Types &amp; Defines&n; *****************************************************************************/
r_typedef
r_struct
(brace
DECL|member|device_handle
id|BM_HANDLE
id|device_handle
suffix:semicolon
DECL|member|device_type
r_char
op_star
id|device_type
suffix:semicolon
DECL|member|device_instance
r_char
op_star
id|device_instance
suffix:semicolon
DECL|member|event_type
id|u32
id|event_type
suffix:semicolon
DECL|member|event_data
id|u32
id|event_data
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|typedef|BM_OSL_EVENT
)brace
id|BM_OSL_EVENT
suffix:semicolon
DECL|macro|BM_PROC_ROOT
mdefine_line|#define BM_PROC_ROOT&t;&t;&quot;acpi&quot;
DECL|macro|BM_PROC_EVENT
mdefine_line|#define BM_PROC_EVENT&t;&t;&quot;event&quot;
DECL|macro|BM_PROC_DEVICES
mdefine_line|#define BM_PROC_DEVICES&t;&t;&quot;devices&quot;
DECL|macro|BM_MAX_STRING_LENGTH
mdefine_line|#define BM_MAX_STRING_LENGTH&t;80
multiline_comment|/****************************************************************************&n; *                                  Globals&n; ****************************************************************************/
DECL|variable|bm_proc_root
r_struct
id|proc_dir_entry
op_star
id|bm_proc_root
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|bm_proc_event
r_static
r_struct
id|proc_dir_entry
op_star
id|bm_proc_event
op_assign
l_int|NULL
suffix:semicolon
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
r_extern
id|BM_NODE_LIST
id|node_list
suffix:semicolon
DECL|variable|bm_osl_event_lock
r_static
id|spinlock_t
id|bm_osl_event_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|bm_event_list
)paren
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|bm_event_wait_queue
)paren
suffix:semicolon
DECL|variable|event_is_open
r_static
r_int
id|event_is_open
op_assign
l_int|0
suffix:semicolon
multiline_comment|/****************************************************************************&n; *                                 Functions&n; ****************************************************************************/
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:&t;bm_osl_generate_event&n; *&n; * DESCRIPTION: Generates an event for user-space consumption by writing&n; *              the event data to the &squot;event&squot; file.&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|bm_osl_generate_event
id|bm_osl_generate_event
(paren
id|BM_HANDLE
id|device_handle
comma
r_char
op_star
id|device_type
comma
r_char
op_star
id|device_instance
comma
id|u32
id|event_type
comma
id|u32
id|event_data
)paren
(brace
id|BM_OSL_EVENT
op_star
id|event
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* drop event on the floor if no one&squot;s listening */
r_if
c_cond
(paren
op_logical_neg
id|event_is_open
)paren
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate a new event structure.&n;&t; */
id|event
op_assign
id|acpi_os_callocate
c_func
(paren
r_sizeof
(paren
id|BM_OSL_EVENT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event
)paren
r_goto
id|alloc_error
suffix:semicolon
id|event-&gt;device_type
op_assign
id|acpi_os_callocate
c_func
(paren
id|strlen
c_func
(paren
id|device_type
)paren
op_plus
r_sizeof
(paren
r_char
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event-&gt;device_type
)paren
r_goto
id|alloc_error
suffix:semicolon
id|event-&gt;device_instance
op_assign
id|acpi_os_callocate
c_func
(paren
id|strlen
c_func
(paren
id|device_instance
)paren
op_plus
r_sizeof
(paren
r_char
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|event-&gt;device_instance
)paren
r_goto
id|alloc_error
suffix:semicolon
multiline_comment|/*&n;&t; * Set event data.&n;&t; */
id|event-&gt;device_handle
op_assign
id|device_handle
suffix:semicolon
id|strcpy
c_func
(paren
id|event-&gt;device_type
comma
id|device_type
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|event-&gt;device_instance
comma
id|device_instance
)paren
suffix:semicolon
id|event-&gt;event_type
op_assign
id|event_type
suffix:semicolon
id|event-&gt;event_data
op_assign
id|event_data
suffix:semicolon
multiline_comment|/*&n;&t; * Add to the end of our event list.&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|bm_osl_event_lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|event-&gt;list
comma
op_amp
id|bm_event_list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|bm_osl_event_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Signal waiting threads (if any).&n;&t; */
id|wake_up_interruptible
c_func
(paren
op_amp
id|bm_event_wait_queue
)paren
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
id|alloc_error
suffix:colon
r_if
c_cond
(paren
id|event-&gt;device_instance
)paren
id|acpi_os_free
c_func
(paren
id|event-&gt;device_instance
)paren
suffix:semicolon
r_if
c_cond
(paren
id|event-&gt;device_type
)paren
id|acpi_os_free
c_func
(paren
id|event-&gt;device_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|event
)paren
id|acpi_os_free
c_func
(paren
id|event
)paren
suffix:semicolon
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
DECL|function|bm_osl_open_event
r_static
r_int
id|bm_osl_open_event
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
id|spin_lock_irq
(paren
op_amp
id|bm_osl_event_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|event_is_open
)paren
(brace
r_goto
id|out_busy
suffix:semicolon
)brace
id|event_is_open
op_assign
l_int|1
suffix:semicolon
id|spin_unlock_irq
(paren
op_amp
id|bm_osl_event_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_busy
suffix:colon
id|spin_unlock_irq
(paren
op_amp
id|bm_osl_event_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
DECL|function|bm_osl_close_event
r_static
r_int
id|bm_osl_close_event
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
id|event_is_open
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:&t;bm_osl_read_event&n; *&n; * DESCRIPTION: Handles reads to the &squot;event&squot; file by blocking user-mode &n; *              threads until data (an event) is generated.&n; *&n; ****************************************************************************/
r_static
id|ssize_t
DECL|function|bm_osl_read_event
id|bm_osl_read_event
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_char
id|str
(braket
id|BM_MAX_STRING_LENGTH
)braket
suffix:semicolon
r_int
id|size
suffix:semicolon
id|BM_OSL_EVENT
op_star
id|event
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|BM_MAX_STRING_LENGTH
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|bm_event_list
)paren
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|bm_event_wait_queue
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|bm_event_list
)paren
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|bm_event_wait_queue
comma
op_amp
id|wait
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|bm_osl_event_lock
comma
id|flags
)paren
suffix:semicolon
id|event
op_assign
id|list_entry
c_func
(paren
id|bm_event_list.next
comma
id|BM_OSL_EVENT
comma
id|list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|event-&gt;list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|bm_osl_event_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* BUG: buffer overrun? */
id|size
op_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;%s %s %08x %08x&bslash;n&quot;
comma
id|event-&gt;device_type
comma
id|event-&gt;device_instance
comma
id|event-&gt;event_type
comma
id|event-&gt;event_data
)paren
suffix:semicolon
id|acpi_os_free
c_func
(paren
id|event-&gt;device_type
)paren
suffix:semicolon
id|acpi_os_free
c_func
(paren
id|event-&gt;device_instance
)paren
suffix:semicolon
id|acpi_os_free
c_func
(paren
id|event
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|str
comma
id|size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|ppos
op_add_assign
id|size
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|variable|proc_event_operations
r_struct
id|file_operations
id|proc_event_operations
op_assign
(brace
id|open
suffix:colon
id|bm_osl_open_event
comma
id|read
suffix:colon
id|bm_osl_read_event
comma
id|release
suffix:colon
id|bm_osl_close_event
comma
)brace
suffix:semicolon
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    bm_osl_init&n; *&n; ****************************************************************************/
r_int
DECL|function|bm_osl_init
id|bm_osl_init
c_func
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
id|bm_proc_root
op_assign
id|proc_mkdir
c_func
(paren
id|BM_PROC_ROOT
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bm_proc_root
)paren
(brace
r_return
id|AE_ERROR
suffix:semicolon
)brace
id|bm_proc_event
op_assign
id|create_proc_entry
c_func
(paren
id|BM_PROC_EVENT
comma
id|S_IRUSR
comma
id|bm_proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bm_proc_event
)paren
(brace
id|bm_proc_event-&gt;proc_fops
op_assign
op_amp
id|proc_event_operations
suffix:semicolon
)brace
id|status
op_assign
id|bm_initialize
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
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    bm_osl_cleanup&n; *&n; ****************************************************************************/
r_void
DECL|function|bm_osl_cleanup
id|bm_osl_cleanup
c_func
(paren
r_void
)paren
(brace
id|bm_terminate
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bm_proc_event
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|BM_PROC_EVENT
comma
id|bm_proc_root
)paren
suffix:semicolon
id|bm_proc_event
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bm_proc_root
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|BM_PROC_ROOT
comma
l_int|NULL
)paren
suffix:semicolon
id|bm_proc_root
op_assign
l_int|NULL
suffix:semicolon
)brace
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
DECL|variable|bm_osl_init
id|module_init
c_func
(paren
id|bm_osl_init
)paren
suffix:semicolon
DECL|variable|bm_osl_cleanup
id|module_exit
c_func
(paren
id|bm_osl_cleanup
)paren
suffix:semicolon
multiline_comment|/****************************************************************************&n; *                                  Symbols&n; ****************************************************************************/
multiline_comment|/* bm.c */
DECL|variable|bm_get_node
id|EXPORT_SYMBOL
c_func
(paren
id|bm_get_node
)paren
suffix:semicolon
multiline_comment|/* bmdriver.c */
DECL|variable|bm_get_device_power_state
id|EXPORT_SYMBOL
c_func
(paren
id|bm_get_device_power_state
)paren
suffix:semicolon
DECL|variable|bm_set_device_power_state
id|EXPORT_SYMBOL
c_func
(paren
id|bm_set_device_power_state
)paren
suffix:semicolon
DECL|variable|bm_get_device_info
id|EXPORT_SYMBOL
c_func
(paren
id|bm_get_device_info
)paren
suffix:semicolon
DECL|variable|bm_get_device_status
id|EXPORT_SYMBOL
c_func
(paren
id|bm_get_device_status
)paren
suffix:semicolon
DECL|variable|bm_get_device_context
id|EXPORT_SYMBOL
c_func
(paren
id|bm_get_device_context
)paren
suffix:semicolon
DECL|variable|bm_register_driver
id|EXPORT_SYMBOL
c_func
(paren
id|bm_register_driver
)paren
suffix:semicolon
DECL|variable|bm_unregister_driver
id|EXPORT_SYMBOL
c_func
(paren
id|bm_unregister_driver
)paren
suffix:semicolon
multiline_comment|/* bmsearch.c */
DECL|variable|bm_search
id|EXPORT_SYMBOL
c_func
(paren
id|bm_search
)paren
suffix:semicolon
multiline_comment|/* bmrequest.c */
DECL|variable|bm_request
id|EXPORT_SYMBOL
c_func
(paren
id|bm_request
)paren
suffix:semicolon
multiline_comment|/* bmutils.c */
DECL|variable|bm_extract_package_data
id|EXPORT_SYMBOL
c_func
(paren
id|bm_extract_package_data
)paren
suffix:semicolon
DECL|variable|bm_evaluate_object
id|EXPORT_SYMBOL
c_func
(paren
id|bm_evaluate_object
)paren
suffix:semicolon
DECL|variable|bm_evaluate_simple_integer
id|EXPORT_SYMBOL
c_func
(paren
id|bm_evaluate_simple_integer
)paren
suffix:semicolon
DECL|variable|bm_evaluate_reference_list
id|EXPORT_SYMBOL
c_func
(paren
id|bm_evaluate_reference_list
)paren
suffix:semicolon
DECL|variable|bm_copy_to_buffer
id|EXPORT_SYMBOL
c_func
(paren
id|bm_copy_to_buffer
)paren
suffix:semicolon
DECL|variable|bm_cast_buffer
id|EXPORT_SYMBOL
c_func
(paren
id|bm_cast_buffer
)paren
suffix:semicolon
multiline_comment|/* bm_proc.c */
DECL|variable|bm_osl_generate_event
id|EXPORT_SYMBOL
c_func
(paren
id|bm_osl_generate_event
)paren
suffix:semicolon
DECL|variable|bm_proc_root
id|EXPORT_SYMBOL
c_func
(paren
id|bm_proc_root
)paren
suffix:semicolon
eof
