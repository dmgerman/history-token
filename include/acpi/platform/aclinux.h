multiline_comment|/******************************************************************************&n; *&n; * Name: aclinux.h - OS specific defines, etc.&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACLINUX_H__
DECL|macro|__ACLINUX_H__
mdefine_line|#define __ACLINUX_H__
DECL|macro|ACPI_USE_SYSTEM_CLIBRARY
mdefine_line|#define ACPI_USE_SYSTEM_CLIBRARY
DECL|macro|ACPI_USE_DO_WHILE_0
mdefine_line|#define ACPI_USE_DO_WHILE_0
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
mdefine_line|#define ACPI_MACHINE_WIDTH  BITS_PER_LONG
macro_line|#else /* !__KERNEL__ */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#if defined(__ia64__) || defined(__x86_64__)
DECL|macro|ACPI_MACHINE_WIDTH
mdefine_line|#define ACPI_MACHINE_WIDTH          64
DECL|macro|COMPILER_DEPENDENT_INT64
mdefine_line|#define COMPILER_DEPENDENT_INT64    long
DECL|macro|COMPILER_DEPENDENT_UINT64
mdefine_line|#define COMPILER_DEPENDENT_UINT64   unsigned long
macro_line|#else
DECL|macro|ACPI_MACHINE_WIDTH
mdefine_line|#define ACPI_MACHINE_WIDTH          32
DECL|macro|COMPILER_DEPENDENT_INT64
mdefine_line|#define COMPILER_DEPENDENT_INT64    long long
DECL|macro|COMPILER_DEPENDENT_UINT64
mdefine_line|#define COMPILER_DEPENDENT_UINT64   unsigned long long
DECL|macro|ACPI_USE_NATIVE_DIVIDE
mdefine_line|#define ACPI_USE_NATIVE_DIVIDE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
multiline_comment|/* Linux uses GCC */
macro_line|#include &quot;acgcc.h&quot;
macro_line|#endif /* __ACLINUX_H__ */
eof
