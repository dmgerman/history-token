multiline_comment|/* Driver for USB Mass Storage compliant devices&n; * Transport Functions Header File&n; *&n; * $Id: transport.h,v 1.15 2001/03/17 20:06:23 jrmayfield Exp $&n; *&n; * Current development and maintenance by:&n; *   (c) 1999, 2000 Matthew Dharm (mdharm-usb@one-eyed-alien.net)&n; *&n; * This driver is based on the &squot;USB Mass Storage Class&squot; document. This&n; * describes in detail the protocol used to communicate with such&n; * devices.  Clearly, the designers had SCSI and ATAPI commands in&n; * mind when they created this document.  The commands are all very&n; * similar to commands in the SCSI-II and ATAPI specifications.&n; *&n; * It is important to note that in a number of cases this class&n; * exhibits class-specific exemptions from the USB specification.&n; * Notably the usage of NAK, STALL and ACK differs from the norm, in&n; * that they are used to communicate wait, failed and OK on commands.&n; *&n; * Also, for certain devices, the interrupt endpoint is used to convey&n; * status of a command.&n; *&n; * Please see http://www.one-eyed-alien.net/~mdharm/linux-usb for more&n; * information about this driver.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _TRANSPORT_H_
DECL|macro|_TRANSPORT_H_
mdefine_line|#define _TRANSPORT_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;usb.h&quot;
macro_line|#include &quot;scsi.h&quot;
multiline_comment|/* Protocols */
DECL|macro|US_PR_CBI
mdefine_line|#define US_PR_CBI&t;0x00&t;&t;/* Control/Bulk/Interrupt */
DECL|macro|US_PR_CB
mdefine_line|#define US_PR_CB&t;0x01&t;&t;/* Control/Bulk w/o interrupt */
DECL|macro|US_PR_BULK
mdefine_line|#define US_PR_BULK&t;0x50&t;&t;/* bulk only */
macro_line|#ifdef CONFIG_USB_STORAGE_HP8200e
DECL|macro|US_PR_SCM_ATAPI
mdefine_line|#define US_PR_SCM_ATAPI&t;0x80&t;&t;/* SCM-ATAPI bridge */
macro_line|#endif
macro_line|#ifdef CONFIG_USB_STORAGE_SDDR09
DECL|macro|US_PR_EUSB_SDDR09
mdefine_line|#define US_PR_EUSB_SDDR09&t;0x81&t;/* SCM-SCSI bridge for&n;&t;&t;&t;&t;&t;&t;SDDR-09 */
macro_line|#endif
DECL|macro|US_PR_DPCM_USB
mdefine_line|#define US_PR_DPCM_USB  0xf0&t;&t;/* Combination CB/SDDR09 */
macro_line|#ifdef CONFIG_USB_STORAGE_FREECOM
DECL|macro|US_PR_FREECOM
mdefine_line|#define US_PR_FREECOM   0xf1            /* Freecom */
macro_line|#endif
macro_line|#ifdef CONFIG_USB_STORAGE_DATAFAB
DECL|macro|US_PR_DATAFAB
mdefine_line|#define US_PR_DATAFAB   0xf2            /* Datafab chipsets */
macro_line|#endif
macro_line|#ifdef CONFIG_USB_STORAGE_JUMPSHOT
DECL|macro|US_PR_JUMPSHOT
mdefine_line|#define US_PR_JUMPSHOT  0xf3            /* Lexar Jumpshot */
macro_line|#endif
multiline_comment|/*&n; * Bulk only data structures&n; */
multiline_comment|/* command block wrapper */
DECL|struct|bulk_cb_wrap
r_struct
id|bulk_cb_wrap
(brace
DECL|member|Signature
id|__u32
id|Signature
suffix:semicolon
multiline_comment|/* contains &squot;USBC&squot; */
DECL|member|Tag
id|__u32
id|Tag
suffix:semicolon
multiline_comment|/* unique per command id */
DECL|member|DataTransferLength
id|__u32
id|DataTransferLength
suffix:semicolon
multiline_comment|/* size of data */
DECL|member|Flags
id|__u8
id|Flags
suffix:semicolon
multiline_comment|/* direction in bit 0 */
DECL|member|Lun
id|__u8
id|Lun
suffix:semicolon
multiline_comment|/* LUN normally 0 */
DECL|member|Length
id|__u8
id|Length
suffix:semicolon
multiline_comment|/* of of the CDB */
DECL|member|CDB
id|__u8
id|CDB
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* max command */
)brace
suffix:semicolon
DECL|macro|US_BULK_CB_WRAP_LEN
mdefine_line|#define US_BULK_CB_WRAP_LEN&t;31
DECL|macro|US_BULK_CB_SIGN
mdefine_line|#define US_BULK_CB_SIGN&t;&t;0x43425355&t;/*spells out USBC */
DECL|macro|US_BULK_FLAG_IN
mdefine_line|#define US_BULK_FLAG_IN&t;&t;1
DECL|macro|US_BULK_FLAG_OUT
mdefine_line|#define US_BULK_FLAG_OUT&t;0
multiline_comment|/* command status wrapper */
DECL|struct|bulk_cs_wrap
r_struct
id|bulk_cs_wrap
(brace
DECL|member|Signature
id|__u32
id|Signature
suffix:semicolon
multiline_comment|/* should = &squot;USBS&squot; */
DECL|member|Tag
id|__u32
id|Tag
suffix:semicolon
multiline_comment|/* same as original command */
DECL|member|Residue
id|__u32
id|Residue
suffix:semicolon
multiline_comment|/* amount not transferred */
DECL|member|Status
id|__u8
id|Status
suffix:semicolon
multiline_comment|/* see below */
DECL|member|Filler
id|__u8
id|Filler
(braket
l_int|18
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|US_BULK_CS_WRAP_LEN
mdefine_line|#define US_BULK_CS_WRAP_LEN&t;13
DECL|macro|US_BULK_CS_SIGN
mdefine_line|#define US_BULK_CS_SIGN&t;&t;0x53425355&t;/* spells out &squot;USBS&squot; */
DECL|macro|US_BULK_STAT_OK
mdefine_line|#define US_BULK_STAT_OK&t;&t;0
DECL|macro|US_BULK_STAT_FAIL
mdefine_line|#define US_BULK_STAT_FAIL&t;1
DECL|macro|US_BULK_STAT_PHASE
mdefine_line|#define US_BULK_STAT_PHASE&t;2
multiline_comment|/* bulk-only class specific requests */
DECL|macro|US_BULK_RESET_REQUEST
mdefine_line|#define US_BULK_RESET_REQUEST&t;0xff
DECL|macro|US_BULK_GET_MAX_LUN
mdefine_line|#define US_BULK_GET_MAX_LUN&t;0xfe
multiline_comment|/*&n; * usb_stor_transfer() return codes&n; */
DECL|macro|US_BULK_TRANSFER_GOOD
mdefine_line|#define US_BULK_TRANSFER_GOOD&t;&t;0  /* good transfer                 */
DECL|macro|US_BULK_TRANSFER_SHORT
mdefine_line|#define US_BULK_TRANSFER_SHORT&t;&t;1  /* transfered less than expected */
DECL|macro|US_BULK_TRANSFER_FAILED
mdefine_line|#define US_BULK_TRANSFER_FAILED&t;&t;2  /* transfer died in the middle   */
DECL|macro|US_BULK_TRANSFER_ABORTED
mdefine_line|#define US_BULK_TRANSFER_ABORTED&t;3  /* transfer canceled             */
multiline_comment|/*&n; * Transport return codes&n; */
DECL|macro|USB_STOR_TRANSPORT_GOOD
mdefine_line|#define USB_STOR_TRANSPORT_GOOD&t;   0   /* Transport good, command good&t;   */
DECL|macro|USB_STOR_TRANSPORT_FAILED
mdefine_line|#define USB_STOR_TRANSPORT_FAILED  1   /* Transport good, command failed   */
DECL|macro|USB_STOR_TRANSPORT_ERROR
mdefine_line|#define USB_STOR_TRANSPORT_ERROR   2   /* Transport bad (i.e. device dead) */
DECL|macro|USB_STOR_TRANSPORT_ABORTED
mdefine_line|#define USB_STOR_TRANSPORT_ABORTED 3   /* Transport aborted                */
multiline_comment|/*&n; * CBI accept device specific command&n; */
DECL|macro|US_CBI_ADSC
mdefine_line|#define US_CBI_ADSC&t;&t;0
r_extern
r_void
id|usb_stor_CBI_irq
c_func
(paren
r_struct
id|urb
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_stor_CBI_transport
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_struct
id|us_data
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_stor_CB_transport
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_struct
id|us_data
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_stor_CB_reset
c_func
(paren
r_struct
id|us_data
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_stor_Bulk_transport
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_struct
id|us_data
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_stor_Bulk_max_lun
c_func
(paren
r_struct
id|us_data
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_stor_Bulk_reset
c_func
(paren
r_struct
id|us_data
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|usb_stor_transfer_length
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_void
id|usb_stor_invoke_transport
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_struct
id|us_data
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_stor_transfer_partial
c_func
(paren
r_struct
id|us_data
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|usb_stor_bulk_msg
c_func
(paren
r_struct
id|us_data
op_star
comma
r_void
op_star
comma
r_int
comma
r_int
r_int
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_stor_control_msg
c_func
(paren
r_struct
id|us_data
op_star
comma
r_int
r_int
comma
id|u8
comma
id|u8
comma
id|u16
comma
id|u16
comma
r_void
op_star
comma
id|u16
)paren
suffix:semicolon
r_extern
r_void
id|usb_stor_transfer
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_struct
id|us_data
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_stor_clear_halt
c_func
(paren
r_struct
id|usb_device
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
