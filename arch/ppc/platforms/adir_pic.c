multiline_comment|/*&n; * arch/ppc/platforms/adir_pic.c&n; * &n; * Interrupt controller support for SBS Adirondack&n; *&n; * By Michael Sokolov &lt;msokolov@ivan.Harhan.ORG&gt;&n; * based on the K2 and SCM versions by Matt Porter &lt;mporter@mvista.com&gt;&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/i8259.h&gt;
macro_line|#include &quot;adir.h&quot;
r_static
r_void
id|adir_onboard_pic_enable
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|adir_onboard_pic_disable
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
DECL|function|no_action
id|no_action
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
)brace
id|__init
r_static
r_void
DECL|function|adir_onboard_pic_init
id|adir_onboard_pic_init
c_func
(paren
r_void
)paren
(brace
r_volatile
id|u_short
op_star
id|maskreg
op_assign
(paren
r_volatile
id|u_short
op_star
)paren
id|ADIR_PROCA_INT_MASK
suffix:semicolon
multiline_comment|/* Disable all Adirondack onboard interrupts */
id|out_be16
c_func
(paren
id|maskreg
comma
l_int|0xFFFF
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|adir_onboard_pic_get_irq
id|adir_onboard_pic_get_irq
c_func
(paren
r_void
)paren
(brace
r_volatile
id|u_short
op_star
id|statreg
op_assign
(paren
r_volatile
id|u_short
op_star
)paren
id|ADIR_PROCA_INT_STAT
suffix:semicolon
r_int
id|irq
suffix:semicolon
id|u_short
id|int_status
comma
id|int_test
suffix:semicolon
id|int_status
op_assign
id|in_be16
c_func
(paren
id|statreg
)paren
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
comma
id|int_test
op_assign
l_int|1
suffix:semicolon
id|irq
OL
l_int|16
suffix:semicolon
id|irq
op_increment
comma
id|int_test
op_lshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|int_status
op_amp
id|int_test
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_eq
l_int|16
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
(paren
id|irq
op_plus
l_int|16
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|adir_onboard_pic_enable
id|adir_onboard_pic_enable
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_volatile
id|u_short
op_star
id|maskreg
op_assign
(paren
r_volatile
id|u_short
op_star
)paren
id|ADIR_PROCA_INT_MASK
suffix:semicolon
multiline_comment|/* Change irq to Adirondack onboard native value */
id|irq
op_sub_assign
l_int|16
suffix:semicolon
multiline_comment|/* Enable requested irq number */
id|out_be16
c_func
(paren
id|maskreg
comma
id|in_be16
c_func
(paren
id|maskreg
)paren
op_amp
op_complement
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
DECL|function|adir_onboard_pic_disable
id|adir_onboard_pic_disable
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_volatile
id|u_short
op_star
id|maskreg
op_assign
(paren
r_volatile
id|u_short
op_star
)paren
id|ADIR_PROCA_INT_MASK
suffix:semicolon
multiline_comment|/* Change irq to Adirondack onboard native value */
id|irq
op_sub_assign
l_int|16
suffix:semicolon
multiline_comment|/* Disable requested irq number */
id|out_be16
c_func
(paren
id|maskreg
comma
id|in_be16
c_func
(paren
id|maskreg
)paren
op_or
(paren
l_int|1
op_lshift
id|irq
)paren
)paren
suffix:semicolon
)brace
DECL|variable|adir_onboard_pic
r_static
r_struct
id|hw_interrupt_type
id|adir_onboard_pic
op_assign
(brace
l_string|&quot; ADIR PIC &quot;
comma
l_int|NULL
comma
l_int|NULL
comma
id|adir_onboard_pic_enable
comma
multiline_comment|/* unmask */
id|adir_onboard_pic_disable
comma
multiline_comment|/* mask */
id|adir_onboard_pic_disable
comma
multiline_comment|/* mask and ack */
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n; * Linux interrupt values are assigned as follows:&n; *&n; * &t;0-15&t;&t;VT82C686 8259 interrupts&n; * &t;16-31&t;&t;Adirondack CPLD interrupts&n; */
id|__init
r_void
DECL|function|adir_init_IRQ
id|adir_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Initialize the cascaded 8259&squot;s on the VT82C686 */
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
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|i8259_pic
suffix:semicolon
id|i8259_init
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* Initialize Adirondack CPLD PIC and enable 8259 interrupt cascade */
r_for
c_loop
(paren
id|i
op_assign
l_int|16
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
id|i
op_increment
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|adir_onboard_pic
suffix:semicolon
id|adir_onboard_pic_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Enable 8259 interrupt cascade */
id|request_irq
c_func
(paren
id|ADIR_IRQ_VT82C686_INTR
comma
id|no_action
comma
id|SA_INTERRUPT
comma
l_string|&quot;82c59 primary cascade&quot;
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_int
DECL|function|adir_get_irq
id|adir_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|irq
op_assign
id|adir_onboard_pic_get_irq
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
id|ADIR_IRQ_VT82C686_INTR
)paren
id|irq
op_assign
id|i8259_irq
c_func
(paren
id|regs
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
eof
