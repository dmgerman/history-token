multiline_comment|/*&n; * I2O kernel space accessible structures/APIs&n; *&n; * (c) Copyright 1999, 2000 Red Hat Software&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; *************************************************************************&n; *&n; * This header file defined the I2O APIs/structures for use by&n; * the I2O kernel modules.&n; *&n; */
macro_line|#ifndef _I2O_H
DECL|macro|_I2O_H
mdefine_line|#define _I2O_H
macro_line|#ifdef __KERNEL__&t;&t;/* This file to be included by kernel only */
macro_line|#include &lt;linux/i2o-dev.h&gt;
multiline_comment|/* How many different OSM&squot;s are we allowing */
DECL|macro|I2O_MAX_DRIVERS
mdefine_line|#define I2O_MAX_DRIVERS&t;&t;8
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;&t;/* Needed for MUTEX init macros */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
multiline_comment|/* message queue empty */
DECL|macro|I2O_QUEUE_EMPTY
mdefine_line|#define I2O_QUEUE_EMPTY&t;&t;0xffffffff
multiline_comment|/*&n; *&t;Message structures&n; */
DECL|struct|i2o_message
r_struct
id|i2o_message
(brace
r_union
(brace
r_struct
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
DECL|member|icntxt
id|u32
id|icntxt
suffix:semicolon
multiline_comment|/* initiator context */
DECL|member|tcntxt
id|u32
id|tcntxt
suffix:semicolon
multiline_comment|/* transaction context */
DECL|member|s
)brace
id|s
suffix:semicolon
DECL|member|head
id|u32
id|head
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
multiline_comment|/* List follows */
DECL|member|body
id|u32
id|body
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Each I2O device entity has one of these. There is one per device.&n; */
DECL|struct|i2o_device
r_struct
id|i2o_device
(brace
DECL|member|lct_data
id|i2o_lct_entry
id|lct_data
suffix:semicolon
multiline_comment|/* Device LCT information */
DECL|member|iop
r_struct
id|i2o_controller
op_star
id|iop
suffix:semicolon
multiline_comment|/* Controlling IOP */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* node in IOP devices list */
DECL|member|device
r_struct
id|device
id|device
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
multiline_comment|/* device lock */
DECL|member|classdev
r_struct
id|class_device
id|classdev
suffix:semicolon
multiline_comment|/* i2o device class */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Event structure provided to the event handling function&n; */
DECL|struct|i2o_event
r_struct
id|i2o_event
(brace
DECL|member|work
r_struct
id|work_struct
id|work
suffix:semicolon
DECL|member|i2o_dev
r_struct
id|i2o_device
op_star
id|i2o_dev
suffix:semicolon
multiline_comment|/* I2O device pointer from which the&n;&t;&t;&t;&t;&t;   event reply was initiated */
DECL|member|size
id|u16
id|size
suffix:semicolon
multiline_comment|/* Size of data in 32-bit words */
DECL|member|tcntxt
id|u32
id|tcntxt
suffix:semicolon
multiline_comment|/* Transaction context used at&n;&t;&t;&t;&t;   registration */
DECL|member|event_indicator
id|u32
id|event_indicator
suffix:semicolon
multiline_comment|/* Event indicator from reply */
DECL|member|data
id|u32
id|data
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Event data from reply */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;I2O classes which could be handled by the OSM&n; */
DECL|struct|i2o_class_id
r_struct
id|i2o_class_id
(brace
DECL|member|class_id
id|u16
id|class_id
suffix:colon
l_int|12
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;I2O driver structure for OSMs&n; */
DECL|struct|i2o_driver
r_struct
id|i2o_driver
(brace
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
DECL|member|classes
r_struct
id|i2o_class_id
op_star
id|classes
suffix:semicolon
multiline_comment|/* I2O classes that this OSM handles */
multiline_comment|/* Message reply handler */
DECL|member|reply
r_int
(paren
op_star
id|reply
)paren
(paren
r_struct
id|i2o_controller
op_star
comma
id|u32
comma
r_struct
id|i2o_message
op_star
)paren
suffix:semicolon
multiline_comment|/* Event handler */
DECL|member|event
r_void
(paren
op_star
id|event
)paren
(paren
r_struct
id|i2o_event
op_star
)paren
suffix:semicolon
DECL|member|event_queue
r_struct
id|workqueue_struct
op_star
id|event_queue
suffix:semicolon
multiline_comment|/* Event queue */
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
multiline_comment|/* notification of changes */
DECL|member|notify_controller_add
r_void
(paren
op_star
id|notify_controller_add
)paren
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
DECL|member|notify_controller_remove
r_void
(paren
op_star
id|notify_controller_remove
)paren
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
DECL|member|notify_device_add
r_void
(paren
op_star
id|notify_device_add
)paren
(paren
r_struct
id|i2o_device
op_star
)paren
suffix:semicolon
DECL|member|notify_device_remove
r_void
(paren
op_star
id|notify_device_remove
)paren
(paren
r_struct
id|i2o_device
op_star
)paren
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Contains all information which are necessary for DMA operations&n; */
DECL|struct|i2o_dma
r_struct
id|i2o_dma
(brace
DECL|member|virt
r_void
op_star
id|virt
suffix:semicolon
DECL|member|phys
id|dma_addr_t
id|phys
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Context queue entry, used for 32-bit context on 64-bit systems&n; */
DECL|struct|i2o_context_list_element
r_struct
id|i2o_context_list_element
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|context
id|u32
id|context
suffix:semicolon
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
DECL|member|timestamp
r_int
r_int
id|timestamp
suffix:semicolon
)brace
suffix:semicolon
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
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
multiline_comment|/* PCI device */
DECL|member|short_req
r_int
r_int
id|short_req
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* use small block sizes */
DECL|member|no_quiesce
r_int
r_int
id|no_quiesce
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* dont quiesce before reset */
DECL|member|raptor
r_int
r_int
id|raptor
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* split bar */
DECL|member|promise
r_int
r_int
id|promise
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Promise controller */
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
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
multiline_comment|/* list of I2O devices */
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
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* Controller list */
DECL|member|post_port
r_void
id|__iomem
op_star
id|post_port
suffix:semicolon
multiline_comment|/* Inbout port address */
DECL|member|reply_port
r_void
id|__iomem
op_star
id|reply_port
suffix:semicolon
multiline_comment|/* Outbound port address */
DECL|member|irq_mask
r_void
id|__iomem
op_star
id|irq_mask
suffix:semicolon
multiline_comment|/* Interrupt register address */
multiline_comment|/* Dynamic LCT related data */
DECL|member|status
r_struct
id|i2o_dma
id|status
suffix:semicolon
multiline_comment|/* status of IOP */
DECL|member|hrt
r_struct
id|i2o_dma
id|hrt
suffix:semicolon
multiline_comment|/* HW Resource Table */
DECL|member|lct
id|i2o_lct
op_star
id|lct
suffix:semicolon
multiline_comment|/* Logical Config Table */
DECL|member|dlct
r_struct
id|i2o_dma
id|dlct
suffix:semicolon
multiline_comment|/* Temp LCT */
DECL|member|lct_lock
r_struct
id|semaphore
id|lct_lock
suffix:semicolon
multiline_comment|/* Lock for LCT updates */
DECL|member|status_block
r_struct
id|i2o_dma
id|status_block
suffix:semicolon
multiline_comment|/* IOP status block */
DECL|member|base
r_struct
id|i2o_dma
id|base
suffix:semicolon
multiline_comment|/* controller messaging unit */
DECL|member|in_queue
r_struct
id|i2o_dma
id|in_queue
suffix:semicolon
multiline_comment|/* inbound message queue Host-&gt;IOP */
DECL|member|out_queue
r_struct
id|i2o_dma
id|out_queue
suffix:semicolon
multiline_comment|/* outbound message queue IOP-&gt;Host */
DECL|member|battery
r_int
r_int
id|battery
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Has a battery backup */
DECL|member|io_alloc
r_int
r_int
id|io_alloc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* An I/O resource was allocated */
DECL|member|mem_alloc
r_int
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
DECL|member|bus_list
r_struct
id|list_head
id|bus_list
suffix:semicolon
multiline_comment|/* list of busses on IOP */
DECL|member|device
r_struct
id|device
id|device
suffix:semicolon
DECL|member|exec
r_struct
id|i2o_device
op_star
id|exec
suffix:semicolon
multiline_comment|/* Executive */
macro_line|#if BITS_PER_LONG == 64
DECL|member|context_list_lock
id|spinlock_t
id|context_list_lock
suffix:semicolon
multiline_comment|/* lock for context_list */
DECL|member|context_list_counter
id|atomic_t
id|context_list_counter
suffix:semicolon
multiline_comment|/* needed for unique contexts */
DECL|member|context_list
r_struct
id|list_head
id|context_list
suffix:semicolon
multiline_comment|/* list of context id&squot;s&n;&t;&t;&t;&t;&t;   and pointers */
macro_line|#endif
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* lock for controller&n;&t;&t;&t;&t;   configuration */
DECL|member|driver_data
r_void
op_star
id|driver_data
(braket
id|I2O_MAX_DRIVERS
)braket
suffix:semicolon
multiline_comment|/* storage for drivers */
)brace
suffix:semicolon
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
r_extern
r_struct
id|list_head
id|i2o_controllers
suffix:semicolon
multiline_comment|/* Message functions */
r_static
r_inline
id|u32
id|i2o_msg_get
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_struct
id|i2o_message
id|__iomem
op_star
op_star
)paren
suffix:semicolon
r_extern
id|u32
id|i2o_msg_get_wait
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_struct
id|i2o_message
id|__iomem
op_star
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_inline
r_void
id|i2o_msg_post
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
id|u32
)paren
suffix:semicolon
r_static
r_inline
r_int
id|i2o_msg_post_wait
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
id|u32
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|i2o_msg_post_wait_mem
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
id|u32
comma
r_int
r_int
comma
r_struct
id|i2o_dma
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2o_msg_nop
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
id|u32
)paren
suffix:semicolon
r_static
r_inline
r_void
id|i2o_flush_reply
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
id|u32
)paren
suffix:semicolon
multiline_comment|/* DMA handling functions */
r_static
r_inline
r_int
id|i2o_dma_alloc
c_func
(paren
r_struct
id|device
op_star
comma
r_struct
id|i2o_dma
op_star
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_inline
r_void
id|i2o_dma_free
c_func
(paren
r_struct
id|device
op_star
comma
r_struct
id|i2o_dma
op_star
)paren
suffix:semicolon
r_int
id|i2o_dma_realloc
c_func
(paren
r_struct
id|device
op_star
comma
r_struct
id|i2o_dma
op_star
comma
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_inline
r_int
id|i2o_dma_map
c_func
(paren
r_struct
id|device
op_star
comma
r_struct
id|i2o_dma
op_star
)paren
suffix:semicolon
r_static
r_inline
r_void
id|i2o_dma_unmap
c_func
(paren
r_struct
id|device
op_star
comma
r_struct
id|i2o_dma
op_star
)paren
suffix:semicolon
multiline_comment|/* IOP functions */
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
id|i2o_event_register
c_func
(paren
r_struct
id|i2o_device
op_star
comma
r_struct
id|i2o_driver
op_star
comma
r_int
comma
id|u32
)paren
suffix:semicolon
r_extern
r_struct
id|i2o_device
op_star
id|i2o_iop_find_device
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
id|u16
)paren
suffix:semicolon
r_extern
r_struct
id|i2o_controller
op_star
id|i2o_find_iop
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* Functions needed for handling 64-bit pointers in 32-bit context */
macro_line|#if BITS_PER_LONG == 64
r_extern
id|u32
id|i2o_cntxt_list_add
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
op_star
id|i2o_cntxt_list_get
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
id|u32
id|i2o_cntxt_list_remove
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
id|u32
id|i2o_cntxt_list_get_ptr
c_func
(paren
r_struct
id|i2o_controller
op_star
comma
r_void
op_star
)paren
suffix:semicolon
DECL|function|i2o_ptr_low
r_static
r_inline
id|u32
id|i2o_ptr_low
c_func
(paren
r_void
op_star
id|ptr
)paren
(brace
r_return
(paren
id|u32
)paren
(paren
id|u64
)paren
id|ptr
suffix:semicolon
)brace
suffix:semicolon
DECL|function|i2o_ptr_high
r_static
r_inline
id|u32
id|i2o_ptr_high
c_func
(paren
r_void
op_star
id|ptr
)paren
(brace
r_return
(paren
id|u32
)paren
(paren
(paren
id|u64
)paren
id|ptr
op_rshift
l_int|32
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else
DECL|function|i2o_cntxt_list_add
r_static
r_inline
id|u32
id|i2o_cntxt_list_add
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
r_void
op_star
id|ptr
)paren
(brace
r_return
(paren
id|u32
)paren
id|ptr
suffix:semicolon
)brace
suffix:semicolon
DECL|function|i2o_cntxt_list_get
r_static
r_inline
r_void
op_star
id|i2o_cntxt_list_get
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|context
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|context
suffix:semicolon
)brace
suffix:semicolon
DECL|function|i2o_cntxt_list_remove
r_static
r_inline
id|u32
id|i2o_cntxt_list_remove
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
r_void
op_star
id|ptr
)paren
(brace
r_return
(paren
id|u32
)paren
id|ptr
suffix:semicolon
)brace
suffix:semicolon
DECL|function|i2o_cntxt_list_get_ptr
r_static
r_inline
id|u32
id|i2o_cntxt_list_get_ptr
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
r_void
op_star
id|ptr
)paren
(brace
r_return
(paren
id|u32
)paren
id|ptr
suffix:semicolon
)brace
suffix:semicolon
DECL|function|i2o_ptr_low
r_static
r_inline
id|u32
id|i2o_ptr_low
c_func
(paren
r_void
op_star
id|ptr
)paren
(brace
r_return
(paren
id|u32
)paren
id|ptr
suffix:semicolon
)brace
suffix:semicolon
DECL|function|i2o_ptr_high
r_static
r_inline
id|u32
id|i2o_ptr_high
c_func
(paren
r_void
op_star
id|ptr
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* I2O driver (OSM) functions */
r_extern
r_int
id|i2o_driver_register
c_func
(paren
r_struct
id|i2o_driver
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2o_driver_unregister
c_func
(paren
r_struct
id|i2o_driver
op_star
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_driver_notify_controller_add - Send notification of added controller&n; *&t;&t;&t;&t;&t;   to a single I2O driver&n; *&n; *&t;Send notification of added controller to a single registered driver.&n; */
DECL|function|i2o_driver_notify_controller_add
r_static
r_inline
r_void
id|i2o_driver_notify_controller_add
c_func
(paren
r_struct
id|i2o_driver
op_star
id|drv
comma
r_struct
id|i2o_controller
op_star
id|c
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;notify_controller_add
)paren
id|drv
op_member_access_from_pointer
id|notify_controller_add
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_driver_notify_controller_remove - Send notification of removed&n; *&t;&t;&t;&t;&t;      controller to a single I2O driver&n; *&n; *&t;Send notification of removed controller to a single registered driver.&n; */
DECL|function|i2o_driver_notify_controller_remove
r_static
r_inline
r_void
id|i2o_driver_notify_controller_remove
c_func
(paren
r_struct
id|i2o_driver
op_star
id|drv
comma
r_struct
id|i2o_controller
op_star
id|c
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;notify_controller_remove
)paren
id|drv
op_member_access_from_pointer
id|notify_controller_remove
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_driver_notify_device_add - Send notification of added device to a&n; *&t;&t;&t;&t;       single I2O driver&n; *&n; *&t;Send notification of added device to a single registered driver.&n; */
DECL|function|i2o_driver_notify_device_add
r_static
r_inline
r_void
id|i2o_driver_notify_device_add
c_func
(paren
r_struct
id|i2o_driver
op_star
id|drv
comma
r_struct
id|i2o_device
op_star
id|i2o_dev
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;notify_device_add
)paren
id|drv
op_member_access_from_pointer
id|notify_device_add
c_func
(paren
id|i2o_dev
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_driver_notify_device_remove - Send notification of removed device&n; *&t;&t;&t;&t;&t;  to a single I2O driver&n; *&n; *&t;Send notification of removed device to a single registered driver.&n; */
DECL|function|i2o_driver_notify_device_remove
r_static
r_inline
r_void
id|i2o_driver_notify_device_remove
c_func
(paren
r_struct
id|i2o_driver
op_star
id|drv
comma
r_struct
id|i2o_device
op_star
id|i2o_dev
)paren
(brace
r_if
c_cond
(paren
id|drv-&gt;notify_device_remove
)paren
id|drv
op_member_access_from_pointer
id|notify_device_remove
c_func
(paren
id|i2o_dev
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|i2o_driver_notify_controller_add_all
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2o_driver_notify_controller_remove_all
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2o_driver_notify_device_add_all
c_func
(paren
r_struct
id|i2o_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2o_driver_notify_device_remove_all
c_func
(paren
r_struct
id|i2o_device
op_star
)paren
suffix:semicolon
multiline_comment|/* I2O device functions */
r_extern
r_int
id|i2o_device_claim
c_func
(paren
r_struct
id|i2o_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|i2o_device_claim_release
c_func
(paren
r_struct
id|i2o_device
op_star
)paren
suffix:semicolon
multiline_comment|/* Exec OSM functions */
r_extern
r_int
id|i2o_exec_lct_get
c_func
(paren
r_struct
id|i2o_controller
op_star
)paren
suffix:semicolon
multiline_comment|/* device to i2o_device and driver to i2o_driver convertion functions */
DECL|macro|to_i2o_driver
mdefine_line|#define to_i2o_driver(drv) container_of(drv,struct i2o_driver, driver)
DECL|macro|to_i2o_device
mdefine_line|#define to_i2o_device(dev) container_of(dev, struct i2o_device, device)
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
id|rmb
c_func
(paren
)paren
suffix:semicolon
r_return
id|readl
c_func
(paren
id|c-&gt;post_port
)paren
suffix:semicolon
)brace
suffix:semicolon
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
id|val
)paren
(brace
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|c-&gt;post_port
)paren
suffix:semicolon
)brace
suffix:semicolon
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
id|rmb
c_func
(paren
)paren
suffix:semicolon
r_return
id|readl
c_func
(paren
id|c-&gt;reply_port
)paren
suffix:semicolon
)brace
suffix:semicolon
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
id|val
)paren
(brace
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|c-&gt;reply_port
)paren
suffix:semicolon
)brace
suffix:semicolon
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
id|rmb
c_func
(paren
)paren
suffix:semicolon
r_return
id|readl
c_func
(paren
id|c-&gt;irq_mask
)paren
suffix:semicolon
)brace
suffix:semicolon
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
id|val
)paren
(brace
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|writel
c_func
(paren
id|val
comma
id|c-&gt;irq_mask
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_msg_get - obtain an I2O message from the IOP&n; *&t;@c: I2O controller&n; *&t;@msg: pointer to a I2O message pointer&n; *&n; *&t;This function tries to get a message slot. If no message slot is&n; *&t;available do not wait until one is availabe (see also i2o_msg_get_wait).&n; *&n; *&t;On a success the message is returned and the pointer to the message is&n; *&t;set in msg. The returned message is the physical page frame offset&n; *&t;address from the read port (see the i2o spec). If no message is&n; *&t;available returns I2O_QUEUE_EMPTY and msg is leaved untouched.&n; */
DECL|function|i2o_msg_get
r_static
r_inline
id|u32
id|i2o_msg_get
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
r_struct
id|i2o_message
id|__iomem
op_star
op_star
id|msg
)paren
(brace
id|u32
id|m
suffix:semicolon
r_if
c_cond
(paren
(paren
id|m
op_assign
id|I2O_POST_READ32
c_func
(paren
id|c
)paren
)paren
op_ne
id|I2O_QUEUE_EMPTY
)paren
op_star
id|msg
op_assign
id|c-&gt;in_queue.virt
op_plus
id|m
suffix:semicolon
r_return
id|m
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_msg_post - Post I2O message to I2O controller&n; *&t;@c: I2O controller to which the message should be send&n; *&t;@m: the message identifier&n; *&n; *&t;Post the message to the I2O controller.&n; */
DECL|function|i2o_msg_post
r_static
r_inline
r_void
id|i2o_msg_post
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
id|I2O_POST_WRITE32
c_func
(paren
id|c
comma
id|m
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; * &t;i2o_msg_post_wait - Post and wait a message and wait until return&n; *&t;@c: controller&n; *&t;@m: message to post&n; *&t;@timeout: time in seconds to wait&n; *&n; * &t;This API allows an OSM to post a message and then be told whether or&n; *&t;not the system received a successful reply. If the message times out&n; *&t;then the value &squot;-ETIMEDOUT&squot; is returned.&n; *&n; *&t;Returns 0 on success or negative error code on failure.&n; */
DECL|function|i2o_msg_post_wait
r_static
r_inline
r_int
id|i2o_msg_post_wait
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
comma
id|u32
id|m
comma
r_int
r_int
id|timeout
)paren
(brace
r_return
id|i2o_msg_post_wait_mem
c_func
(paren
id|c
comma
id|m
comma
id|timeout
comma
l_int|NULL
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_flush_reply - Flush reply from I2O controller&n; *&t;@c: I2O controller&n; *&t;@m: the message identifier&n; *&n; *&t;The I2O controller must be informed that the reply message is not needed&n; *&t;anymore. If you forget to flush the reply, the message frame can&squot;t be&n; *&t;used by the controller anymore and is therefore lost.&n; *&n; *&t;FIXME: is there a timeout after which the controller reuse the message?&n; */
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
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_out_to_virt - Turn an I2O message to a virtual address&n; *&t;@c: controller&n; *&t;@m: message engine value&n; *&n; *&t;Turn a receive message from an I2O controller bus address into&n; *&t;a Linux virtual address. The shared page frame is a linear block&n; *&t;so we simply have to shift the offset. This function does not&n; *&t;work for sender side messages as they are ioremap objects&n; *&t;provided by the I2O controller.&n; */
DECL|function|i2o_msg_out_to_virt
r_static
r_inline
r_struct
id|i2o_message
op_star
id|i2o_msg_out_to_virt
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
id|BUG_ON
c_func
(paren
id|m
OL
id|c-&gt;out_queue.phys
op_logical_or
id|m
op_ge
id|c-&gt;out_queue.phys
op_plus
id|c-&gt;out_queue.len
)paren
suffix:semicolon
r_return
id|c-&gt;out_queue.virt
op_plus
(paren
id|m
op_minus
id|c-&gt;out_queue.phys
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_msg_in_to_virt - Turn an I2O message to a virtual address&n; *&t;@c: controller&n; *&t;@m: message engine value&n; *&n; *&t;Turn a send message from an I2O controller bus address into&n; *&t;a Linux virtual address. The shared page frame is a linear block&n; *&t;so we simply have to shift the offset. This function does not&n; *&t;work for receive side messages as they are kmalloc objects&n; *&t;in a different pool.&n; */
DECL|function|i2o_msg_in_to_virt
r_static
r_inline
r_struct
id|i2o_message
id|__iomem
op_star
id|i2o_msg_in_to_virt
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
r_return
id|c-&gt;in_queue.virt
op_plus
id|m
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_dma_alloc - Allocate DMA memory&n; *&t;@dev: struct device pointer to the PCI device of the I2O controller&n; *&t;@addr: i2o_dma struct which should get the DMA buffer&n; *&t;@len: length of the new DMA memory&n; *&t;@gfp_mask: GFP mask&n; *&n; *&t;Allocate a coherent DMA memory and write the pointers into addr.&n; *&n; *&t;Returns 0 on success or -ENOMEM on failure.&n; */
DECL|function|i2o_dma_alloc
r_static
r_inline
r_int
id|i2o_dma_alloc
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|i2o_dma
op_star
id|addr
comma
r_int
id|len
comma
r_int
r_int
id|gfp_mask
)paren
(brace
id|addr-&gt;virt
op_assign
id|dma_alloc_coherent
c_func
(paren
id|dev
comma
id|len
comma
op_amp
id|addr-&gt;phys
comma
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr-&gt;virt
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|addr-&gt;virt
comma
l_int|0
comma
id|len
)paren
suffix:semicolon
id|addr-&gt;len
op_assign
id|len
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_dma_free - Free DMA memory&n; *&t;@dev: struct device pointer to the PCI device of the I2O controller&n; *&t;@addr: i2o_dma struct which contains the DMA buffer&n; *&n; *&t;Free a coherent DMA memory and set virtual address of addr to NULL.&n; */
DECL|function|i2o_dma_free
r_static
r_inline
r_void
id|i2o_dma_free
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|i2o_dma
op_star
id|addr
)paren
(brace
r_if
c_cond
(paren
id|addr-&gt;virt
)paren
(brace
r_if
c_cond
(paren
id|addr-&gt;phys
)paren
id|dma_free_coherent
c_func
(paren
id|dev
comma
id|addr-&gt;len
comma
id|addr-&gt;virt
comma
id|addr-&gt;phys
)paren
suffix:semicolon
r_else
id|kfree
c_func
(paren
id|addr-&gt;virt
)paren
suffix:semicolon
id|addr-&gt;virt
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_dma_map - Map the memory to DMA&n; *&t;@dev: struct device pointer to the PCI device of the I2O controller&n; *&t;@addr: i2o_dma struct which should be mapped&n; *&n; *&t;Map the memory in addr-&gt;virt to coherent DMA memory and write the&n; *&t;physical address into addr-&gt;phys.&n; *&n; *&t;Returns 0 on success or -ENOMEM on failure.&n; */
DECL|function|i2o_dma_map
r_static
r_inline
r_int
id|i2o_dma_map
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|i2o_dma
op_star
id|addr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|addr-&gt;virt
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr-&gt;phys
)paren
id|addr-&gt;phys
op_assign
id|dma_map_single
c_func
(paren
id|dev
comma
id|addr-&gt;virt
comma
id|addr-&gt;len
comma
id|DMA_BIDIRECTIONAL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr-&gt;phys
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;i2o_dma_unmap - Unmap the DMA memory&n; *&t;@dev: struct device pointer to the PCI device of the I2O controller&n; *&t;@addr: i2o_dma struct which should be unmapped&n; *&n; *&t;Unmap the memory in addr-&gt;virt from DMA memory.&n; */
DECL|function|i2o_dma_unmap
r_static
r_inline
r_void
id|i2o_dma_unmap
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|i2o_dma
op_star
id|addr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|addr-&gt;virt
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|addr-&gt;phys
)paren
(brace
id|dma_unmap_single
c_func
(paren
id|dev
comma
id|addr-&gt;phys
comma
id|addr-&gt;len
comma
id|DMA_BIDIRECTIONAL
)paren
suffix:semicolon
id|addr-&gt;phys
op_assign
l_int|0
suffix:semicolon
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Endian handling wrapped into the macro - keeps the core code&n; *&t;cleaner.&n; */
DECL|macro|i2o_raw_writel
mdefine_line|#define i2o_raw_writel(val, mem)&t;__raw_writel(cpu_to_le32(val), mem)
r_extern
r_int
id|i2o_parm_field_get
c_func
(paren
r_struct
id|i2o_device
op_star
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
id|i2o_parm_table_get
c_func
(paren
r_struct
id|i2o_device
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
multiline_comment|/* debugging and troubleshooting/diagnostic helpers. */
DECL|macro|osm_printk
mdefine_line|#define osm_printk(level, format, arg...)  &bslash;&n;&t;printk(level &quot;%s: &quot; format, OSM_NAME , ## arg)
macro_line|#ifdef DEBUG
DECL|macro|osm_debug
mdefine_line|#define osm_debug(format, arg...) &bslash;&n;&t;osm_printk(KERN_DEBUG, format , ## arg)
macro_line|#else
DECL|macro|osm_debug
mdefine_line|#define osm_debug(format, arg...) &bslash;&n;        do { } while (0)
macro_line|#endif
DECL|macro|osm_err
mdefine_line|#define osm_err(format, arg...)&t;&t;&bslash;&n;&t;osm_printk(KERN_ERR, format , ## arg)
DECL|macro|osm_info
mdefine_line|#define osm_info(format, arg...)&t;&t;&bslash;&n;&t;osm_printk(KERN_INFO, format , ## arg)
DECL|macro|osm_warn
mdefine_line|#define osm_warn(format, arg...)&t;&t;&bslash;&n;&t;osm_printk(KERN_WARNING, format , ## arg)
multiline_comment|/* debugging functions */
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
r_struct
id|i2o_message
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2o_dump_message
c_func
(paren
r_struct
id|i2o_message
op_star
)paren
suffix:semicolon
r_extern
r_void
id|i2o_dump_hrt
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
suffix:semicolon
r_extern
r_void
id|i2o_debug_state
c_func
(paren
r_struct
id|i2o_controller
op_star
id|c
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Cache strategies&n; */
multiline_comment|/*&t;The NULL strategy leaves everything up to the controller. This tends to be a&n; *&t;pessimal but functional choice.&n; */
DECL|macro|CACHE_NULL
mdefine_line|#define CACHE_NULL&t;&t;0
multiline_comment|/*&t;Prefetch data when reading. We continually attempt to load the next 32 sectors&n; *&t;into the controller cache.&n; */
DECL|macro|CACHE_PREFETCH
mdefine_line|#define CACHE_PREFETCH&t;&t;1
multiline_comment|/*&t;Prefetch data when reading. We sometimes attempt to load the next 32 sectors&n; *&t;into the controller cache. When an I/O is less &lt;= 8K we assume its probably&n; *&t;not sequential and don&squot;t prefetch (default)&n; */
DECL|macro|CACHE_SMARTFETCH
mdefine_line|#define CACHE_SMARTFETCH&t;2
multiline_comment|/*&t;Data is written to the cache and then out on to the disk. The I/O must be&n; *&t;physically on the medium before the write is acknowledged (default without&n; *&t;NVRAM)&n; */
DECL|macro|CACHE_WRITETHROUGH
mdefine_line|#define CACHE_WRITETHROUGH&t;17
multiline_comment|/*&t;Data is written to the cache and then out on to the disk. The controller&n; *&t;is permitted to write back the cache any way it wants. (default if battery&n; *&t;backed NVRAM is present). It can be useful to set this for swap regardless of&n; *&t;battery state.&n; */
DECL|macro|CACHE_WRITEBACK
mdefine_line|#define CACHE_WRITEBACK&t;&t;18
multiline_comment|/*&t;Optimise for under powered controllers, especially on RAID1 and RAID0. We&n; *&t;write large I/O&squot;s directly to disk bypassing the cache to avoid the extra&n; *&t;memory copy hits. Small writes are writeback cached&n; */
DECL|macro|CACHE_SMARTBACK
mdefine_line|#define CACHE_SMARTBACK&t;&t;19
multiline_comment|/*&t;Optimise for under powered controllers, especially on RAID1 and RAID0. We&n; *&t;write large I/O&squot;s directly to disk bypassing the cache to avoid the extra&n; *&t;memory copy hits. Small writes are writethrough cached. Suitable for devices&n; *&t;lacking battery backup&n; */
DECL|macro|CACHE_SMARTTHROUGH
mdefine_line|#define CACHE_SMARTTHROUGH&t;20
multiline_comment|/*&n; *&t;Ioctl structures&n; */
DECL|macro|BLKI2OGRSTRAT
mdefine_line|#define &t;BLKI2OGRSTRAT&t;_IOR(&squot;2&squot;, 1, int)
DECL|macro|BLKI2OGWSTRAT
mdefine_line|#define &t;BLKI2OGWSTRAT&t;_IOR(&squot;2&squot;, 2, int)
DECL|macro|BLKI2OSRSTRAT
mdefine_line|#define &t;BLKI2OSRSTRAT&t;_IOW(&squot;2&squot;, 3, int)
DECL|macro|BLKI2OSWSTRAT
mdefine_line|#define &t;BLKI2OSWSTRAT&t;_IOW(&squot;2&squot;, 4, int)
multiline_comment|/*&n; *&t;I2O Function codes&n; */
multiline_comment|/*&n; *&t;Executive Class&n; */
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
DECL|macro|I2O_CMD_BLOCK_POWER
mdefine_line|#define I2O_CMD_BLOCK_POWER&t;&t;0x70
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
multiline_comment|/* DetailedStatusCode defines for Block Storage Operation: Table 6-7 Detailed&n;   Status Codes.*/
DECL|macro|I2O_BSA_DSC_SUCCESS
mdefine_line|#define I2O_BSA_DSC_SUCCESS               0x0000
DECL|macro|I2O_BSA_DSC_MEDIA_ERROR
mdefine_line|#define I2O_BSA_DSC_MEDIA_ERROR           0x0001
DECL|macro|I2O_BSA_DSC_ACCESS_ERROR
mdefine_line|#define I2O_BSA_DSC_ACCESS_ERROR          0x0002
DECL|macro|I2O_BSA_DSC_DEVICE_FAILURE
mdefine_line|#define I2O_BSA_DSC_DEVICE_FAILURE        0x0003
DECL|macro|I2O_BSA_DSC_DEVICE_NOT_READY
mdefine_line|#define I2O_BSA_DSC_DEVICE_NOT_READY      0x0004
DECL|macro|I2O_BSA_DSC_MEDIA_NOT_PRESENT
mdefine_line|#define I2O_BSA_DSC_MEDIA_NOT_PRESENT     0x0005
DECL|macro|I2O_BSA_DSC_MEDIA_LOCKED
mdefine_line|#define I2O_BSA_DSC_MEDIA_LOCKED          0x0006
DECL|macro|I2O_BSA_DSC_MEDIA_FAILURE
mdefine_line|#define I2O_BSA_DSC_MEDIA_FAILURE         0x0007
DECL|macro|I2O_BSA_DSC_PROTOCOL_FAILURE
mdefine_line|#define I2O_BSA_DSC_PROTOCOL_FAILURE      0x0008
DECL|macro|I2O_BSA_DSC_BUS_FAILURE
mdefine_line|#define I2O_BSA_DSC_BUS_FAILURE           0x0009
DECL|macro|I2O_BSA_DSC_ACCESS_VIOLATION
mdefine_line|#define I2O_BSA_DSC_ACCESS_VIOLATION      0x000A
DECL|macro|I2O_BSA_DSC_WRITE_PROTECTED
mdefine_line|#define I2O_BSA_DSC_WRITE_PROTECTED       0x000B
DECL|macro|I2O_BSA_DSC_DEVICE_RESET
mdefine_line|#define I2O_BSA_DSC_DEVICE_RESET          0x000C
DECL|macro|I2O_BSA_DSC_VOLUME_CHANGED
mdefine_line|#define I2O_BSA_DSC_VOLUME_CHANGED        0x000D
DECL|macro|I2O_BSA_DSC_TIMEOUT
mdefine_line|#define I2O_BSA_DSC_TIMEOUT               0x000E
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
DECL|macro|ELEVEN_WORD_MSG_SIZE
mdefine_line|#define ELEVEN_WORD_MSG_SIZE&t;0x000B0000
DECL|macro|I2O_MESSAGE_SIZE
mdefine_line|#define I2O_MESSAGE_SIZE(x)&t;((x)&lt;&lt;16)
multiline_comment|/* Special TID Assignments */
DECL|macro|ADAPTER_TID
mdefine_line|#define ADAPTER_TID&t;&t;0
DECL|macro|HOST_TID
mdefine_line|#define HOST_TID&t;&t;1
DECL|macro|MSG_FRAME_SIZE
mdefine_line|#define MSG_FRAME_SIZE&t;&t;128&t;/* i2o_scsi assumes &gt;= 32 */
DECL|macro|REPLY_FRAME_SIZE
mdefine_line|#define REPLY_FRAME_SIZE&t;17
DECL|macro|SG_TABLESIZE
mdefine_line|#define SG_TABLESIZE&t;&t;30
DECL|macro|NMBR_MSG_FRAMES
mdefine_line|#define NMBR_MSG_FRAMES&t;&t;128
DECL|macro|MSG_POOL_SIZE
mdefine_line|#define MSG_POOL_SIZE&t;&t;(MSG_FRAME_SIZE*NMBR_MSG_FRAMES*sizeof(u32))
DECL|macro|I2O_POST_WAIT_OK
mdefine_line|#define I2O_POST_WAIT_OK&t;0
DECL|macro|I2O_POST_WAIT_TIMEOUT
mdefine_line|#define I2O_POST_WAIT_TIMEOUT&t;-ETIMEDOUT
DECL|macro|I2O_CONTEXT_LIST_MIN_LENGTH
mdefine_line|#define I2O_CONTEXT_LIST_MIN_LENGTH&t;15
DECL|macro|I2O_CONTEXT_LIST_USED
mdefine_line|#define I2O_CONTEXT_LIST_USED&t;&t;0x01
DECL|macro|I2O_CONTEXT_LIST_DELETED
mdefine_line|#define I2O_CONTEXT_LIST_DELETED&t;0x02
multiline_comment|/* timeouts */
DECL|macro|I2O_TIMEOUT_INIT_OUTBOUND_QUEUE
mdefine_line|#define I2O_TIMEOUT_INIT_OUTBOUND_QUEUE&t;15
DECL|macro|I2O_TIMEOUT_MESSAGE_GET
mdefine_line|#define I2O_TIMEOUT_MESSAGE_GET&t;&t;5
DECL|macro|I2O_TIMEOUT_RESET
mdefine_line|#define I2O_TIMEOUT_RESET&t;&t;30
DECL|macro|I2O_TIMEOUT_STATUS_GET
mdefine_line|#define I2O_TIMEOUT_STATUS_GET&t;&t;5
DECL|macro|I2O_TIMEOUT_LCT_GET
mdefine_line|#define I2O_TIMEOUT_LCT_GET&t;&t;360
DECL|macro|I2O_TIMEOUT_SCSI_SCB_ABORT
mdefine_line|#define I2O_TIMEOUT_SCSI_SCB_ABORT&t;240
multiline_comment|/* retries */
DECL|macro|I2O_HRT_GET_TRIES
mdefine_line|#define I2O_HRT_GET_TRIES&t;&t;3
DECL|macro|I2O_LCT_GET_TRIES
mdefine_line|#define I2O_LCT_GET_TRIES&t;&t;3
multiline_comment|/* request queue sizes */
DECL|macro|I2O_MAX_SECTORS
mdefine_line|#define I2O_MAX_SECTORS&t;&t;&t;1024
DECL|macro|I2O_MAX_SEGMENTS
mdefine_line|#define I2O_MAX_SEGMENTS&t;&t;128
DECL|macro|I2O_REQ_MEMPOOL_SIZE
mdefine_line|#define I2O_REQ_MEMPOOL_SIZE&t;&t;32
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#endif&t;&t;&t;&t;/* _I2O_H */
eof
