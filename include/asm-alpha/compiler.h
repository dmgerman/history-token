macro_line|#ifndef __ALPHA_COMPILER_H
DECL|macro|__ALPHA_COMPILER_H
mdefine_line|#define __ALPHA_COMPILER_H
multiline_comment|/* &n; * Herein are macros we use when describing various patterns we want to GCC.&n; * In all cases we can get better schedules out of the compiler if we hide&n; * as little as possible inside inline assembly.  However, we want to be&n; * able to know what we&squot;ll get out before giving up inline assembly.  Thus&n; * these tests and macros.&n; */
macro_line|#if 0
mdefine_line|#define __kernel_insbl(val, shift) &bslash;&n;  (((unsigned long)(val) &amp; 0xfful) &lt;&lt; ((shift) * 8))
mdefine_line|#define __kernel_inswl(val, shift) &bslash;&n;  (((unsigned long)(val) &amp; 0xfffful) &lt;&lt; ((shift) * 8))
mdefine_line|#define __kernel_insql(val, shift) &bslash;&n;  ((unsigned long)(val) &lt;&lt; ((shift) * 8))
macro_line|#else
DECL|macro|__kernel_insbl
mdefine_line|#define __kernel_insbl(val, shift)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;insbl %2,%1,%0&quot; : &quot;=r&quot;(__kir) : &quot;rI&quot;(shift), &quot;r&quot;(val));&t;&bslash;&n;     __kir; })
DECL|macro|__kernel_inswl
mdefine_line|#define __kernel_inswl(val, shift)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;inswl %2,%1,%0&quot; : &quot;=r&quot;(__kir) : &quot;rI&quot;(shift), &quot;r&quot;(val));&t;&bslash;&n;     __kir; })
DECL|macro|__kernel_insql
mdefine_line|#define __kernel_insql(val, shift)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;insql %2,%1,%0&quot; : &quot;=r&quot;(__kir) : &quot;rI&quot;(shift), &quot;r&quot;(val));&t;&bslash;&n;     __kir; })
macro_line|#endif
macro_line|#if 0 &amp;&amp; (__GNUC__ &gt; 2 || __GNUC_MINOR__ &gt;= 92)
mdefine_line|#define __kernel_extbl(val, shift)  (((val) &gt;&gt; (((shift) &amp; 7) * 8)) &amp; 0xfful)
mdefine_line|#define __kernel_extwl(val, shift)  (((val) &gt;&gt; (((shift) &amp; 7) * 8)) &amp; 0xfffful)
macro_line|#else
DECL|macro|__kernel_extbl
mdefine_line|#define __kernel_extbl(val, shift)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;extbl %2,%1,%0&quot; : &quot;=r&quot;(__kir) : &quot;rI&quot;(shift), &quot;r&quot;(val));&t;&bslash;&n;     __kir; })
DECL|macro|__kernel_extwl
mdefine_line|#define __kernel_extwl(val, shift)&t;&t;&t;&t;&t;&bslash;&n;  ({ unsigned long __kir;&t;&t;&t;&t;&t;&t;&bslash;&n;     __asm__(&quot;extwl %2,%1,%0&quot; : &quot;=r&quot;(__kir) : &quot;rI&quot;(shift), &quot;r&quot;(val));&t;&bslash;&n;     __kir; })
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
multiline_comment|/* Somewhere in the middle of the GCC 2.96 development cycle, we implemented&n;   a mechanism by which the user can annotate likely branch directions and&n;   expect the blocks to be reordered appropriately.  Define __builtin_expect&n;   to nothing for earlier compilers.  */
macro_line|#if __GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 96
DECL|macro|__builtin_expect
mdefine_line|#define __builtin_expect(x, expected_value) (x)
macro_line|#endif
macro_line|#endif /* __ALPHA_COMPILER_H */
eof
