multiline_comment|/*&n; * linux/include/asm-arm/arch-cl7500/vmalloc.h&n; */
multiline_comment|/*&n; * Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET&t;  (8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;  (((unsigned long)high_memory + VMALLOC_OFFSET) &amp; ~(VMALLOC_OFFSET-1))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END       (PAGE_OFFSET + 0x1c000000)
DECL|macro|MODULE_START
mdefine_line|#define MODULE_START&t;(PAGE_OFFSET - 16*1048576)
DECL|macro|MODULE_END
mdefine_line|#define MODULE_END&t;(PAGE_OFFSET)
eof
