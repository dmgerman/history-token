multiline_comment|/* Special Initializers for certain USB Mass Storage devices&n; *&n; * $Id: initializers.c,v 1.2 2000/09/06 22:35:57 mdharm Exp $&n; *&n; * Current development and maintenance by:&n; *   (c) 1999, 2000 Matthew Dharm (mdharm-usb@one-eyed-alien.net)&n; *&n; * This driver is based on the &squot;USB Mass Storage Class&squot; document. This&n; * describes in detail the protocol used to communicate with such&n; * devices.  Clearly, the designers had SCSI and ATAPI commands in&n; * mind when they created this document.  The commands are all very&n; * similar to commands in the SCSI-II and ATAPI specifications.&n; *&n; * It is important to note that in a number of cases this class&n; * exhibits class-specific exemptions from the USB specification.&n; * Notably the usage of NAK, STALL and ACK differs from the norm, in&n; * that they are used to communicate wait, failed and OK on commands.&n; *&n; * Also, for certain devices, the interrupt endpoint is used to convey&n; * status of a command.&n; *&n; * Please see http://www.one-eyed-alien.net/~mdharm/linux-usb for more&n; * information about this driver.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &quot;initializers.h&quot;
macro_line|#include &quot;debug.h&quot;
macro_line|#include &quot;transport.h&quot;
multiline_comment|/* This places the Shuttle/SCM USB&lt;-&gt;SCSI bridge devices in multi-target&n; * mode */
DECL|function|usb_stor_euscsi_init
r_int
id|usb_stor_euscsi_init
c_func
(paren
r_struct
id|us_data
op_star
id|us
)paren
(brace
r_int
r_char
id|data
op_assign
l_int|0x1
suffix:semicolon
r_int
id|result
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;Attempting to init eUSCSI bridge...&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
id|usb_stor_control_msg
c_func
(paren
id|us
comma
id|us-&gt;send_ctrl_pipe
comma
l_int|0x0C
comma
id|USB_RECIP_INTERFACE
op_or
id|USB_TYPE_VENDOR
comma
l_int|0x01
comma
l_int|0x0
comma
op_amp
id|data
comma
l_int|0x1
comma
l_int|5
op_star
id|HZ
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;-- result is %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;-- data afterwards is %d&bslash;n&quot;
comma
id|data
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This function is required to activate all four slots on the UCR-61S2B&n; * flash reader */
DECL|function|usb_stor_ucr61s2b_init
r_int
id|usb_stor_ucr61s2b_init
c_func
(paren
r_struct
id|us_data
op_star
id|us
)paren
(brace
r_struct
id|bulk_cb_wrap
op_star
id|bcb
suffix:semicolon
r_struct
id|bulk_cs_wrap
op_star
id|bcs
suffix:semicolon
r_int
id|res
comma
id|partial
suffix:semicolon
id|bcb
op_assign
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|bcb
comma
id|in_interrupt
c_func
(paren
)paren
ques
c_cond
id|GFP_ATOMIC
suffix:colon
id|GFP_NOIO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bcb
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|bcs
op_assign
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|bcs
comma
id|in_interrupt
c_func
(paren
)paren
ques
c_cond
id|GFP_ATOMIC
suffix:colon
id|GFP_NOIO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bcs
)paren
(brace
id|kfree
c_func
(paren
id|bcb
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|US_DEBUGP
c_func
(paren
l_string|&quot;Sending UCR-61S2B initialization packet...&bslash;n&quot;
)paren
suffix:semicolon
id|bcb-&gt;Signature
op_assign
id|cpu_to_le32
c_func
(paren
id|US_BULK_CB_SIGN
)paren
suffix:semicolon
id|bcb-&gt;Tag
op_assign
l_int|0
suffix:semicolon
id|bcb-&gt;DataTransferLength
op_assign
id|cpu_to_le32
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|bcb-&gt;Flags
op_assign
id|bcb-&gt;Lun
op_assign
l_int|0
suffix:semicolon
id|bcb-&gt;Length
op_assign
r_sizeof
(paren
id|UCR61S2B_INIT
)paren
suffix:semicolon
id|memset
c_func
(paren
id|bcb-&gt;CDB
comma
l_int|0
comma
r_sizeof
(paren
id|bcb-&gt;CDB
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|bcb-&gt;CDB
comma
id|UCR61S2B_INIT
comma
r_sizeof
(paren
id|UCR61S2B_INIT
)paren
)paren
suffix:semicolon
id|res
op_assign
id|usb_stor_bulk_transfer_buf
c_func
(paren
id|us
comma
id|us-&gt;send_bulk_pipe
comma
id|bcb
comma
id|US_BULK_CB_WRAP_LEN
comma
op_amp
id|partial
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;-- result is %d&bslash;n&quot;
comma
id|res
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|bcb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
id|kfree
c_func
(paren
id|bcs
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|res
op_assign
id|usb_stor_bulk_transfer_buf
c_func
(paren
id|us
comma
id|us-&gt;recv_bulk_pipe
comma
id|bcs
comma
id|US_BULK_CS_WRAP_LEN
comma
op_amp
id|partial
)paren
suffix:semicolon
id|US_DEBUGP
c_func
(paren
l_string|&quot;-- result of status read is %d&bslash;n&quot;
comma
id|res
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|bcs
)paren
suffix:semicolon
r_return
id|res
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
eof
