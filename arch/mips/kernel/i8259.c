multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Code to handle x86 style IRQs plus some generic interrupt stuff.&n; *&n; * Copyright (C) 1992 Linus Torvalds&n; * Copyright (C) 1994 - 2000 Ralf Baechle&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;asm/i8259.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_void
id|enable_8259A_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_void
id|disable_8259A_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
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
DECL|macro|cached_21
mdefine_line|#define cached_21&t;(cached_irq_mask)
DECL|macro|cached_A1
mdefine_line|#define cached_A1&t;(cached_irq_mask &gt;&gt; 8)
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
multiline_comment|/*&n;&t; * Lightweight spurious IRQ detection. We do not want to overdo&n;&t; * spurious IRQ handling - it&squot;s usually a sign of hardware problems, so&n;&t; * we only do the checks we can do without slowing down good hardware&n;&t; * nnecesserily.&n;&t; *&n;&t; * Note that IRQ7 and IRQ15 (the two spurious IRQs usually resulting&n;&t; * rom the 8259A-1|2 PICs) occur even if the IRQ is masked in the 8259A.&n;&t; * Thus we can check spurious 8259A IRQs without doing the quite slow&n;&t; * i8259A_irq_real() call for every IRQ.  This does not cover 100% of&n;&t; * spurious interrupts, but should be enough to warn the user that&n;&t; * there is something bad going on ...&n;&t; */
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
op_assign
l_int|0
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
id|__init
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
l_int|0x00
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* ICW2: 8259A-1 IR0-7 mapped to 0x00-0x07 */
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
l_int|0x08
comma
l_int|0xA1
)paren
suffix:semicolon
multiline_comment|/* ICW2: 8259A-2 IR0-7 mapped to 0x08-0x0f */
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
l_int|0
comma
l_string|&quot;cascade&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|pic1_io_resource
r_static
r_struct
id|resource
id|pic1_io_resource
op_assign
(brace
l_string|&quot;pic1&quot;
comma
l_int|0x20
comma
l_int|0x3f
comma
id|IORESOURCE_BUSY
)brace
suffix:semicolon
DECL|variable|pic2_io_resource
r_static
r_struct
id|resource
id|pic2_io_resource
op_assign
(brace
l_string|&quot;pic2&quot;
comma
l_int|0xa0
comma
l_int|0xbf
comma
id|IORESOURCE_BUSY
)brace
suffix:semicolon
multiline_comment|/*&n; * On systems with i8259-style interrupt controllers we assume for&n; * driver compatibility reasons interrupts 0 - 15 to be the i8295&n; * interrupts even if the hardware uses a different interrupt numbering.&n; */
DECL|function|init_i8259_irqs
r_void
id|__init
id|init_i8259_irqs
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|pic1_io_resource
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|pic2_io_resource
)paren
suffix:semicolon
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
l_int|16
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
