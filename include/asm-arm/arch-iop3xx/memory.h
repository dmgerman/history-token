multiline_comment|/*&n; * linux/include/asm-arm/arch-iop80310/memory.h&n; */
macro_line|#ifndef __ASM_ARCH_MEMORY_H
DECL|macro|__ASM_ARCH_MEMORY_H
mdefine_line|#define __ASM_ARCH_MEMORY_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/arch/iop310.h&gt;
macro_line|#include &lt;asm/arch/iop321.h&gt;
multiline_comment|/*&n; * Physical DRAM offset.&n; */
DECL|macro|PHYS_OFFSET
mdefine_line|#define PHYS_OFFSET&t;(0xa0000000UL)
multiline_comment|/*&n; * Virtual view &lt;-&gt; DMA view memory address translations&n; * virt_to_bus: Used to translate the virtual address to an&n; *&t;&t;address suitable to be passed to set_dma_addr&n; * bus_to_virt: Used to convert an address for DMA operations&n; *&t;&t;to an address that the kernel can use.&n; */
macro_line|#ifdef CONFIG_ARCH_IOP310
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;(((__virt_to_phys(x)) &amp; ~(*IOP310_SIATVR)) | ((*IOP310_SIABAR) &amp; 0xfffffff0))
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)    (__phys_to_virt(((x) &amp; ~(*IOP310_SIALR)) | ( *IOP310_SIATVR)))
macro_line|#elif defined(CONFIG_ARCH_IOP321)
DECL|macro|__virt_to_bus
mdefine_line|#define __virt_to_bus(x)&t;(((__virt_to_phys(x)) &amp; ~(*IOP321_IATVR2)) | ((*IOP321_IABAR2) &amp; 0xfffffff0))
DECL|macro|__bus_to_virt
mdefine_line|#define __bus_to_virt(x)    (__phys_to_virt(((x) &amp; ~(*IOP321_IALR2)) | ( *IOP321_IATVR2)))
macro_line|#endif
multiline_comment|/* boot mem allocate global pointer for MU circular queues QBAR */
macro_line|#ifdef CONFIG_IOP3XX_MU
r_extern
r_void
op_star
id|mu_mem
suffix:semicolon
macro_line|#endif
DECL|macro|PFN_TO_NID
mdefine_line|#define PFN_TO_NID(addr)&t;(0)
macro_line|#endif
eof
