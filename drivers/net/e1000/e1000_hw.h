multiline_comment|/*******************************************************************************&n;&n;  This software program is available to you under a choice of one of two&n;  licenses. You may choose to be licensed under either the GNU General Public&n;  License 2.0, June 1991, available at http://www.fsf.org/copyleft/gpl.html,&n;  or the Intel BSD + Patent License, the text of which follows:&n;  &n;  Recipient has requested a license and Intel Corporation (&quot;Intel&quot;) is willing&n;  to grant a license for the software entitled Linux Base Driver for the&n;  Intel(R) PRO/1000 Family of Adapters (e1000) (the &quot;Software&quot;) being provided&n;  by Intel Corporation. The following definitions apply to this license:&n;  &n;  &quot;Licensed Patents&quot; means patent claims licensable by Intel Corporation which&n;  are necessarily infringed by the use of sale of the Software alone or when&n;  combined with the operating system referred to below.&n;  &n;  &quot;Recipient&quot; means the party to whom Intel delivers this Software.&n;  &n;  &quot;Licensee&quot; means Recipient and those third parties that receive a license to&n;  any operating system available under the GNU General Public License 2.0 or&n;  later.&n;  &n;  Copyright (c) 1999 - 2002 Intel Corporation.&n;  All rights reserved.&n;  &n;  The license is provided to Recipient and Recipient&squot;s Licensees under the&n;  following terms.&n;  &n;  Redistribution and use in source and binary forms of the Software, with or&n;  without modification, are permitted provided that the following conditions&n;  are met:&n;  &n;  Redistributions of source code of the Software may retain the above&n;  copyright notice, this list of conditions and the following disclaimer.&n;  &n;  Redistributions in binary form of the Software may reproduce the above&n;  copyright notice, this list of conditions and the following disclaimer in&n;  the documentation and/or materials provided with the distribution.&n;  &n;  Neither the name of Intel Corporation nor the names of its contributors&n;  shall be used to endorse or promote products derived from this Software&n;  without specific prior written permission.&n;  &n;  Intel hereby grants Recipient and Licensees a non-exclusive, worldwide,&n;  royalty-free patent license under Licensed Patents to make, use, sell, offer&n;  to sell, import and otherwise transfer the Software, if any, in source code&n;  and object code form. This license shall include changes to the Software&n;  that are error corrections or other minor changes to the Software that do&n;  not add functionality or features when the Software is incorporated in any&n;  version of an operating system that has been distributed under the GNU&n;  General Public License 2.0 or later. This patent license shall apply to the&n;  combination of the Software and any operating system licensed under the GNU&n;  General Public License 2.0 or later if, at the time Intel provides the&n;  Software to Recipient, such addition of the Software to the then publicly&n;  available versions of such operating systems available under the GNU General&n;  Public License 2.0 or later (whether in gold, beta or alpha form) causes&n;  such combination to be covered by the Licensed Patents. The patent license&n;  shall not apply to any other combinations which include the Software. NO&n;  hardware per se is licensed hereunder.&n;  &n;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS &quot;AS IS&quot;&n;  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n;  IMPLIED WARRANTIES OF MECHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n;  ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR IT CONTRIBUTORS BE LIABLE FOR ANY&n;  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES&n;  (INCLUDING, BUT NOT LIMITED, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;&n;  ANY LOSS OF USE; DATA, OR PROFITS; OR BUSINESS INTERUPTION) HOWEVER CAUSED&n;  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY OR&n;  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE&n;  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n;&n;*******************************************************************************/
multiline_comment|/* e1000_hw.h&n; * Structures, enums, and macros for the MAC&n; */
macro_line|#ifndef _E1000_HW_H_
DECL|macro|_E1000_HW_H_
mdefine_line|#define _E1000_HW_H_
macro_line|#include &quot;e1000_osdep.h&quot;
multiline_comment|/* Forward declarations of structures used by the shared code */
r_struct
id|e1000_hw
suffix:semicolon
r_struct
id|e1000_hw_stats
suffix:semicolon
multiline_comment|/* Enumerated types specific to the e1000 hardware */
multiline_comment|/* Media Access Controlers */
r_typedef
r_enum
(brace
DECL|enumerator|e1000_82542_rev2_0
id|e1000_82542_rev2_0
op_assign
l_int|0
comma
DECL|enumerator|e1000_82542_rev2_1
id|e1000_82542_rev2_1
comma
DECL|enumerator|e1000_82543
id|e1000_82543
comma
DECL|enumerator|e1000_82544
id|e1000_82544
comma
DECL|enumerator|e1000_82540
id|e1000_82540
comma
DECL|enumerator|e1000_82545
id|e1000_82545
comma
DECL|enumerator|e1000_82546
id|e1000_82546
comma
DECL|enumerator|e1000_num_macs
id|e1000_num_macs
DECL|typedef|e1000_mac_type
)brace
id|e1000_mac_type
suffix:semicolon
multiline_comment|/* Media Types */
r_typedef
r_enum
(brace
DECL|enumerator|e1000_media_type_copper
id|e1000_media_type_copper
op_assign
l_int|0
comma
DECL|enumerator|e1000_media_type_fiber
id|e1000_media_type_fiber
op_assign
l_int|1
comma
DECL|enumerator|e1000_num_media_types
id|e1000_num_media_types
DECL|typedef|e1000_media_type
)brace
id|e1000_media_type
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|e1000_10_half
id|e1000_10_half
op_assign
l_int|0
comma
DECL|enumerator|e1000_10_full
id|e1000_10_full
op_assign
l_int|1
comma
DECL|enumerator|e1000_100_half
id|e1000_100_half
op_assign
l_int|2
comma
DECL|enumerator|e1000_100_full
id|e1000_100_full
op_assign
l_int|3
DECL|typedef|e1000_speed_duplex_type
)brace
id|e1000_speed_duplex_type
suffix:semicolon
multiline_comment|/* Flow Control Settings */
r_typedef
r_enum
(brace
DECL|enumerator|e1000_fc_none
id|e1000_fc_none
op_assign
l_int|0
comma
DECL|enumerator|e1000_fc_rx_pause
id|e1000_fc_rx_pause
op_assign
l_int|1
comma
DECL|enumerator|e1000_fc_tx_pause
id|e1000_fc_tx_pause
op_assign
l_int|2
comma
DECL|enumerator|e1000_fc_full
id|e1000_fc_full
op_assign
l_int|3
comma
DECL|enumerator|e1000_fc_default
id|e1000_fc_default
op_assign
l_int|0xFF
DECL|typedef|e1000_fc_type
)brace
id|e1000_fc_type
suffix:semicolon
multiline_comment|/* PCI bus types */
r_typedef
r_enum
(brace
DECL|enumerator|e1000_bus_type_unknown
id|e1000_bus_type_unknown
op_assign
l_int|0
comma
DECL|enumerator|e1000_bus_type_pci
id|e1000_bus_type_pci
comma
DECL|enumerator|e1000_bus_type_pcix
id|e1000_bus_type_pcix
DECL|typedef|e1000_bus_type
)brace
id|e1000_bus_type
suffix:semicolon
multiline_comment|/* PCI bus speeds */
r_typedef
r_enum
(brace
DECL|enumerator|e1000_bus_speed_unknown
id|e1000_bus_speed_unknown
op_assign
l_int|0
comma
DECL|enumerator|e1000_bus_speed_33
id|e1000_bus_speed_33
comma
DECL|enumerator|e1000_bus_speed_66
id|e1000_bus_speed_66
comma
DECL|enumerator|e1000_bus_speed_100
id|e1000_bus_speed_100
comma
DECL|enumerator|e1000_bus_speed_133
id|e1000_bus_speed_133
comma
DECL|enumerator|e1000_bus_speed_reserved
id|e1000_bus_speed_reserved
DECL|typedef|e1000_bus_speed
)brace
id|e1000_bus_speed
suffix:semicolon
multiline_comment|/* PCI bus widths */
r_typedef
r_enum
(brace
DECL|enumerator|e1000_bus_width_unknown
id|e1000_bus_width_unknown
op_assign
l_int|0
comma
DECL|enumerator|e1000_bus_width_32
id|e1000_bus_width_32
comma
DECL|enumerator|e1000_bus_width_64
id|e1000_bus_width_64
DECL|typedef|e1000_bus_width
)brace
id|e1000_bus_width
suffix:semicolon
multiline_comment|/* PHY status info structure and supporting enums */
r_typedef
r_enum
(brace
DECL|enumerator|e1000_cable_length_50
id|e1000_cable_length_50
op_assign
l_int|0
comma
DECL|enumerator|e1000_cable_length_50_80
id|e1000_cable_length_50_80
comma
DECL|enumerator|e1000_cable_length_80_110
id|e1000_cable_length_80_110
comma
DECL|enumerator|e1000_cable_length_110_140
id|e1000_cable_length_110_140
comma
DECL|enumerator|e1000_cable_length_140
id|e1000_cable_length_140
comma
DECL|enumerator|e1000_cable_length_undefined
id|e1000_cable_length_undefined
op_assign
l_int|0xFF
DECL|typedef|e1000_cable_length
)brace
id|e1000_cable_length
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|e1000_10bt_ext_dist_enable_normal
id|e1000_10bt_ext_dist_enable_normal
op_assign
l_int|0
comma
DECL|enumerator|e1000_10bt_ext_dist_enable_lower
id|e1000_10bt_ext_dist_enable_lower
comma
DECL|enumerator|e1000_10bt_ext_dist_enable_undefined
id|e1000_10bt_ext_dist_enable_undefined
op_assign
l_int|0xFF
DECL|typedef|e1000_10bt_ext_dist_enable
)brace
id|e1000_10bt_ext_dist_enable
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|e1000_rev_polarity_normal
id|e1000_rev_polarity_normal
op_assign
l_int|0
comma
DECL|enumerator|e1000_rev_polarity_reversed
id|e1000_rev_polarity_reversed
comma
DECL|enumerator|e1000_rev_polarity_undefined
id|e1000_rev_polarity_undefined
op_assign
l_int|0xFF
DECL|typedef|e1000_rev_polarity
)brace
id|e1000_rev_polarity
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|e1000_polarity_reversal_enabled
id|e1000_polarity_reversal_enabled
op_assign
l_int|0
comma
DECL|enumerator|e1000_polarity_reversal_disabled
id|e1000_polarity_reversal_disabled
comma
DECL|enumerator|e1000_polarity_reversal_undefined
id|e1000_polarity_reversal_undefined
op_assign
l_int|0xFF
DECL|typedef|e1000_polarity_reversal
)brace
id|e1000_polarity_reversal
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|e1000_auto_x_mode_manual_mdi
id|e1000_auto_x_mode_manual_mdi
op_assign
l_int|0
comma
DECL|enumerator|e1000_auto_x_mode_manual_mdix
id|e1000_auto_x_mode_manual_mdix
comma
DECL|enumerator|e1000_auto_x_mode_auto1
id|e1000_auto_x_mode_auto1
comma
DECL|enumerator|e1000_auto_x_mode_auto2
id|e1000_auto_x_mode_auto2
comma
DECL|enumerator|e1000_auto_x_mode_undefined
id|e1000_auto_x_mode_undefined
op_assign
l_int|0xFF
DECL|typedef|e1000_auto_x_mode
)brace
id|e1000_auto_x_mode
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|e1000_1000t_rx_status_not_ok
id|e1000_1000t_rx_status_not_ok
op_assign
l_int|0
comma
DECL|enumerator|e1000_1000t_rx_status_ok
id|e1000_1000t_rx_status_ok
comma
DECL|enumerator|e1000_1000t_rx_status_undefined
id|e1000_1000t_rx_status_undefined
op_assign
l_int|0xFF
DECL|typedef|e1000_1000t_rx_status
)brace
id|e1000_1000t_rx_status
suffix:semicolon
DECL|struct|e1000_phy_info
r_struct
id|e1000_phy_info
(brace
DECL|member|cable_length
id|e1000_cable_length
id|cable_length
suffix:semicolon
DECL|member|extended_10bt_distance
id|e1000_10bt_ext_dist_enable
id|extended_10bt_distance
suffix:semicolon
DECL|member|cable_polarity
id|e1000_rev_polarity
id|cable_polarity
suffix:semicolon
DECL|member|polarity_correction
id|e1000_polarity_reversal
id|polarity_correction
suffix:semicolon
DECL|member|mdix_mode
id|e1000_auto_x_mode
id|mdix_mode
suffix:semicolon
DECL|member|local_rx
id|e1000_1000t_rx_status
id|local_rx
suffix:semicolon
DECL|member|remote_rx
id|e1000_1000t_rx_status
id|remote_rx
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|e1000_phy_stats
r_struct
id|e1000_phy_stats
(brace
DECL|member|idle_errors
r_uint32
id|idle_errors
suffix:semicolon
DECL|member|receive_errors
r_uint32
id|receive_errors
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Error Codes */
DECL|macro|E1000_SUCCESS
mdefine_line|#define E1000_SUCCESS    0
DECL|macro|E1000_ERR_EEPROM
mdefine_line|#define E1000_ERR_EEPROM 1
DECL|macro|E1000_ERR_PHY
mdefine_line|#define E1000_ERR_PHY    2
DECL|macro|E1000_ERR_CONFIG
mdefine_line|#define E1000_ERR_CONFIG 3
DECL|macro|E1000_ERR_PARAM
mdefine_line|#define E1000_ERR_PARAM  4
multiline_comment|/* Function prototypes */
multiline_comment|/* Initialization */
r_void
id|e1000_reset_hw
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_int32
id|e1000_init_hw
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
multiline_comment|/* Link Configuration */
r_int32
id|e1000_setup_link
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_int32
id|e1000_phy_setup_autoneg
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_void
id|e1000_config_collision_dist
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_int32
id|e1000_config_fc_after_link_up
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_int32
id|e1000_check_for_link
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_void
id|e1000_get_speed_and_duplex
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
comma
r_uint16
op_star
id|speed
comma
r_uint16
op_star
id|duplex
)paren
suffix:semicolon
r_int32
id|e1000_wait_autoneg
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
multiline_comment|/* PHY */
r_int32
id|e1000_read_phy_reg
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
comma
r_uint32
id|reg_addr
comma
r_uint16
op_star
id|phy_data
)paren
suffix:semicolon
r_int32
id|e1000_write_phy_reg
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
comma
r_uint32
id|reg_addr
comma
r_uint16
id|data
)paren
suffix:semicolon
r_void
id|e1000_phy_hw_reset
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_int32
id|e1000_phy_reset
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_int32
id|e1000_detect_gig_phy
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_int32
id|e1000_phy_get_info
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
comma
r_struct
id|e1000_phy_info
op_star
id|phy_info
)paren
suffix:semicolon
r_int32
id|e1000_validate_mdi_setting
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
multiline_comment|/* EEPROM Functions */
r_int32
id|e1000_read_eeprom
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
comma
r_uint16
id|reg
comma
r_uint16
op_star
id|data
)paren
suffix:semicolon
r_int32
id|e1000_validate_eeprom_checksum
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_int32
id|e1000_read_part_num
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
comma
r_uint32
op_star
id|part_num
)paren
suffix:semicolon
r_int32
id|e1000_read_mac_addr
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
multiline_comment|/* Filters (multicast, vlan, receive) */
r_void
id|e1000_init_rx_addrs
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_void
id|e1000_mc_addr_list_update
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
comma
r_uint8
op_star
id|mc_addr_list
comma
r_uint32
id|mc_addr_count
comma
r_uint32
id|pad
)paren
suffix:semicolon
r_uint32
id|e1000_hash_mc_addr
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
comma
r_uint8
op_star
id|mc_addr
)paren
suffix:semicolon
r_void
id|e1000_mta_set
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
comma
r_uint32
id|hash_value
)paren
suffix:semicolon
r_void
id|e1000_rar_set
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
comma
r_uint8
op_star
id|mc_addr
comma
r_uint32
id|rar_index
)paren
suffix:semicolon
r_void
id|e1000_write_vfta
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
comma
r_uint32
id|offset
comma
r_uint32
id|value
)paren
suffix:semicolon
r_void
id|e1000_clear_vfta
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
multiline_comment|/* LED functions */
r_int32
id|e1000_setup_led
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_int32
id|e1000_cleanup_led
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_int32
id|e1000_led_on
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_int32
id|e1000_led_off
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
multiline_comment|/* Adaptive IFS Functions */
multiline_comment|/* Everything else */
r_void
id|e1000_clear_hw_cntrs
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_void
id|e1000_reset_adaptive
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_void
id|e1000_update_adaptive
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_void
id|e1000_tbi_adjust_stats
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
comma
r_struct
id|e1000_hw_stats
op_star
id|stats
comma
r_uint32
id|frame_len
comma
r_uint8
op_star
id|mac_addr
)paren
suffix:semicolon
r_void
id|e1000_get_bus_info
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
)paren
suffix:semicolon
r_void
id|e1000_read_pci_cfg
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
comma
r_uint32
id|reg
comma
r_uint16
op_star
id|value
)paren
suffix:semicolon
r_void
id|e1000_write_pci_cfg
c_func
(paren
r_struct
id|e1000_hw
op_star
id|hw
comma
r_uint32
id|reg
comma
r_uint16
op_star
id|value
)paren
suffix:semicolon
multiline_comment|/* PCI Device IDs */
DECL|macro|E1000_DEV_ID_82542
mdefine_line|#define E1000_DEV_ID_82542          0x1000
DECL|macro|E1000_DEV_ID_82543GC_FIBER
mdefine_line|#define E1000_DEV_ID_82543GC_FIBER  0x1001
DECL|macro|E1000_DEV_ID_82543GC_COPPER
mdefine_line|#define E1000_DEV_ID_82543GC_COPPER 0x1004
DECL|macro|E1000_DEV_ID_82544EI_COPPER
mdefine_line|#define E1000_DEV_ID_82544EI_COPPER 0x1008
DECL|macro|E1000_DEV_ID_82544EI_FIBER
mdefine_line|#define E1000_DEV_ID_82544EI_FIBER  0x1009
DECL|macro|E1000_DEV_ID_82544GC_COPPER
mdefine_line|#define E1000_DEV_ID_82544GC_COPPER 0x100C
DECL|macro|E1000_DEV_ID_82544GC_LOM
mdefine_line|#define E1000_DEV_ID_82544GC_LOM    0x100D
DECL|macro|E1000_DEV_ID_82540EM
mdefine_line|#define E1000_DEV_ID_82540EM        0x100E
DECL|macro|E1000_DEV_ID_82540EM_LOM
mdefine_line|#define E1000_DEV_ID_82540EM_LOM    0x1015
DECL|macro|E1000_DEV_ID_82545EM_COPPER
mdefine_line|#define E1000_DEV_ID_82545EM_COPPER 0x100F
DECL|macro|E1000_DEV_ID_82545EM_FIBER
mdefine_line|#define E1000_DEV_ID_82545EM_FIBER  0x1011
DECL|macro|E1000_DEV_ID_82546EB_COPPER
mdefine_line|#define E1000_DEV_ID_82546EB_COPPER 0x1010
DECL|macro|E1000_DEV_ID_82546EB_FIBER
mdefine_line|#define E1000_DEV_ID_82546EB_FIBER  0x1012
DECL|macro|NUM_DEV_IDS
mdefine_line|#define NUM_DEV_IDS 13
DECL|macro|NODE_ADDRESS_SIZE
mdefine_line|#define NODE_ADDRESS_SIZE 6
DECL|macro|ETH_LENGTH_OF_ADDRESS
mdefine_line|#define ETH_LENGTH_OF_ADDRESS 6
multiline_comment|/* MAC decode size is 128K - This is the size of BAR0 */
DECL|macro|MAC_DECODE_SIZE
mdefine_line|#define MAC_DECODE_SIZE (128 * 1024)
DECL|macro|E1000_82542_2_0_REV_ID
mdefine_line|#define E1000_82542_2_0_REV_ID 2
DECL|macro|E1000_82542_2_1_REV_ID
mdefine_line|#define E1000_82542_2_1_REV_ID 3
DECL|macro|SPEED_10
mdefine_line|#define SPEED_10    10
DECL|macro|SPEED_100
mdefine_line|#define SPEED_100   100
DECL|macro|SPEED_1000
mdefine_line|#define SPEED_1000  1000
DECL|macro|HALF_DUPLEX
mdefine_line|#define HALF_DUPLEX 1
DECL|macro|FULL_DUPLEX
mdefine_line|#define FULL_DUPLEX 2
multiline_comment|/* The sizes (in bytes) of a ethernet packet */
DECL|macro|ENET_HEADER_SIZE
mdefine_line|#define ENET_HEADER_SIZE             14
DECL|macro|MAXIMUM_ETHERNET_FRAME_SIZE
mdefine_line|#define MAXIMUM_ETHERNET_FRAME_SIZE  1518 /* With FCS */
DECL|macro|MINIMUM_ETHERNET_FRAME_SIZE
mdefine_line|#define MINIMUM_ETHERNET_FRAME_SIZE  64   /* With FCS */
DECL|macro|ETHERNET_FCS_SIZE
mdefine_line|#define ETHERNET_FCS_SIZE            4
DECL|macro|MAXIMUM_ETHERNET_PACKET_SIZE
mdefine_line|#define MAXIMUM_ETHERNET_PACKET_SIZE &bslash;&n;    (MAXIMUM_ETHERNET_FRAME_SIZE - ETHERNET_FCS_SIZE)
DECL|macro|MINIMUM_ETHERNET_PACKET_SIZE
mdefine_line|#define MINIMUM_ETHERNET_PACKET_SIZE &bslash;&n;    (MINIMUM_ETHERNET_FRAME_SIZE - ETHERNET_FCS_SIZE)
DECL|macro|CRC_LENGTH
mdefine_line|#define CRC_LENGTH                   ETHERNET_FCS_SIZE
DECL|macro|MAX_JUMBO_FRAME_SIZE
mdefine_line|#define MAX_JUMBO_FRAME_SIZE         0x3F00
multiline_comment|/* 802.1q VLAN Packet Sizes */
DECL|macro|VLAN_TAG_SIZE
mdefine_line|#define VLAN_TAG_SIZE                     4     /* 802.3ac tag (not DMAed) */
multiline_comment|/* Ethertype field values */
DECL|macro|ETHERNET_IEEE_VLAN_TYPE
mdefine_line|#define ETHERNET_IEEE_VLAN_TYPE 0x8100  /* 802.3ac packet */
DECL|macro|ETHERNET_IP_TYPE
mdefine_line|#define ETHERNET_IP_TYPE        0x0800  /* IP packets */
DECL|macro|ETHERNET_ARP_TYPE
mdefine_line|#define ETHERNET_ARP_TYPE       0x0806  /* Address Resolution Protocol (ARP) */
multiline_comment|/* Packet Header defines */
DECL|macro|IP_PROTOCOL_TCP
mdefine_line|#define IP_PROTOCOL_TCP    6
DECL|macro|IP_PROTOCOL_UDP
mdefine_line|#define IP_PROTOCOL_UDP    0x11
multiline_comment|/* This defines the bits that are set in the Interrupt Mask&n; * Set/Read Register.  Each bit is documented below:&n; *   o RXDMT0 = Receive Descriptor Minimum Threshold hit (ring 0)&n; *   o RXSEQ  = Receive Sequence Error &n; */
DECL|macro|POLL_IMS_ENABLE_MASK
mdefine_line|#define POLL_IMS_ENABLE_MASK ( &bslash;&n;    E1000_IMS_RXDMT0 |         &bslash;&n;    E1000_IMS_RXSEQ)
multiline_comment|/* This defines the bits that are set in the Interrupt Mask&n; * Set/Read Register.  Each bit is documented below:&n; *   o RXT0   = Receiver Timer Interrupt (ring 0)&n; *   o TXDW   = Transmit Descriptor Written Back&n; *   o RXDMT0 = Receive Descriptor Minimum Threshold hit (ring 0)&n; *   o RXSEQ  = Receive Sequence Error&n; *   o LSC    = Link Status Change&n; */
DECL|macro|IMS_ENABLE_MASK
mdefine_line|#define IMS_ENABLE_MASK ( &bslash;&n;    E1000_IMS_RXT0   |    &bslash;&n;    E1000_IMS_TXDW   |    &bslash;&n;    E1000_IMS_RXDMT0 |    &bslash;&n;    E1000_IMS_RXSEQ  |    &bslash;&n;    E1000_IMS_LSC)
multiline_comment|/* The number of high/low register pairs in the RAR. The RAR (Receive Address&n; * Registers) holds the directed and multicast addresses that we monitor. We&n; * reserve one of these spots for our directed address, allowing us room for&n; * E1000_RAR_ENTRIES - 1 multicast addresses. &n; */
DECL|macro|E1000_RAR_ENTRIES
mdefine_line|#define E1000_RAR_ENTRIES 16
DECL|macro|MIN_NUMBER_OF_DESCRIPTORS
mdefine_line|#define MIN_NUMBER_OF_DESCRIPTORS 8
DECL|macro|MAX_NUMBER_OF_DESCRIPTORS
mdefine_line|#define MAX_NUMBER_OF_DESCRIPTORS 0xFFF8
multiline_comment|/* Receive Descriptor */
DECL|struct|e1000_rx_desc
r_struct
id|e1000_rx_desc
(brace
DECL|member|buffer_addr
r_uint64
id|buffer_addr
suffix:semicolon
multiline_comment|/* Address of the descriptor&squot;s data buffer */
DECL|member|length
r_uint16
id|length
suffix:semicolon
multiline_comment|/* Length of data DMAed into data buffer */
DECL|member|csum
r_uint16
id|csum
suffix:semicolon
multiline_comment|/* Packet checksum */
DECL|member|status
r_uint8
id|status
suffix:semicolon
multiline_comment|/* Descriptor status */
DECL|member|errors
r_uint8
id|errors
suffix:semicolon
multiline_comment|/* Descriptor Errors */
DECL|member|special
r_uint16
id|special
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Receive Decriptor bit definitions */
DECL|macro|E1000_RXD_STAT_DD
mdefine_line|#define E1000_RXD_STAT_DD       0x01    /* Descriptor Done */
DECL|macro|E1000_RXD_STAT_EOP
mdefine_line|#define E1000_RXD_STAT_EOP      0x02    /* End of Packet */
DECL|macro|E1000_RXD_STAT_IXSM
mdefine_line|#define E1000_RXD_STAT_IXSM     0x04    /* Ignore checksum */
DECL|macro|E1000_RXD_STAT_VP
mdefine_line|#define E1000_RXD_STAT_VP       0x08    /* IEEE VLAN Packet */
DECL|macro|E1000_RXD_STAT_TCPCS
mdefine_line|#define E1000_RXD_STAT_TCPCS    0x20    /* TCP xsum calculated */
DECL|macro|E1000_RXD_STAT_IPCS
mdefine_line|#define E1000_RXD_STAT_IPCS     0x40    /* IP xsum calculated */
DECL|macro|E1000_RXD_STAT_PIF
mdefine_line|#define E1000_RXD_STAT_PIF      0x80    /* passed in-exact filter */
DECL|macro|E1000_RXD_ERR_CE
mdefine_line|#define E1000_RXD_ERR_CE        0x01    /* CRC Error */
DECL|macro|E1000_RXD_ERR_SE
mdefine_line|#define E1000_RXD_ERR_SE        0x02    /* Symbol Error */
DECL|macro|E1000_RXD_ERR_SEQ
mdefine_line|#define E1000_RXD_ERR_SEQ       0x04    /* Sequence Error */
DECL|macro|E1000_RXD_ERR_CXE
mdefine_line|#define E1000_RXD_ERR_CXE       0x10    /* Carrier Extension Error */
DECL|macro|E1000_RXD_ERR_TCPE
mdefine_line|#define E1000_RXD_ERR_TCPE      0x20    /* TCP/UDP Checksum Error */
DECL|macro|E1000_RXD_ERR_IPE
mdefine_line|#define E1000_RXD_ERR_IPE       0x40    /* IP Checksum Error */
DECL|macro|E1000_RXD_ERR_RXE
mdefine_line|#define E1000_RXD_ERR_RXE       0x80    /* Rx Data Error */
DECL|macro|E1000_RXD_SPC_VLAN_MASK
mdefine_line|#define E1000_RXD_SPC_VLAN_MASK 0x0FFF  /* VLAN ID is in lower 12 bits */
DECL|macro|E1000_RXD_SPC_PRI_MASK
mdefine_line|#define E1000_RXD_SPC_PRI_MASK  0xE000  /* Priority is in upper 3 bits */
DECL|macro|E1000_RXD_SPC_PRI_SHIFT
mdefine_line|#define E1000_RXD_SPC_PRI_SHIFT 0x000D  /* Priority is in upper 3 of 16 */
DECL|macro|E1000_RXD_SPC_CFI_MASK
mdefine_line|#define E1000_RXD_SPC_CFI_MASK  0x1000  /* CFI is bit 12 */
DECL|macro|E1000_RXD_SPC_CFI_SHIFT
mdefine_line|#define E1000_RXD_SPC_CFI_SHIFT 0x000C  /* CFI is bit 12 */
multiline_comment|/* mask to determine if packets should be dropped due to frame errors */
DECL|macro|E1000_RXD_ERR_FRAME_ERR_MASK
mdefine_line|#define E1000_RXD_ERR_FRAME_ERR_MASK ( &bslash;&n;    E1000_RXD_ERR_CE  |                &bslash;&n;    E1000_RXD_ERR_SE  |                &bslash;&n;    E1000_RXD_ERR_SEQ |                &bslash;&n;    E1000_RXD_ERR_CXE |                &bslash;&n;    E1000_RXD_ERR_RXE)
multiline_comment|/* Transmit Descriptor */
DECL|struct|e1000_tx_desc
r_struct
id|e1000_tx_desc
(brace
DECL|member|buffer_addr
r_uint64
id|buffer_addr
suffix:semicolon
multiline_comment|/* Address of the descriptor&squot;s data buffer */
r_union
(brace
DECL|member|data
r_uint32
id|data
suffix:semicolon
r_struct
(brace
DECL|member|length
r_uint16
id|length
suffix:semicolon
multiline_comment|/* Data buffer length */
DECL|member|cso
r_uint8
id|cso
suffix:semicolon
multiline_comment|/* Checksum offset */
DECL|member|cmd
r_uint8
id|cmd
suffix:semicolon
multiline_comment|/* Descriptor control */
DECL|member|flags
)brace
id|flags
suffix:semicolon
DECL|member|lower
)brace
id|lower
suffix:semicolon
r_union
(brace
DECL|member|data
r_uint32
id|data
suffix:semicolon
r_struct
(brace
DECL|member|status
r_uint8
id|status
suffix:semicolon
multiline_comment|/* Descriptor status */
DECL|member|css
r_uint8
id|css
suffix:semicolon
multiline_comment|/* Checksum start */
DECL|member|special
r_uint16
id|special
suffix:semicolon
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|member|upper
)brace
id|upper
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Transmit Descriptor bit definitions */
DECL|macro|E1000_TXD_DTYP_D
mdefine_line|#define E1000_TXD_DTYP_D     0x00100000 /* Data Descriptor */
DECL|macro|E1000_TXD_DTYP_C
mdefine_line|#define E1000_TXD_DTYP_C     0x00000000 /* Context Descriptor */
DECL|macro|E1000_TXD_POPTS_IXSM
mdefine_line|#define E1000_TXD_POPTS_IXSM 0x01       /* Insert IP checksum */
DECL|macro|E1000_TXD_POPTS_TXSM
mdefine_line|#define E1000_TXD_POPTS_TXSM 0x02       /* Insert TCP/UDP checksum */
DECL|macro|E1000_TXD_CMD_EOP
mdefine_line|#define E1000_TXD_CMD_EOP    0x01000000 /* End of Packet */
DECL|macro|E1000_TXD_CMD_IFCS
mdefine_line|#define E1000_TXD_CMD_IFCS   0x02000000 /* Insert FCS (Ethernet CRC) */
DECL|macro|E1000_TXD_CMD_IC
mdefine_line|#define E1000_TXD_CMD_IC     0x04000000 /* Insert Checksum */
DECL|macro|E1000_TXD_CMD_RS
mdefine_line|#define E1000_TXD_CMD_RS     0x08000000 /* Report Status */
DECL|macro|E1000_TXD_CMD_RPS
mdefine_line|#define E1000_TXD_CMD_RPS    0x10000000 /* Report Packet Sent */
DECL|macro|E1000_TXD_CMD_DEXT
mdefine_line|#define E1000_TXD_CMD_DEXT   0x20000000 /* Descriptor extension (0 = legacy) */
DECL|macro|E1000_TXD_CMD_VLE
mdefine_line|#define E1000_TXD_CMD_VLE    0x40000000 /* Add VLAN tag */
DECL|macro|E1000_TXD_CMD_IDE
mdefine_line|#define E1000_TXD_CMD_IDE    0x80000000 /* Enable Tidv register */
DECL|macro|E1000_TXD_STAT_DD
mdefine_line|#define E1000_TXD_STAT_DD    0x00000001 /* Descriptor Done */
DECL|macro|E1000_TXD_STAT_EC
mdefine_line|#define E1000_TXD_STAT_EC    0x00000002 /* Excess Collisions */
DECL|macro|E1000_TXD_STAT_LC
mdefine_line|#define E1000_TXD_STAT_LC    0x00000004 /* Late Collisions */
DECL|macro|E1000_TXD_STAT_TU
mdefine_line|#define E1000_TXD_STAT_TU    0x00000008 /* Transmit underrun */
DECL|macro|E1000_TXD_CMD_TCP
mdefine_line|#define E1000_TXD_CMD_TCP    0x01000000 /* TCP packet */
DECL|macro|E1000_TXD_CMD_IP
mdefine_line|#define E1000_TXD_CMD_IP     0x02000000 /* IP packet */
DECL|macro|E1000_TXD_CMD_TSE
mdefine_line|#define E1000_TXD_CMD_TSE    0x04000000 /* TCP Seg enable */
DECL|macro|E1000_TXD_STAT_TC
mdefine_line|#define E1000_TXD_STAT_TC    0x00000004 /* Tx Underrun */
multiline_comment|/* Offload Context Descriptor */
DECL|struct|e1000_context_desc
r_struct
id|e1000_context_desc
(brace
r_union
(brace
DECL|member|ip_config
r_uint32
id|ip_config
suffix:semicolon
r_struct
(brace
DECL|member|ipcss
r_uint8
id|ipcss
suffix:semicolon
multiline_comment|/* IP checksum start */
DECL|member|ipcso
r_uint8
id|ipcso
suffix:semicolon
multiline_comment|/* IP checksum offset */
DECL|member|ipcse
r_uint16
id|ipcse
suffix:semicolon
multiline_comment|/* IP checksum end */
DECL|member|ip_fields
)brace
id|ip_fields
suffix:semicolon
DECL|member|lower_setup
)brace
id|lower_setup
suffix:semicolon
r_union
(brace
DECL|member|tcp_config
r_uint32
id|tcp_config
suffix:semicolon
r_struct
(brace
DECL|member|tucss
r_uint8
id|tucss
suffix:semicolon
multiline_comment|/* TCP checksum start */
DECL|member|tucso
r_uint8
id|tucso
suffix:semicolon
multiline_comment|/* TCP checksum offset */
DECL|member|tucse
r_uint16
id|tucse
suffix:semicolon
multiline_comment|/* TCP checksum end */
DECL|member|tcp_fields
)brace
id|tcp_fields
suffix:semicolon
DECL|member|upper_setup
)brace
id|upper_setup
suffix:semicolon
DECL|member|cmd_and_length
r_uint32
id|cmd_and_length
suffix:semicolon
multiline_comment|/* */
r_union
(brace
DECL|member|data
r_uint32
id|data
suffix:semicolon
r_struct
(brace
DECL|member|status
r_uint8
id|status
suffix:semicolon
multiline_comment|/* Descriptor status */
DECL|member|hdr_len
r_uint8
id|hdr_len
suffix:semicolon
multiline_comment|/* Header length */
DECL|member|mss
r_uint16
id|mss
suffix:semicolon
multiline_comment|/* Maximum segment size */
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|member|tcp_seg_setup
)brace
id|tcp_seg_setup
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Offload data descriptor */
DECL|struct|e1000_data_desc
r_struct
id|e1000_data_desc
(brace
DECL|member|buffer_addr
r_uint64
id|buffer_addr
suffix:semicolon
multiline_comment|/* Address of the descriptor&squot;s buffer address */
r_union
(brace
DECL|member|data
r_uint32
id|data
suffix:semicolon
r_struct
(brace
DECL|member|length
r_uint16
id|length
suffix:semicolon
multiline_comment|/* Data buffer length */
DECL|member|typ_len_ext
r_uint8
id|typ_len_ext
suffix:semicolon
multiline_comment|/* */
DECL|member|cmd
r_uint8
id|cmd
suffix:semicolon
multiline_comment|/* */
DECL|member|flags
)brace
id|flags
suffix:semicolon
DECL|member|lower
)brace
id|lower
suffix:semicolon
r_union
(brace
DECL|member|data
r_uint32
id|data
suffix:semicolon
r_struct
(brace
DECL|member|status
r_uint8
id|status
suffix:semicolon
multiline_comment|/* Descriptor status */
DECL|member|popts
r_uint8
id|popts
suffix:semicolon
multiline_comment|/* Packet Options */
DECL|member|special
r_uint16
id|special
suffix:semicolon
multiline_comment|/* */
DECL|member|fields
)brace
id|fields
suffix:semicolon
DECL|member|upper
)brace
id|upper
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Filters */
DECL|macro|E1000_NUM_UNICAST
mdefine_line|#define E1000_NUM_UNICAST          16   /* Unicast filter entries */
DECL|macro|E1000_MC_TBL_SIZE
mdefine_line|#define E1000_MC_TBL_SIZE          128  /* Multicast Filter Table (4096 bits) */
DECL|macro|E1000_VLAN_FILTER_TBL_SIZE
mdefine_line|#define E1000_VLAN_FILTER_TBL_SIZE 128  /* VLAN Filter Table (4096 bits) */
multiline_comment|/* Receive Address Register */
DECL|struct|e1000_rar
r_struct
id|e1000_rar
(brace
DECL|member|low
r_volatile
r_uint32
id|low
suffix:semicolon
multiline_comment|/* receive address low */
DECL|member|high
r_volatile
r_uint32
id|high
suffix:semicolon
multiline_comment|/* receive address high */
)brace
suffix:semicolon
multiline_comment|/* The number of entries in the Multicast Table Array (MTA). */
DECL|macro|E1000_NUM_MTA_REGISTERS
mdefine_line|#define E1000_NUM_MTA_REGISTERS 128
multiline_comment|/* IPv4 Address Table Entry */
DECL|struct|e1000_ipv4_at_entry
r_struct
id|e1000_ipv4_at_entry
(brace
DECL|member|ipv4_addr
r_volatile
r_uint32
id|ipv4_addr
suffix:semicolon
multiline_comment|/* IP Address (RW) */
DECL|member|reserved
r_volatile
r_uint32
id|reserved
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Four wakeup IP addresses are supported */
DECL|macro|E1000_WAKEUP_IP_ADDRESS_COUNT_MAX
mdefine_line|#define E1000_WAKEUP_IP_ADDRESS_COUNT_MAX 4
DECL|macro|E1000_IP4AT_SIZE
mdefine_line|#define E1000_IP4AT_SIZE                  E1000_WAKEUP_IP_ADDRESS_COUNT_MAX
DECL|macro|E1000_IP6AT_SIZE
mdefine_line|#define E1000_IP6AT_SIZE                  1
multiline_comment|/* IPv6 Address Table Entry */
DECL|struct|e1000_ipv6_at_entry
r_struct
id|e1000_ipv6_at_entry
(brace
DECL|member|ipv6_addr
r_volatile
r_uint8
id|ipv6_addr
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Flexible Filter Length Table Entry */
DECL|struct|e1000_fflt_entry
r_struct
id|e1000_fflt_entry
(brace
DECL|member|length
r_volatile
r_uint32
id|length
suffix:semicolon
multiline_comment|/* Flexible Filter Length (RW) */
DECL|member|reserved
r_volatile
r_uint32
id|reserved
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Flexible Filter Mask Table Entry */
DECL|struct|e1000_ffmt_entry
r_struct
id|e1000_ffmt_entry
(brace
DECL|member|mask
r_volatile
r_uint32
id|mask
suffix:semicolon
multiline_comment|/* Flexible Filter Mask (RW) */
DECL|member|reserved
r_volatile
r_uint32
id|reserved
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Flexible Filter Value Table Entry */
DECL|struct|e1000_ffvt_entry
r_struct
id|e1000_ffvt_entry
(brace
DECL|member|value
r_volatile
r_uint32
id|value
suffix:semicolon
multiline_comment|/* Flexible Filter Value (RW) */
DECL|member|reserved
r_volatile
r_uint32
id|reserved
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Four Flexible Filters are supported */
DECL|macro|E1000_FLEXIBLE_FILTER_COUNT_MAX
mdefine_line|#define E1000_FLEXIBLE_FILTER_COUNT_MAX 4
multiline_comment|/* Each Flexible Filter is at most 128 (0x80) bytes in length */
DECL|macro|E1000_FLEXIBLE_FILTER_SIZE_MAX
mdefine_line|#define E1000_FLEXIBLE_FILTER_SIZE_MAX  128
DECL|macro|E1000_FFLT_SIZE
mdefine_line|#define E1000_FFLT_SIZE E1000_FLEXIBLE_FILTER_COUNT_MAX
DECL|macro|E1000_FFMT_SIZE
mdefine_line|#define E1000_FFMT_SIZE E1000_FLEXIBLE_FILTER_SIZE_MAX
DECL|macro|E1000_FFVT_SIZE
mdefine_line|#define E1000_FFVT_SIZE E1000_FLEXIBLE_FILTER_SIZE_MAX
multiline_comment|/* Register Set. (82543, 82544)&n; *&n; * Registers are defined to be 32 bits and  should be accessed as 32 bit values.&n; * These registers are physically located on the NIC, but are mapped into the &n; * host memory address space.&n; *&n; * RW - register is both readable and writable&n; * RO - register is read only&n; * WO - register is write only&n; * R/clr - register is read only and is cleared when read&n; * A - register array&n; */
DECL|macro|E1000_CTRL
mdefine_line|#define E1000_CTRL     0x00000  /* Device Control - RW */
DECL|macro|E1000_STATUS
mdefine_line|#define E1000_STATUS   0x00008  /* Device Status - RO */
DECL|macro|E1000_EECD
mdefine_line|#define E1000_EECD     0x00010  /* EEPROM/Flash Control - RW */
DECL|macro|E1000_EERD
mdefine_line|#define E1000_EERD     0x00014  /* EEPROM Read - RW */
DECL|macro|E1000_CTRL_EXT
mdefine_line|#define E1000_CTRL_EXT 0x00018  /* Extended Device Control - RW */
DECL|macro|E1000_MDIC
mdefine_line|#define E1000_MDIC     0x00020  /* MDI Control - RW */
DECL|macro|E1000_FCAL
mdefine_line|#define E1000_FCAL     0x00028  /* Flow Control Address Low - RW */
DECL|macro|E1000_FCAH
mdefine_line|#define E1000_FCAH     0x0002C  /* Flow Control Address High -RW */
DECL|macro|E1000_FCT
mdefine_line|#define E1000_FCT      0x00030  /* Flow Control Type - RW */
DECL|macro|E1000_VET
mdefine_line|#define E1000_VET      0x00038  /* VLAN Ether Type - RW */
DECL|macro|E1000_ICR
mdefine_line|#define E1000_ICR      0x000C0  /* Interrupt Cause Read - R/clr */
DECL|macro|E1000_ITR
mdefine_line|#define E1000_ITR      0x000C4  /* Interrupt Throttling Rate - RW */
DECL|macro|E1000_ICS
mdefine_line|#define E1000_ICS      0x000C8  /* Interrupt Cause Set - WO */
DECL|macro|E1000_IMS
mdefine_line|#define E1000_IMS      0x000D0  /* Interrupt Mask Set - RW */
DECL|macro|E1000_IMC
mdefine_line|#define E1000_IMC      0x000D8  /* Interrupt Mask Clear - WO */
DECL|macro|E1000_RCTL
mdefine_line|#define E1000_RCTL     0x00100  /* RX Control - RW */
DECL|macro|E1000_FCTTV
mdefine_line|#define E1000_FCTTV    0x00170  /* Flow Control Transmit Timer Value - RW */
DECL|macro|E1000_TXCW
mdefine_line|#define E1000_TXCW     0x00178  /* TX Configuration Word - RW */
DECL|macro|E1000_RXCW
mdefine_line|#define E1000_RXCW     0x00180  /* RX Configuration Word - RO */
DECL|macro|E1000_TCTL
mdefine_line|#define E1000_TCTL     0x00400  /* TX Control - RW */
DECL|macro|E1000_TIPG
mdefine_line|#define E1000_TIPG     0x00410  /* TX Inter-packet gap -RW */
DECL|macro|E1000_TBT
mdefine_line|#define E1000_TBT      0x00448  /* TX Burst Timer - RW */
DECL|macro|E1000_AIT
mdefine_line|#define E1000_AIT      0x00458  /* Adaptive Interframe Spacing Throttle - RW */
DECL|macro|E1000_LEDCTL
mdefine_line|#define E1000_LEDCTL   0x00E00  /* LED Control - RW */
DECL|macro|E1000_PBA
mdefine_line|#define E1000_PBA      0x01000  /* Packet Buffer Allocation - RW */
DECL|macro|E1000_FCRTL
mdefine_line|#define E1000_FCRTL    0x02160  /* Flow Control Receive Threshold Low - RW */
DECL|macro|E1000_FCRTH
mdefine_line|#define E1000_FCRTH    0x02168  /* Flow Control Receive Threshold High - RW */
DECL|macro|E1000_RDBAL
mdefine_line|#define E1000_RDBAL    0x02800  /* RX Descriptor Base Address Low - RW */
DECL|macro|E1000_RDBAH
mdefine_line|#define E1000_RDBAH    0x02804  /* RX Descriptor Base Address High - RW */
DECL|macro|E1000_RDLEN
mdefine_line|#define E1000_RDLEN    0x02808  /* RX Descriptor Length - RW */
DECL|macro|E1000_RDH
mdefine_line|#define E1000_RDH      0x02810  /* RX Descriptor Head - RW */
DECL|macro|E1000_RDT
mdefine_line|#define E1000_RDT      0x02818  /* RX Descriptor Tail - RW */
DECL|macro|E1000_RDTR
mdefine_line|#define E1000_RDTR     0x02820  /* RX Delay Timer - RW */
DECL|macro|E1000_RXDCTL
mdefine_line|#define E1000_RXDCTL   0x02828  /* RX Descriptor Control - RW */
DECL|macro|E1000_RADV
mdefine_line|#define E1000_RADV     0x0282C  /* RX Interrupt Absolute Delay Timer - RW */
DECL|macro|E1000_RSRPD
mdefine_line|#define E1000_RSRPD    0x02C00  /* RX Small Packet Detect - RW */
DECL|macro|E1000_TXDMAC
mdefine_line|#define E1000_TXDMAC   0x03000  /* TX DMA Control - RW */
DECL|macro|E1000_TDBAL
mdefine_line|#define E1000_TDBAL    0x03800  /* TX Descriptor Base Address Low - RW */
DECL|macro|E1000_TDBAH
mdefine_line|#define E1000_TDBAH    0x03804  /* TX Descriptor Base Address High - RW */
DECL|macro|E1000_TDLEN
mdefine_line|#define E1000_TDLEN    0x03808  /* TX Descriptor Length - RW */
DECL|macro|E1000_TDH
mdefine_line|#define E1000_TDH      0x03810  /* TX Descriptor Head - RW */
DECL|macro|E1000_TDT
mdefine_line|#define E1000_TDT      0x03818  /* TX Descripotr Tail - RW */
DECL|macro|E1000_TIDV
mdefine_line|#define E1000_TIDV     0x03820  /* TX Interrupt Delay Value - RW */
DECL|macro|E1000_TXDCTL
mdefine_line|#define E1000_TXDCTL   0x03828  /* TX Descriptor Control - RW */
DECL|macro|E1000_TADV
mdefine_line|#define E1000_TADV     0x0382C  /* TX Interrupt Absolute Delay Val - RW */
DECL|macro|E1000_TSPMT
mdefine_line|#define E1000_TSPMT    0x03830  /* TCP Segmentation PAD &amp; Min Threshold - RW */
DECL|macro|E1000_CRCERRS
mdefine_line|#define E1000_CRCERRS  0x04000  /* CRC Error Count - R/clr */
DECL|macro|E1000_ALGNERRC
mdefine_line|#define E1000_ALGNERRC 0x04004  /* Alignment Error Count - R/clr */
DECL|macro|E1000_SYMERRS
mdefine_line|#define E1000_SYMERRS  0x04008  /* Symbol Error Count - R/clr */
DECL|macro|E1000_RXERRC
mdefine_line|#define E1000_RXERRC   0x0400C  /* Receive Error Count - R/clr */
DECL|macro|E1000_MPC
mdefine_line|#define E1000_MPC      0x04010  /* Missed Packet Count - R/clr */
DECL|macro|E1000_SCC
mdefine_line|#define E1000_SCC      0x04014  /* Single Collision Count - R/clr */
DECL|macro|E1000_ECOL
mdefine_line|#define E1000_ECOL     0x04018  /* Excessive Collision Count - R/clr */
DECL|macro|E1000_MCC
mdefine_line|#define E1000_MCC      0x0401C  /* Multiple Collision Count - R/clr */
DECL|macro|E1000_LATECOL
mdefine_line|#define E1000_LATECOL  0x04020  /* Late Collision Count - R/clr */
DECL|macro|E1000_COLC
mdefine_line|#define E1000_COLC     0x04028  /* Collision Count - R/clr */
DECL|macro|E1000_DC
mdefine_line|#define E1000_DC       0x04030  /* Defer Count - R/clr */
DECL|macro|E1000_TNCRS
mdefine_line|#define E1000_TNCRS    0x04034  /* TX-No CRS - R/clr */
DECL|macro|E1000_SEC
mdefine_line|#define E1000_SEC      0x04038  /* Sequence Error Count - R/clr */
DECL|macro|E1000_CEXTERR
mdefine_line|#define E1000_CEXTERR  0x0403C  /* Carrier Extension Error Count - R/clr */
DECL|macro|E1000_RLEC
mdefine_line|#define E1000_RLEC     0x04040  /* Receive Length Error Count - R/clr */
DECL|macro|E1000_XONRXC
mdefine_line|#define E1000_XONRXC   0x04048  /* XON RX Count - R/clr */
DECL|macro|E1000_XONTXC
mdefine_line|#define E1000_XONTXC   0x0404C  /* XON TX Count - R/clr */
DECL|macro|E1000_XOFFRXC
mdefine_line|#define E1000_XOFFRXC  0x04050  /* XOFF RX Count - R/clr */
DECL|macro|E1000_XOFFTXC
mdefine_line|#define E1000_XOFFTXC  0x04054  /* XOFF TX Count - R/clr */
DECL|macro|E1000_FCRUC
mdefine_line|#define E1000_FCRUC    0x04058  /* Flow Control RX Unsupported Count- R/clr */
DECL|macro|E1000_PRC64
mdefine_line|#define E1000_PRC64    0x0405C  /* Packets RX (64 bytes) - R/clr */
DECL|macro|E1000_PRC127
mdefine_line|#define E1000_PRC127   0x04060  /* Packets RX (65-127 bytes) - R/clr */
DECL|macro|E1000_PRC255
mdefine_line|#define E1000_PRC255   0x04064  /* Packets RX (128-255 bytes) - R/clr */
DECL|macro|E1000_PRC511
mdefine_line|#define E1000_PRC511   0x04068  /* Packets RX (255-511 bytes) - R/clr */
DECL|macro|E1000_PRC1023
mdefine_line|#define E1000_PRC1023  0x0406C  /* Packets RX (512-1023 bytes) - R/clr */
DECL|macro|E1000_PRC1522
mdefine_line|#define E1000_PRC1522  0x04070  /* Packets RX (1024-1522 bytes) - R/clr */
DECL|macro|E1000_GPRC
mdefine_line|#define E1000_GPRC     0x04074  /* Good Packets RX Count - R/clr */
DECL|macro|E1000_BPRC
mdefine_line|#define E1000_BPRC     0x04078  /* Broadcast Packets RX Count - R/clr */
DECL|macro|E1000_MPRC
mdefine_line|#define E1000_MPRC     0x0407C  /* Multicast Packets RX Count - R/clr */
DECL|macro|E1000_GPTC
mdefine_line|#define E1000_GPTC     0x04080  /* Good Packets TX Count - R/clr */
DECL|macro|E1000_GORCL
mdefine_line|#define E1000_GORCL    0x04088  /* Good Octets RX Count Low - R/clr */
DECL|macro|E1000_GORCH
mdefine_line|#define E1000_GORCH    0x0408C  /* Good Octets RX Count High - R/clr */
DECL|macro|E1000_GOTCL
mdefine_line|#define E1000_GOTCL    0x04090  /* Good Octets TX Count Low - R/clr */
DECL|macro|E1000_GOTCH
mdefine_line|#define E1000_GOTCH    0x04094  /* Good Octets TX Count High - R/clr */
DECL|macro|E1000_RNBC
mdefine_line|#define E1000_RNBC     0x040A0  /* RX No Buffers Count - R/clr */
DECL|macro|E1000_RUC
mdefine_line|#define E1000_RUC      0x040A4  /* RX Undersize Count - R/clr */
DECL|macro|E1000_RFC
mdefine_line|#define E1000_RFC      0x040A8  /* RX Fragment Count - R/clr */
DECL|macro|E1000_ROC
mdefine_line|#define E1000_ROC      0x040AC  /* RX Oversize Count - R/clr */
DECL|macro|E1000_RJC
mdefine_line|#define E1000_RJC      0x040B0  /* RX Jabber Count - R/clr */
DECL|macro|E1000_MGTPRC
mdefine_line|#define E1000_MGTPRC   0x040B4  /* Management Packets RX Count - R/clr */
DECL|macro|E1000_MGTPDC
mdefine_line|#define E1000_MGTPDC   0x040B8  /* Management Packets Dropped Count - R/clr */
DECL|macro|E1000_MGTPTC
mdefine_line|#define E1000_MGTPTC   0x040BC  /* Management Packets TX Count - R/clr */
DECL|macro|E1000_TORL
mdefine_line|#define E1000_TORL     0x040C0  /* Total Octets RX Low - R/clr */
DECL|macro|E1000_TORH
mdefine_line|#define E1000_TORH     0x040C4  /* Total Octets RX High - R/clr */
DECL|macro|E1000_TOTL
mdefine_line|#define E1000_TOTL     0x040C8  /* Total Octets TX Low - R/clr */
DECL|macro|E1000_TOTH
mdefine_line|#define E1000_TOTH     0x040CC  /* Total Octets TX High - R/clr */
DECL|macro|E1000_TPR
mdefine_line|#define E1000_TPR      0x040D0  /* Total Packets RX - R/clr */
DECL|macro|E1000_TPT
mdefine_line|#define E1000_TPT      0x040D4  /* Total Packets TX - R/clr */
DECL|macro|E1000_PTC64
mdefine_line|#define E1000_PTC64    0x040D8  /* Packets TX (64 bytes) - R/clr */
DECL|macro|E1000_PTC127
mdefine_line|#define E1000_PTC127   0x040DC  /* Packets TX (65-127 bytes) - R/clr */
DECL|macro|E1000_PTC255
mdefine_line|#define E1000_PTC255   0x040E0  /* Packets TX (128-255 bytes) - R/clr */
DECL|macro|E1000_PTC511
mdefine_line|#define E1000_PTC511   0x040E4  /* Packets TX (256-511 bytes) - R/clr */
DECL|macro|E1000_PTC1023
mdefine_line|#define E1000_PTC1023  0x040E8  /* Packets TX (512-1023 bytes) - R/clr */
DECL|macro|E1000_PTC1522
mdefine_line|#define E1000_PTC1522  0x040EC  /* Packets TX (1024-1522 Bytes) - R/clr */
DECL|macro|E1000_MPTC
mdefine_line|#define E1000_MPTC     0x040F0  /* Multicast Packets TX Count - R/clr */
DECL|macro|E1000_BPTC
mdefine_line|#define E1000_BPTC     0x040F4  /* Broadcast Packets TX Count - R/clr */
DECL|macro|E1000_TSCTC
mdefine_line|#define E1000_TSCTC    0x040F8  /* TCP Segmentation Context TX - R/clr */
DECL|macro|E1000_TSCTFC
mdefine_line|#define E1000_TSCTFC   0x040FC  /* TCP Segmentation Context TX Fail - R/clr */
DECL|macro|E1000_RXCSUM
mdefine_line|#define E1000_RXCSUM   0x05000  /* RX Checksum Control - RW */
DECL|macro|E1000_MTA
mdefine_line|#define E1000_MTA      0x05200  /* Multicast Table Array - RW Array */
DECL|macro|E1000_RA
mdefine_line|#define E1000_RA       0x05400  /* Receive Address - RW Array */
DECL|macro|E1000_VFTA
mdefine_line|#define E1000_VFTA     0x05600  /* VLAN Filter Table Array - RW Array */
DECL|macro|E1000_WUC
mdefine_line|#define E1000_WUC      0x05800  /* Wakeup Control - RW */
DECL|macro|E1000_WUFC
mdefine_line|#define E1000_WUFC     0x05808  /* Wakeup Filter Control - RW */
DECL|macro|E1000_WUS
mdefine_line|#define E1000_WUS      0x05810  /* Wakeup Status - RO */
DECL|macro|E1000_MANC
mdefine_line|#define E1000_MANC     0x05820  /* Management Control - RW */
DECL|macro|E1000_IPAV
mdefine_line|#define E1000_IPAV     0x05838  /* IP Address Valid - RW */
DECL|macro|E1000_IP4AT
mdefine_line|#define E1000_IP4AT    0x05840  /* IPv4 Address Table - RW Array */
DECL|macro|E1000_IP6AT
mdefine_line|#define E1000_IP6AT    0x05880  /* IPv6 Address Table - RW Array */
DECL|macro|E1000_WUPL
mdefine_line|#define E1000_WUPL     0x05900  /* Wakeup Packet Length - RW */
DECL|macro|E1000_WUPM
mdefine_line|#define E1000_WUPM     0x05A00  /* Wakeup Packet Memory - RO A */
DECL|macro|E1000_FFLT
mdefine_line|#define E1000_FFLT     0x05F00  /* Flexible Filter Length Table - RW Array */
DECL|macro|E1000_FFMT
mdefine_line|#define E1000_FFMT     0x09000  /* Flexible Filter Mask Table - RW Array */
DECL|macro|E1000_FFVT
mdefine_line|#define E1000_FFVT     0x09800  /* Flexible Filter Value Table - RW Array */
multiline_comment|/* Register Set (82542)&n; *&n; * Some of the 82542 registers are located at different offsets than they are&n; * in more current versions of the 8254x. Despite the difference in location,&n; * the registers function in the same manner.&n; */
DECL|macro|E1000_82542_CTRL
mdefine_line|#define E1000_82542_CTRL     E1000_CTRL
DECL|macro|E1000_82542_STATUS
mdefine_line|#define E1000_82542_STATUS   E1000_STATUS
DECL|macro|E1000_82542_EECD
mdefine_line|#define E1000_82542_EECD     E1000_EECD
DECL|macro|E1000_82542_EERD
mdefine_line|#define E1000_82542_EERD     E1000_EERD
DECL|macro|E1000_82542_CTRL_EXT
mdefine_line|#define E1000_82542_CTRL_EXT E1000_CTRL_EXT
DECL|macro|E1000_82542_MDIC
mdefine_line|#define E1000_82542_MDIC     E1000_MDIC
DECL|macro|E1000_82542_FCAL
mdefine_line|#define E1000_82542_FCAL     E1000_FCAL
DECL|macro|E1000_82542_FCAH
mdefine_line|#define E1000_82542_FCAH     E1000_FCAH
DECL|macro|E1000_82542_FCT
mdefine_line|#define E1000_82542_FCT      E1000_FCT
DECL|macro|E1000_82542_VET
mdefine_line|#define E1000_82542_VET      E1000_VET
DECL|macro|E1000_82542_RA
mdefine_line|#define E1000_82542_RA       0x00040
DECL|macro|E1000_82542_ICR
mdefine_line|#define E1000_82542_ICR      E1000_ICR
DECL|macro|E1000_82542_ITR
mdefine_line|#define E1000_82542_ITR      E1000_ITR
DECL|macro|E1000_82542_ICS
mdefine_line|#define E1000_82542_ICS      E1000_ICS
DECL|macro|E1000_82542_IMS
mdefine_line|#define E1000_82542_IMS      E1000_IMS
DECL|macro|E1000_82542_IMC
mdefine_line|#define E1000_82542_IMC      E1000_IMC
DECL|macro|E1000_82542_RCTL
mdefine_line|#define E1000_82542_RCTL     E1000_RCTL
DECL|macro|E1000_82542_RDTR
mdefine_line|#define E1000_82542_RDTR     0x00108
DECL|macro|E1000_82542_RDBAL
mdefine_line|#define E1000_82542_RDBAL    0x00110
DECL|macro|E1000_82542_RDBAH
mdefine_line|#define E1000_82542_RDBAH    0x00114
DECL|macro|E1000_82542_RDLEN
mdefine_line|#define E1000_82542_RDLEN    0x00118
DECL|macro|E1000_82542_RDH
mdefine_line|#define E1000_82542_RDH      0x00120
DECL|macro|E1000_82542_RDT
mdefine_line|#define E1000_82542_RDT      0x00128
DECL|macro|E1000_82542_FCRTH
mdefine_line|#define E1000_82542_FCRTH    0x00160
DECL|macro|E1000_82542_FCRTL
mdefine_line|#define E1000_82542_FCRTL    0x00168
DECL|macro|E1000_82542_FCTTV
mdefine_line|#define E1000_82542_FCTTV    E1000_FCTTV
DECL|macro|E1000_82542_TXCW
mdefine_line|#define E1000_82542_TXCW     E1000_TXCW
DECL|macro|E1000_82542_RXCW
mdefine_line|#define E1000_82542_RXCW     E1000_RXCW
DECL|macro|E1000_82542_MTA
mdefine_line|#define E1000_82542_MTA      0x00200
DECL|macro|E1000_82542_TCTL
mdefine_line|#define E1000_82542_TCTL     E1000_TCTL
DECL|macro|E1000_82542_TIPG
mdefine_line|#define E1000_82542_TIPG     E1000_TIPG
DECL|macro|E1000_82542_TDBAL
mdefine_line|#define E1000_82542_TDBAL    0x00420
DECL|macro|E1000_82542_TDBAH
mdefine_line|#define E1000_82542_TDBAH    0x00424
DECL|macro|E1000_82542_TDLEN
mdefine_line|#define E1000_82542_TDLEN    0x00428
DECL|macro|E1000_82542_TDH
mdefine_line|#define E1000_82542_TDH      0x00430
DECL|macro|E1000_82542_TDT
mdefine_line|#define E1000_82542_TDT      0x00438
DECL|macro|E1000_82542_TIDV
mdefine_line|#define E1000_82542_TIDV     0x00440
DECL|macro|E1000_82542_TBT
mdefine_line|#define E1000_82542_TBT      E1000_TBT
DECL|macro|E1000_82542_AIT
mdefine_line|#define E1000_82542_AIT      E1000_AIT
DECL|macro|E1000_82542_VFTA
mdefine_line|#define E1000_82542_VFTA     0x00600
DECL|macro|E1000_82542_LEDCTL
mdefine_line|#define E1000_82542_LEDCTL   E1000_LEDCTL
DECL|macro|E1000_82542_PBA
mdefine_line|#define E1000_82542_PBA      E1000_PBA
DECL|macro|E1000_82542_RXDCTL
mdefine_line|#define E1000_82542_RXDCTL   E1000_RXDCTL
DECL|macro|E1000_82542_RADV
mdefine_line|#define E1000_82542_RADV     E1000_RADV
DECL|macro|E1000_82542_RSRPD
mdefine_line|#define E1000_82542_RSRPD    E1000_RSRPD
DECL|macro|E1000_82542_TXDMAC
mdefine_line|#define E1000_82542_TXDMAC   E1000_TXDMAC
DECL|macro|E1000_82542_TXDCTL
mdefine_line|#define E1000_82542_TXDCTL   E1000_TXDCTL
DECL|macro|E1000_82542_TADV
mdefine_line|#define E1000_82542_TADV     E1000_TADV
DECL|macro|E1000_82542_TSPMT
mdefine_line|#define E1000_82542_TSPMT    E1000_TSPMT
DECL|macro|E1000_82542_CRCERRS
mdefine_line|#define E1000_82542_CRCERRS  E1000_CRCERRS
DECL|macro|E1000_82542_ALGNERRC
mdefine_line|#define E1000_82542_ALGNERRC E1000_ALGNERRC
DECL|macro|E1000_82542_SYMERRS
mdefine_line|#define E1000_82542_SYMERRS  E1000_SYMERRS
DECL|macro|E1000_82542_RXERRC
mdefine_line|#define E1000_82542_RXERRC   E1000_RXERRC
DECL|macro|E1000_82542_MPC
mdefine_line|#define E1000_82542_MPC      E1000_MPC
DECL|macro|E1000_82542_SCC
mdefine_line|#define E1000_82542_SCC      E1000_SCC
DECL|macro|E1000_82542_ECOL
mdefine_line|#define E1000_82542_ECOL     E1000_ECOL
DECL|macro|E1000_82542_MCC
mdefine_line|#define E1000_82542_MCC      E1000_MCC
DECL|macro|E1000_82542_LATECOL
mdefine_line|#define E1000_82542_LATECOL  E1000_LATECOL
DECL|macro|E1000_82542_COLC
mdefine_line|#define E1000_82542_COLC     E1000_COLC
DECL|macro|E1000_82542_DC
mdefine_line|#define E1000_82542_DC       E1000_DC
DECL|macro|E1000_82542_TNCRS
mdefine_line|#define E1000_82542_TNCRS    E1000_TNCRS
DECL|macro|E1000_82542_SEC
mdefine_line|#define E1000_82542_SEC      E1000_SEC
DECL|macro|E1000_82542_CEXTERR
mdefine_line|#define E1000_82542_CEXTERR  E1000_CEXTERR
DECL|macro|E1000_82542_RLEC
mdefine_line|#define E1000_82542_RLEC     E1000_RLEC
DECL|macro|E1000_82542_XONRXC
mdefine_line|#define E1000_82542_XONRXC   E1000_XONRXC
DECL|macro|E1000_82542_XONTXC
mdefine_line|#define E1000_82542_XONTXC   E1000_XONTXC
DECL|macro|E1000_82542_XOFFRXC
mdefine_line|#define E1000_82542_XOFFRXC  E1000_XOFFRXC
DECL|macro|E1000_82542_XOFFTXC
mdefine_line|#define E1000_82542_XOFFTXC  E1000_XOFFTXC
DECL|macro|E1000_82542_FCRUC
mdefine_line|#define E1000_82542_FCRUC    E1000_FCRUC
DECL|macro|E1000_82542_PRC64
mdefine_line|#define E1000_82542_PRC64    E1000_PRC64
DECL|macro|E1000_82542_PRC127
mdefine_line|#define E1000_82542_PRC127   E1000_PRC127
DECL|macro|E1000_82542_PRC255
mdefine_line|#define E1000_82542_PRC255   E1000_PRC255
DECL|macro|E1000_82542_PRC511
mdefine_line|#define E1000_82542_PRC511   E1000_PRC511
DECL|macro|E1000_82542_PRC1023
mdefine_line|#define E1000_82542_PRC1023  E1000_PRC1023
DECL|macro|E1000_82542_PRC1522
mdefine_line|#define E1000_82542_PRC1522  E1000_PRC1522
DECL|macro|E1000_82542_GPRC
mdefine_line|#define E1000_82542_GPRC     E1000_GPRC
DECL|macro|E1000_82542_BPRC
mdefine_line|#define E1000_82542_BPRC     E1000_BPRC
DECL|macro|E1000_82542_MPRC
mdefine_line|#define E1000_82542_MPRC     E1000_MPRC
DECL|macro|E1000_82542_GPTC
mdefine_line|#define E1000_82542_GPTC     E1000_GPTC
DECL|macro|E1000_82542_GORCL
mdefine_line|#define E1000_82542_GORCL    E1000_GORCL
DECL|macro|E1000_82542_GORCH
mdefine_line|#define E1000_82542_GORCH    E1000_GORCH
DECL|macro|E1000_82542_GOTCL
mdefine_line|#define E1000_82542_GOTCL    E1000_GOTCL
DECL|macro|E1000_82542_GOTCH
mdefine_line|#define E1000_82542_GOTCH    E1000_GOTCH
DECL|macro|E1000_82542_RNBC
mdefine_line|#define E1000_82542_RNBC     E1000_RNBC
DECL|macro|E1000_82542_RUC
mdefine_line|#define E1000_82542_RUC      E1000_RUC
DECL|macro|E1000_82542_RFC
mdefine_line|#define E1000_82542_RFC      E1000_RFC
DECL|macro|E1000_82542_ROC
mdefine_line|#define E1000_82542_ROC      E1000_ROC
DECL|macro|E1000_82542_RJC
mdefine_line|#define E1000_82542_RJC      E1000_RJC
DECL|macro|E1000_82542_MGTPRC
mdefine_line|#define E1000_82542_MGTPRC   E1000_MGTPRC
DECL|macro|E1000_82542_MGTPDC
mdefine_line|#define E1000_82542_MGTPDC   E1000_MGTPDC
DECL|macro|E1000_82542_MGTPTC
mdefine_line|#define E1000_82542_MGTPTC   E1000_MGTPTC
DECL|macro|E1000_82542_TORL
mdefine_line|#define E1000_82542_TORL     E1000_TORL
DECL|macro|E1000_82542_TORH
mdefine_line|#define E1000_82542_TORH     E1000_TORH
DECL|macro|E1000_82542_TOTL
mdefine_line|#define E1000_82542_TOTL     E1000_TOTL
DECL|macro|E1000_82542_TOTH
mdefine_line|#define E1000_82542_TOTH     E1000_TOTH
DECL|macro|E1000_82542_TPR
mdefine_line|#define E1000_82542_TPR      E1000_TPR
DECL|macro|E1000_82542_TPT
mdefine_line|#define E1000_82542_TPT      E1000_TPT
DECL|macro|E1000_82542_PTC64
mdefine_line|#define E1000_82542_PTC64    E1000_PTC64
DECL|macro|E1000_82542_PTC127
mdefine_line|#define E1000_82542_PTC127   E1000_PTC127
DECL|macro|E1000_82542_PTC255
mdefine_line|#define E1000_82542_PTC255   E1000_PTC255
DECL|macro|E1000_82542_PTC511
mdefine_line|#define E1000_82542_PTC511   E1000_PTC511
DECL|macro|E1000_82542_PTC1023
mdefine_line|#define E1000_82542_PTC1023  E1000_PTC1023
DECL|macro|E1000_82542_PTC1522
mdefine_line|#define E1000_82542_PTC1522  E1000_PTC1522
DECL|macro|E1000_82542_MPTC
mdefine_line|#define E1000_82542_MPTC     E1000_MPTC
DECL|macro|E1000_82542_BPTC
mdefine_line|#define E1000_82542_BPTC     E1000_BPTC
DECL|macro|E1000_82542_TSCTC
mdefine_line|#define E1000_82542_TSCTC    E1000_TSCTC
DECL|macro|E1000_82542_TSCTFC
mdefine_line|#define E1000_82542_TSCTFC   E1000_TSCTFC
DECL|macro|E1000_82542_RXCSUM
mdefine_line|#define E1000_82542_RXCSUM   E1000_RXCSUM
DECL|macro|E1000_82542_WUC
mdefine_line|#define E1000_82542_WUC      E1000_WUC
DECL|macro|E1000_82542_WUFC
mdefine_line|#define E1000_82542_WUFC     E1000_WUFC
DECL|macro|E1000_82542_WUS
mdefine_line|#define E1000_82542_WUS      E1000_WUS
DECL|macro|E1000_82542_MANC
mdefine_line|#define E1000_82542_MANC     E1000_MANC
DECL|macro|E1000_82542_IPAV
mdefine_line|#define E1000_82542_IPAV     E1000_IPAV
DECL|macro|E1000_82542_IP4AT
mdefine_line|#define E1000_82542_IP4AT    E1000_IP4AT
DECL|macro|E1000_82542_IP6AT
mdefine_line|#define E1000_82542_IP6AT    E1000_IP6AT
DECL|macro|E1000_82542_WUPL
mdefine_line|#define E1000_82542_WUPL     E1000_WUPL
DECL|macro|E1000_82542_WUPM
mdefine_line|#define E1000_82542_WUPM     E1000_WUPM
DECL|macro|E1000_82542_FFLT
mdefine_line|#define E1000_82542_FFLT     E1000_FFLT
DECL|macro|E1000_82542_FFMT
mdefine_line|#define E1000_82542_FFMT     E1000_FFMT
DECL|macro|E1000_82542_FFVT
mdefine_line|#define E1000_82542_FFVT     E1000_FFVT
multiline_comment|/* Statistics counters collected by the MAC */
DECL|struct|e1000_hw_stats
r_struct
id|e1000_hw_stats
(brace
DECL|member|crcerrs
r_uint64
id|crcerrs
suffix:semicolon
DECL|member|algnerrc
r_uint64
id|algnerrc
suffix:semicolon
DECL|member|symerrs
r_uint64
id|symerrs
suffix:semicolon
DECL|member|rxerrc
r_uint64
id|rxerrc
suffix:semicolon
DECL|member|mpc
r_uint64
id|mpc
suffix:semicolon
DECL|member|scc
r_uint64
id|scc
suffix:semicolon
DECL|member|ecol
r_uint64
id|ecol
suffix:semicolon
DECL|member|mcc
r_uint64
id|mcc
suffix:semicolon
DECL|member|latecol
r_uint64
id|latecol
suffix:semicolon
DECL|member|colc
r_uint64
id|colc
suffix:semicolon
DECL|member|dc
r_uint64
id|dc
suffix:semicolon
DECL|member|tncrs
r_uint64
id|tncrs
suffix:semicolon
DECL|member|sec
r_uint64
id|sec
suffix:semicolon
DECL|member|cexterr
r_uint64
id|cexterr
suffix:semicolon
DECL|member|rlec
r_uint64
id|rlec
suffix:semicolon
DECL|member|xonrxc
r_uint64
id|xonrxc
suffix:semicolon
DECL|member|xontxc
r_uint64
id|xontxc
suffix:semicolon
DECL|member|xoffrxc
r_uint64
id|xoffrxc
suffix:semicolon
DECL|member|xofftxc
r_uint64
id|xofftxc
suffix:semicolon
DECL|member|fcruc
r_uint64
id|fcruc
suffix:semicolon
DECL|member|prc64
r_uint64
id|prc64
suffix:semicolon
DECL|member|prc127
r_uint64
id|prc127
suffix:semicolon
DECL|member|prc255
r_uint64
id|prc255
suffix:semicolon
DECL|member|prc511
r_uint64
id|prc511
suffix:semicolon
DECL|member|prc1023
r_uint64
id|prc1023
suffix:semicolon
DECL|member|prc1522
r_uint64
id|prc1522
suffix:semicolon
DECL|member|gprc
r_uint64
id|gprc
suffix:semicolon
DECL|member|bprc
r_uint64
id|bprc
suffix:semicolon
DECL|member|mprc
r_uint64
id|mprc
suffix:semicolon
DECL|member|gptc
r_uint64
id|gptc
suffix:semicolon
DECL|member|gorcl
r_uint64
id|gorcl
suffix:semicolon
DECL|member|gorch
r_uint64
id|gorch
suffix:semicolon
DECL|member|gotcl
r_uint64
id|gotcl
suffix:semicolon
DECL|member|gotch
r_uint64
id|gotch
suffix:semicolon
DECL|member|rnbc
r_uint64
id|rnbc
suffix:semicolon
DECL|member|ruc
r_uint64
id|ruc
suffix:semicolon
DECL|member|rfc
r_uint64
id|rfc
suffix:semicolon
DECL|member|roc
r_uint64
id|roc
suffix:semicolon
DECL|member|rjc
r_uint64
id|rjc
suffix:semicolon
DECL|member|mgprc
r_uint64
id|mgprc
suffix:semicolon
DECL|member|mgpdc
r_uint64
id|mgpdc
suffix:semicolon
DECL|member|mgptc
r_uint64
id|mgptc
suffix:semicolon
DECL|member|torl
r_uint64
id|torl
suffix:semicolon
DECL|member|torh
r_uint64
id|torh
suffix:semicolon
DECL|member|totl
r_uint64
id|totl
suffix:semicolon
DECL|member|toth
r_uint64
id|toth
suffix:semicolon
DECL|member|tpr
r_uint64
id|tpr
suffix:semicolon
DECL|member|tpt
r_uint64
id|tpt
suffix:semicolon
DECL|member|ptc64
r_uint64
id|ptc64
suffix:semicolon
DECL|member|ptc127
r_uint64
id|ptc127
suffix:semicolon
DECL|member|ptc255
r_uint64
id|ptc255
suffix:semicolon
DECL|member|ptc511
r_uint64
id|ptc511
suffix:semicolon
DECL|member|ptc1023
r_uint64
id|ptc1023
suffix:semicolon
DECL|member|ptc1522
r_uint64
id|ptc1522
suffix:semicolon
DECL|member|mptc
r_uint64
id|mptc
suffix:semicolon
DECL|member|bptc
r_uint64
id|bptc
suffix:semicolon
DECL|member|tsctc
r_uint64
id|tsctc
suffix:semicolon
DECL|member|tsctfc
r_uint64
id|tsctfc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Structure containing variables used by the shared code (e1000_hw.c) */
DECL|struct|e1000_hw
r_struct
id|e1000_hw
(brace
DECL|member|hw_addr
r_uint8
op_star
id|hw_addr
suffix:semicolon
DECL|member|mac_type
id|e1000_mac_type
id|mac_type
suffix:semicolon
DECL|member|media_type
id|e1000_media_type
id|media_type
suffix:semicolon
DECL|member|back
r_void
op_star
id|back
suffix:semicolon
DECL|member|fc
id|e1000_fc_type
id|fc
suffix:semicolon
DECL|member|bus_speed
id|e1000_bus_speed
id|bus_speed
suffix:semicolon
DECL|member|bus_width
id|e1000_bus_width
id|bus_width
suffix:semicolon
DECL|member|bus_type
id|e1000_bus_type
id|bus_type
suffix:semicolon
DECL|member|phy_id
r_uint32
id|phy_id
suffix:semicolon
DECL|member|phy_addr
r_uint32
id|phy_addr
suffix:semicolon
DECL|member|original_fc
r_uint32
id|original_fc
suffix:semicolon
DECL|member|txcw
r_uint32
id|txcw
suffix:semicolon
DECL|member|autoneg_failed
r_uint32
id|autoneg_failed
suffix:semicolon
DECL|member|max_frame_size
r_uint32
id|max_frame_size
suffix:semicolon
DECL|member|min_frame_size
r_uint32
id|min_frame_size
suffix:semicolon
DECL|member|mc_filter_type
r_uint32
id|mc_filter_type
suffix:semicolon
DECL|member|num_mc_addrs
r_uint32
id|num_mc_addrs
suffix:semicolon
DECL|member|collision_delta
r_uint32
id|collision_delta
suffix:semicolon
DECL|member|tx_packet_delta
r_uint32
id|tx_packet_delta
suffix:semicolon
DECL|member|ledctl_default
r_uint32
id|ledctl_default
suffix:semicolon
DECL|member|ledctl_mode1
r_uint32
id|ledctl_mode1
suffix:semicolon
DECL|member|ledctl_mode2
r_uint32
id|ledctl_mode2
suffix:semicolon
DECL|member|autoneg_advertised
r_uint16
id|autoneg_advertised
suffix:semicolon
DECL|member|pci_cmd_word
r_uint16
id|pci_cmd_word
suffix:semicolon
DECL|member|fc_high_water
r_uint16
id|fc_high_water
suffix:semicolon
DECL|member|fc_low_water
r_uint16
id|fc_low_water
suffix:semicolon
DECL|member|fc_pause_time
r_uint16
id|fc_pause_time
suffix:semicolon
DECL|member|current_ifs_val
r_uint16
id|current_ifs_val
suffix:semicolon
DECL|member|ifs_min_val
r_uint16
id|ifs_min_val
suffix:semicolon
DECL|member|ifs_max_val
r_uint16
id|ifs_max_val
suffix:semicolon
DECL|member|ifs_step_size
r_uint16
id|ifs_step_size
suffix:semicolon
DECL|member|ifs_ratio
r_uint16
id|ifs_ratio
suffix:semicolon
DECL|member|device_id
r_uint16
id|device_id
suffix:semicolon
DECL|member|vendor_id
r_uint16
id|vendor_id
suffix:semicolon
DECL|member|subsystem_id
r_uint16
id|subsystem_id
suffix:semicolon
DECL|member|subsystem_vendor_id
r_uint16
id|subsystem_vendor_id
suffix:semicolon
DECL|member|revision_id
r_uint8
id|revision_id
suffix:semicolon
DECL|member|autoneg
r_uint8
id|autoneg
suffix:semicolon
DECL|member|mdix
r_uint8
id|mdix
suffix:semicolon
DECL|member|forced_speed_duplex
r_uint8
id|forced_speed_duplex
suffix:semicolon
DECL|member|wait_autoneg_complete
r_uint8
id|wait_autoneg_complete
suffix:semicolon
DECL|member|dma_fairness
r_uint8
id|dma_fairness
suffix:semicolon
DECL|member|mac_addr
r_uint8
id|mac_addr
(braket
id|NODE_ADDRESS_SIZE
)braket
suffix:semicolon
DECL|member|perm_mac_addr
r_uint8
id|perm_mac_addr
(braket
id|NODE_ADDRESS_SIZE
)braket
suffix:semicolon
DECL|member|disable_polarity_correction
id|boolean_t
id|disable_polarity_correction
suffix:semicolon
DECL|member|get_link_status
id|boolean_t
id|get_link_status
suffix:semicolon
DECL|member|tbi_compatibility_en
id|boolean_t
id|tbi_compatibility_en
suffix:semicolon
DECL|member|tbi_compatibility_on
id|boolean_t
id|tbi_compatibility_on
suffix:semicolon
DECL|member|fc_send_xon
id|boolean_t
id|fc_send_xon
suffix:semicolon
DECL|member|report_tx_early
id|boolean_t
id|report_tx_early
suffix:semicolon
DECL|member|adaptive_ifs
id|boolean_t
id|adaptive_ifs
suffix:semicolon
DECL|member|ifs_params_forced
id|boolean_t
id|ifs_params_forced
suffix:semicolon
DECL|member|in_ifs_mode
id|boolean_t
id|in_ifs_mode
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|E1000_EEPROM_SWDPIN0
mdefine_line|#define E1000_EEPROM_SWDPIN0   0x0001   /* SWDPIN 0 EEPROM Value */
DECL|macro|E1000_EEPROM_LED_LOGIC
mdefine_line|#define E1000_EEPROM_LED_LOGIC 0x0020   /* Led Logic Word */
multiline_comment|/* Register Bit Masks */
multiline_comment|/* Device Control */
DECL|macro|E1000_CTRL_FD
mdefine_line|#define E1000_CTRL_FD       0x00000001  /* Full duplex.0=half; 1=full */
DECL|macro|E1000_CTRL_BEM
mdefine_line|#define E1000_CTRL_BEM      0x00000002  /* Endian Mode.0=little,1=big */
DECL|macro|E1000_CTRL_PRIOR
mdefine_line|#define E1000_CTRL_PRIOR    0x00000004  /* Priority on PCI. 0=rx,1=fair */
DECL|macro|E1000_CTRL_LRST
mdefine_line|#define E1000_CTRL_LRST     0x00000008  /* Link reset. 0=normal,1=reset */
DECL|macro|E1000_CTRL_TME
mdefine_line|#define E1000_CTRL_TME      0x00000010  /* Test mode. 0=normal,1=test */
DECL|macro|E1000_CTRL_SLE
mdefine_line|#define E1000_CTRL_SLE      0x00000020  /* Serial Link on 0=dis,1=en */
DECL|macro|E1000_CTRL_ASDE
mdefine_line|#define E1000_CTRL_ASDE     0x00000020  /* Auto-speed detect enable */
DECL|macro|E1000_CTRL_SLU
mdefine_line|#define E1000_CTRL_SLU      0x00000040  /* Set link up (Force Link) */
DECL|macro|E1000_CTRL_ILOS
mdefine_line|#define E1000_CTRL_ILOS     0x00000080  /* Invert Loss-Of Signal */
DECL|macro|E1000_CTRL_SPD_SEL
mdefine_line|#define E1000_CTRL_SPD_SEL  0x00000300  /* Speed Select Mask */
DECL|macro|E1000_CTRL_SPD_10
mdefine_line|#define E1000_CTRL_SPD_10   0x00000000  /* Force 10Mb */
DECL|macro|E1000_CTRL_SPD_100
mdefine_line|#define E1000_CTRL_SPD_100  0x00000100  /* Force 100Mb */
DECL|macro|E1000_CTRL_SPD_1000
mdefine_line|#define E1000_CTRL_SPD_1000 0x00000200  /* Force 1Gb */
DECL|macro|E1000_CTRL_BEM32
mdefine_line|#define E1000_CTRL_BEM32    0x00000400  /* Big Endian 32 mode */
DECL|macro|E1000_CTRL_FRCSPD
mdefine_line|#define E1000_CTRL_FRCSPD   0x00000800  /* Force Speed */
DECL|macro|E1000_CTRL_FRCDPX
mdefine_line|#define E1000_CTRL_FRCDPX   0x00001000  /* Force Duplex */
DECL|macro|E1000_CTRL_SWDPIN0
mdefine_line|#define E1000_CTRL_SWDPIN0  0x00040000  /* SWDPIN 0 value */
DECL|macro|E1000_CTRL_SWDPIN1
mdefine_line|#define E1000_CTRL_SWDPIN1  0x00080000  /* SWDPIN 1 value */
DECL|macro|E1000_CTRL_SWDPIN2
mdefine_line|#define E1000_CTRL_SWDPIN2  0x00100000  /* SWDPIN 2 value */
DECL|macro|E1000_CTRL_SWDPIN3
mdefine_line|#define E1000_CTRL_SWDPIN3  0x00200000  /* SWDPIN 3 value */
DECL|macro|E1000_CTRL_SWDPIO0
mdefine_line|#define E1000_CTRL_SWDPIO0  0x00400000  /* SWDPIN 0 Input or output */
DECL|macro|E1000_CTRL_SWDPIO1
mdefine_line|#define E1000_CTRL_SWDPIO1  0x00800000  /* SWDPIN 1 input or output */
DECL|macro|E1000_CTRL_SWDPIO2
mdefine_line|#define E1000_CTRL_SWDPIO2  0x01000000  /* SWDPIN 2 input or output */
DECL|macro|E1000_CTRL_SWDPIO3
mdefine_line|#define E1000_CTRL_SWDPIO3  0x02000000  /* SWDPIN 3 input or output */
DECL|macro|E1000_CTRL_RST
mdefine_line|#define E1000_CTRL_RST      0x04000000  /* Global reset */
DECL|macro|E1000_CTRL_RFCE
mdefine_line|#define E1000_CTRL_RFCE     0x08000000  /* Receive Flow Control enable */
DECL|macro|E1000_CTRL_TFCE
mdefine_line|#define E1000_CTRL_TFCE     0x10000000  /* Transmit flow control enable */
DECL|macro|E1000_CTRL_RTE
mdefine_line|#define E1000_CTRL_RTE      0x20000000  /* Routing tag enable */
DECL|macro|E1000_CTRL_VME
mdefine_line|#define E1000_CTRL_VME      0x40000000  /* IEEE VLAN mode enable */
DECL|macro|E1000_CTRL_PHY_RST
mdefine_line|#define E1000_CTRL_PHY_RST  0x80000000  /* PHY Reset */
multiline_comment|/* Device Status */
DECL|macro|E1000_STATUS_FD
mdefine_line|#define E1000_STATUS_FD         0x00000001      /* Full duplex.0=half,1=full */
DECL|macro|E1000_STATUS_LU
mdefine_line|#define E1000_STATUS_LU         0x00000002      /* Link up.0=no,1=link */
DECL|macro|E1000_STATUS_FUNC_MASK
mdefine_line|#define E1000_STATUS_FUNC_MASK  0x0000000C      /* PCI Function Mask */
DECL|macro|E1000_STATUS_FUNC_0
mdefine_line|#define E1000_STATUS_FUNC_0     0x00000000      /* Function 0 */
DECL|macro|E1000_STATUS_FUNC_1
mdefine_line|#define E1000_STATUS_FUNC_1     0x00000004      /* Function 1 */
DECL|macro|E1000_STATUS_TXOFF
mdefine_line|#define E1000_STATUS_TXOFF      0x00000010      /* transmission paused */
DECL|macro|E1000_STATUS_TBIMODE
mdefine_line|#define E1000_STATUS_TBIMODE    0x00000020      /* TBI mode */
DECL|macro|E1000_STATUS_SPEED_MASK
mdefine_line|#define E1000_STATUS_SPEED_MASK 0x000000C0
DECL|macro|E1000_STATUS_SPEED_10
mdefine_line|#define E1000_STATUS_SPEED_10   0x00000000      /* Speed 10Mb/s */
DECL|macro|E1000_STATUS_SPEED_100
mdefine_line|#define E1000_STATUS_SPEED_100  0x00000040      /* Speed 100Mb/s */
DECL|macro|E1000_STATUS_SPEED_1000
mdefine_line|#define E1000_STATUS_SPEED_1000 0x00000080      /* Speed 1000Mb/s */
DECL|macro|E1000_STATUS_ASDV
mdefine_line|#define E1000_STATUS_ASDV       0x00000300      /* Auto speed detect value */
DECL|macro|E1000_STATUS_MTXCKOK
mdefine_line|#define E1000_STATUS_MTXCKOK    0x00000400      /* MTX clock running OK */
DECL|macro|E1000_STATUS_PCI66
mdefine_line|#define E1000_STATUS_PCI66      0x00000800      /* In 66Mhz slot */
DECL|macro|E1000_STATUS_BUS64
mdefine_line|#define E1000_STATUS_BUS64      0x00001000      /* In 64 bit slot */
DECL|macro|E1000_STATUS_PCIX_MODE
mdefine_line|#define E1000_STATUS_PCIX_MODE  0x00002000      /* PCI-X mode */
DECL|macro|E1000_STATUS_PCIX_SPEED
mdefine_line|#define E1000_STATUS_PCIX_SPEED 0x0000C000      /* PCI-X bus speed */
multiline_comment|/* Constants used to intrepret the masked PCI-X bus speed. */
DECL|macro|E1000_STATUS_PCIX_SPEED_66
mdefine_line|#define E1000_STATUS_PCIX_SPEED_66  0x00000000 /* PCI-X bus speed  50-66 MHz */
DECL|macro|E1000_STATUS_PCIX_SPEED_100
mdefine_line|#define E1000_STATUS_PCIX_SPEED_100 0x00004000 /* PCI-X bus speed  66-100 MHz */
DECL|macro|E1000_STATUS_PCIX_SPEED_133
mdefine_line|#define E1000_STATUS_PCIX_SPEED_133 0x00008000 /* PCI-X bus speed 100-133 MHz */
multiline_comment|/* EEPROM/Flash Control */
DECL|macro|E1000_EECD_SK
mdefine_line|#define E1000_EECD_SK        0x00000001 /* EEPROM Clock */
DECL|macro|E1000_EECD_CS
mdefine_line|#define E1000_EECD_CS        0x00000002 /* EEPROM Chip Select */
DECL|macro|E1000_EECD_DI
mdefine_line|#define E1000_EECD_DI        0x00000004 /* EEPROM Data In */
DECL|macro|E1000_EECD_DO
mdefine_line|#define E1000_EECD_DO        0x00000008 /* EEPROM Data Out */
DECL|macro|E1000_EECD_FWE_MASK
mdefine_line|#define E1000_EECD_FWE_MASK  0x00000030 
DECL|macro|E1000_EECD_FWE_DIS
mdefine_line|#define E1000_EECD_FWE_DIS   0x00000010 /* Disable FLASH writes */
DECL|macro|E1000_EECD_FWE_EN
mdefine_line|#define E1000_EECD_FWE_EN    0x00000020 /* Enable FLASH writes */
DECL|macro|E1000_EECD_FWE_SHIFT
mdefine_line|#define E1000_EECD_FWE_SHIFT 4
DECL|macro|E1000_EECD_SIZE
mdefine_line|#define E1000_EECD_SIZE      0x00000200 /* EEPROM Size (0=64 word 1=256 word) */
DECL|macro|E1000_EECD_REQ
mdefine_line|#define E1000_EECD_REQ       0x00000040 /* EEPROM Access Request */
DECL|macro|E1000_EECD_GNT
mdefine_line|#define E1000_EECD_GNT       0x00000080 /* EEPROM Access Grant */
DECL|macro|E1000_EECD_PRES
mdefine_line|#define E1000_EECD_PRES      0x00000100 /* EEPROM Present */
multiline_comment|/* EEPROM Read */
DECL|macro|E1000_EERD_START
mdefine_line|#define E1000_EERD_START      0x00000001 /* Start Read */
DECL|macro|E1000_EERD_DONE
mdefine_line|#define E1000_EERD_DONE       0x00000010 /* Read Done */
DECL|macro|E1000_EERD_ADDR_SHIFT
mdefine_line|#define E1000_EERD_ADDR_SHIFT 8
DECL|macro|E1000_EERD_ADDR_MASK
mdefine_line|#define E1000_EERD_ADDR_MASK  0x0000FF00 /* Read Address */
DECL|macro|E1000_EERD_DATA_SHIFT
mdefine_line|#define E1000_EERD_DATA_SHIFT 16
DECL|macro|E1000_EERD_DATA_MASK
mdefine_line|#define E1000_EERD_DATA_MASK  0xFFFF0000 /* Read Data */
multiline_comment|/* Extended Device Control */
DECL|macro|E1000_CTRL_EXT_GPI0_EN
mdefine_line|#define E1000_CTRL_EXT_GPI0_EN   0x00000001 /* Maps SDP4 to GPI0 */ 
DECL|macro|E1000_CTRL_EXT_GPI1_EN
mdefine_line|#define E1000_CTRL_EXT_GPI1_EN   0x00000002 /* Maps SDP5 to GPI1 */
DECL|macro|E1000_CTRL_EXT_PHYINT_EN
mdefine_line|#define E1000_CTRL_EXT_PHYINT_EN E1000_CTRL_EXT_GPI1_EN
DECL|macro|E1000_CTRL_EXT_GPI2_EN
mdefine_line|#define E1000_CTRL_EXT_GPI2_EN   0x00000004 /* Maps SDP6 to GPI2 */
DECL|macro|E1000_CTRL_EXT_GPI3_EN
mdefine_line|#define E1000_CTRL_EXT_GPI3_EN   0x00000008 /* Maps SDP7 to GPI3 */
DECL|macro|E1000_CTRL_EXT_SDP4_DATA
mdefine_line|#define E1000_CTRL_EXT_SDP4_DATA 0x00000010 /* Value of SW Defineable Pin 4 */
DECL|macro|E1000_CTRL_EXT_SDP5_DATA
mdefine_line|#define E1000_CTRL_EXT_SDP5_DATA 0x00000020 /* Value of SW Defineable Pin 5 */
DECL|macro|E1000_CTRL_EXT_PHY_INT
mdefine_line|#define E1000_CTRL_EXT_PHY_INT   E1000_CTRL_EXT_SDP5_DATA
DECL|macro|E1000_CTRL_EXT_SDP6_DATA
mdefine_line|#define E1000_CTRL_EXT_SDP6_DATA 0x00000040 /* Value of SW Defineable Pin 6 */
DECL|macro|E1000_CTRL_EXT_SDP7_DATA
mdefine_line|#define E1000_CTRL_EXT_SDP7_DATA 0x00000080 /* Value of SW Defineable Pin 7 */
DECL|macro|E1000_CTRL_EXT_SDP4_DIR
mdefine_line|#define E1000_CTRL_EXT_SDP4_DIR  0x00000100 /* Direction of SDP4 0=in 1=out */
DECL|macro|E1000_CTRL_EXT_SDP5_DIR
mdefine_line|#define E1000_CTRL_EXT_SDP5_DIR  0x00000200 /* Direction of SDP5 0=in 1=out */
DECL|macro|E1000_CTRL_EXT_SDP6_DIR
mdefine_line|#define E1000_CTRL_EXT_SDP6_DIR  0x00000400 /* Direction of SDP6 0=in 1=out */
DECL|macro|E1000_CTRL_EXT_SDP7_DIR
mdefine_line|#define E1000_CTRL_EXT_SDP7_DIR  0x00000800 /* Direction of SDP7 0=in 1=out */
DECL|macro|E1000_CTRL_EXT_ASDCHK
mdefine_line|#define E1000_CTRL_EXT_ASDCHK    0x00001000 /* Initiate an ASD sequence */
DECL|macro|E1000_CTRL_EXT_EE_RST
mdefine_line|#define E1000_CTRL_EXT_EE_RST    0x00002000 /* Reinitialize from EEPROM */
DECL|macro|E1000_CTRL_EXT_IPS
mdefine_line|#define E1000_CTRL_EXT_IPS       0x00004000 /* Invert Power State */
DECL|macro|E1000_CTRL_EXT_SPD_BYPS
mdefine_line|#define E1000_CTRL_EXT_SPD_BYPS  0x00008000 /* Speed Select Bypass */
DECL|macro|E1000_CTRL_EXT_LINK_MODE_MASK
mdefine_line|#define E1000_CTRL_EXT_LINK_MODE_MASK 0x00C00000
DECL|macro|E1000_CTRL_EXT_LINK_MODE_GMII
mdefine_line|#define E1000_CTRL_EXT_LINK_MODE_GMII 0x00000000
DECL|macro|E1000_CTRL_EXT_LINK_MODE_TBI
mdefine_line|#define E1000_CTRL_EXT_LINK_MODE_TBI  0x00C00000
DECL|macro|E1000_CTRL_EXT_WR_WMARK_MASK
mdefine_line|#define E1000_CTRL_EXT_WR_WMARK_MASK  0x03000000
DECL|macro|E1000_CTRL_EXT_WR_WMARK_256
mdefine_line|#define E1000_CTRL_EXT_WR_WMARK_256   0x00000000
DECL|macro|E1000_CTRL_EXT_WR_WMARK_320
mdefine_line|#define E1000_CTRL_EXT_WR_WMARK_320   0x01000000
DECL|macro|E1000_CTRL_EXT_WR_WMARK_384
mdefine_line|#define E1000_CTRL_EXT_WR_WMARK_384   0x02000000
DECL|macro|E1000_CTRL_EXT_WR_WMARK_448
mdefine_line|#define E1000_CTRL_EXT_WR_WMARK_448   0x03000000
multiline_comment|/* MDI Control */
DECL|macro|E1000_MDIC_DATA_MASK
mdefine_line|#define E1000_MDIC_DATA_MASK 0x0000FFFF
DECL|macro|E1000_MDIC_REG_MASK
mdefine_line|#define E1000_MDIC_REG_MASK  0x001F0000
DECL|macro|E1000_MDIC_REG_SHIFT
mdefine_line|#define E1000_MDIC_REG_SHIFT 16
DECL|macro|E1000_MDIC_PHY_MASK
mdefine_line|#define E1000_MDIC_PHY_MASK  0x03E00000
DECL|macro|E1000_MDIC_PHY_SHIFT
mdefine_line|#define E1000_MDIC_PHY_SHIFT 21
DECL|macro|E1000_MDIC_OP_WRITE
mdefine_line|#define E1000_MDIC_OP_WRITE  0x04000000
DECL|macro|E1000_MDIC_OP_READ
mdefine_line|#define E1000_MDIC_OP_READ   0x08000000
DECL|macro|E1000_MDIC_READY
mdefine_line|#define E1000_MDIC_READY     0x10000000
DECL|macro|E1000_MDIC_INT_EN
mdefine_line|#define E1000_MDIC_INT_EN    0x20000000
DECL|macro|E1000_MDIC_ERROR
mdefine_line|#define E1000_MDIC_ERROR     0x40000000
multiline_comment|/* LED Control */
DECL|macro|E1000_LEDCTL_LED0_MODE_MASK
mdefine_line|#define E1000_LEDCTL_LED0_MODE_MASK  0x0000000F
DECL|macro|E1000_LEDCTL_LED0_MODE_SHIFT
mdefine_line|#define E1000_LEDCTL_LED0_MODE_SHIFT 0
DECL|macro|E1000_LEDCTL_LED0_IVRT
mdefine_line|#define E1000_LEDCTL_LED0_IVRT       0x00000040
DECL|macro|E1000_LEDCTL_LED0_BLINK
mdefine_line|#define E1000_LEDCTL_LED0_BLINK      0x00000080
DECL|macro|E1000_LEDCTL_LED1_MODE_MASK
mdefine_line|#define E1000_LEDCTL_LED1_MODE_MASK  0x00000F00
DECL|macro|E1000_LEDCTL_LED1_MODE_SHIFT
mdefine_line|#define E1000_LEDCTL_LED1_MODE_SHIFT 8
DECL|macro|E1000_LEDCTL_LED1_IVRT
mdefine_line|#define E1000_LEDCTL_LED1_IVRT       0x00004000
DECL|macro|E1000_LEDCTL_LED1_BLINK
mdefine_line|#define E1000_LEDCTL_LED1_BLINK      0x00008000
DECL|macro|E1000_LEDCTL_LED2_MODE_MASK
mdefine_line|#define E1000_LEDCTL_LED2_MODE_MASK  0x000F0000
DECL|macro|E1000_LEDCTL_LED2_MODE_SHIFT
mdefine_line|#define E1000_LEDCTL_LED2_MODE_SHIFT 16
DECL|macro|E1000_LEDCTL_LED2_IVRT
mdefine_line|#define E1000_LEDCTL_LED2_IVRT       0x00400000
DECL|macro|E1000_LEDCTL_LED2_BLINK
mdefine_line|#define E1000_LEDCTL_LED2_BLINK      0x00800000
DECL|macro|E1000_LEDCTL_LED3_MODE_MASK
mdefine_line|#define E1000_LEDCTL_LED3_MODE_MASK  0x0F000000
DECL|macro|E1000_LEDCTL_LED3_MODE_SHIFT
mdefine_line|#define E1000_LEDCTL_LED3_MODE_SHIFT 24
DECL|macro|E1000_LEDCTL_LED3_IVRT
mdefine_line|#define E1000_LEDCTL_LED3_IVRT       0x40000000
DECL|macro|E1000_LEDCTL_LED3_BLINK
mdefine_line|#define E1000_LEDCTL_LED3_BLINK      0x80000000
DECL|macro|E1000_LEDCTL_MODE_LINK_10_1000
mdefine_line|#define E1000_LEDCTL_MODE_LINK_10_1000  0x0
DECL|macro|E1000_LEDCTL_MODE_LINK_100_1000
mdefine_line|#define E1000_LEDCTL_MODE_LINK_100_1000 0x1
DECL|macro|E1000_LEDCTL_MODE_LINK_UP
mdefine_line|#define E1000_LEDCTL_MODE_LINK_UP       0x2
DECL|macro|E1000_LEDCTL_MODE_ACTIVITY
mdefine_line|#define E1000_LEDCTL_MODE_ACTIVITY      0x3
DECL|macro|E1000_LEDCTL_MODE_LINK_ACTIVITY
mdefine_line|#define E1000_LEDCTL_MODE_LINK_ACTIVITY 0x4
DECL|macro|E1000_LEDCTL_MODE_LINK_10
mdefine_line|#define E1000_LEDCTL_MODE_LINK_10       0x5
DECL|macro|E1000_LEDCTL_MODE_LINK_100
mdefine_line|#define E1000_LEDCTL_MODE_LINK_100      0x6
DECL|macro|E1000_LEDCTL_MODE_LINK_1000
mdefine_line|#define E1000_LEDCTL_MODE_LINK_1000     0x7
DECL|macro|E1000_LEDCTL_MODE_PCIX_MODE
mdefine_line|#define E1000_LEDCTL_MODE_PCIX_MODE     0x8
DECL|macro|E1000_LEDCTL_MODE_FULL_DUPLEX
mdefine_line|#define E1000_LEDCTL_MODE_FULL_DUPLEX   0x9
DECL|macro|E1000_LEDCTL_MODE_COLLISION
mdefine_line|#define E1000_LEDCTL_MODE_COLLISION     0xA
DECL|macro|E1000_LEDCTL_MODE_BUS_SPEED
mdefine_line|#define E1000_LEDCTL_MODE_BUS_SPEED     0xB
DECL|macro|E1000_LEDCTL_MODE_BUS_SIZE
mdefine_line|#define E1000_LEDCTL_MODE_BUS_SIZE      0xC
DECL|macro|E1000_LEDCTL_MODE_PAUSED
mdefine_line|#define E1000_LEDCTL_MODE_PAUSED        0xD
DECL|macro|E1000_LEDCTL_MODE_LED_ON
mdefine_line|#define E1000_LEDCTL_MODE_LED_ON        0xE
DECL|macro|E1000_LEDCTL_MODE_LED_OFF
mdefine_line|#define E1000_LEDCTL_MODE_LED_OFF       0xF
multiline_comment|/* Receive Address */
DECL|macro|E1000_RAH_AV
mdefine_line|#define E1000_RAH_AV  0x80000000        /* Receive descriptor valid */
multiline_comment|/* Interrupt Cause Read */
DECL|macro|E1000_ICR_TXDW
mdefine_line|#define E1000_ICR_TXDW    0x00000001    /* Transmit desc written back */
DECL|macro|E1000_ICR_TXQE
mdefine_line|#define E1000_ICR_TXQE    0x00000002    /* Transmit Queue empty */
DECL|macro|E1000_ICR_LSC
mdefine_line|#define E1000_ICR_LSC     0x00000004    /* Link Status Change */
DECL|macro|E1000_ICR_RXSEQ
mdefine_line|#define E1000_ICR_RXSEQ   0x00000008    /* rx sequence error */
DECL|macro|E1000_ICR_RXDMT0
mdefine_line|#define E1000_ICR_RXDMT0  0x00000010    /* rx desc min. threshold (0) */
DECL|macro|E1000_ICR_RXO
mdefine_line|#define E1000_ICR_RXO     0x00000040    /* rx overrun */
DECL|macro|E1000_ICR_RXT0
mdefine_line|#define E1000_ICR_RXT0    0x00000080    /* rx timer intr (ring 0) */
DECL|macro|E1000_ICR_MDAC
mdefine_line|#define E1000_ICR_MDAC    0x00000200    /* MDIO access complete */
DECL|macro|E1000_ICR_RXCFG
mdefine_line|#define E1000_ICR_RXCFG   0x00000400    /* RX /c/ ordered set */
DECL|macro|E1000_ICR_GPI_EN0
mdefine_line|#define E1000_ICR_GPI_EN0 0x00000800    /* GP Int 0 */
DECL|macro|E1000_ICR_GPI_EN1
mdefine_line|#define E1000_ICR_GPI_EN1 0x00001000    /* GP Int 1 */
DECL|macro|E1000_ICR_GPI_EN2
mdefine_line|#define E1000_ICR_GPI_EN2 0x00002000    /* GP Int 2 */
DECL|macro|E1000_ICR_GPI_EN3
mdefine_line|#define E1000_ICR_GPI_EN3 0x00004000    /* GP Int 3 */
DECL|macro|E1000_ICR_TXD_LOW
mdefine_line|#define E1000_ICR_TXD_LOW 0x00008000
DECL|macro|E1000_ICR_SRPD
mdefine_line|#define E1000_ICR_SRPD    0x00010000
multiline_comment|/* Interrupt Cause Set */
DECL|macro|E1000_ICS_TXDW
mdefine_line|#define E1000_ICS_TXDW    E1000_ICR_TXDW        /* Transmit desc written back */
DECL|macro|E1000_ICS_TXQE
mdefine_line|#define E1000_ICS_TXQE    E1000_ICR_TXQE        /* Transmit Queue empty */
DECL|macro|E1000_ICS_LSC
mdefine_line|#define E1000_ICS_LSC     E1000_ICR_LSC         /* Link Status Change */
DECL|macro|E1000_ICS_RXSEQ
mdefine_line|#define E1000_ICS_RXSEQ   E1000_ICR_RXSEQ       /* rx sequence error */
DECL|macro|E1000_ICS_RXDMT0
mdefine_line|#define E1000_ICS_RXDMT0  E1000_ICR_RXDMT0      /* rx desc min. threshold */
DECL|macro|E1000_ICS_RXO
mdefine_line|#define E1000_ICS_RXO     E1000_ICR_RXO         /* rx overrun */
DECL|macro|E1000_ICS_RXT0
mdefine_line|#define E1000_ICS_RXT0    E1000_ICR_RXT0        /* rx timer intr */
DECL|macro|E1000_ICS_MDAC
mdefine_line|#define E1000_ICS_MDAC    E1000_ICR_MDAC        /* MDIO access complete */
DECL|macro|E1000_ICS_RXCFG
mdefine_line|#define E1000_ICS_RXCFG   E1000_ICR_RXCFG       /* RX /c/ ordered set */
DECL|macro|E1000_ICS_GPI_EN0
mdefine_line|#define E1000_ICS_GPI_EN0 E1000_ICR_GPI_EN0     /* GP Int 0 */
DECL|macro|E1000_ICS_GPI_EN1
mdefine_line|#define E1000_ICS_GPI_EN1 E1000_ICR_GPI_EN1     /* GP Int 1 */
DECL|macro|E1000_ICS_GPI_EN2
mdefine_line|#define E1000_ICS_GPI_EN2 E1000_ICR_GPI_EN2     /* GP Int 2 */
DECL|macro|E1000_ICS_GPI_EN3
mdefine_line|#define E1000_ICS_GPI_EN3 E1000_ICR_GPI_EN3     /* GP Int 3 */
DECL|macro|E1000_ICS_TXD_LOW
mdefine_line|#define E1000_ICS_TXD_LOW E1000_ICR_TXD_LOW
DECL|macro|E1000_ICS_SRPD
mdefine_line|#define E1000_ICS_SRPD    E1000_ICR_SRPD
multiline_comment|/* Interrupt Mask Set */
DECL|macro|E1000_IMS_TXDW
mdefine_line|#define E1000_IMS_TXDW    E1000_ICR_TXDW        /* Transmit desc written back */
DECL|macro|E1000_IMS_TXQE
mdefine_line|#define E1000_IMS_TXQE    E1000_ICR_TXQE        /* Transmit Queue empty */
DECL|macro|E1000_IMS_LSC
mdefine_line|#define E1000_IMS_LSC     E1000_ICR_LSC         /* Link Status Change */
DECL|macro|E1000_IMS_RXSEQ
mdefine_line|#define E1000_IMS_RXSEQ   E1000_ICR_RXSEQ       /* rx sequence error */
DECL|macro|E1000_IMS_RXDMT0
mdefine_line|#define E1000_IMS_RXDMT0  E1000_ICR_RXDMT0      /* rx desc min. threshold */
DECL|macro|E1000_IMS_RXO
mdefine_line|#define E1000_IMS_RXO     E1000_ICR_RXO         /* rx overrun */
DECL|macro|E1000_IMS_RXT0
mdefine_line|#define E1000_IMS_RXT0    E1000_ICR_RXT0        /* rx timer intr */
DECL|macro|E1000_IMS_MDAC
mdefine_line|#define E1000_IMS_MDAC    E1000_ICR_MDAC        /* MDIO access complete */
DECL|macro|E1000_IMS_RXCFG
mdefine_line|#define E1000_IMS_RXCFG   E1000_ICR_RXCFG       /* RX /c/ ordered set */
DECL|macro|E1000_IMS_GPI_EN0
mdefine_line|#define E1000_IMS_GPI_EN0 E1000_ICR_GPI_EN0     /* GP Int 0 */
DECL|macro|E1000_IMS_GPI_EN1
mdefine_line|#define E1000_IMS_GPI_EN1 E1000_ICR_GPI_EN1     /* GP Int 1 */
DECL|macro|E1000_IMS_GPI_EN2
mdefine_line|#define E1000_IMS_GPI_EN2 E1000_ICR_GPI_EN2     /* GP Int 2 */
DECL|macro|E1000_IMS_GPI_EN3
mdefine_line|#define E1000_IMS_GPI_EN3 E1000_ICR_GPI_EN3     /* GP Int 3 */
DECL|macro|E1000_IMS_TXD_LOW
mdefine_line|#define E1000_IMS_TXD_LOW E1000_ICR_TXD_LOW
DECL|macro|E1000_IMS_SRPD
mdefine_line|#define E1000_IMS_SRPD    E1000_ICR_SRPD
multiline_comment|/* Interrupt Mask Clear */
DECL|macro|E1000_IMC_TXDW
mdefine_line|#define E1000_IMC_TXDW    E1000_ICR_TXDW        /* Transmit desc written back */
DECL|macro|E1000_IMC_TXQE
mdefine_line|#define E1000_IMC_TXQE    E1000_ICR_TXQE        /* Transmit Queue empty */
DECL|macro|E1000_IMC_LSC
mdefine_line|#define E1000_IMC_LSC     E1000_ICR_LSC         /* Link Status Change */
DECL|macro|E1000_IMC_RXSEQ
mdefine_line|#define E1000_IMC_RXSEQ   E1000_ICR_RXSEQ       /* rx sequence error */
DECL|macro|E1000_IMC_RXDMT0
mdefine_line|#define E1000_IMC_RXDMT0  E1000_ICR_RXDMT0      /* rx desc min. threshold */
DECL|macro|E1000_IMC_RXO
mdefine_line|#define E1000_IMC_RXO     E1000_ICR_RXO         /* rx overrun */
DECL|macro|E1000_IMC_RXT0
mdefine_line|#define E1000_IMC_RXT0    E1000_ICR_RXT0        /* rx timer intr */
DECL|macro|E1000_IMC_MDAC
mdefine_line|#define E1000_IMC_MDAC    E1000_ICR_MDAC        /* MDIO access complete */
DECL|macro|E1000_IMC_RXCFG
mdefine_line|#define E1000_IMC_RXCFG   E1000_ICR_RXCFG       /* RX /c/ ordered set */
DECL|macro|E1000_IMC_GPI_EN0
mdefine_line|#define E1000_IMC_GPI_EN0 E1000_ICR_GPI_EN0     /* GP Int 0 */
DECL|macro|E1000_IMC_GPI_EN1
mdefine_line|#define E1000_IMC_GPI_EN1 E1000_ICR_GPI_EN1     /* GP Int 1 */
DECL|macro|E1000_IMC_GPI_EN2
mdefine_line|#define E1000_IMC_GPI_EN2 E1000_ICR_GPI_EN2     /* GP Int 2 */
DECL|macro|E1000_IMC_GPI_EN3
mdefine_line|#define E1000_IMC_GPI_EN3 E1000_ICR_GPI_EN3     /* GP Int 3 */
DECL|macro|E1000_IMC_TXD_LOW
mdefine_line|#define E1000_IMC_TXD_LOW E1000_ICR_TXD_LOW
DECL|macro|E1000_IMC_SRPD
mdefine_line|#define E1000_IMC_SRPD    E1000_ICR_SRPD
multiline_comment|/* Receive Control */
DECL|macro|E1000_RCTL_RST
mdefine_line|#define E1000_RCTL_RST          0x00000001      /* Software reset */
DECL|macro|E1000_RCTL_EN
mdefine_line|#define E1000_RCTL_EN           0x00000002      /* enable */
DECL|macro|E1000_RCTL_SBP
mdefine_line|#define E1000_RCTL_SBP          0x00000004      /* store bad packet */
DECL|macro|E1000_RCTL_UPE
mdefine_line|#define E1000_RCTL_UPE          0x00000008      /* unicast promiscuous enable */
DECL|macro|E1000_RCTL_MPE
mdefine_line|#define E1000_RCTL_MPE          0x00000010      /* multicast promiscuous enab */
DECL|macro|E1000_RCTL_LPE
mdefine_line|#define E1000_RCTL_LPE          0x00000020      /* long packet enable */
DECL|macro|E1000_RCTL_LBM_NO
mdefine_line|#define E1000_RCTL_LBM_NO       0x00000000      /* no loopback mode */
DECL|macro|E1000_RCTL_LBM_MAC
mdefine_line|#define E1000_RCTL_LBM_MAC      0x00000040      /* MAC loopback mode */
DECL|macro|E1000_RCTL_LBM_SLP
mdefine_line|#define E1000_RCTL_LBM_SLP      0x00000080      /* serial link loopback mode */
DECL|macro|E1000_RCTL_LBM_TCVR
mdefine_line|#define E1000_RCTL_LBM_TCVR     0x000000C0      /* tcvr loopback mode */
DECL|macro|E1000_RCTL_RDMTS_HALF
mdefine_line|#define E1000_RCTL_RDMTS_HALF   0x00000000      /* rx desc min threshold size */
DECL|macro|E1000_RCTL_RDMTS_QUAT
mdefine_line|#define E1000_RCTL_RDMTS_QUAT   0x00000100      /* rx desc min threshold size */
DECL|macro|E1000_RCTL_RDMTS_EIGTH
mdefine_line|#define E1000_RCTL_RDMTS_EIGTH  0x00000200      /* rx desc min threshold size */
DECL|macro|E1000_RCTL_MO_SHIFT
mdefine_line|#define E1000_RCTL_MO_SHIFT     12              /* multicast offset shift */
DECL|macro|E1000_RCTL_MO_0
mdefine_line|#define E1000_RCTL_MO_0         0x00000000      /* multicast offset 11:0 */
DECL|macro|E1000_RCTL_MO_1
mdefine_line|#define E1000_RCTL_MO_1         0x00001000      /* multicast offset 12:1 */
DECL|macro|E1000_RCTL_MO_2
mdefine_line|#define E1000_RCTL_MO_2         0x00002000      /* multicast offset 13:2 */
DECL|macro|E1000_RCTL_MO_3
mdefine_line|#define E1000_RCTL_MO_3         0x00003000      /* multicast offset 15:4 */
DECL|macro|E1000_RCTL_MDR
mdefine_line|#define E1000_RCTL_MDR          0x00004000      /* multicast desc ring 0 */
DECL|macro|E1000_RCTL_BAM
mdefine_line|#define E1000_RCTL_BAM          0x00008000      /* broadcast enable */
multiline_comment|/* these buffer sizes are valid if E1000_RCTL_BSEX is 0 */
DECL|macro|E1000_RCTL_SZ_2048
mdefine_line|#define E1000_RCTL_SZ_2048      0x00000000      /* rx buffer size 2048 */
DECL|macro|E1000_RCTL_SZ_1024
mdefine_line|#define E1000_RCTL_SZ_1024      0x00010000      /* rx buffer size 1024 */
DECL|macro|E1000_RCTL_SZ_512
mdefine_line|#define E1000_RCTL_SZ_512       0x00020000      /* rx buffer size 512 */
DECL|macro|E1000_RCTL_SZ_256
mdefine_line|#define E1000_RCTL_SZ_256       0x00030000      /* rx buffer size 256 */
multiline_comment|/* these buffer sizes are valid if E1000_RCTL_BSEX is 1 */
DECL|macro|E1000_RCTL_SZ_16384
mdefine_line|#define E1000_RCTL_SZ_16384     0x00010000      /* rx buffer size 16384 */
DECL|macro|E1000_RCTL_SZ_8192
mdefine_line|#define E1000_RCTL_SZ_8192      0x00020000      /* rx buffer size 8192 */
DECL|macro|E1000_RCTL_SZ_4096
mdefine_line|#define E1000_RCTL_SZ_4096      0x00030000      /* rx buffer size 4096 */
DECL|macro|E1000_RCTL_VFE
mdefine_line|#define E1000_RCTL_VFE          0x00040000      /* vlan filter enable */
DECL|macro|E1000_RCTL_CFIEN
mdefine_line|#define E1000_RCTL_CFIEN        0x00080000      /* canonical form enable */
DECL|macro|E1000_RCTL_CFI
mdefine_line|#define E1000_RCTL_CFI          0x00100000      /* canonical form indicator */
DECL|macro|E1000_RCTL_DPF
mdefine_line|#define E1000_RCTL_DPF          0x00400000      /* discard pause frames */
DECL|macro|E1000_RCTL_PMCF
mdefine_line|#define E1000_RCTL_PMCF         0x00800000      /* pass MAC control frames */
DECL|macro|E1000_RCTL_BSEX
mdefine_line|#define E1000_RCTL_BSEX         0x02000000      /* Buffer size extension */
multiline_comment|/* Receive Descriptor */
DECL|macro|E1000_RDT_DELAY
mdefine_line|#define E1000_RDT_DELAY 0x0000ffff      /* Delay timer (1=1024us) */
DECL|macro|E1000_RDT_FPDB
mdefine_line|#define E1000_RDT_FPDB  0x80000000      /* Flush descriptor block */
DECL|macro|E1000_RDLEN_LEN
mdefine_line|#define E1000_RDLEN_LEN 0x0007ff80      /* descriptor length */
DECL|macro|E1000_RDH_RDH
mdefine_line|#define E1000_RDH_RDH   0x0000ffff      /* receive descriptor head */
DECL|macro|E1000_RDT_RDT
mdefine_line|#define E1000_RDT_RDT   0x0000ffff      /* receive descriptor tail */
multiline_comment|/* Flow Control */
DECL|macro|E1000_FCRTH_RTH
mdefine_line|#define E1000_FCRTH_RTH  0x0000FFF8     /* Mask Bits[15:3] for RTH */
DECL|macro|E1000_FCRTH_XFCE
mdefine_line|#define E1000_FCRTH_XFCE 0x80000000     /* External Flow Control Enable */
DECL|macro|E1000_FCRTL_RTL
mdefine_line|#define E1000_FCRTL_RTL  0x0000FFF8     /* Mask Bits[15:3] for RTL */
DECL|macro|E1000_FCRTL_XONE
mdefine_line|#define E1000_FCRTL_XONE 0x80000000     /* Enable XON frame transmission */
multiline_comment|/* Receive Descriptor Control */
DECL|macro|E1000_RXDCTL_PTHRESH
mdefine_line|#define E1000_RXDCTL_PTHRESH 0x0000003F /* RXDCTL Prefetch Threshold */
DECL|macro|E1000_RXDCTL_HTHRESH
mdefine_line|#define E1000_RXDCTL_HTHRESH 0x00003F00 /* RXDCTL Host Threshold */
DECL|macro|E1000_RXDCTL_WTHRESH
mdefine_line|#define E1000_RXDCTL_WTHRESH 0x003F0000 /* RXDCTL Writeback Threshold */
DECL|macro|E1000_RXDCTL_GRAN
mdefine_line|#define E1000_RXDCTL_GRAN    0x01000000 /* RXDCTL Granularity */
multiline_comment|/* Transmit Descriptor Control */
DECL|macro|E1000_TXDCTL_PTHRESH
mdefine_line|#define E1000_TXDCTL_PTHRESH 0x000000FF /* TXDCTL Prefetch Threshold */
DECL|macro|E1000_TXDCTL_HTHRESH
mdefine_line|#define E1000_TXDCTL_HTHRESH 0x0000FF00 /* TXDCTL Host Threshold */
DECL|macro|E1000_TXDCTL_WTHRESH
mdefine_line|#define E1000_TXDCTL_WTHRESH 0x00FF0000 /* TXDCTL Writeback Threshold */
DECL|macro|E1000_TXDCTL_GRAN
mdefine_line|#define E1000_TXDCTL_GRAN    0x01000000 /* TXDCTL Granularity */
DECL|macro|E1000_TXDCTL_LWTHRESH
mdefine_line|#define E1000_TXDCTL_LWTHRESH 0xFE000000 /* TXDCTL Low Threshold */
multiline_comment|/* Transmit Configuration Word */
DECL|macro|E1000_TXCW_FD
mdefine_line|#define E1000_TXCW_FD         0x00000020        /* TXCW full duplex */
DECL|macro|E1000_TXCW_HD
mdefine_line|#define E1000_TXCW_HD         0x00000040        /* TXCW half duplex */
DECL|macro|E1000_TXCW_PAUSE
mdefine_line|#define E1000_TXCW_PAUSE      0x00000080        /* TXCW sym pause request */
DECL|macro|E1000_TXCW_ASM_DIR
mdefine_line|#define E1000_TXCW_ASM_DIR    0x00000100        /* TXCW astm pause direction */
DECL|macro|E1000_TXCW_PAUSE_MASK
mdefine_line|#define E1000_TXCW_PAUSE_MASK 0x00000180        /* TXCW pause request mask */
DECL|macro|E1000_TXCW_RF
mdefine_line|#define E1000_TXCW_RF         0x00003000        /* TXCW remote fault */
DECL|macro|E1000_TXCW_NP
mdefine_line|#define E1000_TXCW_NP         0x00008000        /* TXCW next page */
DECL|macro|E1000_TXCW_CW
mdefine_line|#define E1000_TXCW_CW         0x0000ffff        /* TxConfigWord mask */
DECL|macro|E1000_TXCW_TXC
mdefine_line|#define E1000_TXCW_TXC        0x40000000        /* Transmit Config control */
DECL|macro|E1000_TXCW_ANE
mdefine_line|#define E1000_TXCW_ANE        0x80000000        /* Auto-neg enable */
multiline_comment|/* Receive Configuration Word */
DECL|macro|E1000_RXCW_CW
mdefine_line|#define E1000_RXCW_CW    0x0000ffff     /* RxConfigWord mask */
DECL|macro|E1000_RXCW_NC
mdefine_line|#define E1000_RXCW_NC    0x04000000     /* Receive config no carrier */
DECL|macro|E1000_RXCW_IV
mdefine_line|#define E1000_RXCW_IV    0x08000000     /* Receive config invalid */
DECL|macro|E1000_RXCW_CC
mdefine_line|#define E1000_RXCW_CC    0x10000000     /* Receive config change */
DECL|macro|E1000_RXCW_C
mdefine_line|#define E1000_RXCW_C     0x20000000     /* Receive config */
DECL|macro|E1000_RXCW_SYNCH
mdefine_line|#define E1000_RXCW_SYNCH 0x40000000     /* Receive config synch */
DECL|macro|E1000_RXCW_ANC
mdefine_line|#define E1000_RXCW_ANC   0x80000000     /* Auto-neg complete */
multiline_comment|/* Transmit Control */
DECL|macro|E1000_TCTL_RST
mdefine_line|#define E1000_TCTL_RST    0x00000001    /* software reset */
DECL|macro|E1000_TCTL_EN
mdefine_line|#define E1000_TCTL_EN     0x00000002    /* enable tx */
DECL|macro|E1000_TCTL_BCE
mdefine_line|#define E1000_TCTL_BCE    0x00000004    /* busy check enable */
DECL|macro|E1000_TCTL_PSP
mdefine_line|#define E1000_TCTL_PSP    0x00000008    /* pad short packets */
DECL|macro|E1000_TCTL_CT
mdefine_line|#define E1000_TCTL_CT     0x00000ff0    /* collision threshold */
DECL|macro|E1000_TCTL_COLD
mdefine_line|#define E1000_TCTL_COLD   0x003ff000    /* collision distance */
DECL|macro|E1000_TCTL_SWXOFF
mdefine_line|#define E1000_TCTL_SWXOFF 0x00400000    /* SW Xoff transmission */
DECL|macro|E1000_TCTL_PBE
mdefine_line|#define E1000_TCTL_PBE    0x00800000    /* Packet Burst Enable */
DECL|macro|E1000_TCTL_RTLC
mdefine_line|#define E1000_TCTL_RTLC   0x01000000    /* Re-transmit on late collision */
DECL|macro|E1000_TCTL_NRTU
mdefine_line|#define E1000_TCTL_NRTU   0x02000000    /* No Re-transmit on underrun */
multiline_comment|/* Receive Checksum Control */
DECL|macro|E1000_RXCSUM_PCSS_MASK
mdefine_line|#define E1000_RXCSUM_PCSS_MASK 0x000000FF   /* Packet Checksum Start */
DECL|macro|E1000_RXCSUM_IPOFL
mdefine_line|#define E1000_RXCSUM_IPOFL     0x00000100   /* IPv4 checksum offload */
DECL|macro|E1000_RXCSUM_TUOFL
mdefine_line|#define E1000_RXCSUM_TUOFL     0x00000200   /* TCP / UDP checksum offload */
DECL|macro|E1000_RXCSUM_IPV6OFL
mdefine_line|#define E1000_RXCSUM_IPV6OFL   0x00000400   /* IPv6 checksum offload */
multiline_comment|/* Definitions for power management and wakeup registers */
multiline_comment|/* Wake Up Control */
DECL|macro|E1000_WUC_APME
mdefine_line|#define E1000_WUC_APME       0x00000001 /* APM Enable */
DECL|macro|E1000_WUC_PME_EN
mdefine_line|#define E1000_WUC_PME_EN     0x00000002 /* PME Enable */
DECL|macro|E1000_WUC_PME_STATUS
mdefine_line|#define E1000_WUC_PME_STATUS 0x00000004 /* PME Status */
DECL|macro|E1000_WUC_APMPME
mdefine_line|#define E1000_WUC_APMPME     0x00000008 /* Assert PME on APM Wakeup */
multiline_comment|/* Wake Up Filter Control */
DECL|macro|E1000_WUFC_LNKC
mdefine_line|#define E1000_WUFC_LNKC 0x00000001 /* Link Status Change Wakeup Enable */
DECL|macro|E1000_WUFC_MAG
mdefine_line|#define E1000_WUFC_MAG  0x00000002 /* Magic Packet Wakeup Enable */
DECL|macro|E1000_WUFC_EX
mdefine_line|#define E1000_WUFC_EX   0x00000004 /* Directed Exact Wakeup Enable */
DECL|macro|E1000_WUFC_MC
mdefine_line|#define E1000_WUFC_MC   0x00000008 /* Directed Multicast Wakeup Enable */
DECL|macro|E1000_WUFC_BC
mdefine_line|#define E1000_WUFC_BC   0x00000010 /* Broadcast Wakeup Enable */
DECL|macro|E1000_WUFC_ARP
mdefine_line|#define E1000_WUFC_ARP  0x00000020 /* ARP Request Packet Wakeup Enable */
DECL|macro|E1000_WUFC_IPV4
mdefine_line|#define E1000_WUFC_IPV4 0x00000040 /* Directed IPv4 Packet Wakeup Enable */
DECL|macro|E1000_WUFC_IPV6
mdefine_line|#define E1000_WUFC_IPV6 0x00000080 /* Directed IPv6 Packet Wakeup Enable */
DECL|macro|E1000_WUFC_FLX0
mdefine_line|#define E1000_WUFC_FLX0 0x00010000 /* Flexible Filter 0 Enable */
DECL|macro|E1000_WUFC_FLX1
mdefine_line|#define E1000_WUFC_FLX1 0x00020000 /* Flexible Filter 1 Enable */
DECL|macro|E1000_WUFC_FLX2
mdefine_line|#define E1000_WUFC_FLX2 0x00040000 /* Flexible Filter 2 Enable */
DECL|macro|E1000_WUFC_FLX3
mdefine_line|#define E1000_WUFC_FLX3 0x00080000 /* Flexible Filter 3 Enable */
DECL|macro|E1000_WUFC_ALL_FILTERS
mdefine_line|#define E1000_WUFC_ALL_FILTERS 0x000F00FF /* Mask for all wakeup filters */
DECL|macro|E1000_WUFC_FLX_OFFSET
mdefine_line|#define E1000_WUFC_FLX_OFFSET 16       /* Offset to the Flexible Filters bits */
DECL|macro|E1000_WUFC_FLX_FILTERS
mdefine_line|#define E1000_WUFC_FLX_FILTERS 0x000F0000 /* Mask for the 4 flexible filters */
multiline_comment|/* Wake Up Status */
DECL|macro|E1000_WUS_LNKC
mdefine_line|#define E1000_WUS_LNKC 0x00000001 /* Link Status Changed */
DECL|macro|E1000_WUS_MAG
mdefine_line|#define E1000_WUS_MAG  0x00000002 /* Magic Packet Received */
DECL|macro|E1000_WUS_EX
mdefine_line|#define E1000_WUS_EX   0x00000004 /* Directed Exact Received */
DECL|macro|E1000_WUS_MC
mdefine_line|#define E1000_WUS_MC   0x00000008 /* Directed Multicast Received */
DECL|macro|E1000_WUS_BC
mdefine_line|#define E1000_WUS_BC   0x00000010 /* Broadcast Received */
DECL|macro|E1000_WUS_ARP
mdefine_line|#define E1000_WUS_ARP  0x00000020 /* ARP Request Packet Received */
DECL|macro|E1000_WUS_IPV4
mdefine_line|#define E1000_WUS_IPV4 0x00000040 /* Directed IPv4 Packet Wakeup Received */
DECL|macro|E1000_WUS_IPV6
mdefine_line|#define E1000_WUS_IPV6 0x00000080 /* Directed IPv6 Packet Wakeup Received */
DECL|macro|E1000_WUS_FLX0
mdefine_line|#define E1000_WUS_FLX0 0x00010000 /* Flexible Filter 0 Match */
DECL|macro|E1000_WUS_FLX1
mdefine_line|#define E1000_WUS_FLX1 0x00020000 /* Flexible Filter 1 Match */
DECL|macro|E1000_WUS_FLX2
mdefine_line|#define E1000_WUS_FLX2 0x00040000 /* Flexible Filter 2 Match */
DECL|macro|E1000_WUS_FLX3
mdefine_line|#define E1000_WUS_FLX3 0x00080000 /* Flexible Filter 3 Match */
DECL|macro|E1000_WUS_FLX_FILTERS
mdefine_line|#define E1000_WUS_FLX_FILTERS 0x000F0000 /* Mask for the 4 flexible filters */
multiline_comment|/* Management Control */
DECL|macro|E1000_MANC_SMBUS_EN
mdefine_line|#define E1000_MANC_SMBUS_EN      0x00000001 /* SMBus Enabled - RO */
DECL|macro|E1000_MANC_ASF_EN
mdefine_line|#define E1000_MANC_ASF_EN        0x00000002 /* ASF Enabled - RO */
DECL|macro|E1000_MANC_R_ON_FORCE
mdefine_line|#define E1000_MANC_R_ON_FORCE    0x00000004 /* Reset on Force TCO - RO */
DECL|macro|E1000_MANC_RMCP_EN
mdefine_line|#define E1000_MANC_RMCP_EN       0x00000100 /* Enable RCMP 026Fh Filtering */
DECL|macro|E1000_MANC_0298_EN
mdefine_line|#define E1000_MANC_0298_EN       0x00000200 /* Enable RCMP 0298h Filtering */
DECL|macro|E1000_MANC_IPV4_EN
mdefine_line|#define E1000_MANC_IPV4_EN       0x00000400 /* Enable IPv4 */
DECL|macro|E1000_MANC_IPV6_EN
mdefine_line|#define E1000_MANC_IPV6_EN       0x00000800 /* Enable IPv6 */
DECL|macro|E1000_MANC_SNAP_EN
mdefine_line|#define E1000_MANC_SNAP_EN       0x00001000 /* Accept LLC/SNAP */
DECL|macro|E1000_MANC_ARP_EN
mdefine_line|#define E1000_MANC_ARP_EN        0x00002000 /* Enable ARP Request Filtering */
DECL|macro|E1000_MANC_NEIGHBOR_EN
mdefine_line|#define E1000_MANC_NEIGHBOR_EN   0x00004000 /* Enable Neighbor Discovery &n;                                             * Filtering */
DECL|macro|E1000_MANC_TCO_RESET
mdefine_line|#define E1000_MANC_TCO_RESET     0x00010000 /* TCO Reset Occurred */
DECL|macro|E1000_MANC_RCV_TCO_EN
mdefine_line|#define E1000_MANC_RCV_TCO_EN    0x00020000 /* Receive TCO Packets Enabled */
DECL|macro|E1000_MANC_REPORT_STATUS
mdefine_line|#define E1000_MANC_REPORT_STATUS 0x00040000 /* Status Reporting Enabled */
DECL|macro|E1000_MANC_SMB_REQ
mdefine_line|#define E1000_MANC_SMB_REQ       0x01000000 /* SMBus Request */
DECL|macro|E1000_MANC_SMB_GNT
mdefine_line|#define E1000_MANC_SMB_GNT       0x02000000 /* SMBus Grant */
DECL|macro|E1000_MANC_SMB_CLK_IN
mdefine_line|#define E1000_MANC_SMB_CLK_IN    0x04000000 /* SMBus Clock In */
DECL|macro|E1000_MANC_SMB_DATA_IN
mdefine_line|#define E1000_MANC_SMB_DATA_IN   0x08000000 /* SMBus Data In */
DECL|macro|E1000_MANC_SMB_DATA_OUT
mdefine_line|#define E1000_MANC_SMB_DATA_OUT  0x10000000 /* SMBus Data Out */
DECL|macro|E1000_MANC_SMB_CLK_OUT
mdefine_line|#define E1000_MANC_SMB_CLK_OUT   0x20000000 /* SMBus Clock Out */
DECL|macro|E1000_MANC_SMB_DATA_OUT_SHIFT
mdefine_line|#define E1000_MANC_SMB_DATA_OUT_SHIFT  28 /* SMBus Data Out Shift */
DECL|macro|E1000_MANC_SMB_CLK_OUT_SHIFT
mdefine_line|#define E1000_MANC_SMB_CLK_OUT_SHIFT   29 /* SMBus Clock Out Shift */
multiline_comment|/* Wake Up Packet Length */
DECL|macro|E1000_WUPL_LENGTH_MASK
mdefine_line|#define E1000_WUPL_LENGTH_MASK 0x0FFF   /* Only the lower 12 bits are valid */
DECL|macro|E1000_MDALIGN
mdefine_line|#define E1000_MDALIGN          4096
multiline_comment|/* EEPROM Commands */
DECL|macro|EEPROM_READ_OPCODE
mdefine_line|#define EEPROM_READ_OPCODE  0x6  /* EERPOM read opcode */
DECL|macro|EEPROM_WRITE_OPCODE
mdefine_line|#define EEPROM_WRITE_OPCODE 0x5  /* EERPOM write opcode */
DECL|macro|EEPROM_ERASE_OPCODE
mdefine_line|#define EEPROM_ERASE_OPCODE 0x7  /* EERPOM erase opcode */
DECL|macro|EEPROM_EWEN_OPCODE
mdefine_line|#define EEPROM_EWEN_OPCODE  0x13 /* EERPOM erase/write enable */
DECL|macro|EEPROM_EWDS_OPCODE
mdefine_line|#define EEPROM_EWDS_OPCODE  0x10 /* EERPOM erast/write disable */
multiline_comment|/* EEPROM Word Offsets */
DECL|macro|EEPROM_ID_LED_SETTINGS
mdefine_line|#define EEPROM_ID_LED_SETTINGS     0x0004
DECL|macro|EEPROM_INIT_CONTROL1_REG
mdefine_line|#define EEPROM_INIT_CONTROL1_REG   0x000A
DECL|macro|EEPROM_INIT_CONTROL2_REG
mdefine_line|#define EEPROM_INIT_CONTROL2_REG   0x000F
DECL|macro|EEPROM_FLASH_VERSION
mdefine_line|#define EEPROM_FLASH_VERSION       0x0032
DECL|macro|EEPROM_CHECKSUM_REG
mdefine_line|#define EEPROM_CHECKSUM_REG        0x003F
multiline_comment|/* Word definitions for ID LED Settings */
DECL|macro|ID_LED_RESERVED_0000
mdefine_line|#define ID_LED_RESERVED_0000 0x0000
DECL|macro|ID_LED_RESERVED_FFFF
mdefine_line|#define ID_LED_RESERVED_FFFF 0xFFFF
DECL|macro|ID_LED_DEFAULT
mdefine_line|#define ID_LED_DEFAULT       ((ID_LED_OFF1_ON2 &lt;&lt; 12) | &bslash;&n;&t;&t;              (ID_LED_OFF1_OFF2 &lt;&lt; 8) | &bslash;&n;&t;&t;              (ID_LED_DEF1_DEF2 &lt;&lt; 4) | &bslash;&n;&t;&t;&t;      (ID_LED_DEF1_DEF2))
DECL|macro|ID_LED_DEF1_DEF2
mdefine_line|#define ID_LED_DEF1_DEF2     0x1
DECL|macro|ID_LED_DEF1_ON2
mdefine_line|#define ID_LED_DEF1_ON2      0x2
DECL|macro|ID_LED_DEF1_OFF2
mdefine_line|#define ID_LED_DEF1_OFF2     0x3
DECL|macro|ID_LED_ON1_DEF2
mdefine_line|#define ID_LED_ON1_DEF2      0x4
DECL|macro|ID_LED_ON1_ON2
mdefine_line|#define ID_LED_ON1_ON2       0x5
DECL|macro|ID_LED_ON1_OFF2
mdefine_line|#define ID_LED_ON1_OFF2      0x6
DECL|macro|ID_LED_OFF1_DEF2
mdefine_line|#define ID_LED_OFF1_DEF2     0x7
DECL|macro|ID_LED_OFF1_ON2
mdefine_line|#define ID_LED_OFF1_ON2      0x8
DECL|macro|ID_LED_OFF1_OFF2
mdefine_line|#define ID_LED_OFF1_OFF2     0x9
multiline_comment|/* Mask bits for fields in Word 0x0a of the EEPROM */
DECL|macro|EEPROM_WORD0A_ILOS
mdefine_line|#define EEPROM_WORD0A_ILOS   0x0010
DECL|macro|EEPROM_WORD0A_SWDPIO
mdefine_line|#define EEPROM_WORD0A_SWDPIO 0x01E0
DECL|macro|EEPROM_WORD0A_LRST
mdefine_line|#define EEPROM_WORD0A_LRST   0x0200
DECL|macro|EEPROM_WORD0A_FD
mdefine_line|#define EEPROM_WORD0A_FD     0x0400
DECL|macro|EEPROM_WORD0A_66MHZ
mdefine_line|#define EEPROM_WORD0A_66MHZ  0x0800
multiline_comment|/* Mask bits for fields in Word 0x0f of the EEPROM */
DECL|macro|EEPROM_WORD0F_PAUSE_MASK
mdefine_line|#define EEPROM_WORD0F_PAUSE_MASK 0x3000
DECL|macro|EEPROM_WORD0F_PAUSE
mdefine_line|#define EEPROM_WORD0F_PAUSE      0x1000
DECL|macro|EEPROM_WORD0F_ASM_DIR
mdefine_line|#define EEPROM_WORD0F_ASM_DIR    0x2000
DECL|macro|EEPROM_WORD0F_ANE
mdefine_line|#define EEPROM_WORD0F_ANE        0x0800
DECL|macro|EEPROM_WORD0F_SWPDIO_EXT
mdefine_line|#define EEPROM_WORD0F_SWPDIO_EXT 0x00F0
multiline_comment|/* For checksumming, the sum of all words in the EEPROM should equal 0xBABA. */
DECL|macro|EEPROM_SUM
mdefine_line|#define EEPROM_SUM 0xBABA
multiline_comment|/* EEPROM Map defines (WORD OFFSETS)*/
DECL|macro|EEPROM_NODE_ADDRESS_BYTE_0
mdefine_line|#define EEPROM_NODE_ADDRESS_BYTE_0 0
DECL|macro|EEPROM_PBA_BYTE_1
mdefine_line|#define EEPROM_PBA_BYTE_1          8
multiline_comment|/* EEPROM Map Sizes (Byte Counts) */
DECL|macro|PBA_SIZE
mdefine_line|#define PBA_SIZE 4
multiline_comment|/* Collision related configuration parameters */
DECL|macro|E1000_COLLISION_THRESHOLD
mdefine_line|#define E1000_COLLISION_THRESHOLD       16
DECL|macro|E1000_CT_SHIFT
mdefine_line|#define E1000_CT_SHIFT                  4
DECL|macro|E1000_COLLISION_DISTANCE
mdefine_line|#define E1000_COLLISION_DISTANCE        64
DECL|macro|E1000_FDX_COLLISION_DISTANCE
mdefine_line|#define E1000_FDX_COLLISION_DISTANCE    E1000_COLLISION_DISTANCE
DECL|macro|E1000_HDX_COLLISION_DISTANCE
mdefine_line|#define E1000_HDX_COLLISION_DISTANCE    E1000_COLLISION_DISTANCE
DECL|macro|E1000_GB_HDX_COLLISION_DISTANCE
mdefine_line|#define E1000_GB_HDX_COLLISION_DISTANCE 512
DECL|macro|E1000_COLD_SHIFT
mdefine_line|#define E1000_COLD_SHIFT                12
multiline_comment|/* The number of Transmit and Receive Descriptors must be a multiple of 8 */
DECL|macro|REQ_TX_DESCRIPTOR_MULTIPLE
mdefine_line|#define REQ_TX_DESCRIPTOR_MULTIPLE  8
DECL|macro|REQ_RX_DESCRIPTOR_MULTIPLE
mdefine_line|#define REQ_RX_DESCRIPTOR_MULTIPLE  8
multiline_comment|/* Default values for the transmit IPG register */
DECL|macro|DEFAULT_82542_TIPG_IPGT
mdefine_line|#define DEFAULT_82542_TIPG_IPGT        10
DECL|macro|DEFAULT_82543_TIPG_IPGT_FIBER
mdefine_line|#define DEFAULT_82543_TIPG_IPGT_FIBER  9
DECL|macro|DEFAULT_82543_TIPG_IPGT_COPPER
mdefine_line|#define DEFAULT_82543_TIPG_IPGT_COPPER 8
DECL|macro|E1000_TIPG_IPGT_MASK
mdefine_line|#define E1000_TIPG_IPGT_MASK  0x000003FF
DECL|macro|E1000_TIPG_IPGR1_MASK
mdefine_line|#define E1000_TIPG_IPGR1_MASK 0x000FFC00
DECL|macro|E1000_TIPG_IPGR2_MASK
mdefine_line|#define E1000_TIPG_IPGR2_MASK 0x3FF00000
DECL|macro|DEFAULT_82542_TIPG_IPGR1
mdefine_line|#define DEFAULT_82542_TIPG_IPGR1 2
DECL|macro|DEFAULT_82543_TIPG_IPGR1
mdefine_line|#define DEFAULT_82543_TIPG_IPGR1 8
DECL|macro|E1000_TIPG_IPGR1_SHIFT
mdefine_line|#define E1000_TIPG_IPGR1_SHIFT  10
DECL|macro|DEFAULT_82542_TIPG_IPGR2
mdefine_line|#define DEFAULT_82542_TIPG_IPGR2 10
DECL|macro|DEFAULT_82543_TIPG_IPGR2
mdefine_line|#define DEFAULT_82543_TIPG_IPGR2 6
DECL|macro|E1000_TIPG_IPGR2_SHIFT
mdefine_line|#define E1000_TIPG_IPGR2_SHIFT  20
DECL|macro|E1000_TXDMAC_DPP
mdefine_line|#define E1000_TXDMAC_DPP 0x00000001
multiline_comment|/* Adaptive IFS defines */
DECL|macro|TX_THRESHOLD_START
mdefine_line|#define TX_THRESHOLD_START     8
DECL|macro|TX_THRESHOLD_INCREMENT
mdefine_line|#define TX_THRESHOLD_INCREMENT 10
DECL|macro|TX_THRESHOLD_DECREMENT
mdefine_line|#define TX_THRESHOLD_DECREMENT 1
DECL|macro|TX_THRESHOLD_STOP
mdefine_line|#define TX_THRESHOLD_STOP      190
DECL|macro|TX_THRESHOLD_DISABLE
mdefine_line|#define TX_THRESHOLD_DISABLE   0
DECL|macro|TX_THRESHOLD_TIMER_MS
mdefine_line|#define TX_THRESHOLD_TIMER_MS  10000
DECL|macro|MIN_NUM_XMITS
mdefine_line|#define MIN_NUM_XMITS          1000
DECL|macro|IFS_MAX
mdefine_line|#define IFS_MAX                80
DECL|macro|IFS_STEP
mdefine_line|#define IFS_STEP               10
DECL|macro|IFS_MIN
mdefine_line|#define IFS_MIN                40
DECL|macro|IFS_RATIO
mdefine_line|#define IFS_RATIO              4
multiline_comment|/* PBA constants */
DECL|macro|E1000_PBA_16K
mdefine_line|#define E1000_PBA_16K 0x0010    /* 16KB, default TX allocation */
DECL|macro|E1000_PBA_24K
mdefine_line|#define E1000_PBA_24K 0x0018
DECL|macro|E1000_PBA_40K
mdefine_line|#define E1000_PBA_40K 0x0028
DECL|macro|E1000_PBA_48K
mdefine_line|#define E1000_PBA_48K 0x0030    /* 48KB, default RX allocation */
multiline_comment|/* Flow Control Constants */
DECL|macro|FLOW_CONTROL_ADDRESS_LOW
mdefine_line|#define FLOW_CONTROL_ADDRESS_LOW  0x00C28001
DECL|macro|FLOW_CONTROL_ADDRESS_HIGH
mdefine_line|#define FLOW_CONTROL_ADDRESS_HIGH 0x00000100
DECL|macro|FLOW_CONTROL_TYPE
mdefine_line|#define FLOW_CONTROL_TYPE         0x8808
multiline_comment|/* The historical defaults for the flow control values are given below. */
DECL|macro|FC_DEFAULT_HI_THRESH
mdefine_line|#define FC_DEFAULT_HI_THRESH        (0x8000)    /* 32KB */
DECL|macro|FC_DEFAULT_LO_THRESH
mdefine_line|#define FC_DEFAULT_LO_THRESH        (0x4000)    /* 16KB */
DECL|macro|FC_DEFAULT_TX_TIMER
mdefine_line|#define FC_DEFAULT_TX_TIMER         (0x100)     /* ~130 us */
multiline_comment|/* PCIX Config space */
DECL|macro|PCIX_COMMAND_REGISTER
mdefine_line|#define PCIX_COMMAND_REGISTER    0xE6
DECL|macro|PCIX_STATUS_REGISTER_LO
mdefine_line|#define PCIX_STATUS_REGISTER_LO  0xE8
DECL|macro|PCIX_STATUS_REGISTER_HI
mdefine_line|#define PCIX_STATUS_REGISTER_HI  0xEA
DECL|macro|PCIX_COMMAND_MMRBC_MASK
mdefine_line|#define PCIX_COMMAND_MMRBC_MASK      0x000C
DECL|macro|PCIX_COMMAND_MMRBC_SHIFT
mdefine_line|#define PCIX_COMMAND_MMRBC_SHIFT     0x2
DECL|macro|PCIX_STATUS_HI_MMRBC_MASK
mdefine_line|#define PCIX_STATUS_HI_MMRBC_MASK    0x0060
DECL|macro|PCIX_STATUS_HI_MMRBC_SHIFT
mdefine_line|#define PCIX_STATUS_HI_MMRBC_SHIFT   0x5
multiline_comment|/* The number of bits that we need to shift right to move the &quot;pause&quot;&n; * bits from the EEPROM (bits 13:12) to the &quot;pause&quot; (bits 8:7) field&n; * in the TXCW register &n; */
DECL|macro|PAUSE_SHIFT
mdefine_line|#define PAUSE_SHIFT 5
multiline_comment|/* The number of bits that we need to shift left to move the &quot;SWDPIO&quot;&n; * bits from the EEPROM (bits 8:5) to the &quot;SWDPIO&quot; (bits 25:22) field&n; * in the CTRL register &n; */
DECL|macro|SWDPIO_SHIFT
mdefine_line|#define SWDPIO_SHIFT 17
multiline_comment|/* The number of bits that we need to shift left to move the &quot;SWDPIO_EXT&quot;&n; * bits from the EEPROM word F (bits 7:4) to the bits 11:8 of The&n; * Extended CTRL register.&n; * in the CTRL register &n; */
DECL|macro|SWDPIO__EXT_SHIFT
mdefine_line|#define SWDPIO__EXT_SHIFT 4
multiline_comment|/* The number of bits that we need to shift left to move the &quot;ILOS&quot;&n; * bit from the EEPROM (bit 4) to the &quot;ILOS&quot; (bit 7) field&n; * in the CTRL register &n; */
DECL|macro|ILOS_SHIFT
mdefine_line|#define ILOS_SHIFT  3
DECL|macro|RECEIVE_BUFFER_ALIGN_SIZE
mdefine_line|#define RECEIVE_BUFFER_ALIGN_SIZE  (256)
multiline_comment|/* The number of milliseconds we wait for auto-negotiation to complete */
DECL|macro|LINK_UP_TIMEOUT
mdefine_line|#define LINK_UP_TIMEOUT             500
DECL|macro|E1000_TX_BUFFER_SIZE
mdefine_line|#define E1000_TX_BUFFER_SIZE ((uint32_t)1514)
multiline_comment|/* The carrier extension symbol, as received by the NIC. */
DECL|macro|CARRIER_EXTENSION
mdefine_line|#define CARRIER_EXTENSION   0x0F
multiline_comment|/* TBI_ACCEPT macro definition:&n; *&n; * This macro requires:&n; *      adapter = a pointer to struct e1000_hw &n; *      status = the 8 bit status field of the RX descriptor with EOP set&n; *      error = the 8 bit error field of the RX descriptor with EOP set&n; *      length = the sum of all the length fields of the RX descriptors that&n; *               make up the current frame&n; *      last_byte = the last byte of the frame DMAed by the hardware&n; *      max_frame_length = the maximum frame length we want to accept.&n; *      min_frame_length = the minimum frame length we want to accept.&n; *&n; * This macro is a conditional that should be used in the interrupt &n; * handler&squot;s Rx processing routine when RxErrors have been detected.&n; *&n; * Typical use:&n; *  ...&n; *  if (TBI_ACCEPT) {&n; *      accept_frame = TRUE;&n; *      e1000_tbi_adjust_stats(adapter, MacAddress);&n; *      frame_length--;&n; *  } else {&n; *      accept_frame = FALSE;&n; *  }&n; *  ...&n; */
DECL|macro|TBI_ACCEPT
mdefine_line|#define TBI_ACCEPT(adapter, status, errors, length, last_byte) &bslash;&n;    ((adapter)-&gt;tbi_compatibility_on &amp;&amp; &bslash;&n;     (((errors) &amp; E1000_RXD_ERR_FRAME_ERR_MASK) == E1000_RXD_ERR_CE) &amp;&amp; &bslash;&n;     ((last_byte) == CARRIER_EXTENSION) &amp;&amp; &bslash;&n;     (((status) &amp; E1000_RXD_STAT_VP) ? &bslash;&n;          (((length) &gt; ((adapter)-&gt;min_frame_size - VLAN_TAG_SIZE)) &amp;&amp; &bslash;&n;           ((length) &lt;= ((adapter)-&gt;max_frame_size + 1))) : &bslash;&n;          (((length) &gt; (adapter)-&gt;min_frame_size) &amp;&amp; &bslash;&n;           ((length) &lt;= ((adapter)-&gt;max_frame_size + VLAN_TAG_SIZE + 1)))))
multiline_comment|/* Structures, enums, and macros for the PHY */
multiline_comment|/* Bit definitions for the Management Data IO (MDIO) and Management Data&n; * Clock (MDC) pins in the Device Control Register.&n; */
DECL|macro|E1000_CTRL_PHY_RESET_DIR
mdefine_line|#define E1000_CTRL_PHY_RESET_DIR  E1000_CTRL_SWDPIO0
DECL|macro|E1000_CTRL_PHY_RESET
mdefine_line|#define E1000_CTRL_PHY_RESET      E1000_CTRL_SWDPIN0
DECL|macro|E1000_CTRL_MDIO_DIR
mdefine_line|#define E1000_CTRL_MDIO_DIR       E1000_CTRL_SWDPIO2
DECL|macro|E1000_CTRL_MDIO
mdefine_line|#define E1000_CTRL_MDIO           E1000_CTRL_SWDPIN2
DECL|macro|E1000_CTRL_MDC_DIR
mdefine_line|#define E1000_CTRL_MDC_DIR        E1000_CTRL_SWDPIO3
DECL|macro|E1000_CTRL_MDC
mdefine_line|#define E1000_CTRL_MDC            E1000_CTRL_SWDPIN3
DECL|macro|E1000_CTRL_PHY_RESET_DIR4
mdefine_line|#define E1000_CTRL_PHY_RESET_DIR4 E1000_CTRL_EXT_SDP4_DIR
DECL|macro|E1000_CTRL_PHY_RESET4
mdefine_line|#define E1000_CTRL_PHY_RESET4     E1000_CTRL_EXT_SDP4_DATA
multiline_comment|/* PHY 1000 MII Register/Bit Definitions */
multiline_comment|/* PHY Registers defined by IEEE */
DECL|macro|PHY_CTRL
mdefine_line|#define PHY_CTRL         0x00 /* Control Register */
DECL|macro|PHY_STATUS
mdefine_line|#define PHY_STATUS       0x01 /* Status Regiser */
DECL|macro|PHY_ID1
mdefine_line|#define PHY_ID1          0x02 /* Phy Id Reg (word 1) */
DECL|macro|PHY_ID2
mdefine_line|#define PHY_ID2          0x03 /* Phy Id Reg (word 2) */
DECL|macro|PHY_AUTONEG_ADV
mdefine_line|#define PHY_AUTONEG_ADV  0x04 /* Autoneg Advertisement */
DECL|macro|PHY_LP_ABILITY
mdefine_line|#define PHY_LP_ABILITY   0x05 /* Link Partner Ability (Base Page) */
DECL|macro|PHY_AUTONEG_EXP
mdefine_line|#define PHY_AUTONEG_EXP  0x06 /* Autoneg Expansion Reg */
DECL|macro|PHY_NEXT_PAGE_TX
mdefine_line|#define PHY_NEXT_PAGE_TX 0x07 /* Next Page TX */
DECL|macro|PHY_LP_NEXT_PAGE
mdefine_line|#define PHY_LP_NEXT_PAGE 0x08 /* Link Partner Next Page */
DECL|macro|PHY_1000T_CTRL
mdefine_line|#define PHY_1000T_CTRL   0x09 /* 1000Base-T Control Reg */
DECL|macro|PHY_1000T_STATUS
mdefine_line|#define PHY_1000T_STATUS 0x0A /* 1000Base-T Status Reg */
DECL|macro|PHY_EXT_STATUS
mdefine_line|#define PHY_EXT_STATUS   0x0F /* Extended Status Reg */
multiline_comment|/* M88E1000 Specific Registers */
DECL|macro|M88E1000_PHY_SPEC_CTRL
mdefine_line|#define M88E1000_PHY_SPEC_CTRL     0x10  /* PHY Specific Control Register */
DECL|macro|M88E1000_PHY_SPEC_STATUS
mdefine_line|#define M88E1000_PHY_SPEC_STATUS   0x11  /* PHY Specific Status Register */
DECL|macro|M88E1000_INT_ENABLE
mdefine_line|#define M88E1000_INT_ENABLE        0x12  /* Interrupt Enable Register */
DECL|macro|M88E1000_INT_STATUS
mdefine_line|#define M88E1000_INT_STATUS        0x13  /* Interrupt Status Register */
DECL|macro|M88E1000_EXT_PHY_SPEC_CTRL
mdefine_line|#define M88E1000_EXT_PHY_SPEC_CTRL 0x14  /* Extended PHY Specific Control */
DECL|macro|M88E1000_RX_ERR_CNTR
mdefine_line|#define M88E1000_RX_ERR_CNTR       0x15  /* Receive Error Counter */
DECL|macro|MAX_PHY_REG_ADDRESS
mdefine_line|#define MAX_PHY_REG_ADDRESS 0x1F        /* 5 bit address bus (0-0x1F) */
multiline_comment|/* PHY Control Register */
DECL|macro|MII_CR_SPEED_SELECT_MSB
mdefine_line|#define MII_CR_SPEED_SELECT_MSB 0x0040  /* bits 6,13: 10=1000, 01=100, 00=10 */
DECL|macro|MII_CR_COLL_TEST_ENABLE
mdefine_line|#define MII_CR_COLL_TEST_ENABLE 0x0080  /* Collision test enable */
DECL|macro|MII_CR_FULL_DUPLEX
mdefine_line|#define MII_CR_FULL_DUPLEX      0x0100  /* FDX =1, half duplex =0 */
DECL|macro|MII_CR_RESTART_AUTO_NEG
mdefine_line|#define MII_CR_RESTART_AUTO_NEG 0x0200  /* Restart auto negotiation */
DECL|macro|MII_CR_ISOLATE
mdefine_line|#define MII_CR_ISOLATE          0x0400  /* Isolate PHY from MII */
DECL|macro|MII_CR_POWER_DOWN
mdefine_line|#define MII_CR_POWER_DOWN       0x0800  /* Power down */
DECL|macro|MII_CR_AUTO_NEG_EN
mdefine_line|#define MII_CR_AUTO_NEG_EN      0x1000  /* Auto Neg Enable */
DECL|macro|MII_CR_SPEED_SELECT_LSB
mdefine_line|#define MII_CR_SPEED_SELECT_LSB 0x2000  /* bits 6,13: 10=1000, 01=100, 00=10 */
DECL|macro|MII_CR_LOOPBACK
mdefine_line|#define MII_CR_LOOPBACK         0x4000  /* 0 = normal, 1 = loopback */
DECL|macro|MII_CR_RESET
mdefine_line|#define MII_CR_RESET            0x8000  /* 0 = normal, 1 = PHY reset */
multiline_comment|/* PHY Status Register */
DECL|macro|MII_SR_EXTENDED_CAPS
mdefine_line|#define MII_SR_EXTENDED_CAPS     0x0001 /* Extended register capabilities */
DECL|macro|MII_SR_JABBER_DETECT
mdefine_line|#define MII_SR_JABBER_DETECT     0x0002 /* Jabber Detected */
DECL|macro|MII_SR_LINK_STATUS
mdefine_line|#define MII_SR_LINK_STATUS       0x0004 /* Link Status 1 = link */
DECL|macro|MII_SR_AUTONEG_CAPS
mdefine_line|#define MII_SR_AUTONEG_CAPS      0x0008 /* Auto Neg Capable */
DECL|macro|MII_SR_REMOTE_FAULT
mdefine_line|#define MII_SR_REMOTE_FAULT      0x0010 /* Remote Fault Detect */
DECL|macro|MII_SR_AUTONEG_COMPLETE
mdefine_line|#define MII_SR_AUTONEG_COMPLETE  0x0020 /* Auto Neg Complete */
DECL|macro|MII_SR_PREAMBLE_SUPPRESS
mdefine_line|#define MII_SR_PREAMBLE_SUPPRESS 0x0040 /* Preamble may be suppressed */
DECL|macro|MII_SR_EXTENDED_STATUS
mdefine_line|#define MII_SR_EXTENDED_STATUS   0x0100 /* Ext. status info in Reg 0x0F */
DECL|macro|MII_SR_100T2_HD_CAPS
mdefine_line|#define MII_SR_100T2_HD_CAPS     0x0200 /* 100T2 Half Duplex Capable */
DECL|macro|MII_SR_100T2_FD_CAPS
mdefine_line|#define MII_SR_100T2_FD_CAPS     0x0400 /* 100T2 Full Duplex Capable */
DECL|macro|MII_SR_10T_HD_CAPS
mdefine_line|#define MII_SR_10T_HD_CAPS       0x0800 /* 10T   Half Duplex Capable */
DECL|macro|MII_SR_10T_FD_CAPS
mdefine_line|#define MII_SR_10T_FD_CAPS       0x1000 /* 10T   Full Duplex Capable */
DECL|macro|MII_SR_100X_HD_CAPS
mdefine_line|#define MII_SR_100X_HD_CAPS      0x2000 /* 100X  Half Duplex Capable */
DECL|macro|MII_SR_100X_FD_CAPS
mdefine_line|#define MII_SR_100X_FD_CAPS      0x4000 /* 100X  Full Duplex Capable */
DECL|macro|MII_SR_100T4_CAPS
mdefine_line|#define MII_SR_100T4_CAPS        0x8000 /* 100T4 Capable */
multiline_comment|/* Autoneg Advertisement Register */
DECL|macro|NWAY_AR_SELECTOR_FIELD
mdefine_line|#define NWAY_AR_SELECTOR_FIELD 0x0001   /* indicates IEEE 802.3 CSMA/CD */
DECL|macro|NWAY_AR_10T_HD_CAPS
mdefine_line|#define NWAY_AR_10T_HD_CAPS    0x0020   /* 10T   Half Duplex Capable */
DECL|macro|NWAY_AR_10T_FD_CAPS
mdefine_line|#define NWAY_AR_10T_FD_CAPS    0x0040   /* 10T   Full Duplex Capable */
DECL|macro|NWAY_AR_100TX_HD_CAPS
mdefine_line|#define NWAY_AR_100TX_HD_CAPS  0x0080   /* 100TX Half Duplex Capable */
DECL|macro|NWAY_AR_100TX_FD_CAPS
mdefine_line|#define NWAY_AR_100TX_FD_CAPS  0x0100   /* 100TX Full Duplex Capable */
DECL|macro|NWAY_AR_100T4_CAPS
mdefine_line|#define NWAY_AR_100T4_CAPS     0x0200   /* 100T4 Capable */
DECL|macro|NWAY_AR_PAUSE
mdefine_line|#define NWAY_AR_PAUSE          0x0400   /* Pause operation desired */
DECL|macro|NWAY_AR_ASM_DIR
mdefine_line|#define NWAY_AR_ASM_DIR        0x0800   /* Asymmetric Pause Direction bit */
DECL|macro|NWAY_AR_REMOTE_FAULT
mdefine_line|#define NWAY_AR_REMOTE_FAULT   0x2000   /* Remote Fault detected */
DECL|macro|NWAY_AR_NEXT_PAGE
mdefine_line|#define NWAY_AR_NEXT_PAGE      0x8000   /* Next Page ability supported */
multiline_comment|/* Link Partner Ability Register (Base Page) */
DECL|macro|NWAY_LPAR_SELECTOR_FIELD
mdefine_line|#define NWAY_LPAR_SELECTOR_FIELD 0x0000 /* LP protocol selector field */
DECL|macro|NWAY_LPAR_10T_HD_CAPS
mdefine_line|#define NWAY_LPAR_10T_HD_CAPS    0x0020 /* LP is 10T   Half Duplex Capable */
DECL|macro|NWAY_LPAR_10T_FD_CAPS
mdefine_line|#define NWAY_LPAR_10T_FD_CAPS    0x0040 /* LP is 10T   Full Duplex Capable */
DECL|macro|NWAY_LPAR_100TX_HD_CAPS
mdefine_line|#define NWAY_LPAR_100TX_HD_CAPS  0x0080 /* LP is 100TX Half Duplex Capable */
DECL|macro|NWAY_LPAR_100TX_FD_CAPS
mdefine_line|#define NWAY_LPAR_100TX_FD_CAPS  0x0100 /* LP is 100TX Full Duplex Capable */
DECL|macro|NWAY_LPAR_100T4_CAPS
mdefine_line|#define NWAY_LPAR_100T4_CAPS     0x0200 /* LP is 100T4 Capable */
DECL|macro|NWAY_LPAR_PAUSE
mdefine_line|#define NWAY_LPAR_PAUSE          0x0400 /* LP Pause operation desired */
DECL|macro|NWAY_LPAR_ASM_DIR
mdefine_line|#define NWAY_LPAR_ASM_DIR        0x0800 /* LP Asymmetric Pause Direction bit */
DECL|macro|NWAY_LPAR_REMOTE_FAULT
mdefine_line|#define NWAY_LPAR_REMOTE_FAULT   0x2000 /* LP has detected Remote Fault */
DECL|macro|NWAY_LPAR_ACKNOWLEDGE
mdefine_line|#define NWAY_LPAR_ACKNOWLEDGE    0x4000 /* LP has rx&squot;d link code word */
DECL|macro|NWAY_LPAR_NEXT_PAGE
mdefine_line|#define NWAY_LPAR_NEXT_PAGE      0x8000 /* Next Page ability supported */
multiline_comment|/* Autoneg Expansion Register */
DECL|macro|NWAY_ER_LP_NWAY_CAPS
mdefine_line|#define NWAY_ER_LP_NWAY_CAPS      0x0001 /* LP has Auto Neg Capability */
DECL|macro|NWAY_ER_PAGE_RXD
mdefine_line|#define NWAY_ER_PAGE_RXD          0x0002 /* LP is 10T   Half Duplex Capable */
DECL|macro|NWAY_ER_NEXT_PAGE_CAPS
mdefine_line|#define NWAY_ER_NEXT_PAGE_CAPS    0x0004 /* LP is 10T   Full Duplex Capable */
DECL|macro|NWAY_ER_LP_NEXT_PAGE_CAPS
mdefine_line|#define NWAY_ER_LP_NEXT_PAGE_CAPS 0x0008 /* LP is 100TX Half Duplex Capable */
DECL|macro|NWAY_ER_PAR_DETECT_FAULT
mdefine_line|#define NWAY_ER_PAR_DETECT_FAULT  0x0100 /* LP is 100TX Full Duplex Capable */
multiline_comment|/* Next Page TX Register */
DECL|macro|NPTX_MSG_CODE_FIELD
mdefine_line|#define NPTX_MSG_CODE_FIELD 0x0001 /* NP msg code or unformatted data */
DECL|macro|NPTX_TOGGLE
mdefine_line|#define NPTX_TOGGLE         0x0800 /* Toggles between exchanges&n;                                    * of different NP&n;                                    */
DECL|macro|NPTX_ACKNOWLDGE2
mdefine_line|#define NPTX_ACKNOWLDGE2    0x1000 /* 1 = will comply with msg&n;                                    * 0 = cannot comply with msg&n;                                    */
DECL|macro|NPTX_MSG_PAGE
mdefine_line|#define NPTX_MSG_PAGE       0x2000 /* formatted(1)/unformatted(0) pg */
DECL|macro|NPTX_NEXT_PAGE
mdefine_line|#define NPTX_NEXT_PAGE      0x8000 /* 1 = addition NP will follow &n;                                    * 0 = sending last NP&n;                                    */
multiline_comment|/* Link Partner Next Page Register */
DECL|macro|LP_RNPR_MSG_CODE_FIELD
mdefine_line|#define LP_RNPR_MSG_CODE_FIELD 0x0001 /* NP msg code or unformatted data */
DECL|macro|LP_RNPR_TOGGLE
mdefine_line|#define LP_RNPR_TOGGLE         0x0800 /* Toggles between exchanges&n;                                       * of different NP&n;                                       */
DECL|macro|LP_RNPR_ACKNOWLDGE2
mdefine_line|#define LP_RNPR_ACKNOWLDGE2    0x1000 /* 1 = will comply with msg &n;                                       * 0 = cannot comply with msg&n;                                       */
DECL|macro|LP_RNPR_MSG_PAGE
mdefine_line|#define LP_RNPR_MSG_PAGE       0x2000  /* formatted(1)/unformatted(0) pg */
DECL|macro|LP_RNPR_ACKNOWLDGE
mdefine_line|#define LP_RNPR_ACKNOWLDGE     0x4000  /* 1 = ACK / 0 = NO ACK */
DECL|macro|LP_RNPR_NEXT_PAGE
mdefine_line|#define LP_RNPR_NEXT_PAGE      0x8000  /* 1 = addition NP will follow&n;                                        * 0 = sending last NP &n;                                        */
multiline_comment|/* 1000BASE-T Control Register */
DECL|macro|CR_1000T_ASYM_PAUSE
mdefine_line|#define CR_1000T_ASYM_PAUSE      0x0080 /* Advertise asymmetric pause bit */
DECL|macro|CR_1000T_HD_CAPS
mdefine_line|#define CR_1000T_HD_CAPS         0x0100 /* Advertise 1000T HD capability */
DECL|macro|CR_1000T_FD_CAPS
mdefine_line|#define CR_1000T_FD_CAPS         0x0200 /* Advertise 1000T FD capability  */
DECL|macro|CR_1000T_REPEATER_DTE
mdefine_line|#define CR_1000T_REPEATER_DTE    0x0400 /* 1=Repeater/switch device port */
multiline_comment|/* 0=DTE device */
DECL|macro|CR_1000T_MS_VALUE
mdefine_line|#define CR_1000T_MS_VALUE        0x0800 /* 1=Configure PHY as Master */
multiline_comment|/* 0=Configure PHY as Slave */
DECL|macro|CR_1000T_MS_ENABLE
mdefine_line|#define CR_1000T_MS_ENABLE       0x1000 /* 1=Master/Slave manual config value */
multiline_comment|/* 0=Automatic Master/Slave config */
DECL|macro|CR_1000T_TEST_MODE_NORMAL
mdefine_line|#define CR_1000T_TEST_MODE_NORMAL 0x0000 /* Normal Operation */
DECL|macro|CR_1000T_TEST_MODE_1
mdefine_line|#define CR_1000T_TEST_MODE_1     0x2000 /* Transmit Waveform test */
DECL|macro|CR_1000T_TEST_MODE_2
mdefine_line|#define CR_1000T_TEST_MODE_2     0x4000 /* Master Transmit Jitter test */
DECL|macro|CR_1000T_TEST_MODE_3
mdefine_line|#define CR_1000T_TEST_MODE_3     0x6000 /* Slave Transmit Jitter test */
DECL|macro|CR_1000T_TEST_MODE_4
mdefine_line|#define CR_1000T_TEST_MODE_4     0x8000 /* Transmitter Distortion test */
multiline_comment|/* 1000BASE-T Status Register */
DECL|macro|SR_1000T_IDLE_ERROR_CNT
mdefine_line|#define SR_1000T_IDLE_ERROR_CNT   0x00FF /* Num idle errors since last read */
DECL|macro|SR_1000T_ASYM_PAUSE_DIR
mdefine_line|#define SR_1000T_ASYM_PAUSE_DIR   0x0100 /* LP asymmetric pause direction bit */
DECL|macro|SR_1000T_LP_HD_CAPS
mdefine_line|#define SR_1000T_LP_HD_CAPS       0x0400 /* LP is 1000T HD capable */
DECL|macro|SR_1000T_LP_FD_CAPS
mdefine_line|#define SR_1000T_LP_FD_CAPS       0x0800 /* LP is 1000T FD capable */
DECL|macro|SR_1000T_REMOTE_RX_STATUS
mdefine_line|#define SR_1000T_REMOTE_RX_STATUS 0x1000 /* Remote receiver OK */
DECL|macro|SR_1000T_LOCAL_RX_STATUS
mdefine_line|#define SR_1000T_LOCAL_RX_STATUS  0x2000 /* Local receiver OK */
DECL|macro|SR_1000T_MS_CONFIG_RES
mdefine_line|#define SR_1000T_MS_CONFIG_RES    0x4000 /* 1=Local TX is Master, 0=Slave */
DECL|macro|SR_1000T_MS_CONFIG_FAULT
mdefine_line|#define SR_1000T_MS_CONFIG_FAULT  0x8000 /* Master/Slave config fault */
DECL|macro|SR_1000T_REMOTE_RX_STATUS_SHIFT
mdefine_line|#define SR_1000T_REMOTE_RX_STATUS_SHIFT 12
DECL|macro|SR_1000T_LOCAL_RX_STATUS_SHIFT
mdefine_line|#define SR_1000T_LOCAL_RX_STATUS_SHIFT  13
multiline_comment|/* Extended Status Register */
DECL|macro|IEEE_ESR_1000T_HD_CAPS
mdefine_line|#define IEEE_ESR_1000T_HD_CAPS 0x1000 /* 1000T HD capable */
DECL|macro|IEEE_ESR_1000T_FD_CAPS
mdefine_line|#define IEEE_ESR_1000T_FD_CAPS 0x2000 /* 1000T FD capable */
DECL|macro|IEEE_ESR_1000X_HD_CAPS
mdefine_line|#define IEEE_ESR_1000X_HD_CAPS 0x4000 /* 1000X HD capable */
DECL|macro|IEEE_ESR_1000X_FD_CAPS
mdefine_line|#define IEEE_ESR_1000X_FD_CAPS 0x8000 /* 1000X FD capable */
DECL|macro|PHY_TX_POLARITY_MASK
mdefine_line|#define PHY_TX_POLARITY_MASK   0x0100 /* register 10h bit 8 (polarity bit) */
DECL|macro|PHY_TX_NORMAL_POLARITY
mdefine_line|#define PHY_TX_NORMAL_POLARITY 0      /* register 10h bit 8 (normal polarity) */
DECL|macro|AUTO_POLARITY_DISABLE
mdefine_line|#define AUTO_POLARITY_DISABLE  0x0010 /* register 11h bit 4 */
multiline_comment|/* (0=enable, 1=disable) */
multiline_comment|/* M88E1000 PHY Specific Control Register */
DECL|macro|M88E1000_PSCR_JABBER_DISABLE
mdefine_line|#define M88E1000_PSCR_JABBER_DISABLE    0x0001 /* 1=Jabber Function disabled */
DECL|macro|M88E1000_PSCR_POLARITY_REVERSAL
mdefine_line|#define M88E1000_PSCR_POLARITY_REVERSAL 0x0002 /* 1=Polarity Reversal enabled */
DECL|macro|M88E1000_PSCR_SQE_TEST
mdefine_line|#define M88E1000_PSCR_SQE_TEST          0x0004 /* 1=SQE Test enabled */
DECL|macro|M88E1000_PSCR_CLK125_DISABLE
mdefine_line|#define M88E1000_PSCR_CLK125_DISABLE    0x0010 /* 1=CLK125 low, &n;                                                * 0=CLK125 toggling&n;                                                */
DECL|macro|M88E1000_PSCR_MDI_MANUAL_MODE
mdefine_line|#define M88E1000_PSCR_MDI_MANUAL_MODE  0x0000  /* MDI Crossover Mode bits 6:5 */
multiline_comment|/* Manual MDI configuration */
DECL|macro|M88E1000_PSCR_MDIX_MANUAL_MODE
mdefine_line|#define M88E1000_PSCR_MDIX_MANUAL_MODE 0x0020  /* Manual MDIX configuration */
DECL|macro|M88E1000_PSCR_AUTO_X_1000T
mdefine_line|#define M88E1000_PSCR_AUTO_X_1000T     0x0040  /* 1000BASE-T: Auto crossover,&n;                                                *  100BASE-TX/10BASE-T: &n;                                                *  MDI Mode&n;                                                */
DECL|macro|M88E1000_PSCR_AUTO_X_MODE
mdefine_line|#define M88E1000_PSCR_AUTO_X_MODE      0x0060  /* Auto crossover enabled &n;                                                * all speeds. &n;                                                */
DECL|macro|M88E1000_PSCR_10BT_EXT_DIST_ENABLE
mdefine_line|#define M88E1000_PSCR_10BT_EXT_DIST_ENABLE 0x0080 
multiline_comment|/* 1=Enable Extended 10BASE-T distance&n;                                         * (Lower 10BASE-T RX Threshold)&n;                                         * 0=Normal 10BASE-T RX Threshold */
DECL|macro|M88E1000_PSCR_MII_5BIT_ENABLE
mdefine_line|#define M88E1000_PSCR_MII_5BIT_ENABLE      0x0100
multiline_comment|/* 1=5-Bit interface in 100BASE-TX&n;                                         * 0=MII interface in 100BASE-TX */
DECL|macro|M88E1000_PSCR_SCRAMBLER_DISABLE
mdefine_line|#define M88E1000_PSCR_SCRAMBLER_DISABLE    0x0200 /* 1=Scrambler disable */
DECL|macro|M88E1000_PSCR_FORCE_LINK_GOOD
mdefine_line|#define M88E1000_PSCR_FORCE_LINK_GOOD      0x0400 /* 1=Force link good */
DECL|macro|M88E1000_PSCR_ASSERT_CRS_ON_TX
mdefine_line|#define M88E1000_PSCR_ASSERT_CRS_ON_TX     0x0800 /* 1=Assert CRS on Transmit */
DECL|macro|M88E1000_PSCR_POLARITY_REVERSAL_SHIFT
mdefine_line|#define M88E1000_PSCR_POLARITY_REVERSAL_SHIFT    1
DECL|macro|M88E1000_PSCR_AUTO_X_MODE_SHIFT
mdefine_line|#define M88E1000_PSCR_AUTO_X_MODE_SHIFT          5
DECL|macro|M88E1000_PSCR_10BT_EXT_DIST_ENABLE_SHIFT
mdefine_line|#define M88E1000_PSCR_10BT_EXT_DIST_ENABLE_SHIFT 7
multiline_comment|/* M88E1000 PHY Specific Status Register */
DECL|macro|M88E1000_PSSR_JABBER
mdefine_line|#define M88E1000_PSSR_JABBER             0x0001 /* 1=Jabber */
DECL|macro|M88E1000_PSSR_REV_POLARITY
mdefine_line|#define M88E1000_PSSR_REV_POLARITY       0x0002 /* 1=Polarity reversed */
DECL|macro|M88E1000_PSSR_MDIX
mdefine_line|#define M88E1000_PSSR_MDIX               0x0040 /* 1=MDIX; 0=MDI */
DECL|macro|M88E1000_PSSR_CABLE_LENGTH
mdefine_line|#define M88E1000_PSSR_CABLE_LENGTH       0x0380 /* 0=&lt;50M;1=50-80M;2=80-110M;&n;                                            * 3=110-140M;4=&gt;140M */
DECL|macro|M88E1000_PSSR_LINK
mdefine_line|#define M88E1000_PSSR_LINK               0x0400 /* 1=Link up, 0=Link down */
DECL|macro|M88E1000_PSSR_SPD_DPLX_RESOLVED
mdefine_line|#define M88E1000_PSSR_SPD_DPLX_RESOLVED  0x0800 /* 1=Speed &amp; Duplex resolved */
DECL|macro|M88E1000_PSSR_PAGE_RCVD
mdefine_line|#define M88E1000_PSSR_PAGE_RCVD          0x1000 /* 1=Page received */
DECL|macro|M88E1000_PSSR_DPLX
mdefine_line|#define M88E1000_PSSR_DPLX               0x2000 /* 1=Duplex 0=Half Duplex */
DECL|macro|M88E1000_PSSR_SPEED
mdefine_line|#define M88E1000_PSSR_SPEED              0xC000 /* Speed, bits 14:15 */
DECL|macro|M88E1000_PSSR_10MBS
mdefine_line|#define M88E1000_PSSR_10MBS              0x0000 /* 00=10Mbs */
DECL|macro|M88E1000_PSSR_100MBS
mdefine_line|#define M88E1000_PSSR_100MBS             0x4000 /* 01=100Mbs */
DECL|macro|M88E1000_PSSR_1000MBS
mdefine_line|#define M88E1000_PSSR_1000MBS            0x8000 /* 10=1000Mbs */
DECL|macro|M88E1000_PSSR_REV_POLARITY_SHIFT
mdefine_line|#define M88E1000_PSSR_REV_POLARITY_SHIFT 1
DECL|macro|M88E1000_PSSR_MDIX_SHIFT
mdefine_line|#define M88E1000_PSSR_MDIX_SHIFT         6
DECL|macro|M88E1000_PSSR_CABLE_LENGTH_SHIFT
mdefine_line|#define M88E1000_PSSR_CABLE_LENGTH_SHIFT 7
multiline_comment|/* M88E1000 Extended PHY Specific Control Register */
DECL|macro|M88E1000_EPSCR_FIBER_LOOPBACK
mdefine_line|#define M88E1000_EPSCR_FIBER_LOOPBACK 0x4000 /* 1=Fiber loopback */
DECL|macro|M88E1000_EPSCR_DOWN_NO_IDLE
mdefine_line|#define M88E1000_EPSCR_DOWN_NO_IDLE   0x8000 /* 1=Lost lock detect enabled.&n;                                              * Will assert lost lock and bring&n;                                              * link down if idle not seen&n;                                              * within 1ms in 1000BASE-T &n;                                              */
multiline_comment|/* Number of times we will attempt to autonegotiate before downshifting if we&n; * are the master */
DECL|macro|M88E1000_EPSCR_MASTER_DOWNSHIFT_MASK
mdefine_line|#define M88E1000_EPSCR_MASTER_DOWNSHIFT_MASK 0x0C00
DECL|macro|M88E1000_EPSCR_MASTER_DOWNSHIFT_1X
mdefine_line|#define M88E1000_EPSCR_MASTER_DOWNSHIFT_1X   0x0000    
DECL|macro|M88E1000_EPSCR_MASTER_DOWNSHIFT_2X
mdefine_line|#define M88E1000_EPSCR_MASTER_DOWNSHIFT_2X   0x0400
DECL|macro|M88E1000_EPSCR_MASTER_DOWNSHIFT_3X
mdefine_line|#define M88E1000_EPSCR_MASTER_DOWNSHIFT_3X   0x0800
DECL|macro|M88E1000_EPSCR_MASTER_DOWNSHIFT_4X
mdefine_line|#define M88E1000_EPSCR_MASTER_DOWNSHIFT_4X   0x0C00
multiline_comment|/* Number of times we will attempt to autonegotiate before downshifting if we&n; * are the slave */
DECL|macro|M88E1000_EPSCR_SLAVE_DOWNSHIFT_MASK
mdefine_line|#define M88E1000_EPSCR_SLAVE_DOWNSHIFT_MASK  0x0300
DECL|macro|M88E1000_EPSCR_SLAVE_DOWNSHIFT_DIS
mdefine_line|#define M88E1000_EPSCR_SLAVE_DOWNSHIFT_DIS   0x0000
DECL|macro|M88E1000_EPSCR_SLAVE_DOWNSHIFT_1X
mdefine_line|#define M88E1000_EPSCR_SLAVE_DOWNSHIFT_1X    0x0100
DECL|macro|M88E1000_EPSCR_SLAVE_DOWNSHIFT_2X
mdefine_line|#define M88E1000_EPSCR_SLAVE_DOWNSHIFT_2X    0x0200
DECL|macro|M88E1000_EPSCR_SLAVE_DOWNSHIFT_3X
mdefine_line|#define M88E1000_EPSCR_SLAVE_DOWNSHIFT_3X    0x0300
DECL|macro|M88E1000_EPSCR_TX_CLK_2_5
mdefine_line|#define M88E1000_EPSCR_TX_CLK_2_5     0x0060 /* 2.5 MHz TX_CLK */
DECL|macro|M88E1000_EPSCR_TX_CLK_25
mdefine_line|#define M88E1000_EPSCR_TX_CLK_25      0x0070 /* 25  MHz TX_CLK */
DECL|macro|M88E1000_EPSCR_TX_CLK_0
mdefine_line|#define M88E1000_EPSCR_TX_CLK_0       0x0000 /* NO  TX_CLK */
multiline_comment|/* Bit definitions for valid PHY IDs. */
DECL|macro|M88E1000_E_PHY_ID
mdefine_line|#define M88E1000_E_PHY_ID  0x01410C50
DECL|macro|M88E1000_I_PHY_ID
mdefine_line|#define M88E1000_I_PHY_ID  0x01410C30
DECL|macro|M88E1011_I_PHY_ID
mdefine_line|#define M88E1011_I_PHY_ID  0x01410C20
DECL|macro|M88E1000_12_PHY_ID
mdefine_line|#define M88E1000_12_PHY_ID M88E1000_E_PHY_ID
DECL|macro|M88E1000_14_PHY_ID
mdefine_line|#define M88E1000_14_PHY_ID M88E1000_E_PHY_ID
multiline_comment|/* Miscellaneous PHY bit definitions. */
DECL|macro|PHY_PREAMBLE
mdefine_line|#define PHY_PREAMBLE        0xFFFFFFFF
DECL|macro|PHY_SOF
mdefine_line|#define PHY_SOF             0x01
DECL|macro|PHY_OP_READ
mdefine_line|#define PHY_OP_READ         0x02
DECL|macro|PHY_OP_WRITE
mdefine_line|#define PHY_OP_WRITE        0x01
DECL|macro|PHY_TURNAROUND
mdefine_line|#define PHY_TURNAROUND      0x02
DECL|macro|PHY_PREAMBLE_SIZE
mdefine_line|#define PHY_PREAMBLE_SIZE   32
DECL|macro|MII_CR_SPEED_1000
mdefine_line|#define MII_CR_SPEED_1000   0x0040
DECL|macro|MII_CR_SPEED_100
mdefine_line|#define MII_CR_SPEED_100    0x2000
DECL|macro|MII_CR_SPEED_10
mdefine_line|#define MII_CR_SPEED_10     0x0000
DECL|macro|E1000_PHY_ADDRESS
mdefine_line|#define E1000_PHY_ADDRESS   0x01
DECL|macro|PHY_AUTO_NEG_TIME
mdefine_line|#define PHY_AUTO_NEG_TIME   45  /* 4.5 Seconds */
DECL|macro|PHY_FORCE_TIME
mdefine_line|#define PHY_FORCE_TIME      20  /* 2.0 Seconds */
DECL|macro|PHY_REVISION_MASK
mdefine_line|#define PHY_REVISION_MASK   0xFFFFFFF0
DECL|macro|DEVICE_SPEED_MASK
mdefine_line|#define DEVICE_SPEED_MASK   0x00000300  /* Device Ctrl Reg Speed Mask */
DECL|macro|REG4_SPEED_MASK
mdefine_line|#define REG4_SPEED_MASK     0x01E0
DECL|macro|REG9_SPEED_MASK
mdefine_line|#define REG9_SPEED_MASK     0x0300
DECL|macro|ADVERTISE_10_HALF
mdefine_line|#define ADVERTISE_10_HALF   0x0001
DECL|macro|ADVERTISE_10_FULL
mdefine_line|#define ADVERTISE_10_FULL   0x0002
DECL|macro|ADVERTISE_100_HALF
mdefine_line|#define ADVERTISE_100_HALF  0x0004
DECL|macro|ADVERTISE_100_FULL
mdefine_line|#define ADVERTISE_100_FULL  0x0008
DECL|macro|ADVERTISE_1000_HALF
mdefine_line|#define ADVERTISE_1000_HALF 0x0010
DECL|macro|ADVERTISE_1000_FULL
mdefine_line|#define ADVERTISE_1000_FULL 0x0020
DECL|macro|AUTONEG_ADVERTISE_SPEED_DEFAULT
mdefine_line|#define AUTONEG_ADVERTISE_SPEED_DEFAULT 0x002F  /* Everything but 1000-Half */
macro_line|#endif /* _E1000_HW_H_ */
eof
