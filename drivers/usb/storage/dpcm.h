multiline_comment|/* Driver for Microtech DPCM-USB CompactFlash/SmartMedia reader&n; *&n; * $Id: dpcm.h,v 1.2 2000/08/25 00:13:51 mdharm Exp $&n; *&n; * DPCM driver v0.1:&n; *&n; * First release&n; *&n; * Current development and maintenance by:&n; *   (c) 2000 Brian Webb (webbb@earthlink.net)&n; *&n; * See dpcm.c for more explanation&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef _MICROTECH_DPCM_USB_H
DECL|macro|_MICROTECH_DPCM_USB_H
mdefine_line|#define _MICROTECH_DPCM_USB_H
r_extern
r_int
id|dpcm_transport
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
macro_line|#endif
eof
