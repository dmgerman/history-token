multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * xwidget.h - generic crosstalk widget header file, derived from IRIX&n; * &lt;sys/xtalk/xtalkwidget.h&gt;, revision 1.32.&n; *&n; * Copyright (C) 1996, 1999 Silcon Graphics, Inc.&n; * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#ifndef _ASM_XTALK_XWIDGET_H
DECL|macro|_ASM_XTALK_XWIDGET_H
mdefine_line|#define _ASM_XTALK_XWIDGET_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/xtalk/xtalk.h&gt;
DECL|macro|WIDGET_ID
mdefine_line|#define WIDGET_ID&t;&t;&t;0x04
DECL|macro|WIDGET_STATUS
mdefine_line|#define WIDGET_STATUS&t;&t;&t;0x0c
DECL|macro|WIDGET_ERR_UPPER_ADDR
mdefine_line|#define WIDGET_ERR_UPPER_ADDR&t;&t;0x14
DECL|macro|WIDGET_ERR_LOWER_ADDR
mdefine_line|#define WIDGET_ERR_LOWER_ADDR&t;&t;0x1c
DECL|macro|WIDGET_CONTROL
mdefine_line|#define WIDGET_CONTROL&t;&t;&t;0x24
DECL|macro|WIDGET_REQ_TIMEOUT
mdefine_line|#define WIDGET_REQ_TIMEOUT&t;&t;0x2c
DECL|macro|WIDGET_INTDEST_UPPER_ADDR
mdefine_line|#define WIDGET_INTDEST_UPPER_ADDR&t;0x34
DECL|macro|WIDGET_INTDEST_LOWER_ADDR
mdefine_line|#define WIDGET_INTDEST_LOWER_ADDR&t;0x3c
DECL|macro|WIDGET_ERR_CMD_WORD
mdefine_line|#define WIDGET_ERR_CMD_WORD&t;&t;0x44
DECL|macro|WIDGET_LLP_CFG
mdefine_line|#define WIDGET_LLP_CFG&t;&t;&t;0x4c
DECL|macro|WIDGET_TFLUSH
mdefine_line|#define WIDGET_TFLUSH&t;&t;&t;0x54
multiline_comment|/* WIDGET_ID */
DECL|macro|WIDGET_REV_NUM
mdefine_line|#define WIDGET_REV_NUM&t;&t;&t;0xf0000000
DECL|macro|WIDGET_PART_NUM
mdefine_line|#define WIDGET_PART_NUM&t;&t;&t;0x0ffff000
DECL|macro|WIDGET_MFG_NUM
mdefine_line|#define WIDGET_MFG_NUM&t;&t;&t;0x00000ffe
DECL|macro|WIDGET_REV_NUM_SHFT
mdefine_line|#define WIDGET_REV_NUM_SHFT&t;&t;28
DECL|macro|WIDGET_PART_NUM_SHFT
mdefine_line|#define WIDGET_PART_NUM_SHFT&t;&t;12
DECL|macro|WIDGET_MFG_NUM_SHFT
mdefine_line|#define WIDGET_MFG_NUM_SHFT&t;&t;1
DECL|macro|XWIDGET_PART_NUM
mdefine_line|#define XWIDGET_PART_NUM(widgetid) (((widgetid) &amp; WIDGET_PART_NUM) &gt;&gt; WIDGET_PART_NUM_SHFT)
DECL|macro|XWIDGET_REV_NUM
mdefine_line|#define XWIDGET_REV_NUM(widgetid) (((widgetid) &amp; WIDGET_REV_NUM) &gt;&gt; WIDGET_REV_NUM_SHFT)
DECL|macro|XWIDGET_MFG_NUM
mdefine_line|#define XWIDGET_MFG_NUM(widgetid) (((widgetid) &amp; WIDGET_MFG_NUM) &gt;&gt; WIDGET_MFG_NUM_SHFT)
multiline_comment|/* WIDGET_STATUS */
DECL|macro|WIDGET_LLP_REC_CNT
mdefine_line|#define WIDGET_LLP_REC_CNT&t;&t;0xff000000
DECL|macro|WIDGET_LLP_TX_CNT
mdefine_line|#define WIDGET_LLP_TX_CNT&t;&t;0x00ff0000
DECL|macro|WIDGET_PENDING
mdefine_line|#define WIDGET_PENDING&t;&t;&t;0x0000001f
multiline_comment|/* WIDGET_ERR_UPPER_ADDR */
DECL|macro|WIDGET_ERR_UPPER_ADDR_ONLY
mdefine_line|#define&t;WIDGET_ERR_UPPER_ADDR_ONLY&t;0x0000ffff
multiline_comment|/* WIDGET_CONTROL */
DECL|macro|WIDGET_F_BAD_PKT
mdefine_line|#define WIDGET_F_BAD_PKT&t;&t;0x00010000
DECL|macro|WIDGET_LLP_XBAR_CRD
mdefine_line|#define WIDGET_LLP_XBAR_CRD&t;&t;0x0000f000
DECL|macro|WIDGET_LLP_XBAR_CRD_SHFT
mdefine_line|#define&t;WIDGET_LLP_XBAR_CRD_SHFT&t;12
DECL|macro|WIDGET_CLR_RLLP_CNT
mdefine_line|#define WIDGET_CLR_RLLP_CNT&t;&t;0x00000800
DECL|macro|WIDGET_CLR_TLLP_CNT
mdefine_line|#define WIDGET_CLR_TLLP_CNT&t;&t;0x00000400
DECL|macro|WIDGET_SYS_END
mdefine_line|#define WIDGET_SYS_END&t;&t;&t;0x00000200
DECL|macro|WIDGET_MAX_TRANS
mdefine_line|#define WIDGET_MAX_TRANS&t;&t;0x000001f0
DECL|macro|WIDGET_WIDGET_ID
mdefine_line|#define WIDGET_WIDGET_ID&t;&t;0x0000000f
multiline_comment|/* WIDGET_INTDEST_UPPER_ADDR */
DECL|macro|WIDGET_INT_VECTOR
mdefine_line|#define WIDGET_INT_VECTOR&t;&t;0xff000000
DECL|macro|WIDGET_INT_VECTOR_SHFT
mdefine_line|#define WIDGET_INT_VECTOR_SHFT&t;&t;24
DECL|macro|WIDGET_TARGET_ID
mdefine_line|#define WIDGET_TARGET_ID&t;&t;0x000f0000
DECL|macro|WIDGET_TARGET_ID_SHFT
mdefine_line|#define WIDGET_TARGET_ID_SHFT&t;&t;16
DECL|macro|WIDGET_UPP_ADDR
mdefine_line|#define WIDGET_UPP_ADDR&t;&t;&t;0x0000ffff
multiline_comment|/* WIDGET_ERR_CMD_WORD */
DECL|macro|WIDGET_DIDN
mdefine_line|#define WIDGET_DIDN&t;&t;&t;0xf0000000
DECL|macro|WIDGET_SIDN
mdefine_line|#define WIDGET_SIDN&t;&t;&t;0x0f000000
DECL|macro|WIDGET_PACTYP
mdefine_line|#define WIDGET_PACTYP&t;&t;&t;0x00f00000
DECL|macro|WIDGET_TNUM
mdefine_line|#define WIDGET_TNUM&t;&t;&t;0x000f8000
DECL|macro|WIDGET_COHERENT
mdefine_line|#define WIDGET_COHERENT&t;&t;&t;0x00004000
DECL|macro|WIDGET_DS
mdefine_line|#define WIDGET_DS&t;&t;&t;0x00003000
DECL|macro|WIDGET_GBR
mdefine_line|#define WIDGET_GBR&t;&t;&t;0x00000800
DECL|macro|WIDGET_VBPM
mdefine_line|#define WIDGET_VBPM&t;&t;&t;0x00000400
DECL|macro|WIDGET_ERROR
mdefine_line|#define WIDGET_ERROR&t;&t;&t;0x00000200
DECL|macro|WIDGET_BARRIER
mdefine_line|#define WIDGET_BARRIER&t;&t;&t;0x00000100
multiline_comment|/* WIDGET_LLP_CFG */
DECL|macro|WIDGET_LLP_MAXRETRY
mdefine_line|#define WIDGET_LLP_MAXRETRY&t;&t;0x03ff0000
DECL|macro|WIDGET_LLP_MAXRETRY_SHFT
mdefine_line|#define WIDGET_LLP_MAXRETRY_SHFT&t;16
DECL|macro|WIDGET_LLP_NULLTIMEOUT
mdefine_line|#define WIDGET_LLP_NULLTIMEOUT&t;&t;0x0000fc00
DECL|macro|WIDGET_LLP_NULLTIMEOUT_SHFT
mdefine_line|#define WIDGET_LLP_NULLTIMEOUT_SHFT&t;10
DECL|macro|WIDGET_LLP_MAXBURST
mdefine_line|#define WIDGET_LLP_MAXBURST&t;&t;0x000003ff
DECL|macro|WIDGET_LLP_MAXBURST_SHFT
mdefine_line|#define WIDGET_LLP_MAXBURST_SHFT&t;0
multiline_comment|/*&n; * according to the crosstalk spec, only 32-bits access to the widget&n; * configuration registers is allowed.  some widgets may allow 64-bits&n; * access but software should not depend on it.  registers beyond the&n; * widget target flush register are widget dependent thus will not be&n; * defined here&n; */
macro_line|#if _LANGUAGE_C
DECL|typedef|widgetreg_t
r_typedef
id|u32
id|widgetreg_t
suffix:semicolon
multiline_comment|/* widget configuration registers */
DECL|struct|widget_cfg
r_typedef
r_volatile
r_struct
id|widget_cfg
(brace
DECL|member|w_pad_0
id|widgetreg_t
id|w_pad_0
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|w_id
id|widgetreg_t
id|w_id
suffix:semicolon
multiline_comment|/* 0x04 */
DECL|member|w_pad_1
id|widgetreg_t
id|w_pad_1
suffix:semicolon
multiline_comment|/* 0x08 */
DECL|member|w_status
id|widgetreg_t
id|w_status
suffix:semicolon
multiline_comment|/* 0x0c */
DECL|member|w_pad_2
id|widgetreg_t
id|w_pad_2
suffix:semicolon
multiline_comment|/* 0x10 */
DECL|member|w_err_upper_addr
id|widgetreg_t
id|w_err_upper_addr
suffix:semicolon
multiline_comment|/* 0x14 */
DECL|member|w_pad_3
id|widgetreg_t
id|w_pad_3
suffix:semicolon
multiline_comment|/* 0x18 */
DECL|member|w_err_lower_addr
id|widgetreg_t
id|w_err_lower_addr
suffix:semicolon
multiline_comment|/* 0x1c */
DECL|member|w_pad_4
id|widgetreg_t
id|w_pad_4
suffix:semicolon
multiline_comment|/* 0x20 */
DECL|member|w_control
id|widgetreg_t
id|w_control
suffix:semicolon
multiline_comment|/* 0x24 */
DECL|member|w_pad_5
id|widgetreg_t
id|w_pad_5
suffix:semicolon
multiline_comment|/* 0x28 */
DECL|member|w_req_timeout
id|widgetreg_t
id|w_req_timeout
suffix:semicolon
multiline_comment|/* 0x2c */
DECL|member|w_pad_6
id|widgetreg_t
id|w_pad_6
suffix:semicolon
multiline_comment|/* 0x30 */
DECL|member|w_intdest_upper_addr
id|widgetreg_t
id|w_intdest_upper_addr
suffix:semicolon
multiline_comment|/* 0x34 */
DECL|member|w_pad_7
id|widgetreg_t
id|w_pad_7
suffix:semicolon
multiline_comment|/* 0x38 */
DECL|member|w_intdest_lower_addr
id|widgetreg_t
id|w_intdest_lower_addr
suffix:semicolon
multiline_comment|/* 0x3c */
DECL|member|w_pad_8
id|widgetreg_t
id|w_pad_8
suffix:semicolon
multiline_comment|/* 0x40 */
DECL|member|w_err_cmd_word
id|widgetreg_t
id|w_err_cmd_word
suffix:semicolon
multiline_comment|/* 0x44 */
DECL|member|w_pad_9
id|widgetreg_t
id|w_pad_9
suffix:semicolon
multiline_comment|/* 0x48 */
DECL|member|w_llp_cfg
id|widgetreg_t
id|w_llp_cfg
suffix:semicolon
multiline_comment|/* 0x4c */
DECL|member|w_pad_10
id|widgetreg_t
id|w_pad_10
suffix:semicolon
multiline_comment|/* 0x50 */
DECL|member|w_tflush
id|widgetreg_t
id|w_tflush
suffix:semicolon
multiline_comment|/* 0x54 */
DECL|typedef|widget_cfg_t
)brace
id|widget_cfg_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|didn
r_int
id|didn
suffix:colon
l_int|4
suffix:semicolon
DECL|member|sidn
r_int
id|sidn
suffix:colon
l_int|4
suffix:semicolon
DECL|member|pactyp
r_int
id|pactyp
suffix:colon
l_int|4
suffix:semicolon
DECL|member|tnum
r_int
id|tnum
suffix:colon
l_int|5
suffix:semicolon
DECL|member|ct
r_int
id|ct
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ds
r_int
id|ds
suffix:colon
l_int|2
suffix:semicolon
DECL|member|gbr
r_int
id|gbr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vbpm
r_int
id|vbpm
suffix:colon
l_int|1
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:colon
l_int|1
suffix:semicolon
DECL|member|bo
r_int
id|bo
suffix:colon
l_int|1
suffix:semicolon
DECL|member|other
r_int
id|other
suffix:colon
l_int|8
suffix:semicolon
DECL|typedef|w_err_cmd_word_f
)brace
id|w_err_cmd_word_f
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|r
id|widgetreg_t
id|r
suffix:semicolon
DECL|member|f
id|w_err_cmd_word_f
id|f
suffix:semicolon
DECL|typedef|w_err_cmd_word_u
)brace
id|w_err_cmd_word_u
suffix:semicolon
DECL|typedef|xwidget_info_t
r_typedef
r_struct
id|xwidget_info_s
op_star
id|xwidget_info_t
suffix:semicolon
multiline_comment|/*&n; * Crosstalk Widget Hardware Identification, as defined in the Crosstalk spec.&n; */
DECL|struct|xwidget_hwid_s
r_typedef
r_struct
id|xwidget_hwid_s
(brace
DECL|member|part_num
id|xwidget_part_num_t
id|part_num
suffix:semicolon
DECL|member|rev_num
id|xwidget_rev_num_t
id|rev_num
suffix:semicolon
DECL|member|mfg_num
id|xwidget_mfg_num_t
id|mfg_num
suffix:semicolon
DECL|typedef|xwidget_hwid_t
)brace
op_star
id|xwidget_hwid_t
suffix:semicolon
multiline_comment|/*&n; * Returns 1 if a driver that handles devices described by hwid1 is able&n; * to manage a device with hardwareid hwid2.  NOTE: We don&squot;t check rev&n; * numbers at all.&n; */
DECL|macro|XWIDGET_HARDWARE_ID_MATCH
mdefine_line|#define XWIDGET_HARDWARE_ID_MATCH(hwid1, hwid2) &bslash;&n;&t;(((hwid1)-&gt;part_num == (hwid2)-&gt;part_num) &amp;&amp; &bslash;&n;&t;(((hwid1)-&gt;mfg_num == XWIDGET_MFG_NUM_NONE) || &bslash;&n;&t;((hwid2)-&gt;mfg_num == XWIDGET_MFG_NUM_NONE) || &bslash;&n;&t;((hwid1)-&gt;mfg_num == (hwid2)-&gt;mfg_num)))
macro_line|#endif&t;&t;&t;&t;/* _LANGUAGE_C */
macro_line|#endif /* _ASM_XTALK_XWIDGET_H */
eof
