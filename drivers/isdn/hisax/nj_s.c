multiline_comment|/* $Id: nj_s.c,v 2.7.6.6 2001/09/23 22:24:50 kai Exp $&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ppp_defs.h&gt;
macro_line|#include &quot;netjet.h&quot;
DECL|variable|NETjet_S_revision
r_const
r_char
op_star
id|NETjet_S_revision
op_assign
l_string|&quot;$Revision: 2.7.6.6 $&quot;
suffix:semicolon
r_static
r_void
DECL|function|nj_s_interrupt
id|nj_s_interrupt
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
id|u8
id|val
comma
id|sval
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|cs-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|sval
op_assign
id|bytein
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_IRQSTAT1
)paren
)paren
op_amp
id|NETJET_ISACIRQ
)paren
)paren
(brace
id|val
op_assign
id|NETjet_ReadIC
c_func
(paren
id|cs
comma
id|ISAC_ISTA
)paren
suffix:semicolon
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
l_string|&quot;tiger: i1 %x %x&quot;
comma
id|sval
comma
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
id|isac_interrupt
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
id|NETjet_WriteIC
c_func
(paren
id|cs
comma
id|ISAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|NETjet_WriteIC
c_func
(paren
id|cs
comma
id|ISAC_MASK
comma
l_int|0x0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* start new code 13/07/00 GE */
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
multiline_comment|/* we have a DMA interrupt */
(brace
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
multiline_comment|/* end new code 13/07/00 GE */
)brace
multiline_comment|/*&t;if (!testcnt--) {&n;&t;&t;cs-&gt;hw.njet.dmactrl = 0;&n;&t;&t;byteout(cs-&gt;hw.njet.base + NETJET_DMACTRL,&n;&t;&t;&t;cs-&gt;hw.njet.dmactrl);&n;&t;&t;byteout(cs-&gt;hw.njet.base + NETJET_IRQMASK0, 0);&n;&t;}&n;*/
id|spin_unlock
c_func
(paren
op_amp
id|cs-&gt;lock
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|nj_s_reset
id|nj_s_reset
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|cs-&gt;hw.njet.ctrl_reg
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* Reset On */
id|byteout
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
id|cs-&gt;hw.njet.ctrl_reg
op_assign
l_int|0x40
suffix:semicolon
multiline_comment|/* Reset Off and status read clear */
multiline_comment|/* now edge triggered for TJ320 GE 13/07/00 */
id|byteout
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
l_int|0
suffix:semicolon
id|cs-&gt;hw.njet.dmactrl
op_assign
l_int|0
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_AUXCTRL
comma
op_complement
id|NETJET_ISACIRQ
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_IRQMASK1
comma
id|NETJET_ISACIRQ
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.njet.auxa
comma
id|cs-&gt;hw.njet.auxd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|nj_s_init
id|nj_s_init
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
id|initisac
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
DECL|variable|nj_s_ops
r_static
r_struct
id|card_ops
id|nj_s_ops
op_assign
(brace
dot
id|init
op_assign
id|nj_s_init
comma
dot
id|reset
op_assign
id|nj_s_reset
comma
dot
id|release
op_assign
id|netjet_release
comma
dot
id|irq_func
op_assign
id|nj_s_interrupt
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
r_int
id|__init
DECL|function|setup_netjet_s
id|setup_netjet_s
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
id|NETjet_S_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Traverse Tech. NETjet-S driver Rev. %s&bslash;n&quot;
comma
id|HiSax_getrev
c_func
(paren
id|tmp
)paren
)paren
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
id|pci_set_master
c_func
(paren
id|dev_netjet
)paren
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
l_string|&quot;NETjet-S: No IRQ for PCI card found&bslash;n&quot;
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
l_string|&quot;NETjet-S: No IO-Adr for PCI card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* 2001/10/04 Christoph Ersfeld, Formula-n Europe AG www.formula-n.com */
r_if
c_cond
(paren
(paren
id|dev_netjet-&gt;subsystem_vendor
op_eq
l_int|0x55
)paren
op_logical_and
(paren
id|dev_netjet-&gt;subsystem_device
op_eq
l_int|0x02
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Netjet: You tried to load this driver with an incompatible TigerJet-card&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Use type=41 for Formula-n enter:now ISDN PCI and compatible&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end new code */
id|cs-&gt;hw.njet.pdev
op_assign
id|dev_netjet
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;NETjet-S: No PCI card found&bslash;n&quot;
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
op_or
id|NETJET_ISAC_OFF
suffix:semicolon
id|cs-&gt;hw.njet.ctrl_reg
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* Reset On */
id|byteout
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
id|cs-&gt;hw.njet.ctrl_reg
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Reset Off and status read clear */
id|byteout
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
l_int|0xC0
suffix:semicolon
id|cs-&gt;hw.njet.dmactrl
op_assign
l_int|0
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_AUXCTRL
comma
op_complement
id|NETJET_ISACIRQ
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.njet.base
op_plus
id|NETJET_IRQMASK1
comma
id|NETJET_ISACIRQ
)paren
suffix:semicolon
id|byteout
c_func
(paren
id|cs-&gt;hw.njet.auxa
comma
id|cs-&gt;hw.njet.auxd
)paren
suffix:semicolon
r_switch
c_cond
(paren
(paren
(paren
id|NETjet_ReadIC
c_func
(paren
id|cs
comma
id|ISAC_RBCH
)paren
op_rshift
l_int|5
)paren
op_amp
l_int|3
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;NETjet-S: NETspider-U PCI card found&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;NETjet-S: No PCI card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;NETjet-S: PCI card configured at %#lx IRQ %d&bslash;n&quot;
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
l_string|&quot;netjet-s isdn&quot;
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|nj_s_reset
c_func
(paren
id|cs
)paren
suffix:semicolon
id|cs-&gt;irq_flags
op_or_assign
id|SA_SHIRQ
suffix:semicolon
id|cs-&gt;card_ops
op_assign
op_amp
id|nj_s_ops
suffix:semicolon
id|isac_setup
c_func
(paren
id|cs
comma
op_amp
id|netjet_dc_ops
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
