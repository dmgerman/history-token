macro_line|#ifndef _ALPHA_BUG_H
DECL|macro|_ALPHA_BUG_H
mdefine_line|#define _ALPHA_BUG_H
macro_line|#include &lt;asm/pal.h&gt;
multiline_comment|/* ??? Would be nice to use .gprel32 here, but we can&squot;t be sure that the&n;   function loaded the GP, so this could fail in modules.  */
DECL|macro|BUG
mdefine_line|#define BUG() &bslash;&n;  __asm__ __volatile__(&quot;call_pal %0  # bugchk&bslash;n&bslash;t&quot;&quot;.long %1&bslash;n&bslash;t.8byte %2&quot; &bslash;&n;&t;&t;       : : &quot;i&quot; (PAL_bugchk), &quot;i&quot;(__LINE__), &quot;i&quot;(__FILE__))
DECL|macro|BUG_ON
mdefine_line|#define BUG_ON(condition) do { if (unlikely((condition)!=0)) BUG(); } while(0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page)&t;BUG()
DECL|macro|WARN_ON
mdefine_line|#define WARN_ON(condition) do { &bslash;&n;&t;if (unlikely((condition)!=0)) { &bslash;&n;&t;&t;printk(&quot;Badness in %s at %s:%d&bslash;n&quot;, __FUNCTION__, __FILE__, __LINE__); &bslash;&n;&t;&t;dump_stack(); &bslash;&n;&t;} &bslash;&n;} while (0)
macro_line|#endif
eof
