multiline_comment|/*&n; * drivers/input/serio/gscps2.c&n; *&n; * Copyright (c) 2004 Helge Deller &lt;deller@gmx.de&gt;&n; * Copyright (c) 2002 Laurent Canet &lt;canetl@esiee.fr&gt;&n; * Copyright (c) 2002 Thibaut Varene &lt;varenet@esiee.fr&gt;&n; *&n; * Pieces of code based on linux-2.4&squot;s hp_mouse.c &amp; hp_keyb.c&n; * &t;Copyright (c) 1999 Alex deVries &lt;alex@onefishtwo.ca&gt;&n; *&t;Copyright (c) 1999-2000 Philipp Rumpf &lt;prumpf@tux.org&gt;&n; *&t;Copyright (c) 2000 Xavier Debacker &lt;debackex@esiee.fr&gt;&n; *&t;Copyright (c) 2000-2001 Thomas Marteau &lt;marteaut@esiee.fr&gt;&n; *&n; * HP GSC PS/2 port driver, found in PA/RISC Workstations&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * TODO:&n; * - Dino testing (did HP ever shipped a machine on which this port&n; *                 was usable/enabled ?)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci_ids.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/parisc-device.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Laurent Canet &lt;canetl@esiee.fr&gt;, Thibaut Varene &lt;varenet@esiee.fr&gt;, Helge Deller &lt;deller@gmx.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;HP GSC PS2 port driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|parisc
comma
id|gscps2_device_tbl
)paren
suffix:semicolon
DECL|macro|PFX
mdefine_line|#define PFX &quot;gscps2.c: &quot;
multiline_comment|/*&n; * Driver constants&n; */
multiline_comment|/* various constants */
DECL|macro|ENABLE
mdefine_line|#define ENABLE&t;&t;&t;1
DECL|macro|DISABLE
mdefine_line|#define DISABLE&t;&t;&t;0
DECL|macro|GSC_DINO_OFFSET
mdefine_line|#define GSC_DINO_OFFSET&t;&t;0x0800&t;/* offset for DINO controller versus LASI one */
multiline_comment|/* PS/2 IO port offsets */
DECL|macro|GSC_ID
mdefine_line|#define GSC_ID&t;&t;&t;0x00&t;/* device ID offset (see: GSC_ID_XXX) */
DECL|macro|GSC_RESET
mdefine_line|#define GSC_RESET&t;&t;0x00&t;/* reset port offset */
DECL|macro|GSC_RCVDATA
mdefine_line|#define GSC_RCVDATA&t;&t;0x04&t;/* receive port offset */
DECL|macro|GSC_XMTDATA
mdefine_line|#define GSC_XMTDATA&t;&t;0x04&t;/* transmit port offset */
DECL|macro|GSC_CONTROL
mdefine_line|#define GSC_CONTROL&t;&t;0x08&t;/* see: Control register bits */
DECL|macro|GSC_STATUS
mdefine_line|#define GSC_STATUS&t;&t;0x0C&t;/* see: Status register bits */
multiline_comment|/* Control register bits */
DECL|macro|GSC_CTRL_ENBL
mdefine_line|#define GSC_CTRL_ENBL&t;&t;0x01&t;/* enable interface */
DECL|macro|GSC_CTRL_LPBXR
mdefine_line|#define GSC_CTRL_LPBXR&t;&t;0x02&t;/* loopback operation */
DECL|macro|GSC_CTRL_DIAG
mdefine_line|#define GSC_CTRL_DIAG&t;&t;0x20&t;/* directly control clock/data line */
DECL|macro|GSC_CTRL_DATDIR
mdefine_line|#define GSC_CTRL_DATDIR&t;&t;0x40&t;/* data line direct control */
DECL|macro|GSC_CTRL_CLKDIR
mdefine_line|#define GSC_CTRL_CLKDIR&t;&t;0x80&t;/* clock line direct control */
multiline_comment|/* Status register bits */
DECL|macro|GSC_STAT_RBNE
mdefine_line|#define GSC_STAT_RBNE&t;&t;0x01&t;/* Receive Buffer Not Empty */
DECL|macro|GSC_STAT_TBNE
mdefine_line|#define GSC_STAT_TBNE&t;&t;0x02&t;/* Transmit Buffer Not Empty */
DECL|macro|GSC_STAT_TERR
mdefine_line|#define GSC_STAT_TERR&t;&t;0x04&t;/* Timeout Error */
DECL|macro|GSC_STAT_PERR
mdefine_line|#define GSC_STAT_PERR&t;&t;0x08&t;/* Parity Error */
DECL|macro|GSC_STAT_CMPINTR
mdefine_line|#define GSC_STAT_CMPINTR&t;0x10&t;/* Composite Interrupt = irq on any port */
DECL|macro|GSC_STAT_DATSHD
mdefine_line|#define GSC_STAT_DATSHD&t;&t;0x40&t;/* Data Line Shadow */
DECL|macro|GSC_STAT_CLKSHD
mdefine_line|#define GSC_STAT_CLKSHD&t;&t;0x80&t;/* Clock Line Shadow */
multiline_comment|/* IDs returned by GSC_ID port register */
DECL|macro|GSC_ID_KEYBOARD
mdefine_line|#define GSC_ID_KEYBOARD&t;&t;0&t;/* device ID values */
DECL|macro|GSC_ID_MOUSE
mdefine_line|#define GSC_ID_MOUSE&t;&t;1
r_static
id|irqreturn_t
id|gscps2_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|macro|BUFFER_SIZE
mdefine_line|#define BUFFER_SIZE 0x0f
multiline_comment|/* GSC PS/2 port device struct */
DECL|struct|gscps2port
r_struct
id|gscps2port
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|padev
r_struct
id|parisc_device
op_star
id|padev
suffix:semicolon
DECL|member|port
r_struct
id|serio
op_star
id|port
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|addr
r_char
op_star
id|addr
suffix:semicolon
DECL|member|act
DECL|member|append
id|u8
id|act
comma
id|append
suffix:semicolon
multiline_comment|/* position in buffer[] */
r_struct
(brace
DECL|member|data
id|u8
id|data
suffix:semicolon
DECL|member|str
id|u8
id|str
suffix:semicolon
DECL|member|buffer
)brace
id|buffer
(braket
id|BUFFER_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|id
r_int
id|id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Various HW level routines&n; */
DECL|macro|gscps2_readb_input
mdefine_line|#define gscps2_readb_input(x)&t;&t;readb((x)+GSC_RCVDATA)
DECL|macro|gscps2_readb_control
mdefine_line|#define gscps2_readb_control(x)&t;&t;readb((x)+GSC_CONTROL)
DECL|macro|gscps2_readb_status
mdefine_line|#define gscps2_readb_status(x)&t;&t;readb((x)+GSC_STATUS)
DECL|macro|gscps2_writeb_control
mdefine_line|#define gscps2_writeb_control(x, y)&t;writeb((x), (y)+GSC_CONTROL)
multiline_comment|/*&n; * wait_TBE() - wait for Transmit Buffer Empty&n; */
DECL|function|wait_TBE
r_static
r_int
id|wait_TBE
c_func
(paren
r_char
op_star
id|addr
)paren
(brace
r_int
id|timeout
op_assign
l_int|25000
suffix:semicolon
multiline_comment|/* device is expected to react within 250 msec */
r_while
c_loop
(paren
id|gscps2_readb_status
c_func
(paren
id|addr
)paren
op_amp
id|GSC_STAT_TBNE
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|timeout
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* This should not happen */
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * gscps2_flush() - flush the receive buffer&n; */
DECL|function|gscps2_flush
r_static
r_void
id|gscps2_flush
c_func
(paren
r_struct
id|gscps2port
op_star
id|ps2port
)paren
(brace
r_while
c_loop
(paren
id|gscps2_readb_status
c_func
(paren
id|ps2port-&gt;addr
)paren
op_amp
id|GSC_STAT_RBNE
)paren
id|gscps2_readb_input
c_func
(paren
id|ps2port-&gt;addr
)paren
suffix:semicolon
id|ps2port-&gt;act
op_assign
id|ps2port-&gt;append
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * gscps2_writeb_output() - write a byte to the port&n; *&n; * returns 1 on sucess, 0 on error&n; */
DECL|function|gscps2_writeb_output
r_static
r_inline
r_int
id|gscps2_writeb_output
c_func
(paren
r_struct
id|gscps2port
op_star
id|ps2port
comma
id|u8
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_char
op_star
id|addr
op_assign
id|ps2port-&gt;addr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|wait_TBE
c_func
(paren
id|addr
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|PFX
l_string|&quot;timeout - could not write byte %#x&bslash;n&quot;
comma
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
id|gscps2_readb_status
c_func
(paren
id|ps2port-&gt;addr
)paren
op_amp
id|GSC_STAT_RBNE
)paren
multiline_comment|/* wait */
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ps2port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|data
comma
id|addr
op_plus
id|GSC_XMTDATA
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ps2port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* this is ugly, but due to timing of the port it seems to be necessary. */
id|mdelay
c_func
(paren
l_int|6
)paren
suffix:semicolon
multiline_comment|/* make sure any received data is returned as fast as possible */
multiline_comment|/* this is important e.g. when we set the LEDs on the keyboard */
id|gscps2_interrupt
c_func
(paren
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * gscps2_enable() - enables or disables the port&n; */
DECL|function|gscps2_enable
r_static
r_void
id|gscps2_enable
c_func
(paren
r_struct
id|gscps2port
op_star
id|ps2port
comma
r_int
id|enable
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|data
suffix:semicolon
multiline_comment|/* now enable/disable the port */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ps2port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|gscps2_flush
c_func
(paren
id|ps2port
)paren
suffix:semicolon
id|data
op_assign
id|gscps2_readb_control
c_func
(paren
id|ps2port-&gt;addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|enable
)paren
id|data
op_or_assign
id|GSC_CTRL_ENBL
suffix:semicolon
r_else
id|data
op_and_assign
op_complement
id|GSC_CTRL_ENBL
suffix:semicolon
id|gscps2_writeb_control
c_func
(paren
id|data
comma
id|ps2port-&gt;addr
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ps2port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|wait_TBE
c_func
(paren
id|ps2port-&gt;addr
)paren
suffix:semicolon
id|gscps2_flush
c_func
(paren
id|ps2port
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * gscps2_reset() - resets the PS/2 port&n; */
DECL|function|gscps2_reset
r_static
r_void
id|gscps2_reset
c_func
(paren
r_struct
id|gscps2port
op_star
id|ps2port
)paren
(brace
r_char
op_star
id|addr
op_assign
id|ps2port-&gt;addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* reset the interface */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ps2port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|gscps2_flush
c_func
(paren
id|ps2port
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0xff
comma
id|addr
op_plus
id|GSC_RESET
)paren
suffix:semicolon
id|gscps2_flush
c_func
(paren
id|ps2port
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ps2port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* enable it */
id|gscps2_enable
c_func
(paren
id|ps2port
comma
id|ENABLE
)paren
suffix:semicolon
)brace
r_static
id|LIST_HEAD
c_func
(paren
id|ps2port_list
)paren
suffix:semicolon
multiline_comment|/**&n; * gscps2_interrupt() - Interruption service routine&n; *&n; * This function reads received PS/2 bytes and processes them on&n; * all interfaces.&n; * The problematic part here is, that the keyboard and mouse PS/2 port&n; * share the same interrupt and it&squot;s not possible to send data if any&n; * one of them holds input data. To solve this problem we try to receive&n; * the data as fast as possible and handle the reporting to the upper layer&n; * later.&n; */
DECL|function|gscps2_interrupt
r_static
id|irqreturn_t
id|gscps2_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|gscps2port
op_star
id|ps2port
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|ps2port
comma
op_amp
id|ps2port_list
comma
id|node
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ps2port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|ps2port-&gt;buffer
(braket
id|ps2port-&gt;append
)braket
dot
id|str
op_assign
id|gscps2_readb_status
c_func
(paren
id|ps2port-&gt;addr
)paren
)paren
op_amp
id|GSC_STAT_RBNE
)paren
(brace
id|ps2port-&gt;buffer
(braket
id|ps2port-&gt;append
)braket
dot
id|data
op_assign
id|gscps2_readb_input
c_func
(paren
id|ps2port-&gt;addr
)paren
suffix:semicolon
id|ps2port-&gt;append
op_assign
(paren
(paren
id|ps2port-&gt;append
op_plus
l_int|1
)paren
op_amp
id|BUFFER_SIZE
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ps2port-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* list_for_each_entry */
multiline_comment|/* all data was read from the ports - now report the data to upper layer */
id|list_for_each_entry
c_func
(paren
id|ps2port
comma
op_amp
id|ps2port_list
comma
id|node
)paren
(brace
r_while
c_loop
(paren
id|ps2port-&gt;act
op_ne
id|ps2port-&gt;append
)paren
(brace
r_int
r_int
id|rxflags
suffix:semicolon
id|u8
id|data
comma
id|status
suffix:semicolon
multiline_comment|/* Did new data arrived while we read existing data ?&n;&t;       If yes, exit now and let the new irq handler start over again */
r_if
c_cond
(paren
id|gscps2_readb_status
c_func
(paren
id|ps2port-&gt;addr
)paren
op_amp
id|GSC_STAT_CMPINTR
)paren
r_return
id|IRQ_HANDLED
suffix:semicolon
id|status
op_assign
id|ps2port-&gt;buffer
(braket
id|ps2port-&gt;act
)braket
dot
id|str
suffix:semicolon
id|data
op_assign
id|ps2port-&gt;buffer
(braket
id|ps2port-&gt;act
)braket
dot
id|data
suffix:semicolon
id|ps2port-&gt;act
op_assign
(paren
(paren
id|ps2port-&gt;act
op_plus
l_int|1
)paren
op_amp
id|BUFFER_SIZE
)paren
suffix:semicolon
id|rxflags
op_assign
(paren
(paren
id|status
op_amp
id|GSC_STAT_TERR
)paren
ques
c_cond
id|SERIO_TIMEOUT
suffix:colon
l_int|0
)paren
op_or
(paren
(paren
id|status
op_amp
id|GSC_STAT_PERR
)paren
ques
c_cond
id|SERIO_PARITY
suffix:colon
l_int|0
)paren
suffix:semicolon
id|serio_interrupt
c_func
(paren
id|ps2port-&gt;port
comma
id|data
comma
id|rxflags
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/* while() */
)brace
multiline_comment|/* list_for_each_entry */
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * gscps2_write() - send a byte out through the aux interface.&n; */
DECL|function|gscps2_write
r_static
r_int
id|gscps2_write
c_func
(paren
r_struct
id|serio
op_star
id|port
comma
r_int
r_char
id|data
)paren
(brace
r_struct
id|gscps2port
op_star
id|ps2port
op_assign
id|port-&gt;port_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gscps2_writeb_output
c_func
(paren
id|ps2port
comma
id|data
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|PFX
l_string|&quot;sending byte %#x failed.&bslash;n&quot;
comma
id|data
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * gscps2_open() is called when a port is opened by the higher layer.&n; * It resets and enables the port.&n; */
DECL|function|gscps2_open
r_static
r_int
id|gscps2_open
c_func
(paren
r_struct
id|serio
op_star
id|port
)paren
(brace
r_struct
id|gscps2port
op_star
id|ps2port
op_assign
id|port-&gt;port_data
suffix:semicolon
id|gscps2_reset
c_func
(paren
id|ps2port
)paren
suffix:semicolon
id|gscps2_interrupt
c_func
(paren
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * gscps2_close() disables the port&n; */
DECL|function|gscps2_close
r_static
r_void
id|gscps2_close
c_func
(paren
r_struct
id|serio
op_star
id|port
)paren
(brace
r_struct
id|gscps2port
op_star
id|ps2port
op_assign
id|port-&gt;port_data
suffix:semicolon
id|gscps2_enable
c_func
(paren
id|ps2port
comma
id|DISABLE
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * gscps2_probe() - Probes PS2 devices&n; * @return: success/error report&n; */
DECL|function|gscps2_probe
r_static
r_int
id|__init
id|gscps2_probe
c_func
(paren
r_struct
id|parisc_device
op_star
id|dev
)paren
(brace
r_struct
id|gscps2port
op_star
id|ps2port
suffix:semicolon
r_struct
id|serio
op_star
id|serio
suffix:semicolon
r_int
r_int
id|hpa
op_assign
id|dev-&gt;hpa
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;irq
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Offset for DINO PS/2. Works with LASI even */
r_if
c_cond
(paren
id|dev-&gt;id.sversion
op_eq
l_int|0x96
)paren
id|hpa
op_add_assign
id|GSC_DINO_OFFSET
suffix:semicolon
id|ps2port
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|gscps2port
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|serio
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|serio
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ps2port
op_logical_or
op_logical_neg
id|serio
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|fail_nomem
suffix:semicolon
)brace
id|dev_set_drvdata
c_func
(paren
op_amp
id|dev-&gt;dev
comma
id|ps2port
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ps2port
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|gscps2port
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|serio
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|serio
)paren
)paren
suffix:semicolon
id|ps2port-&gt;port
op_assign
id|serio
suffix:semicolon
id|ps2port-&gt;padev
op_assign
id|dev
suffix:semicolon
id|ps2port-&gt;addr
op_assign
id|ioremap
c_func
(paren
id|hpa
comma
id|GSC_STATUS
op_plus
l_int|4
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|ps2port-&gt;lock
)paren
suffix:semicolon
id|gscps2_reset
c_func
(paren
id|ps2port
)paren
suffix:semicolon
id|ps2port-&gt;id
op_assign
id|readb
c_func
(paren
id|ps2port-&gt;addr
op_plus
id|GSC_ID
)paren
op_amp
l_int|0x0f
suffix:semicolon
id|snprintf
c_func
(paren
id|serio-&gt;name
comma
r_sizeof
(paren
id|serio-&gt;name
)paren
comma
l_string|&quot;GSC PS/2 %s&quot;
comma
(paren
id|ps2port-&gt;id
op_eq
id|GSC_ID_KEYBOARD
)paren
ques
c_cond
l_string|&quot;keyboard&quot;
suffix:colon
l_string|&quot;mouse&quot;
)paren
suffix:semicolon
id|strlcpy
c_func
(paren
id|serio-&gt;phys
comma
id|dev-&gt;dev.bus_id
comma
r_sizeof
(paren
id|serio-&gt;phys
)paren
)paren
suffix:semicolon
id|serio-&gt;id.type
op_assign
id|SERIO_8042
suffix:semicolon
id|serio-&gt;write
op_assign
id|gscps2_write
suffix:semicolon
id|serio-&gt;open
op_assign
id|gscps2_open
suffix:semicolon
id|serio-&gt;close
op_assign
id|gscps2_close
suffix:semicolon
id|serio-&gt;port_data
op_assign
id|ps2port
suffix:semicolon
id|serio-&gt;dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|ps2port-&gt;node
comma
op_amp
id|ps2port_list
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|gscps2_interrupt
comma
id|SA_SHIRQ
comma
id|ps2port-&gt;port-&gt;name
comma
id|ps2port
)paren
)paren
r_goto
id|fail_miserably
suffix:semicolon
r_if
c_cond
(paren
id|ps2port-&gt;id
op_ne
id|GSC_ID_KEYBOARD
op_logical_and
id|ps2port-&gt;id
op_ne
id|GSC_ID_MOUSE
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PFX
l_string|&quot;Unsupported PS/2 port at 0x%08lx (id=%d) ignored&bslash;n&quot;
comma
id|hpa
comma
id|ps2port-&gt;id
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
macro_line|#if 0
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|hpa
comma
id|GSC_STATUS
op_plus
l_int|4
comma
id|ps2port-&gt;port.name
)paren
)paren
r_goto
id|fail
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;serio: %s port at 0x%p irq %d @ %s&bslash;n&quot;
comma
id|ps2port-&gt;port-&gt;name
comma
id|ps2port-&gt;addr
comma
id|ps2port-&gt;padev-&gt;irq
comma
id|ps2port-&gt;port-&gt;phys
)paren
suffix:semicolon
id|serio_register_port
c_func
(paren
id|ps2port-&gt;port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|ps2port
)paren
suffix:semicolon
id|fail_miserably
suffix:colon
id|list_del
c_func
(paren
op_amp
id|ps2port-&gt;node
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|ps2port-&gt;addr
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|dev-&gt;hpa
comma
id|GSC_STATUS
op_plus
l_int|4
)paren
suffix:semicolon
id|fail_nomem
suffix:colon
id|kfree
c_func
(paren
id|ps2port
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|serio
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * gscps2_remove() - Removes PS2 devices&n; * @return: success/error report&n; */
DECL|function|gscps2_remove
r_static
r_int
id|__devexit
id|gscps2_remove
c_func
(paren
r_struct
id|parisc_device
op_star
id|dev
)paren
(brace
r_struct
id|gscps2port
op_star
id|ps2port
op_assign
id|dev_get_drvdata
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
id|serio_unregister_port
c_func
(paren
id|ps2port-&gt;port
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|ps2port
)paren
suffix:semicolon
id|gscps2_flush
c_func
(paren
id|ps2port
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|ps2port-&gt;node
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|ps2port-&gt;addr
)paren
suffix:semicolon
macro_line|#if 0
id|release_mem_region
c_func
(paren
id|dev-&gt;hpa
comma
id|GSC_STATUS
op_plus
l_int|4
)paren
suffix:semicolon
macro_line|#endif
id|dev_set_drvdata
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_int|NULL
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ps2port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|gscps2_device_tbl
r_static
r_struct
id|parisc_device_id
id|gscps2_device_tbl
(braket
)braket
op_assign
(brace
(brace
id|HPHW_FIO
comma
id|HVERSION_REV_ANY_ID
comma
id|HVERSION_ANY_ID
comma
l_int|0x00084
)brace
comma
multiline_comment|/* LASI PS/2 */
macro_line|#ifdef DINO_TESTED
(brace
id|HPHW_FIO
comma
id|HVERSION_REV_ANY_ID
comma
id|HVERSION_ANY_ID
comma
l_int|0x00096
)brace
comma
multiline_comment|/* DINO PS/2 */
macro_line|#endif
(brace
l_int|0
comma
)brace
multiline_comment|/* 0 terminated list */
)brace
suffix:semicolon
DECL|variable|parisc_ps2_driver
r_static
r_struct
id|parisc_driver
id|parisc_ps2_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;GSC PS2&quot;
comma
dot
id|id_table
op_assign
id|gscps2_device_tbl
comma
dot
id|probe
op_assign
id|gscps2_probe
comma
dot
id|remove
op_assign
id|gscps2_remove
comma
)brace
suffix:semicolon
DECL|function|gscps2_init
r_static
r_int
id|__init
id|gscps2_init
c_func
(paren
r_void
)paren
(brace
id|register_parisc_driver
c_func
(paren
op_amp
id|parisc_ps2_driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gscps2_exit
r_static
r_void
id|__exit
id|gscps2_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_parisc_driver
c_func
(paren
op_amp
id|parisc_ps2_driver
)paren
suffix:semicolon
)brace
DECL|variable|gscps2_init
id|module_init
c_func
(paren
id|gscps2_init
)paren
suffix:semicolon
DECL|variable|gscps2_exit
id|module_exit
c_func
(paren
id|gscps2_exit
)paren
suffix:semicolon
eof
