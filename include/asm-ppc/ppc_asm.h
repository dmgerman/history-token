multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * include/asm-ppc/ppc_asm.h&n; *&n; * Definitions used by various bits of low-level assembly code on PowerPC.&n; *&n; * Copyright (C) 1995-1999 Gary Thomas, Paul Mackerras, Cort Dougan.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Macros for storing registers into and loading registers from&n; * exception frames.&n; */
DECL|macro|SAVE_GPR
mdefine_line|#define SAVE_GPR(n, base)&t;stw&t;n,GPR0+4*(n)(base)
DECL|macro|SAVE_2GPRS
mdefine_line|#define SAVE_2GPRS(n, base)&t;SAVE_GPR(n, base); SAVE_GPR(n+1, base)
DECL|macro|SAVE_4GPRS
mdefine_line|#define SAVE_4GPRS(n, base)&t;SAVE_2GPRS(n, base); SAVE_2GPRS(n+2, base)
DECL|macro|SAVE_8GPRS
mdefine_line|#define SAVE_8GPRS(n, base)&t;SAVE_4GPRS(n, base); SAVE_4GPRS(n+4, base)
DECL|macro|SAVE_10GPRS
mdefine_line|#define SAVE_10GPRS(n, base)&t;SAVE_8GPRS(n, base); SAVE_2GPRS(n+8, base)
DECL|macro|REST_GPR
mdefine_line|#define REST_GPR(n, base)&t;lwz&t;n,GPR0+4*(n)(base)
DECL|macro|REST_2GPRS
mdefine_line|#define REST_2GPRS(n, base)&t;REST_GPR(n, base); REST_GPR(n+1, base)
DECL|macro|REST_4GPRS
mdefine_line|#define REST_4GPRS(n, base)&t;REST_2GPRS(n, base); REST_2GPRS(n+2, base)
DECL|macro|REST_8GPRS
mdefine_line|#define REST_8GPRS(n, base)&t;REST_4GPRS(n, base); REST_4GPRS(n+4, base)
DECL|macro|REST_10GPRS
mdefine_line|#define REST_10GPRS(n, base)&t;REST_8GPRS(n, base); REST_2GPRS(n+8, base)
DECL|macro|SAVE_NVGPRS
mdefine_line|#define SAVE_NVGPRS(base)&t;SAVE_GPR(13, base); SAVE_8GPRS(14, base); &bslash;&n;&t;&t;&t;&t;SAVE_10GPRS(22, base)
DECL|macro|REST_NVGPRS
mdefine_line|#define REST_NVGPRS(base)&t;REST_GPR(13, base); REST_8GPRS(14, base); &bslash;&n;&t;&t;&t;&t;REST_10GPRS(22, base)
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
multiline_comment|/*&n; * Once a version of gas that understands the AltiVec instructions&n; */
DECL|macro|LVX
mdefine_line|#define LVX(r,a,b)&t;.long&t;(31&lt;&lt;26)+((r)&lt;&lt;21)+((a)&lt;&lt;16)+((b)&lt;&lt;11)+(103&lt;&lt;1)
DECL|macro|STVX
mdefine_line|#define STVX(r,a,b)&t;.long&t;(31&lt;&lt;26)+((r)&lt;&lt;21)+((a)&lt;&lt;16)+((b)&lt;&lt;11)+(231&lt;&lt;1)
DECL|macro|MFVSCR
mdefine_line|#define MFVSCR(r)&t;.long&t;(4&lt;&lt;26)+((r)&lt;&lt;21)+(770&lt;&lt;1)
DECL|macro|MTVSCR
mdefine_line|#define MTVSCR(r)&t;.long&t;(4&lt;&lt;26)+((r)&lt;&lt;11)+(802&lt;&lt;1)
DECL|macro|SAVE_VR
mdefine_line|#define SAVE_VR(n,b,base)&t;li b,THREAD_VR0+(16*(n)); STVX(n,b,base)
DECL|macro|SAVE_2VR
mdefine_line|#define SAVE_2VR(n,b,base)&t;SAVE_VR(n,b,base); SAVE_VR(n+1,b,base) 
DECL|macro|SAVE_4VR
mdefine_line|#define SAVE_4VR(n,b,base)&t;SAVE_2VR(n,b,base); SAVE_2VR(n+2,b,base) 
DECL|macro|SAVE_8VR
mdefine_line|#define SAVE_8VR(n,b,base)&t;SAVE_4VR(n,b,base); SAVE_4VR(n+4,b,base) 
DECL|macro|SAVE_16VR
mdefine_line|#define SAVE_16VR(n,b,base)&t;SAVE_8VR(n,b,base); SAVE_8VR(n+8,b,base)
DECL|macro|SAVE_32VR
mdefine_line|#define SAVE_32VR(n,b,base)&t;SAVE_16VR(n,b,base); SAVE_16VR(n+16,b,base)
DECL|macro|REST_VR
mdefine_line|#define REST_VR(n,b,base)&t;li b,THREAD_VR0+(16*(n)); LVX(n,b,base)
DECL|macro|REST_2VR
mdefine_line|#define REST_2VR(n,b,base)&t;REST_VR(n,b,base); REST_VR(n+1,b,base) 
DECL|macro|REST_4VR
mdefine_line|#define REST_4VR(n,b,base)&t;REST_2VR(n,b,base); REST_2VR(n+2,b,base) 
DECL|macro|REST_8VR
mdefine_line|#define REST_8VR(n,b,base)&t;REST_4VR(n,b,base); REST_4VR(n+4,b,base) 
DECL|macro|REST_16VR
mdefine_line|#define REST_16VR(n,b,base)&t;REST_8VR(n,b,base); REST_8VR(n+8,b,base) 
DECL|macro|REST_32VR
mdefine_line|#define REST_32VR(n,b,base)&t;REST_16VR(n,b,base); REST_16VR(n+16,b,base)
macro_line|#ifdef CONFIG_PPC601_SYNC_FIX
DECL|macro|SYNC
mdefine_line|#define SYNC&t;&t;&t;&t;&bslash;&n;BEGIN_FTR_SECTION&t;&t;&t;&bslash;&n;&t;sync;&t;&t;&t;&t;&bslash;&n;&t;isync;&t;&t;&t;&t;&bslash;&n;END_FTR_SECTION_IFSET(CPU_FTR_601)
DECL|macro|SYNC_601
mdefine_line|#define SYNC_601&t;&t;&t;&bslash;&n;BEGIN_FTR_SECTION&t;&t;&t;&bslash;&n;&t;sync;&t;&t;&t;&t;&bslash;&n;END_FTR_SECTION_IFSET(CPU_FTR_601)
DECL|macro|ISYNC_601
mdefine_line|#define ISYNC_601&t;&t;&t;&bslash;&n;BEGIN_FTR_SECTION&t;&t;&t;&bslash;&n;&t;isync;&t;&t;&t;&t;&bslash;&n;END_FTR_SECTION_IFSET(CPU_FTR_601)
macro_line|#else
DECL|macro|SYNC
mdefine_line|#define&t;SYNC
DECL|macro|SYNC_601
mdefine_line|#define SYNC_601
DECL|macro|ISYNC_601
mdefine_line|#define ISYNC_601
macro_line|#endif
macro_line|#ifndef CONFIG_SMP
DECL|macro|TLBSYNC
mdefine_line|#define TLBSYNC
macro_line|#else /* CONFIG_SMP */
multiline_comment|/* tlbsync is not implemented on 601 */
DECL|macro|TLBSYNC
mdefine_line|#define TLBSYNC&t;&t;&t;&t;&bslash;&n;BEGIN_FTR_SECTION&t;&t;&t;&bslash;&n;&t;tlbsync;&t;&t;&t;&bslash;&n;&t;sync;&t;&t;&t;&t;&bslash;&n;END_FTR_SECTION_IFCLR(CPU_FTR_601)
macro_line|#endif
multiline_comment|/*&n; * This instruction is not implemented on the PPC 603 or 601; however, on&n; * the 403GCX and 405GP tlbia IS defined and tlbie is not.&n; * All of these instructions exist in the 8xx, they have magical powers,&n; * and they must be used.&n; */
macro_line|#if !defined(CONFIG_4xx) &amp;&amp; !defined(CONFIG_8xx)
DECL|macro|tlbia
mdefine_line|#define tlbia&t;&t;&t;&t;&t;&bslash;&n;&t;li&t;r4,1024;&t;&t;&t;&bslash;&n;&t;mtctr&t;r4;&t;&t;&t;&t;&bslash;&n;&t;lis&t;r4,KERNELBASE@h;&t;&t;&bslash;&n;0:&t;tlbie&t;r4;&t;&t;&t;&t;&bslash;&n;&t;addi&t;r4,r4,0x1000;&t;&t;&t;&bslash;&n;&t;bdnz&t;0b
macro_line|#endif
macro_line|#ifndef CONFIG_PPC_ISERIES
multiline_comment|/*&n; * On APUS (Amiga PowerPC cpu upgrade board), we don&squot;t know the&n; * physical base address of RAM at compile time.&n; */
DECL|macro|tophys
mdefine_line|#define tophys(rd,rs)&t;&t;&t;&t;&bslash;&n;0:&t;addis&t;rd,rs,-KERNELBASE@h;&t;&t;&bslash;&n;&t;.section &quot;.vtop_fixup&quot;,&quot;aw&quot;;&t;&t;&bslash;&n;&t;.align  1;&t;&t;&t;&t;&bslash;&n;&t;.long   0b;&t;&t;&t;&t;&bslash;&n;&t;.previous
DECL|macro|tovirt
mdefine_line|#define tovirt(rd,rs)&t;&t;&t;&t;&bslash;&n;0:&t;addis&t;rd,rs,KERNELBASE@h;&t;&t;&bslash;&n;&t;.section &quot;.ptov_fixup&quot;,&quot;aw&quot;;&t;&t;&bslash;&n;&t;.align  1;&t;&t;&t;&t;&bslash;&n;&t;.long   0b;&t;&t;&t;&t;&bslash;&n;&t;.previous
macro_line|#else  /* CONFIG_PPC_ISERIES */
DECL|macro|tophys
mdefine_line|#define tophys(rd,rs)&t;&t;&t;&t;&bslash;&n;&t;mr&t;rd,rs
DECL|macro|tovirt
mdefine_line|#define tovirt(rd,rs)&t;&t;&t;&t;&bslash;&n;&t;mr&t;rd,rs
multiline_comment|/* Macros to adjust thread priority for iSeries hardware multi-threading */
DECL|macro|HMT_LOW
mdefine_line|#define HMT_LOW&t;&t;or 1,1,1
DECL|macro|HMT_MEDIUM
mdefine_line|#define HMT_MEDIUM&t;or 2,2,2
DECL|macro|HMT_HIGH
mdefine_line|#define HMT_HIGH&t;or 3,3,3
macro_line|#endif /* CONFIG_PPC_ISERIES */
multiline_comment|/*&n; * On 64-bit cpus, we use the rfid instruction instead of rfi, but&n; * we then have to make sure we preserve the top 32 bits except for&n; * the 64-bit mode bit, which we clear.&n; */
macro_line|#ifdef CONFIG_PPC64BRIDGE
DECL|macro|FIX_SRR1
mdefine_line|#define&t;FIX_SRR1(ra, rb)&t;&bslash;&n;&t;mr&t;rb,ra;&t;&t;&bslash;&n;&t;mfmsr&t;ra;&t;&t;&bslash;&n;&t;clrldi&t;ra,ra,1;&t;&t;/* turn off 64-bit mode */ &bslash;&n;&t;rldimi&t;ra,rb,0,32
DECL|macro|RFI
mdefine_line|#define&t;RFI&t;&t;.long&t;0x4c000024&t;/* rfid instruction */
DECL|macro|MTMSRD
mdefine_line|#define MTMSRD(r)&t;.long&t;(0x7c000164 + ((r) &lt;&lt; 21))&t;/* mtmsrd */
DECL|macro|CLR_TOP32
mdefine_line|#define CLR_TOP32(r)&t;rlwinm&t;(r),(r),0,0,31&t;/* clear top 32 bits */
macro_line|#else
DECL|macro|FIX_SRR1
mdefine_line|#define FIX_SRR1(ra, rb)
macro_line|#ifndef CONFIG_40x
DECL|macro|RFI
mdefine_line|#define&t;RFI&t;&t;rfi
macro_line|#else
DECL|macro|RFI
mdefine_line|#define RFI&t;&t;rfi; b .&t;/* Prevent prefetch past rfi */
macro_line|#endif
DECL|macro|MTMSRD
mdefine_line|#define MTMSRD(r)&t;mtmsr&t;r
DECL|macro|CLR_TOP32
mdefine_line|#define CLR_TOP32(r)
macro_line|#endif /* CONFIG_PPC64BRIDGE */
macro_line|#ifdef CONFIG_PPC_ISERIES
DECL|macro|HMT_LOW
mdefine_line|#define HMT_LOW&t;&t;or&t;1,1,1
DECL|macro|HMT_MEDIUM
mdefine_line|#define HMT_MEDIUM&t;or&t;2,2,2
DECL|macro|HMT_HIGH
mdefine_line|#define HMT_HIGH  &t;or&t;3,3,3
macro_line|#else /* CONFIG_PPC_ISERIES */
DECL|macro|HMT_LOW
mdefine_line|#define HMT_LOW&t;&t;/* nothing */
DECL|macro|HMT_MEDIUM
mdefine_line|#define HMT_MEDIUM&t;/* nothing */
DECL|macro|HMT_HIGH
mdefine_line|#define HMT_HIGH&t;/* nothing */
macro_line|#endif /* CONFIG_PPC_ISERIES */
macro_line|#ifdef CONFIG_IBM405_ERR77
DECL|macro|PPC405_ERR77
mdefine_line|#define PPC405_ERR77(ra,rb)&t;dcbt&t;ra, rb;
DECL|macro|PPC405_ERR77_SYNC
mdefine_line|#define&t;PPC405_ERR77_SYNC&t;sync;
macro_line|#else
DECL|macro|PPC405_ERR77
mdefine_line|#define PPC405_ERR77(ra,rb)
DECL|macro|PPC405_ERR77_SYNC
mdefine_line|#define PPC405_ERR77_SYNC
macro_line|#endif
multiline_comment|/* The boring bits... */
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
multiline_comment|/* some stab codes */
DECL|macro|N_FUN
mdefine_line|#define N_FUN&t;36
DECL|macro|N_RSYM
mdefine_line|#define N_RSYM&t;64
DECL|macro|N_SLINE
mdefine_line|#define N_SLINE&t;68
DECL|macro|N_SO
mdefine_line|#define N_SO&t;100
eof
