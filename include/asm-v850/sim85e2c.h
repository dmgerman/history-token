multiline_comment|/*&n; * include/asm-v850/sim85e2c.h -- Machine-dependent defs for&n; *&t;V850E2 RTL simulator&n; *&n; *  Copyright (C) 2002  NEC Corporation&n; *  Copyright (C) 2002  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_SIM85E2C_H__
DECL|macro|__V850_SIM85E2C_H__
mdefine_line|#define __V850_SIM85E2C_H__
DECL|macro|CPU_ARCH
mdefine_line|#define CPU_ARCH&t;&t;&quot;v850e2&quot;
DECL|macro|CPU_MODEL
mdefine_line|#define CPU_MODEL&t;&t;&quot;sim85e2c simulator&quot;
multiline_comment|/* Various memory areas supported by the simulator.&n;   These should match the corresponding definitions in the linker script.  */
multiline_comment|/* `instruction RAM&squot;; instruction fetches are much faster from IRAM than&n;   from DRAM.  */
DECL|macro|IRAM_ADDR
mdefine_line|#define IRAM_ADDR&t;&t;0
DECL|macro|IRAM_SIZE
mdefine_line|#define IRAM_SIZE&t;&t;0x00100000 /* 1MB */
multiline_comment|/* `data RAM&squot;, below and contiguous with the I/O space.&n;   Data fetches are much faster from DRAM than from IRAM.  */
DECL|macro|DRAM_ADDR
mdefine_line|#define DRAM_ADDR&t;&t;0xfff00000
DECL|macro|DRAM_SIZE
mdefine_line|#define DRAM_SIZE&t;&t;0x000ff000 /* 1020KB */
multiline_comment|/* `external ram&squot;.  Unlike the above RAM areas, this memory is cached,&n;   so both instruction and data fetches should be (mostly) fast --&n;   however, currently only write-through caching is supported, so writes&n;   to ERAM will be slow.  */
DECL|macro|ERAM_ADDR
mdefine_line|#define ERAM_ADDR&t;&t;0x00100000
DECL|macro|ERAM_SIZE
mdefine_line|#define ERAM_SIZE&t;&t;0x07f00000 /* 127MB (max) */
multiline_comment|/* CPU core control registers; these should be expanded and moved into&n;   separate header files when we support some other processors based on&n;   the same E2 core.  */
multiline_comment|/* Bus Transaction Control Register */
DECL|macro|NA85E2C_CACHE_BTSC_ADDR
mdefine_line|#define NA85E2C_CACHE_BTSC_ADDR&t;0xfffff070
DECL|macro|NA85E2C_CACHE_BTSC
mdefine_line|#define NA85E2C_CACHE_BTSC &t;(*(volatile unsigned short *)NA85E2C_CACHE_BTSC_ADDR)
DECL|macro|NA85E2C_CACHE_BTSC_ICM
mdefine_line|#define NA85E2C_CACHE_BTSC_ICM&t;0x1 /* icache enable */
DECL|macro|NA85E2C_CACHE_BTSC_DCM0
mdefine_line|#define NA85E2C_CACHE_BTSC_DCM0&t;0x4 /* dcache enable, bit 0 */
DECL|macro|NA85E2C_CACHE_BTSC_DCM1
mdefine_line|#define NA85E2C_CACHE_BTSC_DCM1&t;0x8 /* dcache enable, bit 1 */
multiline_comment|/* Cache Configuration Register */
DECL|macro|NA85E2C_BUSM_BHC_ADDR
mdefine_line|#define NA85E2C_BUSM_BHC_ADDR&t;0xfffff06a
DECL|macro|NA85E2C_BUSM_BHC
mdefine_line|#define NA85E2C_BUSM_BHC&t;(*(volatile unsigned short *)NA85E2C_BUSM_BHC_ADDR)
multiline_comment|/* Simulator specific control registers.  */
multiline_comment|/* NOTHAL controls whether the simulator will stop at a `halt&squot; insn.  */
DECL|macro|NOTHAL_ADDR
mdefine_line|#define NOTHAL_ADDR&t;&t;0xffffff22
DECL|macro|NOTHAL
mdefine_line|#define NOTHAL&t;&t;&t;(*(volatile unsigned char *)NOTHAL_ADDR)
multiline_comment|/* The simulator will stop N cycles after N is written to SIMFIN.  */
DECL|macro|SIMFIN_ADDR
mdefine_line|#define SIMFIN_ADDR&t;&t;0xffffff24
DECL|macro|SIMFIN
mdefine_line|#define SIMFIN&t;&t;&t;(*(volatile unsigned short *)SIMFIN_ADDR)
multiline_comment|/* The simulator has an nb85e-style interrupt system.  */
macro_line|#include &lt;asm/nb85e_intc.h&gt;
multiline_comment|/* For &lt;asm/irq.h&gt; */
DECL|macro|NUM_CPU_IRQS
mdefine_line|#define NUM_CPU_IRQS&t;&t;64
multiline_comment|/* For &lt;asm/page.h&gt; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;DRAM_ADDR
multiline_comment|/* For &lt;asm/entry.h&gt; */
multiline_comment|/* `R0 RAM&squot;, used for a few miscellaneous variables that must be accessible&n;   using a load instruction relative to R0.  The sim85e2c simulator&n;   actually puts 1020K of RAM from FFF00000 to FFFFF000, so we arbitarily&n;   choose a small portion at the end of that.  */
DECL|macro|R0_RAM_ADDR
mdefine_line|#define R0_RAM_ADDR&t;&t;0xFFFFE000
multiline_comment|/* For &lt;asm/param.h&gt; */
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ&t;&t;&t;24&t;/* Minimum supported frequency.  */
macro_line|#endif
macro_line|#endif /* __V850_SIM85E2C_H__ */
eof
