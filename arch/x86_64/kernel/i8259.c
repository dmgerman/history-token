macro_line|#include &lt;linux/linkage.h&gt;
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
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/acpi.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
multiline_comment|/*&n; * Common place to define all x86 IRQ vectors&n; *&n; * This builds up the IRQ handler stubs using some ugly macros in irq.h&n; *&n; * These macros create the low-level assembly IRQ routines that save&n; * register context and call do_IRQ(). do_IRQ() then does all the&n; * operations that are needed to keep the AT (or SMP IOAPIC)&n; * interrupt-controller happy.&n; */
DECL|macro|BI
mdefine_line|#define BI(x,y) &bslash;&n;&t;BUILD_IRQ(x##y)
DECL|macro|BUILD_16_IRQS
mdefine_line|#define BUILD_16_IRQS(x) &bslash;&n;&t;BI(x,0) BI(x,1) BI(x,2) BI(x,3) &bslash;&n;&t;BI(x,4) BI(x,5) BI(x,6) BI(x,7) &bslash;&n;&t;BI(x,8) BI(x,9) BI(x,a) BI(x,b) &bslash;&n;&t;BI(x,c) BI(x,d) BI(x,e) BI(x,f)
DECL|macro|BUILD_14_IRQS
mdefine_line|#define BUILD_14_IRQS(x) &bslash;&n;&t;BI(x,0) BI(x,1) BI(x,2) BI(x,3) &bslash;&n;&t;BI(x,4) BI(x,5) BI(x,6) BI(x,7) &bslash;&n;&t;BI(x,8) BI(x,9) BI(x,a) BI(x,b) &bslash;&n;&t;BI(x,c) BI(x,d)
multiline_comment|/*&n; * ISA PIC or low IO-APIC triggered (INTA-cycle or APIC) interrupts:&n; * (these are usually mapped to vectors 0x20-0x2f)&n; */
id|BUILD_16_IRQS
c_func
(paren
l_int|0x0
)paren
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
multiline_comment|/*&n; * The IO-APIC gives us many more interrupt sources. Most of these &n; * are unused but an SMP system is supposed to have enough memory ...&n; * sometimes (mostly wrt. hw bugs) we get corrupted vectors all&n; * across the spectrum, so we really want to be prepared to get all&n; * of these. Plus, more powerful systems might have more than 64&n; * IO-APIC registers.&n; *&n; * (these are usually mapped into the 0x30-0xff vector range)&n; */
id|BUILD_16_IRQS
c_func
(paren
l_int|0x1
)paren
id|BUILD_16_IRQS
c_func
(paren
l_int|0x2
)paren
id|BUILD_16_IRQS
c_func
(paren
l_int|0x3
)paren
id|BUILD_16_IRQS
c_func
(paren
l_int|0x4
)paren
id|BUILD_16_IRQS
c_func
(paren
l_int|0x5
)paren
id|BUILD_16_IRQS
c_func
(paren
l_int|0x6
)paren
id|BUILD_16_IRQS
c_func
(paren
l_int|0x7
)paren
id|BUILD_16_IRQS
c_func
(paren
l_int|0x8
)paren
id|BUILD_16_IRQS
c_func
(paren
l_int|0x9
)paren
id|BUILD_16_IRQS
c_func
(paren
l_int|0xa
)paren
id|BUILD_16_IRQS
c_func
(paren
l_int|0xb
)paren
id|BUILD_16_IRQS
c_func
(paren
l_int|0xc
)paren
id|BUILD_16_IRQS
c_func
(paren
l_int|0xd
)paren
macro_line|#ifdef CONFIG_PCI_MSI
id|BUILD_14_IRQS
c_func
(paren
l_int|0xe
)paren
macro_line|#endif
macro_line|#endif
DECL|macro|BUILD_16_IRQS
macro_line|#undef BUILD_16_IRQS
DECL|macro|BUILD_14_IRQS
macro_line|#undef BUILD_14_IRQS
DECL|macro|BI
macro_line|#undef BI
DECL|macro|IRQ
mdefine_line|#define IRQ(x,y) &bslash;&n;&t;IRQ##x##y##_interrupt
DECL|macro|IRQLIST_16
mdefine_line|#define IRQLIST_16(x) &bslash;&n;&t;IRQ(x,0), IRQ(x,1), IRQ(x,2), IRQ(x,3), &bslash;&n;&t;IRQ(x,4), IRQ(x,5), IRQ(x,6), IRQ(x,7), &bslash;&n;&t;IRQ(x,8), IRQ(x,9), IRQ(x,a), IRQ(x,b), &bslash;&n;&t;IRQ(x,c), IRQ(x,d), IRQ(x,e), IRQ(x,f)
DECL|macro|IRQLIST_14
mdefine_line|#define IRQLIST_14(x) &bslash;&n;&t;IRQ(x,0), IRQ(x,1), IRQ(x,2), IRQ(x,3), &bslash;&n;&t;IRQ(x,4), IRQ(x,5), IRQ(x,6), IRQ(x,7), &bslash;&n;&t;IRQ(x,8), IRQ(x,9), IRQ(x,a), IRQ(x,b), &bslash;&n;&t;IRQ(x,c), IRQ(x,d)
DECL|variable|interrupt
r_void
(paren
op_star
id|interrupt
(braket
id|NR_IRQS
)braket
)paren
(paren
r_void
)paren
op_assign
(brace
id|IRQLIST_16
c_func
(paren
l_int|0x0
)paren
comma
macro_line|#ifdef CONFIG_X86_IO_APIC
id|IRQLIST_16
c_func
(paren
l_int|0x1
)paren
comma
id|IRQLIST_16
c_func
(paren
l_int|0x2
)paren
comma
id|IRQLIST_16
c_func
(paren
l_int|0x3
)paren
comma
id|IRQLIST_16
c_func
(paren
l_int|0x4
)paren
comma
id|IRQLIST_16
c_func
(paren
l_int|0x5
)paren
comma
id|IRQLIST_16
c_func
(paren
l_int|0x6
)paren
comma
id|IRQLIST_16
c_func
(paren
l_int|0x7
)paren
comma
id|IRQLIST_16
c_func
(paren
l_int|0x8
)paren
comma
id|IRQLIST_16
c_func
(paren
l_int|0x9
)paren
comma
id|IRQLIST_16
c_func
(paren
l_int|0xa
)paren
comma
id|IRQLIST_16
c_func
(paren
l_int|0xb
)paren
comma
id|IRQLIST_16
c_func
(paren
l_int|0xc
)paren
comma
id|IRQLIST_16
c_func
(paren
l_int|0xd
)paren
macro_line|#ifdef CONFIG_PCI_MSI
comma
id|IRQLIST_14
c_func
(paren
l_int|0xe
)paren
macro_line|#endif
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|IRQ
macro_line|#undef IRQ
DECL|macro|IRQLIST_16
macro_line|#undef IRQLIST_16
DECL|macro|IRQLIST_14
macro_line|#undef IRQLIST_14
multiline_comment|/*&n; * This is the &squot;legacy&squot; 8259A Programmable Interrupt Controller,&n; * present in the majority of PC/AT boxes.&n; * plus some generic x86 specific things if generic specifics makes&n; * any sense at all.&n; * this file should become arch/i386/kernel/irq.c when the old irq.c&n; * moves to arch independent land&n; */
DECL|variable|i8259A_lock
id|DEFINE_SPINLOCK
c_func
(paren
id|i8259A_lock
)paren
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
id|irq
OG
l_int|256
)paren
(brace
r_char
id|var
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;return %p stack %p ti %p&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
comma
op_amp
id|var
comma
id|current-&gt;thread_info
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
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
r_static
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
r_static
r_int
r_int
id|cached_irq_mask
op_assign
l_int|0xffff
suffix:semicolon
DECL|macro|__byte
mdefine_line|#define __byte(x,y) &t;(((unsigned char *)&amp;(y))[x])
DECL|macro|cached_21
mdefine_line|#define cached_21&t;(__byte(0,cached_irq_mask))
DECL|macro|cached_A1
mdefine_line|#define cached_A1&t;(__byte(1,cached_irq_mask))
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
id|cached_A1
comma
l_int|0xA1
)paren
suffix:semicolon
r_else
id|outb
c_func
(paren
id|cached_21
comma
l_int|0x21
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
id|cached_A1
comma
l_int|0xA1
)paren
suffix:semicolon
r_else
id|outb
c_func
(paren
id|cached_21
comma
l_int|0x21
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
l_int|0x20
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
l_int|0xA0
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
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* ISR register */
id|value
op_assign
id|inb
c_func
(paren
l_int|0x20
)paren
op_amp
id|irqmask
suffix:semicolon
id|outb
c_func
(paren
l_int|0x0A
comma
l_int|0x20
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
l_int|0xA0
)paren
suffix:semicolon
multiline_comment|/* ISR register */
id|value
op_assign
id|inb
c_func
(paren
l_int|0xA0
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
l_int|0xA0
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
l_int|0xA1
)paren
suffix:semicolon
multiline_comment|/* DUMMY - (do we need this?) */
id|outb
c_func
(paren
id|cached_A1
comma
l_int|0xA1
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
l_int|0xA0
)paren
suffix:semicolon
multiline_comment|/* &squot;Specific EOI&squot; to slave */
id|outb
c_func
(paren
l_int|0x62
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* &squot;Specific EOI&squot; to master-IRQ2 */
)brace
r_else
(brace
id|inb
c_func
(paren
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* DUMMY - (do we need this?) */
id|outb
c_func
(paren
id|cached_21
comma
l_int|0x21
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x60
op_plus
id|irq
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* &squot;Specific EOI&squot; to master */
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
id|KERN_DEBUG
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
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* mask all of 8259A-1 */
id|outb
c_func
(paren
l_int|0xff
comma
l_int|0xA1
)paren
suffix:semicolon
multiline_comment|/* mask all of 8259A-2 */
multiline_comment|/*&n;&t; * outb_p - this has to work on a wide range of PC hardware.&n;&t; */
id|outb_p
c_func
(paren
l_int|0x11
comma
l_int|0x20
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
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* ICW2: 8259A-1 IR0-7 mapped to 0x20-0x27 */
id|outb_p
c_func
(paren
l_int|0x04
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* 8259A-1 (the master) has a slave on IR2 */
r_if
c_cond
(paren
id|auto_eoi
)paren
id|outb_p
c_func
(paren
l_int|0x03
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* master does Auto EOI */
r_else
id|outb_p
c_func
(paren
l_int|0x01
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* master expects normal EOI */
id|outb_p
c_func
(paren
l_int|0x11
comma
l_int|0xA0
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
l_int|0xA1
)paren
suffix:semicolon
multiline_comment|/* ICW2: 8259A-2 IR0-7 mapped to 0x28-0x2f */
id|outb_p
c_func
(paren
l_int|0x02
comma
l_int|0xA1
)paren
suffix:semicolon
multiline_comment|/* 8259A-2 is a slave on master&squot;s IR2 */
id|outb_p
c_func
(paren
l_int|0x01
comma
l_int|0xA1
)paren
suffix:semicolon
multiline_comment|/* (slave&squot;s support for AEOI in flat mode&n;&t;&t;&t;&t;    is to be investigated) */
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
id|cached_21
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* restore master IRQ mask */
id|outb
c_func
(paren
id|cached_A1
comma
l_int|0xA1
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
DECL|variable|irq_trigger
r_static
r_char
id|irq_trigger
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/**&n; * ELCR registers (0x4d0, 0x4d1) control edge/level of IRQ&n; */
DECL|function|restore_ELCR
r_static
r_void
id|restore_ELCR
c_func
(paren
r_char
op_star
id|trigger
)paren
(brace
id|outb
c_func
(paren
id|trigger
(braket
l_int|0
)braket
comma
l_int|0x4d0
)paren
suffix:semicolon
id|outb
c_func
(paren
id|trigger
(braket
l_int|1
)braket
comma
l_int|0x4d1
)paren
suffix:semicolon
)brace
DECL|function|save_ELCR
r_static
r_void
id|save_ELCR
c_func
(paren
r_char
op_star
id|trigger
)paren
(brace
multiline_comment|/* IRQ 0,1,2,8,13 are marked as reserved */
id|trigger
(braket
l_int|0
)braket
op_assign
id|inb
c_func
(paren
l_int|0x4d0
)paren
op_amp
l_int|0xF8
suffix:semicolon
id|trigger
(braket
l_int|1
)braket
op_assign
id|inb
c_func
(paren
l_int|0x4d1
)paren
op_amp
l_int|0xDE
suffix:semicolon
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
id|restore_ELCR
c_func
(paren
id|irq_trigger
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i8259A_suspend
r_static
r_int
id|i8259A_suspend
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
comma
id|u32
id|state
)paren
(brace
id|save_ELCR
c_func
(paren
id|irq_trigger
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
id|suspend
op_assign
id|i8259A_suspend
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
id|sysdev_register
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
multiline_comment|/*&n; * IRQ2 is cascade interrupt to second interrupt controller&n; */
DECL|variable|irq2
r_static
r_struct
id|irqaction
id|irq2
op_assign
(brace
id|no_action
comma
l_int|0
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
r_void
id|apic_timer_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|spurious_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|error_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|reschedule_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|call_function_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|invalidate_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|thermal_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|setup_timer
r_static
r_void
id|setup_timer
c_func
(paren
r_void
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x34
comma
l_int|0x43
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
l_int|0x40
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
l_int|0x40
)paren
suffix:semicolon
multiline_comment|/* MSB */
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
id|sysdev_register
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
id|init_ISA_irqs
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
(paren
id|NR_VECTORS
op_minus
id|FIRST_EXTERNAL_VECTOR
)paren
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
id|i
op_ge
id|NR_IRQS
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|vector
op_ne
id|IA32_SYSCALL_VECTOR
op_logical_and
id|vector
op_ne
id|KDB_VECTOR
)paren
(brace
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
)brace
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n;&t; * IRQ0 must be given a fixed assignment and initialized,&n;&t; * because it&squot;s used before the IO-APIC is set up.&n;&t; */
id|set_intr_gate
c_func
(paren
id|FIRST_DEVICE_VECTOR
comma
id|interrupt
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The reschedule interrupt is a CPU-to-CPU reschedule-helper&n;&t; * IPI, driven by wakeup.&n;&t; */
id|set_intr_gate
c_func
(paren
id|RESCHEDULE_VECTOR
comma
id|reschedule_interrupt
)paren
suffix:semicolon
multiline_comment|/* IPI for invalidation */
id|set_intr_gate
c_func
(paren
id|INVALIDATE_TLB_VECTOR
comma
id|invalidate_interrupt
)paren
suffix:semicolon
multiline_comment|/* IPI for generic function call */
id|set_intr_gate
c_func
(paren
id|CALL_FUNCTION_VECTOR
comma
id|call_function_interrupt
)paren
suffix:semicolon
macro_line|#endif&t;
id|set_intr_gate
c_func
(paren
id|THERMAL_APIC_VECTOR
comma
id|thermal_interrupt
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
multiline_comment|/* self generated IPI for local APIC timer */
id|set_intr_gate
c_func
(paren
id|LOCAL_TIMER_VECTOR
comma
id|apic_timer_interrupt
)paren
suffix:semicolon
multiline_comment|/* IPI vectors for APIC spurious and error interrupts */
id|set_intr_gate
c_func
(paren
id|SPURIOUS_APIC_VECTOR
comma
id|spurious_interrupt
)paren
suffix:semicolon
id|set_intr_gate
c_func
(paren
id|ERROR_APIC_VECTOR
comma
id|error_interrupt
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Set the clock to HZ Hz, we already have a valid&n;&t; * vector now:&n;&t; */
id|setup_timer
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_ioapic
)paren
id|setup_irq
c_func
(paren
l_int|2
comma
op_amp
id|irq2
)paren
suffix:semicolon
)brace
eof
