multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Alchemy Pb1000 board setup.&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/root_dev.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/au1000.h&gt;
macro_line|#include &lt;asm/pb1500.h&gt;
macro_line|#ifdef CONFIG_USB_OHCI
singleline_comment|// Enable the workaround for the OHCI DoneHead
singleline_comment|// register corruption problem.
DECL|macro|CONFIG_AU1000_OHCI_FIX
mdefine_line|#define CONFIG_AU1000_OHCI_FIX
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_extern
r_int
r_int
id|initrd_start
comma
id|initrd_end
suffix:semicolon
r_extern
r_void
op_star
id|__rd_start
comma
op_star
id|__rd_end
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDE
r_extern
r_struct
id|ide_ops
id|std_ide_ops
suffix:semicolon
r_extern
r_struct
id|ide_ops
op_star
id|ide_ops
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_RTC
r_extern
r_struct
id|rtc_ops
id|pb1500_rtc_ops
suffix:semicolon
macro_line|#endif
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
id|au1x_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__init
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
macro_line|#ifdef CONFIG_64BIT_PHYS_ADDR
r_extern
id|phys_t
(paren
op_star
id|fixup_bigphys_addr
)paren
(paren
id|phys_t
id|phys_addr
comma
id|phys_t
id|size
)paren
suffix:semicolon
r_static
id|phys_t
id|pb1500_fixup_bigphys_addr
c_func
(paren
id|phys_t
id|phys_addr
comma
id|phys_t
id|size
)paren
suffix:semicolon
macro_line|#endif
DECL|function|au1x00_setup
r_void
id|__init
id|au1x00_setup
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|argptr
suffix:semicolon
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
id|argptr
op_assign
id|prom_getcmdline
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* NOTE: The memory map is established by YAMON 2.08+ */
multiline_comment|/* Various early Au1500 Errata corrected by this */
id|set_c0_config
c_func
(paren
l_int|1
op_lshift
l_int|19
)paren
suffix:semicolon
multiline_comment|/* Config[OD] */
id|board_time_init
op_assign
id|au1x_time_init
suffix:semicolon
id|board_timer_setup
op_assign
id|au1x_timer_setup
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
macro_line|#endif
macro_line|#ifdef CONFIG_SOUND_AU1X00
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
macro_line|#ifdef CONFIG_64BIT_PHYS_ADDR
id|fixup_bigphys_addr
op_assign
id|pb1500_fixup_bigphys_addr
suffix:semicolon
macro_line|#endif
singleline_comment|// IO/MEM resources.
id|set_io_port_base
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|ioport_resource.start
op_assign
l_int|0x00000000
suffix:semicolon
id|ioport_resource.end
op_assign
l_int|0xffffffff
suffix:semicolon
id|iomem_resource.start
op_assign
l_int|0x10000000
suffix:semicolon
id|iomem_resource.end
op_assign
l_int|0xffffffff
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|ROOT_DEV
op_assign
id|Root_RAM0
suffix:semicolon
id|initrd_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|__rd_start
suffix:semicolon
id|initrd_end
op_assign
(paren
r_int
r_int
)paren
op_amp
id|__rd_end
suffix:semicolon
macro_line|#endif
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
macro_line|#ifdef CONFIG_USB_OHCI
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
l_string|&quot;usb_ohci=&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
r_char
id|usb_args
(braket
l_int|80
)braket
suffix:semicolon
id|argptr
op_assign
id|prom_getcmdline
c_func
(paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|usb_args
comma
l_int|0
comma
r_sizeof
(paren
id|usb_args
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|usb_args
comma
l_string|&quot; usb_ohci=base:0x%x,len:0x%x,irq:%d&quot;
comma
id|USB_OHCI_BASE
comma
id|USB_OHCI_LEN
comma
id|AU1000_USB_HOST_INT
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|argptr
comma
id|usb_args
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* GPIO201 is input for PCMCIA card detect */
multiline_comment|/* GPIO203 is input for PCMCIA interrupt request */
id|au_writel
c_func
(paren
id|au_readl
c_func
(paren
id|GPIO2_DIR
)paren
op_amp
(paren
id|u32
)paren
(paren
op_complement
(paren
(paren
l_int|1
op_lshift
l_int|1
)paren
op_or
(paren
l_int|1
op_lshift
l_int|3
)paren
)paren
)paren
comma
id|GPIO2_DIR
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
macro_line|#ifdef CONFIG_USB_OHCI
singleline_comment|// enable host controller and wait for reset done
id|au_writel
c_func
(paren
l_int|0x08
comma
id|USB_HOST_CONFIG
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x0c
comma
id|USB_HOST_CONFIG
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
id|au_readl
c_func
(paren
id|USB_HOST_CONFIG
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|au_readl
c_func
(paren
id|USB_HOST_CONFIG
)paren
op_amp
l_int|0x10
)paren
)paren
suffix:semicolon
id|au_readl
c_func
(paren
id|USB_HOST_CONFIG
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FB
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
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
id|strcat
c_func
(paren
id|argptr
comma
l_string|&quot; video=e1356fb:system:pb1500&quot;
)paren
suffix:semicolon
)brace
macro_line|#elif defined (CONFIG_FB_XPERT98)
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
singleline_comment|// CONFIG_FB_E1356
macro_line|#ifndef CONFIG_SERIAL_AU1X00_CONSOLE
multiline_comment|/* don&squot;t touch the default serial console */
id|au_writel
c_func
(paren
l_int|0
comma
id|UART0_ADDR
op_plus
id|UART_CLK
)paren
suffix:semicolon
macro_line|#endif
id|au_writel
c_func
(paren
l_int|0
comma
id|UART3_ADDR
op_plus
id|UART_CLK
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_IDE
id|ide_ops
op_assign
op_amp
id|std_ide_ops
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PCI
singleline_comment|// Setup PCI bus controller
id|au_writel
c_func
(paren
l_int|0
comma
id|Au1500_PCI_CMEM
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x00003fff
comma
id|Au1500_CFG_BASE
)paren
suffix:semicolon
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
id|au_writel
c_func
(paren
l_int|0xf0000000
comma
id|Au1500_PCI_MWMASK_DEV
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0
comma
id|Au1500_PCI_MWBASE_REV_CCL
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x02a00356
comma
id|Au1500_PCI_STATCMD
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x00003c04
comma
id|Au1500_PCI_HDRTYPE
)paren
suffix:semicolon
id|au_writel
c_func
(paren
l_int|0x00000008
comma
id|Au1500_PCI_MBAR
)paren
suffix:semicolon
id|au_sync
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* Enable BCLK switching */
id|au_writel
c_func
(paren
l_int|0x00000060
comma
l_int|0xb190003c
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_RTC
id|rtc_ops
op_assign
op_amp
id|pb1500_rtc_ops
suffix:semicolon
singleline_comment|// Enable the RTC if not already enabled
r_if
c_cond
(paren
op_logical_neg
(paren
id|au_readl
c_func
(paren
l_int|0xac000028
)paren
op_amp
l_int|0x20
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;enabling clock ...&bslash;n&quot;
)paren
suffix:semicolon
id|au_writel
c_func
(paren
(paren
id|au_readl
c_func
(paren
l_int|0xac000028
)paren
op_or
l_int|0x20
)paren
comma
l_int|0xac000028
)paren
suffix:semicolon
)brace
singleline_comment|// Put the clock in BCD mode
r_if
c_cond
(paren
id|readl
c_func
(paren
l_int|0xac00002C
)paren
op_amp
l_int|0x4
)paren
(brace
multiline_comment|/* reg B */
id|au_writel
c_func
(paren
id|au_readl
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
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_64BIT_PHYS_ADDR
DECL|function|pb1500_fixup_bigphys_addr
r_static
id|phys_t
id|pb1500_fixup_bigphys_addr
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
id|pci_start
op_assign
(paren
id|u32
)paren
id|Au1500_PCI_MEM_START
suffix:semicolon
id|u32
id|pci_end
op_assign
(paren
id|u32
)paren
id|Au1500_PCI_MEM_END
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
multiline_comment|/* check for pci memory window */
r_if
c_cond
(paren
(paren
id|phys_addr
op_ge
id|pci_start
)paren
op_logical_and
(paren
(paren
id|phys_addr
op_plus
id|size
)paren
OL
id|pci_end
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
id|pci_start
)paren
op_plus
id|Au1500_PCI_MEM_START
)paren
suffix:semicolon
)brace
r_else
r_return
id|phys_addr
suffix:semicolon
)brace
macro_line|#endif
eof
