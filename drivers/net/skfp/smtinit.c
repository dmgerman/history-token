multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;See the file &quot;skfddi.c&quot; for further information.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/*&n;&t;Init SMT&n;&t;call all module level initialization routines&n;*/
macro_line|#include &quot;h/types.h&quot;
macro_line|#include &quot;h/fddi.h&quot;
macro_line|#include &quot;h/smc.h&quot;
macro_line|#ifndef&t;lint
DECL|variable|ID_sccs
r_static
r_const
r_char
id|ID_sccs
(braket
)braket
op_assign
l_string|&quot;@(#)smtinit.c&t;1.15 97/05/06 (C) SK &quot;
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|init_fddi_driver
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* define global debug variable */
macro_line|#if defined(DEBUG) &amp;&amp; !defined(DEBUG_BRD)
DECL|variable|debug
r_struct
id|smt_debug
id|debug
suffix:semicolon
macro_line|#endif
macro_line|#ifndef MULT_OEM
DECL|macro|OEMID
mdefine_line|#define OEMID(smc,i)&t;oem_id[i]
r_extern
id|u_char
id|oem_id
(braket
)braket
suffix:semicolon
macro_line|#else&t;/* MULT_OEM */
DECL|macro|OEMID
mdefine_line|#define OEMID(smc,i)&t;smc-&gt;hw.oem_id-&gt;oi_mark[i]
r_extern
r_struct
id|s_oem_ids
id|oem_ids
(braket
)braket
suffix:semicolon
macro_line|#endif&t;/* MULT_OEM */
multiline_comment|/*&n; * Set OEM specific values&n; *&n; * Can not be called in smt_reset_defaults, because it is not sure that&n; * the OEM ID is already defined.&n; */
DECL|function|set_oem_spec_val
r_static
r_void
id|set_oem_spec_val
c_func
(paren
id|smc
)paren
r_struct
id|s_smc
op_star
id|smc
suffix:semicolon
(brace
r_struct
id|fddi_mib
op_star
id|mib
suffix:semicolon
id|mib
op_assign
op_amp
id|smc-&gt;mib
suffix:semicolon
multiline_comment|/*&n;&t; * set IBM specific values&n;&t; */
r_if
c_cond
(paren
id|OEMID
c_func
(paren
id|smc
comma
l_int|0
)paren
op_eq
l_char|&squot;I&squot;
)paren
(brace
id|mib-&gt;fddiSMTConnectionPolicy
op_assign
id|POLICY_MM
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Init SMT&n; */
DECL|function|init_smt
r_int
id|init_smt
c_func
(paren
id|smc
comma
id|mac_addr
)paren
r_struct
id|s_smc
op_star
id|smc
suffix:semicolon
id|u_char
op_star
id|mac_addr
suffix:semicolon
multiline_comment|/* canonical address or NULL */
(brace
r_int
id|p
suffix:semicolon
macro_line|#if defined(DEBUG) &amp;&amp; !defined(DEBUG_BRD)
id|debug.d_smt
op_assign
l_int|0
suffix:semicolon
id|debug.d_smtf
op_assign
l_int|0
suffix:semicolon
id|debug.d_rmt
op_assign
l_int|0
suffix:semicolon
id|debug.d_ecm
op_assign
l_int|0
suffix:semicolon
id|debug.d_pcm
op_assign
l_int|0
suffix:semicolon
id|debug.d_cfm
op_assign
l_int|0
suffix:semicolon
id|debug.d_plc
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef&t;ESS
id|debug.d_ess
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#ifdef&t;SBA
id|debug.d_sba
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* DEBUG &amp;&amp; !DEBUG_BRD */
multiline_comment|/* First initialize the ports mib-&gt;pointers */
r_for
c_loop
(paren
id|p
op_assign
l_int|0
suffix:semicolon
id|p
OL
id|NUMPHYS
suffix:semicolon
id|p
op_increment
)paren
(brace
id|smc-&gt;y
(braket
id|p
)braket
dot
id|mib
op_assign
op_amp
id|smc-&gt;mib.p
(braket
id|p
)braket
suffix:semicolon
)brace
id|set_oem_spec_val
c_func
(paren
id|smc
)paren
suffix:semicolon
(paren
r_void
)paren
id|smt_set_mac_opvalues
c_func
(paren
id|smc
)paren
suffix:semicolon
id|init_fddi_driver
c_func
(paren
id|smc
comma
id|mac_addr
)paren
suffix:semicolon
multiline_comment|/* HW driver */
id|smt_fixup_mib
c_func
(paren
id|smc
)paren
suffix:semicolon
multiline_comment|/* update values that depend on s.sas */
id|ev_init
c_func
(paren
id|smc
)paren
suffix:semicolon
multiline_comment|/* event queue */
macro_line|#ifndef&t;SLIM_SMT
id|smt_init_evc
c_func
(paren
id|smc
)paren
suffix:semicolon
multiline_comment|/* evcs in MIB */
macro_line|#endif&t;/* no SLIM_SMT */
id|smt_timer_init
c_func
(paren
id|smc
)paren
suffix:semicolon
multiline_comment|/* timer package */
id|smt_agent_init
c_func
(paren
id|smc
)paren
suffix:semicolon
multiline_comment|/* SMT frame manager */
id|pcm_init
c_func
(paren
id|smc
)paren
suffix:semicolon
multiline_comment|/* PCM state machine */
id|ecm_init
c_func
(paren
id|smc
)paren
suffix:semicolon
multiline_comment|/* ECM state machine */
id|cfm_init
c_func
(paren
id|smc
)paren
suffix:semicolon
multiline_comment|/* CFM state machine */
id|rmt_init
c_func
(paren
id|smc
)paren
suffix:semicolon
multiline_comment|/* RMT state machine */
r_for
c_loop
(paren
id|p
op_assign
l_int|0
suffix:semicolon
id|p
OL
id|NUMPHYS
suffix:semicolon
id|p
op_increment
)paren
(brace
id|pcm
c_func
(paren
id|smc
comma
id|p
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* PCM A state machine */
)brace
id|ecm
c_func
(paren
id|smc
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* ECM state machine */
id|cfm
c_func
(paren
id|smc
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* CFM state machine */
id|rmt
c_func
(paren
id|smc
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* RMT state machine */
id|smt_agent_task
c_func
(paren
id|smc
)paren
suffix:semicolon
multiline_comment|/* NIF FSM etc */
id|PNMI_INIT
c_func
(paren
id|smc
)paren
suffix:semicolon
multiline_comment|/* PNMI initialization */
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
eof
