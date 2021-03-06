multiline_comment|/*&n; * event.c - exporting ACPI events via procfs&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; */
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;acpi/acpi_drivers.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_SYSTEM_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;event&quot;
)paren
multiline_comment|/* Global vars for handling event proc entry */
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|acpi_system_event_lock
)paren
suffix:semicolon
DECL|variable|event_is_open
r_int
id|event_is_open
op_assign
l_int|0
suffix:semicolon
r_extern
r_struct
id|list_head
id|acpi_bus_event_list
suffix:semicolon
r_extern
id|wait_queue_head_t
id|acpi_bus_event_queue
suffix:semicolon
r_static
r_int
DECL|function|acpi_system_open_event
id|acpi_system_open_event
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
id|acpi_system_event_lock
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
id|acpi_system_event_lock
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
id|acpi_system_event_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|acpi_system_read_event
id|acpi_system_read_event
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_bus_event
id|event
suffix:semicolon
r_static
r_char
id|str
(braket
id|ACPI_MAX_STRING
)braket
suffix:semicolon
r_static
r_int
id|chars_remaining
op_assign
l_int|0
suffix:semicolon
r_static
r_char
op_star
id|ptr
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_system_read_event&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chars_remaining
)paren
(brace
id|memset
c_func
(paren
op_amp
id|event
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|acpi_bus_event
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
op_logical_and
(paren
id|list_empty
c_func
(paren
op_amp
id|acpi_bus_event_list
)paren
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EAGAIN
)paren
suffix:semicolon
id|result
op_assign
id|acpi_bus_receive_event
c_func
(paren
op_amp
id|event
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|return_VALUE
c_func
(paren
op_minus
id|EIO
)paren
suffix:semicolon
)brace
id|chars_remaining
op_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;%s %s %08x %08x&bslash;n&quot;
comma
id|event.device_class
ques
c_cond
id|event.device_class
suffix:colon
l_string|&quot;&lt;unknown&gt;&quot;
comma
id|event.bus_id
ques
c_cond
id|event.bus_id
suffix:colon
l_string|&quot;&lt;unknown&gt;&quot;
comma
id|event.type
comma
id|event.data
)paren
suffix:semicolon
id|ptr
op_assign
id|str
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chars_remaining
OL
id|count
)paren
(brace
id|count
op_assign
id|chars_remaining
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|ptr
comma
id|count
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
op_star
id|ppos
op_add_assign
id|count
suffix:semicolon
id|chars_remaining
op_sub_assign
id|count
suffix:semicolon
id|ptr
op_add_assign
id|count
suffix:semicolon
id|return_VALUE
c_func
(paren
id|count
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_system_close_event
id|acpi_system_close_event
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
id|acpi_system_event_lock
)paren
suffix:semicolon
id|event_is_open
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irq
(paren
op_amp
id|acpi_system_event_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|acpi_system_poll_event
id|acpi_system_poll_event
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|acpi_bus_event_queue
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|acpi_bus_event_list
)paren
)paren
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|acpi_system_event_ops
r_static
r_struct
id|file_operations
id|acpi_system_event_ops
op_assign
(brace
dot
id|open
op_assign
id|acpi_system_open_event
comma
dot
id|read
op_assign
id|acpi_system_read_event
comma
dot
id|release
op_assign
id|acpi_system_close_event
comma
dot
id|poll
op_assign
id|acpi_system_poll_event
comma
)brace
suffix:semicolon
DECL|function|acpi_event_init
r_static
r_int
id|__init
id|acpi_event_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_event_init&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_disabled
)paren
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* &squot;event&squot; [R] */
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;event&quot;
comma
id|S_IRUSR
comma
id|acpi_root_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
id|entry-&gt;proc_fops
op_assign
op_amp
id|acpi_system_event_ops
suffix:semicolon
r_else
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unable to create &squot;%s&squot; proc fs entry&bslash;n&quot;
comma
l_string|&quot;event&quot;
)paren
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
id|return_VALUE
c_func
(paren
id|error
)paren
suffix:semicolon
)brace
DECL|variable|acpi_event_init
id|subsys_initcall
c_func
(paren
id|acpi_event_init
)paren
suffix:semicolon
eof
