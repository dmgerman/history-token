macro_line|#ifndef __ASM_CPU_SH4_DMA_H
DECL|macro|__ASM_CPU_SH4_DMA_H
mdefine_line|#define __ASM_CPU_SH4_DMA_H
DECL|macro|SH_DMAC_BASE
mdefine_line|#define SH_DMAC_BASE&t;0xffa00000
DECL|macro|SAR
mdefine_line|#define SAR&t;((unsigned long[]){SH_DMAC_BASE + 0x00, SH_DMAC_BASE + 0x10, &bslash;&n;&t;&t;&t;&t;   SH_DMAC_BASE + 0x20, SH_DMAC_BASE + 0x30})
DECL|macro|DAR
mdefine_line|#define DAR&t;((unsigned long[]){SH_DMAC_BASE + 0x04, SH_DMAC_BASE + 0x14, &bslash;&n;&t;&t;&t;&t;   SH_DMAC_BASE + 0x24, SH_DMAC_BASE + 0x34})
DECL|macro|DMATCR
mdefine_line|#define DMATCR&t;((unsigned long[]){SH_DMAC_BASE + 0x08, SH_DMAC_BASE + 0x18, &bslash;&n;&t;&t;&t;&t;   SH_DMAC_BASE + 0x28, SH_DMAC_BASE + 0x38})
DECL|macro|CHCR
mdefine_line|#define CHCR&t;((unsigned long[]){SH_DMAC_BASE + 0x0c, SH_DMAC_BASE + 0x1c, &bslash;&n;&t;&t;&t;&t;   SH_DMAC_BASE + 0x2c, SH_DMAC_BASE + 0x3c})
DECL|macro|DMAOR
mdefine_line|#define DMAOR&t;(SH_DMAC_BASE + 0x40)
macro_line|#endif /* __ASM_CPU_SH4_DMA_H */
eof
