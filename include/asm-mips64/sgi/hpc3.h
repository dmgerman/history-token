multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License. See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * hpc3.h: Definitions for SGI HPC3 controller&n; *&n; * Copyright (C) 1996 David S. Miller&n; * Copyright (C) 1998 Ralf Baechle&n; */
macro_line|#ifndef _SGI_HPC3_H
DECL|macro|_SGI_HPC3_H
mdefine_line|#define _SGI_HPC3_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* An HPC DMA descriptor. */
DECL|struct|hpc_dma_desc
r_struct
id|hpc_dma_desc
(brace
DECL|member|pbuf
id|u32
id|pbuf
suffix:semicolon
multiline_comment|/* physical address of data buffer */
DECL|member|cntinfo
id|u32
id|cntinfo
suffix:semicolon
multiline_comment|/* counter and info bits */
DECL|macro|HPCDMA_EOX
mdefine_line|#define HPCDMA_EOX&t;0x80000000 /* last desc in chain for tx */
DECL|macro|HPCDMA_EOR
mdefine_line|#define HPCDMA_EOR&t;0x80000000 /* last desc in chain for rx */
DECL|macro|HPCDMA_EOXP
mdefine_line|#define HPCDMA_EOXP&t;0x40000000 /* end of packet for tx */
DECL|macro|HPCDMA_EORP
mdefine_line|#define HPCDMA_EORP&t;0x40000000 /* end of packet for rx */
DECL|macro|HPCDMA_XIE
mdefine_line|#define HPCDMA_XIE&t;0x20000000 /* irq generated when at end of this desc */
DECL|macro|HPCDMA_XIU
mdefine_line|#define HPCDMA_XIU&t;0x01000000 /* Tx buffer in use by CPU. */
DECL|macro|HPCDMA_EIPC
mdefine_line|#define HPCDMA_EIPC&t;0x00ff0000 /* SEEQ ethernet special xternal bytecount */
DECL|macro|HPCDMA_ETXD
mdefine_line|#define HPCDMA_ETXD&t;0x00008000 /* set to one by HPC when packet tx&squot;d */
DECL|macro|HPCDMA_OWN
mdefine_line|#define HPCDMA_OWN&t;0x00004000 /* Denotes ring buffer ownership on rx */
DECL|macro|HPCDMA_BCNT
mdefine_line|#define HPCDMA_BCNT&t;0x00003fff /* size in bytes of this dma buffer */
DECL|member|pnext
id|u32
id|pnext
suffix:semicolon
multiline_comment|/* paddr of next hpc_dma_desc if any */
)brace
suffix:semicolon
multiline_comment|/* The set of regs for each HPC3 PBUS DMA channel. */
DECL|struct|hpc3_pbus_dmacregs
r_struct
id|hpc3_pbus_dmacregs
(brace
DECL|member|pbdma_bptr
r_volatile
id|u32
id|pbdma_bptr
suffix:semicolon
multiline_comment|/* pbus dma channel buffer ptr */
DECL|member|pbdma_dptr
r_volatile
id|u32
id|pbdma_dptr
suffix:semicolon
multiline_comment|/* pbus dma channel desc ptr */
DECL|member|_unused0
id|u32
id|_unused0
(braket
l_int|0x1000
op_div
l_int|4
op_minus
l_int|2
)braket
suffix:semicolon
multiline_comment|/* padding */
DECL|member|pbdma_ctrl
r_volatile
id|u32
id|pbdma_ctrl
suffix:semicolon
multiline_comment|/* pbus dma channel control register has&n;&t;&t;&t;&t;&t; * copletely different meaning for read&n;&t;&t;&t;&t;&t; * compared with write */
multiline_comment|/* read */
DECL|macro|HPC3_PDMACTRL_INT
mdefine_line|#define HPC3_PDMACTRL_INT&t;0x00000001 /* interrupt (cleared after read) */
DECL|macro|HPC3_PDMACTRL_ISACT
mdefine_line|#define HPC3_PDMACTRL_ISACT&t;0x00000002 /* channel active */
multiline_comment|/* write */
DECL|macro|HPC3_PDMACTRL_SEL
mdefine_line|#define HPC3_PDMACTRL_SEL&t;0x00000002 /* little endian transfer */
DECL|macro|HPC3_PDMACTRL_RCV
mdefine_line|#define HPC3_PDMACTRL_RCV&t;0x00000004 /* direction is receive */
DECL|macro|HPC3_PDMACTRL_FLSH
mdefine_line|#define HPC3_PDMACTRL_FLSH&t;0x00000008 /* enable flush for receive DMA */
DECL|macro|HPC3_PDMACTRL_ACT
mdefine_line|#define HPC3_PDMACTRL_ACT&t;0x00000010 /* start dma transfer */
DECL|macro|HPC3_PDMACTRL_LD
mdefine_line|#define HPC3_PDMACTRL_LD&t;0x00000020 /* load enable for ACT */
DECL|macro|HPC3_PDMACTRL_RT
mdefine_line|#define HPC3_PDMACTRL_RT&t;0x00000040 /* Use realtime GIO bus servicing */
DECL|macro|HPC3_PDMACTRL_HW
mdefine_line|#define HPC3_PDMACTRL_HW&t;0x0000ff00 /* DMA High-water mark */
DECL|macro|HPC3_PDMACTRL_FB
mdefine_line|#define HPC3_PDMACTRL_FB&t;0x003f0000 /* Ptr to beginning of fifo */
DECL|macro|HPC3_PDMACTRL_FE
mdefine_line|#define HPC3_PDMACTRL_FE&t;0x3f000000 /* Ptr to end of fifo */
DECL|member|_unused1
id|u32
id|_unused1
(braket
l_int|0x1000
op_div
l_int|4
op_minus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* padding */
)brace
suffix:semicolon
multiline_comment|/* The HPC3 SCSI registers, this does not include external ones. */
DECL|struct|hpc3_scsiregs
r_struct
id|hpc3_scsiregs
(brace
DECL|member|cbptr
r_volatile
id|u32
id|cbptr
suffix:semicolon
multiline_comment|/* current dma buffer ptr, diagnostic use only */
DECL|member|ndptr
r_volatile
id|u32
id|ndptr
suffix:semicolon
multiline_comment|/* next dma descriptor ptr */
DECL|member|_unused0
id|u32
id|_unused0
(braket
l_int|0x1000
op_div
l_int|4
op_minus
l_int|2
)braket
suffix:semicolon
multiline_comment|/* padding */
DECL|member|bcd
r_volatile
id|u32
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
r_volatile
id|u32
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
r_volatile
id|u32
id|gfptr
suffix:semicolon
multiline_comment|/* current GIO fifo ptr */
DECL|member|dfptr
r_volatile
id|u32
id|dfptr
suffix:semicolon
multiline_comment|/* current device fifo ptr */
DECL|member|dconfig
r_volatile
id|u32
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
r_volatile
id|u32
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
DECL|member|_unused1
id|u32
id|_unused1
(braket
l_int|0x1000
op_div
l_int|4
op_minus
l_int|6
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
r_volatile
id|u32
id|rx_cbptr
suffix:semicolon
multiline_comment|/* current dma buffer ptr, diagnostic use only */
DECL|member|rx_ndptr
r_volatile
id|u32
id|rx_ndptr
suffix:semicolon
multiline_comment|/* next dma descriptor ptr */
DECL|member|_unused0
id|u32
id|_unused0
(braket
l_int|0x1000
op_div
l_int|4
op_minus
l_int|2
)braket
suffix:semicolon
multiline_comment|/* padding */
DECL|member|rx_bcd
r_volatile
id|u32
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
r_volatile
id|u32
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
r_volatile
id|u32
id|rx_gfptr
suffix:semicolon
multiline_comment|/* current GIO fifo ptr */
DECL|member|rx_dfptr
r_volatile
id|u32
id|rx_dfptr
suffix:semicolon
multiline_comment|/* current device fifo ptr */
DECL|member|_unused1
id|u32
id|_unused1
suffix:semicolon
multiline_comment|/* padding */
DECL|member|rx_reset
r_volatile
id|u32
id|rx_reset
suffix:semicolon
multiline_comment|/* reset register */
DECL|macro|HPC3_ERXRST_CRESET
mdefine_line|#define HPC3_ERXRST_CRESET 0x1&t;/* Reset dma channel and external controller */
DECL|macro|HPC3_ERXRST_CLRIRQ
mdefine_line|#define HPC3_ERXRST_CLRIRQ 0x2&t;/* Clear channel interrupt */
DECL|macro|HPC3_ERXRST_LBACK
mdefine_line|#define HPC3_ERXRST_LBACK  0x4&t;/* Enable diagnostic loopback mode of Seeq8003 */
DECL|member|rx_dconfig
r_volatile
id|u32
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
r_volatile
id|u32
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
DECL|member|_unused2
id|u32
id|_unused2
(braket
l_int|0x1000
op_div
l_int|4
op_minus
l_int|8
)braket
suffix:semicolon
multiline_comment|/* padding */
multiline_comment|/* Transmitter registers. */
DECL|member|tx_cbptr
r_volatile
id|u32
id|tx_cbptr
suffix:semicolon
multiline_comment|/* current dma buffer ptr, diagnostic use only */
DECL|member|tx_ndptr
r_volatile
id|u32
id|tx_ndptr
suffix:semicolon
multiline_comment|/* next dma descriptor ptr */
DECL|member|_unused3
id|u32
id|_unused3
(braket
l_int|0x1000
op_div
l_int|4
op_minus
l_int|2
)braket
suffix:semicolon
multiline_comment|/* padding */
DECL|member|tx_bcd
r_volatile
id|u32
id|tx_bcd
suffix:semicolon
multiline_comment|/* byte count info */
DECL|macro|HPC3_ETXBCD_BCNTMSK
mdefine_line|#define HPC3_ETXBCD_BCNTMSK 0x00003fff&t;/* bytes to be read from memory */
DECL|macro|HPC3_ETXBCD_ESAMP
mdefine_line|#define HPC3_ETXBCD_ESAMP   0x10000000&t;/* if set, too late to add descriptor */
DECL|macro|HPC3_ETXBCD_XIE
mdefine_line|#define HPC3_ETXBCD_XIE     0x20000000&t;/* Interrupt cpu at end of cur desc */
DECL|macro|HPC3_ETXBCD_EOP
mdefine_line|#define HPC3_ETXBCD_EOP     0x40000000&t;/* Last byte of cur buf is end of packet */
DECL|macro|HPC3_ETXBCD_EOX
mdefine_line|#define HPC3_ETXBCD_EOX     0x80000000&t;/* This buf is the end of desc chain */
DECL|member|tx_ctrl
r_volatile
id|u32
id|tx_ctrl
suffix:semicolon
multiline_comment|/* control register */
DECL|macro|HPC3_ETXCTRL_STAT30
mdefine_line|#define HPC3_ETXCTRL_STAT30 0x0000000f&t;/* Rdonly copy of seeq tx stat reg */
DECL|macro|HPC3_ETXCTRL_STAT4
mdefine_line|#define HPC3_ETXCTRL_STAT4  0x00000010&t;/* Indicate late collision occurred */
DECL|macro|HPC3_ETXCTRL_STAT75
mdefine_line|#define HPC3_ETXCTRL_STAT75 0x000000e0&t;/* Rdonly irq status from seeq */
DECL|macro|HPC3_ETXCTRL_ENDIAN
mdefine_line|#define HPC3_ETXCTRL_ENDIAN 0x00000100&t;/* DMA channel endian mode, 1=little 0=big */
DECL|macro|HPC3_ETXCTRL_ACTIVE
mdefine_line|#define HPC3_ETXCTRL_ACTIVE 0x00000200&t;/* DMA tx channel is active */
DECL|macro|HPC3_ETXCTRL_AMASK
mdefine_line|#define HPC3_ETXCTRL_AMASK  0x00000400&t;/* Indicates ACTIVE inhibits PIO&squot;s */
DECL|member|tx_gfptr
r_volatile
id|u32
id|tx_gfptr
suffix:semicolon
multiline_comment|/* current GIO fifo ptr */
DECL|member|tx_dfptr
r_volatile
id|u32
id|tx_dfptr
suffix:semicolon
multiline_comment|/* current device fifo ptr */
DECL|member|_unused4
id|u32
id|_unused4
(braket
l_int|0x1000
op_div
l_int|4
op_minus
l_int|4
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
multiline_comment|/* Here are where the hpc3 fifo&squot;s can be directly accessed&n;&t; * via PIO accesses.  Under normal operation we never stick&n;&t; * our grubby paws in here so it&squot;s just padding. */
DECL|member|_unused0
id|u32
id|_unused0
(braket
l_int|0x18000
op_div
l_int|4
)braket
suffix:semicolon
multiline_comment|/* HPC3 irq status regs.  Due to a peculiar bug you need to&n;&t; * look at two different register addresses to get at all of&n;&t; * the status bits.  The first reg can only reliably report&n;&t; * bits 4:0 of the status, and the second reg can only&n;&t; * reliably report bits 9:5 of the hpc3 irq status.  I told&n;&t; * you it was a peculiar bug. ;-)&n;&t; */
DECL|member|istat0
r_volatile
id|u32
id|istat0
suffix:semicolon
multiline_comment|/* Irq status, only bits &lt;4:0&gt; reliable. */
DECL|macro|HPC3_ISTAT_PBIMASK
mdefine_line|#define HPC3_ISTAT_PBIMASK&t;0x0ff&t;/* irq bits for pbus devs 0 --&gt; 7 */
DECL|macro|HPC3_ISTAT_SC0MASK
mdefine_line|#define HPC3_ISTAT_SC0MASK&t;0x100&t;/* irq bit for scsi channel 0 */
DECL|macro|HPC3_ISTAT_SC1MASK
mdefine_line|#define HPC3_ISTAT_SC1MASK&t;0x200&t;/* irq bit for scsi channel 1 */
DECL|member|gio_misc
r_volatile
id|u32
id|gio_misc
suffix:semicolon
multiline_comment|/* GIO misc control bits. */
DECL|macro|HPC3_GIOMISC_ERTIME
mdefine_line|#define HPC3_GIOMISC_ERTIME&t;0x1&t;/* Enable external timer real time. */
DECL|macro|HPC3_GIOMISC_DENDIAN
mdefine_line|#define HPC3_GIOMISC_DENDIAN&t;0x2&t;/* dma descriptor endian, 1=lit 0=big */
DECL|member|eeprom
r_volatile
id|u32
id|eeprom
suffix:semicolon
multiline_comment|/* EEPROM data reg. */
DECL|macro|HPC3_EEPROM_EPROT
mdefine_line|#define HPC3_EEPROM_EPROT&t;0x01&t;/* Protect register enable */
DECL|macro|HPC3_EEPROM_CSEL
mdefine_line|#define HPC3_EEPROM_CSEL&t;0x02&t;/* Chip select */
DECL|macro|HPC3_EEPROM_ECLK
mdefine_line|#define HPC3_EEPROM_ECLK&t;0x04&t;/* EEPROM clock */
DECL|macro|HPC3_EEPROM_DATO
mdefine_line|#define HPC3_EEPROM_DATO&t;0x08&t;/* Data out */
DECL|macro|HPC3_EEPROM_DATI
mdefine_line|#define HPC3_EEPROM_DATI&t;0x10&t;/* Data in */
DECL|member|istat1
r_volatile
id|u32
id|istat1
suffix:semicolon
multiline_comment|/* Irq status, only bits &lt;9:5&gt; reliable. */
DECL|member|gio_estat
r_volatile
id|u32
id|gio_estat
suffix:semicolon
multiline_comment|/* GIO error interrupt status reg. */
DECL|macro|HPC3_GIOESTAT_BLMASK
mdefine_line|#define HPC3_GIOESTAT_BLMASK&t;0x000ff&t;/* Bus lane where bad parity occurred */
DECL|macro|HPC3_GIOESTAT_CTYPE
mdefine_line|#define HPC3_GIOESTAT_CTYPE&t;0x00100&t;/* Bus cycle type, 0=PIO 1=DMA */
DECL|macro|HPC3_GIOESTAT_PIDMSK
mdefine_line|#define HPC3_GIOESTAT_PIDMSK&t;0x3f700&t;/* DMA channel parity identifier */
DECL|member|_unused1
id|u32
id|_unused1
(braket
l_int|0x14000
op_div
l_int|4
op_minus
l_int|5
)braket
suffix:semicolon
multiline_comment|/* padding */
multiline_comment|/* Now direct PIO per-HPC3 peripheral access to external regs. */
DECL|member|scsi0_ext
r_volatile
id|u32
id|scsi0_ext
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* SCSI channel 0 external regs */
DECL|member|_unused2
id|u32
id|_unused2
(braket
l_int|0x7c00
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|scsi1_ext
r_volatile
id|u32
id|scsi1_ext
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* SCSI channel 1 external regs */
DECL|member|_unused3
id|u32
id|_unused3
(braket
l_int|0x7c00
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|eth_ext
r_volatile
id|u32
id|eth_ext
(braket
l_int|320
)braket
suffix:semicolon
multiline_comment|/* Ethernet external registers */
DECL|member|_unused4
id|u32
id|_unused4
(braket
l_int|0x3b00
op_div
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Per-peripheral device external registers and DMA/PIO control. */
DECL|member|pbus_extregs
r_volatile
id|u32
id|pbus_extregs
(braket
l_int|16
)braket
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|pbus_dmacfg
r_volatile
id|u32
id|pbus_dmacfg
(braket
l_int|8
)braket
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* Cycles to spend in D3 for reads */
DECL|macro|HPC3_DMACFG_D3R_MASK
mdefine_line|#define HPC3_DMACFG_D3R_MASK&t;&t;0x00000001
DECL|macro|HPC3_DMACFG_D3R_SHIFT
mdefine_line|#define HPC3_DMACFG_D3R_SHIFT&t;&t;0
multiline_comment|/* Cycles to spend in D4 for reads */
DECL|macro|HPC3_DMACFG_D4R_MASK
mdefine_line|#define HPC3_DMACFG_D4R_MASK&t;&t;0x0000001e
DECL|macro|HPC3_DMACFG_D4R_SHIFT
mdefine_line|#define HPC3_DMACFG_D4R_SHIFT&t;&t;1
multiline_comment|/* Cycles to spend in D5 for reads */
DECL|macro|HPC3_DMACFG_D5R_MASK
mdefine_line|#define HPC3_DMACFG_D5R_MASK&t;&t;0x000001e0
DECL|macro|HPC3_DMACFG_D5R_SHIFT
mdefine_line|#define HPC3_DMACFG_D5R_SHIFT&t;&t;5
multiline_comment|/* Cycles to spend in D3 for writes */
DECL|macro|HPC3_DMACFG_D3W_MASK
mdefine_line|#define HPC3_DMACFG_D3W_MASK&t;&t;0x00000200
DECL|macro|HPC3_DMACFG_D3W_SHIFT
mdefine_line|#define HPC3_DMACFG_D3W_SHIFT&t;&t;9
multiline_comment|/* Cycles to spend in D4 for writes */
DECL|macro|HPC3_DMACFG_D4W_MASK
mdefine_line|#define HPC3_DMACFG_D4W_MASK&t;&t;0x00003c00
DECL|macro|HPC3_DMACFG_D4W_SHIFT
mdefine_line|#define HPC3_DMACFG_D4W_SHIFT&t;&t;10
multiline_comment|/* Cycles to spend in D5 for writes */
DECL|macro|HPC3_DMACFG_D5W_MASK
mdefine_line|#define HPC3_DMACFG_D5W_MASK&t;&t;0x0003c000
DECL|macro|HPC3_DMACFG_D5W_SHIFT
mdefine_line|#define HPC3_DMACFG_D5W_SHIFT&t;&t;14
multiline_comment|/* Enable 16-bit DMA access mode */
DECL|macro|HPC3_DMACFG_DS16
mdefine_line|#define HPC3_DMACFG_DS16&t;&t;0x00040000
multiline_comment|/* Places halfwords on high 16 bits of bus */
DECL|macro|HPC3_DMACFG_EVENHI
mdefine_line|#define HPC3_DMACFG_EVENHI&t;&t;0x00080000
multiline_comment|/* Make this device real time */
DECL|macro|HPC3_DMACFG_RTIME
mdefine_line|#define HPC3_DMACFG_RTIME&t;&t;0x00200000
multiline_comment|/* 5 bit burst count for DMA device */
DECL|macro|HPC3_DMACFG_BURST_MASK
mdefine_line|#define HPC3_DMACFG_BURST_MASK&t;&t;0x07c00000
DECL|macro|HPC3_DMACFG_BURST_SHIFT
mdefine_line|#define HPC3_DMACFG_BURST_SHIFT&t;22
multiline_comment|/* Use live pbus_dreq unsynchronized signal */
DECL|macro|HPC3_DMACFG_DRQLIVE
mdefine_line|#define HPC3_DMACFG_DRQLIVE&t;&t;0x08000000
DECL|member|pbus_piocfg
r_volatile
id|u32
id|pbus_piocfg
(braket
l_int|16
)braket
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Cycles to spend in P2 state for reads */
DECL|macro|HPC3_PIOCFG_P2R_MASK
mdefine_line|#define HPC3_PIOCFG_P2R_MASK&t;&t;0x00001
DECL|macro|HPC3_PIOCFG_P2R_SHIFT
mdefine_line|#define HPC3_PIOCFG_P2R_SHIFT&t;&t;0
multiline_comment|/* Cycles to spend in P3 state for reads */
DECL|macro|HPC3_PIOCFG_P3R_MASK
mdefine_line|#define HPC3_PIOCFG_P3R_MASK&t;&t;0x0001e
DECL|macro|HPC3_PIOCFG_P3R_SHIFT
mdefine_line|#define HPC3_PIOCFG_P3R_SHIFT&t;&t;1
multiline_comment|/* Cycles to spend in P4 state for reads */
DECL|macro|HPC3_PIOCFG_P4R_MASK
mdefine_line|#define HPC3_PIOCFG_P4R_MASK&t;&t;0x001e0
DECL|macro|HPC3_PIOCFG_P4R_SHIFT
mdefine_line|#define HPC3_PIOCFG_P4R_SHIFT&t;&t;5
multiline_comment|/* Cycles to spend in P2 state for writes */
DECL|macro|HPC3_PIOCFG_P2W_MASK
mdefine_line|#define HPC3_PIOCFG_P2W_MASK&t;&t;0x00200
DECL|macro|HPC3_PIOCFG_P2W_SHIFT
mdefine_line|#define HPC3_PIOCFG_P2W_SHIFT&t;&t;9
multiline_comment|/* Cycles to spend in P3 state for writes */
DECL|macro|HPC3_PIOCFG_P3W_MASK
mdefine_line|#define HPC3_PIOCFG_P3W_MASK&t;&t;0x03c00
DECL|macro|HPC3_PIOCFG_P3W_SHIFT
mdefine_line|#define HPC3_PIOCFG_P3W_SHIFT&t;&t;10
multiline_comment|/* Cycles to spend in P4 state for writes */
DECL|macro|HPC3_PIOCFG_P4W_MASK
mdefine_line|#define HPC3_PIOCFG_P4W_MASK&t;&t;0x3c000
DECL|macro|HPC3_PIOCFG_P4W_SHIFT
mdefine_line|#define HPC3_PIOCFG_P4W_SHIFT&t;&t;14
multiline_comment|/* Enable 16-bit PIO accesses */
DECL|macro|HPC3_PIOCFG_DS16
mdefine_line|#define HPC3_PIOCFG_DS16&t;&t;0x40000
multiline_comment|/* Place even address bits in bits &lt;15:8&gt; */
DECL|macro|HPC3_PIOCFG_EVENHI
mdefine_line|#define HPC3_PIOCFG_EVENHI&t;&t;0x80000
multiline_comment|/* PBUS PROM control regs. */
DECL|member|pbus_promwe
r_volatile
id|u32
id|pbus_promwe
suffix:semicolon
multiline_comment|/* PROM write enable register */
DECL|macro|HPC3_PROM_WENAB
mdefine_line|#define HPC3_PROM_WENAB&t;0x1&t;/* Enable writes to the PROM */
DECL|member|_unused5
id|u32
id|_unused5
(braket
l_int|0x0800
op_div
l_int|4
op_minus
l_int|1
)braket
suffix:semicolon
DECL|member|pbus_promswap
r_volatile
id|u32
id|pbus_promswap
suffix:semicolon
multiline_comment|/* Chip select swap reg */
DECL|macro|HPC3_PROM_SWAP
mdefine_line|#define HPC3_PROM_SWAP&t;0x1&t;/* invert GIO addr bit to select prom0 or prom1 */
DECL|member|_unused6
id|u32
id|_unused6
(braket
l_int|0x0800
op_div
l_int|4
op_minus
l_int|1
)braket
suffix:semicolon
DECL|member|pbus_gout
r_volatile
id|u32
id|pbus_gout
suffix:semicolon
multiline_comment|/* PROM general purpose output reg */
DECL|macro|HPC3_PROM_STAT
mdefine_line|#define HPC3_PROM_STAT&t;0x1&t;/* General purpose status bit in gout */
DECL|member|_unused7
id|u32
id|_unused7
(braket
l_int|0x1000
op_div
l_int|4
op_minus
l_int|1
)braket
suffix:semicolon
DECL|member|rtcregs
r_volatile
id|u32
id|rtcregs
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* Dallas clock registers */
DECL|member|_unused8
id|u32
id|_unused8
(braket
l_int|50
)braket
suffix:semicolon
DECL|member|bbram
r_volatile
id|u32
id|bbram
(braket
l_int|8192
op_minus
l_int|50
op_minus
l_int|14
)braket
suffix:semicolon
multiline_comment|/* Battery backed ram */
)brace
suffix:semicolon
multiline_comment|/* &n; * It is possible to have two HPC3&squot;s within the address space on&n; * one machine, though only having one is more likely on an Indy.&n; */
r_extern
r_struct
id|hpc3_regs
op_star
id|hpc3c0
comma
op_star
id|hpc3c1
suffix:semicolon
DECL|macro|HPC3_CHIP0_BASE
mdefine_line|#define HPC3_CHIP0_BASE&t;&t;0x1fb80000&t;/* physical */
DECL|macro|HPC3_CHIP1_BASE
mdefine_line|#define HPC3_CHIP1_BASE&t;&t;0x1fb00000&t;/* physical */
r_extern
r_void
id|sgihpc_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _SGI_HPC3_H */
eof
