multiline_comment|/* Driver for Datafab USB Compact Flash reader&n; *&n; * $Id: datafab.c,v 1.7 2002/02/25 00:40:13 mdharm Exp $&n; *&n; * datafab driver v0.1:&n; *&n; * First release&n; *&n; * Current development and maintenance by:&n; *   (c) 2000 Jimmie Mayfield (mayfield+datafab@sackheads.org)&n; *&n; *   Many thanks to Robert Baruch for the SanDisk SmartMedia reader driver&n; *   which I used as a template for this driver.&n; *&n; *   Some bugfixes and scatter-gather code by Gregory P. Smith &n; *   (greg-usb@electricrain.com)&n; *&n; *   Fix for media change by Joerg Schneider (js@joergschneider.com)&n; *&n; * Other contributors:&n; *   (c) 2002 Alan Stern &lt;stern@rowland.org&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * This driver attempts to support USB CompactFlash reader/writer devices&n; * based on Datafab USB-to-ATA chips.  It was specifically developed for the &n; * Datafab MDCFE-B USB CompactFlash reader but has since been found to work &n; * with a variety of Datafab-based devices from a number of manufacturers.&n; * I&squot;ve received a report of this driver working with a Datafab-based&n; * SmartMedia device though please be aware that I&squot;m personally unable to&n; * test SmartMedia support.&n; *&n; * This driver supports reading and writing.  If you&squot;re truly paranoid,&n; * however, you can force the driver into a write-protected state by setting&n; * the WP enable bits in datafab_handle_mode_sense().  See the comments&n; * in that routine.&n; */
macro_line|#include &quot;transport.h&quot;
macro_line|#include &quot;protocol.h&quot;
macro_line|#include &quot;usb.h&quot;
macro_line|#include &quot;debug.h&quot;
macro_line|#include &quot;datafab.h&quot;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
r_static
r_int
id|datafab_determine_lun
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_struct
id|datafab_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_inline
r_int
DECL|function|datafab_bulk_read
id|datafab_bulk_read
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
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
r_return
id|USB_STOR_XFER_GOOD
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_bulk_read:  len = %d&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
r_return
id|usb_stor_bulk_transfer_buf
c_func
(paren
id|us
comma
id|us-&gt;recv_bulk_pipe
comma
id|data
comma
id|len
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|datafab_bulk_write
id|datafab_bulk_write
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
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
r_return
id|USB_STOR_XFER_GOOD
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_bulk_write:  len = %d&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
r_return
id|usb_stor_bulk_transfer_buf
c_func
(paren
id|us
comma
id|us-&gt;send_bulk_pipe
comma
id|data
comma
id|len
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|datafab_read_data
r_static
r_int
id|datafab_read_data
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_struct
id|datafab_info
op_star
id|info
comma
id|u32
id|sector
comma
id|u32
id|sectors
)paren
(brace
r_int
r_char
op_star
id|command
op_assign
id|us-&gt;iobuf
suffix:semicolon
r_int
r_char
op_star
id|buffer
suffix:semicolon
r_int
r_char
id|thistime
suffix:semicolon
r_int
r_int
id|totallen
comma
id|alloclen
suffix:semicolon
r_int
id|len
comma
id|result
suffix:semicolon
r_int
r_int
id|sg_idx
op_assign
l_int|0
comma
id|sg_offset
op_assign
l_int|0
suffix:semicolon
singleline_comment|// we&squot;re working in LBA mode.  according to the ATA spec, 
singleline_comment|// we can support up to 28-bit addressing.  I don&squot;t know if Datafab
singleline_comment|// supports beyond 24-bit addressing.  It&squot;s kind of hard to test 
singleline_comment|// since it requires &gt; 8GB CF card.
singleline_comment|//
r_if
c_cond
(paren
id|sectors
OG
l_int|0x0FFFFFFF
)paren
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;lun
op_eq
op_minus
l_int|1
)paren
(brace
id|result
op_assign
id|datafab_determine_lun
c_func
(paren
id|us
comma
id|info
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
)brace
id|totallen
op_assign
id|sectors
op_star
id|info-&gt;ssize
suffix:semicolon
singleline_comment|// Since we don&squot;t read more than 64 KB at a time, we have to create
singleline_comment|// a bounce buffer and move the data a piece at a time between the
singleline_comment|// bounce buffer and the actual transfer buffer.
id|alloclen
op_assign
id|min
c_func
(paren
id|totallen
comma
l_int|65536u
)paren
suffix:semicolon
id|buffer
op_assign
id|kmalloc
c_func
(paren
id|alloclen
comma
id|GFP_NOIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
op_eq
l_int|NULL
)paren
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
r_do
(brace
singleline_comment|// loop, never allocate or transfer more than 64k at once
singleline_comment|// (min(128k, 255*info-&gt;ssize) is the real limit)
id|len
op_assign
id|min
c_func
(paren
id|totallen
comma
id|alloclen
)paren
suffix:semicolon
id|thistime
op_assign
(paren
id|len
op_div
id|info-&gt;ssize
)paren
op_amp
l_int|0xff
suffix:semicolon
id|command
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|command
(braket
l_int|1
)braket
op_assign
id|thistime
suffix:semicolon
id|command
(braket
l_int|2
)braket
op_assign
id|sector
op_amp
l_int|0xFF
suffix:semicolon
id|command
(braket
l_int|3
)braket
op_assign
(paren
id|sector
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|command
(braket
l_int|4
)braket
op_assign
(paren
id|sector
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|command
(braket
l_int|5
)braket
op_assign
l_int|0xE0
op_plus
(paren
id|info-&gt;lun
op_lshift
l_int|4
)paren
suffix:semicolon
id|command
(braket
l_int|5
)braket
op_or_assign
(paren
id|sector
op_rshift
l_int|24
)paren
op_amp
l_int|0x0F
suffix:semicolon
id|command
(braket
l_int|6
)braket
op_assign
l_int|0x20
suffix:semicolon
id|command
(braket
l_int|7
)braket
op_assign
l_int|0x01
suffix:semicolon
singleline_comment|// send the read command
id|result
op_assign
id|datafab_bulk_write
c_func
(paren
id|us
comma
id|command
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|USB_STOR_XFER_GOOD
)paren
r_goto
id|leave
suffix:semicolon
singleline_comment|// read the result
id|result
op_assign
id|datafab_bulk_read
c_func
(paren
id|us
comma
id|buffer
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|USB_STOR_XFER_GOOD
)paren
r_goto
id|leave
suffix:semicolon
singleline_comment|// Store the data in the transfer buffer
id|usb_stor_access_xfer_buf
c_func
(paren
id|buffer
comma
id|len
comma
id|us-&gt;srb
comma
op_amp
id|sg_idx
comma
op_amp
id|sg_offset
comma
id|TO_XFER_BUF
)paren
suffix:semicolon
id|sector
op_add_assign
id|thistime
suffix:semicolon
id|totallen
op_sub_assign
id|len
suffix:semicolon
)brace
r_while
c_loop
(paren
id|totallen
OG
l_int|0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
id|leave
suffix:colon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
DECL|function|datafab_write_data
r_static
r_int
id|datafab_write_data
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_struct
id|datafab_info
op_star
id|info
comma
id|u32
id|sector
comma
id|u32
id|sectors
)paren
(brace
r_int
r_char
op_star
id|command
op_assign
id|us-&gt;iobuf
suffix:semicolon
r_int
r_char
op_star
id|reply
op_assign
id|us-&gt;iobuf
suffix:semicolon
r_int
r_char
op_star
id|buffer
suffix:semicolon
r_int
r_char
id|thistime
suffix:semicolon
r_int
r_int
id|totallen
comma
id|alloclen
suffix:semicolon
r_int
id|len
comma
id|result
suffix:semicolon
r_int
r_int
id|sg_idx
op_assign
l_int|0
comma
id|sg_offset
op_assign
l_int|0
suffix:semicolon
singleline_comment|// we&squot;re working in LBA mode.  according to the ATA spec, 
singleline_comment|// we can support up to 28-bit addressing.  I don&squot;t know if Datafab
singleline_comment|// supports beyond 24-bit addressing.  It&squot;s kind of hard to test 
singleline_comment|// since it requires &gt; 8GB CF card.
singleline_comment|//
r_if
c_cond
(paren
id|sectors
OG
l_int|0x0FFFFFFF
)paren
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;lun
op_eq
op_minus
l_int|1
)paren
(brace
id|result
op_assign
id|datafab_determine_lun
c_func
(paren
id|us
comma
id|info
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
)brace
id|totallen
op_assign
id|sectors
op_star
id|info-&gt;ssize
suffix:semicolon
singleline_comment|// Since we don&squot;t write more than 64 KB at a time, we have to create
singleline_comment|// a bounce buffer and move the data a piece at a time between the
singleline_comment|// bounce buffer and the actual transfer buffer.
id|alloclen
op_assign
id|min
c_func
(paren
id|totallen
comma
l_int|65536u
)paren
suffix:semicolon
id|buffer
op_assign
id|kmalloc
c_func
(paren
id|alloclen
comma
id|GFP_NOIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
op_eq
l_int|NULL
)paren
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
r_do
(brace
singleline_comment|// loop, never allocate or transfer more than 64k at once
singleline_comment|// (min(128k, 255*info-&gt;ssize) is the real limit)
id|len
op_assign
id|min
c_func
(paren
id|totallen
comma
id|alloclen
)paren
suffix:semicolon
id|thistime
op_assign
(paren
id|len
op_div
id|info-&gt;ssize
)paren
op_amp
l_int|0xff
suffix:semicolon
singleline_comment|// Get the data from the transfer buffer
id|usb_stor_access_xfer_buf
c_func
(paren
id|buffer
comma
id|len
comma
id|us-&gt;srb
comma
op_amp
id|sg_idx
comma
op_amp
id|sg_offset
comma
id|FROM_XFER_BUF
)paren
suffix:semicolon
id|command
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|command
(braket
l_int|1
)braket
op_assign
id|thistime
suffix:semicolon
id|command
(braket
l_int|2
)braket
op_assign
id|sector
op_amp
l_int|0xFF
suffix:semicolon
id|command
(braket
l_int|3
)braket
op_assign
(paren
id|sector
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|command
(braket
l_int|4
)braket
op_assign
(paren
id|sector
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|command
(braket
l_int|5
)braket
op_assign
l_int|0xE0
op_plus
(paren
id|info-&gt;lun
op_lshift
l_int|4
)paren
suffix:semicolon
id|command
(braket
l_int|5
)braket
op_or_assign
(paren
id|sector
op_rshift
l_int|24
)paren
op_amp
l_int|0x0F
suffix:semicolon
id|command
(braket
l_int|6
)braket
op_assign
l_int|0x30
suffix:semicolon
id|command
(braket
l_int|7
)braket
op_assign
l_int|0x02
suffix:semicolon
singleline_comment|// send the command
id|result
op_assign
id|datafab_bulk_write
c_func
(paren
id|us
comma
id|command
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|USB_STOR_XFER_GOOD
)paren
r_goto
id|leave
suffix:semicolon
singleline_comment|// send the data
id|result
op_assign
id|datafab_bulk_write
c_func
(paren
id|us
comma
id|buffer
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|USB_STOR_XFER_GOOD
)paren
r_goto
id|leave
suffix:semicolon
singleline_comment|// read the result
id|result
op_assign
id|datafab_bulk_read
c_func
(paren
id|us
comma
id|reply
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ne
id|USB_STOR_XFER_GOOD
)paren
r_goto
id|leave
suffix:semicolon
r_if
c_cond
(paren
id|reply
(braket
l_int|0
)braket
op_ne
l_int|0x50
op_logical_and
id|reply
(braket
l_int|1
)braket
op_ne
l_int|0
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_write_data:  Gah! &quot;
l_string|&quot;write return code: %02x %02x&bslash;n&quot;
comma
id|reply
(braket
l_int|0
)braket
comma
id|reply
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|result
op_assign
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
r_goto
id|leave
suffix:semicolon
)brace
id|sector
op_add_assign
id|thistime
suffix:semicolon
id|totallen
op_sub_assign
id|len
suffix:semicolon
)brace
r_while
c_loop
(paren
id|totallen
OG
l_int|0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
id|leave
suffix:colon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
DECL|function|datafab_determine_lun
r_static
r_int
id|datafab_determine_lun
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_struct
id|datafab_info
op_star
id|info
)paren
(brace
singleline_comment|// Dual-slot readers can be thought of as dual-LUN devices.
singleline_comment|// We need to determine which card slot is being used.
singleline_comment|// We&squot;ll send an IDENTIFY DEVICE command and see which LUN responds...
singleline_comment|//
singleline_comment|// There might be a better way of doing this?
r_static
r_int
r_char
id|scommand
(braket
l_int|8
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0xa0
comma
l_int|0xec
comma
l_int|1
)brace
suffix:semicolon
r_int
r_char
op_star
id|command
op_assign
id|us-&gt;iobuf
suffix:semicolon
r_int
r_char
op_star
id|buf
suffix:semicolon
r_int
id|count
op_assign
l_int|0
comma
id|rc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|us
op_logical_or
op_logical_neg
id|info
)paren
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
id|memcpy
c_func
(paren
id|command
comma
id|scommand
comma
l_int|8
)paren
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
l_int|512
comma
id|GFP_NOIO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_determine_lun:  locating...&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// we&squot;ll try 3 times before giving up...
singleline_comment|//
r_while
c_loop
(paren
id|count
op_increment
OL
l_int|3
)paren
(brace
id|command
(braket
l_int|5
)braket
op_assign
l_int|0xa0
suffix:semicolon
id|rc
op_assign
id|datafab_bulk_write
c_func
(paren
id|us
comma
id|command
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|USB_STOR_XFER_GOOD
)paren
(brace
id|rc
op_assign
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
r_goto
id|leave
suffix:semicolon
)brace
id|rc
op_assign
id|datafab_bulk_read
c_func
(paren
id|us
comma
id|buf
comma
l_int|512
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
id|USB_STOR_XFER_GOOD
)paren
(brace
id|info-&gt;lun
op_assign
l_int|0
suffix:semicolon
id|rc
op_assign
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
r_goto
id|leave
suffix:semicolon
)brace
id|command
(braket
l_int|5
)braket
op_assign
l_int|0xb0
suffix:semicolon
id|rc
op_assign
id|datafab_bulk_write
c_func
(paren
id|us
comma
id|command
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|USB_STOR_XFER_GOOD
)paren
(brace
id|rc
op_assign
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
r_goto
id|leave
suffix:semicolon
)brace
id|rc
op_assign
id|datafab_bulk_read
c_func
(paren
id|us
comma
id|buf
comma
l_int|512
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
id|USB_STOR_XFER_GOOD
)paren
(brace
id|info-&gt;lun
op_assign
l_int|1
suffix:semicolon
id|rc
op_assign
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
r_goto
id|leave
suffix:semicolon
)brace
id|wait_ms
c_func
(paren
l_int|20
)paren
suffix:semicolon
)brace
id|rc
op_assign
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
id|leave
suffix:colon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|datafab_id_device
r_static
r_int
id|datafab_id_device
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
r_struct
id|datafab_info
op_star
id|info
)paren
(brace
singleline_comment|// this is a variation of the ATA &quot;IDENTIFY DEVICE&quot; command...according
singleline_comment|// to the ATA spec, &squot;Sector Count&squot; isn&squot;t used but the Windows driver
singleline_comment|// sets this bit so we do too...
singleline_comment|//
r_static
r_int
r_char
id|scommand
(braket
l_int|8
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0xa0
comma
l_int|0xec
comma
l_int|1
)brace
suffix:semicolon
r_int
r_char
op_star
id|command
op_assign
id|us-&gt;iobuf
suffix:semicolon
r_int
r_char
op_star
id|reply
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|us
op_logical_or
op_logical_neg
id|info
)paren
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;lun
op_eq
op_minus
l_int|1
)paren
(brace
id|rc
op_assign
id|datafab_determine_lun
c_func
(paren
id|us
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|USB_STOR_TRANSPORT_GOOD
)paren
r_return
id|rc
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|command
comma
id|scommand
comma
l_int|8
)paren
suffix:semicolon
id|reply
op_assign
id|kmalloc
c_func
(paren
l_int|512
comma
id|GFP_NOIO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reply
)paren
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
id|command
(braket
l_int|5
)braket
op_add_assign
(paren
id|info-&gt;lun
op_lshift
l_int|4
)paren
suffix:semicolon
id|rc
op_assign
id|datafab_bulk_write
c_func
(paren
id|us
comma
id|command
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|USB_STOR_XFER_GOOD
)paren
(brace
id|rc
op_assign
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
r_goto
id|leave
suffix:semicolon
)brace
singleline_comment|// we&squot;ll go ahead and extract the media capacity while we&squot;re here...
singleline_comment|//
id|rc
op_assign
id|datafab_bulk_read
c_func
(paren
id|us
comma
id|reply
comma
l_int|512
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
id|USB_STOR_XFER_GOOD
)paren
(brace
singleline_comment|// capacity is at word offset 57-58
singleline_comment|//
id|info-&gt;sectors
op_assign
(paren
(paren
id|u32
)paren
(paren
id|reply
(braket
l_int|117
)braket
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|reply
(braket
l_int|116
)braket
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|reply
(braket
l_int|115
)braket
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|reply
(braket
l_int|114
)braket
)paren
)paren
suffix:semicolon
id|rc
op_assign
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
r_goto
id|leave
suffix:semicolon
)brace
id|rc
op_assign
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
id|leave
suffix:colon
id|kfree
c_func
(paren
id|reply
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|datafab_handle_mode_sense
r_static
r_int
id|datafab_handle_mode_sense
c_func
(paren
r_struct
id|us_data
op_star
id|us
comma
id|Scsi_Cmnd
op_star
id|srb
comma
r_int
id|sense_6
)paren
(brace
r_static
r_int
r_char
id|rw_err_page
(braket
l_int|12
)braket
op_assign
(brace
l_int|0x1
comma
l_int|0xA
comma
l_int|0x21
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_static
r_int
r_char
id|cache_page
(braket
l_int|12
)braket
op_assign
(brace
l_int|0x8
comma
l_int|0xA
comma
l_int|0x1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_static
r_int
r_char
id|rbac_page
(braket
l_int|12
)braket
op_assign
(brace
l_int|0x1B
comma
l_int|0xA
comma
l_int|0
comma
l_int|0x81
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_static
r_int
r_char
id|timer_page
(braket
l_int|8
)braket
op_assign
(brace
l_int|0x1C
comma
l_int|0x6
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
r_char
id|pc
comma
id|page_code
suffix:semicolon
r_int
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_struct
id|datafab_info
op_star
id|info
op_assign
(paren
r_struct
id|datafab_info
op_star
)paren
(paren
id|us-&gt;extra
)paren
suffix:semicolon
r_int
r_char
op_star
id|ptr
op_assign
id|us-&gt;iobuf
suffix:semicolon
singleline_comment|// most of this stuff is just a hack to get things working.  the
singleline_comment|// datafab reader doesn&squot;t present a SCSI interface so we
singleline_comment|// fudge the SCSI commands...
singleline_comment|//
id|pc
op_assign
id|srb-&gt;cmnd
(braket
l_int|2
)braket
op_rshift
l_int|6
suffix:semicolon
id|page_code
op_assign
id|srb-&gt;cmnd
(braket
l_int|2
)braket
op_amp
l_int|0x3F
suffix:semicolon
r_switch
c_cond
(paren
id|pc
)paren
(brace
r_case
l_int|0x0
suffix:colon
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_handle_mode_sense:  Current values&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1
suffix:colon
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_handle_mode_sense:  Changeable values&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x2
suffix:colon
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_handle_mode_sense:  Default values&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3
suffix:colon
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_handle_mode_sense:  Saves values&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ptr
comma
l_int|0
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sense_6
)paren
(brace
id|ptr
(braket
l_int|2
)braket
op_assign
l_int|0x00
suffix:semicolon
singleline_comment|// WP enable: 0x80
id|i
op_assign
l_int|4
suffix:semicolon
)brace
r_else
(brace
id|ptr
(braket
l_int|3
)braket
op_assign
l_int|0x00
suffix:semicolon
singleline_comment|// WP enable: 0x80
id|i
op_assign
l_int|8
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|page_code
)paren
(brace
r_default
suffix:colon
singleline_comment|// vendor-specific mode
id|info-&gt;sense_key
op_assign
l_int|0x05
suffix:semicolon
id|info-&gt;sense_asc
op_assign
l_int|0x24
suffix:semicolon
id|info-&gt;sense_ascq
op_assign
l_int|0x00
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_FAILED
suffix:semicolon
r_case
l_int|0x1
suffix:colon
id|memcpy
c_func
(paren
id|ptr
op_plus
id|i
comma
id|rw_err_page
comma
r_sizeof
(paren
id|rw_err_page
)paren
)paren
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
id|rw_err_page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x8
suffix:colon
id|memcpy
c_func
(paren
id|ptr
op_plus
id|i
comma
id|cache_page
comma
r_sizeof
(paren
id|cache_page
)paren
)paren
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
id|cache_page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1B
suffix:colon
id|memcpy
c_func
(paren
id|ptr
op_plus
id|i
comma
id|rbac_page
comma
r_sizeof
(paren
id|rbac_page
)paren
)paren
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
id|rbac_page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1C
suffix:colon
id|memcpy
c_func
(paren
id|ptr
op_plus
id|i
comma
id|timer_page
comma
r_sizeof
(paren
id|timer_page
)paren
)paren
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
id|timer_page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3F
suffix:colon
singleline_comment|// retrieve all pages
id|memcpy
c_func
(paren
id|ptr
op_plus
id|i
comma
id|timer_page
comma
r_sizeof
(paren
id|timer_page
)paren
)paren
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
id|timer_page
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ptr
op_plus
id|i
comma
id|rbac_page
comma
r_sizeof
(paren
id|rbac_page
)paren
)paren
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
id|rbac_page
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ptr
op_plus
id|i
comma
id|cache_page
comma
r_sizeof
(paren
id|cache_page
)paren
)paren
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
id|cache_page
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ptr
op_plus
id|i
comma
id|rw_err_page
comma
r_sizeof
(paren
id|rw_err_page
)paren
)paren
suffix:semicolon
id|i
op_add_assign
r_sizeof
(paren
id|rw_err_page
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sense_6
)paren
id|ptr
(braket
l_int|0
)braket
op_assign
id|i
op_minus
l_int|1
suffix:semicolon
r_else
(paren
(paren
id|u16
op_star
)paren
id|ptr
)paren
(braket
l_int|0
)braket
op_assign
id|cpu_to_be16
c_func
(paren
id|i
op_minus
l_int|2
)paren
suffix:semicolon
id|usb_stor_set_xfer_buf
c_func
(paren
id|ptr
comma
id|i
comma
id|srb
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
)brace
DECL|function|datafab_info_destructor
r_static
r_void
id|datafab_info_destructor
c_func
(paren
r_void
op_star
id|extra
)paren
(brace
singleline_comment|// this routine is a placeholder...
singleline_comment|// currently, we don&squot;t allocate any extra memory so we&squot;re okay
)brace
singleline_comment|// Transport for the Datafab MDCFE-B
singleline_comment|//
DECL|function|datafab_transport
r_int
id|datafab_transport
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
id|datafab_info
op_star
id|info
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_int
r_int
id|block
comma
id|blocks
suffix:semicolon
r_int
r_char
op_star
id|ptr
op_assign
id|us-&gt;iobuf
suffix:semicolon
r_static
r_int
r_char
id|inquiry_reply
(braket
l_int|8
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x80
comma
l_int|0x00
comma
l_int|0x01
comma
l_int|0x1F
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|us-&gt;extra
)paren
(brace
id|us-&gt;extra
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|datafab_info
)paren
comma
id|GFP_NOIO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|us-&gt;extra
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_transport:  Gah! &quot;
l_string|&quot;Can&squot;t allocate storage for Datafab info struct!&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
id|memset
c_func
(paren
id|us-&gt;extra
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|datafab_info
)paren
)paren
suffix:semicolon
id|us-&gt;extra_destructor
op_assign
id|datafab_info_destructor
suffix:semicolon
(paren
(paren
r_struct
id|datafab_info
op_star
)paren
id|us-&gt;extra
)paren
op_member_access_from_pointer
id|lun
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|info
op_assign
(paren
r_struct
id|datafab_info
op_star
)paren
(paren
id|us-&gt;extra
)paren
suffix:semicolon
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|INQUIRY
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_transport:  INQUIRY.  Returning bogus response&quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|ptr
comma
id|inquiry_reply
comma
r_sizeof
(paren
id|inquiry_reply
)paren
)paren
suffix:semicolon
id|fill_inquiry_response
c_func
(paren
id|us
comma
id|ptr
comma
l_int|36
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|READ_CAPACITY
)paren
(brace
id|info-&gt;ssize
op_assign
l_int|0x200
suffix:semicolon
singleline_comment|// hard coded 512 byte sectors as per ATA spec
id|rc
op_assign
id|datafab_id_device
c_func
(paren
id|us
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
id|USB_STOR_TRANSPORT_GOOD
)paren
r_return
id|rc
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_transport:  READ_CAPACITY:  %ld sectors, %ld bytes per sector&bslash;n&quot;
comma
id|info-&gt;sectors
comma
id|info-&gt;ssize
)paren
suffix:semicolon
singleline_comment|// build the reply
singleline_comment|// we need the last sector, not the number of sectors
(paren
(paren
id|u32
op_star
)paren
id|ptr
)paren
(braket
l_int|0
)braket
op_assign
id|cpu_to_be32
c_func
(paren
id|info-&gt;sectors
op_minus
l_int|1
)paren
suffix:semicolon
(paren
(paren
id|u32
op_star
)paren
id|ptr
)paren
(braket
l_int|1
)braket
op_assign
id|cpu_to_be32
c_func
(paren
id|info-&gt;ssize
)paren
suffix:semicolon
id|usb_stor_set_xfer_buf
c_func
(paren
id|ptr
comma
l_int|8
comma
id|srb
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|MODE_SELECT_10
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_transport:  Gah! MODE_SELECT_10.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_ERROR
suffix:semicolon
)brace
singleline_comment|// don&squot;t bother implementing READ_6 or WRITE_6.
singleline_comment|//
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|READ_10
)paren
(brace
id|block
op_assign
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|2
)braket
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|3
)braket
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|4
)braket
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
id|blocks
op_assign
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|7
)braket
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|8
)braket
)paren
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_transport:  READ_10: read block 0x%04lx  count %ld&bslash;n&quot;
comma
id|block
comma
id|blocks
)paren
suffix:semicolon
r_return
id|datafab_read_data
c_func
(paren
id|us
comma
id|info
comma
id|block
comma
id|blocks
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|READ_12
)paren
(brace
singleline_comment|// we&squot;ll probably never see a READ_12 but we&squot;ll do it anyway...
singleline_comment|//
id|block
op_assign
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|2
)braket
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|3
)braket
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|4
)braket
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
id|blocks
op_assign
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|6
)braket
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|7
)braket
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|8
)braket
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|9
)braket
)paren
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_transport:  READ_12: read block 0x%04lx  count %ld&bslash;n&quot;
comma
id|block
comma
id|blocks
)paren
suffix:semicolon
r_return
id|datafab_read_data
c_func
(paren
id|us
comma
id|info
comma
id|block
comma
id|blocks
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|WRITE_10
)paren
(brace
id|block
op_assign
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|2
)braket
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|3
)braket
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|4
)braket
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
id|blocks
op_assign
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|7
)braket
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|8
)braket
)paren
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_transport:  WRITE_10: write block 0x%04lx  count %ld&bslash;n&quot;
comma
id|block
comma
id|blocks
)paren
suffix:semicolon
r_return
id|datafab_write_data
c_func
(paren
id|us
comma
id|info
comma
id|block
comma
id|blocks
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|WRITE_12
)paren
(brace
singleline_comment|// we&squot;ll probably never see a WRITE_12 but we&squot;ll do it anyway...
singleline_comment|//
id|block
op_assign
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|2
)braket
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|3
)braket
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|4
)braket
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|5
)braket
)paren
)paren
suffix:semicolon
id|blocks
op_assign
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|6
)braket
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|7
)braket
)paren
op_lshift
l_int|16
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|8
)braket
)paren
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|u32
)paren
(paren
id|srb-&gt;cmnd
(braket
l_int|9
)braket
)paren
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_transport:  WRITE_12: write block 0x%04lx  count %ld&bslash;n&quot;
comma
id|block
comma
id|blocks
)paren
suffix:semicolon
r_return
id|datafab_write_data
c_func
(paren
id|us
comma
id|info
comma
id|block
comma
id|blocks
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|TEST_UNIT_READY
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_transport:  TEST_UNIT_READY.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|datafab_id_device
c_func
(paren
id|us
comma
id|info
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|REQUEST_SENSE
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_transport:  REQUEST_SENSE.  Returning faked response&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|// this response is pretty bogus right now.  eventually if necessary
singleline_comment|// we can set the correct sense data.  so far though it hasn&squot;t been
singleline_comment|// necessary
singleline_comment|//
id|memset
c_func
(paren
id|ptr
comma
l_int|0
comma
l_int|18
)paren
suffix:semicolon
id|ptr
(braket
l_int|0
)braket
op_assign
l_int|0xF0
suffix:semicolon
id|ptr
(braket
l_int|2
)braket
op_assign
id|info-&gt;sense_key
suffix:semicolon
id|ptr
(braket
l_int|7
)braket
op_assign
l_int|11
suffix:semicolon
id|ptr
(braket
l_int|12
)braket
op_assign
id|info-&gt;sense_asc
suffix:semicolon
id|ptr
(braket
l_int|13
)braket
op_assign
id|info-&gt;sense_ascq
suffix:semicolon
id|usb_stor_set_xfer_buf
c_func
(paren
id|ptr
comma
l_int|18
comma
id|srb
)paren
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|MODE_SENSE
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_transport:  MODE_SENSE_6 detected&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|datafab_handle_mode_sense
c_func
(paren
id|us
comma
id|srb
comma
id|TRUE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|MODE_SENSE_10
)paren
(brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_transport:  MODE_SENSE_10 detected&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|datafab_handle_mode_sense
c_func
(paren
id|us
comma
id|srb
comma
id|FALSE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|ALLOW_MEDIUM_REMOVAL
)paren
(brace
singleline_comment|// sure.  whatever.  not like we can stop the user from
singleline_comment|// popping the media out of the device (no locking doors, etc)
singleline_comment|//
r_return
id|USB_STOR_TRANSPORT_GOOD
suffix:semicolon
)brace
r_if
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
op_eq
id|START_STOP
)paren
(brace
multiline_comment|/* this is used by sd.c&squot;check_scsidisk_media_change to detect&n;&t;&t;   media change */
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_transport:  START_STOP.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* the first datafab_id_device after a media change returns&n;&t;&t;   an error (determined experimentally) */
id|rc
op_assign
id|datafab_id_device
c_func
(paren
id|us
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
id|USB_STOR_TRANSPORT_GOOD
)paren
(brace
id|info-&gt;sense_key
op_assign
id|NO_SENSE
suffix:semicolon
id|srb-&gt;result
op_assign
id|SUCCESS
suffix:semicolon
)brace
r_else
(brace
id|info-&gt;sense_key
op_assign
id|UNIT_ATTENTION
suffix:semicolon
id|srb-&gt;result
op_assign
id|SAM_STAT_CHECK_CONDITION
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;datafab_transport:  Gah! Unknown command: %d (0x%x)&bslash;n&quot;
comma
id|srb-&gt;cmnd
(braket
l_int|0
)braket
comma
id|srb-&gt;cmnd
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|info-&gt;sense_key
op_assign
l_int|0x05
suffix:semicolon
id|info-&gt;sense_asc
op_assign
l_int|0x20
suffix:semicolon
id|info-&gt;sense_ascq
op_assign
l_int|0x00
suffix:semicolon
r_return
id|USB_STOR_TRANSPORT_FAILED
suffix:semicolon
)brace
eof
