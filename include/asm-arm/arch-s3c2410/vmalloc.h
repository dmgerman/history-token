multiline_comment|/* linux/include/asm-arm/arch-s3c2410/vmalloc.h&n; *&n; * from linux/include/asm-arm/arch-iop3xx/vmalloc.h&n; *&n; * Copyright (c) 2003 Simtec Electronics &lt;linux@simtec.co.uk&gt;&n; *&t;&t;      http://www.simtec.co.uk/products/SWLINUX/&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * S3C2410 vmalloc definition&n; *&n; *  Changelog:&n; *    12-Mar-2004 BJD&t;Fixed header, added include protection&n; *    12=Mar-2004 BJD&t;Fixed VMALLOC_END definitions&n; */
macro_line|#ifndef __ASM_ARCH_VMALLOC_H
DECL|macro|__ASM_ARCH_VMALLOC_H
mdefine_line|#define __ASM_ARCH_VMALLOC_H
multiline_comment|/*&n; * Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET&t;  (8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;  (((unsigned long)high_memory + VMALLOC_OFFSET) &amp; ~(VMALLOC_OFFSET-1))
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;  (0xE0000000)
macro_line|#endif /* __ASM_ARCH_VMALLOC_H */
eof
