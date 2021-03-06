multiline_comment|/*&n; * Access to HP-HIL MLC through HP System Device Controller.&n; *&n; * Copyright (c) 2001 Brian S. Julin&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. The name of the author may not be used to endorse or promote products&n; *    derived from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;).&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND&n; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n; * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n; * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; *&n; * References:&n; * HP-HIL Technical Reference Manual.  Hewlett Packard Product No. 45918A&n; * System Device Controller Microprocessor Firmware Theory of Operation&n; *      for Part Number 1820-4784 Revision B.  Dwg No. A-1820-4784-2&n; *&n; */
macro_line|#include &lt;linux/hil_mlc.h&gt;
macro_line|#include &lt;linux/hp_sdc.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
DECL|macro|PREFIX
mdefine_line|#define PREFIX &quot;HP SDC MLC: &quot;
DECL|variable|hp_sdc_mlc
r_static
id|hil_mlc
id|hp_sdc_mlc
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Brian S. Julin &lt;bri@calyx.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Glue for onboard HIL MLC in HP-PARISC machines&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual BSD/GPL&quot;
)paren
suffix:semicolon
DECL|struct|hp_sdc_mlc_priv_s
r_struct
id|hp_sdc_mlc_priv_s
(brace
DECL|member|emtestmode
r_int
id|emtestmode
suffix:semicolon
DECL|member|trans
id|hp_sdc_transaction
id|trans
suffix:semicolon
DECL|member|tseq
id|u8
id|tseq
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|got5x
r_int
id|got5x
suffix:semicolon
DECL|variable|hp_sdc_mlc_priv
)brace
id|hp_sdc_mlc_priv
suffix:semicolon
multiline_comment|/************************* Interrupt context ******************************/
DECL|function|hp_sdc_mlc_isr
r_static
r_void
id|hp_sdc_mlc_isr
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_uint8
id|status
comma
r_uint8
id|data
)paren
(brace
r_int
id|idx
suffix:semicolon
id|hil_mlc
op_star
id|mlc
op_assign
op_amp
id|hp_sdc_mlc
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
(paren
id|mlc-&gt;lock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mlc-&gt;icount
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;HIL Overflow!&bslash;n&quot;
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|mlc-&gt;isem
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|idx
op_assign
l_int|15
op_minus
id|mlc-&gt;icount
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|HP_SDC_STATUS_IRQMASK
)paren
op_eq
id|HP_SDC_STATUS_HILDATA
)paren
(brace
id|mlc-&gt;ipacket
(braket
id|idx
)braket
op_or_assign
id|data
op_or
id|HIL_ERR_INT
suffix:semicolon
id|mlc-&gt;icount
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|hp_sdc_mlc_priv.got5x
)paren
r_goto
id|check
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|idx
)paren
r_goto
id|check
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mlc-&gt;ipacket
(braket
id|idx
op_minus
l_int|1
)braket
op_amp
id|HIL_PKT_ADDR_MASK
)paren
op_ne
(paren
id|mlc-&gt;ipacket
(braket
id|idx
)braket
op_amp
id|HIL_PKT_ADDR_MASK
)paren
)paren
(brace
id|mlc-&gt;ipacket
(braket
id|idx
)braket
op_and_assign
op_complement
id|HIL_PKT_ADDR_MASK
suffix:semicolon
id|mlc-&gt;ipacket
(braket
id|idx
)braket
op_or_assign
(paren
id|mlc-&gt;ipacket
(braket
id|idx
op_minus
l_int|1
)braket
op_amp
id|HIL_PKT_ADDR_MASK
)paren
suffix:semicolon
)brace
r_goto
id|check
suffix:semicolon
)brace
multiline_comment|/* We know status is 5X */
r_if
c_cond
(paren
id|data
op_amp
id|HP_SDC_HIL_ISERR
)paren
r_goto
id|err
suffix:semicolon
id|mlc-&gt;ipacket
(braket
id|idx
)braket
op_assign
(paren
id|data
op_amp
id|HP_SDC_HIL_R1MASK
)paren
op_lshift
id|HIL_PKT_ADDR_SHIFT
suffix:semicolon
id|hp_sdc_mlc_priv.got5x
op_assign
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|check
suffix:colon
id|hp_sdc_mlc_priv.got5x
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mlc-&gt;imatch
op_eq
l_int|0
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mlc-&gt;imatch
op_eq
(paren
id|HIL_ERR_INT
op_or
id|HIL_PKT_CMD
op_or
id|HIL_CMD_POL
)paren
)paren
op_logical_and
(paren
id|mlc-&gt;ipacket
(braket
id|idx
)braket
op_eq
(paren
id|mlc-&gt;imatch
op_or
id|idx
)paren
)paren
)paren
r_goto
id|done
suffix:semicolon
r_if
c_cond
(paren
id|mlc-&gt;ipacket
(braket
id|idx
)braket
op_eq
id|mlc-&gt;imatch
)paren
r_goto
id|done
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|err
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
id|PREFIX
l_string|&quot;err code %x&bslash;n&quot;
comma
id|data
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|data
)paren
(brace
r_case
id|HP_SDC_HIL_RC_DONE
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Bastard SDC reconfigured loop!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HP_SDC_HIL_ERR
suffix:colon
id|mlc-&gt;ipacket
(braket
id|idx
)braket
op_or_assign
id|HIL_ERR_INT
op_or
id|HIL_ERR_PERR
op_or
id|HIL_ERR_FERR
op_or
id|HIL_ERR_FOF
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HP_SDC_HIL_TO
suffix:colon
id|mlc-&gt;ipacket
(braket
id|idx
)braket
op_or_assign
id|HIL_ERR_INT
op_or
id|HIL_ERR_LERR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HP_SDC_HIL_RC
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Bastard SDC decided to reconfigure loop!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Unkown HIL Error status (%x)!&bslash;n&quot;
comma
id|data
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* No more data will be coming due to an error. */
id|done
suffix:colon
id|tasklet_schedule
c_func
(paren
id|mlc-&gt;tasklet
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
(paren
id|mlc-&gt;isem
)paren
)paren
suffix:semicolon
id|out
suffix:colon
id|write_unlock
c_func
(paren
op_amp
(paren
id|mlc-&gt;lock
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/******************** Tasklet or userspace context functions ****************/
DECL|function|hp_sdc_mlc_in
r_static
r_int
id|hp_sdc_mlc_in
(paren
id|hil_mlc
op_star
id|mlc
comma
id|suseconds_t
id|timeout
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|hp_sdc_mlc_priv_s
op_star
id|priv
suffix:semicolon
r_int
id|rc
op_assign
l_int|2
suffix:semicolon
id|priv
op_assign
id|mlc-&gt;priv
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
(paren
id|mlc-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Try to down the semaphore */
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
(paren
id|mlc-&gt;isem
)paren
)paren
)paren
(brace
r_struct
id|timeval
id|tv
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;emtestmode
)paren
(brace
id|mlc-&gt;ipacket
(braket
l_int|0
)braket
op_assign
id|HIL_ERR_INT
op_or
(paren
id|mlc-&gt;opacket
op_amp
(paren
id|HIL_PKT_CMD
op_or
id|HIL_PKT_ADDR_MASK
op_or
id|HIL_PKT_DATA_MASK
)paren
)paren
suffix:semicolon
id|mlc-&gt;icount
op_assign
l_int|14
suffix:semicolon
multiline_comment|/* printk(KERN_DEBUG PREFIX &quot;&gt;[%x]&bslash;n&quot;, mlc-&gt;ipacket[0]); */
r_goto
id|wasup
suffix:semicolon
)brace
id|do_gettimeofday
c_func
(paren
op_amp
id|tv
)paren
suffix:semicolon
id|tv.tv_usec
op_add_assign
l_int|1000000
op_star
(paren
id|tv.tv_sec
op_minus
id|mlc-&gt;instart.tv_sec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tv.tv_usec
op_minus
id|mlc-&gt;instart.tv_usec
OG
id|mlc-&gt;intimeout
)paren
(brace
multiline_comment|/*&t;&t;  printk(&quot;!%i %i&quot;, &n;&t;&t;&t;&t;  tv.tv_usec - mlc-&gt;instart.tv_usec, &n;&t;&t;&t;&t;  mlc-&gt;intimeout);&n;&t;&t;  */
id|rc
op_assign
l_int|1
suffix:semicolon
id|up
c_func
(paren
op_amp
(paren
id|mlc-&gt;isem
)paren
)paren
suffix:semicolon
)brace
r_goto
id|done
suffix:semicolon
)brace
id|wasup
suffix:colon
id|up
c_func
(paren
op_amp
(paren
id|mlc-&gt;isem
)paren
)paren
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
r_goto
id|done
suffix:semicolon
id|done
suffix:colon
id|write_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|mlc-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|hp_sdc_mlc_cts
r_static
r_int
id|hp_sdc_mlc_cts
(paren
id|hil_mlc
op_star
id|mlc
)paren
(brace
r_struct
id|hp_sdc_mlc_priv_s
op_star
id|priv
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|priv
op_assign
id|mlc-&gt;priv
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
(paren
id|mlc-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Try to down the semaphores -- they should be up. */
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
(paren
id|mlc-&gt;isem
)paren
)paren
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_goto
id|busy
suffix:semicolon
)brace
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
(paren
id|mlc-&gt;osem
)paren
)paren
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
(paren
id|mlc-&gt;isem
)paren
)paren
suffix:semicolon
r_goto
id|busy
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
(paren
id|mlc-&gt;isem
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
(paren
id|mlc-&gt;osem
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
(paren
id|mlc-&gt;csem
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|priv-&gt;trans.act.semaphore
op_ne
op_amp
(paren
id|mlc-&gt;csem
)paren
)paren
r_goto
id|poll
suffix:semicolon
r_goto
id|busy
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|priv-&gt;tseq
(braket
l_int|4
)braket
op_amp
id|HP_SDC_USE_LOOP
)paren
)paren
r_goto
id|done
suffix:semicolon
id|poll
suffix:colon
id|priv-&gt;trans.act.semaphore
op_assign
op_amp
(paren
id|mlc-&gt;csem
)paren
suffix:semicolon
id|priv-&gt;trans.actidx
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;trans.idx
op_assign
l_int|1
suffix:semicolon
id|priv-&gt;trans.endidx
op_assign
l_int|5
suffix:semicolon
id|priv-&gt;tseq
(braket
l_int|0
)braket
op_assign
id|HP_SDC_ACT_POSTCMD
op_or
id|HP_SDC_ACT_DATAIN
op_or
id|HP_SDC_ACT_SEMAPHORE
suffix:semicolon
id|priv-&gt;tseq
(braket
l_int|1
)braket
op_assign
id|HP_SDC_CMD_READ_USE
suffix:semicolon
id|priv-&gt;tseq
(braket
l_int|2
)braket
op_assign
l_int|1
suffix:semicolon
id|priv-&gt;tseq
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;tseq
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
id|hp_sdc_enqueue_transaction
c_func
(paren
op_amp
(paren
id|priv-&gt;trans
)paren
)paren
suffix:semicolon
id|busy
suffix:colon
id|write_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|mlc-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|done
suffix:colon
id|priv-&gt;trans.act.semaphore
op_assign
op_amp
(paren
id|mlc-&gt;osem
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
(paren
id|mlc-&gt;csem
)paren
)paren
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|mlc-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hp_sdc_mlc_out
r_static
r_void
id|hp_sdc_mlc_out
(paren
id|hil_mlc
op_star
id|mlc
)paren
(brace
r_struct
id|hp_sdc_mlc_priv_s
op_star
id|priv
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|priv
op_assign
id|mlc-&gt;priv
suffix:semicolon
id|write_lock_irqsave
c_func
(paren
op_amp
(paren
id|mlc-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Try to down the semaphore -- it should be up. */
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
(paren
id|mlc-&gt;osem
)paren
)paren
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mlc-&gt;opacket
op_amp
id|HIL_DO_ALTER_CTRL
)paren
r_goto
id|do_control
suffix:semicolon
id|do_data
suffix:colon
r_if
c_cond
(paren
id|priv-&gt;emtestmode
)paren
(brace
id|up
c_func
(paren
op_amp
(paren
id|mlc-&gt;osem
)paren
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/* Shouldn&squot;t be sending commands when loop may be busy */
r_if
c_cond
(paren
id|down_trylock
c_func
(paren
op_amp
(paren
id|mlc-&gt;csem
)paren
)paren
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
(paren
id|mlc-&gt;csem
)paren
)paren
suffix:semicolon
id|priv-&gt;trans.actidx
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;trans.idx
op_assign
l_int|1
suffix:semicolon
id|priv-&gt;trans.act.semaphore
op_assign
op_amp
(paren
id|mlc-&gt;osem
)paren
suffix:semicolon
id|priv-&gt;trans.endidx
op_assign
l_int|6
suffix:semicolon
id|priv-&gt;tseq
(braket
l_int|0
)braket
op_assign
id|HP_SDC_ACT_DATAREG
op_or
id|HP_SDC_ACT_POSTCMD
op_or
id|HP_SDC_ACT_SEMAPHORE
suffix:semicolon
id|priv-&gt;tseq
(braket
l_int|1
)braket
op_assign
l_int|0x7
suffix:semicolon
id|priv-&gt;tseq
(braket
l_int|2
)braket
op_assign
(paren
id|mlc-&gt;opacket
op_amp
(paren
id|HIL_PKT_ADDR_MASK
op_or
id|HIL_PKT_CMD
)paren
)paren
op_rshift
id|HIL_PKT_ADDR_SHIFT
suffix:semicolon
id|priv-&gt;tseq
(braket
l_int|3
)braket
op_assign
(paren
id|mlc-&gt;opacket
op_amp
id|HIL_PKT_DATA_MASK
)paren
op_rshift
id|HIL_PKT_DATA_SHIFT
suffix:semicolon
id|priv-&gt;tseq
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* No timeout */
r_if
c_cond
(paren
id|priv-&gt;tseq
(braket
l_int|3
)braket
op_eq
id|HIL_CMD_DHR
)paren
id|priv-&gt;tseq
(braket
l_int|4
)braket
op_assign
l_int|1
suffix:semicolon
id|priv-&gt;tseq
(braket
l_int|5
)braket
op_assign
id|HP_SDC_CMD_DO_HIL
suffix:semicolon
r_goto
id|enqueue
suffix:semicolon
id|do_control
suffix:colon
id|priv-&gt;emtestmode
op_assign
id|mlc-&gt;opacket
op_amp
id|HIL_CTRL_TEST
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mlc-&gt;opacket
op_amp
(paren
id|HIL_CTRL_APE
op_or
id|HIL_CTRL_IPF
)paren
)paren
op_eq
id|HIL_CTRL_APE
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* we cannot emulate this, it should not be used. */
)brace
r_if
c_cond
(paren
(paren
id|mlc-&gt;opacket
op_amp
id|HIL_CTRL_ONLY
)paren
op_eq
id|HIL_CTRL_ONLY
)paren
r_goto
id|control_only
suffix:semicolon
r_if
c_cond
(paren
id|mlc-&gt;opacket
op_amp
id|HIL_CTRL_APE
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Should not send command/data after engaging APE */
r_goto
id|done
suffix:semicolon
)brace
multiline_comment|/* Disengaging APE this way would not be valid either since &n;&t; * the loop must be allowed to idle.&n;&t; *&n;&t; * So, it works out that we really never actually send control &n;&t; * and data when using SDC, we just send the data. &n;&t; */
r_goto
id|do_data
suffix:semicolon
id|control_only
suffix:colon
id|priv-&gt;trans.actidx
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;trans.idx
op_assign
l_int|1
suffix:semicolon
id|priv-&gt;trans.act.semaphore
op_assign
op_amp
(paren
id|mlc-&gt;osem
)paren
suffix:semicolon
id|priv-&gt;trans.endidx
op_assign
l_int|4
suffix:semicolon
id|priv-&gt;tseq
(braket
l_int|0
)braket
op_assign
id|HP_SDC_ACT_PRECMD
op_or
id|HP_SDC_ACT_DATAOUT
op_or
id|HP_SDC_ACT_SEMAPHORE
suffix:semicolon
id|priv-&gt;tseq
(braket
l_int|1
)braket
op_assign
id|HP_SDC_CMD_SET_LPC
suffix:semicolon
id|priv-&gt;tseq
(braket
l_int|2
)braket
op_assign
l_int|1
suffix:semicolon
singleline_comment|//&t;priv-&gt;tseq[3] = (mlc-&gt;ddc + 1) | HP_SDC_LPS_ACSUCC;
id|priv-&gt;tseq
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mlc-&gt;opacket
op_amp
id|HIL_CTRL_APE
)paren
(brace
id|priv-&gt;tseq
(braket
l_int|3
)braket
op_or_assign
id|HP_SDC_LPC_APE_IPF
suffix:semicolon
id|down_trylock
c_func
(paren
op_amp
(paren
id|mlc-&gt;csem
)paren
)paren
suffix:semicolon
)brace
id|enqueue
suffix:colon
id|hp_sdc_enqueue_transaction
c_func
(paren
op_amp
(paren
id|priv-&gt;trans
)paren
)paren
suffix:semicolon
id|done
suffix:colon
id|write_unlock_irqrestore
c_func
(paren
op_amp
(paren
id|mlc-&gt;lock
)paren
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|hp_sdc_mlc_init
r_static
r_int
id|__init
id|hp_sdc_mlc_init
c_func
(paren
r_void
)paren
(brace
id|hil_mlc
op_star
id|mlc
op_assign
op_amp
id|hp_sdc_mlc
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;Registering the System Domain Controller&squot;s HIL MLC.&bslash;n&quot;
)paren
suffix:semicolon
id|hp_sdc_mlc_priv.emtestmode
op_assign
l_int|0
suffix:semicolon
id|hp_sdc_mlc_priv.trans.seq
op_assign
id|hp_sdc_mlc_priv.tseq
suffix:semicolon
id|hp_sdc_mlc_priv.trans.act.semaphore
op_assign
op_amp
(paren
id|mlc-&gt;osem
)paren
suffix:semicolon
id|hp_sdc_mlc_priv.got5x
op_assign
l_int|0
suffix:semicolon
id|mlc-&gt;cts
op_assign
op_amp
id|hp_sdc_mlc_cts
suffix:semicolon
id|mlc-&gt;in
op_assign
op_amp
id|hp_sdc_mlc_in
suffix:semicolon
id|mlc-&gt;out
op_assign
op_amp
id|hp_sdc_mlc_out
suffix:semicolon
r_if
c_cond
(paren
id|hil_mlc_register
c_func
(paren
id|mlc
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Failed to register MLC structure with hil_mlc&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err0
suffix:semicolon
)brace
id|mlc-&gt;priv
op_assign
op_amp
id|hp_sdc_mlc_priv
suffix:semicolon
r_if
c_cond
(paren
id|hp_sdc_request_hil_irq
c_func
(paren
op_amp
id|hp_sdc_mlc_isr
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|PREFIX
l_string|&quot;Request for raw HIL ISR hook denied&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|err1
suffix:colon
r_if
c_cond
(paren
id|hil_mlc_unregister
c_func
(paren
id|mlc
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Failed to unregister MLC structure with hil_mlc.&bslash;n&quot;
l_string|&quot;This is bad.  Could cause an oops.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|err0
suffix:colon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
DECL|function|hp_sdc_mlc_exit
r_static
r_void
id|__exit
id|hp_sdc_mlc_exit
c_func
(paren
r_void
)paren
(brace
id|hil_mlc
op_star
id|mlc
op_assign
op_amp
id|hp_sdc_mlc
suffix:semicolon
r_if
c_cond
(paren
id|hp_sdc_release_hil_irq
c_func
(paren
op_amp
id|hp_sdc_mlc_isr
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Failed to release the raw HIL ISR hook.&bslash;n&quot;
l_string|&quot;This is bad.  Could cause an oops.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hil_mlc_unregister
c_func
(paren
id|mlc
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PREFIX
l_string|&quot;Failed to unregister MLC structure with hil_mlc.&bslash;n&quot;
l_string|&quot;This is bad.  Could cause an oops.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|variable|hp_sdc_mlc_init
id|module_init
c_func
(paren
id|hp_sdc_mlc_init
)paren
suffix:semicolon
DECL|variable|hp_sdc_mlc_exit
id|module_exit
c_func
(paren
id|hp_sdc_mlc_exit
)paren
suffix:semicolon
eof
