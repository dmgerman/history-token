multiline_comment|/*&n; * linux/arch/h8300/platform/h8s/ints_h8s.c&n; * Interrupt handling CPU variants&n; *&n; * Yoshinori Sato &lt;ysato@users.sourceforge.jp&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/gpio.h&gt;
macro_line|#include &lt;asm/regs267x.h&gt;
multiline_comment|/* saved vector list */
DECL|variable|h8300_saved_vectors
r_const
r_int
id|__initdata
id|h8300_saved_vectors
(braket
)braket
op_assign
initialization_block
suffix:semicolon
multiline_comment|/* trap entry table */
DECL|variable|h8300_trap_table
r_const
r_int
r_int
id|__initdata
id|h8300_trap_table
(braket
id|NR_TRAPS
)braket
op_assign
initialization_block
suffix:semicolon
multiline_comment|/* IRQ pin assignment */
DECL|struct|irq_pins
r_struct
id|irq_pins
(brace
DECL|member|port_no
r_int
r_char
id|port_no
suffix:semicolon
DECL|member|bit_no
r_int
r_char
id|bit_no
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|1
)paren
comma
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* ISTR = 0 */
DECL|variable|irq_assign_table0
r_const
r_static
r_struct
id|irq_pins
id|irq_assign_table0
(braket
l_int|16
)braket
op_assign
initialization_block
suffix:semicolon
multiline_comment|/* ISTR = 1 */
DECL|variable|irq_assign_table1
r_const
r_static
r_struct
id|irq_pins
id|irq_assign_table1
(braket
l_int|16
)braket
op_assign
initialization_block
suffix:semicolon
multiline_comment|/* IRQ to GPIO pinno transrate */
DECL|macro|IRQ_GPIO_MAP
mdefine_line|#define IRQ_GPIO_MAP(irqbit,irq,port,bit)&t;&t;&t;  &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;if (*(volatile unsigned short *)ITSR &amp; irqbit) {&t;  &bslash;&n;&t;&t;port = irq_assign_table1[irq - EXT_IRQ0].port_no; &bslash;&n;&t;&t;bit  = irq_assign_table1[irq - EXT_IRQ0].bit_no;  &bslash;&n;&t;} else {&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;port = irq_assign_table0[irq - EXT_IRQ0].port_no; &bslash;&n;&t;&t;bit  = irq_assign_table0[irq - EXT_IRQ0].bit_no;  &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;} while(0)
DECL|function|h8300_enable_irq_pin
r_int
id|h8300_enable_irq_pin
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
id|irq
op_ge
id|EXT_IRQ0
op_logical_and
id|irq
op_le
id|EXT_IRQ15
)paren
(brace
r_int
r_int
id|ptn
op_assign
l_int|1
op_lshift
(paren
id|irq
op_minus
id|EXT_IRQ0
)paren
suffix:semicolon
r_int
r_int
id|port_no
comma
id|bit_no
suffix:semicolon
id|IRQ_GPIO_MAP
c_func
(paren
id|ptn
comma
id|irq
comma
id|port_no
comma
id|bit_no
)paren
suffix:semicolon
r_if
c_cond
(paren
id|H8300_GPIO_RESERVE
c_func
(paren
id|port_no
comma
id|bit_no
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* pin already use */
id|H8300_GPIO_DDR
c_func
(paren
id|port_no
comma
id|bit_no
comma
id|H8300_GPIO_INPUT
)paren
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ISR
op_and_assign
op_complement
id|ptn
suffix:semicolon
multiline_comment|/* ISR clear */
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|h8300_disable_irq_pin
r_void
id|h8300_disable_irq_pin
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
id|irq
op_ge
id|EXT_IRQ0
op_logical_and
id|irq
op_le
id|EXT_IRQ15
)paren
(brace
multiline_comment|/* disable interrupt &amp; release IRQ pin */
r_int
r_int
id|ptn
op_assign
l_int|1
op_lshift
(paren
id|irq
op_minus
id|EXT_IRQ0
)paren
suffix:semicolon
r_int
r_int
id|port_no
comma
id|bit_no
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|ISR
op_and_assign
op_complement
id|ptn
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|IER
op_and_assign
op_complement
id|ptn
suffix:semicolon
id|IRQ_GPIO_MAP
c_func
(paren
id|ptn
comma
id|port_no
comma
id|bit_no
)paren
suffix:semicolon
id|H8300_GPIO_FREE
c_func
(paren
id|port_no
comma
id|bit_no
)paren
suffix:semicolon
)brace
)brace
eof
