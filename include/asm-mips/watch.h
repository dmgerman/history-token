multiline_comment|/* $Id: watch.h,v 1.3 1998/08/19 21:58:15 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997, 1998 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_WATCH_H
DECL|macro|__ASM_WATCH_H
mdefine_line|#define __ASM_WATCH_H
macro_line|#include &lt;linux/linkage.h&gt;
multiline_comment|/*&n; * Types of reference for watch_set()&n; */
DECL|enum|wref_type
r_enum
id|wref_type
(brace
DECL|enumerator|wr_save
id|wr_save
op_assign
l_int|1
comma
DECL|enumerator|wr_load
id|wr_load
op_assign
l_int|2
)brace
suffix:semicolon
r_extern
r_char
id|watch_available
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|__watch_set
c_func
(paren
r_int
r_int
id|addr
comma
r_enum
id|wref_type
id|ref
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|__watch_clear
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|__watch_reenable
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|watch_set
mdefine_line|#define watch_set(addr, ref)&t;&t;&t;&t;&t;&bslash;&n;&t;if (watch_available)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__watch_set(addr, ref)
DECL|macro|watch_clear
mdefine_line|#define watch_clear()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (watch_available)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__watch_clear()
DECL|macro|watch_reenable
mdefine_line|#define watch_reenable()&t;&t;&t;&t;&t;&bslash;&n;&t;if (watch_available)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;__watch_reenable()
macro_line|#endif __ASM_WATCH_H
eof
