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
multiline_comment|/* value in the PPR/SDTR command */
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|width
r_int
id|width
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0 - narrow, 1 - wide */
DECL|member|iu
r_int
id|iu
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Information Units enabled */
DECL|member|dt
r_int
id|dt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* DT clocking enabled */
DECL|member|qas
r_int
id|qas
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Quick Arbitration and Selection enabled */
DECL|member|wr_flow
r_int
id|wr_flow
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Write Flow control enabled */
DECL|member|rd_strm
r_int
id|rd_strm
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Read streaming enabled */
DECL|member|rti
r_int
id|rti
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Retain Training Information */
DECL|member|pcomp_en
r_int
id|pcomp_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Precompensation enabled */
)brace
suffix:semicolon
multiline_comment|/* accessor functions */
DECL|macro|spi_period
mdefine_line|#define spi_period(x)&t;(((struct spi_transport_attrs *)&amp;(x)-&gt;transport_data)-&gt;period)
DECL|macro|spi_offset
mdefine_line|#define spi_offset(x)&t;(((struct spi_transport_attrs *)&amp;(x)-&gt;transport_data)-&gt;offset)
DECL|macro|spi_width
mdefine_line|#define spi_width(x)&t;(((struct spi_transport_attrs *)&amp;(x)-&gt;transport_data)-&gt;width)
DECL|macro|spi_iu
mdefine_line|#define spi_iu(x)&t;(((struct spi_transport_attrs *)&amp;(x)-&gt;transport_data)-&gt;iu)
DECL|macro|spi_dt
mdefine_line|#define spi_dt(x)&t;(((struct spi_transport_attrs *)&amp;(x)-&gt;transport_data)-&gt;dt)
DECL|macro|spi_qas
mdefine_line|#define spi_qas(x)&t;(((struct spi_transport_attrs *)&amp;(x)-&gt;transport_data)-&gt;qas)
DECL|macro|spi_wr_flow
mdefine_line|#define spi_wr_flow(x)&t;(((struct spi_transport_attrs *)&amp;(x)-&gt;transport_data)-&gt;wr_flow)
DECL|macro|spi_rd_strm
mdefine_line|#define spi_rd_strm(x)&t;(((struct spi_transport_attrs *)&amp;(x)-&gt;transport_data)-&gt;rd_strm)
DECL|macro|spi_rti
mdefine_line|#define spi_rti(x)&t;(((struct spi_transport_attrs *)&amp;(x)-&gt;transport_data)-&gt;rti)
DECL|macro|spi_pcomp_en
mdefine_line|#define spi_pcomp_en(x)&t;(((struct spi_transport_attrs *)&amp;(x)-&gt;transport_data)-&gt;pcomp_en)
r_extern
r_struct
id|scsi_transport_template
id|spi_transport_template
suffix:semicolon
macro_line|#endif /* SCSI_TRANSPORT_SPI_H */
eof
