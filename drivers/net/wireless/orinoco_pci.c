multiline_comment|/* orinoco_pci.c 0.13e&n; * &n; * Driver for Prism II devices that have a direct PCI interface&n; * (i.e., not in a Pcmcia or PLX bridge)&n; *&n; * Specifically here we&squot;re talking about the Linksys WMP11&n; *&n; * Some of this code is borrowed from orinoco_plx.c&n; *&t;Copyright (C) 2001 Daniel Barlow &lt;dan AT telent.net&gt;&n; * Some of this code is &quot;inspired&quot; by linux-wlan-ng-0.1.10, but nothing&n; * has been copied from it. linux-wlan-ng-0.1.10 is originally :&n; *&t;Copyright (C) 1999 AbsoluteValue Systems, Inc.  All Rights Reserved.&n; * This file originally written by:&n; *&t;Copyright (C) 2001 Jean Tourrilhes &lt;jt AT hpl.hp.com&gt;&n; * And is now maintained by:&n; *&t;Copyright (C) 2002 David Gibson, IBM Corporation &lt;herme AT gibson.dropbear.id.au&gt;&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in&n; * which case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use your&n; * version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
multiline_comment|/*&n; * Theory of operation...&n; * -------------------&n; * Maybe you had a look in orinoco_plx. Well, this is totally different...&n; *&n; * The card contains only one PCI region, which contains all the usual&n; * hermes registers.&n; *&n; * The driver will memory map this region in normal memory. Because&n; * the hermes registers are mapped in normal memory and not in ISA I/O&n; * post space, we can&squot;t use the usual inw/outw macros and we need to&n; * use readw/writew.&n; * This slight difference force us to compile our own version of&n; * hermes.c with the register access macro changed. That&squot;s a bit&n; * hackish but works fine.&n; *&n; * Note that the PCI region is pretty big (4K). That&squot;s much more than&n; * the usual set of hermes register (0x0 -&gt; 0x3E). I&squot;ve got a strong&n; * suspicion that the whole memory space of the adapter is in fact in&n; * this region. Accessing directly the adapter memory instead of going&n; * through the usual register would speed up significantely the&n; * operations...&n; *&n; * Finally, the card looks like this :&n;-----------------------&n;  Bus  0, device  14, function  0:&n;    Network controller: PCI device 1260:3873 (Harris Semiconductor) (rev 1).&n;      IRQ 11.&n;      Master Capable.  Latency=248.  &n;      Prefetchable 32 bit memory at 0xffbcc000 [0xffbccfff].&n;-----------------------&n;00:0e.0 Network controller: Harris Semiconductor: Unknown device 3873 (rev 01)&n;        Subsystem: Unknown device 1737:3874&n;        Control: I/O+ Mem+ BusMaster+ SpecCycle- MemWINV- VGASnoop- ParErr- Stepping- SERR- FastB2B-&n;        Status: Cap+ 66Mhz- UDF- FastB2B+ ParErr- DEVSEL=medium &gt;TAbort- &lt;TAbort- &lt;MAbort- &gt;SERR- &lt;PERR-&n;        Latency: 248 set, cache line size 08&n;        Interrupt: pin A routed to IRQ 11&n;        Region 0: Memory at ffbcc000 (32-bit, prefetchable) [size=4K]&n;        Capabilities: [dc] Power Management version 2&n;                Flags: PMEClk- AuxPwr- DSI- D1+ D2+ PME+&n;                Status: D0 PME-Enable- DSel=0 DScale=0 PME-&n;-----------------------&n; *&n; * That&squot;s all..&n; *&n; * Jean II&n; */
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
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/wireless.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;hermes.h&quot;
macro_line|#include &quot;orinoco.h&quot;
multiline_comment|/* All the magic there is from wlan-ng */
multiline_comment|/* Magic offset of the reset register of the PCI card */
DECL|macro|HERMES_PCI_COR
mdefine_line|#define HERMES_PCI_COR&t;&t;(0x26)
multiline_comment|/* Magic bitmask to reset the card */
DECL|macro|HERMES_PCI_COR_MASK
mdefine_line|#define HERMES_PCI_COR_MASK&t;(0x0080)
multiline_comment|/* Magic timeouts for doing the reset.&n; * Those times are straight from wlan-ng, and it is claimed that they&n; * are necessary. Alan will kill me. Take your time and grab a coffee. */
DECL|macro|HERMES_PCI_COR_ONT
mdefine_line|#define HERMES_PCI_COR_ONT&t;(250)&t;&t;/* ms */
DECL|macro|HERMES_PCI_COR_OFFT
mdefine_line|#define HERMES_PCI_COR_OFFT&t;(500)&t;&t;/* ms */
DECL|macro|HERMES_PCI_COR_BUSYT
mdefine_line|#define HERMES_PCI_COR_BUSYT&t;(500)&t;&t;/* ms */
multiline_comment|/*&n; * Do a soft reset of the PCI card using the Configuration Option Register&n; * We need this to get going...&n; * This is the part of the code that is strongly inspired from wlan-ng&n; *&n; * Note : This code is done with irq enabled. This mean that many&n; * interrupts will occur while we are there. This is why we use the&n; * jiffies to regulate time instead of a straight mdelay(). Usually we&n; * need only around 245 iteration of the loop to do 250 ms delay.&n; *&n; * Note bis : Don&squot;t try to access HERMES_CMD during the reset phase.&n; * It just won&squot;t work !&n; */
r_static
r_int
DECL|function|orinoco_pci_cor_reset
id|orinoco_pci_cor_reset
c_func
(paren
r_struct
id|orinoco_private
op_star
id|priv
)paren
(brace
id|hermes_t
op_star
id|hw
op_assign
op_amp
id|priv-&gt;hw
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
id|u16
id|reg
suffix:semicolon
multiline_comment|/* Assert the reset until the card notice */
id|hermes_write_regn
c_func
(paren
id|hw
comma
id|PCI_COR
comma
id|HERMES_PCI_COR_MASK
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Reset done&quot;
)paren
suffix:semicolon
id|timeout
op_assign
id|jiffies
op_plus
(paren
id|HERMES_PCI_COR_ONT
op_star
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
r_while
c_loop
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|timeout
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;;&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|//mdelay(HERMES_PCI_COR_ONT);
multiline_comment|/* Give time for the card to recover from this hard effort */
id|hermes_write_regn
c_func
(paren
id|hw
comma
id|PCI_COR
comma
l_int|0x0000
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Clear Reset&quot;
)paren
suffix:semicolon
id|timeout
op_assign
id|jiffies
op_plus
(paren
id|HERMES_PCI_COR_OFFT
op_star
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
r_while
c_loop
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|timeout
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;;&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|//mdelay(HERMES_PCI_COR_OFFT);
multiline_comment|/* The card is ready when it&squot;s no longer busy */
id|timeout
op_assign
id|jiffies
op_plus
(paren
id|HERMES_PCI_COR_BUSYT
op_star
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
id|reg
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|CMD
)paren
suffix:semicolon
r_while
c_loop
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|timeout
)paren
op_logical_and
(paren
id|reg
op_amp
id|HERMES_CMD_BUSY
)paren
)paren
(brace
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|reg
op_assign
id|hermes_read_regn
c_func
(paren
id|hw
comma
id|CMD
)paren
suffix:semicolon
)brace
multiline_comment|/* Did we timeout ? */
r_if
c_cond
(paren
id|time_after_eq
c_func
(paren
id|jiffies
comma
id|timeout
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;orinoco_pci: Busy timeout&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;pci_cor : reg = 0x%X - %lX - %lX&bslash;n&quot;
comma
id|reg
comma
id|timeout
comma
id|jiffies
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialise a card. Mostly similar to PLX code.&n; */
DECL|function|orinoco_pci_init_one
r_static
r_int
id|orinoco_pci_init_one
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
r_int
r_int
id|pci_iorange
suffix:semicolon
id|u16
op_star
id|pci_ioaddr
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|pci_iolen
suffix:semicolon
r_struct
id|orinoco_private
op_star
id|priv
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
l_int|NULL
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
multiline_comment|/* Resource 0 is mapped to the hermes registers */
id|pci_iorange
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
id|pci_iolen
op_assign
id|pci_resource_len
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
id|pci_ioaddr
op_assign
id|ioremap
c_func
(paren
id|pci_iorange
comma
id|pci_iolen
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_iorange
)paren
r_goto
id|fail
suffix:semicolon
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
(paren
r_int
r_int
)paren
id|pci_ioaddr
suffix:semicolon
id|dev-&gt;mem_start
op_assign
id|pci_iorange
suffix:semicolon
id|dev-&gt;mem_end
op_assign
id|pci_iorange
op_plus
id|pci_iolen
op_minus
l_int|1
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
l_string|&quot;Detected Orinoco/Prism2 PCI device at %s, mem:0x%lX to 0x%lX -&gt; 0x%p, irq:%d&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|pdev
)paren
comma
id|dev-&gt;mem_start
comma
id|dev-&gt;mem_end
comma
id|pci_ioaddr
comma
id|pdev-&gt;irq
)paren
suffix:semicolon
id|hermes_struct_init
c_func
(paren
op_amp
id|priv-&gt;hw
comma
id|dev-&gt;base_addr
comma
id|HERMES_MEM
comma
id|HERMES_32BIT_REGSPACING
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
l_string|&quot;orinoco_pci: Error allocating IRQ %d.&bslash;n&quot;
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
multiline_comment|/* Perform a COR reset to start the card */
r_if
c_cond
(paren
id|orinoco_pci_cor_reset
c_func
(paren
id|priv
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Failed to start the card&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ETIMEDOUT
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
multiline_comment|/* Override the normal firmware detection - the Prism 2.5 PCI&n;&t; * cards look like Lucent firmware but are actually Intersil */
id|priv-&gt;firmware_type
op_assign
id|FIRMWARE_TYPE_INTERSIL
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
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Failed to register net device&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
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
id|pci_ioaddr
)paren
id|iounmap
c_func
(paren
id|pci_ioaddr
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
DECL|function|orinoco_pci_remove_one
r_static
r_void
id|__devexit
id|orinoco_pci_remove_one
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
r_struct
id|orinoco_private
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
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
r_if
c_cond
(paren
id|priv-&gt;hw.iobase
)paren
id|iounmap
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|priv-&gt;hw.iobase
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
id|pci_disable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
)brace
DECL|function|orinoco_pci_suspend
r_static
r_int
id|orinoco_pci_suspend
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
id|u32
id|state
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
r_struct
id|orinoco_private
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|err
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Orinoco-PCI entering sleep mode (state=%d)&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|state
)paren
suffix:semicolon
id|err
op_assign
id|orinoco_lock
c_func
(paren
id|priv
comma
op_amp
id|flags
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
l_string|&quot;%s: hw_unavailable on orinoco_pci_suspend&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|err
op_assign
id|__orinoco_down
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
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: orinoco_pci_suspend(): Error %d downing interface&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|err
)paren
suffix:semicolon
id|netif_device_detach
c_func
(paren
id|dev
)paren
suffix:semicolon
id|priv-&gt;hw_unavailable
op_increment
suffix:semicolon
id|orinoco_unlock
c_func
(paren
id|priv
comma
op_amp
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|orinoco_pci_resume
r_static
r_int
id|orinoco_pci_resume
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
r_struct
id|orinoco_private
op_star
id|priv
op_assign
id|netdev_priv
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|err
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: Orinoco-PCI waking up&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|err
op_assign
id|orinoco_reinit_firmware
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
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Error %d re-initializing firmware on orinoco_pci_resume()&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|netif_device_attach
c_func
(paren
id|dev
)paren
suffix:semicolon
id|priv-&gt;hw_unavailable
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;open
op_logical_and
(paren
op_logical_neg
id|priv-&gt;hw_unavailable
)paren
)paren
(brace
id|err
op_assign
id|__orinoco_up
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
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Error %d restarting card on orinoco_pci_resume()&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|err
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|priv-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|orinoco_pci_pci_id_table
r_static
r_struct
id|pci_device_id
id|orinoco_pci_pci_id_table
(braket
)braket
op_assign
(brace
multiline_comment|/* Intersil Prism 3 */
(brace
l_int|0x1260
comma
l_int|0x3872
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
multiline_comment|/* Intersil Prism 2.5 */
(brace
l_int|0x1260
comma
l_int|0x3873
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
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
id|orinoco_pci_pci_id_table
)paren
suffix:semicolon
DECL|variable|orinoco_pci_driver
r_static
r_struct
id|pci_driver
id|orinoco_pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;orinoco_pci&quot;
comma
dot
id|id_table
op_assign
id|orinoco_pci_pci_id_table
comma
dot
id|probe
op_assign
id|orinoco_pci_init_one
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|orinoco_pci_remove_one
)paren
comma
dot
id|suspend
op_assign
id|orinoco_pci_suspend
comma
dot
id|resume
op_assign
id|orinoco_pci_resume
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
l_string|&quot;orinoco_pci.c 0.13e (David Gibson &lt;hermes@gibson.dropbear.id.au&gt; &amp; Jean Tourrilhes &lt;jt@hpl.hp.com&gt;)&quot;
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David Gibson &lt;hermes@gibson.dropbear.id.au&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver for wireless LAN cards using direct PCI interface&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual MPL/GPL&quot;
)paren
suffix:semicolon
DECL|function|orinoco_pci_init
r_static
r_int
id|__init
id|orinoco_pci_init
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
id|orinoco_pci_driver
)paren
suffix:semicolon
)brace
DECL|function|orinoco_pci_exit
r_void
id|__exit
id|orinoco_pci_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|orinoco_pci_driver
)paren
suffix:semicolon
)brace
DECL|variable|orinoco_pci_init
id|module_init
c_func
(paren
id|orinoco_pci_init
)paren
suffix:semicolon
DECL|variable|orinoco_pci_exit
id|module_exit
c_func
(paren
id|orinoco_pci_exit
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; *  c-indent-level: 8&n; *  c-basic-offset: 8&n; *  tab-width: 8&n; * End:&n; */
eof
