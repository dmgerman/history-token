multiline_comment|/* &n; * Copyright (C) 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;linux/list.h&quot;
macro_line|#include &quot;linux/interrupt.h&quot;
macro_line|#include &quot;linux/devfs_fs_kernel.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;chan_kern.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;line.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;irq_kern.h&quot;
DECL|macro|LINE_BUFSIZE
mdefine_line|#define LINE_BUFSIZE 4096
DECL|function|line_interrupt
r_static
id|irqreturn_t
id|line_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|data
comma
r_struct
id|pt_regs
op_star
id|unused
)paren
(brace
r_struct
id|line
op_star
id|dev
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;count
OG
l_int|0
)paren
(brace
id|chan_interrupt
c_func
(paren
op_amp
id|dev-&gt;chan_list
comma
op_amp
id|dev-&gt;task
comma
id|dev-&gt;tty
comma
id|irq
comma
id|dev
)paren
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|line_timer_cb
r_static
r_void
id|line_timer_cb
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|line
op_star
id|dev
op_assign
id|arg
suffix:semicolon
id|line_interrupt
c_func
(paren
id|dev-&gt;driver-&gt;read_irq
comma
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|write_room
r_static
r_int
id|write_room
c_func
(paren
r_struct
id|line
op_star
id|dev
)paren
(brace
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;buffer
op_eq
l_int|NULL
)paren
(brace
r_return
id|LINE_BUFSIZE
op_minus
l_int|1
suffix:semicolon
)brace
id|n
op_assign
id|dev-&gt;head
op_minus
id|dev-&gt;tail
suffix:semicolon
r_if
c_cond
(paren
id|n
op_le
l_int|0
)paren
(brace
id|n
op_assign
id|LINE_BUFSIZE
op_plus
id|n
suffix:semicolon
)brace
r_return
id|n
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|buffer_data
r_static
r_int
id|buffer_data
c_func
(paren
r_struct
id|line
op_star
id|line
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
r_int
id|end
comma
id|room
suffix:semicolon
r_if
c_cond
(paren
id|line-&gt;buffer
op_eq
l_int|NULL
)paren
(brace
id|line-&gt;buffer
op_assign
id|kmalloc
c_func
(paren
id|LINE_BUFSIZE
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line-&gt;buffer
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;buffer_data - atomic allocation failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|line-&gt;head
op_assign
id|line-&gt;buffer
suffix:semicolon
id|line-&gt;tail
op_assign
id|line-&gt;buffer
suffix:semicolon
)brace
id|room
op_assign
id|write_room
c_func
(paren
id|line
)paren
suffix:semicolon
id|len
op_assign
(paren
id|len
OG
id|room
)paren
ques
c_cond
id|room
suffix:colon
id|len
suffix:semicolon
id|end
op_assign
id|line-&gt;buffer
op_plus
id|LINE_BUFSIZE
op_minus
id|line-&gt;tail
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
id|end
)paren
(brace
id|memcpy
c_func
(paren
id|line-&gt;tail
comma
id|buf
comma
id|len
)paren
suffix:semicolon
id|line-&gt;tail
op_add_assign
id|len
suffix:semicolon
)brace
r_else
(brace
id|memcpy
c_func
(paren
id|line-&gt;tail
comma
id|buf
comma
id|end
)paren
suffix:semicolon
id|buf
op_add_assign
id|end
suffix:semicolon
id|memcpy
c_func
(paren
id|line-&gt;buffer
comma
id|buf
comma
id|len
op_minus
id|end
)paren
suffix:semicolon
id|line-&gt;tail
op_assign
id|line-&gt;buffer
op_plus
id|len
op_minus
id|end
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|function|flush_buffer
r_static
r_int
id|flush_buffer
c_func
(paren
r_struct
id|line
op_star
id|line
)paren
(brace
r_int
id|n
comma
id|count
suffix:semicolon
r_if
c_cond
(paren
(paren
id|line-&gt;buffer
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|line-&gt;head
op_eq
id|line-&gt;tail
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|line-&gt;tail
OL
id|line-&gt;head
)paren
(brace
id|count
op_assign
id|line-&gt;buffer
op_plus
id|LINE_BUFSIZE
op_minus
id|line-&gt;head
suffix:semicolon
id|n
op_assign
id|write_chan
c_func
(paren
op_amp
id|line-&gt;chan_list
comma
id|line-&gt;head
comma
id|count
comma
id|line-&gt;driver-&gt;write_irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
r_return
id|n
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_eq
id|count
)paren
(brace
id|line-&gt;head
op_assign
id|line-&gt;buffer
suffix:semicolon
)brace
r_else
(brace
id|line-&gt;head
op_add_assign
id|n
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|count
op_assign
id|line-&gt;tail
op_minus
id|line-&gt;head
suffix:semicolon
id|n
op_assign
id|write_chan
c_func
(paren
op_amp
id|line-&gt;chan_list
comma
id|line-&gt;head
comma
id|count
comma
id|line-&gt;driver-&gt;write_irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
r_return
id|n
suffix:semicolon
)brace
id|line-&gt;head
op_add_assign
id|n
suffix:semicolon
r_return
id|line-&gt;head
op_eq
id|line-&gt;tail
suffix:semicolon
)brace
DECL|function|line_write
r_int
id|line_write
c_func
(paren
r_struct
id|line
op_star
id|lines
comma
r_struct
id|tty_struct
op_star
id|tty
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
id|line
op_star
id|line
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|n
comma
id|err
comma
id|i
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;stopped
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|i
op_assign
id|tty-&gt;index
suffix:semicolon
id|line
op_assign
op_amp
id|lines
(braket
id|i
)braket
suffix:semicolon
id|down
c_func
(paren
op_amp
id|line-&gt;sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line-&gt;head
op_ne
id|line-&gt;tail
)paren
(brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ret
op_add_assign
id|buffer_data
c_func
(paren
id|line
comma
id|buf
comma
id|len
)paren
suffix:semicolon
id|err
op_assign
id|flush_buffer
c_func
(paren
id|line
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_le
l_int|0
)paren
(brace
r_goto
id|out_up
suffix:semicolon
)brace
)brace
r_else
(brace
id|n
op_assign
id|write_chan
c_func
(paren
op_amp
id|line-&gt;chan_list
comma
id|buf
comma
id|len
comma
id|line-&gt;driver-&gt;write_irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
id|ret
op_assign
id|n
suffix:semicolon
r_goto
id|out_up
suffix:semicolon
)brace
id|len
op_sub_assign
id|n
suffix:semicolon
id|ret
op_add_assign
id|n
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|0
)paren
(brace
id|ret
op_add_assign
id|buffer_data
c_func
(paren
id|line
comma
id|buf
op_plus
id|n
comma
id|len
)paren
suffix:semicolon
)brace
)brace
id|out_up
suffix:colon
id|up
c_func
(paren
op_amp
id|line-&gt;sem
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|line_write_interrupt
r_static
id|irqreturn_t
id|line_write_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|data
comma
r_struct
id|pt_regs
op_star
id|unused
)paren
(brace
r_struct
id|line
op_star
id|dev
op_assign
id|data
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
op_assign
id|dev-&gt;tty
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|flush_buffer
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
(brace
r_return
id|IRQ_NONE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|dev-&gt;head
op_assign
id|dev-&gt;buffer
suffix:semicolon
id|dev-&gt;tail
op_assign
id|dev-&gt;buffer
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tty
op_eq
l_int|NULL
)paren
(brace
r_return
id|IRQ_NONE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|TTY_DO_WRITE_WAKEUP
comma
op_amp
id|tty-&gt;flags
)paren
op_logical_and
(paren
id|tty-&gt;ldisc.write_wakeup
op_ne
l_int|NULL
)paren
)paren
(brace
(paren
id|tty-&gt;ldisc.write_wakeup
)paren
(paren
id|tty
)paren
suffix:semicolon
)brace
multiline_comment|/* BLOCKING mode&n;&t; * In blocking mode, everything sleeps on tty-&gt;write_wait.&n;&t; * Sleeping in the console driver would break non-blocking&n;&t; * writes.&n;&t; */
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|tty-&gt;write_wait
)paren
)paren
(brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|tty-&gt;write_wait
)paren
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|line_setup_irq
r_int
id|line_setup_irq
c_func
(paren
r_int
id|fd
comma
r_int
id|input
comma
r_int
id|output
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|line
op_star
id|line
op_assign
id|data
suffix:semicolon
r_struct
id|line_driver
op_star
id|driver
op_assign
id|line-&gt;driver
suffix:semicolon
r_int
id|err
op_assign
l_int|0
comma
id|flags
op_assign
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
op_or
id|SA_SAMPLE_RANDOM
suffix:semicolon
r_if
c_cond
(paren
id|input
)paren
(brace
id|err
op_assign
id|um_request_irq
c_func
(paren
id|driver-&gt;read_irq
comma
id|fd
comma
id|IRQ_READ
comma
id|line_interrupt
comma
id|flags
comma
id|driver-&gt;read_irq_name
comma
id|line
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|output
)paren
(brace
id|err
op_assign
id|um_request_irq
c_func
(paren
id|driver-&gt;write_irq
comma
id|fd
comma
id|IRQ_WRITE
comma
id|line_write_interrupt
comma
id|flags
comma
id|driver-&gt;write_irq_name
comma
id|line
)paren
suffix:semicolon
)brace
id|line-&gt;have_irq
op_assign
l_int|1
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|line_disable
r_void
id|line_disable
c_func
(paren
r_struct
id|line
op_star
id|line
comma
r_int
id|current_irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|line-&gt;have_irq
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|line-&gt;driver-&gt;read_irq
op_eq
id|current_irq
)paren
(brace
id|free_irq_later
c_func
(paren
id|line-&gt;driver-&gt;read_irq
comma
id|line
)paren
suffix:semicolon
)brace
r_else
(brace
id|free_irq_by_irq_and_dev
c_func
(paren
id|line-&gt;driver-&gt;read_irq
comma
id|line
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|line-&gt;driver-&gt;read_irq
comma
id|line
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|line-&gt;driver-&gt;write_irq
op_eq
id|current_irq
)paren
(brace
id|free_irq_later
c_func
(paren
id|line-&gt;driver-&gt;write_irq
comma
id|line
)paren
suffix:semicolon
)brace
r_else
(brace
id|free_irq_by_irq_and_dev
c_func
(paren
id|line-&gt;driver-&gt;write_irq
comma
id|line
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|line-&gt;driver-&gt;write_irq
comma
id|line
)paren
suffix:semicolon
)brace
id|line-&gt;have_irq
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|line_open
r_int
id|line_open
c_func
(paren
r_struct
id|line
op_star
id|lines
comma
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|chan_opts
op_star
id|opts
)paren
(brace
r_struct
id|line
op_star
id|line
suffix:semicolon
r_int
id|n
comma
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tty
op_eq
l_int|NULL
)paren
(brace
id|n
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|n
op_assign
id|tty-&gt;index
suffix:semicolon
id|line
op_assign
op_amp
id|lines
(braket
id|n
)braket
suffix:semicolon
id|down
c_func
(paren
op_amp
id|line-&gt;sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line-&gt;count
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|line-&gt;valid
)paren
(brace
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|line-&gt;chan_list
)paren
)paren
(brace
id|err
op_assign
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
id|n
comma
id|opts
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|open_chan
c_func
(paren
op_amp
id|line-&gt;chan_list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
)brace
id|enable_chan
c_func
(paren
op_amp
id|line-&gt;chan_list
comma
id|line
)paren
suffix:semicolon
id|INIT_WORK
c_func
(paren
op_amp
id|line-&gt;task
comma
id|line_timer_cb
comma
id|line
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|line-&gt;sigio
)paren
(brace
id|chan_enable_winch
c_func
(paren
op_amp
id|line-&gt;chan_list
comma
id|line
)paren
suffix:semicolon
id|line-&gt;sigio
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* This is outside the if because the initial console is opened&n;&t; * with tty == NULL&n;&t; */
id|line-&gt;tty
op_assign
id|tty
suffix:semicolon
r_if
c_cond
(paren
id|tty
op_ne
l_int|NULL
)paren
(brace
id|tty-&gt;driver_data
op_assign
id|line
suffix:semicolon
id|chan_window_size
c_func
(paren
op_amp
id|line-&gt;chan_list
comma
op_amp
id|tty-&gt;winsize.ws_row
comma
op_amp
id|tty-&gt;winsize.ws_col
)paren
suffix:semicolon
)brace
id|line-&gt;count
op_increment
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|line-&gt;sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|line_close
r_void
id|line_close
c_func
(paren
r_struct
id|line
op_star
id|lines
comma
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|line
op_star
id|line
suffix:semicolon
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
id|tty
op_eq
l_int|NULL
)paren
(brace
id|n
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|n
op_assign
id|tty-&gt;index
suffix:semicolon
id|line
op_assign
op_amp
id|lines
(braket
id|n
)braket
suffix:semicolon
id|down
c_func
(paren
op_amp
id|line-&gt;sem
)paren
suffix:semicolon
id|line-&gt;count
op_decrement
suffix:semicolon
multiline_comment|/* I don&squot;t like this, but I can&squot;t think of anything better.  What&squot;s&n;&t; * going on is that the tty is in the process of being closed for&n;&t; * the last time.  Its count hasn&squot;t been dropped yet, so it&squot;s still&n;&t; * at 1.  This may happen when line-&gt;count != 0 because of the initial&n;&t; * console open (without a tty) bumping it up to 1.&n;&t; */
r_if
c_cond
(paren
(paren
id|line-&gt;tty
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|line-&gt;tty-&gt;count
op_eq
l_int|1
)paren
)paren
(brace
id|line-&gt;tty
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|line-&gt;count
op_eq
l_int|0
)paren
(brace
id|line_disable
c_func
(paren
id|line
comma
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|line-&gt;sem
)paren
suffix:semicolon
)brace
DECL|function|close_lines
r_void
id|close_lines
c_func
(paren
r_struct
id|line
op_star
id|lines
comma
r_int
id|nlines
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
id|nlines
suffix:semicolon
id|i
op_increment
)paren
(brace
id|close_chan
c_func
(paren
op_amp
id|lines
(braket
id|i
)braket
dot
id|chan_list
)paren
suffix:semicolon
)brace
)brace
DECL|function|line_setup
r_int
id|line_setup
c_func
(paren
r_struct
id|line
op_star
id|lines
comma
r_int
id|num
comma
r_char
op_star
id|init
comma
r_int
id|all_allowed
)paren
(brace
r_int
id|i
comma
id|n
suffix:semicolon
r_char
op_star
id|end
suffix:semicolon
r_if
c_cond
(paren
op_star
id|init
op_eq
l_char|&squot;=&squot;
)paren
(brace
id|n
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|n
op_assign
id|simple_strtoul
c_func
(paren
id|init
comma
op_amp
id|end
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|end
op_ne
l_char|&squot;=&squot;
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;line_setup failed to parse &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|init
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|init
op_assign
id|end
suffix:semicolon
)brace
id|init
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|n
op_ge
l_int|0
)paren
op_logical_and
(paren
id|n
op_ge
id|num
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;line_setup - %d out of range ((0 ... %d) allowed)&bslash;n&quot;
comma
id|n
comma
id|num
op_minus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|lines
(braket
id|n
)braket
dot
id|count
OG
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;line_setup - device %d is open&bslash;n&quot;
comma
id|n
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lines
(braket
id|n
)braket
dot
id|init_pri
op_le
id|INIT_ONE
)paren
(brace
id|lines
(braket
id|n
)braket
dot
id|init_pri
op_assign
id|INIT_ONE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|init
comma
l_string|&quot;none&quot;
)paren
)paren
(brace
id|lines
(braket
id|n
)braket
dot
id|valid
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|lines
(braket
id|n
)braket
dot
id|init_str
op_assign
id|init
suffix:semicolon
id|lines
(braket
id|n
)braket
dot
id|valid
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|all_allowed
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;line_setup - can&squot;t configure all devices from &quot;
l_string|&quot;mconsole&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|lines
(braket
id|i
)braket
dot
id|init_pri
op_le
id|INIT_ALL
)paren
(brace
id|lines
(braket
id|i
)braket
dot
id|init_pri
op_assign
id|INIT_ALL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|init
comma
l_string|&quot;none&quot;
)paren
)paren
(brace
id|lines
(braket
id|i
)braket
dot
id|valid
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|lines
(braket
id|i
)braket
dot
id|init_str
op_assign
id|init
suffix:semicolon
id|lines
(braket
id|i
)braket
dot
id|valid
op_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|line_config
r_int
id|line_config
c_func
(paren
r_struct
id|line
op_star
id|lines
comma
r_int
id|num
comma
r_char
op_star
id|str
)paren
(brace
r_char
op_star
r_new
op_assign
id|uml_strdup
c_func
(paren
id|str
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
id|printk
c_func
(paren
l_string|&quot;line_config - uml_strdup failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_return
op_logical_neg
id|line_setup
c_func
(paren
id|lines
comma
id|num
comma
r_new
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|line_get_config
r_int
id|line_get_config
c_func
(paren
r_char
op_star
id|name
comma
r_struct
id|line
op_star
id|lines
comma
r_int
id|num
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
id|line
op_star
id|line
suffix:semicolon
r_char
op_star
id|end
suffix:semicolon
r_int
id|dev
comma
id|n
op_assign
l_int|0
suffix:semicolon
id|dev
op_assign
id|simple_strtoul
c_func
(paren
id|name
comma
op_amp
id|end
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|end
op_ne
l_char|&squot;&bslash;0&squot;
)paren
op_logical_or
(paren
id|end
op_eq
id|name
)paren
)paren
(brace
op_star
id|error_out
op_assign
l_string|&quot;line_get_config failed to parse device number&quot;
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|dev
OL
l_int|0
)paren
op_logical_or
(paren
id|dev
op_ge
id|num
)paren
)paren
(brace
op_star
id|error_out
op_assign
l_string|&quot;device number of of range&quot;
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|line
op_assign
op_amp
id|lines
(braket
id|dev
)braket
suffix:semicolon
id|down
c_func
(paren
op_amp
id|line-&gt;sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|line-&gt;valid
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
)brace
r_else
r_if
c_cond
(paren
id|line-&gt;count
op_eq
l_int|0
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
id|line-&gt;init_str
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|n
op_assign
id|chan_config_string
c_func
(paren
op_amp
id|line-&gt;chan_list
comma
id|str
comma
id|size
comma
id|error_out
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|line-&gt;sem
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|function|line_remove
r_int
id|line_remove
c_func
(paren
r_struct
id|line
op_star
id|lines
comma
r_int
id|num
comma
r_char
op_star
id|str
)paren
(brace
r_char
id|config
(braket
r_sizeof
(paren
l_string|&quot;conxxxx=none&bslash;0&quot;
)paren
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|config
comma
l_string|&quot;%s=none&quot;
comma
id|str
)paren
suffix:semicolon
r_return
op_logical_neg
id|line_setup
c_func
(paren
id|lines
comma
id|num
comma
id|config
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|line_write_room
r_int
id|line_write_room
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|line
op_star
id|dev
op_assign
id|tty-&gt;driver_data
suffix:semicolon
r_return
id|write_room
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|line_register_devfs
r_struct
id|tty_driver
op_star
id|line_register_devfs
c_func
(paren
r_struct
id|lines
op_star
id|set
comma
r_struct
id|line_driver
op_star
id|line_driver
comma
r_struct
id|tty_operations
op_star
id|ops
comma
r_struct
id|line
op_star
id|lines
comma
r_int
id|nlines
)paren
(brace
r_int
id|err
comma
id|i
suffix:semicolon
r_char
op_star
id|from
comma
op_star
id|to
suffix:semicolon
r_struct
id|tty_driver
op_star
id|driver
op_assign
id|alloc_tty_driver
c_func
(paren
id|nlines
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|driver
)paren
r_return
l_int|NULL
suffix:semicolon
id|driver-&gt;driver_name
op_assign
id|line_driver-&gt;name
suffix:semicolon
id|driver-&gt;name
op_assign
id|line_driver-&gt;device_name
suffix:semicolon
id|driver-&gt;devfs_name
op_assign
id|line_driver-&gt;devfs_name
suffix:semicolon
id|driver-&gt;major
op_assign
id|line_driver-&gt;major
suffix:semicolon
id|driver-&gt;minor_start
op_assign
id|line_driver-&gt;minor_start
suffix:semicolon
id|driver-&gt;type
op_assign
id|line_driver-&gt;type
suffix:semicolon
id|driver-&gt;subtype
op_assign
id|line_driver-&gt;subtype
suffix:semicolon
id|driver-&gt;flags
op_assign
id|TTY_DRIVER_REAL_RAW
suffix:semicolon
id|driver-&gt;init_termios
op_assign
id|tty_std_termios
suffix:semicolon
id|tty_set_operations
c_func
(paren
id|driver
comma
id|ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty_register_driver
c_func
(paren
id|driver
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;line_register_devfs : Couldn&squot;t register driver&bslash;n&quot;
)paren
suffix:semicolon
id|from
op_assign
id|line_driver-&gt;symlink_from
suffix:semicolon
id|to
op_assign
id|line_driver-&gt;symlink_to
suffix:semicolon
id|err
op_assign
id|devfs_mk_symlink
c_func
(paren
id|from
comma
id|to
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Symlink creation from /dev/%s to /dev/%s &quot;
l_string|&quot;returned %d&bslash;n&quot;
comma
id|from
comma
id|to
comma
id|err
)paren
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
id|nlines
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lines
(braket
id|i
)braket
dot
id|valid
)paren
(brace
id|tty_unregister_device
c_func
(paren
id|driver
comma
id|i
)paren
suffix:semicolon
)brace
)brace
id|mconsole_register_dev
c_func
(paren
op_amp
id|line_driver-&gt;mc
)paren
suffix:semicolon
r_return
id|driver
suffix:semicolon
)brace
DECL|function|lines_init
r_void
id|lines_init
c_func
(paren
r_struct
id|line
op_star
id|lines
comma
r_int
id|nlines
)paren
(brace
r_struct
id|line
op_star
id|line
suffix:semicolon
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
id|nlines
suffix:semicolon
id|i
op_increment
)paren
(brace
id|line
op_assign
op_amp
id|lines
(braket
id|i
)braket
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|line-&gt;chan_list
)paren
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|line-&gt;sem
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line-&gt;init_str
op_ne
l_int|NULL
)paren
(brace
id|line-&gt;init_str
op_assign
id|uml_strdup
c_func
(paren
id|line-&gt;init_str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line-&gt;init_str
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lines_init - uml_strdup returned &quot;
l_string|&quot;NULL&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|struct|winch
r_struct
id|winch
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|tty_fd
r_int
id|tty_fd
suffix:semicolon
DECL|member|pid
r_int
id|pid
suffix:semicolon
DECL|member|line
r_struct
id|line
op_star
id|line
suffix:semicolon
)brace
suffix:semicolon
DECL|function|winch_interrupt
id|irqreturn_t
id|winch_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|data
comma
r_struct
id|pt_regs
op_star
id|unused
)paren
(brace
r_struct
id|winch
op_star
id|winch
op_assign
id|data
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_int
id|err
suffix:semicolon
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|winch-&gt;fd
op_ne
op_minus
l_int|1
)paren
(brace
id|err
op_assign
id|generic_read
c_func
(paren
id|winch-&gt;fd
comma
op_amp
id|c
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|err
op_ne
op_minus
id|EAGAIN
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;winch_interrupt : read failed, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fd %d is losing SIGWINCH support&bslash;n&quot;
comma
id|winch-&gt;tty_fd
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_goto
id|out
suffix:semicolon
)brace
)brace
id|tty
op_assign
id|winch-&gt;line-&gt;tty
suffix:semicolon
r_if
c_cond
(paren
id|tty
op_ne
l_int|NULL
)paren
(brace
id|chan_window_size
c_func
(paren
op_amp
id|winch-&gt;line-&gt;chan_list
comma
op_amp
id|tty-&gt;winsize.ws_row
comma
op_amp
id|tty-&gt;winsize.ws_col
)paren
suffix:semicolon
id|kill_pg
c_func
(paren
id|tty-&gt;pgrp
comma
id|SIGWINCH
comma
l_int|1
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|winch-&gt;fd
op_ne
op_minus
l_int|1
)paren
(brace
id|reactivate_fd
c_func
(paren
id|winch-&gt;fd
comma
id|WINCH_IRQ
)paren
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|variable|winch_handler_sem
id|DECLARE_MUTEX
c_func
(paren
id|winch_handler_sem
)paren
suffix:semicolon
DECL|variable|winch_handlers
id|LIST_HEAD
c_func
(paren
id|winch_handlers
)paren
suffix:semicolon
DECL|function|register_winch_irq
r_void
id|register_winch_irq
c_func
(paren
r_int
id|fd
comma
r_int
id|tty_fd
comma
r_int
id|pid
comma
r_void
op_star
id|line
)paren
(brace
r_struct
id|winch
op_star
id|winch
suffix:semicolon
id|down
c_func
(paren
op_amp
id|winch_handler_sem
)paren
suffix:semicolon
id|winch
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|winch
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|winch
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;register_winch_irq - kmalloc failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
op_star
id|winch
op_assign
(paren
(paren
r_struct
id|winch
)paren
(brace
dot
id|list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|winch-&gt;list
)paren
comma
dot
id|fd
op_assign
id|fd
comma
dot
id|tty_fd
op_assign
id|tty_fd
comma
dot
id|pid
op_assign
id|pid
comma
dot
id|line
op_assign
id|line
)brace
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|winch-&gt;list
comma
op_amp
id|winch_handlers
)paren
suffix:semicolon
r_if
c_cond
(paren
id|um_request_irq
c_func
(paren
id|WINCH_IRQ
comma
id|fd
comma
id|IRQ_READ
comma
id|winch_interrupt
comma
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
op_or
id|SA_SAMPLE_RANDOM
comma
l_string|&quot;winch&quot;
comma
id|winch
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;register_winch_irq - failed to register IRQ&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|winch_handler_sem
)paren
suffix:semicolon
)brace
DECL|function|winch_cleanup
r_static
r_void
id|winch_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|ele
suffix:semicolon
r_struct
id|winch
op_star
id|winch
suffix:semicolon
(def_block
id|list_for_each
c_func
(paren
id|ele
comma
op_amp
id|winch_handlers
)paren
(brace
id|winch
op_assign
id|list_entry
c_func
(paren
id|ele
comma
r_struct
id|winch
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|winch-&gt;fd
op_ne
op_minus
l_int|1
)paren
(brace
id|deactivate_fd
c_func
(paren
id|winch-&gt;fd
comma
id|WINCH_IRQ
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|winch-&gt;fd
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|winch-&gt;pid
op_ne
op_minus
l_int|1
)paren
(brace
id|os_kill_process
c_func
(paren
id|winch-&gt;pid
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
)def_block
)brace
DECL|variable|winch_cleanup
id|__uml_exitcall
c_func
(paren
id|winch_cleanup
)paren
suffix:semicolon
DECL|function|add_xterm_umid
r_char
op_star
id|add_xterm_umid
c_func
(paren
r_char
op_star
id|base
)paren
(brace
r_char
op_star
id|umid
comma
op_star
id|title
suffix:semicolon
r_int
id|len
suffix:semicolon
id|umid
op_assign
id|get_umid
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|umid
op_eq
l_int|NULL
)paren
(brace
r_return
id|base
suffix:semicolon
)brace
id|len
op_assign
id|strlen
c_func
(paren
id|base
)paren
op_plus
id|strlen
c_func
(paren
l_string|&quot; ()&quot;
)paren
op_plus
id|strlen
c_func
(paren
id|umid
)paren
op_plus
l_int|1
suffix:semicolon
id|title
op_assign
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|title
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to allocate buffer for xterm title&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|base
suffix:semicolon
)brace
id|snprintf
c_func
(paren
id|title
comma
id|len
comma
l_string|&quot;%s (%s)&quot;
comma
id|base
comma
id|umid
)paren
suffix:semicolon
r_return
id|title
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
