multiline_comment|/* Driver for USB Mass Storage compliant devices&n; * SCSI Connecting Glue Header File&n; *&n; * $Id: scsiglue.h,v 1.4 2000/08/25 00:13:51 mdharm Exp $&n; *&n; * Current development and maintenance by:&n; *   (c) 1999, 2000 Matthew Dharm (mdharm-usb@one-eyed-alien.net)&n; *&n; * This driver is based on the &squot;USB Mass Storage Class&squot; document. This&n; * describes in detail the protocol used to communicate with such&n; * devices.  Clearly, the designers had SCSI and ATAPI commands in&n; * mind when they created this document.  The commands are all very&n; * similar to commands in the SCSI-II and ATAPI specifications.&n; *&n; * It is important to note that in a number of cases this class&n; * exhibits class-specific exemptions from the USB specification.&n; * Notably the usage of NAK, STALL and ACK differs from the norm, in&n; * that they are used to communicate wait, failed and OK on commands.&n; *&n; * Also, for certain devices, the interrupt endpoint is used to convey&n; * status of a command.&n; *&n; * Please see http://www.one-eyed-alien.net/~mdharm/linux-usb for more&n; * information about this driver.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _SCSIGLUE_H_
DECL|macro|_SCSIGLUE_H_
mdefine_line|#define _SCSIGLUE_H_
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
r_extern
r_int
r_char
id|usb_stor_sense_notready
(braket
l_int|18
)braket
suffix:semicolon
r_extern
r_int
r_char
id|usb_stor_sense_invalidCDB
(braket
l_int|18
)braket
suffix:semicolon
r_extern
id|Scsi_Host_Template
id|usb_stor_host_template
suffix:semicolon
r_extern
r_int
id|usb_stor_scsiSense10to6
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|usb_stor_scsiSense6to10
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
