multiline_comment|/*&n; * linux/include/asm/arch-iop3xx/iop331.h&n; *&n; * Intel IOP331 Chip definitions&n; *&n; * Author: Dave Jiang (dave.jiang@intel.com)&n; * Copyright (C) 2003, 2004 Intel Corp.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _IOP331_HW_H_
DECL|macro|_IOP331_HW_H_
mdefine_line|#define _IOP331_HW_H_
multiline_comment|/*&n; * This is needed for mixed drivers that need to work on all&n; * IOP3xx variants but behave slightly differently on each.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef&t;CONFIG_ARCH_IOP331
multiline_comment|/*#define&t;iop_is_331()&t;((processor_id &amp; 0xffffffb0) == 0x69054090) */
DECL|macro|iop_is_331
mdefine_line|#define&t;iop_is_331()&t;((processor_id &amp; 0xffffff30) == 0x69054010)
macro_line|#else
DECL|macro|iop_is_331
mdefine_line|#define&t;iop_is_331()&t;0
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * IOP331 I/O and Mem space regions for PCI autoconfiguration&n; */
DECL|macro|IOP331_PCI_IO_WINDOW_SIZE
mdefine_line|#define IOP331_PCI_IO_WINDOW_SIZE   0x00010000
DECL|macro|IOP331_PCI_LOWER_IO_PA
mdefine_line|#define IOP331_PCI_LOWER_IO_PA      0x90000000
DECL|macro|IOP331_PCI_LOWER_IO_VA
mdefine_line|#define IOP331_PCI_LOWER_IO_VA      0xfe000000
DECL|macro|IOP331_PCI_LOWER_IO_BA
mdefine_line|#define IOP331_PCI_LOWER_IO_BA      (*IOP331_OIOWTVR)
DECL|macro|IOP331_PCI_UPPER_IO_PA
mdefine_line|#define IOP331_PCI_UPPER_IO_PA      (IOP331_PCI_LOWER_IO_PA + IOP331_PCI_IO_WINDOW_SIZE - 1)
DECL|macro|IOP331_PCI_UPPER_IO_VA
mdefine_line|#define IOP331_PCI_UPPER_IO_VA      (IOP331_PCI_LOWER_IO_VA + IOP331_PCI_IO_WINDOW_SIZE - 1)
DECL|macro|IOP331_PCI_UPPER_IO_BA
mdefine_line|#define IOP331_PCI_UPPER_IO_BA      (IOP331_PCI_LOWER_IO_BA + IOP331_PCI_IO_WINDOW_SIZE - 1)
DECL|macro|IOP331_PCI_IO_OFFSET
mdefine_line|#define IOP331_PCI_IO_OFFSET        (IOP331_PCI_LOWER_IO_VA - IOP331_PCI_LOWER_IO_BA)
multiline_comment|/* this can be 128M if OMWTVR1 is set */
DECL|macro|IOP331_PCI_MEM_WINDOW_SIZE
mdefine_line|#define IOP331_PCI_MEM_WINDOW_SIZE&t;0x04000000 /* 64M outbound window */
singleline_comment|//#define IOP331_PCI_MEM_WINDOW_SIZE  (~*IOP331_IALR1 + 1)
DECL|macro|IOP331_PCI_LOWER_MEM_PA
mdefine_line|#define IOP331_PCI_LOWER_MEM_PA     0x80000000
DECL|macro|IOP331_PCI_LOWER_MEM_BA
mdefine_line|#define IOP331_PCI_LOWER_MEM_BA     (*IOP331_OMWTVR0)
DECL|macro|IOP331_PCI_UPPER_MEM_PA
mdefine_line|#define IOP331_PCI_UPPER_MEM_PA     (IOP331_PCI_LOWER_MEM_PA + IOP331_PCI_MEM_WINDOW_SIZE - 1)
DECL|macro|IOP331_PCI_UPPER_MEM_BA
mdefine_line|#define IOP331_PCI_UPPER_MEM_BA     (IOP331_PCI_LOWER_MEM_BA + IOP331_PCI_MEM_WINDOW_SIZE - 1)
DECL|macro|IOP331_PCI_MEM_OFFSET
mdefine_line|#define IOP331_PCI_MEM_OFFSET       (IOP331_PCI_LOWER_MEM_PA - IOP331_PCI_LOWER_MEM_BA)
multiline_comment|/*&n; * IOP331 chipset registers&n; */
DECL|macro|IOP331_VIRT_MEM_BASE
mdefine_line|#define IOP331_VIRT_MEM_BASE  0xfeffe000  /* chip virtual mem address*/
DECL|macro|IOP331_PHYS_MEM_BASE
mdefine_line|#define IOP331_PHYS_MEM_BASE  0xffffe000  /* chip physical memory address */
DECL|macro|IOP331_REG_ADDR
mdefine_line|#define IOP331_REG_ADDR(reg) (IOP331_VIRT_MEM_BASE | (reg))
multiline_comment|/* Reserved 0x00000000 through 0x000000FF */
multiline_comment|/* Address Translation Unit 0x00000100 through 0x000001FF */
DECL|macro|IOP331_ATUVID
mdefine_line|#define IOP331_ATUVID     (volatile u16 *)IOP331_REG_ADDR(0x00000100)
DECL|macro|IOP331_ATUDID
mdefine_line|#define IOP331_ATUDID     (volatile u16 *)IOP331_REG_ADDR(0x00000102)
DECL|macro|IOP331_ATUCMD
mdefine_line|#define IOP331_ATUCMD     (volatile u16 *)IOP331_REG_ADDR(0x00000104)
DECL|macro|IOP331_ATUSR
mdefine_line|#define IOP331_ATUSR      (volatile u16 *)IOP331_REG_ADDR(0x00000106)
DECL|macro|IOP331_ATURID
mdefine_line|#define IOP331_ATURID     (volatile u8  *)IOP331_REG_ADDR(0x00000108)
DECL|macro|IOP331_ATUCCR
mdefine_line|#define IOP331_ATUCCR     (volatile u32 *)IOP331_REG_ADDR(0x00000109)
DECL|macro|IOP331_ATUCLSR
mdefine_line|#define IOP331_ATUCLSR    (volatile u8  *)IOP331_REG_ADDR(0x0000010C)
DECL|macro|IOP331_ATULT
mdefine_line|#define IOP331_ATULT      (volatile u8  *)IOP331_REG_ADDR(0x0000010D)
DECL|macro|IOP331_ATUHTR
mdefine_line|#define IOP331_ATUHTR     (volatile u8  *)IOP331_REG_ADDR(0x0000010E)
DECL|macro|IOP331_ATUBIST
mdefine_line|#define IOP331_ATUBIST    (volatile u8  *)IOP331_REG_ADDR(0x0000010F)
DECL|macro|IOP331_IABAR0
mdefine_line|#define IOP331_IABAR0     (volatile u32 *)IOP331_REG_ADDR(0x00000110)
DECL|macro|IOP331_IAUBAR0
mdefine_line|#define IOP331_IAUBAR0    (volatile u32 *)IOP331_REG_ADDR(0x00000114)
DECL|macro|IOP331_IABAR1
mdefine_line|#define IOP331_IABAR1     (volatile u32 *)IOP331_REG_ADDR(0x00000118)
DECL|macro|IOP331_IAUBAR1
mdefine_line|#define IOP331_IAUBAR1    (volatile u32 *)IOP331_REG_ADDR(0x0000011C)
DECL|macro|IOP331_IABAR2
mdefine_line|#define IOP331_IABAR2     (volatile u32 *)IOP331_REG_ADDR(0x00000120)
DECL|macro|IOP331_IAUBAR2
mdefine_line|#define IOP331_IAUBAR2    (volatile u32 *)IOP331_REG_ADDR(0x00000124)
DECL|macro|IOP331_ASVIR
mdefine_line|#define IOP331_ASVIR      (volatile u16 *)IOP331_REG_ADDR(0x0000012C)
DECL|macro|IOP331_ASIR
mdefine_line|#define IOP331_ASIR       (volatile u16 *)IOP331_REG_ADDR(0x0000012E)
DECL|macro|IOP331_ERBAR
mdefine_line|#define IOP331_ERBAR      (volatile u32 *)IOP331_REG_ADDR(0x00000130)
DECL|macro|IOP331_ATU_CAPPTR
mdefine_line|#define IOP331_ATU_CAPPTR (volatile u32 *)IOP331_REG_ADDR(0x00000134)
multiline_comment|/* Reserved 0x00000138 through 0x0000013B */
DECL|macro|IOP331_ATUILR
mdefine_line|#define IOP331_ATUILR     (volatile u8  *)IOP331_REG_ADDR(0x0000013C)
DECL|macro|IOP331_ATUIPR
mdefine_line|#define IOP331_ATUIPR     (volatile u8  *)IOP331_REG_ADDR(0x0000013D)
DECL|macro|IOP331_ATUMGNT
mdefine_line|#define IOP331_ATUMGNT    (volatile u8  *)IOP331_REG_ADDR(0x0000013E)
DECL|macro|IOP331_ATUMLAT
mdefine_line|#define IOP331_ATUMLAT    (volatile u8  *)IOP331_REG_ADDR(0x0000013F)
DECL|macro|IOP331_IALR0
mdefine_line|#define IOP331_IALR0      (volatile u32 *)IOP331_REG_ADDR(0x00000140)
DECL|macro|IOP331_IATVR0
mdefine_line|#define IOP331_IATVR0     (volatile u32 *)IOP331_REG_ADDR(0x00000144)
DECL|macro|IOP331_ERLR
mdefine_line|#define IOP331_ERLR       (volatile u32 *)IOP331_REG_ADDR(0x00000148)
DECL|macro|IOP331_ERTVR
mdefine_line|#define IOP331_ERTVR      (volatile u32 *)IOP331_REG_ADDR(0x0000014C)
DECL|macro|IOP331_IALR1
mdefine_line|#define IOP331_IALR1      (volatile u32 *)IOP331_REG_ADDR(0x00000150)
DECL|macro|IOP331_IALR2
mdefine_line|#define IOP331_IALR2      (volatile u32 *)IOP331_REG_ADDR(0x00000154)
DECL|macro|IOP331_IATVR2
mdefine_line|#define IOP331_IATVR2     (volatile u32 *)IOP331_REG_ADDR(0x00000158)
DECL|macro|IOP331_OIOWTVR
mdefine_line|#define IOP331_OIOWTVR    (volatile u32 *)IOP331_REG_ADDR(0x0000015C)
DECL|macro|IOP331_OMWTVR0
mdefine_line|#define IOP331_OMWTVR0    (volatile u32 *)IOP331_REG_ADDR(0x00000160)
DECL|macro|IOP331_OUMWTVR0
mdefine_line|#define IOP331_OUMWTVR0   (volatile u32 *)IOP331_REG_ADDR(0x00000164)
DECL|macro|IOP331_OMWTVR1
mdefine_line|#define IOP331_OMWTVR1    (volatile u32 *)IOP331_REG_ADDR(0x00000168)
DECL|macro|IOP331_OUMWTVR1
mdefine_line|#define IOP331_OUMWTVR1   (volatile u32 *)IOP331_REG_ADDR(0x0000016C)
multiline_comment|/* Reserved 0x00000170 through 0x00000177*/
DECL|macro|IOP331_OUDWTVR
mdefine_line|#define IOP331_OUDWTVR    (volatile u32 *)IOP331_REG_ADDR(0x00000178)
multiline_comment|/* Reserved 0x0000017C through 0x0000017F*/
DECL|macro|IOP331_ATUCR
mdefine_line|#define IOP331_ATUCR      (volatile u32 *)IOP331_REG_ADDR(0x00000180)
DECL|macro|IOP331_PCSR
mdefine_line|#define IOP331_PCSR       (volatile u32 *)IOP331_REG_ADDR(0x00000184)
DECL|macro|IOP331_ATUISR
mdefine_line|#define IOP331_ATUISR     (volatile u32 *)IOP331_REG_ADDR(0x00000188)
DECL|macro|IOP331_ATUIMR
mdefine_line|#define IOP331_ATUIMR     (volatile u32 *)IOP331_REG_ADDR(0x0000018C)
DECL|macro|IOP331_IABAR3
mdefine_line|#define IOP331_IABAR3     (volatile u32 *)IOP331_REG_ADDR(0x00000190)
DECL|macro|IOP331_IAUBAR3
mdefine_line|#define IOP331_IAUBAR3    (volatile u32 *)IOP331_REG_ADDR(0x00000194)
DECL|macro|IOP331_IALR3
mdefine_line|#define IOP331_IALR3      (volatile u32 *)IOP331_REG_ADDR(0x00000198)
DECL|macro|IOP331_IATVR3
mdefine_line|#define IOP331_IATVR3     (volatile u32 *)IOP331_REG_ADDR(0x0000019C)
multiline_comment|/* Reserved 0x000001A0 through 0x000001A3*/
DECL|macro|IOP331_OCCAR
mdefine_line|#define IOP331_OCCAR      (volatile u32 *)IOP331_REG_ADDR(0x000001A4)
multiline_comment|/* Reserved 0x000001A8 through 0x000001AB*/
DECL|macro|IOP331_OCCDR
mdefine_line|#define IOP331_OCCDR      (volatile u32 *)IOP331_REG_ADDR(0x000001AC)
multiline_comment|/* Reserved 0x000001B0 through 0x000001BB*/
DECL|macro|IOP331_VPDCAPID
mdefine_line|#define IOP331_VPDCAPID   (volatile u8 *)IOP331_REG_ADDR(0x000001B8)
DECL|macro|IOP331_VPDNXTP
mdefine_line|#define IOP331_VPDNXTP    (volatile u8 *)IOP331_REG_ADDR(0x000001B9)
DECL|macro|IOP331_VPDAR
mdefine_line|#define IOP331_VPDAR&t;  (volatile u16 *)IOP331_REG_ADDR(0x000001BA)
DECL|macro|IOP331_VPDDR
mdefine_line|#define IOP331_VPDDR      (volatile u32 *)IOP331_REG_ADDR(0x000001BC)
DECL|macro|IOP331_PMCAPID
mdefine_line|#define IOP331_PMCAPID    (volatile u8 *)IOP331_REG_ADDR(0x000001C0)
DECL|macro|IOP331_PMNEXT
mdefine_line|#define IOP331_PMNEXT     (volatile u8 *)IOP331_REG_ADDR(0x000001C1)
DECL|macro|IOP331_APMCR
mdefine_line|#define IOP331_APMCR      (volatile u16 *)IOP331_REG_ADDR(0x000001C2)
DECL|macro|IOP331_APMCSR
mdefine_line|#define IOP331_APMCSR     (volatile u16 *)IOP331_REG_ADDR(0x000001C4)
multiline_comment|/* Reserved 0x000001C6 through 0x000001CF */
DECL|macro|IOP331_MSICAPID
mdefine_line|#define IOP331_MSICAPID   (volatile u8 *)IOP331_REG_ADDR(0x000001D0)
DECL|macro|IOP331_MSINXTP
mdefine_line|#define IOP331_MSINXTP&t;  (volatile u8 *)IOP331_REG_ADDR(0x000001D1)
DECL|macro|IOP331_MSIMCR
mdefine_line|#define IOP331_MSIMCR     (volatile u16 *)IOP331_REG_ADDR(0x000001D2)
DECL|macro|IOP331_MSIMAR
mdefine_line|#define IOP331_MSIMAR     (volatile u32 *)IOP331_REG_ADDR(0x000001D4)
DECL|macro|IOP331_MSIMUAR
mdefine_line|#define IOP331_MSIMUAR&t;  (volatile u32 *)IOP331_REG_ADDR(0x000001D8)
DECL|macro|IOP331_MSIMDR
mdefine_line|#define IOP331_MSIMDR&t;  (volatile u32 *)IOP331_REG_ADDR(0x000001DC)
DECL|macro|IOP331_PCIXCAPID
mdefine_line|#define IOP331_PCIXCAPID  (volatile u8 *)IOP331_REG_ADDR(0x000001E0)
DECL|macro|IOP331_PCIXNEXT
mdefine_line|#define IOP331_PCIXNEXT   (volatile u8 *)IOP331_REG_ADDR(0x000001E1)
DECL|macro|IOP331_PCIXCMD
mdefine_line|#define IOP331_PCIXCMD    (volatile u16 *)IOP331_REG_ADDR(0x000001E2)
DECL|macro|IOP331_PCIXSR
mdefine_line|#define IOP331_PCIXSR     (volatile u32 *)IOP331_REG_ADDR(0x000001E4)
DECL|macro|IOP331_PCIIRSR
mdefine_line|#define IOP331_PCIIRSR    (volatile u32 *)IOP331_REG_ADDR(0x000001EC)
multiline_comment|/* Messaging Unit 0x00000300 through 0x000003FF */
multiline_comment|/* Reserved 0x00000300 through 0x0000030c */
DECL|macro|IOP331_IMR0
mdefine_line|#define IOP331_IMR0       (volatile u32 *)IOP331_REG_ADDR(0x00000310)
DECL|macro|IOP331_IMR1
mdefine_line|#define IOP331_IMR1       (volatile u32 *)IOP331_REG_ADDR(0x00000314)
DECL|macro|IOP331_OMR0
mdefine_line|#define IOP331_OMR0       (volatile u32 *)IOP331_REG_ADDR(0x00000318)
DECL|macro|IOP331_OMR1
mdefine_line|#define IOP331_OMR1       (volatile u32 *)IOP331_REG_ADDR(0x0000031C)
DECL|macro|IOP331_IDR
mdefine_line|#define IOP331_IDR        (volatile u32 *)IOP331_REG_ADDR(0x00000320)
DECL|macro|IOP331_IISR
mdefine_line|#define IOP331_IISR       (volatile u32 *)IOP331_REG_ADDR(0x00000324)
DECL|macro|IOP331_IIMR
mdefine_line|#define IOP331_IIMR       (volatile u32 *)IOP331_REG_ADDR(0x00000328)
DECL|macro|IOP331_ODR
mdefine_line|#define IOP331_ODR        (volatile u32 *)IOP331_REG_ADDR(0x0000032C)
DECL|macro|IOP331_OISR
mdefine_line|#define IOP331_OISR       (volatile u32 *)IOP331_REG_ADDR(0x00000330)
DECL|macro|IOP331_OIMR
mdefine_line|#define IOP331_OIMR       (volatile u32 *)IOP331_REG_ADDR(0x00000334)
multiline_comment|/* Reserved 0x00000338 through 0x0000034F */
DECL|macro|IOP331_MUCR
mdefine_line|#define IOP331_MUCR       (volatile u32 *)IOP331_REG_ADDR(0x00000350)
DECL|macro|IOP331_QBAR
mdefine_line|#define IOP331_QBAR       (volatile u32 *)IOP331_REG_ADDR(0x00000354)
multiline_comment|/* Reserved 0x00000358 through 0x0000035C */
DECL|macro|IOP331_IFHPR
mdefine_line|#define IOP331_IFHPR      (volatile u32 *)IOP331_REG_ADDR(0x00000360)
DECL|macro|IOP331_IFTPR
mdefine_line|#define IOP331_IFTPR      (volatile u32 *)IOP331_REG_ADDR(0x00000364)
DECL|macro|IOP331_IPHPR
mdefine_line|#define IOP331_IPHPR      (volatile u32 *)IOP331_REG_ADDR(0x00000368)
DECL|macro|IOP331_IPTPR
mdefine_line|#define IOP331_IPTPR      (volatile u32 *)IOP331_REG_ADDR(0x0000036C)
DECL|macro|IOP331_OFHPR
mdefine_line|#define IOP331_OFHPR      (volatile u32 *)IOP331_REG_ADDR(0x00000370)
DECL|macro|IOP331_OFTPR
mdefine_line|#define IOP331_OFTPR      (volatile u32 *)IOP331_REG_ADDR(0x00000374)
DECL|macro|IOP331_OPHPR
mdefine_line|#define IOP331_OPHPR      (volatile u32 *)IOP331_REG_ADDR(0x00000378)
DECL|macro|IOP331_OPTPR
mdefine_line|#define IOP331_OPTPR      (volatile u32 *)IOP331_REG_ADDR(0x0000037C)
DECL|macro|IOP331_IAR
mdefine_line|#define IOP331_IAR        (volatile u32 *)IOP331_REG_ADDR(0x00000380)
multiline_comment|/* Reserved 0x00000384 through 0x000003FF */
multiline_comment|/* DMA Controller 0x00000400 through 0x000004FF */
DECL|macro|IOP331_DMA0_CCR
mdefine_line|#define IOP331_DMA0_CCR   (volatile u32 *)IOP331_REG_ADDR(0x00000400)
DECL|macro|IOP331_DMA0_CSR
mdefine_line|#define IOP331_DMA0_CSR   (volatile u32 *)IOP331_REG_ADDR(0x00000404)
DECL|macro|IOP331_DMA0_DAR
mdefine_line|#define IOP331_DMA0_DAR   (volatile u32 *)IOP331_REG_ADDR(0x0000040C)
DECL|macro|IOP331_DMA0_NDAR
mdefine_line|#define IOP331_DMA0_NDAR  (volatile u32 *)IOP331_REG_ADDR(0x00000410)
DECL|macro|IOP331_DMA0_PADR
mdefine_line|#define IOP331_DMA0_PADR  (volatile u32 *)IOP331_REG_ADDR(0x00000414)
DECL|macro|IOP331_DMA0_PUADR
mdefine_line|#define IOP331_DMA0_PUADR (volatile u32 *)IOP331_REG_ADDR(0x00000418)
DECL|macro|IOP331_DMA0_LADR
mdefine_line|#define IOP331_DMA0_LADR  (volatile u32 *)IOP331_REG_ADDR(0X0000041C)
DECL|macro|IOP331_DMA0_BCR
mdefine_line|#define IOP331_DMA0_BCR   (volatile u32 *)IOP331_REG_ADDR(0x00000420)
DECL|macro|IOP331_DMA0_DCR
mdefine_line|#define IOP331_DMA0_DCR   (volatile u32 *)IOP331_REG_ADDR(0x00000424)
multiline_comment|/* Reserved 0x00000428 through 0x0000043C */
DECL|macro|IOP331_DMA1_CCR
mdefine_line|#define IOP331_DMA1_CCR   (volatile u32 *)IOP331_REG_ADDR(0x00000440)
DECL|macro|IOP331_DMA1_CSR
mdefine_line|#define IOP331_DMA1_CSR   (volatile u32 *)IOP331_REG_ADDR(0x00000444)
DECL|macro|IOP331_DMA1_DAR
mdefine_line|#define IOP331_DMA1_DAR   (volatile u32 *)IOP331_REG_ADDR(0x0000044C)
DECL|macro|IOP331_DMA1_NDAR
mdefine_line|#define IOP331_DMA1_NDAR  (volatile u32 *)IOP331_REG_ADDR(0x00000450)
DECL|macro|IOP331_DMA1_PADR
mdefine_line|#define IOP331_DMA1_PADR  (volatile u32 *)IOP331_REG_ADDR(0x00000454)
DECL|macro|IOP331_DMA1_PUADR
mdefine_line|#define IOP331_DMA1_PUADR (volatile u32 *)IOP331_REG_ADDR(0x00000458)
DECL|macro|IOP331_DMA1_LADR
mdefine_line|#define IOP331_DMA1_LADR  (volatile u32 *)IOP331_REG_ADDR(0x0000045C)
DECL|macro|IOP331_DMA1_BCR
mdefine_line|#define IOP331_DMA1_BCR   (volatile u32 *)IOP331_REG_ADDR(0x00000460)
DECL|macro|IOP331_DMA1_DCR
mdefine_line|#define IOP331_DMA1_DCR   (volatile u32 *)IOP331_REG_ADDR(0x00000464)
multiline_comment|/* Reserved 0x00000468 through 0x000004FF */
multiline_comment|/* Memory controller 0x00000500 through 0x0005FF */
multiline_comment|/* Peripheral bus interface unit 0x00000680 through 0x0006FF */
DECL|macro|IOP331_PBCR
mdefine_line|#define IOP331_PBCR       (volatile u32 *)IOP331_REG_ADDR(0x00000680)
DECL|macro|IOP331_PBISR
mdefine_line|#define IOP331_PBISR      (volatile u32 *)IOP331_REG_ADDR(0x00000684)
DECL|macro|IOP331_PBBAR0
mdefine_line|#define IOP331_PBBAR0     (volatile u32 *)IOP331_REG_ADDR(0x00000688)
DECL|macro|IOP331_PBLR0
mdefine_line|#define IOP331_PBLR0      (volatile u32 *)IOP331_REG_ADDR(0x0000068C)
DECL|macro|IOP331_PBBAR1
mdefine_line|#define IOP331_PBBAR1     (volatile u32 *)IOP331_REG_ADDR(0x00000690)
DECL|macro|IOP331_PBLR1
mdefine_line|#define IOP331_PBLR1      (volatile u32 *)IOP331_REG_ADDR(0x00000694)
DECL|macro|IOP331_PBBAR2
mdefine_line|#define IOP331_PBBAR2     (volatile u32 *)IOP331_REG_ADDR(0x00000698)
DECL|macro|IOP331_PBLR2
mdefine_line|#define IOP331_PBLR2      (volatile u32 *)IOP331_REG_ADDR(0x0000069C)
DECL|macro|IOP331_PBBAR3
mdefine_line|#define IOP331_PBBAR3     (volatile u32 *)IOP331_REG_ADDR(0x000006A0)
DECL|macro|IOP331_PBLR3
mdefine_line|#define IOP331_PBLR3      (volatile u32 *)IOP331_REG_ADDR(0x000006A4)
DECL|macro|IOP331_PBBAR4
mdefine_line|#define IOP331_PBBAR4     (volatile u32 *)IOP331_REG_ADDR(0x000006A8)
DECL|macro|IOP331_PBLR4
mdefine_line|#define IOP331_PBLR4      (volatile u32 *)IOP331_REG_ADDR(0x000006AC)
DECL|macro|IOP331_PBBAR5
mdefine_line|#define IOP331_PBBAR5     (volatile u32 *)IOP331_REG_ADDR(0x000006B0)
DECL|macro|IOP331_PBLR5
mdefine_line|#define IOP331_PBLR5      (volatile u32 *)IOP331_REG_ADDR(0x000006B4)
DECL|macro|IOP331_PBDSCR
mdefine_line|#define IOP331_PBDSCR     (volatile u32 *)IOP331_REG_ADDR(0x000006B8)
multiline_comment|/* Reserved 0x000006BC */
DECL|macro|IOP331_PMBR0
mdefine_line|#define IOP331_PMBR0      (volatile u32 *)IOP331_REG_ADDR(0x000006C0)
multiline_comment|/* Reserved 0x000006C4 through 0x000006DC */
DECL|macro|IOP331_PMBR1
mdefine_line|#define IOP331_PMBR1      (volatile u32 *)IOP331_REG_ADDR(0x000006E0)
DECL|macro|IOP331_PMBR2
mdefine_line|#define IOP331_PMBR2      (volatile u32 *)IOP331_REG_ADDR(0x000006E4)
DECL|macro|IOP331_PBCR_EN
mdefine_line|#define IOP331_PBCR_EN    0x1
DECL|macro|IOP331_PBISR_BOOR_ERR
mdefine_line|#define IOP331_PBISR_BOOR_ERR 0x1
multiline_comment|/* Peripheral performance monitoring unit 0x00000700 through 0x00077F */
multiline_comment|/* Internal arbitration unit 0x00000780 through 0x0007BF */
multiline_comment|/* Interrupt Controller */
DECL|macro|IOP331_INTCTL0
mdefine_line|#define IOP331_INTCTL0    (volatile u32 *)IOP331_REG_ADDR(0x00000790)
DECL|macro|IOP331_INTCTL1
mdefine_line|#define IOP331_INTCTL1    (volatile u32 *)IOP331_REG_ADDR(0x00000794)
DECL|macro|IOP331_INTSTR0
mdefine_line|#define IOP331_INTSTR0    (volatile u32 *)IOP331_REG_ADDR(0x00000798)
DECL|macro|IOP331_INTSTR1
mdefine_line|#define IOP331_INTSTR1    (volatile u32 *)IOP331_REG_ADDR(0x0000079C)
DECL|macro|IOP331_IINTSRC0
mdefine_line|#define IOP331_IINTSRC0   (volatile u32 *)IOP331_REG_ADDR(0x000007A0)
DECL|macro|IOP331_IINTSRC1
mdefine_line|#define IOP331_IINTSRC1   (volatile u32 *)IOP331_REG_ADDR(0x000007A4)
DECL|macro|IOP331_FINTSRC0
mdefine_line|#define IOP331_FINTSRC0   (volatile u32 *)IOP331_REG_ADDR(0x000007A8)
DECL|macro|IOP331_FINTSRC1
mdefine_line|#define IOP331_FINTSRC1   (volatile u32 *)IOP331_REG_ADDR(0x000007AC)
DECL|macro|IOP331_IPR0
mdefine_line|#define IOP331_IPR0       (volatile u32 *)IOP331_REG_ADDR(0x000007B0)
DECL|macro|IOP331_IPR1
mdefine_line|#define IOP331_IPR1       (volatile u32 *)IOP331_REG_ADDR(0x000007B4)
DECL|macro|IOP331_IPR2
mdefine_line|#define IOP331_IPR2       (volatile u32 *)IOP331_REG_ADDR(0x000007B8)
DECL|macro|IOP331_IPR3
mdefine_line|#define IOP331_IPR3       (volatile u32 *)IOP331_REG_ADDR(0x000007BC)
DECL|macro|IOP331_INTBASE
mdefine_line|#define IOP331_INTBASE    (volatile u32 *)IOP331_REG_ADDR(0x000007C0)
DECL|macro|IOP331_INTSIZE
mdefine_line|#define IOP331_INTSIZE    (volatile u32 *)IOP331_REG_ADDR(0x000007C4)
DECL|macro|IOP331_IINTVEC
mdefine_line|#define IOP331_IINTVEC    (volatile u32 *)IOP331_REG_ADDR(0x000007C8)
DECL|macro|IOP331_FINTVEC
mdefine_line|#define IOP331_FINTVEC    (volatile u32 *)IOP331_REG_ADDR(0x000007CC)
multiline_comment|/* Timers */
DECL|macro|IOP331_TU_TMR0
mdefine_line|#define IOP331_TU_TMR0&t;&t;(volatile u32 *)IOP331_REG_ADDR(0x000007D0)
DECL|macro|IOP331_TU_TMR1
mdefine_line|#define IOP331_TU_TMR1&t;&t;(volatile u32 *)IOP331_REG_ADDR(0x000007D4)
DECL|macro|IOP331_TMR_TC
mdefine_line|#define IOP331_TMR_TC&t;&t;0x01
DECL|macro|IOP331_TMR_EN
mdefine_line|#define&t;IOP331_TMR_EN&t;&t;0x02
DECL|macro|IOP331_TMR_RELOAD
mdefine_line|#define IOP331_TMR_RELOAD&t;0x04
DECL|macro|IOP331_TMR_PRIVILEGED
mdefine_line|#define&t;IOP331_TMR_PRIVILEGED&t;0x09
DECL|macro|IOP331_TMR_RATIO_1_1
mdefine_line|#define&t;IOP331_TMR_RATIO_1_1&t;0x00
DECL|macro|IOP331_TMR_RATIO_4_1
mdefine_line|#define&t;IOP331_TMR_RATIO_4_1&t;0x10
DECL|macro|IOP331_TMR_RATIO_8_1
mdefine_line|#define&t;IOP331_TMR_RATIO_8_1&t;0x20
DECL|macro|IOP331_TMR_RATIO_16_1
mdefine_line|#define&t;IOP331_TMR_RATIO_16_1&t;0x30
DECL|macro|IOP331_TU_TCR0
mdefine_line|#define IOP331_TU_TCR0    (volatile u32 *)IOP331_REG_ADDR(0x000007D8)
DECL|macro|IOP331_TU_TCR1
mdefine_line|#define IOP331_TU_TCR1    (volatile u32 *)IOP331_REG_ADDR(0x000007DC)
DECL|macro|IOP331_TU_TRR0
mdefine_line|#define IOP331_TU_TRR0    (volatile u32 *)IOP331_REG_ADDR(0x000007E0)
DECL|macro|IOP331_TU_TRR1
mdefine_line|#define IOP331_TU_TRR1    (volatile u32 *)IOP331_REG_ADDR(0x000007E4)
DECL|macro|IOP331_TU_TISR
mdefine_line|#define IOP331_TU_TISR    (volatile u32 *)IOP331_REG_ADDR(0x000007E8)
DECL|macro|IOP331_TU_WDTCR
mdefine_line|#define IOP331_TU_WDTCR   (volatile u32 *)IOP331_REG_ADDR(0x000007EC)
macro_line|#if defined(CONFIG_ARCH_IOP331)
DECL|macro|IOP331_TICK_RATE
mdefine_line|#define&t;IOP331_TICK_RATE&t;266000000&t;/* 266 MHz IB clock */
macro_line|#endif
macro_line|#if defined(CONFIG_IOP331_STEPD) || defined(CONFIG_ARCH_IQ80333)
DECL|macro|IOP331_TICK_RATE
macro_line|#undef IOP331_TICK_RATE
DECL|macro|IOP331_TICK_RATE
mdefine_line|#define IOP331_TICK_RATE&t;333000000&t;/* 333 Mhz IB clock */
macro_line|#endif
multiline_comment|/* Application accelerator unit 0x00000800 - 0x000008FF */
DECL|macro|IOP331_AAU_ACR
mdefine_line|#define IOP331_AAU_ACR     (volatile u32 *)IOP331_REG_ADDR(0x00000800)
DECL|macro|IOP331_AAU_ASR
mdefine_line|#define IOP331_AAU_ASR     (volatile u32 *)IOP331_REG_ADDR(0x00000804)
DECL|macro|IOP331_AAU_ADAR
mdefine_line|#define IOP331_AAU_ADAR    (volatile u32 *)IOP331_REG_ADDR(0x00000808)
DECL|macro|IOP331_AAU_ANDAR
mdefine_line|#define IOP331_AAU_ANDAR   (volatile u32 *)IOP331_REG_ADDR(0x0000080C)
DECL|macro|IOP331_AAU_SAR1
mdefine_line|#define IOP331_AAU_SAR1    (volatile u32 *)IOP331_REG_ADDR(0x00000810)
DECL|macro|IOP331_AAU_SAR2
mdefine_line|#define IOP331_AAU_SAR2    (volatile u32 *)IOP331_REG_ADDR(0x00000814)
DECL|macro|IOP331_AAU_SAR3
mdefine_line|#define IOP331_AAU_SAR3    (volatile u32 *)IOP331_REG_ADDR(0x00000818)
DECL|macro|IOP331_AAU_SAR4
mdefine_line|#define IOP331_AAU_SAR4    (volatile u32 *)IOP331_REG_ADDR(0x0000081C)
DECL|macro|IOP331_AAU_SAR5
mdefine_line|#define IOP331_AAU_SAR5    (volatile u32 *)IOP331_REG_ADDR(0x0000082C)
DECL|macro|IOP331_AAU_SAR6
mdefine_line|#define IOP331_AAU_SAR6    (volatile u32 *)IOP331_REG_ADDR(0x00000830)
DECL|macro|IOP331_AAU_SAR7
mdefine_line|#define IOP331_AAU_SAR7    (volatile u32 *)IOP331_REG_ADDR(0x00000834)
DECL|macro|IOP331_AAU_SAR8
mdefine_line|#define IOP331_AAU_SAR8    (volatile u32 *)IOP331_REG_ADDR(0x00000838)
DECL|macro|IOP331_AAU_SAR9
mdefine_line|#define IOP331_AAU_SAR9    (volatile u32 *)IOP331_REG_ADDR(0x00000840)
DECL|macro|IOP331_AAU_SAR10
mdefine_line|#define IOP331_AAU_SAR10   (volatile u32 *)IOP331_REG_ADDR(0x00000844)
DECL|macro|IOP331_AAU_SAR11
mdefine_line|#define IOP331_AAU_SAR11   (volatile u32 *)IOP331_REG_ADDR(0x00000848)
DECL|macro|IOP331_AAU_SAR12
mdefine_line|#define IOP331_AAU_SAR12   (volatile u32 *)IOP331_REG_ADDR(0x0000084C)
DECL|macro|IOP331_AAU_SAR13
mdefine_line|#define IOP331_AAU_SAR13   (volatile u32 *)IOP331_REG_ADDR(0x00000850)
DECL|macro|IOP331_AAU_SAR14
mdefine_line|#define IOP331_AAU_SAR14   (volatile u32 *)IOP331_REG_ADDR(0x00000854)
DECL|macro|IOP331_AAU_SAR15
mdefine_line|#define IOP331_AAU_SAR15   (volatile u32 *)IOP331_REG_ADDR(0x00000858)
DECL|macro|IOP331_AAU_SAR16
mdefine_line|#define IOP331_AAU_SAR16   (volatile u32 *)IOP331_REG_ADDR(0x0000085C)
DECL|macro|IOP331_AAU_SAR17
mdefine_line|#define IOP331_AAU_SAR17   (volatile u32 *)IOP331_REG_ADDR(0x00000864)
DECL|macro|IOP331_AAU_SAR18
mdefine_line|#define IOP331_AAU_SAR18   (volatile u32 *)IOP331_REG_ADDR(0x00000868)
DECL|macro|IOP331_AAU_SAR19
mdefine_line|#define IOP331_AAU_SAR19   (volatile u32 *)IOP331_REG_ADDR(0x0000086C)
DECL|macro|IOP331_AAU_SAR20
mdefine_line|#define IOP331_AAU_SAR20   (volatile u32 *)IOP331_REG_ADDR(0x00000870)
DECL|macro|IOP331_AAU_SAR21
mdefine_line|#define IOP331_AAU_SAR21   (volatile u32 *)IOP331_REG_ADDR(0x00000874)
DECL|macro|IOP331_AAU_SAR22
mdefine_line|#define IOP331_AAU_SAR22   (volatile u32 *)IOP331_REG_ADDR(0x00000878)
DECL|macro|IOP331_AAU_SAR23
mdefine_line|#define IOP331_AAU_SAR23   (volatile u32 *)IOP331_REG_ADDR(0x0000087C)
DECL|macro|IOP331_AAU_SAR24
mdefine_line|#define IOP331_AAU_SAR24   (volatile u32 *)IOP331_REG_ADDR(0x00000880)
DECL|macro|IOP331_AAU_SAR25
mdefine_line|#define IOP331_AAU_SAR25   (volatile u32 *)IOP331_REG_ADDR(0x00000888)
DECL|macro|IOP331_AAU_SAR26
mdefine_line|#define IOP331_AAU_SAR26   (volatile u32 *)IOP331_REG_ADDR(0x0000088C)
DECL|macro|IOP331_AAU_SAR27
mdefine_line|#define IOP331_AAU_SAR27   (volatile u32 *)IOP331_REG_ADDR(0x00000890)
DECL|macro|IOP331_AAU_SAR28
mdefine_line|#define IOP331_AAU_SAR28   (volatile u32 *)IOP331_REG_ADDR(0x00000894)
DECL|macro|IOP331_AAU_SAR29
mdefine_line|#define IOP331_AAU_SAR29   (volatile u32 *)IOP331_REG_ADDR(0x00000898)
DECL|macro|IOP331_AAU_SAR30
mdefine_line|#define IOP331_AAU_SAR30   (volatile u32 *)IOP331_REG_ADDR(0x0000089C)
DECL|macro|IOP331_AAU_SAR31
mdefine_line|#define IOP331_AAU_SAR31   (volatile u32 *)IOP331_REG_ADDR(0x000008A0)
DECL|macro|IOP331_AAU_SAR32
mdefine_line|#define IOP331_AAU_SAR32   (volatile u32 *)IOP331_REG_ADDR(0x000008A4)
DECL|macro|IOP331_AAU_DAR
mdefine_line|#define IOP331_AAU_DAR     (volatile u32 *)IOP331_REG_ADDR(0x00000820)
DECL|macro|IOP331_AAU_ABCR
mdefine_line|#define IOP331_AAU_ABCR    (volatile u32 *)IOP331_REG_ADDR(0x00000824)
DECL|macro|IOP331_AAU_ADCR
mdefine_line|#define IOP331_AAU_ADCR    (volatile u32 *)IOP331_REG_ADDR(0x00000828)
DECL|macro|IOP331_AAU_EDCR0
mdefine_line|#define IOP331_AAU_EDCR0   (volatile u32 *)IOP331_REG_ADDR(0x0000083c)
DECL|macro|IOP331_AAU_EDCR1
mdefine_line|#define IOP331_AAU_EDCR1   (volatile u32 *)IOP331_REG_ADDR(0x00000860)
DECL|macro|IOP331_AAU_EDCR2
mdefine_line|#define IOP331_AAU_EDCR2   (volatile u32 *)IOP331_REG_ADDR(0x00000884)
DECL|macro|IOP331_SPDSCR
mdefine_line|#define IOP331_SPDSCR&t;  (volatile u32 *)IOP331_REG_ADDR(0x000015C0)
DECL|macro|IOP331_PPDSCR
mdefine_line|#define IOP331_PPDSCR&t;  (volatile u32 *)IOP331_REG_ADDR(0x000015C8)
multiline_comment|/* SSP serial port unit 0x00001600 - 0x0000167F */
multiline_comment|/* I2C bus interface unit 0x00001680 - 0x000016FF */
multiline_comment|/* for I2C bit defs see drivers/i2c/i2c-iop3xx.h */
DECL|macro|IOP331_ICR0
mdefine_line|#define IOP331_ICR0       (volatile u32 *)IOP331_REG_ADDR(0x00001680)
DECL|macro|IOP331_ISR0
mdefine_line|#define IOP331_ISR0       (volatile u32 *)IOP331_REG_ADDR(0x00001684)
DECL|macro|IOP331_ISAR0
mdefine_line|#define IOP331_ISAR0      (volatile u32 *)IOP331_REG_ADDR(0x00001688)
DECL|macro|IOP331_IDBR0
mdefine_line|#define IOP331_IDBR0      (volatile u32 *)IOP331_REG_ADDR(0x0000168C)
multiline_comment|/* Reserved 0x00001690 */
DECL|macro|IOP331_IBMR0
mdefine_line|#define IOP331_IBMR0      (volatile u32 *)IOP331_REG_ADDR(0x00001694)
multiline_comment|/* Reserved 0x00001698 */
multiline_comment|/* Reserved 0x0000169C */
DECL|macro|IOP331_ICR1
mdefine_line|#define IOP331_ICR1       (volatile u32 *)IOP331_REG_ADDR(0x000016A0)
DECL|macro|IOP331_ISR1
mdefine_line|#define IOP331_ISR1       (volatile u32 *)IOP331_REG_ADDR(0x000016A4)
DECL|macro|IOP331_ISAR1
mdefine_line|#define IOP331_ISAR1      (volatile u32 *)IOP331_REG_ADDR(0x000016A8)
DECL|macro|IOP331_IDBR1
mdefine_line|#define IOP331_IDBR1      (volatile u32 *)IOP331_REG_ADDR(0x000016AC)
DECL|macro|IOP331_IBMR1
mdefine_line|#define IOP331_IBMR1      (volatile u32 *)IOP331_REG_ADDR(0x000016B4)
multiline_comment|/* Reserved 0x000016B8 through 0x000016FF */
multiline_comment|/* 0x00001700 through 0x0000172C  UART 0 */
multiline_comment|/* Reserved 0x00001730 through 0x0000173F */
multiline_comment|/* 0x00001740 through 0x0000176C UART 1 */
DECL|macro|IOP331_UART0_PHYS
mdefine_line|#define IOP331_UART0_PHYS  (IOP331_PHYS_MEM_BASE | 0x00001700)&t;/* UART #1 physical */
DECL|macro|IOP331_UART1_PHYS
mdefine_line|#define IOP331_UART1_PHYS  (IOP331_PHYS_MEM_BASE | 0x00001740)&t;/* UART #2 physical */
DECL|macro|IOP331_UART0_VIRT
mdefine_line|#define IOP331_UART0_VIRT  (IOP331_VIRT_MEM_BASE | 0x00001700) /* UART #1 virtual addr */
DECL|macro|IOP331_UART1_VIRT
mdefine_line|#define IOP331_UART1_VIRT  (IOP331_VIRT_MEM_BASE | 0x00001740) /* UART #2 virtual addr */
multiline_comment|/* Reserved 0x00001770 through 0x0000177F */
multiline_comment|/* General Purpose I/O Registers */
DECL|macro|IOP331_GPOE
mdefine_line|#define IOP331_GPOE       (volatile u32 *)IOP331_REG_ADDR(0x00001780)
DECL|macro|IOP331_GPID
mdefine_line|#define IOP331_GPID       (volatile u32 *)IOP331_REG_ADDR(0x00001784)
DECL|macro|IOP331_GPOD
mdefine_line|#define IOP331_GPOD       (volatile u32 *)IOP331_REG_ADDR(0x00001788)
multiline_comment|/* Reserved 0x0000178c through 0x000019ff */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|iop331_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iop331_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|iop331_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif 
singleline_comment|// _IOP331_HW_H_
eof
