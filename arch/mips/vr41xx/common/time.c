multiline_comment|/*&n; * FILE NAME&n; *&t;arch/mips/vr41xx/common/time.c&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Timer routines for the NEC VR4100 series.&n; *&n; * Author: Yoichi Yuasa&n; *         yyuasa@mvista.com or source@mvista.com&n; *&n; * Copyright 2001,2002 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * Changes:&n; *  MontaVista Software Inc. &lt;yyuasa@mvista.com&gt; or &lt;source@mvista.com&gt;&n; *  - Added support for NEC VR4100 series RTC Unit.&n; *&n; *  MontaVista Software Inc. &lt;yyuasa@mvista.com&gt; or &lt;source@mvista.com&gt;&n; *  - New creation, NEC VR4100 series are supported.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/vr41xx/vr41xx.h&gt;
DECL|macro|VR4111_ETIMELREG
mdefine_line|#define VR4111_ETIMELREG&t;KSEG1ADDR(0x0b0000c0)
DECL|macro|VR4122_ETIMELREG
mdefine_line|#define VR4122_ETIMELREG&t;KSEG1ADDR(0x0f000100)
DECL|variable|vr41xx_rtc_base
id|u32
id|vr41xx_rtc_base
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_VR41XX_RTC
r_extern
r_int
r_int
id|vr41xx_rtc_get_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|vr41xx_rtc_set_time
c_func
(paren
r_int
r_int
id|sec
)paren
suffix:semicolon
macro_line|#endif
DECL|function|vr41xx_time_init
r_void
id|vr41xx_time_init
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|current_cpu_data.cputype
)paren
(brace
r_case
id|CPU_VR4111
suffix:colon
r_case
id|CPU_VR4121
suffix:colon
id|vr41xx_rtc_base
op_assign
id|VR4111_ETIMELREG
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_VR4122
suffix:colon
r_case
id|CPU_VR4131
suffix:colon
id|vr41xx_rtc_base
op_assign
id|VR4122_ETIMELREG
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Unexpected CPU of NEC VR4100 series&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_VR41XX_RTC
id|rtc_get_time
op_assign
id|vr41xx_rtc_get_time
suffix:semicolon
id|rtc_set_time
op_assign
id|vr41xx_rtc_set_time
suffix:semicolon
macro_line|#endif
)brace
DECL|function|vr41xx_timer_setup
r_void
id|vr41xx_timer_setup
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
(brace
id|u32
id|count
suffix:semicolon
id|setup_irq
c_func
(paren
id|MIPS_COUNTER_IRQ
comma
id|irq
)paren
suffix:semicolon
id|count
op_assign
id|read_c0_count
c_func
(paren
)paren
suffix:semicolon
id|write_c0_compare
c_func
(paren
id|count
op_plus
(paren
id|mips_counter_frequency
op_div
id|HZ
)paren
)paren
suffix:semicolon
)brace
eof
