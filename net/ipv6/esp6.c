multiline_comment|/*&n; * Copyright (C)2002 USAGI/WIDE Project&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; * Authors&n; *&n; *&t;Mitsuru KANDA @USAGI       : IPv6 Support &n; * &t;Kazunori MIYAZAWA @USAGI   :&n; * &t;Kunihiro Ishiguro &lt;kunihiro@ipinfusion.com&gt;&n; * &t;&n; * &t;This file is derived from net/ipv4/esp.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/xfrm.h&gt;
macro_line|#include &lt;net/esp.h&gt;
macro_line|#include &lt;asm/scatterlist.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;linux/pfkeyv2.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;linux/icmpv6.h&gt;
DECL|function|esp6_output
r_static
r_int
id|esp6_output
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
r_int
id|hdr_len
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
id|ipv6hdr
op_star
id|top_iph
suffix:semicolon
r_struct
id|ipv6_esp_hdr
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
id|esp
op_assign
id|x-&gt;data
suffix:semicolon
id|hdr_len
op_assign
id|skb-&gt;h.raw
op_minus
id|skb-&gt;data
op_plus
r_sizeof
(paren
op_star
id|esph
)paren
op_plus
id|esp-&gt;conf.ivlen
suffix:semicolon
multiline_comment|/* Strip IP+ESP header. */
id|__skb_pull
c_func
(paren
id|skb
comma
id|hdr_len
)paren
suffix:semicolon
multiline_comment|/* Now skb is pure payload to encrypt */
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Round to block size */
id|clen
op_assign
id|skb-&gt;len
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
(brace
r_goto
id|error
suffix:semicolon
)brace
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
id|top_iph
op_assign
(paren
r_struct
id|ipv6hdr
op_star
)paren
id|__skb_push
c_func
(paren
id|skb
comma
id|hdr_len
)paren
suffix:semicolon
id|esph
op_assign
(paren
r_struct
id|ipv6_esp_hdr
op_star
)paren
id|skb-&gt;h.raw
suffix:semicolon
id|top_iph-&gt;payload_len
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
op_star
id|top_iph
)paren
)paren
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
op_star
id|skb-&gt;nh.raw
suffix:semicolon
op_star
id|skb-&gt;nh.raw
op_assign
id|IPPROTO_ESP
suffix:semicolon
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
op_star
id|sg
op_assign
op_amp
id|esp-&gt;sgbuf
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|nfrags
OG
id|ESP_NUM_FAST_SG
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
op_amp
id|esp-&gt;sgbuf
(braket
l_int|0
)braket
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
id|ipv6_esp_hdr
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
id|err
op_assign
l_int|0
suffix:semicolon
id|error
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|esp6_input
r_static
r_int
id|esp6_input
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
id|ipv6hdr
op_star
id|iph
suffix:semicolon
r_struct
id|ipv6_esp_hdr
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
id|ipv6_esp_hdr
)paren
op_minus
id|esp-&gt;conf.ivlen
op_minus
id|alen
suffix:semicolon
r_int
id|hdr_len
op_assign
id|skb-&gt;h.raw
op_minus
id|skb-&gt;nh.raw
suffix:semicolon
r_int
id|nfrags
suffix:semicolon
r_int
r_char
op_star
id|tmp_hdr
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
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
id|ipv6_esp_hdr
)paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out_nofree
suffix:semicolon
)brace
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
(brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out_nofree
suffix:semicolon
)brace
id|tmp_hdr
op_assign
id|kmalloc
c_func
(paren
id|hdr_len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp_hdr
)paren
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_nofree
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|tmp_hdr
comma
id|skb-&gt;nh.raw
comma
id|hdr_len
)paren
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
id|ret
op_assign
op_minus
id|EINVAL
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
(brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|skb-&gt;ip_summed
op_assign
id|CHECKSUM_NONE
suffix:semicolon
id|esph
op_assign
(paren
r_struct
id|ipv6_esp_hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
id|iph
op_assign
id|skb-&gt;nh.ipv6h
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
op_star
id|sg
op_assign
op_amp
id|esp-&gt;sgbuf
(braket
l_int|0
)braket
suffix:semicolon
id|u8
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
id|ESP_NUM_FAST_SG
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
(brace
id|ret
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
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
id|ipv6_esp_hdr
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
op_amp
id|esp-&gt;sgbuf
(braket
l_int|0
)braket
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
(brace
id|LIMIT_NETDEBUG
c_func
(paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ipsec esp packet is garbage padlen=%d, elen=%d&bslash;n&quot;
comma
id|padlen
op_plus
l_int|2
comma
id|elen
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* ... check padding bits here. Silly. :-) */
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
id|ipv6_esp_hdr
)paren
op_plus
id|esp-&gt;conf.ivlen
)paren
suffix:semicolon
id|skb-&gt;nh.raw
op_add_assign
r_sizeof
(paren
r_struct
id|ipv6_esp_hdr
)paren
op_plus
id|esp-&gt;conf.ivlen
suffix:semicolon
id|memcpy
c_func
(paren
id|skb-&gt;nh.raw
comma
id|tmp_hdr
comma
id|hdr_len
)paren
suffix:semicolon
id|skb-&gt;nh.ipv6h-&gt;payload_len
op_assign
id|htons
c_func
(paren
id|skb-&gt;len
op_minus
r_sizeof
(paren
r_struct
id|ipv6hdr
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|nexthdr
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|out
suffix:colon
id|kfree
c_func
(paren
id|tmp_hdr
)paren
suffix:semicolon
id|out_nofree
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|esp6_get_max_size
r_static
id|u32
id|esp6_get_max_size
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
id|esp-&gt;auth.icv_full_len
suffix:semicolon
)brace
DECL|function|esp6_err
r_static
r_void
id|esp6_err
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|inet6_skb_parm
op_star
id|opt
comma
r_int
id|type
comma
r_int
id|code
comma
r_int
id|offset
comma
id|__u32
id|info
)paren
(brace
r_struct
id|ipv6hdr
op_star
id|iph
op_assign
(paren
r_struct
id|ipv6hdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_struct
id|ipv6_esp_hdr
op_star
id|esph
op_assign
(paren
r_struct
id|ipv6_esp_hdr
op_star
)paren
(paren
id|skb-&gt;data
op_plus
id|offset
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
id|type
op_ne
id|ICMPV6_DEST_UNREACH
op_logical_and
id|type
op_ne
id|ICMPV6_PKT_TOOBIG
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
id|AF_INET6
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
l_string|&quot;pmtu discovery on SA ESP/%08x/&quot;
l_string|&quot;%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|esph-&gt;spi
)paren
comma
id|NIP6
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
DECL|function|esp6_destroy
r_static
r_void
id|esp6_destroy
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
op_logical_neg
id|esp
)paren
r_return
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
DECL|function|esp6_init_state
r_static
r_int
id|esp6_init_state
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
r_if
c_cond
(paren
id|x-&gt;encap
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
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|esp-&gt;conf.ivec
op_eq
l_int|NULL
)paren
)paren
r_goto
id|error
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
id|ipv6_esp_hdr
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
id|ipv6hdr
)paren
suffix:semicolon
id|x-&gt;data
op_assign
id|esp
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
DECL|variable|esp6_type
r_static
r_struct
id|xfrm_type
id|esp6_type
op_assign
(brace
dot
id|description
op_assign
l_string|&quot;ESP6&quot;
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
id|esp6_init_state
comma
dot
id|destructor
op_assign
id|esp6_destroy
comma
dot
id|get_max_size
op_assign
id|esp6_get_max_size
comma
dot
id|input
op_assign
id|esp6_input
comma
dot
id|output
op_assign
id|esp6_output
)brace
suffix:semicolon
DECL|variable|esp6_protocol
r_static
r_struct
id|inet6_protocol
id|esp6_protocol
op_assign
(brace
dot
id|handler
op_assign
id|xfrm6_rcv
comma
dot
id|err_handler
op_assign
id|esp6_err
comma
dot
id|flags
op_assign
id|INET6_PROTO_NOPOLICY
comma
)brace
suffix:semicolon
DECL|function|esp6_init
r_static
r_int
id|__init
id|esp6_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|xfrm_register_type
c_func
(paren
op_amp
id|esp6_type
comma
id|AF_INET6
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ipv6 esp init: can&squot;t add xfrm type&bslash;n&quot;
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
id|inet6_add_protocol
c_func
(paren
op_amp
id|esp6_protocol
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
l_string|&quot;ipv6 esp init: can&squot;t add protocol&bslash;n&quot;
)paren
suffix:semicolon
id|xfrm_unregister_type
c_func
(paren
op_amp
id|esp6_type
comma
id|AF_INET6
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
DECL|function|esp6_fini
r_static
r_void
id|__exit
id|esp6_fini
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|inet6_del_protocol
c_func
(paren
op_amp
id|esp6_protocol
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
l_string|&quot;ipv6 esp close: can&squot;t remove protocol&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfrm_unregister_type
c_func
(paren
op_amp
id|esp6_type
comma
id|AF_INET6
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ipv6 esp close: can&squot;t remove xfrm type&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|esp6_init
id|module_init
c_func
(paren
id|esp6_init
)paren
suffix:semicolon
DECL|variable|esp6_fini
id|module_exit
c_func
(paren
id|esp6_fini
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
