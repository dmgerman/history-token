macro_line|#ifndef __LINUX_BRIDGE_EBT_AMONG_H
DECL|macro|__LINUX_BRIDGE_EBT_AMONG_H
mdefine_line|#define __LINUX_BRIDGE_EBT_AMONG_H
DECL|macro|EBT_AMONG_DST
mdefine_line|#define EBT_AMONG_DST 0x01
DECL|macro|EBT_AMONG_SRC
mdefine_line|#define EBT_AMONG_SRC 0x02
multiline_comment|/* Grzegorz Borowiak &lt;grzes@gnu.univ.gda.pl&gt; 2003&n; * &n; * Write-once-read-many hash table, used for checking if a given&n; * MAC address belongs to a set or not and possibly for checking&n; * if it is related with a given IPv4 address.&n; *&n; * The hash value of an address is its last byte.&n; * &n; * In real-world ethernet addresses, values of the last byte are&n; * evenly distributed and there is no need to consider other bytes.&n; * It would only slow the routines down.&n; *&n; * For MAC address comparison speedup reasons, we introduce a trick.&n; * MAC address is mapped onto an array of two 32-bit integers.&n; * This pair of integers is compared with MAC addresses in the&n; * hash table, which are stored also in form of pairs of integers&n; * (in `cmp&squot; array). This is quick as it requires only two elementary&n; * number comparisons in worst case. Further, we take advantage of&n; * fact that entropy of 3 last bytes of address is larger than entropy&n; * of 3 first bytes. So first we compare 4 last bytes of addresses and&n; * if they are the same we compare 2 first.&n; *&n; * Yes, it is a memory overhead, but in 2003 AD, who cares?&n; */
DECL|struct|ebt_mac_wormhash_tuple
r_struct
id|ebt_mac_wormhash_tuple
(brace
DECL|member|cmp
r_uint32
id|cmp
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ip
r_uint32
id|ip
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ebt_mac_wormhash
r_struct
id|ebt_mac_wormhash
(brace
DECL|member|table
r_int
id|table
(braket
l_int|257
)braket
suffix:semicolon
DECL|member|poolsize
r_int
id|poolsize
suffix:semicolon
DECL|member|pool
r_struct
id|ebt_mac_wormhash_tuple
id|pool
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ebt_mac_wormhash_size
mdefine_line|#define ebt_mac_wormhash_size(x) ((x) ? sizeof(struct ebt_mac_wormhash) &bslash;&n;&t;&t;+ (x)-&gt;poolsize * sizeof(struct ebt_mac_wormhash_tuple) : 0)
DECL|struct|ebt_among_info
r_struct
id|ebt_among_info
(brace
DECL|member|wh_dst_ofs
r_int
id|wh_dst_ofs
suffix:semicolon
DECL|member|wh_src_ofs
r_int
id|wh_src_ofs
suffix:semicolon
DECL|member|bitmask
r_int
id|bitmask
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EBT_AMONG_DST_NEG
mdefine_line|#define EBT_AMONG_DST_NEG 0x1
DECL|macro|EBT_AMONG_SRC_NEG
mdefine_line|#define EBT_AMONG_SRC_NEG 0x2
DECL|macro|ebt_among_wh_dst
mdefine_line|#define ebt_among_wh_dst(x) ((x)-&gt;wh_dst_ofs ? &bslash;&n;&t;(struct ebt_mac_wormhash*)((char*)(x) + (x)-&gt;wh_dst_ofs) : NULL)
DECL|macro|ebt_among_wh_src
mdefine_line|#define ebt_among_wh_src(x) ((x)-&gt;wh_src_ofs ? &bslash;&n;&t;(struct ebt_mac_wormhash*)((char*)(x) + (x)-&gt;wh_src_ofs) : NULL)
DECL|macro|EBT_AMONG_MATCH
mdefine_line|#define EBT_AMONG_MATCH &quot;among&quot;
macro_line|#endif
eof
