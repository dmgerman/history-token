multiline_comment|/*&n; * Helpfile for jazzdma.c -- Mips Jazz R4030 DMA controller support&n; */
macro_line|#ifndef _ASM_JAZZDMA_H
DECL|macro|_ASM_JAZZDMA_H
mdefine_line|#define _ASM_JAZZDMA_H
multiline_comment|/*&n; * Prototypes and macros&n; */
r_extern
r_void
id|vdma_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|vdma_alloc
c_func
(paren
r_int
r_int
id|paddr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|vdma_free
c_func
(paren
r_int
r_int
id|laddr
)paren
suffix:semicolon
r_extern
r_int
id|vdma_remap
c_func
(paren
r_int
r_int
id|laddr
comma
r_int
r_int
id|paddr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
r_int
id|vdma_phys2log
c_func
(paren
r_int
r_int
id|paddr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|vdma_log2phys
c_func
(paren
r_int
r_int
id|laddr
)paren
suffix:semicolon
r_extern
r_void
id|vdma_stats
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* for debugging only */
r_extern
r_void
id|vdma_enable
c_func
(paren
r_int
id|channel
)paren
suffix:semicolon
r_extern
r_void
id|vdma_disable
c_func
(paren
r_int
id|channel
)paren
suffix:semicolon
r_extern
r_void
id|vdma_set_mode
c_func
(paren
r_int
id|channel
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_void
id|vdma_set_addr
c_func
(paren
r_int
id|channel
comma
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|vdma_set_count
c_func
(paren
r_int
id|channel
comma
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
id|vdma_get_residue
c_func
(paren
r_int
id|channel
)paren
suffix:semicolon
r_extern
r_int
id|vdma_get_enable
c_func
(paren
r_int
id|channel
)paren
suffix:semicolon
multiline_comment|/*&n; * some definitions used by the driver functions&n; */
DECL|macro|VDMA_PAGESIZE
mdefine_line|#define VDMA_PAGESIZE&t;&t;4096
DECL|macro|VDMA_PGTBL_ENTRIES
mdefine_line|#define VDMA_PGTBL_ENTRIES&t;4096
DECL|macro|VDMA_PGTBL_SIZE
mdefine_line|#define VDMA_PGTBL_SIZE&t;&t;(sizeof(VDMA_PGTBL_ENTRY) * VDMA_PGTBL_ENTRIES)
DECL|macro|VDMA_PAGE_EMPTY
mdefine_line|#define VDMA_PAGE_EMPTY&t;&t;0xff000000
multiline_comment|/*&n; * Macros to get page no. and offset of a given address&n; * Note that VDMA_PAGE() works for physical addresses only&n; */
DECL|macro|VDMA_PAGE
mdefine_line|#define VDMA_PAGE(a)            ((unsigned int)(a) &gt;&gt; 12)
DECL|macro|VDMA_OFFSET
mdefine_line|#define VDMA_OFFSET(a)          ((unsigned int)(a) &amp; (VDMA_PAGESIZE-1))
multiline_comment|/*&n; * error code returned by vdma_alloc()&n; * (See also arch/mips/kernel/jazzdma.c)&n; */
DECL|macro|VDMA_ERROR
mdefine_line|#define VDMA_ERROR              0xffffffff
multiline_comment|/*&n; * VDMA pagetable entry description&n; */
DECL|struct|VDMA_PGTBL_ENTRY
r_typedef
r_volatile
r_struct
id|VDMA_PGTBL_ENTRY
(brace
DECL|member|frame
r_int
r_int
id|frame
suffix:semicolon
multiline_comment|/* physical frame no. */
DECL|member|owner
r_int
r_int
id|owner
suffix:semicolon
multiline_comment|/* owner of this entry (0=free) */
DECL|typedef|VDMA_PGTBL_ENTRY
)brace
id|VDMA_PGTBL_ENTRY
suffix:semicolon
multiline_comment|/*&n; * DMA channel control registers&n; * in the R4030 MCT_ADR chip&n; */
DECL|macro|JAZZ_R4030_CHNL_MODE
mdefine_line|#define JAZZ_R4030_CHNL_MODE&t;0xE0000100&t;/* 8 DMA Channel Mode Registers, */
multiline_comment|/* 0xE0000100,120,140... */
DECL|macro|JAZZ_R4030_CHNL_ENABLE
mdefine_line|#define JAZZ_R4030_CHNL_ENABLE  0xE0000108&t;/* 8 DMA Channel Enable Regs, */
multiline_comment|/* 0xE0000108,128,148... */
DECL|macro|JAZZ_R4030_CHNL_COUNT
mdefine_line|#define JAZZ_R4030_CHNL_COUNT   0xE0000110&t;/* 8 DMA Channel Byte Cnt Regs, */
multiline_comment|/* 0xE0000110,130,150... */
DECL|macro|JAZZ_R4030_CHNL_ADDR
mdefine_line|#define JAZZ_R4030_CHNL_ADDR&t;0xE0000118&t;/* 8 DMA Channel Address Regs, */
multiline_comment|/* 0xE0000118,138,158... */
multiline_comment|/* channel enable register bits */
DECL|macro|R4030_CHNL_ENABLE
mdefine_line|#define R4030_CHNL_ENABLE        (1&lt;&lt;0)
DECL|macro|R4030_CHNL_WRITE
mdefine_line|#define R4030_CHNL_WRITE         (1&lt;&lt;1)
DECL|macro|R4030_TC_INTR
mdefine_line|#define R4030_TC_INTR            (1&lt;&lt;8)
DECL|macro|R4030_MEM_INTR
mdefine_line|#define R4030_MEM_INTR           (1&lt;&lt;9)
DECL|macro|R4030_ADDR_INTR
mdefine_line|#define R4030_ADDR_INTR          (1&lt;&lt;10)
multiline_comment|/*&n; * Channel mode register bits&n; */
DECL|macro|R4030_MODE_ATIME_40
mdefine_line|#define R4030_MODE_ATIME_40      (0) /* device access time on remote bus */
DECL|macro|R4030_MODE_ATIME_80
mdefine_line|#define R4030_MODE_ATIME_80      (1)
DECL|macro|R4030_MODE_ATIME_120
mdefine_line|#define R4030_MODE_ATIME_120     (2)
DECL|macro|R4030_MODE_ATIME_160
mdefine_line|#define R4030_MODE_ATIME_160     (3)
DECL|macro|R4030_MODE_ATIME_200
mdefine_line|#define R4030_MODE_ATIME_200     (4)
DECL|macro|R4030_MODE_ATIME_240
mdefine_line|#define R4030_MODE_ATIME_240     (5)
DECL|macro|R4030_MODE_ATIME_280
mdefine_line|#define R4030_MODE_ATIME_280     (6)
DECL|macro|R4030_MODE_ATIME_320
mdefine_line|#define R4030_MODE_ATIME_320     (7)
DECL|macro|R4030_MODE_WIDTH_8
mdefine_line|#define R4030_MODE_WIDTH_8       (1&lt;&lt;3)&t;/* device data bus width */
DECL|macro|R4030_MODE_WIDTH_16
mdefine_line|#define R4030_MODE_WIDTH_16      (2&lt;&lt;3)
DECL|macro|R4030_MODE_WIDTH_32
mdefine_line|#define R4030_MODE_WIDTH_32      (3&lt;&lt;3)
DECL|macro|R4030_MODE_INTR_EN
mdefine_line|#define R4030_MODE_INTR_EN       (1&lt;&lt;5)
DECL|macro|R4030_MODE_BURST
mdefine_line|#define R4030_MODE_BURST         (1&lt;&lt;6)&t;/* Rev. 2 only */
DECL|macro|R4030_MODE_FAST_ACK
mdefine_line|#define R4030_MODE_FAST_ACK      (1&lt;&lt;7)&t;/* Rev. 2 only */
macro_line|#endif /* _ASM_JAZZDMA_H */
eof
