multiline_comment|/*&n; * include/asm-i386/cache.h&n; */
macro_line|#ifndef __ARCH_I386_CACHE_H
DECL|macro|__ARCH_I386_CACHE_H
mdefine_line|#define __ARCH_I386_CACHE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* L1 cache line size */
DECL|macro|L1_CACHE_SHIFT
mdefine_line|#define L1_CACHE_SHIFT&t;(CONFIG_X86_L1_CACHE_SHIFT)
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;(1 &lt;&lt; L1_CACHE_SHIFT)
DECL|macro|L1_CACHE_SHIFT_MAX
mdefine_line|#define L1_CACHE_SHIFT_MAX 7&t;/* largest L1 which this arch supports */
macro_line|#endif
eof
