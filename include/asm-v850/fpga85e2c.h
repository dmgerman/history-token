multiline_comment|/*&n; * include/asm-v850/fpga85e2c.h -- Machine-dependent defs for&n; *&t;FPGA implementation of V850E2/NA85E2C&n; *&n; *  Copyright (C) 2002,03  NEC Electronics Corporation&n; *  Copyright (C) 2002,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_FPGA85E2C_H__
DECL|macro|__V850_FPGA85E2C_H__
mdefine_line|#define __V850_FPGA85E2C_H__
macro_line|#include &lt;asm/clinkage.h&gt;
DECL|macro|CPU_ARCH
mdefine_line|#define CPU_ARCH &t;&quot;v850e2&quot;
DECL|macro|CPU_MODEL
mdefine_line|#define CPU_MODEL&t;&quot;v850e2/fpga85e2c&quot;
DECL|macro|CPU_MODEL_LONG
mdefine_line|#define CPU_MODEL_LONG&t;&quot;NEC V850E2/NA85E2C&quot;
DECL|macro|PLATFORM
mdefine_line|#define PLATFORM&t;&quot;fpga85e2c&quot;
DECL|macro|PLATFORM_LONG
mdefine_line|#define PLATFORM_LONG&t;&quot;NA85E2C FPGA implementation&quot;
multiline_comment|/* `external ram&squot;.  */
DECL|macro|ERAM_ADDR
mdefine_line|#define ERAM_ADDR&t;&t;0
DECL|macro|ERAM_SIZE
mdefine_line|#define ERAM_SIZE&t;&t;0x00100000 /* 1MB */
multiline_comment|/* FPGA specific control registers.  */
multiline_comment|/* Writing a non-zero value to FLGREG(0) will signal the controlling CPU&n;   to stop execution.  */
DECL|macro|FLGREG_ADDR
mdefine_line|#define FLGREG_ADDR(n)&t;&t;(0xFFE80100 + 2*(n))
DECL|macro|FLGREG
mdefine_line|#define FLGREG(n)&t;&t;(*(volatile unsigned char *)FLGREG_ADDR (n))
DECL|macro|FLGREG_NUM
mdefine_line|#define FLGREG_NUM&t;&t;2
DECL|macro|CSDEV_ADDR
mdefine_line|#define CSDEV_ADDR(n)&t;&t;(0xFFE80110 + 2*(n))
DECL|macro|CSDEV
mdefine_line|#define CSDEV(n)&t;&t;(*(volatile unsigned char *)CSDEV_ADDR (n))
multiline_comment|/* The BSC register controls bus-sizing.  Each memory area CSn uses a pair&n;   of bits N*2 and N*2+1, where 00 means an 8-bit bus size, 01 16-bit, and&n;   10 32-bit.  */
DECL|macro|BSC_ADDR
mdefine_line|#define BSC_ADDR&t;&t;0xFFFFF066
DECL|macro|BSC
mdefine_line|#define BSC&t;&t;&t;(*(volatile unsigned short *)BSC_ADDR)
DECL|macro|DWC_ADDR
mdefine_line|#define DWC_ADDR(n)&t;&t;(0xFFFFF484 + 2*(n))
DECL|macro|DWC
mdefine_line|#define DWC(n)&t;&t;&t;(*(volatile unsigned short *)DWC_ADDR (n))
DECL|macro|ASC_ADDR
mdefine_line|#define ASC_ADDR&t;&t;0xFFFFF48A
DECL|macro|ASC
mdefine_line|#define ASC&t;&t;&t;(*(volatile unsigned short *)ASC_ADDR)
DECL|macro|BTSC_ADDR
mdefine_line|#define BTSC_ADDR&t;&t;0xFFFFF070
DECL|macro|BTSC
mdefine_line|#define BTSC&t;&t;&t;(*(volatile unsigned short *)BTSC_ADDR)
DECL|macro|BHC_ADDR
mdefine_line|#define BHC_ADDR&t;&t;0xFFFFF06A
DECL|macro|BHC
mdefine_line|#define BHC&t;&t;&t;(*(volatile unsigned short *)BHC_ADDR)
multiline_comment|/* NB85E-style interrupt system.  */
macro_line|#include &lt;asm/nb85e_intc.h&gt;
multiline_comment|/* Timer interrupts 0-3, interrupt at intervals from CLK/4096 to CLK/16384.  */
DECL|macro|IRQ_RPU
mdefine_line|#define IRQ_RPU(n)&t;&t;(60 + (n))
DECL|macro|IRQ_RPU_NUM
mdefine_line|#define IRQ_RPU_NUM&t;&t;4
multiline_comment|/* For &lt;asm/irq.h&gt; */
DECL|macro|NUM_CPU_IRQS
mdefine_line|#define NUM_CPU_IRQS&t;&t;64
multiline_comment|/* General-purpose timer.  */
multiline_comment|/* control/status register (can only be read/written via bit insns) */
DECL|macro|RPU_GTMC_ADDR
mdefine_line|#define RPU_GTMC_ADDR&t;&t;0xFFFFFB00
DECL|macro|RPU_GTMC
mdefine_line|#define RPU_GTMC&t;&t;(*(volatile unsigned char *)RPU_GTMC_ADDR)
DECL|macro|RPU_GTMC_CE_BIT
mdefine_line|#define RPU_GTMC_CE_BIT&t;&t;7 /* clock enable (control) */
DECL|macro|RPU_GTMC_OV_BIT
mdefine_line|#define RPU_GTMC_OV_BIT&t;&t;6 /* overflow (status) */
DECL|macro|RPU_GTMC_CLK_BIT
mdefine_line|#define RPU_GTMC_CLK_BIT&t;1 /* 0 = .5 MHz CLK, 1 = 1 Mhz (control) */
multiline_comment|/* 32-bit count (8 least-significant bits are always zero).  */
DECL|macro|RPU_GTM_ADDR
mdefine_line|#define RPU_GTM_ADDR&t;&t;0xFFFFFB28
DECL|macro|RPU_GTM
mdefine_line|#define RPU_GTM&t;&t;&t;(*(volatile unsigned long *)RPU_GTMC_ADDR)
multiline_comment|/* For &lt;asm/page.h&gt; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;ERAM_ADDR /* minimum allocatable address */
multiline_comment|/* For &lt;asm/entry.h&gt; */
multiline_comment|/* `R0 RAM&squot;, used for a few miscellaneous variables that must be accessible&n;   using a load instruction relative to R0.  The FPGA implementation&n;   actually has no on-chip RAM, so we use part of main ram just after the&n;   interrupt vectors.  */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|R0_RAM_ADDR
mdefine_line|#define R0_RAM_ADDR&t;&t;lo(C_SYMBOL_NAME(_r0_ram))
macro_line|#else
r_extern
r_char
id|_r0_ram
suffix:semicolon
DECL|macro|R0_RAM_ADDR
mdefine_line|#define R0_RAM_ADDR&t;&t;((unsigned long)&amp;_r0_ram);
macro_line|#endif
multiline_comment|/* For &lt;asm/param.h&gt; */
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ&t;&t;&t;122 /* actually, 8.192ms ticks =~ 122.07 */
macro_line|#endif
macro_line|#endif /* __V850_FPGA85E2C_H__ */
eof
