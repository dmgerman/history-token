multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Alchemy Db1x00 board setup.&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/au1000.h&gt;
r_extern
r_struct
id|rtc_ops
id|no_rtc_ops
suffix:semicolon
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
suffix:semicolon
id|rtc_ops
op_assign
op_amp
id|no_rtc_ops
suffix:semicolon
macro_line|#ifdef CONFIG_AU1X00_USB_DEVICE
singleline_comment|// 2nd USB port is USB device
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
id|au_writel
c_func
(paren
id|pin_func
comma
id|SYS_PINFUNC
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_IRDA) &amp;&amp; (defined(CONFIG_SOC_AU1000) || defined(CONFIG_SOC_AU1100))
multiline_comment|/* set IRFIRSEL instead of GPIO15 */
id|pin_func
op_assign
id|au_readl
c_func
(paren
id|SYS_PINFUNC
)paren
op_or
(paren
id|u32
)paren
(paren
(paren
l_int|1
op_lshift
l_int|8
)paren
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
id|au_sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;AMD Alchemy Hydrogen3 Board&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
