macro_line|#ifndef __UM_PAGE_H
DECL|macro|__UM_PAGE_H
mdefine_line|#define __UM_PAGE_H
r_struct
id|page
suffix:semicolon
macro_line|#include &quot;asm/arch/page.h&quot;
macro_line|#include &quot;asm/bug.h&quot;
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
id|region_pa
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
id|region_va
c_func
(paren
r_int
r_int
id|phys
)paren
suffix:semicolon
DECL|macro|__pa
mdefine_line|#define __pa(virt) region_pa((void *) (virt))
DECL|macro|__va
mdefine_line|#define __va(phys) region_va((unsigned long) (phys))
r_extern
r_int
r_int
id|page_to_pfn
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|pfn_to_page
c_func
(paren
r_int
r_int
id|pfn
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|phys_to_page
c_func
(paren
r_int
r_int
id|phys
)paren
suffix:semicolon
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(v) (phys_to_page(__pa(v)))
r_extern
r_struct
id|page
op_star
id|page_mem_map
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
DECL|macro|pfn_valid
mdefine_line|#define pfn_valid(pfn) (page_mem_map(pfn_to_page(pfn)) != NULL)
DECL|macro|virt_addr_valid
mdefine_line|#define virt_addr_valid(v) pfn_valid(__pa(v) &gt;&gt; PAGE_SHIFT)
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
macro_line|#endif
eof
