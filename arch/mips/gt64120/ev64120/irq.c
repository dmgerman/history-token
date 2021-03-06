multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; * Code to handle irqs on GT64120A boards&n; *  Derived from mips/orion and Cort &lt;cort@fsmlabs.com&gt;&n; *&n; * Copyright (C) 2000 RidgeRun, Inc.&n; * Author: RidgeRun, Inc.&n; *   glonnon@ridgerun.com, skranz@ridgerun.com, stevej@ridgerun.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
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
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/gt64120.h&gt;
DECL|function|pci_intA
id|asmlinkage
r_inline
r_void
id|pci_intA
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|do_IRQ
c_func
(paren
id|GT_INTA
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|pci_intD
id|asmlinkage
r_inline
r_void
id|pci_intD
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|do_IRQ
c_func
(paren
id|GT_INTD
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|disable_ev64120_irq
r_static
r_void
id|disable_ev64120_irq
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
r_if
c_cond
(paren
id|irq_nr
op_ge
l_int|8
)paren
(brace
singleline_comment|// All PCI interrupts are on line 5 or 2
id|clear_c0_status
c_func
(paren
l_int|9
op_lshift
l_int|10
)paren
suffix:semicolon
)brace
r_else
(brace
id|clear_c0_status
c_func
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_plus
l_int|8
)paren
)paren
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|enable_ev64120_irq
r_static
r_void
id|enable_ev64120_irq
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
r_if
c_cond
(paren
id|irq_nr
op_ge
l_int|8
)paren
singleline_comment|// All PCI interrupts are on line 5 or 2
id|set_c0_status
c_func
(paren
l_int|9
op_lshift
l_int|10
)paren
suffix:semicolon
r_else
id|set_c0_status
c_func
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_plus
l_int|8
)paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|startup_ev64120_irq
r_static
r_int
r_int
id|startup_ev64120_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_ev64120_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Never anything pending  */
)brace
DECL|macro|shutdown_ev64120_irq
mdefine_line|#define shutdown_ev64120_irq     disable_ev64120_irq
DECL|macro|mask_and_ack_ev64120_irq
mdefine_line|#define mask_and_ack_ev64120_irq disable_ev64120_irq
DECL|function|end_ev64120_irq
r_static
r_void
id|end_ev64120_irq
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
id|enable_ev64120_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|ev64120_irq_type
r_static
r_struct
id|hw_interrupt_type
id|ev64120_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;EV64120&quot;
comma
dot
id|startup
op_assign
id|startup_ev64120_irq
comma
dot
id|shutdown
op_assign
id|shutdown_ev64120_irq
comma
dot
id|enable
op_assign
id|enable_ev64120_irq
comma
dot
id|disable
op_assign
id|disable_ev64120_irq
comma
dot
id|ack
op_assign
id|mask_and_ack_ev64120_irq
comma
dot
id|end
op_assign
id|end_ev64120_irq
comma
dot
id|set_affinity
op_assign
l_int|NULL
)brace
suffix:semicolon
DECL|function|gt64120_irq_setup
r_void
id|gt64120_irq_setup
c_func
(paren
r_void
)paren
(brace
r_extern
id|asmlinkage
r_void
id|galileo_handle_int
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Clear all of the interrupts while we change the able around a bit.&n;&t; */
id|clear_c0_status
c_func
(paren
id|ST0_IM
)paren
suffix:semicolon
multiline_comment|/* Sets the exception_handler array. */
id|set_except_vector
c_func
(paren
l_int|0
comma
id|galileo_handle_int
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Enable timer.  Other interrupts will be enabled as they are&n;&t; * registered.&n;&t; */
id|set_c0_status
c_func
(paren
id|IE_IRQ2
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
multiline_comment|/*  Let&squot;s initialize our IRQ descriptors  */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_IRQS
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
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|no_irq_type
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|action
op_assign
l_int|NULL
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|depth
op_assign
l_int|0
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
id|gt64120_irq_setup
c_func
(paren
)paren
suffix:semicolon
)brace
eof
