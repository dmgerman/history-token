multiline_comment|/* Driver for USB Mass Storage compliant devices&n; * Main Header File&n; *&n; * $Id: usb.h,v 1.21 2002/04/21 02:57:59 mdharm Exp $&n; *&n; * Current development and maintenance by:&n; *   (c) 1999-2002 Matthew Dharm (mdharm-usb@one-eyed-alien.net)&n; *&n; * Initial work by:&n; *   (c) 1999 Michael Gee (michael@linuxspecific.com)&n; *&n; * This driver is based on the &squot;USB Mass Storage Class&squot; document. This&n; * describes in detail the protocol used to communicate with such&n; * devices.  Clearly, the designers had SCSI and ATAPI commands in&n; * mind when they created this document.  The commands are all very&n; * similar to commands in the SCSI-II and ATAPI specifications.&n; *&n; * It is important to note that in a number of cases this class&n; * exhibits class-specific exemptions from the USB specification.&n; * Notably the usage of NAK, STALL and ACK differs from the norm, in&n; * that they are used to communicate wait, failed and OK on commands.&n; *&n; * Also, for certain devices, the interrupt endpoint is used to convey&n; * status of a command.&n; *&n; * Please see http://www.one-eyed-alien.net/~mdharm/linux-usb for more&n; * information about this driver.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _USB_H_
DECL|macro|_USB_H_
mdefine_line|#define _USB_H_
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
multiline_comment|/* &n; * GUID definitions&n; */
DECL|macro|GUID
mdefine_line|#define GUID(x) __u32 x[3]
DECL|macro|GUID_EQUAL
mdefine_line|#define GUID_EQUAL(x, y) (x[0] == y[0] &amp;&amp; x[1] == y[1] &amp;&amp; x[2] == y[2])
DECL|macro|GUID_CLEAR
mdefine_line|#define GUID_CLEAR(x) x[0] = x[1] = x[2] = 0;
DECL|macro|GUID_NONE
mdefine_line|#define GUID_NONE(x) (!x[0] &amp;&amp; !x[1] &amp;&amp; !x[2])
DECL|macro|GUID_FORMAT
mdefine_line|#define GUID_FORMAT &quot;%08x%08x%08x&quot;
DECL|macro|GUID_ARGS
mdefine_line|#define GUID_ARGS(x) x[0], x[1], x[2]
DECL|function|make_guid
r_static
r_inline
r_void
id|make_guid
c_func
(paren
id|__u32
op_star
id|pg
comma
id|__u16
id|vendor
comma
id|__u16
id|product
comma
r_char
op_star
id|serial
)paren
(brace
id|pg
(braket
l_int|0
)braket
op_assign
(paren
id|vendor
op_lshift
l_int|16
)paren
op_or
id|product
suffix:semicolon
id|pg
(braket
l_int|1
)braket
op_assign
id|pg
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|serial
)paren
(brace
id|pg
(braket
l_int|1
)braket
op_lshift_assign
l_int|4
suffix:semicolon
id|pg
(braket
l_int|1
)braket
op_or_assign
id|pg
(braket
l_int|2
)braket
op_rshift
l_int|28
suffix:semicolon
id|pg
(braket
l_int|2
)braket
op_lshift_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
op_star
id|serial
op_ge
l_char|&squot;a&squot;
)paren
op_star
id|serial
op_sub_assign
l_char|&squot;a&squot;
op_minus
l_char|&squot;A&squot;
suffix:semicolon
id|pg
(braket
l_int|2
)braket
op_or_assign
(paren
op_star
id|serial
op_le
l_char|&squot;9&squot;
op_logical_and
op_star
id|serial
op_ge
l_char|&squot;0&squot;
)paren
ques
c_cond
op_star
id|serial
op_minus
l_char|&squot;0&squot;
suffix:colon
op_star
id|serial
op_minus
l_char|&squot;A&squot;
op_plus
l_int|10
suffix:semicolon
id|serial
op_increment
suffix:semicolon
)brace
)brace
r_struct
id|us_data
suffix:semicolon
multiline_comment|/*&n; * Unusual device list definitions &n; */
DECL|struct|us_unusual_dev
r_struct
id|us_unusual_dev
(brace
DECL|member|vendorName
r_const
r_char
op_star
id|vendorName
suffix:semicolon
DECL|member|productName
r_const
r_char
op_star
id|productName
suffix:semicolon
DECL|member|useProtocol
id|__u8
id|useProtocol
suffix:semicolon
DECL|member|useTransport
id|__u8
id|useTransport
suffix:semicolon
DECL|member|initFunction
r_int
(paren
op_star
id|initFunction
)paren
(paren
r_struct
id|us_data
op_star
)paren
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Flag definitions */
DECL|macro|US_FL_SINGLE_LUN
mdefine_line|#define US_FL_SINGLE_LUN      0x00000001 /* allow access to only LUN 0&t;    */
DECL|macro|US_FL_MODE_XLATE
mdefine_line|#define US_FL_MODE_XLATE      0x00000002 /* translate _6 to _10 commands for&n;&t;&t;&t;&t;&t;&t;    Win/MacOS compatibility */
DECL|macro|US_FL_START_STOP
mdefine_line|#define US_FL_START_STOP      0x00000004 /* ignore START_STOP commands&t;    */
DECL|macro|US_FL_IGNORE_SER
mdefine_line|#define US_FL_IGNORE_SER      0x00000010 /* Ignore the serial number given  */
DECL|macro|US_FL_SCM_MULT_TARG
mdefine_line|#define US_FL_SCM_MULT_TARG   0x00000020 /* supports multiple targets */
DECL|macro|US_FL_FIX_INQUIRY
mdefine_line|#define US_FL_FIX_INQUIRY     0x00000040 /* INQUIRY response needs fixing */
multiline_comment|/* kernel thread actions */
DECL|macro|US_ACT_COMMAND
mdefine_line|#define US_ACT_COMMAND&t;&t;1
DECL|macro|US_ACT_EXIT
mdefine_line|#define US_ACT_EXIT&t;&t;5
multiline_comment|/* processing state machine states */
DECL|macro|US_STATE_IDLE
mdefine_line|#define US_STATE_IDLE&t;&t;1
DECL|macro|US_STATE_RUNNING
mdefine_line|#define US_STATE_RUNNING&t;2
DECL|macro|US_STATE_RESETTING
mdefine_line|#define US_STATE_RESETTING&t;3
DECL|macro|US_STATE_ABORTING
mdefine_line|#define US_STATE_ABORTING&t;4
DECL|macro|USB_STOR_STRING_LEN
mdefine_line|#define USB_STOR_STRING_LEN 32
DECL|typedef|trans_cmnd
r_typedef
r_int
(paren
op_star
id|trans_cmnd
)paren
(paren
id|Scsi_Cmnd
op_star
comma
r_struct
id|us_data
op_star
)paren
suffix:semicolon
DECL|typedef|trans_reset
r_typedef
r_int
(paren
op_star
id|trans_reset
)paren
(paren
r_struct
id|us_data
op_star
)paren
suffix:semicolon
DECL|typedef|proto_cmnd
r_typedef
r_void
(paren
op_star
id|proto_cmnd
)paren
(paren
id|Scsi_Cmnd
op_star
comma
r_struct
id|us_data
op_star
)paren
suffix:semicolon
DECL|typedef|extra_data_destructor
r_typedef
r_void
(paren
op_star
id|extra_data_destructor
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* extra data destructor   */
multiline_comment|/* we allocate one of these for every device that we remember */
DECL|struct|us_data
r_struct
id|us_data
(brace
DECL|member|next
r_struct
id|us_data
op_star
id|next
suffix:semicolon
multiline_comment|/* next device */
multiline_comment|/* The device we&squot;re working with&n;&t; * It&squot;s important to note:&n;&t; *    (o) you must hold dev_semaphore to change pusb_dev&n;&t; *    (o) DEV_ATTACHED in bitflags should change whenever pusb_dev does&n;&t; */
DECL|member|dev_semaphore
r_struct
id|semaphore
id|dev_semaphore
suffix:semicolon
multiline_comment|/* protect pusb_dev */
DECL|member|pusb_dev
r_struct
id|usb_device
op_star
id|pusb_dev
suffix:semicolon
multiline_comment|/* this usb_device */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* from filter initially */
multiline_comment|/* information about the device -- always good */
DECL|member|vendor
r_char
id|vendor
(braket
id|USB_STOR_STRING_LEN
)braket
suffix:semicolon
DECL|member|product
r_char
id|product
(braket
id|USB_STOR_STRING_LEN
)braket
suffix:semicolon
DECL|member|serial
r_char
id|serial
(braket
id|USB_STOR_STRING_LEN
)braket
suffix:semicolon
DECL|member|transport_name
r_char
op_star
id|transport_name
suffix:semicolon
DECL|member|protocol_name
r_char
op_star
id|protocol_name
suffix:semicolon
DECL|member|subclass
id|u8
id|subclass
suffix:semicolon
DECL|member|protocol
id|u8
id|protocol
suffix:semicolon
DECL|member|max_lun
id|u8
id|max_lun
suffix:semicolon
multiline_comment|/* information about the device -- only good if device is attached */
DECL|member|ifnum
id|u8
id|ifnum
suffix:semicolon
multiline_comment|/* interface number   */
DECL|member|ep_in
id|u8
id|ep_in
suffix:semicolon
multiline_comment|/* bulk in endpoint   */
DECL|member|ep_out
id|u8
id|ep_out
suffix:semicolon
multiline_comment|/* bulk out endpoint  */
DECL|member|ep_int
r_struct
id|usb_endpoint_descriptor
op_star
id|ep_int
suffix:semicolon
multiline_comment|/* interrupt endpoint */
multiline_comment|/* function pointers for this device */
DECL|member|transport
id|trans_cmnd
id|transport
suffix:semicolon
multiline_comment|/* transport function&t;   */
DECL|member|transport_reset
id|trans_reset
id|transport_reset
suffix:semicolon
multiline_comment|/* transport device reset */
DECL|member|proto_handler
id|proto_cmnd
id|proto_handler
suffix:semicolon
multiline_comment|/* protocol handler&t;   */
multiline_comment|/* SCSI interfaces */
id|GUID
c_func
(paren
id|guid
)paren
suffix:semicolon
multiline_comment|/* unique dev id&t;*/
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
multiline_comment|/* our dummy host data */
DECL|member|htmplt
id|Scsi_Host_Template
id|htmplt
suffix:semicolon
multiline_comment|/* own host template&t;*/
DECL|member|host_number
r_int
id|host_number
suffix:semicolon
multiline_comment|/* to find us&t;&t;*/
DECL|member|host_no
r_int
id|host_no
suffix:semicolon
multiline_comment|/* allocated by scsi&t;*/
DECL|member|srb
id|Scsi_Cmnd
op_star
id|srb
suffix:semicolon
multiline_comment|/* current srb&t;&t;*/
multiline_comment|/* thread information */
DECL|member|queue_srb
id|Scsi_Cmnd
op_star
id|queue_srb
suffix:semicolon
multiline_comment|/* the single queue slot */
DECL|member|action
r_int
id|action
suffix:semicolon
multiline_comment|/* what to do&t;&t;  */
DECL|member|pid
r_int
id|pid
suffix:semicolon
multiline_comment|/* control thread&t;  */
DECL|member|sm_state
id|atomic_t
id|sm_state
suffix:semicolon
multiline_comment|/* interrupt info for CBI devices -- only good if attached */
DECL|member|ip_waitq
r_struct
id|semaphore
id|ip_waitq
suffix:semicolon
multiline_comment|/* for CBI interrupts&t; */
DECL|member|bitflags
r_int
r_int
id|bitflags
suffix:semicolon
multiline_comment|/* single-bit flags:&t; */
DECL|macro|IP_WANTED
mdefine_line|#define IP_WANTED&t;1&t;&t;&t; /* is an IRQ expected?&t; */
DECL|macro|DEV_ATTACHED
mdefine_line|#define DEV_ATTACHED&t;2&t;&t;&t; /* is the dev. attached?*/
multiline_comment|/* interrupt communications data */
DECL|member|irq_urb_sem
r_struct
id|semaphore
id|irq_urb_sem
suffix:semicolon
multiline_comment|/* to protect irq_urb&t; */
DECL|member|irq_urb
r_struct
id|urb
op_star
id|irq_urb
suffix:semicolon
multiline_comment|/* for USB int requests */
DECL|member|irqbuf
r_int
r_char
id|irqbuf
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* buffer for USB IRQ&t; */
DECL|member|irqdata
r_int
r_char
id|irqdata
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* data from USB IRQ&t; */
multiline_comment|/* control and bulk communications data */
DECL|member|current_urb_sem
r_struct
id|semaphore
id|current_urb_sem
suffix:semicolon
multiline_comment|/* to protect irq_urb&t; */
DECL|member|current_urb
r_struct
id|urb
op_star
id|current_urb
suffix:semicolon
multiline_comment|/* non-int USB requests */
DECL|member|dr
r_struct
id|usb_ctrlrequest
op_star
id|dr
suffix:semicolon
multiline_comment|/* control requests&t; */
multiline_comment|/* the semaphore for sleeping the control thread */
DECL|member|sema
r_struct
id|semaphore
id|sema
suffix:semicolon
multiline_comment|/* to sleep thread on   */
multiline_comment|/* mutual exclusion structures */
DECL|member|notify
r_struct
id|completion
id|notify
suffix:semicolon
multiline_comment|/* thread begin/end&t;    */
DECL|member|queue_exclusion
id|spinlock_t
id|queue_exclusion
suffix:semicolon
multiline_comment|/* to protect data structs */
DECL|member|unusual_dev
r_struct
id|us_unusual_dev
op_star
id|unusual_dev
suffix:semicolon
multiline_comment|/* If unusual device       */
DECL|member|extra
r_void
op_star
id|extra
suffix:semicolon
multiline_comment|/* Any extra data          */
DECL|member|extra_destructor
id|extra_data_destructor
id|extra_destructor
suffix:semicolon
multiline_comment|/* extra data destructor   */
)brace
suffix:semicolon
multiline_comment|/* The list of structures and the protective lock for them */
r_extern
r_struct
id|us_data
op_star
id|us_list
suffix:semicolon
r_extern
r_struct
id|semaphore
id|us_list_semaphore
suffix:semicolon
multiline_comment|/* The structure which defines our driver */
r_extern
r_struct
id|usb_driver
id|usb_storage_driver
suffix:semicolon
multiline_comment|/* Function to fill an inquiry response. See usb.c for details */
r_extern
r_void
id|fill_inquiry_response
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_int
r_char
op_star
id|data
comma
r_int
r_int
id|data_len
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,3)
DECL|macro|scsi_unlock
mdefine_line|#define scsi_unlock(host)&t;spin_unlock_irq(host-&gt;host_lock)
DECL|macro|scsi_lock
mdefine_line|#define scsi_lock(host)&t;&t;spin_lock_irq(host-&gt;host_lock)
DECL|macro|sg_address
mdefine_line|#define sg_address(psg)&t;&t;(page_address((psg)-&gt;page) + (psg)-&gt;offset)
macro_line|#else
DECL|macro|scsi_unlock
mdefine_line|#define scsi_unlock(host)&t;spin_unlock_irq(&amp;io_request_lock)
DECL|macro|scsi_lock
mdefine_line|#define scsi_lock(host)&t;&t;spin_lock_irq(&amp;io_request_lock)
DECL|macro|sg_address
mdefine_line|#define sg_address(psg)&t;&t;((psg)-&gt;address)
macro_line|#endif
macro_line|#endif
eof
