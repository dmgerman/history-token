macro_line|#ifndef __LINUX_LLC_H
DECL|macro|__LINUX_LLC_H
mdefine_line|#define __LINUX_LLC_H
multiline_comment|/*&n; * IEEE 802.2 User Interface SAPs for Linux, data structures and indicators.&n; *&n; * Copyright (c) 2001 by Jay Schulist &lt;jschlst@samba.org&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
DECL|macro|__LLC_SOCK_SIZE__
mdefine_line|#define __LLC_SOCK_SIZE__ 28&t;/* sizeof(sockaddr_llc), word align. */
DECL|struct|sockaddr_llc
r_struct
id|sockaddr_llc
(brace
DECL|member|sllc_family
id|sa_family_t
id|sllc_family
suffix:semicolon
multiline_comment|/* AF_LLC */
DECL|member|sllc_arphrd
id|sa_family_t
id|sllc_arphrd
suffix:semicolon
multiline_comment|/* ARPHRD_ETHER */
DECL|member|sllc_test
r_int
r_char
id|sllc_test
suffix:semicolon
DECL|member|sllc_xid
r_int
r_char
id|sllc_xid
suffix:semicolon
DECL|member|sllc_ua
r_int
r_char
id|sllc_ua
suffix:semicolon
multiline_comment|/* UA data, only for SOCK_STREAM. */
DECL|member|sllc_dsap
r_int
r_char
id|sllc_dsap
suffix:semicolon
DECL|member|sllc_ssap
r_int
r_char
id|sllc_ssap
suffix:semicolon
DECL|member|sllc_dmac
r_int
r_char
id|sllc_dmac
(braket
id|IFHWADDRLEN
)braket
suffix:semicolon
DECL|member|sllc_smac
r_int
r_char
id|sllc_smac
(braket
id|IFHWADDRLEN
)braket
suffix:semicolon
DECL|member|sllc_mmac
r_int
r_char
id|sllc_mmac
(braket
id|IFHWADDRLEN
)braket
suffix:semicolon
DECL|member|__pad
r_int
r_char
id|__pad
(braket
id|__LLC_SOCK_SIZE__
op_minus
r_sizeof
(paren
id|sa_family_t
)paren
op_star
l_int|2
op_minus
r_sizeof
(paren
r_int
r_char
)paren
op_star
l_int|5
op_minus
id|IFHWADDRLEN
op_star
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* sockopt definitions. */
DECL|enum|llc_sockopts
r_enum
id|llc_sockopts
(brace
DECL|enumerator|LLC_OPT_UNKNOWN
id|LLC_OPT_UNKNOWN
op_assign
l_int|0
comma
DECL|enumerator|LLC_OPT_RETRY
id|LLC_OPT_RETRY
comma
multiline_comment|/* max retrans attempts. */
DECL|enumerator|LLC_OPT_SIZE
id|LLC_OPT_SIZE
comma
multiline_comment|/* max PDU size (octets). */
DECL|enumerator|LLC_OPT_ACK_TMR_EXP
id|LLC_OPT_ACK_TMR_EXP
comma
multiline_comment|/* ack expire time (secs). */
DECL|enumerator|LLC_OPT_P_TMR_EXP
id|LLC_OPT_P_TMR_EXP
comma
multiline_comment|/* pf cycle expire time (secs). */
DECL|enumerator|LLC_OPT_REJ_TMR_EXP
id|LLC_OPT_REJ_TMR_EXP
comma
multiline_comment|/* rej sent expire time (secs). */
DECL|enumerator|LLC_OPT_BUSY_TMR_EXP
id|LLC_OPT_BUSY_TMR_EXP
comma
multiline_comment|/* busy state expire time (secs). */
DECL|enumerator|LLC_OPT_TX_WIN
id|LLC_OPT_TX_WIN
comma
multiline_comment|/* tx window size. */
DECL|enumerator|LLC_OPT_RX_WIN
id|LLC_OPT_RX_WIN
comma
multiline_comment|/* rx window size. */
DECL|enumerator|LLC_OPT_MAX
id|LLC_OPT_MAX
)brace
suffix:semicolon
DECL|macro|LLC_OPT_MAX_RETRY
mdefine_line|#define LLC_OPT_MAX_RETRY&t; 100
DECL|macro|LLC_OPT_MAX_SIZE
mdefine_line|#define LLC_OPT_MAX_SIZE&t;4196
DECL|macro|LLC_OPT_MAX_WIN
mdefine_line|#define LLC_OPT_MAX_WIN&t;&t; 127
DECL|macro|LLC_OPT_MAX_ACK_TMR_EXP
mdefine_line|#define LLC_OPT_MAX_ACK_TMR_EXP&t;  60
DECL|macro|LLC_OPT_MAX_P_TMR_EXP
mdefine_line|#define LLC_OPT_MAX_P_TMR_EXP&t;  60
DECL|macro|LLC_OPT_MAX_REJ_TMR_EXP
mdefine_line|#define LLC_OPT_MAX_REJ_TMR_EXP&t;  60
DECL|macro|LLC_OPT_MAX_BUSY_TMR_EXP
mdefine_line|#define LLC_OPT_MAX_BUSY_TMR_EXP  60
multiline_comment|/* LLC SAP types. */
DECL|macro|LLC_SAP_NULL
mdefine_line|#define LLC_SAP_NULL&t;0x00&t;&t;/* NULL SAP. &t;&t;&t;*/
DECL|macro|LLC_SAP_LLC
mdefine_line|#define LLC_SAP_LLC&t;0x02&t;&t;/* LLC Sublayer Managment. &t;*/
DECL|macro|LLC_SAP_SNA
mdefine_line|#define LLC_SAP_SNA&t;0x04&t;&t;/* SNA Path Control. &t;&t;*/
DECL|macro|LLC_SAP_PNM
mdefine_line|#define LLC_SAP_PNM&t;0x0E&t;&t;/* Proway Network Managment.&t;*/&t;
DECL|macro|LLC_SAP_IP
mdefine_line|#define LLC_SAP_IP&t;0x06&t;&t;/* TCP/IP. &t;&t;&t;*/
DECL|macro|LLC_SAP_BSPAN
mdefine_line|#define LLC_SAP_BSPAN&t;0x42&t;&t;/* Bridge Spanning Tree Proto&t;*/
DECL|macro|LLC_SAP_MMS
mdefine_line|#define LLC_SAP_MMS&t;0x4E&t;&t;/* Manufacturing Message Srv.&t;*/
DECL|macro|LLC_SAP_8208
mdefine_line|#define LLC_SAP_8208&t;0x7E&t;&t;/* ISO 8208&t;&t;&t;*/
DECL|macro|LLC_SAP_3COM
mdefine_line|#define LLC_SAP_3COM&t;0x80&t;&t;/* 3COM. &t;&t;&t;*/
DECL|macro|LLC_SAP_PRO
mdefine_line|#define LLC_SAP_PRO&t;0x8E&t;&t;/* Proway Active Station List&t;*/
DECL|macro|LLC_SAP_SNAP
mdefine_line|#define LLC_SAP_SNAP&t;0xAA&t;&t;/* SNAP. &t;&t;&t;*/
DECL|macro|LLC_SAP_BANYAN
mdefine_line|#define LLC_SAP_BANYAN&t;0xBC&t;&t;/* Banyan. &t;&t;&t;*/
DECL|macro|LLC_SAP_IPX
mdefine_line|#define LLC_SAP_IPX&t;0xE0&t;&t;/* IPX/SPX. &t;&t;&t;*/
DECL|macro|LLC_SAP_NETBEUI
mdefine_line|#define LLC_SAP_NETBEUI&t;0xF0&t;&t;/* NetBEUI. &t;&t;&t;*/
DECL|macro|LLC_SAP_LANMGR
mdefine_line|#define LLC_SAP_LANMGR&t;0xF4&t;&t;/* LanManager. &t;&t;&t;*/
DECL|macro|LLC_SAP_IMPL
mdefine_line|#define LLC_SAP_IMPL&t;0xF8&t;&t;/* IMPL&t;&t;&t;&t;*/
DECL|macro|LLC_SAP_DISC
mdefine_line|#define LLC_SAP_DISC&t;0xFC&t;&t;/* Discovery&t;&t;&t;*/
DECL|macro|LLC_SAP_OSI
mdefine_line|#define LLC_SAP_OSI&t;0xFE&t;&t;/* OSI Network Layers. &t;&t;*/
DECL|macro|LLC_SAP_LAR
mdefine_line|#define LLC_SAP_LAR&t;0xDC&t;&t;/* LAN Address Resolution &t;*/
DECL|macro|LLC_SAP_RM
mdefine_line|#define LLC_SAP_RM&t;0xD4&t;&t;/* Resource Management &t;&t;*/
DECL|macro|LLC_SAP_GLOBAL
mdefine_line|#define LLC_SAP_GLOBAL&t;0xFF&t;&t;/* Global SAP. &t;&t;&t;*/
macro_line|#ifdef __KERNEL__
DECL|macro|LLC_SAP_DYN_START
mdefine_line|#define LLC_SAP_DYN_START&t;0xC0
DECL|macro|LLC_SAP_DYN_STOP
mdefine_line|#define LLC_SAP_DYN_STOP&t;0xDE
DECL|macro|LLC_SAP_DYN_TRIES
mdefine_line|#define LLC_SAP_DYN_TRIES&t;4
r_struct
id|sock
suffix:semicolon
DECL|struct|llc_ui_opt
r_struct
id|llc_ui_opt
(brace
DECL|member|link
id|u16
id|link
suffix:semicolon
multiline_comment|/* network layer link number */
DECL|member|sap
r_struct
id|llc_sap
op_star
id|sap
suffix:semicolon
multiline_comment|/* pointer to parent SAP */
DECL|member|core_sk
r_struct
id|sock
op_star
id|core_sk
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* device to send to remote */
DECL|member|addr
r_struct
id|sockaddr_llc
id|addr
suffix:semicolon
multiline_comment|/* address sock is bound to */
)brace
suffix:semicolon
DECL|macro|llc_ui_sk
mdefine_line|#define llc_ui_sk(__sk) ((struct llc_ui_opt *)(__sk)-&gt;protinfo)
DECL|macro|llc_ui_skb_cb
mdefine_line|#define llc_ui_skb_cb(__skb) ((struct sockaddr_llc *)&amp;((__skb)-&gt;cb[0]))
macro_line|#ifdef CONFIG_LLC_UI
r_extern
r_int
id|llc_ui_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|llc_ui_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|macro|llc_ui_init
mdefine_line|#define llc_ui_init()
DECL|macro|llc_ui_exit
mdefine_line|#define llc_ui_exit()
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __LINUX_LLC_H */
eof
