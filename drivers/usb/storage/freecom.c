multiline_comment|/* Driver for Freecom USB/IDE adaptor&n; *&n; * $Id: freecom.c,v 1.19 2001/11/11 05:42:34 mdharm Exp $&n; *&n; * Freecom v0.1:&n; *&n; * First release&n; *&n; * Current development and maintenance by:&n; *   (C) 2000 David Brown &lt;usb-storage@davidb.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * This driver was developed with information provided in FREECOM&squot;s USB&n; * Programmers Reference Guide.  For further information contact Freecom&n; * (http://www.freecom.de/)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;protocol.h&quot;
macro_line|#include &quot;usb.h&quot;
macro_line|#include &quot;debug.h&quot;
macro_line|#include &quot;freecom.h&quot;
macro_line|#include &quot;linux/hdreg.h&quot;
macro_line|#ifdef CONFIG_USB_STORAGE_DEBUG
r_static
r_void
id|pdump
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
DECL|struct|freecom_udata
r_struct
id|freecom_udata
(brace
DECL|member|buffer
id|__u8
id|buffer
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Common command block. */
)brace
suffix:semicolon
DECL|typedef|freecom_udata_t
r_typedef
r_struct
id|freecom_udata
op_star
id|freecom_udata_t
suffix:semicolon
multiline_comment|/* All of the outgoing packets are 64 bytes long. */
DECL|struct|freecom_cb_wrap
r_struct
id|freecom_cb_wrap
(brace
DECL|member|Type
id|__u8
id|Type
suffix:semicolon
multiline_comment|/* Command type. */
DECL|member|Timeout
id|__u8
id|Timeout
suffix:semicolon
multiline_comment|/* Timeout in seconds. */
DECL|member|Atapi
id|__u8
id|Atapi
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* An ATAPI packet. */
DECL|member|Filler
id|__u8
id|Filler
(braket
l_int|50
)braket
suffix:semicolon
multiline_comment|/* Padding Data. */
)brace
suffix:semicolon
DECL|struct|freecom_xfer_wrap
r_struct
id|freecom_xfer_wrap
(brace
DECL|member|Type
id|__u8
id|Type
suffix:semicolon
multiline_comment|/* Command type. */
DECL|member|Timeout
id|__u8
id|Timeout
suffix:semicolon
multiline_comment|/* Timeout in seconds. */
DECL|member|Count
id|__u32
id|Count
suffix:semicolon
multiline_comment|/* Number of bytes to transfer. */
DECL|member|Pad
id|__u8
id|Pad
(braket
l_int|58
)braket
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|struct|freecom_ide_out
r_struct
id|freecom_ide_out
(brace
DECL|member|Type
id|__u8
id|Type
suffix:semicolon
multiline_comment|/* Type + IDE register. */
DECL|member|Pad
id|__u8
id|Pad
suffix:semicolon
DECL|member|Value
id|__u16
id|Value
suffix:semicolon
multiline_comment|/* Value to write. */
DECL|member|Pad2
id|__u8
id|Pad2
(braket
l_int|60
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|freecom_ide_in
r_struct
id|freecom_ide_in
(brace
DECL|member|Type
id|__u8
id|Type
suffix:semicolon
multiline_comment|/* Type | IDE register. */
DECL|member|Pad
id|__u8
id|Pad
(braket
l_int|63
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|freecom_status
r_struct
id|freecom_status
(brace
DECL|member|Status
id|__u8
id|Status
suffix:semicolon
DECL|member|Reason
id|__u8
id|Reason
suffix:semicolon
DECL|member|Count
id|__u16
id|Count
suffix:semicolon
DECL|member|Pad
id|__u8
id|Pad
(braket
l_int|60
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Freecom stuffs the interrupt status in the INDEX_STAT bit of the ide&n; * register. */
DECL|macro|FCM_INT_STATUS
mdefine_line|#define FCM_INT_STATUS&t;&t;0x02 /* INDEX_STAT */
DECL|macro|FCM_STATUS_BUSY
mdefine_line|#define FCM_STATUS_BUSY&t;&t;0x80
multiline_comment|/* These are the packet types.  The low bit indicates that this command&n; * should wait for an interrupt. */
DECL|macro|FCM_PACKET_ATAPI
mdefine_line|#define FCM_PACKET_ATAPI&t;0x21
DECL|macro|FCM_PACKET_STATUS
mdefine_line|#define FCM_PACKET_STATUS&t;0x20
multiline_comment|/* Receive data from the IDE interface.  The ATAPI packet has already&n; * waited, so the data should be immediately available. */
DECL|macro|FCM_PACKET_INPUT
mdefine_line|#define FCM_PACKET_INPUT&t;0x81
multiline_comment|/* Send data to the IDE interface. */
DECL|macro|FCM_PACKET_OUTPUT
mdefine_line|#define FCM_PACKET_OUTPUT&t;0x01
multiline_comment|/* Write a value to an ide register.  Or the ide register to write after&n; * munging the address a bit. */
DECL|macro|FCM_PACKET_IDE_WRITE
mdefine_line|#define FCM_PACKET_IDE_WRITE&t;0x40
DECL|macro|FCM_PACKET_IDE_READ
mdefine_line|#define FCM_PACKET_IDE_READ&t;0xC0
multiline_comment|/* All packets (except for status) are 64 bytes long. */
DECL|macro|FCM_PACKET_LENGTH
mdefine_line|#define FCM_PACKET_LENGTH&t;64
multiline_comment|/*&n; * Transfer an entire SCSI command&squot;s worth of data payload over the bulk&n; * pipe.&n; *&n; * Note that this uses usb_stor_transfer_partial to achieve it&squot;s goals -- this&n; * function simply determines if we&squot;re going to use scatter-gather or not,&n; * and acts appropriately.  For now, it also re-interprets the error codes.&n; */
DECL|function|us_transfer_freecom
r_static
r_void
id|us_transfer_freecom
c_func
(paren
id|Scsi_Cmnd
op_star
id|srb
comma
r_struct
id|us_data
op_star
id|us
comma
r_int
id|transfer_amount
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sg
suffix:semicolon
r_int
r_int
id|total_transferred
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* was someone foolish enough to request more data than available&n;&t; * buffer space? */
r_if
c_cond
(paren
id|transfer_amount
OG
id|srb-&gt;request_bufflen
)paren
id|transfer_amount
op_assign
id|srb-&gt;request_bufflen
suffix:semicolon
multiline_comment|/* are we scatter-gathering? */
r_if
c_cond
(paren
id|srb-&gt;use_sg
)paren
(brace
multiline_comment|/* loop over all the scatter gather structures and &n;&t;&t; * make the appropriate requests for each, until done&n;&t;&t; */
id|sg
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|srb-&gt;request_buffer
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
id|srb-&gt;use_sg
suffix:semicolon
id|i
op_increment
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;transfer_amount: %d and total_transferred: %d&bslash;n&quot;
comma
id|transfer_amount
comma
id|total_transferred
)paren
suffix:semicolon
multiline_comment|/* End this if we&squot;re done */
r_if
c_cond
(paren
id|transfer_amount
op_eq
id|total_transferred
)paren
r_break
suffix:semicolon
multiline_comment|/* transfer the lesser of the next buffer or the&n;&t;&t;&t; * remaining data */
r_if
c_cond
(paren
id|transfer_amount
op_minus
id|total_transferred
op_ge
id|sg
(braket
id|i
)braket
dot
id|length
)paren
(brace
id|result
op_assign
id|usb_stor_transfer_partial
c_func
(paren
id|us
comma
id|sg
(braket
id|i
)braket
dot
id|address
comma
id|sg
(braket
id|i
)braket
dot
id|length
)paren
suffix:semicolon
id|total_transferred
op_add_assign
id|sg
(braket
id|i
)braket
dot
id|length
suffix:semicolon
)brace
r_else
(brace
id|result
op_assign
id|usb_stor_transfer_partial
c_func
(paren
id|us
comma
id|sg
(braket
id|i
)braket
dot
id|address
comma
id|transfer_amount
op_minus
id|total_transferred
)paren
suffix:semicolon
id|total_transferred
op_add_assign
id|transfer_amount
op_minus
id|total_transferred
suffix:semicolon
)brace
multiline_comment|/* if we get an error, end the loop here */
r_if
c_cond
(paren
id|result
)paren
r_break
suffix:semicolon
)brace
)brace
r_else
multiline_comment|/* no scatter-gather, just make the request */
id|result
op_assign
id|usb_stor_transfer_partial
c_func
(paren
id|us
comma
id|srb-&gt;request_buffer
comma
id|transfer_amount
)paren
suffix:semicolon
multiline_comment|/* return the result in the data structure itself */
id|srb-&gt;result
op_assign
id|result
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/* Write a value to an ide register. */
r_static
r_int
id|freecom_ide_write
(paren
r_struct
id|us_data
op_star
id|us
comma
r_int
id|reg
comma
r_int
id|value
)paren
(brace
id|freecom_udata_t
id|extra
op_assign
(paren
id|freecom_udata_t
)paren
id|us-&gt;extra
suffix:semicolon
r_struct
id|freecom_ide_out
op_star
id|ideout
op_assign
(paren
r_struct
id|freecom_ide_out
op_star
)paren
id|extra-&gt;buffer
suffix:semicolon
r_int
id|opipe
suffix:semicolon
r_int
id|result
comma
id|partial
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;IDE out 0x%02x &lt;- 0x%02x&bslash;n&quot;
comma
id|reg
comma
id|value
)paren
suffix:semicolon
multiline_comment|/* Get handles for both transports. */
id|opipe
op_assign
id|usb_sndbulkpipe
(paren
id|us-&gt;pusb_dev
comma
id|us-&gt;ep_out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
template_param
l_int|8
)paren
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
r_if
c_cond
(paren
id|reg
OL
l_int|8
)paren
id|reg
op_or_assign
l_int|0x20
suffix:semicolon
r_else
id|reg
op_assign
l_int|0x0e
suffix:semicolon
id|ideout-&gt;Type
op_assign
id|FCM_PACKET_IDE_WRITE
op_or
id|reg
suffix:semicolon
id|ideout-&gt;Pad
op_assign
l_int|0
suffix:semicolon
id|ideout-&gt;Value
op_assign
id|cpu_to_le16
(paren
id|value
)paren
suffix:semicolon
id|memset
(paren
id|ideout-&gt;Pad2
comma
l_int|0
comma
r_sizeof
(paren
id|ideout-&gt;Pad2
)paren
)paren
suffix:semicolon
id|result
op_assign
id|usb_stor_bulk_msg
(paren
id|us
comma
id|ideout
comma
id|opipe
comma
id|FCM_PACKET_LENGTH
comma
op_amp
id|partial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ENOENT
)paren
r_return
id|US_BULK_TRANSFER_ABORTED
suffix:semicolon
r_else
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
r_return
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if 0 /* Unused at this time */
multiline_comment|/* Read a value from an ide register. */
r_static
r_int
id|freecom_ide_read
(paren
r_struct
id|us_data
op_star
id|us
comma
r_int
id|reg
comma
r_int
op_star
id|value
)paren
(brace
id|freecom_udata_t
id|extra
op_assign
(paren
id|freecom_udata_t
)paren
id|us-&gt;extra
suffix:semicolon
r_struct
id|freecom_ide_in
op_star
id|idein
op_assign
(paren
r_struct
id|freecom_ide_in
op_star
)paren
id|extra-&gt;buffer
suffix:semicolon
id|__u8
op_star
id|buffer
op_assign
id|extra-&gt;buffer
suffix:semicolon
r_int
id|ipipe
comma
id|opipe
suffix:semicolon
r_int
id|result
comma
id|partial
suffix:semicolon
r_int
id|desired_length
suffix:semicolon
multiline_comment|/* Get handles for both transports. */
id|opipe
op_assign
id|usb_sndbulkpipe
(paren
id|us-&gt;pusb_dev
comma
id|us-&gt;ep_out
)paren
suffix:semicolon
id|ipipe
op_assign
id|usb_rcvbulkpipe
(paren
id|us-&gt;pusb_dev
comma
id|us-&gt;ep_in
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
template_param
l_int|8
)paren
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
r_if
c_cond
(paren
id|reg
OL
l_int|8
)paren
id|reg
op_or_assign
l_int|0x10
suffix:semicolon
r_else
id|reg
op_assign
l_int|0x0e
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;IDE in request for register 0x%02x&bslash;n&quot;
comma
id|reg
)paren
suffix:semicolon
id|idein-&gt;Type
op_assign
id|FCM_PACKET_IDE_READ
op_or
id|reg
suffix:semicolon
id|memset
(paren
id|idein-&gt;Pad
comma
l_int|0
comma
r_sizeof
(paren
id|idein-&gt;Pad
)paren
)paren
suffix:semicolon
id|result
op_assign
id|usb_stor_bulk_msg
(paren
id|us
comma
id|idein
comma
id|opipe
comma
id|FCM_PACKET_LENGTH
comma
op_amp
id|partial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ENOENT
)paren
r_return
id|US_BULK_TRANSFER_ABORTED
suffix:semicolon
r_else
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
id|desired_length
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_eq
l_int|0x10
)paren
id|desired_length
op_assign
l_int|2
suffix:semicolon
id|result
op_assign
id|usb_stor_bulk_msg
(paren
id|us
comma
id|buffer
comma
id|ipipe
comma
id|desired_length
comma
op_amp
id|partial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ENOENT
)paren
r_return
id|US_BULK_TRANSFER_ABORTED
suffix:semicolon
r_else
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;IDE in partial is %d&bslash;n&quot;
comma
id|partial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|desired_length
op_eq
l_int|1
)paren
op_star
id|value
op_assign
id|buffer
(braket
l_int|0
)braket
suffix:semicolon
r_else
op_star
id|value
op_assign
id|le16_to_cpu
(paren
op_star
(paren
id|__u16
op_star
)paren
id|buffer
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;IDE in 0x%02x -&gt; 0x%02x&bslash;n&quot;
comma
id|reg
comma
op_star
id|value
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
)brace
macro_line|#endif
r_static
r_int
DECL|function|freecom_readdata
id|freecom_readdata
(paren
id|Scsi_Cmnd
op_star
id|srb
comma
r_struct
id|us_data
op_star
id|us
comma
r_int
id|ipipe
comma
r_int
id|opipe
comma
r_int
id|count
)paren
(brace
id|freecom_udata_t
id|extra
op_assign
(paren
id|freecom_udata_t
)paren
id|us-&gt;extra
suffix:semicolon
r_struct
id|freecom_xfer_wrap
op_star
id|fxfr
op_assign
(paren
r_struct
id|freecom_xfer_wrap
op_star
)paren
id|extra-&gt;buffer
suffix:semicolon
r_int
id|result
comma
id|partial
suffix:semicolon
id|fxfr-&gt;Type
op_assign
id|FCM_PACKET_INPUT
op_or
l_int|0x00
suffix:semicolon
id|fxfr-&gt;Timeout
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Short timeout for debugging. */
id|fxfr-&gt;Count
op_assign
id|cpu_to_le32
(paren
id|count
)paren
suffix:semicolon
id|memset
(paren
id|fxfr-&gt;Pad
comma
l_int|0
comma
r_sizeof
(paren
id|fxfr-&gt;Pad
)paren
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;Read data Freecom! (c=%d)&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
multiline_comment|/* Issue the transfer command. */
id|result
op_assign
id|usb_stor_bulk_msg
(paren
id|us
comma
id|fxfr
comma
id|opipe
comma
id|FCM_PACKET_LENGTH
comma
op_amp
id|partial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
l_int|0
)paren
(brace
id|US_DEBUGP
(paren
l_string|&quot;Freecom readdata xpot failure: r=%d, p=%d&bslash;n&quot;
comma
id|result
comma
id|partial
)paren
suffix:semicolon
multiline_comment|/* -ENOENT -- we canceled this transfer */
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ENOENT
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;freecom_readdata(): transfer aborted&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|US_BULK_TRANSFER_ABORTED
suffix:semicolon
)brace
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;Done issuing read request: %d %d&bslash;n&quot;
comma
id|result
comma
id|partial
)paren
suffix:semicolon
multiline_comment|/* Now transfer all of our blocks. */
id|US_DEBUGP
c_func
(paren
l_string|&quot;Start of read&bslash;n&quot;
)paren
suffix:semicolon
id|us_transfer_freecom
c_func
(paren
id|srb
comma
id|us
comma
id|count
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;freecom_readdata done!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
)brace
r_static
r_int
DECL|function|freecom_writedata
id|freecom_writedata
(paren
id|Scsi_Cmnd
op_star
id|srb
comma
r_struct
id|us_data
op_star
id|us
comma
r_int
id|ipipe
comma
r_int
id|opipe
comma
r_int
id|count
)paren
(brace
id|freecom_udata_t
id|extra
op_assign
(paren
id|freecom_udata_t
)paren
id|us-&gt;extra
suffix:semicolon
r_struct
id|freecom_xfer_wrap
op_star
id|fxfr
op_assign
(paren
r_struct
id|freecom_xfer_wrap
op_star
)paren
id|extra-&gt;buffer
suffix:semicolon
r_int
id|result
comma
id|partial
suffix:semicolon
id|fxfr-&gt;Type
op_assign
id|FCM_PACKET_OUTPUT
op_or
l_int|0x00
suffix:semicolon
id|fxfr-&gt;Timeout
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Short timeout for debugging. */
id|fxfr-&gt;Count
op_assign
id|cpu_to_le32
(paren
id|count
)paren
suffix:semicolon
id|memset
(paren
id|fxfr-&gt;Pad
comma
l_int|0
comma
r_sizeof
(paren
id|fxfr-&gt;Pad
)paren
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;Write data Freecom! (c=%d)&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
multiline_comment|/* Issue the transfer command. */
id|result
op_assign
id|usb_stor_bulk_msg
(paren
id|us
comma
id|fxfr
comma
id|opipe
comma
id|FCM_PACKET_LENGTH
comma
op_amp
id|partial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
l_int|0
)paren
(brace
id|US_DEBUGP
(paren
l_string|&quot;Freecom writedata xpot failure: r=%d, p=%d&bslash;n&quot;
comma
id|result
comma
id|partial
)paren
suffix:semicolon
multiline_comment|/* -ENOENT -- we canceled this transfer */
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ENOENT
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;freecom_writedata(): transfer aborted&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|US_BULK_TRANSFER_ABORTED
suffix:semicolon
)brace
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;Done issuing write request: %d %d&bslash;n&quot;
comma
id|result
comma
id|partial
)paren
suffix:semicolon
multiline_comment|/* Now transfer all of our blocks. */
id|US_DEBUGP
c_func
(paren
l_string|&quot;Start of write&bslash;n&quot;
)paren
suffix:semicolon
id|us_transfer_freecom
c_func
(paren
id|srb
comma
id|us
comma
id|count
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;freecom_writedata done!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
)brace
multiline_comment|/*&n; * Transport for the Freecom USB/IDE adaptor.&n; *&n; */
DECL|function|freecom_transport
r_int
id|freecom_transport
c_func
(paren
id|Scsi_Cmnd
op_star
id|srb
comma
r_struct
id|us_data
op_star
id|us
)paren
(brace
r_struct
id|freecom_cb_wrap
op_star
id|fcb
suffix:semicolon
r_struct
id|freecom_status
op_star
id|fst
suffix:semicolon
r_int
id|ipipe
comma
id|opipe
suffix:semicolon
multiline_comment|/* We need both pipes. */
r_int
id|result
suffix:semicolon
r_int
id|partial
suffix:semicolon
r_int
id|length
suffix:semicolon
id|freecom_udata_t
id|extra
suffix:semicolon
id|extra
op_assign
(paren
id|freecom_udata_t
)paren
id|us-&gt;extra
suffix:semicolon
id|fcb
op_assign
(paren
r_struct
id|freecom_cb_wrap
op_star
)paren
id|extra-&gt;buffer
suffix:semicolon
id|fst
op_assign
(paren
r_struct
id|freecom_status
op_star
)paren
id|extra-&gt;buffer
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;Freecom TRANSPORT STARTED&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Get handles for both transports. */
id|opipe
op_assign
id|usb_sndbulkpipe
(paren
id|us-&gt;pusb_dev
comma
id|us-&gt;ep_out
)paren
suffix:semicolon
id|ipipe
op_assign
id|usb_rcvbulkpipe
(paren
id|us-&gt;pusb_dev
comma
id|us-&gt;ep_in
)paren
suffix:semicolon
multiline_comment|/* The ATAPI Command always goes out first. */
id|fcb-&gt;Type
op_assign
id|FCM_PACKET_ATAPI
op_or
l_int|0x00
suffix:semicolon
id|fcb-&gt;Timeout
op_assign
l_int|0
suffix:semicolon
id|memcpy
(paren
id|fcb-&gt;Atapi
comma
id|srb-&gt;cmnd
comma
l_int|12
)paren
suffix:semicolon
id|memset
(paren
id|fcb-&gt;Filler
comma
l_int|0
comma
r_sizeof
(paren
id|fcb-&gt;Filler
)paren
)paren
suffix:semicolon
id|US_DEBUG
c_func
(paren
id|pdump
(paren
id|srb-&gt;cmnd
comma
l_int|12
)paren
)paren
suffix:semicolon
multiline_comment|/* Send it out. */
id|result
op_assign
id|usb_stor_bulk_msg
(paren
id|us
comma
id|fcb
comma
id|opipe
comma
id|FCM_PACKET_LENGTH
comma
op_amp
id|partial
)paren
suffix:semicolon
multiline_comment|/* The Freecom device will only fail if there is something wrong in&n;         * USB land.  It returns the status in its own registers, which&n;         * come back in the bulk pipe. */
r_if
c_cond
(paren
id|result
op_ne
l_int|0
)paren
(brace
id|US_DEBUGP
(paren
l_string|&quot;freecom xport failure: r=%d, p=%d&bslash;n&quot;
comma
id|result
comma
id|partial
)paren
suffix:semicolon
multiline_comment|/* -ENOENT -- we canceled this transfer */
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ENOENT
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;freecom_transport(): transfer aborted&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|US_BULK_TRANSFER_ABORTED
suffix:semicolon
)brace
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
multiline_comment|/* There are times we can optimize out this status read, but it&n;         * doesn&squot;t hurt us to always do it now. */
id|result
op_assign
id|usb_stor_bulk_msg
(paren
id|us
comma
id|fst
comma
id|ipipe
comma
id|FCM_PACKET_LENGTH
comma
op_amp
id|partial
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;foo Status result %d %d&bslash;n&quot;
comma
id|result
comma
id|partial
)paren
suffix:semicolon
multiline_comment|/* -ENOENT -- we canceled this transfer */
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ENOENT
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;freecom_transport(): transfer aborted&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|US_BULK_TRANSFER_ABORTED
suffix:semicolon
)brace
id|US_DEBUG
c_func
(paren
id|pdump
(paren
(paren
r_void
op_star
)paren
id|fst
comma
id|partial
)paren
)paren
suffix:semicolon
multiline_comment|/* The firmware will time-out commands after 20 seconds. Some commands&n;&t; * can legitimately take longer than this, so we use a different&n;&t; * command that only waits for the interrupt and then sends status,&n;&t; * without having to send a new ATAPI command to the device. &n;&t; *&n;&t; * NOTE: There is some indication that a data transfer after a timeout&n;&t; * may not work, but that is a condition that should never happen.&n;&t; */
r_while
c_loop
(paren
id|fst-&gt;Status
op_amp
id|FCM_STATUS_BUSY
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;20 second USB/ATAPI bridge TIMEOUT occured!&bslash;n&quot;
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;fst-&gt;Status is %x&bslash;n&quot;
comma
id|fst-&gt;Status
)paren
suffix:semicolon
multiline_comment|/* Get the status again */
id|fcb-&gt;Type
op_assign
id|FCM_PACKET_STATUS
suffix:semicolon
id|fcb-&gt;Timeout
op_assign
l_int|0
suffix:semicolon
id|memset
(paren
id|fcb-&gt;Atapi
comma
l_int|0
comma
r_sizeof
(paren
id|fcb-&gt;Filler
)paren
)paren
suffix:semicolon
id|memset
(paren
id|fcb-&gt;Filler
comma
l_int|0
comma
r_sizeof
(paren
id|fcb-&gt;Filler
)paren
)paren
suffix:semicolon
multiline_comment|/* Send it out. */
id|result
op_assign
id|usb_stor_bulk_msg
(paren
id|us
comma
id|fcb
comma
id|opipe
comma
id|FCM_PACKET_LENGTH
comma
op_amp
id|partial
)paren
suffix:semicolon
multiline_comment|/* The Freecom device will only fail if there is something&n;&t;&t; * wrong in USB land.  It returns the status in its own&n;&t;&t; * registers, which come back in the bulk pipe.&n;&t;&t; */
r_if
c_cond
(paren
id|result
op_ne
l_int|0
)paren
(brace
id|US_DEBUGP
(paren
l_string|&quot;freecom xport failure: r=%d, p=%d&bslash;n&quot;
comma
id|result
comma
id|partial
)paren
suffix:semicolon
multiline_comment|/* -ENOENT -- we canceled this transfer */
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ENOENT
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;freecom_transport(): transfer aborted&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|US_BULK_TRANSFER_ABORTED
suffix:semicolon
)brace
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
multiline_comment|/* get the data */
id|result
op_assign
id|usb_stor_bulk_msg
(paren
id|us
comma
id|fst
comma
id|ipipe
comma
id|FCM_PACKET_LENGTH
comma
op_amp
id|partial
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;bar Status result %d %d&bslash;n&quot;
comma
id|result
comma
id|partial
)paren
suffix:semicolon
multiline_comment|/* -ENOENT -- we canceled this transfer */
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ENOENT
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;freecom_transport(): transfer aborted&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|US_BULK_TRANSFER_ABORTED
suffix:semicolon
)brace
id|US_DEBUG
c_func
(paren
id|pdump
(paren
(paren
r_void
op_star
)paren
id|fst
comma
id|partial
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|partial
op_ne
l_int|4
op_logical_or
id|result
op_ne
l_int|0
)paren
(brace
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|fst-&gt;Status
op_amp
l_int|1
)paren
op_ne
l_int|0
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;operation failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_FAILED
suffix:semicolon
)brace
multiline_comment|/* The device might not have as much data available as we&n;         * requested.  If you ask for more than the device has, this reads&n;         * and such will hang. */
id|US_DEBUGP
c_func
(paren
l_string|&quot;Device indicates that it has %d bytes available&bslash;n&quot;
comma
id|le16_to_cpu
(paren
id|fst-&gt;Count
)paren
)paren
suffix:semicolon
multiline_comment|/* Find the length we desire to read. */
id|length
op_assign
id|usb_stor_transfer_length
(paren
id|srb
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;SCSI requested %d&bslash;n&quot;
comma
id|length
)paren
suffix:semicolon
multiline_comment|/* verify that this amount is legal */
r_if
c_cond
(paren
id|length
OG
id|srb-&gt;request_bufflen
)paren
(brace
id|length
op_assign
id|srb-&gt;request_bufflen
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;Truncating request to match buffer length: %d&bslash;n&quot;
comma
id|length
)paren
suffix:semicolon
)brace
multiline_comment|/* What we do now depends on what direction the data is supposed to&n;         * move in. */
r_switch
c_cond
(paren
id|us-&gt;srb-&gt;sc_data_direction
)paren
(brace
r_case
id|SCSI_DATA_READ
suffix:colon
multiline_comment|/* Make sure that the status indicates that the device&n;                 * wants data as well. */
r_if
c_cond
(paren
(paren
id|fst-&gt;Status
op_amp
id|DRQ_STAT
)paren
op_eq
l_int|0
op_logical_or
(paren
id|fst-&gt;Reason
op_amp
l_int|3
)paren
op_ne
l_int|2
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;SCSI wants data, drive doesn&squot;t have any&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_FAILED
suffix:semicolon
)brace
id|result
op_assign
id|freecom_readdata
(paren
id|srb
comma
id|us
comma
id|ipipe
comma
id|opipe
comma
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|USB_STOR_TRANSPORT_GOOD
)paren
r_return
id|result
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;FCM: Waiting for status&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
id|usb_stor_bulk_msg
(paren
id|us
comma
id|fst
comma
id|ipipe
comma
id|FCM_PACKET_LENGTH
comma
op_amp
id|partial
)paren
suffix:semicolon
id|US_DEBUG
c_func
(paren
id|pdump
(paren
(paren
r_void
op_star
)paren
id|fst
comma
id|partial
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ENOENT
)paren
(brace
id|US_DEBUGP
(paren
l_string|&quot;freecom_transport: transfer aborted&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|US_BULK_TRANSFER_ABORTED
suffix:semicolon
)brace
r_if
c_cond
(paren
id|partial
op_ne
l_int|4
op_logical_or
id|result
op_ne
l_int|0
)paren
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fst-&gt;Status
op_amp
id|ERR_STAT
)paren
op_ne
l_int|0
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;operation failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_FAILED
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|fst-&gt;Reason
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;Drive seems still hungry&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_FAILED
suffix:semicolon
)brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;Transfer happy&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSI_DATA_WRITE
suffix:colon
multiline_comment|/* Make sure the status indicates that the device wants to&n;                 * send us data. */
multiline_comment|/* !!IMPLEMENT!! */
id|result
op_assign
id|freecom_writedata
(paren
id|srb
comma
id|us
comma
id|ipipe
comma
id|opipe
comma
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|USB_STOR_TRANSPORT_GOOD
)paren
r_return
id|result
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;FCM: Waiting for status&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
id|usb_stor_bulk_msg
(paren
id|us
comma
id|fst
comma
id|ipipe
comma
id|FCM_PACKET_LENGTH
comma
op_amp
id|partial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|ENOENT
)paren
(brace
id|US_DEBUGP
(paren
l_string|&quot;freecom_transport: transfer aborted&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|US_BULK_TRANSFER_ABORTED
suffix:semicolon
)brace
r_if
c_cond
(paren
id|partial
op_ne
l_int|4
op_logical_or
id|result
op_ne
l_int|0
)paren
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fst-&gt;Status
op_amp
id|ERR_STAT
)paren
op_ne
l_int|0
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;operation failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_FAILED
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|fst-&gt;Reason
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;Drive seems still hungry&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_FAILED
suffix:semicolon
)brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;Transfer happy&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSI_DATA_NONE
suffix:colon
multiline_comment|/* Easy, do nothing. */
r_break
suffix:semicolon
r_default
suffix:colon
id|US_DEBUGP
(paren
l_string|&quot;freecom unimplemented direction: %d&bslash;n&quot;
comma
id|us-&gt;srb-&gt;sc_data_direction
)paren
suffix:semicolon
singleline_comment|// Return fail, SCSI seems to handle this better.
r_return
id|USB_STOR_TRANSPORT_FAILED
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;Freecom: transfer_length = %d&bslash;n&quot;
comma
id|usb_stor_transfer_length
(paren
id|srb
)paren
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;Freecom: direction = %d&bslash;n&quot;
comma
id|srb-&gt;sc_data_direction
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
r_int
DECL|function|freecom_init
id|freecom_init
(paren
r_struct
id|us_data
op_star
id|us
)paren
(brace
r_int
id|result
suffix:semicolon
r_char
id|buffer
(braket
l_int|33
)braket
suffix:semicolon
multiline_comment|/* Allocate a buffer for us.  The upper usb transport code will&n;         * free this for us when cleaning up. */
r_if
c_cond
(paren
id|us-&gt;extra
op_eq
l_int|NULL
)paren
(brace
id|us-&gt;extra
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|freecom_udata
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|us-&gt;extra
op_eq
l_int|NULL
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;Out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
)brace
id|result
op_assign
id|usb_control_msg
c_func
(paren
id|us-&gt;pusb_dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|us-&gt;pusb_dev
comma
l_int|0
)paren
comma
l_int|0x4c
comma
l_int|0xc0
comma
l_int|0x4346
comma
l_int|0x0
comma
id|buffer
comma
l_int|0x20
comma
l_int|3
op_star
id|HZ
)paren
suffix:semicolon
id|buffer
(braket
l_int|32
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;String returned from FC init is: %s&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
multiline_comment|/* Special thanks to the people at Freecom for providing me with&n;&t; * this &quot;magic sequence&quot;, which they use in their Windows and MacOS&n;&t; * drivers to make sure that all the attached perhiperals are&n;&t; * properly reset.&n;&t; */
multiline_comment|/* send reset */
id|result
op_assign
id|usb_control_msg
c_func
(paren
id|us-&gt;pusb_dev
comma
id|usb_sndctrlpipe
c_func
(paren
id|us-&gt;pusb_dev
comma
l_int|0
)paren
comma
l_int|0x4d
comma
l_int|0x40
comma
l_int|0x24d8
comma
l_int|0x0
comma
l_int|NULL
comma
l_int|0x0
comma
l_int|3
op_star
id|HZ
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;result from activate reset is %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
multiline_comment|/* wait 250ms */
id|mdelay
c_func
(paren
l_int|250
)paren
suffix:semicolon
multiline_comment|/* clear reset */
id|result
op_assign
id|usb_control_msg
c_func
(paren
id|us-&gt;pusb_dev
comma
id|usb_sndctrlpipe
c_func
(paren
id|us-&gt;pusb_dev
comma
l_int|0
)paren
comma
l_int|0x4d
comma
l_int|0x40
comma
l_int|0x24f8
comma
l_int|0x0
comma
l_int|NULL
comma
l_int|0x0
comma
l_int|3
op_star
id|HZ
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;result from clear reset is %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
multiline_comment|/* wait 3 seconds */
id|mdelay
c_func
(paren
l_int|3
op_star
l_int|1000
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
)brace
DECL|function|usb_stor_freecom_reset
r_int
id|usb_stor_freecom_reset
c_func
(paren
r_struct
id|us_data
op_star
id|us
)paren
(brace
id|printk
(paren
id|KERN_CRIT
l_string|&quot;freecom reset called&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* We don&squot;t really have this feature. */
r_return
id|FAILED
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_USB_STORAGE_DEBUG
DECL|function|pdump
r_static
r_void
id|pdump
(paren
r_void
op_star
id|ibuffer
comma
r_int
id|length
)paren
(brace
r_static
r_char
id|line
(braket
l_int|80
)braket
suffix:semicolon
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_int
r_char
op_star
id|buffer
op_assign
(paren
r_int
r_char
op_star
)paren
id|ibuffer
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|from
comma
id|base
suffix:semicolon
id|offset
op_assign
l_int|0
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
id|length
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
op_amp
l_int|15
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
(brace
id|offset
op_add_assign
id|sprintf
(paren
id|line
op_plus
id|offset
comma
l_string|&quot; - &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|i
op_minus
l_int|16
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
id|buffer
(braket
id|j
)braket
op_ge
l_int|32
op_logical_and
id|buffer
(braket
id|j
)braket
op_le
l_int|126
)paren
id|line
(braket
id|offset
op_increment
)braket
op_assign
id|buffer
(braket
id|j
)braket
suffix:semicolon
r_else
id|line
(braket
id|offset
op_increment
)braket
op_assign
l_char|&squot;.&squot;
suffix:semicolon
)brace
id|line
(braket
id|offset
)braket
op_assign
l_int|0
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|line
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
)brace
id|offset
op_add_assign
id|sprintf
(paren
id|line
op_plus
id|offset
comma
l_string|&quot;%08x:&quot;
comma
id|i
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|i
op_amp
l_int|7
)paren
op_eq
l_int|0
)paren
(brace
id|offset
op_add_assign
id|sprintf
(paren
id|line
op_plus
id|offset
comma
l_string|&quot; -&quot;
)paren
suffix:semicolon
)brace
id|offset
op_add_assign
id|sprintf
(paren
id|line
op_plus
id|offset
comma
l_string|&quot; %02x&quot;
comma
id|buffer
(braket
id|i
)braket
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
multiline_comment|/* Add the last &quot;chunk&quot; of data. */
id|from
op_assign
(paren
id|length
op_minus
l_int|1
)paren
op_mod
l_int|16
suffix:semicolon
id|base
op_assign
(paren
(paren
id|length
op_minus
l_int|1
)paren
op_div
l_int|16
)paren
op_star
l_int|16
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|from
op_plus
l_int|1
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|offset
op_add_assign
id|sprintf
(paren
id|line
op_plus
id|offset
comma
l_string|&quot;   &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from
OL
l_int|8
)paren
id|offset
op_add_assign
id|sprintf
(paren
id|line
op_plus
id|offset
comma
l_string|&quot;  &quot;
)paren
suffix:semicolon
id|offset
op_add_assign
id|sprintf
(paren
id|line
op_plus
id|offset
comma
l_string|&quot; - &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|from
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|buffer
(braket
id|base
op_plus
id|i
)braket
op_ge
l_int|32
op_logical_and
id|buffer
(braket
id|base
op_plus
id|i
)braket
op_le
l_int|126
)paren
id|line
(braket
id|offset
op_increment
)braket
op_assign
id|buffer
(braket
id|base
op_plus
id|i
)braket
suffix:semicolon
r_else
id|line
(braket
id|offset
op_increment
)braket
op_assign
l_char|&squot;.&squot;
suffix:semicolon
)brace
id|line
(braket
id|offset
)braket
op_assign
l_int|0
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|line
)paren
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
