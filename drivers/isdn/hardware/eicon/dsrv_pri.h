multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef __DIVA_XDI_DSRV_PRI_INC__
DECL|macro|__DIVA_XDI_DSRV_PRI_INC__
mdefine_line|#define __DIVA_XDI_DSRV_PRI_INC__
multiline_comment|/*&n; Functions exported from os dependent part of&n; PRI card configuration and used in&n; OS independed part&n; */
multiline_comment|/*&n; Prepare OS dependent part of PRI/PRI Rev.2 functions&n; */
r_void
id|diva_os_prepare_pri_functions
(paren
id|PISDN_ADAPTER
id|IoAdapter
)paren
suffix:semicolon
r_void
id|diva_os_prepare_pri2_functions
(paren
id|PISDN_ADAPTER
id|IoAdapter
)paren
suffix:semicolon
macro_line|#endif
eof
