multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Alchemy Db1000 board setup.&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
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
macro_line|#include &lt;asm/db1x00.h&gt;
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
r_extern
r_struct
id|rtc_ops
id|no_rtc_ops
suffix:semicolon
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
macro_line|#if defined(CONFIG_64BIT_PHYS_ADDR) &amp;&amp; defined(CONFIG_SOC_AU1500)
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
id|db_fixup_bigphys_addr
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
id|u32
id|prid
op_assign
id|read_c0_prid
c_func
(paren
)paren
suffix:semicolon
id|argptr
op_assign
id|prom_getcmdline
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Various early Au1000 Errata corrected by this */
id|set_c0_config
c_func
(paren
l_int|1
op_lshift
l_int|19
)paren
suffix:semicolon
multiline_comment|/* Config[OD] */
macro_line|#ifdef CONFIG_AU1X00_SERIAL_CONSOLE
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
singleline_comment|//strcat(argptr, &quot; video=au1100fb:panel:Sharp_320x240_16&quot;);
id|strcat
c_func
(paren
id|argptr
comma
l_string|&quot; video=au1100fb:panel:s10,nohwcursor&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_SOUND_AU1X00) &amp;&amp; !defined(CONFIG_SOC_AU1000)
singleline_comment|// au1000 does not support vra, au1500 and au1100 do
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
id|rtc_ops
op_assign
op_amp
id|no_rtc_ops
suffix:semicolon
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
macro_line|#if defined(CONFIG_64BIT_PHYS_ADDR) &amp;&amp; defined(CONFIG_SOC_AU1500)
id|fixup_bigphys_addr
op_assign
id|db_fixup_bigphys_addr
suffix:semicolon
macro_line|#endif
singleline_comment|// IO/MEM resources. 
id|set_io_port_base
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SOC_AU1500
id|ioport_resource.start
op_assign
l_int|0x00000000
suffix:semicolon
macro_line|#else
multiline_comment|/* don&squot;t allow any legacy ports probing */
id|ioport_resource.start
op_assign
l_int|0x10000000
suffix:semicolon
macro_line|#endif
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
id|MKDEV
c_func
(paren
id|RAMDISK_MAJOR
comma
l_int|0
)paren
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
singleline_comment|//
singleline_comment|// NOTE:
singleline_comment|//
singleline_comment|// YAMON (specifically reset_db1500.s) enables 32khz osc
singleline_comment|// YAMON (specifically reset_db1x00.s) setups all clocking and GPIOs
singleline_comment|// YAMON (specifically reset_db1500.s) setups all PCI
singleline_comment|//
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
l_int|0x0E
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
singleline_comment|// throw away first read
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
id|au_readl
c_func
(paren
id|USB_HOST_CONFIG
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#endif 
singleline_comment|// defined (CONFIG_USB_OHCI) || defined (CONFIG_AU1X00_USB_DEVICE)
macro_line|#ifdef CONFIG_FB
singleline_comment|// Needed if PCI video card in use
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
macro_line|#ifndef CONFIG_SERIAL_NONSTANDARD
multiline_comment|/* don&squot;t touch the default serial console */
id|au_writel
c_func
(paren
l_int|0
comma
id|UART_ADDR
op_plus
id|UART_CLK
)paren
suffix:semicolon
macro_line|#endif
singleline_comment|//au_writel(0, UART3_ADDR + UART_CLK);
macro_line|#ifdef CONFIG_BLK_DEV_IDE
id|ide_ops
op_assign
op_amp
id|std_ide_ops
suffix:semicolon
macro_line|#endif
macro_line|#if 0
singleline_comment|//// FIX!!! must be valid for au1000, au1500 and au1100
multiline_comment|/* Enable Au1000 BCLK switching */
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
id|au_writel
c_func
(paren
l_int|0x00000060
comma
l_int|0xb190003c
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
id|au_writel
c_func
(paren
l_int|0
comma
l_int|0xAE000010
)paren
suffix:semicolon
multiline_comment|/* turn off pcmcia power */
macro_line|#ifdef CONFIG_MIPS_DB1000
id|printk
c_func
(paren
l_string|&quot;AMD Alchemy Au1000/Db1000 Board&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_DB1500
id|printk
c_func
(paren
l_string|&quot;AMD Alchemy Au1500/Db1500 Board&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_DB1100
id|printk
c_func
(paren
l_string|&quot;AMD Alchemy Au1100/Db1100 Board&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#if defined(CONFIG_64BIT_PHYS_ADDR) &amp;&amp; defined(CONFIG_SOC_AU1500)
DECL|function|db_fixup_bigphys_addr
r_static
id|phys_t
id|db_fixup_bigphys_addr
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
