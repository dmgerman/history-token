multiline_comment|/* $Id: sungem.h,v 1.11 2002/01/12 07:19:55 davem Exp $&n; * sungem.h: Definitions for Sun GEM ethernet driver.&n; *&n; * Copyright (C) 2000 David S. Miller (davem@redhat.com)&n; */
macro_line|#ifndef _SUNGEM_H
DECL|macro|_SUNGEM_H
mdefine_line|#define _SUNGEM_H
multiline_comment|/* Global Registers */
DECL|macro|GREG_SEBSTATE
mdefine_line|#define GREG_SEBSTATE&t;0x0000UL&t;/* SEB State Register&t;&t;*/
DECL|macro|GREG_CFG
mdefine_line|#define GREG_CFG&t;0x0004UL&t;/* Configuration Register&t;*/
DECL|macro|GREG_STAT
mdefine_line|#define GREG_STAT&t;0x000CUL&t;/* Status Register&t;&t;*/
DECL|macro|GREG_IMASK
mdefine_line|#define GREG_IMASK&t;0x0010UL&t;/* Interrupt Mask Register&t;*/
DECL|macro|GREG_IACK
mdefine_line|#define GREG_IACK&t;0x0014UL&t;/* Interrupt ACK Register&t;*/
DECL|macro|GREG_STAT2
mdefine_line|#define GREG_STAT2&t;0x001CUL&t;/* Alias of GREG_STAT&t;&t;*/
DECL|macro|GREG_PCIESTAT
mdefine_line|#define GREG_PCIESTAT&t;0x1000UL&t;/* PCI Error Status Register&t;*/
DECL|macro|GREG_PCIEMASK
mdefine_line|#define GREG_PCIEMASK&t;0x1004UL&t;/* PCI Error Mask Register&t;*/
DECL|macro|GREG_BIFCFG
mdefine_line|#define GREG_BIFCFG&t;0x1008UL&t;/* BIF Configuration Register&t;*/
DECL|macro|GREG_BIFDIAG
mdefine_line|#define GREG_BIFDIAG&t;0x100CUL&t;/* BIF Diagnostics Register&t;*/
DECL|macro|GREG_SWRST
mdefine_line|#define GREG_SWRST&t;0x1010UL&t;/* Software Reset Register&t;*/
multiline_comment|/* Global SEB State Register */
DECL|macro|GREG_SEBSTATE_ARB
mdefine_line|#define GREG_SEBSTATE_ARB&t;0x00000003&t;/* State of Arbiter&t;&t;*/
DECL|macro|GREG_SEBSTATE_RXWON
mdefine_line|#define GREG_SEBSTATE_RXWON&t;0x00000004&t;/* RX won internal arbitration&t;*/
multiline_comment|/* Global Configuration Register */
DECL|macro|GREG_CFG_IBURST
mdefine_line|#define GREG_CFG_IBURST&t;&t;0x00000001&t;/* Infinite Burst&t;&t;*/
DECL|macro|GREG_CFG_TXDMALIM
mdefine_line|#define GREG_CFG_TXDMALIM&t;0x0000003e&t;/* TX DMA grant limit&t;&t;*/
DECL|macro|GREG_CFG_RXDMALIM
mdefine_line|#define GREG_CFG_RXDMALIM&t;0x000007c0&t;/* RX DMA grant limit&t;&t;*/
multiline_comment|/* Global Interrupt Status Register.&n; *&n; * Reading this register automatically clears bits 0 through 6.&n; * This auto-clearing does not occur when the alias at GREG_STAT2&n; * is read instead.  The rest of the interrupt bits only clear when&n; * the secondary interrupt status register corresponding to that&n; * bit is read (ie. if GREG_STAT_PCS is set, it will be cleared by&n; * reading PCS_ISTAT).&n; */
DECL|macro|GREG_STAT_TXINTME
mdefine_line|#define GREG_STAT_TXINTME&t;0x00000001&t;/* TX INTME frame transferred&t;*/
DECL|macro|GREG_STAT_TXALL
mdefine_line|#define GREG_STAT_TXALL&t;&t;0x00000002&t;/* All TX frames transferred&t;*/
DECL|macro|GREG_STAT_TXDONE
mdefine_line|#define GREG_STAT_TXDONE&t;0x00000004&t;/* One TX frame transferred&t;*/
DECL|macro|GREG_STAT_RXDONE
mdefine_line|#define GREG_STAT_RXDONE&t;0x00000010&t;/* One RX frame arrived&t;&t;*/
DECL|macro|GREG_STAT_RXNOBUF
mdefine_line|#define GREG_STAT_RXNOBUF&t;0x00000020&t;/* No free RX buffers available&t;*/
DECL|macro|GREG_STAT_RXTAGERR
mdefine_line|#define GREG_STAT_RXTAGERR&t;0x00000040&t;/* RX tag framing is corrupt&t;*/
DECL|macro|GREG_STAT_PCS
mdefine_line|#define GREG_STAT_PCS&t;&t;0x00002000&t;/* PCS signalled interrupt&t;*/
DECL|macro|GREG_STAT_TXMAC
mdefine_line|#define GREG_STAT_TXMAC&t;&t;0x00004000&t;/* TX MAC signalled interrupt&t;*/
DECL|macro|GREG_STAT_RXMAC
mdefine_line|#define GREG_STAT_RXMAC&t;&t;0x00008000&t;/* RX MAC signalled interrupt&t;*/
DECL|macro|GREG_STAT_MAC
mdefine_line|#define GREG_STAT_MAC&t;&t;0x00010000&t;/* MAC Control signalled irq&t;*/
DECL|macro|GREG_STAT_MIF
mdefine_line|#define GREG_STAT_MIF&t;&t;0x00020000&t;/* MIF signalled interrupt&t;*/
DECL|macro|GREG_STAT_PCIERR
mdefine_line|#define GREG_STAT_PCIERR&t;0x00040000&t;/* PCI Error interrupt&t;&t;*/
DECL|macro|GREG_STAT_TXNR
mdefine_line|#define GREG_STAT_TXNR&t;&t;0xfff80000&t;/* == TXDMA_TXDONE reg val&t;*/
DECL|macro|GREG_STAT_TXNR_SHIFT
mdefine_line|#define GREG_STAT_TXNR_SHIFT&t;19
DECL|macro|GREG_STAT_ABNORMAL
mdefine_line|#define GREG_STAT_ABNORMAL&t;(GREG_STAT_RXNOBUF | GREG_STAT_RXTAGERR | &bslash;&n;&t;&t;&t;&t; GREG_STAT_PCS | GREG_STAT_TXMAC | GREG_STAT_RXMAC | &bslash;&n;&t;&t;&t;&t; GREG_STAT_MAC | GREG_STAT_MIF | GREG_STAT_PCIERR)
multiline_comment|/* The layout of GREG_IMASK and GREG_IACK is identical to GREG_STAT.&n; * Bits set in GREG_IMASK will prevent that interrupt type from being&n; * signalled to the cpu.  GREG_IACK can be used to clear specific top-level&n; * interrupt conditions in GREG_STAT, ie. it only works for bits 0 through 6.&n; * Setting the bit will clear that interrupt, clear bits will have no effect&n; * on GREG_STAT.&n; */
multiline_comment|/* Global PCI Error Status Register */
DECL|macro|GREG_PCIESTAT_BADACK
mdefine_line|#define GREG_PCIESTAT_BADACK&t;0x00000001&t;/* No ACK64# during ABS64 cycle&t;*/
DECL|macro|GREG_PCIESTAT_DTRTO
mdefine_line|#define GREG_PCIESTAT_DTRTO&t;0x00000002&t;/* Delayed transaction timeout&t;*/
DECL|macro|GREG_PCIESTAT_OTHER
mdefine_line|#define GREG_PCIESTAT_OTHER&t;0x00000004&t;/* Other PCI error, check cfg space */
multiline_comment|/* The layout of the GREG_PCIEMASK is identical to that of GREG_PCIESTAT.&n; * Bits set in GREG_PCIEMASK will prevent that interrupt type from being&n; * signalled to the cpu.&n; */
multiline_comment|/* Global BIF Configuration Register */
DECL|macro|GREG_BIFCFG_SLOWCLK
mdefine_line|#define GREG_BIFCFG_SLOWCLK&t;0x00000001&t;/* Set if PCI runs &lt; 25Mhz&t;*/
DECL|macro|GREG_BIFCFG_B64DIS
mdefine_line|#define GREG_BIFCFG_B64DIS&t;0x00000002&t;/* Disable 64bit wide data cycle*/
DECL|macro|GREG_BIFCFG_M66EN
mdefine_line|#define GREG_BIFCFG_M66EN&t;0x00000004&t;/* Set if on 66Mhz PCI segment&t;*/
multiline_comment|/* Global BIF Diagnostics Register */
DECL|macro|GREG_BIFDIAG_BURSTSM
mdefine_line|#define GREG_BIFDIAG_BURSTSM&t;0x007f0000&t;/* PCI Burst state machine&t;*/
DECL|macro|GREG_BIFDIAG_BIFSM
mdefine_line|#define GREG_BIFDIAG_BIFSM&t;0xff000000&t;/* BIF state machine&t;&t;*/
multiline_comment|/* Global Software Reset Register.&n; *&n; * This register is used to perform a global reset of the RX and TX portions&n; * of the GEM asic.  Setting the RX or TX reset bit will start the reset.&n; * The driver _MUST_ poll these bits until they clear.  One may not attempt&n; * to program any other part of GEM until the bits clear.&n; */
DECL|macro|GREG_SWRST_TXRST
mdefine_line|#define GREG_SWRST_TXRST&t;0x00000001&t;/* TX Software Reset&t;&t;*/
DECL|macro|GREG_SWRST_RXRST
mdefine_line|#define GREG_SWRST_RXRST&t;0x00000002&t;/* RX Software Reset&t;&t;*/
DECL|macro|GREG_SWRST_RSTOUT
mdefine_line|#define GREG_SWRST_RSTOUT&t;0x00000004&t;/* Force RST# pin active&t;*/
multiline_comment|/* TX DMA Registers */
DECL|macro|TXDMA_KICK
mdefine_line|#define TXDMA_KICK&t;0x2000UL&t;/* TX Kick Register&t;&t;*/
DECL|macro|TXDMA_CFG
mdefine_line|#define TXDMA_CFG&t;0x2004UL&t;/* TX Configuration Register&t;*/
DECL|macro|TXDMA_DBLOW
mdefine_line|#define TXDMA_DBLOW&t;0x2008UL&t;/* TX Desc. Base Low&t;&t;*/
DECL|macro|TXDMA_DBHI
mdefine_line|#define TXDMA_DBHI&t;0x200CUL&t;/* TX Desc. Base High&t;&t;*/
DECL|macro|TXDMA_FWPTR
mdefine_line|#define TXDMA_FWPTR&t;0x2014UL&t;/* TX FIFO Write Pointer&t;*/
DECL|macro|TXDMA_FSWPTR
mdefine_line|#define TXDMA_FSWPTR&t;0x2018UL&t;/* TX FIFO Shadow Write Pointer&t;*/
DECL|macro|TXDMA_FRPTR
mdefine_line|#define TXDMA_FRPTR&t;0x201CUL&t;/* TX FIFO Read Pointer&t;&t;*/
DECL|macro|TXDMA_FSRPTR
mdefine_line|#define TXDMA_FSRPTR&t;0x2020UL&t;/* TX FIFO Shadow Read Pointer&t;*/
DECL|macro|TXDMA_PCNT
mdefine_line|#define TXDMA_PCNT&t;0x2024UL&t;/* TX FIFO Packet Counter&t;*/
DECL|macro|TXDMA_SMACHINE
mdefine_line|#define TXDMA_SMACHINE&t;0x2028UL&t;/* TX State Machine Register&t;*/
DECL|macro|TXDMA_DPLOW
mdefine_line|#define TXDMA_DPLOW&t;0x2030UL&t;/* TX Data Pointer Low&t;&t;*/
DECL|macro|TXDMA_DPHI
mdefine_line|#define TXDMA_DPHI&t;0x2034UL&t;/* TX Data Pointer High&t;&t;*/
DECL|macro|TXDMA_TXDONE
mdefine_line|#define TXDMA_TXDONE&t;0x2100UL&t;/* TX Completion Register&t;*/
DECL|macro|TXDMA_FADDR
mdefine_line|#define TXDMA_FADDR&t;0x2104UL&t;/* TX FIFO Address&t;&t;*/
DECL|macro|TXDMA_FTAG
mdefine_line|#define TXDMA_FTAG&t;0x2108UL&t;/* TX FIFO Tag&t;&t;&t;*/
DECL|macro|TXDMA_DLOW
mdefine_line|#define TXDMA_DLOW&t;0x210CUL&t;/* TX FIFO Data Low&t;&t;*/
DECL|macro|TXDMA_DHIT1
mdefine_line|#define TXDMA_DHIT1&t;0x2110UL&t;/* TX FIFO Data HighT1&t;&t;*/
DECL|macro|TXDMA_DHIT0
mdefine_line|#define TXDMA_DHIT0&t;0x2114UL&t;/* TX FIFO Data HighT0&t;&t;*/
DECL|macro|TXDMA_FSZ
mdefine_line|#define TXDMA_FSZ&t;0x2118UL&t;/* TX FIFO Size&t;&t;&t;*/
multiline_comment|/* TX Kick Register.&n; *&n; * This 13-bit register is programmed by the driver to hold the descriptor&n; * entry index which follows the last valid transmit descriptor.&n; */
multiline_comment|/* TX Completion Register.&n; *&n; * This 13-bit register is updated by GEM to hold to descriptor entry index&n; * which follows the last descriptor already processed by GEM.  Note that&n; * this value is mirrored in GREG_STAT which eliminates the need to even&n; * access this register in the driver during interrupt processing.&n; */
multiline_comment|/* TX Configuration Register.&n; *&n; * Note that TXDMA_CFG_FTHRESH, the TX FIFO Threshold, is an obsolete feature&n; * that was meant to be used with jumbo packets.  It should be set to the&n; * maximum value of 0x4ff, else one risks getting TX MAC Underrun errors.&n; */
DECL|macro|TXDMA_CFG_ENABLE
mdefine_line|#define TXDMA_CFG_ENABLE&t;0x00000001&t;/* Enable TX DMA channel&t;*/
DECL|macro|TXDMA_CFG_RINGSZ
mdefine_line|#define TXDMA_CFG_RINGSZ&t;0x0000001e&t;/* TX descriptor ring size&t;*/
DECL|macro|TXDMA_CFG_RINGSZ_32
mdefine_line|#define TXDMA_CFG_RINGSZ_32&t;0x00000000&t;/* 32 TX descriptors&t;&t;*/
DECL|macro|TXDMA_CFG_RINGSZ_64
mdefine_line|#define TXDMA_CFG_RINGSZ_64&t;0x00000002&t;/* 64 TX descriptors&t;&t;*/
DECL|macro|TXDMA_CFG_RINGSZ_128
mdefine_line|#define TXDMA_CFG_RINGSZ_128&t;0x00000004&t;/* 128 TX descriptors&t;&t;*/
DECL|macro|TXDMA_CFG_RINGSZ_256
mdefine_line|#define TXDMA_CFG_RINGSZ_256&t;0x00000006&t;/* 256 TX descriptors&t;&t;*/
DECL|macro|TXDMA_CFG_RINGSZ_512
mdefine_line|#define TXDMA_CFG_RINGSZ_512&t;0x00000008&t;/* 512 TX descriptors&t;&t;*/
DECL|macro|TXDMA_CFG_RINGSZ_1K
mdefine_line|#define TXDMA_CFG_RINGSZ_1K&t;0x0000000a&t;/* 1024 TX descriptors&t;&t;*/
DECL|macro|TXDMA_CFG_RINGSZ_2K
mdefine_line|#define TXDMA_CFG_RINGSZ_2K&t;0x0000000c&t;/* 2048 TX descriptors&t;&t;*/
DECL|macro|TXDMA_CFG_RINGSZ_4K
mdefine_line|#define TXDMA_CFG_RINGSZ_4K&t;0x0000000e&t;/* 4096 TX descriptors&t;&t;*/
DECL|macro|TXDMA_CFG_RINGSZ_8K
mdefine_line|#define TXDMA_CFG_RINGSZ_8K&t;0x00000010&t;/* 8192 TX descriptors&t;&t;*/
DECL|macro|TXDMA_CFG_PIOSEL
mdefine_line|#define TXDMA_CFG_PIOSEL&t;0x00000020&t;/* Enable TX FIFO PIO from cpu&t;*/
DECL|macro|TXDMA_CFG_FTHRESH
mdefine_line|#define TXDMA_CFG_FTHRESH&t;0x001ffc00&t;/* TX FIFO Threshold, obsolete&t;*/
DECL|macro|TXDMA_CFG_PMODE
mdefine_line|#define TXDMA_CFG_PMODE&t;&t;0x00200000&t;/* TXALL irq means TX FIFO empty*/
multiline_comment|/* TX Descriptor Base Low/High.&n; *&n; * These two registers store the 53 most significant bits of the base address&n; * of the TX descriptor table.  The 11 least significant bits are always&n; * zero.  As a result, the TX descriptor table must be 2K aligned.&n; */
multiline_comment|/* The rest of the TXDMA_* registers are for diagnostics and debug, I will document&n; * them later. -DaveM&n; */
multiline_comment|/* Receive DMA Registers */
DECL|macro|RXDMA_CFG
mdefine_line|#define RXDMA_CFG&t;0x4000UL&t;/* RX Configuration Register&t;*/
DECL|macro|RXDMA_DBLOW
mdefine_line|#define RXDMA_DBLOW&t;0x4004UL&t;/* RX Descriptor Base Low&t;*/
DECL|macro|RXDMA_DBHI
mdefine_line|#define RXDMA_DBHI&t;0x4008UL&t;/* RX Descriptor Base High&t;*/
DECL|macro|RXDMA_FWPTR
mdefine_line|#define RXDMA_FWPTR&t;0x400CUL&t;/* RX FIFO Write Pointer&t;*/
DECL|macro|RXDMA_FSWPTR
mdefine_line|#define RXDMA_FSWPTR&t;0x4010UL&t;/* RX FIFO Shadow Write Pointer&t;*/
DECL|macro|RXDMA_FRPTR
mdefine_line|#define RXDMA_FRPTR&t;0x4014UL&t;/* RX FIFO Read Pointer&t;&t;*/
DECL|macro|RXDMA_PCNT
mdefine_line|#define RXDMA_PCNT&t;0x4018UL&t;/* RX FIFO Packet Counter&t;*/
DECL|macro|RXDMA_SMACHINE
mdefine_line|#define RXDMA_SMACHINE&t;0x401CUL&t;/* RX State Machine Register&t;*/
DECL|macro|RXDMA_PTHRESH
mdefine_line|#define RXDMA_PTHRESH&t;0x4020UL&t;/* Pause Thresholds&t;&t;*/
DECL|macro|RXDMA_DPLOW
mdefine_line|#define RXDMA_DPLOW&t;0x4024UL&t;/* RX Data Pointer Low&t;&t;*/
DECL|macro|RXDMA_DPHI
mdefine_line|#define RXDMA_DPHI&t;0x4028UL&t;/* RX Data Pointer High&t;&t;*/
DECL|macro|RXDMA_KICK
mdefine_line|#define RXDMA_KICK&t;0x4100UL&t;/* RX Kick Register&t;&t;*/
DECL|macro|RXDMA_DONE
mdefine_line|#define RXDMA_DONE&t;0x4104UL&t;/* RX Completion Register&t;*/
DECL|macro|RXDMA_BLANK
mdefine_line|#define RXDMA_BLANK&t;0x4108UL&t;/* RX Blanking Register&t;&t;*/
DECL|macro|RXDMA_FADDR
mdefine_line|#define RXDMA_FADDR&t;0x410CUL&t;/* RX FIFO Address&t;&t;*/
DECL|macro|RXDMA_FTAG
mdefine_line|#define RXDMA_FTAG&t;0x4110UL&t;/* RX FIFO Tag&t;&t;&t;*/
DECL|macro|RXDMA_DLOW
mdefine_line|#define RXDMA_DLOW&t;0x4114UL&t;/* RX FIFO Data Low&t;&t;*/
DECL|macro|RXDMA_DHIT1
mdefine_line|#define RXDMA_DHIT1&t;0x4118UL&t;/* RX FIFO Data HighT0&t;&t;*/
DECL|macro|RXDMA_DHIT0
mdefine_line|#define RXDMA_DHIT0&t;0x411CUL&t;/* RX FIFO Data HighT1&t;&t;*/
DECL|macro|RXDMA_FSZ
mdefine_line|#define RXDMA_FSZ&t;0x4120UL&t;/* RX FIFO Size&t;&t;&t;*/
multiline_comment|/* RX Configuration Register. */
DECL|macro|RXDMA_CFG_ENABLE
mdefine_line|#define RXDMA_CFG_ENABLE&t;0x00000001&t;/* Enable RX DMA channel&t;*/
DECL|macro|RXDMA_CFG_RINGSZ
mdefine_line|#define RXDMA_CFG_RINGSZ&t;0x0000001e&t;/* RX descriptor ring size&t;*/
DECL|macro|RXDMA_CFG_RINGSZ_32
mdefine_line|#define RXDMA_CFG_RINGSZ_32&t;0x00000000&t;/* - 32   entries&t;&t;*/
DECL|macro|RXDMA_CFG_RINGSZ_64
mdefine_line|#define RXDMA_CFG_RINGSZ_64&t;0x00000002&t;/* - 64   entries&t;&t;*/
DECL|macro|RXDMA_CFG_RINGSZ_128
mdefine_line|#define RXDMA_CFG_RINGSZ_128&t;0x00000004&t;/* - 128  entries&t;&t;*/
DECL|macro|RXDMA_CFG_RINGSZ_256
mdefine_line|#define RXDMA_CFG_RINGSZ_256&t;0x00000006&t;/* - 256  entries&t;&t;*/
DECL|macro|RXDMA_CFG_RINGSZ_512
mdefine_line|#define RXDMA_CFG_RINGSZ_512&t;0x00000008&t;/* - 512  entries&t;&t;*/
DECL|macro|RXDMA_CFG_RINGSZ_1K
mdefine_line|#define RXDMA_CFG_RINGSZ_1K&t;0x0000000a&t;/* - 1024 entries&t;&t;*/
DECL|macro|RXDMA_CFG_RINGSZ_2K
mdefine_line|#define RXDMA_CFG_RINGSZ_2K&t;0x0000000c&t;/* - 2048 entries&t;&t;*/
DECL|macro|RXDMA_CFG_RINGSZ_4K
mdefine_line|#define RXDMA_CFG_RINGSZ_4K&t;0x0000000e&t;/* - 4096 entries&t;&t;*/
DECL|macro|RXDMA_CFG_RINGSZ_8K
mdefine_line|#define RXDMA_CFG_RINGSZ_8K&t;0x00000010&t;/* - 8192 entries&t;&t;*/
DECL|macro|RXDMA_CFG_RINGSZ_BDISAB
mdefine_line|#define RXDMA_CFG_RINGSZ_BDISAB&t;0x00000020&t;/* Disable RX desc batching&t;*/
DECL|macro|RXDMA_CFG_FBOFF
mdefine_line|#define RXDMA_CFG_FBOFF&t;&t;0x00001c00&t;/* Offset of first data byte&t;*/
DECL|macro|RXDMA_CFG_CSUMOFF
mdefine_line|#define RXDMA_CFG_CSUMOFF&t;0x000fe000&t;/* Skip bytes before csum calc&t;*/
DECL|macro|RXDMA_CFG_FTHRESH
mdefine_line|#define RXDMA_CFG_FTHRESH&t;0x07000000&t;/* RX FIFO dma start threshold&t;*/
DECL|macro|RXDMA_CFG_FTHRESH_64
mdefine_line|#define RXDMA_CFG_FTHRESH_64&t;0x00000000&t;/* - 64   bytes&t;&t;&t;*/
DECL|macro|RXDMA_CFG_FTHRESH_128
mdefine_line|#define RXDMA_CFG_FTHRESH_128&t;0x01000000&t;/* - 128  bytes&t;&t;&t;*/
DECL|macro|RXDMA_CFG_FTHRESH_256
mdefine_line|#define RXDMA_CFG_FTHRESH_256&t;0x02000000&t;/* - 256  bytes&t;&t;&t;*/
DECL|macro|RXDMA_CFG_FTHRESH_512
mdefine_line|#define RXDMA_CFG_FTHRESH_512&t;0x03000000&t;/* - 512  bytes&t;&t;&t;*/
DECL|macro|RXDMA_CFG_FTHRESH_1K
mdefine_line|#define RXDMA_CFG_FTHRESH_1K&t;0x04000000&t;/* - 1024 bytes&t;&t;&t;*/
DECL|macro|RXDMA_CFG_FTHRESH_2K
mdefine_line|#define RXDMA_CFG_FTHRESH_2K&t;0x05000000&t;/* - 2048 bytes&t;&t;&t;*/
multiline_comment|/* RX Descriptor Base Low/High.&n; *&n; * These two registers store the 53 most significant bits of the base address&n; * of the RX descriptor table.  The 11 least significant bits are always&n; * zero.  As a result, the RX descriptor table must be 2K aligned.&n; */
multiline_comment|/* RX PAUSE Thresholds.&n; *&n; * These values determine when XOFF and XON PAUSE frames are emitted by&n; * GEM.  The thresholds measure RX FIFO occupancy in units of 64 bytes.&n; */
DECL|macro|RXDMA_PTHRESH_OFF
mdefine_line|#define RXDMA_PTHRESH_OFF&t;0x000001ff&t;/* XOFF emitted w/FIFO &gt; this&t;*/
DECL|macro|RXDMA_PTHRESH_ON
mdefine_line|#define RXDMA_PTHRESH_ON&t;0x001ff000&t;/* XON emitted w/FIFO &lt; this&t;*/
multiline_comment|/* RX Kick Register.&n; *&n; * This 13-bit register is written by the host CPU and holds the last&n; * valid RX descriptor number plus one.  This is, if &squot;N&squot; is written to&n; * this register, it means that all RX descriptors up to but excluding&n; * &squot;N&squot; are valid.&n; *&n; * The hardware requires that RX descriptors are posted in increments&n; * of 4.  This means &squot;N&squot; must be a multiple of four.  For the best&n; * performance, the first new descriptor being posted should be (PCI)&n; * cache line aligned.&n; */
multiline_comment|/* RX Completion Register.&n; *&n; * This 13-bit register is updated by GEM to indicate which RX descriptors&n; * have already been used for receive frames.  All descriptors up to but&n; * excluding the value in this register are ready to be processed.  GEM&n; * updates this register value after the RX FIFO empties completely into&n; * the RX descriptor&squot;s buffer, but before the RX_DONE bit is set in the&n; * interrupt status register.&n; */
multiline_comment|/* RX Blanking Register. */
DECL|macro|RXDMA_BLANK_IPKTS
mdefine_line|#define RXDMA_BLANK_IPKTS&t;0x000001ff&t;/* RX_DONE asserted after this&n;&t;&t;&t;&t;&t;&t; * many packets received since&n;&t;&t;&t;&t;&t;&t; * previous RX_DONE.&n;&t;&t;&t;&t;&t;&t; */
DECL|macro|RXDMA_BLANK_ITIME
mdefine_line|#define RXDMA_BLANK_ITIME&t;0x000ff000&t;/* RX_DONE asserted after this&n;&t;&t;&t;&t;&t;&t; * many clocks (measured in 2048&n;&t;&t;&t;&t;&t;&t; * PCI clocks) were counted since&n;&t;&t;&t;&t;&t;&t; * the previous RX_DONE.&n;&t;&t;&t;&t;&t;&t; */
multiline_comment|/* RX FIFO Size.&n; *&n; * This 11-bit read-only register indicates how large, in units of 64-bytes,&n; * the RX FIFO is.  The driver uses this to properly configure the RX PAUSE&n; * thresholds.&n; */
multiline_comment|/* The rest of the RXDMA_* registers are for diagnostics and debug, I will document&n; * them later. -DaveM&n; */
multiline_comment|/* MAC Registers */
DECL|macro|MAC_TXRST
mdefine_line|#define MAC_TXRST&t;0x6000UL&t;/* TX MAC Software Reset Command*/
DECL|macro|MAC_RXRST
mdefine_line|#define MAC_RXRST&t;0x6004UL&t;/* RX MAC Software Reset Command*/
DECL|macro|MAC_SNDPAUSE
mdefine_line|#define MAC_SNDPAUSE&t;0x6008UL&t;/* Send Pause Command Register&t;*/
DECL|macro|MAC_TXSTAT
mdefine_line|#define MAC_TXSTAT&t;0x6010UL&t;/* TX MAC Status Register&t;*/
DECL|macro|MAC_RXSTAT
mdefine_line|#define MAC_RXSTAT&t;0x6014UL&t;/* RX MAC Status Register&t;*/
DECL|macro|MAC_CSTAT
mdefine_line|#define MAC_CSTAT&t;0x6018UL&t;/* MAC Control Status Register&t;*/
DECL|macro|MAC_TXMASK
mdefine_line|#define MAC_TXMASK&t;0x6020UL&t;/* TX MAC Mask Register&t;&t;*/
DECL|macro|MAC_RXMASK
mdefine_line|#define MAC_RXMASK&t;0x6024UL&t;/* RX MAC Mask Register&t;&t;*/
DECL|macro|MAC_MCMASK
mdefine_line|#define MAC_MCMASK&t;0x6028UL&t;/* MAC Control Mask Register&t;*/
DECL|macro|MAC_TXCFG
mdefine_line|#define MAC_TXCFG&t;0x6030UL&t;/* TX MAC Configuration Register*/
DECL|macro|MAC_RXCFG
mdefine_line|#define MAC_RXCFG&t;0x6034UL&t;/* RX MAC Configuration Register*/
DECL|macro|MAC_MCCFG
mdefine_line|#define MAC_MCCFG&t;0x6038UL&t;/* MAC Control Config Register&t;*/
DECL|macro|MAC_XIFCFG
mdefine_line|#define MAC_XIFCFG&t;0x603CUL&t;/* XIF Configuration Register&t;*/
DECL|macro|MAC_IPG0
mdefine_line|#define MAC_IPG0&t;0x6040UL&t;/* InterPacketGap0 Register&t;*/
DECL|macro|MAC_IPG1
mdefine_line|#define MAC_IPG1&t;0x6044UL&t;/* InterPacketGap1 Register&t;*/
DECL|macro|MAC_IPG2
mdefine_line|#define MAC_IPG2&t;0x6048UL&t;/* InterPacketGap2 Register&t;*/
DECL|macro|MAC_STIME
mdefine_line|#define MAC_STIME&t;0x604CUL&t;/* SlotTime Register&t;&t;*/
DECL|macro|MAC_MINFSZ
mdefine_line|#define MAC_MINFSZ&t;0x6050UL&t;/* MinFrameSize Register&t;*/
DECL|macro|MAC_MAXFSZ
mdefine_line|#define MAC_MAXFSZ&t;0x6054UL&t;/* MaxFrameSize Register&t;*/
DECL|macro|MAC_PASIZE
mdefine_line|#define MAC_PASIZE&t;0x6058UL&t;/* PA Size Register&t;&t;*/
DECL|macro|MAC_JAMSIZE
mdefine_line|#define MAC_JAMSIZE&t;0x605CUL&t;/* JamSize Register&t;&t;*/
DECL|macro|MAC_ATTLIM
mdefine_line|#define MAC_ATTLIM&t;0x6060UL&t;/* Attempt Limit Register&t;*/
DECL|macro|MAC_MCTYPE
mdefine_line|#define MAC_MCTYPE&t;0x6064UL&t;/* MAC Control Type Register&t;*/
DECL|macro|MAC_ADDR0
mdefine_line|#define MAC_ADDR0&t;0x6080UL&t;/* MAC Address 0 Register&t;*/
DECL|macro|MAC_ADDR1
mdefine_line|#define MAC_ADDR1&t;0x6084UL&t;/* MAC Address 1 Register&t;*/
DECL|macro|MAC_ADDR2
mdefine_line|#define MAC_ADDR2&t;0x6088UL&t;/* MAC Address 2 Register&t;*/
DECL|macro|MAC_ADDR3
mdefine_line|#define MAC_ADDR3&t;0x608CUL&t;/* MAC Address 3 Register&t;*/
DECL|macro|MAC_ADDR4
mdefine_line|#define MAC_ADDR4&t;0x6090UL&t;/* MAC Address 4 Register&t;*/
DECL|macro|MAC_ADDR5
mdefine_line|#define MAC_ADDR5&t;0x6094UL&t;/* MAC Address 5 Register&t;*/
DECL|macro|MAC_ADDR6
mdefine_line|#define MAC_ADDR6&t;0x6098UL&t;/* MAC Address 6 Register&t;*/
DECL|macro|MAC_ADDR7
mdefine_line|#define MAC_ADDR7&t;0x609CUL&t;/* MAC Address 7 Register&t;*/
DECL|macro|MAC_ADDR8
mdefine_line|#define MAC_ADDR8&t;0x60A0UL&t;/* MAC Address 8 Register&t;*/
DECL|macro|MAC_AFILT0
mdefine_line|#define MAC_AFILT0&t;0x60A4UL&t;/* Address Filter 0 Register&t;*/
DECL|macro|MAC_AFILT1
mdefine_line|#define MAC_AFILT1&t;0x60A8UL&t;/* Address Filter 1 Register&t;*/
DECL|macro|MAC_AFILT2
mdefine_line|#define MAC_AFILT2&t;0x60ACUL&t;/* Address Filter 2 Register&t;*/
DECL|macro|MAC_AF21MSK
mdefine_line|#define MAC_AF21MSK&t;0x60B0UL&t;/* Address Filter 2&amp;1 Mask Reg&t;*/
DECL|macro|MAC_AF0MSK
mdefine_line|#define MAC_AF0MSK&t;0x60B4UL&t;/* Address Filter 0 Mask Reg&t;*/
DECL|macro|MAC_HASH0
mdefine_line|#define MAC_HASH0&t;0x60C0UL&t;/* Hash Table 0 Register&t;*/
DECL|macro|MAC_HASH1
mdefine_line|#define MAC_HASH1&t;0x60C4UL&t;/* Hash Table 1 Register&t;*/
DECL|macro|MAC_HASH2
mdefine_line|#define MAC_HASH2&t;0x60C8UL&t;/* Hash Table 2 Register&t;*/
DECL|macro|MAC_HASH3
mdefine_line|#define MAC_HASH3&t;0x60CCUL&t;/* Hash Table 3 Register&t;*/
DECL|macro|MAC_HASH4
mdefine_line|#define MAC_HASH4&t;0x60D0UL&t;/* Hash Table 4 Register&t;*/
DECL|macro|MAC_HASH5
mdefine_line|#define MAC_HASH5&t;0x60D4UL&t;/* Hash Table 5 Register&t;*/
DECL|macro|MAC_HASH6
mdefine_line|#define MAC_HASH6&t;0x60D8UL&t;/* Hash Table 6 Register&t;*/
DECL|macro|MAC_HASH7
mdefine_line|#define MAC_HASH7&t;0x60DCUL&t;/* Hash Table 7 Register&t;*/
DECL|macro|MAC_HASH8
mdefine_line|#define MAC_HASH8&t;0x60E0UL&t;/* Hash Table 8 Register&t;*/
DECL|macro|MAC_HASH9
mdefine_line|#define MAC_HASH9&t;0x60E4UL&t;/* Hash Table 9 Register&t;*/
DECL|macro|MAC_HASH10
mdefine_line|#define MAC_HASH10&t;0x60E8UL&t;/* Hash Table 10 Register&t;*/
DECL|macro|MAC_HASH11
mdefine_line|#define MAC_HASH11&t;0x60ECUL&t;/* Hash Table 11 Register&t;*/
DECL|macro|MAC_HASH12
mdefine_line|#define MAC_HASH12&t;0x60F0UL&t;/* Hash Table 12 Register&t;*/
DECL|macro|MAC_HASH13
mdefine_line|#define MAC_HASH13&t;0x60F4UL&t;/* Hash Table 13 Register&t;*/
DECL|macro|MAC_HASH14
mdefine_line|#define MAC_HASH14&t;0x60F8UL&t;/* Hash Table 14 Register&t;*/
DECL|macro|MAC_HASH15
mdefine_line|#define MAC_HASH15&t;0x60FCUL&t;/* Hash Table 15 Register&t;*/
DECL|macro|MAC_NCOLL
mdefine_line|#define MAC_NCOLL&t;0x6100UL&t;/* Normal Collision Counter&t;*/
DECL|macro|MAC_FASUCC
mdefine_line|#define MAC_FASUCC&t;0x6104UL&t;/* First Attmpt. Succ Coll Ctr.&t;*/
DECL|macro|MAC_ECOLL
mdefine_line|#define MAC_ECOLL&t;0x6108UL&t;/* Excessive Collision Counter&t;*/
DECL|macro|MAC_LCOLL
mdefine_line|#define MAC_LCOLL&t;0x610CUL&t;/* Late Collision Counter&t;*/
DECL|macro|MAC_DTIMER
mdefine_line|#define MAC_DTIMER&t;0x6110UL&t;/* Defer Timer&t;&t;&t;*/
DECL|macro|MAC_PATMPS
mdefine_line|#define MAC_PATMPS&t;0x6114UL&t;/* Peak Attempts Register&t;*/
DECL|macro|MAC_RFCTR
mdefine_line|#define MAC_RFCTR&t;0x6118UL&t;/* Receive Frame Counter&t;*/
DECL|macro|MAC_LERR
mdefine_line|#define MAC_LERR&t;0x611CUL&t;/* Length Error Counter&t;&t;*/
DECL|macro|MAC_AERR
mdefine_line|#define MAC_AERR&t;0x6120UL&t;/* Alignment Error Counter&t;*/
DECL|macro|MAC_FCSERR
mdefine_line|#define MAC_FCSERR&t;0x6124UL&t;/* FCS Error Counter&t;&t;*/
DECL|macro|MAC_RXCVERR
mdefine_line|#define MAC_RXCVERR&t;0x6128UL&t;/* RX code Violation Error Ctr&t;*/
DECL|macro|MAC_RANDSEED
mdefine_line|#define MAC_RANDSEED&t;0x6130UL&t;/* Random Number Seed Register&t;*/
DECL|macro|MAC_SMACHINE
mdefine_line|#define MAC_SMACHINE&t;0x6134UL&t;/* State Machine Register&t;*/
multiline_comment|/* TX MAC Software Reset Command. */
DECL|macro|MAC_TXRST_CMD
mdefine_line|#define MAC_TXRST_CMD&t;0x00000001&t;/* Start sw reset, self-clears&t;*/
multiline_comment|/* RX MAC Software Reset Command. */
DECL|macro|MAC_RXRST_CMD
mdefine_line|#define MAC_RXRST_CMD&t;0x00000001&t;/* Start sw reset, self-clears&t;*/
multiline_comment|/* Send Pause Command. */
DECL|macro|MAC_SNDPAUSE_TS
mdefine_line|#define MAC_SNDPAUSE_TS&t;0x0000ffff&t;/* The pause_time operand used in&n;&t;&t;&t;&t;&t; * Send_Pause and flow-control&n;&t;&t;&t;&t;&t; * handshakes.&n;&t;&t;&t;&t;&t; */
DECL|macro|MAC_SNDPAUSE_SP
mdefine_line|#define MAC_SNDPAUSE_SP&t;0x00010000&t;/* Setting this bit instructs the MAC&n;&t;&t;&t;&t;&t; * to send a Pause Flow Control&n;&t;&t;&t;&t;&t; * frame onto the network.&n;&t;&t;&t;&t;&t; */
multiline_comment|/* TX MAC Status Register. */
DECL|macro|MAC_TXSTAT_XMIT
mdefine_line|#define MAC_TXSTAT_XMIT&t;0x00000001&t;/* Frame Transmitted&t;&t;*/
DECL|macro|MAC_TXSTAT_URUN
mdefine_line|#define MAC_TXSTAT_URUN&t;0x00000002&t;/* TX Underrun&t;&t;&t;*/
DECL|macro|MAC_TXSTAT_MPE
mdefine_line|#define MAC_TXSTAT_MPE&t;0x00000004&t;/* Max Packet Size Error&t;*/
DECL|macro|MAC_TXSTAT_NCE
mdefine_line|#define MAC_TXSTAT_NCE&t;0x00000008&t;/* Normal Collision Cntr Expire&t;*/
DECL|macro|MAC_TXSTAT_ECE
mdefine_line|#define MAC_TXSTAT_ECE&t;0x00000010&t;/* Excess Collision Cntr Expire&t;*/
DECL|macro|MAC_TXSTAT_LCE
mdefine_line|#define MAC_TXSTAT_LCE&t;0x00000020&t;/* Late Collision Cntr Expire&t;*/
DECL|macro|MAC_TXSTAT_FCE
mdefine_line|#define MAC_TXSTAT_FCE&t;0x00000040&t;/* First Collision Cntr Expire&t;*/
DECL|macro|MAC_TXSTAT_DTE
mdefine_line|#define MAC_TXSTAT_DTE&t;0x00000080&t;/* Defer Timer Expire&t;&t;*/
DECL|macro|MAC_TXSTAT_PCE
mdefine_line|#define MAC_TXSTAT_PCE&t;0x00000100&t;/* Peak Attempts Cntr Expire&t;*/
multiline_comment|/* RX MAC Status Register. */
DECL|macro|MAC_RXSTAT_RCV
mdefine_line|#define MAC_RXSTAT_RCV&t;0x00000001&t;/* Frame Received&t;&t;*/
DECL|macro|MAC_RXSTAT_OFLW
mdefine_line|#define MAC_RXSTAT_OFLW&t;0x00000002&t;/* Receive Overflow&t;&t;*/
DECL|macro|MAC_RXSTAT_FCE
mdefine_line|#define MAC_RXSTAT_FCE&t;0x00000004&t;/* Frame Cntr Expire&t;&t;*/
DECL|macro|MAC_RXSTAT_ACE
mdefine_line|#define MAC_RXSTAT_ACE&t;0x00000008&t;/* Align Error Cntr Expire&t;*/
DECL|macro|MAC_RXSTAT_CCE
mdefine_line|#define MAC_RXSTAT_CCE&t;0x00000010&t;/* CRC Error Cntr Expire&t;*/
DECL|macro|MAC_RXSTAT_LCE
mdefine_line|#define MAC_RXSTAT_LCE&t;0x00000020&t;/* Length Error Cntr Expire&t;*/
DECL|macro|MAC_RXSTAT_VCE
mdefine_line|#define MAC_RXSTAT_VCE&t;0x00000040&t;/* Code Violation Cntr Expire&t;*/
multiline_comment|/* MAC Control Status Register. */
DECL|macro|MAC_CSTAT_PRCV
mdefine_line|#define MAC_CSTAT_PRCV&t;0x00000001&t;/* Pause Received&t;&t;*/
DECL|macro|MAC_CSTAT_PS
mdefine_line|#define MAC_CSTAT_PS&t;0x00000002&t;/* Paused State&t;&t;&t;*/
DECL|macro|MAC_CSTAT_NPS
mdefine_line|#define MAC_CSTAT_NPS&t;0x00000004&t;/* Not Paused State&t;&t;*/
DECL|macro|MAC_CSTAT_PTR
mdefine_line|#define MAC_CSTAT_PTR&t;0xffff0000&t;/* Pause Time Received&t;&t;*/
multiline_comment|/* The layout of the MAC_{TX,RX,C}MASK registers is identical to that&n; * of MAC_{TX,RX,C}STAT.  Bits set in MAC_{TX,RX,C}MASK will prevent&n; * that interrupt type from being signalled to front end of GEM.  For&n; * the interrupt to actually get sent to the cpu, it is necessary to&n; * properly set the appropriate GREG_IMASK_{TX,RX,}MAC bits as well.&n; */
multiline_comment|/* TX MAC Configuration Register.&n; *&n; * NOTE: The TX MAC Enable bit must be cleared and polled until&n; *&t; zero before any other bits in this register are changed.&n; *&n; *&t; Also, enabling the Carrier Extension feature of GEM is&n; *&t; a 3 step process 1) Set TX Carrier Extension 2) Set&n; *&t; RX Carrier Extension 3) Set Slot Time to 0x200.  This&n; *&t; mode must be enabled when in half-duplex at 1Gbps, else&n; *&t; it must be disabled.&n; */
DECL|macro|MAC_TXCFG_ENAB
mdefine_line|#define MAC_TXCFG_ENAB&t;0x00000001&t;/* TX MAC Enable&t;&t;*/
DECL|macro|MAC_TXCFG_ICS
mdefine_line|#define MAC_TXCFG_ICS&t;0x00000002&t;/* Ignore Carrier Sense&t;&t;*/
DECL|macro|MAC_TXCFG_ICOLL
mdefine_line|#define MAC_TXCFG_ICOLL&t;0x00000004&t;/* Ignore Collisions&t;&t;*/
DECL|macro|MAC_TXCFG_EIPG0
mdefine_line|#define MAC_TXCFG_EIPG0&t;0x00000008&t;/* Enable IPG0&t;&t;&t;*/
DECL|macro|MAC_TXCFG_NGU
mdefine_line|#define MAC_TXCFG_NGU&t;0x00000010&t;/* Never Give Up&t;&t;*/
DECL|macro|MAC_TXCFG_NGUL
mdefine_line|#define MAC_TXCFG_NGUL&t;0x00000020&t;/* Never Give Up Limit&t;&t;*/
DECL|macro|MAC_TXCFG_NBO
mdefine_line|#define MAC_TXCFG_NBO&t;0x00000040&t;/* No Backoff&t;&t;&t;*/
DECL|macro|MAC_TXCFG_SD
mdefine_line|#define MAC_TXCFG_SD&t;0x00000080&t;/* Slow Down&t;&t;&t;*/
DECL|macro|MAC_TXCFG_NFCS
mdefine_line|#define MAC_TXCFG_NFCS&t;0x00000100&t;/* No FCS&t;&t;&t;*/
DECL|macro|MAC_TXCFG_TCE
mdefine_line|#define MAC_TXCFG_TCE&t;0x00000200&t;/* TX Carrier Extension&t;&t;*/
multiline_comment|/* RX MAC Configuration Register.&n; *&n; * NOTE: The RX MAC Enable bit must be cleared and polled until&n; *&t; zero before any other bits in this register are changed.&n; *&n; *&t; Similar rules apply to the Hash Filter Enable bit when&n; *&t; programming the hash table registers, and the Address Filter&n; *&t; Enable bit when programming the address filter registers.&n; */
DECL|macro|MAC_RXCFG_ENAB
mdefine_line|#define MAC_RXCFG_ENAB&t;0x00000001&t;/* RX MAC Enable&t;&t;*/
DECL|macro|MAC_RXCFG_SPAD
mdefine_line|#define MAC_RXCFG_SPAD&t;0x00000002&t;/* Strip Pad&t;&t;&t;*/
DECL|macro|MAC_RXCFG_SFCS
mdefine_line|#define MAC_RXCFG_SFCS&t;0x00000004&t;/* Strip FCS&t;&t;&t;*/
DECL|macro|MAC_RXCFG_PROM
mdefine_line|#define MAC_RXCFG_PROM&t;0x00000008&t;/* Promiscuous Mode&t;&t;*/
DECL|macro|MAC_RXCFG_PGRP
mdefine_line|#define MAC_RXCFG_PGRP&t;0x00000010&t;/* Promiscuous Group&t;&t;*/
DECL|macro|MAC_RXCFG_HFE
mdefine_line|#define MAC_RXCFG_HFE&t;0x00000020&t;/* Hash Filter Enable&t;&t;*/
DECL|macro|MAC_RXCFG_AFE
mdefine_line|#define MAC_RXCFG_AFE&t;0x00000040&t;/* Address Filter Enable&t;*/
DECL|macro|MAC_RXCFG_DDE
mdefine_line|#define MAC_RXCFG_DDE&t;0x00000080&t;/* Disable Discard on Error&t;*/
DECL|macro|MAC_RXCFG_RCE
mdefine_line|#define MAC_RXCFG_RCE&t;0x00000100&t;/* RX Carrier Extension&t;&t;*/
multiline_comment|/* MAC Control Config Register. */
DECL|macro|MAC_MCCFG_SPE
mdefine_line|#define MAC_MCCFG_SPE&t;0x00000001&t;/* Send Pause Enable&t;&t;*/
DECL|macro|MAC_MCCFG_RPE
mdefine_line|#define MAC_MCCFG_RPE&t;0x00000002&t;/* Receive Pause Enable&t;&t;*/
DECL|macro|MAC_MCCFG_PMC
mdefine_line|#define MAC_MCCFG_PMC&t;0x00000004&t;/* Pass MAC Control&t;&t;*/
multiline_comment|/* XIF Configuration Register.&n; *&n; * NOTE: When leaving or entering loopback mode, a global hardware&n; *       init of GEM should be performed.&n; */
DECL|macro|MAC_XIFCFG_OE
mdefine_line|#define MAC_XIFCFG_OE&t;0x00000001&t;/* MII TX Output Driver Enable&t;*/
DECL|macro|MAC_XIFCFG_LBCK
mdefine_line|#define MAC_XIFCFG_LBCK&t;0x00000002&t;/* Loopback TX to RX&t;&t;*/
DECL|macro|MAC_XIFCFG_DISE
mdefine_line|#define MAC_XIFCFG_DISE&t;0x00000004&t;/* Disable RX path during TX&t;*/
DECL|macro|MAC_XIFCFG_GMII
mdefine_line|#define MAC_XIFCFG_GMII&t;0x00000008&t;/* Use GMII clocks + datapath&t;*/
DECL|macro|MAC_XIFCFG_MBOE
mdefine_line|#define MAC_XIFCFG_MBOE&t;0x00000010&t;/* Controls MII_BUF_EN pin&t;*/
DECL|macro|MAC_XIFCFG_LLED
mdefine_line|#define MAC_XIFCFG_LLED&t;0x00000020&t;/* Force LINKLED# active (low)&t;*/
DECL|macro|MAC_XIFCFG_FLED
mdefine_line|#define MAC_XIFCFG_FLED&t;0x00000040&t;/* Force FDPLXLED# active (low)&t;*/
multiline_comment|/* InterPacketGap0 Register.  This 8-bit value is used as an extension&n; * to the InterPacketGap1 Register.  Specifically it contributes to the&n; * timing of the RX-to-TX IPG.  This value is ignored and presumed to&n; * be zero for TX-to-TX IPG calculations and/or when the Enable IPG0 bit&n; * is cleared in the TX MAC Configuration Register.&n; *&n; * This value in this register in terms of media byte time.&n; *&n; * Recommended value: 0x00&n; */
multiline_comment|/* InterPacketGap1 Register.  This 8-bit value defines the first 2/3&n; * portion of the Inter Packet Gap.&n; *&n; * This value in this register in terms of media byte time.&n; *&n; * Recommended value: 0x08&n; */
multiline_comment|/* InterPacketGap2 Register.  This 8-bit value defines the second 1/3&n; * portion of the Inter Packet Gap.&n; *&n; * This value in this register in terms of media byte time.&n; *&n; * Recommended value: 0x04&n; */
multiline_comment|/* Slot Time Register.  This 10-bit value specifies the slot time&n; * parameter in units of media byte time.  It determines the physical&n; * span of the network.&n; *&n; * Recommended value: 0x40&n; */
multiline_comment|/* Minimum Frame Size Register.  This 10-bit register specifies the&n; * smallest sized frame the TXMAC will send onto the medium, and the&n; * RXMAC will receive from the medium.&n; *&n; * Recommended value: 0x40&n; */
multiline_comment|/* Maximum Frame and Burst Size Register.&n; *&n; * This register specifies two things.  First it specifies the maximum&n; * sized frame the TXMAC will send and the RXMAC will recognize as&n; * valid.  Second, it specifies the maximum run length of a burst of&n; * packets sent in half-duplex gigabit modes.&n; *&n; * Recommended value: 0x200005ee&n; */
DECL|macro|MAC_MAXFSZ_MFS
mdefine_line|#define MAC_MAXFSZ_MFS&t;0x00007fff&t;/* Max Frame Size&t;&t;*/
DECL|macro|MAC_MAXFSZ_MBS
mdefine_line|#define MAC_MAXFSZ_MBS&t;0x7fff0000&t;/* Max Burst Size&t;&t;*/
multiline_comment|/* PA Size Register.  This 10-bit register specifies the number of preamble&n; * bytes which will be transmitted at the beginning of each frame.  A&n; * value of two or greater should be programmed here.&n; *&n; * Recommended value: 0x07&n; */
multiline_comment|/* Jam Size Register.  This 4-bit register specifies the duration of&n; * the jam in units of media byte time.&n; *&n; * Recommended value: 0x04&n; */
multiline_comment|/* Attempts Limit Register.  This 8-bit register specifies the number&n; * of attempts that the TXMAC will make to transmit a frame, before it&n; * resets its Attempts Counter.  After reaching the Attempts Limit the&n; * TXMAC may or may not drop the frame, as determined by the NGU&n; * (Never Give Up) and NGUL (Never Give Up Limit) bits in the TXMAC&n; * Configuration Register.&n; *&n; * Recommended value: 0x10&n; */
multiline_comment|/* MAX Control Type Register.  This 16-bit register specifies the&n; * &quot;type&quot; field of a MAC Control frame.  The TXMAC uses this field to&n; * encapsulate the MAC Control frame for transmission, and the RXMAC&n; * uses it for decoding valid MAC Control frames received from the&n; * network.&n; *&n; * Recommended value: 0x8808&n; */
multiline_comment|/* MAC Address Registers.  Each of these registers specify the&n; * ethernet MAC of the interface, 16-bits at a time.  Register&n; * 0 specifies bits [47:32], register 1 bits [31:16], and register&n; * 2 bits [15:0].&n; *&n; * Registers 3 through and including 5 specify an alternate&n; * MAC address for the interface.&n; *&n; * Registers 6 through and including 8 specify the MAC Control&n; * Address, which must be the reserved multicast address for MAC&n; * Control frames.&n; *&n; * Example: To program primary station address a:b:c:d:e:f into&n; *&t;    the chip.&n; *&t;&t;MAC_Address_2 = (a &lt;&lt; 8) | b&n; *&t;&t;MAC_Address_1 = (c &lt;&lt; 8) | d&n; *&t;&t;MAC_Address_0 = (e &lt;&lt; 8) | f&n; */
multiline_comment|/* Address Filter Registers.  Registers 0 through 2 specify bit&n; * fields [47:32] through [15:0], respectively, of the address&n; * filter.  The Address Filter 2&amp;1 Mask Register denotes the 8-bit&n; * nibble mask for Address Filter Registers 2 and 1.  The Address&n; * Filter 0 Mask Register denotes the 16-bit mask for the Address&n; * Filter Register 0.&n; */
multiline_comment|/* Hash Table Registers.  Registers 0 through 15 specify bit fields&n; * [255:240] through [15:0], respectively, of the hash table.&n; */
multiline_comment|/* Statistics Registers.  All of these registers are 16-bits and&n; * track occurances of a specific event.  GEM can be configured&n; * to interrupt the host cpu when any of these counters overflow.&n; * They should all be explicitly initialized to zero when the interface&n; * is brought up.&n; */
multiline_comment|/* Random Number Seed Register.  This 10-bit value is used as the&n; * RNG seed inside GEM for the CSMA/CD backoff algorithm.  It is&n; * recommended to program this register to the 10 LSB of the&n; * interfaces MAC address.&n; */
multiline_comment|/* Pause Timer, read-only.  This 16-bit timer is used to time the pause&n; * interval as indicated by a received pause flow control frame.&n; * A non-zero value in this timer indicates that the MAC is currently in&n; * the paused state.&n; */
multiline_comment|/* MIF Registers */
DECL|macro|MIF_BBCLK
mdefine_line|#define MIF_BBCLK&t;0x6200UL&t;/* MIF Bit-Bang Clock&t;&t;*/
DECL|macro|MIF_BBDATA
mdefine_line|#define MIF_BBDATA&t;0x6204UL&t;/* MIF Bit-Band Data&t;&t;*/
DECL|macro|MIF_BBOENAB
mdefine_line|#define MIF_BBOENAB&t;0x6208UL&t;/* MIF Bit-Bang Output Enable&t;*/
DECL|macro|MIF_FRAME
mdefine_line|#define MIF_FRAME&t;0x620CUL&t;/* MIF Frame/Output Register&t;*/
DECL|macro|MIF_CFG
mdefine_line|#define MIF_CFG&t;&t;0x6210UL&t;/* MIF Configuration Register&t;*/
DECL|macro|MIF_MASK
mdefine_line|#define MIF_MASK&t;0x6214UL&t;/* MIF Mask Register&t;&t;*/
DECL|macro|MIF_STATUS
mdefine_line|#define MIF_STATUS&t;0x6218UL&t;/* MIF Status Register&t;&t;*/
DECL|macro|MIF_SMACHINE
mdefine_line|#define MIF_SMACHINE&t;0x621CUL&t;/* MIF State Machine Register&t;*/
multiline_comment|/* MIF Bit-Bang Clock.  This 1-bit register is used to generate the&n; * MDC clock waveform on the MII Management Interface when the MIF is&n; * programmed in the &quot;Bit-Bang&quot; mode.  Writing a &squot;1&squot; after a &squot;0&squot; into&n; * this register will create a rising edge on the MDC, while writing&n; * a &squot;0&squot; after a &squot;1&squot; will create a falling edge.  For every bit that&n; * is transferred on the management interface, both edges have to be&n; * generated.&n; */
multiline_comment|/* MIF Bit-Bang Data.  This 1-bit register is used to generate the&n; * outgoing data (MDO) on the MII Management Interface when the MIF&n; * is programmed in the &quot;Bit-Bang&quot; mode.  The daa will be steered to the&n; * appropriate MDIO based on the state of the PHY_Select bit in the MIF&n; * Configuration Register.&n; */
multiline_comment|/* MIF Big-Band Output Enable.  THis 1-bit register is used to enable&n; * (&squot;1&squot;) or disable (&squot;0&squot;) the I-directional driver on the MII when the&n; * MIF is programmed in the &quot;Bit-Bang&quot; mode.  The MDIO should be enabled&n; * when data bits are transferred from the MIF to the transceiver, and it&n; * should be disabled when the interface is idle or when data bits are&n; * transferred from the transceiver to the MIF (data portion of a read&n; * instruction).  Only one MDIO will be enabled at a given time, depending&n; * on the state of the PHY_Select bit in the MIF Configuration Register.&n; */
multiline_comment|/* MIF Configuration Register.  This 15-bit register controls the operation&n; * of the MIF.&n; */
DECL|macro|MIF_CFG_PSELECT
mdefine_line|#define MIF_CFG_PSELECT&t;0x00000001&t;/* Xcvr slct: 0=mdio0 1=mdio1&t;*/
DECL|macro|MIF_CFG_POLL
mdefine_line|#define MIF_CFG_POLL&t;0x00000002&t;/* Enable polling mechanism&t;*/
DECL|macro|MIF_CFG_BBMODE
mdefine_line|#define MIF_CFG_BBMODE&t;0x00000004&t;/* 1=bit-bang 0=frame mode&t;*/
DECL|macro|MIF_CFG_PRADDR
mdefine_line|#define MIF_CFG_PRADDR&t;0x000000f8&t;/* Xcvr poll register address&t;*/
DECL|macro|MIF_CFG_MDI0
mdefine_line|#define MIF_CFG_MDI0&t;0x00000100&t;/* MDIO_0 present or read-bit&t;*/
DECL|macro|MIF_CFG_MDI1
mdefine_line|#define MIF_CFG_MDI1&t;0x00000200&t;/* MDIO_1 present or read-bit&t;*/
DECL|macro|MIF_CFG_PPADDR
mdefine_line|#define MIF_CFG_PPADDR&t;0x00007c00&t;/* Xcvr poll PHY address&t;*/
multiline_comment|/* MIF Frame/Output Register.  This 32-bit register allows the host to&n; * communicate with a transceiver in frame mode (as opposed to big-bang&n; * mode).  Writes by the host specify an instrution.  After being issued&n; * the host must poll this register for completion.  Also, after&n; * completion this register holds the data returned by the transceiver&n; * if applicable.&n; */
DECL|macro|MIF_FRAME_ST
mdefine_line|#define MIF_FRAME_ST&t;0xc0000000&t;/* STart of frame&t;&t;*/
DECL|macro|MIF_FRAME_OP
mdefine_line|#define MIF_FRAME_OP&t;0x30000000&t;/* OPcode&t;&t;&t;*/
DECL|macro|MIF_FRAME_PHYAD
mdefine_line|#define MIF_FRAME_PHYAD&t;0x0f800000&t;/* PHY ADdress&t;&t;&t;*/
DECL|macro|MIF_FRAME_REGAD
mdefine_line|#define MIF_FRAME_REGAD&t;0x007c0000&t;/* REGister ADdress&t;&t;*/
DECL|macro|MIF_FRAME_TAMSB
mdefine_line|#define MIF_FRAME_TAMSB&t;0x00020000&t;/* Turn Around MSB&t;&t;*/
DECL|macro|MIF_FRAME_TALSB
mdefine_line|#define MIF_FRAME_TALSB&t;0x00010000&t;/* Turn Around LSB&t;&t;*/
DECL|macro|MIF_FRAME_DATA
mdefine_line|#define MIF_FRAME_DATA&t;0x0000ffff&t;/* Instruction Payload&t;&t;*/
multiline_comment|/* MIF Status Register.  This register reports status when the MIF is&n; * operating in the poll mode.  The poll status field is auto-clearing&n; * on read.&n; */
DECL|macro|MIF_STATUS_DATA
mdefine_line|#define MIF_STATUS_DATA&t;0xffff0000&t;/* Live image of XCVR reg&t;*/
DECL|macro|MIF_STATUS_STAT
mdefine_line|#define MIF_STATUS_STAT&t;0x0000ffff&t;/* Which bits have changed&t;*/
multiline_comment|/* MIF Mask Register.  This 16-bit register is used when in poll mode&n; * to say which bits of the polled register will cause an interrupt&n; * when changed.&n; */
multiline_comment|/* PCS/Serialink Registers */
DECL|macro|PCS_MIICTRL
mdefine_line|#define PCS_MIICTRL&t;0x9000UL&t;/* PCS MII Control Register&t;*/
DECL|macro|PCS_MIISTAT
mdefine_line|#define PCS_MIISTAT&t;0x9004UL&t;/* PCS MII Status Register&t;*/
DECL|macro|PCS_MIIADV
mdefine_line|#define PCS_MIIADV&t;0x9008UL&t;/* PCS MII Advertisement Reg&t;*/
DECL|macro|PCS_MIILP
mdefine_line|#define PCS_MIILP&t;0x900CUL&t;/* PCS MII Link Partner Ability&t;*/
DECL|macro|PCS_CFG
mdefine_line|#define PCS_CFG&t;&t;0x9010UL&t;/* PCS Configuration Register&t;*/
DECL|macro|PCS_SMACHINE
mdefine_line|#define PCS_SMACHINE&t;0x9014UL&t;/* PCS State Machine Register&t;*/
DECL|macro|PCS_ISTAT
mdefine_line|#define PCS_ISTAT&t;0x9018UL&t;/* PCS Interrupt Status Reg&t;*/
DECL|macro|PCS_DMODE
mdefine_line|#define PCS_DMODE&t;0x9050UL&t;/* Datapath Mode Register&t;*/
DECL|macro|PCS_SCTRL
mdefine_line|#define PCS_SCTRL&t;0x9054UL&t;/* Serialink Control Register&t;*/
DECL|macro|PCS_SOS
mdefine_line|#define PCS_SOS&t;&t;0x9058UL&t;/* Shared Output Select Reg&t;*/
DECL|macro|PCS_SSTATE
mdefine_line|#define PCS_SSTATE&t;0x905CUL&t;/* Serialink State Register&t;*/
multiline_comment|/* PCD MII Control Register. */
DECL|macro|PCS_MIICTRL_SPD
mdefine_line|#define PCS_MIICTRL_SPD&t;0x00000040&t;/* Read as one, writes ignored&t;*/
DECL|macro|PCS_MIICTRL_CT
mdefine_line|#define PCS_MIICTRL_CT&t;0x00000080&t;/* Force COL signal active&t;*/
DECL|macro|PCS_MIICTRL_DM
mdefine_line|#define PCS_MIICTRL_DM&t;0x00000100&t;/* Duplex mode, forced low&t;*/
DECL|macro|PCS_MIICTRL_RAN
mdefine_line|#define PCS_MIICTRL_RAN&t;0x00000200&t;/* Restart auto-neg, self clear&t;*/
DECL|macro|PCS_MIICTRL_ISO
mdefine_line|#define PCS_MIICTRL_ISO&t;0x00000400&t;/* Read as zero, writes ignored&t;*/
DECL|macro|PCS_MIICTRL_PD
mdefine_line|#define PCS_MIICTRL_PD&t;0x00000800&t;/* Read as zero, writes ignored&t;*/
DECL|macro|PCS_MIICTRL_ANE
mdefine_line|#define PCS_MIICTRL_ANE&t;0x00001000&t;/* Auto-neg enable&t;&t;*/
DECL|macro|PCS_MIICTRL_SS
mdefine_line|#define PCS_MIICTRL_SS&t;0x00002000&t;/* Read as zero, writes ignored&t;*/
DECL|macro|PCS_MIICTRL_WB
mdefine_line|#define PCS_MIICTRL_WB&t;0x00004000&t;/* Wrapback, loopback at 10-bit&n;&t;&t;&t;&t;&t; * input side of Serialink&n;&t;&t;&t;&t;&t; */
DECL|macro|PCS_MIICTRL_RST
mdefine_line|#define PCS_MIICTRL_RST&t;0x00008000&t;/* Resets PCS, self clearing&t;*/
multiline_comment|/* PCS MII Status Register. */
DECL|macro|PCS_MIISTAT_EC
mdefine_line|#define PCS_MIISTAT_EC&t;0x00000001&t;/* Ext Capability: Read as zero&t;*/
DECL|macro|PCS_MIISTAT_JD
mdefine_line|#define PCS_MIISTAT_JD&t;0x00000002&t;/* Jabber Detect: Read as zero&t;*/
DECL|macro|PCS_MIISTAT_LS
mdefine_line|#define PCS_MIISTAT_LS&t;0x00000004&t;/* Link Status: 1=up 0=down&t;*/
DECL|macro|PCS_MIISTAT_ANA
mdefine_line|#define PCS_MIISTAT_ANA&t;0x00000008&t;/* Auto-neg Ability, always 1&t;*/
DECL|macro|PCS_MIISTAT_RF
mdefine_line|#define PCS_MIISTAT_RF&t;0x00000010&t;/* Remote Fault&t;&t;&t;*/
DECL|macro|PCS_MIISTAT_ANC
mdefine_line|#define PCS_MIISTAT_ANC&t;0x00000020&t;/* Auto-neg complete&t;&t;*/
DECL|macro|PCS_MIISTAT_ES
mdefine_line|#define PCS_MIISTAT_ES&t;0x00000100&t;/* Extended Status, always 1&t;*/
multiline_comment|/* PCS MII Advertisement Register. */
DECL|macro|PCS_MIIADV_FD
mdefine_line|#define PCS_MIIADV_FD&t;0x00000020&t;/* Advertise Full Duplex&t;*/
DECL|macro|PCS_MIIADV_HD
mdefine_line|#define PCS_MIIADV_HD&t;0x00000040&t;/* Advertise Half Duplex&t;*/
DECL|macro|PCS_MIIADV_SP
mdefine_line|#define PCS_MIIADV_SP&t;0x00000080&t;/* Advertise Symmetric Pause&t;*/
DECL|macro|PCS_MIIADV_AP
mdefine_line|#define PCS_MIIADV_AP&t;0x00000100&t;/* Advertise Asymmetric Pause&t;*/
DECL|macro|PCS_MIIADV_RF
mdefine_line|#define PCS_MIIADV_RF&t;0x00003000&t;/* Remote Fault&t;&t;&t;*/
DECL|macro|PCS_MIIADV_ACK
mdefine_line|#define PCS_MIIADV_ACK&t;0x00004000&t;/* Read-only&t;&t;&t;*/
DECL|macro|PCS_MIIADV_NP
mdefine_line|#define PCS_MIIADV_NP&t;0x00008000&t;/* Next-page, forced low&t;*/
multiline_comment|/* PCS MII Link Partner Ability Register.   This register is equivalent&n; * to the Link Partnet Ability Register of the standard MII register set.&n; * It&squot;s layout corresponds to the PCS MII Advertisement Register.&n; */
multiline_comment|/* PCS Configuration Register. */
DECL|macro|PCS_CFG_ENABLE
mdefine_line|#define PCS_CFG_ENABLE&t;0x00000001&t;/* Must be zero while changing&n;&t;&t;&t;&t;&t; * PCS MII advertisement reg.&n;&t;&t;&t;&t;&t; */
DECL|macro|PCS_CFG_SDO
mdefine_line|#define PCS_CFG_SDO&t;0x00000002&t;/* Signal detect override&t;*/
DECL|macro|PCS_CFG_SDL
mdefine_line|#define PCS_CFG_SDL&t;0x00000004&t;/* Signal detect active low&t;*/
DECL|macro|PCS_CFG_JS
mdefine_line|#define PCS_CFG_JS&t;0x00000018&t;/* Jitter-study:&n;&t;&t;&t;&t;&t; * 0 = normal operation&n;&t;&t;&t;&t;&t; * 1 = high-frequency test pattern&n;&t;&t;&t;&t;&t; * 2 = low-frequency test pattern&n;&t;&t;&t;&t;&t; * 3 = reserved&n;&t;&t;&t;&t;&t; */
DECL|macro|PCS_CFG_TO
mdefine_line|#define PCS_CFG_TO&t;0x00000020&t;/* 10ms auto-neg timer override&t;*/
multiline_comment|/* PCS Interrupt Status Register.  This register is self-clearing&n; * when read.&n; */
DECL|macro|PCS_ISTAT_LSC
mdefine_line|#define PCS_ISTAT_LSC&t;0x00000004&t;/* Link Status Change&t;&t;*/
multiline_comment|/* Datapath Mode Register. */
DECL|macro|PCS_DMODE_SM
mdefine_line|#define PCS_DMODE_SM&t;0x00000001&t;/* 1 = use internal Serialink&t;*/
DECL|macro|PCS_DMODE_ESM
mdefine_line|#define PCS_DMODE_ESM&t;0x00000002&t;/* External SERDES mode&t;&t;*/
DECL|macro|PCS_DMODE_MGM
mdefine_line|#define PCS_DMODE_MGM&t;0x00000004&t;/* MII/GMII mode&t;&t;*/
DECL|macro|PCS_DMODE_GMOE
mdefine_line|#define PCS_DMODE_GMOE&t;0x00000008&t;/* GMII Output Enable&t;&t;*/
multiline_comment|/* Serialink Control Register.&n; *&n; * NOTE: When in SERDES mode, the loopback bit has inverse logic.&n; */
DECL|macro|PCS_SCTRL_LOOP
mdefine_line|#define PCS_SCTRL_LOOP&t;0x00000001&t;/* Loopback enable&t;&t;*/
DECL|macro|PCS_SCTRL_ESCD
mdefine_line|#define PCS_SCTRL_ESCD&t;0x00000002&t;/* Enable sync char detection&t;*/
DECL|macro|PCS_SCTRL_LOCK
mdefine_line|#define PCS_SCTRL_LOCK&t;0x00000004&t;/* Lock to reference clock&t;*/
DECL|macro|PCS_SCTRL_EMP
mdefine_line|#define PCS_SCTRL_EMP&t;0x00000018&t;/* Output driver emphasis&t;*/
DECL|macro|PCS_SCTRL_STEST
mdefine_line|#define PCS_SCTRL_STEST&t;0x000001c0&t;/* Self test patterns&t;&t;*/
DECL|macro|PCS_SCTRL_PDWN
mdefine_line|#define PCS_SCTRL_PDWN&t;0x00000200&t;/* Software power-down&t;&t;*/
DECL|macro|PCS_SCTRL_RXZ
mdefine_line|#define PCS_SCTRL_RXZ&t;0x00000c00&t;/* PLL input to Serialink&t;*/
DECL|macro|PCS_SCTRL_RXP
mdefine_line|#define PCS_SCTRL_RXP&t;0x00003000&t;/* PLL input to Serialink&t;*/
DECL|macro|PCS_SCTRL_TXZ
mdefine_line|#define PCS_SCTRL_TXZ&t;0x0000c000&t;/* PLL input to Serialink&t;*/
DECL|macro|PCS_SCTRL_TXP
mdefine_line|#define PCS_SCTRL_TXP&t;0x00030000&t;/* PLL input to Serialink&t;*/
multiline_comment|/* Shared Output Select Register.  For test and debug, allows multiplexing&n; * test outputs into the PROM address pins.  Set to zero for normal&n; * operation.&n; */
DECL|macro|PCS_SOS_PADDR
mdefine_line|#define PCS_SOS_PADDR&t;0x00000003&t;/* PROM Address&t;&t;&t;*/
multiline_comment|/* PROM Image Space */
DECL|macro|PROM_START
mdefine_line|#define PROM_START&t;0x100000UL&t;/* Expansion ROM run time access*/
DECL|macro|PROM_SIZE
mdefine_line|#define PROM_SIZE&t;0x0fffffUL&t;/* Size of ROM&t;&t;&t;*/
DECL|macro|PROM_END
mdefine_line|#define PROM_END&t;0x200000UL&t;/* End of ROM&t;&t;&t;*/
multiline_comment|/* MII definitions missing from mii.h */
DECL|macro|BMCR_SPD2
mdefine_line|#define BMCR_SPD2&t;0x0040&t;&t;/* Gigabit enable? (bcm5411)&t;*/
DECL|macro|LPA_PAUSE
mdefine_line|#define LPA_PAUSE&t;0x0400
multiline_comment|/* More PHY registers (specific to Broadcom models) */
multiline_comment|/* MII BCM5201 MULTIPHY interrupt register */
DECL|macro|MII_BCM5201_INTERRUPT
mdefine_line|#define MII_BCM5201_INTERRUPT&t;&t;&t;0x1A
DECL|macro|MII_BCM5201_INTERRUPT_INTENABLE
mdefine_line|#define MII_BCM5201_INTERRUPT_INTENABLE&t;&t;0x4000
DECL|macro|MII_BCM5201_AUXMODE2
mdefine_line|#define MII_BCM5201_AUXMODE2&t;&t;&t;0x1B
DECL|macro|MII_BCM5201_AUXMODE2_LOWPOWER
mdefine_line|#define MII_BCM5201_AUXMODE2_LOWPOWER&t;&t;0x0008
DECL|macro|MII_BCM5201_MULTIPHY
mdefine_line|#define MII_BCM5201_MULTIPHY                    0x1E
multiline_comment|/* MII BCM5201 MULTIPHY register bits */
DECL|macro|MII_BCM5201_MULTIPHY_SERIALMODE
mdefine_line|#define MII_BCM5201_MULTIPHY_SERIALMODE         0x0002
DECL|macro|MII_BCM5201_MULTIPHY_SUPERISOLATE
mdefine_line|#define MII_BCM5201_MULTIPHY_SUPERISOLATE       0x0008
multiline_comment|/* MII BCM5400 1000-BASET Control register */
DECL|macro|MII_BCM5400_GB_CONTROL
mdefine_line|#define MII_BCM5400_GB_CONTROL&t;&t;&t;0x09
DECL|macro|MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP
mdefine_line|#define MII_BCM5400_GB_CONTROL_FULLDUPLEXCAP&t;0x0200
multiline_comment|/* MII BCM5400 AUXCONTROL register */
DECL|macro|MII_BCM5400_AUXCONTROL
mdefine_line|#define MII_BCM5400_AUXCONTROL                  0x18
DECL|macro|MII_BCM5400_AUXCONTROL_PWR10BASET
mdefine_line|#define MII_BCM5400_AUXCONTROL_PWR10BASET       0x0004
multiline_comment|/* MII BCM5400 AUXSTATUS register */
DECL|macro|MII_BCM5400_AUXSTATUS
mdefine_line|#define MII_BCM5400_AUXSTATUS                   0x19
DECL|macro|MII_BCM5400_AUXSTATUS_LINKMODE_MASK
mdefine_line|#define MII_BCM5400_AUXSTATUS_LINKMODE_MASK     0x0700
DECL|macro|MII_BCM5400_AUXSTATUS_LINKMODE_SHIFT
mdefine_line|#define MII_BCM5400_AUXSTATUS_LINKMODE_SHIFT    8  
multiline_comment|/* When it can, GEM internally caches 4 aligned TX descriptors&n; * at a time, so that it can use full cacheline DMA reads.&n; *&n; * Note that unlike HME, there is no ownership bit in the descriptor&n; * control word.  The same functionality is obtained via the TX-Kick&n; * and TX-Complete registers.  As a result, GEM need not write back&n; * updated values to the TX descriptor ring, it only performs reads.&n; *&n; * Since TX descriptors are never modified by GEM, the driver can&n; * use the buffer DMA address as a place to keep track of allocated&n; * DMA mappings for a transmitted packet.&n; */
DECL|struct|gem_txd
r_struct
id|gem_txd
(brace
DECL|member|control_word
id|u64
id|control_word
suffix:semicolon
DECL|member|buffer
id|u64
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TXDCTRL_BUFSZ
mdefine_line|#define TXDCTRL_BUFSZ&t;0x0000000000007fff&t;/* Buffer Size&t;&t;*/
DECL|macro|TXDCTRL_CSTART
mdefine_line|#define TXDCTRL_CSTART&t;0x00000000001f8000&t;/* CSUM Start Offset&t;*/
DECL|macro|TXDCTRL_COFF
mdefine_line|#define TXDCTRL_COFF&t;0x000000001fe00000&t;/* CSUM Stuff Offset&t;*/
DECL|macro|TXDCTRL_CENAB
mdefine_line|#define TXDCTRL_CENAB&t;0x0000000020000000&t;/* CSUM Enable&t;&t;*/
DECL|macro|TXDCTRL_EOF
mdefine_line|#define TXDCTRL_EOF&t;0x0000000040000000&t;/* End of Frame&t;&t;*/
DECL|macro|TXDCTRL_SOF
mdefine_line|#define TXDCTRL_SOF&t;0x0000000080000000&t;/* Start of Frame&t;*/
DECL|macro|TXDCTRL_INTME
mdefine_line|#define TXDCTRL_INTME&t;0x0000000100000000&t;/* &quot;Interrupt Me&quot;&t;*/
DECL|macro|TXDCTRL_NOCRC
mdefine_line|#define TXDCTRL_NOCRC&t;0x0000000200000000&t;/* No CRC Present&t;*/
multiline_comment|/* GEM requires that RX descriptors are provided four at a time,&n; * aligned.  Also, the RX ring may not wrap around.  This means that&n; * there will be at least 4 unused desciptor entries in the middle&n; * of the RX ring at all times.&n; *&n; * Similar to HME, GEM assumes that it can write garbage bytes before&n; * the beginning of the buffer and right after the end in order to DMA&n; * whole cachelines.&n; *&n; * Unlike for TX, GEM does update the status word in the RX descriptors&n; * when packets arrive.  Therefore an ownership bit does exist in the&n; * RX descriptors.  It is advisory, GEM clears it but does not check&n; * it in any way.  So when buffers are posted to the RX ring (via the&n; * RX Kick register) by the driver it must make sure the buffers are&n; * truly ready and that the ownership bits are set properly.&n; *&n; * Even though GEM modifies the RX descriptors, it guarentees that the&n; * buffer DMA address field will stay the same when it performs these&n; * updates.  Therefore it can be used to keep track of DMA mappings&n; * by the host driver just as in the TX descriptor case above.&n; */
DECL|struct|gem_rxd
r_struct
id|gem_rxd
(brace
DECL|member|status_word
id|u64
id|status_word
suffix:semicolon
DECL|member|buffer
id|u64
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RXDCTRL_TCPCSUM
mdefine_line|#define RXDCTRL_TCPCSUM&t;0x000000000000ffff&t;/* TCP Pseudo-CSUM&t;*/
DECL|macro|RXDCTRL_BUFSZ
mdefine_line|#define RXDCTRL_BUFSZ&t;0x000000007fff0000&t;/* Buffer Size&t;&t;*/
DECL|macro|RXDCTRL_OWN
mdefine_line|#define RXDCTRL_OWN&t;0x0000000080000000&t;/* GEM owns this entry&t;*/
DECL|macro|RXDCTRL_HASHVAL
mdefine_line|#define RXDCTRL_HASHVAL&t;0x0ffff00000000000&t;/* Hash Value&t;&t;*/
DECL|macro|RXDCTRL_HPASS
mdefine_line|#define RXDCTRL_HPASS&t;0x1000000000000000&t;/* Passed Hash Filter&t;*/
DECL|macro|RXDCTRL_ALTMAC
mdefine_line|#define RXDCTRL_ALTMAC&t;0x2000000000000000&t;/* Matched ALT MAC&t;*/
DECL|macro|RXDCTRL_BAD
mdefine_line|#define RXDCTRL_BAD&t;0x4000000000000000&t;/* Frame has bad CRC&t;*/
DECL|macro|RXDCTRL_FRESH
mdefine_line|#define RXDCTRL_FRESH(gp)&t;&bslash;&n;&t;((((RX_BUF_ALLOC_SIZE(gp) - RX_OFFSET) &lt;&lt; 16) &amp; RXDCTRL_BUFSZ) | &bslash;&n;&t; RXDCTRL_OWN)
DECL|macro|TX_RING_SIZE
mdefine_line|#define TX_RING_SIZE 128
DECL|macro|RX_RING_SIZE
mdefine_line|#define RX_RING_SIZE 128
macro_line|#if TX_RING_SIZE == 32
DECL|macro|TXDMA_CFG_BASE
mdefine_line|#define TXDMA_CFG_BASE&t;TXDMA_CFG_RINGSZ_32
macro_line|#elif TX_RING_SIZE == 64
DECL|macro|TXDMA_CFG_BASE
mdefine_line|#define TXDMA_CFG_BASE&t;TXDMA_CFG_RINGSZ_64
macro_line|#elif TX_RING_SIZE == 128
DECL|macro|TXDMA_CFG_BASE
mdefine_line|#define TXDMA_CFG_BASE&t;TXDMA_CFG_RINGSZ_128
macro_line|#elif TX_RING_SIZE == 256
DECL|macro|TXDMA_CFG_BASE
mdefine_line|#define TXDMA_CFG_BASE&t;TXDMA_CFG_RINGSZ_256
macro_line|#elif TX_RING_SIZE == 512
DECL|macro|TXDMA_CFG_BASE
mdefine_line|#define TXDMA_CFG_BASE&t;TXDMA_CFG_RINGSZ_512
macro_line|#elif TX_RING_SIZE == 1024
DECL|macro|TXDMA_CFG_BASE
mdefine_line|#define TXDMA_CFG_BASE&t;TXDMA_CFG_RINGSZ_1K
macro_line|#elif TX_RING_SIZE == 2048
DECL|macro|TXDMA_CFG_BASE
mdefine_line|#define TXDMA_CFG_BASE&t;TXDMA_CFG_RINGSZ_2K
macro_line|#elif TX_RING_SIZE == 4096
DECL|macro|TXDMA_CFG_BASE
mdefine_line|#define TXDMA_CFG_BASE&t;TXDMA_CFG_RINGSZ_4K
macro_line|#elif TX_RING_SIZE == 8192
DECL|macro|TXDMA_CFG_BASE
mdefine_line|#define TXDMA_CFG_BASE&t;TXDMA_CFG_RINGSZ_8K
macro_line|#else
macro_line|#error TX_RING_SIZE value is illegal...
macro_line|#endif
macro_line|#if RX_RING_SIZE == 32
DECL|macro|RXDMA_CFG_BASE
mdefine_line|#define RXDMA_CFG_BASE&t;RXDMA_CFG_RINGSZ_32
macro_line|#elif RX_RING_SIZE == 64
DECL|macro|RXDMA_CFG_BASE
mdefine_line|#define RXDMA_CFG_BASE&t;RXDMA_CFG_RINGSZ_64
macro_line|#elif RX_RING_SIZE == 128
DECL|macro|RXDMA_CFG_BASE
mdefine_line|#define RXDMA_CFG_BASE&t;RXDMA_CFG_RINGSZ_128
macro_line|#elif RX_RING_SIZE == 256
DECL|macro|RXDMA_CFG_BASE
mdefine_line|#define RXDMA_CFG_BASE&t;RXDMA_CFG_RINGSZ_256
macro_line|#elif RX_RING_SIZE == 512
DECL|macro|RXDMA_CFG_BASE
mdefine_line|#define RXDMA_CFG_BASE&t;RXDMA_CFG_RINGSZ_512
macro_line|#elif RX_RING_SIZE == 1024
DECL|macro|RXDMA_CFG_BASE
mdefine_line|#define RXDMA_CFG_BASE&t;RXDMA_CFG_RINGSZ_1K
macro_line|#elif RX_RING_SIZE == 2048
DECL|macro|RXDMA_CFG_BASE
mdefine_line|#define RXDMA_CFG_BASE&t;RXDMA_CFG_RINGSZ_2K
macro_line|#elif RX_RING_SIZE == 4096
DECL|macro|RXDMA_CFG_BASE
mdefine_line|#define RXDMA_CFG_BASE&t;RXDMA_CFG_RINGSZ_4K
macro_line|#elif RX_RING_SIZE == 8192
DECL|macro|RXDMA_CFG_BASE
mdefine_line|#define RXDMA_CFG_BASE&t;RXDMA_CFG_RINGSZ_8K
macro_line|#else
macro_line|#error RX_RING_SIZE is illegal...
macro_line|#endif
DECL|macro|NEXT_TX
mdefine_line|#define NEXT_TX(N)&t;(((N) + 1) &amp; (TX_RING_SIZE - 1))
DECL|macro|NEXT_RX
mdefine_line|#define NEXT_RX(N)&t;(((N) + 1) &amp; (RX_RING_SIZE - 1))
DECL|macro|TX_BUFFS_AVAIL
mdefine_line|#define TX_BUFFS_AVAIL(GP)&t;&t;&t;&t;&t;&bslash;&n;&t;(((GP)-&gt;tx_old &lt;= (GP)-&gt;tx_new) ?&t;&t;&t;&bslash;&n;&t;  (GP)-&gt;tx_old + (TX_RING_SIZE - 1) - (GP)-&gt;tx_new :&t;&bslash;&n;&t;  (GP)-&gt;tx_old - (GP)-&gt;tx_new - 1)
DECL|macro|RX_OFFSET
mdefine_line|#define RX_OFFSET          2
DECL|macro|RX_BUF_ALLOC_SIZE
mdefine_line|#define RX_BUF_ALLOC_SIZE(gp)&t;((gp)-&gt;dev-&gt;mtu + 46 + RX_OFFSET + 64)
DECL|macro|RX_COPY_THRESHOLD
mdefine_line|#define RX_COPY_THRESHOLD  256
macro_line|#if TX_RING_SIZE &lt; 128
DECL|macro|INIT_BLOCK_TX_RING_SIZE
mdefine_line|#define INIT_BLOCK_TX_RING_SIZE&t;&t;128
macro_line|#else
DECL|macro|INIT_BLOCK_TX_RING_SIZE
mdefine_line|#define INIT_BLOCK_TX_RING_SIZE&t;&t;TX_RING_SIZE
macro_line|#endif
macro_line|#if RX_RING_SIZE &lt; 128
DECL|macro|INIT_BLOCK_RX_RING_SIZE
mdefine_line|#define INIT_BLOCK_RX_RING_SIZE&t;&t;128
macro_line|#else
DECL|macro|INIT_BLOCK_RX_RING_SIZE
mdefine_line|#define INIT_BLOCK_RX_RING_SIZE&t;&t;RX_RING_SIZE
macro_line|#endif
DECL|struct|gem_init_block
r_struct
id|gem_init_block
(brace
DECL|member|txd
r_struct
id|gem_txd
id|txd
(braket
id|INIT_BLOCK_TX_RING_SIZE
)braket
suffix:semicolon
DECL|member|rxd
r_struct
id|gem_rxd
id|rxd
(braket
id|INIT_BLOCK_RX_RING_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|gem_phy_type
r_enum
id|gem_phy_type
(brace
DECL|enumerator|phy_mii_mdio0
id|phy_mii_mdio0
comma
DECL|enumerator|phy_mii_mdio1
id|phy_mii_mdio1
comma
DECL|enumerator|phy_serialink
id|phy_serialink
comma
DECL|enumerator|phy_serdes
id|phy_serdes
comma
)brace
suffix:semicolon
DECL|enum|gem_phy_model
r_enum
id|gem_phy_model
(brace
DECL|enumerator|phymod_generic
id|phymod_generic
comma
DECL|enumerator|phymod_bcm5201
id|phymod_bcm5201
comma
DECL|enumerator|phymod_bcm5221
id|phymod_bcm5221
comma
DECL|enumerator|phymod_bcm5400
id|phymod_bcm5400
comma
DECL|enumerator|phymod_bcm5401
id|phymod_bcm5401
comma
DECL|enumerator|phymod_bcm5411
id|phymod_bcm5411
comma
)brace
suffix:semicolon
DECL|enum|link_state
r_enum
id|link_state
(brace
DECL|enumerator|link_down
id|link_down
op_assign
l_int|0
comma
multiline_comment|/* No link, will retry */
DECL|enumerator|link_aneg
id|link_aneg
comma
multiline_comment|/* Autoneg in progress */
DECL|enumerator|link_force_try
id|link_force_try
comma
multiline_comment|/* Try Forced link speed */
DECL|enumerator|link_force_ret
id|link_force_ret
comma
multiline_comment|/* Forced mode worked, retrying autoneg */
DECL|enumerator|link_force_ok
id|link_force_ok
comma
multiline_comment|/* Stay in forced mode */
DECL|enumerator|link_up
id|link_up
multiline_comment|/* Link is up */
)brace
suffix:semicolon
DECL|struct|gem
r_struct
id|gem
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|regs
r_int
r_int
id|regs
suffix:semicolon
DECL|member|rx_new
DECL|member|rx_old
r_int
id|rx_new
comma
id|rx_old
suffix:semicolon
DECL|member|tx_new
DECL|member|tx_old
r_int
id|tx_new
comma
id|tx_old
suffix:semicolon
multiline_comment|/* Set when chip is actually in operational state&n;&t; * (ie. not power managed)&n;&t; */
DECL|member|hw_running
r_int
id|hw_running
suffix:semicolon
DECL|member|opened
r_int
id|opened
suffix:semicolon
DECL|member|pm_sem
r_struct
id|semaphore
id|pm_sem
suffix:semicolon
DECL|member|pm_task
r_struct
id|tq_struct
id|pm_task
suffix:semicolon
DECL|member|pm_timer
r_struct
id|timer_list
id|pm_timer
suffix:semicolon
DECL|member|init_block
r_struct
id|gem_init_block
op_star
id|init_block
suffix:semicolon
DECL|member|rx_skbs
r_struct
id|sk_buff
op_star
id|rx_skbs
(braket
id|RX_RING_SIZE
)braket
suffix:semicolon
DECL|member|tx_skbs
r_struct
id|sk_buff
op_star
id|tx_skbs
(braket
id|RX_RING_SIZE
)braket
suffix:semicolon
DECL|member|msg_enable
id|u32
id|msg_enable
suffix:semicolon
DECL|member|net_stats
r_struct
id|net_device_stats
id|net_stats
suffix:semicolon
DECL|member|phy_type
r_enum
id|gem_phy_type
id|phy_type
suffix:semicolon
DECL|member|phy_mod
r_enum
id|gem_phy_model
id|phy_mod
suffix:semicolon
DECL|member|tx_fifo_sz
r_int
id|tx_fifo_sz
suffix:semicolon
DECL|member|rx_fifo_sz
r_int
id|rx_fifo_sz
suffix:semicolon
DECL|member|rx_pause_off
r_int
id|rx_pause_off
suffix:semicolon
DECL|member|rx_pause_on
r_int
id|rx_pause_on
suffix:semicolon
DECL|member|mii_phy_addr
r_int
id|mii_phy_addr
suffix:semicolon
DECL|member|gigabit_capable
r_int
id|gigabit_capable
suffix:semicolon
multiline_comment|/* Autoneg &amp; PHY control */
DECL|member|link_cntl
r_int
id|link_cntl
suffix:semicolon
DECL|member|link_advertise
r_int
id|link_advertise
suffix:semicolon
DECL|member|link_fcntl
r_int
id|link_fcntl
suffix:semicolon
DECL|member|lstate
r_enum
id|link_state
id|lstate
suffix:semicolon
DECL|member|link_timer
r_struct
id|timer_list
id|link_timer
suffix:semicolon
DECL|member|timer_ticks
r_int
id|timer_ticks
suffix:semicolon
DECL|member|wake_on_lan
r_int
id|wake_on_lan
suffix:semicolon
DECL|member|reset_task
r_struct
id|tq_struct
id|reset_task
suffix:semicolon
DECL|member|reset_task_pending
r_volatile
r_int
id|reset_task_pending
suffix:semicolon
multiline_comment|/* Diagnostic counters and state. */
DECL|member|pause_entered
id|u64
id|pause_entered
suffix:semicolon
DECL|member|pause_last_time_recvd
id|u16
id|pause_last_time_recvd
suffix:semicolon
DECL|member|gblock_dvma
id|dma_addr_t
id|gblock_dvma
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
macro_line|#ifdef CONFIG_ALL_PPC
DECL|member|of_node
r_struct
id|device_node
op_star
id|of_node
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|ALIGNED_RX_SKB_ADDR
mdefine_line|#define ALIGNED_RX_SKB_ADDR(addr) &bslash;&n;        ((((unsigned long)(addr) + (64UL - 1UL)) &amp; ~(64UL - 1UL)) - (unsigned long)(addr))
DECL|function|gem_alloc_skb
r_static
id|__inline__
r_struct
id|sk_buff
op_star
id|gem_alloc_skb
c_func
(paren
r_int
id|size
comma
r_int
id|gfp_flags
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|size
op_plus
l_int|64
comma
id|gfp_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
r_int
id|offset
op_assign
(paren
r_int
)paren
id|ALIGNED_RX_SKB_ADDR
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
id|skb_reserve
c_func
(paren
id|skb
comma
id|offset
)paren
suffix:semicolon
)brace
r_return
id|skb
suffix:semicolon
)brace
macro_line|#endif /* _SUNGEM_H */
eof
