multiline_comment|/*&n; *  linux/include/asm-arm/arch-pxa/pxa-regs.h&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Jun 15, 2001&n; *  Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __PXA_REGS_H
DECL|macro|__PXA_REGS_H
mdefine_line|#define __PXA_REGS_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * PXA Chip selects&n; */
DECL|macro|PXA_CS0_PHYS
mdefine_line|#define PXA_CS0_PHYS&t;0x00000000
DECL|macro|PXA_CS1_PHYS
mdefine_line|#define PXA_CS1_PHYS&t;0x04000000
DECL|macro|PXA_CS2_PHYS
mdefine_line|#define PXA_CS2_PHYS&t;0x08000000
DECL|macro|PXA_CS3_PHYS
mdefine_line|#define PXA_CS3_PHYS&t;0x0C000000
DECL|macro|PXA_CS4_PHYS
mdefine_line|#define PXA_CS4_PHYS&t;0x10000000
DECL|macro|PXA_CS5_PHYS
mdefine_line|#define PXA_CS5_PHYS&t;0x14000000
multiline_comment|/*&n; * Personal Computer Memory Card International Association (PCMCIA) sockets&n; */
DECL|macro|PCMCIAPrtSp
mdefine_line|#define PCMCIAPrtSp&t;0x04000000&t;/* PCMCIA Partition Space [byte]   */
DECL|macro|PCMCIASp
mdefine_line|#define PCMCIASp&t;(4*PCMCIAPrtSp)&t;/* PCMCIA Space [byte]             */
DECL|macro|PCMCIAIOSp
mdefine_line|#define PCMCIAIOSp&t;PCMCIAPrtSp&t;/* PCMCIA I/O Space [byte]         */
DECL|macro|PCMCIAAttrSp
mdefine_line|#define PCMCIAAttrSp&t;PCMCIAPrtSp&t;/* PCMCIA Attribute Space [byte]   */
DECL|macro|PCMCIAMemSp
mdefine_line|#define PCMCIAMemSp&t;PCMCIAPrtSp&t;/* PCMCIA Memory Space [byte]      */
DECL|macro|PCMCIA0Sp
mdefine_line|#define PCMCIA0Sp&t;PCMCIASp&t;/* PCMCIA 0 Space [byte]           */
DECL|macro|PCMCIA0IOSp
mdefine_line|#define PCMCIA0IOSp&t;PCMCIAIOSp&t;/* PCMCIA 0 I/O Space [byte]       */
DECL|macro|PCMCIA0AttrSp
mdefine_line|#define PCMCIA0AttrSp&t;PCMCIAAttrSp&t;/* PCMCIA 0 Attribute Space [byte] */
DECL|macro|PCMCIA0MemSp
mdefine_line|#define PCMCIA0MemSp&t;PCMCIAMemSp&t;/* PCMCIA 0 Memory Space [byte]    */
DECL|macro|PCMCIA1Sp
mdefine_line|#define PCMCIA1Sp&t;PCMCIASp&t;/* PCMCIA 1 Space [byte]           */
DECL|macro|PCMCIA1IOSp
mdefine_line|#define PCMCIA1IOSp&t;PCMCIAIOSp&t;/* PCMCIA 1 I/O Space [byte]       */
DECL|macro|PCMCIA1AttrSp
mdefine_line|#define PCMCIA1AttrSp&t;PCMCIAAttrSp&t;/* PCMCIA 1 Attribute Space [byte] */
DECL|macro|PCMCIA1MemSp
mdefine_line|#define PCMCIA1MemSp&t;PCMCIAMemSp&t;/* PCMCIA 1 Memory Space [byte]    */
DECL|macro|_PCMCIA
mdefine_line|#define _PCMCIA(Nb)&t;        &t;/* PCMCIA [0..1]                   */ &bslash;&n;                &t;(0x20000000 + (Nb)*PCMCIASp)
DECL|macro|_PCMCIAIO
mdefine_line|#define _PCMCIAIO(Nb)&t;_PCMCIA (Nb)&t;/* PCMCIA I/O [0..1]               */
DECL|macro|_PCMCIAAttr
mdefine_line|#define _PCMCIAAttr(Nb)&t;        &t;/* PCMCIA Attribute [0..1]         */ &bslash;&n;                &t;(_PCMCIA (Nb) + 2*PCMCIAPrtSp)
DECL|macro|_PCMCIAMem
mdefine_line|#define _PCMCIAMem(Nb)&t;        &t;/* PCMCIA Memory [0..1]            */ &bslash;&n;                &t;(_PCMCIA (Nb) + 3*PCMCIAPrtSp)
DECL|macro|_PCMCIA0
mdefine_line|#define _PCMCIA0&t;_PCMCIA (0)&t;/* PCMCIA 0                        */
DECL|macro|_PCMCIA0IO
mdefine_line|#define _PCMCIA0IO&t;_PCMCIAIO (0)&t;/* PCMCIA 0 I/O                    */
DECL|macro|_PCMCIA0Attr
mdefine_line|#define _PCMCIA0Attr&t;_PCMCIAAttr (0)&t;/* PCMCIA 0 Attribute              */
DECL|macro|_PCMCIA0Mem
mdefine_line|#define _PCMCIA0Mem&t;_PCMCIAMem (0)&t;/* PCMCIA 0 Memory                 */
DECL|macro|_PCMCIA1
mdefine_line|#define _PCMCIA1&t;_PCMCIA (1)&t;/* PCMCIA 1                        */
DECL|macro|_PCMCIA1IO
mdefine_line|#define _PCMCIA1IO&t;_PCMCIAIO (1)&t;/* PCMCIA 1 I/O                    */
DECL|macro|_PCMCIA1Attr
mdefine_line|#define _PCMCIA1Attr&t;_PCMCIAAttr (1)&t;/* PCMCIA 1 Attribute              */
DECL|macro|_PCMCIA1Mem
mdefine_line|#define _PCMCIA1Mem&t;_PCMCIAMem (1)&t;/* PCMCIA 1 Memory                 */
multiline_comment|/*&n; * DMA Controller&n; */
DECL|macro|DCSR0
mdefine_line|#define DCSR0&t;&t;__REG(0x40000000)  /* DMA Control / Status Register for Channel 0 */
DECL|macro|DCSR1
mdefine_line|#define DCSR1&t;&t;__REG(0x40000004)  /* DMA Control / Status Register for Channel 1 */
DECL|macro|DCSR2
mdefine_line|#define DCSR2&t;&t;__REG(0x40000008)  /* DMA Control / Status Register for Channel 2 */
DECL|macro|DCSR3
mdefine_line|#define DCSR3&t;&t;__REG(0x4000000c)  /* DMA Control / Status Register for Channel 3 */
DECL|macro|DCSR4
mdefine_line|#define DCSR4&t;&t;__REG(0x40000010)  /* DMA Control / Status Register for Channel 4 */
DECL|macro|DCSR5
mdefine_line|#define DCSR5&t;&t;__REG(0x40000014)  /* DMA Control / Status Register for Channel 5 */
DECL|macro|DCSR6
mdefine_line|#define DCSR6&t;&t;__REG(0x40000018)  /* DMA Control / Status Register for Channel 6 */
DECL|macro|DCSR7
mdefine_line|#define DCSR7&t;&t;__REG(0x4000001c)  /* DMA Control / Status Register for Channel 7 */
DECL|macro|DCSR8
mdefine_line|#define DCSR8&t;&t;__REG(0x40000020)  /* DMA Control / Status Register for Channel 8 */
DECL|macro|DCSR9
mdefine_line|#define DCSR9&t;&t;__REG(0x40000024)  /* DMA Control / Status Register for Channel 9 */
DECL|macro|DCSR10
mdefine_line|#define DCSR10&t;&t;__REG(0x40000028)  /* DMA Control / Status Register for Channel 10 */
DECL|macro|DCSR11
mdefine_line|#define DCSR11&t;&t;__REG(0x4000002c)  /* DMA Control / Status Register for Channel 11 */
DECL|macro|DCSR12
mdefine_line|#define DCSR12&t;&t;__REG(0x40000030)  /* DMA Control / Status Register for Channel 12 */
DECL|macro|DCSR13
mdefine_line|#define DCSR13&t;&t;__REG(0x40000034)  /* DMA Control / Status Register for Channel 13 */
DECL|macro|DCSR14
mdefine_line|#define DCSR14&t;&t;__REG(0x40000038)  /* DMA Control / Status Register for Channel 14 */
DECL|macro|DCSR15
mdefine_line|#define DCSR15&t;&t;__REG(0x4000003c)  /* DMA Control / Status Register for Channel 15 */
DECL|macro|DCSR
mdefine_line|#define DCSR(x)&t;&t;__REG2(0x40000000, (x) &lt;&lt; 2)
DECL|macro|DCSR_RUN
mdefine_line|#define DCSR_RUN&t;(1 &lt;&lt; 31)&t;/* Run Bit (read / write) */
DECL|macro|DCSR_NODESC
mdefine_line|#define DCSR_NODESC&t;(1 &lt;&lt; 30)&t;/* No-Descriptor Fetch (read / write) */
DECL|macro|DCSR_STOPIRQEN
mdefine_line|#define DCSR_STOPIRQEN&t;(1 &lt;&lt; 29)&t;/* Stop Interrupt Enable (read / write) */
macro_line|#ifdef CONFIG_PXA27x
DECL|macro|DCSR_EORIRQEN
mdefine_line|#define DCSR_EORIRQEN&t;(1 &lt;&lt; 28)       /* End of Receive Interrupt Enable (R/W) */
DECL|macro|DCSR_EORJMPEN
mdefine_line|#define DCSR_EORJMPEN&t;(1 &lt;&lt; 27)       /* Jump to next descriptor on EOR */
DECL|macro|DCSR_EORSTOPEN
mdefine_line|#define DCSR_EORSTOPEN&t;(1 &lt;&lt; 26)       /* STOP on an EOR */
DECL|macro|DCSR_SETCMPST
mdefine_line|#define DCSR_SETCMPST&t;(1 &lt;&lt; 25)       /* Set Descriptor Compare Status */
DECL|macro|DCSR_CLRCMPST
mdefine_line|#define DCSR_CLRCMPST&t;(1 &lt;&lt; 24)       /* Clear Descriptor Compare Status */
DECL|macro|DCSR_CMPST
mdefine_line|#define DCSR_CMPST&t;(1 &lt;&lt; 10)       /* The Descriptor Compare Status */
DECL|macro|DCSR_ENRINTR
mdefine_line|#define DCSR_ENRINTR&t;(1 &lt;&lt; 9)        /* The end of Receive */
macro_line|#endif
DECL|macro|DCSR_REQPEND
mdefine_line|#define DCSR_REQPEND&t;(1 &lt;&lt; 8)&t;/* Request Pending (read-only) */
DECL|macro|DCSR_STOPSTATE
mdefine_line|#define DCSR_STOPSTATE&t;(1 &lt;&lt; 3)&t;/* Stop State (read-only) */
DECL|macro|DCSR_ENDINTR
mdefine_line|#define DCSR_ENDINTR&t;(1 &lt;&lt; 2)&t;/* End Interrupt (read / write) */
DECL|macro|DCSR_STARTINTR
mdefine_line|#define DCSR_STARTINTR&t;(1 &lt;&lt; 1)&t;/* Start Interrupt (read / write) */
DECL|macro|DCSR_BUSERR
mdefine_line|#define DCSR_BUSERR&t;(1 &lt;&lt; 0)&t;/* Bus Error Interrupt (read / write) */
DECL|macro|DINT
mdefine_line|#define DINT&t;&t;__REG(0x400000f0)  /* DMA Interrupt Register */
DECL|macro|DRCMR
mdefine_line|#define DRCMR(n)&t;__REG2(0x40000100, (n)&lt;&lt;2)
DECL|macro|DRCMR0
mdefine_line|#define DRCMR0&t;&t;__REG(0x40000100)  /* Request to Channel Map Register for DREQ 0 */
DECL|macro|DRCMR1
mdefine_line|#define DRCMR1&t;&t;__REG(0x40000104)  /* Request to Channel Map Register for DREQ 1 */
DECL|macro|DRCMR2
mdefine_line|#define DRCMR2&t;&t;__REG(0x40000108)  /* Request to Channel Map Register for I2S receive Request */
DECL|macro|DRCMR3
mdefine_line|#define DRCMR3&t;&t;__REG(0x4000010c)  /* Request to Channel Map Register for I2S transmit Request */
DECL|macro|DRCMR4
mdefine_line|#define DRCMR4&t;&t;__REG(0x40000110)  /* Request to Channel Map Register for BTUART receive Request */
DECL|macro|DRCMR5
mdefine_line|#define DRCMR5&t;&t;__REG(0x40000114)  /* Request to Channel Map Register for BTUART transmit Request. */
DECL|macro|DRCMR6
mdefine_line|#define DRCMR6&t;&t;__REG(0x40000118)  /* Request to Channel Map Register for FFUART receive Request */
DECL|macro|DRCMR7
mdefine_line|#define DRCMR7&t;&t;__REG(0x4000011c)  /* Request to Channel Map Register for FFUART transmit Request */
DECL|macro|DRCMR8
mdefine_line|#define DRCMR8&t;&t;__REG(0x40000120)  /* Request to Channel Map Register for AC97 microphone Request */
DECL|macro|DRCMR9
mdefine_line|#define DRCMR9&t;&t;__REG(0x40000124)  /* Request to Channel Map Register for AC97 modem receive Request */
DECL|macro|DRCMR10
mdefine_line|#define DRCMR10&t;&t;__REG(0x40000128)  /* Request to Channel Map Register for AC97 modem transmit Request */
DECL|macro|DRCMR11
mdefine_line|#define DRCMR11&t;&t;__REG(0x4000012c)  /* Request to Channel Map Register for AC97 audio receive Request */
DECL|macro|DRCMR12
mdefine_line|#define DRCMR12&t;&t;__REG(0x40000130)  /* Request to Channel Map Register for AC97 audio transmit Request */
DECL|macro|DRCMR13
mdefine_line|#define DRCMR13&t;&t;__REG(0x40000134)  /* Request to Channel Map Register for SSP receive Request */
DECL|macro|DRCMR14
mdefine_line|#define DRCMR14&t;&t;__REG(0x40000138)  /* Request to Channel Map Register for SSP transmit Request */
DECL|macro|DRCMR15
mdefine_line|#define DRCMR15&t;&t;__REG(0x4000013c)  /* Reserved */
DECL|macro|DRCMR16
mdefine_line|#define DRCMR16&t;&t;__REG(0x40000140)  /* Reserved */
DECL|macro|DRCMR17
mdefine_line|#define DRCMR17&t;&t;__REG(0x40000144)  /* Request to Channel Map Register for ICP receive Request */
DECL|macro|DRCMR18
mdefine_line|#define DRCMR18&t;&t;__REG(0x40000148)  /* Request to Channel Map Register for ICP transmit Request */
DECL|macro|DRCMR19
mdefine_line|#define DRCMR19&t;&t;__REG(0x4000014c)  /* Request to Channel Map Register for STUART receive Request */
DECL|macro|DRCMR20
mdefine_line|#define DRCMR20&t;&t;__REG(0x40000150)  /* Request to Channel Map Register for STUART transmit Request */
DECL|macro|DRCMR21
mdefine_line|#define DRCMR21&t;&t;__REG(0x40000154)  /* Request to Channel Map Register for MMC receive Request */
DECL|macro|DRCMR22
mdefine_line|#define DRCMR22&t;&t;__REG(0x40000158)  /* Request to Channel Map Register for MMC transmit Request */
DECL|macro|DRCMR23
mdefine_line|#define DRCMR23&t;&t;__REG(0x4000015c)  /* Reserved */
DECL|macro|DRCMR24
mdefine_line|#define DRCMR24&t;&t;__REG(0x40000160)  /* Reserved */
DECL|macro|DRCMR25
mdefine_line|#define DRCMR25&t;&t;__REG(0x40000164)  /* Request to Channel Map Register for USB endpoint 1 Request */
DECL|macro|DRCMR26
mdefine_line|#define DRCMR26&t;&t;__REG(0x40000168)  /* Request to Channel Map Register for USB endpoint 2 Request */
DECL|macro|DRCMR27
mdefine_line|#define DRCMR27&t;&t;__REG(0x4000016C)  /* Request to Channel Map Register for USB endpoint 3 Request */
DECL|macro|DRCMR28
mdefine_line|#define DRCMR28&t;&t;__REG(0x40000170)  /* Request to Channel Map Register for USB endpoint 4 Request */
DECL|macro|DRCMR29
mdefine_line|#define DRCMR29&t;&t;__REG(0x40000174)  /* Reserved */
DECL|macro|DRCMR30
mdefine_line|#define DRCMR30&t;&t;__REG(0x40000178)  /* Request to Channel Map Register for USB endpoint 6 Request */
DECL|macro|DRCMR31
mdefine_line|#define DRCMR31&t;&t;__REG(0x4000017C)  /* Request to Channel Map Register for USB endpoint 7 Request */
DECL|macro|DRCMR32
mdefine_line|#define DRCMR32&t;&t;__REG(0x40000180)  /* Request to Channel Map Register for USB endpoint 8 Request */
DECL|macro|DRCMR33
mdefine_line|#define DRCMR33&t;&t;__REG(0x40000184)  /* Request to Channel Map Register for USB endpoint 9 Request */
DECL|macro|DRCMR34
mdefine_line|#define DRCMR34&t;&t;__REG(0x40000188)  /* Reserved */
DECL|macro|DRCMR35
mdefine_line|#define DRCMR35&t;&t;__REG(0x4000018C)  /* Request to Channel Map Register for USB endpoint 11 Request */
DECL|macro|DRCMR36
mdefine_line|#define DRCMR36&t;&t;__REG(0x40000190)  /* Request to Channel Map Register for USB endpoint 12 Request */
DECL|macro|DRCMR37
mdefine_line|#define DRCMR37&t;&t;__REG(0x40000194)  /* Request to Channel Map Register for USB endpoint 13 Request */
DECL|macro|DRCMR38
mdefine_line|#define DRCMR38&t;&t;__REG(0x40000198)  /* Request to Channel Map Register for USB endpoint 14 Request */
DECL|macro|DRCMR39
mdefine_line|#define DRCMR39&t;&t;__REG(0x4000019C)  /* Reserved */
DECL|macro|DRCMR68
mdefine_line|#define DRCMR68&t;&t;__REG(0x40001110)  /* Request to Channel Map Register for Camera FIFO 0 Request */
DECL|macro|DRCMR69
mdefine_line|#define DRCMR69&t;&t;__REG(0x40001114)  /* Request to Channel Map Register for Camera FIFO 1 Request */
DECL|macro|DRCMR70
mdefine_line|#define DRCMR70&t;&t;__REG(0x40001118)  /* Request to Channel Map Register for Camera FIFO 2 Request */
DECL|macro|DRCMRRXSADR
mdefine_line|#define DRCMRRXSADR&t;DRCMR2
DECL|macro|DRCMRTXSADR
mdefine_line|#define DRCMRTXSADR&t;DRCMR3
DECL|macro|DRCMRRXBTRBR
mdefine_line|#define DRCMRRXBTRBR&t;DRCMR4
DECL|macro|DRCMRTXBTTHR
mdefine_line|#define DRCMRTXBTTHR&t;DRCMR5
DECL|macro|DRCMRRXFFRBR
mdefine_line|#define DRCMRRXFFRBR&t;DRCMR6
DECL|macro|DRCMRTXFFTHR
mdefine_line|#define DRCMRTXFFTHR&t;DRCMR7
DECL|macro|DRCMRRXMCDR
mdefine_line|#define DRCMRRXMCDR&t;DRCMR8
DECL|macro|DRCMRRXMODR
mdefine_line|#define DRCMRRXMODR&t;DRCMR9
DECL|macro|DRCMRTXMODR
mdefine_line|#define DRCMRTXMODR&t;DRCMR10
DECL|macro|DRCMRRXPCDR
mdefine_line|#define DRCMRRXPCDR&t;DRCMR11
DECL|macro|DRCMRTXPCDR
mdefine_line|#define DRCMRTXPCDR&t;DRCMR12
DECL|macro|DRCMRRXSSDR
mdefine_line|#define DRCMRRXSSDR&t;DRCMR13
DECL|macro|DRCMRTXSSDR
mdefine_line|#define DRCMRTXSSDR&t;DRCMR14
DECL|macro|DRCMRRXSS2DR
mdefine_line|#define DRCMRRXSS2DR   DRCMR15
DECL|macro|DRCMRTXSS2DR
mdefine_line|#define DRCMRTXSS2DR   DRCMR16
DECL|macro|DRCMRRXICDR
mdefine_line|#define DRCMRRXICDR&t;DRCMR17
DECL|macro|DRCMRTXICDR
mdefine_line|#define DRCMRTXICDR&t;DRCMR18
DECL|macro|DRCMRRXSTRBR
mdefine_line|#define DRCMRRXSTRBR&t;DRCMR19
DECL|macro|DRCMRTXSTTHR
mdefine_line|#define DRCMRTXSTTHR&t;DRCMR20
DECL|macro|DRCMRRXMMC
mdefine_line|#define DRCMRRXMMC&t;DRCMR21
DECL|macro|DRCMRTXMMC
mdefine_line|#define DRCMRTXMMC&t;DRCMR22
DECL|macro|DRCMRRXSS3DR
mdefine_line|#define DRCMRRXSS3DR   DRCMR66
DECL|macro|DRCMRTXSS3DR
mdefine_line|#define DRCMRTXSS3DR   DRCMR67
DECL|macro|DRCMRUDC
mdefine_line|#define DRCMRUDC(x)&t;DRCMR((x) + 24)
DECL|macro|DRCMR_MAPVLD
mdefine_line|#define DRCMR_MAPVLD&t;(1 &lt;&lt; 7)&t;/* Map Valid (read / write) */
DECL|macro|DRCMR_CHLNUM
mdefine_line|#define DRCMR_CHLNUM&t;0x1f&t;&t;/* mask for Channel Number (read / write) */
DECL|macro|DDADR0
mdefine_line|#define DDADR0&t;&t;__REG(0x40000200)  /* DMA Descriptor Address Register Channel 0 */
DECL|macro|DSADR0
mdefine_line|#define DSADR0&t;&t;__REG(0x40000204)  /* DMA Source Address Register Channel 0 */
DECL|macro|DTADR0
mdefine_line|#define DTADR0&t;&t;__REG(0x40000208)  /* DMA Target Address Register Channel 0 */
DECL|macro|DCMD0
mdefine_line|#define DCMD0&t;&t;__REG(0x4000020c)  /* DMA Command Address Register Channel 0 */
DECL|macro|DDADR1
mdefine_line|#define DDADR1&t;&t;__REG(0x40000210)  /* DMA Descriptor Address Register Channel 1 */
DECL|macro|DSADR1
mdefine_line|#define DSADR1&t;&t;__REG(0x40000214)  /* DMA Source Address Register Channel 1 */
DECL|macro|DTADR1
mdefine_line|#define DTADR1&t;&t;__REG(0x40000218)  /* DMA Target Address Register Channel 1 */
DECL|macro|DCMD1
mdefine_line|#define DCMD1&t;&t;__REG(0x4000021c)  /* DMA Command Address Register Channel 1 */
DECL|macro|DDADR2
mdefine_line|#define DDADR2&t;&t;__REG(0x40000220)  /* DMA Descriptor Address Register Channel 2 */
DECL|macro|DSADR2
mdefine_line|#define DSADR2&t;&t;__REG(0x40000224)  /* DMA Source Address Register Channel 2 */
DECL|macro|DTADR2
mdefine_line|#define DTADR2&t;&t;__REG(0x40000228)  /* DMA Target Address Register Channel 2 */
DECL|macro|DCMD2
mdefine_line|#define DCMD2&t;&t;__REG(0x4000022c)  /* DMA Command Address Register Channel 2 */
DECL|macro|DDADR3
mdefine_line|#define DDADR3&t;&t;__REG(0x40000230)  /* DMA Descriptor Address Register Channel 3 */
DECL|macro|DSADR3
mdefine_line|#define DSADR3&t;&t;__REG(0x40000234)  /* DMA Source Address Register Channel 3 */
DECL|macro|DTADR3
mdefine_line|#define DTADR3&t;&t;__REG(0x40000238)  /* DMA Target Address Register Channel 3 */
DECL|macro|DCMD3
mdefine_line|#define DCMD3&t;&t;__REG(0x4000023c)  /* DMA Command Address Register Channel 3 */
DECL|macro|DDADR4
mdefine_line|#define DDADR4&t;&t;__REG(0x40000240)  /* DMA Descriptor Address Register Channel 4 */
DECL|macro|DSADR4
mdefine_line|#define DSADR4&t;&t;__REG(0x40000244)  /* DMA Source Address Register Channel 4 */
DECL|macro|DTADR4
mdefine_line|#define DTADR4&t;&t;__REG(0x40000248)  /* DMA Target Address Register Channel 4 */
DECL|macro|DCMD4
mdefine_line|#define DCMD4&t;&t;__REG(0x4000024c)  /* DMA Command Address Register Channel 4 */
DECL|macro|DDADR5
mdefine_line|#define DDADR5&t;&t;__REG(0x40000250)  /* DMA Descriptor Address Register Channel 5 */
DECL|macro|DSADR5
mdefine_line|#define DSADR5&t;&t;__REG(0x40000254)  /* DMA Source Address Register Channel 5 */
DECL|macro|DTADR5
mdefine_line|#define DTADR5&t;&t;__REG(0x40000258)  /* DMA Target Address Register Channel 5 */
DECL|macro|DCMD5
mdefine_line|#define DCMD5&t;&t;__REG(0x4000025c)  /* DMA Command Address Register Channel 5 */
DECL|macro|DDADR6
mdefine_line|#define DDADR6&t;&t;__REG(0x40000260)  /* DMA Descriptor Address Register Channel 6 */
DECL|macro|DSADR6
mdefine_line|#define DSADR6&t;&t;__REG(0x40000264)  /* DMA Source Address Register Channel 6 */
DECL|macro|DTADR6
mdefine_line|#define DTADR6&t;&t;__REG(0x40000268)  /* DMA Target Address Register Channel 6 */
DECL|macro|DCMD6
mdefine_line|#define DCMD6&t;&t;__REG(0x4000026c)  /* DMA Command Address Register Channel 6 */
DECL|macro|DDADR7
mdefine_line|#define DDADR7&t;&t;__REG(0x40000270)  /* DMA Descriptor Address Register Channel 7 */
DECL|macro|DSADR7
mdefine_line|#define DSADR7&t;&t;__REG(0x40000274)  /* DMA Source Address Register Channel 7 */
DECL|macro|DTADR7
mdefine_line|#define DTADR7&t;&t;__REG(0x40000278)  /* DMA Target Address Register Channel 7 */
DECL|macro|DCMD7
mdefine_line|#define DCMD7&t;&t;__REG(0x4000027c)  /* DMA Command Address Register Channel 7 */
DECL|macro|DDADR8
mdefine_line|#define DDADR8&t;&t;__REG(0x40000280)  /* DMA Descriptor Address Register Channel 8 */
DECL|macro|DSADR8
mdefine_line|#define DSADR8&t;&t;__REG(0x40000284)  /* DMA Source Address Register Channel 8 */
DECL|macro|DTADR8
mdefine_line|#define DTADR8&t;&t;__REG(0x40000288)  /* DMA Target Address Register Channel 8 */
DECL|macro|DCMD8
mdefine_line|#define DCMD8&t;&t;__REG(0x4000028c)  /* DMA Command Address Register Channel 8 */
DECL|macro|DDADR9
mdefine_line|#define DDADR9&t;&t;__REG(0x40000290)  /* DMA Descriptor Address Register Channel 9 */
DECL|macro|DSADR9
mdefine_line|#define DSADR9&t;&t;__REG(0x40000294)  /* DMA Source Address Register Channel 9 */
DECL|macro|DTADR9
mdefine_line|#define DTADR9&t;&t;__REG(0x40000298)  /* DMA Target Address Register Channel 9 */
DECL|macro|DCMD9
mdefine_line|#define DCMD9&t;&t;__REG(0x4000029c)  /* DMA Command Address Register Channel 9 */
DECL|macro|DDADR10
mdefine_line|#define DDADR10&t;&t;__REG(0x400002a0)  /* DMA Descriptor Address Register Channel 10 */
DECL|macro|DSADR10
mdefine_line|#define DSADR10&t;&t;__REG(0x400002a4)  /* DMA Source Address Register Channel 10 */
DECL|macro|DTADR10
mdefine_line|#define DTADR10&t;&t;__REG(0x400002a8)  /* DMA Target Address Register Channel 10 */
DECL|macro|DCMD10
mdefine_line|#define DCMD10&t;&t;__REG(0x400002ac)  /* DMA Command Address Register Channel 10 */
DECL|macro|DDADR11
mdefine_line|#define DDADR11&t;&t;__REG(0x400002b0)  /* DMA Descriptor Address Register Channel 11 */
DECL|macro|DSADR11
mdefine_line|#define DSADR11&t;&t;__REG(0x400002b4)  /* DMA Source Address Register Channel 11 */
DECL|macro|DTADR11
mdefine_line|#define DTADR11&t;&t;__REG(0x400002b8)  /* DMA Target Address Register Channel 11 */
DECL|macro|DCMD11
mdefine_line|#define DCMD11&t;&t;__REG(0x400002bc)  /* DMA Command Address Register Channel 11 */
DECL|macro|DDADR12
mdefine_line|#define DDADR12&t;&t;__REG(0x400002c0)  /* DMA Descriptor Address Register Channel 12 */
DECL|macro|DSADR12
mdefine_line|#define DSADR12&t;&t;__REG(0x400002c4)  /* DMA Source Address Register Channel 12 */
DECL|macro|DTADR12
mdefine_line|#define DTADR12&t;&t;__REG(0x400002c8)  /* DMA Target Address Register Channel 12 */
DECL|macro|DCMD12
mdefine_line|#define DCMD12&t;&t;__REG(0x400002cc)  /* DMA Command Address Register Channel 12 */
DECL|macro|DDADR13
mdefine_line|#define DDADR13&t;&t;__REG(0x400002d0)  /* DMA Descriptor Address Register Channel 13 */
DECL|macro|DSADR13
mdefine_line|#define DSADR13&t;&t;__REG(0x400002d4)  /* DMA Source Address Register Channel 13 */
DECL|macro|DTADR13
mdefine_line|#define DTADR13&t;&t;__REG(0x400002d8)  /* DMA Target Address Register Channel 13 */
DECL|macro|DCMD13
mdefine_line|#define DCMD13&t;&t;__REG(0x400002dc)  /* DMA Command Address Register Channel 13 */
DECL|macro|DDADR14
mdefine_line|#define DDADR14&t;&t;__REG(0x400002e0)  /* DMA Descriptor Address Register Channel 14 */
DECL|macro|DSADR14
mdefine_line|#define DSADR14&t;&t;__REG(0x400002e4)  /* DMA Source Address Register Channel 14 */
DECL|macro|DTADR14
mdefine_line|#define DTADR14&t;&t;__REG(0x400002e8)  /* DMA Target Address Register Channel 14 */
DECL|macro|DCMD14
mdefine_line|#define DCMD14&t;&t;__REG(0x400002ec)  /* DMA Command Address Register Channel 14 */
DECL|macro|DDADR15
mdefine_line|#define DDADR15&t;&t;__REG(0x400002f0)  /* DMA Descriptor Address Register Channel 15 */
DECL|macro|DSADR15
mdefine_line|#define DSADR15&t;&t;__REG(0x400002f4)  /* DMA Source Address Register Channel 15 */
DECL|macro|DTADR15
mdefine_line|#define DTADR15&t;&t;__REG(0x400002f8)  /* DMA Target Address Register Channel 15 */
DECL|macro|DCMD15
mdefine_line|#define DCMD15&t;&t;__REG(0x400002fc)  /* DMA Command Address Register Channel 15 */
DECL|macro|DDADR
mdefine_line|#define DDADR(x)&t;__REG2(0x40000200, (x) &lt;&lt; 4)
DECL|macro|DSADR
mdefine_line|#define DSADR(x)&t;__REG2(0x40000204, (x) &lt;&lt; 4)
DECL|macro|DTADR
mdefine_line|#define DTADR(x)&t;__REG2(0x40000208, (x) &lt;&lt; 4)
DECL|macro|DCMD
mdefine_line|#define DCMD(x)&t;&t;__REG2(0x4000020c, (x) &lt;&lt; 4)
DECL|macro|DDADR_DESCADDR
mdefine_line|#define DDADR_DESCADDR&t;0xfffffff0&t;/* Address of next descriptor (mask) */
DECL|macro|DDADR_STOP
mdefine_line|#define DDADR_STOP&t;(1 &lt;&lt; 0)&t;/* Stop (read / write) */
DECL|macro|DCMD_INCSRCADDR
mdefine_line|#define DCMD_INCSRCADDR&t;(1 &lt;&lt; 31)&t;/* Source Address Increment Setting. */
DECL|macro|DCMD_INCTRGADDR
mdefine_line|#define DCMD_INCTRGADDR&t;(1 &lt;&lt; 30)&t;/* Target Address Increment Setting. */
DECL|macro|DCMD_FLOWSRC
mdefine_line|#define DCMD_FLOWSRC&t;(1 &lt;&lt; 29)&t;/* Flow Control by the source. */
DECL|macro|DCMD_FLOWTRG
mdefine_line|#define DCMD_FLOWTRG&t;(1 &lt;&lt; 28)&t;/* Flow Control by the target. */
DECL|macro|DCMD_STARTIRQEN
mdefine_line|#define DCMD_STARTIRQEN&t;(1 &lt;&lt; 22)&t;/* Start Interrupt Enable */
DECL|macro|DCMD_ENDIRQEN
mdefine_line|#define DCMD_ENDIRQEN&t;(1 &lt;&lt; 21)&t;/* End Interrupt Enable */
DECL|macro|DCMD_ENDIAN
mdefine_line|#define DCMD_ENDIAN&t;(1 &lt;&lt; 18)&t;/* Device Endian-ness. */
DECL|macro|DCMD_BURST8
mdefine_line|#define DCMD_BURST8&t;(1 &lt;&lt; 16)&t;/* 8 byte burst */
DECL|macro|DCMD_BURST16
mdefine_line|#define DCMD_BURST16&t;(2 &lt;&lt; 16)&t;/* 16 byte burst */
DECL|macro|DCMD_BURST32
mdefine_line|#define DCMD_BURST32&t;(3 &lt;&lt; 16)&t;/* 32 byte burst */
DECL|macro|DCMD_WIDTH1
mdefine_line|#define DCMD_WIDTH1&t;(1 &lt;&lt; 14)&t;/* 1 byte width */
DECL|macro|DCMD_WIDTH2
mdefine_line|#define DCMD_WIDTH2&t;(2 &lt;&lt; 14)&t;/* 2 byte width (HalfWord) */
DECL|macro|DCMD_WIDTH4
mdefine_line|#define DCMD_WIDTH4&t;(3 &lt;&lt; 14)&t;/* 4 byte width (Word) */
DECL|macro|DCMD_LENGTH
mdefine_line|#define DCMD_LENGTH&t;0x01fff&t;&t;/* length mask (max = 8K - 1) */
multiline_comment|/* default combinations */
DECL|macro|DCMD_RXPCDR
mdefine_line|#define DCMD_RXPCDR&t;(DCMD_INCTRGADDR|DCMD_FLOWSRC|DCMD_BURST32|DCMD_WIDTH4)
DECL|macro|DCMD_RXMCDR
mdefine_line|#define DCMD_RXMCDR&t;(DCMD_INCTRGADDR|DCMD_FLOWSRC|DCMD_BURST32|DCMD_WIDTH4)
DECL|macro|DCMD_TXPCDR
mdefine_line|#define DCMD_TXPCDR&t;(DCMD_INCSRCADDR|DCMD_FLOWTRG|DCMD_BURST32|DCMD_WIDTH4)
multiline_comment|/*&n; * UARTs&n; */
multiline_comment|/* Full Function UART (FFUART) */
DECL|macro|FFUART
mdefine_line|#define FFUART&t;&t;FFRBR
DECL|macro|FFRBR
mdefine_line|#define FFRBR&t;&t;__REG(0x40100000)  /* Receive Buffer Register (read only) */
DECL|macro|FFTHR
mdefine_line|#define FFTHR&t;&t;__REG(0x40100000)  /* Transmit Holding Register (write only) */
DECL|macro|FFIER
mdefine_line|#define FFIER&t;&t;__REG(0x40100004)  /* Interrupt Enable Register (read/write) */
DECL|macro|FFIIR
mdefine_line|#define FFIIR&t;&t;__REG(0x40100008)  /* Interrupt ID Register (read only) */
DECL|macro|FFFCR
mdefine_line|#define FFFCR&t;&t;__REG(0x40100008)  /* FIFO Control Register (write only) */
DECL|macro|FFLCR
mdefine_line|#define FFLCR&t;&t;__REG(0x4010000C)  /* Line Control Register (read/write) */
DECL|macro|FFMCR
mdefine_line|#define FFMCR&t;&t;__REG(0x40100010)  /* Modem Control Register (read/write) */
DECL|macro|FFLSR
mdefine_line|#define FFLSR&t;&t;__REG(0x40100014)  /* Line Status Register (read only) */
DECL|macro|FFMSR
mdefine_line|#define FFMSR&t;&t;__REG(0x40100018)  /* Modem Status Register (read only) */
DECL|macro|FFSPR
mdefine_line|#define FFSPR&t;&t;__REG(0x4010001C)  /* Scratch Pad Register (read/write) */
DECL|macro|FFISR
mdefine_line|#define FFISR&t;&t;__REG(0x40100020)  /* Infrared Selection Register (read/write) */
DECL|macro|FFDLL
mdefine_line|#define FFDLL&t;&t;__REG(0x40100000)  /* Divisor Latch Low Register (DLAB = 1) (read/write) */
DECL|macro|FFDLH
mdefine_line|#define FFDLH&t;&t;__REG(0x40100004)  /* Divisor Latch High Register (DLAB = 1) (read/write) */
multiline_comment|/* Bluetooth UART (BTUART) */
DECL|macro|BTUART
mdefine_line|#define BTUART&t;&t;BTRBR
DECL|macro|BTRBR
mdefine_line|#define BTRBR&t;&t;__REG(0x40200000)  /* Receive Buffer Register (read only) */
DECL|macro|BTTHR
mdefine_line|#define BTTHR&t;&t;__REG(0x40200000)  /* Transmit Holding Register (write only) */
DECL|macro|BTIER
mdefine_line|#define BTIER&t;&t;__REG(0x40200004)  /* Interrupt Enable Register (read/write) */
DECL|macro|BTIIR
mdefine_line|#define BTIIR&t;&t;__REG(0x40200008)  /* Interrupt ID Register (read only) */
DECL|macro|BTFCR
mdefine_line|#define BTFCR&t;&t;__REG(0x40200008)  /* FIFO Control Register (write only) */
DECL|macro|BTLCR
mdefine_line|#define BTLCR&t;&t;__REG(0x4020000C)  /* Line Control Register (read/write) */
DECL|macro|BTMCR
mdefine_line|#define BTMCR&t;&t;__REG(0x40200010)  /* Modem Control Register (read/write) */
DECL|macro|BTLSR
mdefine_line|#define BTLSR&t;&t;__REG(0x40200014)  /* Line Status Register (read only) */
DECL|macro|BTMSR
mdefine_line|#define BTMSR&t;&t;__REG(0x40200018)  /* Modem Status Register (read only) */
DECL|macro|BTSPR
mdefine_line|#define BTSPR&t;&t;__REG(0x4020001C)  /* Scratch Pad Register (read/write) */
DECL|macro|BTISR
mdefine_line|#define BTISR&t;&t;__REG(0x40200020)  /* Infrared Selection Register (read/write) */
DECL|macro|BTDLL
mdefine_line|#define BTDLL&t;&t;__REG(0x40200000)  /* Divisor Latch Low Register (DLAB = 1) (read/write) */
DECL|macro|BTDLH
mdefine_line|#define BTDLH&t;&t;__REG(0x40200004)  /* Divisor Latch High Register (DLAB = 1) (read/write) */
multiline_comment|/* Standard UART (STUART) */
DECL|macro|STUART
mdefine_line|#define STUART&t;&t;STRBR
DECL|macro|STRBR
mdefine_line|#define STRBR&t;&t;__REG(0x40700000)  /* Receive Buffer Register (read only) */
DECL|macro|STTHR
mdefine_line|#define STTHR&t;&t;__REG(0x40700000)  /* Transmit Holding Register (write only) */
DECL|macro|STIER
mdefine_line|#define STIER&t;&t;__REG(0x40700004)  /* Interrupt Enable Register (read/write) */
DECL|macro|STIIR
mdefine_line|#define STIIR&t;&t;__REG(0x40700008)  /* Interrupt ID Register (read only) */
DECL|macro|STFCR
mdefine_line|#define STFCR&t;&t;__REG(0x40700008)  /* FIFO Control Register (write only) */
DECL|macro|STLCR
mdefine_line|#define STLCR&t;&t;__REG(0x4070000C)  /* Line Control Register (read/write) */
DECL|macro|STMCR
mdefine_line|#define STMCR&t;&t;__REG(0x40700010)  /* Modem Control Register (read/write) */
DECL|macro|STLSR
mdefine_line|#define STLSR&t;&t;__REG(0x40700014)  /* Line Status Register (read only) */
DECL|macro|STMSR
mdefine_line|#define STMSR&t;&t;__REG(0x40700018)  /* Reserved */
DECL|macro|STSPR
mdefine_line|#define STSPR&t;&t;__REG(0x4070001C)  /* Scratch Pad Register (read/write) */
DECL|macro|STISR
mdefine_line|#define STISR&t;&t;__REG(0x40700020)  /* Infrared Selection Register (read/write) */
DECL|macro|STDLL
mdefine_line|#define STDLL&t;&t;__REG(0x40700000)  /* Divisor Latch Low Register (DLAB = 1) (read/write) */
DECL|macro|STDLH
mdefine_line|#define STDLH&t;&t;__REG(0x40700004)  /* Divisor Latch High Register (DLAB = 1) (read/write) */
DECL|macro|IER_DMAE
mdefine_line|#define IER_DMAE&t;(1 &lt;&lt; 7)&t;/* DMA Requests Enable */
DECL|macro|IER_UUE
mdefine_line|#define IER_UUE&t;&t;(1 &lt;&lt; 6)&t;/* UART Unit Enable */
DECL|macro|IER_NRZE
mdefine_line|#define IER_NRZE&t;(1 &lt;&lt; 5)&t;/* NRZ coding Enable */
DECL|macro|IER_RTIOE
mdefine_line|#define IER_RTIOE&t;(1 &lt;&lt; 4)&t;/* Receiver Time Out Interrupt Enable */
DECL|macro|IER_MIE
mdefine_line|#define IER_MIE&t;&t;(1 &lt;&lt; 3)&t;/* Modem Interrupt Enable */
DECL|macro|IER_RLSE
mdefine_line|#define IER_RLSE&t;(1 &lt;&lt; 2)&t;/* Receiver Line Status Interrupt Enable */
DECL|macro|IER_TIE
mdefine_line|#define IER_TIE&t;&t;(1 &lt;&lt; 1)&t;/* Transmit Data request Interrupt Enable */
DECL|macro|IER_RAVIE
mdefine_line|#define IER_RAVIE&t;(1 &lt;&lt; 0)&t;/* Receiver Data Available Interrupt Enable */
DECL|macro|IIR_FIFOES1
mdefine_line|#define IIR_FIFOES1&t;(1 &lt;&lt; 7)&t;/* FIFO Mode Enable Status */
DECL|macro|IIR_FIFOES0
mdefine_line|#define IIR_FIFOES0&t;(1 &lt;&lt; 6)&t;/* FIFO Mode Enable Status */
DECL|macro|IIR_TOD
mdefine_line|#define IIR_TOD&t;&t;(1 &lt;&lt; 3)&t;/* Time Out Detected */
DECL|macro|IIR_IID2
mdefine_line|#define IIR_IID2&t;(1 &lt;&lt; 2)&t;/* Interrupt Source Encoded */
DECL|macro|IIR_IID1
mdefine_line|#define IIR_IID1&t;(1 &lt;&lt; 1)&t;/* Interrupt Source Encoded */
DECL|macro|IIR_IP
mdefine_line|#define IIR_IP&t;&t;(1 &lt;&lt; 0)&t;/* Interrupt Pending (active low) */
DECL|macro|FCR_ITL2
mdefine_line|#define FCR_ITL2&t;(1 &lt;&lt; 7)&t;/* Interrupt Trigger Level */
DECL|macro|FCR_ITL1
mdefine_line|#define FCR_ITL1&t;(1 &lt;&lt; 6)&t;/* Interrupt Trigger Level */
DECL|macro|FCR_RESETTF
mdefine_line|#define FCR_RESETTF&t;(1 &lt;&lt; 2)&t;/* Reset Transmitter FIFO */
DECL|macro|FCR_RESETRF
mdefine_line|#define FCR_RESETRF&t;(1 &lt;&lt; 1)&t;/* Reset Receiver FIFO */
DECL|macro|FCR_TRFIFOE
mdefine_line|#define FCR_TRFIFOE&t;(1 &lt;&lt; 0)&t;/* Transmit and Receive FIFO Enable */
DECL|macro|FCR_ITL_1
mdefine_line|#define FCR_ITL_1&t;(0)
DECL|macro|FCR_ITL_8
mdefine_line|#define FCR_ITL_8&t;(FCR_ITL1)
DECL|macro|FCR_ITL_16
mdefine_line|#define FCR_ITL_16&t;(FCR_ITL2)
DECL|macro|FCR_ITL_32
mdefine_line|#define FCR_ITL_32&t;(FCR_ITL2|FCR_ITL1)
DECL|macro|LCR_DLAB
mdefine_line|#define LCR_DLAB&t;(1 &lt;&lt; 7)&t;/* Divisor Latch Access Bit */
DECL|macro|LCR_SB
mdefine_line|#define LCR_SB&t;&t;(1 &lt;&lt; 6)&t;/* Set Break */
DECL|macro|LCR_STKYP
mdefine_line|#define LCR_STKYP&t;(1 &lt;&lt; 5)&t;/* Sticky Parity */
DECL|macro|LCR_EPS
mdefine_line|#define LCR_EPS&t;&t;(1 &lt;&lt; 4)&t;/* Even Parity Select */
DECL|macro|LCR_PEN
mdefine_line|#define LCR_PEN&t;&t;(1 &lt;&lt; 3)&t;/* Parity Enable */
DECL|macro|LCR_STB
mdefine_line|#define LCR_STB&t;&t;(1 &lt;&lt; 2)&t;/* Stop Bit */
DECL|macro|LCR_WLS1
mdefine_line|#define LCR_WLS1&t;(1 &lt;&lt; 1)&t;/* Word Length Select */
DECL|macro|LCR_WLS0
mdefine_line|#define LCR_WLS0&t;(1 &lt;&lt; 0)&t;/* Word Length Select */
DECL|macro|LSR_FIFOE
mdefine_line|#define LSR_FIFOE&t;(1 &lt;&lt; 7)&t;/* FIFO Error Status */
DECL|macro|LSR_TEMT
mdefine_line|#define LSR_TEMT&t;(1 &lt;&lt; 6)&t;/* Transmitter Empty */
DECL|macro|LSR_TDRQ
mdefine_line|#define LSR_TDRQ&t;(1 &lt;&lt; 5)&t;/* Transmit Data Request */
DECL|macro|LSR_BI
mdefine_line|#define LSR_BI&t;&t;(1 &lt;&lt; 4)&t;/* Break Interrupt */
DECL|macro|LSR_FE
mdefine_line|#define LSR_FE&t;&t;(1 &lt;&lt; 3)&t;/* Framing Error */
DECL|macro|LSR_PE
mdefine_line|#define LSR_PE&t;&t;(1 &lt;&lt; 2)&t;/* Parity Error */
DECL|macro|LSR_OE
mdefine_line|#define LSR_OE&t;&t;(1 &lt;&lt; 1)&t;/* Overrun Error */
DECL|macro|LSR_DR
mdefine_line|#define LSR_DR&t;&t;(1 &lt;&lt; 0)&t;/* Data Ready */
DECL|macro|MCR_LOOP
mdefine_line|#define MCR_LOOP&t;(1 &lt;&lt; 4)
DECL|macro|MCR_OUT2
mdefine_line|#define MCR_OUT2&t;(1 &lt;&lt; 3)&t;/* force MSR_DCD in loopback mode */
DECL|macro|MCR_OUT1
mdefine_line|#define MCR_OUT1&t;(1 &lt;&lt; 2)&t;/* force MSR_RI in loopback mode */
DECL|macro|MCR_RTS
mdefine_line|#define MCR_RTS&t;&t;(1 &lt;&lt; 1)&t;/* Request to Send */
DECL|macro|MCR_DTR
mdefine_line|#define MCR_DTR&t;&t;(1 &lt;&lt; 0)&t;/* Data Terminal Ready */
DECL|macro|MSR_DCD
mdefine_line|#define MSR_DCD&t;&t;(1 &lt;&lt; 7)&t;/* Data Carrier Detect */
DECL|macro|MSR_RI
mdefine_line|#define MSR_RI&t;&t;(1 &lt;&lt; 6)&t;/* Ring Indicator */
DECL|macro|MSR_DSR
mdefine_line|#define MSR_DSR&t;&t;(1 &lt;&lt; 5)&t;/* Data Set Ready */
DECL|macro|MSR_CTS
mdefine_line|#define MSR_CTS&t;&t;(1 &lt;&lt; 4)&t;/* Clear To Send */
DECL|macro|MSR_DDCD
mdefine_line|#define MSR_DDCD&t;(1 &lt;&lt; 3)&t;/* Delta Data Carrier Detect */
DECL|macro|MSR_TERI
mdefine_line|#define MSR_TERI&t;(1 &lt;&lt; 2)&t;/* Trailing Edge Ring Indicator */
DECL|macro|MSR_DDSR
mdefine_line|#define MSR_DDSR&t;(1 &lt;&lt; 1)&t;/* Delta Data Set Ready */
DECL|macro|MSR_DCTS
mdefine_line|#define MSR_DCTS&t;(1 &lt;&lt; 0)&t;/* Delta Clear To Send */
multiline_comment|/*&n; * IrSR (Infrared Selection Register)&n; */
DECL|macro|STISR_RXPL
mdefine_line|#define STISR_RXPL      (1 &lt;&lt; 4)        /* Receive Data Polarity */
DECL|macro|STISR_TXPL
mdefine_line|#define STISR_TXPL      (1 &lt;&lt; 3)        /* Transmit Data Polarity */
DECL|macro|STISR_XMODE
mdefine_line|#define STISR_XMODE     (1 &lt;&lt; 2)        /* Transmit Pulse Width Select */
DECL|macro|STISR_RCVEIR
mdefine_line|#define STISR_RCVEIR    (1 &lt;&lt; 1)        /* Receiver SIR Enable */
DECL|macro|STISR_XMITIR
mdefine_line|#define STISR_XMITIR    (1 &lt;&lt; 0)        /* Transmitter SIR Enable */
multiline_comment|/*&n; * I2C registers&n; */
DECL|macro|IBMR
mdefine_line|#define IBMR&t;&t;__REG(0x40301680)  /* I2C Bus Monitor Register - IBMR */
DECL|macro|IDBR
mdefine_line|#define IDBR&t;&t;__REG(0x40301688)  /* I2C Data Buffer Register - IDBR */
DECL|macro|ICR
mdefine_line|#define ICR&t;&t;__REG(0x40301690)  /* I2C Control Register - ICR */
DECL|macro|ISR
mdefine_line|#define ISR&t;&t;__REG(0x40301698)  /* I2C Status Register - ISR */
DECL|macro|ISAR
mdefine_line|#define ISAR&t;&t;__REG(0x403016A0)  /* I2C Slave Address Register - ISAR */
DECL|macro|PWRIBMR
mdefine_line|#define PWRIBMR    __REG(0x40f00180)  /* Power I2C Bus Monitor Register-IBMR */
DECL|macro|PWRIDBR
mdefine_line|#define PWRIDBR    __REG(0x40f00188)  /* Power I2C Data Buffer Register-IDBR */
DECL|macro|PWRICR
mdefine_line|#define PWRICR __REG(0x40f00190)  /* Power I2C Control Register - ICR */
DECL|macro|PWRISR
mdefine_line|#define PWRISR __REG(0x40f00198)  /* Power I2C Status Register - ISR */
DECL|macro|PWRISAR
mdefine_line|#define PWRISAR    __REG(0x40f001A0)  /*Power I2C Slave Address Register-ISAR */
DECL|macro|ICR_START
mdefine_line|#define ICR_START&t;(1 &lt;&lt; 0)&t;   /* start bit */
DECL|macro|ICR_STOP
mdefine_line|#define ICR_STOP&t;(1 &lt;&lt; 1)&t;   /* stop bit */
DECL|macro|ICR_ACKNAK
mdefine_line|#define ICR_ACKNAK&t;(1 &lt;&lt; 2)&t;   /* send ACK(0) or NAK(1) */
DECL|macro|ICR_TB
mdefine_line|#define ICR_TB&t;&t;(1 &lt;&lt; 3)&t;   /* transfer byte bit */
DECL|macro|ICR_MA
mdefine_line|#define ICR_MA&t;&t;(1 &lt;&lt; 4)&t;   /* master abort */
DECL|macro|ICR_SCLE
mdefine_line|#define ICR_SCLE&t;(1 &lt;&lt; 5)&t;   /* master clock enable */
DECL|macro|ICR_IUE
mdefine_line|#define ICR_IUE&t;&t;(1 &lt;&lt; 6)&t;   /* unit enable */
DECL|macro|ICR_GCD
mdefine_line|#define ICR_GCD&t;&t;(1 &lt;&lt; 7)&t;   /* general call disable */
DECL|macro|ICR_ITEIE
mdefine_line|#define ICR_ITEIE&t;(1 &lt;&lt; 8)&t;   /* enable tx interrupts */
DECL|macro|ICR_IRFIE
mdefine_line|#define ICR_IRFIE&t;(1 &lt;&lt; 9)&t;   /* enable rx interrupts */
DECL|macro|ICR_BEIE
mdefine_line|#define ICR_BEIE&t;(1 &lt;&lt; 10)&t;   /* enable bus error ints */
DECL|macro|ICR_SSDIE
mdefine_line|#define ICR_SSDIE&t;(1 &lt;&lt; 11)&t;   /* slave STOP detected int enable */
DECL|macro|ICR_ALDIE
mdefine_line|#define ICR_ALDIE&t;(1 &lt;&lt; 12)&t;   /* enable arbitration interrupt */
DECL|macro|ICR_SADIE
mdefine_line|#define ICR_SADIE&t;(1 &lt;&lt; 13)&t;   /* slave address detected int enable */
DECL|macro|ICR_UR
mdefine_line|#define ICR_UR&t;&t;(1 &lt;&lt; 14)&t;   /* unit reset */
DECL|macro|ISR_RWM
mdefine_line|#define ISR_RWM&t;&t;(1 &lt;&lt; 0)&t;   /* read/write mode */
DECL|macro|ISR_ACKNAK
mdefine_line|#define ISR_ACKNAK&t;(1 &lt;&lt; 1)&t;   /* ack/nak status */
DECL|macro|ISR_UB
mdefine_line|#define ISR_UB&t;&t;(1 &lt;&lt; 2)&t;   /* unit busy */
DECL|macro|ISR_IBB
mdefine_line|#define ISR_IBB&t;&t;(1 &lt;&lt; 3)&t;   /* bus busy */
DECL|macro|ISR_SSD
mdefine_line|#define ISR_SSD&t;&t;(1 &lt;&lt; 4)&t;   /* slave stop detected */
DECL|macro|ISR_ALD
mdefine_line|#define ISR_ALD&t;&t;(1 &lt;&lt; 5)&t;   /* arbitration loss detected */
DECL|macro|ISR_ITE
mdefine_line|#define ISR_ITE&t;&t;(1 &lt;&lt; 6)&t;   /* tx buffer empty */
DECL|macro|ISR_IRF
mdefine_line|#define ISR_IRF&t;&t;(1 &lt;&lt; 7)&t;   /* rx buffer full */
DECL|macro|ISR_GCAD
mdefine_line|#define ISR_GCAD&t;(1 &lt;&lt; 8)&t;   /* general call address detected */
DECL|macro|ISR_SAD
mdefine_line|#define ISR_SAD&t;&t;(1 &lt;&lt; 9)&t;   /* slave address detected */
DECL|macro|ISR_BED
mdefine_line|#define ISR_BED&t;&t;(1 &lt;&lt; 10)&t;   /* bus error no ACK/NAK */
multiline_comment|/*&n; * Serial Audio Controller&n; */
multiline_comment|/* FIXME: This clash with SA1111 defines */
macro_line|#ifndef CONFIG_SA1111
DECL|macro|SACR0
mdefine_line|#define SACR0&t;&t;__REG(0x40400000)  /* Global Control Register */
DECL|macro|SACR1
mdefine_line|#define SACR1&t;&t;__REG(0x40400004)  /* Serial Audio I 2 S/MSB-Justified Control Register */
DECL|macro|SASR0
mdefine_line|#define SASR0&t;&t;__REG(0x4040000C)  /* Serial Audio I 2 S/MSB-Justified Interface and FIFO Status Register */
DECL|macro|SAIMR
mdefine_line|#define SAIMR&t;&t;__REG(0x40400014)  /* Serial Audio Interrupt Mask Register */
DECL|macro|SAICR
mdefine_line|#define SAICR&t;&t;__REG(0x40400018)  /* Serial Audio Interrupt Clear Register */
DECL|macro|SADIV
mdefine_line|#define SADIV&t;&t;__REG(0x40400060)  /* Audio Clock Divider Register. */
DECL|macro|SADR
mdefine_line|#define SADR&t;&t;__REG(0x40400080)  /* Serial Audio Data Register (TX and RX FIFO access Register). */
macro_line|#endif
DECL|macro|SACR0_RFTH
mdefine_line|#define SACR0_RFTH(x)&t;(x &lt;&lt; 12)&t;&t;/* Rx FIFO Interrupt or DMA Trigger Threshold */
DECL|macro|SACR0_TFTH
mdefine_line|#define SACR0_TFTH(x)&t;(x &lt;&lt; 8)&t;&t;/* Tx FIFO Interrupt or DMA Trigger Threshold */
DECL|macro|SACR0_STRF
mdefine_line|#define SACR0_STRF&t;&t;(1 &lt;&lt; 5)&t;&t;/* FIFO Select for EFWR Special Function */
DECL|macro|SACR0_EFWR
mdefine_line|#define SACR0_EFWR&t;&t;(1 &lt;&lt; 4)&t;&t;/* Enable EFWR Function  */
DECL|macro|SACR0_RST
mdefine_line|#define SACR0_RST&t;&t;(1 &lt;&lt; 3)&t;&t;/* FIFO, i2s Register Reset */
DECL|macro|SACR0_BCKD
mdefine_line|#define SACR0_BCKD&t;&t;(1 &lt;&lt; 2) &t;&t;/* Bit Clock Direction */
DECL|macro|SACR0_ENB
mdefine_line|#define SACR0_ENB&t;&t;(1 &lt;&lt; 0)&t;&t;/* Enable I2S Link */
DECL|macro|SACR1_ENLBF
mdefine_line|#define SACR1_ENLBF&t;&t;(1 &lt;&lt; 5)&t;&t;/* Enable Loopback */
DECL|macro|SACR1_DRPL
mdefine_line|#define SACR1_DRPL&t;&t;(1 &lt;&lt; 4) &t;&t;/* Disable Replaying Function */
DECL|macro|SACR1_DREC
mdefine_line|#define SACR1_DREC&t;&t;(1 &lt;&lt; 3)&t;&t;/* Disable Recording Function */
DECL|macro|SACR1_AMSL
mdefine_line|#define SACR1_AMSL&t;&t;(1 &lt;&lt; 1)&t;&t;/* Specify Alternate Mode */
DECL|macro|SASR0_I2SOFF
mdefine_line|#define SASR0_I2SOFF&t;(1 &lt;&lt; 7)&t;&t;/* Controller Status */
DECL|macro|SASR0_ROR
mdefine_line|#define SASR0_ROR&t;&t;(1 &lt;&lt; 6)&t;&t;/* Rx FIFO Overrun */
DECL|macro|SASR0_TUR
mdefine_line|#define SASR0_TUR&t;&t;(1 &lt;&lt; 5)&t;&t;/* Tx FIFO Underrun */
DECL|macro|SASR0_RFS
mdefine_line|#define SASR0_RFS&t;&t;(1 &lt;&lt; 4)&t;&t;/* Rx FIFO Service Request */
DECL|macro|SASR0_TFS
mdefine_line|#define SASR0_TFS&t;&t;(1 &lt;&lt; 3)&t;&t;/* Tx FIFO Service Request */
DECL|macro|SASR0_BSY
mdefine_line|#define SASR0_BSY&t;&t;(1 &lt;&lt; 2)&t;&t;/* I2S Busy */
DECL|macro|SASR0_RNE
mdefine_line|#define SASR0_RNE&t;&t;(1 &lt;&lt; 1)&t;&t;/* Rx FIFO Not Empty */
DECL|macro|SASR0_TNF
mdefine_line|#define SASR0_TNF&t;&t;(1 &lt;&lt; 0) &t;&t;/* Tx FIFO Not Empty */
DECL|macro|SADIV_3_058M
mdefine_line|#define SADIV_3_058M&t;0x0c&t;&t;&t;/* Serial Clock Divider 3.058MHz */
DECL|macro|SADIV_2_836M
mdefine_line|#define SADIV_2_836M&t;0x0d&t;&t;&t;/* 2.836 MHz */
DECL|macro|SADIV_1_405M
mdefine_line|#define SADIV_1_405M&t;0x1a&t;&t;&t;/* 1.405 MHz */
DECL|macro|SADIV_1_026M
mdefine_line|#define SADIV_1_026M&t;0x24&t;&t;&t;/* 1.026 MHz */
DECL|macro|SADIV_702K
mdefine_line|#define SADIV_702K&t;&t;0x34&t;&t;&t;/* 702 kHz */
DECL|macro|SADIV_513K
mdefine_line|#define SADIV_513K&t;&t;0x48&t;&t;&t;/* 513 kHz */
DECL|macro|SAICR_ROR
mdefine_line|#define SAICR_ROR&t;&t;(1 &lt;&lt; 6)&t;&t;/* Clear Rx FIFO Overrun Interrupt */
DECL|macro|SAICR_TUR
mdefine_line|#define SAICR_TUR&t;&t;(1 &lt;&lt; 5)&t;&t;/* Clear Tx FIFO Underrun Interrupt */
DECL|macro|SAIMR_ROR
mdefine_line|#define SAIMR_ROR&t;&t;(1 &lt;&lt; 6)&t;&t;/* Enable Rx FIFO Overrun Condition Interrupt */
DECL|macro|SAIMR_TUR
mdefine_line|#define SAIMR_TUR&t;&t;(1 &lt;&lt; 5)&t;&t;/* Enable Tx FIFO Underrun Condition Interrupt */
DECL|macro|SAIMR_RFS
mdefine_line|#define SAIMR_RFS&t;&t;(1 &lt;&lt; 4)&t;&t;/* Enable Rx FIFO Service Interrupt */
DECL|macro|SAIMR_TFS
mdefine_line|#define SAIMR_TFS&t;&t;(1 &lt;&lt; 3)&t;&t;/* Enable Tx FIFO Service Interrupt */
multiline_comment|/*&n; * AC97 Controller registers&n; */
DECL|macro|POCR
mdefine_line|#define POCR&t;&t;__REG(0x40500000)  /* PCM Out Control Register */
DECL|macro|POCR_FEIE
mdefine_line|#define POCR_FEIE&t;(1 &lt;&lt; 3)&t;/* FIFO Error Interrupt Enable */
DECL|macro|PICR
mdefine_line|#define PICR&t;&t;__REG(0x40500004)  /* PCM In Control Register */
DECL|macro|PICR_FEIE
mdefine_line|#define PICR_FEIE&t;(1 &lt;&lt; 3)&t;/* FIFO Error Interrupt Enable */
DECL|macro|MCCR
mdefine_line|#define MCCR&t;&t;__REG(0x40500008)  /* Mic In Control Register */
DECL|macro|MCCR_FEIE
mdefine_line|#define MCCR_FEIE&t;(1 &lt;&lt; 3)&t;/* FIFO Error Interrupt Enable */
DECL|macro|GCR
mdefine_line|#define GCR&t;&t;__REG(0x4050000C)  /* Global Control Register */
DECL|macro|GCR_CDONE_IE
mdefine_line|#define GCR_CDONE_IE&t;(1 &lt;&lt; 19)&t;/* Command Done Interrupt Enable */
DECL|macro|GCR_SDONE_IE
mdefine_line|#define GCR_SDONE_IE&t;(1 &lt;&lt; 18)&t;/* Status Done Interrupt Enable */
DECL|macro|GCR_SECRDY_IEN
mdefine_line|#define GCR_SECRDY_IEN&t;(1 &lt;&lt; 9)&t;/* Secondary Ready Interrupt Enable */
DECL|macro|GCR_PRIRDY_IEN
mdefine_line|#define GCR_PRIRDY_IEN&t;(1 &lt;&lt; 8)&t;/* Primary Ready Interrupt Enable */
DECL|macro|GCR_SECRES_IEN
mdefine_line|#define GCR_SECRES_IEN&t;(1 &lt;&lt; 5)&t;/* Secondary Resume Interrupt Enable */
DECL|macro|GCR_PRIRES_IEN
mdefine_line|#define GCR_PRIRES_IEN&t;(1 &lt;&lt; 4)&t;/* Primary Resume Interrupt Enable */
DECL|macro|GCR_ACLINK_OFF
mdefine_line|#define GCR_ACLINK_OFF&t;(1 &lt;&lt; 3)&t;/* AC-link Shut Off */
DECL|macro|GCR_WARM_RST
mdefine_line|#define GCR_WARM_RST&t;(1 &lt;&lt; 2)&t;/* AC97 Warm Reset */
DECL|macro|GCR_COLD_RST
mdefine_line|#define GCR_COLD_RST&t;(1 &lt;&lt; 1)&t;/* AC&squot;97 Cold Reset (0 = active) */
DECL|macro|GCR_GIE
mdefine_line|#define GCR_GIE&t;&t;(1 &lt;&lt; 0)&t;/* Codec GPI Interrupt Enable */
DECL|macro|POSR
mdefine_line|#define POSR&t;&t;__REG(0x40500010)  /* PCM Out Status Register */
DECL|macro|POSR_FIFOE
mdefine_line|#define POSR_FIFOE&t;(1 &lt;&lt; 4)&t;/* FIFO error */
DECL|macro|PISR
mdefine_line|#define PISR&t;&t;__REG(0x40500014)  /* PCM In Status Register */
DECL|macro|PISR_FIFOE
mdefine_line|#define PISR_FIFOE&t;(1 &lt;&lt; 4)&t;/* FIFO error */
DECL|macro|MCSR
mdefine_line|#define MCSR&t;&t;__REG(0x40500018)  /* Mic In Status Register */
DECL|macro|MCSR_FIFOE
mdefine_line|#define MCSR_FIFOE&t;(1 &lt;&lt; 4)&t;/* FIFO error */
DECL|macro|GSR
mdefine_line|#define GSR&t;&t;__REG(0x4050001C)  /* Global Status Register */
DECL|macro|GSR_CDONE
mdefine_line|#define GSR_CDONE&t;(1 &lt;&lt; 19)&t;/* Command Done */
DECL|macro|GSR_SDONE
mdefine_line|#define GSR_SDONE&t;(1 &lt;&lt; 18)&t;/* Status Done */
DECL|macro|GSR_RDCS
mdefine_line|#define GSR_RDCS&t;(1 &lt;&lt; 15)&t;/* Read Completion Status */
DECL|macro|GSR_BIT3SLT12
mdefine_line|#define GSR_BIT3SLT12&t;(1 &lt;&lt; 14)&t;/* Bit 3 of slot 12 */
DECL|macro|GSR_BIT2SLT12
mdefine_line|#define GSR_BIT2SLT12&t;(1 &lt;&lt; 13)&t;/* Bit 2 of slot 12 */
DECL|macro|GSR_BIT1SLT12
mdefine_line|#define GSR_BIT1SLT12&t;(1 &lt;&lt; 12)&t;/* Bit 1 of slot 12 */
DECL|macro|GSR_SECRES
mdefine_line|#define GSR_SECRES&t;(1 &lt;&lt; 11)&t;/* Secondary Resume Interrupt */
DECL|macro|GSR_PRIRES
mdefine_line|#define GSR_PRIRES&t;(1 &lt;&lt; 10)&t;/* Primary Resume Interrupt */
DECL|macro|GSR_SCR
mdefine_line|#define GSR_SCR&t;&t;(1 &lt;&lt; 9)&t;/* Secondary Codec Ready */
DECL|macro|GSR_PCR
mdefine_line|#define GSR_PCR&t;&t;(1 &lt;&lt; 8)&t;/*  Primary Codec Ready */
DECL|macro|GSR_MINT
mdefine_line|#define GSR_MINT&t;(1 &lt;&lt; 7)&t;/* Mic In Interrupt */
DECL|macro|GSR_POINT
mdefine_line|#define GSR_POINT&t;(1 &lt;&lt; 6)&t;/* PCM Out Interrupt */
DECL|macro|GSR_PIINT
mdefine_line|#define GSR_PIINT&t;(1 &lt;&lt; 5)&t;/* PCM In Interrupt */
DECL|macro|GSR_MOINT
mdefine_line|#define GSR_MOINT&t;(1 &lt;&lt; 2)&t;/* Modem Out Interrupt */
DECL|macro|GSR_MIINT
mdefine_line|#define GSR_MIINT&t;(1 &lt;&lt; 1)&t;/* Modem In Interrupt */
DECL|macro|GSR_GSCI
mdefine_line|#define GSR_GSCI&t;(1 &lt;&lt; 0)&t;/* Codec GPI Status Change Interrupt */
DECL|macro|CAR
mdefine_line|#define CAR&t;&t;__REG(0x40500020)  /* CODEC Access Register */
DECL|macro|CAR_CAIP
mdefine_line|#define CAR_CAIP&t;(1 &lt;&lt; 0)&t;/* Codec Access In Progress */
DECL|macro|PCDR
mdefine_line|#define PCDR&t;&t;__REG(0x40500040)  /* PCM FIFO Data Register */
DECL|macro|MCDR
mdefine_line|#define MCDR&t;&t;__REG(0x40500060)  /* Mic-in FIFO Data Register */
DECL|macro|MOCR
mdefine_line|#define MOCR&t;&t;__REG(0x40500100)  /* Modem Out Control Register */
DECL|macro|MOCR_FEIE
mdefine_line|#define MOCR_FEIE&t;(1 &lt;&lt; 3)&t;/* FIFO Error */
DECL|macro|MICR
mdefine_line|#define MICR&t;&t;__REG(0x40500108)  /* Modem In Control Register */
DECL|macro|MICR_FEIE
mdefine_line|#define MICR_FEIE&t;(1 &lt;&lt; 3)&t;/* FIFO Error */
DECL|macro|MOSR
mdefine_line|#define MOSR&t;&t;__REG(0x40500110)  /* Modem Out Status Register */
DECL|macro|MOSR_FIFOE
mdefine_line|#define MOSR_FIFOE&t;(1 &lt;&lt; 4)&t;/* FIFO error */
DECL|macro|MISR
mdefine_line|#define MISR&t;&t;__REG(0x40500118)  /* Modem In Status Register */
DECL|macro|MISR_FIFOE
mdefine_line|#define MISR_FIFOE&t;(1 &lt;&lt; 4)&t;/* FIFO error */
DECL|macro|MODR
mdefine_line|#define MODR&t;&t;__REG(0x40500140)  /* Modem FIFO Data Register */
DECL|macro|PAC_REG_BASE
mdefine_line|#define PAC_REG_BASE&t;__REG(0x40500200)  /* Primary Audio Codec */
DECL|macro|SAC_REG_BASE
mdefine_line|#define SAC_REG_BASE&t;__REG(0x40500300)  /* Secondary Audio Codec */
DECL|macro|PMC_REG_BASE
mdefine_line|#define PMC_REG_BASE&t;__REG(0x40500400)  /* Primary Modem Codec */
DECL|macro|SMC_REG_BASE
mdefine_line|#define SMC_REG_BASE&t;__REG(0x40500500)  /* Secondary Modem Codec */
multiline_comment|/*&n; * USB Device Controller&n; * PXA25x and PXA27x USB device controller registers are different.&n; */
macro_line|#if defined(CONFIG_PXA25x)
DECL|macro|UDC_RES1
mdefine_line|#define UDC_RES1&t;__REG(0x40600004)  /* UDC Undocumented - Reserved1 */
DECL|macro|UDC_RES2
mdefine_line|#define UDC_RES2&t;__REG(0x40600008)  /* UDC Undocumented - Reserved2 */
DECL|macro|UDC_RES3
mdefine_line|#define UDC_RES3&t;__REG(0x4060000C)  /* UDC Undocumented - Reserved3 */
DECL|macro|UDCCR
mdefine_line|#define UDCCR&t;&t;__REG(0x40600000)  /* UDC Control Register */
DECL|macro|UDCCR_UDE
mdefine_line|#define UDCCR_UDE&t;(1 &lt;&lt; 0)&t;/* UDC enable */
DECL|macro|UDCCR_UDA
mdefine_line|#define UDCCR_UDA&t;(1 &lt;&lt; 1)&t;/* UDC active */
DECL|macro|UDCCR_RSM
mdefine_line|#define UDCCR_RSM&t;(1 &lt;&lt; 2)&t;/* Device resume */
DECL|macro|UDCCR_RESIR
mdefine_line|#define UDCCR_RESIR&t;(1 &lt;&lt; 3)&t;/* Resume interrupt request */
DECL|macro|UDCCR_SUSIR
mdefine_line|#define UDCCR_SUSIR&t;(1 &lt;&lt; 4)&t;/* Suspend interrupt request */
DECL|macro|UDCCR_SRM
mdefine_line|#define UDCCR_SRM&t;(1 &lt;&lt; 5)&t;/* Suspend/resume interrupt mask */
DECL|macro|UDCCR_RSTIR
mdefine_line|#define UDCCR_RSTIR&t;(1 &lt;&lt; 6)&t;/* Reset interrupt request */
DECL|macro|UDCCR_REM
mdefine_line|#define UDCCR_REM&t;(1 &lt;&lt; 7)&t;/* Reset interrupt mask */
DECL|macro|UDCCS0
mdefine_line|#define UDCCS0&t;&t;__REG(0x40600010)  /* UDC Endpoint 0 Control/Status Register */
DECL|macro|UDCCS0_OPR
mdefine_line|#define UDCCS0_OPR&t;(1 &lt;&lt; 0)&t;/* OUT packet ready */
DECL|macro|UDCCS0_IPR
mdefine_line|#define UDCCS0_IPR&t;(1 &lt;&lt; 1)&t;/* IN packet ready */
DECL|macro|UDCCS0_FTF
mdefine_line|#define UDCCS0_FTF&t;(1 &lt;&lt; 2)&t;/* Flush Tx FIFO */
DECL|macro|UDCCS0_DRWF
mdefine_line|#define UDCCS0_DRWF&t;(1 &lt;&lt; 3)&t;/* Device remote wakeup feature */
DECL|macro|UDCCS0_SST
mdefine_line|#define UDCCS0_SST&t;(1 &lt;&lt; 4)&t;/* Sent stall */
DECL|macro|UDCCS0_FST
mdefine_line|#define UDCCS0_FST&t;(1 &lt;&lt; 5)&t;/* Force stall */
DECL|macro|UDCCS0_RNE
mdefine_line|#define UDCCS0_RNE&t;(1 &lt;&lt; 6)&t;/* Receive FIFO no empty */
DECL|macro|UDCCS0_SA
mdefine_line|#define UDCCS0_SA&t;(1 &lt;&lt; 7)&t;/* Setup active */
multiline_comment|/* Bulk IN - Endpoint 1,6,11 */
DECL|macro|UDCCS1
mdefine_line|#define UDCCS1&t;&t;__REG(0x40600014)  /* UDC Endpoint 1 (IN) Control/Status Register */
DECL|macro|UDCCS6
mdefine_line|#define UDCCS6&t;&t;__REG(0x40600028)  /* UDC Endpoint 6 (IN) Control/Status Register */
DECL|macro|UDCCS11
mdefine_line|#define UDCCS11&t;&t;__REG(0x4060003C)  /* UDC Endpoint 11 (IN) Control/Status Register */
DECL|macro|UDCCS_BI_TFS
mdefine_line|#define UDCCS_BI_TFS&t;(1 &lt;&lt; 0)&t;/* Transmit FIFO service */
DECL|macro|UDCCS_BI_TPC
mdefine_line|#define UDCCS_BI_TPC&t;(1 &lt;&lt; 1)&t;/* Transmit packet complete */
DECL|macro|UDCCS_BI_FTF
mdefine_line|#define UDCCS_BI_FTF&t;(1 &lt;&lt; 2)&t;/* Flush Tx FIFO */
DECL|macro|UDCCS_BI_TUR
mdefine_line|#define UDCCS_BI_TUR&t;(1 &lt;&lt; 3)&t;/* Transmit FIFO underrun */
DECL|macro|UDCCS_BI_SST
mdefine_line|#define UDCCS_BI_SST&t;(1 &lt;&lt; 4)&t;/* Sent stall */
DECL|macro|UDCCS_BI_FST
mdefine_line|#define UDCCS_BI_FST&t;(1 &lt;&lt; 5)&t;/* Force stall */
DECL|macro|UDCCS_BI_TSP
mdefine_line|#define UDCCS_BI_TSP&t;(1 &lt;&lt; 7)&t;/* Transmit short packet */
multiline_comment|/* Bulk OUT - Endpoint 2,7,12 */
DECL|macro|UDCCS2
mdefine_line|#define UDCCS2&t;&t;__REG(0x40600018)  /* UDC Endpoint 2 (OUT) Control/Status Register */
DECL|macro|UDCCS7
mdefine_line|#define UDCCS7&t;&t;__REG(0x4060002C)  /* UDC Endpoint 7 (OUT) Control/Status Register */
DECL|macro|UDCCS12
mdefine_line|#define UDCCS12&t;&t;__REG(0x40600040)  /* UDC Endpoint 12 (OUT) Control/Status Register */
DECL|macro|UDCCS_BO_RFS
mdefine_line|#define UDCCS_BO_RFS&t;(1 &lt;&lt; 0)&t;/* Receive FIFO service */
DECL|macro|UDCCS_BO_RPC
mdefine_line|#define UDCCS_BO_RPC&t;(1 &lt;&lt; 1)&t;/* Receive packet complete */
DECL|macro|UDCCS_BO_DME
mdefine_line|#define UDCCS_BO_DME&t;(1 &lt;&lt; 3)&t;/* DMA enable */
DECL|macro|UDCCS_BO_SST
mdefine_line|#define UDCCS_BO_SST&t;(1 &lt;&lt; 4)&t;/* Sent stall */
DECL|macro|UDCCS_BO_FST
mdefine_line|#define UDCCS_BO_FST&t;(1 &lt;&lt; 5)&t;/* Force stall */
DECL|macro|UDCCS_BO_RNE
mdefine_line|#define UDCCS_BO_RNE&t;(1 &lt;&lt; 6)&t;/* Receive FIFO not empty */
DECL|macro|UDCCS_BO_RSP
mdefine_line|#define UDCCS_BO_RSP&t;(1 &lt;&lt; 7)&t;/* Receive short packet */
multiline_comment|/* Isochronous IN - Endpoint 3,8,13 */
DECL|macro|UDCCS3
mdefine_line|#define UDCCS3&t;&t;__REG(0x4060001C)  /* UDC Endpoint 3 (IN) Control/Status Register */
DECL|macro|UDCCS8
mdefine_line|#define UDCCS8&t;&t;__REG(0x40600030)  /* UDC Endpoint 8 (IN) Control/Status Register */
DECL|macro|UDCCS13
mdefine_line|#define UDCCS13&t;&t;__REG(0x40600044)  /* UDC Endpoint 13 (IN) Control/Status Register */
DECL|macro|UDCCS_II_TFS
mdefine_line|#define UDCCS_II_TFS&t;(1 &lt;&lt; 0)&t;/* Transmit FIFO service */
DECL|macro|UDCCS_II_TPC
mdefine_line|#define UDCCS_II_TPC&t;(1 &lt;&lt; 1)&t;/* Transmit packet complete */
DECL|macro|UDCCS_II_FTF
mdefine_line|#define UDCCS_II_FTF&t;(1 &lt;&lt; 2)&t;/* Flush Tx FIFO */
DECL|macro|UDCCS_II_TUR
mdefine_line|#define UDCCS_II_TUR&t;(1 &lt;&lt; 3)&t;/* Transmit FIFO underrun */
DECL|macro|UDCCS_II_TSP
mdefine_line|#define UDCCS_II_TSP&t;(1 &lt;&lt; 7)&t;/* Transmit short packet */
multiline_comment|/* Isochronous OUT - Endpoint 4,9,14 */
DECL|macro|UDCCS4
mdefine_line|#define UDCCS4&t;&t;__REG(0x40600020)  /* UDC Endpoint 4 (OUT) Control/Status Register */
DECL|macro|UDCCS9
mdefine_line|#define UDCCS9&t;&t;__REG(0x40600034)  /* UDC Endpoint 9 (OUT) Control/Status Register */
DECL|macro|UDCCS14
mdefine_line|#define UDCCS14&t;&t;__REG(0x40600048)  /* UDC Endpoint 14 (OUT) Control/Status Register */
DECL|macro|UDCCS_IO_RFS
mdefine_line|#define UDCCS_IO_RFS&t;(1 &lt;&lt; 0)&t;/* Receive FIFO service */
DECL|macro|UDCCS_IO_RPC
mdefine_line|#define UDCCS_IO_RPC&t;(1 &lt;&lt; 1)&t;/* Receive packet complete */
DECL|macro|UDCCS_IO_ROF
mdefine_line|#define UDCCS_IO_ROF&t;(1 &lt;&lt; 3)&t;/* Receive overflow */
DECL|macro|UDCCS_IO_DME
mdefine_line|#define UDCCS_IO_DME&t;(1 &lt;&lt; 3)&t;/* DMA enable */
DECL|macro|UDCCS_IO_RNE
mdefine_line|#define UDCCS_IO_RNE&t;(1 &lt;&lt; 6)&t;/* Receive FIFO not empty */
DECL|macro|UDCCS_IO_RSP
mdefine_line|#define UDCCS_IO_RSP&t;(1 &lt;&lt; 7)&t;/* Receive short packet */
multiline_comment|/* Interrupt IN - Endpoint 5,10,15 */
DECL|macro|UDCCS5
mdefine_line|#define UDCCS5&t;&t;__REG(0x40600024)  /* UDC Endpoint 5 (Interrupt) Control/Status Register */
DECL|macro|UDCCS10
mdefine_line|#define UDCCS10&t;&t;__REG(0x40600038)  /* UDC Endpoint 10 (Interrupt) Control/Status Register */
DECL|macro|UDCCS15
mdefine_line|#define UDCCS15&t;&t;__REG(0x4060004C)  /* UDC Endpoint 15 (Interrupt) Control/Status Register */
DECL|macro|UDCCS_INT_TFS
mdefine_line|#define UDCCS_INT_TFS&t;(1 &lt;&lt; 0)&t;/* Transmit FIFO service */
DECL|macro|UDCCS_INT_TPC
mdefine_line|#define UDCCS_INT_TPC&t;(1 &lt;&lt; 1)&t;/* Transmit packet complete */
DECL|macro|UDCCS_INT_FTF
mdefine_line|#define UDCCS_INT_FTF&t;(1 &lt;&lt; 2)&t;/* Flush Tx FIFO */
DECL|macro|UDCCS_INT_TUR
mdefine_line|#define UDCCS_INT_TUR&t;(1 &lt;&lt; 3)&t;/* Transmit FIFO underrun */
DECL|macro|UDCCS_INT_SST
mdefine_line|#define UDCCS_INT_SST&t;(1 &lt;&lt; 4)&t;/* Sent stall */
DECL|macro|UDCCS_INT_FST
mdefine_line|#define UDCCS_INT_FST&t;(1 &lt;&lt; 5)&t;/* Force stall */
DECL|macro|UDCCS_INT_TSP
mdefine_line|#define UDCCS_INT_TSP&t;(1 &lt;&lt; 7)&t;/* Transmit short packet */
DECL|macro|UFNRH
mdefine_line|#define UFNRH&t;&t;__REG(0x40600060)  /* UDC Frame Number Register High */
DECL|macro|UFNRL
mdefine_line|#define UFNRL&t;&t;__REG(0x40600064)  /* UDC Frame Number Register Low */
DECL|macro|UBCR2
mdefine_line|#define UBCR2&t;&t;__REG(0x40600068)  /* UDC Byte Count Reg 2 */
DECL|macro|UBCR4
mdefine_line|#define UBCR4&t;&t;__REG(0x4060006c)  /* UDC Byte Count Reg 4 */
DECL|macro|UBCR7
mdefine_line|#define UBCR7&t;&t;__REG(0x40600070)  /* UDC Byte Count Reg 7 */
DECL|macro|UBCR9
mdefine_line|#define UBCR9&t;&t;__REG(0x40600074)  /* UDC Byte Count Reg 9 */
DECL|macro|UBCR12
mdefine_line|#define UBCR12&t;&t;__REG(0x40600078)  /* UDC Byte Count Reg 12 */
DECL|macro|UBCR14
mdefine_line|#define UBCR14&t;&t;__REG(0x4060007c)  /* UDC Byte Count Reg 14 */
DECL|macro|UDDR0
mdefine_line|#define UDDR0&t;&t;__REG(0x40600080)  /* UDC Endpoint 0 Data Register */
DECL|macro|UDDR1
mdefine_line|#define UDDR1&t;&t;__REG(0x40600100)  /* UDC Endpoint 1 Data Register */
DECL|macro|UDDR2
mdefine_line|#define UDDR2&t;&t;__REG(0x40600180)  /* UDC Endpoint 2 Data Register */
DECL|macro|UDDR3
mdefine_line|#define UDDR3&t;&t;__REG(0x40600200)  /* UDC Endpoint 3 Data Register */
DECL|macro|UDDR4
mdefine_line|#define UDDR4&t;&t;__REG(0x40600400)  /* UDC Endpoint 4 Data Register */
DECL|macro|UDDR5
mdefine_line|#define UDDR5&t;&t;__REG(0x406000A0)  /* UDC Endpoint 5 Data Register */
DECL|macro|UDDR6
mdefine_line|#define UDDR6&t;&t;__REG(0x40600600)  /* UDC Endpoint 6 Data Register */
DECL|macro|UDDR7
mdefine_line|#define UDDR7&t;&t;__REG(0x40600680)  /* UDC Endpoint 7 Data Register */
DECL|macro|UDDR8
mdefine_line|#define UDDR8&t;&t;__REG(0x40600700)  /* UDC Endpoint 8 Data Register */
DECL|macro|UDDR9
mdefine_line|#define UDDR9&t;&t;__REG(0x40600900)  /* UDC Endpoint 9 Data Register */
DECL|macro|UDDR10
mdefine_line|#define UDDR10&t;&t;__REG(0x406000C0)  /* UDC Endpoint 10 Data Register */
DECL|macro|UDDR11
mdefine_line|#define UDDR11&t;&t;__REG(0x40600B00)  /* UDC Endpoint 11 Data Register */
DECL|macro|UDDR12
mdefine_line|#define UDDR12&t;&t;__REG(0x40600B80)  /* UDC Endpoint 12 Data Register */
DECL|macro|UDDR13
mdefine_line|#define UDDR13&t;&t;__REG(0x40600C00)  /* UDC Endpoint 13 Data Register */
DECL|macro|UDDR14
mdefine_line|#define UDDR14&t;&t;__REG(0x40600E00)  /* UDC Endpoint 14 Data Register */
DECL|macro|UDDR15
mdefine_line|#define UDDR15&t;&t;__REG(0x406000E0)  /* UDC Endpoint 15 Data Register */
DECL|macro|UICR0
mdefine_line|#define UICR0&t;&t;__REG(0x40600050)  /* UDC Interrupt Control Register 0 */
DECL|macro|UICR0_IM0
mdefine_line|#define UICR0_IM0&t;(1 &lt;&lt; 0)&t;/* Interrupt mask ep 0 */
DECL|macro|UICR0_IM1
mdefine_line|#define UICR0_IM1&t;(1 &lt;&lt; 1)&t;/* Interrupt mask ep 1 */
DECL|macro|UICR0_IM2
mdefine_line|#define UICR0_IM2&t;(1 &lt;&lt; 2)&t;/* Interrupt mask ep 2 */
DECL|macro|UICR0_IM3
mdefine_line|#define UICR0_IM3&t;(1 &lt;&lt; 3)&t;/* Interrupt mask ep 3 */
DECL|macro|UICR0_IM4
mdefine_line|#define UICR0_IM4&t;(1 &lt;&lt; 4)&t;/* Interrupt mask ep 4 */
DECL|macro|UICR0_IM5
mdefine_line|#define UICR0_IM5&t;(1 &lt;&lt; 5)&t;/* Interrupt mask ep 5 */
DECL|macro|UICR0_IM6
mdefine_line|#define UICR0_IM6&t;(1 &lt;&lt; 6)&t;/* Interrupt mask ep 6 */
DECL|macro|UICR0_IM7
mdefine_line|#define UICR0_IM7&t;(1 &lt;&lt; 7)&t;/* Interrupt mask ep 7 */
DECL|macro|UICR1
mdefine_line|#define UICR1&t;&t;__REG(0x40600054)  /* UDC Interrupt Control Register 1 */
DECL|macro|UICR1_IM8
mdefine_line|#define UICR1_IM8&t;(1 &lt;&lt; 0)&t;/* Interrupt mask ep 8 */
DECL|macro|UICR1_IM9
mdefine_line|#define UICR1_IM9&t;(1 &lt;&lt; 1)&t;/* Interrupt mask ep 9 */
DECL|macro|UICR1_IM10
mdefine_line|#define UICR1_IM10&t;(1 &lt;&lt; 2)&t;/* Interrupt mask ep 10 */
DECL|macro|UICR1_IM11
mdefine_line|#define UICR1_IM11&t;(1 &lt;&lt; 3)&t;/* Interrupt mask ep 11 */
DECL|macro|UICR1_IM12
mdefine_line|#define UICR1_IM12&t;(1 &lt;&lt; 4)&t;/* Interrupt mask ep 12 */
DECL|macro|UICR1_IM13
mdefine_line|#define UICR1_IM13&t;(1 &lt;&lt; 5)&t;/* Interrupt mask ep 13 */
DECL|macro|UICR1_IM14
mdefine_line|#define UICR1_IM14&t;(1 &lt;&lt; 6)&t;/* Interrupt mask ep 14 */
DECL|macro|UICR1_IM15
mdefine_line|#define UICR1_IM15&t;(1 &lt;&lt; 7)&t;/* Interrupt mask ep 15 */
DECL|macro|USIR0
mdefine_line|#define USIR0&t;&t;__REG(0x40600058)  /* UDC Status Interrupt Register 0 */
DECL|macro|USIR0_IR0
mdefine_line|#define USIR0_IR0&t;(1 &lt;&lt; 0)&t;/* Interrup request ep 0 */
DECL|macro|USIR0_IR1
mdefine_line|#define USIR0_IR1&t;(1 &lt;&lt; 1)&t;/* Interrup request ep 1 */
DECL|macro|USIR0_IR2
mdefine_line|#define USIR0_IR2&t;(1 &lt;&lt; 2)&t;/* Interrup request ep 2 */
DECL|macro|USIR0_IR3
mdefine_line|#define USIR0_IR3&t;(1 &lt;&lt; 3)&t;/* Interrup request ep 3 */
DECL|macro|USIR0_IR4
mdefine_line|#define USIR0_IR4&t;(1 &lt;&lt; 4)&t;/* Interrup request ep 4 */
DECL|macro|USIR0_IR5
mdefine_line|#define USIR0_IR5&t;(1 &lt;&lt; 5)&t;/* Interrup request ep 5 */
DECL|macro|USIR0_IR6
mdefine_line|#define USIR0_IR6&t;(1 &lt;&lt; 6)&t;/* Interrup request ep 6 */
DECL|macro|USIR0_IR7
mdefine_line|#define USIR0_IR7&t;(1 &lt;&lt; 7)&t;/* Interrup request ep 7 */
DECL|macro|USIR1
mdefine_line|#define USIR1&t;&t;__REG(0x4060005C)  /* UDC Status Interrupt Register 1 */
DECL|macro|USIR1_IR8
mdefine_line|#define USIR1_IR8&t;(1 &lt;&lt; 0)&t;/* Interrup request ep 8 */
DECL|macro|USIR1_IR9
mdefine_line|#define USIR1_IR9&t;(1 &lt;&lt; 1)&t;/* Interrup request ep 9 */
DECL|macro|USIR1_IR10
mdefine_line|#define USIR1_IR10&t;(1 &lt;&lt; 2)&t;/* Interrup request ep 10 */
DECL|macro|USIR1_IR11
mdefine_line|#define USIR1_IR11&t;(1 &lt;&lt; 3)&t;/* Interrup request ep 11 */
DECL|macro|USIR1_IR12
mdefine_line|#define USIR1_IR12&t;(1 &lt;&lt; 4)&t;/* Interrup request ep 12 */
DECL|macro|USIR1_IR13
mdefine_line|#define USIR1_IR13&t;(1 &lt;&lt; 5)&t;/* Interrup request ep 13 */
DECL|macro|USIR1_IR14
mdefine_line|#define USIR1_IR14&t;(1 &lt;&lt; 6)&t;/* Interrup request ep 14 */
DECL|macro|USIR1_IR15
mdefine_line|#define USIR1_IR15&t;(1 &lt;&lt; 7)&t;/* Interrup request ep 15 */
macro_line|#elif defined(CONFIG_PXA27x)
DECL|macro|UDCCR
mdefine_line|#define UDCCR           __REG(0x40600000) /* UDC Control Register */
DECL|macro|UDCCR_OEN
mdefine_line|#define UDCCR_OEN&t;(1 &lt;&lt; 31)&t;/* On-the-Go Enable */
DECL|macro|UDCCR_AALTHNP
mdefine_line|#define UDCCR_AALTHNP&t;(1 &lt;&lt; 30)&t;/* A-device Alternate Host Negotiation&n;&t;&t;&t;&t;&t;   Protocol Port Support */
DECL|macro|UDCCR_AHNP
mdefine_line|#define UDCCR_AHNP&t;(1 &lt;&lt; 29)&t;/* A-device Host Negotiation Protocol&n;&t;&t;&t;&t;&t;   Support */
DECL|macro|UDCCR_BHNP
mdefine_line|#define UDCCR_BHNP&t;(1 &lt;&lt; 28)&t;/* B-device Host Negotiation Protocol&n;&t;&t;&t;&t;&t;   Enable */
DECL|macro|UDCCR_DWRE
mdefine_line|#define UDCCR_DWRE&t;(1 &lt;&lt; 16)&t;/* Device Remote Wake-up Enable */
DECL|macro|UDCCR_ACN
mdefine_line|#define UDCCR_ACN&t;(0x03 &lt;&lt; 11)&t;/* Active UDC configuration Number */
DECL|macro|UDCCR_ACN_S
mdefine_line|#define UDCCR_ACN_S&t;11
DECL|macro|UDCCR_AIN
mdefine_line|#define UDCCR_AIN&t;(0x07 &lt;&lt; 8)&t;/* Active UDC interface Number */
DECL|macro|UDCCR_AIN_S
mdefine_line|#define UDCCR_AIN_S&t;8
DECL|macro|UDCCR_AAISN
mdefine_line|#define UDCCR_AAISN&t;(0x07 &lt;&lt; 5)&t;/* Active UDC Alternate Interface&n;&t;&t;&t;&t;&t;   Setting Number */
DECL|macro|UDCCR_AAISN_S
mdefine_line|#define UDCCR_AAISN_S&t;5
DECL|macro|UDCCR_SMAC
mdefine_line|#define UDCCR_SMAC&t;(1 &lt;&lt; 4)&t;/* Switch Endpoint Memory to Active&n;&t;&t;&t;&t;&t;   Configuration */
DECL|macro|UDCCR_EMCE
mdefine_line|#define UDCCR_EMCE&t;(1 &lt;&lt; 3)&t;/* Endpoint Memory Configuration&n;&t;&t;&t;&t;&t;   Error */
DECL|macro|UDCCR_UDR
mdefine_line|#define UDCCR_UDR&t;(1 &lt;&lt; 2)&t;/* UDC Resume */
DECL|macro|UDCCR_UDA
mdefine_line|#define UDCCR_UDA&t;(1 &lt;&lt; 1)&t;/* UDC Active */
DECL|macro|UDCCR_UDE
mdefine_line|#define UDCCR_UDE&t;(1 &lt;&lt; 0)&t;/* UDC Enable */
DECL|macro|UDCICR0
mdefine_line|#define UDCICR0         __REG(0x40600004) /* UDC Interrupt Control Register0 */
DECL|macro|UDCICR1
mdefine_line|#define UDCICR1         __REG(0x40600008) /* UDC Interrupt Control Register1 */
DECL|macro|UDCICR_FIFOERR
mdefine_line|#define UDCICR_FIFOERR&t;(1 &lt;&lt; 1)&t;/* FIFO Error interrupt for EP */
DECL|macro|UDCICR_PKTCOMPL
mdefine_line|#define UDCICR_PKTCOMPL (1 &lt;&lt; 0)&t;/* Packet Complete interrupt for EP */
DECL|macro|UDC_INT_FIFOERROR
mdefine_line|#define UDC_INT_FIFOERROR  (0x2)
DECL|macro|UDC_INT_PACKETCMP
mdefine_line|#define UDC_INT_PACKETCMP  (0x1)
DECL|macro|UDCICR_INT
mdefine_line|#define UDCICR_INT(n,intr) (((intr) &amp; 0x03) &lt;&lt; (((n) &amp; 0x0F) * 2))
DECL|macro|UDCICR1_IECC
mdefine_line|#define UDCICR1_IECC&t;(1 &lt;&lt; 31)&t;/* IntEn - Configuration Change */
DECL|macro|UDCICR1_IESOF
mdefine_line|#define UDCICR1_IESOF&t;(1 &lt;&lt; 30)&t;/* IntEn - Start of Frame */
DECL|macro|UDCICR1_IERU
mdefine_line|#define UDCICR1_IERU&t;(1 &lt;&lt; 29)&t;/* IntEn - Resume */
DECL|macro|UDCICR1_IESU
mdefine_line|#define UDCICR1_IESU&t;(1 &lt;&lt; 28)&t;/* IntEn - Suspend */
DECL|macro|UDCICR1_IERS
mdefine_line|#define UDCICR1_IERS&t;(1 &lt;&lt; 27)&t;/* IntEn - Reset */
DECL|macro|UDCISR0
mdefine_line|#define UDCISR0         __REG(0x4060000C) /* UDC Interrupt Status Register 0 */
DECL|macro|UDCISR1
mdefine_line|#define UDCISR1         __REG(0x40600010) /* UDC Interrupt Status Register 1 */
DECL|macro|UDCISR_INT
mdefine_line|#define UDCISR_INT(n,intr) (((intr) &amp; 0x03) &lt;&lt; (((n) &amp; 0x0F) * 2))
DECL|macro|UDCISR1_IECC
mdefine_line|#define UDCISR1_IECC&t;(1 &lt;&lt; 31)&t;/* IntEn - Configuration Change */
DECL|macro|UDCISR1_IESOF
mdefine_line|#define UDCISR1_IESOF&t;(1 &lt;&lt; 30)&t;/* IntEn - Start of Frame */
DECL|macro|UDCISR1_IERU
mdefine_line|#define UDCISR1_IERU&t;(1 &lt;&lt; 29)&t;/* IntEn - Resume */
DECL|macro|UDCISR1_IESU
mdefine_line|#define UDCISR1_IESU&t;(1 &lt;&lt; 28)&t;/* IntEn - Suspend */
DECL|macro|UDCISR1_IERS
mdefine_line|#define UDCISR1_IERS&t;(1 &lt;&lt; 27)&t;/* IntEn - Reset */
DECL|macro|UDCFNR
mdefine_line|#define UDCFNR          __REG(0x40600014) /* UDC Frame Number Register */
DECL|macro|UDCOTGICR
mdefine_line|#define UDCOTGICR&t;__REG(0x40600018) /* UDC On-The-Go interrupt control */
DECL|macro|UDCOTGICR_IESF
mdefine_line|#define UDCOTGICR_IESF&t;(1 &lt;&lt; 24)&t;/* OTG SET_FEATURE command recvd */
DECL|macro|UDCOTGICR_IEXR
mdefine_line|#define UDCOTGICR_IEXR&t;(1 &lt;&lt; 17)&t;/* Extra Transciever Interrupt&n;&t;&t;&t;&t;&t;   Rising Edge Interrupt Enable */
DECL|macro|UDCOTGICR_IEXF
mdefine_line|#define UDCOTGICR_IEXF&t;(1 &lt;&lt; 16)&t;/* Extra Transciever Interrupt&n;&t;&t;&t;&t;&t;   Falling Edge Interrupt Enable */
DECL|macro|UDCOTGICR_IEVV40R
mdefine_line|#define UDCOTGICR_IEVV40R (1 &lt;&lt; 9)&t;/* OTG Vbus Valid 4.0V Rising Edge&n;&t;&t;&t;&t;&t;   Interrupt Enable */
DECL|macro|UDCOTGICR_IEVV40F
mdefine_line|#define UDCOTGICR_IEVV40F (1 &lt;&lt; 8)&t;/* OTG Vbus Valid 4.0V Falling Edge&n;&t;&t;&t;&t;&t;   Interrupt Enable */
DECL|macro|UDCOTGICR_IEVV44R
mdefine_line|#define UDCOTGICR_IEVV44R (1 &lt;&lt; 7)&t;/* OTG Vbus Valid 4.4V Rising Edge&n;&t;&t;&t;&t;&t;   Interrupt Enable */
DECL|macro|UDCOTGICR_IEVV44F
mdefine_line|#define UDCOTGICR_IEVV44F (1 &lt;&lt; 6)&t;/* OTG Vbus Valid 4.4V Falling Edge&n;&t;&t;&t;&t;&t;   Interrupt Enable */
DECL|macro|UDCOTGICR_IESVR
mdefine_line|#define UDCOTGICR_IESVR&t;(1 &lt;&lt; 5)&t;/* OTG Session Valid Rising Edge&n;&t;&t;&t;&t;&t;   Interrupt Enable */
DECL|macro|UDCOTGICR_IESVF
mdefine_line|#define UDCOTGICR_IESVF&t;(1 &lt;&lt; 4)&t;/* OTG Session Valid Falling Edge&n;&t;&t;&t;&t;&t;   Interrupt Enable */
DECL|macro|UDCOTGICR_IESDR
mdefine_line|#define UDCOTGICR_IESDR&t;(1 &lt;&lt; 3)&t;/* OTG A-Device SRP Detect Rising&n;&t;&t;&t;&t;&t;   Edge Interrupt Enable */
DECL|macro|UDCOTGICR_IESDF
mdefine_line|#define UDCOTGICR_IESDF&t;(1 &lt;&lt; 2)&t;/* OTG A-Device SRP Detect Falling&n;&t;&t;&t;&t;&t;   Edge Interrupt Enable */
DECL|macro|UDCOTGICR_IEIDR
mdefine_line|#define UDCOTGICR_IEIDR&t;(1 &lt;&lt; 1)&t;/* OTG ID Change Rising Edge&n;&t;&t;&t;&t;&t;   Interrupt Enable */
DECL|macro|UDCOTGICR_IEIDF
mdefine_line|#define UDCOTGICR_IEIDF&t;(1 &lt;&lt; 0)&t;/* OTG ID Change Falling Edge&n;&t;&t;&t;&t;&t;   Interrupt Enable */
DECL|macro|UDCCSN
mdefine_line|#define UDCCSN(x)&t;__REG2(0x40600100, (x) &lt;&lt; 2)
DECL|macro|UDCCSR0
mdefine_line|#define UDCCSR0         __REG(0x40600100) /* UDC Control/Status register - Endpoint 0 */
DECL|macro|UDCCSR0_SA
mdefine_line|#define UDCCSR0_SA&t;(1 &lt;&lt; 7)&t;/* Setup Active */
DECL|macro|UDCCSR0_RNE
mdefine_line|#define UDCCSR0_RNE&t;(1 &lt;&lt; 6)&t;/* Receive FIFO Not Empty */
DECL|macro|UDCCSR0_FST
mdefine_line|#define UDCCSR0_FST&t;(1 &lt;&lt; 5)&t;/* Force Stall */
DECL|macro|UDCCSR0_SST
mdefine_line|#define UDCCSR0_SST&t;(1 &lt;&lt; 4)&t;/* Sent Stall */
DECL|macro|UDCCSR0_DME
mdefine_line|#define UDCCSR0_DME&t;(1 &lt;&lt; 3)&t;/* DMA Enable */
DECL|macro|UDCCSR0_FTF
mdefine_line|#define UDCCSR0_FTF&t;(1 &lt;&lt; 2)&t;/* Flush Transmit FIFO */
DECL|macro|UDCCSR0_IPR
mdefine_line|#define UDCCSR0_IPR&t;(1 &lt;&lt; 1)&t;/* IN Packet Ready */
DECL|macro|UDCCSR0_OPC
mdefine_line|#define UDCCSR0_OPC&t;(1 &lt;&lt; 0)&t;/* OUT Packet Complete */
DECL|macro|UDCCSRA
mdefine_line|#define UDCCSRA         __REG(0x40600104) /* UDC Control/Status register - Endpoint A */
DECL|macro|UDCCSRB
mdefine_line|#define UDCCSRB         __REG(0x40600108) /* UDC Control/Status register - Endpoint B */
DECL|macro|UDCCSRC
mdefine_line|#define UDCCSRC         __REG(0x4060010C) /* UDC Control/Status register - Endpoint C */
DECL|macro|UDCCSRD
mdefine_line|#define UDCCSRD         __REG(0x40600110) /* UDC Control/Status register - Endpoint D */
DECL|macro|UDCCSRE
mdefine_line|#define UDCCSRE         __REG(0x40600114) /* UDC Control/Status register - Endpoint E */
DECL|macro|UDCCSRF
mdefine_line|#define UDCCSRF         __REG(0x40600118) /* UDC Control/Status register - Endpoint F */
DECL|macro|UDCCSRG
mdefine_line|#define UDCCSRG         __REG(0x4060011C) /* UDC Control/Status register - Endpoint G */
DECL|macro|UDCCSRH
mdefine_line|#define UDCCSRH         __REG(0x40600120) /* UDC Control/Status register - Endpoint H */
DECL|macro|UDCCSRI
mdefine_line|#define UDCCSRI         __REG(0x40600124) /* UDC Control/Status register - Endpoint I */
DECL|macro|UDCCSRJ
mdefine_line|#define UDCCSRJ         __REG(0x40600128) /* UDC Control/Status register - Endpoint J */
DECL|macro|UDCCSRK
mdefine_line|#define UDCCSRK         __REG(0x4060012C) /* UDC Control/Status register - Endpoint K */
DECL|macro|UDCCSRL
mdefine_line|#define UDCCSRL         __REG(0x40600130) /* UDC Control/Status register - Endpoint L */
DECL|macro|UDCCSRM
mdefine_line|#define UDCCSRM         __REG(0x40600134) /* UDC Control/Status register - Endpoint M */
DECL|macro|UDCCSRN
mdefine_line|#define UDCCSRN         __REG(0x40600138) /* UDC Control/Status register - Endpoint N */
DECL|macro|UDCCSRP
mdefine_line|#define UDCCSRP         __REG(0x4060013C) /* UDC Control/Status register - Endpoint P */
DECL|macro|UDCCSRQ
mdefine_line|#define UDCCSRQ         __REG(0x40600140) /* UDC Control/Status register - Endpoint Q */
DECL|macro|UDCCSRR
mdefine_line|#define UDCCSRR         __REG(0x40600144) /* UDC Control/Status register - Endpoint R */
DECL|macro|UDCCSRS
mdefine_line|#define UDCCSRS         __REG(0x40600148) /* UDC Control/Status register - Endpoint S */
DECL|macro|UDCCSRT
mdefine_line|#define UDCCSRT         __REG(0x4060014C) /* UDC Control/Status register - Endpoint T */
DECL|macro|UDCCSRU
mdefine_line|#define UDCCSRU         __REG(0x40600150) /* UDC Control/Status register - Endpoint U */
DECL|macro|UDCCSRV
mdefine_line|#define UDCCSRV         __REG(0x40600154) /* UDC Control/Status register - Endpoint V */
DECL|macro|UDCCSRW
mdefine_line|#define UDCCSRW         __REG(0x40600158) /* UDC Control/Status register - Endpoint W */
DECL|macro|UDCCSRX
mdefine_line|#define UDCCSRX         __REG(0x4060015C) /* UDC Control/Status register - Endpoint X */
DECL|macro|UDCCSR_DPE
mdefine_line|#define UDCCSR_DPE&t;(1 &lt;&lt; 9)&t;/* Data Packet Error */
DECL|macro|UDCCSR_FEF
mdefine_line|#define UDCCSR_FEF&t;(1 &lt;&lt; 8)&t;/* Flush Endpoint FIFO */
DECL|macro|UDCCSR_SP
mdefine_line|#define UDCCSR_SP&t;(1 &lt;&lt; 7)&t;/* Short Packet Control/Status */
DECL|macro|UDCCSR_BNE
mdefine_line|#define UDCCSR_BNE&t;(1 &lt;&lt; 6)&t;/* Buffer Not Empty (IN endpoints) */
DECL|macro|UDCCSR_BNF
mdefine_line|#define UDCCSR_BNF&t;(1 &lt;&lt; 6)&t;/* Buffer Not Full (OUT endpoints) */
DECL|macro|UDCCSR_FST
mdefine_line|#define UDCCSR_FST&t;(1 &lt;&lt; 5)&t;/* Force STALL */
DECL|macro|UDCCSR_SST
mdefine_line|#define UDCCSR_SST&t;(1 &lt;&lt; 4)&t;/* Sent STALL */
DECL|macro|UDCCSR_DME
mdefine_line|#define UDCCSR_DME&t;(1 &lt;&lt; 3)&t;/* DMA Enable */
DECL|macro|UDCCSR_TRN
mdefine_line|#define UDCCSR_TRN&t;(1 &lt;&lt; 2)&t;/* Tx/Rx NAK */
DECL|macro|UDCCSR_PC
mdefine_line|#define UDCCSR_PC&t;(1 &lt;&lt; 1)&t;/* Packet Complete */
DECL|macro|UDCCSR_FS
mdefine_line|#define UDCCSR_FS&t;(1 &lt;&lt; 0)&t;/* FIFO needs service */
DECL|macro|UDCBCN
mdefine_line|#define UDCBCN(x)&t;__REG2(0x40600200, (x)&lt;&lt;2)
DECL|macro|UDCBCR0
mdefine_line|#define UDCBCR0         __REG(0x40600200) /* Byte Count Register - EP0 */
DECL|macro|UDCBCRA
mdefine_line|#define UDCBCRA         __REG(0x40600204) /* Byte Count Register - EPA */
DECL|macro|UDCBCRB
mdefine_line|#define UDCBCRB         __REG(0x40600208) /* Byte Count Register - EPB */
DECL|macro|UDCBCRC
mdefine_line|#define UDCBCRC         __REG(0x4060020C) /* Byte Count Register - EPC */
DECL|macro|UDCBCRD
mdefine_line|#define UDCBCRD         __REG(0x40600210) /* Byte Count Register - EPD */
DECL|macro|UDCBCRE
mdefine_line|#define UDCBCRE         __REG(0x40600214) /* Byte Count Register - EPE */
DECL|macro|UDCBCRF
mdefine_line|#define UDCBCRF         __REG(0x40600218) /* Byte Count Register - EPF */
DECL|macro|UDCBCRG
mdefine_line|#define UDCBCRG         __REG(0x4060021C) /* Byte Count Register - EPG */
DECL|macro|UDCBCRH
mdefine_line|#define UDCBCRH         __REG(0x40600220) /* Byte Count Register - EPH */
DECL|macro|UDCBCRI
mdefine_line|#define UDCBCRI         __REG(0x40600224) /* Byte Count Register - EPI */
DECL|macro|UDCBCRJ
mdefine_line|#define UDCBCRJ         __REG(0x40600228) /* Byte Count Register - EPJ */
DECL|macro|UDCBCRK
mdefine_line|#define UDCBCRK         __REG(0x4060022C) /* Byte Count Register - EPK */
DECL|macro|UDCBCRL
mdefine_line|#define UDCBCRL         __REG(0x40600230) /* Byte Count Register - EPL */
DECL|macro|UDCBCRM
mdefine_line|#define UDCBCRM         __REG(0x40600234) /* Byte Count Register - EPM */
DECL|macro|UDCBCRN
mdefine_line|#define UDCBCRN         __REG(0x40600238) /* Byte Count Register - EPN */
DECL|macro|UDCBCRP
mdefine_line|#define UDCBCRP         __REG(0x4060023C) /* Byte Count Register - EPP */
DECL|macro|UDCBCRQ
mdefine_line|#define UDCBCRQ         __REG(0x40600240) /* Byte Count Register - EPQ */
DECL|macro|UDCBCRR
mdefine_line|#define UDCBCRR         __REG(0x40600244) /* Byte Count Register - EPR */
DECL|macro|UDCBCRS
mdefine_line|#define UDCBCRS         __REG(0x40600248) /* Byte Count Register - EPS */
DECL|macro|UDCBCRT
mdefine_line|#define UDCBCRT         __REG(0x4060024C) /* Byte Count Register - EPT */
DECL|macro|UDCBCRU
mdefine_line|#define UDCBCRU         __REG(0x40600250) /* Byte Count Register - EPU */
DECL|macro|UDCBCRV
mdefine_line|#define UDCBCRV         __REG(0x40600254) /* Byte Count Register - EPV */
DECL|macro|UDCBCRW
mdefine_line|#define UDCBCRW         __REG(0x40600258) /* Byte Count Register - EPW */
DECL|macro|UDCBCRX
mdefine_line|#define UDCBCRX         __REG(0x4060025C) /* Byte Count Register - EPX */
DECL|macro|UDCDN
mdefine_line|#define UDCDN(x)&t;__REG2(0x40600300, (x)&lt;&lt;2)
DECL|macro|PHYS_UDCDN
mdefine_line|#define PHYS_UDCDN(x)&t;(0x40600300 + ((x)&lt;&lt;2))
DECL|macro|PUDCDN
mdefine_line|#define PUDCDN(x)&t;(volatile u32 *)(io_p2v(PHYS_UDCDN((x))))
DECL|macro|UDCDR0
mdefine_line|#define UDCDR0          __REG(0x40600300) /* Data Register - EP0 */
DECL|macro|UDCDRA
mdefine_line|#define UDCDRA          __REG(0x40600304) /* Data Register - EPA */
DECL|macro|UDCDRB
mdefine_line|#define UDCDRB          __REG(0x40600308) /* Data Register - EPB */
DECL|macro|UDCDRC
mdefine_line|#define UDCDRC          __REG(0x4060030C) /* Data Register - EPC */
DECL|macro|UDCDRD
mdefine_line|#define UDCDRD          __REG(0x40600310) /* Data Register - EPD */
DECL|macro|UDCDRE
mdefine_line|#define UDCDRE          __REG(0x40600314) /* Data Register - EPE */
DECL|macro|UDCDRF
mdefine_line|#define UDCDRF          __REG(0x40600318) /* Data Register - EPF */
DECL|macro|UDCDRG
mdefine_line|#define UDCDRG          __REG(0x4060031C) /* Data Register - EPG */
DECL|macro|UDCDRH
mdefine_line|#define UDCDRH          __REG(0x40600320) /* Data Register - EPH */
DECL|macro|UDCDRI
mdefine_line|#define UDCDRI          __REG(0x40600324) /* Data Register - EPI */
DECL|macro|UDCDRJ
mdefine_line|#define UDCDRJ          __REG(0x40600328) /* Data Register - EPJ */
DECL|macro|UDCDRK
mdefine_line|#define UDCDRK          __REG(0x4060032C) /* Data Register - EPK */
DECL|macro|UDCDRL
mdefine_line|#define UDCDRL          __REG(0x40600330) /* Data Register - EPL */
DECL|macro|UDCDRM
mdefine_line|#define UDCDRM          __REG(0x40600334) /* Data Register - EPM */
DECL|macro|UDCDRN
mdefine_line|#define UDCDRN          __REG(0x40600338) /* Data Register - EPN */
DECL|macro|UDCDRP
mdefine_line|#define UDCDRP          __REG(0x4060033C) /* Data Register - EPP */
DECL|macro|UDCDRQ
mdefine_line|#define UDCDRQ          __REG(0x40600340) /* Data Register - EPQ */
DECL|macro|UDCDRR
mdefine_line|#define UDCDRR          __REG(0x40600344) /* Data Register - EPR */
DECL|macro|UDCDRS
mdefine_line|#define UDCDRS          __REG(0x40600348) /* Data Register - EPS */
DECL|macro|UDCDRT
mdefine_line|#define UDCDRT          __REG(0x4060034C) /* Data Register - EPT */
DECL|macro|UDCDRU
mdefine_line|#define UDCDRU          __REG(0x40600350) /* Data Register - EPU */
DECL|macro|UDCDRV
mdefine_line|#define UDCDRV          __REG(0x40600354) /* Data Register - EPV */
DECL|macro|UDCDRW
mdefine_line|#define UDCDRW          __REG(0x40600358) /* Data Register - EPW */
DECL|macro|UDCDRX
mdefine_line|#define UDCDRX          __REG(0x4060035C) /* Data Register - EPX */
DECL|macro|UDCCN
mdefine_line|#define UDCCN(x)       __REG2(0x40600400, (x)&lt;&lt;2)
DECL|macro|UDCCRA
mdefine_line|#define UDCCRA          __REG(0x40600404) /* Configuration register EPA */
DECL|macro|UDCCRB
mdefine_line|#define UDCCRB          __REG(0x40600408) /* Configuration register EPB */
DECL|macro|UDCCRC
mdefine_line|#define UDCCRC          __REG(0x4060040C) /* Configuration register EPC */
DECL|macro|UDCCRD
mdefine_line|#define UDCCRD          __REG(0x40600410) /* Configuration register EPD */
DECL|macro|UDCCRE
mdefine_line|#define UDCCRE          __REG(0x40600414) /* Configuration register EPE */
DECL|macro|UDCCRF
mdefine_line|#define UDCCRF          __REG(0x40600418) /* Configuration register EPF */
DECL|macro|UDCCRG
mdefine_line|#define UDCCRG          __REG(0x4060041C) /* Configuration register EPG */
DECL|macro|UDCCRH
mdefine_line|#define UDCCRH          __REG(0x40600420) /* Configuration register EPH */
DECL|macro|UDCCRI
mdefine_line|#define UDCCRI          __REG(0x40600424) /* Configuration register EPI */
DECL|macro|UDCCRJ
mdefine_line|#define UDCCRJ          __REG(0x40600428) /* Configuration register EPJ */
DECL|macro|UDCCRK
mdefine_line|#define UDCCRK          __REG(0x4060042C) /* Configuration register EPK */
DECL|macro|UDCCRL
mdefine_line|#define UDCCRL          __REG(0x40600430) /* Configuration register EPL */
DECL|macro|UDCCRM
mdefine_line|#define UDCCRM          __REG(0x40600434) /* Configuration register EPM */
DECL|macro|UDCCRN
mdefine_line|#define UDCCRN          __REG(0x40600438) /* Configuration register EPN */
DECL|macro|UDCCRP
mdefine_line|#define UDCCRP          __REG(0x4060043C) /* Configuration register EPP */
DECL|macro|UDCCRQ
mdefine_line|#define UDCCRQ          __REG(0x40600440) /* Configuration register EPQ */
DECL|macro|UDCCRR
mdefine_line|#define UDCCRR          __REG(0x40600444) /* Configuration register EPR */
DECL|macro|UDCCRS
mdefine_line|#define UDCCRS          __REG(0x40600448) /* Configuration register EPS */
DECL|macro|UDCCRT
mdefine_line|#define UDCCRT          __REG(0x4060044C) /* Configuration register EPT */
DECL|macro|UDCCRU
mdefine_line|#define UDCCRU          __REG(0x40600450) /* Configuration register EPU */
DECL|macro|UDCCRV
mdefine_line|#define UDCCRV          __REG(0x40600454) /* Configuration register EPV */
DECL|macro|UDCCRW
mdefine_line|#define UDCCRW          __REG(0x40600458) /* Configuration register EPW */
DECL|macro|UDCCRX
mdefine_line|#define UDCCRX          __REG(0x4060045C) /* Configuration register EPX */
DECL|macro|UDCCONR_CN
mdefine_line|#define UDCCONR_CN&t;(0x03 &lt;&lt; 25)&t;/* Configuration Number */
DECL|macro|UDCCONR_CN_S
mdefine_line|#define UDCCONR_CN_S&t;(25)
DECL|macro|UDCCONR_IN
mdefine_line|#define UDCCONR_IN&t;(0x07 &lt;&lt; 22)&t;/* Interface Number */
DECL|macro|UDCCONR_IN_S
mdefine_line|#define UDCCONR_IN_S&t;(22)
DECL|macro|UDCCONR_AISN
mdefine_line|#define UDCCONR_AISN&t;(0x07 &lt;&lt; 19)&t;/* Alternate Interface Number */
DECL|macro|UDCCONR_AISN_S
mdefine_line|#define UDCCONR_AISN_S&t;(19)
DECL|macro|UDCCONR_EN
mdefine_line|#define UDCCONR_EN&t;(0x0f &lt;&lt; 15)&t;/* Endpoint Number */
DECL|macro|UDCCONR_EN_S
mdefine_line|#define UDCCONR_EN_S&t;(15)
DECL|macro|UDCCONR_ET
mdefine_line|#define UDCCONR_ET&t;(0x03 &lt;&lt; 13)&t;/* Endpoint Type: */
DECL|macro|UDCCONR_ET_S
mdefine_line|#define UDCCONR_ET_S&t;(13)
DECL|macro|UDCCONR_ET_INT
mdefine_line|#define UDCCONR_ET_INT&t;(0x03 &lt;&lt; 13)&t;/*   Interrupt */
DECL|macro|UDCCONR_ET_BULK
mdefine_line|#define UDCCONR_ET_BULK&t;(0x02 &lt;&lt; 13)&t;/*   Bulk */
DECL|macro|UDCCONR_ET_ISO
mdefine_line|#define UDCCONR_ET_ISO&t;(0x01 &lt;&lt; 13)&t;/*   Isochronous */
DECL|macro|UDCCONR_ET_NU
mdefine_line|#define UDCCONR_ET_NU&t;(0x00 &lt;&lt; 13)&t;/*   Not used */
DECL|macro|UDCCONR_ED
mdefine_line|#define UDCCONR_ED&t;(1 &lt;&lt; 12)&t;/* Endpoint Direction */
DECL|macro|UDCCONR_MPS
mdefine_line|#define UDCCONR_MPS&t;(0x3ff &lt;&lt; 2)&t;/* Maximum Packet Size */
DECL|macro|UDCCONR_MPS_S
mdefine_line|#define UDCCONR_MPS_S&t;(2)
DECL|macro|UDCCONR_DE
mdefine_line|#define UDCCONR_DE&t;(1 &lt;&lt; 1)&t;/* Double Buffering Enable */
DECL|macro|UDCCONR_EE
mdefine_line|#define UDCCONR_EE&t;(1 &lt;&lt; 0)&t;/* Endpoint Enable */
DECL|macro|UDC_INT_FIFOERROR
mdefine_line|#define UDC_INT_FIFOERROR  (0x2)
DECL|macro|UDC_INT_PACKETCMP
mdefine_line|#define UDC_INT_PACKETCMP  (0x1)
DECL|macro|UDC_FNR_MASK
mdefine_line|#define UDC_FNR_MASK     (0x7ff)
DECL|macro|UDCCSR_WR_MASK
mdefine_line|#define UDCCSR_WR_MASK   (UDCCSR_DME|UDCCSR_FST)
DECL|macro|UDC_BCR_MASK
mdefine_line|#define UDC_BCR_MASK    (0x3ff)
macro_line|#endif
multiline_comment|/*&n; * Fast Infrared Communication Port&n; */
DECL|macro|FICP
mdefine_line|#define FICP&t;&t;__REG(0x40800000)  /* Start of FICP area */
DECL|macro|ICCR0
mdefine_line|#define ICCR0&t;&t;__REG(0x40800000)  /* ICP Control Register 0 */
DECL|macro|ICCR1
mdefine_line|#define ICCR1&t;&t;__REG(0x40800004)  /* ICP Control Register 1 */
DECL|macro|ICCR2
mdefine_line|#define ICCR2&t;&t;__REG(0x40800008)  /* ICP Control Register 2 */
DECL|macro|ICDR
mdefine_line|#define ICDR&t;&t;__REG(0x4080000c)  /* ICP Data Register */
DECL|macro|ICSR0
mdefine_line|#define ICSR0&t;&t;__REG(0x40800014)  /* ICP Status Register 0 */
DECL|macro|ICSR1
mdefine_line|#define ICSR1&t;&t;__REG(0x40800018)  /* ICP Status Register 1 */
DECL|macro|ICCR0_AME
mdefine_line|#define ICCR0_AME&t;(1 &lt;&lt; 7)&t;/* Adress match enable */
DECL|macro|ICCR0_TIE
mdefine_line|#define ICCR0_TIE&t;(1 &lt;&lt; 6)&t;/* Transmit FIFO interrupt enable */
DECL|macro|ICCR0_RIE
mdefine_line|#define ICCR0_RIE&t;(1 &lt;&lt; 5)&t;/* Recieve FIFO interrupt enable */
DECL|macro|ICCR0_RXE
mdefine_line|#define ICCR0_RXE&t;(1 &lt;&lt; 4)&t;/* Receive enable */
DECL|macro|ICCR0_TXE
mdefine_line|#define ICCR0_TXE&t;(1 &lt;&lt; 3)&t;/* Transmit enable */
DECL|macro|ICCR0_TUS
mdefine_line|#define ICCR0_TUS&t;(1 &lt;&lt; 2)&t;/* Transmit FIFO underrun select */
DECL|macro|ICCR0_LBM
mdefine_line|#define ICCR0_LBM&t;(1 &lt;&lt; 1)&t;/* Loopback mode */
DECL|macro|ICCR0_ITR
mdefine_line|#define ICCR0_ITR&t;(1 &lt;&lt; 0)&t;/* IrDA transmission */
macro_line|#ifdef CONFIG_PXA27x
DECL|macro|ICCR2_RXP
mdefine_line|#define ICCR2_RXP       (1 &lt;&lt; 3)&t;/* Receive Pin Polarity select */
DECL|macro|ICCR2_TXP
mdefine_line|#define ICCR2_TXP       (1 &lt;&lt; 2)&t;/* Transmit Pin Polarity select */
DECL|macro|ICCR2_TRIG
mdefine_line|#define ICCR2_TRIG&t;(3 &lt;&lt; 0)&t;/* Receive FIFO Trigger threshold */
DECL|macro|ICCR2_TRIG_8
mdefine_line|#define ICCR2_TRIG_8    (0 &lt;&lt; 0)&t;/* &t;&gt;= 8 bytes */
DECL|macro|ICCR2_TRIG_16
mdefine_line|#define ICCR2_TRIG_16   (1 &lt;&lt; 0)&t;/*&t;&gt;= 16 bytes */
DECL|macro|ICCR2_TRIG_32
mdefine_line|#define ICCR2_TRIG_32   (2 &lt;&lt; 0)&t;/*&t;&gt;= 32 bytes */
macro_line|#endif
macro_line|#ifdef CONFIG_PXA27x
DECL|macro|ICSR0_EOC
mdefine_line|#define ICSR0_EOC&t;(1 &lt;&lt; 6)&t;/* DMA End of Descriptor Chain */
macro_line|#endif
DECL|macro|ICSR0_FRE
mdefine_line|#define ICSR0_FRE&t;(1 &lt;&lt; 5)&t;/* Framing error */
DECL|macro|ICSR0_RFS
mdefine_line|#define ICSR0_RFS&t;(1 &lt;&lt; 4)&t;/* Receive FIFO service request */
DECL|macro|ICSR0_TFS
mdefine_line|#define ICSR0_TFS&t;(1 &lt;&lt; 3)&t;/* Transnit FIFO service request */
DECL|macro|ICSR0_RAB
mdefine_line|#define ICSR0_RAB&t;(1 &lt;&lt; 2)&t;/* Receiver abort */
DECL|macro|ICSR0_TUR
mdefine_line|#define ICSR0_TUR&t;(1 &lt;&lt; 1)&t;/* Trunsmit FIFO underun */
DECL|macro|ICSR0_EIF
mdefine_line|#define ICSR0_EIF&t;(1 &lt;&lt; 0)&t;/* End/Error in FIFO */
DECL|macro|ICSR1_ROR
mdefine_line|#define ICSR1_ROR&t;(1 &lt;&lt; 6)&t;/* Receiver FIFO underrun  */
DECL|macro|ICSR1_CRE
mdefine_line|#define ICSR1_CRE&t;(1 &lt;&lt; 5)&t;/* CRC error */
DECL|macro|ICSR1_EOF
mdefine_line|#define ICSR1_EOF&t;(1 &lt;&lt; 4)&t;/* End of frame */
DECL|macro|ICSR1_TNF
mdefine_line|#define ICSR1_TNF&t;(1 &lt;&lt; 3)&t;/* Transmit FIFO not full */
DECL|macro|ICSR1_RNE
mdefine_line|#define ICSR1_RNE&t;(1 &lt;&lt; 2)&t;/* Receive FIFO not empty */
DECL|macro|ICSR1_TBY
mdefine_line|#define ICSR1_TBY&t;(1 &lt;&lt; 1)&t;/* Tramsmiter busy flag */
DECL|macro|ICSR1_RSY
mdefine_line|#define ICSR1_RSY&t;(1 &lt;&lt; 0)&t;/* Recevier synchronized flag */
multiline_comment|/*&n; * Real Time Clock&n; */
DECL|macro|RCNR
mdefine_line|#define RCNR&t;&t;__REG(0x40900000)  /* RTC Count Register */
DECL|macro|RTAR
mdefine_line|#define RTAR&t;&t;__REG(0x40900004)  /* RTC Alarm Register */
DECL|macro|RTSR
mdefine_line|#define RTSR&t;&t;__REG(0x40900008)  /* RTC Status Register */
DECL|macro|RTTR
mdefine_line|#define RTTR&t;&t;__REG(0x4090000C)  /* RTC Timer Trim Register */
DECL|macro|PIAR
mdefine_line|#define PIAR&t;&t;__REG(0x40900038)  /* Periodic Interrupt Alarm Register */
DECL|macro|RTSR_PICE
mdefine_line|#define RTSR_PICE&t;(1 &lt;&lt; 15)&t;/* Periodic interrupt count enable */
DECL|macro|RTSR_PIALE
mdefine_line|#define RTSR_PIALE&t;(1 &lt;&lt; 14)&t;/* Periodic interrupt Alarm enable */
DECL|macro|RTSR_HZE
mdefine_line|#define RTSR_HZE&t;(1 &lt;&lt; 3)&t;/* HZ interrupt enable */
DECL|macro|RTSR_ALE
mdefine_line|#define RTSR_ALE&t;(1 &lt;&lt; 2)&t;/* RTC alarm interrupt enable */
DECL|macro|RTSR_HZ
mdefine_line|#define RTSR_HZ&t;&t;(1 &lt;&lt; 1)&t;/* HZ rising-edge detected */
DECL|macro|RTSR_AL
mdefine_line|#define RTSR_AL&t;&t;(1 &lt;&lt; 0)&t;/* RTC alarm detected */
multiline_comment|/*&n; * OS Timer &amp; Match Registers&n; */
DECL|macro|OSMR0
mdefine_line|#define OSMR0&t;&t;__REG(0x40A00000)  /* */
DECL|macro|OSMR1
mdefine_line|#define OSMR1&t;&t;__REG(0x40A00004)  /* */
DECL|macro|OSMR2
mdefine_line|#define OSMR2&t;&t;__REG(0x40A00008)  /* */
DECL|macro|OSMR3
mdefine_line|#define OSMR3&t;&t;__REG(0x40A0000C)  /* */
DECL|macro|OSMR4
mdefine_line|#define OSMR4&t;&t;__REG(0x40A00080)  /* */
DECL|macro|OSCR
mdefine_line|#define OSCR&t;&t;__REG(0x40A00010)  /* OS Timer Counter Register */
DECL|macro|OSCR4
mdefine_line|#define OSCR4&t;&t;__REG(0x40A00040)  /* OS Timer Counter Register */
DECL|macro|OMCR4
mdefine_line|#define OMCR4&t;&t;__REG(0x40A000C0)  /* */
DECL|macro|OSSR
mdefine_line|#define OSSR&t;&t;__REG(0x40A00014)  /* OS Timer Status Register */
DECL|macro|OWER
mdefine_line|#define OWER&t;&t;__REG(0x40A00018)  /* OS Timer Watchdog Enable Register */
DECL|macro|OIER
mdefine_line|#define OIER&t;&t;__REG(0x40A0001C)  /* OS Timer Interrupt Enable Register */
DECL|macro|OSSR_M3
mdefine_line|#define OSSR_M3&t;&t;(1 &lt;&lt; 3)&t;/* Match status channel 3 */
DECL|macro|OSSR_M2
mdefine_line|#define OSSR_M2&t;&t;(1 &lt;&lt; 2)&t;/* Match status channel 2 */
DECL|macro|OSSR_M1
mdefine_line|#define OSSR_M1&t;&t;(1 &lt;&lt; 1)&t;/* Match status channel 1 */
DECL|macro|OSSR_M0
mdefine_line|#define OSSR_M0&t;&t;(1 &lt;&lt; 0)&t;/* Match status channel 0 */
DECL|macro|OWER_WME
mdefine_line|#define OWER_WME&t;(1 &lt;&lt; 0)&t;/* Watchdog Match Enable */
DECL|macro|OIER_E3
mdefine_line|#define OIER_E3&t;&t;(1 &lt;&lt; 3)&t;/* Interrupt enable channel 3 */
DECL|macro|OIER_E2
mdefine_line|#define OIER_E2&t;&t;(1 &lt;&lt; 2)&t;/* Interrupt enable channel 2 */
DECL|macro|OIER_E1
mdefine_line|#define OIER_E1&t;&t;(1 &lt;&lt; 1)&t;/* Interrupt enable channel 1 */
DECL|macro|OIER_E0
mdefine_line|#define OIER_E0&t;&t;(1 &lt;&lt; 0)&t;/* Interrupt enable channel 0 */
multiline_comment|/*&n; * Pulse Width Modulator&n; */
DECL|macro|PWM_CTRL0
mdefine_line|#define PWM_CTRL0&t;__REG(0x40B00000)  /* PWM 0 Control Register */
DECL|macro|PWM_PWDUTY0
mdefine_line|#define PWM_PWDUTY0&t;__REG(0x40B00004)  /* PWM 0 Duty Cycle Register */
DECL|macro|PWM_PERVAL0
mdefine_line|#define PWM_PERVAL0&t;__REG(0x40B00008)  /* PWM 0 Period Control Register */
DECL|macro|PWM_CTRL1
mdefine_line|#define PWM_CTRL1&t;__REG(0x40C00000)  /* PWM 1Control Register */
DECL|macro|PWM_PWDUTY1
mdefine_line|#define PWM_PWDUTY1&t;__REG(0x40C00004)  /* PWM 1 Duty Cycle Register */
DECL|macro|PWM_PERVAL1
mdefine_line|#define PWM_PERVAL1&t;__REG(0x40C00008)  /* PWM 1 Period Control Register */
multiline_comment|/*&n; * Interrupt Controller&n; */
DECL|macro|ICIP
mdefine_line|#define ICIP&t;&t;__REG(0x40D00000)  /* Interrupt Controller IRQ Pending Register */
DECL|macro|ICMR
mdefine_line|#define ICMR&t;&t;__REG(0x40D00004)  /* Interrupt Controller Mask Register */
DECL|macro|ICLR
mdefine_line|#define ICLR&t;&t;__REG(0x40D00008)  /* Interrupt Controller Level Register */
DECL|macro|ICFP
mdefine_line|#define ICFP&t;&t;__REG(0x40D0000C)  /* Interrupt Controller FIQ Pending Register */
DECL|macro|ICPR
mdefine_line|#define ICPR&t;&t;__REG(0x40D00010)  /* Interrupt Controller Pending Register */
DECL|macro|ICCR
mdefine_line|#define ICCR&t;&t;__REG(0x40D00014)  /* Interrupt Controller Control Register */
multiline_comment|/*&n; * General Purpose I/O&n; */
DECL|macro|GPLR0
mdefine_line|#define GPLR0&t;&t;__REG(0x40E00000)  /* GPIO Pin-Level Register GPIO&lt;31:0&gt; */
DECL|macro|GPLR1
mdefine_line|#define GPLR1&t;&t;__REG(0x40E00004)  /* GPIO Pin-Level Register GPIO&lt;63:32&gt; */
DECL|macro|GPLR2
mdefine_line|#define GPLR2&t;&t;__REG(0x40E00008)  /* GPIO Pin-Level Register GPIO&lt;80:64&gt; */
DECL|macro|GPDR0
mdefine_line|#define GPDR0&t;&t;__REG(0x40E0000C)  /* GPIO Pin Direction Register GPIO&lt;31:0&gt; */
DECL|macro|GPDR1
mdefine_line|#define GPDR1&t;&t;__REG(0x40E00010)  /* GPIO Pin Direction Register GPIO&lt;63:32&gt; */
DECL|macro|GPDR2
mdefine_line|#define GPDR2&t;&t;__REG(0x40E00014)  /* GPIO Pin Direction Register GPIO&lt;80:64&gt; */
DECL|macro|GPSR0
mdefine_line|#define GPSR0&t;&t;__REG(0x40E00018)  /* GPIO Pin Output Set Register GPIO&lt;31:0&gt; */
DECL|macro|GPSR1
mdefine_line|#define GPSR1&t;&t;__REG(0x40E0001C)  /* GPIO Pin Output Set Register GPIO&lt;63:32&gt; */
DECL|macro|GPSR2
mdefine_line|#define GPSR2&t;&t;__REG(0x40E00020)  /* GPIO Pin Output Set Register GPIO&lt;80:64&gt; */
DECL|macro|GPCR0
mdefine_line|#define GPCR0&t;&t;__REG(0x40E00024)  /* GPIO Pin Output Clear Register GPIO&lt;31:0&gt; */
DECL|macro|GPCR1
mdefine_line|#define GPCR1&t;&t;__REG(0x40E00028)  /* GPIO Pin Output Clear Register GPIO &lt;63:32&gt; */
DECL|macro|GPCR2
mdefine_line|#define GPCR2&t;&t;__REG(0x40E0002C)  /* GPIO Pin Output Clear Register GPIO &lt;80:64&gt; */
DECL|macro|GRER0
mdefine_line|#define GRER0&t;&t;__REG(0x40E00030)  /* GPIO Rising-Edge Detect Register GPIO&lt;31:0&gt; */
DECL|macro|GRER1
mdefine_line|#define GRER1&t;&t;__REG(0x40E00034)  /* GPIO Rising-Edge Detect Register GPIO&lt;63:32&gt; */
DECL|macro|GRER2
mdefine_line|#define GRER2&t;&t;__REG(0x40E00038)  /* GPIO Rising-Edge Detect Register GPIO&lt;80:64&gt; */
DECL|macro|GFER0
mdefine_line|#define GFER0&t;&t;__REG(0x40E0003C)  /* GPIO Falling-Edge Detect Register GPIO&lt;31:0&gt; */
DECL|macro|GFER1
mdefine_line|#define GFER1&t;&t;__REG(0x40E00040)  /* GPIO Falling-Edge Detect Register GPIO&lt;63:32&gt; */
DECL|macro|GFER2
mdefine_line|#define GFER2&t;&t;__REG(0x40E00044)  /* GPIO Falling-Edge Detect Register GPIO&lt;80:64&gt; */
DECL|macro|GEDR0
mdefine_line|#define GEDR0&t;&t;__REG(0x40E00048)  /* GPIO Edge Detect Status Register GPIO&lt;31:0&gt; */
DECL|macro|GEDR1
mdefine_line|#define GEDR1&t;&t;__REG(0x40E0004C)  /* GPIO Edge Detect Status Register GPIO&lt;63:32&gt; */
DECL|macro|GEDR2
mdefine_line|#define GEDR2&t;&t;__REG(0x40E00050)  /* GPIO Edge Detect Status Register GPIO&lt;80:64&gt; */
DECL|macro|GAFR0_L
mdefine_line|#define GAFR0_L&t;&t;__REG(0x40E00054)  /* GPIO Alternate Function Select Register GPIO&lt;15:0&gt; */
DECL|macro|GAFR0_U
mdefine_line|#define GAFR0_U&t;&t;__REG(0x40E00058)  /* GPIO Alternate Function Select Register GPIO&lt;31:16&gt; */
DECL|macro|GAFR1_L
mdefine_line|#define GAFR1_L&t;&t;__REG(0x40E0005C)  /* GPIO Alternate Function Select Register GPIO&lt;47:32&gt; */
DECL|macro|GAFR1_U
mdefine_line|#define GAFR1_U&t;&t;__REG(0x40E00060)  /* GPIO Alternate Function Select Register GPIO&lt;63:48&gt; */
DECL|macro|GAFR2_L
mdefine_line|#define GAFR2_L&t;&t;__REG(0x40E00064)  /* GPIO Alternate Function Select Register GPIO&lt;79:64&gt; */
DECL|macro|GAFR2_U
mdefine_line|#define GAFR2_U&t;&t;__REG(0x40E00068)  /* GPIO Alternate Function Select Register GPIO&lt;95-80&gt; */
DECL|macro|GAFR3_L
mdefine_line|#define GAFR3_L&t;&t;__REG(0x40E0006C)  /* GPIO Alternate Function Select Register GPIO&lt;111:96&gt; */
DECL|macro|GAFR3_U
mdefine_line|#define GAFR3_U&t;&t;__REG(0x40E00070)  /* GPIO Alternate Function Select Register GPIO&lt;127:112&gt; */
DECL|macro|GPLR3
mdefine_line|#define GPLR3&t;&t;__REG(0x40E00100)  /* GPIO Pin-Level Register GPIO&lt;127:96&gt; */
DECL|macro|GPDR3
mdefine_line|#define GPDR3&t;&t;__REG(0x40E0010C)  /* GPIO Pin Direction Register GPIO&lt;127:96&gt; */
DECL|macro|GPSR3
mdefine_line|#define GPSR3&t;&t;__REG(0x40E00118)  /* GPIO Pin Output Set Register GPIO&lt;127:96&gt; */
DECL|macro|GPCR3
mdefine_line|#define GPCR3&t;&t;__REG(0x40E00124)  /* GPIO Pin Output Clear Register GPIO&lt;127:96&gt; */
DECL|macro|GRER3
mdefine_line|#define GRER3&t;&t;__REG(0x40E00130)  /* GPIO Rising-Edge Detect Register GPIO&lt;127:96&gt; */
DECL|macro|GFER3
mdefine_line|#define GFER3&t;&t;__REG(0x40E0013C)  /* GPIO Falling-Edge Detect Register GPIO&lt;127:96&gt; */
DECL|macro|GEDR3
mdefine_line|#define GEDR3&t;&t;__REG(0x40E00148)  /* GPIO Edge Detect Status Register GPIO&lt;127:96&gt; */
multiline_comment|/* More handy macros.  The argument is a literal GPIO number. */
DECL|macro|GPIO_bit
mdefine_line|#define GPIO_bit(x)&t;(1 &lt;&lt; ((x) &amp; 0x1f))
macro_line|#ifdef CONFIG_PXA27x
multiline_comment|/* Interrupt Controller */
DECL|macro|ICIP2
mdefine_line|#define ICIP2&t;&t;__REG(0x40D0009C)  /* Interrupt Controller IRQ Pending Register 2 */
DECL|macro|ICMR2
mdefine_line|#define ICMR2&t;&t;__REG(0x40D000A0)  /* Interrupt Controller Mask Register 2 */
DECL|macro|ICLR2
mdefine_line|#define ICLR2&t;&t;__REG(0x40D000A4)  /* Interrupt Controller Level Register 2 */
DECL|macro|ICFP2
mdefine_line|#define ICFP2&t;&t;__REG(0x40D000A8)  /* Interrupt Controller FIQ Pending Register 2 */
DECL|macro|ICPR2
mdefine_line|#define ICPR2&t;&t;__REG(0x40D000AC)  /* Interrupt Controller Pending Register 2 */
DECL|macro|_GPLR
mdefine_line|#define _GPLR(x)&t;__REG2(0x40E00000, ((x) &amp; 0x60) &gt;&gt; 3)
DECL|macro|_GPDR
mdefine_line|#define _GPDR(x)&t;__REG2(0x40E0000C, ((x) &amp; 0x60) &gt;&gt; 3)
DECL|macro|_GPSR
mdefine_line|#define _GPSR(x)&t;__REG2(0x40E00018, ((x) &amp; 0x60) &gt;&gt; 3)
DECL|macro|_GPCR
mdefine_line|#define _GPCR(x)&t;__REG2(0x40E00024, ((x) &amp; 0x60) &gt;&gt; 3)
DECL|macro|_GRER
mdefine_line|#define _GRER(x)&t;__REG2(0x40E00030, ((x) &amp; 0x60) &gt;&gt; 3)
DECL|macro|_GFER
mdefine_line|#define _GFER(x)&t;__REG2(0x40E0003C, ((x) &amp; 0x60) &gt;&gt; 3)
DECL|macro|_GEDR
mdefine_line|#define _GEDR(x)&t;__REG2(0x40E00048, ((x) &amp; 0x60) &gt;&gt; 3)
DECL|macro|_GAFR
mdefine_line|#define _GAFR(x)&t;__REG2(0x40E00054, ((x) &amp; 0x70) &gt;&gt; 2)
DECL|macro|GPLR
mdefine_line|#define GPLR(x) &t;(*((((x) &amp; 0x7f) &lt; 96) ? &amp;_GPLR(x) : &amp;GPLR3))
DECL|macro|GPDR
mdefine_line|#define GPDR(x)&t;&t;(*((((x) &amp; 0x7f) &lt; 96) ? &amp;_GPDR(x) : &amp;GPDR3))
DECL|macro|GPSR
mdefine_line|#define GPSR(x)&t;&t;(*((((x) &amp; 0x7f) &lt; 96) ? &amp;_GPSR(x) : &amp;GPSR3))
DECL|macro|GPCR
mdefine_line|#define GPCR(x)&t;&t;(*((((x) &amp; 0x7f) &lt; 96) ? &amp;_GPCR(x) : &amp;GPCR3))
DECL|macro|GRER
mdefine_line|#define GRER(x)&t;&t;(*((((x) &amp; 0x7f) &lt; 96) ? &amp;_GRER(x) : &amp;GRER3))
DECL|macro|GFER
mdefine_line|#define GFER(x)&t;&t;(*((((x) &amp; 0x7f) &lt; 96) ? &amp;_GFER(x) : &amp;GFER3))
DECL|macro|GEDR
mdefine_line|#define GEDR(x)&t;&t;(*((((x) &amp; 0x7f) &lt; 96) ? &amp;_GEDR(x) : &amp;GEDR3))
DECL|macro|GAFR
mdefine_line|#define GAFR(x)&t;&t;(*((((x) &amp; 0x7f) &lt; 96) ? &amp;_GAFR(x) : &bslash;&n;&t;&t;&t; ((((x) &amp; 0x7f) &lt; 112) ? &amp;GAFR3_L : &amp;GAFR3_U)))
macro_line|#else
DECL|macro|GPLR
mdefine_line|#define GPLR(x)&t;&t;__REG2(0x40E00000, ((x) &amp; 0x60) &gt;&gt; 3)
DECL|macro|GPDR
mdefine_line|#define GPDR(x)&t;&t;__REG2(0x40E0000C, ((x) &amp; 0x60) &gt;&gt; 3)
DECL|macro|GPSR
mdefine_line|#define GPSR(x)&t;&t;__REG2(0x40E00018, ((x) &amp; 0x60) &gt;&gt; 3)
DECL|macro|GPCR
mdefine_line|#define GPCR(x)&t;&t;__REG2(0x40E00024, ((x) &amp; 0x60) &gt;&gt; 3)
DECL|macro|GRER
mdefine_line|#define GRER(x)&t;&t;__REG2(0x40E00030, ((x) &amp; 0x60) &gt;&gt; 3)
DECL|macro|GFER
mdefine_line|#define GFER(x)&t;&t;__REG2(0x40E0003C, ((x) &amp; 0x60) &gt;&gt; 3)
DECL|macro|GEDR
mdefine_line|#define GEDR(x)&t;&t;__REG2(0x40E00048, ((x) &amp; 0x60) &gt;&gt; 3)
DECL|macro|GAFR
mdefine_line|#define GAFR(x)&t;&t;__REG2(0x40E00054, ((x) &amp; 0x70) &gt;&gt; 2)
macro_line|#endif
multiline_comment|/* GPIO alternate function assignments */
DECL|macro|GPIO1_RST
mdefine_line|#define GPIO1_RST&t;&t;1&t;/* reset */
DECL|macro|GPIO6_MMCCLK
mdefine_line|#define GPIO6_MMCCLK&t;&t;6&t;/* MMC Clock */
DECL|macro|GPIO7_48MHz
mdefine_line|#define GPIO7_48MHz&t;&t;7&t;/* 48 MHz clock output */
DECL|macro|GPIO8_MMCCS0
mdefine_line|#define GPIO8_MMCCS0&t;&t;8&t;/* MMC Chip Select 0 */
DECL|macro|GPIO9_MMCCS1
mdefine_line|#define GPIO9_MMCCS1&t;&t;9&t;/* MMC Chip Select 1 */
DECL|macro|GPIO10_RTCCLK
mdefine_line|#define GPIO10_RTCCLK&t;&t;10&t;/* real time clock (1 Hz) */
DECL|macro|GPIO11_3_6MHz
mdefine_line|#define GPIO11_3_6MHz&t;&t;11&t;/* 3.6 MHz oscillator out */
DECL|macro|GPIO12_32KHz
mdefine_line|#define GPIO12_32KHz&t;&t;12&t;/* 32 kHz out */
DECL|macro|GPIO13_MBGNT
mdefine_line|#define GPIO13_MBGNT&t;&t;13&t;/* memory controller grant */
DECL|macro|GPIO14_MBREQ
mdefine_line|#define GPIO14_MBREQ&t;&t;14&t;/* alternate bus master request */
DECL|macro|GPIO15_nCS_1
mdefine_line|#define GPIO15_nCS_1&t;&t;15&t;/* chip select 1 */
DECL|macro|GPIO16_PWM0
mdefine_line|#define GPIO16_PWM0&t;&t;16&t;/* PWM0 output */
DECL|macro|GPIO17_PWM1
mdefine_line|#define GPIO17_PWM1&t;&t;17&t;/* PWM1 output */
DECL|macro|GPIO18_RDY
mdefine_line|#define GPIO18_RDY&t;&t;18&t;/* Ext. Bus Ready */
DECL|macro|GPIO19_DREQ1
mdefine_line|#define GPIO19_DREQ1&t;&t;19&t;/* External DMA Request */
DECL|macro|GPIO20_DREQ0
mdefine_line|#define GPIO20_DREQ0&t;&t;20&t;/* External DMA Request */
DECL|macro|GPIO23_SCLK
mdefine_line|#define GPIO23_SCLK&t;&t;23&t;/* SSP clock */
DECL|macro|GPIO24_SFRM
mdefine_line|#define GPIO24_SFRM&t;&t;24&t;/* SSP Frame */
DECL|macro|GPIO25_STXD
mdefine_line|#define GPIO25_STXD&t;&t;25&t;/* SSP transmit */
DECL|macro|GPIO26_SRXD
mdefine_line|#define GPIO26_SRXD&t;&t;26&t;/* SSP receive */
DECL|macro|GPIO27_SEXTCLK
mdefine_line|#define GPIO27_SEXTCLK&t;&t;27&t;/* SSP ext_clk */
DECL|macro|GPIO28_BITCLK
mdefine_line|#define GPIO28_BITCLK&t;&t;28&t;/* AC97/I2S bit_clk */
DECL|macro|GPIO29_SDATA_IN
mdefine_line|#define GPIO29_SDATA_IN&t;&t;29&t;/* AC97 Sdata_in0 / I2S Sdata_in */
DECL|macro|GPIO30_SDATA_OUT
mdefine_line|#define GPIO30_SDATA_OUT&t;30&t;/* AC97/I2S Sdata_out */
DECL|macro|GPIO31_SYNC
mdefine_line|#define GPIO31_SYNC&t;&t;31&t;/* AC97/I2S sync */
DECL|macro|GPIO32_SDATA_IN1
mdefine_line|#define GPIO32_SDATA_IN1&t;32&t;/* AC97 Sdata_in1 */
DECL|macro|GPIO32_MMCCLK
mdefine_line|#define GPIO32_MMCCLK&t;&t;32&t;/* MMC Clock (PXA270) */
DECL|macro|GPIO33_nCS_5
mdefine_line|#define GPIO33_nCS_5&t;&t;33&t;/* chip select 5 */
DECL|macro|GPIO34_FFRXD
mdefine_line|#define GPIO34_FFRXD&t;&t;34&t;/* FFUART receive */
DECL|macro|GPIO34_MMCCS0
mdefine_line|#define GPIO34_MMCCS0&t;&t;34&t;/* MMC Chip Select 0 */
DECL|macro|GPIO35_FFCTS
mdefine_line|#define GPIO35_FFCTS&t;&t;35&t;/* FFUART Clear to send */
DECL|macro|GPIO36_FFDCD
mdefine_line|#define GPIO36_FFDCD&t;&t;36&t;/* FFUART Data carrier detect */
DECL|macro|GPIO37_FFDSR
mdefine_line|#define GPIO37_FFDSR&t;&t;37&t;/* FFUART data set ready */
DECL|macro|GPIO38_FFRI
mdefine_line|#define GPIO38_FFRI&t;&t;38&t;/* FFUART Ring Indicator */
DECL|macro|GPIO39_MMCCS1
mdefine_line|#define GPIO39_MMCCS1&t;&t;39&t;/* MMC Chip Select 1 */
DECL|macro|GPIO39_FFTXD
mdefine_line|#define GPIO39_FFTXD&t;&t;39&t;/* FFUART transmit data */
DECL|macro|GPIO40_FFDTR
mdefine_line|#define GPIO40_FFDTR&t;&t;40&t;/* FFUART data terminal Ready */
DECL|macro|GPIO41_FFRTS
mdefine_line|#define GPIO41_FFRTS&t;&t;41&t;/* FFUART request to send */
DECL|macro|GPIO42_BTRXD
mdefine_line|#define GPIO42_BTRXD&t;&t;42&t;/* BTUART receive data */
DECL|macro|GPIO43_BTTXD
mdefine_line|#define GPIO43_BTTXD&t;&t;43&t;/* BTUART transmit data */
DECL|macro|GPIO44_BTCTS
mdefine_line|#define GPIO44_BTCTS&t;&t;44&t;/* BTUART clear to send */
DECL|macro|GPIO45_BTRTS
mdefine_line|#define GPIO45_BTRTS&t;&t;45&t;/* BTUART request to send */
DECL|macro|GPIO45_AC97_SYSCLK
mdefine_line|#define GPIO45_AC97_SYSCLK&t;45&t;/* AC97 System Clock */
DECL|macro|GPIO46_ICPRXD
mdefine_line|#define GPIO46_ICPRXD&t;&t;46&t;/* ICP receive data */
DECL|macro|GPIO46_STRXD
mdefine_line|#define GPIO46_STRXD&t;&t;46&t;/* STD_UART receive data */
DECL|macro|GPIO47_ICPTXD
mdefine_line|#define GPIO47_ICPTXD&t;&t;47&t;/* ICP transmit data */
DECL|macro|GPIO47_STTXD
mdefine_line|#define GPIO47_STTXD&t;&t;47&t;/* STD_UART transmit data */
DECL|macro|GPIO48_nPOE
mdefine_line|#define GPIO48_nPOE&t;&t;48&t;/* Output Enable for Card Space */
DECL|macro|GPIO49_nPWE
mdefine_line|#define GPIO49_nPWE&t;&t;49&t;/* Write Enable for Card Space */
DECL|macro|GPIO50_nPIOR
mdefine_line|#define GPIO50_nPIOR&t;&t;50&t;/* I/O Read for Card Space */
DECL|macro|GPIO51_nPIOW
mdefine_line|#define GPIO51_nPIOW&t;&t;51&t;/* I/O Write for Card Space */
DECL|macro|GPIO52_nPCE_1
mdefine_line|#define GPIO52_nPCE_1&t;&t;52&t;/* Card Enable for Card Space */
DECL|macro|GPIO53_nPCE_2
mdefine_line|#define GPIO53_nPCE_2&t;&t;53&t;/* Card Enable for Card Space */
DECL|macro|GPIO53_MMCCLK
mdefine_line|#define GPIO53_MMCCLK&t;&t;53&t;/* MMC Clock */
DECL|macro|GPIO54_MMCCLK
mdefine_line|#define GPIO54_MMCCLK&t;&t;54&t;/* MMC Clock */
DECL|macro|GPIO54_pSKTSEL
mdefine_line|#define GPIO54_pSKTSEL&t;&t;54&t;/* Socket Select for Card Space */
DECL|macro|GPIO54_nPCE_2
mdefine_line|#define GPIO54_nPCE_2&t;&t;54&t;/* Card Enable for Card Space (PXA27x) */
DECL|macro|GPIO55_nPREG
mdefine_line|#define GPIO55_nPREG&t;&t;55&t;/* Card Address bit 26 */
DECL|macro|GPIO56_nPWAIT
mdefine_line|#define GPIO56_nPWAIT&t;&t;56&t;/* Wait signal for Card Space */
DECL|macro|GPIO57_nIOIS16
mdefine_line|#define GPIO57_nIOIS16&t;&t;57&t;/* Bus Width select for I/O Card Space */
DECL|macro|GPIO58_LDD_0
mdefine_line|#define GPIO58_LDD_0&t;&t;58&t;/* LCD data pin 0 */
DECL|macro|GPIO59_LDD_1
mdefine_line|#define GPIO59_LDD_1&t;&t;59&t;/* LCD data pin 1 */
DECL|macro|GPIO60_LDD_2
mdefine_line|#define GPIO60_LDD_2&t;&t;60&t;/* LCD data pin 2 */
DECL|macro|GPIO61_LDD_3
mdefine_line|#define GPIO61_LDD_3&t;&t;61&t;/* LCD data pin 3 */
DECL|macro|GPIO62_LDD_4
mdefine_line|#define GPIO62_LDD_4&t;&t;62&t;/* LCD data pin 4 */
DECL|macro|GPIO63_LDD_5
mdefine_line|#define GPIO63_LDD_5&t;&t;63&t;/* LCD data pin 5 */
DECL|macro|GPIO64_LDD_6
mdefine_line|#define GPIO64_LDD_6&t;&t;64&t;/* LCD data pin 6 */
DECL|macro|GPIO65_LDD_7
mdefine_line|#define GPIO65_LDD_7&t;&t;65&t;/* LCD data pin 7 */
DECL|macro|GPIO66_LDD_8
mdefine_line|#define GPIO66_LDD_8&t;&t;66&t;/* LCD data pin 8 */
DECL|macro|GPIO66_MBREQ
mdefine_line|#define GPIO66_MBREQ&t;&t;66&t;/* alternate bus master req */
DECL|macro|GPIO67_LDD_9
mdefine_line|#define GPIO67_LDD_9&t;&t;67&t;/* LCD data pin 9 */
DECL|macro|GPIO67_MMCCS0
mdefine_line|#define GPIO67_MMCCS0&t;&t;67&t;/* MMC Chip Select 0 */
DECL|macro|GPIO68_LDD_10
mdefine_line|#define GPIO68_LDD_10&t;&t;68&t;/* LCD data pin 10 */
DECL|macro|GPIO68_MMCCS1
mdefine_line|#define GPIO68_MMCCS1&t;&t;68&t;/* MMC Chip Select 1 */
DECL|macro|GPIO69_LDD_11
mdefine_line|#define GPIO69_LDD_11&t;&t;69&t;/* LCD data pin 11 */
DECL|macro|GPIO69_MMCCLK
mdefine_line|#define GPIO69_MMCCLK&t;&t;69&t;/* MMC_CLK */
DECL|macro|GPIO70_LDD_12
mdefine_line|#define GPIO70_LDD_12&t;&t;70&t;/* LCD data pin 12 */
DECL|macro|GPIO70_RTCCLK
mdefine_line|#define GPIO70_RTCCLK&t;&t;70&t;/* Real Time clock (1 Hz) */
DECL|macro|GPIO71_LDD_13
mdefine_line|#define GPIO71_LDD_13&t;&t;71&t;/* LCD data pin 13 */
DECL|macro|GPIO71_3_6MHz
mdefine_line|#define GPIO71_3_6MHz&t;&t;71&t;/* 3.6 MHz Oscillator clock */
DECL|macro|GPIO72_LDD_14
mdefine_line|#define GPIO72_LDD_14&t;&t;72&t;/* LCD data pin 14 */
DECL|macro|GPIO72_32kHz
mdefine_line|#define GPIO72_32kHz&t;&t;72&t;/* 32 kHz clock */
DECL|macro|GPIO73_LDD_15
mdefine_line|#define GPIO73_LDD_15&t;&t;73&t;/* LCD data pin 15 */
DECL|macro|GPIO73_MBGNT
mdefine_line|#define GPIO73_MBGNT&t;&t;73&t;/* Memory controller grant */
DECL|macro|GPIO74_LCD_FCLK
mdefine_line|#define GPIO74_LCD_FCLK&t;&t;74&t;/* LCD Frame clock */
DECL|macro|GPIO75_LCD_LCLK
mdefine_line|#define GPIO75_LCD_LCLK&t;&t;75&t;/* LCD line clock */
DECL|macro|GPIO76_LCD_PCLK
mdefine_line|#define GPIO76_LCD_PCLK&t;&t;76&t;/* LCD Pixel clock */
DECL|macro|GPIO77_LCD_ACBIAS
mdefine_line|#define GPIO77_LCD_ACBIAS&t;77&t;/* LCD AC Bias */
DECL|macro|GPIO78_nCS_2
mdefine_line|#define GPIO78_nCS_2&t;&t;78&t;/* chip select 2 */
DECL|macro|GPIO79_nCS_3
mdefine_line|#define GPIO79_nCS_3&t;&t;79&t;/* chip select 3 */
DECL|macro|GPIO80_nCS_4
mdefine_line|#define GPIO80_nCS_4&t;&t;80&t;/* chip select 4 */
DECL|macro|GPIO85_nPCE_1
mdefine_line|#define GPIO85_nPCE_1&t;&t;85&t;/* Card Enable for Card Space (PXA27x) */
DECL|macro|GPIO92_MMCDAT0
mdefine_line|#define GPIO92_MMCDAT0&t;&t;92&t;/* MMC DAT0 (PXA27x) */
DECL|macro|GPIO109_MMCDAT1
mdefine_line|#define GPIO109_MMCDAT1&t;&t;109&t;/* MMC DAT1 (PXA27x) */
DECL|macro|GPIO110_MMCDAT2
mdefine_line|#define GPIO110_MMCDAT2&t;&t;110&t;/* MMC DAT2 (PXA27x) */
DECL|macro|GPIO110_MMCCS0
mdefine_line|#define GPIO110_MMCCS0&t;&t;110&t;/* MMC Chip Select 0 (PXA27x) */
DECL|macro|GPIO111_MMCDAT3
mdefine_line|#define GPIO111_MMCDAT3&t;&t;111&t;/* MMC DAT3 (PXA27x) */
DECL|macro|GPIO111_MMCCS1
mdefine_line|#define GPIO111_MMCCS1&t;&t;111&t;/* MMC Chip Select 1 (PXA27x) */
DECL|macro|GPIO112_MMCCMD
mdefine_line|#define GPIO112_MMCCMD&t;&t;112&t;/* MMC CMD (PXA27x) */
DECL|macro|GPIO113_AC97_RESET_N
mdefine_line|#define GPIO113_AC97_RESET_N&t;113&t;/* AC97 NRESET on (PXA27x) */
multiline_comment|/* GPIO alternate function mode &amp; direction */
DECL|macro|GPIO_IN
mdefine_line|#define GPIO_IN&t;&t;&t;0x000
DECL|macro|GPIO_OUT
mdefine_line|#define GPIO_OUT&t;&t;0x080
DECL|macro|GPIO_ALT_FN_1_IN
mdefine_line|#define GPIO_ALT_FN_1_IN&t;0x100
DECL|macro|GPIO_ALT_FN_1_OUT
mdefine_line|#define GPIO_ALT_FN_1_OUT&t;0x180
DECL|macro|GPIO_ALT_FN_2_IN
mdefine_line|#define GPIO_ALT_FN_2_IN&t;0x200
DECL|macro|GPIO_ALT_FN_2_OUT
mdefine_line|#define GPIO_ALT_FN_2_OUT&t;0x280
DECL|macro|GPIO_ALT_FN_3_IN
mdefine_line|#define GPIO_ALT_FN_3_IN&t;0x300
DECL|macro|GPIO_ALT_FN_3_OUT
mdefine_line|#define GPIO_ALT_FN_3_OUT&t;0x380
DECL|macro|GPIO_MD_MASK_NR
mdefine_line|#define GPIO_MD_MASK_NR&t;&t;0x07f
DECL|macro|GPIO_MD_MASK_DIR
mdefine_line|#define GPIO_MD_MASK_DIR&t;0x080
DECL|macro|GPIO_MD_MASK_FN
mdefine_line|#define GPIO_MD_MASK_FN&t;&t;0x300
DECL|macro|GPIO1_RTS_MD
mdefine_line|#define GPIO1_RTS_MD&t;&t;( 1 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO6_MMCCLK_MD
mdefine_line|#define GPIO6_MMCCLK_MD&t;&t;( 6 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO7_48MHz_MD
mdefine_line|#define GPIO7_48MHz_MD&t;&t;( 7 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO8_MMCCS0_MD
mdefine_line|#define GPIO8_MMCCS0_MD&t;&t;( 8 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO9_MMCCS1_MD
mdefine_line|#define GPIO9_MMCCS1_MD&t;&t;( 9 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO10_RTCCLK_MD
mdefine_line|#define GPIO10_RTCCLK_MD&t;(10 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO11_3_6MHz_MD
mdefine_line|#define GPIO11_3_6MHz_MD&t;(11 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO12_32KHz_MD
mdefine_line|#define GPIO12_32KHz_MD&t;&t;(12 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO13_MBGNT_MD
mdefine_line|#define GPIO13_MBGNT_MD&t;&t;(13 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO14_MBREQ_MD
mdefine_line|#define GPIO14_MBREQ_MD&t;&t;(14 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO15_nCS_1_MD
mdefine_line|#define GPIO15_nCS_1_MD&t;&t;(15 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO16_PWM0_MD
mdefine_line|#define GPIO16_PWM0_MD&t;&t;(16 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO17_PWM1_MD
mdefine_line|#define GPIO17_PWM1_MD&t;&t;(17 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO18_RDY_MD
mdefine_line|#define GPIO18_RDY_MD&t;&t;(18 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO19_DREQ1_MD
mdefine_line|#define GPIO19_DREQ1_MD&t;&t;(19 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO20_DREQ0_MD
mdefine_line|#define GPIO20_DREQ0_MD&t;&t;(20 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO23_SCLK_md
mdefine_line|#define GPIO23_SCLK_md&t;&t;(23 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO24_SFRM_MD
mdefine_line|#define GPIO24_SFRM_MD&t;&t;(24 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO25_STXD_MD
mdefine_line|#define GPIO25_STXD_MD&t;&t;(25 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO26_SRXD_MD
mdefine_line|#define GPIO26_SRXD_MD&t;&t;(26 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO27_SEXTCLK_MD
mdefine_line|#define GPIO27_SEXTCLK_MD&t;(27 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO28_BITCLK_AC97_MD
mdefine_line|#define GPIO28_BITCLK_AC97_MD&t;(28 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO28_BITCLK_I2S_MD
mdefine_line|#define GPIO28_BITCLK_I2S_MD&t;(28 | GPIO_ALT_FN_2_IN)
DECL|macro|GPIO29_SDATA_IN_AC97_MD
mdefine_line|#define GPIO29_SDATA_IN_AC97_MD&t;(29 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO29_SDATA_IN_I2S_MD
mdefine_line|#define GPIO29_SDATA_IN_I2S_MD&t;(29 | GPIO_ALT_FN_2_IN)
DECL|macro|GPIO30_SDATA_OUT_AC97_MD
mdefine_line|#define GPIO30_SDATA_OUT_AC97_MD&t;(30 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO30_SDATA_OUT_I2S_MD
mdefine_line|#define GPIO30_SDATA_OUT_I2S_MD&t;(30 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO31_SYNC_AC97_MD
mdefine_line|#define GPIO31_SYNC_AC97_MD&t;(31 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO31_SYNC_I2S_MD
mdefine_line|#define GPIO31_SYNC_I2S_MD&t;(31 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO32_SDATA_IN1_AC97_MD
mdefine_line|#define GPIO32_SDATA_IN1_AC97_MD&t;(32 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO32_MMCCLK_MD
mdefine_line|#define GPIO32_MMCCLK_MD&t;&t;( 32 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO33_nCS_5_MD
mdefine_line|#define GPIO33_nCS_5_MD&t;&t;(33 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO34_FFRXD_MD
mdefine_line|#define GPIO34_FFRXD_MD&t;&t;(34 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO34_MMCCS0_MD
mdefine_line|#define GPIO34_MMCCS0_MD&t;(34 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO35_FFCTS_MD
mdefine_line|#define GPIO35_FFCTS_MD&t;&t;(35 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO36_FFDCD_MD
mdefine_line|#define GPIO36_FFDCD_MD&t;&t;(36 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO37_FFDSR_MD
mdefine_line|#define GPIO37_FFDSR_MD&t;&t;(37 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO38_FFRI_MD
mdefine_line|#define GPIO38_FFRI_MD&t;&t;(38 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO39_MMCCS1_MD
mdefine_line|#define GPIO39_MMCCS1_MD&t;(39 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO39_FFTXD_MD
mdefine_line|#define GPIO39_FFTXD_MD&t;&t;(39 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO40_FFDTR_MD
mdefine_line|#define GPIO40_FFDTR_MD&t;&t;(40 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO41_FFRTS_MD
mdefine_line|#define GPIO41_FFRTS_MD&t;&t;(41 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO42_BTRXD_MD
mdefine_line|#define GPIO42_BTRXD_MD&t;&t;(42 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO43_BTTXD_MD
mdefine_line|#define GPIO43_BTTXD_MD&t;&t;(43 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO44_BTCTS_MD
mdefine_line|#define GPIO44_BTCTS_MD&t;&t;(44 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO45_BTRTS_MD
mdefine_line|#define GPIO45_BTRTS_MD&t;&t;(45 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO45_SYSCLK_AC97_MD
mdefine_line|#define GPIO45_SYSCLK_AC97_MD&t;&t;(45 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO46_ICPRXD_MD
mdefine_line|#define GPIO46_ICPRXD_MD&t;(46 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO46_STRXD_MD
mdefine_line|#define GPIO46_STRXD_MD&t;&t;(46 | GPIO_ALT_FN_2_IN)
DECL|macro|GPIO47_ICPTXD_MD
mdefine_line|#define GPIO47_ICPTXD_MD&t;(47 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO47_STTXD_MD
mdefine_line|#define GPIO47_STTXD_MD&t;&t;(47 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO48_nPOE_MD
mdefine_line|#define GPIO48_nPOE_MD&t;&t;(48 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO49_nPWE_MD
mdefine_line|#define GPIO49_nPWE_MD&t;&t;(49 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO50_nPIOR_MD
mdefine_line|#define GPIO50_nPIOR_MD&t;&t;(50 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO51_nPIOW_MD
mdefine_line|#define GPIO51_nPIOW_MD&t;&t;(51 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO52_nPCE_1_MD
mdefine_line|#define GPIO52_nPCE_1_MD&t;(52 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO53_nPCE_2_MD
mdefine_line|#define GPIO53_nPCE_2_MD&t;(53 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO53_MMCCLK_MD
mdefine_line|#define GPIO53_MMCCLK_MD&t;(53 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO54_MMCCLK_MD
mdefine_line|#define GPIO54_MMCCLK_MD&t;(54 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO54_nPCE_2_MD
mdefine_line|#define GPIO54_nPCE_2_MD&t;(54 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO54_pSKTSEL_MD
mdefine_line|#define GPIO54_pSKTSEL_MD&t;(54 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO55_nPREG_MD
mdefine_line|#define GPIO55_nPREG_MD&t;&t;(55 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO56_nPWAIT_MD
mdefine_line|#define GPIO56_nPWAIT_MD&t;(56 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO57_nIOIS16_MD
mdefine_line|#define GPIO57_nIOIS16_MD&t;(57 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO58_LDD_0_MD
mdefine_line|#define GPIO58_LDD_0_MD&t;&t;(58 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO59_LDD_1_MD
mdefine_line|#define GPIO59_LDD_1_MD&t;&t;(59 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO60_LDD_2_MD
mdefine_line|#define GPIO60_LDD_2_MD&t;&t;(60 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO61_LDD_3_MD
mdefine_line|#define GPIO61_LDD_3_MD&t;&t;(61 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO62_LDD_4_MD
mdefine_line|#define GPIO62_LDD_4_MD&t;&t;(62 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO63_LDD_5_MD
mdefine_line|#define GPIO63_LDD_5_MD&t;&t;(63 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO64_LDD_6_MD
mdefine_line|#define GPIO64_LDD_6_MD&t;&t;(64 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO65_LDD_7_MD
mdefine_line|#define GPIO65_LDD_7_MD&t;&t;(65 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO66_LDD_8_MD
mdefine_line|#define GPIO66_LDD_8_MD&t;&t;(66 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO66_MBREQ_MD
mdefine_line|#define GPIO66_MBREQ_MD&t;&t;(66 | GPIO_ALT_FN_1_IN)
DECL|macro|GPIO67_LDD_9_MD
mdefine_line|#define GPIO67_LDD_9_MD&t;&t;(67 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO67_MMCCS0_MD
mdefine_line|#define GPIO67_MMCCS0_MD&t;(67 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO68_LDD_10_MD
mdefine_line|#define GPIO68_LDD_10_MD&t;(68 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO68_MMCCS1_MD
mdefine_line|#define GPIO68_MMCCS1_MD&t;(68 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO69_LDD_11_MD
mdefine_line|#define GPIO69_LDD_11_MD&t;(69 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO69_MMCCLK_MD
mdefine_line|#define GPIO69_MMCCLK_MD&t;(69 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO70_LDD_12_MD
mdefine_line|#define GPIO70_LDD_12_MD&t;(70 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO70_RTCCLK_MD
mdefine_line|#define GPIO70_RTCCLK_MD&t;(70 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO71_LDD_13_MD
mdefine_line|#define GPIO71_LDD_13_MD&t;(71 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO71_3_6MHz_MD
mdefine_line|#define GPIO71_3_6MHz_MD&t;(71 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO72_LDD_14_MD
mdefine_line|#define GPIO72_LDD_14_MD&t;(72 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO72_32kHz_MD
mdefine_line|#define GPIO72_32kHz_MD&t;&t;(72 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO73_LDD_15_MD
mdefine_line|#define GPIO73_LDD_15_MD&t;(73 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO73_MBGNT_MD
mdefine_line|#define GPIO73_MBGNT_MD&t;&t;(73 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO74_LCD_FCLK_MD
mdefine_line|#define GPIO74_LCD_FCLK_MD&t;(74 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO75_LCD_LCLK_MD
mdefine_line|#define GPIO75_LCD_LCLK_MD&t;(75 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO76_LCD_PCLK_MD
mdefine_line|#define GPIO76_LCD_PCLK_MD&t;(76 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO77_LCD_ACBIAS_MD
mdefine_line|#define GPIO77_LCD_ACBIAS_MD&t;(77 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO78_nCS_2_MD
mdefine_line|#define GPIO78_nCS_2_MD&t;&t;(78 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO79_nCS_3_MD
mdefine_line|#define GPIO79_nCS_3_MD&t;&t;(79 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO79_pSKTSEL_MD
mdefine_line|#define GPIO79_pSKTSEL_MD&t;(79 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO80_nCS_4_MD
mdefine_line|#define GPIO80_nCS_4_MD&t;&t;(80 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO85_nPCE_1_MD
mdefine_line|#define GPIO85_nPCE_1_MD&t;(85 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO92_MMCDAT0_MD
mdefine_line|#define GPIO92_MMCDAT0_MD&t;(92 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO109_MMCDAT1_MD
mdefine_line|#define GPIO109_MMCDAT1_MD&t;(109 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO110_MMCDAT2_MD
mdefine_line|#define GPIO110_MMCDAT2_MD&t;(110 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO110_MMCCS0_MD
mdefine_line|#define GPIO110_MMCCS0_MD&t;(110 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO111_MMCDAT3_MD
mdefine_line|#define GPIO111_MMCDAT3_MD&t;(111 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO110_MMCCS1_MD
mdefine_line|#define GPIO110_MMCCS1_MD&t;(111 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO112_MMCCMD_MD
mdefine_line|#define GPIO112_MMCCMD_MD&t;(112 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO113_AC97_RESET_N_MD
mdefine_line|#define GPIO113_AC97_RESET_N_MD&t;(113 | GPIO_ALT_FN_2_OUT)
DECL|macro|GPIO117_I2CSCL_MD
mdefine_line|#define GPIO117_I2CSCL_MD&t;(117 | GPIO_ALT_FN_1_OUT)
DECL|macro|GPIO118_I2CSDA_MD
mdefine_line|#define GPIO118_I2CSDA_MD&t;(118 | GPIO_ALT_FN_1_IN)
multiline_comment|/*&n; * Power Manager&n; */
DECL|macro|PMCR
mdefine_line|#define PMCR&t;&t;__REG(0x40F00000)  /* Power Manager Control Register */
DECL|macro|PSSR
mdefine_line|#define PSSR&t;&t;__REG(0x40F00004)  /* Power Manager Sleep Status Register */
DECL|macro|PSPR
mdefine_line|#define PSPR&t;&t;__REG(0x40F00008)  /* Power Manager Scratch Pad Register */
DECL|macro|PWER
mdefine_line|#define PWER&t;&t;__REG(0x40F0000C)  /* Power Manager Wake-up Enable Register */
DECL|macro|PRER
mdefine_line|#define PRER&t;&t;__REG(0x40F00010)  /* Power Manager GPIO Rising-Edge Detect Enable Register */
DECL|macro|PFER
mdefine_line|#define PFER&t;&t;__REG(0x40F00014)  /* Power Manager GPIO Falling-Edge Detect Enable Register */
DECL|macro|PEDR
mdefine_line|#define PEDR&t;&t;__REG(0x40F00018)  /* Power Manager GPIO Edge Detect Status Register */
DECL|macro|PCFR
mdefine_line|#define PCFR&t;&t;__REG(0x40F0001C)  /* Power Manager General Configuration Register */
DECL|macro|PGSR0
mdefine_line|#define PGSR0&t;&t;__REG(0x40F00020)  /* Power Manager GPIO Sleep State Register for GP[31-0] */
DECL|macro|PGSR1
mdefine_line|#define PGSR1&t;&t;__REG(0x40F00024)  /* Power Manager GPIO Sleep State Register for GP[63-32] */
DECL|macro|PGSR2
mdefine_line|#define PGSR2&t;&t;__REG(0x40F00028)  /* Power Manager GPIO Sleep State Register for GP[84-64] */
DECL|macro|PGSR3
mdefine_line|#define PGSR3&t;&t;__REG(0x40F0002C)  /* Power Manager GPIO Sleep State Register for GP[118-96] */
DECL|macro|RCSR
mdefine_line|#define RCSR&t;&t;__REG(0x40F00030)  /* Reset Controller Status Register */
DECL|macro|PSLR
mdefine_line|#define PSLR&t;&t;__REG(0x40F00034)&t;/* Power Manager Sleep Config Register */
DECL|macro|PSTR
mdefine_line|#define PSTR&t;&t;__REG(0x40F00038)&t;/*Power Manager Standby Config Register */
DECL|macro|PSNR
mdefine_line|#define PSNR&t;&t;__REG(0x40F0003C)&t;/*Power Manager Sense Config Register */
DECL|macro|PVCR
mdefine_line|#define PVCR&t;&t;__REG(0x40F00040)&t;/*Power Manager VoltageControl Register */
DECL|macro|PKWR
mdefine_line|#define PKWR&t;&t;__REG(0x40F00050)&t;/* Power Manager KB Wake-up Enable Reg */
DECL|macro|PKSR
mdefine_line|#define PKSR&t;&t;__REG(0x40F00054)&t;/* Power Manager KB Level-Detect Register */
DECL|macro|PCMD
mdefine_line|#define PCMD(x)&t;__REG2(0x40F00080, (x)&lt;&lt;2)
DECL|macro|PCMD0
mdefine_line|#define PCMD0&t;__REG(0x40F00080 + 0 * 4)
DECL|macro|PCMD1
mdefine_line|#define PCMD1&t;__REG(0x40F00080 + 1 * 4)
DECL|macro|PCMD2
mdefine_line|#define PCMD2&t;__REG(0x40F00080 + 2 * 4)
DECL|macro|PCMD3
mdefine_line|#define PCMD3&t;__REG(0x40F00080 + 3 * 4)
DECL|macro|PCMD4
mdefine_line|#define PCMD4&t;__REG(0x40F00080 + 4 * 4)
DECL|macro|PCMD5
mdefine_line|#define PCMD5&t;__REG(0x40F00080 + 5 * 4)
DECL|macro|PCMD6
mdefine_line|#define PCMD6&t;__REG(0x40F00080 + 6 * 4)
DECL|macro|PCMD7
mdefine_line|#define PCMD7&t;__REG(0x40F00080 + 7 * 4)
DECL|macro|PCMD8
mdefine_line|#define PCMD8&t;__REG(0x40F00080 + 8 * 4)
DECL|macro|PCMD9
mdefine_line|#define PCMD9&t;__REG(0x40F00080 + 9 * 4)
DECL|macro|PCMD10
mdefine_line|#define PCMD10&t;__REG(0x40F00080 + 10 * 4)
DECL|macro|PCMD11
mdefine_line|#define PCMD11&t;__REG(0x40F00080 + 11 * 4)
DECL|macro|PCMD12
mdefine_line|#define PCMD12&t;__REG(0x40F00080 + 12 * 4)
DECL|macro|PCMD13
mdefine_line|#define PCMD13&t;__REG(0x40F00080 + 13 * 4)
DECL|macro|PCMD14
mdefine_line|#define PCMD14&t;__REG(0x40F00080 + 14 * 4)
DECL|macro|PCMD15
mdefine_line|#define PCMD15&t;__REG(0x40F00080 + 15 * 4)
DECL|macro|PCMD16
mdefine_line|#define PCMD16&t;__REG(0x40F00080 + 16 * 4)
DECL|macro|PCMD17
mdefine_line|#define PCMD17&t;__REG(0x40F00080 + 17 * 4)
DECL|macro|PCMD18
mdefine_line|#define PCMD18&t;__REG(0x40F00080 + 18 * 4)
DECL|macro|PCMD19
mdefine_line|#define PCMD19&t;__REG(0x40F00080 + 19 * 4)
DECL|macro|PCMD20
mdefine_line|#define PCMD20&t;__REG(0x40F00080 + 20 * 4)
DECL|macro|PCMD21
mdefine_line|#define PCMD21&t;__REG(0x40F00080 + 21 * 4)
DECL|macro|PCMD22
mdefine_line|#define PCMD22&t;__REG(0x40F00080 + 22 * 4)
DECL|macro|PCMD23
mdefine_line|#define PCMD23&t;__REG(0x40F00080 + 23 * 4)
DECL|macro|PCMD24
mdefine_line|#define PCMD24&t;__REG(0x40F00080 + 24 * 4)
DECL|macro|PCMD25
mdefine_line|#define PCMD25&t;__REG(0x40F00080 + 25 * 4)
DECL|macro|PCMD26
mdefine_line|#define PCMD26&t;__REG(0x40F00080 + 26 * 4)
DECL|macro|PCMD27
mdefine_line|#define PCMD27&t;__REG(0x40F00080 + 27 * 4)
DECL|macro|PCMD28
mdefine_line|#define PCMD28&t;__REG(0x40F00080 + 28 * 4)
DECL|macro|PCMD29
mdefine_line|#define PCMD29&t;__REG(0x40F00080 + 29 * 4)
DECL|macro|PCMD30
mdefine_line|#define PCMD30&t;__REG(0x40F00080 + 30 * 4)
DECL|macro|PCMD31
mdefine_line|#define PCMD31&t;__REG(0x40F00080 + 31 * 4)
DECL|macro|PCMD_MBC
mdefine_line|#define PCMD_MBC&t;(1&lt;&lt;12)
DECL|macro|PCMD_DCE
mdefine_line|#define PCMD_DCE&t;(1&lt;&lt;11)
DECL|macro|PCMD_LC
mdefine_line|#define PCMD_LC&t;(1&lt;&lt;10)
multiline_comment|/* FIXME:  PCMD_SQC need be checked.   */
DECL|macro|PCMD_SQC
mdefine_line|#define PCMD_SQC&t;(3&lt;&lt;8)&t;/* currently only bit 8 is changeable,&n;&t;&t;&t;&t;   bit 9 should be 0 all day. */
DECL|macro|PVCR_VCSA
mdefine_line|#define PVCR_VCSA&t;(0x1&lt;&lt;14)
DECL|macro|PVCR_CommandDelay
mdefine_line|#define PVCR_CommandDelay (0xf80)
DECL|macro|PCFR_PI2C_EN
mdefine_line|#define PCFR_PI2C_EN&t;(0x1 &lt;&lt; 6)
DECL|macro|PSSR_OTGPH
mdefine_line|#define PSSR_OTGPH&t;(1 &lt;&lt; 7)&t;/* OTG Peripheral control Hold */
DECL|macro|PSSR_RDH
mdefine_line|#define PSSR_RDH&t;(1 &lt;&lt; 5)&t;/* Read Disable Hold */
DECL|macro|PSSR_PH
mdefine_line|#define PSSR_PH&t;&t;(1 &lt;&lt; 4)&t;/* Peripheral Control Hold */
DECL|macro|PSSR_VFS
mdefine_line|#define PSSR_VFS&t;(1 &lt;&lt; 2)&t;/* VDD Fault Status */
DECL|macro|PSSR_BFS
mdefine_line|#define PSSR_BFS&t;(1 &lt;&lt; 1)&t;/* Battery Fault Status */
DECL|macro|PSSR_SSS
mdefine_line|#define PSSR_SSS&t;(1 &lt;&lt; 0)&t;/* Software Sleep Status */
DECL|macro|PCFR_RO
mdefine_line|#define PCFR_RO&t;&t;(1 &lt;&lt; 15)&t;/* RDH Override */
DECL|macro|PCFR_PO
mdefine_line|#define PCFR_PO&t;&t;(1 &lt;&lt; 14)&t;/* PH Override */
DECL|macro|PCFR_GPROD
mdefine_line|#define PCFR_GPROD&t;(1 &lt;&lt; 12)&t;/* GPIO nRESET_OUT Disable */
DECL|macro|PCFR_L1_EN
mdefine_line|#define PCFR_L1_EN&t;(1 &lt;&lt; 11)&t;/* Sleep Mode L1 converter Enable */
DECL|macro|PCFR_FVC
mdefine_line|#define PCFR_FVC&t;(1 &lt;&lt; 10)&t;/* Frequency/Voltage Change */
DECL|macro|PCFR_DC_EN
mdefine_line|#define PCFR_DC_EN&t;(1 &lt;&lt; 7)&t;/* Sleep/deep-sleep DC-DC Converter Enable */
DECL|macro|PCFR_PI2CEN
mdefine_line|#define PCFR_PI2CEN&t;(1 &lt;&lt; 6)&t;/* Enable PI2C controller */
DECL|macro|PCFR_DS
mdefine_line|#define PCFR_DS&t;&t;(1 &lt;&lt; 3)&t;/* Deep Sleep Mode */
DECL|macro|PCFR_FS
mdefine_line|#define PCFR_FS&t;&t;(1 &lt;&lt; 2)&t;/* Float Static Chip Selects */
DECL|macro|PCFR_FP
mdefine_line|#define PCFR_FP&t;&t;(1 &lt;&lt; 1)&t;/* Float PCMCIA controls */
DECL|macro|PCFR_OPDE
mdefine_line|#define PCFR_OPDE&t;(1 &lt;&lt; 0)&t;/* 3.6864 MHz oscillator power-down enable */
DECL|macro|RCSR_GPR
mdefine_line|#define RCSR_GPR&t;(1 &lt;&lt; 3)&t;/* GPIO Reset */
DECL|macro|RCSR_SMR
mdefine_line|#define RCSR_SMR&t;(1 &lt;&lt; 2)&t;/* Sleep Mode */
DECL|macro|RCSR_WDR
mdefine_line|#define RCSR_WDR&t;(1 &lt;&lt; 1)&t;/* Watchdog Reset */
DECL|macro|RCSR_HWR
mdefine_line|#define RCSR_HWR&t;(1 &lt;&lt; 0)&t;/* Hardware Reset */
multiline_comment|/*&n; * SSP Serial Port Registers&n; * PXA250, PXA255, PXA26x and PXA27x SSP controllers are all slightly different.&n; * PXA255, PXA26x and PXA27x have extra ports, registers and bits.&n; */
multiline_comment|/* Common PXA2xx bits first */
DECL|macro|SSCR0_DSS
mdefine_line|#define SSCR0_DSS&t;(0x0000000f)&t;/* Data Size Select (mask) */
DECL|macro|SSCR0_DataSize
mdefine_line|#define SSCR0_DataSize(x)  ((x) - 1)&t;/* Data Size Select [4..16] */
DECL|macro|SSCR0_FRF
mdefine_line|#define SSCR0_FRF&t;(0x00000030)&t;/* FRame Format (mask) */
DECL|macro|SSCR0_Motorola
mdefine_line|#define SSCR0_Motorola&t;(0x0 &lt;&lt; 4)&t;/* Motorola&squot;s Serial Peripheral Interface (SPI) */
DECL|macro|SSCR0_TI
mdefine_line|#define SSCR0_TI&t;(0x1 &lt;&lt; 4)&t;/* Texas Instruments&squot; Synchronous Serial Protocol (SSP) */
DECL|macro|SSCR0_National
mdefine_line|#define SSCR0_National&t;(0x2 &lt;&lt; 4)&t;/* National Microwire */
DECL|macro|SSCR0_ECS
mdefine_line|#define SSCR0_ECS&t;(1 &lt;&lt; 6)&t;/* External clock select */
DECL|macro|SSCR0_SSE
mdefine_line|#define SSCR0_SSE&t;(1 &lt;&lt; 7)&t;/* Synchronous Serial Port Enable */
DECL|macro|SSCR0_SCR
mdefine_line|#define SSCR0_SCR&t;(0x0000ff00)&t;/* Serial Clock Rate (mask) */
DECL|macro|SSCR0_SerClkDiv
mdefine_line|#define SSCR0_SerClkDiv(x) ((((x) - 2)/2) &lt;&lt; 8) /* Divisor [2..512] */
DECL|macro|SSCR1_RIE
mdefine_line|#define SSCR1_RIE&t;(1 &lt;&lt; 0)&t;/* Receive FIFO Interrupt Enable */
DECL|macro|SSCR1_TIE
mdefine_line|#define SSCR1_TIE&t;(1 &lt;&lt; 1)&t;/* Transmit FIFO Interrupt Enable */
DECL|macro|SSCR1_LBM
mdefine_line|#define SSCR1_LBM&t;(1 &lt;&lt; 2)&t;/* Loop-Back Mode */
DECL|macro|SSCR1_SPO
mdefine_line|#define SSCR1_SPO&t;(1 &lt;&lt; 3)&t;/* Motorola SPI SSPSCLK polarity setting */
DECL|macro|SSCR1_SPH
mdefine_line|#define SSCR1_SPH&t;(1 &lt;&lt; 4)&t;/* Motorola SPI SSPSCLK phase setting */
DECL|macro|SSCR1_MWDS
mdefine_line|#define SSCR1_MWDS&t;(1 &lt;&lt; 5)&t;/* Microwire Transmit Data Size */
DECL|macro|SSCR1_TFT
mdefine_line|#define SSCR1_TFT&t;(0x000003c0)&t;/* Transmit FIFO Threshold (mask) */
DECL|macro|SSCR1_TxTresh
mdefine_line|#define SSCR1_TxTresh(x) (((x) - 1) &lt;&lt; 6) /* level [1..16] */
DECL|macro|SSCR1_RFT
mdefine_line|#define SSCR1_RFT&t;(0x00003c00)&t;/* Receive FIFO Threshold (mask) */
DECL|macro|SSCR1_RxTresh
mdefine_line|#define SSCR1_RxTresh(x) (((x) - 1) &lt;&lt; 10) /* level [1..16] */
DECL|macro|SSSR_TNF
mdefine_line|#define SSSR_TNF&t;(1 &lt;&lt; 2)&t;/* Transmit FIFO Not Full */
DECL|macro|SSSR_RNE
mdefine_line|#define SSSR_RNE&t;(1 &lt;&lt; 3)&t;/* Receive FIFO Not Empty */
DECL|macro|SSSR_BSY
mdefine_line|#define SSSR_BSY&t;(1 &lt;&lt; 4)&t;/* SSP Busy */
DECL|macro|SSSR_TFS
mdefine_line|#define SSSR_TFS&t;(1 &lt;&lt; 5)&t;/* Transmit FIFO Service Request */
DECL|macro|SSSR_RFS
mdefine_line|#define SSSR_RFS&t;(1 &lt;&lt; 6)&t;/* Receive FIFO Service Request */
DECL|macro|SSSR_ROR
mdefine_line|#define SSSR_ROR&t;(1 &lt;&lt; 7)&t;/* Receive FIFO Overrun */
DECL|macro|SSCR0_TIM
mdefine_line|#define SSCR0_TIM&t;&t;(1 &lt;&lt; 23)&t;/* Transmit FIFO Under Run Interrupt Mask */
DECL|macro|SSCR0_RIM
mdefine_line|#define SSCR0_RIM&t;&t;(1 &lt;&lt; 22)&t;/* Receive FIFO Over Run interrupt Mask */
DECL|macro|SSCR0_NCS
mdefine_line|#define SSCR0_NCS&t;&t;(1 &lt;&lt; 21)&t;/* Network Clock Select */
DECL|macro|SSCR0_EDSS
mdefine_line|#define SSCR0_EDSS&t;&t;(1 &lt;&lt; 20)&t;/* Extended Data Size Select */
multiline_comment|/* extra bits in PXA255, PXA26x and PXA27x SSP ports */
DECL|macro|SSCR1_TTELP
mdefine_line|#define SSCR1_TTELP&t;&t;(1 &lt;&lt; 31)&t;/* TXD Tristate Enable Last Phase */
DECL|macro|SSCR1_TTE
mdefine_line|#define SSCR1_TTE&t;&t;(1 &lt;&lt; 30)&t;/* TXD Tristate Enable */
DECL|macro|SSCR1_EBCEI
mdefine_line|#define SSCR1_EBCEI&t;&t;(1 &lt;&lt; 29)&t;/* Enable Bit Count Error interrupt */
DECL|macro|SSCR1_SCFR
mdefine_line|#define SSCR1_SCFR&t;&t;(1 &lt;&lt; 28)&t;/* Slave Clock free Running */
DECL|macro|SSCR1_ECRA
mdefine_line|#define SSCR1_ECRA&t;&t;(1 &lt;&lt; 27)&t;/* Enable Clock Request A */
DECL|macro|SSCR1_ECRB
mdefine_line|#define SSCR1_ECRB&t;&t;(1 &lt;&lt; 26)&t;/* Enable Clock request B */
DECL|macro|SSCR1_SCLKDIR
mdefine_line|#define SSCR1_SCLKDIR&t;(1 &lt;&lt; 25)&t;/* Serial Bit Rate Clock Direction */
DECL|macro|SSCR1_SFRMDIR
mdefine_line|#define SSCR1_SFRMDIR&t;(1 &lt;&lt; 24)&t;/* Frame Direction */
DECL|macro|SSCR1_RWOT
mdefine_line|#define SSCR1_RWOT&t;&t;(1 &lt;&lt; 23)&t;/* Receive Without Transmit */
DECL|macro|SSCR1_TRAIL
mdefine_line|#define SSCR1_TRAIL&t;&t;(1 &lt;&lt; 22)&t;/* Trailing Byte */
DECL|macro|SSCR1_TSRE
mdefine_line|#define SSCR1_TSRE&t;&t;(1 &lt;&lt; 21)&t;/* Transmit Service Request Enable */
DECL|macro|SSCR1_RSRE
mdefine_line|#define SSCR1_RSRE&t;&t;(1 &lt;&lt; 20)&t;/* Receive Service Request Enable */
DECL|macro|SSCR1_TINTE
mdefine_line|#define SSCR1_TINTE&t;&t;(1 &lt;&lt; 19)&t;/* Receiver Time-out Interrupt enable */
DECL|macro|SSCR1_PINTE
mdefine_line|#define SSCR1_PINTE&t;&t;(1 &lt;&lt; 18)&t;/* Peripheral Trailing Byte Interupt Enable */
DECL|macro|SSCR1_STRF
mdefine_line|#define SSCR1_STRF&t;&t;(1 &lt;&lt; 15)&t;/* Select FIFO or EFWR */
DECL|macro|SSCR1_EFWR
mdefine_line|#define SSCR1_EFWR&t;&t;(1 &lt;&lt; 14)&t;/* Enable FIFO Write/Read */
DECL|macro|SSSR_BCE
mdefine_line|#define SSSR_BCE&t;&t;(1 &lt;&lt; 23)&t;/* Bit Count Error */
DECL|macro|SSSR_CSS
mdefine_line|#define SSSR_CSS&t;&t;(1 &lt;&lt; 22)&t;/* Clock Synchronisation Status */
DECL|macro|SSSR_TUR
mdefine_line|#define SSSR_TUR&t;&t;(1 &lt;&lt; 21)&t;/* Transmit FIFO Under Run */
DECL|macro|SSSR_EOC
mdefine_line|#define SSSR_EOC&t;&t;(1 &lt;&lt; 20)&t;/* End Of Chain */
DECL|macro|SSSR_TINT
mdefine_line|#define SSSR_TINT&t;&t;(1 &lt;&lt; 19)&t;/* Receiver Time-out Interrupt */
DECL|macro|SSSR_PINT
mdefine_line|#define SSSR_PINT&t;&t;(1 &lt;&lt; 18)&t;/* Peripheral Trailing Byte Interrupt */
DECL|macro|SSPSP_DMYSTOP
mdefine_line|#define SSPSP_DMYSTOP(x)&t;(x &lt;&lt; 23)&t;/* Dummy Stop */
DECL|macro|SSPSP_SFRMWDTH
mdefine_line|#define SSPSP_SFRMWDTH(x)&t;(x &lt;&lt; 16)&t;/* Serial Frame Width */
DECL|macro|SSPSP_SFRMDLY
mdefine_line|#define SSPSP_SFRMDLY(x)&t;(x &lt;&lt; 9)&t;/* Serial Frame Delay */
DECL|macro|SSPSP_DMYSTRT
mdefine_line|#define SSPSP_DMYSTRT(x)&t;(x &lt;&lt; 7)&t;/* Dummy Start */
DECL|macro|SSPSP_STRTDLY
mdefine_line|#define SSPSP_STRTDLY(x)&t;(x &lt;&lt; 4)&t;/* Start Delay */
DECL|macro|SSPSP_ETDS
mdefine_line|#define SSPSP_ETDS&t;&t;&t;(1 &lt;&lt; 3)&t;/* End of Transfer data State */
DECL|macro|SSPSP_SFRMP
mdefine_line|#define SSPSP_SFRMP&t;&t;&t;(1 &lt;&lt; 2)&t;/* Serial Frame Polarity */
DECL|macro|SSPSP_SCMODE
mdefine_line|#define SSPSP_SCMODE(x)&t;&t;(x &lt;&lt; 0)&t;/* Serial Bit Rate Clock Mode */
DECL|macro|SSCR0_P1
mdefine_line|#define SSCR0_P1&t;__REG(0x41000000)  /* SSP Port 1 Control Register 0 */
DECL|macro|SSCR1_P1
mdefine_line|#define SSCR1_P1&t;__REG(0x41000004)  /* SSP Port 1 Control Register 1 */
DECL|macro|SSSR_P1
mdefine_line|#define SSSR_P1&t;&t;__REG(0x41000008)  /* SSP Port 1 Status Register */
DECL|macro|SSITR_P1
mdefine_line|#define SSITR_P1&t;__REG(0x4100000C)  /* SSP Port 1 Interrupt Test Register */
DECL|macro|SSDR_P1
mdefine_line|#define SSDR_P1&t;&t;__REG(0x41000010)  /* (Write / Read) SSP Port 1 Data Write Register/SSP Data Read Register */
multiline_comment|/* Support existing PXA25x drivers */
DECL|macro|SSCR0
mdefine_line|#define SSCR0&t;&t;SSCR0_P1  /* SSP Control Register 0 */
DECL|macro|SSCR1
mdefine_line|#define SSCR1&t;&t;SSCR1_P1  /* SSP Control Register 1 */
DECL|macro|SSSR
mdefine_line|#define SSSR&t;&t;SSSR_P1&t;  /* SSP Status Register */
DECL|macro|SSITR
mdefine_line|#define SSITR&t;&t;SSITR_P1  /* SSP Interrupt Test Register */
DECL|macro|SSDR
mdefine_line|#define SSDR&t;&t;SSDR_P1&t;  /* (Write / Read) SSP Data Write Register/SSP Data Read Register */
multiline_comment|/* PXA27x ports */
macro_line|#if defined (CONFIG_PXA27x)
DECL|macro|SSTO_P1
mdefine_line|#define SSTO_P1&t;&t;__REG(0x41000028)  /* SSP Port 1 Time Out Register */
DECL|macro|SSPSP_P1
mdefine_line|#define SSPSP_P1&t;__REG(0x4100002C)  /* SSP Port 1 Programmable Serial Protocol */
DECL|macro|SSCR0_P2
mdefine_line|#define SSCR0_P2&t;__REG(0x41700000)  /* SSP Port 2 Control Register 0 */
DECL|macro|SSCR1_P2
mdefine_line|#define SSCR1_P2&t;__REG(0x41700004)  /* SSP Port 2 Control Register 1 */
DECL|macro|SSSR_P2
mdefine_line|#define SSSR_P2&t;&t;__REG(0x41700008)  /* SSP Port 2 Status Register */
DECL|macro|SSITR_P2
mdefine_line|#define SSITR_P2&t;__REG(0x4170000C)  /* SSP Port 2 Interrupt Test Register */
DECL|macro|SSDR_P2
mdefine_line|#define SSDR_P2&t;&t;__REG(0x41700010)  /* (Write / Read) SSP Port 2 Data Write Register/SSP Data Read Register */
DECL|macro|SSTO_P2
mdefine_line|#define SSTO_P2&t;&t;__REG(0x41700028)  /* SSP Port 2 Time Out Register */
DECL|macro|SSPSP_P2
mdefine_line|#define SSPSP_P2&t;__REG(0x4170002C)  /* SSP Port 2 Programmable Serial Protocol */
DECL|macro|SSCR0_P3
mdefine_line|#define SSCR0_P3&t;__REG(0x41900000)  /* SSP Port 3 Control Register 0 */
DECL|macro|SSCR1_P3
mdefine_line|#define SSCR1_P3&t;__REG(0x41900004)  /* SSP Port 3 Control Register 1 */
DECL|macro|SSSR_P3
mdefine_line|#define SSSR_P3&t;&t;__REG(0x41900008)  /* SSP Port 3 Status Register */
DECL|macro|SSITR_P3
mdefine_line|#define SSITR_P3&t;__REG(0x4190000C)  /* SSP Port 3 Interrupt Test Register */
DECL|macro|SSDR_P3
mdefine_line|#define SSDR_P3&t;&t;__REG(0x41900010)  /* (Write / Read) SSP Port 3 Data Write Register/SSP Data Read Register */
DECL|macro|SSTO_P3
mdefine_line|#define SSTO_P3&t;&t;__REG(0x41900028)  /* SSP Port 3 Time Out Register */
DECL|macro|SSPSP_P3
mdefine_line|#define SSPSP_P3&t;__REG(0x4190002C)  /* SSP Port 3 Programmable Serial Protocol */
macro_line|#else /* PXA255 (only port 2) and PXA26x ports*/
DECL|macro|SSTO_P1
mdefine_line|#define SSTO_P1&t;&t;__REG(0x41000028)  /* SSP Port 1 Time Out Register */
DECL|macro|SSPSP_P1
mdefine_line|#define SSPSP_P1&t;__REG(0x4100002C)  /* SSP Port 1 Programmable Serial Protocol */
DECL|macro|SSCR0_P2
mdefine_line|#define SSCR0_P2&t;__REG(0x41400000)  /* SSP Port 2 Control Register 0 */
DECL|macro|SSCR1_P2
mdefine_line|#define SSCR1_P2&t;__REG(0x41400004)  /* SSP Port 2 Control Register 1 */
DECL|macro|SSSR_P2
mdefine_line|#define SSSR_P2&t;&t;__REG(0x41400008)  /* SSP Port 2 Status Register */
DECL|macro|SSITR_P2
mdefine_line|#define SSITR_P2&t;__REG(0x4140000C)  /* SSP Port 2 Interrupt Test Register */
DECL|macro|SSDR_P2
mdefine_line|#define SSDR_P2&t;&t;__REG(0x41400010)  /* (Write / Read) SSP Port 2 Data Write Register/SSP Data Read Register */
DECL|macro|SSTO_P2
mdefine_line|#define SSTO_P2&t;&t;__REG(0x41400028)  /* SSP Port 2 Time Out Register */
DECL|macro|SSPSP_P2
mdefine_line|#define SSPSP_P2&t;__REG(0x4140002C)  /* SSP Port 2 Programmable Serial Protocol */
DECL|macro|SSCR0_P3
mdefine_line|#define SSCR0_P3&t;__REG(0x41500000)  /* SSP Port 3 Control Register 0 */
DECL|macro|SSCR1_P3
mdefine_line|#define SSCR1_P3&t;__REG(0x41500004)  /* SSP Port 3 Control Register 1 */
DECL|macro|SSSR_P3
mdefine_line|#define SSSR_P3&t;&t;__REG(0x41500008)  /* SSP Port 3 Status Register */
DECL|macro|SSITR_P3
mdefine_line|#define SSITR_P3&t;__REG(0x4150000C)  /* SSP Port 3 Interrupt Test Register */
DECL|macro|SSDR_P3
mdefine_line|#define SSDR_P3&t;&t;__REG(0x41500010)  /* (Write / Read) SSP Port 3 Data Write Register/SSP Data Read Register */
DECL|macro|SSTO_P3
mdefine_line|#define SSTO_P3&t;&t;__REG(0x41500028)  /* SSP Port 3 Time Out Register */
DECL|macro|SSPSP_P3
mdefine_line|#define SSPSP_P3&t;__REG(0x4150002C)  /* SSP Port 3 Programmable Serial Protocol */
macro_line|#endif
DECL|macro|SSCR0_P
mdefine_line|#define SSCR0_P(x) (*(((x) == 1) ? &amp;SSCR0_P1 : ((x) == 2) ? &amp;SSCR0_P2 : ((x) == 3) ? &amp;SSCR0_P3 : NULL))
DECL|macro|SSCR1_P
mdefine_line|#define SSCR1_P(x) (*(((x) == 1) ? &amp;SSCR1_P1 : ((x) == 2) ? &amp;SSCR1_P2 : ((x) == 3) ? &amp;SSCR1_P3 : NULL))
DECL|macro|SSSR_P
mdefine_line|#define SSSR_P(x) (*(((x) == 1) ? &amp;SSSR_P1 : ((x) == 2) ? &amp;SSSR_P2 : ((x) == 3) ? &amp;SSSR_P3 : NULL))
DECL|macro|SSITR_P
mdefine_line|#define SSITR_P(x) (*(((x) == 1) ? &amp;SSITR_P1 : ((x) == 2) ? &amp;SSITR_P2 : ((x) == 3) ? &amp;SSITR_P3 : NULL))
DECL|macro|SSDR_P
mdefine_line|#define SSDR_P(x) (*(((x) == 1) ? &amp;SSDR_P1 : ((x) == 2) ? &amp;SSDR_P2 : ((x) == 3) ? &amp;SSDR_P3 : NULL))
DECL|macro|SSTO_P
mdefine_line|#define SSTO_P(x) (*(((x) == 1) ? &amp;SSTO_P1 : ((x) == 2) ? &amp;SSTO_P2 : ((x) == 3) ? &amp;SSTO_P3 : NULL))
DECL|macro|SSPSP_P
mdefine_line|#define SSPSP_P(x) (*(((x) == 1) ? &amp;SSPSP_P1 : ((x) == 2) ? &amp;SSPSP_P2 : ((x) == 3) ? &amp;SSPSP_P3 : NULL))
multiline_comment|/*&n; * MultiMediaCard (MMC) controller&n; */
DECL|macro|MMC_STRPCL
mdefine_line|#define MMC_STRPCL&t;__REG(0x41100000)  /* Control to start and stop MMC clock */
DECL|macro|MMC_STAT
mdefine_line|#define MMC_STAT&t;__REG(0x41100004)  /* MMC Status Register (read only) */
DECL|macro|MMC_CLKRT
mdefine_line|#define MMC_CLKRT&t;__REG(0x41100008)  /* MMC clock rate */
DECL|macro|MMC_SPI
mdefine_line|#define MMC_SPI&t;&t;__REG(0x4110000c)  /* SPI mode control bits */
DECL|macro|MMC_CMDAT
mdefine_line|#define MMC_CMDAT&t;__REG(0x41100010)  /* Command/response/data sequence control */
DECL|macro|MMC_RESTO
mdefine_line|#define MMC_RESTO&t;__REG(0x41100014)  /* Expected response time out */
DECL|macro|MMC_RDTO
mdefine_line|#define MMC_RDTO&t;__REG(0x41100018)  /* Expected data read time out */
DECL|macro|MMC_BLKLEN
mdefine_line|#define MMC_BLKLEN&t;__REG(0x4110001c)  /* Block length of data transaction */
DECL|macro|MMC_NOB
mdefine_line|#define MMC_NOB&t;&t;__REG(0x41100020)  /* Number of blocks, for block mode */
DECL|macro|MMC_PRTBUF
mdefine_line|#define MMC_PRTBUF&t;__REG(0x41100024)  /* Partial MMC_TXFIFO FIFO written */
DECL|macro|MMC_I_MASK
mdefine_line|#define MMC_I_MASK&t;__REG(0x41100028)  /* Interrupt Mask */
DECL|macro|MMC_I_REG
mdefine_line|#define MMC_I_REG&t;__REG(0x4110002c)  /* Interrupt Register (read only) */
DECL|macro|MMC_CMD
mdefine_line|#define MMC_CMD&t;&t;__REG(0x41100030)  /* Index of current command */
DECL|macro|MMC_ARGH
mdefine_line|#define MMC_ARGH&t;__REG(0x41100034)  /* MSW part of the current command argument */
DECL|macro|MMC_ARGL
mdefine_line|#define MMC_ARGL&t;__REG(0x41100038)  /* LSW part of the current command argument */
DECL|macro|MMC_RES
mdefine_line|#define MMC_RES&t;&t;__REG(0x4110003c)  /* Response FIFO (read only) */
DECL|macro|MMC_RXFIFO
mdefine_line|#define MMC_RXFIFO&t;__REG(0x41100040)  /* Receive FIFO (read only) */
DECL|macro|MMC_TXFIFO
mdefine_line|#define MMC_TXFIFO&t;__REG(0x41100044)  /* Transmit FIFO (write only) */
multiline_comment|/*&n; * Core Clock&n; */
DECL|macro|CCCR
mdefine_line|#define CCCR&t;&t;__REG(0x41300000)  /* Core Clock Configuration Register */
DECL|macro|CKEN
mdefine_line|#define CKEN&t;&t;__REG(0x41300004)  /* Clock Enable Register */
DECL|macro|OSCC
mdefine_line|#define OSCC&t;&t;__REG(0x41300008)  /* Oscillator Configuration Register */
DECL|macro|CCSR
mdefine_line|#define CCSR&t;&t;__REG(0x4130000C)  /* Core Clock Status Register */
DECL|macro|CCCR_N_MASK
mdefine_line|#define CCCR_N_MASK&t;0x0380&t;&t;/* Run Mode Frequency to Turbo Mode Frequency Multiplier */
DECL|macro|CCCR_M_MASK
mdefine_line|#define CCCR_M_MASK&t;0x0060&t;&t;/* Memory Frequency to Run Mode Frequency Multiplier */
DECL|macro|CCCR_L_MASK
mdefine_line|#define CCCR_L_MASK&t;0x001f&t;&t;/* Crystal Frequency to Memory Frequency Multiplier */
DECL|macro|CKEN24_CAMERA
mdefine_line|#define CKEN24_CAMERA&t;(1 &lt;&lt; 24)&t;/* Camera Interface Clock Enable */
DECL|macro|CKEN23_SSP1
mdefine_line|#define CKEN23_SSP1&t;(1 &lt;&lt; 23)&t;/* SSP1 Unit Clock Enable */
DECL|macro|CKEN22_MEMC
mdefine_line|#define CKEN22_MEMC&t;(1 &lt;&lt; 22)&t;/* Memory Controller Clock Enable */
DECL|macro|CKEN21_MEMSTK
mdefine_line|#define CKEN21_MEMSTK&t;(1 &lt;&lt; 21)&t;/* Memory Stick Host Controller */
DECL|macro|CKEN20_IM
mdefine_line|#define CKEN20_IM&t;(1 &lt;&lt; 20)&t;/* Internal Memory Clock Enable */
DECL|macro|CKEN19_KEYPAD
mdefine_line|#define CKEN19_KEYPAD&t;(1 &lt;&lt; 19)&t;/* Keypad Interface Clock Enable */
DECL|macro|CKEN18_USIM
mdefine_line|#define CKEN18_USIM&t;(1 &lt;&lt; 18)&t;/* USIM Unit Clock Enable */
DECL|macro|CKEN17_MSL
mdefine_line|#define CKEN17_MSL&t;(1 &lt;&lt; 17)&t;/* MSL Unit Clock Enable */
DECL|macro|CKEN16_LCD
mdefine_line|#define CKEN16_LCD&t;(1 &lt;&lt; 16)&t;/* LCD Unit Clock Enable */
DECL|macro|CKEN15_PWRI2C
mdefine_line|#define CKEN15_PWRI2C&t;(1 &lt;&lt; 15)&t;/* PWR I2C Unit Clock Enable */
DECL|macro|CKEN14_I2C
mdefine_line|#define CKEN14_I2C&t;(1 &lt;&lt; 14)&t;/* I2C Unit Clock Enable */
DECL|macro|CKEN13_FICP
mdefine_line|#define CKEN13_FICP&t;(1 &lt;&lt; 13)&t;/* FICP Unit Clock Enable */
DECL|macro|CKEN12_MMC
mdefine_line|#define CKEN12_MMC&t;(1 &lt;&lt; 12)&t;/* MMC Unit Clock Enable */
DECL|macro|CKEN11_USB
mdefine_line|#define CKEN11_USB&t;(1 &lt;&lt; 11)&t;/* USB Unit Clock Enable */
DECL|macro|CKEN10_ASSP
mdefine_line|#define CKEN10_ASSP&t;(1 &lt;&lt; 10)&t;/* ASSP (SSP3) Clock Enable */
DECL|macro|CKEN10_USBHOST
mdefine_line|#define CKEN10_USBHOST&t;(1 &lt;&lt; 10)&t;/* USB Host Unit Clock Enable */
DECL|macro|CKEN9_OSTIMER
mdefine_line|#define CKEN9_OSTIMER&t;(1 &lt;&lt; 9)&t;/* OS Timer Unit Clock Enable */
DECL|macro|CKEN9_NSSP
mdefine_line|#define CKEN9_NSSP&t;(1 &lt;&lt; 9)&t;/* NSSP (SSP2) Clock Enable */
DECL|macro|CKEN8_I2S
mdefine_line|#define CKEN8_I2S&t;(1 &lt;&lt; 8)&t;/* I2S Unit Clock Enable */
DECL|macro|CKEN7_BTUART
mdefine_line|#define CKEN7_BTUART&t;(1 &lt;&lt; 7)&t;/* BTUART Unit Clock Enable */
DECL|macro|CKEN6_FFUART
mdefine_line|#define CKEN6_FFUART&t;(1 &lt;&lt; 6)&t;/* FFUART Unit Clock Enable */
DECL|macro|CKEN5_STUART
mdefine_line|#define CKEN5_STUART&t;(1 &lt;&lt; 5)&t;/* STUART Unit Clock Enable */
DECL|macro|CKEN4_SSP3
mdefine_line|#define CKEN4_SSP3&t;(1 &lt;&lt; 4)&t;/* SSP3 Unit Clock Enable */
DECL|macro|CKEN3_SSP
mdefine_line|#define CKEN3_SSP&t;(1 &lt;&lt; 3)&t;/* SSP Unit Clock Enable */
DECL|macro|CKEN3_SSP2
mdefine_line|#define CKEN3_SSP2&t;(1 &lt;&lt; 3)&t;/* SSP2 Unit Clock Enable */
DECL|macro|CKEN2_AC97
mdefine_line|#define CKEN2_AC97&t;(1 &lt;&lt; 2)&t;/* AC97 Unit Clock Enable */
DECL|macro|CKEN1_PWM1
mdefine_line|#define CKEN1_PWM1&t;(1 &lt;&lt; 1)&t;/* PWM1 Clock Enable */
DECL|macro|CKEN0_PWM0
mdefine_line|#define CKEN0_PWM0&t;(1 &lt;&lt; 0)&t;/* PWM0 Clock Enable */
DECL|macro|OSCC_OON
mdefine_line|#define OSCC_OON&t;(1 &lt;&lt; 1)&t;/* 32.768kHz OON (write-once only bit) */
DECL|macro|OSCC_OOK
mdefine_line|#define OSCC_OOK&t;(1 &lt;&lt; 0)&t;/* 32.768kHz OOK (read-only bit) */
multiline_comment|/*&n; * LCD&n; */
DECL|macro|LCCR0
mdefine_line|#define LCCR0&t;&t;__REG(0x44000000)  /* LCD Controller Control Register 0 */
DECL|macro|LCCR1
mdefine_line|#define LCCR1&t;&t;__REG(0x44000004)  /* LCD Controller Control Register 1 */
DECL|macro|LCCR2
mdefine_line|#define LCCR2&t;&t;__REG(0x44000008)  /* LCD Controller Control Register 2 */
DECL|macro|LCCR3
mdefine_line|#define LCCR3&t;&t;__REG(0x4400000C)  /* LCD Controller Control Register 3 */
DECL|macro|DFBR0
mdefine_line|#define DFBR0&t;&t;__REG(0x44000020)  /* DMA Channel 0 Frame Branch Register */
DECL|macro|DFBR1
mdefine_line|#define DFBR1&t;&t;__REG(0x44000024)  /* DMA Channel 1 Frame Branch Register */
DECL|macro|LCSR
mdefine_line|#define LCSR&t;&t;__REG(0x44000038)  /* LCD Controller Status Register */
DECL|macro|LIIDR
mdefine_line|#define LIIDR&t;&t;__REG(0x4400003C)  /* LCD Controller Interrupt ID Register */
DECL|macro|TMEDRGBR
mdefine_line|#define TMEDRGBR&t;__REG(0x44000040)  /* TMED RGB Seed Register */
DECL|macro|TMEDCR
mdefine_line|#define TMEDCR&t;&t;__REG(0x44000044)  /* TMED Control Register */
DECL|macro|LCCR3_1BPP
mdefine_line|#define LCCR3_1BPP (0 &lt;&lt; 24)
DECL|macro|LCCR3_2BPP
mdefine_line|#define LCCR3_2BPP (1 &lt;&lt; 24)
DECL|macro|LCCR3_4BPP
mdefine_line|#define LCCR3_4BPP (2 &lt;&lt; 24)
DECL|macro|LCCR3_8BPP
mdefine_line|#define LCCR3_8BPP (3 &lt;&lt; 24)
DECL|macro|LCCR3_16BPP
mdefine_line|#define LCCR3_16BPP (4 &lt;&lt; 24)
DECL|macro|FDADR0
mdefine_line|#define FDADR0&t;&t;__REG(0x44000200)  /* DMA Channel 0 Frame Descriptor Address Register */
DECL|macro|FSADR0
mdefine_line|#define FSADR0&t;&t;__REG(0x44000204)  /* DMA Channel 0 Frame Source Address Register */
DECL|macro|FIDR0
mdefine_line|#define FIDR0&t;&t;__REG(0x44000208)  /* DMA Channel 0 Frame ID Register */
DECL|macro|LDCMD0
mdefine_line|#define LDCMD0&t;&t;__REG(0x4400020C)  /* DMA Channel 0 Command Register */
DECL|macro|FDADR1
mdefine_line|#define FDADR1&t;&t;__REG(0x44000210)  /* DMA Channel 1 Frame Descriptor Address Register */
DECL|macro|FSADR1
mdefine_line|#define FSADR1&t;&t;__REG(0x44000214)  /* DMA Channel 1 Frame Source Address Register */
DECL|macro|FIDR1
mdefine_line|#define FIDR1&t;&t;__REG(0x44000218)  /* DMA Channel 1 Frame ID Register */
DECL|macro|LDCMD1
mdefine_line|#define LDCMD1&t;&t;__REG(0x4400021C)  /* DMA Channel 1 Command Register */
DECL|macro|LCCR0_ENB
mdefine_line|#define LCCR0_ENB&t;(1 &lt;&lt; 0)&t;/* LCD Controller enable */
DECL|macro|LCCR0_CMS
mdefine_line|#define LCCR0_CMS&t;(1 &lt;&lt; 1)&t;/* Color/Monochrome Display Select */
DECL|macro|LCCR0_Color
mdefine_line|#define LCCR0_Color     (LCCR0_CMS*0)   /*  Color display                  */
DECL|macro|LCCR0_Mono
mdefine_line|#define LCCR0_Mono      (LCCR0_CMS*1)   /*  Monochrome display             */
DECL|macro|LCCR0_SDS
mdefine_line|#define LCCR0_SDS&t;(1 &lt;&lt; 2)&t;/* Single/Dual Panel Display       */
multiline_comment|/* Select                          */
DECL|macro|LCCR0_Sngl
mdefine_line|#define LCCR0_Sngl      (LCCR0_SDS*0)   /*  Single panel display           */
DECL|macro|LCCR0_Dual
mdefine_line|#define LCCR0_Dual      (LCCR0_SDS*1)   /*  Dual panel display             */
DECL|macro|LCCR0_LDM
mdefine_line|#define LCCR0_LDM&t;(1 &lt;&lt; 3)&t;/* LCD Disable Done Mask */
DECL|macro|LCCR0_SFM
mdefine_line|#define LCCR0_SFM&t;(1 &lt;&lt; 4)&t;/* Start of frame mask */
DECL|macro|LCCR0_IUM
mdefine_line|#define LCCR0_IUM&t;(1 &lt;&lt; 5)&t;/* Input FIFO underrun mask */
DECL|macro|LCCR0_EFM
mdefine_line|#define LCCR0_EFM&t;(1 &lt;&lt; 6)&t;/* End of Frame mask */
DECL|macro|LCCR0_PAS
mdefine_line|#define LCCR0_PAS&t;(1 &lt;&lt; 7)&t;/* Passive/Active display Select   */
DECL|macro|LCCR0_Pas
mdefine_line|#define LCCR0_Pas       (LCCR0_PAS*0)   /*  Passive display (STN)          */
DECL|macro|LCCR0_Act
mdefine_line|#define LCCR0_Act       (LCCR0_PAS*1)   /*  Active display (TFT)           */
DECL|macro|LCCR0_DPD
mdefine_line|#define LCCR0_DPD&t;(1 &lt;&lt; 9)&t;/* Double Pixel Data (monochrome   */
multiline_comment|/* display mode)                   */
DECL|macro|LCCR0_4PixMono
mdefine_line|#define LCCR0_4PixMono  (LCCR0_DPD*0)   /*  4-Pixel/clock Monochrome       */
multiline_comment|/*  display                        */
DECL|macro|LCCR0_8PixMono
mdefine_line|#define LCCR0_8PixMono  (LCCR0_DPD*1)   /*  8-Pixel/clock Monochrome       */
multiline_comment|/*  display                        */
DECL|macro|LCCR0_DIS
mdefine_line|#define LCCR0_DIS&t;(1 &lt;&lt; 10)&t;/* LCD Disable */
DECL|macro|LCCR0_QDM
mdefine_line|#define LCCR0_QDM&t;(1 &lt;&lt; 11)&t;/* LCD Quick Disable mask */
DECL|macro|LCCR0_PDD
mdefine_line|#define LCCR0_PDD&t;(0xff &lt;&lt; 12)&t;/* Palette DMA request delay */
DECL|macro|LCCR0_PDD_S
mdefine_line|#define LCCR0_PDD_S&t;12
DECL|macro|LCCR0_BM
mdefine_line|#define LCCR0_BM&t;(1 &lt;&lt; 20) &t;/* Branch mask */
DECL|macro|LCCR0_OUM
mdefine_line|#define LCCR0_OUM&t;(1 &lt;&lt; 21)&t;/* Output FIFO underrun mask */
DECL|macro|LCCR1_PPL
mdefine_line|#define LCCR1_PPL       Fld (10, 0)      /* Pixels Per Line - 1 */
DECL|macro|LCCR1_DisWdth
mdefine_line|#define LCCR1_DisWdth(Pixel)            /* Display Width [1..800 pix.]  */ &bslash;&n;                        (((Pixel) - 1) &lt;&lt; FShft (LCCR1_PPL))
DECL|macro|LCCR1_HSW
mdefine_line|#define LCCR1_HSW       Fld (6, 10)     /* Horizontal Synchronization     */
DECL|macro|LCCR1_HorSnchWdth
mdefine_line|#define LCCR1_HorSnchWdth(Tpix)         /* Horizontal Synchronization     */ &bslash;&n;                                        /* pulse Width [1..64 Tpix]       */ &bslash;&n;                        (((Tpix) - 1) &lt;&lt; FShft (LCCR1_HSW))
DECL|macro|LCCR1_ELW
mdefine_line|#define LCCR1_ELW       Fld (8, 16)     /* End-of-Line pixel clock Wait    */
multiline_comment|/* count - 1 [Tpix]                */
DECL|macro|LCCR1_EndLnDel
mdefine_line|#define LCCR1_EndLnDel(Tpix)            /*  End-of-Line Delay              */ &bslash;&n;                                        /*  [1..256 Tpix]                  */ &bslash;&n;                        (((Tpix) - 1) &lt;&lt; FShft (LCCR1_ELW))
DECL|macro|LCCR1_BLW
mdefine_line|#define LCCR1_BLW       Fld (8, 24)     /* Beginning-of-Line pixel clock   */
multiline_comment|/* Wait count - 1 [Tpix]           */
DECL|macro|LCCR1_BegLnDel
mdefine_line|#define LCCR1_BegLnDel(Tpix)            /*  Beginning-of-Line Delay        */ &bslash;&n;                                        /*  [1..256 Tpix]                  */ &bslash;&n;                        (((Tpix) - 1) &lt;&lt; FShft (LCCR1_BLW))
DECL|macro|LCCR2_LPP
mdefine_line|#define LCCR2_LPP       Fld (10, 0)     /* Line Per Panel - 1              */
DECL|macro|LCCR2_DisHght
mdefine_line|#define LCCR2_DisHght(Line)             /*  Display Height [1..1024 lines] */ &bslash;&n;                        (((Line) - 1) &lt;&lt; FShft (LCCR2_LPP))
DECL|macro|LCCR2_VSW
mdefine_line|#define LCCR2_VSW       Fld (6, 10)     /* Vertical Synchronization pulse  */
multiline_comment|/* Width - 1 [Tln] (L_FCLK)        */
DECL|macro|LCCR2_VrtSnchWdth
mdefine_line|#define LCCR2_VrtSnchWdth(Tln)          /*  Vertical Synchronization pulse */ &bslash;&n;                                        /*  Width [1..64 Tln]              */ &bslash;&n;                        (((Tln) - 1) &lt;&lt; FShft (LCCR2_VSW))
DECL|macro|LCCR2_EFW
mdefine_line|#define LCCR2_EFW       Fld (8, 16)     /* End-of-Frame line clock Wait    */
multiline_comment|/* count [Tln]                     */
DECL|macro|LCCR2_EndFrmDel
mdefine_line|#define LCCR2_EndFrmDel(Tln)            /*  End-of-Frame Delay             */ &bslash;&n;                                        /*  [0..255 Tln]                   */ &bslash;&n;                        ((Tln) &lt;&lt; FShft (LCCR2_EFW))
DECL|macro|LCCR2_BFW
mdefine_line|#define LCCR2_BFW       Fld (8, 24)     /* Beginning-of-Frame line clock   */
multiline_comment|/* Wait count [Tln]                */
DECL|macro|LCCR2_BegFrmDel
mdefine_line|#define LCCR2_BegFrmDel(Tln)            /*  Beginning-of-Frame Delay       */ &bslash;&n;                                        /*  [0..255 Tln]                   */ &bslash;&n;                        ((Tln) &lt;&lt; FShft (LCCR2_BFW))
macro_line|#if 0
mdefine_line|#define LCCR3_PCD&t;(0xff)&t;&t;/* Pixel clock divisor */
mdefine_line|#define LCCR3_ACB&t;(0xff &lt;&lt; 8)&t;/* AC Bias pin frequency */
mdefine_line|#define LCCR3_ACB_S&t;8
macro_line|#endif
DECL|macro|LCCR3_API
mdefine_line|#define LCCR3_API&t;(0xf &lt;&lt; 16)&t;/* AC Bias pin trasitions per interrupt */
DECL|macro|LCCR3_API_S
mdefine_line|#define LCCR3_API_S&t;16
DECL|macro|LCCR3_VSP
mdefine_line|#define LCCR3_VSP&t;(1 &lt;&lt; 20)&t;/* vertical sync polarity */
DECL|macro|LCCR3_HSP
mdefine_line|#define LCCR3_HSP&t;(1 &lt;&lt; 21)&t;/* horizontal sync polarity */
DECL|macro|LCCR3_PCP
mdefine_line|#define LCCR3_PCP&t;(1 &lt;&lt; 22)&t;/* Pixel Clock Polarity (L_PCLK)   */
DECL|macro|LCCR3_PixRsEdg
mdefine_line|#define LCCR3_PixRsEdg  (LCCR3_PCP*0)   /*  Pixel clock Rising-Edge        */
DECL|macro|LCCR3_PixFlEdg
mdefine_line|#define LCCR3_PixFlEdg  (LCCR3_PCP*1)   /*  Pixel clock Falling-Edge       */
DECL|macro|LCCR3_OEP
mdefine_line|#define LCCR3_OEP       (1 &lt;&lt; 23)       /* Output Enable Polarity (L_BIAS, */
multiline_comment|/* active display mode)            */
DECL|macro|LCCR3_OutEnH
mdefine_line|#define LCCR3_OutEnH    (LCCR3_OEP*0)   /*  Output Enable active High      */
DECL|macro|LCCR3_OutEnL
mdefine_line|#define LCCR3_OutEnL    (LCCR3_OEP*1)   /*  Output Enable active Low       */
macro_line|#if 0
mdefine_line|#define LCCR3_BPP&t;(7 &lt;&lt; 24)&t;/* bits per pixel */
mdefine_line|#define LCCR3_BPP_S&t;24
macro_line|#endif
DECL|macro|LCCR3_DPC
mdefine_line|#define LCCR3_DPC&t;(1 &lt;&lt; 27)&t;/* double pixel clock mode */
DECL|macro|LCCR3_PCD
mdefine_line|#define LCCR3_PCD       Fld (8, 0)      /* Pixel Clock Divisor */
DECL|macro|LCCR3_PixClkDiv
mdefine_line|#define LCCR3_PixClkDiv(Div)            /* Pixel Clock Divisor */ &bslash;&n;                        (((Div) &lt;&lt; FShft (LCCR3_PCD)))
DECL|macro|LCCR3_BPP
mdefine_line|#define LCCR3_BPP       Fld (3, 24)     /* Bit Per Pixel */
DECL|macro|LCCR3_Bpp
mdefine_line|#define LCCR3_Bpp(Bpp)                  /* Bit Per Pixel */ &bslash;&n;                        (((Bpp) &lt;&lt; FShft (LCCR3_BPP)))
DECL|macro|LCCR3_ACB
mdefine_line|#define LCCR3_ACB       Fld (8, 8)      /* AC Bias */
DECL|macro|LCCR3_Acb
mdefine_line|#define LCCR3_Acb(Acb)                  /* BAC Bias */ &bslash;&n;                        (((Acb) &lt;&lt; FShft (LCCR3_ACB)))
DECL|macro|LCCR3_HorSnchH
mdefine_line|#define LCCR3_HorSnchH  (LCCR3_HSP*0)   /*  Horizontal Synchronization     */
multiline_comment|/*  pulse active High              */
DECL|macro|LCCR3_HorSnchL
mdefine_line|#define LCCR3_HorSnchL  (LCCR3_HSP*1)   /*  Horizontal Synchronization     */
DECL|macro|LCCR3_VrtSnchH
mdefine_line|#define LCCR3_VrtSnchH  (LCCR3_VSP*0)   /*  Vertical Synchronization pulse */
multiline_comment|/*  active High                    */
DECL|macro|LCCR3_VrtSnchL
mdefine_line|#define LCCR3_VrtSnchL  (LCCR3_VSP*1)   /*  Vertical Synchronization pulse */
multiline_comment|/*  active Low                     */
DECL|macro|LCSR_LDD
mdefine_line|#define LCSR_LDD&t;(1 &lt;&lt; 0)&t;/* LCD Disable Done */
DECL|macro|LCSR_SOF
mdefine_line|#define LCSR_SOF&t;(1 &lt;&lt; 1)&t;/* Start of frame */
DECL|macro|LCSR_BER
mdefine_line|#define LCSR_BER&t;(1 &lt;&lt; 2)&t;/* Bus error */
DECL|macro|LCSR_ABC
mdefine_line|#define LCSR_ABC&t;(1 &lt;&lt; 3)&t;/* AC Bias count */
DECL|macro|LCSR_IUL
mdefine_line|#define LCSR_IUL&t;(1 &lt;&lt; 4)&t;/* input FIFO underrun Lower panel */
DECL|macro|LCSR_IUU
mdefine_line|#define LCSR_IUU&t;(1 &lt;&lt; 5)&t;/* input FIFO underrun Upper panel */
DECL|macro|LCSR_OU
mdefine_line|#define LCSR_OU&t;&t;(1 &lt;&lt; 6)&t;/* output FIFO underrun */
DECL|macro|LCSR_QD
mdefine_line|#define LCSR_QD&t;&t;(1 &lt;&lt; 7)&t;/* quick disable */
DECL|macro|LCSR_EOF
mdefine_line|#define LCSR_EOF&t;(1 &lt;&lt; 8)&t;/* end of frame */
DECL|macro|LCSR_BS
mdefine_line|#define LCSR_BS&t;&t;(1 &lt;&lt; 9)&t;/* branch status */
DECL|macro|LCSR_SINT
mdefine_line|#define LCSR_SINT&t;(1 &lt;&lt; 10)&t;/* subsequent interrupt */
DECL|macro|LDCMD_PAL
mdefine_line|#define LDCMD_PAL&t;(1 &lt;&lt; 26)&t;/* instructs DMA to load palette buffer */
DECL|macro|LCSR_LDD
mdefine_line|#define LCSR_LDD&t;(1 &lt;&lt; 0)&t;/* LCD Disable Done */
DECL|macro|LCSR_SOF
mdefine_line|#define LCSR_SOF&t;(1 &lt;&lt; 1)&t;/* Start of frame */
DECL|macro|LCSR_BER
mdefine_line|#define LCSR_BER&t;(1 &lt;&lt; 2)&t;/* Bus error */
DECL|macro|LCSR_ABC
mdefine_line|#define LCSR_ABC&t;(1 &lt;&lt; 3)&t;/* AC Bias count */
DECL|macro|LCSR_IUL
mdefine_line|#define LCSR_IUL&t;(1 &lt;&lt; 4)&t;/* input FIFO underrun Lower panel */
DECL|macro|LCSR_IUU
mdefine_line|#define LCSR_IUU&t;(1 &lt;&lt; 5)&t;/* input FIFO underrun Upper panel */
DECL|macro|LCSR_OU
mdefine_line|#define LCSR_OU&t;&t;(1 &lt;&lt; 6)&t;/* output FIFO underrun */
DECL|macro|LCSR_QD
mdefine_line|#define LCSR_QD&t;&t;(1 &lt;&lt; 7)&t;/* quick disable */
DECL|macro|LCSR_EOF
mdefine_line|#define LCSR_EOF&t;(1 &lt;&lt; 8)&t;/* end of frame */
DECL|macro|LCSR_BS
mdefine_line|#define LCSR_BS&t;&t;(1 &lt;&lt; 9)&t;/* branch status */
DECL|macro|LCSR_SINT
mdefine_line|#define LCSR_SINT&t;(1 &lt;&lt; 10)&t;/* subsequent interrupt */
DECL|macro|LDCMD_PAL
mdefine_line|#define LDCMD_PAL&t;(1 &lt;&lt; 26)&t;/* instructs DMA to load palette buffer */
multiline_comment|/*&n; * Memory controller&n; */
DECL|macro|MDCNFG
mdefine_line|#define MDCNFG&t;&t;__REG(0x48000000)  /* SDRAM Configuration Register 0 */
DECL|macro|MDREFR
mdefine_line|#define MDREFR&t;&t;__REG(0x48000004)  /* SDRAM Refresh Control Register */
DECL|macro|MSC0
mdefine_line|#define MSC0&t;&t;__REG(0x48000008)  /* Static Memory Control Register 0 */
DECL|macro|MSC1
mdefine_line|#define MSC1&t;&t;__REG(0x4800000C)  /* Static Memory Control Register 1 */
DECL|macro|MSC2
mdefine_line|#define MSC2&t;&t;__REG(0x48000010)  /* Static Memory Control Register 2 */
DECL|macro|MECR
mdefine_line|#define MECR&t;&t;__REG(0x48000014)  /* Expansion Memory (PCMCIA/Compact Flash) Bus Configuration */
DECL|macro|SXLCR
mdefine_line|#define SXLCR&t;&t;__REG(0x48000018)  /* LCR value to be written to SDRAM-Timing Synchronous Flash */
DECL|macro|SXCNFG
mdefine_line|#define SXCNFG&t;&t;__REG(0x4800001C)  /* Synchronous Static Memory Control Register */
DECL|macro|SXMRS
mdefine_line|#define SXMRS&t;&t;__REG(0x48000024)  /* MRS value to be written to Synchronous Flash or SMROM */
DECL|macro|MCMEM0
mdefine_line|#define MCMEM0&t;&t;__REG(0x48000028)  /* Card interface Common Memory Space Socket 0 Timing */
DECL|macro|MCMEM1
mdefine_line|#define MCMEM1&t;&t;__REG(0x4800002C)  /* Card interface Common Memory Space Socket 1 Timing */
DECL|macro|MCATT0
mdefine_line|#define MCATT0&t;&t;__REG(0x48000030)  /* Card interface Attribute Space Socket 0 Timing Configuration */
DECL|macro|MCATT1
mdefine_line|#define MCATT1&t;&t;__REG(0x48000034)  /* Card interface Attribute Space Socket 1 Timing Configuration */
DECL|macro|MCIO0
mdefine_line|#define MCIO0&t;&t;__REG(0x48000038)  /* Card interface I/O Space Socket 0 Timing Configuration */
DECL|macro|MCIO1
mdefine_line|#define MCIO1&t;&t;__REG(0x4800003C)  /* Card interface I/O Space Socket 1 Timing Configuration */
DECL|macro|MDMRS
mdefine_line|#define MDMRS&t;&t;__REG(0x48000040)  /* MRS value to be written to SDRAM */
DECL|macro|BOOT_DEF
mdefine_line|#define BOOT_DEF&t;__REG(0x48000044)  /* Read-Only Boot-Time Register. Contains BOOT_SEL and PKG_SEL */
multiline_comment|/*&n; * More handy macros for PCMCIA&n; *&n; * Arg is socket number&n; */
DECL|macro|MCMEM
mdefine_line|#define MCMEM(s)&t;__REG2(0x48000028, (s)&lt;&lt;2 )  /* Card interface Common Memory Space Socket s Timing */
DECL|macro|MCATT
mdefine_line|#define MCATT(s)&t;__REG2(0x48000030, (s)&lt;&lt;2 )  /* Card interface Attribute Space Socket s Timing Configuration */
DECL|macro|MCIO
mdefine_line|#define MCIO(s)&t;&t;__REG2(0x48000038, (s)&lt;&lt;2 )  /* Card interface I/O Space Socket s Timing Configuration */
multiline_comment|/* MECR register defines */
DECL|macro|MECR_NOS
mdefine_line|#define MECR_NOS&t;(1 &lt;&lt; 0)&t;/* Number Of Sockets: 0 -&gt; 1 sock, 1 -&gt; 2 sock */
DECL|macro|MECR_CIT
mdefine_line|#define MECR_CIT&t;(1 &lt;&lt; 1)&t;/* Card Is There: 0 -&gt; no card, 1 -&gt; card inserted */
DECL|macro|MDREFR_K2FREE
mdefine_line|#define MDREFR_K2FREE&t;(1 &lt;&lt; 25)&t;/* SDRAM Free-Running Control */
DECL|macro|MDREFR_K1FREE
mdefine_line|#define MDREFR_K1FREE&t;(1 &lt;&lt; 24)&t;/* SDRAM Free-Running Control */
DECL|macro|MDREFR_K0FREE
mdefine_line|#define MDREFR_K0FREE&t;(1 &lt;&lt; 23)&t;/* SDRAM Free-Running Control */
DECL|macro|MDREFR_SLFRSH
mdefine_line|#define MDREFR_SLFRSH&t;(1 &lt;&lt; 22)&t;/* SDRAM Self-Refresh Control/Status */
DECL|macro|MDREFR_APD
mdefine_line|#define MDREFR_APD&t;(1 &lt;&lt; 20)&t;/* SDRAM/SSRAM Auto-Power-Down Enable */
DECL|macro|MDREFR_K2DB2
mdefine_line|#define MDREFR_K2DB2&t;(1 &lt;&lt; 19)&t;/* SDCLK2 Divide by 2 Control/Status */
DECL|macro|MDREFR_K2RUN
mdefine_line|#define MDREFR_K2RUN&t;(1 &lt;&lt; 18)&t;/* SDCLK2 Run Control/Status */
DECL|macro|MDREFR_K1DB2
mdefine_line|#define MDREFR_K1DB2&t;(1 &lt;&lt; 17)&t;/* SDCLK1 Divide by 2 Control/Status */
DECL|macro|MDREFR_K1RUN
mdefine_line|#define MDREFR_K1RUN&t;(1 &lt;&lt; 16)&t;/* SDCLK1 Run Control/Status */
DECL|macro|MDREFR_E1PIN
mdefine_line|#define MDREFR_E1PIN&t;(1 &lt;&lt; 15)&t;/* SDCKE1 Level Control/Status */
DECL|macro|MDREFR_K0DB2
mdefine_line|#define MDREFR_K0DB2&t;(1 &lt;&lt; 14)&t;/* SDCLK0 Divide by 2 Control/Status */
DECL|macro|MDREFR_K0RUN
mdefine_line|#define MDREFR_K0RUN&t;(1 &lt;&lt; 13)&t;/* SDCLK0 Run Control/Status */
DECL|macro|MDREFR_E0PIN
mdefine_line|#define MDREFR_E0PIN&t;(1 &lt;&lt; 12)&t;/* SDCKE0 Level Control/Status */
macro_line|#ifdef CONFIG_PXA27x
multiline_comment|/*&n; * Keypad&n; */
DECL|macro|KPC
mdefine_line|#define KPC             __REG(0x41500000) /* Keypad Interface Control register */
DECL|macro|KPDK
mdefine_line|#define KPDK            __REG(0x41500008) /* Keypad Interface Direct Key register */
DECL|macro|KPREC
mdefine_line|#define KPREC           __REG(0x41500010) /* Keypad Interface Rotary Encoder register */
DECL|macro|KPMK
mdefine_line|#define KPMK            __REG(0x41500018) /* Keypad Interface Matrix Key register */
DECL|macro|KPAS
mdefine_line|#define KPAS            __REG(0x41500020) /* Keypad Interface Automatic Scan register */
DECL|macro|KPASMKP0
mdefine_line|#define KPASMKP0        __REG(0x41500028) /* Keypad Interface Automatic Scan Multiple Key Presser register 0 */
DECL|macro|KPASMKP1
mdefine_line|#define KPASMKP1        __REG(0x41500030) /* Keypad Interface Automatic Scan Multiple Key Presser register 1 */
DECL|macro|KPASMKP2
mdefine_line|#define KPASMKP2        __REG(0x41500038) /* Keypad Interface Automatic Scan Multiple Key Presser register 2 */
DECL|macro|KPASMKP3
mdefine_line|#define KPASMKP3        __REG(0x41500040) /* Keypad Interface Automatic Scan Multiple Key Presser register 3 */
DECL|macro|KPKDI
mdefine_line|#define KPKDI           __REG(0x41500048) /* Keypad Interface Key Debounce Interval register */
DECL|macro|KPC_AS
mdefine_line|#define KPC_AS          (0x1 &lt;&lt; 30)  /* Automatic Scan bit */
DECL|macro|KPC_ASACT
mdefine_line|#define KPC_ASACT       (0x1 &lt;&lt; 29)  /* Automatic Scan on Activity */
DECL|macro|KPC_MI
mdefine_line|#define KPC_MI          (0x1 &lt;&lt; 22)  /* Matrix interrupt bit */
DECL|macro|KPC_IMKP
mdefine_line|#define KPC_IMKP        (0x1 &lt;&lt; 21)  /* Ignore Multiple Key Press */
DECL|macro|KPC_MS7
mdefine_line|#define KPC_MS7         (0x1 &lt;&lt; 20)  /* Matrix scan line 7 */
DECL|macro|KPC_MS6
mdefine_line|#define KPC_MS6         (0x1 &lt;&lt; 19)  /* Matrix scan line 6 */
DECL|macro|KPC_MS5
mdefine_line|#define KPC_MS5         (0x1 &lt;&lt; 18)  /* Matrix scan line 5 */
DECL|macro|KPC_MS4
mdefine_line|#define KPC_MS4         (0x1 &lt;&lt; 17)  /* Matrix scan line 4 */
DECL|macro|KPC_MS3
mdefine_line|#define KPC_MS3         (0x1 &lt;&lt; 16)  /* Matrix scan line 3 */
DECL|macro|KPC_MS2
mdefine_line|#define KPC_MS2         (0x1 &lt;&lt; 15)  /* Matrix scan line 2 */
DECL|macro|KPC_MS1
mdefine_line|#define KPC_MS1         (0x1 &lt;&lt; 14)  /* Matrix scan line 1 */
DECL|macro|KPC_MS0
mdefine_line|#define KPC_MS0         (0x1 &lt;&lt; 13)  /* Matrix scan line 0 */
DECL|macro|KPC_MS_ALL
mdefine_line|#define KPC_MS_ALL      (KPC_MS0 | KPC_MS1 | KPC_MS2 | KPC_MS3 | KPC_MS4 | KPC_MS5 | KPC_MS6 | KPC_MS7)
DECL|macro|KPC_ME
mdefine_line|#define KPC_ME          (0x1 &lt;&lt; 12)  /* Matrix Keypad Enable */
DECL|macro|KPC_MIE
mdefine_line|#define KPC_MIE         (0x1 &lt;&lt; 11)  /* Matrix Interrupt Enable */
DECL|macro|KPC_DK_DEB_SEL
mdefine_line|#define KPC_DK_DEB_SEL&t;(0x1 &lt;&lt;  9)  /* Direct Keypad Debounce Select */
DECL|macro|KPC_DI
mdefine_line|#define KPC_DI          (0x1 &lt;&lt;  5)  /* Direct key interrupt bit */
DECL|macro|KPC_RE_ZERO_DEB
mdefine_line|#define KPC_RE_ZERO_DEB (0x1 &lt;&lt;  4)  /* Rotary Encoder Zero Debounce */
DECL|macro|KPC_REE1
mdefine_line|#define KPC_REE1        (0x1 &lt;&lt;  3)  /* Rotary Encoder1 Enable */
DECL|macro|KPC_REE0
mdefine_line|#define KPC_REE0        (0x1 &lt;&lt;  2)  /* Rotary Encoder0 Enable */
DECL|macro|KPC_DE
mdefine_line|#define KPC_DE          (0x1 &lt;&lt;  1)  /* Direct Keypad Enable */
DECL|macro|KPC_DIE
mdefine_line|#define KPC_DIE         (0x1 &lt;&lt;  0)  /* Direct Keypad interrupt Enable */
DECL|macro|KPDK_DKP
mdefine_line|#define KPDK_DKP        (0x1 &lt;&lt; 31)
DECL|macro|KPDK_DK7
mdefine_line|#define KPDK_DK7        (0x1 &lt;&lt;  7)
DECL|macro|KPDK_DK6
mdefine_line|#define KPDK_DK6        (0x1 &lt;&lt;  6)
DECL|macro|KPDK_DK5
mdefine_line|#define KPDK_DK5        (0x1 &lt;&lt;  5)
DECL|macro|KPDK_DK4
mdefine_line|#define KPDK_DK4        (0x1 &lt;&lt;  4)
DECL|macro|KPDK_DK3
mdefine_line|#define KPDK_DK3        (0x1 &lt;&lt;  3)
DECL|macro|KPDK_DK2
mdefine_line|#define KPDK_DK2        (0x1 &lt;&lt;  2)
DECL|macro|KPDK_DK1
mdefine_line|#define KPDK_DK1        (0x1 &lt;&lt;  1)
DECL|macro|KPDK_DK0
mdefine_line|#define KPDK_DK0        (0x1 &lt;&lt;  0)
DECL|macro|KPREC_OF1
mdefine_line|#define KPREC_OF1       (0x1 &lt;&lt; 31)
DECL|macro|kPREC_UF1
mdefine_line|#define kPREC_UF1       (0x1 &lt;&lt; 30)
DECL|macro|KPREC_OF0
mdefine_line|#define KPREC_OF0       (0x1 &lt;&lt; 15)
DECL|macro|KPREC_UF0
mdefine_line|#define KPREC_UF0       (0x1 &lt;&lt; 14)
DECL|macro|KPMK_MKP
mdefine_line|#define KPMK_MKP        (0x1 &lt;&lt; 31)
DECL|macro|KPAS_SO
mdefine_line|#define KPAS_SO         (0x1 &lt;&lt; 31)
DECL|macro|KPASMKPx_SO
mdefine_line|#define KPASMKPx_SO     (0x1 &lt;&lt; 31)
multiline_comment|/*&n; * UHC: USB Host Controller (OHCI-like) register definitions&n; */
DECL|macro|UHC_BASE_PHYS
mdefine_line|#define UHC_BASE_PHYS&t;(0x4C000000)
DECL|macro|UHCREV
mdefine_line|#define UHCREV&t;&t;__REG(0x4C000000) /* UHC HCI Spec Revision */
DECL|macro|UHCHCON
mdefine_line|#define UHCHCON&t;&t;__REG(0x4C000004) /* UHC Host Control Register */
DECL|macro|UHCCOMS
mdefine_line|#define UHCCOMS&t;&t;__REG(0x4C000008) /* UHC Command Status Register */
DECL|macro|UHCINTS
mdefine_line|#define UHCINTS&t;&t;__REG(0x4C00000C) /* UHC Interrupt Status Register */
DECL|macro|UHCINTE
mdefine_line|#define UHCINTE&t;&t;__REG(0x4C000010) /* UHC Interrupt Enable */
DECL|macro|UHCINTD
mdefine_line|#define UHCINTD&t;&t;__REG(0x4C000014) /* UHC Interrupt Disable */
DECL|macro|UHCHCCA
mdefine_line|#define UHCHCCA&t;&t;__REG(0x4C000018) /* UHC Host Controller Comm. Area */
DECL|macro|UHCPCED
mdefine_line|#define UHCPCED&t;&t;__REG(0x4C00001C) /* UHC Period Current Endpt Descr */
DECL|macro|UHCCHED
mdefine_line|#define UHCCHED&t;&t;__REG(0x4C000020) /* UHC Control Head Endpt Descr */
DECL|macro|UHCCCED
mdefine_line|#define UHCCCED&t;&t;__REG(0x4C000024) /* UHC Control Current Endpt Descr */
DECL|macro|UHCBHED
mdefine_line|#define UHCBHED&t;&t;__REG(0x4C000028) /* UHC Bulk Head Endpt Descr */
DECL|macro|UHCBCED
mdefine_line|#define UHCBCED&t;&t;__REG(0x4C00002C) /* UHC Bulk Current Endpt Descr */
DECL|macro|UHCDHEAD
mdefine_line|#define UHCDHEAD&t;__REG(0x4C000030) /* UHC Done Head */
DECL|macro|UHCFMI
mdefine_line|#define UHCFMI&t;&t;__REG(0x4C000034) /* UHC Frame Interval */
DECL|macro|UHCFMR
mdefine_line|#define UHCFMR&t;&t;__REG(0x4C000038) /* UHC Frame Remaining */
DECL|macro|UHCFMN
mdefine_line|#define UHCFMN&t;&t;__REG(0x4C00003C) /* UHC Frame Number */
DECL|macro|UHCPERS
mdefine_line|#define UHCPERS&t;&t;__REG(0x4C000040) /* UHC Periodic Start */
DECL|macro|UHCLS
mdefine_line|#define UHCLS&t;&t;__REG(0x4C000044) /* UHC Low Speed Threshold */
DECL|macro|UHCRHDA
mdefine_line|#define UHCRHDA&t;&t;__REG(0x4C000048) /* UHC Root Hub Descriptor A */
DECL|macro|UHCRHDB
mdefine_line|#define UHCRHDB&t;&t;__REG(0x4C00004C) /* UHC Root Hub Descriptor B */
DECL|macro|UHCRHS
mdefine_line|#define UHCRHS&t;&t;__REG(0x4C000050) /* UHC Root Hub Status */
DECL|macro|UHCRHPS1
mdefine_line|#define UHCRHPS1&t;__REG(0x4C000054) /* UHC Root Hub Port 1 Status */
DECL|macro|UHCRHPS2
mdefine_line|#define UHCRHPS2&t;__REG(0x4C000058) /* UHC Root Hub Port 2 Status */
DECL|macro|UHCRHPS3
mdefine_line|#define UHCRHPS3&t;__REG(0x4C00005C) /* UHC Root Hub Port 3 Status */
DECL|macro|UHCSTAT
mdefine_line|#define UHCSTAT&t;&t;__REG(0x4C000060) /* UHC Status Register */
DECL|macro|UHCSTAT_UPS3
mdefine_line|#define UHCSTAT_UPS3&t;(1 &lt;&lt; 16)&t;/* USB Power Sense Port3 */
DECL|macro|UHCSTAT_SBMAI
mdefine_line|#define UHCSTAT_SBMAI&t;(1 &lt;&lt; 15)&t;/* System Bus Master Abort Interrupt*/
DECL|macro|UHCSTAT_SBTAI
mdefine_line|#define UHCSTAT_SBTAI&t;(1 &lt;&lt; 14)&t;/* System Bus Target Abort Interrupt*/
DECL|macro|UHCSTAT_UPRI
mdefine_line|#define UHCSTAT_UPRI&t;(1 &lt;&lt; 13)&t;/* USB Port Resume Interrupt */
DECL|macro|UHCSTAT_UPS2
mdefine_line|#define UHCSTAT_UPS2&t;(1 &lt;&lt; 12)&t;/* USB Power Sense Port 2 */
DECL|macro|UHCSTAT_UPS1
mdefine_line|#define UHCSTAT_UPS1&t;(1 &lt;&lt; 11)&t;/* USB Power Sense Port 1 */
DECL|macro|UHCSTAT_HTA
mdefine_line|#define UHCSTAT_HTA&t;(1 &lt;&lt; 10)&t;/* HCI Target Abort */
DECL|macro|UHCSTAT_HBA
mdefine_line|#define UHCSTAT_HBA&t;(1 &lt;&lt; 8)&t;/* HCI Buffer Active */
DECL|macro|UHCSTAT_RWUE
mdefine_line|#define UHCSTAT_RWUE&t;(1 &lt;&lt; 7)&t;/* HCI Remote Wake Up Event */
DECL|macro|UHCHR
mdefine_line|#define UHCHR           __REG(0x4C000064) /* UHC Reset Register */
DECL|macro|UHCHR_SSEP3
mdefine_line|#define UHCHR_SSEP3&t;(1 &lt;&lt; 11)&t;/* Sleep Standby Enable for Port3 */
DECL|macro|UHCHR_SSEP2
mdefine_line|#define UHCHR_SSEP2&t;(1 &lt;&lt; 10)&t;/* Sleep Standby Enable for Port2 */
DECL|macro|UHCHR_SSEP1
mdefine_line|#define UHCHR_SSEP1&t;(1 &lt;&lt; 9)&t;/* Sleep Standby Enable for Port1 */
DECL|macro|UHCHR_PCPL
mdefine_line|#define UHCHR_PCPL&t;(1 &lt;&lt; 7)&t;/* Power control polarity low */
DECL|macro|UHCHR_PSPL
mdefine_line|#define UHCHR_PSPL&t;(1 &lt;&lt; 6)&t;/* Power sense polarity low */
DECL|macro|UHCHR_SSE
mdefine_line|#define UHCHR_SSE&t;(1 &lt;&lt; 5)&t;/* Sleep Standby Enable */
DECL|macro|UHCHR_UIT
mdefine_line|#define UHCHR_UIT&t;(1 &lt;&lt; 4)&t;/* USB Interrupt Test */
DECL|macro|UHCHR_SSDC
mdefine_line|#define UHCHR_SSDC&t;(1 &lt;&lt; 3)&t;/* Simulation Scale Down Clock */
DECL|macro|UHCHR_CGR
mdefine_line|#define UHCHR_CGR&t;(1 &lt;&lt; 2)&t;/* Clock Generation Reset */
DECL|macro|UHCHR_FHR
mdefine_line|#define UHCHR_FHR&t;(1 &lt;&lt; 1)&t;/* Force Host Controller Reset */
DECL|macro|UHCHR_FSBIR
mdefine_line|#define UHCHR_FSBIR&t;(1 &lt;&lt; 0)&t;/* Force System Bus Iface Reset */
DECL|macro|UHCHIE
mdefine_line|#define UHCHIE          __REG(0x4C000068) /* UHC Interrupt Enable Register*/
DECL|macro|UHCHIE_UPS3IE
mdefine_line|#define UHCHIE_UPS3IE&t;(1 &lt;&lt; 14)&t;/* Power Sense Port3 IntEn */
DECL|macro|UHCHIE_UPRIE
mdefine_line|#define UHCHIE_UPRIE&t;(1 &lt;&lt; 13)&t;/* Port Resume IntEn */
DECL|macro|UHCHIE_UPS2IE
mdefine_line|#define UHCHIE_UPS2IE&t;(1 &lt;&lt; 12)&t;/* Power Sense Port2 IntEn */
DECL|macro|UHCHIE_UPS1IE
mdefine_line|#define UHCHIE_UPS1IE&t;(1 &lt;&lt; 11)&t;/* Power Sense Port1 IntEn */
DECL|macro|UHCHIE_TAIE
mdefine_line|#define UHCHIE_TAIE&t;(1 &lt;&lt; 10)&t;/* HCI Interface Transfer Abort&n;&t;&t;&t;&t;&t;   Interrupt Enable*/
DECL|macro|UHCHIE_HBAIE
mdefine_line|#define UHCHIE_HBAIE&t;(1 &lt;&lt; 8)&t;/* HCI Buffer Active IntEn */
DECL|macro|UHCHIE_RWIE
mdefine_line|#define UHCHIE_RWIE&t;(1 &lt;&lt; 7)&t;/* Remote Wake-up IntEn */
DECL|macro|UHCHIT
mdefine_line|#define UHCHIT          __REG(0x4C00006C) /* UHC Interrupt Test register */
multiline_comment|/* Camera Interface */
DECL|macro|CICR0
mdefine_line|#define CICR0&t;&t;__REG(0x50000000)
DECL|macro|CICR1
mdefine_line|#define CICR1&t;&t;__REG(0x50000004)
DECL|macro|CICR2
mdefine_line|#define CICR2&t;&t;__REG(0x50000008)
DECL|macro|CICR3
mdefine_line|#define CICR3&t;&t;__REG(0x5000000C)
DECL|macro|CICR4
mdefine_line|#define CICR4&t;&t;__REG(0x50000010)
DECL|macro|CISR
mdefine_line|#define CISR&t;&t;__REG(0x50000014)
DECL|macro|CIFR
mdefine_line|#define CIFR&t;&t;__REG(0x50000018)
DECL|macro|CITOR
mdefine_line|#define CITOR&t;&t;__REG(0x5000001C)
DECL|macro|CIBR0
mdefine_line|#define CIBR0&t;&t;__REG(0x50000028)
DECL|macro|CIBR1
mdefine_line|#define CIBR1&t;&t;__REG(0x50000030)
DECL|macro|CIBR2
mdefine_line|#define CIBR2&t;&t;__REG(0x50000038)
DECL|macro|CICR0_DMAEN
mdefine_line|#define CICR0_DMAEN&t;(1 &lt;&lt; 31)&t;/* DMA request enable */
DECL|macro|CICR0_PAR_EN
mdefine_line|#define CICR0_PAR_EN&t;(1 &lt;&lt; 30)&t;/* Parity enable */
DECL|macro|CICR0_SL_CAP_EN
mdefine_line|#define CICR0_SL_CAP_EN&t;(1 &lt;&lt; 29)&t;/* Capture enable for slave mode */
DECL|macro|CICR0_ENB
mdefine_line|#define CICR0_ENB&t;(1 &lt;&lt; 28)&t;/* Camera interface enable */
DECL|macro|CICR0_DIS
mdefine_line|#define CICR0_DIS&t;(1 &lt;&lt; 27)&t;/* Camera interface disable */
DECL|macro|CICR0_SIM
mdefine_line|#define CICR0_SIM&t;(0x7 &lt;&lt; 24)&t;/* Sensor interface mode mask */
DECL|macro|CICR0_TOM
mdefine_line|#define CICR0_TOM&t;(1 &lt;&lt; 9)&t;/* Time-out mask */
DECL|macro|CICR0_RDAVM
mdefine_line|#define CICR0_RDAVM&t;(1 &lt;&lt; 8)&t;/* Receive-data-available mask */
DECL|macro|CICR0_FEM
mdefine_line|#define CICR0_FEM&t;(1 &lt;&lt; 7)&t;/* FIFO-empty mask */
DECL|macro|CICR0_EOLM
mdefine_line|#define CICR0_EOLM&t;(1 &lt;&lt; 6)&t;/* End-of-line mask */
DECL|macro|CICR0_PERRM
mdefine_line|#define CICR0_PERRM&t;(1 &lt;&lt; 5)&t;/* Parity-error mask */
DECL|macro|CICR0_QDM
mdefine_line|#define CICR0_QDM&t;(1 &lt;&lt; 4)&t;/* Quick-disable mask */
DECL|macro|CICR0_CDM
mdefine_line|#define CICR0_CDM&t;(1 &lt;&lt; 3)&t;/* Disable-done mask */
DECL|macro|CICR0_SOFM
mdefine_line|#define CICR0_SOFM&t;(1 &lt;&lt; 2)&t;/* Start-of-frame mask */
DECL|macro|CICR0_EOFM
mdefine_line|#define CICR0_EOFM&t;(1 &lt;&lt; 1)&t;/* End-of-frame mask */
DECL|macro|CICR0_FOM
mdefine_line|#define CICR0_FOM&t;(1 &lt;&lt; 0)&t;/* FIFO-overrun mask */
DECL|macro|CICR1_TBIT
mdefine_line|#define CICR1_TBIT&t;(1 &lt;&lt; 31)&t;/* Transparency bit */
DECL|macro|CICR1_RGBT_CONV
mdefine_line|#define CICR1_RGBT_CONV&t;(0x3 &lt;&lt; 30)&t;/* RGBT conversion mask */
DECL|macro|CICR1_PPL
mdefine_line|#define CICR1_PPL&t;(0x3f &lt;&lt; 15)&t;/* Pixels per line mask */
DECL|macro|CICR1_RGB_CONV
mdefine_line|#define CICR1_RGB_CONV&t;(0x7 &lt;&lt; 12)&t;/* RGB conversion mask */
DECL|macro|CICR1_RGB_F
mdefine_line|#define CICR1_RGB_F&t;(1 &lt;&lt; 11)&t;/* RGB format */
DECL|macro|CICR1_YCBCR_F
mdefine_line|#define CICR1_YCBCR_F&t;(1 &lt;&lt; 10)&t;/* YCbCr format */
DECL|macro|CICR1_RGB_BPP
mdefine_line|#define CICR1_RGB_BPP&t;(0x7 &lt;&lt; 7)&t;/* RGB bis per pixel mask */
DECL|macro|CICR1_RAW_BPP
mdefine_line|#define CICR1_RAW_BPP&t;(0x3 &lt;&lt; 5)&t;/* Raw bis per pixel mask */
DECL|macro|CICR1_COLOR_SP
mdefine_line|#define CICR1_COLOR_SP&t;(0x3 &lt;&lt; 3)&t;/* Color space mask */
DECL|macro|CICR1_DW
mdefine_line|#define CICR1_DW&t;(0x7 &lt;&lt; 0)&t;/* Data width mask */
DECL|macro|CICR2_BLW
mdefine_line|#define CICR2_BLW&t;(0xff &lt;&lt; 24)&t;/* Beginning-of-line pixel clock&n;&t;&t;&t;&t;&t;   wait count mask */
DECL|macro|CICR2_ELW
mdefine_line|#define CICR2_ELW&t;(0xff &lt;&lt; 16)&t;/* End-of-line pixel clock&n;&t;&t;&t;&t;&t;   wait count mask */
DECL|macro|CICR2_HSW
mdefine_line|#define CICR2_HSW&t;(0x3f &lt;&lt; 10)&t;/* Horizontal sync pulse width mask */
DECL|macro|CICR2_BFPW
mdefine_line|#define CICR2_BFPW&t;(0x3f &lt;&lt; 3)&t;/* Beginning-of-frame pixel clock&n;&t;&t;&t;&t;&t;   wait count mask */
DECL|macro|CICR2_FSW
mdefine_line|#define CICR2_FSW&t;(0x7 &lt;&lt; 0)&t;/* Frame stabilization&n;&t;&t;&t;&t;&t;   wait count mask */
DECL|macro|CICR3_BFW
mdefine_line|#define CICR3_BFW&t;(0xff &lt;&lt; 24)&t;/* Beginning-of-frame line clock&n;&t;&t;&t;&t;&t;   wait count mask */
DECL|macro|CICR3_EFW
mdefine_line|#define CICR3_EFW&t;(0xff &lt;&lt; 16)&t;/* End-of-frame line clock&n;&t;&t;&t;&t;&t;   wait count mask */
DECL|macro|CICR3_VSW
mdefine_line|#define CICR3_VSW&t;(0x3f &lt;&lt; 10)&t;/* Vertical sync pulse width mask */
DECL|macro|CICR3_BFPW
mdefine_line|#define CICR3_BFPW&t;(0x3f &lt;&lt; 3)&t;/* Beginning-of-frame pixel clock&n;&t;&t;&t;&t;&t;   wait count mask */
DECL|macro|CICR3_LPF
mdefine_line|#define CICR3_LPF&t;(0x3ff &lt;&lt; 0)&t;/* Lines per frame mask */
DECL|macro|CICR4_MCLK_DLY
mdefine_line|#define CICR4_MCLK_DLY&t;(0x3 &lt;&lt; 24)&t;/* MCLK Data Capture Delay mask */
DECL|macro|CICR4_PCLK_EN
mdefine_line|#define CICR4_PCLK_EN&t;(1 &lt;&lt; 23)&t;/* Pixel clock enable */
DECL|macro|CICR4_PCP
mdefine_line|#define CICR4_PCP&t;(1 &lt;&lt; 22)&t;/* Pixel clock polarity */
DECL|macro|CICR4_HSP
mdefine_line|#define CICR4_HSP&t;(1 &lt;&lt; 21)&t;/* Horizontal sync polarity */
DECL|macro|CICR4_VSP
mdefine_line|#define CICR4_VSP&t;(1 &lt;&lt; 20)&t;/* Vertical sync polarity */
DECL|macro|CICR4_MCLK_EN
mdefine_line|#define CICR4_MCLK_EN&t;(1 &lt;&lt; 19)&t;/* MCLK enable */
DECL|macro|CICR4_FR_RATE
mdefine_line|#define CICR4_FR_RATE&t;(0x7 &lt;&lt; 8)&t;/* Frame rate mask */
DECL|macro|CICR4_DIV
mdefine_line|#define CICR4_DIV&t;(0xff &lt;&lt; 0)&t;/* Clock divisor mask */
DECL|macro|CISR_FTO
mdefine_line|#define CISR_FTO&t;(1 &lt;&lt; 15)&t;/* FIFO time-out */
DECL|macro|CISR_RDAV_2
mdefine_line|#define CISR_RDAV_2&t;(1 &lt;&lt; 14)&t;/* Channel 2 receive data available */
DECL|macro|CISR_RDAV_1
mdefine_line|#define CISR_RDAV_1&t;(1 &lt;&lt; 13)&t;/* Channel 1 receive data available */
DECL|macro|CISR_RDAV_0
mdefine_line|#define CISR_RDAV_0&t;(1 &lt;&lt; 12)&t;/* Channel 0 receive data available */
DECL|macro|CISR_FEMPTY_2
mdefine_line|#define CISR_FEMPTY_2&t;(1 &lt;&lt; 11)&t;/* Channel 2 FIFO empty */
DECL|macro|CISR_FEMPTY_1
mdefine_line|#define CISR_FEMPTY_1&t;(1 &lt;&lt; 10)&t;/* Channel 1 FIFO empty */
DECL|macro|CISR_FEMPTY_0
mdefine_line|#define CISR_FEMPTY_0&t;(1 &lt;&lt; 9)&t;/* Channel 0 FIFO empty */
DECL|macro|CISR_EOL
mdefine_line|#define CISR_EOL&t;(1 &lt;&lt; 8)&t;/* End of line */
DECL|macro|CISR_PAR_ERR
mdefine_line|#define CISR_PAR_ERR&t;(1 &lt;&lt; 7)&t;/* Parity error */
DECL|macro|CISR_CQD
mdefine_line|#define CISR_CQD&t;(1 &lt;&lt; 6)&t;/* Camera interface quick disable */
DECL|macro|CISR_SOF
mdefine_line|#define CISR_SOF&t;(1 &lt;&lt; 5)&t;/* Start of frame */
DECL|macro|CISR_CDD
mdefine_line|#define CISR_CDD&t;(1 &lt;&lt; 4)&t;/* Camera interface disable done */
DECL|macro|CISR_EOF
mdefine_line|#define CISR_EOF&t;(1 &lt;&lt; 3)&t;/* End of frame */
DECL|macro|CISR_IFO_2
mdefine_line|#define CISR_IFO_2&t;(1 &lt;&lt; 2)&t;/* FIFO overrun for Channel 2 */
DECL|macro|CISR_IFO_1
mdefine_line|#define CISR_IFO_1&t;(1 &lt;&lt; 1)&t;/* FIFO overrun for Channel 1 */
DECL|macro|CISR_IFO_0
mdefine_line|#define CISR_IFO_0&t;(1 &lt;&lt; 0)&t;/* FIFO overrun for Channel 0 */
DECL|macro|CIFR_FLVL2
mdefine_line|#define CIFR_FLVL2&t;(0x7f &lt;&lt; 23)&t;/* FIFO 2 level mask */
DECL|macro|CIFR_FLVL1
mdefine_line|#define CIFR_FLVL1&t;(0x7f &lt;&lt; 16)&t;/* FIFO 1 level mask */
DECL|macro|CIFR_FLVL0
mdefine_line|#define CIFR_FLVL0&t;(0xff &lt;&lt; 8)&t;/* FIFO 0 level mask */
DECL|macro|CIFR_THL_0
mdefine_line|#define CIFR_THL_0&t;(0x3 &lt;&lt; 4)&t;/* Threshold Level for Channel 0 FIFO */
DECL|macro|CIFR_RESET_F
mdefine_line|#define CIFR_RESET_F&t;(1 &lt;&lt; 3)&t;/* Reset input FIFOs */
DECL|macro|CIFR_FEN2
mdefine_line|#define CIFR_FEN2&t;(1 &lt;&lt; 2)&t;/* FIFO enable for channel 2 */
DECL|macro|CIFR_FEN1
mdefine_line|#define CIFR_FEN1&t;(1 &lt;&lt; 1)&t;/* FIFO enable for channel 1 */
DECL|macro|CIFR_FEN0
mdefine_line|#define CIFR_FEN0&t;(1 &lt;&lt; 0)&t;/* FIFO enable for channel 0 */
DECL|macro|SRAM_SIZE
mdefine_line|#define SRAM_SIZE&t;&t;0x40000 /* 4x64K  */
DECL|macro|SRAM_MEM_PHYS
mdefine_line|#define SRAM_MEM_PHYS&t;&t;0x5C000000
DECL|macro|IMPMCR
mdefine_line|#define IMPMCR&t;&t;__REG(0x58000000) /* IM Power Management Control Reg */
DECL|macro|IMPMSR
mdefine_line|#define IMPMSR&t;&t;__REG(0x58000008) /* IM Power Management Status Reg */
DECL|macro|IMPMCR_PC3
mdefine_line|#define IMPMCR_PC3&t;&t;(0x3 &lt;&lt; 22) /* Bank 3 Power Control */
DECL|macro|IMPMCR_PC3_RUN_MODE
mdefine_line|#define IMPMCR_PC3_RUN_MODE&t;(0x0 &lt;&lt; 22) /*   Run mode */
DECL|macro|IMPMCR_PC3_STANDBY_MODE
mdefine_line|#define IMPMCR_PC3_STANDBY_MODE&t;(0x1 &lt;&lt; 22) /*   Standby mode */
DECL|macro|IMPMCR_PC3_AUTO_MODE
mdefine_line|#define IMPMCR_PC3_AUTO_MODE&t;(0x3 &lt;&lt; 22) /*   Automatically controlled */
DECL|macro|IMPMCR_PC2
mdefine_line|#define IMPMCR_PC2&t;&t;(0x3 &lt;&lt; 20) /* Bank 2 Power Control */
DECL|macro|IMPMCR_PC2_RUN_MODE
mdefine_line|#define IMPMCR_PC2_RUN_MODE&t;(0x0 &lt;&lt; 20) /*   Run mode */
DECL|macro|IMPMCR_PC2_STANDBY_MODE
mdefine_line|#define IMPMCR_PC2_STANDBY_MODE&t;(0x1 &lt;&lt; 20) /*   Standby mode */
DECL|macro|IMPMCR_PC2_AUTO_MODE
mdefine_line|#define IMPMCR_PC2_AUTO_MODE&t;(0x3 &lt;&lt; 20) /*   Automatically controlled */
DECL|macro|IMPMCR_PC1
mdefine_line|#define IMPMCR_PC1&t;&t;(0x3 &lt;&lt; 18) /* Bank 1 Power Control */
DECL|macro|IMPMCR_PC1_RUN_MODE
mdefine_line|#define IMPMCR_PC1_RUN_MODE&t;(0x0 &lt;&lt; 18) /*   Run mode */
DECL|macro|IMPMCR_PC1_STANDBY_MODE
mdefine_line|#define IMPMCR_PC1_STANDBY_MODE&t;(0x1 &lt;&lt; 18) /*   Standby mode */
DECL|macro|IMPMCR_PC1_AUTO_MODE
mdefine_line|#define IMPMCR_PC1_AUTO_MODE&t;(0x3 &lt;&lt; 18) /*   Automatically controlled */
DECL|macro|IMPMCR_PC0
mdefine_line|#define IMPMCR_PC0&t;&t;(0x3 &lt;&lt; 16) /* Bank 0 Power Control */
DECL|macro|IMPMCR_PC0_RUN_MODE
mdefine_line|#define IMPMCR_PC0_RUN_MODE&t;(0x0 &lt;&lt; 16) /*   Run mode */
DECL|macro|IMPMCR_PC0_STANDBY_MODE
mdefine_line|#define IMPMCR_PC0_STANDBY_MODE&t;(0x1 &lt;&lt; 16) /*   Standby mode */
DECL|macro|IMPMCR_PC0_AUTO_MODE
mdefine_line|#define IMPMCR_PC0_AUTO_MODE&t;(0x3 &lt;&lt; 16) /*   Automatically controlled */
DECL|macro|IMPMCR_AW3
mdefine_line|#define IMPMCR_AW3&t;&t;(1 &lt;&lt; 11) /* Bank 3 Automatic Wake-up enable */
DECL|macro|IMPMCR_AW2
mdefine_line|#define IMPMCR_AW2&t;&t;(1 &lt;&lt; 10) /* Bank 2 Automatic Wake-up enable */
DECL|macro|IMPMCR_AW1
mdefine_line|#define IMPMCR_AW1&t;&t;(1 &lt;&lt; 9)  /* Bank 1 Automatic Wake-up enable */
DECL|macro|IMPMCR_AW0
mdefine_line|#define IMPMCR_AW0&t;&t;(1 &lt;&lt; 8)  /* Bank 0 Automatic Wake-up enable */
DECL|macro|IMPMCR_DST
mdefine_line|#define IMPMCR_DST&t;&t;(0xFF &lt;&lt; 0) /* Delay Standby Time, ms */
DECL|macro|IMPMSR_PS3
mdefine_line|#define IMPMSR_PS3&t;&t;(0x3 &lt;&lt; 6) /* Bank 3 Power Status: */
DECL|macro|IMPMSR_PS3_RUN_MODE
mdefine_line|#define IMPMSR_PS3_RUN_MODE&t;(0x0 &lt;&lt; 6) /*    Run mode */
DECL|macro|IMPMSR_PS3_STANDBY_MODE
mdefine_line|#define IMPMSR_PS3_STANDBY_MODE&t;(0x1 &lt;&lt; 6) /*    Standby mode */
DECL|macro|IMPMSR_PS2
mdefine_line|#define IMPMSR_PS2&t;&t;(0x3 &lt;&lt; 4) /* Bank 2 Power Status: */
DECL|macro|IMPMSR_PS2_RUN_MODE
mdefine_line|#define IMPMSR_PS2_RUN_MODE&t;(0x0 &lt;&lt; 4) /*    Run mode */
DECL|macro|IMPMSR_PS2_STANDBY_MODE
mdefine_line|#define IMPMSR_PS2_STANDBY_MODE&t;(0x1 &lt;&lt; 4) /*    Standby mode */
DECL|macro|IMPMSR_PS1
mdefine_line|#define IMPMSR_PS1&t;&t;(0x3 &lt;&lt; 2) /* Bank 1 Power Status: */
DECL|macro|IMPMSR_PS1_RUN_MODE
mdefine_line|#define IMPMSR_PS1_RUN_MODE&t;(0x0 &lt;&lt; 2) /*    Run mode */
DECL|macro|IMPMSR_PS1_STANDBY_MODE
mdefine_line|#define IMPMSR_PS1_STANDBY_MODE&t;(0x1 &lt;&lt; 2) /*    Standby mode */
DECL|macro|IMPMSR_PS0
mdefine_line|#define IMPMSR_PS0&t;&t;(0x3 &lt;&lt; 0) /* Bank 0 Power Status: */
DECL|macro|IMPMSR_PS0_RUN_MODE
mdefine_line|#define IMPMSR_PS0_RUN_MODE&t;(0x0 &lt;&lt; 0) /*    Run mode */
DECL|macro|IMPMSR_PS0_STANDBY_MODE
mdefine_line|#define IMPMSR_PS0_STANDBY_MODE&t;(0x1 &lt;&lt; 0) /*    Standby mode */
macro_line|#endif
macro_line|#endif
eof
