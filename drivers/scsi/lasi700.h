multiline_comment|/* -*- mode: c; c-basic-offset: 8 -*- */
multiline_comment|/* PARISC LASI driver for the 53c700 chip&n; *&n; * Copyright (C) 2001 by James.Bottomley@HansenPartnership.com&n;**-----------------------------------------------------------------------------&n;**  &n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n; */
macro_line|#ifndef _LASI700_H
DECL|macro|_LASI700_H
mdefine_line|#define _LASI700_H
r_static
r_int
id|lasi700_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_static
r_int
id|lasi700_driver_callback
c_func
(paren
r_struct
id|parisc_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|lasi700_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
DECL|macro|LASI700_SCSI
mdefine_line|#define LASI700_SCSI {&t;&t;&t;&t;&bslash;&n;&t;name:&t;&t;&quot;LASI SCSI 53c700&quot;,&t;&bslash;&n;&t;proc_name:&t;&quot;lasi700&quot;,&t;&t;&bslash;&n;&t;detect:&t;&t;lasi700_detect,&t;&t;&bslash;&n;&t;release:&t;lasi700_release,&t;&bslash;&n;&t;this_id:&t;7,&t;&t;&t;&bslash;&n;}
DECL|macro|LASI_710_SVERSION
mdefine_line|#define LASI_710_SVERSION&t;0x082
DECL|macro|LASI_700_SVERSION
mdefine_line|#define LASI_700_SVERSION&t;0x071
DECL|macro|LASI700_ID_TABLE
mdefine_line|#define LASI700_ID_TABLE {&t;&t;&t;&bslash;&n;&t;hw_type:&t;HPHW_FIO,&t;&t;&bslash;&n;&t;sversion:&t;LASI_700_SVERSION,&t;&bslash;&n;&t;hversion:&t;HVERSION_ANY_ID,&t;&bslash;&n;&t;hversion_rev:&t;HVERSION_REV_ANY_ID,&t;&bslash;&n;}
DECL|macro|LASI710_ID_TABLE
mdefine_line|#define LASI710_ID_TABLE {&t;&t;&t;&bslash;&n;&t;hw_type:&t;HPHW_FIO,&t;&t;&bslash;&n;&t;sversion:&t;LASI_710_SVERSION,&t;&bslash;&n;&t;hversion:&t;HVERSION_ANY_ID,&t;&bslash;&n;&t;hversion_rev:&t;HVERSION_REV_ANY_ID,&t;&bslash;&n;}
DECL|macro|LASI700_DRIVER
mdefine_line|#define LASI700_DRIVER {&t;&t;&t;&bslash;&n;&t;name:&t;&t;&quot;Lasi SCSI&quot;,&t;&t;&bslash;&n;&t;id_table:&t;lasi700_scsi_tbl,&t;&bslash;&n;&t;probe:&t;&t;lasi700_driver_callback,&bslash;&n;}
DECL|macro|LASI700_CLOCK
mdefine_line|#define LASI700_CLOCK&t;25
DECL|macro|LASI710_CLOCK
mdefine_line|#define LASI710_CLOCK&t;40
DECL|macro|LASI_SCSI_CORE_OFFSET
mdefine_line|#define LASI_SCSI_CORE_OFFSET 0x100
macro_line|#endif
eof
