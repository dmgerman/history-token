macro_line|#ifndef _ATMSAR_H_
DECL|macro|_ATMSAR_H_
mdefine_line|#define _ATMSAR_H_
multiline_comment|/******************************************************************************&n; *  atmsar.h  --  General SAR library for ATM devices.&n; *&n; *  Copyright (C) 2000, Johan Verrept&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the Free&n; *  Software Foundation; either version 2 of the License, or (at your option)&n; *  any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but WITHOUT&n; *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for&n; *  more details.&n; *&n; *  You should have received a copy of the GNU General Public License along with&n; *  this program; if not, write to the Free Software Foundation, Inc., 59&n; *  Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; ******************************************************************************/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/atm.h&gt;
DECL|macro|ATMSAR_USE_53BYTE_CELL
mdefine_line|#define ATMSAR_USE_53BYTE_CELL  0x1L
DECL|macro|ATMSAR_SET_PTI
mdefine_line|#define ATMSAR_SET_PTI          0x2L
DECL|macro|ATM_CELL_HEADER
mdefine_line|#define ATM_CELL_HEADER&t;&t;(ATM_CELL_SIZE - ATM_CELL_PAYLOAD)
multiline_comment|/* types */
DECL|macro|ATMSAR_TYPE_AAL0
mdefine_line|#define ATMSAR_TYPE_AAL0        ATM_AAL0
DECL|macro|ATMSAR_TYPE_AAL1
mdefine_line|#define ATMSAR_TYPE_AAL1        ATM_AAL1
DECL|macro|ATMSAR_TYPE_AAL2
mdefine_line|#define ATMSAR_TYPE_AAL2        ATM_AAL2
DECL|macro|ATMSAR_TYPE_AAL34
mdefine_line|#define ATMSAR_TYPE_AAL34       ATM_AAL34
DECL|macro|ATMSAR_TYPE_AAL5
mdefine_line|#define ATMSAR_TYPE_AAL5        ATM_AAL5
multiline_comment|/* default MTU&squot;s */
DECL|macro|ATMSAR_DEF_MTU_AAL0
mdefine_line|#define ATMSAR_DEF_MTU_AAL0         48
DECL|macro|ATMSAR_DEF_MTU_AAL1
mdefine_line|#define ATMSAR_DEF_MTU_AAL1         47
DECL|macro|ATMSAR_DEF_MTU_AAL2
mdefine_line|#define ATMSAR_DEF_MTU_AAL2          0&t;/* not supported */
DECL|macro|ATMSAR_DEF_MTU_AAL34
mdefine_line|#define ATMSAR_DEF_MTU_AAL34         0&t;/* not supported */
DECL|macro|ATMSAR_DEF_MTU_AAL5
mdefine_line|#define ATMSAR_DEF_MTU_AAL5      65535&t;/* max mtu ..    */
DECL|struct|atmsar_vcc_data
r_struct
id|atmsar_vcc_data
(brace
DECL|member|next
r_struct
id|atmsar_vcc_data
op_star
id|next
suffix:semicolon
multiline_comment|/* general atmsar flags, per connection */
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* connection specific non-atmsar data */
DECL|member|alloc_tx
r_struct
id|sk_buff
op_star
(paren
op_star
id|alloc_tx
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|member|vcc
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
DECL|member|stats
r_struct
id|k_atm_aal_stats
op_star
id|stats
suffix:semicolon
DECL|member|mtu
r_int
r_int
id|mtu
suffix:semicolon
multiline_comment|/* max is actually  65k for AAL5... */
multiline_comment|/* cell data */
DECL|member|vp
r_int
r_int
id|vp
suffix:semicolon
DECL|member|vc
r_int
r_int
id|vc
suffix:semicolon
DECL|member|gfc
r_int
r_char
id|gfc
suffix:semicolon
DECL|member|pti
r_int
r_char
id|pti
suffix:semicolon
DECL|member|headerFlags
r_int
r_int
id|headerFlags
suffix:semicolon
DECL|member|atmHeader
r_int
r_int
id|atmHeader
suffix:semicolon
multiline_comment|/* raw cell reassembly */
DECL|member|reasBuffer
r_struct
id|sk_buff
op_star
id|reasBuffer
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|atmsar_vcc_data
op_star
id|atmsar_open
(paren
r_struct
id|atmsar_vcc_data
op_star
op_star
id|list
comma
r_struct
id|atm_vcc
op_star
id|vcc
comma
id|uint
id|type
comma
id|ushort
id|vpi
comma
id|ushort
id|vci
comma
id|unchar
id|pti
comma
id|unchar
id|gfc
comma
id|uint
id|flags
)paren
suffix:semicolon
r_extern
r_void
id|atmsar_close
(paren
r_struct
id|atmsar_vcc_data
op_star
op_star
id|list
comma
r_struct
id|atmsar_vcc_data
op_star
id|vcc
)paren
suffix:semicolon
r_extern
r_struct
id|sk_buff
op_star
id|atmsar_encode_rawcell
(paren
r_struct
id|atmsar_vcc_data
op_star
id|ctx
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
id|atmsar_encode_aal5
(paren
r_struct
id|atmsar_vcc_data
op_star
id|ctx
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|atmsar_decode_rawcell
(paren
r_struct
id|atmsar_vcc_data
op_star
id|list
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|atmsar_vcc_data
op_star
op_star
id|ctx
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|atmsar_decode_aal5
(paren
r_struct
id|atmsar_vcc_data
op_star
id|ctx
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_struct
id|sk_buff
op_star
id|atmsar_alloc_tx
(paren
r_struct
id|atmsar_vcc_data
op_star
id|vcc
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_int
r_int
id|atmsar_encode
(paren
r_struct
id|atmsar_vcc_data
op_star
id|ctx
comma
r_char
op_star
id|source
comma
r_char
op_star
id|target
comma
r_int
r_int
id|pdu_length
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ATMSAR_H_ */
eof
