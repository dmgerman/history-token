multiline_comment|/*&n; * budget-patch.c: driver for Budget Patch,&n; * hardware modification of DVB-S cards enabling full TS&n; *&n; * Written by Emard &lt;emard@softhome.net&gt;&n; *&n; * Original idea by Roberto Deza &lt;rdeza@unav.es&gt;&n; *&n; * Special thanks to Holger Waechtler, Michael Hunold, Marian Durkovic&n; * and Metzlerbros&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; * &n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.&n; * Or, point your browser to http://www.gnu.org/copyleft/gpl.html&n; * &n; *&n; * the project&squot;s page is at http://www.linuxtv.org/dvb/&n; */
macro_line|#include &quot;av7110.h&quot;
macro_line|#include &quot;av7110_hw.h&quot;
macro_line|#include &quot;budget.h&quot;
DECL|macro|budget_patch
mdefine_line|#define budget_patch budget
DECL|variable|budget_extension
r_static
r_struct
id|saa7146_extension
id|budget_extension
suffix:semicolon
id|MAKE_BUDGET_INFO
c_func
(paren
id|fs_1_3
comma
l_string|&quot;Siemens/Technotrend/Hauppauge PCI rev1.3+Budget_Patch&quot;
comma
id|BUDGET_PATCH
)paren
suffix:semicolon
DECL|variable|pci_tbl
r_static
r_struct
id|pci_device_id
id|pci_tbl
(braket
)braket
op_assign
(brace
id|MAKE_EXTENSION_PCI
c_func
(paren
id|fs_1_3
comma
l_int|0x13c2
comma
l_int|0x0000
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
DECL|function|budget_wdebi
r_static
r_int
id|budget_wdebi
c_func
(paren
r_struct
id|budget_patch
op_star
id|budget
comma
id|u32
id|config
comma
r_int
id|addr
comma
id|u32
id|val
comma
r_int
id|count
)paren
(brace
r_struct
id|saa7146_dev
op_star
id|dev
op_assign
id|budget-&gt;dev
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|0
op_logical_or
id|count
OG
l_int|4
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|DEBI_CONFIG
comma
id|config
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|DEBI_AD
comma
id|val
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|DEBI_COMMAND
comma
(paren
id|count
op_lshift
l_int|17
)paren
op_or
(paren
id|addr
op_amp
l_int|0xffff
)paren
)paren
suffix:semicolon
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC2
comma
(paren
l_int|2
op_lshift
l_int|16
)paren
op_or
l_int|2
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|budget_av7110_send_fw_cmd
r_static
r_int
id|budget_av7110_send_fw_cmd
c_func
(paren
r_struct
id|budget_patch
op_star
id|budget
comma
id|u16
op_star
id|buf
comma
r_int
id|length
)paren
(brace
r_int
id|i
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
OL
id|length
suffix:semicolon
id|i
op_increment
)paren
id|budget_wdebi
c_func
(paren
id|budget
comma
id|DEBINOSWAP
comma
id|COMMAND
op_plus
l_int|2
op_star
id|i
comma
(paren
id|u32
)paren
id|buf
(braket
id|i
)braket
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
)paren
id|budget_wdebi
c_func
(paren
id|budget
comma
id|DEBINOSWAP
comma
id|COMMAND
op_plus
l_int|2
comma
(paren
id|u32
)paren
id|buf
(braket
l_int|1
)braket
comma
l_int|2
)paren
suffix:semicolon
r_else
id|budget_wdebi
c_func
(paren
id|budget
comma
id|DEBINOSWAP
comma
id|COMMAND
op_plus
l_int|2
comma
l_int|0
comma
l_int|2
)paren
suffix:semicolon
id|budget_wdebi
c_func
(paren
id|budget
comma
id|DEBINOSWAP
comma
id|COMMAND
comma
(paren
id|u32
)paren
id|buf
(braket
l_int|0
)braket
comma
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|av7110_set22k
r_static
r_void
id|av7110_set22k
c_func
(paren
r_struct
id|budget_patch
op_star
id|budget
comma
r_int
id|state
)paren
(brace
id|u16
id|buf
(braket
l_int|2
)braket
op_assign
(brace
(paren
id|COMTYPE_AUDIODAC
op_lshift
l_int|8
)paren
op_or
(paren
id|state
ques
c_cond
id|ON22K
suffix:colon
id|OFF22K
)paren
comma
l_int|0
)brace
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
)paren
suffix:semicolon
id|budget_av7110_send_fw_cmd
c_func
(paren
id|budget
comma
id|buf
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|function|av7110_send_diseqc_msg
r_static
r_int
id|av7110_send_diseqc_msg
c_func
(paren
r_struct
id|budget_patch
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
id|burst
)paren
(brace
r_int
id|i
suffix:semicolon
id|u16
id|buf
(braket
l_int|18
)braket
op_assign
(brace
(paren
(paren
id|COMTYPE_AUDIODAC
op_lshift
l_int|8
)paren
op_or
id|SendDiSEqC
)paren
comma
l_int|16
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|10
)paren
id|len
op_assign
l_int|10
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|len
op_plus
l_int|2
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|burst
op_ne
op_minus
l_int|1
)paren
id|buf
(braket
l_int|3
)braket
op_assign
id|burst
ques
c_cond
l_int|0x01
suffix:colon
l_int|0x00
suffix:semicolon
r_else
id|buf
(braket
l_int|3
)braket
op_assign
l_int|0xffff
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
id|buf
(braket
id|i
op_plus
l_int|4
)braket
op_assign
id|msg
(braket
id|i
)braket
suffix:semicolon
id|budget_av7110_send_fw_cmd
c_func
(paren
id|budget
comma
id|buf
comma
l_int|18
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|budget_patch_diseqc_ioctl
r_int
id|budget_patch_diseqc_ioctl
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
id|budget_patch
op_star
id|budget
op_assign
id|fe-&gt;before_after_data
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
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
id|av7110_set22k
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
id|av7110_set22k
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
id|av7110_send_diseqc_msg
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
id|av7110_send_diseqc_msg
(paren
id|budget
comma
l_int|0
comma
l_int|NULL
comma
(paren
r_int
)paren
(paren
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|budget_patch_attach
r_static
r_int
id|budget_patch_attach
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
id|budget_patch
op_star
id|budget
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|budget
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|budget_patch
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dprintk
c_func
(paren
l_int|2
comma
l_string|&quot;budget: %p&bslash;n&quot;
comma
id|budget
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
id|kfree
(paren
id|budget
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n;**      This code will setup the SAA7146_RPS1 to generate a square &n;**      wave on GPIO3, changing when a field (TS_HEIGHT/2 &quot;lines&quot; of &n;**      TS_WIDTH packets) has been acquired on SAA7146_D1B video port; &n;**      then, this GPIO3 output which is connected to the D1B_VSYNC &n;**      input, will trigger the acquisition of the alternate field &n;**      and so on.&n;**      Currently, the TT_budget / WinTV_Nova cards have two ICs &n;**      (74HCT4040, LVC74) for the generation of this VSYNC signal, &n;**      which seems that can be done perfectly without this :-)).&n;*/
singleline_comment|// Setup RPS1 &quot;program&quot; (p35)
singleline_comment|// Wait reset Source Line Counter Threshold                     (p36)
id|WRITE_RPS1
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|CMD_PAUSE
op_or
id|RPS_INV
op_or
id|EVT_HS
)paren
)paren
suffix:semicolon
singleline_comment|// Wait Source Line Counter Threshold                           (p36)
id|WRITE_RPS1
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|CMD_PAUSE
op_or
id|EVT_HS
)paren
)paren
suffix:semicolon
singleline_comment|// Set GPIO3=1                                                  (p42)
id|WRITE_RPS1
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|CMD_WR_REG_MASK
op_or
(paren
id|GPIO_CTRL
op_rshift
l_int|2
)paren
)paren
)paren
suffix:semicolon
id|WRITE_RPS1
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|GPIO3_MSK
)paren
)paren
suffix:semicolon
id|WRITE_RPS1
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|SAA7146_GPIO_OUTHI
op_lshift
l_int|24
)paren
)paren
suffix:semicolon
singleline_comment|// Wait reset Source Line Counter Threshold                     (p36)
id|WRITE_RPS1
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|CMD_PAUSE
op_or
id|RPS_INV
op_or
id|EVT_HS
)paren
)paren
suffix:semicolon
singleline_comment|// Wait Source Line Counter Threshold
id|WRITE_RPS1
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|CMD_PAUSE
op_or
id|EVT_HS
)paren
)paren
suffix:semicolon
singleline_comment|// Set GPIO3=0                                                  (p42)
id|WRITE_RPS1
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|CMD_WR_REG_MASK
op_or
(paren
id|GPIO_CTRL
op_rshift
l_int|2
)paren
)paren
)paren
suffix:semicolon
id|WRITE_RPS1
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|GPIO3_MSK
)paren
)paren
suffix:semicolon
id|WRITE_RPS1
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|SAA7146_GPIO_OUTLO
op_lshift
l_int|24
)paren
)paren
suffix:semicolon
singleline_comment|// Jump to begin of RPS program                                 (p37)
id|WRITE_RPS1
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|CMD_JUMP
)paren
)paren
suffix:semicolon
id|WRITE_RPS1
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|dev-&gt;d_rps1.dma_handle
)paren
)paren
suffix:semicolon
singleline_comment|// Fix VSYNC level
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
singleline_comment|// Set RPS1 Address register to point to RPS code               (r108 p42)
id|saa7146_write
c_func
(paren
id|dev
comma
id|RPS_ADDR1
comma
id|dev-&gt;d_rps1.dma_handle
)paren
suffix:semicolon
singleline_comment|// Set Source Line Counter Threshold, using BRS                 (rCC p43)
id|saa7146_write
c_func
(paren
id|dev
comma
id|RPS_THRESH1
comma
(paren
(paren
id|TS_HEIGHT
op_div
l_int|2
)paren
op_or
id|MASK_12
)paren
)paren
suffix:semicolon
singleline_comment|// Enable RPS1                                                  (rFC p33)
id|saa7146_write
c_func
(paren
id|dev
comma
id|MC1
comma
(paren
id|MASK_13
op_or
id|MASK_29
)paren
)paren
suffix:semicolon
id|dvb_add_frontend_ioctls
(paren
id|budget-&gt;dvb_adapter
comma
id|budget_patch_diseqc_ioctl
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
DECL|function|budget_patch_detach
r_static
r_int
id|budget_patch_detach
(paren
r_struct
id|saa7146_dev
op_star
id|dev
)paren
(brace
r_struct
id|budget_patch
op_star
id|budget
op_assign
(paren
r_struct
id|budget_patch
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
id|budget_patch_diseqc_ioctl
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
r_return
id|err
suffix:semicolon
)brace
DECL|function|budget_patch_init
r_static
r_int
id|__init
id|budget_patch_init
c_func
(paren
r_void
)paren
(brace
r_return
id|saa7146_register_extension
c_func
(paren
op_amp
id|budget_extension
)paren
suffix:semicolon
)brace
DECL|function|budget_patch_exit
r_static
r_void
id|__exit
id|budget_patch_exit
c_func
(paren
r_void
)paren
(brace
id|saa7146_unregister_extension
c_func
(paren
op_amp
id|budget_extension
)paren
suffix:semicolon
)brace
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
l_string|&quot;budget_patch dvb&bslash;0&quot;
comma
dot
id|flags
op_assign
l_int|0
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
id|budget_patch_attach
comma
dot
id|detach
op_assign
id|budget_patch_detach
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
DECL|variable|budget_patch_init
id|module_init
c_func
(paren
id|budget_patch_init
)paren
suffix:semicolon
DECL|variable|budget_patch_exit
id|module_exit
c_func
(paren
id|budget_patch_exit
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
l_string|&quot;Emard, Roberto Deza, Holger Waechtler, Michael Hunold, others&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver for full TS modified DVB-S SAA7146+AV7110 &quot;
l_string|&quot;based so-called Budget Patch cards&quot;
)paren
suffix:semicolon
eof
