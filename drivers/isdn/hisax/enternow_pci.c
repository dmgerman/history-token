multiline_comment|/* enternow_pci.c,v 0.99 2001/10/02&n; *&n; * enternow_pci.c       Card-specific routines for&n; *                      Formula-n enter:now ISDN PCI ab&n; *                      Gerdes AG Power ISDN PCI&n; *                      Woerltronic SA 16 PCI&n; *                      (based on HiSax driver by Karsten Keil)&n; *&n; * Author               Christoph Ersfeld &lt;info@formula-n.de&gt;&n; *                      Formula-n Europe AG (www.formula-n.com)&n; *                      previously Gerdes AG&n; *&n; *&n; *                      This file is (c) under GNU PUBLIC LICENSE&n; *&n; * Notes:&n; * This driver interfaces to netjet.c which performs B-channel&n; * processing.&n; *&n; * Version 0.99 is the first release of this driver and there are&n; * certainly a few bugs.&n; * It isn&squot;t testet on linux 2.4 yet, so consider this code to be&n; * beta.&n; *&n; * Please don&squot;t report me any malfunction without sending&n; * (compressed) debug-logs.&n; * It would be nearly impossible to retrace it.&n; *&n; * Log D-channel-processing as follows:&n; *&n; * 1. Load hisax with card-specific parameters, this example ist for&n; *    Formula-n enter:now ISDN PCI and compatible&n; *    (f.e. Gerdes Power ISDN PCI)&n; *&n; *    modprobe hisax type=41 protocol=2 id=gerdes&n; *&n; *    if you chose an other value for id, you need to modify the&n; *    code below, too.&n; *&n; * 2. set debug-level&n; *&n; *    hisaxctrl gerdes 1 0x3ff&n; *    hisaxctrl gerdes 11 0x4f&n; *    cat /dev/isdnctrl &gt;&gt; ~/log &amp;&n; *&n; * Please take also a look into /var/log/messages if there is&n; * anything importand concerning HISAX.&n; *&n; *&n; * Credits:&n; * Programming the driver for Formula-n enter:now ISDN PCI and&n; * neccessary the driver for the used Amd 7930 D-channel-controller&n; * was spnsored by Formula-n Europe AG.&n; * Thanks to Karsten Keil and Petr Novak, who gave me support in&n; * Hisax-specific questions.&n; * I want so say special thanks to Carl-Friedrich Braun, who had to&n; * answer a lot of questions about generally ISDN and about handling&n; * of the Amd-Chip.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &quot;amd7930_fn.h&quot;
macro_line|#include &quot;enternow.h&quot;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ppp_defs.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;netjet.h&quot;
DECL|variable|enternow_pci_rev
r_const
r_char
op_star
id|enternow_pci_rev
op_assign
l_string|&quot;$Revision: 1.1.2.1 $&quot;
suffix:semicolon
multiline_comment|/* *************************** I/O-Interface functions ************************************* */
multiline_comment|/* cs-&gt;readisac, macro rByteAMD */
r_static
id|BYTE
DECL|function|ReadByteAmd7930
id|ReadByteAmd7930
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|BYTE
id|offset
)paren
(brace
multiline_comment|/* direktes Register */
r_if
c_cond
(paren
id|offset
OL
l_int|8
)paren
(brace
r_return
(paren
id|InByte
c_func
(paren
id|cs-&gt;hw.njet.isac
op_plus
l_int|4
op_star
id|offset
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* indirektes Register */
r_else
(brace
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.isac
op_plus
l_int|4
op_star
id|AMD_CR
comma
id|offset
)paren
suffix:semicolon
r_return
id|InByte
c_func
(paren
id|cs-&gt;hw.njet.isac
op_plus
l_int|4
op_star
id|AMD_DR
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* cs-&gt;writeisac, macro wByteAMD */
r_static
r_void
DECL|function|WriteByteAmd7930
id|WriteByteAmd7930
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|BYTE
id|offset
comma
id|BYTE
id|value
)paren
(brace
multiline_comment|/* direktes Register */
r_if
c_cond
(paren
id|offset
OL
l_int|8
)paren
(brace
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.isac
op_plus
l_int|4
op_star
id|offset
comma
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/* indirektes Register */
r_else
(brace
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.isac
op_plus
l_int|4
op_star
id|AMD_CR
comma
id|offset
)paren
suffix:semicolon
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.isac
op_plus
l_int|4
op_star
id|AMD_DR
comma
id|value
)paren
suffix:semicolon
)brace
)brace
DECL|variable|enternow_ops
r_static
r_struct
id|dc_hw_ops
id|enternow_ops
op_assign
(brace
dot
id|read_reg
op_assign
id|ReadByteAmd7930
comma
dot
id|write_reg
op_assign
id|WriteByteAmd7930
comma
)brace
suffix:semicolon
r_void
DECL|function|enpci_setIrqMask
id|enpci_setIrqMask
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|BYTE
id|val
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_IRQMASK1
comma
l_int|0x00
)paren
suffix:semicolon
r_else
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_IRQMASK1
comma
id|TJ_AMD_IRQ
)paren
suffix:semicolon
)brace
multiline_comment|/* ******************************************************************************** */
r_static
r_void
DECL|function|reset_enpci
id|reset_enpci
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;enter:now PCI: reset&quot;
)paren
suffix:semicolon
multiline_comment|/* Reset on, (also for AMD) */
id|cs-&gt;hw.njet.ctrl_reg
op_assign
l_int|0x07
suffix:semicolon
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_CTRL
comma
id|cs-&gt;hw.njet.ctrl_reg
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
multiline_comment|/* 80 ms delay */
id|schedule_timeout
c_func
(paren
(paren
l_int|80
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* Reset off */
id|cs-&gt;hw.njet.ctrl_reg
op_assign
l_int|0x70
suffix:semicolon
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_CTRL
comma
id|cs-&gt;hw.njet.ctrl_reg
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
multiline_comment|/* 80ms delay */
id|schedule_timeout
c_func
(paren
(paren
l_int|80
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
id|cs-&gt;hw.njet.auxd
op_assign
l_int|0
suffix:semicolon
singleline_comment|// LED-status
id|cs-&gt;hw.njet.dmactrl
op_assign
l_int|0
suffix:semicolon
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_AUXCTRL
comma
op_complement
id|TJ_AMD_IRQ
)paren
suffix:semicolon
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_IRQMASK1
comma
id|TJ_AMD_IRQ
)paren
suffix:semicolon
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.auxa
comma
id|cs-&gt;hw.njet.auxd
)paren
suffix:semicolon
singleline_comment|// LED off
)brace
r_static
r_void
DECL|function|enpci_bc_activate
id|enpci_bc_activate
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|chan
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;enter:now PCI: assign phys. BC %d in AMD LMR1&quot;
comma
id|chan
)paren
suffix:semicolon
id|cs-&gt;dc.amd7930
dot
id|ph_command
c_func
(paren
id|cs
comma
(paren
id|cs-&gt;dc.amd7930.lmr1
op_or
(paren
id|chan
op_plus
l_int|1
)paren
)paren
comma
l_string|&quot;MDL_BC_ASSIGN&quot;
)paren
suffix:semicolon
multiline_comment|/* at least one b-channel in use, LED 2 on */
id|cs-&gt;hw.njet.auxd
op_or_assign
id|TJ_AMD_IRQ
op_lshift
l_int|2
suffix:semicolon
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_AUXDATA
comma
id|cs-&gt;hw.njet.auxd
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|enpci_bc_deactivate
id|enpci_bc_deactivate
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|chan
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;enter:now PCI: release phys. BC %d in Amd LMR1&quot;
comma
id|chan
)paren
suffix:semicolon
id|cs-&gt;dc.amd7930
dot
id|ph_command
c_func
(paren
id|cs
comma
(paren
id|cs-&gt;dc.amd7930.lmr1
op_amp
op_complement
(paren
id|chan
op_plus
l_int|1
)paren
)paren
comma
l_string|&quot;MDL_BC_RELEASE&quot;
)paren
suffix:semicolon
multiline_comment|/* no b-channel active -&gt; LED2 off */
r_if
c_cond
(paren
op_logical_neg
(paren
id|cs-&gt;dc.amd7930.lmr1
op_amp
l_int|3
)paren
)paren
(brace
id|cs-&gt;hw.njet.auxd
op_and_assign
op_complement
(paren
id|TJ_AMD_IRQ
op_lshift
l_int|2
)paren
suffix:semicolon
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_AUXDATA
comma
id|cs-&gt;hw.njet.auxd
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|enpci_card_msg
id|enpci_card_msg
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|mt
comma
r_void
op_star
id|arg
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;debug
op_amp
id|L1_DEB_ISAC
)paren
id|debugl1
c_func
(paren
id|cs
comma
l_string|&quot;enter:now PCI: card_msg: 0x%04X&quot;
comma
id|mt
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|mt
)paren
(brace
r_case
id|MDL_ASSIGN
suffix:colon
multiline_comment|/* TEI assigned, LED1 on */
id|cs-&gt;hw.njet.auxd
op_assign
id|TJ_AMD_IRQ
op_lshift
l_int|1
suffix:semicolon
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_AUXDATA
comma
id|cs-&gt;hw.njet.auxd
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MDL_REMOVE
suffix:colon
multiline_comment|/* TEI removed, LEDs off */
id|cs-&gt;hw.njet.auxd
op_assign
l_int|0
suffix:semicolon
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_AUXDATA
comma
l_int|0x00
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|enpci_init
id|enpci_init
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|inittiger
c_func
(paren
id|cs
)paren
suffix:semicolon
id|Amd7930_init
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|enpci_reset
id|enpci_reset
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|reset_enpci
c_func
(paren
id|cs
)paren
suffix:semicolon
id|Amd7930_init
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|enpci_interrupt
id|enpci_interrupt
c_func
(paren
r_int
id|intno
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|dev_id
suffix:semicolon
id|BYTE
id|sval
comma
id|ir
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cs-&gt;lock
)paren
suffix:semicolon
id|sval
op_assign
id|InByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_IRQSTAT1
)paren
suffix:semicolon
multiline_comment|/* AMD threw an interrupt */
r_if
c_cond
(paren
op_logical_neg
(paren
id|sval
op_amp
id|TJ_AMD_IRQ
)paren
)paren
(brace
multiline_comment|/* read and clear interrupt-register */
id|ir
op_assign
id|ReadByteAmd7930
c_func
(paren
id|cs
comma
l_int|0x00
)paren
suffix:semicolon
id|Amd7930_interrupt
c_func
(paren
id|cs
comma
id|ir
)paren
suffix:semicolon
)brace
multiline_comment|/* DMA-Interrupt: B-channel-stuff */
multiline_comment|/* set bits in sval to indicate which page is free */
multiline_comment|/* set bits in sval to indicate which page is free */
r_if
c_cond
(paren
id|inl
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_DMA_WRITE_ADR
)paren
OL
id|inl
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_DMA_WRITE_IRQ
)paren
)paren
multiline_comment|/* the 2nd write page is free */
id|sval
op_assign
l_int|0x08
suffix:semicolon
r_else
multiline_comment|/* the 1st write page is free */
id|sval
op_assign
l_int|0x04
suffix:semicolon
r_if
c_cond
(paren
id|inl
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_DMA_READ_ADR
)paren
OL
id|inl
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_DMA_READ_IRQ
)paren
)paren
multiline_comment|/* the 2nd read page is free */
id|sval
op_assign
id|sval
op_or
l_int|0x02
suffix:semicolon
r_else
multiline_comment|/* the 1st read page is free */
id|sval
op_assign
id|sval
op_or
l_int|0x01
suffix:semicolon
r_if
c_cond
(paren
id|sval
op_ne
id|cs-&gt;hw.njet.last_is0
)paren
(brace
multiline_comment|/* we have a DMA interrupt */
id|cs-&gt;hw.njet.irqstat0
op_assign
id|sval
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cs-&gt;hw.njet.irqstat0
op_amp
id|NETJET_IRQM0_READ
)paren
op_ne
(paren
id|cs-&gt;hw.njet.last_is0
op_amp
id|NETJET_IRQM0_READ
)paren
)paren
multiline_comment|/* we have a read dma int */
id|read_tiger
c_func
(paren
id|cs
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cs-&gt;hw.njet.irqstat0
op_amp
id|NETJET_IRQM0_WRITE
)paren
op_ne
(paren
id|cs-&gt;hw.njet.last_is0
op_amp
id|NETJET_IRQM0_WRITE
)paren
)paren
multiline_comment|/* we have a write dma int */
id|write_tiger
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|cs-&gt;lock
)paren
suffix:semicolon
)brace
DECL|variable|enpci_ops
r_static
r_struct
id|card_ops
id|enpci_ops
op_assign
(brace
dot
id|init
op_assign
id|enpci_init
comma
dot
id|reset
op_assign
id|enpci_reset
comma
dot
id|release
op_assign
id|netjet_release
comma
dot
id|irq_func
op_assign
id|enpci_interrupt
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|pci_dev
op_star
id|dev_netjet
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* called by config.c */
r_int
id|__init
DECL|function|setup_enternow_pci
id|setup_enternow_pci
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
(brace
r_struct
id|IsdnCardState
op_star
id|cs
op_assign
id|card-&gt;cs
suffix:semicolon
r_char
id|tmp
(braket
l_int|64
)braket
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
macro_line|#error &quot;not running on big endian machines now&quot;
macro_line|#endif
id|strcpy
c_func
(paren
id|tmp
comma
id|enternow_pci_rev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Formula-n Europe AG enter:now ISDN PCI driver Rev. %s&bslash;n&quot;
comma
id|HiSax_getrev
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;typ
op_ne
id|ISDN_CTYPE_ENTERNOW
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
(paren
id|dev_netjet
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_TIGERJET
comma
id|PCI_DEVICE_ID_TIGERJET_300
comma
id|dev_netjet
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|dev_netjet
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|cs-&gt;irq
op_assign
id|dev_netjet-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs-&gt;irq
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;enter:now PCI: No IRQ for PCI card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cs-&gt;hw.njet.base
op_assign
id|pci_resource_start
c_func
(paren
id|dev_netjet
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs-&gt;hw.njet.base
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;enter:now PCI: No IO-Adr for PCI card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* checks Sub-Vendor ID because system crashes with Traverse-Card */
r_if
c_cond
(paren
(paren
id|dev_netjet-&gt;subsystem_vendor
op_ne
l_int|0x55
)paren
op_logical_or
(paren
id|dev_netjet-&gt;subsystem_device
op_ne
l_int|0x02
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;enter:now: You tried to load this driver with an incompatible TigerJet-card&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Use type=20 for Traverse NetJet PCI Card.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;enter:now PCI: No PCI card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cs-&gt;hw.njet.auxa
op_assign
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_AUXDATA
suffix:semicolon
id|cs-&gt;hw.njet.isac
op_assign
id|cs-&gt;hw.njet.base
op_plus
l_int|0xC0
suffix:semicolon
singleline_comment|// Fenster zum AMD
multiline_comment|/* Reset an */
id|cs-&gt;hw.njet.ctrl_reg
op_assign
l_int|0x07
suffix:semicolon
singleline_comment|// ge&#xfffd;ndert von 0xff
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_CTRL
comma
id|cs-&gt;hw.njet.ctrl_reg
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
multiline_comment|/* 50 ms Pause */
id|schedule_timeout
c_func
(paren
(paren
l_int|50
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
id|cs-&gt;hw.njet.ctrl_reg
op_assign
l_int|0x30
suffix:semicolon
multiline_comment|/* Reset Off and status read clear */
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_CTRL
comma
id|cs-&gt;hw.njet.ctrl_reg
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
(paren
l_int|10
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
multiline_comment|/* Timeout 10ms */
id|cs-&gt;hw.njet.auxd
op_assign
l_int|0x00
suffix:semicolon
singleline_comment|// war 0xc0
id|cs-&gt;hw.njet.dmactrl
op_assign
l_int|0
suffix:semicolon
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_AUXCTRL
comma
op_complement
id|TJ_AMD_IRQ
)paren
suffix:semicolon
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_IRQMASK1
comma
id|TJ_AMD_IRQ
)paren
suffix:semicolon
id|OutByte
c_func
(paren
id|cs-&gt;hw.njet.auxa
comma
id|cs-&gt;hw.njet.auxd
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;enter:now PCI: PCI card configured at 0x%lx IRQ %d&bslash;n&quot;
comma
id|cs-&gt;hw.njet.base
comma
id|cs-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_io
c_func
(paren
op_amp
id|cs-&gt;rs
comma
id|cs-&gt;hw.njet.base
comma
l_int|0x100
comma
l_string|&quot;Fn_ISDN&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|reset_enpci
c_func
(paren
id|cs
)paren
suffix:semicolon
id|cs-&gt;hw.njet.last_is0
op_assign
l_int|0
suffix:semicolon
id|cs-&gt;hw.njet.bc_activate
op_assign
id|enpci_bc_activate
suffix:semicolon
id|cs-&gt;hw.njet.bc_deactivate
op_assign
id|enpci_bc_deactivate
suffix:semicolon
id|cs-&gt;dc_hw_ops
op_assign
op_amp
id|enternow_ops
suffix:semicolon
id|cs-&gt;dc.amd7930.setIrqMask
op_assign
op_amp
id|enpci_setIrqMask
suffix:semicolon
id|cs-&gt;cardmsg
op_assign
op_amp
id|enpci_card_msg
suffix:semicolon
id|cs-&gt;irq_flags
op_or_assign
id|SA_SHIRQ
suffix:semicolon
id|cs-&gt;card_ops
op_assign
op_amp
id|enpci_ops
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
