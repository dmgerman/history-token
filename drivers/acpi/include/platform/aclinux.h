multiline_comment|/******************************************************************************&n; *&n; * Name: aclinux.h - OS specific defines, etc.&n; *       $Revision: 25 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
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
macro_line|#include &lt;asm/acpi.h&gt;
DECL|macro|strtoul
mdefine_line|#define strtoul simple_strtoul
DECL|macro|ACPI_MACHINE_WIDTH
mdefine_line|#define ACPI_MACHINE_WIDTH&t;BITS_PER_LONG
macro_line|#else /* !__KERNEL__ */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;ctype.h&gt;
macro_line|#if defined(__ia64__) || defined(__x86_64__)
DECL|macro|ACPI_MACHINE_WIDTH
mdefine_line|#define ACPI_MACHINE_WIDTH&t;&t;64
DECL|macro|COMPILER_DEPENDENT_INT64
mdefine_line|#define COMPILER_DEPENDENT_INT64&t;long
DECL|macro|COMPILER_DEPENDENT_UINT64
mdefine_line|#define COMPILER_DEPENDENT_UINT64&t;unsigned long
macro_line|#else
DECL|macro|ACPI_MACHINE_WIDTH
mdefine_line|#define ACPI_MACHINE_WIDTH&t;&t;32
DECL|macro|COMPILER_DEPENDENT_INT64
mdefine_line|#define COMPILER_DEPENDENT_INT64&t;long long
DECL|macro|COMPILER_DEPENDENT_UINT64
mdefine_line|#define COMPILER_DEPENDENT_UINT64&t;unsigned long long
DECL|macro|ACPI_USE_NATIVE_DIVIDE
mdefine_line|#define ACPI_USE_NATIVE_DIVIDE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* Linux uses GCC */
macro_line|#include &quot;acgcc.h&quot;
DECL|macro|DEBUGGER_THREADING
macro_line|#undef DEBUGGER_THREADING
DECL|macro|DEBUGGER_THREADING
mdefine_line|#define DEBUGGER_THREADING&t;DEBUGGER_SINGLE_THREADED
macro_line|#endif /* __ACLINUX_H__ */
eof
