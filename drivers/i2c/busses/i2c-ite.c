multiline_comment|/*&n;   -------------------------------------------------------------------------&n;   i2c-adap-ite.c i2c-hw access for the IIC peripheral on the ITE MIPS system&n;   -------------------------------------------------------------------------&n;   Hai-Pao Fan, MontaVista Software, Inc.&n;   hpfan@mvista.com or source@mvista.com&n;&n;   Copyright 2001 MontaVista Software Inc.&n;&n;   ----------------------------------------------------------------------------&n;   This file was highly leveraged from i2c-elektor.c, which was created&n;   by Simon G. Vogl and Hans Berglund:&n;&n; &n;     Copyright (C) 1995-97 Simon G. Vogl&n;                   1998-99 Hans Berglund&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* With some changes from Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt; and even&n;   Frodo Looijaard &lt;frodol@dds.nl&gt; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-ite.h&gt;
macro_line|#include &lt;linux/i2c-adap-ite.h&gt;
macro_line|#include &quot;../i2c-ite.h&quot;
DECL|macro|DEFAULT_BASE
mdefine_line|#define DEFAULT_BASE  0x14014030
DECL|macro|ITE_IIC_IO_SIZE
mdefine_line|#define ITE_IIC_IO_SIZE&t;0x40
DECL|macro|DEFAULT_IRQ
mdefine_line|#define DEFAULT_IRQ   0
DECL|macro|DEFAULT_CLOCK
mdefine_line|#define DEFAULT_CLOCK 0x1b0e&t;/* default 16MHz/(27+14) = 400KHz */
DECL|macro|DEFAULT_OWN
mdefine_line|#define DEFAULT_OWN   0x55
DECL|variable|base
r_static
r_int
id|base
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
suffix:semicolon
DECL|variable|clock
r_static
r_int
id|clock
suffix:semicolon
DECL|variable|own
r_static
r_int
id|own
suffix:semicolon
DECL|variable|gpi
r_static
r_struct
id|iic_ite
id|gpi
suffix:semicolon
DECL|variable|iic_wait
r_static
id|wait_queue_head_t
id|iic_wait
suffix:semicolon
DECL|variable|iic_pending
r_static
r_int
id|iic_pending
suffix:semicolon
DECL|variable|lock
r_static
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* ----- local functions ----------------------------------------------&t;*/
DECL|function|iic_ite_setiic
r_static
r_void
id|iic_ite_setiic
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|ctl
comma
r_int
id|val
)paren
(brace
r_int
r_int
id|j
op_assign
id|jiffies
op_plus
l_int|10
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot; Write 0x%02x to 0x%x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|val
comma
id|ctl
op_amp
l_int|0xff
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
r_while
c_loop
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|j
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|outw
c_func
(paren
id|val
comma
id|ctl
)paren
suffix:semicolon
)brace
DECL|function|iic_ite_getiic
r_static
r_int
id|iic_ite_getiic
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|ctl
)paren
(brace
r_int
id|val
suffix:semicolon
id|val
op_assign
id|inw
c_func
(paren
id|ctl
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;Read 0x%02x from 0x%x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|val
comma
id|ctl
op_amp
l_int|0xff
)paren
suffix:semicolon
r_return
(paren
id|val
)paren
suffix:semicolon
)brace
multiline_comment|/* Return our slave address.  This is the address&n; * put on the I2C bus when another master on the bus wants to address us&n; * as a slave&n; */
DECL|function|iic_ite_getown
r_static
r_int
id|iic_ite_getown
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
id|gpi.iic_own
)paren
suffix:semicolon
)brace
DECL|function|iic_ite_getclock
r_static
r_int
id|iic_ite_getclock
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
id|gpi.iic_clock
)paren
suffix:semicolon
)brace
multiline_comment|/* Put this process to sleep.  We will wake up when the&n; * IIC controller interrupts.&n; */
DECL|function|iic_ite_waitforpin
r_static
r_void
id|iic_ite_waitforpin
c_func
(paren
r_void
)paren
(brace
id|DEFINE_WAIT
c_func
(paren
id|wait
)paren
suffix:semicolon
r_int
id|timeout
op_assign
l_int|2
suffix:semicolon
r_int
id|flags
suffix:semicolon
multiline_comment|/* If interrupts are enabled (which they are), then put the process to&n;    * sleep.  This process will be awakened by two events -- either the&n;    * the IIC peripheral interrupts or the timeout expires. &n;    * If interrupts are not enabled then delay for a reasonable amount &n;    * of time and return.&n;    */
r_if
c_cond
(paren
id|gpi.iic_irq
OG
l_int|0
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iic_pending
op_eq
l_int|0
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
id|prepare_to_wait
c_func
(paren
op_amp
id|iic_wait
comma
op_amp
id|wait
comma
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|schedule_timeout
c_func
(paren
id|timeout
op_star
id|HZ
)paren
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iic_pending
op_eq
l_int|1
)paren
(brace
id|iic_pending
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
)brace
id|finish_wait
c_func
(paren
op_amp
id|iic_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
r_else
(brace
id|iic_pending
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
)brace
)brace
DECL|function|iic_ite_handler
r_static
id|irqreturn_t
id|iic_ite_handler
c_func
(paren
r_int
id|this_irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
id|iic_pending
op_assign
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|iic_wait
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/* Lock the region of memory where I/O registers exist.  Request our&n; * interrupt line and register its associated handler.&n; */
DECL|function|iic_hw_resrc_init
r_static
r_int
id|iic_hw_resrc_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|gpi.iic_base
comma
id|ITE_IIC_IO_SIZE
comma
l_string|&quot;i2c&quot;
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|gpi.iic_irq
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|gpi.iic_irq
comma
id|iic_ite_handler
comma
l_int|0
comma
l_string|&quot;ITE IIC&quot;
comma
l_int|0
)paren
OL
l_int|0
)paren
id|gpi.iic_irq
op_assign
l_int|0
suffix:semicolon
r_else
id|enable_irq
c_func
(paren
id|gpi.iic_irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|iic_ite_release
r_static
r_void
id|iic_ite_release
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|gpi.iic_irq
OG
l_int|0
)paren
(brace
id|disable_irq
c_func
(paren
id|gpi.iic_irq
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|gpi.iic_irq
comma
l_int|0
)paren
suffix:semicolon
)brace
id|release_region
c_func
(paren
id|gpi.iic_base
comma
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------------------&n; * Encapsulate the above functions in the correct operations structure.&n; * This is only done when more than one hardware adapter is supported.&n; */
DECL|variable|iic_ite_data
r_static
r_struct
id|i2c_algo_iic_data
id|iic_ite_data
op_assign
(brace
l_int|NULL
comma
id|iic_ite_setiic
comma
id|iic_ite_getiic
comma
id|iic_ite_getown
comma
id|iic_ite_getclock
comma
id|iic_ite_waitforpin
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
DECL|variable|iic_ite_ops
r_static
r_struct
id|i2c_adapter
id|iic_ite_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|id
op_assign
id|I2C_HW_I_IIC
comma
dot
id|algo_data
op_assign
op_amp
id|iic_ite_data
comma
dot
id|dev
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ITE IIC adapter&quot;
comma
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* Called when the module is loaded.  This function starts the&n; * cascade of calls up through the hierarchy of i2c modules (i.e. up to the&n; *  algorithm layer and into to the core layer)&n; */
DECL|function|iic_ite_init
r_static
r_int
id|__init
id|iic_ite_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|iic_ite
op_star
id|piic
op_assign
op_amp
id|gpi
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Initialize ITE IIC adapter module&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
op_eq
l_int|0
)paren
id|piic-&gt;iic_base
op_assign
id|DEFAULT_BASE
suffix:semicolon
r_else
id|piic-&gt;iic_base
op_assign
id|base
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
l_int|0
)paren
id|piic-&gt;iic_irq
op_assign
id|DEFAULT_IRQ
suffix:semicolon
r_else
id|piic-&gt;iic_irq
op_assign
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|clock
op_eq
l_int|0
)paren
id|piic-&gt;iic_clock
op_assign
id|DEFAULT_CLOCK
suffix:semicolon
r_else
id|piic-&gt;iic_clock
op_assign
id|clock
suffix:semicolon
r_if
c_cond
(paren
id|own
op_eq
l_int|0
)paren
id|piic-&gt;iic_own
op_assign
id|DEFAULT_OWN
suffix:semicolon
r_else
id|piic-&gt;iic_own
op_assign
id|own
suffix:semicolon
id|iic_ite_data.data
op_assign
(paren
r_void
op_star
)paren
id|piic
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|iic_wait
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iic_hw_resrc_init
c_func
(paren
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|i2c_iic_add_bus
c_func
(paren
op_amp
id|iic_ite_ops
)paren
OL
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; found device at %#x irq %d.&bslash;n&quot;
comma
id|piic-&gt;iic_base
comma
id|piic-&gt;iic_irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|iic_ite_exit
r_static
r_void
id|iic_ite_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_iic_del_bus
c_func
(paren
op_amp
id|iic_ite_ops
)paren
suffix:semicolon
id|iic_ite_release
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* If modules is NOT defined when this file is compiled, then the MODULE_*&n; * macros will resolve to nothing&n; */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;MontaVista Software &lt;www.mvista.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I2C-Bus adapter routines for ITE IIC bus adapter&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|base
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|irq
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|clock
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|own
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Called when module is loaded or when kernel is initialized.&n; * If MODULES is defined when this file is compiled, then this function will&n; * resolve to init_module (the function called when insmod is invoked for a&n; * module).  Otherwise, this function is called early in the boot, when the&n; * kernel is intialized.  Check out /include/init.h to see how this works.&n; */
DECL|variable|iic_ite_init
id|module_init
c_func
(paren
id|iic_ite_init
)paren
suffix:semicolon
multiline_comment|/* Resolves to module_cleanup when MODULES is defined. */
DECL|variable|iic_ite_exit
id|module_exit
c_func
(paren
id|iic_ite_exit
)paren
suffix:semicolon
eof
