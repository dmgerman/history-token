multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;chan_kern.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;sigio.h&quot;
macro_line|#include &quot;line.h&quot;
macro_line|#include &quot;os.h&quot;
macro_line|#ifdef CONFIG_NOCONFIG_CHAN
DECL|function|not_configged_init
r_static
r_void
op_star
id|not_configged_init
c_func
(paren
r_char
op_star
id|str
comma
r_int
id|device
comma
r_struct
id|chan_opts
op_star
id|opts
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Using a channel type which is configured out of &quot;
l_string|&quot;UML&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|not_configged_open
r_static
r_int
id|not_configged_open
c_func
(paren
r_int
id|input
comma
r_int
id|output
comma
r_int
id|primary
comma
r_void
op_star
id|data
comma
r_char
op_star
op_star
id|dev_out
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Using a channel type which is configured out of &quot;
l_string|&quot;UML&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|not_configged_close
r_static
r_void
id|not_configged_close
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|data
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Using a channel type which is configured out of &quot;
l_string|&quot;UML&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|not_configged_read
r_static
r_int
id|not_configged_read
c_func
(paren
r_int
id|fd
comma
r_char
op_star
id|c_out
comma
r_void
op_star
id|data
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Using a channel type which is configured out of &quot;
l_string|&quot;UML&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|not_configged_write
r_static
r_int
id|not_configged_write
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_void
op_star
id|data
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Using a channel type which is configured out of &quot;
l_string|&quot;UML&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|not_configged_console_write
r_static
r_int
id|not_configged_console_write
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_void
op_star
id|data
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Using a channel type which is configured out of &quot;
l_string|&quot;UML&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|not_configged_window_size
r_static
r_int
id|not_configged_window_size
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|data
comma
r_int
r_int
op_star
id|rows
comma
r_int
r_int
op_star
id|cols
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Using a channel type which is configured out of &quot;
l_string|&quot;UML&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|not_configged_free
r_static
r_void
id|not_configged_free
c_func
(paren
r_void
op_star
id|data
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Using a channel type which is configured out of &quot;
l_string|&quot;UML&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|not_configged_ops
r_static
r_struct
id|chan_ops
id|not_configged_ops
op_assign
(brace
dot
id|init
op_assign
id|not_configged_init
comma
dot
id|open
op_assign
id|not_configged_open
comma
dot
id|close
op_assign
id|not_configged_close
comma
dot
id|read
op_assign
id|not_configged_read
comma
dot
id|write
op_assign
id|not_configged_write
comma
dot
id|console_write
op_assign
id|not_configged_console_write
comma
dot
id|window_size
op_assign
id|not_configged_window_size
comma
dot
id|free
op_assign
id|not_configged_free
comma
dot
id|winch
op_assign
l_int|0
comma
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_NOCONFIG_CHAN */
DECL|function|generic_close
r_void
id|generic_close
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|unused
)paren
(brace
id|os_close_file
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
DECL|function|generic_read
r_int
id|generic_read
c_func
(paren
r_int
id|fd
comma
r_char
op_star
id|c_out
comma
r_void
op_star
id|unused
)paren
(brace
r_int
id|n
suffix:semicolon
id|n
op_assign
id|os_read_file
c_func
(paren
id|fd
comma
id|c_out
comma
r_sizeof
(paren
op_star
id|c_out
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
op_minus
id|EAGAIN
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
multiline_comment|/* XXX Trivial wrapper around os_write_file */
DECL|function|generic_write
r_int
id|generic_write
c_func
(paren
r_int
id|fd
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|n
comma
r_void
op_star
id|unused
)paren
(brace
r_return
id|os_write_file
c_func
(paren
id|fd
comma
id|buf
comma
id|n
)paren
suffix:semicolon
)brace
DECL|function|generic_window_size
r_int
id|generic_window_size
c_func
(paren
r_int
id|fd
comma
r_void
op_star
id|unused
comma
r_int
r_int
op_star
id|rows_out
comma
r_int
r_int
op_star
id|cols_out
)paren
(brace
r_int
id|rows
comma
id|cols
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|os_window_size
c_func
(paren
id|fd
comma
op_amp
id|rows
comma
op_amp
id|cols
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
(paren
(paren
op_star
id|rows_out
op_ne
id|rows
)paren
op_logical_or
(paren
op_star
id|cols_out
op_ne
id|cols
)paren
)paren
suffix:semicolon
op_star
id|rows_out
op_assign
id|rows
suffix:semicolon
op_star
id|cols_out
op_assign
id|cols
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|generic_free
r_void
id|generic_free
c_func
(paren
r_void
op_star
id|data
)paren
(brace
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
DECL|function|tty_receive_char
r_static
r_void
id|tty_receive_char
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_char
id|ch
)paren
(brace
r_if
c_cond
(paren
id|tty
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|I_IXON
c_func
(paren
id|tty
)paren
op_logical_and
op_logical_neg
id|I_IXOFF
c_func
(paren
id|tty
)paren
op_logical_and
op_logical_neg
id|tty-&gt;raw
)paren
(brace
r_if
c_cond
(paren
id|ch
op_eq
id|STOP_CHAR
c_func
(paren
id|tty
)paren
)paren
(brace
id|stop_tty
c_func
(paren
id|tty
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ch
op_eq
id|START_CHAR
c_func
(paren
id|tty
)paren
)paren
(brace
id|start_tty
c_func
(paren
id|tty
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|tty-&gt;flip.flag_buf_ptr
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|tty-&gt;flip.char_buf_ptr
op_eq
l_int|NULL
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|tty_insert_flip_char
c_func
(paren
id|tty
comma
id|ch
comma
id|TTY_NORMAL
)paren
suffix:semicolon
)brace
DECL|function|open_one_chan
r_static
r_int
id|open_one_chan
c_func
(paren
r_struct
id|chan
op_star
id|chan
comma
r_int
id|input
comma
r_int
id|output
comma
r_int
id|primary
)paren
(brace
r_int
id|fd
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;opened
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chan-&gt;ops-&gt;open
op_eq
l_int|NULL
)paren
(brace
id|fd
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|fd
op_assign
(paren
op_star
id|chan-&gt;ops-&gt;open
)paren
(paren
id|input
comma
id|output
comma
id|primary
comma
id|chan-&gt;data
comma
op_amp
id|chan-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
r_return
id|fd
suffix:semicolon
)brace
id|chan-&gt;fd
op_assign
id|fd
suffix:semicolon
id|chan-&gt;opened
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|open_chan
r_int
id|open_chan
c_func
(paren
r_struct
id|list_head
op_star
id|chans
)paren
(brace
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
r_struct
id|chan
op_star
id|chan
suffix:semicolon
r_int
id|ret
comma
id|err
op_assign
l_int|0
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
id|chans
)paren
(brace
id|chan
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|chan
comma
id|list
)paren
suffix:semicolon
id|ret
op_assign
id|open_one_chan
c_func
(paren
id|chan
comma
id|chan-&gt;input
comma
id|chan-&gt;output
comma
id|chan-&gt;primary
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;primary
)paren
(brace
id|err
op_assign
id|ret
suffix:semicolon
)brace
)brace
)def_block
r_return
id|err
suffix:semicolon
)brace
DECL|function|chan_enable_winch
r_void
id|chan_enable_winch
c_func
(paren
r_struct
id|list_head
op_star
id|chans
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
r_struct
id|chan
op_star
id|chan
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
id|chans
)paren
(brace
id|chan
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|chan
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;primary
op_logical_and
id|chan-&gt;output
op_logical_and
id|chan-&gt;ops-&gt;winch
)paren
(brace
id|register_winch
c_func
(paren
id|chan-&gt;fd
comma
id|tty
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)def_block
)brace
DECL|function|enable_chan
r_void
id|enable_chan
c_func
(paren
r_struct
id|list_head
op_star
id|chans
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
r_struct
id|chan
op_star
id|chan
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
id|chans
)paren
(brace
id|chan
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|chan
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chan-&gt;opened
)paren
(brace
r_continue
suffix:semicolon
)brace
id|line_setup_irq
c_func
(paren
id|chan-&gt;fd
comma
id|chan-&gt;input
comma
id|chan-&gt;output
comma
id|tty
)paren
suffix:semicolon
)brace
)def_block
)brace
DECL|function|close_chan
r_void
id|close_chan
c_func
(paren
r_struct
id|list_head
op_star
id|chans
)paren
(brace
r_struct
id|chan
op_star
id|chan
suffix:semicolon
multiline_comment|/* Close in reverse order as open in case more than one of them&n;&t; * refers to the same device and they save and restore that device&squot;s&n;&t; * state.  Then, the first one opened will have the original state,&n;&t; * so it must be the last closed.&n;&t; */
id|list_for_each_entry_reverse
c_func
(paren
id|chan
comma
id|chans
comma
id|list
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|chan-&gt;opened
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chan-&gt;ops-&gt;close
op_ne
l_int|NULL
)paren
(brace
(paren
op_star
id|chan-&gt;ops-&gt;close
)paren
(paren
id|chan-&gt;fd
comma
id|chan-&gt;data
)paren
suffix:semicolon
)brace
id|chan-&gt;opened
op_assign
l_int|0
suffix:semicolon
id|chan-&gt;fd
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|write_chan
r_int
id|write_chan
c_func
(paren
r_struct
id|list_head
op_star
id|chans
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|write_irq
)paren
(brace
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
r_struct
id|chan
op_star
id|chan
op_assign
l_int|NULL
suffix:semicolon
r_int
id|n
comma
id|ret
op_assign
l_int|0
suffix:semicolon
id|list_for_each
c_func
(paren
id|ele
comma
id|chans
)paren
(brace
id|chan
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|chan
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chan-&gt;output
op_logical_or
(paren
id|chan-&gt;ops-&gt;write
op_eq
l_int|NULL
)paren
)paren
r_continue
suffix:semicolon
id|n
op_assign
id|chan-&gt;ops
op_member_access_from_pointer
id|write
c_func
(paren
id|chan-&gt;fd
comma
id|buf
comma
id|len
comma
id|chan-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;primary
)paren
(brace
id|ret
op_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_eq
op_minus
id|EAGAIN
)paren
op_logical_or
(paren
(paren
id|ret
op_ge
l_int|0
)paren
op_logical_and
(paren
id|ret
OL
id|len
)paren
)paren
)paren
id|reactivate_fd
c_func
(paren
id|chan-&gt;fd
comma
id|write_irq
)paren
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|console_write_chan
r_int
id|console_write_chan
c_func
(paren
r_struct
id|list_head
op_star
id|chans
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
r_struct
id|chan
op_star
id|chan
suffix:semicolon
r_int
id|n
comma
id|ret
op_assign
l_int|0
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
id|chans
)paren
(brace
id|chan
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|chan
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chan-&gt;output
op_logical_or
(paren
id|chan-&gt;ops-&gt;console_write
op_eq
l_int|NULL
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
id|n
op_assign
id|chan-&gt;ops
op_member_access_from_pointer
id|console_write
c_func
(paren
id|chan-&gt;fd
comma
id|buf
comma
id|len
comma
id|chan-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;primary
)paren
(brace
id|ret
op_assign
id|n
suffix:semicolon
)brace
)brace
)def_block
r_return
id|ret
suffix:semicolon
)brace
DECL|function|console_open_chan
r_int
id|console_open_chan
c_func
(paren
r_struct
id|line
op_star
id|line
comma
r_struct
id|console
op_star
id|co
comma
r_struct
id|chan_opts
op_star
id|opts
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|line-&gt;chan_list
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|parse_chan_pair
c_func
(paren
id|line-&gt;init_str
comma
op_amp
id|line-&gt;chan_list
comma
id|line-&gt;init_pri
comma
id|co-&gt;index
comma
id|opts
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|open_chan
c_func
(paren
op_amp
id|line-&gt;chan_list
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Console initialized on /dev/%s%d&bslash;n&quot;
comma
id|co-&gt;name
comma
id|co-&gt;index
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|chan_window_size
r_int
id|chan_window_size
c_func
(paren
r_struct
id|list_head
op_star
id|chans
comma
r_int
r_int
op_star
id|rows_out
comma
r_int
r_int
op_star
id|cols_out
)paren
(brace
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
r_struct
id|chan
op_star
id|chan
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
id|chans
)paren
(brace
id|chan
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|chan
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;primary
)paren
(brace
r_if
c_cond
(paren
id|chan-&gt;ops-&gt;window_size
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|chan-&gt;ops
op_member_access_from_pointer
id|window_size
c_func
(paren
id|chan-&gt;fd
comma
id|chan-&gt;data
comma
id|rows_out
comma
id|cols_out
)paren
suffix:semicolon
)brace
)brace
)def_block
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|free_one_chan
r_void
id|free_one_chan
c_func
(paren
r_struct
id|chan
op_star
id|chan
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|chan-&gt;list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;ops-&gt;free
op_ne
l_int|NULL
)paren
(brace
(paren
op_star
id|chan-&gt;ops-&gt;free
)paren
(paren
id|chan-&gt;data
)paren
suffix:semicolon
)brace
id|free_irq_by_fd
c_func
(paren
id|chan-&gt;fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;primary
op_logical_and
id|chan-&gt;output
)paren
(brace
id|ignore_sigio_fd
c_func
(paren
id|chan-&gt;fd
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|chan
)paren
suffix:semicolon
)brace
DECL|function|free_chan
r_void
id|free_chan
c_func
(paren
r_struct
id|list_head
op_star
id|chans
)paren
(brace
r_struct
id|list_head
op_star
id|ele
comma
op_star
id|next
suffix:semicolon
r_struct
id|chan
op_star
id|chan
suffix:semicolon
(def_block
id|list_for_each_safe
c_func
(paren
id|ele
comma
id|next
comma
id|chans
)paren
(brace
id|chan
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|chan
comma
id|list
)paren
suffix:semicolon
id|free_one_chan
c_func
(paren
id|chan
)paren
suffix:semicolon
)brace
)def_block
)brace
DECL|function|one_chan_config_string
r_static
r_int
id|one_chan_config_string
c_func
(paren
r_struct
id|chan
op_star
id|chan
comma
r_char
op_star
id|str
comma
r_int
id|size
comma
r_char
op_star
op_star
id|error_out
)paren
(brace
r_int
id|n
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|chan
op_eq
l_int|NULL
)paren
(brace
id|CONFIG_CHUNK
c_func
(paren
id|str
comma
id|size
comma
id|n
comma
l_string|&quot;none&quot;
comma
l_int|1
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
id|CONFIG_CHUNK
c_func
(paren
id|str
comma
id|size
comma
id|n
comma
id|chan-&gt;ops-&gt;type
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;dev
op_eq
l_int|NULL
)paren
(brace
id|CONFIG_CHUNK
c_func
(paren
id|str
comma
id|size
comma
id|n
comma
l_string|&quot;&quot;
comma
l_int|1
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
id|CONFIG_CHUNK
c_func
(paren
id|str
comma
id|size
comma
id|n
comma
l_string|&quot;:&quot;
comma
l_int|0
)paren
suffix:semicolon
id|CONFIG_CHUNK
c_func
(paren
id|str
comma
id|size
comma
id|n
comma
id|chan-&gt;dev
comma
l_int|0
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|function|chan_pair_config_string
r_static
r_int
id|chan_pair_config_string
c_func
(paren
r_struct
id|chan
op_star
id|in
comma
r_struct
id|chan
op_star
id|out
comma
r_char
op_star
id|str
comma
r_int
id|size
comma
r_char
op_star
op_star
id|error_out
)paren
(brace
r_int
id|n
suffix:semicolon
id|n
op_assign
id|one_chan_config_string
c_func
(paren
id|in
comma
id|str
comma
id|size
comma
id|error_out
)paren
suffix:semicolon
id|str
op_add_assign
id|n
suffix:semicolon
id|size
op_sub_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
id|in
op_eq
id|out
)paren
(brace
id|CONFIG_CHUNK
c_func
(paren
id|str
comma
id|size
comma
id|n
comma
l_string|&quot;&quot;
comma
l_int|1
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
id|CONFIG_CHUNK
c_func
(paren
id|str
comma
id|size
comma
id|n
comma
l_string|&quot;,&quot;
comma
l_int|1
)paren
suffix:semicolon
id|n
op_assign
id|one_chan_config_string
c_func
(paren
id|out
comma
id|str
comma
id|size
comma
id|error_out
)paren
suffix:semicolon
id|str
op_add_assign
id|n
suffix:semicolon
id|size
op_sub_assign
id|n
suffix:semicolon
id|CONFIG_CHUNK
c_func
(paren
id|str
comma
id|size
comma
id|n
comma
l_string|&quot;&quot;
comma
l_int|1
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|function|chan_config_string
r_int
id|chan_config_string
c_func
(paren
r_struct
id|list_head
op_star
id|chans
comma
r_char
op_star
id|str
comma
r_int
id|size
comma
r_char
op_star
op_star
id|error_out
)paren
(brace
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
r_struct
id|chan
op_star
id|chan
comma
op_star
id|in
op_assign
l_int|NULL
comma
op_star
id|out
op_assign
l_int|NULL
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
id|chans
)paren
(brace
id|chan
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|chan
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chan-&gt;primary
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chan-&gt;input
)paren
(brace
id|in
op_assign
id|chan
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chan-&gt;output
)paren
(brace
id|out
op_assign
id|chan
suffix:semicolon
)brace
)brace
)def_block
r_return
id|chan_pair_config_string
c_func
(paren
id|in
comma
id|out
comma
id|str
comma
id|size
comma
id|error_out
)paren
suffix:semicolon
)brace
DECL|struct|chan_type
r_struct
id|chan_type
(brace
DECL|member|key
r_char
op_star
id|key
suffix:semicolon
DECL|member|ops
r_struct
id|chan_ops
op_star
id|ops
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|chan_table
r_struct
id|chan_type
id|chan_table
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;fd&quot;
comma
op_amp
id|fd_ops
)brace
comma
macro_line|#ifdef CONFIG_NULL_CHAN
(brace
l_string|&quot;null&quot;
comma
op_amp
id|null_ops
)brace
comma
macro_line|#else
(brace
l_string|&quot;null&quot;
comma
op_amp
id|not_configged_ops
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_PORT_CHAN
(brace
l_string|&quot;port&quot;
comma
op_amp
id|port_ops
)brace
comma
macro_line|#else
(brace
l_string|&quot;port&quot;
comma
op_amp
id|not_configged_ops
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_PTY_CHAN
(brace
l_string|&quot;pty&quot;
comma
op_amp
id|pty_ops
)brace
comma
(brace
l_string|&quot;pts&quot;
comma
op_amp
id|pts_ops
)brace
comma
macro_line|#else
(brace
l_string|&quot;pty&quot;
comma
op_amp
id|not_configged_ops
)brace
comma
(brace
l_string|&quot;pts&quot;
comma
op_amp
id|not_configged_ops
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_TTY_CHAN
(brace
l_string|&quot;tty&quot;
comma
op_amp
id|tty_ops
)brace
comma
macro_line|#else
(brace
l_string|&quot;tty&quot;
comma
op_amp
id|not_configged_ops
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_XTERM_CHAN
(brace
l_string|&quot;xterm&quot;
comma
op_amp
id|xterm_ops
)brace
comma
macro_line|#else
(brace
l_string|&quot;xterm&quot;
comma
op_amp
id|not_configged_ops
)brace
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|parse_chan
r_static
r_struct
id|chan
op_star
id|parse_chan
c_func
(paren
r_char
op_star
id|str
comma
r_int
id|pri
comma
r_int
id|device
comma
r_struct
id|chan_opts
op_star
id|opts
)paren
(brace
r_struct
id|chan_type
op_star
id|entry
suffix:semicolon
r_struct
id|chan_ops
op_star
id|ops
suffix:semicolon
r_struct
id|chan
op_star
id|chan
suffix:semicolon
r_void
op_star
id|data
suffix:semicolon
r_int
id|i
suffix:semicolon
id|ops
op_assign
l_int|NULL
suffix:semicolon
id|data
op_assign
l_int|NULL
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
r_sizeof
(paren
id|chan_table
)paren
op_div
r_sizeof
(paren
id|chan_table
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|entry
op_assign
op_amp
id|chan_table
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
id|entry-&gt;key
comma
id|strlen
c_func
(paren
id|entry-&gt;key
)paren
)paren
)paren
(brace
id|ops
op_assign
id|entry-&gt;ops
suffix:semicolon
id|str
op_add_assign
id|strlen
c_func
(paren
id|entry-&gt;key
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|ops
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;parse_chan couldn&squot;t parse &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ops-&gt;init
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|data
op_assign
(paren
op_star
id|ops-&gt;init
)paren
(paren
id|str
comma
id|device
comma
id|opts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|chan
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|chan
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chan
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|chan
op_assign
(paren
(paren
r_struct
id|chan
)paren
(brace
dot
id|list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|chan-&gt;list
)paren
comma
dot
id|primary
op_assign
l_int|1
comma
dot
id|input
op_assign
l_int|0
comma
dot
id|output
op_assign
l_int|0
comma
dot
id|opened
op_assign
l_int|0
comma
dot
id|fd
op_assign
op_minus
l_int|1
comma
dot
id|pri
op_assign
id|pri
comma
dot
id|ops
op_assign
id|ops
comma
dot
id|data
op_assign
id|data
)brace
)paren
suffix:semicolon
r_return
id|chan
suffix:semicolon
)brace
DECL|function|parse_chan_pair
r_int
id|parse_chan_pair
c_func
(paren
r_char
op_star
id|str
comma
r_struct
id|list_head
op_star
id|chans
comma
r_int
id|pri
comma
r_int
id|device
comma
r_struct
id|chan_opts
op_star
id|opts
)paren
(brace
r_struct
id|chan
op_star
r_new
comma
op_star
id|chan
suffix:semicolon
r_char
op_star
id|in
comma
op_star
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|chans
)paren
)paren
(brace
id|chan
op_assign
id|list_entry
c_func
(paren
id|chans-&gt;next
comma
r_struct
id|chan
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;pri
op_ge
id|pri
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|free_chan
c_func
(paren
id|chans
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
id|chans
)paren
suffix:semicolon
)brace
id|out
op_assign
id|strchr
c_func
(paren
id|str
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out
op_ne
l_int|NULL
)paren
(brace
id|in
op_assign
id|str
suffix:semicolon
op_star
id|out
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|out
op_increment
suffix:semicolon
r_new
op_assign
id|parse_chan
c_func
(paren
id|in
comma
id|pri
comma
id|device
comma
id|opts
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_new
op_member_access_from_pointer
id|input
op_assign
l_int|1
suffix:semicolon
id|list_add
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|list
comma
id|chans
)paren
suffix:semicolon
r_new
op_assign
id|parse_chan
c_func
(paren
id|out
comma
id|pri
comma
id|device
comma
id|opts
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|list
comma
id|chans
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|output
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_new
op_assign
id|parse_chan
c_func
(paren
id|str
comma
id|pri
comma
id|device
comma
id|opts
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|list_add
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|list
comma
id|chans
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|input
op_assign
l_int|1
suffix:semicolon
r_new
op_member_access_from_pointer
id|output
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|chan_out_fd
r_int
id|chan_out_fd
c_func
(paren
r_struct
id|list_head
op_star
id|chans
)paren
(brace
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
r_struct
id|chan
op_star
id|chan
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
id|chans
)paren
(brace
id|chan
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|chan
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;primary
op_logical_and
id|chan-&gt;output
)paren
(brace
r_return
id|chan-&gt;fd
suffix:semicolon
)brace
)brace
)def_block
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|chan_interrupt
r_void
id|chan_interrupt
c_func
(paren
r_struct
id|list_head
op_star
id|chans
comma
r_struct
id|work_struct
op_star
id|task
comma
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|irq
)paren
(brace
r_struct
id|list_head
op_star
id|ele
comma
op_star
id|next
suffix:semicolon
r_struct
id|chan
op_star
id|chan
suffix:semicolon
r_int
id|err
suffix:semicolon
r_char
id|c
suffix:semicolon
(def_block
id|list_for_each_safe
c_func
(paren
id|ele
comma
id|next
comma
id|chans
)paren
(brace
id|chan
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|chan
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chan-&gt;input
op_logical_or
(paren
id|chan-&gt;ops-&gt;read
op_eq
l_int|NULL
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
r_do
(brace
r_if
c_cond
(paren
(paren
id|tty
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|tty-&gt;flip.count
op_ge
id|TTY_FLIPBUF_SIZE
)paren
)paren
(brace
id|schedule_work
c_func
(paren
id|task
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|chan-&gt;ops
op_member_access_from_pointer
id|read
c_func
(paren
id|chan-&gt;fd
comma
op_amp
id|c
comma
id|chan-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OG
l_int|0
)paren
(brace
id|tty_receive_char
c_func
(paren
id|tty
comma
id|c
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|err
OG
l_int|0
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
(brace
id|reactivate_fd
c_func
(paren
id|chan-&gt;fd
comma
id|irq
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|EIO
)paren
(brace
r_if
c_cond
(paren
id|chan-&gt;primary
)paren
(brace
r_if
c_cond
(paren
id|tty
op_ne
l_int|NULL
)paren
(brace
id|tty_hangup
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
id|line_disable
c_func
(paren
id|tty
comma
id|irq
)paren
suffix:semicolon
id|close_chan
c_func
(paren
id|chans
)paren
suffix:semicolon
id|free_chan
c_func
(paren
id|chans
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|chan-&gt;ops-&gt;close
op_ne
l_int|NULL
)paren
(brace
id|chan-&gt;ops
op_member_access_from_pointer
id|close
c_func
(paren
id|chan-&gt;fd
comma
id|chan-&gt;data
)paren
suffix:semicolon
)brace
id|free_one_chan
c_func
(paren
id|chan
)paren
suffix:semicolon
)brace
)brace
)brace
)def_block
id|out
suffix:colon
r_if
c_cond
(paren
id|tty
)paren
(brace
id|tty_flip_buffer_push
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
