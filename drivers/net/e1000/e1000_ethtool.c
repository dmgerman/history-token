multiline_comment|/*******************************************************************************&n;&n;  &n;  Copyright(c) 1999 - 2003 Intel Corporation. All rights reserved.&n;  &n;  This program is free software; you can redistribute it and/or modify it &n;  under the terms of the GNU General Public License as published by the Free &n;  Software Foundation; either version 2 of the License, or (at your option) &n;  any later version.&n;  &n;  This program is distributed in the hope that it will be useful, but WITHOUT &n;  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or &n;  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for &n;  more details.&n;  &n;  You should have received a copy of the GNU General Public License along with&n;  this program; if not, write to the Free Software Foundation, Inc., 59 &n;  Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n;  &n;  The full GNU General Public License is included in this distribution in the&n;  file called LICENSE.&n;  &n;  Contact Information:&n;  Linux NICS &lt;linux.nics@intel.com&gt;&n;  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497&n;&n;*******************************************************************************/
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
r_extern
r_void
id|e1000_reset
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
)paren
suffix:semicolon
r_extern
r_int
id|e1000_set_spd_dplx
c_func
(paren
r_struct
id|e1000_adapter
op_star
id|adapter
comma
r_uint16
id|spddplx
)paren
suffix:semicolon
DECL|variable|e1000_gstrings_stats
r_static
r_char
id|e1000_gstrings_stats
(braket
)braket
(braket
id|ETH_GSTRING_LEN
)braket
op_assign
(brace
l_string|&quot;rx_packets&quot;
comma
l_string|&quot;tx_packets&quot;
comma
l_string|&quot;rx_bytes&quot;
comma
l_string|&quot;tx_bytes&quot;
comma
l_string|&quot;rx_errors&quot;
comma
l_string|&quot;tx_errors&quot;
comma
l_string|&quot;rx_dropped&quot;
comma
l_string|&quot;tx_dropped&quot;
comma
l_string|&quot;multicast&quot;
comma
l_string|&quot;collisions&quot;
comma
l_string|&quot;rx_length_errors&quot;
comma
l_string|&quot;rx_over_errors&quot;
comma
l_string|&quot;rx_crc_errors&quot;
comma
l_string|&quot;rx_frame_errors&quot;
comma
l_string|&quot;rx_fifo_errors&quot;
comma
l_string|&quot;rx_missed_errors&quot;
comma
l_string|&quot;tx_aborted_errors&quot;
comma
l_string|&quot;tx_carrier_errors&quot;
comma
l_string|&quot;tx_fifo_errors&quot;
comma
l_string|&quot;tx_heartbeat_errors&quot;
comma
l_string|&quot;tx_window_errors&quot;
comma
)brace
suffix:semicolon
DECL|macro|E1000_STATS_LEN
mdefine_line|#define E1000_STATS_LEN&t;sizeof(e1000_gstrings_stats) / ETH_GSTRING_LEN
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
l_int|0x002F
suffix:semicolon
id|ecmd-&gt;advertising
op_assign
l_int|0x002F
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|e1000_set_spd_dplx
c_func
(paren
id|adapter
comma
id|ecmd-&gt;speed
op_plus
id|ecmd-&gt;duplex
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* reset the link */
r_if
c_cond
(paren
id|netif_running
c_func
(paren
id|adapter-&gt;netdev
)paren
)paren
(brace
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
)brace
r_else
id|e1000_reset
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
l_string|&quot;N/A&quot;
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
id|drvinfo-&gt;n_stats
op_assign
id|E1000_STATS_LEN
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
id|adapter-&gt;hw.eeprom.word_size
op_star
l_int|2
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
r_int
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
id|first_word
comma
id|last_word
suffix:semicolon
r_int
id|ret_val
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|eeprom-&gt;len
op_eq
l_int|0
)paren
(brace
id|ret_val
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|geeprom_error
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|eeprom-&gt;offset
OG
id|eeprom-&gt;offset
op_plus
id|eeprom-&gt;len
)paren
(brace
id|ret_val
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|geeprom_error
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|eeprom-&gt;offset
op_plus
id|eeprom-&gt;len
)paren
OG
(paren
id|hw-&gt;eeprom.word_size
op_star
l_int|2
)paren
)paren
(brace
id|eeprom-&gt;len
op_assign
(paren
(paren
id|hw-&gt;eeprom.word_size
op_star
l_int|2
)paren
op_minus
id|eeprom-&gt;offset
)paren
suffix:semicolon
)brace
id|first_word
op_assign
id|eeprom-&gt;offset
op_rshift
l_int|1
suffix:semicolon
id|last_word
op_assign
(paren
id|eeprom-&gt;offset
op_plus
id|eeprom-&gt;len
op_minus
l_int|1
)paren
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;eeprom.type
op_eq
id|e1000_eeprom_spi
)paren
(brace
id|ret_val
op_assign
id|e1000_read_eeprom
c_func
(paren
id|hw
comma
id|first_word
comma
id|last_word
op_minus
id|first_word
op_plus
l_int|1
comma
id|eeprom_buff
)paren
suffix:semicolon
)brace
r_else
(brace
r_uint16
id|i
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
id|last_word
op_minus
id|first_word
op_plus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|ret_val
op_assign
id|e1000_read_eeprom
c_func
(paren
id|hw
comma
id|first_word
op_plus
id|i
comma
l_int|1
comma
op_amp
id|eeprom_buff
(braket
id|i
)braket
)paren
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
id|geeprom_error
suffix:colon
r_return
id|ret_val
suffix:semicolon
)brace
r_static
r_int
DECL|function|e1000_ethtool_seeprom
id|e1000_ethtool_seeprom
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
r_void
op_star
id|user_data
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
r_uint16
op_star
id|eeprom_buff
suffix:semicolon
r_void
op_star
id|ptr
suffix:semicolon
r_int
id|max_len
comma
id|first_word
comma
id|last_word
comma
id|ret_val
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|eeprom-&gt;len
op_eq
l_int|0
)paren
(brace
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
r_if
c_cond
(paren
id|eeprom-&gt;magic
op_ne
(paren
id|hw-&gt;vendor_id
op_or
(paren
id|hw-&gt;device_id
op_lshift
l_int|16
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|max_len
op_assign
id|hw-&gt;eeprom.word_size
op_star
l_int|2
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
(brace
id|eeprom-&gt;len
op_assign
(paren
id|max_len
op_minus
id|eeprom-&gt;offset
)paren
suffix:semicolon
)brace
id|first_word
op_assign
id|eeprom-&gt;offset
op_rshift
l_int|1
suffix:semicolon
id|last_word
op_assign
(paren
id|eeprom-&gt;offset
op_plus
id|eeprom-&gt;len
op_minus
l_int|1
)paren
op_rshift
l_int|1
suffix:semicolon
id|eeprom_buff
op_assign
id|kmalloc
c_func
(paren
id|max_len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eeprom_buff
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|ptr
op_assign
(paren
r_void
op_star
)paren
id|eeprom_buff
suffix:semicolon
r_if
c_cond
(paren
id|eeprom-&gt;offset
op_amp
l_int|1
)paren
(brace
multiline_comment|/* need read/modify/write of first changed EEPROM word */
multiline_comment|/* only the second byte of the word is being modified */
id|ret_val
op_assign
id|e1000_read_eeprom
c_func
(paren
id|hw
comma
id|first_word
comma
l_int|1
comma
op_amp
id|eeprom_buff
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|ptr
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
(paren
id|eeprom-&gt;offset
op_plus
id|eeprom-&gt;len
)paren
op_amp
l_int|1
)paren
op_logical_and
(paren
id|ret_val
op_eq
l_int|0
)paren
)paren
(brace
multiline_comment|/* need read/modify/write of last changed EEPROM word */
multiline_comment|/* only the first byte of the word is being modified */
id|ret_val
op_assign
id|e1000_read_eeprom
c_func
(paren
id|hw
comma
id|last_word
comma
l_int|1
comma
op_amp
id|eeprom_buff
(braket
id|last_word
op_minus
id|first_word
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ret_val
op_ne
l_int|0
)paren
op_logical_or
id|copy_from_user
c_func
(paren
id|ptr
comma
id|user_data
comma
id|eeprom-&gt;len
)paren
)paren
(brace
id|ret_val
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|seeprom_error
suffix:semicolon
)brace
id|ret_val
op_assign
id|e1000_write_eeprom
c_func
(paren
id|hw
comma
id|first_word
comma
id|last_word
op_minus
id|first_word
op_plus
l_int|1
comma
id|eeprom_buff
)paren
suffix:semicolon
multiline_comment|/* Update the checksum over the first part of the EEPROM if needed */
r_if
c_cond
(paren
(paren
id|ret_val
op_eq
l_int|0
)paren
op_logical_and
id|first_word
op_le
id|EEPROM_CHECKSUM_REG
)paren
(brace
id|e1000_update_eeprom_checksum
c_func
(paren
id|hw
)paren
suffix:semicolon
)brace
id|seeprom_error
suffix:colon
id|kfree
c_func
(paren
id|eeprom_buff
)paren
suffix:semicolon
r_return
id|ret_val
suffix:semicolon
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
r_default
suffix:colon
id|wol-&gt;supported
op_assign
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
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|wol-&gt;wolopts
op_amp
(paren
id|WAKE_ARP
op_or
id|WAKE_MAGICSECURE
op_or
id|WAKE_PHY
)paren
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
id|ETHTOOL_GSTRINGS
suffix:colon
(brace
r_struct
id|ethtool_gstrings
id|gstrings
op_assign
(brace
id|ETHTOOL_GSTRINGS
)brace
suffix:semicolon
r_char
op_star
id|strings
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|gstrings
comma
id|addr
comma
r_sizeof
(paren
id|gstrings
)paren
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
id|gstrings.string_set
)paren
(brace
r_case
id|ETH_SS_STATS
suffix:colon
id|gstrings.len
op_assign
id|E1000_STATS_LEN
suffix:semicolon
id|strings
op_assign
op_star
id|e1000_gstrings_stats
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
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
op_amp
id|gstrings
comma
r_sizeof
(paren
id|gstrings
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
id|ethtool_gstrings
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
id|strings
comma
id|gstrings.len
op_star
id|ETH_GSTRING_LEN
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
r_if
c_cond
(paren
id|netif_running
c_func
(paren
id|netdev
)paren
)paren
(brace
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
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
r_struct
id|e1000_hw
op_star
id|hw
op_assign
op_amp
id|adapter-&gt;hw
suffix:semicolon
r_uint16
op_star
id|eeprom_buff
suffix:semicolon
r_void
op_star
id|ptr
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|eeprom_buff
op_assign
id|kmalloc
c_func
(paren
id|hw-&gt;eeprom.word_size
op_star
l_int|2
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eeprom_buff
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
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
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|err_geeprom_ioctl
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
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
)paren
)paren
(brace
r_goto
id|err_geeprom_ioctl
suffix:semicolon
)brace
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
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|err_geeprom_ioctl
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
id|ptr
op_assign
(paren
(paren
r_void
op_star
)paren
id|eeprom_buff
)paren
op_plus
(paren
id|eeprom.offset
op_amp
l_int|1
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
id|ptr
comma
id|eeprom.len
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
id|err_geeprom_ioctl
suffix:colon
id|kfree
c_func
(paren
id|eeprom_buff
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_case
id|ETHTOOL_SEEPROM
suffix:colon
(brace
r_struct
id|ethtool_eeprom
id|eeprom
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
r_return
id|e1000_ethtool_seeprom
c_func
(paren
id|adapter
comma
op_amp
id|eeprom
comma
id|addr
)paren
suffix:semicolon
)brace
r_case
id|ETHTOOL_GSTATS
suffix:colon
(brace
r_struct
(brace
r_struct
id|ethtool_stats
id|cmd
suffix:semicolon
r_uint64
id|data
(braket
id|E1000_STATS_LEN
)braket
suffix:semicolon
)brace
id|stats
op_assign
(brace
(brace
id|ETHTOOL_GSTATS
comma
id|E1000_STATS_LEN
)brace
)brace
suffix:semicolon
r_int
id|i
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
id|E1000_STATS_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|stats.data
(braket
id|i
)braket
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
op_amp
id|adapter-&gt;net_stats
)paren
(braket
id|i
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|addr
comma
op_amp
id|stats
comma
r_sizeof
(paren
id|stats
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
r_default
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
)brace
eof
