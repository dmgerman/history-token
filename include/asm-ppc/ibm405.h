multiline_comment|/*&n; * Author: Armin Kuster &lt;akuster@mvista.com&gt;&n; *&n; * 2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.1.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IBM405_H__
DECL|macro|__ASM_IBM405_H__
mdefine_line|#define __ASM_IBM405_H__
macro_line|#ifdef DCRN_BE_BASE
DECL|macro|DCRN_BEAR
mdefine_line|#define DCRN_BEAR&t;(DCRN_BE_BASE + 0x0)&t;/* Bus Error Address Register */
DECL|macro|DCRN_BESR
mdefine_line|#define DCRN_BESR&t;(DCRN_BE_BASE + 0x1)&t;/* Bus Error Syndrome Register */
macro_line|#endif
multiline_comment|/* DCRN_BESR */
DECL|macro|BESR_DSES
mdefine_line|#define BESR_DSES&t;0x80000000&t;/* Data-Side Error Status */
DECL|macro|BESR_DMES
mdefine_line|#define BESR_DMES&t;0x40000000&t;/* DMA Error Status */
DECL|macro|BESR_RWS
mdefine_line|#define BESR_RWS&t;0x20000000&t;/* Read/Write Status */
DECL|macro|BESR_ETMASK
mdefine_line|#define BESR_ETMASK&t;0x1C000000&t;/* Error Type */
DECL|macro|ET_PROT
mdefine_line|#define ET_PROT&t;0
DECL|macro|ET_PARITY
mdefine_line|#define ET_PARITY&t;1
DECL|macro|ET_NCFG
mdefine_line|#define ET_NCFG&t;2
DECL|macro|ET_BUSERR
mdefine_line|#define ET_BUSERR&t;4
DECL|macro|ET_BUSTO
mdefine_line|#define ET_BUSTO&t;6
multiline_comment|/* Clock and power management shifts for emacs */
DECL|macro|IBM_CPM_EMMII
mdefine_line|#define IBM_CPM_EMMII&t;0&t;/* Shift value for MII */
DECL|macro|IBM_CPM_EMRX
mdefine_line|#define IBM_CPM_EMRX&t;1&t;/* Shift value for recv */
DECL|macro|IBM_CPM_EMTX
mdefine_line|#define IBM_CPM_EMTX&t;2&t;/* Shift value for MAC */
macro_line|#ifdef DCRN_CHCR_BASE
DECL|macro|DCRN_CHCR0
mdefine_line|#define DCRN_CHCR0&t;(DCRN_CHCR_BASE + 0x0)&t;/* Chip Control Register 1 */
DECL|macro|DCRN_CHCR1
mdefine_line|#define DCRN_CHCR1&t;(DCRN_CHCR_BASE + 0x1)&t;/* Chip Control Register 2 */
macro_line|#endif
DECL|macro|CHR1_PCIPW
mdefine_line|#define CHR1_PCIPW&t;0x00008000&t;/* PCI Int enable/Peripheral Write enable */
macro_line|#ifdef DCRN_CHPSR_BASE
DECL|macro|DCRN_CHPSR
mdefine_line|#define DCRN_CHPSR&t;(DCRN_CHPSR_BASE + 0x0)&t;/* Chip Pin Strapping */
macro_line|#endif
macro_line|#ifdef DCRN_CPMFR_BASE
DECL|macro|DCRN_CPMFR
mdefine_line|#define DCRN_CPMFR&t;(DCRN_CPMFR_BASE + 0x0)&t;/* CPM Force */
macro_line|#endif
macro_line|#ifdef DCRN_CPMSR_BASE
DECL|macro|DCRN_CPMSR
mdefine_line|#define DCRN_CPMSR&t;(DCRN_CPMSR_BASE + 0x0)&t;/* CPM Status */
DECL|macro|DCRN_CPMER
mdefine_line|#define DCRN_CPMER&t;(DCRN_CPMSR_BASE + 0x1)&t;/* CPM Enable */
macro_line|#endif
macro_line|#ifdef DCRN_DCP0_BASE
multiline_comment|/* Decompression Controller Address */
DECL|macro|DCRN_DCP0_CFGADDR
mdefine_line|#define DCRN_DCP0_CFGADDR&t;(DCRN_DCP0_BASE + 0x0)
multiline_comment|/* Decompression Controller Data */
DECL|macro|DCRN_DCP0_CFGDATA
mdefine_line|#define DCRN_DCP0_CFGDATA&t;(DCRN_DCP0_BASE + 0x1)
macro_line|#else
DECL|macro|DCRN_DCP0_CFGADDR
mdefine_line|#define DCRN_DCP0_CFGADDR&t;0x0
DECL|macro|DCRN_DCP0_CFGDATA
mdefine_line|#define DCRN_DCP0_CFGDATA&t;0x0
macro_line|#endif
macro_line|#ifdef DCRN_DMA0_BASE
multiline_comment|/* DMA Channel Control Register 0 */
DECL|macro|DCRN_DMACR0
mdefine_line|#define DCRN_DMACR0&t;(DCRN_DMA0_BASE + 0x0)
DECL|macro|DCRN_DMACT0
mdefine_line|#define DCRN_DMACT0&t;(DCRN_DMA0_BASE + 0x1)&t;/* DMA Count Register 0 */
multiline_comment|/* DMA Destination Address Register 0 */
DECL|macro|DCRN_DMADA0
mdefine_line|#define DCRN_DMADA0&t;(DCRN_DMA0_BASE + 0x2)
multiline_comment|/* DMA Source Address Register 0 */
DECL|macro|DCRN_DMASA0
mdefine_line|#define DCRN_DMASA0&t;(DCRN_DMA0_BASE + 0x3)
macro_line|#ifdef DCRNCAP_DMA_CC
multiline_comment|/* DMA Chained Count Register 0 */
DECL|macro|DCRN_DMACC0
mdefine_line|#define DCRN_DMACC0&t;(DCRN_DMA0_BASE + 0x4)
macro_line|#endif
macro_line|#ifdef DCRNCAP_DMA_SG
multiline_comment|/* DMA Scatter/Gather Descriptor Addr 0 */
DECL|macro|DCRN_ASG0
mdefine_line|#define DCRN_ASG0&t;(DCRN_DMA0_BASE + 0x4)
macro_line|#endif
macro_line|#endif
macro_line|#ifdef DCRN_DMA1_BASE
multiline_comment|/* DMA Channel Control Register 1 */
DECL|macro|DCRN_DMACR1
mdefine_line|#define DCRN_DMACR1&t;(DCRN_DMA1_BASE + 0x0)
DECL|macro|DCRN_DMACT1
mdefine_line|#define DCRN_DMACT1&t;(DCRN_DMA1_BASE + 0x1)&t;/* DMA Count Register 1 */
multiline_comment|/* DMA Destination Address Register 1 */
DECL|macro|DCRN_DMADA1
mdefine_line|#define DCRN_DMADA1&t;(DCRN_DMA1_BASE + 0x2)
multiline_comment|/* DMA Source Address Register 1 */
DECL|macro|DCRN_DMASA1
mdefine_line|#define DCRN_DMASA1&t;(DCRN_DMA1_BASE + 0x3)&t;/* DMA Source Address Register 1 */
macro_line|#ifdef DCRNCAP_DMA_CC
multiline_comment|/* DMA Chained Count Register 1 */
DECL|macro|DCRN_DMACC1
mdefine_line|#define DCRN_DMACC1&t;(DCRN_DMA1_BASE + 0x4)
macro_line|#endif
macro_line|#ifdef DCRNCAP_DMA_SG
multiline_comment|/* DMA Scatter/Gather Descriptor Addr 1 */
DECL|macro|DCRN_ASG1
mdefine_line|#define DCRN_ASG1&t;(DCRN_DMA1_BASE + 0x4)
macro_line|#endif
macro_line|#endif
macro_line|#ifdef DCRN_DMA2_BASE
DECL|macro|DCRN_DMACR2
mdefine_line|#define DCRN_DMACR2&t;(DCRN_DMA2_BASE + 0x0)&t;/* DMA Channel Control Register 2 */
DECL|macro|DCRN_DMACT2
mdefine_line|#define DCRN_DMACT2&t;(DCRN_DMA2_BASE + 0x1)&t;/* DMA Count Register 2 */
DECL|macro|DCRN_DMADA2
mdefine_line|#define DCRN_DMADA2&t;(DCRN_DMA2_BASE + 0x2)&t;/* DMA Destination Address Register 2 */
DECL|macro|DCRN_DMASA2
mdefine_line|#define DCRN_DMASA2&t;(DCRN_DMA2_BASE + 0x3)&t;/* DMA Source Address Register 2 */
macro_line|#ifdef DCRNCAP_DMA_CC
DECL|macro|DCRN_DMACC2
mdefine_line|#define DCRN_DMACC2&t;(DCRN_DMA2_BASE + 0x4)&t;/* DMA Chained Count Register 2 */
macro_line|#endif
macro_line|#ifdef DCRNCAP_DMA_SG
DECL|macro|DCRN_ASG2
mdefine_line|#define DCRN_ASG2&t;(DCRN_DMA2_BASE + 0x4)&t;/* DMA Scatter/Gather Descriptor Addr 2 */
macro_line|#endif
macro_line|#endif
macro_line|#ifdef DCRN_DMA3_BASE
DECL|macro|DCRN_DMACR3
mdefine_line|#define DCRN_DMACR3&t;(DCRN_DMA3_BASE + 0x0)&t;/* DMA Channel Control Register 3 */
DECL|macro|DCRN_DMACT3
mdefine_line|#define DCRN_DMACT3&t;(DCRN_DMA3_BASE + 0x1)&t;/* DMA Count Register 3 */
DECL|macro|DCRN_DMADA3
mdefine_line|#define DCRN_DMADA3&t;(DCRN_DMA3_BASE + 0x2)&t;/* DMA Destination Address Register 3 */
DECL|macro|DCRN_DMASA3
mdefine_line|#define DCRN_DMASA3&t;(DCRN_DMA3_BASE + 0x3)&t;/* DMA Source Address Register 3 */
macro_line|#ifdef DCRNCAP_DMA_CC
DECL|macro|DCRN_DMACC3
mdefine_line|#define DCRN_DMACC3&t;(DCRN_DMA3_BASE + 0x4)&t;/* DMA Chained Count Register 3 */
macro_line|#endif
macro_line|#ifdef DCRNCAP_DMA_SG
DECL|macro|DCRN_ASG3
mdefine_line|#define DCRN_ASG3&t;(DCRN_DMA3_BASE + 0x4)&t;/* DMA Scatter/Gather Descriptor Addr 3 */
macro_line|#endif
macro_line|#endif
macro_line|#ifdef DCRN_DMASR_BASE
DECL|macro|DCRN_DMASR
mdefine_line|#define DCRN_DMASR&t;(DCRN_DMASR_BASE + 0x0)&t;/* DMA Status Register */
macro_line|#ifdef DCRNCAP_DMA_SG
DECL|macro|DCRN_ASGC
mdefine_line|#define DCRN_ASGC&t;(DCRN_DMASR_BASE + 0x3)&t;/* DMA Scatter/Gather Command */
multiline_comment|/* don&squot;t know if these two registers always exist if scatter/gather exists */
DECL|macro|DCRN_POL
mdefine_line|#define DCRN_POL&t;(DCRN_DMASR_BASE + 0x6)&t;/* DMA Polarity Register */
DECL|macro|DCRN_SLP
mdefine_line|#define DCRN_SLP&t;(DCRN_DMASR_BASE + 0x5)&t;/* DMA Sleep Register */
macro_line|#endif
macro_line|#endif
macro_line|#ifdef DCRN_EBC_BASE
DECL|macro|DCRN_EBCCFGADR
mdefine_line|#define DCRN_EBCCFGADR&t;(DCRN_EBC_BASE + 0x0)&t;/* Peripheral Controller Address */
DECL|macro|DCRN_EBCCFGDATA
mdefine_line|#define DCRN_EBCCFGDATA&t;(DCRN_EBC_BASE + 0x1)&t;/* Peripheral Controller Data */
macro_line|#endif
macro_line|#ifdef DCRN_EXIER_BASE
DECL|macro|DCRN_EXIER
mdefine_line|#define DCRN_EXIER&t;(DCRN_EXIER_BASE + 0x0)&t;/* External Interrupt Enable Register */
macro_line|#endif
macro_line|#ifdef DCRN_EXISR_BASE
DECL|macro|DCRN_EXISR
mdefine_line|#define DCRN_EXISR&t;(DCRN_EXISR_BASE + 0x0)&t;/* External Interrupt Status Register */
macro_line|#endif
DECL|macro|EXIER_CIE
mdefine_line|#define EXIER_CIE&t;0x80000000&t;/* Critical Interrupt Enable */
DECL|macro|EXIER_SRIE
mdefine_line|#define EXIER_SRIE&t;0x08000000&t;/* Serial Port Rx Int. Enable */
DECL|macro|EXIER_STIE
mdefine_line|#define EXIER_STIE&t;0x04000000&t;/* Serial Port Tx Int. Enable */
DECL|macro|EXIER_JRIE
mdefine_line|#define EXIER_JRIE&t;0x02000000&t;/* JTAG Serial Port Rx Int. Enable */
DECL|macro|EXIER_JTIE
mdefine_line|#define EXIER_JTIE&t;0x01000000&t;/* JTAG Serial Port Tx Int. Enable */
DECL|macro|EXIER_D0IE
mdefine_line|#define EXIER_D0IE&t;0x00800000&t;/* DMA Channel 0 Interrupt Enable */
DECL|macro|EXIER_D1IE
mdefine_line|#define EXIER_D1IE&t;0x00400000&t;/* DMA Channel 1 Interrupt Enable */
DECL|macro|EXIER_D2IE
mdefine_line|#define EXIER_D2IE&t;0x00200000&t;/* DMA Channel 2 Interrupt Enable */
DECL|macro|EXIER_D3IE
mdefine_line|#define EXIER_D3IE&t;0x00100000&t;/* DMA Channel 3 Interrupt Enable */
DECL|macro|EXIER_E0IE
mdefine_line|#define EXIER_E0IE&t;0x00000010&t;/* External Interrupt 0 Enable */
DECL|macro|EXIER_E1IE
mdefine_line|#define EXIER_E1IE&t;0x00000008&t;/* External Interrupt 1 Enable */
DECL|macro|EXIER_E2IE
mdefine_line|#define EXIER_E2IE&t;0x00000004&t;/* External Interrupt 2 Enable */
DECL|macro|EXIER_E3IE
mdefine_line|#define EXIER_E3IE&t;0x00000002&t;/* External Interrupt 3 Enable */
DECL|macro|EXIER_E4IE
mdefine_line|#define EXIER_E4IE&t;0x00000001&t;/* External Interrupt 4 Enable */
macro_line|#ifdef DCRN_IOCR_BASE
DECL|macro|DCRN_IOCR
mdefine_line|#define DCRN_IOCR&t;(DCRN_IOCR_BASE + 0x0)&t;/* Input/Output Configuration Register */
macro_line|#endif
DECL|macro|IOCR_E0TE
mdefine_line|#define IOCR_E0TE&t;0x80000000
DECL|macro|IOCR_E0LP
mdefine_line|#define IOCR_E0LP&t;0x40000000
DECL|macro|IOCR_E1TE
mdefine_line|#define IOCR_E1TE&t;0x20000000
DECL|macro|IOCR_E1LP
mdefine_line|#define IOCR_E1LP&t;0x10000000
DECL|macro|IOCR_E2TE
mdefine_line|#define IOCR_E2TE&t;0x08000000
DECL|macro|IOCR_E2LP
mdefine_line|#define IOCR_E2LP&t;0x04000000
DECL|macro|IOCR_E3TE
mdefine_line|#define IOCR_E3TE&t;0x02000000
DECL|macro|IOCR_E3LP
mdefine_line|#define IOCR_E3LP&t;0x01000000
DECL|macro|IOCR_E4TE
mdefine_line|#define IOCR_E4TE&t;0x00800000
DECL|macro|IOCR_E4LP
mdefine_line|#define IOCR_E4LP&t;0x00400000
DECL|macro|IOCR_EDT
mdefine_line|#define IOCR_EDT&t;0x00080000
DECL|macro|IOCR_SOR
mdefine_line|#define IOCR_SOR&t;0x00040000
DECL|macro|IOCR_EDO
mdefine_line|#define IOCR_EDO&t;0x00008000
DECL|macro|IOCR_2XC
mdefine_line|#define IOCR_2XC&t;0x00004000
DECL|macro|IOCR_ATC
mdefine_line|#define IOCR_ATC&t;0x00002000
DECL|macro|IOCR_SPD
mdefine_line|#define IOCR_SPD&t;0x00001000
DECL|macro|IOCR_BEM
mdefine_line|#define IOCR_BEM&t;0x00000800
DECL|macro|IOCR_PTD
mdefine_line|#define IOCR_PTD&t;0x00000400
DECL|macro|IOCR_ARE
mdefine_line|#define IOCR_ARE&t;0x00000080
DECL|macro|IOCR_DRC
mdefine_line|#define IOCR_DRC&t;0x00000020
DECL|macro|IOCR_RDM
mdefine_line|#define IOCR_RDM(x)&t;(((x) &amp; 0x3) &lt;&lt; 3)
DECL|macro|IOCR_TCS
mdefine_line|#define IOCR_TCS&t;0x00000004
DECL|macro|IOCR_SCS
mdefine_line|#define IOCR_SCS&t;0x00000002
DECL|macro|IOCR_SPC
mdefine_line|#define IOCR_SPC&t;0x00000001
DECL|macro|DCRN_MALCR
mdefine_line|#define DCRN_MALCR(base)&t;(base + 0x0)&t;/* MAL Configuration */
DECL|macro|DCRN_MALDBR
mdefine_line|#define DCRN_MALDBR(base)&t;((base) + 0x3)&t;/* Debug Register */
DECL|macro|DCRN_MALESR
mdefine_line|#define DCRN_MALESR(base)&t;((base) + 0x1)&t;/* Error Status */
DECL|macro|DCRN_MALIER
mdefine_line|#define DCRN_MALIER(base)&t;((base) + 0x2)&t;/* Interrupt Enable */
DECL|macro|DCRN_MALTXCARR
mdefine_line|#define DCRN_MALTXCARR(base)&t;((base) + 0x5)&t;/* TX Channed Active Reset Register */
DECL|macro|DCRN_MALTXCASR
mdefine_line|#define DCRN_MALTXCASR(base)&t;((base) + 0x4)&t;/* TX Channel Active Set Register */
DECL|macro|DCRN_MALTXDEIR
mdefine_line|#define DCRN_MALTXDEIR(base)&t;((base) + 0x7)&t;/* Tx Descriptor Error Interrupt */
DECL|macro|DCRN_MALTXEOBISR
mdefine_line|#define DCRN_MALTXEOBISR(base)&t;((base) + 0x6)&t;/* Tx End of Buffer Interrupt Status */
DECL|macro|DCRN_MALRXCARR
mdefine_line|#define DCRN_MALRXCARR(base)&t;((base) + 0x11)&t;/* RX Channed Active Reset Register */
DECL|macro|DCRN_MALRXCASR
mdefine_line|#define DCRN_MALRXCASR(base)&t;((base) + 0x10)&t;/* RX Channel Active Set Register */
DECL|macro|DCRN_MALRXDEIR
mdefine_line|#define DCRN_MALRXDEIR(base)&t;((base) + 0x13)&t;/* Rx Descriptor Error Interrupt */
DECL|macro|DCRN_MALRXEOBISR
mdefine_line|#define DCRN_MALRXEOBISR(base)&t;((base) + 0x12)&t;/* Rx End of Buffer Interrupt Status */
DECL|macro|DCRN_MALRXCTP0R
mdefine_line|#define DCRN_MALRXCTP0R(base)&t;((base) + 0x40)&t;/* Channel Rx 0 Channel Table Pointer */
DECL|macro|DCRN_MALRXCTP1R
mdefine_line|#define DCRN_MALRXCTP1R(base)&t;((base) + 0x41)&t;/* Channel Rx 1 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP0R
mdefine_line|#define DCRN_MALTXCTP0R(base)&t;((base) + 0x20)&t;/* Channel Tx 0 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP1R
mdefine_line|#define DCRN_MALTXCTP1R(base)&t;((base) + 0x21)&t;/* Channel Tx 1 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP2R
mdefine_line|#define DCRN_MALTXCTP2R(base)&t;((base) + 0x22)&t;/* Channel Tx 2 Channel Table Pointer */
DECL|macro|DCRN_MALTXCTP3R
mdefine_line|#define DCRN_MALTXCTP3R(base)&t;((base) + 0x23)&t;/* Channel Tx 3 Channel Table Pointer */
DECL|macro|DCRN_MALRCBS0
mdefine_line|#define DCRN_MALRCBS0(base)&t;((base) + 0x60)&t;/* Channel Rx 0 Channel Buffer Size */
DECL|macro|DCRN_MALRCBS1
mdefine_line|#define DCRN_MALRCBS1(base)&t;((base) + 0x61)&t;/* Channel Rx 1 Channel Buffer Size */
multiline_comment|/* DCRN_MALCR */
DECL|macro|MALCR_MMSR
mdefine_line|#define MALCR_MMSR&t;&t;0x80000000&t;/* MAL Software reset */
DECL|macro|MALCR_PLBP_1
mdefine_line|#define MALCR_PLBP_1&t;&t;0x00400000&t;/* MAL reqest priority: */
DECL|macro|MALCR_PLBP_2
mdefine_line|#define MALCR_PLBP_2&t;&t;0x00800000&t;/* lowsest is 00 */
DECL|macro|MALCR_PLBP_3
mdefine_line|#define MALCR_PLBP_3&t;&t;0x00C00000&t;/* highest */
DECL|macro|MALCR_GA
mdefine_line|#define MALCR_GA&t;&t;0x00200000&t;/* Guarded Active Bit */
DECL|macro|MALCR_OA
mdefine_line|#define MALCR_OA&t;&t;0x00100000&t;/* Ordered Active Bit */
DECL|macro|MALCR_PLBLE
mdefine_line|#define MALCR_PLBLE&t;&t;0x00080000&t;/* PLB Lock Error Bit */
DECL|macro|MALCR_PLBLT_1
mdefine_line|#define MALCR_PLBLT_1&t;&t;0x00040000&t;/* PLB Latency Timer */
DECL|macro|MALCR_PLBLT_2
mdefine_line|#define MALCR_PLBLT_2 &t;&t;0x00020000
DECL|macro|MALCR_PLBLT_3
mdefine_line|#define MALCR_PLBLT_3&t;&t;0x00010000
DECL|macro|MALCR_PLBLT_4
mdefine_line|#define MALCR_PLBLT_4&t;&t;0x00008000
DECL|macro|MALCR_PLBLT_DEFAULT
mdefine_line|#define MALCR_PLBLT_DEFAULT&t;0x00078000&t;/* JSP: Is this a valid default?? */
DECL|macro|MALCR_PLBB
mdefine_line|#define MALCR_PLBB&t;&t;0x00004000&t;/* PLB Burst Deactivation Bit */
DECL|macro|MALCR_OPBBL
mdefine_line|#define MALCR_OPBBL&t;&t;0x00000080&t;/* OPB Lock Bit */
DECL|macro|MALCR_EOPIE
mdefine_line|#define MALCR_EOPIE&t;&t;0x00000004&t;/* End Of Packet Interrupt Enable */
DECL|macro|MALCR_LEA
mdefine_line|#define MALCR_LEA&t;&t;0x00000002&t;/* Locked Error Active */
DECL|macro|MALCR_MSD
mdefine_line|#define MALCR_MSD&t;&t;0x00000001&t;/* MAL Scroll Descriptor Bit */
multiline_comment|/* DCRN_MALESR */
DECL|macro|MALESR_EVB
mdefine_line|#define MALESR_EVB&t;&t;0x80000000&t;/* Error Valid Bit */
DECL|macro|MALESR_CIDRX
mdefine_line|#define MALESR_CIDRX&t;&t;0x40000000&t;/* Channel ID Receive */
DECL|macro|MALESR_DE
mdefine_line|#define MALESR_DE&t;&t;0x00100000&t;/* Descriptor Error */
DECL|macro|MALESR_OEN
mdefine_line|#define MALESR_OEN&t;&t;0x00080000&t;/* OPB Non-Fullword Error */
DECL|macro|MALESR_OTE
mdefine_line|#define MALESR_OTE&t;&t;0x00040000&t;/* OPB Timeout Error */
DECL|macro|MALESR_OSE
mdefine_line|#define MALESR_OSE&t;&t;0x00020000&t;/* OPB Slave Error */
DECL|macro|MALESR_PEIN
mdefine_line|#define MALESR_PEIN&t;&t;0x00010000&t;/* PLB Bus Error Indication */
DECL|macro|MALESR_DEI
mdefine_line|#define MALESR_DEI&t;&t;0x00000010&t;/* Descriptor Error Interrupt */
DECL|macro|MALESR_ONEI
mdefine_line|#define MALESR_ONEI&t;&t;0x00000008&t;/* OPB Non-Fullword Error Interrupt */
DECL|macro|MALESR_OTEI
mdefine_line|#define MALESR_OTEI&t;&t;0x00000004&t;/* OPB Timeout Error Interrupt */
DECL|macro|MALESR_OSEI
mdefine_line|#define MALESR_OSEI&t;&t;0x00000002&t;/* OPB Slace Error Interrupt */
DECL|macro|MALESR_PBEI
mdefine_line|#define MALESR_PBEI&t;&t;0x00000001&t;/* PLB Bus Error Interrupt */
multiline_comment|/* DCRN_MALIER */
DECL|macro|MALIER_DE
mdefine_line|#define MALIER_DE&t;&t;0x00000010&t;/* Descriptor Error Interrupt Enable */
DECL|macro|MALIER_NE
mdefine_line|#define MALIER_NE&t;&t;0x00000008&t;/* OPB Non-word Transfer Int Enable */
DECL|macro|MALIER_TE
mdefine_line|#define MALIER_TE&t;&t;0x00000004&t;/* OPB Time Out Error Interrupt Enable */
DECL|macro|MALIER_OPBE
mdefine_line|#define MALIER_OPBE&t;&t;0x00000002&t;/* OPB Slave Error Interrupt Enable */
DECL|macro|MALIER_PLBE
mdefine_line|#define MALIER_PLBE&t;&t;0x00000001&t;/* PLB Error Interrupt Enable */
multiline_comment|/* DCRN_MALTXEOBISR */
DECL|macro|MALOBISR_CH0
mdefine_line|#define MALOBISR_CH0&t;&t;0x80000000&t;/* EOB channel 1 bit */
DECL|macro|MALOBISR_CH2
mdefine_line|#define MALOBISR_CH2&t;&t;0x40000000&t;/* EOB channel 2 bit */
macro_line|#ifdef DCRN_PLB0_BASE
DECL|macro|DCRN_PLB0_BESR
mdefine_line|#define DCRN_PLB0_BESR&t;(DCRN_PLB0_BASE + 0x0)
DECL|macro|DCRN_PLB0_BEAR
mdefine_line|#define DCRN_PLB0_BEAR&t;(DCRN_PLB0_BASE + 0x2)
multiline_comment|/* doesn&squot;t exist on stb03xxx? */
DECL|macro|DCRN_PLB0_ACR
mdefine_line|#define DCRN_PLB0_ACR&t;(DCRN_PLB0_BASE + 0x3)
macro_line|#endif
macro_line|#ifdef DCRN_PLB1_BASE
DECL|macro|DCRN_PLB1_BESR
mdefine_line|#define DCRN_PLB1_BESR&t;(DCRN_PLB1_BASE + 0x0)
DECL|macro|DCRN_PLB1_BEAR
mdefine_line|#define DCRN_PLB1_BEAR&t;(DCRN_PLB1_BASE + 0x1)
multiline_comment|/* doesn&squot;t exist on stb03xxx? */
DECL|macro|DCRN_PLB1_ACR
mdefine_line|#define DCRN_PLB1_ACR&t;(DCRN_PLB1_BASE + 0x2)
macro_line|#endif
macro_line|#ifdef DCRN_PLLMR_BASE
DECL|macro|DCRN_PLLMR
mdefine_line|#define DCRN_PLLMR&t;(DCRN_PLLMR_BASE + 0x0)&t;/* PL1 Mode */
macro_line|#endif
macro_line|#ifdef DCRN_POB0_BASE
DECL|macro|DCRN_POB0_BESR0
mdefine_line|#define DCRN_POB0_BESR0&t;(DCRN_POB0_BASE + 0x0)
DECL|macro|DCRN_POB0_BEAR
mdefine_line|#define DCRN_POB0_BEAR&t;(DCRN_POB0_BASE + 0x2)
DECL|macro|DCRN_POB0_BESR1
mdefine_line|#define DCRN_POB0_BESR1&t;(DCRN_POB0_BASE + 0x4)
macro_line|#endif
DECL|macro|DCRN_UIC_SR
mdefine_line|#define DCRN_UIC_SR(base)&t;(base + 0x0)
DECL|macro|DCRN_UIC_ER
mdefine_line|#define DCRN_UIC_ER(base)&t;(base + 0x2)
DECL|macro|DCRN_UIC_CR
mdefine_line|#define DCRN_UIC_CR(base)&t;(base + 0x3)
DECL|macro|DCRN_UIC_PR
mdefine_line|#define DCRN_UIC_PR(base)&t;(base + 0x4)
DECL|macro|DCRN_UIC_TR
mdefine_line|#define DCRN_UIC_TR(base)&t;(base + 0x5)
DECL|macro|DCRN_UIC_MSR
mdefine_line|#define DCRN_UIC_MSR(base)&t;(base + 0x6)
DECL|macro|DCRN_UIC_VR
mdefine_line|#define DCRN_UIC_VR(base)&t;(base + 0x7)
DECL|macro|DCRN_UIC_VCR
mdefine_line|#define DCRN_UIC_VCR(base)&t;(base + 0x8)
macro_line|#ifdef DCRN_SDRAM0_BASE
DECL|macro|DCRN_SDRAM0_CFGADDR
mdefine_line|#define DCRN_SDRAM0_CFGADDR&t;(DCRN_SDRAM0_BASE + 0x0)&t;/* Memory Controller Address */
DECL|macro|DCRN_SDRAM0_CFGDATA
mdefine_line|#define DCRN_SDRAM0_CFGDATA&t;(DCRN_SDRAM0_BASE + 0x1)&t;/* Memory Controller Data */
macro_line|#endif
macro_line|#ifdef DCRN_OCM0_BASE
DECL|macro|DCRN_OCMISARC
mdefine_line|#define DCRN_OCMISARC&t;(DCRN_OCM0_BASE + 0x0)&t;/* OCM Instr Side Addr Range Compare */
DECL|macro|DCRN_OCMISCR
mdefine_line|#define DCRN_OCMISCR&t;(DCRN_OCM0_BASE + 0x1)&t;/* OCM Instr Side Control */
DECL|macro|DCRN_OCMDSARC
mdefine_line|#define DCRN_OCMDSARC&t;(DCRN_OCM0_BASE + 0x2)&t;/* OCM Data Side Addr Range Compare */
DECL|macro|DCRN_OCMDSCR
mdefine_line|#define DCRN_OCMDSCR&t;(DCRN_OCM0_BASE + 0x3)&t;/* OCM Data Side Control */
macro_line|#endif
macro_line|#endif&t;&t;&t;&t;/* __ASM_IBM405_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
