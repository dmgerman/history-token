multiline_comment|/*&n; * Copyright (C) 2000 RidgeRun, Inc.&n; * Author: RidgeRun, Inc.&n; *   glonnon@ridgerun.com, skranz@ridgerun.com, stevej@ridgerun.com&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; * Copyright (C) 2000, 01, 05 Ralf Baechle (ralf@linux-mips.org)&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
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
macro_line|#include &lt;asm/irq_cpu.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/mv64340.h&gt;
macro_line|#include &lt;asm/system.h&gt;
r_extern
id|asmlinkage
r_void
id|ocelot_handle_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|uart_irq_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cpci_irq_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|cascade_fpga
r_static
r_struct
id|irqaction
id|cascade_fpga
op_assign
(brace
id|no_action
comma
id|SA_INTERRUPT
comma
id|CPU_MASK_NONE
comma
l_string|&quot;cascade via FPGA&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|cascade_mv64340
r_static
r_struct
id|irqaction
id|cascade_mv64340
op_assign
(brace
id|no_action
comma
id|SA_INTERRUPT
comma
id|CPU_MASK_NONE
comma
l_string|&quot;cascade via MV64340&quot;
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|arch_init_irq
r_void
id|__init
id|arch_init_irq
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Clear all of the interrupts while we change the able around a bit.&n;&t; * int-handler is not on bootstrap&n;&t; */
id|clear_c0_status
c_func
(paren
id|ST0_IM
)paren
suffix:semicolon
multiline_comment|/* Sets the first-level interrupt dispatcher. */
id|set_except_vector
c_func
(paren
l_int|0
comma
id|ocelot_handle_int
)paren
suffix:semicolon
id|mips_cpu_irq_init
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* set up the cascading interrupts */
id|setup_irq
c_func
(paren
l_int|3
comma
op_amp
id|cascade_fpga
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
l_int|5
comma
op_amp
id|cascade_fpga
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
l_int|6
comma
op_amp
id|cascade_mv64340
)paren
suffix:semicolon
id|mv64340_irq_init
c_func
(paren
l_int|16
)paren
suffix:semicolon
id|uart_irq_init
c_func
(paren
)paren
suffix:semicolon
id|cpci_irq_init
c_func
(paren
)paren
suffix:semicolon
)brace
eof
