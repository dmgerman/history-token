multiline_comment|/*&n; * drivers/s390/cio/device_pgid.c&n; *&n; *    Copyright (C) 2002 IBM Deutschland Entwicklung GmbH,&n; *&t;&t;&t; IBM Corporation&n; *    Author(s): Cornelia Huck(cohuck@de.ibm.com)&n; *&t;&t; Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; * Path Group ID functions.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ccwdev.h&gt;
macro_line|#include &lt;asm/cio.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
macro_line|#include &quot;cio.h&quot;
macro_line|#include &quot;cio_debug.h&quot;
macro_line|#include &quot;css.h&quot;
macro_line|#include &quot;device.h&quot;
multiline_comment|/*&n; * Start Sense Path Group ID helper function. Used in ccw_device_recog&n; * and ccw_device_sense_pgid.&n; */
r_static
r_int
DECL|function|__ccw_device_sense_pgid_start
id|__ccw_device_sense_pgid_start
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
r_struct
id|ccw1
op_star
id|ccw
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
multiline_comment|/* Setup sense path group id channel program. */
id|ccw
op_assign
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iccws
suffix:semicolon
id|ccw-&gt;cmd_code
op_assign
id|CCW_CMD_SENSE_PGID
suffix:semicolon
id|ccw-&gt;cda
op_assign
(paren
id|__u32
)paren
id|__pa
(paren
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|pgid
)paren
suffix:semicolon
id|ccw-&gt;count
op_assign
r_sizeof
(paren
r_struct
id|pgid
)paren
suffix:semicolon
id|ccw-&gt;flags
op_assign
id|CCW_FLAG_SLI
suffix:semicolon
multiline_comment|/* Reset device status. */
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
multiline_comment|/* Try on every path. */
id|ret
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_while
c_loop
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Try every path multiple times. */
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iretry
OG
l_int|0
)paren
(brace
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iretry
op_decrement
suffix:semicolon
id|ret
op_assign
id|cio_start
(paren
id|sch
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iccws
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
)paren
suffix:semicolon
multiline_comment|/* ret is 0, -EBUSY, -EACCES or -ENODEV */
r_if
c_cond
(paren
id|ret
op_ne
op_minus
id|EACCES
)paren
r_return
id|ret
suffix:semicolon
id|CIO_MSG_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;SNID - Device %s on Subchannel &quot;
l_string|&quot;%s, lpm %02X, became &squot;not &quot;
l_string|&quot;operational&squot;&bslash;n&quot;
comma
id|cdev-&gt;dev.bus_id
comma
id|sch-&gt;dev.bus_id
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
)paren
suffix:semicolon
)brace
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
op_rshift_assign
l_int|1
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iretry
op_assign
l_int|5
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_void
DECL|function|ccw_device_sense_pgid_start
id|ccw_device_sense_pgid_start
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
r_int
id|ret
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|state
op_assign
id|DEV_STATE_SENSE_PGID
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
op_assign
l_int|0x80
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iretry
op_assign
l_int|5
suffix:semicolon
id|memset
(paren
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|pgid
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pgid
)paren
)paren
suffix:semicolon
id|ret
op_assign
id|__ccw_device_sense_pgid_start
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_logical_and
id|ret
op_ne
op_minus
id|EBUSY
)paren
id|ccw_device_sense_pgid_done
c_func
(paren
id|cdev
comma
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Called from interrupt context to check if a valid answer&n; * to Sense Path Group ID was received.&n; */
r_static
r_int
DECL|function|__ccw_device_check_sense_pgid
id|__ccw_device_check_sense_pgid
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
r_struct
id|irb
op_star
id|irb
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
id|irb
op_assign
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|irb
suffix:semicolon
r_if
c_cond
(paren
id|irb-&gt;scsw.fctl
op_amp
(paren
id|SCSW_FCTL_HALT_FUNC
op_or
id|SCSW_FCTL_CLEAR_FUNC
)paren
)paren
r_return
op_minus
id|ETIME
suffix:semicolon
r_if
c_cond
(paren
id|irb-&gt;esw.esw0.erw.cons
op_logical_and
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
(brace
multiline_comment|/*&n;&t;&t; * If the device doesn&squot;t support the Sense Path Group ID&n;&t;&t; *  command further retries wouldn&squot;t help ...&n;&t;&t; */
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irb-&gt;esw.esw0.erw.cons
)paren
(brace
id|CIO_MSG_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;SNID - device %s, unit check, &quot;
l_string|&quot;lpum %02X, cnt %02d, sns : &quot;
l_string|&quot;%02X%02X%02X%02X %02X%02X%02X%02X ...&bslash;n&quot;
comma
id|cdev-&gt;dev.bus_id
comma
id|irb-&gt;esw.esw0.sublog.lpum
comma
id|irb-&gt;esw.esw0.erw.scnt
comma
id|irb-&gt;ecw
(braket
l_int|0
)braket
comma
id|irb-&gt;ecw
(braket
l_int|1
)braket
comma
id|irb-&gt;ecw
(braket
l_int|2
)braket
comma
id|irb-&gt;ecw
(braket
l_int|3
)braket
comma
id|irb-&gt;ecw
(braket
l_int|4
)braket
comma
id|irb-&gt;ecw
(braket
l_int|5
)braket
comma
id|irb-&gt;ecw
(braket
l_int|6
)braket
comma
id|irb-&gt;ecw
(braket
l_int|7
)braket
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irb-&gt;scsw.cc
op_eq
l_int|3
)paren
(brace
id|CIO_MSG_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;SNID - Device %s on Subchannel &quot;
l_string|&quot;%s, lpm %02X, became &squot;not operational&squot;&bslash;n&quot;
comma
id|cdev-&gt;dev.bus_id
comma
id|sch-&gt;dev.bus_id
comma
id|sch-&gt;orb.lpm
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|pgid.inf.ps.state2
op_eq
id|SNID_STATE2_RESVD_ELSE
)paren
(brace
id|CIO_MSG_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;SNID - Device %s on Subchannel %s &quot;
l_string|&quot;is reserved by someone else&bslash;n&quot;
comma
id|cdev-&gt;dev.bus_id
comma
id|sch-&gt;dev.bus_id
)paren
suffix:semicolon
r_return
op_minus
id|EUSERS
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Got interrupt for Sense Path Group ID.&n; */
r_void
DECL|function|ccw_device_sense_pgid_irq
id|ccw_device_sense_pgid_irq
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_enum
id|dev_event
id|dev_event
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_struct
id|irb
op_star
id|irb
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|irb
op_assign
(paren
r_struct
id|irb
op_star
)paren
id|__LC_IRB
suffix:semicolon
multiline_comment|/*&n;&t; * Unsolicited interrupts may pertain to an earlier status pending or&n;&t; * busy condition on the subchannel. Retry sense pgid.&n;&t; */
r_if
c_cond
(paren
id|irb-&gt;scsw.stctl
op_eq
(paren
id|SCSW_STCTL_STATUS_PEND
op_or
id|SCSW_STCTL_ALERT_STATUS
)paren
)paren
(brace
id|ret
op_assign
id|__ccw_device_sense_pgid_start
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_logical_and
id|ret
op_ne
op_minus
id|EBUSY
)paren
id|ccw_device_sense_pgid_done
c_func
(paren
id|cdev
comma
id|ret
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ccw_device_accumulate_and_sense
c_func
(paren
id|cdev
comma
id|irb
)paren
op_ne
l_int|0
)paren
r_return
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|__ccw_device_check_sense_pgid
c_func
(paren
id|cdev
)paren
)paren
(brace
multiline_comment|/* 0, -ETIME, -EOPNOTSUPP, -EAGAIN, -EACCES or -EUSERS */
r_case
l_int|0
suffix:colon
multiline_comment|/* Sense Path Group ID successful. */
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|pgid.inf.ps.state1
op_eq
id|SNID_STATE1_RESET
)paren
id|memcpy
c_func
(paren
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|pgid
comma
op_amp
id|global_pgid
comma
r_sizeof
(paren
r_struct
id|pgid
)paren
)paren
suffix:semicolon
id|ccw_device_sense_pgid_done
c_func
(paren
id|cdev
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|EOPNOTSUPP
suffix:colon
multiline_comment|/* Sense Path Group ID not supported */
id|ccw_device_sense_pgid_done
c_func
(paren
id|cdev
comma
op_minus
id|EOPNOTSUPP
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ETIME
suffix:colon
multiline_comment|/* Sense path group id stopped by timeout. */
id|ccw_device_sense_pgid_done
c_func
(paren
id|cdev
comma
op_minus
id|ETIME
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|EACCES
suffix:colon
multiline_comment|/* channel is not operational. */
id|sch-&gt;lpm
op_and_assign
op_complement
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
op_rshift_assign
l_int|1
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iretry
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* Fall through. */
r_case
op_minus
id|EAGAIN
suffix:colon
multiline_comment|/* Try again. */
id|ret
op_assign
id|__ccw_device_sense_pgid_start
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
op_logical_and
id|ret
op_ne
op_minus
id|EBUSY
)paren
id|ccw_device_sense_pgid_done
c_func
(paren
id|cdev
comma
op_minus
id|ENODEV
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|EUSERS
suffix:colon
multiline_comment|/* device is reserved for someone else. */
id|ccw_device_sense_pgid_done
c_func
(paren
id|cdev
comma
op_minus
id|EUSERS
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Path Group ID helper function.&n; */
r_static
r_int
DECL|function|__ccw_device_do_pgid
id|__ccw_device_do_pgid
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
id|__u8
id|func
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_struct
id|ccw1
op_star
id|ccw
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
multiline_comment|/* Setup sense path group id channel program. */
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|pgid.inf.fc
op_assign
id|func
suffix:semicolon
id|ccw
op_assign
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iccws
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|flags.pgid_single
)paren
(brace
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|pgid.inf.fc
op_or_assign
id|SPID_FUNC_MULTI_PATH
suffix:semicolon
id|ccw-&gt;cmd_code
op_assign
id|CCW_CMD_SUSPEND_RECONN
suffix:semicolon
id|ccw-&gt;cda
op_assign
l_int|0
suffix:semicolon
id|ccw-&gt;count
op_assign
l_int|0
suffix:semicolon
id|ccw-&gt;flags
op_assign
id|CCW_FLAG_SLI
op_or
id|CCW_FLAG_CC
suffix:semicolon
id|ccw
op_increment
suffix:semicolon
)brace
r_else
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|pgid.inf.fc
op_or_assign
id|SPID_FUNC_SINGLE_PATH
suffix:semicolon
id|ccw-&gt;cmd_code
op_assign
id|CCW_CMD_SET_PGID
suffix:semicolon
id|ccw-&gt;cda
op_assign
(paren
id|__u32
)paren
id|__pa
(paren
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|pgid
)paren
suffix:semicolon
id|ccw-&gt;count
op_assign
r_sizeof
(paren
r_struct
id|pgid
)paren
suffix:semicolon
id|ccw-&gt;flags
op_assign
id|CCW_FLAG_SLI
suffix:semicolon
multiline_comment|/* Reset device status. */
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
multiline_comment|/* Try multiple times. */
id|ret
op_assign
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
id|iretry
OG
l_int|0
)paren
(brace
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iretry
op_decrement
suffix:semicolon
id|ret
op_assign
id|cio_start
(paren
id|sch
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iccws
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
)paren
suffix:semicolon
multiline_comment|/* ret is 0, -EBUSY, -EACCES or -ENODEV */
r_if
c_cond
(paren
id|ret
op_ne
op_minus
id|EACCES
)paren
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* PGID command failed on this path. Switch it off. */
id|sch-&gt;lpm
op_and_assign
op_complement
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
suffix:semicolon
id|sch-&gt;vpm
op_and_assign
op_complement
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
suffix:semicolon
id|CIO_MSG_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;SPID - Device %s on Subchannel &quot;
l_string|&quot;%s, lpm %02X, became &squot;not operational&squot;&bslash;n&quot;
comma
id|cdev-&gt;dev.bus_id
comma
id|sch-&gt;dev.bus_id
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Called from interrupt context to check if a valid answer&n; * to Set Path Group ID was received.&n; */
r_static
r_int
DECL|function|__ccw_device_check_pgid
id|__ccw_device_check_pgid
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
r_struct
id|irb
op_star
id|irb
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
id|irb
op_assign
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|irb
suffix:semicolon
r_if
c_cond
(paren
id|irb-&gt;scsw.fctl
op_amp
(paren
id|SCSW_FCTL_HALT_FUNC
op_or
id|SCSW_FCTL_CLEAR_FUNC
)paren
)paren
r_return
op_minus
id|ETIME
suffix:semicolon
r_if
c_cond
(paren
id|irb-&gt;esw.esw0.erw.cons
)paren
(brace
r_if
c_cond
(paren
id|irb-&gt;ecw
(braket
l_int|0
)braket
op_amp
id|SNS0_CMD_REJECT
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
multiline_comment|/* Hmm, whatever happened, try again. */
id|CIO_MSG_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;SPID - device %s, unit check, cnt %02d, &quot;
l_string|&quot;sns : %02X%02X%02X%02X %02X%02X%02X%02X ...&bslash;n&quot;
comma
id|cdev-&gt;dev.bus_id
comma
id|irb-&gt;esw.esw0.erw.scnt
comma
id|irb-&gt;ecw
(braket
l_int|0
)braket
comma
id|irb-&gt;ecw
(braket
l_int|1
)braket
comma
id|irb-&gt;ecw
(braket
l_int|2
)braket
comma
id|irb-&gt;ecw
(braket
l_int|3
)braket
comma
id|irb-&gt;ecw
(braket
l_int|4
)braket
comma
id|irb-&gt;ecw
(braket
l_int|5
)braket
comma
id|irb-&gt;ecw
(braket
l_int|6
)braket
comma
id|irb-&gt;ecw
(braket
l_int|7
)braket
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irb-&gt;scsw.cc
op_eq
l_int|3
)paren
(brace
id|CIO_MSG_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;SPID - Device %s on Subchannel &quot;
l_string|&quot;%s, lpm %02X, became &squot;not operational&squot;&bslash;n&quot;
comma
id|cdev-&gt;dev.bus_id
comma
id|sch-&gt;dev.bus_id
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|__ccw_device_verify_start
id|__ccw_device_verify_start
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
id|__u8
id|imask
comma
id|func
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sch-&gt;vpm
op_ne
id|sch-&gt;lpm
)paren
(brace
multiline_comment|/* Find first unequal bit in vpm vs. lpm */
r_for
c_loop
(paren
id|imask
op_assign
l_int|0x80
suffix:semicolon
id|imask
op_ne
l_int|0
suffix:semicolon
id|imask
op_rshift_assign
l_int|1
)paren
r_if
c_cond
(paren
(paren
id|sch-&gt;vpm
op_amp
id|imask
)paren
op_ne
(paren
id|sch-&gt;lpm
op_amp
id|imask
)paren
)paren
r_break
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
op_assign
id|imask
suffix:semicolon
id|func
op_assign
(paren
id|sch-&gt;vpm
op_amp
id|imask
)paren
ques
c_cond
id|SPID_FUNC_RESIGN
suffix:colon
id|SPID_FUNC_ESTABLISH
suffix:semicolon
id|ret
op_assign
id|__ccw_device_do_pgid
c_func
(paren
id|cdev
comma
id|func
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
op_logical_or
id|ret
op_eq
op_minus
id|EBUSY
)paren
r_return
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iretry
op_assign
l_int|5
suffix:semicolon
)brace
id|ccw_device_verify_done
c_func
(paren
id|cdev
comma
(paren
id|sch-&gt;lpm
op_ne
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Got interrupt for Set Path Group ID.&n; */
r_void
DECL|function|ccw_device_verify_irq
id|ccw_device_verify_irq
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_enum
id|dev_event
id|dev_event
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_struct
id|irb
op_star
id|irb
suffix:semicolon
id|irb
op_assign
(paren
r_struct
id|irb
op_star
)paren
id|__LC_IRB
suffix:semicolon
multiline_comment|/*&n;&t; * Unsolicited interrupts may pertain to an earlier status pending or&n;&t; * busy condition on the subchannel. Restart path verification.&n;&t; */
r_if
c_cond
(paren
id|irb-&gt;scsw.stctl
op_eq
(paren
id|SCSW_STCTL_STATUS_PEND
op_or
id|SCSW_STCTL_ALERT_STATUS
)paren
)paren
(brace
id|__ccw_device_verify_start
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ccw_device_accumulate_and_sense
c_func
(paren
id|cdev
comma
id|irb
)paren
op_ne
l_int|0
)paren
r_return
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|__ccw_device_check_pgid
c_func
(paren
id|cdev
)paren
)paren
(brace
multiline_comment|/* 0, -ETIME, -EAGAIN, -EOPNOTSUPP or -EACCES */
r_case
l_int|0
suffix:colon
multiline_comment|/* Establish or Resign Path Group done. Update vpm. */
r_if
c_cond
(paren
(paren
id|sch-&gt;lpm
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
)paren
op_ne
l_int|0
)paren
id|sch-&gt;vpm
op_or_assign
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
suffix:semicolon
r_else
id|sch-&gt;vpm
op_and_assign
op_complement
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iretry
op_assign
l_int|5
suffix:semicolon
id|__ccw_device_verify_start
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|EOPNOTSUPP
suffix:colon
multiline_comment|/*&n;&t;&t; * One of those strange devices which claim to be able&n;&t;&t; * to do multipathing but not for Set Path Group ID.&n;&t;&t; */
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|flags.pgid_single
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* fall through. */
r_case
op_minus
id|EAGAIN
suffix:colon
multiline_comment|/* Try again. */
id|__ccw_device_verify_start
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ETIME
suffix:colon
multiline_comment|/* Set path group id stopped by timeout. */
id|ccw_device_verify_done
c_func
(paren
id|cdev
comma
op_minus
id|ETIME
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|EACCES
suffix:colon
multiline_comment|/* channel is not operational. */
id|sch-&gt;lpm
op_and_assign
op_complement
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
suffix:semicolon
id|sch-&gt;vpm
op_and_assign
op_complement
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iretry
op_assign
l_int|5
suffix:semicolon
id|__ccw_device_verify_start
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_void
DECL|function|ccw_device_verify_start
id|ccw_device_verify_start
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|flags.pgid_single
op_assign
l_int|0
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iretry
op_assign
l_int|5
suffix:semicolon
id|__ccw_device_verify_start
c_func
(paren
id|cdev
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|__ccw_device_disband_start
id|__ccw_device_disband_start
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
id|ret
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
r_while
c_loop
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|sch-&gt;lpm
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
)paren
(brace
id|ret
op_assign
id|__ccw_device_do_pgid
c_func
(paren
id|cdev
comma
id|SPID_FUNC_DISBAND
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
r_return
suffix:semicolon
)brace
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iretry
op_assign
l_int|5
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|ccw_device_verify_done
c_func
(paren
id|cdev
comma
(paren
id|sch-&gt;lpm
op_ne
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Got interrupt for Unset Path Group ID.&n; */
r_void
DECL|function|ccw_device_disband_irq
id|ccw_device_disband_irq
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
comma
r_enum
id|dev_event
id|dev_event
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_struct
id|irb
op_star
id|irb
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|irb
op_assign
(paren
r_struct
id|irb
op_star
)paren
id|__LC_IRB
suffix:semicolon
multiline_comment|/* Ignore unsolicited interrupts. */
r_if
c_cond
(paren
id|irb-&gt;scsw.stctl
op_eq
(paren
id|SCSW_STCTL_STATUS_PEND
op_or
id|SCSW_STCTL_ALERT_STATUS
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ccw_device_accumulate_and_sense
c_func
(paren
id|cdev
comma
id|irb
)paren
op_ne
l_int|0
)paren
r_return
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|cdev-&gt;dev.parent
)paren
suffix:semicolon
id|ret
op_assign
id|__ccw_device_check_pgid
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|ret
)paren
(brace
multiline_comment|/* 0, -ETIME, -EAGAIN, -EOPNOTSUPP or -EACCES */
r_case
l_int|0
suffix:colon
multiline_comment|/* disband successful. */
id|sch-&gt;vpm
op_assign
l_int|0
suffix:semicolon
id|ccw_device_disband_done
c_func
(paren
id|cdev
comma
id|ret
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|EOPNOTSUPP
suffix:colon
multiline_comment|/*&n;&t;&t; * One of those strange devices which claim to be able&n;&t;&t; * to do multipathing but not for Unset Path Group ID.&n;&t;&t; */
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|flags.pgid_single
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* fall through. */
r_case
op_minus
id|EAGAIN
suffix:colon
multiline_comment|/* Try again. */
id|__ccw_device_disband_start
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ETIME
suffix:colon
multiline_comment|/* Set path group id stopped by timeout. */
id|ccw_device_disband_done
c_func
(paren
id|cdev
comma
op_minus
id|ETIME
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|EACCES
suffix:colon
multiline_comment|/* channel is not operational. */
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
op_rshift_assign
l_int|1
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iretry
op_assign
l_int|5
suffix:semicolon
id|__ccw_device_disband_start
c_func
(paren
id|cdev
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_void
DECL|function|ccw_device_disband_start
id|ccw_device_disband_start
c_func
(paren
r_struct
id|ccw_device
op_star
id|cdev
)paren
(brace
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|flags.pgid_single
op_assign
l_int|0
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|iretry
op_assign
l_int|5
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
op_assign
l_int|0x80
suffix:semicolon
id|__ccw_device_disband_start
c_func
(paren
id|cdev
)paren
suffix:semicolon
)brace
eof
