multiline_comment|/*&n; *  Generic cache management functions. Everything is arch-specific,  &n; *  but this header exists to make sure the defines/functions can be&n; *  used in a generic way.&n; *&n; *  2000-11-13  Arjan van de Ven   &lt;arjan@fenrus.demon.nl&gt;&n; *&n; */
macro_line|#ifndef _LINUX_PREFETCH_H
DECL|macro|_LINUX_PREFETCH_H
mdefine_line|#define _LINUX_PREFETCH_H
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
multiline_comment|/*&n;&t;prefetch(x) attempts to pre-emptively get the memory pointed to&n;&t;by address &quot;x&quot; into the CPU L1 cache. &n;&t;prefetch(x) should not cause any kind of exception, prefetch(0) is&n;&t;specifically ok.&n;&n;&t;prefetch() should be defined by the architecture, if not, the &n;&t;#define below provides a no-op define.&t;&n;&t;&n;&t;There are 3 prefetch() macros:&n;&t;&n;&t;prefetch(x)  &t;- prefetches the cacheline at &quot;x&quot; for read&n;&t;prefetchw(x)&t;- prefetches the cacheline at &quot;x&quot; for write&n;&t;spin_lock_prefetch(x) - prefectches the spinlock *x for taking&n;&t;&n;&t;there is also PREFETCH_STRIDE which is the architecure-prefered &n;&t;&quot;lookahead&quot; size for prefetching streamed operations.&n;&t;&n;*/
multiline_comment|/*&n; *&t;These cannot be do{}while(0) macros. See the mental gymnastics in&n; *&t;the loop macro.&n; */
macro_line|#ifndef ARCH_HAS_PREFETCH
DECL|macro|ARCH_HAS_PREFETCH
mdefine_line|#define ARCH_HAS_PREFETCH
DECL|function|prefetch
r_static
r_inline
r_void
id|prefetch
c_func
(paren
r_const
r_void
op_star
id|x
)paren
(brace
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef ARCH_HAS_PREFETCHW
DECL|macro|ARCH_HAS_PREFETCHW
mdefine_line|#define ARCH_HAS_PREFETCHW
DECL|function|prefetchw
r_static
r_inline
r_void
id|prefetchw
c_func
(paren
r_const
r_void
op_star
id|x
)paren
(brace
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef ARCH_HAS_SPINLOCK_PREFETCH
DECL|macro|ARCH_HAS_SPINLOCK_PREFETCH
mdefine_line|#define ARCH_HAS_SPINLOCK_PREFETCH
DECL|macro|spin_lock_prefetch
mdefine_line|#define spin_lock_prefetch(x) prefetchw(x)
macro_line|#endif
macro_line|#ifndef PREFETCH_STRIDE
DECL|macro|PREFETCH_STRIDE
mdefine_line|#define PREFETCH_STRIDE (4*L1_CACHE_BYTE)
macro_line|#endif
macro_line|#endif
eof
