multiline_comment|/*&n; * Copyright (c) 2001 by David Brownell&n; * &n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY&n; * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software Foundation,&n; * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/*&n; * USB Host Controller Driver (usb_hcd) framework&n; *&n; * Since &quot;struct usb_bus&quot; is so thin, you can&squot;t share much code in it.&n; * This framework is a layer over that, and should be more sharable.&n; */
multiline_comment|/*-------------------------------------------------------------------------*/
DECL|struct|usb_hcd
r_struct
id|usb_hcd
(brace
multiline_comment|/* usb_bus.hcpriv points to this */
multiline_comment|/*&n;&t; * housekeeping&n;&t; */
DECL|member|bus
r_struct
id|usb_bus
op_star
id|bus
suffix:semicolon
multiline_comment|/* hcd is-a bus */
DECL|member|hcd_list
r_struct
id|list_head
id|hcd_list
suffix:semicolon
DECL|member|bus_name
r_const
r_char
op_star
id|bus_name
suffix:semicolon
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
macro_line|#ifdef&t;CONFIG_PCI
multiline_comment|/* a few non-PCI controllers exist, mostly for OHCI */
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
multiline_comment|/* pci is typical */
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
multiline_comment|/* each driver provides one of these, and hardware init support */
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
singleline_comment|// FIXME: rework generic-to-specific HCD linkage (specific contains generic)
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
singleline_comment|// frees configuration resources -- allocated as needed during
singleline_comment|// urb_enqueue, and not freed by urb_dequeue
DECL|member|free_config
r_void
(paren
op_star
id|free_config
)paren
(paren
r_struct
id|usb_hcd
op_star
id|hcd
comma
r_struct
id|usb_device
op_star
id|dev
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
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
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
multiline_comment|/* hub.h ... DeviceRemovable in 2.4.2-ac11, gone in 2.4.10 */
singleline_comment|// bleech -- resurfaced in 2.4.11 or 2.4.12
DECL|macro|bitmap
mdefine_line|#define bitmap &t;DeviceRemovable
multiline_comment|/*-------------------------------------------------------------------------*/
multiline_comment|/* random stuff */
DECL|macro|RUN_CONTEXT
mdefine_line|#define&t;RUN_CONTEXT (in_irq () ? &quot;in_irq&quot; &bslash;&n;&t;&t;: (in_interrupt () ? &quot;in_interrupt&quot; : &quot;can sleep&quot;))
eof
