multiline_comment|/*&n; * budget.c: driver for the SAA7146 based Budget DVB cards &n; *&n; * Compiled from various sources by Michael Hunold &lt;michael@mihu.de&gt; &n; *&n; * Copyright (C) 2002 Ralph Metzler &lt;rjkm@metzlerbros.de&gt;&n; *&n; * Copyright (C) 1999-2002 Ralph  Metzler &n; *                       &amp; Marcus Metzler for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; * &n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; * Or, point your browser to http://www.gnu.org/copyleft/gpl.html&n; * &n; *&n; * the project&squot;s page is at http://www.linuxtv.org/dvb/&n; */
macro_line|#include &quot;budget.h&quot;
macro_line|#include &quot;dvb_functions.h&quot;
DECL|function|Set22K
r_static
r_void
id|Set22K
(paren
r_struct
id|budget
op_star
id|budget
comma
r_int
id|state
)paren
(brace
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|budget-&gt;dev
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
)paren
)paren
suffix:semicolon
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|3
comma
(paren
id|state
ques
c_cond
id|SAA7146_GPIO_OUTHI
suffix:colon
id|SAA7146_GPIO_OUTLO
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Diseqc functions only for TT Budget card */
multiline_comment|/* taken from the Skyvision DVB driver by&n;   Ralph Metzler &lt;rjkm@metzlerbros.de&gt; */
DECL|function|DiseqcSendBit
r_static
r_void
id|DiseqcSendBit
(paren
r_struct
id|budget
op_star
id|budget
comma
r_int
id|data
)paren
(brace
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|budget-&gt;dev
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
)paren
)paren
suffix:semicolon
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|3
comma
id|SAA7146_GPIO_OUTHI
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|data
ques
c_cond
l_int|500
suffix:colon
l_int|1000
)paren
suffix:semicolon
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|3
comma
id|SAA7146_GPIO_OUTLO
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|data
ques
c_cond
l_int|1000
suffix:colon
l_int|500
)paren
suffix:semicolon
)brace
DECL|function|DiseqcSendByte
r_static
r_void
id|DiseqcSendByte
(paren
r_struct
id|budget
op_star
id|budget
comma
r_int
id|data
)paren
(brace
r_int
id|i
comma
id|par
op_assign
l_int|1
comma
id|d
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|d
op_assign
(paren
id|data
op_rshift
id|i
)paren
op_amp
l_int|1
suffix:semicolon
id|par
op_xor_assign
id|d
suffix:semicolon
id|DiseqcSendBit
c_func
(paren
id|budget
comma
id|d
)paren
suffix:semicolon
)brace
id|DiseqcSendBit
c_func
(paren
id|budget
comma
id|par
)paren
suffix:semicolon
)brace
DECL|function|SendDiSEqCMsg
r_static
r_int
id|SendDiSEqCMsg
(paren
r_struct
id|budget
op_star
id|budget
comma
r_int
id|len
comma
id|u8
op_star
id|msg
comma
r_int
r_int
id|burst
)paren
(brace
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|budget-&gt;dev
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
)paren
)paren
suffix:semicolon
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|3
comma
id|SAA7146_GPIO_OUTLO
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|16
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
id|len
suffix:semicolon
id|i
op_increment
)paren
id|DiseqcSendByte
c_func
(paren
id|budget
comma
id|msg
(braket
id|i
)braket
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|burst
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|burst
)paren
id|DiseqcSendByte
c_func
(paren
id|budget
comma
l_int|0xff
)paren
suffix:semicolon
r_else
(brace
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|3
comma
id|SAA7146_GPIO_OUTHI
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|12500
)paren
suffix:semicolon
id|saa7146_setgpio
c_func
(paren
id|dev
comma
l_int|3
comma
id|SAA7146_GPIO_OUTLO
)paren
suffix:semicolon
)brace
id|dvb_delay
c_func
(paren
l_int|20
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|budget_diseqc_ioctl
r_int
id|budget_diseqc_ioctl
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|budget
op_star
id|budget
op_assign
id|fe-&gt;before_after_data
suffix:semicolon
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FE_SET_TONE
suffix:colon
r_switch
c_cond
(paren
(paren
id|fe_sec_tone_mode_t
)paren
id|arg
)paren
(brace
r_case
id|SEC_TONE_ON
suffix:colon
id|Set22K
(paren
id|budget
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SEC_TONE_OFF
suffix:colon
id|Set22K
(paren
id|budget
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_DISEQC_SEND_MASTER_CMD
suffix:colon
(brace
r_struct
id|dvb_diseqc_master_cmd
op_star
id|cmd
op_assign
id|arg
suffix:semicolon
id|SendDiSEqCMsg
(paren
id|budget
comma
id|cmd-&gt;msg_len
comma
id|cmd-&gt;msg
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|FE_DISEQC_SEND_BURST
suffix:colon
id|SendDiSEqCMsg
(paren
id|budget
comma
l_int|0
comma
l_int|NULL
comma
(paren
r_int
r_int
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|budget_attach
r_static
r_int
id|budget_attach
(paren
r_struct
id|saa7146_dev
op_star
id|dev
comma
r_struct
id|saa7146_pci_extension_data
op_star
id|info
)paren
(brace
r_struct
id|budget
op_star
id|budget
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
suffix:semicolon
id|budget
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|budget
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|budget
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;dev:%p, info:%p, budget:%p&bslash;n&quot;
comma
id|dev
comma
id|info
comma
id|budget
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|ttpci_budget_init
(paren
id|budget
comma
id|dev
comma
id|info
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;==&gt; failed&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
(paren
id|budget
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|dvb_add_frontend_ioctls
(paren
id|budget-&gt;dvb_adapter
comma
id|budget_diseqc_ioctl
comma
l_int|NULL
comma
id|budget
)paren
suffix:semicolon
id|dev-&gt;ext_priv
op_assign
id|budget
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|budget_detach
r_static
r_int
id|budget_detach
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
r_struct
id|budget
op_star
id|budget
op_assign
(paren
r_struct
id|budget
op_star
)paren
id|dev-&gt;ext_priv
suffix:semicolon
r_int
id|err
suffix:semicolon
id|dvb_remove_frontend_ioctls
(paren
id|budget-&gt;dvb_adapter
comma
id|budget_diseqc_ioctl
comma
l_int|NULL
)paren
suffix:semicolon
id|err
op_assign
id|ttpci_budget_deinit
(paren
id|budget
)paren
suffix:semicolon
id|kfree
(paren
id|budget
)paren
suffix:semicolon
id|dev-&gt;ext_priv
op_assign
l_int|NULL
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|budget_extension
r_static
r_struct
id|saa7146_extension
id|budget_extension
suffix:semicolon
id|MAKE_BUDGET_INFO
c_func
(paren
id|ttbs
comma
l_string|&quot;TT-Budget/WinTV-NOVA-S  PCI&quot;
comma
id|BUDGET_TT
)paren
suffix:semicolon
id|MAKE_BUDGET_INFO
c_func
(paren
id|ttbc
comma
l_string|&quot;TT-Budget/WinTV-NOVA-C  PCI&quot;
comma
id|BUDGET_TT
)paren
suffix:semicolon
id|MAKE_BUDGET_INFO
c_func
(paren
id|ttbt
comma
l_string|&quot;TT-Budget/WinTV-NOVA-T  PCI&quot;
comma
id|BUDGET_TT
)paren
suffix:semicolon
id|MAKE_BUDGET_INFO
c_func
(paren
id|satel
comma
l_string|&quot;SATELCO Multimedia PCI&quot;
comma
id|BUDGET_TT_HW_DISEQC
)paren
suffix:semicolon
multiline_comment|/* Uncomment for Budget Patch */
multiline_comment|/*MAKE_BUDGET_INFO(fs_1_3,&quot;Siemens/Technotrend/Hauppauge PCI rev1.3+Budget_Patch&quot;, BUDGET_PATCH);*/
DECL|variable|pci_tbl
r_static
r_struct
id|pci_device_id
id|pci_tbl
(braket
)braket
op_assign
(brace
multiline_comment|/* Uncomment for Budget Patch */
multiline_comment|/*MAKE_EXTENSION_PCI(fs_1_3,0x13c2, 0x0000),*/
id|MAKE_EXTENSION_PCI
c_func
(paren
id|ttbs
comma
l_int|0x13c2
comma
l_int|0x1003
)paren
comma
id|MAKE_EXTENSION_PCI
c_func
(paren
id|ttbc
comma
l_int|0x13c2
comma
l_int|0x1004
)paren
comma
id|MAKE_EXTENSION_PCI
c_func
(paren
id|ttbt
comma
l_int|0x13c2
comma
l_int|0x1005
)paren
comma
id|MAKE_EXTENSION_PCI
c_func
(paren
id|satel
comma
l_int|0x13c2
comma
l_int|0x1013
)paren
comma
(brace
dot
id|vendor
op_assign
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|pci_tbl
)paren
suffix:semicolon
DECL|variable|budget_extension
r_static
r_struct
id|saa7146_extension
id|budget_extension
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;budget dvb&bslash;0&quot;
comma
dot
id|flags
op_assign
l_int|0
comma
dot
id|ext_vv_data
op_assign
l_int|NULL
comma
dot
id|module
op_assign
id|THIS_MODULE
comma
dot
id|pci_tbl
op_assign
id|pci_tbl
comma
dot
id|attach
op_assign
id|budget_attach
comma
dot
id|detach
op_assign
id|budget_detach
comma
dot
id|irq_mask
op_assign
id|MASK_10
comma
dot
id|irq_func
op_assign
id|ttpci_budget_irq10_handler
comma
)brace
suffix:semicolon
DECL|function|budget_init
r_static
r_int
id|__init
id|budget_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|saa7146_register_extension
c_func
(paren
op_amp
id|budget_extension
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|budget_exit
r_static
r_void
id|__exit
id|budget_exit
c_func
(paren
r_void
)paren
(brace
id|DEB_EE
c_func
(paren
(paren
l_string|&quot;.&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|saa7146_unregister_extension
c_func
(paren
op_amp
id|budget_extension
)paren
suffix:semicolon
)brace
DECL|variable|budget_init
id|module_init
c_func
(paren
id|budget_init
)paren
suffix:semicolon
DECL|variable|budget_exit
id|module_exit
c_func
(paren
id|budget_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Ralph Metzler, Marcus Metzler, Michael Hunold, others&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;driver for the SAA7146 based so-called &quot;
l_string|&quot;budget PCI DVB cards by Siemens, Technotrend, Hauppauge&quot;
)paren
suffix:semicolon
eof
