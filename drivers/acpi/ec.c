multiline_comment|/*&n; *  acpi_ec.c - ACPI Embedded Controller Driver ($Revision: 31 $)&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/compatmac.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;acpi_bus.h&quot;
macro_line|#include &quot;acpi_drivers.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_EC_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;acpi_ec&quot;
)paren
DECL|macro|PREFIX
mdefine_line|#define PREFIX&t;&t;&t;&quot;ACPI: &quot;
DECL|macro|ACPI_EC_FLAG_OBF
mdefine_line|#define ACPI_EC_FLAG_OBF&t;0x01&t;/* Output buffer full */
DECL|macro|ACPI_EC_FLAG_IBF
mdefine_line|#define ACPI_EC_FLAG_IBF&t;0x02&t;/* Input buffer full */
DECL|macro|ACPI_EC_FLAG_SCI
mdefine_line|#define ACPI_EC_FLAG_SCI&t;0x20&t;/* EC-SCI occurred */
DECL|macro|ACPI_EC_EVENT_OBF
mdefine_line|#define ACPI_EC_EVENT_OBF&t;0x01&t;/* Output buffer full */
DECL|macro|ACPI_EC_EVENT_IBE
mdefine_line|#define ACPI_EC_EVENT_IBE&t;0x02&t;/* Input buffer empty */
DECL|macro|ACPI_EC_UDELAY
mdefine_line|#define ACPI_EC_UDELAY&t;&t;100&t;/* Poll @ 100us increments */
DECL|macro|ACPI_EC_UDELAY_COUNT
mdefine_line|#define ACPI_EC_UDELAY_COUNT&t;1000&t;/* Wait 10ms max. during EC ops */
DECL|macro|ACPI_EC_UDELAY_GLK
mdefine_line|#define ACPI_EC_UDELAY_GLK&t;1000&t;/* Wait 1ms max. to get global lock */
DECL|macro|ACPI_EC_COMMAND_READ
mdefine_line|#define ACPI_EC_COMMAND_READ&t;0x80
DECL|macro|ACPI_EC_COMMAND_WRITE
mdefine_line|#define ACPI_EC_COMMAND_WRITE&t;0x81
DECL|macro|ACPI_EC_COMMAND_QUERY
mdefine_line|#define ACPI_EC_COMMAND_QUERY&t;0x84
r_static
r_int
id|acpi_ec_add
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
r_static
r_int
id|acpi_ec_remove
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
r_static
r_int
id|acpi_ec_start
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
r_static
r_int
id|acpi_ec_stop
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
DECL|variable|acpi_ec_driver
r_static
r_struct
id|acpi_driver
id|acpi_ec_driver
op_assign
(brace
id|name
suffix:colon
id|ACPI_EC_DRIVER_NAME
comma
r_class
suffix:colon
id|ACPI_EC_CLASS
comma
id|ids
suffix:colon
id|ACPI_EC_HID
comma
id|ops
suffix:colon
(brace
id|add
suffix:colon
id|acpi_ec_add
comma
id|remove
suffix:colon
id|acpi_ec_remove
comma
id|start
suffix:colon
id|acpi_ec_start
comma
id|stop
suffix:colon
id|acpi_ec_stop
comma
)brace
comma
)brace
suffix:semicolon
DECL|struct|acpi_ec
r_struct
id|acpi_ec
(brace
DECL|member|handle
id|acpi_handle
id|handle
suffix:semicolon
DECL|member|gpe_bit
r_int
r_int
id|gpe_bit
suffix:semicolon
DECL|member|status_port
r_int
r_int
id|status_port
suffix:semicolon
DECL|member|command_port
r_int
r_int
id|command_port
suffix:semicolon
DECL|member|data_port
r_int
r_int
id|data_port
suffix:semicolon
DECL|member|global_lock
r_int
r_int
id|global_lock
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;                             Transaction Management&n;   -------------------------------------------------------------------------- */
r_static
r_int
DECL|function|acpi_ec_wait
id|acpi_ec_wait
(paren
r_struct
id|acpi_ec
op_star
id|ec
comma
id|u8
id|event
)paren
(brace
id|u8
id|acpi_ec_status
op_assign
l_int|0
suffix:semicolon
id|u32
id|i
op_assign
id|ACPI_EC_UDELAY_COUNT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ec
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Poll the EC status register waiting for the event to occur. */
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|ACPI_EC_EVENT_OBF
suffix:colon
r_do
(brace
id|acpi_ec_status
op_assign
id|inb
c_func
(paren
id|ec-&gt;status_port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_ec_status
op_amp
id|ACPI_EC_FLAG_OBF
)paren
r_return
l_int|0
suffix:semicolon
id|udelay
c_func
(paren
id|ACPI_EC_UDELAY
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
OG
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_EC_EVENT_IBE
suffix:colon
r_do
(brace
id|acpi_ec_status
op_assign
id|inb
c_func
(paren
id|ec-&gt;status_port
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|acpi_ec_status
op_amp
id|ACPI_EC_FLAG_IBF
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|udelay
c_func
(paren
id|ACPI_EC_UDELAY
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|i
OG
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
op_minus
id|ETIME
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_ec_read
id|acpi_ec_read
(paren
r_struct
id|acpi_ec
op_star
id|ec
comma
id|u8
id|address
comma
id|u8
op_star
id|data
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
id|u32
id|glk
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_ec_read&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ec
op_logical_or
op_logical_neg
id|data
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
op_star
id|data
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ec-&gt;global_lock
)paren
(brace
id|status
op_assign
id|acpi_acquire_global_lock
c_func
(paren
id|ACPI_EC_UDELAY_GLK
comma
op_amp
id|glk
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
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ec-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ACPI_EC_COMMAND_READ
comma
id|ec-&gt;command_port
)paren
suffix:semicolon
id|result
op_assign
id|acpi_ec_wait
c_func
(paren
id|ec
comma
id|ACPI_EC_EVENT_IBE
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
id|outb
c_func
(paren
id|address
comma
id|ec-&gt;data_port
)paren
suffix:semicolon
id|result
op_assign
id|acpi_ec_wait
c_func
(paren
id|ec
comma
id|ACPI_EC_EVENT_OBF
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
op_star
id|data
op_assign
id|inb
c_func
(paren
id|ec-&gt;data_port
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Read [%02x] from address [%02x]&bslash;n&quot;
comma
op_star
id|data
comma
id|address
)paren
)paren
suffix:semicolon
id|end
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ec-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ec-&gt;global_lock
)paren
id|acpi_release_global_lock
c_func
(paren
id|glk
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
DECL|function|acpi_ec_write
id|acpi_ec_write
(paren
r_struct
id|acpi_ec
op_star
id|ec
comma
id|u8
id|address
comma
id|u8
id|data
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
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
id|u32
id|glk
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_ec_write&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ec
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ec-&gt;global_lock
)paren
(brace
id|status
op_assign
id|acpi_acquire_global_lock
c_func
(paren
id|ACPI_EC_UDELAY_GLK
comma
op_amp
id|glk
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
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ec-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ACPI_EC_COMMAND_WRITE
comma
id|ec-&gt;command_port
)paren
suffix:semicolon
id|result
op_assign
id|acpi_ec_wait
c_func
(paren
id|ec
comma
id|ACPI_EC_EVENT_IBE
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
id|outb
c_func
(paren
id|address
comma
id|ec-&gt;data_port
)paren
suffix:semicolon
id|result
op_assign
id|acpi_ec_wait
c_func
(paren
id|ec
comma
id|ACPI_EC_EVENT_IBE
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
id|outb
c_func
(paren
id|data
comma
id|ec-&gt;data_port
)paren
suffix:semicolon
id|result
op_assign
id|acpi_ec_wait
c_func
(paren
id|ec
comma
id|ACPI_EC_EVENT_IBE
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
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Wrote [%02x] to address [%02x]&bslash;n&quot;
comma
id|data
comma
id|address
)paren
)paren
suffix:semicolon
id|end
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ec-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ec-&gt;global_lock
)paren
id|acpi_release_global_lock
c_func
(paren
id|glk
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
DECL|function|acpi_ec_query
id|acpi_ec_query
(paren
r_struct
id|acpi_ec
op_star
id|ec
comma
id|u8
op_star
id|data
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
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
id|u32
id|glk
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_ec_query&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ec
op_logical_or
op_logical_neg
id|data
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
op_star
id|data
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ec-&gt;global_lock
)paren
(brace
id|status
op_assign
id|acpi_acquire_global_lock
c_func
(paren
id|ACPI_EC_UDELAY_GLK
comma
op_amp
id|glk
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
)brace
multiline_comment|/*&n;&t; * Query the EC to find out which _Qxx method we need to evaluate.&n;&t; * Note that successful completion of the query causes the ACPI_EC_SCI&n;&t; * bit to be cleared (and thus clearing the interrupt source).&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ec-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ACPI_EC_COMMAND_QUERY
comma
id|ec-&gt;command_port
)paren
suffix:semicolon
id|result
op_assign
id|acpi_ec_wait
c_func
(paren
id|ec
comma
id|ACPI_EC_EVENT_OBF
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
op_star
id|data
op_assign
id|inb
c_func
(paren
id|ec-&gt;data_port
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|data
)paren
id|result
op_assign
op_minus
id|ENODATA
suffix:semicolon
id|end
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ec-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ec-&gt;global_lock
)paren
id|acpi_release_global_lock
c_func
(paren
id|glk
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;                                Event Management&n;   -------------------------------------------------------------------------- */
DECL|struct|acpi_ec_query_data
r_struct
id|acpi_ec_query_data
(brace
DECL|member|handle
id|acpi_handle
id|handle
suffix:semicolon
DECL|member|data
id|u8
id|data
suffix:semicolon
)brace
suffix:semicolon
r_static
r_void
DECL|function|acpi_ec_gpe_query
id|acpi_ec_gpe_query
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|acpi_ec_query_data
op_star
id|query_data
op_assign
l_int|NULL
suffix:semicolon
r_static
r_char
id|object_name
(braket
l_int|5
)braket
op_assign
(brace
l_char|&squot;_&squot;
comma
l_char|&squot;Q&squot;
comma
l_char|&squot;0&squot;
comma
l_char|&squot;0&squot;
comma
l_char|&squot;&bslash;0&squot;
)brace
suffix:semicolon
r_const
r_char
id|hex
(braket
)braket
op_assign
(brace
l_char|&squot;0&squot;
comma
l_char|&squot;1&squot;
comma
l_char|&squot;2&squot;
comma
l_char|&squot;3&squot;
comma
l_char|&squot;4&squot;
comma
l_char|&squot;5&squot;
comma
l_char|&squot;6&squot;
comma
l_char|&squot;7&squot;
comma
l_char|&squot;8&squot;
comma
l_char|&squot;9&squot;
comma
l_char|&squot;A&squot;
comma
l_char|&squot;B&squot;
comma
l_char|&squot;C&squot;
comma
l_char|&squot;D&squot;
comma
l_char|&squot;E&squot;
comma
l_char|&squot;F&squot;
)brace
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_ec_gpe_query&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
suffix:semicolon
id|query_data
op_assign
(paren
r_struct
id|acpi_ec_query_data
op_star
)paren
id|data
suffix:semicolon
id|object_name
(braket
l_int|2
)braket
op_assign
id|hex
(braket
(paren
(paren
id|query_data-&gt;data
op_rshift
l_int|4
)paren
op_amp
l_int|0x0F
)paren
)braket
suffix:semicolon
id|object_name
(braket
l_int|3
)braket
op_assign
id|hex
(braket
(paren
id|query_data-&gt;data
op_amp
l_int|0x0F
)paren
)braket
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Evaluating %s&bslash;n&quot;
comma
id|object_name
)paren
)paren
suffix:semicolon
id|acpi_evaluate
c_func
(paren
id|query_data-&gt;handle
comma
id|object_name
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|query_data
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|acpi_ec_gpe_handler
id|acpi_ec_gpe_handler
(paren
r_void
op_star
id|data
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_ec
op_star
id|ec
op_assign
(paren
r_struct
id|acpi_ec
op_star
)paren
id|data
suffix:semicolon
id|u8
id|value
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_ec_query_data
op_star
id|query_data
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ec
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ec-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|value
op_assign
id|inb
c_func
(paren
id|ec-&gt;command_port
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ec-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* TBD: Implement asynch events!&n;&t; * NOTE: All we care about are EC-SCI&squot;s.  Other EC events are&n;&t; *       handled via polling (yuck!).  This is because some systems&n;&t; *       treat EC-SCIs as level (versus EDGE!) triggered, preventing&n;&t; *       a purely interrupt-driven approach (grumble, grumble).&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|value
op_amp
id|ACPI_EC_FLAG_SCI
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|acpi_ec_query
c_func
(paren
id|ec
comma
op_amp
id|value
)paren
)paren
r_return
suffix:semicolon
id|query_data
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|acpi_ec_query_data
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|query_data
)paren
r_return
suffix:semicolon
id|query_data-&gt;handle
op_assign
id|ec-&gt;handle
suffix:semicolon
id|query_data-&gt;data
op_assign
id|value
suffix:semicolon
id|status
op_assign
id|acpi_os_queue_for_execution
c_func
(paren
id|OSD_PRIORITY_GPE
comma
id|acpi_ec_gpe_query
comma
id|query_data
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
id|kfree
c_func
(paren
id|query_data
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;                             Address Space Management&n;   -------------------------------------------------------------------------- */
r_static
id|acpi_status
DECL|function|acpi_ec_space_setup
id|acpi_ec_space_setup
(paren
id|acpi_handle
id|region_handle
comma
id|u32
id|function
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
op_star
id|return_context
)paren
(brace
multiline_comment|/*&n;&t; * The EC object is in the handler context and is needed&n;&t; * when calling the acpi_ec_space_handler.&n;&t; */
op_star
id|return_context
op_assign
id|handler_context
suffix:semicolon
r_return
id|AE_OK
suffix:semicolon
)brace
r_static
id|acpi_status
DECL|function|acpi_ec_space_handler
id|acpi_ec_space_handler
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|acpi_integer
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_ec
op_star
id|ec
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_ec_space_handler&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|address
OG
l_int|0xFF
)paren
op_logical_or
(paren
id|bit_width
op_ne
l_int|8
)paren
op_logical_or
op_logical_neg
id|value
op_logical_or
op_logical_neg
id|handler_context
)paren
id|return_VALUE
c_func
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
id|ec
op_assign
(paren
r_struct
id|acpi_ec
op_star
)paren
id|handler_context
suffix:semicolon
r_switch
c_cond
(paren
id|function
)paren
(brace
r_case
id|ACPI_READ
suffix:colon
id|result
op_assign
id|acpi_ec_read
c_func
(paren
id|ec
comma
(paren
id|u8
)paren
id|address
comma
(paren
id|u8
op_star
)paren
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_WRITE
suffix:colon
id|result
op_assign
id|acpi_ec_write
c_func
(paren
id|ec
comma
(paren
id|u8
)paren
id|address
comma
(paren
id|u8
)paren
op_star
id|value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|result
)paren
(brace
r_case
op_minus
id|EINVAL
suffix:colon
id|return_VALUE
c_func
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ENODEV
suffix:colon
id|return_VALUE
c_func
(paren
id|AE_NOT_FOUND
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ETIME
suffix:colon
id|return_VALUE
c_func
(paren
id|AE_TIME
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|return_VALUE
c_func
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;                              FS Interface (/proc)&n;   -------------------------------------------------------------------------- */
DECL|variable|acpi_ec_dir
r_struct
id|proc_dir_entry
op_star
id|acpi_ec_dir
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
DECL|function|acpi_ec_read_info
id|acpi_ec_read_info
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|acpi_ec
op_star
id|ec
op_assign
(paren
r_struct
id|acpi_ec
op_star
)paren
id|data
suffix:semicolon
r_char
op_star
id|p
op_assign
id|page
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_ec_read_info&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ec
op_logical_or
(paren
id|off
op_ne
l_int|0
)paren
)paren
r_goto
id|end
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;gpe bit:                 0x%02x&bslash;n&quot;
comma
(paren
id|u32
)paren
id|ec-&gt;gpe_bit
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;ports:                   0x%02x, 0x%02x&bslash;n&quot;
comma
(paren
id|u32
)paren
id|ec-&gt;status_port
comma
(paren
id|u32
)paren
id|ec-&gt;data_port
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;use global lock:         %s&bslash;n&quot;
comma
id|ec-&gt;global_lock
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|end
suffix:colon
id|len
op_assign
(paren
id|p
op_minus
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
id|off
op_plus
id|count
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|count
)paren
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
id|return_VALUE
c_func
(paren
id|len
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_ec_add_fs
id|acpi_ec_add_fs
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_ec_add_fs&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_ec_dir
)paren
(brace
id|acpi_ec_dir
op_assign
id|proc_mkdir
c_func
(paren
id|ACPI_EC_CLASS
comma
id|acpi_root_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_ec_dir
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|acpi_device_dir
c_func
(paren
id|device
)paren
)paren
(brace
id|acpi_device_dir
c_func
(paren
id|device
)paren
op_assign
id|proc_mkdir
c_func
(paren
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
id|acpi_ec_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_device_dir
c_func
(paren
id|device
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|entry
op_assign
id|create_proc_read_entry
c_func
(paren
id|ACPI_EC_FILE_INFO
comma
id|S_IRUGO
comma
id|acpi_device_dir
c_func
(paren
id|device
)paren
comma
id|acpi_ec_read_info
comma
id|acpi_driver_data
c_func
(paren
id|device
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Unable to create &squot;%s&squot; fs entry&bslash;n&quot;
comma
id|ACPI_EC_FILE_INFO
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
r_static
r_int
DECL|function|acpi_ec_remove_fs
id|acpi_ec_remove_fs
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_ec_remove_fs&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_ec_dir
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_device_dir
c_func
(paren
id|device
)paren
)paren
id|remove_proc_entry
c_func
(paren
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
id|acpi_ec_dir
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;                               Driver Interface&n;   -------------------------------------------------------------------------- */
r_static
r_int
DECL|function|acpi_ec_add
id|acpi_ec_add
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
id|acpi_ec
op_star
id|ec
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_ec_add&quot;
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
id|ec
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|acpi_ec
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ec
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
id|ec
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|acpi_ec
)paren
)paren
suffix:semicolon
id|ec-&gt;handle
op_assign
id|device-&gt;handle
suffix:semicolon
id|ec-&gt;lock
op_assign
id|SPIN_LOCK_UNLOCKED
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
id|ACPI_EC_DEVICE_NAME
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
id|ACPI_EC_CLASS
)paren
suffix:semicolon
id|acpi_driver_data
c_func
(paren
id|device
)paren
op_assign
id|ec
suffix:semicolon
multiline_comment|/* Use the global lock for all EC transactions? */
id|acpi_evaluate_integer
c_func
(paren
id|ec-&gt;handle
comma
l_string|&quot;_GLK&quot;
comma
l_int|NULL
comma
op_amp
id|ec-&gt;global_lock
)paren
suffix:semicolon
multiline_comment|/* Get GPE bit assignment (EC events). */
id|status
op_assign
id|acpi_evaluate_integer
c_func
(paren
id|ec-&gt;handle
comma
l_string|&quot;_GPE&quot;
comma
l_int|NULL
comma
op_amp
id|ec-&gt;gpe_bit
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
l_string|&quot;Error obtaining GPE bit assignment&bslash;n&quot;
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
id|result
op_assign
id|acpi_ec_add_fs
c_func
(paren
id|device
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
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;%s [%s] (gpe %d)&bslash;n&quot;
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
(paren
id|u32
)paren
id|ec-&gt;gpe_bit
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
id|ec
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
DECL|function|acpi_ec_remove
id|acpi_ec_remove
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
id|acpi_ec
op_star
id|ec
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_ec_remove&quot;
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
id|ec
op_assign
(paren
r_struct
id|acpi_ec
op_star
)paren
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
id|acpi_ec_remove_fs
c_func
(paren
id|device
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ec
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
DECL|function|acpi_ec_start
id|acpi_ec_start
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
id|acpi_ec
op_star
id|ec
op_assign
l_int|NULL
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
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_ec_start&quot;
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
id|ec
op_assign
(paren
r_struct
id|acpi_ec
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
id|ec
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get I/O port addresses&n;&t; */
id|status
op_assign
id|acpi_get_current_resources
c_func
(paren
id|ec-&gt;handle
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
l_string|&quot;Error getting I/O port addresses&quot;
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
id|resource
op_assign
(paren
id|acpi_resource
op_star
)paren
id|buffer.pointer
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resource
op_logical_or
(paren
id|resource-&gt;id
op_ne
id|ACPI_RSTYPE_IO
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid or missing resource&bslash;n&quot;
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
id|ec-&gt;data_port
op_assign
id|resource-&gt;data.io.min_base_address
suffix:semicolon
id|resource
op_assign
id|ACPI_NEXT_RESOURCE
c_func
(paren
id|resource
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resource
op_logical_or
(paren
id|resource-&gt;id
op_ne
id|ACPI_RSTYPE_IO
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid or missing resource&bslash;n&quot;
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
id|ec-&gt;command_port
op_assign
id|ec-&gt;status_port
op_assign
id|resource-&gt;data.io.min_base_address
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;gpe=0x%02x, ports=0x%2x,0x%2x&bslash;n&quot;
comma
(paren
id|u32
)paren
id|ec-&gt;gpe_bit
comma
(paren
id|u32
)paren
id|ec-&gt;command_port
comma
(paren
id|u32
)paren
id|ec-&gt;data_port
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Install GPE handler&n;&t; */
id|status
op_assign
id|acpi_install_gpe_handler
c_func
(paren
id|ec-&gt;gpe_bit
comma
id|ACPI_EVENT_EDGE_TRIGGERED
comma
op_amp
id|acpi_ec_gpe_handler
comma
id|ec
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
id|status
op_assign
id|acpi_install_address_space_handler
(paren
id|ec-&gt;handle
comma
id|ACPI_ADR_SPACE_EC
comma
op_amp
id|acpi_ec_space_handler
comma
op_amp
id|acpi_ec_space_setup
comma
id|ec
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
id|acpi_remove_address_space_handler
c_func
(paren
id|ec-&gt;handle
comma
id|ACPI_ADR_SPACE_EC
comma
op_amp
id|acpi_ec_space_handler
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
id|end
suffix:colon
id|kfree
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
DECL|function|acpi_ec_stop
id|acpi_ec_stop
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
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_ec
op_star
id|ec
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_ec_stop&quot;
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
id|ec
op_assign
(paren
r_struct
id|acpi_ec
op_star
)paren
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
id|status
op_assign
id|acpi_remove_address_space_handler
c_func
(paren
id|ec-&gt;handle
comma
id|ACPI_ADR_SPACE_EC
comma
op_amp
id|acpi_ec_space_handler
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
id|status
op_assign
id|acpi_remove_gpe_handler
c_func
(paren
id|ec-&gt;gpe_bit
comma
op_amp
id|acpi_ec_gpe_handler
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
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|acpi_ec_init
id|acpi_ec_init
(paren
r_void
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_ec_init&quot;
)paren
suffix:semicolon
id|result
op_assign
id|acpi_bus_register_driver
c_func
(paren
op_amp
id|acpi_ec_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|ACPI_EC_CLASS
comma
id|acpi_root_dir
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
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_void
id|__exit
DECL|function|acpi_ec_exit
id|acpi_ec_exit
(paren
r_void
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_ec_exit&quot;
)paren
suffix:semicolon
id|result
op_assign
id|acpi_bus_unregister_driver
c_func
(paren
op_amp
id|acpi_ec_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
id|remove_proc_entry
c_func
(paren
id|ACPI_EC_CLASS
comma
id|acpi_root_dir
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
eof