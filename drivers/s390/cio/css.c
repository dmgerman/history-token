multiline_comment|/*&n; *  drivers/s390/cio/css.c&n; *  driver for channel subsystem&n; *   $Revision: 1.74 $&n; *&n; *    Copyright (C) 2002 IBM Deutschland Entwicklung GmbH,&n; *&t;&t;&t; IBM Corporation&n; *    Author(s): Arnd Bergmann (arndb@de.ibm.com)&n; *&t;&t; Cornelia Huck (cohuck@de.ibm.com)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &quot;css.h&quot;
macro_line|#include &quot;cio.h&quot;
macro_line|#include &quot;cio_debug.h&quot;
macro_line|#include &quot;ioasm.h&quot;
DECL|variable|highest_subchannel
r_int
r_int
id|highest_subchannel
suffix:semicolon
DECL|variable|need_rescan
r_int
id|need_rescan
op_assign
l_int|0
suffix:semicolon
DECL|variable|css_init_done
r_int
id|css_init_done
op_assign
l_int|0
suffix:semicolon
DECL|variable|css_bus_device
r_struct
id|device
id|css_bus_device
op_assign
(brace
dot
id|bus_id
op_assign
l_string|&quot;css0&quot;
comma
)brace
suffix:semicolon
r_static
r_struct
id|subchannel
op_star
DECL|function|css_alloc_subchannel
id|css_alloc_subchannel
c_func
(paren
r_int
id|irq
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
id|kmalloc
(paren
r_sizeof
(paren
op_star
id|sch
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
id|sch
op_eq
l_int|NULL
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|ret
op_assign
id|cio_validate_subchannel
(paren
id|sch
comma
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|sch
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
OG
id|highest_subchannel
)paren
id|highest_subchannel
op_assign
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|sch-&gt;st
op_ne
id|SUBCHANNEL_TYPE_IO
)paren
(brace
multiline_comment|/* For now we ignore all non-io subchannels. */
id|kfree
c_func
(paren
id|sch
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * Set intparm to subchannel address.&n;&t; * This is fine even on 64bit since the subchannel is always located&n;&t; * under 2G.&n;&t; */
id|sch-&gt;schib.pmcw.intparm
op_assign
(paren
id|__u32
)paren
(paren
r_int
r_int
)paren
id|sch
suffix:semicolon
id|ret
op_assign
id|cio_modify
c_func
(paren
id|sch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|kfree
c_func
(paren
id|sch
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
r_return
id|sch
suffix:semicolon
)brace
r_static
r_void
DECL|function|css_free_subchannel
id|css_free_subchannel
c_func
(paren
r_struct
id|subchannel
op_star
id|sch
)paren
(brace
r_if
c_cond
(paren
id|sch
)paren
(brace
multiline_comment|/* Reset intparm to zeroes. */
id|sch-&gt;schib.pmcw.intparm
op_assign
l_int|0
suffix:semicolon
id|cio_modify
c_func
(paren
id|sch
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sch
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|css_subchannel_release
id|css_subchannel_release
c_func
(paren
r_struct
id|device
op_star
id|dev
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
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cio_is_console
c_func
(paren
id|sch-&gt;irq
)paren
)paren
id|kfree
c_func
(paren
id|sch
)paren
suffix:semicolon
)brace
r_extern
r_int
id|css_get_ssd_info
c_func
(paren
r_struct
id|subchannel
op_star
id|sch
)paren
suffix:semicolon
r_static
r_int
DECL|function|css_register_subchannel
id|css_register_subchannel
c_func
(paren
r_struct
id|subchannel
op_star
id|sch
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/* Initialize the subchannel structure */
id|sch-&gt;dev.parent
op_assign
op_amp
id|css_bus_device
suffix:semicolon
id|sch-&gt;dev.bus
op_assign
op_amp
id|css_bus_type
suffix:semicolon
id|sch-&gt;dev.release
op_assign
op_amp
id|css_subchannel_release
suffix:semicolon
multiline_comment|/* make it known to the system */
id|ret
op_assign
id|device_register
c_func
(paren
op_amp
id|sch-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|printk
(paren
id|KERN_WARNING
l_string|&quot;%s: could not register %s&bslash;n&quot;
comma
id|__func__
comma
id|sch-&gt;dev.bus_id
)paren
suffix:semicolon
r_else
id|css_get_ssd_info
c_func
(paren
id|sch
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|css_probe_device
id|css_probe_device
c_func
(paren
r_int
id|irq
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
id|css_alloc_subchannel
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|sch
)paren
)paren
r_return
id|PTR_ERR
c_func
(paren
id|sch
)paren
suffix:semicolon
id|ret
op_assign
id|css_register_subchannel
c_func
(paren
id|sch
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|css_free_subchannel
c_func
(paren
id|sch
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_struct
id|subchannel
op_star
DECL|function|get_subchannel_by_schid
id|get_subchannel_by_schid
c_func
(paren
r_int
id|irq
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_struct
id|device
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|get_bus
c_func
(paren
op_amp
id|css_bus_type
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|css_bus_type.subsys.rwsem
)paren
suffix:semicolon
id|sch
op_assign
l_int|NULL
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|css_bus_type.devices.list
)paren
(brace
id|dev
op_assign
id|get_device
c_func
(paren
id|container_of
c_func
(paren
id|entry
comma
r_struct
id|device
comma
id|bus_list
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_continue
suffix:semicolon
id|sch
op_assign
id|to_subchannel
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sch-&gt;irq
op_eq
id|irq
)paren
r_break
suffix:semicolon
id|put_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|sch
op_assign
l_int|NULL
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|css_bus_type.subsys.rwsem
)paren
suffix:semicolon
id|put_bus
c_func
(paren
op_amp
id|css_bus_type
)paren
suffix:semicolon
r_return
id|sch
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|css_get_subchannel_status
id|css_get_subchannel_status
c_func
(paren
r_struct
id|subchannel
op_star
id|sch
comma
r_int
id|schid
)paren
(brace
r_struct
id|schib
id|schib
suffix:semicolon
r_int
id|cc
suffix:semicolon
id|cc
op_assign
id|stsch
c_func
(paren
id|schid
comma
op_amp
id|schib
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cc
)paren
r_return
id|CIO_GONE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|schib.pmcw.dnv
)paren
r_return
id|CIO_GONE
suffix:semicolon
r_if
c_cond
(paren
id|sch
op_logical_and
id|sch-&gt;schib.pmcw.dnv
op_logical_and
(paren
id|schib.pmcw.dev
op_ne
id|sch-&gt;schib.pmcw.dev
)paren
)paren
r_return
id|CIO_REVALIDATE
suffix:semicolon
r_return
id|CIO_OPER
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|css_evaluate_subchannel
id|css_evaluate_subchannel
c_func
(paren
r_int
id|irq
comma
r_int
id|slow
)paren
(brace
r_int
id|event
comma
id|ret
comma
id|disc
suffix:semicolon
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
id|sch
op_assign
id|get_subchannel_by_schid
c_func
(paren
id|irq
)paren
suffix:semicolon
id|disc
op_assign
id|sch
ques
c_cond
id|device_is_disconnected
c_func
(paren
id|sch
)paren
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|disc
op_logical_and
id|slow
)paren
(brace
r_if
c_cond
(paren
id|sch
)paren
id|put_device
c_func
(paren
op_amp
id|sch-&gt;dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Already processed. */
)brace
r_if
c_cond
(paren
op_logical_neg
id|disc
op_logical_and
op_logical_neg
id|slow
)paren
(brace
r_if
c_cond
(paren
id|sch
)paren
id|put_device
c_func
(paren
op_amp
id|sch-&gt;dev
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
multiline_comment|/* Will be done on the slow path. */
)brace
id|event
op_assign
id|css_get_subchannel_status
c_func
(paren
id|sch
comma
id|irq
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|CIO_GONE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sch
)paren
(brace
multiline_comment|/* Never used this subchannel. Ignore. */
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sch-&gt;driver
op_logical_and
id|sch-&gt;driver-&gt;notify
op_logical_and
id|sch-&gt;driver
op_member_access_from_pointer
id|notify
c_func
(paren
op_amp
id|sch-&gt;dev
comma
id|CIO_GONE
)paren
)paren
(brace
id|device_set_disconnected
c_func
(paren
id|sch
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Unregister subchannel.&n;&t;&t; * The device will be killed automatically.&n;&t;&t; */
id|device_unregister
c_func
(paren
op_amp
id|sch-&gt;dev
)paren
suffix:semicolon
multiline_comment|/* Reset intparm to zeroes. */
id|sch-&gt;schib.pmcw.intparm
op_assign
l_int|0
suffix:semicolon
id|cio_modify
c_func
(paren
id|sch
)paren
suffix:semicolon
id|put_device
c_func
(paren
op_amp
id|sch-&gt;dev
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CIO_REVALIDATE
suffix:colon
multiline_comment|/* &n;&t;&t; * Revalidation machine check. Sick.&n;&t;&t; * We don&squot;t notify the driver since we have to throw the device&n;&t;&t; * away in any case.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|disc
)paren
(brace
id|device_unregister
c_func
(paren
op_amp
id|sch-&gt;dev
)paren
suffix:semicolon
multiline_comment|/* Reset intparm to zeroes. */
id|sch-&gt;schib.pmcw.intparm
op_assign
l_int|0
suffix:semicolon
id|cio_modify
c_func
(paren
id|sch
)paren
suffix:semicolon
id|put_device
c_func
(paren
op_amp
id|sch-&gt;dev
)paren
suffix:semicolon
id|ret
op_assign
id|css_probe_device
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * We can&squot;t immediately deregister the disconnected&n;&t;&t;&t; * device since it might block.&n;&t;&t;&t; */
id|device_trigger_reprobe
c_func
(paren
id|sch
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CIO_OPER
suffix:colon
r_if
c_cond
(paren
id|disc
)paren
multiline_comment|/* Get device operational again. */
id|device_trigger_reprobe
c_func
(paren
id|sch
)paren
suffix:semicolon
id|ret
op_assign
id|sch
ques
c_cond
l_int|0
suffix:colon
id|css_probe_device
c_func
(paren
id|irq
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
r_static
r_void
DECL|function|css_rescan_devices
id|css_rescan_devices
c_func
(paren
r_void
)paren
(brace
r_int
id|irq
comma
id|ret
suffix:semicolon
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
id|ret
op_assign
id|css_evaluate_subchannel
c_func
(paren
id|irq
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* No more memory. It doesn&squot;t make sense to continue. No&n;&t;&t; * panic because this can happen in midflight and just&n;&t;&t; * because we can&squot;t use a new device is no reason to crash&n;&t;&t; * the system. */
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ENOMEM
)paren
r_break
suffix:semicolon
multiline_comment|/* -ENXIO indicates that there are no more subchannels. */
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ENXIO
)paren
r_break
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|css_evaluate_slow_subchannel
id|css_evaluate_slow_subchannel
c_func
(paren
r_int
r_int
id|schid
)paren
(brace
id|css_evaluate_subchannel
c_func
(paren
id|schid
comma
l_int|1
)paren
suffix:semicolon
)brace
r_void
DECL|function|css_trigger_slow_path
id|css_trigger_slow_path
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|need_rescan
)paren
(brace
id|need_rescan
op_assign
l_int|0
suffix:semicolon
id|css_rescan_devices
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|css_walk_subchannel_slow_list
c_func
(paren
id|css_evaluate_slow_subchannel
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Rescan for new devices. FIXME: This is slow.&n; * This function is called when we have lost CRWs due to overflows and we have&n; * to do subchannel housekeeping.&n; */
r_void
DECL|function|css_reiterate_subchannels
id|css_reiterate_subchannels
c_func
(paren
r_void
)paren
(brace
id|css_clear_subchannel_slow_list
c_func
(paren
)paren
suffix:semicolon
id|need_rescan
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Called from the machine check handler for subchannel report words.&n; */
r_int
DECL|function|css_process_crw
id|css_process_crw
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|ret
suffix:semicolon
id|CIO_CRW_EVENT
c_func
(paren
l_int|2
comma
l_string|&quot;source is subchannel %04X&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_rescan
)paren
multiline_comment|/* We need to iterate all subchannels anyway. */
r_return
op_minus
id|EAGAIN
suffix:semicolon
multiline_comment|/* &n;&t; * Since we are always presented with IPI in the CRW, we have to&n;&t; * use stsch() to find out if the subchannel in question has come&n;&t; * or gone.&n;&t; */
id|ret
op_assign
id|css_evaluate_subchannel
c_func
(paren
id|irq
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|EAGAIN
)paren
(brace
r_if
c_cond
(paren
id|css_enqueue_subchannel_slow
c_func
(paren
id|irq
)paren
)paren
(brace
id|css_clear_subchannel_slow_list
c_func
(paren
)paren
suffix:semicolon
id|need_rescan
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * some of the initialization has already been done from init_IRQ(),&n; * here we do the rest now that the driver core is running.&n; * The struct subchannel&squot;s are created during probing (except for the&n; * static console subchannel).&n; */
r_static
r_int
id|__init
DECL|function|init_channel_subsystem
id|init_channel_subsystem
(paren
r_void
)paren
(brace
r_int
id|ret
comma
id|irq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|bus_register
c_func
(paren
op_amp
id|css_bus_type
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|device_register
(paren
op_amp
id|css_bus_device
)paren
)paren
)paren
r_goto
id|out_bus
suffix:semicolon
id|css_init_done
op_assign
l_int|1
suffix:semicolon
id|ctl_set_bit
c_func
(paren
l_int|6
comma
l_int|28
)paren
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
OL
id|__MAX_SUBCHANNELS
suffix:semicolon
id|irq
op_increment
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
id|cio_is_console
c_func
(paren
id|irq
)paren
)paren
id|sch
op_assign
id|cio_get_console_subchannel
c_func
(paren
)paren
suffix:semicolon
r_else
(brace
id|sch
op_assign
id|css_alloc_subchannel
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|sch
)paren
)paren
id|ret
op_assign
id|PTR_ERR
c_func
(paren
id|sch
)paren
suffix:semicolon
r_else
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ENOMEM
)paren
id|panic
c_func
(paren
l_string|&quot;Out of memory in &quot;
l_string|&quot;init_channel_subsystem&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* -ENXIO: no more subchannels. */
r_if
c_cond
(paren
id|ret
op_eq
op_minus
id|ENXIO
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * We register ALL valid subchannels in ioinfo, even those&n;&t;&t; * that have been present before init_channel_subsystem.&n;&t;&t; * These subchannels can&squot;t have been registered yet (kmalloc&n;&t;&t; * not working) so we do it now. This is true e.g. for the&n;&t;&t; * console subchannel.&n;&t;&t; */
id|css_register_subchannel
c_func
(paren
id|sch
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|out_bus
suffix:colon
id|bus_unregister
c_func
(paren
op_amp
id|css_bus_type
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * find a driver for a subchannel. They identify by the subchannel&n; * type with the exception that the console subchannel driver has its own&n; * subchannel type although the device is an i/o subchannel&n; */
r_static
r_int
DECL|function|css_bus_match
id|css_bus_match
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|device_driver
op_star
id|drv
)paren
(brace
r_struct
id|subchannel
op_star
id|sch
op_assign
id|container_of
(paren
id|dev
comma
r_struct
id|subchannel
comma
id|dev
)paren
suffix:semicolon
r_struct
id|css_driver
op_star
id|driver
op_assign
id|container_of
(paren
id|drv
comma
r_struct
id|css_driver
comma
id|drv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sch-&gt;st
op_eq
id|driver-&gt;subchannel_type
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|css_bus_type
r_struct
id|bus_type
id|css_bus_type
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;css&quot;
comma
dot
id|match
op_assign
op_amp
id|css_bus_match
comma
)brace
suffix:semicolon
DECL|variable|init_channel_subsystem
id|subsys_initcall
c_func
(paren
id|init_channel_subsystem
)paren
suffix:semicolon
multiline_comment|/*&n; * Register root devices for some drivers. The release function must not be&n; * in the device drivers, so we do it here.&n; */
r_static
r_void
DECL|function|s390_root_dev_release
id|s390_root_dev_release
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_struct
id|device
op_star
DECL|function|s390_root_dev_register
id|s390_root_dev_register
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|device
op_star
id|dev
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strlen
c_func
(paren
id|name
)paren
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|device
)paren
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|dev-&gt;bus_id
comma
id|name
comma
id|min
c_func
(paren
id|strlen
c_func
(paren
id|name
)paren
comma
(paren
r_int
)paren
id|BUS_ID_SIZE
)paren
)paren
suffix:semicolon
id|dev-&gt;release
op_assign
id|s390_root_dev_release
suffix:semicolon
id|ret
op_assign
id|device_register
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|ERR_PTR
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
r_return
id|dev
suffix:semicolon
)brace
r_void
DECL|function|s390_root_dev_unregister
id|s390_root_dev_unregister
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev
)paren
id|device_unregister
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|struct|slow_subchannel
r_struct
id|slow_subchannel
(brace
DECL|member|slow_list
r_struct
id|list_head
id|slow_list
suffix:semicolon
DECL|member|schid
r_int
r_int
id|schid
suffix:semicolon
)brace
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|slow_subchannels_head
)paren
suffix:semicolon
DECL|variable|slow_subchannel_lock
r_static
id|spinlock_t
id|slow_subchannel_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_int
DECL|function|css_enqueue_subchannel_slow
id|css_enqueue_subchannel_slow
c_func
(paren
r_int
r_int
id|schid
)paren
(brace
r_struct
id|slow_subchannel
op_star
id|new_slow_sch
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|new_slow_sch
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|slow_subchannel
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_slow_sch
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|new_slow_sch-&gt;schid
op_assign
id|schid
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|slow_subchannel_lock
comma
id|flags
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|new_slow_sch-&gt;slow_list
comma
op_amp
id|slow_subchannels_head
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|slow_subchannel_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|css_clear_subchannel_slow_list
id|css_clear_subchannel_slow_list
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|slow_subchannel_lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|slow_subchannels_head
)paren
)paren
(brace
r_struct
id|slow_subchannel
op_star
id|slow_sch
op_assign
id|list_entry
c_func
(paren
id|slow_subchannels_head.next
comma
r_struct
id|slow_subchannel
comma
id|slow_list
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
id|slow_subchannels_head.next
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|slow_sch
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|slow_subchannel_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_void
DECL|function|css_walk_subchannel_slow_list
id|css_walk_subchannel_slow_list
c_func
(paren
r_void
(paren
op_star
id|fn
)paren
(paren
r_int
r_int
)paren
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|slow_subchannel_lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|slow_subchannels_head
)paren
)paren
(brace
r_struct
id|slow_subchannel
op_star
id|slow_sch
op_assign
id|list_entry
c_func
(paren
id|slow_subchannels_head.next
comma
r_struct
id|slow_subchannel
comma
id|slow_list
)paren
suffix:semicolon
id|list_del_init
c_func
(paren
id|slow_subchannels_head.next
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|slow_subchannel_lock
comma
id|flags
)paren
suffix:semicolon
id|fn
c_func
(paren
id|slow_sch-&gt;schid
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|slow_subchannel_lock
comma
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|slow_sch
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|slow_subchannel_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_int
DECL|function|css_slow_subchannels_exist
id|css_slow_subchannels_exist
c_func
(paren
r_void
)paren
(brace
r_return
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|slow_subchannels_head
)paren
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|css_bus_type
id|EXPORT_SYMBOL
c_func
(paren
id|css_bus_type
)paren
suffix:semicolon
DECL|variable|s390_root_dev_register
id|EXPORT_SYMBOL
c_func
(paren
id|s390_root_dev_register
)paren
suffix:semicolon
DECL|variable|s390_root_dev_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|s390_root_dev_unregister
)paren
suffix:semicolon
eof
