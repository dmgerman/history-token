multiline_comment|/*&n; * linux/include/asm/arch-iop3xx/iop321.h&n; *&n; * Intel IOP321 Chip definitions&n; *&n; * Author: Rory Bolt &lt;rorybolt@pacbell.net&gt;&n; * Copyright (C) 2002 Rory Bolt&n; * Copyright (C) 2004 Intel Corp.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _IOP321_HW_H_
DECL|macro|_IOP321_HW_H_
mdefine_line|#define _IOP321_HW_H_
multiline_comment|/*&n; * This is needed for mixed drivers that need to work on all&n; * IOP3xx variants but behave slightly differently on each.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef&t;CONFIG_ARCH_IOP321
DECL|macro|iop_is_321
mdefine_line|#define iop_is_321() (((processor_id &amp; 0xfffff5e0) == 0x69052420))
macro_line|#else
DECL|macro|iop_is_321
mdefine_line|#define&t;iop_is_321()&t;0
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * IOP321 I/O and Mem space regions for PCI autoconfiguration&n; */
DECL|macro|IOP321_PCI_IO_WINDOW_SIZE
mdefine_line|#define IOP321_PCI_IO_WINDOW_SIZE   0x10000
DECL|macro|IOP321_PCI_LOWER_IO_PA
mdefine_line|#define IOP321_PCI_LOWER_IO_PA      0x90000000
DECL|macro|IOP321_PCI_LOWER_IO_VA
mdefine_line|#define IOP321_PCI_LOWER_IO_VA      0xfe000000
DECL|macro|IOP321_PCI_LOWER_IO_BA
mdefine_line|#define IOP321_PCI_LOWER_IO_BA      (*IOP321_OIOWTVR)
DECL|macro|IOP321_PCI_UPPER_IO_PA
mdefine_line|#define IOP321_PCI_UPPER_IO_PA      (IOP321_PCI_LOWER_IO_PA + IOP321_PCI_IO_WINDOW_SIZE - 1)
DECL|macro|IOP321_PCI_UPPER_IO_VA
mdefine_line|#define IOP321_PCI_UPPER_IO_VA      (IOP321_PCI_LOWER_IO_VA + IOP321_PCI_IO_WINDOW_SIZE - 1)
DECL|macro|IOP321_PCI_UPPER_IO_BA
mdefine_line|#define IOP321_PCI_UPPER_IO_BA      (IOP321_PCI_LOWER_IO_BA + IOP321_PCI_IO_WINDOW_SIZE - 1)
DECL|macro|IOP321_PCI_IO_OFFSET
mdefine_line|#define IOP321_PCI_IO_OFFSET        (IOP321_PCI_LOWER_IO_VA - IOP321_PCI_LOWER_IO_BA)
DECL|macro|IOP321_PCI_MEM_WINDOW_SIZE
mdefine_line|#define IOP321_PCI_MEM_WINDOW_SIZE  (~*IOP321_IALR1 + 1)
DECL|macro|IOP321_PCI_LOWER_MEM_PA
mdefine_line|#define IOP321_PCI_LOWER_MEM_PA     0x80000000
DECL|macro|IOP321_PCI_LOWER_MEM_VA
mdefine_line|#define IOP321_PCI_LOWER_MEM_VA     0x80000000
DECL|macro|IOP321_PCI_LOWER_MEM_BA
mdefine_line|#define IOP321_PCI_LOWER_MEM_BA     (*IOP321_OMWTVR0)
DECL|macro|IOP321_PCI_UPPER_MEM_PA
mdefine_line|#define IOP321_PCI_UPPER_MEM_PA     (IOP321_PCI_LOWER_MEM_PA + IOP321_PCI_MEM_WINDOW_SIZE - 1)
DECL|macro|IOP321_PCI_UPPER_MEM_VA
mdefine_line|#define IOP321_PCI_UPPER_MEM_VA     (IOP321_PCI_LOWER_MEM_VA + IOP321_PCI_MEM_WINDOW_SIZE - 1)
DECL|macro|IOP321_PCI_UPPER_MEM_BA
mdefine_line|#define IOP321_PCI_UPPER_MEM_BA     (IOP321_PCI_LOWER_MEM_BA + IOP321_PCI_MEM_WINDOW_SIZE - 1)
DECL|macro|IOP321_PCI_MEM_OFFSET
mdefine_line|#define IOP321_PCI_MEM_OFFSET       (IOP321_PCI_LOWER_MEM_VA - IOP321_PCI_LOWER_MEM_BA)
multiline_comment|/*&n; * IOP321 chipset registers&n; */
DECL|macro|IOP321_VIRT_MEM_BASE
mdefine_line|#define IOP321_VIRT_MEM_BASE 0xfeffe000  /* chip virtual mem address*/
DECL|macro|IOP321_PHYS_MEM_BASE
mdefine_line|#define IOP321_PHYS_MEM_BASE 0xffffe000  /* chip physical memory address */
DECL|macro|IOP321_REG_ADDR
mdefine_line|#define IOP321_REG_ADDR(reg) (IOP321_VIRT_MEM_BASE | (reg))
multiline_comment|/* Reserved 0x00000000 through 0x000000FF */
multiline_comment|/* Address Translation Unit 0x00000100 through 0x000001FF */
DECL|macro|IOP321_ATUVID
mdefine_line|#define IOP321_ATUVID     (volatile u16 *)IOP321_REG_ADDR(0x00000100)
DECL|macro|IOP321_ATUDID
mdefine_line|#define IOP321_ATUDID     (volatile u16 *)IOP321_REG_ADDR(0x00000102)
DECL|macro|IOP321_ATUCMD
mdefine_line|#define IOP321_ATUCMD     (volatile u16 *)IOP321_REG_ADDR(0x00000104)
DECL|macro|IOP321_ATUSR
mdefine_line|#define IOP321_ATUSR      (volatile u16 *)IOP321_REG_ADDR(0x00000106)
DECL|macro|IOP321_ATURID
mdefine_line|#define IOP321_ATURID     (volatile u8  *)IOP321_REG_ADDR(0x00000108)
DECL|macro|IOP321_ATUCCR
mdefine_line|#define IOP321_ATUCCR     (volatile u32 *)IOP321_REG_ADDR(0x00000109)
DECL|macro|IOP321_ATUCLSR
mdefine_line|#define IOP321_ATUCLSR    (volatile u8  *)IOP321_REG_ADDR(0x0000010C)
DECL|macro|IOP321_ATULT
mdefine_line|#define IOP321_ATULT      (volatile u8  *)IOP321_REG_ADDR(0x0000010D)
DECL|macro|IOP321_ATUHTR
mdefine_line|#define IOP321_ATUHTR     (volatile u8  *)IOP321_REG_ADDR(0x0000010E)
DECL|macro|IOP321_ATUBIST
mdefine_line|#define IOP321_ATUBIST    (volatile u8  *)IOP321_REG_ADDR(0x0000010F)
DECL|macro|IOP321_IABAR0
mdefine_line|#define IOP321_IABAR0     (volatile u32 *)IOP321_REG_ADDR(0x00000110)
DECL|macro|IOP321_IAUBAR0
mdefine_line|#define IOP321_IAUBAR0    (volatile u32 *)IOP321_REG_ADDR(0x00000114)
DECL|macro|IOP321_IABAR1
mdefine_line|#define IOP321_IABAR1     (volatile u32 *)IOP321_REG_ADDR(0x00000118)
DECL|macro|IOP321_IAUBAR1
mdefine_line|#define IOP321_IAUBAR1    (volatile u32 *)IOP321_REG_ADDR(0x0000011C)
DECL|macro|IOP321_IABAR2
mdefine_line|#define IOP321_IABAR2     (volatile u32 *)IOP321_REG_ADDR(0x00000120)
DECL|macro|IOP321_IAUBAR2
mdefine_line|#define IOP321_IAUBAR2    (volatile u32 *)IOP321_REG_ADDR(0x00000124)
DECL|macro|IOP321_ASVIR
mdefine_line|#define IOP321_ASVIR      (volatile u16 *)IOP321_REG_ADDR(0x0000012C)
DECL|macro|IOP321_ASIR
mdefine_line|#define IOP321_ASIR       (volatile u16 *)IOP321_REG_ADDR(0x0000012E)
DECL|macro|IOP321_ERBAR
mdefine_line|#define IOP321_ERBAR      (volatile u32 *)IOP321_REG_ADDR(0x00000130)
multiline_comment|/* Reserved 0x00000134 through 0x0000013B */
DECL|macro|IOP321_ATUILR
mdefine_line|#define IOP321_ATUILR     (volatile u8  *)IOP321_REG_ADDR(0x0000013C)
DECL|macro|IOP321_ATUIPR
mdefine_line|#define IOP321_ATUIPR     (volatile u8  *)IOP321_REG_ADDR(0x0000013D)
DECL|macro|IOP321_ATUMGNT
mdefine_line|#define IOP321_ATUMGNT    (volatile u8  *)IOP321_REG_ADDR(0x0000013E)
DECL|macro|IOP321_ATUMLAT
mdefine_line|#define IOP321_ATUMLAT    (volatile u8  *)IOP321_REG_ADDR(0x0000013F)
DECL|macro|IOP321_IALR0
mdefine_line|#define IOP321_IALR0      (volatile u32 *)IOP321_REG_ADDR(0x00000140)
DECL|macro|IOP321_IATVR0
mdefine_line|#define IOP321_IATVR0     (volatile u32 *)IOP321_REG_ADDR(0x00000144)
DECL|macro|IOP321_ERLR
mdefine_line|#define IOP321_ERLR       (volatile u32 *)IOP321_REG_ADDR(0x00000148)
DECL|macro|IOP321_ERTVR
mdefine_line|#define IOP321_ERTVR      (volatile u32 *)IOP321_REG_ADDR(0x0000014C)
DECL|macro|IOP321_IALR1
mdefine_line|#define IOP321_IALR1      (volatile u32 *)IOP321_REG_ADDR(0x00000150)
DECL|macro|IOP321_IALR2
mdefine_line|#define IOP321_IALR2      (volatile u32 *)IOP321_REG_ADDR(0x00000154)
DECL|macro|IOP321_IATVR2
mdefine_line|#define IOP321_IATVR2     (volatile u32 *)IOP321_REG_ADDR(0x00000158)
DECL|macro|IOP321_OIOWTVR
mdefine_line|#define IOP321_OIOWTVR    (volatile u32 *)IOP321_REG_ADDR(0x0000015C)
DECL|macro|IOP321_OMWTVR0
mdefine_line|#define IOP321_OMWTVR0    (volatile u32 *)IOP321_REG_ADDR(0x00000160)
DECL|macro|IOP321_OUMWTVR0
mdefine_line|#define IOP321_OUMWTVR0   (volatile u32 *)IOP321_REG_ADDR(0x00000164)
DECL|macro|IOP321_OMWTVR1
mdefine_line|#define IOP321_OMWTVR1    (volatile u32 *)IOP321_REG_ADDR(0x00000168)
DECL|macro|IOP321_OUMWTVR1
mdefine_line|#define IOP321_OUMWTVR1   (volatile u32 *)IOP321_REG_ADDR(0x0000016C)
multiline_comment|/* Reserved 0x00000170 through 0x00000177*/
DECL|macro|IOP321_OUDWTVR
mdefine_line|#define IOP321_OUDWTVR    (volatile u32 *)IOP321_REG_ADDR(0x00000178)
multiline_comment|/* Reserved 0x0000017C through 0x0000017F*/
DECL|macro|IOP321_ATUCR
mdefine_line|#define IOP321_ATUCR      (volatile u32 *)IOP321_REG_ADDR(0x00000180)
DECL|macro|IOP321_PCSR
mdefine_line|#define IOP321_PCSR       (volatile u32 *)IOP321_REG_ADDR(0x00000184)
DECL|macro|IOP321_ATUISR
mdefine_line|#define IOP321_ATUISR     (volatile u32 *)IOP321_REG_ADDR(0x00000188)
DECL|macro|IOP321_ATUIMR
mdefine_line|#define IOP321_ATUIMR     (volatile u32 *)IOP321_REG_ADDR(0x0000018C)
DECL|macro|IOP321_IABAR3
mdefine_line|#define IOP321_IABAR3     (volatile u32 *)IOP321_REG_ADDR(0x00000190)
DECL|macro|IOP321_IAUBAR3
mdefine_line|#define IOP321_IAUBAR3    (volatile u32 *)IOP321_REG_ADDR(0x00000194)
DECL|macro|IOP321_IALR3
mdefine_line|#define IOP321_IALR3      (volatile u32 *)IOP321_REG_ADDR(0x00000198)
DECL|macro|IOP321_IATVR3
mdefine_line|#define IOP321_IATVR3     (volatile u32 *)IOP321_REG_ADDR(0x0000019C)
multiline_comment|/* Reserved 0x000001A0 through 0x000001A3*/
DECL|macro|IOP321_OCCAR
mdefine_line|#define IOP321_OCCAR      (volatile u32 *)IOP321_REG_ADDR(0x000001A4)
multiline_comment|/* Reserved 0x000001A8 through 0x000001AB*/
DECL|macro|IOP321_OCCDR
mdefine_line|#define IOP321_OCCDR      (volatile u32 *)IOP321_REG_ADDR(0x000001AC)
multiline_comment|/* Reserved 0x000001B0 through 0x000001BB*/
DECL|macro|IOP321_PDSCR
mdefine_line|#define IOP321_PDSCR      (volatile u32 *)IOP321_REG_ADDR(0x000001BC)
DECL|macro|IOP321_PMCAPID
mdefine_line|#define IOP321_PMCAPID    (volatile u8  *)IOP321_REG_ADDR(0x000001C0)
DECL|macro|IOP321_PMNEXT
mdefine_line|#define IOP321_PMNEXT     (volatile u8  *)IOP321_REG_ADDR(0x000001C1)
DECL|macro|IOP321_APMCR
mdefine_line|#define IOP321_APMCR      (volatile u16 *)IOP321_REG_ADDR(0x000001C2)
DECL|macro|IOP321_APMCSR
mdefine_line|#define IOP321_APMCSR     (volatile u16 *)IOP321_REG_ADDR(0x000001C4)
multiline_comment|/* Reserved 0x000001C6 through 0x000001DF */
DECL|macro|IOP321_PCIXCAPID
mdefine_line|#define IOP321_PCIXCAPID  (volatile u8  *)IOP321_REG_ADDR(0x000001E0)
DECL|macro|IOP321_PCIXNEXT
mdefine_line|#define IOP321_PCIXNEXT   (volatile u8  *)IOP321_REG_ADDR(0x000001E1)
DECL|macro|IOP321_PCIXCMD
mdefine_line|#define IOP321_PCIXCMD    (volatile u16 *)IOP321_REG_ADDR(0x000001E2)
DECL|macro|IOP321_PCIXSR
mdefine_line|#define IOP321_PCIXSR     (volatile u32 *)IOP321_REG_ADDR(0x000001E4)
DECL|macro|IOP321_PCIIRSR
mdefine_line|#define IOP321_PCIIRSR    (volatile u32 *)IOP321_REG_ADDR(0x000001EC)
multiline_comment|/* Messaging Unit 0x00000300 through 0x000003FF */
multiline_comment|/* Reserved 0x00000300 through 0x0000030c */
DECL|macro|IOP321_IMR0
mdefine_line|#define IOP321_IMR0       (volatile u32 *)IOP321_REG_ADDR(0x00000310)
DECL|macro|IOP321_IMR1
mdefine_line|#define IOP321_IMR1       (volatile u32 *)IOP321_REG_ADDR(0x00000314)
DECL|macro|IOP321_OMR0
mdefine_line|#define IOP321_OMR0       (volatile u32 *)IOP321_REG_ADDR(0x00000318)
DECL|macro|IOP321_OMR1
mdefine_line|#define IOP321_OMR1       (volatile u32 *)IOP321_REG_ADDR(0x0000031C)
DECL|macro|IOP321_IDR
mdefine_line|#define IOP321_IDR        (volatile u32 *)IOP321_REG_ADDR(0x00000320)
DECL|macro|IOP321_IISR
mdefine_line|#define IOP321_IISR       (volatile u32 *)IOP321_REG_ADDR(0x00000324)
DECL|macro|IOP321_IIMR
mdefine_line|#define IOP321_IIMR       (volatile u32 *)IOP321_REG_ADDR(0x00000328)
DECL|macro|IOP321_ODR
mdefine_line|#define IOP321_ODR        (volatile u32 *)IOP321_REG_ADDR(0x0000032C)
DECL|macro|IOP321_OISR
mdefine_line|#define IOP321_OISR       (volatile u32 *)IOP321_REG_ADDR(0x00000330)
DECL|macro|IOP321_OIMR
mdefine_line|#define IOP321_OIMR       (volatile u32 *)IOP321_REG_ADDR(0x00000334)
multiline_comment|/* Reserved 0x00000338 through 0x0000034F */
DECL|macro|IOP321_MUCR
mdefine_line|#define IOP321_MUCR       (volatile u32 *)IOP321_REG_ADDR(0x00000350)
DECL|macro|IOP321_QBAR
mdefine_line|#define IOP321_QBAR       (volatile u32 *)IOP321_REG_ADDR(0x00000354)
multiline_comment|/* Reserved 0x00000358 through 0x0000035C */
DECL|macro|IOP321_IFHPR
mdefine_line|#define IOP321_IFHPR      (volatile u32 *)IOP321_REG_ADDR(0x00000360)
DECL|macro|IOP321_IFTPR
mdefine_line|#define IOP321_IFTPR      (volatile u32 *)IOP321_REG_ADDR(0x00000364)
DECL|macro|IOP321_IPHPR
mdefine_line|#define IOP321_IPHPR      (volatile u32 *)IOP321_REG_ADDR(0x00000368)
DECL|macro|IOP321_IPTPR
mdefine_line|#define IOP321_IPTPR      (volatile u32 *)IOP321_REG_ADDR(0x0000036C)
DECL|macro|IOP321_OFHPR
mdefine_line|#define IOP321_OFHPR      (volatile u32 *)IOP321_REG_ADDR(0x00000370)
DECL|macro|IOP321_OFTPR
mdefine_line|#define IOP321_OFTPR      (volatile u32 *)IOP321_REG_ADDR(0x00000374)
DECL|macro|IOP321_OPHPR
mdefine_line|#define IOP321_OPHPR      (volatile u32 *)IOP321_REG_ADDR(0x00000378)
DECL|macro|IOP321_OPTPR
mdefine_line|#define IOP321_OPTPR      (volatile u32 *)IOP321_REG_ADDR(0x0000037C)
DECL|macro|IOP321_IAR
mdefine_line|#define IOP321_IAR        (volatile u32 *)IOP321_REG_ADDR(0x00000380)
DECL|macro|IOP321_IIxR_MASK
mdefine_line|#define IOP321_IIxR_MASK&t;0x7f /* masks all */
DECL|macro|IOP321_IIxR_IRI
mdefine_line|#define IOP321_IIxR_IRI&t;&t;0x40 /* RC Index Register Interrupt */
DECL|macro|IOP321_IIxR_OFQF
mdefine_line|#define IOP321_IIxR_OFQF&t;0x20 /* RC Output Free Q Full (ERROR) */
DECL|macro|IOP321_IIxR_ipq
mdefine_line|#define IOP321_IIxR_ipq&t;&t;0x10 /* RC Inbound Post Q (post) */
DECL|macro|IOP321_IIxR_ERRDI
mdefine_line|#define IOP321_IIxR_ERRDI&t;0x08 /* RO Error Doorbell Interrupt */
DECL|macro|IOP321_IIxR_IDI
mdefine_line|#define IOP321_IIxR_IDI&t;&t;0x04 /* RO Inbound Doorbell Interrupt */
DECL|macro|IOP321_IIxR_IM1
mdefine_line|#define IOP321_IIxR_IM1&t;&t;0x02 /* RC Inbound Message 1 Interrupt */
DECL|macro|IOP321_IIxR_IM0
mdefine_line|#define IOP321_IIxR_IM0&t;&t;0x01 /* RC Inbound Message 0 Interrupt */
multiline_comment|/* Reserved 0x00000384 through 0x000003FF */
multiline_comment|/* DMA Controller 0x00000400 through 0x000004FF */
DECL|macro|IOP321_DMA0_CCR
mdefine_line|#define IOP321_DMA0_CCR   (volatile u32 *)IOP321_REG_ADDR(0x00000400)
DECL|macro|IOP321_DMA0_CSR
mdefine_line|#define IOP321_DMA0_CSR   (volatile u32 *)IOP321_REG_ADDR(0x00000404)
DECL|macro|IOP321_DMA0_DAR
mdefine_line|#define IOP321_DMA0_DAR   (volatile u32 *)IOP321_REG_ADDR(0x0000040C)
DECL|macro|IOP321_DMA0_NDAR
mdefine_line|#define IOP321_DMA0_NDAR  (volatile u32 *)IOP321_REG_ADDR(0x00000410)
DECL|macro|IOP321_DMA0_PADR
mdefine_line|#define IOP321_DMA0_PADR  (volatile u32 *)IOP321_REG_ADDR(0x00000414)
DECL|macro|IOP321_DMA0_PUADR
mdefine_line|#define IOP321_DMA0_PUADR (volatile u32 *)IOP321_REG_ADDR(0x00000418)
DECL|macro|IOP321_DMA0_LADR
mdefine_line|#define IOP321_DMA0_LADR  (volatile u32 *)IOP321_REG_ADDR(0X0000041C)
DECL|macro|IOP321_DMA0_BCR
mdefine_line|#define IOP321_DMA0_BCR   (volatile u32 *)IOP321_REG_ADDR(0x00000420)
DECL|macro|IOP321_DMA0_DCR
mdefine_line|#define IOP321_DMA0_DCR   (volatile u32 *)IOP321_REG_ADDR(0x00000424)
multiline_comment|/* Reserved 0x00000428 through 0x0000043C */
DECL|macro|IOP321_DMA1_CCR
mdefine_line|#define IOP321_DMA1_CCR   (volatile u32 *)IOP321_REG_ADDR(0x00000440)
DECL|macro|IOP321_DMA1_CSR
mdefine_line|#define IOP321_DMA1_CSR   (volatile u32 *)IOP321_REG_ADDR(0x00000444)
DECL|macro|IOP321_DMA1_DAR
mdefine_line|#define IOP321_DMA1_DAR   (volatile u32 *)IOP321_REG_ADDR(0x0000044C)
DECL|macro|IOP321_DMA1_NDAR
mdefine_line|#define IOP321_DMA1_NDAR  (volatile u32 *)IOP321_REG_ADDR(0x00000450)
DECL|macro|IOP321_DMA1_PADR
mdefine_line|#define IOP321_DMA1_PADR  (volatile u32 *)IOP321_REG_ADDR(0x00000454)
DECL|macro|IOP321_DMA1_PUADR
mdefine_line|#define IOP321_DMA1_PUADR (volatile u32 *)IOP321_REG_ADDR(0x00000458)
DECL|macro|IOP321_DMA1_LADR
mdefine_line|#define IOP321_DMA1_LADR  (volatile u32 *)IOP321_REG_ADDR(0x0000045C)
DECL|macro|IOP321_DMA1_BCR
mdefine_line|#define IOP321_DMA1_BCR   (volatile u32 *)IOP321_REG_ADDR(0x00000460)
DECL|macro|IOP321_DMA1_DCR
mdefine_line|#define IOP321_DMA1_DCR   (volatile u32 *)IOP321_REG_ADDR(0x00000464)
multiline_comment|/* Reserved 0x00000468 through 0x000004FF */
multiline_comment|/* Memory controller 0x00000500 through 0x0005FF */
multiline_comment|/* Peripheral bus interface unit 0x00000680 through 0x0006FF */
DECL|macro|IOP321_PBCR
mdefine_line|#define IOP321_PBCR       (volatile u32 *)IOP321_REG_ADDR(0x00000680)
DECL|macro|IOP321_PBISR
mdefine_line|#define IOP321_PBISR      (volatile u32 *)IOP321_REG_ADDR(0x00000684)
DECL|macro|IOP321_PBBAR0
mdefine_line|#define IOP321_PBBAR0     (volatile u32 *)IOP321_REG_ADDR(0x00000688)
DECL|macro|IOP321_PBLR0
mdefine_line|#define IOP321_PBLR0      (volatile u32 *)IOP321_REG_ADDR(0x0000068C)
DECL|macro|IOP321_PBBAR1
mdefine_line|#define IOP321_PBBAR1     (volatile u32 *)IOP321_REG_ADDR(0x00000690)
DECL|macro|IOP321_PBLR1
mdefine_line|#define IOP321_PBLR1      (volatile u32 *)IOP321_REG_ADDR(0x00000694)
DECL|macro|IOP321_PBBAR2
mdefine_line|#define IOP321_PBBAR2     (volatile u32 *)IOP321_REG_ADDR(0x00000698)
DECL|macro|IOP321_PBLR2
mdefine_line|#define IOP321_PBLR2      (volatile u32 *)IOP321_REG_ADDR(0x0000069C)
DECL|macro|IOP321_PBBAR3
mdefine_line|#define IOP321_PBBAR3     (volatile u32 *)IOP321_REG_ADDR(0x000006A0)
DECL|macro|IOP321_PBLR3
mdefine_line|#define IOP321_PBLR3      (volatile u32 *)IOP321_REG_ADDR(0x000006A4)
DECL|macro|IOP321_PBBAR4
mdefine_line|#define IOP321_PBBAR4     (volatile u32 *)IOP321_REG_ADDR(0x000006A8)
DECL|macro|IOP321_PBLR4
mdefine_line|#define IOP321_PBLR4      (volatile u32 *)IOP321_REG_ADDR(0x000006AC)
DECL|macro|IOP321_PBBAR5
mdefine_line|#define IOP321_PBBAR5     (volatile u32 *)IOP321_REG_ADDR(0x000006B0)
DECL|macro|IOP321_PBLR5
mdefine_line|#define IOP321_PBLR5      (volatile u32 *)IOP321_REG_ADDR(0x000006B4)
DECL|macro|IOP321_PBDSCR
mdefine_line|#define IOP321_PBDSCR     (volatile u32 *)IOP321_REG_ADDR(0x000006B8)
multiline_comment|/* Reserved 0x000006BC */
DECL|macro|IOP321_PMBR0
mdefine_line|#define IOP321_PMBR0      (volatile u32 *)IOP321_REG_ADDR(0x000006C0)
multiline_comment|/* Reserved 0x000006C4 through 0x000006DC */
DECL|macro|IOP321_PMBR1
mdefine_line|#define IOP321_PMBR1      (volatile u32 *)IOP321_REG_ADDR(0x000006E0)
DECL|macro|IOP321_PMBR2
mdefine_line|#define IOP321_PMBR2      (volatile u32 *)IOP321_REG_ADDR(0x000006E4)
DECL|macro|IOP321_PBCR_EN
mdefine_line|#define IOP321_PBCR_EN    0x1
DECL|macro|IOP321_PBISR_BOOR_ERR
mdefine_line|#define IOP321_PBISR_BOOR_ERR 0x1
multiline_comment|/* Peripheral performance monitoring unit 0x00000700 through 0x00077F */
DECL|macro|IOP321_GTMR
mdefine_line|#define IOP321_GTMR&t;(volatile u32 *)IOP321_REG_ADDR(0x00000700)
DECL|macro|IOP321_ESR
mdefine_line|#define IOP321_ESR&t;(volatile u32 *)IOP321_REG_ADDR(0x00000704)
DECL|macro|IOP321_EMISR
mdefine_line|#define IOP321_EMISR&t;(volatile u32 *)IOP321_REG_ADDR(0x00000708)
multiline_comment|/* reserved 0x00000070c */
DECL|macro|IOP321_GTSR
mdefine_line|#define IOP321_GTSR&t;(volatile u32 *)IOP321_REG_ADDR(0x00000710)
multiline_comment|/* PERC0 DOESN&squot;T EXIST - index from 1! */
DECL|macro|IOP321_PERCR0
mdefine_line|#define IOP321_PERCR0&t;(volatile u32 *)IOP321_REG_ADDR(0x00000710)
DECL|macro|IOP321_GTMR_NGCE
mdefine_line|#define IOP321_GTMR_NGCE&t;0x04 /* (Not) Global Counter Enable */
multiline_comment|/* Internal arbitration unit 0x00000780 through 0x0007BF */
DECL|macro|IOP321_IACR
mdefine_line|#define IOP321_IACR&t;(volatile u32 *)IOP321_REG_ADDR(0x00000780)
DECL|macro|IOP321_MTTR1
mdefine_line|#define IOP321_MTTR1&t;(volatile u32 *)IOP321_REG_ADDR(0x00000784)
DECL|macro|IOP321_MTTR2
mdefine_line|#define IOP321_MTTR2&t;(volatile u32 *)IOP321_REG_ADDR(0x00000788)
multiline_comment|/* General Purpose I/O Registers */
DECL|macro|IOP321_GPOE
mdefine_line|#define IOP321_GPOE       (volatile u32 *)IOP321_REG_ADDR(0x000007C4)
DECL|macro|IOP321_GPID
mdefine_line|#define IOP321_GPID       (volatile u32 *)IOP321_REG_ADDR(0x000007C8)
DECL|macro|IOP321_GPOD
mdefine_line|#define IOP321_GPOD       (volatile u32 *)IOP321_REG_ADDR(0x000007CC)
multiline_comment|/* Interrupt Controller */
DECL|macro|IOP321_INTCTL
mdefine_line|#define IOP321_INTCTL     (volatile u32 *)IOP321_REG_ADDR(0x000007D0)
DECL|macro|IOP321_INTSTR
mdefine_line|#define IOP321_INTSTR     (volatile u32 *)IOP321_REG_ADDR(0x000007D4)
DECL|macro|IOP321_IINTSRC
mdefine_line|#define IOP321_IINTSRC    (volatile u32 *)IOP321_REG_ADDR(0x000007D8)
DECL|macro|IOP321_FINTSRC
mdefine_line|#define IOP321_FINTSRC    (volatile u32 *)IOP321_REG_ADDR(0x000007DC)
multiline_comment|/* Timers */
DECL|macro|IOP321_TU_TMR0
mdefine_line|#define IOP321_TU_TMR0&t;&t;(volatile u32 *)IOP321_REG_ADDR(0x000007E0)
DECL|macro|IOP321_TU_TMR1
mdefine_line|#define IOP321_TU_TMR1&t;&t;(volatile u32 *)IOP321_REG_ADDR(0x000007E4)
macro_line|#ifdef CONFIG_ARCH_IQ80321
DECL|macro|IOP321_TICK_RATE
mdefine_line|#define&t;IOP321_TICK_RATE&t;200000000&t;/* 200 MHz clock */
macro_line|#elif defined(CONFIG_ARCH_IQ31244)
DECL|macro|IOP321_TICK_RATE
mdefine_line|#define IOP321_TICK_RATE&t;198000000&t;/* 33.000 MHz crystal */
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_EP80219
DECL|macro|IOP321_TICK_RATE
macro_line|#undef IOP321_TICK_RATE
DECL|macro|IOP321_TICK_RATE
mdefine_line|#define IOP321_TICK_RATE 200000000 /* 33.333333 Mhz crystal */
macro_line|#endif
DECL|macro|IOP321_TMR_TC
mdefine_line|#define IOP321_TMR_TC&t;&t;0x01
DECL|macro|IOP321_TMR_EN
mdefine_line|#define&t;IOP321_TMR_EN&t;&t;0x02
DECL|macro|IOP321_TMR_RELOAD
mdefine_line|#define IOP321_TMR_RELOAD&t;0x04
DECL|macro|IOP321_TMR_PRIVILEGED
mdefine_line|#define&t;IOP321_TMR_PRIVILEGED&t;0x09
DECL|macro|IOP321_TMR_RATIO_1_1
mdefine_line|#define&t;IOP321_TMR_RATIO_1_1&t;0x00
DECL|macro|IOP321_TMR_RATIO_4_1
mdefine_line|#define&t;IOP321_TMR_RATIO_4_1&t;0x10
DECL|macro|IOP321_TMR_RATIO_8_1
mdefine_line|#define&t;IOP321_TMR_RATIO_8_1&t;0x20
DECL|macro|IOP321_TMR_RATIO_16_1
mdefine_line|#define&t;IOP321_TMR_RATIO_16_1&t;0x30
DECL|macro|IOP321_TU_TCR0
mdefine_line|#define IOP321_TU_TCR0    (volatile u32 *)IOP321_REG_ADDR(0x000007E8)
DECL|macro|IOP321_TU_TCR1
mdefine_line|#define IOP321_TU_TCR1    (volatile u32 *)IOP321_REG_ADDR(0x000007EC)
DECL|macro|IOP321_TU_TRR0
mdefine_line|#define IOP321_TU_TRR0    (volatile u32 *)IOP321_REG_ADDR(0x000007F0)
DECL|macro|IOP321_TU_TRR1
mdefine_line|#define IOP321_TU_TRR1    (volatile u32 *)IOP321_REG_ADDR(0x000007F4)
DECL|macro|IOP321_TU_TISR
mdefine_line|#define IOP321_TU_TISR    (volatile u32 *)IOP321_REG_ADDR(0x000007F8)
DECL|macro|IOP321_TU_WDTCR
mdefine_line|#define IOP321_TU_WDTCR   (volatile u32 *)IOP321_REG_ADDR(0x000007FC)
multiline_comment|/* Application accelerator unit 0x00000800 - 0x000008FF */
DECL|macro|IOP321_AAU_ACR
mdefine_line|#define IOP321_AAU_ACR     (volatile u32 *)IOP321_REG_ADDR(0x00000800)
DECL|macro|IOP321_AAU_ASR
mdefine_line|#define IOP321_AAU_ASR     (volatile u32 *)IOP321_REG_ADDR(0x00000804)
DECL|macro|IOP321_AAU_ADAR
mdefine_line|#define IOP321_AAU_ADAR    (volatile u32 *)IOP321_REG_ADDR(0x00000808)
DECL|macro|IOP321_AAU_ANDAR
mdefine_line|#define IOP321_AAU_ANDAR   (volatile u32 *)IOP321_REG_ADDR(0x0000080C)
DECL|macro|IOP321_AAU_SAR1
mdefine_line|#define IOP321_AAU_SAR1    (volatile u32 *)IOP321_REG_ADDR(0x00000810)
DECL|macro|IOP321_AAU_SAR2
mdefine_line|#define IOP321_AAU_SAR2    (volatile u32 *)IOP321_REG_ADDR(0x00000814)
DECL|macro|IOP321_AAU_SAR3
mdefine_line|#define IOP321_AAU_SAR3    (volatile u32 *)IOP321_REG_ADDR(0x00000818)
DECL|macro|IOP321_AAU_SAR4
mdefine_line|#define IOP321_AAU_SAR4    (volatile u32 *)IOP321_REG_ADDR(0x0000081C)
DECL|macro|IOP321_AAU_SAR5
mdefine_line|#define IOP321_AAU_SAR5    (volatile u32 *)IOP321_REG_ADDR(0x0000082C)
DECL|macro|IOP321_AAU_SAR6
mdefine_line|#define IOP321_AAU_SAR6    (volatile u32 *)IOP321_REG_ADDR(0x00000830)
DECL|macro|IOP321_AAU_SAR7
mdefine_line|#define IOP321_AAU_SAR7    (volatile u32 *)IOP321_REG_ADDR(0x00000834)
DECL|macro|IOP321_AAU_SAR8
mdefine_line|#define IOP321_AAU_SAR8    (volatile u32 *)IOP321_REG_ADDR(0x00000838)
DECL|macro|IOP321_AAU_SAR9
mdefine_line|#define IOP321_AAU_SAR9    (volatile u32 *)IOP321_REG_ADDR(0x00000840)
DECL|macro|IOP321_AAU_SAR10
mdefine_line|#define IOP321_AAU_SAR10   (volatile u32 *)IOP321_REG_ADDR(0x00000844)
DECL|macro|IOP321_AAU_SAR11
mdefine_line|#define IOP321_AAU_SAR11   (volatile u32 *)IOP321_REG_ADDR(0x00000848)
DECL|macro|IOP321_AAU_SAR12
mdefine_line|#define IOP321_AAU_SAR12   (volatile u32 *)IOP321_REG_ADDR(0x0000084C)
DECL|macro|IOP321_AAU_SAR13
mdefine_line|#define IOP321_AAU_SAR13   (volatile u32 *)IOP321_REG_ADDR(0x00000850)
DECL|macro|IOP321_AAU_SAR14
mdefine_line|#define IOP321_AAU_SAR14   (volatile u32 *)IOP321_REG_ADDR(0x00000854)
DECL|macro|IOP321_AAU_SAR15
mdefine_line|#define IOP321_AAU_SAR15   (volatile u32 *)IOP321_REG_ADDR(0x00000858)
DECL|macro|IOP321_AAU_SAR16
mdefine_line|#define IOP321_AAU_SAR16   (volatile u32 *)IOP321_REG_ADDR(0x0000085C)
DECL|macro|IOP321_AAU_SAR17
mdefine_line|#define IOP321_AAU_SAR17   (volatile u32 *)IOP321_REG_ADDR(0x00000864)
DECL|macro|IOP321_AAU_SAR18
mdefine_line|#define IOP321_AAU_SAR18   (volatile u32 *)IOP321_REG_ADDR(0x00000868)
DECL|macro|IOP321_AAU_SAR19
mdefine_line|#define IOP321_AAU_SAR19   (volatile u32 *)IOP321_REG_ADDR(0x0000086C)
DECL|macro|IOP321_AAU_SAR20
mdefine_line|#define IOP321_AAU_SAR20   (volatile u32 *)IOP321_REG_ADDR(0x00000870)
DECL|macro|IOP321_AAU_SAR21
mdefine_line|#define IOP321_AAU_SAR21   (volatile u32 *)IOP321_REG_ADDR(0x00000874)
DECL|macro|IOP321_AAU_SAR22
mdefine_line|#define IOP321_AAU_SAR22   (volatile u32 *)IOP321_REG_ADDR(0x00000878)
DECL|macro|IOP321_AAU_SAR23
mdefine_line|#define IOP321_AAU_SAR23   (volatile u32 *)IOP321_REG_ADDR(0x0000087C)
DECL|macro|IOP321_AAU_SAR24
mdefine_line|#define IOP321_AAU_SAR24   (volatile u32 *)IOP321_REG_ADDR(0x00000880)
DECL|macro|IOP321_AAU_SAR25
mdefine_line|#define IOP321_AAU_SAR25   (volatile u32 *)IOP321_REG_ADDR(0x00000888)
DECL|macro|IOP321_AAU_SAR26
mdefine_line|#define IOP321_AAU_SAR26   (volatile u32 *)IOP321_REG_ADDR(0x0000088C)
DECL|macro|IOP321_AAU_SAR27
mdefine_line|#define IOP321_AAU_SAR27   (volatile u32 *)IOP321_REG_ADDR(0x00000890)
DECL|macro|IOP321_AAU_SAR28
mdefine_line|#define IOP321_AAU_SAR28   (volatile u32 *)IOP321_REG_ADDR(0x00000894)
DECL|macro|IOP321_AAU_SAR29
mdefine_line|#define IOP321_AAU_SAR29   (volatile u32 *)IOP321_REG_ADDR(0x00000898)
DECL|macro|IOP321_AAU_SAR30
mdefine_line|#define IOP321_AAU_SAR30   (volatile u32 *)IOP321_REG_ADDR(0x0000089C)
DECL|macro|IOP321_AAU_SAR31
mdefine_line|#define IOP321_AAU_SAR31   (volatile u32 *)IOP321_REG_ADDR(0x000008A0)
DECL|macro|IOP321_AAU_SAR32
mdefine_line|#define IOP321_AAU_SAR32   (volatile u32 *)IOP321_REG_ADDR(0x000008A4)
DECL|macro|IOP321_AAU_DAR
mdefine_line|#define IOP321_AAU_DAR     (volatile u32 *)IOP321_REG_ADDR(0x00000820)
DECL|macro|IOP321_AAU_ABCR
mdefine_line|#define IOP321_AAU_ABCR    (volatile u32 *)IOP321_REG_ADDR(0x00000824)
DECL|macro|IOP321_AAU_ADCR
mdefine_line|#define IOP321_AAU_ADCR    (volatile u32 *)IOP321_REG_ADDR(0x00000828)
DECL|macro|IOP321_AAU_EDCR0
mdefine_line|#define IOP321_AAU_EDCR0   (volatile u32 *)IOP321_REG_ADDR(0x0000083c)
DECL|macro|IOP321_AAU_EDCR1
mdefine_line|#define IOP321_AAU_EDCR1   (volatile u32 *)IOP321_REG_ADDR(0x00000860)
DECL|macro|IOP321_AAU_EDCR2
mdefine_line|#define IOP321_AAU_EDCR2   (volatile u32 *)IOP321_REG_ADDR(0x00000884)
multiline_comment|/* SSP serial port unit 0x00001600 - 0x0000167F */
multiline_comment|/* I2C bus interface unit 0x00001680 - 0x000016FF */
DECL|macro|IOP321_ICR0
mdefine_line|#define IOP321_ICR0       (volatile u32 *)IOP321_REG_ADDR(0x00001680)
DECL|macro|IOP321_ISR0
mdefine_line|#define IOP321_ISR0       (volatile u32 *)IOP321_REG_ADDR(0x00001684)
DECL|macro|IOP321_ISAR0
mdefine_line|#define IOP321_ISAR0      (volatile u32 *)IOP321_REG_ADDR(0x00001688)
DECL|macro|IOP321_IDBR0
mdefine_line|#define IOP321_IDBR0      (volatile u32 *)IOP321_REG_ADDR(0x0000168C)
multiline_comment|/* Reserved 0x00001690 */
DECL|macro|IOP321_IBMR0
mdefine_line|#define IOP321_IBMR0      (volatile u32 *)IOP321_REG_ADDR(0x00001694)
multiline_comment|/* Reserved 0x00001698 */
multiline_comment|/* Reserved 0x0000169C */
DECL|macro|IOP321_ICR1
mdefine_line|#define IOP321_ICR1       (volatile u32 *)IOP321_REG_ADDR(0x000016A0)
DECL|macro|IOP321_ISR1
mdefine_line|#define IOP321_ISR1       (volatile u32 *)IOP321_REG_ADDR(0x000016A4)
DECL|macro|IOP321_ISAR1
mdefine_line|#define IOP321_ISAR1      (volatile u32 *)IOP321_REG_ADDR(0x000016A8)
DECL|macro|IOP321_IDBR1
mdefine_line|#define IOP321_IDBR1      (volatile u32 *)IOP321_REG_ADDR(0x000016AC)
DECL|macro|IOP321_IBMR1
mdefine_line|#define IOP321_IBMR1      (volatile u32 *)IOP321_REG_ADDR(0x000016B4)
multiline_comment|/* Reserved 0x000016B8 through 0x000016FC */
multiline_comment|/* for I2C bit defs see drivers/i2c/i2c-iop3xx.h */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|iop321_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iop321_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iop321_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif 
singleline_comment|// _IOP321_HW_H_
eof
