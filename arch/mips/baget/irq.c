multiline_comment|/*&n; * Code to handle Baget/MIPS IRQs plus some generic interrupt stuff.&n; *&n; * Copyright (C) 1998 Vladimir Roganov &amp; Gleb Raiko&n; *      Code (mostly sleleton and comments) derived from DECstation IRQ&n; *      handling.&n; */
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
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/baget/baget.h&gt;
DECL|variable|irq_err_count
r_volatile
r_int
r_int
id|irq_err_count
suffix:semicolon
multiline_comment|/*&n; * This table is a correspondence between IRQ numbers and CPU PILs&n; */
DECL|variable|irq_to_pil_map
r_static
r_int
id|irq_to_pil_map
(braket
id|BAGET_IRQ_NR
)braket
op_assign
(brace
l_int|7
multiline_comment|/*fixme: dma_err -1*/
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
multiline_comment|/* 0x00 - 0x0f */
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|3
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|2
comma
l_int|2
comma
l_int|2
comma
op_minus
l_int|1
comma
l_int|3
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|3
multiline_comment|/*fixme: lance*/
comma
multiline_comment|/* 0x10 - 0x1f */
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|5
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|7
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
multiline_comment|/* 0x20 - 0x2f */
op_minus
l_int|1
comma
l_int|3
comma
l_int|2
multiline_comment|/*fixme systimer:3*/
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
comma
l_int|3
multiline_comment|/* 0x30 - 0x3f */
)brace
suffix:semicolon
DECL|function|irq_to_pil
r_static
r_inline
r_int
id|irq_to_pil
c_func
(paren
r_int
id|irq_nr
)paren
(brace
r_int
id|pil
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|irq_nr
op_ge
id|BAGET_IRQ_NR
)paren
id|baget_printk
c_func
(paren
l_string|&quot;irq_to_pil: too large irq_nr = 0x%x&bslash;n&quot;
comma
id|irq_nr
)paren
suffix:semicolon
r_else
(brace
id|pil
op_assign
id|irq_to_pil_map
(braket
id|irq_nr
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pil
op_eq
op_minus
l_int|1
)paren
id|baget_printk
c_func
(paren
l_string|&quot;irq_to_pil: unknown irq = 0x%x&bslash;n&quot;
comma
id|irq_nr
)paren
suffix:semicolon
)brace
r_return
id|pil
suffix:semicolon
)brace
multiline_comment|/* Function for careful CP0 interrupt mask access */
DECL|function|modify_cp0_intmask
r_static
r_inline
r_void
id|modify_cp0_intmask
c_func
(paren
r_int
id|clr_mask
comma
r_int
id|set_mask
)paren
(brace
r_int
r_int
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
suffix:semicolon
id|write_c0_status
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  These two functions may be used for unconditional IRQ&n; *  masking via their PIL protection.&n; */
DECL|function|mask_irq
r_static
r_inline
r_void
id|mask_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
id|modify_cp0_intmask
c_func
(paren
id|irq_to_pil
c_func
(paren
id|irq_nr
)paren
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
id|irq_nr
)paren
(brace
id|modify_cp0_intmask
c_func
(paren
l_int|0
comma
id|irq_to_pil
c_func
(paren
id|irq_nr
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following section is introduced for masking/unasking IRQ&n; * only while no more IRQs uses same CPU PIL.&n; *&n; * These functions are used in request_irq, free_irq, but it looks&n; * they cannot change something: CP0_STATUS is private for any&n; * process, and their action is invisible for system.&n; */
DECL|variable|pil_in_use
r_static
r_volatile
r_int
r_int
id|pil_in_use
(braket
id|BAGET_PIL_NR
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|function|mask_irq_count
r_void
id|mask_irq_count
c_func
(paren
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|pil
op_assign
id|irq_to_pil
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|pil_in_use
(braket
id|pil
)braket
)paren
id|mask_irq
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|unmask_irq_count
r_void
id|unmask_irq_count
c_func
(paren
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|pil
op_assign
id|irq_to_pil
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pil_in_use
(braket
id|pil
)braket
op_increment
)paren
id|unmask_irq
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Two functions below are exported versions of mask/unmask IRQ&n; */
DECL|function|disable_irq
r_void
id|disable_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|mask_irq
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|enable_irq
r_void
id|enable_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|unmask_irq
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Pointers to the low-level handlers: first the general ones, then the&n; * fast ones, then the bad ones.&n; */
DECL|variable|irq_action
r_static
r_struct
id|irqaction
op_star
id|irq_action
(braket
id|BAGET_IRQ_NR
)braket
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|get_irq_list
r_int
id|get_irq_list
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
id|i
comma
id|len
op_assign
l_int|0
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
r_int
id|flags
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
id|BAGET_IRQ_NR
suffix:semicolon
id|i
op_increment
)paren
(brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|action
op_assign
id|irq_action
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
id|gotos
id|skip
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%2d: %8d %c %s&quot;
comma
id|i
comma
id|kstat_this_cpu.irqs
(braket
id|i
)braket
comma
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot; &squot;
comma
id|action-&gt;name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|action
op_assign
id|action-&gt;next
suffix:semicolon
id|action
suffix:semicolon
id|action
op_assign
id|action-&gt;next
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;,%s %s&quot;
comma
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
ques
c_cond
l_string|&quot; +&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|skip
suffix:colon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * do_IRQ handles IRQ&squot;s that have been installed without the&n; * SA_INTERRUPT flag: it uses the full signal-handling return&n; * and runs with other interrupts enabled. All relatively slow&n; * IRQ&squot;s should use this format: notably the keyboard/timer&n; * routines.&n; */
DECL|function|do_IRQ
r_static
r_void
id|do_IRQ
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
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
id|ret
comma
id|do_random
comma
id|cpu
suffix:semicolon
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|kstat_cpus
c_func
(paren
id|cpu
)paren
dot
id|irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|mask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|action
op_assign
op_star
(paren
id|irq
op_plus
id|irq_action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
)paren
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|action
op_assign
op_star
(paren
id|irq
op_plus
id|irq_action
)paren
suffix:semicolon
id|do_random
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|ret
op_assign
id|action
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|action-&gt;dev_id
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|IRQ_HANDLED
)paren
id|do_random
op_or_assign
id|action-&gt;flags
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_random
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|add_interrupt_randomness
c_func
(paren
id|irq
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;do_IRQ: Unregistered IRQ (0x%X) occurred&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
id|unmask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* unmasking and bottom half handling is done magically for us. */
)brace
multiline_comment|/*&n; *  What to do in case of &squot;no VIC register available&squot; for current interrupt&n; */
DECL|function|vic_reg_error
r_static
r_void
id|vic_reg_error
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_char
id|active_pils
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nNo VIC register found: reg=%08lx active_pils=%02x&bslash;n&quot;
l_string|&quot;Current interrupt mask from CP0_CAUSE: %02x&bslash;n&quot;
comma
id|address
comma
l_int|0xff
op_amp
id|active_pils
comma
l_int|0xff
op_amp
(paren
id|read_c0_cause
c_func
(paren
)paren
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
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
l_int|10000
suffix:semicolon
id|i
op_increment
)paren
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
)brace
)brace
DECL|variable|baget_fpu_irq
r_static
r_char
id|baget_fpu_irq
op_assign
id|BAGET_FPU_IRQ
suffix:semicolon
DECL|macro|BAGET_INT_FPU
mdefine_line|#define BAGET_INT_FPU {(unsigned long)&amp;baget_fpu_irq, 1}
multiline_comment|/*&n; *  Main interrupt handler: interrupt demultiplexer&n; */
DECL|function|baget_interrupt
id|asmlinkage
r_void
id|baget_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_static
r_struct
id|baget_int_reg
id|int_reg
(braket
id|BAGET_PIL_NR
)braket
op_assign
(brace
id|BAGET_INT_NONE
comma
id|BAGET_INT_NONE
comma
id|BAGET_INT0_ACK
comma
id|BAGET_INT1_ACK
comma
id|BAGET_INT_NONE
comma
id|BAGET_INT_FPU
comma
id|BAGET_INT_NONE
comma
id|BAGET_INT5_ACK
)brace
suffix:semicolon
r_int
r_char
id|active_pils
suffix:semicolon
r_while
c_loop
(paren
(paren
id|active_pils
op_assign
id|read_c0_cause
c_func
(paren
)paren
op_rshift
l_int|8
)paren
)paren
(brace
r_int
id|pil
suffix:semicolon
r_struct
id|baget_int_reg
op_star
id|reg
suffix:semicolon
r_for
c_loop
(paren
id|pil
op_assign
l_int|0
suffix:semicolon
id|pil
OL
id|BAGET_PIL_NR
suffix:semicolon
id|pil
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|active_pils
op_amp
(paren
l_int|1
op_lshift
id|pil
)paren
)paren
)paren
r_continue
suffix:semicolon
id|reg
op_assign
op_amp
id|int_reg
(braket
id|pil
)braket
suffix:semicolon
r_if
c_cond
(paren
id|reg-&gt;address
)paren
(brace
r_extern
r_int
id|try_read
c_func
(paren
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|irq
op_assign
id|try_read
c_func
(paren
id|reg-&gt;address
comma
id|reg-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ne
op_minus
l_int|1
)paren
id|do_IRQ
c_func
(paren
id|BAGET_IRQ_MASK
c_func
(paren
id|irq
)paren
comma
id|regs
)paren
suffix:semicolon
r_else
id|vic_reg_error
c_func
(paren
id|reg-&gt;address
comma
id|active_pils
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;baget_interrupt: unknown interrupt &quot;
l_string|&quot;(pil = %d)&bslash;n&quot;
comma
id|pil
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/*&n; * Idea is to put all interrupts&n; * in a single table and differenciate them just by number.&n; */
DECL|function|setup_baget_irq
r_int
id|setup_baget_irq
c_func
(paren
r_int
id|irq
comma
r_struct
id|irqaction
op_star
r_new
)paren
(brace
r_int
id|shared
op_assign
l_int|0
suffix:semicolon
r_struct
id|irqaction
op_star
id|old
comma
op_star
op_star
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|p
op_assign
id|irq_action
op_plus
id|irq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|old
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Can&squot;t share interrupts unless both agree to */
r_if
c_cond
(paren
op_logical_neg
(paren
id|old-&gt;flags
op_amp
r_new
op_member_access_from_pointer
id|flags
op_amp
id|SA_SHIRQ
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Can&squot;t share interrupts unless both are same type */
r_if
c_cond
(paren
(paren
id|old-&gt;flags
op_xor
r_new
op_member_access_from_pointer
id|flags
)paren
op_amp
id|SA_INTERRUPT
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* add new interrupt at end of irq queue */
r_do
(brace
id|p
op_assign
op_amp
id|old-&gt;next
suffix:semicolon
id|old
op_assign
op_star
id|p
suffix:semicolon
)brace
r_while
c_loop
(paren
id|old
)paren
suffix:semicolon
id|shared
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|flags
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|rand_initialize_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|p
op_assign
r_new
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shared
)paren
(brace
id|unmask_irq_count
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|request_irq
r_int
id|request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|irqflags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
(brace
r_int
id|retval
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|BAGET_IRQ_NR
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|irq_to_pil_map
(braket
id|irq
)braket
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|action
op_assign
(paren
r_struct
id|irqaction
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irqaction
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|action-&gt;handler
op_assign
id|handler
suffix:semicolon
id|action-&gt;flags
op_assign
id|irqflags
suffix:semicolon
id|cpus_clear
c_func
(paren
id|action-&gt;mask
)paren
suffix:semicolon
id|action-&gt;name
op_assign
id|devname
suffix:semicolon
id|action-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|action-&gt;dev_id
op_assign
id|dev_id
suffix:semicolon
id|retval
op_assign
id|setup_baget_irq
c_func
(paren
id|irq
comma
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|kfree
c_func
(paren
id|action
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|request_irq
id|EXPORT_SYMBOL
c_func
(paren
id|request_irq
)paren
suffix:semicolon
DECL|function|free_irq
r_void
id|free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
r_struct
id|irqaction
op_star
id|action
comma
op_star
op_star
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|BAGET_IRQ_NR
)paren
id|printk
c_func
(paren
l_string|&quot;Trying to free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|irq
op_plus
id|irq_action
suffix:semicolon
(paren
id|action
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
suffix:semicolon
id|p
op_assign
op_amp
id|action-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|action-&gt;dev_id
op_ne
id|dev_id
)paren
r_continue
suffix:semicolon
multiline_comment|/* Found it - now free it */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
op_star
id|p
op_assign
id|action-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irq
(braket
id|irq_action
)braket
)paren
id|unmask_irq_count
c_func
(paren
id|irq
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|action
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Trying to free free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|free_irq
id|EXPORT_SYMBOL
c_func
(paren
id|free_irq
)paren
suffix:semicolon
DECL|function|probe_irq_on
r_int
r_int
id|probe_irq_on
(paren
r_void
)paren
(brace
multiline_comment|/* TODO */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|probe_irq_on
id|EXPORT_SYMBOL
c_func
(paren
id|probe_irq_on
)paren
suffix:semicolon
DECL|function|probe_irq_off
r_int
id|probe_irq_off
(paren
r_int
r_int
id|irqs
)paren
(brace
multiline_comment|/* TODO */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|probe_irq_off
id|EXPORT_SYMBOL
c_func
(paren
id|probe_irq_off
)paren
suffix:semicolon
DECL|function|write_err_interrupt
r_static
r_void
id|write_err_interrupt
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
op_star
(paren
r_volatile
r_char
op_star
)paren
id|BAGET_WRERR_ACK
op_assign
l_int|0
suffix:semicolon
)brace
DECL|variable|irq0
r_static
r_struct
id|irqaction
id|irq0
op_assign
(brace
id|write_err_interrupt
comma
id|SA_INTERRUPT
comma
id|CPU_MASK_NONE
comma
l_string|&quot;bus write error&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
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
id|irq_setup
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Enable access to VIC interrupt registers */
id|vac_outw
c_func
(paren
l_int|0xacef
op_or
l_int|0x8200
comma
id|VAC_PIO_FUNC
)paren
suffix:semicolon
multiline_comment|/* Enable interrupts for pils 2 and 3 (lines 0 and 1) */
id|modify_cp0_intmask
c_func
(paren
l_int|0
comma
(paren
l_int|1
op_lshift
l_int|2
)paren
op_or
(paren
l_int|1
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|setup_baget_irq
c_func
(paren
l_int|0
comma
op_amp
id|irq0
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;init_IRQ: unable to register write_err irq&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
