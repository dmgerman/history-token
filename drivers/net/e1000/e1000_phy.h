multiline_comment|/*******************************************************************************&n;&n;  This software program is available to you under a choice of one of two&n;  licenses. You may choose to be licensed under either the GNU General Public&n;  License (GPL) Version 2, June 1991, available at&n;  http://www.fsf.org/copyleft/gpl.html, or the Intel BSD + Patent License, the&n;  text of which follows:&n;  &n;  Recipient has requested a license and Intel Corporation (&quot;Intel&quot;) is willing&n;  to grant a license for the software entitled Linux Base Driver for the&n;  Intel(R) PRO/1000 Family of Adapters (e1000) (the &quot;Software&quot;) being provided&n;  by Intel Corporation. The following definitions apply to this license:&n;  &n;  &quot;Licensed Patents&quot; means patent claims licensable by Intel Corporation which&n;  are necessarily infringed by the use of sale of the Software alone or when&n;  combined with the operating system referred to below.&n;  &n;  &quot;Recipient&quot; means the party to whom Intel delivers this Software.&n;  &n;  &quot;Licensee&quot; means Recipient and those third parties that receive a license to&n;  any operating system available under the GNU Public License version 2.0 or&n;  later.&n;  &n;  Copyright (c) 1999 - 2002 Intel Corporation.&n;  All rights reserved.&n;  &n;  The license is provided to Recipient and Recipient&squot;s Licensees under the&n;  following terms.&n;  &n;  Redistribution and use in source and binary forms of the Software, with or&n;  without modification, are permitted provided that the following conditions&n;  are met:&n;  &n;  Redistributions of source code of the Software may retain the above&n;  copyright notice, this list of conditions and the following disclaimer.&n;  &n;  Redistributions in binary form of the Software may reproduce the above&n;  copyright notice, this list of conditions and the following disclaimer in&n;  the documentation and/or materials provided with the distribution.&n;  &n;  Neither the name of Intel Corporation nor the names of its contributors&n;  shall be used to endorse or promote products derived from this Software&n;  without specific prior written permission.&n;  &n;  Intel hereby grants Recipient and Licensees a non-exclusive, worldwide,&n;  royalty-free patent license under Licensed Patents to make, use, sell, offer&n;  to sell, import and otherwise transfer the Software, if any, in source code&n;  and object code form. This license shall include changes to the Software&n;  that are error corrections or other minor changes to the Software that do&n;  not add functionality or features when the Software is incorporated in any&n;  version of an operating system that has been distributed under the GNU&n;  General Public License 2.0 or later. This patent license shall apply to the&n;  combination of the Software and any operating system licensed under the GNU&n;  Public License version 2.0 or later if, at the time Intel provides the&n;  Software to Recipient, such addition of the Software to the then publicly&n;  available versions of such operating systems available under the GNU Public&n;  License version 2.0 or later (whether in gold, beta or alpha form) causes&n;  such combination to be covered by the Licensed Patents. The patent license&n;  shall not apply to any other combinations which include the Software. NO&n;  hardware per se is licensed hereunder.&n;  &n;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS &quot;AS IS&quot;&n;  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE&n;  IMPLIED WARRANTIES OF MECHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE&n;  ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR IT CONTRIBUTORS BE LIABLE FOR ANY&n;  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES&n;  (INCLUDING, BUT NOT LIMITED, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;&n;  ANY LOSS OF USE; DATA, OR PROFITS; OR BUSINESS INTERUPTION) HOWEVER CAUSED&n;  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY OR&n;  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE&n;  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n;&n;*******************************************************************************/
multiline_comment|/* e1000_phy.h&n; * Structures, enums, and macros for the PHY&n; */
macro_line|#ifndef _E1000_PHY_H_
DECL|macro|_E1000_PHY_H_
mdefine_line|#define _E1000_PHY_H_
macro_line|#include &quot;e1000_osdep.h&quot;
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
DECL|enumerator|e1000_down_no_idle_no_detect
id|e1000_down_no_idle_no_detect
op_assign
l_int|0
comma
DECL|enumerator|e1000_down_no_idle_detect
id|e1000_down_no_idle_detect
comma
DECL|enumerator|e1000_down_no_idle_undefined
id|e1000_down_no_idle_undefined
op_assign
l_int|0xFF
DECL|typedef|e1000_down_no_idle
)brace
id|e1000_down_no_idle
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
DECL|member|link_reset
id|e1000_down_no_idle
id|link_reset
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
multiline_comment|/* Function Prototypes */
r_uint16
id|e1000_read_phy_reg
c_func
(paren
r_struct
id|e1000_shared_adapter
op_star
id|shared
comma
r_uint32
id|reg_addr
)paren
suffix:semicolon
r_void
id|e1000_write_phy_reg
c_func
(paren
r_struct
id|e1000_shared_adapter
op_star
id|shared
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
id|e1000_shared_adapter
op_star
id|shared
)paren
suffix:semicolon
id|boolean_t
id|e1000_phy_reset
c_func
(paren
r_struct
id|e1000_shared_adapter
op_star
id|shared
)paren
suffix:semicolon
id|boolean_t
id|e1000_phy_setup
c_func
(paren
r_struct
id|e1000_shared_adapter
op_star
id|shared
comma
r_uint32
id|ctrl_reg
)paren
suffix:semicolon
id|boolean_t
id|e1000_phy_setup_autoneg
c_func
(paren
r_struct
id|e1000_shared_adapter
op_star
id|shared
)paren
suffix:semicolon
r_void
id|e1000_config_mac_to_phy
c_func
(paren
r_struct
id|e1000_shared_adapter
op_star
id|shared
comma
r_uint16
id|mii_reg
)paren
suffix:semicolon
r_void
id|e1000_config_collision_dist
c_func
(paren
r_struct
id|e1000_shared_adapter
op_star
id|shared
)paren
suffix:semicolon
id|boolean_t
id|e1000_detect_gig_phy
c_func
(paren
r_struct
id|e1000_shared_adapter
op_star
id|shared
)paren
suffix:semicolon
r_void
id|e1000_phy_reset_dsp
c_func
(paren
r_struct
id|e1000_shared_adapter
op_star
id|shared
)paren
suffix:semicolon
id|boolean_t
id|e1000_wait_autoneg
c_func
(paren
r_struct
id|e1000_shared_adapter
op_star
id|shared
)paren
suffix:semicolon
id|boolean_t
id|e1000_phy_get_info
c_func
(paren
r_struct
id|e1000_shared_adapter
op_star
id|shared
comma
r_struct
id|e1000_phy_info
op_star
id|phy_status_info
)paren
suffix:semicolon
id|boolean_t
id|e1000_validate_mdi_setting
c_func
(paren
r_struct
id|e1000_shared_adapter
op_star
id|shared
)paren
suffix:semicolon
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
DECL|macro|M88E1000_EPSCR_TX_CLK_2_5
mdefine_line|#define M88E1000_EPSCR_TX_CLK_2_5     0x0060 /* 2.5 MHz TX_CLK */
DECL|macro|M88E1000_EPSCR_TX_CLK_25
mdefine_line|#define M88E1000_EPSCR_TX_CLK_25      0x0070 /* 25  MHz TX_CLK */
DECL|macro|M88E1000_EPSCR_TX_CLK_0
mdefine_line|#define M88E1000_EPSCR_TX_CLK_0       0x0000 /* NO  TX_CLK */
DECL|macro|M88E1000_EPSCR_DOWN_NO_IDLE_SHIFT
mdefine_line|#define M88E1000_EPSCR_DOWN_NO_IDLE_SHIFT 15
multiline_comment|/* Bit definitions for valid PHY IDs. */
DECL|macro|M88E1000_12_PHY_ID
mdefine_line|#define M88E1000_12_PHY_ID 0x01410C50
DECL|macro|M88E1000_14_PHY_ID
mdefine_line|#define M88E1000_14_PHY_ID 0x01410C40
DECL|macro|M88E1000_I_PHY_ID
mdefine_line|#define M88E1000_I_PHY_ID  0x01410C30
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
macro_line|#endif /* _E1000_PHY_H_ */
eof
