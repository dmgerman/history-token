multiline_comment|/* virtconvert.h: virtual/physical/page address convertion&n; *&n; * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _ASM_VIRTCONVERT_H
DECL|macro|_ASM_VIRTCONVERT_H
mdefine_line|#define _ASM_VIRTCONVERT_H
multiline_comment|/*&n; * Macros used for converting between virtual and physical mappings.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#ifdef CONFIG_MMU
DECL|macro|phys_to_virt
mdefine_line|#define phys_to_virt(vaddr)&t;((void *) ((unsigned long)(vaddr) + PAGE_OFFSET))
DECL|macro|virt_to_phys
mdefine_line|#define virt_to_phys(vaddr)&t;((unsigned long) (vaddr) - PAGE_OFFSET)
macro_line|#else
DECL|macro|phys_to_virt
mdefine_line|#define phys_to_virt(vaddr)&t;((void *) (vaddr))
DECL|macro|virt_to_phys
mdefine_line|#define virt_to_phys(vaddr)&t;((unsigned long) (vaddr))
macro_line|#endif
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
DECL|macro|__page_address
mdefine_line|#define __page_address(page)&t;(PAGE_OFFSET + (((page) - mem_map) &lt;&lt; PAGE_SHIFT))
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;virt_to_phys((void *)__page_address(page))
macro_line|#endif
macro_line|#endif
eof
