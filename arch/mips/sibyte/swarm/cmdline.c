multiline_comment|/*&n; * Copyright (C) 2000, 2001 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#include &lt;asm/bootinfo.h&gt;
multiline_comment|/*&n; * The naming of this variable is a remnant of the initial mips port to&n; * ARC-firmware based SGI consoles.  We don&squot;t really need to do anything for&n; * the variable other than provide an instantiation.  Everything about&n; * arcs_cmdline seems more than a little bit hackish...&n; */
DECL|variable|arcs_cmdline
r_char
id|arcs_cmdline
(braket
id|CL_SIZE
)braket
suffix:semicolon
eof
