multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2001 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/module.h&gt;
macro_line|#include &lt;asm/sn/nic.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
DECL|variable|master_procid
id|cpuid_t
id|master_procid
op_assign
l_int|0
suffix:semicolon
DECL|variable|arg_maxnodes
r_char
id|arg_maxnodes
(braket
l_int|4
)braket
suffix:semicolon
r_extern
r_void
id|init_all_devices
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_IA64_SGI_SN1)
DECL|variable|Synergy_da_indr
id|synergy_da_t
op_star
id|Synergy_da_indr
(braket
id|MAX_COMPACT_NODES
op_star
l_int|2
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Return non-zero if the given variable was specified&n; */
r_int
DECL|function|is_specified
id|is_specified
c_func
(paren
r_char
op_star
id|s
)paren
(brace
r_return
(paren
id|strlen
c_func
(paren
id|s
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|xbmon_init
r_void
id|xbmon_init
c_func
(paren
r_void
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;xbmon_init : no-op&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|pciiox_init
r_void
id|pciiox_init
c_func
(paren
r_void
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;pciiox_init : no-op&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|usrpci_init
r_void
id|usrpci_init
c_func
(paren
r_void
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;usrpci_init : no-op&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|ioc3_init
r_void
id|ioc3_init
c_func
(paren
r_void
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;ioc3_init : no-op&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|initialize_io
r_void
id|initialize_io
c_func
(paren
r_void
)paren
(brace
id|init_all_devices
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Routines provided by ml/SN/promif.c.&n; */
DECL|variable|master_bridge_base
r_static
id|__psunsigned_t
id|master_bridge_base
op_assign
(paren
id|__psunsigned_t
)paren
l_int|NULL
suffix:semicolon
DECL|variable|console_nasid
id|nasid_t
id|console_nasid
op_assign
(paren
id|nasid_t
)paren
op_minus
l_int|1
suffix:semicolon
DECL|variable|console_wid
r_static
r_char
id|console_wid
suffix:semicolon
DECL|variable|console_pcislot
r_static
r_char
id|console_pcislot
suffix:semicolon
r_void
DECL|function|set_master_bridge_base
id|set_master_bridge_base
c_func
(paren
r_void
)paren
(brace
id|console_wid
op_assign
id|WIDGETID_GET
c_func
(paren
id|KL_CONFIG_CH_CONS_INFO
c_func
(paren
id|master_nasid
)paren
op_member_access_from_pointer
id|memory_base
)paren
suffix:semicolon
id|console_pcislot
op_assign
id|KL_CONFIG_CH_CONS_INFO
c_func
(paren
id|master_nasid
)paren
op_member_access_from_pointer
id|npci
suffix:semicolon
id|master_bridge_base
op_assign
(paren
id|__psunsigned_t
)paren
id|NODE_SWIN_BASE
c_func
(paren
id|console_nasid
comma
id|console_wid
)paren
suffix:semicolon
singleline_comment|// FIXME(&quot;WARNING: set_master_bridge_base: NON NASID 0 DOES NOT WORK&bslash;n&quot;);
)brace
r_int
DECL|function|check_nasid_equiv
id|check_nasid_equiv
c_func
(paren
id|nasid_t
id|nasida
comma
id|nasid_t
id|nasidb
)paren
(brace
r_if
c_cond
(paren
(paren
id|nasida
op_eq
id|nasidb
)paren
op_logical_or
(paren
id|nasida
op_eq
id|NODEPDA
c_func
(paren
id|NASID_TO_COMPACT_NODEID
c_func
(paren
id|nasidb
)paren
)paren
op_member_access_from_pointer
id|xbow_peer
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|is_master_nasid_widget
id|is_master_nasid_widget
c_func
(paren
id|nasid_t
id|test_nasid
comma
id|xwidgetnum_t
id|test_wid
)paren
(brace
multiline_comment|/*&n;         * If the widget numbers are different, we&squot;re not the master.&n;         */
r_if
c_cond
(paren
id|test_wid
op_ne
(paren
id|xwidgetnum_t
)paren
id|console_wid
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;         * If the NASIDs are the same or equivalent, we&squot;re the master.&n;         */
r_if
c_cond
(paren
id|check_nasid_equiv
c_func
(paren
id|test_nasid
comma
id|console_nasid
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Routines provided by ml/SN/nvram.c&n; */
r_void
DECL|function|nvram_baseinit
id|nvram_baseinit
c_func
(paren
r_void
)paren
(brace
id|FIXME
c_func
(paren
l_string|&quot;nvram_baseinit : no-op&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
