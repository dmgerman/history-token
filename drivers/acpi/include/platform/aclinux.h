multiline_comment|/******************************************************************************&n; *&n; * Name: aclinux.h - OS specific defines, etc.&n; *       $Revision: 14 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACLINUX_H__
DECL|macro|__ACLINUX_H__
mdefine_line|#define __ACLINUX_H__
DECL|macro|ACPI_OS_NAME
mdefine_line|#define ACPI_OS_NAME                &quot;Linux&quot;
DECL|macro|ACPI_USE_SYSTEM_CLIBRARY
mdefine_line|#define ACPI_USE_SYSTEM_CLIBRARY
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
DECL|macro|strtoul
mdefine_line|#define strtoul simple_strtoul
macro_line|#else
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;ctype.h&gt;
macro_line|#endif
multiline_comment|/* Linux uses GCC */
macro_line|#include &quot;acgcc.h&quot;
DECL|macro|DEBUGGER_THREADING
macro_line|#undef DEBUGGER_THREADING
DECL|macro|DEBUGGER_THREADING
mdefine_line|#define DEBUGGER_THREADING          DEBUGGER_SINGLE_THREADED
macro_line|#endif /* __ACLINUX_H__ */
eof
