multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;usbdevice_fs.h  --  USB device file system.&n; *&n; *&t;Copyright (C) 2000&n; *          Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  History:&n; *   0.1  04.01.2000  Created&n; *&n; *  $Id: usbdevice_fs.h,v 1.1 2000/01/06 18:40:41 tom Exp $&n; */
multiline_comment|/*****************************************************************************/
macro_line|#ifndef _LINUX_USBDEVICE_FS_H
DECL|macro|_LINUX_USBDEVICE_FS_H
mdefine_line|#define _LINUX_USBDEVICE_FS_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* --------------------------------------------------------------------- */
DECL|macro|USBDEVICE_SUPER_MAGIC
mdefine_line|#define USBDEVICE_SUPER_MAGIC 0x9fa2
multiline_comment|/* usbdevfs ioctl codes */
DECL|struct|usbdevfs_ctrltransfer
r_struct
id|usbdevfs_ctrltransfer
(brace
DECL|member|requesttype
id|__u8
id|requesttype
suffix:semicolon
DECL|member|request
id|__u8
id|request
suffix:semicolon
DECL|member|value
id|__u16
id|value
suffix:semicolon
DECL|member|index
id|__u16
id|index
suffix:semicolon
DECL|member|length
id|__u16
id|length
suffix:semicolon
DECL|member|timeout
id|__u32
id|timeout
suffix:semicolon
multiline_comment|/* in milliseconds */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|usbdevfs_bulktransfer
r_struct
id|usbdevfs_bulktransfer
(brace
DECL|member|ep
r_int
r_int
id|ep
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* in milliseconds */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|usbdevfs_setinterface
r_struct
id|usbdevfs_setinterface
(brace
DECL|member|interface
r_int
r_int
id|interface
suffix:semicolon
DECL|member|altsetting
r_int
r_int
id|altsetting
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|usbdevfs_disconnectsignal
r_struct
id|usbdevfs_disconnectsignal
(brace
DECL|member|signr
r_int
r_int
id|signr
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|USBDEVFS_MAXDRIVERNAME
mdefine_line|#define USBDEVFS_MAXDRIVERNAME 255
DECL|struct|usbdevfs_getdriver
r_struct
id|usbdevfs_getdriver
(brace
DECL|member|interface
r_int
r_int
id|interface
suffix:semicolon
DECL|member|driver
r_char
id|driver
(braket
id|USBDEVFS_MAXDRIVERNAME
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|usbdevfs_connectinfo
r_struct
id|usbdevfs_connectinfo
(brace
DECL|member|devnum
r_int
r_int
id|devnum
suffix:semicolon
DECL|member|slow
r_int
r_char
id|slow
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|USBDEVFS_URB_DISABLE_SPD
mdefine_line|#define USBDEVFS_URB_DISABLE_SPD           1
DECL|macro|USBDEVFS_URB_ISO_ASAP
mdefine_line|#define USBDEVFS_URB_ISO_ASAP              2
DECL|macro|USBDEVFS_URB_QUEUE_BULK
mdefine_line|#define USBDEVFS_URB_QUEUE_BULK            0x10
DECL|macro|USBDEVFS_URB_TYPE_ISO
mdefine_line|#define USBDEVFS_URB_TYPE_ISO&t;&t;   0
DECL|macro|USBDEVFS_URB_TYPE_INTERRUPT
mdefine_line|#define USBDEVFS_URB_TYPE_INTERRUPT&t;   1
DECL|macro|USBDEVFS_URB_TYPE_CONTROL
mdefine_line|#define USBDEVFS_URB_TYPE_CONTROL&t;   2
DECL|macro|USBDEVFS_URB_TYPE_BULK
mdefine_line|#define USBDEVFS_URB_TYPE_BULK&t;&t;   3
DECL|struct|usbdevfs_iso_packet_desc
r_struct
id|usbdevfs_iso_packet_desc
(brace
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|actual_length
r_int
r_int
id|actual_length
suffix:semicolon
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|usbdevfs_urb
r_struct
id|usbdevfs_urb
(brace
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|endpoint
r_int
r_char
id|endpoint
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
DECL|member|buffer_length
r_int
id|buffer_length
suffix:semicolon
DECL|member|actual_length
r_int
id|actual_length
suffix:semicolon
DECL|member|start_frame
r_int
id|start_frame
suffix:semicolon
DECL|member|number_of_packets
r_int
id|number_of_packets
suffix:semicolon
DECL|member|error_count
r_int
id|error_count
suffix:semicolon
DECL|member|signr
r_int
r_int
id|signr
suffix:semicolon
multiline_comment|/* signal to be sent on error, -1 if none should be sent */
DECL|member|usercontext
r_void
op_star
id|usercontext
suffix:semicolon
DECL|member|iso_frame_desc
r_struct
id|usbdevfs_iso_packet_desc
id|iso_frame_desc
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ioctls for talking to drivers in the usbcore module: */
DECL|struct|usbdevfs_ioctl
r_struct
id|usbdevfs_ioctl
(brace
DECL|member|ifno
r_int
id|ifno
suffix:semicolon
multiline_comment|/* interface 0..N ; negative numbers reserved */
DECL|member|ioctl_code
r_int
id|ioctl_code
suffix:semicolon
multiline_comment|/* MUST encode size + direction of data so the&n;&t;&t;&t;&t; * macros in &lt;asm/ioctl.h&gt; give correct values */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* param buffer (in, or out) */
)brace
suffix:semicolon
multiline_comment|/* You can do most things with hubs just through control messages,&n; * except find out what device connects to what port. */
DECL|struct|usbdevfs_hub_portinfo
r_struct
id|usbdevfs_hub_portinfo
(brace
DECL|member|nports
r_char
id|nports
suffix:semicolon
multiline_comment|/* number of downstream ports in this hub */
DECL|member|port
r_char
id|port
(braket
l_int|127
)braket
suffix:semicolon
multiline_comment|/* e.g. port 3 connects to device 27 */
)brace
suffix:semicolon
DECL|macro|USBDEVFS_CONTROL
mdefine_line|#define USBDEVFS_CONTROL           _IOWR(&squot;U&squot;, 0, struct usbdevfs_ctrltransfer)
DECL|macro|USBDEVFS_BULK
mdefine_line|#define USBDEVFS_BULK              _IOWR(&squot;U&squot;, 2, struct usbdevfs_bulktransfer)
DECL|macro|USBDEVFS_RESETEP
mdefine_line|#define USBDEVFS_RESETEP           _IOR(&squot;U&squot;, 3, unsigned int)
DECL|macro|USBDEVFS_SETINTERFACE
mdefine_line|#define USBDEVFS_SETINTERFACE      _IOR(&squot;U&squot;, 4, struct usbdevfs_setinterface)
DECL|macro|USBDEVFS_SETCONFIGURATION
mdefine_line|#define USBDEVFS_SETCONFIGURATION  _IOR(&squot;U&squot;, 5, unsigned int)
DECL|macro|USBDEVFS_GETDRIVER
mdefine_line|#define USBDEVFS_GETDRIVER         _IOW(&squot;U&squot;, 8, struct usbdevfs_getdriver)
DECL|macro|USBDEVFS_SUBMITURB
mdefine_line|#define USBDEVFS_SUBMITURB         _IOR(&squot;U&squot;, 10, struct usbdevfs_urb)
DECL|macro|USBDEVFS_DISCARDURB
mdefine_line|#define USBDEVFS_DISCARDURB        _IO(&squot;U&squot;, 11)
DECL|macro|USBDEVFS_REAPURB
mdefine_line|#define USBDEVFS_REAPURB           _IOW(&squot;U&squot;, 12, void *)
DECL|macro|USBDEVFS_REAPURBNDELAY
mdefine_line|#define USBDEVFS_REAPURBNDELAY     _IOW(&squot;U&squot;, 13, void *)
DECL|macro|USBDEVFS_DISCSIGNAL
mdefine_line|#define USBDEVFS_DISCSIGNAL        _IOR(&squot;U&squot;, 14, struct usbdevfs_disconnectsignal)
DECL|macro|USBDEVFS_CLAIMINTERFACE
mdefine_line|#define USBDEVFS_CLAIMINTERFACE    _IOR(&squot;U&squot;, 15, unsigned int)
DECL|macro|USBDEVFS_RELEASEINTERFACE
mdefine_line|#define USBDEVFS_RELEASEINTERFACE  _IOR(&squot;U&squot;, 16, unsigned int)
DECL|macro|USBDEVFS_CONNECTINFO
mdefine_line|#define USBDEVFS_CONNECTINFO       _IOW(&squot;U&squot;, 17, struct usbdevfs_connectinfo)
DECL|macro|USBDEVFS_IOCTL
mdefine_line|#define USBDEVFS_IOCTL             _IOWR(&squot;U&squot;, 18, struct usbdevfs_ioctl)
DECL|macro|USBDEVFS_HUB_PORTINFO
mdefine_line|#define USBDEVFS_HUB_PORTINFO      _IOR(&squot;U&squot;, 19, struct usbdevfs_hub_portinfo)
DECL|macro|USBDEVFS_RESET
mdefine_line|#define USBDEVFS_RESET             _IO(&squot;U&squot;, 20)
DECL|macro|USBDEVFS_CLEAR_HALT
mdefine_line|#define USBDEVFS_CLEAR_HALT        _IOR(&squot;U&squot;, 21, unsigned int)
multiline_comment|/* --------------------------------------------------------------------- */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
DECL|struct|dev_state
r_struct
id|dev_state
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* state list */
DECL|member|devsem
r_struct
id|rw_semaphore
id|devsem
suffix:semicolon
multiline_comment|/* protects modifications to dev (dev == NULL indicating disconnect) */
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
DECL|member|file
r_struct
id|file
op_star
id|file
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
multiline_comment|/* protects the async urb lists */
DECL|member|async_pending
r_struct
id|list_head
id|async_pending
suffix:semicolon
DECL|member|async_completed
r_struct
id|list_head
id|async_completed
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
multiline_comment|/* wake up if a request completed */
DECL|member|discsignr
r_int
r_int
id|discsignr
suffix:semicolon
DECL|member|disctask
r_struct
id|task_struct
op_star
id|disctask
suffix:semicolon
DECL|member|disccontext
r_void
op_star
id|disccontext
suffix:semicolon
DECL|member|ifclaimed
r_int
r_int
id|ifclaimed
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* internal methods &amp; data */
r_extern
r_struct
id|usb_driver
id|usbdevfs_driver
suffix:semicolon
r_extern
r_struct
id|file_operations
id|usbdevfs_drivers_fops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|usbdevfs_devices_fops
suffix:semicolon
r_extern
r_struct
id|file_operations
id|usbdevfs_device_file_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|usbdevfs_device_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|usbdevfs_bus_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|usbdevfs_bus_file_operations
suffix:semicolon
r_extern
r_void
id|usbdevfs_conn_disc_event
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* --------------------------------------------------------------------- */
macro_line|#endif /* _LINUX_USBDEVICE_FS_H */
eof
