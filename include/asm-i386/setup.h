multiline_comment|/*&n; *&t;Just a place holder. We don&squot;t want to have to test x86 before&n; *&t;we include stuff&n; */
macro_line|#ifndef _i386_SETUP_H
DECL|macro|_i386_SETUP_H
mdefine_line|#define _i386_SETUP_H
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x)&t;(((x) + PAGE_SIZE-1) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_DOWN
mdefine_line|#define PFN_DOWN(x)&t;((x) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_PHYS
mdefine_line|#define PFN_PHYS(x)&t;((x) &lt;&lt; PAGE_SHIFT)
multiline_comment|/*&n; * Reserved space for vmalloc and iomap - defined in asm/page.h&n; */
DECL|macro|MAXMEM_PFN
mdefine_line|#define MAXMEM_PFN&t;PFN_DOWN(MAXMEM)
DECL|macro|MAX_NONPAE_PFN
mdefine_line|#define MAX_NONPAE_PFN&t;(1 &lt;&lt; 20)
macro_line|#endif /* _i386_SETUP_H */
eof
