multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* i2c-philips-par.c i2c-hw access for philips style parallel port adapters  */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 1995-2000 Simon G. Vogl&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* With some changes from Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt; and even&n;   Frodo Looijaard &lt;frodol@dds.nl&gt; */
multiline_comment|/* $Id: i2c-philips-par.c,v 1.23 2002/02/06 08:50:58 simon Exp $ */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#ifndef __exit
DECL|macro|__exit
mdefine_line|#define __exit __init
macro_line|#endif
DECL|variable|type
r_static
r_int
id|type
suffix:semicolon
DECL|struct|i2c_par
r_struct
id|i2c_par
(brace
DECL|member|pdev
r_struct
id|pardevice
op_star
id|pdev
suffix:semicolon
DECL|member|adapter
r_struct
id|i2c_adapter
id|adapter
suffix:semicolon
DECL|member|bit_lp_data
r_struct
id|i2c_algo_bit_data
id|bit_lp_data
suffix:semicolon
DECL|member|next
r_struct
id|i2c_par
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|adapter_list
r_static
r_struct
id|i2c_par
op_star
id|adapter_list
suffix:semicolon
multiline_comment|/* ----- global defines -----------------------------------------------&t;*/
DECL|macro|DEB
mdefine_line|#define DEB(x)&t;&t;/* should be reasonable open, close &amp;c. &t;*/
DECL|macro|DEB2
mdefine_line|#define DEB2(x) &t;/* low level debugging - very slow &t;&t;*/
DECL|macro|DEBE
mdefine_line|#define DEBE(x)&t;x&t;/* error messages &t;&t;&t;&t;*/
multiline_comment|/* ----- printer port defines ------------------------------------------*/
multiline_comment|/* Pin Port  Inverted&t;name&t;*/
DECL|macro|I2C_ON
mdefine_line|#define I2C_ON&t;&t;0x20&t;&t;/* 12 status N&t;paper&t;&t;*/
multiline_comment|/* ... only for phil. not used  */
DECL|macro|I2C_SDA
mdefine_line|#define I2C_SDA&t;&t;0x80&t;&t;/*  9 data   N&t;data7&t;&t;*/
DECL|macro|I2C_SCL
mdefine_line|#define I2C_SCL&t;&t;0x08&t;&t;/* 17 ctrl   N&t;dsel&t;&t;*/
DECL|macro|I2C_SDAIN
mdefine_line|#define I2C_SDAIN&t;0x80&t;&t;/* 11 stat   Y&t;busy&t;&t;*/
DECL|macro|I2C_SCLIN
mdefine_line|#define I2C_SCLIN&t;0x08&t;&t;/* 15 stat   Y&t;enable&t;&t;*/
DECL|macro|I2C_DMASK
mdefine_line|#define I2C_DMASK&t;0x7f
DECL|macro|I2C_CMASK
mdefine_line|#define I2C_CMASK&t;0xf7
multiline_comment|/* ----- local functions ----------------------------------------------&t;*/
DECL|function|bit_lp_setscl
r_static
r_void
id|bit_lp_setscl
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
multiline_comment|/*be cautious about state of the control register - &n;&t;&t;touch only the one bit needed*/
r_if
c_cond
(paren
id|state
)paren
(brace
id|parport_write_control
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
comma
id|parport_read_control
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
)paren
op_or
id|I2C_SCL
)paren
suffix:semicolon
)brace
r_else
(brace
id|parport_write_control
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
comma
id|parport_read_control
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
)paren
op_amp
id|I2C_CMASK
)paren
suffix:semicolon
)brace
)brace
DECL|function|bit_lp_setsda
r_static
r_void
id|bit_lp_setsda
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
r_if
c_cond
(paren
id|state
)paren
(brace
id|parport_write_data
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
comma
id|I2C_DMASK
)paren
suffix:semicolon
)brace
r_else
(brace
id|parport_write_data
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
comma
id|I2C_SDA
)paren
suffix:semicolon
)brace
)brace
DECL|function|bit_lp_getscl
r_static
r_int
id|bit_lp_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
id|parport_read_status
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
)paren
op_amp
id|I2C_SCLIN
suffix:semicolon
)brace
DECL|function|bit_lp_getsda
r_static
r_int
id|bit_lp_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
id|parport_read_status
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
)paren
op_amp
id|I2C_SDAIN
suffix:semicolon
)brace
DECL|function|bit_lp_setscl2
r_static
r_void
id|bit_lp_setscl2
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
r_if
c_cond
(paren
id|state
)paren
(brace
id|parport_write_data
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
comma
id|parport_read_data
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
)paren
op_or
l_int|0x1
)paren
suffix:semicolon
)brace
r_else
(brace
id|parport_write_data
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
comma
id|parport_read_data
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
)paren
op_amp
l_int|0xfe
)paren
suffix:semicolon
)brace
)brace
DECL|function|bit_lp_setsda2
r_static
r_void
id|bit_lp_setsda2
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
r_if
c_cond
(paren
id|state
)paren
(brace
id|parport_write_data
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
comma
id|parport_read_data
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
)paren
op_or
l_int|0x2
)paren
suffix:semicolon
)brace
r_else
(brace
id|parport_write_data
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
comma
id|parport_read_data
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
)paren
op_amp
l_int|0xfd
)paren
suffix:semicolon
)brace
)brace
DECL|function|bit_lp_getsda2
r_static
r_int
id|bit_lp_getsda2
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
id|parport_read_status
c_func
(paren
(paren
r_struct
id|parport
op_star
)paren
id|data
)paren
op_amp
id|PARPORT_STATUS_BUSY
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|bit_lp_reg
r_static
r_int
id|bit_lp_reg
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bit_lp_unreg
r_static
r_int
id|bit_lp_unreg
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bit_lp_inc_use
r_static
r_void
id|bit_lp_inc_use
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|bit_lp_dec_use
r_static
r_void
id|bit_lp_dec_use
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------------------&n; * Encapsulate the above functions in the correct operations structure.&n; * This is only done when more than one hardware adapter is supported.&n; */
DECL|variable|bit_lp_data
r_static
r_struct
id|i2c_algo_bit_data
id|bit_lp_data
op_assign
(brace
l_int|NULL
comma
id|bit_lp_setsda
comma
id|bit_lp_setscl
comma
id|bit_lp_getsda
comma
id|bit_lp_getscl
comma
l_int|80
comma
l_int|80
comma
l_int|100
comma
multiline_comment|/*&t;waits, timeout */
)brace
suffix:semicolon
DECL|variable|bit_lp_data2
r_static
r_struct
id|i2c_algo_bit_data
id|bit_lp_data2
op_assign
(brace
l_int|NULL
comma
id|bit_lp_setsda2
comma
id|bit_lp_setscl2
comma
id|bit_lp_getsda2
comma
l_int|NULL
comma
l_int|80
comma
l_int|80
comma
l_int|100
comma
multiline_comment|/*&t;waits, timeout */
)brace
suffix:semicolon
DECL|variable|bit_lp_ops
r_static
r_struct
id|i2c_adapter
id|bit_lp_ops
op_assign
(brace
l_string|&quot;Philips Parallel port adapter&quot;
comma
id|I2C_HW_B_LP
comma
l_int|NULL
comma
l_int|NULL
comma
id|bit_lp_inc_use
comma
id|bit_lp_dec_use
comma
id|bit_lp_reg
comma
id|bit_lp_unreg
comma
)brace
suffix:semicolon
DECL|function|i2c_parport_attach
r_static
r_void
id|i2c_parport_attach
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_struct
id|i2c_par
op_star
id|adapter
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|i2c_par
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|adapter
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-philips-par: Unable to malloc.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;i2c-philips-par.o: attaching to %s&bslash;n&quot;
comma
id|port-&gt;name
)paren
suffix:semicolon
id|adapter-&gt;pdev
op_assign
id|parport_register_device
c_func
(paren
id|port
comma
l_string|&quot;i2c-philips-par&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|PARPORT_FLAG_EXCL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|adapter-&gt;pdev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-philips-par: Unable to register with parport.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|adapter-&gt;adapter
op_assign
id|bit_lp_ops
suffix:semicolon
id|adapter-&gt;adapter.algo_data
op_assign
op_amp
id|adapter-&gt;bit_lp_data
suffix:semicolon
id|adapter-&gt;bit_lp_data
op_assign
id|type
ques
c_cond
id|bit_lp_data2
suffix:colon
id|bit_lp_data
suffix:semicolon
id|adapter-&gt;bit_lp_data.data
op_assign
id|port
suffix:semicolon
r_if
c_cond
(paren
id|parport_claim_or_block
c_func
(paren
id|adapter-&gt;pdev
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-philips-par: Could not claim parallel port.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* reset hardware to sane state */
id|bit_lp_setsda
c_func
(paren
id|port
comma
l_int|1
)paren
suffix:semicolon
id|bit_lp_setscl
c_func
(paren
id|port
comma
l_int|1
)paren
suffix:semicolon
id|parport_release
c_func
(paren
id|adapter-&gt;pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|adapter-&gt;adapter
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-philips-par: Unable to register with I2C.&bslash;n&quot;
)paren
suffix:semicolon
id|parport_unregister_device
c_func
(paren
id|adapter-&gt;pdev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|adapter
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* No good */
)brace
id|adapter-&gt;next
op_assign
id|adapter_list
suffix:semicolon
id|adapter_list
op_assign
id|adapter
suffix:semicolon
)brace
DECL|function|i2c_parport_detach
r_static
r_void
id|i2c_parport_detach
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_struct
id|i2c_par
op_star
id|adapter
comma
op_star
id|prev
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|adapter
op_assign
id|adapter_list
suffix:semicolon
id|adapter
suffix:semicolon
id|adapter
op_assign
id|adapter-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|adapter-&gt;pdev-&gt;port
op_eq
id|port
)paren
(brace
id|parport_unregister_device
c_func
(paren
id|adapter-&gt;pdev
)paren
suffix:semicolon
id|i2c_bit_del_bus
c_func
(paren
op_amp
id|adapter-&gt;adapter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prev
)paren
id|prev-&gt;next
op_assign
id|adapter-&gt;next
suffix:semicolon
r_else
id|adapter_list
op_assign
id|adapter-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|adapter
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|prev
op_assign
id|adapter
suffix:semicolon
)brace
)brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,4)
DECL|variable|i2c_driver
r_static
r_struct
id|parport_driver
id|i2c_driver
op_assign
(brace
l_string|&quot;i2c-philips-par&quot;
comma
id|i2c_parport_attach
comma
id|i2c_parport_detach
comma
l_int|NULL
)brace
suffix:semicolon
macro_line|#endif
DECL|function|i2c_bitlp_init
r_int
id|__init
id|i2c_bitlp_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,4)
r_struct
id|parport
op_star
id|port
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c-philips-par.o: i2c Philips parallel port adapter module version %s (%s)&bslash;n&quot;
comma
id|I2C_VERSION
comma
id|I2C_DATE
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,4)
id|parport_register_driver
c_func
(paren
op_amp
id|i2c_driver
)paren
suffix:semicolon
macro_line|#else
r_for
c_loop
(paren
id|port
op_assign
id|parport_enumerate
c_func
(paren
)paren
suffix:semicolon
id|port
suffix:semicolon
id|port
op_assign
id|port-&gt;next
)paren
id|i2c_parport_attach
c_func
(paren
id|port
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2c_bitlp_exit
r_void
id|__exit
id|i2c_bitlp_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,4)
id|parport_unregister_driver
c_func
(paren
op_amp
id|i2c_driver
)paren
suffix:semicolon
macro_line|#else
r_struct
id|parport
op_star
id|port
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
id|parport_enumerate
c_func
(paren
)paren
suffix:semicolon
id|port
suffix:semicolon
id|port
op_assign
id|port-&gt;next
)paren
id|i2c_parport_detach
c_func
(paren
id|port
)paren
suffix:semicolon
macro_line|#endif
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Simon G. Vogl &lt;simon@tk.uni-linz.ac.at&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I2C-Bus adapter routines for Philips parallel port adapter&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|type
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|i2c_bitlp_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|i2c_bitlp_exit
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
