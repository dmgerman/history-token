multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; * Bluetooth HCI UART driver.&n; *&n; * $Id: hci_ldisc.c,v 1.5 2002/10/02 18:37:20 maxk Exp $    &n; */
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;2.1&quot;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
macro_line|#include &lt;net/bluetooth/hci_core.h&gt;
macro_line|#include &quot;hci_uart.h&quot;
macro_line|#ifndef CONFIG_BT_HCIUART_DEBUG
DECL|macro|BT_DBG
macro_line|#undef  BT_DBG
DECL|macro|BT_DBG
mdefine_line|#define BT_DBG( A... )
DECL|macro|BT_DMP
macro_line|#undef  BT_DMP
DECL|macro|BT_DMP
mdefine_line|#define BT_DMP( A... )
macro_line|#endif
DECL|variable|hup
r_static
r_struct
id|hci_uart_proto
op_star
id|hup
(braket
id|HCI_UART_MAX_PROTO
)braket
suffix:semicolon
DECL|function|hci_uart_register_proto
r_int
id|hci_uart_register_proto
c_func
(paren
r_struct
id|hci_uart_proto
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;id
op_ge
id|HCI_UART_MAX_PROTO
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|hup
(braket
id|p-&gt;id
)braket
)paren
r_return
op_minus
id|EEXIST
suffix:semicolon
id|hup
(braket
id|p-&gt;id
)braket
op_assign
id|p
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_uart_unregister_proto
r_int
id|hci_uart_unregister_proto
c_func
(paren
r_struct
id|hci_uart_proto
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;id
op_ge
id|HCI_UART_MAX_PROTO
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hup
(braket
id|p-&gt;id
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|hup
(braket
id|p-&gt;id
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_uart_get_proto
r_static
r_struct
id|hci_uart_proto
op_star
id|hci_uart_get_proto
c_func
(paren
r_int
r_int
id|id
)paren
(brace
r_if
c_cond
(paren
id|id
op_ge
id|HCI_UART_MAX_PROTO
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|hup
(braket
id|id
)braket
suffix:semicolon
)brace
DECL|function|hci_uart_tx_complete
r_static
r_inline
r_void
id|hci_uart_tx_complete
c_func
(paren
r_struct
id|hci_uart
op_star
id|hu
comma
r_int
id|pkt_type
)paren
(brace
r_struct
id|hci_dev
op_star
id|hdev
op_assign
op_amp
id|hu-&gt;hdev
suffix:semicolon
multiline_comment|/* Update HCI stat counters */
r_switch
c_cond
(paren
id|pkt_type
)paren
(brace
r_case
id|HCI_COMMAND_PKT
suffix:colon
id|hdev-&gt;stat.cmd_tx
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_ACLDATA_PKT
suffix:colon
id|hdev-&gt;stat.acl_tx
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HCI_SCODATA_PKT
suffix:colon
id|hdev-&gt;stat.cmd_tx
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|hci_uart_dequeue
r_static
r_inline
r_struct
id|sk_buff
op_star
id|hci_uart_dequeue
c_func
(paren
r_struct
id|hci_uart
op_star
id|hu
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|hu-&gt;tx_skb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
id|skb
op_assign
id|hu-&gt;proto
op_member_access_from_pointer
id|dequeue
c_func
(paren
id|hu
)paren
suffix:semicolon
r_else
id|hu-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
DECL|function|hci_uart_tx_wakeup
r_int
id|hci_uart_tx_wakeup
c_func
(paren
r_struct
id|hci_uart
op_star
id|hu
)paren
(brace
r_struct
id|tty_struct
op_star
id|tty
op_assign
id|hu-&gt;tty
suffix:semicolon
r_struct
id|hci_dev
op_star
id|hdev
op_assign
op_amp
id|hu-&gt;hdev
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|HCI_UART_SENDING
comma
op_amp
id|hu-&gt;tx_state
)paren
)paren
(brace
id|set_bit
c_func
(paren
id|HCI_UART_TX_WAKEUP
comma
op_amp
id|hu-&gt;tx_state
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|BT_DBG
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|restart
suffix:colon
id|clear_bit
c_func
(paren
id|HCI_UART_TX_WAKEUP
comma
op_amp
id|hu-&gt;tx_state
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|hci_uart_dequeue
c_func
(paren
id|hu
)paren
)paren
)paren
(brace
r_int
id|len
suffix:semicolon
id|set_bit
c_func
(paren
id|TTY_DO_WRITE_WAKEUP
comma
op_amp
id|tty-&gt;flags
)paren
suffix:semicolon
id|len
op_assign
id|tty-&gt;driver
dot
id|write
c_func
(paren
id|tty
comma
l_int|0
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|hdev-&gt;stat.byte_tx
op_add_assign
id|len
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
)paren
(brace
id|hu-&gt;tx_skb
op_assign
id|skb
suffix:semicolon
r_break
suffix:semicolon
)brace
id|hci_uart_tx_complete
c_func
(paren
id|hu
comma
id|skb-&gt;pkt_type
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|HCI_UART_TX_WAKEUP
comma
op_amp
id|hu-&gt;tx_state
)paren
)paren
r_goto
id|restart
suffix:semicolon
id|clear_bit
c_func
(paren
id|HCI_UART_SENDING
comma
op_amp
id|hu-&gt;tx_state
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------- Interface to HCI layer ------ */
multiline_comment|/* Initialize device */
DECL|function|hci_uart_open
r_static
r_int
id|hci_uart_open
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
id|BT_DBG
c_func
(paren
l_string|&quot;%s %p&quot;
comma
id|hdev-&gt;name
comma
id|hdev
)paren
suffix:semicolon
multiline_comment|/* Nothing to do for UART driver */
id|set_bit
c_func
(paren
id|HCI_RUNNING
comma
op_amp
id|hdev-&gt;flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Reset device */
DECL|function|hci_uart_flush
r_static
r_int
id|hci_uart_flush
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|hci_uart
op_star
id|hu
op_assign
(paren
r_struct
id|hci_uart
op_star
)paren
id|hdev-&gt;driver_data
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
op_assign
id|hu-&gt;tty
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;hdev %p tty %p&quot;
comma
id|hdev
comma
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hu-&gt;tx_skb
)paren
(brace
id|kfree_skb
c_func
(paren
id|hu-&gt;tx_skb
)paren
suffix:semicolon
id|hu-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Flush any pending characters in the driver and discipline. */
r_if
c_cond
(paren
id|tty-&gt;ldisc.flush_buffer
)paren
id|tty-&gt;ldisc
dot
id|flush_buffer
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver.flush_buffer
)paren
id|tty-&gt;driver
dot
id|flush_buffer
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|HCI_UART_PROTO_SET
comma
op_amp
id|hu-&gt;flags
)paren
)paren
id|hu-&gt;proto
op_member_access_from_pointer
id|flush
c_func
(paren
id|hu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Close device */
DECL|function|hci_uart_close
r_static
r_int
id|hci_uart_close
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
id|BT_DBG
c_func
(paren
l_string|&quot;hdev %p&quot;
comma
id|hdev
)paren
suffix:semicolon
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
id|hdev-&gt;flags
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|hci_uart_flush
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Send frames from HCI layer */
DECL|function|hci_uart_send_frame
r_static
r_int
id|hci_uart_send_frame
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
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
id|skb-&gt;dev
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_struct
id|hci_uart
op_star
id|hu
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
l_string|&quot;Frame for uknown device (hdev=NULL)&quot;
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
id|test_bit
c_func
(paren
id|HCI_RUNNING
comma
op_amp
id|hdev-&gt;flags
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|hu
op_assign
(paren
r_struct
id|hci_uart
op_star
)paren
id|hdev-&gt;driver_data
suffix:semicolon
id|tty
op_assign
id|hu-&gt;tty
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;%s: type %d len %d&quot;
comma
id|hdev-&gt;name
comma
id|skb-&gt;pkt_type
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|hu-&gt;proto
op_member_access_from_pointer
id|enqueue
c_func
(paren
id|hu
comma
id|skb
)paren
suffix:semicolon
id|hci_uart_tx_wakeup
c_func
(paren
id|hu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_uart_destruct
r_static
r_void
id|hci_uart_destruct
c_func
(paren
r_struct
id|hci_dev
op_star
id|hdev
)paren
(brace
r_struct
id|hci_uart
op_star
id|hu
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hdev
)paren
r_return
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;%s&quot;
comma
id|hdev-&gt;name
)paren
suffix:semicolon
id|hu
op_assign
(paren
r_struct
id|hci_uart
op_star
)paren
id|hdev-&gt;driver_data
suffix:semicolon
id|kfree
c_func
(paren
id|hu
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/* ------ LDISC part ------ */
multiline_comment|/* hci_uart_tty_open&n; * &n; *     Called when line discipline changed to HCI_UART.&n; *&n; * Arguments:&n; *     tty    pointer to tty info structure&n; * Return Value:    &n; *     0 if success, otherwise error code&n; */
DECL|function|hci_uart_tty_open
r_static
r_int
id|hci_uart_tty_open
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|hci_uart
op_star
id|hu
op_assign
(paren
r_void
op_star
)paren
id|tty-&gt;disc_data
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;tty %p&quot;
comma
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hu
)paren
r_return
op_minus
id|EEXIST
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|hu
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hci_uart
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate controll structure&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENFILE
suffix:semicolon
)brace
id|memset
c_func
(paren
id|hu
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|hci_uart
)paren
)paren
suffix:semicolon
id|tty-&gt;disc_data
op_assign
id|hu
suffix:semicolon
id|hu-&gt;tty
op_assign
id|tty
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|hu-&gt;rx_lock
)paren
suffix:semicolon
multiline_comment|/* Flush any pending characters in the driver and line discipline */
r_if
c_cond
(paren
id|tty-&gt;ldisc.flush_buffer
)paren
id|tty-&gt;ldisc
dot
id|flush_buffer
c_func
(paren
id|tty
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver.flush_buffer
)paren
id|tty-&gt;driver
dot
id|flush_buffer
c_func
(paren
id|tty
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* hci_uart_tty_close()&n; *&n; *    Called when the line discipline is changed to something&n; *    else, the tty is closed, or the tty detects a hangup.&n; */
DECL|function|hci_uart_tty_close
r_static
r_void
id|hci_uart_tty_close
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|hci_uart
op_star
id|hu
op_assign
(paren
r_void
op_star
)paren
id|tty-&gt;disc_data
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;tty %p&quot;
comma
id|tty
)paren
suffix:semicolon
multiline_comment|/* Detach from the tty */
id|tty-&gt;disc_data
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|hu
)paren
(brace
r_struct
id|hci_dev
op_star
id|hdev
op_assign
op_amp
id|hu-&gt;hdev
suffix:semicolon
id|hci_uart_close
c_func
(paren
id|hdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|HCI_UART_PROTO_SET
comma
op_amp
id|hu-&gt;flags
)paren
)paren
(brace
id|hu-&gt;proto
op_member_access_from_pointer
id|close
c_func
(paren
id|hu
)paren
suffix:semicolon
id|hci_unregister_dev
c_func
(paren
id|hdev
)paren
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
)brace
multiline_comment|/* hci_uart_tty_wakeup()&n; *&n; *    Callback for transmit wakeup. Called when low level&n; *    device driver can accept more send data.&n; *&n; * Arguments:        tty    pointer to associated tty instance data&n; * Return Value:    None&n; */
DECL|function|hci_uart_tty_wakeup
r_static
r_void
id|hci_uart_tty_wakeup
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_struct
id|hci_uart
op_star
id|hu
op_assign
(paren
r_void
op_star
)paren
id|tty-&gt;disc_data
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hu
)paren
r_return
suffix:semicolon
id|clear_bit
c_func
(paren
id|TTY_DO_WRITE_WAKEUP
comma
op_amp
id|tty-&gt;flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty
op_ne
id|hu-&gt;tty
)paren
r_return
suffix:semicolon
id|hci_uart_tx_wakeup
c_func
(paren
id|hu
)paren
suffix:semicolon
)brace
multiline_comment|/* hci_uart_tty_room()&n; * &n; *    Callback function from tty driver. Return the amount of &n; *    space left in the receiver&squot;s buffer to decide if remote&n; *    transmitter is to be throttled.&n; *&n; * Arguments:        tty    pointer to associated tty instance data&n; * Return Value:    number of bytes left in receive buffer&n; */
DECL|function|hci_uart_tty_room
r_static
r_int
id|hci_uart_tty_room
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
(brace
r_return
l_int|65536
suffix:semicolon
)brace
multiline_comment|/* hci_uart_tty_receive()&n; * &n; *     Called by tty low level driver when receive data is&n; *     available.&n; *     &n; * Arguments:  tty          pointer to tty isntance data&n; *             data         pointer to received data&n; *             flags        pointer to flags for data&n; *             count        count of received data in bytes&n; *     &n; * Return Value:    None&n; */
DECL|function|hci_uart_tty_receive
r_static
r_void
id|hci_uart_tty_receive
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_const
id|__u8
op_star
id|data
comma
r_char
op_star
id|flags
comma
r_int
id|count
)paren
(brace
r_struct
id|hci_uart
op_star
id|hu
op_assign
(paren
r_void
op_star
)paren
id|tty-&gt;disc_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hu
op_logical_or
id|tty
op_ne
id|hu-&gt;tty
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|HCI_UART_PROTO_SET
comma
op_amp
id|hu-&gt;flags
)paren
)paren
r_return
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|hu-&gt;rx_lock
)paren
suffix:semicolon
id|hu-&gt;proto
op_member_access_from_pointer
id|recv
c_func
(paren
id|hu
comma
(paren
r_void
op_star
)paren
id|data
comma
id|count
)paren
suffix:semicolon
id|hu-&gt;hdev.stat.byte_rx
op_add_assign
id|count
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|hu-&gt;rx_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|TTY_THROTTLED
comma
op_amp
id|tty-&gt;flags
)paren
op_logical_and
id|tty-&gt;driver.unthrottle
)paren
id|tty-&gt;driver
dot
id|unthrottle
c_func
(paren
id|tty
)paren
suffix:semicolon
)brace
DECL|function|hci_uart_register_dev
r_static
r_int
id|hci_uart_register_dev
c_func
(paren
r_struct
id|hci_uart
op_star
id|hu
)paren
(brace
r_struct
id|hci_dev
op_star
id|hdev
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
multiline_comment|/* Initialize and register HCI device */
id|hdev
op_assign
op_amp
id|hu-&gt;hdev
suffix:semicolon
id|hdev-&gt;type
op_assign
id|HCI_UART
suffix:semicolon
id|hdev-&gt;driver_data
op_assign
id|hu
suffix:semicolon
id|hdev-&gt;open
op_assign
id|hci_uart_open
suffix:semicolon
id|hdev-&gt;close
op_assign
id|hci_uart_close
suffix:semicolon
id|hdev-&gt;flush
op_assign
id|hci_uart_flush
suffix:semicolon
id|hdev-&gt;send
op_assign
id|hci_uart_send_frame
suffix:semicolon
id|hdev-&gt;destruct
op_assign
id|hci_uart_destruct
suffix:semicolon
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
l_string|&quot;Can&squot;t register HCI device %s&quot;
comma
id|hdev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_uart_set_proto
r_static
r_int
id|hci_uart_set_proto
c_func
(paren
r_struct
id|hci_uart
op_star
id|hu
comma
r_int
id|id
)paren
(brace
r_struct
id|hci_uart_proto
op_star
id|p
suffix:semicolon
r_int
id|err
suffix:semicolon
id|p
op_assign
id|hci_uart_get_proto
c_func
(paren
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
op_minus
id|EPROTONOSUPPORT
suffix:semicolon
id|err
op_assign
id|p
op_member_access_from_pointer
id|open
c_func
(paren
id|hu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|hu-&gt;proto
op_assign
id|p
suffix:semicolon
id|err
op_assign
id|hci_uart_register_dev
c_func
(paren
id|hu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|p
op_member_access_from_pointer
id|close
c_func
(paren
id|hu
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* hci_uart_tty_ioctl()&n; *&n; *    Process IOCTL system call for the tty device.&n; *&n; * Arguments:&n; *&n; *    tty        pointer to tty instance data&n; *    file       pointer to open file object for device&n; *    cmd        IOCTL command code&n; *    arg        argument for IOCTL call (cmd dependent)&n; *&n; * Return Value:    Command dependent&n; */
DECL|function|hci_uart_tty_ioctl
r_static
r_int
id|hci_uart_tty_ioctl
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
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
r_struct
id|hci_uart
op_star
id|hu
op_assign
(paren
r_void
op_star
)paren
id|tty-&gt;disc_data
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
multiline_comment|/* Verify the status of the device */
r_if
c_cond
(paren
op_logical_neg
id|hu
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|HCIUARTSETPROTO
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|HCI_UART_PROTO_SET
comma
op_amp
id|hu-&gt;flags
)paren
)paren
(brace
id|err
op_assign
id|hci_uart_set_proto
c_func
(paren
id|hu
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|clear_bit
c_func
(paren
id|HCI_UART_PROTO_SET
comma
op_amp
id|hu-&gt;flags
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|tty-&gt;low_latency
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EBUSY
suffix:semicolon
r_case
id|HCIUARTGETPROTO
suffix:colon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|HCI_UART_PROTO_SET
comma
op_amp
id|hu-&gt;flags
)paren
)paren
r_return
id|hu-&gt;proto-&gt;id
suffix:semicolon
r_return
op_minus
id|EUNATCH
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
id|n_tty_ioctl
c_func
(paren
id|tty
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * We don&squot;t provide read/write/poll interface for user space.&n; */
DECL|function|hci_uart_tty_read
r_static
id|ssize_t
id|hci_uart_tty_read
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|nr
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_uart_tty_write
r_static
id|ssize_t
id|hci_uart_tty_write
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|file
comma
r_const
r_int
r_char
op_star
id|data
comma
r_int
id|count
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_uart_tty_poll
r_static
r_int
r_int
id|hci_uart_tty_poll
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BT_HCIUART_H4
r_int
id|h4_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|h4_deinit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BT_HCIUART_BCSP
r_int
id|bcsp_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|bcsp_deinit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|hci_uart_init
r_int
id|__init
id|hci_uart_init
c_func
(paren
r_void
)paren
(brace
r_static
r_struct
id|tty_ldisc
id|hci_uart_ldisc
suffix:semicolon
r_int
id|err
suffix:semicolon
id|BT_INFO
c_func
(paren
l_string|&quot;Bluetooth HCI UART driver ver %s Copyright (C) 2000,2001 Qualcomm Inc&quot;
comma
id|VERSION
)paren
suffix:semicolon
id|BT_INFO
c_func
(paren
l_string|&quot;Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&quot;
)paren
suffix:semicolon
multiline_comment|/* Register the tty discipline */
id|memset
c_func
(paren
op_amp
id|hci_uart_ldisc
comma
l_int|0
comma
r_sizeof
(paren
id|hci_uart_ldisc
)paren
)paren
suffix:semicolon
id|hci_uart_ldisc.magic
op_assign
id|TTY_LDISC_MAGIC
suffix:semicolon
id|hci_uart_ldisc.name
op_assign
l_string|&quot;n_hci&quot;
suffix:semicolon
id|hci_uart_ldisc.open
op_assign
id|hci_uart_tty_open
suffix:semicolon
id|hci_uart_ldisc.close
op_assign
id|hci_uart_tty_close
suffix:semicolon
id|hci_uart_ldisc.read
op_assign
id|hci_uart_tty_read
suffix:semicolon
id|hci_uart_ldisc.write
op_assign
id|hci_uart_tty_write
suffix:semicolon
id|hci_uart_ldisc.ioctl
op_assign
id|hci_uart_tty_ioctl
suffix:semicolon
id|hci_uart_ldisc.poll
op_assign
id|hci_uart_tty_poll
suffix:semicolon
id|hci_uart_ldisc.receive_room
op_assign
id|hci_uart_tty_room
suffix:semicolon
id|hci_uart_ldisc.receive_buf
op_assign
id|hci_uart_tty_receive
suffix:semicolon
id|hci_uart_ldisc.write_wakeup
op_assign
id|hci_uart_tty_wakeup
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|tty_register_ldisc
c_func
(paren
id|N_HCI
comma
op_amp
id|hci_uart_ldisc
)paren
)paren
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t register HCI line discipline (%d)&quot;
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BT_HCIUART_H4
id|h4_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BT_HCIUART_BCSP
id|bcsp_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hci_uart_cleanup
r_void
id|hci_uart_cleanup
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
macro_line|#ifdef CONFIG_BT_HCIUART_H4
id|h4_deinit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BT_HCIUART_BCSP
id|bcsp_deinit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Release tty registration of line discipline */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|tty_register_ldisc
c_func
(paren
id|N_HCI
comma
l_int|NULL
)paren
)paren
)paren
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t unregister HCI line discipline (%d)&quot;
comma
id|err
)paren
suffix:semicolon
)brace
DECL|variable|hci_uart_init
id|module_init
c_func
(paren
id|hci_uart_init
)paren
suffix:semicolon
DECL|variable|hci_uart_cleanup
id|module_exit
c_func
(paren
id|hci_uart_cleanup
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Bluetooth HCI UART driver ver &quot;
id|VERSION
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
