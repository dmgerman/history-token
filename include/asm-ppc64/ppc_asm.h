multiline_comment|/*&n; * arch/ppc64/kernel/ppc_asm.h&n; *&n; * Definitions used by various bits of low-level assembly code on PowerPC.&n; *&n; * Copyright (C) 1995-1999 Gary Thomas, Paul Mackerras, Cort Dougan.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
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
multiline_comment|/* Condition Register Bit Fields */
DECL|macro|cr0
mdefine_line|#define&t;cr0&t;0
DECL|macro|cr1
mdefine_line|#define&t;cr1&t;1
DECL|macro|cr2
mdefine_line|#define&t;cr2&t;2
DECL|macro|cr3
mdefine_line|#define&t;cr3&t;3
DECL|macro|cr4
mdefine_line|#define&t;cr4&t;4
DECL|macro|cr5
mdefine_line|#define&t;cr5&t;5
DECL|macro|cr6
mdefine_line|#define&t;cr6&t;6
DECL|macro|cr7
mdefine_line|#define&t;cr7&t;7
multiline_comment|/* General Purpose Registers (GPRs) */
DECL|macro|r0
mdefine_line|#define&t;r0&t;0
DECL|macro|r1
mdefine_line|#define&t;r1&t;1
DECL|macro|r2
mdefine_line|#define&t;r2&t;2
DECL|macro|r3
mdefine_line|#define&t;r3&t;3
DECL|macro|r4
mdefine_line|#define&t;r4&t;4
DECL|macro|r5
mdefine_line|#define&t;r5&t;5
DECL|macro|r6
mdefine_line|#define&t;r6&t;6
DECL|macro|r7
mdefine_line|#define&t;r7&t;7
DECL|macro|r8
mdefine_line|#define&t;r8&t;8
DECL|macro|r9
mdefine_line|#define&t;r9&t;9
DECL|macro|r10
mdefine_line|#define&t;r10&t;10
DECL|macro|r11
mdefine_line|#define&t;r11&t;11
DECL|macro|r12
mdefine_line|#define&t;r12&t;12
DECL|macro|r13
mdefine_line|#define&t;r13&t;13
DECL|macro|r14
mdefine_line|#define&t;r14&t;14
DECL|macro|r15
mdefine_line|#define&t;r15&t;15
DECL|macro|r16
mdefine_line|#define&t;r16&t;16
DECL|macro|r17
mdefine_line|#define&t;r17&t;17
DECL|macro|r18
mdefine_line|#define&t;r18&t;18
DECL|macro|r19
mdefine_line|#define&t;r19&t;19
DECL|macro|r20
mdefine_line|#define&t;r20&t;20
DECL|macro|r21
mdefine_line|#define&t;r21&t;21
DECL|macro|r22
mdefine_line|#define&t;r22&t;22
DECL|macro|r23
mdefine_line|#define&t;r23&t;23
DECL|macro|r24
mdefine_line|#define&t;r24&t;24
DECL|macro|r25
mdefine_line|#define&t;r25&t;25
DECL|macro|r26
mdefine_line|#define&t;r26&t;26
DECL|macro|r27
mdefine_line|#define&t;r27&t;27
DECL|macro|r28
mdefine_line|#define&t;r28&t;28
DECL|macro|r29
mdefine_line|#define&t;r29&t;29
DECL|macro|r30
mdefine_line|#define&t;r30&t;30
DECL|macro|r31
mdefine_line|#define&t;r31&t;31
multiline_comment|/* Floating Point Registers (FPRs) */
DECL|macro|fr0
mdefine_line|#define&t;fr0&t;0
DECL|macro|fr1
mdefine_line|#define&t;fr1&t;1
DECL|macro|fr2
mdefine_line|#define&t;fr2&t;2
DECL|macro|fr3
mdefine_line|#define&t;fr3&t;3
DECL|macro|fr4
mdefine_line|#define&t;fr4&t;4
DECL|macro|fr5
mdefine_line|#define&t;fr5&t;5
DECL|macro|fr6
mdefine_line|#define&t;fr6&t;6
DECL|macro|fr7
mdefine_line|#define&t;fr7&t;7
DECL|macro|fr8
mdefine_line|#define&t;fr8&t;8
DECL|macro|fr9
mdefine_line|#define&t;fr9&t;9
DECL|macro|fr10
mdefine_line|#define&t;fr10&t;10
DECL|macro|fr11
mdefine_line|#define&t;fr11&t;11
DECL|macro|fr12
mdefine_line|#define&t;fr12&t;12
DECL|macro|fr13
mdefine_line|#define&t;fr13&t;13
DECL|macro|fr14
mdefine_line|#define&t;fr14&t;14
DECL|macro|fr15
mdefine_line|#define&t;fr15&t;15
DECL|macro|fr16
mdefine_line|#define&t;fr16&t;16
DECL|macro|fr17
mdefine_line|#define&t;fr17&t;17
DECL|macro|fr18
mdefine_line|#define&t;fr18&t;18
DECL|macro|fr19
mdefine_line|#define&t;fr19&t;19
DECL|macro|fr20
mdefine_line|#define&t;fr20&t;20
DECL|macro|fr21
mdefine_line|#define&t;fr21&t;21
DECL|macro|fr22
mdefine_line|#define&t;fr22&t;22
DECL|macro|fr23
mdefine_line|#define&t;fr23&t;23
DECL|macro|fr24
mdefine_line|#define&t;fr24&t;24
DECL|macro|fr25
mdefine_line|#define&t;fr25&t;25
DECL|macro|fr26
mdefine_line|#define&t;fr26&t;26
DECL|macro|fr27
mdefine_line|#define&t;fr27&t;27
DECL|macro|fr28
mdefine_line|#define&t;fr28&t;28
DECL|macro|fr29
mdefine_line|#define&t;fr29&t;29
DECL|macro|fr30
mdefine_line|#define&t;fr30&t;30
DECL|macro|fr31
mdefine_line|#define&t;fr31&t;31
DECL|macro|vr0
mdefine_line|#define&t;vr0&t;0
DECL|macro|vr1
mdefine_line|#define&t;vr1&t;1
DECL|macro|vr2
mdefine_line|#define&t;vr2&t;2
DECL|macro|vr3
mdefine_line|#define&t;vr3&t;3
DECL|macro|vr4
mdefine_line|#define&t;vr4&t;4
DECL|macro|vr5
mdefine_line|#define&t;vr5&t;5
DECL|macro|vr6
mdefine_line|#define&t;vr6&t;6
DECL|macro|vr7
mdefine_line|#define&t;vr7&t;7
DECL|macro|vr8
mdefine_line|#define&t;vr8&t;8
DECL|macro|vr9
mdefine_line|#define&t;vr9&t;9
DECL|macro|vr10
mdefine_line|#define&t;vr10&t;10
DECL|macro|vr11
mdefine_line|#define&t;vr11&t;11
DECL|macro|vr12
mdefine_line|#define&t;vr12&t;12
DECL|macro|vr13
mdefine_line|#define&t;vr13&t;13
DECL|macro|vr14
mdefine_line|#define&t;vr14&t;14
DECL|macro|vr15
mdefine_line|#define&t;vr15&t;15
DECL|macro|vr16
mdefine_line|#define&t;vr16&t;16
DECL|macro|vr17
mdefine_line|#define&t;vr17&t;17
DECL|macro|vr18
mdefine_line|#define&t;vr18&t;18
DECL|macro|vr19
mdefine_line|#define&t;vr19&t;19
DECL|macro|vr20
mdefine_line|#define&t;vr20&t;20
DECL|macro|vr21
mdefine_line|#define&t;vr21&t;21
DECL|macro|vr22
mdefine_line|#define&t;vr22&t;22
DECL|macro|vr23
mdefine_line|#define&t;vr23&t;23
DECL|macro|vr24
mdefine_line|#define&t;vr24&t;24
DECL|macro|vr25
mdefine_line|#define&t;vr25&t;25
DECL|macro|vr26
mdefine_line|#define&t;vr26&t;26
DECL|macro|vr27
mdefine_line|#define&t;vr27&t;27
DECL|macro|vr28
mdefine_line|#define&t;vr28&t;28
DECL|macro|vr29
mdefine_line|#define&t;vr29&t;29
DECL|macro|vr30
mdefine_line|#define&t;vr30&t;30
DECL|macro|vr31
mdefine_line|#define&t;vr31&t;31
eof
