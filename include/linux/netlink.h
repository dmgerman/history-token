macro_line|#ifndef __LINUX_NETLINK_H
DECL|macro|__LINUX_NETLINK_H
mdefine_line|#define __LINUX_NETLINK_H
DECL|macro|NETLINK_ROUTE
mdefine_line|#define NETLINK_ROUTE&t;&t;0&t;/* Routing/device hook&t;&t;&t;&t;*/
DECL|macro|NETLINK_SKIP
mdefine_line|#define NETLINK_SKIP&t;&t;1&t;/* Reserved for ENskip  &t;&t;&t;*/
DECL|macro|NETLINK_USERSOCK
mdefine_line|#define NETLINK_USERSOCK&t;2&t;/* Reserved for user mode socket protocols &t;*/
DECL|macro|NETLINK_FIREWALL
mdefine_line|#define NETLINK_FIREWALL&t;3&t;/* Firewalling hook&t;&t;&t;&t;*/
DECL|macro|NETLINK_ARPD
mdefine_line|#define NETLINK_ARPD&t;&t;8
DECL|macro|NETLINK_ROUTE6
mdefine_line|#define NETLINK_ROUTE6&t;&t;11&t;/* af_inet6 route comm channel */
DECL|macro|NETLINK_IP6_FW
mdefine_line|#define NETLINK_IP6_FW&t;&t;13
DECL|macro|NETLINK_DNRTMSG
mdefine_line|#define NETLINK_DNRTMSG&t;&t;14&t;/* DECnet routing messages */
DECL|macro|NETLINK_TAPBASE
mdefine_line|#define NETLINK_TAPBASE&t;&t;16&t;/* 16 to 31 are ethertap */
DECL|macro|MAX_LINKS
mdefine_line|#define MAX_LINKS 32&t;&t;
DECL|struct|sockaddr_nl
r_struct
id|sockaddr_nl
(brace
DECL|member|nl_family
id|sa_family_t
id|nl_family
suffix:semicolon
multiline_comment|/* AF_NETLINK&t;*/
DECL|member|nl_pad
r_int
r_int
id|nl_pad
suffix:semicolon
multiline_comment|/* zero&t;&t;*/
DECL|member|nl_pid
id|__u32
id|nl_pid
suffix:semicolon
multiline_comment|/* process pid&t;*/
DECL|member|nl_groups
id|__u32
id|nl_groups
suffix:semicolon
multiline_comment|/* multicast groups mask */
)brace
suffix:semicolon
DECL|struct|nlmsghdr
r_struct
id|nlmsghdr
(brace
DECL|member|nlmsg_len
id|__u32
id|nlmsg_len
suffix:semicolon
multiline_comment|/* Length of message including header */
DECL|member|nlmsg_type
id|__u16
id|nlmsg_type
suffix:semicolon
multiline_comment|/* Message content */
DECL|member|nlmsg_flags
id|__u16
id|nlmsg_flags
suffix:semicolon
multiline_comment|/* Additional flags */
DECL|member|nlmsg_seq
id|__u32
id|nlmsg_seq
suffix:semicolon
multiline_comment|/* Sequence number */
DECL|member|nlmsg_pid
id|__u32
id|nlmsg_pid
suffix:semicolon
multiline_comment|/* Sending process PID */
)brace
suffix:semicolon
multiline_comment|/* Flags values */
DECL|macro|NLM_F_REQUEST
mdefine_line|#define NLM_F_REQUEST&t;&t;1&t;/* It is request message. &t;*/
DECL|macro|NLM_F_MULTI
mdefine_line|#define NLM_F_MULTI&t;&t;2&t;/* Multipart message, terminated by NLMSG_DONE */
DECL|macro|NLM_F_ACK
mdefine_line|#define NLM_F_ACK&t;&t;4&t;/* Reply with ack, with zero or error code */
DECL|macro|NLM_F_ECHO
mdefine_line|#define NLM_F_ECHO&t;&t;8&t;/* Echo this request &t;&t;*/
multiline_comment|/* Modifiers to GET request */
DECL|macro|NLM_F_ROOT
mdefine_line|#define NLM_F_ROOT&t;0x100&t;/* specify tree&t;root&t;*/
DECL|macro|NLM_F_MATCH
mdefine_line|#define NLM_F_MATCH&t;0x200&t;/* return all matching&t;*/
DECL|macro|NLM_F_ATOMIC
mdefine_line|#define NLM_F_ATOMIC&t;0x400&t;/* atomic GET&t;&t;*/
DECL|macro|NLM_F_DUMP
mdefine_line|#define NLM_F_DUMP&t;(NLM_F_ROOT|NLM_F_MATCH)
multiline_comment|/* Modifiers to NEW request */
DECL|macro|NLM_F_REPLACE
mdefine_line|#define NLM_F_REPLACE&t;0x100&t;/* Override existing&t;&t;*/
DECL|macro|NLM_F_EXCL
mdefine_line|#define NLM_F_EXCL&t;0x200&t;/* Do not touch, if it exists&t;*/
DECL|macro|NLM_F_CREATE
mdefine_line|#define NLM_F_CREATE&t;0x400&t;/* Create, if it does not exist&t;*/
DECL|macro|NLM_F_APPEND
mdefine_line|#define NLM_F_APPEND&t;0x800&t;/* Add to end of list&t;&t;*/
multiline_comment|/*&n;   4.4BSD ADD&t;&t;NLM_F_CREATE|NLM_F_EXCL&n;   4.4BSD CHANGE&t;NLM_F_REPLACE&n;&n;   True CHANGE&t;&t;NLM_F_CREATE|NLM_F_REPLACE&n;   Append&t;&t;NLM_F_CREATE&n;   Check&t;&t;NLM_F_EXCL&n; */
DECL|macro|NLMSG_ALIGNTO
mdefine_line|#define NLMSG_ALIGNTO&t;4
DECL|macro|NLMSG_ALIGN
mdefine_line|#define NLMSG_ALIGN(len) ( ((len)+NLMSG_ALIGNTO-1) &amp; ~(NLMSG_ALIGNTO-1) )
DECL|macro|NLMSG_LENGTH
mdefine_line|#define NLMSG_LENGTH(len) ((len)+NLMSG_ALIGN(sizeof(struct nlmsghdr)))
DECL|macro|NLMSG_SPACE
mdefine_line|#define NLMSG_SPACE(len) NLMSG_ALIGN(NLMSG_LENGTH(len))
DECL|macro|NLMSG_DATA
mdefine_line|#define NLMSG_DATA(nlh)  ((void*)(((char*)nlh) + NLMSG_LENGTH(0)))
DECL|macro|NLMSG_NEXT
mdefine_line|#define NLMSG_NEXT(nlh,len)&t; ((len) -= NLMSG_ALIGN((nlh)-&gt;nlmsg_len), &bslash;&n;&t;&t;&t;&t;  (struct nlmsghdr*)(((char*)(nlh)) + NLMSG_ALIGN((nlh)-&gt;nlmsg_len)))
DECL|macro|NLMSG_OK
mdefine_line|#define NLMSG_OK(nlh,len) ((len) &gt; 0 &amp;&amp; (nlh)-&gt;nlmsg_len &gt;= sizeof(struct nlmsghdr) &amp;&amp; &bslash;&n;&t;&t;&t;   (nlh)-&gt;nlmsg_len &lt;= (len))
DECL|macro|NLMSG_PAYLOAD
mdefine_line|#define NLMSG_PAYLOAD(nlh,len) ((nlh)-&gt;nlmsg_len - NLMSG_SPACE((len)))
DECL|macro|NLMSG_NOOP
mdefine_line|#define NLMSG_NOOP&t;&t;0x1&t;/* Nothing.&t;&t;*/
DECL|macro|NLMSG_ERROR
mdefine_line|#define NLMSG_ERROR&t;&t;0x2&t;/* Error&t;&t;*/
DECL|macro|NLMSG_DONE
mdefine_line|#define NLMSG_DONE&t;&t;0x3&t;/* End of a dump&t;*/
DECL|macro|NLMSG_OVERRUN
mdefine_line|#define NLMSG_OVERRUN&t;&t;0x4&t;/* Data lost&t;&t;*/
DECL|struct|nlmsgerr
r_struct
id|nlmsgerr
(brace
DECL|member|error
r_int
id|error
suffix:semicolon
DECL|member|msg
r_struct
id|nlmsghdr
id|msg
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NET_MAJOR
mdefine_line|#define NET_MAJOR 36&t;&t;/* Major 36 is reserved for networking &t;&t;&t;&t;&t;&t;*/
macro_line|#ifdef __KERNEL__
DECL|struct|netlink_skb_parms
r_struct
id|netlink_skb_parms
(brace
DECL|member|creds
r_struct
id|ucred
id|creds
suffix:semicolon
multiline_comment|/* Skb credentials&t;*/
DECL|member|pid
id|__u32
id|pid
suffix:semicolon
DECL|member|groups
id|__u32
id|groups
suffix:semicolon
DECL|member|dst_pid
id|__u32
id|dst_pid
suffix:semicolon
DECL|member|dst_groups
id|__u32
id|dst_groups
suffix:semicolon
DECL|member|eff_cap
id|kernel_cap_t
id|eff_cap
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NETLINK_CB
mdefine_line|#define NETLINK_CB(skb)&t;&t;(*(struct netlink_skb_parms*)&amp;((skb)-&gt;cb))
DECL|macro|NETLINK_CREDS
mdefine_line|#define NETLINK_CREDS(skb)&t;(&amp;NETLINK_CB((skb)).creds)
r_extern
r_int
id|netlink_attach
c_func
(paren
r_int
id|unit
comma
r_int
(paren
op_star
id|function
)paren
(paren
r_int
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
)paren
suffix:semicolon
r_extern
r_void
id|netlink_detach
c_func
(paren
r_int
id|unit
)paren
suffix:semicolon
r_extern
r_int
id|netlink_post
c_func
(paren
r_int
id|unit
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|init_netlink
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|sock
op_star
id|netlink_kernel_create
c_func
(paren
r_int
id|unit
comma
r_void
(paren
op_star
id|input
)paren
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|len
)paren
)paren
suffix:semicolon
r_extern
r_void
id|netlink_ack
c_func
(paren
r_struct
id|sk_buff
op_star
id|in_skb
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_int
id|err
)paren
suffix:semicolon
r_extern
r_int
id|netlink_unicast
c_func
(paren
r_struct
id|sock
op_star
id|ssk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|__u32
id|pid
comma
r_int
id|nonblock
)paren
suffix:semicolon
r_extern
r_void
id|netlink_broadcast
c_func
(paren
r_struct
id|sock
op_star
id|ssk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
id|__u32
id|pid
comma
id|__u32
id|group
comma
r_int
id|allocation
)paren
suffix:semicolon
r_extern
r_void
id|netlink_set_err
c_func
(paren
r_struct
id|sock
op_star
id|ssk
comma
id|__u32
id|pid
comma
id|__u32
id|group
comma
r_int
id|code
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;skb should fit one page. This choice is good for headerless malloc.&n; *&n; *      FIXME: What is the best size for SLAB???? --ANK&n; */
DECL|macro|NLMSG_GOODSIZE
mdefine_line|#define NLMSG_GOODSIZE (PAGE_SIZE - ((sizeof(struct sk_buff)+0xF)&amp;~0xF))
DECL|struct|netlink_callback
r_struct
id|netlink_callback
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|nlh
r_struct
id|nlmsghdr
op_star
id|nlh
suffix:semicolon
DECL|member|dump
r_int
(paren
op_star
id|dump
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
id|cb
)paren
suffix:semicolon
DECL|member|done
r_int
(paren
op_star
id|done
)paren
(paren
r_struct
id|netlink_callback
op_star
id|cb
)paren
suffix:semicolon
DECL|member|family
r_int
id|family
suffix:semicolon
DECL|member|args
r_int
id|args
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
id|__inline__
r_struct
id|nlmsghdr
op_star
DECL|function|__nlmsg_put
id|__nlmsg_put
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u32
id|pid
comma
id|u32
id|seq
comma
r_int
id|type
comma
r_int
id|len
)paren
(brace
r_struct
id|nlmsghdr
op_star
id|nlh
suffix:semicolon
r_int
id|size
op_assign
id|NLMSG_LENGTH
c_func
(paren
id|len
)paren
suffix:semicolon
id|nlh
op_assign
(paren
r_struct
id|nlmsghdr
op_star
)paren
id|skb_put
c_func
(paren
id|skb
comma
id|NLMSG_ALIGN
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
id|nlh-&gt;nlmsg_type
op_assign
id|type
suffix:semicolon
id|nlh-&gt;nlmsg_len
op_assign
id|size
suffix:semicolon
id|nlh-&gt;nlmsg_flags
op_assign
l_int|0
suffix:semicolon
id|nlh-&gt;nlmsg_pid
op_assign
id|pid
suffix:semicolon
id|nlh-&gt;nlmsg_seq
op_assign
id|seq
suffix:semicolon
r_return
id|nlh
suffix:semicolon
)brace
DECL|macro|NLMSG_PUT
mdefine_line|#define NLMSG_PUT(skb, pid, seq, type, len) &bslash;&n;({ if (skb_tailroom(skb) &lt; (int)NLMSG_SPACE(len)) goto nlmsg_failure; &bslash;&n;   __nlmsg_put(skb, pid, seq, type, len); })
r_extern
r_int
id|netlink_dump_start
c_func
(paren
r_struct
id|sock
op_star
id|ssk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|nlmsghdr
op_star
id|nlh
comma
r_int
(paren
op_star
id|dump
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|netlink_callback
op_star
)paren
comma
r_int
(paren
op_star
id|done
)paren
(paren
r_struct
id|netlink_callback
op_star
)paren
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif&t;/* __LINUX_NETLINK_H */
eof
