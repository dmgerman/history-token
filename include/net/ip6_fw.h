macro_line|#ifndef __NET_IP6_FW_H
DECL|macro|__NET_IP6_FW_H
mdefine_line|#define __NET_IP6_FW_H
DECL|macro|IP6_FW_LISTHEAD
mdefine_line|#define IP6_FW_LISTHEAD&t;&t;0x1000
DECL|macro|IP6_FW_ACCEPT
mdefine_line|#define IP6_FW_ACCEPT&t;&t;0x0001
DECL|macro|IP6_FW_REJECT
mdefine_line|#define IP6_FW_REJECT&t;&t;0x0002
DECL|macro|IP6_FW_DEBUG
mdefine_line|#define IP6_FW_DEBUG&t;2
DECL|macro|IP6_FW_MSG_ADD
mdefine_line|#define IP6_FW_MSG_ADD&t;&t;1
DECL|macro|IP6_FW_MSG_DEL
mdefine_line|#define IP6_FW_MSG_DEL&t;&t;2
DECL|macro|IP6_FW_MSG_REPORT
mdefine_line|#define IP6_FW_MSG_REPORT&t;3
multiline_comment|/*&n; *&t;Fast &quot;hack&quot; user interface&n; */
DECL|struct|ip6_fw_msg
r_struct
id|ip6_fw_msg
(brace
DECL|member|dst
r_struct
id|in6_addr
id|dst
suffix:semicolon
DECL|member|src
r_struct
id|in6_addr
id|src
suffix:semicolon
DECL|member|dst_len
r_int
id|dst_len
suffix:semicolon
DECL|member|src_len
r_int
id|src_len
suffix:semicolon
DECL|member|action
r_int
id|action
suffix:semicolon
DECL|member|policy
r_int
id|policy
suffix:semicolon
DECL|member|proto
r_int
id|proto
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|sport
id|__u16
id|sport
suffix:semicolon
DECL|member|dport
id|__u16
id|dport
suffix:semicolon
DECL|member|transp
)brace
id|transp
suffix:semicolon
DECL|member|data
r_int
r_int
id|data
suffix:semicolon
DECL|member|icmp_type
r_int
id|icmp_type
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|msg_len
r_int
id|msg_len
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;net/flow.h&gt;
DECL|struct|ip6_fw_rule
r_struct
id|ip6_fw_rule
(brace
DECL|member|flowr
r_struct
id|flow_rule
id|flowr
suffix:semicolon
DECL|member|next
r_struct
id|ip6_fw_rule
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|ip6_fw_rule
op_star
id|prev
suffix:semicolon
DECL|member|info
r_struct
id|flowi
id|info
suffix:semicolon
DECL|member|policy
r_int
r_int
id|policy
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
