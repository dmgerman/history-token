multiline_comment|/*&n; * include/asm-alpha/cache.h&n; */
macro_line|#ifndef __ARCH_ALPHA_CACHE_H
DECL|macro|__ARCH_ALPHA_CACHE_H
mdefine_line|#define __ARCH_ALPHA_CACHE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Bytes per L1 (data) cache line. */
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_EV6) || defined(CONFIG_ALPHA_EV67)
DECL|macro|L1_CACHE_BYTES
macro_line|# define L1_CACHE_BYTES     64
DECL|macro|L1_CACHE_SHIFT
macro_line|# define L1_CACHE_SHIFT     6
macro_line|#else
multiline_comment|/* Both EV4 and EV5 are write-through, read-allocate,&n;   direct-mapped, physical.&n;*/
DECL|macro|L1_CACHE_BYTES
macro_line|# define L1_CACHE_BYTES     32
DECL|macro|L1_CACHE_SHIFT
macro_line|# define L1_CACHE_SHIFT     5
macro_line|#endif
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define L1_CACHE_ALIGN(x)  (((x)+(L1_CACHE_BYTES-1))&amp;~(L1_CACHE_BYTES-1))
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define SMP_CACHE_BYTES    L1_CACHE_BYTES
macro_line|#endif
eof
