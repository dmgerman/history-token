multiline_comment|/*&n; *  include/asm-s390/chandev.h&n; *&n; *    Copyright (C) 2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; * &n; *  Generic channel device initialisation support. &n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
multiline_comment|/* chandev_type is a bitmask for registering &amp; describing device types. */
r_typedef
r_enum
(brace
DECL|enumerator|none
id|none
op_assign
l_int|0x0
comma
DECL|enumerator|ctc
id|ctc
op_assign
l_int|0x1
comma
DECL|enumerator|escon
id|escon
op_assign
l_int|0x2
comma
DECL|enumerator|lcs
id|lcs
op_assign
l_int|0x4
comma
DECL|enumerator|osad
id|osad
op_assign
l_int|0x8
comma
DECL|enumerator|qeth
id|qeth
op_assign
l_int|0x10
comma
DECL|enumerator|claw
id|claw
op_assign
l_int|0x20
comma
DECL|typedef|chandev_type
)brace
id|chandev_type
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|no_category
id|no_category
comma
DECL|enumerator|network_device
id|network_device
comma
DECL|enumerator|serial_device
id|serial_device
comma
DECL|typedef|chandev_category
)brace
id|chandev_category
suffix:semicolon
multiline_comment|/*&n; * The chandev_probeinfo structure is passed to the device driver with configuration&n; * info for which irq&squot;s &amp; ports to use when attempting to probe the device.&n; */
r_typedef
r_struct
(brace
DECL|member|read_irq
r_int
id|read_irq
suffix:semicolon
DECL|member|write_irq
r_int
id|write_irq
suffix:semicolon
DECL|member|read_devno
id|u16
id|read_devno
suffix:semicolon
DECL|member|write_devno
id|u16
id|write_devno
suffix:semicolon
DECL|member|port_protocol_no
id|s16
id|port_protocol_no
suffix:semicolon
multiline_comment|/* -1 don&squot;t care */
DECL|member|hint_port_no
id|u8
id|hint_port_no
suffix:semicolon
multiline_comment|/* lcs specific */
DECL|member|max_port_no
id|u8
id|max_port_no
suffix:semicolon
multiline_comment|/* lcs specific */
DECL|member|chan_type
id|chandev_type
id|chan_type
suffix:semicolon
DECL|member|checksum_received_ip_pkts
id|u8
id|checksum_received_ip_pkts
suffix:semicolon
DECL|member|use_hw_stats
id|u8
id|use_hw_stats
suffix:semicolon
multiline_comment|/* where available e.g. lcs */
DECL|member|cu_type
id|u16
id|cu_type
suffix:semicolon
multiline_comment|/* control unit type */
DECL|member|cu_model
id|u8
id|cu_model
suffix:semicolon
multiline_comment|/* control unit model */
DECL|member|dev_type
id|u16
id|dev_type
suffix:semicolon
multiline_comment|/* device type */
DECL|member|dev_model
id|u8
id|dev_model
suffix:semicolon
multiline_comment|/* device model */
DECL|member|parmstr
r_char
op_star
id|parmstr
suffix:semicolon
multiline_comment|/* driver specific parameters added by add_parms keyword */
multiline_comment|/* newdevice used internally by chandev.c */
DECL|member|newdevice
r_struct
id|chandev_activelist
op_star
id|newdevice
suffix:semicolon
DECL|member|devif_num
id|s32
id|devif_num
suffix:semicolon
multiline_comment|/* devif_num=-1 implies don&squot;t care,0 implies tr0, info used by chandev_initnetdevice */
DECL|typedef|chandev_probeinfo
)brace
id|chandev_probeinfo
suffix:semicolon
multiline_comment|/*&n; * This is a wrapper to the machine check handler &amp; should be used&n; * instead of reqest_irq or s390_request_irq_special for anything&n; * using the channel device layer.&n; */
r_int
id|chandev_request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|irqflags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
multiline_comment|/*&n; * I originally believed this function wouldn&squot;t be necessary&n; * I subsequently found that reprobing failed in certain cases :-(,&n; * It is just a wrapper for free irq.&n; */
r_void
id|chandev_free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|good
id|good
op_assign
l_int|0
comma
DECL|enumerator|not_oper
id|not_oper
comma
DECL|enumerator|first_msck
id|first_msck
op_assign
id|not_oper
comma
DECL|enumerator|no_path
id|no_path
comma
DECL|enumerator|revalidate
id|revalidate
comma
DECL|enumerator|gone
id|gone
comma
DECL|enumerator|last_msck
id|last_msck
comma
DECL|typedef|chandev_msck_status
)brace
id|chandev_msck_status
suffix:semicolon
DECL|typedef|chandev_probefunc
r_typedef
r_int
(paren
op_star
id|chandev_probefunc
)paren
(paren
id|chandev_probeinfo
op_star
id|probeinfo
)paren
suffix:semicolon
DECL|typedef|chandev_shutdownfunc
r_typedef
r_void
(paren
op_star
id|chandev_shutdownfunc
)paren
(paren
r_void
op_star
id|device
)paren
suffix:semicolon
DECL|typedef|chandev_unregfunc
r_typedef
r_void
(paren
op_star
id|chandev_unregfunc
)paren
(paren
r_void
op_star
id|device
)paren
suffix:semicolon
DECL|typedef|chandev_reoperfunc
r_typedef
r_void
(paren
op_star
id|chandev_reoperfunc
)paren
(paren
r_void
op_star
id|device
comma
r_int
id|msck_for_read_chan
comma
id|chandev_msck_status
id|prevstatus
)paren
suffix:semicolon
multiline_comment|/* A driver should call chandev_register_and_probe when ready to be probed,&n; * after registeration the drivers probefunction will be called asynchronously&n; * when more devices become available at normal task time.&n; * The shutdownfunc parameter is used so that the channel layer&n; * can request a driver to close unregister itself &amp; release its interrupts.&n; * repoper func is used when a device becomes operational again after being temporarily&n; * not operational the previous status is sent in the prevstatus variable.&n; * This can be used in cases when the default handling isn&squot;t quite adequete&n; * e.g. if a ssch is needed to reinitialize long running channel programs.&n; */
r_int
id|chandev_register_and_probe
c_func
(paren
id|chandev_probefunc
id|probefunc
comma
id|chandev_shutdownfunc
id|shutdownfunc
comma
id|chandev_reoperfunc
id|reoperfunc
comma
id|chandev_type
id|chan_type
)paren
suffix:semicolon
multiline_comment|/* The chandev_unregister function is typically called when a module is being removed &n; * from the system. The shutdown parameter if TRUE calls shutdownfunc for each &n; * device instance so the driver writer doesn&squot;t have to.&n; */
r_void
id|chandev_unregister
c_func
(paren
id|chandev_probefunc
id|probefunc
comma
r_int
id|call_shutdown
)paren
suffix:semicolon
multiline_comment|/* chandev_initdevice should be called immeadiately before returning after */
multiline_comment|/* a successful probe. */
r_int
id|chandev_initdevice
c_func
(paren
id|chandev_probeinfo
op_star
id|probeinfo
comma
r_void
op_star
id|dev_ptr
comma
id|u8
id|port_no
comma
r_char
op_star
id|devname
comma
id|chandev_category
id|category
comma
id|chandev_unregfunc
id|unreg_dev
)paren
suffix:semicolon
multiline_comment|/* chandev_initnetdevice registers a network device with the channel layer. &n; * It returns the device structure if successful,if dev=NULL it kmallocs it, &n; * On device initialisation failure it will kfree it under ALL curcumstances&n; * i.e. if dev is not NULL on entering this routine it MUST be malloced with kmalloc. &n; * The base name is tr ( e.g. tr0 without the 0 ), for token ring eth for ethernet,&n; *  ctc or escon for ctc device drivers.&n; * If valid function pointers are given they will be called to setup,&n; * register &amp; unregister the device. &n; * An example of setup is eth_setup in drivers/net/net_init.c.&n; * An example of init_dev is init_trdev(struct net_device *dev)&n; * &amp; an example of unregister is unregister_trdev, &n; * unregister_netdev should be used for escon &amp; ctc&n; * as there is no network unregister_ctcdev in the kernel.&n;*/
macro_line|#if LINUX_VERSION_CODE&gt;=KERNEL_VERSION(2,3,0)
r_struct
id|net_device
op_star
id|chandev_initnetdevice
c_func
(paren
id|chandev_probeinfo
op_star
id|probeinfo
comma
id|u8
id|port_no
comma
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|sizeof_priv
comma
r_char
op_star
id|basename
comma
r_struct
id|net_device
op_star
(paren
op_star
id|init_netdevfunc
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|sizeof_priv
)paren
comma
r_void
(paren
op_star
id|unreg_netdevfunc
)paren
(paren
r_struct
id|net_device
op_star
id|dev
)paren
)paren
suffix:semicolon
macro_line|#else
r_struct
id|device
op_star
id|chandev_initnetdevice
c_func
(paren
id|chandev_probeinfo
op_star
id|probeinfo
comma
id|u8
id|port_no
comma
r_struct
id|device
op_star
id|dev
comma
r_int
id|sizeof_priv
comma
r_char
op_star
id|basename
comma
r_struct
id|device
op_star
(paren
op_star
id|init_netdevfunc
)paren
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|sizeof_priv
)paren
comma
r_void
(paren
op_star
id|unreg_netdevfunc
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
)paren
suffix:semicolon
macro_line|#endif
eof
