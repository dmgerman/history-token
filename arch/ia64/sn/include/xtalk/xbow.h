multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997,2000-2004 Silicon Graphics, Inc. All Rights Reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_XTALK_XBOW_H
DECL|macro|_ASM_IA64_SN_XTALK_XBOW_H
mdefine_line|#define _ASM_IA64_SN_XTALK_XBOW_H
DECL|macro|XBOW_PORT_8
mdefine_line|#define XBOW_PORT_8&t;0x8
DECL|macro|XBOW_PORT_C
mdefine_line|#define XBOW_PORT_C&t;0xc
DECL|macro|XBOW_PORT_F
mdefine_line|#define XBOW_PORT_F&t;0xf
DECL|macro|MAX_XBOW_PORTS
mdefine_line|#define MAX_XBOW_PORTS&t;8&t;/* number of ports on xbow chip */
DECL|macro|BASE_XBOW_PORT
mdefine_line|#define BASE_XBOW_PORT&t;XBOW_PORT_8&t;/* Lowest external port */
DECL|macro|XBOW_CREDIT
mdefine_line|#define&t;XBOW_CREDIT&t;4
DECL|macro|MAX_XBOW_NAME
mdefine_line|#define MAX_XBOW_NAME &t;16
multiline_comment|/* Register set for each xbow link */
DECL|struct|xb_linkregs_s
r_typedef
r_volatile
r_struct
id|xb_linkregs_s
(brace
multiline_comment|/* &n; * we access these through synergy unswizzled space, so the address&n; * gets twiddled (i.e. references to 0x4 actually go to 0x0 and vv.)&n; * That&squot;s why we put the register first and filler second.&n; */
DECL|member|link_ibf
r_uint32
id|link_ibf
suffix:semicolon
DECL|member|filler0
r_uint32
id|filler0
suffix:semicolon
multiline_comment|/* filler for proper alignment */
DECL|member|link_control
r_uint32
id|link_control
suffix:semicolon
DECL|member|filler1
r_uint32
id|filler1
suffix:semicolon
DECL|member|link_status
r_uint32
id|link_status
suffix:semicolon
DECL|member|filler2
r_uint32
id|filler2
suffix:semicolon
DECL|member|link_arb_upper
r_uint32
id|link_arb_upper
suffix:semicolon
DECL|member|filler3
r_uint32
id|filler3
suffix:semicolon
DECL|member|link_arb_lower
r_uint32
id|link_arb_lower
suffix:semicolon
DECL|member|filler4
r_uint32
id|filler4
suffix:semicolon
DECL|member|link_status_clr
r_uint32
id|link_status_clr
suffix:semicolon
DECL|member|filler5
r_uint32
id|filler5
suffix:semicolon
DECL|member|link_reset
r_uint32
id|link_reset
suffix:semicolon
DECL|member|filler6
r_uint32
id|filler6
suffix:semicolon
DECL|member|link_aux_status
r_uint32
id|link_aux_status
suffix:semicolon
DECL|member|filler7
r_uint32
id|filler7
suffix:semicolon
DECL|typedef|xb_linkregs_t
)brace
id|xb_linkregs_t
suffix:semicolon
DECL|struct|xbow_s
r_typedef
r_volatile
r_struct
id|xbow_s
(brace
multiline_comment|/* standard widget configuration                       0x000000-0x000057 */
DECL|member|xb_widget
r_struct
id|widget_cfg
id|xb_widget
suffix:semicolon
multiline_comment|/* 0x000000 */
multiline_comment|/* helper fieldnames for accessing bridge widget */
DECL|macro|xb_wid_id
mdefine_line|#define xb_wid_id                       xb_widget.w_id
DECL|macro|xb_wid_stat
mdefine_line|#define xb_wid_stat                     xb_widget.w_status
DECL|macro|xb_wid_err_upper
mdefine_line|#define xb_wid_err_upper                xb_widget.w_err_upper_addr
DECL|macro|xb_wid_err_lower
mdefine_line|#define xb_wid_err_lower                xb_widget.w_err_lower_addr
DECL|macro|xb_wid_control
mdefine_line|#define xb_wid_control                  xb_widget.w_control
DECL|macro|xb_wid_req_timeout
mdefine_line|#define xb_wid_req_timeout              xb_widget.w_req_timeout
DECL|macro|xb_wid_int_upper
mdefine_line|#define xb_wid_int_upper                xb_widget.w_intdest_upper_addr
DECL|macro|xb_wid_int_lower
mdefine_line|#define xb_wid_int_lower                xb_widget.w_intdest_lower_addr
DECL|macro|xb_wid_err_cmdword
mdefine_line|#define xb_wid_err_cmdword              xb_widget.w_err_cmd_word
DECL|macro|xb_wid_llp
mdefine_line|#define xb_wid_llp                      xb_widget.w_llp_cfg
DECL|macro|xb_wid_stat_clr
mdefine_line|#define xb_wid_stat_clr                 xb_widget.w_tflush
multiline_comment|/* &n; * we access these through synergy unswizzled space, so the address&n; * gets twiddled (i.e. references to 0x4 actually go to 0x0 and vv.)&n; * That&squot;s why we put the register first and filler second.&n; */
multiline_comment|/* xbow-specific widget configuration                  0x000058-0x0000FF */
DECL|member|xb_wid_arb_reload
r_uint32
id|xb_wid_arb_reload
suffix:semicolon
multiline_comment|/* 0x00005C */
DECL|member|_pad_000058
r_uint32
id|_pad_000058
suffix:semicolon
DECL|member|xb_perf_ctr_a
r_uint32
id|xb_perf_ctr_a
suffix:semicolon
multiline_comment|/* 0x000064 */
DECL|member|_pad_000060
r_uint32
id|_pad_000060
suffix:semicolon
DECL|member|xb_perf_ctr_b
r_uint32
id|xb_perf_ctr_b
suffix:semicolon
multiline_comment|/* 0x00006c */
DECL|member|_pad_000068
r_uint32
id|_pad_000068
suffix:semicolon
DECL|member|xb_nic
r_uint32
id|xb_nic
suffix:semicolon
multiline_comment|/* 0x000074 */
DECL|member|_pad_000070
r_uint32
id|_pad_000070
suffix:semicolon
multiline_comment|/* Xbridge only */
DECL|member|xb_w0_rst_fnc
r_uint32
id|xb_w0_rst_fnc
suffix:semicolon
multiline_comment|/* 0x00007C */
DECL|member|_pad_000078
r_uint32
id|_pad_000078
suffix:semicolon
DECL|member|xb_l8_rst_fnc
r_uint32
id|xb_l8_rst_fnc
suffix:semicolon
multiline_comment|/* 0x000084 */
DECL|member|_pad_000080
r_uint32
id|_pad_000080
suffix:semicolon
DECL|member|xb_l9_rst_fnc
r_uint32
id|xb_l9_rst_fnc
suffix:semicolon
multiline_comment|/* 0x00008c */
DECL|member|_pad_000088
r_uint32
id|_pad_000088
suffix:semicolon
DECL|member|xb_la_rst_fnc
r_uint32
id|xb_la_rst_fnc
suffix:semicolon
multiline_comment|/* 0x000094 */
DECL|member|_pad_000090
r_uint32
id|_pad_000090
suffix:semicolon
DECL|member|xb_lb_rst_fnc
r_uint32
id|xb_lb_rst_fnc
suffix:semicolon
multiline_comment|/* 0x00009c */
DECL|member|_pad_000098
r_uint32
id|_pad_000098
suffix:semicolon
DECL|member|xb_lc_rst_fnc
r_uint32
id|xb_lc_rst_fnc
suffix:semicolon
multiline_comment|/* 0x0000a4 */
DECL|member|_pad_0000a0
r_uint32
id|_pad_0000a0
suffix:semicolon
DECL|member|xb_ld_rst_fnc
r_uint32
id|xb_ld_rst_fnc
suffix:semicolon
multiline_comment|/* 0x0000ac */
DECL|member|_pad_0000a8
r_uint32
id|_pad_0000a8
suffix:semicolon
DECL|member|xb_le_rst_fnc
r_uint32
id|xb_le_rst_fnc
suffix:semicolon
multiline_comment|/* 0x0000b4 */
DECL|member|_pad_0000b0
r_uint32
id|_pad_0000b0
suffix:semicolon
DECL|member|xb_lf_rst_fnc
r_uint32
id|xb_lf_rst_fnc
suffix:semicolon
multiline_comment|/* 0x0000bc */
DECL|member|_pad_0000b8
r_uint32
id|_pad_0000b8
suffix:semicolon
DECL|member|xb_lock
r_uint32
id|xb_lock
suffix:semicolon
multiline_comment|/* 0x0000c4 */
DECL|member|_pad_0000c0
r_uint32
id|_pad_0000c0
suffix:semicolon
DECL|member|xb_lock_clr
r_uint32
id|xb_lock_clr
suffix:semicolon
multiline_comment|/* 0x0000cc */
DECL|member|_pad_0000c8
r_uint32
id|_pad_0000c8
suffix:semicolon
multiline_comment|/* end of Xbridge only */
DECL|member|_pad_0000d0
r_uint32
id|_pad_0000d0
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* Link Specific Registers, port 8..15                 0x000100-0x000300 */
DECL|member|xb_link_raw
id|xb_linkregs_t
id|xb_link_raw
(braket
id|MAX_XBOW_PORTS
)braket
suffix:semicolon
DECL|macro|xb_link
mdefine_line|#define xb_link(p)      xb_link_raw[(p) &amp; (MAX_XBOW_PORTS - 1)]
DECL|typedef|xbow_t
)brace
id|xbow_t
suffix:semicolon
DECL|macro|XB_FLAGS_EXISTS
mdefine_line|#define XB_FLAGS_EXISTS&t;&t;0x1&t;/* device exists */
DECL|macro|XB_FLAGS_MASTER
mdefine_line|#define XB_FLAGS_MASTER&t;&t;0x2
DECL|macro|XB_FLAGS_SLAVE
mdefine_line|#define XB_FLAGS_SLAVE&t;&t;0x0
DECL|macro|XB_FLAGS_GBR
mdefine_line|#define XB_FLAGS_GBR&t;&t;0x4
DECL|macro|XB_FLAGS_16BIT
mdefine_line|#define XB_FLAGS_16BIT&t;&t;0x8
DECL|macro|XB_FLAGS_8BIT
mdefine_line|#define XB_FLAGS_8BIT&t;&t;0x0
multiline_comment|/* is widget port number valid?  (based on version 7.0 of xbow spec) */
DECL|macro|XBOW_WIDGET_IS_VALID
mdefine_line|#define XBOW_WIDGET_IS_VALID(wid) ((wid) &gt;= XBOW_PORT_8 &amp;&amp; (wid) &lt;= XBOW_PORT_F)
multiline_comment|/* whether to use upper or lower arbitration register, given source widget id */
DECL|macro|XBOW_ARB_IS_UPPER
mdefine_line|#define XBOW_ARB_IS_UPPER(wid) &t;((wid) &gt;= XBOW_PORT_8 &amp;&amp; (wid) &lt;= XBOW_PORT_B)
DECL|macro|XBOW_ARB_IS_LOWER
mdefine_line|#define XBOW_ARB_IS_LOWER(wid) &t;((wid) &gt;= XBOW_PORT_C &amp;&amp; (wid) &lt;= XBOW_PORT_F)
multiline_comment|/* offset of arbitration register, given source widget id */
DECL|macro|XBOW_ARB_OFF
mdefine_line|#define XBOW_ARB_OFF(wid) &t;(XBOW_ARB_IS_UPPER(wid) ? 0x1c : 0x24)
DECL|macro|XBOW_WID_ID
mdefine_line|#define&t;XBOW_WID_ID&t;&t;WIDGET_ID
DECL|macro|XBOW_WID_STAT
mdefine_line|#define&t;XBOW_WID_STAT&t;&t;WIDGET_STATUS
DECL|macro|XBOW_WID_ERR_UPPER
mdefine_line|#define&t;XBOW_WID_ERR_UPPER&t;WIDGET_ERR_UPPER_ADDR
DECL|macro|XBOW_WID_ERR_LOWER
mdefine_line|#define&t;XBOW_WID_ERR_LOWER&t;WIDGET_ERR_LOWER_ADDR
DECL|macro|XBOW_WID_CONTROL
mdefine_line|#define&t;XBOW_WID_CONTROL&t;WIDGET_CONTROL
DECL|macro|XBOW_WID_REQ_TO
mdefine_line|#define&t;XBOW_WID_REQ_TO&t;&t;WIDGET_REQ_TIMEOUT
DECL|macro|XBOW_WID_INT_UPPER
mdefine_line|#define&t;XBOW_WID_INT_UPPER&t;WIDGET_INTDEST_UPPER_ADDR
DECL|macro|XBOW_WID_INT_LOWER
mdefine_line|#define&t;XBOW_WID_INT_LOWER&t;WIDGET_INTDEST_LOWER_ADDR
DECL|macro|XBOW_WID_ERR_CMDWORD
mdefine_line|#define&t;XBOW_WID_ERR_CMDWORD&t;WIDGET_ERR_CMD_WORD
DECL|macro|XBOW_WID_LLP
mdefine_line|#define&t;XBOW_WID_LLP&t;&t;WIDGET_LLP_CFG
DECL|macro|XBOW_WID_STAT_CLR
mdefine_line|#define&t;XBOW_WID_STAT_CLR&t;WIDGET_TFLUSH
DECL|macro|XBOW_WID_ARB_RELOAD
mdefine_line|#define XBOW_WID_ARB_RELOAD &t;0x5c
DECL|macro|XBOW_WID_PERF_CTR_A
mdefine_line|#define XBOW_WID_PERF_CTR_A &t;0x64
DECL|macro|XBOW_WID_PERF_CTR_B
mdefine_line|#define XBOW_WID_PERF_CTR_B &t;0x6c
DECL|macro|XBOW_WID_NIC
mdefine_line|#define XBOW_WID_NIC &t;&t;0x74
multiline_comment|/* Xbridge only */
DECL|macro|XBOW_W0_RST_FNC
mdefine_line|#define XBOW_W0_RST_FNC&t;&t;0x00007C
DECL|macro|XBOW_L8_RST_FNC
mdefine_line|#define&t;XBOW_L8_RST_FNC&t;&t;0x000084
DECL|macro|XBOW_L9_RST_FNC
mdefine_line|#define&t;XBOW_L9_RST_FNC&t;&t;0x00008c
DECL|macro|XBOW_LA_RST_FNC
mdefine_line|#define&t;XBOW_LA_RST_FNC&t;&t;0x000094
DECL|macro|XBOW_LB_RST_FNC
mdefine_line|#define&t;XBOW_LB_RST_FNC&t;&t;0x00009c
DECL|macro|XBOW_LC_RST_FNC
mdefine_line|#define&t;XBOW_LC_RST_FNC&t;&t;0x0000a4
DECL|macro|XBOW_LD_RST_FNC
mdefine_line|#define&t;XBOW_LD_RST_FNC&t;&t;0x0000ac
DECL|macro|XBOW_LE_RST_FNC
mdefine_line|#define&t;XBOW_LE_RST_FNC&t;&t;0x0000b4
DECL|macro|XBOW_LF_RST_FNC
mdefine_line|#define&t;XBOW_LF_RST_FNC&t;&t;0x0000bc
DECL|macro|XBOW_RESET_FENCE
mdefine_line|#define XBOW_RESET_FENCE(x) ((x) &gt; 7 &amp;&amp; (x) &lt; 16) ? &bslash;&n;&t;&t;&t;&t;(XBOW_W0_RST_FNC + ((x) - 7) * 8) : &bslash;&n;&t;&t;&t;&t;((x) == 0) ? XBOW_W0_RST_FNC : 0
DECL|macro|XBOW_LOCK
mdefine_line|#define XBOW_LOCK&t;&t;0x0000c4
DECL|macro|XBOW_LOCK_CLR
mdefine_line|#define XBOW_LOCK_CLR&t;&t;0x0000cc
multiline_comment|/* End of Xbridge only */
multiline_comment|/* used only in ide, but defined here within the reserved portion */
multiline_comment|/*              of the widget0 address space (before 0xf4) */
DECL|macro|XBOW_WID_UNDEF
mdefine_line|#define&t;XBOW_WID_UNDEF&t;&t;0xe4
multiline_comment|/* xbow link register set base, legal value for x is 0x8..0xf */
DECL|macro|XB_LINK_BASE
mdefine_line|#define&t;XB_LINK_BASE&t;&t;0x100
DECL|macro|XB_LINK_OFFSET
mdefine_line|#define&t;XB_LINK_OFFSET&t;&t;0x40
DECL|macro|XB_LINK_REG_BASE
mdefine_line|#define&t;XB_LINK_REG_BASE(x)&t;(XB_LINK_BASE + ((x) &amp; (MAX_XBOW_PORTS - 1)) * XB_LINK_OFFSET)
DECL|macro|XB_LINK_IBUF_FLUSH
mdefine_line|#define&t;XB_LINK_IBUF_FLUSH(x)&t;(XB_LINK_REG_BASE(x) + 0x4)
DECL|macro|XB_LINK_CTRL
mdefine_line|#define&t;XB_LINK_CTRL(x)&t;&t;(XB_LINK_REG_BASE(x) + 0xc)
DECL|macro|XB_LINK_STATUS
mdefine_line|#define&t;XB_LINK_STATUS(x)&t;(XB_LINK_REG_BASE(x) + 0x14)
DECL|macro|XB_LINK_ARB_UPPER
mdefine_line|#define&t;XB_LINK_ARB_UPPER(x)&t;(XB_LINK_REG_BASE(x) + 0x1c)
DECL|macro|XB_LINK_ARB_LOWER
mdefine_line|#define&t;XB_LINK_ARB_LOWER(x)&t;(XB_LINK_REG_BASE(x) + 0x24)
DECL|macro|XB_LINK_STATUS_CLR
mdefine_line|#define&t;XB_LINK_STATUS_CLR(x)&t;(XB_LINK_REG_BASE(x) + 0x2c)
DECL|macro|XB_LINK_RESET
mdefine_line|#define&t;XB_LINK_RESET(x)&t;(XB_LINK_REG_BASE(x) + 0x34)
DECL|macro|XB_LINK_AUX_STATUS
mdefine_line|#define&t;XB_LINK_AUX_STATUS(x)&t;(XB_LINK_REG_BASE(x) + 0x3c)
multiline_comment|/* link_control(x) */
DECL|macro|XB_CTRL_LINKALIVE_IE
mdefine_line|#define&t;XB_CTRL_LINKALIVE_IE&t;&t;0x80000000&t;/* link comes alive */
multiline_comment|/* reserved:&t;&t;&t;0x40000000 */
DECL|macro|XB_CTRL_PERF_CTR_MODE_MSK
mdefine_line|#define&t;XB_CTRL_PERF_CTR_MODE_MSK&t;0x30000000&t;/* perf counter mode */
DECL|macro|XB_CTRL_IBUF_LEVEL_MSK
mdefine_line|#define&t;XB_CTRL_IBUF_LEVEL_MSK&t;&t;0x0e000000&t;/* input packet buffer level */
DECL|macro|XB_CTRL_8BIT_MODE
mdefine_line|#define&t;XB_CTRL_8BIT_MODE&t;&t;0x01000000&t;/* force link into 8 bit mode */
DECL|macro|XB_CTRL_BAD_LLP_PKT
mdefine_line|#define XB_CTRL_BAD_LLP_PKT&t;&t;0x00800000&t;/* force bad LLP packet */
DECL|macro|XB_CTRL_WIDGET_CR_MSK
mdefine_line|#define XB_CTRL_WIDGET_CR_MSK&t;&t;0x007c0000&t;/* LLP widget credit mask */
DECL|macro|XB_CTRL_WIDGET_CR_SHFT
mdefine_line|#define XB_CTRL_WIDGET_CR_SHFT&t;18&t;&t;&t;/* LLP widget credit shift */
DECL|macro|XB_CTRL_ILLEGAL_DST_IE
mdefine_line|#define XB_CTRL_ILLEGAL_DST_IE&t;&t;0x00020000&t;/* illegal destination */
DECL|macro|XB_CTRL_OALLOC_IBUF_IE
mdefine_line|#define XB_CTRL_OALLOC_IBUF_IE&t;&t;0x00010000&t;/* overallocated input buffer */
multiline_comment|/* reserved:&t;&t;&t;0x0000fe00 */
DECL|macro|XB_CTRL_BNDWDTH_ALLOC_IE
mdefine_line|#define XB_CTRL_BNDWDTH_ALLOC_IE&t;0x00000100&t;/* bandwidth alloc */
DECL|macro|XB_CTRL_RCV_CNT_OFLOW_IE
mdefine_line|#define XB_CTRL_RCV_CNT_OFLOW_IE&t;0x00000080&t;/* rcv retry overflow */
DECL|macro|XB_CTRL_XMT_CNT_OFLOW_IE
mdefine_line|#define XB_CTRL_XMT_CNT_OFLOW_IE&t;0x00000040&t;/* xmt retry overflow */
DECL|macro|XB_CTRL_XMT_MAX_RTRY_IE
mdefine_line|#define XB_CTRL_XMT_MAX_RTRY_IE&t;&t;0x00000020&t;/* max transmit retry */
DECL|macro|XB_CTRL_RCV_IE
mdefine_line|#define XB_CTRL_RCV_IE&t;&t;&t;0x00000010&t;/* receive */
DECL|macro|XB_CTRL_XMT_RTRY_IE
mdefine_line|#define XB_CTRL_XMT_RTRY_IE&t;&t;0x00000008&t;/* transmit retry */
multiline_comment|/* reserved:&t;&t;&t;0x00000004 */
DECL|macro|XB_CTRL_MAXREQ_TOUT_IE
mdefine_line|#define&t;XB_CTRL_MAXREQ_TOUT_IE&t;&t;0x00000002&t;/* maximum request timeout */
DECL|macro|XB_CTRL_SRC_TOUT_IE
mdefine_line|#define&t;XB_CTRL_SRC_TOUT_IE&t;&t;0x00000001&t;/* source timeout */
multiline_comment|/* link_status(x) */
DECL|macro|XB_STAT_LINKALIVE
mdefine_line|#define&t;XB_STAT_LINKALIVE&t;&t;XB_CTRL_LINKALIVE_IE
multiline_comment|/* reserved:&t;&t;&t;0x7ff80000 */
DECL|macro|XB_STAT_MULTI_ERR
mdefine_line|#define&t;XB_STAT_MULTI_ERR&t;&t;0x00040000&t;/* multi error */
DECL|macro|XB_STAT_ILLEGAL_DST_ERR
mdefine_line|#define&t;XB_STAT_ILLEGAL_DST_ERR&t;&t;XB_CTRL_ILLEGAL_DST_IE
DECL|macro|XB_STAT_OALLOC_IBUF_ERR
mdefine_line|#define&t;XB_STAT_OALLOC_IBUF_ERR&t;&t;XB_CTRL_OALLOC_IBUF_IE
DECL|macro|XB_STAT_BNDWDTH_ALLOC_ID_MSK
mdefine_line|#define&t;XB_STAT_BNDWDTH_ALLOC_ID_MSK&t;0x0000ff00&t;/* port bitmask */
DECL|macro|XB_STAT_RCV_CNT_OFLOW_ERR
mdefine_line|#define&t;XB_STAT_RCV_CNT_OFLOW_ERR&t;XB_CTRL_RCV_CNT_OFLOW_IE
DECL|macro|XB_STAT_XMT_CNT_OFLOW_ERR
mdefine_line|#define&t;XB_STAT_XMT_CNT_OFLOW_ERR&t;XB_CTRL_XMT_CNT_OFLOW_IE
DECL|macro|XB_STAT_XMT_MAX_RTRY_ERR
mdefine_line|#define&t;XB_STAT_XMT_MAX_RTRY_ERR&t;XB_CTRL_XMT_MAX_RTRY_IE
DECL|macro|XB_STAT_RCV_ERR
mdefine_line|#define&t;XB_STAT_RCV_ERR&t;&t;&t;XB_CTRL_RCV_IE
DECL|macro|XB_STAT_XMT_RTRY_ERR
mdefine_line|#define&t;XB_STAT_XMT_RTRY_ERR&t;&t;XB_CTRL_XMT_RTRY_IE
multiline_comment|/* reserved:&t;&t;&t;0x00000004 */
DECL|macro|XB_STAT_MAXREQ_TOUT_ERR
mdefine_line|#define&t;XB_STAT_MAXREQ_TOUT_ERR&t;&t;XB_CTRL_MAXREQ_TOUT_IE
DECL|macro|XB_STAT_SRC_TOUT_ERR
mdefine_line|#define&t;XB_STAT_SRC_TOUT_ERR&t;&t;XB_CTRL_SRC_TOUT_IE
multiline_comment|/* link_aux_status(x) */
DECL|macro|XB_AUX_STAT_RCV_CNT
mdefine_line|#define&t;XB_AUX_STAT_RCV_CNT&t;0xff000000
DECL|macro|XB_AUX_STAT_XMT_CNT
mdefine_line|#define&t;XB_AUX_STAT_XMT_CNT&t;0x00ff0000
DECL|macro|XB_AUX_STAT_TOUT_DST
mdefine_line|#define&t;XB_AUX_STAT_TOUT_DST&t;0x0000ff00
DECL|macro|XB_AUX_LINKFAIL_RST_BAD
mdefine_line|#define&t;XB_AUX_LINKFAIL_RST_BAD&t;0x00000040
DECL|macro|XB_AUX_STAT_PRESENT
mdefine_line|#define&t;XB_AUX_STAT_PRESENT&t;0x00000020
DECL|macro|XB_AUX_STAT_PORT_WIDTH
mdefine_line|#define&t;XB_AUX_STAT_PORT_WIDTH&t;0x00000010
multiline_comment|/*&t;reserved:&t;&t;0x0000000f */
multiline_comment|/*&n; * link_arb_upper/link_arb_lower(x), (reg) should be the link_arb_upper&n; * register if (x) is 0x8..0xb, link_arb_lower if (x) is 0xc..0xf&n; */
DECL|macro|XB_ARB_GBR_MSK
mdefine_line|#define&t;XB_ARB_GBR_MSK&t;&t;0x1f
DECL|macro|XB_ARB_RR_MSK
mdefine_line|#define&t;XB_ARB_RR_MSK&t;&t;0x7
DECL|macro|XB_ARB_GBR_SHFT
mdefine_line|#define&t;XB_ARB_GBR_SHFT(x)&t;(((x) &amp; 0x3) * 8)
DECL|macro|XB_ARB_RR_SHFT
mdefine_line|#define&t;XB_ARB_RR_SHFT(x)&t;(((x) &amp; 0x3) * 8 + 5)
DECL|macro|XB_ARB_GBR_CNT
mdefine_line|#define&t;XB_ARB_GBR_CNT(reg,x)&t;((reg) &gt;&gt; XB_ARB_GBR_SHFT(x) &amp; XB_ARB_GBR_MSK)
DECL|macro|XB_ARB_RR_CNT
mdefine_line|#define&t;XB_ARB_RR_CNT(reg,x)&t;((reg) &gt;&gt; XB_ARB_RR_SHFT(x) &amp; XB_ARB_RR_MSK)
multiline_comment|/* XBOW_WID_STAT */
DECL|macro|XB_WID_STAT_LINK_INTR_SHFT
mdefine_line|#define&t;XB_WID_STAT_LINK_INTR_SHFT&t;(24)
DECL|macro|XB_WID_STAT_LINK_INTR_MASK
mdefine_line|#define&t;XB_WID_STAT_LINK_INTR_MASK&t;(0xFF &lt;&lt; XB_WID_STAT_LINK_INTR_SHFT)
DECL|macro|XB_WID_STAT_LINK_INTR
mdefine_line|#define&t;XB_WID_STAT_LINK_INTR(x)&t;(0x1 &lt;&lt; (((x)&amp;7) + XB_WID_STAT_LINK_INTR_SHFT))
DECL|macro|XB_WID_STAT_WIDGET0_INTR
mdefine_line|#define&t;XB_WID_STAT_WIDGET0_INTR&t;0x00800000
DECL|macro|XB_WID_STAT_SRCID_MASK
mdefine_line|#define XB_WID_STAT_SRCID_MASK&t;&t;0x000003c0&t;/* Xbridge only */
DECL|macro|XB_WID_STAT_REG_ACC_ERR
mdefine_line|#define&t;XB_WID_STAT_REG_ACC_ERR&t;&t;0x00000020
DECL|macro|XB_WID_STAT_RECV_TOUT
mdefine_line|#define XB_WID_STAT_RECV_TOUT&t;&t;0x00000010&t;/* Xbridge only */
DECL|macro|XB_WID_STAT_ARB_TOUT
mdefine_line|#define XB_WID_STAT_ARB_TOUT&t;&t;0x00000008&t;/* Xbridge only */
DECL|macro|XB_WID_STAT_XTALK_ERR
mdefine_line|#define&t;XB_WID_STAT_XTALK_ERR&t;&t;0x00000004
DECL|macro|XB_WID_STAT_DST_TOUT
mdefine_line|#define XB_WID_STAT_DST_TOUT&t;&t;0x00000002&t;/* Xbridge only */
DECL|macro|XB_WID_STAT_MULTI_ERR
mdefine_line|#define&t;XB_WID_STAT_MULTI_ERR&t;&t;0x00000001
DECL|macro|XB_WID_STAT_SRCID_SHFT
mdefine_line|#define XB_WID_STAT_SRCID_SHFT&t;&t;6
multiline_comment|/* XBOW_WID_CONTROL */
DECL|macro|XB_WID_CTRL_REG_ACC_IE
mdefine_line|#define XB_WID_CTRL_REG_ACC_IE&t;&t;XB_WID_STAT_REG_ACC_ERR
DECL|macro|XB_WID_CTRL_RECV_TOUT
mdefine_line|#define XB_WID_CTRL_RECV_TOUT&t;&t;XB_WID_STAT_RECV_TOUT
DECL|macro|XB_WID_CTRL_ARB_TOUT
mdefine_line|#define XB_WID_CTRL_ARB_TOUT&t;&t;XB_WID_STAT_ARB_TOUT
DECL|macro|XB_WID_CTRL_XTALK_IE
mdefine_line|#define XB_WID_CTRL_XTALK_IE&t;&t;XB_WID_STAT_XTALK_ERR
multiline_comment|/* XBOW_WID_INT_UPPER */
multiline_comment|/* defined in xwidget.h for WIDGET_INTDEST_UPPER_ADDR */
multiline_comment|/* XBOW WIDGET part number, in the ID register */
DECL|macro|XBOW_WIDGET_PART_NUM
mdefine_line|#define XBOW_WIDGET_PART_NUM&t;0x0&t;&t;/* crossbow */
DECL|macro|XXBOW_WIDGET_PART_NUM
mdefine_line|#define XXBOW_WIDGET_PART_NUM&t;0xd000&t;&t;/* Xbridge */
DECL|macro|XBOW_WIDGET_MFGR_NUM
mdefine_line|#define&t;XBOW_WIDGET_MFGR_NUM&t;0x0
DECL|macro|XXBOW_WIDGET_MFGR_NUM
mdefine_line|#define&t;XXBOW_WIDGET_MFGR_NUM&t;0x0
DECL|macro|PXBOW_WIDGET_PART_NUM
mdefine_line|#define PXBOW_WIDGET_PART_NUM   0xd100          /* PIC */
DECL|macro|XBOW_REV_1_0
mdefine_line|#define&t;XBOW_REV_1_0&t;&t;0x1&t;/* xbow rev 1.0 is &quot;1&quot; */
DECL|macro|XBOW_REV_1_1
mdefine_line|#define&t;XBOW_REV_1_1&t;&t;0x2&t;/* xbow rev 1.1 is &quot;2&quot; */
DECL|macro|XBOW_REV_1_2
mdefine_line|#define XBOW_REV_1_2&t;&t;0x3&t;/* xbow rev 1.2 is &quot;3&quot; */
DECL|macro|XBOW_REV_1_3
mdefine_line|#define XBOW_REV_1_3&t;&t;0x4&t;/* xbow rev 1.3 is &quot;4&quot; */
DECL|macro|XBOW_REV_2_0
mdefine_line|#define XBOW_REV_2_0&t;&t;0x5&t;/* xbow rev 2.0 is &quot;5&quot; */
DECL|macro|XXBOW_PART_REV_1_0
mdefine_line|#define XXBOW_PART_REV_1_0&t;&t;(XXBOW_WIDGET_PART_NUM &lt;&lt; 4 | 0x1 )
DECL|macro|XXBOW_PART_REV_2_0
mdefine_line|#define XXBOW_PART_REV_2_0&t;&t;(XXBOW_WIDGET_PART_NUM &lt;&lt; 4 | 0x2 )
multiline_comment|/* XBOW_WID_ARB_RELOAD */
DECL|macro|XBOW_WID_ARB_RELOAD_INT
mdefine_line|#define&t;XBOW_WID_ARB_RELOAD_INT&t;0x3f&t;/* GBR reload interval */
DECL|macro|IS_XBRIDGE_XBOW
mdefine_line|#define IS_XBRIDGE_XBOW(wid) &bslash;&n;        (XWIDGET_PART_NUM(wid) == XXBOW_WIDGET_PART_NUM &amp;&amp; &bslash;&n;                        XWIDGET_MFG_NUM(wid) == XXBOW_WIDGET_MFGR_NUM)
DECL|macro|IS_PIC_XBOW
mdefine_line|#define IS_PIC_XBOW(wid) &bslash;&n;        (XWIDGET_PART_NUM(wid) == PXBOW_WIDGET_PART_NUM &amp;&amp; &bslash;&n;                        XWIDGET_MFG_NUM(wid) == XXBOW_WIDGET_MFGR_NUM)
DECL|macro|XBOW_WAR_ENABLED
mdefine_line|#define XBOW_WAR_ENABLED(pv, widid) ((1 &lt;&lt; XWIDGET_REV_NUM(widid)) &amp; pv)
macro_line|#endif                          /* _ASM_IA64_SN_XTALK_XBOW_H */
eof
