macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;linux/pfkeyv2.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
DECL|struct|ah_data
r_struct
id|ah_data
(brace
DECL|member|key
id|u8
op_star
id|key
suffix:semicolon
DECL|member|key_len
r_int
id|key_len
suffix:semicolon
DECL|member|work_digest
id|u8
op_star
id|work_digest
suffix:semicolon
DECL|member|digest_len
r_int
id|digest_len
suffix:semicolon
DECL|member|digest
r_void
(paren
op_star
id|digest
)paren
(paren
r_struct
id|ah_data
op_star
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|digest
)paren
suffix:semicolon
DECL|member|tfm
r_struct
id|crypto_tfm
op_star
id|tfm
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Clear mutable options and find final destination to substitute&n; * into IP header for digest calculation. Options are already checked&n; * for validity, so paranoia is not required. */
DECL|function|ip_clear_mutable_options
r_int
id|ip_clear_mutable_options
c_func
(paren
r_struct
id|iphdr
op_star
id|iph
comma
id|u32
op_star
id|daddr
)paren
(brace
r_int
r_char
op_star
id|optptr
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|iph
op_plus
l_int|1
)paren
suffix:semicolon
r_int
id|l
op_assign
id|iph-&gt;ihl
op_star
l_int|4
op_minus
l_int|20
suffix:semicolon
r_int
id|optlen
suffix:semicolon
r_while
c_loop
(paren
id|l
OG
l_int|0
)paren
(brace
r_switch
c_cond
(paren
op_star
id|optptr
)paren
(brace
r_case
id|IPOPT_END
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|IPOPT_NOOP
suffix:colon
id|l
op_decrement
suffix:semicolon
id|optptr
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|optlen
op_assign
id|optptr
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|optlen
id|l
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|optptr
)paren
(brace
r_case
id|IPOPT_SEC
suffix:colon
r_case
l_int|0x85
suffix:colon
multiline_comment|/* Some &quot;Extended Security&quot; crap. */
r_case
l_int|0x86
suffix:colon
multiline_comment|/* Another &quot;Commercial Security&quot; crap. */
r_case
id|IPOPT_RA
suffix:colon
r_case
l_int|0x80
op_or
l_int|21
suffix:colon
multiline_comment|/* RFC1770 */
r_break
suffix:semicolon
r_case
id|IPOPT_LSRR
suffix:colon
r_case
id|IPOPT_SSRR
suffix:colon
r_if
c_cond
(paren
id|optlen
OL
l_int|6
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memcpy
c_func
(paren
id|daddr
comma
id|optptr
op_plus
id|optlen
op_minus
l_int|4
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* Fall through */
r_default
suffix:colon
id|memset
c_func
(paren
id|optptr
op_plus
l_int|2
comma
l_int|0
comma
id|optlen
op_minus
l_int|2
)paren
suffix:semicolon
)brace
id|l
op_sub_assign
id|optlen
suffix:semicolon
id|optptr
op_add_assign
id|optlen
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|skb_ah_walk
r_void
id|skb_ah_walk
c_func
(paren
r_const
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|crypto_tfm
op_star
id|tfm
)paren
(brace
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_int
id|len
op_assign
id|skb-&gt;len
suffix:semicolon
r_int
id|start
op_assign
id|skb-&gt;len
op_minus
id|skb-&gt;data_len
suffix:semicolon
r_int
id|i
comma
id|copy
op_assign
id|start
op_minus
id|offset
suffix:semicolon
r_struct
id|scatterlist
id|sg
suffix:semicolon
multiline_comment|/* Checksum header. */
r_if
c_cond
(paren
id|copy
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy
OG
id|len
)paren
id|copy
op_assign
id|len
suffix:semicolon
id|sg.page
op_assign
id|virt_to_page
c_func
(paren
id|skb-&gt;data
op_plus
id|offset
)paren
suffix:semicolon
id|sg.offset
op_assign
(paren
r_int
r_int
)paren
(paren
id|skb-&gt;data
op_plus
id|offset
)paren
op_mod
id|PAGE_SIZE
suffix:semicolon
id|sg.length
op_assign
id|copy
suffix:semicolon
id|crypto_hmac_update
c_func
(paren
id|tfm
comma
op_amp
id|sg
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
id|copy
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|offset
op_add_assign
id|copy
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
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|nr_frags
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|end
suffix:semicolon
id|BUG_TRAP
c_func
(paren
id|start
op_le
id|offset
op_plus
id|len
)paren
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frags
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
(paren
id|copy
op_assign
id|end
op_minus
id|offset
)paren
OG
l_int|0
)paren
(brace
id|skb_frag_t
op_star
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
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|copy
OG
id|len
)paren
id|copy
op_assign
id|len
suffix:semicolon
id|sg.page
op_assign
id|frag-&gt;page
suffix:semicolon
id|sg.offset
op_assign
id|frag-&gt;page_offset
op_plus
id|offset
op_minus
id|start
suffix:semicolon
id|sg.length
op_assign
id|copy
suffix:semicolon
id|crypto_hmac_update
c_func
(paren
id|tfm
comma
op_amp
id|sg
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|len
op_sub_assign
id|copy
)paren
)paren
r_return
suffix:semicolon
id|offset
op_add_assign
id|copy
suffix:semicolon
)brace
id|start
op_assign
id|end
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frag_list
)paren
(brace
r_struct
id|sk_buff
op_star
id|list
op_assign
id|skb_shinfo
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|frag_list
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
(brace
r_int
id|end
suffix:semicolon
id|BUG_TRAP
c_func
(paren
id|start
op_le
id|offset
op_plus
id|len
)paren
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|list-&gt;len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|copy
op_assign
id|end
op_minus
id|offset
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy
OG
id|len
)paren
id|copy
op_assign
id|len
suffix:semicolon
id|skb_ah_walk
c_func
(paren
id|list
comma
id|tfm
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
id|copy
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|offset
op_add_assign
id|copy
suffix:semicolon
)brace
id|start
op_assign
id|end
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|len
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ah_hmac_digest
id|ah_hmac_digest
c_func
(paren
r_struct
id|ah_data
op_star
id|ahp
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|auth_data
)paren
(brace
r_struct
id|crypto_tfm
op_star
id|tfm
op_assign
id|ahp-&gt;tfm
suffix:semicolon
id|memset
c_func
(paren
id|auth_data
comma
l_int|0
comma
id|ahp-&gt;digest_len
)paren
suffix:semicolon
id|crypto_hmac_init
c_func
(paren
id|tfm
comma
id|ahp-&gt;key
comma
op_amp
id|ahp-&gt;key_len
)paren
suffix:semicolon
id|skb_ah_walk
c_func
(paren
id|skb
comma
id|tfm
)paren
suffix:semicolon
id|crypto_hmac_final
c_func
(paren
id|tfm
comma
id|ahp-&gt;key
comma
op_amp
id|ahp-&gt;key_len
comma
id|ahp-&gt;work_digest
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|auth_data
comma
id|ahp-&gt;work_digest
comma
id|ahp-&gt;digest_len
)paren
suffix:semicolon
)brace
DECL|function|ah_output
r_int
id|ah_output
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|dst_entry
op_star
id|dst
op_assign
id|skb-&gt;dst
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
op_assign
id|dst-&gt;xfrm
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
comma
op_star
id|top_iph
suffix:semicolon
r_struct
id|ip_auth_hdr
op_star
id|ah
suffix:semicolon
r_struct
id|ah_data
op_star
id|ahp
suffix:semicolon
r_union
(brace
r_struct
id|iphdr
id|iph
suffix:semicolon
r_char
id|buf
(braket
l_int|60
)braket
suffix:semicolon
)brace
id|tmp_iph
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;ip_summed
op_eq
id|CHECKSUM_HW
op_logical_and
id|skb_checksum_help
c_func
(paren
id|skb
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|xfrm_state_check_expire
c_func
(paren
id|x
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|xfrm_state_check_space
c_func
(paren
id|x
comma
id|skb
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|error
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
(brace
id|top_iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
id|x-&gt;props.header_len
)paren
suffix:semicolon
id|top_iph-&gt;ihl
op_assign
l_int|5
suffix:semicolon
id|top_iph-&gt;version
op_assign
l_int|4
suffix:semicolon
id|top_iph-&gt;tos
op_assign
l_int|0
suffix:semicolon
id|top_iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
)paren
suffix:semicolon
id|top_iph-&gt;frag_off
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_DF
)paren
)paren
)paren
id|__ip_select_ident
c_func
(paren
id|top_iph
comma
id|dst
comma
l_int|0
)paren
suffix:semicolon
id|top_iph-&gt;ttl
op_assign
l_int|0
suffix:semicolon
id|top_iph-&gt;protocol
op_assign
id|IPPROTO_AH
suffix:semicolon
id|top_iph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|top_iph-&gt;saddr
op_assign
id|x-&gt;props.saddr.xfrm4_addr
suffix:semicolon
id|top_iph-&gt;daddr
op_assign
id|x-&gt;id.daddr.xfrm4_addr
suffix:semicolon
id|ah
op_assign
(paren
r_struct
id|ip_auth_hdr
op_star
)paren
(paren
id|top_iph
op_plus
l_int|1
)paren
suffix:semicolon
id|ah-&gt;nexthdr
op_assign
id|IPPROTO_IP
suffix:semicolon
)brace
r_else
(brace
id|memcpy
c_func
(paren
op_amp
id|tmp_iph
comma
id|skb-&gt;data
comma
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|top_iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|skb_push
c_func
(paren
id|skb
comma
id|x-&gt;props.header_len
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|top_iph
comma
op_amp
id|tmp_iph
comma
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|iph
op_assign
op_amp
id|tmp_iph.iph
suffix:semicolon
id|top_iph-&gt;tos
op_assign
l_int|0
suffix:semicolon
id|top_iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
)paren
suffix:semicolon
id|top_iph-&gt;frag_off
op_assign
l_int|0
suffix:semicolon
id|top_iph-&gt;ttl
op_assign
l_int|0
suffix:semicolon
id|top_iph-&gt;protocol
op_assign
id|IPPROTO_AH
suffix:semicolon
id|top_iph-&gt;check
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|top_iph-&gt;ihl
op_ne
l_int|5
)paren
(brace
id|err
op_assign
id|ip_clear_mutable_options
c_func
(paren
id|top_iph
comma
op_amp
id|top_iph-&gt;daddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|error
suffix:semicolon
)brace
id|ah
op_assign
(paren
r_struct
id|ip_auth_hdr
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|top_iph
op_plus
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|ah-&gt;nexthdr
op_assign
id|iph-&gt;protocol
suffix:semicolon
)brace
id|ahp
op_assign
id|x-&gt;data
suffix:semicolon
id|ah-&gt;hdrlen
op_assign
(paren
(paren
(paren
id|ahp-&gt;digest_len
op_plus
l_int|12
op_plus
l_int|7
)paren
op_amp
op_complement
l_int|7
)paren
op_rshift
l_int|2
)paren
op_minus
l_int|2
suffix:semicolon
id|ah-&gt;reserved
op_assign
l_int|0
suffix:semicolon
id|ah-&gt;spi
op_assign
id|x-&gt;id.spi
suffix:semicolon
id|ah-&gt;seq_no
op_assign
id|htonl
c_func
(paren
op_increment
id|x-&gt;replay.oseq
)paren
suffix:semicolon
id|ahp
op_member_access_from_pointer
id|digest
c_func
(paren
id|ahp
comma
id|skb
comma
id|ah-&gt;auth_data
)paren
suffix:semicolon
id|top_iph-&gt;tos
op_assign
id|iph-&gt;tos
suffix:semicolon
id|top_iph-&gt;ttl
op_assign
id|iph-&gt;ttl
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
(brace
id|top_iph-&gt;frag_off
op_assign
id|iph-&gt;frag_off
op_amp
op_complement
id|htons
c_func
(paren
id|IP_MF
op_or
id|IP_OFFSET
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
(paren
id|IPCB
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|opt
)paren
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ip_options
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|top_iph-&gt;frag_off
op_assign
id|iph-&gt;frag_off
suffix:semicolon
id|top_iph-&gt;daddr
op_assign
id|iph-&gt;daddr
suffix:semicolon
r_if
c_cond
(paren
id|iph-&gt;ihl
op_ne
l_int|5
)paren
id|memcpy
c_func
(paren
id|top_iph
op_plus
l_int|1
comma
id|iph
op_plus
l_int|1
comma
id|iph-&gt;ihl
op_star
l_int|5
op_minus
l_int|20
)paren
suffix:semicolon
)brace
id|ip_send_check
c_func
(paren
id|top_iph
)paren
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb-&gt;data
suffix:semicolon
id|x-&gt;curlft.bytes
op_add_assign
id|skb-&gt;len
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb-&gt;dst
op_assign
id|dst_pop
c_func
(paren
id|dst
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|error
suffix:semicolon
r_return
id|NET_XMIT_BYPASS
suffix:semicolon
id|error
suffix:colon
id|spin_unlock_bh
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|ah_input
r_int
id|ah_input
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
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
id|ip_auth_hdr
op_star
id|ah
suffix:semicolon
r_struct
id|ah_data
op_star
id|ahp
suffix:semicolon
r_char
id|work_buf
(braket
l_int|60
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|ip_auth_hdr
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ah
op_assign
(paren
r_struct
id|ip_auth_hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|ahp
op_assign
id|x-&gt;data
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|ah-&gt;hdrlen
op_plus
l_int|2
)paren
op_lshift
l_int|2
)paren
op_ne
(paren
(paren
id|ahp-&gt;digest_len
op_plus
l_int|12
op_plus
l_int|7
)paren
op_amp
op_complement
l_int|7
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pskb_may_pull
c_func
(paren
id|skb
comma
(paren
id|ah-&gt;hdrlen
op_plus
l_int|2
)paren
op_lshift
l_int|2
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* We are going to _remove_ AH header to keep sockets happy,&n;&t; * so... Later this can change. */
r_if
c_cond
(paren
id|skb_cloned
c_func
(paren
id|skb
)paren
op_logical_and
id|pskb_expand_head
c_func
(paren
id|skb
comma
l_int|0
comma
l_int|0
comma
id|GFP_ATOMIC
)paren
)paren
r_goto
id|out
suffix:semicolon
id|ah
op_assign
(paren
r_struct
id|ip_auth_hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|memcpy
c_func
(paren
id|work_buf
comma
id|iph
comma
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|iph-&gt;ttl
op_assign
l_int|0
suffix:semicolon
id|iph-&gt;tos
op_assign
l_int|0
suffix:semicolon
id|iph-&gt;frag_off
op_assign
l_int|0
suffix:semicolon
id|iph-&gt;check
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|iph-&gt;ihl
op_ne
l_int|5
)paren
(brace
id|u32
id|dummy
suffix:semicolon
r_if
c_cond
(paren
id|ip_clear_mutable_options
c_func
(paren
id|iph
comma
op_amp
id|dummy
)paren
)paren
r_goto
id|out
suffix:semicolon
)brace
(brace
id|u8
id|auth_data
(braket
id|ahp-&gt;digest_len
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|auth_data
comma
id|ah-&gt;auth_data
comma
id|ahp-&gt;digest_len
)paren
suffix:semicolon
id|skb_push
c_func
(paren
id|skb
comma
id|skb-&gt;data
op_minus
id|skb-&gt;nh.raw
)paren
suffix:semicolon
id|ahp
op_member_access_from_pointer
id|digest
c_func
(paren
id|ahp
comma
id|skb
comma
id|ah-&gt;auth_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|ah-&gt;auth_data
comma
id|auth_data
comma
id|ahp-&gt;digest_len
)paren
)paren
(brace
id|x-&gt;stats.integrity_failed
op_increment
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
(paren
(paren
r_struct
id|iphdr
op_star
)paren
id|work_buf
)paren
op_member_access_from_pointer
id|protocol
op_assign
id|ah-&gt;nexthdr
suffix:semicolon
id|skb-&gt;nh.raw
op_assign
id|skb_pull
c_func
(paren
id|skb
comma
(paren
id|ah-&gt;hdrlen
op_plus
l_int|2
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|skb-&gt;nh.raw
comma
id|work_buf
comma
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|skb-&gt;nh.iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
)paren
suffix:semicolon
id|skb_pull
c_func
(paren
id|skb
comma
id|skb-&gt;nh.iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb-&gt;data
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|ah4_err
r_void
id|ah4_err
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
id|info
)paren
(brace
r_struct
id|iphdr
op_star
id|iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|ip_auth_hdr
op_star
id|ah
op_assign
(paren
r_struct
id|ip_auth_hdr
op_star
)paren
(paren
id|skb-&gt;data
op_plus
(paren
id|iph-&gt;ihl
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|x
suffix:semicolon
r_if
c_cond
(paren
id|skb-&gt;h.icmph-&gt;type
op_ne
id|ICMP_DEST_UNREACH
op_logical_or
id|skb-&gt;h.icmph-&gt;code
op_ne
id|ICMP_FRAG_NEEDED
)paren
r_return
suffix:semicolon
id|x
op_assign
id|xfrm_state_lookup
c_func
(paren
id|iph-&gt;daddr
comma
id|ah-&gt;spi
comma
id|IPPROTO_AH
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|x
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;pmtu discvovery on SA AH/%08x/%08x&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|ah-&gt;spi
)paren
comma
id|ntohl
c_func
(paren
id|iph-&gt;daddr
)paren
)paren
suffix:semicolon
id|xfrm_state_put
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|ah_init_state
r_int
id|ah_init_state
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_void
op_star
id|args
)paren
(brace
r_struct
id|ah_data
op_star
id|ahp
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;aalg
op_eq
l_int|NULL
op_logical_or
id|x-&gt;aalg-&gt;alg_key_len
op_eq
l_int|0
op_logical_or
id|x-&gt;aalg-&gt;alg_key_len
OG
l_int|512
)paren
r_goto
id|error
suffix:semicolon
id|ahp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|ahp
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ahp
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|ahp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ahp
)paren
)paren
suffix:semicolon
id|ahp-&gt;key
op_assign
id|x-&gt;aalg-&gt;alg_key
suffix:semicolon
id|ahp-&gt;key_len
op_assign
(paren
id|x-&gt;aalg-&gt;alg_key_len
op_plus
l_int|7
)paren
op_div
l_int|8
suffix:semicolon
id|ahp-&gt;tfm
op_assign
id|crypto_alloc_tfm
c_func
(paren
id|x-&gt;aalg-&gt;alg_name
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ahp-&gt;tfm
)paren
r_goto
id|error
suffix:semicolon
id|ahp-&gt;digest
op_assign
id|ah_hmac_digest
suffix:semicolon
id|ahp-&gt;digest_len
op_assign
l_int|12
suffix:semicolon
id|ahp-&gt;work_digest
op_assign
id|kmalloc
c_func
(paren
id|crypto_tfm_alg_digestsize
c_func
(paren
id|ahp-&gt;tfm
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ahp-&gt;work_digest
)paren
r_goto
id|error
suffix:semicolon
id|x-&gt;props.header_len
op_assign
(paren
l_int|12
op_plus
id|ahp-&gt;digest_len
op_plus
l_int|7
)paren
op_amp
op_complement
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
id|x-&gt;props.header_len
op_add_assign
l_int|20
suffix:semicolon
id|x-&gt;data
op_assign
id|ahp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
r_if
c_cond
(paren
id|ahp
)paren
(brace
r_if
c_cond
(paren
id|ahp-&gt;work_digest
)paren
id|kfree
c_func
(paren
id|ahp-&gt;work_digest
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ahp-&gt;tfm
)paren
id|crypto_free_tfm
c_func
(paren
id|ahp-&gt;tfm
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ahp
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|ah_destroy
r_void
id|ah_destroy
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
r_struct
id|ah_data
op_star
id|ahp
op_assign
id|x-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|ahp-&gt;work_digest
)paren
(brace
id|kfree
c_func
(paren
id|ahp-&gt;work_digest
)paren
suffix:semicolon
id|ahp-&gt;work_digest
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ahp-&gt;tfm
)paren
(brace
id|crypto_free_tfm
c_func
(paren
id|ahp-&gt;tfm
)paren
suffix:semicolon
id|ahp-&gt;tfm
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|variable|ah_type
r_static
r_struct
id|xfrm_type
id|ah_type
op_assign
(brace
dot
id|description
op_assign
l_string|&quot;AH4&quot;
comma
dot
id|proto
op_assign
id|IPPROTO_AH
comma
dot
id|init_state
op_assign
id|ah_init_state
comma
dot
id|destructor
op_assign
id|ah_destroy
comma
dot
id|input
op_assign
id|ah_input
comma
dot
id|output
op_assign
id|ah_output
)brace
suffix:semicolon
DECL|variable|ah4_protocol
r_static
r_struct
id|inet_protocol
id|ah4_protocol
op_assign
(brace
dot
id|handler
op_assign
id|xfrm4_rcv
comma
dot
id|err_handler
op_assign
id|ah4_err
comma
dot
id|no_policy
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|function|ah4_init
r_int
id|__init
id|ah4_init
c_func
(paren
r_void
)paren
(brace
id|SET_MODULE_OWNER
c_func
(paren
op_amp
id|ah_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfrm_register_type
c_func
(paren
op_amp
id|ah_type
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ip ah init: can&squot;t add xfrm type&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inet_add_protocol
c_func
(paren
op_amp
id|ah4_protocol
comma
id|IPPROTO_AH
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ip ah init: can&squot;t add protocol&bslash;n&quot;
)paren
suffix:semicolon
id|xfrm_unregister_type
c_func
(paren
op_amp
id|ah_type
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ah4_fini
r_static
r_void
id|__exit
id|ah4_fini
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|inet_del_protocol
c_func
(paren
op_amp
id|ah4_protocol
comma
id|IPPROTO_AH
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ip ah close: can&squot;t remove protocol&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfrm_unregister_type
c_func
(paren
op_amp
id|ah_type
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ip ah close: can&squot;t remove xfrm type&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|ah4_init
id|module_init
c_func
(paren
id|ah4_init
)paren
suffix:semicolon
DECL|variable|ah4_fini
id|module_exit
c_func
(paren
id|ah4_fini
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
