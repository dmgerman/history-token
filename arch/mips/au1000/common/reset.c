multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Au1000 reset routines.&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/mach-au1x00/au1000.h&gt;
r_extern
r_int
id|au_sleep
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|flush_cache_all
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|function|au1000_restart
r_void
id|au1000_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
multiline_comment|/* Set all integrated peripherals to disabled states */
r_extern
r_void
id|board_reset
(paren
r_void
)paren
suffix:semicolon
id|u32
id|prid
op_assign
id|read_c0_prid
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;&bslash;n** Resetting Integrated Peripherals&bslash;n&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|prid
op_amp
l_int|0xFF000000
)paren
(brace
r_case
l_int|0x00000000
suffix:colon
multiline_comment|/* Au1000 */
id|au_writel
c_func
(paren
l_int|0x02
comma
l_int|0xb0000010
)paren
suffix:semicolon
multiline_comment|/* ac97_enable */
id|au_writel
c_func
(paren
l_int|0x08
comma
l_int|0xb017fffc
)paren
suffix:semicolon
multiline_comment|/* usbh_enable - early errata */
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb017fffc
)paren
suffix:semicolon
multiline_comment|/* usbh_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb0200058
)paren
suffix:semicolon
multiline_comment|/* usbd_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb0300040
)paren
suffix:semicolon
multiline_comment|/* ir_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004104
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004114
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004124
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004134
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb0520000
)paren
suffix:semicolon
multiline_comment|/* macen0 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb0520004
)paren
suffix:semicolon
multiline_comment|/* macen1 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1000008
)paren
suffix:semicolon
multiline_comment|/* i2s_enable  */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1100100
)paren
suffix:semicolon
multiline_comment|/* uart0_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1200100
)paren
suffix:semicolon
multiline_comment|/* uart1_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1300100
)paren
suffix:semicolon
multiline_comment|/* uart2_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1400100
)paren
suffix:semicolon
multiline_comment|/* uart3_enable */
id|au_writel
c_func
(paren
l_int|0x02
comma
l_int|0xb1600100
)paren
suffix:semicolon
multiline_comment|/* ssi0_enable */
id|au_writel
c_func
(paren
l_int|0x02
comma
l_int|0xb1680100
)paren
suffix:semicolon
multiline_comment|/* ssi1_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900020
)paren
suffix:semicolon
multiline_comment|/* sys_freqctrl0 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900024
)paren
suffix:semicolon
multiline_comment|/* sys_freqctrl1 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900028
)paren
suffix:semicolon
multiline_comment|/* sys_clksrc */
id|au_writel
c_func
(paren
l_int|0x10
comma
l_int|0xb1900060
)paren
suffix:semicolon
multiline_comment|/* sys_cpupll */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900064
)paren
suffix:semicolon
multiline_comment|/* sys_auxpll */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900100
)paren
suffix:semicolon
multiline_comment|/* sys_pininputen */
r_break
suffix:semicolon
r_case
l_int|0x01000000
suffix:colon
multiline_comment|/* Au1500 */
id|au_writel
c_func
(paren
l_int|0x02
comma
l_int|0xb0000010
)paren
suffix:semicolon
multiline_comment|/* ac97_enable */
id|au_writel
c_func
(paren
l_int|0x08
comma
l_int|0xb017fffc
)paren
suffix:semicolon
multiline_comment|/* usbh_enable - early errata */
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb017fffc
)paren
suffix:semicolon
multiline_comment|/* usbh_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb0200058
)paren
suffix:semicolon
multiline_comment|/* usbd_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004104
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004114
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004124
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004134
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1520000
)paren
suffix:semicolon
multiline_comment|/* macen0 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1520004
)paren
suffix:semicolon
multiline_comment|/* macen1 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1100100
)paren
suffix:semicolon
multiline_comment|/* uart0_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1400100
)paren
suffix:semicolon
multiline_comment|/* uart3_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900020
)paren
suffix:semicolon
multiline_comment|/* sys_freqctrl0 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900024
)paren
suffix:semicolon
multiline_comment|/* sys_freqctrl1 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900028
)paren
suffix:semicolon
multiline_comment|/* sys_clksrc */
id|au_writel
c_func
(paren
l_int|0x10
comma
l_int|0xb1900060
)paren
suffix:semicolon
multiline_comment|/* sys_cpupll */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900064
)paren
suffix:semicolon
multiline_comment|/* sys_auxpll */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900100
)paren
suffix:semicolon
multiline_comment|/* sys_pininputen */
r_break
suffix:semicolon
r_case
l_int|0x02000000
suffix:colon
multiline_comment|/* Au1100 */
id|au_writel
c_func
(paren
l_int|0x02
comma
l_int|0xb0000010
)paren
suffix:semicolon
multiline_comment|/* ac97_enable */
id|au_writel
c_func
(paren
l_int|0x08
comma
l_int|0xb017fffc
)paren
suffix:semicolon
multiline_comment|/* usbh_enable - early errata */
id|asm
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb017fffc
)paren
suffix:semicolon
multiline_comment|/* usbh_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb0200058
)paren
suffix:semicolon
multiline_comment|/* usbd_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb0300040
)paren
suffix:semicolon
multiline_comment|/* ir_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004104
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004114
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004124
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004134
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb0520000
)paren
suffix:semicolon
multiline_comment|/* macen0 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1000008
)paren
suffix:semicolon
multiline_comment|/* i2s_enable  */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1100100
)paren
suffix:semicolon
multiline_comment|/* uart0_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1200100
)paren
suffix:semicolon
multiline_comment|/* uart1_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1400100
)paren
suffix:semicolon
multiline_comment|/* uart3_enable */
id|au_writel
c_func
(paren
l_int|0x02
comma
l_int|0xb1600100
)paren
suffix:semicolon
multiline_comment|/* ssi0_enable */
id|au_writel
c_func
(paren
l_int|0x02
comma
l_int|0xb1680100
)paren
suffix:semicolon
multiline_comment|/* ssi1_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900020
)paren
suffix:semicolon
multiline_comment|/* sys_freqctrl0 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900024
)paren
suffix:semicolon
multiline_comment|/* sys_freqctrl1 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900028
)paren
suffix:semicolon
multiline_comment|/* sys_clksrc */
id|au_writel
c_func
(paren
l_int|0x10
comma
l_int|0xb1900060
)paren
suffix:semicolon
multiline_comment|/* sys_cpupll */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900064
)paren
suffix:semicolon
multiline_comment|/* sys_auxpll */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900100
)paren
suffix:semicolon
multiline_comment|/* sys_pininputen */
r_break
suffix:semicolon
r_case
l_int|0x03000000
suffix:colon
multiline_comment|/* Au1550 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1a00004
)paren
suffix:semicolon
multiline_comment|/* psc 0 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1b00004
)paren
suffix:semicolon
multiline_comment|/* psc 1 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb0a00004
)paren
suffix:semicolon
multiline_comment|/* psc 2 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb0b00004
)paren
suffix:semicolon
multiline_comment|/* psc 3 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb017fffc
)paren
suffix:semicolon
multiline_comment|/* usbh_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb0200058
)paren
suffix:semicolon
multiline_comment|/* usbd_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004104
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004114
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004124
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb4004134
)paren
suffix:semicolon
multiline_comment|/* mac dma */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1520000
)paren
suffix:semicolon
multiline_comment|/* macen0 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1520004
)paren
suffix:semicolon
multiline_comment|/* macen1 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1100100
)paren
suffix:semicolon
multiline_comment|/* uart0_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1200100
)paren
suffix:semicolon
multiline_comment|/* uart1_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1400100
)paren
suffix:semicolon
multiline_comment|/* uart3_enable */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900020
)paren
suffix:semicolon
multiline_comment|/* sys_freqctrl0 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900024
)paren
suffix:semicolon
multiline_comment|/* sys_freqctrl1 */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900028
)paren
suffix:semicolon
multiline_comment|/* sys_clksrc */
id|au_writel
c_func
(paren
l_int|0x10
comma
l_int|0xb1900060
)paren
suffix:semicolon
multiline_comment|/* sys_cpupll */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900064
)paren
suffix:semicolon
multiline_comment|/* sys_auxpll */
id|au_writel
c_func
(paren
l_int|0x00
comma
l_int|0xb1900100
)paren
suffix:semicolon
multiline_comment|/* sys_pininputen */
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|set_c0_status
c_func
(paren
id|ST0_BEV
op_or
id|ST0_ERL
)paren
suffix:semicolon
id|set_c0_config
c_func
(paren
id|CONF_CM_UNCACHED
)paren
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|write_c0_wired
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Give board a chance to do a hardware reset */
id|board_reset
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Jump to the beggining in case board_reset() is empty */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;jr&bslash;t%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
l_int|0xbfc00000
)paren
)paren
suffix:semicolon
)brace
DECL|function|au1000_halt
r_void
id|au1000_halt
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_MIPS_PB1550)
multiline_comment|/* power off system */
id|printk
c_func
(paren
l_string|&quot;&bslash;n** Powering off Pb1550&bslash;n&quot;
)paren
suffix:semicolon
id|au_writew
c_func
(paren
id|au_readw
c_func
(paren
l_int|0xAF00001C
)paren
op_or
(paren
l_int|3
op_lshift
l_int|14
)paren
comma
l_int|0xAF00001C
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* should not get here */
macro_line|#endif
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;&bslash;n** You can safely turn off the power&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MIPS_MIRAGE
id|au_writel
c_func
(paren
(paren
l_int|1
op_lshift
l_int|26
)paren
op_or
(paren
l_int|1
op_lshift
l_int|10
)paren
comma
id|GPIO2_OUTPUT
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PM
id|au_sleep
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* should not get here */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Unable to put cpu in sleep mode&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
macro_line|#else
r_while
c_loop
(paren
l_int|1
)paren
id|__asm__
c_func
(paren
l_string|&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;
l_string|&quot;wait&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips0&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|au1000_power_off
r_void
id|au1000_power_off
c_func
(paren
r_void
)paren
(brace
id|au1000_halt
c_func
(paren
)paren
suffix:semicolon
)brace
eof
