multiline_comment|/*&n; * Device driver for the SYMBIOS/LSILOGIC 53C8XX and 53C1010 family &n; * of PCI-SCSI IO processors.&n; *&n; * Copyright (C) 1999-2001  Gerard Roudier &lt;groudier@free.fr&gt;&n; *&n; * This driver is derived from the Linux sym53c8xx driver.&n; * Copyright (C) 1998-2000  Gerard Roudier&n; *&n; * The sym53c8xx driver is derived from the ncr53c8xx driver that had been &n; * a port of the FreeBSD ncr driver to Linux-1.2.13.&n; *&n; * The original ncr driver has been written for 386bsd and FreeBSD by&n; *         Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n; *         Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n; * Copyright (C) 1994  Wolfgang Stanglmeier&n; *&n; * Other major contributions:&n; *&n; * NVRAM detection and reading.&n; * Copyright (C) 1997 Richard Waltham &lt;dormouse@farsrobt.demon.co.uk&gt;&n; *&n; *-----------------------------------------------------------------------------&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions and the following disclaimer.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Where this Software is combined with software released under the terms of &n; * the GNU Public License (&quot;GPL&quot;) and the terms of the GPL would require the &n; * combined work to also be released under the terms of the GPL, the terms&n; * and conditions of this License will apply in addition to those of the&n; * GPL with the exception of any terms or conditions of this License that&n; * conflict with, or are expressly prohibited by, the GPL.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#ifdef __FreeBSD__
macro_line|#include &lt;dev/sym/sym_glue.h&gt;
macro_line|#else
macro_line|#include &quot;sym_glue.h&quot;
macro_line|#endif
macro_line|#ifdef&t;SYM_OPT_HANDLE_IO_TIMEOUT
multiline_comment|/*&n; *  Optional CCB timeout handling.&n; *&n; *  This code is useful for O/Ses that allow or expect &n; *  SIMs (low-level drivers) to handle SCSI IO timeouts.&n; *  It uses a power-of-two based algorithm of my own:) &n; *  that avoids scanning of lists, provided that:&n; *&n; *  - The IO does complete in less than half the associated&n; *    timeout value.&n; *  - The greatest delay between the queuing of the IO and &n; *    its completion is less than &n; *          (1&lt;&lt;(SYM_CONF_TIMEOUT_ORDER_MAX-1))/2 ticks.&n; *&n; *  For example, if tick is 1 second and the max order is 8,&n; *  any IO that is completed within less than 64 seconds will &n; *  just be put into some list at queuing and be removed &n; *  at completion without any additionnal overhead.&n; */
multiline_comment|/*&n; *  Set a timeout condition on a CCB.&n; */
DECL|function|sym_timeout_ccb
r_void
id|sym_timeout_ccb
c_func
(paren
id|hcb_p
id|np
comma
id|ccb_p
id|cp
comma
id|u_int
id|ticks
)paren
(brace
id|sym_remque
c_func
(paren
op_amp
id|cp-&gt;tmo_linkq
)paren
suffix:semicolon
id|cp-&gt;tmo_clock
op_assign
id|np-&gt;tmo_clock
op_plus
id|ticks
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ticks
)paren
(brace
id|sym_insque_head
c_func
(paren
op_amp
id|cp-&gt;tmo_linkq
comma
op_amp
id|np-&gt;tmo0_ccbq
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|i
op_assign
id|SYM_CONF_TIMEOUT_ORDER_MAX
op_minus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|i
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ticks
op_ge
(paren
l_int|1
op_lshift
(paren
id|i
op_plus
l_int|1
)paren
)paren
)paren
r_break
suffix:semicolon
op_decrement
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|np-&gt;tmo_actq
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
id|i
op_add_assign
id|SYM_CONF_TIMEOUT_ORDER_MAX
suffix:semicolon
id|sym_insque_head
c_func
(paren
op_amp
id|cp-&gt;tmo_linkq
comma
op_amp
id|np-&gt;tmo_ccbq
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  Walk a list of CCB and handle timeout conditions.&n; *  Should never be called in normal situations.&n; */
DECL|function|sym_walk_ccb_tmo_list
r_static
r_void
id|sym_walk_ccb_tmo_list
c_func
(paren
id|hcb_p
id|np
comma
id|SYM_QUEHEAD
op_star
id|tmoq
)paren
(brace
id|SYM_QUEHEAD
id|qtmp
comma
op_star
id|qp
suffix:semicolon
id|ccb_p
id|cp
suffix:semicolon
id|sym_que_move
c_func
(paren
id|tmoq
comma
op_amp
id|qtmp
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|qp
op_assign
id|sym_remque_head
c_func
(paren
op_amp
id|qtmp
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|sym_insque_head
c_func
(paren
id|qp
comma
op_amp
id|np-&gt;tmo0_ccbq
)paren
suffix:semicolon
id|cp
op_assign
id|sym_que_entry
c_func
(paren
id|qp
comma
r_struct
id|sym_ccb
comma
id|tmo_linkq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cp-&gt;tmo_clock
op_ne
id|np-&gt;tmo_clock
op_logical_and
id|cp-&gt;tmo_clock
op_plus
l_int|1
op_ne
id|np-&gt;tmo_clock
)paren
id|sym_timeout_ccb
c_func
(paren
id|np
comma
id|cp
comma
id|cp-&gt;tmo_clock
op_minus
id|np-&gt;tmo_clock
)paren
suffix:semicolon
r_else
id|sym_abort_ccb
c_func
(paren
id|np
comma
id|cp
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Our clock handler called from the O/S specific side.&n; */
DECL|function|sym_clock
r_void
id|sym_clock
c_func
(paren
id|hcb_p
id|np
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
id|u_int
id|tmp
suffix:semicolon
id|tmp
op_assign
id|np-&gt;tmo_clock
suffix:semicolon
id|tmp
op_xor_assign
(paren
op_increment
id|np-&gt;tmo_clock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SYM_CONF_TIMEOUT_ORDER_MAX
suffix:semicolon
id|i
op_increment
comma
id|tmp
op_rshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmp
op_amp
l_int|1
)paren
)paren
r_continue
suffix:semicolon
id|j
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;tmo_actq
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
id|j
op_add_assign
id|SYM_CONF_TIMEOUT_ORDER_MAX
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sym_que_empty
c_func
(paren
op_amp
id|np-&gt;tmo_ccbq
(braket
id|j
)braket
)paren
)paren
(brace
id|sym_walk_ccb_tmo_list
c_func
(paren
id|np
comma
op_amp
id|np-&gt;tmo_ccbq
(braket
id|j
)braket
)paren
suffix:semicolon
)brace
id|np-&gt;tmo_actq
op_xor_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif&t;/* SYM_OPT_HANDLE_IO_TIMEOUT */
macro_line|#ifdef&t;SYM_OPT_ANNOUNCE_TRANSFER_RATE
multiline_comment|/*&n; *  Announce transfer rate if anything changed since last announcement.&n; */
DECL|function|sym_announce_transfer_rate
r_void
id|sym_announce_transfer_rate
c_func
(paren
id|hcb_p
id|np
comma
r_int
id|target
)paren
(brace
id|tcb_p
id|tp
op_assign
op_amp
id|np-&gt;target
(braket
id|target
)braket
suffix:semicolon
DECL|macro|__tprev
mdefine_line|#define __tprev&t;tp-&gt;tinfo.prev
DECL|macro|__tcurr
mdefine_line|#define __tcurr&t;tp-&gt;tinfo.curr
r_if
c_cond
(paren
id|__tprev.options
op_eq
id|__tcurr.options
op_logical_and
id|__tprev.width
op_eq
id|__tcurr.width
op_logical_and
id|__tprev.offset
op_eq
id|__tcurr.offset
op_logical_and
op_logical_neg
(paren
id|__tprev.offset
op_logical_and
id|__tprev.period
op_ne
id|__tcurr.period
)paren
)paren
r_return
suffix:semicolon
id|__tprev.options
op_assign
id|__tcurr.options
suffix:semicolon
id|__tprev.width
op_assign
id|__tcurr.width
suffix:semicolon
id|__tprev.offset
op_assign
id|__tcurr.offset
suffix:semicolon
id|__tprev.period
op_assign
id|__tcurr.period
suffix:semicolon
r_if
c_cond
(paren
id|__tcurr.offset
op_logical_and
id|__tcurr.period
)paren
(brace
id|u_int
id|period
comma
id|f10
comma
id|mb10
suffix:semicolon
r_char
op_star
id|scsi
suffix:semicolon
id|period
op_assign
id|f10
op_assign
id|mb10
op_assign
l_int|0
suffix:semicolon
id|scsi
op_assign
l_string|&quot;FAST-5&quot;
suffix:semicolon
r_if
c_cond
(paren
id|__tcurr.period
op_le
l_int|9
)paren
(brace
id|scsi
op_assign
l_string|&quot;FAST-80&quot;
suffix:semicolon
id|period
op_assign
l_int|125
suffix:semicolon
id|mb10
op_assign
l_int|1600
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|__tcurr.period
op_le
l_int|11
)paren
(brace
id|scsi
op_assign
l_string|&quot;FAST-40&quot;
suffix:semicolon
id|period
op_assign
l_int|250
suffix:semicolon
r_if
c_cond
(paren
id|__tcurr.period
op_eq
l_int|11
)paren
id|period
op_assign
l_int|303
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|__tcurr.period
OL
l_int|25
)paren
(brace
id|scsi
op_assign
l_string|&quot;FAST-20&quot;
suffix:semicolon
r_if
c_cond
(paren
id|__tcurr.period
op_eq
l_int|12
)paren
id|period
op_assign
l_int|500
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|__tcurr.period
op_le
l_int|50
)paren
(brace
id|scsi
op_assign
l_string|&quot;FAST-10&quot;
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|period
)paren
id|period
op_assign
l_int|40
op_star
id|__tcurr.period
suffix:semicolon
id|f10
op_assign
l_int|100000
op_lshift
(paren
id|__tcurr.width
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|mb10
op_assign
(paren
id|f10
op_plus
id|period
op_div
l_int|2
)paren
op_div
id|period
suffix:semicolon
)brace
id|printf_info
(paren
l_string|&quot;%s:%d: %s %sSCSI %d.%d MB/s %s (%d.%d ns, offset %d)&bslash;n&quot;
comma
id|sym_name
c_func
(paren
id|np
)paren
comma
id|target
comma
id|scsi
comma
id|__tcurr.width
ques
c_cond
l_string|&quot;WIDE &quot;
suffix:colon
l_string|&quot;&quot;
comma
id|mb10
op_div
l_int|10
comma
id|mb10
op_mod
l_int|10
comma
(paren
id|__tcurr.options
op_amp
id|PPR_OPT_DT
)paren
ques
c_cond
l_string|&quot;DT&quot;
suffix:colon
l_string|&quot;ST&quot;
comma
id|period
op_div
l_int|10
comma
id|period
op_mod
l_int|10
comma
id|__tcurr.offset
)paren
suffix:semicolon
)brace
r_else
id|printf_info
(paren
l_string|&quot;%s:%d: %sasynchronous.&bslash;n&quot;
comma
id|sym_name
c_func
(paren
id|np
)paren
comma
id|target
comma
id|__tcurr.width
ques
c_cond
l_string|&quot;wide &quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
DECL|macro|__tprev
macro_line|#undef __tprev
DECL|macro|__tcurr
macro_line|#undef __tcurr
macro_line|#endif&t;/* SYM_OPT_ANNOUNCE_TRANSFER_RATE */
macro_line|#ifdef&t;SYM_OPT_SNIFF_INQUIRY
multiline_comment|/*&n; *  Update transfer settings according to user settings &n; *  and bits sniffed out from INQUIRY response.&n; */
DECL|function|sym_update_trans_settings
r_void
id|sym_update_trans_settings
c_func
(paren
id|hcb_p
id|np
comma
id|tcb_p
id|tp
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|tp-&gt;tinfo.goal
comma
op_amp
id|tp-&gt;tinfo.user
comma
r_sizeof
(paren
id|tp-&gt;tinfo.goal
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tp-&gt;inq_version
op_ge
l_int|4
)paren
(brace
r_switch
c_cond
(paren
id|tp-&gt;inq_byte56
op_amp
id|INQ56_CLOCKING
)paren
(brace
r_case
id|INQ56_ST_ONLY
suffix:colon
id|tp-&gt;tinfo.goal.options
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INQ56_DT_ONLY
suffix:colon
r_case
id|INQ56_ST_DT
suffix:colon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|tp-&gt;inq_byte7
op_amp
id|tp-&gt;inq_byte7_valid
)paren
op_amp
id|INQ7_WIDE16
)paren
)paren
(brace
id|tp-&gt;tinfo.goal.width
op_assign
l_int|0
suffix:semicolon
id|tp-&gt;tinfo.goal.options
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|tp-&gt;inq_byte7
op_amp
id|tp-&gt;inq_byte7_valid
)paren
op_amp
id|INQ7_SYNC
)paren
)paren
(brace
id|tp-&gt;tinfo.goal.offset
op_assign
l_int|0
suffix:semicolon
id|tp-&gt;tinfo.goal.options
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tp-&gt;tinfo.goal.options
op_amp
id|PPR_OPT_DT
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;tinfo.goal.offset
OG
id|np-&gt;maxoffs_dt
)paren
id|tp-&gt;tinfo.goal.offset
op_assign
id|np-&gt;maxoffs_dt
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|tp-&gt;tinfo.goal.offset
OG
id|np-&gt;maxoffs
)paren
id|tp-&gt;tinfo.goal.offset
op_assign
id|np-&gt;maxoffs
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  Snoop target capabilities from INQUIRY response.&n; *  We only believe device versions &gt;= SCSI-2 that use &n; *  appropriate response data format (2). But it seems &n; *  that some CCS devices also support SYNC (?).&n; */
r_int
DECL|function|__sym_sniff_inquiry
id|__sym_sniff_inquiry
c_func
(paren
id|hcb_p
id|np
comma
id|u_char
id|tn
comma
id|u_char
id|ln
comma
id|u_char
op_star
id|inq_data
comma
r_int
id|inq_len
)paren
(brace
id|tcb_p
id|tp
op_assign
op_amp
id|np-&gt;target
(braket
id|tn
)braket
suffix:semicolon
id|u_char
id|inq_version
suffix:semicolon
id|u_char
id|inq_byte7
suffix:semicolon
id|u_char
id|inq_byte56
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inq_data
op_logical_or
id|inq_len
OL
l_int|2
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; *  Check device type and qualifier.&n;&t; */
r_if
c_cond
(paren
(paren
id|inq_data
(braket
l_int|0
)braket
op_amp
l_int|0xe0
)paren
op_eq
l_int|0x60
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; *  Get SPC version.&n;&t; */
r_if
c_cond
(paren
id|inq_len
op_le
l_int|2
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|inq_version
op_assign
id|inq_data
(braket
l_int|2
)braket
op_amp
l_int|0x7
suffix:semicolon
multiline_comment|/*&n;&t; *  Get SYNC/WIDE16 capabilities.&n;&t; */
id|inq_byte7
op_assign
id|tp-&gt;inq_byte7
suffix:semicolon
r_if
c_cond
(paren
id|inq_version
op_ge
l_int|2
op_logical_and
(paren
id|inq_data
(braket
l_int|3
)braket
op_amp
l_int|0xf
)paren
op_eq
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|inq_len
OG
l_int|7
)paren
id|inq_byte7
op_assign
id|inq_data
(braket
l_int|7
)braket
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|inq_version
op_eq
l_int|1
op_logical_and
(paren
id|inq_data
(braket
l_int|3
)braket
op_amp
l_int|0xf
)paren
op_eq
l_int|1
)paren
id|inq_byte7
op_assign
id|INQ7_SYNC
suffix:semicolon
multiline_comment|/*&n;&t; *  Get Tagged Command Queuing capability.&n;&t; */
r_if
c_cond
(paren
id|inq_byte7
op_amp
id|INQ7_CMDQ
)paren
id|sym_set_bit
c_func
(paren
id|tp-&gt;cmdq_map
comma
id|ln
)paren
suffix:semicolon
r_else
id|sym_clr_bit
c_func
(paren
id|tp-&gt;cmdq_map
comma
id|ln
)paren
suffix:semicolon
id|inq_byte7
op_and_assign
op_complement
id|INQ7_CMDQ
suffix:semicolon
multiline_comment|/*&n;&t; *  Get CLOCKING capability.&n;&t; */
id|inq_byte56
op_assign
id|tp-&gt;inq_byte56
suffix:semicolon
r_if
c_cond
(paren
id|inq_version
op_ge
l_int|4
op_logical_and
id|inq_len
OG
l_int|56
)paren
id|inq_byte56
op_assign
id|inq_data
(braket
l_int|56
)braket
suffix:semicolon
macro_line|#if 0
id|printf
c_func
(paren
l_string|&quot;XXXXXX [%d] inq_version=%x inq_byte7=%x inq_byte56=%x XXXXX&bslash;n&quot;
comma
id|inq_len
comma
id|inq_version
comma
id|inq_byte7
comma
id|inq_byte56
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *  Trigger a negotiation if needed.&n;&t; */
r_if
c_cond
(paren
id|tp-&gt;inq_version
op_ne
id|inq_version
op_logical_or
id|tp-&gt;inq_byte7
op_ne
id|inq_byte7
op_logical_or
id|tp-&gt;inq_byte56
op_ne
id|inq_byte56
)paren
(brace
id|tp-&gt;inq_version
op_assign
id|inq_version
suffix:semicolon
id|tp-&gt;inq_byte7
op_assign
id|inq_byte7
suffix:semicolon
id|tp-&gt;inq_byte56
op_assign
id|inq_byte56
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif&t;/* SYM_OPT_SNIFF_INQUIRY */
eof
