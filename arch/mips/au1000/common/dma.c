multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *      A DMA channel allocator for Au1000. API is modeled loosely off of&n; *      linux/kernel/dma.c.&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;stevel@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/au1000.h&gt;
macro_line|#include &lt;asm/au1000_dma.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * A note on resource allocation:&n; *&n; * All drivers needing DMA channels, should allocate and release them&n; * through the public routines `request_dma()&squot; and `free_dma()&squot;.&n; *&n; * In order to avoid problems, all processes should allocate resources in&n; * the same sequence and release them in the reverse order.&n; *&n; * So, when allocating DMAs and IRQs, first allocate the DMA, then the IRQ.&n; * When releasing them, first release the IRQ, then release the DMA. The&n; * main reason for this order is that, if you are requesting the DMA buffer&n; * done interrupt, you won&squot;t know the irq number until the DMA channel is&n; * returned from request_dma.&n; */
DECL|variable|au1000_dma_spin_lock
id|spinlock_t
id|au1000_dma_spin_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|au1000_dma_table
r_struct
id|dma_chan
id|au1000_dma_table
(braket
id|NUM_AU1000_DMA_CHANNELS
)braket
op_assign
(brace
(brace
dot
id|dev_id
op_assign
op_minus
l_int|1
comma
)brace
comma
(brace
dot
id|dev_id
op_assign
op_minus
l_int|1
comma
)brace
comma
(brace
dot
id|dev_id
op_assign
op_minus
l_int|1
comma
)brace
comma
(brace
dot
id|dev_id
op_assign
op_minus
l_int|1
comma
)brace
comma
(brace
dot
id|dev_id
op_assign
op_minus
l_int|1
comma
)brace
comma
(brace
dot
id|dev_id
op_assign
op_minus
l_int|1
comma
)brace
comma
(brace
dot
id|dev_id
op_assign
op_minus
l_int|1
comma
)brace
comma
(brace
dot
id|dev_id
op_assign
op_minus
l_int|1
comma
)brace
)brace
suffix:semicolon
singleline_comment|// Device FIFO addresses and default DMA modes
r_static
r_const
r_struct
(brace
DECL|member|fifo_addr
r_int
r_int
id|fifo_addr
suffix:semicolon
DECL|member|dma_mode
r_int
r_int
id|dma_mode
suffix:semicolon
DECL|variable|dma_dev_table
)brace
id|dma_dev_table
(braket
id|DMA_NUM_DEV
)braket
op_assign
(brace
(brace
id|UART0_ADDR
op_plus
id|UART_TX
comma
l_int|0
)brace
comma
(brace
id|UART0_ADDR
op_plus
id|UART_RX
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
id|AC97C_DATA
comma
id|DMA_DW16
)brace
comma
singleline_comment|// coherent
(brace
id|AC97C_DATA
comma
id|DMA_DR
op_or
id|DMA_DW16
)brace
comma
singleline_comment|// coherent
(brace
id|UART3_ADDR
op_plus
id|UART_TX
comma
id|DMA_DW8
op_or
id|DMA_NC
)brace
comma
(brace
id|UART3_ADDR
op_plus
id|UART_RX
comma
id|DMA_DR
op_or
id|DMA_DW8
op_or
id|DMA_NC
)brace
comma
(brace
id|USBD_EP0RD
comma
id|DMA_DR
op_or
id|DMA_DW8
op_or
id|DMA_NC
)brace
comma
(brace
id|USBD_EP0WR
comma
id|DMA_DW8
op_or
id|DMA_NC
)brace
comma
(brace
id|USBD_EP2WR
comma
id|DMA_DW8
op_or
id|DMA_NC
)brace
comma
(brace
id|USBD_EP3WR
comma
id|DMA_DW8
op_or
id|DMA_NC
)brace
comma
(brace
id|USBD_EP4RD
comma
id|DMA_DR
op_or
id|DMA_DW8
op_or
id|DMA_NC
)brace
comma
(brace
id|USBD_EP5RD
comma
id|DMA_DR
op_or
id|DMA_DW8
op_or
id|DMA_NC
)brace
comma
(brace
id|I2S_DATA
comma
id|DMA_DW32
op_or
id|DMA_NC
)brace
comma
(brace
id|I2S_DATA
comma
id|DMA_DR
op_or
id|DMA_DW32
op_or
id|DMA_NC
)brace
)brace
suffix:semicolon
DECL|function|au1000_dma_read_proc
r_int
id|au1000_dma_read_proc
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|fpos
comma
r_int
id|length
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|i
comma
id|len
op_assign
l_int|0
suffix:semicolon
r_struct
id|dma_chan
op_star
id|chan
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
id|NUM_AU1000_DMA_CHANNELS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|chan
op_assign
id|get_dma_chan
c_func
(paren
id|i
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%2d: %s&bslash;n&quot;
comma
id|i
comma
id|chan-&gt;dev_str
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|fpos
op_ge
id|len
)paren
(brace
op_star
id|start
op_assign
id|buf
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|start
op_assign
id|buf
op_plus
id|fpos
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
id|fpos
)paren
OG
id|length
)paren
r_return
id|length
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|dump_au1000_dma_channel
r_void
id|dump_au1000_dma_channel
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_struct
id|dma_chan
op_star
id|chan
suffix:semicolon
r_if
c_cond
(paren
id|dmanr
OG
id|NUM_AU1000_DMA_CHANNELS
)paren
r_return
suffix:semicolon
id|chan
op_assign
op_amp
id|au1000_dma_table
(braket
id|dmanr
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Au1000 DMA%d Register Dump:&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;  mode = 0x%08x&bslash;n&quot;
comma
id|au_readl
c_func
(paren
id|chan-&gt;io
op_plus
id|DMA_MODE_SET
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;  addr = 0x%08x&bslash;n&quot;
comma
id|au_readl
c_func
(paren
id|chan-&gt;io
op_plus
id|DMA_PERIPHERAL_ADDR
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;  start0 = 0x%08x&bslash;n&quot;
comma
id|au_readl
c_func
(paren
id|chan-&gt;io
op_plus
id|DMA_BUFFER0_START
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;  start1 = 0x%08x&bslash;n&quot;
comma
id|au_readl
c_func
(paren
id|chan-&gt;io
op_plus
id|DMA_BUFFER1_START
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;  count0 = 0x%08x&bslash;n&quot;
comma
id|au_readl
c_func
(paren
id|chan-&gt;io
op_plus
id|DMA_BUFFER0_COUNT
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;  count1 = 0x%08x&bslash;n&quot;
comma
id|au_readl
c_func
(paren
id|chan-&gt;io
op_plus
id|DMA_BUFFER1_COUNT
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Finds a free channel, and binds the requested device to it.&n; * Returns the allocated channel number, or negative on error.&n; * Requests the DMA done IRQ if irqhandler != NULL.&n; */
DECL|function|request_au1000_dma
r_int
id|request_au1000_dma
c_func
(paren
r_int
id|dev_id
comma
r_const
r_char
op_star
id|dev_str
comma
r_void
(paren
op_star
id|irqhandler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|irqflags
comma
r_void
op_star
id|irq_dev_id
)paren
(brace
r_struct
id|dma_chan
op_star
id|chan
suffix:semicolon
r_int
id|i
comma
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|dev_id
OL
l_int|0
op_logical_or
id|dev_id
op_ge
id|DMA_NUM_DEV
)paren
r_return
op_minus
id|EINVAL
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
id|NUM_AU1000_DMA_CHANNELS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|au1000_dma_table
(braket
id|i
)braket
dot
id|dev_id
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|NUM_AU1000_DMA_CHANNELS
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|chan
op_assign
op_amp
id|au1000_dma_table
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|irqhandler
)paren
(brace
id|chan-&gt;irq
op_assign
id|AU1000_DMA_INT_BASE
op_plus
id|i
suffix:semicolon
id|chan-&gt;irq_dev
op_assign
id|irq_dev_id
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|request_irq
c_func
(paren
id|chan-&gt;irq
comma
id|irqhandler
comma
id|irqflags
comma
id|dev_str
comma
id|chan-&gt;irq_dev
)paren
)paren
)paren
(brace
id|chan-&gt;irq
op_assign
l_int|0
suffix:semicolon
id|chan-&gt;irq_dev
op_assign
l_int|NULL
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)brace
r_else
(brace
id|chan-&gt;irq
op_assign
l_int|0
suffix:semicolon
id|chan-&gt;irq_dev
op_assign
l_int|NULL
suffix:semicolon
)brace
singleline_comment|// fill it in
id|chan-&gt;io
op_assign
id|DMA_CHANNEL_BASE
op_plus
id|i
op_star
id|DMA_CHANNEL_LEN
suffix:semicolon
id|chan-&gt;dev_id
op_assign
id|dev_id
suffix:semicolon
id|chan-&gt;dev_str
op_assign
id|dev_str
suffix:semicolon
id|chan-&gt;fifo_addr
op_assign
id|dma_dev_table
(braket
id|dev_id
)braket
dot
id|fifo_addr
suffix:semicolon
id|chan-&gt;mode
op_assign
id|dma_dev_table
(braket
id|dev_id
)braket
dot
id|dma_mode
suffix:semicolon
multiline_comment|/* initialize the channel before returning */
id|init_dma
c_func
(paren
id|i
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|free_au1000_dma
r_void
id|free_au1000_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_struct
id|dma_chan
op_star
id|chan
op_assign
id|get_dma_chan
c_func
(paren
id|dmanr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chan
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free DMA%d&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|disable_dma
c_func
(paren
id|dmanr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chan-&gt;irq
)paren
id|free_irq
c_func
(paren
id|chan-&gt;irq
comma
id|chan-&gt;irq_dev
)paren
suffix:semicolon
id|chan-&gt;irq
op_assign
l_int|0
suffix:semicolon
id|chan-&gt;irq_dev
op_assign
l_int|NULL
suffix:semicolon
id|chan-&gt;dev_id
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
eof
