multiline_comment|/* gdb-stub.h: FRV GDB stub&n; *&n; * Copyright (C) 2003 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; * - Derived from asm-mips/gdb-stub.h (c) 1995 Andreas Busse&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __ASM_GDB_STUB_H
DECL|macro|__ASM_GDB_STUB_H
mdefine_line|#define __ASM_GDB_STUB_H
DECL|macro|GDBSTUB_DEBUG_PROTOCOL
macro_line|#undef GDBSTUB_DEBUG_PROTOCOL
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/*&n; * important register numbers in GDB protocol&n; * - GR0,  GR1,  GR2,  GR3,  GR4,  GR5,  GR6,  GR7,&n; * - GR8,  GR9,  GR10, GR11, GR12, GR13, GR14, GR15,&n; * - GR16, GR17, GR18, GR19, GR20, GR21, GR22, GR23,&n; * - GR24, GR25, GR26, GR27, GR28, GR29, GR30, GR31,&n; * - GR32, GR33, GR34, GR35, GR36, GR37, GR38, GR39,&n; * - GR40, GR41, GR42, GR43, GR44, GR45, GR46, GR47,&n; * - GR48, GR49, GR50, GR51, GR52, GR53, GR54, GR55,&n; * - GR56, GR57, GR58, GR59, GR60, GR61, GR62, GR63,&n; * - FR0,  FR1,  FR2,  FR3,  FR4,  FR5,  FR6,  FR7,&n; * - FR8,  FR9,  FR10, FR11, FR12, FR13, FR14, FR15,&n; * - FR16, FR17, FR18, FR19, FR20, FR21, FR22, FR23,&n; * - FR24, FR25, FR26, FR27, FR28, FR29, FR30, FR31,&n; * - FR32, FR33, FR34, FR35, FR36, FR37, FR38, FR39,&n; * - FR40, FR41, FR42, FR43, FR44, FR45, FR46, FR47,&n; * - FR48, FR49, FR50, FR51, FR52, FR53, FR54, FR55,&n; * - FR56, FR57, FR58, FR59, FR60, FR61, FR62, FR63,&n; * - PC, PSR, CCR, CCCR,&n; * - _X132, _X133, _X134&n; * - TBR, BRR, DBAR0, DBAR1, DBAR2, DBAR3,&n; * - SCR0, SCR1, SCR2, SCR3,&n; * - LR, LCR,&n; * - IACC0H, IACC0L,&n; * - FSR0,&n; * - ACC0, ACC1, ACC2, ACC3, ACC4, ACC5, ACC6, ACC7,&n; * - ACCG0123, ACCG4567,&n; * - MSR0, MSR1,&n; * - GNER0, GNER1,&n; * - FNER0, FNER1,&n; */
DECL|macro|GDB_REG_GR
mdefine_line|#define GDB_REG_GR(N)&t;(N)
DECL|macro|GDB_REG_FR
mdefine_line|#define GDB_REG_FR(N)&t;(64+(N))
DECL|macro|GDB_REG_PC
mdefine_line|#define GDB_REG_PC&t;128
DECL|macro|GDB_REG_PSR
mdefine_line|#define GDB_REG_PSR&t;129
DECL|macro|GDB_REG_CCR
mdefine_line|#define GDB_REG_CCR&t;130
DECL|macro|GDB_REG_CCCR
mdefine_line|#define GDB_REG_CCCR&t;131
DECL|macro|GDB_REG_TBR
mdefine_line|#define GDB_REG_TBR&t;135
DECL|macro|GDB_REG_BRR
mdefine_line|#define GDB_REG_BRR&t;136
DECL|macro|GDB_REG_DBAR
mdefine_line|#define GDB_REG_DBAR(N)&t;(137+(N))
DECL|macro|GDB_REG_SCR
mdefine_line|#define GDB_REG_SCR(N)&t;(141+(N))
DECL|macro|GDB_REG_LR
mdefine_line|#define GDB_REG_LR&t;145
DECL|macro|GDB_REG_LCR
mdefine_line|#define GDB_REG_LCR&t;146
DECL|macro|GDB_REG_FSR0
mdefine_line|#define GDB_REG_FSR0&t;149
DECL|macro|GDB_REG_ACC
mdefine_line|#define GDB_REG_ACC(N)&t;(150+(N))
DECL|macro|GDB_REG_ACCG
mdefine_line|#define GDB_REG_ACCG(N)&t;(158+(N)/4)
DECL|macro|GDB_REG_MSR
mdefine_line|#define GDB_REG_MSR(N)&t;(160+(N))
DECL|macro|GDB_REG_GNER
mdefine_line|#define GDB_REG_GNER(N)&t;(162+(N))
DECL|macro|GDB_REG_FNER
mdefine_line|#define GDB_REG_FNER(N)&t;(164+(N))
DECL|macro|GDB_REG_SP
mdefine_line|#define GDB_REG_SP&t;GDB_REG_GR(1)
DECL|macro|GDB_REG_FP
mdefine_line|#define GDB_REG_FP&t;GDB_REG_GR(2)
macro_line|#ifndef _LANGUAGE_ASSEMBLY
multiline_comment|/*&n; * Prototypes&n; */
r_extern
r_void
id|show_registers_only
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|gdbstub_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|gdbstub
c_func
(paren
r_int
id|type
)paren
suffix:semicolon
r_extern
r_void
id|gdbstub_exit
c_func
(paren
r_int
id|status
)paren
suffix:semicolon
r_extern
r_void
id|gdbstub_io_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|gdbstub_set_baud
c_func
(paren
r_int
id|baud
)paren
suffix:semicolon
r_extern
r_int
id|gdbstub_rx_char
c_func
(paren
r_int
r_char
op_star
id|_ch
comma
r_int
id|nonblock
)paren
suffix:semicolon
r_extern
r_void
id|gdbstub_tx_char
c_func
(paren
r_int
r_char
id|ch
)paren
suffix:semicolon
r_extern
r_void
id|gdbstub_tx_flush
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|gdbstub_do_rx
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|__debug_stub_init_break
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|__break_hijack_kernel_event
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|start_kernel
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|gdbstub_rx_handler
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|gdbstub_rx_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|gdbstub_intercept
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_uint32
id|__entry_usertrap_table
(braket
)braket
suffix:semicolon
r_extern
r_uint32
id|__entry_kerneltrap_table
(braket
)braket
suffix:semicolon
r_extern
r_volatile
id|u8
id|gdbstub_rx_buffer
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
r_extern
r_volatile
id|u32
id|gdbstub_rx_inp
suffix:semicolon
r_extern
r_volatile
id|u32
id|gdbstub_rx_outp
suffix:semicolon
r_extern
r_volatile
id|u8
id|gdbstub_rx_overflow
suffix:semicolon
r_extern
id|u8
id|gdbstub_rx_unget
suffix:semicolon
r_extern
r_void
id|gdbstub_printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_void
id|debug_to_serial
c_func
(paren
r_const
r_char
op_star
id|p
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
r_void
id|console_set_baud
c_func
(paren
r_int
id|baud
)paren
suffix:semicolon
macro_line|#ifdef GDBSTUB_DEBUG_PROTOCOL
DECL|macro|gdbstub_proto
mdefine_line|#define gdbstub_proto(FMT,...) gdbstub_printk(FMT,##__VA_ARGS__)
macro_line|#else
DECL|macro|gdbstub_proto
mdefine_line|#define gdbstub_proto(FMT,...) ({ 0; })
macro_line|#endif
macro_line|#endif /* _LANGUAGE_ASSEMBLY */
macro_line|#endif /* __ASM_GDB_STUB_H */
eof
