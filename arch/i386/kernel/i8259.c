macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &lt;asm/arch_hooks.h&gt;
macro_line|#include &lt;asm/i8259.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;io_ports.h&gt;
multiline_comment|/*&n; * This is the &squot;legacy&squot; 8259A Programmable Interrupt Controller,&n; * present in the majority of PC/AT boxes.&n; * plus some generic x86 specific things if generic specifics makes&n; * any sense at all.&n; * this file should become arch/i386/kernel/irq.c when the old irq.c&n; * moves to arch independent land&n; */
DECL|variable|i8259A_lock
id|spinlock_t
id|i8259A_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|end_8259A_irq
r_static
r_void
id|end_8259A_irq
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
op_logical_and
id|irq_desc
(braket
id|irq
)braket
dot
id|action
)paren
id|enable_8259A_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|macro|shutdown_8259A_irq
mdefine_line|#define shutdown_8259A_irq&t;disable_8259A_irq
r_void
id|mask_and_ack_8259A
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|function|startup_8259A_irq
r_int
r_int
id|startup_8259A_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_8259A_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* never anything pending */
)brace
DECL|variable|i8259A_irq_type
r_static
r_struct
id|hw_interrupt_type
id|i8259A_irq_type
op_assign
(brace
l_string|&quot;XT-PIC&quot;
comma
id|startup_8259A_irq
comma
id|shutdown_8259A_irq
comma
id|enable_8259A_irq
comma
id|disable_8259A_irq
comma
id|mask_and_ack_8259A
comma
id|end_8259A_irq
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n; * 8259A PIC functions to handle ISA devices:&n; */
multiline_comment|/*&n; * This contains the irq mask for both 8259A irq controllers,&n; */
DECL|variable|cached_irq_mask
r_int
r_int
id|cached_irq_mask
op_assign
l_int|0xffff
suffix:semicolon
multiline_comment|/*&n; * Not all IRQs can be routed through the IO-APIC, eg. on certain (older)&n; * boards the timer interrupt is not really connected to any IO-APIC pin,&n; * it&squot;s fed to the master 8259A&squot;s IR0 line only.&n; *&n; * Any &squot;1&squot; bit in this mask means the IRQ is routed through the IO-APIC.&n; * this &squot;mixed mode&squot; IRQ handling costs nothing because it&squot;s only used&n; * at IRQ setup time.&n; */
DECL|variable|io_apic_irqs
r_int
r_int
id|io_apic_irqs
suffix:semicolon
DECL|function|disable_8259A_irq
r_void
id|disable_8259A_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8259A_lock
comma
id|flags
)paren
suffix:semicolon
id|cached_irq_mask
op_or_assign
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_amp
l_int|8
)paren
id|outb
c_func
(paren
id|cached_slave_mask
comma
id|PIC_SLAVE_IMR
)paren
suffix:semicolon
r_else
id|outb
c_func
(paren
id|cached_master_mask
comma
id|PIC_MASTER_IMR
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8259A_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|enable_8259A_irq
r_void
id|enable_8259A_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8259A_lock
comma
id|flags
)paren
suffix:semicolon
id|cached_irq_mask
op_and_assign
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_amp
l_int|8
)paren
id|outb
c_func
(paren
id|cached_slave_mask
comma
id|PIC_SLAVE_IMR
)paren
suffix:semicolon
r_else
id|outb
c_func
(paren
id|cached_master_mask
comma
id|PIC_MASTER_IMR
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8259A_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|i8259A_irq_pending
r_int
id|i8259A_irq_pending
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8259A_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
l_int|8
)paren
id|ret
op_assign
id|inb
c_func
(paren
id|PIC_MASTER_CMD
)paren
op_amp
id|mask
suffix:semicolon
r_else
id|ret
op_assign
id|inb
c_func
(paren
id|PIC_SLAVE_CMD
)paren
op_amp
(paren
id|mask
op_rshift
l_int|8
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8259A_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|make_8259A_irq
r_void
id|make_8259A_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|disable_irq_nosync
c_func
(paren
id|irq
)paren
suffix:semicolon
id|io_apic_irqs
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|handler
op_assign
op_amp
id|i8259A_irq_type
suffix:semicolon
id|enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function assumes to be called rarely. Switching between&n; * 8259A registers is slow.&n; * This has to be protected by the irq controller spinlock&n; * before being called.&n; */
DECL|function|i8259A_irq_real
r_static
r_inline
r_int
id|i8259A_irq_real
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|value
suffix:semicolon
r_int
id|irqmask
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
l_int|8
)paren
(brace
id|outb
c_func
(paren
l_int|0x0B
comma
id|PIC_MASTER_CMD
)paren
suffix:semicolon
multiline_comment|/* ISR register */
id|value
op_assign
id|inb
c_func
(paren
id|PIC_MASTER_CMD
)paren
op_amp
id|irqmask
suffix:semicolon
id|outb
c_func
(paren
l_int|0x0A
comma
id|PIC_MASTER_CMD
)paren
suffix:semicolon
multiline_comment|/* back to the IRR register */
r_return
id|value
suffix:semicolon
)brace
id|outb
c_func
(paren
l_int|0x0B
comma
id|PIC_SLAVE_CMD
)paren
suffix:semicolon
multiline_comment|/* ISR register */
id|value
op_assign
id|inb
c_func
(paren
id|PIC_SLAVE_CMD
)paren
op_amp
(paren
id|irqmask
op_rshift
l_int|8
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x0A
comma
id|PIC_SLAVE_CMD
)paren
suffix:semicolon
multiline_comment|/* back to the IRR register */
r_return
id|value
suffix:semicolon
)brace
multiline_comment|/*&n; * Careful! The 8259A is a fragile beast, it pretty&n; * much _has_ to be done exactly like this (mask it&n; * first, _then_ send the EOI, and the order of EOI&n; * to the two 8259s is important!&n; */
DECL|function|mask_and_ack_8259A
r_void
id|mask_and_ack_8259A
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|irqmask
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8259A_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Lightweight spurious IRQ detection. We do not want&n;&t; * to overdo spurious IRQ handling - it&squot;s usually a sign&n;&t; * of hardware problems, so we only do the checks we can&n;&t; * do without slowing down good hardware unnecesserily.&n;&t; *&n;&t; * Note that IRQ7 and IRQ15 (the two spurious IRQs&n;&t; * usually resulting from the 8259A-1|2 PICs) occur&n;&t; * even if the IRQ is masked in the 8259A. Thus we&n;&t; * can check spurious 8259A IRQs without doing the&n;&t; * quite slow i8259A_irq_real() call for every IRQ.&n;&t; * This does not cover 100% of spurious interrupts,&n;&t; * but should be enough to warn the user that there&n;&t; * is something bad going on ...&n;&t; */
r_if
c_cond
(paren
id|cached_irq_mask
op_amp
id|irqmask
)paren
r_goto
id|spurious_8259A_irq
suffix:semicolon
id|cached_irq_mask
op_or_assign
id|irqmask
suffix:semicolon
id|handle_real_irq
suffix:colon
r_if
c_cond
(paren
id|irq
op_amp
l_int|8
)paren
(brace
id|inb
c_func
(paren
id|PIC_SLAVE_IMR
)paren
suffix:semicolon
multiline_comment|/* DUMMY - (do we need this?) */
id|outb
c_func
(paren
id|cached_slave_mask
comma
id|PIC_SLAVE_IMR
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x60
op_plus
(paren
id|irq
op_amp
l_int|7
)paren
comma
id|PIC_SLAVE_CMD
)paren
suffix:semicolon
multiline_comment|/* &squot;Specific EOI&squot; to slave */
id|outb
c_func
(paren
l_int|0x60
op_plus
id|PIC_CASCADE_IR
comma
id|PIC_MASTER_CMD
)paren
suffix:semicolon
multiline_comment|/* &squot;Specific EOI&squot; to master-IRQ2 */
)brace
r_else
(brace
id|inb
c_func
(paren
id|PIC_MASTER_IMR
)paren
suffix:semicolon
multiline_comment|/* DUMMY - (do we need this?) */
id|outb
c_func
(paren
id|cached_master_mask
comma
id|PIC_MASTER_IMR
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x60
op_plus
id|irq
comma
id|PIC_MASTER_CMD
)paren
suffix:semicolon
multiline_comment|/* &squot;Specific EOI to master */
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8259A_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
id|spurious_8259A_irq
suffix:colon
multiline_comment|/*&n;&t; * this is the slow path - should happen rarely.&n;&t; */
r_if
c_cond
(paren
id|i8259A_irq_real
c_func
(paren
id|irq
)paren
)paren
multiline_comment|/*&n;&t;&t; * oops, the IRQ _is_ in service according to the&n;&t;&t; * 8259A - not spurious, go handle it.&n;&t;&t; */
r_goto
id|handle_real_irq
suffix:semicolon
(brace
r_static
r_int
id|spurious_irq_mask
suffix:semicolon
multiline_comment|/*&n;&t;&t; * At this point we can be sure the IRQ is spurious,&n;&t;&t; * lets ACK and report it. [once per IRQ]&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|spurious_irq_mask
op_amp
id|irqmask
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;spurious 8259A interrupt: IRQ%d.&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|spurious_irq_mask
op_or_assign
id|irqmask
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|irq_err_count
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Theoretically we do not have to handle this IRQ,&n;&t;&t; * but in Linux this does not cause problems and is&n;&t;&t; * simpler for us.&n;&t;&t; */
r_goto
id|handle_real_irq
suffix:semicolon
)brace
)brace
DECL|function|i8259A_resume
r_static
r_int
id|i8259A_resume
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
)paren
(brace
id|init_8259A
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|i8259_sysdev_class
r_static
r_struct
id|sysdev_class
id|i8259_sysdev_class
op_assign
(brace
id|set_kset_name
c_func
(paren
l_string|&quot;i8259&quot;
)paren
comma
dot
id|resume
op_assign
id|i8259A_resume
comma
)brace
suffix:semicolon
DECL|variable|device_i8259A
r_static
r_struct
id|sys_device
id|device_i8259A
op_assign
(brace
dot
id|id
op_assign
l_int|0
comma
dot
id|cls
op_assign
op_amp
id|i8259_sysdev_class
comma
)brace
suffix:semicolon
DECL|function|i8259A_init_sysfs
r_static
r_int
id|__init
id|i8259A_init_sysfs
c_func
(paren
r_void
)paren
(brace
r_int
id|error
op_assign
id|sysdev_class_register
c_func
(paren
op_amp
id|i8259_sysdev_class
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|sys_device_register
c_func
(paren
op_amp
id|device_i8259A
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|i8259A_init_sysfs
id|device_initcall
c_func
(paren
id|i8259A_init_sysfs
)paren
suffix:semicolon
DECL|function|init_8259A
r_void
id|init_8259A
c_func
(paren
r_int
id|auto_eoi
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8259A_lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xff
comma
id|PIC_MASTER_IMR
)paren
suffix:semicolon
multiline_comment|/* mask all of 8259A-1 */
id|outb
c_func
(paren
l_int|0xff
comma
id|PIC_SLAVE_IMR
)paren
suffix:semicolon
multiline_comment|/* mask all of 8259A-2 */
multiline_comment|/*&n;&t; * outb_p - this has to work on a wide range of PC hardware.&n;&t; */
id|outb_p
c_func
(paren
l_int|0x11
comma
id|PIC_MASTER_CMD
)paren
suffix:semicolon
multiline_comment|/* ICW1: select 8259A-1 init */
id|outb_p
c_func
(paren
l_int|0x20
op_plus
l_int|0
comma
id|PIC_MASTER_IMR
)paren
suffix:semicolon
multiline_comment|/* ICW2: 8259A-1 IR0-7 mapped to 0x20-0x27 */
id|outb_p
c_func
(paren
l_int|1U
op_lshift
id|PIC_CASCADE_IR
comma
id|PIC_MASTER_IMR
)paren
suffix:semicolon
multiline_comment|/* 8259A-1 (the master) has a slave on IR2 */
r_if
c_cond
(paren
id|auto_eoi
)paren
multiline_comment|/* master does Auto EOI */
id|outb_p
c_func
(paren
id|MASTER_ICW4_DEFAULT
op_or
id|PIC_ICW4_AEOI
comma
id|PIC_MASTER_IMR
)paren
suffix:semicolon
r_else
multiline_comment|/* master expects normal EOI */
id|outb_p
c_func
(paren
id|MASTER_ICW4_DEFAULT
comma
id|PIC_MASTER_IMR
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x11
comma
id|PIC_SLAVE_CMD
)paren
suffix:semicolon
multiline_comment|/* ICW1: select 8259A-2 init */
id|outb_p
c_func
(paren
l_int|0x20
op_plus
l_int|8
comma
id|PIC_SLAVE_IMR
)paren
suffix:semicolon
multiline_comment|/* ICW2: 8259A-2 IR0-7 mapped to 0x28-0x2f */
id|outb_p
c_func
(paren
id|PIC_CASCADE_IR
comma
id|PIC_SLAVE_IMR
)paren
suffix:semicolon
multiline_comment|/* 8259A-2 is a slave on master&squot;s IR2 */
id|outb_p
c_func
(paren
id|SLAVE_ICW4_DEFAULT
comma
id|PIC_SLAVE_IMR
)paren
suffix:semicolon
multiline_comment|/* (slave&squot;s support for AEOI in flat mode is to be investigated) */
r_if
c_cond
(paren
id|auto_eoi
)paren
multiline_comment|/*&n;&t;&t; * in AEOI mode we just have to mask the interrupt&n;&t;&t; * when acking.&n;&t;&t; */
id|i8259A_irq_type.ack
op_assign
id|disable_8259A_irq
suffix:semicolon
r_else
id|i8259A_irq_type.ack
op_assign
id|mask_and_ack_8259A
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
multiline_comment|/* wait for 8259A to initialize */
id|outb
c_func
(paren
id|cached_master_mask
comma
id|PIC_MASTER_IMR
)paren
suffix:semicolon
multiline_comment|/* restore master IRQ mask */
id|outb
c_func
(paren
id|cached_slave_mask
comma
id|PIC_SLAVE_IMR
)paren
suffix:semicolon
multiline_comment|/* restore slave IRQ mask */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8259A_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that on a 486, we don&squot;t want to do a SIGFPE on an irq13&n; * as the irq is unreliable, and exception 16 works correctly&n; * (ie as explained in the intel literature). On a 386, you&n; * can&squot;t use exception 16 due to bad IBM design, so we have to&n; * rely on the less exact irq13.&n; *&n; * Careful.. Not only is IRQ13 unreliable, but it is also&n; * leads to races. IBM designers who came up with it should&n; * be shot.&n; */
multiline_comment|/*&n; * =PC9800NOTE= In NEC PC-9800, we use irq8 instead of irq13!&n; */
DECL|function|math_error_irq
r_static
id|irqreturn_t
id|math_error_irq
c_func
(paren
r_int
id|cpl
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_extern
r_void
id|math_error
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_X86_PC9800
id|outb
c_func
(paren
l_int|0
comma
l_int|0xF0
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ignore_fpu_irq
op_logical_or
op_logical_neg
id|boot_cpu_data.hard_math
)paren
r_return
id|IRQ_NONE
suffix:semicolon
id|math_error
c_func
(paren
(paren
r_void
op_star
)paren
id|regs-&gt;eip
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * New motherboards sometimes make IRQ 13 be a PCI interrupt,&n; * so allow interrupt sharing.&n; */
DECL|variable|fpu_irq
r_static
r_struct
id|irqaction
id|fpu_irq
op_assign
(brace
id|math_error_irq
comma
l_int|0
comma
l_int|0
comma
l_string|&quot;fpu&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|init_ISA_irqs
r_void
id|__init
id|init_ISA_irqs
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
id|init_bsp_APIC
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|init_8259A
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_IRQS
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
l_int|0
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
r_if
c_cond
(paren
id|i
OL
l_int|16
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * 16 old-style INTA-cycle interrupts:&n;&t;&t;&t; */
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|i8259A_irq_type
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * &squot;high&squot; PCI IRQs filled in on demand&n;&t;&t;&t; */
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|no_irq_type
suffix:semicolon
)brace
)brace
)brace
DECL|function|setup_timer
r_static
r_void
id|setup_timer
c_func
(paren
r_void
)paren
(brace
r_extern
id|spinlock_t
id|i8253_lock
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|i8253_lock
comma
id|flags
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x34
comma
id|PIT_MODE
)paren
suffix:semicolon
multiline_comment|/* binary, mode 2, LSB/MSB, ch 0 */
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|LATCH
op_amp
l_int|0xff
comma
id|PIT_CH0
)paren
suffix:semicolon
multiline_comment|/* LSB */
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|outb
c_func
(paren
id|LATCH
op_rshift
l_int|8
comma
id|PIT_CH0
)paren
suffix:semicolon
multiline_comment|/* MSB */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8253_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|timer_resume
r_static
r_int
id|timer_resume
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
)paren
(brace
id|setup_timer
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|timer_sysclass
r_static
r_struct
id|sysdev_class
id|timer_sysclass
op_assign
(brace
id|set_kset_name
c_func
(paren
l_string|&quot;timer&quot;
)paren
comma
dot
id|resume
op_assign
id|timer_resume
comma
)brace
suffix:semicolon
DECL|variable|device_timer
r_static
r_struct
id|sys_device
id|device_timer
op_assign
(brace
dot
id|id
op_assign
l_int|0
comma
dot
id|cls
op_assign
op_amp
id|timer_sysclass
comma
)brace
suffix:semicolon
DECL|function|init_timer_sysfs
r_static
r_int
id|__init
id|init_timer_sysfs
c_func
(paren
r_void
)paren
(brace
r_int
id|error
op_assign
id|sysdev_class_register
c_func
(paren
op_amp
id|timer_sysclass
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|sys_device_register
c_func
(paren
op_amp
id|device_timer
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|init_timer_sysfs
id|device_initcall
c_func
(paren
id|init_timer_sysfs
)paren
suffix:semicolon
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* all the set up before the call gates are initialised */
id|pre_intr_init_hook
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Cover the whole vector space, no vector can escape&n;&t; * us. (some of these will be overridden and become&n;&t; * &squot;special&squot; SMP interrupts)&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|vector
op_assign
id|FIRST_EXTERNAL_VECTOR
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|vector
op_ne
id|SYSCALL_VECTOR
)paren
id|set_intr_gate
c_func
(paren
id|vector
comma
id|interrupt
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* setup after call gates are initialised (usually add in&n;&t; * the architecture specific gates)&n;&t; */
id|intr_init_hook
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set the clock to HZ Hz, we already have a valid&n;&t; * vector now:&n;&t; */
id|setup_timer
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * External FPU? Set up irq13 if so, for&n;&t; * original braindamaged IBM FERR coupling.&n;&t; */
r_if
c_cond
(paren
id|boot_cpu_data.hard_math
op_logical_and
op_logical_neg
id|cpu_has_fpu
)paren
id|setup_irq
c_func
(paren
id|FPU_IRQ
comma
op_amp
id|fpu_irq
)paren
suffix:semicolon
)brace
eof
