multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; *&t;ITE 8172G interrupt/setup routines.&n; *&n; * Copyright 2000,2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; * Part of this file was derived from Carsten Langgaard&squot;s&n; * arch/mips/mips-boards/atlas/atlas_int.c.&n; *&n; * Carsten Langgaard, carstenl@mips.com&n; * Copyright (C) 1999,2000 MIPS Technologies, Inc.  All rights reserved.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
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
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/it8172/it8172.h&gt;
macro_line|#include &lt;asm/it8172/it8172_int.h&gt;
macro_line|#include &lt;asm/it8172/it8172_dbg.h&gt;
DECL|macro|DEBUG_IRQ
macro_line|#undef DEBUG_IRQ
macro_line|#ifdef DEBUG_IRQ
multiline_comment|/* note: prints function name for you */
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(fmt, args...) printk(&quot;%s: &quot; fmt, __FUNCTION__ , ## args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(fmt, args...)
macro_line|#endif
multiline_comment|/* revisit */
DECL|macro|EXT_IRQ0_TO_IP
mdefine_line|#define EXT_IRQ0_TO_IP 2 /* IP 2 */
DECL|macro|EXT_IRQ5_TO_IP
mdefine_line|#define EXT_IRQ5_TO_IP 7 /* IP 7 */
DECL|macro|ALLINTS_NOTIMER
mdefine_line|#define ALLINTS_NOTIMER (IE_IRQ0 | IE_IRQ1 | IE_IRQ2 | IE_IRQ3 | IE_IRQ4)
r_void
id|disable_it8172_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
suffix:semicolon
r_void
id|enable_it8172_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
suffix:semicolon
r_extern
r_void
id|set_debug_traps
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mips_timer_interrupt
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
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|it8172_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|it8172_hw0_icregs
r_struct
id|it8172_intc_regs
r_volatile
op_star
id|it8172_hw0_icregs
op_assign
(paren
r_struct
id|it8172_intc_regs
r_volatile
op_star
)paren
(paren
id|KSEG1ADDR
c_func
(paren
id|IT8172_PCI_IO_BASE
op_plus
id|IT_INTC_BASE
)paren
)paren
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
id|irq_nr
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
id|irq_nr
)paren
suffix:semicolon
)brace
DECL|function|local_disable_irq
r_void
id|local_disable_irq
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
id|disable_it8172_irq
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
DECL|function|local_enable_irq
r_void
id|local_enable_irq
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
id|enable_it8172_irq
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
DECL|function|disable_it8172_irq
r_void
id|disable_it8172_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;disable_it8172_irq %d&bslash;n&quot;
comma
id|irq_nr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|irq_nr
op_ge
id|IT8172_LPC_IRQ_BASE
)paren
op_logical_and
(paren
id|irq_nr
op_le
id|IT8172_SERIRQ_15
)paren
)paren
(brace
multiline_comment|/* LPC interrupt */
id|DPRINTK
c_func
(paren
l_string|&quot;DB lpc_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;lpc_mask
)paren
suffix:semicolon
id|it8172_hw0_icregs-&gt;lpc_mask
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
id|IT8172_LPC_IRQ_BASE
)paren
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;DA lpc_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;lpc_mask
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|irq_nr
op_ge
id|IT8172_LB_IRQ_BASE
)paren
op_logical_and
(paren
id|irq_nr
op_le
id|IT8172_IOCHK_IRQ
)paren
)paren
(brace
multiline_comment|/* Local Bus interrupt */
id|DPRINTK
c_func
(paren
l_string|&quot;DB lb_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;lb_mask
)paren
suffix:semicolon
id|it8172_hw0_icregs-&gt;lb_mask
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
id|IT8172_LB_IRQ_BASE
)paren
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;DA lb_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;lb_mask
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|irq_nr
op_ge
id|IT8172_PCI_DEV_IRQ_BASE
)paren
op_logical_and
(paren
id|irq_nr
op_le
id|IT8172_DMA_IRQ
)paren
)paren
(brace
multiline_comment|/* PCI and other interrupts */
id|DPRINTK
c_func
(paren
l_string|&quot;DB pci_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;pci_mask
)paren
suffix:semicolon
id|it8172_hw0_icregs-&gt;pci_mask
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
id|IT8172_PCI_DEV_IRQ_BASE
)paren
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;DA pci_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;pci_mask
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|irq_nr
op_ge
id|IT8172_NMI_IRQ_BASE
)paren
op_logical_and
(paren
id|irq_nr
op_le
id|IT8172_POWER_NMI_IRQ
)paren
)paren
(brace
multiline_comment|/* NMI interrupts */
id|DPRINTK
c_func
(paren
l_string|&quot;DB nmi_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;nmi_mask
)paren
suffix:semicolon
id|it8172_hw0_icregs-&gt;nmi_mask
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
id|IT8172_NMI_IRQ_BASE
)paren
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;DA nmi_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;nmi_mask
)paren
suffix:semicolon
)brace
r_else
(brace
id|panic
c_func
(paren
l_string|&quot;disable_it8172_irq: bad irq %d&quot;
comma
id|irq_nr
)paren
suffix:semicolon
)brace
)brace
DECL|function|enable_it8172_irq
r_void
id|enable_it8172_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;enable_it8172_irq %d&bslash;n&quot;
comma
id|irq_nr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|irq_nr
op_ge
id|IT8172_LPC_IRQ_BASE
)paren
op_logical_and
(paren
id|irq_nr
op_le
id|IT8172_SERIRQ_15
)paren
)paren
(brace
multiline_comment|/* LPC interrupt */
id|DPRINTK
c_func
(paren
l_string|&quot;EB before lpc_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;lpc_mask
)paren
suffix:semicolon
id|it8172_hw0_icregs-&gt;lpc_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
id|IT8172_LPC_IRQ_BASE
)paren
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;EA after lpc_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;lpc_mask
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|irq_nr
op_ge
id|IT8172_LB_IRQ_BASE
)paren
op_logical_and
(paren
id|irq_nr
op_le
id|IT8172_IOCHK_IRQ
)paren
)paren
(brace
multiline_comment|/* Local Bus interrupt */
id|DPRINTK
c_func
(paren
l_string|&quot;EB lb_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;lb_mask
)paren
suffix:semicolon
id|it8172_hw0_icregs-&gt;lb_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
id|IT8172_LB_IRQ_BASE
)paren
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;EA lb_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;lb_mask
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|irq_nr
op_ge
id|IT8172_PCI_DEV_IRQ_BASE
)paren
op_logical_and
(paren
id|irq_nr
op_le
id|IT8172_DMA_IRQ
)paren
)paren
(brace
multiline_comment|/* PCI and other interrupts */
id|DPRINTK
c_func
(paren
l_string|&quot;EB pci_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;pci_mask
)paren
suffix:semicolon
id|it8172_hw0_icregs-&gt;pci_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
id|IT8172_PCI_DEV_IRQ_BASE
)paren
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;EA pci_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;pci_mask
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|irq_nr
op_ge
id|IT8172_NMI_IRQ_BASE
)paren
op_logical_and
(paren
id|irq_nr
op_le
id|IT8172_POWER_NMI_IRQ
)paren
)paren
(brace
multiline_comment|/* NMI interrupts */
id|DPRINTK
c_func
(paren
l_string|&quot;EB nmi_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;nmi_mask
)paren
suffix:semicolon
id|it8172_hw0_icregs-&gt;nmi_mask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
id|IT8172_NMI_IRQ_BASE
)paren
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;EA nmi_mask  %x&bslash;n&quot;
comma
id|it8172_hw0_icregs-&gt;nmi_mask
)paren
suffix:semicolon
)brace
r_else
(brace
id|panic
c_func
(paren
l_string|&quot;enable_it8172_irq: bad irq %d&quot;
comma
id|irq_nr
)paren
suffix:semicolon
)brace
)brace
DECL|function|startup_ite_irq
r_static
r_int
r_int
id|startup_ite_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_it8172_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|shutdown_ite_irq
mdefine_line|#define shutdown_ite_irq&t;disable_it8172_irq
DECL|macro|mask_and_ack_ite_irq
mdefine_line|#define mask_and_ack_ite_irq    disable_it8172_irq
DECL|function|end_ite_irq
r_static
r_void
id|end_ite_irq
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
id|enable_it8172_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|it8172_irq_type
r_static
r_struct
id|hw_interrupt_type
id|it8172_irq_type
op_assign
(brace
l_string|&quot;ITE8172&quot;
comma
id|startup_ite_irq
comma
id|shutdown_ite_irq
comma
id|enable_it8172_irq
comma
id|disable_it8172_irq
comma
id|mask_and_ack_ite_irq
comma
id|end_ite_irq
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|enable_none
r_static
r_void
id|enable_none
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|function|startup_none
r_static
r_int
r_int
id|startup_none
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|disable_none
r_static
r_void
id|disable_none
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|function|ack_none
r_static
r_void
id|ack_none
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
multiline_comment|/* startup is the same as &quot;enable&quot;, shutdown is same as &quot;disable&quot; */
DECL|macro|shutdown_none
mdefine_line|#define shutdown_none&t;disable_none
DECL|macro|end_none
mdefine_line|#define end_none&t;enable_none
DECL|variable|cp0_irq_type
r_static
r_struct
id|hw_interrupt_type
id|cp0_irq_type
op_assign
(brace
l_string|&quot;CP0 Count&quot;
comma
id|startup_none
comma
id|shutdown_none
comma
id|enable_none
comma
id|disable_none
comma
id|ack_none
comma
id|end_none
)brace
suffix:semicolon
DECL|function|enable_cpu_timer
r_void
id|enable_cpu_timer
c_func
(paren
r_void
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
l_int|1
op_lshift
id|EXT_IRQ5_TO_IP
)paren
suffix:semicolon
multiline_comment|/* timer interrupt */
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|arch_init_irq
r_void
id|__init
id|arch_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|memset
c_func
(paren
id|irq_desc
comma
l_int|0
comma
r_sizeof
(paren
id|irq_desc
)paren
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|0
comma
id|it8172_IRQ
)paren
suffix:semicolon
multiline_comment|/* mask all interrupts */
id|it8172_hw0_icregs-&gt;lb_mask
op_assign
l_int|0xffff
suffix:semicolon
id|it8172_hw0_icregs-&gt;lpc_mask
op_assign
l_int|0xffff
suffix:semicolon
id|it8172_hw0_icregs-&gt;pci_mask
op_assign
l_int|0xffff
suffix:semicolon
id|it8172_hw0_icregs-&gt;nmi_mask
op_assign
l_int|0xffff
suffix:semicolon
multiline_comment|/* make all interrupts level triggered */
id|it8172_hw0_icregs-&gt;lb_trigger
op_assign
l_int|0
suffix:semicolon
id|it8172_hw0_icregs-&gt;lpc_trigger
op_assign
l_int|0
suffix:semicolon
id|it8172_hw0_icregs-&gt;pci_trigger
op_assign
l_int|0
suffix:semicolon
id|it8172_hw0_icregs-&gt;nmi_trigger
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* active level setting */
multiline_comment|/* uart, keyboard, and mouse are active high */
id|it8172_hw0_icregs-&gt;lpc_level
op_assign
(paren
l_int|0x10
op_or
l_int|0x2
op_or
l_int|0x1000
)paren
suffix:semicolon
id|it8172_hw0_icregs-&gt;lb_level
op_or_assign
l_int|0x20
suffix:semicolon
multiline_comment|/* keyboard and mouse are edge triggered */
id|it8172_hw0_icregs-&gt;lpc_trigger
op_or_assign
(paren
l_int|0x2
op_or
l_int|0x1000
)paren
suffix:semicolon
macro_line|#if 0
singleline_comment|// Enable this piece of code to make internal USB interrupt
singleline_comment|// edge triggered.
id|it8172_hw0_icregs-&gt;pci_trigger
op_or_assign
(paren
l_int|1
op_lshift
(paren
id|IT8172_USB_IRQ
op_minus
id|IT8172_PCI_DEV_IRQ_BASE
)paren
)paren
suffix:semicolon
id|it8172_hw0_icregs-&gt;pci_level
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|IT8172_USB_IRQ
op_minus
id|IT8172_PCI_DEV_IRQ_BASE
)paren
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|IT8172_LAST_IRQ
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
id|handler
op_assign
op_amp
id|it8172_irq_type
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|irq_desc
(braket
id|i
)braket
dot
id|lock
)paren
suffix:semicolon
)brace
id|irq_desc
(braket
id|MIPS_CPU_TIMER_IRQ
)braket
dot
id|handler
op_assign
op_amp
id|cp0_irq_type
suffix:semicolon
id|set_c0_status
c_func
(paren
id|ALLINTS_NOTIMER
)paren
suffix:semicolon
)brace
DECL|function|mips_spurious_interrupt
r_void
id|mips_spurious_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#if 1
r_return
suffix:semicolon
macro_line|#else
r_int
r_int
id|status
comma
id|cause
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;got spurious interrupt&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
id|cause
op_assign
id|read_c0_cause
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;status %x cause %x&bslash;n&quot;
comma
id|status
comma
id|cause
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;epc %x badvaddr %x &bslash;n&quot;
comma
id|regs-&gt;cp0_epc
comma
id|regs-&gt;cp0_badvaddr
)paren
suffix:semicolon
singleline_comment|//&t;while(1);
macro_line|#endif
)brace
DECL|function|it8172_hw0_irqdispatch
r_void
id|it8172_hw0_irqdispatch
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
r_int
r_int
id|intstatus
op_assign
l_int|0
comma
id|status
op_assign
l_int|0
suffix:semicolon
id|intstatus
op_assign
id|it8172_hw0_icregs-&gt;intstatus
suffix:semicolon
r_if
c_cond
(paren
id|intstatus
op_amp
l_int|0x8
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Got NMI interrupt&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|intstatus
op_amp
l_int|0x4
)paren
(brace
multiline_comment|/* PCI interrupt */
id|irq
op_assign
l_int|0
suffix:semicolon
id|status
op_or_assign
id|it8172_hw0_icregs-&gt;pci_req
suffix:semicolon
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
id|irq
op_add_assign
id|IT8172_PCI_DEV_IRQ_BASE
suffix:semicolon
singleline_comment|//printk(&quot;pci int %d&bslash;n&quot;, irq);
)brace
r_else
r_if
c_cond
(paren
id|intstatus
op_amp
l_int|0x1
)paren
(brace
multiline_comment|/* Local Bus interrupt */
id|irq
op_assign
l_int|0
suffix:semicolon
id|status
op_or_assign
id|it8172_hw0_icregs-&gt;lb_req
suffix:semicolon
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
id|irq
op_add_assign
id|IT8172_LB_IRQ_BASE
suffix:semicolon
singleline_comment|//printk(&quot;lb int %d&bslash;n&quot;, irq);
)brace
r_else
r_if
c_cond
(paren
id|intstatus
op_amp
l_int|0x2
)paren
(brace
multiline_comment|/* LPC interrupt */
multiline_comment|/* Since some lpc interrupts are edge triggered,&n;&t;&t; * we could lose an interrupt this way because&n;&t;&t; * we acknowledge all ints at onces. Revisit.&n;&t;&t; */
id|status
op_or_assign
id|it8172_hw0_icregs-&gt;lpc_req
suffix:semicolon
id|it8172_hw0_icregs-&gt;lpc_req
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* acknowledge ints */
id|irq
op_assign
l_int|0
suffix:semicolon
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
id|irq
op_add_assign
id|IT8172_LPC_IRQ_BASE
suffix:semicolon
singleline_comment|//printk(&quot;LPC int %d&bslash;n&quot;, irq);
)brace
r_else
r_return
suffix:semicolon
id|do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|show_pending_irqs
r_void
id|show_pending_irqs
c_func
(paren
r_void
)paren
(brace
id|fputs
c_func
(paren
l_string|&quot;intstatus:  &quot;
)paren
suffix:semicolon
id|put32
c_func
(paren
id|it8172_hw0_icregs-&gt;intstatus
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot;pci_req:  &quot;
)paren
suffix:semicolon
id|put32
c_func
(paren
id|it8172_hw0_icregs-&gt;pci_req
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot;lb_req:  &quot;
)paren
suffix:semicolon
id|put32
c_func
(paren
id|it8172_hw0_icregs-&gt;lb_req
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
id|fputs
c_func
(paren
l_string|&quot;lpc_req:  &quot;
)paren
suffix:semicolon
id|put32
c_func
(paren
id|it8172_hw0_icregs-&gt;lpc_req
)paren
suffix:semicolon
id|puts
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
eof
