multiline_comment|/*&n; * linux/include/asm/arch-iop3xx/iop321.h&n; *&n; * Intel IOP321 Chip definitions&n; *&n; * Author: Rory Bolt &lt;rorybolt@pacbell.net&gt;&n; * Copyright (C) 2002 Rory Bolt&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _IOP321_HW_H_
DECL|macro|_IOP321_HW_H_
mdefine_line|#define _IOP321_HW_H_
multiline_comment|/*&n; * IOP321 I/O and Mem space regions for PCI autoconfiguration&n; */
DECL|macro|IOP321_PCI_IO_BASE
mdefine_line|#define&t;IOP321_PCI_IO_BASE&t;&t;0x90000000
DECL|macro|IOP321_PCI_IO_SIZE
mdefine_line|#define&t;IOP321_PCI_IO_SIZE&t;&t;0x00010000
DECL|macro|IOP321_PCI_MEM_BASE
mdefine_line|#define IOP321_PCI_MEM_BASE&t;&t;0x40000000
DECL|macro|IOP321_PCI_MEM_SIZE
mdefine_line|#define IOP321_PCI_MEM_SIZE&t;&t;0x40000000
multiline_comment|/*&n; * IOP321 chipset registers&n; */
DECL|macro|IOP321_VIRT_MEM_BASE
mdefine_line|#define IOP321_VIRT_MEM_BASE 0xfff00000  /* chip virtual mem address*/
DECL|macro|IOP321_PHY_MEM_BASE
mdefine_line|#define IOP321_PHY_MEM_BASE  0xffffe000  /* chip physical memory address */
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
multiline_comment|/* DMA Controller 0x00000400 through 0x000004FF */
multiline_comment|/* Memory controller 0x00000500 through 0x0005FF */
multiline_comment|/* Peripheral bus interface unit 0x00000680 through 0x0006FF */
multiline_comment|/* Peripheral performance monitoring unit 0x00000700 through 0x00077F */
multiline_comment|/* Internal arbitration unit 0x00000780 through 0x0007BF */
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
DECL|macro|IOP321_AAUACR
mdefine_line|#define IOP321_AAUACR     (volatile u32 *)IOP321_REG_ADDR(0x00000800)
DECL|macro|IOP321_AAUASR
mdefine_line|#define IOP321_AAUASR     (volatile u32 *)IOP321_REG_ADDR(0x00000804)
DECL|macro|IOP321_AAUANDAR
mdefine_line|#define IOP321_AAUANDAR   (volatile u32 *)IOP321_REG_ADDR(0x0000080C)
multiline_comment|/* SSP serial port unit 0x00001600 - 0x0000167F */
multiline_comment|/* I2C bus interface unit 0x00001680 - 0x000016FF */
macro_line|#endif 
singleline_comment|// _IOP321_HW_H_
eof
