macro_line|#ifndef LLC_MAC_H
DECL|macro|LLC_MAC_H
mdefine_line|#define LLC_MAC_H
multiline_comment|/*&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; * &t;&t; 2001-2003 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
DECL|macro|LLC_DEST_INVALID
mdefine_line|#define LLC_DEST_INVALID         0      /* Invalid LLC PDU type */
DECL|macro|LLC_DEST_SAP
mdefine_line|#define LLC_DEST_SAP             1      /* Type 1 goes here */
DECL|macro|LLC_DEST_CONN
mdefine_line|#define LLC_DEST_CONN            2      /* Type 2 goes here */
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
r_struct
id|llc_sap
suffix:semicolon
r_struct
id|sk_buff
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
macro_line|#endif /* LLC_MAC_H */
eof
