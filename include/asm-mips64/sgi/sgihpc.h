multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * sgihpc.h: Various HPC I/O controller defines.  The HPC is basically&n; *           the approximate functional equivalent of the Sun SYSIO&n; *           on SGI INDY machines.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; * Copyright (C) 1998 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#ifndef _ASM_SGI_SGIHPC_H
DECL|macro|_ASM_SGI_SGIHPC_H
mdefine_line|#define _ASM_SGI_SGIHPC_H
macro_line|#include &lt;asm/page.h&gt;
r_extern
r_int
id|sgi_has_ioc2
suffix:semicolon
multiline_comment|/* to know if we have older ioc1 or ioc2. */
r_extern
r_int
id|sgi_guiness
suffix:semicolon
multiline_comment|/* GUINESS or FULLHOUSE machine. */
r_extern
r_int
id|sgi_boardid
suffix:semicolon
multiline_comment|/* Board revision. */
multiline_comment|/* An HPC dma descriptor. */
DECL|struct|hpc_dma_desc
r_struct
id|hpc_dma_desc
(brace
DECL|member|pbuf
r_int
id|pbuf
suffix:semicolon
multiline_comment|/* physical address of data buffer */
DECL|member|cntinfo
r_int
id|cntinfo
suffix:semicolon
multiline_comment|/* counter and info bits */
DECL|macro|HPCDMA_EOX
mdefine_line|#define HPCDMA_EOX    0x80000000 /* last desc in chain for tx */
DECL|macro|HPCDMA_EOR
mdefine_line|#define HPCDMA_EOR    0x80000000 /* last desc in chain for rx */
DECL|macro|HPCDMA_EOXP
mdefine_line|#define HPCDMA_EOXP   0x40000000 /* end of packet for tx */
DECL|macro|HPCDMA_EORP
mdefine_line|#define HPCDMA_EORP   0x40000000 /* end of packet for rx */
DECL|macro|HPCDMA_XIE
mdefine_line|#define HPCDMA_XIE    0x20000000 /* irq generated when at end of this desc */
DECL|macro|HPCDMA_XIU
mdefine_line|#define HPCDMA_XIU    0x01000000 /* Tx buffer in use by CPU. */
DECL|macro|HPCDMA_EIPC
mdefine_line|#define HPCDMA_EIPC   0x00ff0000 /* SEEQ ethernet special xternal bytecount */
DECL|macro|HPCDMA_ETXD
mdefine_line|#define HPCDMA_ETXD   0x00008000 /* set to one by HPC when packet tx&squot;d */
DECL|macro|HPCDMA_OWN
mdefine_line|#define HPCDMA_OWN    0x00004000 /* Denotes ring buffer ownership on rx */
DECL|macro|HPCDMA_BCNT
mdefine_line|#define HPCDMA_BCNT   0x00003fff /* size in bytes of this dma buffer */
DECL|member|pnext
r_int
id|pnext
suffix:semicolon
multiline_comment|/* paddr of next hpc_dma_desc if any */
)brace
suffix:semicolon
DECL|typedef|hpcreg
r_typedef
r_volatile
r_int
r_int
id|hpcreg
suffix:semicolon
multiline_comment|/* HPC1 stuff. */
multiline_comment|/* HPC3 stuff. */
multiline_comment|/* The set of regs for each HPC3 pbus dma channel. */
DECL|struct|hpc3_pbus_dmacregs
r_struct
id|hpc3_pbus_dmacregs
(brace
DECL|member|pbdma_bptr
id|hpcreg
id|pbdma_bptr
suffix:semicolon
multiline_comment|/* pbus dma channel buffer ptr */
DECL|member|pbdma_dptr
id|hpcreg
id|pbdma_dptr
suffix:semicolon
multiline_comment|/* pbus dma channel desc ptr */
DECL|member|_unused1
r_char
id|_unused1
(braket
id|PAGE_SIZE
op_minus
(paren
l_int|2
op_star
r_sizeof
(paren
id|hpcreg
)paren
)paren
)braket
suffix:semicolon
multiline_comment|/* padding */
DECL|member|pbdma_ctrl
id|hpcreg
id|pbdma_ctrl
suffix:semicolon
multiline_comment|/* pbus dma channel control reg */
DECL|macro|HPC3_PDMACTRL_SEL
mdefine_line|#define HPC3_PDMACTRL_SEL  0x00000002 /* little endian transfer */
DECL|macro|HPC3_PDMACTRL_RCV
mdefine_line|#define HPC3_PDMACTRL_RCV  0x00000004 /* direction is receive */
DECL|macro|HPC3_PDMACTRL_FLSH
mdefine_line|#define HPC3_PDMACTRL_FLSH 0x00000008 /* enable flush for receive DMA */
DECL|macro|HPC3_PDMACTRL_ACT
mdefine_line|#define HPC3_PDMACTRL_ACT  0x00000010 /* start dma transfer */
DECL|macro|HPC3_PDMACTRL_LD
mdefine_line|#define HPC3_PDMACTRL_LD   0x00000020 /* load enable for ACT */
DECL|macro|HPC3_PDMACTRL_RT
mdefine_line|#define HPC3_PDMACTRL_RT   0x00000040 /* Use realtime GIO bus servicing */
DECL|macro|HPC3_PDMACTRL_HW
mdefine_line|#define HPC3_PDMACTRL_HW   0x0000ff00 /* DMA High-water mark */
DECL|macro|HPC3_PDMACTRL_FB
mdefine_line|#define HPC3_PDMACTRL_FB   0x003f0000 /* Ptr to beginning of fifo */
DECL|macro|HPC3_PDMACTRL_FE
mdefine_line|#define HPC3_PDMACTRL_FE   0x3f000000 /* Ptr to end of fifo */
DECL|member|_unused2
r_char
id|_unused2
(braket
id|PAGE_SIZE
op_minus
(paren
r_sizeof
(paren
id|hpcreg
)paren
)paren
)braket
suffix:semicolon
multiline_comment|/* padding */
)brace
suffix:semicolon
multiline_comment|/* The HPC3 scsi registers, this does not include external ones. */
DECL|struct|hpc3_scsiregs
r_struct
id|hpc3_scsiregs
(brace
DECL|member|cbptr
id|hpcreg
id|cbptr
suffix:semicolon
multiline_comment|/* current dma buffer ptr, diagnostic use only */
DECL|member|ndptr
id|hpcreg
id|ndptr
suffix:semicolon
multiline_comment|/* next dma descriptor ptr */
DECL|member|_unused1
r_char
id|_unused1
(braket
id|PAGE_SIZE
op_minus
(paren
l_int|2
op_star
r_sizeof
(paren
id|hpcreg
)paren
)paren
)braket
suffix:semicolon
multiline_comment|/* padding */
DECL|member|bcd
id|hpcreg
id|bcd
suffix:semicolon
multiline_comment|/* byte count info */
DECL|macro|HPC3_SBCD_BCNTMSK
mdefine_line|#define HPC3_SBCD_BCNTMSK 0x00003fff /* bytes to transfer from/to memory */
DECL|macro|HPC3_SBCD_XIE
mdefine_line|#define HPC3_SBCD_XIE     0x00004000 /* Send IRQ when done with cur buf */
DECL|macro|HPC3_SBCD_EOX
mdefine_line|#define HPC3_SBCD_EOX     0x00008000 /* Indicates this is last buf in chain */
DECL|member|ctrl
id|hpcreg
id|ctrl
suffix:semicolon
multiline_comment|/* control register */
DECL|macro|HPC3_SCTRL_IRQ
mdefine_line|#define HPC3_SCTRL_IRQ    0x01 /* IRQ asserted, either dma done or parity */
DECL|macro|HPC3_SCTRL_ENDIAN
mdefine_line|#define HPC3_SCTRL_ENDIAN 0x02 /* DMA endian mode, 0=big 1=little */
DECL|macro|HPC3_SCTRL_DIR
mdefine_line|#define HPC3_SCTRL_DIR    0x04 /* DMA direction, 1=dev2mem 0=mem2dev */
DECL|macro|HPC3_SCTRL_FLUSH
mdefine_line|#define HPC3_SCTRL_FLUSH  0x08 /* Tells HPC3 to flush scsi fifos */
DECL|macro|HPC3_SCTRL_ACTIVE
mdefine_line|#define HPC3_SCTRL_ACTIVE 0x10 /* SCSI DMA channel is active */
DECL|macro|HPC3_SCTRL_AMASK
mdefine_line|#define HPC3_SCTRL_AMASK  0x20 /* DMA active inhibits PIO */
DECL|macro|HPC3_SCTRL_CRESET
mdefine_line|#define HPC3_SCTRL_CRESET 0x40 /* Resets dma channel and external controller */
DECL|macro|HPC3_SCTRL_PERR
mdefine_line|#define HPC3_SCTRL_PERR   0x80 /* Bad parity on HPC3 iface to scsi controller */
DECL|member|gfptr
id|hpcreg
id|gfptr
suffix:semicolon
multiline_comment|/* current GIO fifo ptr */
DECL|member|dfptr
id|hpcreg
id|dfptr
suffix:semicolon
multiline_comment|/* current device fifo ptr */
DECL|member|dconfig
id|hpcreg
id|dconfig
suffix:semicolon
multiline_comment|/* DMA configuration register */
DECL|macro|HPC3_SDCFG_HCLK
mdefine_line|#define HPC3_SDCFG_HCLK 0x00001 /* Enable DMA half clock mode */
DECL|macro|HPC3_SDCFG_D1
mdefine_line|#define HPC3_SDCFG_D1   0x00006 /* Cycles to spend in D1 state */
DECL|macro|HPC3_SDCFG_D2
mdefine_line|#define HPC3_SDCFG_D2   0x00038 /* Cycles to spend in D2 state */
DECL|macro|HPC3_SDCFG_D3
mdefine_line|#define HPC3_SDCFG_D3   0x001c0 /* Cycles to spend in D3 state */
DECL|macro|HPC3_SDCFG_HWAT
mdefine_line|#define HPC3_SDCFG_HWAT 0x00e00 /* DMA high water mark */
DECL|macro|HPC3_SDCFG_HW
mdefine_line|#define HPC3_SDCFG_HW   0x01000 /* Enable 16-bit halfword DMA accesses to scsi */
DECL|macro|HPC3_SDCFG_SWAP
mdefine_line|#define HPC3_SDCFG_SWAP 0x02000 /* Byte swap all DMA accesses */
DECL|macro|HPC3_SDCFG_EPAR
mdefine_line|#define HPC3_SDCFG_EPAR 0x04000 /* Enable parity checking for DMA */
DECL|macro|HPC3_SDCFG_POLL
mdefine_line|#define HPC3_SDCFG_POLL 0x08000 /* hd_dreq polarity control */
DECL|macro|HPC3_SDCFG_ERLY
mdefine_line|#define HPC3_SDCFG_ERLY 0x30000 /* hd_dreq behavior control bits */
DECL|member|pconfig
id|hpcreg
id|pconfig
suffix:semicolon
multiline_comment|/* PIO configuration register */
DECL|macro|HPC3_SPCFG_P3
mdefine_line|#define HPC3_SPCFG_P3   0x0003 /* Cycles to spend in P3 state */
DECL|macro|HPC3_SPCFG_P2W
mdefine_line|#define HPC3_SPCFG_P2W  0x001c /* Cycles to spend in P2 state for writes */
DECL|macro|HPC3_SPCFG_P2R
mdefine_line|#define HPC3_SPCFG_P2R  0x01e0 /* Cycles to spend in P2 state for reads */
DECL|macro|HPC3_SPCFG_P1
mdefine_line|#define HPC3_SPCFG_P1   0x0e00 /* Cycles to spend in P1 state */
DECL|macro|HPC3_SPCFG_HW
mdefine_line|#define HPC3_SPCFG_HW   0x1000 /* Enable 16-bit halfword PIO accesses to scsi */
DECL|macro|HPC3_SPCFG_SWAP
mdefine_line|#define HPC3_SPCFG_SWAP 0x2000 /* Byte swap all PIO accesses */
DECL|macro|HPC3_SPCFG_EPAR
mdefine_line|#define HPC3_SPCFG_EPAR 0x4000 /* Enable parity checking for PIO */
DECL|macro|HPC3_SPCFG_FUJI
mdefine_line|#define HPC3_SPCFG_FUJI 0x8000 /* Fujitsu scsi controller mode for faster dma/pio */
DECL|member|_unused2
r_char
id|_unused2
(braket
id|PAGE_SIZE
op_minus
(paren
l_int|6
op_star
r_sizeof
(paren
id|hpcreg
)paren
)paren
)braket
suffix:semicolon
multiline_comment|/* padding */
)brace
suffix:semicolon
multiline_comment|/* SEEQ ethernet HPC3 registers, only one seeq per HPC3. */
DECL|struct|hpc3_ethregs
r_struct
id|hpc3_ethregs
(brace
multiline_comment|/* Receiver registers. */
DECL|member|rx_cbptr
id|hpcreg
id|rx_cbptr
suffix:semicolon
multiline_comment|/* current dma buffer ptr, diagnostic use only */
DECL|member|rx_ndptr
id|hpcreg
id|rx_ndptr
suffix:semicolon
multiline_comment|/* next dma descriptor ptr */
DECL|member|_unused1
r_char
id|_unused1
(braket
id|PAGE_SIZE
op_minus
(paren
l_int|2
op_star
r_sizeof
(paren
id|hpcreg
)paren
)paren
)braket
suffix:semicolon
multiline_comment|/* padding */
DECL|member|rx_bcd
id|hpcreg
id|rx_bcd
suffix:semicolon
multiline_comment|/* byte count info */
DECL|macro|HPC3_ERXBCD_BCNTMSK
mdefine_line|#define HPC3_ERXBCD_BCNTMSK 0x00003fff /* bytes to be sent to memory */
DECL|macro|HPC3_ERXBCD_XIE
mdefine_line|#define HPC3_ERXBCD_XIE     0x20000000 /* HPC3 interrupts cpu at end of this buf */
DECL|macro|HPC3_ERXBCD_EOX
mdefine_line|#define HPC3_ERXBCD_EOX     0x80000000 /* flags this as end of descriptor chain */
DECL|member|rx_ctrl
id|hpcreg
id|rx_ctrl
suffix:semicolon
multiline_comment|/* control register */
DECL|macro|HPC3_ERXCTRL_STAT50
mdefine_line|#define HPC3_ERXCTRL_STAT50 0x0000003f /* Receive status reg bits of Seeq8003 */
DECL|macro|HPC3_ERXCTRL_STAT6
mdefine_line|#define HPC3_ERXCTRL_STAT6  0x00000040 /* Rdonly irq status */
DECL|macro|HPC3_ERXCTRL_STAT7
mdefine_line|#define HPC3_ERXCTRL_STAT7  0x00000080 /* Rdonlt old/new status bit from Seeq */
DECL|macro|HPC3_ERXCTRL_ENDIAN
mdefine_line|#define HPC3_ERXCTRL_ENDIAN 0x00000100 /* Endian for dma channel, little=1 big=0 */
DECL|macro|HPC3_ERXCTRL_ACTIVE
mdefine_line|#define HPC3_ERXCTRL_ACTIVE 0x00000200 /* Tells if DMA transfer is in progress */
DECL|macro|HPC3_ERXCTRL_AMASK
mdefine_line|#define HPC3_ERXCTRL_AMASK  0x00000400 /* Tells if ACTIVE inhibits PIO&squot;s to hpc3 */
DECL|macro|HPC3_ERXCTRL_RBO
mdefine_line|#define HPC3_ERXCTRL_RBO    0x00000800 /* Receive buffer overflow if set to 1 */
DECL|member|rx_gfptr
id|hpcreg
id|rx_gfptr
suffix:semicolon
multiline_comment|/* current GIO fifo ptr */
DECL|member|rx_dfptr
id|hpcreg
id|rx_dfptr
suffix:semicolon
multiline_comment|/* current device fifo ptr */
DECL|member|_unused2
id|hpcreg
id|_unused2
suffix:semicolon
multiline_comment|/* padding */
DECL|member|rx_reset
id|hpcreg
id|rx_reset
suffix:semicolon
multiline_comment|/* reset register */
DECL|macro|HPC3_ERXRST_CRESET
mdefine_line|#define HPC3_ERXRST_CRESET 0x1 /* Reset dma channel and external controller */
DECL|macro|HPC3_ERXRST_CLRIRQ
mdefine_line|#define HPC3_ERXRST_CLRIRQ 0x2 /* Clear channel interrupt */
DECL|macro|HPC3_ERXRST_LBACK
mdefine_line|#define HPC3_ERXRST_LBACK  0x4 /* Enable diagnostic loopback mode of Seeq8003 */
DECL|member|rx_dconfig
id|hpcreg
id|rx_dconfig
suffix:semicolon
multiline_comment|/* DMA configuration register */
DECL|macro|HPC3_ERXDCFG_D1
mdefine_line|#define HPC3_ERXDCFG_D1    0x0000f /* Cycles to spend in D1 state for PIO */
DECL|macro|HPC3_ERXDCFG_D2
mdefine_line|#define HPC3_ERXDCFG_D2    0x000f0 /* Cycles to spend in D2 state for PIO */
DECL|macro|HPC3_ERXDCFG_D3
mdefine_line|#define HPC3_ERXDCFG_D3    0x00f00 /* Cycles to spend in D3 state for PIO */
DECL|macro|HPC3_ERXDCFG_WCTRL
mdefine_line|#define HPC3_ERXDCFG_WCTRL 0x01000 /* Enable writes of desc into ex ctrl port */
DECL|macro|HPC3_ERXDCFG_FRXDC
mdefine_line|#define HPC3_ERXDCFG_FRXDC 0x02000 /* Clear eop stat bits upon rxdc, hw seeq fix */
DECL|macro|HPC3_ERXDCFG_FEOP
mdefine_line|#define HPC3_ERXDCFG_FEOP  0x04000 /* Bad packet marker timeout enable */
DECL|macro|HPC3_ERXDCFG_FIRQ
mdefine_line|#define HPC3_ERXDCFG_FIRQ  0x08000 /* Another bad packet timeout enable */
DECL|macro|HPC3_ERXDCFG_PTO
mdefine_line|#define HPC3_ERXDCFG_PTO   0x30000 /* Programmed timeout value for above two */
DECL|member|rx_pconfig
id|hpcreg
id|rx_pconfig
suffix:semicolon
multiline_comment|/* PIO configuration register */
DECL|macro|HPC3_ERXPCFG_P1
mdefine_line|#define HPC3_ERXPCFG_P1    0x000f /* Cycles to spend in P1 state for PIO */
DECL|macro|HPC3_ERXPCFG_P2
mdefine_line|#define HPC3_ERXPCFG_P2    0x00f0 /* Cycles to spend in P2 state for PIO */
DECL|macro|HPC3_ERXPCFG_P3
mdefine_line|#define HPC3_ERXPCFG_P3    0x0f00 /* Cycles to spend in P3 state for PIO */
DECL|macro|HPC3_ERXPCFG_TST
mdefine_line|#define HPC3_ERXPCFG_TST   0x1000 /* Diagnistic ram test feature bit */
DECL|member|_unused3
r_char
id|_unused3
(braket
id|PAGE_SIZE
op_minus
(paren
l_int|8
op_star
r_sizeof
(paren
id|hpcreg
)paren
)paren
)braket
suffix:semicolon
multiline_comment|/* padding */
multiline_comment|/* Transmitter registers. */
DECL|member|tx_cbptr
id|hpcreg
id|tx_cbptr
suffix:semicolon
multiline_comment|/* current dma buffer ptr, diagnostic use only */
DECL|member|tx_ndptr
id|hpcreg
id|tx_ndptr
suffix:semicolon
multiline_comment|/* next dma descriptor ptr */
DECL|member|_unused4
r_char
id|_unused4
(braket
id|PAGE_SIZE
op_minus
(paren
l_int|2
op_star
r_sizeof
(paren
id|hpcreg
)paren
)paren
)braket
suffix:semicolon
multiline_comment|/* padding */
DECL|member|tx_bcd
id|hpcreg
id|tx_bcd
suffix:semicolon
multiline_comment|/* byte count info */
DECL|macro|HPC3_ETXBCD_BCNTMSK
mdefine_line|#define HPC3_ETXBCD_BCNTMSK 0x00003fff /* bytes to be read from memory */
DECL|macro|HPC3_ETXBCD_ESAMP
mdefine_line|#define HPC3_ETXBCD_ESAMP   0x10000000 /* if set, too late to add descriptor */
DECL|macro|HPC3_ETXBCD_XIE
mdefine_line|#define HPC3_ETXBCD_XIE     0x20000000 /* Interrupt cpu at end of cur desc */
DECL|macro|HPC3_ETXBCD_EOP
mdefine_line|#define HPC3_ETXBCD_EOP     0x40000000 /* Last byte of cur buf is end of packet */
DECL|macro|HPC3_ETXBCD_EOX
mdefine_line|#define HPC3_ETXBCD_EOX     0x80000000 /* This buf is the end of desc chain */
DECL|member|tx_ctrl
id|hpcreg
id|tx_ctrl
suffix:semicolon
multiline_comment|/* control register */
DECL|macro|HPC3_ETXCTRL_STAT30
mdefine_line|#define HPC3_ETXCTRL_STAT30 0x0000000f /* Rdonly copy of seeq tx stat reg */
DECL|macro|HPC3_ETXCTRL_STAT4
mdefine_line|#define HPC3_ETXCTRL_STAT4  0x00000010 /* Indicate late collision occurred */
DECL|macro|HPC3_ETXCTRL_STAT75
mdefine_line|#define HPC3_ETXCTRL_STAT75 0x000000e0 /* Rdonly irq status from seeq */
DECL|macro|HPC3_ETXCTRL_ENDIAN
mdefine_line|#define HPC3_ETXCTRL_ENDIAN 0x00000100 /* Dma channel endian mode, 1=little 0=big */
DECL|macro|HPC3_ETXCTRL_ACTIVE
mdefine_line|#define HPC3_ETXCTRL_ACTIVE 0x00000200 /* DMA tx channel is active */
DECL|macro|HPC3_ETXCTRL_AMASK
mdefine_line|#define HPC3_ETXCTRL_AMASK  0x00000400 /* Indicates ACTIVE inhibits PIO&squot;s */
DECL|member|tx_gfptr
id|hpcreg
id|tx_gfptr
suffix:semicolon
multiline_comment|/* current GIO fifo ptr */
DECL|member|tx_dfptr
id|hpcreg
id|tx_dfptr
suffix:semicolon
multiline_comment|/* current device fifo ptr */
DECL|member|_unused5
r_char
id|_unused5
(braket
id|PAGE_SIZE
op_minus
(paren
l_int|4
op_star
r_sizeof
(paren
id|hpcreg
)paren
)paren
)braket
suffix:semicolon
multiline_comment|/* padding */
)brace
suffix:semicolon
DECL|struct|hpc3_regs
r_struct
id|hpc3_regs
(brace
multiline_comment|/* First regs for the PBUS 8 dma channels. */
DECL|member|pbdma
r_struct
id|hpc3_pbus_dmacregs
id|pbdma
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Now the HPC scsi registers, we get two scsi reg sets. */
DECL|member|scsi_chan0
DECL|member|scsi_chan1
r_struct
id|hpc3_scsiregs
id|scsi_chan0
comma
id|scsi_chan1
suffix:semicolon
multiline_comment|/* The SEEQ hpc3 ethernet dma/control registers. */
DECL|member|ethregs
r_struct
id|hpc3_ethregs
id|ethregs
suffix:semicolon
multiline_comment|/* Here are where the hpc3 fifo&squot;s can be directly accessed&n;&t; * via PIO accesses.  Under normal operation we never stick&n;&t; * our grubby paws in here so it&squot;s just padding.&n;&t; */
DECL|member|_unused1
r_char
id|_unused1
(braket
id|PAGE_SIZE
op_star
l_int|24
)braket
suffix:semicolon
multiline_comment|/* HPC3 irq status regs.  Due to a peculiar bug you need to&n;&t; * look at two different register addresses to get at all of&n;&t; * the status bits.  The first reg can only reliably report&n;&t; * bits 4:0 of the status, and the second reg can only&n;&t; * reliably report bits 9:5 of the hpc3 irq status.  I told&n;&t; * you it was a peculiar bug. ;-)&n;&t; */
DECL|member|istat0
id|hpcreg
id|istat0
suffix:semicolon
multiline_comment|/* Irq status, only bits &lt;4:0&gt; reliable. */
DECL|macro|HPC3_ISTAT_PBIMASK
mdefine_line|#define HPC3_ISTAT_PBIMASK  0x0ff  /* irq bits for pbus devs 0 --&gt; 7 */
DECL|macro|HPC3_ISTAT_SC0MASK
mdefine_line|#define HPC3_ISTAT_SC0MASK  0x100  /* irq bit for scsi channel 0 */
DECL|macro|HPC3_ISTAT_SC1MASK
mdefine_line|#define HPC3_ISTAT_SC1MASK  0x200  /* irq bit for scsi channel 1 */
DECL|member|gio64_misc
id|hpcreg
id|gio64_misc
suffix:semicolon
multiline_comment|/* GIO64 misc control bits. */
DECL|macro|HPC3_GIOMISC_ERTIME
mdefine_line|#define HPC3_GIOMISC_ERTIME   0x1    /* Enable external timer real time. */
DECL|macro|HPC3_GIOMISC_DENDIAN
mdefine_line|#define HPC3_GIOMISC_DENDIAN  0x2    /* dma descriptor endian, 1=lit 0=big */
DECL|member|eeprom_data
id|hpcreg
id|eeprom_data
suffix:semicolon
multiline_comment|/* EEPROM data reg. */
DECL|macro|HPC3_EEPROM_EPROT
mdefine_line|#define HPC3_EEPROM_EPROT     0x01   /* Protect register enable */
DECL|macro|HPC3_EEPROM_CSEL
mdefine_line|#define HPC3_EEPROM_CSEL      0x02   /* Chip select */
DECL|macro|HPC3_EEPROM_ECLK
mdefine_line|#define HPC3_EEPROM_ECLK      0x04   /* EEPROM clock */
DECL|macro|HPC3_EEPROM_DATO
mdefine_line|#define HPC3_EEPROM_DATO      0x08   /* Data out */
DECL|macro|HPC3_EEPROM_DATI
mdefine_line|#define HPC3_EEPROM_DATI      0x10   /* Data in */
DECL|member|istat1
id|hpcreg
id|istat1
suffix:semicolon
multiline_comment|/* Irq status, only bits &lt;9:5&gt; reliable. */
DECL|member|gio64_estat
id|hpcreg
id|gio64_estat
suffix:semicolon
multiline_comment|/* GIO64 error interrupt status reg. */
DECL|macro|HPC3_GIOESTAT_BLMASK
mdefine_line|#define HPC3_GIOESTAT_BLMASK  0x000ff  /* Bus lane where bad parity occurred */
DECL|macro|HPC3_GIOESTAT_CTYPE
mdefine_line|#define HPC3_GIOESTAT_CTYPE   0x00100  /* Bus cycle type, 0=PIO 1=DMA */
DECL|macro|HPC3_GIOESTAT_PIDMSK
mdefine_line|#define HPC3_GIOESTAT_PIDMSK  0x3f700  /* DMA channel parity identifier */
multiline_comment|/* Now direct PIO per-HPC3 peripheral access to external regs. */
DECL|member|_unused2
r_char
id|_unused2
(braket
l_int|0x13fec
)braket
suffix:semicolon
multiline_comment|/* Trust me... */
DECL|member|scsi0_ext
id|hpcreg
id|scsi0_ext
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* SCSI channel 0 external regs */
DECL|member|_unused3
r_char
id|_unused3
(braket
l_int|0x07c00
)braket
suffix:semicolon
multiline_comment|/* Trust me... */
DECL|member|scsi1_ext
id|hpcreg
id|scsi1_ext
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* SCSI channel 1 external regs */
DECL|member|_unused4
r_char
id|_unused4
(braket
l_int|0x07c00
)braket
suffix:semicolon
multiline_comment|/* It&squot;ll only hurt a little... */
multiline_comment|/* Did DaveM forget the ethernet external regs?&n;&t; * Anyhow, they&squot;re not here and we need some padding instead.&n;&t; */
DECL|member|_unused5
r_char
id|_unused5
(braket
l_int|0x04000
)braket
suffix:semicolon
multiline_comment|/* It&squot;ll hurt a lot if you leave this out */
multiline_comment|/* Per-peripheral device external registers and dma/pio control. */
DECL|member|pbus_extregs
id|hpcreg
id|pbus_extregs
(braket
l_int|16
)braket
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* 2nd indice indexes controller */
DECL|member|pbus_dmacfgs
id|hpcreg
id|pbus_dmacfgs
(braket
l_int|8
)braket
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* 2nd indice indexes controller */
DECL|macro|HPC3_PIODCFG_D3R
mdefine_line|#define HPC3_PIODCFG_D3R    0x00000001 /* Cycles to spend in D3 for reads */
DECL|macro|HPC3_PIODCFG_D4R
mdefine_line|#define HPC3_PIODCFG_D4R    0x0000001e /* Cycles to spend in D4 for reads */
DECL|macro|HPC3_PIODCFG_D5R
mdefine_line|#define HPC3_PIODCFG_D5R    0x000001e0 /* Cycles to spend in D5 for reads */
DECL|macro|HPC3_PIODCFG_D3W
mdefine_line|#define HPC3_PIODCFG_D3W    0x00000200 /* Cycles to spend in D3 for writes */
DECL|macro|HPC3_PIODCFG_D4W
mdefine_line|#define HPC3_PIODCFG_D4W    0x00003c00 /* Cycles to spend in D4 for writes */
DECL|macro|HPC3_PIODCFG_D5W
mdefine_line|#define HPC3_PIODCFG_D5W    0x0003c000 /* Cycles to spend in D5 for writes */
DECL|macro|HPC3_PIODCFG_HWORD
mdefine_line|#define HPC3_PIODCFG_HWORD  0x00040000 /* Enable 16-bit dma access mode */
DECL|macro|HPC3_PIODCFG_EHI
mdefine_line|#define HPC3_PIODCFG_EHI    0x00080000 /* Places halfwords on high 16 bits of bus */
DECL|macro|HPC3_PIODCFG_RTIME
mdefine_line|#define HPC3_PIODCFG_RTIME  0x00200000 /* Make this device real time on GIO bus */
DECL|macro|HPC3_PIODCFG_BURST
mdefine_line|#define HPC3_PIODCFG_BURST  0x07c00000 /* 5 bit burst count for DMA device */
DECL|macro|HPC3_PIODCFG_DRQLV
mdefine_line|#define HPC3_PIODCFG_DRQLV  0x08000000 /* Use live pbus_dreq unsynchronized signal */
DECL|member|pbus_piocfgs
id|hpcreg
id|pbus_piocfgs
(braket
l_int|64
)braket
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* 2nd indice indexes controller */
DECL|macro|HPC3_PIOPCFG_RP2
mdefine_line|#define HPC3_PIOPCFG_RP2    0x00001  /* Cycles to spend in P2 state for reads */
DECL|macro|HPC3_PIOPCFG_RP3
mdefine_line|#define HPC3_PIOPCFG_RP3    0x0001e  /* Cycles to spend in P3 state for reads */
DECL|macro|HPC3_PIOPCFG_RP4
mdefine_line|#define HPC3_PIOPCFG_RP4    0x001e0  /* Cycles to spend in P4 state for reads */
DECL|macro|HPC3_PIOPCFG_WP2
mdefine_line|#define HPC3_PIOPCFG_WP2    0x00200  /* Cycles to spend in P2 state for writes */
DECL|macro|HPC3_PIOPCFG_WP3
mdefine_line|#define HPC3_PIOPCFG_WP3    0x03c00  /* Cycles to spend in P3 state for writes */
DECL|macro|HPC3_PIOPCFG_WP4
mdefine_line|#define HPC3_PIOPCFG_WP4    0x3c000  /* Cycles to spend in P4 state for writes */
DECL|macro|HPC3_PIOPCFG_HW
mdefine_line|#define HPC3_PIOPCFG_HW     0x40000  /* Enable 16-bit PIO accesses */
DECL|macro|HPC3_PIOPCFG_EHI
mdefine_line|#define HPC3_PIOPCFG_EHI    0x80000  /* Place even address bits in bits &lt;15:8&gt; */
multiline_comment|/* PBUS PROM control regs. */
DECL|member|pbus_promwe
id|hpcreg
id|pbus_promwe
suffix:semicolon
multiline_comment|/* PROM write enable register */
DECL|macro|HPC3_PROM_WENAB
mdefine_line|#define HPC3_PROM_WENAB     0x1 /* Enable writes to the PROM */
DECL|member|_unused6
r_char
id|_unused6
(braket
l_int|0x800
op_minus
r_sizeof
(paren
id|hpcreg
)paren
)braket
suffix:semicolon
DECL|member|pbus_promswap
id|hpcreg
id|pbus_promswap
suffix:semicolon
multiline_comment|/* Chip select swap reg */
DECL|macro|HPC3_PROM_SWAP
mdefine_line|#define HPC3_PROM_SWAP      0x1 /* invert GIO addr bit to select prom0 or prom1 */
DECL|member|_unused7
r_char
id|_unused7
(braket
l_int|0x800
op_minus
r_sizeof
(paren
id|hpcreg
)paren
)braket
suffix:semicolon
DECL|member|pbus_gout
id|hpcreg
id|pbus_gout
suffix:semicolon
multiline_comment|/* PROM general purpose output reg */
DECL|macro|HPC3_PROM_STAT
mdefine_line|#define HPC3_PROM_STAT      0x1 /* General purpose status bit in gout */
DECL|member|_unused8
r_char
id|_unused8
(braket
l_int|0x1000
op_minus
r_sizeof
(paren
id|hpcreg
)paren
)braket
suffix:semicolon
DECL|member|pbus_promram
id|hpcreg
id|pbus_promram
(braket
l_int|16384
)braket
suffix:semicolon
multiline_comment|/* 64k of PROM battery backed ram */
)brace
suffix:semicolon
multiline_comment|/* It is possible to have two HPC3&squot;s within the address space on&n; * one machine, though only having one is more likely on an INDY.&n; * Controller 0 lives at physical address 0x1fb80000 and the controller&n; * 1 if present lives at address 0x1fb00000.&n; */
r_extern
r_struct
id|hpc3_regs
op_star
id|hpc3c0
comma
op_star
id|hpc3c1
suffix:semicolon
DECL|macro|HPC3_CHIP0_PBASE
mdefine_line|#define HPC3_CHIP0_PBASE   0x1fb80000 /* physical */
DECL|macro|HPC3_CHIP1_PBASE
mdefine_line|#define HPC3_CHIP1_PBASE   0x1fb00000 /* physical */
multiline_comment|/* Control and misc status information, these live in pbus channel 6. */
DECL|struct|hpc3_miscregs
r_struct
id|hpc3_miscregs
(brace
DECL|member|pdata
DECL|member|pctrl
DECL|member|pstat
DECL|member|pdmactrl
DECL|member|pistat
DECL|member|pimask
id|hpcreg
id|pdata
comma
id|pctrl
comma
id|pstat
comma
id|pdmactrl
comma
id|pistat
comma
id|pimask
suffix:semicolon
DECL|member|ptimer1
DECL|member|ptimer2
DECL|member|ptimer3
DECL|member|ptimer4
id|hpcreg
id|ptimer1
comma
id|ptimer2
comma
id|ptimer3
comma
id|ptimer4
suffix:semicolon
DECL|member|_unused1
id|hpcreg
id|_unused1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ser1cmd
DECL|member|ser1data
id|hpcreg
id|ser1cmd
comma
id|ser1data
suffix:semicolon
DECL|member|ser0cmd
DECL|member|ser0data
id|hpcreg
id|ser0cmd
comma
id|ser0data
suffix:semicolon
DECL|member|kbdmouse0
DECL|member|kbdmouse1
id|hpcreg
id|kbdmouse0
comma
id|kbdmouse1
suffix:semicolon
DECL|member|gcsel
DECL|member|genctrl
DECL|member|panel
id|hpcreg
id|gcsel
comma
id|genctrl
comma
id|panel
suffix:semicolon
DECL|member|_unused2
id|hpcreg
id|_unused2
suffix:semicolon
DECL|member|sysid
id|hpcreg
id|sysid
suffix:semicolon
DECL|member|_unused3
id|hpcreg
id|_unused3
suffix:semicolon
DECL|member|read
DECL|member|_unused4
id|hpcreg
id|read
comma
id|_unused4
suffix:semicolon
DECL|member|dselect
id|hpcreg
id|dselect
suffix:semicolon
DECL|macro|HPC3_DSELECT_SCLK10MHZ
mdefine_line|#define HPC3_DSELECT_SCLK10MHZ   0x00 /* use 10MHZ serial clock */
DECL|macro|HPC3_DSELECT_ISDNB
mdefine_line|#define HPC3_DSELECT_ISDNB       0x01 /* enable isdn B */
DECL|macro|HPC3_DSELECT_ISDNA
mdefine_line|#define HPC3_DSELECT_ISDNA       0x02 /* enable isdn A */
DECL|macro|HPC3_DSELECT_LPR
mdefine_line|#define HPC3_DSELECT_LPR         0x04 /* use parallel DMA */
DECL|macro|HPC3_DSELECT_SCLK667MHZ
mdefine_line|#define HPC3_DSELECT_SCLK667MHZ  0x10 /* use 6.67MHZ serial clock */
DECL|macro|HPC3_DSELECT_SCLKEXT
mdefine_line|#define HPC3_DSELECT_SCLKEXT     0x20 /* use external serial clock */
DECL|member|_unused5
id|hpcreg
id|_unused5
suffix:semicolon
DECL|member|write1
id|hpcreg
id|write1
suffix:semicolon
DECL|macro|HPC3_WRITE1_PRESET
mdefine_line|#define HPC3_WRITE1_PRESET    0x01  /* 0=LPR_RESET, 1=NORMAL */
DECL|macro|HPC3_WRITE1_KMRESET
mdefine_line|#define HPC3_WRITE1_KMRESET   0x02  /* 0=KBDMOUSE_RESET, 1=NORMAL */
DECL|macro|HPC3_WRITE1_ERESET
mdefine_line|#define HPC3_WRITE1_ERESET    0x04  /* 0=EISA_RESET, 1=NORMAL */
DECL|macro|HPC3_WRITE1_GRESET
mdefine_line|#define HPC3_WRITE1_GRESET    0x08  /* 0=MAGIC_GIO_RESET, 1=NORMAL */
DECL|macro|HPC3_WRITE1_LC0OFF
mdefine_line|#define HPC3_WRITE1_LC0OFF    0x10  /* turn led off (guiness=red, else green) */
DECL|macro|HPC3_WRITE1_LC1OFF
mdefine_line|#define HPC3_WRITE1_LC1OFF    0x20  /* turn led off (guiness=green, else amber) */
DECL|member|_unused6
id|hpcreg
id|_unused6
suffix:semicolon
DECL|member|write2
id|hpcreg
id|write2
suffix:semicolon
DECL|macro|HPC3_WRITE2_NTHRESH
mdefine_line|#define HPC3_WRITE2_NTHRESH  0x01 /* use 4.5db threshhold */
DECL|macro|HPC3_WRITE2_TPSPEED
mdefine_line|#define HPC3_WRITE2_TPSPEED  0x02 /* use 100ohm TP speed */
DECL|macro|HPC3_WRITE2_EPSEL
mdefine_line|#define HPC3_WRITE2_EPSEL    0x04 /* force cable mode: 1=AUI 0=TP */
DECL|macro|HPC3_WRITE2_EASEL
mdefine_line|#define HPC3_WRITE2_EASEL    0x08 /* 1=autoselect 0=manual cable selection */
DECL|macro|HPC3_WRITE2_U1AMODE
mdefine_line|#define HPC3_WRITE2_U1AMODE  0x10 /* 1=PC 0=MAC UART mode */
DECL|macro|HPC3_WRITE2_U0AMODE
mdefine_line|#define HPC3_WRITE2_U0AMODE  0x20 /* 1=PC 0=MAC UART mode */
DECL|macro|HPC3_WRITE2_MLO
mdefine_line|#define HPC3_WRITE2_MLO      0x40 /* 1=4.75V 0=+5V */
DECL|macro|HPC3_WRITE2_MHI
mdefine_line|#define HPC3_WRITE2_MHI      0x80 /* 1=5.25V 0=+5V */
)brace
suffix:semicolon
r_extern
r_struct
id|hpc3_miscregs
op_star
id|hpc3mregs
suffix:semicolon
DECL|macro|HPC3_MREGS_PBASE
mdefine_line|#define HPC3_MREGS_PBASE   0x1fbd9800 /* physical */
multiline_comment|/* We need software copies of these because they are write only. */
r_extern
r_int
r_int
id|sgi_hpc_write1
comma
id|sgi_hpc_write2
suffix:semicolon
DECL|struct|hpc_keyb
r_struct
id|hpc_keyb
(brace
macro_line|#ifdef __MIPSEB__
DECL|member|_unused0
r_int
r_char
id|_unused0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|data
r_volatile
r_int
r_char
id|data
suffix:semicolon
DECL|member|_unused1
r_int
r_char
id|_unused1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|command
r_volatile
r_int
r_char
id|command
suffix:semicolon
macro_line|#else
r_volatile
r_int
r_char
id|data
suffix:semicolon
r_int
r_char
id|_unused0
(braket
l_int|3
)braket
suffix:semicolon
r_volatile
r_int
r_char
id|command
suffix:semicolon
r_int
r_char
id|_unused1
(braket
l_int|3
)braket
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* Indy RTC  */
multiline_comment|/* The layout of registers for the INDY Dallas 1286 clock chipset. */
DECL|struct|indy_clock
r_struct
id|indy_clock
(brace
DECL|member|hsec
r_volatile
r_int
r_int
id|hsec
suffix:semicolon
DECL|member|sec
r_volatile
r_int
r_int
id|sec
suffix:semicolon
DECL|member|min
r_volatile
r_int
r_int
id|min
suffix:semicolon
DECL|member|malarm
r_volatile
r_int
r_int
id|malarm
suffix:semicolon
DECL|member|hr
r_volatile
r_int
r_int
id|hr
suffix:semicolon
DECL|member|halarm
r_volatile
r_int
r_int
id|halarm
suffix:semicolon
DECL|member|day
r_volatile
r_int
r_int
id|day
suffix:semicolon
DECL|member|dalarm
r_volatile
r_int
r_int
id|dalarm
suffix:semicolon
DECL|member|date
r_volatile
r_int
r_int
id|date
suffix:semicolon
DECL|member|month
r_volatile
r_int
r_int
id|month
suffix:semicolon
DECL|member|year
r_volatile
r_int
r_int
id|year
suffix:semicolon
DECL|member|cmd
r_volatile
r_int
r_int
id|cmd
suffix:semicolon
DECL|member|whsec
r_volatile
r_int
r_int
id|whsec
suffix:semicolon
DECL|member|wsec
r_volatile
r_int
r_int
id|wsec
suffix:semicolon
DECL|member|_unused0
r_volatile
r_int
r_int
id|_unused0
(braket
l_int|50
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INDY_CLOCK_REGS
mdefine_line|#define INDY_CLOCK_REGS (KSEG1ADDR(0x1fbe0000))
r_extern
r_void
id|sgihpc_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _ASM_SGI_SGIHPC_H */
eof
