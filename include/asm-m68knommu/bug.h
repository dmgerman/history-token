macro_line|#ifndef _M68KNOMMU_BUG_H
DECL|macro|_M68KNOMMU_BUG_H
mdefine_line|#define _M68KNOMMU_BUG_H
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;  printk(&quot;%s(%d): kernel BUG!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;} while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { &bslash;&n;         BUG(); &bslash;&n;} while (0)
macro_line|#endif
eof
