multiline_comment|/*&n; *  drivers/s390/cio/device_ops.c&n; *&n; *   $Revision: 1.34 $&n; *&n; *    Copyright (C) 2002 IBM Deutschland Entwicklung GmbH,&n; *&t;&t;&t; IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *               Cornelia Huck (cohuck@de.ibm.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/ccwdev.h&gt;
macro_line|#include &lt;asm/idals.h&gt;
macro_line|#include &lt;asm/qdio.h&gt;
macro_line|#include &quot;cio.h&quot;
macro_line|#include &quot;cio_debug.h&quot;
macro_line|#include &quot;css.h&quot;
macro_line|#include &quot;device.h&quot;
macro_line|#include &quot;qdio.h&quot;
r_int
DECL|function|ccw_device_set_options
id|ccw_device_set_options
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_int
r_int
id|flags
)paren
(brace
multiline_comment|/*&n;&t;* The flag usage is mutal exclusive ...&n;&t;*/
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|CCWDEV_EARLY_NOTIFICATION
)paren
op_logical_and
(paren
id|flags
op_amp
id|CCWDEV_REPORT_ALL
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|options.fast
op_assign
(paren
id|flags
op_amp
id|CCWDEV_EARLY_NOTIFICATION
)paren
op_ne
l_int|0
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|options.repall
op_assign
(paren
id|flags
op_amp
id|CCWDEV_REPORT_ALL
)paren
op_ne
l_int|0
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|options.pgroup
op_assign
(paren
id|flags
op_amp
id|CCWDEV_DO_PATHGROUP
)paren
op_ne
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|ccw_device_clear
id|ccw_device_clear
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_int
r_int
id|intparm
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_ne
id|DEV_STATE_ONLINE
op_logical_and
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_ne
id|DEV_STATE_W4SENSE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sch
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ret
op_assign
id|cio_clear
c_func
(paren
id|sch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
op_assign
id|intparm
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|ccw_device_start
id|ccw_device_start
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_struct
id|ccw1
op_star
id|cpa
comma
r_int
r_int
id|intparm
comma
id|__u8
id|lpm
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sch
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_ne
id|DEV_STATE_ONLINE
op_logical_or
id|sch-&gt;schib.scsw.actl
op_ne
l_int|0
op_logical_or
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|flags.doverify
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|ret
op_assign
id|cio_set_options
(paren
id|sch
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* 0xe4e2c5d9 == ebcdic &quot;USER&quot; */
id|ret
op_assign
id|cio_start
(paren
id|sch
comma
id|cpa
comma
l_int|0xe4e2c5d9
comma
id|lpm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
op_assign
id|intparm
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|ccw_device_start_timeout
id|ccw_device_start_timeout
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_struct
id|ccw1
op_star
id|cpa
comma
r_int
r_int
id|intparm
comma
id|__u8
id|lpm
comma
r_int
r_int
id|flags
comma
r_int
id|expires
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ccw_device_set_timeout
c_func
(paren
id|cdev
comma
id|expires
)paren
suffix:semicolon
id|ret
op_assign
id|ccw_device_start
c_func
(paren
id|cdev
comma
id|cpa
comma
id|intparm
comma
id|lpm
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
id|ccw_device_set_timeout
c_func
(paren
id|cdev
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|ccw_device_halt
id|ccw_device_halt
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_int
r_int
id|intparm
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_ne
id|DEV_STATE_ONLINE
op_logical_and
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_ne
id|DEV_STATE_W4SENSE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sch
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ret
op_assign
id|cio_halt
c_func
(paren
id|sch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
op_assign
id|intparm
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|ccw_device_resume
id|ccw_device_resume
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sch
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_ne
id|DEV_STATE_ONLINE
op_logical_or
op_logical_neg
(paren
id|sch-&gt;schib.scsw.actl
op_amp
id|SCSW_ACTL_SUSPENDED
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|cio_resume
c_func
(paren
id|sch
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Pass interrupt to device driver.&n; */
r_int
DECL|function|ccw_device_call_handler
id|ccw_device_call_handler
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_int
r_int
id|stctl
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * we allow for the device action handler if .&n;&t; *  - we received ending status&n;&t; *  - the action handler requested to see all interrupts&n;&t; *  - we received an intermediate status&n;&t; *  - fast notification was requested (primary status)&n;&t; *  - unsolicited interrupts&n;&t; */
id|stctl
op_assign
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|irb.scsw.stctl
suffix:semicolon
r_if
c_cond
(paren
id|sch-&gt;schib.scsw.actl
op_ne
l_int|0
op_logical_and
op_logical_neg
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|options.repall
op_logical_and
op_logical_neg
(paren
id|stctl
op_amp
id|SCSW_STCTL_INTER_STATUS
)paren
op_logical_and
op_logical_neg
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|options.fast
op_logical_and
(paren
id|stctl
op_amp
id|SCSW_STCTL_PRIM_STATUS
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Now we are ready to call the device driver interrupt handler.&n;&t; */
r_if
c_cond
(paren
id|cdev-&gt;handler
)paren
id|cdev
op_member_access_from_pointer
id|handler
c_func
(paren
id|cdev
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
comma
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|irb
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Clear the old and now useless interrupt response block.&n;&t; */
id|memset
c_func
(paren
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|irb
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|irb
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Search for CIW command in extended sense data.&n; */
r_struct
id|ciw
op_star
DECL|function|ccw_device_get_ciw
id|ccw_device_get_ciw
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
id|__u32
id|ct
)paren
(brace
r_int
id|ciw_cnt
suffix:semicolon
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|flags.esid
op_eq
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|ciw_cnt
op_assign
l_int|0
suffix:semicolon
id|ciw_cnt
OL
id|MAX_CIWS
suffix:semicolon
id|ciw_cnt
op_increment
)paren
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|senseid.ciw
(braket
id|ciw_cnt
)braket
dot
id|ct
op_eq
id|ct
)paren
r_return
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|senseid.ciw
op_plus
id|ciw_cnt
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|__u8
DECL|function|ccw_device_get_path_mask
id|ccw_device_get_path_mask
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sch
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
id|sch-&gt;vpm
suffix:semicolon
)brace
r_static
r_void
DECL|function|ccw_device_wake_up
id|ccw_device_wake_up
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_int
r_int
id|ip
comma
r_struct
id|irb
op_star
id|irb
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ip
)paren
multiline_comment|/* unsolicited interrupt */
r_return
suffix:semicolon
multiline_comment|/* Abuse intparm for error reporting. */
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|irb
)paren
)paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
op_assign
op_minus
id|EIO
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|irb-&gt;scsw.dstat
op_ne
(paren
id|DEV_STAT_CHN_END
op_or
id|DEV_STAT_DEV_END
)paren
)paren
op_logical_or
(paren
id|irb-&gt;scsw.cstat
op_ne
l_int|0
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * We didn&squot;t get channel end / device end. Check if path&n;&t;&t; * verification has been started; we can retry after it has&n;&t;&t; * finished. We also retry unit checks except for command reject&n;&t;&t; * or intervention required.&n;&t;&t; */
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|flags.doverify
op_logical_or
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_eq
id|DEV_STATE_VERIFY
)paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
(paren
id|irb-&gt;scsw.dstat
op_amp
id|DEV_STAT_UNIT_CHECK
)paren
op_logical_and
op_logical_neg
(paren
id|irb-&gt;ecw
(braket
l_int|0
)braket
op_amp
(paren
id|SNS0_CMD_REJECT
op_or
id|SNS0_INTERVENTION_REQ
)paren
)paren
)paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_else
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_else
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|wait_q
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|__ccw_device_retry_loop
id|__ccw_device_retry_loop
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_struct
id|ccw1
op_star
id|ccw
comma
r_int
id|magic
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
r_do
(brace
id|ret
op_assign
id|cio_start
(paren
id|sch
comma
id|ccw
comma
id|magic
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_eq
op_minus
id|EBUSY
)paren
op_logical_or
(paren
id|ret
op_eq
op_minus
id|EACCES
)paren
)paren
(brace
multiline_comment|/* Try again later. */
id|spin_unlock_irq
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
multiline_comment|/* Non-retryable error. */
r_break
suffix:semicolon
multiline_comment|/* Wait for end of request. */
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
op_assign
id|magic
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
id|wait_event
c_func
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|wait_q
comma
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
op_eq
op_minus
id|EIO
)paren
op_logical_or
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
op_eq
op_minus
id|EAGAIN
)paren
op_logical_or
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
op_eq
l_int|0
)paren
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* Check at least for channel end / device end */
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
op_eq
op_minus
id|EIO
)paren
(brace
multiline_comment|/* Non-retryable error. */
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|intparm
op_eq
l_int|0
)paren
multiline_comment|/* Success. */
r_break
suffix:semicolon
multiline_comment|/* Try again later. */
id|spin_unlock_irq
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * read_dev_chars() - read device characteristics&n; * @param cdev   target ccw device&n; * @param buffer pointer to buffer for rdc data&n; * @param length size of rdc data&n; * @returns 0 for success, negative error value on failure&n; *&n; * Context:&n; *   called for online device, lock not held&n; **/
r_int
DECL|function|read_dev_chars
id|read_dev_chars
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_void
op_star
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|ccw_device
op_star
comma
r_int
r_int
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
r_char
id|dbf_txt
(braket
l_int|15
)braket
suffix:semicolon
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_struct
id|ccw1
op_star
id|rdc_ccw
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
op_logical_or
op_logical_neg
id|length
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
id|sprintf
(paren
id|dbf_txt
comma
l_string|&quot;rddevch%x&quot;
comma
id|sch-&gt;irq
)paren
suffix:semicolon
id|CIO_TRACE_EVENT
(paren
l_int|4
comma
id|dbf_txt
)paren
suffix:semicolon
id|rdc_ccw
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ccw1
)paren
comma
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rdc_ccw
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|rdc_ccw
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ccw1
)paren
)paren
suffix:semicolon
id|rdc_ccw-&gt;cmd_code
op_assign
id|CCW_CMD_RDC
suffix:semicolon
id|rdc_ccw-&gt;count
op_assign
id|length
suffix:semicolon
id|rdc_ccw-&gt;flags
op_assign
id|CCW_FLAG_SLI
suffix:semicolon
id|ret
op_assign
id|set_normalized_cda
(paren
id|rdc_ccw
comma
(paren
op_star
id|buffer
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|rdc_ccw
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|spin_lock_irq
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* Save interrupt handler. */
id|handler
op_assign
id|cdev-&gt;handler
suffix:semicolon
multiline_comment|/* Temporarily install own handler. */
id|cdev-&gt;handler
op_assign
id|ccw_device_wake_up
suffix:semicolon
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_ne
id|DEV_STATE_ONLINE
)paren
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sch-&gt;schib.scsw.actl
op_ne
l_int|0
op_logical_or
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|flags.doverify
)paren
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_else
multiline_comment|/* 0x00D9C4C3 == ebcdic &quot;RDC&quot; */
id|ret
op_assign
id|__ccw_device_retry_loop
c_func
(paren
id|cdev
comma
id|rdc_ccw
comma
l_int|0x00D9C4C3
)paren
suffix:semicolon
multiline_comment|/* Restore interrupt handler. */
id|cdev-&gt;handler
op_assign
id|handler
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
id|clear_normalized_cda
(paren
id|rdc_ccw
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|rdc_ccw
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; *  Read Configuration data&n; */
r_int
DECL|function|read_conf_data
id|read_conf_data
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_void
op_star
op_star
id|buffer
comma
r_int
op_star
id|length
)paren
(brace
r_void
(paren
op_star
id|handler
)paren
(paren
r_struct
id|ccw_device
op_star
comma
r_int
r_int
comma
r_struct
id|irb
op_star
)paren
suffix:semicolon
r_char
id|dbf_txt
(braket
l_int|15
)braket
suffix:semicolon
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_struct
id|ciw
op_star
id|ciw
suffix:semicolon
r_char
op_star
id|rcd_buf
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_struct
id|ccw1
op_star
id|rcd_ccw
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
op_logical_or
op_logical_neg
id|length
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
id|sprintf
(paren
id|dbf_txt
comma
l_string|&quot;rdconf%x&quot;
comma
id|sch-&gt;irq
)paren
suffix:semicolon
id|CIO_TRACE_EVENT
(paren
l_int|4
comma
id|dbf_txt
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * scan for RCD command in extended SenseID data&n;&t; */
id|ciw
op_assign
id|ccw_device_get_ciw
c_func
(paren
id|cdev
comma
id|CIW_TYPE_RCD
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ciw
op_logical_or
id|ciw-&gt;cmd
op_eq
l_int|0
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
id|rcd_ccw
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ccw1
)paren
comma
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rcd_ccw
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|rcd_ccw
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ccw1
)paren
)paren
suffix:semicolon
id|rcd_buf
op_assign
id|kmalloc
c_func
(paren
id|ciw-&gt;count
comma
id|GFP_KERNEL
op_or
id|GFP_DMA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rcd_buf
)paren
(brace
id|kfree
c_func
(paren
id|rcd_ccw
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
(paren
id|rcd_buf
comma
l_int|0
comma
id|ciw-&gt;count
)paren
suffix:semicolon
id|rcd_ccw-&gt;cmd_code
op_assign
id|ciw-&gt;cmd
suffix:semicolon
id|rcd_ccw-&gt;cda
op_assign
(paren
id|__u32
)paren
id|__pa
(paren
id|rcd_buf
)paren
suffix:semicolon
id|rcd_ccw-&gt;count
op_assign
id|ciw-&gt;count
suffix:semicolon
id|rcd_ccw-&gt;flags
op_assign
id|CCW_FLAG_SLI
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* Save interrupt handler. */
id|handler
op_assign
id|cdev-&gt;handler
suffix:semicolon
multiline_comment|/* Temporarily install own handler. */
id|cdev-&gt;handler
op_assign
id|ccw_device_wake_up
suffix:semicolon
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_ne
id|DEV_STATE_ONLINE
)paren
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sch-&gt;schib.scsw.actl
op_ne
l_int|0
op_logical_or
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|flags.doverify
)paren
id|ret
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_else
multiline_comment|/* 0x00D9C3C4 == ebcdic &quot;RCD&quot; */
id|ret
op_assign
id|__ccw_device_retry_loop
c_func
(paren
id|cdev
comma
id|rcd_ccw
comma
l_int|0x00D9C3C4
)paren
suffix:semicolon
multiline_comment|/* Restore interrupt handler. */
id|cdev-&gt;handler
op_assign
id|handler
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
multiline_comment|/*&n; &t; * on success we update the user input parms&n; &t; */
r_if
c_cond
(paren
id|ret
)paren
(brace
id|kfree
(paren
id|rcd_buf
)paren
suffix:semicolon
op_star
id|buffer
op_assign
l_int|NULL
suffix:semicolon
op_star
id|length
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
op_star
id|length
op_assign
id|ciw-&gt;count
suffix:semicolon
op_star
id|buffer
op_assign
id|rcd_buf
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|rcd_ccw
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to issue an unconditional reserve on a boxed device.&n; */
r_int
DECL|function|ccw_device_stlck
id|ccw_device_stlck
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_char
id|buf
(braket
l_int|32
)braket
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
id|CIO_TRACE_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;stl lock&quot;
)paren
suffix:semicolon
id|CIO_TRACE_EVENT
c_func
(paren
l_int|2
comma
id|cdev-&gt;dev.bus_id
)paren
suffix:semicolon
multiline_comment|/* Setup ccw. This cmd code seems not to be in use elsewhere. */
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iccws
(braket
l_int|0
)braket
dot
id|cmd_code
op_assign
id|CCW_CMD_STLCK
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iccws
(braket
l_int|0
)braket
dot
id|cda
op_assign
(paren
id|__u32
)paren
id|__pa
c_func
(paren
id|buf
)paren
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iccws
(braket
l_int|0
)braket
dot
id|count
op_assign
l_int|32
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iccws
(braket
l_int|0
)braket
dot
id|flags
op_assign
id|CCW_FLAG_SLI
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sch-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
id|cio_start
c_func
(paren
id|sch
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iccws
comma
l_int|0xE2D3C3D2
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sch-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|wait_event
c_func
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|wait_q
comma
id|sch-&gt;schib.scsw.actl
op_eq
l_int|0
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sch-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|irb.scsw.dstat
op_ne
(paren
id|DEV_STAT_CHN_END
op_or
id|DEV_STAT_DEV_END
)paren
)paren
op_logical_or
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|irb.scsw.cstat
op_ne
l_int|0
)paren
)paren
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* Clear irb. */
id|memset
c_func
(paren
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|irb
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|irb
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sch-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
singleline_comment|// FIXME: these have to go:
r_int
DECL|function|_ccw_device_get_subchannel_number
id|_ccw_device_get_subchannel_number
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_return
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|irq
suffix:semicolon
)brace
r_int
DECL|function|_ccw_device_get_device_number
id|_ccw_device_get_device_number
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_return
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|devno
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|ccw_device_set_options
id|EXPORT_SYMBOL
c_func
(paren
id|ccw_device_set_options
)paren
suffix:semicolon
DECL|variable|ccw_device_clear
id|EXPORT_SYMBOL
c_func
(paren
id|ccw_device_clear
)paren
suffix:semicolon
DECL|variable|ccw_device_halt
id|EXPORT_SYMBOL
c_func
(paren
id|ccw_device_halt
)paren
suffix:semicolon
DECL|variable|ccw_device_resume
id|EXPORT_SYMBOL
c_func
(paren
id|ccw_device_resume
)paren
suffix:semicolon
DECL|variable|ccw_device_start_timeout
id|EXPORT_SYMBOL
c_func
(paren
id|ccw_device_start_timeout
)paren
suffix:semicolon
DECL|variable|ccw_device_start
id|EXPORT_SYMBOL
c_func
(paren
id|ccw_device_start
)paren
suffix:semicolon
DECL|variable|ccw_device_get_ciw
id|EXPORT_SYMBOL
c_func
(paren
id|ccw_device_get_ciw
)paren
suffix:semicolon
DECL|variable|ccw_device_get_path_mask
id|EXPORT_SYMBOL
c_func
(paren
id|ccw_device_get_path_mask
)paren
suffix:semicolon
DECL|variable|read_conf_data
id|EXPORT_SYMBOL
c_func
(paren
id|read_conf_data
)paren
suffix:semicolon
DECL|variable|read_dev_chars
id|EXPORT_SYMBOL
c_func
(paren
id|read_dev_chars
)paren
suffix:semicolon
DECL|variable|_ccw_device_get_subchannel_number
id|EXPORT_SYMBOL
c_func
(paren
id|_ccw_device_get_subchannel_number
)paren
suffix:semicolon
DECL|variable|_ccw_device_get_device_number
id|EXPORT_SYMBOL
c_func
(paren
id|_ccw_device_get_device_number
)paren
suffix:semicolon
eof
