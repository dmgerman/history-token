macro_line|#ifndef _M32R_BUG_H
DECL|macro|_M32R_BUG_H
mdefine_line|#define _M32R_BUG_H
DECL|macro|BUG
mdefine_line|#define BUG()&t;do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;} while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page)&t;do { BUG(); } while (0)
DECL|macro|BUG_ON
mdefine_line|#define BUG_ON(condition) &bslash;&n;&t;do { if (unlikely((condition)!=0)) BUG(); } while(0)
DECL|macro|WARN_ON
mdefine_line|#define WARN_ON(condition) do { &bslash;&n;&t;if (unlikely((condition)!=0)) { &bslash;&n;&t;&t;printk(&quot;Badness in %s at %s:%d&bslash;n&quot;, __FUNCTION__, &bslash;&n;&t;&t;__FILE__, __LINE__); &bslash;&n;&t;&t;dump_stack(); &bslash;&n;&t;} &bslash;&n;} while (0)
macro_line|#endif /* _M32R_BUG_H */
eof
