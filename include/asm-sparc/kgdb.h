multiline_comment|/* $Id: kgdb.h,v 1.8 1998/01/07 06:33:44 baccala Exp $&n; * kgdb.h: Defines and declarations for serial line source level&n; *         remote debugging of the Linux kernel using gdb.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_KGDB_H
DECL|macro|_SPARC_KGDB_H
mdefine_line|#define _SPARC_KGDB_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* To init the kgdb engine. */
r_extern
r_void
id|set_debug_traps
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* To enter the debugger explicitly. */
r_extern
r_void
id|breakpoint
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* For convenience we define the format of a kgdb trap breakpoint&n; * frame here also.&n; */
DECL|struct|kgdb_frame
r_struct
id|kgdb_frame
(brace
DECL|member|globals
r_int
r_int
id|globals
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|outs
r_int
r_int
id|outs
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|locals
r_int
r_int
id|locals
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ins
r_int
r_int
id|ins
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|fpregs
r_int
r_int
id|fpregs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|y
r_int
r_int
id|y
suffix:semicolon
DECL|member|psr
r_int
r_int
id|psr
suffix:semicolon
DECL|member|wim
r_int
r_int
id|wim
suffix:semicolon
DECL|member|tbr
r_int
r_int
id|tbr
suffix:semicolon
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
DECL|member|npc
r_int
r_int
id|npc
suffix:semicolon
DECL|member|fpsr
r_int
r_int
id|fpsr
suffix:semicolon
DECL|member|cpsr
r_int
r_int
id|cpsr
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
multiline_comment|/* Macros for assembly usage of the kgdb breakpoint frame. */
DECL|macro|KGDB_G0
mdefine_line|#define KGDB_G0     0x000
DECL|macro|KGDB_G1
mdefine_line|#define KGDB_G1     0x004
DECL|macro|KGDB_G2
mdefine_line|#define KGDB_G2     0x008
DECL|macro|KGDB_G4
mdefine_line|#define KGDB_G4     0x010
DECL|macro|KGDB_G6
mdefine_line|#define KGDB_G6     0x018
DECL|macro|KGDB_I0
mdefine_line|#define KGDB_I0     0x020
DECL|macro|KGDB_I2
mdefine_line|#define KGDB_I2     0x028
DECL|macro|KGDB_I4
mdefine_line|#define KGDB_I4     0x030
DECL|macro|KGDB_I6
mdefine_line|#define KGDB_I6     0x038
DECL|macro|KGDB_Y
mdefine_line|#define KGDB_Y      0x100
DECL|macro|KGDB_PSR
mdefine_line|#define KGDB_PSR    0x104
DECL|macro|KGDB_WIM
mdefine_line|#define KGDB_WIM    0x108
DECL|macro|KGDB_TBR
mdefine_line|#define KGDB_TBR    0x10c
DECL|macro|KGDB_PC
mdefine_line|#define KGDB_PC     0x110
DECL|macro|KGDB_NPC
mdefine_line|#define KGDB_NPC    0x114
DECL|macro|SAVE_KGDB_GLOBALS
mdefine_line|#define SAVE_KGDB_GLOBALS(reg) &bslash;&n;        std     %g0, [%reg + REGWIN_SZ + KGDB_G0]; &bslash;&n;        std     %g2, [%reg + REGWIN_SZ + KGDB_G2]; &bslash;&n;        std     %g4, [%reg + REGWIN_SZ + KGDB_G4]; &bslash;&n;        std     %g6, [%reg + REGWIN_SZ + KGDB_G6];
DECL|macro|SAVE_KGDB_INS
mdefine_line|#define SAVE_KGDB_INS(reg) &bslash;&n;        std     %i0, [%reg + REGWIN_SZ + KGDB_I0]; &bslash;&n;        std     %i2, [%reg + REGWIN_SZ + KGDB_I2]; &bslash;&n;        std     %i4, [%reg + REGWIN_SZ + KGDB_I4]; &bslash;&n;        std     %i6, [%reg + REGWIN_SZ + KGDB_I6];
DECL|macro|SAVE_KGDB_SREGS
mdefine_line|#define SAVE_KGDB_SREGS(reg, reg_y, reg_psr, reg_wim, reg_tbr, reg_pc, reg_npc) &bslash;&n;        st      %reg_y, [%reg + REGWIN_SZ + KGDB_Y]; &bslash;&n;        st      %reg_psr, [%reg + REGWIN_SZ + KGDB_PSR]; &bslash;&n;        st      %reg_wim, [%reg + REGWIN_SZ + KGDB_WIM]; &bslash;&n;        st      %reg_tbr, [%reg + REGWIN_SZ + KGDB_TBR]; &bslash;&n;        st      %reg_pc, [%reg + REGWIN_SZ + KGDB_PC]; &bslash;&n;        st      %reg_npc, [%reg + REGWIN_SZ + KGDB_NPC];
DECL|macro|LOAD_KGDB_GLOBALS
mdefine_line|#define LOAD_KGDB_GLOBALS(reg) &bslash;&n;        ld      [%reg + REGWIN_SZ + KGDB_G1], %g1; &bslash;&n;        ldd     [%reg + REGWIN_SZ + KGDB_G2], %g2; &bslash;&n;        ldd     [%reg + REGWIN_SZ + KGDB_G4], %g4; &bslash;&n;        ldd     [%reg + REGWIN_SZ + KGDB_G6], %g6;
DECL|macro|LOAD_KGDB_INS
mdefine_line|#define LOAD_KGDB_INS(reg) &bslash;&n;        ldd     [%reg + REGWIN_SZ + KGDB_I0], %i0; &bslash;&n;        ldd     [%reg + REGWIN_SZ + KGDB_I2], %i2; &bslash;&n;        ldd     [%reg + REGWIN_SZ + KGDB_I4], %i4; &bslash;&n;        ldd     [%reg + REGWIN_SZ + KGDB_I6], %i6;
DECL|macro|LOAD_KGDB_SREGS
mdefine_line|#define LOAD_KGDB_SREGS(reg, reg_y, reg_psr, reg_wim, reg_tbr, reg_pc, reg_npc) &bslash;&n;&t;ld&t;[%reg + REGWIN_SZ + KGDB_Y], %reg_y; &bslash;&n;&t;ld&t;[%reg + REGWIN_SZ + KGDB_PSR], %reg_psr; &bslash;&n;&t;ld&t;[%reg + REGWIN_SZ + KGDB_WIM], %reg_wim; &bslash;&n;&t;ld&t;[%reg + REGWIN_SZ + KGDB_TBR], %reg_tbr; &bslash;&n;&t;ld&t;[%reg + REGWIN_SZ + KGDB_PC], %reg_pc; &bslash;&n;&t;ld&t;[%reg + REGWIN_SZ + KGDB_NPC], %reg_npc;
macro_line|#endif /* !(_SPARC_KGDB_H) */
eof
