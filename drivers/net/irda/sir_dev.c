multiline_comment|/*********************************************************************&n; *&n; *&t;sir_dev.c:&t;irda sir network device&n; * &n; *&t;Copyright (c) 2002 Martin Diehl&n; * &n; *&t;This program is free software; you can redistribute it and/or &n; *&t;modify it under the terms of the GNU General Public License as &n; *&t;published by the Free Software Foundation; either version 2 of &n; *&t;the License, or (at your option) any later version.&n; *&n; ********************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/wrapper.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
macro_line|#include &quot;sir-dev.h&quot;
multiline_comment|/***************************************************************************/
DECL|function|sirdev_enable_rx
r_void
id|sirdev_enable_rx
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;enable_rx
)paren
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* flush rx-buffer - should also help in case of problems with echo cancelation */
id|dev-&gt;rx_buff.data
op_assign
id|dev-&gt;rx_buff.head
suffix:semicolon
id|dev-&gt;tx_buff.len
op_assign
l_int|0
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;enable_rx
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|sirdev_is_receiving
r_static
r_int
id|sirdev_is_receiving
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;enable_rx
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
id|dev-&gt;rx_buff.state
op_ne
id|OUTSIDE_FRAME
)paren
suffix:semicolon
)brace
DECL|function|sirdev_set_dongle
r_int
id|sirdev_set_dongle
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
comma
id|IRDA_DONGLE
id|type
)paren
(brace
r_int
id|err
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|3
comma
l_string|&quot;%s : requesting dongle %d.&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|type
)paren
suffix:semicolon
id|err
op_assign
id|sirdev_schedule_dongle_open
c_func
(paren
id|dev
comma
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|err
)paren
)paren
r_return
id|err
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;fsm.sem
)paren
suffix:semicolon
multiline_comment|/* block until config change completed */
id|err
op_assign
id|dev-&gt;fsm.result
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;fsm.sem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* used by dongle drivers for dongle programming */
DECL|function|sirdev_raw_write
r_int
id|sirdev_raw_write
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|len
OG
id|dev-&gt;tx_buff.truesize
)paren
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|dev-&gt;tx_lock
)paren
suffix:semicolon
multiline_comment|/* serialize with other tx operations */
r_while
c_loop
(paren
id|dev-&gt;tx_buff.len
OG
l_int|0
)paren
(brace
multiline_comment|/* wait until tx idle */
id|spin_unlock_bh
c_func
(paren
op_amp
id|dev-&gt;tx_lock
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|MSECS_TO_JIFFIES
c_func
(paren
l_int|10
)paren
)paren
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|dev-&gt;tx_lock
)paren
suffix:semicolon
)brace
id|dev-&gt;tx_buff.data
op_assign
id|dev-&gt;tx_buff.head
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;tx_buff.data
comma
id|buf
comma
id|len
)paren
suffix:semicolon
id|ret
op_assign
id|dev-&gt;drv
op_member_access_from_pointer
id|do_write
c_func
(paren
id|dev
comma
id|dev-&gt;tx_buff.data
comma
id|dev-&gt;tx_buff.len
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|dev-&gt;tx_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* seems some dongle drivers may need this */
DECL|function|sirdev_raw_read
r_int
id|sirdev_raw_read
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|count
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;enable_rx
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* fail if we expect irda-frames */
id|count
op_assign
(paren
id|len
OL
id|dev-&gt;rx_buff.len
)paren
ques
c_cond
id|len
suffix:colon
id|dev-&gt;rx_buff.len
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
id|memcpy
c_func
(paren
id|buf
comma
id|dev-&gt;rx_buff.head
comma
id|count
)paren
suffix:semicolon
multiline_comment|/* forget trailing stuff */
id|dev-&gt;rx_buff.data
op_assign
id|dev-&gt;rx_buff.head
suffix:semicolon
id|dev-&gt;rx_buff.len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;rx_buff.state
op_assign
id|OUTSIDE_FRAME
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/**********************************************************************/
multiline_comment|/* called from client driver - likely with bh-context - to indicate&n; * it made some progress with transmission. Hence we send the next&n; * chunk, if any, or complete the skb otherwise&n; */
DECL|function|sirdev_write_complete
r_void
id|sirdev_write_complete
c_func
(paren
r_struct
id|sir_dev
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
id|actual
op_assign
l_int|0
suffix:semicolon
r_int
id|err
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|dev-&gt;tx_lock
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|3
comma
l_string|&quot;%s() - dev-&gt;tx_buff.len = %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|dev-&gt;tx_buff.len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|dev-&gt;tx_buff.len
OG
l_int|0
)paren
)paren
(brace
multiline_comment|/* Write data left in transmit buffer */
id|actual
op_assign
id|dev-&gt;drv
op_member_access_from_pointer
id|do_write
c_func
(paren
id|dev
comma
id|dev-&gt;tx_buff.data
comma
id|dev-&gt;tx_buff.len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|actual
OG
l_int|0
)paren
)paren
(brace
id|dev-&gt;tx_buff.data
op_add_assign
id|actual
suffix:semicolon
id|dev-&gt;tx_buff.len
op_sub_assign
id|actual
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|actual
OL
l_int|0
)paren
)paren
(brace
multiline_comment|/* could be dropped later when we have tx_timeout to recover */
id|ERROR
c_func
(paren
l_string|&quot;%s: drv-&gt;do_write failed (%d)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|actual
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|dev-&gt;tx_skb
)paren
op_ne
l_int|NULL
)paren
(brace
id|dev-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
id|dev-&gt;stats.tx_errors
op_increment
suffix:semicolon
id|dev-&gt;stats.tx_dropped
op_increment
suffix:semicolon
)brace
id|dev-&gt;tx_buff.len
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;tx_buff.len
OG
l_int|0
)paren
(brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|dev-&gt;tx_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* we have finished now sending this skb.&n;&t; * update statistics and free the skb.&n;&t; * finally we check and trigger a pending speed change, if any.&n;&t; * if not we switch to rx mode and wake the queue for further&n;&t; * packets.&n;&t; * note the scheduled speed request blocks until the lower&n;&t; * client driver and the corresponding hardware has really&n;&t; * finished sending all data (xmit fifo drained f.e.)&n;&t; * before the speed change gets finally done and the queue&n;&t; * re-activated.&n;&t; */
id|IRDA_DEBUG
c_func
(paren
l_int|5
comma
l_string|&quot;%s(), finished with frame!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|dev-&gt;tx_skb
)paren
op_ne
l_int|NULL
)paren
(brace
id|dev-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;stats.tx_packets
op_increment
suffix:semicolon
id|dev-&gt;stats.tx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|dev-&gt;new_speed
OG
l_int|0
)paren
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|5
comma
l_string|&quot;%s(), Changing speed!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|err
op_assign
id|sirdev_schedule_speed
c_func
(paren
id|dev
comma
id|dev-&gt;new_speed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|err
)paren
)paren
(brace
multiline_comment|/* should never happen&n;&t;&t;&t; * forget the speed change and hope the stack recovers&n;&t;&t;&t; */
id|ERROR
c_func
(paren
l_string|&quot;%s - schedule speed change failed: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|err
)paren
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|dev-&gt;netdev
)paren
suffix:semicolon
)brace
multiline_comment|/* else: success&n;&t;&t; *&t;speed change in progress now&n;&t;&t; *&t;on completion dev-&gt;new_speed gets cleared,&n;&t;&t; *&t;rx-reenabled and the queue restarted&n;&t;&t; */
)brace
r_else
(brace
id|sirdev_enable_rx
c_func
(paren
id|dev
)paren
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|dev-&gt;netdev
)paren
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|dev-&gt;tx_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* called from client driver - likely with bh-context - to give us&n; * some more received bytes. We put them into the rx-buffer,&n; * normally unwrapping and building LAP-skb&squot;s (unless rx disabled)&n; */
DECL|function|sirdev_receive
r_int
id|sirdev_receive
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
comma
r_const
r_int
r_char
op_star
id|cp
comma
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|dev-&gt;netdev
)paren
(brace
id|WARNING
c_func
(paren
l_string|&quot;%s(), not ready yet!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;irlap
)paren
(brace
id|WARNING
c_func
(paren
l_string|&quot;%s - too early: %p / %d!&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|cp
comma
id|count
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cp
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* error already at lower level receive&n;&t;&t; * just update stats and set media busy&n;&t;&t; */
id|irda_device_set_media_busy
c_func
(paren
id|dev-&gt;netdev
comma
id|TRUE
)paren
suffix:semicolon
id|dev-&gt;stats.rx_dropped
op_increment
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s; rx-drop: %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Read the characters into the buffer */
r_if
c_cond
(paren
id|likely
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;enable_rx
)paren
)paren
)paren
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
multiline_comment|/* Unwrap and destuff one byte */
id|async_unwrap_char
c_func
(paren
id|dev-&gt;netdev
comma
op_amp
id|dev-&gt;stats
comma
op_amp
id|dev-&gt;rx_buff
comma
op_star
id|cp
op_increment
)paren
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
multiline_comment|/* rx not enabled: save the raw bytes and never&n;&t;&t;&t; * trigger any netif_rx. The received bytes are flushed&n;&t;&t;&t; * later when we re-enable rx but might be read meanwhile&n;&t;&t;&t; * by the dongle driver.&n;&t;&t;&t; */
id|dev-&gt;rx_buff.data
(braket
id|dev-&gt;rx_buff.len
op_increment
)braket
op_assign
op_star
id|cp
op_increment
suffix:semicolon
multiline_comment|/* What should we do when the buffer is full? */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|dev-&gt;rx_buff.len
op_eq
id|dev-&gt;rx_buff.truesize
)paren
)paren
id|dev-&gt;rx_buff.len
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**********************************************************************/
multiline_comment|/* callbacks from network layer */
DECL|function|sirdev_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|sirdev_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
)paren
(brace
r_struct
id|sir_dev
op_star
id|dev
op_assign
id|ndev-&gt;priv
suffix:semicolon
r_return
(paren
id|dev
)paren
ques
c_cond
op_amp
id|dev-&gt;stats
suffix:colon
l_int|NULL
suffix:semicolon
)brace
DECL|function|sirdev_hard_xmit
r_static
r_int
id|sirdev_hard_xmit
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
id|ndev
)paren
(brace
r_struct
id|sir_dev
op_star
id|dev
op_assign
id|ndev-&gt;priv
suffix:semicolon
r_int
id|actual
op_assign
l_int|0
suffix:semicolon
r_int
id|err
suffix:semicolon
id|s32
id|speed
suffix:semicolon
id|ASSERT
c_func
(paren
id|dev
op_ne
l_int|NULL
comma
r_return
l_int|0
suffix:semicolon
)paren
suffix:semicolon
id|netif_stop_queue
c_func
(paren
id|ndev
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|3
comma
l_string|&quot;%s(), skb-&gt;len = %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|speed
op_assign
id|irda_get_next_speed
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|speed
op_ne
id|dev-&gt;speed
)paren
op_logical_and
(paren
id|speed
op_ne
op_minus
l_int|1
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|skb-&gt;len
)paren
(brace
id|err
op_assign
id|sirdev_schedule_speed
c_func
(paren
id|dev
comma
id|speed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|err
op_eq
op_minus
id|EWOULDBLOCK
)paren
)paren
(brace
multiline_comment|/* Failed to initiate the speed change, likely the fsm&n;&t;&t;&t;&t; * is still busy (pretty unlikely, but...)&n;&t;&t;&t;&t; * We refuse to accept the skb and return with the queue&n;&t;&t;&t;&t; * stopped so the network layer will retry after the&n;&t;&t;&t;&t; * fsm completes and wakes the queue.&n;&t;&t;&t;&t; */
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|err
)paren
)paren
(brace
multiline_comment|/* other fatal error - forget the speed change and&n;&t;&t;&t;&t; * hope the stack will recover somehow&n;&t;&t;&t;&t; */
id|netif_start_queue
c_func
(paren
id|ndev
)paren
suffix:semicolon
)brace
multiline_comment|/* else: success&n;&t;&t;&t; *&t;speed change in progress now&n;&t;&t;&t; *&t;on completion the queue gets restarted&n;&t;&t;&t; */
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
id|dev-&gt;new_speed
op_assign
id|speed
suffix:semicolon
)brace
multiline_comment|/* Init tx buffer*/
id|dev-&gt;tx_buff.data
op_assign
id|dev-&gt;tx_buff.head
suffix:semicolon
multiline_comment|/* Check problems */
r_if
c_cond
(paren
id|spin_is_locked
c_func
(paren
op_amp
id|dev-&gt;tx_lock
)paren
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|3
comma
l_string|&quot;%s(), write not completed&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
multiline_comment|/* serialize with write completion */
id|spin_lock_bh
c_func
(paren
op_amp
id|dev-&gt;tx_lock
)paren
suffix:semicolon
multiline_comment|/* Copy skb to tx_buff while wrapping, stuffing and making CRC */
id|dev-&gt;tx_buff.len
op_assign
id|async_wrap_skb
c_func
(paren
id|skb
comma
id|dev-&gt;tx_buff.data
comma
id|dev-&gt;tx_buff.truesize
)paren
suffix:semicolon
multiline_comment|/* transmission will start now - disable receive.&n;&t; * if we are just in the middle of an incoming frame,&n;&t; * treat it as collision. probably it&squot;s a good idea to&n;&t; * reset the rx_buf OUTSIDE_FRAME in this case too?&n;&t; */
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;enable_rx
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|sirdev_is_receiving
c_func
(paren
id|dev
)paren
)paren
)paren
id|dev-&gt;stats.collisions
op_increment
suffix:semicolon
id|actual
op_assign
id|dev-&gt;drv
op_member_access_from_pointer
id|do_write
c_func
(paren
id|dev
comma
id|dev-&gt;tx_buff.data
comma
id|dev-&gt;tx_buff.len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|actual
OG
l_int|0
)paren
)paren
(brace
id|dev-&gt;tx_skb
op_assign
id|skb
suffix:semicolon
id|ndev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|dev-&gt;tx_buff.data
op_add_assign
id|actual
suffix:semicolon
id|dev-&gt;tx_buff.len
op_sub_assign
id|actual
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|actual
OL
l_int|0
)paren
)paren
(brace
multiline_comment|/* could be dropped later when we have tx_timeout to recover */
id|ERROR
c_func
(paren
l_string|&quot;%s: drv-&gt;do_write failed (%d)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|actual
)paren
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
id|dev-&gt;stats.tx_errors
op_increment
suffix:semicolon
id|dev-&gt;stats.tx_dropped
op_increment
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|ndev
)paren
suffix:semicolon
)brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|dev-&gt;tx_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* called from network layer with rtnl hold */
DECL|function|sirdev_ioctl
r_static
r_int
id|sirdev_ioctl
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
comma
r_struct
id|ifreq
op_star
id|rq
comma
r_int
id|cmd
)paren
(brace
r_struct
id|if_irda_req
op_star
id|irq
op_assign
(paren
r_struct
id|if_irda_req
op_star
)paren
id|rq
suffix:semicolon
r_struct
id|sir_dev
op_star
id|dev
op_assign
id|ndev-&gt;priv
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|ASSERT
c_func
(paren
id|dev
op_ne
l_int|NULL
comma
r_return
op_minus
l_int|1
suffix:semicolon
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|3
comma
l_string|&quot;%s(), %s, (cmd=0x%X)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ndev-&gt;name
comma
id|cmd
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCSBANDWIDTH
suffix:colon
multiline_comment|/* Set bandwidth */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_else
id|ret
op_assign
id|sirdev_schedule_speed
c_func
(paren
id|dev
comma
id|irq-&gt;ifr_baudrate
)paren
suffix:semicolon
multiline_comment|/* cannot sleep here for completion&n;&t;&t; * we are called from network layer with rtnl hold&n;&t;&t; */
r_break
suffix:semicolon
r_case
id|SIOCSDONGLE
suffix:colon
multiline_comment|/* Set dongle */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_else
id|ret
op_assign
id|sirdev_schedule_dongle_open
c_func
(paren
id|dev
comma
id|irq-&gt;ifr_dongle
)paren
suffix:semicolon
multiline_comment|/* cannot sleep here for completion&n;&t;&t; * we are called from network layer with rtnl hold&n;&t;&t; */
r_break
suffix:semicolon
r_case
id|SIOCSMEDIABUSY
suffix:colon
multiline_comment|/* Set media busy */
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_else
id|irda_device_set_media_busy
c_func
(paren
id|dev-&gt;netdev
comma
id|TRUE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIOCGRECEIVING
suffix:colon
multiline_comment|/* Check if we are receiving right now */
id|irq-&gt;ifr_receiving
op_assign
id|sirdev_is_receiving
c_func
(paren
id|dev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIOCSDTRRTS
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_else
id|ret
op_assign
id|sirdev_schedule_dtr_rts
c_func
(paren
id|dev
comma
id|irq-&gt;ifr_dtr
comma
id|irq-&gt;ifr_rts
)paren
suffix:semicolon
multiline_comment|/* cannot sleep here for completion&n;&t;&t; * we are called from network layer with rtnl hold&n;&t;&t; */
r_break
suffix:semicolon
r_case
id|SIOCSMODE
suffix:colon
macro_line|#if 0
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_else
id|ret
op_assign
id|sirdev_schedule_mode
c_func
(paren
id|dev
comma
id|irq-&gt;ifr_mode
)paren
suffix:semicolon
multiline_comment|/* cannot sleep here for completion&n;&t;&t; * we are called from network layer with rtnl hold&n;&t;&t; */
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------------- */
DECL|macro|SIRBUF_ALLOCSIZE
mdefine_line|#define SIRBUF_ALLOCSIZE 4269&t;/* worst case size of a wrapped IrLAP frame */
DECL|function|sirdev_alloc_buffers
r_static
r_int
id|sirdev_alloc_buffers
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
(brace
id|dev-&gt;tx_buff.truesize
op_assign
id|SIRBUF_ALLOCSIZE
suffix:semicolon
id|dev-&gt;rx_buff.truesize
op_assign
id|IRDA_SKB_MAX_MTU
suffix:semicolon
multiline_comment|/* Bootstrap ZeroCopy Rx */
id|dev-&gt;rx_buff.skb
op_assign
id|__dev_alloc_skb
c_func
(paren
id|dev-&gt;rx_buff.truesize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;rx_buff.skb
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|skb_reserve
c_func
(paren
id|dev-&gt;rx_buff.skb
comma
l_int|1
)paren
suffix:semicolon
id|dev-&gt;rx_buff.head
op_assign
id|dev-&gt;rx_buff.skb-&gt;data
suffix:semicolon
id|dev-&gt;tx_buff.head
op_assign
id|kmalloc
c_func
(paren
id|dev-&gt;tx_buff.truesize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;tx_buff.head
op_eq
l_int|NULL
)paren
(brace
id|kfree_skb
c_func
(paren
id|dev-&gt;rx_buff.skb
)paren
suffix:semicolon
id|dev-&gt;rx_buff.skb
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;rx_buff.head
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|dev-&gt;tx_buff.data
op_assign
id|dev-&gt;tx_buff.head
suffix:semicolon
id|dev-&gt;rx_buff.data
op_assign
id|dev-&gt;rx_buff.head
suffix:semicolon
id|dev-&gt;tx_buff.len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;rx_buff.len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;rx_buff.in_frame
op_assign
id|FALSE
suffix:semicolon
id|dev-&gt;rx_buff.state
op_assign
id|OUTSIDE_FRAME
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
DECL|function|sirdev_free_buffers
r_static
r_void
id|sirdev_free_buffers
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;rx_buff.skb
)paren
id|kfree_skb
c_func
(paren
id|dev-&gt;rx_buff.skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;tx_buff.head
)paren
id|kfree
c_func
(paren
id|dev-&gt;tx_buff.head
)paren
suffix:semicolon
id|dev-&gt;rx_buff.head
op_assign
id|dev-&gt;tx_buff.head
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;rx_buff.skb
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|sirdev_open
r_static
r_int
id|sirdev_open
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
)paren
(brace
r_struct
id|sir_dev
op_star
id|dev
op_assign
id|ndev-&gt;priv
suffix:semicolon
r_const
r_struct
id|sir_driver
op_star
id|drv
op_assign
id|dev-&gt;drv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drv
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* increase the reference count of the driver module before doing serious stuff */
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|drv-&gt;owner
)paren
)paren
r_return
op_minus
id|ESTALE
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s()&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sirdev_alloc_buffers
c_func
(paren
id|dev
)paren
)paren
r_goto
id|errout_dec
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;drv-&gt;start_dev
op_logical_or
id|dev-&gt;drv
op_member_access_from_pointer
id|start_dev
c_func
(paren
id|dev
)paren
)paren
r_goto
id|errout_free
suffix:semicolon
id|sirdev_enable_rx
c_func
(paren
id|dev
)paren
suffix:semicolon
id|netif_start_queue
c_func
(paren
id|ndev
)paren
suffix:semicolon
id|dev-&gt;irlap
op_assign
id|irlap_open
c_func
(paren
id|ndev
comma
op_amp
id|dev-&gt;qos
comma
id|dev-&gt;hwname
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;irlap
)paren
r_goto
id|errout_stop
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|ndev
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s - done, speed = %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|dev-&gt;speed
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|errout_stop
suffix:colon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;enable_rx
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;drv-&gt;stop_dev
)paren
id|dev-&gt;drv
op_member_access_from_pointer
id|stop_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|errout_free
suffix:colon
id|sirdev_free_buffers
c_func
(paren
id|dev
)paren
suffix:semicolon
id|errout_dec
suffix:colon
id|module_put
c_func
(paren
id|drv-&gt;owner
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
DECL|function|sirdev_close
r_static
r_int
id|sirdev_close
c_func
(paren
r_struct
id|net_device
op_star
id|ndev
)paren
(brace
r_struct
id|sir_dev
op_star
id|dev
op_assign
id|ndev-&gt;priv
suffix:semicolon
r_const
r_struct
id|sir_driver
op_star
id|drv
suffix:semicolon
singleline_comment|//&t;IRDA_DEBUG(0, &quot;%s&bslash;n&quot;, __FUNCTION__);
id|netif_stop_queue
c_func
(paren
id|ndev
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;fsm.sem
)paren
suffix:semicolon
multiline_comment|/* block on pending config completion */
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;enable_rx
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|dev-&gt;irlap
)paren
)paren
r_goto
id|out
suffix:semicolon
id|irlap_close
c_func
(paren
id|dev-&gt;irlap
)paren
suffix:semicolon
id|dev-&gt;irlap
op_assign
l_int|NULL
suffix:semicolon
id|drv
op_assign
id|dev-&gt;drv
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|drv
op_logical_or
op_logical_neg
id|dev-&gt;priv
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|drv-&gt;stop_dev
)paren
id|drv
op_member_access_from_pointer
id|stop_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|sirdev_free_buffers
c_func
(paren
id|dev
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|drv-&gt;owner
)paren
suffix:semicolon
id|out
suffix:colon
id|dev-&gt;speed
op_assign
l_int|0
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;fsm.sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------------- */
DECL|function|sirdev_get_instance
r_struct
id|sir_dev
op_star
id|sirdev_get_instance
c_func
(paren
r_const
r_struct
id|sir_driver
op_star
id|drv
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|net_device
op_star
id|ndev
suffix:semicolon
r_struct
id|sir_dev
op_star
id|dev
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s - %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|name
)paren
suffix:semicolon
multiline_comment|/* instead of adding tests to protect against drv-&gt;do_write==NULL&n;&t; * at several places we refuse to create a sir_dev instance for&n;&t; * drivers which don&squot;t implement do_write.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|drv
op_logical_or
op_logical_neg
id|drv-&gt;do_write
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; *  Allocate new instance of the device&n;&t; */
id|ndev
op_assign
id|alloc_irdadev
c_func
(paren
r_sizeof
(paren
op_star
id|dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ndev
op_eq
l_int|NULL
)paren
(brace
id|ERROR
c_func
(paren
l_string|&quot;%s - Can&squot;t allocate memory for IrDA control block!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|dev
op_assign
id|ndev-&gt;priv
suffix:semicolon
id|irda_init_max_qos_capabilies
c_func
(paren
op_amp
id|dev-&gt;qos
)paren
suffix:semicolon
id|dev-&gt;qos.baud_rate.bits
op_assign
id|IR_9600
op_or
id|IR_19200
op_or
id|IR_38400
op_or
id|IR_57600
op_or
id|IR_115200
suffix:semicolon
id|dev-&gt;qos.min_turn_time.bits
op_assign
id|drv-&gt;qos_mtt_bits
suffix:semicolon
id|irda_qos_bits_to_value
c_func
(paren
op_amp
id|dev-&gt;qos
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|dev-&gt;hwname
comma
id|name
comma
r_sizeof
(paren
id|dev-&gt;hwname
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;enable_rx
comma
l_int|0
)paren
suffix:semicolon
id|dev-&gt;tx_skb
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|dev-&gt;tx_lock
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|dev-&gt;fsm.sem
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|dev-&gt;fsm.rq.lh_request
)paren
suffix:semicolon
id|dev-&gt;fsm.rq.pending
op_assign
l_int|0
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|dev-&gt;fsm.rq.timer
)paren
suffix:semicolon
id|dev-&gt;drv
op_assign
id|drv
suffix:semicolon
id|dev-&gt;netdev
op_assign
id|ndev
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|ndev
)paren
suffix:semicolon
id|dev-&gt;flags
op_assign
id|IFF_SIR
op_or
id|IFF_PIO
suffix:semicolon
multiline_comment|/* Override the network functions we need to use */
id|ndev-&gt;hard_start_xmit
op_assign
id|sirdev_hard_xmit
suffix:semicolon
id|ndev-&gt;open
op_assign
id|sirdev_open
suffix:semicolon
id|ndev-&gt;stop
op_assign
id|sirdev_close
suffix:semicolon
id|ndev-&gt;get_stats
op_assign
id|sirdev_get_stats
suffix:semicolon
id|ndev-&gt;do_ioctl
op_assign
id|sirdev_ioctl
suffix:semicolon
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
id|ndev
)paren
)paren
(brace
id|ERROR
c_func
(paren
l_string|&quot;%s(), register_netdev() failed!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_goto
id|out_freenetdev
suffix:semicolon
)brace
r_return
id|dev
suffix:semicolon
id|out_freenetdev
suffix:colon
id|free_netdev
c_func
(paren
id|ndev
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|sirdev_put_instance
r_int
id|sirdev_put_instance
c_func
(paren
r_struct
id|sir_dev
op_star
id|dev
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;enable_rx
comma
l_int|0
)paren
suffix:semicolon
id|netif_carrier_off
c_func
(paren
id|dev-&gt;netdev
)paren
suffix:semicolon
id|netif_device_detach
c_func
(paren
id|dev-&gt;netdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;dongle_drv
)paren
id|err
op_assign
id|sirdev_schedule_dongle_close
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|ERROR
c_func
(paren
l_string|&quot;%s - error %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|err
)paren
suffix:semicolon
id|sirdev_close
c_func
(paren
id|dev-&gt;netdev
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;fsm.sem
)paren
suffix:semicolon
id|dev-&gt;fsm.state
op_assign
id|SIRDEV_STATE_DEAD
suffix:semicolon
multiline_comment|/* mark staled */
id|dev-&gt;dongle_drv
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;priv
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;fsm.sem
)paren
suffix:semicolon
multiline_comment|/* Remove netdevice */
id|unregister_netdev
c_func
(paren
id|dev-&gt;netdev
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev-&gt;netdev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
