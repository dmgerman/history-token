multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* i2c-elektor.c i2c-hw access for PCF8584 style isa bus adaptes             */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 1995-97 Simon G. Vogl&n;                   1998-99 Hans Berglund&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* With some changes from Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt; and even&n;   Frodo Looijaard &lt;frodol@dds.nl&gt; */
multiline_comment|/* Partialy rewriten by Oleg I. Vdovikin for mmapped support of &n;   for Alpha Processor Inc. UP-2000(+) boards */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-pcf.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;../algos/i2c-algo-pcf.h&quot;
DECL|macro|DEFAULT_BASE
mdefine_line|#define DEFAULT_BASE 0x330
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
op_assign
l_int|0x1c
suffix:semicolon
DECL|variable|own
r_static
r_int
id|own
op_assign
l_int|0x55
suffix:semicolon
DECL|variable|mmapped
r_static
r_int
id|mmapped
suffix:semicolon
multiline_comment|/* vdovikin: removed static struct i2c_pcf_isa gpi; code - &n;  this module in real supports only one device, due to missing arguments&n;  in some functions, called from the algo-pcf module. Sometimes it&squot;s&n;  need to be rewriten - but for now just remove this for simpler reading */
DECL|variable|pcf_wait
r_static
id|wait_queue_head_t
id|pcf_wait
suffix:semicolon
DECL|variable|pcf_pending
r_static
r_int
id|pcf_pending
suffix:semicolon
DECL|variable|lock
r_static
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* ----- local functions ----------------------------------------------&t;*/
DECL|function|pcf_isa_setbyte
r_static
r_void
id|pcf_isa_setbyte
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
id|address
op_assign
id|ctl
ques
c_cond
(paren
id|base
op_plus
l_int|1
)paren
suffix:colon
id|base
suffix:semicolon
multiline_comment|/* enable irq if any specified for serial operation */
r_if
c_cond
(paren
id|ctl
op_logical_and
id|irq
op_logical_and
(paren
id|val
op_amp
id|I2C_PCF_ESO
)paren
)paren
(brace
id|val
op_or_assign
id|I2C_PCF_ENI
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
l_string|&quot;i2c-elektor: Write 0x%X 0x%02X&bslash;n&quot;
comma
id|address
comma
id|val
op_amp
l_int|255
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|mmapped
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* regular I/O */
id|outb
c_func
(paren
id|val
comma
id|address
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* double mapped I/O needed for UP2000 board,&n;                   I don&squot;t know why this... */
id|writeb
c_func
(paren
id|val
comma
(paren
r_void
op_star
)paren
id|address
)paren
suffix:semicolon
multiline_comment|/* fall */
r_case
l_int|1
suffix:colon
multiline_comment|/* memory mapped I/O */
id|writeb
c_func
(paren
id|val
comma
(paren
r_void
op_star
)paren
id|address
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|pcf_isa_getbyte
r_static
r_int
id|pcf_isa_getbyte
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
id|address
op_assign
id|ctl
ques
c_cond
(paren
id|base
op_plus
l_int|1
)paren
suffix:colon
id|base
suffix:semicolon
r_int
id|val
op_assign
id|mmapped
ques
c_cond
id|readb
c_func
(paren
(paren
r_void
op_star
)paren
id|address
)paren
suffix:colon
id|inb
c_func
(paren
id|address
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;i2c-elektor: Read 0x%X 0x%02X&bslash;n&quot;
comma
id|address
comma
id|val
)paren
suffix:semicolon
r_return
(paren
id|val
)paren
suffix:semicolon
)brace
DECL|function|pcf_isa_getown
r_static
r_int
id|pcf_isa_getown
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
id|own
)paren
suffix:semicolon
)brace
DECL|function|pcf_isa_getclock
r_static
r_int
id|pcf_isa_getclock
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
id|clock
)paren
suffix:semicolon
)brace
DECL|function|pcf_isa_waitforpin
r_static
r_void
id|pcf_isa_waitforpin
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
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
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
id|pcf_pending
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
id|pcf_wait
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
id|pcf_pending
op_eq
l_int|1
)paren
(brace
id|pcf_pending
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
id|pcf_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
r_else
(brace
id|pcf_pending
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
DECL|function|pcf_isa_handler
r_static
id|irqreturn_t
id|pcf_isa_handler
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
id|pcf_pending
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
id|pcf_wait
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|pcf_isa_init
r_static
r_int
id|pcf_isa_init
c_func
(paren
r_void
)paren
(brace
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
op_logical_neg
id|mmapped
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|base
comma
l_int|2
comma
l_string|&quot;i2c (isa bus adapter)&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-elektor: requested I/O region (0x%X:2) &quot;
l_string|&quot;is in use.&bslash;n&quot;
comma
id|base
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|irq
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq
comma
id|pcf_isa_handler
comma
l_int|0
comma
l_string|&quot;PCF8584&quot;
comma
l_int|NULL
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-elektor: Request irq%d failed&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|irq
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------------------&n; * Encapsulate the above functions in the correct operations structure.&n; * This is only done when more than one hardware adapter is supported.&n; */
DECL|variable|pcf_isa_data
r_static
r_struct
id|i2c_algo_pcf_data
id|pcf_isa_data
op_assign
(brace
dot
id|setpcf
op_assign
id|pcf_isa_setbyte
comma
dot
id|getpcf
op_assign
id|pcf_isa_getbyte
comma
dot
id|getown
op_assign
id|pcf_isa_getown
comma
dot
id|getclock
op_assign
id|pcf_isa_getclock
comma
dot
id|waitforpin
op_assign
id|pcf_isa_waitforpin
comma
dot
id|udelay
op_assign
l_int|10
comma
dot
id|mdelay
op_assign
l_int|10
comma
dot
id|timeout
op_assign
l_int|100
comma
)brace
suffix:semicolon
DECL|variable|pcf_isa_ops
r_static
r_struct
id|i2c_adapter
id|pcf_isa_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
r_class
op_assign
id|I2C_CLASS_HWMON
comma
dot
id|id
op_assign
id|I2C_HW_P_ELEK
comma
dot
id|algo_data
op_assign
op_amp
id|pcf_isa_data
comma
dot
id|name
op_assign
l_string|&quot;PCF8584 ISA adapter&quot;
comma
)brace
suffix:semicolon
DECL|function|i2c_pcfisa_init
r_static
r_int
id|__init
id|i2c_pcfisa_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef __alpha__
multiline_comment|/* check to see we have memory mapped PCF8584 connected to the &n;&t;Cypress cy82c693 PCI-ISA bridge as on UP2000 board */
r_if
c_cond
(paren
id|base
op_eq
l_int|0
)paren
(brace
r_struct
id|pci_dev
op_star
id|cy693_dev
suffix:semicolon
id|cy693_dev
op_assign
id|pci_get_device
c_func
(paren
id|PCI_VENDOR_ID_CONTAQ
comma
id|PCI_DEVICE_ID_CONTAQ_82C693
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cy693_dev
)paren
(brace
r_char
id|config
suffix:semicolon
multiline_comment|/* yeap, we&squot;ve found cypress, let&squot;s check config */
r_if
c_cond
(paren
op_logical_neg
id|pci_read_config_byte
c_func
(paren
id|cy693_dev
comma
l_int|0x47
comma
op_amp
id|config
)paren
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;i2c-elektor: found cy82c693, config register 0x47 = 0x%02x.&bslash;n&quot;
comma
id|config
)paren
suffix:semicolon
multiline_comment|/* UP2000 board has this register set to 0xe1,&n;                                   but the most significant bit as seems can be &n;&t;&t;&t;&t;   reset during the proper initialisation&n;                                   sequence if guys from API decides to do that&n;                                   (so, we can even enable Tsunami Pchip&n;                                   window for the upper 1 Gb) */
multiline_comment|/* so just check for ROMCS at 0xe0000,&n;                                   ROMCS enabled for writes&n;&t;&t;&t;&t;   and external XD Bus buffer in use. */
r_if
c_cond
(paren
(paren
id|config
op_amp
l_int|0x7f
)paren
op_eq
l_int|0x61
)paren
(brace
multiline_comment|/* seems to be UP2000 like board */
id|base
op_assign
l_int|0xe0000
suffix:semicolon
multiline_comment|/* I don&squot;t know why we need to&n;                                           write twice */
id|mmapped
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* UP2000 drives ISA with&n;&t;&t;&t;&t;&t;   8.25 MHz (PCI/4) clock&n;&t;&t;&t;&t;&t;   (this can be read from cypress) */
id|clock
op_assign
id|I2C_PCF_CLK
op_or
id|I2C_PCF_TRNS90
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c-elektor: found API UP2000 like board, will probe PCF8584 later.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|pci_dev_put
c_func
(paren
id|cy693_dev
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/* sanity checks for mmapped I/O */
r_if
c_cond
(paren
id|mmapped
op_logical_and
id|base
OL
l_int|0xc8000
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-elektor: incorrect base address (0x%0X) specified for mmapped I/O.&bslash;n&quot;
comma
id|base
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c-elektor: i2c pcf8584-isa adapter driver&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
op_eq
l_int|0
)paren
(brace
id|base
op_assign
id|DEFAULT_BASE
suffix:semicolon
)brace
id|init_waitqueue_head
c_func
(paren
op_amp
id|pcf_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pcf_isa_init
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|i2c_pcf_add_bus
c_func
(paren
op_amp
id|pcf_isa_ops
)paren
OL
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-elektor: found device at %#x.&bslash;n&quot;
comma
id|base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
r_if
c_cond
(paren
id|irq
OG
l_int|0
)paren
(brace
id|disable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|irq
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mmapped
)paren
id|release_region
c_func
(paren
id|base
comma
l_int|2
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|i2c_pcfisa_exit
r_static
r_void
id|i2c_pcfisa_exit
c_func
(paren
r_void
)paren
(brace
id|i2c_pcf_del_bus
c_func
(paren
op_amp
id|pcf_isa_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
OG
l_int|0
)paren
(brace
id|disable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|irq
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|mmapped
)paren
id|release_region
c_func
(paren
id|base
comma
l_int|2
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Hans Berglund &lt;hb@spacetec.no&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I2C-Bus adapter routines for PCF8584 ISA bus adapter&quot;
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
id|module_param
c_func
(paren
id|mmapped
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
DECL|variable|i2c_pcfisa_init
id|module_init
c_func
(paren
id|i2c_pcfisa_init
)paren
suffix:semicolon
DECL|variable|i2c_pcfisa_exit
id|module_exit
c_func
(paren
id|i2c_pcfisa_exit
)paren
suffix:semicolon
eof
