multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992-1997,2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/module.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
DECL|variable|master_procid
id|cpuid_t
id|master_procid
suffix:semicolon
multiline_comment|/*&n; * Routines provided by ml/SN/promif.c.&n; */
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
DECL|variable|master_baseio_wid
r_char
id|master_baseio_wid
suffix:semicolon
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
DECL|function|is_master_baseio_nasid_widget
id|is_master_baseio_nasid_widget
c_func
(paren
id|nasid_t
id|test_nasid
comma
id|xwidgetnum_t
id|test_wid
)paren
(brace
r_extern
id|nasid_t
id|master_baseio_nasid
suffix:semicolon
multiline_comment|/*&n;         * If the widget numbers are different, we&squot;re not the master.&n;         */
r_if
c_cond
(paren
id|test_wid
op_ne
(paren
id|xwidgetnum_t
)paren
id|master_baseio_wid
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;         * If the NASIDs are the same or equivalent, we&squot;re the master.&n;         */
r_if
c_cond
(paren
id|check_nasid_equiv
c_func
(paren
id|test_nasid
comma
id|master_baseio_nasid
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
eof
