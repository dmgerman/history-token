macro_line|#ifndef LLC_H
DECL|macro|LLC_H
mdefine_line|#define LLC_H
multiline_comment|/*&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; * &t;&t; 2001-2003 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
r_struct
id|net_device
suffix:semicolon
r_struct
id|packet_type
suffix:semicolon
r_struct
id|sk_buff
suffix:semicolon
DECL|struct|llc_addr
r_struct
id|llc_addr
(brace
DECL|member|lsap
r_int
r_char
id|lsap
suffix:semicolon
DECL|member|mac
r_int
r_char
id|mac
(braket
id|IFHWADDRLEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LLC_SAP_STATE_INACTIVE
mdefine_line|#define LLC_SAP_STATE_INACTIVE&t;1
DECL|macro|LLC_SAP_STATE_ACTIVE
mdefine_line|#define LLC_SAP_STATE_ACTIVE&t;2
multiline_comment|/**&n; * struct llc_sap - Defines the SAP component&n; *&n; * @station - station this sap belongs to&n; * @state - sap state&n; * @p_bit - only lowest-order bit used&n; * @f_bit - only lowest-order bit used&n; * @laddr - SAP value in this &squot;lsap&squot;&n; * @node - entry in station sap_list&n; * @sk_list - LLC sockets this one manages&n; */
DECL|struct|llc_sap
r_struct
id|llc_sap
(brace
DECL|member|state
r_int
r_char
id|state
suffix:semicolon
DECL|member|p_bit
r_int
r_char
id|p_bit
suffix:semicolon
DECL|member|f_bit
r_int
r_char
id|f_bit
suffix:semicolon
DECL|member|rcv_func
r_int
(paren
op_star
id|rcv_func
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|packet_type
op_star
id|pt
)paren
suffix:semicolon
DECL|member|laddr
r_struct
id|llc_addr
id|laddr
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
r_struct
(brace
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|list
r_struct
id|hlist_head
id|list
suffix:semicolon
DECL|member|sk_list
)brace
id|sk_list
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|LLC_DEST_INVALID
mdefine_line|#define LLC_DEST_INVALID         0      /* Invalid LLC PDU type */
DECL|macro|LLC_DEST_SAP
mdefine_line|#define LLC_DEST_SAP             1      /* Type 1 goes here */
DECL|macro|LLC_DEST_CONN
mdefine_line|#define LLC_DEST_CONN            2      /* Type 2 goes here */
r_extern
r_struct
id|list_head
id|llc_sap_list
suffix:semicolon
r_extern
id|rwlock_t
id|llc_sap_list_lock
suffix:semicolon
r_extern
r_int
r_char
id|llc_station_mac_sa
(braket
id|ETH_ALEN
)braket
suffix:semicolon
r_extern
r_int
id|llc_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|packet_type
op_star
id|pt
)paren
suffix:semicolon
r_extern
r_int
id|llc_mac_hdr_init
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_char
op_star
id|sa
comma
r_int
r_char
op_star
id|da
)paren
suffix:semicolon
r_extern
r_void
id|llc_add_pack
c_func
(paren
r_int
id|type
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|llc_sap
op_star
id|sap
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
id|llc_remove_pack
c_func
(paren
r_int
id|type
)paren
suffix:semicolon
r_extern
r_void
id|llc_set_station_handler
c_func
(paren
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|llc_sap
op_star
id|llc_sap_open
c_func
(paren
r_int
r_char
id|lsap
comma
r_int
(paren
op_star
id|rcv
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|packet_type
op_star
id|pt
)paren
)paren
suffix:semicolon
r_extern
r_void
id|llc_sap_close
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
)paren
suffix:semicolon
r_extern
r_struct
id|llc_sap
op_star
id|llc_sap_find
c_func
(paren
r_int
r_char
id|sap_value
)paren
suffix:semicolon
r_extern
r_int
id|llc_build_and_send_ui_pkt
c_func
(paren
r_struct
id|llc_sap
op_star
id|sap
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
r_char
op_star
id|dmac
comma
r_int
r_char
id|dsap
)paren
suffix:semicolon
r_extern
r_int
id|llc_station_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|llc_station_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_extern
r_int
id|llc_proc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|llc_proc_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|macro|llc_proc_init
mdefine_line|#define llc_proc_init()&t;(0)
DECL|macro|llc_proc_exit
mdefine_line|#define llc_proc_exit()&t;do { } while(0)
macro_line|#endif /* CONFIG_PROC_FS */
macro_line|#endif /* LLC_H */
eof
