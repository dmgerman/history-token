multiline_comment|/*&n; * FILE NAME&n; *&t;arch/mips/vr41xx/common/cmu.c&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Clock Mask Unit routines for the NEC VR4100 series.&n; *&n; * Author: Yoichi Yuasa&n; *         yyuasa@mvista.com or source@mvista.com&n; *&n; * Copyright 2001,2002 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n; * Changes:&n; *  MontaVista Software Inc. &lt;yyuasa@mvista.com&gt; or &lt;source@mvista.com&gt;&n; *  - Added support for NEC VR4111 and VR4121.&n; *&n; *  MontaVista Software Inc. &lt;yyuasa@mvista.com&gt; or &lt;source@mvista.com&gt;&n; *  - New creation, NEC VR4122 and VR4131 are supported.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|VR4111_CMUCLKMSK
mdefine_line|#define VR4111_CMUCLKMSK&t;KSEG1ADDR(0x0b000060)
DECL|macro|VR4122_CMUCLKMSK
mdefine_line|#define VR4122_CMUCLKMSK&t;KSEG1ADDR(0x0f000060)
DECL|variable|vr41xx_cmu_base
r_static
id|u32
id|vr41xx_cmu_base
op_assign
l_int|0
suffix:semicolon
DECL|variable|cmuclkmsk
r_static
id|u16
id|cmuclkmsk
op_assign
l_int|0
suffix:semicolon
DECL|macro|write_cmu
mdefine_line|#define write_cmu(mask)&t;writew((mask), vr41xx_cmu_base)
DECL|function|vr41xx_clock_supply
r_void
id|vr41xx_clock_supply
c_func
(paren
id|u16
id|mask
)paren
(brace
id|cmuclkmsk
op_or_assign
id|mask
suffix:semicolon
id|write_cmu
c_func
(paren
id|cmuclkmsk
)paren
suffix:semicolon
)brace
DECL|function|vr41xx_clock_mask
r_void
id|vr41xx_clock_mask
c_func
(paren
id|u16
id|mask
)paren
(brace
id|cmuclkmsk
op_and_assign
op_complement
id|mask
suffix:semicolon
id|write_cmu
c_func
(paren
id|cmuclkmsk
)paren
suffix:semicolon
)brace
DECL|function|vr41xx_cmu_init
r_void
id|__init
id|vr41xx_cmu_init
c_func
(paren
id|u16
id|mask
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
id|vr41xx_cmu_base
op_assign
id|VR4111_CMUCLKMSK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_VR4122
suffix:colon
r_case
id|CPU_VR4131
suffix:colon
id|vr41xx_cmu_base
op_assign
id|VR4122_CMUCLKMSK
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
id|cmuclkmsk
op_assign
id|mask
suffix:semicolon
)brace
eof
