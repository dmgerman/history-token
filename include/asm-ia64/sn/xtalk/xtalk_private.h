multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997, 2000-2002 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#ifndef _ASM_SN_XTALK_XTALK_PRIVATE_H
DECL|macro|_ASM_SN_XTALK_XTALK_PRIVATE_H
mdefine_line|#define _ASM_SN_XTALK_XTALK_PRIVATE_H
macro_line|#include &lt;asm/sn/ioerror.h&gt;        /* for error function and arg types */
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xwidget.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xtalk.h&gt;
multiline_comment|/*&n; * xtalk_private.h -- private definitions for xtalk&n; * crosstalk drivers should NOT include this file.&n; */
multiline_comment|/*&n; * All Crosstalk providers set up PIO using this information.&n; */
DECL|struct|xtalk_piomap_s
r_struct
id|xtalk_piomap_s
(brace
DECL|member|xp_dev
id|devfs_handle_t
id|xp_dev
suffix:semicolon
multiline_comment|/* a requestor of this mapping */
DECL|member|xp_target
id|xwidgetnum_t
id|xp_target
suffix:semicolon
multiline_comment|/* target (node&squot;s widget number) */
DECL|member|xp_xtalk_addr
id|iopaddr_t
id|xp_xtalk_addr
suffix:semicolon
multiline_comment|/* which crosstalk addr is mapped */
DECL|member|xp_mapsz
r_int
id|xp_mapsz
suffix:semicolon
multiline_comment|/* size of this mapping */
DECL|member|xp_kvaddr
id|caddr_t
id|xp_kvaddr
suffix:semicolon
multiline_comment|/* kernel virtual address to use */
)brace
suffix:semicolon
multiline_comment|/*&n; * All Crosstalk providers set up DMA using this information.&n; */
DECL|struct|xtalk_dmamap_s
r_struct
id|xtalk_dmamap_s
(brace
DECL|member|xd_dev
id|devfs_handle_t
id|xd_dev
suffix:semicolon
multiline_comment|/* a requestor of this mapping */
DECL|member|xd_target
id|xwidgetnum_t
id|xd_target
suffix:semicolon
multiline_comment|/* target (node&squot;s widget number) */
)brace
suffix:semicolon
multiline_comment|/*&n; * All Crosstalk providers set up interrupts using this information.&n; */
DECL|struct|xtalk_intr_s
r_struct
id|xtalk_intr_s
(brace
DECL|member|xi_dev
id|devfs_handle_t
id|xi_dev
suffix:semicolon
multiline_comment|/* requestor of this intr */
DECL|member|xi_target
id|xwidgetnum_t
id|xi_target
suffix:semicolon
multiline_comment|/* master&squot;s widget number */
DECL|member|xi_vector
id|xtalk_intr_vector_t
id|xi_vector
suffix:semicolon
multiline_comment|/* 8-bit interrupt vector */
DECL|member|xi_addr
id|iopaddr_t
id|xi_addr
suffix:semicolon
multiline_comment|/* xtalk address to generate intr */
DECL|member|xi_sfarg
r_void
op_star
id|xi_sfarg
suffix:semicolon
multiline_comment|/* argument for setfunc */
DECL|member|xi_setfunc
id|xtalk_intr_setfunc_t
id|xi_setfunc
suffix:semicolon
multiline_comment|/* device&squot;s setfunc routine */
)brace
suffix:semicolon
multiline_comment|/*&n; * Xtalk interrupt handler structure access functions&n; */
DECL|macro|xtalk_intr_arg
mdefine_line|#define&t;xtalk_intr_arg(xt)&t;((xt)-&gt;xi_sfarg)
DECL|macro|xwidget_hwid_is_sn0_xswitch
mdefine_line|#define&t;xwidget_hwid_is_sn0_xswitch(_hwid)&t;&bslash;&n;&t;&t;(((_hwid)-&gt;part_num == XBOW_WIDGET_PART_NUM ) &amp;&amp;  &t;&bslash;&n;&t;&t; ((_hwid)-&gt;mfg_num == XBOW_WIDGET_MFGR_NUM ))
DECL|macro|xwidget_hwid_is_sn1_xswitch
mdefine_line|#define&t;xwidget_hwid_is_sn1_xswitch(_hwid)&t;&bslash;&n;&t;&t;(((_hwid)-&gt;part_num == XXBOW_WIDGET_PART_NUM ) &amp;&amp;  &t;&bslash;&n;&t;&t; ((_hwid)-&gt;mfg_num == XXBOW_WIDGET_MFGR_NUM ))
DECL|macro|xwidget_hwid_is_xswitch
mdefine_line|#define&t;xwidget_hwid_is_xswitch(_hwid)&t;&bslash;&n;&t;&t;(xwidget_hwid_is_sn0_xswitch(_hwid) ||&t;&t;&t;&bslash;&n;&t;&t;&t;xwidget_hwid_is_sn1_xswitch(_hwid))
multiline_comment|/* common iograph info for all widgets,&n; * stashed in FASTINFO of widget connection points.&n; */
DECL|struct|xwidget_info_s
r_struct
id|xwidget_info_s
(brace
DECL|member|w_fingerprint
r_char
op_star
id|w_fingerprint
suffix:semicolon
DECL|member|w_vertex
id|devfs_handle_t
id|w_vertex
suffix:semicolon
multiline_comment|/* back pointer to vertex */
DECL|member|w_id
id|xwidgetnum_t
id|w_id
suffix:semicolon
multiline_comment|/* widget id */
DECL|member|w_hwid
r_struct
id|xwidget_hwid_s
id|w_hwid
suffix:semicolon
multiline_comment|/* hardware identification (part/rev/mfg) */
DECL|member|w_master
id|devfs_handle_t
id|w_master
suffix:semicolon
multiline_comment|/* CACHED widget&squot;s master */
DECL|member|w_masterid
id|xwidgetnum_t
id|w_masterid
suffix:semicolon
multiline_comment|/* CACHED widget&squot;s master&squot;s widgetnum */
DECL|member|w_efunc
id|error_handler_f
op_star
id|w_efunc
suffix:semicolon
multiline_comment|/* error handling function */
DECL|member|w_einfo
id|error_handler_arg_t
id|w_einfo
suffix:semicolon
multiline_comment|/* first parameter for efunc */
DECL|member|w_name
r_char
op_star
id|w_name
suffix:semicolon
multiline_comment|/* canonical hwgraph name */
)brace
suffix:semicolon
r_extern
r_char
id|widget_info_fingerprint
(braket
)braket
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ASM_SN_XTALK_XTALK_PRIVATE_H */
eof
