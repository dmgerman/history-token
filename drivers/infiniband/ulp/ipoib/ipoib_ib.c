multiline_comment|/*&n; * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.&n; *&n; * This software is available to you under a choice of one of two&n; * licenses.  You may choose to be licensed under the terms of the GNU&n; * General Public License (GPL) Version 2, available from the file&n; * COPYING in the main directory of this source tree, or the&n; * OpenIB.org BSD license below:&n; *&n; *     Redistribution and use in source and binary forms, with or&n; *     without modification, are permitted provided that the following&n; *     conditions are met:&n; *&n; *      - Redistributions of source code must retain the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer.&n; *&n; *      - Redistributions in binary form must reproduce the above&n; *        copyright notice, this list of conditions and the following&n; *        disclaimer in the documentation and/or other materials&n; *        provided with the distribution.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND,&n; * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF&n; * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND&n; * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS&n; * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN&n; * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN&n; * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE&n; * SOFTWARE.&n; *&n; * $Id: ipoib_ib.c 1386 2004-12-27 16:23:17Z roland $&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;ib_cache.h&gt;
macro_line|#include &quot;ipoib.h&quot;
macro_line|#ifdef CONFIG_INFINIBAND_IPOIB_DEBUG_DATA
DECL|variable|data_debug_level
r_int
id|data_debug_level
suffix:semicolon
id|module_param
c_func
(paren
id|data_debug_level
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|data_debug_level
comma
l_string|&quot;Enable data path debug tracing if &gt; 0&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|IPOIB_OP_RECV
mdefine_line|#define&t;IPOIB_OP_RECV&t;(1ul &lt;&lt; 31)
r_static
id|DECLARE_MUTEX
c_func
(paren
id|pkey_sem
)paren
suffix:semicolon
DECL|function|ipoib_create_ah
r_struct
id|ipoib_ah
op_star
id|ipoib_create_ah
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ib_pd
op_star
id|pd
comma
r_struct
id|ib_ah_attr
op_star
id|attr
)paren
(brace
r_struct
id|ipoib_ah
op_star
id|ah
suffix:semicolon
id|ah
op_assign
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|ah
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ah
)paren
r_return
l_int|NULL
suffix:semicolon
id|ah-&gt;dev
op_assign
id|dev
suffix:semicolon
id|ah-&gt;last_send
op_assign
l_int|0
suffix:semicolon
id|kref_init
c_func
(paren
op_amp
id|ah-&gt;ref
)paren
suffix:semicolon
id|ah-&gt;ah
op_assign
id|ib_create_ah
c_func
(paren
id|pd
comma
id|attr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|ah-&gt;ah
)paren
)paren
(brace
id|kfree
c_func
(paren
id|ah
)paren
suffix:semicolon
id|ah
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
id|ipoib_dbg
c_func
(paren
id|netdev_priv
c_func
(paren
id|dev
)paren
comma
l_string|&quot;Created ah %p&bslash;n&quot;
comma
id|ah-&gt;ah
)paren
suffix:semicolon
r_return
id|ah
suffix:semicolon
)brace
DECL|function|ipoib_free_ah
r_void
id|ipoib_free_ah
c_func
(paren
r_struct
id|kref
op_star
id|kref
)paren
(brace
r_struct
id|ipoib_ah
op_star
id|ah
op_assign
id|container_of
c_func
(paren
id|kref
comma
r_struct
id|ipoib_ah
comma
id|ref
)paren
suffix:semicolon
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|ah-&gt;dev
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|ah-&gt;last_send
op_le
id|priv-&gt;tx_tail
)paren
(brace
id|ipoib_dbg
c_func
(paren
id|priv
comma
l_string|&quot;Freeing ah %p&bslash;n&quot;
comma
id|ah-&gt;ah
)paren
suffix:semicolon
id|ib_destroy_ah
c_func
(paren
id|ah-&gt;ah
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ah
)paren
suffix:semicolon
)brace
r_else
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|ah-&gt;list
comma
op_amp
id|priv-&gt;dead_ahs
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
DECL|function|ipoib_ib_receive
r_static
r_inline
r_int
id|ipoib_ib_receive
c_func
(paren
r_struct
id|ipoib_dev_priv
op_star
id|priv
comma
r_int
r_int
id|wr_id
comma
id|dma_addr_t
id|addr
)paren
(brace
r_struct
id|ib_sge
id|list
op_assign
(brace
dot
id|addr
op_assign
id|addr
comma
dot
id|length
op_assign
id|IPOIB_BUF_SIZE
comma
dot
id|lkey
op_assign
id|priv-&gt;mr-&gt;lkey
comma
)brace
suffix:semicolon
r_struct
id|ib_recv_wr
id|param
op_assign
(brace
dot
id|wr_id
op_assign
id|wr_id
op_or
id|IPOIB_OP_RECV
comma
dot
id|sg_list
op_assign
op_amp
id|list
comma
dot
id|num_sge
op_assign
l_int|1
comma
dot
id|recv_flags
op_assign
id|IB_RECV_SIGNALED
)brace
suffix:semicolon
r_struct
id|ib_recv_wr
op_star
id|bad_wr
suffix:semicolon
r_return
id|ib_post_recv
c_func
(paren
id|priv-&gt;qp
comma
op_amp
id|param
comma
op_amp
id|bad_wr
)paren
suffix:semicolon
)brace
DECL|function|ipoib_ib_post_receive
r_static
r_int
id|ipoib_ib_post_receive
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|id
)paren
(brace
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|dma_addr_t
id|addr
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|IPOIB_BUF_SIZE
op_plus
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb
)paren
(brace
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;failed to allocate receive buffer&bslash;n&quot;
)paren
suffix:semicolon
id|priv-&gt;rx_ring
(braket
id|id
)braket
dot
id|skb
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|skb_reserve
c_func
(paren
id|skb
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* 16 byte align IP header */
id|priv-&gt;rx_ring
(braket
id|id
)braket
dot
id|skb
op_assign
id|skb
suffix:semicolon
id|addr
op_assign
id|dma_map_single
c_func
(paren
id|priv-&gt;ca-&gt;dma_device
comma
id|skb-&gt;data
comma
id|IPOIB_BUF_SIZE
comma
id|DMA_FROM_DEVICE
)paren
suffix:semicolon
id|pci_unmap_addr_set
c_func
(paren
op_amp
id|priv-&gt;rx_ring
(braket
id|id
)braket
comma
id|mapping
comma
id|addr
)paren
suffix:semicolon
id|ret
op_assign
id|ipoib_ib_receive
c_func
(paren
id|priv
comma
id|id
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;ipoib_ib_receive failed for buf %d (%d)&bslash;n&quot;
comma
id|id
comma
id|ret
)paren
suffix:semicolon
id|priv-&gt;rx_ring
(braket
id|id
)braket
dot
id|skb
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ipoib_ib_post_receives
r_static
r_int
id|ipoib_ib_post_receives
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|i
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
id|IPOIB_RX_RING_SIZE
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|ipoib_ib_post_receive
c_func
(paren
id|dev
comma
id|i
)paren
)paren
(brace
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;ipoib_ib_post_receive failed for buf %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipoib_ib_handle_wc
r_static
r_void
id|ipoib_ib_handle_wc
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ib_wc
op_star
id|wc
)paren
(brace
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
r_int
id|wr_id
op_assign
id|wc-&gt;wr_id
suffix:semicolon
id|ipoib_dbg_data
c_func
(paren
id|priv
comma
l_string|&quot;called: id %d, op %d, status: %d&bslash;n&quot;
comma
id|wr_id
comma
id|wc-&gt;opcode
comma
id|wc-&gt;status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wr_id
op_amp
id|IPOIB_OP_RECV
)paren
(brace
id|wr_id
op_and_assign
op_complement
id|IPOIB_OP_RECV
suffix:semicolon
r_if
c_cond
(paren
id|wr_id
OL
id|IPOIB_RX_RING_SIZE
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|priv-&gt;rx_ring
(braket
id|wr_id
)braket
dot
id|skb
suffix:semicolon
id|priv-&gt;rx_ring
(braket
id|wr_id
)braket
dot
id|skb
op_assign
l_int|NULL
suffix:semicolon
id|dma_unmap_single
c_func
(paren
id|priv-&gt;ca-&gt;dma_device
comma
id|pci_unmap_addr
c_func
(paren
op_amp
id|priv-&gt;rx_ring
(braket
id|wr_id
)braket
comma
id|mapping
)paren
comma
id|IPOIB_BUF_SIZE
comma
id|DMA_FROM_DEVICE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wc-&gt;status
op_ne
id|IB_WC_SUCCESS
)paren
(brace
r_if
c_cond
(paren
id|wc-&gt;status
op_ne
id|IB_WC_WR_FLUSH_ERR
)paren
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;failed recv event &quot;
l_string|&quot;(status=%d, wrid=%d vend_err %x)&bslash;n&quot;
comma
id|wc-&gt;status
comma
id|wr_id
comma
id|wc-&gt;vendor_err
)paren
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ipoib_dbg_data
c_func
(paren
id|priv
comma
l_string|&quot;received %d bytes, SLID 0x%04x&bslash;n&quot;
comma
id|wc-&gt;byte_len
comma
id|wc-&gt;slid
)paren
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
id|wc-&gt;byte_len
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|IB_GRH_BYTES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wc-&gt;slid
op_ne
id|priv-&gt;local_lid
op_logical_or
id|wc-&gt;src_qp
op_ne
id|priv-&gt;qp-&gt;qp_num
)paren
(brace
id|skb-&gt;protocol
op_assign
(paren
(paren
r_struct
id|ipoib_header
op_star
)paren
id|skb-&gt;data
)paren
op_member_access_from_pointer
id|proto
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|IPOIB_ENCAP_LEN
)paren
suffix:semicolon
id|dev-&gt;last_rx
op_assign
id|jiffies
suffix:semicolon
op_increment
id|priv-&gt;stats.rx_packets
suffix:semicolon
id|priv-&gt;stats.rx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/* XXX get correct PACKET_ type here */
id|skb-&gt;pkt_type
op_assign
id|PACKET_HOST
suffix:semicolon
id|netif_rx_ni
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
id|ipoib_dbg_data
c_func
(paren
id|priv
comma
l_string|&quot;dropping loopback packet&bslash;n&quot;
)paren
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
multiline_comment|/* repost receive */
r_if
c_cond
(paren
id|ipoib_ib_post_receive
c_func
(paren
id|dev
comma
id|wr_id
)paren
)paren
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;ipoib_ib_post_receive failed &quot;
l_string|&quot;for buf %d&bslash;n&quot;
comma
id|wr_id
)paren
suffix:semicolon
)brace
r_else
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;completion event with wrid %d&bslash;n&quot;
comma
id|wr_id
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|ipoib_buf
op_star
id|tx_req
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|wr_id
op_ge
id|IPOIB_TX_RING_SIZE
)paren
(brace
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;completion event with wrid %d (&gt; %d)&bslash;n&quot;
comma
id|wr_id
comma
id|IPOIB_TX_RING_SIZE
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ipoib_dbg_data
c_func
(paren
id|priv
comma
l_string|&quot;send complete, wrid %d&bslash;n&quot;
comma
id|wr_id
)paren
suffix:semicolon
id|tx_req
op_assign
op_amp
id|priv-&gt;tx_ring
(braket
id|wr_id
)braket
suffix:semicolon
id|dma_unmap_single
c_func
(paren
id|priv-&gt;ca-&gt;dma_device
comma
id|pci_unmap_addr
c_func
(paren
id|tx_req
comma
id|mapping
)paren
comma
id|tx_req-&gt;skb-&gt;len
comma
id|DMA_TO_DEVICE
)paren
suffix:semicolon
op_increment
id|priv-&gt;stats.tx_packets
suffix:semicolon
id|priv-&gt;stats.tx_bytes
op_add_assign
id|tx_req-&gt;skb-&gt;len
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|tx_req-&gt;skb
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;tx_lock
comma
id|flags
)paren
suffix:semicolon
op_increment
id|priv-&gt;tx_tail
suffix:semicolon
r_if
c_cond
(paren
id|netif_queue_stopped
c_func
(paren
id|dev
)paren
op_logical_and
id|priv-&gt;tx_head
op_minus
id|priv-&gt;tx_tail
op_le
id|IPOIB_TX_RING_SIZE
op_div
l_int|2
)paren
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;tx_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wc-&gt;status
op_ne
id|IB_WC_SUCCESS
op_logical_and
id|wc-&gt;status
op_ne
id|IB_WC_WR_FLUSH_ERR
)paren
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;failed send event &quot;
l_string|&quot;(status=%d, wrid=%d vend_err %x)&bslash;n&quot;
comma
id|wc-&gt;status
comma
id|wr_id
comma
id|wc-&gt;vendor_err
)paren
suffix:semicolon
)brace
)brace
DECL|function|ipoib_ib_completion
r_void
id|ipoib_ib_completion
c_func
(paren
r_struct
id|ib_cq
op_star
id|cq
comma
r_void
op_star
id|dev_ptr
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|dev_ptr
suffix:semicolon
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|n
comma
id|i
suffix:semicolon
id|ib_req_notify_cq
c_func
(paren
id|cq
comma
id|IB_CQ_NEXT_COMP
)paren
suffix:semicolon
r_do
(brace
id|n
op_assign
id|ib_poll_cq
c_func
(paren
id|cq
comma
id|IPOIB_NUM_WC
comma
id|priv-&gt;ibwc
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
id|n
suffix:semicolon
op_increment
id|i
)paren
id|ipoib_ib_handle_wc
c_func
(paren
id|dev
comma
id|priv-&gt;ibwc
op_plus
id|i
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|n
op_eq
id|IPOIB_NUM_WC
)paren
suffix:semicolon
)brace
DECL|function|post_send
r_static
r_inline
r_int
id|post_send
c_func
(paren
r_struct
id|ipoib_dev_priv
op_star
id|priv
comma
r_int
r_int
id|wr_id
comma
r_struct
id|ib_ah
op_star
id|address
comma
id|u32
id|qpn
comma
id|dma_addr_t
id|addr
comma
r_int
id|len
)paren
(brace
r_struct
id|ib_send_wr
op_star
id|bad_wr
suffix:semicolon
id|priv-&gt;tx_sge.addr
op_assign
id|addr
suffix:semicolon
id|priv-&gt;tx_sge.length
op_assign
id|len
suffix:semicolon
id|priv-&gt;tx_wr.wr_id
op_assign
id|wr_id
suffix:semicolon
id|priv-&gt;tx_wr.wr.ud.remote_qpn
op_assign
id|qpn
suffix:semicolon
id|priv-&gt;tx_wr.wr.ud.ah
op_assign
id|address
suffix:semicolon
r_return
id|ib_post_send
c_func
(paren
id|priv-&gt;qp
comma
op_amp
id|priv-&gt;tx_wr
comma
op_amp
id|bad_wr
)paren
suffix:semicolon
)brace
DECL|function|ipoib_send
r_void
id|ipoib_send
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|ipoib_ah
op_star
id|address
comma
id|u32
id|qpn
)paren
(brace
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|ipoib_buf
op_star
id|tx_req
suffix:semicolon
id|dma_addr_t
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;len
OG
id|dev-&gt;mtu
op_plus
id|INFINIBAND_ALEN
)paren
(brace
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;packet len %d (&gt; %d) too long to send, dropping&bslash;n&quot;
comma
id|skb-&gt;len
comma
id|dev-&gt;mtu
op_plus
id|INFINIBAND_ALEN
)paren
suffix:semicolon
op_increment
id|priv-&gt;stats.tx_dropped
suffix:semicolon
op_increment
id|priv-&gt;stats.tx_errors
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ipoib_dbg_data
c_func
(paren
id|priv
comma
l_string|&quot;sending packet, length=%d address=%p qpn=0x%06x&bslash;n&quot;
comma
id|skb-&gt;len
comma
id|address
comma
id|qpn
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We put the skb into the tx_ring _before_ we call post_send()&n;&t; * because it&squot;s entirely possible that the completion handler will&n;&t; * run before we execute anything after the post_send().  That&n;&t; * means we have to make sure everything is properly recorded and&n;&t; * our state is consistent before we call post_send().&n;&t; */
id|tx_req
op_assign
op_amp
id|priv-&gt;tx_ring
(braket
id|priv-&gt;tx_head
op_amp
(paren
id|IPOIB_TX_RING_SIZE
op_minus
l_int|1
)paren
)braket
suffix:semicolon
id|tx_req-&gt;skb
op_assign
id|skb
suffix:semicolon
id|addr
op_assign
id|dma_map_single
c_func
(paren
id|priv-&gt;ca-&gt;dma_device
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
id|DMA_TO_DEVICE
)paren
suffix:semicolon
id|pci_unmap_addr_set
c_func
(paren
id|tx_req
comma
id|mapping
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|post_send
c_func
(paren
id|priv
comma
id|priv-&gt;tx_head
op_amp
(paren
id|IPOIB_TX_RING_SIZE
op_minus
l_int|1
)paren
comma
id|address-&gt;ah
comma
id|qpn
comma
id|addr
comma
id|skb-&gt;len
)paren
)paren
)paren
(brace
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;post_send failed&bslash;n&quot;
)paren
suffix:semicolon
op_increment
id|priv-&gt;stats.tx_errors
suffix:semicolon
id|dma_unmap_single
c_func
(paren
id|priv-&gt;ca-&gt;dma_device
comma
id|addr
comma
id|skb-&gt;len
comma
id|DMA_TO_DEVICE
)paren
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|address-&gt;last_send
op_assign
id|priv-&gt;tx_head
suffix:semicolon
op_increment
id|priv-&gt;tx_head
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;tx_head
op_minus
id|priv-&gt;tx_tail
op_eq
id|IPOIB_TX_RING_SIZE
)paren
(brace
id|ipoib_dbg
c_func
(paren
id|priv
comma
l_string|&quot;TX ring full, stopping kernel net queue&bslash;n&quot;
)paren
suffix:semicolon
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|__ipoib_reap_ah
r_static
r_void
id|__ipoib_reap_ah
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|ipoib_ah
op_star
id|ah
comma
op_star
id|tah
suffix:semicolon
id|LIST_HEAD
c_func
(paren
id|remove_list
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|priv-&gt;lock
)paren
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|ah
comma
id|tah
comma
op_amp
id|priv-&gt;dead_ahs
comma
id|list
)paren
r_if
c_cond
(paren
id|ah-&gt;last_send
op_le
id|priv-&gt;tx_tail
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|ah-&gt;list
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|ah-&gt;list
comma
op_amp
id|remove_list
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|priv-&gt;lock
)paren
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|ah
comma
id|tah
comma
op_amp
id|remove_list
comma
id|list
)paren
(brace
id|ipoib_dbg
c_func
(paren
id|priv
comma
l_string|&quot;Reaping ah %p&bslash;n&quot;
comma
id|ah-&gt;ah
)paren
suffix:semicolon
id|ib_destroy_ah
c_func
(paren
id|ah-&gt;ah
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ah
)paren
suffix:semicolon
)brace
)brace
DECL|function|ipoib_reap_ah
r_void
id|ipoib_reap_ah
c_func
(paren
r_void
op_star
id|dev_ptr
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|dev_ptr
suffix:semicolon
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|__ipoib_reap_ah
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|IPOIB_STOP_REAPER
comma
op_amp
id|priv-&gt;flags
)paren
)paren
id|queue_delayed_work
c_func
(paren
id|ipoib_workqueue
comma
op_amp
id|priv-&gt;ah_reap_task
comma
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|ipoib_ib_dev_open
r_int
id|ipoib_ib_dev_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|ipoib_qp_create
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;ipoib_qp_create returned %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|ret
op_assign
id|ipoib_ib_post_receives
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;ipoib_ib_post_receives returned %d&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
id|IPOIB_STOP_REAPER
comma
op_amp
id|priv-&gt;flags
)paren
suffix:semicolon
id|queue_delayed_work
c_func
(paren
id|ipoib_workqueue
comma
op_amp
id|priv-&gt;ah_reap_task
comma
id|HZ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipoib_ib_dev_up
r_int
id|ipoib_ib_dev_up
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|IPOIB_FLAG_OPER_UP
comma
op_amp
id|priv-&gt;flags
)paren
suffix:semicolon
r_return
id|ipoib_mcast_start_thread
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|ipoib_ib_dev_down
r_int
id|ipoib_ib_dev_down
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ipoib_dbg
c_func
(paren
id|priv
comma
l_string|&quot;downing ib_dev&bslash;n&quot;
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|IPOIB_FLAG_OPER_UP
comma
op_amp
id|priv-&gt;flags
)paren
suffix:semicolon
id|netif_carrier_off
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Shutdown the P_Key thread if still active */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|IPOIB_PKEY_ASSIGNED
comma
op_amp
id|priv-&gt;flags
)paren
)paren
(brace
id|down
c_func
(paren
op_amp
id|pkey_sem
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|IPOIB_PKEY_STOP
comma
op_amp
id|priv-&gt;flags
)paren
suffix:semicolon
id|cancel_delayed_work
c_func
(paren
op_amp
id|priv-&gt;pkey_task
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pkey_sem
)paren
suffix:semicolon
id|flush_workqueue
c_func
(paren
id|ipoib_workqueue
)paren
suffix:semicolon
)brace
id|ipoib_mcast_stop_thread
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Flush the multicast groups first so we stop any multicast joins. The&n;&t; * completion thread may have already died and we may deadlock waiting&n;&t; * for the completion thread to finish some multicast joins.&n;&t; */
id|ipoib_mcast_dev_flush
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Delete broadcast and local addresses since they will be recreated */
id|ipoib_mcast_dev_down
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ipoib_flush_paths
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|recvs_pending
r_static
r_int
id|recvs_pending
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|pending
op_assign
l_int|0
suffix:semicolon
r_int
id|i
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
id|IPOIB_RX_RING_SIZE
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|priv-&gt;rx_ring
(braket
id|i
)braket
dot
id|skb
)paren
op_increment
id|pending
suffix:semicolon
r_return
id|pending
suffix:semicolon
)brace
DECL|function|ipoib_ib_dev_stop
r_int
id|ipoib_ib_dev_stop
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|ib_qp_attr
id|qp_attr
suffix:semicolon
r_int
id|attr_mask
suffix:semicolon
r_int
r_int
id|begin
suffix:semicolon
r_struct
id|ipoib_buf
op_star
id|tx_req
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Kill the existing QP and allocate a new one */
id|qp_attr.qp_state
op_assign
id|IB_QPS_ERR
suffix:semicolon
id|attr_mask
op_assign
id|IB_QP_STATE
suffix:semicolon
r_if
c_cond
(paren
id|ib_modify_qp
c_func
(paren
id|priv-&gt;qp
comma
op_amp
id|qp_attr
comma
id|attr_mask
)paren
)paren
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;Failed to modify QP to ERROR state&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Wait for all sends and receives to complete */
id|begin
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
id|priv-&gt;tx_head
op_ne
id|priv-&gt;tx_tail
op_logical_or
id|recvs_pending
c_func
(paren
id|dev
)paren
)paren
(brace
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|begin
op_plus
l_int|5
op_star
id|HZ
)paren
)paren
(brace
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;timing out; %d sends %d receives not completed&bslash;n&quot;
comma
id|priv-&gt;tx_head
op_minus
id|priv-&gt;tx_tail
comma
id|recvs_pending
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * assume the HW is wedged and just free up&n;&t;&t;&t; * all our pending work requests.&n;&t;&t;&t; */
r_while
c_loop
(paren
id|priv-&gt;tx_tail
OL
id|priv-&gt;tx_head
)paren
(brace
id|tx_req
op_assign
op_amp
id|priv-&gt;tx_ring
(braket
id|priv-&gt;tx_tail
op_amp
(paren
id|IPOIB_TX_RING_SIZE
op_minus
l_int|1
)paren
)braket
suffix:semicolon
id|dma_unmap_single
c_func
(paren
id|priv-&gt;ca-&gt;dma_device
comma
id|pci_unmap_addr
c_func
(paren
id|tx_req
comma
id|mapping
)paren
comma
id|tx_req-&gt;skb-&gt;len
comma
id|DMA_TO_DEVICE
)paren
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|tx_req-&gt;skb
)paren
suffix:semicolon
op_increment
id|priv-&gt;tx_tail
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IPOIB_RX_RING_SIZE
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|priv-&gt;rx_ring
(braket
id|i
)braket
dot
id|skb
)paren
(brace
id|dma_unmap_single
c_func
(paren
id|priv-&gt;ca-&gt;dma_device
comma
id|pci_unmap_addr
c_func
(paren
op_amp
id|priv-&gt;rx_ring
(braket
id|i
)braket
comma
id|mapping
)paren
comma
id|IPOIB_BUF_SIZE
comma
id|DMA_FROM_DEVICE
)paren
suffix:semicolon
id|dev_kfree_skb_any
c_func
(paren
id|priv-&gt;rx_ring
(braket
id|i
)braket
dot
id|skb
)paren
suffix:semicolon
id|priv-&gt;rx_ring
(braket
id|i
)braket
dot
id|skb
op_assign
l_int|NULL
suffix:semicolon
)brace
r_goto
id|timeout
suffix:semicolon
)brace
id|yield
c_func
(paren
)paren
suffix:semicolon
)brace
id|ipoib_dbg
c_func
(paren
id|priv
comma
l_string|&quot;All sends and receives done.&bslash;n&quot;
)paren
suffix:semicolon
id|timeout
suffix:colon
id|qp_attr.qp_state
op_assign
id|IB_QPS_RESET
suffix:semicolon
id|attr_mask
op_assign
id|IB_QP_STATE
suffix:semicolon
r_if
c_cond
(paren
id|ib_modify_qp
c_func
(paren
id|priv-&gt;qp
comma
op_amp
id|qp_attr
comma
id|attr_mask
)paren
)paren
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;Failed to modify QP to RESET state&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Wait for all AHs to be reaped */
id|set_bit
c_func
(paren
id|IPOIB_STOP_REAPER
comma
op_amp
id|priv-&gt;flags
)paren
suffix:semicolon
id|cancel_delayed_work
c_func
(paren
op_amp
id|priv-&gt;ah_reap_task
)paren
suffix:semicolon
id|flush_workqueue
c_func
(paren
id|ipoib_workqueue
)paren
suffix:semicolon
id|begin
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|priv-&gt;dead_ahs
)paren
)paren
(brace
id|__ipoib_reap_ah
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|begin
op_plus
id|HZ
)paren
)paren
(brace
id|ipoib_warn
c_func
(paren
id|priv
comma
l_string|&quot;timing out; will leak address handles&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|yield
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipoib_ib_dev_init
r_int
id|ipoib_ib_dev_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ib_device
op_star
id|ca
comma
r_int
id|port
)paren
(brace
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|priv-&gt;ca
op_assign
id|ca
suffix:semicolon
id|priv-&gt;port
op_assign
id|port
suffix:semicolon
id|priv-&gt;qp
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ipoib_transport_dev_init
c_func
(paren
id|dev
comma
id|ca
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: ipoib_transport_dev_init failed&bslash;n&quot;
comma
id|ca-&gt;name
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
id|dev-&gt;flags
op_amp
id|IFF_UP
)paren
(brace
r_if
c_cond
(paren
id|ipoib_ib_dev_open
c_func
(paren
id|dev
)paren
)paren
(brace
id|ipoib_transport_dev_cleanup
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ipoib_ib_dev_flush
r_void
id|ipoib_ib_dev_flush
c_func
(paren
r_void
op_star
id|_dev
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
(paren
r_struct
id|net_device
op_star
)paren
id|_dev
suffix:semicolon
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
comma
op_star
id|cpriv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|IPOIB_FLAG_ADMIN_UP
comma
op_amp
id|priv-&gt;flags
)paren
)paren
r_return
suffix:semicolon
id|ipoib_dbg
c_func
(paren
id|priv
comma
l_string|&quot;flushing&bslash;n&quot;
)paren
suffix:semicolon
id|ipoib_ib_dev_down
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The device could have been brought down between the start and when&n;&t; * we get here, don&squot;t bring it back up if it&squot;s not configured up&n;&t; */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|IPOIB_FLAG_ADMIN_UP
comma
op_amp
id|priv-&gt;flags
)paren
)paren
id|ipoib_ib_dev_up
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Flush any child interfaces too */
id|list_for_each_entry
c_func
(paren
id|cpriv
comma
op_amp
id|priv-&gt;child_intfs
comma
id|list
)paren
id|ipoib_ib_dev_flush
c_func
(paren
op_amp
id|cpriv-&gt;dev
)paren
suffix:semicolon
)brace
DECL|function|ipoib_ib_dev_cleanup
r_void
id|ipoib_ib_dev_cleanup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ipoib_dbg
c_func
(paren
id|priv
comma
l_string|&quot;cleaning up ib_dev&bslash;n&quot;
)paren
suffix:semicolon
id|ipoib_mcast_stop_thread
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Delete the broadcast address and the local address */
id|ipoib_mcast_dev_down
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ipoib_transport_dev_cleanup
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Delayed P_Key Assigment Interim Support&n; *&n; * The following is initial implementation of delayed P_Key assigment&n; * mechanism. It is using the same approach implemented for the multicast&n; * group join. The single goal of this implementation is to quickly address&n; * Bug #2507. This implementation will probably be removed when the P_Key&n; * change async notification is available.&n; */
r_int
id|ipoib_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|function|ipoib_pkey_dev_check_presence
r_static
r_void
id|ipoib_pkey_dev_check_presence
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|u16
id|pkey_index
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ib_find_cached_pkey
c_func
(paren
id|priv-&gt;ca
comma
id|priv-&gt;port
comma
id|priv-&gt;pkey
comma
op_amp
id|pkey_index
)paren
)paren
id|clear_bit
c_func
(paren
id|IPOIB_PKEY_ASSIGNED
comma
op_amp
id|priv-&gt;flags
)paren
suffix:semicolon
r_else
id|set_bit
c_func
(paren
id|IPOIB_PKEY_ASSIGNED
comma
op_amp
id|priv-&gt;flags
)paren
suffix:semicolon
)brace
DECL|function|ipoib_pkey_poll
r_void
id|ipoib_pkey_poll
c_func
(paren
r_void
op_star
id|dev_ptr
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|dev_ptr
suffix:semicolon
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ipoib_pkey_dev_check_presence
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|IPOIB_PKEY_ASSIGNED
comma
op_amp
id|priv-&gt;flags
)paren
)paren
id|ipoib_open
c_func
(paren
id|dev
)paren
suffix:semicolon
r_else
(brace
id|down
c_func
(paren
op_amp
id|pkey_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|IPOIB_PKEY_STOP
comma
op_amp
id|priv-&gt;flags
)paren
)paren
id|queue_delayed_work
c_func
(paren
id|ipoib_workqueue
comma
op_amp
id|priv-&gt;pkey_task
comma
id|HZ
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pkey_sem
)paren
suffix:semicolon
)brace
)brace
DECL|function|ipoib_pkey_dev_delay_open
r_int
id|ipoib_pkey_dev_delay_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|ipoib_dev_priv
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Look for the interface pkey value in the IB Port P_Key table and */
multiline_comment|/* set the interface pkey assigment flag                            */
id|ipoib_pkey_dev_check_presence
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* P_Key value not assigned yet - start polling */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|IPOIB_PKEY_ASSIGNED
comma
op_amp
id|priv-&gt;flags
)paren
)paren
(brace
id|down
c_func
(paren
op_amp
id|pkey_sem
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|IPOIB_PKEY_STOP
comma
op_amp
id|priv-&gt;flags
)paren
suffix:semicolon
id|queue_delayed_work
c_func
(paren
id|ipoib_workqueue
comma
op_amp
id|priv-&gt;pkey_task
comma
id|HZ
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pkey_sem
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
