multiline_comment|/* &n; *  Transport specific attributes.&n; *&n; *  Copyright (c) 2003 Silicon Graphics, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef SCSI_TRANSPORT_H
DECL|macro|SCSI_TRANSPORT_H
mdefine_line|#define SCSI_TRANSPORT_H
macro_line|#include &lt;linux/transport_class.h&gt;
DECL|struct|scsi_transport_template
r_struct
id|scsi_transport_template
(brace
multiline_comment|/* The statistics attached to the host class only */
DECL|member|host_statistics
r_struct
id|attribute_group
op_star
id|host_statistics
suffix:semicolon
multiline_comment|/* the attribute containers */
DECL|member|host_attrs
r_struct
id|attribute_container
id|host_attrs
suffix:semicolon
DECL|member|target_attrs
r_struct
id|attribute_container
id|target_attrs
suffix:semicolon
DECL|member|device_attrs
r_struct
id|attribute_container
id|device_attrs
suffix:semicolon
multiline_comment|/* The size of the specific transport attribute structure (a&n;&t; * space of this size will be left at the end of the&n;&t; * scsi_* structure */
DECL|member|device_size
r_int
id|device_size
suffix:semicolon
DECL|member|target_size
r_int
id|target_size
suffix:semicolon
DECL|member|host_size
r_int
id|host_size
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|transport_class_to_shost
mdefine_line|#define transport_class_to_shost(tc) &bslash;&n;&t;dev_to_shost((tc)-&gt;dev)
macro_line|#endif /* SCSI_TRANSPORT_H */
eof
