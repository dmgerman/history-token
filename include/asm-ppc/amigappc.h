multiline_comment|/*&n; * BK Id: SCCS/s.amigappc.h 1.5 05/17/01 18:14:24 cort&n; */
multiline_comment|/*&n;** asm-m68k/amigappc.h -- This header defines some values and pointers for&n;**                        the Phase 5 PowerUp card.&n;**&n;** Copyright 1997, 1998 by Phase5, Germany.&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;** Created: 7/22/97 by Jesper Skov&n;*/
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _M68K_AMIGAPPC_H
DECL|macro|_M68K_AMIGAPPC_H
mdefine_line|#define _M68K_AMIGAPPC_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* #include &lt;asm/system.h&gt; */
DECL|macro|mb
mdefine_line|#define mb()  __asm__ __volatile__ (&quot;sync&quot; : : : &quot;memory&quot;)
DECL|macro|APUS_WRITE
mdefine_line|#define APUS_WRITE(_a_, _v_)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*((volatile unsigned char *)(_a_)) = (_v_));&t;&bslash;&n;&t;mb();&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|APUS_READ
mdefine_line|#define APUS_READ(_a_, _v_)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(_v_) = (*((volatile unsigned char *)(_a_)));&t;&bslash;&n;&t;mb();&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* ndef __ASSEMBLY__ */
multiline_comment|/* Maybe add a [#ifdef WANT_ZTWOBASE] condition to amigahw.h? */
DECL|macro|zTwoBase
mdefine_line|#define zTwoBase (0x80000000)
DECL|macro|APUS_IPL_BASE
mdefine_line|#define APUS_IPL_BASE   &t;(zTwoBase + 0x00f60000)
DECL|macro|APUS_REG_RESET
mdefine_line|#define APUS_REG_RESET    &t;(APUS_IPL_BASE + 0x00)
DECL|macro|APUS_REG_WAITSTATE
mdefine_line|#define APUS_REG_WAITSTATE    &t;(APUS_IPL_BASE + 0x10)
DECL|macro|APUS_REG_SHADOW
mdefine_line|#define APUS_REG_SHADOW    &t;(APUS_IPL_BASE + 0x18)
DECL|macro|APUS_REG_LOCK
mdefine_line|#define APUS_REG_LOCK&t;&t;(APUS_IPL_BASE + 0x20)
DECL|macro|APUS_REG_INT
mdefine_line|#define APUS_REG_INT    &t;(APUS_IPL_BASE + 0x28)
DECL|macro|APUS_IPL_EMU
mdefine_line|#define APUS_IPL_EMU&t;&t;(APUS_IPL_BASE + 0x30)
DECL|macro|APUS_INT_LVL
mdefine_line|#define APUS_INT_LVL&t;&t;(APUS_IPL_BASE + 0x38)
DECL|macro|REGSHADOW_SETRESET
mdefine_line|#define REGSHADOW_SETRESET&t;(0x80)
DECL|macro|REGSHADOW_SELFRESET
mdefine_line|#define REGSHADOW_SELFRESET&t;(0x40)
DECL|macro|REGLOCK_SETRESET
mdefine_line|#define REGLOCK_SETRESET&t;(0x80)
DECL|macro|REGLOCK_BLACKMAGICK1
mdefine_line|#define REGLOCK_BLACKMAGICK1&t;(0x40)
DECL|macro|REGLOCK_BLACKMAGICK2
mdefine_line|#define REGLOCK_BLACKMAGICK2&t;(0x20)
DECL|macro|REGLOCK_BLACKMAGICK3
mdefine_line|#define REGLOCK_BLACKMAGICK3&t;(0x10)
DECL|macro|REGWAITSTATE_SETRESET
mdefine_line|#define REGWAITSTATE_SETRESET&t;(0x80)
DECL|macro|REGWAITSTATE_PPCW
mdefine_line|#define REGWAITSTATE_PPCW&t;(0x08)
DECL|macro|REGWAITSTATE_PPCR
mdefine_line|#define REGWAITSTATE_PPCR&t;(0x04)
DECL|macro|REGRESET_SETRESET
mdefine_line|#define REGRESET_SETRESET&t;(0x80)
DECL|macro|REGRESET_PPCRESET
mdefine_line|#define REGRESET_PPCRESET&t;(0x10)
DECL|macro|REGRESET_M68KRESET
mdefine_line|#define REGRESET_M68KRESET&t;(0x08)
DECL|macro|REGRESET_AMIGARESET
mdefine_line|#define REGRESET_AMIGARESET&t;(0x04)
DECL|macro|REGRESET_AUXRESET
mdefine_line|#define REGRESET_AUXRESET&t;(0x02)
DECL|macro|REGRESET_SCSIRESET
mdefine_line|#define REGRESET_SCSIRESET&t;(0x01)
DECL|macro|REGINT_SETRESET
mdefine_line|#define REGINT_SETRESET&t;&t;(0x80)
DECL|macro|REGINT_ENABLEIPL
mdefine_line|#define REGINT_ENABLEIPL&t;(0x02)
DECL|macro|REGINT_INTMASTER
mdefine_line|#define REGINT_INTMASTER&t;(0x01)
DECL|macro|IPLEMU_SETRESET
mdefine_line|#define IPLEMU_SETRESET&t;&t;(0x80)
DECL|macro|IPLEMU_DISABLEINT
mdefine_line|#define IPLEMU_DISABLEINT&t;(0x40)
DECL|macro|IPLEMU_IPL2
mdefine_line|#define IPLEMU_IPL2&t;&t;(0x20)
DECL|macro|IPLEMU_IPL1
mdefine_line|#define IPLEMU_IPL1&t;&t;(0x10)
DECL|macro|IPLEMU_IPL0
mdefine_line|#define IPLEMU_IPL0&t;&t;(0x08)
DECL|macro|IPLEMU_PPCIPL2
mdefine_line|#define IPLEMU_PPCIPL2&t;&t;(0x04)
DECL|macro|IPLEMU_PPCIPL1
mdefine_line|#define IPLEMU_PPCIPL1&t;&t;(0x02)
DECL|macro|IPLEMU_PPCIPL0
mdefine_line|#define IPLEMU_PPCIPL0&t;&t;(0x01)
DECL|macro|IPLEMU_IPLMASK
mdefine_line|#define IPLEMU_IPLMASK&t;&t;(IPLEMU_PPCIPL2|IPLEMU_PPCIPL1|IPLEMU_PPCIPL0)
DECL|macro|INTLVL_SETRESET
mdefine_line|#define INTLVL_SETRESET         (0x80)
DECL|macro|INTLVL_MASK
mdefine_line|#define INTLVL_MASK             (0x7f)
macro_line|#endif /* _M68k_AMIGAPPC_H */
macro_line|#endif /* __KERNEL__ */
eof
