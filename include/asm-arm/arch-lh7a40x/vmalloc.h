multiline_comment|/* include/asm-arm/arch-lh7a40x/vmalloc.h&n; *&n; *  Copyright (C) 2004 Coastal Environmental Systems&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  version 2 as published by the Free Software Foundation.&n; *&n; */
multiline_comment|/*&n; * Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after&n; * the physical memory until the kernel virtual memory starts.  That&n; * means that any out-of-bounds memory accesses will hopefully be&n; * caught.  The vmalloc() routines leaves a hole of 4kB (one page)&n; * between each vmalloced area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET&t;  (8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;  (((unsigned long)high_memory + VMALLOC_OFFSET) &amp; ~(VMALLOC_OFFSET-1))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END       (0xe8000000)
eof
