multiline_comment|/*&n; * IEEE 1394 for Linux&n; *&n; * Low level (host adapter) management.&n; *&n; * Copyright (C) 1999 Andreas E. Bombe&n; * Copyright (C) 1999 Emanuel Pirker&n; *&n; * This code is licensed under the GPL.  See the file COPYING in the root&n; * directory of the kernel sources for details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &quot;csr1212.h&quot;
macro_line|#include &quot;ieee1394.h&quot;
macro_line|#include &quot;ieee1394_types.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;ieee1394_core.h&quot;
macro_line|#include &quot;highlevel.h&quot;
macro_line|#include &quot;nodemgr.h&quot;
macro_line|#include &quot;csr.h&quot;
DECL|function|delayed_reset_bus
r_static
r_void
id|delayed_reset_bus
c_func
(paren
r_int
r_int
id|__reset_info
)paren
(brace
r_struct
id|hpsb_host
op_star
id|host
op_assign
(paren
r_struct
id|hpsb_host
op_star
)paren
id|__reset_info
suffix:semicolon
r_int
id|generation
op_assign
id|host-&gt;csr.generation
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* The generation field rolls over to 2 rather than 0 per IEEE&n;&t; * 1394a-2000. */
r_if
c_cond
(paren
id|generation
OG
l_int|0xf
op_logical_or
id|generation
OL
l_int|2
)paren
id|generation
op_assign
l_int|2
suffix:semicolon
id|CSR_SET_BUS_INFO_GENERATION
c_func
(paren
id|host-&gt;csr.rom
comma
id|generation
)paren
suffix:semicolon
r_if
c_cond
(paren
id|csr1212_generate_csr_image
c_func
(paren
id|host-&gt;csr.rom
)paren
op_ne
id|CSR1212_SUCCESS
)paren
(brace
multiline_comment|/* CSR image creation failed, reset generation field and do not&n;&t;&t; * issue a bus reset. */
id|CSR_SET_BUS_INFO_GENERATION
c_func
(paren
id|host-&gt;csr.rom
comma
id|host-&gt;csr.generation
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|host-&gt;csr.generation
op_assign
id|generation
suffix:semicolon
id|host-&gt;update_config_rom
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;driver-&gt;set_hw_config_rom
)paren
id|host-&gt;driver
op_member_access_from_pointer
id|set_hw_config_rom
c_func
(paren
id|host
comma
id|host-&gt;csr.rom-&gt;bus_info_data
)paren
suffix:semicolon
id|host-&gt;csr.gen_timestamp
(braket
id|host-&gt;csr.generation
)braket
op_assign
id|jiffies
suffix:semicolon
id|hpsb_reset_bus
c_func
(paren
id|host
comma
id|SHORT_RESET
)paren
suffix:semicolon
)brace
DECL|function|dummy_transmit_packet
r_static
r_int
id|dummy_transmit_packet
c_func
(paren
r_struct
id|hpsb_host
op_star
id|h
comma
r_struct
id|hpsb_packet
op_star
id|p
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_devctl
r_static
r_int
id|dummy_devctl
c_func
(paren
r_struct
id|hpsb_host
op_star
id|h
comma
r_enum
id|devctl_cmd
id|c
comma
r_int
id|arg
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|dummy_isoctl
r_static
r_int
id|dummy_isoctl
c_func
(paren
r_struct
id|hpsb_iso
op_star
id|iso
comma
r_enum
id|isoctl_cmd
id|command
comma
r_int
r_int
id|arg
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|dummy_driver
r_static
r_struct
id|hpsb_host_driver
id|dummy_driver
op_assign
(brace
dot
id|transmit_packet
op_assign
id|dummy_transmit_packet
comma
dot
id|devctl
op_assign
id|dummy_devctl
comma
dot
id|isoctl
op_assign
id|dummy_isoctl
)brace
suffix:semicolon
DECL|function|alloc_hostnum_cb
r_static
r_int
id|alloc_hostnum_cb
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_void
op_star
id|__data
)paren
(brace
r_int
op_star
id|hostnum
op_assign
id|__data
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;id
op_eq
op_star
id|hostnum
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * hpsb_alloc_host - allocate a new host controller.&n; * @drv: the driver that will manage the host controller&n; * @extra: number of extra bytes to allocate for the driver&n; *&n; * Allocate a &amp;hpsb_host and initialize the general subsystem specific&n; * fields.  If the driver needs to store per host data, as drivers&n; * usually do, the amount of memory required can be specified by the&n; * @extra parameter.  Once allocated, the driver should initialize the&n; * driver specific parts, enable the controller and make it available&n; * to the general subsystem using hpsb_add_host().&n; *&n; * Return Value: a pointer to the &amp;hpsb_host if succesful, %NULL if&n; * no memory was available.&n; */
DECL|function|hpsb_alloc_host
r_struct
id|hpsb_host
op_star
id|hpsb_alloc_host
c_func
(paren
r_struct
id|hpsb_host_driver
op_star
id|drv
comma
r_int
id|extra
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|hpsb_host
op_star
id|h
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|hostnum
op_assign
l_int|0
suffix:semicolon
id|h
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hpsb_host
)paren
op_plus
id|extra
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|h
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|h
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|hpsb_host
)paren
op_plus
id|extra
)paren
suffix:semicolon
id|h-&gt;csr.rom
op_assign
id|csr1212_create_csr
c_func
(paren
op_amp
id|csr_bus_ops
comma
id|CSR_BUS_INFO_SIZE
comma
id|h
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|h-&gt;csr.rom
)paren
(brace
id|kfree
c_func
(paren
id|h
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|h-&gt;hostdata
op_assign
id|h
op_plus
l_int|1
suffix:semicolon
id|h-&gt;driver
op_assign
id|drv
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|h-&gt;pending_packets
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|h-&gt;pending_pkt_lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|h-&gt;addr_space
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|h-&gt;delayed_reset
)paren
suffix:semicolon
id|h-&gt;delayed_reset.function
op_assign
id|delayed_reset_bus
suffix:semicolon
id|h-&gt;delayed_reset.data
op_assign
(paren
r_int
r_int
)paren
id|h
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|h-&gt;csr.gen_timestamp
(braket
id|i
)braket
op_assign
id|jiffies
op_minus
l_int|60
op_star
id|HZ
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
id|ARRAY_SIZE
c_func
(paren
id|h-&gt;tpool
)paren
suffix:semicolon
id|i
op_increment
)paren
id|HPSB_TPOOL_INIT
c_func
(paren
op_amp
id|h-&gt;tpool
(braket
id|i
)braket
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|h-&gt;generation
comma
l_int|0
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|h-&gt;timeout
)paren
suffix:semicolon
id|h-&gt;timeout.data
op_assign
(paren
r_int
r_int
)paren
id|h
suffix:semicolon
id|h-&gt;timeout.function
op_assign
id|abort_timedouts
suffix:semicolon
id|h-&gt;timeout_interval
op_assign
id|HZ
op_div
l_int|20
suffix:semicolon
singleline_comment|// 50ms by default
id|h-&gt;topology_map
op_assign
id|h-&gt;csr.topology_map
op_plus
l_int|3
suffix:semicolon
id|h-&gt;speed_map
op_assign
(paren
id|u8
op_star
)paren
(paren
id|h-&gt;csr.speed_map
op_plus
l_int|2
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|nodemgr_for_each_host
c_func
(paren
op_amp
id|hostnum
comma
id|alloc_hostnum_cb
)paren
)paren
(brace
id|h-&gt;id
op_assign
id|hostnum
suffix:semicolon
r_break
suffix:semicolon
)brace
id|hostnum
op_increment
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|h-&gt;device
comma
op_amp
id|nodemgr_dev_template_host
comma
r_sizeof
(paren
id|h-&gt;device
)paren
)paren
suffix:semicolon
id|h-&gt;device.parent
op_assign
id|dev
suffix:semicolon
id|snprintf
c_func
(paren
id|h-&gt;device.bus_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;fw-host%d&quot;
comma
id|h-&gt;id
)paren
suffix:semicolon
id|h-&gt;class_dev.dev
op_assign
op_amp
id|h-&gt;device
suffix:semicolon
id|h-&gt;class_dev
dot
r_class
op_assign
op_amp
id|hpsb_host_class
suffix:semicolon
id|snprintf
c_func
(paren
id|h-&gt;class_dev.class_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;fw-host%d&quot;
comma
id|h-&gt;id
)paren
suffix:semicolon
id|device_register
c_func
(paren
op_amp
id|h-&gt;device
)paren
suffix:semicolon
id|class_device_register
c_func
(paren
op_amp
id|h-&gt;class_dev
)paren
suffix:semicolon
id|get_device
c_func
(paren
op_amp
id|h-&gt;device
)paren
suffix:semicolon
r_return
id|h
suffix:semicolon
)brace
DECL|function|hpsb_add_host
r_void
id|hpsb_add_host
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
id|highlevel_add_host
c_func
(paren
id|host
)paren
suffix:semicolon
)brace
DECL|function|hpsb_remove_host
r_void
id|hpsb_remove_host
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
id|host-&gt;is_shutdown
op_assign
l_int|1
suffix:semicolon
id|host-&gt;driver
op_assign
op_amp
id|dummy_driver
suffix:semicolon
id|highlevel_remove_host
c_func
(paren
id|host
)paren
suffix:semicolon
id|class_device_unregister
c_func
(paren
op_amp
id|host-&gt;class_dev
)paren
suffix:semicolon
id|device_unregister
c_func
(paren
op_amp
id|host-&gt;device
)paren
suffix:semicolon
)brace
DECL|function|hpsb_update_config_rom_image
r_int
id|hpsb_update_config_rom_image
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
r_int
r_int
id|reset_time
suffix:semicolon
r_int
id|next_gen
op_assign
id|host-&gt;csr.generation
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host-&gt;update_config_rom
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|next_gen
OG
l_int|0xf
)paren
id|next_gen
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* Stop the delayed interrupt, we&squot;re about to change the config rom and&n;&t; * it would be a waste to do a bus reset twice. */
id|del_timer_sync
c_func
(paren
op_amp
id|host-&gt;delayed_reset
)paren
suffix:semicolon
multiline_comment|/* IEEE 1394a-2000 prohibits using the same generation number&n;&t; * twice in a 60 second period. */
r_if
c_cond
(paren
id|jiffies
op_minus
id|host-&gt;csr.gen_timestamp
(braket
id|next_gen
)braket
OL
l_int|60
op_star
id|HZ
)paren
multiline_comment|/* Wait 60 seconds from the last time this generation number was&n;&t;&t; * used. */
id|reset_time
op_assign
(paren
l_int|60
op_star
id|HZ
)paren
op_plus
id|host-&gt;csr.gen_timestamp
(braket
id|next_gen
)braket
suffix:semicolon
r_else
multiline_comment|/* Wait 1 second in case some other code wants to change the&n;&t;&t; * Config ROM in the near future. */
id|reset_time
op_assign
id|jiffies
op_plus
id|HZ
suffix:semicolon
multiline_comment|/* This will add the timer as well as modify it */
id|mod_timer
c_func
(paren
op_amp
id|host-&gt;delayed_reset
comma
id|reset_time
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
