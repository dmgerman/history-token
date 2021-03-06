multiline_comment|/*&n; *  linux/include/asm-arm/mach/irq.h&n; *&n; *  Copyright (C) 1995-2000 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_ARM_MACH_IRQ_H
DECL|macro|__ASM_ARM_MACH_IRQ_H
mdefine_line|#define __ASM_ARM_MACH_IRQ_H
r_struct
id|irqdesc
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_struct
id|seq_file
suffix:semicolon
DECL|typedef|irq_handler_t
r_typedef
r_void
(paren
op_star
id|irq_handler_t
)paren
(paren
r_int
r_int
comma
r_struct
id|irqdesc
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|typedef|irq_control_t
r_typedef
r_void
(paren
op_star
id|irq_control_t
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|struct|irqchip
r_struct
id|irqchip
(brace
multiline_comment|/*&n;&t; * Acknowledge the IRQ.&n;&t; * If this is a level-based IRQ, then it is expected to mask the IRQ&n;&t; * as well.&n;&t; */
DECL|member|ack
r_void
(paren
op_star
id|ack
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Mask the IRQ in hardware.&n;&t; */
DECL|member|mask
r_void
(paren
op_star
id|mask
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Unmask the IRQ in hardware.&n;&t; */
DECL|member|unmask
r_void
(paren
op_star
id|unmask
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ask the hardware to re-trigger the IRQ.&n;&t; * Note: This method _must_ _not_ call the interrupt handler.&n;&t; * If you are unable to retrigger the interrupt, do not&n;&t; * provide a function, or if you do, return non-zero.&n;&t; */
DECL|member|retrigger
r_int
(paren
op_star
id|retrigger
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the type of the IRQ.&n;&t; */
DECL|member|type
r_int
(paren
op_star
id|type
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set wakeup-enable on the selected IRQ&n;&t; */
DECL|member|wake
r_int
(paren
op_star
id|wake
)paren
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n;&t; * Route an interrupt to a CPU&n;&t; */
DECL|member|set_cpu
r_void
(paren
op_star
id|set_cpu
)paren
(paren
r_struct
id|irqdesc
op_star
id|desc
comma
r_int
r_int
id|irq
comma
r_int
r_int
id|cpu
)paren
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|irqdesc
r_struct
id|irqdesc
(brace
DECL|member|handle
id|irq_handler_t
id|handle
suffix:semicolon
DECL|member|chip
r_struct
id|irqchip
op_star
id|chip
suffix:semicolon
DECL|member|action
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
DECL|member|pend
r_struct
id|list_head
id|pend
suffix:semicolon
DECL|member|chipdata
r_void
op_star
id|chipdata
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|disable_depth
r_int
r_int
id|disable_depth
suffix:semicolon
DECL|member|triggered
r_int
r_int
id|triggered
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* IRQ has occurred&t;      */
DECL|member|running
r_int
r_int
id|running
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* IRQ is running             */
DECL|member|pending
r_int
r_int
id|pending
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* IRQ is pending&t;      */
DECL|member|probing
r_int
r_int
id|probing
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* IRQ in use for a probe     */
DECL|member|probe_ok
r_int
r_int
id|probe_ok
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* IRQ can be used for probe  */
DECL|member|valid
r_int
r_int
id|valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* IRQ claimable&t;      */
DECL|member|noautoenable
r_int
r_int
id|noautoenable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* don&squot;t automatically enable IRQ */
DECL|member|unused
r_int
r_int
id|unused
suffix:colon
l_int|25
suffix:semicolon
DECL|member|procdir
r_struct
id|proc_dir_entry
op_star
id|procdir
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|member|affinity
id|cpumask_t
id|affinity
suffix:semicolon
DECL|member|cpu
r_int
r_int
id|cpu
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * IRQ lock detection&n;&t; */
DECL|member|lck_cnt
r_int
r_int
id|lck_cnt
suffix:semicolon
DECL|member|lck_pc
r_int
r_int
id|lck_pc
suffix:semicolon
DECL|member|lck_jif
r_int
r_int
id|lck_jif
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|irqdesc
id|irq_desc
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * This is internal.  Do not use it.&n; */
r_extern
r_void
(paren
op_star
id|init_arch_irq
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|init_FIQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|show_fiq_list
c_func
(paren
r_struct
id|seq_file
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_void
id|__set_irq_handler
c_func
(paren
r_int
r_int
id|irq
comma
id|irq_handler_t
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * External stuff.&n; */
DECL|macro|set_irq_handler
mdefine_line|#define set_irq_handler(irq,handler)&t;&t;__set_irq_handler(irq,handler,0)
DECL|macro|set_irq_chained_handler
mdefine_line|#define set_irq_chained_handler(irq,handler)&t;__set_irq_handler(irq,handler,1)
DECL|macro|set_irq_data
mdefine_line|#define set_irq_data(irq,d)&t;&t;&t;do { irq_desc[irq].data = d; } while (0)
DECL|macro|set_irq_chipdata
mdefine_line|#define set_irq_chipdata(irq,d)&t;&t;&t;do { irq_desc[irq].chipdata = d; } while (0)
DECL|macro|get_irq_chipdata
mdefine_line|#define get_irq_chipdata(irq)&t;&t;&t;(irq_desc[irq].chipdata)
r_void
id|set_irq_chip
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqchip
op_star
)paren
suffix:semicolon
r_void
id|set_irq_flags
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
DECL|macro|IRQF_VALID
mdefine_line|#define IRQF_VALID&t;(1 &lt;&lt; 0)
DECL|macro|IRQF_PROBE
mdefine_line|#define IRQF_PROBE&t;(1 &lt;&lt; 1)
DECL|macro|IRQF_NOAUTOEN
mdefine_line|#define IRQF_NOAUTOEN&t;(1 &lt;&lt; 2)
multiline_comment|/*&n; * Built-in IRQ handlers.&n; */
r_void
id|do_level_IRQ
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqdesc
op_star
id|desc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_void
id|do_edge_IRQ
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqdesc
op_star
id|desc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_void
id|do_simple_IRQ
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqdesc
op_star
id|desc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_void
id|do_bad_IRQ
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqdesc
op_star
id|desc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_void
id|dummy_mask_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
macro_line|#endif
eof
