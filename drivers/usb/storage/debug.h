multiline_comment|/* Driver for USB Mass Storage compliant devices&n; * Debugging Functions Header File&n; *&n; * $Id: debug.h,v 1.6 2001/01/12 23:51:04 mdharm Exp $&n; *&n; * Current development and maintenance by:&n; *   (c) 1999, 2000 Matthew Dharm (mdharm-usb@one-eyed-alien.net)&n; *&n; * Initial work by:&n; *   (c) 1999 Michael Gee (michael@linuxspecific.com)&n; *&n; * This driver is based on the &squot;USB Mass Storage Class&squot; document. This&n; * describes in detail the protocol used to communicate with such&n; * devices.  Clearly, the designers had SCSI and ATAPI commands in&n; * mind when they created this document.  The commands are all very&n; * similar to commands in the SCSI-II and ATAPI specifications.&n; *&n; * It is important to note that in a number of cases this class&n; * exhibits class-specific exemptions from the USB specification.&n; * Notably the usage of NAK, STALL and ACK differs from the norm, in&n; * that they are used to communicate wait, failed and OK on commands.&n; *&n; * Also, for certain devices, the interrupt endpoint is used to convey&n; * status of a command.&n; *&n; * Please see http://www.one-eyed-alien.net/~mdharm/linux-usb for more&n; * information about this driver.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _DEBUG_H_
DECL|macro|_DEBUG_H_
mdefine_line|#define _DEBUG_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/cdrom.h&gt;
macro_line|#include &quot;scsi.h&quot;
DECL|macro|USB_STORAGE
mdefine_line|#define USB_STORAGE &quot;usb-storage: &quot;
macro_line|#ifdef CONFIG_USB_STORAGE_DEBUG
r_void
id|usb_stor_show_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|srb
)paren
suffix:semicolon
r_void
id|usb_stor_print_Scsi_Cmnd
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_void
id|usb_stor_show_sense
c_func
(paren
r_int
r_char
id|key
comma
r_int
r_char
id|asc
comma
r_int
r_char
id|ascq
)paren
suffix:semicolon
DECL|macro|US_DEBUGP
mdefine_line|#define US_DEBUGP(x...) printk( KERN_DEBUG USB_STORAGE x )
DECL|macro|US_DEBUGPX
mdefine_line|#define US_DEBUGPX(x...) printk( x )
DECL|macro|US_DEBUG
mdefine_line|#define US_DEBUG(x) x 
macro_line|#else
DECL|macro|US_DEBUGP
mdefine_line|#define US_DEBUGP(x...)
DECL|macro|US_DEBUGPX
mdefine_line|#define US_DEBUGPX(x...)
DECL|macro|US_DEBUG
mdefine_line|#define US_DEBUG(x)
macro_line|#endif
macro_line|#endif
eof
