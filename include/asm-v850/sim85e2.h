multiline_comment|/*&n; * include/asm-v850/sim85e2.h -- Machine-dependent defs for&n; *&t;V850E2 RTL simulator&n; *&n; *  Copyright (C) 2002,03  NEC Electronics Corporation&n; *  Copyright (C) 2002,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_SIM85E2_H__
DECL|macro|__V850_SIM85E2_H__
mdefine_line|#define __V850_SIM85E2_H__
macro_line|#include &lt;asm/v850e2.h&gt;&t;&t;/* Based on V850E2 core.  */
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
multiline_comment|/* Dynamic RAM; uses memory controller.  */
DECL|macro|SDRAM_ADDR
mdefine_line|#define SDRAM_ADDR&t;&t;0x10000000
macro_line|#if 0
mdefine_line|#define SDRAM_SIZE&t;&t;0x01000000 /* 16MB */
macro_line|#else
DECL|macro|SDRAM_SIZE
mdefine_line|#define SDRAM_SIZE&t;&t;0x00200000 /* Only use 2MB for testing */
macro_line|#endif
multiline_comment|/* Simulator specific control registers.  */
multiline_comment|/* NOTHAL controls whether the simulator will stop at a `halt&squot; insn.  */
DECL|macro|SIM85E2_NOTHAL_ADDR
mdefine_line|#define SIM85E2_NOTHAL_ADDR&t;0xffffff22
DECL|macro|SIM85E2_NOTHAL
mdefine_line|#define SIM85E2_NOTHAL&t;&t;(*(volatile u8 *)SIM85E2_NOTHAL_ADDR)
multiline_comment|/* The simulator will stop N cycles after N is written to SIMFIN.  */
DECL|macro|SIM85E2_SIMFIN_ADDR
mdefine_line|#define SIM85E2_SIMFIN_ADDR&t;0xffffff24
DECL|macro|SIM85E2_SIMFIN
mdefine_line|#define SIM85E2_SIMFIN&t;&t;(*(volatile u16 *)SIM85E2_SIMFIN_ADDR)
multiline_comment|/* For &lt;asm/irq.h&gt; */
DECL|macro|NUM_CPU_IRQS
mdefine_line|#define NUM_CPU_IRQS&t;&t;64
multiline_comment|/* For &lt;asm/page.h&gt; */
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;SDRAM_ADDR
multiline_comment|/* For &lt;asm/entry.h&gt; */
multiline_comment|/* `R0 RAM&squot;, used for a few miscellaneous variables that must be accessible&n;   using a load instruction relative to R0.  The sim85e2 simulator&n;   actually puts 1020K of RAM from FFF00000 to FFFFF000, so we arbitarily&n;   choose a small portion at the end of that.  */
DECL|macro|R0_RAM_ADDR
mdefine_line|#define R0_RAM_ADDR&t;&t;0xFFFFE000
multiline_comment|/* For &lt;asm/param.h&gt; */
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ&t;&t;&t;24&t;/* Minimum supported frequency.  */
macro_line|#endif
macro_line|#endif /* __V850_SIM85E2_H__ */
eof
