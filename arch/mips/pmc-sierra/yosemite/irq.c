multiline_comment|/*&n; * Copyright (C) 2003 PMC-Sierra Inc.&n; * Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Second level Interrupt handlers for the PMC-Sierra Titan/Yosemite board&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/irq_cpu.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/titan_dep.h&gt;
multiline_comment|/* Hypertransport specific */
DECL|macro|IRQ_ACK_BITS
mdefine_line|#define IRQ_ACK_BITS            0x00000000&t;/* Ack bits */
DECL|macro|HYPERTRANSPORT_INTA
mdefine_line|#define HYPERTRANSPORT_INTA     0x78&t;&t;/* INTA# */
DECL|macro|HYPERTRANSPORT_INTB
mdefine_line|#define HYPERTRANSPORT_INTB     0x79&t;&t;/* INTB# */
DECL|macro|HYPERTRANSPORT_INTC
mdefine_line|#define HYPERTRANSPORT_INTC     0x7a&t;&t;/* INTC# */
DECL|macro|HYPERTRANSPORT_INTD
mdefine_line|#define HYPERTRANSPORT_INTD     0x7b&t;&t;/* INTD# */
r_extern
id|asmlinkage
r_void
id|titan_handle_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|jaguar_mailbox_irq
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/* &n; * Handle hypertransport &amp; SMP interrupts. The interrupt lines are scarce.&n; * For interprocessor interrupts, the best thing to do is to use the INTMSG&n; * register. We use the same external interrupt line, i.e. INTB3 and monitor&n; * another status bit&n; */
DECL|function|ll_ht_smp_irq_handler
id|asmlinkage
r_void
id|ll_ht_smp_irq_handler
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
id|u32
id|status
op_assign
id|OCD_READ
c_func
(paren
id|RM9000x2_OCD_INTP0STATUS4
)paren
suffix:semicolon
multiline_comment|/* Ack all the bits that correspond to the interrupt sources */
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_INTP0STATUS4
comma
id|IRQ_ACK_BITS
)paren
suffix:semicolon
id|status
op_assign
id|OCD_READ
c_func
(paren
id|RM9000x2_OCD_INTP1STATUS4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_INTP1STATUS4
comma
id|IRQ_ACK_BITS
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HT_LEVEL_TRIGGER
multiline_comment|/*&n;&t; * Level Trigger Mode only. Send the HT EOI message back to the source.&n;&t; */
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
l_int|0x1000000
suffix:colon
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_HTEOI
comma
id|HYPERTRANSPORT_INTA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x2000000
suffix:colon
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_HTEOI
comma
id|HYPERTRANSPORT_INTB
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x4000000
suffix:colon
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_HTEOI
comma
id|HYPERTRANSPORT_INTC
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x8000000
suffix:colon
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_HTEOI
comma
id|HYPERTRANSPORT_INTD
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0000001
suffix:colon
multiline_comment|/* PLX */
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_HTEOI
comma
l_int|0x20
)paren
suffix:semicolon
id|OCD_WRITE
c_func
(paren
id|IRQ_CLEAR_REG
comma
id|IRQ_ACK_BITS
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf000000
suffix:colon
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_HTEOI
comma
id|HYPERTRANSPORT_INTA
)paren
suffix:semicolon
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_HTEOI
comma
id|HYPERTRANSPORT_INTB
)paren
suffix:semicolon
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_HTEOI
comma
id|HYPERTRANSPORT_INTC
)paren
suffix:semicolon
id|OCD_WRITE
c_func
(paren
id|RM9000x2_OCD_HTEOI
comma
id|HYPERTRANSPORT_INTD
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_HT_LEVEL_TRIGGER */
id|do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_KGDB
r_extern
r_void
id|init_second_port
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Initialize the next level interrupt handler&n; */
DECL|function|arch_init_irq
r_void
id|__init
id|arch_init_irq
c_func
(paren
r_void
)paren
(brace
id|clear_c0_status
c_func
(paren
id|ST0_IM
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|0
comma
id|titan_handle_int
)paren
suffix:semicolon
id|mips_cpu_irq_init
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|rm7k_cpu_irq_init
c_func
(paren
l_int|8
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_KGDB
multiline_comment|/* At this point, initialize the second serial port */
id|init_second_port
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_GDB_CONSOLE
id|register_gdb_console
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_KGDB
multiline_comment|/*&n; * The 16550 DUART has two ports, but is allocated one IRQ&n; * for the serial console. Hence, a generic framework for&n; * serial IRQ routing in place. Currently, just calls the&n; * do_IRQ fuction. But, going in the future, need to check&n; * DUART registers for channel A and B, then decide the&n; * appropriate action&n; */
DECL|function|yosemite_kgdb_irq
id|asmlinkage
r_void
id|yosemite_kgdb_irq
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
id|do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
