multiline_comment|/* $Id: winmacro.h,v 1.22 2000/05/09 17:40:15 davem Exp $&n; * winmacro.h: Window loading-unloading macros.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_WINMACRO_H
DECL|macro|_SPARC_WINMACRO_H
mdefine_line|#define _SPARC_WINMACRO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
multiline_comment|/* These are just handy. */
DECL|macro|_SV
mdefine_line|#define _SV&t;save&t;%sp, -REGWIN_SZ, %sp
DECL|macro|_RS
mdefine_line|#define _RS     restore 
DECL|macro|FLUSH_ALL_KERNEL_WINDOWS
mdefine_line|#define FLUSH_ALL_KERNEL_WINDOWS &bslash;&n;&t;_SV; _SV; _SV; _SV; _SV; _SV; _SV; &bslash;&n;&t;_RS; _RS; _RS; _RS; _RS; _RS; _RS;
multiline_comment|/* Store the register window onto the 8-byte aligned area starting&n; * at %reg.  It might be %sp, it might not, we don&squot;t care.&n; */
DECL|macro|STORE_WINDOW
mdefine_line|#define STORE_WINDOW(reg) &bslash;&n;&t;std&t;%l0, [%reg + RW_L0]; &bslash;&n;&t;std&t;%l2, [%reg + RW_L2]; &bslash;&n;&t;std&t;%l4, [%reg + RW_L4]; &bslash;&n;&t;std&t;%l6, [%reg + RW_L6]; &bslash;&n;&t;std&t;%i0, [%reg + RW_I0]; &bslash;&n;&t;std&t;%i2, [%reg + RW_I2]; &bslash;&n;&t;std&t;%i4, [%reg + RW_I4]; &bslash;&n;&t;std&t;%i6, [%reg + RW_I6];
multiline_comment|/* Load a register window from the area beginning at %reg. */
DECL|macro|LOAD_WINDOW
mdefine_line|#define LOAD_WINDOW(reg) &bslash;&n;&t;ldd&t;[%reg + RW_L0], %l0; &bslash;&n;&t;ldd&t;[%reg + RW_L2], %l2; &bslash;&n;&t;ldd&t;[%reg + RW_L4], %l4; &bslash;&n;&t;ldd&t;[%reg + RW_L6], %l6; &bslash;&n;&t;ldd&t;[%reg + RW_I0], %i0; &bslash;&n;&t;ldd&t;[%reg + RW_I2], %i2; &bslash;&n;&t;ldd&t;[%reg + RW_I4], %i4; &bslash;&n;&t;ldd&t;[%reg + RW_I6], %i6;
multiline_comment|/* Loading and storing struct pt_reg trap frames. */
DECL|macro|LOAD_PT_INS
mdefine_line|#define LOAD_PT_INS(base_reg) &bslash;&n;        ldd     [%base_reg + REGWIN_SZ + PT_I0], %i0; &bslash;&n;        ldd     [%base_reg + REGWIN_SZ + PT_I2], %i2; &bslash;&n;        ldd     [%base_reg + REGWIN_SZ + PT_I4], %i4; &bslash;&n;        ldd     [%base_reg + REGWIN_SZ + PT_I6], %i6;
DECL|macro|LOAD_PT_GLOBALS
mdefine_line|#define LOAD_PT_GLOBALS(base_reg) &bslash;&n;        ld      [%base_reg + REGWIN_SZ + PT_G1], %g1; &bslash;&n;        ldd     [%base_reg + REGWIN_SZ + PT_G2], %g2; &bslash;&n;        ldd     [%base_reg + REGWIN_SZ + PT_G4], %g4; &bslash;&n;        ldd     [%base_reg + REGWIN_SZ + PT_G6], %g6;
DECL|macro|LOAD_PT_YREG
mdefine_line|#define LOAD_PT_YREG(base_reg, scratch) &bslash;&n;        ld      [%base_reg + REGWIN_SZ + PT_Y], %scratch; &bslash;&n;        wr      %scratch, 0x0, %y;
DECL|macro|LOAD_PT_PRIV
mdefine_line|#define LOAD_PT_PRIV(base_reg, pt_psr, pt_pc, pt_npc) &bslash;&n;        ld      [%base_reg + REGWIN_SZ + PT_PSR], %pt_psr; &bslash;&n;        ld      [%base_reg + REGWIN_SZ + PT_PC], %pt_pc; &bslash;&n;        ld      [%base_reg + REGWIN_SZ + PT_NPC], %pt_npc;
DECL|macro|LOAD_PT_ALL
mdefine_line|#define LOAD_PT_ALL(base_reg, pt_psr, pt_pc, pt_npc, scratch) &bslash;&n;        LOAD_PT_YREG(base_reg, scratch) &bslash;&n;        LOAD_PT_INS(base_reg) &bslash;&n;        LOAD_PT_GLOBALS(base_reg) &bslash;&n;        LOAD_PT_PRIV(base_reg, pt_psr, pt_pc, pt_npc)
DECL|macro|STORE_PT_INS
mdefine_line|#define STORE_PT_INS(base_reg) &bslash;&n;        std     %i0, [%base_reg + REGWIN_SZ + PT_I0]; &bslash;&n;        std     %i2, [%base_reg + REGWIN_SZ + PT_I2]; &bslash;&n;        std     %i4, [%base_reg + REGWIN_SZ + PT_I4]; &bslash;&n;        std     %i6, [%base_reg + REGWIN_SZ + PT_I6];
DECL|macro|STORE_PT_GLOBALS
mdefine_line|#define STORE_PT_GLOBALS(base_reg) &bslash;&n;        st      %g1, [%base_reg + REGWIN_SZ + PT_G1]; &bslash;&n;        std     %g2, [%base_reg + REGWIN_SZ + PT_G2]; &bslash;&n;        std     %g4, [%base_reg + REGWIN_SZ + PT_G4]; &bslash;&n;        std     %g6, [%base_reg + REGWIN_SZ + PT_G6];
DECL|macro|STORE_PT_YREG
mdefine_line|#define STORE_PT_YREG(base_reg, scratch) &bslash;&n;        rd      %y, %scratch; &bslash;&n;        st      %scratch, [%base_reg + REGWIN_SZ + PT_Y];
DECL|macro|STORE_PT_PRIV
mdefine_line|#define STORE_PT_PRIV(base_reg, pt_psr, pt_pc, pt_npc) &bslash;&n;        st      %pt_psr, [%base_reg + REGWIN_SZ + PT_PSR]; &bslash;&n;        st      %pt_pc,  [%base_reg + REGWIN_SZ + PT_PC]; &bslash;&n;        st      %pt_npc, [%base_reg + REGWIN_SZ + PT_NPC];
DECL|macro|STORE_PT_ALL
mdefine_line|#define STORE_PT_ALL(base_reg, reg_psr, reg_pc, reg_npc, g_scratch) &bslash;&n;        STORE_PT_PRIV(base_reg, reg_psr, reg_pc, reg_npc) &bslash;&n;        STORE_PT_GLOBALS(base_reg) &bslash;&n;        STORE_PT_YREG(base_reg, g_scratch) &bslash;&n;        STORE_PT_INS(base_reg)
DECL|macro|SAVE_BOLIXED_USER_STACK
mdefine_line|#define SAVE_BOLIXED_USER_STACK(cur_reg, scratch) &bslash;&n;        ld       [%cur_reg + AOFF_task_thread + AOFF_thread_w_saved], %scratch; &bslash;&n;        sll      %scratch, 2, %scratch; &bslash;&n;        add      %scratch, %cur_reg, %scratch; &bslash;&n;        st       %sp, [%scratch + AOFF_task_thread + AOFF_thread_rwbuf_stkptrs]; &bslash;&n;        sub      %scratch, %cur_reg, %scratch; &bslash;&n;        sll      %scratch, 4, %scratch; &bslash;&n;        add      %scratch, %cur_reg, %scratch; &bslash;&n;        STORE_WINDOW(scratch + AOFF_task_thread + AOFF_thread_reg_window); &bslash;&n;        sub      %scratch, %cur_reg, %scratch; &bslash;&n;        srl      %scratch, 6, %scratch; &bslash;&n;        add      %scratch, 1, %scratch; &bslash;&n;        st       %scratch, [%cur_reg + AOFF_task_thread + AOFF_thread_w_saved];
macro_line|#ifdef CONFIG_SMP
DECL|macro|LOAD_CURRENT4M
mdefine_line|#define LOAD_CURRENT4M(dest_reg, idreg) &bslash;&n;        rd       %tbr, %idreg; &bslash;&n;&t;sethi    %hi(C_LABEL(current_set)), %dest_reg; &bslash;&n;        srl      %idreg, 10, %idreg; &bslash;&n;&t;or       %dest_reg, %lo(C_LABEL(current_set)), %dest_reg; &bslash;&n;&t;and      %idreg, 0xc, %idreg; &bslash;&n;&t;ld       [%idreg + %dest_reg], %dest_reg;
multiline_comment|/* Sliiick. We have a Linux current register :) -jj */
DECL|macro|LOAD_CURRENT4D
mdefine_line|#define LOAD_CURRENT4D(dest_reg) &bslash;&n;&t;lda&t; [%g0] ASI_M_VIKING_TMP2, %dest_reg;
multiline_comment|/* Blackbox - take care with this... - check smp4m and smp4d before changing this. */
DECL|macro|LOAD_CURRENT
mdefine_line|#define LOAD_CURRENT(dest_reg, idreg) &t;&t;&t;&t;&t;&bslash;&n;&t;sethi&t; %hi(___b_load_current), %idreg;&t;&t;&t;&bslash;&n;&t;sethi    %hi(C_LABEL(current_set)), %dest_reg; &t;&t;&t;&bslash;&n;&t;sethi    %hi(C_LABEL(boot_cpu_id4)), %idreg; &t;&t;&t;&bslash;&n;&t;or       %dest_reg, %lo(C_LABEL(current_set)), %dest_reg; &t;&bslash;&n;&t;ldub&t; [%idreg + %lo(C_LABEL(boot_cpu_id4))], %idreg;&t;&t;&bslash;&n;&t;ld       [%idreg + %dest_reg], %dest_reg;
macro_line|#else
DECL|macro|LOAD_CURRENT
mdefine_line|#define LOAD_CURRENT(dest_reg, idreg) &bslash;&n;        sethi    %hi(C_LABEL(current_set)), %idreg; &bslash;&n;        ld       [%idreg + %lo(C_LABEL(current_set))], %dest_reg;
macro_line|#endif
macro_line|#endif /* !(_SPARC_WINMACRO_H) */
eof
