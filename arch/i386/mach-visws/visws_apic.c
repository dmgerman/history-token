multiline_comment|/*&n; *&t;linux/arch/i386/mach_visws/visws_apic.c&n; *&n; *&t;Copyright (C) 1999 Bent Hagemark, Ingo Molnar&n; *&n; *  SGI Visual Workstation interrupt controller&n; *&n; *  The Cobalt system ASIC in the Visual Workstation contains a &quot;Cobalt&quot; APIC&n; *  which serves as the main interrupt controller in the system.  Non-legacy&n; *  hardware in the system uses this controller directly.  Legacy devices&n; *  are connected to the PIIX4 which in turn has its 8259(s) connected to&n; *  a of the Cobalt APIC entry.&n; *&n; *  09/02/2000 - Updated for 2.4 by jbarnes@sgi.com&n; *&n; *  25/11/2002 - Updated for 2.5 by Andrey Panin &lt;pazke@orbita1.ru&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &lt;asm/i8259.h&gt;
macro_line|#include &quot;cobalt.h&quot;
macro_line|#include &quot;irq_vectors.h&quot;
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|cobalt_lock
)paren
suffix:semicolon
multiline_comment|/*&n; * Set the given Cobalt APIC Redirection Table entry to point&n; * to the given IDT vector/index.&n; */
DECL|function|co_apic_set
r_static
r_inline
r_void
id|co_apic_set
c_func
(paren
r_int
id|entry
comma
r_int
id|irq
)paren
(brace
id|co_apic_write
c_func
(paren
id|CO_APIC_LO
c_func
(paren
id|entry
)paren
comma
id|CO_APIC_LEVEL
op_or
(paren
id|irq
op_plus
id|FIRST_EXTERNAL_VECTOR
)paren
)paren
suffix:semicolon
id|co_apic_write
c_func
(paren
id|CO_APIC_HI
c_func
(paren
id|entry
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Cobalt (IO)-APIC functions to handle PCI devices.&n; */
DECL|function|co_apic_ide0_hack
r_static
r_inline
r_int
id|co_apic_ide0_hack
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
id|visws_board_type
suffix:semicolon
r_extern
r_char
id|visws_board_rev
suffix:semicolon
r_if
c_cond
(paren
id|visws_board_type
op_eq
id|VISWS_320
op_logical_and
id|visws_board_rev
op_eq
l_int|5
)paren
r_return
l_int|5
suffix:semicolon
r_return
id|CO_APIC_IDE0
suffix:semicolon
)brace
DECL|function|is_co_apic
r_static
r_int
id|is_co_apic
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
id|IS_CO_APIC
c_func
(paren
id|irq
)paren
)paren
r_return
id|CO_APIC
c_func
(paren
id|irq
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
id|CO_APIC_CPU
suffix:semicolon
r_case
id|CO_IRQ_IDE0
suffix:colon
r_return
id|co_apic_ide0_hack
c_func
(paren
)paren
suffix:semicolon
r_case
id|CO_IRQ_IDE1
suffix:colon
r_return
id|CO_APIC_IDE1
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This is the SGI Cobalt (IO-)APIC:&n; */
DECL|function|enable_cobalt_irq
r_static
r_void
id|enable_cobalt_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|co_apic_set
c_func
(paren
id|is_co_apic
c_func
(paren
id|irq
)paren
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|function|disable_cobalt_irq
r_static
r_void
id|disable_cobalt_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
id|entry
op_assign
id|is_co_apic
c_func
(paren
id|irq
)paren
suffix:semicolon
id|co_apic_write
c_func
(paren
id|CO_APIC_LO
c_func
(paren
id|entry
)paren
comma
id|CO_APIC_MASK
)paren
suffix:semicolon
id|co_apic_read
c_func
(paren
id|CO_APIC_LO
c_func
(paren
id|entry
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * &quot;irq&quot; really just serves to identify the device.  Here is where we&n; * map this to the Cobalt APIC entry where it&squot;s physically wired.&n; * This is called via request_irq -&gt; setup_irq -&gt; irq_desc-&gt;startup()&n; */
DECL|function|startup_cobalt_irq
r_static
r_int
r_int
id|startup_cobalt_irq
c_func
(paren
r_int
r_int
id|irq
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
id|cobalt_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
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
op_or
id|IRQ_WAITING
)paren
)paren
)paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_and_assign
op_complement
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
op_or
id|IRQ_WAITING
)paren
suffix:semicolon
id|enable_cobalt_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cobalt_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ack_cobalt_irq
r_static
r_void
id|ack_cobalt_irq
c_func
(paren
r_int
r_int
id|irq
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
id|cobalt_lock
comma
id|flags
)paren
suffix:semicolon
id|disable_cobalt_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|apic_write
c_func
(paren
id|APIC_EOI
comma
id|APIC_EIO_ACK
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cobalt_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|end_cobalt_irq
r_static
r_void
id|end_cobalt_irq
c_func
(paren
r_int
r_int
id|irq
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
id|cobalt_lock
comma
id|flags
)paren
suffix:semicolon
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
id|enable_cobalt_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cobalt_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|cobalt_irq_type
r_static
r_struct
id|hw_interrupt_type
id|cobalt_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;Cobalt-APIC&quot;
comma
dot
id|startup
op_assign
id|startup_cobalt_irq
comma
dot
id|shutdown
op_assign
id|disable_cobalt_irq
comma
dot
id|enable
op_assign
id|enable_cobalt_irq
comma
dot
id|disable
op_assign
id|disable_cobalt_irq
comma
dot
id|ack
op_assign
id|ack_cobalt_irq
comma
dot
id|end
op_assign
id|end_cobalt_irq
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the PIIX4-based 8259 that is wired up indirectly to Cobalt&n; * -- not the manner expected by the code in i8259.c.&n; *&n; * there is a &squot;master&squot; physical interrupt source that gets sent to&n; * the CPU. But in the chipset there are various &squot;virtual&squot; interrupts&n; * waiting to be handled. We represent this to Linux through a &squot;master&squot;&n; * interrupt controller type, and through a special virtual interrupt-&n; * controller. Device drivers only see the virtual interrupt sources.&n; */
DECL|function|startup_piix4_master_irq
r_static
r_int
r_int
id|startup_piix4_master_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|init_8259A
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
id|startup_cobalt_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|function|end_piix4_master_irq
r_static
r_void
id|end_piix4_master_irq
c_func
(paren
r_int
r_int
id|irq
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
id|cobalt_lock
comma
id|flags
)paren
suffix:semicolon
id|enable_cobalt_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|cobalt_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|piix4_master_irq_type
r_static
r_struct
id|hw_interrupt_type
id|piix4_master_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;PIIX4-master&quot;
comma
dot
id|startup
op_assign
id|startup_piix4_master_irq
comma
dot
id|ack
op_assign
id|ack_cobalt_irq
comma
dot
id|end
op_assign
id|end_piix4_master_irq
comma
)brace
suffix:semicolon
DECL|variable|piix4_virtual_irq_type
r_static
r_struct
id|hw_interrupt_type
id|piix4_virtual_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;PIIX4-virtual&quot;
comma
dot
id|startup
op_assign
id|startup_8259A_irq
comma
dot
id|shutdown
op_assign
id|disable_8259A_irq
comma
dot
id|enable
op_assign
id|enable_8259A_irq
comma
dot
id|disable
op_assign
id|disable_8259A_irq
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * PIIX4-8259 master/virtual functions to handle interrupt requests&n; * from legacy devices: floppy, parallel, serial, rtc.&n; *&n; * None of these get Cobalt APIC entries, neither do they have IDT&n; * entries. These interrupts are purely virtual and distributed from&n; * the &squot;master&squot; interrupt source: CO_IRQ_8259.&n; *&n; * When the 8259 interrupts its handler figures out which of these&n; * devices is interrupting and dispatches to its handler.&n; *&n; * CAREFUL: devices see the &squot;virtual&squot; interrupt only. Thus disable/&n; * enable_irq gets the right irq. This &squot;master&squot; irq is never directly&n; * manipulated by any driver.&n; */
DECL|function|piix4_master_intr
r_static
id|irqreturn_t
id|piix4_master_intr
c_func
(paren
r_int
id|irq
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
r_int
id|realirq
suffix:semicolon
id|irq_desc_t
op_star
id|desc
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
multiline_comment|/* Find out what&squot;s interrupting in the PIIX4 master 8259 */
id|outb
c_func
(paren
l_int|0x0c
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* OCW3 Poll command */
id|realirq
op_assign
id|inb
c_func
(paren
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Bit 7 == 0 means invalid/spurious&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
(paren
id|realirq
op_amp
l_int|0x80
)paren
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|realirq
op_and_assign
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|realirq
op_eq
l_int|2
)paren
)paren
(brace
id|outb
c_func
(paren
l_int|0x0c
comma
l_int|0xa0
)paren
suffix:semicolon
id|realirq
op_assign
id|inb
c_func
(paren
l_int|0xa0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
(paren
id|realirq
op_amp
l_int|0x80
)paren
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|realirq
op_assign
(paren
id|realirq
op_amp
l_int|7
)paren
op_plus
l_int|8
suffix:semicolon
)brace
multiline_comment|/* mask and ack interrupt */
id|cached_irq_mask
op_or_assign
l_int|1
op_lshift
id|realirq
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|realirq
OG
l_int|7
)paren
)paren
(brace
id|inb
c_func
(paren
l_int|0xa1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|cached_slave_mask
comma
l_int|0xa1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x60
op_plus
(paren
id|realirq
op_amp
l_int|7
)paren
comma
l_int|0xa0
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x60
op_plus
l_int|2
comma
l_int|0x20
)paren
suffix:semicolon
)brace
r_else
(brace
id|inb
c_func
(paren
l_int|0x21
)paren
suffix:semicolon
id|outb
c_func
(paren
id|cached_master_mask
comma
l_int|0x21
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x60
op_plus
id|realirq
comma
l_int|0x20
)paren
suffix:semicolon
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
id|desc
op_assign
id|irq_desc
op_plus
id|realirq
suffix:semicolon
multiline_comment|/*&n;&t; * handle this &squot;virtual interrupt&squot; as a Cobalt one now.&n;&t; */
id|kstat_cpu
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
dot
id|irqs
(braket
id|realirq
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|desc-&gt;action
op_ne
l_int|NULL
)paren
)paren
id|handle_IRQ_event
c_func
(paren
id|realirq
comma
id|regs
comma
id|desc-&gt;action
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|desc-&gt;status
op_amp
id|IRQ_DISABLED
)paren
)paren
id|enable_8259A_irq
c_func
(paren
id|realirq
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
id|out_unlock
suffix:colon
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
id|IRQ_NONE
suffix:semicolon
)brace
DECL|variable|master_action
r_static
r_struct
id|irqaction
id|master_action
op_assign
(brace
dot
id|handler
op_assign
id|piix4_master_intr
comma
dot
id|name
op_assign
l_string|&quot;PIIX4-8259&quot;
comma
)brace
suffix:semicolon
DECL|variable|cascade_action
r_static
r_struct
id|irqaction
id|cascade_action
op_assign
(brace
dot
id|handler
op_assign
id|no_action
comma
dot
id|name
op_assign
l_string|&quot;cascade&quot;
comma
)brace
suffix:semicolon
DECL|function|init_VISWS_APIC_irqs
r_void
id|init_VISWS_APIC_irqs
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|CO_IRQ_APIC0
op_plus
id|CO_APIC_LAST
op_plus
l_int|1
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
op_eq
l_int|0
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|cobalt_irq_type
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_eq
id|CO_IRQ_IDE0
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|cobalt_irq_type
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_eq
id|CO_IRQ_IDE1
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|cobalt_irq_type
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_eq
id|CO_IRQ_8259
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|piix4_master_irq_type
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
OL
id|CO_IRQ_APIC0
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|piix4_virtual_irq_type
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|IS_CO_APIC
c_func
(paren
id|i
)paren
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|cobalt_irq_type
suffix:semicolon
)brace
)brace
id|setup_irq
c_func
(paren
id|CO_IRQ_8259
comma
op_amp
id|master_action
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
l_int|2
comma
op_amp
id|cascade_action
)paren
suffix:semicolon
)brace
eof
