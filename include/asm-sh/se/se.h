macro_line|#ifndef __ASM_SH_HITACHI_SE_H
DECL|macro|__ASM_SH_HITACHI_SE_H
mdefine_line|#define __ASM_SH_HITACHI_SE_H
multiline_comment|/*&n; * linux/include/asm-sh/hitachi_se.h&n; *&n; * Copyright (C) 2000  Kazumoto Kojima&n; *&n; * Hitachi SolutionEngine support&n; */
multiline_comment|/* Box specific addresses.  */
DECL|macro|PA_ROM
mdefine_line|#define PA_ROM&t;&t;0x00000000&t;/* EPROM */
DECL|macro|PA_ROM_SIZE
mdefine_line|#define PA_ROM_SIZE&t;0x00400000&t;/* EPROM size 4M byte */
DECL|macro|PA_FROM
mdefine_line|#define PA_FROM&t;&t;0x01000000&t;/* EPROM */
DECL|macro|PA_FROM_SIZE
mdefine_line|#define PA_FROM_SIZE&t;0x00400000&t;/* EPROM size 4M byte */
DECL|macro|PA_EXT1
mdefine_line|#define PA_EXT1&t;&t;0x04000000
DECL|macro|PA_EXT1_SIZE
mdefine_line|#define PA_EXT1_SIZE&t;0x04000000
DECL|macro|PA_EXT2
mdefine_line|#define PA_EXT2&t;&t;0x08000000
DECL|macro|PA_EXT2_SIZE
mdefine_line|#define PA_EXT2_SIZE&t;0x04000000
DECL|macro|PA_SDRAM
mdefine_line|#define PA_SDRAM&t;0x0c000000
DECL|macro|PA_SDRAM_SIZE
mdefine_line|#define PA_SDRAM_SIZE&t;0x04000000
DECL|macro|PA_EXT4
mdefine_line|#define PA_EXT4&t;&t;0x12000000
DECL|macro|PA_EXT4_SIZE
mdefine_line|#define PA_EXT4_SIZE&t;0x02000000
DECL|macro|PA_EXT5
mdefine_line|#define PA_EXT5&t;&t;0x14000000
DECL|macro|PA_EXT5_SIZE
mdefine_line|#define PA_EXT5_SIZE&t;0x04000000
DECL|macro|PA_PCIC
mdefine_line|#define PA_PCIC&t;&t;0x18000000&t;/* MR-SHPC-01 PCMCIA */
DECL|macro|PA_83902
mdefine_line|#define PA_83902&t;0xb0000000&t;/* DP83902A */
DECL|macro|PA_83902_IF
mdefine_line|#define PA_83902_IF&t;0xb0040000&t;/* DP83902A remote io port */
DECL|macro|PA_83902_RST
mdefine_line|#define PA_83902_RST&t;0xb0080000&t;/* DP83902A reset port */
DECL|macro|PA_SUPERIO
mdefine_line|#define PA_SUPERIO&t;0xb0400000&t;/* SMC37C935A super io chip */
DECL|macro|PA_DIPSW0
mdefine_line|#define PA_DIPSW0&t;0xb0800000&t;/* Dip switch 5,6 */
DECL|macro|PA_DIPSW1
mdefine_line|#define PA_DIPSW1&t;0xb0800002&t;/* Dip switch 7,8 */
DECL|macro|PA_LED
mdefine_line|#define PA_LED&t;&t;0xb0c00000&t;/* LED */
DECL|macro|PA_BCR
mdefine_line|#define PA_BCR&t;&t;0xb1400000&t;/* FPGA */
DECL|macro|PA_MRSHPC
mdefine_line|#define PA_MRSHPC&t;0xb83fffe0&t;/* MR-SHPC-01 PCMCIA controller */
DECL|macro|PA_MRSHPC_MW1
mdefine_line|#define PA_MRSHPC_MW1&t;0xb8400000&t;/* MR-SHPC-01 memory window base */
DECL|macro|PA_MRSHPC_MW2
mdefine_line|#define PA_MRSHPC_MW2&t;0xb8500000&t;/* MR-SHPC-01 attribute window base */
DECL|macro|PA_MRSHPC_IO
mdefine_line|#define PA_MRSHPC_IO&t;0xb8600000&t;/* MR-SHPC-01 I/O window base */
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
DECL|macro|BCR_ILCRA
mdefine_line|#define BCR_ILCRA&t;(PA_BCR + 0)
DECL|macro|BCR_ILCRB
mdefine_line|#define BCR_ILCRB&t;(PA_BCR + 2)
DECL|macro|BCR_ILCRC
mdefine_line|#define BCR_ILCRC&t;(PA_BCR + 4)
DECL|macro|BCR_ILCRD
mdefine_line|#define BCR_ILCRD&t;(PA_BCR + 6)
DECL|macro|BCR_ILCRE
mdefine_line|#define BCR_ILCRE&t;(PA_BCR + 8)
DECL|macro|BCR_ILCRF
mdefine_line|#define BCR_ILCRF&t;(PA_BCR + 10)
DECL|macro|BCR_ILCRG
mdefine_line|#define BCR_ILCRG&t;(PA_BCR + 12)
DECL|macro|IRQ_STNIC
mdefine_line|#define IRQ_STNIC&t;10
macro_line|#endif  /* __ASM_SH_HITACHI_SE_H */
eof
