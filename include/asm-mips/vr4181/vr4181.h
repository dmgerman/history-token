multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999 by Michael Klar&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; */
macro_line|#ifndef __ASM_VR4181_VR4181_H
DECL|macro|__ASM_VR4181_VR4181_H
mdefine_line|#define __ASM_VR4181_VR4181_H
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/vr4181/irq.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|macro|__preg8
mdefine_line|#define __preg8&t;&t;(volatile unsigned char*)
DECL|macro|__preg16
mdefine_line|#define __preg16&t;(volatile unsigned short*)
DECL|macro|__preg32
mdefine_line|#define __preg32&t;(volatile unsigned int*)
macro_line|#else
DECL|macro|__preg8
mdefine_line|#define __preg8
DECL|macro|__preg16
mdefine_line|#define __preg16
DECL|macro|__preg32
mdefine_line|#define __preg32
macro_line|#endif
singleline_comment|// Embedded CPU peripheral registers
singleline_comment|// Note that many of the registers have different physical address for VR4181
singleline_comment|// Bus Control Unit (BCU)
DECL|macro|VR4181_BCUCNTREG1
mdefine_line|#define VR4181_BCUCNTREG1&t;__preg16(KSEG1 + 0x0A000000)&t;/* BCU control register 1 (R/W) */
DECL|macro|VR4181_CMUCLKMSK
mdefine_line|#define VR4181_CMUCLKMSK&t;__preg16(KSEG1 + 0x0A000004)&t;/* Clock mask register (R/W) */
DECL|macro|VR4181_CMUCLKMSK_MSKCSUPCLK
mdefine_line|#define VR4181_CMUCLKMSK_MSKCSUPCLK  0x0040
DECL|macro|VR4181_CMUCLKMSK_MSKAIUPCLK
mdefine_line|#define VR4181_CMUCLKMSK_MSKAIUPCLK  0x0020
DECL|macro|VR4181_CMUCLKMSK_MSKPIUPCLK
mdefine_line|#define VR4181_CMUCLKMSK_MSKPIUPCLK  0x0010
DECL|macro|VR4181_CMUCLKMSK_MSKADUPCLK
mdefine_line|#define VR4181_CMUCLKMSK_MSKADUPCLK  0x0008
DECL|macro|VR4181_CMUCLKMSK_MSKSIU18M
mdefine_line|#define VR4181_CMUCLKMSK_MSKSIU18M   0x0004
DECL|macro|VR4181_CMUCLKMSK_MSKADU18M
mdefine_line|#define VR4181_CMUCLKMSK_MSKADU18M   0x0002
DECL|macro|VR4181_CMUCLKMSK_MSKUSB
mdefine_line|#define VR4181_CMUCLKMSK_MSKUSB      0x0001
DECL|macro|VR4181_CMUCLKMSK_MSKSIU
mdefine_line|#define VR4181_CMUCLKMSK_MSKSIU      VR4181_CMUCLKMSK_MSKSIU18M
DECL|macro|VR4181_BCUSPEEDREG
mdefine_line|#define VR4181_BCUSPEEDREG&t;__preg16(KSEG1 + 0x0A00000C)&t;/* BCU access time parameter (R/W) */
DECL|macro|VR4181_BCURFCNTREG
mdefine_line|#define VR4181_BCURFCNTREG&t;__preg16(KSEG1 + 0x0A000010)&t;/* BCU refresh control register (R/W) */
DECL|macro|VR4181_REVIDREG
mdefine_line|#define VR4181_REVIDREG&t;&t;__preg16(KSEG1 + 0x0A000014)&t;/* Revision ID register (R) */
DECL|macro|VR4181_CLKSPEEDREG
mdefine_line|#define VR4181_CLKSPEEDREG&t;__preg16(KSEG1 + 0x0A000018)&t;/* Clock speed register (R) */
DECL|macro|VR4181_EDOMCYTREG
mdefine_line|#define VR4181_EDOMCYTREG&t;__preg16(KSEG1 + 0x0A000300)&t;/* Memory cycle timing register (R/W) */
DECL|macro|VR4181_MEMCFG_REG
mdefine_line|#define VR4181_MEMCFG_REG&t;__preg16(KSEG1 + 0x0A000304)&t;/* Memory configuration register (R/W) */
DECL|macro|VR4181_MODE_REG
mdefine_line|#define VR4181_MODE_REG&t;&t;__preg16(KSEG1 + 0x0A000308)&t;/* SDRAM mode register (R/W) */
DECL|macro|VR4181_SDTIMINGREG
mdefine_line|#define VR4181_SDTIMINGREG&t;__preg16(KSEG1 + 0x0A00030C)&t;/* SDRAM timing register (R/W) */
singleline_comment|// DMA Control Unit (DCU)
DECL|macro|VR4181_MICDEST1REG1
mdefine_line|#define VR4181_MICDEST1REG1&t;__preg16(KSEG1 + 0x0A000020)&t;/* Microphone destination 1 address register 1 (R/W) */
DECL|macro|VR4181_MICDEST1REG2
mdefine_line|#define VR4181_MICDEST1REG2&t;__preg16(KSEG1 + 0x0A000022)&t;/* Microphone destination 1 address register 2 (R/W) */
DECL|macro|VR4181_MICDEST2REG1
mdefine_line|#define VR4181_MICDEST2REG1&t;__preg16(KSEG1 + 0x0A000024)&t;/* Microphone destination 2 address register 1 (R/W) */
DECL|macro|VR4181_MICDEST2REG2
mdefine_line|#define VR4181_MICDEST2REG2&t;__preg16(KSEG1 + 0x0A000026)&t;/* Microphone destination 2 address register 2 (R/W) */
DECL|macro|VR4181_SPKRRC1REG1
mdefine_line|#define VR4181_SPKRRC1REG1&t;__preg16(KSEG1 + 0x0A000028)&t;/* Speaker Source 1 address register 1 (R/W) */
DECL|macro|VR4181_SPKRRC1REG2
mdefine_line|#define VR4181_SPKRRC1REG2&t;__preg16(KSEG1 + 0x0A00002A)&t;/* Speaker Source 1 address register 2 (R/W) */
DECL|macro|VR4181_SPKRRC2REG1
mdefine_line|#define VR4181_SPKRRC2REG1&t;__preg16(KSEG1 + 0x0A00002C)&t;/* Speaker Source 2 address register 1 (R/W) */
DECL|macro|VR4181_SPKRRC2REG2
mdefine_line|#define VR4181_SPKRRC2REG2&t;__preg16(KSEG1 + 0x0A00002E)&t;/* Speaker Source 2 address register 2 (R/W) */
DECL|macro|VR4181_DMARSTREG
mdefine_line|#define VR4181_DMARSTREG&t;__preg16(KSEG1 + 0x0A000040)&t;/* DMA Reset register (R/W) */
DECL|macro|VR4181_AIUDMAMSKREG
mdefine_line|#define VR4181_AIUDMAMSKREG&t;__preg16(KSEG1 + 0x0A000046)&t;/* Audio DMA mask register (R/W) */
DECL|macro|VR4181_USBDMAMSKREG
mdefine_line|#define VR4181_USBDMAMSKREG&t;__preg16(KSEG1 + 0x0A000600)&t;/* USB DMA Mask register (R/W) */
DECL|macro|VR4181_USBRXS1AREG1
mdefine_line|#define VR4181_USBRXS1AREG1&t;__preg16(KSEG1 + 0x0A000602)&t;/* USB Rx source 1 address register 1 (R/W) */
DECL|macro|VR4181_USBRXS1AREG2
mdefine_line|#define VR4181_USBRXS1AREG2&t;__preg16(KSEG1 + 0x0A000604)&t;/* USB Rx source 1 address register 2 (R/W) */
DECL|macro|VR4181_USBRXS2AREG1
mdefine_line|#define VR4181_USBRXS2AREG1&t;__preg16(KSEG1 + 0x0A000606)&t;/* USB Rx source 2 address register 1 (R/W) */
DECL|macro|VR4181_USBRXS2AREG2
mdefine_line|#define VR4181_USBRXS2AREG2&t;__preg16(KSEG1 + 0x0A000608)&t;/* USB Rx source 2 address register 2 (R/W) */
DECL|macro|VR4181_USBTXS1AREG1
mdefine_line|#define VR4181_USBTXS1AREG1&t;__preg16(KSEG1 + 0x0A00060A)&t;/* USB Tx source 1 address register 1 (R/W) */
DECL|macro|VR4181_USBTXS1AREG2
mdefine_line|#define VR4181_USBTXS1AREG2&t;__preg16(KSEG1 + 0x0A00060C)&t;/* USB Tx source 1 address register 2 (R/W) */
DECL|macro|VR4181_USBTXS2AREG1
mdefine_line|#define VR4181_USBTXS2AREG1&t;__preg16(KSEG1 + 0x0A00060E)&t;/* USB Tx source 2 address register 1 (R/W) */
DECL|macro|VR4181_USBTXS2AREG2
mdefine_line|#define VR4181_USBTXS2AREG2&t;__preg16(KSEG1 + 0x0A000610)&t;/* USB Tx source 2 address register 2 (R/W) */
DECL|macro|VR4181_USBRXD1AREG1
mdefine_line|#define VR4181_USBRXD1AREG1&t;__preg16(KSEG1 + 0x0A00062A)&t;/* USB Rx destination 1 address register 1 (R/W) */
DECL|macro|VR4181_USBRXD1AREG2
mdefine_line|#define VR4181_USBRXD1AREG2&t;__preg16(KSEG1 + 0x0A00062C)&t;/* USB Rx destination 1 address register 2 (R/W) */
DECL|macro|VR4181_USBRXD2AREG1
mdefine_line|#define VR4181_USBRXD2AREG1&t;__preg16(KSEG1 + 0x0A00062E)&t;/* USB Rx destination 2 address register 1 (R/W) */
DECL|macro|VR4181_USBRXD2AREG2
mdefine_line|#define VR4181_USBRXD2AREG2&t;__preg16(KSEG1 + 0x0A000630)&t;/* USB Rx destination 2 address register 2 (R/W) */
DECL|macro|VR4181_USBTXD1AREG1
mdefine_line|#define VR4181_USBTXD1AREG1&t;__preg16(KSEG1 + 0x0A000632)&t;/* USB Tx destination 1 address register 1 (R/W) */
DECL|macro|VR4181_USBTXD1AREG2
mdefine_line|#define VR4181_USBTXD1AREG2&t;__preg16(KSEG1 + 0x0A000634)&t;/* USB Tx destination 1 address register 2 (R/W) */
DECL|macro|VR4181_USBTXD2AREG1
mdefine_line|#define VR4181_USBTXD2AREG1&t;__preg16(KSEG1 + 0x0A000636)&t;/* USB Tx destination 2 address register 1 (R/W) */
DECL|macro|VR4181_USBTXD2AREG2
mdefine_line|#define VR4181_USBTXD2AREG2&t;__preg16(KSEG1 + 0x0A000638)&t;/* USB Tx destination 2 address register 2 (R/W) */
DECL|macro|VR4181_RxRCLENREG
mdefine_line|#define VR4181_RxRCLENREG&t;__preg16(KSEG1 + 0x0A000652)&t;/* USB Rx record length register (R/W) */
DECL|macro|VR4181_TxRCLENREG
mdefine_line|#define VR4181_TxRCLENREG&t;__preg16(KSEG1 + 0x0A000654)&t;/* USB Tx record length register (R/W) */
DECL|macro|VR4181_MICRCLENREG
mdefine_line|#define VR4181_MICRCLENREG&t;__preg16(KSEG1 + 0x0A000658)&t;/* Microphone record length register (R/W) */
DECL|macro|VR4181_SPKRCLENREG
mdefine_line|#define VR4181_SPKRCLENREG&t;__preg16(KSEG1 + 0x0A00065A)&t;/* Speaker record length register (R/W) */
DECL|macro|VR4181_USBCFGREG
mdefine_line|#define VR4181_USBCFGREG&t;__preg16(KSEG1 + 0x0A00065C)&t;/* USB configuration register (R/W) */
DECL|macro|VR4181_MICDMACFGREG
mdefine_line|#define VR4181_MICDMACFGREG&t;__preg16(KSEG1 + 0x0A00065E)&t;/* Microphone DMA configuration register (R/W) */
DECL|macro|VR4181_SPKDMACFGREG
mdefine_line|#define VR4181_SPKDMACFGREG&t;__preg16(KSEG1 + 0x0A000660)&t;/* Speaker DMA configuration register (R/W) */
DECL|macro|VR4181_DMAITRQREG
mdefine_line|#define VR4181_DMAITRQREG&t;__preg16(KSEG1 + 0x0A000662)&t;/* DMA interrupt request register (R/W) */
DECL|macro|VR4181_DMACLTREG
mdefine_line|#define VR4181_DMACLTREG&t;__preg16(KSEG1 + 0x0A000664)&t;/* DMA control register (R/W) */
DECL|macro|VR4181_DMAITMKREG
mdefine_line|#define VR4181_DMAITMKREG&t;__preg16(KSEG1 + 0x0A000666)&t;/* DMA interrupt mask register (R/W) */
singleline_comment|// ISA Bridge
DECL|macro|VR4181_ISABRGCTL
mdefine_line|#define VR4181_ISABRGCTL&t;__preg16(KSEG1 + 0x0B0002C0)&t;/* ISA Bridge Control Register (R/W) */
DECL|macro|VR4181_ISABRGSTS
mdefine_line|#define VR4181_ISABRGSTS&t;__preg16(KSEG1 + 0x0B0002C2)&t;/* ISA Bridge Status Register (R/W) */
DECL|macro|VR4181_XISACTL
mdefine_line|#define VR4181_XISACTL&t;&t;__preg16(KSEG1 + 0x0B0002C4)&t;/* External ISA Control Register (R/W) */
singleline_comment|// Clocked Serial Interface (CSI)
DECL|macro|VR4181_CSIMODE
mdefine_line|#define VR4181_CSIMODE&t;&t;__preg16(KSEG1 + 0x0B000900)&t;/* CSI Mode Register (R/W) */
DECL|macro|VR4181_CSIRXDATA
mdefine_line|#define VR4181_CSIRXDATA&t;__preg16(KSEG1 + 0x0B000902)&t;/* CSI Receive Data Register (R) */
DECL|macro|VR4181_CSITXDATA
mdefine_line|#define VR4181_CSITXDATA&t;__preg16(KSEG1 + 0x0B000904)&t;/* CSI Transmit Data Register (R/W) */
DECL|macro|VR4181_CSILSTAT
mdefine_line|#define VR4181_CSILSTAT&t;&t;__preg16(KSEG1 + 0x0B000906)&t;/* CSI Line Status Register (R/W) */
DECL|macro|VR4181_CSIINTMSK
mdefine_line|#define VR4181_CSIINTMSK&t;__preg16(KSEG1 + 0x0B000908)&t;/* CSI Interrupt Mask Register (R/W) */
DECL|macro|VR4181_CSIINTSTAT
mdefine_line|#define VR4181_CSIINTSTAT&t;__preg16(KSEG1 + 0x0B00090a)&t;/* CSI Interrupt Status Register (R/W) */
DECL|macro|VR4181_CSITXBLEN
mdefine_line|#define VR4181_CSITXBLEN&t;__preg16(KSEG1 + 0x0B00090c)&t;/* CSI Transmit Burst Length Register (R/W) */
DECL|macro|VR4181_CSIRXBLEN
mdefine_line|#define VR4181_CSIRXBLEN&t;__preg16(KSEG1 + 0x0B00090e)&t;/* CSI Receive Burst Length Register (R/W) */
singleline_comment|// Interrupt Control Unit (ICU)
DECL|macro|VR4181_SYSINT1REG
mdefine_line|#define VR4181_SYSINT1REG&t;__preg16(KSEG1 + 0x0A000080)&t;/* Level 1 System interrupt register 1 (R) */
DECL|macro|VR4181_MSYSINT1REG
mdefine_line|#define VR4181_MSYSINT1REG&t;__preg16(KSEG1 + 0x0A00008C)&t;/* Level 1 mask system interrupt register 1 (R/W) */
DECL|macro|VR4181_NMIREG
mdefine_line|#define VR4181_NMIREG&t;&t;__preg16(KSEG1 + 0x0A000098)&t;/* NMI register (R/W) */
DECL|macro|VR4181_SOFTINTREG
mdefine_line|#define VR4181_SOFTINTREG&t;__preg16(KSEG1 + 0x0A00009A)&t;/* Software interrupt register (R/W) */
DECL|macro|VR4181_SYSINT2REG
mdefine_line|#define VR4181_SYSINT2REG&t;__preg16(KSEG1 + 0x0A000200)&t;/* Level 1 System interrupt register 2 (R) */
DECL|macro|VR4181_MSYSINT2REG
mdefine_line|#define VR4181_MSYSINT2REG&t;__preg16(KSEG1 + 0x0A000206)&t;/* Level 1 mask system interrupt register 2 (R/W) */
DECL|macro|VR4181_PIUINTREGro
mdefine_line|#define VR4181_PIUINTREGro&t;__preg16(KSEG1 + 0x0B000082)&t;/* Level 2 PIU interrupt register (R) */
DECL|macro|VR4181_AIUINTREG
mdefine_line|#define VR4181_AIUINTREG&t;__preg16(KSEG1 + 0x0B000084)&t;/* Level 2 AIU interrupt register (R) */
DECL|macro|VR4181_MPIUINTREG
mdefine_line|#define VR4181_MPIUINTREG&t;__preg16(KSEG1 + 0x0B00008E)&t;/* Level 2 mask PIU interrupt register (R/W) */
DECL|macro|VR4181_MAIUINTREG
mdefine_line|#define VR4181_MAIUINTREG&t;__preg16(KSEG1 + 0x0B000090)&t;/* Level 2 mask AIU interrupt register (R/W) */
DECL|macro|VR4181_MKIUINTREG
mdefine_line|#define VR4181_MKIUINTREG&t;__preg16(KSEG1 + 0x0B000092)&t;/* Level 2 mask KIU interrupt register (R/W) */
DECL|macro|VR4181_KIUINTREG
mdefine_line|#define VR4181_KIUINTREG&t;__preg16(KSEG1 + 0x0B000198)&t;/* Level 2 KIU interrupt register (R) */
singleline_comment|// Power Management Unit (PMU)
DECL|macro|VR4181_PMUINTREG
mdefine_line|#define VR4181_PMUINTREG&t;__preg16(KSEG1 + 0x0B0000A0)&t;/* PMU Status Register (R/W) */
DECL|macro|VR4181_PMUINT_POWERSW
mdefine_line|#define VR4181_PMUINT_POWERSW  0x1&t;/* Power switch */
DECL|macro|VR4181_PMUINT_BATT
mdefine_line|#define VR4181_PMUINT_BATT     0x2&t;/* Low batt during normal operation */
DECL|macro|VR4181_PMUINT_DEADMAN
mdefine_line|#define VR4181_PMUINT_DEADMAN  0x4&t;/* Deadman&squot;s switch */
DECL|macro|VR4181_PMUINT_RESET
mdefine_line|#define VR4181_PMUINT_RESET    0x8&t;/* Reset switch */
DECL|macro|VR4181_PMUINT_RTCRESET
mdefine_line|#define VR4181_PMUINT_RTCRESET 0x10&t;/* RTC Reset */
DECL|macro|VR4181_PMUINT_TIMEOUT
mdefine_line|#define VR4181_PMUINT_TIMEOUT  0x20&t;/* HAL Timer Reset */
DECL|macro|VR4181_PMUINT_BATTLOW
mdefine_line|#define VR4181_PMUINT_BATTLOW  0x100&t;/* Battery low */
DECL|macro|VR4181_PMUINT_RTC
mdefine_line|#define VR4181_PMUINT_RTC      0x200&t;/* RTC Alarm */
DECL|macro|VR4181_PMUINT_DCD
mdefine_line|#define VR4181_PMUINT_DCD      0x400&t;/* DCD# */
DECL|macro|VR4181_PMUINT_GPIO0
mdefine_line|#define VR4181_PMUINT_GPIO0    0x1000&t;/* GPIO0 */
DECL|macro|VR4181_PMUINT_GPIO1
mdefine_line|#define VR4181_PMUINT_GPIO1    0x2000&t;/* GPIO1 */
DECL|macro|VR4181_PMUINT_GPIO2
mdefine_line|#define VR4181_PMUINT_GPIO2    0x4000&t;/* GPIO2 */
DECL|macro|VR4181_PMUINT_GPIO3
mdefine_line|#define VR4181_PMUINT_GPIO3    0x8000&t;/* GPIO3 */
DECL|macro|VR4181_PMUCNTREG
mdefine_line|#define VR4181_PMUCNTREG&t;__preg16(KSEG1 + 0x0B0000A2)&t;/* PMU Control Register (R/W) */
DECL|macro|VR4181_PMUWAITREG
mdefine_line|#define VR4181_PMUWAITREG&t;__preg16(KSEG1 + 0x0B0000A8)&t;/* PMU Wait Counter Register (R/W) */
DECL|macro|VR4181_PMUDIVREG
mdefine_line|#define VR4181_PMUDIVREG&t;__preg16(KSEG1 + 0x0B0000AC)&t;/* PMU Divide Mode Register (R/W) */
DECL|macro|VR4181_DRAMHIBCTL
mdefine_line|#define VR4181_DRAMHIBCTL&t;__preg16(KSEG1 + 0x0B0000B2)&t;/* DRAM Hibernate Control Register (R/W) */
singleline_comment|// Real Time Clock Unit (RTC)
DECL|macro|VR4181_ETIMELREG
mdefine_line|#define VR4181_ETIMELREG&t;__preg16(KSEG1 + 0x0B0000C0)&t;/* Elapsed Time L Register (R/W) */
DECL|macro|VR4181_ETIMEMREG
mdefine_line|#define VR4181_ETIMEMREG&t;__preg16(KSEG1 + 0x0B0000C2)&t;/* Elapsed Time M Register (R/W) */
DECL|macro|VR4181_ETIMEHREG
mdefine_line|#define VR4181_ETIMEHREG&t;__preg16(KSEG1 + 0x0B0000C4)&t;/* Elapsed Time H Register (R/W) */
DECL|macro|VR4181_ECMPLREG
mdefine_line|#define VR4181_ECMPLREG&t;&t;__preg16(KSEG1 + 0x0B0000C8)&t;/* Elapsed Compare L Register (R/W) */
DECL|macro|VR4181_ECMPMREG
mdefine_line|#define VR4181_ECMPMREG&t;&t;__preg16(KSEG1 + 0x0B0000CA)&t;/* Elapsed Compare M Register (R/W) */
DECL|macro|VR4181_ECMPHREG
mdefine_line|#define VR4181_ECMPHREG&t;&t;__preg16(KSEG1 + 0x0B0000CC)&t;/* Elapsed Compare H Register (R/W) */
DECL|macro|VR4181_RTCL1LREG
mdefine_line|#define VR4181_RTCL1LREG&t;__preg16(KSEG1 + 0x0B0000D0)&t;/* RTC Long 1 L Register (R/W) */
DECL|macro|VR4181_RTCL1HREG
mdefine_line|#define VR4181_RTCL1HREG&t;__preg16(KSEG1 + 0x0B0000D2)&t;/* RTC Long 1 H Register (R/W) */
DECL|macro|VR4181_RTCL1CNTLREG
mdefine_line|#define VR4181_RTCL1CNTLREG&t;__preg16(KSEG1 + 0x0B0000D4)&t;/* RTC Long 1 Count L Register (R) */
DECL|macro|VR4181_RTCL1CNTHREG
mdefine_line|#define VR4181_RTCL1CNTHREG&t;__preg16(KSEG1 + 0x0B0000D6)&t;/* RTC Long 1 Count H Register (R) */
DECL|macro|VR4181_RTCL2LREG
mdefine_line|#define VR4181_RTCL2LREG&t;__preg16(KSEG1 + 0x0B0000D8)&t;/* RTC Long 2 L Register (R/W) */
DECL|macro|VR4181_RTCL2HREG
mdefine_line|#define VR4181_RTCL2HREG&t;__preg16(KSEG1 + 0x0B0000DA)&t;/* RTC Long 2 H Register (R/W) */
DECL|macro|VR4181_RTCL2CNTLREG
mdefine_line|#define VR4181_RTCL2CNTLREG&t;__preg16(KSEG1 + 0x0B0000DC)&t;/* RTC Long 2 Count L Register (R) */
DECL|macro|VR4181_RTCL2CNTHREG
mdefine_line|#define VR4181_RTCL2CNTHREG&t;__preg16(KSEG1 + 0x0B0000DE)&t;/* RTC Long 2 Count H Register (R) */
DECL|macro|VR4181_RTCINTREG
mdefine_line|#define VR4181_RTCINTREG&t;__preg16(KSEG1 + 0x0B0001DE)&t;/* RTC Interrupt Register (R/W) */
singleline_comment|// Deadman&squot;s Switch Unit (DSU)
DECL|macro|VR4181_DSUCNTREG
mdefine_line|#define VR4181_DSUCNTREG&t;__preg16(KSEG1 + 0x0B0000E0)&t;/* DSU Control Register (R/W) */
DECL|macro|VR4181_DSUSETREG
mdefine_line|#define VR4181_DSUSETREG&t;__preg16(KSEG1 + 0x0B0000E2)&t;/* DSU Dead Time Set Register (R/W) */
DECL|macro|VR4181_DSUCLRREG
mdefine_line|#define VR4181_DSUCLRREG&t;__preg16(KSEG1 + 0x0B0000E4)&t;/* DSU Clear Register (W) */
DECL|macro|VR4181_DSUTIMREG
mdefine_line|#define VR4181_DSUTIMREG&t;__preg16(KSEG1 + 0x0B0000E6)&t;/* DSU Elapsed Time Register (R/W) */
singleline_comment|// General Purpose I/O Unit (GIU)
DECL|macro|VR4181_GPMD0REG
mdefine_line|#define VR4181_GPMD0REG&t;&t;__preg16(KSEG1 + 0x0B000300)&t;/* GPIO Mode 0 Register (R/W) */
DECL|macro|VR4181_GPMD1REG
mdefine_line|#define VR4181_GPMD1REG&t;&t;__preg16(KSEG1 + 0x0B000302)&t;/* GPIO Mode 1 Register (R/W) */
DECL|macro|VR4181_GPMD2REG
mdefine_line|#define VR4181_GPMD2REG&t;&t;__preg16(KSEG1 + 0x0B000304)&t;/* GPIO Mode 2 Register (R/W) */
DECL|macro|VR4181_GPMD3REG
mdefine_line|#define VR4181_GPMD3REG&t;&t;__preg16(KSEG1 + 0x0B000306)&t;/* GPIO Mode 3 Register (R/W) */
DECL|macro|VR4181_GPDATHREG
mdefine_line|#define VR4181_GPDATHREG&t;__preg16(KSEG1 + 0x0B000308)&t;/* GPIO Data High Register (R/W) */
DECL|macro|VR4181_GPDATHREG_GPIO16
mdefine_line|#define VR4181_GPDATHREG_GPIO16  0x0001
DECL|macro|VR4181_GPDATHREG_GPIO17
mdefine_line|#define VR4181_GPDATHREG_GPIO17  0x0002
DECL|macro|VR4181_GPDATHREG_GPIO18
mdefine_line|#define VR4181_GPDATHREG_GPIO18  0x0004
DECL|macro|VR4181_GPDATHREG_GPIO19
mdefine_line|#define VR4181_GPDATHREG_GPIO19  0x0008
DECL|macro|VR4181_GPDATHREG_GPIO20
mdefine_line|#define VR4181_GPDATHREG_GPIO20  0x0010
DECL|macro|VR4181_GPDATHREG_GPIO21
mdefine_line|#define VR4181_GPDATHREG_GPIO21  0x0020
DECL|macro|VR4181_GPDATHREG_GPIO22
mdefine_line|#define VR4181_GPDATHREG_GPIO22  0x0040
DECL|macro|VR4181_GPDATHREG_GPIO23
mdefine_line|#define VR4181_GPDATHREG_GPIO23  0x0080
DECL|macro|VR4181_GPDATHREG_GPIO24
mdefine_line|#define VR4181_GPDATHREG_GPIO24  0x0100
DECL|macro|VR4181_GPDATHREG_GPIO25
mdefine_line|#define VR4181_GPDATHREG_GPIO25  0x0200
DECL|macro|VR4181_GPDATHREG_GPIO26
mdefine_line|#define VR4181_GPDATHREG_GPIO26  0x0400
DECL|macro|VR4181_GPDATHREG_GPIO27
mdefine_line|#define VR4181_GPDATHREG_GPIO27  0x0800
DECL|macro|VR4181_GPDATHREG_GPIO28
mdefine_line|#define VR4181_GPDATHREG_GPIO28  0x1000
DECL|macro|VR4181_GPDATHREG_GPIO29
mdefine_line|#define VR4181_GPDATHREG_GPIO29  0x2000
DECL|macro|VR4181_GPDATHREG_GPIO30
mdefine_line|#define VR4181_GPDATHREG_GPIO30  0x4000
DECL|macro|VR4181_GPDATHREG_GPIO31
mdefine_line|#define VR4181_GPDATHREG_GPIO31  0x8000
DECL|macro|VR4181_GPDATLREG
mdefine_line|#define VR4181_GPDATLREG&t;__preg16(KSEG1 + 0x0B00030A)&t;/* GPIO Data Low Register (R/W) */
DECL|macro|VR4181_GPDATLREG_GPIO0
mdefine_line|#define VR4181_GPDATLREG_GPIO0   0x0001
DECL|macro|VR4181_GPDATLREG_GPIO1
mdefine_line|#define VR4181_GPDATLREG_GPIO1   0x0002
DECL|macro|VR4181_GPDATLREG_GPIO2
mdefine_line|#define VR4181_GPDATLREG_GPIO2   0x0004
DECL|macro|VR4181_GPDATLREG_GPIO3
mdefine_line|#define VR4181_GPDATLREG_GPIO3   0x0008
DECL|macro|VR4181_GPDATLREG_GPIO4
mdefine_line|#define VR4181_GPDATLREG_GPIO4   0x0010
DECL|macro|VR4181_GPDATLREG_GPIO5
mdefine_line|#define VR4181_GPDATLREG_GPIO5   0x0020
DECL|macro|VR4181_GPDATLREG_GPIO6
mdefine_line|#define VR4181_GPDATLREG_GPIO6   0x0040
DECL|macro|VR4181_GPDATLREG_GPIO7
mdefine_line|#define VR4181_GPDATLREG_GPIO7   0x0080
DECL|macro|VR4181_GPDATLREG_GPIO8
mdefine_line|#define VR4181_GPDATLREG_GPIO8   0x0100
DECL|macro|VR4181_GPDATLREG_GPIO9
mdefine_line|#define VR4181_GPDATLREG_GPIO9   0x0200
DECL|macro|VR4181_GPDATLREG_GPIO10
mdefine_line|#define VR4181_GPDATLREG_GPIO10  0x0400
DECL|macro|VR4181_GPDATLREG_GPIO11
mdefine_line|#define VR4181_GPDATLREG_GPIO11  0x0800
DECL|macro|VR4181_GPDATLREG_GPIO12
mdefine_line|#define VR4181_GPDATLREG_GPIO12  0x1000
DECL|macro|VR4181_GPDATLREG_GPIO13
mdefine_line|#define VR4181_GPDATLREG_GPIO13  0x2000
DECL|macro|VR4181_GPDATLREG_GPIO14
mdefine_line|#define VR4181_GPDATLREG_GPIO14  0x4000
DECL|macro|VR4181_GPDATLREG_GPIO15
mdefine_line|#define VR4181_GPDATLREG_GPIO15  0x8000
DECL|macro|VR4181_GPINTEN
mdefine_line|#define VR4181_GPINTEN&t;&t;__preg16(KSEG1 + 0x0B00030C)&t;/* GPIO Interrupt Enable Register (R/W) */
DECL|macro|VR4181_GPINTMSK
mdefine_line|#define VR4181_GPINTMSK&t;&t;__preg16(KSEG1 + 0x0B00030E)&t;/* GPIO Interrupt Mask Register (R/W) */
DECL|macro|VR4181_GPINTTYPH
mdefine_line|#define VR4181_GPINTTYPH&t;__preg16(KSEG1 + 0x0B000310)&t;/* GPIO Interrupt Type High Register (R/W) */
DECL|macro|VR4181_GPINTTYPL
mdefine_line|#define VR4181_GPINTTYPL&t;__preg16(KSEG1 + 0x0B000312)&t;/* GPIO Interrupt Type Low Register (R/W) */
DECL|macro|VR4181_GPINTSTAT
mdefine_line|#define VR4181_GPINTSTAT&t;__preg16(KSEG1 + 0x0B000314)&t;/* GPIO Interrupt Status Register (R/W) */
DECL|macro|VR4181_GPHIBSTH
mdefine_line|#define VR4181_GPHIBSTH&t;&t;__preg16(KSEG1 + 0x0B000316)&t;/* GPIO Hibernate Pin State High Register (R/W) */
DECL|macro|VR4181_GPHIBSTL
mdefine_line|#define VR4181_GPHIBSTL&t;&t;__preg16(KSEG1 + 0x0B000318)&t;/* GPIO Hibernate Pin State Low Register (R/W) */
DECL|macro|VR4181_GPSICTL
mdefine_line|#define VR4181_GPSICTL&t;&t;__preg16(KSEG1 + 0x0B00031A)&t;/* GPIO Serial Interface Control Register (R/W) */
DECL|macro|VR4181_KEYEN
mdefine_line|#define VR4181_KEYEN&t;&t;__preg16(KSEG1 + 0x0B00031C)&t;/* Keyboard Scan Pin Enable Register (R/W) */
DECL|macro|VR4181_PCS0STRA
mdefine_line|#define VR4181_PCS0STRA&t;&t;__preg16(KSEG1 + 0x0B000320)&t;/* Programmable Chip Select [0] Start Address Register (R/W) */
DECL|macro|VR4181_PCS0STPA
mdefine_line|#define VR4181_PCS0STPA&t;&t;__preg16(KSEG1 + 0x0B000322)&t;/* Programmable Chip Select [0] Stop Address Register (R/W) */
DECL|macro|VR4181_PCS0HIA
mdefine_line|#define VR4181_PCS0HIA&t;&t;__preg16(KSEG1 + 0x0B000324)&t;/* Programmable Chip Select [0] High Address Register (R/W) */
DECL|macro|VR4181_PCS1STRA
mdefine_line|#define VR4181_PCS1STRA&t;&t;__preg16(KSEG1 + 0x0B000326)&t;/* Programmable Chip Select [1] Start Address Register (R/W) */
DECL|macro|VR4181_PCS1STPA
mdefine_line|#define VR4181_PCS1STPA&t;&t;__preg16(KSEG1 + 0x0B000328)&t;/* Programmable Chip Select [1] Stop Address Register (R/W) */
DECL|macro|VR4181_PCS1HIA
mdefine_line|#define VR4181_PCS1HIA&t;&t;__preg16(KSEG1 + 0x0B00032A)&t;/* Programmable Chip Select [1] High Address Register (R/W) */
DECL|macro|VR4181_PCSMODE
mdefine_line|#define VR4181_PCSMODE&t;&t;__preg16(KSEG1 + 0x0B00032C)&t;/* Programmable Chip Select Mode Register (R/W) */
DECL|macro|VR4181_LCDGPMODE
mdefine_line|#define VR4181_LCDGPMODE&t;__preg16(KSEG1 + 0x0B00032E)&t;/* LCD General Purpose Mode Register (R/W) */
DECL|macro|VR4181_MISCREG0
mdefine_line|#define VR4181_MISCREG0&t;&t;__preg16(KSEG1 + 0x0B000330)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG1
mdefine_line|#define VR4181_MISCREG1&t;&t;__preg16(KSEG1 + 0x0B000332)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG2
mdefine_line|#define VR4181_MISCREG2&t;&t;__preg16(KSEG1 + 0x0B000334)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG3
mdefine_line|#define VR4181_MISCREG3&t;&t;__preg16(KSEG1 + 0x0B000336)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG4
mdefine_line|#define VR4181_MISCREG4&t;&t;__preg16(KSEG1 + 0x0B000338)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG5
mdefine_line|#define VR4181_MISCREG5&t;&t;__preg16(KSEG1 + 0x0B00033A)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG6
mdefine_line|#define VR4181_MISCREG6&t;&t;__preg16(KSEG1 + 0x0B00033C)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG7
mdefine_line|#define VR4181_MISCREG7&t;&t;__preg16(KSEG1 + 0x0B00033D)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG8
mdefine_line|#define VR4181_MISCREG8&t;&t;__preg16(KSEG1 + 0x0B000340)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG9
mdefine_line|#define VR4181_MISCREG9&t;&t;__preg16(KSEG1 + 0x0B000342)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG10
mdefine_line|#define VR4181_MISCREG10&t;__preg16(KSEG1 + 0x0B000344)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG11
mdefine_line|#define VR4181_MISCREG11&t;__preg16(KSEG1 + 0x0B000346)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG12
mdefine_line|#define VR4181_MISCREG12&t;__preg16(KSEG1 + 0x0B000348)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG13
mdefine_line|#define VR4181_MISCREG13&t;__preg16(KSEG1 + 0x0B00034A)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG14
mdefine_line|#define VR4181_MISCREG14&t;__preg16(KSEG1 + 0x0B00034C)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_MISCREG15
mdefine_line|#define VR4181_MISCREG15&t;__preg16(KSEG1 + 0x0B00034E)&t;/* Misc. R/W Battery Backed Registers for Non-Volatile Storage (R/W) */
DECL|macro|VR4181_SECIRQMASKL
mdefine_line|#define VR4181_SECIRQMASKL&t;VR4181_GPINTEN
singleline_comment|// No SECIRQMASKH for VR4181
singleline_comment|// Touch Panel Interface Unit (PIU)
DECL|macro|VR4181_PIUCNTREG
mdefine_line|#define VR4181_PIUCNTREG&t;__preg16(KSEG1 + 0x0B000122)&t;/* PIU Control register (R/W) */
DECL|macro|VR4181_PIUCNTREG_PIUSEQEN
mdefine_line|#define VR4181_PIUCNTREG_PIUSEQEN&t;0x0004
DECL|macro|VR4181_PIUCNTREG_PIUPWR
mdefine_line|#define VR4181_PIUCNTREG_PIUPWR&t;&t;0x0002
DECL|macro|VR4181_PIUCNTREG_PADRST
mdefine_line|#define VR4181_PIUCNTREG_PADRST&t;&t;0x0001
DECL|macro|VR4181_PIUINTREG
mdefine_line|#define VR4181_PIUINTREG&t;__preg16(KSEG1 + 0x0B000124)&t;/* PIU Interrupt cause register (R/W) */
DECL|macro|VR4181_PIUINTREG_OVP
mdefine_line|#define VR4181_PIUINTREG_OVP&t;&t;0x8000
DECL|macro|VR4181_PIUINTREG_PADCMD
mdefine_line|#define VR4181_PIUINTREG_PADCMD&t;&t;0x0040
DECL|macro|VR4181_PIUINTREG_PADADP
mdefine_line|#define VR4181_PIUINTREG_PADADP&t;&t;0x0020
DECL|macro|VR4181_PIUINTREG_PADPAGE1
mdefine_line|#define VR4181_PIUINTREG_PADPAGE1&t;0x0010
DECL|macro|VR4181_PIUINTREG_PADPAGE0
mdefine_line|#define VR4181_PIUINTREG_PADPAGE0&t;0x0008
DECL|macro|VR4181_PIUINTREG_PADDLOST
mdefine_line|#define VR4181_PIUINTREG_PADDLOST&t;0x0004
DECL|macro|VR4181_PIUINTREG_PENCHG
mdefine_line|#define VR4181_PIUINTREG_PENCHG&t;&t;0x0001
DECL|macro|VR4181_PIUSIVLREG
mdefine_line|#define VR4181_PIUSIVLREG&t;__preg16(KSEG1 + 0x0B000126)&t;/* PIU Data sampling interval register (R/W) */
DECL|macro|VR4181_PIUSTBLREG
mdefine_line|#define VR4181_PIUSTBLREG&t;__preg16(KSEG1 + 0x0B000128)&t;/* PIU A/D converter start delay register (R/W) */
DECL|macro|VR4181_PIUCMDREG
mdefine_line|#define VR4181_PIUCMDREG&t;__preg16(KSEG1 + 0x0B00012A)&t;/* PIU A/D command register (R/W) */
DECL|macro|VR4181_PIUASCNREG
mdefine_line|#define VR4181_PIUASCNREG&t;__preg16(KSEG1 + 0x0B000130)&t;/* PIU A/D port scan register (R/W) */
DECL|macro|VR4181_PIUAMSKREG
mdefine_line|#define VR4181_PIUAMSKREG&t;__preg16(KSEG1 + 0x0B000132)&t;/* PIU A/D scan mask register (R/W) */
DECL|macro|VR4181_PIUCIVLREG
mdefine_line|#define VR4181_PIUCIVLREG&t;__preg16(KSEG1 + 0x0B00013E)&t;/* PIU Check interval register (R) */
DECL|macro|VR4181_PIUPB00REG
mdefine_line|#define VR4181_PIUPB00REG&t;__preg16(KSEG1 + 0x0B0002A0)&t;/* PIU Page 0 Buffer 0 register (R/W) */
DECL|macro|VR4181_PIUPB01REG
mdefine_line|#define VR4181_PIUPB01REG&t;__preg16(KSEG1 + 0x0B0002A2)&t;/* PIU Page 0 Buffer 1 register (R/W) */
DECL|macro|VR4181_PIUPB02REG
mdefine_line|#define VR4181_PIUPB02REG&t;__preg16(KSEG1 + 0x0B0002A4)&t;/* PIU Page 0 Buffer 2 register (R/W) */
DECL|macro|VR4181_PIUPB03REG
mdefine_line|#define VR4181_PIUPB03REG&t;__preg16(KSEG1 + 0x0B0002A6)&t;/* PIU Page 0 Buffer 3 register (R/W) */
DECL|macro|VR4181_PIUPB10REG
mdefine_line|#define VR4181_PIUPB10REG&t;__preg16(KSEG1 + 0x0B0002A8)&t;/* PIU Page 1 Buffer 0 register (R/W) */
DECL|macro|VR4181_PIUPB11REG
mdefine_line|#define VR4181_PIUPB11REG&t;__preg16(KSEG1 + 0x0B0002AA)&t;/* PIU Page 1 Buffer 1 register (R/W) */
DECL|macro|VR4181_PIUPB12REG
mdefine_line|#define VR4181_PIUPB12REG&t;__preg16(KSEG1 + 0x0B0002AC)&t;/* PIU Page 1 Buffer 2 register (R/W) */
DECL|macro|VR4181_PIUPB13REG
mdefine_line|#define VR4181_PIUPB13REG&t;__preg16(KSEG1 + 0x0B0002AE)&t;/* PIU Page 1 Buffer 3 register (R/W) */
DECL|macro|VR4181_PIUAB0REG
mdefine_line|#define VR4181_PIUAB0REG&t;__preg16(KSEG1 + 0x0B0002B0)&t;/* PIU A/D scan Buffer 0 register (R/W) */
DECL|macro|VR4181_PIUAB1REG
mdefine_line|#define VR4181_PIUAB1REG&t;__preg16(KSEG1 + 0x0B0002B2)&t;/* PIU A/D scan Buffer 1 register (R/W) */
DECL|macro|VR4181_PIUAB2REG
mdefine_line|#define VR4181_PIUAB2REG&t;__preg16(KSEG1 + 0x0B0002B4)&t;/* PIU A/D scan Buffer 2 register (R/W) */
DECL|macro|VR4181_PIUAB3REG
mdefine_line|#define VR4181_PIUAB3REG&t;__preg16(KSEG1 + 0x0B0002B6)&t;/* PIU A/D scan Buffer 3 register (R/W) */
DECL|macro|VR4181_PIUPB04REG
mdefine_line|#define VR4181_PIUPB04REG&t;__preg16(KSEG1 + 0x0B0002BC)&t;/* PIU Page 0 Buffer 4 register (R/W) */
DECL|macro|VR4181_PIUPB14REG
mdefine_line|#define VR4181_PIUPB14REG&t;__preg16(KSEG1 + 0x0B0002BE)&t;/* PIU Page 1 Buffer 4 register (R/W) */
singleline_comment|// Audio Interface Unit (AIU)
DECL|macro|VR4181_SODATREG
mdefine_line|#define VR4181_SODATREG&t;&t;__preg16(KSEG1 + 0x0B000166)&t;/* Speaker Output Data Register (R/W) */
DECL|macro|VR4181_SCNTREG
mdefine_line|#define VR4181_SCNTREG&t;&t;__preg16(KSEG1 + 0x0B000168)&t;/* Speaker Output Control Register (R/W) */
DECL|macro|VR4181_MIDATREG
mdefine_line|#define VR4181_MIDATREG&t;&t;__preg16(KSEG1 + 0x0B000170)&t;/* Mike Input Data Register (R/W) */
DECL|macro|VR4181_MCNTREG
mdefine_line|#define VR4181_MCNTREG&t;&t;__preg16(KSEG1 + 0x0B000172)&t;/* Mike Input Control Register (R/W) */
DECL|macro|VR4181_DVALIDREG
mdefine_line|#define VR4181_DVALIDREG&t;__preg16(KSEG1 + 0x0B000178)&t;/* Data Valid Register (R/W) */
DECL|macro|VR4181_SEQREG
mdefine_line|#define VR4181_SEQREG&t;&t;__preg16(KSEG1 + 0x0B00017A)&t;/* Sequential Register (R/W) */
DECL|macro|VR4181_INTREG
mdefine_line|#define VR4181_INTREG&t;&t;__preg16(KSEG1 + 0x0B00017C)&t;/* Interrupt Register (R/W) */
DECL|macro|VR4181_SDMADATREG
mdefine_line|#define VR4181_SDMADATREG&t;__preg16(KSEG1 + 0x0B000160)&t;/* Speaker DMA Data Register (R/W) */
DECL|macro|VR4181_MDMADATREG
mdefine_line|#define VR4181_MDMADATREG&t;__preg16(KSEG1 + 0x0B000162)&t;/* Microphone DMA Data Register (R/W) */
DECL|macro|VR4181_DAVREF_SETUP
mdefine_line|#define VR4181_DAVREF_SETUP&t;__preg16(KSEG1 + 0x0B000164)&t;/* DAC Vref setup register (R/W) */
DECL|macro|VR4181_SCNVC_END
mdefine_line|#define VR4181_SCNVC_END&t;__preg16(KSEG1 + 0x0B00016E)&t;/* Speaker sample rate control (R/W) */
DECL|macro|VR4181_MIDATREG
mdefine_line|#define VR4181_MIDATREG&t;&t;__preg16(KSEG1 + 0x0B000170)&t;/* Microphone Input Data Register (R/W) */
DECL|macro|VR4181_MCNTREG
mdefine_line|#define VR4181_MCNTREG&t;&t;__preg16(KSEG1 + 0x0B000172)&t;/* Microphone Input Control Register (R/W) */
DECL|macro|VR4181_MCNVC_END
mdefine_line|#define VR4181_MCNVC_END&t;__preg16(KSEG1 + 0x0B00017E)&t;/* Microphone sample rate control (R/W) */
singleline_comment|// Keyboard Interface Unit (KIU)
DECL|macro|VR4181_KIUDAT0
mdefine_line|#define VR4181_KIUDAT0&t;&t;__preg16(KSEG1 + 0x0B000180)&t;/* KIU Data0 Register (R/W) */
DECL|macro|VR4181_KIUDAT1
mdefine_line|#define VR4181_KIUDAT1&t;&t;__preg16(KSEG1 + 0x0B000182)&t;/* KIU Data1 Register (R/W) */
DECL|macro|VR4181_KIUDAT2
mdefine_line|#define VR4181_KIUDAT2&t;&t;__preg16(KSEG1 + 0x0B000184)&t;/* KIU Data2 Register (R/W) */
DECL|macro|VR4181_KIUDAT3
mdefine_line|#define VR4181_KIUDAT3&t;&t;__preg16(KSEG1 + 0x0B000186)&t;/* KIU Data3 Register (R/W) */
DECL|macro|VR4181_KIUDAT4
mdefine_line|#define VR4181_KIUDAT4&t;&t;__preg16(KSEG1 + 0x0B000188)&t;/* KIU Data4 Register (R/W) */
DECL|macro|VR4181_KIUDAT5
mdefine_line|#define VR4181_KIUDAT5&t;&t;__preg16(KSEG1 + 0x0B00018A)&t;/* KIU Data5 Register (R/W) */
DECL|macro|VR4181_KIUSCANREP
mdefine_line|#define VR4181_KIUSCANREP&t;__preg16(KSEG1 + 0x0B000190)&t;/* KIU Scan/Repeat Register (R/W) */
DECL|macro|VR4181_KIUSCANREP_KEYEN
mdefine_line|#define VR4181_KIUSCANREP_KEYEN      0x8000
DECL|macro|VR4181_KIUSCANREP_SCANSTP
mdefine_line|#define VR4181_KIUSCANREP_SCANSTP    0x0008
DECL|macro|VR4181_KIUSCANREP_SCANSTART
mdefine_line|#define VR4181_KIUSCANREP_SCANSTART  0x0004
DECL|macro|VR4181_KIUSCANREP_ATSTP
mdefine_line|#define VR4181_KIUSCANREP_ATSTP      0x0002
DECL|macro|VR4181_KIUSCANREP_ATSCAN
mdefine_line|#define VR4181_KIUSCANREP_ATSCAN     0x0001
DECL|macro|VR4181_KIUSCANS
mdefine_line|#define VR4181_KIUSCANS&t;&t;__preg16(KSEG1 + 0x0B000192)&t;/* KIU Scan Status Register (R) */
DECL|macro|VR4181_KIUWKS
mdefine_line|#define VR4181_KIUWKS&t;&t;__preg16(KSEG1 + 0x0B000194)&t;/* KIU Wait Keyscan Stable Register (R/W) */
DECL|macro|VR4181_KIUWKI
mdefine_line|#define VR4181_KIUWKI&t;&t;__preg16(KSEG1 + 0x0B000196)&t;/* KIU Wait Keyscan Interval Register (R/W) */
DECL|macro|VR4181_KIUINT
mdefine_line|#define VR4181_KIUINT&t;&t;__preg16(KSEG1 + 0x0B000198)&t;/* KIU Interrupt Register (R/W) */
DECL|macro|VR4181_KIUINT_KDATLOST
mdefine_line|#define VR4181_KIUINT_KDATLOST       0x0004
DECL|macro|VR4181_KIUINT_KDATRDY
mdefine_line|#define VR4181_KIUINT_KDATRDY        0x0002
DECL|macro|VR4181_KIUINT_SCANINT
mdefine_line|#define VR4181_KIUINT_SCANINT        0x0001
DECL|macro|VR4181_KIUDAT6
mdefine_line|#define VR4181_KIUDAT6&t;&t;__preg16(KSEG1 + 0x0B00018C)&t;/* Scan Line 6 Key Data Register (R) */
DECL|macro|VR4181_KIUDAT7
mdefine_line|#define VR4181_KIUDAT7&t;&t;__preg16(KSEG1 + 0x0B00018E)&t;/* Scan Line 7 Key Data Register (R) */
singleline_comment|// CompactFlash Controller
DECL|macro|VR4181_PCCARDINDEX
mdefine_line|#define VR4181_PCCARDINDEX&t;__preg8(KSEG1 + 0x0B0008E0)&t;/* PC Card Controller Index Register */
DECL|macro|VR4181_PCCARDDATA
mdefine_line|#define VR4181_PCCARDDATA&t;__preg8(KSEG1 + 0x0B0008E1)&t;/* PC Card Controller Data Register */
DECL|macro|VR4181_INTSTATREG
mdefine_line|#define VR4181_INTSTATREG&t;__preg16(KSEG1 + 0x0B0008F8)&t;/* Interrupt Status Register (R/W) */
DECL|macro|VR4181_INTMSKREG
mdefine_line|#define VR4181_INTMSKREG&t;__preg16(KSEG1 + 0x0B0008FA)&t;/* Interrupt Mask Register (R/W) */
DECL|macro|VR4181_CFG_REG_1
mdefine_line|#define VR4181_CFG_REG_1&t;__preg16(KSEG1 + 0x0B0008FE)&t;/* Configuration Register 1 */
singleline_comment|// LED Control Unit (LED)
DECL|macro|VR4181_LEDHTSREG
mdefine_line|#define VR4181_LEDHTSREG&t;__preg16(KSEG1 + 0x0B000240)&t;/* LED H Time Set register (R/W) */
DECL|macro|VR4181_LEDLTSREG
mdefine_line|#define VR4181_LEDLTSREG&t;__preg16(KSEG1 + 0x0B000242)&t;/* LED L Time Set register (R/W) */
DECL|macro|VR4181_LEDCNTREG
mdefine_line|#define VR4181_LEDCNTREG&t;__preg16(KSEG1 + 0x0B000248)&t;/* LED Control register (R/W) */
DECL|macro|VR4181_LEDASTCREG
mdefine_line|#define VR4181_LEDASTCREG&t;__preg16(KSEG1 + 0x0B00024A)&t;/* LED Auto Stop Time Count register (R/W) */
DECL|macro|VR4181_LEDINTREG
mdefine_line|#define VR4181_LEDINTREG&t;__preg16(KSEG1 + 0x0B00024C)&t;/* LED Interrupt register (R/W) */
singleline_comment|// Serial Interface Unit (SIU / SIU1 and SIU2)
DECL|macro|VR4181_SIURB
mdefine_line|#define VR4181_SIURB&t;&t;__preg8(KSEG1 + 0x0C000010)&t;/* Receiver Buffer Register (Read) DLAB = 0 (R) */
DECL|macro|VR4181_SIUTH
mdefine_line|#define VR4181_SIUTH&t;&t;__preg8(KSEG1 + 0x0C000010)&t;/* Transmitter Holding Register (Write) DLAB = 0 (W) */
DECL|macro|VR4181_SIUDLL
mdefine_line|#define VR4181_SIUDLL&t;&t;__preg8(KSEG1 + 0x0C000010)&t;/* Divisor Latch (Least Significant Byte) DLAB = 1 (R/W) */
DECL|macro|VR4181_SIUIE
mdefine_line|#define VR4181_SIUIE&t;&t;__preg8(KSEG1 + 0x0C000011)&t;/* Interrupt Enable DLAB = 0 (R/W) */
DECL|macro|VR4181_SIUDLM
mdefine_line|#define VR4181_SIUDLM&t;&t;__preg8(KSEG1 + 0x0C000011)&t;/* Divisor Latch (Most Significant Byte) DLAB = 1 (R/W) */
DECL|macro|VR4181_SIUIID
mdefine_line|#define VR4181_SIUIID&t;&t;__preg8(KSEG1 + 0x0C000012)&t;/* Interrupt Identification Register (Read) (R) */
DECL|macro|VR4181_SIUFC
mdefine_line|#define VR4181_SIUFC&t;&t;__preg8(KSEG1 + 0x0C000012)&t;/* FIFO Control Register (Write) (W) */
DECL|macro|VR4181_SIULC
mdefine_line|#define VR4181_SIULC&t;&t;__preg8(KSEG1 + 0x0C000013)&t;/* Line Control Register (R/W) */
DECL|macro|VR4181_SIUMC
mdefine_line|#define VR4181_SIUMC&t;&t;__preg8(KSEG1 + 0x0C000014)&t;/* MODEM Control Register (R/W) */
DECL|macro|VR4181_SIULS
mdefine_line|#define VR4181_SIULS&t;&t;__preg8(KSEG1 + 0x0C000015)&t;/* Line Status Register (R/W) */
DECL|macro|VR4181_SIUMS
mdefine_line|#define VR4181_SIUMS&t;&t;__preg8(KSEG1 + 0x0C000016)&t;/* MODEM Status Register (R/W) */
DECL|macro|VR4181_SIUSC
mdefine_line|#define VR4181_SIUSC&t;&t;__preg8(KSEG1 + 0x0C000017)&t;/* Scratch Register (R/W) */
DECL|macro|VR4181_SIURESET
mdefine_line|#define VR4181_SIURESET&t;&t;__preg8(KSEG1 + 0x0C000019)&t;/* SIU Reset Register (R/W) */
DECL|macro|VR4181_SIUACTMSK
mdefine_line|#define VR4181_SIUACTMSK&t;__preg8(KSEG1 + 0x0C00001C)&t;/* SIU Activity Mask (R/W) */
DECL|macro|VR4181_SIUACTTMR
mdefine_line|#define VR4181_SIUACTTMR&t;__preg8(KSEG1 + 0x0C00001E)&t;/* SIU Activity Timer (R/W) */
DECL|macro|VR4181_SIURB_2
mdefine_line|#define VR4181_SIURB_2&t;&t;__preg8(KSEG1 + 0x0C000000)&t;/* Receive Buffer Register (Read) (R) */
DECL|macro|VR4181_SIUTH_2
mdefine_line|#define VR4181_SIUTH_2&t;&t;__preg8(KSEG1 + 0x0C000000)&t;/* Transmitter Holding Register (Write) (W) */
DECL|macro|VR4181_SIUDLL_2
mdefine_line|#define VR4181_SIUDLL_2&t;&t;__preg8(KSEG1 + 0x0C000000)&t;/* Divisor Latch (Least Significant Byte) (R/W) */
DECL|macro|VR4181_SIUIE_2
mdefine_line|#define VR4181_SIUIE_2&t;&t;__preg8(KSEG1 + 0x0C000001)&t;/* Interrupt Enable (DLAB = 0) (R/W) */
DECL|macro|VR4181_SIUDLM_2
mdefine_line|#define VR4181_SIUDLM_2&t;&t;__preg8(KSEG1 + 0x0C000001)&t;/* Divisor Latch (Most Significant Byte) (DLAB = 1) (R/W) */
DECL|macro|VR4181_SIUIID_2
mdefine_line|#define VR4181_SIUIID_2&t;&t;__preg8(KSEG1 + 0x0C000002)&t;/* Interrupt Identification Register (Read) (R) */
DECL|macro|VR4181_SIUFC_2
mdefine_line|#define VR4181_SIUFC_2&t;&t;__preg8(KSEG1 + 0x0C000002)&t;/* FIFO Control Register (Write) (W) */
DECL|macro|VR4181_SIULC_2
mdefine_line|#define VR4181_SIULC_2&t;&t;__preg8(KSEG1 + 0x0C000003)&t;/* Line Control Register (R/W) */
DECL|macro|VR4181_SIUMC_2
mdefine_line|#define VR4181_SIUMC_2&t;&t;__preg8(KSEG1 + 0x0C000004)&t;/* Modem Control Register (R/W) */
DECL|macro|VR4181_SIULS_2
mdefine_line|#define VR4181_SIULS_2&t;&t;__preg8(KSEG1 + 0x0C000005)&t;/* Line Status Register (R/W) */
DECL|macro|VR4181_SIUMS_2
mdefine_line|#define VR4181_SIUMS_2&t;&t;__preg8(KSEG1 + 0x0C000006)&t;/* Modem Status Register (R/W) */
DECL|macro|VR4181_SIUSC_2
mdefine_line|#define VR4181_SIUSC_2&t;&t;__preg8(KSEG1 + 0x0C000007)&t;/* Scratch Register (R/W) */
DECL|macro|VR4181_SIUIRSEL_2
mdefine_line|#define VR4181_SIUIRSEL_2&t;__preg8(KSEG1 + 0x0C000008)&t;/* SIU IrDA Selectot (R/W) */
DECL|macro|VR4181_SIURESET_2
mdefine_line|#define VR4181_SIURESET_2&t;__preg8(KSEG1 + 0x0C000009)&t;/* SIU Reset Register (R/W) */
DECL|macro|VR4181_SIUCSEL_2
mdefine_line|#define VR4181_SIUCSEL_2&t;__preg8(KSEG1 + 0x0C00000A)&t;/* IrDA Echo-back Control (R/W) */
DECL|macro|VR4181_SIUACTMSK_2
mdefine_line|#define VR4181_SIUACTMSK_2&t;__preg8(KSEG1 + 0x0C00000C)&t;/* SIU Activity Mask Register (R/W) */
DECL|macro|VR4181_SIUACTTMR_2
mdefine_line|#define VR4181_SIUACTTMR_2&t;__preg8(KSEG1 + 0x0C00000E)&t;/* SIU Activity Timer Register (R/W) */
singleline_comment|// USB Module
DECL|macro|VR4181_USBINFIFO
mdefine_line|#define VR4181_USBINFIFO&t;__preg16(KSEG1 + 0x0B000780)&t;/* USB Bulk Input FIFO (Bulk In End Point) (W) */
DECL|macro|VR4181_USBOUTFIFO
mdefine_line|#define VR4181_USBOUTFIFO&t;__preg16(KSEG1 + 0x0B000782)&t;/* USB Bulk Output FIFO (Bulk Out End Point) (R) */
DECL|macro|VR4181_USBCTLFIFO
mdefine_line|#define VR4181_USBCTLFIFO&t;__preg16(KSEG1 + 0x0B000784)&t;/* USB Control FIFO (Control End Point) (W) */
DECL|macro|VR4181_USBSTAT
mdefine_line|#define VR4181_USBSTAT&t;&t;__preg16(KSEG1 + 0x0B000786)&t;/* Interrupt Status Register (R/W) */
DECL|macro|VR4181_USBINTMSK
mdefine_line|#define VR4181_USBINTMSK&t;__preg16(KSEG1 + 0x0B000788)&t;/* Interrupt Mask Register (R/W) */
DECL|macro|VR4181_USBCTLREG
mdefine_line|#define VR4181_USBCTLREG&t;__preg16(KSEG1 + 0x0B00078A)&t;/* Control Register (R/W) */
DECL|macro|VR4181_USBSTPREG
mdefine_line|#define VR4181_USBSTPREG&t;__preg16(KSEG1 + 0x0B00078C)&t;/* USB Transfer Stop Register (R/W) */
singleline_comment|// LCD Controller
DECL|macro|VR4181_HRTOTALREG
mdefine_line|#define VR4181_HRTOTALREG&t;__preg16(KSEG1 + 0x0A000400)&t;/* Horizontal total Register (R/W) */
DECL|macro|VR4181_HRVISIBREG
mdefine_line|#define VR4181_HRVISIBREG&t;__preg16(KSEG1 + 0x0A000402)&t;/* Horizontal Visible Register (R/W) */
DECL|macro|VR4181_LDCLKSTREG
mdefine_line|#define VR4181_LDCLKSTREG&t;__preg16(KSEG1 + 0x0A000404)&t;/* Load clock start Register (R/W) */
DECL|macro|VR4181_LDCLKNDREG
mdefine_line|#define VR4181_LDCLKNDREG&t;__preg16(KSEG1 + 0x0A000406)&t;/* Load clock end Register (R/W) */
DECL|macro|VR4181_VRTOTALREG
mdefine_line|#define VR4181_VRTOTALREG&t;__preg16(KSEG1 + 0x0A000408)&t;/* Vertical Total Register (R/W) */
DECL|macro|VR4181_VRVISIBREG
mdefine_line|#define VR4181_VRVISIBREG&t;__preg16(KSEG1 + 0x0A00040A)&t;/* Vertical Visible Register (R/W) */
DECL|macro|VR4181_FVSTARTREG
mdefine_line|#define VR4181_FVSTARTREG&t;__preg16(KSEG1 + 0x0A00040C)&t;/* FLM vertical start Register (R/W) */
DECL|macro|VR4181_FVENDREG
mdefine_line|#define VR4181_FVENDREG&t;&t;__preg16(KSEG1 + 0x0A00040E)&t;/* FLM vertical end Register (R/W) */
DECL|macro|VR4181_LCDCTRLREG
mdefine_line|#define VR4181_LCDCTRLREG&t;__preg16(KSEG1 + 0x0A000410)&t;/* LCD control Register (R/W) */
DECL|macro|VR4181_LCDINRQREG
mdefine_line|#define VR4181_LCDINRQREG&t;__preg16(KSEG1 + 0x0A000412)&t;/* LCD Interrupt request Register (R/W) */
DECL|macro|VR4181_LCDCFGREG0
mdefine_line|#define VR4181_LCDCFGREG0&t;__preg16(KSEG1 + 0x0A000414)&t;/* LCD Configuration Register 0 (R/W) */
DECL|macro|VR4181_LCDCFGREG1
mdefine_line|#define VR4181_LCDCFGREG1&t;__preg16(KSEG1 + 0x0A000416)&t;/* LCD Configuration Register 1 (R/W) */
DECL|macro|VR4181_FBSTAD1REG
mdefine_line|#define VR4181_FBSTAD1REG&t;__preg16(KSEG1 + 0x0A000418)&t;/* Frame Buffer Start Address 1 Register (R/W) */
DECL|macro|VR4181_FBSTAD2REG
mdefine_line|#define VR4181_FBSTAD2REG&t;__preg16(KSEG1 + 0x0A00041A)&t;/* Frame Buffer Start Address 2 Register (R/W) */
DECL|macro|VR4181_FBNDAD1REG
mdefine_line|#define VR4181_FBNDAD1REG&t;__preg16(KSEG1 + 0x0A000420)&t;/* Frame Buffer End Address 1 Register (R/W) */
DECL|macro|VR4181_FBNDAD2REG
mdefine_line|#define VR4181_FBNDAD2REG&t;__preg16(KSEG1 + 0x0A000422)&t;/* Frame Buffer End Address 2 register (R/W) */
DECL|macro|VR4181_FHSTARTREG
mdefine_line|#define VR4181_FHSTARTREG&t;__preg16(KSEG1 + 0x0A000424)&t;/* FLM horizontal Start Register (R/W) */
DECL|macro|VR4181_FHENDREG
mdefine_line|#define VR4181_FHENDREG&t;&t;__preg16(KSEG1 + 0x0A000426)&t;/* FLM horizontal End Register (R/W) */
DECL|macro|VR4181_PWRCONREG1
mdefine_line|#define VR4181_PWRCONREG1&t;__preg16(KSEG1 + 0x0A000430)&t;/* Power Control register 1 (R/W) */
DECL|macro|VR4181_PWRCONREG2
mdefine_line|#define VR4181_PWRCONREG2&t;__preg16(KSEG1 + 0x0A000432)&t;/* Power Control register 2 (R/W) */
DECL|macro|VR4181_LCDIMSKREG
mdefine_line|#define VR4181_LCDIMSKREG&t;__preg16(KSEG1 + 0x0A000434)&t;/* LCD Interrupt Mask register (R/W) */
DECL|macro|VR4181_CPINDCTREG
mdefine_line|#define VR4181_CPINDCTREG&t;__preg16(KSEG1 + 0x0A00047E)&t;/* Color palette Index and control Register (R/W) */
DECL|macro|VR4181_CPALDATREG
mdefine_line|#define VR4181_CPALDATREG&t;__preg32(KSEG1 + 0x0A000480)&t;/* Color palette data register (32bits Register) (R/W) */
singleline_comment|// physical address spaces
DECL|macro|VR4181_LCD
mdefine_line|#define VR4181_LCD             0x0a000000
DECL|macro|VR4181_INTERNAL_IO_2
mdefine_line|#define VR4181_INTERNAL_IO_2   0x0b000000
DECL|macro|VR4181_INTERNAL_IO_1
mdefine_line|#define VR4181_INTERNAL_IO_1   0x0c000000
DECL|macro|VR4181_ISA_MEM
mdefine_line|#define VR4181_ISA_MEM         0x10000000
DECL|macro|VR4181_ISA_IO
mdefine_line|#define VR4181_ISA_IO          0x14000000
DECL|macro|VR4181_ROM
mdefine_line|#define VR4181_ROM             0x18000000
singleline_comment|// This is the base address for IO port decoding to which the 16 bit IO port address
singleline_comment|// is added.  Defining it to 0 will usually cause a kernel oops any time port IO is
singleline_comment|// attempted, which can be handy for turning up parts of the kernel that make
singleline_comment|// incorrect architecture assumptions (by assuming that everything acts like a PC),
singleline_comment|// but we need it correctly defined to use the PCMCIA/CF controller:
DECL|macro|VR4181_PORT_BASE
mdefine_line|#define VR4181_PORT_BASE&t;(KSEG1 + VR4181_ISA_IO)
DECL|macro|VR4181_ISAMEM_BASE
mdefine_line|#define VR4181_ISAMEM_BASE&t;(KSEG1 + VR4181_ISA_MEM)
macro_line|#endif /* __ASM_VR4181_VR4181_H */
eof
