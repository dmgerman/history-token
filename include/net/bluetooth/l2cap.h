multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
macro_line|#ifndef __L2CAP_H
DECL|macro|__L2CAP_H
mdefine_line|#define __L2CAP_H
multiline_comment|/* L2CAP defaults */
DECL|macro|L2CAP_DEFAULT_MTU
mdefine_line|#define L2CAP_DEFAULT_MTU&t;672
DECL|macro|L2CAP_DEFAULT_FLUSH_TO
mdefine_line|#define L2CAP_DEFAULT_FLUSH_TO&t;0xFFFF
DECL|macro|L2CAP_CONN_TIMEOUT
mdefine_line|#define L2CAP_CONN_TIMEOUT&t;(HZ * 40)
multiline_comment|/* L2CAP socket address */
DECL|struct|sockaddr_l2
r_struct
id|sockaddr_l2
(brace
DECL|member|l2_family
id|sa_family_t
id|l2_family
suffix:semicolon
DECL|member|l2_psm
r_int
r_int
id|l2_psm
suffix:semicolon
DECL|member|l2_bdaddr
id|bdaddr_t
id|l2_bdaddr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* L2CAP socket options */
DECL|macro|L2CAP_OPTIONS
mdefine_line|#define L2CAP_OPTIONS&t;0x01
DECL|struct|l2cap_options
r_struct
id|l2cap_options
(brace
DECL|member|omtu
id|__u16
id|omtu
suffix:semicolon
DECL|member|imtu
id|__u16
id|imtu
suffix:semicolon
DECL|member|flush_to
id|__u16
id|flush_to
suffix:semicolon
DECL|member|mode
id|__u8
id|mode
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|L2CAP_CONNINFO
mdefine_line|#define L2CAP_CONNINFO&t;0x02
DECL|struct|l2cap_conninfo
r_struct
id|l2cap_conninfo
(brace
DECL|member|hci_handle
id|__u16
id|hci_handle
suffix:semicolon
DECL|member|dev_class
id|__u8
id|dev_class
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|L2CAP_LM
mdefine_line|#define L2CAP_LM&t;0x03
DECL|macro|L2CAP_LM_MASTER
mdefine_line|#define L2CAP_LM_MASTER&t;&t;0x0001
DECL|macro|L2CAP_LM_AUTH
mdefine_line|#define L2CAP_LM_AUTH&t;&t;0x0002
DECL|macro|L2CAP_LM_ENCRYPT
mdefine_line|#define L2CAP_LM_ENCRYPT&t;0x0004
DECL|macro|L2CAP_LM_TRUSTED
mdefine_line|#define L2CAP_LM_TRUSTED&t;0x0008
DECL|macro|L2CAP_LM_RELIABLE
mdefine_line|#define L2CAP_LM_RELIABLE&t;0x0010
DECL|macro|L2CAP_LM_SECURE
mdefine_line|#define L2CAP_LM_SECURE&t;&t;0x0020
multiline_comment|/* L2CAP command codes */
DECL|macro|L2CAP_COMMAND_REJ
mdefine_line|#define L2CAP_COMMAND_REJ 0x01
DECL|macro|L2CAP_CONN_REQ
mdefine_line|#define L2CAP_CONN_REQ    0x02
DECL|macro|L2CAP_CONN_RSP
mdefine_line|#define L2CAP_CONN_RSP    0x03
DECL|macro|L2CAP_CONF_REQ
mdefine_line|#define L2CAP_CONF_REQ    0x04
DECL|macro|L2CAP_CONF_RSP
mdefine_line|#define L2CAP_CONF_RSP    0x05
DECL|macro|L2CAP_DISCONN_REQ
mdefine_line|#define L2CAP_DISCONN_REQ 0x06
DECL|macro|L2CAP_DISCONN_RSP
mdefine_line|#define L2CAP_DISCONN_RSP 0x07
DECL|macro|L2CAP_ECHO_REQ
mdefine_line|#define L2CAP_ECHO_REQ    0x08
DECL|macro|L2CAP_ECHO_RSP
mdefine_line|#define L2CAP_ECHO_RSP    0x09
DECL|macro|L2CAP_INFO_REQ
mdefine_line|#define L2CAP_INFO_REQ    0x0a
DECL|macro|L2CAP_INFO_RSP
mdefine_line|#define L2CAP_INFO_RSP    0x0b
multiline_comment|/* L2CAP structures */
DECL|struct|l2cap_hdr
r_struct
id|l2cap_hdr
(brace
DECL|member|len
id|__u16
id|len
suffix:semicolon
DECL|member|cid
id|__u16
id|cid
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|L2CAP_HDR_SIZE
mdefine_line|#define L2CAP_HDR_SIZE&t;&t;4
DECL|struct|l2cap_cmd_hdr
r_struct
id|l2cap_cmd_hdr
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
DECL|member|ident
id|__u8
id|ident
suffix:semicolon
DECL|member|len
id|__u16
id|len
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|L2CAP_CMD_HDR_SIZE
mdefine_line|#define L2CAP_CMD_HDR_SIZE&t;4
DECL|struct|l2cap_cmd_rej
r_struct
id|l2cap_cmd_rej
(brace
DECL|member|reason
id|__u16
id|reason
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|l2cap_conn_req
r_struct
id|l2cap_conn_req
(brace
DECL|member|psm
id|__u16
id|psm
suffix:semicolon
DECL|member|scid
id|__u16
id|scid
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|l2cap_conn_rsp
r_struct
id|l2cap_conn_rsp
(brace
DECL|member|dcid
id|__u16
id|dcid
suffix:semicolon
DECL|member|scid
id|__u16
id|scid
suffix:semicolon
DECL|member|result
id|__u16
id|result
suffix:semicolon
DECL|member|status
id|__u16
id|status
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* connect result */
DECL|macro|L2CAP_CR_SUCCESS
mdefine_line|#define L2CAP_CR_SUCCESS    0x0000
DECL|macro|L2CAP_CR_PEND
mdefine_line|#define L2CAP_CR_PEND       0x0001
DECL|macro|L2CAP_CR_BAD_PSM
mdefine_line|#define L2CAP_CR_BAD_PSM    0x0002
DECL|macro|L2CAP_CR_SEC_BLOCK
mdefine_line|#define L2CAP_CR_SEC_BLOCK  0x0003
DECL|macro|L2CAP_CR_NO_MEM
mdefine_line|#define L2CAP_CR_NO_MEM     0x0004
multiline_comment|/* connect status */
DECL|macro|L2CAP_CS_NO_INFO
mdefine_line|#define L2CAP_CS_NO_INFO      0x0000
DECL|macro|L2CAP_CS_AUTHEN_PEND
mdefine_line|#define L2CAP_CS_AUTHEN_PEND  0x0001
DECL|macro|L2CAP_CS_AUTHOR_PEND
mdefine_line|#define L2CAP_CS_AUTHOR_PEND  0x0002
DECL|struct|l2cap_conf_req
r_struct
id|l2cap_conf_req
(brace
DECL|member|dcid
id|__u16
id|dcid
suffix:semicolon
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
DECL|member|data
id|__u8
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|l2cap_conf_rsp
r_struct
id|l2cap_conf_rsp
(brace
DECL|member|scid
id|__u16
id|scid
suffix:semicolon
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
DECL|member|result
id|__u16
id|result
suffix:semicolon
DECL|member|data
id|__u8
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|L2CAP_CONF_SUCCESS
mdefine_line|#define L2CAP_CONF_SUCCESS&t;0x00
DECL|macro|L2CAP_CONF_UNACCEPT
mdefine_line|#define L2CAP_CONF_UNACCEPT&t;0x01
DECL|struct|l2cap_conf_opt
r_struct
id|l2cap_conf_opt
(brace
DECL|member|type
id|__u8
id|type
suffix:semicolon
DECL|member|len
id|__u8
id|len
suffix:semicolon
DECL|member|val
id|__u8
id|val
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|macro|L2CAP_CONF_OPT_SIZE
mdefine_line|#define L2CAP_CONF_OPT_SIZE&t;2
DECL|macro|L2CAP_CONF_MTU
mdefine_line|#define L2CAP_CONF_MTU&t;&t;0x01
DECL|macro|L2CAP_CONF_FLUSH_TO
mdefine_line|#define L2CAP_CONF_FLUSH_TO&t;0x02
DECL|macro|L2CAP_CONF_QOS
mdefine_line|#define L2CAP_CONF_QOS&t;&t;0x03
DECL|macro|L2CAP_CONF_RFC
mdefine_line|#define L2CAP_CONF_RFC&t;&t;0x04
DECL|macro|L2CAP_CONF_MAX_SIZE
mdefine_line|#define L2CAP_CONF_MAX_SIZE&t;22
DECL|struct|l2cap_disconn_req
r_struct
id|l2cap_disconn_req
(brace
DECL|member|dcid
id|__u16
id|dcid
suffix:semicolon
DECL|member|scid
id|__u16
id|scid
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|l2cap_disconn_rsp
r_struct
id|l2cap_disconn_rsp
(brace
DECL|member|dcid
id|__u16
id|dcid
suffix:semicolon
DECL|member|scid
id|__u16
id|scid
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|l2cap_info_req
r_struct
id|l2cap_info_req
(brace
DECL|member|type
id|__u16
id|type
suffix:semicolon
DECL|member|data
id|__u8
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|l2cap_info_rsp
r_struct
id|l2cap_info_rsp
(brace
DECL|member|type
id|__u16
id|type
suffix:semicolon
DECL|member|result
id|__u16
id|result
suffix:semicolon
DECL|member|data
id|__u8
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* info type */
DECL|macro|L2CAP_IT_CL_MTU
mdefine_line|#define L2CAP_IT_CL_MTU     0x0001
DECL|macro|L2CAP_IT_FEAT_MASK
mdefine_line|#define L2CAP_IT_FEAT_MASK  0x0002
multiline_comment|/* info result */
DECL|macro|L2CAP_IR_SUCCESS
mdefine_line|#define L2CAP_IR_SUCCESS    0x0000
DECL|macro|L2CAP_IR_NOTSUPP
mdefine_line|#define L2CAP_IR_NOTSUPP    0x0001
multiline_comment|/* ----- L2CAP connections ----- */
DECL|struct|l2cap_chan_list
r_struct
id|l2cap_chan_list
(brace
DECL|member|head
r_struct
id|sock
op_star
id|head
suffix:semicolon
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|num
r_int
id|num
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|l2cap_conn
r_struct
id|l2cap_conn
(brace
DECL|member|hcon
r_struct
id|hci_conn
op_star
id|hcon
suffix:semicolon
DECL|member|dst
id|bdaddr_t
op_star
id|dst
suffix:semicolon
DECL|member|src
id|bdaddr_t
op_star
id|src
suffix:semicolon
DECL|member|mtu
r_int
r_int
id|mtu
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|rx_skb
r_struct
id|sk_buff
op_star
id|rx_skb
suffix:semicolon
DECL|member|rx_len
id|__u32
id|rx_len
suffix:semicolon
DECL|member|rx_ident
id|__u8
id|rx_ident
suffix:semicolon
DECL|member|tx_ident
id|__u8
id|tx_ident
suffix:semicolon
DECL|member|chan_list
r_struct
id|l2cap_chan_list
id|chan_list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ----- L2CAP channel and socket info ----- */
DECL|macro|l2cap_pi
mdefine_line|#define l2cap_pi(sk) ((struct l2cap_pinfo *) sk)
DECL|struct|l2cap_pinfo
r_struct
id|l2cap_pinfo
(brace
DECL|member|bt
r_struct
id|bt_sock
id|bt
suffix:semicolon
DECL|member|psm
id|__u16
id|psm
suffix:semicolon
DECL|member|dcid
id|__u16
id|dcid
suffix:semicolon
DECL|member|scid
id|__u16
id|scid
suffix:semicolon
DECL|member|imtu
id|__u16
id|imtu
suffix:semicolon
DECL|member|omtu
id|__u16
id|omtu
suffix:semicolon
DECL|member|flush_to
id|__u16
id|flush_to
suffix:semicolon
DECL|member|link_mode
id|__u32
id|link_mode
suffix:semicolon
DECL|member|conf_state
id|__u8
id|conf_state
suffix:semicolon
DECL|member|conf_retry
id|__u8
id|conf_retry
suffix:semicolon
DECL|member|conf_mtu
id|__u16
id|conf_mtu
suffix:semicolon
DECL|member|ident
id|__u8
id|ident
suffix:semicolon
DECL|member|sport
id|__u16
id|sport
suffix:semicolon
DECL|member|conn
r_struct
id|l2cap_conn
op_star
id|conn
suffix:semicolon
DECL|member|next_c
r_struct
id|sock
op_star
id|next_c
suffix:semicolon
DECL|member|prev_c
r_struct
id|sock
op_star
id|prev_c
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|L2CAP_CONF_REQ_SENT
mdefine_line|#define L2CAP_CONF_REQ_SENT    0x01
DECL|macro|L2CAP_CONF_INPUT_DONE
mdefine_line|#define L2CAP_CONF_INPUT_DONE  0x02
DECL|macro|L2CAP_CONF_OUTPUT_DONE
mdefine_line|#define L2CAP_CONF_OUTPUT_DONE 0x04
DECL|macro|L2CAP_CONF_MAX_RETRIES
mdefine_line|#define L2CAP_CONF_MAX_RETRIES 2
r_void
id|l2cap_load
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __L2CAP_H */
eof
