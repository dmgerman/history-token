multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Ralf Baechle&n; * Copyright (C) 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SGI_IO_H
DECL|macro|_ASM_SGI_IO_H
mdefine_line|#define _ASM_SGI_IO_H
macro_line|#include &lt;asm/addrspace.h&gt;
DECL|macro|IO_SPACE_BASE
mdefine_line|#define IO_SPACE_BASE K1BASE
multiline_comment|/* For Indigo2.  */
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff
multiline_comment|/* XXX ISA specific functions go here here.  */
macro_line|#endif /* _ASM_SGI_IO_H */
eof
