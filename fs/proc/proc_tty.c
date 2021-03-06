multiline_comment|/*&n; * proc_tty.c -- handles /proc/tty&n; *&n; * Copyright 1997, Theodore Ts&squot;o&n; */
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
r_static
r_int
id|tty_ldiscs_read_proc
c_func
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
suffix:semicolon
multiline_comment|/*&n; * The /proc/tty directory inodes...&n; */
DECL|variable|proc_tty_ldisc
DECL|variable|proc_tty_driver
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_tty_ldisc
comma
op_star
id|proc_tty_driver
suffix:semicolon
multiline_comment|/*&n; * This is the handler for /proc/tty/drivers&n; */
DECL|function|show_tty_range
r_static
r_void
id|show_tty_range
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_struct
id|tty_driver
op_star
id|p
comma
id|dev_t
id|from
comma
r_int
id|num
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%-20s &quot;
comma
id|p-&gt;driver_name
ques
c_cond
id|p-&gt;driver_name
suffix:colon
l_string|&quot;unknown&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;/dev/%-8s &quot;
comma
id|p-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;num
OG
l_int|1
)paren
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%3d %d-%d &quot;
comma
id|MAJOR
c_func
(paren
id|from
)paren
comma
id|MINOR
c_func
(paren
id|from
)paren
comma
id|MINOR
c_func
(paren
id|from
)paren
op_plus
id|num
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%3d %7d &quot;
comma
id|MAJOR
c_func
(paren
id|from
)paren
comma
id|MINOR
c_func
(paren
id|from
)paren
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|p-&gt;type
)paren
(brace
r_case
id|TTY_DRIVER_TYPE_SYSTEM
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;system&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;subtype
op_eq
id|SYSTEM_TYPE_TTY
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;:/dev/tty&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|p-&gt;subtype
op_eq
id|SYSTEM_TYPE_SYSCONS
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;:console&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|p-&gt;subtype
op_eq
id|SYSTEM_TYPE_CONSOLE
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;:vtmaster&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TTY_DRIVER_TYPE_CONSOLE
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;console&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TTY_DRIVER_TYPE_SERIAL
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;serial&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TTY_DRIVER_TYPE_PTY
suffix:colon
r_if
c_cond
(paren
id|p-&gt;subtype
op_eq
id|PTY_TYPE_MASTER
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;pty:master&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|p-&gt;subtype
op_eq
id|PTY_TYPE_SLAVE
)paren
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;pty:slave&quot;
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;pty&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;type:%d.%d&quot;
comma
id|p-&gt;type
comma
id|p-&gt;subtype
)paren
suffix:semicolon
)brace
id|seq_putc
c_func
(paren
id|m
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
DECL|function|show_tty_driver
r_static
r_int
id|show_tty_driver
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
r_struct
id|tty_driver
op_star
id|p
op_assign
id|v
suffix:semicolon
id|dev_t
id|from
op_assign
id|MKDEV
c_func
(paren
id|p-&gt;major
comma
id|p-&gt;minor_start
)paren
suffix:semicolon
id|dev_t
id|to
op_assign
id|from
op_plus
id|p-&gt;num
suffix:semicolon
r_if
c_cond
(paren
op_amp
id|p-&gt;tty_drivers
op_eq
id|tty_drivers.next
)paren
(brace
multiline_comment|/* pseudo-drivers first */
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%-20s /dev/%-8s &quot;
comma
l_string|&quot;/dev/tty&quot;
comma
l_string|&quot;tty&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%3d %7d &quot;
comma
id|TTYAUX_MAJOR
comma
l_int|0
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;system:/dev/tty&bslash;n&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%-20s /dev/%-8s &quot;
comma
l_string|&quot;/dev/console&quot;
comma
l_string|&quot;console&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%3d %7d &quot;
comma
id|TTYAUX_MAJOR
comma
l_int|1
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;system:console&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_UNIX98_PTYS
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%-20s /dev/%-8s &quot;
comma
l_string|&quot;/dev/ptmx&quot;
comma
l_string|&quot;ptmx&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%3d %7d &quot;
comma
id|TTYAUX_MAJOR
comma
l_int|2
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;system&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VT
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%-20s /dev/%-8s &quot;
comma
l_string|&quot;/dev/vc/0&quot;
comma
l_string|&quot;vc/0&quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;%3d %7d &quot;
comma
id|TTY_MAJOR
comma
l_int|0
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|m
comma
l_string|&quot;system:vtmaster&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_while
c_loop
(paren
id|MAJOR
c_func
(paren
id|from
)paren
OL
id|MAJOR
c_func
(paren
id|to
)paren
)paren
(brace
id|dev_t
id|next
op_assign
id|MKDEV
c_func
(paren
id|MAJOR
c_func
(paren
id|from
)paren
op_plus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|show_tty_range
c_func
(paren
id|m
comma
id|p
comma
id|from
comma
id|next
op_minus
id|from
)paren
suffix:semicolon
id|from
op_assign
id|next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|from
op_ne
id|to
)paren
id|show_tty_range
c_func
(paren
id|m
comma
id|p
comma
id|from
comma
id|to
op_minus
id|from
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* iterator */
DECL|function|t_start
r_static
r_void
op_star
id|t_start
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|list_head
op_star
id|p
suffix:semicolon
id|loff_t
id|l
op_assign
op_star
id|pos
suffix:semicolon
id|list_for_each
c_func
(paren
id|p
comma
op_amp
id|tty_drivers
)paren
r_if
c_cond
(paren
op_logical_neg
id|l
op_decrement
)paren
r_return
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|tty_driver
comma
id|tty_drivers
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|t_next
r_static
r_void
op_star
id|t_next
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
comma
id|loff_t
op_star
id|pos
)paren
(brace
r_struct
id|list_head
op_star
id|p
op_assign
(paren
(paren
r_struct
id|tty_driver
op_star
)paren
id|v
)paren
op_member_access_from_pointer
id|tty_drivers.next
suffix:semicolon
(paren
op_star
id|pos
)paren
op_increment
suffix:semicolon
r_return
id|p
op_eq
op_amp
id|tty_drivers
ques
c_cond
l_int|NULL
suffix:colon
id|list_entry
c_func
(paren
id|p
comma
r_struct
id|tty_driver
comma
id|tty_drivers
)paren
suffix:semicolon
)brace
DECL|function|t_stop
r_static
r_void
id|t_stop
c_func
(paren
r_struct
id|seq_file
op_star
id|m
comma
r_void
op_star
id|v
)paren
(brace
)brace
DECL|variable|tty_drivers_op
r_static
r_struct
id|seq_operations
id|tty_drivers_op
op_assign
(brace
dot
id|start
op_assign
id|t_start
comma
dot
id|next
op_assign
id|t_next
comma
dot
id|stop
op_assign
id|t_stop
comma
dot
id|show
op_assign
id|show_tty_driver
)brace
suffix:semicolon
DECL|function|tty_drivers_open
r_static
r_int
id|tty_drivers_open
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
r_return
id|seq_open
c_func
(paren
id|file
comma
op_amp
id|tty_drivers_op
)paren
suffix:semicolon
)brace
DECL|variable|proc_tty_drivers_operations
r_static
r_struct
id|file_operations
id|proc_tty_drivers_operations
op_assign
(brace
dot
id|open
op_assign
id|tty_drivers_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|seq_release
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the handler for /proc/tty/ldiscs&n; */
DECL|function|tty_ldiscs_read_proc
r_static
r_int
id|tty_ldiscs_read_proc
c_func
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
r_int
id|i
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
suffix:semicolon
r_struct
id|tty_ldisc
op_star
id|ld
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_LDISCS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ld
op_assign
id|tty_ldisc_get
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ld
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%-10s %2d&bslash;n&quot;
comma
id|ld-&gt;name
ques
c_cond
id|ld-&gt;name
suffix:colon
l_string|&quot;???&quot;
comma
id|i
)paren
suffix:semicolon
id|tty_ldisc_put
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_plus
id|begin
OG
id|off
op_plus
id|count
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|len
op_plus
id|begin
OL
id|off
)paren
(brace
id|begin
op_add_assign
id|len
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_ge
id|NR_LDISCS
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ge
id|len
op_plus
id|begin
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
(paren
id|off
op_minus
id|begin
)paren
suffix:semicolon
r_return
(paren
(paren
id|count
OL
id|begin
op_plus
id|len
op_minus
id|off
)paren
ques
c_cond
id|count
suffix:colon
id|begin
op_plus
id|len
op_minus
id|off
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function is called by tty_register_driver() to handle&n; * registering the driver&squot;s /proc handler into /proc/tty/driver/&lt;foo&gt;&n; */
DECL|function|proc_tty_register_driver
r_void
id|proc_tty_register_driver
c_func
(paren
r_struct
id|tty_driver
op_star
id|driver
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|driver-&gt;read_proc
op_logical_and
op_logical_neg
id|driver-&gt;write_proc
)paren
op_logical_or
op_logical_neg
id|driver-&gt;driver_name
op_logical_or
id|driver-&gt;proc_entry
)paren
r_return
suffix:semicolon
id|ent
op_assign
id|create_proc_entry
c_func
(paren
id|driver-&gt;driver_name
comma
l_int|0
comma
id|proc_tty_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_return
suffix:semicolon
id|ent-&gt;read_proc
op_assign
id|driver-&gt;read_proc
suffix:semicolon
id|ent-&gt;write_proc
op_assign
id|driver-&gt;write_proc
suffix:semicolon
id|ent-&gt;owner
op_assign
id|driver-&gt;owner
suffix:semicolon
id|ent-&gt;data
op_assign
id|driver
suffix:semicolon
id|driver-&gt;proc_entry
op_assign
id|ent
suffix:semicolon
)brace
multiline_comment|/*&n; * This function is called by tty_unregister_driver()&n; */
DECL|function|proc_tty_unregister_driver
r_void
id|proc_tty_unregister_driver
c_func
(paren
r_struct
id|tty_driver
op_star
id|driver
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
id|ent
op_assign
id|driver-&gt;proc_entry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ent
)paren
r_return
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|driver-&gt;driver_name
comma
id|proc_tty_driver
)paren
suffix:semicolon
id|driver-&gt;proc_entry
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Called by proc_root_init() to initialize the /proc/tty subtree&n; */
DECL|function|proc_tty_init
r_void
id|__init
id|proc_tty_init
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
r_if
c_cond
(paren
op_logical_neg
id|proc_mkdir
c_func
(paren
l_string|&quot;tty&quot;
comma
l_int|NULL
)paren
)paren
r_return
suffix:semicolon
id|proc_tty_ldisc
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;tty/ldisc&quot;
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * /proc/tty/driver/serial reveals the exact character counts for&n;&t; * serial links which is just too easy to abuse for inferring&n;&t; * password lengths and inter-keystroke timings during password&n;&t; * entry.&n;&t; */
id|proc_tty_driver
op_assign
id|proc_mkdir_mode
c_func
(paren
l_string|&quot;tty/driver&quot;
comma
id|S_IRUSR
op_or
id|S_IXUSR
comma
l_int|NULL
)paren
suffix:semicolon
id|create_proc_read_entry
c_func
(paren
l_string|&quot;tty/ldiscs&quot;
comma
l_int|0
comma
l_int|NULL
comma
id|tty_ldiscs_read_proc
comma
l_int|NULL
)paren
suffix:semicolon
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;tty/drivers&quot;
comma
l_int|0
comma
l_int|NULL
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
id|proc_tty_drivers_operations
suffix:semicolon
)brace
eof
