multiline_comment|/*&n; * Copyright (C) 2003 PMC-Sierra Inc.&n; * Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Second level Interrupt handlers for the PMC-Sierra Titan/Yosemite board&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* Hypertransport specific */
DECL|macro|IRQ_STATUS_REG_CPU0
mdefine_line|#define IRQ_STATUS_REG_CPU0     0xbb001b30 &t;/* INT# 3 status register on CPU 0*/
DECL|macro|IRQ_STATUS_REG_CPU1
mdefine_line|#define&t;IRQ_STATUS_REG_CPU1&t;0xbb002b30&t;/* INT# 3 status register on CPU 1*/
DECL|macro|IRQ_ACK_BITS
mdefine_line|#define IRQ_ACK_BITS            0x00000000 &t;/* Ack bits */
DECL|macro|IRQ_CLEAR_REG_CPU0
mdefine_line|#define IRQ_CLEAR_REG_CPU0      0xbb002b3c &t;/* IRQ clear register on CPU 0*/
DECL|macro|IRQ_CLEAR_REG_CPU0
mdefine_line|#define IRQ_CLEAR_REG_CPU0      0xbb002b3c      /* IRQ clear register on CPU 1*/
DECL|macro|HYPERTRANSPORT_EOI
mdefine_line|#define HYPERTRANSPORT_EOI      0xbb0006E0 &t;/* End of Interrupt */
DECL|macro|HYPERTRANSPORT_INTA
mdefine_line|#define HYPERTRANSPORT_INTA     0x78    &t;/* INTA# */
DECL|macro|HYPERTRANSPORT_INTB
mdefine_line|#define HYPERTRANSPORT_INTB     0x79    &t;/* INTB# */
DECL|macro|HYPERTRANSPORT_INTC
mdefine_line|#define HYPERTRANSPORT_INTC     0x7a    &t;/* INTC# */
DECL|macro|HYPERTRANSPORT_INTD
mdefine_line|#define HYPERTRANSPORT_INTD     0x7b    &t;/* INTD# */
DECL|macro|read_32bit_cp0_set1_register
mdefine_line|#define read_32bit_cp0_set1_register(source)                    &bslash;&n;({ int __res;                                                   &bslash;&n;        __asm__ __volatile__(                                   &bslash;&n;        &quot;.set&bslash;tpush&bslash;n&bslash;t&quot;                                        &bslash;&n;        &quot;.set&bslash;treorder&bslash;n&bslash;t&quot;                                     &bslash;&n;        &quot;cfc0&bslash;t%0,&quot;STR(source)&quot;&bslash;n&bslash;t&quot;                            &bslash;&n;        &quot;.set&bslash;tpop&quot;                                             &bslash;&n;        : &quot;=r&quot; (__res));                                        &bslash;&n;        __res;})
DECL|macro|write_32bit_cp0_set1_register
mdefine_line|#define write_32bit_cp0_set1_register(register,value)           &bslash;&n;        __asm__ __volatile__(                                   &bslash;&n;        &quot;ctc0&bslash;t%0,&quot;STR(register)&quot;&bslash;n&bslash;t&quot;                          &bslash;&n;        &quot;nop&quot;                                                   &bslash;&n;        : : &quot;r&quot; (value));
DECL|variable|irq_lock
r_static
id|spinlock_t
id|irq_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* Function for careful CP0 interrupt mask access */
DECL|function|modify_cp0_intmask
r_static
r_inline
r_void
id|modify_cp0_intmask
c_func
(paren
r_int
id|clr_mask_in
comma
r_int
id|set_mask_in
)paren
(brace
r_int
r_int
id|status
suffix:semicolon
r_int
id|clr_mask
suffix:semicolon
r_int
id|set_mask
suffix:semicolon
multiline_comment|/* do the low 8 bits first */
id|clr_mask
op_assign
l_int|0xff
op_amp
id|clr_mask_in
suffix:semicolon
id|set_mask
op_assign
l_int|0xff
op_amp
id|set_mask_in
suffix:semicolon
id|status
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
(paren
id|clr_mask
op_amp
l_int|0xFF
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|status
op_or_assign
(paren
id|set_mask
op_amp
l_int|0xFF
)paren
op_lshift
l_int|8
op_or
l_int|0x0000FF00
suffix:semicolon
id|write_c0_status
c_func
(paren
id|status
)paren
suffix:semicolon
multiline_comment|/* do the high 8 bits */
id|clr_mask
op_assign
l_int|0xff
op_amp
(paren
id|clr_mask_in
op_rshift
l_int|8
)paren
suffix:semicolon
id|set_mask
op_assign
l_int|0xff
op_amp
(paren
id|set_mask_in
op_rshift
l_int|8
)paren
suffix:semicolon
id|status
op_assign
id|read_32bit_cp0_set1_register
c_func
(paren
id|CP0_S1_INTCONTROL
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
(paren
(paren
id|clr_mask
op_amp
l_int|0xFF
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|status
op_or_assign
(paren
id|set_mask
op_amp
l_int|0xFF
)paren
op_lshift
l_int|8
suffix:semicolon
id|write_32bit_cp0_set1_register
c_func
(paren
id|CP0_S1_INTCONTROL
comma
id|status
)paren
suffix:semicolon
)brace
DECL|function|mask_irq
r_static
r_inline
r_void
id|mask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|modify_cp0_intmask
c_func
(paren
id|irq
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|unmask_irq
r_static
r_inline
r_void
id|unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|modify_cp0_intmask
c_func
(paren
l_int|0
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|function|enable_rm9000_irq
r_static
r_void
id|enable_rm9000_irq
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
id|irq_lock
comma
id|flags
)paren
suffix:semicolon
id|unmask_irq
c_func
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|startup_rm9000_irq
r_static
r_int
r_int
id|startup_rm9000_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_rm9000_irq
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
DECL|function|disable_rm9000_irq
r_static
r_void
id|disable_rm9000_irq
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
id|irq_lock
comma
id|flags
)paren
suffix:semicolon
id|mask_irq
c_func
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|macro|shutdown_rm9000_irq
mdefine_line|#define shutdown_rm9000_irq disable_rm9000_irq
DECL|function|mask_and_ack_rm9000_irq
r_static
r_void
id|mask_and_ack_rm9000_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|mask_irq
c_func
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|function|end_rm9000_irq
r_static
r_void
id|end_rm9000_irq
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
id|unmask_irq
c_func
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|variable|rm9000_hpcdma_irq_type
r_static
r_struct
id|hw_interrupt_type
id|rm9000_hpcdma_irq_type
op_assign
(brace
l_string|&quot;RM9000&quot;
comma
id|startup_rm9000_irq
comma
id|shutdown_rm9000_irq
comma
id|enable_rm9000_irq
comma
id|disable_rm9000_irq
comma
id|mask_and_ack_rm9000_irq
comma
id|end_rm9000_irq
comma
l_int|NULL
)brace
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|titan_handle_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|jaguar_mailbox_irq
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/* &n; * Handle hypertransport &amp; SMP interrupts. The interrupt lines are scarce. For interprocessor&n; * interrupts, the best thing to do is to use the INTMSG register. We use the same external&n; * interrupt line, i.e. INTB3 and monitor another status bit&n; */
DECL|function|ll_ht_smp_irq_handler
id|asmlinkage
r_void
id|ll_ht_smp_irq_handler
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u32
id|status
suffix:semicolon
id|status
op_assign
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
id|IRQ_STATUS_REG_CPU0
)paren
suffix:semicolon
multiline_comment|/* Ack all the bits that correspond to the interrupt sources */
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
id|IRQ_STATUS_REG_CPU0
)paren
op_assign
id|IRQ_ACK_BITS
suffix:semicolon
id|status
op_assign
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
id|IRQ_STATUS_REG_CPU1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
id|IRQ_STATUS_REG_CPU1
)paren
op_assign
id|IRQ_ACK_BITS
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|status
op_eq
l_int|0x2
)paren
(brace
multiline_comment|/* This is an SMP IPI sent from one core to another */
id|jaguar_mailbox_irq
c_func
(paren
id|regs
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_HT_LEVEL_TRIGGER
multiline_comment|/*&n;         * Level Trigger Mode only. Send the HT EOI message back to the source.&n;         */
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
l_int|0x1000000
suffix:colon
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
id|HYPERTRANSPORT_EOI
)paren
op_assign
id|HYPERTRANSPORT_INTA
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x2000000
suffix:colon
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
id|HYPERTRANSPORT_EOI
)paren
op_assign
id|HYPERTRANSPORT_INTB
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x4000000
suffix:colon
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
id|HYPERTRANSPORT_EOI
)paren
op_assign
id|HYPERTRANSPORT_INTC
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x8000000
suffix:colon
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
id|HYPERTRANSPORT_EOI
)paren
op_assign
id|HYPERTRANSPORT_INTD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0000001
suffix:colon
multiline_comment|/* PLX */
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
id|HYPERTRANSPORT_EOI
)paren
op_assign
l_int|0x20
suffix:semicolon
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
id|IRQ_CLEAR_REG
)paren
op_assign
id|IRQ_ACK_BITS
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf000000
suffix:colon
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
id|HYPERTRANSPORT_EOI
)paren
op_assign
id|HYPERTRANSPORT_INTA
suffix:semicolon
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
id|HYPERTRANSPORT_EOI
)paren
op_assign
id|HYPERTRANSPORT_INTB
suffix:semicolon
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
id|HYPERTRANSPORT_EOI
)paren
op_assign
id|HYPERTRANSPORT_INTC
suffix:semicolon
op_star
(paren
r_volatile
r_uint32
op_star
)paren
(paren
id|HYPERTRANSPORT_EOI
)paren
op_assign
id|HYPERTRANSPORT_INTD
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_HT_LEVEL_TRIGGER */
id|done
suffix:colon
r_if
c_cond
(paren
id|status
op_ne
l_int|0x2
)paren
multiline_comment|/* Not for SMP */
id|do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the next level interrupt handler&n; */
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
id|clear_c0_status
c_func
(paren
id|ST0_IM
op_or
id|ST0_BEV
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|0
comma
id|titan_handle_int
)paren
suffix:semicolon
id|init_generic_irq
c_func
(paren
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
l_int|13
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
id|rm9000_hpcdma_irq_type
suffix:semicolon
)brace
)brace
eof
