multiline_comment|/*&n; * linux/include/asm-arm/arch-iop80310/memory.h&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
multiline_comment|/*&n; * Task size: 3GB&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0xc0000000UL)
DECL|macro|TASK_SIZE_26
mdefine_line|#define TASK_SIZE_26&t;(0x04000000UL)
multiline_comment|/*&n; * This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE (TASK_SIZE / 3)
multiline_comment|/*&n; * Page offset: 3GB&n; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;(0xc0000000UL)
multiline_comment|/*&n; * Physical DRAM offset.&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0xa0000000UL)
multiline_comment|/*&n; * physical vs virtual ram conversion&n; */
DECL|macro|__virt_to_phys__is_a_macro
mdefine_line|#define __virt_to_phys__is_a_macro
DECL|macro|__phys_to_virt__is_a_macro
mdefine_line|#define __phys_to_virt__is_a_macro
DECL|macro|__virt_to_phys
mdefine_line|#define __virt_to_phys(x)&t;((x) - PAGE_OFFSET + PHYS_OFFSET)
DECL|macro|__phys_to_virt
mdefine_line|#define __phys_to_virt(x)&t;((x) - PHYS_OFFSET + PAGE_OFFSET)
multiline_comment|/*&n; * Virtual view &lt;-&gt; DMA view memory address translations&n; * virt_to_bus: Used to translate the virtual address to an&n; *&t;&t;address suitable to be passed to set_dma_addr&n; * bus_to_virt: Used to convert an address for DMA operations&n; *&t;&t;to an address that the kernel can use.&n; */
DECL|macro|__virt_to_bus__is_a_macro
mdefine_line|#define __virt_to_bus__is_a_macro
DECL|macro|__bus_to_virt__is_a_macro
mdefine_line|#define __bus_to_virt__is_a_macro
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;(((__virt_to_phys(x)) &amp; ~(*IOP310_SIATVR)) | ((*IOP310_SIABAR) &amp; 0xfffffff0))
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)    (__phys_to_virt(((x) &amp; ~(*IOP310_SIALR)) | ( *IOP310_SIATVR)))
DECL|macro|PHYS_TO_NID
mdefine_line|#define PHYS_TO_NID(x)&t;&t;0
multiline_comment|/* boot mem allocate global pointer for MU circular queues QBAR */
macro_line|#ifdef CONFIG_IOP310_MU
r_extern
r_void
op_star
id|mu_mem
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
