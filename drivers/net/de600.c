DECL|variable|version
r_static
r_const
r_char
id|version
(braket
)braket
op_assign
l_string|&quot;de600.c: $Revision: 1.41-2.5 $,  Bjorn Ekwall (bj0rn@blox.se)&bslash;n&quot;
suffix:semicolon
multiline_comment|/*&n; *&t;de600.c&n; *&n; *&t;Linux driver for the D-Link DE-600 Ethernet pocket adapter.&n; *&n; *&t;Portions (C) Copyright 1993, 1994 by Bjorn Ekwall&n; *&t;The Author may be reached as bj0rn@blox.se&n; *&n; *&t;Based on adapter information gathered from DE600.ASM by D-Link Inc.,&n; *&t;as included on disk C in the v.2.11 of PC/TCP from FTP Software.&n; *&t;For DE600.asm:&n; *&t;&t;Portions (C) Copyright 1990 D-Link, Inc.&n; *&t;&t;Copyright, 1988-1992, Russell Nelson, Crynwr Software&n; *&n; *&t;Adapted to the sample network driver core for linux,&n; *&t;written by: Donald Becker &lt;becker@super.org&gt;&n; *&t;&t;(Now at &lt;becker@scyld.com&gt;)&n; *&n; **************************************************************/
multiline_comment|/*&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2, or (at your option)&n; *&t;any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; **************************************************************/
multiline_comment|/* Add more time here if your adapter won&squot;t work OK: */
DECL|macro|DE600_SLOW_DOWN
mdefine_line|#define DE600_SLOW_DOWN&t;udelay(delay_time)
multiline_comment|/*&n; * If you still have trouble reading/writing to the adapter,&n; * modify the following &quot;#define&quot;: (see &lt;asm/io.h&gt; for more info)&n;#define REALLY_SLOW_IO&n; */
DECL|macro|SLOW_IO_BY_JUMPING
mdefine_line|#define SLOW_IO_BY_JUMPING /* Looks &quot;better&quot; than dummy write to port 0x80 :-) */
multiline_comment|/* use 0 for production, 1 for verification, &gt;2 for debug */
macro_line|#ifdef DE600_DEBUG
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x) if (de600_debug &gt;= 2) printk x
macro_line|#else
DECL|macro|DE600_DEBUG
mdefine_line|#define DE600_DEBUG 0
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x) /**/
macro_line|#endif
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;de600.h&quot;
DECL|variable|de600_debug
r_static
r_int
r_int
id|de600_debug
op_assign
id|DE600_DEBUG
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|de600_debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|de600_debug
comma
l_string|&quot;DE-600 debug level (0-2)&quot;
)paren
suffix:semicolon
DECL|variable|check_lost
r_static
r_int
r_int
id|check_lost
op_assign
l_int|1
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|check_lost
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|check_lost
comma
l_string|&quot;If set then check for unplugged de600&quot;
)paren
suffix:semicolon
DECL|variable|delay_time
r_static
r_int
r_int
id|delay_time
op_assign
l_int|10
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|delay_time
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|delay_time
comma
l_string|&quot;DE-600 deley on I/O in microseconds&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * D-Link driver variables:&n; */
DECL|variable|rx_page
r_static
r_volatile
r_int
id|rx_page
suffix:semicolon
DECL|macro|TX_PAGES
mdefine_line|#define TX_PAGES 2
DECL|variable|tx_fifo
r_static
r_volatile
r_int
id|tx_fifo
(braket
id|TX_PAGES
)braket
suffix:semicolon
DECL|variable|tx_fifo_in
r_static
r_volatile
r_int
id|tx_fifo_in
suffix:semicolon
DECL|variable|tx_fifo_out
r_static
r_volatile
r_int
id|tx_fifo_out
suffix:semicolon
DECL|variable|free_tx_pages
r_static
r_volatile
r_int
id|free_tx_pages
op_assign
id|TX_PAGES
suffix:semicolon
DECL|variable|was_down
r_static
r_int
id|was_down
suffix:semicolon
DECL|variable|de600_lock
r_static
id|spinlock_t
id|de600_lock
suffix:semicolon
DECL|function|de600_read_status
r_static
r_inline
id|u8
id|de600_read_status
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|u8
id|status
suffix:semicolon
id|outb_p
c_func
(paren
id|STATUS
comma
id|DATA_PORT
)paren
suffix:semicolon
id|status
op_assign
id|inb
c_func
(paren
id|STATUS_PORT
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|NULL_COMMAND
op_or
id|HI_NIBBLE
comma
id|DATA_PORT
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|de600_read_byte
r_static
r_inline
id|u8
id|de600_read_byte
c_func
(paren
r_int
r_char
id|type
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
multiline_comment|/* dev used by macros */
id|u8
id|lo
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|type
)paren
comma
id|DATA_PORT
)paren
suffix:semicolon
id|lo
op_assign
(paren
(paren
r_int
r_char
)paren
id|inb
c_func
(paren
id|STATUS_PORT
)paren
)paren
op_rshift
l_int|4
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|type
)paren
op_or
id|HI_NIBBLE
comma
id|DATA_PORT
)paren
suffix:semicolon
r_return
(paren
(paren
r_int
r_char
)paren
id|inb
c_func
(paren
id|STATUS_PORT
)paren
op_amp
(paren
r_int
r_char
)paren
l_int|0xf0
)paren
op_or
id|lo
suffix:semicolon
)brace
multiline_comment|/*&n; * Open/initialize the board.  This is called (in the current kernel)&n; * after booting when &squot;ifconfig &lt;dev-&gt;name&gt; $IP_ADDR&squot; is run (in rc.inet1).&n; *&n; * This routine should set everything up anew at each open, even&n; * registers that &quot;should&quot; only need to be set once at boot, so that&n; * there is a non-reboot way to recover if something goes wrong.&n; */
DECL|function|de600_open
r_static
r_int
id|de600_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
op_assign
id|request_irq
c_func
(paren
id|DE600_IRQ
comma
id|de600_interrupt
comma
l_int|0
comma
id|dev-&gt;name
comma
id|dev
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
id|KERN_ERR
l_string|&quot;%s: unable to get IRQ %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|DE600_IRQ
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|de600_lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
id|adapter_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|de600_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * The inverse routine to de600_open().&n; */
DECL|function|de600_close
r_static
r_int
id|de600_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|select_nic
c_func
(paren
)paren
suffix:semicolon
id|rx_page
op_assign
l_int|0
suffix:semicolon
id|de600_put_command
c_func
(paren
id|RESET
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
id|STOP_RESET
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|select_prn
c_func
(paren
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|DE600_IRQ
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_stats
r_static
r_struct
id|net_device_stats
op_star
id|get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
(paren
r_struct
id|net_device_stats
op_star
)paren
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
)brace
DECL|function|trigger_interrupt
r_static
r_inline
r_void
id|trigger_interrupt
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|de600_put_command
c_func
(paren
id|FLIP_IRQ
)paren
suffix:semicolon
id|select_prn
c_func
(paren
)paren
suffix:semicolon
id|DE600_SLOW_DOWN
suffix:semicolon
id|select_nic
c_func
(paren
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy a buffer to the adapter transmit page memory.&n; * Start sending.&n; */
DECL|function|de600_start_xmit
r_static
r_int
id|de600_start_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|transmit_from
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|tickssofar
suffix:semicolon
id|u8
op_star
id|buffer
op_assign
id|skb-&gt;data
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|free_tx_pages
op_le
l_int|0
)paren
(brace
multiline_comment|/* Do timeouts, to avoid hangs. */
id|tickssofar
op_assign
id|jiffies
op_minus
id|dev-&gt;trans_start
suffix:semicolon
r_if
c_cond
(paren
id|tickssofar
OL
l_int|5
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* else */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: transmit timed out (%d), %s?&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|tickssofar
comma
l_string|&quot;network cable problem&quot;
)paren
suffix:semicolon
multiline_comment|/* Restart the adapter. */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|de600_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|adapter_init
c_func
(paren
id|dev
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|de600_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|de600_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Start real output */
id|PRINTK
c_func
(paren
(paren
l_string|&quot;de600_start_xmit:len=%d, page %d/%d&bslash;n&quot;
comma
id|skb-&gt;len
comma
id|tx_fifo_in
comma
id|free_tx_pages
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_assign
id|skb-&gt;len
)paren
OL
id|RUNT
)paren
id|len
op_assign
id|RUNT
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|de600_lock
comma
id|flags
)paren
suffix:semicolon
id|select_nic
c_func
(paren
)paren
suffix:semicolon
id|tx_fifo
(braket
id|tx_fifo_in
)braket
op_assign
id|transmit_from
op_assign
id|tx_page_adr
c_func
(paren
id|tx_fifo_in
)paren
op_minus
id|len
suffix:semicolon
id|tx_fifo_in
op_assign
(paren
id|tx_fifo_in
op_plus
l_int|1
)paren
op_mod
id|TX_PAGES
suffix:semicolon
multiline_comment|/* Next free tx page */
r_if
c_cond
(paren
id|check_lost
)paren
(brace
multiline_comment|/* This costs about 40 instructions per packet... */
id|de600_setup_address
c_func
(paren
id|NODE_ADDRESS
comma
id|RW_ADDR
)paren
suffix:semicolon
id|de600_read_byte
c_func
(paren
id|READ_DATA
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|was_down
op_logical_or
(paren
id|de600_read_byte
c_func
(paren
id|READ_DATA
comma
id|dev
)paren
op_ne
l_int|0xde
)paren
)paren
(brace
r_if
c_cond
(paren
id|adapter_init
c_func
(paren
id|dev
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|de600_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
)brace
id|de600_setup_address
c_func
(paren
id|transmit_from
comma
id|RW_ADDR
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
id|skb-&gt;len
suffix:semicolon
op_increment
id|i
comma
op_increment
id|buffer
)paren
id|de600_put_byte
c_func
(paren
op_star
id|buffer
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
op_increment
id|i
)paren
id|de600_put_byte
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_tx_pages
op_decrement
op_eq
id|TX_PAGES
)paren
(brace
multiline_comment|/* No transmission going on */
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|netif_start_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* allow more packets into adapter */
multiline_comment|/* Send page and generate a faked interrupt */
id|de600_setup_address
c_func
(paren
id|transmit_from
comma
id|TX_ADDR
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
id|TX_ENABLE
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|free_tx_pages
)paren
id|netif_start_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_else
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|select_prn
c_func
(paren
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|de600_lock
comma
id|flags
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The typical workload of the driver:&n; * Handle the network interface interrupts.&n; */
DECL|function|de600_interrupt
r_static
id|irqreturn_t
id|de600_interrupt
c_func
(paren
r_int
id|irq
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
r_struct
id|net_device
op_star
id|dev
op_assign
id|dev_id
suffix:semicolon
id|u8
id|irq_status
suffix:semicolon
r_int
id|retrig
op_assign
l_int|0
suffix:semicolon
r_int
id|boguscount
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This might just as well be deleted now, no crummy drivers present :-) */
r_if
c_cond
(paren
(paren
id|dev
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|DE600_IRQ
op_ne
id|irq
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: bogus interrupt %d&bslash;n&quot;
comma
id|dev
ques
c_cond
id|dev-&gt;name
suffix:colon
l_string|&quot;DE-600&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
id|IRQ_NONE
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|de600_lock
)paren
suffix:semicolon
id|select_nic
c_func
(paren
)paren
suffix:semicolon
id|irq_status
op_assign
id|de600_read_status
c_func
(paren
id|dev
)paren
suffix:semicolon
r_do
(brace
id|PRINTK
c_func
(paren
(paren
l_string|&quot;de600_interrupt (%02X)&bslash;n&quot;
comma
id|irq_status
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_status
op_amp
id|RX_GOOD
)paren
id|de600_rx_intr
c_func
(paren
id|dev
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_status
op_amp
id|RX_BUSY
)paren
)paren
id|de600_put_command
c_func
(paren
id|RX_ENABLE
)paren
suffix:semicolon
multiline_comment|/* Any transmission in progress? */
r_if
c_cond
(paren
id|free_tx_pages
OL
id|TX_PAGES
)paren
id|retrig
op_assign
id|de600_tx_intr
c_func
(paren
id|dev
comma
id|irq_status
)paren
suffix:semicolon
r_else
id|retrig
op_assign
l_int|0
suffix:semicolon
id|irq_status
op_assign
id|de600_read_status
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|irq_status
op_amp
id|RX_GOOD
)paren
op_logical_or
(paren
(paren
op_increment
id|boguscount
OL
l_int|100
)paren
op_logical_and
id|retrig
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Yeah, it _looks_ like busy waiting, smells like busy waiting&n;&t; * and I know it&squot;s not PC, but please, it will only occur once&n;&t; * in a while and then only for a loop or so (&lt; 1ms for sure!)&n;&t; */
multiline_comment|/* Enable adapter interrupts */
id|select_prn
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retrig
)paren
id|trigger_interrupt
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|de600_lock
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|de600_tx_intr
r_static
r_int
id|de600_tx_intr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|irq_status
)paren
(brace
multiline_comment|/*&n;&t; * Returns 1 if tx still not done&n;&t; */
multiline_comment|/* Check if current transmission is done yet */
r_if
c_cond
(paren
id|irq_status
op_amp
id|TX_BUSY
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* tx not done, try again */
multiline_comment|/* else */
multiline_comment|/* If last transmission OK then bump fifo index */
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_status
op_amp
id|TX_FAILED16
)paren
)paren
(brace
id|tx_fifo_out
op_assign
(paren
id|tx_fifo_out
op_plus
l_int|1
)paren
op_mod
id|TX_PAGES
suffix:semicolon
op_increment
id|free_tx_pages
suffix:semicolon
(paren
(paren
r_struct
id|net_device_stats
op_star
)paren
(paren
id|dev-&gt;priv
)paren
)paren
op_member_access_from_pointer
id|tx_packets
op_increment
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/* More to send, or resend last packet? */
r_if
c_cond
(paren
(paren
id|free_tx_pages
OL
id|TX_PAGES
)paren
op_logical_or
(paren
id|irq_status
op_amp
id|TX_FAILED16
)paren
)paren
(brace
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|de600_setup_address
c_func
(paren
id|tx_fifo
(braket
id|tx_fifo_out
)braket
comma
id|TX_ADDR
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
id|TX_ENABLE
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* else */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We have a good packet, get it out of the adapter.&n; */
DECL|function|de600_rx_intr
r_static
r_void
id|de600_rx_intr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|read_from
suffix:semicolon
r_int
id|size
suffix:semicolon
r_int
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/* Get size of received packet */
id|size
op_assign
id|de600_read_byte
c_func
(paren
id|RX_LEN
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* low byte */
id|size
op_add_assign
(paren
id|de600_read_byte
c_func
(paren
id|RX_LEN
comma
id|dev
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* high byte */
id|size
op_sub_assign
l_int|4
suffix:semicolon
multiline_comment|/* Ignore trailing 4 CRC-bytes */
multiline_comment|/* Tell adapter where to store next incoming packet, enable receiver */
id|read_from
op_assign
id|rx_page_adr
c_func
(paren
)paren
suffix:semicolon
id|next_rx_page
c_func
(paren
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
id|RX_ENABLE
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|size
OL
l_int|32
)paren
op_logical_or
(paren
id|size
OG
l_int|1535
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: Bogus packet size %d.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|10000
)paren
id|adapter_init
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|size
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Couldn&squot;t allocate a sk_buff of size %d.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|size
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* else */
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Align */
multiline_comment|/* &squot;skb-&gt;data&squot; points to the start of sk_buff data area. */
id|buffer
op_assign
id|skb_put
c_func
(paren
id|skb
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* copy the packet into the buffer */
id|de600_setup_address
c_func
(paren
id|read_from
comma
id|RW_ADDR
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|size
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
op_decrement
id|i
comma
op_increment
id|buffer
)paren
op_star
id|buffer
op_assign
id|de600_read_byte
c_func
(paren
id|READ_DATA
comma
id|dev
)paren
suffix:semicolon
id|skb-&gt;protocol
op_assign
id|eth_type_trans
c_func
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/* update stats */
id|dev-&gt;last_rx
op_assign
id|jiffies
suffix:semicolon
(paren
(paren
r_struct
id|net_device_stats
op_star
)paren
(paren
id|dev-&gt;priv
)paren
)paren
op_member_access_from_pointer
id|rx_packets
op_increment
suffix:semicolon
multiline_comment|/* count all receives */
(paren
(paren
r_struct
id|net_device_stats
op_star
)paren
(paren
id|dev-&gt;priv
)paren
)paren
op_member_access_from_pointer
id|rx_bytes
op_add_assign
id|size
suffix:semicolon
multiline_comment|/* count all received bytes */
multiline_comment|/*&n;&t; * If any worth-while packets have been received, netif_rx()&n;&t; * will work on them when we get to the tasklets.&n;&t; */
)brace
DECL|function|de600_probe
r_int
id|__init
id|de600_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_static
r_struct
id|net_device_stats
id|de600_netstats
suffix:semicolon
multiline_comment|/*dev-&gt;priv = kmalloc(sizeof(struct net_device_stats), GFP_KERNEL);*/
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: D-Link DE-600 pocket adapter&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
multiline_comment|/* Alpha testers must have the version number to report bugs. */
r_if
c_cond
(paren
id|de600_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|version
)paren
suffix:semicolon
multiline_comment|/* probe for adapter */
id|rx_page
op_assign
l_int|0
suffix:semicolon
id|select_nic
c_func
(paren
)paren
suffix:semicolon
(paren
r_void
)paren
id|de600_read_status
c_func
(paren
id|dev
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
id|RESET
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
id|STOP_RESET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|de600_read_status
c_func
(paren
id|dev
)paren
op_amp
l_int|0xf0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;: not at I/O %#3x.&bslash;n&quot;
comma
id|DATA_PORT
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Maybe we found one,&n;&t; * have to check if it is a D-Link DE-600 adapter...&n;&t; */
multiline_comment|/* Get the adapter ethernet address from the ROM */
id|de600_setup_address
c_func
(paren
id|NODE_ADDRESS
comma
id|RW_ADDR
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
id|ETH_ALEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|de600_read_byte
c_func
(paren
id|READ_DATA
comma
id|dev
)paren
suffix:semicolon
id|dev-&gt;broadcast
(braket
id|i
)braket
op_assign
l_int|0xff
suffix:semicolon
)brace
multiline_comment|/* Check magic code */
r_if
c_cond
(paren
(paren
id|dev-&gt;dev_addr
(braket
l_int|1
)braket
op_eq
l_int|0xde
)paren
op_logical_and
(paren
id|dev-&gt;dev_addr
(braket
l_int|2
)braket
op_eq
l_int|0x15
)paren
)paren
(brace
multiline_comment|/* OK, install real address */
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
op_assign
l_int|0x00
suffix:semicolon
id|dev-&gt;dev_addr
(braket
l_int|1
)braket
op_assign
l_int|0x80
suffix:semicolon
id|dev-&gt;dev_addr
(braket
l_int|2
)braket
op_assign
l_int|0xc8
suffix:semicolon
id|dev-&gt;dev_addr
(braket
l_int|3
)braket
op_and_assign
l_int|0x0f
suffix:semicolon
id|dev-&gt;dev_addr
(braket
l_int|3
)braket
op_or_assign
l_int|0x70
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot; not identified in the printer port&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|DE600_IO
comma
l_int|3
comma
l_string|&quot;de600&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;DE600: port 0x%x busy&bslash;n&quot;
comma
id|DE600_IO
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;, Ethernet Address: %02X&quot;
comma
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|ETH_ALEN
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;:%02X&quot;
comma
id|dev-&gt;dev_addr
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Initialize the device structure. */
id|dev-&gt;priv
op_assign
op_amp
id|de600_netstats
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|net_device_stats
)paren
)paren
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|get_stats
suffix:semicolon
id|dev-&gt;open
op_assign
id|de600_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|de600_close
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
op_amp
id|de600_start_xmit
suffix:semicolon
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;flags
op_and_assign
op_complement
id|IFF_MULTICAST
suffix:semicolon
id|select_prn
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|adapter_init
r_static
r_int
id|adapter_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
id|select_nic
c_func
(paren
)paren
suffix:semicolon
id|rx_page
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* used by RESET */
id|de600_put_command
c_func
(paren
id|RESET
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
id|STOP_RESET
)paren
suffix:semicolon
multiline_comment|/* Check if it is still there... */
multiline_comment|/* Get the some bytes of the adapter ethernet address from the ROM */
id|de600_setup_address
c_func
(paren
id|NODE_ADDRESS
comma
id|RW_ADDR
)paren
suffix:semicolon
id|de600_read_byte
c_func
(paren
id|READ_DATA
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|de600_read_byte
c_func
(paren
id|READ_DATA
comma
id|dev
)paren
op_ne
l_int|0xde
)paren
op_logical_or
(paren
id|de600_read_byte
c_func
(paren
id|READ_DATA
comma
id|dev
)paren
op_ne
l_int|0x15
)paren
)paren
(brace
multiline_comment|/* was: if (de600_read_status(dev) &amp; 0xf0) { */
id|printk
c_func
(paren
l_string|&quot;Something has happened to the DE-600!  Please check it and do a new ifconfig!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Goodbye, cruel world... */
id|dev-&gt;flags
op_and_assign
op_complement
id|IFF_UP
suffix:semicolon
id|de600_close
c_func
(paren
id|dev
)paren
suffix:semicolon
id|was_down
op_assign
l_int|1
suffix:semicolon
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Transmit busy...  */
r_return
l_int|1
suffix:semicolon
multiline_comment|/* failed */
)brace
r_if
c_cond
(paren
id|was_down
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Thanks, I feel much better now!&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|was_down
op_assign
l_int|0
suffix:semicolon
)brace
id|tx_fifo_in
op_assign
l_int|0
suffix:semicolon
id|tx_fifo_out
op_assign
l_int|0
suffix:semicolon
id|free_tx_pages
op_assign
id|TX_PAGES
suffix:semicolon
multiline_comment|/* set the ether address. */
id|de600_setup_address
c_func
(paren
id|NODE_ADDRESS
comma
id|RW_ADDR
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
id|ETH_ALEN
suffix:semicolon
id|i
op_increment
)paren
id|de600_put_byte
c_func
(paren
id|dev-&gt;dev_addr
(braket
id|i
)braket
)paren
suffix:semicolon
multiline_comment|/* where to start saving incoming packets */
id|rx_page
op_assign
id|RX_BP
op_or
id|RX_BASE_PAGE
suffix:semicolon
id|de600_setup_address
c_func
(paren
id|MEM_4K
comma
id|RW_ADDR
)paren
suffix:semicolon
multiline_comment|/* Enable receiver */
id|de600_put_command
c_func
(paren
id|RX_ENABLE
)paren
suffix:semicolon
id|select_prn
c_func
(paren
)paren
suffix:semicolon
id|netif_start_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* OK */
)brace
DECL|variable|de600_dev
r_static
r_struct
id|net_device
id|de600_dev
suffix:semicolon
DECL|function|de600_init
r_static
r_int
id|__init
id|de600_init
c_func
(paren
r_void
)paren
(brace
id|spin_lock_init
c_func
(paren
op_amp
id|de600_lock
)paren
suffix:semicolon
id|de600_dev.init
op_assign
id|de600_probe
suffix:semicolon
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
op_amp
id|de600_dev
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|de600_exit
r_static
r_void
id|__exit
id|de600_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_netdev
c_func
(paren
op_amp
id|de600_dev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|DE600_IO
comma
l_int|3
)paren
suffix:semicolon
)brace
DECL|variable|de600_init
id|module_init
c_func
(paren
id|de600_init
)paren
suffix:semicolon
DECL|variable|de600_exit
id|module_exit
c_func
(paren
id|de600_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
