multiline_comment|/*&n; * I2O kernel space accessible structures/APIs&n; * &n; * (c) Copyright 1999, 2000 Red Hat Software&n; *&n; * This program is free software; you can redistribute it and/or &n; * modify it under the terms of the GNU General Public License &n; * as published by the Free Software Foundation; either version &n; * 2 of the License, or (at your option) any later version.  &n; * &n; *************************************************************************&n; *&n; * This header file defined the I2O APIs/structures for use by &n; * the I2O kernel modules.&n; *&n; */
macro_line|#ifndef _I2O_H
DECL|macro|_I2O_H
mdefine_line|#define _I2O_H
macro_line|#ifdef __KERNEL__&t;/* This file to be included by kernel only */
macro_line|#include &lt;linux/i2o-dev.h&gt;
multiline_comment|/* How many different OSM&squot;s are we allowing */
DECL|macro|MAX_I2O_MODULES
mdefine_line|#define MAX_I2O_MODULES&t;&t;64
multiline_comment|/* How many OSMs can register themselves for device status updates? */
DECL|macro|I2O_MAX_MANAGERS
mdefine_line|#define I2O_MAX_MANAGERS&t;4
macro_line|#include &lt;asm/semaphore.h&gt; /* Needed for MUTEX init macros */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * message structures&n; */
DECL|struct|i2o_message
r_struct
id|i2o_message
(brace
DECL|member|version_offset
id|u8
id|version_offset
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|size
id|u16
id|size
suffix:semicolon
DECL|member|target_tid
id|u32
id|target_tid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|init_tid
id|u32
id|init_tid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|function
id|u32
id|function
suffix:colon
l_int|8
suffix:semicolon
DECL|member|initiator_context
id|u32
id|initiator_context
suffix:semicolon
multiline_comment|/* List follows */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Each I2O device entity has one or more of these. There is one&n; *&t;per device.&n; */
DECL|struct|i2o_device
r_struct
id|i2o_device
(brace
DECL|member|lct_data
id|i2o_lct_entry
id|lct_data
suffix:semicolon
multiline_comment|/* Device LCT information */
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|i2oversion
r_int
id|i2oversion
suffix:semicolon
multiline_comment|/* I2O version supported. Actually there&n;&t;&t;&t;&t; * should be high and low version */
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
multiline_comment|/* /proc dir */
multiline_comment|/* Primary user */
DECL|member|owner
r_struct
id|i2o_handler
op_star
id|owner
suffix:semicolon
multiline_comment|/* Management users */
DECL|member|managers
r_struct
id|i2o_handler
op_star
id|managers
(braket
id|I2O_MAX_MANAGERS
)braket
suffix:semicolon
DECL|member|num_managers
r_int
id|num_managers
suffix:semicolon
DECL|member|controller
r_struct
id|i2o_controller
op_star
id|controller
suffix:semicolon
multiline_comment|/* Controlling IOP */
DECL|member|next
r_struct
id|i2o_device
op_star
id|next
suffix:semicolon
multiline_comment|/* Chain */
DECL|member|prev
r_struct
id|i2o_device
op_star
id|prev
suffix:semicolon
DECL|member|dev_name
r_char
id|dev_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* linux /dev name if available */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Resource data for each PCI I2O controller&n; */
DECL|struct|i2o_pci
r_struct
id|i2o_pci
(brace
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
multiline_comment|/* PCI device */
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|queue_buggy
r_int
id|queue_buggy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Don&squot;t send a lot of messages */
DECL|member|short_req
r_int
id|short_req
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Use small block sizes&t;*/
DECL|member|dpt
r_int
id|dpt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Don&squot;t quiesce&t;&t;*/
macro_line|#ifdef CONFIG_MTRR
DECL|member|mtrr_reg0
r_int
id|mtrr_reg0
suffix:semicolon
DECL|member|mtrr_reg1
r_int
id|mtrr_reg1
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; * Transport types supported by I2O stack&n; */
DECL|macro|I2O_TYPE_PCI
mdefine_line|#define I2O_TYPE_PCI&t;&t;0x01&t;&t;/* PCI I2O controller */&t;
multiline_comment|/*&n; * Each I2O controller has one of these objects&n; */
DECL|struct|i2o_controller
r_struct
id|i2o_controller
(brace
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|unit
r_int
id|unit
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|enabled
r_int
id|enabled
suffix:semicolon
DECL|member|event_notifer
r_struct
id|notifier_block
op_star
id|event_notifer
suffix:semicolon
multiline_comment|/* Events */
DECL|member|users
id|atomic_t
id|users
suffix:semicolon
DECL|member|devices
r_struct
id|i2o_device
op_star
id|devices
suffix:semicolon
multiline_comment|/* I2O device chain */
DECL|member|next
r_struct
id|i2o_controller
op_star
id|next
suffix:semicolon
multiline_comment|/* Controller chain */
DECL|member|post_port
r_volatile
id|u32
op_star
id|post_port
suffix:semicolon
multiline_comment|/* Inbout port */
DECL|member|reply_port
r_volatile
id|u32
op_star
id|reply_port
suffix:semicolon
multiline_comment|/* Outbound port */
DECL|member|irq_mask
r_volatile
id|u32
op_star
id|irq_mask
suffix:semicolon
multiline_comment|/* Interrupt register */
multiline_comment|/* Dynamic LCT related data */
DECL|member|lct_sem
r_struct
id|semaphore
id|lct_sem
suffix:semicolon
DECL|member|lct_pid
r_int
id|lct_pid
suffix:semicolon
DECL|member|lct_running
r_int
id|lct_running
suffix:semicolon
DECL|member|status_block
id|i2o_status_block
op_star
id|status_block
suffix:semicolon
multiline_comment|/* IOP status block */
DECL|member|lct
id|i2o_lct
op_star
id|lct
suffix:semicolon
multiline_comment|/* Logical Config Table */
DECL|member|dlct
id|i2o_lct
op_star
id|dlct
suffix:semicolon
multiline_comment|/* Temp LCT */
DECL|member|hrt
id|i2o_hrt
op_star
id|hrt
suffix:semicolon
multiline_comment|/* HW Resource Table */
DECL|member|mem_offset
id|u32
id|mem_offset
suffix:semicolon
multiline_comment|/* MFA offset */
DECL|member|mem_phys
id|u32
id|mem_phys
suffix:semicolon
multiline_comment|/* MFA physical */
DECL|member|battery
r_int
id|battery
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Has a battery backup */
DECL|member|io_alloc
r_int
id|io_alloc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* An I/O resource was allocated */
DECL|member|mem_alloc
r_int
id|mem_alloc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* A memory resource was allocated */
DECL|member|io_resource
r_struct
id|resource
id|io_resource
suffix:semicolon
multiline_comment|/* I/O resource allocated to the IOP */
DECL|member|mem_resource
r_struct
id|resource
id|mem_resource
suffix:semicolon
multiline_comment|/* Mem resource allocated to the IOP */
DECL|member|proc_entry
r_struct
id|proc_dir_entry
op_star
id|proc_entry
suffix:semicolon
multiline_comment|/* /proc dir */
r_union
(brace
multiline_comment|/* Bus information */
DECL|member|pci
r_struct
id|i2o_pci
id|pci
suffix:semicolon
DECL|member|bus
)brace
id|bus
suffix:semicolon
multiline_comment|/* Bus specific destructor */
DECL|member|destructor
r_void
(paren
op_star
id|destructor
)paren
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
multiline_comment|/* Bus specific attach/detach */
DECL|member|bind
r_int
(paren
op_star
id|bind
)paren
(paren
r_struct
id|i2o_controller
op_star
comma
r_struct
id|i2o_device
op_star
)paren
suffix:semicolon
multiline_comment|/* Bus specific initiator */
DECL|member|unbind
r_int
(paren
op_star
id|unbind
)paren
(paren
r_struct
id|i2o_controller
op_star
comma
r_struct
id|i2o_device
op_star
)paren
suffix:semicolon
multiline_comment|/* Bus specific enable/disable */
DECL|member|bus_enable
r_void
(paren
op_star
id|bus_enable
)paren
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
suffix:semicolon
DECL|member|bus_disable
r_void
(paren
op_star
id|bus_disable
)paren
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
suffix:semicolon
DECL|member|page_frame
r_void
op_star
id|page_frame
suffix:semicolon
multiline_comment|/* Message buffers */
)brace
suffix:semicolon
multiline_comment|/*&n; * OSM resgistration block&n; *&n; * Each OSM creates at least one of these and registers it with the&n; * I2O core through i2o_register_handler.  An OSM may want to&n; * register more than one if it wants a fast path to a reply&n; * handler by having a separate initiator context for each &n; * class function.&n; */
DECL|struct|i2o_handler
r_struct
id|i2o_handler
(brace
multiline_comment|/* Message reply handler */
DECL|member|reply
r_void
(paren
op_star
id|reply
)paren
(paren
r_struct
id|i2o_handler
op_star
comma
r_struct
id|i2o_controller
op_star
comma
r_struct
id|i2o_message
op_star
)paren
suffix:semicolon
multiline_comment|/* New device notification handler */
DECL|member|new_dev_notify
r_void
(paren
op_star
id|new_dev_notify
)paren
(paren
r_struct
id|i2o_controller
op_star
comma
r_struct
id|i2o_device
op_star
)paren
suffix:semicolon
multiline_comment|/* Device deltion handler */
DECL|member|dev_del_notify
r_void
(paren
op_star
id|dev_del_notify
)paren
(paren
r_struct
id|i2o_controller
op_star
comma
r_struct
id|i2o_device
op_star
)paren
suffix:semicolon
multiline_comment|/* Reboot notification handler */
DECL|member|reboot_notify
r_void
(paren
op_star
id|reboot_notify
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* OSM name */
DECL|member|context
r_int
id|context
suffix:semicolon
multiline_comment|/* Low 8 bits of the transaction info */
DECL|member|class
id|u32
r_class
suffix:semicolon
multiline_comment|/* I2O classes that this driver handles */
multiline_comment|/* User data follows */
)brace
suffix:semicolon
macro_line|#ifdef MODULE
multiline_comment|/*&n; * Used by bus specific modules to communicate with the core&n; *&n; * This is needed because the bus modules cannot make direct&n; * calls to the core as this results in the i2o_bus_specific_module&n; * being dependent on the core, not the otherway around.&n; * In that case, a &squot;modprobe i2o_lan&squot; loads i2o_core &amp; i2o_lan,&n; * but _not_ i2o_pci...which makes the whole thing pretty useless :)&n; *&n; */
DECL|struct|i2o_core_func_table
r_struct
id|i2o_core_func_table
(brace
DECL|member|install
r_int
(paren
op_star
id|install
)paren
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
DECL|member|activate
r_int
(paren
op_star
id|activate
)paren
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
DECL|member|find
r_struct
id|i2o_controller
op_star
(paren
op_star
id|find
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|unlock
r_void
(paren
op_star
id|unlock
)paren
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
DECL|member|run_queue
r_void
(paren
op_star
id|run_queue
)paren
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
suffix:semicolon
DECL|member|delete
r_int
(paren
op_star
r_delete
)paren
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif 
singleline_comment|// MODULE
multiline_comment|/*&n; * I2O System table entry&n; *&n; * The system table contains information about all the IOPs in the&n; * system.  It is sent to all IOPs so that they can create peer2peer&n; * connections between them.&n; */
DECL|struct|i2o_sys_tbl_entry
r_struct
id|i2o_sys_tbl_entry
(brace
DECL|member|org_id
id|u16
id|org_id
suffix:semicolon
DECL|member|reserved1
id|u16
id|reserved1
suffix:semicolon
DECL|member|iop_id
id|u32
id|iop_id
suffix:colon
l_int|12
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:colon
l_int|20
suffix:semicolon
DECL|member|seg_num
id|u16
id|seg_num
suffix:colon
l_int|12
suffix:semicolon
DECL|member|i2o_version
id|u16
id|i2o_version
suffix:colon
l_int|4
suffix:semicolon
DECL|member|iop_state
id|u8
id|iop_state
suffix:semicolon
DECL|member|msg_type
id|u8
id|msg_type
suffix:semicolon
DECL|member|frame_size
id|u16
id|frame_size
suffix:semicolon
DECL|member|reserved3
id|u16
id|reserved3
suffix:semicolon
DECL|member|last_changed
id|u32
id|last_changed
suffix:semicolon
DECL|member|iop_capabilities
id|u32
id|iop_capabilities
suffix:semicolon
DECL|member|inbound_low
id|u32
id|inbound_low
suffix:semicolon
DECL|member|inbound_high
id|u32
id|inbound_high
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|i2o_sys_tbl
r_struct
id|i2o_sys_tbl
(brace
DECL|member|num_entries
id|u8
id|num_entries
suffix:semicolon
DECL|member|version
id|u8
id|version
suffix:semicolon
DECL|member|reserved1
id|u16
id|reserved1
suffix:semicolon
DECL|member|change_ind
id|u32
id|change_ind
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|iops
r_struct
id|i2o_sys_tbl_entry
id|iops
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Messenger inlines&n; */
DECL|function|I2O_POST_READ32
r_static
r_inline
id|u32
id|I2O_POST_READ32
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
(brace
r_return
op_star
id|c-&gt;post_port
suffix:semicolon
)brace
DECL|function|I2O_POST_WRITE32
r_static
r_inline
r_void
id|I2O_POST_WRITE32
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|Val
)paren
(brace
op_star
id|c-&gt;post_port
op_assign
id|Val
suffix:semicolon
)brace
DECL|function|I2O_REPLY_READ32
r_static
r_inline
id|u32
id|I2O_REPLY_READ32
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
(brace
r_return
op_star
id|c-&gt;reply_port
suffix:semicolon
)brace
DECL|function|I2O_REPLY_WRITE32
r_static
r_inline
r_void
id|I2O_REPLY_WRITE32
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|Val
)paren
(brace
op_star
id|c-&gt;reply_port
op_assign
id|Val
suffix:semicolon
)brace
DECL|function|I2O_IRQ_READ32
r_static
r_inline
id|u32
id|I2O_IRQ_READ32
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
(brace
r_return
op_star
id|c-&gt;irq_mask
suffix:semicolon
)brace
DECL|function|I2O_IRQ_WRITE32
r_static
r_inline
r_void
id|I2O_IRQ_WRITE32
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|Val
)paren
(brace
op_star
id|c-&gt;irq_mask
op_assign
id|Val
suffix:semicolon
)brace
DECL|function|i2o_post_message
r_static
r_inline
r_void
id|i2o_post_message
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|m
)paren
(brace
multiline_comment|/* The second line isnt spurious - thats forcing PCI posting */
id|I2O_POST_WRITE32
c_func
(paren
id|c
comma
id|m
)paren
suffix:semicolon
(paren
r_void
)paren
id|I2O_IRQ_READ32
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
DECL|function|i2o_flush_reply
r_static
r_inline
r_void
id|i2o_flush_reply
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|m
)paren
(brace
id|I2O_REPLY_WRITE32
c_func
(paren
id|c
comma
id|m
)paren
suffix:semicolon
)brace
r_extern
r_struct
id|i2o_controller
op_star
id|i2o_find_controller
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|i2o_unlock_controller
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|i2o_controller
op_star
id|i2o_controller_chain
suffix:semicolon
r_extern
r_int
id|i2o_num_controllers
suffix:semicolon
r_extern
r_int
id|i2o_status_get
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_install_handler
c_func
(paren
r_struct
id|i2o_handler
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_remove_handler
c_func
(paren
r_struct
id|i2o_handler
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_claim_device
c_func
(paren
r_struct
id|i2o_device
op_star
comma
r_struct
id|i2o_handler
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_release_device
c_func
(paren
r_struct
id|i2o_device
op_star
comma
r_struct
id|i2o_handler
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_device_notify_on
c_func
(paren
r_struct
id|i2o_device
op_star
comma
r_struct
id|i2o_handler
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_device_notify_off
c_func
(paren
r_struct
id|i2o_device
op_star
comma
r_struct
id|i2o_handler
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_post_this
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
id|u32
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2o_post_wait
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
id|u32
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2o_post_wait_mem
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
id|u32
op_star
comma
r_int
comma
r_int
comma
r_void
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_query_scalar
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2o_set_scalar
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2o_query_table
c_func
(paren
r_int
comma
r_struct
id|i2o_controller
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_void
op_star
comma
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2o_clear_table
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2o_row_add_table
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2o_issue_params
c_func
(paren
r_int
comma
r_struct
id|i2o_controller
op_star
comma
r_int
comma
r_void
op_star
comma
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2o_event_register
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
id|u32
comma
id|u32
comma
id|u32
comma
id|u32
)paren
suffix:semicolon
r_extern
r_int
id|i2o_event_ack
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2o_report_status
c_func
(paren
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
id|u32
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2o_dump_message
c_func
(paren
id|u32
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|i2o_get_class_name
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2o_install_controller
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_activate_controller
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2o_run_queue
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_delete_controller
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * I2O Function codes&n; */
multiline_comment|/*&n; * Executive Class&n; */
DECL|macro|I2O_CMD_ADAPTER_ASSIGN
mdefine_line|#define&t;I2O_CMD_ADAPTER_ASSIGN&t;&t;0xB3
DECL|macro|I2O_CMD_ADAPTER_READ
mdefine_line|#define&t;I2O_CMD_ADAPTER_READ&t;&t;0xB2
DECL|macro|I2O_CMD_ADAPTER_RELEASE
mdefine_line|#define&t;I2O_CMD_ADAPTER_RELEASE&t;&t;0xB5
DECL|macro|I2O_CMD_BIOS_INFO_SET
mdefine_line|#define&t;I2O_CMD_BIOS_INFO_SET&t;&t;0xA5
DECL|macro|I2O_CMD_BOOT_DEVICE_SET
mdefine_line|#define&t;I2O_CMD_BOOT_DEVICE_SET&t;&t;0xA7
DECL|macro|I2O_CMD_CONFIG_VALIDATE
mdefine_line|#define&t;I2O_CMD_CONFIG_VALIDATE&t;&t;0xBB
DECL|macro|I2O_CMD_CONN_SETUP
mdefine_line|#define&t;I2O_CMD_CONN_SETUP&t;&t;0xCA
DECL|macro|I2O_CMD_DDM_DESTROY
mdefine_line|#define&t;I2O_CMD_DDM_DESTROY&t;&t;0xB1
DECL|macro|I2O_CMD_DDM_ENABLE
mdefine_line|#define&t;I2O_CMD_DDM_ENABLE&t;&t;0xD5
DECL|macro|I2O_CMD_DDM_QUIESCE
mdefine_line|#define&t;I2O_CMD_DDM_QUIESCE&t;&t;0xC7
DECL|macro|I2O_CMD_DDM_RESET
mdefine_line|#define&t;I2O_CMD_DDM_RESET&t;&t;0xD9
DECL|macro|I2O_CMD_DDM_SUSPEND
mdefine_line|#define&t;I2O_CMD_DDM_SUSPEND&t;&t;0xAF
DECL|macro|I2O_CMD_DEVICE_ASSIGN
mdefine_line|#define&t;I2O_CMD_DEVICE_ASSIGN&t;&t;0xB7
DECL|macro|I2O_CMD_DEVICE_RELEASE
mdefine_line|#define&t;I2O_CMD_DEVICE_RELEASE&t;&t;0xB9
DECL|macro|I2O_CMD_HRT_GET
mdefine_line|#define&t;I2O_CMD_HRT_GET&t;&t;&t;0xA8
DECL|macro|I2O_CMD_ADAPTER_CLEAR
mdefine_line|#define&t;I2O_CMD_ADAPTER_CLEAR&t;&t;0xBE
DECL|macro|I2O_CMD_ADAPTER_CONNECT
mdefine_line|#define&t;I2O_CMD_ADAPTER_CONNECT&t;&t;0xC9
DECL|macro|I2O_CMD_ADAPTER_RESET
mdefine_line|#define&t;I2O_CMD_ADAPTER_RESET&t;&t;0xBD
DECL|macro|I2O_CMD_LCT_NOTIFY
mdefine_line|#define&t;I2O_CMD_LCT_NOTIFY&t;&t;0xA2
DECL|macro|I2O_CMD_OUTBOUND_INIT
mdefine_line|#define&t;I2O_CMD_OUTBOUND_INIT&t;&t;0xA1
DECL|macro|I2O_CMD_PATH_ENABLE
mdefine_line|#define&t;I2O_CMD_PATH_ENABLE&t;&t;0xD3
DECL|macro|I2O_CMD_PATH_QUIESCE
mdefine_line|#define&t;I2O_CMD_PATH_QUIESCE&t;&t;0xC5
DECL|macro|I2O_CMD_PATH_RESET
mdefine_line|#define&t;I2O_CMD_PATH_RESET&t;&t;0xD7
DECL|macro|I2O_CMD_STATIC_MF_CREATE
mdefine_line|#define&t;I2O_CMD_STATIC_MF_CREATE&t;0xDD
DECL|macro|I2O_CMD_STATIC_MF_RELEASE
mdefine_line|#define&t;I2O_CMD_STATIC_MF_RELEASE&t;0xDF
DECL|macro|I2O_CMD_STATUS_GET
mdefine_line|#define&t;I2O_CMD_STATUS_GET&t;&t;0xA0
DECL|macro|I2O_CMD_SW_DOWNLOAD
mdefine_line|#define&t;I2O_CMD_SW_DOWNLOAD&t;&t;0xA9
DECL|macro|I2O_CMD_SW_UPLOAD
mdefine_line|#define&t;I2O_CMD_SW_UPLOAD&t;&t;0xAB
DECL|macro|I2O_CMD_SW_REMOVE
mdefine_line|#define&t;I2O_CMD_SW_REMOVE&t;&t;0xAD
DECL|macro|I2O_CMD_SYS_ENABLE
mdefine_line|#define&t;I2O_CMD_SYS_ENABLE&t;&t;0xD1
DECL|macro|I2O_CMD_SYS_MODIFY
mdefine_line|#define&t;I2O_CMD_SYS_MODIFY&t;&t;0xC1
DECL|macro|I2O_CMD_SYS_QUIESCE
mdefine_line|#define&t;I2O_CMD_SYS_QUIESCE&t;&t;0xC3
DECL|macro|I2O_CMD_SYS_TAB_SET
mdefine_line|#define&t;I2O_CMD_SYS_TAB_SET&t;&t;0xA3
multiline_comment|/*&n; * Utility Class&n; */
DECL|macro|I2O_CMD_UTIL_NOP
mdefine_line|#define I2O_CMD_UTIL_NOP&t;&t;0x00
DECL|macro|I2O_CMD_UTIL_ABORT
mdefine_line|#define I2O_CMD_UTIL_ABORT&t;&t;0x01
DECL|macro|I2O_CMD_UTIL_CLAIM
mdefine_line|#define I2O_CMD_UTIL_CLAIM&t;&t;0x09
DECL|macro|I2O_CMD_UTIL_RELEASE
mdefine_line|#define I2O_CMD_UTIL_RELEASE&t;&t;0x0B
DECL|macro|I2O_CMD_UTIL_PARAMS_GET
mdefine_line|#define I2O_CMD_UTIL_PARAMS_GET&t;&t;0x06
DECL|macro|I2O_CMD_UTIL_PARAMS_SET
mdefine_line|#define I2O_CMD_UTIL_PARAMS_SET&t;&t;0x05
DECL|macro|I2O_CMD_UTIL_EVT_REGISTER
mdefine_line|#define I2O_CMD_UTIL_EVT_REGISTER&t;0x13
DECL|macro|I2O_CMD_UTIL_EVT_ACK
mdefine_line|#define I2O_CMD_UTIL_EVT_ACK&t;&t;0x14
DECL|macro|I2O_CMD_UTIL_CONFIG_DIALOG
mdefine_line|#define I2O_CMD_UTIL_CONFIG_DIALOG&t;0x10
DECL|macro|I2O_CMD_UTIL_DEVICE_RESERVE
mdefine_line|#define I2O_CMD_UTIL_DEVICE_RESERVE&t;0x0D
DECL|macro|I2O_CMD_UTIL_DEVICE_RELEASE
mdefine_line|#define I2O_CMD_UTIL_DEVICE_RELEASE&t;0x0F
DECL|macro|I2O_CMD_UTIL_LOCK
mdefine_line|#define I2O_CMD_UTIL_LOCK&t;&t;0x17
DECL|macro|I2O_CMD_UTIL_LOCK_RELEASE
mdefine_line|#define I2O_CMD_UTIL_LOCK_RELEASE&t;0x19
DECL|macro|I2O_CMD_UTIL_REPLY_FAULT_NOTIFY
mdefine_line|#define I2O_CMD_UTIL_REPLY_FAULT_NOTIFY&t;0x15
multiline_comment|/*&n; * SCSI Host Bus Adapter Class&n; */
DECL|macro|I2O_CMD_SCSI_EXEC
mdefine_line|#define I2O_CMD_SCSI_EXEC&t;&t;0x81
DECL|macro|I2O_CMD_SCSI_ABORT
mdefine_line|#define I2O_CMD_SCSI_ABORT&t;&t;0x83
DECL|macro|I2O_CMD_SCSI_BUSRESET
mdefine_line|#define I2O_CMD_SCSI_BUSRESET&t;&t;0x27
multiline_comment|/*&n; * Random Block Storage Class&n; */
DECL|macro|I2O_CMD_BLOCK_READ
mdefine_line|#define I2O_CMD_BLOCK_READ&t;&t;0x30
DECL|macro|I2O_CMD_BLOCK_WRITE
mdefine_line|#define I2O_CMD_BLOCK_WRITE&t;&t;0x31
DECL|macro|I2O_CMD_BLOCK_CFLUSH
mdefine_line|#define I2O_CMD_BLOCK_CFLUSH&t;&t;0x37
DECL|macro|I2O_CMD_BLOCK_MLOCK
mdefine_line|#define I2O_CMD_BLOCK_MLOCK&t;&t;0x49
DECL|macro|I2O_CMD_BLOCK_MUNLOCK
mdefine_line|#define I2O_CMD_BLOCK_MUNLOCK&t;&t;0x4B
DECL|macro|I2O_CMD_BLOCK_MMOUNT
mdefine_line|#define I2O_CMD_BLOCK_MMOUNT&t;&t;0x41
DECL|macro|I2O_CMD_BLOCK_MEJECT
mdefine_line|#define I2O_CMD_BLOCK_MEJECT&t;&t;0x43
DECL|macro|I2O_PRIVATE_MSG
mdefine_line|#define I2O_PRIVATE_MSG&t;&t;&t;0xFF
multiline_comment|/* Command status values  */
DECL|macro|I2O_CMD_IN_PROGRESS
mdefine_line|#define I2O_CMD_IN_PROGRESS&t;0x01
DECL|macro|I2O_CMD_REJECTED
mdefine_line|#define I2O_CMD_REJECTED&t;0x02
DECL|macro|I2O_CMD_FAILED
mdefine_line|#define I2O_CMD_FAILED&t;&t;0x03
DECL|macro|I2O_CMD_COMPLETED
mdefine_line|#define I2O_CMD_COMPLETED&t;0x04
multiline_comment|/* I2O API function return values */
DECL|macro|I2O_RTN_NO_ERROR
mdefine_line|#define I2O_RTN_NO_ERROR&t;&t;&t;0
DECL|macro|I2O_RTN_NOT_INIT
mdefine_line|#define I2O_RTN_NOT_INIT&t;&t;&t;1
DECL|macro|I2O_RTN_FREE_Q_EMPTY
mdefine_line|#define I2O_RTN_FREE_Q_EMPTY&t;&t;&t;2
DECL|macro|I2O_RTN_TCB_ERROR
mdefine_line|#define I2O_RTN_TCB_ERROR&t;&t;&t;3
DECL|macro|I2O_RTN_TRANSACTION_ERROR
mdefine_line|#define I2O_RTN_TRANSACTION_ERROR&t;&t;4
DECL|macro|I2O_RTN_ADAPTER_ALREADY_INIT
mdefine_line|#define I2O_RTN_ADAPTER_ALREADY_INIT&t;&t;5
DECL|macro|I2O_RTN_MALLOC_ERROR
mdefine_line|#define I2O_RTN_MALLOC_ERROR&t;&t;&t;6
DECL|macro|I2O_RTN_ADPTR_NOT_REGISTERED
mdefine_line|#define I2O_RTN_ADPTR_NOT_REGISTERED&t;&t;7
DECL|macro|I2O_RTN_MSG_REPLY_TIMEOUT
mdefine_line|#define I2O_RTN_MSG_REPLY_TIMEOUT&t;&t;8
DECL|macro|I2O_RTN_NO_STATUS
mdefine_line|#define I2O_RTN_NO_STATUS&t;&t;&t;9
DECL|macro|I2O_RTN_NO_FIRM_VER
mdefine_line|#define I2O_RTN_NO_FIRM_VER&t;&t;&t;10
DECL|macro|I2O_RTN_NO_LINK_SPEED
mdefine_line|#define&t;I2O_RTN_NO_LINK_SPEED&t;&t;&t;11
multiline_comment|/* Reply message status defines for all messages */
DECL|macro|I2O_REPLY_STATUS_SUCCESS
mdefine_line|#define I2O_REPLY_STATUS_SUCCESS                    &t;0x00
DECL|macro|I2O_REPLY_STATUS_ABORT_DIRTY
mdefine_line|#define I2O_REPLY_STATUS_ABORT_DIRTY                &t;0x01
DECL|macro|I2O_REPLY_STATUS_ABORT_NO_DATA_TRANSFER
mdefine_line|#define I2O_REPLY_STATUS_ABORT_NO_DATA_TRANSFER     &t;0x02
DECL|macro|I2O_REPLY_STATUS_ABORT_PARTIAL_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_ABORT_PARTIAL_TRANSFER&t;&t;0x03
DECL|macro|I2O_REPLY_STATUS_ERROR_DIRTY
mdefine_line|#define&t;I2O_REPLY_STATUS_ERROR_DIRTY&t;&t;&t;0x04
DECL|macro|I2O_REPLY_STATUS_ERROR_NO_DATA_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_ERROR_NO_DATA_TRANSFER&t;&t;0x05
DECL|macro|I2O_REPLY_STATUS_ERROR_PARTIAL_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_ERROR_PARTIAL_TRANSFER&t;&t;0x06
DECL|macro|I2O_REPLY_STATUS_PROCESS_ABORT_DIRTY
mdefine_line|#define&t;I2O_REPLY_STATUS_PROCESS_ABORT_DIRTY&t;&t;0x08
DECL|macro|I2O_REPLY_STATUS_PROCESS_ABORT_NO_DATA_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_PROCESS_ABORT_NO_DATA_TRANSFER&t;0x09
DECL|macro|I2O_REPLY_STATUS_PROCESS_ABORT_PARTIAL_TRANSFER
mdefine_line|#define&t;I2O_REPLY_STATUS_PROCESS_ABORT_PARTIAL_TRANSFER&t;0x0A
DECL|macro|I2O_REPLY_STATUS_TRANSACTION_ERROR
mdefine_line|#define&t;I2O_REPLY_STATUS_TRANSACTION_ERROR&t;&t;0x0B
DECL|macro|I2O_REPLY_STATUS_PROGRESS_REPORT
mdefine_line|#define&t;I2O_REPLY_STATUS_PROGRESS_REPORT&t;&t;0x80
multiline_comment|/* Status codes and Error Information for Parameter functions */
DECL|macro|I2O_PARAMS_STATUS_SUCCESS
mdefine_line|#define I2O_PARAMS_STATUS_SUCCESS&t;&t;0x00
DECL|macro|I2O_PARAMS_STATUS_BAD_KEY_ABORT
mdefine_line|#define I2O_PARAMS_STATUS_BAD_KEY_ABORT&t;&t;0x01
DECL|macro|I2O_PARAMS_STATUS_BAD_KEY_CONTINUE
mdefine_line|#define I2O_PARAMS_STATUS_BAD_KEY_CONTINUE   &t;0x02
DECL|macro|I2O_PARAMS_STATUS_BUFFER_FULL
mdefine_line|#define I2O_PARAMS_STATUS_BUFFER_FULL&t;&t;0x03
DECL|macro|I2O_PARAMS_STATUS_BUFFER_TOO_SMALL
mdefine_line|#define I2O_PARAMS_STATUS_BUFFER_TOO_SMALL&t;0x04
DECL|macro|I2O_PARAMS_STATUS_FIELD_UNREADABLE
mdefine_line|#define I2O_PARAMS_STATUS_FIELD_UNREADABLE&t;0x05
DECL|macro|I2O_PARAMS_STATUS_FIELD_UNWRITEABLE
mdefine_line|#define I2O_PARAMS_STATUS_FIELD_UNWRITEABLE&t;0x06
DECL|macro|I2O_PARAMS_STATUS_INSUFFICIENT_FIELDS
mdefine_line|#define I2O_PARAMS_STATUS_INSUFFICIENT_FIELDS&t;0x07
DECL|macro|I2O_PARAMS_STATUS_INVALID_GROUP_ID
mdefine_line|#define I2O_PARAMS_STATUS_INVALID_GROUP_ID&t;0x08
DECL|macro|I2O_PARAMS_STATUS_INVALID_OPERATION
mdefine_line|#define I2O_PARAMS_STATUS_INVALID_OPERATION&t;0x09
DECL|macro|I2O_PARAMS_STATUS_NO_KEY_FIELD
mdefine_line|#define I2O_PARAMS_STATUS_NO_KEY_FIELD&t;&t;0x0A
DECL|macro|I2O_PARAMS_STATUS_NO_SUCH_FIELD
mdefine_line|#define I2O_PARAMS_STATUS_NO_SUCH_FIELD&t;&t;0x0B
DECL|macro|I2O_PARAMS_STATUS_NON_DYNAMIC_GROUP
mdefine_line|#define I2O_PARAMS_STATUS_NON_DYNAMIC_GROUP&t;0x0C
DECL|macro|I2O_PARAMS_STATUS_OPERATION_ERROR
mdefine_line|#define I2O_PARAMS_STATUS_OPERATION_ERROR&t;0x0D
DECL|macro|I2O_PARAMS_STATUS_SCALAR_ERROR
mdefine_line|#define I2O_PARAMS_STATUS_SCALAR_ERROR&t;&t;0x0E
DECL|macro|I2O_PARAMS_STATUS_TABLE_ERROR
mdefine_line|#define I2O_PARAMS_STATUS_TABLE_ERROR&t;&t;0x0F
DECL|macro|I2O_PARAMS_STATUS_WRONG_GROUP_TYPE
mdefine_line|#define I2O_PARAMS_STATUS_WRONG_GROUP_TYPE&t;0x10
multiline_comment|/* DetailedStatusCode defines for Executive, DDM, Util and Transaction error&n; * messages: Table 3-2 Detailed Status Codes.*/
DECL|macro|I2O_DSC_SUCCESS
mdefine_line|#define I2O_DSC_SUCCESS                        0x0000
DECL|macro|I2O_DSC_BAD_KEY
mdefine_line|#define I2O_DSC_BAD_KEY                        0x0002
DECL|macro|I2O_DSC_TCL_ERROR
mdefine_line|#define I2O_DSC_TCL_ERROR                      0x0003
DECL|macro|I2O_DSC_REPLY_BUFFER_FULL
mdefine_line|#define I2O_DSC_REPLY_BUFFER_FULL              0x0004
DECL|macro|I2O_DSC_NO_SUCH_PAGE
mdefine_line|#define I2O_DSC_NO_SUCH_PAGE                   0x0005
DECL|macro|I2O_DSC_INSUFFICIENT_RESOURCE_SOFT
mdefine_line|#define I2O_DSC_INSUFFICIENT_RESOURCE_SOFT     0x0006
DECL|macro|I2O_DSC_INSUFFICIENT_RESOURCE_HARD
mdefine_line|#define I2O_DSC_INSUFFICIENT_RESOURCE_HARD     0x0007
DECL|macro|I2O_DSC_CHAIN_BUFFER_TOO_LARGE
mdefine_line|#define I2O_DSC_CHAIN_BUFFER_TOO_LARGE         0x0009
DECL|macro|I2O_DSC_UNSUPPORTED_FUNCTION
mdefine_line|#define I2O_DSC_UNSUPPORTED_FUNCTION           0x000A
DECL|macro|I2O_DSC_DEVICE_LOCKED
mdefine_line|#define I2O_DSC_DEVICE_LOCKED                  0x000B
DECL|macro|I2O_DSC_DEVICE_RESET
mdefine_line|#define I2O_DSC_DEVICE_RESET                   0x000C
DECL|macro|I2O_DSC_INAPPROPRIATE_FUNCTION
mdefine_line|#define I2O_DSC_INAPPROPRIATE_FUNCTION         0x000D
DECL|macro|I2O_DSC_INVALID_INITIATOR_ADDRESS
mdefine_line|#define I2O_DSC_INVALID_INITIATOR_ADDRESS      0x000E
DECL|macro|I2O_DSC_INVALID_MESSAGE_FLAGS
mdefine_line|#define I2O_DSC_INVALID_MESSAGE_FLAGS          0x000F
DECL|macro|I2O_DSC_INVALID_OFFSET
mdefine_line|#define I2O_DSC_INVALID_OFFSET                 0x0010
DECL|macro|I2O_DSC_INVALID_PARAMETER
mdefine_line|#define I2O_DSC_INVALID_PARAMETER              0x0011
DECL|macro|I2O_DSC_INVALID_REQUEST
mdefine_line|#define I2O_DSC_INVALID_REQUEST                0x0012
DECL|macro|I2O_DSC_INVALID_TARGET_ADDRESS
mdefine_line|#define I2O_DSC_INVALID_TARGET_ADDRESS         0x0013
DECL|macro|I2O_DSC_MESSAGE_TOO_LARGE
mdefine_line|#define I2O_DSC_MESSAGE_TOO_LARGE              0x0014
DECL|macro|I2O_DSC_MESSAGE_TOO_SMALL
mdefine_line|#define I2O_DSC_MESSAGE_TOO_SMALL              0x0015
DECL|macro|I2O_DSC_MISSING_PARAMETER
mdefine_line|#define I2O_DSC_MISSING_PARAMETER              0x0016
DECL|macro|I2O_DSC_TIMEOUT
mdefine_line|#define I2O_DSC_TIMEOUT                        0x0017
DECL|macro|I2O_DSC_UNKNOWN_ERROR
mdefine_line|#define I2O_DSC_UNKNOWN_ERROR                  0x0018
DECL|macro|I2O_DSC_UNKNOWN_FUNCTION
mdefine_line|#define I2O_DSC_UNKNOWN_FUNCTION               0x0019
DECL|macro|I2O_DSC_UNSUPPORTED_VERSION
mdefine_line|#define I2O_DSC_UNSUPPORTED_VERSION            0x001A
DECL|macro|I2O_DSC_DEVICE_BUSY
mdefine_line|#define I2O_DSC_DEVICE_BUSY                    0x001B
DECL|macro|I2O_DSC_DEVICE_NOT_AVAILABLE
mdefine_line|#define I2O_DSC_DEVICE_NOT_AVAILABLE           0x001C
multiline_comment|/* FailureStatusCodes, Table 3-3 Message Failure Codes */
DECL|macro|I2O_FSC_TRANSPORT_SERVICE_SUSPENDED
mdefine_line|#define I2O_FSC_TRANSPORT_SERVICE_SUSPENDED             0x81
DECL|macro|I2O_FSC_TRANSPORT_SERVICE_TERMINATED
mdefine_line|#define I2O_FSC_TRANSPORT_SERVICE_TERMINATED            0x82
DECL|macro|I2O_FSC_TRANSPORT_CONGESTION
mdefine_line|#define I2O_FSC_TRANSPORT_CONGESTION                    0x83
DECL|macro|I2O_FSC_TRANSPORT_FAILURE
mdefine_line|#define I2O_FSC_TRANSPORT_FAILURE                       0x84
DECL|macro|I2O_FSC_TRANSPORT_STATE_ERROR
mdefine_line|#define I2O_FSC_TRANSPORT_STATE_ERROR                   0x85
DECL|macro|I2O_FSC_TRANSPORT_TIME_OUT
mdefine_line|#define I2O_FSC_TRANSPORT_TIME_OUT                      0x86
DECL|macro|I2O_FSC_TRANSPORT_ROUTING_FAILURE
mdefine_line|#define I2O_FSC_TRANSPORT_ROUTING_FAILURE               0x87
DECL|macro|I2O_FSC_TRANSPORT_INVALID_VERSION
mdefine_line|#define I2O_FSC_TRANSPORT_INVALID_VERSION               0x88
DECL|macro|I2O_FSC_TRANSPORT_INVALID_OFFSET
mdefine_line|#define I2O_FSC_TRANSPORT_INVALID_OFFSET                0x89
DECL|macro|I2O_FSC_TRANSPORT_INVALID_MSG_FLAGS
mdefine_line|#define I2O_FSC_TRANSPORT_INVALID_MSG_FLAGS             0x8A
DECL|macro|I2O_FSC_TRANSPORT_FRAME_TOO_SMALL
mdefine_line|#define I2O_FSC_TRANSPORT_FRAME_TOO_SMALL               0x8B
DECL|macro|I2O_FSC_TRANSPORT_FRAME_TOO_LARGE
mdefine_line|#define I2O_FSC_TRANSPORT_FRAME_TOO_LARGE               0x8C
DECL|macro|I2O_FSC_TRANSPORT_INVALID_TARGET_ID
mdefine_line|#define I2O_FSC_TRANSPORT_INVALID_TARGET_ID             0x8D
DECL|macro|I2O_FSC_TRANSPORT_INVALID_INITIATOR_ID
mdefine_line|#define I2O_FSC_TRANSPORT_INVALID_INITIATOR_ID          0x8E
DECL|macro|I2O_FSC_TRANSPORT_INVALID_INITIATOR_CONTEXT
mdefine_line|#define I2O_FSC_TRANSPORT_INVALID_INITIATOR_CONTEXT     0x8F
DECL|macro|I2O_FSC_TRANSPORT_UNKNOWN_FAILURE
mdefine_line|#define I2O_FSC_TRANSPORT_UNKNOWN_FAILURE               0xFF
multiline_comment|/* Device Claim Types */
DECL|macro|I2O_CLAIM_PRIMARY
mdefine_line|#define&t;I2O_CLAIM_PRIMARY&t;&t;&t;&t;&t;0x01000000
DECL|macro|I2O_CLAIM_MANAGEMENT
mdefine_line|#define&t;I2O_CLAIM_MANAGEMENT&t;&t;&t;&t;&t;0x02000000
DECL|macro|I2O_CLAIM_AUTHORIZED
mdefine_line|#define&t;I2O_CLAIM_AUTHORIZED&t;&t;&t;&t;&t;0x03000000
DECL|macro|I2O_CLAIM_SECONDARY
mdefine_line|#define&t;I2O_CLAIM_SECONDARY&t;&t;&t;&t;&t;0x04000000
multiline_comment|/* Message header defines for VersionOffset */
DECL|macro|I2OVER15
mdefine_line|#define I2OVER15&t;0x0001
DECL|macro|I2OVER20
mdefine_line|#define I2OVER20&t;0x0002
multiline_comment|/* Default is 1.5, FIXME: Need support for both 1.5 and 2.0 */
DECL|macro|I2OVERSION
mdefine_line|#define I2OVERSION&t;I2OVER15
DECL|macro|SGL_OFFSET_0
mdefine_line|#define SGL_OFFSET_0    I2OVERSION
DECL|macro|SGL_OFFSET_4
mdefine_line|#define SGL_OFFSET_4    (0x0040 | I2OVERSION)
DECL|macro|SGL_OFFSET_5
mdefine_line|#define SGL_OFFSET_5    (0x0050 | I2OVERSION)
DECL|macro|SGL_OFFSET_6
mdefine_line|#define SGL_OFFSET_6    (0x0060 | I2OVERSION)
DECL|macro|SGL_OFFSET_7
mdefine_line|#define SGL_OFFSET_7    (0x0070 | I2OVERSION)
DECL|macro|SGL_OFFSET_8
mdefine_line|#define SGL_OFFSET_8    (0x0080 | I2OVERSION)
DECL|macro|SGL_OFFSET_9
mdefine_line|#define SGL_OFFSET_9    (0x0090 | I2OVERSION)
DECL|macro|SGL_OFFSET_10
mdefine_line|#define SGL_OFFSET_10   (0x00A0 | I2OVERSION)
DECL|macro|TRL_OFFSET_5
mdefine_line|#define TRL_OFFSET_5    (0x0050 | I2OVERSION)
DECL|macro|TRL_OFFSET_6
mdefine_line|#define TRL_OFFSET_6    (0x0060 | I2OVERSION)
multiline_comment|/* Transaction Reply Lists (TRL) Control Word structure */
DECL|macro|TRL_SINGLE_FIXED_LENGTH
mdefine_line|#define TRL_SINGLE_FIXED_LENGTH&t;&t;0x00
DECL|macro|TRL_SINGLE_VARIABLE_LENGTH
mdefine_line|#define TRL_SINGLE_VARIABLE_LENGTH&t;0x40
DECL|macro|TRL_MULTIPLE_FIXED_LENGTH
mdefine_line|#define TRL_MULTIPLE_FIXED_LENGTH&t;0x80
multiline_comment|/* msg header defines for MsgFlags */
DECL|macro|MSG_STATIC
mdefine_line|#define MSG_STATIC&t;0x0100
DECL|macro|MSG_64BIT_CNTXT
mdefine_line|#define MSG_64BIT_CNTXT&t;0x0200
DECL|macro|MSG_MULTI_TRANS
mdefine_line|#define MSG_MULTI_TRANS&t;0x1000
DECL|macro|MSG_FAIL
mdefine_line|#define MSG_FAIL&t;0x2000
DECL|macro|MSG_FINAL
mdefine_line|#define MSG_FINAL&t;0x4000
DECL|macro|MSG_REPLY
mdefine_line|#define MSG_REPLY&t;0x8000
multiline_comment|/* minimum size msg */
DECL|macro|THREE_WORD_MSG_SIZE
mdefine_line|#define THREE_WORD_MSG_SIZE&t;0x00030000
DECL|macro|FOUR_WORD_MSG_SIZE
mdefine_line|#define FOUR_WORD_MSG_SIZE&t;0x00040000
DECL|macro|FIVE_WORD_MSG_SIZE
mdefine_line|#define FIVE_WORD_MSG_SIZE&t;0x00050000
DECL|macro|SIX_WORD_MSG_SIZE
mdefine_line|#define SIX_WORD_MSG_SIZE&t;0x00060000
DECL|macro|SEVEN_WORD_MSG_SIZE
mdefine_line|#define SEVEN_WORD_MSG_SIZE&t;0x00070000
DECL|macro|EIGHT_WORD_MSG_SIZE
mdefine_line|#define EIGHT_WORD_MSG_SIZE&t;0x00080000
DECL|macro|NINE_WORD_MSG_SIZE
mdefine_line|#define NINE_WORD_MSG_SIZE&t;0x00090000
DECL|macro|TEN_WORD_MSG_SIZE
mdefine_line|#define TEN_WORD_MSG_SIZE&t;0x000A0000
DECL|macro|I2O_MESSAGE_SIZE
mdefine_line|#define I2O_MESSAGE_SIZE(x)&t;((x)&lt;&lt;16)
multiline_comment|/* Special TID Assignments */
DECL|macro|ADAPTER_TID
mdefine_line|#define ADAPTER_TID&t;&t;0
DECL|macro|HOST_TID
mdefine_line|#define HOST_TID&t;&t;1
DECL|macro|MSG_FRAME_SIZE
mdefine_line|#define MSG_FRAME_SIZE&t;&t;128
DECL|macro|NMBR_MSG_FRAMES
mdefine_line|#define NMBR_MSG_FRAMES&t;&t;128
DECL|macro|MSG_POOL_SIZE
mdefine_line|#define MSG_POOL_SIZE&t;&t;16384
DECL|macro|I2O_POST_WAIT_OK
mdefine_line|#define I2O_POST_WAIT_OK&t;0
DECL|macro|I2O_POST_WAIT_TIMEOUT
mdefine_line|#define I2O_POST_WAIT_TIMEOUT&t;-ETIMEDOUT
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _I2O_H */
eof
