multiline_comment|/*&n; * The Embedded Planet HIOX expansion card definitions.&n; * There were a few different versions of these cards, but only&n; * the one that escaped real production is defined here.&n; *&n; * Copyright (c) 2000 Dan Malek (dmalek@jlc.net)&n; */
macro_line|#ifndef __MACH_RPX_HIOX_DEFS
DECL|macro|__MACH_RPX_HIOX_DEFS
mdefine_line|#define __MACH_RPX_HIOX_DEFS
DECL|macro|HIOX_CSR_ADDR
mdefine_line|#define HIOX_CSR_ADDR&t;&t;((uint)0xfac00000)
DECL|macro|HIOX_CSR_SIZE
mdefine_line|#define HIOX_CSR_SIZE&t;&t;((uint)(4 * 1024))
DECL|macro|HIOX_CSR0_ADDR
mdefine_line|#define HIOX_CSR0_ADDR&t;&t;HIOX_CSR_ADDR
DECL|macro|HIOX_CSR4_ADDR
mdefine_line|#define HIOX_CSR4_ADDR&t;&t;((uint)0xfac00004)
DECL|macro|HIOX_CSR0_DEFAULT
mdefine_line|#define HIOX_CSR0_DEFAULT&t;((uint)0x380f3c00)
DECL|macro|HIOX_CSR0_ENSCC2
mdefine_line|#define HIOX_CSR0_ENSCC2&t;((uint)0x80000000)
DECL|macro|HIOX_CSR0_ENSMC2
mdefine_line|#define HIOX_CSR0_ENSMC2&t;((uint)0x04000000)
DECL|macro|HIOX_CSR0_ENVDOCLK
mdefine_line|#define HIOX_CSR0_ENVDOCLK&t;((uint)0x02000000)
DECL|macro|HIOX_CSR0_VDORST_HL
mdefine_line|#define HIOX_CSR0_VDORST_HL&t;((uint)0x01000000)
DECL|macro|HIOX_CSR0_RS232SEL
mdefine_line|#define HIOX_CSR0_RS232SEL&t;((uint)0x0000c000)
DECL|macro|HIOX_CSR0_SCC3SEL
mdefine_line|#define HIOX_CSR0_SCC3SEL&t;((uint)0x0000c000)
DECL|macro|HIOX_CSR0_SMC1SEL
mdefine_line|#define HIOX_CSR0_SMC1SEL&t;((uint)0x00008000)
DECL|macro|HIOX_CSR0_SCC1SEL
mdefine_line|#define HIOX_CSR0_SCC1SEL&t;((uint)0x00004000)
DECL|macro|HIOX_CSR0_ENTOUCH
mdefine_line|#define HIOX_CSR0_ENTOUCH&t;((uint)0x00000080)
DECL|macro|HIOX_CSR0_PDOWN100
mdefine_line|#define HIOX_CSR0_PDOWN100&t;((uint)0x00000060)
DECL|macro|HIOX_CSR0_PDOWN10
mdefine_line|#define HIOX_CSR0_PDOWN10&t;((uint)0x00000040)
DECL|macro|HIOX_CSR0_PDOWN1
mdefine_line|#define HIOX_CSR0_PDOWN1&t;((uint)0x00000020)
DECL|macro|HIOX_CSR0_TSELSPI
mdefine_line|#define HIOX_CSR0_TSELSPI&t;((uint)0x00000010)
DECL|macro|HIOX_CSR0_TIRQSTAT
mdefine_line|#define HIOX_CSR0_TIRQSTAT&t;((uint)0x00000008)
DECL|macro|HIOX_CSR4_DEFAULT
mdefine_line|#define HIOX_CSR4_DEFAULT&t;((uint)0x00000000)
DECL|macro|HIOX_CSR4_ENTIRQ2
mdefine_line|#define HIOX_CSR4_ENTIRQ2&t;((uint)0x20000000)
DECL|macro|HIOX_CSR4_ENTIRQ3
mdefine_line|#define HIOX_CSR4_ENTIRQ3&t;((uint)0x10000000)
DECL|macro|HIOX_CSR4_ENAUDIO
mdefine_line|#define HIOX_CSR4_ENAUDIO&t;((uint)0x00000080)
DECL|macro|HIOX_CSR4_RSTAUDIO
mdefine_line|#define HIOX_CSR4_RSTAUDIO&t;((uint)0x00000040)&t;/* 0 == reset */
DECL|macro|HIOX_CSR4_AUDCLKHI
mdefine_line|#define HIOX_CSR4_AUDCLKHI&t;((uint)0x00000020)
DECL|macro|HIOX_CSR4_AUDSPISEL
mdefine_line|#define HIOX_CSR4_AUDSPISEL&t;((uint)0x00000010)
DECL|macro|HIOX_CSR4_AUDIRQSTAT
mdefine_line|#define HIOX_CSR4_AUDIRQSTAT&t;((uint)0x00000008)
DECL|macro|HIOX_CSR4_AUDCLKSEL
mdefine_line|#define HIOX_CSR4_AUDCLKSEL&t;((uint)0x00000007)
macro_line|#endif
eof
