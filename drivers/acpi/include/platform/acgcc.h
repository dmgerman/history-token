multiline_comment|/******************************************************************************&n; *&n; * Name: acgcc.h - GCC specific defines, etc.&n; *       $Revision: 23 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACGCC_H__
DECL|macro|__ACGCC_H__
mdefine_line|#define __ACGCC_H__
multiline_comment|/* This macro is used to tag functions as &quot;printf-like&quot; because&n; * some compilers (like GCC) can catch printf format string problems.&n; */
DECL|macro|ACPI_PRINTF_LIKE_FUNC
mdefine_line|#define ACPI_PRINTF_LIKE_FUNC __attribute__ ((__format__ (__printf__, 4, 5)))
macro_line|#endif /* __ACGCC_H__ */
eof
