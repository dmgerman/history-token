multiline_comment|/*&n; * Copyright (c) 2001-2002 by David Brownell&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY&n; * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifdef __KERNEL__
multiline_comment|/* This file contains declarations of usbcore internals that are mostly&n; * used or exposed by Host Controller Drivers.&n; */
multiline_comment|/*&n; * USB Packet IDs (PIDs)&n; */
DECL|macro|USB_PID_UNDEF_0
mdefine_line|#define USB_PID_UNDEF_0&t;&t;&t;0xf0
DECL|macro|USB_PID_OUT
mdefine_line|#define USB_PID_OUT&t;&t;&t;0xe1
DECL|macro|USB_PID_ACK
mdefine_line|#define USB_PID_ACK&t;&t;&t;0xd2
DECL|macro|USB_PID_DATA0
mdefine_line|#define USB_PID_DATA0&t;&t;&t;0xc3
DECL|macro|USB_PID_PING
mdefine_line|#define USB_PID_PING&t;&t;&t;0xb4&t;/* USB 2.0 */
DECL|macro|USB_PID_SOF
mdefine_line|#define USB_PID_SOF&t;&t;&t;0xa5
DECL|macro|USB_PID_NYET
mdefine_line|#define USB_PID_NYET&t;&t;&t;0x96&t;/* USB 2.0 */
DECL|macro|USB_PID_DATA2
mdefine_line|#define USB_PID_DATA2&t;&t;&t;0x87&t;/* USB 2.0 */
DECL|macro|USB_PID_SPLIT
mdefine_line|#define USB_PID_SPLIT&t;&t;&t;0x78&t;/* USB 2.0 */
DECL|macro|USB_PID_IN
mdefine_line|#define USB_PID_IN&t;&t;&t;0x69
DECL|macro|USB_PID_NAK
mdefine_line|#define USB_PID_NAK&t;&t;&t;0x5a
DECL|macro|USB_PID_DATA1
mdefine_line|#define USB_PID_DATA1&t;&t;&t;0x4b
DECL|macro|USB_PID_PREAMBLE
mdefine_line|#define USB_PID_PREAMBLE&t;&t;0x3c&t;/* Token mode */
DECL|macro|USB_PID_ERR
mdefine_line|#define USB_PID_ERR&t;&t;&t;0x3c&t;/* USB 2.0: handshake mode */
DECL|macro|USB_PID_SETUP
mdefine_line|#define USB_PID_SETUP&t;&t;&t;0x2d
DECL|macro|USB_PID_STALL
mdefine_line|#define USB_PID_STALL&t;&t;&t;0x1e
DECL|macro|USB_PID_MDATA
mdefine_line|#define USB_PID_MDATA&t;&t;&t;0x0f&t;/* USB 2.0 */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * USB Host Controller Driver (usb_hcd) framework&n; *&n; * Since &quot;struct usb_bus&quot; is so thin, you can&squot;t share much code in it.&n; * This framework is a layer over that, and should be more sharable.&n; */
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|struct|usb_hcd
r_struct
id|usb_hcd
(brace
multiline_comment|/* usb_bus.hcpriv points to this */
multiline_comment|/*&n;&t; * housekeeping&n;&t; */
DECL|member|self
r_struct
id|usb_bus
id|self
suffix:semicolon
multiline_comment|/* hcd is-a bus */
DECL|member|product_desc
r_const
r_char
op_star
id|product_desc
suffix:semicolon
multiline_comment|/* product/vendor string */
DECL|member|irq_descr
r_char
id|irq_descr
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* driver + bus # */
DECL|member|rh_timer
r_struct
id|timer_list
id|rh_timer
suffix:semicolon
multiline_comment|/* drives root hub */
multiline_comment|/*&n;&t; * hardware info/state&n;&t; */
DECL|member|driver
r_const
r_struct
id|hc_driver
op_star
id|driver
suffix:semicolon
multiline_comment|/* hw-specific hooks */
DECL|member|saw_irq
r_int
id|saw_irq
suffix:colon
l_int|1
suffix:semicolon
DECL|member|can_wakeup
r_int
id|can_wakeup
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* hw supports wakeup? */
DECL|member|remote_wakeup
r_int
id|remote_wakeup
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* sw should use wakeup? */
DECL|member|rh_registered
r_int
id|rh_registered
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* is root hub registered? */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* irq allocated */
DECL|member|regs
r_void
id|__iomem
op_star
id|regs
suffix:semicolon
multiline_comment|/* device memory/io */
DECL|member|rsrc_start
id|u64
id|rsrc_start
suffix:semicolon
multiline_comment|/* memory/io resource start */
DECL|member|rsrc_len
id|u64
id|rsrc_len
suffix:semicolon
multiline_comment|/* memory/io resource length */
DECL|macro|HCD_BUFFER_POOLS
mdefine_line|#define HCD_BUFFER_POOLS&t;4
DECL|member|pool
r_struct
id|dma_pool
op_star
id|pool
(braket
id|HCD_BUFFER_POOLS
)braket
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|macro|__ACTIVE
macro_line|#&t;define&t;__ACTIVE&t;&t;0x01
DECL|macro|__SUSPEND
macro_line|#&t;define&t;__SUSPEND&t;&t;0x04
DECL|macro|__TRANSIENT
macro_line|#&t;define&t;__TRANSIENT&t;&t;0x80
DECL|macro|HC_STATE_HALT
macro_line|#&t;define&t;HC_STATE_HALT&t;&t;0
DECL|macro|HC_STATE_RUNNING
macro_line|#&t;define&t;HC_STATE_RUNNING&t;(__ACTIVE)
DECL|macro|HC_STATE_QUIESCING
macro_line|#&t;define&t;HC_STATE_QUIESCING&t;(__SUSPEND|__TRANSIENT|__ACTIVE)
DECL|macro|HC_STATE_RESUMING
macro_line|#&t;define&t;HC_STATE_RESUMING&t;(__SUSPEND|__TRANSIENT)
DECL|macro|HC_STATE_SUSPENDED
macro_line|#&t;define&t;HC_STATE_SUSPENDED&t;(__SUSPEND)
DECL|macro|HC_IS_RUNNING
mdefine_line|#define&t;HC_IS_RUNNING(state) ((state) &amp; __ACTIVE)
DECL|macro|HC_IS_SUSPENDED
mdefine_line|#define&t;HC_IS_SUSPENDED(state) ((state) &amp; __SUSPEND)
multiline_comment|/* more shared queuing code would be good; it should support&n;&t; * smarter scheduling, handle transaction translators, etc;&n;&t; * input size of periodic table to an interrupt scheduler. &n;&t; * (ohci 32, uhci 1024, ehci 256/512/1024).&n;&t; */
multiline_comment|/* The HC driver&squot;s private data is stored at the end of&n;&t; * this structure.&n;&t; */
DECL|member|hcd_priv
r_int
r_int
id|hcd_priv
(braket
l_int|0
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
r_sizeof
(paren
r_int
r_int
)paren
)paren
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* 2.4 does this a bit differently ... */
DECL|function|hcd_to_bus
r_static
r_inline
r_struct
id|usb_bus
op_star
id|hcd_to_bus
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_return
op_amp
id|hcd-&gt;self
suffix:semicolon
)brace
singleline_comment|// urb.hcpriv is really hardware-specific
DECL|struct|hcd_timeout
r_struct
id|hcd_timeout
(brace
multiline_comment|/* timeouts we allocate */
DECL|member|timeout_list
r_struct
id|list_head
id|timeout_list
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * FIXME usb_operations should vanish or become hc_driver,&n; * when usb_bus and usb_hcd become the same thing.&n; */
DECL|struct|usb_operations
r_struct
id|usb_operations
(brace
DECL|member|get_frame_number
r_int
(paren
op_star
id|get_frame_number
)paren
(paren
r_struct
id|usb_device
op_star
id|usb_dev
)paren
suffix:semicolon
DECL|member|submit_urb
r_int
(paren
op_star
id|submit_urb
)paren
(paren
r_struct
id|urb
op_star
id|urb
comma
r_int
id|mem_flags
)paren
suffix:semicolon
DECL|member|unlink_urb
r_int
(paren
op_star
id|unlink_urb
)paren
(paren
r_struct
id|urb
op_star
id|urb
comma
r_int
id|status
)paren
suffix:semicolon
multiline_comment|/* allocate dma-consistent buffer for URB_DMA_NOMAPPING */
DECL|member|buffer_alloc
r_void
op_star
(paren
op_star
id|buffer_alloc
)paren
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_int
id|size
comma
r_int
id|mem_flags
comma
id|dma_addr_t
op_star
id|dma
)paren
suffix:semicolon
DECL|member|buffer_free
r_void
(paren
op_star
id|buffer_free
)paren
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_int
id|size
comma
r_void
op_star
id|addr
comma
id|dma_addr_t
id|dma
)paren
suffix:semicolon
DECL|member|disable
r_void
(paren
op_star
id|disable
)paren
(paren
r_struct
id|usb_device
op_star
id|udev
comma
r_struct
id|usb_host_endpoint
op_star
id|ep
)paren
suffix:semicolon
multiline_comment|/* global suspend/resume of bus */
DECL|member|hub_suspend
r_int
(paren
op_star
id|hub_suspend
)paren
(paren
r_struct
id|usb_bus
op_star
)paren
suffix:semicolon
DECL|member|hub_resume
r_int
(paren
op_star
id|hub_resume
)paren
(paren
r_struct
id|usb_bus
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* each driver provides one of these, and hardware init support */
r_struct
id|pt_regs
suffix:semicolon
DECL|struct|hc_driver
r_struct
id|hc_driver
(brace
DECL|member|description
r_const
r_char
op_star
id|description
suffix:semicolon
multiline_comment|/* &quot;ehci-hcd&quot; etc */
DECL|member|product_desc
r_const
r_char
op_star
id|product_desc
suffix:semicolon
multiline_comment|/* product/vendor string */
DECL|member|hcd_priv_size
r_int
id|hcd_priv_size
suffix:semicolon
multiline_comment|/* size of private data */
multiline_comment|/* irq handler */
DECL|member|irq
id|irqreturn_t
(paren
op_star
id|irq
)paren
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|macro|HCD_MEMORY
mdefine_line|#define&t;HCD_MEMORY&t;0x0001&t;&t;/* HC regs use memory (else I/O) */
DECL|macro|HCD_USB11
mdefine_line|#define&t;HCD_USB11&t;0x0010&t;&t;/* USB 1.1 */
DECL|macro|HCD_USB2
mdefine_line|#define&t;HCD_USB2&t;0x0020&t;&t;/* USB 2.0 */
multiline_comment|/* called to init HCD and root hub */
DECL|member|reset
r_int
(paren
op_star
id|reset
)paren
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
suffix:semicolon
DECL|member|start
r_int
(paren
op_star
id|start
)paren
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
suffix:semicolon
multiline_comment|/* NOTE:  these suspend/resume calls relate to the HC as&n;&t; * a whole, not just the root hub; they&squot;re for bus glue.&n;&t; */
multiline_comment|/* called after all devices were suspended */
DECL|member|suspend
r_int
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
id|u32
id|state
)paren
suffix:semicolon
multiline_comment|/* called before any devices get resumed */
DECL|member|resume
r_int
(paren
op_star
id|resume
)paren
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
suffix:semicolon
multiline_comment|/* cleanly make HCD stop writing memory and doing I/O */
DECL|member|stop
r_void
(paren
op_star
id|stop
)paren
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
suffix:semicolon
multiline_comment|/* return current frame number */
DECL|member|get_frame_number
r_int
(paren
op_star
id|get_frame_number
)paren
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
suffix:semicolon
multiline_comment|/* manage i/o requests, device state */
DECL|member|urb_enqueue
r_int
(paren
op_star
id|urb_enqueue
)paren
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_struct
id|usb_host_endpoint
op_star
id|ep
comma
r_struct
id|urb
op_star
id|urb
comma
r_int
id|mem_flags
)paren
suffix:semicolon
DECL|member|urb_dequeue
r_int
(paren
op_star
id|urb_dequeue
)paren
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
multiline_comment|/* hw synch, freeing endpoint resources that urb_dequeue can&squot;t */
DECL|member|endpoint_disable
r_void
(paren
op_star
id|endpoint_disable
)paren
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_struct
id|usb_host_endpoint
op_star
id|ep
)paren
suffix:semicolon
multiline_comment|/* root hub support */
DECL|member|hub_status_data
r_int
(paren
op_star
id|hub_status_data
)paren
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|hub_control
r_int
(paren
op_star
id|hub_control
)paren
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
id|u16
id|typeReq
comma
id|u16
id|wValue
comma
id|u16
id|wIndex
comma
r_char
op_star
id|buf
comma
id|u16
id|wLength
)paren
suffix:semicolon
DECL|member|hub_suspend
r_int
(paren
op_star
id|hub_suspend
)paren
(paren
r_struct
id|usb_hcd
op_star
)paren
suffix:semicolon
DECL|member|hub_resume
r_int
(paren
op_star
id|hub_resume
)paren
(paren
r_struct
id|usb_hcd
op_star
)paren
suffix:semicolon
DECL|member|start_port_reset
r_int
(paren
op_star
id|start_port_reset
)paren
(paren
r_struct
id|usb_hcd
op_star
comma
r_int
id|port_num
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|usb_hcd_giveback_urb
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_struct
id|usb_hcd
op_star
id|usb_create_hcd
(paren
r_const
r_struct
id|hc_driver
op_star
id|driver
comma
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|bus_name
)paren
suffix:semicolon
r_extern
r_void
id|usb_put_hcd
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
suffix:semicolon
r_extern
r_int
id|usb_add_hcd
c_func
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_int
r_int
id|irqnum
comma
r_int
r_int
id|irqflags
)paren
suffix:semicolon
r_extern
r_void
id|usb_remove_hcd
c_func
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
r_struct
id|pci_dev
suffix:semicolon
r_struct
id|pci_device_id
suffix:semicolon
r_extern
r_int
id|usb_hcd_pci_probe
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
suffix:semicolon
r_extern
r_void
id|usb_hcd_pci_remove
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
r_extern
r_int
id|usb_hcd_pci_suspend
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u32
id|state
)paren
suffix:semicolon
r_extern
r_int
id|usb_hcd_pci_resume
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PM */
macro_line|#endif /* CONFIG_PCI */
multiline_comment|/* pci-ish (pdev null is ok) buffer alloc/mapping support */
r_int
id|hcd_buffer_create
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
suffix:semicolon
r_void
id|hcd_buffer_destroy
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
suffix:semicolon
r_void
op_star
id|hcd_buffer_alloc
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_int
id|size
comma
r_int
id|mem_flags
comma
id|dma_addr_t
op_star
id|dma
)paren
suffix:semicolon
r_void
id|hcd_buffer_free
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_int
id|size
comma
r_void
op_star
id|addr
comma
id|dma_addr_t
id|dma
)paren
suffix:semicolon
multiline_comment|/* generic bus glue, needed for host controllers that don&squot;t use PCI */
r_extern
id|irqreturn_t
id|usb_hcd_irq
(paren
r_int
id|irq
comma
r_void
op_star
id|__hcd
comma
r_struct
id|pt_regs
op_star
id|r
)paren
suffix:semicolon
r_extern
r_void
id|usb_hc_died
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
suffix:semicolon
multiline_comment|/* -------------------------------------------------------------------------- */
multiline_comment|/* Enumeration is only for the hub driver, or HCD virtual root hubs */
r_extern
r_struct
id|usb_device
op_star
id|usb_alloc_dev
c_func
(paren
r_struct
id|usb_device
op_star
id|parent
comma
r_struct
id|usb_bus
op_star
comma
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
id|usb_new_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|usb_disconnect
c_func
(paren
r_struct
id|usb_device
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_get_configuration
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|usb_destroy_configuration
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * HCD Root Hub support&n; */
macro_line|#include &quot;hub.h&quot;
multiline_comment|/* (shifted) direction/type/recipient from the USB 2.0 spec, table 9.2 */
DECL|macro|DeviceRequest
mdefine_line|#define DeviceRequest &bslash;&n;&t;((USB_DIR_IN|USB_TYPE_STANDARD|USB_RECIP_DEVICE)&lt;&lt;8)
DECL|macro|DeviceOutRequest
mdefine_line|#define DeviceOutRequest &bslash;&n;&t;((USB_DIR_OUT|USB_TYPE_STANDARD|USB_RECIP_DEVICE)&lt;&lt;8)
DECL|macro|InterfaceRequest
mdefine_line|#define InterfaceRequest &bslash;&n;&t;((USB_DIR_IN|USB_TYPE_STANDARD|USB_RECIP_INTERFACE)&lt;&lt;8)
DECL|macro|EndpointRequest
mdefine_line|#define EndpointRequest &bslash;&n;&t;((USB_DIR_IN|USB_TYPE_STANDARD|USB_RECIP_INTERFACE)&lt;&lt;8)
DECL|macro|EndpointOutRequest
mdefine_line|#define EndpointOutRequest &bslash;&n;&t;((USB_DIR_OUT|USB_TYPE_STANDARD|USB_RECIP_INTERFACE)&lt;&lt;8)
multiline_comment|/* class requests from the USB 2.0 hub spec, table 11-15 */
multiline_comment|/* GetBusState and SetHubDescriptor are optional, omitted */
DECL|macro|ClearHubFeature
mdefine_line|#define ClearHubFeature&t;&t;(0x2000 | USB_REQ_CLEAR_FEATURE)
DECL|macro|ClearPortFeature
mdefine_line|#define ClearPortFeature&t;(0x2300 | USB_REQ_CLEAR_FEATURE)
DECL|macro|GetHubDescriptor
mdefine_line|#define GetHubDescriptor&t;(0xa000 | USB_REQ_GET_DESCRIPTOR)
DECL|macro|GetHubStatus
mdefine_line|#define GetHubStatus&t;&t;(0xa000 | USB_REQ_GET_STATUS)
DECL|macro|GetPortStatus
mdefine_line|#define GetPortStatus&t;&t;(0xa300 | USB_REQ_GET_STATUS)
DECL|macro|SetHubFeature
mdefine_line|#define SetHubFeature&t;&t;(0x2000 | USB_REQ_SET_FEATURE)
DECL|macro|SetPortFeature
mdefine_line|#define SetPortFeature&t;&t;(0x2300 | USB_REQ_SET_FEATURE)
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * Generic bandwidth allocation constants/support&n; */
DECL|macro|FRAME_TIME_USECS
mdefine_line|#define FRAME_TIME_USECS&t;1000L
DECL|macro|BitTime
mdefine_line|#define BitTime(bytecount)  (7 * 8 * bytecount / 6)  /* with integer truncation */
multiline_comment|/* Trying not to use worst-case bit-stuffing&n;                   of (7/6 * 8 * bytecount) = 9.33 * bytecount */
multiline_comment|/* bytecount = data payload byte count */
DECL|macro|NS_TO_US
mdefine_line|#define NS_TO_US(ns)&t;((ns + 500L) / 1000L)
multiline_comment|/* convert &amp; round nanoseconds to microseconds */
r_extern
r_void
id|usb_claim_bandwidth
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_struct
id|urb
op_star
id|urb
comma
r_int
id|bustime
comma
r_int
id|isoc
)paren
suffix:semicolon
r_extern
r_void
id|usb_release_bandwidth
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_struct
id|urb
op_star
id|urb
comma
r_int
id|isoc
)paren
suffix:semicolon
multiline_comment|/*&n; * Full/low speed bandwidth allocation constants/support.&n; */
DECL|macro|BW_HOST_DELAY
mdefine_line|#define BW_HOST_DELAY&t;1000L&t;&t;/* nanoseconds */
DECL|macro|BW_HUB_LS_SETUP
mdefine_line|#define BW_HUB_LS_SETUP&t;333L&t;&t;/* nanoseconds */
multiline_comment|/* 4 full-speed bit times (est.) */
DECL|macro|FRAME_TIME_BITS
mdefine_line|#define FRAME_TIME_BITS         12000L&t;&t;/* frame = 1 millisecond */
DECL|macro|FRAME_TIME_MAX_BITS_ALLOC
mdefine_line|#define FRAME_TIME_MAX_BITS_ALLOC&t;(90L * FRAME_TIME_BITS / 100L)
DECL|macro|FRAME_TIME_MAX_USECS_ALLOC
mdefine_line|#define FRAME_TIME_MAX_USECS_ALLOC&t;(90L * FRAME_TIME_USECS / 100L)
r_extern
r_int
id|usb_check_bandwidth
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
multiline_comment|/*&n; * Ceiling microseconds (typical) for that many bytes at high speed&n; * ISO is a bit less, no ACK ... from USB 2.0 spec, 5.11.3 (and needed&n; * to preallocate bandwidth)&n; */
DECL|macro|USB2_HOST_DELAY
mdefine_line|#define USB2_HOST_DELAY&t;5&t;/* nsec, guess */
DECL|macro|HS_USECS
mdefine_line|#define HS_USECS(bytes) NS_TO_US ( ((55 * 8 * 2083)/1000) &bslash;&n;&t;+ ((2083UL * (3167 + BitTime (bytes)))/1000) &bslash;&n;&t;+ USB2_HOST_DELAY)
DECL|macro|HS_USECS_ISO
mdefine_line|#define HS_USECS_ISO(bytes) NS_TO_US ( ((38 * 8 * 2083)/1000) &bslash;&n;&t;+ ((2083UL * (3167 + BitTime (bytes)))/1000) &bslash;&n;&t;+ USB2_HOST_DELAY)
r_extern
r_int
id|usb_calc_bus_time
(paren
r_int
id|speed
comma
r_int
id|is_input
comma
r_int
id|isoc
comma
r_int
id|bytecount
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
r_extern
r_struct
id|usb_bus
op_star
id|usb_alloc_bus
(paren
r_struct
id|usb_operations
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_hcd_register_root_hub
(paren
r_struct
id|usb_device
op_star
id|usb_dev
comma
r_struct
id|usb_hcd
op_star
id|hcd
)paren
suffix:semicolon
r_extern
r_void
id|usb_hcd_resume_root_hub
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
suffix:semicolon
r_extern
r_void
id|usb_set_device_state
c_func
(paren
r_struct
id|usb_device
op_star
id|udev
comma
r_enum
id|usb_device_state
id|new_state
)paren
suffix:semicolon
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* exported only within usbcore */
r_extern
r_struct
id|list_head
id|usb_bus_list
suffix:semicolon
r_extern
r_struct
id|semaphore
id|usb_bus_list_lock
suffix:semicolon
r_extern
id|wait_queue_head_t
id|usb_kill_urb_queue
suffix:semicolon
r_extern
r_struct
id|usb_bus
op_star
id|usb_bus_get
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_void
id|usb_bus_put
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_int
id|usb_find_interface_driver
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_struct
id|usb_interface
op_star
id|interface
)paren
suffix:semicolon
DECL|macro|usb_endpoint_out
mdefine_line|#define usb_endpoint_out(ep_dir)&t;(!((ep_dir) &amp; USB_DIR_IN))
multiline_comment|/*&n; * USB device fs stuff&n; */
macro_line|#ifdef CONFIG_USB_DEVICEFS
multiline_comment|/*&n; * these are expected to be called from the USB core/hub thread&n; * with the kernel lock held&n; */
r_extern
r_void
id|usbfs_add_bus
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_void
id|usbfs_remove_bus
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_void
id|usbfs_add_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|usbfs_remove_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|usbfs_update_special
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|usbfs_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|usbfs_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else /* CONFIG_USB_DEVICEFS */
DECL|function|usbfs_add_bus
r_static
r_inline
r_void
id|usbfs_add_bus
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
(brace
)brace
DECL|function|usbfs_remove_bus
r_static
r_inline
r_void
id|usbfs_remove_bus
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
(brace
)brace
DECL|function|usbfs_add_device
r_static
r_inline
r_void
id|usbfs_add_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
)brace
DECL|function|usbfs_remove_device
r_static
r_inline
r_void
id|usbfs_remove_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
)brace
DECL|function|usbfs_update_special
r_static
r_inline
r_void
id|usbfs_update_special
(paren
r_void
)paren
(brace
)brace
DECL|function|usbfs_init
r_static
r_inline
r_int
id|usbfs_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usbfs_cleanup
r_static
r_inline
r_void
id|usbfs_cleanup
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* CONFIG_USB_DEVICEFS */
multiline_comment|/*-------------------------------------------------------------------------*/
macro_line|#if defined(CONFIG_USB_MON) || defined(CONFIG_USB_MON_MODULE)
DECL|struct|usb_mon_operations
r_struct
id|usb_mon_operations
(brace
DECL|member|urb_submit
r_void
(paren
op_star
id|urb_submit
)paren
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
DECL|member|urb_submit_error
r_void
(paren
op_star
id|urb_submit_error
)paren
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_struct
id|urb
op_star
id|urb
comma
r_int
id|err
)paren
suffix:semicolon
DECL|member|urb_complete
r_void
(paren
op_star
id|urb_complete
)paren
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
multiline_comment|/* void (*urb_unlink)(struct usb_bus *bus, struct urb *urb); */
DECL|member|bus_add
r_void
(paren
op_star
id|bus_add
)paren
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
suffix:semicolon
DECL|member|bus_remove
r_void
(paren
op_star
id|bus_remove
)paren
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|usb_mon_operations
op_star
id|mon_ops
suffix:semicolon
DECL|function|usbmon_urb_submit
r_static
r_inline
r_void
id|usbmon_urb_submit
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_if
c_cond
(paren
id|bus-&gt;monitored
)paren
(paren
op_star
id|mon_ops-&gt;urb_submit
)paren
(paren
id|bus
comma
id|urb
)paren
suffix:semicolon
)brace
DECL|function|usbmon_urb_submit_error
r_static
r_inline
r_void
id|usbmon_urb_submit_error
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_struct
id|urb
op_star
id|urb
comma
r_int
id|error
)paren
(brace
r_if
c_cond
(paren
id|bus-&gt;monitored
)paren
(paren
op_star
id|mon_ops-&gt;urb_submit_error
)paren
(paren
id|bus
comma
id|urb
comma
id|error
)paren
suffix:semicolon
)brace
DECL|function|usbmon_urb_complete
r_static
r_inline
r_void
id|usbmon_urb_complete
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_if
c_cond
(paren
id|bus-&gt;monitored
)paren
(paren
op_star
id|mon_ops-&gt;urb_complete
)paren
(paren
id|bus
comma
id|urb
)paren
suffix:semicolon
)brace
DECL|function|usbmon_notify_bus_add
r_static
r_inline
r_void
id|usbmon_notify_bus_add
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
(brace
r_if
c_cond
(paren
id|mon_ops
)paren
(paren
op_star
id|mon_ops-&gt;bus_add
)paren
(paren
id|bus
)paren
suffix:semicolon
)brace
DECL|function|usbmon_notify_bus_remove
r_static
r_inline
r_void
id|usbmon_notify_bus_remove
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
(brace
r_if
c_cond
(paren
id|mon_ops
)paren
(paren
op_star
id|mon_ops-&gt;bus_remove
)paren
(paren
id|bus
)paren
suffix:semicolon
)brace
r_int
id|usb_mon_register
c_func
(paren
r_struct
id|usb_mon_operations
op_star
id|ops
)paren
suffix:semicolon
r_void
id|usb_mon_deregister
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
DECL|function|usbmon_urb_submit
r_static
r_inline
r_void
id|usbmon_urb_submit
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_struct
id|urb
op_star
id|urb
)paren
(brace
)brace
DECL|function|usbmon_urb_submit_error
r_static
r_inline
r_void
id|usbmon_urb_submit_error
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_struct
id|urb
op_star
id|urb
comma
r_int
id|error
)paren
(brace
)brace
DECL|function|usbmon_urb_complete
r_static
r_inline
r_void
id|usbmon_urb_complete
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_struct
id|urb
op_star
id|urb
)paren
(brace
)brace
DECL|function|usbmon_notify_bus_add
r_static
r_inline
r_void
id|usbmon_notify_bus_add
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
(brace
)brace
DECL|function|usbmon_notify_bus_remove
r_static
r_inline
r_void
id|usbmon_notify_bus_remove
c_func
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
(brace
)brace
macro_line|#endif /* CONFIG_USB_MON */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* hub.h ... DeviceRemovable in 2.4.2-ac11, gone in 2.4.10 */
singleline_comment|// bleech -- resurfaced in 2.4.11 or 2.4.12
DECL|macro|bitmap
mdefine_line|#define bitmap &t;DeviceRemovable
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* random stuff */
DECL|macro|RUN_CONTEXT
mdefine_line|#define&t;RUN_CONTEXT (in_irq () ? &quot;in_irq&quot; &bslash;&n;&t;&t;: (in_interrupt () ? &quot;in_interrupt&quot; : &quot;can sleep&quot;))
macro_line|#endif /* __KERNEL__ */
eof
