macro_line|#ifndef LLC_PDU_H
DECL|macro|LLC_PDU_H
mdefine_line|#define LLC_PDU_H
multiline_comment|/*&n; * Copyright (c) 1997 by Procom Technology,Inc.&n; * &t;&t; 2001 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
multiline_comment|/* LLC PDU structure */
multiline_comment|/* Lengths of frame formats */
DECL|macro|LLC_PDU_LEN_I
mdefine_line|#define LLC_PDU_LEN_I&t;4       /* header and 2 control bytes */
DECL|macro|LLC_PDU_LEN_S
mdefine_line|#define LLC_PDU_LEN_S&t;4
DECL|macro|LLC_PDU_LEN_U
mdefine_line|#define LLC_PDU_LEN_U&t;3       /* header and 1 control byte */
multiline_comment|/* Known SAP addresses */
DECL|macro|LLC_GLOBAL_SAP
mdefine_line|#define LLC_GLOBAL_SAP&t;0xFF
DECL|macro|LLC_NULL_SAP
mdefine_line|#define LLC_NULL_SAP&t;0x00&t;/* not network-layer visible */
DECL|macro|LLC_MGMT_INDIV
mdefine_line|#define LLC_MGMT_INDIV&t;0x02&t;/* station LLC mgmt indiv addr */
DECL|macro|LLC_MGMT_GRP
mdefine_line|#define LLC_MGMT_GRP&t;0x03&t;/* station LLC mgmt group addr */
DECL|macro|LLC_RDE_SAP
mdefine_line|#define LLC_RDE_SAP&t;0xA6&t;/* route ... */
multiline_comment|/* SAP field bit masks */
DECL|macro|LLC_ISO_RESERVED_SAP
mdefine_line|#define LLC_ISO_RESERVED_SAP&t;0x02
DECL|macro|LLC_SAP_GROUP_DSAP
mdefine_line|#define LLC_SAP_GROUP_DSAP&t;0x01
DECL|macro|LLC_SAP_RESP_SSAP
mdefine_line|#define LLC_SAP_RESP_SSAP&t;0x01
multiline_comment|/* Group/individual DSAP indicator is DSAP field */
DECL|macro|LLC_PDU_GROUP_DSAP_MASK
mdefine_line|#define LLC_PDU_GROUP_DSAP_MASK    0x01
DECL|macro|LLC_PDU_IS_GROUP_DSAP
mdefine_line|#define LLC_PDU_IS_GROUP_DSAP(pdu)      &bslash;&n;&t;((pdu-&gt;dsap &amp; LLC_PDU_GROUP_DSAP_MASK) ? 0 : 1)
DECL|macro|LLC_PDU_IS_INDIV_DSAP
mdefine_line|#define LLC_PDU_IS_INDIV_DSAP(pdu)      &bslash;&n;&t;(!(pdu-&gt;dsap &amp; LLC_PDU_GROUP_DSAP_MASK) ? 0 : 1)
multiline_comment|/* Command/response PDU indicator in SSAP field */
DECL|macro|LLC_PDU_CMD_RSP_MASK
mdefine_line|#define LLC_PDU_CMD_RSP_MASK&t;0x01
DECL|macro|LLC_PDU_CMD
mdefine_line|#define LLC_PDU_CMD&t;&t;0
DECL|macro|LLC_PDU_RSP
mdefine_line|#define LLC_PDU_RSP&t;&t;1
DECL|macro|LLC_PDU_IS_CMD
mdefine_line|#define LLC_PDU_IS_CMD(pdu)    ((pdu-&gt;ssap &amp; LLC_PDU_RSP) ? 1 : 0)
DECL|macro|LLC_PDU_IS_RSP
mdefine_line|#define LLC_PDU_IS_RSP(pdu)    ((pdu-&gt;ssap &amp; LLC_PDU_RSP) ? 0 : 1)
multiline_comment|/* Get PDU type from 2 lowest-order bits of control field first byte */
DECL|macro|LLC_PDU_TYPE_I_MASK
mdefine_line|#define LLC_PDU_TYPE_I_MASK    0x01&t;/* 16-bit control field */
DECL|macro|LLC_PDU_TYPE_S_MASK
mdefine_line|#define LLC_PDU_TYPE_S_MASK    0x03
DECL|macro|LLC_PDU_TYPE_U_MASK
mdefine_line|#define LLC_PDU_TYPE_U_MASK    0x03&t;/* 8-bit control field */
DECL|macro|LLC_PDU_TYPE_MASK
mdefine_line|#define LLC_PDU_TYPE_MASK      0x03
DECL|macro|LLC_PDU_TYPE_I
mdefine_line|#define LLC_PDU_TYPE_I&t;0&t;/* first bit */
DECL|macro|LLC_PDU_TYPE_S
mdefine_line|#define LLC_PDU_TYPE_S&t;1&t;/* first two bits */
DECL|macro|LLC_PDU_TYPE_U
mdefine_line|#define LLC_PDU_TYPE_U&t;3&t;/* first two bits */
DECL|macro|LLC_PDU_TYPE_IS_I
mdefine_line|#define LLC_PDU_TYPE_IS_I(pdu) &bslash;&n;&t;((!(pdu-&gt;ctrl_1 &amp; LLC_PDU_TYPE_I_MASK)) ? 0 : 1)
DECL|macro|LLC_PDU_TYPE_IS_U
mdefine_line|#define LLC_PDU_TYPE_IS_U(pdu) &bslash;&n;&t;(((pdu-&gt;ctrl_1 &amp; LLC_PDU_TYPE_U_MASK) == LLC_PDU_TYPE_U) ? 0 : 1)
DECL|macro|LLC_PDU_TYPE_IS_S
mdefine_line|#define LLC_PDU_TYPE_IS_S(pdu) &bslash;&n;&t;(((pdu-&gt;ctrl_1 &amp; LLC_PDU_TYPE_S_MASK) == LLC_PDU_TYPE_S) ? 0 : 1)
multiline_comment|/* U-format PDU control field masks */
DECL|macro|LLC_U_PF_BIT_MASK
mdefine_line|#define LLC_U_PF_BIT_MASK      0x10&t;/* P/F bit mask */
DECL|macro|LLC_U_PF_IS_1
mdefine_line|#define LLC_U_PF_IS_1(pdu)     ((pdu-&gt;ctrl_1 &amp; LLC_U_PF_BIT_MASK) ? 0 : 1)
DECL|macro|LLC_U_PF_IS_0
mdefine_line|#define LLC_U_PF_IS_0(pdu)     ((!(pdu-&gt;ctrl_1 &amp; LLC_U_PF_BIT_MASK)) ? 0 : 1)
DECL|macro|LLC_U_PDU_CMD_MASK
mdefine_line|#define LLC_U_PDU_CMD_MASK     0xEC&t;/* cmd/rsp mask */
DECL|macro|LLC_U_PDU_CMD
mdefine_line|#define LLC_U_PDU_CMD(pdu)     (pdu-&gt;ctrl_1 &amp; LLC_U_PDU_CMD_MASK)
DECL|macro|LLC_U_PDU_RSP
mdefine_line|#define LLC_U_PDU_RSP(pdu)     (pdu-&gt;ctrl_1 &amp; LLC_U_PDU_CMD_MASK)
DECL|macro|LLC_1_PDU_CMD_UI
mdefine_line|#define LLC_1_PDU_CMD_UI       0x00&t;/* Type 1 cmds/rsps */
DECL|macro|LLC_1_PDU_CMD_XID
mdefine_line|#define LLC_1_PDU_CMD_XID      0xAC
DECL|macro|LLC_1_PDU_CMD_TEST
mdefine_line|#define LLC_1_PDU_CMD_TEST     0xE0
DECL|macro|LLC_2_PDU_CMD_SABME
mdefine_line|#define LLC_2_PDU_CMD_SABME    0x6C&t;/* Type 2 cmds/rsps */
DECL|macro|LLC_2_PDU_CMD_DISC
mdefine_line|#define LLC_2_PDU_CMD_DISC     0x40
DECL|macro|LLC_2_PDU_RSP_UA
mdefine_line|#define LLC_2_PDU_RSP_UA       0x60
DECL|macro|LLC_2_PDU_RSP_DM
mdefine_line|#define LLC_2_PDU_RSP_DM       0x0C
DECL|macro|LLC_2_PDU_RSP_FRMR
mdefine_line|#define LLC_2_PDU_RSP_FRMR     0x84
multiline_comment|/* Type 1 operations */
multiline_comment|/* XID information field bit masks */
multiline_comment|/* LLC format identifier (byte 1) */
DECL|macro|LLC_XID_FMT_ID
mdefine_line|#define LLC_XID_FMT_ID&t;&t;0x81&t;/* first byte must be this */
multiline_comment|/* LLC types/classes identifier (byte 2) */
DECL|macro|LLC_XID_CLASS_ZEROS_MASK
mdefine_line|#define LLC_XID_CLASS_ZEROS_MASK&t;0xE0&t;/* these must be zeros */
DECL|macro|LLC_XID_CLASS_MASK
mdefine_line|#define LLC_XID_CLASS_MASK&t;&t;0x1F&t;/* AND with byte to get below */
DECL|macro|LLC_XID_NULL_CLASS_1
mdefine_line|#define LLC_XID_NULL_CLASS_1&t;0x01&t;/* if NULL LSAP...use these */
DECL|macro|LLC_XID_NULL_CLASS_2
mdefine_line|#define LLC_XID_NULL_CLASS_2&t;0x03
DECL|macro|LLC_XID_NULL_CLASS_3
mdefine_line|#define LLC_XID_NULL_CLASS_3&t;0x05
DECL|macro|LLC_XID_NULL_CLASS_4
mdefine_line|#define LLC_XID_NULL_CLASS_4&t;0x07
DECL|macro|LLC_XID_NNULL_TYPE_1
mdefine_line|#define LLC_XID_NNULL_TYPE_1&t;0x01&t;/* if non-NULL LSAP...use these */
DECL|macro|LLC_XID_NNULL_TYPE_2
mdefine_line|#define LLC_XID_NNULL_TYPE_2&t;0x02
DECL|macro|LLC_XID_NNULL_TYPE_3
mdefine_line|#define LLC_XID_NNULL_TYPE_3&t;0x04
DECL|macro|LLC_XID_NNULL_TYPE_1_2
mdefine_line|#define LLC_XID_NNULL_TYPE_1_2&t;0x03
DECL|macro|LLC_XID_NNULL_TYPE_1_3
mdefine_line|#define LLC_XID_NNULL_TYPE_1_3&t;0x05
DECL|macro|LLC_XID_NNULL_TYPE_2_3
mdefine_line|#define LLC_XID_NNULL_TYPE_2_3&t;0x06
DECL|macro|LLC_XID_NNULL_ALL
mdefine_line|#define LLC_XID_NNULL_ALL&t;&t;0x07
multiline_comment|/* Sender Receive Window (byte 3) */
DECL|macro|LLC_XID_RW_MASK
mdefine_line|#define LLC_XID_RW_MASK&t;0xFE&t;/* AND with value to get below */
DECL|macro|LLC_XID_MIN_RW
mdefine_line|#define LLC_XID_MIN_RW&t;0x02&t;/* lowest-order bit always zero */
multiline_comment|/* Type 2 operations */
DECL|macro|LLC_2_SEQ_NBR_MODULO
mdefine_line|#define LLC_2_SEQ_NBR_MODULO   ((u8) 128)
multiline_comment|/* I-PDU masks (&squot;ctrl&squot; is I-PDU control word) */
DECL|macro|LLC_I_GET_NS
mdefine_line|#define LLC_I_GET_NS(pdu)     (u8)((pdu-&gt;ctrl_1 &amp; 0xFE) &gt;&gt; 1)
DECL|macro|LLC_I_GET_NR
mdefine_line|#define LLC_I_GET_NR(pdu)     (u8)((pdu-&gt;ctrl_2 &amp; 0xFE) &gt;&gt; 1)
DECL|macro|LLC_I_PF_BIT_MASK
mdefine_line|#define LLC_I_PF_BIT_MASK      0x01
DECL|macro|LLC_I_PF_IS_0
mdefine_line|#define LLC_I_PF_IS_0(pdu)     ((!(pdu-&gt;ctrl_2 &amp; LLC_I_PF_BIT_MASK)) ? 0 : 1)
DECL|macro|LLC_I_PF_IS_1
mdefine_line|#define LLC_I_PF_IS_1(pdu)     ((pdu-&gt;ctrl_2 &amp; LLC_I_PF_BIT_MASK) ? 0 : 1)
multiline_comment|/* S-PDU supervisory commands and responses */
DECL|macro|LLC_S_PDU_CMD_MASK
mdefine_line|#define LLC_S_PDU_CMD_MASK     0x0C
DECL|macro|LLC_S_PDU_CMD
mdefine_line|#define LLC_S_PDU_CMD(pdu)     (pdu-&gt;ctrl_1 &amp; LLC_S_PDU_CMD_MASK)
DECL|macro|LLC_S_PDU_RSP
mdefine_line|#define LLC_S_PDU_RSP(pdu)     (pdu-&gt;ctrl_1 &amp; LLC_S_PDU_CMD_MASK)
DECL|macro|LLC_2_PDU_CMD_RR
mdefine_line|#define LLC_2_PDU_CMD_RR       0x00&t;/* rx ready cmd */
DECL|macro|LLC_2_PDU_RSP_RR
mdefine_line|#define LLC_2_PDU_RSP_RR       0x00&t;/* rx ready rsp */
DECL|macro|LLC_2_PDU_CMD_REJ
mdefine_line|#define LLC_2_PDU_CMD_REJ      0x08&t;/* reject PDU cmd */
DECL|macro|LLC_2_PDU_RSP_REJ
mdefine_line|#define LLC_2_PDU_RSP_REJ      0x08&t;/* reject PDU rsp */
DECL|macro|LLC_2_PDU_CMD_RNR
mdefine_line|#define LLC_2_PDU_CMD_RNR      0x04&t;/* rx not ready cmd */
DECL|macro|LLC_2_PDU_RSP_RNR
mdefine_line|#define LLC_2_PDU_RSP_RNR      0x04&t;/* rx not ready rsp */
DECL|macro|LLC_S_PF_BIT_MASK
mdefine_line|#define LLC_S_PF_BIT_MASK      0x01
DECL|macro|LLC_S_PF_IS_0
mdefine_line|#define LLC_S_PF_IS_0(pdu)     ((!(pdu-&gt;ctrl_2 &amp; LLC_S_PF_BIT_MASK)) ? 0 : 1)
DECL|macro|LLC_S_PF_IS_1
mdefine_line|#define LLC_S_PF_IS_1(pdu)     ((pdu-&gt;ctrl_2 &amp; LLC_S_PF_BIT_MASK) ? 0 : 1)
DECL|macro|PDU_SUPV_GET_Nr
mdefine_line|#define PDU_SUPV_GET_Nr(pdu)   ((pdu-&gt;ctrl_2 &amp; 0xFE) &gt;&gt; 1)
DECL|macro|PDU_GET_NEXT_Vr
mdefine_line|#define PDU_GET_NEXT_Vr(sn)    (++sn &amp; ~LLC_2_SEQ_NBR_MODULO)
multiline_comment|/* FRMR information field macros */
DECL|macro|FRMR_INFO_LENGTH
mdefine_line|#define FRMR_INFO_LENGTH       5&t;/* 5 bytes of information */
multiline_comment|/*&n; * info is pointer to FRMR info field structure; &squot;rej_ctrl&squot; is byte pointer&n; * (if U-PDU) or word pointer to rejected PDU control field&n; */
DECL|macro|FRMR_INFO_SET_REJ_CNTRL
mdefine_line|#define FRMR_INFO_SET_REJ_CNTRL(info,rej_ctrl) &bslash;&n;&t;info-&gt;rej_pdu_ctrl = ((*((u8 *) rej_ctrl) &amp; &bslash;&n;&t;&t;&t;&t;LLC_PDU_TYPE_U) != LLC_PDU_TYPE_U ? &bslash;&n;&t;&t;&t;&t;(u16)*((u16 *) rej_ctrl) : &bslash;&n;&t;&t;&t;&t;(((u16) *((u8 *) rej_ctrl)) &amp; 0x00FF))
multiline_comment|/*&n; * Info is pointer to FRMR info field structure; &squot;vs&squot; is a byte containing&n; * send state variable value in low-order 7 bits (insure the lowest-order&n; * bit remains zero (0))&n; */
DECL|macro|FRMR_INFO_SET_Vs
mdefine_line|#define FRMR_INFO_SET_Vs(info,vs) (info-&gt;curr_ssv = (((u8) vs) &lt;&lt; 1))
DECL|macro|FRMR_INFO_SET_Vr
mdefine_line|#define FRMR_INFO_SET_Vr(info,vr) (info-&gt;curr_rsv = (((u8) vr) &lt;&lt; 1))
multiline_comment|/*&n; * Info is pointer to FRMR info field structure; &squot;cr&squot; is a byte containing&n; * the C/R bit value in the low-order bit&n; */
DECL|macro|FRMR_INFO_SET_C_R_BIT
mdefine_line|#define FRMR_INFO_SET_C_R_BIT(info, cr)  (info-&gt;curr_rsv |= (((u8) cr) &amp; 0x01))
multiline_comment|/*&n; * In the remaining five macros, &squot;info&squot; is pointer to FRMR info field&n; * structure; &squot;ind&squot; is a byte containing the bit value to set in the&n; * lowest-order bit)&n; */
DECL|macro|FRMR_INFO_SET_INVALID_PDU_CTRL_IND
mdefine_line|#define FRMR_INFO_SET_INVALID_PDU_CTRL_IND(info, ind) &bslash;&n;       (info-&gt;ind_bits = ((info-&gt;ind_bits &amp; 0xFE) | (((u8) ind) &amp; 0x01)))
DECL|macro|FRMR_INFO_SET_INVALID_PDU_INFO_IND
mdefine_line|#define FRMR_INFO_SET_INVALID_PDU_INFO_IND(info, ind) &bslash;&n;       (info-&gt;ind_bits = ( (info-&gt;ind_bits &amp; 0xFD) | (((u8) ind) &amp; 0x02)))
DECL|macro|FRMR_INFO_SET_PDU_INFO_2LONG_IND
mdefine_line|#define FRMR_INFO_SET_PDU_INFO_2LONG_IND(info, ind) &bslash;&n;       (info-&gt;ind_bits = ( (info-&gt;ind_bits &amp; 0xFB) | (((u8) ind) &amp; 0x04)))
DECL|macro|FRMR_INFO_SET_PDU_INVALID_Nr_IND
mdefine_line|#define FRMR_INFO_SET_PDU_INVALID_Nr_IND(info, ind) &bslash;&n;       (info-&gt;ind_bits = ( (info-&gt;ind_bits &amp; 0xF7) | (((u8) ind) &amp; 0x08)))
DECL|macro|FRMR_INFO_SET_PDU_INVALID_Ns_IND
mdefine_line|#define FRMR_INFO_SET_PDU_INVALID_Ns_IND(info, ind) &bslash;&n;       (info-&gt;ind_bits = ( (info-&gt;ind_bits &amp; 0xEF) | (((u8) ind) &amp; 0x10)))
multiline_comment|/* Sequence-numbered PDU format (4 bytes in length) */
DECL|struct|llc_pdu_sn
r_typedef
r_struct
id|llc_pdu_sn
(brace
DECL|member|dsap
id|u8
id|dsap
suffix:semicolon
DECL|member|ssap
id|u8
id|ssap
suffix:semicolon
DECL|member|ctrl_1
id|u8
id|ctrl_1
suffix:semicolon
DECL|member|ctrl_2
id|u8
id|ctrl_2
suffix:semicolon
DECL|typedef|llc_pdu_sn_t
)brace
id|llc_pdu_sn_t
suffix:semicolon
multiline_comment|/* Un-numbered PDU format (3 bytes in length) */
DECL|struct|llc_pdu_un
r_typedef
r_struct
id|llc_pdu_un
(brace
DECL|member|dsap
id|u8
id|dsap
suffix:semicolon
DECL|member|ssap
id|u8
id|ssap
suffix:semicolon
DECL|member|ctrl_1
id|u8
id|ctrl_1
suffix:semicolon
DECL|typedef|llc_pdu_un_t
)brace
id|llc_pdu_un_t
suffix:semicolon
multiline_comment|/* LLC Type 1 XID command/response information fields format */
DECL|struct|llc_xid_info
r_typedef
r_struct
id|llc_xid_info
(brace
DECL|member|fmt_id
id|u8
id|fmt_id
suffix:semicolon
multiline_comment|/* always 0x18 for LLC */
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* different if NULL/non-NULL LSAP */
DECL|member|rw
id|u8
id|rw
suffix:semicolon
multiline_comment|/* sender receive window */
DECL|typedef|llc_xid_info_t
)brace
id|llc_xid_info_t
suffix:semicolon
multiline_comment|/* LLC Type 2 FRMR response information field format */
DECL|struct|llc_frmr_info
r_typedef
r_struct
id|llc_frmr_info
(brace
DECL|member|rej_pdu_ctrl
id|u16
id|rej_pdu_ctrl
suffix:semicolon
multiline_comment|/* bits 1-8 if U-PDU */
DECL|member|curr_ssv
id|u8
id|curr_ssv
suffix:semicolon
multiline_comment|/* current send state variable val */
DECL|member|curr_rsv
id|u8
id|curr_rsv
suffix:semicolon
multiline_comment|/* current receive state variable */
DECL|member|ind_bits
id|u8
id|ind_bits
suffix:semicolon
multiline_comment|/* indicator bits set with macro */
DECL|typedef|llc_frmr_info_t
)brace
id|llc_frmr_info_t
suffix:semicolon
r_extern
r_void
id|llc_pdu_set_cmd_rsp
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|type
)paren
suffix:semicolon
r_extern
r_void
id|llc_pdu_set_pf_bit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|bit_value
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_decode_pf_bit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|pf_bit
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_decode_cr_bit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|cr_bit
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_decode_sa
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|sa
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_decode_da
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|ds
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_decode_dsap
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|dsap
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_decode_ssap
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|ssap
)paren
suffix:semicolon
r_extern
r_int
id|llc_decode_pdu_type
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|destination
)paren
suffix:semicolon
r_extern
r_void
id|llc_pdu_header_init
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|pdu_type
comma
id|u8
id|ssap
comma
id|u8
id|dsap
comma
id|u8
id|cr
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_ui_cmd
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_xid_cmd
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|svcs_supported
comma
id|u8
id|rx_window
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_test_cmd
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_disc_cmd
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|p_bit
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_i_cmd
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|p_bit
comma
id|u8
id|ns
comma
id|u8
id|nr
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_rej_cmd
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|p_bit
comma
id|u8
id|nr
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_rnr_cmd
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|p_bit
comma
id|u8
id|nr
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_rr_cmd
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|p_bit
comma
id|u8
id|nr
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_sabme_cmd
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|p_bit
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_dm_rsp
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|f_bit
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_xid_rsp
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|svcs_supported
comma
id|u8
id|rx_window
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_test_rsp
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|sk_buff
op_star
id|ev_skb
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_frmr_rsp
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|llc_pdu_sn_t
op_star
id|prev_pdu
comma
id|u8
id|f_bit
comma
id|u8
id|vs
comma
id|u8
id|vr
comma
id|u8
id|vzyxw
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_rr_rsp
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|f_bit
comma
id|u8
id|nr
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_rej_rsp
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|f_bit
comma
id|u8
id|nr
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_rnr_rsp
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|f_bit
comma
id|u8
id|nr
)paren
suffix:semicolon
r_extern
r_int
id|llc_pdu_init_as_ua_rsp
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
id|f_bit
)paren
suffix:semicolon
macro_line|#endif /* LLC_PDU_H */
eof
