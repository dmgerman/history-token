multiline_comment|/* &n; *  Transport specific attributes.&n; *&n; *  Copyright (c) 2003 Silicon Graphics, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef SCSI_TRANSPORT_H
DECL|macro|SCSI_TRANSPORT_H
mdefine_line|#define SCSI_TRANSPORT_H
DECL|struct|scsi_transport_template
r_struct
id|scsi_transport_template
(brace
multiline_comment|/* The NULL terminated list of transport attributes&n;&t; * that should be exported.&n;&t; */
DECL|member|attrs
r_struct
id|class_device_attribute
op_star
op_star
id|attrs
suffix:semicolon
multiline_comment|/* The transport class that the device is in */
DECL|member|class
r_struct
r_class
op_star
r_class
suffix:semicolon
multiline_comment|/* Constructor/Destructor functions */
DECL|member|setup
r_int
(paren
op_star
id|setup
)paren
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
DECL|member|cleanup
r_void
(paren
op_star
id|cleanup
)paren
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
multiline_comment|/* The size of the specific transport attribute structure (a&n;&t; * space of this size will be left at the end of the&n;&t; * scsi_device structure */
DECL|member|size
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* SCSI_TRANSPORT_H */
eof
