multiline_comment|/* &n; *  Parallel SCSI (SPI) transport specific attributes exported to sysfs.&n; *&n; *  Copyright (c) 2003 Silicon Graphics, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef SCSI_TRANSPORT_SPI_H
DECL|macro|SCSI_TRANSPORT_SPI_H
mdefine_line|#define SCSI_TRANSPORT_SPI_H
macro_line|#include &lt;linux/config.h&gt;
r_struct
id|scsi_transport_template
suffix:semicolon
DECL|struct|spi_transport_attrs
r_struct
id|spi_transport_attrs
(brace
DECL|member|period
r_int
id|period
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* accessor functions */
DECL|macro|spi_period
mdefine_line|#define spi_period(x)&t;(((struct spi_transport_attrs *)&amp;(x)-&gt;transport_data)-&gt;period)
DECL|macro|spi_offset
mdefine_line|#define spi_offset(x)&t;(((struct spi_transport_attrs *)&amp;(x)-&gt;transport_data)-&gt;offset)
r_extern
r_struct
id|scsi_transport_template
id|spi_transport_template
suffix:semicolon
macro_line|#endif /* SCSI_TRANSPORT_SPI_H */
eof
