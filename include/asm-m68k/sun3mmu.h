multiline_comment|/*&n; * Definitions for Sun3 custom MMU.&n; */
macro_line|#include &lt;asm/movs.h&gt;
macro_line|#ifndef __SUN3_MMU_H__
DECL|macro|__SUN3_MMU_H__
mdefine_line|#define __SUN3_MMU_H__
DECL|macro|FC_CONTROL
mdefine_line|#define FC_CONTROL 3
multiline_comment|/* MMU characteristics. */
DECL|macro|SUN3_SEGMAPS_PER_CONTEXT
mdefine_line|#define SUN3_SEGMAPS_PER_CONTEXT&t;2048
DECL|macro|SUN3_PMEGS_NUM
mdefine_line|#define SUN3_PMEGS_NUM&t;&t;&t;256
DECL|macro|SUN3_CONTEXTS_NUM
mdefine_line|#define SUN3_CONTEXTS_NUM               8
DECL|macro|SUN3_PMEG_SIZE_BITS
mdefine_line|#define SUN3_PMEG_SIZE_BITS&t; 17
DECL|macro|SUN3_PMEG_SIZE
mdefine_line|#define SUN3_PMEG_SIZE&t;&t; (1 &lt;&lt; SUN3_PMEG_SIZE_BITS)
DECL|macro|SUN3_PMEG_MASK
mdefine_line|#define SUN3_PMEG_MASK&t;&t; (SUN3_PMEG_SIZE - 1)
DECL|macro|SUN3_PTE_SIZE_BITS
mdefine_line|#define SUN3_PTE_SIZE_BITS       13
DECL|macro|SUN3_PTE_SIZE
mdefine_line|#define SUN3_PTE_SIZE&t;&t; (1 &lt;&lt; SUN3_PTE_SIZE_BITS)
DECL|macro|SUN3_PTE_MASK
mdefine_line|#define SUN3_PTE_MASK&t;&t; (SUN3_PTE_SIZE - 1)
DECL|macro|SUN3_CONTROL_MASK
mdefine_line|#define SUN3_CONTROL_MASK       (0x0FFFFFFC)
DECL|macro|SUN3_INVALID_PMEG
mdefine_line|#define SUN3_INVALID_PMEG&t;255
DECL|macro|SUN3_INVALID_CONTEXT
mdefine_line|#define SUN3_INVALID_CONTEXT 255
DECL|macro|AC_IDPROM
mdefine_line|#define AC_IDPROM     0x00000000    /* 34  ID PROM, R/O, byte, 32 bytes      */
DECL|macro|AC_PAGEMAP
mdefine_line|#define AC_PAGEMAP    0x10000000    /* 3   Pagemap R/W, long                 */
DECL|macro|AC_SEGMAP
mdefine_line|#define AC_SEGMAP     0x20000000    /* 3   Segment map, byte                 */
DECL|macro|AC_CONTEXT
mdefine_line|#define AC_CONTEXT    0x30000000    /* 34c current mmu-context               */
DECL|macro|AC_SENABLE
mdefine_line|#define AC_SENABLE    0x40000000    /* 34c system dvma/cache/reset enable reg*/
DECL|macro|AC_UDVMA_ENB
mdefine_line|#define AC_UDVMA_ENB  0x50000000    /* 34  Not used on Sun boards, byte      */
DECL|macro|AC_BUS_ERROR
mdefine_line|#define AC_BUS_ERROR  0x60000000    /* 34  Cleared on read, byte.            */
DECL|macro|AC_SYNC_ERR
mdefine_line|#define AC_SYNC_ERR   0x60000000    /*   c fault type                        */
DECL|macro|AC_SYNC_VA
mdefine_line|#define AC_SYNC_VA    0x60000004    /*   c fault virtual address             */
DECL|macro|AC_ASYNC_ERR
mdefine_line|#define AC_ASYNC_ERR  0x60000008    /*   c asynchronous fault type           */
DECL|macro|AC_ASYNC_VA
mdefine_line|#define AC_ASYNC_VA   0x6000000c    /*   c async fault virtual address       */
DECL|macro|AC_LEDS
mdefine_line|#define AC_LEDS       0x70000000    /* 34  Zero turns on LEDs, byte          */
DECL|macro|AC_CACHETAGS
mdefine_line|#define AC_CACHETAGS  0x80000000    /* 34c direct access to the VAC tags     */
DECL|macro|AC_CACHEDDATA
mdefine_line|#define AC_CACHEDDATA 0x90000000    /* 3 c direct access to the VAC data     */
DECL|macro|AC_UDVMA_MAP
mdefine_line|#define AC_UDVMA_MAP  0xD0000000    /* 4   Not used on Sun boards, byte      */
DECL|macro|AC_VME_VECTOR
mdefine_line|#define AC_VME_VECTOR 0xE0000000    /* 4   For non-Autovector VME, byte      */
DECL|macro|AC_BOOT_SCC
mdefine_line|#define AC_BOOT_SCC   0xF0000000    /* 34  bypass to access Zilog 8530. byte.*/
DECL|macro|SUN3_PAGE_CHG_MASK
mdefine_line|#define SUN3_PAGE_CHG_MASK (SUN3_PAGE_PGNUM_MASK &bslash;&n;&t;&t;&t;    | SUN3_PAGE_ACCESSED | SUN3_PAGE_MODIFIED)
multiline_comment|/* Bus access type within PTE. */
DECL|macro|SUN3_PAGE_TYPE_MASK
mdefine_line|#define SUN3_PAGE_TYPE_MASK   (0x0c000000)
DECL|macro|SUN3_PAGE_TYPE_MEMORY
mdefine_line|#define SUN3_PAGE_TYPE_MEMORY (0x00000000)
DECL|macro|SUN3_PAGE_TYPE_IO
mdefine_line|#define SUN3_PAGE_TYPE_IO     (0x04000000)
DECL|macro|SUN3_PAGE_TYPE_VME16
mdefine_line|#define SUN3_PAGE_TYPE_VME16  (0x08000000)
DECL|macro|SUN3_PAGE_TYPE_VME32
mdefine_line|#define SUN3_PAGE_TYPE_VME32  (0x0c000000)
multiline_comment|/* Mask for page number within PTE. */
DECL|macro|SUN3_PAGE_PGNUM_MASK
mdefine_line|#define SUN3_PAGE_PGNUM_MASK (0x0007FFFF)
multiline_comment|/* Bits within bus-error register. */
DECL|macro|SUN3_BUSERR_WATCHDOG
mdefine_line|#define SUN3_BUSERR_WATCHDOG&t;(0x01)
DECL|macro|SUN3_BUSERR_unused
mdefine_line|#define SUN3_BUSERR_unused&t;(0x02)
DECL|macro|SUN3_BUSERR_FPAENERR
mdefine_line|#define SUN3_BUSERR_FPAENERR&t;(0x04)
DECL|macro|SUN3_BUSERR_FPABERR
mdefine_line|#define SUN3_BUSERR_FPABERR&t;(0x08)
DECL|macro|SUN3_BUSERR_VMEBERR
mdefine_line|#define SUN3_BUSERR_VMEBERR&t;(0x10)
DECL|macro|SUN3_BUSERR_TIMEOUT
mdefine_line|#define SUN3_BUSERR_TIMEOUT&t;(0x20)
DECL|macro|SUN3_BUSERR_PROTERR
mdefine_line|#define SUN3_BUSERR_PROTERR&t;(0x40)
DECL|macro|SUN3_BUSERR_INVALID
mdefine_line|#define SUN3_BUSERR_INVALID&t;(0x80)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Read bus error status register (implicitly clearing it). */
DECL|function|sun3_get_buserr
r_extern
id|__inline__
r_int
r_char
id|sun3_get_buserr
(paren
r_void
)paren
(brace
r_int
r_char
id|sfc
comma
id|c
suffix:semicolon
id|GET_SFC
(paren
id|sfc
)paren
suffix:semicolon
id|SET_SFC
(paren
id|FC_CONTROL
)paren
suffix:semicolon
id|GET_CONTROL_BYTE
(paren
id|AC_BUS_ERROR
comma
id|c
)paren
suffix:semicolon
id|SET_SFC
(paren
id|sfc
)paren
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
multiline_comment|/* Read segmap from hardware MMU. */
DECL|function|sun3_get_segmap
r_extern
id|__inline__
r_int
r_int
id|sun3_get_segmap
(paren
r_int
r_int
id|addr
)paren
(brace
r_register
r_int
r_int
id|entry
suffix:semicolon
r_int
r_char
id|c
comma
id|sfc
suffix:semicolon
id|GET_SFC
(paren
id|sfc
)paren
suffix:semicolon
id|SET_SFC
(paren
id|FC_CONTROL
)paren
suffix:semicolon
id|GET_CONTROL_BYTE
(paren
id|AC_SEGMAP
op_or
(paren
id|addr
op_amp
id|SUN3_CONTROL_MASK
)paren
comma
id|c
)paren
suffix:semicolon
id|SET_SFC
(paren
id|sfc
)paren
suffix:semicolon
id|entry
op_assign
id|c
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
multiline_comment|/* Write segmap to hardware MMU. */
DECL|function|sun3_put_segmap
r_extern
id|__inline__
r_void
id|sun3_put_segmap
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|entry
)paren
(brace
r_int
r_char
id|sfc
suffix:semicolon
id|GET_DFC
(paren
id|sfc
)paren
suffix:semicolon
id|SET_DFC
(paren
id|FC_CONTROL
)paren
suffix:semicolon
id|SET_CONTROL_BYTE
(paren
id|AC_SEGMAP
op_or
(paren
id|addr
op_amp
id|SUN3_CONTROL_MASK
)paren
comma
id|entry
)paren
suffix:semicolon
id|SET_DFC
(paren
id|sfc
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Read PTE from hardware MMU. */
DECL|function|sun3_get_pte
r_extern
id|__inline__
r_int
r_int
id|sun3_get_pte
(paren
r_int
r_int
id|addr
)paren
(brace
r_register
r_int
r_int
id|entry
suffix:semicolon
r_int
r_char
id|sfc
suffix:semicolon
id|GET_SFC
(paren
id|sfc
)paren
suffix:semicolon
id|SET_SFC
(paren
id|FC_CONTROL
)paren
suffix:semicolon
id|GET_CONTROL_WORD
(paren
id|AC_PAGEMAP
op_or
(paren
id|addr
op_amp
id|SUN3_CONTROL_MASK
)paren
comma
id|entry
)paren
suffix:semicolon
id|SET_SFC
(paren
id|sfc
)paren
suffix:semicolon
r_return
id|entry
suffix:semicolon
)brace
multiline_comment|/* Write PTE to hardware MMU. */
DECL|function|sun3_put_pte
r_extern
id|__inline__
r_void
id|sun3_put_pte
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|entry
)paren
(brace
r_int
r_char
id|sfc
suffix:semicolon
id|GET_DFC
(paren
id|sfc
)paren
suffix:semicolon
id|SET_DFC
(paren
id|FC_CONTROL
)paren
suffix:semicolon
id|SET_CONTROL_WORD
(paren
id|AC_PAGEMAP
op_or
(paren
id|addr
op_amp
id|SUN3_CONTROL_MASK
)paren
comma
id|entry
)paren
suffix:semicolon
id|SET_DFC
(paren
id|sfc
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* get current context */
DECL|function|sun3_get_context
r_extern
id|__inline__
r_int
r_char
id|sun3_get_context
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|sfc
comma
id|c
suffix:semicolon
id|GET_SFC
c_func
(paren
id|sfc
)paren
suffix:semicolon
id|SET_SFC
c_func
(paren
id|FC_CONTROL
)paren
suffix:semicolon
id|GET_CONTROL_BYTE
c_func
(paren
id|AC_CONTEXT
comma
id|c
)paren
suffix:semicolon
id|SET_SFC
c_func
(paren
id|sfc
)paren
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
multiline_comment|/* set alternate context */
DECL|function|sun3_put_context
r_extern
id|__inline__
r_void
id|sun3_put_context
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_int
r_char
id|dfc
suffix:semicolon
id|GET_DFC
c_func
(paren
id|dfc
)paren
suffix:semicolon
id|SET_DFC
c_func
(paren
id|FC_CONTROL
)paren
suffix:semicolon
id|SET_CONTROL_BYTE
c_func
(paren
id|AC_CONTEXT
comma
id|c
)paren
suffix:semicolon
id|SET_DFC
c_func
(paren
id|dfc
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif&t;/* !__ASSEMBLY__ */
macro_line|#endif&t;/* !__SUN3_MMU_H__ */
eof
