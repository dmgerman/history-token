multiline_comment|/*&n; * MTD primitives for XIP support&n; *&n; * Author:&t;Nicolas Pitre&n; * Created:&t;Nov 2, 2004&n; * Copyright:&t;(C) 2004 MontaVista Software, Inc.&n; *&n; * This XIP support for MTD has been loosely inspired&n; * by an earlier patch authored by David Woodhouse.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * $Id: xip.h,v 1.1 2004/11/05 22:41:06 nico Exp $&n; */
macro_line|#ifndef __LINUX_MTD_XIP_H__
DECL|macro|__LINUX_MTD_XIP_H__
mdefine_line|#define __LINUX_MTD_XIP_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_MTD_XIP
multiline_comment|/*&n; * Function that are modifying the flash state away from array mode must&n; * obviously not be running from flash.  The __xipram is therefore marking&n; * those functions so they get relocated to ram.&n; */
DECL|macro|__xipram
mdefine_line|#define __xipram __attribute__ ((__section__ (&quot;.data&quot;)))
multiline_comment|/*&n; * We really don&squot;t want gcc to guess anything.&n; * We absolutely _need_ proper inlining.&n; */
macro_line|#include &lt;linux/compiler.h&gt;
multiline_comment|/*&n; * Each architecture has to provide the following macros.  They must access&n; * the hardware directly and not rely on any other (XIP) functions since they&n; * won&squot;t be available when used (flash not in array mode).&n; *&n; * xip_irqpending()&n; *&n; * &t;return non zero when any hardware interrupt is pending.&n; *&n; * xip_currtime()&n; *&n; * &t;return a platform specific time reference to be used with&n; * &t;xip_elapsed_since().&n; *&n; * xip_elapsed_since(x)&n; *&n; * &t;return in usecs the elapsed timebetween now and the reference x as&n; * &t;returned by xip_currtime().&n; *&n; * &t;note 1: convertion to usec can be approximated, as long as the&n; * &t;&t;returned value is &lt;= the real elapsed time.&n; * &t;note 2: this should be able to cope with a few seconds without&n; * &t;&t;overflowing.&n; */
macro_line|#if defined(CONFIG_ARCH_SA1100) || defined(CONFIG_ARCH_PXA)
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#ifdef CONFIG_ARCH_PXA
macro_line|#include &lt;asm/arch/pxa-regs.h&gt;
macro_line|#endif
DECL|macro|xip_irqpending
mdefine_line|#define xip_irqpending()&t;(ICIP &amp; ICMR)
multiline_comment|/* we sample OSCR and convert desired delta to usec (1/4 ~= 1000000/3686400) */
DECL|macro|xip_currtime
mdefine_line|#define xip_currtime()&t;&t;(OSCR)
DECL|macro|xip_elapsed_since
mdefine_line|#define xip_elapsed_since(x)&t;(signed)((OSCR - (x)) / 4)
macro_line|#else
macro_line|#error &quot;missing IRQ and timer primitives for XIP MTD support&quot;
macro_line|#endif
multiline_comment|/*&n; * xip_cpu_idle() is used when waiting for a delay equal or larger than&n; * the system timer tick period.  This should put the CPU into idle mode&n; * to save power and to be woken up only when some interrupts are pending.&n; * As above, this should not rely upon standard kernel code.&n; */
macro_line|#if defined(CONFIG_CPU_XSCALE)
DECL|macro|xip_cpu_idle
mdefine_line|#define xip_cpu_idle()  asm volatile (&quot;mcr p14, 0, %0, c7, c0, 0&quot; :: &quot;r&quot; (1))
macro_line|#else
DECL|macro|xip_cpu_idle
mdefine_line|#define xip_cpu_idle()  do { } while (0)
macro_line|#endif
macro_line|#else
DECL|macro|__xipram
mdefine_line|#define __xipram
macro_line|#endif /* CONFIG_MTD_XIP */
macro_line|#endif /* __LINUX_MTD_XIP_H__ */
eof
