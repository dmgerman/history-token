multiline_comment|/*&n; * linux/arch/mips/au1000/db1x00/mirage_ts.c&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Glue between Mirage board-specific touchscreen pieces&n; *&t;and generic Wolfson Codec touchscreen support.&n; *&n; *&t;Based on pb1100_ts.c used in Hydrogen II.&n; *&n; * Copyright (c) 2003 Embedded Edge, LLC&n; *&t;&t;dan@embeddededge.com&n; *&n; *  This program is free software; you can redistribute&t; it and/or modify it&n; *  under  the terms of&t; the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the&t;License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED&t;  ``AS&t;IS&squot;&squot; AND   ANY&t;EXPRESS OR IMPLIED&n; *  WARRANTIES,&t;  INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO&t;EVENT  SHALL   THE AUTHOR  BE&t; LIABLE FOR ANY&t;  DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED&t;  TO, PROCUREMENT OF  SUBSTITUTE GOODS&t;OR SERVICES; LOSS OF&n; *  USE, DATA,&t;OR PROFITS; OR&t;BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN&t; CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/au1000.h&gt;
multiline_comment|/*&n; *  Imported interface to Wolfson Codec driver.&n; */
r_extern
r_void
op_star
id|wm97xx_ts_get_handle
c_func
(paren
r_int
id|which
)paren
suffix:semicolon
r_extern
r_int
id|wm97xx_ts_ready
c_func
(paren
r_void
op_star
id|ts_handle
)paren
suffix:semicolon
r_extern
r_void
id|wm97xx_ts_set_cal
c_func
(paren
r_void
op_star
id|ts_handle
comma
r_int
id|xscale
comma
r_int
id|xtrans
comma
r_int
id|yscale
comma
r_int
id|ytrans
)paren
suffix:semicolon
r_extern
id|u16
id|wm97xx_ts_get_ac97
c_func
(paren
r_void
op_star
id|ts_handle
comma
id|u8
id|reg
)paren
suffix:semicolon
r_extern
r_void
id|wm97xx_ts_set_ac97
c_func
(paren
r_void
op_star
id|ts_handle
comma
id|u8
id|reg
comma
id|u16
id|val
)paren
suffix:semicolon
r_extern
r_int
id|wm97xx_ts_read_data
c_func
(paren
r_void
op_star
id|ts_handle
comma
r_int
op_star
id|x
comma
r_int
op_star
id|y
comma
r_int
op_star
id|pressure
)paren
suffix:semicolon
r_extern
r_void
id|wm97xx_ts_send_data
c_func
(paren
r_void
op_star
id|ts_handle
comma
r_int
id|x
comma
r_int
id|y
comma
r_int
id|z
)paren
suffix:semicolon
DECL|variable|wm97xx_comodule_present
r_int
id|wm97xx_comodule_present
op_assign
l_int|1
suffix:semicolon
DECL|macro|TS_NAME
mdefine_line|#define TS_NAME &quot;mirage_ts&quot;
DECL|macro|err
mdefine_line|#define err(format, arg...) printk(KERN_ERR TS_NAME &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
DECL|macro|info
mdefine_line|#define info(format, arg...) printk(KERN_INFO TS_NAME &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
DECL|macro|warn
mdefine_line|#define warn(format, arg...) printk(KERN_WARNING TS_NAME &quot;: &quot; format &quot;&bslash;n&quot; , ## arg)
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format, arg...) printk(&quot;%s: &quot; format &quot;&bslash;n&quot;, __FUNCTION__ , ## arg)
DECL|macro|PEN_DOWN_IRQ
mdefine_line|#define PEN_DOWN_IRQ&t;AU1000_GPIO_7
DECL|variable|ts_task
r_static
r_struct
id|task_struct
op_star
id|ts_task
op_assign
l_int|0
suffix:semicolon
r_static
id|DECLARE_COMPLETION
c_func
(paren
id|ts_complete
)paren
suffix:semicolon
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|pendown_wait
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_WM97XX_FIVEWIRETS
DECL|variable|release_pressure
r_static
r_int
id|release_pressure
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|release_pressure
r_static
r_int
id|release_pressure
op_assign
l_int|50
suffix:semicolon
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|x
r_int
id|x
suffix:semicolon
DECL|member|y
r_int
id|y
suffix:semicolon
DECL|typedef|DOWN_EVENT
)brace
id|DOWN_EVENT
suffix:semicolon
DECL|macro|SAMPLE_RATE
mdefine_line|#define SAMPLE_RATE&t;50&t;/* samples per second */
DECL|macro|PEN_DEBOUNCE
mdefine_line|#define PEN_DEBOUNCE&t;5&t;/* samples for settling - fn of SAMPLE_RATE */
DECL|macro|PEN_UP_TIMEOUT
mdefine_line|#define PEN_UP_TIMEOUT&t;10&t;/* in seconds */
DECL|macro|PEN_UP_SETTLE
mdefine_line|#define PEN_UP_SETTLE&t;5&t;/* samples per second */
r_static
r_struct
(brace
DECL|member|xscale
r_int
id|xscale
suffix:semicolon
DECL|member|xtrans
r_int
id|xtrans
suffix:semicolon
DECL|member|yscale
r_int
id|yscale
suffix:semicolon
DECL|member|ytrans
r_int
id|ytrans
suffix:semicolon
DECL|variable|mirage_ts_cal
)brace
id|mirage_ts_cal
op_assign
(brace
macro_line|#if 0
id|xscale
suffix:colon
l_int|84
comma
id|xtrans
suffix:colon
op_minus
l_int|157
comma
id|yscale
suffix:colon
l_int|66
comma
id|ytrans
suffix:colon
op_minus
l_int|150
comma
macro_line|#else
id|xscale
suffix:colon
l_int|84
comma
id|xtrans
suffix:colon
op_minus
l_int|150
comma
id|yscale
suffix:colon
l_int|66
comma
id|ytrans
suffix:colon
op_minus
l_int|146
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|pendown_irq
r_static
r_void
id|pendown_irq
c_func
(paren
r_int
id|irqnr
comma
r_void
op_star
id|devid
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
singleline_comment|//DPRINTK(&quot;got one 0x%x&quot;, au_readl(SYS_PINSTATERD));
id|wake_up
c_func
(paren
op_amp
id|pendown_wait
)paren
suffix:semicolon
)brace
DECL|function|ts_thread
r_static
r_int
id|ts_thread
c_func
(paren
r_void
op_star
id|id
)paren
(brace
r_static
r_int
id|pen_was_down
op_assign
l_int|0
suffix:semicolon
r_static
id|DOWN_EVENT
id|pen_xy
suffix:semicolon
r_int
id|x
comma
id|y
comma
id|z
suffix:semicolon
r_void
op_star
id|ts
suffix:semicolon
multiline_comment|/* handle */
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_int
id|timeout
op_assign
id|HZ
op_div
id|SAMPLE_RATE
suffix:semicolon
id|ts_task
op_assign
id|tsk
suffix:semicolon
id|daemonize
c_func
(paren
)paren
suffix:semicolon
id|tsk-&gt;tty
op_assign
l_int|NULL
suffix:semicolon
id|tsk-&gt;policy
op_assign
id|SCHED_FIFO
suffix:semicolon
id|tsk-&gt;rt_priority
op_assign
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|tsk-&gt;comm
comma
l_string|&quot;touchscreen&quot;
)paren
suffix:semicolon
multiline_comment|/* only want to receive SIGKILL */
id|spin_lock_irq
c_func
(paren
op_amp
id|tsk-&gt;sigmask_lock
)paren
suffix:semicolon
id|siginitsetinv
c_func
(paren
op_amp
id|tsk-&gt;blocked
comma
id|sigmask
c_func
(paren
id|SIGKILL
)paren
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|tsk-&gt;sigmask_lock
)paren
suffix:semicolon
multiline_comment|/* get handle for codec */
id|ts
op_assign
id|wm97xx_ts_get_handle
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* proceed only after everybody is ready */
id|wait_event_timeout
c_func
(paren
id|pendown_wait
comma
id|wm97xx_ts_ready
c_func
(paren
id|ts
)paren
comma
id|HZ
op_div
l_int|4
)paren
suffix:semicolon
multiline_comment|/* board-specific calibration */
id|wm97xx_ts_set_cal
c_func
(paren
id|ts
comma
id|mirage_ts_cal.xscale
comma
id|mirage_ts_cal.xtrans
comma
id|mirage_ts_cal.yscale
comma
id|mirage_ts_cal.ytrans
)paren
suffix:semicolon
multiline_comment|/* route Wolfson pendown interrupts to our GPIO */
id|au_sync
c_func
(paren
)paren
suffix:semicolon
id|wm97xx_ts_set_ac97
c_func
(paren
id|ts
comma
l_int|0x4c
comma
id|wm97xx_ts_get_ac97
c_func
(paren
id|ts
comma
l_int|0x4c
)paren
op_amp
op_complement
l_int|0x0008
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
id|wm97xx_ts_set_ac97
c_func
(paren
id|ts
comma
l_int|0x56
comma
id|wm97xx_ts_get_ac97
c_func
(paren
id|ts
comma
l_int|0x56
)paren
op_amp
op_complement
l_int|0x0008
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
id|wm97xx_ts_set_ac97
c_func
(paren
id|ts
comma
l_int|0x52
comma
id|wm97xx_ts_get_ac97
c_func
(paren
id|ts
comma
l_int|0x52
)paren
op_or
l_int|0x2008
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|interruptible_sleep_on_timeout
c_func
(paren
op_amp
id|pendown_wait
comma
id|timeout
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
id|PEN_DOWN_IRQ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|tsk
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/* read codec */
r_if
c_cond
(paren
op_logical_neg
id|wm97xx_ts_read_data
c_func
(paren
id|ts
comma
op_amp
id|x
comma
op_amp
id|y
comma
op_amp
id|z
)paren
)paren
id|z
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* treat no-data and pen-up the same */
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|tsk
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|z
op_ge
id|release_pressure
)paren
(brace
id|y
op_assign
op_complement
id|y
suffix:semicolon
multiline_comment|/* top to bottom */
r_if
c_cond
(paren
id|pen_was_down
OG
l_int|1
multiline_comment|/*&amp;&amp; pen_was_down &lt; PEN_DEBOUNCE*/
)paren
(brace
singleline_comment|//THXXX
multiline_comment|/* bounce ? */
id|x
op_assign
id|pen_xy.x
suffix:semicolon
id|y
op_assign
id|pen_xy.y
suffix:semicolon
op_decrement
id|pen_was_down
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pen_was_down
op_le
l_int|1
)paren
(brace
id|pen_xy.x
op_assign
id|x
suffix:semicolon
id|pen_xy.y
op_assign
id|y
suffix:semicolon
r_if
c_cond
(paren
id|pen_was_down
)paren
id|wm97xx_ts_send_data
c_func
(paren
id|ts
comma
id|x
comma
id|y
comma
id|z
)paren
suffix:semicolon
id|pen_was_down
op_assign
id|PEN_DEBOUNCE
suffix:semicolon
)brace
singleline_comment|//wm97xx_ts_send_data(ts, x, y, z);
id|timeout
op_assign
id|HZ
op_div
id|SAMPLE_RATE
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|pen_was_down
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|pen_was_down
)paren
id|z
op_assign
id|release_pressure
suffix:semicolon
r_else
singleline_comment|//THXXX
id|wm97xx_ts_send_data
c_func
(paren
id|ts
comma
id|pen_xy.x
comma
id|pen_xy.y
comma
id|z
)paren
suffix:semicolon
)brace
multiline_comment|/* The pendown signal takes some time to settle after&n;&t;&t;&t; * reading the pen pressure so wait a little&n;&t;&t;&t; * before enabling the pen.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|pen_was_down
)paren
(brace
singleline_comment|//&t;&t;&t;&t;interruptible_sleep_on_timeout(&amp;pendown_wait, HZ / PEN_UP_SETTLE);
id|timeout
op_assign
id|HZ
op_star
id|PEN_UP_TIMEOUT
suffix:semicolon
)brace
)brace
id|enable_irq
c_func
(paren
id|PEN_DOWN_IRQ
)paren
suffix:semicolon
)brace
id|enable_irq
c_func
(paren
id|PEN_DOWN_IRQ
)paren
suffix:semicolon
id|ts_task
op_assign
l_int|NULL
suffix:semicolon
id|complete
c_func
(paren
op_amp
id|ts_complete
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ts_mirage_init
r_static
r_int
id|__init
id|ts_mirage_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/* pen down signal is connected to GPIO 7 */
id|ret
op_assign
id|request_irq
c_func
(paren
id|PEN_DOWN_IRQ
comma
id|pendown_irq
comma
l_int|0
comma
l_string|&quot;ts-pendown&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|err
c_func
(paren
l_string|&quot;unable to get pendown irq%d: [%d]&quot;
comma
id|PEN_DOWN_IRQ
comma
id|ret
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|kernel_thread
c_func
(paren
id|ts_thread
comma
l_int|NULL
comma
id|CLONE_FS
op_or
id|CLONE_FILES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|info
c_func
(paren
l_string|&quot;Mirage touchscreen IRQ initialized.&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ts_mirage_exit
r_static
r_void
id|__exit
id|ts_mirage_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|ts_task
)paren
(brace
id|send_sig
c_func
(paren
id|SIGKILL
comma
id|ts_task
comma
l_int|1
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|ts_complete
)paren
suffix:semicolon
)brace
id|free_irq
c_func
(paren
id|PEN_DOWN_IRQ
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|ts_mirage_init
id|module_init
c_func
(paren
id|ts_mirage_init
)paren
suffix:semicolon
DECL|variable|ts_mirage_exit
id|module_exit
c_func
(paren
id|ts_mirage_exit
)paren
suffix:semicolon
eof
