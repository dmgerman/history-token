multiline_comment|/*&n;*&n;* smapi.c -- SMAPI interface routines&n;*&n;*&n;* Written By: Mike Sullivan IBM Corporation&n;*&n;* Copyright (C) 1999 IBM Corporation&n;*&n;* This program is free software; you can redistribute it and/or modify&n;* it under the terms of the GNU General Public License as published by&n;* the Free Software Foundation; either version 2 of the License, or&n;* (at your option) any later version.&n;*&n;* This program is distributed in the hope that it will be useful,&n;* but WITHOUT ANY WARRANTY; without even the implied warranty of&n;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;* GNU General Public License for more details.&n;*&n;* NO WARRANTY&n;* THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;* CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;* LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;* solely responsible for determining the appropriateness of using and&n;* distributing the Program and assumes all risks associated with its&n;* exercise of rights under this Agreement, including but not limited to&n;* the risks and costs of program errors, damage to or loss of data,&n;* programs or equipment, and unavailability or interruption of operations.&n;*&n;* DISCLAIMER OF LIABILITY&n;* NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;* DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;* USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;* HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;*&n;* You should have received a copy of the GNU General Public License&n;* along with this program; if not, write to the Free Software&n;* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*&n;*&n;* 10/23/2000 - Alpha Release&n;*&t;First release to the public&n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;&t;/* CMOS defines */
macro_line|#include &quot;smapi.h&quot;
macro_line|#include &quot;mwavedd.h&quot;
DECL|variable|g_usSmapiPort
r_static
r_int
r_int
id|g_usSmapiPort
op_assign
l_int|0
suffix:semicolon
DECL|function|smapi_request
r_static
r_int
id|smapi_request
c_func
(paren
r_int
r_int
id|inBX
comma
r_int
r_int
id|inCX
comma
r_int
r_int
id|inDI
comma
r_int
r_int
id|inSI
comma
r_int
r_int
op_star
id|outAX
comma
r_int
r_int
op_star
id|outBX
comma
r_int
r_int
op_star
id|outCX
comma
r_int
r_int
op_star
id|outDX
comma
r_int
r_int
op_star
id|outDI
comma
r_int
r_int
op_star
id|outSI
)paren
(brace
r_int
r_int
id|myoutAX
op_assign
l_int|2
comma
op_star
id|pmyoutAX
op_assign
op_amp
id|myoutAX
suffix:semicolon
r_int
r_int
id|myoutBX
op_assign
l_int|3
comma
op_star
id|pmyoutBX
op_assign
op_amp
id|myoutBX
suffix:semicolon
r_int
r_int
id|myoutCX
op_assign
l_int|4
comma
op_star
id|pmyoutCX
op_assign
op_amp
id|myoutCX
suffix:semicolon
r_int
r_int
id|myoutDX
op_assign
l_int|5
comma
op_star
id|pmyoutDX
op_assign
op_amp
id|myoutDX
suffix:semicolon
r_int
r_int
id|myoutDI
op_assign
l_int|6
comma
op_star
id|pmyoutDI
op_assign
op_amp
id|myoutDI
suffix:semicolon
r_int
r_int
id|myoutSI
op_assign
l_int|7
comma
op_star
id|pmyoutSI
op_assign
op_amp
id|myoutSI
suffix:semicolon
r_int
r_int
id|usSmapiOK
op_assign
op_minus
id|EIO
comma
op_star
id|pusSmapiOK
op_assign
op_amp
id|usSmapiOK
suffix:semicolon
r_int
r_int
id|inBXCX
op_assign
(paren
id|inBX
op_lshift
l_int|16
)paren
op_or
id|inCX
suffix:semicolon
r_int
r_int
id|inDISI
op_assign
(paren
id|inDI
op_lshift
l_int|16
)paren
op_or
id|inSI
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|PRINTK_5
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;inBX %x inCX %x inDI %x inSI %x&bslash;n&quot;
comma
id|inBX
comma
id|inCX
comma
id|inDI
comma
id|inSI
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movw  $0x5380,%%ax&bslash;n&bslash;t&quot;
l_string|&quot;movl  %7,%%ebx&bslash;n&bslash;t&quot;
l_string|&quot;shrl  $16, %%ebx&bslash;n&bslash;t&quot;
l_string|&quot;movw  %7,%%cx&bslash;n&bslash;t&quot;
l_string|&quot;movl  %8,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;shrl  $16,%%edi&bslash;n&bslash;t&quot;
l_string|&quot;movw  %8,%%si&bslash;n&bslash;t&quot;
l_string|&quot;movw  %9,%%dx&bslash;n&bslash;t&quot;
l_string|&quot;out   %%al,%%dx&bslash;n&bslash;t&quot;
l_string|&quot;out   %%al,$0x4F&bslash;n&bslash;t&quot;
l_string|&quot;cmpb  $0x53,%%ah&bslash;n&bslash;t&quot;
l_string|&quot;je    2f&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;orb   %%ah,%%ah&bslash;n&bslash;t&quot;
l_string|&quot;jnz   2f&bslash;n&bslash;t&quot;
l_string|&quot;movw  %%ax,%0&bslash;n&bslash;t&quot;
l_string|&quot;movw  %%bx,%1&bslash;n&bslash;t&quot;
l_string|&quot;movw  %%cx,%2&bslash;n&bslash;t&quot;
l_string|&quot;movw  %%dx,%3&bslash;n&bslash;t&quot;
l_string|&quot;movw  %%di,%4&bslash;n&bslash;t&quot;
l_string|&quot;movw  %%si,%5&bslash;n&bslash;t&quot;
l_string|&quot;movw  $1,%6&bslash;n&bslash;t&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|pmyoutAX
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|pmyoutBX
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|pmyoutCX
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|pmyoutDX
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|pmyoutDI
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|pmyoutSI
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|pusSmapiOK
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|inBXCX
)paren
comma
l_string|&quot;m&quot;
(paren
id|inDISI
)paren
comma
l_string|&quot;m&quot;
(paren
id|g_usSmapiPort
)paren
suffix:colon
l_string|&quot;%eax&quot;
comma
l_string|&quot;%ebx&quot;
comma
l_string|&quot;%ecx&quot;
comma
l_string|&quot;%edx&quot;
comma
l_string|&quot;%edi&quot;
comma
l_string|&quot;%esi&quot;
)paren
suffix:semicolon
id|PRINTK_8
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;myoutAX %x myoutBX %x myoutCX %x myoutDX %x myoutDI %x myoutSI %x usSmapiOK %x&bslash;n&quot;
comma
id|myoutAX
comma
id|myoutBX
comma
id|myoutCX
comma
id|myoutDX
comma
id|myoutDI
comma
id|myoutSI
comma
id|usSmapiOK
)paren
suffix:semicolon
op_star
id|outAX
op_assign
id|myoutAX
suffix:semicolon
op_star
id|outBX
op_assign
id|myoutBX
suffix:semicolon
op_star
id|outCX
op_assign
id|myoutCX
suffix:semicolon
op_star
id|outDX
op_assign
id|myoutDX
suffix:semicolon
op_star
id|outDI
op_assign
id|myoutDI
suffix:semicolon
op_star
id|outSI
op_assign
id|myoutSI
suffix:semicolon
id|retval
op_assign
(paren
id|usSmapiOK
op_eq
l_int|1
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_request exit retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|smapi_query_DSP_cfg
r_int
id|smapi_query_DSP_cfg
c_func
(paren
id|SMAPI_DSP_SETTINGS
op_star
id|pSettings
)paren
(brace
r_int
id|bRC
op_assign
op_minus
id|EIO
suffix:semicolon
r_int
r_int
id|usAX
comma
id|usBX
comma
id|usCX
comma
id|usDX
comma
id|usDI
comma
id|usSI
suffix:semicolon
r_int
r_int
id|ausDspBases
(braket
)braket
op_assign
(brace
l_int|0x0030
comma
l_int|0x4E30
comma
l_int|0x8E30
comma
l_int|0xCE30
comma
l_int|0x0130
comma
l_int|0x0350
comma
l_int|0x0070
comma
l_int|0x0DB0
)brace
suffix:semicolon
r_int
r_int
id|ausUartBases
(braket
)braket
op_assign
(brace
l_int|0x03F8
comma
l_int|0x02F8
comma
l_int|0x03E8
comma
l_int|0x02E8
)brace
suffix:semicolon
r_int
r_int
id|numDspBases
op_assign
l_int|8
suffix:semicolon
r_int
r_int
id|numUartBases
op_assign
l_int|4
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_query_DSP_cfg entry&bslash;n&quot;
)paren
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1802
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_query_DSP_cfg: Error: Could not get DSP Settings. Aborting.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|bRC
suffix:semicolon
)brace
id|PRINTK_1
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_query_DSP_cfg, smapi_request OK&bslash;n&quot;
)paren
suffix:semicolon
id|pSettings-&gt;bDSPPresent
op_assign
(paren
(paren
id|usBX
op_amp
l_int|0x0100
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|pSettings-&gt;bDSPEnabled
op_assign
(paren
(paren
id|usCX
op_amp
l_int|0x0001
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|pSettings-&gt;usDspIRQ
op_assign
id|usSI
op_amp
l_int|0x00FF
suffix:semicolon
id|pSettings-&gt;usDspDMA
op_assign
(paren
id|usSI
op_amp
l_int|0xFF00
)paren
op_rshift
l_int|8
suffix:semicolon
r_if
c_cond
(paren
(paren
id|usDI
op_amp
l_int|0x00FF
)paren
OL
id|numDspBases
)paren
(brace
id|pSettings-&gt;usDspBaseIO
op_assign
id|ausDspBases
(braket
id|usDI
op_amp
l_int|0x00FF
)braket
suffix:semicolon
)brace
r_else
(brace
id|pSettings-&gt;usDspBaseIO
op_assign
l_int|0
suffix:semicolon
)brace
id|PRINTK_6
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_query_DSP_cfg get DSP Settings bDSPPresent %x bDSPEnabled %x usDspIRQ %x usDspDMA %x usDspBaseIO %x&bslash;n&quot;
comma
id|pSettings-&gt;bDSPPresent
comma
id|pSettings-&gt;bDSPEnabled
comma
id|pSettings-&gt;usDspIRQ
comma
id|pSettings-&gt;usDspDMA
comma
id|pSettings-&gt;usDspBaseIO
)paren
suffix:semicolon
multiline_comment|/* check for illegal values */
r_if
c_cond
(paren
id|pSettings-&gt;usDspBaseIO
op_eq
l_int|0
)paren
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_query_DSP_cfg: Worry: DSP base I/O address is 0&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pSettings-&gt;usDspIRQ
op_eq
l_int|0
)paren
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_query_DSP_cfg: Worry: DSP IRQ line is 0&bslash;n&quot;
)paren
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1804
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
l_string|&quot;smapi::smapi_query_DSP_cfg: Error: Could not get DSP modem settings. Aborting.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|bRC
suffix:semicolon
)brace
id|PRINTK_1
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_query_DSP_cfg, smapi_request OK&bslash;n&quot;
)paren
suffix:semicolon
id|pSettings-&gt;bModemEnabled
op_assign
(paren
(paren
id|usCX
op_amp
l_int|0x0001
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|pSettings-&gt;usUartIRQ
op_assign
id|usSI
op_amp
l_int|0x000F
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|usSI
op_amp
l_int|0xFF00
)paren
op_rshift
l_int|8
)paren
OL
id|numUartBases
)paren
(brace
id|pSettings-&gt;usUartBaseIO
op_assign
id|ausUartBases
(braket
(paren
id|usSI
op_amp
l_int|0xFF00
)paren
op_rshift
l_int|8
)braket
suffix:semicolon
)brace
r_else
(brace
id|pSettings-&gt;usUartBaseIO
op_assign
l_int|0
suffix:semicolon
)brace
id|PRINTK_4
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_query_DSP_cfg get DSP modem settings bModemEnabled %x usUartIRQ %x usUartBaseIO %x&bslash;n&quot;
comma
id|pSettings-&gt;bModemEnabled
comma
id|pSettings-&gt;usUartIRQ
comma
id|pSettings-&gt;usUartBaseIO
)paren
suffix:semicolon
multiline_comment|/* check for illegal values */
r_if
c_cond
(paren
id|pSettings-&gt;usUartBaseIO
op_eq
l_int|0
)paren
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_query_DSP_cfg: Worry: UART base I/O address is 0&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pSettings-&gt;usUartIRQ
op_eq
l_int|0
)paren
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_query_DSP_cfg: Worry: UART IRQ line is 0&bslash;n&quot;
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_query_DSP_cfg exit bRC %x&bslash;n&quot;
comma
id|bRC
)paren
suffix:semicolon
r_return
id|bRC
suffix:semicolon
)brace
DECL|function|smapi_set_DSP_cfg
r_int
id|smapi_set_DSP_cfg
c_func
(paren
r_void
)paren
(brace
r_int
id|bRC
op_assign
op_minus
id|EIO
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|usAX
comma
id|usBX
comma
id|usCX
comma
id|usDX
comma
id|usDI
comma
id|usSI
suffix:semicolon
r_int
r_int
id|ausDspBases
(braket
)braket
op_assign
(brace
l_int|0x0030
comma
l_int|0x4E30
comma
l_int|0x8E30
comma
l_int|0xCE30
comma
l_int|0x0130
comma
l_int|0x0350
comma
l_int|0x0070
comma
l_int|0x0DB0
)brace
suffix:semicolon
r_int
r_int
id|ausUartBases
(braket
)braket
op_assign
(brace
l_int|0x03F8
comma
l_int|0x02F8
comma
l_int|0x03E8
comma
l_int|0x02E8
)brace
suffix:semicolon
r_int
r_int
id|ausDspIrqs
(braket
)braket
op_assign
(brace
l_int|5
comma
l_int|7
comma
l_int|10
comma
l_int|11
comma
l_int|15
)brace
suffix:semicolon
r_int
r_int
id|ausUartIrqs
(braket
)braket
op_assign
(brace
l_int|3
comma
l_int|4
)brace
suffix:semicolon
r_int
r_int
id|numDspBases
op_assign
l_int|8
suffix:semicolon
r_int
r_int
id|numUartBases
op_assign
l_int|4
suffix:semicolon
r_int
r_int
id|numDspIrqs
op_assign
l_int|5
suffix:semicolon
r_int
r_int
id|numUartIrqs
op_assign
l_int|2
suffix:semicolon
r_int
r_int
id|dspio_index
op_assign
l_int|0
comma
id|uartio_index
op_assign
l_int|0
suffix:semicolon
id|PRINTK_5
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_cfg entry mwave_3780i_irq %x mwave_3780i_io %x mwave_uart_irq %x mwave_uart_io %x&bslash;n&quot;
comma
id|mwave_3780i_irq
comma
id|mwave_3780i_io
comma
id|mwave_uart_irq
comma
id|mwave_uart_io
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mwave_3780i_io
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|numDspBases
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mwave_3780i_io
op_eq
id|ausDspBases
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|numDspBases
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_set_DSP_cfg: Error: Invalid mwave_3780i_io address %x. Aborting.&bslash;n&quot;
comma
id|mwave_3780i_io
)paren
suffix:semicolon
r_return
id|bRC
suffix:semicolon
)brace
id|dspio_index
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mwave_3780i_irq
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|numDspIrqs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mwave_3780i_irq
op_eq
id|ausDspIrqs
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|numDspIrqs
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_set_DSP_cfg: Error: Invalid mwave_3780i_irq %x. Aborting.&bslash;n&quot;
comma
id|mwave_3780i_irq
)paren
suffix:semicolon
r_return
id|bRC
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|mwave_uart_io
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|numUartBases
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mwave_uart_io
op_eq
id|ausUartBases
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|numUartBases
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_set_DSP_cfg: Error: Invalid mwave_uart_io address %x. Aborting.&bslash;n&quot;
comma
id|mwave_uart_io
)paren
suffix:semicolon
r_return
id|bRC
suffix:semicolon
)brace
id|uartio_index
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mwave_uart_irq
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|numUartIrqs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mwave_uart_irq
op_eq
id|ausUartIrqs
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
id|numUartIrqs
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_set_DSP_cfg: Error: Invalid mwave_uart_irq %x. Aborting.&bslash;n&quot;
comma
id|mwave_uart_irq
)paren
suffix:semicolon
r_return
id|bRC
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|mwave_uart_irq
op_logical_or
id|mwave_uart_io
)paren
(brace
multiline_comment|/* Check serial port A */
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1402
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
multiline_comment|/* bRC == 0 */
r_if
c_cond
(paren
id|usBX
op_amp
l_int|0x0100
)paren
(brace
multiline_comment|/* serial port A is present */
r_if
c_cond
(paren
id|usCX
op_amp
l_int|1
)paren
(brace
multiline_comment|/* serial port is enabled */
r_if
c_cond
(paren
(paren
id|usSI
op_amp
l_int|0xFF
)paren
op_eq
id|mwave_uart_irq
)paren
(brace
macro_line|#ifndef MWAVE_FUTZ_WITH_OTHER_DEVICES
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_set_DSP_cfg: Serial port A irq %x conflicts with mwave_uart_irq %x&bslash;n&quot;
comma
id|usSI
op_amp
l_int|0xFF
comma
id|mwave_uart_irq
)paren
suffix:semicolon
macro_line|#else
id|PRINTK_3
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_cfg: Serial port A irq %x conflicts with mwave_uart_irq %x&bslash;n&quot;
comma
id|usSI
op_amp
l_int|0xFF
comma
id|mwave_uart_irq
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MWAVE_FUTZ_WITH_OTHER_DEVICES
id|PRINTK_1
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_cfg Disabling conflicting serial port&bslash;n&quot;
)paren
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1403
comma
l_int|0x0100
comma
l_int|0
comma
id|usSI
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1402
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
macro_line|#else
r_goto
id|exit_conflict
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|usSI
op_rshift
l_int|8
)paren
op_eq
id|uartio_index
)paren
(brace
macro_line|#ifndef MWAVE_FUTZ_WITH_OTHER_DEVICES
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_set_DSP_cfg: Serial port A base I/O address %x conflicts with mwave uart I/O %x&bslash;n&quot;
comma
id|ausUartBases
(braket
id|usSI
op_rshift
l_int|8
)braket
comma
id|ausUartBases
(braket
id|uartio_index
)braket
)paren
suffix:semicolon
macro_line|#else
id|PRINTK_3
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_cfg: Serial port A base I/O address %x conflicts with mwave uart I/O %x&bslash;n&quot;
comma
id|ausUartBases
(braket
id|usSI
op_rshift
l_int|8
)braket
comma
id|ausUartBases
(braket
id|uartio_index
)braket
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MWAVE_FUTZ_WITH_OTHER_DEVICES
id|PRINTK_1
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_cfg Disabling conflicting serial port A&bslash;n&quot;
)paren
suffix:semicolon
id|bRC
op_assign
id|smapi_request
(paren
l_int|0x1403
comma
l_int|0x0100
comma
l_int|0
comma
id|usSI
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
id|bRC
op_assign
id|smapi_request
(paren
l_int|0x1402
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
macro_line|#else
r_goto
id|exit_conflict
suffix:semicolon
macro_line|#endif
)brace
)brace
)brace
)brace
multiline_comment|/* Check serial port B */
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1404
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
multiline_comment|/* bRC == 0 */
r_if
c_cond
(paren
id|usBX
op_amp
l_int|0x0100
)paren
(brace
multiline_comment|/* serial port B is present */
r_if
c_cond
(paren
id|usCX
op_amp
l_int|1
)paren
(brace
multiline_comment|/* serial port is enabled */
r_if
c_cond
(paren
(paren
id|usSI
op_amp
l_int|0xFF
)paren
op_eq
id|mwave_uart_irq
)paren
(brace
macro_line|#ifndef MWAVE_FUTZ_WITH_OTHER_DEVICES
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_set_DSP_cfg: Serial port B irq %x conflicts with mwave_uart_irq %x&bslash;n&quot;
comma
id|usSI
op_amp
l_int|0xFF
comma
id|mwave_uart_irq
)paren
suffix:semicolon
macro_line|#else
id|PRINTK_3
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_cfg: Serial port B irq %x conflicts with mwave_uart_irq %x&bslash;n&quot;
comma
id|usSI
op_amp
l_int|0xFF
comma
id|mwave_uart_irq
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MWAVE_FUTZ_WITH_OTHER_DEVICES
id|PRINTK_1
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_cfg Disabling conflicting serial port B&bslash;n&quot;
)paren
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1405
comma
l_int|0x0100
comma
l_int|0
comma
id|usSI
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1404
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
macro_line|#else
r_goto
id|exit_conflict
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|usSI
op_rshift
l_int|8
)paren
op_eq
id|uartio_index
)paren
(brace
macro_line|#ifndef MWAVE_FUTZ_WITH_OTHER_DEVICES
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_set_DSP_cfg: Serial port B base I/O address %x conflicts with mwave uart I/O %x&bslash;n&quot;
comma
id|ausUartBases
(braket
id|usSI
op_rshift
l_int|8
)braket
comma
id|ausUartBases
(braket
id|uartio_index
)braket
)paren
suffix:semicolon
macro_line|#else
id|PRINTK_3
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_cfg: Serial port B base I/O address %x conflicts with mwave uart I/O %x&bslash;n&quot;
comma
id|ausUartBases
(braket
id|usSI
op_rshift
l_int|8
)braket
comma
id|ausUartBases
(braket
id|uartio_index
)braket
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MWAVE_FUTZ_WITH_OTHER_DEVICES
id|PRINTK_1
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_cfg Disabling conflicting serial port B&bslash;n&quot;
)paren
suffix:semicolon
id|bRC
op_assign
id|smapi_request
(paren
l_int|0x1405
comma
l_int|0x0100
comma
l_int|0
comma
id|usSI
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
id|bRC
op_assign
id|smapi_request
(paren
l_int|0x1404
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
macro_line|#else
r_goto
id|exit_conflict
suffix:semicolon
macro_line|#endif
)brace
)brace
)brace
)brace
multiline_comment|/* Check IR port */
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1700
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1704
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
multiline_comment|/* bRC == 0 */
r_if
c_cond
(paren
(paren
id|usCX
op_amp
l_int|0xff
)paren
op_ne
l_int|0xff
)paren
(brace
multiline_comment|/* IR port not disabled */
r_if
c_cond
(paren
(paren
id|usCX
op_amp
l_int|0xff
)paren
op_eq
id|mwave_uart_irq
)paren
(brace
macro_line|#ifndef MWAVE_FUTZ_WITH_OTHER_DEVICES
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_set_DSP_cfg: IR port irq %x conflicts with mwave_uart_irq %x&bslash;n&quot;
comma
id|usCX
op_amp
l_int|0xff
comma
id|mwave_uart_irq
)paren
suffix:semicolon
macro_line|#else
id|PRINTK_3
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_cfg: IR port irq %x conflicts with mwave_uart_irq %x&bslash;n&quot;
comma
id|usCX
op_amp
l_int|0xff
comma
id|mwave_uart_irq
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MWAVE_FUTZ_WITH_OTHER_DEVICES
id|PRINTK_1
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_cfg Disabling conflicting IR port&bslash;n&quot;
)paren
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1701
comma
l_int|0x0100
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1700
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1705
comma
l_int|0x01ff
comma
l_int|0
comma
id|usSI
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1704
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
macro_line|#else
r_goto
id|exit_conflict
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|usSI
op_amp
l_int|0xff
)paren
op_eq
id|uartio_index
)paren
(brace
macro_line|#ifndef MWAVE_FUTZ_WITH_OTHER_DEVICES
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_set_DSP_cfg: IR port base I/O address %x conflicts with mwave uart I/O %x&bslash;n&quot;
comma
id|ausUartBases
(braket
id|usSI
op_amp
l_int|0xff
)braket
comma
id|ausUartBases
(braket
id|uartio_index
)braket
)paren
suffix:semicolon
macro_line|#else
id|PRINTK_3
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_cfg: IR port base I/O address %x conflicts with mwave uart I/O %x&bslash;n&quot;
comma
id|ausUartBases
(braket
id|usSI
op_amp
l_int|0xff
)braket
comma
id|ausUartBases
(braket
id|uartio_index
)braket
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MWAVE_FUTZ_WITH_OTHER_DEVICES
id|PRINTK_1
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_cfg Disabling conflicting IR port&bslash;n&quot;
)paren
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1701
comma
l_int|0x0100
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1700
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1705
comma
l_int|0x01ff
comma
l_int|0
comma
id|usSI
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1704
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
macro_line|#else
r_goto
id|exit_conflict
suffix:semicolon
macro_line|#endif
)brace
)brace
)brace
)brace
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1802
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
r_if
c_cond
(paren
id|mwave_3780i_io
)paren
(brace
id|usDI
op_assign
id|dspio_index
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mwave_3780i_irq
)paren
(brace
id|usSI
op_assign
(paren
id|usSI
op_amp
l_int|0xff00
)paren
op_or
id|mwave_3780i_irq
suffix:semicolon
)brace
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1803
comma
l_int|0x0101
comma
id|usDI
comma
id|usSI
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1804
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
r_if
c_cond
(paren
id|mwave_uart_io
)paren
(brace
id|usSI
op_assign
(paren
id|usSI
op_amp
l_int|0x00ff
)paren
op_or
(paren
id|uartio_index
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mwave_uart_irq
)paren
(brace
id|usSI
op_assign
(paren
id|usSI
op_amp
l_int|0xff00
)paren
op_or
id|mwave_uart_irq
suffix:semicolon
)brace
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1805
comma
l_int|0x0101
comma
l_int|0
comma
id|usSI
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1802
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x1804
comma
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
)paren
r_goto
id|exit_smapi_request_error
suffix:semicolon
multiline_comment|/* normal exit: */
id|PRINTK_1
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_cfg exit&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|exit_conflict
suffix:colon
multiline_comment|/* Message has already been printed */
r_return
op_minus
id|EIO
suffix:semicolon
id|exit_smapi_request_error
suffix:colon
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;smapi::smapi_set_DSP_cfg exit on smapi_request error bRC %x&bslash;n&quot;
comma
id|bRC
)paren
suffix:semicolon
r_return
id|bRC
suffix:semicolon
)brace
DECL|function|smapi_set_DSP_power_state
r_int
id|smapi_set_DSP_power_state
c_func
(paren
id|BOOLEAN
id|bOn
)paren
(brace
r_int
id|bRC
op_assign
op_minus
id|EIO
suffix:semicolon
r_int
r_int
id|usAX
comma
id|usBX
comma
id|usCX
comma
id|usDX
comma
id|usDI
comma
id|usSI
suffix:semicolon
r_int
r_int
id|usPowerFunction
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_power_state entry bOn %x&bslash;n&quot;
comma
id|bOn
)paren
suffix:semicolon
id|usPowerFunction
op_assign
(paren
id|bOn
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x4901
comma
l_int|0x0000
comma
l_int|0
comma
id|usPowerFunction
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_set_DSP_power_state exit bRC %x&bslash;n&quot;
comma
id|bRC
)paren
suffix:semicolon
r_return
id|bRC
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_int
id|SmapiQuerySystemID
c_func
(paren
r_void
)paren
(brace
r_int
id|bRC
op_assign
op_minus
id|EIO
suffix:semicolon
r_int
r_int
id|usAX
op_assign
l_int|0xffff
comma
id|usBX
op_assign
l_int|0xffff
comma
id|usCX
op_assign
l_int|0xffff
comma
id|usDX
op_assign
l_int|0xffff
comma
id|usDI
op_assign
l_int|0xffff
comma
id|usSI
op_assign
l_int|0xffff
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;smapi::SmapiQUerySystemID entry&bslash;n&quot;
)paren
suffix:semicolon
id|bRC
op_assign
id|smapi_request
c_func
(paren
l_int|0x0000
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|usAX
comma
op_amp
id|usBX
comma
op_amp
id|usCX
comma
op_amp
id|usDX
comma
op_amp
id|usDI
comma
op_amp
id|usSI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bRC
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;AX=%x, BX=%x, CX=%x, DX=%x, DI=%x, SI=%x&bslash;n&quot;
comma
id|usAX
comma
id|usBX
comma
id|usCX
comma
id|usDX
comma
id|usDI
comma
id|usSI
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;smapi::SmapiQuerySystemID smapi_request error&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|bRC
suffix:semicolon
)brace
macro_line|#endif  /*  0  */
DECL|function|smapi_init
r_int
id|smapi_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
r_int
r_int
id|usSmapiID
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_init entry&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
id|usSmapiID
op_assign
id|CMOS_READ
c_func
(paren
l_int|0x7C
)paren
suffix:semicolon
id|usSmapiID
op_or_assign
(paren
id|CMOS_READ
c_func
(paren
l_int|0x7D
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_init usSmapiID %x&bslash;n&quot;
comma
id|usSmapiID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usSmapiID
op_eq
l_int|0x5349
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
id|g_usSmapiPort
op_assign
id|CMOS_READ
c_func
(paren
l_int|0x7E
)paren
suffix:semicolon
id|g_usSmapiPort
op_or_assign
(paren
id|CMOS_READ
c_func
(paren
l_int|0x7F
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|g_usSmapiPort
op_eq
l_int|0
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
l_string|&quot;smapi::smapi_init, ERROR unable to read from SMAPI port&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|PRINTK_2
c_func
(paren
id|TRACE_SMAPI
comma
l_string|&quot;smapi::smapi_init, exit TRUE g_usSmapiPort %x&bslash;n&quot;
comma
id|g_usSmapiPort
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
singleline_comment|//SmapiQuerySystemID();
)brace
)brace
r_else
(brace
id|PRINTK_ERROR
c_func
(paren
l_string|&quot;smapi::smapi_init, ERROR invalid usSmapiID&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENXIO
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
eof
