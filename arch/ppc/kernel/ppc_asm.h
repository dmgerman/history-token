multiline_comment|/*&n; * BK Id: SCCS/s.ppc_asm.h 1.14 07/02/01 22:08:05 paulus&n; */
multiline_comment|/*&n; * arch/ppc/kernel/ppc_asm.h&n; *&n; * Definitions used by various bits of low-level assembly code on PowerPC.&n; *&n; * Copyright (C) 1995-1999 Gary Thomas, Paul Mackerras, Cort Dougan.&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;ppc_asm.tmpl&quot;
macro_line|#include &quot;ppc_defs.h&quot;
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
multiline_comment|/*&n; * Once a version of gas that understands the AltiVec instructions&n; * is freely available, we can do this the normal way...  - paulus&n; */
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
mdefine_line|#define SYNC &bslash;&n;&t;sync; &bslash;&n;&t;isync
macro_line|#else
DECL|macro|SYNC
mdefine_line|#define&t;SYNC
macro_line|#endif
macro_line|#ifndef CONFIG_SMP
DECL|macro|TLBSYNC
mdefine_line|#define TLBSYNC
macro_line|#else /* CONFIG_SMP */
DECL|macro|TLBSYNC
mdefine_line|#define TLBSYNC&t;&t;&t;&t;&bslash;&n;&t;tlbsync;&t;&t;&t;&bslash;&n;&t;sync
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/*&n; * This instruction is not implemented on the PPC 603 or 601; however, on&n; * the 403GCX and 405GP tlbia IS defined and tlbie is not.&n; * All of these instructions exist in the 8xx, they have magical powers,&n; * and they must be used.&n; */
macro_line|#if !defined(CONFIG_4xx) &amp;&amp; !defined(CONFIG_8xx)
DECL|macro|tlbia
mdefine_line|#define tlbia&t;&t;&t;&t;&t;&bslash;&n;&t;li&t;r4,1024;&t;&t;&t;&bslash;&n;&t;mtctr&t;r4;&t;&t;&t;&t;&bslash;&n;&t;lis&t;r4,KERNELBASE@h;&t;&t;&bslash;&n;0:&t;tlbie&t;r4;&t;&t;&t;&t;&bslash;&n;&t;addi&t;r4,r4,0x1000;&t;&t;&t;&bslash;&n;&t;bdnz&t;0b
macro_line|#endif
multiline_comment|/*&n; * On APUS (Amiga PowerPC cpu upgrade board), we don&squot;t know the&n; * physical base address of RAM at compile time.&n; */
DECL|macro|tophys
mdefine_line|#define tophys(rd,rs)&t;&t;&t;&t;&bslash;&n;0:&t;addis&t;rd,rs,-KERNELBASE@h;&t;&t;&bslash;&n;&t;.section &quot;.vtop_fixup&quot;,&quot;aw&quot;;&t;&t;&bslash;&n;&t;.align  1;&t;&t;&t;&t;&bslash;&n;&t;.long   0b;&t;&t;&t;&t;&bslash;&n;&t;.previous
DECL|macro|tovirt
mdefine_line|#define tovirt(rd,rs)&t;&t;&t;&t;&bslash;&n;0:&t;addis&t;rd,rs,KERNELBASE@h;&t;&t;&bslash;&n;&t;.section &quot;.ptov_fixup&quot;,&quot;aw&quot;;&t;&t;&bslash;&n;&t;.align  1;&t;&t;&t;&t;&bslash;&n;&t;.long   0b;&t;&t;&t;&t;&bslash;&n;&t;.previous
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
DECL|macro|RFI
mdefine_line|#define&t;RFI&t;&t;rfi
DECL|macro|MTMSRD
mdefine_line|#define MTMSRD(r)&t;mtmsr&t;r
DECL|macro|CLR_TOP32
mdefine_line|#define CLR_TOP32(r)
macro_line|#endif /* CONFIG_PPC64BRIDGE */
multiline_comment|/*&n; * Defines for cache-line size etc.&n; */
macro_line|#if defined(CONFIG_4xx) || defined(CONFIG_8xx)
DECL|macro|CACHE_LINE_SIZE
mdefine_line|#define CACHE_LINE_SIZE&t;&t;16
DECL|macro|LG_CACHE_LINE_SIZE
mdefine_line|#define LG_CACHE_LINE_SIZE&t;4
DECL|macro|MAX_COPY_PREFETCH
mdefine_line|#define MAX_COPY_PREFETCH&t;1
macro_line|#elif !defined(CONFIG_PPC64BRIDGE)
DECL|macro|CACHE_LINE_SIZE
mdefine_line|#define CACHE_LINE_SIZE&t;&t;32
DECL|macro|LG_CACHE_LINE_SIZE
mdefine_line|#define LG_CACHE_LINE_SIZE&t;5
DECL|macro|MAX_COPY_PREFETCH
mdefine_line|#define MAX_COPY_PREFETCH&t;4
macro_line|#else
DECL|macro|CACHE_LINE_SIZE
mdefine_line|#define CACHE_LINE_SIZE&t;&t;128
DECL|macro|LG_CACHE_LINE_SIZE
mdefine_line|#define LG_CACHE_LINE_SIZE&t;7
DECL|macro|MAX_COPY_PREFETCH
mdefine_line|#define MAX_COPY_PREFETCH&t;1
macro_line|#endif /* CONFIG_4xx || CONFIG_8xx */
eof
