multiline_comment|/*&n; *  linux/include/asm-arm/arch-ebsa285/vmalloc.h&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET&t;  (8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;  (((unsigned long)high_memory + VMALLOC_OFFSET) &amp; ~(VMALLOC_OFFSET-1))
macro_line|#ifdef CONFIG_ARCH_FOOTBRIDGE
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END       (PAGE_OFFSET + 0x30000000)
macro_line|#else
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END       (PAGE_OFFSET + 0x20000000)
macro_line|#endif
eof
