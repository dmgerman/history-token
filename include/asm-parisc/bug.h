macro_line|#ifndef _PARISC_BUG_H
DECL|macro|_PARISC_BUG_H
mdefine_line|#define _PARISC_BUG_H
multiline_comment|/*&n; * Tell the user there is some problem.&n; */
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;} while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { &bslash;&n;&t;BUG(); &bslash;&n;} while (0)
macro_line|#endif
eof
