multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2000-2004 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &quot;ioerror.h&quot;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &quot;shubio.h&quot;
macro_line|#include &lt;asm/sn/geo.h&gt;
macro_line|#include &quot;xtalk/xwidgetdev.h&quot;
macro_line|#include &quot;xtalk/hubdev.h&quot;
macro_line|#include &lt;asm/sn/bte.h&gt;
multiline_comment|/*&n; * Bte error handling is done in two parts.  The first captures&n; * any crb related errors.  Since there can be multiple crbs per&n; * interface and multiple interfaces active, we need to wait until&n; * all active crbs are completed.  This is the first job of the&n; * second part error handler.  When all bte related CRBs are cleanly&n; * completed, it resets the interfaces and gets them ready for new&n; * transfers to be queued.&n; */
r_void
id|bte_error_handler
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Wait until all BTE related CRBs are completed&n; * and then reset the interfaces.&n; */
DECL|function|bte_error_handler
r_void
id|bte_error_handler
c_func
(paren
r_int
r_int
id|_nodepda
)paren
(brace
r_struct
id|nodepda_s
op_star
id|err_nodepda
op_assign
(paren
r_struct
id|nodepda_s
op_star
)paren
id|_nodepda
suffix:semicolon
id|spinlock_t
op_star
id|recovery_lock
op_assign
op_amp
id|err_nodepda-&gt;bte_recovery_lock
suffix:semicolon
r_struct
id|timer_list
op_star
id|recovery_timer
op_assign
op_amp
id|err_nodepda-&gt;bte_recovery_timer
suffix:semicolon
id|nasid_t
id|nasid
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|valid_crbs
suffix:semicolon
r_int
r_int
id|irq_flags
suffix:semicolon
r_volatile
id|u64
op_star
id|notify
suffix:semicolon
id|bte_result_t
id|bh_error
suffix:semicolon
id|ii_imem_u_t
id|imem
suffix:semicolon
multiline_comment|/* II IMEM Register */
id|ii_icrb0_d_u_t
id|icrbd
suffix:semicolon
multiline_comment|/* II CRB Register D */
id|ii_ibcr_u_t
id|ibcr
suffix:semicolon
id|ii_icmr_u_t
id|icmr
suffix:semicolon
id|ii_ieclr_u_t
id|ieclr
suffix:semicolon
id|BTE_PRINTK
c_func
(paren
(paren
l_string|&quot;bte_error_handler(%p) - %d&bslash;n&quot;
comma
id|err_nodepda
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|recovery_lock
comma
id|irq_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err_nodepda-&gt;bte_if
(braket
l_int|0
)braket
dot
id|bh_error
op_eq
id|BTE_SUCCESS
)paren
op_logical_and
(paren
id|err_nodepda-&gt;bte_if
(braket
l_int|1
)braket
dot
id|bh_error
op_eq
id|BTE_SUCCESS
)paren
)paren
(brace
id|BTE_PRINTK
c_func
(paren
(paren
l_string|&quot;eh:%p:%d Nothing to do.&bslash;n&quot;
comma
id|err_nodepda
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|recovery_lock
comma
id|irq_flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Lock all interfaces on this node to prevent new transfers&n;&t; * from being queued.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|BTES_PER_NODE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|err_nodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|cleanup_active
)paren
(brace
r_continue
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|err_nodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|spinlock
)paren
suffix:semicolon
id|BTE_PRINTK
c_func
(paren
(paren
l_string|&quot;eh:%p:%d locked %d&bslash;n&quot;
comma
id|err_nodepda
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|i
)paren
)paren
suffix:semicolon
id|err_nodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|cleanup_active
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Determine information about our hub */
id|nasid
op_assign
id|cnodeid_to_nasid
c_func
(paren
id|err_nodepda-&gt;bte_if
(braket
l_int|0
)braket
dot
id|bte_cnode
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * A BTE transfer can use multiple CRBs.  We need to make sure&n;&t; * that all the BTE CRBs are complete (or timed out) before&n;&t; * attempting to clean up the error.  Resetting the BTE while&n;&t; * there are still BTE CRBs active will hang the BTE.&n;&t; * We should look at all the CRBs to see if they are allocated&n;&t; * to the BTE and see if they are still active.  When none&n;&t; * are active, we can continue with the cleanup.&n;&t; *&n;&t; * We also want to make sure that the local NI port is up.&n;&t; * When a router resets the NI port can go down, while it&n;&t; * goes through the LLP handshake, but then comes back up.&n;&t; */
id|icmr.ii_icmr_regval
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|nasid
comma
id|IIO_ICMR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|icmr.ii_icmr_fld_s.i_crb_mark
op_ne
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * There are errors which still need to be cleaned up by&n;&t;&t; * hubiio_crb_error_handler&n;&t;&t; */
id|mod_timer
c_func
(paren
id|recovery_timer
comma
id|HZ
op_star
l_int|5
)paren
suffix:semicolon
id|BTE_PRINTK
c_func
(paren
(paren
l_string|&quot;eh:%p:%d Marked Giving up&bslash;n&quot;
comma
id|err_nodepda
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|recovery_lock
comma
id|irq_flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|icmr.ii_icmr_fld_s.i_crb_vld
op_ne
l_int|0
)paren
(brace
id|valid_crbs
op_assign
id|icmr.ii_icmr_fld_s.i_crb_vld
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
id|IIO_NUM_CRBS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
l_int|1
op_lshift
id|i
)paren
op_amp
id|valid_crbs
)paren
)paren
(brace
multiline_comment|/* This crb was not marked as valid, ignore */
r_continue
suffix:semicolon
)brace
id|icrbd.ii_icrb0_d_regval
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|nasid
comma
id|IIO_ICRB_D
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|icrbd.d_bteop
)paren
(brace
id|mod_timer
c_func
(paren
id|recovery_timer
comma
id|HZ
op_star
l_int|5
)paren
suffix:semicolon
id|BTE_PRINTK
c_func
(paren
(paren
l_string|&quot;eh:%p:%d Valid %d, Giving up&bslash;n&quot;
comma
id|err_nodepda
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|i
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|recovery_lock
comma
id|irq_flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
id|BTE_PRINTK
c_func
(paren
(paren
l_string|&quot;eh:%p:%d Cleaning up&bslash;n&quot;
comma
id|err_nodepda
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Reenable both bte interfaces */
id|imem.ii_imem_regval
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|nasid
comma
id|IIO_IMEM
)paren
suffix:semicolon
id|imem.ii_imem_fld_s.i_b0_esd
op_assign
id|imem.ii_imem_fld_s.i_b1_esd
op_assign
l_int|1
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_IMEM
comma
id|imem.ii_imem_regval
)paren
suffix:semicolon
multiline_comment|/* Clear BTE0/1 error bits */
id|ieclr.ii_ieclr_regval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|err_nodepda-&gt;bte_if
(braket
l_int|0
)braket
dot
id|bh_error
op_ne
id|BTE_SUCCESS
)paren
id|ieclr.ii_ieclr_fld_s.i_e_bte_0
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|err_nodepda-&gt;bte_if
(braket
l_int|1
)braket
dot
id|bh_error
op_ne
id|BTE_SUCCESS
)paren
id|ieclr.ii_ieclr_fld_s.i_e_bte_1
op_assign
l_int|1
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_IECLR
comma
id|ieclr.ii_ieclr_regval
)paren
suffix:semicolon
multiline_comment|/* Reinitialize both BTE state machines. */
id|ibcr.ii_ibcr_regval
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|nasid
comma
id|IIO_IBCR
)paren
suffix:semicolon
id|ibcr.ii_ibcr_fld_s.i_soft_reset
op_assign
l_int|1
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_IBCR
comma
id|ibcr.ii_ibcr_regval
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
id|BTES_PER_NODE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bh_error
op_assign
id|err_nodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|bh_error
suffix:semicolon
r_if
c_cond
(paren
id|bh_error
op_ne
id|BTE_SUCCESS
)paren
(brace
multiline_comment|/* There is an error which needs to be notified */
id|notify
op_assign
id|err_nodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|most_rcnt_na
suffix:semicolon
id|BTE_PRINTK
c_func
(paren
(paren
l_string|&quot;cnode %d bte %d error=0x%lx&bslash;n&quot;
comma
id|err_nodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|bte_cnode
comma
id|err_nodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|bte_num
comma
id|IBLS_ERROR
op_or
(paren
id|u64
)paren
id|bh_error
)paren
)paren
suffix:semicolon
op_star
id|notify
op_assign
id|IBLS_ERROR
op_or
id|bh_error
suffix:semicolon
id|err_nodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|bh_error
op_assign
id|BTE_SUCCESS
suffix:semicolon
)brace
id|err_nodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|cleanup_active
op_assign
l_int|0
suffix:semicolon
id|BTE_PRINTK
c_func
(paren
(paren
l_string|&quot;eh:%p:%d Unlocked %d&bslash;n&quot;
comma
id|err_nodepda
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|i
)paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|err_nodepda-&gt;bte_if
(braket
id|i
)braket
dot
id|spinlock
)paren
suffix:semicolon
)brace
id|del_timer
c_func
(paren
id|recovery_timer
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|recovery_lock
comma
id|irq_flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * First part error handler.  This is called whenever any error CRB interrupt&n; * is generated by the II.&n; */
r_void
DECL|function|bte_crb_error_handler
id|bte_crb_error_handler
c_func
(paren
id|cnodeid_t
id|cnode
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
comma
r_int
id|bteop
)paren
(brace
r_struct
id|bteinfo_s
op_star
id|bte
suffix:semicolon
id|bte
op_assign
op_amp
(paren
id|NODEPDA
c_func
(paren
id|cnode
)paren
op_member_access_from_pointer
id|bte_if
(braket
id|btenum
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The caller has already figured out the error type, we save that&n;&t; * in the bte handle structure for the thread excercising the&n;&t; * interface to consume.&n;&t; */
id|bte-&gt;bh_error
op_assign
id|ioe-&gt;ie_errortype
op_plus
id|BTEFAIL_OFFSET
suffix:semicolon
id|bte-&gt;bte_error_count
op_increment
suffix:semicolon
id|BTE_PRINTK
c_func
(paren
(paren
l_string|&quot;Got an error on cnode %d bte %d: HW error type 0x%x&bslash;n&quot;
comma
id|bte-&gt;bte_cnode
comma
id|bte-&gt;bte_num
comma
id|ioe-&gt;ie_errortype
)paren
)paren
suffix:semicolon
id|bte_error_handler
c_func
(paren
(paren
r_int
r_int
)paren
id|NODEPDA
c_func
(paren
id|cnode
)paren
)paren
suffix:semicolon
)brace
eof
