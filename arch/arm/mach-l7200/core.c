multiline_comment|/*&n; *  linux/arch/arm/mm/mm-lusl7200.c&n; *&n; *  Copyright (C) 2000 Steve Hill (sjhill@cotw.com)&n; *&n; *  Extra MM routines for L7200 architecture&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/arch/hardware.h&gt;
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
DECL|function|l7200_init_irq
r_static
r_void
id|__init
id|l7200_init_irq
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
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|l7200_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|IO_BASE
comma
id|IO_START
comma
id|IO_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|IO_BASE_2
comma
id|IO_START_2
comma
id|IO_SIZE_2
comma
id|MT_DEVICE
)brace
comma
(brace
id|AUX_BASE
comma
id|AUX_START
comma
id|AUX_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|FLASH1_BASE
comma
id|FLASH1_START
comma
id|FLASH1_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|FLASH2_BASE
comma
id|FLASH2_START
comma
id|FLASH2_SIZE
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
DECL|function|l7200_map_io
r_static
r_void
id|__init
id|l7200_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|l7200_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|l7200_io_desc
)paren
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|L7200
comma
l_string|&quot;LinkUp Systems L7200&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Steve Hill / Scott McConnell&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0xf0000000
comma
l_int|0x80040000
comma
l_int|0xd0000000
)paren
id|MAPIO
c_func
(paren
id|l7200_map_io
)paren
id|INITIRQ
c_func
(paren
id|l7200_init_irq
)paren
id|MACHINE_END
eof
