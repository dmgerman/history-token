multiline_comment|/*&n; * linux/arch/sh/kernel/mach_rts7751r2d.c&n; *&n; * Minor tweak of mach_se.c file to reference rts7751r2d-specific items.&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * Machine vector for the Renesas Technology sales RTS7751R2D&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/rts7751r2d/io.h&gt;
r_extern
r_void
id|heartbeat_rts7751r2d
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|init_rts7751r2d_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
op_star
id|rts7751r2d_ioremap
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|rts7751r2d_irq_demux
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_extern
r_void
op_star
id|voyagergx_consistent_alloc
c_func
(paren
r_struct
id|device
op_star
comma
r_int
comma
id|dma_addr_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|voyagergx_consistent_free
c_func
(paren
r_struct
id|device
op_star
comma
r_int
comma
r_void
op_star
comma
id|dma_addr_t
)paren
suffix:semicolon
multiline_comment|/*&n; * The Machine Vector&n; */
DECL|variable|__initmv
r_struct
id|sh_machine_vector
id|mv_rts7751r2d
id|__initmv
op_assign
(brace
dot
id|mv_nr_irqs
op_assign
l_int|72
comma
dot
id|mv_inb
op_assign
id|rts7751r2d_inb
comma
dot
id|mv_inw
op_assign
id|rts7751r2d_inw
comma
dot
id|mv_inl
op_assign
id|rts7751r2d_inl
comma
dot
id|mv_outb
op_assign
id|rts7751r2d_outb
comma
dot
id|mv_outw
op_assign
id|rts7751r2d_outw
comma
dot
id|mv_outl
op_assign
id|rts7751r2d_outl
comma
dot
id|mv_inb_p
op_assign
id|rts7751r2d_inb_p
comma
dot
id|mv_inw_p
op_assign
id|rts7751r2d_inw
comma
dot
id|mv_inl_p
op_assign
id|rts7751r2d_inl
comma
dot
id|mv_outb_p
op_assign
id|rts7751r2d_outb_p
comma
dot
id|mv_outw_p
op_assign
id|rts7751r2d_outw
comma
dot
id|mv_outl_p
op_assign
id|rts7751r2d_outl
comma
dot
id|mv_insb
op_assign
id|rts7751r2d_insb
comma
dot
id|mv_insw
op_assign
id|rts7751r2d_insw
comma
dot
id|mv_insl
op_assign
id|rts7751r2d_insl
comma
dot
id|mv_outsb
op_assign
id|rts7751r2d_outsb
comma
dot
id|mv_outsw
op_assign
id|rts7751r2d_outsw
comma
dot
id|mv_outsl
op_assign
id|rts7751r2d_outsl
comma
dot
id|mv_ioremap
op_assign
id|rts7751r2d_ioremap
comma
dot
id|mv_isa_port2addr
op_assign
id|rts7751r2d_isa_port2addr
comma
dot
id|mv_init_irq
op_assign
id|init_rts7751r2d_IRQ
comma
macro_line|#ifdef CONFIG_HEARTBEAT
dot
id|mv_heartbeat
op_assign
id|heartbeat_rts7751r2d
comma
macro_line|#endif
dot
id|mv_irq_demux
op_assign
id|rts7751r2d_irq_demux
comma
macro_line|#ifdef CONFIG_USB_OHCI_HCD
dot
id|mv_consistent_alloc
op_assign
id|voyagergx_consistent_alloc
comma
dot
id|mv_consistent_free
op_assign
id|voyagergx_consistent_free
comma
macro_line|#endif
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|rts7751r2d
)paren
eof
