multiline_comment|/*&n; * drivers/s390/cio/device_id.c&n; *&n; *    Copyright (C) 2002 IBM Deutschland Entwicklung GmbH,&n; *&t;&t;&t; IBM Corporation&n; *    Author(s): Cornelia Huck(cohuck@de.ibm.com)&n; *&t;&t; Martin Schwidefsky (schwidefsky@de.ibm.com)&n; *&n; * Sense ID functions.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ccwdev.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/cio.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
macro_line|#include &quot;cio.h&quot;
macro_line|#include &quot;cio_debug.h&quot;
macro_line|#include &quot;css.h&quot;
macro_line|#include &quot;device.h&quot;
macro_line|#include &quot;ioasm.h&quot;
multiline_comment|/*&n; * diag210 is used under VM to get information about a virtual device&n; */
macro_line|#ifdef CONFIG_ARCH_S390X
r_int
DECL|function|diag210
id|diag210
c_func
(paren
r_struct
id|diag210
op_star
id|addr
)paren
(brace
multiline_comment|/*&n;&t; * diag 210 needs its data below the 2GB border, so we&n;&t; * use a static data area to be sure&n;&t; */
r_static
r_struct
id|diag210
id|diag210_tmp
suffix:semicolon
r_static
id|spinlock_t
id|diag210_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ccode
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|diag210_lock
comma
id|flags
)paren
suffix:semicolon
id|diag210_tmp
op_assign
op_star
id|addr
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;   lhi&t;  %0,-1&bslash;n&quot;
l_string|&quot;   sam31&bslash;n&quot;
l_string|&quot;   diag  %1,0,0x210&bslash;n&quot;
l_string|&quot;0: ipm&t;  %0&bslash;n&quot;
l_string|&quot;   srl&t;  %0,28&bslash;n&quot;
l_string|&quot;1: sam64&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;    .align 8&bslash;n&quot;
l_string|&quot;    .quad 0b,1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|__pa
c_func
(paren
op_amp
id|diag210_tmp
)paren
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
op_star
id|addr
op_assign
id|diag210_tmp
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|diag210_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
macro_line|#else
r_int
DECL|function|diag210
id|diag210
c_func
(paren
r_struct
id|diag210
op_star
id|addr
)paren
(brace
r_int
id|ccode
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;   lhi&t;  %0,-1&bslash;n&quot;
l_string|&quot;   diag  %1,0,0x210&bslash;n&quot;
l_string|&quot;0: ipm&t;  %0&bslash;n&quot;
l_string|&quot;   srl&t;  %0,28&bslash;n&quot;
l_string|&quot;1:&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;    .align 4&bslash;n&quot;
l_string|&quot;    .long 0b,1b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|ccode
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|__pa
c_func
(paren
id|addr
)paren
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|ccode
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Input :&n; *   devno - device number&n; *   ps&t;   - pointer to sense ID data area&n; * Output : none&n; */
r_static
r_void
DECL|function|VM_virtual_device_info
id|VM_virtual_device_info
(paren
id|__u16
id|devno
comma
r_struct
id|senseid
op_star
id|ps
)paren
(brace
r_static
r_struct
(brace
r_int
id|vrdcvcla
comma
id|vrdcvtyp
comma
id|cu_type
suffix:semicolon
)brace
id|vm_devices
(braket
)braket
op_assign
(brace
(brace
l_int|0x08
comma
l_int|0x01
comma
l_int|0x3480
)brace
comma
(brace
l_int|0x08
comma
l_int|0x02
comma
l_int|0x3430
)brace
comma
(brace
l_int|0x08
comma
l_int|0x10
comma
l_int|0x3420
)brace
comma
(brace
l_int|0x08
comma
l_int|0x42
comma
l_int|0x3424
)brace
comma
(brace
l_int|0x08
comma
l_int|0x44
comma
l_int|0x9348
)brace
comma
(brace
l_int|0x08
comma
l_int|0x81
comma
l_int|0x3490
)brace
comma
(brace
l_int|0x08
comma
l_int|0x82
comma
l_int|0x3422
)brace
comma
(brace
l_int|0x10
comma
l_int|0x41
comma
l_int|0x1403
)brace
comma
(brace
l_int|0x10
comma
l_int|0x42
comma
l_int|0x3211
)brace
comma
(brace
l_int|0x10
comma
l_int|0x43
comma
l_int|0x3203
)brace
comma
(brace
l_int|0x10
comma
l_int|0x45
comma
l_int|0x3800
)brace
comma
(brace
l_int|0x10
comma
l_int|0x47
comma
l_int|0x3262
)brace
comma
(brace
l_int|0x10
comma
l_int|0x48
comma
l_int|0x3820
)brace
comma
(brace
l_int|0x10
comma
l_int|0x49
comma
l_int|0x3800
)brace
comma
(brace
l_int|0x10
comma
l_int|0x4a
comma
l_int|0x4245
)brace
comma
(brace
l_int|0x10
comma
l_int|0x4b
comma
l_int|0x4248
)brace
comma
(brace
l_int|0x10
comma
l_int|0x4d
comma
l_int|0x3800
)brace
comma
(brace
l_int|0x10
comma
l_int|0x4e
comma
l_int|0x3820
)brace
comma
(brace
l_int|0x10
comma
l_int|0x4f
comma
l_int|0x3820
)brace
comma
(brace
l_int|0x10
comma
l_int|0x82
comma
l_int|0x2540
)brace
comma
(brace
l_int|0x10
comma
l_int|0x84
comma
l_int|0x3525
)brace
comma
(brace
l_int|0x20
comma
l_int|0x81
comma
l_int|0x2501
)brace
comma
(brace
l_int|0x20
comma
l_int|0x82
comma
l_int|0x2540
)brace
comma
(brace
l_int|0x20
comma
l_int|0x84
comma
l_int|0x3505
)brace
comma
(brace
l_int|0x40
comma
l_int|0x01
comma
l_int|0x3278
)brace
comma
(brace
l_int|0x40
comma
l_int|0x04
comma
l_int|0x3277
)brace
comma
(brace
l_int|0x40
comma
l_int|0x80
comma
l_int|0x2250
)brace
comma
(brace
l_int|0x40
comma
l_int|0xc0
comma
l_int|0x5080
)brace
comma
(brace
l_int|0x80
comma
l_int|0x00
comma
l_int|0x3215
)brace
comma
)brace
suffix:semicolon
r_struct
id|diag210
id|diag_data
suffix:semicolon
r_int
id|ccode
comma
id|i
suffix:semicolon
id|CIO_TRACE_EVENT
(paren
l_int|4
comma
l_string|&quot;VMvdinf&quot;
)paren
suffix:semicolon
id|diag_data
op_assign
(paren
r_struct
id|diag210
)paren
(brace
dot
id|vrdcdvno
op_assign
id|devno
comma
dot
id|vrdclen
op_assign
r_sizeof
(paren
id|diag_data
)paren
comma
)brace
suffix:semicolon
id|ccode
op_assign
id|diag210
(paren
op_amp
id|diag_data
)paren
suffix:semicolon
id|ps-&gt;reserved
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* Special case for bloody osa devices. */
r_if
c_cond
(paren
id|diag_data.vrdcvcla
op_eq
l_int|0x02
op_logical_and
id|diag_data.vrdcvtyp
op_eq
l_int|0x20
)paren
(brace
id|ps-&gt;cu_type
op_assign
l_int|0x3088
suffix:semicolon
id|ps-&gt;cu_model
op_assign
l_int|0x60
suffix:semicolon
r_return
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
r_sizeof
(paren
id|vm_devices
)paren
op_div
r_sizeof
(paren
id|vm_devices
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|diag_data.vrdcvcla
op_eq
id|vm_devices
(braket
id|i
)braket
dot
id|vrdcvcla
op_logical_and
id|diag_data.vrdcvtyp
op_eq
id|vm_devices
(braket
id|i
)braket
dot
id|vrdcvtyp
)paren
(brace
id|ps-&gt;cu_type
op_assign
id|vm_devices
(braket
id|i
)braket
dot
id|cu_type
suffix:semicolon
r_return
suffix:semicolon
)brace
id|CIO_MSG_EVENT
c_func
(paren
l_int|0
comma
l_string|&quot;DIAG X&squot;210&squot; for device %04X returned (cc = %d):&quot;
l_string|&quot;vdev class : %02X, vdev type : %04X &bslash;n ...  &quot;
l_string|&quot;rdev class : %02X, rdev type : %04X, &quot;
l_string|&quot;rdev model: %02X&bslash;n&quot;
comma
id|devno
comma
id|ccode
comma
id|diag_data.vrdcvcla
comma
id|diag_data.vrdcvtyp
comma
id|diag_data.vrdcrccl
comma
id|diag_data.vrdccrty
comma
id|diag_data.vrdccrmd
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Start Sense ID helper function.&n; * Try to obtain the &squot;control unit&squot;/&squot;device type&squot; information&n; *  associated with the subchannel.&n; */
r_static
r_int
DECL|function|__ccw_device_sense_id_start
id|__ccw_device_sense_id_start
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
multiline_comment|/* Setup sense channel program. */
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
id|sch-&gt;schib.pmcw.pim
op_ne
l_int|0x80
)paren
(brace
multiline_comment|/* more than one path installed. */
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
id|ccw-&gt;cmd_code
op_assign
id|CCW_CMD_SENSE_ID
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
id|senseid
)paren
suffix:semicolon
id|ccw-&gt;count
op_assign
r_sizeof
(paren
r_struct
id|senseid
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
r_if
c_cond
(paren
(paren
id|sch-&gt;opm
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|imask
)paren
op_ne
l_int|0
op_logical_and
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
DECL|function|ccw_device_sense_id_start
id|ccw_device_sense_id_start
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
id|memset
(paren
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|senseid
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|senseid
)paren
)paren
suffix:semicolon
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|senseid.cu_type
op_assign
l_int|0xFFFF
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
id|ret
op_assign
id|__ccw_device_sense_id_start
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
id|ccw_device_sense_id_done
c_func
(paren
id|cdev
comma
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Called from interrupt context to check if a valid answer&n; * to Sense ID was received.&n; */
r_static
r_int
DECL|function|ccw_device_check_sense_id
id|ccw_device_check_sense_id
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
multiline_comment|/* Did we get a proper answer ? */
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|senseid.cu_type
op_ne
l_int|0xFFFF
op_logical_and
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|senseid.reserved
op_eq
l_int|0xFF
)paren
(brace
r_if
c_cond
(paren
id|irb-&gt;scsw.count
OL
r_sizeof
(paren
r_struct
id|senseid
)paren
op_minus
l_int|8
)paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|flags.esid
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Success */
)brace
multiline_comment|/* Check the error cases. */
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
id|SNS0_CMD_REJECT
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * if the device doesn&squot;t support the SenseID&n;&t;&t; *  command further retries wouldn&squot;t help ...&n;&t;&t; * NB: We don&squot;t check here for intervention required like we&n;&t;&t; *     did before, because tape devices with no tape inserted&n;&t;&t; *     may present this status *in conjunction with* the&n;&t;&t; *     sense id information. So, for intervention required,&n;&t;&t; *     we use the &quot;whack it until it talks&quot; strategy...&n;&t;&t; */
id|CIO_MSG_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;SenseID : device %04x on Subchannel %04x &quot;
l_string|&quot;reports cmd reject&bslash;n&quot;
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|devno
comma
id|sch-&gt;irq
)paren
suffix:semicolon
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
l_string|&quot;SenseID : UC on dev %04x, &quot;
l_string|&quot;lpum %02X, cnt %02d, sns :&quot;
l_string|&quot; %02X%02X%02X%02X %02X%02X%02X%02X ...&bslash;n&quot;
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|devno
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
r_if
c_cond
(paren
(paren
id|sch-&gt;orb.lpm
op_amp
id|sch-&gt;schib.pmcw.pim
op_amp
id|sch-&gt;schib.pmcw.pam
)paren
op_ne
l_int|0
)paren
id|CIO_MSG_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;SenseID : path %02X for device %04x on&quot;
l_string|&quot; subchannel %04x is &squot;not operational&squot;&bslash;n&quot;
comma
id|sch-&gt;orb.lpm
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|devno
comma
id|sch-&gt;irq
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
multiline_comment|/* Hmm, whatever happened, try again. */
id|CIO_MSG_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;SenseID : start_IO() for device %04x on &quot;
l_string|&quot;subchannel %04x returns status %02X%02X&bslash;n&quot;
comma
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|devno
comma
id|sch-&gt;irq
comma
id|irb-&gt;scsw.dstat
comma
id|irb-&gt;scsw.cstat
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
multiline_comment|/*&n; * Got interrupt for Sense ID.&n; */
r_void
DECL|function|ccw_device_sense_id_irq
id|ccw_device_sense_id_irq
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
(paren
r_struct
id|irb
op_star
)paren
id|__LC_IRB
suffix:semicolon
multiline_comment|/*&n;&t; * Unsolicited interrupts may pertain to an earlier status pending or&n;&t; * busy condition on the subchannel. Retry sense id.&n;&t; */
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
id|__ccw_device_sense_id_start
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
id|ccw_device_sense_id_done
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
id|ret
op_assign
id|ccw_device_check_sense_id
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
multiline_comment|/* 0, -ETIME, -EOPNOTSUPP, -EAGAIN or -EACCES */
r_case
l_int|0
suffix:colon
multiline_comment|/* Sense id succeeded. */
r_case
op_minus
id|ETIME
suffix:colon
multiline_comment|/* Sense id stopped by timeout. */
id|ccw_device_sense_id_done
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
multiline_comment|/* fall through. */
r_case
op_minus
id|EAGAIN
suffix:colon
multiline_comment|/* try again. */
id|ret
op_assign
id|__ccw_device_sense_id_start
c_func
(paren
id|cdev
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
r_break
suffix:semicolon
multiline_comment|/* fall through. */
r_default
suffix:colon
(brace
)brace
multiline_comment|/* Sense ID failed. Try asking VM. */
r_if
c_cond
(paren
id|MACHINE_IS_VM
)paren
(brace
id|VM_virtual_device_info
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|devno
comma
op_amp
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|senseid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdev
op_member_access_from_pointer
r_private
op_member_access_from_pointer
id|senseid.cu_type
op_ne
l_int|0xFFFF
)paren
(brace
multiline_comment|/* Got the device information from VM. */
id|ccw_device_sense_id_done
c_func
(paren
id|cdev
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * If we can&squot;t couldn&squot;t identify the device type we&n;&t;&t; *  consider the device &quot;not operational&quot;.&n;&t;&t; */
id|ccw_device_sense_id_done
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
)brace
)brace
DECL|variable|diag210
id|EXPORT_SYMBOL
c_func
(paren
id|diag210
)paren
suffix:semicolon
eof
