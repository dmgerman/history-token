multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Routines for control of MPU-401 in UART mode&n; *&n; *  MPU-401 supports UART mode which is not capable generate transmit&n; *  interrupts thus output is done via polling. Also, if irq &lt; 0, then&n; *  input is done also via polling. Do not expect good performance.&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; *   13-03-2003:&n; *      Added support for different kind of hardware I/O. Build in choices&n; *      are port and mmio. For other kind of I/O, set mpu-&gt;read and&n; *      mpu-&gt;write to your own I/O functions.&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/mpu401.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Routines for control of MPU-401 in UART mode&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_static
r_void
id|snd_mpu401_uart_input_read
c_func
(paren
id|mpu401_t
op_star
id|mpu
)paren
suffix:semicolon
r_static
r_void
id|snd_mpu401_uart_output_write
c_func
(paren
id|mpu401_t
op_star
id|mpu
)paren
suffix:semicolon
multiline_comment|/*&n;&n; */
DECL|macro|snd_mpu401_input_avail
mdefine_line|#define snd_mpu401_input_avail(mpu)&t;(!(mpu-&gt;read(mpu, MPU401C(mpu)) &amp; 0x80))
DECL|macro|snd_mpu401_output_ready
mdefine_line|#define snd_mpu401_output_ready(mpu)&t;(!(mpu-&gt;read(mpu, MPU401C(mpu)) &amp; 0x40))
DECL|macro|MPU401_RESET
mdefine_line|#define MPU401_RESET&t;&t;0xff
DECL|macro|MPU401_ENTER_UART
mdefine_line|#define MPU401_ENTER_UART&t;0x3f
DECL|macro|MPU401_ACK
mdefine_line|#define MPU401_ACK&t;&t;0xfe
multiline_comment|/* Build in lowlevel io */
DECL|function|mpu401_write_port
r_static
r_void
id|mpu401_write_port
c_func
(paren
id|mpu401_t
op_star
id|mpu
comma
r_int
r_char
id|data
comma
r_int
r_int
id|addr
)paren
(brace
id|outb
c_func
(paren
id|data
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|mpu401_read_port
r_static
r_int
r_char
id|mpu401_read_port
c_func
(paren
id|mpu401_t
op_star
id|mpu
comma
r_int
r_int
id|addr
)paren
(brace
r_return
id|inb
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|mpu401_write_mmio
r_static
r_void
id|mpu401_write_mmio
c_func
(paren
id|mpu401_t
op_star
id|mpu
comma
r_int
r_char
id|data
comma
r_int
r_int
id|addr
)paren
(brace
id|writeb
c_func
(paren
id|data
comma
(paren
r_void
id|__iomem
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|mpu401_read_mmio
r_static
r_int
r_char
id|mpu401_read_mmio
c_func
(paren
id|mpu401_t
op_star
id|mpu
comma
r_int
r_int
id|addr
)paren
(brace
r_return
id|readb
c_func
(paren
(paren
r_void
id|__iomem
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/*  */
DECL|function|snd_mpu401_uart_clear_rx
r_static
r_void
id|snd_mpu401_uart_clear_rx
c_func
(paren
id|mpu401_t
op_star
id|mpu
)paren
(brace
r_int
id|timeout
op_assign
l_int|100000
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|timeout
OG
l_int|0
op_logical_and
id|snd_mpu401_input_avail
c_func
(paren
id|mpu
)paren
suffix:semicolon
id|timeout
op_decrement
)paren
id|mpu
op_member_access_from_pointer
id|read
c_func
(paren
id|mpu
comma
id|MPU401D
c_func
(paren
id|mpu
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG
r_if
c_cond
(paren
id|timeout
op_le
l_int|0
)paren
id|snd_printk
c_func
(paren
l_string|&quot;cmd: clear rx timeout (status = 0x%x)&bslash;n&quot;
comma
id|mpu
op_member_access_from_pointer
id|read
c_func
(paren
id|mpu
comma
id|MPU401C
c_func
(paren
id|mpu
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|_snd_mpu401_uart_interrupt
r_static
r_void
id|_snd_mpu401_uart_interrupt
c_func
(paren
id|mpu401_t
op_star
id|mpu
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|mpu-&gt;input_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|MPU401_MODE_BIT_INPUT
comma
op_amp
id|mpu-&gt;mode
)paren
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|mpu-&gt;rx_loop
)paren
suffix:semicolon
id|snd_mpu401_uart_input_read
c_func
(paren
id|mpu
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|mpu-&gt;rx_loop
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_mpu401_uart_clear_rx
c_func
(paren
id|mpu
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mpu-&gt;input_lock
)paren
suffix:semicolon
multiline_comment|/* ok. for better Tx performance try do some output when input is done */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|MPU401_MODE_BIT_OUTPUT
comma
op_amp
id|mpu-&gt;mode
)paren
op_logical_and
id|test_bit
c_func
(paren
id|MPU401_MODE_BIT_OUTPUT_TRIGGER
comma
op_amp
id|mpu-&gt;mode
)paren
)paren
(brace
r_if
c_cond
(paren
id|spin_trylock
c_func
(paren
op_amp
id|mpu-&gt;output_lock
)paren
)paren
(brace
id|atomic_dec
c_func
(paren
op_amp
id|mpu-&gt;tx_loop
)paren
suffix:semicolon
id|snd_mpu401_uart_output_write
c_func
(paren
id|mpu
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|mpu-&gt;tx_loop
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mpu-&gt;output_lock
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/**&n; * snd_mpu401_uart_interrupt - generic MPU401-UART interrupt handler&n; * @irq: the irq number&n; * @dev_id: mpu401 instance&n; * @regs: the reigster&n; *&n; * Processes the interrupt for MPU401-UART i/o.&n; */
DECL|function|snd_mpu401_uart_interrupt
id|irqreturn_t
id|snd_mpu401_uart_interrupt
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
id|mpu401_t
op_star
id|mpu
op_assign
id|dev_id
suffix:semicolon
r_if
c_cond
(paren
id|mpu
op_eq
l_int|NULL
)paren
r_return
id|IRQ_NONE
suffix:semicolon
id|_snd_mpu401_uart_interrupt
c_func
(paren
id|mpu
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * timer callback&n; * reprogram the timer and call the interrupt job&n; */
DECL|function|snd_mpu401_uart_timer
r_static
r_void
id|snd_mpu401_uart_timer
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|mpu401_t
op_star
id|mpu
op_assign
(paren
id|mpu401_t
op_star
)paren
id|data
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mpu-&gt;timer_lock
)paren
suffix:semicolon
multiline_comment|/*mpu-&gt;mode |= MPU401_MODE_TIMER;*/
id|mpu-&gt;timer.expires
op_assign
l_int|1
op_plus
id|jiffies
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|mpu-&gt;timer
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mpu-&gt;timer_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpu-&gt;rmidi
)paren
id|_snd_mpu401_uart_interrupt
c_func
(paren
id|mpu
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * initialize the timer callback if not programmed yet&n; */
DECL|function|snd_mpu401_uart_add_timer
r_static
r_void
id|snd_mpu401_uart_add_timer
(paren
id|mpu401_t
op_star
id|mpu
comma
r_int
id|input
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|mpu-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpu-&gt;timer_invoked
op_eq
l_int|0
)paren
(brace
id|init_timer
c_func
(paren
op_amp
id|mpu-&gt;timer
)paren
suffix:semicolon
id|mpu-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|mpu
suffix:semicolon
id|mpu-&gt;timer.function
op_assign
id|snd_mpu401_uart_timer
suffix:semicolon
id|mpu-&gt;timer.expires
op_assign
l_int|1
op_plus
id|jiffies
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|mpu-&gt;timer
)paren
suffix:semicolon
)brace
id|mpu-&gt;timer_invoked
op_or_assign
id|input
ques
c_cond
id|MPU401_MODE_INPUT_TIMER
suffix:colon
id|MPU401_MODE_OUTPUT_TIMER
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|mpu-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * remove the timer callback if still active&n; */
DECL|function|snd_mpu401_uart_remove_timer
r_static
r_void
id|snd_mpu401_uart_remove_timer
(paren
id|mpu401_t
op_star
id|mpu
comma
r_int
id|input
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
(paren
op_amp
id|mpu-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpu-&gt;timer_invoked
)paren
(brace
id|mpu-&gt;timer_invoked
op_and_assign
id|input
ques
c_cond
op_complement
id|MPU401_MODE_INPUT_TIMER
suffix:colon
op_complement
id|MPU401_MODE_OUTPUT_TIMER
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mpu-&gt;timer_invoked
)paren
id|del_timer
c_func
(paren
op_amp
id|mpu-&gt;timer
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
(paren
op_amp
id|mpu-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&n; */
DECL|function|snd_mpu401_uart_cmd
r_static
r_void
id|snd_mpu401_uart_cmd
c_func
(paren
id|mpu401_t
op_star
id|mpu
comma
r_int
r_char
id|cmd
comma
r_int
id|ack
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|timeout
comma
id|ok
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mpu-&gt;input_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpu-&gt;hardware
op_ne
id|MPU401_HW_TRID4DWAVE
)paren
(brace
id|mpu
op_member_access_from_pointer
id|write
c_func
(paren
id|mpu
comma
l_int|0x00
comma
id|MPU401D
c_func
(paren
id|mpu
)paren
)paren
suffix:semicolon
multiline_comment|/*snd_mpu401_uart_clear_rx(mpu);*/
)brace
multiline_comment|/* ok. standard MPU-401 initialization */
r_if
c_cond
(paren
id|mpu-&gt;hardware
op_ne
id|MPU401_HW_SB
)paren
(brace
r_for
c_loop
(paren
id|timeout
op_assign
l_int|1000
suffix:semicolon
id|timeout
OG
l_int|0
op_logical_and
op_logical_neg
id|snd_mpu401_output_ready
c_func
(paren
id|mpu
)paren
suffix:semicolon
id|timeout
op_decrement
)paren
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG
r_if
c_cond
(paren
op_logical_neg
id|timeout
)paren
id|snd_printk
c_func
(paren
l_string|&quot;cmd: tx timeout (status = 0x%x)&bslash;n&quot;
comma
id|mpu
op_member_access_from_pointer
id|read
c_func
(paren
id|mpu
comma
id|MPU401C
c_func
(paren
id|mpu
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
id|mpu
op_member_access_from_pointer
id|write
c_func
(paren
id|mpu
comma
id|cmd
comma
id|MPU401C
c_func
(paren
id|mpu
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ack
)paren
(brace
id|ok
op_assign
l_int|0
suffix:semicolon
id|timeout
op_assign
l_int|10000
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|ok
op_logical_and
id|timeout
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|snd_mpu401_input_avail
c_func
(paren
id|mpu
)paren
)paren
(brace
r_if
c_cond
(paren
id|mpu
op_member_access_from_pointer
id|read
c_func
(paren
id|mpu
comma
id|MPU401D
c_func
(paren
id|mpu
)paren
)paren
op_eq
id|MPU401_ACK
)paren
id|ok
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|ok
op_logical_and
id|mpu
op_member_access_from_pointer
id|read
c_func
(paren
id|mpu
comma
id|MPU401D
c_func
(paren
id|mpu
)paren
)paren
op_eq
id|MPU401_ACK
)paren
id|ok
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|ok
op_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mpu-&gt;input_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ok
)paren
id|snd_printk
c_func
(paren
l_string|&quot;cmd: 0x%x failed at 0x%lx (status = 0x%x, data = 0x%x)&bslash;n&quot;
comma
id|cmd
comma
id|mpu-&gt;port
comma
id|mpu
op_member_access_from_pointer
id|read
c_func
(paren
id|mpu
comma
id|MPU401C
c_func
(paren
id|mpu
)paren
)paren
comma
id|mpu
op_member_access_from_pointer
id|read
c_func
(paren
id|mpu
comma
id|MPU401D
c_func
(paren
id|mpu
)paren
)paren
)paren
suffix:semicolon
singleline_comment|// snd_printk(&quot;cmd: 0x%x at 0x%lx (status = 0x%x, data = 0x%x)&bslash;n&quot;, cmd, mpu-&gt;port, mpu-&gt;read(mpu, MPU401C(mpu)), mpu-&gt;read(mpu, MPU401D(mpu)));
)brace
multiline_comment|/*&n; * input/output open/close - protected by open_mutex in rawmidi.c&n; */
DECL|function|snd_mpu401_uart_input_open
r_static
r_int
id|snd_mpu401_uart_input_open
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
(brace
id|mpu401_t
op_star
id|mpu
suffix:semicolon
r_int
id|err
suffix:semicolon
id|mpu
op_assign
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|mpu-&gt;open_input
op_logical_and
(paren
id|err
op_assign
id|mpu
op_member_access_from_pointer
id|open_input
c_func
(paren
id|mpu
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|MPU401_MODE_BIT_OUTPUT
comma
op_amp
id|mpu-&gt;mode
)paren
)paren
(brace
id|snd_mpu401_uart_cmd
c_func
(paren
id|mpu
comma
id|MPU401_RESET
comma
l_int|1
)paren
suffix:semicolon
id|snd_mpu401_uart_cmd
c_func
(paren
id|mpu
comma
id|MPU401_ENTER_UART
comma
l_int|1
)paren
suffix:semicolon
)brace
id|mpu-&gt;substream_input
op_assign
id|substream
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|mpu-&gt;rx_loop
comma
l_int|1
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|MPU401_MODE_BIT_INPUT
comma
op_amp
id|mpu-&gt;mode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_mpu401_uart_output_open
r_static
r_int
id|snd_mpu401_uart_output_open
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
(brace
id|mpu401_t
op_star
id|mpu
suffix:semicolon
r_int
id|err
suffix:semicolon
id|mpu
op_assign
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|mpu-&gt;open_output
op_logical_and
(paren
id|err
op_assign
id|mpu
op_member_access_from_pointer
id|open_output
c_func
(paren
id|mpu
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|MPU401_MODE_BIT_INPUT
comma
op_amp
id|mpu-&gt;mode
)paren
)paren
(brace
id|snd_mpu401_uart_cmd
c_func
(paren
id|mpu
comma
id|MPU401_RESET
comma
l_int|1
)paren
suffix:semicolon
id|snd_mpu401_uart_cmd
c_func
(paren
id|mpu
comma
id|MPU401_ENTER_UART
comma
l_int|1
)paren
suffix:semicolon
)brace
id|mpu-&gt;substream_output
op_assign
id|substream
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|mpu-&gt;tx_loop
comma
l_int|1
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|MPU401_MODE_BIT_OUTPUT
comma
op_amp
id|mpu-&gt;mode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_mpu401_uart_input_close
r_static
r_int
id|snd_mpu401_uart_input_close
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
(brace
id|mpu401_t
op_star
id|mpu
suffix:semicolon
id|mpu
op_assign
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
id|clear_bit
c_func
(paren
id|MPU401_MODE_BIT_INPUT
comma
op_amp
id|mpu-&gt;mode
)paren
suffix:semicolon
id|mpu-&gt;substream_input
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|MPU401_MODE_BIT_OUTPUT
comma
op_amp
id|mpu-&gt;mode
)paren
)paren
id|snd_mpu401_uart_cmd
c_func
(paren
id|mpu
comma
id|MPU401_RESET
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpu-&gt;close_input
)paren
id|mpu
op_member_access_from_pointer
id|close_input
c_func
(paren
id|mpu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_mpu401_uart_output_close
r_static
r_int
id|snd_mpu401_uart_output_close
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
)paren
(brace
id|mpu401_t
op_star
id|mpu
suffix:semicolon
id|mpu
op_assign
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
id|clear_bit
c_func
(paren
id|MPU401_MODE_BIT_OUTPUT
comma
op_amp
id|mpu-&gt;mode
)paren
suffix:semicolon
id|mpu-&gt;substream_output
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|MPU401_MODE_BIT_INPUT
comma
op_amp
id|mpu-&gt;mode
)paren
)paren
id|snd_mpu401_uart_cmd
c_func
(paren
id|mpu
comma
id|MPU401_RESET
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpu-&gt;close_output
)paren
id|mpu
op_member_access_from_pointer
id|close_output
c_func
(paren
id|mpu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * trigger input callback&n; */
DECL|function|snd_mpu401_uart_input_trigger
r_static
r_void
id|snd_mpu401_uart_input_trigger
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
comma
r_int
id|up
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|mpu401_t
op_star
id|mpu
suffix:semicolon
r_int
id|max
op_assign
l_int|64
suffix:semicolon
id|mpu
op_assign
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|up
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|MPU401_MODE_BIT_INPUT_TRIGGER
comma
op_amp
id|mpu-&gt;mode
)paren
)paren
(brace
multiline_comment|/* first time - flush FIFO */
r_while
c_loop
(paren
id|max
op_decrement
OG
l_int|0
)paren
id|mpu
op_member_access_from_pointer
id|read
c_func
(paren
id|mpu
comma
id|MPU401D
c_func
(paren
id|mpu
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpu-&gt;irq
OL
l_int|0
)paren
id|snd_mpu401_uart_add_timer
c_func
(paren
id|mpu
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* read data in advance */
multiline_comment|/* prevent double enter via rawmidi-&gt;event callback */
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|mpu-&gt;rx_loop
)paren
)paren
(brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|spin_trylock
c_func
(paren
op_amp
id|mpu-&gt;input_lock
)paren
)paren
(brace
id|snd_mpu401_uart_input_read
c_func
(paren
id|mpu
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mpu-&gt;input_lock
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|mpu-&gt;rx_loop
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|mpu-&gt;irq
OL
l_int|0
)paren
id|snd_mpu401_uart_remove_timer
c_func
(paren
id|mpu
comma
l_int|1
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|MPU401_MODE_BIT_INPUT_TRIGGER
comma
op_amp
id|mpu-&gt;mode
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * transfer input pending data&n; * call with input_lock spinlock held&n; */
DECL|function|snd_mpu401_uart_input_read
r_static
r_void
id|snd_mpu401_uart_input_read
c_func
(paren
id|mpu401_t
op_star
id|mpu
)paren
(brace
r_int
id|max
op_assign
l_int|128
suffix:semicolon
r_int
r_char
id|byte
suffix:semicolon
r_while
c_loop
(paren
id|max
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|snd_mpu401_input_avail
c_func
(paren
id|mpu
)paren
)paren
(brace
id|byte
op_assign
id|mpu
op_member_access_from_pointer
id|read
c_func
(paren
id|mpu
comma
id|MPU401D
c_func
(paren
id|mpu
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|MPU401_MODE_BIT_INPUT_TRIGGER
comma
op_amp
id|mpu-&gt;mode
)paren
)paren
id|snd_rawmidi_receive
c_func
(paren
id|mpu-&gt;substream_input
comma
op_amp
id|byte
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
r_break
suffix:semicolon
multiline_comment|/* input not available */
)brace
)brace
)brace
multiline_comment|/*&n; *  Tx FIFO sizes:&n; *    CS4237B&t;&t;&t;- 16 bytes&n; *    AudioDrive ES1688         - 12 bytes&n; *    S3 SonicVibes             -  8 bytes&n; *    SoundBlaster AWE 64       -  2 bytes (ugly hardware)&n; */
multiline_comment|/*&n; * write output pending bytes&n; * call with output_lock spinlock held&n; */
DECL|function|snd_mpu401_uart_output_write
r_static
r_void
id|snd_mpu401_uart_output_write
c_func
(paren
id|mpu401_t
op_star
id|mpu
)paren
(brace
r_int
r_char
id|byte
suffix:semicolon
r_int
id|max
op_assign
l_int|256
comma
id|timeout
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|snd_rawmidi_transmit_peek
c_func
(paren
id|mpu-&gt;substream_output
comma
op_amp
id|byte
comma
l_int|1
)paren
op_eq
l_int|1
)paren
(brace
r_for
c_loop
(paren
id|timeout
op_assign
l_int|100
suffix:semicolon
id|timeout
OG
l_int|0
suffix:semicolon
id|timeout
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|snd_mpu401_output_ready
c_func
(paren
id|mpu
)paren
)paren
(brace
id|mpu
op_member_access_from_pointer
id|write
c_func
(paren
id|mpu
comma
id|byte
comma
id|MPU401D
c_func
(paren
id|mpu
)paren
)paren
suffix:semicolon
id|snd_rawmidi_transmit_ack
c_func
(paren
id|mpu-&gt;substream_output
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|timeout
op_eq
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* Tx FIFO full - try again later */
)brace
r_else
(brace
id|snd_mpu401_uart_remove_timer
(paren
id|mpu
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* no other data - leave the tx loop */
)brace
)brace
r_while
c_loop
(paren
op_decrement
id|max
OG
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * output trigger callback&n; */
DECL|function|snd_mpu401_uart_output_trigger
r_static
r_void
id|snd_mpu401_uart_output_trigger
c_func
(paren
id|snd_rawmidi_substream_t
op_star
id|substream
comma
r_int
id|up
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|mpu401_t
op_star
id|mpu
suffix:semicolon
id|mpu
op_assign
id|substream-&gt;rmidi-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|up
)paren
(brace
id|set_bit
c_func
(paren
id|MPU401_MODE_BIT_OUTPUT_TRIGGER
comma
op_amp
id|mpu-&gt;mode
)paren
suffix:semicolon
multiline_comment|/* try to add the timer at each output trigger,&n;&t;&t; * since the output timer might have been removed in&n;&t;&t; * snd_mpu401_uart_output_write().&n;&t;&t; */
id|snd_mpu401_uart_add_timer
c_func
(paren
id|mpu
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* output pending data */
multiline_comment|/* prevent double enter via rawmidi-&gt;event callback */
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|mpu-&gt;tx_loop
)paren
)paren
(brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|spin_trylock
c_func
(paren
op_amp
id|mpu-&gt;output_lock
)paren
)paren
(brace
id|snd_mpu401_uart_output_write
c_func
(paren
id|mpu
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mpu-&gt;output_lock
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|mpu-&gt;tx_loop
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_mpu401_uart_remove_timer
c_func
(paren
id|mpu
comma
l_int|0
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|MPU401_MODE_BIT_OUTPUT_TRIGGER
comma
op_amp
id|mpu-&gt;mode
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&n; */
DECL|variable|snd_mpu401_uart_output
r_static
id|snd_rawmidi_ops_t
id|snd_mpu401_uart_output
op_assign
(brace
dot
id|open
op_assign
id|snd_mpu401_uart_output_open
comma
dot
id|close
op_assign
id|snd_mpu401_uart_output_close
comma
dot
id|trigger
op_assign
id|snd_mpu401_uart_output_trigger
comma
)brace
suffix:semicolon
DECL|variable|snd_mpu401_uart_input
r_static
id|snd_rawmidi_ops_t
id|snd_mpu401_uart_input
op_assign
(brace
dot
id|open
op_assign
id|snd_mpu401_uart_input_open
comma
dot
id|close
op_assign
id|snd_mpu401_uart_input_close
comma
dot
id|trigger
op_assign
id|snd_mpu401_uart_input_trigger
comma
)brace
suffix:semicolon
DECL|function|snd_mpu401_uart_free
r_static
r_void
id|snd_mpu401_uart_free
c_func
(paren
id|snd_rawmidi_t
op_star
id|rmidi
)paren
(brace
id|mpu401_t
op_star
id|mpu
op_assign
id|rmidi-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|mpu-&gt;irq_flags
op_logical_and
id|mpu-&gt;irq
op_ge
l_int|0
)paren
id|free_irq
c_func
(paren
id|mpu-&gt;irq
comma
(paren
r_void
op_star
)paren
id|mpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpu-&gt;res
)paren
(brace
id|release_resource
c_func
(paren
id|mpu-&gt;res
)paren
suffix:semicolon
id|kfree_nocheck
c_func
(paren
id|mpu-&gt;res
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|mpu
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * snd_mpu401_uart_new - create an MPU401-UART instance&n; * @card: the card instance&n; * @device: the device index, zero-based&n; * @hardware: the hardware type, MPU401_HW_XXXX&n; * @port: the base address of MPU401 port&n; * @integrated: non-zero if the port was already reserved by the chip&n; * @irq: the irq number, -1 if no interrupt for mpu&n; * @irq_flags: the irq request flags (SA_XXX), 0 if irq was already reserved.&n; * @rrawmidi: the pointer to store the new rawmidi instance&n; *&n; * Creates a new MPU-401 instance.&n; *&n; * Note that the rawmidi instance is returned on the rrawmidi argument,&n; * not the mpu401 instance itself.  To access to the mpu401 instance,&n; * cast from rawmidi-&gt;private_data (with mpu401_t magic-cast).&n; *&n; * Returns zero if successful, or a negative error code.&n; */
DECL|function|snd_mpu401_uart_new
r_int
id|snd_mpu401_uart_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
id|device
comma
r_int
r_int
id|hardware
comma
r_int
r_int
id|port
comma
r_int
id|integrated
comma
r_int
id|irq
comma
r_int
id|irq_flags
comma
id|snd_rawmidi_t
op_star
op_star
id|rrawmidi
)paren
(brace
id|mpu401_t
op_star
id|mpu
suffix:semicolon
id|snd_rawmidi_t
op_star
id|rmidi
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|rrawmidi
)paren
op_star
id|rrawmidi
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_rawmidi_new
c_func
(paren
id|card
comma
l_string|&quot;MPU-401U&quot;
comma
id|device
comma
l_int|1
comma
l_int|1
comma
op_amp
id|rmidi
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|mpu
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|mpu
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpu
op_eq
l_int|NULL
)paren
(brace
id|snd_device_free
c_func
(paren
id|card
comma
id|rmidi
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|rmidi-&gt;private_data
op_assign
id|mpu
suffix:semicolon
id|rmidi-&gt;private_free
op_assign
id|snd_mpu401_uart_free
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|mpu-&gt;input_lock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|mpu-&gt;output_lock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|mpu-&gt;timer_lock
)paren
suffix:semicolon
id|mpu-&gt;hardware
op_assign
id|hardware
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|integrated
)paren
(brace
r_int
id|res_size
op_assign
id|hardware
op_eq
id|MPU401_HW_PC98II
ques
c_cond
l_int|4
suffix:colon
l_int|2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mpu-&gt;res
op_assign
id|request_region
c_func
(paren
id|port
comma
id|res_size
comma
l_string|&quot;MPU401 UART&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mpu401_uart: unable to grab port 0x%lx size %d&bslash;n&quot;
comma
id|port
comma
id|res_size
)paren
suffix:semicolon
id|snd_device_free
c_func
(paren
id|card
comma
id|rmidi
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|hardware
)paren
(brace
r_case
id|MPU401_HW_AUREAL
suffix:colon
id|mpu-&gt;write
op_assign
id|mpu401_write_mmio
suffix:semicolon
id|mpu-&gt;read
op_assign
id|mpu401_read_mmio
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|mpu-&gt;write
op_assign
id|mpu401_write_port
suffix:semicolon
id|mpu-&gt;read
op_assign
id|mpu401_read_port
suffix:semicolon
r_break
suffix:semicolon
)brace
id|mpu-&gt;port
op_assign
id|port
suffix:semicolon
r_if
c_cond
(paren
id|hardware
op_eq
id|MPU401_HW_PC98II
)paren
id|mpu-&gt;cport
op_assign
id|port
op_plus
l_int|2
suffix:semicolon
r_else
id|mpu-&gt;cport
op_assign
id|port
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
l_int|0
op_logical_and
id|irq_flags
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
id|snd_mpu401_uart_interrupt
comma
id|irq_flags
comma
l_string|&quot;MPU401 UART&quot;
comma
(paren
r_void
op_star
)paren
id|mpu
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mpu401_uart: unable to grab IRQ %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|snd_device_free
c_func
(paren
id|card
comma
id|rmidi
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
id|mpu-&gt;irq
op_assign
id|irq
suffix:semicolon
id|mpu-&gt;irq_flags
op_assign
id|irq_flags
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;shortname
(braket
l_int|0
)braket
)paren
id|snprintf
c_func
(paren
id|rmidi-&gt;name
comma
r_sizeof
(paren
id|rmidi-&gt;name
)paren
comma
l_string|&quot;%s MIDI&quot;
comma
id|card-&gt;shortname
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|rmidi-&gt;name
comma
l_string|&quot;MPU-401 MIDI %d-%d&quot;
comma
id|card-&gt;number
comma
id|device
)paren
suffix:semicolon
id|snd_rawmidi_set_ops
c_func
(paren
id|rmidi
comma
id|SNDRV_RAWMIDI_STREAM_OUTPUT
comma
op_amp
id|snd_mpu401_uart_output
)paren
suffix:semicolon
id|snd_rawmidi_set_ops
c_func
(paren
id|rmidi
comma
id|SNDRV_RAWMIDI_STREAM_INPUT
comma
op_amp
id|snd_mpu401_uart_input
)paren
suffix:semicolon
id|rmidi-&gt;info_flags
op_or_assign
id|SNDRV_RAWMIDI_INFO_OUTPUT
op_or
id|SNDRV_RAWMIDI_INFO_INPUT
op_or
id|SNDRV_RAWMIDI_INFO_DUPLEX
suffix:semicolon
id|mpu-&gt;rmidi
op_assign
id|rmidi
suffix:semicolon
r_if
c_cond
(paren
id|rrawmidi
)paren
op_star
id|rrawmidi
op_assign
id|rmidi
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|snd_mpu401_uart_interrupt
id|EXPORT_SYMBOL
c_func
(paren
id|snd_mpu401_uart_interrupt
)paren
suffix:semicolon
DECL|variable|snd_mpu401_uart_new
id|EXPORT_SYMBOL
c_func
(paren
id|snd_mpu401_uart_new
)paren
suffix:semicolon
multiline_comment|/*&n; *  INIT part&n; */
DECL|function|alsa_mpu401_uart_init
r_static
r_int
id|__init
id|alsa_mpu401_uart_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_mpu401_uart_exit
r_static
r_void
id|__exit
id|alsa_mpu401_uart_exit
c_func
(paren
r_void
)paren
(brace
)brace
id|module_init
c_func
(paren
id|alsa_mpu401_uart_init
)paren
id|module_exit
c_func
(paren
id|alsa_mpu401_uart_exit
)paren
eof
