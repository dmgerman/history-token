multiline_comment|/* Driver for Lexar &quot;Jumpshot&quot; USB Compact Flash reader&n; * Header File&n; *&n; * Current development and maintenance by:&n; *   (c) 2000 Jimmie Mayfield (mayfield+usb@sackheads.org)&n; *&n; * See jumpshot.c for more explanation&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _USB_JUMPSHOT_H
DECL|macro|_USB_JUMPSHOT_H
mdefine_line|#define _USB_JUMPSHOT_H
DECL|macro|min
mdefine_line|#define min(a,b) (((a)&lt;(b))?(a):(b))  
singleline_comment|// this is defined in tons of header files, i wish it had a standar single definition...
r_extern
r_int
id|jumpshot_transport
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
suffix:semicolon
DECL|struct|jumpshot_info
r_struct
id|jumpshot_info
(brace
DECL|member|sectors
r_int
r_int
id|sectors
suffix:semicolon
singleline_comment|// total sector count
DECL|member|ssize
r_int
r_int
id|ssize
suffix:semicolon
singleline_comment|// sector size in bytes
singleline_comment|// the following aren&squot;t used yet
DECL|member|sense_key
r_int
r_char
id|sense_key
suffix:semicolon
DECL|member|sense_asc
r_int
r_int
id|sense_asc
suffix:semicolon
singleline_comment|// additional sense code
DECL|member|sense_ascq
r_int
r_int
id|sense_ascq
suffix:semicolon
singleline_comment|// additional sense code qualifier
)brace
suffix:semicolon
macro_line|#endif
eof
