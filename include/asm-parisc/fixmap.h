macro_line|#ifndef _ASM_FIXMAP_H
DECL|macro|_ASM_FIXMAP_H
mdefine_line|#define _ASM_FIXMAP_H
multiline_comment|/*&n; * This file defines the locations of the fixed mappings on parisc.&n; *&n; * All of the values in this file are machine virtual addresses.&n; *&n; * All of the values in this file must be &lt;4GB (because of assembly&n; * loading restrictions).  If you place this region anywhere above&n; * __PAGE_OFFSET, you must adjust the memory map accordingly */
multiline_comment|/* The alias region is used in kernel space to do copy/clear to or&n; * from areas congruently mapped with user space.  It is 8MB large&n; * and must be 16MB aligned */
DECL|macro|TMPALIAS_MAP_START
mdefine_line|#define TMPALIAS_MAP_START&t;((__PAGE_OFFSET) - 16*1024*1024)
multiline_comment|/* This is the kernel area for all maps (vmalloc, dma etc.)  most&n; * usually, it extends up to TMPALIAS_MAP_START.  Virtual addresses&n; * 0..GATEWAY_PAGE_SIZE are reserved for the gateway page */
DECL|macro|KERNEL_MAP_START
mdefine_line|#define KERNEL_MAP_START&t;(GATEWAY_PAGE_SIZE)
DECL|macro|KERNEL_MAP_END
mdefine_line|#define KERNEL_MAP_END&t;&t;(TMPALIAS_MAP_START)
macro_line|#endif
eof
