multiline_comment|/* -*- mode: c; c-basic-offset: 8 -*- */
multiline_comment|/* Copyright (C) 2002&n; *&n; * Author: James.Bottomley@HansenPartnership.com&n; *&n; * linux/arch/i386/voyager/irq_vectors.h&n; *&n; * This file provides definitions for the VIC and QIC CPIs&n; */
macro_line|#ifndef _ASM_IRQ_VECTORS_H
DECL|macro|_ASM_IRQ_VECTORS_H
mdefine_line|#define _ASM_IRQ_VECTORS_H
multiline_comment|/*&n; * IDT vectors usable for external interrupt sources start&n; * at 0x20:&n; */
DECL|macro|FIRST_EXTERNAL_VECTOR
mdefine_line|#define FIRST_EXTERNAL_VECTOR&t;0x20
DECL|macro|SYSCALL_VECTOR
mdefine_line|#define SYSCALL_VECTOR&t;&t;0x80
multiline_comment|/*&n; * Vectors 0x20-0x2f are used for ISA interrupts.&n; */
multiline_comment|/* These define the CPIs we use in linux */
DECL|macro|VIC_CPI_LEVEL0
mdefine_line|#define VIC_CPI_LEVEL0&t;&t;&t;0
DECL|macro|VIC_CPI_LEVEL1
mdefine_line|#define VIC_CPI_LEVEL1&t;&t;&t;1
multiline_comment|/* now the fake CPIs */
DECL|macro|VIC_TIMER_CPI
mdefine_line|#define VIC_TIMER_CPI&t;&t;&t;2
DECL|macro|VIC_INVALIDATE_CPI
mdefine_line|#define VIC_INVALIDATE_CPI&t;&t;3
DECL|macro|VIC_RESCHEDULE_CPI
mdefine_line|#define VIC_RESCHEDULE_CPI&t;&t;4
DECL|macro|VIC_ENABLE_IRQ_CPI
mdefine_line|#define VIC_ENABLE_IRQ_CPI&t;&t;5
DECL|macro|VIC_CALL_FUNCTION_CPI
mdefine_line|#define VIC_CALL_FUNCTION_CPI&t;&t;6
multiline_comment|/* Now the QIC CPIs:  Since we don&squot;t need the two initial levels,&n; * these are 2 less than the VIC CPIs */
DECL|macro|QIC_CPI_OFFSET
mdefine_line|#define QIC_CPI_OFFSET&t;&t;&t;1
DECL|macro|QIC_TIMER_CPI
mdefine_line|#define QIC_TIMER_CPI&t;&t;&t;(VIC_TIMER_CPI - QIC_CPI_OFFSET)
DECL|macro|QIC_INVALIDATE_CPI
mdefine_line|#define QIC_INVALIDATE_CPI&t;&t;(VIC_INVALIDATE_CPI - QIC_CPI_OFFSET)
DECL|macro|QIC_RESCHEDULE_CPI
mdefine_line|#define QIC_RESCHEDULE_CPI&t;&t;(VIC_RESCHEDULE_CPI - QIC_CPI_OFFSET)
DECL|macro|QIC_ENABLE_IRQ_CPI
mdefine_line|#define QIC_ENABLE_IRQ_CPI&t;&t;(VIC_ENABLE_IRQ_CPI - QIC_CPI_OFFSET)
DECL|macro|QIC_CALL_FUNCTION_CPI
mdefine_line|#define QIC_CALL_FUNCTION_CPI&t;&t;(VIC_CALL_FUNCTION_CPI - QIC_CPI_OFFSET)
DECL|macro|VIC_START_FAKE_CPI
mdefine_line|#define VIC_START_FAKE_CPI&t;&t;VIC_TIMER_CPI
DECL|macro|VIC_END_FAKE_CPI
mdefine_line|#define VIC_END_FAKE_CPI&t;&t;VIC_CALL_FUNCTION_CPI
multiline_comment|/* this is the SYS_INT CPI. */
DECL|macro|VIC_SYS_INT
mdefine_line|#define VIC_SYS_INT&t;&t;&t;8
DECL|macro|VIC_CMN_INT
mdefine_line|#define VIC_CMN_INT&t;&t;&t;15
multiline_comment|/* This is the boot CPI for alternate processors.  It gets overwritten&n; * by the above once the system has activated all available processors */
DECL|macro|VIC_CPU_BOOT_CPI
mdefine_line|#define VIC_CPU_BOOT_CPI&t;&t;VIC_CPI_LEVEL0
DECL|macro|VIC_CPU_BOOT_ERRATA_CPI
mdefine_line|#define VIC_CPU_BOOT_ERRATA_CPI&t;&t;(VIC_CPI_LEVEL0 + 8)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 224
macro_line|#ifndef __ASSEMBLY__
r_extern
id|asmlinkage
r_void
id|vic_cpi_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|vic_sys_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|vic_cmn_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|qic_timer_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|qic_invalidate_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|qic_reschedule_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|qic_enable_irq_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|qic_call_function_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_IRQ_VECTORS_H */
eof
