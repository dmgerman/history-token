multiline_comment|/*&n; * $Id: cx88-mpeg.c,v 1.14 2004/10/25 11:26:36 kraxel Exp $&n; *&n; *  Support for the mpeg transport stream transfers&n; *  PCI function #2 of the cx2388x.&n; *&n; *    (c) 2004 Jelle Foks &lt;jelle@foks.8m.com&gt;&n; *    (c) 2004 Chris Pascoe &lt;c.pascoe@itee.uq.edu.au&gt;&n; *    (c) 2004 Gerd Knorr &lt;kraxel@bytesex.org&gt;&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &quot;cx88.h&quot;
multiline_comment|/* ------------------------------------------------------------------ */
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;mpeg driver for cx2388x based TV cards&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jelle Foks &lt;jelle@foks.8m.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Chris Pascoe &lt;c.pascoe@itee.uq.edu.au&gt;&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Gerd Knorr &lt;kraxel@bytesex.org&gt; [SuSE Labs]&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|debug
r_static
r_int
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|debug
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|debug
comma
l_string|&quot;enable debug messages [mpeg]&quot;
)paren
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk(level,fmt, arg...)&t;if (debug &gt;= level) &bslash;&n;&t;printk(KERN_DEBUG &quot;%s/2: &quot; fmt, dev-&gt;core-&gt;name , ## arg)
multiline_comment|/* ------------------------------------------------------------------ */
DECL|function|cx8802_start_dma
r_static
r_int
id|cx8802_start_dma
c_func
(paren
r_struct
id|cx8802_dev
op_star
id|dev
comma
r_struct
id|cx88_dmaqueue
op_star
id|q
comma
r_struct
id|cx88_buffer
op_star
id|buf
)paren
(brace
r_struct
id|cx88_core
op_star
id|core
op_assign
id|dev-&gt;core
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
l_string|&quot;cx8802_start_mpegport_dma %d&bslash;n&quot;
comma
id|buf-&gt;vb.width
)paren
suffix:semicolon
multiline_comment|/* setup fifo + format */
id|cx88_sram_channel_setup
c_func
(paren
id|core
comma
op_amp
id|cx88_sram_channels
(braket
id|SRAM_CH28
)braket
comma
id|dev-&gt;ts_packet_size
comma
id|buf-&gt;risc.dma
)paren
suffix:semicolon
multiline_comment|/* write TS length to chip */
id|cx_write
c_func
(paren
id|MO_TS_LNGTH
comma
id|buf-&gt;vb.width
)paren
suffix:semicolon
macro_line|#if 1
multiline_comment|/* FIXME: this needs a review.&n;&t; * also: move to cx88-blackbird + cx88-dvb source files? */
r_if
c_cond
(paren
id|cx88_boards
(braket
id|core-&gt;board
)braket
dot
id|dvb
)paren
(brace
multiline_comment|/* Setup TS portion of chip */
id|cx_write
c_func
(paren
id|TS_GEN_CNTRL
comma
l_int|0x0c
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cx88_boards
(braket
id|core-&gt;board
)braket
dot
id|blackbird
)paren
(brace
id|cx_write
c_func
(paren
id|MO_PINMUX_IO
comma
l_int|0x88
)paren
suffix:semicolon
multiline_comment|/* enable MPEG parallel IO */
singleline_comment|// cx_write(TS_F2_CMD_STAT_MM, 0x2900106); /* F2_CMD_STAT_MM defaults + master + memory space */
id|cx_write
c_func
(paren
id|TS_GEN_CNTRL
comma
l_int|0x46
)paren
suffix:semicolon
multiline_comment|/* punctured clock TS &amp; posedge driven &amp; software reset */
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|cx_write
c_func
(paren
id|TS_HW_SOP_CNTRL
comma
l_int|0x408
)paren
suffix:semicolon
multiline_comment|/* mpeg start byte */
singleline_comment|//cx_write(TS_HW_SOP_CNTRL, 0x2F0BC0); /* mpeg start byte ts: 0x2F0BC0 ? */
id|cx_write
c_func
(paren
id|TS_VALERR_CNTRL
comma
l_int|0x2000
)paren
suffix:semicolon
id|cx_write
c_func
(paren
id|TS_GEN_CNTRL
comma
l_int|0x06
)paren
suffix:semicolon
multiline_comment|/* punctured clock TS &amp; posedge driven */
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* reset counter */
id|cx_write
c_func
(paren
id|MO_TS_GPCNTRL
comma
id|GP_COUNT_CONTROL_RESET
)paren
suffix:semicolon
id|q-&gt;count
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* enable irqs */
id|cx_set
c_func
(paren
id|MO_PCI_INTMSK
comma
l_int|0x00fc04
)paren
suffix:semicolon
id|cx_write
c_func
(paren
id|MO_TS_INTMSK
comma
l_int|0x1f0011
)paren
suffix:semicolon
multiline_comment|/* start dma */
id|cx_write
c_func
(paren
id|MO_DEV_CNTRL2
comma
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
multiline_comment|/* FIXME: s/write/set/ ??? */
id|cx_write
c_func
(paren
id|MO_TS_DMACNTRL
comma
l_int|0x11
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx8802_stop_dma
r_static
r_int
id|cx8802_stop_dma
c_func
(paren
r_struct
id|cx8802_dev
op_star
id|dev
)paren
(brace
r_struct
id|cx88_core
op_star
id|core
op_assign
id|dev-&gt;core
suffix:semicolon
multiline_comment|/* stop dma */
id|cx_clear
c_func
(paren
id|MO_TS_DMACNTRL
comma
l_int|0x11
)paren
suffix:semicolon
multiline_comment|/* disable irqs */
id|cx_clear
c_func
(paren
id|MO_PCI_INTMSK
comma
l_int|0x000004
)paren
suffix:semicolon
id|cx_clear
c_func
(paren
id|MO_TS_INTMSK
comma
l_int|0x1f0011
)paren
suffix:semicolon
multiline_comment|/* Reset the controller */
id|cx_write
c_func
(paren
id|TS_GEN_CNTRL
comma
l_int|0xcd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx8802_restart_queue
r_static
r_int
id|cx8802_restart_queue
c_func
(paren
r_struct
id|cx8802_dev
op_star
id|dev
comma
r_struct
id|cx88_dmaqueue
op_star
id|q
)paren
(brace
r_struct
id|cx88_buffer
op_star
id|buf
suffix:semicolon
r_struct
id|list_head
op_star
id|item
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|q-&gt;active
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|buf
op_assign
id|list_entry
c_func
(paren
id|q-&gt;active.next
comma
r_struct
id|cx88_buffer
comma
id|vb.queue
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;restart_queue [%p/%d]: restart dma&bslash;n&quot;
comma
id|buf
comma
id|buf-&gt;vb.i
)paren
suffix:semicolon
id|cx8802_start_dma
c_func
(paren
id|dev
comma
id|q
comma
id|buf
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|item
comma
op_amp
id|q-&gt;active
)paren
(brace
id|buf
op_assign
id|list_entry
c_func
(paren
id|item
comma
r_struct
id|cx88_buffer
comma
id|vb.queue
)paren
suffix:semicolon
id|buf-&gt;count
op_assign
id|q-&gt;count
op_increment
suffix:semicolon
)brace
id|mod_timer
c_func
(paren
op_amp
id|q-&gt;timeout
comma
id|jiffies
op_plus
id|BUFFER_TIMEOUT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------------ */
DECL|function|cx8802_buf_prepare
r_int
id|cx8802_buf_prepare
c_func
(paren
r_struct
id|cx8802_dev
op_star
id|dev
comma
r_struct
id|cx88_buffer
op_star
id|buf
)paren
(brace
r_int
id|size
op_assign
id|dev-&gt;ts_packet_size
op_star
id|dev-&gt;ts_packet_count
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
l_string|&quot;%s: %p&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|buf-&gt;vb.baddr
op_logical_and
id|buf-&gt;vb.bsize
OL
id|size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|STATE_NEEDS_INIT
op_eq
id|buf-&gt;vb.state
)paren
(brace
id|buf-&gt;vb.width
op_assign
id|dev-&gt;ts_packet_size
suffix:semicolon
id|buf-&gt;vb.height
op_assign
id|dev-&gt;ts_packet_count
suffix:semicolon
id|buf-&gt;vb.size
op_assign
id|size
suffix:semicolon
id|buf-&gt;vb.field
op_assign
id|V4L2_FIELD_TOP
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|rc
op_assign
id|videobuf_iolock
c_func
(paren
id|dev-&gt;pci
comma
op_amp
id|buf-&gt;vb
comma
l_int|NULL
)paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|cx88_risc_databuffer
c_func
(paren
id|dev-&gt;pci
comma
op_amp
id|buf-&gt;risc
comma
id|buf-&gt;vb.dma.sglist
comma
id|buf-&gt;vb.width
comma
id|buf-&gt;vb.height
)paren
suffix:semicolon
)brace
id|buf-&gt;vb.state
op_assign
id|STATE_PREPARED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|cx88_free_buffer
c_func
(paren
id|dev-&gt;pci
comma
id|buf
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|cx8802_buf_queue
r_void
id|cx8802_buf_queue
c_func
(paren
r_struct
id|cx8802_dev
op_star
id|dev
comma
r_struct
id|cx88_buffer
op_star
id|buf
)paren
(brace
r_struct
id|cx88_buffer
op_star
id|prev
suffix:semicolon
r_struct
id|cx88_dmaqueue
op_star
id|q
op_assign
op_amp
id|dev-&gt;mpegq
suffix:semicolon
multiline_comment|/* add jump to stopper */
id|buf-&gt;risc.jmp
(braket
l_int|0
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|RISC_JUMP
op_or
id|RISC_IRQ1
op_or
id|RISC_CNT_INC
)paren
suffix:semicolon
id|buf-&gt;risc.jmp
(braket
l_int|1
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|q-&gt;stopper.dma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|q-&gt;active
)paren
)paren
(brace
id|list_add_tail
c_func
(paren
op_amp
id|buf-&gt;vb.queue
comma
op_amp
id|q-&gt;active
)paren
suffix:semicolon
id|cx8802_start_dma
c_func
(paren
id|dev
comma
id|q
comma
id|buf
)paren
suffix:semicolon
id|buf-&gt;vb.state
op_assign
id|STATE_ACTIVE
suffix:semicolon
id|buf-&gt;count
op_assign
id|q-&gt;count
op_increment
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|q-&gt;timeout
comma
id|jiffies
op_plus
id|BUFFER_TIMEOUT
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;[%p/%d] %s - first active&bslash;n&quot;
comma
id|buf
comma
id|buf-&gt;vb.i
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
r_else
(brace
id|prev
op_assign
id|list_entry
c_func
(paren
id|q-&gt;active.prev
comma
r_struct
id|cx88_buffer
comma
id|vb.queue
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|buf-&gt;vb.queue
comma
op_amp
id|q-&gt;active
)paren
suffix:semicolon
id|buf-&gt;vb.state
op_assign
id|STATE_ACTIVE
suffix:semicolon
id|buf-&gt;count
op_assign
id|q-&gt;count
op_increment
suffix:semicolon
id|prev-&gt;risc.jmp
(braket
l_int|1
)braket
op_assign
id|cpu_to_le32
c_func
(paren
id|buf-&gt;risc.dma
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;[%p/%d] %s - append to active&bslash;n&quot;
comma
id|buf
comma
id|buf-&gt;vb.i
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* ----------------------------------------------------------- */
DECL|function|do_cancel_buffers
r_static
r_void
id|do_cancel_buffers
c_func
(paren
r_struct
id|cx8802_dev
op_star
id|dev
comma
r_char
op_star
id|reason
comma
r_int
id|restart
)paren
(brace
r_struct
id|cx88_dmaqueue
op_star
id|q
op_assign
op_amp
id|dev-&gt;mpegq
suffix:semicolon
r_struct
id|cx88_buffer
op_star
id|buf
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|dev-&gt;slock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|q-&gt;active
)paren
)paren
(brace
id|buf
op_assign
id|list_entry
c_func
(paren
id|q-&gt;active.next
comma
r_struct
id|cx88_buffer
comma
id|vb.queue
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|buf-&gt;vb.queue
)paren
suffix:semicolon
id|buf-&gt;vb.state
op_assign
id|STATE_ERROR
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|buf-&gt;vb.done
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
l_string|&quot;[%p/%d] %s - dma=0x%08lx&bslash;n&quot;
comma
id|buf
comma
id|buf-&gt;vb.i
comma
id|reason
comma
(paren
r_int
r_int
)paren
id|buf-&gt;risc.dma
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|restart
)paren
id|cx8802_restart_queue
c_func
(paren
id|dev
comma
id|q
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|dev-&gt;slock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|cx8802_cancel_buffers
r_void
id|cx8802_cancel_buffers
c_func
(paren
r_struct
id|cx8802_dev
op_star
id|dev
)paren
(brace
r_struct
id|cx88_dmaqueue
op_star
id|q
op_assign
op_amp
id|dev-&gt;mpegq
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|q-&gt;timeout
)paren
suffix:semicolon
id|cx8802_stop_dma
c_func
(paren
id|dev
)paren
suffix:semicolon
id|do_cancel_buffers
c_func
(paren
id|dev
comma
l_string|&quot;cancel&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|cx8802_timeout
r_static
r_void
id|cx8802_timeout
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|cx8802_dev
op_star
id|dev
op_assign
(paren
r_struct
id|cx8802_dev
op_star
)paren
id|data
suffix:semicolon
id|dprintk
c_func
(paren
l_int|1
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
)paren
id|cx88_sram_channel_dump
c_func
(paren
id|dev-&gt;core
comma
op_amp
id|cx88_sram_channels
(braket
id|SRAM_CH28
)braket
)paren
suffix:semicolon
id|cx8802_stop_dma
c_func
(paren
id|dev
)paren
suffix:semicolon
id|do_cancel_buffers
c_func
(paren
id|dev
comma
l_string|&quot;timeout&quot;
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|cx8802_mpeg_irq
r_static
r_void
id|cx8802_mpeg_irq
c_func
(paren
r_struct
id|cx8802_dev
op_star
id|dev
)paren
(brace
r_struct
id|cx88_core
op_star
id|core
op_assign
id|dev-&gt;core
suffix:semicolon
id|u32
id|status
comma
id|mask
comma
id|count
suffix:semicolon
id|status
op_assign
id|cx_read
c_func
(paren
id|MO_TS_INTSTAT
)paren
suffix:semicolon
id|mask
op_assign
id|cx_read
c_func
(paren
id|MO_TS_INTMSK
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
(paren
id|status
op_amp
id|mask
)paren
)paren
r_return
suffix:semicolon
id|cx_write
c_func
(paren
id|MO_TS_INTSTAT
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug
op_logical_or
(paren
id|status
op_amp
id|mask
op_amp
op_complement
l_int|0xff
)paren
)paren
id|cx88_print_irqbits
c_func
(paren
id|core-&gt;name
comma
l_string|&quot;irq mpeg &quot;
comma
id|cx88_mpeg_irqs
comma
id|status
comma
id|mask
)paren
suffix:semicolon
multiline_comment|/* risc op code error */
r_if
c_cond
(paren
id|status
op_amp
(paren
l_int|1
op_lshift
l_int|16
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: mpeg risc op code error&bslash;n&quot;
comma
id|core-&gt;name
)paren
suffix:semicolon
id|cx_clear
c_func
(paren
id|MO_TS_DMACNTRL
comma
l_int|0x11
)paren
suffix:semicolon
id|cx88_sram_channel_dump
c_func
(paren
id|dev-&gt;core
comma
op_amp
id|cx88_sram_channels
(braket
id|SRAM_CH28
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* risc1 y */
r_if
c_cond
(paren
id|status
op_amp
l_int|0x01
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
suffix:semicolon
id|count
op_assign
id|cx_read
c_func
(paren
id|MO_TS_GPCNT
)paren
suffix:semicolon
id|cx88_wakeup
c_func
(paren
id|dev-&gt;core
comma
op_amp
id|dev-&gt;mpegq
comma
id|count
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
suffix:semicolon
)brace
multiline_comment|/* risc2 y */
r_if
c_cond
(paren
id|status
op_amp
l_int|0x10
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
suffix:semicolon
id|cx8802_restart_queue
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;mpegq
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
suffix:semicolon
)brace
multiline_comment|/* other general errors */
r_if
c_cond
(paren
id|status
op_amp
l_int|0x1f0100
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
suffix:semicolon
id|cx8802_stop_dma
c_func
(paren
id|dev
)paren
suffix:semicolon
id|cx8802_restart_queue
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;mpegq
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
suffix:semicolon
)brace
)brace
DECL|function|cx8802_irq
r_static
id|irqreturn_t
id|cx8802_irq
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
id|cx8802_dev
op_star
id|dev
op_assign
id|dev_id
suffix:semicolon
r_struct
id|cx88_core
op_star
id|core
op_assign
id|dev-&gt;core
suffix:semicolon
id|u32
id|status
comma
id|mask
suffix:semicolon
r_int
id|loop
comma
id|handled
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|loop
op_assign
l_int|0
suffix:semicolon
id|loop
OL
l_int|10
suffix:semicolon
id|loop
op_increment
)paren
(brace
id|status
op_assign
id|cx_read
c_func
(paren
id|MO_PCI_INTSTAT
)paren
op_amp
(paren
op_complement
l_int|0x1f
op_or
l_int|0x04
)paren
suffix:semicolon
id|mask
op_assign
id|cx_read
c_func
(paren
id|MO_PCI_INTMSK
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
(paren
id|status
op_amp
id|mask
)paren
)paren
r_goto
id|out
suffix:semicolon
id|handled
op_assign
l_int|1
suffix:semicolon
id|cx_write
c_func
(paren
id|MO_PCI_INTSTAT
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|mask
op_amp
op_complement
l_int|0x1f
)paren
id|cx88_irq
c_func
(paren
id|core
comma
id|status
comma
id|mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x04
)paren
id|cx8802_mpeg_irq
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
l_int|10
op_eq
id|loop
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s/0: irq loop -- clearing mask&bslash;n&quot;
comma
id|core-&gt;name
)paren
suffix:semicolon
id|cx_write
c_func
(paren
id|MO_PCI_INTMSK
comma
l_int|0
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|IRQ_RETVAL
c_func
(paren
id|handled
)paren
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/* exported stuff                                              */
DECL|function|cx8802_init_common
r_int
id|cx8802_init_common
c_func
(paren
r_struct
id|cx8802_dev
op_star
id|dev
)paren
(brace
r_int
id|err
suffix:semicolon
multiline_comment|/* pci init */
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|dev-&gt;pci
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|pci_set_master
c_func
(paren
id|dev-&gt;pci
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_dma_supported
c_func
(paren
id|dev-&gt;pci
comma
l_int|0xffffffff
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s/2: Oops: no 32bit PCI DMA ???&bslash;n&quot;
comma
id|dev-&gt;core-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|pci_read_config_byte
c_func
(paren
id|dev-&gt;pci
comma
id|PCI_CLASS_REVISION
comma
op_amp
id|dev-&gt;pci_rev
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev-&gt;pci
comma
id|PCI_LATENCY_TIMER
comma
op_amp
id|dev-&gt;pci_lat
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s/2: found at %s, rev: %d, irq: %d, &quot;
l_string|&quot;latency: %d, mmio: 0x%lx&bslash;n&quot;
comma
id|dev-&gt;core-&gt;name
comma
id|pci_name
c_func
(paren
id|dev-&gt;pci
)paren
comma
id|dev-&gt;pci_rev
comma
id|dev-&gt;pci-&gt;irq
comma
id|dev-&gt;pci_lat
comma
id|pci_resource_start
c_func
(paren
id|dev-&gt;pci
comma
l_int|0
)paren
)paren
suffix:semicolon
multiline_comment|/* initialize driver struct */
id|init_MUTEX
c_func
(paren
op_amp
id|dev-&gt;lock
)paren
suffix:semicolon
id|dev-&gt;slock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* init dma queue */
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;mpegq.active
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;mpegq.queued
)paren
suffix:semicolon
id|dev-&gt;mpegq.timeout.function
op_assign
id|cx8802_timeout
suffix:semicolon
id|dev-&gt;mpegq.timeout.data
op_assign
(paren
r_int
r_int
)paren
id|dev
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|dev-&gt;mpegq.timeout
)paren
suffix:semicolon
id|cx88_risc_stopper
c_func
(paren
id|dev-&gt;pci
comma
op_amp
id|dev-&gt;mpegq.stopper
comma
id|MO_TS_DMACNTRL
comma
l_int|0x11
comma
l_int|0x00
)paren
suffix:semicolon
macro_line|#if 0 /* FIXME */
multiline_comment|/* initialize hardware */
id|cx8802_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* get irq */
id|err
op_assign
id|request_irq
c_func
(paren
id|dev-&gt;pci-&gt;irq
comma
id|cx8802_irq
comma
id|SA_SHIRQ
op_or
id|SA_INTERRUPT
comma
id|dev-&gt;core-&gt;name
comma
id|dev
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
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: can&squot;t get IRQ %d&bslash;n&quot;
comma
id|dev-&gt;core-&gt;name
comma
id|dev-&gt;pci-&gt;irq
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#if 0 /* FIXME */
multiline_comment|/* register i2c bus + load i2c helpers */
id|cx88_card_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* everything worked */
id|pci_set_drvdata
c_func
(paren
id|dev-&gt;pci
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx8802_fini_common
r_void
id|cx8802_fini_common
c_func
(paren
r_struct
id|cx8802_dev
op_star
id|dev
)paren
(brace
id|cx8802_stop_dma
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pci_disable_device
c_func
(paren
id|dev-&gt;pci
)paren
suffix:semicolon
multiline_comment|/* unregister stuff */
id|free_irq
c_func
(paren
id|dev-&gt;pci-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|dev-&gt;pci
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* free memory */
id|btcx_riscmem_free
c_func
(paren
id|dev-&gt;pci
comma
op_amp
id|dev-&gt;mpegq.stopper
)paren
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------- */
DECL|function|cx8802_suspend_common
r_int
id|cx8802_suspend_common
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci_dev
comma
id|u32
id|state
)paren
(brace
r_struct
id|cx8802_dev
op_star
id|dev
op_assign
id|pci_get_drvdata
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
r_struct
id|cx88_core
op_star
id|core
op_assign
id|dev-&gt;core
suffix:semicolon
multiline_comment|/* stop mpeg dma */
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dev-&gt;mpegq.active
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: suspend mpeg&bslash;n&quot;
comma
id|core-&gt;name
)paren
suffix:semicolon
id|cx8802_stop_dma
c_func
(paren
id|dev
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|dev-&gt;mpegq.timeout
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
suffix:semicolon
macro_line|#if 1
multiline_comment|/* FIXME -- shutdown device */
id|cx88_shutdown
c_func
(paren
id|dev-&gt;core
)paren
suffix:semicolon
macro_line|#endif
id|pci_save_state
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|pci_set_power_state
c_func
(paren
id|pci_dev
comma
id|state
)paren
)paren
(brace
id|pci_disable_device
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
id|dev-&gt;state.disabled
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cx8802_resume_common
r_int
id|cx8802_resume_common
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci_dev
)paren
(brace
r_struct
id|cx8802_dev
op_star
id|dev
op_assign
id|pci_get_drvdata
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
r_struct
id|cx88_core
op_star
id|core
op_assign
id|dev-&gt;core
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;state.disabled
)paren
(brace
id|pci_enable_device
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
id|dev-&gt;state.disabled
op_assign
l_int|0
suffix:semicolon
)brace
id|pci_set_power_state
c_func
(paren
id|pci_dev
comma
l_int|0
)paren
suffix:semicolon
id|pci_restore_state
c_func
(paren
id|pci_dev
)paren
suffix:semicolon
macro_line|#if 1
multiline_comment|/* FIXME: re-initialize hardware */
id|cx88_reset
c_func
(paren
id|dev-&gt;core
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* restart video+vbi capture */
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|dev-&gt;mpegq.active
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: resume mpeg&bslash;n&quot;
comma
id|core-&gt;name
)paren
suffix:semicolon
id|cx8802_restart_queue
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;mpegq
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;slock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------- */
DECL|variable|cx8802_buf_prepare
id|EXPORT_SYMBOL
c_func
(paren
id|cx8802_buf_prepare
)paren
suffix:semicolon
DECL|variable|cx8802_buf_queue
id|EXPORT_SYMBOL
c_func
(paren
id|cx8802_buf_queue
)paren
suffix:semicolon
DECL|variable|cx8802_cancel_buffers
id|EXPORT_SYMBOL
c_func
(paren
id|cx8802_cancel_buffers
)paren
suffix:semicolon
DECL|variable|cx8802_init_common
id|EXPORT_SYMBOL
c_func
(paren
id|cx8802_init_common
)paren
suffix:semicolon
DECL|variable|cx8802_fini_common
id|EXPORT_SYMBOL
c_func
(paren
id|cx8802_fini_common
)paren
suffix:semicolon
DECL|variable|cx8802_suspend_common
id|EXPORT_SYMBOL
c_func
(paren
id|cx8802_suspend_common
)paren
suffix:semicolon
DECL|variable|cx8802_resume_common
id|EXPORT_SYMBOL
c_func
(paren
id|cx8802_resume_common
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
