macro_line|#ifndef M68K_PGALLOC_H
DECL|macro|M68K_PGALLOC_H
mdefine_line|#define M68K_PGALLOC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/virtconvert.h&gt;
macro_line|#ifdef CONFIG_SUN3
macro_line|#include &lt;asm/sun3_pgalloc.h&gt;
macro_line|#else
macro_line|#include &lt;asm/motorola_pgalloc.h&gt;
macro_line|#endif
macro_line|#endif /* M68K_PGALLOC_H */
eof
