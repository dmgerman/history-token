multiline_comment|/*&n; * Copyright (C) 2002 Momentum Computer, Inc.&n; * Author: Matthew Dharm, mdharm@momenco.com&n; *&n; * Based on work by:&n; *   Copyright (C) 2000 RidgeRun, Inc.&n; *   Author: RidgeRun, Inc.&n; *   glonnon@ridgerun.com, skranz@ridgerun.com, stevej@ridgerun.com&n; *&n; *   Copyright 2001 MontaVista Software Inc.&n; *   Author: Jun Sun, jsun@mvista.com or jsun@junsun.net&n; *&n; *   Copyright (C) 2000, 2001 Ralf Baechle (ralf@gnu.org)&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/irq_cpu.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
r_extern
id|asmlinkage
r_void
id|jaguar_handle_int
c_func
(paren
r_void
)paren
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
l_string|&quot;MV64340-Cascade&quot;
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
id|jaguar_handle_int
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
multiline_comment|/* set up the cascading interrupts */
id|setup_irq
c_func
(paren
l_int|8
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
id|set_c0_status
c_func
(paren
id|ST0_IM
)paren
suffix:semicolon
)brace
eof
