multiline_comment|/*&n; * include/asm-v850/rte_nb85e_cb.h -- Midas labs RTE-V850/NB85E-CB board&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_RTE_NB85E_CB_H__
DECL|macro|__V850_RTE_NB85E_CB_H__
mdefine_line|#define __V850_RTE_NB85E_CB_H__
macro_line|#include &lt;asm/rte_cb.h&gt;&t;&t;/* Common defs for Midas RTE-CB boards.  */
DECL|macro|PLATFORM
mdefine_line|#define PLATFORM&t;&quot;rte-v850e/nb85e-cb&quot;
DECL|macro|PLATFORM_LONG
mdefine_line|#define PLATFORM_LONG&t;&quot;Midas lab RTE-V850E/NB85E-CB&quot;
DECL|macro|CPU_CLOCK_FREQ
mdefine_line|#define CPU_CLOCK_FREQ&t;50000000 /* 50MHz */
multiline_comment|/* 1MB of onboard SRAM.  Note that the monitor ROM uses parts of this&n;   for its own purposes, so care must be taken.  */
DECL|macro|SRAM_ADDR
mdefine_line|#define SRAM_ADDR&t;0x03C00000
DECL|macro|SRAM_SIZE
mdefine_line|#define SRAM_SIZE&t;0x00100000 /* 1MB */
multiline_comment|/* 16MB of onbard SDRAM.  */
DECL|macro|SDRAM_ADDR
mdefine_line|#define SDRAM_ADDR&t;0x01000000
DECL|macro|SDRAM_SIZE
mdefine_line|#define SDRAM_SIZE&t;0x01000000 /* 16MB */
macro_line|#ifdef CONFIG_ROM_KERNEL
multiline_comment|/* Kernel is in ROM, starting at address 0.  */
DECL|macro|INTV_BASE
mdefine_line|#define INTV_BASE&t;0
macro_line|#else /* !CONFIG_ROM_KERNEL */
multiline_comment|/* We&squot;re using the ROM monitor.  */
multiline_comment|/* The chip&squot;s real interrupt vectors are in ROM, but they jump to a&n;   secondary interrupt vector table in RAM.  */
DECL|macro|INTV_BASE
mdefine_line|#define INTV_BASE&t;0x004F8000
multiline_comment|/* Scratch memory used by the ROM monitor, which shouldn&squot;t be used by&n;   linux (except for the alternate interrupt vector area, defined&n;   above).  */
DECL|macro|MON_SCRATCH_ADDR
mdefine_line|#define MON_SCRATCH_ADDR&t;0x03CE8000
DECL|macro|MON_SCRATCH_SIZE
mdefine_line|#define MON_SCRATCH_SIZE&t;0x00008000 /* 32KB */
macro_line|#endif /* CONFIG_ROM_KERNEL */
multiline_comment|/* Some misc. on-board devices.  */
multiline_comment|/* Seven-segment LED display (two digits).  Write-only.  */
DECL|macro|LED_ADDR
mdefine_line|#define LED_ADDR(n)&t;(0x03802000 + (n))
DECL|macro|LED
mdefine_line|#define LED(n)&t;&t;(*(volatile unsigned char *)LED_ADDR(n))
DECL|macro|LED_NUM_DIGITS
mdefine_line|#define LED_NUM_DIGITS&t;4
macro_line|#endif /* __V850_RTE_NB85E_CB_H__ */
eof
