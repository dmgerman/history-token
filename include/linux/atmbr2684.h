macro_line|#ifndef _LINUX_ATMBR2684_H
DECL|macro|_LINUX_ATMBR2684_H
mdefine_line|#define _LINUX_ATMBR2684_H
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/if.h&gt;&t;&t;/* For IFNAMSIZ */
multiline_comment|/*&n; * Type of media we&squot;re bridging (ethernet, token ring, etc)  Currently only&n; * ethernet is supported&n; */
DECL|macro|BR2684_MEDIA_ETHERNET
mdefine_line|#define BR2684_MEDIA_ETHERNET&t;(0)&t;/* 802.3 */
DECL|macro|BR2684_MEDIA_802_4
mdefine_line|#define BR2684_MEDIA_802_4&t;(1)&t;/* 802.4 */
DECL|macro|BR2684_MEDIA_TR
mdefine_line|#define BR2684_MEDIA_TR&t;&t;(2)&t;/* 802.5 - token ring */
DECL|macro|BR2684_MEDIA_FDDI
mdefine_line|#define BR2684_MEDIA_FDDI&t;(3)
DECL|macro|BR2684_MEDIA_802_6
mdefine_line|#define BR2684_MEDIA_802_6&t;(4)&t;/* 802.6 */
multiline_comment|/*&n; * Is there FCS inbound on this VC?  This currently isn&squot;t supported.&n; */
DECL|macro|BR2684_FCSIN_NO
mdefine_line|#define BR2684_FCSIN_NO&t;&t;(0)
DECL|macro|BR2684_FCSIN_IGNORE
mdefine_line|#define BR2684_FCSIN_IGNORE&t;(1)
DECL|macro|BR2684_FCSIN_VERIFY
mdefine_line|#define BR2684_FCSIN_VERIFY&t;(2)
multiline_comment|/*&n; * Is there FCS outbound on this VC?  This currently isn&squot;t supported.&n; */
DECL|macro|BR2684_FCSOUT_NO
mdefine_line|#define BR2684_FCSOUT_NO&t;(0)
DECL|macro|BR2684_FCSOUT_SENDZERO
mdefine_line|#define BR2684_FCSOUT_SENDZERO&t;(1)
DECL|macro|BR2684_FCSOUT_GENERATE
mdefine_line|#define BR2684_FCSOUT_GENERATE&t;(2)
multiline_comment|/*&n; * Does this VC include LLC encapsulation?&n; */
DECL|macro|BR2684_ENCAPS_VC
mdefine_line|#define BR2684_ENCAPS_VC&t;(0)&t;/* VC-mux */
DECL|macro|BR2684_ENCAPS_LLC
mdefine_line|#define BR2684_ENCAPS_LLC&t;(1)
DECL|macro|BR2684_ENCAPS_AUTODETECT
mdefine_line|#define BR2684_ENCAPS_AUTODETECT (2)&t;/* Unsuported */
multiline_comment|/*&n; * This is for the ATM_NEWBACKENDIF call - these are like socket families:&n; * the first element of the structure is the backend number and the rest&n; * is per-backend specific&n; */
DECL|struct|atm_newif_br2684
r_struct
id|atm_newif_br2684
(brace
DECL|member|backend_num
id|atm_backend_t
id|backend_num
suffix:semicolon
multiline_comment|/* ATM_BACKEND_BR2684 */
DECL|member|media
r_int
id|media
suffix:semicolon
multiline_comment|/* BR2684_MEDIA_* */
DECL|member|ifname
r_char
id|ifname
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|mtu
r_int
id|mtu
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This structure is used to specify a br2684 interface - either by a&n; * positive integer (returned by ATM_NEWBACKENDIF) or the interfaces name&n; */
DECL|macro|BR2684_FIND_BYNOTHING
mdefine_line|#define BR2684_FIND_BYNOTHING&t;(0)
DECL|macro|BR2684_FIND_BYNUM
mdefine_line|#define BR2684_FIND_BYNUM&t;(1)
DECL|macro|BR2684_FIND_BYIFNAME
mdefine_line|#define BR2684_FIND_BYIFNAME&t;(2)
DECL|struct|br2684_if_spec
r_struct
id|br2684_if_spec
(brace
DECL|member|method
r_int
id|method
suffix:semicolon
multiline_comment|/* BR2684_FIND_* */
r_union
(brace
DECL|member|ifname
r_char
id|ifname
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|devnum
r_int
id|devnum
suffix:semicolon
DECL|member|spec
)brace
id|spec
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is for the ATM_SETBACKEND call - these are like socket families:&n; * the first element of the structure is the backend number and the rest&n; * is per-backend specific&n; */
DECL|struct|atm_backend_br2684
r_struct
id|atm_backend_br2684
(brace
DECL|member|backend_num
id|atm_backend_t
id|backend_num
suffix:semicolon
multiline_comment|/* ATM_BACKEND_BR2684 */
DECL|member|ifspec
r_struct
id|br2684_if_spec
id|ifspec
suffix:semicolon
DECL|member|fcs_in
r_int
id|fcs_in
suffix:semicolon
multiline_comment|/* BR2684_FCSIN_* */
DECL|member|fcs_out
r_int
id|fcs_out
suffix:semicolon
multiline_comment|/* BR2684_FCSOUT_* */
DECL|member|fcs_auto
r_int
id|fcs_auto
suffix:semicolon
multiline_comment|/* 1: fcs_{in,out} disabled if no FCS rx&squot;ed */
DECL|member|encaps
r_int
id|encaps
suffix:semicolon
multiline_comment|/* BR2684_ENCAPS_* */
DECL|member|has_vpiid
r_int
id|has_vpiid
suffix:semicolon
multiline_comment|/* 1: use vpn_id - Unsupported */
DECL|member|vpn_id
id|__u8
id|vpn_id
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|send_padding
r_int
id|send_padding
suffix:semicolon
multiline_comment|/* unsupported */
DECL|member|min_size
r_int
id|min_size
suffix:semicolon
multiline_comment|/* we will pad smaller packets than this */
)brace
suffix:semicolon
multiline_comment|/*&n; * The BR2684_SETFILT ioctl is an experimental mechanism for folks&n; * terminating a large number of IP-only vcc&squot;s.  When netfilter allows&n; * efficient per-if in/out filters, this support will be removed&n; */
DECL|struct|br2684_filter
r_struct
id|br2684_filter
(brace
DECL|member|prefix
id|__u32
id|prefix
suffix:semicolon
multiline_comment|/* network byte order */
DECL|member|netmask
id|__u32
id|netmask
suffix:semicolon
multiline_comment|/* 0 = disable filter */
)brace
suffix:semicolon
DECL|struct|br2684_filter_set
r_struct
id|br2684_filter_set
(brace
DECL|member|ifspec
r_struct
id|br2684_if_spec
id|ifspec
suffix:semicolon
DECL|member|filter
r_struct
id|br2684_filter
id|filter
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|BR2684_SETFILT
mdefine_line|#define BR2684_SETFILT&t;_IOW( &squot;a&squot;, ATMIOC_BACKEND + 0, &bslash;&n;&t;&t;&t;&t;struct br2684_filter_set)
macro_line|#endif /* _LINUX_ATMBR2684_H */
eof
