multiline_comment|/******************************************************************************&n; *&n; * Name: acpi.h - Master include file, Publics and external data.&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACPI_H__
DECL|macro|__ACPI_H__
mdefine_line|#define __ACPI_H__
multiline_comment|/*&n; * Common includes for all ACPI driver files&n; * We put them here because we don&squot;t want to duplicate them&n; * in the rest of the source code again and again.&n; */
macro_line|#include &quot;acconfig.h&quot;           /* Configuration constants */
macro_line|#include &quot;platform/acenv.h&quot;     /* Target environment specific items */
macro_line|#include &quot;actypes.h&quot;            /* Fundamental common data types */
macro_line|#include &quot;acexcep.h&quot;            /* ACPI exception codes */
macro_line|#include &quot;acmacros.h&quot;           /* C macros */
macro_line|#include &quot;actbl.h&quot;              /* ACPI table definitions */
macro_line|#include &quot;aclocal.h&quot;            /* Internal data types */
macro_line|#include &quot;acoutput.h&quot;           /* Error output and Debug macros */
macro_line|#include &quot;acpiosxf.h&quot;           /* Interfaces to the ACPI-to-OS layer*/
macro_line|#include &quot;acpixf.h&quot;             /* ACPI core subsystem external interfaces */
macro_line|#include &quot;acobject.h&quot;           /* ACPI internal object */
macro_line|#include &quot;acstruct.h&quot;           /* Common structures */
macro_line|#include &quot;acglobal.h&quot;           /* All global variables */
macro_line|#include &quot;achware.h&quot;            /* Hardware defines and interfaces */
macro_line|#include &quot;acutils.h&quot;            /* Utility interfaces */
macro_line|#endif /* __ACPI_H__ */
eof
