multiline_comment|/*&n; *&t;Apple Peripheral System Controller (PSC)&n; *&n; *&t;The PSC is used on the AV Macs to control IO functions not handled&n; *&t;by the VIAs (Ethernet, DSP, SCC).&n; *&n; * TO DO:&n; *&n; * Try to figure out what&squot;s going on in pIFR5 and pIFR6. There seem to be&n; * persisant interrupt conditions in those registers and I have no idea what&n; * they are. Granted it doesn&squot;t affect since we&squot;re not enabling any interrupts&n; * on those levels at the moment, but it would be nice to know. I have a feeling&n; * they aren&squot;t actually interrupt lines but data lines (to the DSP?)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt; 
macro_line|#include &lt;asm/macintosh.h&gt; 
macro_line|#include &lt;asm/macints.h&gt; 
macro_line|#include &lt;asm/mac_psc.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
DECL|macro|DEBUG_PSC
mdefine_line|#define DEBUG_PSC
DECL|variable|psc_present
r_int
id|psc_present
suffix:semicolon
DECL|variable|psc
r_volatile
id|__u8
op_star
id|psc
suffix:semicolon
id|irqreturn_t
id|psc_irq
c_func
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
suffix:semicolon
multiline_comment|/*&n; * Debugging dump, used in various places to see what&squot;s going on.&n; */
DECL|function|psc_debug_dump
r_void
id|psc_debug_dump
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|psc_present
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0x30
suffix:semicolon
id|i
OL
l_int|0x70
suffix:semicolon
id|i
op_add_assign
l_int|0x10
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PSC #%d:  IFR = 0x%02X IER = 0x%02X&bslash;n&quot;
comma
id|i
op_rshift
l_int|4
comma
(paren
r_int
)paren
id|psc_read_byte
c_func
(paren
id|pIFRbase
op_plus
id|i
)paren
comma
(paren
r_int
)paren
id|psc_read_byte
c_func
(paren
id|pIERbase
op_plus
id|i
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Try to kill all DMA channels on the PSC. Not sure how this his&n; * supposed to work; this is code lifted from macmace.c and then&n; * expanded to cover what I think are the other 7 channels.&n; */
DECL|function|psc_dma_die_die_die
r_void
id|psc_dma_die_die_die
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Killing all PSC DMA channels...&quot;
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
l_int|9
suffix:semicolon
id|i
op_increment
)paren
(brace
id|psc_write_word
c_func
(paren
id|PSC_CTL_BASE
op_plus
(paren
id|i
op_lshift
l_int|4
)paren
comma
l_int|0x8800
)paren
suffix:semicolon
id|psc_write_word
c_func
(paren
id|PSC_CTL_BASE
op_plus
(paren
id|i
op_lshift
l_int|4
)paren
comma
l_int|0x1000
)paren
suffix:semicolon
id|psc_write_word
c_func
(paren
id|PSC_CMD_BASE
op_plus
(paren
id|i
op_lshift
l_int|5
)paren
comma
l_int|0x1100
)paren
suffix:semicolon
id|psc_write_word
c_func
(paren
id|PSC_CMD_BASE
op_plus
(paren
id|i
op_lshift
l_int|5
)paren
op_plus
l_int|0x10
comma
l_int|0x1100
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;done!&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the PSC. For now this just involves shutting down all&n; * interrupt sources using the IERs.&n; */
DECL|function|psc_init
r_void
id|__init
id|psc_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|macintosh_config-&gt;ident
op_ne
id|MAC_MODEL_C660
op_logical_and
id|macintosh_config-&gt;ident
op_ne
id|MAC_MODEL_Q840
)paren
(brace
id|psc
op_assign
l_int|NULL
suffix:semicolon
id|psc_present
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The PSC is always at the same spot, but using psc&n;&t; * keeps things consisant with the psc_xxxx functions.&n;&t; */
id|psc
op_assign
(paren
r_void
op_star
)paren
id|PSC_BASE
suffix:semicolon
id|psc_present
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PSC detected at %p&bslash;n&quot;
comma
id|psc
)paren
suffix:semicolon
id|psc_dma_die_die_die
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_PSC
id|psc_debug_dump
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Mask and clear all possible interrupts&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0x30
suffix:semicolon
id|i
OL
l_int|0x70
suffix:semicolon
id|i
op_add_assign
l_int|0x10
)paren
(brace
id|psc_write_byte
c_func
(paren
id|pIERbase
op_plus
id|i
comma
l_int|0x0F
)paren
suffix:semicolon
id|psc_write_byte
c_func
(paren
id|pIFRbase
op_plus
id|i
comma
l_int|0x0F
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Register the PSC interrupt dispatchers for autovector interrupts 3-6.&n; */
DECL|function|psc_register_interrupts
r_void
id|__init
id|psc_register_interrupts
c_func
(paren
r_void
)paren
(brace
id|sys_request_irq
c_func
(paren
l_int|3
comma
id|psc_irq
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;psc3&quot;
comma
(paren
r_void
op_star
)paren
l_int|0x30
)paren
suffix:semicolon
id|sys_request_irq
c_func
(paren
l_int|4
comma
id|psc_irq
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;psc4&quot;
comma
(paren
r_void
op_star
)paren
l_int|0x40
)paren
suffix:semicolon
id|sys_request_irq
c_func
(paren
l_int|5
comma
id|psc_irq
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;psc5&quot;
comma
(paren
r_void
op_star
)paren
l_int|0x50
)paren
suffix:semicolon
id|sys_request_irq
c_func
(paren
l_int|6
comma
id|psc_irq
comma
id|IRQ_FLG_LOCK
comma
l_string|&quot;psc6&quot;
comma
(paren
r_void
op_star
)paren
l_int|0x60
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * PSC interrupt handler. It&squot;s a lot like the VIA interrupt handler.&n; */
DECL|function|psc_irq
id|irqreturn_t
id|psc_irq
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
id|pIFR
op_assign
id|pIFRbase
op_plus
(paren
(paren
r_int
)paren
id|dev_id
)paren
suffix:semicolon
r_int
id|pIER
op_assign
id|pIERbase
op_plus
(paren
(paren
r_int
)paren
id|dev_id
)paren
suffix:semicolon
r_int
id|base_irq
suffix:semicolon
r_int
id|irq_bit
comma
id|i
suffix:semicolon
r_int
r_char
id|events
suffix:semicolon
id|base_irq
op_assign
id|irq
op_lshift
l_int|3
suffix:semicolon
macro_line|#ifdef DEBUG_IRQS
id|printk
c_func
(paren
l_string|&quot;psc_irq: irq %d pIFR = 0x%02X pIER = 0x%02X&bslash;n&quot;
comma
id|irq
comma
(paren
r_int
)paren
id|psc_read_byte
c_func
(paren
id|pIFR
)paren
comma
(paren
r_int
)paren
id|psc_read_byte
c_func
(paren
id|pIER
)paren
)paren
suffix:semicolon
macro_line|#endif
id|events
op_assign
id|psc_read_byte
c_func
(paren
id|pIFR
)paren
op_amp
id|psc_read_byte
c_func
(paren
id|pIER
)paren
op_amp
l_int|0xF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|events
)paren
r_return
id|IRQ_NONE
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|irq_bit
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
comma
id|irq_bit
op_lshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|events
op_amp
id|irq_bit
)paren
(brace
id|psc_write_byte
c_func
(paren
id|pIER
comma
id|irq_bit
)paren
suffix:semicolon
id|mac_do_irq_list
c_func
(paren
id|base_irq
op_plus
id|i
comma
id|regs
)paren
suffix:semicolon
id|psc_write_byte
c_func
(paren
id|pIFR
comma
id|irq_bit
)paren
suffix:semicolon
id|psc_write_byte
c_func
(paren
id|pIER
comma
id|irq_bit
op_or
l_int|0x80
)paren
suffix:semicolon
)brace
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|psc_irq_enable
r_void
id|psc_irq_enable
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|irq_src
op_assign
id|IRQ_SRC
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
id|irq_idx
op_assign
id|IRQ_IDX
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
id|pIER
op_assign
id|pIERbase
op_plus
(paren
id|irq_src
op_lshift
l_int|4
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_IRQUSE
id|printk
c_func
(paren
l_string|&quot;psc_irq_enable(%d)&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
macro_line|#endif
id|psc_write_byte
c_func
(paren
id|pIER
comma
(paren
l_int|1
op_lshift
id|irq_idx
)paren
op_or
l_int|0x80
)paren
suffix:semicolon
)brace
DECL|function|psc_irq_disable
r_void
id|psc_irq_disable
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|irq_src
op_assign
id|IRQ_SRC
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
id|irq_idx
op_assign
id|IRQ_IDX
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
id|pIER
op_assign
id|pIERbase
op_plus
(paren
id|irq_src
op_lshift
l_int|4
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_IRQUSE
id|printk
c_func
(paren
l_string|&quot;psc_irq_disable(%d)&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
macro_line|#endif
id|psc_write_byte
c_func
(paren
id|pIER
comma
l_int|1
op_lshift
id|irq_idx
)paren
suffix:semicolon
)brace
DECL|function|psc_irq_clear
r_void
id|psc_irq_clear
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|irq_src
op_assign
id|IRQ_SRC
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
id|irq_idx
op_assign
id|IRQ_IDX
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
id|pIFR
op_assign
id|pIERbase
op_plus
(paren
id|irq_src
op_lshift
l_int|4
)paren
suffix:semicolon
id|psc_write_byte
c_func
(paren
id|pIFR
comma
l_int|1
op_lshift
id|irq_idx
)paren
suffix:semicolon
)brace
DECL|function|psc_irq_pending
r_int
id|psc_irq_pending
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|irq_src
op_assign
id|IRQ_SRC
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
id|irq_idx
op_assign
id|IRQ_IDX
c_func
(paren
id|irq
)paren
suffix:semicolon
r_int
id|pIFR
op_assign
id|pIERbase
op_plus
(paren
id|irq_src
op_lshift
l_int|4
)paren
suffix:semicolon
r_return
id|psc_read_byte
c_func
(paren
id|pIFR
)paren
op_amp
(paren
l_int|1
op_lshift
id|irq_idx
)paren
suffix:semicolon
)brace
eof
