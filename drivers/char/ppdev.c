multiline_comment|/*&n; * linux/drivers/char/ppdev.c&n; *&n; * This is the code behind /dev/parport* -- it allows a user-space&n; * application to use the parport subsystem.&n; *&n; * Copyright (C) 1998-2000, 2002 Tim Waugh &lt;tim@cyberelk.net&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * A /dev/parportx device node represents an arbitrary device&n; * on port &squot;x&squot;.  The following operations are possible:&n; *&n; * open&t;&t;do nothing, set up default IEEE 1284 protocol to be COMPAT&n; * close&t;release port and unregister device (if necessary)&n; * ioctl&n; *   EXCL&t;register device exclusively (may fail)&n; *   CLAIM&t;(register device first time) parport_claim_or_block&n; *   RELEASE&t;parport_release&n; *   SETMODE&t;set the IEEE 1284 protocol to use for read/write&n; *   SETPHASE&t;set the IEEE 1284 phase of a particular mode.  Not to be&n; *              confused with ioctl(fd, SETPHASER, &amp;stun). ;-)&n; *   DATADIR&t;data_forward / data_reverse&n; *   WDATA&t;write_data&n; *   RDATA&t;read_data&n; *   WCONTROL&t;write_control&n; *   RCONTROL&t;read_control&n; *   FCONTROL&t;frob_control&n; *   RSTATUS&t;read_status&n; *   NEGOT&t;parport_negotiate&n; *   YIELD&t;parport_yield_blocking&n; *   WCTLONIRQ&t;on interrupt, set control lines&n; *   CLRIRQ&t;clear (and return) interrupt count&n; *   SETTIME&t;sets device timeout (struct timeval)&n; *   GETTIME&t;gets device timeout (struct timeval)&n; *   GETMODES&t;gets hardware supported modes (unsigned int)&n; *   GETMODE&t;gets the current IEEE1284 mode&n; *   GETPHASE   gets the current IEEE1284 phase&n; *   GETFLAGS   gets current (user-visible) flags&n; *   SETFLAGS   sets current (user-visible) flags&n; * read/write&t;read or write in current IEEE 1284 protocol&n; * select&t;wait for interrupt (in readfds)&n; *&n; * Changes:&n; * Added SETTIME/GETTIME ioctl, Fred Barnes, 1999.&n; *&n; * Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt; 2000/08/25&n; * - On error, copy_from_user and copy_to_user do not return -EFAULT,&n; *   They return the positive number of bytes *not* copied due to address&n; *   space errors.&n; *&n; * Added GETMODES/GETMODE/GETPHASE ioctls, Fred Barnes &lt;frmb2@ukc.ac.uk&gt;, 03/01/2001.&n; * Added GETFLAGS/SETFLAGS ioctls, Fred Barnes, 04/2001&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/ppdev.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
DECL|macro|PP_VERSION
mdefine_line|#define PP_VERSION &quot;ppdev: user-space parallel port driver&quot;
DECL|macro|CHRDEV
mdefine_line|#define CHRDEV &quot;ppdev&quot;
DECL|struct|pp_struct
r_struct
id|pp_struct
(brace
DECL|member|pdev
r_struct
id|pardevice
op_star
id|pdev
suffix:semicolon
DECL|member|irq_wait
id|wait_queue_head_t
id|irq_wait
suffix:semicolon
DECL|member|irqc
id|atomic_t
id|irqc
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|irqresponse
r_int
id|irqresponse
suffix:semicolon
DECL|member|irqctl
r_int
r_char
id|irqctl
suffix:semicolon
DECL|member|state
r_struct
id|ieee1284_info
id|state
suffix:semicolon
DECL|member|saved_state
r_struct
id|ieee1284_info
id|saved_state
suffix:semicolon
DECL|member|default_inactivity
r_int
id|default_inactivity
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* pp_struct.flags bitfields */
DECL|macro|PP_CLAIMED
mdefine_line|#define PP_CLAIMED    (1&lt;&lt;0)
DECL|macro|PP_EXCL
mdefine_line|#define PP_EXCL       (1&lt;&lt;1)
multiline_comment|/* Other constants */
DECL|macro|PP_INTERRUPT_TIMEOUT
mdefine_line|#define PP_INTERRUPT_TIMEOUT (10 * HZ) /* 10s */
DECL|macro|PP_BUFFER_SIZE
mdefine_line|#define PP_BUFFER_SIZE 1024
DECL|macro|PARDEVICE_MAX
mdefine_line|#define PARDEVICE_MAX 8
multiline_comment|/* ROUND_UP macro from fs/select.c */
DECL|macro|ROUND_UP
mdefine_line|#define ROUND_UP(x,y) (((x)+(y)-1)/(y))
DECL|function|pp_enable_irq
r_static
r_inline
r_void
id|pp_enable_irq
(paren
r_struct
id|pp_struct
op_star
id|pp
)paren
(brace
r_struct
id|parport
op_star
id|port
op_assign
id|pp-&gt;pdev-&gt;port
suffix:semicolon
id|port-&gt;ops-&gt;enable_irq
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|pp_read
r_static
id|ssize_t
id|pp_read
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
r_int
r_int
id|minor
op_assign
id|minor
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|pp_struct
op_star
id|pp
op_assign
id|file-&gt;private_data
suffix:semicolon
r_char
op_star
id|kbuffer
suffix:semicolon
id|ssize_t
id|bytes_read
op_assign
l_int|0
suffix:semicolon
r_struct
id|parport
op_star
id|pport
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pp-&gt;flags
op_amp
id|PP_CLAIMED
)paren
)paren
(brace
multiline_comment|/* Don&squot;t have the port claimed */
id|printk
(paren
id|KERN_DEBUG
id|CHRDEV
l_string|&quot;%x: claim the port first&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Trivial case. */
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|kbuffer
op_assign
id|kmalloc
c_func
(paren
id|min_t
c_func
(paren
r_int
comma
id|count
comma
id|PP_BUFFER_SIZE
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbuffer
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|pport
op_assign
id|pp-&gt;pdev-&gt;port
suffix:semicolon
id|mode
op_assign
id|pport-&gt;ieee1284.mode
op_amp
op_complement
(paren
id|IEEE1284_DEVICEID
op_or
id|IEEE1284_ADDR
)paren
suffix:semicolon
id|parport_set_timeout
(paren
id|pp-&gt;pdev
comma
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
ques
c_cond
id|PARPORT_INACTIVITY_O_NONBLOCK
suffix:colon
id|pp-&gt;default_inactivity
)paren
suffix:semicolon
r_while
c_loop
(paren
id|bytes_read
op_eq
l_int|0
)paren
(brace
id|ssize_t
id|need
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|count
comma
id|PP_BUFFER_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
id|IEEE1284_MODE_EPP
)paren
(brace
multiline_comment|/* various specials for EPP mode */
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_int
(paren
op_star
id|fn
)paren
(paren
r_struct
id|parport
op_star
comma
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pp-&gt;flags
op_amp
id|PP_W91284PIC
)paren
(brace
id|flags
op_or_assign
id|PARPORT_W91284PIC
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pp-&gt;flags
op_amp
id|PP_FASTREAD
)paren
(brace
id|flags
op_or_assign
id|PARPORT_EPP_FAST
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pport-&gt;ieee1284.mode
op_amp
id|IEEE1284_ADDR
)paren
(brace
id|fn
op_assign
id|pport-&gt;ops-&gt;epp_read_addr
suffix:semicolon
)brace
r_else
(brace
id|fn
op_assign
id|pport-&gt;ops-&gt;epp_read_data
suffix:semicolon
)brace
id|bytes_read
op_assign
(paren
op_star
id|fn
)paren
(paren
id|pport
comma
id|kbuffer
comma
id|need
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
(brace
id|bytes_read
op_assign
id|parport_read
(paren
id|pport
comma
id|kbuffer
comma
id|need
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bytes_read
op_ne
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
id|bytes_read
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|signal_pending
(paren
id|current
)paren
)paren
(brace
id|bytes_read
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
id|parport_set_timeout
(paren
id|pp-&gt;pdev
comma
id|pp-&gt;default_inactivity
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bytes_read
OG
l_int|0
op_logical_and
id|copy_to_user
(paren
id|buf
comma
id|kbuffer
comma
id|bytes_read
)paren
)paren
id|bytes_read
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|kfree
(paren
id|kbuffer
)paren
suffix:semicolon
id|pp_enable_irq
(paren
id|pp
)paren
suffix:semicolon
r_return
id|bytes_read
suffix:semicolon
)brace
DECL|function|pp_write
r_static
id|ssize_t
id|pp_write
(paren
r_struct
id|file
op_star
id|file
comma
r_const
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
r_int
r_int
id|minor
op_assign
id|minor
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|pp_struct
op_star
id|pp
op_assign
id|file-&gt;private_data
suffix:semicolon
r_char
op_star
id|kbuffer
suffix:semicolon
id|ssize_t
id|bytes_written
op_assign
l_int|0
suffix:semicolon
id|ssize_t
id|wrote
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_struct
id|parport
op_star
id|pport
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pp-&gt;flags
op_amp
id|PP_CLAIMED
)paren
)paren
(brace
multiline_comment|/* Don&squot;t have the port claimed */
id|printk
(paren
id|KERN_DEBUG
id|CHRDEV
l_string|&quot;%x: claim the port first&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|kbuffer
op_assign
id|kmalloc
c_func
(paren
id|min_t
c_func
(paren
r_int
comma
id|count
comma
id|PP_BUFFER_SIZE
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kbuffer
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|pport
op_assign
id|pp-&gt;pdev-&gt;port
suffix:semicolon
id|mode
op_assign
id|pport-&gt;ieee1284.mode
op_amp
op_complement
(paren
id|IEEE1284_DEVICEID
op_or
id|IEEE1284_ADDR
)paren
suffix:semicolon
id|parport_set_timeout
(paren
id|pp-&gt;pdev
comma
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
ques
c_cond
id|PARPORT_INACTIVITY_O_NONBLOCK
suffix:colon
id|pp-&gt;default_inactivity
)paren
suffix:semicolon
r_while
c_loop
(paren
id|bytes_written
OL
id|count
)paren
(brace
id|ssize_t
id|n
op_assign
id|min_t
c_func
(paren
r_int
r_int
comma
id|count
op_minus
id|bytes_written
comma
id|PP_BUFFER_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
(paren
id|kbuffer
comma
id|buf
op_plus
id|bytes_written
comma
id|n
)paren
)paren
(brace
id|bytes_written
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pp-&gt;flags
op_amp
id|PP_FASTWRITE
)paren
op_logical_and
(paren
id|mode
op_eq
id|IEEE1284_MODE_EPP
)paren
)paren
(brace
multiline_comment|/* do a fast EPP write */
r_if
c_cond
(paren
id|pport-&gt;ieee1284.mode
op_amp
id|IEEE1284_ADDR
)paren
(brace
id|wrote
op_assign
id|pport-&gt;ops-&gt;epp_write_addr
(paren
id|pport
comma
id|kbuffer
comma
id|n
comma
id|PARPORT_EPP_FAST
)paren
suffix:semicolon
)brace
r_else
(brace
id|wrote
op_assign
id|pport-&gt;ops-&gt;epp_write_data
(paren
id|pport
comma
id|kbuffer
comma
id|n
comma
id|PARPORT_EPP_FAST
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|wrote
op_assign
id|parport_write
(paren
id|pp-&gt;pdev-&gt;port
comma
id|kbuffer
comma
id|n
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wrote
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bytes_written
)paren
(brace
id|bytes_written
op_assign
id|wrote
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|bytes_written
op_add_assign
id|wrote
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bytes_written
)paren
id|bytes_written
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|signal_pending
(paren
id|current
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bytes_written
)paren
(brace
id|bytes_written
op_assign
op_minus
id|EINTR
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
id|parport_set_timeout
(paren
id|pp-&gt;pdev
comma
id|pp-&gt;default_inactivity
)paren
suffix:semicolon
id|kfree
(paren
id|kbuffer
)paren
suffix:semicolon
id|pp_enable_irq
(paren
id|pp
)paren
suffix:semicolon
r_return
id|bytes_written
suffix:semicolon
)brace
DECL|function|pp_irq
r_static
r_void
id|pp_irq
(paren
r_int
id|irq
comma
r_void
op_star
r_private
comma
r_struct
id|pt_regs
op_star
id|unused
)paren
(brace
r_struct
id|pp_struct
op_star
id|pp
op_assign
(paren
r_struct
id|pp_struct
op_star
)paren
r_private
suffix:semicolon
r_if
c_cond
(paren
id|pp-&gt;irqresponse
)paren
(brace
id|parport_write_control
(paren
id|pp-&gt;pdev-&gt;port
comma
id|pp-&gt;irqctl
)paren
suffix:semicolon
id|pp-&gt;irqresponse
op_assign
l_int|0
suffix:semicolon
)brace
id|atomic_inc
(paren
op_amp
id|pp-&gt;irqc
)paren
suffix:semicolon
id|wake_up_interruptible
(paren
op_amp
id|pp-&gt;irq_wait
)paren
suffix:semicolon
)brace
DECL|function|register_device
r_static
r_int
id|register_device
(paren
r_int
id|minor
comma
r_struct
id|pp_struct
op_star
id|pp
)paren
(brace
r_struct
id|parport
op_star
id|port
suffix:semicolon
r_struct
id|pardevice
op_star
id|pdev
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|fl
suffix:semicolon
id|name
op_assign
id|kmalloc
(paren
id|strlen
(paren
id|CHRDEV
)paren
op_plus
l_int|3
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|sprintf
(paren
id|name
comma
id|CHRDEV
l_string|&quot;%x&quot;
comma
id|minor
)paren
suffix:semicolon
id|port
op_assign
id|parport_find_number
(paren
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;%s: no associated port!&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|kfree
(paren
id|name
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|fl
op_assign
(paren
id|pp-&gt;flags
op_amp
id|PP_EXCL
)paren
ques
c_cond
id|PARPORT_FLAG_EXCL
suffix:colon
l_int|0
suffix:semicolon
id|pdev
op_assign
id|parport_register_device
(paren
id|port
comma
id|name
comma
l_int|NULL
comma
l_int|NULL
comma
id|pp_irq
comma
id|fl
comma
id|pp
)paren
suffix:semicolon
id|parport_put_port
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdev
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;%s: failed to register device!&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|kfree
(paren
id|name
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|pp-&gt;pdev
op_assign
id|pdev
suffix:semicolon
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s: registered pardevice&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_phase
r_static
r_enum
id|ieee1284_phase
id|init_phase
(paren
r_int
id|mode
)paren
(brace
r_switch
c_cond
(paren
id|mode
op_amp
op_complement
(paren
id|IEEE1284_DEVICEID
op_or
id|IEEE1284_ADDR
)paren
)paren
(brace
r_case
id|IEEE1284_MODE_NIBBLE
suffix:colon
r_case
id|IEEE1284_MODE_BYTE
suffix:colon
r_return
id|IEEE1284_PH_REV_IDLE
suffix:semicolon
)brace
r_return
id|IEEE1284_PH_FWD_IDLE
suffix:semicolon
)brace
DECL|function|pp_ioctl
r_static
r_int
id|pp_ioctl
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
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
r_int
id|minor
op_assign
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|pp_struct
op_star
id|pp
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|parport
op_star
id|port
suffix:semicolon
multiline_comment|/* First handle the cases that don&squot;t take arguments. */
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|PPCLAIM
suffix:colon
(brace
r_struct
id|ieee1284_info
op_star
id|info
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|pp-&gt;flags
op_amp
id|PP_CLAIMED
)paren
(brace
id|printk
(paren
id|KERN_DEBUG
id|CHRDEV
l_string|&quot;%x: you&squot;ve already got it!&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Deferred device registration. */
r_if
c_cond
(paren
op_logical_neg
id|pp-&gt;pdev
)paren
(brace
r_int
id|err
op_assign
id|register_device
(paren
id|minor
comma
id|pp
)paren
suffix:semicolon
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
)brace
id|ret
op_assign
id|parport_claim_or_block
(paren
id|pp-&gt;pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|pp-&gt;flags
op_or_assign
id|PP_CLAIMED
suffix:semicolon
multiline_comment|/* For interrupt-reporting to work, we need to be&n;&t;&t; * informed of each interrupt. */
id|pp_enable_irq
(paren
id|pp
)paren
suffix:semicolon
multiline_comment|/* We may need to fix up the state machine. */
id|info
op_assign
op_amp
id|pp-&gt;pdev-&gt;port-&gt;ieee1284
suffix:semicolon
id|pp-&gt;saved_state.mode
op_assign
id|info-&gt;mode
suffix:semicolon
id|pp-&gt;saved_state.phase
op_assign
id|info-&gt;phase
suffix:semicolon
id|info-&gt;mode
op_assign
id|pp-&gt;state.mode
suffix:semicolon
id|info-&gt;phase
op_assign
id|pp-&gt;state.phase
suffix:semicolon
id|pp-&gt;default_inactivity
op_assign
id|parport_set_timeout
(paren
id|pp-&gt;pdev
comma
l_int|0
)paren
suffix:semicolon
id|parport_set_timeout
(paren
id|pp-&gt;pdev
comma
id|pp-&gt;default_inactivity
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|PPEXCL
suffix:colon
r_if
c_cond
(paren
id|pp-&gt;pdev
)paren
(brace
id|printk
(paren
id|KERN_DEBUG
id|CHRDEV
l_string|&quot;%x: too late for PPEXCL; &quot;
l_string|&quot;already registered&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pp-&gt;flags
op_amp
id|PP_EXCL
)paren
multiline_comment|/* But it&squot;s not really an error. */
r_return
l_int|0
suffix:semicolon
multiline_comment|/* There&squot;s no chance of making the driver happy. */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Just remember to register the device exclusively&n;&t;&t; * when we finally do the registration. */
id|pp-&gt;flags
op_or_assign
id|PP_EXCL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PPSETMODE
suffix:colon
(brace
r_int
id|mode
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
(paren
op_amp
id|mode
comma
(paren
r_int
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|mode
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* FIXME: validate mode */
id|pp-&gt;state.mode
op_assign
id|mode
suffix:semicolon
id|pp-&gt;state.phase
op_assign
id|init_phase
(paren
id|mode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pp-&gt;flags
op_amp
id|PP_CLAIMED
)paren
(brace
id|pp-&gt;pdev-&gt;port-&gt;ieee1284.mode
op_assign
id|mode
suffix:semicolon
id|pp-&gt;pdev-&gt;port-&gt;ieee1284.phase
op_assign
id|pp-&gt;state.phase
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|PPGETMODE
suffix:colon
(brace
r_int
id|mode
suffix:semicolon
r_if
c_cond
(paren
id|pp-&gt;flags
op_amp
id|PP_CLAIMED
)paren
(brace
id|mode
op_assign
id|pp-&gt;pdev-&gt;port-&gt;ieee1284.mode
suffix:semicolon
)brace
r_else
(brace
id|mode
op_assign
id|pp-&gt;state.mode
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
(paren
(paren
r_int
op_star
)paren
id|arg
comma
op_amp
id|mode
comma
r_sizeof
(paren
id|mode
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|PPSETPHASE
suffix:colon
(brace
r_int
id|phase
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
(paren
op_amp
id|phase
comma
(paren
r_int
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|phase
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* FIXME: validate phase */
id|pp-&gt;state.phase
op_assign
id|phase
suffix:semicolon
r_if
c_cond
(paren
id|pp-&gt;flags
op_amp
id|PP_CLAIMED
)paren
(brace
id|pp-&gt;pdev-&gt;port-&gt;ieee1284.phase
op_assign
id|phase
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|PPGETPHASE
suffix:colon
(brace
r_int
id|phase
suffix:semicolon
r_if
c_cond
(paren
id|pp-&gt;flags
op_amp
id|PP_CLAIMED
)paren
(brace
id|phase
op_assign
id|pp-&gt;pdev-&gt;port-&gt;ieee1284.phase
suffix:semicolon
)brace
r_else
(brace
id|phase
op_assign
id|pp-&gt;state.phase
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
(paren
(paren
r_int
op_star
)paren
id|arg
comma
op_amp
id|phase
comma
r_sizeof
(paren
id|phase
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|PPGETMODES
suffix:colon
(brace
r_int
r_int
id|modes
suffix:semicolon
id|port
op_assign
id|parport_find_number
(paren
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|port
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|modes
op_assign
id|port-&gt;modes
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
(paren
(paren
r_int
r_int
op_star
)paren
id|arg
comma
op_amp
id|modes
comma
r_sizeof
(paren
id|modes
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|PPSETFLAGS
suffix:colon
(brace
r_int
id|uflags
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
(paren
op_amp
id|uflags
comma
(paren
r_int
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|uflags
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|pp-&gt;flags
op_and_assign
op_complement
id|PP_FLAGMASK
suffix:semicolon
id|pp-&gt;flags
op_or_assign
(paren
id|uflags
op_amp
id|PP_FLAGMASK
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|PPGETFLAGS
suffix:colon
(brace
r_int
id|uflags
suffix:semicolon
id|uflags
op_assign
id|pp-&gt;flags
op_amp
id|PP_FLAGMASK
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
(paren
(paren
r_int
op_star
)paren
id|arg
comma
op_amp
id|uflags
comma
r_sizeof
(paren
id|uflags
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* end switch() */
multiline_comment|/* Everything else requires the port to be claimed, so check&n;&t; * that now. */
r_if
c_cond
(paren
(paren
id|pp-&gt;flags
op_amp
id|PP_CLAIMED
)paren
op_eq
l_int|0
)paren
(brace
id|printk
(paren
id|KERN_DEBUG
id|CHRDEV
l_string|&quot;%x: claim the port first&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|port
op_assign
id|pp-&gt;pdev-&gt;port
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_struct
id|ieee1284_info
op_star
id|info
suffix:semicolon
r_int
r_char
id|reg
suffix:semicolon
r_int
r_char
id|mask
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_struct
id|timeval
id|par_timeout
suffix:semicolon
r_int
id|to_jiffies
suffix:semicolon
r_case
id|PPRSTATUS
suffix:colon
id|reg
op_assign
id|parport_read_status
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
(paren
(paren
r_int
r_char
op_star
)paren
id|arg
comma
op_amp
id|reg
comma
r_sizeof
(paren
id|reg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PPRDATA
suffix:colon
id|reg
op_assign
id|parport_read_data
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
(paren
(paren
r_int
r_char
op_star
)paren
id|arg
comma
op_amp
id|reg
comma
r_sizeof
(paren
id|reg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PPRCONTROL
suffix:colon
id|reg
op_assign
id|parport_read_control
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
(paren
(paren
r_int
r_char
op_star
)paren
id|arg
comma
op_amp
id|reg
comma
r_sizeof
(paren
id|reg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PPYIELD
suffix:colon
id|parport_yield_blocking
(paren
id|pp-&gt;pdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PPRELEASE
suffix:colon
multiline_comment|/* Save the state machine&squot;s state. */
id|info
op_assign
op_amp
id|pp-&gt;pdev-&gt;port-&gt;ieee1284
suffix:semicolon
id|pp-&gt;state.mode
op_assign
id|info-&gt;mode
suffix:semicolon
id|pp-&gt;state.phase
op_assign
id|info-&gt;phase
suffix:semicolon
id|info-&gt;mode
op_assign
id|pp-&gt;saved_state.mode
suffix:semicolon
id|info-&gt;phase
op_assign
id|pp-&gt;saved_state.phase
suffix:semicolon
id|parport_release
(paren
id|pp-&gt;pdev
)paren
suffix:semicolon
id|pp-&gt;flags
op_and_assign
op_complement
id|PP_CLAIMED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PPWCONTROL
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
(paren
op_amp
id|reg
comma
(paren
r_int
r_char
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|reg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|parport_write_control
(paren
id|port
comma
id|reg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PPWDATA
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
(paren
op_amp
id|reg
comma
(paren
r_int
r_char
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|reg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|parport_write_data
(paren
id|port
comma
id|reg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PPFCONTROL
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
(paren
op_amp
id|mask
comma
(paren
r_int
r_char
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|mask
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
(paren
op_amp
id|reg
comma
l_int|1
op_plus
(paren
r_int
r_char
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|reg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|parport_frob_control
(paren
id|port
comma
id|mask
comma
id|reg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PPDATADIR
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
(paren
op_amp
id|mode
comma
(paren
r_int
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|mode
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|mode
)paren
id|port-&gt;ops-&gt;data_reverse
(paren
id|port
)paren
suffix:semicolon
r_else
id|port-&gt;ops-&gt;data_forward
(paren
id|port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PPNEGOT
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
(paren
op_amp
id|mode
comma
(paren
r_int
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|mode
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|ret
op_assign
id|parport_negotiate
(paren
id|port
comma
id|mode
)paren
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
op_minus
l_int|1
suffix:colon
multiline_comment|/* handshake failed, peripheral not IEEE 1284 */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* handshake succeeded, peripheral rejected mode */
id|ret
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pp_enable_irq
(paren
id|pp
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
r_case
id|PPWCTLONIRQ
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
(paren
op_amp
id|reg
comma
(paren
r_int
r_char
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|reg
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* Remember what to set the control lines to, for next&n;&t;&t; * time we get an interrupt. */
id|pp-&gt;irqctl
op_assign
id|reg
suffix:semicolon
id|pp-&gt;irqresponse
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PPCLRIRQ
suffix:colon
id|ret
op_assign
id|atomic_read
(paren
op_amp
id|pp-&gt;irqc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
(paren
(paren
r_int
op_star
)paren
id|arg
comma
op_amp
id|ret
comma
r_sizeof
(paren
id|ret
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|atomic_sub
(paren
id|ret
comma
op_amp
id|pp-&gt;irqc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PPSETTIME
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
(paren
op_amp
id|par_timeout
comma
(paren
r_struct
id|timeval
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|timeval
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* Convert to jiffies, place in pp-&gt;pdev-&gt;timeout */
r_if
c_cond
(paren
(paren
id|par_timeout.tv_sec
OL
l_int|0
)paren
op_logical_or
(paren
id|par_timeout.tv_usec
OL
l_int|0
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|to_jiffies
op_assign
id|ROUND_UP
c_func
(paren
id|par_timeout.tv_usec
comma
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
id|to_jiffies
op_add_assign
id|par_timeout.tv_sec
op_star
(paren
r_int
)paren
id|HZ
suffix:semicolon
r_if
c_cond
(paren
id|to_jiffies
op_le
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|pp-&gt;pdev-&gt;timeout
op_assign
id|to_jiffies
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|PPGETTIME
suffix:colon
id|to_jiffies
op_assign
id|pp-&gt;pdev-&gt;timeout
suffix:semicolon
id|par_timeout.tv_sec
op_assign
id|to_jiffies
op_div
id|HZ
suffix:semicolon
id|par_timeout.tv_usec
op_assign
(paren
id|to_jiffies
op_mod
(paren
r_int
)paren
id|HZ
)paren
op_star
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
(paren
(paren
r_struct
id|timeval
op_star
)paren
id|arg
comma
op_amp
id|par_timeout
comma
r_sizeof
(paren
r_struct
id|timeval
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
id|KERN_DEBUG
id|CHRDEV
l_string|&quot;%x: What? (cmd=0x%x)&bslash;n&quot;
comma
id|minor
comma
id|cmd
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Keep the compiler happy */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pp_open
r_static
r_int
id|pp_open
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
r_int
r_int
id|minor
op_assign
id|minor
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|pp_struct
op_star
id|pp
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_ge
id|PARPORT_MAX
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|pp
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|pp_struct
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pp
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|pp-&gt;state.mode
op_assign
id|IEEE1284_MODE_COMPAT
suffix:semicolon
id|pp-&gt;state.phase
op_assign
id|init_phase
(paren
id|pp-&gt;state.mode
)paren
suffix:semicolon
id|pp-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|pp-&gt;irqresponse
op_assign
l_int|0
suffix:semicolon
id|atomic_set
(paren
op_amp
id|pp-&gt;irqc
comma
l_int|0
)paren
suffix:semicolon
id|init_waitqueue_head
(paren
op_amp
id|pp-&gt;irq_wait
)paren
suffix:semicolon
multiline_comment|/* Defer the actual device registration until the first claim.&n;&t; * That way, we know whether or not the driver wants to have&n;&t; * exclusive access to the port (PPEXCL).&n;&t; */
id|pp-&gt;pdev
op_assign
l_int|NULL
suffix:semicolon
id|file-&gt;private_data
op_assign
id|pp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pp_release
r_static
r_int
id|pp_release
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
r_int
r_int
id|minor
op_assign
id|minor
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|pp_struct
op_star
id|pp
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
id|compat_negot
suffix:semicolon
id|compat_negot
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pp-&gt;flags
op_amp
id|PP_CLAIMED
)paren
op_logical_and
id|pp-&gt;pdev
op_logical_and
(paren
id|pp-&gt;state.mode
op_ne
id|IEEE1284_MODE_COMPAT
)paren
)paren
(brace
r_struct
id|ieee1284_info
op_star
id|info
suffix:semicolon
multiline_comment|/* parport released, but not in compatibility mode */
id|parport_claim_or_block
(paren
id|pp-&gt;pdev
)paren
suffix:semicolon
id|pp-&gt;flags
op_or_assign
id|PP_CLAIMED
suffix:semicolon
id|info
op_assign
op_amp
id|pp-&gt;pdev-&gt;port-&gt;ieee1284
suffix:semicolon
id|pp-&gt;saved_state.mode
op_assign
id|info-&gt;mode
suffix:semicolon
id|pp-&gt;saved_state.phase
op_assign
id|info-&gt;phase
suffix:semicolon
id|info-&gt;mode
op_assign
id|pp-&gt;state.mode
suffix:semicolon
id|info-&gt;phase
op_assign
id|pp-&gt;state.phase
suffix:semicolon
id|compat_negot
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|pp-&gt;flags
op_amp
id|PP_CLAIMED
)paren
op_logical_and
id|pp-&gt;pdev
op_logical_and
(paren
id|pp-&gt;pdev-&gt;port-&gt;ieee1284.mode
op_ne
id|IEEE1284_MODE_COMPAT
)paren
)paren
(brace
id|compat_negot
op_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|compat_negot
)paren
(brace
id|parport_negotiate
(paren
id|pp-&gt;pdev-&gt;port
comma
id|IEEE1284_MODE_COMPAT
)paren
suffix:semicolon
id|printk
(paren
id|KERN_DEBUG
id|CHRDEV
l_string|&quot;%x: negotiated back to compatibility mode because &quot;
l_string|&quot;user-space forgot&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pp-&gt;flags
op_amp
id|PP_CLAIMED
)paren
(brace
r_struct
id|ieee1284_info
op_star
id|info
suffix:semicolon
id|info
op_assign
op_amp
id|pp-&gt;pdev-&gt;port-&gt;ieee1284
suffix:semicolon
id|pp-&gt;state.mode
op_assign
id|info-&gt;mode
suffix:semicolon
id|pp-&gt;state.phase
op_assign
id|info-&gt;phase
suffix:semicolon
id|info-&gt;mode
op_assign
id|pp-&gt;saved_state.mode
suffix:semicolon
id|info-&gt;phase
op_assign
id|pp-&gt;saved_state.phase
suffix:semicolon
id|parport_release
(paren
id|pp-&gt;pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|compat_negot
op_ne
l_int|1
)paren
(brace
id|printk
(paren
id|KERN_DEBUG
id|CHRDEV
l_string|&quot;%x: released pardevice &quot;
l_string|&quot;because user-space forgot&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|pp-&gt;pdev
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|pp-&gt;pdev-&gt;name
suffix:semicolon
id|parport_unregister_device
(paren
id|pp-&gt;pdev
)paren
suffix:semicolon
id|kfree
(paren
id|name
)paren
suffix:semicolon
id|pp-&gt;pdev
op_assign
l_int|NULL
suffix:semicolon
id|printk
(paren
id|KERN_DEBUG
id|CHRDEV
l_string|&quot;%x: unregistered pardevice&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
)brace
id|kfree
(paren
id|pp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* No kernel lock held - fine */
DECL|function|pp_poll
r_static
r_int
r_int
id|pp_poll
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
r_struct
id|pp_struct
op_star
id|pp
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
id|poll_wait
(paren
id|file
comma
op_amp
id|pp-&gt;irq_wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
(paren
op_amp
id|pp-&gt;irqc
)paren
)paren
id|mask
op_or_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|variable|pp_fops
r_static
r_struct
id|file_operations
id|pp_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|read
op_assign
id|pp_read
comma
dot
id|write
op_assign
id|pp_write
comma
dot
id|poll
op_assign
id|pp_poll
comma
dot
id|ioctl
op_assign
id|pp_ioctl
comma
dot
id|open
op_assign
id|pp_open
comma
dot
id|release
op_assign
id|pp_release
comma
)brace
suffix:semicolon
DECL|function|ppdev_init
r_static
r_int
id|__init
id|ppdev_init
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|register_chrdev
(paren
id|PP_MAJOR
comma
id|CHRDEV
comma
op_amp
id|pp_fops
)paren
)paren
(brace
id|printk
(paren
id|KERN_WARNING
id|CHRDEV
l_string|&quot;: unable to get major %d&bslash;n&quot;
comma
id|PP_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|devfs_mk_dir
c_func
(paren
l_string|&quot;parports&quot;
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
id|PARPORT_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;parports/%d&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_register
c_func
(paren
l_int|NULL
comma
id|name
comma
id|DEVFS_FL_DEFAULT
comma
id|PP_MAJOR
comma
id|i
comma
id|S_IFCHR
op_or
id|S_IRUGO
op_or
id|S_IWUGO
comma
op_amp
id|pp_fops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
id|PP_VERSION
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ppdev_cleanup
r_static
r_void
id|__exit
id|ppdev_cleanup
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Clean up all parport stuff */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PARPORT_MAX
suffix:semicolon
id|i
op_increment
)paren
id|devfs_remove
c_func
(paren
l_string|&quot;parports/%d&quot;
comma
id|i
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;parports&quot;
)paren
suffix:semicolon
id|unregister_chrdev
(paren
id|PP_MAJOR
comma
id|CHRDEV
)paren
suffix:semicolon
)brace
DECL|variable|ppdev_init
id|module_init
c_func
(paren
id|ppdev_init
)paren
suffix:semicolon
DECL|variable|ppdev_cleanup
id|module_exit
c_func
(paren
id|ppdev_cleanup
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
