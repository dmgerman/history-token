multiline_comment|/******************************************************************************&n; *&n; * Name: acpi.h - Master include file, Publics and external data.&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2003, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACPI_H__
DECL|macro|__ACPI_H__
mdefine_line|#define __ACPI_H__
multiline_comment|/*&n; * Common includes for all ACPI driver files&n; * We put them here because we don&squot;t want to duplicate them&n; * in the rest of the source code again and again.&n; */
macro_line|#include &lt;acpi/acconfig.h&gt;           /* Configuration constants */
macro_line|#include &lt;acpi/platform/acenv.h&gt;     /* Target environment specific items */
macro_line|#include &lt;acpi/actypes.h&gt;            /* Fundamental common data types */
macro_line|#include &lt;acpi/acexcep.h&gt;            /* ACPI exception codes */
macro_line|#include &lt;acpi/acmacros.h&gt;           /* C macros */
macro_line|#include &lt;acpi/actbl.h&gt;              /* ACPI table definitions */
macro_line|#include &lt;acpi/aclocal.h&gt;            /* Internal data types */
macro_line|#include &lt;acpi/acoutput.h&gt;           /* Error output and Debug macros */
macro_line|#include &lt;acpi/acpiosxf.h&gt;           /* Interfaces to the ACPI-to-OS layer*/
macro_line|#include &lt;acpi/acpixf.h&gt;             /* ACPI core subsystem external interfaces */
macro_line|#include &lt;acpi/acobject.h&gt;           /* ACPI internal object */
macro_line|#include &lt;acpi/acstruct.h&gt;           /* Common structures */
macro_line|#include &lt;acpi/acglobal.h&gt;           /* All global variables */
macro_line|#include &lt;acpi/achware.h&gt;            /* Hardware defines and interfaces */
macro_line|#include &lt;acpi/acutils.h&gt;            /* Utility interfaces */
macro_line|#endif /* __ACPI_H__ */
eof
