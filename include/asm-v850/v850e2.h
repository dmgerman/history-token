multiline_comment|/*&n; * include/asm-v850/v850e2.h -- Machine-dependent defs for V850E2 CPUs&n; *&n; *  Copyright (C) 2002,03  NEC Electronics Corporation&n; *  Copyright (C) 2002,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_V850E2_H__
DECL|macro|__V850_V850E2_H__
mdefine_line|#define __V850_V850E2_H__
macro_line|#include &lt;asm/v850e_intc.h&gt;&t;/* v850e-style interrupt system.  */
DECL|macro|CPU_ARCH
mdefine_line|#define CPU_ARCH &quot;v850e2&quot;
multiline_comment|/* Control registers.  */
multiline_comment|/* Chip area select control */
DECL|macro|V850E2_CSC_ADDR
mdefine_line|#define V850E2_CSC_ADDR(n)&t;(0xFFFFF060 + (n) * 2)
DECL|macro|V850E2_CSC
mdefine_line|#define V850E2_CSC(n)&t;&t;(*(volatile u16 *)V850E2_CSC_ADDR(n))
multiline_comment|/* I/O area select control */
DECL|macro|V850E2_BPC_ADDR
mdefine_line|#define V850E2_BPC_ADDR&t;&t;0xFFFFF064
DECL|macro|V850E2_BPC
mdefine_line|#define V850E2_BPC&t;&t;(*(volatile u16 *)V850E2_BPC_ADDR)
multiline_comment|/* Bus size configuration */
DECL|macro|V850E2_BSC_ADDR
mdefine_line|#define V850E2_BSC_ADDR&t;&t;0xFFFFF066
DECL|macro|V850E2_BSC
mdefine_line|#define V850E2_BSC&t;&t;(*(volatile u16 *)V850E2_BSC_ADDR)
multiline_comment|/* Endian configuration */
DECL|macro|V850E2_BEC_ADDR
mdefine_line|#define V850E2_BEC_ADDR&t;&t;0xFFFFF068
DECL|macro|V850E2_BEC
mdefine_line|#define V850E2_BEC&t;&t;(*(volatile u16 *)V850E2_BEC_ADDR)
multiline_comment|/* Cache configuration */
DECL|macro|V850E2_BHC_ADDR
mdefine_line|#define V850E2_BHC_ADDR&t;&t;0xFFFFF06A
DECL|macro|V850E2_BHC
mdefine_line|#define V850E2_BHC&t;&t;(*(volatile u16 *)V850E2_BHC_ADDR)
multiline_comment|/* NPB strobe-wait configuration */
DECL|macro|V850E2_VSWC_ADDR
mdefine_line|#define V850E2_VSWC_ADDR&t;0xFFFFF06E
DECL|macro|V850E2_VSWC
mdefine_line|#define V850E2_VSWC&t;&t;(*(volatile u16 *)V850E2_VSWC_ADDR)
multiline_comment|/* Bus cycle type */
DECL|macro|V850E2_BCT_ADDR
mdefine_line|#define V850E2_BCT_ADDR(n)&t;(0xFFFFF480 + (n) * 2)
DECL|macro|V850E2_BCT
mdefine_line|#define V850E2_BCT(n)&t;&t;(*(volatile u16 *)V850E2_BCT_ADDR(n))
multiline_comment|/* Data wait control */
DECL|macro|V850E2_DWC_ADDR
mdefine_line|#define V850E2_DWC_ADDR(n)&t;(0xFFFFF484 + (n) * 2)
DECL|macro|V850E2_DWC
mdefine_line|#define V850E2_DWC(n)&t;&t;(*(volatile u16 *)V850E2_DWC_ADDR(n))
multiline_comment|/* Bus cycle control */
DECL|macro|V850E2_BCC_ADDR
mdefine_line|#define V850E2_BCC_ADDR&t;&t;0xFFFFF488
DECL|macro|V850E2_BCC
mdefine_line|#define V850E2_BCC&t;&t;(*(volatile u16 *)V850E2_BCC_ADDR)
multiline_comment|/* Address wait control */
DECL|macro|V850E2_ASC_ADDR
mdefine_line|#define V850E2_ASC_ADDR&t;&t;0xFFFFF48A
DECL|macro|V850E2_ASC
mdefine_line|#define V850E2_ASC&t;&t;(*(volatile u16 *)V850E2_ASC_ADDR)
multiline_comment|/* Local bus sizing control */
DECL|macro|V850E2_LBS_ADDR
mdefine_line|#define V850E2_LBS_ADDR&t;&t;0xFFFFF48E
DECL|macro|V850E2_LBS
mdefine_line|#define V850E2_LBS&t;&t;(*(volatile u16 *)V850E2_LBS_ADDR)
multiline_comment|/* Line buffer control */
DECL|macro|V850E2_LBC_ADDR
mdefine_line|#define V850E2_LBC_ADDR(n)&t;(0xFFFFF490 + (n) * 2)
DECL|macro|V850E2_LBC
mdefine_line|#define V850E2_LBC(n)&t;&t;(*(volatile u16 *)V850E2_LBC_ADDR(n))
multiline_comment|/* SDRAM configuration */
DECL|macro|V850E2_SCR_ADDR
mdefine_line|#define V850E2_SCR_ADDR(n)&t;(0xFFFFF4A0 + (n) * 4)
DECL|macro|V850E2_SCR
mdefine_line|#define V850E2_SCR(n)&t;&t;(*(volatile u16 *)V850E2_SCR_ADDR(n))
multiline_comment|/* SDRAM refresh cycle control */
DECL|macro|V850E2_RFS_ADDR
mdefine_line|#define V850E2_RFS_ADDR(n)&t;(0xFFFFF4A2 + (n) * 4)
DECL|macro|V850E2_RFS
mdefine_line|#define V850E2_RFS(n)&t;&t;(*(volatile u16 *)V850E2_RFS_ADDR(n))
macro_line|#endif /* __V850_V850E2_H__ */
eof
