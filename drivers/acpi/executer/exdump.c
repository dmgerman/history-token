multiline_comment|/******************************************************************************&n; *&n; * Module Name: exdump - Interpreter debug output routines&n; *              $Revision: 114 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;actables.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|MODULE_NAME
(paren
l_string|&quot;exdump&quot;
)paren
multiline_comment|/*&n; * The following routines are used for debug output only&n; */
eof
