multiline_comment|/*&n; * mace.h - definitions for the registers in the &quot;Big Mac&quot;&n; *  Ethernet controller found in PowerMac G3 models.&n; *&n; * Copyright (C) 1998 Randy Gobbel.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/* The &quot;Big MAC&quot; appears to have some parts in common with the Sun &quot;Happy Meal&quot;&n; * (HME) controller.  See sunhme.h&n; */
multiline_comment|/* register offsets */
multiline_comment|/* global status and control */
DECL|macro|XIFC
mdefine_line|#define&t;XIFC&t;&t;0x000   /* low-level interface control */
DECL|macro|TxOutputEnable
macro_line|#&t;define&t;TxOutputEnable&t;0x0001 /* output driver enable */
DECL|macro|XIFLoopback
macro_line|#&t;define&t;XIFLoopback&t;0x0002 /* Loopback-mode XIF enable */
DECL|macro|MIILoopback
macro_line|#&t;define&t;MIILoopback&t;0x0004 /* Loopback-mode MII enable */
DECL|macro|MIILoopbackBits
macro_line|#&t;define&t;MIILoopbackBits&t;0x0006
DECL|macro|MIIBuffDisable
macro_line|#&t;define&t;MIIBuffDisable&t;0x0008 /* MII receive buffer disable */
DECL|macro|SQETestEnable
macro_line|#&t;define&t;SQETestEnable&t;0x0010 /* SQE test enable */
DECL|macro|SQETimeWindow
macro_line|#&t;define&t;SQETimeWindow&t;0x03e0 /* SQE time window */
DECL|macro|XIFLanceMode
macro_line|#&t;define&t;XIFLanceMode&t;0x0010 /* Lance mode enable */
DECL|macro|XIFLanceIPG0
macro_line|#&t;define&t;XIFLanceIPG0&t;0x03e0 /* Lance mode IPG0 */
DECL|macro|TXFIFOCSR
mdefine_line|#define&t;TXFIFOCSR&t;0x100   /* transmit FIFO control */
DECL|macro|TxFIFOEnable
macro_line|#&t;define&t;TxFIFOEnable&t;0x0001
DECL|macro|TXTH
mdefine_line|#define&t;TXTH&t;&t;0x110   /* transmit threshold */
DECL|macro|TxThreshold
macro_line|#&t;define&t;TxThreshold&t;0x0004
DECL|macro|RXFIFOCSR
mdefine_line|#define RXFIFOCSR&t;0x120   /* receive FIFO control */
DECL|macro|RxFIFOEnable
macro_line|#&t;define&t;RxFIFOEnable&t;0x0001
DECL|macro|MEMADD
mdefine_line|#define MEMADD&t;&t;0x130   /* memory address, unknown function */
DECL|macro|MEMDATAHI
mdefine_line|#define MEMDATAHI&t;0x140   /* memory data high, presently unused in driver */
DECL|macro|MEMDATALO
mdefine_line|#define MEMDATALO&t;0x150   /* memory data low, presently unused in driver */
DECL|macro|XCVRIF
mdefine_line|#define XCVRIF&t;&t;0x160   /* transceiver interface control */
DECL|macro|COLActiveLow
macro_line|#&t;define&t;COLActiveLow&t;0x0002
DECL|macro|SerialMode
macro_line|#&t;define&t;SerialMode&t;0x0004
DECL|macro|ClkBit
macro_line|#&t;define&t;ClkBit&t;&t;0x0008
DECL|macro|LinkStatus
macro_line|#&t;define&t;LinkStatus&t;0x0100
DECL|macro|CHIPID
mdefine_line|#define CHIPID          0x170   /* chip ID */
DECL|macro|MIFCSR
mdefine_line|#define&t;MIFCSR&t;&t;0x180   /* ??? */
DECL|macro|SROMCSR
mdefine_line|#define&t;SROMCSR&t;&t;0x190   /* SROM control */
DECL|macro|ChipSelect
macro_line|#&t;define&t;ChipSelect&t;0x0001
DECL|macro|Clk
macro_line|#&t;define&t;Clk&t;&t;0x0002
DECL|macro|TXPNTR
mdefine_line|#define TXPNTR&t;&t;0x1a0   /* transmit pointer */
DECL|macro|RXPNTR
mdefine_line|#define&t;RXPNTR&t;&t;0x1b0   /* receive pointer */
DECL|macro|STATUS
mdefine_line|#define&t;STATUS&t;&t;0x200   /* status--reading this clears it */
DECL|macro|INTDISABLE
mdefine_line|#define&t;INTDISABLE&t;0x210   /* interrupt enable/disable control */
multiline_comment|/* bits below are the same in both STATUS and INTDISABLE registers */
DECL|macro|FrameReceived
macro_line|#&t;define&t;FrameReceived&t;0x00000001 /* Received a frame */
DECL|macro|RxFrameCntExp
macro_line|#&t;define&t;RxFrameCntExp&t;0x00000002 /* Receive frame counter expired */
DECL|macro|RxAlignCntExp
macro_line|#&t;define&t;RxAlignCntExp&t;0x00000004 /* Align-error counter expired */
DECL|macro|RxCRCCntExp
macro_line|#&t;define&t;RxCRCCntExp&t;0x00000008 /* CRC-error counter expired */
DECL|macro|RxLenCntExp
macro_line|#&t;define&t;RxLenCntExp&t;0x00000010 /* Length-error counter expired */
DECL|macro|RxOverFlow
macro_line|#&t;define&t;RxOverFlow&t;0x00000020 /* Receive FIFO overflow */
DECL|macro|RxCodeViolation
macro_line|#&t;define&t;RxCodeViolation&t;0x00000040 /* Code-violation counter expired */
DECL|macro|SQETestError
macro_line|#&t;define&t;SQETestError&t;0x00000080 /* Test error in XIF for SQE */
DECL|macro|FrameSent
macro_line|#&t;define&t;FrameSent&t;0x00000100 /* Transmitted a frame */
DECL|macro|TxUnderrun
macro_line|#&t;define&t;TxUnderrun&t;0x00000200 /* Transmit FIFO underrun */
DECL|macro|TxMaxSizeError
macro_line|#&t;define&t;TxMaxSizeError&t;0x00000400 /* Max-packet size error */
DECL|macro|TxNormalCollExp
macro_line|#&t;define&t;TxNormalCollExp&t;0x00000800 /* Normal-collision counter expired */
DECL|macro|TxExcessCollExp
macro_line|#&t;define&t;TxExcessCollExp&t;0x00001000 /* Excess-collision counter expired */
DECL|macro|TxLateCollExp
macro_line|#&t;define&t;TxLateCollExp&t;0x00002000 /* Late-collision counter expired */
DECL|macro|TxNetworkCollExp
macro_line|#&t;define&t;TxNetworkCollExp 0x00004000 /* First-collision counter expired */
DECL|macro|TxDeferTimerExp
macro_line|#&t;define&t;TxDeferTimerExp&t;0x00008000 /* Defer-timer expired */
DECL|macro|RxFIFOToHost
macro_line|#&t;define&t;RxFIFOToHost&t;0x00010000 /* Data moved from FIFO to host */
DECL|macro|RxNoDescriptors
macro_line|#&t;define&t;RxNoDescriptors&t;0x00020000 /* No more receive descriptors */
DECL|macro|RxDMAError
macro_line|#&t;define&t;RxDMAError&t;0x00040000 /* Error during receive DMA */
DECL|macro|RxDMALateErr
macro_line|#&t;define&t;RxDMALateErr&t;0x00080000 /* Receive DMA, data late */
DECL|macro|RxParityErr
macro_line|#&t;define&t;RxParityErr&t;0x00100000 /* Parity error during receive DMA */
DECL|macro|RxTagError
macro_line|#&t;define&t;RxTagError&t;0x00200000 /* Tag error during receive DMA */
DECL|macro|TxEOPError
macro_line|#&t;define&t;TxEOPError&t;0x00400000 /* Tx descriptor did not have EOP set */
DECL|macro|MIFIntrEvent
macro_line|#&t;define&t;MIFIntrEvent&t;0x00800000 /* MIF is signaling an interrupt */
DECL|macro|TxHostToFIFO
macro_line|#&t;define&t;TxHostToFIFO&t;0x01000000 /* Data moved from host to FIFO  */
DECL|macro|TxFIFOAllSent
macro_line|#&t;define&t;TxFIFOAllSent&t;0x02000000 /* Transmitted all packets in FIFO */
DECL|macro|TxDMAError
macro_line|#&t;define&t;TxDMAError&t;0x04000000 /* Error during transmit DMA */
DECL|macro|TxDMALateError
macro_line|#&t;define&t;TxDMALateError&t;0x08000000 /* Late error during transmit DMA */
DECL|macro|TxParityError
macro_line|#&t;define&t;TxParityError&t;0x10000000 /* Parity error during transmit DMA */
DECL|macro|TxTagError
macro_line|#&t;define&t;TxTagError&t;0x20000000 /* Tag error during transmit DMA */
DECL|macro|PIOError
macro_line|#&t;define&t;PIOError&t;0x40000000 /* PIO access got an error */
DECL|macro|PIOParityError
macro_line|#&t;define&t;PIOParityError&t;0x80000000 /* PIO access got a parity error  */
DECL|macro|DisableAll
macro_line|#&t;define&t;DisableAll&t;0xffffffff
DECL|macro|EnableAll
macro_line|#&t;define&t;EnableAll&t;0x00000000
multiline_comment|/* #&t;define&t;NormalIntEvents&t;~(FrameReceived | FrameSent | TxUnderrun) */
DECL|macro|EnableNormal
macro_line|#&t;define&t;EnableNormal&t;~(FrameReceived | FrameSent)
DECL|macro|EnableErrors
macro_line|#&t;define&t;EnableErrors&t;(FrameReceived | FrameSent)
DECL|macro|RxErrorMask
macro_line|#&t;define&t;RxErrorMask&t;(RxFrameCntExp | RxAlignCntExp | RxCRCCntExp | &bslash;&n;&t;&t;&t;&t; RxLenCntExp | RxOverFlow | RxCodeViolation)
DECL|macro|TxErrorMask
macro_line|#&t;define&t;TxErrorMask&t;(TxUnderrun | TxMaxSizeError | TxExcessCollExp | &bslash;&n;&t;&t;&t;&t; TxLateCollExp | TxNetworkCollExp | TxDeferTimerExp)
multiline_comment|/* transmit control */
DECL|macro|TXRST
mdefine_line|#define&t;TXRST&t;&t;0x420   /* transmit reset */
DECL|macro|TxResetBit
macro_line|#&t;define&t;TxResetBit&t;0x0001
DECL|macro|TXCFG
mdefine_line|#define&t;TXCFG&t;&t;0x430   /* transmit configuration control*/
DECL|macro|TxMACEnable
macro_line|#&t;define&t;TxMACEnable&t;0x0001 /* output driver enable */
DECL|macro|TxSlowMode
macro_line|#&t;define&t;TxSlowMode&t;0x0020 /* enable slow mode */
DECL|macro|TxIgnoreColl
macro_line|#&t;define&t;TxIgnoreColl&t;0x0040 /* ignore transmit collisions */
DECL|macro|TxNoFCS
macro_line|#&t;define&t;TxNoFCS&t;&t;0x0080 /* do not emit FCS */
DECL|macro|TxNoBackoff
macro_line|#&t;define&t;TxNoBackoff&t;0x0100 /* no backoff in case of collisions */
DECL|macro|TxFullDuplex
macro_line|#&t;define&t;TxFullDuplex&t;0x0200 /* enable full-duplex */
DECL|macro|TxNeverGiveUp
macro_line|#&t;define&t;TxNeverGiveUp&t;0x0400 /* don&squot;t give up on transmits */
DECL|macro|IPG1
mdefine_line|#define IPG1&t;&t;0x440   /* Inter-packet gap 1 */
DECL|macro|IPG2
mdefine_line|#define IPG2&t;&t;0x450   /* Inter-packet gap 2 */
DECL|macro|ALIMIT
mdefine_line|#define ALIMIT&t;&t;0x460   /* Transmit attempt limit */
DECL|macro|SLOT
mdefine_line|#define SLOT&t;&t;0x470   /* Transmit slot time */
DECL|macro|PALEN
mdefine_line|#define PALEN&t;&t;0x480   /* Size of transmit preamble */
DECL|macro|PAPAT
mdefine_line|#define PAPAT&t;&t;0x490   /* Pattern for transmit preamble */
DECL|macro|TXSFD
mdefine_line|#define TXSFD&t;&t;0x4a0   /* Transmit frame delimiter */
DECL|macro|JAM
mdefine_line|#define JAM&t;&t;0x4b0   /* Jam size */
DECL|macro|TXMAX
mdefine_line|#define TXMAX&t;&t;0x4c0   /* Transmit max pkt size */
DECL|macro|TXMIN
mdefine_line|#define TXMIN&t;&t;0x4d0   /* Transmit min pkt size */
DECL|macro|PAREG
mdefine_line|#define PAREG&t;&t;0x4e0   /* Count of transmit peak attempts */
DECL|macro|DCNT
mdefine_line|#define DCNT&t;&t;0x4f0   /* Transmit defer timer */
DECL|macro|NCCNT
mdefine_line|#define NCCNT&t;&t;0x500   /* Transmit normal-collision counter */
DECL|macro|NTCNT
mdefine_line|#define NTCNT&t;&t;0x510   /* Transmit first-collision counter */
DECL|macro|EXCNT
mdefine_line|#define EXCNT&t;&t;0x520   /* Transmit excess-collision counter */
DECL|macro|LTCNT
mdefine_line|#define LTCNT&t;&t;0x530   /* Transmit late-collision counter */
DECL|macro|RSEED
mdefine_line|#define RSEED&t;&t;0x540   /* Transmit random number seed */
DECL|macro|TXSM
mdefine_line|#define TXSM&t;&t;0x550   /* Transmit state machine */
multiline_comment|/* receive control */
DECL|macro|RXRST
mdefine_line|#define RXRST&t;&t;0x620   /* receive reset */
DECL|macro|RxResetValue
macro_line|#&t;define&t;RxResetValue&t;0x0000
DECL|macro|RXCFG
mdefine_line|#define RXCFG&t;&t;0x630   /* receive configuration control */
DECL|macro|RxMACEnable
macro_line|#&t;define&t;RxMACEnable&t;0x0001 /* receiver overall enable */
DECL|macro|RxCFGReserved
macro_line|#&t;define&t;RxCFGReserved&t;0x0004
DECL|macro|RxPadStripEnab
macro_line|#&t;define&t;RxPadStripEnab&t;0x0020 /* enable pad byte stripping */
DECL|macro|RxPromiscEnable
macro_line|#&t;define&t;RxPromiscEnable&t;0x0040 /* turn on promiscuous mode */
DECL|macro|RxNoErrCheck
macro_line|#&t;define&t;RxNoErrCheck&t;0x0080 /* disable receive error checking */
DECL|macro|RxCRCNoStrip
macro_line|#&t;define&t;RxCRCNoStrip&t;0x0100 /* disable auto-CRC-stripping */
DECL|macro|RxRejectOwnPackets
macro_line|#&t;define&t;RxRejectOwnPackets 0x0200 /* don&squot;t receive our own packets */
DECL|macro|RxGrpPromisck
macro_line|#&t;define&t;RxGrpPromisck&t;0x0400 /* enable group promiscuous mode */
DECL|macro|RxHashFilterEnable
macro_line|#&t;define&t;RxHashFilterEnable 0x0800 /* enable hash filter */
DECL|macro|RxAddrFilterEnable
macro_line|#&t;define&t;RxAddrFilterEnable 0x1000 /* enable address filter */
DECL|macro|RXMAX
mdefine_line|#define RXMAX&t;&t;0x640   /* Max receive packet size */
DECL|macro|RXMIN
mdefine_line|#define RXMIN&t;&t;0x650   /* Min receive packet size */
DECL|macro|MADD2
mdefine_line|#define MADD2&t;&t;0x660   /* our enet address, high part */
DECL|macro|MADD1
mdefine_line|#define MADD1&t;&t;0x670   /* our enet address, middle part */
DECL|macro|MADD0
mdefine_line|#define MADD0&t;&t;0x680   /* our enet address, low part */
DECL|macro|FRCNT
mdefine_line|#define FRCNT&t;&t;0x690   /* receive frame counter */
DECL|macro|LECNT
mdefine_line|#define LECNT&t;&t;0x6a0   /* Receive excess length error counter */
DECL|macro|AECNT
mdefine_line|#define AECNT&t;&t;0x6b0   /* Receive misaligned error counter */
DECL|macro|FECNT
mdefine_line|#define FECNT&t;&t;0x6c0   /* Receive CRC error counter */
DECL|macro|RXSM
mdefine_line|#define RXSM&t;&t;0x6d0   /* Receive state machine */
DECL|macro|RXCV
mdefine_line|#define RXCV&t;&t;0x6e0   /* Receive code violation */
DECL|macro|BHASH3
mdefine_line|#define BHASH3&t;&t;0x700   /* multicast hash register */
DECL|macro|BHASH2
mdefine_line|#define BHASH2&t;&t;0x710   /* multicast hash register */
DECL|macro|BHASH1
mdefine_line|#define BHASH1&t;&t;0x720   /* multicast hash register */
DECL|macro|BHASH0
mdefine_line|#define BHASH0&t;&t;0x730   /* multicast hash register */
DECL|macro|AFR2
mdefine_line|#define AFR2&t;&t;0x740   /* address filtering setup? */
DECL|macro|AFR1
mdefine_line|#define AFR1&t;&t;0x750   /* address filtering setup? */
DECL|macro|AFR0
mdefine_line|#define AFR0&t;&t;0x760   /* address filtering setup? */
DECL|macro|AFCR
mdefine_line|#define AFCR&t;&t;0x770   /* address filter compare register? */
DECL|macro|EnableAllCompares
macro_line|#&t;define&t;EnableAllCompares 0x0fff
multiline_comment|/* bits in XIFC */
eof
