multiline_comment|/*&n; * arch/ppc/kernel/ppc_asm.h&n; *&n; * Definitions used by various bits of low-level assembly code on PowerPC.&n; *&n; * Copyright (C) 1995-1999 Gary Thomas, Paul Mackerras, Cort Dougan.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;ppc_asm.tmpl&quot;
macro_line|#include &quot;ppc_defs.h&quot;
multiline_comment|/*&n; * Macros for storing registers into and loading registers from&n; * exception frames.&n; */
DECL|macro|SAVE_GPR
mdefine_line|#define SAVE_GPR(n, base)&t;std&t;n,GPR0+8*(n)(base)
DECL|macro|SAVE_2GPRS
mdefine_line|#define SAVE_2GPRS(n, base)&t;SAVE_GPR(n, base); SAVE_GPR(n+1, base)
DECL|macro|SAVE_4GPRS
mdefine_line|#define SAVE_4GPRS(n, base)&t;SAVE_2GPRS(n, base); SAVE_2GPRS(n+2, base)
DECL|macro|SAVE_8GPRS
mdefine_line|#define SAVE_8GPRS(n, base)&t;SAVE_4GPRS(n, base); SAVE_4GPRS(n+4, base)
DECL|macro|SAVE_10GPRS
mdefine_line|#define SAVE_10GPRS(n, base)&t;SAVE_8GPRS(n, base); SAVE_2GPRS(n+8, base)
DECL|macro|REST_GPR
mdefine_line|#define REST_GPR(n, base)&t;ld&t;n,GPR0+8*(n)(base)
DECL|macro|REST_2GPRS
mdefine_line|#define REST_2GPRS(n, base)&t;REST_GPR(n, base); REST_GPR(n+1, base)
DECL|macro|REST_4GPRS
mdefine_line|#define REST_4GPRS(n, base)&t;REST_2GPRS(n, base); REST_2GPRS(n+2, base)
DECL|macro|REST_8GPRS
mdefine_line|#define REST_8GPRS(n, base)&t;REST_4GPRS(n, base); REST_4GPRS(n+4, base)
DECL|macro|REST_10GPRS
mdefine_line|#define REST_10GPRS(n, base)&t;REST_8GPRS(n, base); REST_2GPRS(n+8, base)
DECL|macro|SAVE_FPR
mdefine_line|#define SAVE_FPR(n, base)&t;stfd&t;n,THREAD_FPR0+8*(n)(base)
DECL|macro|SAVE_2FPRS
mdefine_line|#define SAVE_2FPRS(n, base)&t;SAVE_FPR(n, base); SAVE_FPR(n+1, base)
DECL|macro|SAVE_4FPRS
mdefine_line|#define SAVE_4FPRS(n, base)&t;SAVE_2FPRS(n, base); SAVE_2FPRS(n+2, base)
DECL|macro|SAVE_8FPRS
mdefine_line|#define SAVE_8FPRS(n, base)&t;SAVE_4FPRS(n, base); SAVE_4FPRS(n+4, base)
DECL|macro|SAVE_16FPRS
mdefine_line|#define SAVE_16FPRS(n, base)&t;SAVE_8FPRS(n, base); SAVE_8FPRS(n+8, base)
DECL|macro|SAVE_32FPRS
mdefine_line|#define SAVE_32FPRS(n, base)&t;SAVE_16FPRS(n, base); SAVE_16FPRS(n+16, base)
DECL|macro|REST_FPR
mdefine_line|#define REST_FPR(n, base)&t;lfd&t;n,THREAD_FPR0+8*(n)(base)
DECL|macro|REST_2FPRS
mdefine_line|#define REST_2FPRS(n, base)&t;REST_FPR(n, base); REST_FPR(n+1, base)
DECL|macro|REST_4FPRS
mdefine_line|#define REST_4FPRS(n, base)&t;REST_2FPRS(n, base); REST_2FPRS(n+2, base)
DECL|macro|REST_8FPRS
mdefine_line|#define REST_8FPRS(n, base)&t;REST_4FPRS(n, base); REST_4FPRS(n+4, base)
DECL|macro|REST_16FPRS
mdefine_line|#define REST_16FPRS(n, base)&t;REST_8FPRS(n, base); REST_8FPRS(n+8, base)
DECL|macro|REST_32FPRS
mdefine_line|#define REST_32FPRS(n, base)&t;REST_16FPRS(n, base); REST_16FPRS(n+16, base)
DECL|macro|CHECKANYINT
mdefine_line|#define CHECKANYINT(ra,rb)&t;&t;&t;&bslash;&n;&t;mfspr&t;rb,SPRG3;&t;&t;/* Get Paca address */&bslash;&n;&t;ld&t;ra,PACALPPACA+LPPACAANYINT(rb); /* Get pending interrupt flags */&bslash;&n;&t;cmpldi&t;0,ra,0;
multiline_comment|/* Macros to adjust thread priority for Iseries hardware multithreading */
DECL|macro|HMT_LOW
mdefine_line|#define HMT_LOW&t;&t;or 1,1,1
DECL|macro|HMT_MEDIUM
mdefine_line|#define HMT_MEDIUM&t;or 2,2,2
DECL|macro|HMT_HIGH
mdefine_line|#define HMT_HIGH&t;or 3,3,3
multiline_comment|/* Insert the high 32 bits of the MSR into what will be the new&n;   MSR (via SRR1 and rfid)  This preserves the MSR.SF and MSR.ISF&n;   bits. */
DECL|macro|FIX_SRR1
mdefine_line|#define FIX_SRR1(ra, rb)&t;&bslash;&n;&t;mr&t;rb,ra;&t;&t;&bslash;&n;&t;mfmsr&t;ra;&t;&t;&bslash;&n;&t;rldimi&t;ra,rb,0,32
DECL|macro|CLR_TOP32
mdefine_line|#define CLR_TOP32(r)&t;rlwinm&t;(r),(r),0,0,31&t;/* clear top 32 bits */
multiline_comment|/* &n; * LOADADDR( rn, name )&n; *   loads the address of &squot;name&squot; into &squot;rn&squot;&n; *&n; * LOADBASE( rn, name )&n; *   loads the address (less the low 16 bits) of &squot;name&squot; into &squot;rn&squot;&n; *   suitable for base+disp addressing&n; */
DECL|macro|LOADADDR
mdefine_line|#define LOADADDR(rn,name) &bslash;&n;&t;lis&t;rn,name##@highest;&t;&bslash;&n;&t;ori&t;rn,rn,name##@higher;&t;&bslash;&n;&t;rldicr&t;rn,rn,32,31;&t;&t;&bslash;&n;&t;oris&t;rn,rn,name##@h;&t;&t;&bslash;&n;&t;ori&t;rn,rn,name##@l
DECL|macro|LOADBASE
mdefine_line|#define LOADBASE(rn,name) &bslash;&n;&t;lis&t;rn,name@highest;&t;&bslash;&n;&t;ori&t;rn,rn,name@higher;&t;&bslash;&n;&t;rldicr&t;rn,rn,32,31;&t;&t;&bslash;&n;&t;oris&t;rn,rn,name@ha
DECL|macro|SET_REG_TO_CONST
mdefine_line|#define SET_REG_TO_CONST(reg, value)&t;         &t;&bslash;&n;&t;lis     reg,(((value)&gt;&gt;48)&amp;0xFFFF);             &bslash;&n;&t;ori     reg,reg,(((value)&gt;&gt;32)&amp;0xFFFF);         &bslash;&n;&t;rldicr  reg,reg,32,31;                          &bslash;&n;&t;oris    reg,reg,(((value)&gt;&gt;16)&amp;0xFFFF);         &bslash;&n;&t;ori     reg,reg,((value)&amp;0xFFFF);
DECL|macro|SET_REG_TO_LABEL
mdefine_line|#define SET_REG_TO_LABEL(reg, label)&t;         &t;&bslash;&n;&t;lis     reg,(label)@highest;                    &bslash;&n;&t;ori     reg,reg,(label)@higher;                 &bslash;&n;&t;rldicr  reg,reg,32,31;                          &bslash;&n;&t;oris    reg,reg,(label)@h;                      &bslash;&n;&t;ori     reg,reg,(label)@l;
multiline_comment|/* PPPBBB - DRENG  If KERNELBASE is always 0xC0...,&n; * Then we can easily do this with one asm insn. -Peter&n; */
DECL|macro|tophys
mdefine_line|#define tophys(rd,rs)                           &bslash;&n;        lis     rd,((KERNELBASE&gt;&gt;48)&amp;0xFFFF);   &bslash;&n;        rldicr  rd,rd,32,31;                    &bslash;&n;        sub     rd,rs,rd
DECL|macro|tovirt
mdefine_line|#define tovirt(rd,rs)                           &bslash;&n;        lis     rd,((KERNELBASE&gt;&gt;48)&amp;0xFFFF);   &bslash;&n;        rldicr  rd,rd,32,31;                    &bslash;&n;        add     rd,rs,rd
eof
