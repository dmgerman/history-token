multiline_comment|/*&n; * Copyright (C) 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; * linux/arch/mips/vr4181/common/irq.c&n; *&t;Completely re-written to use the new irq.c&n; *&n; * Credits to Bradley D. LaRonde and Michael Klar for writing the original&n; * irq.c file which was derived from the common irq.c file.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/gdb-stub.h&gt;
macro_line|#include &lt;asm/vr4181/vr4181.h&gt;
multiline_comment|/*&n; * Strategy:&n; *&n; * We essentially have three irq controllers, CPU, system, and gpio.&n; *&n; * CPU irq controller is taken care by arch/mips/kernel/irq_cpu.c and&n; * CONFIG_IRQ_CPU config option.&n; *&n; * We here provide sys_irq and gpio_irq controller code.&n; */
DECL|variable|sys_irq_base
r_static
r_int
id|sys_irq_base
suffix:semicolon
DECL|variable|gpio_irq_base
r_static
r_int
id|gpio_irq_base
suffix:semicolon
multiline_comment|/* ---------------------- sys irq ------------------------ */
r_static
r_void
DECL|function|sys_irq_enable
id|sys_irq_enable
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_sub_assign
id|sys_irq_base
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
l_int|16
)paren
(brace
op_star
id|VR4181_MSYSINT1REG
op_or_assign
(paren
id|u16
)paren
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
)brace
r_else
(brace
id|irq
op_sub_assign
l_int|16
suffix:semicolon
op_star
id|VR4181_MSYSINT2REG
op_or_assign
(paren
id|u16
)paren
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|sys_irq_disable
id|sys_irq_disable
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_sub_assign
id|sys_irq_base
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
l_int|16
)paren
(brace
op_star
id|VR4181_MSYSINT1REG
op_and_assign
op_complement
(paren
(paren
id|u16
)paren
(paren
l_int|1
op_lshift
id|irq
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|irq
op_sub_assign
l_int|16
suffix:semicolon
op_star
id|VR4181_MSYSINT2REG
op_and_assign
op_complement
(paren
(paren
id|u16
)paren
(paren
l_int|1
op_lshift
id|irq
)paren
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
r_int
DECL|function|sys_irq_startup
id|sys_irq_startup
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|sys_irq_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|sys_irq_shutdown
mdefine_line|#define sys_irq_shutdown&t;sys_irq_disable
DECL|macro|sys_irq_ack
mdefine_line|#define sys_irq_ack&t;&t;sys_irq_disable
r_static
r_void
DECL|function|sys_irq_end
id|sys_irq_end
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
(brace
id|sys_irq_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
)brace
DECL|variable|sys_irq_controller
r_static
id|hw_irq_controller
id|sys_irq_controller
op_assign
(brace
l_string|&quot;vr4181_sys_irq&quot;
comma
id|sys_irq_startup
comma
id|sys_irq_shutdown
comma
id|sys_irq_enable
comma
id|sys_irq_disable
comma
id|sys_irq_ack
comma
id|sys_irq_end
comma
l_int|NULL
multiline_comment|/* no affinity stuff for UP */
)brace
suffix:semicolon
multiline_comment|/* ---------------------- gpio irq ------------------------ */
multiline_comment|/* gpio irq lines use reverse logic */
r_static
r_void
DECL|function|gpio_irq_enable
id|gpio_irq_enable
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_sub_assign
id|gpio_irq_base
suffix:semicolon
op_star
id|VR4181_GPINTMSK
op_and_assign
op_complement
(paren
(paren
id|u16
)paren
(paren
l_int|1
op_lshift
id|irq
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|gpio_irq_disable
id|gpio_irq_disable
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq
op_sub_assign
id|gpio_irq_base
suffix:semicolon
op_star
id|VR4181_GPINTMSK
op_or_assign
(paren
id|u16
)paren
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|gpio_irq_startup
id|gpio_irq_startup
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|gpio_irq_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
id|irq
op_sub_assign
id|gpio_irq_base
suffix:semicolon
op_star
id|VR4181_GPINTEN
op_or_assign
(paren
id|u16
)paren
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|gpio_irq_shutdown
id|gpio_irq_shutdown
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|gpio_irq_disable
c_func
(paren
id|irq
)paren
suffix:semicolon
id|irq
op_sub_assign
id|gpio_irq_base
suffix:semicolon
op_star
id|VR4181_GPINTEN
op_and_assign
op_complement
(paren
(paren
id|u16
)paren
(paren
l_int|1
op_lshift
id|irq
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|gpio_irq_ack
id|gpio_irq_ack
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u16
id|irqtype
suffix:semicolon
id|u16
id|irqshift
suffix:semicolon
id|gpio_irq_disable
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/* we clear interrupt if it is edge triggered */
id|irq
op_sub_assign
id|gpio_irq_base
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
l_int|8
)paren
(brace
id|irqtype
op_assign
op_star
id|VR4181_GPINTTYPL
suffix:semicolon
id|irqshift
op_assign
l_int|2
op_lshift
(paren
id|irq
op_star
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
id|irqtype
op_assign
op_star
id|VR4181_GPINTTYPH
suffix:semicolon
id|irqshift
op_assign
l_int|2
op_lshift
(paren
(paren
id|irq
op_minus
l_int|8
)paren
op_star
l_int|2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irqtype
op_amp
id|irqshift
)paren
)paren
(brace
op_star
id|VR4181_GPINTSTAT
op_assign
(paren
id|u16
)paren
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|gpio_irq_end
id|gpio_irq_end
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
(brace
id|gpio_irq_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
)brace
DECL|variable|gpio_irq_controller
r_static
id|hw_irq_controller
id|gpio_irq_controller
op_assign
(brace
l_string|&quot;vr4181_gpio_irq&quot;
comma
id|gpio_irq_startup
comma
id|gpio_irq_shutdown
comma
id|gpio_irq_enable
comma
id|gpio_irq_disable
comma
id|gpio_irq_ack
comma
id|gpio_irq_end
comma
l_int|NULL
multiline_comment|/* no affinity stuff for UP */
)brace
suffix:semicolon
multiline_comment|/* ---------------------  IRQ init stuff ---------------------- */
r_extern
id|asmlinkage
r_void
id|vr4181_handle_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|breakpoint
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|setup_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqaction
op_star
id|irqaction
)paren
suffix:semicolon
r_extern
r_void
id|mips_cpu_irq_init
c_func
(paren
id|u32
id|irq_base
)paren
suffix:semicolon
DECL|variable|cascade
r_static
r_struct
id|irqaction
id|cascade
op_assign
(brace
id|no_action
comma
id|SA_INTERRUPT
comma
id|CPU_MASK_NONE
comma
l_string|&quot;cascade&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|reserved
r_static
r_struct
id|irqaction
id|reserved
op_assign
(brace
id|no_action
comma
id|SA_INTERRUPT
comma
id|CPU_MASK_NONE
comma
l_string|&quot;cascade&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|arch_init_irq
r_void
id|__init
id|arch_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|0
comma
id|vr4181_handle_irq
)paren
suffix:semicolon
multiline_comment|/* init CPU irqs */
id|mips_cpu_irq_init
c_func
(paren
id|VR4181_CPU_IRQ_BASE
)paren
suffix:semicolon
multiline_comment|/* init sys irqs */
id|sys_irq_base
op_assign
id|VR4181_SYS_IRQ_BASE
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|sys_irq_base
suffix:semicolon
id|i
OL
id|sys_irq_base
op_plus
id|VR4181_NUM_SYS_IRQ
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|action
op_assign
l_int|NULL
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|sys_irq_controller
suffix:semicolon
)brace
multiline_comment|/* init gpio irqs */
id|gpio_irq_base
op_assign
id|VR4181_GPIO_IRQ_BASE
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|gpio_irq_base
suffix:semicolon
id|i
OL
id|gpio_irq_base
op_plus
id|VR4181_NUM_GPIO_IRQ
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|action
op_assign
l_int|NULL
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|gpio_irq_controller
suffix:semicolon
)brace
multiline_comment|/* Default all ICU IRQs to off ... */
op_star
id|VR4181_MSYSINT1REG
op_assign
l_int|0
suffix:semicolon
op_star
id|VR4181_MSYSINT2REG
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* We initialize the level 2 ICU registers to all bits disabled. */
op_star
id|VR4181_MPIUINTREG
op_assign
l_int|0
suffix:semicolon
op_star
id|VR4181_MAIUINTREG
op_assign
l_int|0
suffix:semicolon
op_star
id|VR4181_MKIUINTREG
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* disable all GPIO intrs */
op_star
id|VR4181_GPINTMSK
op_assign
l_int|0xffff
suffix:semicolon
multiline_comment|/* vector handler.  What these do is register the IRQ as non-sharable */
id|setup_irq
c_func
(paren
id|VR4181_IRQ_INT0
comma
op_amp
id|cascade
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
id|VR4181_IRQ_GIU
comma
op_amp
id|cascade
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * RTC interrupts are interesting.  They have two destinations.&n;&t; * One is at sys irq controller, and the other is at CPU IP3 and IP4.&n;&t; * RTC timer is used as system timer.&n;&t; * We enable them here, but timer routine will register later&n;&t; * with CPU IP3/IP4.&n;&t; */
id|setup_irq
c_func
(paren
id|VR4181_IRQ_RTCL1
comma
op_amp
id|reserved
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
id|VR4181_IRQ_RTCL2
comma
op_amp
id|reserved
)paren
suffix:semicolon
)brace
eof
