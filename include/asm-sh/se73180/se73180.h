macro_line|#ifndef __ASM_SH_HITACHI_SE73180_H
DECL|macro|__ASM_SH_HITACHI_SE73180_H
mdefine_line|#define __ASM_SH_HITACHI_SE73180_H
multiline_comment|/*&n; * include/asm-sh/se/se73180.h&n; *&n; * Copyright (C) 2003 Takashi Kusuda &lt;kusuda-takashi@hitachi-ul.co.jp&gt;&n; *&n; * SH-Mobile SolutionEngine 73180 support&n; */
multiline_comment|/* Box specific addresses.  */
multiline_comment|/* Area 0 */
DECL|macro|PA_ROM
mdefine_line|#define PA_ROM&t;&t;0x00000000&t;/* EPROM */
DECL|macro|PA_ROM_SIZE
mdefine_line|#define PA_ROM_SIZE&t;0x00400000&t;/* EPROM size 4M byte(Actually 2MB) */
DECL|macro|PA_FROM
mdefine_line|#define PA_FROM&t;&t;0x00400000&t;/* Flash ROM */
DECL|macro|PA_FROM_SIZE
mdefine_line|#define PA_FROM_SIZE&t;0x00400000&t;/* Flash size 4M byte */
DECL|macro|PA_SRAM
mdefine_line|#define PA_SRAM&t;&t;0x00800000&t;/* SRAM */
DECL|macro|PA_FROM_SIZE
mdefine_line|#define PA_FROM_SIZE&t;0x00400000&t;/* SRAM size 4M byte */
multiline_comment|/* Area 1 */
DECL|macro|PA_EXT1
mdefine_line|#define PA_EXT1&t;&t;0x04000000
DECL|macro|PA_EXT1_SIZE
mdefine_line|#define PA_EXT1_SIZE&t;0x04000000
multiline_comment|/* Area 2 */
DECL|macro|PA_EXT2
mdefine_line|#define PA_EXT2&t;&t;0x08000000
DECL|macro|PA_EXT2_SIZE
mdefine_line|#define PA_EXT2_SIZE&t;0x04000000
multiline_comment|/* Area 3 */
DECL|macro|PA_SDRAM
mdefine_line|#define PA_SDRAM&t;0x0c000000
DECL|macro|PA_SDRAM_SIZE
mdefine_line|#define PA_SDRAM_SIZE&t;0x04000000
multiline_comment|/* Area 4 */
DECL|macro|PA_PCIC
mdefine_line|#define PA_PCIC&t;&t;0x10000000&t;/* MR-SHPC-01 PCMCIA */
DECL|macro|PA_MRSHPC
mdefine_line|#define PA_MRSHPC       0xb03fffe0      /* MR-SHPC-01 PCMCIA controller */
DECL|macro|PA_MRSHPC_MW1
mdefine_line|#define PA_MRSHPC_MW1   0xb0400000      /* MR-SHPC-01 memory window base */
DECL|macro|PA_MRSHPC_MW2
mdefine_line|#define PA_MRSHPC_MW2   0xb0500000      /* MR-SHPC-01 attribute window base */
DECL|macro|PA_MRSHPC_IO
mdefine_line|#define PA_MRSHPC_IO    0xb0600000      /* MR-SHPC-01 I/O window base */
DECL|macro|MRSHPC_OPTION
mdefine_line|#define MRSHPC_OPTION   (PA_MRSHPC + 6)
DECL|macro|MRSHPC_CSR
mdefine_line|#define MRSHPC_CSR      (PA_MRSHPC + 8)
DECL|macro|MRSHPC_ISR
mdefine_line|#define MRSHPC_ISR      (PA_MRSHPC + 10)
DECL|macro|MRSHPC_ICR
mdefine_line|#define MRSHPC_ICR      (PA_MRSHPC + 12)
DECL|macro|MRSHPC_CPWCR
mdefine_line|#define MRSHPC_CPWCR    (PA_MRSHPC + 14)
DECL|macro|MRSHPC_MW0CR1
mdefine_line|#define MRSHPC_MW0CR1   (PA_MRSHPC + 16)
DECL|macro|MRSHPC_MW1CR1
mdefine_line|#define MRSHPC_MW1CR1   (PA_MRSHPC + 18)
DECL|macro|MRSHPC_IOWCR1
mdefine_line|#define MRSHPC_IOWCR1   (PA_MRSHPC + 20)
DECL|macro|MRSHPC_MW0CR2
mdefine_line|#define MRSHPC_MW0CR2   (PA_MRSHPC + 22)
DECL|macro|MRSHPC_MW1CR2
mdefine_line|#define MRSHPC_MW1CR2   (PA_MRSHPC + 24)
DECL|macro|MRSHPC_IOWCR2
mdefine_line|#define MRSHPC_IOWCR2   (PA_MRSHPC + 26)
DECL|macro|MRSHPC_CDCR
mdefine_line|#define MRSHPC_CDCR     (PA_MRSHPC + 28)
DECL|macro|MRSHPC_PCIC_INFO
mdefine_line|#define MRSHPC_PCIC_INFO (PA_MRSHPC + 30)
DECL|macro|PA_LED
mdefine_line|#define PA_LED&t;&t;0xb0C00000&t;/* LED */
DECL|macro|LED_SHIFT
mdefine_line|#define LED_SHIFT       0
DECL|macro|PA_DIPSW
mdefine_line|#define PA_DIPSW&t;0xb0900000&t;/* Dip switch 31 */
DECL|macro|PA_EPLD_MODESET
mdefine_line|#define PA_EPLD_MODESET&t;0xb0a00000&t;/* FPGA Mode set register */
DECL|macro|PA_EPLD_ST1
mdefine_line|#define PA_EPLD_ST1&t;0xb0a80000&t;/* FPGA Interrupt status register1 */
DECL|macro|PA_EPLD_ST2
mdefine_line|#define PA_EPLD_ST2&t;0xb0ac0000&t;/* FPGA Interrupt status register2 */
multiline_comment|/* Area 5 */
DECL|macro|PA_EXT5
mdefine_line|#define PA_EXT5&t;&t;0x14000000
DECL|macro|PA_EXT5_SIZE
mdefine_line|#define PA_EXT5_SIZE&t;0x04000000
multiline_comment|/* Area 6 */
DECL|macro|PA_LCD1
mdefine_line|#define PA_LCD1&t;&t;0xb8000000
DECL|macro|PA_LCD2
mdefine_line|#define PA_LCD2&t;&t;0xb8800000
macro_line|#endif  /* __ASM_SH_HITACHI_SE73180_H */
eof
