macro_line|#ifndef __H8300_VIRT_CONVERT__
DECL|macro|__H8300_VIRT_CONVERT__
mdefine_line|#define __H8300_VIRT_CONVERT__
multiline_comment|/*&n; * Macros used for converting between virtual and physical mappings.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|macro|mm_ptov
mdefine_line|#define mm_ptov(vaddr)&t;&t;((void *) (vaddr))
DECL|macro|mm_vtop
mdefine_line|#define mm_vtop(vaddr)&t;&t;((unsigned long) (vaddr))
DECL|macro|phys_to_virt
mdefine_line|#define phys_to_virt(vaddr)&t;((void *) (vaddr))
DECL|macro|virt_to_phys
mdefine_line|#define virt_to_phys(vaddr)&t;((unsigned long) (vaddr))
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
macro_line|#endif
macro_line|#endif
eof
