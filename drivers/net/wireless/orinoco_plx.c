multiline_comment|/* orinoco_plx.c&n; *&n; * Driver for Prism II devices which would usually be driven by orinoco_cs,&n; * but are connected to the PCI bus by a PLX9052.&n; *&n; * Current maintainers (as of 29 September 2003) are:&n; * &t;Pavel Roskin &lt;proski AT gnu.org&gt;&n; * and&t;David Gibson &lt;hermes AT gibson.dropbear.id.au&gt;&n; *&n; * (C) Copyright David Gibson, IBM Corp. 2001-2003.&n; * Copyright (C) 2001 Daniel Barlow&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in&n; * which case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use your&n; * version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n;&n; * Caution: this is experimental and probably buggy.  For success and&n; * failure reports for different cards and adaptors, see&n; * orinoco_plx_pci_id_table near the end of the file.  If you have a&n; * card we don&squot;t have the PCI id for, and looks like it should work,&n; * drop me mail with the id and &quot;it works&quot;/&quot;it doesn&squot;t work&quot;.&n; *&n; * Note: if everything gets detected fine but it doesn&squot;t actually send&n; * or receive packets, your first port of call should probably be to&n; * try newer firmware in the card.  Especially if you&squot;re doing Ad-Hoc&n; * modes.&n; *&n; * The actual driving is done by orinoco.c, this is just resource&n; * allocation stuff.  The explanation below is courtesy of Ryan Niemi&n; * on the linux-wlan-ng list at&n; * http://archives.neohapsis.com/archives/dev/linux-wlan/2001-q1/0026.html&n; *&n; * The PLX9052-based cards (WL11000 and several others) are a&n; * different beast than the usual PCMCIA-based PRISM2 configuration&n; * expected by wlan-ng.  Here&squot;s the general details on how the WL11000&n; * PCI adapter works:&n; *&n; * - Two PCI I/O address spaces, one 0x80 long which contains the&n; * PLX9052 registers, and one that&squot;s 0x40 long mapped to the PCMCIA&n; * slot I/O address space.&n; *&n; * - One PCI memory address space, mapped to the PCMCIA memory space&n; * (containing the CIS).&n; *&n; * After identifying the I/O and memory space, you can read through&n; * the memory space to confirm the CIS&squot;s device ID or manufacturer ID&n; * to make sure it&squot;s the expected card.  qKeep in mind that the PCMCIA&n; * spec specifies the CIS as the lower 8 bits of each word read from&n; * the CIS, so to read the bytes of the CIS, read every other byte&n; * (0,2,4,...). Passing that test, you need to enable the I/O address&n; * space on the PCMCIA card via the PCMCIA COR register. This is the&n; * first byte following the CIS. In my case (which may not have any&n; * relation to what&squot;s on the PRISM2 cards), COR was at offset 0x800&n; * within the PCI memory space. Write 0x41 to the COR register to&n; * enable I/O mode and to select level triggered interrupts. To&n; * confirm you actually succeeded, read the COR register back and make&n; * sure it actually got set to 0x41, incase you have an unexpected&n; * card inserted.&n; *&n; * Following that, you can treat the second PCI I/O address space (the&n; * one that&squot;s not 0x80 in length) as the PCMCIA I/O space.&n; *&n; * Note that in the Eumitcom&squot;s source for their drivers, they register&n; * the interrupt as edge triggered when registering it with the&n; * Windows kernel. I don&squot;t recall how to register edge triggered on&n; * Linux (if it can be done at all). But in some experimentation, I&n; * don&squot;t see much operational difference between using either&n; * interrupt mode. Don&squot;t mess with the interrupt mode in the COR&n; * register though, as the PLX9052 wants level triggers with the way&n; * the serial EEPROM configures it on the WL11000.&n; *&n; * There&squot;s some other little quirks related to timing that I bumped&n; * into, but I don&squot;t recall right now. Also, there&squot;s two variants of&n; * the WL11000 I&squot;ve seen, revision A1 and T2. These seem to differ&n; * slightly in the timings configured in the wait-state generator in&n; * the PLX9052. There have also been some comments from Eumitcom that&n; * cards shouldn&squot;t be hot swapped, apparently due to risk of cooking&n; * the PLX9052. I&squot;m unsure why they believe this, as I can&squot;t see&n; * anything in the design that would really cause a problem, except&n; * for crashing drivers not written to expect it. And having developed&n; * drivers for the WL11000, I&squot;d say it&squot;s quite tricky to write code&n; * that will successfully deal with a hot unplug. Very odd things&n; * happen on the I/O side of things. But anyway, be warned. Despite&n; * that, I&squot;ve hot-swapped a number of times during debugging and&n; * driver development for various reasons (stuck WAIT# line after the&n; * radio card&squot;s firmware locks up).&n; *&n; * Hope this is enough info for someone to add PLX9052 support to the&n; * wlan-ng card. In the case of the WL11000, the PCI ID&squot;s are&n; * 0x1639/0x0200, with matching subsystem ID&squot;s. Other PLX9052-based&n; * manufacturers other than Eumitcom (or on cards other than the&n; * WL11000) may have different PCI ID&squot;s.&n; *&n; * If anyone needs any more specific info, let me know. I haven&squot;t had&n; * time to implement support myself yet, and with the way things are&n; * going, might not have time for a while..&n; */
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME &quot;orinoco_plx&quot;
DECL|macro|PFX
mdefine_line|#define PFX DRIVER_NAME &quot;: &quot;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;pcmcia/cisreg.h&gt;
macro_line|#include &quot;hermes.h&quot;
macro_line|#include &quot;orinoco.h&quot;
DECL|macro|COR_OFFSET
mdefine_line|#define COR_OFFSET&t;(0x3e0/2) /* COR attribute offset of Prism2 PC card */
DECL|macro|COR_VALUE
mdefine_line|#define COR_VALUE&t;(COR_LEVEL_REQ | COR_FUNC_ENA) /* Enable PC card with interrupt in level trigger */
DECL|macro|PLX_INTCSR
mdefine_line|#define PLX_INTCSR&t;&t;0x4c /* Interrupt Control &amp; Status Register */
DECL|macro|PLX_INTCSR_INTEN
mdefine_line|#define PLX_INTCSR_INTEN&t;(1&lt;&lt;6) /* Interrupt Enable bit */
DECL|variable|cis_magic
r_static
r_const
id|u16
id|cis_magic
(braket
)braket
op_assign
(brace
l_int|0x0001
comma
l_int|0x0003
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x00ff
comma
l_int|0x0017
comma
l_int|0x0004
comma
l_int|0x0067
)brace
suffix:semicolon
DECL|function|orinoco_plx_init_one
r_static
r_int
id|orinoco_plx_init_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|u16
op_star
id|attr_mem
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|reg
comma
id|addr
suffix:semicolon
r_struct
id|orinoco_private
op_star
id|priv
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|pccard_ioaddr
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|pccard_iolen
op_assign
l_int|0
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
id|err
op_assign
id|pci_enable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* Resource 2 is mapped to the PCMCIA space */
id|attr_mem
op_assign
id|ioremap
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|2
)paren
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|attr_mem
)paren
r_goto
id|fail
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;orinoco_plx: CIS: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%02X:&quot;
comma
(paren
r_int
)paren
id|attr_mem
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Verify whether PC card is present */
multiline_comment|/* FIXME: we probably need to be smarted about this */
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|attr_mem
comma
id|cis_magic
comma
r_sizeof
(paren
id|cis_magic
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;orinoco_plx: The CIS value of Prism2 PC card is invalid.&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
multiline_comment|/* PCMCIA COR is the first byte following CIS: this write should&n;&t; * enable I/O mode and select level-triggered interrupts */
id|attr_mem
(braket
id|COR_OFFSET
)braket
op_assign
id|COR_VALUE
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|reg
op_assign
id|attr_mem
(braket
id|COR_OFFSET
)braket
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_ne
id|COR_VALUE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;orinoco_plx: Error setting COR value (reg=%x)&bslash;n&quot;
comma
id|reg
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|iounmap
c_func
(paren
id|attr_mem
)paren
suffix:semicolon
id|attr_mem
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* done with this now, it seems */
multiline_comment|/* bjoern: We need to tell the card to enable interrupts, in&n;&t;   case the serial eprom didn&squot;t do this already. See the&n;&t;   PLX9052 data book, p8-1 and 8-24 for reference. */
id|addr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|1
)paren
suffix:semicolon
id|reg
op_assign
l_int|0
suffix:semicolon
id|reg
op_assign
id|inl
c_func
(paren
id|addr
op_plus
id|PLX_INTCSR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_amp
id|PLX_INTCSR_INTEN
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;orinoco_plx: &quot;
l_string|&quot;Local Interrupt already enabled&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|reg
op_or_assign
id|PLX_INTCSR_INTEN
suffix:semicolon
id|outl
c_func
(paren
id|reg
comma
id|addr
op_plus
id|PLX_INTCSR
)paren
suffix:semicolon
id|reg
op_assign
id|inl
c_func
(paren
id|addr
op_plus
id|PLX_INTCSR
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|reg
op_amp
id|PLX_INTCSR_INTEN
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;orinoco_plx: &quot;
l_string|&quot;Couldn&squot;t enable Local Interrupts&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
)brace
multiline_comment|/* and 3 to the PCMCIA slot I/O address space */
id|pccard_ioaddr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|3
)paren
suffix:semicolon
id|pccard_iolen
op_assign
id|pci_resource_len
c_func
(paren
id|pdev
comma
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|pccard_ioaddr
comma
id|pccard_iolen
comma
id|DRIVER_NAME
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;orinoco_plx: I/O resource 0x%lx @ 0x%lx busy&bslash;n&quot;
comma
id|pccard_iolen
comma
id|pccard_ioaddr
)paren
suffix:semicolon
id|pccard_ioaddr
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
multiline_comment|/* Allocate network device */
id|dev
op_assign
id|alloc_orinocodev
c_func
(paren
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|pccard_ioaddr
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
id|SET_NETDEV_DEV
c_func
(paren
id|dev
comma
op_amp
id|pdev-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
id|PFX
l_string|&quot;Detected Orinoco/Prism2 PLX device &quot;
l_string|&quot;at %s irq:%d, io addr:0x%lx&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|pdev
)paren
comma
id|pdev-&gt;irq
comma
id|pccard_ioaddr
)paren
suffix:semicolon
id|hermes_struct_init
c_func
(paren
op_amp
(paren
id|priv-&gt;hw
)paren
comma
id|dev-&gt;base_addr
comma
id|HERMES_IO
comma
id|HERMES_16BIT_REGSPACING
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
id|dev
)paren
suffix:semicolon
id|err
op_assign
id|request_irq
c_func
(paren
id|pdev-&gt;irq
comma
id|orinoco_interrupt
comma
id|SA_SHIRQ
comma
id|dev-&gt;name
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;Error allocating IRQ %d.&bslash;n&quot;
comma
id|pdev-&gt;irq
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|dev-&gt;irq
op_assign
id|pdev-&gt;irq
suffix:semicolon
id|err
op_assign
id|register_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|fail
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
id|PFX
l_string|&quot;init_one(), FAIL!&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;irq
)paren
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pccard_ioaddr
)paren
id|release_region
c_func
(paren
id|pccard_ioaddr
comma
id|pccard_iolen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|attr_mem
)paren
id|iounmap
c_func
(paren
id|attr_mem
)paren
suffix:semicolon
id|pci_disable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|orinoco_plx_remove_one
r_static
r_void
id|__devexit
id|orinoco_plx_remove_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|pci_get_drvdata
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
op_logical_neg
id|dev
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
)paren
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
l_int|NULL
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|3
)paren
comma
id|pci_resource_len
c_func
(paren
id|pdev
comma
l_int|3
)paren
)paren
suffix:semicolon
id|pci_disable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
)brace
DECL|variable|orinoco_plx_pci_id_table
r_static
r_struct
id|pci_device_id
id|orinoco_plx_pci_id_table
(braket
)braket
op_assign
(brace
(brace
l_int|0x111a
comma
l_int|0x1023
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
multiline_comment|/* Siemens SpeedStream SS1023 */
(brace
l_int|0x1385
comma
l_int|0x4100
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
multiline_comment|/* Netgear MA301 */
(brace
l_int|0x15e8
comma
l_int|0x0130
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
multiline_comment|/* Correga  - does this work? */
(brace
l_int|0x1638
comma
l_int|0x1100
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
multiline_comment|/* SMC EZConnect SMC2602W,&n;&t;&t;&t;&t;&t;&t;&t;   Eumitcom PCI WL11000,&n;&t;&t;&t;&t;&t;&t;&t;   Addtron AWA-100 */
(brace
l_int|0x16ab
comma
l_int|0x1100
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
multiline_comment|/* Global Sun Tech GL24110P */
(brace
l_int|0x16ab
comma
l_int|0x1101
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
multiline_comment|/* Reported working, but unknown */
(brace
l_int|0x16ab
comma
l_int|0x1102
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
multiline_comment|/* Linksys WDT11 */
(brace
l_int|0x16ec
comma
l_int|0x3685
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
multiline_comment|/* USR 2415 */
(brace
l_int|0xec80
comma
l_int|0xec00
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
multiline_comment|/* Belkin F5D6000 tested by&n;&t;&t;&t;&t;&t;&t;&t;   Brendan W. McAdams &lt;rit AT jacked-in.org&gt; */
(brace
l_int|0x10b7
comma
l_int|0x7770
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
multiline_comment|/* 3Com AirConnect PCI tested by&n;&t;&t;&t;&t;&t;&t;&t;   Damien Persohn &lt;damien AT persohn.net&gt; */
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|orinoco_plx_pci_id_table
)paren
suffix:semicolon
DECL|variable|orinoco_plx_driver
r_static
r_struct
id|pci_driver
id|orinoco_plx_driver
op_assign
(brace
dot
id|name
op_assign
id|DRIVER_NAME
comma
dot
id|id_table
op_assign
id|orinoco_plx_pci_id_table
comma
dot
id|probe
op_assign
id|orinoco_plx_init_one
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|orinoco_plx_remove_one
)paren
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|version
(braket
)braket
id|__initdata
op_assign
id|DRIVER_NAME
l_string|&quot; &quot;
id|DRIVER_VERSION
l_string|&quot; (Pavel Roskin &lt;proski@gnu.org&gt;,&quot;
l_string|&quot; David Gibson &lt;hermes@gibson.dropbear.id.au&gt;,&quot;
l_string|&quot; Daniel Barlow &lt;dan@telent.net&gt;)&quot;
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Daniel Barlow &lt;dan@telent.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver for wireless LAN cards using the PLX9052 PCI bridge&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual MPL/GPL&quot;
)paren
suffix:semicolon
DECL|function|orinoco_plx_init
r_static
r_int
id|__init
id|orinoco_plx_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
r_return
id|pci_module_init
c_func
(paren
op_amp
id|orinoco_plx_driver
)paren
suffix:semicolon
)brace
DECL|function|orinoco_plx_exit
r_static
r_void
id|__exit
id|orinoco_plx_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|orinoco_plx_driver
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
)paren
suffix:semicolon
)brace
DECL|variable|orinoco_plx_init
id|module_init
c_func
(paren
id|orinoco_plx_init
)paren
suffix:semicolon
DECL|variable|orinoco_plx_exit
id|module_exit
c_func
(paren
id|orinoco_plx_exit
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; *  c-indent-level: 8&n; *  c-basic-offset: 8&n; *  tab-width: 8&n; * End:&n; */
eof
