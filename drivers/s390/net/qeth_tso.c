multiline_comment|/*&n; * linux/drivers/s390/net/qeth_tso.c ($Revision: 1.6 $)&n; *&n; * Header file for qeth TCP Segmentation Offload support.&n; *&n; * Copyright 2004 IBM Corporation&n; *&n; *    Author(s): Frank Pavlic &lt;pavlic@de.ibm.com&gt;&n; *&n; *    $Revision: 1.6 $&t; $Date: 2005/03/24 09:04:18 $&n; *&n; */
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/ipv6.h&gt;
macro_line|#include &lt;net/ip6_checksum.h&gt;
macro_line|#include &quot;qeth.h&quot;
macro_line|#include &quot;qeth_mpc.h&quot;
macro_line|#include &quot;qeth_tso.h&quot;
multiline_comment|/**&n; * skb already partially prepared&n; * classic qdio header in skb-&gt;data&n; * */
r_static
r_inline
r_struct
id|qeth_hdr_tso
op_star
DECL|function|qeth_tso_prepare_skb
id|qeth_tso_prepare_skb
c_func
(paren
r_struct
id|qeth_card
op_star
id|card
comma
r_struct
id|sk_buff
op_star
op_star
id|skb
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|QETH_DBF_TEXT
c_func
(paren
id|trace
comma
l_int|5
comma
l_string|&quot;tsoprsk&quot;
)paren
suffix:semicolon
id|rc
op_assign
id|qeth_realloc_headroom
c_func
(paren
id|card
comma
id|skb
comma
r_sizeof
(paren
r_struct
id|qeth_hdr_ext_tso
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|qeth_push_skb
c_func
(paren
id|card
comma
id|skb
comma
r_sizeof
(paren
r_struct
id|qeth_hdr_ext_tso
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * fill header for a TSO packet&n; */
r_static
r_inline
r_void
DECL|function|qeth_tso_fill_header
id|qeth_tso_fill_header
c_func
(paren
r_struct
id|qeth_card
op_star
id|card
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|qeth_hdr_tso
op_star
id|hdr
suffix:semicolon
r_struct
id|tcphdr
op_star
id|tcph
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
id|QETH_DBF_TEXT
c_func
(paren
id|trace
comma
l_int|5
comma
l_string|&quot;tsofhdr&quot;
)paren
suffix:semicolon
id|hdr
op_assign
(paren
r_struct
id|qeth_hdr_tso
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|tcph
op_assign
id|skb-&gt;h.th
suffix:semicolon
multiline_comment|/*fix header to TSO values ...*/
id|hdr-&gt;hdr.hdr.l3.id
op_assign
id|QETH_HEADER_TYPE_TSO
suffix:semicolon
multiline_comment|/*set values which are fix for the first approach ...*/
id|hdr-&gt;ext.hdr_tot_len
op_assign
(paren
id|__u16
)paren
r_sizeof
(paren
r_struct
id|qeth_hdr_ext_tso
)paren
suffix:semicolon
id|hdr-&gt;ext.imb_hdr_no
op_assign
l_int|1
suffix:semicolon
id|hdr-&gt;ext.hdr_type
op_assign
l_int|1
suffix:semicolon
id|hdr-&gt;ext.hdr_version
op_assign
l_int|1
suffix:semicolon
id|hdr-&gt;ext.hdr_len
op_assign
l_int|28
suffix:semicolon
multiline_comment|/*insert non-fix values */
id|hdr-&gt;ext.mss
op_assign
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|tso_size
suffix:semicolon
id|hdr-&gt;ext.dg_hdr_len
op_assign
(paren
id|__u16
)paren
(paren
id|iph-&gt;ihl
op_star
l_int|4
op_plus
id|tcph-&gt;doff
op_star
l_int|4
)paren
suffix:semicolon
id|hdr-&gt;ext.payload_len
op_assign
(paren
id|__u16
)paren
(paren
id|skb-&gt;len
op_minus
id|hdr-&gt;ext.dg_hdr_len
op_minus
r_sizeof
(paren
r_struct
id|qeth_hdr_tso
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * change some header values as requested by hardware&n; */
r_static
r_inline
r_void
DECL|function|qeth_tso_set_tcpip_header
id|qeth_tso_set_tcpip_header
c_func
(paren
r_struct
id|qeth_card
op_star
id|card
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_struct
id|ipv6hdr
op_star
id|ip6h
suffix:semicolon
r_struct
id|tcphdr
op_star
id|tcph
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|ip6h
op_assign
id|skb-&gt;nh.ipv6h
suffix:semicolon
id|tcph
op_assign
id|skb-&gt;h.th
suffix:semicolon
id|tcph-&gt;check
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;protocol
op_eq
id|ETH_P_IPV6
)paren
(brace
id|ip6h-&gt;payload_len
op_assign
l_int|0
suffix:semicolon
id|tcph-&gt;check
op_assign
op_complement
id|csum_ipv6_magic
c_func
(paren
op_amp
id|ip6h-&gt;saddr
comma
op_amp
id|ip6h-&gt;daddr
comma
l_int|0
comma
id|IPPROTO_TCP
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*OSA want us to set these values ...*/
id|tcph-&gt;check
op_assign
op_complement
id|csum_tcpudp_magic
c_func
(paren
id|iph-&gt;saddr
comma
id|iph-&gt;daddr
comma
l_int|0
comma
id|IPPROTO_TCP
comma
l_int|0
)paren
suffix:semicolon
id|iph-&gt;tot_len
op_assign
l_int|0
suffix:semicolon
id|iph-&gt;check
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_struct
id|qeth_hdr_tso
op_star
DECL|function|qeth_tso_prepare_packet
id|qeth_tso_prepare_packet
c_func
(paren
r_struct
id|qeth_card
op_star
id|card
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ipv
comma
r_int
id|cast_type
)paren
(brace
r_struct
id|qeth_hdr_tso
op_star
id|hdr
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|QETH_DBF_TEXT
c_func
(paren
id|trace
comma
l_int|5
comma
l_string|&quot;tsoprep&quot;
)paren
suffix:semicolon
multiline_comment|/*get headroom for tso qdio header */
id|hdr
op_assign
(paren
r_struct
id|qeth_hdr_tso
op_star
)paren
id|qeth_tso_prepare_skb
c_func
(paren
id|card
comma
op_amp
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdr
op_eq
l_int|NULL
)paren
(brace
id|QETH_DBF_TEXT_
c_func
(paren
id|trace
comma
l_int|4
comma
l_string|&quot;2err%d&quot;
comma
id|rc
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|hdr
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|qeth_hdr_tso
)paren
)paren
suffix:semicolon
multiline_comment|/*fill first 32 bytes of  qdio header as used&n;&t; *FIXME: TSO has two struct members&n;&t; * with different names but same size&n;&t; * */
id|qeth_fill_header
c_func
(paren
id|card
comma
op_amp
id|hdr-&gt;hdr
comma
id|skb
comma
id|ipv
comma
id|cast_type
)paren
suffix:semicolon
id|qeth_tso_fill_header
c_func
(paren
id|card
comma
id|skb
)paren
suffix:semicolon
id|qeth_tso_set_tcpip_header
c_func
(paren
id|card
comma
id|skb
)paren
suffix:semicolon
r_return
id|hdr
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|qeth_tso_get_queue_buffer
id|qeth_tso_get_queue_buffer
c_func
(paren
r_struct
id|qeth_qdio_out_q
op_star
id|queue
)paren
(brace
r_struct
id|qeth_qdio_out_buffer
op_star
id|buffer
suffix:semicolon
r_int
id|flush_cnt
op_assign
l_int|0
suffix:semicolon
id|QETH_DBF_TEXT
c_func
(paren
id|trace
comma
l_int|5
comma
l_string|&quot;tsobuf&quot;
)paren
suffix:semicolon
multiline_comment|/* force to non-packing*/
r_if
c_cond
(paren
id|queue-&gt;do_pack
)paren
id|queue-&gt;do_pack
op_assign
l_int|0
suffix:semicolon
id|buffer
op_assign
op_amp
id|queue-&gt;bufs
(braket
id|queue-&gt;next_buf_to_fill
)braket
suffix:semicolon
multiline_comment|/* get a new buffer if current is already in use*/
r_if
c_cond
(paren
(paren
id|atomic_read
c_func
(paren
op_amp
id|buffer-&gt;state
)paren
op_eq
id|QETH_QDIO_BUF_EMPTY
)paren
op_logical_and
(paren
id|buffer-&gt;next_element_to_fill
OG
l_int|0
)paren
)paren
(brace
id|atomic_set
c_func
(paren
op_amp
id|buffer-&gt;state
comma
id|QETH_QDIO_BUF_PRIMED
)paren
suffix:semicolon
id|queue-&gt;next_buf_to_fill
op_assign
(paren
id|queue-&gt;next_buf_to_fill
op_plus
l_int|1
)paren
op_mod
id|QDIO_MAX_BUFFERS_PER_Q
suffix:semicolon
id|flush_cnt
op_increment
suffix:semicolon
)brace
r_return
id|flush_cnt
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__qeth_tso_fill_buffer_frag
id|__qeth_tso_fill_buffer_frag
c_func
(paren
r_struct
id|qeth_qdio_out_buffer
op_star
id|buf
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|skb_frag_struct
op_star
id|frag
suffix:semicolon
r_struct
id|qdio_buffer
op_star
id|buffer
suffix:semicolon
r_int
id|fragno
comma
id|cnt
comma
id|element
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
id|QETH_DBF_TEXT
c_func
(paren
id|trace
comma
l_int|6
comma
l_string|&quot;tsfilfrg&quot;
)paren
suffix:semicolon
multiline_comment|/*initialize variables ...*/
id|fragno
op_assign
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|nr_frags
suffix:semicolon
id|buffer
op_assign
id|buf-&gt;buffer
suffix:semicolon
id|element
op_assign
id|buf-&gt;next_element_to_fill
suffix:semicolon
multiline_comment|/*fill buffer elements .....*/
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|fragno
suffix:semicolon
id|cnt
op_increment
)paren
(brace
id|frag
op_assign
op_amp
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frags
(braket
id|cnt
)braket
suffix:semicolon
id|addr
op_assign
(paren
id|page_to_pfn
c_func
(paren
id|frag-&gt;page
)paren
op_lshift
id|PAGE_SHIFT
)paren
op_plus
id|frag-&gt;page_offset
suffix:semicolon
id|buffer-&gt;element
(braket
id|element
)braket
dot
id|addr
op_assign
(paren
r_char
op_star
)paren
id|addr
suffix:semicolon
id|buffer-&gt;element
(braket
id|element
)braket
dot
id|length
op_assign
id|frag-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|cnt
OL
(paren
id|fragno
op_minus
l_int|1
)paren
)paren
id|buffer-&gt;element
(braket
id|element
)braket
dot
id|flags
op_assign
id|SBAL_FLAGS_MIDDLE_FRAG
suffix:semicolon
r_else
id|buffer-&gt;element
(braket
id|element
)braket
dot
id|flags
op_assign
id|SBAL_FLAGS_LAST_FRAG
suffix:semicolon
id|element
op_increment
suffix:semicolon
)brace
id|buf-&gt;next_element_to_fill
op_assign
id|element
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|qeth_tso_fill_buffer
id|qeth_tso_fill_buffer
c_func
(paren
r_struct
id|qeth_qdio_out_buffer
op_star
id|buf
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|length
comma
id|length_here
comma
id|element
suffix:semicolon
r_int
id|hdr_len
suffix:semicolon
r_struct
id|qdio_buffer
op_star
id|buffer
suffix:semicolon
r_struct
id|qeth_hdr_tso
op_star
id|hdr
suffix:semicolon
r_char
op_star
id|data
suffix:semicolon
id|QETH_DBF_TEXT
c_func
(paren
id|trace
comma
l_int|3
comma
l_string|&quot;tsfilbuf&quot;
)paren
suffix:semicolon
multiline_comment|/*increment user count and queue skb ...*/
id|atomic_inc
c_func
(paren
op_amp
id|skb-&gt;users
)paren
suffix:semicolon
id|skb_queue_tail
c_func
(paren
op_amp
id|buf-&gt;skb_list
comma
id|skb
)paren
suffix:semicolon
multiline_comment|/*initialize all variables...*/
id|buffer
op_assign
id|buf-&gt;buffer
suffix:semicolon
id|hdr
op_assign
(paren
r_struct
id|qeth_hdr_tso
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|hdr_len
op_assign
r_sizeof
(paren
r_struct
id|qeth_hdr_tso
)paren
op_plus
id|hdr-&gt;ext.dg_hdr_len
suffix:semicolon
id|data
op_assign
id|skb-&gt;data
op_plus
id|hdr_len
suffix:semicolon
id|length
op_assign
id|skb-&gt;len
op_minus
id|hdr_len
suffix:semicolon
id|element
op_assign
id|buf-&gt;next_element_to_fill
suffix:semicolon
multiline_comment|/*fill first buffer entry only with header information */
id|buffer-&gt;element
(braket
id|element
)braket
dot
id|addr
op_assign
id|skb-&gt;data
suffix:semicolon
id|buffer-&gt;element
(braket
id|element
)braket
dot
id|length
op_assign
id|hdr_len
suffix:semicolon
id|buffer-&gt;element
(braket
id|element
)braket
dot
id|flags
op_assign
id|SBAL_FLAGS_FIRST_FRAG
suffix:semicolon
id|buf-&gt;next_element_to_fill
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|nr_frags
OG
l_int|0
)paren
(brace
id|__qeth_tso_fill_buffer_frag
c_func
(paren
id|buf
comma
id|skb
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*start filling buffer entries ...*/
id|element
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|length
OG
l_int|0
)paren
(brace
multiline_comment|/* length_here is the remaining amount of data in this page */
id|length_here
op_assign
id|PAGE_SIZE
op_minus
(paren
(paren
r_int
r_int
)paren
id|data
op_mod
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OL
id|length_here
)paren
id|length_here
op_assign
id|length
suffix:semicolon
id|buffer-&gt;element
(braket
id|element
)braket
dot
id|addr
op_assign
id|data
suffix:semicolon
id|buffer-&gt;element
(braket
id|element
)braket
dot
id|length
op_assign
id|length_here
suffix:semicolon
id|length
op_sub_assign
id|length_here
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|length
)paren
id|buffer-&gt;element
(braket
id|element
)braket
dot
id|flags
op_assign
id|SBAL_FLAGS_LAST_FRAG
suffix:semicolon
r_else
id|buffer-&gt;element
(braket
id|element
)braket
dot
id|flags
op_assign
id|SBAL_FLAGS_MIDDLE_FRAG
suffix:semicolon
id|data
op_add_assign
id|length_here
suffix:semicolon
id|element
op_increment
suffix:semicolon
)brace
multiline_comment|/*set the buffer to primed  ...*/
id|buf-&gt;next_element_to_fill
op_assign
id|element
suffix:semicolon
id|out
suffix:colon
id|atomic_set
c_func
(paren
op_amp
id|buf-&gt;state
comma
id|QETH_QDIO_BUF_PRIMED
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|qeth_tso_send_packet
id|qeth_tso_send_packet
c_func
(paren
r_struct
id|qeth_card
op_star
id|card
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|qeth_qdio_out_q
op_star
id|queue
comma
r_int
id|ipv
comma
r_int
id|cast_type
)paren
(brace
r_int
id|flush_cnt
op_assign
l_int|0
suffix:semicolon
r_struct
id|qeth_hdr_tso
op_star
id|hdr
suffix:semicolon
r_struct
id|qeth_qdio_out_buffer
op_star
id|buffer
suffix:semicolon
r_int
id|start_index
suffix:semicolon
id|QETH_DBF_TEXT
c_func
(paren
id|trace
comma
l_int|3
comma
l_string|&quot;tsosend&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|hdr
op_assign
id|qeth_tso_prepare_packet
c_func
(paren
id|card
comma
id|skb
comma
id|ipv
comma
id|cast_type
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/*check if skb fits in one SBAL ...*/
r_if
c_cond
(paren
op_logical_neg
(paren
id|qeth_get_elements_no
c_func
(paren
id|card
comma
(paren
r_void
op_star
)paren
id|hdr
comma
id|skb
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*lock queue, force switching to non-packing and send it ...*/
r_while
c_loop
(paren
id|atomic_compare_and_swap
c_func
(paren
id|QETH_OUT_Q_UNLOCKED
comma
id|QETH_OUT_Q_LOCKED
comma
op_amp
id|queue-&gt;state
)paren
)paren
suffix:semicolon
id|start_index
op_assign
id|queue-&gt;next_buf_to_fill
suffix:semicolon
id|buffer
op_assign
op_amp
id|queue-&gt;bufs
(braket
id|queue-&gt;next_buf_to_fill
)braket
suffix:semicolon
multiline_comment|/*check if card is too busy ...*/
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|buffer-&gt;state
)paren
op_ne
id|QETH_QDIO_BUF_EMPTY
)paren
(brace
id|card-&gt;stats.tx_dropped
op_increment
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*let&squot;s force to non-packing and get a new SBAL*/
id|flush_cnt
op_add_assign
id|qeth_tso_get_queue_buffer
c_func
(paren
id|queue
)paren
suffix:semicolon
id|buffer
op_assign
op_amp
id|queue-&gt;bufs
(braket
id|queue-&gt;next_buf_to_fill
)braket
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|buffer-&gt;state
)paren
op_ne
id|QETH_QDIO_BUF_EMPTY
)paren
(brace
id|card-&gt;stats.tx_dropped
op_increment
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|flush_cnt
op_add_assign
id|qeth_tso_fill_buffer
c_func
(paren
id|buffer
comma
id|skb
)paren
suffix:semicolon
id|queue-&gt;next_buf_to_fill
op_assign
(paren
id|queue-&gt;next_buf_to_fill
op_plus
l_int|1
)paren
op_mod
id|QDIO_MAX_BUFFERS_PER_Q
suffix:semicolon
id|out
suffix:colon
id|atomic_set
c_func
(paren
op_amp
id|queue-&gt;state
comma
id|QETH_OUT_Q_UNLOCKED
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flush_cnt
)paren
id|qeth_flush_buffers
c_func
(paren
id|queue
comma
l_int|0
comma
id|start_index
comma
id|flush_cnt
)paren
suffix:semicolon
multiline_comment|/*do some statistics */
id|card-&gt;stats.tx_packets
op_increment
suffix:semicolon
id|card-&gt;stats.tx_bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
