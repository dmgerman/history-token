multiline_comment|/* $Id: dma.h,v 1.21 2001/12/13 04:16:52 davem Exp $&n; * include/asm-sparc64/dma.h&n; *&n; * Copyright 1996 (C) David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _ASM_SPARC64_DMA_H
DECL|macro|_ASM_SPARC64_DMA_H
mdefine_line|#define _ASM_SPARC64_DMA_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
r_extern
id|spinlock_t
id|dma_spin_lock
suffix:semicolon
DECL|macro|claim_dma_lock
mdefine_line|#define claim_dma_lock() &bslash;&n;({&t;unsigned long flags; &bslash;&n;&t;spin_lock_irqsave(&amp;dma_spin_lock, flags); &bslash;&n;&t;flags; &bslash;&n;})
DECL|macro|release_dma_lock
mdefine_line|#define release_dma_lock(__flags) &bslash;&n;&t;spin_unlock_irqrestore(&amp;dma_spin_lock, __flags);
multiline_comment|/* These are irrelevant for Sparc DMA, but we leave it in so that&n; * things can compile.&n; */
DECL|macro|MAX_DMA_CHANNELS
mdefine_line|#define MAX_DMA_CHANNELS 8
DECL|macro|DMA_MODE_READ
mdefine_line|#define DMA_MODE_READ    1
DECL|macro|DMA_MODE_WRITE
mdefine_line|#define DMA_MODE_WRITE   2
DECL|macro|MAX_DMA_ADDRESS
mdefine_line|#define MAX_DMA_ADDRESS  (~0UL)
multiline_comment|/* Useful constants */
DECL|macro|SIZE_16MB
mdefine_line|#define SIZE_16MB      (16*1024*1024)
DECL|macro|SIZE_64K
mdefine_line|#define SIZE_64K       (64*1024)
multiline_comment|/* SBUS DMA controller reg offsets */
DECL|macro|DMA_CSR
mdefine_line|#define DMA_CSR&t;&t;0x00UL&t;&t;/* rw  DMA control/status register    0x00   */
DECL|macro|DMA_ADDR
mdefine_line|#define DMA_ADDR&t;0x04UL&t;&t;/* rw  DMA transfer address register  0x04   */
DECL|macro|DMA_COUNT
mdefine_line|#define DMA_COUNT&t;0x08UL&t;&t;/* rw  DMA transfer count register    0x08   */
DECL|macro|DMA_TEST
mdefine_line|#define DMA_TEST&t;0x0cUL&t;&t;/* rw  DMA test/debug register        0x0c   */
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
DECL|struct|sbus_dma
r_struct
id|sbus_dma
(brace
DECL|member|next
r_struct
id|sbus_dma
op_star
id|next
suffix:semicolon
DECL|member|sdev
r_struct
id|sbus_dev
op_star
id|sdev
suffix:semicolon
DECL|member|regs
r_int
r_int
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
id|u32
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
id|sbus_dma
op_star
id|dma_chain
suffix:semicolon
multiline_comment|/* Broken hardware... */
DECL|macro|DMA_ISBROKEN
mdefine_line|#define DMA_ISBROKEN(dma)    ((dma)-&gt;revision == dvmarev1)
DECL|macro|DMA_ISESC1
mdefine_line|#define DMA_ISESC1(dma)      ((dma)-&gt;revision == dvmaesc1)
multiline_comment|/* Main routines in dma.c */
r_extern
r_void
id|dvma_init
c_func
(paren
r_struct
id|sbus_bus
op_star
)paren
suffix:semicolon
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
DECL|macro|DMA_SCSI_SBUS64
mdefine_line|#define DMA_SCSI_SBUS64  0x00008000        /* HME: Enable 64-bit SBUS mode. */
DECL|macro|DMA_CSR_DISAB
mdefine_line|#define DMA_CSR_DISAB    0x00010000        /* No FIFO drains during csr */
DECL|macro|DMA_SCSI_DISAB
mdefine_line|#define DMA_SCSI_DISAB   0x00020000        /* No FIFO drains during reg */
DECL|macro|DMA_DSBL_WR_INV
mdefine_line|#define DMA_DSBL_WR_INV  0x00020000        /* No EC inval. on slave writes */
DECL|macro|DMA_ADD_ENABLE
mdefine_line|#define DMA_ADD_ENABLE   0x00040000        /* Special ESC DVMA optimization */
DECL|macro|DMA_E_BURSTS
mdefine_line|#define DMA_E_BURSTS&t; 0x000c0000&t;   /* ENET: SBUS r/w burst mask */
DECL|macro|DMA_E_BURST32
mdefine_line|#define DMA_E_BURST32&t; 0x00040000&t;   /* ENET: SBUS 32 byte r/w burst */
DECL|macro|DMA_E_BURST16
mdefine_line|#define DMA_E_BURST16&t; 0x00000000&t;   /* ENET: SBUS 16 byte r/w burst */
DECL|macro|DMA_BRST_SZ
mdefine_line|#define DMA_BRST_SZ      0x000c0000        /* SCSI: SBUS r/w burst size */
DECL|macro|DMA_BRST64
mdefine_line|#define DMA_BRST64       0x000c0000        /* SCSI: 64byte bursts (HME on UltraSparc only) */
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
DECL|macro|DMA_RESET_FAS366
mdefine_line|#define DMA_RESET_FAS366 0x08000000        /* HME: Assert RESET to FAS366 */
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
mdefine_line|#define DMA_ERROR_P(regs)  (((sbus_readl((regs) + DMA_CSR) &amp; DMA_HNDL_ERROR))
DECL|macro|DMA_IRQ_P
mdefine_line|#define DMA_IRQ_P(regs)    (((sbus_readl((regs) + DMA_CSR)) &amp; (DMA_HNDL_INTR | DMA_HNDL_ERROR)))
DECL|macro|DMA_WRITE_P
mdefine_line|#define DMA_WRITE_P(regs)  (((sbus_readl((regs) + DMA_CSR) &amp; DMA_ST_WRITE))
DECL|macro|DMA_OFF
mdefine_line|#define DMA_OFF(__regs)&t;&t;&bslash;&n;do {&t;u32 tmp = sbus_readl((__regs) + DMA_CSR); &bslash;&n;&t;tmp &amp;= ~DMA_ENABLE; &bslash;&n;&t;sbus_writel(tmp, (__regs) + DMA_CSR); &bslash;&n;} while(0)
DECL|macro|DMA_INTSOFF
mdefine_line|#define DMA_INTSOFF(__regs)&t;&bslash;&n;do {&t;u32 tmp = sbus_readl((__regs) + DMA_CSR); &bslash;&n;&t;tmp &amp;= ~DMA_INT_ENAB; &bslash;&n;&t;sbus_writel(tmp, (__regs) + DMA_CSR); &bslash;&n;} while(0)
DECL|macro|DMA_INTSON
mdefine_line|#define DMA_INTSON(__regs)&t;&bslash;&n;do {&t;u32 tmp = sbus_readl((__regs) + DMA_CSR); &bslash;&n;&t;tmp |= DMA_INT_ENAB; &bslash;&n;&t;sbus_writel(tmp, (__regs) + DMA_CSR); &bslash;&n;} while(0)
DECL|macro|DMA_PUNTFIFO
mdefine_line|#define DMA_PUNTFIFO(__regs)&t;&bslash;&n;do {&t;u32 tmp = sbus_readl((__regs) + DMA_CSR); &bslash;&n;&t;tmp |= DMA_FIFO_INV; &bslash;&n;&t;sbus_writel(tmp, (__regs) + DMA_CSR); &bslash;&n;} while(0)
DECL|macro|DMA_SETSTART
mdefine_line|#define DMA_SETSTART(__regs, __addr)&t;&bslash;&n;&t;sbus_writel((u32)(__addr), (__regs) + DMA_ADDR);
DECL|macro|DMA_BEGINDMA_W
mdefine_line|#define DMA_BEGINDMA_W(__regs)&t;&bslash;&n;do {&t;u32 tmp = sbus_readl((__regs) + DMA_CSR); &bslash;&n;&t;tmp |= (DMA_ST_WRITE|DMA_ENABLE|DMA_INT_ENAB); &bslash;&n;&t;sbus_writel(tmp, (__regs) + DMA_CSR); &bslash;&n;} while(0)
DECL|macro|DMA_BEGINDMA_R
mdefine_line|#define DMA_BEGINDMA_R(__regs)&t;&bslash;&n;do {&t;u32 tmp = sbus_readl((__regs) + DMA_CSR); &bslash;&n;&t;tmp |= (DMA_ENABLE|DMA_INT_ENAB); &bslash;&n;&t;tmp &amp;= ~DMA_ST_WRITE; &bslash;&n;&t;sbus_writel(tmp, (__regs) + DMA_CSR); &bslash;&n;} while(0)
multiline_comment|/* For certain DMA chips, we need to disable ints upon irq entry&n; * and turn them back on when we are done.  So in any ESP interrupt&n; * handler you *must* call DMA_IRQ_ENTRY upon entry and DMA_IRQ_EXIT&n; * when leaving the handler.  You have been warned...&n; */
DECL|macro|DMA_IRQ_ENTRY
mdefine_line|#define DMA_IRQ_ENTRY(dma, dregs) do { &bslash;&n;        if(DMA_ISBROKEN(dma)) DMA_INTSOFF(dregs); &bslash;&n;   } while (0)
DECL|macro|DMA_IRQ_EXIT
mdefine_line|#define DMA_IRQ_EXIT(dma, dregs) do { &bslash;&n;&t;if(DMA_ISBROKEN(dma)) DMA_INTSON(dregs); &bslash;&n;   } while(0)
DECL|macro|for_each_dvma
mdefine_line|#define for_each_dvma(dma) &bslash;&n;        for((dma) = dma_chain; (dma); (dma) = (dma)-&gt;next)
r_extern
r_int
id|get_dma_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|request_dma
c_func
(paren
r_int
r_int
comma
id|__const__
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|free_dma
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* From PCI */
macro_line|#ifdef CONFIG_PCI
r_extern
r_int
id|isa_dma_bridge_buggy
suffix:semicolon
macro_line|#else
DECL|macro|isa_dma_bridge_buggy
mdefine_line|#define isa_dma_bridge_buggy &t;(0)
macro_line|#endif
macro_line|#endif /* !(_ASM_SPARC64_DMA_H) */
eof
