multiline_comment|/* $Id: hfcscard.c,v 1.8.6.2 2001/09/23 22:24:48 kai Exp $&n; *&n; * low level stuff for hfcs based cards (Teles3c, ACER P10)&n; *&n; * Author       Karsten Keil&n; * Copyright    by Karsten Keil      &lt;keil@isdn4linux.de&gt;&n; * &n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/isapnp.h&gt;
macro_line|#include &quot;hisax.h&quot;
macro_line|#include &quot;hfc_2bds0.h&quot;
macro_line|#include &quot;isdnl1.h&quot;
r_extern
r_const
r_char
op_star
id|CardType
(braket
)braket
suffix:semicolon
DECL|variable|hfcs_revision
r_static
r_const
r_char
op_star
id|hfcs_revision
op_assign
l_string|&quot;$Revision: 1.8.6.2 $&quot;
suffix:semicolon
r_static
r_inline
id|u8
DECL|function|hfcs_read_reg
id|hfcs_read_reg
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|data
comma
id|u8
id|reg
)paren
(brace
r_return
id|cs
op_member_access_from_pointer
id|BC_Read_Reg
c_func
(paren
id|cs
comma
id|data
comma
id|reg
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|hfcs_write_reg
id|hfcs_write_reg
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
comma
r_int
id|data
comma
id|u8
id|reg
comma
id|u8
id|val
)paren
(brace
id|cs
op_member_access_from_pointer
id|BC_Write_Reg
c_func
(paren
id|cs
comma
id|data
comma
id|reg
comma
id|val
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|hfcs_interrupt
id|hfcs_interrupt
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
id|u_char
id|val
comma
id|stat
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cs
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HFCS: Spurious interrupt!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|HFCD_ANYINT
op_or
id|HFCD_BUSY_NBUSY
)paren
op_amp
(paren
id|stat
op_assign
id|hfcs_read_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_STAT
)paren
)paren
)paren
(brace
id|val
op_assign
id|hfcs_read_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_INT_S1
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
l_string|&quot;HFCS: stat(%02x) s1(%02x)&quot;
comma
id|stat
comma
id|val
)paren
suffix:semicolon
id|hfc2bds0_interrupt
c_func
(paren
id|cs
comma
id|val
)paren
suffix:semicolon
)brace
r_else
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
l_string|&quot;HFCS: irq_no_irq stat(%02x)&quot;
comma
id|stat
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|hfcs_Timer
id|hfcs_Timer
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|cs-&gt;hw.hfcD.timer.expires
op_assign
id|jiffies
op_plus
l_int|75
suffix:semicolon
multiline_comment|/* WD RESET */
multiline_comment|/*&t;WriteReg(cs, HFCD_DATA, HFCD_CTMT, cs-&gt;hw.hfcD.ctmt | 0x80);&n;&t;add_timer(&amp;cs-&gt;hw.hfcD.timer);&n;*/
)brace
r_void
DECL|function|release_io_hfcs
id|release_io_hfcs
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|release2bds0
c_func
(paren
id|cs
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|cs-&gt;hw.hfcD.timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;hw.hfcD.addr
)paren
id|release_region
c_func
(paren
id|cs-&gt;hw.hfcD.addr
comma
l_int|2
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|reset_hfcs
id|reset_hfcs
c_func
(paren
r_struct
id|IsdnCardState
op_star
id|cs
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HFCS: resetting card&bslash;n&quot;
)paren
suffix:semicolon
id|cs-&gt;hw.hfcD.cirm
op_assign
id|HFCD_RESET
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_TELES3C
)paren
id|cs-&gt;hw.hfcD.cirm
op_or_assign
id|HFCD_MEM8K
suffix:semicolon
id|hfcs_write_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_CIRM
comma
id|cs-&gt;hw.hfcD.cirm
)paren
suffix:semicolon
multiline_comment|/* Reset On */
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
l_int|30
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
id|cs-&gt;hw.hfcD.cirm
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_TELES3C
)paren
id|cs-&gt;hw.hfcD.cirm
op_or_assign
id|HFCD_MEM8K
suffix:semicolon
id|hfcs_write_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_CIRM
comma
id|cs-&gt;hw.hfcD.cirm
)paren
suffix:semicolon
multiline_comment|/* Reset Off */
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
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_TELES3C
)paren
id|cs-&gt;hw.hfcD.cirm
op_or_assign
id|HFCD_INTB
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_ACERP10
)paren
id|cs-&gt;hw.hfcD.cirm
op_or_assign
id|HFCD_INTA
suffix:semicolon
id|hfcs_write_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_CIRM
comma
id|cs-&gt;hw.hfcD.cirm
)paren
suffix:semicolon
id|hfcs_write_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_CLKDEL
comma
l_int|0x0e
)paren
suffix:semicolon
id|hfcs_write_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_TEST
comma
id|HFCD_AUTO_AWAKE
)paren
suffix:semicolon
multiline_comment|/* S/T Auto awake */
id|cs-&gt;hw.hfcD.ctmt
op_assign
id|HFCD_TIM25
op_or
id|HFCD_AUTO_TIMER
suffix:semicolon
id|hfcs_write_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_CTMT
comma
id|cs-&gt;hw.hfcD.ctmt
)paren
suffix:semicolon
id|cs-&gt;hw.hfcD.int_m2
op_assign
id|HFCD_IRQ_ENABLE
suffix:semicolon
id|cs-&gt;hw.hfcD.int_m1
op_assign
id|HFCD_INTS_B1TRANS
op_or
id|HFCD_INTS_B2TRANS
op_or
id|HFCD_INTS_DTRANS
op_or
id|HFCD_INTS_B1REC
op_or
id|HFCD_INTS_B2REC
op_or
id|HFCD_INTS_DREC
op_or
id|HFCD_INTS_L1STATE
suffix:semicolon
id|hfcs_write_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_INT_M1
comma
id|cs-&gt;hw.hfcD.int_m1
)paren
suffix:semicolon
id|hfcs_write_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_INT_M2
comma
id|cs-&gt;hw.hfcD.int_m2
)paren
suffix:semicolon
id|hfcs_write_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_STATES
comma
id|HFCD_LOAD_STATE
op_or
l_int|2
)paren
suffix:semicolon
multiline_comment|/* HFC ST 2 */
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|hfcs_write_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_STATES
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* HFC ST 2 */
id|cs-&gt;hw.hfcD.mst_m
op_assign
id|HFCD_MASTER
suffix:semicolon
id|hfcs_write_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_MST_MODE
comma
id|cs-&gt;hw.hfcD.mst_m
)paren
suffix:semicolon
multiline_comment|/* HFC Master */
id|cs-&gt;hw.hfcD.sctrl
op_assign
l_int|0
suffix:semicolon
id|hfcs_write_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_SCTRL
comma
id|cs-&gt;hw.hfcD.sctrl
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|hfcs_card_msg
id|hfcs_card_msg
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
l_string|&quot;HFCS: card_msg %x&quot;
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
id|CARD_RESET
suffix:colon
id|reset_hfcs
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_RELEASE
suffix:colon
id|release_io_hfcs
c_func
(paren
id|cs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_INIT
suffix:colon
id|cs-&gt;hw.hfcD.timer.expires
op_assign
id|jiffies
op_plus
l_int|75
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|cs-&gt;hw.hfcD.timer
)paren
suffix:semicolon
id|init2bds0
c_func
(paren
id|cs
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
l_int|80
op_star
id|HZ
)paren
op_div
l_int|1000
)paren
suffix:semicolon
id|cs-&gt;hw.hfcD.ctmt
op_or_assign
id|HFCD_TIM800
suffix:semicolon
id|hfcs_write_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_CTMT
comma
id|cs-&gt;hw.hfcD.ctmt
)paren
suffix:semicolon
id|hfcs_write_reg
c_func
(paren
id|cs
comma
id|HFCD_DATA
comma
id|HFCD_MST_MODE
comma
id|cs-&gt;hw.hfcD.mst_m
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CARD_TEST
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef __ISAPNP__
DECL|variable|__initdata
r_static
r_struct
id|isapnp_device_id
id|hfc_ids
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_char|&squot;N&squot;
comma
l_char|&squot;X&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x1114
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;A&squot;
comma
l_char|&squot;N&squot;
comma
l_char|&squot;X&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x1114
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;Acer P10&quot;
)brace
comma
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;B&squot;
comma
l_char|&squot;I&squot;
comma
l_char|&squot;L&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0002
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;B&squot;
comma
l_char|&squot;I&squot;
comma
l_char|&squot;L&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0002
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;Billion 2&quot;
)brace
comma
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;B&squot;
comma
l_char|&squot;I&squot;
comma
l_char|&squot;L&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0001
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;B&squot;
comma
l_char|&squot;I&squot;
comma
l_char|&squot;L&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0001
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;Billion 1&quot;
)brace
comma
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;T&squot;
comma
l_char|&squot;A&squot;
comma
l_char|&squot;G&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x7410
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;T&squot;
comma
l_char|&squot;A&squot;
comma
l_char|&squot;G&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x7410
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;IStar PnP&quot;
)brace
comma
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;T&squot;
comma
l_char|&squot;A&squot;
comma
l_char|&squot;G&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x2610
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;T&squot;
comma
l_char|&squot;A&squot;
comma
l_char|&squot;G&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x2610
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;Teles 16.3c&quot;
)brace
comma
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;F&squot;
comma
l_char|&squot;M&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0001
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;F&squot;
comma
l_char|&squot;M&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0001
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;Tornado Tipa C&quot;
)brace
comma
(brace
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;K&squot;
comma
l_char|&squot;Y&squot;
comma
l_char|&squot;E&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0001
)paren
comma
id|ISAPNP_VENDOR
c_func
(paren
l_char|&squot;K&squot;
comma
l_char|&squot;Y&squot;
comma
l_char|&squot;E&squot;
)paren
comma
id|ISAPNP_FUNCTION
c_func
(paren
l_int|0x0001
)paren
comma
(paren
r_int
r_int
)paren
l_string|&quot;Genius Speed Surfer&quot;
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|variable|hdev
r_static
r_struct
id|isapnp_device_id
op_star
id|hdev
op_assign
op_amp
id|hfc_ids
(braket
l_int|0
)braket
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|pci_bus
op_star
id|pnp_c
id|__devinitdata
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
r_int
id|__init
DECL|function|setup_hfcs
id|setup_hfcs
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
id|strcpy
c_func
(paren
id|tmp
comma
id|hfcs_revision
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: HFC-S driver Rev. %s&bslash;n&quot;
comma
id|HiSax_getrev
c_func
(paren
id|tmp
)paren
)paren
suffix:semicolon
macro_line|#ifdef __ISAPNP__
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;para
(braket
l_int|1
)braket
op_logical_and
id|isapnp_present
c_func
(paren
)paren
)paren
(brace
r_struct
id|pci_bus
op_star
id|pb
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pd
suffix:semicolon
r_while
c_loop
(paren
id|hdev-&gt;card_vendor
)paren
(brace
r_if
c_cond
(paren
(paren
id|pb
op_assign
id|isapnp_find_card
c_func
(paren
id|hdev-&gt;card_vendor
comma
id|hdev-&gt;card_device
comma
id|pnp_c
)paren
)paren
)paren
(brace
id|pnp_c
op_assign
id|pb
suffix:semicolon
id|pd
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pd
op_assign
id|isapnp_find_dev
c_func
(paren
id|pnp_c
comma
id|hdev-&gt;vendor
comma
id|hdev-&gt;function
comma
id|pd
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: %s detected&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
id|hdev-&gt;driver_data
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|prepare
c_func
(paren
id|pd
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|deactivate
c_func
(paren
id|pd
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|activate
c_func
(paren
id|pd
)paren
suffix:semicolon
id|card-&gt;para
(braket
l_int|1
)braket
op_assign
id|pd-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|card-&gt;para
(braket
l_int|0
)braket
op_assign
id|pd-&gt;irq_resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;para
(braket
l_int|0
)braket
op_logical_or
op_logical_neg
id|card-&gt;para
(braket
l_int|1
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;HFC PnP:some resources are missing %ld/%lx&bslash;n&quot;
comma
id|card-&gt;para
(braket
l_int|0
)braket
comma
id|card-&gt;para
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|pd
op_member_access_from_pointer
id|deactivate
c_func
(paren
id|pd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;HFC PnP: PnP error card found, no device&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|hdev
op_increment
suffix:semicolon
id|pnp_c
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|hdev-&gt;card_vendor
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HFC PnP: no ISAPnP card found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
id|cs-&gt;hw.hfcD.addr
op_assign
id|card-&gt;para
(braket
l_int|1
)braket
op_amp
l_int|0xfffe
suffix:semicolon
id|cs-&gt;irq
op_assign
id|card-&gt;para
(braket
l_int|0
)braket
suffix:semicolon
id|cs-&gt;hw.hfcD.cip
op_assign
l_int|0
suffix:semicolon
id|cs-&gt;hw.hfcD.int_s1
op_assign
l_int|0
suffix:semicolon
id|cs-&gt;hw.hfcD.send
op_assign
l_int|NULL
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|0
)braket
dot
id|hw.hfc.send
op_assign
l_int|NULL
suffix:semicolon
id|cs-&gt;bcs
(braket
l_int|1
)braket
dot
id|hw.hfc.send
op_assign
l_int|NULL
suffix:semicolon
id|cs-&gt;hw.hfcD.dfifosize
op_assign
l_int|512
suffix:semicolon
id|cs-&gt;dc.hfcd.ph_state
op_assign
l_int|0
suffix:semicolon
id|cs-&gt;hw.hfcD.fifo
op_assign
l_int|255
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_TELES3C
)paren
(brace
id|cs-&gt;hw.hfcD.bfifosize
op_assign
l_int|1024
op_plus
l_int|512
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_ACERP10
)paren
(brace
id|cs-&gt;hw.hfcD.bfifosize
op_assign
l_int|7
op_star
l_int|1024
op_plus
l_int|512
suffix:semicolon
)brace
r_else
r_return
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
(paren
id|cs-&gt;hw.hfcD.addr
)paren
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;HiSax: %s config port %x-%x already in use&bslash;n&quot;
comma
id|CardType
(braket
id|card-&gt;typ
)braket
comma
id|cs-&gt;hw.hfcD.addr
comma
id|cs-&gt;hw.hfcD.addr
op_plus
l_int|2
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|request_region
c_func
(paren
id|cs-&gt;hw.hfcD.addr
comma
l_int|2
comma
l_string|&quot;HFCS isdn&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HFCS: defined at 0x%x IRQ %d HZ %d&bslash;n&quot;
comma
id|cs-&gt;hw.hfcD.addr
comma
id|cs-&gt;irq
comma
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_TELES3C
)paren
(brace
multiline_comment|/* Teles 16.3c IO ADR is 0x200 | YY0U (YY Bit 15/14 address) */
id|outb
c_func
(paren
l_int|0x00
comma
id|cs-&gt;hw.hfcD.addr
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x56
comma
id|cs-&gt;hw.hfcD.addr
op_or
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cs-&gt;typ
op_eq
id|ISDN_CTYPE_ACERP10
)paren
(brace
multiline_comment|/* Acer P10 IO ADR is 0x300 */
id|outb
c_func
(paren
l_int|0x00
comma
id|cs-&gt;hw.hfcD.addr
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x57
comma
id|cs-&gt;hw.hfcD.addr
op_or
l_int|1
)paren
suffix:semicolon
)brace
id|set_cs_func
c_func
(paren
id|cs
)paren
suffix:semicolon
id|cs-&gt;hw.hfcD.timer.function
op_assign
(paren
r_void
op_star
)paren
id|hfcs_Timer
suffix:semicolon
id|cs-&gt;hw.hfcD.timer.data
op_assign
(paren
r_int
)paren
id|cs
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|cs-&gt;hw.hfcD.timer
)paren
suffix:semicolon
id|reset_hfcs
c_func
(paren
id|cs
)paren
suffix:semicolon
id|cs-&gt;cardmsg
op_assign
op_amp
id|hfcs_card_msg
suffix:semicolon
id|cs-&gt;irq_func
op_assign
op_amp
id|hfcs_interrupt
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
eof
