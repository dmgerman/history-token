multiline_comment|/*&n; * Common tx4927 irq handler&n; *&n; * Author: MontaVista Software, Inc.&n; *         source@mvista.com&n; *&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/tx4927/tx4927.h&gt;
multiline_comment|/*&n; * DEBUG&n; */
DECL|macro|TX4927_IRQ_DEBUG
macro_line|#undef TX4927_IRQ_DEBUG
macro_line|#ifdef TX4927_IRQ_DEBUG
DECL|macro|TX4927_IRQ_NONE
mdefine_line|#define TX4927_IRQ_NONE        0x00000000
DECL|macro|TX4927_IRQ_INFO
mdefine_line|#define TX4927_IRQ_INFO        ( 1 &lt;&lt;  0 )
DECL|macro|TX4927_IRQ_WARN
mdefine_line|#define TX4927_IRQ_WARN        ( 1 &lt;&lt;  1 )
DECL|macro|TX4927_IRQ_EROR
mdefine_line|#define TX4927_IRQ_EROR        ( 1 &lt;&lt;  2 )
DECL|macro|TX4927_IRQ_INIT
mdefine_line|#define TX4927_IRQ_INIT        ( 1 &lt;&lt;  5 )
DECL|macro|TX4927_IRQ_NEST1
mdefine_line|#define TX4927_IRQ_NEST1       ( 1 &lt;&lt;  6 )
DECL|macro|TX4927_IRQ_NEST2
mdefine_line|#define TX4927_IRQ_NEST2       ( 1 &lt;&lt;  7 )
DECL|macro|TX4927_IRQ_NEST3
mdefine_line|#define TX4927_IRQ_NEST3       ( 1 &lt;&lt;  8 )
DECL|macro|TX4927_IRQ_NEST4
mdefine_line|#define TX4927_IRQ_NEST4       ( 1 &lt;&lt;  9 )
DECL|macro|TX4927_IRQ_CP0_INIT
mdefine_line|#define TX4927_IRQ_CP0_INIT     ( 1 &lt;&lt; 10 )
DECL|macro|TX4927_IRQ_CP0_STARTUP
mdefine_line|#define TX4927_IRQ_CP0_STARTUP  ( 1 &lt;&lt; 11 )
DECL|macro|TX4927_IRQ_CP0_SHUTDOWN
mdefine_line|#define TX4927_IRQ_CP0_SHUTDOWN ( 1 &lt;&lt; 12 )
DECL|macro|TX4927_IRQ_CP0_ENABLE
mdefine_line|#define TX4927_IRQ_CP0_ENABLE   ( 1 &lt;&lt; 13 )
DECL|macro|TX4927_IRQ_CP0_DISABLE
mdefine_line|#define TX4927_IRQ_CP0_DISABLE  ( 1 &lt;&lt; 14 )
DECL|macro|TX4927_IRQ_CP0_MASK
mdefine_line|#define TX4927_IRQ_CP0_MASK     ( 1 &lt;&lt; 15 )
DECL|macro|TX4927_IRQ_CP0_ENDIRQ
mdefine_line|#define TX4927_IRQ_CP0_ENDIRQ   ( 1 &lt;&lt; 16 )
DECL|macro|TX4927_IRQ_PIC_INIT
mdefine_line|#define TX4927_IRQ_PIC_INIT     ( 1 &lt;&lt; 20 )
DECL|macro|TX4927_IRQ_PIC_STARTUP
mdefine_line|#define TX4927_IRQ_PIC_STARTUP  ( 1 &lt;&lt; 21 )
DECL|macro|TX4927_IRQ_PIC_SHUTDOWN
mdefine_line|#define TX4927_IRQ_PIC_SHUTDOWN ( 1 &lt;&lt; 22 )
DECL|macro|TX4927_IRQ_PIC_ENABLE
mdefine_line|#define TX4927_IRQ_PIC_ENABLE   ( 1 &lt;&lt; 23 )
DECL|macro|TX4927_IRQ_PIC_DISABLE
mdefine_line|#define TX4927_IRQ_PIC_DISABLE  ( 1 &lt;&lt; 24 )
DECL|macro|TX4927_IRQ_PIC_MASK
mdefine_line|#define TX4927_IRQ_PIC_MASK     ( 1 &lt;&lt; 25 )
DECL|macro|TX4927_IRQ_PIC_ENDIRQ
mdefine_line|#define TX4927_IRQ_PIC_ENDIRQ   ( 1 &lt;&lt; 26 )
DECL|macro|TX4927_IRQ_ALL
mdefine_line|#define TX4927_IRQ_ALL         0xffffffff
macro_line|#endif
macro_line|#ifdef TX4927_IRQ_DEBUG
DECL|variable|tx4927_irq_debug_flag
r_static
r_const
id|u32
id|tx4927_irq_debug_flag
op_assign
(paren
id|TX4927_IRQ_NONE
op_or
id|TX4927_IRQ_INFO
op_or
id|TX4927_IRQ_WARN
op_or
id|TX4927_IRQ_EROR
singleline_comment|//                                       | TX4927_IRQ_CP0_INIT
singleline_comment|//                                       | TX4927_IRQ_CP0_STARTUP
singleline_comment|//                                       | TX4927_IRQ_CP0_SHUTDOWN
singleline_comment|//                                       | TX4927_IRQ_CP0_ENABLE
singleline_comment|//                                       | TX4927_IRQ_CP0_DISABLE
singleline_comment|//                                       | TX4927_IRQ_CP0_MASK
singleline_comment|//                                       | TX4927_IRQ_CP0_ENDIRQ
singleline_comment|//                                       | TX4927_IRQ_PIC_INIT
singleline_comment|//                                       | TX4927_IRQ_PIC_STARTUP
singleline_comment|//                                       | TX4927_IRQ_PIC_SHUTDOWN
singleline_comment|//                                       | TX4927_IRQ_PIC_ENABLE
singleline_comment|//                                       | TX4927_IRQ_PIC_DISABLE
singleline_comment|//                                       | TX4927_IRQ_PIC_MASK
singleline_comment|//                                       | TX4927_IRQ_PIC_ENDIRQ
singleline_comment|//                                       | TX4927_IRQ_INIT
singleline_comment|//                                       | TX4927_IRQ_NEST1
singleline_comment|//                                       | TX4927_IRQ_NEST2
singleline_comment|//                                       | TX4927_IRQ_NEST3
singleline_comment|//                                       | TX4927_IRQ_NEST4
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef TX4927_IRQ_DEBUG
DECL|macro|TX4927_IRQ_DPRINTK
mdefine_line|#define TX4927_IRQ_DPRINTK(flag,str...) &bslash;&n;        if ( (tx4927_irq_debug_flag) &amp; (flag) ) &bslash;&n;        { &bslash;&n;           char tmp[100]; &bslash;&n;           sprintf( tmp, str ); &bslash;&n;           printk( &quot;%s(%s:%u)::%s&quot;, __FUNCTION__, __FILE__, __LINE__, tmp ); &bslash;&n;        }
macro_line|#else
DECL|macro|TX4927_IRQ_DPRINTK
mdefine_line|#define TX4927_IRQ_DPRINTK(flag,str...)
macro_line|#endif
multiline_comment|/*&n; * Forwad definitions for all pic&squot;s&n; */
r_static
r_int
r_int
id|tx4927_irq_cp0_startup
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|tx4927_irq_cp0_shutdown
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|tx4927_irq_cp0_enable
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|tx4927_irq_cp0_disable
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|tx4927_irq_cp0_mask_and_ack
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|tx4927_irq_cp0_end
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_int
r_int
id|tx4927_irq_pic_startup
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|tx4927_irq_pic_shutdown
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|tx4927_irq_pic_enable
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|tx4927_irq_pic_disable
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|tx4927_irq_pic_mask_and_ack
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|tx4927_irq_pic_end
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n; * Kernel structs for all pic&squot;s&n; */
DECL|variable|tx4927_cp0_lock
r_static
id|spinlock_t
id|tx4927_cp0_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|tx4927_pic_lock
r_static
id|spinlock_t
id|tx4927_pic_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|macro|TX4927_CP0_NAME
mdefine_line|#define TX4927_CP0_NAME &quot;TX4927-CP0&quot;
DECL|variable|tx4927_irq_cp0_type
r_static
r_struct
id|hw_interrupt_type
id|tx4927_irq_cp0_type
op_assign
(brace
dot
r_typename
op_assign
id|TX4927_CP0_NAME
comma
dot
id|startup
op_assign
id|tx4927_irq_cp0_startup
comma
dot
id|shutdown
op_assign
id|tx4927_irq_cp0_shutdown
comma
dot
id|enable
op_assign
id|tx4927_irq_cp0_enable
comma
dot
id|disable
op_assign
id|tx4927_irq_cp0_disable
comma
dot
id|ack
op_assign
id|tx4927_irq_cp0_mask_and_ack
comma
dot
id|end
op_assign
id|tx4927_irq_cp0_end
comma
dot
id|set_affinity
op_assign
l_int|NULL
)brace
suffix:semicolon
DECL|macro|TX4927_PIC_NAME
mdefine_line|#define TX4927_PIC_NAME &quot;TX4927-PIC&quot;
DECL|variable|tx4927_irq_pic_type
r_static
r_struct
id|hw_interrupt_type
id|tx4927_irq_pic_type
op_assign
(brace
dot
r_typename
op_assign
id|TX4927_PIC_NAME
comma
dot
id|startup
op_assign
id|tx4927_irq_pic_startup
comma
dot
id|shutdown
op_assign
id|tx4927_irq_pic_shutdown
comma
dot
id|enable
op_assign
id|tx4927_irq_pic_enable
comma
dot
id|disable
op_assign
id|tx4927_irq_pic_disable
comma
dot
id|ack
op_assign
id|tx4927_irq_pic_mask_and_ack
comma
dot
id|end
op_assign
id|tx4927_irq_pic_end
comma
dot
id|set_affinity
op_assign
l_int|NULL
)brace
suffix:semicolon
DECL|macro|TX4927_PIC_ACTION
mdefine_line|#define TX4927_PIC_ACTION(s) { no_action, 0, CPU_MASK_NONE, s, NULL, NULL }
DECL|variable|tx4927_irq_pic_action
r_static
r_struct
id|irqaction
id|tx4927_irq_pic_action
op_assign
id|TX4927_PIC_ACTION
c_func
(paren
id|TX4927_PIC_NAME
)paren
suffix:semicolon
DECL|macro|CCP0_STATUS
mdefine_line|#define CCP0_STATUS 12
DECL|macro|CCP0_CAUSE
mdefine_line|#define CCP0_CAUSE 13
multiline_comment|/*&n; * Functions for cp0&n; */
DECL|macro|tx4927_irq_cp0_mask
mdefine_line|#define tx4927_irq_cp0_mask(irq) ( 1 &lt;&lt; ( irq-TX4927_IRQ_CP0_BEG+8 ) )
r_static
r_void
DECL|function|tx4927_irq_cp0_modify
id|tx4927_irq_cp0_modify
c_func
(paren
r_int
id|cp0_reg
comma
r_int
id|clr_bits
comma
r_int
id|set_bits
)paren
(brace
r_int
r_int
id|val
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|cp0_reg
)paren
(brace
r_case
id|CCP0_STATUS
suffix:colon
id|val
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CCP0_CAUSE
suffix:colon
id|val
op_assign
id|read_c0_cause
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|val
op_and_assign
(paren
op_complement
id|clr_bits
)paren
suffix:semicolon
id|val
op_or_assign
(paren
id|set_bits
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cp0_reg
)paren
(brace
r_case
id|CCP0_STATUS
suffix:colon
(brace
id|write_c0_status
c_func
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|CCP0_CAUSE
suffix:colon
(brace
id|write_c0_cause
c_func
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
suffix:semicolon
)brace
DECL|function|tx4927_irq_cp0_init
r_static
r_void
id|__init
id|tx4927_irq_cp0_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_CP0_INIT
comma
l_string|&quot;beg=%d end=%d&bslash;n&quot;
comma
id|TX4927_IRQ_CP0_BEG
comma
id|TX4927_IRQ_CP0_END
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|TX4927_IRQ_CP0_BEG
suffix:semicolon
id|i
op_le
id|TX4927_IRQ_CP0_END
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
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|tx4927_irq_cp0_type
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|tx4927_irq_cp0_startup
r_static
r_int
r_int
id|tx4927_irq_cp0_startup
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_CP0_STARTUP
comma
l_string|&quot;irq=%d &bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|tx4927_irq_cp0_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|tx4927_irq_cp0_shutdown
r_static
r_void
id|tx4927_irq_cp0_shutdown
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_CP0_SHUTDOWN
comma
l_string|&quot;irq=%d &bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|tx4927_irq_cp0_disable
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|tx4927_irq_cp0_enable
r_static
r_void
id|tx4927_irq_cp0_enable
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_CP0_ENABLE
comma
l_string|&quot;irq=%d &bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|tx4927_cp0_lock
comma
id|flags
)paren
suffix:semicolon
id|tx4927_irq_cp0_modify
c_func
(paren
id|CCP0_STATUS
comma
l_int|0
comma
id|tx4927_irq_cp0_mask
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tx4927_cp0_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|tx4927_irq_cp0_disable
r_static
r_void
id|tx4927_irq_cp0_disable
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_CP0_DISABLE
comma
l_string|&quot;irq=%d &bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|tx4927_cp0_lock
comma
id|flags
)paren
suffix:semicolon
id|tx4927_irq_cp0_modify
c_func
(paren
id|CCP0_STATUS
comma
id|tx4927_irq_cp0_mask
c_func
(paren
id|irq
)paren
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tx4927_cp0_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|tx4927_irq_cp0_mask_and_ack
r_static
r_void
id|tx4927_irq_cp0_mask_and_ack
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_CP0_MASK
comma
l_string|&quot;irq=%d &bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|tx4927_irq_cp0_disable
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|tx4927_irq_cp0_end
r_static
r_void
id|tx4927_irq_cp0_end
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_CP0_ENDIRQ
comma
l_string|&quot;irq=%d &bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
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
(brace
id|tx4927_irq_cp0_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Functions for pic&n; */
DECL|function|tx4927_irq_pic_addr
id|u32
id|tx4927_irq_pic_addr
c_func
(paren
r_int
id|irq
)paren
(brace
multiline_comment|/* MVMCP -- need to formulize this */
id|irq
op_sub_assign
id|TX4927_IRQ_PIC_BEG
suffix:semicolon
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
l_int|17
suffix:colon
r_case
l_int|16
suffix:colon
r_case
l_int|1
suffix:colon
r_case
l_int|0
suffix:colon
r_return
(paren
l_int|0xff1ff610
)paren
suffix:semicolon
r_case
l_int|19
suffix:colon
r_case
l_int|18
suffix:colon
r_case
l_int|3
suffix:colon
r_case
l_int|2
suffix:colon
r_return
(paren
l_int|0xff1ff614
)paren
suffix:semicolon
r_case
l_int|21
suffix:colon
r_case
l_int|20
suffix:colon
r_case
l_int|5
suffix:colon
r_case
l_int|4
suffix:colon
r_return
(paren
l_int|0xff1ff618
)paren
suffix:semicolon
r_case
l_int|23
suffix:colon
r_case
l_int|22
suffix:colon
r_case
l_int|7
suffix:colon
r_case
l_int|6
suffix:colon
r_return
(paren
l_int|0xff1ff61c
)paren
suffix:semicolon
r_case
l_int|25
suffix:colon
r_case
l_int|24
suffix:colon
r_case
l_int|9
suffix:colon
r_case
l_int|8
suffix:colon
r_return
(paren
l_int|0xff1ff620
)paren
suffix:semicolon
r_case
l_int|27
suffix:colon
r_case
l_int|26
suffix:colon
r_case
l_int|11
suffix:colon
r_case
l_int|10
suffix:colon
r_return
(paren
l_int|0xff1ff624
)paren
suffix:semicolon
r_case
l_int|29
suffix:colon
r_case
l_int|28
suffix:colon
r_case
l_int|13
suffix:colon
r_case
l_int|12
suffix:colon
r_return
(paren
l_int|0xff1ff628
)paren
suffix:semicolon
r_case
l_int|31
suffix:colon
r_case
l_int|30
suffix:colon
r_case
l_int|15
suffix:colon
r_case
l_int|14
suffix:colon
r_return
(paren
l_int|0xff1ff62c
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|tx4927_irq_pic_mask
id|u32
id|tx4927_irq_pic_mask
c_func
(paren
r_int
id|irq
)paren
(brace
multiline_comment|/* MVMCP -- need to formulize this */
id|irq
op_sub_assign
id|TX4927_IRQ_PIC_BEG
suffix:semicolon
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
l_int|31
suffix:colon
r_case
l_int|29
suffix:colon
r_case
l_int|27
suffix:colon
r_case
l_int|25
suffix:colon
r_case
l_int|23
suffix:colon
r_case
l_int|21
suffix:colon
r_case
l_int|19
suffix:colon
r_case
l_int|17
suffix:colon
(brace
r_return
(paren
l_int|0x07000000
)paren
suffix:semicolon
)brace
r_case
l_int|30
suffix:colon
r_case
l_int|28
suffix:colon
r_case
l_int|26
suffix:colon
r_case
l_int|24
suffix:colon
r_case
l_int|22
suffix:colon
r_case
l_int|20
suffix:colon
r_case
l_int|18
suffix:colon
r_case
l_int|16
suffix:colon
(brace
r_return
(paren
l_int|0x00070000
)paren
suffix:semicolon
)brace
r_case
l_int|15
suffix:colon
r_case
l_int|13
suffix:colon
r_case
l_int|11
suffix:colon
r_case
l_int|9
suffix:colon
r_case
l_int|7
suffix:colon
r_case
l_int|5
suffix:colon
r_case
l_int|3
suffix:colon
r_case
l_int|1
suffix:colon
(brace
r_return
(paren
l_int|0x00000700
)paren
suffix:semicolon
)brace
r_case
l_int|14
suffix:colon
r_case
l_int|12
suffix:colon
r_case
l_int|10
suffix:colon
r_case
l_int|8
suffix:colon
r_case
l_int|6
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|2
suffix:colon
r_case
l_int|0
suffix:colon
(brace
r_return
(paren
l_int|0x00000007
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
l_int|0x00000000
)paren
suffix:semicolon
)brace
DECL|function|tx4927_irq_pic_modify
r_static
r_void
id|tx4927_irq_pic_modify
c_func
(paren
r_int
id|pic_reg
comma
r_int
id|clr_bits
comma
r_int
id|set_bits
)paren
(brace
r_int
r_int
id|val
op_assign
l_int|0
suffix:semicolon
id|val
op_assign
id|TX4927_RD
c_func
(paren
id|pic_reg
)paren
suffix:semicolon
id|val
op_and_assign
(paren
op_complement
id|clr_bits
)paren
suffix:semicolon
id|val
op_or_assign
(paren
id|set_bits
)paren
suffix:semicolon
id|TX4927_WR
c_func
(paren
id|pic_reg
comma
id|val
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|tx4927_irq_pic_init
r_static
r_void
id|__init
id|tx4927_irq_pic_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_PIC_INIT
comma
l_string|&quot;beg=%d end=%d&bslash;n&quot;
comma
id|TX4927_IRQ_PIC_BEG
comma
id|TX4927_IRQ_PIC_END
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|TX4927_IRQ_PIC_BEG
suffix:semicolon
id|i
op_le
id|TX4927_IRQ_PIC_END
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
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|depth
op_assign
l_int|2
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|tx4927_irq_pic_type
suffix:semicolon
)brace
id|setup_irq
c_func
(paren
id|TX4927_IRQ_NEST_PIC_ON_CP0
comma
op_amp
id|tx4927_irq_pic_action
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|tx4927_pic_lock
comma
id|flags
)paren
suffix:semicolon
id|TX4927_WR
c_func
(paren
l_int|0xff1ff640
comma
l_int|0x6
)paren
suffix:semicolon
multiline_comment|/* irq level mask -- only accept hightest */
id|TX4927_WR
c_func
(paren
l_int|0xff1ff600
comma
id|TX4927_RD
c_func
(paren
l_int|0xff1ff600
)paren
op_or
l_int|0x1
)paren
suffix:semicolon
multiline_comment|/* irq enable */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tx4927_pic_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|tx4927_irq_pic_startup
r_static
r_int
r_int
id|tx4927_irq_pic_startup
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_PIC_STARTUP
comma
l_string|&quot;irq=%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|tx4927_irq_pic_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|tx4927_irq_pic_shutdown
r_static
r_void
id|tx4927_irq_pic_shutdown
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_PIC_SHUTDOWN
comma
l_string|&quot;irq=%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|tx4927_irq_pic_disable
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|tx4927_irq_pic_enable
r_static
r_void
id|tx4927_irq_pic_enable
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_PIC_ENABLE
comma
l_string|&quot;irq=%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|tx4927_pic_lock
comma
id|flags
)paren
suffix:semicolon
id|tx4927_irq_pic_modify
c_func
(paren
id|tx4927_irq_pic_addr
c_func
(paren
id|irq
)paren
comma
l_int|0
comma
id|tx4927_irq_pic_mask
c_func
(paren
id|irq
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tx4927_pic_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|tx4927_irq_pic_disable
r_static
r_void
id|tx4927_irq_pic_disable
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_PIC_DISABLE
comma
l_string|&quot;irq=%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|tx4927_pic_lock
comma
id|flags
)paren
suffix:semicolon
id|tx4927_irq_pic_modify
c_func
(paren
id|tx4927_irq_pic_addr
c_func
(paren
id|irq
)paren
comma
id|tx4927_irq_pic_mask
c_func
(paren
id|irq
)paren
comma
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|tx4927_pic_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|tx4927_irq_pic_mask_and_ack
r_static
r_void
id|tx4927_irq_pic_mask_and_ack
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_PIC_MASK
comma
l_string|&quot;irq=%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|tx4927_irq_pic_disable
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|tx4927_irq_pic_end
r_static
r_void
id|tx4927_irq_pic_end
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_PIC_ENDIRQ
comma
l_string|&quot;irq=%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
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
(brace
id|tx4927_irq_pic_enable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Main init functions&n; */
DECL|function|tx4927_irq_init
r_void
id|__init
id|tx4927_irq_init
c_func
(paren
r_void
)paren
(brace
r_extern
id|asmlinkage
r_void
id|tx4927_irq_handler
c_func
(paren
r_void
)paren
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_INIT
comma
l_string|&quot;-&bslash;n&quot;
)paren
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_INIT
comma
l_string|&quot;=Calling tx4927_irq_cp0_init()&bslash;n&quot;
)paren
suffix:semicolon
id|tx4927_irq_cp0_init
c_func
(paren
)paren
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_INIT
comma
l_string|&quot;=Calling tx4927_irq_pic_init()&bslash;n&quot;
)paren
suffix:semicolon
id|tx4927_irq_pic_init
c_func
(paren
)paren
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_INIT
comma
l_string|&quot;=Calling set_except_vector(tx4927_irq_handler)&bslash;n&quot;
)paren
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|0
comma
id|tx4927_irq_handler
)paren
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_INIT
comma
l_string|&quot;+&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|tx4927_irq_nested
r_int
id|tx4927_irq_nested
c_func
(paren
r_void
)paren
(brace
r_int
id|sw_irq
op_assign
l_int|0
suffix:semicolon
id|u32
id|level2
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_NEST1
comma
l_string|&quot;-&bslash;n&quot;
)paren
suffix:semicolon
id|level2
op_assign
id|TX4927_RD
c_func
(paren
l_int|0xff1ff6a0
)paren
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_NEST2
comma
l_string|&quot;=level2a=0x%x&bslash;n&quot;
comma
id|level2
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|level2
op_amp
l_int|0x10000
)paren
op_eq
l_int|0
)paren
(brace
id|level2
op_and_assign
l_int|0x1f
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_NEST3
comma
l_string|&quot;=level2b=0x%x&bslash;n&quot;
comma
id|level2
)paren
suffix:semicolon
id|sw_irq
op_assign
id|TX4927_IRQ_PIC_BEG
op_plus
id|level2
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_NEST3
comma
l_string|&quot;=sw_irq=%d&bslash;n&quot;
comma
id|sw_irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sw_irq
op_eq
l_int|27
)paren
(brace
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_NEST4
comma
l_string|&quot;=irq-%d&bslash;n&quot;
comma
id|sw_irq
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_TOSHIBA_RBTX4927
(brace
id|sw_irq
op_assign
id|toshiba_rbtx4927_irq_nested
c_func
(paren
id|sw_irq
)paren
suffix:semicolon
)brace
macro_line|#endif
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_NEST4
comma
l_string|&quot;=irq+%d&bslash;n&quot;
comma
id|sw_irq
)paren
suffix:semicolon
)brace
)brace
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_NEST2
comma
l_string|&quot;=sw_irq=%d&bslash;n&quot;
comma
id|sw_irq
)paren
suffix:semicolon
id|TX4927_IRQ_DPRINTK
c_func
(paren
id|TX4927_IRQ_NEST1
comma
l_string|&quot;+&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
id|sw_irq
)paren
suffix:semicolon
)brace
eof
