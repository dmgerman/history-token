multiline_comment|/*&n; *  drivers/s390/cio/chsc.c&n; *   S/390 common I/O routines -- channel subsystem call&n; *   $Revision: 1.46 $&n; *&n; *    Copyright (C) 1999-2002 IBM Deutschland Entwicklung GmbH,&n; *&t;&t;&t;      IBM Corporation&n; *    Author(s): Ingo Adlung (adlung@de.ibm.com)&n; *&t;&t; Cornelia Huck (cohuck@de.ibm.com)&n; *&t;&t; Arnd Bergmann (arndb@de.ibm.com)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/cio.h&gt;
macro_line|#include &lt;asm/ccwdev.h&gt; 
singleline_comment|// FIXME: layering violation, remove this
macro_line|#include &quot;css.h&quot;
macro_line|#include &quot;cio.h&quot;
macro_line|#include &quot;cio_debug.h&quot;
macro_line|#include &quot;device.h&quot; 
singleline_comment|// FIXME: layering violation, remove this
macro_line|#include &quot;ioasm.h&quot;
macro_line|#include &quot;chsc.h&quot;
DECL|macro|CHPID_LONGS
mdefine_line|#define CHPID_LONGS (256 / (8 * sizeof(long))) /* 256 chpids */
DECL|variable|chpids
r_static
r_int
r_int
id|chpids
(braket
id|CHPID_LONGS
)braket
suffix:semicolon
DECL|variable|chpids_logical
r_static
r_int
r_int
id|chpids_logical
(braket
id|CHPID_LONGS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|CHPID_LONGS
op_minus
l_int|1
)braket
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|chpids_known
r_static
r_int
r_int
id|chpids_known
(braket
id|CHPID_LONGS
)braket
suffix:semicolon
DECL|variable|chps
r_static
r_struct
id|channel_path
op_star
id|chps
(braket
id|NR_CHPIDS
)braket
suffix:semicolon
DECL|variable|cio_chsc_desc_avail
r_static
r_int
id|cio_chsc_desc_avail
suffix:semicolon
r_static
r_int
id|new_channel_path
c_func
(paren
r_int
id|chpid
comma
r_int
id|status
)paren
suffix:semicolon
r_static
r_int
DECL|function|set_chp_status
id|set_chp_status
c_func
(paren
r_int
id|chp
comma
r_int
id|status
)paren
(brace
r_if
c_cond
(paren
id|chps
(braket
id|chp
)braket
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|chps
(braket
id|chp
)braket
op_member_access_from_pointer
id|state
op_assign
id|status
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|chsc_chpid_logical
id|chsc_chpid_logical
(paren
r_struct
id|subchannel
op_star
id|sch
comma
r_int
id|chp
)paren
(brace
r_return
id|test_bit
(paren
id|sch-&gt;schib.pmcw.chpid
(braket
id|chp
)braket
comma
id|chpids_logical
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|chsc_clear_chpid
id|chsc_clear_chpid
c_func
(paren
r_struct
id|subchannel
op_star
id|sch
comma
r_int
id|chp
)paren
(brace
id|clear_bit
c_func
(paren
id|sch-&gt;schib.pmcw.chpid
(braket
id|chp
)braket
comma
id|chpids
)paren
suffix:semicolon
)brace
r_void
DECL|function|chsc_validate_chpids
id|chsc_validate_chpids
c_func
(paren
r_struct
id|subchannel
op_star
id|sch
)paren
(brace
r_int
id|mask
comma
id|chp
suffix:semicolon
r_if
c_cond
(paren
id|sch-&gt;lpm
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|chp
op_assign
l_int|0
suffix:semicolon
id|chp
op_le
l_int|7
suffix:semicolon
id|chp
op_increment
)paren
(brace
id|mask
op_assign
l_int|0x80
op_rshift
id|chp
suffix:semicolon
r_if
c_cond
(paren
id|sch-&gt;lpm
op_amp
id|mask
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|chsc_chpid_logical
c_func
(paren
id|sch
comma
id|chp
)paren
)paren
multiline_comment|/* disable using this path */
id|sch-&gt;lpm
op_and_assign
op_complement
id|mask
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* This chpid is not&n;&t;&t;&t; * available to us */
id|chsc_clear_chpid
c_func
(paren
id|sch
comma
id|chp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|chp
comma
id|chpids_known
)paren
)paren
id|set_chp_status
c_func
(paren
id|chp
comma
id|CHP_STANDBY
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* FIXME: this is _always_ called for every subchannel. shouldn&squot;t we&n; *&t;  process more than one at a time?*/
r_static
r_int
DECL|function|chsc_get_sch_desc_irq
id|chsc_get_sch_desc_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|ccode
comma
id|chpid
comma
id|j
suffix:semicolon
multiline_comment|/* FIXME: chsc_area_sei cannot be on the stack since it needs to&n;&t; * be page-aligned. Implement proper locking or dynamic&n;&t; * allocation or prove that this function does not have to be&n;&t; * reentrant! */
r_static
r_struct
id|ssd_area
id|chsc_area_ssd
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
id|PAGE_SIZE
)paren
)paren
)paren
suffix:semicolon
id|typeof
(paren
id|chsc_area_ssd.response_block
)paren
op_star
id|ssd_res
op_assign
op_amp
id|chsc_area_ssd.response_block
suffix:semicolon
id|chsc_area_ssd
op_assign
(paren
r_struct
id|ssd_area
)paren
(brace
dot
id|request_block
op_assign
(brace
dot
id|command_code1
op_assign
l_int|0x0010
comma
dot
id|command_code2
op_assign
l_int|0x0004
comma
dot
id|f_sch
op_assign
id|irq
comma
dot
id|l_sch
op_assign
id|irq
comma
)brace
)brace
suffix:semicolon
id|ccode
op_assign
id|chsc
c_func
(paren
op_amp
id|chsc_area_ssd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccode
OG
l_int|0
)paren
(brace
id|pr_debug
c_func
(paren
l_string|&quot;chsc returned with ccode = %d&bslash;n&quot;
comma
id|ccode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccode
op_eq
l_int|3
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|chsc_area_ssd.response_block.response_code
)paren
(brace
r_case
l_int|0x0001
suffix:colon
multiline_comment|/* everything ok */
r_break
suffix:semicolon
r_case
l_int|0x0002
suffix:colon
id|CIO_CRW_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;Invalid command!&bslash;n&quot;
)paren
suffix:semicolon
r_case
l_int|0x0003
suffix:colon
id|CIO_CRW_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;Error in chsc request block!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
l_int|0x0004
suffix:colon
id|CIO_CRW_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;Model does not provide ssd&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_default
suffix:colon
id|CIO_CRW_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;Unknown CHSC response %d&bslash;n&quot;
comma
id|chsc_area_ssd.response_block.response_code
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * ssd_res-&gt;st stores the type of the detected&n;&t; * subchannel, with the following definitions:&n;&t; *&n;&t; * 0: I/O subchannel:&t;  All fields have meaning&n;&t; * 1: CHSC subchannel:&t;  Only sch_val, st and sch&n;&t; *&t;&t;&t;  have meaning&n;&t; * 2: Message subchannel: All fields except unit_addr&n;&t; *&t;&t;&t;  have meaning&n;&t; * 3: ADM subchannel:&t;  Only sch_val, st and sch&n;&t; *&t;&t;&t;  have meaning&n;&t; *&n;&t; * Other types are currently undefined.&n;&t; */
r_if
c_cond
(paren
id|ssd_res-&gt;st
OG
l_int|3
)paren
(brace
multiline_comment|/* uhm, that looks strange... */
id|CIO_CRW_EVENT
c_func
(paren
l_int|0
comma
l_string|&quot;Strange subchannel type %d&quot;
l_string|&quot; for sch %x&bslash;n&quot;
comma
id|ssd_res-&gt;st
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * There may have been a new subchannel type defined in the&n;&t;&t; * time since this code was written; since we don&squot;t know which&n;&t;&t; * fields have meaning and what to do with it we just jump out&n;&t;&t; */
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_const
r_char
id|type
(braket
l_int|4
)braket
(braket
l_int|8
)braket
op_assign
(brace
l_string|&quot;I/O&quot;
comma
l_string|&quot;chsc&quot;
comma
l_string|&quot;message&quot;
comma
l_string|&quot;ADM&quot;
)brace
suffix:semicolon
id|CIO_CRW_EVENT
c_func
(paren
l_int|6
comma
l_string|&quot;ssd: sch %x is %s subchannel&bslash;n&quot;
comma
id|irq
comma
id|type
(braket
id|ssd_res-&gt;st
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ioinfo
(braket
id|irq
)braket
op_eq
l_int|NULL
)paren
multiline_comment|/* FIXME: we should do device rec. here... */
r_return
l_int|0
suffix:semicolon
id|ioinfo
(braket
id|irq
)braket
op_member_access_from_pointer
id|ssd_info.valid
op_assign
l_int|1
suffix:semicolon
id|ioinfo
(braket
id|irq
)braket
op_member_access_from_pointer
id|ssd_info.type
op_assign
id|ssd_res-&gt;st
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ssd_res-&gt;st
op_eq
l_int|0
op_logical_or
id|ssd_res-&gt;st
op_eq
l_int|2
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|8
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
l_int|0x80
op_rshift
id|j
)paren
op_amp
id|ssd_res-&gt;path_mask
op_amp
id|ssd_res-&gt;fla_valid_mask
)paren
)paren
r_continue
suffix:semicolon
id|chpid
op_assign
id|ssd_res-&gt;chpid
(braket
id|j
)braket
suffix:semicolon
r_if
c_cond
(paren
id|chpid
op_logical_and
(paren
op_logical_neg
id|test_and_set_bit
(paren
id|chpid
comma
id|chpids_known
)paren
)paren
op_logical_and
(paren
id|test_bit
(paren
id|chpid
comma
id|chpids_logical
)paren
)paren
)paren
id|set_bit
(paren
id|chpid
comma
id|chpids
)paren
suffix:semicolon
id|ioinfo
(braket
id|irq
)braket
op_member_access_from_pointer
id|ssd_info.chpid
(braket
id|j
)braket
op_assign
id|chpid
suffix:semicolon
id|ioinfo
(braket
id|irq
)braket
op_member_access_from_pointer
id|ssd_info.fla
(braket
id|j
)braket
op_assign
id|ssd_res-&gt;fla
(braket
id|j
)braket
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|chsc_get_sch_descriptions
id|chsc_get_sch_descriptions
c_func
(paren
r_void
)paren
(brace
r_int
id|irq
suffix:semicolon
r_int
id|err
suffix:semicolon
id|CIO_TRACE_EVENT
c_func
(paren
l_int|4
comma
l_string|&quot;gsdesc&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * get information about chpids and link addresses&n;&t; * by executing the chsc command &squot;store subchannel description&squot;&n;&t; */
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
op_le
id|highest_subchannel
suffix:semicolon
id|irq
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t; * retrieve information for each sch&n;&t;&t; */
id|err
op_assign
id|chsc_get_sch_desc_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_static
r_int
id|cio_chsc_err_msg
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cio_chsc_err_msg
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;chsc_get_sch_descriptions:&quot;
l_string|&quot; Error %d while doing chsc; &quot;
l_string|&quot;processing some machine checks may &quot;
l_string|&quot;not work&bslash;n&quot;
comma
id|err
)paren
suffix:semicolon
id|cio_chsc_err_msg
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
)brace
id|cio_chsc_desc_avail
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|chsc_get_sch_descriptions
id|__initcall
c_func
(paren
id|chsc_get_sch_descriptions
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|s390_subchannel_remove_chpid
id|s390_subchannel_remove_chpid
c_func
(paren
r_struct
id|subchannel
op_star
id|sch
comma
id|__u8
id|chpid
)paren
(brace
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|8
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|sch-&gt;schib.pmcw.chpid
(braket
id|j
)braket
op_eq
id|chpid
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|j
op_ge
l_int|8
)paren
r_return
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
id|chsc_validate_chpids
c_func
(paren
id|sch
)paren
suffix:semicolon
multiline_comment|/* just to be sure... */
id|sch-&gt;lpm
op_and_assign
op_complement
(paren
l_int|0x80
op_rshift
id|j
)paren
suffix:semicolon
multiline_comment|/* trigger path verification. */
id|dev_fsm_event
c_func
(paren
id|sch-&gt;dev.driver_data
comma
id|DEV_EVENT_VERIFY
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* FIXME: don&squot;t iterate all subchannels but use driver_for_each_dev */
r_static
r_inline
r_void
DECL|function|s390_set_chpid_offline
id|s390_set_chpid_offline
c_func
(paren
id|__u8
id|chpid
)paren
(brace
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
id|irq
suffix:semicolon
id|sprintf
c_func
(paren
id|dbf_txt
comma
l_string|&quot;chpr%x&quot;
comma
id|chpid
)paren
suffix:semicolon
id|CIO_TRACE_EVENT
c_func
(paren
l_int|2
comma
id|dbf_txt
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * TODO: the chpid may be not the chpid with the link incident,&n;&t; * but the chpid the report came in through. How to handle???&n;&t; */
id|clear_bit
c_func
(paren
id|chpid
comma
id|chpids
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_and_clear_bit
c_func
(paren
id|chpid
comma
id|chpids_known
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* we didn&squot;t know the chpid anyway */
id|set_chp_status
c_func
(paren
id|chpid
comma
id|CHP_OFFLINE
)paren
suffix:semicolon
macro_line|#if 0
id|driver_for_each_dev
c_func
(paren
id|io_subchannel_driver
comma
id|chpid
comma
id|s390_subchannel_remove_chpid
)paren
suffix:semicolon
macro_line|#else
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
op_le
id|highest_subchannel
suffix:semicolon
id|irq
op_increment
)paren
(brace
id|sch
op_assign
id|ioinfo
(braket
id|irq
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sch
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
multiline_comment|/* we don&squot;t know the device anyway */
id|s390_subchannel_remove_chpid
c_func
(paren
id|sch
comma
id|chpid
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_static
r_int
DECL|function|s390_process_res_acc_sch
id|s390_process_res_acc_sch
c_func
(paren
id|u8
id|chpid
comma
id|__u16
id|fla
comma
id|u32
id|fla_mask
comma
r_struct
id|subchannel
op_star
id|sch
)paren
(brace
r_int
id|found
suffix:semicolon
r_int
id|chp
suffix:semicolon
r_int
id|ccode
suffix:semicolon
multiline_comment|/* Update our ssd_info */
r_if
c_cond
(paren
id|chsc_get_sch_desc_irq
c_func
(paren
id|sch-&gt;irq
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|found
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|chp
op_assign
l_int|0
suffix:semicolon
id|chp
op_le
l_int|7
suffix:semicolon
id|chp
op_increment
)paren
multiline_comment|/*&n;&t;&t; * check if chpid is in information updated by ssd&n;&t;&t; */
r_if
c_cond
(paren
id|sch-&gt;ssd_info.valid
op_logical_and
id|sch-&gt;ssd_info.chpid
(braket
id|chp
)braket
op_eq
id|chpid
op_logical_and
(paren
id|sch-&gt;ssd_info.fla
(braket
id|chp
)braket
op_amp
id|fla_mask
)paren
op_eq
id|fla
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Do a stsch to update our subchannel structure with the&n;&t; * new path information and eventually check for logically&n;&t; * offline chpids.&n;&t; */
id|ccode
op_assign
id|stsch
c_func
(paren
id|sch-&gt;irq
comma
op_amp
id|sch-&gt;schib
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccode
OG
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|0x80
op_rshift
id|chp
suffix:semicolon
)brace
r_static
r_void
DECL|function|s390_process_res_acc
id|s390_process_res_acc
(paren
id|u8
id|chpid
comma
id|__u16
id|fla
comma
id|u32
id|fla_mask
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_int
id|irq
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_char
id|dbf_txt
(braket
l_int|15
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|dbf_txt
comma
l_string|&quot;accpr%x&quot;
comma
id|chpid
)paren
suffix:semicolon
id|CIO_TRACE_EVENT
c_func
(paren
l_int|2
comma
id|dbf_txt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fla
op_ne
l_int|0
)paren
(brace
id|sprintf
c_func
(paren
id|dbf_txt
comma
l_string|&quot;fla%x&quot;
comma
id|fla
)paren
suffix:semicolon
id|CIO_TRACE_EVENT
c_func
(paren
l_int|2
comma
id|dbf_txt
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * I/O resources may have become accessible.&n;&t; * Scan through all subchannels that may be concerned and&n;&t; * do a validation on those.&n;&t; * The more information we have (info), the less scanning&n;&t; * will we have to do.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|cio_chsc_desc_avail
)paren
id|chsc_get_sch_descriptions
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cio_chsc_desc_avail
)paren
(brace
multiline_comment|/*&n;&t;&t; * Something went wrong...&n;&t;&t; */
id|CIO_CRW_EVENT
c_func
(paren
l_int|0
comma
l_string|&quot;Error: Could not retrieve &quot;
l_string|&quot;subchannel descriptions, will not process css&quot;
l_string|&quot;machine check...&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|chpid
comma
id|chpids_logical
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* no need to do the rest */
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
op_le
id|__MAX_SUBCHANNELS
suffix:semicolon
id|irq
op_increment
)paren
(brace
r_int
id|chp_mask
suffix:semicolon
id|sch
op_assign
id|ioinfo
(braket
id|irq
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sch
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * We don&squot;t know the device yet, but since a path&n;&t;&t;&t; * may be available now to the device we&squot;ll have&n;&t;&t;&t; * to do recognition again.&n;&t;&t;&t; * Since we don&squot;t have any idea about which chpid&n;&t;&t;&t; * that beast may be on we&squot;ll have to do a stsch&n;&t;&t;&t; * on all devices, grr...&n;&t;&t;&t; */
id|ret
op_assign
id|css_probe_device
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ENXIO
)paren
multiline_comment|/* We&squot;re through */
r_return
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|spin_lock_irq
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
id|chp_mask
op_assign
id|s390_process_res_acc_sch
c_func
(paren
id|chpid
comma
id|fla
comma
id|fla_mask
comma
id|sch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chp_mask
op_eq
l_int|0
)paren
(brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fla_mask
op_ne
l_int|0
)paren
r_break
suffix:semicolon
r_else
r_continue
suffix:semicolon
)brace
id|sch-&gt;lpm
op_assign
(paren
id|sch-&gt;schib.pmcw.pim
op_amp
id|sch-&gt;schib.pmcw.pam
op_amp
id|sch-&gt;schib.pmcw.pom
)paren
op_or
id|chp_mask
suffix:semicolon
id|chsc_validate_chpids
c_func
(paren
id|sch
)paren
suffix:semicolon
id|dev_fsm_event
c_func
(paren
id|sch-&gt;dev.driver_data
comma
id|DEV_EVENT_VERIFY
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|sch-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fla_mask
op_ne
l_int|0
)paren
r_break
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|do_process_crw
id|do_process_crw
c_func
(paren
r_void
op_star
id|ignore
)paren
(brace
r_int
id|ccode
suffix:semicolon
multiline_comment|/*&n;&t; * build the chsc request block for store event information&n;&t; * and do the call&n;&t; */
multiline_comment|/* FIXME: chsc_area_sei cannot be on the stack since it needs to&n;&t; * be page-aligned. Implement proper locking or dynamic&n;&t; * allocation or prove that this function does not have to be&n;&t; * reentrant! */
r_static
r_struct
id|sei_area
id|chsc_area_sei
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
id|PAGE_SIZE
)paren
)paren
)paren
op_assign
(brace
dot
id|request_block
op_assign
(brace
dot
id|command_code1
op_assign
l_int|0x0010
comma
dot
id|command_code2
op_assign
l_int|0x000e
)brace
)brace
suffix:semicolon
id|typeof
(paren
id|chsc_area_sei.response_block
)paren
op_star
id|sei_res
op_assign
op_amp
id|chsc_area_sei.response_block
suffix:semicolon
id|CIO_TRACE_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;prcss&quot;
)paren
suffix:semicolon
id|ccode
op_assign
id|chsc
c_func
(paren
op_amp
id|chsc_area_sei
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccode
OG
l_int|0
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|chsc_area_sei.response_block.response_code
)paren
(brace
multiline_comment|/* for debug purposes, check for problems */
r_case
l_int|0x0001
suffix:colon
r_break
suffix:semicolon
multiline_comment|/* everything ok */
r_case
l_int|0x0002
suffix:colon
id|CIO_CRW_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;chsc_process_crw:invalid command!&bslash;n&quot;
)paren
suffix:semicolon
r_case
l_int|0x0003
suffix:colon
id|CIO_CRW_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;chsc_process_crw: error in chsc &quot;
l_string|&quot;request block!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|0x0005
suffix:colon
id|CIO_CRW_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;chsc_process_crw: no event information &quot;
l_string|&quot;stored&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
r_default
suffix:colon
id|CIO_CRW_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;chsc_process_crw: chsc response %d&bslash;n&quot;
comma
id|chsc_area_sei.response_block.response_code
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|CIO_CRW_EVENT
c_func
(paren
l_int|4
comma
l_string|&quot;chsc_process_crw: event information successfully &quot;
l_string|&quot;stored&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sei_res-&gt;rs
op_ne
l_int|4
)paren
(brace
id|CIO_CRW_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;chsc_process_crw: &quot;
l_string|&quot;reporting source (%04X) isn&squot;t a chpid!&quot;
l_string|&quot;Aborting processing of machine check...&bslash;n&quot;
comma
id|sei_res-&gt;rsid
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* which kind of information was stored? */
r_switch
c_cond
(paren
id|sei_res-&gt;cc
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* link incident*/
id|CIO_CRW_EVENT
c_func
(paren
l_int|4
comma
l_string|&quot;chsc_process_crw: &quot;
l_string|&quot;channel subsystem reports link incident,&quot;
l_string|&quot; source is chpid %x&bslash;n&quot;
comma
id|sei_res-&gt;rsid
)paren
suffix:semicolon
id|s390_set_chpid_offline
c_func
(paren
id|sei_res-&gt;rsid
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* i/o resource accessibiliy */
id|CIO_CRW_EVENT
c_func
(paren
l_int|4
comma
l_string|&quot;chsc_process_crw: &quot;
l_string|&quot;channel subsystem reports some I/O &quot;
l_string|&quot;devices may have become accessable&bslash;n&quot;
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Data received after sei: &bslash;n&quot;
)paren
suffix:semicolon
id|pr_debug
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Validity flags: %x&bslash;n&quot;
comma
id|sei_res-&gt;vf
)paren
suffix:semicolon
multiline_comment|/* allocate a new channel path structure, if needed */
r_if
c_cond
(paren
id|chps
(braket
id|sei_res-&gt;rsid
)braket
op_eq
l_int|NULL
)paren
id|new_channel_path
c_func
(paren
id|sei_res-&gt;rsid
comma
id|CHP_ONLINE
)paren
suffix:semicolon
r_else
id|set_chp_status
c_func
(paren
id|sei_res-&gt;rsid
comma
id|CHP_ONLINE
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sei_res-&gt;vf
op_amp
l_int|0x80
)paren
op_eq
l_int|0
)paren
(brace
id|pr_debug
c_func
(paren
id|KERN_DEBUG
l_string|&quot;chpid: %x&bslash;n&quot;
comma
id|sei_res-&gt;rsid
)paren
suffix:semicolon
id|s390_process_res_acc
c_func
(paren
id|sei_res-&gt;rsid
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|sei_res-&gt;vf
op_amp
l_int|0xc0
)paren
op_eq
l_int|0x80
)paren
(brace
id|pr_debug
c_func
(paren
id|KERN_DEBUG
l_string|&quot;chpid: %x link addr: %x&bslash;n&quot;
comma
id|sei_res-&gt;rsid
comma
id|sei_res-&gt;fla
)paren
suffix:semicolon
id|s390_process_res_acc
c_func
(paren
id|sei_res-&gt;rsid
comma
id|sei_res-&gt;fla
comma
l_int|0xff00
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|sei_res-&gt;vf
op_amp
l_int|0xc0
)paren
op_eq
l_int|0xc0
)paren
(brace
id|pr_debug
c_func
(paren
id|KERN_DEBUG
l_string|&quot;chpid: %x full link addr: %x&bslash;n&quot;
comma
id|sei_res-&gt;rsid
comma
id|sei_res-&gt;fla
)paren
suffix:semicolon
id|s390_process_res_acc
c_func
(paren
id|sei_res-&gt;rsid
comma
id|sei_res-&gt;fla
comma
l_int|0xffff
)paren
suffix:semicolon
)brace
id|pr_debug
c_func
(paren
id|KERN_DEBUG
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* other stuff */
id|CIO_CRW_EVENT
c_func
(paren
l_int|4
comma
l_string|&quot;chsc_process_crw: event %d&bslash;n&quot;
comma
id|sei_res-&gt;cc
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_void
DECL|function|chsc_process_crw
id|chsc_process_crw
c_func
(paren
r_void
)paren
(brace
r_static
id|DECLARE_WORK
c_func
(paren
id|work
comma
id|do_process_crw
comma
l_int|0
)paren
suffix:semicolon
id|schedule_work
c_func
(paren
op_amp
id|work
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function: s390_vary_chpid&n; * Varies the specified chpid online or offline&n; */
r_static
r_int
DECL|function|s390_vary_chpid
id|s390_vary_chpid
c_func
(paren
id|__u8
id|chpid
comma
r_int
id|on
)paren
(brace
r_char
id|dbf_text
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
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|chpid
op_le
l_int|0
op_logical_or
id|chpid
op_ge
id|NR_CHPIDS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|sprintf
c_func
(paren
id|dbf_text
comma
id|on
ques
c_cond
l_string|&quot;varyon%x&quot;
suffix:colon
l_string|&quot;varyoff%x&quot;
comma
id|chpid
)paren
suffix:semicolon
id|CIO_TRACE_EVENT
c_func
(paren
l_int|2
comma
id|dbf_text
)paren
suffix:semicolon
id|chsc_get_sch_descriptions
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cio_chsc_desc_avail
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Could not get chpid status, &quot;
l_string|&quot;vary on/off not available&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|chpid
comma
id|chpids_known
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Can&squot;t vary unknown chpid %02X&bslash;n&quot;
comma
id|chpid
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
id|test_bit
c_func
(paren
id|chpid
comma
id|chpids
)paren
op_eq
id|on
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;chpid %x is &quot;
l_string|&quot;already %sline&bslash;n&quot;
comma
id|chpid
comma
id|on
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
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
id|on
)paren
(brace
id|set_bit
c_func
(paren
id|chpid
comma
id|chpids_logical
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|chpid
comma
id|chpids
)paren
suffix:semicolon
id|set_chp_status
c_func
(paren
id|chpid
comma
id|CHP_ONLINE
)paren
suffix:semicolon
)brace
r_else
(brace
id|clear_bit
c_func
(paren
id|chpid
comma
id|chpids_logical
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|chpid
comma
id|chpids
)paren
suffix:semicolon
id|set_chp_status
c_func
(paren
id|chpid
comma
id|CHP_LOGICALLY_OFFLINE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Redo PathVerification on the devices the chpid connects to&n;&t; */
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
op_le
id|highest_subchannel
suffix:semicolon
id|irq
op_increment
)paren
(brace
r_int
id|chp
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We don&squot;t need to adjust the lpm, as this will be done in&n;&t;&t; * DevicePathVerification...&n;&t;&t; */
id|sch
op_assign
id|ioinfo
(braket
id|irq
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sch
op_eq
l_int|NULL
op_logical_or
id|sch-&gt;st
op_logical_or
op_logical_neg
id|sch-&gt;ssd_info.valid
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|chp
op_assign
l_int|0
suffix:semicolon
id|chp
OL
l_int|8
suffix:semicolon
id|chp
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sch-&gt;ssd_info.chpid
(braket
id|chp
)braket
op_eq
id|chpid
)paren
(brace
r_if
c_cond
(paren
id|on
)paren
id|sch-&gt;lpm
op_or_assign
(paren
l_int|0x80
op_rshift
id|chp
)paren
suffix:semicolon
r_else
id|sch-&gt;lpm
op_and_assign
op_complement
(paren
l_int|0x80
op_rshift
id|chp
)paren
suffix:semicolon
id|dev_fsm_event
c_func
(paren
id|sch-&gt;dev.driver_data
comma
id|DEV_EVENT_VERIFY
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Files for the channel path entries.&n; */
r_static
id|ssize_t
DECL|function|chp_status_show
id|chp_status_show
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|sys_device
op_star
id|sdev
op_assign
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|sys_device
comma
id|dev
)paren
suffix:semicolon
r_struct
id|channel_path
op_star
id|chp
op_assign
id|container_of
c_func
(paren
id|sdev
comma
r_struct
id|channel_path
comma
id|sdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chp
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|chp-&gt;state
)paren
(brace
r_case
id|CHP_OFFLINE
suffix:colon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;n/a&bslash;n&quot;
)paren
suffix:semicolon
r_case
id|CHP_LOGICALLY_OFFLINE
suffix:colon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;logically offline&bslash;n&quot;
)paren
suffix:semicolon
r_case
id|CHP_STANDBY
suffix:colon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;n/a&bslash;n&quot;
)paren
suffix:semicolon
r_case
id|CHP_ONLINE
suffix:colon
r_return
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;online&bslash;n&quot;
)paren
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_static
id|ssize_t
DECL|function|chp_status_write
id|chp_status_write
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_struct
id|sys_device
op_star
id|sdev
op_assign
id|container_of
c_func
(paren
id|dev
comma
r_struct
id|sys_device
comma
id|dev
)paren
suffix:semicolon
r_struct
id|channel_path
op_star
id|cp
op_assign
id|container_of
c_func
(paren
id|sdev
comma
r_struct
id|channel_path
comma
id|sdev
)paren
suffix:semicolon
r_char
id|cmd
(braket
l_int|10
)braket
suffix:semicolon
r_int
id|num_args
suffix:semicolon
r_int
id|error
suffix:semicolon
id|num_args
op_assign
id|sscanf
c_func
(paren
id|buf
comma
l_string|&quot;%5s&quot;
comma
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|num_args
)paren
r_return
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|cmd
comma
l_string|&quot;on&quot;
comma
l_int|2
)paren
)paren
id|error
op_assign
id|s390_vary_chpid
c_func
(paren
id|cp-&gt;id
comma
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|cmd
comma
l_string|&quot;off&quot;
comma
l_int|3
)paren
)paren
id|error
op_assign
id|s390_vary_chpid
c_func
(paren
id|cp-&gt;id
comma
l_int|0
)paren
suffix:semicolon
r_else
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_return
id|error
OL
l_int|0
ques
c_cond
id|error
suffix:colon
id|count
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|status
comma
l_int|0644
comma
id|chp_status_show
comma
id|chp_status_write
)paren
suffix:semicolon
multiline_comment|/*&n; * Entries for chpids on the system bus.&n; * This replaces /proc/chpids.&n; */
r_static
r_int
DECL|function|new_channel_path
id|new_channel_path
c_func
(paren
r_int
id|chpid
comma
r_int
id|status
)paren
(brace
r_struct
id|channel_path
op_star
id|chp
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|chp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|channel_path
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chp
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|chps
(braket
id|chpid
)braket
op_assign
id|chp
suffix:semicolon
multiline_comment|/* fill in status, etc. */
id|chp-&gt;id
op_assign
id|chpid
suffix:semicolon
id|chp-&gt;state
op_assign
id|status
suffix:semicolon
id|snprintf
c_func
(paren
id|chp-&gt;sdev.dev.name
comma
id|DEVICE_NAME_SIZE
comma
l_string|&quot;channel path %x&quot;
comma
id|chpid
)paren
suffix:semicolon
id|chp-&gt;sdev.name
op_assign
l_string|&quot;channel_path&quot;
suffix:semicolon
id|chp-&gt;sdev.id
op_assign
id|chpid
suffix:semicolon
multiline_comment|/* make it known to the system */
id|ret
op_assign
id|sys_device_register
c_func
(paren
op_amp
id|chp-&gt;sdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: could not register %02x&bslash;n&quot;
comma
id|__func__
comma
id|chpid
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
id|device_create_file
c_func
(paren
op_amp
id|chp-&gt;sdev.dev
comma
op_amp
id|dev_attr_status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|sys_device_unregister
c_func
(paren
op_amp
id|chp-&gt;sdev
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|register_channel_paths
id|register_channel_paths
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* walk through the chpids arrays */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CHPIDS
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* we are only interested in known chpids */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|i
comma
id|chpids_known
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|i
comma
id|chpids
)paren
)paren
multiline_comment|/* standby */
id|ret
op_assign
id|new_channel_path
c_func
(paren
id|i
comma
id|CHP_STANDBY
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
comma
id|chpids_logical
)paren
)paren
multiline_comment|/* online */
id|ret
op_assign
id|new_channel_path
c_func
(paren
id|i
comma
id|CHP_ONLINE
)paren
suffix:semicolon
r_else
multiline_comment|/* logically offline */
id|ret
op_assign
id|new_channel_path
c_func
(paren
id|i
comma
id|CHP_LOGICALLY_OFFLINE
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|register_channel_paths
id|module_init
c_func
(paren
id|register_channel_paths
)paren
suffix:semicolon
eof
