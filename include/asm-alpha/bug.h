macro_line|#ifndef _ALPHA_BUG_H
DECL|macro|_ALPHA_BUG_H
mdefine_line|#define _ALPHA_BUG_H
macro_line|#include &lt;asm/pal.h&gt;
multiline_comment|/* ??? Would be nice to use .gprel32 here, but we can&squot;t be sure that the&n;   function loaded the GP, so this could fail in modules.  */
DECL|macro|BUG
mdefine_line|#define BUG() &bslash;&n;  __asm__ __volatile__(&quot;call_pal %0  # bugchk&bslash;n&bslash;t&quot;&quot;.long %1&bslash;n&bslash;t.8byte %2&quot; &bslash;&n;&t;&t;       : : &quot;i&quot; (PAL_bugchk), &quot;i&quot;(__LINE__), &quot;i&quot;(__FILE__))
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page)&t;BUG()
macro_line|#endif
eof
