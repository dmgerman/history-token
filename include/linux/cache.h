macro_line|#ifndef __LINUX_CACHE_H
DECL|macro|__LINUX_CACHE_H
mdefine_line|#define __LINUX_CACHE_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#ifndef L1_CACHE_ALIGN
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define L1_CACHE_ALIGN(x) ALIGN(x, L1_CACHE_BYTES)
macro_line|#endif
macro_line|#ifndef SMP_CACHE_BYTES
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define SMP_CACHE_BYTES L1_CACHE_BYTES
macro_line|#endif
macro_line|#ifndef ____cacheline_aligned
DECL|macro|____cacheline_aligned
mdefine_line|#define ____cacheline_aligned __attribute__((__aligned__(SMP_CACHE_BYTES)))
macro_line|#endif
macro_line|#ifndef ____cacheline_aligned_in_smp
macro_line|#ifdef CONFIG_SMP
DECL|macro|____cacheline_aligned_in_smp
mdefine_line|#define ____cacheline_aligned_in_smp ____cacheline_aligned
macro_line|#else
DECL|macro|____cacheline_aligned_in_smp
mdefine_line|#define ____cacheline_aligned_in_smp
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif
macro_line|#ifndef __cacheline_aligned
macro_line|#ifdef MODULE
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned ____cacheline_aligned
macro_line|#else
DECL|macro|__cacheline_aligned
mdefine_line|#define __cacheline_aligned&t;&t;&t;&t;&t;&bslash;&n;  __attribute__((__aligned__(SMP_CACHE_BYTES),&t;&t;&t;&bslash;&n;&t;&t; __section__(&quot;.data.cacheline_aligned&quot;)))
macro_line|#endif
macro_line|#endif /* __cacheline_aligned */
macro_line|#ifndef __cacheline_aligned_in_smp
macro_line|#ifdef CONFIG_SMP
DECL|macro|__cacheline_aligned_in_smp
mdefine_line|#define __cacheline_aligned_in_smp __cacheline_aligned
macro_line|#else
DECL|macro|__cacheline_aligned_in_smp
mdefine_line|#define __cacheline_aligned_in_smp
macro_line|#endif /* CONFIG_SMP */
macro_line|#endif
macro_line|#if !defined(____cacheline_maxaligned_in_smp)
macro_line|#if defined(CONFIG_SMP)
DECL|macro|____cacheline_maxaligned_in_smp
mdefine_line|#define ____cacheline_maxaligned_in_smp &bslash;&n;&t;__attribute__((__aligned__(1 &lt;&lt; (L1_CACHE_SHIFT_MAX))))
macro_line|#else
DECL|macro|____cacheline_maxaligned_in_smp
mdefine_line|#define ____cacheline_maxaligned_in_smp
macro_line|#endif
macro_line|#endif
macro_line|#endif /* __LINUX_CACHE_H */
eof
