multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;uss720.c  --  USS720 USB Parport Cable.&n; *&n; *&t;Copyright (C) 1999&n; *&t;    Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  Based on parport_pc.c&n; *&n; *  History:&n; *   0.1  04.08.99  Created&n; *   0.2  07.08.99  Some fixes mainly suggested by Tim Waugh&n; *&t;&t;    Interrupt handling currently disabled because&n; *&t;&t;    usb_request_irq crashes somewhere within ohci.c&n; *&t;&t;    for no apparent reason (that is for me, anyway)&n; *&t;&t;    ECP currently untested&n; *   0.3  10.08.99  fixing merge errors&n; *   0.4  13.08.99  Added Vendor/Product ID of Brad Hard&squot;s cable&n; *   0.5  20.09.99  usb_control_msg wrapper used&n; *        Nov01.00  usb_device_table support by Adam J. Richter&n; *        08.04.01  Identify version on module load.  gb&n; *&n; */
multiline_comment|/*****************************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
multiline_comment|/*&n; * Version Information&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v0.5&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Thomas M. Sailer, sailer@ife.ee.ethz.ch&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB Parport Cable driver for Cables using the Lucent Technologies USS720 Chip&quot;
multiline_comment|/* --------------------------------------------------------------------- */
DECL|struct|parport_uss720_private
r_struct
id|parport_uss720_private
(brace
DECL|member|usbdev
r_struct
id|usb_device
op_star
id|usbdev
suffix:semicolon
DECL|member|irqhandle
r_void
op_star
id|irqhandle
suffix:semicolon
DECL|member|irqpipe
r_int
r_int
id|irqpipe
suffix:semicolon
DECL|member|reg
r_int
r_char
id|reg
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* USB registers */
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|get_1284_register
r_static
r_int
id|get_1284_register
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_int
r_char
id|reg
comma
r_int
r_char
op_star
id|val
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_struct
id|usb_device
op_star
id|usbdev
op_assign
id|priv-&gt;usbdev
suffix:semicolon
r_static
r_const
r_int
r_char
id|regindex
(braket
l_int|9
)braket
op_assign
(brace
l_int|4
comma
l_int|0
comma
l_int|1
comma
l_int|5
comma
l_int|5
comma
l_int|0
comma
l_int|2
comma
l_int|3
comma
l_int|6
)brace
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usbdev
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|ret
op_assign
id|usb_control_msg
c_func
(paren
id|usbdev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|usbdev
comma
l_int|0
)paren
comma
l_int|3
comma
l_int|0xc0
comma
(paren
(paren
r_int
r_int
)paren
id|reg
)paren
op_lshift
l_int|8
comma
l_int|0
comma
id|priv-&gt;reg
comma
l_int|7
comma
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|7
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;uss720: get_1284_register(%d) failed, status 0x%x expected 7&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|reg
comma
id|ret
)paren
suffix:semicolon
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;uss720: get_1284_register(%d) return %02x %02x %02x %02x %02x %02x %02x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|reg
comma
(paren
r_int
r_int
)paren
id|priv-&gt;reg
(braket
l_int|0
)braket
comma
(paren
r_int
r_int
)paren
id|priv-&gt;reg
(braket
l_int|1
)braket
comma
(paren
r_int
r_int
)paren
id|priv-&gt;reg
(braket
l_int|2
)braket
comma
(paren
r_int
r_int
)paren
id|priv-&gt;reg
(braket
l_int|3
)braket
comma
(paren
r_int
r_int
)paren
id|priv-&gt;reg
(braket
l_int|4
)braket
comma
(paren
r_int
r_int
)paren
id|priv-&gt;reg
(braket
l_int|5
)braket
comma
(paren
r_int
r_int
)paren
id|priv-&gt;reg
(braket
l_int|6
)braket
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* if nAck interrupts are enabled and we have an interrupt, call the interrupt procedure */
r_if
c_cond
(paren
id|priv-&gt;reg
(braket
l_int|2
)braket
op_amp
id|priv-&gt;reg
(braket
l_int|1
)braket
op_amp
l_int|0x10
)paren
id|parport_generic_irq
c_func
(paren
l_int|0
comma
id|pp
comma
l_int|NULL
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|val
)paren
op_star
id|val
op_assign
id|priv-&gt;reg
(braket
(paren
id|reg
op_ge
l_int|9
)paren
ques
c_cond
l_int|0
suffix:colon
id|regindex
(braket
id|reg
)braket
)braket
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|set_1284_register
r_static
r_int
id|set_1284_register
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|val
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_struct
id|usb_device
op_star
id|usbdev
op_assign
id|priv-&gt;usbdev
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usbdev
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|ret
op_assign
id|usb_control_msg
c_func
(paren
id|usbdev
comma
id|usb_sndctrlpipe
c_func
(paren
id|usbdev
comma
l_int|0
)paren
comma
l_int|4
comma
l_int|0x40
comma
(paren
(paren
(paren
r_int
r_int
)paren
id|reg
)paren
op_lshift
l_int|8
)paren
op_or
id|val
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;uss720: set_1284_register(%u,0x%02x) failed, status 0x%x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|reg
comma
(paren
r_int
r_int
)paren
id|val
comma
id|ret
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;uss720: set_1284_register(%u,0x%02x)&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|reg
comma
(paren
r_int
r_int
)paren
id|val
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/* ECR modes */
DECL|macro|ECR_SPP
mdefine_line|#define ECR_SPP 00
DECL|macro|ECR_PS2
mdefine_line|#define ECR_PS2 01
DECL|macro|ECR_PPF
mdefine_line|#define ECR_PPF 02
DECL|macro|ECR_ECP
mdefine_line|#define ECR_ECP 03
DECL|macro|ECR_EPP
mdefine_line|#define ECR_EPP 04
multiline_comment|/* Safely change the mode bits in the ECR */
DECL|function|change_mode
r_static
r_int
id|change_mode
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_int
id|m
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_int
id|mode
suffix:semicolon
r_if
c_cond
(paren
id|get_1284_register
c_func
(paren
id|pp
comma
l_int|6
comma
l_int|NULL
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* Bits &lt;7:5&gt; contain the mode. */
id|mode
op_assign
(paren
id|priv-&gt;reg
(braket
l_int|2
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|0x7
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
id|m
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* We have to go through mode 000 or 001 */
r_if
c_cond
(paren
id|mode
OG
id|ECR_PS2
op_logical_and
id|m
OG
id|ECR_PS2
)paren
r_if
c_cond
(paren
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_PS2
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|m
op_le
id|ECR_PS2
op_logical_and
op_logical_neg
(paren
id|priv-&gt;reg
(braket
l_int|1
)braket
op_amp
l_int|0x20
)paren
)paren
(brace
multiline_comment|/* This mode resets the FIFO, so we may&n;&t;&t; * have to wait for it to drain first. */
r_int
r_int
id|expire
op_assign
id|jiffies
op_plus
id|pp-&gt;physport-&gt;cad-&gt;timeout
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|ECR_PPF
suffix:colon
multiline_comment|/* Parallel Port FIFO mode */
r_case
id|ECR_ECP
suffix:colon
multiline_comment|/* ECP Parallel Port mode */
multiline_comment|/* Poll slowly. */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|get_1284_register
c_func
(paren
id|pp
comma
l_int|6
comma
l_int|NULL
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;reg
(braket
l_int|2
)braket
op_amp
l_int|0x01
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|time_after_eq
(paren
id|jiffies
comma
id|expire
)paren
)paren
multiline_comment|/* The FIFO is stuck. */
r_return
op_minus
id|EBUSY
suffix:semicolon
id|msleep_interruptible
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
(paren
id|current
)paren
)paren
r_break
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Set the mode. */
r_if
c_cond
(paren
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|6
comma
id|m
op_lshift
l_int|5
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear TIMEOUT BIT in EPP MODE&n; */
DECL|function|clear_epp_timeout
r_static
r_int
id|clear_epp_timeout
c_func
(paren
r_struct
id|parport
op_star
id|pp
)paren
(brace
r_int
r_char
id|stat
suffix:semicolon
r_if
c_cond
(paren
id|get_1284_register
c_func
(paren
id|pp
comma
l_int|1
comma
op_amp
id|stat
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|stat
op_amp
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Access functions.&n; */
macro_line|#if 0
r_static
r_int
id|uss720_irq
c_func
(paren
r_int
id|usbstatus
comma
r_void
op_star
id|buffer
comma
r_int
id|len
comma
r_void
op_star
id|dev_id
)paren
(brace
r_struct
id|parport
op_star
id|pp
op_assign
(paren
r_struct
id|parport
op_star
)paren
id|dev_id
suffix:semicolon
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|usbstatus
op_ne
l_int|0
op_logical_or
id|len
OL
l_int|4
op_logical_or
op_logical_neg
id|buffer
)paren
r_return
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|priv-&gt;reg
comma
id|buffer
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* if nAck interrupts are enabled and we have an interrupt, call the interrupt procedure */
r_if
c_cond
(paren
id|priv-&gt;reg
(braket
l_int|2
)braket
op_amp
id|priv-&gt;reg
(braket
l_int|1
)braket
op_amp
l_int|0x10
)paren
id|parport_generic_irq
c_func
(paren
l_int|0
comma
id|pp
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
DECL|function|parport_uss720_write_data
r_static
r_void
id|parport_uss720_write_data
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_int
r_char
id|d
)paren
(brace
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|0
comma
id|d
)paren
suffix:semicolon
)brace
DECL|function|parport_uss720_read_data
r_static
r_int
r_char
id|parport_uss720_read_data
c_func
(paren
r_struct
id|parport
op_star
id|pp
)paren
(brace
r_int
r_char
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|get_1284_register
c_func
(paren
id|pp
comma
l_int|0
comma
op_amp
id|ret
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|parport_uss720_write_control
r_static
r_void
id|parport_uss720_write_control
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_int
r_char
id|d
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
id|d
op_assign
(paren
id|d
op_amp
l_int|0xf
)paren
op_or
(paren
id|priv-&gt;reg
(braket
l_int|1
)braket
op_amp
l_int|0xf0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|2
comma
id|d
)paren
)paren
r_return
suffix:semicolon
id|priv-&gt;reg
(braket
l_int|1
)braket
op_assign
id|d
suffix:semicolon
)brace
DECL|function|parport_uss720_read_control
r_static
r_int
r_char
id|parport_uss720_read_control
c_func
(paren
r_struct
id|parport
op_star
id|pp
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_return
id|priv-&gt;reg
(braket
l_int|1
)braket
op_amp
l_int|0xf
suffix:semicolon
multiline_comment|/* Use soft copy */
)brace
DECL|function|parport_uss720_frob_control
r_static
r_int
r_char
id|parport_uss720_frob_control
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_int
r_char
id|mask
comma
r_int
r_char
id|val
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_int
r_char
id|d
suffix:semicolon
id|mask
op_and_assign
l_int|0x0f
suffix:semicolon
id|val
op_and_assign
l_int|0x0f
suffix:semicolon
id|d
op_assign
(paren
id|priv-&gt;reg
(braket
l_int|1
)braket
op_amp
(paren
op_complement
id|mask
)paren
)paren
op_xor
id|val
suffix:semicolon
r_if
c_cond
(paren
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|2
comma
id|d
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|priv-&gt;reg
(braket
l_int|1
)braket
op_assign
id|d
suffix:semicolon
r_return
id|d
op_amp
l_int|0xf
suffix:semicolon
)brace
DECL|function|parport_uss720_read_status
r_static
r_int
r_char
id|parport_uss720_read_status
c_func
(paren
r_struct
id|parport
op_star
id|pp
)paren
(brace
r_int
r_char
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|get_1284_register
c_func
(paren
id|pp
comma
l_int|1
comma
op_amp
id|ret
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|ret
op_amp
l_int|0xf8
suffix:semicolon
)brace
DECL|function|parport_uss720_disable_irq
r_static
r_void
id|parport_uss720_disable_irq
c_func
(paren
r_struct
id|parport
op_star
id|pp
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_int
r_char
id|d
suffix:semicolon
id|d
op_assign
id|priv-&gt;reg
(braket
l_int|1
)braket
op_amp
op_complement
l_int|0x10
suffix:semicolon
r_if
c_cond
(paren
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|2
comma
id|d
)paren
)paren
r_return
suffix:semicolon
id|priv-&gt;reg
(braket
l_int|1
)braket
op_assign
id|d
suffix:semicolon
)brace
DECL|function|parport_uss720_enable_irq
r_static
r_void
id|parport_uss720_enable_irq
c_func
(paren
r_struct
id|parport
op_star
id|pp
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_int
r_char
id|d
suffix:semicolon
id|d
op_assign
id|priv-&gt;reg
(braket
l_int|1
)braket
op_or
l_int|0x10
suffix:semicolon
r_if
c_cond
(paren
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|2
comma
id|d
)paren
)paren
r_return
suffix:semicolon
id|priv-&gt;reg
(braket
l_int|1
)braket
op_assign
id|d
suffix:semicolon
)brace
DECL|function|parport_uss720_data_forward
r_static
r_void
id|parport_uss720_data_forward
(paren
r_struct
id|parport
op_star
id|pp
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_int
r_char
id|d
suffix:semicolon
id|d
op_assign
id|priv-&gt;reg
(braket
l_int|1
)braket
op_amp
op_complement
l_int|0x20
suffix:semicolon
r_if
c_cond
(paren
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|2
comma
id|d
)paren
)paren
r_return
suffix:semicolon
id|priv-&gt;reg
(braket
l_int|1
)braket
op_assign
id|d
suffix:semicolon
)brace
DECL|function|parport_uss720_data_reverse
r_static
r_void
id|parport_uss720_data_reverse
(paren
r_struct
id|parport
op_star
id|pp
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_int
r_char
id|d
suffix:semicolon
id|d
op_assign
id|priv-&gt;reg
(braket
l_int|1
)braket
op_or
l_int|0x20
suffix:semicolon
r_if
c_cond
(paren
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|2
comma
id|d
)paren
)paren
r_return
suffix:semicolon
id|priv-&gt;reg
(braket
l_int|1
)braket
op_assign
id|d
suffix:semicolon
)brace
DECL|function|parport_uss720_init_state
r_static
r_void
id|parport_uss720_init_state
c_func
(paren
r_struct
id|pardevice
op_star
id|dev
comma
r_struct
id|parport_state
op_star
id|s
)paren
(brace
id|s-&gt;u.pc.ctr
op_assign
l_int|0xc
op_or
(paren
id|dev-&gt;irq_func
ques
c_cond
l_int|0x10
suffix:colon
l_int|0x0
)paren
suffix:semicolon
id|s-&gt;u.pc.ecr
op_assign
l_int|0x24
suffix:semicolon
)brace
DECL|function|parport_uss720_save_state
r_static
r_void
id|parport_uss720_save_state
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_struct
id|parport_state
op_star
id|s
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|get_1284_register
c_func
(paren
id|pp
comma
l_int|2
comma
l_int|NULL
)paren
)paren
r_return
suffix:semicolon
id|s-&gt;u.pc.ctr
op_assign
id|priv-&gt;reg
(braket
l_int|1
)braket
suffix:semicolon
id|s-&gt;u.pc.ecr
op_assign
id|priv-&gt;reg
(braket
l_int|2
)braket
suffix:semicolon
)brace
DECL|function|parport_uss720_restore_state
r_static
r_void
id|parport_uss720_restore_state
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_struct
id|parport_state
op_star
id|s
)paren
(brace
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|2
comma
id|s-&gt;u.pc.ctr
)paren
suffix:semicolon
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|6
comma
id|s-&gt;u.pc.ecr
)paren
suffix:semicolon
id|get_1284_register
c_func
(paren
id|pp
comma
l_int|2
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|parport_uss720_epp_read_data
r_static
r_int
id|parport_uss720_epp_read_data
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_void
op_star
id|buf
comma
r_int
id|length
comma
r_int
id|flags
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_int
id|got
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_EPP
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|got
OL
id|length
suffix:semicolon
id|got
op_increment
)paren
(brace
r_if
c_cond
(paren
id|get_1284_register
c_func
(paren
id|pp
comma
l_int|4
comma
(paren
r_char
op_star
)paren
id|buf
)paren
)paren
r_break
suffix:semicolon
id|buf
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;reg
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
(brace
id|clear_epp_timeout
c_func
(paren
id|pp
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_PS2
)paren
suffix:semicolon
r_return
id|got
suffix:semicolon
)brace
DECL|function|parport_uss720_epp_write_data
r_static
r_int
id|parport_uss720_epp_write_data
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|length
comma
r_int
id|flags
)paren
(brace
macro_line|#if 0
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_int
id|written
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_EPP
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|written
OL
id|length
suffix:semicolon
id|written
op_increment
)paren
(brace
r_if
c_cond
(paren
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|4
comma
(paren
r_char
op_star
)paren
id|buf
)paren
)paren
r_break
suffix:semicolon
(paren
(paren
r_char
op_star
)paren
id|buf
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|get_1284_register
c_func
(paren
id|pp
comma
l_int|1
comma
l_int|NULL
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;reg
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
(brace
id|clear_epp_timeout
c_func
(paren
id|pp
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_PS2
)paren
suffix:semicolon
r_return
id|written
suffix:semicolon
macro_line|#else
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_struct
id|usb_device
op_star
id|usbdev
op_assign
id|priv-&gt;usbdev
suffix:semicolon
r_int
id|rlen
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usbdev
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_EPP
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_assign
id|usb_bulk_msg
c_func
(paren
id|usbdev
comma
id|usb_sndbulkpipe
c_func
(paren
id|usbdev
comma
l_int|1
)paren
comma
(paren
r_void
op_star
)paren
id|buf
comma
id|length
comma
op_amp
id|rlen
comma
id|HZ
op_star
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;uss720: sendbulk ep 1 buf %p len %Zu rlen %u&bslash;n&quot;
comma
id|buf
comma
id|length
comma
id|rlen
)paren
suffix:semicolon
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_PS2
)paren
suffix:semicolon
r_return
id|rlen
suffix:semicolon
macro_line|#endif
)brace
DECL|function|parport_uss720_epp_read_addr
r_static
r_int
id|parport_uss720_epp_read_addr
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_void
op_star
id|buf
comma
r_int
id|length
comma
r_int
id|flags
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_int
id|got
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_EPP
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|got
OL
id|length
suffix:semicolon
id|got
op_increment
)paren
(brace
r_if
c_cond
(paren
id|get_1284_register
c_func
(paren
id|pp
comma
l_int|3
comma
(paren
r_char
op_star
)paren
id|buf
)paren
)paren
r_break
suffix:semicolon
id|buf
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;reg
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
(brace
id|clear_epp_timeout
c_func
(paren
id|pp
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_PS2
)paren
suffix:semicolon
r_return
id|got
suffix:semicolon
)brace
DECL|function|parport_uss720_epp_write_addr
r_static
r_int
id|parport_uss720_epp_write_addr
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|length
comma
r_int
id|flags
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_int
id|written
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_EPP
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|written
OL
id|length
suffix:semicolon
id|written
op_increment
)paren
(brace
r_if
c_cond
(paren
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|3
comma
op_star
(paren
r_char
op_star
)paren
id|buf
)paren
)paren
r_break
suffix:semicolon
id|buf
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|get_1284_register
c_func
(paren
id|pp
comma
l_int|1
comma
l_int|NULL
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;reg
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
(brace
id|clear_epp_timeout
c_func
(paren
id|pp
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_PS2
)paren
suffix:semicolon
r_return
id|written
suffix:semicolon
)brace
DECL|function|parport_uss720_ecp_write_data
r_static
r_int
id|parport_uss720_ecp_write_data
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_const
r_void
op_star
id|buffer
comma
r_int
id|len
comma
r_int
id|flags
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_struct
id|usb_device
op_star
id|usbdev
op_assign
id|priv-&gt;usbdev
suffix:semicolon
r_int
id|rlen
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usbdev
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_ECP
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_assign
id|usb_bulk_msg
c_func
(paren
id|usbdev
comma
id|usb_sndbulkpipe
c_func
(paren
id|usbdev
comma
l_int|1
)paren
comma
(paren
r_void
op_star
)paren
id|buffer
comma
id|len
comma
op_amp
id|rlen
comma
id|HZ
op_star
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;uss720: sendbulk ep 1 buf %p len %Zu rlen %u&bslash;n&quot;
comma
id|buffer
comma
id|len
comma
id|rlen
)paren
suffix:semicolon
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_PS2
)paren
suffix:semicolon
r_return
id|rlen
suffix:semicolon
)brace
DECL|function|parport_uss720_ecp_read_data
r_static
r_int
id|parport_uss720_ecp_read_data
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_void
op_star
id|buffer
comma
r_int
id|len
comma
r_int
id|flags
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_struct
id|usb_device
op_star
id|usbdev
op_assign
id|priv-&gt;usbdev
suffix:semicolon
r_int
id|rlen
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usbdev
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_ECP
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_assign
id|usb_bulk_msg
c_func
(paren
id|usbdev
comma
id|usb_rcvbulkpipe
c_func
(paren
id|usbdev
comma
l_int|2
)paren
comma
id|buffer
comma
id|len
comma
op_amp
id|rlen
comma
id|HZ
op_star
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;uss720: recvbulk ep 2 buf %p len %Zu rlen %u&bslash;n&quot;
comma
id|buffer
comma
id|len
comma
id|rlen
)paren
suffix:semicolon
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_PS2
)paren
suffix:semicolon
r_return
id|rlen
suffix:semicolon
)brace
DECL|function|parport_uss720_ecp_write_addr
r_static
r_int
id|parport_uss720_ecp_write_addr
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_const
r_void
op_star
id|buffer
comma
r_int
id|len
comma
r_int
id|flags
)paren
(brace
r_int
id|written
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_ECP
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|written
OL
id|len
suffix:semicolon
id|written
op_increment
)paren
(brace
r_if
c_cond
(paren
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|5
comma
op_star
(paren
r_char
op_star
)paren
id|buffer
)paren
)paren
r_break
suffix:semicolon
id|buffer
op_increment
suffix:semicolon
)brace
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_PS2
)paren
suffix:semicolon
r_return
id|written
suffix:semicolon
)brace
DECL|function|parport_uss720_write_compat
r_static
r_int
id|parport_uss720_write_compat
c_func
(paren
r_struct
id|parport
op_star
id|pp
comma
r_const
r_void
op_star
id|buffer
comma
r_int
id|len
comma
r_int
id|flags
)paren
(brace
r_struct
id|parport_uss720_private
op_star
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
r_struct
id|usb_device
op_star
id|usbdev
op_assign
id|priv-&gt;usbdev
suffix:semicolon
r_int
id|rlen
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usbdev
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_PPF
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_assign
id|usb_bulk_msg
c_func
(paren
id|usbdev
comma
id|usb_sndbulkpipe
c_func
(paren
id|usbdev
comma
l_int|1
)paren
comma
(paren
r_void
op_star
)paren
id|buffer
comma
id|len
comma
op_amp
id|rlen
comma
id|HZ
op_star
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;uss720: sendbulk ep 1 buf %p len %Zu rlen %u&bslash;n&quot;
comma
id|buffer
comma
id|len
comma
id|rlen
)paren
suffix:semicolon
id|change_mode
c_func
(paren
id|pp
comma
id|ECR_PS2
)paren
suffix:semicolon
r_return
id|rlen
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|parport_uss720_ops
r_static
r_struct
id|parport_operations
id|parport_uss720_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|write_data
op_assign
id|parport_uss720_write_data
comma
dot
id|read_data
op_assign
id|parport_uss720_read_data
comma
dot
id|write_control
op_assign
id|parport_uss720_write_control
comma
dot
id|read_control
op_assign
id|parport_uss720_read_control
comma
dot
id|frob_control
op_assign
id|parport_uss720_frob_control
comma
dot
id|read_status
op_assign
id|parport_uss720_read_status
comma
dot
id|enable_irq
op_assign
id|parport_uss720_enable_irq
comma
dot
id|disable_irq
op_assign
id|parport_uss720_disable_irq
comma
dot
id|data_forward
op_assign
id|parport_uss720_data_forward
comma
dot
id|data_reverse
op_assign
id|parport_uss720_data_reverse
comma
dot
id|init_state
op_assign
id|parport_uss720_init_state
comma
dot
id|save_state
op_assign
id|parport_uss720_save_state
comma
dot
id|restore_state
op_assign
id|parport_uss720_restore_state
comma
dot
id|epp_write_data
op_assign
id|parport_uss720_epp_write_data
comma
dot
id|epp_read_data
op_assign
id|parport_uss720_epp_read_data
comma
dot
id|epp_write_addr
op_assign
id|parport_uss720_epp_write_addr
comma
dot
id|epp_read_addr
op_assign
id|parport_uss720_epp_read_addr
comma
dot
id|ecp_write_data
op_assign
id|parport_uss720_ecp_write_data
comma
dot
id|ecp_read_data
op_assign
id|parport_uss720_ecp_read_data
comma
dot
id|ecp_write_addr
op_assign
id|parport_uss720_ecp_write_addr
comma
dot
id|compat_write_data
op_assign
id|parport_uss720_write_compat
comma
dot
id|nibble_read_data
op_assign
id|parport_ieee1284_read_nibble
comma
dot
id|byte_read_data
op_assign
id|parport_ieee1284_read_byte
comma
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|uss720_probe
r_static
r_int
id|uss720_probe
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
(brace
r_struct
id|usb_device
op_star
id|usbdev
op_assign
id|interface_to_usbdev
c_func
(paren
id|intf
)paren
suffix:semicolon
r_struct
id|usb_host_interface
op_star
id|interface
suffix:semicolon
r_struct
id|usb_host_endpoint
op_star
id|endpoint
suffix:semicolon
r_struct
id|parport_uss720_private
op_star
id|priv
suffix:semicolon
r_struct
id|parport
op_star
id|pp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;uss720: probe: vendor id 0x%x, device id 0x%x&bslash;n&quot;
comma
id|usbdev-&gt;descriptor.idVendor
comma
id|usbdev-&gt;descriptor.idProduct
)paren
suffix:semicolon
multiline_comment|/* our known interfaces have 3 alternate settings */
r_if
c_cond
(paren
id|intf-&gt;num_altsetting
op_ne
l_int|3
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|i
op_assign
id|usb_set_interface
c_func
(paren
id|usbdev
comma
id|intf-&gt;altsetting-&gt;desc.bInterfaceNumber
comma
l_int|2
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;uss720: set inteface result %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|interface
op_assign
id|intf-&gt;cur_altsetting
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate parport interface &n;&t; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;uss720: (C) 1999 by Thomas Sailer, &lt;sailer@ife.ee.ethz.ch&gt;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|parport_uss720_private
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pp
op_assign
id|parport_register_port
c_func
(paren
l_int|0
comma
id|PARPORT_IRQ_NONE
comma
id|PARPORT_DMA_NONE
comma
op_amp
id|parport_uss720_ops
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;usb-uss720: could not register parport&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|probe_abort
suffix:semicolon
)brace
id|pp-&gt;private_data
op_assign
id|priv
suffix:semicolon
id|priv-&gt;usbdev
op_assign
id|usbdev
suffix:semicolon
id|pp-&gt;modes
op_assign
id|PARPORT_MODE_PCSPP
op_or
id|PARPORT_MODE_TRISTATE
op_or
id|PARPORT_MODE_EPP
op_or
id|PARPORT_MODE_ECP
op_or
id|PARPORT_MODE_COMPAT
suffix:semicolon
multiline_comment|/* set the USS720 control register to manual mode, no ECP compression, enable all ints */
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|7
comma
l_int|0x00
)paren
suffix:semicolon
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|6
comma
l_int|0x30
)paren
suffix:semicolon
multiline_comment|/* PS/2 mode */
id|set_1284_register
c_func
(paren
id|pp
comma
l_int|2
comma
l_int|0x0c
)paren
suffix:semicolon
multiline_comment|/* debugging */
id|get_1284_register
c_func
(paren
id|pp
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;uss720: reg: %02x %02x %02x %02x %02x %02x %02x&bslash;n&quot;
comma
id|priv-&gt;reg
(braket
l_int|0
)braket
comma
id|priv-&gt;reg
(braket
l_int|1
)braket
comma
id|priv-&gt;reg
(braket
l_int|2
)braket
comma
id|priv-&gt;reg
(braket
l_int|3
)braket
comma
id|priv-&gt;reg
(braket
l_int|4
)braket
comma
id|priv-&gt;reg
(braket
l_int|5
)braket
comma
id|priv-&gt;reg
(braket
l_int|6
)braket
)paren
suffix:semicolon
id|endpoint
op_assign
op_amp
id|interface-&gt;endpoint
(braket
l_int|2
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;uss720: epaddr %d interval %d&bslash;n&quot;
comma
id|endpoint-&gt;desc.bEndpointAddress
comma
id|endpoint-&gt;desc.bInterval
)paren
suffix:semicolon
macro_line|#if 0
id|priv-&gt;irqpipe
op_assign
id|usb_rcvctrlpipe
c_func
(paren
id|usbdev
comma
id|endpoint-&gt;bEndpointAddress
)paren
suffix:semicolon
id|i
op_assign
id|usb_request_irq
c_func
(paren
id|usbdev
comma
id|priv-&gt;irqpipe
comma
id|uss720_irq
comma
id|endpoint-&gt;bInterval
comma
id|pp
comma
op_amp
id|priv-&gt;irqhandle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;usb-uss720: usb_request_irq failed (0x%x)&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_goto
id|probe_abort_port
suffix:semicolon
)brace
macro_line|#endif
id|parport_announce_port
c_func
(paren
id|pp
)paren
suffix:semicolon
id|usb_set_intfdata
(paren
id|intf
comma
id|pp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#if 0
id|probe_abort_port
suffix:colon
id|parport_put_port
c_func
(paren
id|pp
)paren
suffix:semicolon
macro_line|#endif
id|probe_abort
suffix:colon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|uss720_disconnect
r_static
r_void
id|uss720_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
r_struct
id|parport
op_star
id|pp
op_assign
id|usb_get_intfdata
(paren
id|intf
)paren
suffix:semicolon
r_struct
id|parport_uss720_private
op_star
id|priv
suffix:semicolon
id|usb_set_intfdata
(paren
id|intf
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pp
)paren
(brace
id|priv
op_assign
id|pp-&gt;private_data
suffix:semicolon
id|parport_remove_port
c_func
(paren
id|pp
)paren
suffix:semicolon
macro_line|#if 0
id|usb_release_irq
c_func
(paren
id|usbdev
comma
id|priv-&gt;irqhandle
comma
id|priv-&gt;irqpipe
)paren
suffix:semicolon
macro_line|#endif
id|priv-&gt;usbdev
op_assign
l_int|NULL
suffix:semicolon
id|parport_put_port
c_func
(paren
id|pp
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* table of cables that work through this driver */
DECL|variable|uss720_table
r_static
r_struct
id|usb_device_id
id|uss720_table
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x047e
comma
l_int|0x1001
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0557
comma
l_int|0x2001
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0729
comma
l_int|0x1284
)paren
)brace
comma
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x1293
comma
l_int|0x0002
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|uss720_table
)paren
suffix:semicolon
DECL|variable|uss720_driver
r_static
r_struct
id|usb_driver
id|uss720_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;uss720&quot;
comma
dot
id|probe
op_assign
id|uss720_probe
comma
dot
id|disconnect
op_assign
id|uss720_disconnect
comma
dot
id|id_table
op_assign
id|uss720_table
comma
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|uss720_init
r_static
r_int
id|__init
id|uss720_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|usb_register
c_func
(paren
op_amp
id|uss720_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|out
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_VERSION
l_string|&quot;:&quot;
id|DRIVER_DESC
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|uss720_cleanup
r_static
r_void
id|__exit
id|uss720_cleanup
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|uss720_driver
)paren
suffix:semicolon
)brace
DECL|variable|uss720_init
id|module_init
c_func
(paren
id|uss720_init
)paren
suffix:semicolon
DECL|variable|uss720_cleanup
id|module_exit
c_func
(paren
id|uss720_cleanup
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
eof
