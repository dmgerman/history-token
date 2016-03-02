multiline_comment|/******************************************************************************&n; *&n; * Name: acpi.h - Master include file, Publics and external data.&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
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
