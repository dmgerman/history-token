multiline_comment|/*&n; * Copyright 2000-2003 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/au1000.h&gt;
DECL|function|board_reset
r_void
id|board_reset
(paren
r_void
)paren
(brace
multiline_comment|/* Hit BCSR.SYSTEM_CONTROL[SW_RST] */
id|au_writel
c_func
(paren
l_int|0x00000000
comma
l_int|0xAE00001C
)paren
suffix:semicolon
)brace
DECL|function|board_setup
r_void
id|__init
id|board_setup
c_func
(paren
r_void
)paren
(brace
id|u32
id|pin_func
suffix:semicolon
singleline_comment|// set multiple use pins (UART3/GPIO) to UART (it&squot;s used as UART too)
id|pin_func
op_assign
id|au_readl
c_func
(paren
id|SYS_PINFUNC
)paren
op_amp
(paren
id|u32
)paren
(paren
op_complement
id|SYS_PF_UR3
)paren
suffix:semicolon
id|pin_func
op_or_assign
id|SYS_PF_UR3
suffix:semicolon
id|au_writel
c_func
(paren
id|pin_func
comma
id|SYS_PINFUNC
)paren
suffix:semicolon
singleline_comment|// enable UART
id|au_writel
c_func
(paren
l_int|0x01
comma
id|UART3_ADDR
op_plus
id|UART_MOD_CNTRL
)paren
suffix:semicolon
singleline_comment|// clock enable (CE)
id|mdelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x03
comma
id|UART3_ADDR
op_plus
id|UART_MOD_CNTRL
)paren
suffix:semicolon
singleline_comment|// CE and &quot;enable&quot;
id|mdelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
singleline_comment|// enable DTR = USB power up
id|au_writel
c_func
(paren
l_int|0x01
comma
id|UART3_ADDR
op_plus
id|UART_MCR
)paren
suffix:semicolon
singleline_comment|//? UART_MCR_DTR is 0x01???
macro_line|#ifdef CONFIG_PCMCIA_XXS1500
multiline_comment|/* setup pcmcia signals */
id|au_writel
c_func
(paren
l_int|0
comma
id|SYS_PININPUTEN
)paren
suffix:semicolon
multiline_comment|/* gpio 0, 1, and 4 are inputs */
id|au_writel
c_func
(paren
l_int|1
op_or
(paren
l_int|1
op_lshift
l_int|1
)paren
op_or
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
id|SYS_TRIOUTCLR
)paren
suffix:semicolon
multiline_comment|/* enable GPIO2 if not already enabled */
id|au_writel
c_func
(paren
l_int|1
comma
id|GPIO2_ENABLE
)paren
suffix:semicolon
multiline_comment|/* gpio2 208/9/10/11 are inputs */
id|au_writel
c_func
(paren
(paren
l_int|1
op_lshift
l_int|8
)paren
op_or
(paren
l_int|1
op_lshift
l_int|9
)paren
op_or
(paren
l_int|1
op_lshift
l_int|10
)paren
op_or
(paren
l_int|1
op_lshift
l_int|11
)paren
comma
id|GPIO2_DIR
)paren
suffix:semicolon
multiline_comment|/* turn off power */
id|au_writel
c_func
(paren
(paren
id|au_readl
c_func
(paren
id|GPIO2_PINSTATE
)paren
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|14
)paren
)paren
op_or
(paren
l_int|1
op_lshift
l_int|30
)paren
comma
id|GPIO2_OUTPUT
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PCI
macro_line|#if defined(__MIPSEB__)
id|au_writel
c_func
(paren
l_int|0xf
op_or
(paren
l_int|2
op_lshift
l_int|6
)paren
op_or
(paren
l_int|1
op_lshift
l_int|4
)paren
comma
id|Au1500_PCI_CFG
)paren
suffix:semicolon
macro_line|#else
id|au_writel
c_func
(paren
l_int|0xf
comma
id|Au1500_PCI_CFG
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
)brace
eof
