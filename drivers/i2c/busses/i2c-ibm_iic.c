multiline_comment|/*&n; * drivers/i2c/i2c-ibm_iic.c&n; *&n; * Support for the IIC peripheral on IBM PPC 4xx&n; *&n; * Copyright (c) 2003 Zultys Technologies.&n; * Eugene Surovegin &lt;eugene.surovegin@zultys.com&gt; or &lt;ebs@ebshome.net&gt;&n; *&n; * Based on original work by &n; * &t;Ian DaSilva  &lt;idasilva@mvista.com&gt;&n; *      Armin Kuster &lt;akuster@mvista.com&gt;&n; * &t;Matt Porter  &lt;mporter@mvista.com&gt;&n; *&n; *      Copyright 2000-2003 MontaVista Software Inc.&n; *&n; * Original driver version was highly leveraged from i2c-elektor.c&n; *&n; *   &t;Copyright 1995-97 Simon G. Vogl&n; *                1998-99 Hans Berglund&n; *&n; *   &t;With some changes from Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt; &n; *&t;and even Frodo Looijaard &lt;frodol@dds.nl&gt;&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-id.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
macro_line|#include &lt;asm/ibm4xx.h&gt;
macro_line|#include &quot;i2c-ibm_iic.h&quot;
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;2.0&quot;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;IBM IIC driver v&quot;
id|DRIVER_VERSION
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|iic_force_poll
r_static
r_int
id|iic_force_poll
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|iic_force_poll
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|iic_force_poll
comma
l_string|&quot;Force polling mode&quot;
)paren
suffix:semicolon
DECL|variable|iic_force_fast
r_static
r_int
id|iic_force_fast
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|iic_force_fast
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|iic_fast_poll
comma
l_string|&quot;Force fast mode (400 kHz)&quot;
)paren
suffix:semicolon
DECL|macro|DBG_LEVEL
mdefine_line|#define DBG_LEVEL 0
macro_line|#ifdef DBG
DECL|macro|DBG
macro_line|#undef DBG
macro_line|#endif
macro_line|#ifdef DBG2
DECL|macro|DBG2
macro_line|#undef DBG2
macro_line|#endif
macro_line|#if DBG_LEVEL &gt; 0
DECL|macro|DBG
macro_line|#  define DBG(x...)&t;printk(KERN_DEBUG &quot;ibm-iic&quot; ##x)
macro_line|#else
DECL|macro|DBG
macro_line|#  define DBG(x...)&t;((void)0)
macro_line|#endif
macro_line|#if DBG_LEVEL &gt; 1
DECL|macro|DBG2
macro_line|#  define DBG2(x...) &t;DBG( ##x )
macro_line|#else
DECL|macro|DBG2
macro_line|#  define DBG2(x...) &t;((void)0)
macro_line|#endif
macro_line|#if DBG_LEVEL &gt; 2
DECL|function|dump_iic_regs
r_static
r_void
id|dump_iic_regs
c_func
(paren
r_const
r_char
op_star
id|header
comma
r_struct
id|ibm_iic_private
op_star
id|dev
)paren
(brace
r_volatile
r_struct
id|iic_regs
op_star
id|iic
op_assign
id|dev-&gt;vaddr
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ibm-iic%d: %s&bslash;n&quot;
comma
id|dev-&gt;idx
comma
id|header
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;  cntl     = 0x%02x, mdcntl = 0x%02x&bslash;n&quot;
id|KERN_DEBUG
l_string|&quot;  sts      = 0x%02x, extsts = 0x%02x&bslash;n&quot;
id|KERN_DEBUG
l_string|&quot;  clkdiv   = 0x%02x, xfrcnt = 0x%02x&bslash;n&quot;
id|KERN_DEBUG
l_string|&quot;  xtcntlss = 0x%02x, directcntl = 0x%02x&bslash;n&quot;
comma
id|in_8
c_func
(paren
op_amp
id|iic-&gt;cntl
)paren
comma
id|in_8
c_func
(paren
op_amp
id|iic-&gt;mdcntl
)paren
comma
id|in_8
c_func
(paren
op_amp
id|iic-&gt;sts
)paren
comma
id|in_8
c_func
(paren
op_amp
id|iic-&gt;extsts
)paren
comma
id|in_8
c_func
(paren
op_amp
id|iic-&gt;clkdiv
)paren
comma
id|in_8
c_func
(paren
op_amp
id|iic-&gt;xfrcnt
)paren
comma
id|in_8
c_func
(paren
op_amp
id|iic-&gt;xtcntlss
)paren
comma
id|in_8
c_func
(paren
op_amp
id|iic-&gt;directcntl
)paren
)paren
suffix:semicolon
)brace
DECL|macro|DUMP_REGS
macro_line|#  define DUMP_REGS(h,dev)&t;dump_iic_regs((h),(dev))
macro_line|#else
DECL|macro|DUMP_REGS
macro_line|#  define DUMP_REGS(h,dev)&t;((void)0)
macro_line|#endif
multiline_comment|/* Enable/disable interrupt generation */
DECL|function|iic_interrupt_mode
r_static
r_inline
r_void
id|iic_interrupt_mode
c_func
(paren
r_struct
id|ibm_iic_private
op_star
id|dev
comma
r_int
id|enable
)paren
(brace
id|out_8
c_func
(paren
op_amp
id|dev-&gt;vaddr-&gt;intmsk
comma
id|enable
ques
c_cond
id|INTRMSK_EIMTC
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize IIC interface.&n; */
DECL|function|iic_dev_init
r_static
r_void
id|iic_dev_init
c_func
(paren
r_struct
id|ibm_iic_private
op_star
id|dev
)paren
(brace
r_volatile
r_struct
id|iic_regs
op_star
id|iic
op_assign
id|dev-&gt;vaddr
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;%d: init&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
multiline_comment|/* Clear master address */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;lmadr
comma
l_int|0
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|iic-&gt;hmadr
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Clear slave address */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;lsadr
comma
l_int|0
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|iic-&gt;hsadr
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Clear status &amp; extended status */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;sts
comma
id|STS_SCMP
op_or
id|STS_IRQA
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|iic-&gt;extsts
comma
id|EXTSTS_IRQP
op_or
id|EXTSTS_IRQD
op_or
id|EXTSTS_LA
op_or
id|EXTSTS_ICT
op_or
id|EXTSTS_XFRA
)paren
suffix:semicolon
multiline_comment|/* Set clock divider */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;clkdiv
comma
id|dev-&gt;clckdiv
)paren
suffix:semicolon
multiline_comment|/* Clear transfer count */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;xfrcnt
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Clear extended control and status */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;xtcntlss
comma
id|XTCNTLSS_SRC
op_or
id|XTCNTLSS_SRS
op_or
id|XTCNTLSS_SWC
op_or
id|XTCNTLSS_SWS
)paren
suffix:semicolon
multiline_comment|/* Clear control register */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;cntl
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Enable interrupts if possible */
id|iic_interrupt_mode
c_func
(paren
id|dev
comma
id|dev-&gt;irq
op_ge
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Set mode control */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;mdcntl
comma
id|MDCNTL_FMDB
op_or
id|MDCNTL_EINT
op_or
id|MDCNTL_EUBS
op_or
(paren
id|dev-&gt;fast_mode
ques
c_cond
id|MDCNTL_FSM
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|DUMP_REGS
c_func
(paren
l_string|&quot;iic_init&quot;
comma
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * Reset IIC interface&n; */
DECL|function|iic_dev_reset
r_static
r_void
id|iic_dev_reset
c_func
(paren
r_struct
id|ibm_iic_private
op_star
id|dev
)paren
(brace
r_volatile
r_struct
id|iic_regs
op_star
id|iic
op_assign
id|dev-&gt;vaddr
suffix:semicolon
r_int
id|i
suffix:semicolon
id|u8
id|dc
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;%d: soft reset&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
id|DUMP_REGS
c_func
(paren
l_string|&quot;reset&quot;
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* Place chip in the reset state */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;xtcntlss
comma
id|XTCNTLSS_SRST
)paren
suffix:semicolon
multiline_comment|/* Check if bus is free */
id|dc
op_assign
id|in_8
c_func
(paren
op_amp
id|iic-&gt;directcntl
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DIRCTNL_FREE
c_func
(paren
id|dc
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%d: trying to regain bus control&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
multiline_comment|/* Try to set bus free state */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;directcntl
comma
id|DIRCNTL_SDAC
op_or
id|DIRCNTL_SCC
)paren
suffix:semicolon
multiline_comment|/* Wait until we regain bus control */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|100
suffix:semicolon
op_increment
id|i
)paren
(brace
id|dc
op_assign
id|in_8
c_func
(paren
op_amp
id|iic-&gt;directcntl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|DIRCTNL_FREE
c_func
(paren
id|dc
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* Toggle SCL line */
id|dc
op_xor_assign
id|DIRCNTL_SCC
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|iic-&gt;directcntl
comma
id|dc
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|dc
op_xor_assign
id|DIRCNTL_SCC
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|iic-&gt;directcntl
comma
id|dc
)paren
suffix:semicolon
multiline_comment|/* be nice */
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Remove reset */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;xtcntlss
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Reinitialize interface */
id|iic_dev_init
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * IIC interrupt handler&n; */
DECL|function|iic_handler
r_static
id|irqreturn_t
id|iic_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|ibm_iic_private
op_star
id|dev
op_assign
(paren
r_struct
id|ibm_iic_private
op_star
)paren
id|dev_id
suffix:semicolon
r_volatile
r_struct
id|iic_regs
op_star
id|iic
op_assign
id|dev-&gt;vaddr
suffix:semicolon
id|DBG2
c_func
(paren
l_string|&quot;%d: irq handler, STS = 0x%02x, EXTSTS = 0x%02x&bslash;n&quot;
comma
id|dev-&gt;idx
comma
id|in_8
c_func
(paren
op_amp
id|iic-&gt;sts
)paren
comma
id|in_8
c_func
(paren
op_amp
id|iic-&gt;extsts
)paren
)paren
suffix:semicolon
multiline_comment|/* Acknowledge IRQ and wakeup iic_wait_for_tc */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;sts
comma
id|STS_IRQA
op_or
id|STS_SCMP
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;wq
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * Get master transfer result and clear errors if any.&n; * Returns the number of actually transferred bytes or error (&lt;0)&n; */
DECL|function|iic_xfer_result
r_static
r_int
id|iic_xfer_result
c_func
(paren
r_struct
id|ibm_iic_private
op_star
id|dev
)paren
(brace
r_volatile
r_struct
id|iic_regs
op_star
id|iic
op_assign
id|dev-&gt;vaddr
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|in_8
c_func
(paren
op_amp
id|iic-&gt;sts
)paren
op_amp
id|STS_ERR
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%d: xfer error, EXTSTS = 0x%02x&bslash;n&quot;
comma
id|dev-&gt;idx
comma
id|in_8
c_func
(paren
op_amp
id|iic-&gt;extsts
)paren
)paren
suffix:semicolon
multiline_comment|/* Clear errors and possible pending IRQs */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;extsts
comma
id|EXTSTS_IRQP
op_or
id|EXTSTS_IRQD
op_or
id|EXTSTS_LA
op_or
id|EXTSTS_ICT
op_or
id|EXTSTS_XFRA
)paren
suffix:semicolon
multiline_comment|/* Flush master data buffer */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;mdcntl
comma
id|in_8
c_func
(paren
op_amp
id|iic-&gt;mdcntl
)paren
op_or
id|MDCNTL_FMDB
)paren
suffix:semicolon
multiline_comment|/* Is bus free?&n;&t;&t; * If error happened during combined xfer&n;&t;&t; * IIC interface is usually stuck in some strange&n;&t;&t; * state, the only way out - soft reset.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|in_8
c_func
(paren
op_amp
id|iic-&gt;extsts
)paren
op_amp
id|EXTSTS_BCS_MASK
)paren
op_ne
id|EXTSTS_BCS_FREE
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%d: bus is stuck, resetting&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
id|iic_dev_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
r_else
r_return
id|in_8
c_func
(paren
op_amp
id|iic-&gt;xfrcnt
)paren
op_amp
id|XFRCNT_MTC_MASK
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to abort active transfer.&n; */
DECL|function|iic_abort_xfer
r_static
r_void
id|iic_abort_xfer
c_func
(paren
r_struct
id|ibm_iic_private
op_star
id|dev
)paren
(brace
r_volatile
r_struct
id|iic_regs
op_star
id|iic
op_assign
id|dev-&gt;vaddr
suffix:semicolon
r_int
r_int
id|x
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;%d: iic_abort_xfer&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|iic-&gt;cntl
comma
id|CNTL_HMT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Wait for the abort command to complete.&n;&t; * It&squot;s not worth to be optimized, just poll (timeout &gt;= 1 tick)&n;&t; */
id|x
op_assign
id|jiffies
op_plus
l_int|2
suffix:semicolon
r_while
c_loop
(paren
(paren
id|in_8
c_func
(paren
op_amp
id|iic-&gt;extsts
)paren
op_amp
id|EXTSTS_BCS_MASK
)paren
op_ne
id|EXTSTS_BCS_FREE
)paren
(brace
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|x
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%d: abort timeout, resetting...&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
id|iic_dev_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Just to clear errors */
id|iic_xfer_result
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Wait for master transfer to complete.&n; * It puts current process to sleep until we get interrupt or timeout expires.&n; * Returns the number of transferred bytes or error (&lt;0)&n; */
DECL|function|iic_wait_for_tc
r_static
r_int
(def_block
id|iic_wait_for_tc
c_func
(paren
r_struct
id|ibm_iic_private
op_star
id|dev
)paren
(brace
r_volatile
r_struct
id|iic_regs
op_star
id|iic
op_assign
id|dev-&gt;vaddr
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
op_ge
l_int|0
)paren
(brace
multiline_comment|/* Interrupt mode */
id|wait_queue_t
id|wait
suffix:semicolon
id|init_waitqueue_entry
c_func
(paren
op_amp
id|wait
comma
id|current
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|dev-&gt;wq
comma
op_amp
id|wait
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_8
c_func
(paren
op_amp
id|iic-&gt;sts
)paren
op_amp
id|STS_PT
)paren
id|schedule_timeout
c_func
(paren
id|dev-&gt;adap.timeout
op_star
id|HZ
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|dev-&gt;wq
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%d: wait interrupted&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|in_8
c_func
(paren
op_amp
id|iic-&gt;sts
)paren
op_amp
id|STS_PT
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%d: wait timeout&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Polling mode */
r_int
r_int
id|x
op_assign
id|jiffies
op_plus
id|dev-&gt;adap.timeout
op_star
id|HZ
suffix:semicolon
r_while
c_loop
(paren
id|in_8
c_func
(paren
op_amp
id|iic-&gt;sts
)paren
op_amp
id|STS_PT
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|x
)paren
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%d: poll timeout&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%d: poll interrupted&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|ret
OL
l_int|0
)paren
)paren
id|iic_abort_xfer
c_func
(paren
id|dev
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|iic_xfer_result
c_func
(paren
id|dev
)paren
suffix:semicolon
id|DBG2
c_func
(paren
l_string|&quot;%d: iic_wait_for_tc -&gt; %d&bslash;n&quot;
comma
id|dev-&gt;idx
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)def_block
multiline_comment|/*&n; * Low level master transfer routine&n; */
DECL|function|iic_xfer_bytes
r_static
r_int
id|iic_xfer_bytes
c_func
(paren
r_struct
id|ibm_iic_private
op_star
id|dev
comma
r_struct
id|i2c_msg
op_star
id|pm
comma
r_int
id|combined_xfer
)paren
(brace
r_volatile
r_struct
id|iic_regs
op_star
id|iic
op_assign
id|dev-&gt;vaddr
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|pm-&gt;buf
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|loops
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|len
op_assign
id|pm-&gt;len
suffix:semicolon
id|u8
id|cntl
op_assign
(paren
id|in_8
c_func
(paren
op_amp
id|iic-&gt;cntl
)paren
op_amp
id|CNTL_AMD
)paren
op_or
id|CNTL_PT
suffix:semicolon
r_if
c_cond
(paren
id|pm-&gt;flags
op_amp
id|I2C_M_RD
)paren
id|cntl
op_or_assign
id|CNTL_RW
suffix:semicolon
id|loops
op_assign
(paren
id|len
op_plus
l_int|3
)paren
op_div
l_int|4
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
id|loops
suffix:semicolon
op_increment
id|i
comma
id|len
op_sub_assign
l_int|4
)paren
(brace
r_int
id|count
op_assign
id|len
OG
l_int|4
ques
c_cond
l_int|4
suffix:colon
id|len
suffix:semicolon
id|u8
id|cmd
op_assign
id|cntl
op_or
(paren
(paren
id|count
op_minus
l_int|1
)paren
op_lshift
id|CNTL_TCT_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cntl
op_amp
id|CNTL_RW
)paren
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|count
suffix:semicolon
op_increment
id|j
)paren
id|out_8
c_func
(paren
(paren
r_volatile
id|u8
op_star
)paren
op_amp
id|iic-&gt;mdbuf
comma
op_star
id|buf
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|loops
op_minus
l_int|1
)paren
id|cmd
op_or_assign
id|CNTL_CHT
suffix:semicolon
r_else
r_if
c_cond
(paren
id|combined_xfer
)paren
id|cmd
op_or_assign
id|CNTL_RPST
suffix:semicolon
id|DBG2
c_func
(paren
l_string|&quot;%d: xfer_bytes, %d, CNTL = 0x%02x&bslash;n&quot;
comma
id|dev-&gt;idx
comma
id|count
comma
id|cmd
)paren
suffix:semicolon
multiline_comment|/* Start transfer */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;cntl
comma
id|cmd
)paren
suffix:semicolon
multiline_comment|/* Wait for completion */
id|ret
op_assign
id|iic_wait_for_tc
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|ret
OL
l_int|0
)paren
)paren
r_break
suffix:semicolon
r_else
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|ret
op_ne
id|count
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%d: xfer_bytes, requested %d, transfered %d&bslash;n&quot;
comma
id|dev-&gt;idx
comma
id|count
comma
id|ret
)paren
suffix:semicolon
multiline_comment|/* If it&squot;s not a last part of xfer, abort it */
r_if
c_cond
(paren
id|combined_xfer
op_logical_or
(paren
id|i
OL
id|loops
op_minus
l_int|1
)paren
)paren
id|iic_abort_xfer
c_func
(paren
id|dev
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EREMOTEIO
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cntl
op_amp
id|CNTL_RW
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|count
suffix:semicolon
op_increment
id|j
)paren
op_star
id|buf
op_increment
op_assign
id|in_8
c_func
(paren
(paren
r_volatile
id|u8
op_star
)paren
op_amp
id|iic-&gt;mdbuf
)paren
suffix:semicolon
)brace
r_return
id|ret
OG
l_int|0
ques
c_cond
l_int|0
suffix:colon
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Set target slave address for master transfer&n; */
DECL|function|iic_address
r_static
r_inline
r_void
id|iic_address
c_func
(paren
r_struct
id|ibm_iic_private
op_star
id|dev
comma
r_struct
id|i2c_msg
op_star
id|msg
)paren
(brace
r_volatile
r_struct
id|iic_regs
op_star
id|iic
op_assign
id|dev-&gt;vaddr
suffix:semicolon
id|u16
id|addr
op_assign
id|msg-&gt;addr
suffix:semicolon
id|DBG2
c_func
(paren
l_string|&quot;%d: iic_address, 0x%03x (%d-bit)&bslash;n&quot;
comma
id|dev-&gt;idx
comma
id|addr
comma
id|msg-&gt;flags
op_amp
id|I2C_M_TEN
ques
c_cond
l_int|10
suffix:colon
l_int|7
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;flags
op_amp
id|I2C_M_TEN
)paren
(brace
id|out_8
c_func
(paren
op_amp
id|iic-&gt;cntl
comma
id|CNTL_AMD
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|iic-&gt;lmadr
comma
id|addr
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|iic-&gt;hmadr
comma
l_int|0xf0
op_or
(paren
(paren
id|addr
op_rshift
l_int|7
)paren
op_amp
l_int|0x06
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|out_8
c_func
(paren
op_amp
id|iic-&gt;cntl
comma
l_int|0
)paren
suffix:semicolon
id|out_8
c_func
(paren
op_amp
id|iic-&gt;lmadr
comma
id|addr
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|iic_invalid_address
r_static
r_inline
r_int
id|iic_invalid_address
c_func
(paren
r_const
r_struct
id|i2c_msg
op_star
id|p
)paren
(brace
r_return
(paren
id|p-&gt;addr
OG
l_int|0x3ff
)paren
op_logical_or
(paren
op_logical_neg
(paren
id|p-&gt;flags
op_amp
id|I2C_M_TEN
)paren
op_logical_and
(paren
id|p-&gt;addr
OG
l_int|0x7f
)paren
)paren
suffix:semicolon
)brace
DECL|function|iic_address_neq
r_static
r_inline
r_int
id|iic_address_neq
c_func
(paren
r_const
r_struct
id|i2c_msg
op_star
id|p1
comma
r_const
r_struct
id|i2c_msg
op_star
id|p2
)paren
(brace
r_return
(paren
id|p1-&gt;addr
op_ne
id|p2-&gt;addr
)paren
op_logical_or
(paren
(paren
id|p1-&gt;flags
op_amp
id|I2C_M_TEN
)paren
op_ne
(paren
id|p2-&gt;flags
op_amp
id|I2C_M_TEN
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic master transfer entrypoint. &n; * Returns the number of processed messages or error (&lt;0)&n; */
DECL|function|iic_xfer
r_static
r_int
id|iic_xfer
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
r_struct
id|i2c_msg
id|msgs
(braket
)braket
comma
r_int
id|num
)paren
(brace
r_struct
id|ibm_iic_private
op_star
id|dev
op_assign
(paren
r_struct
id|ibm_iic_private
op_star
)paren
(paren
id|i2c_get_adapdata
c_func
(paren
id|adap
)paren
)paren
suffix:semicolon
r_volatile
r_struct
id|iic_regs
op_star
id|iic
op_assign
id|dev-&gt;vaddr
suffix:semicolon
r_int
id|i
comma
id|ret
op_assign
l_int|0
suffix:semicolon
id|DBG2
c_func
(paren
l_string|&quot;%d: iic_xfer, %d msg(s)&bslash;n&quot;
comma
id|dev-&gt;idx
comma
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|num
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Check the sanity of the passed messages.&n;&t; * Uhh, generic i2c layer is more suitable place for such code...&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|iic_invalid_address
c_func
(paren
op_amp
id|msgs
(braket
l_int|0
)braket
)paren
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%d: invalid address 0x%03x (%d-bit)&bslash;n&quot;
comma
id|dev-&gt;idx
comma
id|msgs
(braket
l_int|0
)braket
dot
id|addr
comma
id|msgs
(braket
l_int|0
)braket
dot
id|flags
op_amp
id|I2C_M_TEN
ques
c_cond
l_int|10
suffix:colon
l_int|7
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|msgs
(braket
id|i
)braket
dot
id|len
op_le
l_int|0
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%d: invalid len %d in msg[%d]&bslash;n&quot;
comma
id|dev-&gt;idx
comma
id|msgs
(braket
id|i
)braket
dot
id|len
comma
id|i
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|iic_address_neq
c_func
(paren
op_amp
id|msgs
(braket
l_int|0
)braket
comma
op_amp
id|msgs
(braket
id|i
)braket
)paren
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%d: invalid addr in msg[%d]&bslash;n&quot;
comma
id|dev-&gt;idx
comma
id|i
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/* Check bus state */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
id|in_8
c_func
(paren
op_amp
id|iic-&gt;extsts
)paren
op_amp
id|EXTSTS_BCS_MASK
)paren
op_ne
id|EXTSTS_BCS_FREE
)paren
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%d: iic_xfer, bus is not free&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
multiline_comment|/* Usually it means something serious has happend.&n;&t;&t; * We *cannot* have unfinished previous transfer&n;&t;&t; * so it doesn&squot;t make any sense to try to stop it.&n;&t;&t; * Probably we were not able to recover from the &n;&t;&t; * previous error.&n;&t;&t; * The only *reasonable* thing I can think of here&n;&t;&t; * is soft reset.  --ebs&n;&t;&t; */
id|iic_dev_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|in_8
c_func
(paren
op_amp
id|iic-&gt;extsts
)paren
op_amp
id|EXTSTS_BCS_MASK
)paren
op_ne
id|EXTSTS_BCS_FREE
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;%d: iic_xfer, bus is still not free&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Flush master data buffer (just in case) */
id|out_8
c_func
(paren
op_amp
id|iic-&gt;mdcntl
comma
id|in_8
c_func
(paren
op_amp
id|iic-&gt;mdcntl
)paren
op_or
id|MDCNTL_FMDB
)paren
suffix:semicolon
)brace
multiline_comment|/* Load slave address */
id|iic_address
c_func
(paren
id|dev
comma
op_amp
id|msgs
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* Do real transfer */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
op_logical_and
op_logical_neg
id|ret
suffix:semicolon
op_increment
id|i
)paren
id|ret
op_assign
id|iic_xfer_bytes
c_func
(paren
id|dev
comma
op_amp
id|msgs
(braket
id|i
)braket
comma
id|i
OL
id|num
op_minus
l_int|1
)paren
suffix:semicolon
r_return
id|ret
OL
l_int|0
ques
c_cond
id|ret
suffix:colon
id|num
suffix:semicolon
)brace
DECL|function|iic_func
r_static
id|u32
id|iic_func
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_return
id|I2C_FUNC_I2C
op_or
id|I2C_FUNC_SMBUS_EMUL
op_or
id|I2C_FUNC_10BIT_ADDR
suffix:semicolon
)brace
DECL|variable|iic_algo
r_static
r_struct
id|i2c_algorithm
id|iic_algo
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;IBM IIC algorithm&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_OCP
comma
dot
id|master_xfer
op_assign
id|iic_xfer
comma
dot
id|smbus_xfer
op_assign
l_int|NULL
comma
dot
id|slave_send
op_assign
l_int|NULL
comma
dot
id|slave_recv
op_assign
l_int|NULL
comma
dot
id|algo_control
op_assign
l_int|NULL
comma
dot
id|functionality
op_assign
id|iic_func
)brace
suffix:semicolon
multiline_comment|/*&n; * Calculates IICx_CLCKDIV value for a specific OPB clock frequency&n; */
DECL|function|iic_clckdiv
r_static
r_inline
id|u8
id|iic_clckdiv
c_func
(paren
r_int
r_int
id|opb
)paren
(brace
multiline_comment|/* Compatibility kludge, should go away after all cards&n;&t; * are fixed to fill correct value for opbfreq.&n;&t; * Previous driver version used hardcoded divider value 4,&n;&t; * it corresponds to OPB frequency from the range (40, 50] MHz&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|opb
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ibm-iic: using compatibility value for OPB freq,&quot;
l_string|&quot; fix your board specific setup&bslash;n&quot;
)paren
suffix:semicolon
id|opb
op_assign
l_int|50000000
suffix:semicolon
)brace
multiline_comment|/* Convert to MHz */
id|opb
op_div_assign
l_int|1000000
suffix:semicolon
r_if
c_cond
(paren
id|opb
template_param
l_int|150
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;ibm-iic: invalid OPB clock frequency %u MHz&bslash;n&quot;
comma
id|opb
)paren
suffix:semicolon
id|opb
op_assign
id|opb
OL
l_int|20
ques
c_cond
l_int|20
suffix:colon
l_int|150
suffix:semicolon
)brace
r_return
(paren
id|u8
)paren
(paren
(paren
id|opb
op_plus
l_int|9
)paren
op_div
l_int|10
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Register single IIC interface&n; */
DECL|function|iic_probe
r_static
r_int
id|__devinit
(def_block
id|iic_probe
c_func
(paren
r_struct
id|ocp_device
op_star
id|ocp
)paren
(brace
r_struct
id|ibm_iic_private
op_star
id|dev
suffix:semicolon
r_struct
id|i2c_adapter
op_star
id|adap
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|bd_t
op_star
id|bd
op_assign
(paren
id|bd_t
op_star
)paren
op_amp
id|__res
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|dev
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;ibm-iic: failed to allocate device data&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dev
)paren
)paren
suffix:semicolon
id|dev-&gt;idx
op_assign
id|ocp-&gt;num
suffix:semicolon
id|ocp_set_drvdata
c_func
(paren
id|ocp
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;vaddr
op_assign
id|ioremap
c_func
(paren
id|ocp-&gt;paddr
comma
r_sizeof
(paren
r_struct
id|iic_regs
)paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;ibm-iic%d: failed to ioremap device registers&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_goto
id|fail2
suffix:semicolon
)brace
id|init_waitqueue_head
c_func
(paren
op_amp
id|dev-&gt;wq
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|iic_force_poll
ques
c_cond
op_minus
l_int|1
suffix:colon
id|ocp-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
op_ge
l_int|0
)paren
(brace
multiline_comment|/* Disable interrupts until we finish intialization,&n;&t;&t;   assumes level-sensitive IRQ setup...&n;&t;&t; */
id|iic_interrupt_mode
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|iic_handler
comma
l_int|0
comma
l_string|&quot;IBM IIC&quot;
comma
id|dev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ibm-iic%d: request_irq %d failed&bslash;n&quot;
comma
id|dev-&gt;idx
comma
id|dev-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* Fallback to the polling mode */
id|dev-&gt;irq
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dev-&gt;irq
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ibm-iic%d: using polling mode&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
multiline_comment|/* Board specific settings */
id|BUG_ON
c_func
(paren
id|dev-&gt;idx
op_ge
r_sizeof
(paren
id|bd-&gt;bi_iic_fast
)paren
op_div
r_sizeof
(paren
id|bd-&gt;bi_iic_fast
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|dev-&gt;fast_mode
op_assign
id|iic_force_fast
ques
c_cond
l_int|1
suffix:colon
id|bd-&gt;bi_iic_fast
(braket
id|dev-&gt;idx
)braket
suffix:semicolon
multiline_comment|/* clckdiv is the same for *all* IIC interfaces, &n;&t; * but I&squot;d rather make a copy than introduce another global. --ebs&n;&t; */
id|dev-&gt;clckdiv
op_assign
id|iic_clckdiv
c_func
(paren
id|bd-&gt;bi_opb_busfreq
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;%d: clckdiv = %d&bslash;n&quot;
comma
id|dev-&gt;idx
comma
id|dev-&gt;clckdiv
)paren
suffix:semicolon
multiline_comment|/* Initialize IIC interface */
id|iic_dev_init
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Register it with i2c layer */
id|adap
op_assign
op_amp
id|dev-&gt;adap
suffix:semicolon
id|strcpy
c_func
(paren
id|adap-&gt;name
comma
l_string|&quot;IBM IIC&quot;
)paren
suffix:semicolon
id|i2c_set_adapdata
c_func
(paren
id|adap
comma
id|dev
)paren
suffix:semicolon
id|adap-&gt;id
op_assign
id|I2C_HW_OCP
op_or
id|iic_algo.id
suffix:semicolon
id|adap-&gt;algo
op_assign
op_amp
id|iic_algo
suffix:semicolon
id|adap-&gt;client_register
op_assign
l_int|NULL
suffix:semicolon
id|adap-&gt;client_unregister
op_assign
l_int|NULL
suffix:semicolon
id|adap-&gt;timeout
op_assign
l_int|1
suffix:semicolon
id|adap-&gt;retries
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|i2c_add_adapter
c_func
(paren
id|adap
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;ibm-iic%d: failed to register i2c adapter&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ibm-iic%d: using %s mode&bslash;n&quot;
comma
id|dev-&gt;idx
comma
id|dev-&gt;fast_mode
ques
c_cond
l_string|&quot;fast (400 kHz)&quot;
suffix:colon
l_string|&quot;standard (100 kHz)&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
r_if
c_cond
(paren
id|dev-&gt;irq
op_ge
l_int|0
)paren
(brace
id|iic_interrupt_mode
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
)brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|dev-&gt;vaddr
)paren
suffix:semicolon
id|fail2
suffix:colon
id|ocp_set_drvdata
c_func
(paren
id|ocp
comma
l_int|0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
)def_block
multiline_comment|/*&n; * Cleanup initialized IIC interface&n; */
DECL|function|iic_remove
r_static
r_void
id|__devexit
id|iic_remove
c_func
(paren
r_struct
id|ocp_device
op_star
id|ocp
)paren
(brace
r_struct
id|ibm_iic_private
op_star
id|dev
op_assign
(paren
r_struct
id|ibm_iic_private
op_star
)paren
id|ocp_get_drvdata
c_func
(paren
id|ocp
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|dev
op_eq
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_del_adapter
c_func
(paren
op_amp
id|dev-&gt;adap
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;ibm-iic%d: failed to delete i2c adapter :(&bslash;n&quot;
comma
id|dev-&gt;idx
)paren
suffix:semicolon
multiline_comment|/* That&squot;s *very* bad, just shutdown IRQ ... */
r_if
c_cond
(paren
id|dev-&gt;irq
op_ge
l_int|0
)paren
(brace
id|iic_interrupt_mode
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|dev-&gt;irq
op_ge
l_int|0
)paren
(brace
id|iic_interrupt_mode
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
)brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|dev-&gt;vaddr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
DECL|variable|__devinitdata
r_static
r_struct
id|ocp_device_id
id|ibm_iic_ids
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_IBM
comma
dot
id|device
op_assign
id|OCP_FUNC_IIC
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_INVALID
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|ocp
comma
id|ibm_iic_ids
)paren
suffix:semicolon
DECL|variable|ibm_iic_driver
r_static
r_struct
id|ocp_driver
id|ibm_iic_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ocp_iic&quot;
comma
dot
id|id_table
op_assign
id|ibm_iic_ids
comma
dot
id|probe
op_assign
id|iic_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|iic_remove
)paren
comma
macro_line|#if defined(CONFIG_PM)
dot
id|suspend
op_assign
l_int|NULL
comma
dot
id|resume
op_assign
l_int|NULL
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|iic_init
r_static
r_int
id|__init
id|iic_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;IBM IIC driver v&quot;
id|DRIVER_VERSION
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ocp_module_init
c_func
(paren
op_amp
id|ibm_iic_driver
)paren
suffix:semicolon
)brace
DECL|function|iic_exit
r_static
r_void
id|__exit
id|iic_exit
c_func
(paren
r_void
)paren
(brace
id|ocp_unregister_driver
c_func
(paren
op_amp
id|ibm_iic_driver
)paren
suffix:semicolon
)brace
DECL|variable|iic_init
id|module_init
c_func
(paren
id|iic_init
)paren
suffix:semicolon
DECL|variable|iic_exit
id|module_exit
c_func
(paren
id|iic_exit
)paren
suffix:semicolon
eof
