multiline_comment|/* Driver for USB Mass Storage compliant devices&n; * Main Header File&n; *&n; * $Id: usb.h,v 1.21 2002/04/21 02:57:59 mdharm Exp $&n; *&n; * Current development and maintenance by:&n; *   (c) 1999-2002 Matthew Dharm (mdharm-usb@one-eyed-alien.net)&n; *&n; * Initial work by:&n; *   (c) 1999 Michael Gee (michael@linuxspecific.com)&n; *&n; * This driver is based on the &squot;USB Mass Storage Class&squot; document. This&n; * describes in detail the protocol used to communicate with such&n; * devices.  Clearly, the designers had SCSI and ATAPI commands in&n; * mind when they created this document.  The commands are all very&n; * similar to commands in the SCSI-II and ATAPI specifications.&n; *&n; * It is important to note that in a number of cases this class&n; * exhibits class-specific exemptions from the USB specification.&n; * Notably the usage of NAK, STALL and ACK differs from the norm, in&n; * that they are used to communicate wait, failed and OK on commands.&n; *&n; * Also, for certain devices, the interrupt endpoint is used to convey&n; * status of a command.&n; *&n; * Please see http://www.one-eyed-alien.net/~mdharm/linux-usb for more&n; * information about this driver.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _USB_H_
DECL|macro|_USB_H_
mdefine_line|#define _USB_H_
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
r_struct
id|us_data
suffix:semicolon
r_struct
id|scsi_cmnd
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
multiline_comment|/* Flag definitions: these entries are static */
DECL|macro|US_FL_SINGLE_LUN
mdefine_line|#define US_FL_SINGLE_LUN      0x00000001 /* allow access to only LUN 0&t;    */
DECL|macro|US_FL_MODE_XLATE
mdefine_line|#define US_FL_MODE_XLATE      0          /* [no longer used]                */
DECL|macro|US_FL_NEED_OVERRIDE
mdefine_line|#define US_FL_NEED_OVERRIDE   0x00000004 /* unusual_devs entry is necessary */
DECL|macro|US_FL_IGNORE_SER
mdefine_line|#define US_FL_IGNORE_SER      0&t;&t; /* [no longer used]&t;&t;    */
DECL|macro|US_FL_SCM_MULT_TARG
mdefine_line|#define US_FL_SCM_MULT_TARG   0x00000020 /* supports multiple targets&t;    */
DECL|macro|US_FL_FIX_INQUIRY
mdefine_line|#define US_FL_FIX_INQUIRY     0x00000040 /* INQUIRY response needs faking   */
DECL|macro|US_FL_FIX_CAPACITY
mdefine_line|#define US_FL_FIX_CAPACITY    0x00000080 /* READ CAPACITY response too big  */
DECL|macro|US_FL_IGNORE_RESIDUE
mdefine_line|#define US_FL_IGNORE_RESIDUE  0x00000100 /* reported residue is wrong&t;    */
multiline_comment|/* Dynamic flag definitions: used in set_bit() etc. */
DECL|macro|US_FLIDX_URB_ACTIVE
mdefine_line|#define US_FLIDX_URB_ACTIVE&t;18  /* 0x00040000  current_urb is in use  */
DECL|macro|US_FLIDX_SG_ACTIVE
mdefine_line|#define US_FLIDX_SG_ACTIVE&t;19  /* 0x00080000  current_sg is in use   */
DECL|macro|US_FLIDX_ABORTING
mdefine_line|#define US_FLIDX_ABORTING&t;20  /* 0x00100000  abort is in progress   */
DECL|macro|US_FLIDX_DISCONNECTING
mdefine_line|#define US_FLIDX_DISCONNECTING&t;21  /* 0x00200000  disconnect in progress */
DECL|macro|ABORTING_OR_DISCONNECTING
mdefine_line|#define ABORTING_OR_DISCONNECTING&t;((1UL &lt;&lt; US_FLIDX_ABORTING) | &bslash;&n;&t;&t;&t;&t;&t; (1UL &lt;&lt; US_FLIDX_DISCONNECTING))
DECL|macro|US_FLIDX_RESETTING
mdefine_line|#define US_FLIDX_RESETTING&t;22  /* 0x00400000  device reset in progress */
DECL|macro|US_FLIDX_TIMED_OUT
mdefine_line|#define US_FLIDX_TIMED_OUT&t;23  /* 0x00800000  SCSI midlayer timed out  */
DECL|macro|USB_STOR_STRING_LEN
mdefine_line|#define USB_STOR_STRING_LEN 32
multiline_comment|/*&n; * We provide a DMA-mapped I/O buffer for use with small USB transfers.&n; * It turns out that CB[I] needs a 12-byte buffer and Bulk-only needs a&n; * 31-byte buffer.  But Freecom needs a 64-byte buffer, so that&squot;s the&n; * size we&squot;ll allocate.&n; */
DECL|macro|US_IOBUF_SIZE
mdefine_line|#define US_IOBUF_SIZE&t;&t;64&t;/* Size of the DMA-mapped I/O buffer */
DECL|typedef|trans_cmnd
r_typedef
r_int
(paren
op_star
id|trans_cmnd
)paren
(paren
r_struct
id|scsi_cmnd
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
r_struct
id|scsi_cmnd
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
multiline_comment|/* The device we&squot;re working with&n;&t; * It&squot;s important to note:&n;&t; *    (o) you must hold dev_semaphore to change pusb_dev&n;&t; */
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
DECL|member|pusb_intf
r_struct
id|usb_interface
op_star
id|pusb_intf
suffix:semicolon
multiline_comment|/* this interface */
DECL|member|unusual_dev
r_struct
id|us_unusual_dev
op_star
id|unusual_dev
suffix:semicolon
multiline_comment|/* device-filter entry     */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* from filter initially */
DECL|member|send_bulk_pipe
r_int
r_int
id|send_bulk_pipe
suffix:semicolon
multiline_comment|/* cached pipe values */
DECL|member|recv_bulk_pipe
r_int
r_int
id|recv_bulk_pipe
suffix:semicolon
DECL|member|send_ctrl_pipe
r_int
r_int
id|send_ctrl_pipe
suffix:semicolon
DECL|member|recv_ctrl_pipe
r_int
r_int
id|recv_ctrl_pipe
suffix:semicolon
DECL|member|recv_intr_pipe
r_int
r_int
id|recv_intr_pipe
suffix:semicolon
multiline_comment|/* information about the device */
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
DECL|member|ifnum
id|u8
id|ifnum
suffix:semicolon
multiline_comment|/* interface number   */
DECL|member|ep_bInterval
id|u8
id|ep_bInterval
suffix:semicolon
multiline_comment|/* interrupt interval */
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
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
multiline_comment|/* our dummy host data */
DECL|member|srb
r_struct
id|scsi_cmnd
op_star
id|srb
suffix:semicolon
multiline_comment|/* current srb&t;&t;*/
multiline_comment|/* thread information */
DECL|member|pid
r_int
id|pid
suffix:semicolon
multiline_comment|/* control thread&t; */
multiline_comment|/* control and bulk communications data */
DECL|member|current_urb
r_struct
id|urb
op_star
id|current_urb
suffix:semicolon
multiline_comment|/* USB requests&t; */
DECL|member|cr
r_struct
id|usb_ctrlrequest
op_star
id|cr
suffix:semicolon
multiline_comment|/* control requests&t; */
DECL|member|current_sg
r_struct
id|usb_sg_request
id|current_sg
suffix:semicolon
multiline_comment|/* scatter-gather req.  */
DECL|member|iobuf
r_int
r_char
op_star
id|iobuf
suffix:semicolon
multiline_comment|/* I/O buffer&t;&t; */
DECL|member|cr_dma
id|dma_addr_t
id|cr_dma
suffix:semicolon
multiline_comment|/* buffer DMA addresses */
DECL|member|iobuf_dma
id|dma_addr_t
id|iobuf_dma
suffix:semicolon
multiline_comment|/* mutual exclusion and synchronization structures */
DECL|member|sema
r_struct
id|semaphore
id|sema
suffix:semicolon
multiline_comment|/* to sleep thread on   */
DECL|member|notify
r_struct
id|completion
id|notify
suffix:semicolon
multiline_comment|/* thread begin/end&t; */
DECL|member|dev_reset_wait
id|wait_queue_head_t
id|dev_reset_wait
suffix:semicolon
multiline_comment|/* wait during reset    */
DECL|member|scsi_scan_wait
id|wait_queue_head_t
id|scsi_scan_wait
suffix:semicolon
multiline_comment|/* wait before scanning */
DECL|member|scsi_scan_done
r_struct
id|completion
id|scsi_scan_done
suffix:semicolon
multiline_comment|/* scan thread end&t; */
multiline_comment|/* subdriver information */
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
multiline_comment|/* The scsi_lock() and scsi_unlock() macros protect the sm_state and the&n; * single queue element srb for write access */
DECL|macro|scsi_unlock
mdefine_line|#define scsi_unlock(host)&t;spin_unlock_irq(host-&gt;host_lock)
DECL|macro|scsi_lock
mdefine_line|#define scsi_lock(host)&t;&t;spin_lock_irq(host-&gt;host_lock)
multiline_comment|/* Vendor ID list for devices that require special handling */
DECL|macro|USB_VENDOR_ID_GENESYS
mdefine_line|#define USB_VENDOR_ID_GENESYS&t;&t;0x05e3&t;/* Genesys Logic */
macro_line|#endif
eof
