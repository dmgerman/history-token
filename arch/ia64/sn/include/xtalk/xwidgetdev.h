multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997,2000-2003 Silicon Graphics, Inc. All Rights Reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_XTALK_XWIDGET_H
DECL|macro|_ASM_IA64_SN_XTALK_XWIDGET_H
mdefine_line|#define _ASM_IA64_SN_XTALK_XWIDGET_H
multiline_comment|/* WIDGET_ID */
DECL|macro|WIDGET_REV_NUM
mdefine_line|#define WIDGET_REV_NUM                  0xf0000000
DECL|macro|WIDGET_PART_NUM
mdefine_line|#define WIDGET_PART_NUM                 0x0ffff000
DECL|macro|WIDGET_MFG_NUM
mdefine_line|#define WIDGET_MFG_NUM                  0x00000ffe
DECL|macro|WIDGET_REV_NUM_SHFT
mdefine_line|#define WIDGET_REV_NUM_SHFT             28
DECL|macro|WIDGET_PART_NUM_SHFT
mdefine_line|#define WIDGET_PART_NUM_SHFT            12
DECL|macro|WIDGET_MFG_NUM_SHFT
mdefine_line|#define WIDGET_MFG_NUM_SHFT             1
DECL|macro|XWIDGET_PART_NUM
mdefine_line|#define XWIDGET_PART_NUM(widgetid) (((widgetid) &amp; WIDGET_PART_NUM) &gt;&gt; WIDGET_PART_NUM_SHFT)
DECL|macro|XWIDGET_REV_NUM
mdefine_line|#define XWIDGET_REV_NUM(widgetid) (((widgetid) &amp; WIDGET_REV_NUM) &gt;&gt; WIDGET_REV_NUM_SHFT)
DECL|macro|XWIDGET_MFG_NUM
mdefine_line|#define XWIDGET_MFG_NUM(widgetid) (((widgetid) &amp; WIDGET_MFG_NUM) &gt;&gt; WIDGET_MFG_NUM_SHFT)
DECL|macro|XWIDGET_PART_REV_NUM
mdefine_line|#define XWIDGET_PART_REV_NUM(widgetid) ((XWIDGET_PART_NUM(widgetid) &lt;&lt; 4) | &bslash;&n;                                        XWIDGET_REV_NUM(widgetid))
DECL|macro|XWIDGET_PART_REV_NUM_REV
mdefine_line|#define XWIDGET_PART_REV_NUM_REV(partrev) (partrev &amp; 0xf)
multiline_comment|/* widget configuration registers */
DECL|struct|widget_cfg
r_struct
id|widget_cfg
(brace
DECL|member|w_id
r_uint32
id|w_id
suffix:semicolon
multiline_comment|/* 0x04 */
DECL|member|w_pad_0
r_uint32
id|w_pad_0
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|w_status
r_uint32
id|w_status
suffix:semicolon
multiline_comment|/* 0x0c */
DECL|member|w_pad_1
r_uint32
id|w_pad_1
suffix:semicolon
multiline_comment|/* 0x08 */
DECL|member|w_err_upper_addr
r_uint32
id|w_err_upper_addr
suffix:semicolon
multiline_comment|/* 0x14 */
DECL|member|w_pad_2
r_uint32
id|w_pad_2
suffix:semicolon
multiline_comment|/* 0x10 */
DECL|member|w_err_lower_addr
r_uint32
id|w_err_lower_addr
suffix:semicolon
multiline_comment|/* 0x1c */
DECL|member|w_pad_3
r_uint32
id|w_pad_3
suffix:semicolon
multiline_comment|/* 0x18 */
DECL|member|w_control
r_uint32
id|w_control
suffix:semicolon
multiline_comment|/* 0x24 */
DECL|member|w_pad_4
r_uint32
id|w_pad_4
suffix:semicolon
multiline_comment|/* 0x20 */
DECL|member|w_req_timeout
r_uint32
id|w_req_timeout
suffix:semicolon
multiline_comment|/* 0x2c */
DECL|member|w_pad_5
r_uint32
id|w_pad_5
suffix:semicolon
multiline_comment|/* 0x28 */
DECL|member|w_intdest_upper_addr
r_uint32
id|w_intdest_upper_addr
suffix:semicolon
multiline_comment|/* 0x34 */
DECL|member|w_pad_6
r_uint32
id|w_pad_6
suffix:semicolon
multiline_comment|/* 0x30 */
DECL|member|w_intdest_lower_addr
r_uint32
id|w_intdest_lower_addr
suffix:semicolon
multiline_comment|/* 0x3c */
DECL|member|w_pad_7
r_uint32
id|w_pad_7
suffix:semicolon
multiline_comment|/* 0x38 */
DECL|member|w_err_cmd_word
r_uint32
id|w_err_cmd_word
suffix:semicolon
multiline_comment|/* 0x44 */
DECL|member|w_pad_8
r_uint32
id|w_pad_8
suffix:semicolon
multiline_comment|/* 0x40 */
DECL|member|w_llp_cfg
r_uint32
id|w_llp_cfg
suffix:semicolon
multiline_comment|/* 0x4c */
DECL|member|w_pad_9
r_uint32
id|w_pad_9
suffix:semicolon
multiline_comment|/* 0x48 */
DECL|member|w_tflush
r_uint32
id|w_tflush
suffix:semicolon
multiline_comment|/* 0x54 */
DECL|member|w_pad_10
r_uint32
id|w_pad_10
suffix:semicolon
multiline_comment|/* 0x50 */
)brace
suffix:semicolon
multiline_comment|/*&n; * Crosstalk Widget Hardware Identification, as defined in the Crosstalk spec.&n; */
DECL|struct|xwidget_hwid
r_struct
id|xwidget_hwid
(brace
DECL|member|mfg_num
r_int
id|mfg_num
suffix:semicolon
DECL|member|rev_num
r_int
id|rev_num
suffix:semicolon
DECL|member|part_num
r_int
id|part_num
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xwidget_info
r_struct
id|xwidget_info
(brace
DECL|member|xwi_hwid
r_struct
id|xwidget_hwid
id|xwi_hwid
suffix:semicolon
multiline_comment|/* Widget Identification */
DECL|member|xwi_masterxid
r_char
id|xwi_masterxid
suffix:semicolon
multiline_comment|/* Hub&squot;s Widget Port Number */
DECL|member|xwi_hubinfo
r_void
op_star
id|xwi_hubinfo
suffix:semicolon
multiline_comment|/* Hub&squot;s provider private info */
DECL|member|xwi_hub_provider
r_uint64
op_star
id|xwi_hub_provider
suffix:semicolon
multiline_comment|/* prom provider functions */
DECL|member|xwi_vertex
r_void
op_star
id|xwi_vertex
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif                          /* _ASM_IA64_SN_XTALK_XWIDGET_H */
eof
