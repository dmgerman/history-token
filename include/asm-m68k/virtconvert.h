macro_line|#ifndef __VIRT_CONVERT__
DECL|macro|__VIRT_CONVERT__
mdefine_line|#define __VIRT_CONVERT__
multiline_comment|/*&n; * Macros used for converting between virtual and physical mappings.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#ifdef CONFIG_AMIGA
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; */
macro_line|#ifndef CONFIG_SUN3
r_extern
r_int
r_int
id|mm_vtop
c_func
(paren
r_int
r_int
id|addr
)paren
id|__attribute_const__
suffix:semicolon
r_extern
r_int
r_int
id|mm_ptov
c_func
(paren
r_int
r_int
id|addr
)paren
id|__attribute_const__
suffix:semicolon
macro_line|#else
DECL|function|mm_vtop
r_static
r_inline
r_int
r_int
id|mm_vtop
c_func
(paren
r_int
r_int
id|vaddr
)paren
(brace
r_return
id|__pa
c_func
(paren
id|vaddr
)paren
suffix:semicolon
)brace
DECL|function|mm_ptov
r_static
r_inline
r_int
r_int
id|mm_ptov
c_func
(paren
r_int
r_int
id|paddr
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|paddr
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_SINGLE_MEMORY_CHUNK
DECL|function|virt_to_phys
r_static
r_inline
r_int
r_int
id|virt_to_phys
c_func
(paren
r_void
op_star
id|vaddr
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|vaddr
op_minus
id|PAGE_OFFSET
op_plus
id|m68k_memory
(braket
l_int|0
)braket
dot
id|addr
suffix:semicolon
)brace
DECL|function|phys_to_virt
r_static
r_inline
r_void
op_star
id|phys_to_virt
c_func
(paren
r_int
r_int
id|paddr
)paren
(brace
r_return
(paren
r_void
op_star
)paren
(paren
id|paddr
op_minus
id|m68k_memory
(braket
l_int|0
)braket
dot
id|addr
op_plus
id|PAGE_OFFSET
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|virt_to_phys
r_static
r_inline
r_int
r_int
id|virt_to_phys
c_func
(paren
r_void
op_star
id|address
)paren
(brace
r_return
id|mm_vtop
c_func
(paren
(paren
r_int
r_int
)paren
id|address
)paren
suffix:semicolon
)brace
DECL|function|phys_to_virt
r_static
r_inline
r_void
op_star
id|phys_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|mm_ptov
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Permanent address of a page. */
DECL|macro|__page_address
mdefine_line|#define __page_address(page)&t;(PAGE_OFFSET + (((page) - mem_map) &lt;&lt; PAGE_SHIFT))
DECL|macro|page_to_phys
mdefine_line|#define page_to_phys(page)&t;virt_to_phys((void *)__page_address(page))
multiline_comment|/*&n; * IO bus memory addresses are 1:1 with the physical address,&n; * except on the PCI bus of the Hades.&n; */
macro_line|#ifdef CONFIG_HADES
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus(a) (virt_to_phys(a) + (MACH_IS_HADES ? 0x80000000 : 0))
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt(a) (phys_to_virt((a) - (MACH_IS_HADES ? 0x80000000 : 0)))
macro_line|#else
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
macro_line|#endif
macro_line|#endif
macro_line|#endif
eof
