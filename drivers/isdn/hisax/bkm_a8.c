multiline_comment|/* $Id: bkm_a8.c,v 1.14.6.7 2001/09/23 22:24:46 kai Exp $&n; *&n; * low level stuff for Scitel Quadro (4*S0, passive)&n; *&n; * Author       Roland Klabunde&n; * Copyright    by Roland Klabunde   &lt;R.Klabunde@Berkom.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;isac.h&quot;
macro_line|#include &quot;ipac.h&quot;
macro_line|#include &quot;hscx.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;bkm_ax.h&quot;
macro_line|#if CONFIG_PCI
DECL|macro|ATTEMPT_PCI_REMAPPING
mdefine_line|#define&t;ATTEMPT_PCI_REMAPPING&t;/* Required for PLX rev 1 */
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|bkm_a8_lock
r_static
id|spinlock_t
id|bkm_a8_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|sct_quadro_revision
r_const
r_char
id|sct_quadro_revision
(braket
)braket
op_assign
l_string|&quot;$Revision: 1.14.6.7 $&quot;
suffix:semicolon
DECL|variable|sct_quadro_subtypes
r_static
r_const
r_char
op_star
id|sct_quadro_subtypes
(braket
)braket
op_assign
(brace
l_string|&quot;&quot;
comma
l_string|&quot;#1&quot;
comma
l_string|&quot;#2&quot;
comma
l_string|&quot;#3&quot;
comma
l_string|&quot;#4&quot;
)brace
suffix:semicolon
DECL|macro|wordout
mdefine_line|#define wordout(addr,val) outw(val,addr)
DECL|macro|wordin
mdefine_line|#define wordin(addr) inw(addr)
r_static
r_inline
id|u8
DECL|function|ipac_read
id|ipac_read
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u8
id|off
)paren
(brace
id|u8
id|ret
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|bkm_a8_lock
comma
id|flags
)paren
suffix:semicolon
id|wordout
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|off
)paren
suffix:semicolon
id|ret
op_assign
id|wordin
c_func
(paren
id|cs-&gt;hw.ax.data_adr
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|bkm_a8_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ipac_write
id|ipac_write
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u8
id|off
comma
id|u8
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|bkm_a8_lock
comma
id|flags
)paren
suffix:semicolon
id|wordout
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|off
)paren
suffix:semicolon
id|wordout
c_func
(paren
id|cs-&gt;hw.ax.data_adr
comma
id|data
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|bkm_a8_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ipac_readfifo
id|ipac_readfifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u8
id|off
comma
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
r_int
id|i
suffix:semicolon
id|wordout
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|off
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
id|size
suffix:semicolon
id|i
op_increment
)paren
id|data
(braket
id|i
)braket
op_assign
id|wordin
c_func
(paren
id|cs-&gt;hw.ax.data_adr
)paren
op_amp
l_int|0xFF
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ipac_writefifo
id|ipac_writefifo
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u8
id|off
comma
id|u8
op_star
id|data
comma
r_int
id|size
)paren
(brace
r_int
id|i
suffix:semicolon
id|wordout
c_func
(paren
id|cs-&gt;hw.ax.base
comma
id|off
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
id|size
suffix:semicolon
id|i
op_increment
)paren
id|wordout
c_func
(paren
id|cs-&gt;hw.ax.data_adr
comma
id|data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* This will generate ipac_dc_ops and ipac_bc_ops using the functions&n; * above */
DECL|variable|ipac
id|BUILD_IPAC_OPS
c_func
(paren
id|ipac
)paren
suffix:semicolon
multiline_comment|/* Set the specific ipac to active */
r_static
r_void
DECL|function|set_ipac_active
id|set_ipac_active
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
id|u_int
id|active
)paren
(brace
multiline_comment|/* set irq mask */
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_MASK
comma
id|active
ques
c_cond
l_int|0xc0
suffix:colon
l_int|0xff
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|enable_bkm_int
id|enable_bkm_int
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|bEnable
)paren
(brace
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_SCT_QUADRO
)paren
(brace
r_if
c_cond
(paren
id|bEnable
)paren
id|wordout
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x4C
comma
(paren
id|wordin
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x4C
)paren
op_or
l_int|0x41
)paren
)paren
suffix:semicolon
r_else
id|wordout
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x4C
comma
(paren
id|wordin
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x4C
)paren
op_amp
op_complement
l_int|0x41
)paren
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|reset_bkm
id|reset_bkm
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
id|cs-&gt;subtyp
op_eq
id|SCT_1
)paren
(brace
id|wordout
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x50
comma
(paren
id|wordin
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x50
)paren
op_amp
op_complement
l_int|4
)paren
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
multiline_comment|/* Remove the soft reset */
id|wordout
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x50
comma
(paren
id|wordin
c_func
(paren
id|cs-&gt;hw.ax.plx_adr
op_plus
l_int|0x50
)paren
op_or
l_int|4
)paren
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
)brace
)brace
r_static
r_int
DECL|function|BKM_card_msg
id|BKM_card_msg
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
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|bkm_a8_init
id|bkm_a8_init
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|cs-&gt;debug
op_or_assign
id|L1_DEB_IPAC
suffix:semicolon
id|set_ipac_active
c_func
(paren
id|cs
comma
l_int|1
)paren
suffix:semicolon
id|ipac_init
c_func
(paren
id|cs
)paren
suffix:semicolon
multiline_comment|/* Enable ints */
id|enable_bkm_int
c_func
(paren
id|cs
comma
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|bkm_a8_reset
id|bkm_a8_reset
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
multiline_comment|/* Disable ints */
id|set_ipac_active
c_func
(paren
id|cs
comma
l_int|0
)paren
suffix:semicolon
id|enable_bkm_int
c_func
(paren
id|cs
comma
l_int|0
)paren
suffix:semicolon
id|reset_bkm
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
DECL|function|bkm_a8_release
id|bkm_a8_release
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|set_ipac_active
c_func
(paren
id|cs
comma
l_int|0
)paren
suffix:semicolon
id|enable_bkm_int
c_func
(paren
id|cs
comma
l_int|0
)paren
suffix:semicolon
id|hisax_release_resources
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
DECL|variable|bkm_a8_ops
r_static
r_struct
id|card_ops
id|bkm_a8_ops
op_assign
(brace
dot
id|init
op_assign
id|bkm_a8_init
comma
dot
id|reset
op_assign
id|bkm_a8_reset
comma
dot
id|release
op_assign
id|bkm_a8_release
comma
dot
id|irq_func
op_assign
id|ipac_irq
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|pci_dev
op_star
id|dev_a8
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|__initdata
r_static
id|u16
id|sub_vendor_id
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
id|u16
id|sub_sys_id
id|__initdata
op_assign
l_int|0
suffix:semicolon
DECL|variable|__initdata
r_static
id|u8
id|pci_irq
id|__initdata
op_assign
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_PCI */
r_int
id|__init
DECL|function|setup_sct_quadro
id|setup_sct_quadro
c_func
(paren
r_struct
id|IsdnCard
op_star
id|card
)paren
(brace
macro_line|#if CONFIG_PCI
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
id|u8
id|pci_rev_id
suffix:semicolon
id|u_int
id|found
op_assign
l_int|0
suffix:semicolon
id|u_int
id|pci_ioaddr1
comma
id|pci_ioaddr2
comma
id|pci_ioaddr3
comma
id|pci_ioaddr4
comma
id|pci_ioaddr5
suffix:semicolon
id|strcpy
c_func
(paren
id|tmp
comma
id|sct_quadro_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: T-Berkom driver Rev. %s&bslash;n&quot;
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
op_eq
id|ISDN_CTYPE_SCT_QUADRO
)paren
(brace
id|cs-&gt;subtyp
op_assign
id|SCT_1
suffix:semicolon
multiline_comment|/* Preset */
)brace
r_else
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Identify subtype by para[0] */
r_if
c_cond
(paren
id|card-&gt;para
(braket
l_int|0
)braket
op_ge
id|SCT_1
op_logical_and
id|card-&gt;para
(braket
l_int|0
)braket
op_le
id|SCT_4
)paren
id|cs-&gt;subtyp
op_assign
id|card-&gt;para
(braket
l_int|0
)braket
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s: Invalid subcontroller in configuration, default to 1&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|cs-&gt;subtyp
op_ne
id|SCT_1
)paren
op_logical_and
(paren
(paren
id|sub_sys_id
op_ne
id|PCI_DEVICE_ID_BERKOM_SCITEL_QUADRO
)paren
op_logical_or
(paren
id|sub_vendor_id
op_ne
id|PCI_VENDOR_ID_BERKOM
)paren
)paren
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;subtyp
op_eq
id|SCT_1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pci_present
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;bkm_a4t: no PCI bus present&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|dev_a8
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_PLX
comma
id|PCI_DEVICE_ID_PLX_9050
comma
id|dev_a8
)paren
)paren
)paren
(brace
id|sub_vendor_id
op_assign
id|dev_a8-&gt;subsystem_vendor
suffix:semicolon
id|sub_sys_id
op_assign
id|dev_a8-&gt;subsystem_device
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sub_sys_id
op_eq
id|PCI_DEVICE_ID_BERKOM_SCITEL_QUADRO
)paren
op_logical_and
(paren
id|sub_vendor_id
op_eq
id|PCI_VENDOR_ID_BERKOM
)paren
)paren
(brace
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|dev_a8
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|pci_ioaddr1
op_assign
id|pci_resource_start
c_func
(paren
id|dev_a8
comma
l_int|1
)paren
suffix:semicolon
id|pci_irq
op_assign
id|dev_a8-&gt;irq
suffix:semicolon
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s (%s): Card not found&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|sct_quadro_subtypes
(braket
id|cs-&gt;subtyp
)braket
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef ATTEMPT_PCI_REMAPPING
multiline_comment|/* HACK: PLX revision 1 bug: PLX address bit 7 must not be set */
id|pci_read_config_byte
c_func
(paren
id|dev_a8
comma
id|PCI_REVISION_ID
comma
op_amp
id|pci_rev_id
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pci_ioaddr1
op_amp
l_int|0x80
)paren
op_logical_and
(paren
id|pci_rev_id
op_eq
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s (%s): PLX rev 1, remapping required!&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|sct_quadro_subtypes
(braket
id|cs-&gt;subtyp
)braket
)paren
suffix:semicolon
multiline_comment|/* Restart PCI negotiation */
id|pci_write_config_dword
c_func
(paren
id|dev_a8
comma
id|PCI_BASE_ADDRESS_1
comma
(paren
id|u_int
)paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Move up by 0x80 byte */
id|pci_ioaddr1
op_add_assign
l_int|0x80
suffix:semicolon
id|pci_ioaddr1
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev_a8
comma
id|PCI_BASE_ADDRESS_1
comma
id|pci_ioaddr1
)paren
suffix:semicolon
id|dev_a8-&gt;resource
(braket
l_int|1
)braket
dot
id|start
op_assign
id|pci_ioaddr1
suffix:semicolon
)brace
macro_line|#endif /* End HACK */
)brace
r_if
c_cond
(paren
op_logical_neg
id|pci_irq
)paren
(brace
multiline_comment|/* IRQ range check ?? */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s (%s): No IRQ&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|sct_quadro_subtypes
(braket
id|cs-&gt;subtyp
)braket
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|pci_read_config_dword
c_func
(paren
id|dev_a8
comma
id|PCI_BASE_ADDRESS_1
comma
op_amp
id|pci_ioaddr1
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev_a8
comma
id|PCI_BASE_ADDRESS_2
comma
op_amp
id|pci_ioaddr2
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev_a8
comma
id|PCI_BASE_ADDRESS_3
comma
op_amp
id|pci_ioaddr3
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev_a8
comma
id|PCI_BASE_ADDRESS_4
comma
op_amp
id|pci_ioaddr4
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev_a8
comma
id|PCI_BASE_ADDRESS_5
comma
op_amp
id|pci_ioaddr5
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_ioaddr1
op_logical_or
op_logical_neg
id|pci_ioaddr2
op_logical_or
op_logical_neg
id|pci_ioaddr3
op_logical_or
op_logical_neg
id|pci_ioaddr4
op_logical_or
op_logical_neg
id|pci_ioaddr5
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s (%s): No IO base address(es)&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|sct_quadro_subtypes
(braket
id|cs-&gt;subtyp
)braket
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|pci_ioaddr1
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|pci_ioaddr2
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|pci_ioaddr3
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|pci_ioaddr4
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
id|pci_ioaddr5
op_and_assign
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
multiline_comment|/* Take over */
id|cs-&gt;irq
op_assign
id|pci_irq
suffix:semicolon
id|cs-&gt;irq_flags
op_or_assign
id|SA_SHIRQ
suffix:semicolon
multiline_comment|/* pci_ioaddr1 is unique to all subdevices */
multiline_comment|/* pci_ioaddr2 is for the fourth subdevice only */
multiline_comment|/* pci_ioaddr3 is for the third subdevice only */
multiline_comment|/* pci_ioaddr4 is for the second subdevice only */
multiline_comment|/* pci_ioaddr5 is for the first subdevice only */
id|cs-&gt;hw.ax.plx_adr
op_assign
id|pci_ioaddr1
suffix:semicolon
multiline_comment|/* Enter all ipac_base addresses */
r_switch
c_cond
(paren
id|cs-&gt;subtyp
)paren
(brace
r_case
l_int|1
suffix:colon
id|cs-&gt;hw.ax.base
op_assign
id|pci_ioaddr5
op_plus
l_int|0x00
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
id|pci_ioaddr1
comma
l_int|128
comma
l_string|&quot;scitel&quot;
)paren
)paren
r_goto
id|err
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
id|pci_ioaddr5
comma
l_int|64
comma
l_string|&quot;scitel&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|cs-&gt;hw.ax.base
op_assign
id|pci_ioaddr4
op_plus
l_int|0x08
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
id|pci_ioaddr4
comma
l_int|64
comma
l_string|&quot;scitel&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|cs-&gt;hw.ax.base
op_assign
id|pci_ioaddr3
op_plus
l_int|0x10
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
id|pci_ioaddr3
comma
l_int|64
comma
l_string|&quot;scitel&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|cs-&gt;hw.ax.base
op_assign
id|pci_ioaddr2
op_plus
l_int|0x20
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
id|pci_ioaddr2
comma
l_int|64
comma
l_string|&quot;scitel&quot;
)paren
)paren
r_goto
id|err
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cs-&gt;hw.ax.data_adr
op_assign
id|cs-&gt;hw.ax.base
op_plus
l_int|4
suffix:semicolon
id|ipac_write
c_func
(paren
id|cs
comma
id|IPAC_MASK
comma
l_int|0xFF
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s (%s) configured at 0x%.4lX, 0x%.4lX, 0x%.4lX and IRQ %d&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|sct_quadro_subtypes
(braket
id|cs-&gt;subtyp
)braket
comma
id|cs-&gt;hw.ax.plx_adr
comma
id|cs-&gt;hw.ax.base
comma
id|cs-&gt;hw.ax.data_adr
comma
id|cs-&gt;irq
)paren
suffix:semicolon
id|cs-&gt;dc_hw_ops
op_assign
op_amp
id|ipac_dc_ops
suffix:semicolon
id|cs-&gt;bc_hw_ops
op_assign
op_amp
id|ipac_bc_ops
suffix:semicolon
id|cs-&gt;cardmsg
op_assign
op_amp
id|BKM_card_msg
suffix:semicolon
id|cs-&gt;card_ops
op_assign
op_amp
id|bkm_a8_ops
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s (%s): IPAC Version %d&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|sct_quadro_subtypes
(braket
id|cs-&gt;subtyp
)braket
comma
id|ipac_read
c_func
(paren
id|cs
comma
id|IPAC_ID
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;HiSax: bkm_a8 only supported on PCI Systems&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PCI */
id|err
suffix:colon
id|hisax_release_resources
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
