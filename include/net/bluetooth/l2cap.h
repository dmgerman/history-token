multiline_comment|/* &n;   BlueZ - Bluetooth protocol stack for Linux&n;   Copyright (C) 2000-2001 Qualcomm Incorporated&n;&n;   Written 2000,2001 by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/*&n; *  $Id: l2cap.h,v 1.5 2001/06/14 21:28:26 maxk Exp $&n; */
macro_line|#ifndef __L2CAP_H
DECL|macro|__L2CAP_H
mdefine_line|#define __L2CAP_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/* L2CAP defaults */
DECL|macro|L2CAP_DEFAULT_MTU
mdefine_line|#define L2CAP_DEFAULT_MTU &t;672
DECL|macro|L2CAP_DEFAULT_FLUSH_TO
mdefine_line|#define L2CAP_DEFAULT_FLUSH_TO&t;0xFFFF
DECL|macro|L2CAP_CONN_TIMEOUT
mdefine_line|#define L2CAP_CONN_TIMEOUT &t;(HZ * 40)
DECL|macro|L2CAP_DISCONN_TIMEOUT
mdefine_line|#define L2CAP_DISCONN_TIMEOUT &t;(HZ * 2)
DECL|macro|L2CAP_CONN_IDLE_TIMEOUT
mdefine_line|#define L2CAP_CONN_IDLE_TIMEOUT&t;(HZ * 60)
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
multiline_comment|/* set/get sockopt defines */
DECL|macro|L2CAP_OPTIONS
mdefine_line|#define L2CAP_OPTIONS  0x01
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
DECL|member|token_rate
id|__u32
id|token_rate
suffix:semicolon
DECL|member|bucket_size
id|__u32
id|bucket_size
suffix:semicolon
DECL|member|pick_band
id|__u32
id|pick_band
suffix:semicolon
DECL|member|latency
id|__u32
id|latency
suffix:semicolon
DECL|member|delay_var
id|__u32
id|delay_var
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|L2CAP_CONNINFO
mdefine_line|#define L2CAP_CONNINFO  0x02
DECL|struct|l2cap_conninfo
r_struct
id|l2cap_conninfo
(brace
DECL|member|hci_handle
id|__u16
id|hci_handle
suffix:semicolon
)brace
suffix:semicolon
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
r_typedef
r_struct
(brace
DECL|member|len
id|__u16
id|len
suffix:semicolon
DECL|member|cid
id|__u16
id|cid
suffix:semicolon
DECL|typedef|l2cap_hdr
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|l2cap_hdr
suffix:semicolon
DECL|macro|L2CAP_HDR_SIZE
mdefine_line|#define L2CAP_HDR_SIZE&t;&t;4
r_typedef
r_struct
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
DECL|typedef|l2cap_cmd_hdr
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|l2cap_cmd_hdr
suffix:semicolon
DECL|macro|L2CAP_CMD_HDR_SIZE
mdefine_line|#define L2CAP_CMD_HDR_SIZE&t;4
r_typedef
r_struct
(brace
DECL|member|reason
id|__u16
id|reason
suffix:semicolon
DECL|typedef|l2cap_cmd_rej
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|l2cap_cmd_rej
suffix:semicolon
DECL|macro|L2CAP_CMD_REJ_SIZE
mdefine_line|#define L2CAP_CMD_REJ_SIZE&t;2
r_typedef
r_struct
(brace
DECL|member|psm
id|__u16
id|psm
suffix:semicolon
DECL|member|scid
id|__u16
id|scid
suffix:semicolon
DECL|typedef|l2cap_conn_req
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|l2cap_conn_req
suffix:semicolon
DECL|macro|L2CAP_CONN_REQ_SIZE
mdefine_line|#define L2CAP_CONN_REQ_SIZE&t;4
r_typedef
r_struct
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
DECL|typedef|l2cap_conn_rsp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|l2cap_conn_rsp
suffix:semicolon
DECL|macro|L2CAP_CONN_RSP_SIZE
mdefine_line|#define L2CAP_CONN_RSP_SIZE&t;8
DECL|macro|L2CAP_CONN_SUCCESS
mdefine_line|#define L2CAP_CONN_SUCCESS    0x0000
DECL|macro|L2CAP_CONN_PEND
mdefine_line|#define L2CAP_CONN_PEND       0x0001
DECL|macro|L2CAP_CONN_BAD_PSM
mdefine_line|#define L2CAP_CONN_BAD_PSM    0x0002
DECL|macro|L2CAP_CONN_SEC_BLOCK
mdefine_line|#define L2CAP_CONN_SEC_BLOCK  0x0003
DECL|macro|L2CAP_CONN_NO_MEM
mdefine_line|#define L2CAP_CONN_NO_MEM     0x0004
r_typedef
r_struct
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
DECL|typedef|l2cap_conf_req
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|l2cap_conf_req
suffix:semicolon
DECL|macro|L2CAP_CONF_REQ_SIZE
mdefine_line|#define L2CAP_CONF_REQ_SIZE&t;4
r_typedef
r_struct
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
DECL|typedef|l2cap_conf_rsp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|l2cap_conf_rsp
suffix:semicolon
DECL|macro|L2CAP_CONF_RSP_SIZE
mdefine_line|#define L2CAP_CONF_RSP_SIZE   &t;6
DECL|macro|L2CAP_CONF_SUCCESS
mdefine_line|#define L2CAP_CONF_SUCCESS&t;0x00
DECL|macro|L2CAP_CONF_UNACCEPT
mdefine_line|#define L2CAP_CONF_UNACCEPT&t;0x01
r_typedef
r_struct
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
DECL|typedef|l2cap_conf_opt
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|l2cap_conf_opt
suffix:semicolon
DECL|macro|L2CAP_CONF_OPT_SIZE
mdefine_line|#define L2CAP_CONF_OPT_SIZE&t;2
DECL|macro|L2CAP_CONF_MTU
mdefine_line|#define L2CAP_CONF_MTU&t;&t;0x01
DECL|macro|L2CAP_CONF_FLUSH_TO
mdefine_line|#define L2CAP_CONF_FLUSH_TO&t;0x02
DECL|macro|L2CAP_CONF_QOS
mdefine_line|#define L2CAP_CONF_QOS&t;&t;0x03
r_typedef
r_struct
(brace
DECL|member|dcid
id|__u16
id|dcid
suffix:semicolon
DECL|member|scid
id|__u16
id|scid
suffix:semicolon
DECL|typedef|l2cap_disconn_req
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|l2cap_disconn_req
suffix:semicolon
DECL|macro|L2CAP_DISCONN_REQ_SIZE
mdefine_line|#define L2CAP_DISCONN_REQ_SIZE&t;4
r_typedef
r_struct
(brace
DECL|member|dcid
id|__u16
id|dcid
suffix:semicolon
DECL|member|scid
id|__u16
id|scid
suffix:semicolon
DECL|typedef|l2cap_disconn_rsp
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|l2cap_disconn_rsp
suffix:semicolon
DECL|macro|L2CAP_DISCONN_RSP_SIZE
mdefine_line|#define L2CAP_DISCONN_RSP_SIZE&t;4
macro_line|#endif /* __L2CAP_H */
eof
