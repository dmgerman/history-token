macro_line|#ifndef __UM_BUG_H
DECL|macro|__UM_BUG_H
mdefine_line|#define __UM_BUG_H
macro_line|#ifndef __ASSEMBLY__
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;panic(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;} while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { &bslash;&n;&t;BUG(); &bslash;&n;} while (0)
r_extern
r_int
id|foo
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
