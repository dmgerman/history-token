macro_line|#ifndef _SPARC_BUG_H
DECL|macro|_SPARC_BUG_H
mdefine_line|#define _SPARC_BUG_H
multiline_comment|/* Only use the inline asm until a gcc release that can handle __builtin_trap&n; * -rob 2003-06-25&n; *&n; * gcc-3.3.1 and later will be OK -DaveM&n; */
macro_line|#if (__GNUC__ &gt; 3) || &bslash;&n;    (__GNUC__ == 3 &amp;&amp; __GNUC_MINOR__ &gt; 3) || &bslash;&n;    (__GNUC__ == 3 &amp;&amp; __GNUC_MINOR__ == 3 &amp;&amp; __GNUC_PATCHLEVEL__ &gt;= 4)
DECL|macro|__bug_trap
mdefine_line|#define __bug_trap()&t;&t;__builtin_trap()
macro_line|#else
DECL|macro|__bug_trap
mdefine_line|#define __bug_trap()&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&quot;t 0x5&bslash;n&bslash;t&quot; : : )
macro_line|#endif
macro_line|#ifdef CONFIG_DEBUG_BUGVERBOSE
r_extern
r_void
id|do_BUG
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
)paren
suffix:semicolon
DECL|macro|BUG
mdefine_line|#define BUG() do {&t;&t;&t;&t;&t;&bslash;&n;&t;do_BUG(__FILE__, __LINE__);&t;&t;&t;&bslash;&n;&t;__bug_trap();&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else
DECL|macro|BUG
mdefine_line|#define BUG()&t;&t;__bug_trap()
macro_line|#endif
DECL|macro|HAVE_ARCH_BUG
mdefine_line|#define HAVE_ARCH_BUG
macro_line|#include &lt;asm-generic/bug.h&gt;
macro_line|#endif
eof
