multiline_comment|/* Header file for kernel module to match connection tracking information.&n; * GPL (C) 2001  Marc Boucher (marc@mbsi.ca).&n; */
macro_line|#ifndef _IPT_CONNTRACK_H
DECL|macro|_IPT_CONNTRACK_H
mdefine_line|#define _IPT_CONNTRACK_H
DECL|macro|IPT_CONNTRACK_STATE_BIT
mdefine_line|#define IPT_CONNTRACK_STATE_BIT(ctinfo) (1 &lt;&lt; ((ctinfo)%IP_CT_IS_REPLY+1))
DECL|macro|IPT_CONNTRACK_STATE_INVALID
mdefine_line|#define IPT_CONNTRACK_STATE_INVALID (1 &lt;&lt; 0)
DECL|macro|IPT_CONNTRACK_STATE_SNAT
mdefine_line|#define IPT_CONNTRACK_STATE_SNAT (1 &lt;&lt; (IP_CT_NUMBER + 1))
DECL|macro|IPT_CONNTRACK_STATE_DNAT
mdefine_line|#define IPT_CONNTRACK_STATE_DNAT (1 &lt;&lt; (IP_CT_NUMBER + 2))
DECL|macro|IPT_CONNTRACK_STATE_UNTRACKED
mdefine_line|#define IPT_CONNTRACK_STATE_UNTRACKED (1 &lt;&lt; (IP_CT_NUMBER + 3))
multiline_comment|/* flags, invflags: */
DECL|macro|IPT_CONNTRACK_STATE
mdefine_line|#define IPT_CONNTRACK_STATE&t;0x01
DECL|macro|IPT_CONNTRACK_PROTO
mdefine_line|#define IPT_CONNTRACK_PROTO&t;0x02
DECL|macro|IPT_CONNTRACK_ORIGSRC
mdefine_line|#define IPT_CONNTRACK_ORIGSRC&t;0x04
DECL|macro|IPT_CONNTRACK_ORIGDST
mdefine_line|#define IPT_CONNTRACK_ORIGDST&t;0x08
DECL|macro|IPT_CONNTRACK_REPLSRC
mdefine_line|#define IPT_CONNTRACK_REPLSRC&t;0x10
DECL|macro|IPT_CONNTRACK_REPLDST
mdefine_line|#define IPT_CONNTRACK_REPLDST&t;0x20
DECL|macro|IPT_CONNTRACK_STATUS
mdefine_line|#define IPT_CONNTRACK_STATUS&t;0x40
DECL|macro|IPT_CONNTRACK_EXPIRES
mdefine_line|#define IPT_CONNTRACK_EXPIRES&t;0x80
multiline_comment|/* This is exposed to userspace, so remains frozen in time. */
DECL|struct|ip_conntrack_old_tuple
r_struct
id|ip_conntrack_old_tuple
(brace
r_struct
(brace
DECL|member|ip
id|__u32
id|ip
suffix:semicolon
r_union
(brace
DECL|member|all
id|__u16
id|all
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|src
)brace
id|src
suffix:semicolon
r_struct
(brace
DECL|member|ip
id|__u32
id|ip
suffix:semicolon
r_union
(brace
DECL|member|all
id|__u16
id|all
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
multiline_comment|/* The protocol. */
DECL|member|protonum
id|u16
id|protonum
suffix:semicolon
DECL|member|dst
)brace
id|dst
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ipt_conntrack_info
r_struct
id|ipt_conntrack_info
(brace
DECL|member|statemask
DECL|member|statusmask
r_int
r_int
id|statemask
comma
id|statusmask
suffix:semicolon
DECL|member|tuple
r_struct
id|ip_conntrack_old_tuple
id|tuple
(braket
id|IP_CT_DIR_MAX
)braket
suffix:semicolon
DECL|member|sipmsk
DECL|member|dipmsk
r_struct
id|in_addr
id|sipmsk
(braket
id|IP_CT_DIR_MAX
)braket
comma
id|dipmsk
(braket
id|IP_CT_DIR_MAX
)braket
suffix:semicolon
DECL|member|expires_min
DECL|member|expires_max
r_int
r_int
id|expires_min
comma
id|expires_max
suffix:semicolon
multiline_comment|/* Flags word */
DECL|member|flags
id|u_int8_t
id|flags
suffix:semicolon
multiline_comment|/* Inverse flags */
DECL|member|invflags
id|u_int8_t
id|invflags
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /*_IPT_CONNTRACK_H*/
eof
