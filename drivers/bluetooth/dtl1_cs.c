multiline_comment|/*&n; *&n; *  A driver for Nokia Connectivity Card DTL-1 devices&n; *&n; *  Copyright (C) 2001-2002  Marcel Holtmann &lt;marcel@holtmann.org&gt;&n; *&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License version 2 as&n; *  published by the Free Software Foundation;&n; *&n; *  Software distributed under the License is distributed on an &quot;AS&n; *  IS&quot; basis, WITHOUT WARRANTY OF ANY KIND, either express or&n; *  implied. See the License for the specific language governing&n; *  rights and limitations under the License.&n; *&n; *  The initial developer of the original code is David A. Hinds&n; *  &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; *  are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/ciscode.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
macro_line|#include &lt;pcmcia/cisreg.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
macro_line|#include &lt;net/bluetooth/hci_core.h&gt;
multiline_comment|/* ======================== Module parameters ======================== */
multiline_comment|/* Bit map of interrupts to choose from */
DECL|variable|irq_mask
r_static
r_int
r_int
id|irq_mask
op_assign
l_int|0xffff
suffix:semicolon
DECL|variable|irq_list
r_static
r_int
id|irq_list
(braket
l_int|4
)braket
op_assign
(brace
op_minus
l_int|1
)brace
suffix:semicolon
id|module_param
c_func
(paren
id|irq_mask
comma
id|uint
comma
l_int|0
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|irq_list
comma
r_int
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Marcel Holtmann &lt;marcel@holtmann.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Bluetooth driver for Nokia Connectivity Card DTL-1&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* ======================== Local structures ======================== */
DECL|struct|dtl1_info_t
r_typedef
r_struct
id|dtl1_info_t
(brace
DECL|member|link
id|dev_link_t
id|link
suffix:semicolon
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
DECL|member|hdev
r_struct
id|hci_dev
op_star
id|hdev
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* For serializing operations */
DECL|member|flowmask
r_int
r_int
id|flowmask
suffix:semicolon
multiline_comment|/* HCI flow mask */
DECL|member|ri_latch
r_int
id|ri_latch
suffix:semicolon
DECL|member|txq
r_struct
id|sk_buff_head
id|txq
suffix:semicolon
DECL|member|tx_state
r_int
r_int
id|tx_state
suffix:semicolon
DECL|member|rx_state
r_int
r_int
id|rx_state
suffix:semicolon
DECL|member|rx_count
r_int
r_int
id|rx_count
suffix:semicolon
DECL|member|rx_skb
r_struct
id|sk_buff
op_star
id|rx_skb
suffix:semicolon
DECL|typedef|dtl1_info_t
)brace
id|dtl1_info_t
suffix:semicolon
r_void
id|dtl1_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_void
id|dtl1_release
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_int
id|dtl1_event
c_func
(paren
id|event_t
id|event
comma
r_int
id|priority
comma
id|event_callback_args_t
op_star
id|args
)paren
suffix:semicolon
DECL|variable|dev_info
r_static
id|dev_info_t
id|dev_info
op_assign
l_string|&quot;dtl1_cs&quot;
suffix:semicolon
id|dev_link_t
op_star
id|dtl1_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|dtl1_detach
c_func
(paren
id|dev_link_t
op_star
)paren
suffix:semicolon
DECL|variable|dev_list
r_static
id|dev_link_t
op_star
id|dev_list
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Transmit states  */
DECL|macro|XMIT_SENDING
mdefine_line|#define XMIT_SENDING  1
DECL|macro|XMIT_WAKEUP
mdefine_line|#define XMIT_WAKEUP   2
DECL|macro|XMIT_WAITING
mdefine_line|#define XMIT_WAITING  8
multiline_comment|/* Receiver States */
DECL|macro|RECV_WAIT_NSH
mdefine_line|#define RECV_WAIT_NSH   0
DECL|macro|RECV_WAIT_DATA
mdefine_line|#define RECV_WAIT_DATA  1
r_typedef
r_struct
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|zero
id|u8
id|zero
suffix:semicolon
DECL|member|len
id|u16
id|len
suffix:semicolon
DECL|typedef|nsh_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|nsh_t
suffix:semicolon
multiline_comment|/* Nokia Specific Header */
DECL|macro|NSHL
mdefine_line|#define NSHL  4&t;&t;&t;&t;/* Nokia Specific Header Length */
multiline_comment|/* ======================== Interrupt handling ======================== */
DECL|function|dtl1_write
r_static
r_int
id|dtl1_write
c_func
(paren
r_int
r_int
id|iobase
comma
r_int
id|fifo_size
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|actual
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Tx FIFO should be empty */
r_if
c_cond
(paren
op_logical_neg
(paren
id|inb
c_func
(paren
id|iobase
op_plus
id|UART_LSR
)paren
op_amp
id|UART_LSR_THRE
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Fill FIFO with current frame */
r_while
c_loop
(paren
(paren
id|fifo_size
op_decrement
OG
l_int|0
)paren
op_logical_and
(paren
id|actual
OL
id|len
)paren
)paren
(brace
multiline_comment|/* Transmit next byte */
id|outb
c_func
(paren
id|buf
(braket
id|actual
)braket
comma
id|iobase
op_plus
id|UART_TX
)paren
suffix:semicolon
id|actual
op_increment
suffix:semicolon
)brace
r_return
id|actual
suffix:semicolon
)brace
DECL|function|dtl1_write_wakeup
r_static
r_void
id|dtl1_write_wakeup
c_func
(paren
id|dtl1_info_t
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Unknown device&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|XMIT_WAITING
comma
op_amp
(paren
id|info-&gt;tx_state
)paren
)paren
)paren
(brace
id|set_bit
c_func
(paren
id|XMIT_WAKEUP
comma
op_amp
(paren
id|info-&gt;tx_state
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|XMIT_SENDING
comma
op_amp
(paren
id|info-&gt;tx_state
)paren
)paren
)paren
(brace
id|set_bit
c_func
(paren
id|XMIT_WAKEUP
comma
op_amp
(paren
id|info-&gt;tx_state
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_do
(brace
r_register
r_int
r_int
id|iobase
op_assign
id|info-&gt;link.io.BasePort1
suffix:semicolon
r_register
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_register
r_int
id|len
suffix:semicolon
id|clear_bit
c_func
(paren
id|XMIT_WAKEUP
comma
op_amp
(paren
id|info-&gt;tx_state
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|info-&gt;link.state
op_amp
id|DEV_PRESENT
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
(paren
id|info-&gt;txq
)paren
)paren
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* Send frame */
id|len
op_assign
id|dtl1_write
c_func
(paren
id|iobase
comma
l_int|32
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
id|skb-&gt;len
)paren
(brace
id|set_bit
c_func
(paren
id|XMIT_WAITING
comma
op_amp
(paren
id|info-&gt;tx_state
)paren
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
id|skb_pull
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
id|skb_queue_head
c_func
(paren
op_amp
(paren
id|info-&gt;txq
)paren
comma
id|skb
)paren
suffix:semicolon
)brace
id|info-&gt;hdev-&gt;stat.byte_tx
op_add_assign
id|len
suffix:semicolon
)brace
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|XMIT_WAKEUP
comma
op_amp
(paren
id|info-&gt;tx_state
)paren
)paren
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|XMIT_SENDING
comma
op_amp
(paren
id|info-&gt;tx_state
)paren
)paren
suffix:semicolon
)brace
DECL|function|dtl1_control
r_static
r_void
id|dtl1_control
c_func
(paren
id|dtl1_info_t
op_star
id|info
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|u8
id|flowmask
op_assign
op_star
(paren
id|u8
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Bluetooth: Nokia control data =&quot;
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
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|skb-&gt;data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* transition to active state */
r_if
c_cond
(paren
(paren
(paren
id|info-&gt;flowmask
op_amp
l_int|0x07
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
(paren
id|flowmask
op_amp
l_int|0x07
)paren
op_ne
l_int|0
)paren
)paren
(brace
id|clear_bit
c_func
(paren
id|XMIT_WAITING
comma
op_amp
(paren
id|info-&gt;tx_state
)paren
)paren
suffix:semicolon
id|dtl1_write_wakeup
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
id|info-&gt;flowmask
op_assign
id|flowmask
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
DECL|function|dtl1_receive
r_static
r_void
id|dtl1_receive
c_func
(paren
id|dtl1_info_t
op_star
id|info
)paren
(brace
r_int
r_int
id|iobase
suffix:semicolon
id|nsh_t
op_star
id|nsh
suffix:semicolon
r_int
id|boguscount
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Unknown device&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|iobase
op_assign
id|info-&gt;link.io.BasePort1
suffix:semicolon
r_do
(brace
id|info-&gt;hdev-&gt;stat.byte_rx
op_increment
suffix:semicolon
multiline_comment|/* Allocate packet */
r_if
c_cond
(paren
id|info-&gt;rx_skb
op_eq
l_int|NULL
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|info-&gt;rx_skb
op_assign
id|bt_skb_alloc
c_func
(paren
id|HCI_MAX_FRAME_SIZE
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate mem for new packet&quot;
)paren
suffix:semicolon
id|info-&gt;rx_state
op_assign
id|RECV_WAIT_NSH
suffix:semicolon
id|info-&gt;rx_count
op_assign
id|NSHL
suffix:semicolon
r_return
suffix:semicolon
)brace
op_star
id|skb_put
c_func
(paren
id|info-&gt;rx_skb
comma
l_int|1
)paren
op_assign
id|inb
c_func
(paren
id|iobase
op_plus
id|UART_RX
)paren
suffix:semicolon
id|nsh
op_assign
(paren
id|nsh_t
op_star
)paren
id|info-&gt;rx_skb-&gt;data
suffix:semicolon
id|info-&gt;rx_count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;rx_count
op_eq
l_int|0
)paren
(brace
r_switch
c_cond
(paren
id|info-&gt;rx_state
)paren
(brace
r_case
id|RECV_WAIT_NSH
suffix:colon
id|info-&gt;rx_state
op_assign
id|RECV_WAIT_DATA
suffix:semicolon
id|info-&gt;rx_count
op_assign
id|nsh-&gt;len
op_plus
(paren
id|nsh-&gt;len
op_amp
l_int|0x0001
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RECV_WAIT_DATA
suffix:colon
id|info-&gt;rx_skb-&gt;pkt_type
op_assign
id|nsh-&gt;type
suffix:semicolon
multiline_comment|/* remove PAD byte if it exists */
r_if
c_cond
(paren
id|nsh-&gt;len
op_amp
l_int|0x0001
)paren
(brace
id|info-&gt;rx_skb-&gt;tail
op_decrement
suffix:semicolon
id|info-&gt;rx_skb-&gt;len
op_decrement
suffix:semicolon
)brace
multiline_comment|/* remove NSH */
id|skb_pull
c_func
(paren
id|info-&gt;rx_skb
comma
id|NSHL
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|info-&gt;rx_skb-&gt;pkt_type
)paren
(brace
r_case
l_int|0x80
suffix:colon
multiline_comment|/* control data for the Nokia Card */
id|dtl1_control
c_func
(paren
id|info
comma
id|info-&gt;rx_skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x82
suffix:colon
r_case
l_int|0x83
suffix:colon
r_case
l_int|0x84
suffix:colon
multiline_comment|/* send frame to the HCI layer */
id|info-&gt;rx_skb-&gt;dev
op_assign
(paren
r_void
op_star
)paren
id|info-&gt;hdev
suffix:semicolon
id|info-&gt;rx_skb-&gt;pkt_type
op_and_assign
l_int|0x0f
suffix:semicolon
id|hci_recv_frame
c_func
(paren
id|info-&gt;rx_skb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* unknown packet */
id|BT_ERR
c_func
(paren
l_string|&quot;Unknown HCI packet with type 0x%02x received&quot;
comma
id|info-&gt;rx_skb-&gt;pkt_type
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|info-&gt;rx_skb
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|info-&gt;rx_state
op_assign
id|RECV_WAIT_NSH
suffix:semicolon
id|info-&gt;rx_count
op_assign
id|NSHL
suffix:semicolon
id|info-&gt;rx_skb
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Make sure we don&squot;t stay here too long */
r_if
c_cond
(paren
id|boguscount
op_increment
OG
l_int|32
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|inb
c_func
(paren
id|iobase
op_plus
id|UART_LSR
)paren
op_amp
id|UART_LSR_DR
)paren
suffix:semicolon
)brace
DECL|function|dtl1_interrupt
r_static
id|irqreturn_t
id|dtl1_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_inst
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|dtl1_info_t
op_star
id|info
op_assign
id|dev_inst
suffix:semicolon
r_int
r_int
id|iobase
suffix:semicolon
r_int
r_char
id|msr
suffix:semicolon
r_int
id|boguscount
op_assign
l_int|0
suffix:semicolon
r_int
id|iir
comma
id|lsr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
op_logical_or
op_logical_neg
id|info-&gt;hdev
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Call of irq %d for unknown device&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
id|IRQ_NONE
suffix:semicolon
)brace
id|iobase
op_assign
id|info-&gt;link.io.BasePort1
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
(paren
id|info-&gt;lock
)paren
)paren
suffix:semicolon
id|iir
op_assign
id|inb
c_func
(paren
id|iobase
op_plus
id|UART_IIR
)paren
op_amp
id|UART_IIR_ID
suffix:semicolon
r_while
c_loop
(paren
id|iir
)paren
(brace
multiline_comment|/* Clear interrupt */
id|lsr
op_assign
id|inb
c_func
(paren
id|iobase
op_plus
id|UART_LSR
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|iir
)paren
(brace
r_case
id|UART_IIR_RLSI
suffix:colon
id|BT_ERR
c_func
(paren
l_string|&quot;RLSI&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UART_IIR_RDI
suffix:colon
multiline_comment|/* Receive interrupt */
id|dtl1_receive
c_func
(paren
id|info
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UART_IIR_THRI
suffix:colon
r_if
c_cond
(paren
id|lsr
op_amp
id|UART_LSR_THRE
)paren
(brace
multiline_comment|/* Transmitter ready for data */
id|dtl1_write_wakeup
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|BT_ERR
c_func
(paren
l_string|&quot;Unhandled IIR=%#x&quot;
comma
id|iir
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Make sure we don&squot;t stay here too long */
r_if
c_cond
(paren
id|boguscount
op_increment
OG
l_int|100
)paren
r_break
suffix:semicolon
id|iir
op_assign
id|inb
c_func
(paren
id|iobase
op_plus
id|UART_IIR
)paren
op_amp
id|UART_IIR_ID
suffix:semicolon
)brace
id|msr
op_assign
id|inb
c_func
(paren
id|iobase
op_plus
id|UART_MSR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;ri_latch
op_xor
(paren
id|msr
op_amp
id|UART_MSR_RI
)paren
)paren
(brace
id|info-&gt;ri_latch
op_assign
id|msr
op_amp
id|UART_MSR_RI
suffix:semicolon
id|clear_bit
c_func
(paren
id|XMIT_WAITING
comma
op_amp
(paren
id|info-&gt;tx_state
)paren
)paren
suffix:semicolon
id|dtl1_write_wakeup
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
(paren
id|info-&gt;lock
)paren
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/* ======================== HCI interface ======================== */
DECL|function|dtl1_hci_open
r_static
r_int
id|dtl1_hci_open
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
id|set_bit
c_func
(paren
id|HCI_RUNNING
comma
op_amp
(paren
id|hdev-&gt;flags
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dtl1_hci_flush
r_static
r_int
id|dtl1_hci_flush
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
id|dtl1_info_t
op_star
id|info
op_assign
(paren
id|dtl1_info_t
op_star
)paren
(paren
id|hdev-&gt;driver_data
)paren
suffix:semicolon
multiline_comment|/* Drop TX queue */
id|skb_queue_purge
c_func
(paren
op_amp
(paren
id|info-&gt;txq
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dtl1_hci_close
r_static
r_int
id|dtl1_hci_close
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_clear_bit
c_func
(paren
id|HCI_RUNNING
comma
op_amp
(paren
id|hdev-&gt;flags
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|dtl1_hci_flush
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dtl1_hci_send_frame
r_static
r_int
id|dtl1_hci_send_frame
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
id|dtl1_info_t
op_star
id|info
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hdev
op_assign
(paren
r_struct
id|hci_dev
op_star
)paren
(paren
id|skb-&gt;dev
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|s
suffix:semicolon
id|nsh_t
id|nsh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdev
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Frame for unknown HCI device (hdev=NULL)&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|info
op_assign
(paren
id|dtl1_info_t
op_star
)paren
(paren
id|hdev-&gt;driver_data
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|skb-&gt;pkt_type
)paren
(brace
r_case
id|HCI_COMMAND_PKT
suffix:colon
id|hdev-&gt;stat.cmd_tx
op_increment
suffix:semicolon
id|nsh.type
op_assign
l_int|0x81
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_ACLDATA_PKT
suffix:colon
id|hdev-&gt;stat.acl_tx
op_increment
suffix:semicolon
id|nsh.type
op_assign
l_int|0x82
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_SCODATA_PKT
suffix:colon
id|hdev-&gt;stat.sco_tx
op_increment
suffix:semicolon
id|nsh.type
op_assign
l_int|0x83
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|nsh.zero
op_assign
l_int|0
suffix:semicolon
id|nsh.len
op_assign
id|skb-&gt;len
suffix:semicolon
id|s
op_assign
id|bt_skb_alloc
c_func
(paren
id|NSHL
op_plus
id|skb-&gt;len
op_plus
l_int|1
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|skb_reserve
c_func
(paren
id|s
comma
id|NSHL
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb_put
c_func
(paren
id|s
comma
id|skb-&gt;len
)paren
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
op_amp
l_int|0x0001
)paren
op_star
id|skb_put
c_func
(paren
id|s
comma
l_int|1
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* PAD */
multiline_comment|/* Prepend skb with Nokia frame header and queue */
id|memcpy
c_func
(paren
id|skb_push
c_func
(paren
id|s
comma
id|NSHL
)paren
comma
op_amp
id|nsh
comma
id|NSHL
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
(paren
id|info-&gt;txq
)paren
comma
id|s
)paren
suffix:semicolon
id|dtl1_write_wakeup
c_func
(paren
id|info
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dtl1_hci_destruct
r_static
r_void
id|dtl1_hci_destruct
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
)brace
DECL|function|dtl1_hci_ioctl
r_static
r_int
id|dtl1_hci_ioctl
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
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
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
multiline_comment|/* ======================== Card services HCI interaction ======================== */
DECL|function|dtl1_open
r_int
id|dtl1_open
c_func
(paren
id|dtl1_info_t
op_star
id|info
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|iobase
op_assign
id|info-&gt;link.io.BasePort1
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hdev
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
(paren
id|info-&gt;lock
)paren
)paren
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
(paren
id|info-&gt;txq
)paren
)paren
suffix:semicolon
id|info-&gt;rx_state
op_assign
id|RECV_WAIT_NSH
suffix:semicolon
id|info-&gt;rx_count
op_assign
id|NSHL
suffix:semicolon
id|info-&gt;rx_skb
op_assign
l_int|NULL
suffix:semicolon
id|set_bit
c_func
(paren
id|XMIT_WAITING
comma
op_amp
(paren
id|info-&gt;tx_state
)paren
)paren
suffix:semicolon
multiline_comment|/* Initialize HCI device */
id|hdev
op_assign
id|hci_alloc_dev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdev
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate HCI device&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|info-&gt;hdev
op_assign
id|hdev
suffix:semicolon
id|hdev-&gt;type
op_assign
id|HCI_PCCARD
suffix:semicolon
id|hdev-&gt;driver_data
op_assign
id|info
suffix:semicolon
id|hdev-&gt;open
op_assign
id|dtl1_hci_open
suffix:semicolon
id|hdev-&gt;close
op_assign
id|dtl1_hci_close
suffix:semicolon
id|hdev-&gt;flush
op_assign
id|dtl1_hci_flush
suffix:semicolon
id|hdev-&gt;send
op_assign
id|dtl1_hci_send_frame
suffix:semicolon
id|hdev-&gt;destruct
op_assign
id|dtl1_hci_destruct
suffix:semicolon
id|hdev-&gt;ioctl
op_assign
id|dtl1_hci_ioctl
suffix:semicolon
id|hdev-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
(paren
id|info-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Reset UART */
id|outb
c_func
(paren
l_int|0
comma
id|iobase
op_plus
id|UART_MCR
)paren
suffix:semicolon
multiline_comment|/* Turn off interrupts */
id|outb
c_func
(paren
l_int|0
comma
id|iobase
op_plus
id|UART_IER
)paren
suffix:semicolon
multiline_comment|/* Initialize UART */
id|outb
c_func
(paren
id|UART_LCR_WLEN8
comma
id|iobase
op_plus
id|UART_LCR
)paren
suffix:semicolon
multiline_comment|/* Reset DLAB */
id|outb
c_func
(paren
(paren
id|UART_MCR_DTR
op_or
id|UART_MCR_RTS
op_or
id|UART_MCR_OUT2
)paren
comma
id|iobase
op_plus
id|UART_MCR
)paren
suffix:semicolon
id|info-&gt;ri_latch
op_assign
id|inb
c_func
(paren
id|info-&gt;link.io.BasePort1
op_plus
id|UART_MSR
)paren
op_amp
id|UART_MSR_RI
suffix:semicolon
multiline_comment|/* Turn on interrupts */
id|outb
c_func
(paren
id|UART_IER_RLSI
op_or
id|UART_IER_RDI
op_or
id|UART_IER_THRI
comma
id|iobase
op_plus
id|UART_IER
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|info-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Timeout before it is safe to send the first HCI packet */
id|msleep
c_func
(paren
l_int|2000
)paren
suffix:semicolon
multiline_comment|/* Register HCI device */
r_if
c_cond
(paren
id|hci_register_dev
c_func
(paren
id|hdev
)paren
OL
l_int|0
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t register HCI device&quot;
)paren
suffix:semicolon
id|info-&gt;hdev
op_assign
l_int|NULL
suffix:semicolon
id|hci_free_dev
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dtl1_close
r_int
id|dtl1_close
c_func
(paren
id|dtl1_info_t
op_star
id|info
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|iobase
op_assign
id|info-&gt;link.io.BasePort1
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hdev
op_assign
id|info-&gt;hdev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|dtl1_hci_close
c_func
(paren
id|hdev
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
(paren
id|info-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Reset UART */
id|outb
c_func
(paren
l_int|0
comma
id|iobase
op_plus
id|UART_MCR
)paren
suffix:semicolon
multiline_comment|/* Turn off interrupts */
id|outb
c_func
(paren
l_int|0
comma
id|iobase
op_plus
id|UART_IER
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|info-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hci_unregister_dev
c_func
(paren
id|hdev
)paren
OL
l_int|0
)paren
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t unregister HCI device %s&quot;
comma
id|hdev-&gt;name
)paren
suffix:semicolon
id|hci_free_dev
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dtl1_attach
id|dev_link_t
op_star
id|dtl1_attach
c_func
(paren
r_void
)paren
(brace
id|dtl1_info_t
op_star
id|info
suffix:semicolon
id|client_reg_t
id|client_reg
suffix:semicolon
id|dev_link_t
op_star
id|link
suffix:semicolon
r_int
id|i
comma
id|ret
suffix:semicolon
multiline_comment|/* Create new info device */
id|info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|info
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
id|link
op_assign
op_amp
id|info-&gt;link
suffix:semicolon
id|link-&gt;priv
op_assign
id|info
suffix:semicolon
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_8
suffix:semicolon
id|link-&gt;io.NumPorts1
op_assign
l_int|8
suffix:semicolon
id|link-&gt;irq.Attributes
op_assign
id|IRQ_TYPE_EXCLUSIVE
op_or
id|IRQ_HANDLE_PRESENT
suffix:semicolon
id|link-&gt;irq.IRQInfo1
op_assign
id|IRQ_INFO2_VALID
op_or
id|IRQ_LEVEL_ID
suffix:semicolon
r_if
c_cond
(paren
id|irq_list
(braket
l_int|0
)braket
op_eq
op_minus
l_int|1
)paren
id|link-&gt;irq.IRQInfo2
op_assign
id|irq_mask
suffix:semicolon
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|link-&gt;irq.IRQInfo2
op_or_assign
l_int|1
op_lshift
id|irq_list
(braket
id|i
)braket
suffix:semicolon
id|link-&gt;irq.Handler
op_assign
id|dtl1_interrupt
suffix:semicolon
id|link-&gt;irq.Instance
op_assign
id|info
suffix:semicolon
id|link-&gt;conf.Attributes
op_assign
id|CONF_ENABLE_IRQ
suffix:semicolon
id|link-&gt;conf.Vcc
op_assign
l_int|50
suffix:semicolon
id|link-&gt;conf.IntType
op_assign
id|INT_MEMORY_AND_IO
suffix:semicolon
multiline_comment|/* Register with Card Services */
id|link-&gt;next
op_assign
id|dev_list
suffix:semicolon
id|dev_list
op_assign
id|link
suffix:semicolon
id|client_reg.dev_info
op_assign
op_amp
id|dev_info
suffix:semicolon
id|client_reg.Attributes
op_assign
id|INFO_IO_CLIENT
op_or
id|INFO_CARD_SHARE
suffix:semicolon
id|client_reg.EventMask
op_assign
id|CS_EVENT_CARD_INSERTION
op_or
id|CS_EVENT_CARD_REMOVAL
op_or
id|CS_EVENT_RESET_PHYSICAL
op_or
id|CS_EVENT_CARD_RESET
op_or
id|CS_EVENT_PM_SUSPEND
op_or
id|CS_EVENT_PM_RESUME
suffix:semicolon
id|client_reg.event_handler
op_assign
op_amp
id|dtl1_event
suffix:semicolon
id|client_reg.Version
op_assign
l_int|0x0210
suffix:semicolon
id|client_reg.event_callback_args.client_data
op_assign
id|link
suffix:semicolon
id|ret
op_assign
id|pcmcia_register_client
c_func
(paren
op_amp
id|link-&gt;handle
comma
op_amp
id|client_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|CS_SUCCESS
)paren
(brace
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|RegisterClient
comma
id|ret
)paren
suffix:semicolon
id|dtl1_detach
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|link
suffix:semicolon
)brace
DECL|function|dtl1_detach
r_void
id|dtl1_detach
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|dtl1_info_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
id|dev_link_t
op_star
op_star
id|linkp
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* Locate device structure */
r_for
c_loop
(paren
id|linkp
op_assign
op_amp
id|dev_list
suffix:semicolon
op_star
id|linkp
suffix:semicolon
id|linkp
op_assign
op_amp
(paren
op_star
id|linkp
)paren
op_member_access_from_pointer
id|next
)paren
r_if
c_cond
(paren
op_star
id|linkp
op_eq
id|link
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|linkp
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
id|dtl1_release
c_func
(paren
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;handle
)paren
(brace
id|ret
op_assign
id|pcmcia_deregister_client
c_func
(paren
id|link-&gt;handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|CS_SUCCESS
)paren
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|DeregisterClient
comma
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/* Unlink device structure, free bits */
op_star
id|linkp
op_assign
id|link-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
DECL|function|get_tuple
r_static
r_int
id|get_tuple
c_func
(paren
id|client_handle_t
id|handle
comma
id|tuple_t
op_star
id|tuple
comma
id|cisparse_t
op_star
id|parse
)paren
(brace
r_int
id|i
suffix:semicolon
id|i
op_assign
id|pcmcia_get_tuple_data
c_func
(paren
id|handle
comma
id|tuple
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
r_return
id|i
suffix:semicolon
r_return
id|pcmcia_parse_tuple
c_func
(paren
id|handle
comma
id|tuple
comma
id|parse
)paren
suffix:semicolon
)brace
DECL|function|first_tuple
r_static
r_int
id|first_tuple
c_func
(paren
id|client_handle_t
id|handle
comma
id|tuple_t
op_star
id|tuple
comma
id|cisparse_t
op_star
id|parse
)paren
(brace
r_if
c_cond
(paren
id|pcmcia_get_first_tuple
c_func
(paren
id|handle
comma
id|tuple
)paren
op_ne
id|CS_SUCCESS
)paren
r_return
id|CS_NO_MORE_ITEMS
suffix:semicolon
r_return
id|get_tuple
c_func
(paren
id|handle
comma
id|tuple
comma
id|parse
)paren
suffix:semicolon
)brace
DECL|function|next_tuple
r_static
r_int
id|next_tuple
c_func
(paren
id|client_handle_t
id|handle
comma
id|tuple_t
op_star
id|tuple
comma
id|cisparse_t
op_star
id|parse
)paren
(brace
r_if
c_cond
(paren
id|pcmcia_get_next_tuple
c_func
(paren
id|handle
comma
id|tuple
)paren
op_ne
id|CS_SUCCESS
)paren
r_return
id|CS_NO_MORE_ITEMS
suffix:semicolon
r_return
id|get_tuple
c_func
(paren
id|handle
comma
id|tuple
comma
id|parse
)paren
suffix:semicolon
)brace
DECL|function|dtl1_config
r_void
id|dtl1_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|client_handle_t
id|handle
op_assign
id|link-&gt;handle
suffix:semicolon
id|dtl1_info_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
id|tuple_t
id|tuple
suffix:semicolon
id|u_short
id|buf
(braket
l_int|256
)braket
suffix:semicolon
id|cisparse_t
id|parse
suffix:semicolon
id|cistpl_cftable_entry_t
op_star
id|cf
op_assign
op_amp
id|parse.cftable_entry
suffix:semicolon
id|config_info_t
id|config
suffix:semicolon
r_int
id|i
comma
id|last_ret
comma
id|last_fn
suffix:semicolon
id|tuple.TupleData
op_assign
(paren
id|cisdata_t
op_star
)paren
id|buf
suffix:semicolon
id|tuple.TupleOffset
op_assign
l_int|0
suffix:semicolon
id|tuple.TupleDataMax
op_assign
l_int|255
suffix:semicolon
id|tuple.Attributes
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Get configuration register information */
id|tuple.DesiredTuple
op_assign
id|CISTPL_CONFIG
suffix:semicolon
id|last_ret
op_assign
id|first_tuple
c_func
(paren
id|handle
comma
op_amp
id|tuple
comma
op_amp
id|parse
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last_ret
op_ne
id|CS_SUCCESS
)paren
(brace
id|last_fn
op_assign
id|ParseTuple
suffix:semicolon
r_goto
id|cs_failed
suffix:semicolon
)brace
id|link-&gt;conf.ConfigBase
op_assign
id|parse.config.base
suffix:semicolon
id|link-&gt;conf.Present
op_assign
id|parse.config.rmask
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Configure card */
id|link-&gt;state
op_or_assign
id|DEV_CONFIG
suffix:semicolon
id|i
op_assign
id|pcmcia_get_configuration_info
c_func
(paren
id|handle
comma
op_amp
id|config
)paren
suffix:semicolon
id|link-&gt;conf.Vcc
op_assign
id|config.Vcc
suffix:semicolon
id|tuple.TupleData
op_assign
(paren
id|cisdata_t
op_star
)paren
id|buf
suffix:semicolon
id|tuple.TupleOffset
op_assign
l_int|0
suffix:semicolon
id|tuple.TupleDataMax
op_assign
l_int|255
suffix:semicolon
id|tuple.Attributes
op_assign
l_int|0
suffix:semicolon
id|tuple.DesiredTuple
op_assign
id|CISTPL_CFTABLE_ENTRY
suffix:semicolon
multiline_comment|/* Look for a generic full-sized window */
id|link-&gt;io.NumPorts1
op_assign
l_int|8
suffix:semicolon
id|i
op_assign
id|first_tuple
c_func
(paren
id|handle
comma
op_amp
id|tuple
comma
op_amp
id|parse
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_ne
id|CS_NO_MORE_ITEMS
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
op_eq
id|CS_SUCCESS
)paren
op_logical_and
(paren
id|cf-&gt;io.nwin
op_eq
l_int|1
)paren
op_logical_and
(paren
id|cf-&gt;io.win
(braket
l_int|0
)braket
dot
id|len
OG
l_int|8
)paren
)paren
(brace
id|link-&gt;conf.ConfigIndex
op_assign
id|cf-&gt;index
suffix:semicolon
id|link-&gt;io.BasePort1
op_assign
id|cf-&gt;io.win
(braket
l_int|0
)braket
dot
id|base
suffix:semicolon
id|link-&gt;io.NumPorts1
op_assign
id|cf-&gt;io.win
(braket
l_int|0
)braket
dot
id|len
suffix:semicolon
multiline_comment|/*yo */
id|link-&gt;io.IOAddrLines
op_assign
id|cf-&gt;io.flags
op_amp
id|CISTPL_IO_LINES_MASK
suffix:semicolon
id|i
op_assign
id|pcmcia_request_io
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;io
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|CS_SUCCESS
)paren
r_break
suffix:semicolon
)brace
id|i
op_assign
id|next_tuple
c_func
(paren
id|handle
comma
op_amp
id|tuple
comma
op_amp
id|parse
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
(brace
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|RequestIO
comma
id|i
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
id|i
op_assign
id|pcmcia_request_irq
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
(brace
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|RequestIRQ
comma
id|i
)paren
suffix:semicolon
id|link-&gt;irq.AssignedIRQ
op_assign
l_int|0
suffix:semicolon
)brace
id|i
op_assign
id|pcmcia_request_configuration
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;conf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
(brace
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|RequestConfiguration
comma
id|i
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dtl1_open
c_func
(paren
id|info
)paren
op_ne
l_int|0
)paren
r_goto
id|failed
suffix:semicolon
id|strcpy
c_func
(paren
id|info-&gt;node.dev_name
comma
id|info-&gt;hdev-&gt;name
)paren
suffix:semicolon
id|link-&gt;dev
op_assign
op_amp
id|info-&gt;node
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG_PENDING
suffix:semicolon
r_return
suffix:semicolon
id|cs_failed
suffix:colon
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|last_fn
comma
id|last_ret
)paren
suffix:semicolon
id|failed
suffix:colon
id|dtl1_release
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
DECL|function|dtl1_release
r_void
id|dtl1_release
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|dtl1_info_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_PRESENT
)paren
id|dtl1_close
c_func
(paren
id|info
)paren
suffix:semicolon
id|link-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|pcmcia_release_configuration
c_func
(paren
id|link-&gt;handle
)paren
suffix:semicolon
id|pcmcia_release_io
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;io
)paren
suffix:semicolon
id|pcmcia_release_irq
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;irq
)paren
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG
suffix:semicolon
)brace
DECL|function|dtl1_event
r_int
id|dtl1_event
c_func
(paren
id|event_t
id|event
comma
r_int
id|priority
comma
id|event_callback_args_t
op_star
id|args
)paren
(brace
id|dev_link_t
op_star
id|link
op_assign
id|args-&gt;client_data
suffix:semicolon
id|dtl1_info_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|CS_EVENT_CARD_REMOVAL
suffix:colon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_PRESENT
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
(brace
id|dtl1_close
c_func
(paren
id|info
)paren
suffix:semicolon
id|dtl1_release
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CS_EVENT_CARD_INSERTION
suffix:colon
id|link-&gt;state
op_or_assign
id|DEV_PRESENT
op_or
id|DEV_CONFIG_PENDING
suffix:semicolon
id|dtl1_config
c_func
(paren
id|link
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS_EVENT_PM_SUSPEND
suffix:colon
id|link-&gt;state
op_or_assign
id|DEV_SUSPEND
suffix:semicolon
multiline_comment|/* Fall through... */
r_case
id|CS_EVENT_RESET_PHYSICAL
suffix:colon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
id|pcmcia_release_configuration
c_func
(paren
id|link-&gt;handle
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS_EVENT_PM_RESUME
suffix:colon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_SUSPEND
suffix:semicolon
multiline_comment|/* Fall through... */
r_case
id|CS_EVENT_CARD_RESET
suffix:colon
r_if
c_cond
(paren
id|DEV_OK
c_func
(paren
id|link
)paren
)paren
id|pcmcia_request_configuration
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;conf
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|dtl1_driver
r_static
r_struct
id|pcmcia_driver
id|dtl1_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|drv
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;dtl1_cs&quot;
comma
)brace
comma
dot
id|attach
op_assign
id|dtl1_attach
comma
dot
id|detach
op_assign
id|dtl1_detach
comma
)brace
suffix:semicolon
DECL|function|init_dtl1_cs
r_static
r_int
id|__init
id|init_dtl1_cs
c_func
(paren
r_void
)paren
(brace
r_return
id|pcmcia_register_driver
c_func
(paren
op_amp
id|dtl1_driver
)paren
suffix:semicolon
)brace
DECL|function|exit_dtl1_cs
r_static
r_void
id|__exit
id|exit_dtl1_cs
c_func
(paren
r_void
)paren
(brace
id|pcmcia_unregister_driver
c_func
(paren
op_amp
id|dtl1_driver
)paren
suffix:semicolon
multiline_comment|/* XXX: this really needs to move into generic code.. */
r_while
c_loop
(paren
id|dev_list
op_ne
l_int|NULL
)paren
id|dtl1_detach
c_func
(paren
id|dev_list
)paren
suffix:semicolon
)brace
DECL|variable|init_dtl1_cs
id|module_init
c_func
(paren
id|init_dtl1_cs
)paren
suffix:semicolon
DECL|variable|exit_dtl1_cs
id|module_exit
c_func
(paren
id|exit_dtl1_cs
)paren
suffix:semicolon
eof
