macro_line|#ifndef __ALPHA_COMPILER_H
DECL|macro|__ALPHA_COMPILER_H
mdefine_line|#define __ALPHA_COMPILER_H
multiline_comment|/* &n; * Herein are macros we use when describing various patterns we want to GCC.&n; * In all cases we can get better schedules out of the compiler if we hide&n; * as little as possible inside inline assembly.  However, we want to be&n; * able to know what we&squot;ll get out before giving up inline assembly.  Thus&n; * these tests and macros.&n; */
macro_line|#if __GNUC__ == 3 &amp;&amp; __GNUC_MINOR__ &gt;= 4 || __GNUC__ &gt; 3
DECL|macro|__kernel_insbl
macro_line|# define __kernel_insbl(val, shift)&t;__builtin_alpha_insbl(val, shift)
DECL|macro|__kernel_inswl
macro_line|# define __kernel_inswl(val, shift)&t;__builtin_alpha_inswl(val, shift)
DECL|macro|__kernel_insql
macro_line|# define __kernel_insql(val, shift)&t;__builtin_alpha_insql(val, shift)
DECL|macro|__kernel_inslh
macro_line|# define __kernel_inslh(val, shift)&t;__builtin_alpha_inslh(val, shift)
DECL|macro|__kernel_extbl
macro_line|# define __kernel_extbl(val, shift)&t;__builtin_alpha_extbl(val, shift)
DECL|macro|__kernel_extwl
macro_line|# define __kernel_extwl(val, shift)&t;__builtin_alpha_extwl(val, shift)
DECL|macro|__kernel_cmpbge
macro_line|# define __kernel_cmpbge(a, b)&t;&t;__builtin_alpha_cmpbge(a, b)
DECL|macro|__kernel_cttz
macro_line|# define __kernel_cttz(x)&t;&t;__builtin_ctzl(x)
DECL|macro|__kernel_ctlz
macro_line|# define __kernel_ctlz(x)&t;&t;__builtin_clzl(x)
DECL|macro|__kernel_ctpop
macro_line|# define __kernel_ctpop(x)&t;&t;__builtin_popcountl(x)
macro_line|#else
DECL|macro|__kernel_insbl
macro_line|# define __kernel_insbl(val, shift)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;insbl %2,%1,%0&quot; : &quot;=r&quot;(__kir) : &quot;rI&quot;(shift), &quot;r&quot;(val));&t;&bslash;&n;     __kir; })
DECL|macro|__kernel_inswl
macro_line|# define __kernel_inswl(val, shift)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;inswl %2,%1,%0&quot; : &quot;=r&quot;(__kir) : &quot;rI&quot;(shift), &quot;r&quot;(val));&t;&bslash;&n;     __kir; })
DECL|macro|__kernel_insql
macro_line|# define __kernel_insql(val, shift)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;insql %2,%1,%0&quot; : &quot;=r&quot;(__kir) : &quot;rI&quot;(shift), &quot;r&quot;(val));&t;&bslash;&n;     __kir; })
DECL|macro|__kernel_inslh
macro_line|# define __kernel_inslh(val, shift)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;inslh %2,%1,%0&quot; : &quot;=r&quot;(__kir) : &quot;rI&quot;(shift), &quot;r&quot;(val));&t;&bslash;&n;     __kir; })
DECL|macro|__kernel_extbl
macro_line|# define __kernel_extbl(val, shift)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;extbl %2,%1,%0&quot; : &quot;=r&quot;(__kir) : &quot;rI&quot;(shift), &quot;r&quot;(val));&t;&bslash;&n;     __kir; })
DECL|macro|__kernel_extwl
macro_line|# define __kernel_extwl(val, shift)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;extwl %2,%1,%0&quot; : &quot;=r&quot;(__kir) : &quot;rI&quot;(shift), &quot;r&quot;(val));&t;&bslash;&n;     __kir; })
DECL|macro|__kernel_cmpbge
macro_line|# define __kernel_cmpbge(a, b)&t;&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;cmpbge %r2,%1,%0&quot; : &quot;=r&quot;(__kir) : &quot;rI&quot;(b), &quot;rJ&quot;(a));&t;&bslash;&n;     __kir; })
DECL|macro|__kernel_cttz
macro_line|# define __kernel_cttz(x)&t;&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;cttz %1,%0&quot; : &quot;=r&quot;(__kir) : &quot;r&quot;(x));&t;&t;&t;&bslash;&n;     __kir; })
DECL|macro|__kernel_ctlz
macro_line|# define __kernel_ctlz(x)&t;&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;ctlz %1,%0&quot; : &quot;=r&quot;(__kir) : &quot;r&quot;(x));&t;&t;&t;&bslash;&n;     __kir; })
DECL|macro|__kernel_ctpop
macro_line|# define __kernel_ctpop(x)&t;&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;ctpop %1,%0&quot; : &quot;=r&quot;(__kir) : &quot;r&quot;(x));&t;&t;&t;&bslash;&n;     __kir; })
macro_line|#endif
multiline_comment|/* &n; * Beginning with EGCS 1.1, GCC defines __alpha_bwx__ when the BWX &n; * extension is enabled.  Previous versions did not define anything&n; * we could test during compilation -- too bad, so sad.&n; */
macro_line|#if defined(__alpha_bwx__)
DECL|macro|__kernel_ldbu
mdefine_line|#define __kernel_ldbu(mem)&t;(mem)
DECL|macro|__kernel_ldwu
mdefine_line|#define __kernel_ldwu(mem)&t;(mem)
DECL|macro|__kernel_stb
mdefine_line|#define __kernel_stb(val,mem)&t;((mem) = (val))
DECL|macro|__kernel_stw
mdefine_line|#define __kernel_stw(val,mem)&t;((mem) = (val))
macro_line|#else
DECL|macro|__kernel_ldbu
mdefine_line|#define __kernel_ldbu(mem)&t;&t;&t;&t;&bslash;&n;  ({ unsigned char __kir;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;ldbu %0,%1&quot; : &quot;=r&quot;(__kir) : &quot;m&quot;(mem));&t;&bslash;&n;     __kir; })
DECL|macro|__kernel_ldwu
mdefine_line|#define __kernel_ldwu(mem)&t;&t;&t;&t;&bslash;&n;  ({ unsigned short __kir;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;ldwu %0,%1&quot; : &quot;=r&quot;(__kir) : &quot;m&quot;(mem));&t;&bslash;&n;     __kir; })
DECL|macro|__kernel_stb
mdefine_line|#define __kernel_stb(val,mem) &bslash;&n;  __asm__(&quot;stb %1,%0&quot; : &quot;=m&quot;(mem) : &quot;r&quot;(val))
DECL|macro|__kernel_stw
mdefine_line|#define __kernel_stw(val,mem) &bslash;&n;  __asm__(&quot;stw %1,%0&quot; : &quot;=m&quot;(mem) : &quot;r&quot;(val))
macro_line|#endif
multiline_comment|/* Some idiots over in &lt;linux/compiler.h&gt; thought inline should imply&n;   always_inline.  This breaks stuff.  We&squot;ll include this file whenever&n;   we run into such problems.  */
macro_line|#include &lt;linux/compiler.h&gt;
DECL|macro|inline
macro_line|#undef inline
DECL|macro|__inline__
macro_line|#undef __inline__
DECL|macro|__inline
macro_line|#undef __inline
macro_line|#endif /* __ALPHA_COMPILER_H */
eof
