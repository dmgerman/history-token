multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997, 98, 99, 2000, 2003 Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_CACHE_H
DECL|macro|_ASM_CACHE_H
mdefine_line|#define _ASM_CACHE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_CPU_R3000) || defined(CONFIG_CPU_R6000) || &bslash;&n;    defined(CONFIG_CPU_TX39XX)
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;&t;16
DECL|macro|L1_CACHE_SHIFT_MAX
mdefine_line|#define L1_CACHE_SHIFT_MAX&t; 4&t;/* largest L1 which this arch supports */
macro_line|#else
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES &t;&t;32&t;/* A guess */
DECL|macro|L1_CACHE_SHIFT_MAX
mdefine_line|#define L1_CACHE_SHIFT_MAX&t; 6&t;/* largest L1 which this arch supports */
macro_line|#endif
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define SMP_CACHE_BYTES&t;&t;L1_CACHE_BYTES
macro_line|#endif /* _ASM_CACHE_H */
eof
