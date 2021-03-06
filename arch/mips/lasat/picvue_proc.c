multiline_comment|/* &n; * Picvue PVC160206 display driver&n; *&n; * Brian Murphy &lt;brian.murphy@eicon.com&gt; &n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &quot;picvue.h&quot;
DECL|variable|pvc_lines
r_static
r_char
id|pvc_lines
(braket
id|PVC_NLINES
)braket
(braket
id|PVC_LINELEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|variable|pvc_linedata
r_static
r_int
id|pvc_linedata
(braket
id|PVC_NLINES
)braket
suffix:semicolon
DECL|variable|pvc_display_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|pvc_display_dir
suffix:semicolon
DECL|variable|pvc_linename
r_static
r_char
op_star
id|pvc_linename
(braket
id|PVC_NLINES
)braket
op_assign
(brace
l_string|&quot;line1&quot;
comma
l_string|&quot;line2&quot;
)brace
suffix:semicolon
DECL|macro|DISPLAY_DIR_NAME
mdefine_line|#define DISPLAY_DIR_NAME &quot;display&quot;
DECL|variable|scroll_dir
DECL|variable|scroll_interval
r_static
r_int
id|scroll_dir
op_assign
l_int|0
comma
id|scroll_interval
op_assign
l_int|0
suffix:semicolon
DECL|variable|timer
r_static
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|function|pvc_display
r_static
r_void
id|pvc_display
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_int
id|i
suffix:semicolon
id|pvc_clear
c_func
(paren
)paren
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
id|PVC_NLINES
suffix:semicolon
id|i
op_increment
)paren
id|pvc_write_string
c_func
(paren
id|pvc_lines
(braket
id|i
)braket
comma
l_int|0
comma
id|i
)paren
suffix:semicolon
)brace
DECL|variable|DECLARE_TASKLET
r_static
id|DECLARE_TASKLET
c_func
(paren
id|pvc_display_tasklet
comma
op_amp
id|pvc_display
comma
l_int|0
)paren
suffix:semicolon
DECL|function|pvc_proc_read_line
r_static
r_int
id|pvc_proc_read_line
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
r_char
op_star
id|origpage
op_assign
id|page
suffix:semicolon
r_int
id|lineno
op_assign
op_star
(paren
r_int
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|lineno
template_param
id|PVC_NLINES
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;proc_read_line: invalid lineno %d&bslash;n&quot;
comma
id|lineno
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|pvc_sem
)paren
suffix:semicolon
id|page
op_add_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|pvc_lines
(braket
id|lineno
)braket
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pvc_sem
)paren
suffix:semicolon
r_return
id|page
op_minus
id|origpage
suffix:semicolon
)brace
DECL|function|pvc_proc_write_line
r_static
r_int
id|pvc_proc_write_line
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|origcount
op_assign
id|count
suffix:semicolon
r_int
id|lineno
op_assign
op_star
(paren
r_int
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|lineno
template_param
id|PVC_NLINES
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;proc_write_line: invalid lineno %d&bslash;n&quot;
comma
id|lineno
)paren
suffix:semicolon
r_return
id|origcount
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
id|PVC_LINELEN
)paren
id|count
op_assign
id|PVC_LINELEN
suffix:semicolon
r_if
c_cond
(paren
id|buffer
(braket
id|count
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|count
op_decrement
suffix:semicolon
id|down
c_func
(paren
op_amp
id|pvc_sem
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|pvc_lines
(braket
id|lineno
)braket
comma
id|buffer
comma
id|count
)paren
suffix:semicolon
id|pvc_lines
(braket
id|lineno
)braket
(braket
id|count
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pvc_sem
)paren
suffix:semicolon
id|tasklet_schedule
c_func
(paren
op_amp
id|pvc_display_tasklet
)paren
suffix:semicolon
r_return
id|origcount
suffix:semicolon
)brace
DECL|function|pvc_proc_write_scroll
r_static
r_int
id|pvc_proc_write_scroll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|origcount
op_assign
id|count
suffix:semicolon
r_int
id|cmd
op_assign
id|simple_strtol
c_func
(paren
id|buffer
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|pvc_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scroll_interval
op_ne
l_int|0
)paren
id|del_timer
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
l_int|0
)paren
(brace
id|scroll_dir
op_assign
l_int|0
suffix:semicolon
id|scroll_interval
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|cmd
OL
l_int|0
)paren
(brace
id|scroll_dir
op_assign
op_minus
l_int|1
suffix:semicolon
id|scroll_interval
op_assign
op_minus
id|cmd
suffix:semicolon
)brace
r_else
(brace
id|scroll_dir
op_assign
l_int|1
suffix:semicolon
id|scroll_interval
op_assign
id|cmd
suffix:semicolon
)brace
id|add_timer
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|pvc_sem
)paren
suffix:semicolon
r_return
id|origcount
suffix:semicolon
)brace
DECL|function|pvc_proc_read_scroll
r_static
r_int
id|pvc_proc_read_scroll
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
r_char
op_star
id|origpage
op_assign
id|page
suffix:semicolon
id|down
c_func
(paren
op_amp
id|pvc_sem
)paren
suffix:semicolon
id|page
op_add_assign
id|sprintf
c_func
(paren
id|page
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|scroll_dir
op_star
id|scroll_interval
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pvc_sem
)paren
suffix:semicolon
r_return
id|page
op_minus
id|origpage
suffix:semicolon
)brace
DECL|function|pvc_proc_timerfunc
r_void
id|pvc_proc_timerfunc
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_if
c_cond
(paren
id|scroll_dir
OL
l_int|0
)paren
id|pvc_move
c_func
(paren
id|DISPLAY
op_or
id|RIGHT
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|scroll_dir
OG
l_int|0
)paren
id|pvc_move
c_func
(paren
id|DISPLAY
op_or
id|LEFT
)paren
suffix:semicolon
id|timer.expires
op_assign
id|jiffies
op_plus
id|scroll_interval
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
)brace
DECL|function|pvc_proc_cleanup
r_static
r_void
id|pvc_proc_cleanup
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|PVC_NLINES
suffix:semicolon
id|i
op_increment
)paren
id|remove_proc_entry
c_func
(paren
id|pvc_linename
(braket
id|i
)braket
comma
id|pvc_display_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;scroll&quot;
comma
id|pvc_display_dir
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|DISPLAY_DIR_NAME
comma
l_int|NULL
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
)brace
DECL|function|pvc_proc_init
r_static
r_int
id|__init
id|pvc_proc_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pvc_display_dir
op_assign
id|proc_mkdir
c_func
(paren
id|DISPLAY_DIR_NAME
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pvc_display_dir
op_eq
l_int|NULL
)paren
r_goto
id|error
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
id|PVC_NLINES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|strcpy
c_func
(paren
id|pvc_lines
(braket
id|i
)braket
comma
l_string|&quot;&quot;
)paren
suffix:semicolon
id|pvc_linedata
(braket
id|i
)braket
op_assign
id|i
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PVC_NLINES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|proc_entry
op_assign
id|create_proc_entry
c_func
(paren
id|pvc_linename
(braket
id|i
)braket
comma
l_int|0644
comma
id|pvc_display_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc_entry
op_eq
l_int|NULL
)paren
r_goto
id|error
suffix:semicolon
id|proc_entry-&gt;read_proc
op_assign
id|pvc_proc_read_line
suffix:semicolon
id|proc_entry-&gt;write_proc
op_assign
id|pvc_proc_write_line
suffix:semicolon
id|proc_entry-&gt;data
op_assign
op_amp
id|pvc_linedata
(braket
id|i
)braket
suffix:semicolon
)brace
id|proc_entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;scroll&quot;
comma
l_int|0644
comma
id|pvc_display_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc_entry
op_eq
l_int|NULL
)paren
r_goto
id|error
suffix:semicolon
id|proc_entry-&gt;write_proc
op_assign
id|pvc_proc_write_scroll
suffix:semicolon
id|proc_entry-&gt;read_proc
op_assign
id|pvc_proc_read_scroll
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|timer
)paren
suffix:semicolon
id|timer.function
op_assign
id|pvc_proc_timerfunc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|pvc_proc_cleanup
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|variable|pvc_proc_init
id|module_init
c_func
(paren
id|pvc_proc_init
)paren
suffix:semicolon
DECL|variable|pvc_proc_cleanup
id|module_exit
c_func
(paren
id|pvc_proc_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
