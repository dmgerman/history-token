multiline_comment|/*&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
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
macro_line|#include &lt;asm/mach-pb1x00/pb1000.h&gt;
DECL|function|board_reset
r_void
id|board_reset
(paren
r_void
)paren
(brace
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
comma
id|static_cfg0
suffix:semicolon
id|u32
id|sys_freqctrl
comma
id|sys_clksrc
suffix:semicolon
id|u32
id|prid
op_assign
id|read_c0_prid
c_func
(paren
)paren
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
id|SYS_PINSTATERD
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
macro_line|#if defined (CONFIG_USB_OHCI) || defined (CONFIG_AU1X00_USB_DEVICE)
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
multiline_comment|/* zero and disable USBH/USBD clocks */
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
l_int|0x00007FE0
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
l_int|0x00007FE0
suffix:semicolon
r_switch
c_cond
(paren
id|prid
op_amp
l_int|0x000000FF
)paren
(brace
r_case
l_int|0x00
suffix:colon
multiline_comment|/* DA */
r_case
l_int|0x01
suffix:colon
multiline_comment|/* HA */
r_case
l_int|0x02
suffix:colon
multiline_comment|/* HB */
multiline_comment|/* CPU core freq to 48MHz to slow it way down... */
id|au_writel
c_func
(paren
l_int|4
comma
id|SYS_CPUPLL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Setup 48MHz FREQ2 from CPUPLL for USB Host&n;&t; */
multiline_comment|/* FRDIV2=3 -&gt; div by 8 of 384MHz -&gt; 48MHz */
id|sys_freqctrl
op_or_assign
(paren
(paren
l_int|3
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
l_int|0
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
multiline_comment|/* CPU core freq to 384MHz */
id|au_writel
c_func
(paren
l_int|0x20
comma
id|SYS_CPUPLL
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Au1000: 48MHz OHCI workaround enabled&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* HC and newer */
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
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Route 48MHz FREQ2 into USB Host and/or Device&n;&t; */
macro_line|#ifdef CONFIG_USB_OHCI
id|sys_clksrc
op_or_assign
(paren
(paren
l_int|4
op_lshift
l_int|12
)paren
op_or
(paren
l_int|0
op_lshift
l_int|11
)paren
op_or
(paren
l_int|0
op_lshift
l_int|10
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AU1X00_USB_DEVICE
id|sys_clksrc
op_or_assign
(paren
(paren
l_int|4
op_lshift
l_int|7
)paren
op_or
(paren
l_int|0
op_lshift
l_int|6
)paren
op_or
(paren
l_int|0
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
macro_line|#endif
id|au_writel
c_func
(paren
id|sys_clksrc
comma
id|SYS_CLKSRC
)paren
suffix:semicolon
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
l_int|0x8080
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
id|au_writel
c_func
(paren
l_int|0x2800
comma
id|SYS_TRIOUTCLR
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x0030
comma
id|SYS_OUTPUTCLR
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// defined (CONFIG_USB_OHCI) || defined (CONFIG_AU1X00_USB_DEVICE)
singleline_comment|// make gpio 15 an input (for interrupt line)
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
l_int|0x100
)paren
suffix:semicolon
singleline_comment|// we don&squot;t need I2S, so make it available for GPIO[31:29]
id|pin_func
op_or_assign
(paren
l_int|1
op_lshift
l_int|5
)paren
suffix:semicolon
id|au_writel
c_func
(paren
id|pin_func
comma
id|SYS_PINFUNC
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x8000
comma
id|SYS_TRIOUTCLR
)paren
suffix:semicolon
id|static_cfg0
op_assign
id|au_readl
c_func
(paren
id|MEM_STCFG0
)paren
op_amp
(paren
id|u32
)paren
(paren
op_complement
l_int|0xc00
)paren
suffix:semicolon
id|au_writel
c_func
(paren
id|static_cfg0
comma
id|MEM_STCFG0
)paren
suffix:semicolon
singleline_comment|// configure RCE2* for LCD
id|au_writel
c_func
(paren
l_int|0x00000004
comma
id|MEM_STCFG2
)paren
suffix:semicolon
singleline_comment|// MEM_STTIME2
id|au_writel
c_func
(paren
l_int|0x09000000
comma
id|MEM_STTIME2
)paren
suffix:semicolon
singleline_comment|// Set 32-bit base address decoding for RCE2*
id|au_writel
c_func
(paren
l_int|0x10003ff0
comma
id|MEM_STADDR2
)paren
suffix:semicolon
singleline_comment|// PCI CPLD setup
singleline_comment|// expand CE0 to cover PCI
id|au_writel
c_func
(paren
l_int|0x11803e40
comma
id|MEM_STADDR1
)paren
suffix:semicolon
singleline_comment|// burst visibility on
id|au_writel
c_func
(paren
id|au_readl
c_func
(paren
id|MEM_STCFG0
)paren
op_or
l_int|0x1000
comma
id|MEM_STCFG0
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x83
comma
id|MEM_STCFG1
)paren
suffix:semicolon
singleline_comment|// ewait enabled, flash timing
id|au_writel
c_func
(paren
l_int|0x33030a10
comma
id|MEM_STTIME1
)paren
suffix:semicolon
singleline_comment|// slower timing for FPGA
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
macro_line|#ifdef CONFIG_PCI
id|au_writel
c_func
(paren
l_int|0
comma
id|PCI_BRIDGE_CONFIG
)paren
suffix:semicolon
singleline_comment|// set extend byte to 0
id|au_writel
c_func
(paren
l_int|0
comma
id|SDRAM_MBAR
)paren
suffix:semicolon
singleline_comment|// set mbar to 0
id|au_writel
c_func
(paren
l_int|0x2
comma
id|SDRAM_CMD
)paren
suffix:semicolon
singleline_comment|// enable memory accesses
id|au_sync_delay
c_func
(paren
l_int|1
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Enable Au1000 BCLK switching - note: sed1356 must not use&n;&t; * its BCLK (Au1000 LCLK) for any timings */
r_switch
c_cond
(paren
id|prid
op_amp
l_int|0x000000FF
)paren
(brace
r_case
l_int|0x00
suffix:colon
multiline_comment|/* DA */
r_case
l_int|0x01
suffix:colon
multiline_comment|/* HA */
r_case
l_int|0x02
suffix:colon
multiline_comment|/* HB */
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* HC and newer */
multiline_comment|/* Enable sys bus clock divider when IDLE state or no bus &n;&t;&t;   activity. */
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
r_break
suffix:semicolon
)brace
)brace
eof
