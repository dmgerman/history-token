macro_line|#ifndef __UM_HIGHMEM_H
DECL|macro|__UM_HIGHMEM_H
mdefine_line|#define __UM_HIGHMEM_H
macro_line|#include &quot;asm/page.h&quot;
macro_line|#include &quot;asm/fixmap.h&quot;
macro_line|#include &quot;asm/arch/highmem.h&quot;
DECL|macro|PKMAP_BASE
macro_line|#undef PKMAP_BASE
DECL|macro|PKMAP_BASE
mdefine_line|#define PKMAP_BASE ((FIXADDR_START - LAST_PKMAP * PAGE_SIZE) &amp; PMD_MASK)
macro_line|#endif
eof
