multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000,2002 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/labelcl.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xtalk.h&gt;
macro_line|#include &lt;asm/sn/pci/pcibr_private.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/ioerror.h&gt;
macro_line|#include &lt;asm/sn/sn2/shubio.h&gt;
macro_line|#include &lt;asm/sn/bte.h&gt;
multiline_comment|/************************************************************************&n; *&t;&t;&t;&t;&t;&t;&t;&t;&t;*&n; * &t;&t;&t; BTE ERROR RECOVERY&t;&t;&t;&t;*&n; *&t;&t;&t;&t;&t;&t;&t;&t;&t;*&n; * Given a BTE error, the node causing the error must do the following: *&n; *    a) Clear all crbs relating to that BTE&t;&t;&t;&t;*&n; *&t;&t;1) Read CRBA value for crb in question&t;&t;&t;*&n; *&t;&t;2) Mark CRB as VALID, store local physical &t;&t;*&n; *&t;&t;   address known to be good in the address field&t;*&n; *&t;&t;   (bte_notification_targ is a known good local&t;&t;*&n; *&t;&t;    address).&t;&t;&t;&t;&t;&t;*&n; *&t;&t;3) Write CRBA&t;&t;&t;&t;&t;&t;*&n; *&t;&t;4) Using ICCR, FLUSH the CRB, and wait for it to &t;*&n; *&t;&t;   complete.&t;&t;&t;&t;&t;&t;*&n; *&t;&t;... BTE BUSY bit should now be clear (or at least &t;*&n; *&t;&t;    should be after ALL CRBs associated with the &t;*&n; *&t;&t;    transfer are complete.&t;&t;&t;&t;*&n; *&t;&t;&t;&t;&t;&t;&t;&t;&t;*&n; *    b) Re-enable BTE&t;&t;&t;&t;&t;&t;&t;*&n; *&t;&t;1) Write IMEM with BTE Enable + XXX bits&n; *&t;&t;2) Write IECLR with BTE clear bits&n; *&t;&t;3) Clear IIDSR INT_SENT bits.&n; *&t;&t;&t;&t;&t;&t;&t;&t;&t;*&n; ************************************************************************/
macro_line|#ifdef BTE_ERROR
singleline_comment|// This routine is not called.  Yet.  It may be someday.  It probably
singleline_comment|// *should* be someday.  Until then, ifdef it out.
id|bte_result_t
DECL|function|bte_error_handler
id|bte_error_handler
c_func
(paren
id|bte_handle_t
op_star
id|bh
)paren
multiline_comment|/*&n; * Function: &t;bte_error_handler&n; * Purpose:&t;Process a BTE error after a transfer has failed.&n; * Parameters:&t;bh - bte handle of bte that failed.&n; * Returns:&t;The BTE error type.&n; * Notes:&n; */
(brace
id|devfs_handle_t
id|hub_v
suffix:semicolon
id|hubinfo_t
id|hinfo
suffix:semicolon
r_int
id|il
suffix:semicolon
id|hubreg_t
id|iidsr
comma
id|imem
comma
id|ieclr
suffix:semicolon
id|hubreg_t
id|bte_status
suffix:semicolon
id|bh-&gt;bh_bte-&gt;bte_error_count
op_increment
suffix:semicolon
multiline_comment|/* &n;     * Process any CRB logs - we know that the bte_context contains&n;     * the BTE completion status, but to avoid a race with error&n;     * processing, we force a call to pick up any CRB errors pending. &n;     * After this call, we know that we have any CRB errors related to &n;     * this BTE transfer in the context.&n;     */
id|hub_v
op_assign
id|cnodeid_to_vertex
c_func
(paren
id|bh-&gt;bh_bte-&gt;bte_cnode
)paren
suffix:semicolon
id|hubinfo_get
c_func
(paren
id|hub_v
comma
op_amp
id|hinfo
)paren
suffix:semicolon
(paren
r_void
)paren
id|hubiio_crb_error_handler
c_func
(paren
id|hub_v
comma
id|hinfo
)paren
suffix:semicolon
multiline_comment|/* Be sure BTE is stopped */
(paren
r_void
)paren
id|BTE_LOAD
c_func
(paren
id|bh-&gt;bh_bte-&gt;bte_base
comma
id|BTEOFF_CTRL
)paren
suffix:semicolon
multiline_comment|/*&t;&n;     * Now clear up the rest of the error - be sure to hold crblock &n;     * to avoid race with other cpu on this node.&n;     */
id|imem
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|hinfo-&gt;h_nasid
comma
id|IIO_IMEM
)paren
suffix:semicolon
id|ieclr
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|hinfo-&gt;h_nasid
comma
id|IIO_IECLR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;bh_bte-&gt;bte_num
op_eq
l_int|0
)paren
(brace
id|imem
op_or_assign
id|IIO_IMEM_W0ESD
op_or
id|IIO_IMEM_B0ESD
suffix:semicolon
id|ieclr
op_or_assign
id|IECLR_BTE0
suffix:semicolon
)brace
r_else
(brace
id|imem
op_or_assign
id|IIO_IMEM_W0ESD
op_or
id|IIO_IMEM_B1ESD
suffix:semicolon
id|ieclr
op_or_assign
id|IECLR_BTE1
suffix:semicolon
)brace
id|REMOTE_HUB_S
c_func
(paren
id|hinfo-&gt;h_nasid
comma
id|IIO_IMEM
comma
id|imem
)paren
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|hinfo-&gt;h_nasid
comma
id|IIO_IECLR
comma
id|ieclr
)paren
suffix:semicolon
id|iidsr
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|hinfo-&gt;h_nasid
comma
id|IIO_IIDSR
)paren
suffix:semicolon
id|iidsr
op_and_assign
op_complement
id|IIO_IIDSR_SENT_MASK
suffix:semicolon
id|iidsr
op_or_assign
id|IIO_IIDSR_ENB_MASK
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|hinfo-&gt;h_nasid
comma
id|IIO_IIDSR
comma
id|iidsr
)paren
suffix:semicolon
id|mutex_spinunlock
c_func
(paren
op_amp
id|hinfo-&gt;h_crblock
comma
id|il
)paren
suffix:semicolon
id|bte_status
op_assign
id|BTE_LOAD
c_func
(paren
id|bh-&gt;bh_bte-&gt;bte_base
comma
id|BTEOFF_STAT
)paren
suffix:semicolon
id|BTE_STORE
c_func
(paren
id|bh-&gt;bh_bte-&gt;bte_base
comma
id|BTEOFF_STAT
comma
id|bte_status
op_amp
op_complement
id|IBLS_BUSY
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
op_logical_neg
id|BTE_IS_BUSY
c_func
(paren
id|BTE_LOAD
c_func
(paren
id|bh-&gt;bh_bte-&gt;bte_base
comma
id|BTEOFF_STAT
)paren
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|bh-&gt;bh_error
)paren
(brace
r_case
id|IIO_ICRB_ECODE_PERR
suffix:colon
r_return
id|BTEFAIL_POISON
suffix:semicolon
r_case
id|IIO_ICRB_ECODE_WERR
suffix:colon
r_return
id|BTEFAIL_PROT
suffix:semicolon
r_case
id|IIO_ICRB_ECODE_AERR
suffix:colon
r_return
id|BTEFAIL_ACCESS
suffix:semicolon
r_case
id|IIO_ICRB_ECODE_TOUT
suffix:colon
r_return
id|BTEFAIL_TOUT
suffix:semicolon
r_case
id|IIO_ICRB_ECODE_XTERR
suffix:colon
r_return
id|BTEFAIL_ERROR
suffix:semicolon
r_case
id|IIO_ICRB_ECODE_DERR
suffix:colon
r_return
id|BTEFAIL_DIR
suffix:semicolon
r_case
id|IIO_ICRB_ECODE_PWERR
suffix:colon
r_case
id|IIO_ICRB_ECODE_PRERR
suffix:colon
multiline_comment|/* NO BREAK */
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;BTE failure (%d) unexpected&bslash;n&quot;
comma
id|bh-&gt;bh_error
)paren
suffix:semicolon
r_return
id|BTEFAIL_ERROR
suffix:semicolon
)brace
)brace
macro_line|#endif 
singleline_comment|// BTE_ERROR
r_void
DECL|function|bte_crb_error_handler
id|bte_crb_error_handler
c_func
(paren
id|devfs_handle_t
id|hub_v
comma
r_int
id|btenum
comma
r_int
id|crbnum
comma
id|ioerror_t
op_star
id|ioe
)paren
multiline_comment|/*&n; * Function: &t;bte_crb_error_handler&n; * Purpose:&t;Process a CRB for a specific HUB/BTE&n; * Parameters:&t;hub_v&t;- vertex of hub in HW graph&n; *&t;&t;btenum&t;- bte number on hub (0 == a, 1 == b)&n; *&t;&t;crbnum&t;- crb number being processed&n; * Notes: &n; *&t;This routine assumes serialization at a higher level. A CRB &n; *&t;should not be processed more than once. The error recovery &n; *&t;follows the following sequence - if you change this, be real&n; *&t;sure about what you are doing. &n; *&n; */
(brace
id|hubinfo_t
id|hinfo
suffix:semicolon
id|icrba_t
id|crba
suffix:semicolon
id|icrbb_t
id|crbb
suffix:semicolon
id|nasid_t
id|n
suffix:semicolon
id|hubinfo_get
c_func
(paren
id|hub_v
comma
op_amp
id|hinfo
)paren
suffix:semicolon
id|n
op_assign
id|hinfo-&gt;h_nasid
suffix:semicolon
multiline_comment|/* Step 1 */
id|crba.ii_icrb0_a_regval
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|n
comma
id|IIO_ICRB_A
c_func
(paren
id|crbnum
)paren
)paren
suffix:semicolon
id|crbb.ii_icrb0_b_regval
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|n
comma
id|IIO_ICRB_B
c_func
(paren
id|crbnum
)paren
)paren
suffix:semicolon
multiline_comment|/* Zero error and error code to prevent error_dump complaining&n;&t; * about these CRBs. &n;&t; */
id|crbb.b_error
op_assign
l_int|0
suffix:semicolon
id|crbb.b_ecode
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Step 2 */
id|REMOTE_HUB_S
c_func
(paren
id|n
comma
id|IIO_ICRB_A
c_func
(paren
id|crbnum
)paren
comma
id|crba.ii_icrb0_a_regval
)paren
suffix:semicolon
multiline_comment|/* Step 3 */
id|REMOTE_HUB_S
c_func
(paren
id|n
comma
id|IIO_ICCR
comma
id|IIO_ICCR_PENDING
op_or
id|IIO_ICCR_CMD_FLUSH
op_or
id|crbnum
)paren
suffix:semicolon
r_while
c_loop
(paren
id|REMOTE_HUB_L
c_func
(paren
id|n
comma
id|IIO_ICCR
)paren
op_amp
id|IIO_ICCR_PENDING
)paren
suffix:semicolon
)brace
eof