multiline_comment|/*&n; * llc_pdu.c - access to PDU internals&n; *&n; * Copyright (c) 1997 by Procom Technology, Inc.&n; *&t;&t; 2001-2003 by Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n; *&n; * This program can be redistributed or modified under the terms of the&n; * GNU General Public License as published by the Free Software Foundation.&n; * This program is distributed without any warranty or implied warranty&n; * of merchantability or fitness for a particular purpose.&n; *&n; * See the GNU General Public License for more details.&n; */
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/llc_pdu.h&gt;
r_static
r_void
id|llc_pdu_decode_pdu_type
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|type
)paren
suffix:semicolon
r_static
id|u8
id|llc_pdu_get_pf_bit
c_func
(paren
r_struct
id|llc_pdu_sn
op_star
id|pdu
)paren
suffix:semicolon
DECL|function|llc_pdu_set_cmd_rsp
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
id|pdu_type
)paren
(brace
id|llc_pdu_un_hdr
c_func
(paren
id|skb
)paren
op_member_access_from_pointer
id|ssap
op_or_assign
id|pdu_type
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;pdu_set_pf_bit - sets poll/final bit in LLC header&n; *&t;@pdu_frame: input frame that p/f bit must be set into it.&n; *&t;@bit_value: poll/final bit (0 or 1).&n; *&n; *&t;This function sets poll/final bit in LLC header (based on type of PDU).&n; *&t;in I or S pdus, p/f bit is right bit of fourth byte in header. in U&n; *&t;pdus p/f bit is fifth bit of third byte.&n; */
DECL|function|llc_pdu_set_pf_bit
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
(brace
id|u8
id|pdu_type
suffix:semicolon
r_struct
id|llc_pdu_sn
op_star
id|pdu
suffix:semicolon
id|llc_pdu_decode_pdu_type
c_func
(paren
id|skb
comma
op_amp
id|pdu_type
)paren
suffix:semicolon
id|pdu
op_assign
id|llc_pdu_sn_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|pdu_type
)paren
(brace
r_case
id|LLC_PDU_TYPE_I
suffix:colon
r_case
id|LLC_PDU_TYPE_S
suffix:colon
id|pdu-&gt;ctrl_2
op_assign
(paren
id|pdu-&gt;ctrl_2
op_amp
l_int|0xFE
)paren
op_or
id|bit_value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LLC_PDU_TYPE_U
suffix:colon
id|pdu-&gt;ctrl_1
op_or_assign
(paren
id|pdu-&gt;ctrl_1
op_amp
l_int|0xEF
)paren
op_or
(paren
id|bit_value
op_lshift
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;llc_pdu_decode_pf_bit - extracs poll/final bit from LLC header&n; *&t;@skb: input skb that p/f bit must be extracted from it&n; *&t;@pf_bit: poll/final bit (0 or 1)&n; *&n; *&t;This function extracts poll/final bit from LLC header (based on type of&n; *&t;PDU). In I or S pdus, p/f bit is right bit of fourth byte in header. In&n; *&t;U pdus p/f bit is fifth bit of third byte.&n; */
DECL|function|llc_pdu_decode_pf_bit
r_void
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
(brace
id|u8
id|pdu_type
suffix:semicolon
r_struct
id|llc_pdu_sn
op_star
id|pdu
suffix:semicolon
id|llc_pdu_decode_pdu_type
c_func
(paren
id|skb
comma
op_amp
id|pdu_type
)paren
suffix:semicolon
id|pdu
op_assign
id|llc_pdu_sn_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|pdu_type
)paren
(brace
r_case
id|LLC_PDU_TYPE_I
suffix:colon
r_case
id|LLC_PDU_TYPE_S
suffix:colon
op_star
id|pf_bit
op_assign
id|pdu-&gt;ctrl_2
op_amp
id|LLC_S_PF_BIT_MASK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LLC_PDU_TYPE_U
suffix:colon
op_star
id|pf_bit
op_assign
(paren
id|pdu-&gt;ctrl_1
op_amp
id|LLC_U_PF_BIT_MASK
)paren
op_rshift
l_int|4
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;llc_pdu_init_as_disc_cmd - Builds DISC PDU&n; *&t;@skb: Address of the skb to build&n; *&t;@p_bit: The P bit to set in the PDU&n; *&n; *&t;Builds a pdu frame as a DISC command.&n; */
DECL|function|llc_pdu_init_as_disc_cmd
r_void
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
(brace
r_struct
id|llc_pdu_un
op_star
id|pdu
op_assign
id|llc_pdu_un_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
id|pdu-&gt;ctrl_1
op_assign
id|LLC_PDU_TYPE_U
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
id|LLC_2_PDU_CMD_DISC
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
(paren
(paren
id|p_bit
op_amp
l_int|1
)paren
op_lshift
l_int|4
)paren
op_amp
id|LLC_U_PF_BIT_MASK
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_pdu_init_as_i_cmd - builds I pdu&n; *&t;@skb: Address of the skb to build&n; *&t;@p_bit: The P bit to set in the PDU&n; *&t;@ns: The sequence number of the data PDU&n; *&t;@nr: The seq. number of the expected I PDU from the remote&n; *&n; *&t;Builds a pdu frame as an I command.&n; */
DECL|function|llc_pdu_init_as_i_cmd
r_void
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
(brace
r_struct
id|llc_pdu_sn
op_star
id|pdu
op_assign
id|llc_pdu_sn_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
id|pdu-&gt;ctrl_1
op_assign
id|LLC_PDU_TYPE_I
suffix:semicolon
id|pdu-&gt;ctrl_2
op_assign
l_int|0
suffix:semicolon
id|pdu-&gt;ctrl_2
op_or_assign
(paren
id|p_bit
op_amp
id|LLC_I_PF_BIT_MASK
)paren
suffix:semicolon
multiline_comment|/* p/f bit */
id|pdu-&gt;ctrl_1
op_or_assign
(paren
id|ns
op_lshift
l_int|1
)paren
op_amp
l_int|0xFE
suffix:semicolon
multiline_comment|/* set N(S) in bits 2..8 */
id|pdu-&gt;ctrl_2
op_or_assign
(paren
id|nr
op_lshift
l_int|1
)paren
op_amp
l_int|0xFE
suffix:semicolon
multiline_comment|/* set N(R) in bits 10..16 */
)brace
multiline_comment|/**&n; *&t;llc_pdu_init_as_rej_cmd - builds REJ PDU&n; *&t;@skb: Address of the skb to build&n; *&t;@p_bit: The P bit to set in the PDU&n; *&t;@nr: The seq. number of the expected I PDU from the remote&n; *&n; *&t;Builds a pdu frame as a REJ command.&n; */
DECL|function|llc_pdu_init_as_rej_cmd
r_void
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
(brace
r_struct
id|llc_pdu_sn
op_star
id|pdu
op_assign
id|llc_pdu_sn_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
id|pdu-&gt;ctrl_1
op_assign
id|LLC_PDU_TYPE_S
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
id|LLC_2_PDU_CMD_REJ
suffix:semicolon
id|pdu-&gt;ctrl_2
op_assign
l_int|0
suffix:semicolon
id|pdu-&gt;ctrl_2
op_or_assign
id|p_bit
op_amp
id|LLC_S_PF_BIT_MASK
suffix:semicolon
id|pdu-&gt;ctrl_1
op_and_assign
l_int|0x0F
suffix:semicolon
multiline_comment|/* setting bits 5..8 to zero(reserved) */
id|pdu-&gt;ctrl_2
op_or_assign
(paren
id|nr
op_lshift
l_int|1
)paren
op_amp
l_int|0xFE
suffix:semicolon
multiline_comment|/* set N(R) in bits 10..16 */
)brace
multiline_comment|/**&n; *&t;llc_pdu_init_as_rnr_cmd - builds RNR pdu&n; *&t;@skb: Address of the skb to build&n; *&t;@p_bit: The P bit to set in the PDU&n; *&t;@nr: The seq. number of the expected I PDU from the remote&n; *&n; *&t;Builds a pdu frame as an RNR command.&n; */
DECL|function|llc_pdu_init_as_rnr_cmd
r_void
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
(brace
r_struct
id|llc_pdu_sn
op_star
id|pdu
op_assign
id|llc_pdu_sn_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
id|pdu-&gt;ctrl_1
op_assign
id|LLC_PDU_TYPE_S
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
id|LLC_2_PDU_CMD_RNR
suffix:semicolon
id|pdu-&gt;ctrl_2
op_assign
l_int|0
suffix:semicolon
id|pdu-&gt;ctrl_2
op_or_assign
id|p_bit
op_amp
id|LLC_S_PF_BIT_MASK
suffix:semicolon
id|pdu-&gt;ctrl_1
op_and_assign
l_int|0x0F
suffix:semicolon
multiline_comment|/* setting bits 5..8 to zero(reserved) */
id|pdu-&gt;ctrl_2
op_or_assign
(paren
id|nr
op_lshift
l_int|1
)paren
op_amp
l_int|0xFE
suffix:semicolon
multiline_comment|/* set N(R) in bits 10..16 */
)brace
multiline_comment|/**&n; *&t;llc_pdu_init_as_rr_cmd - Builds RR pdu&n; *&t;@skb: Address of the skb to build&n; *&t;@p_bit: The P bit to set in the PDU&n; *&t;@nr: The seq. number of the expected I PDU from the remote&n; *&n; *&t;Builds a pdu frame as an RR command.&n; */
DECL|function|llc_pdu_init_as_rr_cmd
r_void
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
(brace
r_struct
id|llc_pdu_sn
op_star
id|pdu
op_assign
id|llc_pdu_sn_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
id|pdu-&gt;ctrl_1
op_assign
id|LLC_PDU_TYPE_S
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
id|LLC_2_PDU_CMD_RR
suffix:semicolon
id|pdu-&gt;ctrl_2
op_assign
id|p_bit
op_amp
id|LLC_S_PF_BIT_MASK
suffix:semicolon
id|pdu-&gt;ctrl_1
op_and_assign
l_int|0x0F
suffix:semicolon
multiline_comment|/* setting bits 5..8 to zero(reserved) */
id|pdu-&gt;ctrl_2
op_or_assign
(paren
id|nr
op_lshift
l_int|1
)paren
op_amp
l_int|0xFE
suffix:semicolon
multiline_comment|/* set N(R) in bits 10..16 */
)brace
multiline_comment|/**&n; *&t;llc_pdu_init_as_sabme_cmd - builds SABME pdu&n; *&t;@skb: Address of the skb to build&n; *&t;@p_bit: The P bit to set in the PDU&n; *&n; *&t;Builds a pdu frame as an SABME command.&n; */
DECL|function|llc_pdu_init_as_sabme_cmd
r_void
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
(brace
r_struct
id|llc_pdu_un
op_star
id|pdu
op_assign
id|llc_pdu_un_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
id|pdu-&gt;ctrl_1
op_assign
id|LLC_PDU_TYPE_U
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
id|LLC_2_PDU_CMD_SABME
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
(paren
(paren
id|p_bit
op_amp
l_int|1
)paren
op_lshift
l_int|4
)paren
op_amp
id|LLC_U_PF_BIT_MASK
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_pdu_init_as_dm_rsp - builds DM response pdu&n; *&t;@skb: Address of the skb to build&n; *&t;@f_bit: The F bit to set in the PDU&n; *&n; *&t;Builds a pdu frame as a DM response.&n; */
DECL|function|llc_pdu_init_as_dm_rsp
r_void
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
(brace
r_struct
id|llc_pdu_un
op_star
id|pdu
op_assign
id|llc_pdu_un_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
id|pdu-&gt;ctrl_1
op_assign
id|LLC_PDU_TYPE_U
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
id|LLC_2_PDU_RSP_DM
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
(paren
(paren
id|f_bit
op_amp
l_int|1
)paren
op_lshift
l_int|4
)paren
op_amp
id|LLC_U_PF_BIT_MASK
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_pdu_init_as_frmr_rsp - builds FRMR response PDU&n; *&t;@skb: Address of the frame to build&n; *&t;@prev_pdu: The rejected PDU frame&n; *&t;@f_bit: The F bit to set in the PDU&n; *&t;@vs: tx state vari value for the data link conn at the rejecting LLC&n; *&t;@vr: rx state var value for the data link conn at the rejecting LLC&n; *&t;@vzyxw: completely described in the IEEE Std 802.2 document (Pg 55)&n; *&n; *&t;Builds a pdu frame as a FRMR response.&n; */
DECL|function|llc_pdu_init_as_frmr_rsp
r_void
id|llc_pdu_init_as_frmr_rsp
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|llc_pdu_sn
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
(brace
r_struct
id|llc_frmr_info
op_star
id|frmr_info
suffix:semicolon
id|u8
id|prev_pf
op_assign
l_int|0
suffix:semicolon
id|u8
op_star
id|ctrl
suffix:semicolon
r_struct
id|llc_pdu_sn
op_star
id|pdu
op_assign
id|llc_pdu_sn_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
id|pdu-&gt;ctrl_1
op_assign
id|LLC_PDU_TYPE_U
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
id|LLC_2_PDU_RSP_FRMR
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
(paren
(paren
id|f_bit
op_amp
l_int|1
)paren
op_lshift
l_int|4
)paren
op_amp
id|LLC_U_PF_BIT_MASK
suffix:semicolon
id|frmr_info
op_assign
(paren
r_struct
id|llc_frmr_info
op_star
)paren
op_amp
id|pdu-&gt;ctrl_2
suffix:semicolon
id|ctrl
op_assign
(paren
id|u8
op_star
)paren
op_amp
id|prev_pdu-&gt;ctrl_1
suffix:semicolon
id|FRMR_INFO_SET_REJ_CNTRL
c_func
(paren
id|frmr_info
comma
id|ctrl
)paren
suffix:semicolon
id|FRMR_INFO_SET_Vs
c_func
(paren
id|frmr_info
comma
id|vs
)paren
suffix:semicolon
id|FRMR_INFO_SET_Vr
c_func
(paren
id|frmr_info
comma
id|vr
)paren
suffix:semicolon
id|prev_pf
op_assign
id|llc_pdu_get_pf_bit
c_func
(paren
id|prev_pdu
)paren
suffix:semicolon
id|FRMR_INFO_SET_C_R_BIT
c_func
(paren
id|frmr_info
comma
id|prev_pf
)paren
suffix:semicolon
id|FRMR_INFO_SET_INVALID_PDU_CTRL_IND
c_func
(paren
id|frmr_info
comma
id|vzyxw
)paren
suffix:semicolon
id|FRMR_INFO_SET_INVALID_PDU_INFO_IND
c_func
(paren
id|frmr_info
comma
id|vzyxw
)paren
suffix:semicolon
id|FRMR_INFO_SET_PDU_INFO_2LONG_IND
c_func
(paren
id|frmr_info
comma
id|vzyxw
)paren
suffix:semicolon
id|FRMR_INFO_SET_PDU_INVALID_Nr_IND
c_func
(paren
id|frmr_info
comma
id|vzyxw
)paren
suffix:semicolon
id|FRMR_INFO_SET_PDU_INVALID_Ns_IND
c_func
(paren
id|frmr_info
comma
id|vzyxw
)paren
suffix:semicolon
id|skb_put
c_func
(paren
id|skb
comma
l_int|5
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_pdu_init_as_rr_rsp - builds RR response pdu&n; *&t;@skb: Address of the skb to build&n; *&t;@f_bit: The F bit to set in the PDU&n; *&t;@nr: The seq. number of the expected data PDU from the remote&n; *&n; *&t;Builds a pdu frame as an RR response.&n; */
DECL|function|llc_pdu_init_as_rr_rsp
r_void
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
(brace
r_struct
id|llc_pdu_sn
op_star
id|pdu
op_assign
id|llc_pdu_sn_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
id|pdu-&gt;ctrl_1
op_assign
id|LLC_PDU_TYPE_S
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
id|LLC_2_PDU_RSP_RR
suffix:semicolon
id|pdu-&gt;ctrl_2
op_assign
l_int|0
suffix:semicolon
id|pdu-&gt;ctrl_2
op_or_assign
id|f_bit
op_amp
id|LLC_S_PF_BIT_MASK
suffix:semicolon
id|pdu-&gt;ctrl_1
op_and_assign
l_int|0x0F
suffix:semicolon
multiline_comment|/* setting bits 5..8 to zero(reserved) */
id|pdu-&gt;ctrl_2
op_or_assign
(paren
id|nr
op_lshift
l_int|1
)paren
op_amp
l_int|0xFE
suffix:semicolon
multiline_comment|/* set N(R) in bits 10..16 */
)brace
multiline_comment|/**&n; *&t;llc_pdu_init_as_rej_rsp - builds REJ response pdu&n; *&t;@skb: Address of the skb to build&n; *&t;@f_bit: The F bit to set in the PDU&n; *&t;@nr: The seq. number of the expected data PDU from the remote&n; *&n; *&t;Builds a pdu frame as a REJ response.&n; */
DECL|function|llc_pdu_init_as_rej_rsp
r_void
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
(brace
r_struct
id|llc_pdu_sn
op_star
id|pdu
op_assign
id|llc_pdu_sn_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
id|pdu-&gt;ctrl_1
op_assign
id|LLC_PDU_TYPE_S
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
id|LLC_2_PDU_RSP_REJ
suffix:semicolon
id|pdu-&gt;ctrl_2
op_assign
l_int|0
suffix:semicolon
id|pdu-&gt;ctrl_2
op_or_assign
id|f_bit
op_amp
id|LLC_S_PF_BIT_MASK
suffix:semicolon
id|pdu-&gt;ctrl_1
op_and_assign
l_int|0x0F
suffix:semicolon
multiline_comment|/* setting bits 5..8 to zero(reserved) */
id|pdu-&gt;ctrl_2
op_or_assign
(paren
id|nr
op_lshift
l_int|1
)paren
op_amp
l_int|0xFE
suffix:semicolon
multiline_comment|/* set N(R) in bits 10..16 */
)brace
multiline_comment|/**&n; *&t;llc_pdu_init_as_rnr_rsp - builds RNR response pdu&n; *&t;@skb: Address of the frame to build&n; *&t;@f_bit: The F bit to set in the PDU&n; *&t;@nr: The seq. number of the expected data PDU from the remote&n; *&n; *&t;Builds a pdu frame as an RNR response.&n; */
DECL|function|llc_pdu_init_as_rnr_rsp
r_void
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
(brace
r_struct
id|llc_pdu_sn
op_star
id|pdu
op_assign
id|llc_pdu_sn_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
id|pdu-&gt;ctrl_1
op_assign
id|LLC_PDU_TYPE_S
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
id|LLC_2_PDU_RSP_RNR
suffix:semicolon
id|pdu-&gt;ctrl_2
op_assign
l_int|0
suffix:semicolon
id|pdu-&gt;ctrl_2
op_or_assign
id|f_bit
op_amp
id|LLC_S_PF_BIT_MASK
suffix:semicolon
id|pdu-&gt;ctrl_1
op_and_assign
l_int|0x0F
suffix:semicolon
multiline_comment|/* setting bits 5..8 to zero(reserved) */
id|pdu-&gt;ctrl_2
op_or_assign
(paren
id|nr
op_lshift
l_int|1
)paren
op_amp
l_int|0xFE
suffix:semicolon
multiline_comment|/* set N(R) in bits 10..16 */
)brace
multiline_comment|/**&n; *&t;llc_pdu_init_as_ua_rsp - builds UA response pdu&n; *&t;@skb: Address of the frame to build&n; *&t;@f_bit: The F bit to set in the PDU&n; *&n; *&t;Builds a pdu frame as a UA response.&n; */
DECL|function|llc_pdu_init_as_ua_rsp
r_void
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
(brace
r_struct
id|llc_pdu_un
op_star
id|pdu
op_assign
id|llc_pdu_un_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
id|pdu-&gt;ctrl_1
op_assign
id|LLC_PDU_TYPE_U
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
id|LLC_2_PDU_RSP_UA
suffix:semicolon
id|pdu-&gt;ctrl_1
op_or_assign
(paren
(paren
id|f_bit
op_amp
l_int|1
)paren
op_lshift
l_int|4
)paren
op_amp
id|LLC_U_PF_BIT_MASK
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_pdu_decode_pdu_type - designates PDU type&n; *&t;@skb: input skb that type of it must be designated.&n; *&t;@type: type of PDU (output argument).&n; *&n; *&t;This function designates type of PDU (I, S or U).&n; */
DECL|function|llc_pdu_decode_pdu_type
r_static
r_void
id|llc_pdu_decode_pdu_type
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
id|u8
op_star
id|type
)paren
(brace
r_struct
id|llc_pdu_un
op_star
id|pdu
op_assign
id|llc_pdu_un_hdr
c_func
(paren
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdu-&gt;ctrl_1
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|pdu-&gt;ctrl_1
op_amp
id|LLC_PDU_TYPE_U
)paren
op_eq
id|LLC_PDU_TYPE_U
)paren
op_star
id|type
op_assign
id|LLC_PDU_TYPE_U
suffix:semicolon
r_else
op_star
id|type
op_assign
id|LLC_PDU_TYPE_S
suffix:semicolon
)brace
r_else
op_star
id|type
op_assign
id|LLC_PDU_TYPE_I
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;llc_pdu_get_pf_bit - extracts p/f bit of input PDU&n; *&t;@pdu: pointer to LLC header.&n; *&n; *&t;This function extracts p/f bit of input PDU. at first examines type of&n; *&t;PDU and then extracts p/f bit. Returns the p/f bit.&n; */
DECL|function|llc_pdu_get_pf_bit
r_static
id|u8
id|llc_pdu_get_pf_bit
c_func
(paren
r_struct
id|llc_pdu_sn
op_star
id|pdu
)paren
(brace
id|u8
id|pdu_type
suffix:semicolon
id|u8
id|pf_bit
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pdu-&gt;ctrl_1
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
(paren
id|pdu-&gt;ctrl_1
op_amp
id|LLC_PDU_TYPE_U
)paren
op_eq
id|LLC_PDU_TYPE_U
)paren
id|pdu_type
op_assign
id|LLC_PDU_TYPE_U
suffix:semicolon
r_else
id|pdu_type
op_assign
id|LLC_PDU_TYPE_S
suffix:semicolon
)brace
r_else
id|pdu_type
op_assign
id|LLC_PDU_TYPE_I
suffix:semicolon
r_switch
c_cond
(paren
id|pdu_type
)paren
(brace
r_case
id|LLC_PDU_TYPE_I
suffix:colon
r_case
id|LLC_PDU_TYPE_S
suffix:colon
id|pf_bit
op_assign
id|pdu-&gt;ctrl_2
op_amp
id|LLC_S_PF_BIT_MASK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LLC_PDU_TYPE_U
suffix:colon
id|pf_bit
op_assign
(paren
id|pdu-&gt;ctrl_1
op_amp
id|LLC_U_PF_BIT_MASK
)paren
op_rshift
l_int|4
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|pf_bit
suffix:semicolon
)brace
eof
