multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/8xx_immap.h&gt;
macro_line|#include &lt;asm/mpc8xx.h&gt;
macro_line|#include &quot;ppc8xx_pic.h&quot;
multiline_comment|/* The 8xx internal interrupt controller.  It is usually&n; * the only interrupt controller.  Some boards, like the MBX and&n; * Sandpoint have the 8259 as a secondary controller.  Depending&n; * upon the processor type, the internal controller can have as&n; * few as 16 interrups or as many as 64.  We could use  the&n; * &quot;clear_bit()&quot; and &quot;set_bit()&quot; functions like other platforms,&n; * but they are overkill for us.&n; */
DECL|function|m8xx_mask_irq
r_static
r_void
id|m8xx_mask_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
id|bit
comma
id|word
suffix:semicolon
id|bit
op_assign
id|irq_nr
op_amp
l_int|0x1f
suffix:semicolon
id|word
op_assign
id|irq_nr
op_rshift
l_int|5
suffix:semicolon
id|ppc_cached_irq_mask
(braket
id|word
)braket
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
l_int|31
op_minus
id|bit
)paren
)paren
suffix:semicolon
(paren
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_siu_conf.sc_simask
op_assign
id|ppc_cached_irq_mask
(braket
id|word
)braket
suffix:semicolon
)brace
DECL|function|m8xx_unmask_irq
r_static
r_void
id|m8xx_unmask_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
id|bit
comma
id|word
suffix:semicolon
id|bit
op_assign
id|irq_nr
op_amp
l_int|0x1f
suffix:semicolon
id|word
op_assign
id|irq_nr
op_rshift
l_int|5
suffix:semicolon
id|ppc_cached_irq_mask
(braket
id|word
)braket
op_or_assign
(paren
l_int|1
op_lshift
(paren
l_int|31
op_minus
id|bit
)paren
)paren
suffix:semicolon
(paren
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_siu_conf.sc_simask
op_assign
id|ppc_cached_irq_mask
(braket
id|word
)braket
suffix:semicolon
)brace
DECL|function|m8xx_end_irq
r_static
r_void
id|m8xx_end_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq_nr
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
id|irq_nr
)braket
dot
id|action
)paren
(brace
r_int
id|bit
comma
id|word
suffix:semicolon
id|bit
op_assign
id|irq_nr
op_amp
l_int|0x1f
suffix:semicolon
id|word
op_assign
id|irq_nr
op_rshift
l_int|5
suffix:semicolon
id|ppc_cached_irq_mask
(braket
id|word
)braket
op_or_assign
(paren
l_int|1
op_lshift
(paren
l_int|31
op_minus
id|bit
)paren
)paren
suffix:semicolon
(paren
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_siu_conf.sc_simask
op_assign
id|ppc_cached_irq_mask
(braket
id|word
)braket
suffix:semicolon
)brace
)brace
DECL|function|m8xx_mask_and_ack
r_static
r_void
id|m8xx_mask_and_ack
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
id|bit
comma
id|word
suffix:semicolon
id|bit
op_assign
id|irq_nr
op_amp
l_int|0x1f
suffix:semicolon
id|word
op_assign
id|irq_nr
op_rshift
l_int|5
suffix:semicolon
id|ppc_cached_irq_mask
(braket
id|word
)braket
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
l_int|31
op_minus
id|bit
)paren
)paren
suffix:semicolon
(paren
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_siu_conf.sc_simask
op_assign
id|ppc_cached_irq_mask
(braket
id|word
)braket
suffix:semicolon
(paren
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_siu_conf.sc_sipend
op_assign
l_int|1
op_lshift
(paren
l_int|31
op_minus
id|bit
)paren
suffix:semicolon
)brace
DECL|variable|ppc8xx_pic
r_struct
id|hw_interrupt_type
id|ppc8xx_pic
op_assign
(brace
l_string|&quot; 8xx SIU  &quot;
comma
l_int|NULL
comma
l_int|NULL
comma
id|m8xx_unmask_irq
comma
id|m8xx_mask_irq
comma
id|m8xx_mask_and_ack
comma
id|m8xx_end_irq
comma
l_int|0
)brace
suffix:semicolon
macro_line|#if 0
r_void
id|m8xx_do_IRQ
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|cpu
)paren
(brace
r_int
id|irq
suffix:semicolon
r_int
r_int
id|bits
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* For MPC8xx, read the SIVEC register and shift the bits down&n;         * to get the irq number.         */
id|bits
op_assign
(paren
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_siu_conf.sc_sivec
suffix:semicolon
id|irq
op_assign
id|bits
op_rshift
l_int|26
suffix:semicolon
macro_line|#if 0
id|irq
op_add_assign
id|ppc8xx_pic.irq_offset
suffix:semicolon
macro_line|#endif
id|bits
op_assign
l_int|1UL
op_lshift
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Bogus interrupt %d from PC = %lx&bslash;n&quot;
comma
id|irq
comma
id|regs-&gt;nip
)paren
suffix:semicolon
id|ppc_spurious_interrupts
op_increment
suffix:semicolon
)brace
r_else
(brace
id|ppc_irq_dispatch_handler
c_func
(paren
id|regs
comma
id|irq
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/*&n; * We either return a valid interrupt or -1 if there is nothing pending&n; */
r_int
DECL|function|m8xx_get_irq
id|m8xx_get_irq
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
multiline_comment|/* For MPC8xx, read the SIVEC register and shift the bits down&n;&t; * to get the irq number.&n;&t; */
id|irq
op_assign
(paren
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
)paren
op_member_access_from_pointer
id|im_siu_conf.sc_sivec
op_rshift
l_int|26
suffix:semicolon
multiline_comment|/*&n;&t; * When we read the sivec without an interrupt to process, we will &n;&t; * get back SIU_LEVEL7.  In this case, return -1&n;&t; */
r_if
c_cond
(paren
id|irq
op_eq
id|SIU_LEVEL7
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
multiline_comment|/* The MBX is the only 8xx board that uses the 8259.&n;*/
macro_line|#if defined(CONFIG_MBX) &amp;&amp; defined(CONFIG_PCI)
DECL|function|mbx_i8259_action
r_void
id|mbx_i8259_action
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
r_int
id|bits
comma
id|irq
suffix:semicolon
multiline_comment|/* A bug in the QSpan chip causes it to give us 0xff always&n;&t; * when doing a character read.  So read 32 bits and shift.&n;&t; * This doesn&squot;t seem to return useful values anyway, but&n;&t; * read it to make sure things are acked.&n;&t; * -- Cort&n;&t; */
id|irq
op_assign
(paren
id|inl
c_func
(paren
l_int|0x508
)paren
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ne
l_int|0xff
)paren
id|printk
c_func
(paren
l_string|&quot;iack %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x0C
comma
l_int|0x20
)paren
suffix:semicolon
id|irq
op_assign
id|inb
c_func
(paren
l_int|0x20
)paren
op_amp
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
l_int|2
)paren
(brace
id|outb
c_func
(paren
l_int|0x0C
comma
l_int|0xA0
)paren
suffix:semicolon
id|irq
op_assign
id|inb
c_func
(paren
l_int|0xA0
)paren
suffix:semicolon
id|irq
op_assign
(paren
id|irq
op_amp
l_int|7
)paren
op_plus
l_int|8
suffix:semicolon
)brace
id|bits
op_assign
l_int|1UL
op_lshift
id|irq
suffix:semicolon
id|irq
op_add_assign
id|i8259_pic.irq_offset
suffix:semicolon
id|ppc_irq_dispatch_handler
c_func
(paren
id|regs
comma
id|irq
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Only the MBX uses the external 8259.  This allows us to catch standard&n; * drivers that may mess up the internal interrupt controllers, and also&n; * allow them to run without modification on the MBX.&n; */
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
macro_line|#if defined(CONFIG_MBX) &amp;&amp; defined(CONFIG_PCI)
id|irq
op_add_assign
id|i8259_pic.irq_offset
suffix:semicolon
r_return
(paren
id|request_8xxirq
c_func
(paren
id|irq
comma
id|handler
comma
id|irqflags
comma
id|devname
comma
id|dev_id
)paren
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n;&t; * Handle other &quot;well-known&quot; interrupts, but panic on unknown ones.&n;&t; */
r_switch
c_cond
(paren
id|irq
)paren
(brace
macro_line|#ifdef&t;IDE0_INTERRUPT
r_case
id|IDE0_INTERRUPT
suffix:colon
multiline_comment|/* IDE0 */
r_return
(paren
id|request_8xxirq
c_func
(paren
id|irq
comma
id|handler
comma
id|irqflags
comma
id|devname
comma
id|dev_id
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef&t;IDE1_INTERRUPT
r_case
id|IDE1_INTERRUPT
suffix:colon
multiline_comment|/* IDE1 */
r_return
(paren
id|request_8xxirq
c_func
(paren
id|irq
comma
id|handler
comma
id|irqflags
comma
id|devname
comma
id|dev_id
)paren
)paren
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
multiline_comment|/* unknown IRQ -&gt; panic */
id|panic
c_func
(paren
l_string|&quot;request_irq&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
eof
