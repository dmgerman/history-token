multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; *&t;Au1xxx irq map table&n; *&n; * Copyright 2003 Embedded Edge, LLC&n; *&t;&t;dan@embeddededge.com&n; *&n; *  This program is free software; you can redistribute&t; it and/or modify it&n; *  under  the terms of&t; the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the&t;License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED&t;  ``AS&t;IS&squot;&squot; AND   ANY&t;EXPRESS OR IMPLIED&n; *  WARRANTIES,&t;  INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO&t;EVENT  SHALL   THE AUTHOR  BE&t; LIABLE FOR ANY&t;  DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED&t;  TO, PROCUREMENT OF  SUBSTITUTE GOODS&t;OR SERVICES; LOSS OF&n; *  USE, DATA,&t;OR PROFITS; OR&t;BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN&t; CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
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
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/mach-au1x00/au1000.h&gt;
DECL|variable|au1xxx_irq_map
id|au1xxx_irq_map_t
id|au1xxx_irq_map
(braket
)braket
op_assign
(brace
(brace
id|AU1000_GPIO_15
comma
id|INTC_INT_LOW_LEVEL
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
DECL|variable|au1xxx_nr_irqs
r_int
id|au1xxx_nr_irqs
op_assign
r_sizeof
(paren
id|au1xxx_irq_map
)paren
op_div
r_sizeof
(paren
id|au1xxx_irq_map_t
)paren
suffix:semicolon
eof
