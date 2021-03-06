multiline_comment|/*&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; * Updates to 2.6, Pete Popov, Embedded Alley Solutions, Inc.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mach-au1x00/au1000.h&gt;
macro_line|#include &lt;asm/time.h&gt;
r_extern
r_char
op_star
id|__init
id|prom_getcmdline
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|board_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|au1000_restart
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|au1000_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|au1000_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|resource
id|ioport_resource
suffix:semicolon
r_extern
r_struct
id|resource
id|iomem_resource
suffix:semicolon
r_extern
r_void
(paren
op_star
id|board_time_init
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|au1x_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|board_timer_setup
)paren
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|au1x_timer_setup
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|au1xxx_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|au1xxx_timer_setup
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
suffix:semicolon
r_extern
r_void
id|set_cpuspec
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|au1x00_setup
r_static
r_int
id|__init
id|au1x00_setup
c_func
(paren
r_void
)paren
(brace
r_struct
id|cpu_spec
op_star
id|sp
suffix:semicolon
r_char
op_star
id|argptr
suffix:semicolon
r_int
r_int
id|prid
comma
id|cpupll
comma
id|bclk
op_assign
l_int|1
suffix:semicolon
id|set_cpuspec
c_func
(paren
)paren
suffix:semicolon
id|sp
op_assign
id|cur_cpu_spec
(braket
l_int|0
)braket
suffix:semicolon
id|board_setup
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* board specific setup */
id|prid
op_assign
id|read_c0_prid
c_func
(paren
)paren
suffix:semicolon
id|cpupll
op_assign
(paren
id|au_readl
c_func
(paren
l_int|0xB1900060
)paren
op_amp
l_int|0x3F
)paren
op_star
l_int|12
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;(PRId %08lx) @ %ldMHZ&bslash;n&quot;
comma
id|prid
comma
id|cpupll
)paren
suffix:semicolon
id|bclk
op_assign
id|sp-&gt;cpu_bclk
suffix:semicolon
r_if
c_cond
(paren
id|bclk
)paren
(brace
multiline_comment|/* Enable BCLK switching */
id|bclk
op_assign
id|au_readl
c_func
(paren
l_int|0xB190003C
)paren
suffix:semicolon
id|au_writel
c_func
(paren
id|bclk
op_or
l_int|0x60
comma
l_int|0xB190003C
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;BCLK switching enabled!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sp-&gt;cpu_od
)paren
(brace
multiline_comment|/* Various early Au1000 Errata corrected by this */
id|set_c0_config
c_func
(paren
l_int|1
op_lshift
l_int|19
)paren
suffix:semicolon
multiline_comment|/* Set Config[OD] */
)brace
r_else
(brace
multiline_comment|/* Clear to obtain best system bus performance */
id|clear_c0_config
c_func
(paren
l_int|1
op_lshift
l_int|19
)paren
suffix:semicolon
multiline_comment|/* Clear Config[OD] */
)brace
id|argptr
op_assign
id|prom_getcmdline
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_AU1X00_CONSOLE
r_if
c_cond
(paren
(paren
id|argptr
op_assign
id|strstr
c_func
(paren
id|argptr
comma
l_string|&quot;console=&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|argptr
op_assign
id|prom_getcmdline
c_func
(paren
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|argptr
comma
l_string|&quot; console=ttyS0,115200&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif&t;  
macro_line|#ifdef CONFIG_FB_AU1100
r_if
c_cond
(paren
(paren
id|argptr
op_assign
id|strstr
c_func
(paren
id|argptr
comma
l_string|&quot;video=&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|argptr
op_assign
id|prom_getcmdline
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* default panel */
multiline_comment|/*strcat(argptr, &quot; video=au1100fb:panel:Sharp_320x240_16&quot;);*/
macro_line|#ifdef CONFIG_MIPS_HYDROGEN3
id|strcat
c_func
(paren
id|argptr
comma
l_string|&quot; video=au1100fb:panel:Hydrogen_3_NEC_panel_320x240,nohwcursor&quot;
)paren
suffix:semicolon
macro_line|#else
id|strcat
c_func
(paren
id|argptr
comma
l_string|&quot; video=au1100fb:panel:s10,nohwcursor&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_FB_E1356
r_if
c_cond
(paren
(paren
id|argptr
op_assign
id|strstr
c_func
(paren
id|argptr
comma
l_string|&quot;video=&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|argptr
op_assign
id|prom_getcmdline
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MIPS_PB1000
id|strcat
c_func
(paren
id|argptr
comma
l_string|&quot; video=e1356fb:system:pb1000,mmunalign:1&quot;
)paren
suffix:semicolon
macro_line|#else
id|strcat
c_func
(paren
id|argptr
comma
l_string|&quot; video=e1356fb:system:pb1500&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_FB_XPERT98
r_if
c_cond
(paren
(paren
id|argptr
op_assign
id|strstr
c_func
(paren
id|argptr
comma
l_string|&quot;video=&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|argptr
op_assign
id|prom_getcmdline
c_func
(paren
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|argptr
comma
l_string|&quot; video=atyfb:1024x768-8@70&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_SOUND_AU1X00) &amp;&amp; !defined(CONFIG_SOC_AU1000)
multiline_comment|/* au1000 does not support vra, au1500 and au1100 do */
id|strcat
c_func
(paren
id|argptr
comma
l_string|&quot; au1000_audio=vra&quot;
)paren
suffix:semicolon
id|argptr
op_assign
id|prom_getcmdline
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|_machine_restart
op_assign
id|au1000_restart
suffix:semicolon
id|_machine_halt
op_assign
id|au1000_halt
suffix:semicolon
id|_machine_power_off
op_assign
id|au1000_power_off
suffix:semicolon
id|board_time_init
op_assign
id|au1xxx_time_init
suffix:semicolon
id|board_timer_setup
op_assign
id|au1xxx_timer_setup
suffix:semicolon
multiline_comment|/* IO/MEM resources. */
id|set_io_port_base
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|ioport_resource.start
op_assign
id|IOPORT_RESOURCE_START
suffix:semicolon
id|ioport_resource.end
op_assign
id|IOPORT_RESOURCE_END
suffix:semicolon
id|iomem_resource.start
op_assign
id|IOMEM_RESOURCE_START
suffix:semicolon
id|iomem_resource.end
op_assign
id|IOMEM_RESOURCE_END
suffix:semicolon
r_while
c_loop
(paren
id|au_readl
c_func
(paren
id|SYS_COUNTER_CNTRL
)paren
op_amp
id|SYS_CNTRL_E0S
)paren
suffix:semicolon
id|au_writel
c_func
(paren
id|SYS_CNTRL_E0
op_or
id|SYS_CNTRL_EN0
comma
id|SYS_COUNTER_CNTRL
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
id|au_readl
c_func
(paren
id|SYS_COUNTER_CNTRL
)paren
op_amp
id|SYS_CNTRL_T0S
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0
comma
id|SYS_TOYTRIM
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|au1x00_setup
id|early_initcall
c_func
(paren
id|au1x00_setup
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_64BIT_PHYS_ADDR)
multiline_comment|/* This routine should be valid for all Au1x based boards */
DECL|function|fixup_bigphys_addr
id|phys_t
id|fixup_bigphys_addr
c_func
(paren
id|phys_t
id|phys_addr
comma
id|phys_t
id|size
)paren
(brace
id|u32
id|start
comma
id|end
suffix:semicolon
multiline_comment|/* Don&squot;t fixup 36 bit addresses */
r_if
c_cond
(paren
(paren
id|phys_addr
op_rshift
l_int|32
)paren
op_ne
l_int|0
)paren
r_return
id|phys_addr
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
id|start
op_assign
(paren
id|u32
)paren
id|Au1500_PCI_MEM_START
suffix:semicolon
id|end
op_assign
(paren
id|u32
)paren
id|Au1500_PCI_MEM_END
suffix:semicolon
multiline_comment|/* check for pci memory window */
r_if
c_cond
(paren
(paren
id|phys_addr
op_ge
id|start
)paren
op_logical_and
(paren
(paren
id|phys_addr
op_plus
id|size
)paren
OL
id|end
)paren
)paren
(brace
r_return
(paren
id|phys_t
)paren
(paren
(paren
id|phys_addr
op_minus
id|start
)paren
op_plus
id|Au1500_PCI_MEM_START
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* All Au1x SOCs have a pcmcia controller */
multiline_comment|/* We setup our 32 bit pseudo addresses to be equal to the&n;&t; * 36 bit addr &gt;&gt; 4, to make it easier to check the address&n;&t; * and fix it.&n;&t; * The Au1x socket 0 phys attribute address is 0xF 4000 0000.&n;&t; * The pseudo address we use is 0xF400 0000. Any address over&n;&t; * 0xF400 0000 is a pcmcia pseudo address.&n;&t; */
r_if
c_cond
(paren
(paren
id|phys_addr
op_ge
l_int|0xF4000000
)paren
op_logical_and
(paren
id|phys_addr
OL
l_int|0xFFFFFFFF
)paren
)paren
(brace
r_return
(paren
id|phys_t
)paren
(paren
id|phys_addr
op_lshift
l_int|4
)paren
suffix:semicolon
)brace
multiline_comment|/* default nop */
r_return
id|phys_addr
suffix:semicolon
)brace
macro_line|#endif
eof
