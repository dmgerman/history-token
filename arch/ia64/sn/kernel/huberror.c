multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000,2002-2004 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/sn/sn_sal.h&gt;
macro_line|#include &quot;ioerror.h&quot;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &quot;shubio.h&quot;
macro_line|#include &lt;asm/sn/geo.h&gt;
macro_line|#include &quot;xtalk/xwidgetdev.h&quot;
macro_line|#include &quot;xtalk/hubdev.h&quot;
macro_line|#include &lt;asm/sn/bte.h&gt;
r_void
id|hubiio_crb_error_handler
c_func
(paren
r_struct
id|hubdev_info
op_star
id|hubdev_info
)paren
suffix:semicolon
r_extern
r_void
id|bte_crb_error_handler
c_func
(paren
id|cnodeid_t
comma
r_int
comma
r_int
comma
id|ioerror_t
op_star
comma
r_int
)paren
suffix:semicolon
DECL|function|hub_eint_handler
r_static
id|irqreturn_t
id|hub_eint_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|arg
comma
r_struct
id|pt_regs
op_star
id|ep
)paren
(brace
r_struct
id|hubdev_info
op_star
id|hubdev_info
suffix:semicolon
r_struct
id|ia64_sal_retval
id|ret_stuff
suffix:semicolon
id|nasid_t
id|nasid
suffix:semicolon
id|ret_stuff.status
op_assign
l_int|0
suffix:semicolon
id|ret_stuff.v0
op_assign
l_int|0
suffix:semicolon
id|hubdev_info
op_assign
(paren
r_struct
id|hubdev_info
op_star
)paren
id|arg
suffix:semicolon
id|nasid
op_assign
id|hubdev_info-&gt;hdi_nasid
suffix:semicolon
id|SAL_CALL_NOLOCK
c_func
(paren
id|ret_stuff
comma
id|SN_SAL_HUB_ERROR_INTERRUPT
comma
(paren
id|u64
)paren
id|nasid
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|ret_stuff.v0
)paren
id|panic
c_func
(paren
l_string|&quot;hubii_eint_handler(): Fatal TIO Error&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|nasid
op_amp
l_int|1
)paren
)paren
multiline_comment|/* Not a TIO, handle CRB errors */
(paren
r_void
)paren
id|hubiio_crb_error_handler
c_func
(paren
id|hubdev_info
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * Free the hub CRB &quot;crbnum&quot; which encountered an error.&n; * Assumption is, error handling was successfully done,&n; * and we now want to return the CRB back to Hub for normal usage.&n; *&n; * In order to free the CRB, all that&squot;s needed is to de-allocate it&n; *&n; * Assumption:&n; *      No other processor is mucking around with the hub control register.&n; *      So, upper layer has to single thread this.&n; */
DECL|function|hubiio_crb_free
r_void
id|hubiio_crb_free
c_func
(paren
r_struct
id|hubdev_info
op_star
id|hubdev_info
comma
r_int
id|crbnum
)paren
(brace
id|ii_icrb0_b_u_t
id|icrbb
suffix:semicolon
multiline_comment|/*&n;&t; * The hardware does NOT clear the mark bit, so it must get cleared&n;&t; * here to be sure the error is not processed twice.&n;&t; */
id|icrbb.ii_icrb0_b_regval
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|hubdev_info-&gt;hdi_nasid
comma
id|IIO_ICRB_B
c_func
(paren
id|crbnum
)paren
)paren
suffix:semicolon
id|icrbb.b_mark
op_assign
l_int|0
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|hubdev_info-&gt;hdi_nasid
comma
id|IIO_ICRB_B
c_func
(paren
id|crbnum
)paren
comma
id|icrbb.ii_icrb0_b_regval
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Deallocate the register wait till hub indicates it&squot;s done.&n;&t; */
id|REMOTE_HUB_S
c_func
(paren
id|hubdev_info-&gt;hdi_nasid
comma
id|IIO_ICDR
comma
(paren
id|IIO_ICDR_PND
op_or
id|crbnum
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|REMOTE_HUB_L
c_func
(paren
id|hubdev_info-&gt;hdi_nasid
comma
id|IIO_ICDR
)paren
op_amp
id|IIO_ICDR_PND
)paren
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hubiio_crb_error_handler&n; *&n; *&t;This routine gets invoked when a hub gets an error &n; *&t;interrupt. So, the routine is running in interrupt context&n; *&t;at error interrupt level.&n; * Action:&n; *&t;It&squot;s responsible for identifying ALL the CRBs that are marked&n; *&t;with error, and process them. &n; *&t;&n; * &t;If you find the CRB that&squot;s marked with error, map this to the&n; *&t;reason it caused error, and invoke appropriate error handler.&n; *&n; *&t;XXX Be aware of the information in the context register.&n; *&n; * NOTE:&n; *&t;Use REMOTE_HUB_* macro instead of LOCAL_HUB_* so that the interrupt&n; *&t;handler can be run on any node. (not necessarily the node &n; *&t;corresponding to the hub that encountered error).&n; */
DECL|function|hubiio_crb_error_handler
r_void
id|hubiio_crb_error_handler
c_func
(paren
r_struct
id|hubdev_info
op_star
id|hubdev_info
)paren
(brace
id|nasid_t
id|nasid
suffix:semicolon
id|ii_icrb0_a_u_t
id|icrba
suffix:semicolon
multiline_comment|/* II CRB Register A */
id|ii_icrb0_b_u_t
id|icrbb
suffix:semicolon
multiline_comment|/* II CRB Register B */
id|ii_icrb0_c_u_t
id|icrbc
suffix:semicolon
multiline_comment|/* II CRB Register C */
id|ii_icrb0_d_u_t
id|icrbd
suffix:semicolon
multiline_comment|/* II CRB Register D */
id|ii_icrb0_e_u_t
id|icrbe
suffix:semicolon
multiline_comment|/* II CRB Register D */
r_int
id|i
suffix:semicolon
r_int
id|num_errors
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Num of errors handled */
id|ioerror_t
id|ioerror
suffix:semicolon
id|nasid
op_assign
id|hubdev_info-&gt;hdi_nasid
suffix:semicolon
multiline_comment|/*&n;&t; * XXX - Add locking for any recovery actions&n;&t; */
multiline_comment|/*&n;&t; * Scan through all CRBs in the Hub, and handle the errors&n;&t; * in any of the CRBs marked.&n;&t; */
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
multiline_comment|/* Check this crb entry to see if it is in error. */
id|icrbb.ii_icrb0_b_regval
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|nasid
comma
id|IIO_ICRB_B
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|icrbb.b_mark
op_eq
l_int|0
)paren
(brace
r_continue
suffix:semicolon
)brace
id|icrba.ii_icrb0_a_regval
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|nasid
comma
id|IIO_ICRB_A
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
id|IOERROR_INIT
c_func
(paren
op_amp
id|ioerror
)paren
suffix:semicolon
multiline_comment|/* read other CRB error registers. */
id|icrbc.ii_icrb0_c_regval
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|nasid
comma
id|IIO_ICRB_C
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
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
id|icrbe.ii_icrb0_e_regval
op_assign
id|REMOTE_HUB_L
c_func
(paren
id|nasid
comma
id|IIO_ICRB_E
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
id|IOERROR_SETVALUE
c_func
(paren
op_amp
id|ioerror
comma
id|errortype
comma
id|icrbb.b_ecode
)paren
suffix:semicolon
multiline_comment|/* Check if this error is due to BTE operation,&n;&t;&t; * and handle it separately.&n;&t;&t; */
r_if
c_cond
(paren
id|icrbd.d_bteop
op_logical_or
(paren
(paren
id|icrbb.b_initiator
op_eq
id|IIO_ICRB_INIT_BTE0
op_logical_or
id|icrbb.b_initiator
op_eq
id|IIO_ICRB_INIT_BTE1
)paren
op_logical_and
(paren
id|icrbb.b_imsgtype
op_eq
id|IIO_ICRB_IMSGT_BTE
op_logical_or
id|icrbb.b_imsgtype
op_eq
id|IIO_ICRB_IMSGT_SN1NET
)paren
)paren
)paren
(brace
r_int
id|bte_num
suffix:semicolon
r_if
c_cond
(paren
id|icrbd.d_bteop
)paren
id|bte_num
op_assign
id|icrbc.c_btenum
suffix:semicolon
r_else
multiline_comment|/* b_initiator bit 2 gives BTE number */
id|bte_num
op_assign
(paren
id|icrbb.b_initiator
op_amp
l_int|0x4
)paren
op_rshift
l_int|2
suffix:semicolon
id|hubiio_crb_free
c_func
(paren
id|hubdev_info
comma
id|i
)paren
suffix:semicolon
id|bte_crb_error_handler
c_func
(paren
id|nasid_to_cnodeid
c_func
(paren
id|nasid
)paren
comma
id|bte_num
comma
id|i
comma
op_amp
id|ioerror
comma
id|icrbd.d_bteop
)paren
suffix:semicolon
id|num_errors
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Function&t;: hub_error_init&n; * Purpose&t;: initialize the error handling requirements for a given hub.&n; * Parameters&t;: cnode, the compact nodeid.&n; * Assumptions&t;: Called only once per hub, either by a local cpu. Or by a&n; *&t;&t;&t;remote cpu, when this hub is headless.(cpuless)&n; * Returns&t;: None&n; */
DECL|function|hub_error_init
r_void
id|hub_error_init
c_func
(paren
r_struct
id|hubdev_info
op_star
id|hubdev_info
)paren
(brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|SGI_II_ERROR
comma
(paren
r_void
op_star
)paren
id|hub_eint_handler
comma
id|SA_SHIRQ
comma
l_string|&quot;SN_hub_error&quot;
comma
(paren
r_void
op_star
)paren
id|hubdev_info
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;hub_error_init: Failed to request_irq for 0x%p&bslash;n&quot;
comma
id|hubdev_info
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Function&t;: ice_error_init&n; * Purpose&t;: initialize the error handling requirements for a given tio.&n; * Parameters&t;: cnode, the compact nodeid.&n; * Assumptions&t;: Called only once per tio.&n; * Returns&t;: None&n; */
DECL|function|ice_error_init
r_void
id|ice_error_init
c_func
(paren
r_struct
id|hubdev_info
op_star
id|hubdev_info
)paren
(brace
r_if
c_cond
(paren
id|request_irq
(paren
id|SGI_TIO_ERROR
comma
(paren
r_void
op_star
)paren
id|hub_eint_handler
comma
id|SA_SHIRQ
comma
l_string|&quot;SN_TIO_error&quot;
comma
(paren
r_void
op_star
)paren
id|hubdev_info
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;ice_error_init: request_irq() error hubdev_info 0x%p&bslash;n&quot;
comma
id|hubdev_info
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
