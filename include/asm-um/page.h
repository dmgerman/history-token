multiline_comment|/*&n; *  Copyright (C) 2000 - 2003 Jeff Dike (jdike@addtoit.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_PAGE_H
DECL|macro|__UM_PAGE_H
mdefine_line|#define __UM_PAGE_H
r_struct
id|page
suffix:semicolon
macro_line|#include &quot;asm/arch/page.h&quot;
DECL|macro|__pa
macro_line|#undef __pa
DECL|macro|__va
macro_line|#undef __va
DECL|macro|pfn_to_page
macro_line|#undef pfn_to_page
DECL|macro|page_to_pfn
macro_line|#undef page_to_pfn
DECL|macro|virt_to_page
macro_line|#undef virt_to_page
DECL|macro|pfn_valid
macro_line|#undef pfn_valid
DECL|macro|virt_addr_valid
macro_line|#undef virt_addr_valid
DECL|macro|VALID_PAGE
macro_line|#undef VALID_PAGE
DECL|macro|PAGE_OFFSET
macro_line|#undef PAGE_OFFSET
DECL|macro|KERNELBASE
macro_line|#undef KERNELBASE
r_extern
r_int
r_int
id|uml_physmem
suffix:semicolon
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET (uml_physmem)
DECL|macro|KERNELBASE
mdefine_line|#define KERNELBASE PAGE_OFFSET
DECL|macro|__va_space
mdefine_line|#define __va_space (8*1024*1024)
r_extern
r_int
r_int
id|to_phys
c_func
(paren
r_void
op_star
id|virt
)paren
suffix:semicolon
r_extern
r_void
op_star
id|to_virt
c_func
(paren
r_int
r_int
id|phys
)paren
suffix:semicolon
DECL|macro|__pa
mdefine_line|#define __pa(virt) to_phys((void *) virt)
DECL|macro|__va
mdefine_line|#define __va(phys) to_virt((unsigned long) phys)
DECL|macro|page_to_pfn
mdefine_line|#define page_to_pfn(page) ((page) - mem_map)
DECL|macro|pfn_to_page
mdefine_line|#define pfn_to_page(pfn) (mem_map + (pfn))
DECL|macro|phys_to_pfn
mdefine_line|#define phys_to_pfn(p) ((p) &gt;&gt; PAGE_SHIFT)
DECL|macro|pfn_to_phys
mdefine_line|#define pfn_to_phys(pfn) ((pfn) &lt;&lt; PAGE_SHIFT)
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn) ((pfn) &lt; max_mapnr)
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(v) pfn_valid(phys_to_pfn(__pa(v)))
r_extern
r_struct
id|page
op_star
id|arch_validate
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|mask
comma
r_int
id|order
)paren
suffix:semicolon
DECL|macro|HAVE_ARCH_VALIDATE
mdefine_line|#define HAVE_ARCH_VALIDATE
r_extern
r_void
id|arch_free_page
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|order
)paren
suffix:semicolon
DECL|macro|HAVE_ARCH_FREE_PAGE
mdefine_line|#define HAVE_ARCH_FREE_PAGE
macro_line|#endif
eof
