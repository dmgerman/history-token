multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998, 1999 Ralf Baechle&n; */
macro_line|#ifndef _ASM_INIT_H
DECL|macro|_ASM_INIT_H
mdefine_line|#define _ASM_INIT_H
DECL|macro|__init
mdefine_line|#define __init __attribute__ ((__section__ (&quot;.text.init&quot;)))
DECL|macro|__initdata
mdefine_line|#define __initdata __attribute__ ((__section__ (&quot;.data.init&quot;)))
DECL|macro|__initfunc
mdefine_line|#define __initfunc(__arginit) &bslash;&n;&t;__arginit __init; &bslash;&n;&t;__arginit
multiline_comment|/* For assembly routines */
DECL|macro|__INIT
mdefine_line|#define __INIT&t;&t;.section&t;.text.init,&quot;ax&quot;
DECL|macro|__FINIT
mdefine_line|#define __FINIT&t;&t;.previous
DECL|macro|__INITDATA
mdefine_line|#define __INITDATA&t;.section&t;.data.init,&quot;a&quot;
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned __attribute__((__aligned__(L1_CACHE_BYTES)))
macro_line|#endif /* _ASM_INIT_H */
eof
