macro_line|#ifndef _NET_DN_NSP_H
DECL|macro|_NET_DN_NSP_H
mdefine_line|#define _NET_DN_NSP_H
multiline_comment|/******************************************************************************&n;    (c) 1995-1998 E.M. Serrat&t;&t;emserrat@geocities.com&n;    &n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;*******************************************************************************/
multiline_comment|/* dn_nsp.c functions prototyping */
r_extern
r_void
id|dn_nsp_send_data_ack
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_void
id|dn_nsp_send_oth_ack
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_void
id|dn_nsp_delayed_ack
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_void
id|dn_send_conn_ack
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_void
id|dn_send_conn_conf
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|gfp
)paren
suffix:semicolon
r_extern
r_void
id|dn_nsp_send_disc
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
id|type
comma
r_int
r_int
id|reason
comma
r_int
id|gfp
)paren
suffix:semicolon
r_extern
r_void
id|dn_nsp_return_disc
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_char
id|type
comma
r_int
r_int
id|reason
)paren
suffix:semicolon
r_extern
r_void
id|dn_nsp_send_link
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
id|lsflags
comma
r_char
id|fcval
)paren
suffix:semicolon
r_extern
r_void
id|dn_nsp_send_conninit
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
r_char
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|dn_nsp_output
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
id|dn_nsp_check_xmit_queue
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|sk_buff_head
op_star
id|q
comma
r_int
r_int
id|acknum
)paren
suffix:semicolon
r_extern
r_void
id|dn_nsp_queue_xmit
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|gfp
comma
r_int
id|oob
)paren
suffix:semicolon
r_extern
r_int
r_int
id|dn_nsp_persist
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
id|dn_nsp_xmit_timeout
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
r_extern
r_int
id|dn_nsp_rx
c_func
(paren
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|dn_nsp_backlog_rcv
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|dn_alloc_skb
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
id|size
comma
r_int
id|pri
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|dn_alloc_send_skb
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_int
op_star
id|size
comma
r_int
id|noblock
comma
r_int
op_star
id|err
)paren
suffix:semicolon
DECL|macro|NSP_REASON_OK
mdefine_line|#define NSP_REASON_OK 0&t;&t;/* No error */
DECL|macro|NSP_REASON_NR
mdefine_line|#define NSP_REASON_NR 1&t;&t;/* No resources */
DECL|macro|NSP_REASON_UN
mdefine_line|#define NSP_REASON_UN 2&t;&t;/* Unrecognised node name */
DECL|macro|NSP_REASON_SD
mdefine_line|#define NSP_REASON_SD 3&t;&t;/* Node shutting down */
DECL|macro|NSP_REASON_ID
mdefine_line|#define NSP_REASON_ID 4&t;&t;/* Invalid destination end user */
DECL|macro|NSP_REASON_ER
mdefine_line|#define NSP_REASON_ER 5&t;&t;/* End user lacks resources */
DECL|macro|NSP_REASON_OB
mdefine_line|#define NSP_REASON_OB 6&t;&t;/* Object too busy */
DECL|macro|NSP_REASON_US
mdefine_line|#define NSP_REASON_US 7&t;&t;/* Unspecified error */
DECL|macro|NSP_REASON_TP
mdefine_line|#define NSP_REASON_TP 8&t;&t;/* Third-Party abort */
DECL|macro|NSP_REASON_EA
mdefine_line|#define NSP_REASON_EA 9&t;&t;/* End user has aborted the link */
DECL|macro|NSP_REASON_IF
mdefine_line|#define NSP_REASON_IF 10&t;/* Invalid node name format */
DECL|macro|NSP_REASON_LS
mdefine_line|#define NSP_REASON_LS 11&t;/* Local node shutdown */
DECL|macro|NSP_REASON_LL
mdefine_line|#define NSP_REASON_LL 32&t;/* Node lacks logical-link resources */
DECL|macro|NSP_REASON_LE
mdefine_line|#define NSP_REASON_LE 33&t;/* End user lacks logical-link resources */
DECL|macro|NSP_REASON_UR
mdefine_line|#define NSP_REASON_UR 34&t;/* Unacceptable RQSTRID or PASSWORD field */
DECL|macro|NSP_REASON_UA
mdefine_line|#define NSP_REASON_UA 36&t;/* Unacceptable ACCOUNT field */
DECL|macro|NSP_REASON_TM
mdefine_line|#define NSP_REASON_TM 38&t;/* End user timed out logical link */
DECL|macro|NSP_REASON_NU
mdefine_line|#define NSP_REASON_NU 39&t;/* Node unreachable */
DECL|macro|NSP_REASON_NL
mdefine_line|#define NSP_REASON_NL 41&t;/* No-link message */
DECL|macro|NSP_REASON_DC
mdefine_line|#define NSP_REASON_DC 42&t;/* Disconnect confirm */
DECL|macro|NSP_REASON_IO
mdefine_line|#define NSP_REASON_IO 43&t;/* Image data field overflow */
DECL|macro|NSP_DISCINIT
mdefine_line|#define NSP_DISCINIT 0x38
DECL|macro|NSP_DISCCONF
mdefine_line|#define NSP_DISCCONF 0x48
multiline_comment|/*------------------------- NSP - messages ------------------------------*/
multiline_comment|/* Data Messages */
multiline_comment|/*---------------*/
multiline_comment|/* Data Messages    (data segment/interrupt/link service)               */
DECL|struct|nsp_data_seg_msg
r_struct
id|nsp_data_seg_msg
(brace
DECL|member|msgflg
r_int
r_char
id|msgflg
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|dstaddr
r_int
r_int
id|dstaddr
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|srcaddr
r_int
r_int
id|srcaddr
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nsp_data_opt_msg
r_struct
id|nsp_data_opt_msg
(brace
DECL|member|acknum
r_int
r_int
id|acknum
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|segnum
r_int
r_int
id|segnum
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|lsflgs
r_int
r_int
id|lsflgs
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nsp_data_opt_msg1
r_struct
id|nsp_data_opt_msg1
(brace
DECL|member|acknum
r_int
r_int
id|acknum
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|segnum
r_int
r_int
id|segnum
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Acknowledgment Message (data/other data)                             */
DECL|struct|nsp_data_ack_msg
r_struct
id|nsp_data_ack_msg
(brace
DECL|member|msgflg
r_int
r_char
id|msgflg
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|dstaddr
r_int
r_int
id|dstaddr
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|srcaddr
r_int
r_int
id|srcaddr
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|acknum
r_int
r_int
id|acknum
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Connect Acknowledgment Message */
DECL|struct|nsp_conn_ack_msg
r_struct
id|nsp_conn_ack_msg
(brace
DECL|member|msgflg
r_int
r_char
id|msgflg
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|dstaddr
r_int
r_int
id|dstaddr
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Connect Initiate/Retransmit Initiate/Connect Confirm */
DECL|struct|nsp_conn_init_msg
r_struct
id|nsp_conn_init_msg
(brace
DECL|member|msgflg
r_int
r_char
id|msgflg
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|NSP_CI
mdefine_line|#define NSP_CI      0x18            /* Connect Initiate     */
DECL|macro|NSP_RCI
mdefine_line|#define NSP_RCI     0x68            /* Retrans. Conn Init   */
DECL|member|dstaddr
r_int
r_int
id|dstaddr
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|srcaddr
r_int
r_int
id|srcaddr
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|services
r_int
r_char
id|services
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|NSP_FC_NONE
mdefine_line|#define NSP_FC_NONE   0x00            /* Flow Control None    */
DECL|macro|NSP_FC_SRC
mdefine_line|#define NSP_FC_SRC    0x04            /* Seg Req. Count       */
DECL|macro|NSP_FC_SCMC
mdefine_line|#define NSP_FC_SCMC   0x08            /* Sess. Control Mess   */
DECL|macro|NSP_FC_MASK
mdefine_line|#define NSP_FC_MASK   0x0c            /* FC type mask         */
DECL|member|info
r_int
r_char
id|info
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|segsize
r_int
r_int
id|segsize
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Disconnect Initiate/Disconnect Confirm */
DECL|struct|nsp_disconn_init_msg
r_struct
id|nsp_disconn_init_msg
(brace
DECL|member|msgflg
r_int
r_char
id|msgflg
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|dstaddr
r_int
r_int
id|dstaddr
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|srcaddr
r_int
r_int
id|srcaddr
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|reason
r_int
r_int
id|reason
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|srcobj_fmt
r_struct
id|srcobj_fmt
(brace
DECL|member|format
r_char
id|format
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|task
r_int
r_char
id|task
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|grpcode
r_int
r_int
id|grpcode
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|usrcode
r_int
r_int
id|usrcode
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|dlen
r_char
id|dlen
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * A collection of functions for manipulating the sequence&n; * numbers used in NSP. Similar in operation to the functions&n; * of the same name in TCP.&n; */
DECL|function|dn_before
r_static
id|__inline__
r_int
id|dn_before
c_func
(paren
r_int
r_int
id|seq1
comma
r_int
r_int
id|seq2
)paren
(brace
id|seq1
op_and_assign
l_int|0x0fff
suffix:semicolon
id|seq2
op_and_assign
l_int|0x0fff
suffix:semicolon
r_return
(paren
r_int
)paren
(paren
(paren
id|seq1
op_minus
id|seq2
)paren
op_amp
l_int|0x0fff
)paren
OG
l_int|2048
suffix:semicolon
)brace
DECL|function|dn_after
r_static
id|__inline__
r_int
id|dn_after
c_func
(paren
r_int
r_int
id|seq1
comma
r_int
r_int
id|seq2
)paren
(brace
id|seq1
op_and_assign
l_int|0x0fff
suffix:semicolon
id|seq2
op_and_assign
l_int|0x0fff
suffix:semicolon
r_return
(paren
r_int
)paren
(paren
(paren
id|seq2
op_minus
id|seq1
)paren
op_amp
l_int|0x0fff
)paren
OG
l_int|2048
suffix:semicolon
)brace
DECL|function|dn_equal
r_static
id|__inline__
r_int
id|dn_equal
c_func
(paren
r_int
r_int
id|seq1
comma
r_int
r_int
id|seq2
)paren
(brace
r_return
(paren
(paren
id|seq1
op_xor
id|seq2
)paren
op_amp
l_int|0x0fff
)paren
op_eq
l_int|0
suffix:semicolon
)brace
DECL|function|dn_before_or_equal
r_static
id|__inline__
r_int
id|dn_before_or_equal
c_func
(paren
r_int
r_int
id|seq1
comma
r_int
r_int
id|seq2
)paren
(brace
r_return
(paren
id|dn_before
c_func
(paren
id|seq1
comma
id|seq2
)paren
op_logical_or
id|dn_equal
c_func
(paren
id|seq1
comma
id|seq2
)paren
)paren
suffix:semicolon
)brace
DECL|function|seq_add
r_static
id|__inline__
r_void
id|seq_add
c_func
(paren
r_int
r_int
op_star
id|seq
comma
r_int
r_int
id|off
)paren
(brace
(paren
op_star
id|seq
)paren
op_add_assign
id|off
suffix:semicolon
(paren
op_star
id|seq
)paren
op_and_assign
l_int|0x0fff
suffix:semicolon
)brace
DECL|function|seq_next
r_static
id|__inline__
r_int
id|seq_next
c_func
(paren
r_int
r_int
id|seq1
comma
r_int
r_int
id|seq2
)paren
(brace
r_return
id|dn_equal
c_func
(paren
id|seq1
op_plus
l_int|1
comma
id|seq2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Can we delay the ack ?&n; */
DECL|function|sendack
r_static
id|__inline__
r_int
id|sendack
c_func
(paren
r_int
r_int
id|seq
)paren
(brace
r_return
(paren
r_int
)paren
(paren
(paren
id|seq
op_amp
l_int|0x1000
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Is socket congested ?&n; */
DECL|function|dn_congested
r_static
id|__inline__
r_int
id|dn_congested
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_return
id|atomic_read
c_func
(paren
op_amp
id|sk-&gt;sk_rmem_alloc
)paren
OG
(paren
id|sk-&gt;sk_rcvbuf
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
DECL|macro|DN_MAX_NSP_DATA_HEADER
mdefine_line|#define DN_MAX_NSP_DATA_HEADER (11)
macro_line|#endif /* _NET_DN_NSP_H */
eof
