multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;4G Systems MTX-1 board setup.&n; *&n; * Copyright 2003 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *         Bruno Randolf &lt;bruno.randolf@4g-systems.biz&gt;&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
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
macro_line|#include &lt;asm/mach-au1x00/au1000.h&gt;
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
macro_line|#if defined (CONFIG_USB_OHCI) || defined (CONFIG_AU1X00_USB_DEVICE)
macro_line|#ifdef CONFIG_AU1X00_USB_DEVICE
singleline_comment|// 2nd USB port is USB device
id|au_writel
c_func
(paren
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
comma
id|SYS_PINFUNC
)paren
suffix:semicolon
macro_line|#endif
singleline_comment|// enable USB power switch
id|au_writel
c_func
(paren
id|au_readl
c_func
(paren
id|GPIO2_DIR
)paren
op_or
l_int|0x10
comma
id|GPIO2_DIR
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x100000
comma
id|GPIO2_OUTPUT
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// defined (CONFIG_USB_OHCI) || defined (CONFIG_AU1X00_USB_DEVICE)
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
singleline_comment|// initialize sys_pinfunc:
singleline_comment|// disable second ethernet port (SYS_PF_NI2)
singleline_comment|// set U3/GPIO23 to GPIO23 (SYS_PF_U3)
id|au_writel
c_func
(paren
id|SYS_PF_NI2
op_or
id|SYS_PF_U3
comma
id|SYS_PINFUNC
)paren
suffix:semicolon
singleline_comment|// initialize GPIO
id|au_writel
c_func
(paren
l_int|0xFFFFFFFF
comma
id|SYS_TRIOUTCLR
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x00000001
comma
id|SYS_OUTPUTCLR
)paren
suffix:semicolon
singleline_comment|// set M66EN (PCI 66MHz) to OFF
id|au_writel
c_func
(paren
l_int|0x00000008
comma
id|SYS_OUTPUTSET
)paren
suffix:semicolon
singleline_comment|// set PCI CLKRUN# to OFF
id|au_writel
c_func
(paren
l_int|0x00000020
comma
id|SYS_OUTPUTCLR
)paren
suffix:semicolon
singleline_comment|// set eth PHY TX_ER to OFF
singleline_comment|// enable LED and set it to green
id|au_writel
c_func
(paren
id|au_readl
c_func
(paren
id|GPIO2_DIR
)paren
op_or
l_int|0x1800
comma
id|GPIO2_DIR
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x18000800
comma
id|GPIO2_OUTPUT
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;4G Systems MTX-1 Board&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
