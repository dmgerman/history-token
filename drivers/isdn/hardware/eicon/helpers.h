multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef __DIVA_XDI_CARD_CONFIG_HELPERS_INC__
DECL|macro|__DIVA_XDI_CARD_CONFIG_HELPERS_INC__
mdefine_line|#define __DIVA_XDI_CARD_CONFIG_HELPERS_INC__
id|dword
id|diva_get_protocol_file_features
(paren
id|byte
op_star
id|File
comma
r_int
id|offset
comma
r_char
op_star
id|IdStringBuffer
comma
id|dword
id|IdBufferSize
)paren
suffix:semicolon
r_void
id|diva_configure_protocol
(paren
id|PISDN_ADAPTER
id|IoAdapter
)paren
suffix:semicolon
multiline_comment|/*&n; Low level file access system abstraction&n; */
multiline_comment|/* -------------------------------------------------------------------------&n;  Access to single file&n;  Return pointer to the image of the requested file,&n;  write image length to &squot;FileLength&squot;&n;  ------------------------------------------------------------------------- */
r_void
op_star
id|xdiLoadFile
(paren
r_char
op_star
id|FileName
comma
id|dword
op_star
id|FileLength
comma
r_int
r_int
id|MaxLoadSize
)paren
suffix:semicolon
multiline_comment|/* -------------------------------------------------------------------------&n;  Dependent on the protocol settings does read return pointer&n;  to the image of appropriate protocol file&n;  ------------------------------------------------------------------------- */
r_void
op_star
id|xdiLoadArchive
(paren
id|PISDN_ADAPTER
id|IoAdapter
comma
id|dword
op_star
id|FileLength
comma
r_int
r_int
id|MaxLoadSize
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;  Free all system resources accessed by xdiLoadFile and xdiLoadArchive&n;  -------------------------------------------------------------------------- */
r_void
id|xdiFreeFile
(paren
r_void
op_star
id|handle
)paren
suffix:semicolon
macro_line|#endif
eof
