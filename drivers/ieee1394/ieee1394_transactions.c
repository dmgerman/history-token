multiline_comment|/*&n; * IEEE 1394 for Linux&n; *&n; * Transaction support.&n; *&n; * Copyright (C) 1999 Andreas E. Bombe&n; *&n; * This code is licensed under the GPL.  See the file COPYING in the root&n; * directory of the kernel sources for details.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;ieee1394.h&quot;
macro_line|#include &quot;ieee1394_types.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;ieee1394_core.h&quot;
macro_line|#include &quot;highlevel.h&quot;
macro_line|#include &quot;nodemgr.h&quot;
DECL|macro|PREP_ASYNC_HEAD_ADDRESS
mdefine_line|#define PREP_ASYNC_HEAD_ADDRESS(tc) &bslash;&n;        packet-&gt;tcode = tc; &bslash;&n;        packet-&gt;header[0] = (packet-&gt;node_id &lt;&lt; 16) | (packet-&gt;tlabel &lt;&lt; 10) &bslash;&n;                | (1 &lt;&lt; 8) | (tc &lt;&lt; 4); &bslash;&n;        packet-&gt;header[1] = (packet-&gt;host-&gt;node_id &lt;&lt; 16) | (addr &gt;&gt; 32); &bslash;&n;        packet-&gt;header[2] = addr &amp; 0xffffffff
DECL|function|fill_async_readquad
r_static
r_void
id|fill_async_readquad
c_func
(paren
r_struct
id|hpsb_packet
op_star
id|packet
comma
id|u64
id|addr
)paren
(brace
id|PREP_ASYNC_HEAD_ADDRESS
c_func
(paren
id|TCODE_READQ
)paren
suffix:semicolon
id|packet-&gt;header_size
op_assign
l_int|12
suffix:semicolon
id|packet-&gt;data_size
op_assign
l_int|0
suffix:semicolon
id|packet-&gt;expect_response
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|fill_async_readblock
r_static
r_void
id|fill_async_readblock
c_func
(paren
r_struct
id|hpsb_packet
op_star
id|packet
comma
id|u64
id|addr
comma
r_int
id|length
)paren
(brace
id|PREP_ASYNC_HEAD_ADDRESS
c_func
(paren
id|TCODE_READB
)paren
suffix:semicolon
id|packet-&gt;header
(braket
l_int|3
)braket
op_assign
id|length
op_lshift
l_int|16
suffix:semicolon
id|packet-&gt;header_size
op_assign
l_int|16
suffix:semicolon
id|packet-&gt;data_size
op_assign
l_int|0
suffix:semicolon
id|packet-&gt;expect_response
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|fill_async_writequad
r_static
r_void
id|fill_async_writequad
c_func
(paren
r_struct
id|hpsb_packet
op_star
id|packet
comma
id|u64
id|addr
comma
id|quadlet_t
id|data
)paren
(brace
id|PREP_ASYNC_HEAD_ADDRESS
c_func
(paren
id|TCODE_WRITEQ
)paren
suffix:semicolon
id|packet-&gt;header
(braket
l_int|3
)braket
op_assign
id|data
suffix:semicolon
id|packet-&gt;header_size
op_assign
l_int|16
suffix:semicolon
id|packet-&gt;data_size
op_assign
l_int|0
suffix:semicolon
id|packet-&gt;expect_response
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|fill_async_writeblock
r_static
r_void
id|fill_async_writeblock
c_func
(paren
r_struct
id|hpsb_packet
op_star
id|packet
comma
id|u64
id|addr
comma
r_int
id|length
)paren
(brace
id|PREP_ASYNC_HEAD_ADDRESS
c_func
(paren
id|TCODE_WRITEB
)paren
suffix:semicolon
id|packet-&gt;header
(braket
l_int|3
)braket
op_assign
id|length
op_lshift
l_int|16
suffix:semicolon
id|packet-&gt;header_size
op_assign
l_int|16
suffix:semicolon
id|packet-&gt;expect_response
op_assign
l_int|1
suffix:semicolon
id|packet-&gt;data_size
op_assign
id|length
op_plus
(paren
id|length
op_mod
l_int|4
ques
c_cond
l_int|4
op_minus
(paren
id|length
op_mod
l_int|4
)paren
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|fill_async_lock
r_static
r_void
id|fill_async_lock
c_func
(paren
r_struct
id|hpsb_packet
op_star
id|packet
comma
id|u64
id|addr
comma
r_int
id|extcode
comma
r_int
id|length
)paren
(brace
id|PREP_ASYNC_HEAD_ADDRESS
c_func
(paren
id|TCODE_LOCK_REQUEST
)paren
suffix:semicolon
id|packet-&gt;header
(braket
l_int|3
)braket
op_assign
(paren
id|length
op_lshift
l_int|16
)paren
op_or
id|extcode
suffix:semicolon
id|packet-&gt;header_size
op_assign
l_int|16
suffix:semicolon
id|packet-&gt;data_size
op_assign
id|length
suffix:semicolon
id|packet-&gt;expect_response
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|fill_iso_packet
r_static
r_void
id|fill_iso_packet
c_func
(paren
r_struct
id|hpsb_packet
op_star
id|packet
comma
r_int
id|length
comma
r_int
id|channel
comma
r_int
id|tag
comma
r_int
id|sync
)paren
(brace
id|packet-&gt;header
(braket
l_int|0
)braket
op_assign
(paren
id|length
op_lshift
l_int|16
)paren
op_or
(paren
id|tag
op_lshift
l_int|14
)paren
op_or
(paren
id|channel
op_lshift
l_int|8
)paren
op_or
(paren
id|TCODE_ISO_DATA
op_lshift
l_int|4
)paren
op_or
id|sync
suffix:semicolon
id|packet-&gt;header_size
op_assign
l_int|4
suffix:semicolon
id|packet-&gt;data_size
op_assign
id|length
suffix:semicolon
id|packet-&gt;type
op_assign
id|hpsb_iso
suffix:semicolon
id|packet-&gt;tcode
op_assign
id|TCODE_ISO_DATA
suffix:semicolon
)brace
DECL|function|fill_phy_packet
r_static
r_void
id|fill_phy_packet
c_func
(paren
r_struct
id|hpsb_packet
op_star
id|packet
comma
id|quadlet_t
id|data
)paren
(brace
id|packet-&gt;header
(braket
l_int|0
)braket
op_assign
id|data
suffix:semicolon
id|packet-&gt;header
(braket
l_int|1
)braket
op_assign
op_complement
id|data
suffix:semicolon
id|packet-&gt;header_size
op_assign
l_int|8
suffix:semicolon
id|packet-&gt;data_size
op_assign
l_int|0
suffix:semicolon
id|packet-&gt;expect_response
op_assign
l_int|0
suffix:semicolon
id|packet-&gt;type
op_assign
id|hpsb_raw
suffix:semicolon
multiline_comment|/* No CRC added */
id|packet-&gt;speed_code
op_assign
id|SPEED_100
suffix:semicolon
multiline_comment|/* Force speed to be 100Mbps */
)brace
DECL|function|fill_async_stream_packet
r_static
r_void
id|fill_async_stream_packet
c_func
(paren
r_struct
id|hpsb_packet
op_star
id|packet
comma
r_int
id|length
comma
r_int
id|channel
comma
r_int
id|tag
comma
r_int
id|sync
)paren
(brace
id|packet-&gt;header
(braket
l_int|0
)braket
op_assign
(paren
id|length
op_lshift
l_int|16
)paren
op_or
(paren
id|tag
op_lshift
l_int|14
)paren
op_or
(paren
id|channel
op_lshift
l_int|8
)paren
op_or
(paren
id|TCODE_STREAM_DATA
op_lshift
l_int|4
)paren
op_or
id|sync
suffix:semicolon
id|packet-&gt;header_size
op_assign
l_int|4
suffix:semicolon
id|packet-&gt;data_size
op_assign
id|length
suffix:semicolon
id|packet-&gt;type
op_assign
id|hpsb_async
suffix:semicolon
id|packet-&gt;tcode
op_assign
id|TCODE_ISO_DATA
suffix:semicolon
)brace
multiline_comment|/**&n; * hpsb_get_tlabel - allocate a transaction label&n; * @packet: the packet who&squot;s tlabel/tpool we set&n; * @wait: whether to sleep if no tlabel is available&n; *&n; * Every asynchronous transaction on the 1394 bus needs a transaction label to&n; * match the response to the request.  This label has to be different from any&n; * other transaction label in an outstanding request to the same node to make&n; * matching possible without ambiguity.&n; *&n; * There are 64 different tlabels, so an allocated tlabel has to be freed with&n; * hpsb_free_tlabel() after the transaction is complete (unless it&squot;s reused again for&n; * the same target node).&n; *&n; * @wait cannot be set if in_interrupt()&n; *&n; * Return value: Zero on success, otherwise non-zero. A non-zero return&n; * generally means there are no available tlabels.&n; */
DECL|function|hpsb_get_tlabel
r_int
id|hpsb_get_tlabel
c_func
(paren
r_struct
id|hpsb_packet
op_star
id|packet
comma
r_int
id|wait
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|hpsb_tlabel_pool
op_star
id|tp
suffix:semicolon
id|tp
op_assign
op_amp
id|packet-&gt;host-&gt;tpool
(braket
id|packet-&gt;node_id
op_amp
id|NODE_MASK
)braket
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
(brace
id|BUG_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|tp-&gt;count
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
id|tp-&gt;count
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|tp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|packet-&gt;tlabel
op_assign
id|find_next_zero_bit
c_func
(paren
op_amp
id|tp-&gt;pool
comma
l_int|64
comma
id|tp-&gt;next
)paren
suffix:semicolon
id|tp-&gt;next
op_assign
(paren
id|packet-&gt;tlabel
op_plus
l_int|1
)paren
op_mod
l_int|64
suffix:semicolon
multiline_comment|/* Should _never_ happen */
id|BUG_ON
c_func
(paren
id|test_and_set_bit
c_func
(paren
id|packet-&gt;tlabel
comma
op_amp
id|tp-&gt;pool
)paren
)paren
suffix:semicolon
id|tp-&gt;allocations
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/** &n; * hpsb_free_tlabel - free an allocated transaction label&n; * @packet: packet whos tlabel/tpool needs to be cleared&n; *&n; * Frees the transaction label allocated with hpsb_get_tlabel().  The&n; * tlabel has to be freed after the transaction is complete (i.e. response&n; * was received for a split transaction or packet was sent for a unified&n; * transaction).&n; *&n; * A tlabel must not be freed twice.&n; */
DECL|function|hpsb_free_tlabel
r_void
id|hpsb_free_tlabel
c_func
(paren
r_struct
id|hpsb_packet
op_star
id|packet
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|hpsb_tlabel_pool
op_star
id|tp
suffix:semicolon
id|tp
op_assign
op_amp
id|packet-&gt;host-&gt;tpool
(braket
id|packet-&gt;node_id
op_amp
id|NODE_MASK
)braket
suffix:semicolon
id|BUG_ON
c_func
(paren
id|packet-&gt;tlabel
OG
l_int|63
op_logical_or
id|packet-&gt;tlabel
OL
l_int|0
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|tp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|test_and_clear_bit
c_func
(paren
id|packet-&gt;tlabel
comma
op_amp
id|tp-&gt;pool
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tp-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|tp-&gt;count
)paren
suffix:semicolon
)brace
DECL|function|hpsb_packet_success
r_int
id|hpsb_packet_success
c_func
(paren
r_struct
id|hpsb_packet
op_star
id|packet
)paren
(brace
r_switch
c_cond
(paren
id|packet-&gt;ack_code
)paren
(brace
r_case
id|ACK_PENDING
suffix:colon
r_switch
c_cond
(paren
(paren
id|packet-&gt;header
(braket
l_int|1
)braket
op_rshift
l_int|12
)paren
op_amp
l_int|0xf
)paren
(brace
r_case
id|RCODE_COMPLETE
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|RCODE_CONFLICT_ERROR
suffix:colon
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_case
id|RCODE_DATA_ERROR
suffix:colon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
r_case
id|RCODE_TYPE_ERROR
suffix:colon
r_return
op_minus
id|EACCES
suffix:semicolon
r_case
id|RCODE_ADDRESS_ERROR
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_default
suffix:colon
id|HPSB_ERR
c_func
(paren
l_string|&quot;received reserved rcode %d from node %d&quot;
comma
(paren
id|packet-&gt;header
(braket
l_int|1
)braket
op_rshift
l_int|12
)paren
op_amp
l_int|0xf
comma
id|packet-&gt;node_id
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|HPSB_PANIC
c_func
(paren
l_string|&quot;reached unreachable code 1 in %s&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_case
id|ACK_BUSY_X
suffix:colon
r_case
id|ACK_BUSY_A
suffix:colon
r_case
id|ACK_BUSY_B
suffix:colon
r_return
op_minus
id|EBUSY
suffix:semicolon
r_case
id|ACK_TYPE_ERROR
suffix:colon
r_return
op_minus
id|EACCES
suffix:semicolon
r_case
id|ACK_COMPLETE
suffix:colon
r_if
c_cond
(paren
id|packet-&gt;tcode
op_eq
id|TCODE_WRITEQ
op_logical_or
id|packet-&gt;tcode
op_eq
id|TCODE_WRITEB
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|HPSB_ERR
c_func
(paren
l_string|&quot;impossible ack_complete from node %d &quot;
l_string|&quot;(tcode %d)&quot;
comma
id|packet-&gt;node_id
comma
id|packet-&gt;tcode
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_case
id|ACK_DATA_ERROR
suffix:colon
r_if
c_cond
(paren
id|packet-&gt;tcode
op_eq
id|TCODE_WRITEB
op_logical_or
id|packet-&gt;tcode
op_eq
id|TCODE_LOCK_REQUEST
)paren
(brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_else
(brace
id|HPSB_ERR
c_func
(paren
l_string|&quot;impossible ack_data_error from node %d &quot;
l_string|&quot;(tcode %d)&quot;
comma
id|packet-&gt;node_id
comma
id|packet-&gt;tcode
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_case
id|ACKX_NONE
suffix:colon
r_case
id|ACKX_SEND_ERROR
suffix:colon
r_case
id|ACKX_ABORTED
suffix:colon
r_case
id|ACKX_TIMEOUT
suffix:colon
multiline_comment|/* error while sending */
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_default
suffix:colon
id|HPSB_ERR
c_func
(paren
l_string|&quot;got invalid ack %d from node %d (tcode %d)&quot;
comma
id|packet-&gt;ack_code
comma
id|packet-&gt;node_id
comma
id|packet-&gt;tcode
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|HPSB_PANIC
c_func
(paren
l_string|&quot;reached unreachable code 2 in %s&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
DECL|function|hpsb_make_readpacket
r_struct
id|hpsb_packet
op_star
id|hpsb_make_readpacket
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
id|nodeid_t
id|node
comma
id|u64
id|addr
comma
r_int
id|length
)paren
(brace
r_struct
id|hpsb_packet
op_star
id|packet
suffix:semicolon
r_if
c_cond
(paren
id|length
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|packet
op_assign
id|alloc_hpsb_packet
c_func
(paren
id|length
op_plus
(paren
id|length
op_mod
l_int|4
ques
c_cond
l_int|4
op_minus
(paren
id|length
op_mod
l_int|4
)paren
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|packet
)paren
r_return
l_int|NULL
suffix:semicolon
id|packet-&gt;host
op_assign
id|host
suffix:semicolon
id|packet-&gt;node_id
op_assign
id|node
suffix:semicolon
r_if
c_cond
(paren
id|hpsb_get_tlabel
c_func
(paren
id|packet
comma
id|in_interrupt
c_func
(paren
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
)paren
(brace
id|free_hpsb_packet
c_func
(paren
id|packet
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|length
op_eq
l_int|4
)paren
id|fill_async_readquad
c_func
(paren
id|packet
comma
id|addr
)paren
suffix:semicolon
r_else
id|fill_async_readblock
c_func
(paren
id|packet
comma
id|addr
comma
id|length
)paren
suffix:semicolon
r_return
id|packet
suffix:semicolon
)brace
DECL|function|hpsb_make_writepacket
r_struct
id|hpsb_packet
op_star
id|hpsb_make_writepacket
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
id|nodeid_t
id|node
comma
id|u64
id|addr
comma
id|quadlet_t
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
r_struct
id|hpsb_packet
op_star
id|packet
suffix:semicolon
r_if
c_cond
(paren
id|length
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
id|packet
op_assign
id|alloc_hpsb_packet
c_func
(paren
id|length
op_plus
(paren
id|length
op_mod
l_int|4
ques
c_cond
l_int|4
op_minus
(paren
id|length
op_mod
l_int|4
)paren
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|packet
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|length
op_mod
l_int|4
)paren
(brace
multiline_comment|/* zero padding bytes */
id|packet-&gt;data
(braket
id|length
op_rshift
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|packet-&gt;host
op_assign
id|host
suffix:semicolon
id|packet-&gt;node_id
op_assign
id|node
suffix:semicolon
r_if
c_cond
(paren
id|hpsb_get_tlabel
c_func
(paren
id|packet
comma
id|in_interrupt
c_func
(paren
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
)paren
(brace
id|free_hpsb_packet
c_func
(paren
id|packet
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|length
op_eq
l_int|4
)paren
(brace
id|fill_async_writequad
c_func
(paren
id|packet
comma
id|addr
comma
id|buffer
ques
c_cond
op_star
id|buffer
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|fill_async_writeblock
c_func
(paren
id|packet
comma
id|addr
comma
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
)paren
id|memcpy
c_func
(paren
id|packet-&gt;data
comma
id|buffer
comma
id|length
)paren
suffix:semicolon
)brace
r_return
id|packet
suffix:semicolon
)brace
DECL|function|hpsb_make_lockpacket
r_struct
id|hpsb_packet
op_star
id|hpsb_make_lockpacket
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
id|nodeid_t
id|node
comma
id|u64
id|addr
comma
r_int
id|extcode
comma
id|quadlet_t
op_star
id|data
comma
id|quadlet_t
id|arg
)paren
(brace
r_struct
id|hpsb_packet
op_star
id|p
suffix:semicolon
id|u32
id|length
suffix:semicolon
id|p
op_assign
id|alloc_hpsb_packet
c_func
(paren
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|NULL
suffix:semicolon
id|p-&gt;host
op_assign
id|host
suffix:semicolon
id|p-&gt;node_id
op_assign
id|node
suffix:semicolon
r_if
c_cond
(paren
id|hpsb_get_tlabel
c_func
(paren
id|p
comma
id|in_interrupt
c_func
(paren
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
)paren
(brace
id|free_hpsb_packet
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|extcode
)paren
(brace
r_case
id|EXTCODE_FETCH_ADD
suffix:colon
r_case
id|EXTCODE_LITTLE_ADD
suffix:colon
id|length
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
id|p-&gt;data
(braket
l_int|0
)braket
op_assign
op_star
id|data
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|length
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
(brace
id|p-&gt;data
(braket
l_int|0
)braket
op_assign
id|arg
suffix:semicolon
id|p-&gt;data
(braket
l_int|1
)braket
op_assign
op_star
id|data
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|fill_async_lock
c_func
(paren
id|p
comma
id|addr
comma
id|extcode
comma
id|length
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|hpsb_make_lock64packet
r_struct
id|hpsb_packet
op_star
id|hpsb_make_lock64packet
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
id|nodeid_t
id|node
comma
id|u64
id|addr
comma
r_int
id|extcode
comma
id|octlet_t
op_star
id|data
comma
id|octlet_t
id|arg
)paren
(brace
r_struct
id|hpsb_packet
op_star
id|p
suffix:semicolon
id|u32
id|length
suffix:semicolon
id|p
op_assign
id|alloc_hpsb_packet
c_func
(paren
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|NULL
suffix:semicolon
id|p-&gt;host
op_assign
id|host
suffix:semicolon
id|p-&gt;node_id
op_assign
id|node
suffix:semicolon
r_if
c_cond
(paren
id|hpsb_get_tlabel
c_func
(paren
id|p
comma
id|in_interrupt
c_func
(paren
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
)paren
(brace
id|free_hpsb_packet
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|extcode
)paren
(brace
r_case
id|EXTCODE_FETCH_ADD
suffix:colon
r_case
id|EXTCODE_LITTLE_ADD
suffix:colon
id|length
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
(brace
id|p-&gt;data
(braket
l_int|0
)braket
op_assign
op_star
id|data
op_rshift
l_int|32
suffix:semicolon
id|p-&gt;data
(braket
l_int|1
)braket
op_assign
op_star
id|data
op_amp
l_int|0xffffffff
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|length
op_assign
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
(brace
id|p-&gt;data
(braket
l_int|0
)braket
op_assign
id|arg
op_rshift
l_int|32
suffix:semicolon
id|p-&gt;data
(braket
l_int|1
)braket
op_assign
id|arg
op_amp
l_int|0xffffffff
suffix:semicolon
id|p-&gt;data
(braket
l_int|2
)braket
op_assign
op_star
id|data
op_rshift
l_int|32
suffix:semicolon
id|p-&gt;data
(braket
l_int|3
)braket
op_assign
op_star
id|data
op_amp
l_int|0xffffffff
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|fill_async_lock
c_func
(paren
id|p
comma
id|addr
comma
id|extcode
comma
id|length
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|hpsb_make_phypacket
r_struct
id|hpsb_packet
op_star
id|hpsb_make_phypacket
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
id|quadlet_t
id|data
)paren
(brace
r_struct
id|hpsb_packet
op_star
id|p
suffix:semicolon
id|p
op_assign
id|alloc_hpsb_packet
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|NULL
suffix:semicolon
id|p-&gt;host
op_assign
id|host
suffix:semicolon
id|fill_phy_packet
c_func
(paren
id|p
comma
id|data
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|hpsb_make_isopacket
r_struct
id|hpsb_packet
op_star
id|hpsb_make_isopacket
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|length
comma
r_int
id|channel
comma
r_int
id|tag
comma
r_int
id|sync
)paren
(brace
r_struct
id|hpsb_packet
op_star
id|p
suffix:semicolon
id|p
op_assign
id|alloc_hpsb_packet
c_func
(paren
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|NULL
suffix:semicolon
id|p-&gt;host
op_assign
id|host
suffix:semicolon
id|fill_iso_packet
c_func
(paren
id|p
comma
id|length
comma
id|channel
comma
id|tag
comma
id|sync
)paren
suffix:semicolon
id|p-&gt;generation
op_assign
id|get_hpsb_generation
c_func
(paren
id|host
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * FIXME - these functions should probably read from / write to user space to&n; * avoid in kernel buffers for user space callers&n; */
DECL|function|hpsb_read
r_int
id|hpsb_read
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
id|nodeid_t
id|node
comma
r_int
r_int
id|generation
comma
id|u64
id|addr
comma
id|quadlet_t
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
r_struct
id|hpsb_packet
op_star
id|packet
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|length
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|BUG_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
singleline_comment|// We can&squot;t be called in an interrupt, yet
id|packet
op_assign
id|hpsb_make_readpacket
c_func
(paren
id|host
comma
id|node
comma
id|addr
comma
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|packet
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|packet-&gt;generation
op_assign
id|generation
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hpsb_send_packet
c_func
(paren
id|packet
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|hpsb_read_fail
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|packet-&gt;state_change
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|packet-&gt;state_change
)paren
suffix:semicolon
id|retval
op_assign
id|hpsb_packet_success
c_func
(paren
id|packet
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|length
op_eq
l_int|4
)paren
(brace
op_star
id|buffer
op_assign
id|packet-&gt;header
(braket
l_int|3
)braket
suffix:semicolon
)brace
r_else
(brace
id|memcpy
c_func
(paren
id|buffer
comma
id|packet-&gt;data
comma
id|length
)paren
suffix:semicolon
)brace
)brace
id|hpsb_read_fail
suffix:colon
id|hpsb_free_tlabel
c_func
(paren
id|packet
)paren
suffix:semicolon
id|free_hpsb_packet
c_func
(paren
id|packet
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|hpsb_write
r_int
id|hpsb_write
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
id|nodeid_t
id|node
comma
r_int
r_int
id|generation
comma
id|u64
id|addr
comma
id|quadlet_t
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
r_struct
id|hpsb_packet
op_star
id|packet
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|length
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|BUG_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
singleline_comment|// We can&squot;t be called in an interrupt, yet
id|packet
op_assign
id|hpsb_make_writepacket
(paren
id|host
comma
id|node
comma
id|addr
comma
id|buffer
comma
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|packet
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|packet-&gt;generation
op_assign
id|generation
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hpsb_send_packet
c_func
(paren
id|packet
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|hpsb_write_fail
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|packet-&gt;state_change
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|packet-&gt;state_change
)paren
suffix:semicolon
id|retval
op_assign
id|hpsb_packet_success
c_func
(paren
id|packet
)paren
suffix:semicolon
id|hpsb_write_fail
suffix:colon
id|hpsb_free_tlabel
c_func
(paren
id|packet
)paren
suffix:semicolon
id|free_hpsb_packet
c_func
(paren
id|packet
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|hpsb_lock
r_int
id|hpsb_lock
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
id|nodeid_t
id|node
comma
r_int
r_int
id|generation
comma
id|u64
id|addr
comma
r_int
id|extcode
comma
id|quadlet_t
op_star
id|data
comma
id|quadlet_t
id|arg
)paren
(brace
r_struct
id|hpsb_packet
op_star
id|packet
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|BUG_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
singleline_comment|// We can&squot;t be called in an interrupt, yet
id|packet
op_assign
id|hpsb_make_lockpacket
c_func
(paren
id|host
comma
id|node
comma
id|addr
comma
id|extcode
comma
id|data
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|packet
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|packet-&gt;generation
op_assign
id|generation
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hpsb_send_packet
c_func
(paren
id|packet
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|hpsb_lock_fail
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|packet-&gt;state_change
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|packet-&gt;state_change
)paren
suffix:semicolon
id|retval
op_assign
id|hpsb_packet_success
c_func
(paren
id|packet
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
(brace
op_star
id|data
op_assign
id|packet-&gt;data
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|hpsb_lock_fail
suffix:colon
id|hpsb_free_tlabel
c_func
(paren
id|packet
)paren
suffix:semicolon
id|free_hpsb_packet
c_func
(paren
id|packet
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|hpsb_lock64
r_int
id|hpsb_lock64
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
id|nodeid_t
id|node
comma
r_int
r_int
id|generation
comma
id|u64
id|addr
comma
r_int
id|extcode
comma
id|octlet_t
op_star
id|data
comma
id|octlet_t
id|arg
)paren
(brace
r_struct
id|hpsb_packet
op_star
id|packet
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|BUG_ON
c_func
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
suffix:semicolon
singleline_comment|// We can&squot;t be called in an interrupt, yet
id|packet
op_assign
id|hpsb_make_lock64packet
c_func
(paren
id|host
comma
id|node
comma
id|addr
comma
id|extcode
comma
id|data
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|packet
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|packet-&gt;generation
op_assign
id|generation
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hpsb_send_packet
c_func
(paren
id|packet
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|hpsb_lock64_fail
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|packet-&gt;state_change
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|packet-&gt;state_change
)paren
suffix:semicolon
id|retval
op_assign
id|hpsb_packet_success
c_func
(paren
id|packet
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
op_star
id|data
op_assign
(paren
id|u64
)paren
id|packet-&gt;data
(braket
l_int|1
)braket
op_lshift
l_int|32
op_or
id|packet-&gt;data
(braket
l_int|0
)braket
suffix:semicolon
id|hpsb_lock64_fail
suffix:colon
id|hpsb_free_tlabel
c_func
(paren
id|packet
)paren
suffix:semicolon
id|free_hpsb_packet
c_func
(paren
id|packet
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|hpsb_send_gasp
r_int
id|hpsb_send_gasp
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|channel
comma
r_int
r_int
id|generation
comma
id|quadlet_t
op_star
id|buffer
comma
r_int
id|length
comma
id|u32
id|specifier_id
comma
r_int
r_int
id|version
)paren
(brace
macro_line|#ifdef CONFIG_IEEE1394_VERBOSEDEBUG
r_int
id|i
suffix:semicolon
macro_line|#endif
r_struct
id|hpsb_packet
op_star
id|packet
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|u16
id|specifier_id_hi
op_assign
(paren
id|specifier_id
op_amp
l_int|0x00ffff00
)paren
op_rshift
l_int|8
suffix:semicolon
id|u8
id|specifier_id_lo
op_assign
id|specifier_id
op_amp
l_int|0xff
suffix:semicolon
macro_line|#ifdef CONFIG_IEEE1394_VERBOSEDEBUG
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;Send GASP: channel = %d, length = %d&quot;
comma
id|channel
comma
id|length
)paren
suffix:semicolon
macro_line|#endif
id|length
op_add_assign
l_int|8
suffix:semicolon
id|packet
op_assign
id|alloc_hpsb_packet
c_func
(paren
id|length
op_plus
(paren
id|length
op_mod
l_int|4
ques
c_cond
l_int|4
op_minus
(paren
id|length
op_mod
l_int|4
)paren
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|packet
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|length
op_mod
l_int|4
)paren
(brace
id|packet-&gt;data
(braket
id|length
op_div
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|packet-&gt;host
op_assign
id|host
suffix:semicolon
id|fill_async_stream_packet
c_func
(paren
id|packet
comma
id|length
comma
id|channel
comma
l_int|3
comma
l_int|0
)paren
suffix:semicolon
id|packet-&gt;data
(braket
l_int|0
)braket
op_assign
id|cpu_to_be32
c_func
(paren
(paren
id|host-&gt;node_id
op_lshift
l_int|16
)paren
op_or
id|specifier_id_hi
)paren
suffix:semicolon
id|packet-&gt;data
(braket
l_int|1
)braket
op_assign
id|cpu_to_be32
c_func
(paren
(paren
id|specifier_id_lo
op_lshift
l_int|24
)paren
op_or
(paren
id|version
op_amp
l_int|0x00ffffff
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
(paren
id|packet-&gt;data
(braket
l_int|2
)braket
)paren
comma
id|buffer
comma
id|length
op_minus
l_int|4
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IEEE1394_VERBOSEDEBUG
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;GASP: packet-&gt;header_size = %d&quot;
comma
id|packet-&gt;header_size
)paren
suffix:semicolon
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;GASP: packet-&gt;data_size = %d&quot;
comma
id|packet-&gt;data_size
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
(paren
id|packet-&gt;data_size
op_div
l_int|4
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|HPSB_DEBUG
c_func
(paren
l_string|&quot;GASP: data[%d]: 0x%08x&quot;
comma
id|i
op_star
l_int|4
comma
id|be32_to_cpu
c_func
(paren
id|packet-&gt;data
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|packet-&gt;generation
op_assign
id|generation
suffix:semicolon
id|packet-&gt;no_waiter
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hpsb_send_packet
c_func
(paren
id|packet
)paren
)paren
(brace
id|free_hpsb_packet
c_func
(paren
id|packet
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
eof
