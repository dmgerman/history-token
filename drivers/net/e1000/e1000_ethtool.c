multiline_comment|/*******************************************************************************&n;&n;  This software program is available to you under a choice of one of two&n;  licenses. You may choose to be licensed under either the GNU General Public&n;  License 2.0, June 1991, available at http://www.fsf.org/copyleft/gpl.html,&n;  or the Intel BSD + Patent License, the text of which follows:&n;  &n;  Recipient has requested a license and Intel Corporation (&quot;Intel&quot;) is willing&n;  to grant a license for the software entitled Linux Base Driver for the&n;  Intel(R) PRO/1000 Family of Adapters (e1000) (the &quot;Software&quot;) being provided&n;  by Intel Corporation. The following definitions apply to this license:&n;  &n;  &quot;Licensed Patents&quot; means patent claims licensable by Intel Corporation which&n;  are necessarily infringed by the use of sale of the Software alone or when&n;  combined with the operating system referred to below.&n;  &n;  &quot;Recipient&quot; means the party to whom Intel delivers this Software.&n;  &n;  &quot;Licensee&quot; means Recipient and those third parties that receive a license to&n;  any operating system available under the GNU General Public License 2.0 or&n;  later.&n;  &n;  Copyright (c) 1999 - 2002 Intel Corporation.&n;  All rights reserved.&n;  &n;  The license is provided to Recipient and Recipient&squot;s Licensees under the&n;  following terms.&n;  &n;  Redistribution and use in source and binary forms of the Software, with or&n;  without modification, are permitted provided that the following conditions&n;  are met:&n;  &n;  Redistributions of source code of the Software may retain the above&n;  copyright notice, this list of conditions and the following disclaimer.&n;  &n;  Redistributions in binary form of the Software may reproduce the above&n;  copyright notice, this list of conditions and the following disclaimer in&n;  the documentation and/or materials provided with the distribution.&n;  &n;  Neither the name of Intel Corporation nor the names of its contributors&n;  shall be used to endorse or promote products derived from this Software&n;  without specific prior written permission.&n;  &n;  Intel hereby grants Recipient and Licensees a non-exclusive, worldwide,&n;  royalty-free patent license under Licensed Patents to make, use, sell, offer&n;  to sell, import and otherwise transfer the Software, if any, in source code&n;  and object code form. This license shall include changes to the Software&n;  that are error corrections or other minor changes to the Software that do&n;  not add functionality or features when the Software is incorporated in any&n;  version of an operating system that has been distributed under the GNU&n;  General Public License 2.0 or later. This patent license shall apply to the&n;  combination of the Software and any operating system licensed under the GNU&n;  General Public License 2.0 or later if, at the time Intel provides the&n;  Software to Recipient, such addition of the Software to the then publicly&n;  available versions of such operating systems available under the GNU General&n;  Public License 2.0 or later (whether in gold, beta or alpha form) causes&n;  such combination to be covered by the Licensed Patents. The patent license&n;  shall not apply to any other combinations which include the Software. NO&n;  hardware per se is licensed hereunder.&n;  &n;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS &quot;AS IS&quot;&n;  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n;  IMPLIED WARRANTIES OF MECHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n;  ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR IT CONTRIBUTORS BE LIABLE FOR ANY&n;  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES&n;  (INCLUDING, BUT NOT LIMITED, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;&n;  ANY LOSS OF USE; DATA, OR PROFITS; OR BUSINESS INTERUPTION) HOWEVER CAUSED&n;  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY OR&n;  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE&n;  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n;&n;*******************************************************************************/
multiline_comment|/* ethtool support for e1000 */
macro_line|#include &quot;e1000.h&quot;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_char
id|e1000_driver_name
(braket
)braket
suffix:semicolon
r_extern
r_char
id|e1000_driver_version
(braket
)braket
suffix:semicolon
r_extern
r_int
id|e1000_up
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
)paren
suffix:semicolon
r_extern
r_void
id|e1000_down
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
)paren
suffix:semicolon
r_static
r_void
DECL|function|e1000_ethtool_gset
id|e1000_ethtool_gset
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
comma
r_struct
id|ethtool_cmd
op_star
id|ecmd
)paren
(brace
r_struct
id|e1000_hw
op_star
id|hw
op_assign
op_amp
id|adapter-&gt;hw
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;media_type
op_eq
id|e1000_media_type_copper
)paren
(brace
id|ecmd-&gt;supported
op_assign
(paren
id|SUPPORTED_10baseT_Half
op_or
id|SUPPORTED_10baseT_Full
op_or
id|SUPPORTED_100baseT_Half
op_or
id|SUPPORTED_100baseT_Full
op_or
id|SUPPORTED_1000baseT_Full
op_or
id|SUPPORTED_Autoneg
op_or
id|SUPPORTED_TP
)paren
suffix:semicolon
id|ecmd-&gt;advertising
op_assign
id|ADVERTISED_TP
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;autoneg
op_eq
l_int|1
)paren
(brace
id|ecmd-&gt;advertising
op_or_assign
id|ADVERTISED_Autoneg
suffix:semicolon
multiline_comment|/* the e1000 autoneg seems to match ethtool nicely */
id|ecmd-&gt;advertising
op_or_assign
id|hw-&gt;autoneg_advertised
suffix:semicolon
)brace
id|ecmd-&gt;port
op_assign
id|PORT_TP
suffix:semicolon
id|ecmd-&gt;phy_address
op_assign
id|hw-&gt;phy_addr
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;mac_type
op_eq
id|e1000_82543
)paren
(brace
id|ecmd-&gt;transceiver
op_assign
id|XCVR_EXTERNAL
suffix:semicolon
)brace
r_else
id|ecmd-&gt;transceiver
op_assign
id|XCVR_INTERNAL
suffix:semicolon
)brace
r_else
(brace
id|ecmd-&gt;supported
op_assign
(paren
id|SUPPORTED_1000baseT_Full
op_or
id|SUPPORTED_FIBRE
op_or
id|SUPPORTED_Autoneg
)paren
suffix:semicolon
id|ecmd-&gt;advertising
op_assign
(paren
id|SUPPORTED_1000baseT_Full
op_or
id|SUPPORTED_FIBRE
op_or
id|SUPPORTED_Autoneg
)paren
suffix:semicolon
id|ecmd-&gt;port
op_assign
id|PORT_FIBRE
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;mac_type
op_ge
id|e1000_82545
)paren
(brace
id|ecmd-&gt;transceiver
op_assign
id|XCVR_INTERNAL
suffix:semicolon
)brace
r_else
id|ecmd-&gt;transceiver
op_assign
id|XCVR_EXTERNAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|netif_carrier_ok
c_func
(paren
id|adapter-&gt;netdev
)paren
)paren
(brace
id|e1000_get_speed_and_duplex
c_func
(paren
id|hw
comma
op_amp
id|adapter-&gt;link_speed
comma
op_amp
id|adapter-&gt;link_duplex
)paren
suffix:semicolon
id|ecmd-&gt;speed
op_assign
id|adapter-&gt;link_speed
suffix:semicolon
multiline_comment|/* unfortunatly FULL_DUPLEX != DUPLEX_FULL&n;&t;&t; *          and HALF_DUPLEX != DUPLEX_HALF */
r_if
c_cond
(paren
id|adapter-&gt;link_duplex
op_eq
id|FULL_DUPLEX
)paren
(brace
id|ecmd-&gt;duplex
op_assign
id|DUPLEX_FULL
suffix:semicolon
)brace
r_else
id|ecmd-&gt;duplex
op_assign
id|DUPLEX_HALF
suffix:semicolon
)brace
r_else
(brace
id|ecmd-&gt;speed
op_assign
op_minus
l_int|1
suffix:semicolon
id|ecmd-&gt;duplex
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|ecmd-&gt;autoneg
op_assign
(paren
id|hw-&gt;autoneg
ques
c_cond
id|AUTONEG_ENABLE
suffix:colon
id|AUTONEG_DISABLE
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|e1000_ethtool_sset
id|e1000_ethtool_sset
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
comma
r_struct
id|ethtool_cmd
op_star
id|ecmd
)paren
(brace
r_struct
id|e1000_hw
op_star
id|hw
op_assign
op_amp
id|adapter-&gt;hw
suffix:semicolon
r_if
c_cond
(paren
id|ecmd-&gt;autoneg
op_eq
id|AUTONEG_ENABLE
)paren
(brace
id|hw-&gt;autoneg
op_assign
l_int|1
suffix:semicolon
id|hw-&gt;autoneg_advertised
op_assign
(paren
id|ecmd-&gt;advertising
op_amp
l_int|0x002F
)paren
suffix:semicolon
)brace
r_else
(brace
id|hw-&gt;autoneg
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|ecmd-&gt;speed
op_plus
id|ecmd-&gt;duplex
)paren
(brace
r_case
id|SPEED_10
op_plus
id|DUPLEX_HALF
suffix:colon
id|hw-&gt;forced_speed_duplex
op_assign
id|e1000_10_half
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_10
op_plus
id|DUPLEX_FULL
suffix:colon
id|hw-&gt;forced_speed_duplex
op_assign
id|e1000_10_full
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_100
op_plus
id|DUPLEX_HALF
suffix:colon
id|hw-&gt;forced_speed_duplex
op_assign
id|e1000_100_half
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_100
op_plus
id|DUPLEX_FULL
suffix:colon
id|hw-&gt;forced_speed_duplex
op_assign
id|e1000_100_full
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_1000
op_plus
id|DUPLEX_FULL
suffix:colon
id|hw-&gt;autoneg
op_assign
l_int|1
suffix:semicolon
id|hw-&gt;autoneg_advertised
op_assign
id|ADVERTISE_1000_FULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEED_1000
op_plus
id|DUPLEX_HALF
suffix:colon
multiline_comment|/* not supported */
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/* reset the link */
id|e1000_down
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|e1000_up
c_func
(paren
id|adapter
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|e1000_eeprom_size
id|e1000_eeprom_size
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
(brace
r_if
c_cond
(paren
(paren
id|hw-&gt;mac_type
OG
id|e1000_82544
)paren
op_logical_and
(paren
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|EECD
)paren
op_amp
id|E1000_EECD_SIZE
)paren
)paren
(brace
r_return
l_int|512
suffix:semicolon
)brace
r_else
r_return
l_int|128
suffix:semicolon
)brace
r_static
r_void
DECL|function|e1000_ethtool_gdrvinfo
id|e1000_ethtool_gdrvinfo
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
comma
r_struct
id|ethtool_drvinfo
op_star
id|drvinfo
)paren
(brace
id|strncpy
c_func
(paren
id|drvinfo-&gt;driver
comma
id|e1000_driver_name
comma
l_int|32
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|drvinfo-&gt;version
comma
id|e1000_driver_version
comma
l_int|32
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|drvinfo-&gt;fw_version
comma
l_string|&quot;&quot;
comma
l_int|32
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|drvinfo-&gt;bus_info
comma
id|adapter-&gt;pdev-&gt;slot_name
comma
l_int|32
)paren
suffix:semicolon
DECL|macro|E1000_REGS_LEN
mdefine_line|#define E1000_REGS_LEN 32
id|drvinfo-&gt;regdump_len
op_assign
id|E1000_REGS_LEN
op_star
r_sizeof
(paren
r_uint32
)paren
suffix:semicolon
id|drvinfo-&gt;eedump_len
op_assign
id|e1000_eeprom_size
c_func
(paren
op_amp
id|adapter-&gt;hw
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|e1000_ethtool_gregs
id|e1000_ethtool_gregs
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
comma
r_struct
id|ethtool_regs
op_star
id|regs
comma
r_uint32
op_star
id|regs_buff
)paren
(brace
r_struct
id|e1000_hw
op_star
id|hw
op_assign
op_amp
id|adapter-&gt;hw
suffix:semicolon
id|regs-&gt;version
op_assign
(paren
l_int|1
op_lshift
l_int|24
)paren
op_or
(paren
id|hw-&gt;revision_id
op_lshift
l_int|16
)paren
op_or
id|hw-&gt;device_id
suffix:semicolon
id|regs_buff
(braket
l_int|0
)braket
op_assign
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|CTRL
)paren
suffix:semicolon
id|regs_buff
(braket
l_int|1
)braket
op_assign
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|STATUS
)paren
suffix:semicolon
id|regs_buff
(braket
l_int|2
)braket
op_assign
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|RCTL
)paren
suffix:semicolon
id|regs_buff
(braket
l_int|3
)braket
op_assign
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|RDLEN
)paren
suffix:semicolon
id|regs_buff
(braket
l_int|4
)braket
op_assign
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|RDH
)paren
suffix:semicolon
id|regs_buff
(braket
l_int|5
)braket
op_assign
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|RDT
)paren
suffix:semicolon
id|regs_buff
(braket
l_int|6
)braket
op_assign
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|RDTR
)paren
suffix:semicolon
id|regs_buff
(braket
l_int|7
)braket
op_assign
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|TCTL
)paren
suffix:semicolon
id|regs_buff
(braket
l_int|8
)braket
op_assign
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|TDLEN
)paren
suffix:semicolon
id|regs_buff
(braket
l_int|9
)braket
op_assign
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|TDH
)paren
suffix:semicolon
id|regs_buff
(braket
l_int|10
)braket
op_assign
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|TDT
)paren
suffix:semicolon
id|regs_buff
(braket
l_int|11
)braket
op_assign
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|TIDV
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|e1000_ethtool_geeprom
id|e1000_ethtool_geeprom
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
comma
r_struct
id|ethtool_eeprom
op_star
id|eeprom
comma
r_uint16
op_star
id|eeprom_buff
)paren
(brace
r_struct
id|e1000_hw
op_star
id|hw
op_assign
op_amp
id|adapter-&gt;hw
suffix:semicolon
r_int
id|i
comma
id|max_len
suffix:semicolon
id|eeprom-&gt;magic
op_assign
id|hw-&gt;vendor_id
op_or
(paren
id|hw-&gt;device_id
op_lshift
l_int|16
)paren
suffix:semicolon
id|max_len
op_assign
id|e1000_eeprom_size
c_func
(paren
id|hw
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|eeprom-&gt;offset
op_plus
id|eeprom-&gt;len
)paren
OG
id|max_len
)paren
id|eeprom-&gt;len
op_assign
(paren
id|max_len
op_minus
id|eeprom-&gt;offset
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
(paren
id|max_len
op_rshift
l_int|1
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|e1000_read_eeprom
c_func
(paren
op_amp
id|adapter-&gt;hw
comma
id|i
comma
op_amp
id|eeprom_buff
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|e1000_ethtool_gwol
id|e1000_ethtool_gwol
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
comma
r_struct
id|ethtool_wolinfo
op_star
id|wol
)paren
(brace
r_struct
id|e1000_hw
op_star
id|hw
op_assign
op_amp
id|adapter-&gt;hw
suffix:semicolon
r_switch
c_cond
(paren
id|adapter-&gt;hw.device_id
)paren
(brace
r_case
id|E1000_DEV_ID_82542
suffix:colon
r_case
id|E1000_DEV_ID_82543GC_FIBER
suffix:colon
r_case
id|E1000_DEV_ID_82543GC_COPPER
suffix:colon
r_case
id|E1000_DEV_ID_82544EI_FIBER
suffix:colon
r_default
suffix:colon
id|wol-&gt;supported
op_assign
l_int|0
suffix:semicolon
id|wol-&gt;wolopts
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
r_case
id|E1000_DEV_ID_82546EB_FIBER
suffix:colon
multiline_comment|/* Wake events only supported on port A for dual fiber */
r_if
c_cond
(paren
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|STATUS
)paren
op_amp
id|E1000_STATUS_FUNC_1
)paren
(brace
id|wol-&gt;supported
op_assign
l_int|0
suffix:semicolon
id|wol-&gt;wolopts
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Fall Through */
r_case
id|E1000_DEV_ID_82544EI_COPPER
suffix:colon
r_case
id|E1000_DEV_ID_82544GC_COPPER
suffix:colon
r_case
id|E1000_DEV_ID_82544GC_LOM
suffix:colon
r_case
id|E1000_DEV_ID_82540EM
suffix:colon
r_case
id|E1000_DEV_ID_82540EM_LOM
suffix:colon
r_case
id|E1000_DEV_ID_82545EM_COPPER
suffix:colon
r_case
id|E1000_DEV_ID_82545EM_FIBER
suffix:colon
r_case
id|E1000_DEV_ID_82546EB_COPPER
suffix:colon
id|wol-&gt;supported
op_assign
id|WAKE_PHY
op_or
id|WAKE_UCAST
op_or
id|WAKE_MCAST
op_or
id|WAKE_BCAST
op_or
id|WAKE_MAGIC
suffix:semicolon
id|wol-&gt;wolopts
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|adapter-&gt;wol
op_amp
id|E1000_WUFC_LNKC
)paren
(brace
id|wol-&gt;wolopts
op_or_assign
id|WAKE_PHY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|adapter-&gt;wol
op_amp
id|E1000_WUFC_EX
)paren
(brace
id|wol-&gt;wolopts
op_or_assign
id|WAKE_UCAST
suffix:semicolon
)brace
r_if
c_cond
(paren
id|adapter-&gt;wol
op_amp
id|E1000_WUFC_MC
)paren
(brace
id|wol-&gt;wolopts
op_or_assign
id|WAKE_MCAST
suffix:semicolon
)brace
r_if
c_cond
(paren
id|adapter-&gt;wol
op_amp
id|E1000_WUFC_BC
)paren
(brace
id|wol-&gt;wolopts
op_or_assign
id|WAKE_BCAST
suffix:semicolon
)brace
r_if
c_cond
(paren
id|adapter-&gt;wol
op_amp
id|E1000_WUFC_MAG
)paren
(brace
id|wol-&gt;wolopts
op_or_assign
id|WAKE_MAGIC
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|e1000_ethtool_swol
id|e1000_ethtool_swol
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
comma
r_struct
id|ethtool_wolinfo
op_star
id|wol
)paren
(brace
r_struct
id|e1000_hw
op_star
id|hw
op_assign
op_amp
id|adapter-&gt;hw
suffix:semicolon
r_switch
c_cond
(paren
id|adapter-&gt;hw.device_id
)paren
(brace
r_case
id|E1000_DEV_ID_82542
suffix:colon
r_case
id|E1000_DEV_ID_82543GC_FIBER
suffix:colon
r_case
id|E1000_DEV_ID_82543GC_COPPER
suffix:colon
r_case
id|E1000_DEV_ID_82544EI_FIBER
suffix:colon
r_default
suffix:colon
r_return
id|wol-&gt;wolopts
ques
c_cond
op_minus
id|EOPNOTSUPP
suffix:colon
l_int|0
suffix:semicolon
r_case
id|E1000_DEV_ID_82546EB_FIBER
suffix:colon
multiline_comment|/* Wake events only supported on port A for dual fiber */
r_if
c_cond
(paren
id|E1000_READ_REG
c_func
(paren
id|hw
comma
id|STATUS
)paren
op_amp
id|E1000_STATUS_FUNC_1
)paren
(brace
r_return
id|wol-&gt;wolopts
ques
c_cond
op_minus
id|EOPNOTSUPP
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Fall Through */
r_case
id|E1000_DEV_ID_82544EI_COPPER
suffix:colon
r_case
id|E1000_DEV_ID_82544GC_COPPER
suffix:colon
r_case
id|E1000_DEV_ID_82544GC_LOM
suffix:colon
r_case
id|E1000_DEV_ID_82540EM
suffix:colon
r_case
id|E1000_DEV_ID_82540EM_LOM
suffix:colon
r_case
id|E1000_DEV_ID_82545EM_COPPER
suffix:colon
r_case
id|E1000_DEV_ID_82545EM_FIBER
suffix:colon
r_case
id|E1000_DEV_ID_82546EB_COPPER
suffix:colon
r_if
c_cond
(paren
id|wol-&gt;wolopts
op_amp
id|WAKE_ARP
)paren
(brace
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
id|adapter-&gt;wol
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|wol-&gt;wolopts
op_amp
id|WAKE_PHY
)paren
(brace
id|adapter-&gt;wol
op_or_assign
id|E1000_WUFC_LNKC
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wol-&gt;wolopts
op_amp
id|WAKE_UCAST
)paren
(brace
id|adapter-&gt;wol
op_or_assign
id|E1000_WUFC_EX
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wol-&gt;wolopts
op_amp
id|WAKE_MCAST
)paren
(brace
id|adapter-&gt;wol
op_or_assign
id|E1000_WUFC_MC
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wol-&gt;wolopts
op_amp
id|WAKE_BCAST
)paren
(brace
id|adapter-&gt;wol
op_or_assign
id|E1000_WUFC_BC
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wol-&gt;wolopts
op_amp
id|WAKE_MAGIC
)paren
(brace
id|adapter-&gt;wol
op_or_assign
id|E1000_WUFC_MAG
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef&t;ETHTOOL_PHYS_ID
multiline_comment|/* toggle LED 4 times per second = 2 &quot;blinks&quot; per second */
DECL|macro|E1000_ID_INTERVAL
mdefine_line|#define E1000_ID_INTERVAL&t;(HZ/4)
multiline_comment|/* bit defines for adapter-&gt;led_status */
DECL|macro|E1000_LED_ON
mdefine_line|#define E1000_LED_ON&t;&t;0
r_static
r_void
DECL|function|e1000_led_blink_callback
id|e1000_led_blink_callback
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|e1000_adapter
op_star
id|adapter
op_assign
(paren
r_struct
id|e1000_adapter
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|test_and_change_bit
c_func
(paren
id|E1000_LED_ON
comma
op_amp
id|adapter-&gt;led_status
)paren
)paren
(brace
id|e1000_led_off
c_func
(paren
op_amp
id|adapter-&gt;hw
)paren
suffix:semicolon
)brace
r_else
id|e1000_led_on
c_func
(paren
op_amp
id|adapter-&gt;hw
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|adapter-&gt;blink_timer
comma
id|jiffies
op_plus
id|E1000_ID_INTERVAL
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|e1000_ethtool_led_blink
id|e1000_ethtool_led_blink
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
comma
r_struct
id|ethtool_value
op_star
id|id
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|adapter-&gt;blink_timer.function
)paren
(brace
id|init_timer
c_func
(paren
op_amp
id|adapter-&gt;blink_timer
)paren
suffix:semicolon
id|adapter-&gt;blink_timer.function
op_assign
id|e1000_led_blink_callback
suffix:semicolon
id|adapter-&gt;blink_timer.data
op_assign
(paren
r_int
r_int
)paren
id|adapter
suffix:semicolon
)brace
id|e1000_setup_led
c_func
(paren
op_amp
id|adapter-&gt;hw
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|adapter-&gt;blink_timer
comma
id|jiffies
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|id-&gt;data
)paren
(brace
id|schedule_timeout
c_func
(paren
id|id-&gt;data
op_star
id|HZ
)paren
suffix:semicolon
)brace
r_else
id|schedule_timeout
c_func
(paren
id|MAX_SCHEDULE_TIMEOUT
)paren
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|adapter-&gt;blink_timer
)paren
suffix:semicolon
id|e1000_led_off
c_func
(paren
op_amp
id|adapter-&gt;hw
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|E1000_LED_ON
comma
op_amp
id|adapter-&gt;led_status
)paren
suffix:semicolon
id|e1000_cleanup_led
c_func
(paren
op_amp
id|adapter-&gt;hw
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif&t;/* ETHTOOL_PHYS_ID */
r_int
DECL|function|e1000_ethtool_ioctl
id|e1000_ethtool_ioctl
c_func
(paren
r_struct
id|net_device
op_star
id|netdev
comma
r_struct
id|ifreq
op_star
id|ifr
)paren
(brace
r_struct
id|e1000_adapter
op_star
id|adapter
op_assign
id|netdev-&gt;priv
suffix:semicolon
r_void
op_star
id|addr
op_assign
id|ifr-&gt;ifr_data
suffix:semicolon
r_uint32
id|cmd
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|cmd
comma
(paren
r_uint32
op_star
)paren
id|addr
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|ETHTOOL_GSET
suffix:colon
(brace
r_struct
id|ethtool_cmd
id|ecmd
op_assign
(brace
id|ETHTOOL_GSET
)brace
suffix:semicolon
id|e1000_ethtool_gset
c_func
(paren
id|adapter
comma
op_amp
id|ecmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
op_amp
id|ecmd
comma
r_sizeof
(paren
id|ecmd
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|ETHTOOL_SSET
suffix:colon
(brace
r_struct
id|ethtool_cmd
id|ecmd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ecmd
comma
id|addr
comma
r_sizeof
(paren
id|ecmd
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|e1000_ethtool_sset
c_func
(paren
id|adapter
comma
op_amp
id|ecmd
)paren
suffix:semicolon
)brace
r_case
id|ETHTOOL_GDRVINFO
suffix:colon
(brace
r_struct
id|ethtool_drvinfo
id|drvinfo
op_assign
(brace
id|ETHTOOL_GDRVINFO
)brace
suffix:semicolon
id|e1000_ethtool_gdrvinfo
c_func
(paren
id|adapter
comma
op_amp
id|drvinfo
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
op_amp
id|drvinfo
comma
r_sizeof
(paren
id|drvinfo
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|ETHTOOL_GREGS
suffix:colon
(brace
r_struct
id|ethtool_regs
id|regs
op_assign
(brace
id|ETHTOOL_GREGS
)brace
suffix:semicolon
r_uint32
id|regs_buff
(braket
id|E1000_REGS_LEN
)braket
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|regs
comma
id|addr
comma
r_sizeof
(paren
id|regs
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|e1000_ethtool_gregs
c_func
(paren
id|adapter
comma
op_amp
id|regs
comma
id|regs_buff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
op_amp
id|regs
comma
r_sizeof
(paren
id|regs
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|addr
op_add_assign
m_offsetof
(paren
r_struct
id|ethtool_regs
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
id|regs_buff
comma
id|regs.len
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|ETHTOOL_NWAY_RST
suffix:colon
(brace
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|e1000_down
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|e1000_up
c_func
(paren
id|adapter
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef&t;ETHTOOL_PHYS_ID
r_case
id|ETHTOOL_PHYS_ID
suffix:colon
(brace
r_struct
id|ethtool_value
id|id
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|id
comma
id|addr
comma
r_sizeof
(paren
id|id
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|e1000_ethtool_led_blink
c_func
(paren
id|adapter
comma
op_amp
id|id
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* ETHTOOL_PHYS_ID */
r_case
id|ETHTOOL_GLINK
suffix:colon
(brace
r_struct
id|ethtool_value
id|link
op_assign
(brace
id|ETHTOOL_GLINK
)brace
suffix:semicolon
id|link.data
op_assign
id|netif_carrier_ok
c_func
(paren
id|netdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
op_amp
id|link
comma
r_sizeof
(paren
id|link
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|ETHTOOL_GWOL
suffix:colon
(brace
r_struct
id|ethtool_wolinfo
id|wol
op_assign
(brace
id|ETHTOOL_GWOL
)brace
suffix:semicolon
id|e1000_ethtool_gwol
c_func
(paren
id|adapter
comma
op_amp
id|wol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
op_amp
id|wol
comma
r_sizeof
(paren
id|wol
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|ETHTOOL_SWOL
suffix:colon
(brace
r_struct
id|ethtool_wolinfo
id|wol
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_NET_ADMIN
)paren
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|wol
comma
id|addr
comma
r_sizeof
(paren
id|wol
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|e1000_ethtool_swol
c_func
(paren
id|adapter
comma
op_amp
id|wol
)paren
suffix:semicolon
)brace
r_case
id|ETHTOOL_GEEPROM
suffix:colon
(brace
r_struct
id|ethtool_eeprom
id|eeprom
op_assign
(brace
id|ETHTOOL_GEEPROM
)brace
suffix:semicolon
r_uint16
id|eeprom_buff
(braket
l_int|256
)braket
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|eeprom
comma
id|addr
comma
r_sizeof
(paren
id|eeprom
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|e1000_ethtool_geeprom
c_func
(paren
id|adapter
comma
op_amp
id|eeprom
comma
id|eeprom_buff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
op_amp
id|eeprom
comma
r_sizeof
(paren
id|eeprom
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|addr
op_add_assign
m_offsetof
(paren
r_struct
id|ethtool_eeprom
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
id|eeprom_buff
op_plus
id|eeprom.offset
comma
id|eeprom.len
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
)brace
eof
