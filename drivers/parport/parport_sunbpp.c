multiline_comment|/* $Id: parport_sunbpp.c,v 1.12 2001/05/26 03:01:42 davem Exp $&n; * Parallel-port routines for Sun architecture&n; * &n; * Author: Derrick J. Brashear &lt;shadow@dementia.org&gt;&n; *&n; * based on work by:&n; *          Phil Blundell &lt;Philip.Blundell@pobox.com&gt;&n; *          Tim Waugh &lt;tim@cyberelk.demon.co.uk&gt;&n; *&t;    Jose Renau &lt;renau@acm.org&gt;&n; *          David Campbell &lt;campbell@tirian.che.curtin.edu.au&gt;&n; *          Grant Guenther &lt;grant@torque.net&gt;&n; *          Eddie C. Dost &lt;ecd@skynet.be&gt;&n; *          Stephen Williams (steve@icarus.com)&n; *          Gus Baldauf (gbaldauf@ix.netcom.com)&n; *          Peter Zaitcev&n; *          Tom Dyas&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;           /* OpenProm Library */
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/dma.h&gt;             /* BPP uses LSI 64854 for DMA */
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/sunbpp.h&gt;
DECL|macro|__SUNBPP_DEBUG
macro_line|#undef __SUNBPP_DEBUG
macro_line|#ifdef __SUNBPP_DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(x) printk x
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(x)
macro_line|#endif
DECL|function|parport_sunbpp_interrupt
r_static
r_void
id|parport_sunbpp_interrupt
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
id|parport_generic_irq
c_func
(paren
id|irq
comma
(paren
r_struct
id|parport
op_star
)paren
id|dev_id
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|parport_sunbpp_disable_irq
r_static
r_void
id|parport_sunbpp_disable_irq
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_struct
id|bpp_regs
op_star
id|regs
op_assign
(paren
r_struct
id|bpp_regs
op_star
)paren
id|p-&gt;base
suffix:semicolon
id|u32
id|tmp
suffix:semicolon
id|tmp
op_assign
id|sbus_readl
c_func
(paren
op_amp
id|regs-&gt;p_csr
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
id|DMA_INT_ENAB
suffix:semicolon
id|sbus_writel
c_func
(paren
id|tmp
comma
op_amp
id|regs-&gt;p_csr
)paren
suffix:semicolon
)brace
DECL|function|parport_sunbpp_enable_irq
r_static
r_void
id|parport_sunbpp_enable_irq
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_struct
id|bpp_regs
op_star
id|regs
op_assign
(paren
r_struct
id|bpp_regs
op_star
)paren
id|p-&gt;base
suffix:semicolon
id|u32
id|tmp
suffix:semicolon
id|tmp
op_assign
id|sbus_readl
c_func
(paren
op_amp
id|regs-&gt;p_csr
)paren
suffix:semicolon
id|tmp
op_or_assign
id|DMA_INT_ENAB
suffix:semicolon
id|sbus_writel
c_func
(paren
id|tmp
comma
op_amp
id|regs-&gt;p_csr
)paren
suffix:semicolon
)brace
DECL|function|parport_sunbpp_write_data
r_static
r_void
id|parport_sunbpp_write_data
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|d
)paren
(brace
r_struct
id|bpp_regs
op_star
id|regs
op_assign
(paren
r_struct
id|bpp_regs
op_star
)paren
id|p-&gt;base
suffix:semicolon
id|sbus_writeb
c_func
(paren
id|d
comma
op_amp
id|regs-&gt;p_dr
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;wrote 0x%x&bslash;n&quot;
comma
id|d
)paren
)paren
suffix:semicolon
)brace
DECL|function|parport_sunbpp_read_data
r_static
r_int
r_char
id|parport_sunbpp_read_data
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_struct
id|bpp_regs
op_star
id|regs
op_assign
(paren
r_struct
id|bpp_regs
op_star
)paren
id|p-&gt;base
suffix:semicolon
r_return
id|sbus_readb
c_func
(paren
op_amp
id|regs-&gt;p_dr
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_void
id|control_pc_to_sunbpp
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|status
)paren
(brace
r_struct
id|bpp_regs
op_star
id|regs
op_assign
(paren
r_struct
id|bpp_regs
op_star
)paren
id|p-&gt;base
suffix:semicolon
r_int
r_char
id|value_tcr
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|regs-&gt;p_tcr
)paren
suffix:semicolon
r_int
r_char
id|value_or
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|regs-&gt;p_or
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|PARPORT_CONTROL_STROBE
)paren
id|value_tcr
op_or_assign
id|P_TCR_DS
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|PARPORT_CONTROL_AUTOFD
)paren
id|value_or
op_or_assign
id|P_OR_AFXN
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|PARPORT_CONTROL_INIT
)paren
id|value_or
op_or_assign
id|P_OR_INIT
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|PARPORT_CONTROL_SELECT
)paren
id|value_or
op_or_assign
id|P_OR_SLCT_IN
suffix:semicolon
id|sbus_writeb
c_func
(paren
id|value_or
comma
op_amp
id|regs-&gt;p_or
)paren
suffix:semicolon
id|sbus_writeb
c_func
(paren
id|value_tcr
comma
op_amp
id|regs-&gt;p_tcr
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|status_sunbpp_to_pc
r_static
r_int
r_char
id|status_sunbpp_to_pc
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_struct
id|bpp_regs
op_star
id|regs
op_assign
(paren
r_struct
id|bpp_regs
op_star
)paren
id|p-&gt;base
suffix:semicolon
r_int
r_char
id|bits
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|value_tcr
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|regs-&gt;p_tcr
)paren
suffix:semicolon
r_int
r_char
id|value_ir
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|regs-&gt;p_ir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|value_ir
op_amp
id|P_IR_ERR
)paren
)paren
id|bits
op_or_assign
id|PARPORT_STATUS_ERROR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|value_ir
op_amp
id|P_IR_SLCT
)paren
)paren
id|bits
op_or_assign
id|PARPORT_STATUS_SELECT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|value_ir
op_amp
id|P_IR_PE
)paren
)paren
id|bits
op_or_assign
id|PARPORT_STATUS_PAPEROUT
suffix:semicolon
r_if
c_cond
(paren
id|value_tcr
op_amp
id|P_TCR_ACK
)paren
id|bits
op_or_assign
id|PARPORT_STATUS_ACK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|value_tcr
op_amp
id|P_TCR_BUSY
)paren
)paren
id|bits
op_or_assign
id|PARPORT_STATUS_BUSY
suffix:semicolon
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;tcr 0x%x ir 0x%x&bslash;n&quot;
comma
id|regs-&gt;p_tcr
comma
id|regs-&gt;p_ir
)paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;read status 0x%x&bslash;n&quot;
comma
id|bits
)paren
)paren
suffix:semicolon
r_return
id|bits
suffix:semicolon
)brace
DECL|function|control_sunbpp_to_pc
r_static
r_int
r_char
id|control_sunbpp_to_pc
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_struct
id|bpp_regs
op_star
id|regs
op_assign
(paren
r_struct
id|bpp_regs
op_star
)paren
id|p-&gt;base
suffix:semicolon
r_int
r_char
id|bits
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|value_tcr
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|regs-&gt;p_tcr
)paren
suffix:semicolon
r_int
r_char
id|value_or
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|regs-&gt;p_or
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|value_tcr
op_amp
id|P_TCR_DS
)paren
)paren
id|bits
op_or_assign
id|PARPORT_CONTROL_STROBE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|value_or
op_amp
id|P_OR_AFXN
)paren
)paren
id|bits
op_or_assign
id|PARPORT_CONTROL_AUTOFD
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|value_or
op_amp
id|P_OR_INIT
)paren
)paren
id|bits
op_or_assign
id|PARPORT_CONTROL_INIT
suffix:semicolon
r_if
c_cond
(paren
id|value_or
op_amp
id|P_OR_SLCT_IN
)paren
id|bits
op_or_assign
id|PARPORT_CONTROL_SELECT
suffix:semicolon
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;tcr 0x%x or 0x%x&bslash;n&quot;
comma
id|regs-&gt;p_tcr
comma
id|regs-&gt;p_or
)paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;read control 0x%x&bslash;n&quot;
comma
id|bits
)paren
)paren
suffix:semicolon
r_return
id|bits
suffix:semicolon
)brace
DECL|function|parport_sunbpp_read_control
r_static
r_int
r_char
id|parport_sunbpp_read_control
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_return
id|control_sunbpp_to_pc
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|parport_sunbpp_frob_control
r_static
r_int
r_char
id|parport_sunbpp_frob_control
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|mask
comma
r_int
r_char
id|val
)paren
(brace
r_struct
id|bpp_regs
op_star
id|regs
op_assign
(paren
r_struct
id|bpp_regs
op_star
)paren
id|p-&gt;base
suffix:semicolon
r_int
r_char
id|value_tcr
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|regs-&gt;p_tcr
)paren
suffix:semicolon
r_int
r_char
id|value_or
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|regs-&gt;p_or
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;frob1: tcr 0x%x or 0x%x&bslash;n&quot;
comma
id|regs-&gt;p_tcr
comma
id|regs-&gt;p_or
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
id|PARPORT_CONTROL_STROBE
)paren
(brace
r_if
c_cond
(paren
id|val
op_amp
id|PARPORT_CONTROL_STROBE
)paren
(brace
id|value_tcr
op_and_assign
op_complement
id|P_TCR_DS
suffix:semicolon
)brace
r_else
(brace
id|value_tcr
op_or_assign
id|P_TCR_DS
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|mask
op_amp
id|PARPORT_CONTROL_AUTOFD
)paren
(brace
r_if
c_cond
(paren
id|val
op_amp
id|PARPORT_CONTROL_AUTOFD
)paren
(brace
id|value_or
op_and_assign
op_complement
id|P_OR_AFXN
suffix:semicolon
)brace
r_else
(brace
id|value_or
op_or_assign
id|P_OR_AFXN
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|mask
op_amp
id|PARPORT_CONTROL_INIT
)paren
(brace
r_if
c_cond
(paren
id|val
op_amp
id|PARPORT_CONTROL_INIT
)paren
(brace
id|value_or
op_and_assign
op_complement
id|P_OR_INIT
suffix:semicolon
)brace
r_else
(brace
id|value_or
op_or_assign
id|P_OR_INIT
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|mask
op_amp
id|PARPORT_CONTROL_SELECT
)paren
(brace
r_if
c_cond
(paren
id|val
op_amp
id|PARPORT_CONTROL_SELECT
)paren
(brace
id|value_or
op_or_assign
id|P_OR_SLCT_IN
suffix:semicolon
)brace
r_else
(brace
id|value_or
op_and_assign
op_complement
id|P_OR_SLCT_IN
suffix:semicolon
)brace
)brace
id|sbus_writeb
c_func
(paren
id|value_or
comma
op_amp
id|regs-&gt;p_or
)paren
suffix:semicolon
id|sbus_writeb
c_func
(paren
id|value_tcr
comma
op_amp
id|regs-&gt;p_tcr
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;frob2: tcr 0x%x or 0x%x&bslash;n&quot;
comma
id|regs-&gt;p_tcr
comma
id|regs-&gt;p_or
)paren
)paren
suffix:semicolon
r_return
id|parport_sunbpp_read_control
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|parport_sunbpp_write_control
r_static
r_void
id|parport_sunbpp_write_control
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|d
)paren
(brace
r_const
r_int
r_char
id|wm
op_assign
(paren
id|PARPORT_CONTROL_STROBE
op_or
id|PARPORT_CONTROL_AUTOFD
op_or
id|PARPORT_CONTROL_INIT
op_or
id|PARPORT_CONTROL_SELECT
)paren
suffix:semicolon
id|parport_sunbpp_frob_control
(paren
id|p
comma
id|wm
comma
id|d
op_amp
id|wm
)paren
suffix:semicolon
)brace
DECL|function|parport_sunbpp_read_status
r_static
r_int
r_char
id|parport_sunbpp_read_status
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_return
id|status_sunbpp_to_pc
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|parport_sunbpp_data_forward
r_static
r_void
id|parport_sunbpp_data_forward
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_struct
id|bpp_regs
op_star
id|regs
op_assign
(paren
r_struct
id|bpp_regs
op_star
)paren
id|p-&gt;base
suffix:semicolon
r_int
r_char
id|value_tcr
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|regs-&gt;p_tcr
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;forward&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|value_tcr
op_and_assign
op_complement
id|P_TCR_DIR
suffix:semicolon
id|sbus_writeb
c_func
(paren
id|value_tcr
comma
op_amp
id|regs-&gt;p_tcr
)paren
suffix:semicolon
)brace
DECL|function|parport_sunbpp_data_reverse
r_static
r_void
id|parport_sunbpp_data_reverse
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_struct
id|bpp_regs
op_star
id|regs
op_assign
(paren
r_struct
id|bpp_regs
op_star
)paren
id|p-&gt;base
suffix:semicolon
id|u8
id|val
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|regs-&gt;p_tcr
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;reverse&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|val
op_or_assign
id|P_TCR_DIR
suffix:semicolon
id|sbus_writeb
c_func
(paren
id|val
comma
op_amp
id|regs-&gt;p_tcr
)paren
suffix:semicolon
)brace
DECL|function|parport_sunbpp_init_state
r_static
r_void
id|parport_sunbpp_init_state
c_func
(paren
r_struct
id|pardevice
op_star
id|dev
comma
r_struct
id|parport_state
op_star
id|s
)paren
(brace
id|s-&gt;u.pc.ctr
op_assign
l_int|0xc
suffix:semicolon
id|s-&gt;u.pc.ecr
op_assign
l_int|0x0
suffix:semicolon
)brace
DECL|function|parport_sunbpp_save_state
r_static
r_void
id|parport_sunbpp_save_state
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_struct
id|parport_state
op_star
id|s
)paren
(brace
id|s-&gt;u.pc.ctr
op_assign
id|parport_sunbpp_read_control
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
DECL|function|parport_sunbpp_restore_state
r_static
r_void
id|parport_sunbpp_restore_state
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_struct
id|parport_state
op_star
id|s
)paren
(brace
id|parport_sunbpp_write_control
c_func
(paren
id|p
comma
id|s-&gt;u.pc.ctr
)paren
suffix:semicolon
)brace
DECL|variable|parport_sunbpp_ops
r_static
r_struct
id|parport_operations
id|parport_sunbpp_ops
op_assign
(brace
dot
id|write_data
op_assign
id|parport_sunbpp_write_data
comma
dot
id|read_data
op_assign
id|parport_sunbpp_read_data
comma
dot
id|write_control
op_assign
id|parport_sunbpp_write_control
comma
dot
id|read_control
op_assign
id|parport_sunbpp_read_control
comma
dot
id|frob_control
op_assign
id|parport_sunbpp_frob_control
comma
dot
id|read_status
op_assign
id|parport_sunbpp_read_status
comma
dot
id|enable_irq
op_assign
id|parport_sunbpp_enable_irq
comma
dot
id|disable_irq
op_assign
id|parport_sunbpp_disable_irq
comma
dot
id|data_forward
op_assign
id|parport_sunbpp_data_forward
comma
dot
id|data_reverse
op_assign
id|parport_sunbpp_data_reverse
comma
dot
id|init_state
op_assign
id|parport_sunbpp_init_state
comma
dot
id|save_state
op_assign
id|parport_sunbpp_save_state
comma
dot
id|restore_state
op_assign
id|parport_sunbpp_restore_state
comma
dot
id|epp_write_data
op_assign
id|parport_ieee1284_epp_write_data
comma
dot
id|epp_read_data
op_assign
id|parport_ieee1284_epp_read_data
comma
dot
id|epp_write_addr
op_assign
id|parport_ieee1284_epp_write_addr
comma
dot
id|epp_read_addr
op_assign
id|parport_ieee1284_epp_read_addr
comma
dot
id|ecp_write_data
op_assign
id|parport_ieee1284_ecp_write_data
comma
dot
id|ecp_read_data
op_assign
id|parport_ieee1284_ecp_read_data
comma
dot
id|ecp_write_addr
op_assign
id|parport_ieee1284_ecp_write_addr
comma
dot
id|compat_write_data
op_assign
id|parport_ieee1284_write_compat
comma
dot
id|nibble_read_data
op_assign
id|parport_ieee1284_read_nibble
comma
dot
id|byte_read_data
op_assign
id|parport_ieee1284_read_byte
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|port
r_struct
id|parport
op_star
id|port
suffix:semicolon
DECL|typedef|Node
)brace
id|Node
suffix:semicolon
multiline_comment|/* no locks, everything&squot;s serialized */
r_static
id|LIST_HEAD
c_func
(paren
id|port_list
)paren
suffix:semicolon
DECL|function|init_one_port
r_static
r_int
id|__init
id|init_one_port
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
)paren
(brace
r_struct
id|parport
op_star
id|p
suffix:semicolon
multiline_comment|/* at least in theory there may be a &quot;we don&squot;t dma&quot; case */
r_struct
id|parport_operations
op_star
id|ops
suffix:semicolon
r_int
r_int
id|base
suffix:semicolon
r_int
id|irq
comma
id|dma
comma
id|err
op_assign
l_int|0
comma
id|size
suffix:semicolon
r_struct
id|bpp_regs
op_star
id|regs
suffix:semicolon
r_int
r_char
id|value_tcr
suffix:semicolon
id|Node
op_star
id|node
suffix:semicolon
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;init_one_port(%p): ranges, alloc_io, &quot;
comma
id|sdev
)paren
)paren
suffix:semicolon
id|node
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|Node
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
r_goto
id|out0
suffix:semicolon
id|irq
op_assign
id|sdev-&gt;irqs
(braket
l_int|0
)braket
suffix:semicolon
id|base
op_assign
id|sbus_ioremap
c_func
(paren
op_amp
id|sdev-&gt;resource
(braket
l_int|0
)braket
comma
l_int|0
comma
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|reg_size
comma
l_string|&quot;sunbpp&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base
)paren
r_goto
id|out1
suffix:semicolon
id|size
op_assign
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|reg_size
suffix:semicolon
id|dma
op_assign
id|PARPORT_DMA_NONE
suffix:semicolon
id|dprintk
c_func
(paren
(paren
l_string|&quot;alloc(ppops), &quot;
)paren
)paren
suffix:semicolon
id|ops
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|parport_operations
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ops
)paren
r_goto
id|out2
suffix:semicolon
id|memcpy
(paren
id|ops
comma
op_amp
id|parport_sunbpp_ops
comma
r_sizeof
(paren
r_struct
id|parport_operations
)paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
l_string|&quot;register_port&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|parport_register_port
c_func
(paren
id|base
comma
id|irq
comma
id|dma
comma
id|ops
)paren
)paren
)paren
r_goto
id|out3
suffix:semicolon
id|p-&gt;size
op_assign
id|size
suffix:semicolon
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;init_one_port: request_irq(%08x:%p:%x:%s:%p) &quot;
comma
id|p-&gt;irq
comma
id|parport_sunbpp_interrupt
comma
id|SA_SHIRQ
comma
id|p-&gt;name
comma
id|p
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|request_irq
c_func
(paren
id|p-&gt;irq
comma
id|parport_sunbpp_interrupt
comma
id|SA_SHIRQ
comma
id|p-&gt;name
comma
id|p
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
(paren
l_string|&quot;ERROR %d&bslash;n&quot;
comma
id|err
)paren
)paren
suffix:semicolon
r_goto
id|out4
suffix:semicolon
)brace
id|dprintk
c_func
(paren
(paren
l_string|&quot;OK&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|parport_sunbpp_enable_irq
c_func
(paren
id|p
)paren
suffix:semicolon
id|regs
op_assign
(paren
r_struct
id|bpp_regs
op_star
)paren
id|p-&gt;base
suffix:semicolon
id|dprintk
c_func
(paren
(paren
id|KERN_DEBUG
l_string|&quot;forward&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|value_tcr
op_assign
id|sbus_readb
c_func
(paren
op_amp
id|regs-&gt;p_tcr
)paren
suffix:semicolon
id|value_tcr
op_and_assign
op_complement
id|P_TCR_DIR
suffix:semicolon
id|sbus_writeb
c_func
(paren
id|value_tcr
comma
op_amp
id|regs-&gt;p_tcr
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: sunbpp at 0x%lx&bslash;n&quot;
comma
id|p-&gt;name
comma
id|p-&gt;base
)paren
suffix:semicolon
id|node-&gt;port
op_assign
id|p
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|node-&gt;list
comma
op_amp
id|port_list
)paren
suffix:semicolon
id|parport_announce_port
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|out4
suffix:colon
id|parport_put_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|out3
suffix:colon
id|kfree
c_func
(paren
id|ops
)paren
suffix:semicolon
id|out2
suffix:colon
id|sbus_iounmap
c_func
(paren
id|base
comma
id|size
)paren
suffix:semicolon
id|out1
suffix:colon
id|kfree
c_func
(paren
id|node
)paren
suffix:semicolon
id|out0
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|parport_sunbpp_init
r_static
r_int
id|__init
id|parport_sunbpp_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|sbus_bus
op_star
id|sbus
suffix:semicolon
r_struct
id|sbus_dev
op_star
id|sdev
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
id|for_each_sbus
c_func
(paren
id|sbus
)paren
(brace
id|for_each_sbusdev
c_func
(paren
id|sdev
comma
id|sbus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|sdev-&gt;prom_name
comma
l_string|&quot;SUNW,bpp&quot;
)paren
)paren
id|count
op_add_assign
id|init_one_port
c_func
(paren
id|sdev
)paren
suffix:semicolon
)brace
)brace
r_return
id|count
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|parport_sunbpp_exit
r_static
r_void
id|__exit
id|parport_sunbpp_exit
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|port_list
)paren
)paren
(brace
id|Node
op_star
id|node
op_assign
id|list_entry
c_func
(paren
id|port_list.next
comma
id|Node
comma
id|list
)paren
suffix:semicolon
r_struct
id|parport
op_star
id|p
op_assign
id|node-&gt;port
suffix:semicolon
r_struct
id|parport_operations
op_star
id|ops
op_assign
id|p-&gt;ops
suffix:semicolon
id|parport_remove_port
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;irq
op_ne
id|PARPORT_IRQ_NONE
)paren
(brace
id|parport_sunbpp_disable_irq
c_func
(paren
id|p
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|p-&gt;irq
comma
id|p
)paren
suffix:semicolon
)brace
id|sbus_iounmap
c_func
(paren
id|p-&gt;base
comma
id|p-&gt;size
)paren
suffix:semicolon
id|parport_put_port
c_func
(paren
id|p
)paren
suffix:semicolon
id|kfree
(paren
id|ops
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|node-&gt;list
)paren
suffix:semicolon
id|kfree
(paren
id|node
)paren
suffix:semicolon
)brace
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Derrick J Brashear&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Parport Driver for Sparc bidirectional Port&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;Sparc Bidirectional Parallel Port&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|module_init
c_func
(paren
id|parport_sunbpp_init
)paren
id|module_exit
c_func
(paren
id|parport_sunbpp_exit
)paren
eof
