multiline_comment|/* $Id: dvma.h,v 1.4 1999/03/27 20:23:41 tsbogend Exp $&n; * include/asm-m68k/dma.h&n; *&n; * Copyright 1995 (C) David S. Miller (davem@caip.rutgers.edu)&n; * &n; * Hacked to fit Sun3x needs by Thomas Bogendoerfer&n; */
macro_line|#ifndef __M68K_DVMA_H
DECL|macro|__M68K_DVMA_H
mdefine_line|#define __M68K_DVMA_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|DVMA_PAGE_SHIFT
mdefine_line|#define DVMA_PAGE_SHIFT&t;13
DECL|macro|DVMA_PAGE_SIZE
mdefine_line|#define DVMA_PAGE_SIZE&t;(1UL &lt;&lt; DVMA_PAGE_SHIFT)
DECL|macro|DVMA_PAGE_MASK
mdefine_line|#define DVMA_PAGE_MASK&t;(~(DVMA_PAGE_SIZE-1))
DECL|macro|DVMA_PAGE_ALIGN
mdefine_line|#define DVMA_PAGE_ALIGN(addr)&t;(((addr)+DVMA_PAGE_SIZE-1)&amp;DVMA_PAGE_MASK)
r_extern
r_void
id|dvma_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|dvma_map_iommu
c_func
(paren
r_int
r_int
id|kaddr
comma
r_int
r_int
id|baddr
comma
r_int
id|len
)paren
suffix:semicolon
DECL|macro|dvma_malloc
mdefine_line|#define dvma_malloc(x) dvma_malloc_align(x, 0)
DECL|macro|dvma_map
mdefine_line|#define dvma_map(x, y) dvma_map_align(x, y, 0)
r_extern
r_int
r_int
id|dvma_map_align
c_func
(paren
r_int
r_int
id|kaddr
comma
r_int
id|len
comma
r_int
id|align
)paren
suffix:semicolon
r_extern
r_void
op_star
id|dvma_malloc_align
c_func
(paren
r_int
r_int
id|len
comma
r_int
r_int
id|align
)paren
suffix:semicolon
r_extern
r_void
id|dvma_unmap
c_func
(paren
r_void
op_star
id|baddr
)paren
suffix:semicolon
r_extern
r_void
id|dvma_free
c_func
(paren
r_void
op_star
id|vaddr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SUN3
multiline_comment|/* sun3 dvma page support */
multiline_comment|/* memory and pmegs potentially reserved for dvma */
DECL|macro|DVMA_PMEG_START
mdefine_line|#define DVMA_PMEG_START 10
DECL|macro|DVMA_PMEG_END
mdefine_line|#define DVMA_PMEG_END 16
DECL|macro|DVMA_START
mdefine_line|#define DVMA_START 0xf00000
DECL|macro|DVMA_END
mdefine_line|#define DVMA_END 0xfe0000
DECL|macro|DVMA_SIZE
mdefine_line|#define DVMA_SIZE (DVMA_END-DVMA_START)
DECL|macro|IOMMU_TOTAL_ENTRIES
mdefine_line|#define IOMMU_TOTAL_ENTRIES 128
DECL|macro|IOMMU_ENTRIES
mdefine_line|#define IOMMU_ENTRIES 120
multiline_comment|/* empirical kludge -- dvma regions only seem to work right on 0x10000 &n;   byte boundries */
DECL|macro|DVMA_REGION_SIZE
mdefine_line|#define DVMA_REGION_SIZE 0x10000
DECL|macro|DVMA_ALIGN
mdefine_line|#define DVMA_ALIGN(addr) (((addr)+DVMA_REGION_SIZE-1) &amp; &bslash;&n;                         ~(DVMA_REGION_SIZE-1))
multiline_comment|/* virt &lt;-&gt; phys conversions */
DECL|macro|dvma_vtop
mdefine_line|#define dvma_vtop(x) ((unsigned long)(x) &amp; 0xffffff)
DECL|macro|dvma_ptov
mdefine_line|#define dvma_ptov(x) ((unsigned long)(x) | 0xf000000)
DECL|macro|dvma_vtob
mdefine_line|#define dvma_vtob(x) dvma_vtop(x)
DECL|macro|dvma_btov
mdefine_line|#define dvma_btov(x) dvma_ptov(x)
DECL|function|dvma_map_cpu
r_extern
r_inline
r_int
id|dvma_map_cpu
c_func
(paren
r_int
r_int
id|kaddr
comma
r_int
r_int
id|vaddr
comma
r_int
id|len
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
r_int
id|dvma_page
c_func
(paren
r_int
r_int
id|kaddr
comma
r_int
r_int
id|vaddr
)paren
suffix:semicolon
macro_line|#else /* Sun3x */
multiline_comment|/* sun3x dvma page support */
DECL|macro|DVMA_START
mdefine_line|#define DVMA_START 0x0
DECL|macro|DVMA_END
mdefine_line|#define DVMA_END 0xf00000
DECL|macro|DVMA_SIZE
mdefine_line|#define DVMA_SIZE (DVMA_END-DVMA_START)
DECL|macro|IOMMU_TOTAL_ENTRIES
mdefine_line|#define IOMMU_TOTAL_ENTRIES&t;   2048
multiline_comment|/* the prom takes the top meg */
DECL|macro|IOMMU_ENTRIES
mdefine_line|#define IOMMU_ENTRIES              (IOMMU_TOTAL_ENTRIES - 0x80)
DECL|macro|dvma_vtob
mdefine_line|#define dvma_vtob(x) ((unsigned long)(x) &amp; 0x00ffffff)
DECL|macro|dvma_btov
mdefine_line|#define dvma_btov(x) ((unsigned long)(x) | 0xff000000)
r_extern
r_int
id|dvma_map_cpu
c_func
(paren
r_int
r_int
id|kaddr
comma
r_int
r_int
id|vaddr
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/* everything below this line is specific to dma used for the onboard &n;   ESP scsi on sun3x */
multiline_comment|/* Structure to describe the current status of DMA registers on the Sparc */
DECL|struct|sparc_dma_registers
r_struct
id|sparc_dma_registers
(brace
DECL|member|cond_reg
id|__volatile__
r_int
r_int
id|cond_reg
suffix:semicolon
multiline_comment|/* DMA condition register */
DECL|member|st_addr
id|__volatile__
r_int
r_int
id|st_addr
suffix:semicolon
multiline_comment|/* Start address of this transfer */
DECL|member|cnt
id|__volatile__
r_int
r_int
id|cnt
suffix:semicolon
multiline_comment|/* How many bytes to transfer */
DECL|member|dma_test
id|__volatile__
r_int
r_int
id|dma_test
suffix:semicolon
multiline_comment|/* DMA test register */
)brace
suffix:semicolon
multiline_comment|/* DVMA chip revisions */
DECL|enum|dvma_rev
r_enum
id|dvma_rev
(brace
DECL|enumerator|dvmarev0
id|dvmarev0
comma
DECL|enumerator|dvmaesc1
id|dvmaesc1
comma
DECL|enumerator|dvmarev1
id|dvmarev1
comma
DECL|enumerator|dvmarev2
id|dvmarev2
comma
DECL|enumerator|dvmarev3
id|dvmarev3
comma
DECL|enumerator|dvmarevplus
id|dvmarevplus
comma
DECL|enumerator|dvmahme
id|dvmahme
)brace
suffix:semicolon
DECL|macro|DMA_HASCOUNT
mdefine_line|#define DMA_HASCOUNT(rev)  ((rev)==dvmaesc1)
multiline_comment|/* Linux DMA information structure, filled during probe. */
DECL|struct|Linux_SBus_DMA
r_struct
id|Linux_SBus_DMA
(brace
DECL|member|next
r_struct
id|Linux_SBus_DMA
op_star
id|next
suffix:semicolon
DECL|member|SBus_dev
r_struct
id|linux_sbus_device
op_star
id|SBus_dev
suffix:semicolon
DECL|member|regs
r_struct
id|sparc_dma_registers
op_star
id|regs
suffix:semicolon
multiline_comment|/* Status, misc info */
DECL|member|node
r_int
id|node
suffix:semicolon
multiline_comment|/* Prom node for this DMA device */
DECL|member|running
r_int
id|running
suffix:semicolon
multiline_comment|/* Are we doing DMA now? */
DECL|member|allocated
r_int
id|allocated
suffix:semicolon
multiline_comment|/* Are we &quot;owned&quot; by anyone yet? */
multiline_comment|/* Transfer information. */
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* Start address of current transfer */
DECL|member|nbytes
r_int
id|nbytes
suffix:semicolon
multiline_comment|/* Size of current transfer */
DECL|member|realbytes
r_int
id|realbytes
suffix:semicolon
multiline_comment|/* For splitting up large transfers, etc. */
multiline_comment|/* DMA revision */
DECL|member|revision
r_enum
id|dvma_rev
id|revision
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|Linux_SBus_DMA
op_star
id|dma_chain
suffix:semicolon
multiline_comment|/* Broken hardware... */
DECL|macro|DMA_ISBROKEN
mdefine_line|#define DMA_ISBROKEN(dma)    ((dma)-&gt;revision == dvmarev1)
DECL|macro|DMA_ISESC1
mdefine_line|#define DMA_ISESC1(dma)      ((dma)-&gt;revision == dvmaesc1)
multiline_comment|/* Fields in the cond_reg register */
multiline_comment|/* First, the version identification bits */
DECL|macro|DMA_DEVICE_ID
mdefine_line|#define DMA_DEVICE_ID    0xf0000000        /* Device identification bits */
DECL|macro|DMA_VERS0
mdefine_line|#define DMA_VERS0        0x00000000        /* Sunray DMA version */
DECL|macro|DMA_ESCV1
mdefine_line|#define DMA_ESCV1        0x40000000        /* DMA ESC Version 1 */
DECL|macro|DMA_VERS1
mdefine_line|#define DMA_VERS1        0x80000000        /* DMA rev 1 */
DECL|macro|DMA_VERS2
mdefine_line|#define DMA_VERS2        0xa0000000        /* DMA rev 2 */
DECL|macro|DMA_VERHME
mdefine_line|#define DMA_VERHME       0xb0000000        /* DMA hme gate array */
DECL|macro|DMA_VERSPLUS
mdefine_line|#define DMA_VERSPLUS     0x90000000        /* DMA rev 1 PLUS */
DECL|macro|DMA_HNDL_INTR
mdefine_line|#define DMA_HNDL_INTR    0x00000001        /* An IRQ needs to be handled */
DECL|macro|DMA_HNDL_ERROR
mdefine_line|#define DMA_HNDL_ERROR   0x00000002        /* We need to take an error */
DECL|macro|DMA_FIFO_ISDRAIN
mdefine_line|#define DMA_FIFO_ISDRAIN 0x0000000c        /* The DMA FIFO is draining */
DECL|macro|DMA_INT_ENAB
mdefine_line|#define DMA_INT_ENAB     0x00000010        /* Turn on interrupts */
DECL|macro|DMA_FIFO_INV
mdefine_line|#define DMA_FIFO_INV     0x00000020        /* Invalidate the FIFO */
DECL|macro|DMA_ACC_SZ_ERR
mdefine_line|#define DMA_ACC_SZ_ERR   0x00000040        /* The access size was bad */
DECL|macro|DMA_FIFO_STDRAIN
mdefine_line|#define DMA_FIFO_STDRAIN 0x00000040        /* DMA_VERS1 Drain the FIFO */
DECL|macro|DMA_RST_SCSI
mdefine_line|#define DMA_RST_SCSI     0x00000080        /* Reset the SCSI controller */
DECL|macro|DMA_RST_ENET
mdefine_line|#define DMA_RST_ENET     DMA_RST_SCSI      /* Reset the ENET controller */
DECL|macro|DMA_ST_WRITE
mdefine_line|#define DMA_ST_WRITE     0x00000100        /* write from device to memory */
DECL|macro|DMA_ENABLE
mdefine_line|#define DMA_ENABLE       0x00000200        /* Fire up DMA, handle requests */
DECL|macro|DMA_PEND_READ
mdefine_line|#define DMA_PEND_READ    0x00000400        /* DMA_VERS1/0/PLUS Pending Read */
DECL|macro|DMA_ESC_BURST
mdefine_line|#define DMA_ESC_BURST    0x00000800        /* 1=16byte 0=32byte */
DECL|macro|DMA_READ_AHEAD
mdefine_line|#define DMA_READ_AHEAD   0x00001800        /* DMA read ahead partial longword */
DECL|macro|DMA_DSBL_RD_DRN
mdefine_line|#define DMA_DSBL_RD_DRN  0x00001000        /* No EC drain on slave reads */
DECL|macro|DMA_BCNT_ENAB
mdefine_line|#define DMA_BCNT_ENAB    0x00002000        /* If on, use the byte counter */
DECL|macro|DMA_TERM_CNTR
mdefine_line|#define DMA_TERM_CNTR    0x00004000        /* Terminal counter */
DECL|macro|DMA_CSR_DISAB
mdefine_line|#define DMA_CSR_DISAB    0x00010000        /* No FIFO drains during csr */
DECL|macro|DMA_SCSI_DISAB
mdefine_line|#define DMA_SCSI_DISAB   0x00020000        /* No FIFO drains during reg */
DECL|macro|DMA_DSBL_WR_INV
mdefine_line|#define DMA_DSBL_WR_INV  0x00020000        /* No EC inval. on slave writes */
DECL|macro|DMA_ADD_ENABLE
mdefine_line|#define DMA_ADD_ENABLE   0x00040000        /* Special ESC DVMA optimization */
DECL|macro|DMA_E_BURST8
mdefine_line|#define DMA_E_BURST8&t; 0x00040000&t;   /* ENET: SBUS r/w burst size */
DECL|macro|DMA_BRST_SZ
mdefine_line|#define DMA_BRST_SZ      0x000c0000        /* SCSI: SBUS r/w burst size */
DECL|macro|DMA_BRST64
mdefine_line|#define DMA_BRST64       0x00080000        /* SCSI: 64byte bursts (HME on UltraSparc only) */
DECL|macro|DMA_BRST32
mdefine_line|#define DMA_BRST32       0x00040000        /* SCSI: 32byte bursts */
DECL|macro|DMA_BRST16
mdefine_line|#define DMA_BRST16       0x00000000        /* SCSI: 16byte bursts */
DECL|macro|DMA_BRST0
mdefine_line|#define DMA_BRST0        0x00080000        /* SCSI: no bursts (non-HME gate arrays) */
DECL|macro|DMA_ADDR_DISAB
mdefine_line|#define DMA_ADDR_DISAB   0x00100000        /* No FIFO drains during addr */
DECL|macro|DMA_2CLKS
mdefine_line|#define DMA_2CLKS        0x00200000        /* Each transfer = 2 clock ticks */
DECL|macro|DMA_3CLKS
mdefine_line|#define DMA_3CLKS        0x00400000        /* Each transfer = 3 clock ticks */
DECL|macro|DMA_EN_ENETAUI
mdefine_line|#define DMA_EN_ENETAUI   DMA_3CLKS         /* Put lance into AUI-cable mode */
DECL|macro|DMA_CNTR_DISAB
mdefine_line|#define DMA_CNTR_DISAB   0x00800000        /* No IRQ when DMA_TERM_CNTR set */
DECL|macro|DMA_AUTO_NADDR
mdefine_line|#define DMA_AUTO_NADDR   0x01000000        /* Use &quot;auto nxt addr&quot; feature */
DECL|macro|DMA_SCSI_ON
mdefine_line|#define DMA_SCSI_ON      0x02000000        /* Enable SCSI dma */
DECL|macro|DMA_PARITY_OFF
mdefine_line|#define DMA_PARITY_OFF   0x02000000        /* HME: disable parity checking */
DECL|macro|DMA_LOADED_ADDR
mdefine_line|#define DMA_LOADED_ADDR  0x04000000        /* Address has been loaded */
DECL|macro|DMA_LOADED_NADDR
mdefine_line|#define DMA_LOADED_NADDR 0x08000000        /* Next address has been loaded */
multiline_comment|/* Values describing the burst-size property from the PROM */
DECL|macro|DMA_BURST1
mdefine_line|#define DMA_BURST1       0x01
DECL|macro|DMA_BURST2
mdefine_line|#define DMA_BURST2       0x02
DECL|macro|DMA_BURST4
mdefine_line|#define DMA_BURST4       0x04
DECL|macro|DMA_BURST8
mdefine_line|#define DMA_BURST8       0x08
DECL|macro|DMA_BURST16
mdefine_line|#define DMA_BURST16      0x10
DECL|macro|DMA_BURST32
mdefine_line|#define DMA_BURST32      0x20
DECL|macro|DMA_BURST64
mdefine_line|#define DMA_BURST64      0x40
DECL|macro|DMA_BURSTBITS
mdefine_line|#define DMA_BURSTBITS    0x7f
multiline_comment|/* Determine highest possible final transfer address given a base */
DECL|macro|DMA_MAXEND
mdefine_line|#define DMA_MAXEND(addr) (0x01000000UL-(((unsigned long)(addr))&amp;0x00ffffffUL))
multiline_comment|/* Yes, I hack a lot of elisp in my spare time... */
DECL|macro|DMA_ERROR_P
mdefine_line|#define DMA_ERROR_P(regs)  ((((regs)-&gt;cond_reg) &amp; DMA_HNDL_ERROR))
DECL|macro|DMA_IRQ_P
mdefine_line|#define DMA_IRQ_P(regs)    ((((regs)-&gt;cond_reg) &amp; (DMA_HNDL_INTR | DMA_HNDL_ERROR)))
DECL|macro|DMA_WRITE_P
mdefine_line|#define DMA_WRITE_P(regs)  ((((regs)-&gt;cond_reg) &amp; DMA_ST_WRITE))
DECL|macro|DMA_OFF
mdefine_line|#define DMA_OFF(regs)      ((((regs)-&gt;cond_reg) &amp;= (~DMA_ENABLE)))
DECL|macro|DMA_INTSOFF
mdefine_line|#define DMA_INTSOFF(regs)  ((((regs)-&gt;cond_reg) &amp;= (~DMA_INT_ENAB)))
DECL|macro|DMA_INTSON
mdefine_line|#define DMA_INTSON(regs)   ((((regs)-&gt;cond_reg) |= (DMA_INT_ENAB)))
DECL|macro|DMA_PUNTFIFO
mdefine_line|#define DMA_PUNTFIFO(regs) ((((regs)-&gt;cond_reg) |= DMA_FIFO_INV))
DECL|macro|DMA_SETSTART
mdefine_line|#define DMA_SETSTART(regs, addr)  ((((regs)-&gt;st_addr) = (char *) addr))
DECL|macro|DMA_BEGINDMA_W
mdefine_line|#define DMA_BEGINDMA_W(regs) &bslash;&n;        ((((regs)-&gt;cond_reg |= (DMA_ST_WRITE|DMA_ENABLE|DMA_INT_ENAB))))
DECL|macro|DMA_BEGINDMA_R
mdefine_line|#define DMA_BEGINDMA_R(regs) &bslash;&n;        ((((regs)-&gt;cond_reg |= ((DMA_ENABLE|DMA_INT_ENAB)&amp;(~DMA_ST_WRITE)))))
multiline_comment|/* For certain DMA chips, we need to disable ints upon irq entry&n; * and turn them back on when we are done.  So in any ESP interrupt&n; * handler you *must* call DMA_IRQ_ENTRY upon entry and DMA_IRQ_EXIT&n; * when leaving the handler.  You have been warned...&n; */
DECL|macro|DMA_IRQ_ENTRY
mdefine_line|#define DMA_IRQ_ENTRY(dma, dregs) do { &bslash;&n;        if(DMA_ISBROKEN(dma)) DMA_INTSOFF(dregs); &bslash;&n;   } while (0)
DECL|macro|DMA_IRQ_EXIT
mdefine_line|#define DMA_IRQ_EXIT(dma, dregs) do { &bslash;&n;&t;if(DMA_ISBROKEN(dma)) DMA_INTSON(dregs); &bslash;&n;   } while(0)
multiline_comment|/* Reset the friggin&squot; thing... */
DECL|macro|DMA_RESET
mdefine_line|#define DMA_RESET(dma) do { &bslash;&n;&t;struct sparc_dma_registers *regs = dma-&gt;regs;                      &bslash;&n;&t;/* Let the current FIFO drain itself */                            &bslash;&n;&t;sparc_dma_pause(regs, (DMA_FIFO_ISDRAIN));                         &bslash;&n;&t;/* Reset the logic */                                              &bslash;&n;&t;regs-&gt;cond_reg |= (DMA_RST_SCSI);     /* assert */                 &bslash;&n;&t;__delay(400);                         /* let the bits set ;) */    &bslash;&n;&t;regs-&gt;cond_reg &amp;= ~(DMA_RST_SCSI);    /* de-assert */              &bslash;&n;&t;sparc_dma_enable_interrupts(regs);    /* Re-enable interrupts */   &bslash;&n;&t;/* Enable FAST transfers if available */                           &bslash;&n;&t;if(dma-&gt;revision&gt;dvmarev1) regs-&gt;cond_reg |= DMA_3CLKS;            &bslash;&n;&t;dma-&gt;running = 0;                                                  &bslash;&n;} while(0)
macro_line|#endif /* !CONFIG_SUN3 */
macro_line|#endif /* !(__M68K_DVMA_H) */
eof
