macro_line|#ifndef _ASM_IA64_AGP_H
DECL|macro|_ASM_IA64_AGP_H
mdefine_line|#define _ASM_IA64_AGP_H
multiline_comment|/*&n; * IA-64 specific AGP definitions.&n; *&n; * Copyright (C) 2002-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
multiline_comment|/*&n; * To avoid memory-attribute aliasing issues, we require that the AGPGART engine operate&n; * in coherent mode, which lets us map the AGP memory as normal (write-back) memory&n; * (unlike x86, where it gets mapped &quot;write-coalescing&quot;).&n; */
DECL|macro|map_page_into_agp
mdefine_line|#define map_page_into_agp(page)&t;&t;/* nothing */
DECL|macro|unmap_page_from_agp
mdefine_line|#define unmap_page_from_agp(page)&t;/* nothing */
DECL|macro|flush_agp_mappings
mdefine_line|#define flush_agp_mappings()&t;&t;/* nothing */
DECL|macro|flush_agp_cache
mdefine_line|#define flush_agp_cache()&t;&t;mb()
macro_line|#endif /* _ASM_IA64_AGP_H */
eof
