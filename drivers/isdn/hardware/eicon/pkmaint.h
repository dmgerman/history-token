multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef __DIVA_XDI_OS_DEPENDENT_PACK_MAIN_ON_BYTE_INC__
DECL|macro|__DIVA_XDI_OS_DEPENDENT_PACK_MAIN_ON_BYTE_INC__
mdefine_line|#define __DIVA_XDI_OS_DEPENDENT_PACK_MAIN_ON_BYTE_INC__
multiline_comment|/*&n;&t;Only one purpose of this compiler dependent file to pack&n;&t;structures, described in pc_maint.h so that no padding&n;&t;will be included.&n;&n;&t;With microsoft compile it is done by &quot;pshpack1.h&quot; and&n;&t;after is restored by &quot;poppack.h&quot;&n;&t;*/
macro_line|#include &quot;pc_maint.h&quot;
macro_line|#endif
eof
