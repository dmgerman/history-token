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
DECL|member|description
r_const
r_char
op_star
id|description
suffix:semicolon
multiline_comment|/* &quot;ehci-hcd&quot; etc */
DECL|member|rh_timer
r_struct
id|timer_list
id|rh_timer
suffix:semicolon
multiline_comment|/* drives root hub */
DECL|member|dev_list
r_struct
id|list_head
id|dev_list
suffix:semicolon
multiline_comment|/* devices on this bus */
DECL|member|work
r_struct
id|work_struct
id|work
suffix:semicolon
multiline_comment|/*&n;&t; * hardware info/state&n;&t; */
DECL|member|driver
r_struct
id|hc_driver
op_star
id|driver
suffix:semicolon
multiline_comment|/* hw-specific hooks */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* irq allocated */
DECL|member|regs
r_void
op_star
id|regs
suffix:semicolon
multiline_comment|/* device memory/io */
DECL|member|controller
r_struct
id|device
op_star
id|controller
suffix:semicolon
multiline_comment|/* handle to hardware */
multiline_comment|/* a few non-PCI controllers exist, mostly for OHCI */
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
multiline_comment|/* pci is typical */
macro_line|#ifdef&t;CONFIG_PCI
DECL|member|region
r_int
id|region
suffix:semicolon
multiline_comment|/* pci region for regs */
DECL|member|pci_state
id|u32
id|pci_state
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* for PM state save */
DECL|member|resume_count
id|atomic_t
id|resume_count
suffix:semicolon
multiline_comment|/* multiple resumes issue */
macro_line|#endif
DECL|macro|HCD_BUFFER_POOLS
mdefine_line|#define HCD_BUFFER_POOLS&t;4
DECL|member|pool
r_struct
id|pci_pool
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
DECL|macro|__SLEEPY
macro_line|#&t;define&t;__SLEEPY&t;&t;0x02
DECL|macro|__SUSPEND
macro_line|#&t;define&t;__SUSPEND&t;&t;0x04
DECL|macro|__TRANSIENT
macro_line|#&t;define&t;__TRANSIENT&t;&t;0x80
DECL|macro|USB_STATE_HALT
macro_line|#&t;define&t;USB_STATE_HALT&t;&t;0
DECL|macro|USB_STATE_RUNNING
macro_line|#&t;define&t;USB_STATE_RUNNING&t;(__ACTIVE)
DECL|macro|USB_STATE_READY
macro_line|#&t;define&t;USB_STATE_READY&t;&t;(__ACTIVE|__SLEEPY)
DECL|macro|USB_STATE_QUIESCING
macro_line|#&t;define&t;USB_STATE_QUIESCING&t;(__SUSPEND|__TRANSIENT|__ACTIVE)
DECL|macro|USB_STATE_RESUMING
macro_line|#&t;define&t;USB_STATE_RESUMING&t;(__SUSPEND|__TRANSIENT)
DECL|macro|USB_STATE_SUSPENDED
macro_line|#&t;define&t;USB_STATE_SUSPENDED&t;(__SUSPEND)
DECL|macro|HCD_IS_RUNNING
mdefine_line|#define&t;HCD_IS_RUNNING(state) ((state) &amp; __ACTIVE)
DECL|macro|HCD_IS_SUSPENDED
mdefine_line|#define&t;HCD_IS_SUSPENDED(state) ((state) &amp; __SUSPEND)
multiline_comment|/* more shared queuing code would be good; it should support&n;&t; * smarter scheduling, handle transaction translators, etc;&n;&t; * input size of periodic table to an interrupt scheduler. &n;&t; * (ohci 32, uhci 1024, ehci 256/512/1024).&n;&t; */
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
DECL|struct|hcd_dev
r_struct
id|hcd_dev
(brace
multiline_comment|/* usb_device.hcpriv points to this */
DECL|member|dev_list
r_struct
id|list_head
id|dev_list
suffix:semicolon
multiline_comment|/* on this hcd */
DECL|member|urb_list
r_struct
id|list_head
id|urb_list
suffix:semicolon
multiline_comment|/* pending on this dev */
multiline_comment|/* per-configuration HC/HCD state, such as QH or ED */
DECL|member|ep
r_void
op_star
id|ep
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
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
DECL|member|allocate
r_int
(paren
op_star
id|allocate
)paren
(paren
r_struct
id|usb_device
op_star
)paren
suffix:semicolon
DECL|member|deallocate
r_int
(paren
op_star
id|deallocate
)paren
(paren
r_struct
id|usb_device
op_star
)paren
suffix:semicolon
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
r_int
id|bEndpointAddress
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
multiline_comment|/* irq handler */
DECL|member|irq
r_void
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
multiline_comment|/* memory lifecycle */
DECL|member|hcd_alloc
r_struct
id|usb_hcd
op_star
(paren
op_star
id|hcd_alloc
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|hcd_free
r_void
(paren
op_star
id|hcd_free
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
id|hcd_dev
op_star
id|dev
comma
r_int
id|bEndpointAddress
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
r_void
id|usb_bus_init
(paren
r_struct
id|usb_bus
op_star
id|bus
)paren
suffix:semicolon
r_extern
r_void
id|usb_rh_status_dequeue
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
singleline_comment|// FIXME:  see Documentation/power/pci.txt (2.4.6 and later?)
singleline_comment|// extern int usb_hcd_pci_save_state (struct pci_dev *dev, u32 state);
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
singleline_comment|// extern int usb_hcd_pci_enable_wake (struct pci_dev *dev, u32 state, int flg);
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
r_struct
id|usb_operations
id|usb_hcd_operations
suffix:semicolon
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
r_int
id|usb_new_device
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_struct
id|device
op_star
id|parent
)paren
suffix:semicolon
r_extern
r_void
id|usb_choose_address
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
multiline_comment|/* exported to hub driver ONLY to support usb_reset_device () */
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
r_extern
r_int
id|usb_set_address
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* use these only before the device&squot;s address has been set */
DECL|macro|usb_snddefctrl
mdefine_line|#define usb_snddefctrl(dev)&t;&t;((PIPE_CONTROL &lt;&lt; 30))
DECL|macro|usb_rcvdefctrl
mdefine_line|#define usb_rcvdefctrl(dev)&t;&t;((PIPE_CONTROL &lt;&lt; 30) | USB_DIR_IN)
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
multiline_comment|/* table 9.6 standard features */
DECL|macro|DEVICE_REMOTE_WAKEUP
mdefine_line|#define DEVICE_REMOTE_WAKEUP&t;1
DECL|macro|ENDPOINT_HALT
mdefine_line|#define ENDPOINT_HALT&t;&t;0
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
mdefine_line|#define HS_USECS_ISO(bytes) NS_TO_US ( ((long)(38 * 8 * 2.083)) &bslash;&n;&t;+ ((2083UL * (3167 + BitTime (bytes)))/1000) &bslash;&n;&t;+ USB2_HOST_DELAY)
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
id|usb_register_bus
(paren
r_struct
id|usb_bus
op_star
)paren
suffix:semicolon
r_extern
r_void
id|usb_deregister_bus
(paren
r_struct
id|usb_bus
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_register_root_hub
(paren
r_struct
id|usb_device
op_star
id|usb_dev
comma
r_struct
id|device
op_star
id|parent_dev
)paren
suffix:semicolon
multiline_comment|/* for portability to 2.4, hcds should call this */
DECL|function|hcd_register_root
r_static
r_inline
r_int
id|hcd_register_root
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_return
id|usb_register_root_hub
(paren
id|hcd_to_bus
(paren
id|hcd
)paren
op_member_access_from_pointer
id|root_hub
comma
id|hcd-&gt;controller
)paren
suffix:semicolon
)brace
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
DECL|macro|usb_endpoint_halt
mdefine_line|#define usb_endpoint_halt(dev, ep, out) ((dev)-&gt;halted[out] |= (1 &lt;&lt; (ep)))
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
