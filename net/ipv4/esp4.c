macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;net/inet_ecn.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;net/esp.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;linux/pfkeyv2.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
DECL|macro|MAX_SG_ONSTACK
mdefine_line|#define MAX_SG_ONSTACK 4
multiline_comment|/* decapsulation data for use when post-processing */
DECL|struct|esp_decap_data
r_struct
id|esp_decap_data
(brace
DECL|member|saddr
id|xfrm_address_t
id|saddr
suffix:semicolon
DECL|member|sport
id|__u16
id|sport
suffix:semicolon
DECL|member|proto
id|__u8
id|proto
suffix:semicolon
)brace
suffix:semicolon
DECL|function|esp_output
r_int
id|esp_output
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
id|ip_esp_hdr
op_star
id|esph
suffix:semicolon
r_struct
id|crypto_tfm
op_star
id|tfm
suffix:semicolon
r_struct
id|esp_data
op_star
id|esp
suffix:semicolon
r_struct
id|sk_buff
op_star
id|trailer
suffix:semicolon
r_struct
id|udphdr
op_star
id|uh
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|xfrm_encap_tmpl
op_star
id|encap
op_assign
l_int|NULL
suffix:semicolon
r_int
id|blksize
suffix:semicolon
r_int
id|clen
suffix:semicolon
r_int
id|alen
suffix:semicolon
r_int
id|nfrags
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
multiline_comment|/* First, if the skb is not checksummed, complete checksum. */
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
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|error_nolock
suffix:semicolon
)brace
id|spin_lock_bh
c_func
(paren
op_amp
id|x-&gt;lock
)paren
suffix:semicolon
id|err
op_assign
id|xfrm_check_output
c_func
(paren
id|x
comma
id|skb
comma
id|AF_INET
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
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Strip IP header in transport mode. Save it. */
r_if
c_cond
(paren
op_logical_neg
id|x-&gt;props.mode
)paren
(brace
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|tmp_iph
comma
id|iph
comma
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|__skb_pull
c_func
(paren
id|skb
comma
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
)brace
multiline_comment|/* Now skb is pure payload to encrypt */
multiline_comment|/* Round to block size */
id|clen
op_assign
id|skb-&gt;len
suffix:semicolon
id|esp
op_assign
id|x-&gt;data
suffix:semicolon
id|alen
op_assign
id|esp-&gt;auth.icv_trunc_len
suffix:semicolon
id|tfm
op_assign
id|esp-&gt;conf.tfm
suffix:semicolon
id|blksize
op_assign
(paren
id|crypto_tfm_alg_blocksize
c_func
(paren
id|tfm
)paren
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
suffix:semicolon
id|clen
op_assign
(paren
id|clen
op_plus
l_int|2
op_plus
id|blksize
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|blksize
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|esp-&gt;conf.padlen
)paren
id|clen
op_assign
(paren
id|clen
op_plus
id|esp-&gt;conf.padlen
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|esp-&gt;conf.padlen
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nfrags
op_assign
id|skb_cow_data
c_func
(paren
id|skb
comma
id|clen
op_minus
id|skb-&gt;len
op_plus
id|alen
comma
op_amp
id|trailer
)paren
)paren
OL
l_int|0
)paren
r_goto
id|error
suffix:semicolon
multiline_comment|/* Fill padding... */
r_do
(brace
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
id|clen
op_minus
id|skb-&gt;len
op_minus
l_int|2
suffix:semicolon
id|i
op_increment
)paren
op_star
(paren
id|u8
op_star
)paren
(paren
id|trailer-&gt;tail
op_plus
id|i
)paren
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|0
)paren
suffix:semicolon
op_star
(paren
id|u8
op_star
)paren
(paren
id|trailer-&gt;tail
op_plus
id|clen
op_minus
id|skb-&gt;len
op_minus
l_int|2
)paren
op_assign
(paren
id|clen
op_minus
id|skb-&gt;len
)paren
op_minus
l_int|2
suffix:semicolon
id|pskb_put
c_func
(paren
id|skb
comma
id|trailer
comma
id|clen
op_minus
id|skb-&gt;len
)paren
suffix:semicolon
id|encap
op_assign
id|x-&gt;encap
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
id|esph
op_assign
(paren
r_struct
id|ip_esp_hdr
op_star
)paren
(paren
id|top_iph
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|encap
op_logical_and
id|encap-&gt;encap_type
)paren
(brace
r_switch
c_cond
(paren
id|encap-&gt;encap_type
)paren
(brace
r_case
id|UDP_ENCAP_ESPINUDP
suffix:colon
id|uh
op_assign
(paren
r_struct
id|udphdr
op_star
)paren
id|esph
suffix:semicolon
id|esph
op_assign
(paren
r_struct
id|ip_esp_hdr
op_star
)paren
(paren
id|uh
op_plus
l_int|1
)paren
suffix:semicolon
id|top_iph-&gt;protocol
op_assign
id|IPPROTO_UDP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;esp_output(): Unhandled encap: %u&bslash;n&quot;
comma
id|encap-&gt;encap_type
)paren
suffix:semicolon
id|top_iph-&gt;protocol
op_assign
id|IPPROTO_ESP
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
id|top_iph-&gt;protocol
op_assign
id|IPPROTO_ESP
suffix:semicolon
op_star
(paren
id|u8
op_star
)paren
(paren
id|trailer-&gt;tail
op_minus
l_int|1
)paren
op_assign
id|IPPROTO_IPIP
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
id|iph-&gt;tos
suffix:semicolon
multiline_comment|/* DS disclosed */
r_if
c_cond
(paren
id|x-&gt;props.flags
op_amp
id|XFRM_STATE_NOECN
)paren
id|IP_ECN_clear
c_func
(paren
id|top_iph
)paren
suffix:semicolon
id|top_iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
op_plus
id|alen
)paren
suffix:semicolon
id|top_iph-&gt;frag_off
op_assign
id|iph-&gt;frag_off
op_amp
id|htons
c_func
(paren
id|IP_DF
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|top_iph-&gt;frag_off
)paren
)paren
id|ip_select_ident
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
id|iph-&gt;ttl
suffix:semicolon
multiline_comment|/* TTL disclosed */
id|top_iph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|top_iph-&gt;saddr
op_assign
id|x-&gt;props.saddr.a4
suffix:semicolon
id|top_iph-&gt;daddr
op_assign
id|x-&gt;id.daddr.a4
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
id|esph
op_assign
(paren
r_struct
id|ip_esp_hdr
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
id|iph-&gt;ihl
op_star
l_int|4
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
r_if
c_cond
(paren
id|encap
op_logical_and
id|encap-&gt;encap_type
)paren
(brace
r_switch
c_cond
(paren
id|encap-&gt;encap_type
)paren
(brace
r_case
id|UDP_ENCAP_ESPINUDP
suffix:colon
id|uh
op_assign
(paren
r_struct
id|udphdr
op_star
)paren
id|esph
suffix:semicolon
id|esph
op_assign
(paren
r_struct
id|ip_esp_hdr
op_star
)paren
(paren
id|uh
op_plus
l_int|1
)paren
suffix:semicolon
id|top_iph-&gt;protocol
op_assign
id|IPPROTO_UDP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;esp_output(): Unhandled encap: %u&bslash;n&quot;
comma
id|encap-&gt;encap_type
)paren
suffix:semicolon
id|top_iph-&gt;protocol
op_assign
id|IPPROTO_ESP
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
id|top_iph-&gt;protocol
op_assign
id|IPPROTO_ESP
suffix:semicolon
id|iph
op_assign
op_amp
id|tmp_iph.iph
suffix:semicolon
id|top_iph-&gt;tot_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
op_plus
id|alen
)paren
suffix:semicolon
id|top_iph-&gt;check
op_assign
l_int|0
suffix:semicolon
id|top_iph-&gt;frag_off
op_assign
id|iph-&gt;frag_off
suffix:semicolon
op_star
(paren
id|u8
op_star
)paren
(paren
id|trailer-&gt;tail
op_minus
l_int|1
)paren
op_assign
id|iph-&gt;protocol
suffix:semicolon
)brace
multiline_comment|/* this is non-NULL only with UDP Encapsulation */
r_if
c_cond
(paren
id|encap
op_logical_and
id|uh
)paren
(brace
id|uh-&gt;source
op_assign
id|encap-&gt;encap_sport
suffix:semicolon
id|uh-&gt;dest
op_assign
id|encap-&gt;encap_dport
suffix:semicolon
id|uh-&gt;len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
op_plus
id|alen
op_minus
r_sizeof
(paren
r_struct
id|iphdr
)paren
)paren
suffix:semicolon
id|uh-&gt;check
op_assign
l_int|0
suffix:semicolon
)brace
id|esph-&gt;spi
op_assign
id|x-&gt;id.spi
suffix:semicolon
id|esph-&gt;seq_no
op_assign
id|htonl
c_func
(paren
op_increment
id|x-&gt;replay.oseq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|esp-&gt;conf.ivlen
)paren
id|crypto_cipher_set_iv
c_func
(paren
id|tfm
comma
id|esp-&gt;conf.ivec
comma
id|crypto_tfm_alg_ivsize
c_func
(paren
id|tfm
)paren
)paren
suffix:semicolon
r_do
(brace
r_struct
id|scatterlist
id|sgbuf
(braket
id|nfrags
OG
id|MAX_SG_ONSTACK
ques
c_cond
l_int|0
suffix:colon
id|nfrags
)braket
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sg
op_assign
id|sgbuf
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|nfrags
OG
id|MAX_SG_ONSTACK
)paren
)paren
(brace
id|sg
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|scatterlist
)paren
op_star
id|nfrags
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sg
)paren
r_goto
id|error
suffix:semicolon
)brace
id|skb_to_sgvec
c_func
(paren
id|skb
comma
id|sg
comma
id|esph-&gt;enc_data
op_plus
id|esp-&gt;conf.ivlen
op_minus
id|skb-&gt;data
comma
id|clen
)paren
suffix:semicolon
id|crypto_cipher_encrypt
c_func
(paren
id|tfm
comma
id|sg
comma
id|sg
comma
id|clen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|sg
op_ne
id|sgbuf
)paren
)paren
id|kfree
c_func
(paren
id|sg
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|esp-&gt;conf.ivlen
)paren
(brace
id|memcpy
c_func
(paren
id|esph-&gt;enc_data
comma
id|esp-&gt;conf.ivec
comma
id|crypto_tfm_alg_ivsize
c_func
(paren
id|tfm
)paren
)paren
suffix:semicolon
id|crypto_cipher_get_iv
c_func
(paren
id|tfm
comma
id|esp-&gt;conf.ivec
comma
id|crypto_tfm_alg_ivsize
c_func
(paren
id|tfm
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|esp-&gt;auth.icv_full_len
)paren
(brace
id|esp-&gt;auth
dot
id|icv
c_func
(paren
id|esp
comma
id|skb
comma
(paren
id|u8
op_star
)paren
id|esph
op_minus
id|skb-&gt;data
comma
r_sizeof
(paren
r_struct
id|ip_esp_hdr
)paren
op_plus
id|esp-&gt;conf.ivlen
op_plus
id|clen
comma
id|trailer-&gt;tail
)paren
suffix:semicolon
id|pskb_put
c_func
(paren
id|skb
comma
id|trailer
comma
id|alen
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
id|x-&gt;curlft.packets
op_increment
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
(brace
id|err
op_assign
op_minus
id|EHOSTUNREACH
suffix:semicolon
r_goto
id|error_nolock
suffix:semicolon
)brace
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
id|error_nolock
suffix:colon
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
multiline_comment|/*&n; * Note: detecting truncated vs. non-truncated authentication data is very&n; * expensive, so we only support truncated data, which is the recommended&n; * and common case.&n; */
DECL|function|esp_input
r_int
id|esp_input
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_struct
id|xfrm_decap_state
op_star
id|decap
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
id|ip_esp_hdr
op_star
id|esph
suffix:semicolon
r_struct
id|esp_data
op_star
id|esp
op_assign
id|x-&gt;data
suffix:semicolon
r_struct
id|sk_buff
op_star
id|trailer
suffix:semicolon
r_int
id|blksize
op_assign
id|crypto_tfm_alg_blocksize
c_func
(paren
id|esp-&gt;conf.tfm
)paren
suffix:semicolon
r_int
id|alen
op_assign
id|esp-&gt;auth.icv_trunc_len
suffix:semicolon
r_int
id|elen
op_assign
id|skb-&gt;len
op_minus
r_sizeof
(paren
r_struct
id|ip_esp_hdr
)paren
op_minus
id|esp-&gt;conf.ivlen
op_minus
id|alen
suffix:semicolon
r_int
id|nfrags
suffix:semicolon
r_int
id|encap_len
op_assign
l_int|0
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
id|ip_esp_hdr
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|elen
op_le
l_int|0
op_logical_or
(paren
id|elen
op_amp
(paren
id|blksize
op_minus
l_int|1
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* If integrity check is required, do this. */
r_if
c_cond
(paren
id|esp-&gt;auth.icv_full_len
)paren
(brace
id|u8
id|sum
(braket
id|esp-&gt;auth.icv_full_len
)braket
suffix:semicolon
id|u8
id|sum1
(braket
id|alen
)braket
suffix:semicolon
id|esp-&gt;auth
dot
id|icv
c_func
(paren
id|esp
comma
id|skb
comma
l_int|0
comma
id|skb-&gt;len
op_minus
id|alen
comma
id|sum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|skb-&gt;len
op_minus
id|alen
comma
id|sum1
comma
id|alen
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|memcmp
c_func
(paren
id|sum
comma
id|sum1
comma
id|alen
)paren
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
r_if
c_cond
(paren
(paren
id|nfrags
op_assign
id|skb_cow_data
c_func
(paren
id|skb
comma
l_int|0
comma
op_amp
id|trailer
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
id|esph
op_assign
(paren
r_struct
id|ip_esp_hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.iph
suffix:semicolon
multiline_comment|/* Get ivec. This can be wrong, check against another impls. */
r_if
c_cond
(paren
id|esp-&gt;conf.ivlen
)paren
id|crypto_cipher_set_iv
c_func
(paren
id|esp-&gt;conf.tfm
comma
id|esph-&gt;enc_data
comma
id|crypto_tfm_alg_ivsize
c_func
(paren
id|esp-&gt;conf.tfm
)paren
)paren
suffix:semicolon
(brace
id|u8
id|nexthdr
(braket
l_int|2
)braket
suffix:semicolon
r_struct
id|scatterlist
id|sgbuf
(braket
id|nfrags
OG
id|MAX_SG_ONSTACK
ques
c_cond
l_int|0
suffix:colon
id|nfrags
)braket
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sg
op_assign
id|sgbuf
suffix:semicolon
id|u8
id|workbuf
(braket
l_int|60
)braket
suffix:semicolon
r_int
id|padlen
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|nfrags
OG
id|MAX_SG_ONSTACK
)paren
)paren
(brace
id|sg
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|scatterlist
)paren
op_star
id|nfrags
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sg
)paren
r_goto
id|out
suffix:semicolon
)brace
id|skb_to_sgvec
c_func
(paren
id|skb
comma
id|sg
comma
r_sizeof
(paren
r_struct
id|ip_esp_hdr
)paren
op_plus
id|esp-&gt;conf.ivlen
comma
id|elen
)paren
suffix:semicolon
id|crypto_cipher_decrypt
c_func
(paren
id|esp-&gt;conf.tfm
comma
id|sg
comma
id|sg
comma
id|elen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|sg
op_ne
id|sgbuf
)paren
)paren
id|kfree
c_func
(paren
id|sg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb_copy_bits
c_func
(paren
id|skb
comma
id|skb-&gt;len
op_minus
id|alen
op_minus
l_int|2
comma
id|nexthdr
comma
l_int|2
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|padlen
op_assign
id|nexthdr
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|padlen
op_plus
l_int|2
op_ge
id|elen
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* ... check padding bits here. Silly. :-) */
r_if
c_cond
(paren
id|x-&gt;encap
op_logical_and
id|decap
op_logical_and
id|decap-&gt;decap_type
)paren
(brace
r_struct
id|esp_decap_data
op_star
id|encap_data
suffix:semicolon
r_struct
id|udphdr
op_star
id|uh
op_assign
(paren
r_struct
id|udphdr
op_star
)paren
(paren
id|iph
op_plus
l_int|1
)paren
suffix:semicolon
id|encap_data
op_assign
(paren
r_struct
id|esp_decap_data
op_star
)paren
(paren
id|decap-&gt;decap_data
)paren
suffix:semicolon
id|encap_data-&gt;proto
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|decap-&gt;decap_type
)paren
(brace
r_case
id|UDP_ENCAP_ESPINUDP
suffix:colon
r_if
c_cond
(paren
(paren
r_void
op_star
)paren
id|uh
op_eq
(paren
r_void
op_star
)paren
id|esph
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;esp_input(): Got ESP; expecting ESPinUDP&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|encap_data-&gt;proto
op_assign
id|AF_INET
suffix:semicolon
id|encap_data-&gt;saddr.a4
op_assign
id|iph-&gt;saddr
suffix:semicolon
id|encap_data-&gt;sport
op_assign
id|uh-&gt;source
suffix:semicolon
id|encap_len
op_assign
(paren
r_void
op_star
)paren
id|esph
op_minus
(paren
r_void
op_star
)paren
id|uh
suffix:semicolon
r_if
c_cond
(paren
id|encap_len
op_ne
r_sizeof
(paren
op_star
id|uh
)paren
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;esp_input(): UDP -&gt; ESP: too much room: %d&bslash;n&quot;
comma
id|encap_len
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;esp_input(): processing unknown encap type: %u&bslash;n&quot;
comma
id|decap-&gt;decap_type
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|iph-&gt;protocol
op_assign
id|nexthdr
(braket
l_int|1
)braket
suffix:semicolon
id|pskb_trim
c_func
(paren
id|skb
comma
id|skb-&gt;len
op_minus
id|alen
op_minus
id|padlen
op_minus
l_int|2
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|workbuf
comma
id|skb-&gt;nh.raw
comma
id|iph-&gt;ihl
op_star
l_int|4
)paren
suffix:semicolon
id|skb-&gt;h.raw
op_assign
id|skb_pull
c_func
(paren
id|skb
comma
r_sizeof
(paren
r_struct
id|ip_esp_hdr
)paren
op_plus
id|esp-&gt;conf.ivlen
)paren
suffix:semicolon
id|skb-&gt;nh.raw
op_add_assign
id|encap_len
op_plus
r_sizeof
(paren
r_struct
id|ip_esp_hdr
)paren
op_plus
id|esp-&gt;conf.ivlen
suffix:semicolon
id|memcpy
c_func
(paren
id|skb-&gt;nh.raw
comma
id|workbuf
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
)brace
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
DECL|function|esp_post_input
r_int
id|esp_post_input
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_struct
id|xfrm_decap_state
op_star
id|decap
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_if
c_cond
(paren
id|x-&gt;encap
)paren
(brace
r_struct
id|xfrm_encap_tmpl
op_star
id|encap
suffix:semicolon
r_struct
id|esp_decap_data
op_star
id|decap_data
suffix:semicolon
id|encap
op_assign
id|x-&gt;encap
suffix:semicolon
id|decap_data
op_assign
(paren
r_struct
id|esp_decap_data
op_star
)paren
(paren
id|decap-&gt;decap_data
)paren
suffix:semicolon
multiline_comment|/* first, make sure that the decap type == the encap type */
r_if
c_cond
(paren
id|encap-&gt;encap_type
op_ne
id|decap-&gt;decap_type
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Next, if we don&squot;t have an encap type, then ignore it */
r_if
c_cond
(paren
op_logical_neg
id|encap-&gt;encap_type
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|encap-&gt;encap_type
)paren
(brace
r_case
id|UDP_ENCAP_ESPINUDP
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * 1) if the NAT-T peer&squot;s IP or port changed then&n;&t;&t;&t; *    advertize the change to the keying daemon.&n;&t;&t;&t; *    This is an inbound SA, so just compare&n;&t;&t;&t; *    SRC ports.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|decap_data-&gt;proto
op_eq
id|AF_INET
op_logical_and
(paren
id|decap_data-&gt;saddr.a4
op_ne
id|x-&gt;props.saddr.a4
op_logical_or
id|decap_data-&gt;sport
op_ne
id|encap-&gt;encap_sport
)paren
)paren
(brace
id|xfrm_address_t
id|ipaddr
suffix:semicolon
id|ipaddr.a4
op_assign
id|decap_data-&gt;saddr.a4
suffix:semicolon
id|km_new_mapping
c_func
(paren
id|x
comma
op_amp
id|ipaddr
comma
id|decap_data-&gt;sport
)paren
suffix:semicolon
multiline_comment|/* XXX: perhaps add an extra&n;&t;&t;&t;&t; * policy check here, to see&n;&t;&t;&t;&t; * if we should allow or&n;&t;&t;&t;&t; * reject a packet from a&n;&t;&t;&t;&t; * different source&n;&t;&t;&t;&t; * address/port.&n;&t;&t;&t;&t; */
)brace
multiline_comment|/*&n;&t;&t;&t; * 2) ignore UDP/TCP checksums in case&n;&t;&t;&t; *    of NAT-T in Transport Mode, or&n;&t;&t;&t; *    perform other post-processing fixes&n;&t;&t;&t; *    as per * draft-ietf-ipsec-udp-encaps-06,&n;&t;&t;&t; *    section 3.1.2&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|x-&gt;props.mode
)paren
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_UNNECESSARY
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;esp4_post_input(): Unhandled encap type: %u&bslash;n&quot;
comma
id|encap-&gt;encap_type
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|esp4_get_max_size
r_static
id|u32
id|esp4_get_max_size
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_int
id|mtu
)paren
(brace
r_struct
id|esp_data
op_star
id|esp
op_assign
id|x-&gt;data
suffix:semicolon
id|u32
id|blksize
op_assign
id|crypto_tfm_alg_blocksize
c_func
(paren
id|esp-&gt;conf.tfm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
(brace
id|mtu
op_assign
(paren
id|mtu
op_plus
l_int|2
op_plus
id|blksize
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|blksize
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* The worst case. */
id|mtu
op_add_assign
l_int|2
op_plus
id|blksize
suffix:semicolon
)brace
r_if
c_cond
(paren
id|esp-&gt;conf.padlen
)paren
id|mtu
op_assign
(paren
id|mtu
op_plus
id|esp-&gt;conf.padlen
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|esp-&gt;conf.padlen
op_minus
l_int|1
)paren
suffix:semicolon
r_return
id|mtu
op_plus
id|x-&gt;props.header_len
op_plus
id|esp-&gt;auth.icv_trunc_len
suffix:semicolon
)brace
DECL|function|esp4_err
r_void
id|esp4_err
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
id|ip_esp_hdr
op_star
id|esph
op_assign
(paren
r_struct
id|ip_esp_hdr
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
(paren
id|xfrm_address_t
op_star
)paren
op_amp
id|iph-&gt;daddr
comma
id|esph-&gt;spi
comma
id|IPPROTO_ESP
comma
id|AF_INET
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
l_string|&quot;pmtu discovery on SA ESP/%08x/%08x&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|esph-&gt;spi
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
DECL|function|esp_destroy
r_void
id|esp_destroy
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
r_struct
id|esp_data
op_star
id|esp
op_assign
id|x-&gt;data
suffix:semicolon
r_if
c_cond
(paren
id|esp-&gt;conf.tfm
)paren
(brace
id|crypto_free_tfm
c_func
(paren
id|esp-&gt;conf.tfm
)paren
suffix:semicolon
id|esp-&gt;conf.tfm
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|esp-&gt;conf.ivec
)paren
(brace
id|kfree
c_func
(paren
id|esp-&gt;conf.ivec
)paren
suffix:semicolon
id|esp-&gt;conf.ivec
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|esp-&gt;auth.tfm
)paren
(brace
id|crypto_free_tfm
c_func
(paren
id|esp-&gt;auth.tfm
)paren
suffix:semicolon
id|esp-&gt;auth.tfm
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|esp-&gt;auth.work_icv
)paren
(brace
id|kfree
c_func
(paren
id|esp-&gt;auth.work_icv
)paren
suffix:semicolon
id|esp-&gt;auth.work_icv
op_assign
l_int|NULL
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|esp
)paren
suffix:semicolon
)brace
DECL|function|esp_init_state
r_int
id|esp_init_state
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
id|esp_data
op_star
id|esp
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* null auth and encryption can have zero length keys */
r_if
c_cond
(paren
id|x-&gt;aalg
)paren
(brace
r_if
c_cond
(paren
id|x-&gt;aalg-&gt;alg_key_len
OG
l_int|512
)paren
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x-&gt;ealg
op_eq
l_int|NULL
)paren
r_goto
id|error
suffix:semicolon
id|esp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|esp
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|esp
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
id|esp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|esp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;aalg
)paren
(brace
r_struct
id|xfrm_algo_desc
op_star
id|aalg_desc
suffix:semicolon
id|esp-&gt;auth.key
op_assign
id|x-&gt;aalg-&gt;alg_key
suffix:semicolon
id|esp-&gt;auth.key_len
op_assign
(paren
id|x-&gt;aalg-&gt;alg_key_len
op_plus
l_int|7
)paren
op_div
l_int|8
suffix:semicolon
id|esp-&gt;auth.tfm
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
id|esp-&gt;auth.tfm
op_eq
l_int|NULL
)paren
r_goto
id|error
suffix:semicolon
id|esp-&gt;auth.icv
op_assign
id|esp_hmac_digest
suffix:semicolon
id|aalg_desc
op_assign
id|xfrm_aalg_get_byname
c_func
(paren
id|x-&gt;aalg-&gt;alg_name
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|aalg_desc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aalg_desc-&gt;uinfo.auth.icv_fullbits
op_div
l_int|8
op_ne
id|crypto_tfm_alg_digestsize
c_func
(paren
id|esp-&gt;auth.tfm
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ESP: %s digestsize %u != %hu&bslash;n&quot;
comma
id|x-&gt;aalg-&gt;alg_name
comma
id|crypto_tfm_alg_digestsize
c_func
(paren
id|esp-&gt;auth.tfm
)paren
comma
id|aalg_desc-&gt;uinfo.auth.icv_fullbits
op_div
l_int|8
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|esp-&gt;auth.icv_full_len
op_assign
id|aalg_desc-&gt;uinfo.auth.icv_fullbits
op_div
l_int|8
suffix:semicolon
id|esp-&gt;auth.icv_trunc_len
op_assign
id|aalg_desc-&gt;uinfo.auth.icv_truncbits
op_div
l_int|8
suffix:semicolon
id|esp-&gt;auth.work_icv
op_assign
id|kmalloc
c_func
(paren
id|esp-&gt;auth.icv_full_len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|esp-&gt;auth.work_icv
)paren
r_goto
id|error
suffix:semicolon
)brace
id|esp-&gt;conf.key
op_assign
id|x-&gt;ealg-&gt;alg_key
suffix:semicolon
id|esp-&gt;conf.key_len
op_assign
(paren
id|x-&gt;ealg-&gt;alg_key_len
op_plus
l_int|7
)paren
op_div
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;props.ealgo
op_eq
id|SADB_EALG_NULL
)paren
id|esp-&gt;conf.tfm
op_assign
id|crypto_alloc_tfm
c_func
(paren
id|x-&gt;ealg-&gt;alg_name
comma
id|CRYPTO_TFM_MODE_ECB
)paren
suffix:semicolon
r_else
id|esp-&gt;conf.tfm
op_assign
id|crypto_alloc_tfm
c_func
(paren
id|x-&gt;ealg-&gt;alg_name
comma
id|CRYPTO_TFM_MODE_CBC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|esp-&gt;conf.tfm
op_eq
l_int|NULL
)paren
r_goto
id|error
suffix:semicolon
id|esp-&gt;conf.ivlen
op_assign
id|crypto_tfm_alg_ivsize
c_func
(paren
id|esp-&gt;conf.tfm
)paren
suffix:semicolon
id|esp-&gt;conf.padlen
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|esp-&gt;conf.ivlen
)paren
(brace
id|esp-&gt;conf.ivec
op_assign
id|kmalloc
c_func
(paren
id|esp-&gt;conf.ivlen
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|get_random_bytes
c_func
(paren
id|esp-&gt;conf.ivec
comma
id|esp-&gt;conf.ivlen
)paren
suffix:semicolon
)brace
id|crypto_cipher_setkey
c_func
(paren
id|esp-&gt;conf.tfm
comma
id|esp-&gt;conf.key
comma
id|esp-&gt;conf.key_len
)paren
suffix:semicolon
id|x-&gt;props.header_len
op_assign
r_sizeof
(paren
r_struct
id|ip_esp_hdr
)paren
op_plus
id|esp-&gt;conf.ivlen
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;props.mode
)paren
id|x-&gt;props.header_len
op_add_assign
r_sizeof
(paren
r_struct
id|iphdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x-&gt;encap
)paren
(brace
r_struct
id|xfrm_encap_tmpl
op_star
id|encap
op_assign
id|x-&gt;encap
suffix:semicolon
r_if
c_cond
(paren
id|encap-&gt;encap_type
)paren
(brace
r_switch
c_cond
(paren
id|encap-&gt;encap_type
)paren
(brace
r_case
id|UDP_ENCAP_ESPINUDP
suffix:colon
id|x-&gt;props.header_len
op_add_assign
r_sizeof
(paren
r_struct
id|udphdr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
id|KERN_INFO
l_string|&quot;esp_init_state(): Unhandled encap type: %u&bslash;n&quot;
comma
id|encap-&gt;encap_type
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
id|x-&gt;data
op_assign
id|esp
suffix:semicolon
id|x-&gt;props.trailer_len
op_assign
id|esp4_get_max_size
c_func
(paren
id|x
comma
l_int|0
)paren
op_minus
id|x-&gt;props.header_len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
r_if
c_cond
(paren
id|esp
)paren
(brace
r_if
c_cond
(paren
id|esp-&gt;auth.tfm
)paren
id|crypto_free_tfm
c_func
(paren
id|esp-&gt;auth.tfm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|esp-&gt;auth.work_icv
)paren
id|kfree
c_func
(paren
id|esp-&gt;auth.work_icv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|esp-&gt;conf.tfm
)paren
id|crypto_free_tfm
c_func
(paren
id|esp-&gt;conf.tfm
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|esp
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|esp_type
r_static
r_struct
id|xfrm_type
id|esp_type
op_assign
(brace
dot
id|description
op_assign
l_string|&quot;ESP4&quot;
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|proto
op_assign
id|IPPROTO_ESP
comma
dot
id|init_state
op_assign
id|esp_init_state
comma
dot
id|destructor
op_assign
id|esp_destroy
comma
dot
id|get_max_size
op_assign
id|esp4_get_max_size
comma
dot
id|input
op_assign
id|esp_input
comma
dot
id|post_input
op_assign
id|esp_post_input
comma
dot
id|output
op_assign
id|esp_output
)brace
suffix:semicolon
DECL|variable|esp4_protocol
r_static
r_struct
id|inet_protocol
id|esp4_protocol
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
id|esp4_err
comma
dot
id|no_policy
op_assign
l_int|1
comma
)brace
suffix:semicolon
DECL|function|esp4_init
r_static
r_int
id|__init
id|esp4_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|xfrm_decap_state
id|decap
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
r_struct
id|esp_decap_data
)paren
OL
r_sizeof
(paren
id|decap.decap_data
)paren
)paren
(brace
r_extern
r_void
id|decap_data_too_small
c_func
(paren
r_void
)paren
suffix:semicolon
id|decap_data_too_small
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xfrm_register_type
c_func
(paren
op_amp
id|esp_type
comma
id|AF_INET
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ip esp init: can&squot;t add xfrm type&bslash;n&quot;
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
id|esp4_protocol
comma
id|IPPROTO_ESP
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ip esp init: can&squot;t add protocol&bslash;n&quot;
)paren
suffix:semicolon
id|xfrm_unregister_type
c_func
(paren
op_amp
id|esp_type
comma
id|AF_INET
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
DECL|function|esp4_fini
r_static
r_void
id|__exit
id|esp4_fini
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
id|esp4_protocol
comma
id|IPPROTO_ESP
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ip esp close: can&squot;t remove protocol&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfrm_unregister_type
c_func
(paren
op_amp
id|esp_type
comma
id|AF_INET
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ip esp close: can&squot;t remove xfrm type&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|esp4_init
id|module_init
c_func
(paren
id|esp4_init
)paren
suffix:semicolon
DECL|variable|esp4_fini
id|module_exit
c_func
(paren
id|esp4_fini
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
