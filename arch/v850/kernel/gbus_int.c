multiline_comment|/*&n; * arch/v850/kernel/gbus_int.c -- Midas labs GBUS interrupt support&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
multiline_comment|/* The number of shared GINT interrupts. */
DECL|macro|NUM_GINTS
mdefine_line|#define NUM_GINTS   &t;4
multiline_comment|/* For each GINT interrupt, how many GBUS interrupts are using it.  */
DECL|variable|gint_num_active_irqs
r_static
r_int
id|gint_num_active_irqs
(braket
id|NUM_GINTS
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
multiline_comment|/* A table of GINTn interrupts we actually use.&n;   Note that we don&squot;t use GINT0 because all the boards we support treat it&n;   specially.  */
DECL|struct|used_gint
r_struct
id|used_gint
(brace
DECL|member|gint
r_int
id|gint
suffix:semicolon
DECL|member|priority
r_int
id|priority
suffix:semicolon
DECL|variable|used_gint
)brace
id|used_gint
(braket
)braket
op_assign
(brace
(brace
l_int|1
comma
id|GBUS_INT_PRIORITY_HIGH
)brace
comma
(brace
l_int|3
comma
id|GBUS_INT_PRIORITY_LOW
)brace
)brace
suffix:semicolon
DECL|macro|NUM_USED_GINTS
mdefine_line|#define NUM_USED_GINTS&t;(sizeof used_gint / sizeof used_gint[0])
multiline_comment|/* A table of which GINT is used by each GBUS interrupts (they are&n;   assigned based on priority).  */
DECL|variable|gbus_int_gint
r_static
r_int
r_char
id|gbus_int_gint
(braket
id|IRQ_GBUS_INT_NUM
)braket
suffix:semicolon
"&f;"
multiline_comment|/* Interrupt enabling/disabling.  */
multiline_comment|/* Enable interrupt handling for interrupt IRQ.  */
DECL|function|gbus_int_enable_irq
r_void
id|gbus_int_enable_irq
(paren
r_int
id|irq
)paren
(brace
r_int
id|gint
op_assign
id|gbus_int_gint
(braket
id|irq
op_minus
id|GBUS_INT_BASE_IRQ
)braket
suffix:semicolon
id|GBUS_INT_ENABLE
(paren
id|GBUS_INT_IRQ_WORD
c_func
(paren
id|irq
)paren
comma
id|gint
)paren
op_or_assign
id|GBUS_INT_IRQ_MASK
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/* Disable interrupt handling for interrupt IRQ.  Note that any&n;   interrupts received while disabled will be delivered once the&n;   interrupt is enabled again, unless they are explicitly cleared using&n;   `gbus_int_clear_pending_irq&squot;.  */
DECL|function|gbus_int_disable_irq
r_void
id|gbus_int_disable_irq
(paren
r_int
id|irq
)paren
(brace
r_int
id|gint
op_assign
id|gbus_int_gint
(braket
id|irq
op_minus
id|GBUS_INT_BASE_IRQ
)braket
suffix:semicolon
id|GBUS_INT_ENABLE
(paren
id|GBUS_INT_IRQ_WORD
c_func
(paren
id|irq
)paren
comma
id|gint
)paren
op_and_assign
op_complement
id|GBUS_INT_IRQ_MASK
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/* Return true if interrupt handling for interrupt IRQ is enabled.  */
DECL|function|gbus_int_irq_enabled
r_int
id|gbus_int_irq_enabled
(paren
r_int
id|irq
)paren
(brace
r_int
id|gint
op_assign
id|gbus_int_gint
(braket
id|irq
op_minus
id|GBUS_INT_BASE_IRQ
)braket
suffix:semicolon
r_return
(paren
id|GBUS_INT_ENABLE
(paren
id|GBUS_INT_IRQ_WORD
c_func
(paren
id|irq
)paren
comma
id|gint
)paren
op_amp
id|GBUS_INT_IRQ_MASK
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Disable all GBUS irqs.  */
DECL|function|gbus_int_disable_irqs
r_void
id|gbus_int_disable_irqs
(paren
)paren
(brace
r_int
id|w
comma
id|n
suffix:semicolon
r_for
c_loop
(paren
id|w
op_assign
l_int|0
suffix:semicolon
id|w
OL
id|GBUS_INT_NUM_WORDS
suffix:semicolon
id|w
op_increment
)paren
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|IRQ_GINT_NUM
suffix:semicolon
id|n
op_increment
)paren
id|GBUS_INT_ENABLE
(paren
id|w
comma
id|n
)paren
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Clear any pending interrupts for IRQ.  */
DECL|function|gbus_int_clear_pending_irq
r_void
id|gbus_int_clear_pending_irq
(paren
r_int
id|irq
)paren
(brace
id|GBUS_INT_CLEAR
(paren
id|GBUS_INT_IRQ_WORD
c_func
(paren
id|irq
)paren
)paren
op_assign
id|GBUS_INT_IRQ_MASK
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/* Return true if interrupt IRQ is pending (but disabled).  */
DECL|function|gbus_int_irq_pending
r_int
id|gbus_int_irq_pending
(paren
r_int
id|irq
)paren
(brace
r_return
(paren
id|GBUS_INT_STATUS
(paren
id|GBUS_INT_IRQ_WORD
c_func
(paren
id|irq
)paren
)paren
op_amp
id|GBUS_INT_IRQ_MASK
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
)brace
"&f;"
multiline_comment|/* Delegating interrupts.  */
multiline_comment|/* Handle a shared GINT interrupt by passing to the appropriate GBUS&n;   interrupt handler.  */
DECL|function|gbus_int_handle_irq
r_static
id|irqreturn_t
id|gbus_int_handle_irq
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
id|w
suffix:semicolon
id|irqreturn_t
id|rval
op_assign
id|IRQ_NONE
suffix:semicolon
r_int
id|gint
op_assign
id|irq
op_minus
id|IRQ_GINT
(paren
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|w
op_assign
l_int|0
suffix:semicolon
id|w
OL
id|GBUS_INT_NUM_WORDS
suffix:semicolon
id|w
op_increment
)paren
(brace
r_int
id|status
op_assign
id|GBUS_INT_STATUS
(paren
id|w
)paren
suffix:semicolon
r_int
id|enable
op_assign
id|GBUS_INT_ENABLE
(paren
id|w
comma
id|gint
)paren
suffix:semicolon
multiline_comment|/* Only pay attention to enabled interrupts.  */
id|status
op_and_assign
id|enable
suffix:semicolon
r_if
c_cond
(paren
id|status
)paren
(brace
r_int
id|base_irq
op_assign
id|IRQ_GBUS_INT
(paren
id|w
op_star
id|GBUS_INT_BITS_PER_WORD
)paren
suffix:semicolon
id|irq
op_assign
id|base_irq
suffix:semicolon
r_do
(brace
multiline_comment|/* There&squot;s an active interrupt in word&n;&t;&t;&t;&t;   W, find out which one, and call its&n;&t;&t;&t;&t;   handler.  */
r_while
c_loop
(paren
op_logical_neg
(paren
id|status
op_amp
l_int|0x1
)paren
)paren
(brace
id|irq
op_increment
suffix:semicolon
id|status
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|status
op_and_assign
op_complement
l_int|0x1
suffix:semicolon
multiline_comment|/* Recursively call handle_irq to handle it. */
id|handle_irq
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
id|rval
op_assign
id|IRQ_HANDLED
suffix:semicolon
)brace
r_while
c_loop
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Toggle the `all enable&squot; bit back and forth, which should cause&n;&t;   another edge transition if there are any other interrupts&n;&t;   still pending, and so result in another CPU interrupt.  */
id|GBUS_INT_ENABLE
(paren
l_int|0
comma
id|gint
)paren
op_and_assign
op_complement
l_int|0x1
suffix:semicolon
id|GBUS_INT_ENABLE
(paren
l_int|0
comma
id|gint
)paren
op_or_assign
l_int|0x1
suffix:semicolon
r_return
id|rval
suffix:semicolon
)brace
"&f;"
multiline_comment|/* Initialize GBUS interrupt sources.  */
DECL|function|irq_nop
r_static
r_void
id|irq_nop
(paren
r_int
id|irq
)paren
(brace
)brace
DECL|function|gbus_int_startup_irq
r_static
r_int
id|gbus_int_startup_irq
(paren
r_int
id|irq
)paren
(brace
r_int
id|gint
op_assign
id|gbus_int_gint
(braket
id|irq
op_minus
id|GBUS_INT_BASE_IRQ
)braket
suffix:semicolon
r_if
c_cond
(paren
id|gint_num_active_irqs
(braket
id|gint
)braket
op_eq
l_int|0
)paren
(brace
multiline_comment|/* First enable the CPU interrupt.  */
r_int
id|rval
op_assign
id|request_irq
(paren
id|IRQ_GINT
c_func
(paren
id|gint
)paren
comma
id|gbus_int_handle_irq
comma
id|SA_INTERRUPT
comma
l_string|&quot;gbus_int_handler&quot;
comma
op_amp
id|gint_num_active_irqs
(braket
id|gint
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rval
op_ne
l_int|0
)paren
r_return
id|rval
suffix:semicolon
)brace
id|gint_num_active_irqs
(braket
id|gint
)braket
op_increment
suffix:semicolon
id|gbus_int_clear_pending_irq
(paren
id|irq
)paren
suffix:semicolon
id|gbus_int_enable_irq
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gbus_int_shutdown_irq
r_static
r_void
id|gbus_int_shutdown_irq
(paren
r_int
id|irq
)paren
(brace
r_int
id|gint
op_assign
id|gbus_int_gint
(braket
id|irq
op_minus
id|GBUS_INT_BASE_IRQ
)braket
suffix:semicolon
id|gbus_int_disable_irq
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|gint_num_active_irqs
(braket
id|gint
)braket
op_eq
l_int|0
)paren
multiline_comment|/* Disable the CPU interrupt.  */
id|free_irq
(paren
id|IRQ_GINT
c_func
(paren
id|gint
)paren
comma
op_amp
id|gint_num_active_irqs
(braket
id|gint
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize HW_IRQ_TYPES for INTC-controlled irqs described in array&n;   INITS (which is terminated by an entry with the name field == 0).  */
DECL|function|gbus_int_init_irq_types
r_void
id|__init
id|gbus_int_init_irq_types
(paren
r_struct
id|gbus_int_irq_init
op_star
id|inits
comma
r_struct
id|hw_interrupt_type
op_star
id|hw_irq_types
)paren
(brace
r_struct
id|gbus_int_irq_init
op_star
id|init
suffix:semicolon
r_for
c_loop
(paren
id|init
op_assign
id|inits
suffix:semicolon
id|init-&gt;name
suffix:semicolon
id|init
op_increment
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|hw_interrupt_type
op_star
id|hwit
op_assign
id|hw_irq_types
op_increment
suffix:semicolon
id|hwit
op_member_access_from_pointer
r_typename
op_assign
id|init-&gt;name
suffix:semicolon
id|hwit-&gt;startup
op_assign
id|gbus_int_startup_irq
suffix:semicolon
id|hwit-&gt;shutdown
op_assign
id|gbus_int_shutdown_irq
suffix:semicolon
id|hwit-&gt;enable
op_assign
id|gbus_int_enable_irq
suffix:semicolon
id|hwit-&gt;disable
op_assign
id|gbus_int_disable_irq
suffix:semicolon
id|hwit-&gt;ack
op_assign
id|irq_nop
suffix:semicolon
id|hwit-&gt;end
op_assign
id|irq_nop
suffix:semicolon
multiline_comment|/* Initialize kernel IRQ infrastructure for this interrupt.  */
id|init_irq_handlers
c_func
(paren
id|init-&gt;base
comma
id|init-&gt;num
comma
id|init-&gt;interval
comma
id|hwit
)paren
suffix:semicolon
multiline_comment|/* Set the interrupt priorities.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|init-&gt;num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NUM_USED_GINTS
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|used_gint
(braket
id|j
)braket
dot
id|priority
OG
id|init-&gt;priority
)paren
r_break
suffix:semicolon
multiline_comment|/* Wherever we stopped looking is one past the&n;&t;&t;&t;   GINT we want. */
id|gbus_int_gint
(braket
id|init-&gt;base
op_plus
id|i
op_star
id|init-&gt;interval
op_minus
id|GBUS_INT_BASE_IRQ
)braket
op_assign
id|used_gint
(braket
id|j
OG
l_int|0
ques
c_cond
id|j
op_minus
l_int|1
suffix:colon
l_int|0
)braket
dot
id|gint
suffix:semicolon
)brace
)brace
)brace
"&f;"
multiline_comment|/* Initialize IRQS.  */
multiline_comment|/* Chip interrupts (GINTn) shared among GBUS interrupts.  */
DECL|variable|gint_hw_itypes
r_static
r_struct
id|hw_interrupt_type
id|gint_hw_itypes
(braket
id|NUM_USED_GINTS
)braket
suffix:semicolon
multiline_comment|/* GBUS interrupts themselves.  */
DECL|variable|__initdata
r_struct
id|gbus_int_irq_init
id|gbus_irq_inits
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* First set defaults.  */
(brace
l_string|&quot;GBUS_INT&quot;
comma
id|IRQ_GBUS_INT
c_func
(paren
l_int|0
)paren
comma
id|IRQ_GBUS_INT_NUM
comma
l_int|1
comma
l_int|6
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|NUM_GBUS_IRQ_INITS
mdefine_line|#define NUM_GBUS_IRQ_INITS  &bslash;&n;   ((sizeof gbus_irq_inits / sizeof gbus_irq_inits[0]) - 1)
DECL|variable|gbus_hw_itypes
r_static
r_struct
id|hw_interrupt_type
id|gbus_hw_itypes
(braket
id|NUM_GBUS_IRQ_INITS
)braket
suffix:semicolon
multiline_comment|/* Initialize GBUS interrupts.  */
DECL|function|gbus_int_init_irqs
r_void
id|__init
id|gbus_int_init_irqs
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* First initialize the shared gint interrupts.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_USED_GINTS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|gint
op_assign
id|used_gint
(braket
id|i
)braket
dot
id|gint
suffix:semicolon
r_struct
id|v850e_intc_irq_init
id|gint_irq_init
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* We initialize one GINT interrupt at a time.  */
id|gint_irq_init
(braket
l_int|0
)braket
dot
id|name
op_assign
l_string|&quot;GINT&quot;
suffix:semicolon
id|gint_irq_init
(braket
l_int|0
)braket
dot
id|base
op_assign
id|IRQ_GINT
(paren
id|gint
)paren
suffix:semicolon
id|gint_irq_init
(braket
l_int|0
)braket
dot
id|num
op_assign
l_int|1
suffix:semicolon
id|gint_irq_init
(braket
l_int|0
)braket
dot
id|interval
op_assign
l_int|1
suffix:semicolon
id|gint_irq_init
(braket
l_int|0
)braket
dot
id|priority
op_assign
id|used_gint
(braket
id|i
)braket
dot
id|priority
suffix:semicolon
id|gint_irq_init
(braket
l_int|1
)braket
dot
id|name
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Terminate the vector.  */
id|v850e_intc_init_irq_types
(paren
id|gint_irq_init
comma
id|gint_hw_itypes
)paren
suffix:semicolon
)brace
multiline_comment|/* Then the GBUS interrupts.  */
id|gbus_int_disable_irqs
(paren
)paren
suffix:semicolon
id|gbus_int_init_irq_types
(paren
id|gbus_irq_inits
comma
id|gbus_hw_itypes
)paren
suffix:semicolon
multiline_comment|/* Turn on the `all enable&squot; bits, which are ANDed with&n;&t;   individual interrupt enable bits; we only want to bother with&n;&t;   the latter.  They are the first bit in the first word of each&n;&t;   interrupt-enable area.  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_USED_GINTS
suffix:semicolon
id|i
op_increment
)paren
id|GBUS_INT_ENABLE
(paren
l_int|0
comma
id|used_gint
(braket
id|i
)braket
dot
id|gint
)paren
op_assign
l_int|0x1
suffix:semicolon
)brace
eof
