multiline_comment|/* $Id: irq.h,v 1.32 2000/08/26 02:42:28 anton Exp $&n; * irq.h: IRQ registers on the Sparc.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_IRQ_H
DECL|macro|_SPARC_IRQ_H
mdefine_line|#define _SPARC_IRQ_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/threads.h&gt;     /* For NR_CPUS */
macro_line|#include &lt;asm/system.h&gt;     /* For SUN4M_NCPUS */
macro_line|#include &lt;asm/btfixup.h&gt;
DECL|macro|__irq_ino
mdefine_line|#define __irq_ino(irq) irq
DECL|macro|__irq_pil
mdefine_line|#define __irq_pil(irq) irq
id|BTFIXUPDEF_CALL
c_func
(paren
r_char
op_star
comma
id|__irq_itoa
comma
r_int
r_int
)paren
DECL|macro|__irq_itoa
mdefine_line|#define __irq_itoa(irq) BTFIXUP_CALL(__irq_itoa)(irq)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS    15
multiline_comment|/* Dave Redman (djhr@tadpole.co.uk)&n; * changed these to function pointers.. it saves cycles and will allow&n; * the irq dependencies to be split into different files at a later date&n; * sun4c_irq.c, sun4m_irq.c etc so we could reduce the kernel size.&n; * Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; * Changed these to btfixup entities... It saves cycles :)&n; */
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|disable_irq
comma
r_int
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|enable_irq
comma
r_int
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|disable_pil_irq
comma
r_int
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|enable_pil_irq
comma
r_int
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|clear_clock_irq
comma
r_void
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|clear_profile_irq
comma
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|load_profile_irq
comma
r_int
comma
r_int
r_int
)paren
DECL|macro|disable_irq_nosync
mdefine_line|#define disable_irq_nosync disable_irq
DECL|macro|disable_irq
mdefine_line|#define disable_irq(irq) BTFIXUP_CALL(disable_irq)(irq)
DECL|macro|enable_irq
mdefine_line|#define enable_irq(irq) BTFIXUP_CALL(enable_irq)(irq)
DECL|macro|disable_pil_irq
mdefine_line|#define disable_pil_irq(irq) BTFIXUP_CALL(disable_pil_irq)(irq)
DECL|macro|enable_pil_irq
mdefine_line|#define enable_pil_irq(irq) BTFIXUP_CALL(enable_pil_irq)(irq)
DECL|macro|clear_clock_irq
mdefine_line|#define clear_clock_irq() BTFIXUP_CALL(clear_clock_irq)()
DECL|macro|clear_profile_irq
mdefine_line|#define clear_profile_irq(cpu) BTFIXUP_CALL(clear_profile_irq)(cpu)
DECL|macro|load_profile_irq
mdefine_line|#define load_profile_irq(cpu,limit) BTFIXUP_CALL(load_profile_irq)(cpu,limit)
r_extern
r_void
(paren
op_star
id|init_timers
)paren
(paren
r_void
(paren
op_star
id|lvl10_irq
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
suffix:semicolon
r_extern
r_void
id|claim_ticker14
c_func
(paren
r_void
(paren
op_star
id|irq_handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
id|irq
comma
r_int
r_int
id|timeout
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|set_cpu_int
comma
r_int
comma
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|clear_cpu_int
comma
r_int
comma
r_int
)paren
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|set_irq_udt
comma
r_int
)paren
DECL|macro|set_cpu_int
mdefine_line|#define set_cpu_int(cpu,level) BTFIXUP_CALL(set_cpu_int)(cpu,level)
DECL|macro|clear_cpu_int
mdefine_line|#define clear_cpu_int(cpu,level) BTFIXUP_CALL(clear_cpu_int)(cpu,level)
DECL|macro|set_irq_udt
mdefine_line|#define set_irq_udt(cpu) BTFIXUP_CALL(set_irq_udt)(cpu)
macro_line|#endif
r_extern
r_int
id|request_fast_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|flags
comma
id|__const__
r_char
op_star
id|devname
)paren
suffix:semicolon
multiline_comment|/* On the sun4m, just like the timers, we have both per-cpu and master&n; * interrupt registers.&n; */
multiline_comment|/* These registers are used for sending/receiving irqs from/to&n; * different cpu&squot;s.&n; */
DECL|struct|sun4m_intreg_percpu
r_struct
id|sun4m_intreg_percpu
(brace
DECL|member|tbt
r_int
r_int
id|tbt
suffix:semicolon
multiline_comment|/* Interrupts still pending for this cpu. */
multiline_comment|/* These next two registers are WRITE-ONLY and are only&n;&t; * &quot;on bit&quot; sensitive, &quot;off bits&quot; written have NO affect.&n;&t; */
DECL|member|clear
r_int
r_int
id|clear
suffix:semicolon
multiline_comment|/* Clear this cpus irqs here. */
DECL|member|set
r_int
r_int
id|set
suffix:semicolon
multiline_comment|/* Set this cpus irqs here. */
DECL|member|space
r_int
r_char
id|space
(braket
id|PAGE_SIZE
op_minus
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * djhr&n; * Actually the clear and set fields in this struct are misleading..&n; * according to the SLAVIO manual (and the same applies for the SEC)&n; * the clear field clears bits in the mask which will ENABLE that IRQ&n; * the set field sets bits in the mask to DISABLE the IRQ.&n; *&n; * Also the undirected_xx address in the SLAVIO is defined as&n; * RESERVED and write only..&n; *&n; * DAVEM_NOTE: The SLAVIO only specifies behavior on uniprocessor&n; *             sun4m machines, for MP the layout makes more sense.&n; */
DECL|struct|sun4m_intregs
r_struct
id|sun4m_intregs
(brace
DECL|member|cpu_intregs
r_struct
id|sun4m_intreg_percpu
id|cpu_intregs
(braket
id|SUN4M_NCPUS
)braket
suffix:semicolon
DECL|member|tbt
r_int
r_int
id|tbt
suffix:semicolon
multiline_comment|/* IRQ&squot;s that are still pending. */
DECL|member|irqs
r_int
r_int
id|irqs
suffix:semicolon
multiline_comment|/* Master IRQ bits. */
multiline_comment|/* Again, like the above, two these registers are WRITE-ONLY. */
DECL|member|clear
r_int
r_int
id|clear
suffix:semicolon
multiline_comment|/* Clear master IRQ&squot;s by setting bits here. */
DECL|member|set
r_int
r_int
id|set
suffix:semicolon
multiline_comment|/* Set master IRQ&squot;s by setting bits here. */
multiline_comment|/* This register is both READ and WRITE. */
DECL|member|undirected_target
r_int
r_int
id|undirected_target
suffix:semicolon
multiline_comment|/* Which cpu gets undirected irqs. */
)brace
suffix:semicolon
r_extern
r_struct
id|sun4m_intregs
op_star
id|sun4m_interrupts
suffix:semicolon
multiline_comment|/* &n; * Bit field defines for the interrupt registers on various&n; * Sparc machines.&n; */
multiline_comment|/* The sun4c interrupt register. */
DECL|macro|SUN4C_INT_ENABLE
mdefine_line|#define SUN4C_INT_ENABLE  0x01     /* Allow interrupts. */
DECL|macro|SUN4C_INT_E14
mdefine_line|#define SUN4C_INT_E14     0x80     /* Enable level 14 IRQ. */
DECL|macro|SUN4C_INT_E10
mdefine_line|#define SUN4C_INT_E10     0x20     /* Enable level 10 IRQ. */
DECL|macro|SUN4C_INT_E8
mdefine_line|#define SUN4C_INT_E8      0x10     /* Enable level 8 IRQ. */
DECL|macro|SUN4C_INT_E6
mdefine_line|#define SUN4C_INT_E6      0x08     /* Enable level 6 IRQ. */
DECL|macro|SUN4C_INT_E4
mdefine_line|#define SUN4C_INT_E4      0x04     /* Enable level 4 IRQ. */
DECL|macro|SUN4C_INT_E1
mdefine_line|#define SUN4C_INT_E1      0x02     /* Enable level 1 IRQ. */
multiline_comment|/* Dave Redman (djhr@tadpole.co.uk)&n; * The sun4m interrupt registers.&n; */
DECL|macro|SUN4M_INT_ENABLE
mdefine_line|#define SUN4M_INT_ENABLE  &t;0x80000000
DECL|macro|SUN4M_INT_E14
mdefine_line|#define SUN4M_INT_E14     &t;0x00000080
DECL|macro|SUN4M_INT_E10
mdefine_line|#define SUN4M_INT_E10     &t;0x00080000
DECL|macro|SUN4M_HARD_INT
mdefine_line|#define SUN4M_HARD_INT(x)&t;(0x000000001 &lt;&lt; (x))
DECL|macro|SUN4M_SOFT_INT
mdefine_line|#define SUN4M_SOFT_INT(x)&t;(0x000010000 &lt;&lt; (x))
DECL|macro|SUN4M_INT_MASKALL
mdefine_line|#define&t;SUN4M_INT_MASKALL&t;0x80000000&t;  /* mask all interrupts */
DECL|macro|SUN4M_INT_MODULE_ERR
mdefine_line|#define&t;SUN4M_INT_MODULE_ERR&t;0x40000000&t;  /* module error */
DECL|macro|SUN4M_INT_M2S_WRITE
mdefine_line|#define&t;SUN4M_INT_M2S_WRITE&t;0x20000000&t;  /* write buffer error */
DECL|macro|SUN4M_INT_ECC
mdefine_line|#define&t;SUN4M_INT_ECC&t;&t;0x10000000&t;  /* ecc memory error */
DECL|macro|SUN4M_INT_FLOPPY
mdefine_line|#define&t;SUN4M_INT_FLOPPY&t;0x00400000&t;  /* floppy disk */
DECL|macro|SUN4M_INT_MODULE
mdefine_line|#define&t;SUN4M_INT_MODULE&t;0x00200000&t;  /* module interrupt */
DECL|macro|SUN4M_INT_VIDEO
mdefine_line|#define&t;SUN4M_INT_VIDEO&t;&t;0x00100000&t;  /* onboard video */
DECL|macro|SUN4M_INT_REALTIME
mdefine_line|#define&t;SUN4M_INT_REALTIME&t;0x00080000&t;  /* system timer */
DECL|macro|SUN4M_INT_SCSI
mdefine_line|#define&t;SUN4M_INT_SCSI&t;&t;0x00040000&t;  /* onboard scsi */
DECL|macro|SUN4M_INT_AUDIO
mdefine_line|#define&t;SUN4M_INT_AUDIO&t;&t;0x00020000&t;  /* audio/isdn */
DECL|macro|SUN4M_INT_ETHERNET
mdefine_line|#define&t;SUN4M_INT_ETHERNET&t;0x00010000&t;  /* onboard ethernet */
DECL|macro|SUN4M_INT_SERIAL
mdefine_line|#define&t;SUN4M_INT_SERIAL&t;0x00008000&t;  /* serial ports */
DECL|macro|SUN4M_INT_KBDMS
mdefine_line|#define&t;SUN4M_INT_KBDMS&t;&t;0x00004000&t;  /* keyboard/mouse */
DECL|macro|SUN4M_INT_SBUSBITS
mdefine_line|#define&t;SUN4M_INT_SBUSBITS&t;0x00003F80&t;  /* sbus int bits */
DECL|macro|SUN4M_INT_SBUS
mdefine_line|#define SUN4M_INT_SBUS(x)&t;(1 &lt;&lt; (x+7))
DECL|macro|SUN4M_INT_VME
mdefine_line|#define SUN4M_INT_VME(x)&t;(1 &lt;&lt; (x))
macro_line|#endif
eof
