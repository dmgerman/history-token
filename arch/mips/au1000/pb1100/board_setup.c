multiline_comment|/*&n; * Copyright 2002 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
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
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/au1000.h&gt;
macro_line|#include &lt;asm/pb1100.h&gt;
macro_line|#ifdef CONFIG_USB_OHCI
singleline_comment|// Enable the workaround for the OHCI DoneHead
singleline_comment|// register corruption problem.
DECL|macro|CONFIG_AU1000_OHCI_FIX
mdefine_line|#define CONFIG_AU1000_OHCI_FIX
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_xor
op_logical_neg
op_logical_neg
op_logical_neg
id|I
id|shall
op_logical_neg
id|define
id|symbols
id|starting
id|with
id|CONFIG_
op_logical_neg
op_logical_neg
op_logical_neg
macro_line|#endif
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
id|u32
id|sys_freqctrl
comma
id|sys_clksrc
suffix:semicolon
singleline_comment|// set AUX clock to 12MHz * 8 = 96 MHz
id|au_writel
c_func
(paren
l_int|8
comma
id|SYS_AUXPLL
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0
comma
id|SYS_PININPUTEN
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
macro_line|#if defined (CONFIG_USB_OHCI) || defined (CONFIG_AU1X00_USB_DEVICE)
singleline_comment|// configure pins GPIO[14:9] as GPIO
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
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* zero and disable FREQ2 */
id|sys_freqctrl
op_assign
id|au_readl
c_func
(paren
id|SYS_FREQCTRL0
)paren
suffix:semicolon
id|sys_freqctrl
op_and_assign
op_complement
l_int|0xFFF00000
suffix:semicolon
id|au_writel
c_func
(paren
id|sys_freqctrl
comma
id|SYS_FREQCTRL0
)paren
suffix:semicolon
multiline_comment|/* zero and disable USBH/USBD/IrDA clock */
id|sys_clksrc
op_assign
id|au_readl
c_func
(paren
id|SYS_CLKSRC
)paren
suffix:semicolon
id|sys_clksrc
op_and_assign
op_complement
l_int|0x0000001F
suffix:semicolon
id|au_writel
c_func
(paren
id|sys_clksrc
comma
id|SYS_CLKSRC
)paren
suffix:semicolon
id|sys_freqctrl
op_assign
id|au_readl
c_func
(paren
id|SYS_FREQCTRL0
)paren
suffix:semicolon
id|sys_freqctrl
op_and_assign
op_complement
l_int|0xFFF00000
suffix:semicolon
id|sys_clksrc
op_assign
id|au_readl
c_func
(paren
id|SYS_CLKSRC
)paren
suffix:semicolon
id|sys_clksrc
op_and_assign
op_complement
l_int|0x0000001F
suffix:semicolon
singleline_comment|// FREQ2 = aux/2 = 48 MHz
id|sys_freqctrl
op_or_assign
(paren
(paren
l_int|0
op_lshift
l_int|22
)paren
op_or
(paren
l_int|1
op_lshift
l_int|21
)paren
op_or
(paren
l_int|1
op_lshift
l_int|20
)paren
)paren
suffix:semicolon
id|au_writel
c_func
(paren
id|sys_freqctrl
comma
id|SYS_FREQCTRL0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Route 48MHz FREQ2 into USBH/USBD/IrDA&n;&t; */
id|sys_clksrc
op_or_assign
(paren
(paren
l_int|4
op_lshift
l_int|2
)paren
op_or
(paren
l_int|0
op_lshift
l_int|1
)paren
op_or
l_int|0
)paren
suffix:semicolon
id|au_writel
c_func
(paren
id|sys_clksrc
comma
id|SYS_CLKSRC
)paren
suffix:semicolon
multiline_comment|/* setup the static bus controller */
id|au_writel
c_func
(paren
l_int|0x00000002
comma
id|MEM_STCFG3
)paren
suffix:semicolon
multiline_comment|/* type = PCMCIA */
id|au_writel
c_func
(paren
l_int|0x280E3D07
comma
id|MEM_STTIME3
)paren
suffix:semicolon
multiline_comment|/* 250ns cycle time */
id|au_writel
c_func
(paren
l_int|0x10000000
comma
id|MEM_STADDR3
)paren
suffix:semicolon
multiline_comment|/* any PCMCIA select */
singleline_comment|// get USB Functionality pin state (device vs host drive pins)
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
l_int|0x8000
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_AU1X00_USB_DEVICE
singleline_comment|// 2nd USB port is USB host
id|pin_func
op_or_assign
l_int|0x8000
suffix:semicolon
macro_line|#endif
id|au_writel
c_func
(paren
id|pin_func
comma
id|SYS_PINFUNC
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// defined (CONFIG_USB_OHCI) || defined (CONFIG_AU1X00_USB_DEVICE)
multiline_comment|/* Enable sys bus clock divider when IDLE state or no bus activity. */
id|au_writel
c_func
(paren
id|au_readl
c_func
(paren
id|SYS_POWERCTRL
)paren
op_or
(paren
l_int|0x3
op_lshift
l_int|5
)paren
comma
id|SYS_POWERCTRL
)paren
suffix:semicolon
singleline_comment|// Enable the RTC if not already enabled
r_if
c_cond
(paren
op_logical_neg
(paren
id|readb
c_func
(paren
l_int|0xac000028
)paren
op_amp
l_int|0x20
)paren
)paren
(brace
id|writeb
c_func
(paren
id|readb
c_func
(paren
l_int|0xac000028
)paren
op_or
l_int|0x20
comma
l_int|0xac000028
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
)brace
singleline_comment|// Put the clock in BCD mode
r_if
c_cond
(paren
id|readb
c_func
(paren
l_int|0xac00002C
)paren
op_amp
l_int|0x4
)paren
(brace
multiline_comment|/* reg B */
id|writeb
c_func
(paren
id|readb
c_func
(paren
l_int|0xac00002c
)paren
op_amp
op_complement
l_int|0x4
comma
l_int|0xac00002c
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
eof
