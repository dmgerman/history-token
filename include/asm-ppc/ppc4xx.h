multiline_comment|/*&n; *&n; *    Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Module name: ppc4xx.h&n; *&n; *    Description:&n; *&t;A generic include file which pulls in appropriate include files&n; *      for specific board types based on configuration settings.&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __PPC4XX_H__
DECL|macro|__PPC4XX_H__
mdefine_line|#define&t;__PPC4XX_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#if defined(CONFIG_OAK)
macro_line|#include &lt;asm/oak.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_WALNUT)
macro_line|#include &lt;asm/walnut.h&gt;
macro_line|#endif
multiline_comment|/* IO_BASE is for PCI I/O.&n; * ISA not supported, just here to resolve copilation.&n; */
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE&t;0xe8000000&t;/* The PCI address window */
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE&t;0
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET&t;0
r_extern
r_int
r_int
id|isa_io_base
suffix:semicolon
multiline_comment|/*&n; * The &quot;residual&quot; board information structure the boot loader passes&n; * into the kernel.&n; */
r_extern
r_int
r_char
id|__res
(braket
)braket
suffix:semicolon
multiline_comment|/* I don&squot;t know if this is general to 4xx, or unique to a specific&n; * processor or board.  In any case it is easy to move.&n; */
DECL|macro|PPC4xx_PCI_IO_ADDR
mdefine_line|#define PPC4xx_PCI_IO_ADDR&t;((uint)0xe8000000)
DECL|macro|PPC4xx_PCI_IO_SIZE
mdefine_line|#define PPC4xx_PCI_IO_SIZE&t;((uint)64*1024)
DECL|macro|PPC4xx_PCI_CFG_ADDR
mdefine_line|#define PPC4xx_PCI_CFG_ADDR&t;((uint)0xeec00000)
DECL|macro|PPC4xx_PCI_CFG_SIZE
mdefine_line|#define PPC4xx_PCI_CFG_SIZE&t;((uint)4*1024)
DECL|macro|PPC4xx_PCI_LCFG_ADDR
mdefine_line|#define PPC4xx_PCI_LCFG_ADDR&t;((uint)0xef400000)
DECL|macro|PPC4xx_PCI_LCFG_SIZE
mdefine_line|#define PPC4xx_PCI_LCFG_SIZE&t;((uint)4*1024)
DECL|macro|PPC4xx_ONB_IO_ADDR
mdefine_line|#define PPC4xx_ONB_IO_ADDR&t;((uint)0xef600000)
DECL|macro|PPC4xx_ONB_IO_SIZE
mdefine_line|#define PPC4xx_ONB_IO_SIZE&t;((uint)4*1024)
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* Device Control Registers unique to 4xx */
DECL|macro|DCRN_BEAR
mdefine_line|#define&t;DCRN_BEAR&t;0x090&t;/* Bus Error Address Register */
DECL|macro|DCRN_BESR
mdefine_line|#define&t;DCRN_BESR&t;0x091&t;/* Bus Error Syndrome Register */
DECL|macro|BESR_DSES
mdefine_line|#define&t;  BESR_DSES    &t;0x80000000&t;/* Data-Side Error Status */
DECL|macro|BESR_DMES
mdefine_line|#define&t;  BESR_DMES&t;0x40000000&t;/* DMA Error Status */
DECL|macro|BESR_RWS
mdefine_line|#define&t;  BESR_RWS&t;0x20000000&t;/* Read/Write Status */
DECL|macro|BESR_ETMASK
mdefine_line|#define&t;  BESR_ETMASK&t;0x1C000000&t;/* Error Type */
DECL|macro|ET_PROT
mdefine_line|#define&t;    ET_PROT&t;0
DECL|macro|ET_PARITY
mdefine_line|#define&t;    ET_PARITY&t;1
DECL|macro|ET_NCFG
mdefine_line|#define&t;    ET_NCFG&t;2
DECL|macro|ET_BUSERR
mdefine_line|#define&t;    ET_BUSERR&t;4
DECL|macro|ET_BUSTO
mdefine_line|#define&t;    ET_BUSTO&t;6
DECL|macro|DCRN_CHCR0
mdefine_line|#define DCRN_CHCR0&t;0x0B1&t;/* Chip Control Register 1                    */
DECL|macro|DCRN_CHCR1
mdefine_line|#define DCRN_CHCR1&t;0x0B2&t;/* Chip Control Register 2                    */
DECL|macro|DCRN_CHPSR
mdefine_line|#define DCRN_CHPSR&t;0x0B4&t;/* Chip Pin Strapping                         */
DECL|macro|DCRN_CPMER
mdefine_line|#define DCRN_CPMER&t;0x0B9&t;/* CPM Enable                                 */
DECL|macro|DCRN_CPMFR
mdefine_line|#define DCRN_CPMFR&t;0x0BA&t;/* CPM Force                                  */
DECL|macro|CPM_IIC
mdefine_line|#define   CPM_IIC&t;0x80000000  /* IIC interface                          */
DECL|macro|CPM_PCI
mdefine_line|#define   CPM_PCI&t;0x40000000  /* PCI bridge                             */
DECL|macro|CPM_CPU
mdefine_line|#define   CPM_CPU&t;0x20000000  /* processor core                         */
DECL|macro|CPM_DMA
mdefine_line|#define   CPM_DMA&t;0x10000000  /* DMA controller                         */
DECL|macro|CPM_BRG
mdefine_line|#define   CPM_BRG&t;0x08000000  /* PLB to OPB bridge                      */
DECL|macro|CPM_DCP
mdefine_line|#define   CPM_DCP&t;0x04000000  /* CodePack                               */
DECL|macro|CPM_EBC
mdefine_line|#define   CPM_EBC&t;0x02000000  /* ROM/SRAM peripheral controller         */
DECL|macro|CPM_SDRAM
mdefine_line|#define   CPM_SDRAM&t;0x01000000  /* SDRAM memory controller                */
DECL|macro|CPM_PLB
mdefine_line|#define   CPM_PLB&t;0x00800000  /* PLB bus arbiter                        */
DECL|macro|CPM_GPIO
mdefine_line|#define   CPM_GPIO&t;0x00400000  /* General Purpose IO (??)                */
DECL|macro|CPM_UART0
mdefine_line|#define   CPM_UART0&t;0x00200000  /* serial port 0                          */
DECL|macro|CPM_UART1
mdefine_line|#define   CPM_UART1&t;0x00100000  /* serial port 1                          */
DECL|macro|CPM_UIC
mdefine_line|#define   CPM_UIC&t;0x00080000  /* Universal Interrupt Controller         */
DECL|macro|CPM_TMRCLK
mdefine_line|#define   CPM_TMRCLK&t;0x00040000  /* CPU timers                             */
DECL|macro|CPM_EMAC_MM
mdefine_line|#define   CPM_EMAC_MM&t;0x00020000  /* on-chip ethernet MM unit               */
DECL|macro|CPM_EMAC_RM
mdefine_line|#define   CPM_EMAC_RM&t;0x00010000  /* on-chip ethernet RM unit               */
DECL|macro|CPM_EMAC_TM
mdefine_line|#define   CPM_EMAC_TM&t;0x00008000  /* on-chip ethernet TM unit               */
DECL|macro|DCRN_CPMSR
mdefine_line|#define DCRN_CPMSR&t;0x0B8&t;/* CPM Status                                 */
DECL|macro|DCRN_DMACR0
mdefine_line|#define&t;DCRN_DMACR0&t;0x100&t;/* DMA Channel Control Register 0             */
DECL|macro|DCRN_DMACT0
mdefine_line|#define&t;DCRN_DMACT0&t;0x101&t;/* DMA Count Register 0                       */
DECL|macro|DCRN_DMADA0
mdefine_line|#define&t;DCRN_DMADA0&t;0x102&t;/* DMA Destination Address Register 0         */
DECL|macro|DCRN_DMASA0
mdefine_line|#define&t;DCRN_DMASA0&t;0x103&t;/* DMA Source Address Register 0              */
DECL|macro|DCRN_ASG0
mdefine_line|#define DCRN_ASG0&t;0x104&t;/* DMA Scatter/Gather Descriptor Addr 0       */
DECL|macro|DCRN_DMACR1
mdefine_line|#define&t;DCRN_DMACR1&t;0x108&t;/* DMA Channel Control Register 1             */
DECL|macro|DCRN_DMACT1
mdefine_line|#define&t;DCRN_DMACT1&t;0x109&t;/* DMA Count Register 1                       */
DECL|macro|DCRN_DMADA1
mdefine_line|#define&t;DCRN_DMADA1&t;0x10A&t;/* DMA Destination Address Register 1         */
DECL|macro|DCRN_DMASA1
mdefine_line|#define&t;DCRN_DMASA1&t;0x10B&t;/* DMA Source Address Register 1              */
DECL|macro|DCRN_ASG1
mdefine_line|#define DCRN_ASG1&t;0x10C&t;/* DMA Scatter/Gather Descriptor Addr 1       */
DECL|macro|DCRN_DMACR2
mdefine_line|#define&t;DCRN_DMACR2&t;0x110&t;/* DMA Channel Control Register 2             */
DECL|macro|DCRN_DMACT2
mdefine_line|#define&t;DCRN_DMACT2&t;0x111&t;/* DMA Count Register 2                       */
DECL|macro|DCRN_DMADA2
mdefine_line|#define&t;DCRN_DMADA2&t;0x112&t;/* DMA Destination Address Register 2         */
DECL|macro|DCRN_DMASA2
mdefine_line|#define&t;DCRN_DMASA2&t;0x113&t;/* DMA Source Address Register 2              */
DECL|macro|DCRN_ASG2
mdefine_line|#define DCRN_ASG2&t;0x114&t;/* DMA Scatter/Gather Descriptor Addr 2       */
DECL|macro|DCRN_DMACR3
mdefine_line|#define&t;DCRN_DMACR3&t;0x118&t;/* DMA Channel Control Register 3             */
DECL|macro|DCRN_DMACT3
mdefine_line|#define&t;DCRN_DMACT3&t;0x119&t;/* DMA Count Register 3                       */
DECL|macro|DCRN_DMADA3
mdefine_line|#define&t;DCRN_DMADA3&t;0x11A&t;/* DMA Destination Address Register 3         */
DECL|macro|DCRN_DMASA3
mdefine_line|#define&t;DCRN_DMASA3&t;0x11B&t;/* DMA Source Address Register 3              */
DECL|macro|DCRN_ASG3
mdefine_line|#define DCRN_ASG3&t;0x11C&t;/* DMA Scatter/Gather Descriptor Addr 3       */
DECL|macro|DCRN_DMASR
mdefine_line|#define&t;DCRN_DMASR&t;0x120&t;/* DMA Status Register                        */
DECL|macro|DCRN_ASGC
mdefine_line|#define DCRN_ASGC&t;0x123&t;/* DMA Scatter/Gather Command                 */
DECL|macro|DCRN_ADR
mdefine_line|#define DCRN_ADR&t;0x124&t;/* DMA Address Decode                         */
DECL|macro|DCRN_SLP
mdefine_line|#define DCRN_SLP        0x125   /* DMA Sleep Register                         */
DECL|macro|DCRN_POL
mdefine_line|#define DCRN_POL        0x126   /* DMA Polarity Register                      */
DECL|macro|DCRN_EBCCFGADR
mdefine_line|#define DCRN_EBCCFGADR&t;0x012&t;/* Peripheral Controller Address              */
DECL|macro|DCRN_EBCCFGDATA
mdefine_line|#define DCRN_EBCCFGDATA&t;0x013&t;/* Peripheral Controller Data                 */
DECL|macro|DCRN_EXISR
mdefine_line|#define&t;DCRN_EXISR&t;0x040    /* External Interrupt Status Register */
DECL|macro|DCRN_EXIER
mdefine_line|#define&t;DCRN_EXIER&t;0x042    /* External Interrupt Enable Register */
DECL|macro|EXIER_CIE
mdefine_line|#define&t;  EXIER_CIE&t;0x80000000&t;/* Critical Interrupt Enable */
DECL|macro|EXIER_SRIE
mdefine_line|#define&t;  EXIER_SRIE&t;0x08000000&t;/* Serial Port Rx Int. Enable */
DECL|macro|EXIER_STIE
mdefine_line|#define&t;  EXIER_STIE&t;0x04000000&t;/* Serial Port Tx Int. Enable */
DECL|macro|EXIER_JRIE
mdefine_line|#define&t;  EXIER_JRIE&t;0x02000000&t;/* JTAG Serial Port Rx Int. Enable */
DECL|macro|EXIER_JTIE
mdefine_line|#define&t;  EXIER_JTIE&t;0x01000000&t;/* JTAG Serial Port Tx Int. Enable */
DECL|macro|EXIER_D0IE
mdefine_line|#define&t;  EXIER_D0IE&t;0x00800000&t;/* DMA Channel 0 Interrupt Enable */
DECL|macro|EXIER_D1IE
mdefine_line|#define&t;  EXIER_D1IE&t;0x00400000&t;/* DMA Channel 1 Interrupt Enable */
DECL|macro|EXIER_D2IE
mdefine_line|#define&t;  EXIER_D2IE&t;0x00200000&t;/* DMA Channel 2 Interrupt Enable */
DECL|macro|EXIER_D3IE
mdefine_line|#define&t;  EXIER_D3IE&t;0x00100000&t;/* DMA Channel 3 Interrupt Enable */
DECL|macro|EXIER_E0IE
mdefine_line|#define&t;  EXIER_E0IE&t;0x00000010&t;/* External Interrupt 0 Enable */
DECL|macro|EXIER_E1IE
mdefine_line|#define&t;  EXIER_E1IE&t;0x00000008&t;/* External Interrupt 1 Enable */
DECL|macro|EXIER_E2IE
mdefine_line|#define&t;  EXIER_E2IE&t;0x00000004&t;/* External Interrupt 2 Enable */
DECL|macro|EXIER_E3IE
mdefine_line|#define&t;  EXIER_E3IE&t;0x00000002&t;/* External Interrupt 3 Enable */
DECL|macro|EXIER_E4IE
mdefine_line|#define&t;  EXIER_E4IE&t;0x00000001&t;/* External Interrupt 4 Enable */
DECL|macro|DCRN_IOCR
mdefine_line|#define&t;DCRN_IOCR&t;0x0A0    /* Input/Output Configuration Register */
DECL|macro|IOCR_E0TE
mdefine_line|#define&t;  IOCR_E0TE&t;0x80000000
DECL|macro|IOCR_E0LP
mdefine_line|#define&t;  IOCR_E0LP&t;0x40000000
DECL|macro|IOCR_E1TE
mdefine_line|#define&t;  IOCR_E1TE&t;0x20000000
DECL|macro|IOCR_E1LP
mdefine_line|#define&t;  IOCR_E1LP&t;0x10000000
DECL|macro|IOCR_E2TE
mdefine_line|#define&t;  IOCR_E2TE&t;0x08000000
DECL|macro|IOCR_E2LP
mdefine_line|#define&t;  IOCR_E2LP&t;0x04000000
DECL|macro|IOCR_E3TE
mdefine_line|#define&t;  IOCR_E3TE&t;0x02000000
DECL|macro|IOCR_E3LP
mdefine_line|#define&t;  IOCR_E3LP&t;0x01000000
DECL|macro|IOCR_E4TE
mdefine_line|#define&t;  IOCR_E4TE&t;0x00800000
DECL|macro|IOCR_E4LP
mdefine_line|#define&t;  IOCR_E4LP&t;0x00400000
DECL|macro|IOCR_EDT
mdefine_line|#define&t;  IOCR_EDT     &t;0x00080000
DECL|macro|IOCR_SOR
mdefine_line|#define&t;  IOCR_SOR     &t;0x00040000
DECL|macro|IOCR_EDO
mdefine_line|#define&t;  IOCR_EDO&t;0x00008000
DECL|macro|IOCR_2XC
mdefine_line|#define&t;  IOCR_2XC&t;0x00004000
DECL|macro|IOCR_ATC
mdefine_line|#define&t;  IOCR_ATC&t;0x00002000
DECL|macro|IOCR_SPD
mdefine_line|#define&t;  IOCR_SPD&t;0x00001000
DECL|macro|IOCR_BEM
mdefine_line|#define&t;  IOCR_BEM&t;0x00000800
DECL|macro|IOCR_PTD
mdefine_line|#define&t;  IOCR_PTD&t;0x00000400
DECL|macro|IOCR_ARE
mdefine_line|#define&t;  IOCR_ARE&t;0x00000080
DECL|macro|IOCR_DRC
mdefine_line|#define&t;  IOCR_DRC&t;0x00000020
DECL|macro|IOCR_RDM
mdefine_line|#define&t;  IOCR_RDM(x)&t;(((x) &amp; 0x3) &lt;&lt; 3)
DECL|macro|IOCR_TCS
mdefine_line|#define&t;  IOCR_TCS&t;0x00000004
DECL|macro|IOCR_SCS
mdefine_line|#define&t;  IOCR_SCS&t;0x00000002
DECL|macro|IOCR_SPC
mdefine_line|#define&t;  IOCR_SPC&t;0x00000001
DECL|macro|DCRN_KIAR
mdefine_line|#define DCRN_KIAR&t;0x014&t;/* Decompression Controller Address           */
DECL|macro|DCRN_KIDR
mdefine_line|#define DCRN_KIDR&t;0x015&t;/* Decompression Controller Data              */
DECL|macro|DCRN_MALCR
mdefine_line|#define DCRN_MALCR&t;0x180&t;/* MAL Configuration                          */
DECL|macro|MALCR_MMSR
mdefine_line|#define   MALCR_MMSR    0x80000000    /* MAL Software reset                   */
DECL|macro|MALCR_PLBP_1
mdefine_line|#define   MALCR_PLBP_1  0x00400000    /* MAL reqest priority:                 */
DECL|macro|MALCR_PLBP_2
mdefine_line|#define   MALCR_PLBP_2  0x00800000    /*   lowsest is 00                      */
DECL|macro|MALCR_PLBP_3
mdefine_line|#define   MALCR_PLBP_3  0x00C00000    /*   highest                            */
DECL|macro|MALCR_GA
mdefine_line|#define   MALCR_GA      0x00200000    /* Guarded Active Bit                   */
DECL|macro|MALCR_OA
mdefine_line|#define   MALCR_OA      0x00100000    /* Ordered Active Bit                   */
DECL|macro|MALCR_PLBLE
mdefine_line|#define   MALCR_PLBLE   0x00080000    /* PLB Lock Error Bit                   */
DECL|macro|MALCR_PLBLT_1
mdefine_line|#define   MALCR_PLBLT_1 0x00040000    /* PLB Latency Timer                    */
DECL|macro|MALCR_PLBLT_2
mdefine_line|#define   MALCR_PLBLT_2 0x00020000
DECL|macro|MALCR_PLBLT_3
mdefine_line|#define   MALCR_PLBLT_3 0x00010000
DECL|macro|MALCR_PLBLT_4
mdefine_line|#define   MALCR_PLBLT_4 0x00008000
DECL|macro|MALCR_PLBLT_DEFAULT
mdefine_line|#define   MALCR_PLBLT_DEFAULT 0x00078000 /* JSP: Is this a valid default??    */
DECL|macro|MALCR_PLBB
mdefine_line|#define   MALCR_PLBB    0x00004000    /* PLB Burst Deactivation Bit           */
DECL|macro|MALCR_OPBBL
mdefine_line|#define   MALCR_OPBBL   0x00000080    /* OPB Lock Bit                         */
DECL|macro|MALCR_EOPIE
mdefine_line|#define   MALCR_EOPIE   0x00000004    /* End Of Packet Interrupt Enable       */
DECL|macro|MALCR_LEA
mdefine_line|#define   MALCR_LEA     0x00000002    /* Locked Error Active                  */
DECL|macro|MALCR_MSD
mdefine_line|#define   MALCR_MSD     0x00000001    /* MAL Scroll Descriptor Bit            */
DECL|macro|DCRN_MALDBR
mdefine_line|#define DCRN_MALDBR     0x183   /* Debug Register                             */
DECL|macro|DCRN_MALESR
mdefine_line|#define DCRN_MALESR&t;0x181&t;/* Error Status                               */
DECL|macro|MALESR_EVB
mdefine_line|#define   MALESR_EVB    0x80000000    /* Error Valid Bit                      */
DECL|macro|MALESR_CID
mdefine_line|#define   MALESR_CID    0x40000000    /* Channel ID Bit  for channel 0        */
DECL|macro|MALESR_DE
mdefine_line|#define   MALESR_DE     0x00100000    /* Descriptor Error                     */
DECL|macro|MALESR_OEN
mdefine_line|#define   MALESR_OEN    0x00080000    /* OPB Non-Fullword Error               */
DECL|macro|MALESR_OTE
mdefine_line|#define   MALESR_OTE    0x00040000    /* OPB Timeout Error                    */
DECL|macro|MALESR_OSE
mdefine_line|#define   MALESR_OSE    0x00020000    /* OPB Slave Error                      */
DECL|macro|MALESR_PEIN
mdefine_line|#define   MALESR_PEIN   0x00010000    /* PLB Bus Error Indication             */
DECL|macro|MALESR_DEI
mdefine_line|#define   MALESR_DEI    0x00000010    /* Descriptor Error Interrupt           */
DECL|macro|MALESR_ONEI
mdefine_line|#define   MALESR_ONEI   0x00000008    /* OPB Non-Fullword Error Interrupt     */
DECL|macro|MALESR_OTEI
mdefine_line|#define   MALESR_OTEI   0x00000004    /* OPB Timeout Error Interrupt          */
DECL|macro|MALESR_OSEI
mdefine_line|#define   MALESR_OSEI   0x00000002    /* OPB Slace Error Interrupt            */
DECL|macro|MALESR_PBEI
mdefine_line|#define   MALESR_PBEI   0x00000001    /* PLB Bus Error Interrupt              */
DECL|macro|DCRN_MALIER
mdefine_line|#define DCRN_MALIER&t;0x182&t;/* Interrupt Enable                           */
DECL|macro|MALIER_DE
mdefine_line|#define   MALIER_DE     0x00000010    /* Descriptor Error Interrupt Enable    */
DECL|macro|MALIER_NE
mdefine_line|#define   MALIER_NE     0x00000008    /* OPB Non-word Transfer Int Enable     */
DECL|macro|MALIER_TE
mdefine_line|#define   MALIER_TE     0x00000004    /* OPB Time Out Error Interrupt Enable  */
DECL|macro|MALIER_OPBE
mdefine_line|#define   MALIER_OPBE   0x00000002    /* OPB Slave Error Interrupt Enable     */
DECL|macro|MALIER_PLBE
mdefine_line|#define   MALIER_PLBE   0x00000001    /* PLB Error Interrupt Enable           */
DECL|macro|DCRN_MALTXCARR
mdefine_line|#define DCRN_MALTXCARR  0x185   /* TX Channed Active Reset Register           */
DECL|macro|DCRN_MALTXCASR
mdefine_line|#define DCRN_MALTXCASR  0x184   /* TX Channel Active Set Register             */
DECL|macro|DCRN_MALTXDEIR
mdefine_line|#define DCRN_MALTXDEIR&t;0x187&t;/* Tx Descriptor Error Interrupt              */
DECL|macro|DCRN_MALTXEOBISR
mdefine_line|#define DCRN_MALTXEOBISR    0x186   /* Tx End of Buffer Interrupt Status      */
DECL|macro|MALOBISR_CH0
mdefine_line|#define   MALOBISR_CH0  0x80000000    /* EOB channel 1 bit                    */
DECL|macro|MALOBISR_CH2
mdefine_line|#define   MALOBISR_CH2  0x40000000    /* EOB channel 2 bit                    */
DECL|macro|DCRN_MALRXCARR
mdefine_line|#define DCRN_MALRXCARR  0x191   /* RX Channed Active Reset Register           */
DECL|macro|DCRN_MALRXCASR
mdefine_line|#define DCRN_MALRXCASR  0x190   /* RX Channel Active Set Register             */
DECL|macro|DCRN_MALRXDEIR
mdefine_line|#define DCRN_MALRXDEIR&t;0x193&t;/* Rx Descriptor Error Interrupt              */
DECL|macro|DCRN_MALRXEOBISR
mdefine_line|#define DCRN_MALRXEOBISR    0x192   /* Rx End of Buffer Interrupt Status      */
DECL|macro|DCRN_MALRXCTP0R
mdefine_line|#define DCRN_MALRXCTP0R&t;0x1C0&t;/* Channel Rx 0 Channel Table Pointer         */
DECL|macro|DCRN_MALTXCTP0R
mdefine_line|#define DCRN_MALTXCTP0R&t;0x1A0&t;/* Channel Tx 0 Channel Table Pointer         */
DECL|macro|DCRN_MALTXCTP1R
mdefine_line|#define DCRN_MALTXCTP1R&t;0x1A1&t;/* Channel Tx 1 Channel Table Pointer         */
DECL|macro|DCRN_MALRCBS0
mdefine_line|#define DCRN_MALRCBS0&t;0x1E0&t;/* Channel Rx 0 Channel Buffer Size           */
DECL|macro|DCRN_MEMCFGADR
mdefine_line|#define DCRN_MEMCFGADR&t;0x010&t;/* Memory Controller Address                  */
DECL|macro|DCRN_MEMCFGDATA
mdefine_line|#define DCRN_MEMCFGDATA&t;0x011&t;/* Memory Controller Data                     */
DECL|macro|DCRN_OCMISARC
mdefine_line|#define DCRN_OCMISARC&t;0x018&t;/* OCM Instr Side Addr Range Compare          */
DECL|macro|DCRN_OCMISCR
mdefine_line|#define DCRN_OCMISCR&t;0x019&t;/* OCM Instr Side Control                     */
DECL|macro|DCRN_OCMDSARC
mdefine_line|#define DCRN_OCMDSARC&t;0x01A&t;/* OCM Data Side Addr Range Compare           */
DECL|macro|DCRN_OCMDSCR
mdefine_line|#define DCRN_OCMDSCR&t;0x01B&t;/* OCM Data Side Control                      */
DECL|macro|DCRN_PLB0_ACR
mdefine_line|#define DCRN_PLB0_ACR&t;0x087&t;/* PLB Arbiter Control                        */
DECL|macro|DCRN_PLB0_BEAR
mdefine_line|#define DCRN_PLB0_BEAR&t;0x086&t;/* PLB Error Address                          */
DECL|macro|DCRN_PLB0_BESR
mdefine_line|#define DCRN_PLB0_BESR&t;0x084&t;/* PLB Error Status                           */
DECL|macro|DCRN_PLLMR
mdefine_line|#define DCRN_PLLMR&t;0x0B0&t;/* PLL Mode                                   */
DECL|macro|DCRN_POB0_BEAR
mdefine_line|#define DCRN_POB0_BEAR&t;0x0A2&t;/* PLB to OPB Error Address                   */
DECL|macro|DCRN_POB0_BESR0
mdefine_line|#define DCRN_POB0_BESR0&t;0x0A0&t;/* PLB to OPB Error Status Register 1         */
DECL|macro|DCRN_POB0_BESR1
mdefine_line|#define DCRN_POB0_BESR1&t;0x0A4&t;/* PLB to OPB Error Status Register 1         */
DECL|macro|DCRN_UICCR
mdefine_line|#define DCRN_UICCR&t;0x0C3&t;/* UIC Critical                               */
DECL|macro|DCRN_UICER
mdefine_line|#define DCRN_UICER&t;0x0C2&t;/* UIC Enable                                 */
DECL|macro|DCRN_UICPR
mdefine_line|#define DCRN_UICPR&t;0x0C4&t;/* UIC Polarity                               */
DECL|macro|DCRN_UICSR
mdefine_line|#define DCRN_UICSR&t;0x0C0&t;/* UIC Status                                 */
DECL|macro|DCRN_UICTR
mdefine_line|#define DCRN_UICTR&t;0x0C5&t;/* UIC Triggering                             */
DECL|macro|DCRN_UICMSR
mdefine_line|#define DCRN_UICMSR&t;0x0C6&t;/* UIC Masked Status                          */
DECL|macro|DCRN_UICVR
mdefine_line|#define DCRN_UICVR&t;0x0C7&t;/* UIC Vector                                 */
DECL|macro|DCRN_UICVCR
mdefine_line|#define DCRN_UICVCR&t;0x0C8&t;/* UIC Vector Configuration                   */
DECL|macro|UIC_U0
mdefine_line|#define   UIC_U0&t;0x80000000  /* UART0                                  */
DECL|macro|UIC_U1
mdefine_line|#define   UIC_U1&t;0x40000000  /* UART1                                  */
DECL|macro|UIC_IIC
mdefine_line|#define   UIC_IIC&t;0x20000000  /* IIC                                    */
DECL|macro|UIC_EM
mdefine_line|#define   UIC_EM&t;0x10000000  /* External Master                        */
DECL|macro|UIC_PCI
mdefine_line|#define   UIC_PCI&t;0x08000000  /* PCI                                    */
DECL|macro|UIC_D0
mdefine_line|#define   UIC_D0&t;0x04000000  /* DMA Channel 0                          */
DECL|macro|UIC_D1
mdefine_line|#define   UIC_D1&t;0x02000000  /* DMA Channel 1                          */
DECL|macro|UIC_D2
mdefine_line|#define   UIC_D2&t;0x01000000  /* DMA Channel 2                          */
DECL|macro|UIC_D3
mdefine_line|#define   UIC_D3&t;0x00800000  /* DMA Channel 3                          */
DECL|macro|UIC_EW
mdefine_line|#define   UIC_EW&t;0x00400000  /* Ethernet Wake-up                       */
DECL|macro|UIC_MS
mdefine_line|#define   UIC_MS&t;0x00200000  /* MAL SERR                               */
DECL|macro|UIC_MTE
mdefine_line|#define   UIC_MTE&t;0x00100000  /* MAL TX EOB                             */
DECL|macro|UIC_MRE
mdefine_line|#define   UIC_MRE&t;0x00080000  /* MAL RX EOB                             */
DECL|macro|UIC_MTD
mdefine_line|#define   UIC_MTD&t;0x00040000  /* MAL TX DE                              */
DECL|macro|UIC_MRD
mdefine_line|#define   UIC_MRD&t;0x00020000  /* MAL RX DE                              */
DECL|macro|UIC_E
mdefine_line|#define   UIC_E&t;&t;0x00010000  /* Ethernet                               */
DECL|macro|UIC_EPS
mdefine_line|#define   UIC_EPS&t;0x00008000  /* External PCI SERR                      */
DECL|macro|UIC_EC
mdefine_line|#define   UIC_EC&t;0x00004000  /* ECC Correctable Error                  */
DECL|macro|UIC_PPM
mdefine_line|#define   UIC_PPM&t;0x00002000  /* PCI Power Management                   */
multiline_comment|/*&n;**&t;&t;&t;0x00001000  reserved&n;**&t;&t;&t;0x00000800  reserved&n;**&t;&t;&t;0x00000400  reserved&n;**&t;&t;&t;0x00000200  reserved&n;**&t;&t;&t;0x00000100  reserved&n;**&t;&t;&t;0x00000080  reserved&n;*/
DECL|macro|UIC_EIR0
mdefine_line|#define   UIC_EIR0&t;0x00000040  /* External IRQ 0                         */
DECL|macro|UIC_EIR1
mdefine_line|#define   UIC_EIR1&t;0x00000020  /* External IRQ 0                         */
DECL|macro|UIC_EIR2
mdefine_line|#define   UIC_EIR2&t;0x00000010  /* External IRQ 0                         */
DECL|macro|UIC_EIR3
mdefine_line|#define   UIC_EIR3&t;0x00000008  /* External IRQ 0                         */
DECL|macro|UIC_EIR4
mdefine_line|#define   UIC_EIR4&t;0x00000004  /* External IRQ 0                         */
DECL|macro|UIC_EIR5
mdefine_line|#define   UIC_EIR5&t;0x00000002  /* External IRQ 0                         */
DECL|macro|UIC_EIR6
mdefine_line|#define   UIC_EIR6&t;0x00000001  /* External IRQ 0                         */
macro_line|#endif /* __PPC4XX_H__ */
macro_line|#endif /* __KERNEL__ */
eof
