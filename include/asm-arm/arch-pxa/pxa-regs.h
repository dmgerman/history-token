multiline_comment|/*&n; *  linux/include/asm-arm/arch-pxa/pxa-regs.h&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Jun 15, 2001&n; *  Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
singleline_comment|// FIXME hack so that SA-1111.h will work [cb]
macro_line|#ifndef __ASSEMBLY__
DECL|typedef|Word16
r_typedef
r_int
r_int
id|Word16
suffix:semicolon
DECL|typedef|Word32
r_typedef
r_int
r_int
id|Word32
suffix:semicolon
DECL|typedef|Word
r_typedef
id|Word32
id|Word
suffix:semicolon
DECL|typedef|Quad
r_typedef
id|Word
id|Quad
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|Address
r_typedef
r_void
op_star
id|Address
suffix:semicolon
DECL|typedef|ExcpHndlr
r_typedef
r_void
(paren
op_star
id|ExcpHndlr
)paren
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
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
DECL|macro|DRCMR_MAPVLD
mdefine_line|#define DRCMR_MAPVLD&t;(1 &lt;&lt; 7)&t;/* Map Valid (read / write) */
DECL|macro|DRCMR_CHLNUM
mdefine_line|#define DRCMR_CHLNUM&t;0x0f&t;&t;/* mask for Channel Number (read / write) */
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
multiline_comment|/*&n; * Serial Audio Controller&n; */
multiline_comment|/* FIXME the audio defines collide w/ the SA1111 defines.  I don&squot;t like these&n; * short defines because there is too much chance of namespace collision */
singleline_comment|//#define SACR0&t;&t;__REG(0x40400000)  /* Global Control Register */
singleline_comment|//#define SACR1&t;&t;__REG(0x40400004)  /* Serial Audio I 2 S/MSB-Justified Control Register */
singleline_comment|//#define SASR0&t;&t;__REG(0x4040000C)  /* Serial Audio I 2 S/MSB-Justified Interface and FIFO Status Register */
singleline_comment|//#define SAIMR&t;&t;__REG(0x40400014)  /* Serial Audio Interrupt Mask Register */
singleline_comment|//#define SAICR&t;&t;__REG(0x40400018)  /* Serial Audio Interrupt Clear Register */
singleline_comment|//#define SADIV&t;&t;__REG(0x40400060)  /* Audio Clock Divider Register. */
singleline_comment|//#define SADR&t;&t;__REG(0x40400080)  /* Serial Audio Data Register (TX and RX FIFO access Register). */
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
multiline_comment|/*&n; * USB Device Controller&n; */
DECL|macro|UDCCR
mdefine_line|#define UDCCR&t;&t;__REG(0x40600000)  /* UDC Control Register */
DECL|macro|UDCCS0
mdefine_line|#define UDCCS0&t;&t;__REG(0x40600010)  /* UDC Endpoint 0 Control/Status Register */
DECL|macro|UDCCS1
mdefine_line|#define UDCCS1&t;&t;__REG(0x40600014)  /* UDC Endpoint 1 (IN) Control/Status Register */
DECL|macro|UDCCS2
mdefine_line|#define UDCCS2&t;&t;__REG(0x40600018)  /* UDC Endpoint 2 (OUT) Control/Status Register */
DECL|macro|UDCCS3
mdefine_line|#define UDCCS3&t;&t;__REG(0x4060001C)  /* UDC Endpoint 3 (IN) Control/Status Register */
DECL|macro|UDCCS4
mdefine_line|#define UDCCS4&t;&t;__REG(0x40600020)  /* UDC Endpoint 4 (OUT) Control/Status Register */
DECL|macro|UDCCS5
mdefine_line|#define UDCCS5&t;&t;__REG(0x40600024)  /* UDC Endpoint 5 (Interrupt) Control/Status Register */
DECL|macro|UDCCS6
mdefine_line|#define UDCCS6&t;&t;__REG(0x40600028)  /* UDC Endpoint 6 (IN) Control/Status Register */
DECL|macro|UDCCS7
mdefine_line|#define UDCCS7&t;&t;__REG(0x4060002C)  /* UDC Endpoint 7 (OUT) Control/Status Register */
DECL|macro|UDCCS8
mdefine_line|#define UDCCS8&t;&t;__REG(0x40600030)  /* UDC Endpoint 8 (IN) Control/Status Register */
DECL|macro|UDCCS9
mdefine_line|#define UDCCS9&t;&t;__REG(0x40600034)  /* UDC Endpoint 9 (OUT) Control/Status Register */
DECL|macro|UDCCS10
mdefine_line|#define UDCCS10&t;&t;__REG(0x40600038)  /* UDC Endpoint 10 (Interrupt) Control/Status Register */
DECL|macro|UDCCS11
mdefine_line|#define UDCCS11&t;&t;__REG(0x4060003C)  /* UDC Endpoint 11 (IN) Control/Status Register */
DECL|macro|UDCCS12
mdefine_line|#define UDCCS12&t;&t;__REG(0x40600040)  /* UDC Endpoint 12 (OUT) Control/Status Register */
DECL|macro|UDCCS13
mdefine_line|#define UDCCS13&t;&t;__REG(0x40600044)  /* UDC Endpoint 13 (IN) Control/Status Register */
DECL|macro|UDCCS14
mdefine_line|#define UDCCS14&t;&t;__REG(0x40600048)  /* UDC Endpoint 14 (OUT) Control/Status Register */
DECL|macro|UDCCS15
mdefine_line|#define UDCCS15&t;&t;__REG(0x4060004C)  /* UDC Endpoint 15 (Interrupt) Control/Status Register */
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
DECL|macro|UICR1
mdefine_line|#define UICR1&t;&t;__REG(0x40600054)  /* UDC Interrupt Control Register 1 */
DECL|macro|USIR0
mdefine_line|#define USIR0&t;&t;__REG(0x40600058)  /* UDC Status Interrupt Register 0 */
DECL|macro|USIR1
mdefine_line|#define USIR1&t;&t;__REG(0x4060005C)  /* UDC Status Interrupt Register 1 */
multiline_comment|/*&n; * Fast Infrared Communication Port&n; */
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
multiline_comment|/*&n; * Real Time Clock&n; */
DECL|macro|RCNR
mdefine_line|#define RCNR&t;&t;__REG(0x40900000)  /* RTC Count Register */
DECL|macro|RTAR
mdefine_line|#define RTAR&t;&t;__REG(0x40900004)  /* RTC Alarm Register */
DECL|macro|RTSR
mdefine_line|#define RTSR&t;&t;__REG(0x40900008)  /* RTC Status Register */
DECL|macro|RTTR
mdefine_line|#define RTTR&t;&t;__REG(0x4090000C)  /* RTC Timer Trim Register */
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
DECL|macro|OSCR
mdefine_line|#define OSCR&t;&t;__REG(0x40A00010)  /* OS Timer Counter Register */
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
mdefine_line|#define GAFR2_U&t;&t;__REG(0x40E00068)  /* GPIO Alternate Function Select Register GPIO 80 */
multiline_comment|/* More handy macros.  The argument is a literal GPIO number. */
DECL|macro|GPIO_bit
mdefine_line|#define GPIO_bit(x)&t;(1 &lt;&lt; ((x) &amp; 0x1f))
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
multiline_comment|/* GPIO alternate function assignments */
DECL|macro|GPIO1_RST
mdefine_line|#define GPIO1_RST&t;&t;1&t;/* reset */
DECL|macro|GPIO6_MMCCLK
mdefine_line|#define GPIO6_MMCCLK&t;&t;6&t;/* MMC Clock */
DECL|macro|GPIO8_48MHz
mdefine_line|#define GPIO8_48MHz&t;&t;7&t;/* 48 MHz clock output */
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
DECL|macro|GPIO8_48MHz_MD
mdefine_line|#define GPIO8_48MHz_MD&t;&t;( 8 | GPIO_ALT_FN_1_OUT)
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
DECL|macro|GPIO80_nCS_4_MD
mdefine_line|#define GPIO80_nCS_4_MD&t;&t;(80 | GPIO_ALT_FN_2_OUT)
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
DECL|macro|RCSR
mdefine_line|#define RCSR&t;&t;__REG(0x40F00030)  /* Reset Controller Status Register */
multiline_comment|/*&n; * SSP Serial Port Registers&n; */
DECL|macro|SSCR0
mdefine_line|#define SSCR0&t;&t;__REG(0x41000000)  /* SSP Control Register 0 */
DECL|macro|SSCR1
mdefine_line|#define SSCR1&t;&t;__REG(0x41000004)  /* SSP Control Register 1 */
DECL|macro|SSSR
mdefine_line|#define SSSR&t;&t;__REG(0x41000008)  /* SSP Status Register */
DECL|macro|SSITR
mdefine_line|#define SSITR&t;&t;__REG(0x4100000C)  /* SSP Interrupt Test Register */
DECL|macro|SSDR
mdefine_line|#define SSDR&t;&t;__REG(0x41000010)  /* (Write / Read) SSP Data Write Register/SSP Data Read Register */
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
DECL|macro|CCCR_N_MASK
mdefine_line|#define CCCR_N_MASK&t;0x0380&t;&t;/* Run Mode Frequency to Turbo Mode Frequency Multiplier */
DECL|macro|CCCR_M_MASK
mdefine_line|#define CCCR_M_MASK&t;0x0060&t;&t;/* Memory Frequency to Run Mode Frequency Multiplier */
DECL|macro|CCCR_L_MASK
mdefine_line|#define CCCR_L_MASK&t;0x001f&t;&t;/* Crystal Frequency to Memory Frequency Multiplier */
DECL|macro|CKEN16_LCD
mdefine_line|#define CKEN16_LCD&t;(1 &lt;&lt; 16)&t;/* LCD Unit Clock Enable */
DECL|macro|CKEN14_I2C
mdefine_line|#define CKEN14_I2C&t;(1 &lt;&lt; 14)&t;/* I2C Unit Clock Enable */
DECL|macro|CKEN13_FICP
mdefine_line|#define CKEN13_FICP&t;(1 &lt;&lt; 13)&t;/* FICP Unit Clock Enable */
DECL|macro|CKEN12_MMC
mdefine_line|#define CKEN12_MMC&t;(1 &lt;&lt; 12)&t;/* MMC Unit Clock Enable */
DECL|macro|CKEN11_USB
mdefine_line|#define CKEN11_USB&t;(1 &lt;&lt; 11)&t;/* USB Unit Clock Enable */
DECL|macro|CKEN8_I2S
mdefine_line|#define CKEN8_I2S&t;(1 &lt;&lt; 8)&t;/* I2S Unit Clock Enable */
DECL|macro|CKEN7_BTUART
mdefine_line|#define CKEN7_BTUART&t;(1 &lt;&lt; 7)&t;/* BTUART Unit Clock Enable */
DECL|macro|CKEN6_FFUART
mdefine_line|#define CKEN6_FFUART&t;(1 &lt;&lt; 6)&t;/* FFUART Unit Clock Enable */
DECL|macro|CKEN5_STUART
mdefine_line|#define CKEN5_STUART&t;(1 &lt;&lt; 5)&t;/* STUART Unit Clock Enable */
DECL|macro|CKEN3_SSP
mdefine_line|#define CKEN3_SSP&t;(1 &lt;&lt; 3)&t;/* SSP Unit Clock Enable */
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
mdefine_line|#define LCCR0_CMS&t;(1 &lt;&lt; 1)&t;/* Color = 0, Monochrome = 1 */
DECL|macro|LCCR0_SDS
mdefine_line|#define LCCR0_SDS&t;(1 &lt;&lt; 2)&t;/* Single Panel = 0, Dual Panel = 1 */
DECL|macro|LCCR0_LDM
mdefine_line|#define LCCR0_LDM&t;(1 &lt;&lt; 3)&t;/* LCD Disable Done Mask */
DECL|macro|LCCR0_SFM
mdefine_line|#define LCCR0_SFM&t;(1 &lt;&lt; 4)&t;/* Start of frame mask */
DECL|macro|LCCR0_IUM
mdefine_line|#define LCCR0_IUM&t;(1 &lt;&lt; 5)&t;/* Input FIFO underrun mask */
DECL|macro|LCCR0_EFM
mdefine_line|#define LCCR0_EFM&t;(1 &lt;&lt; 6)&t;/* End of Frame mask */
DECL|macro|LCCR0_PAS
mdefine_line|#define LCCR0_PAS&t;(1 &lt;&lt; 7)&t;/* Passive = 0, Active = 1 */
DECL|macro|LCCR0_BLE
mdefine_line|#define LCCR0_BLE&t;(1 &lt;&lt; 8)&t;/* Little Endian = 0, Big Endian = 1 */
DECL|macro|LCCR0_DPD
mdefine_line|#define LCCR0_DPD&t;(1 &lt;&lt; 9)&t;/* Double Pixel mode, 4 pixel value = 0, 8 pixle values = 1 */
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
DECL|macro|LCCR3_PCD
mdefine_line|#define LCCR3_PCD&t;(0xff)&t;&t;/* Pixel clock divisor */
DECL|macro|LCCR3_ACB
mdefine_line|#define LCCR3_ACB&t;(0xff &lt;&lt; 8)&t;/* AC Bias pin frequency */
DECL|macro|LCCR3_ACB_S
mdefine_line|#define LCCR3_ACB_S&t;8
DECL|macro|LCCR3_API
mdefine_line|#define LCCR3_API&t;(0xf &lt;&lt; 16)&t;/* AC Bias pin trasitions per interrupt */
DECL|macro|LCCR3_API_S
mdefine_line|#define LCCR3_API_S&t;16
DECL|macro|LCCR3_VSP
mdefine_line|#define LCCR3_VSP&t;(1 &lt;&lt; 20)&t;/* vertical sync polarity */
DECL|macro|LCCR3_HSP
mdefine_line|#define LCCR3_HSP&t;(1 &lt;&lt; 21)&t;/* horizontal sync polarity */
DECL|macro|LCCR3_PCP
mdefine_line|#define LCCR3_PCP&t;(1 &lt;&lt; 22)&t;/* pixel clock polarity */
DECL|macro|LCCR3_OEP
mdefine_line|#define LCCR3_OEP&t;(1 &lt;&lt; 23)&t;/* output enable polarity */
DECL|macro|LCCR3_BPP
mdefine_line|#define LCCR3_BPP&t;(7 &lt;&lt; 24)&t;/* bits per pixel */
DECL|macro|LCCR3_BPP_S
mdefine_line|#define LCCR3_BPP_S&t;24
DECL|macro|LCCR3_DPC
mdefine_line|#define LCCR3_DPC&t;(1 &lt;&lt; 27)&t;/* double pixel clock mode */
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
eof
