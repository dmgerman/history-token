multiline_comment|/* Header File for In-System Design, Inc. ISD200 ASIC&n; *&n; * First release&n; *&n; * Current development and maintenance by:&n; *   (c) 2000 In-System Design, Inc. (support@in-system.com)&n; *&n; * See isd200.c for more information.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _USB_ISD200_H
DECL|macro|_USB_ISD200_H
mdefine_line|#define _USB_ISD200_H
r_extern
r_void
id|isd200_ata_command
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
r_extern
r_int
id|isd200_Initialization
c_func
(paren
r_struct
id|us_data
op_star
id|us
)paren
suffix:semicolon
macro_line|#endif
eof
