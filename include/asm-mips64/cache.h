multiline_comment|/* $Id: cache.h,v 1.3 2000/02/04 07:40:53 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997, 1998, 1999 Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_CACHE_H
DECL|macro|_ASM_CACHE_H
mdefine_line|#define _ASM_CACHE_H
multiline_comment|/* bytes per L1 cache line */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;&t;32&t;/* A guess */
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define SMP_CACHE_BYTES&t;&t;L1_CACHE_BYTES
macro_line|#endif /* _ASM_CACHE_H */
eof
