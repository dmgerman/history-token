multiline_comment|/*&n; * Defines for synchronous PPP/Cisco link level subroutines.&n; *&n; * Copyright (C) 1994 Cronyx Ltd.&n; * Author: Serge Vakulenko, &lt;vak@zebub.msk.su&gt;&n; *&n; * This software is distributed with NO WARRANTIES, not even the implied&n; * warranties for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Authors grant any other persons or organizations permission to use&n; * or modify this software as long as this message is kept with the software,&n; * all derivative works or modified versions.&n; *&n; * Version 1.7, Wed Jun  7 22:12:02 MSD 1995&n; *&n; *&n; *&n; */
macro_line|#ifndef _SYNCPPP_H_
DECL|macro|_SYNCPPP_H_
mdefine_line|#define _SYNCPPP_H_ 1
macro_line|#ifdef __KERNEL__
DECL|struct|slcp
r_struct
id|slcp
(brace
DECL|member|state
id|u16
id|state
suffix:semicolon
multiline_comment|/* state machine */
DECL|member|magic
id|u32
id|magic
suffix:semicolon
multiline_comment|/* local magic number */
DECL|member|echoid
id|u_char
id|echoid
suffix:semicolon
multiline_comment|/* id of last keepalive echo request */
DECL|member|confid
id|u_char
id|confid
suffix:semicolon
multiline_comment|/* id of last configuration request */
)brace
suffix:semicolon
DECL|struct|sipcp
r_struct
id|sipcp
(brace
DECL|member|state
id|u16
id|state
suffix:semicolon
multiline_comment|/* state machine */
DECL|member|confid
id|u_char
id|confid
suffix:semicolon
multiline_comment|/* id of last configuration request */
)brace
suffix:semicolon
DECL|struct|sppp
r_struct
id|sppp
(brace
DECL|member|pp_next
r_struct
id|sppp
op_star
id|pp_next
suffix:semicolon
multiline_comment|/* next interface in keepalive list */
DECL|member|pp_flags
id|u32
id|pp_flags
suffix:semicolon
multiline_comment|/* use Cisco protocol instead of PPP */
DECL|member|pp_alivecnt
id|u16
id|pp_alivecnt
suffix:semicolon
multiline_comment|/* keepalive packets counter */
DECL|member|pp_loopcnt
id|u16
id|pp_loopcnt
suffix:semicolon
multiline_comment|/* loopback detection counter */
DECL|member|pp_seq
id|u32
id|pp_seq
suffix:semicolon
multiline_comment|/* local sequence number */
DECL|member|pp_rseq
id|u32
id|pp_rseq
suffix:semicolon
multiline_comment|/* remote sequence number */
DECL|member|lcp
r_struct
id|slcp
id|lcp
suffix:semicolon
multiline_comment|/* LCP params */
DECL|member|ipcp
r_struct
id|sipcp
id|ipcp
suffix:semicolon
multiline_comment|/* IPCP params */
DECL|member|ibytes
DECL|member|obytes
id|u32
id|ibytes
comma
id|obytes
suffix:semicolon
multiline_comment|/* Bytes in/out */
DECL|member|ipkts
DECL|member|opkts
id|u32
id|ipkts
comma
id|opkts
suffix:semicolon
multiline_comment|/* Packets in/out */
DECL|member|pp_timer
r_struct
id|timer_list
id|pp_timer
suffix:semicolon
DECL|member|pp_if
r_struct
id|net_device
op_star
id|pp_if
suffix:semicolon
DECL|member|pp_link_state
r_char
id|pp_link_state
suffix:semicolon
multiline_comment|/* Link status */
)brace
suffix:semicolon
DECL|struct|ppp_device
r_struct
id|ppp_device
(brace
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Network device pointer */
DECL|member|sppp
r_struct
id|sppp
id|sppp
suffix:semicolon
multiline_comment|/* Synchronous PPP */
)brace
suffix:semicolon
DECL|macro|sppp_of
mdefine_line|#define sppp_of(dev)&t;&bslash;&n;&t;    (&amp;((struct ppp_device *)(*(unsigned long *)((dev)-&gt;priv)))-&gt;sppp)
DECL|macro|PP_KEEPALIVE
mdefine_line|#define PP_KEEPALIVE    0x01    /* use keepalive protocol */
DECL|macro|PP_CISCO
mdefine_line|#define PP_CISCO        0x02    /* use Cisco protocol instead of PPP */
DECL|macro|PP_TIMO
mdefine_line|#define PP_TIMO         0x04    /* cp_timeout routine active */
DECL|macro|PP_DEBUG
mdefine_line|#define PP_DEBUG&t;0x08
DECL|macro|PPP_MTU
mdefine_line|#define PPP_MTU          1500    /* max. transmit unit */
DECL|macro|LCP_STATE_CLOSED
mdefine_line|#define LCP_STATE_CLOSED        0       /* LCP state: closed (conf-req sent) */
DECL|macro|LCP_STATE_ACK_RCVD
mdefine_line|#define LCP_STATE_ACK_RCVD      1       /* LCP state: conf-ack received */
DECL|macro|LCP_STATE_ACK_SENT
mdefine_line|#define LCP_STATE_ACK_SENT      2       /* LCP state: conf-ack sent */
DECL|macro|LCP_STATE_OPENED
mdefine_line|#define LCP_STATE_OPENED        3       /* LCP state: opened */
DECL|macro|IPCP_STATE_CLOSED
mdefine_line|#define IPCP_STATE_CLOSED       0       /* IPCP state: closed (conf-req sent) */
DECL|macro|IPCP_STATE_ACK_RCVD
mdefine_line|#define IPCP_STATE_ACK_RCVD     1       /* IPCP state: conf-ack received */
DECL|macro|IPCP_STATE_ACK_SENT
mdefine_line|#define IPCP_STATE_ACK_SENT     2       /* IPCP state: conf-ack sent */
DECL|macro|IPCP_STATE_OPENED
mdefine_line|#define IPCP_STATE_OPENED       3       /* IPCP state: opened */
DECL|macro|SPPP_LINK_DOWN
mdefine_line|#define SPPP_LINK_DOWN&t;&t;0&t;/* link down - no keepalive */
DECL|macro|SPPP_LINK_UP
mdefine_line|#define SPPP_LINK_UP&t;&t;1&t;/* link is up - keepalive ok */
r_void
id|sppp_attach
(paren
r_struct
id|ppp_device
op_star
id|pd
)paren
suffix:semicolon
r_void
id|sppp_detach
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|sppp_input
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|sk_buff
op_star
id|m
)paren
suffix:semicolon
r_int
id|sppp_do_ioctl
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|ifr
comma
r_int
id|cmd
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|sppp_dequeue
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|sppp_isempty
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|sppp_flush
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|sppp_open
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|sppp_reopen
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|sppp_close
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|SPPPIOCCISCO
mdefine_line|#define SPPPIOCCISCO&t;(SIOCDEVPRIVATE)
DECL|macro|SPPPIOCPPP
mdefine_line|#define SPPPIOCPPP&t;(SIOCDEVPRIVATE+1)
DECL|macro|SPPPIOCDEBUG
mdefine_line|#define SPPPIOCDEBUG&t;(SIOCDEVPRIVATE+2)
macro_line|#endif /* _SYNCPPP_H_ */
eof
