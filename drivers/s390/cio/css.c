multiline_comment|/*&n; *  drivers/s390/cio/css.c&n; *  driver for channel subsystem&n; *   $Revision: 1.49 $&n; *&n; *    Copyright (C) 2002 IBM Deutschland Entwicklung GmbH,&n; *&t;&t;&t; IBM Corporation&n; *    Author(s): Arnd Bergmann (arndb@de.ibm.com)&n; *&t;&t; Cornelia Huck (cohuck@de.ibm.com)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/ccwdev.h&gt; 
singleline_comment|// FIXME: layering violation, remove this
macro_line|#include &quot;css.h&quot;
macro_line|#include &quot;cio.h&quot;
macro_line|#include &quot;cio_debug.h&quot;
macro_line|#include &quot;device.h&quot; 
singleline_comment|// FIXME: dito
macro_line|#include &quot;ioasm.h&quot;
DECL|variable|ioinfo
r_struct
id|subchannel
op_star
id|ioinfo
(braket
id|__MAX_SUBCHANNELS
)braket
suffix:semicolon
DECL|variable|highest_subchannel
r_int
r_int
id|highest_subchannel
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
r_int
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
r_if
c_cond
(paren
id|ioinfo
(braket
id|irq
)braket
)paren
multiline_comment|/* There already is a struct subchannel for this irq. */
r_return
op_minus
id|EBUSY
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
op_minus
id|ENOMEM
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
id|ret
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
op_minus
id|EINVAL
suffix:semicolon
)brace
id|ioinfo
(braket
id|irq
)braket
op_assign
id|sch
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|css_free_subchannel
id|css_free_subchannel
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
)paren
(brace
id|ioinfo
(braket
id|irq
)braket
op_assign
l_int|NULL
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
multiline_comment|/* Set a name for the subchannel */
id|snprintf
(paren
id|sch-&gt;dev.bus_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;0.0.%04x&quot;
comma
id|sch-&gt;irq
)paren
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
id|ret
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
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|ret
op_assign
id|css_register_subchannel
c_func
(paren
id|ioinfo
(braket
id|irq
)braket
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
id|irq
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Rescan for new devices. FIXME: This is slow.&n; */
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
OL
id|__MAX_SUBCHANNELS
suffix:semicolon
id|irq
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ioinfo
(braket
id|irq
)braket
)paren
r_continue
suffix:semicolon
id|ret
op_assign
id|css_probe_device
c_func
(paren
id|irq
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
multiline_comment|/*&n; * Called from the machine check handler for subchannel report words.&n; * Note: this is called disabled from the machine check handler itself.&n; */
r_void
DECL|function|css_process_crw
id|css_process_crw
c_func
(paren
r_int
id|irq
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
r_struct
id|subchannel
op_star
id|sch
suffix:semicolon
r_int
id|ccode
comma
id|devno
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
(brace
id|queue_work
c_func
(paren
id|ccw_device_work
comma
op_amp
id|work
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sch-&gt;dev.driver_data
)paren
r_return
suffix:semicolon
id|devno
op_assign
id|sch-&gt;schib.pmcw.dev
suffix:semicolon
multiline_comment|/* FIXME: css_process_crw must not know about ccw_device */
id|dev_fsm_event
c_func
(paren
id|sch-&gt;dev.driver_data
comma
id|DEV_EVENT_NOTOPER
)paren
suffix:semicolon
id|ccode
op_assign
id|stsch
c_func
(paren
id|irq
comma
op_amp
id|sch-&gt;schib
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ccode
)paren
r_if
c_cond
(paren
id|devno
op_ne
id|sch-&gt;schib.pmcw.dev
)paren
id|queue_work
c_func
(paren
id|ccw_device_work
comma
op_amp
id|work
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * some of the initialization has already been done from init_IRQ(),&n; * here we do the rest now that the driver core is running.&n; * Currently, this functions scans all the subchannel structures for&n; * devices. The long term plan is to remove ioinfo[] and then the&n; * struct subchannel&squot;s will be created during probing. &n; */
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
r_if
c_cond
(paren
op_logical_neg
id|ioinfo
(braket
id|irq
)braket
)paren
(brace
id|ret
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
id|ioinfo
(braket
id|irq
)braket
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
eof
