multiline_comment|/*&n; * include/asm-arm/arch-l7200/irq.h&n; *&n; * Copyright (C) 2000 Rob Scott (rscott@mtrob.fdns.ne&n; *                    Steve Hill (sjhill@cotw.com)&n; *&n; * Changelog:&n; *   01-02-2000&t;RS&t;Created l7200 version, derived from ebsa110 code&n; *   04-15-2000 RS      Made dependent on hardware.h&n; *   05-05-2000 SJH     Complete rewrite&n; */
multiline_comment|/*&n; * IRQ base register&n; */
DECL|macro|IRQ_BASE
mdefine_line|#define&t;IRQ_BASE&t;(IO_BASE_2 + 0x1000)
multiline_comment|/* &n; * Normal IRQ registers&n; */
DECL|macro|IRQ_STATUS
mdefine_line|#define IRQ_STATUS&t;(*(volatile unsigned long *) (IRQ_BASE + 0x000))
DECL|macro|IRQ_RAWSTATUS
mdefine_line|#define IRQ_RAWSTATUS&t;(*(volatile unsigned long *) (IRQ_BASE + 0x004))
DECL|macro|IRQ_ENABLE
mdefine_line|#define IRQ_ENABLE&t;(*(volatile unsigned long *) (IRQ_BASE + 0x008))
DECL|macro|IRQ_ENABLECLEAR
mdefine_line|#define IRQ_ENABLECLEAR&t;(*(volatile unsigned long *) (IRQ_BASE + 0x00c))
DECL|macro|IRQ_SOFT
mdefine_line|#define IRQ_SOFT&t;(*(volatile unsigned long *) (IRQ_BASE + 0x010))
DECL|macro|IRQ_SOURCESEL
mdefine_line|#define IRQ_SOURCESEL&t;(*(volatile unsigned long *) (IRQ_BASE + 0x018))
multiline_comment|/* &n; * Fast IRQ registers&n; */
DECL|macro|FIQ_STATUS
mdefine_line|#define FIQ_STATUS&t;(*(volatile unsigned long *) (IRQ_BASE + 0x100))
DECL|macro|FIQ_RAWSTATUS
mdefine_line|#define FIQ_RAWSTATUS&t;(*(volatile unsigned long *) (IRQ_BASE + 0x104))
DECL|macro|FIQ_ENABLE
mdefine_line|#define FIQ_ENABLE&t;(*(volatile unsigned long *) (IRQ_BASE + 0x108))
DECL|macro|FIQ_ENABLECLEAR
mdefine_line|#define FIQ_ENABLECLEAR&t;(*(volatile unsigned long *) (IRQ_BASE + 0x10c))
DECL|macro|FIQ_SOFT
mdefine_line|#define FIQ_SOFT&t;(*(volatile unsigned long *) (IRQ_BASE + 0x110))
DECL|macro|FIQ_SOURCESEL
mdefine_line|#define FIQ_SOURCESEL&t;(*(volatile unsigned long *) (IRQ_BASE + 0x118))
DECL|macro|fixup_irq
mdefine_line|#define fixup_irq(x) (x)
DECL|function|l7200_mask_irq
r_static
r_void
id|l7200_mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|IRQ_ENABLECLEAR
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
)brace
DECL|function|l7200_unmask_irq
r_static
r_void
id|l7200_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|IRQ_ENABLE
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
)brace
DECL|function|irq_init_irq
r_static
id|__inline__
r_void
id|irq_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|irq
suffix:semicolon
id|IRQ_ENABLECLEAR
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* clear all interrupt enables */
id|FIQ_ENABLECLEAR
op_assign
l_int|0xffffffff
suffix:semicolon
multiline_comment|/* clear all fast interrupt enables */
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
OL
id|NR_IRQS
suffix:semicolon
id|irq
op_increment
)paren
(brace
id|irq_desc
(braket
id|irq
)braket
dot
id|valid
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|probe_ok
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|mask_ack
op_assign
id|l7200_mask_irq
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|mask
op_assign
id|l7200_mask_irq
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|unmask
op_assign
id|l7200_unmask_irq
suffix:semicolon
)brace
id|init_FIQ
c_func
(paren
)paren
suffix:semicolon
)brace
eof
