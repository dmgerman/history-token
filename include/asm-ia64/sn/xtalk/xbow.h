multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_SN_XTALK_XBOW_H
DECL|macro|_ASM_SN_SN_XTALK_XBOW_H
mdefine_line|#define _ASM_SN_SN_XTALK_XBOW_H
multiline_comment|/*&n; * xbow.h - header file for crossbow chip and xbow section of xbridge&n; */
macro_line|#include &lt;asm/sn/xtalk/xtalk.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xwidget.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xswitch.h&gt;
macro_line|#ifdef LANGUAGE_C
macro_line|#include &lt;asm/sn/xtalk/xbow_info.h&gt;
macro_line|#endif
DECL|macro|XBOW_DRV_PREFIX
mdefine_line|#define&t;XBOW_DRV_PREFIX&t;&quot;xbow_&quot;
multiline_comment|/* The crossbow chip supports 8 8/16 bits I/O ports, numbered 0x8 through 0xf.&n; * It also implements the widget 0 address space and register set.&n; */
DECL|macro|XBOW_PORT_0
mdefine_line|#define XBOW_PORT_0&t;0x0
DECL|macro|XBOW_PORT_8
mdefine_line|#define XBOW_PORT_8&t;0x8
DECL|macro|XBOW_PORT_9
mdefine_line|#define XBOW_PORT_9&t;0x9
DECL|macro|XBOW_PORT_A
mdefine_line|#define XBOW_PORT_A&t;0xa
DECL|macro|XBOW_PORT_B
mdefine_line|#define XBOW_PORT_B&t;0xb
DECL|macro|XBOW_PORT_C
mdefine_line|#define XBOW_PORT_C&t;0xc
DECL|macro|XBOW_PORT_D
mdefine_line|#define XBOW_PORT_D&t;0xd
DECL|macro|XBOW_PORT_E
mdefine_line|#define XBOW_PORT_E&t;0xe
DECL|macro|XBOW_PORT_F
mdefine_line|#define XBOW_PORT_F&t;0xf
DECL|macro|MAX_XBOW_PORTS
mdefine_line|#define MAX_XBOW_PORTS&t;8&t;/* number of ports on xbow chip */
DECL|macro|BASE_XBOW_PORT
mdefine_line|#define BASE_XBOW_PORT&t;XBOW_PORT_8&t;/* Lowest external port */
DECL|macro|MAX_PORT_NUM
mdefine_line|#define MAX_PORT_NUM&t;0x10&t;/* maximum port number + 1 */
DECL|macro|XBOW_WIDGET_ID
mdefine_line|#define XBOW_WIDGET_ID&t;0&t;/* xbow is itself widget 0 */
DECL|macro|XBOW_CREDIT
mdefine_line|#define&t;XBOW_CREDIT&t;4
DECL|macro|MAX_XBOW_NAME
mdefine_line|#define MAX_XBOW_NAME &t;16
macro_line|#if LANGUAGE_C
DECL|typedef|xbowreg_t
r_typedef
r_uint32
id|xbowreg_t
suffix:semicolon
DECL|macro|XBOWCONST
mdefine_line|#define XBOWCONST&t;(xbowreg_t)
multiline_comment|/* Generic xbow register, given base and offset */
DECL|macro|XBOW_REG_PTR
mdefine_line|#define XBOW_REG_PTR(base, offset) ((volatile xbowreg_t*) &bslash;&n;&t;((__psunsigned_t)(base) + (__psunsigned_t)(offset)))
multiline_comment|/* Register set for each xbow link */
DECL|struct|xb_linkregs_s
r_typedef
r_volatile
r_struct
id|xb_linkregs_s
(brace
macro_line|#ifdef LITTLE_ENDIAN
multiline_comment|/* &n; * we access these through synergy unswizzled space, so the address&n; * gets twiddled (i.e. references to 0x4 actually go to 0x0 and vv.)&n; * That&squot;s why we put the register first and filler second.&n; */
DECL|member|link_ibf
id|xbowreg_t
id|link_ibf
suffix:semicolon
DECL|member|filler0
id|xbowreg_t
id|filler0
suffix:semicolon
multiline_comment|/* filler for proper alignment */
DECL|member|link_control
id|xbowreg_t
id|link_control
suffix:semicolon
DECL|member|filler1
id|xbowreg_t
id|filler1
suffix:semicolon
DECL|member|link_status
id|xbowreg_t
id|link_status
suffix:semicolon
DECL|member|filler2
id|xbowreg_t
id|filler2
suffix:semicolon
DECL|member|link_arb_upper
id|xbowreg_t
id|link_arb_upper
suffix:semicolon
DECL|member|filler3
id|xbowreg_t
id|filler3
suffix:semicolon
DECL|member|link_arb_lower
id|xbowreg_t
id|link_arb_lower
suffix:semicolon
DECL|member|filler4
id|xbowreg_t
id|filler4
suffix:semicolon
DECL|member|link_status_clr
id|xbowreg_t
id|link_status_clr
suffix:semicolon
DECL|member|filler5
id|xbowreg_t
id|filler5
suffix:semicolon
DECL|member|link_reset
id|xbowreg_t
id|link_reset
suffix:semicolon
DECL|member|filler6
id|xbowreg_t
id|filler6
suffix:semicolon
DECL|member|link_aux_status
id|xbowreg_t
id|link_aux_status
suffix:semicolon
DECL|member|filler7
id|xbowreg_t
id|filler7
suffix:semicolon
macro_line|#else
id|xbowreg_t
id|filler0
suffix:semicolon
multiline_comment|/* filler for proper alignment */
id|xbowreg_t
id|link_ibf
suffix:semicolon
id|xbowreg_t
id|filler1
suffix:semicolon
id|xbowreg_t
id|link_control
suffix:semicolon
id|xbowreg_t
id|filler2
suffix:semicolon
id|xbowreg_t
id|link_status
suffix:semicolon
id|xbowreg_t
id|filler3
suffix:semicolon
id|xbowreg_t
id|link_arb_upper
suffix:semicolon
id|xbowreg_t
id|filler4
suffix:semicolon
id|xbowreg_t
id|link_arb_lower
suffix:semicolon
id|xbowreg_t
id|filler5
suffix:semicolon
id|xbowreg_t
id|link_status_clr
suffix:semicolon
id|xbowreg_t
id|filler6
suffix:semicolon
id|xbowreg_t
id|link_reset
suffix:semicolon
id|xbowreg_t
id|filler7
suffix:semicolon
id|xbowreg_t
id|link_aux_status
suffix:semicolon
macro_line|#endif /* LITTLE_ENDIAN */
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
id|widget_cfg_t
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
macro_line|#ifdef LITTLE_ENDIAN
multiline_comment|/* &n; * we access these through synergy unswizzled space, so the address&n; * gets twiddled (i.e. references to 0x4 actually go to 0x0 and vv.)&n; * That&squot;s why we put the register first and filler second.&n; */
multiline_comment|/* xbow-specific widget configuration                  0x000058-0x0000FF */
DECL|member|xb_wid_arb_reload
id|xbowreg_t
id|xb_wid_arb_reload
suffix:semicolon
multiline_comment|/* 0x00005C */
DECL|member|_pad_000058
id|xbowreg_t
id|_pad_000058
suffix:semicolon
DECL|member|xb_perf_ctr_a
id|xbowreg_t
id|xb_perf_ctr_a
suffix:semicolon
multiline_comment|/* 0x000064 */
DECL|member|_pad_000060
id|xbowreg_t
id|_pad_000060
suffix:semicolon
DECL|member|xb_perf_ctr_b
id|xbowreg_t
id|xb_perf_ctr_b
suffix:semicolon
multiline_comment|/* 0x00006c */
DECL|member|_pad_000068
id|xbowreg_t
id|_pad_000068
suffix:semicolon
DECL|member|xb_nic
id|xbowreg_t
id|xb_nic
suffix:semicolon
multiline_comment|/* 0x000074 */
DECL|member|_pad_000070
id|xbowreg_t
id|_pad_000070
suffix:semicolon
multiline_comment|/* Xbridge only */
DECL|member|xb_w0_rst_fnc
id|xbowreg_t
id|xb_w0_rst_fnc
suffix:semicolon
multiline_comment|/* 0x00007C */
DECL|member|_pad_000078
id|xbowreg_t
id|_pad_000078
suffix:semicolon
DECL|member|xb_l8_rst_fnc
id|xbowreg_t
id|xb_l8_rst_fnc
suffix:semicolon
multiline_comment|/* 0x000084 */
DECL|member|_pad_000080
id|xbowreg_t
id|_pad_000080
suffix:semicolon
DECL|member|xb_l9_rst_fnc
id|xbowreg_t
id|xb_l9_rst_fnc
suffix:semicolon
multiline_comment|/* 0x00008c */
DECL|member|_pad_000088
id|xbowreg_t
id|_pad_000088
suffix:semicolon
DECL|member|xb_la_rst_fnc
id|xbowreg_t
id|xb_la_rst_fnc
suffix:semicolon
multiline_comment|/* 0x000094 */
DECL|member|_pad_000090
id|xbowreg_t
id|_pad_000090
suffix:semicolon
DECL|member|xb_lb_rst_fnc
id|xbowreg_t
id|xb_lb_rst_fnc
suffix:semicolon
multiline_comment|/* 0x00009c */
DECL|member|_pad_000098
id|xbowreg_t
id|_pad_000098
suffix:semicolon
DECL|member|xb_lc_rst_fnc
id|xbowreg_t
id|xb_lc_rst_fnc
suffix:semicolon
multiline_comment|/* 0x0000a4 */
DECL|member|_pad_0000a0
id|xbowreg_t
id|_pad_0000a0
suffix:semicolon
DECL|member|xb_ld_rst_fnc
id|xbowreg_t
id|xb_ld_rst_fnc
suffix:semicolon
multiline_comment|/* 0x0000ac */
DECL|member|_pad_0000a8
id|xbowreg_t
id|_pad_0000a8
suffix:semicolon
DECL|member|xb_le_rst_fnc
id|xbowreg_t
id|xb_le_rst_fnc
suffix:semicolon
multiline_comment|/* 0x0000b4 */
DECL|member|_pad_0000b0
id|xbowreg_t
id|_pad_0000b0
suffix:semicolon
DECL|member|xb_lf_rst_fnc
id|xbowreg_t
id|xb_lf_rst_fnc
suffix:semicolon
multiline_comment|/* 0x0000bc */
DECL|member|_pad_0000b8
id|xbowreg_t
id|_pad_0000b8
suffix:semicolon
DECL|member|xb_lock
id|xbowreg_t
id|xb_lock
suffix:semicolon
multiline_comment|/* 0x0000c4 */
DECL|member|_pad_0000c0
id|xbowreg_t
id|_pad_0000c0
suffix:semicolon
DECL|member|xb_lock_clr
id|xbowreg_t
id|xb_lock_clr
suffix:semicolon
multiline_comment|/* 0x0000cc */
DECL|member|_pad_0000c8
id|xbowreg_t
id|_pad_0000c8
suffix:semicolon
multiline_comment|/* end of Xbridge only */
DECL|member|_pad_0000d0
id|xbowreg_t
id|_pad_0000d0
(braket
l_int|12
)braket
suffix:semicolon
macro_line|#else
multiline_comment|/* xbow-specific widget configuration                  0x000058-0x0000FF */
DECL|member|_pad_000058
id|xbowreg_t
id|_pad_000058
suffix:semicolon
DECL|member|xb_wid_arb_reload
id|xbowreg_t
id|xb_wid_arb_reload
suffix:semicolon
multiline_comment|/* 0x00005C */
DECL|member|_pad_000060
id|xbowreg_t
id|_pad_000060
suffix:semicolon
DECL|member|xb_perf_ctr_a
id|xbowreg_t
id|xb_perf_ctr_a
suffix:semicolon
multiline_comment|/* 0x000064 */
DECL|member|_pad_000068
id|xbowreg_t
id|_pad_000068
suffix:semicolon
DECL|member|xb_perf_ctr_b
id|xbowreg_t
id|xb_perf_ctr_b
suffix:semicolon
multiline_comment|/* 0x00006c */
DECL|member|_pad_000070
id|xbowreg_t
id|_pad_000070
suffix:semicolon
DECL|member|xb_nic
id|xbowreg_t
id|xb_nic
suffix:semicolon
multiline_comment|/* 0x000074 */
multiline_comment|/* Xbridge only */
DECL|member|_pad_000078
id|xbowreg_t
id|_pad_000078
suffix:semicolon
DECL|member|xb_w0_rst_fnc
id|xbowreg_t
id|xb_w0_rst_fnc
suffix:semicolon
multiline_comment|/* 0x00007C */
DECL|member|_pad_000080
id|xbowreg_t
id|_pad_000080
suffix:semicolon
DECL|member|xb_l8_rst_fnc
id|xbowreg_t
id|xb_l8_rst_fnc
suffix:semicolon
multiline_comment|/* 0x000084 */
DECL|member|_pad_000088
id|xbowreg_t
id|_pad_000088
suffix:semicolon
DECL|member|xb_l9_rst_fnc
id|xbowreg_t
id|xb_l9_rst_fnc
suffix:semicolon
multiline_comment|/* 0x00008c */
DECL|member|_pad_000090
id|xbowreg_t
id|_pad_000090
suffix:semicolon
DECL|member|xb_la_rst_fnc
id|xbowreg_t
id|xb_la_rst_fnc
suffix:semicolon
multiline_comment|/* 0x000094 */
DECL|member|_pad_000098
id|xbowreg_t
id|_pad_000098
suffix:semicolon
DECL|member|xb_lb_rst_fnc
id|xbowreg_t
id|xb_lb_rst_fnc
suffix:semicolon
multiline_comment|/* 0x00009c */
DECL|member|_pad_0000a0
id|xbowreg_t
id|_pad_0000a0
suffix:semicolon
DECL|member|xb_lc_rst_fnc
id|xbowreg_t
id|xb_lc_rst_fnc
suffix:semicolon
multiline_comment|/* 0x0000a4 */
DECL|member|_pad_0000a8
id|xbowreg_t
id|_pad_0000a8
suffix:semicolon
DECL|member|xb_ld_rst_fnc
id|xbowreg_t
id|xb_ld_rst_fnc
suffix:semicolon
multiline_comment|/* 0x0000ac */
DECL|member|_pad_0000b0
id|xbowreg_t
id|_pad_0000b0
suffix:semicolon
DECL|member|xb_le_rst_fnc
id|xbowreg_t
id|xb_le_rst_fnc
suffix:semicolon
multiline_comment|/* 0x0000b4 */
DECL|member|_pad_0000b8
id|xbowreg_t
id|_pad_0000b8
suffix:semicolon
DECL|member|xb_lf_rst_fnc
id|xbowreg_t
id|xb_lf_rst_fnc
suffix:semicolon
multiline_comment|/* 0x0000bc */
DECL|member|_pad_0000c0
id|xbowreg_t
id|_pad_0000c0
suffix:semicolon
DECL|member|xb_lock
id|xbowreg_t
id|xb_lock
suffix:semicolon
multiline_comment|/* 0x0000c4 */
DECL|member|_pad_0000c8
id|xbowreg_t
id|_pad_0000c8
suffix:semicolon
DECL|member|xb_lock_clr
id|xbowreg_t
id|xb_lock_clr
suffix:semicolon
multiline_comment|/* 0x0000cc */
multiline_comment|/* end of Xbridge only */
DECL|member|_pad_0000d0
id|xbowreg_t
id|_pad_0000d0
(braket
l_int|12
)braket
suffix:semicolon
macro_line|#endif /* LITTLE_ENDIAN */
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
multiline_comment|/* Configuration structure which describes each xbow link */
DECL|struct|xbow_cfg_s
r_typedef
r_struct
id|xbow_cfg_s
(brace
DECL|member|xb_port
r_int
id|xb_port
suffix:semicolon
multiline_comment|/* port number (0-15) */
DECL|member|xb_flags
r_int
id|xb_flags
suffix:semicolon
multiline_comment|/* port software flags */
DECL|member|xb_shift
r_int
id|xb_shift
suffix:semicolon
multiline_comment|/* shift for arb reg (mask is 0xff) */
DECL|member|xb_ul
r_int
id|xb_ul
suffix:semicolon
multiline_comment|/* upper or lower arb reg */
DECL|member|xb_pad
r_int
id|xb_pad
suffix:semicolon
multiline_comment|/* use this later (pad to ptr align) */
DECL|member|xb_linkregs
id|xb_linkregs_t
op_star
id|xb_linkregs
suffix:semicolon
multiline_comment|/* pointer to link registers */
DECL|member|xb_widget
id|widget_cfg_t
op_star
id|xb_widget
suffix:semicolon
multiline_comment|/* pointer to widget registers */
DECL|member|xb_name
r_char
id|xb_name
(braket
id|MAX_XBOW_NAME
)braket
suffix:semicolon
multiline_comment|/* port name */
DECL|member|xb_sh_arb_upper
id|xbowreg_t
id|xb_sh_arb_upper
suffix:semicolon
multiline_comment|/* shadow upper arb register */
DECL|member|xb_sh_arb_lower
id|xbowreg_t
id|xb_sh_arb_lower
suffix:semicolon
multiline_comment|/* shadow lower arb register */
DECL|typedef|xbow_cfg_t
)brace
id|xbow_cfg_t
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
multiline_comment|/* get xbow config information for port p */
DECL|macro|XB_CONFIG
mdefine_line|#define XB_CONFIG(p)&t;xbow_cfg[xb_ports[p]]
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
macro_line|#endif&t;&t;&t;&t;/* LANGUAGE_C */
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
multiline_comment|/* pointer to link arbitration register, given xbow base, dst and src widget id */
DECL|macro|XBOW_PRIO_ARBREG_PTR
mdefine_line|#define XBOW_PRIO_ARBREG_PTR(base, dst_wid, src_wid) &bslash;&n;&t;XBOW_REG_PTR(XBOW_PRIO_LINKREGS_PTR(base, dst_wid), XBOW_ARB_OFF(src_wid))
multiline_comment|/* pointer to link registers base, given xbow base and destination widget id */
DECL|macro|XBOW_PRIO_LINKREGS_PTR
mdefine_line|#define XBOW_PRIO_LINKREGS_PTR(base, dst_wid) (xb_linkregs_t*) &bslash;&n;&t;XBOW_REG_PTR(base, XB_LINK_REG_BASE(dst_wid))
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
DECL|macro|nasid_has_xbridge
mdefine_line|#define nasid_has_xbridge(nasid)&t;&bslash;&n;&t;(XWIDGET_PART_NUM(XWIDGET_ID_READ(nasid, 0)) == XXBOW_WIDGET_PART_NUM)
macro_line|#ifdef _LANGUAGE_C
multiline_comment|/*&n; * XBOW Widget 0 Register formats.&n; * Format for many of these registers are similar to the standard&n; * widget register format described as part of xtalk specification&n; * Standard widget register field format description is available in&n; * xwidget.h&n; * Following structures define the format for xbow widget 0 registers&n; */
multiline_comment|/*&n; * Xbow Widget 0 Command error word&n; */
macro_line|#ifdef LITTLE_ENDIAN
DECL|union|xbw0_cmdword_u
r_typedef
r_union
id|xbw0_cmdword_u
(brace
DECL|member|cmdword
id|xbowreg_t
id|cmdword
suffix:semicolon
r_struct
(brace
DECL|member|rsvd
r_uint32
id|rsvd
suffix:colon
l_int|8
comma
multiline_comment|/* Reserved */
DECL|member|barr
id|barr
suffix:colon
l_int|1
comma
multiline_comment|/* Barrier operation */
DECL|member|error
id|error
suffix:colon
l_int|1
comma
multiline_comment|/* Error Occured */
DECL|member|vbpm
id|vbpm
suffix:colon
l_int|1
comma
multiline_comment|/* Virtual Backplane message */
DECL|member|gbr
id|gbr
suffix:colon
l_int|1
comma
multiline_comment|/* GBR enable ?                 */
DECL|member|ds
id|ds
suffix:colon
l_int|2
comma
multiline_comment|/* Data size                    */
DECL|member|ct
id|ct
suffix:colon
l_int|1
comma
multiline_comment|/* Is it a coherent transaction */
DECL|member|tnum
id|tnum
suffix:colon
l_int|5
comma
multiline_comment|/* Transaction Number */
DECL|member|pactyp
id|pactyp
suffix:colon
l_int|4
comma
multiline_comment|/* Packet type: */
DECL|member|srcid
id|srcid
suffix:colon
l_int|4
comma
multiline_comment|/* Source ID number */
DECL|member|destid
id|destid
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Desination ID number */
DECL|member|xbw0_cmdfield
)brace
id|xbw0_cmdfield
suffix:semicolon
DECL|typedef|xbw0_cmdword_t
)brace
id|xbw0_cmdword_t
suffix:semicolon
macro_line|#else
DECL|union|xbw0_cmdword_u
r_typedef
r_union
id|xbw0_cmdword_u
(brace
DECL|member|cmdword
id|xbowreg_t
id|cmdword
suffix:semicolon
r_struct
(brace
DECL|member|destid
r_uint32
id|destid
suffix:colon
l_int|4
comma
multiline_comment|/* Desination ID number */
DECL|member|srcid
id|srcid
suffix:colon
l_int|4
comma
multiline_comment|/* Source ID number */
DECL|member|pactyp
id|pactyp
suffix:colon
l_int|4
comma
multiline_comment|/* Packet type: */
DECL|member|tnum
id|tnum
suffix:colon
l_int|5
comma
multiline_comment|/* Transaction Number */
DECL|member|ct
id|ct
suffix:colon
l_int|1
comma
multiline_comment|/* Is it a coherent transaction */
DECL|member|ds
id|ds
suffix:colon
l_int|2
comma
multiline_comment|/* Data size&t;&t;&t;*/
DECL|member|gbr
id|gbr
suffix:colon
l_int|1
comma
multiline_comment|/* GBR enable ?&t;&t;&t;*/
DECL|member|vbpm
id|vbpm
suffix:colon
l_int|1
comma
multiline_comment|/* Virtual Backplane message */
DECL|member|error
id|error
suffix:colon
l_int|1
comma
multiline_comment|/* Error Occured */
DECL|member|barr
id|barr
suffix:colon
l_int|1
comma
multiline_comment|/* Barrier operation */
DECL|member|rsvd
id|rsvd
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|xbw0_cmdfield
)brace
id|xbw0_cmdfield
suffix:semicolon
DECL|typedef|xbw0_cmdword_t
)brace
id|xbw0_cmdword_t
suffix:semicolon
macro_line|#endif
DECL|macro|xbcmd_destid
mdefine_line|#define&t;xbcmd_destid&t;xbw0_cmdfield.destid
DECL|macro|xbcmd_srcid
mdefine_line|#define&t;xbcmd_srcid&t;xbw0_cmdfield.srcid
DECL|macro|xbcmd_pactyp
mdefine_line|#define&t;xbcmd_pactyp&t;xbw0_cmdfield.pactyp
DECL|macro|xbcmd_tnum
mdefine_line|#define&t;xbcmd_tnum&t;xbw0_cmdfield.tnum
DECL|macro|xbcmd_ct
mdefine_line|#define&t;xbcmd_ct&t;xbw0_cmdfield.ct
DECL|macro|xbcmd_ds
mdefine_line|#define&t;xbcmd_ds&t;xbw0_cmdfield.ds
DECL|macro|xbcmd_gbr
mdefine_line|#define&t;xbcmd_gbr&t;xbw0_cmdfield.gbr
DECL|macro|xbcmd_vbpm
mdefine_line|#define&t;xbcmd_vbpm&t;xbw0_cmdfield.vbpm
DECL|macro|xbcmd_error
mdefine_line|#define&t;xbcmd_error&t;xbw0_cmdfield.error
DECL|macro|xbcmd_barr
mdefine_line|#define&t;xbcmd_barr&t;xbw0_cmdfield.barr
multiline_comment|/*&n; * Values for field PACTYP in xbow error command word&n; */
DECL|macro|XBCMDTYP_READREQ
mdefine_line|#define&t;XBCMDTYP_READREQ&t;0&t;/* Read Request   packet  */
DECL|macro|XBCMDTYP_READRESP
mdefine_line|#define&t;XBCMDTYP_READRESP&t;1&t;/* Read Response packet   */
DECL|macro|XBCMDTYP_WRREQ_RESP
mdefine_line|#define&t;XBCMDTYP_WRREQ_RESP&t;2&t;/* Write Request with response    */
DECL|macro|XBCMDTYP_WRRESP
mdefine_line|#define&t;XBCMDTYP_WRRESP&t;&t;3&t;/* Write Response */
DECL|macro|XBCMDTYP_WRREQ_NORESP
mdefine_line|#define&t;XBCMDTYP_WRREQ_NORESP&t;4&t;/* Write request with  No Response */
DECL|macro|XBCMDTYP_FETCHOP
mdefine_line|#define&t;XBCMDTYP_FETCHOP&t;6&t;/* Fetch &amp; Op packet      */
DECL|macro|XBCMDTYP_STOREOP
mdefine_line|#define&t;XBCMDTYP_STOREOP&t;8&t;/* Store &amp; Op packet      */
DECL|macro|XBCMDTYP_SPLPKT_REQ
mdefine_line|#define&t;XBCMDTYP_SPLPKT_REQ&t;0xE&t;/* Special packet request */
DECL|macro|XBCMDTYP_SPLPKT_RESP
mdefine_line|#define&t;XBCMDTYP_SPLPKT_RESP&t;0xF&t;/* Special packet response        */
multiline_comment|/*&n; * Values for field ds (datasize) in xbow error command word&n; */
DECL|macro|XBCMDSZ_DOUBLEWORD
mdefine_line|#define&t;XBCMDSZ_DOUBLEWORD&t;0
DECL|macro|XBCMDSZ_QUARTRCACHE
mdefine_line|#define&t;XBCMDSZ_QUARTRCACHE&t;1
DECL|macro|XBCMDSZ_FULLCACHE
mdefine_line|#define&t;XBCMDSZ_FULLCACHE&t;2
multiline_comment|/*&n; * Xbow widget 0 Status register format.&n; */
macro_line|#ifdef LITTLE_ENDIAN
DECL|union|xbw0_status_u
r_typedef
r_union
id|xbw0_status_u
(brace
DECL|member|statusword
id|xbowreg_t
id|statusword
suffix:semicolon
r_struct
(brace
DECL|member|mult_err
r_uint32
id|mult_err
suffix:colon
l_int|1
comma
multiline_comment|/* Multiple error occured */
DECL|member|connect_tout
id|connect_tout
suffix:colon
l_int|1
comma
multiline_comment|/* Connection timeout   */
DECL|member|xtalk_err
id|xtalk_err
suffix:colon
l_int|1
comma
multiline_comment|/* Xtalk pkt with error bit */
multiline_comment|/* End of Xbridge only */
DECL|member|w0_arb_tout
id|w0_arb_tout
comma
multiline_comment|/* arbiter timeout err */
DECL|member|w0_recv_tout
id|w0_recv_tout
comma
multiline_comment|/* receive timeout err */
multiline_comment|/* Xbridge only */
DECL|member|regacc_err
id|regacc_err
suffix:colon
l_int|1
comma
multiline_comment|/* Reg Access error     */
DECL|member|src_id
id|src_id
suffix:colon
l_int|4
comma
multiline_comment|/* source id. Xbridge only */
DECL|member|resvd1
id|resvd1
suffix:colon
l_int|13
comma
DECL|member|wid0intr
id|wid0intr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Widget 0 err intr */
DECL|member|xbw0_stfield
)brace
id|xbw0_stfield
suffix:semicolon
DECL|typedef|xbw0_status_t
)brace
id|xbw0_status_t
suffix:semicolon
macro_line|#else
DECL|union|xbw0_status_u
r_typedef
r_union
id|xbw0_status_u
(brace
DECL|member|statusword
id|xbowreg_t
id|statusword
suffix:semicolon
r_struct
(brace
DECL|member|linkXintr
r_uint32
id|linkXintr
suffix:colon
l_int|8
comma
multiline_comment|/* link(x) error intr */
DECL|member|wid0intr
id|wid0intr
suffix:colon
l_int|1
comma
multiline_comment|/* Widget 0 err intr */
DECL|member|resvd1
id|resvd1
suffix:colon
l_int|13
comma
DECL|member|src_id
id|src_id
suffix:colon
l_int|4
comma
multiline_comment|/* source id. Xbridge only */
DECL|member|regacc_err
id|regacc_err
suffix:colon
l_int|1
comma
multiline_comment|/* Reg Access error&t;*/
multiline_comment|/* Xbridge only */
DECL|member|w0_recv_tout
id|w0_recv_tout
comma
multiline_comment|/* receive timeout err */
DECL|member|w0_arb_tout
id|w0_arb_tout
comma
multiline_comment|/* arbiter timeout err */
multiline_comment|/* End of Xbridge only */
DECL|member|xtalk_err
id|xtalk_err
suffix:colon
l_int|1
comma
multiline_comment|/* Xtalk pkt with error bit */
DECL|member|connect_tout
id|connect_tout
suffix:colon
l_int|1
comma
multiline_comment|/* Connection timeout&t;*/
DECL|member|mult_err
id|mult_err
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Multiple error occured */
DECL|member|xbw0_stfield
)brace
id|xbw0_stfield
suffix:semicolon
DECL|typedef|xbw0_status_t
)brace
id|xbw0_status_t
suffix:semicolon
macro_line|#endif
DECL|macro|xbst_linkXintr
mdefine_line|#define&t;xbst_linkXintr&t;&t;xbw0_stfield.linkXintr
DECL|macro|xbst_w0intr
mdefine_line|#define&t;xbst_w0intr&t;&t;xbw0_stfield.wid0intr
DECL|macro|xbst_regacc_err
mdefine_line|#define&t;xbst_regacc_err&t;&t;xbw0_stfield.regacc_err
DECL|macro|xbst_xtalk_err
mdefine_line|#define&t;xbst_xtalk_err&t;&t;xbw0_stfield.xtalk_err
DECL|macro|xbst_connect_tout
mdefine_line|#define&t;xbst_connect_tout&t;xbw0_stfield.connect_tout
DECL|macro|xbst_mult_err
mdefine_line|#define&t;xbst_mult_err&t;&t;xbw0_stfield.mult_err
DECL|macro|xbst_src_id
mdefine_line|#define xbst_src_id&t;&t;xbw0_stfield.src_id&t;    /* Xbridge only */
DECL|macro|xbst_w0_recv_tout
mdefine_line|#define xbst_w0_recv_tout&t;xbw0_stfield.w0_recv_tout   /* Xbridge only */
DECL|macro|xbst_w0_arb_tout
mdefine_line|#define xbst_w0_arb_tout&t;xbw0_stfield.w0_arb_tout    /* Xbridge only */
multiline_comment|/*&n; * Xbow widget 0 Control register format&n; */
macro_line|#ifdef LITTLE_ENDIAN
DECL|union|xbw0_ctrl_u
r_typedef
r_union
id|xbw0_ctrl_u
(brace
DECL|member|ctrlword
id|xbowreg_t
id|ctrlword
suffix:semicolon
r_struct
(brace
r_uint32
DECL|member|resvd3
id|resvd3
suffix:colon
l_int|1
comma
DECL|member|conntout_intr
id|conntout_intr
suffix:colon
l_int|1
comma
DECL|member|xtalkerr_intr
id|xtalkerr_intr
suffix:colon
l_int|1
comma
DECL|member|w0_arg_tout_intr
id|w0_arg_tout_intr
suffix:colon
l_int|1
comma
multiline_comment|/* Xbridge only */
DECL|member|w0_recv_tout_intr
id|w0_recv_tout_intr
suffix:colon
l_int|1
comma
multiline_comment|/* Xbridge only */
DECL|member|accerr_intr
id|accerr_intr
suffix:colon
l_int|1
comma
DECL|member|enable_w0_tout_cntr
id|enable_w0_tout_cntr
suffix:colon
l_int|1
comma
multiline_comment|/* Xbridge only */
DECL|member|enable_watchdog
id|enable_watchdog
suffix:colon
l_int|1
comma
multiline_comment|/* Xbridge only */
DECL|member|resvd1
id|resvd1
suffix:colon
l_int|24
suffix:semicolon
DECL|member|xbw0_ctrlfield
)brace
id|xbw0_ctrlfield
suffix:semicolon
DECL|typedef|xbw0_ctrl_t
)brace
id|xbw0_ctrl_t
suffix:semicolon
macro_line|#else
DECL|union|xbw0_ctrl_u
r_typedef
r_union
id|xbw0_ctrl_u
(brace
DECL|member|ctrlword
id|xbowreg_t
id|ctrlword
suffix:semicolon
r_struct
(brace
r_uint32
DECL|member|resvd1
id|resvd1
suffix:colon
l_int|24
comma
DECL|member|enable_watchdog
id|enable_watchdog
suffix:colon
l_int|1
comma
multiline_comment|/* Xbridge only */
DECL|member|enable_w0_tout_cntr
id|enable_w0_tout_cntr
suffix:colon
l_int|1
comma
multiline_comment|/* Xbridge only */
DECL|member|accerr_intr
id|accerr_intr
suffix:colon
l_int|1
comma
DECL|member|w0_recv_tout_intr
id|w0_recv_tout_intr
suffix:colon
l_int|1
comma
multiline_comment|/* Xbridge only */
DECL|member|w0_arg_tout_intr
id|w0_arg_tout_intr
suffix:colon
l_int|1
comma
multiline_comment|/* Xbridge only */
DECL|member|xtalkerr_intr
id|xtalkerr_intr
suffix:colon
l_int|1
comma
DECL|member|conntout_intr
id|conntout_intr
suffix:colon
l_int|1
comma
DECL|member|resvd3
id|resvd3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|xbw0_ctrlfield
)brace
id|xbw0_ctrlfield
suffix:semicolon
DECL|typedef|xbw0_ctrl_t
)brace
id|xbw0_ctrl_t
suffix:semicolon
macro_line|#endif
macro_line|#ifdef LITTLE_ENDIAN
DECL|union|xbow_linkctrl_u
r_typedef
r_union
id|xbow_linkctrl_u
(brace
DECL|member|xbl_ctrlword
id|xbowreg_t
id|xbl_ctrlword
suffix:semicolon
r_struct
(brace
DECL|member|srcto_intr
r_uint32
id|srcto_intr
suffix:colon
l_int|1
comma
DECL|member|maxto_intr
id|maxto_intr
suffix:colon
l_int|1
comma
DECL|member|rsvd3
id|rsvd3
suffix:colon
l_int|1
comma
DECL|member|trx_retry_intr
id|trx_retry_intr
suffix:colon
l_int|1
comma
DECL|member|rcv_err_intr
id|rcv_err_intr
suffix:colon
l_int|1
comma
DECL|member|trx_max_retry_intr
id|trx_max_retry_intr
suffix:colon
l_int|1
comma
DECL|member|trxov_intr
id|trxov_intr
suffix:colon
l_int|1
comma
DECL|member|rcvov_intr
id|rcvov_intr
suffix:colon
l_int|1
comma
DECL|member|bwalloc_intr
id|bwalloc_intr
suffix:colon
l_int|1
comma
DECL|member|rsvd2
id|rsvd2
suffix:colon
l_int|7
comma
DECL|member|obuf_intr
id|obuf_intr
suffix:colon
l_int|1
comma
DECL|member|idest_intr
id|idest_intr
suffix:colon
l_int|1
comma
DECL|member|llp_credit
id|llp_credit
suffix:colon
l_int|5
comma
DECL|member|force_badllp
id|force_badllp
suffix:colon
l_int|1
comma
DECL|member|send_bm8
id|send_bm8
suffix:colon
l_int|1
comma
DECL|member|inbuf_level
id|inbuf_level
suffix:colon
l_int|3
comma
DECL|member|perf_mode
id|perf_mode
suffix:colon
l_int|2
comma
DECL|member|rsvd1
id|rsvd1
suffix:colon
l_int|1
comma
DECL|member|alive_intr
id|alive_intr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|xb_linkcontrol
)brace
id|xb_linkcontrol
suffix:semicolon
DECL|typedef|xbow_linkctrl_t
)brace
id|xbow_linkctrl_t
suffix:semicolon
macro_line|#else
DECL|union|xbow_linkctrl_u
r_typedef
r_union
id|xbow_linkctrl_u
(brace
DECL|member|xbl_ctrlword
id|xbowreg_t
id|xbl_ctrlword
suffix:semicolon
r_struct
(brace
DECL|member|alive_intr
r_uint32
id|alive_intr
suffix:colon
l_int|1
comma
DECL|member|rsvd1
id|rsvd1
suffix:colon
l_int|1
comma
DECL|member|perf_mode
id|perf_mode
suffix:colon
l_int|2
comma
DECL|member|inbuf_level
id|inbuf_level
suffix:colon
l_int|3
comma
DECL|member|send_bm8
id|send_bm8
suffix:colon
l_int|1
comma
DECL|member|force_badllp
id|force_badllp
suffix:colon
l_int|1
comma
DECL|member|llp_credit
id|llp_credit
suffix:colon
l_int|5
comma
DECL|member|idest_intr
id|idest_intr
suffix:colon
l_int|1
comma
DECL|member|obuf_intr
id|obuf_intr
suffix:colon
l_int|1
comma
DECL|member|rsvd2
id|rsvd2
suffix:colon
l_int|7
comma
DECL|member|bwalloc_intr
id|bwalloc_intr
suffix:colon
l_int|1
comma
DECL|member|rcvov_intr
id|rcvov_intr
suffix:colon
l_int|1
comma
DECL|member|trxov_intr
id|trxov_intr
suffix:colon
l_int|1
comma
DECL|member|trx_max_retry_intr
id|trx_max_retry_intr
suffix:colon
l_int|1
comma
DECL|member|rcv_err_intr
id|rcv_err_intr
suffix:colon
l_int|1
comma
DECL|member|trx_retry_intr
id|trx_retry_intr
suffix:colon
l_int|1
comma
DECL|member|rsvd3
id|rsvd3
suffix:colon
l_int|1
comma
DECL|member|maxto_intr
id|maxto_intr
suffix:colon
l_int|1
comma
DECL|member|srcto_intr
id|srcto_intr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|xb_linkcontrol
)brace
id|xb_linkcontrol
suffix:semicolon
DECL|typedef|xbow_linkctrl_t
)brace
id|xbow_linkctrl_t
suffix:semicolon
macro_line|#endif
DECL|macro|xbctl_accerr_intr
mdefine_line|#define&t;xbctl_accerr_intr&t;(xbw0_ctrlfield.accerr_intr)
DECL|macro|xbctl_xtalkerr_intr
mdefine_line|#define&t;xbctl_xtalkerr_intr&t;(xbw0_ctrlfield.xtalkerr_intr)
DECL|macro|xbctl_cnntout_intr
mdefine_line|#define&t;xbctl_cnntout_intr&t;(xbw0_ctrlfield.conntout_intr)
DECL|macro|XBW0_CTRL_ACCERR_INTR
mdefine_line|#define&t;XBW0_CTRL_ACCERR_INTR&t;(1 &lt;&lt; 5)
DECL|macro|XBW0_CTRL_XTERR_INTR
mdefine_line|#define&t;XBW0_CTRL_XTERR_INTR&t;(1 &lt;&lt; 2)
DECL|macro|XBW0_CTRL_CONNTOUT_INTR
mdefine_line|#define&t;XBW0_CTRL_CONNTOUT_INTR&t;(1 &lt;&lt; 1)
multiline_comment|/*&n; * Xbow Link specific Registers structure definitions.&n; */
macro_line|#ifdef LITTLE_ENDIAN
DECL|union|xbow_linkX_status_u
r_typedef
r_union
id|xbow_linkX_status_u
(brace
DECL|member|linkstatus
id|xbowreg_t
id|linkstatus
suffix:semicolon
r_struct
(brace
DECL|member|pkt_toutsrc
r_uint32
id|pkt_toutsrc
suffix:colon
l_int|1
comma
DECL|member|pkt_toutconn
id|pkt_toutconn
suffix:colon
l_int|1
comma
multiline_comment|/* max_req_tout in Xbridge */
DECL|member|pkt_toutdest
id|pkt_toutdest
suffix:colon
l_int|1
comma
multiline_comment|/* reserved in Xbridge */
DECL|member|llp_xmitretry
id|llp_xmitretry
suffix:colon
l_int|1
comma
DECL|member|llp_rcverror
id|llp_rcverror
suffix:colon
l_int|1
comma
DECL|member|llp_maxtxretry
id|llp_maxtxretry
suffix:colon
l_int|1
comma
DECL|member|llp_txovflow
id|llp_txovflow
suffix:colon
l_int|1
comma
DECL|member|llp_rxovflow
id|llp_rxovflow
suffix:colon
l_int|1
comma
DECL|member|bw_errport
id|bw_errport
suffix:colon
l_int|8
comma
multiline_comment|/* BW allocation error port   */
DECL|member|ioe
id|ioe
suffix:colon
l_int|1
comma
multiline_comment|/* Input overallocation error */
DECL|member|illdest
id|illdest
suffix:colon
l_int|1
comma
DECL|member|merror
id|merror
suffix:colon
l_int|1
comma
DECL|member|resvd1
id|resvd1
suffix:colon
l_int|12
comma
DECL|member|alive
id|alive
suffix:colon
l_int|1
suffix:semicolon
DECL|member|xb_linkstatus
)brace
id|xb_linkstatus
suffix:semicolon
DECL|typedef|xbwX_stat_t
)brace
id|xbwX_stat_t
suffix:semicolon
macro_line|#else
DECL|union|xbow_linkX_status_u
r_typedef
r_union
id|xbow_linkX_status_u
(brace
DECL|member|linkstatus
id|xbowreg_t
id|linkstatus
suffix:semicolon
r_struct
(brace
DECL|member|alive
r_uint32
id|alive
suffix:colon
l_int|1
comma
DECL|member|resvd1
id|resvd1
suffix:colon
l_int|12
comma
DECL|member|merror
id|merror
suffix:colon
l_int|1
comma
DECL|member|illdest
id|illdest
suffix:colon
l_int|1
comma
DECL|member|ioe
id|ioe
suffix:colon
l_int|1
comma
multiline_comment|/* Input overallocation error */
DECL|member|bw_errport
id|bw_errport
suffix:colon
l_int|8
comma
multiline_comment|/* BW allocation error port   */
DECL|member|llp_rxovflow
id|llp_rxovflow
suffix:colon
l_int|1
comma
DECL|member|llp_txovflow
id|llp_txovflow
suffix:colon
l_int|1
comma
DECL|member|llp_maxtxretry
id|llp_maxtxretry
suffix:colon
l_int|1
comma
DECL|member|llp_rcverror
id|llp_rcverror
suffix:colon
l_int|1
comma
DECL|member|llp_xmitretry
id|llp_xmitretry
suffix:colon
l_int|1
comma
DECL|member|pkt_toutdest
id|pkt_toutdest
suffix:colon
l_int|1
comma
multiline_comment|/* reserved in Xbridge */
DECL|member|pkt_toutconn
id|pkt_toutconn
suffix:colon
l_int|1
comma
multiline_comment|/* max_req_tout in Xbridge */
DECL|member|pkt_toutsrc
id|pkt_toutsrc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|xb_linkstatus
)brace
id|xb_linkstatus
suffix:semicolon
DECL|typedef|xbwX_stat_t
)brace
id|xbwX_stat_t
suffix:semicolon
macro_line|#endif
DECL|macro|link_alive
mdefine_line|#define&t;link_alive&t;&t;xb_linkstatus.alive
DECL|macro|link_multierror
mdefine_line|#define&t;link_multierror&t;&t;xb_linkstatus.merror
DECL|macro|link_illegal_dest
mdefine_line|#define&t;link_illegal_dest&t;xb_linkstatus.illdest
DECL|macro|link_ioe
mdefine_line|#define&t;link_ioe&t;&t;xb_linkstatus.ioe
DECL|macro|link_max_req_tout
mdefine_line|#define link_max_req_tout&t;xb_linkstatus.pkt_toutconn  /* Xbridge */
DECL|macro|link_pkt_toutconn
mdefine_line|#define link_pkt_toutconn&t;xb_linkstatus.pkt_toutconn  /* Xbow */
DECL|macro|link_pkt_toutdest
mdefine_line|#define link_pkt_toutdest&t;xb_linkstatus.pkt_toutdest
DECL|macro|link_pkt_toutsrc
mdefine_line|#define&t;link_pkt_toutsrc&t;xb_linkstatus.pkt_toutsrc
macro_line|#ifdef LITTLE_ENDIAN
DECL|union|xbow_aux_linkX_status_u
r_typedef
r_union
id|xbow_aux_linkX_status_u
(brace
DECL|member|aux_linkstatus
id|xbowreg_t
id|aux_linkstatus
suffix:semicolon
r_struct
(brace
DECL|member|rsvd2
r_uint32
id|rsvd2
suffix:colon
l_int|4
comma
DECL|member|bit_mode_8
id|bit_mode_8
suffix:colon
l_int|1
comma
DECL|member|wid_present
id|wid_present
suffix:colon
l_int|1
comma
DECL|member|fail_mode
id|fail_mode
suffix:colon
l_int|1
comma
DECL|member|rsvd1
id|rsvd1
suffix:colon
l_int|1
comma
DECL|member|to_src_loc
id|to_src_loc
suffix:colon
l_int|8
comma
DECL|member|tx_retry_cnt
id|tx_retry_cnt
suffix:colon
l_int|8
comma
DECL|member|rx_err_cnt
id|rx_err_cnt
suffix:colon
l_int|8
suffix:semicolon
DECL|member|xb_aux_linkstatus
)brace
id|xb_aux_linkstatus
suffix:semicolon
DECL|typedef|xbow_aux_link_status_t
)brace
id|xbow_aux_link_status_t
suffix:semicolon
macro_line|#else
DECL|union|xbow_aux_linkX_status_u
r_typedef
r_union
id|xbow_aux_linkX_status_u
(brace
DECL|member|aux_linkstatus
id|xbowreg_t
id|aux_linkstatus
suffix:semicolon
r_struct
(brace
DECL|member|rx_err_cnt
r_uint32
id|rx_err_cnt
suffix:colon
l_int|8
comma
DECL|member|tx_retry_cnt
id|tx_retry_cnt
suffix:colon
l_int|8
comma
DECL|member|to_src_loc
id|to_src_loc
suffix:colon
l_int|8
comma
DECL|member|rsvd1
id|rsvd1
suffix:colon
l_int|1
comma
DECL|member|fail_mode
id|fail_mode
suffix:colon
l_int|1
comma
DECL|member|wid_present
id|wid_present
suffix:colon
l_int|1
comma
DECL|member|bit_mode_8
id|bit_mode_8
suffix:colon
l_int|1
comma
DECL|member|rsvd2
id|rsvd2
suffix:colon
l_int|4
suffix:semicolon
DECL|member|xb_aux_linkstatus
)brace
id|xb_aux_linkstatus
suffix:semicolon
DECL|typedef|xbow_aux_link_status_t
)brace
id|xbow_aux_link_status_t
suffix:semicolon
macro_line|#endif
macro_line|#ifdef LITTLE_ENDIAN
DECL|union|xbow_perf_count_u
r_typedef
r_union
id|xbow_perf_count_u
(brace
DECL|member|xb_counter_val
id|xbowreg_t
id|xb_counter_val
suffix:semicolon
r_struct
(brace
DECL|member|count
r_uint32
id|count
suffix:colon
l_int|20
comma
DECL|member|link_select
id|link_select
suffix:colon
l_int|3
comma
DECL|member|rsvd
id|rsvd
suffix:colon
l_int|9
suffix:semicolon
DECL|member|xb_perf
)brace
id|xb_perf
suffix:semicolon
DECL|typedef|xbow_perfcount_t
)brace
id|xbow_perfcount_t
suffix:semicolon
macro_line|#else
DECL|union|xbow_perf_count_u
r_typedef
r_union
id|xbow_perf_count_u
(brace
DECL|member|xb_counter_val
id|xbowreg_t
id|xb_counter_val
suffix:semicolon
r_struct
(brace
DECL|member|rsvd
r_uint32
id|rsvd
suffix:colon
l_int|9
comma
DECL|member|link_select
id|link_select
suffix:colon
l_int|3
comma
DECL|member|count
id|count
suffix:colon
l_int|20
suffix:semicolon
DECL|member|xb_perf
)brace
id|xb_perf
suffix:semicolon
DECL|typedef|xbow_perfcount_t
)brace
id|xbow_perfcount_t
suffix:semicolon
macro_line|#endif
DECL|macro|XBOW_COUNTER_MASK
mdefine_line|#define XBOW_COUNTER_MASK&t;0xFFFFF
r_extern
r_int
id|xbow_widget_present
c_func
(paren
id|xbow_t
op_star
id|xbow
comma
r_int
id|port
)paren
suffix:semicolon
r_extern
id|xwidget_intr_preset_f
id|xbow_intr_preset
suffix:semicolon
r_extern
id|xswitch_reset_link_f
id|xbow_reset_link
suffix:semicolon
r_void
id|xbow_mlreset
c_func
(paren
id|xbow_t
op_star
)paren
suffix:semicolon
multiline_comment|/* ========================================================================&n; */
macro_line|#ifdef&t;MACROFIELD_LINE
multiline_comment|/*&n; * This table forms a relation between the byte offset macros normally&n; * used for ASM coding and the calculated byte offsets of the fields&n; * in the C structure.&n; *&n; * See xbow_check.c xbow_html.c for further details.&n; */
macro_line|#ifndef MACROFIELD_LINE_BITFIELD
DECL|macro|MACROFIELD_LINE_BITFIELD
mdefine_line|#define MACROFIELD_LINE_BITFIELD(m)&t;/* ignored */
macro_line|#endif
DECL|variable|xbow_macrofield
r_struct
id|macrofield_s
id|xbow_macrofield
(braket
)braket
op_assign
(brace
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_ID
comma
id|xb_wid_id
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_STAT
comma
id|xb_wid_stat
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_WID_STAT_LINK_INTR
c_func
(paren
l_int|0xF
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_WID_STAT_LINK_INTR
c_func
(paren
l_int|0xE
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_WID_STAT_LINK_INTR
c_func
(paren
l_int|0xD
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_WID_STAT_LINK_INTR
c_func
(paren
l_int|0xC
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_WID_STAT_LINK_INTR
c_func
(paren
l_int|0xB
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_WID_STAT_LINK_INTR
c_func
(paren
l_int|0xA
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_WID_STAT_LINK_INTR
c_func
(paren
l_int|0x9
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_WID_STAT_LINK_INTR
c_func
(paren
l_int|0x8
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_WID_STAT_WIDGET0_INTR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_WID_STAT_REG_ACC_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_WID_STAT_XTALK_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_WID_STAT_MULTI_ERR
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_ERR_UPPER
comma
id|xb_wid_err_upper
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_ERR_LOWER
comma
id|xb_wid_err_lower
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_CONTROL
comma
id|xb_wid_control
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_WID_CTRL_REG_ACC_IE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_WID_CTRL_XTALK_IE
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_REQ_TO
comma
id|xb_wid_req_timeout
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_INT_UPPER
comma
id|xb_wid_int_upper
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_INT_LOWER
comma
id|xb_wid_int_lower
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_ERR_CMDWORD
comma
id|xb_wid_err_cmdword
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_LLP
comma
id|xb_wid_llp
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_STAT_CLR
comma
id|xb_wid_stat_clr
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_ARB_RELOAD
comma
id|xb_wid_arb_reload
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_PERF_CTR_A
comma
id|xb_perf_ctr_a
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_PERF_CTR_B
comma
id|xb_perf_ctr_b
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XBOW_WID_NIC
comma
id|xb_nic
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_REG_BASE
c_func
(paren
l_int|8
)paren
comma
id|xb_link
c_func
(paren
l_int|8
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_IBUF_FLUSH
c_func
(paren
l_int|8
)paren
comma
id|xb_link
c_func
(paren
l_int|8
)paren
dot
id|link_ibf
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_CTRL
c_func
(paren
l_int|8
)paren
comma
id|xb_link
c_func
(paren
l_int|8
)paren
dot
id|link_control
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_LINKALIVE_IE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_PERF_CTR_MODE_MSK
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_IBUF_LEVEL_MSK
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_8BIT_MODE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_BAD_LLP_PKT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_WIDGET_CR_MSK
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_ILLEGAL_DST_IE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_OALLOC_IBUF_IE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_BNDWDTH_ALLOC_IE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_RCV_CNT_OFLOW_IE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_XMT_CNT_OFLOW_IE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_XMT_MAX_RTRY_IE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_RCV_IE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_XMT_RTRY_IE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_MAXREQ_TOUT_IE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_CTRL_SRC_TOUT_IE
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_STATUS
c_func
(paren
l_int|8
)paren
comma
id|xb_link
c_func
(paren
l_int|8
)paren
dot
id|link_status
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_STAT_LINKALIVE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_STAT_MULTI_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_STAT_ILLEGAL_DST_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_STAT_OALLOC_IBUF_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_STAT_BNDWDTH_ALLOC_ID_MSK
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_STAT_RCV_CNT_OFLOW_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_STAT_XMT_CNT_OFLOW_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_STAT_XMT_MAX_RTRY_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_STAT_RCV_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_STAT_XMT_RTRY_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_STAT_MAXREQ_TOUT_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_STAT_SRC_TOUT_ERR
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_ARB_UPPER
c_func
(paren
l_int|8
)paren
comma
id|xb_link
c_func
(paren
l_int|8
)paren
dot
id|link_arb_upper
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_RR_MSK
op_lshift
id|XB_ARB_RR_SHFT
c_func
(paren
l_int|0xb
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_GBR_MSK
op_lshift
id|XB_ARB_GBR_SHFT
c_func
(paren
l_int|0xb
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_RR_MSK
op_lshift
id|XB_ARB_RR_SHFT
c_func
(paren
l_int|0xa
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_GBR_MSK
op_lshift
id|XB_ARB_GBR_SHFT
c_func
(paren
l_int|0xa
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_RR_MSK
op_lshift
id|XB_ARB_RR_SHFT
c_func
(paren
l_int|0x9
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_GBR_MSK
op_lshift
id|XB_ARB_GBR_SHFT
c_func
(paren
l_int|0x9
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_RR_MSK
op_lshift
id|XB_ARB_RR_SHFT
c_func
(paren
l_int|0x8
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_GBR_MSK
op_lshift
id|XB_ARB_GBR_SHFT
c_func
(paren
l_int|0x8
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_ARB_LOWER
c_func
(paren
l_int|8
)paren
comma
id|xb_link
c_func
(paren
l_int|8
)paren
dot
id|link_arb_lower
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_RR_MSK
op_lshift
id|XB_ARB_RR_SHFT
c_func
(paren
l_int|0xf
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_GBR_MSK
op_lshift
id|XB_ARB_GBR_SHFT
c_func
(paren
l_int|0xf
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_RR_MSK
op_lshift
id|XB_ARB_RR_SHFT
c_func
(paren
l_int|0xe
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_GBR_MSK
op_lshift
id|XB_ARB_GBR_SHFT
c_func
(paren
l_int|0xe
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_RR_MSK
op_lshift
id|XB_ARB_RR_SHFT
c_func
(paren
l_int|0xd
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_GBR_MSK
op_lshift
id|XB_ARB_GBR_SHFT
c_func
(paren
l_int|0xd
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_RR_MSK
op_lshift
id|XB_ARB_RR_SHFT
c_func
(paren
l_int|0xc
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_ARB_GBR_MSK
op_lshift
id|XB_ARB_GBR_SHFT
c_func
(paren
l_int|0xc
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_STATUS_CLR
c_func
(paren
l_int|8
)paren
comma
id|xb_link
c_func
(paren
l_int|8
)paren
dot
id|link_status_clr
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_RESET
c_func
(paren
l_int|8
)paren
comma
id|xb_link
c_func
(paren
l_int|8
)paren
dot
id|link_reset
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_AUX_STATUS
c_func
(paren
l_int|8
)paren
comma
id|xb_link
c_func
(paren
l_int|8
)paren
dot
id|link_aux_status
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_AUX_STAT_RCV_CNT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_AUX_STAT_XMT_CNT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_AUX_LINKFAIL_RST_BAD
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_AUX_STAT_PRESENT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_AUX_STAT_PORT_WIDTH
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|XB_AUX_STAT_TOUT_DST
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_REG_BASE
c_func
(paren
l_int|0x8
)paren
comma
id|xb_link
c_func
(paren
l_int|0x8
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_REG_BASE
c_func
(paren
l_int|0x9
)paren
comma
id|xb_link
c_func
(paren
l_int|0x9
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_REG_BASE
c_func
(paren
l_int|0xA
)paren
comma
id|xb_link
c_func
(paren
l_int|0xA
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_REG_BASE
c_func
(paren
l_int|0xB
)paren
comma
id|xb_link
c_func
(paren
l_int|0xB
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_REG_BASE
c_func
(paren
l_int|0xC
)paren
comma
id|xb_link
c_func
(paren
l_int|0xC
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_REG_BASE
c_func
(paren
l_int|0xD
)paren
comma
id|xb_link
c_func
(paren
l_int|0xD
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_REG_BASE
c_func
(paren
l_int|0xE
)paren
comma
id|xb_link
c_func
(paren
l_int|0xE
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|XB_LINK_REG_BASE
c_func
(paren
l_int|0xF
)paren
comma
id|xb_link
c_func
(paren
l_int|0xF
)paren
)paren
)brace
suffix:semicolon
multiline_comment|/* xbow_macrofield[] */
macro_line|#endif&t;&t;&t;&t;/* MACROFIELD_LINE */
macro_line|#endif&t;&t;&t;&t;/* _LANGUAGE_C */
macro_line|#endif                          /* _ASM_SN_SN_XTALK_XBOW_H */
eof
