multiline_comment|/*******************************************************************************&n;&n;  &n;  Copyright(c) 1999 - 2004 Intel Corporation. All rights reserved.&n;  &n;  This program is free software; you can redistribute it and/or modify it &n;  under the terms of the GNU General Public License as published by the Free &n;  Software Foundation; either version 2 of the License, or (at your option) &n;  any later version.&n;  &n;  This program is distributed in the hope that it will be useful, but WITHOUT &n;  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or &n;  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for &n;  more details.&n;  &n;  You should have received a copy of the GNU General Public License along with&n;  this program; if not, write to the Free Software Foundation, Inc., 59 &n;  Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n;  &n;  The full GNU General Public License is included in this distribution in the&n;  file called LICENSE.&n;  &n;  Contact Information:&n;  Linux NICS &lt;linux.nics@intel.com&gt;&n;  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497&n;&n;*******************************************************************************/
macro_line|#ifndef _IXGB_HW_H_
DECL|macro|_IXGB_HW_H_
mdefine_line|#define _IXGB_HW_H_
macro_line|#include &quot;ixgb_osdep.h&quot;
multiline_comment|/* Enums */
r_typedef
r_enum
(brace
DECL|enumerator|ixgb_mac_unknown
id|ixgb_mac_unknown
op_assign
l_int|0
comma
DECL|enumerator|ixgb_82597
id|ixgb_82597
comma
DECL|enumerator|ixgb_num_macs
id|ixgb_num_macs
DECL|typedef|ixgb_mac_type
)brace
id|ixgb_mac_type
suffix:semicolon
multiline_comment|/* Types of physical layer modules */
r_typedef
r_enum
(brace
DECL|enumerator|ixgb_phy_type_unknown
id|ixgb_phy_type_unknown
op_assign
l_int|0
comma
DECL|enumerator|ixgb_phy_type_g6005
id|ixgb_phy_type_g6005
comma
multiline_comment|/* 850nm, MM fiber, XPAK transceiver */
DECL|enumerator|ixgb_phy_type_g6104
id|ixgb_phy_type_g6104
comma
multiline_comment|/* 1310nm, SM fiber, XPAK transceiver */
DECL|enumerator|ixgb_phy_type_txn17201
id|ixgb_phy_type_txn17201
comma
multiline_comment|/* 850nm, MM fiber, XPAK transceiver */
DECL|enumerator|ixgb_phy_type_txn17401
id|ixgb_phy_type_txn17401
multiline_comment|/* 1310nm, SM fiber, XENPAK transceiver */
DECL|typedef|ixgb_phy_type
)brace
id|ixgb_phy_type
suffix:semicolon
multiline_comment|/* XPAK transceiver vendors, for the SR adapters */
r_typedef
r_enum
(brace
DECL|enumerator|ixgb_xpak_vendor_intel
id|ixgb_xpak_vendor_intel
comma
DECL|enumerator|ixgb_xpak_vendor_infineon
id|ixgb_xpak_vendor_infineon
DECL|typedef|ixgb_xpak_vendor
)brace
id|ixgb_xpak_vendor
suffix:semicolon
multiline_comment|/* Media Types */
r_typedef
r_enum
(brace
DECL|enumerator|ixgb_media_type_unknown
id|ixgb_media_type_unknown
op_assign
l_int|0
comma
DECL|enumerator|ixgb_media_type_fiber
id|ixgb_media_type_fiber
op_assign
l_int|1
comma
DECL|enumerator|ixgb_num_media_types
id|ixgb_num_media_types
DECL|typedef|ixgb_media_type
)brace
id|ixgb_media_type
suffix:semicolon
multiline_comment|/* Flow Control Settings */
r_typedef
r_enum
(brace
DECL|enumerator|ixgb_fc_none
id|ixgb_fc_none
op_assign
l_int|0
comma
DECL|enumerator|ixgb_fc_rx_pause
id|ixgb_fc_rx_pause
op_assign
l_int|1
comma
DECL|enumerator|ixgb_fc_tx_pause
id|ixgb_fc_tx_pause
op_assign
l_int|2
comma
DECL|enumerator|ixgb_fc_full
id|ixgb_fc_full
op_assign
l_int|3
comma
DECL|enumerator|ixgb_fc_default
id|ixgb_fc_default
op_assign
l_int|0xFF
DECL|typedef|ixgb_fc_type
)brace
id|ixgb_fc_type
suffix:semicolon
multiline_comment|/* PCI bus types */
r_typedef
r_enum
(brace
DECL|enumerator|ixgb_bus_type_unknown
id|ixgb_bus_type_unknown
op_assign
l_int|0
comma
DECL|enumerator|ixgb_bus_type_pci
id|ixgb_bus_type_pci
comma
DECL|enumerator|ixgb_bus_type_pcix
id|ixgb_bus_type_pcix
DECL|typedef|ixgb_bus_type
)brace
id|ixgb_bus_type
suffix:semicolon
multiline_comment|/* PCI bus speeds */
r_typedef
r_enum
(brace
DECL|enumerator|ixgb_bus_speed_unknown
id|ixgb_bus_speed_unknown
op_assign
l_int|0
comma
DECL|enumerator|ixgb_bus_speed_33
id|ixgb_bus_speed_33
comma
DECL|enumerator|ixgb_bus_speed_66
id|ixgb_bus_speed_66
comma
DECL|enumerator|ixgb_bus_speed_100
id|ixgb_bus_speed_100
comma
DECL|enumerator|ixgb_bus_speed_133
id|ixgb_bus_speed_133
comma
DECL|enumerator|ixgb_bus_speed_reserved
id|ixgb_bus_speed_reserved
DECL|typedef|ixgb_bus_speed
)brace
id|ixgb_bus_speed
suffix:semicolon
multiline_comment|/* PCI bus widths */
r_typedef
r_enum
(brace
DECL|enumerator|ixgb_bus_width_unknown
id|ixgb_bus_width_unknown
op_assign
l_int|0
comma
DECL|enumerator|ixgb_bus_width_32
id|ixgb_bus_width_32
comma
DECL|enumerator|ixgb_bus_width_64
id|ixgb_bus_width_64
DECL|typedef|ixgb_bus_width
)brace
id|ixgb_bus_width
suffix:semicolon
DECL|macro|IXGB_ETH_LENGTH_OF_ADDRESS
mdefine_line|#define IXGB_ETH_LENGTH_OF_ADDRESS   6
DECL|macro|IXGB_EEPROM_SIZE
mdefine_line|#define IXGB_EEPROM_SIZE    64&t;/* Size in words */
DECL|macro|SPEED_10000
mdefine_line|#define SPEED_10000  10000
DECL|macro|FULL_DUPLEX
mdefine_line|#define FULL_DUPLEX  2
DECL|macro|MIN_NUMBER_OF_DESCRIPTORS
mdefine_line|#define MIN_NUMBER_OF_DESCRIPTORS       8
DECL|macro|MAX_NUMBER_OF_DESCRIPTORS
mdefine_line|#define MAX_NUMBER_OF_DESCRIPTORS  0xFFF8&t;/* 13 bits in RDLEN/TDLEN, 128B aligned     */
DECL|macro|IXGB_DELAY_BEFORE_RESET
mdefine_line|#define IXGB_DELAY_BEFORE_RESET        10&t;/* allow 10ms after idling rx/tx units      */
DECL|macro|IXGB_DELAY_AFTER_RESET
mdefine_line|#define IXGB_DELAY_AFTER_RESET          1&t;/* allow 1ms after the reset                */
DECL|macro|IXGB_DELAY_AFTER_EE_RESET
mdefine_line|#define IXGB_DELAY_AFTER_EE_RESET      10&t;/* allow 10ms after the EEPROM reset        */
DECL|macro|IXGB_DELAY_USECS_AFTER_LINK_RESET
mdefine_line|#define IXGB_DELAY_USECS_AFTER_LINK_RESET    13&t;/* allow 13 microseconds after the reset    */
multiline_comment|/* NOTE: this is MICROSECONDS               */
DECL|macro|MAX_RESET_ITERATIONS
mdefine_line|#define MAX_RESET_ITERATIONS            8&t;/* number of iterations to get things right */
multiline_comment|/* General Registers */
DECL|macro|IXGB_CTRL0
mdefine_line|#define IXGB_CTRL0   0x00000&t;/* Device Control Register 0 - RW */
DECL|macro|IXGB_CTRL1
mdefine_line|#define IXGB_CTRL1   0x00008&t;/* Device Control Register 1 - RW */
DECL|macro|IXGB_STATUS
mdefine_line|#define IXGB_STATUS  0x00010&t;/* Device Status Register - RO */
DECL|macro|IXGB_EECD
mdefine_line|#define IXGB_EECD    0x00018&t;/* EEPROM/Flash Control/Data Register - RW */
DECL|macro|IXGB_MFS
mdefine_line|#define IXGB_MFS     0x00020&t;/* Maximum Frame Size - RW */
multiline_comment|/* Interrupt */
DECL|macro|IXGB_ICR
mdefine_line|#define IXGB_ICR     0x00080&t;/* Interrupt Cause Read - R/clr */
DECL|macro|IXGB_ICS
mdefine_line|#define IXGB_ICS     0x00088&t;/* Interrupt Cause Set - RW */
DECL|macro|IXGB_IMS
mdefine_line|#define IXGB_IMS     0x00090&t;/* Interrupt Mask Set/Read - RW */
DECL|macro|IXGB_IMC
mdefine_line|#define IXGB_IMC     0x00098&t;/* Interrupt Mask Clear - WO */
multiline_comment|/* Receive */
DECL|macro|IXGB_RCTL
mdefine_line|#define IXGB_RCTL    0x00100&t;/* RX Control - RW */
DECL|macro|IXGB_FCRTL
mdefine_line|#define IXGB_FCRTL   0x00108&t;/* Flow Control Receive Threshold Low - RW */
DECL|macro|IXGB_FCRTH
mdefine_line|#define IXGB_FCRTH   0x00110&t;/* Flow Control Receive Threshold High - RW */
DECL|macro|IXGB_RDBAL
mdefine_line|#define IXGB_RDBAL   0x00118&t;/* RX Descriptor Base Low - RW */
DECL|macro|IXGB_RDBAH
mdefine_line|#define IXGB_RDBAH   0x0011C&t;/* RX Descriptor Base High - RW */
DECL|macro|IXGB_RDLEN
mdefine_line|#define IXGB_RDLEN   0x00120&t;/* RX Descriptor Length - RW */
DECL|macro|IXGB_RDH
mdefine_line|#define IXGB_RDH     0x00128&t;/* RX Descriptor Head - RW */
DECL|macro|IXGB_RDT
mdefine_line|#define IXGB_RDT     0x00130&t;/* RX Descriptor Tail - RW */
DECL|macro|IXGB_RDTR
mdefine_line|#define IXGB_RDTR    0x00138&t;/* RX Delay Timer Ring - RW */
DECL|macro|IXGB_RXDCTL
mdefine_line|#define IXGB_RXDCTL  0x00140&t;/* Receive Descriptor Control - RW */
DECL|macro|IXGB_RAIDC
mdefine_line|#define IXGB_RAIDC   0x00148&t;/* Receive Adaptive Interrupt Delay Control - RW */
DECL|macro|IXGB_RXCSUM
mdefine_line|#define IXGB_RXCSUM  0x00158&t;/* Receive Checksum Control - RW */
DECL|macro|IXGB_RA
mdefine_line|#define IXGB_RA      0x00180&t;/* Receive Address Array Base - RW */
DECL|macro|IXGB_RAL
mdefine_line|#define IXGB_RAL     0x00180&t;/* Receive Address Low [0:15] - RW */
DECL|macro|IXGB_RAH
mdefine_line|#define IXGB_RAH     0x00184&t;/* Receive Address High [0:15] - RW */
DECL|macro|IXGB_MTA
mdefine_line|#define IXGB_MTA     0x00200&t;/* Multicast Table Array [0:127] - RW */
DECL|macro|IXGB_VFTA
mdefine_line|#define IXGB_VFTA    0x00400&t;/* VLAN Filter Table Array [0:127] - RW */
DECL|macro|IXGB_REQ_RX_DESCRIPTOR_MULTIPLE
mdefine_line|#define IXGB_REQ_RX_DESCRIPTOR_MULTIPLE 8
multiline_comment|/* Transmit */
DECL|macro|IXGB_TCTL
mdefine_line|#define IXGB_TCTL    0x00600&t;/* TX Control - RW */
DECL|macro|IXGB_TDBAL
mdefine_line|#define IXGB_TDBAL   0x00608&t;/* TX Descriptor Base Low - RW */
DECL|macro|IXGB_TDBAH
mdefine_line|#define IXGB_TDBAH   0x0060C&t;/* TX Descriptor Base High - RW */
DECL|macro|IXGB_TDLEN
mdefine_line|#define IXGB_TDLEN   0x00610&t;/* TX Descriptor Length - RW */
DECL|macro|IXGB_TDH
mdefine_line|#define IXGB_TDH     0x00618&t;/* TX Descriptor Head - RW */
DECL|macro|IXGB_TDT
mdefine_line|#define IXGB_TDT     0x00620&t;/* TX Descriptor Tail - RW */
DECL|macro|IXGB_TIDV
mdefine_line|#define IXGB_TIDV    0x00628&t;/* TX Interrupt Delay Value - RW */
DECL|macro|IXGB_TXDCTL
mdefine_line|#define IXGB_TXDCTL  0x00630&t;/* Transmit Descriptor Control - RW */
DECL|macro|IXGB_TSPMT
mdefine_line|#define IXGB_TSPMT   0x00638&t;/* TCP Segmentation PAD &amp; Min Threshold - RW */
DECL|macro|IXGB_PAP
mdefine_line|#define IXGB_PAP     0x00640&t;/* Pause and Pace - RW */
DECL|macro|IXGB_REQ_TX_DESCRIPTOR_MULTIPLE
mdefine_line|#define IXGB_REQ_TX_DESCRIPTOR_MULTIPLE 8
multiline_comment|/* Physical */
DECL|macro|IXGB_PCSC1
mdefine_line|#define IXGB_PCSC1   0x00700&t;/* PCS Control 1 - RW */
DECL|macro|IXGB_PCSC2
mdefine_line|#define IXGB_PCSC2   0x00708&t;/* PCS Control 2 - RW */
DECL|macro|IXGB_PCSS1
mdefine_line|#define IXGB_PCSS1   0x00710&t;/* PCS Status 1 - RO */
DECL|macro|IXGB_PCSS2
mdefine_line|#define IXGB_PCSS2   0x00718&t;/* PCS Status 2 - RO */
DECL|macro|IXGB_XPCSS
mdefine_line|#define IXGB_XPCSS   0x00720&t;/* 10GBASE-X PCS Status (or XGXS Lane Status) - RO */
DECL|macro|IXGB_UCCR
mdefine_line|#define IXGB_UCCR    0x00728&t;/* Unilink Circuit Control Register */
DECL|macro|IXGB_XPCSTC
mdefine_line|#define IXGB_XPCSTC  0x00730&t;/* 10GBASE-X PCS Test Control */
DECL|macro|IXGB_MACA
mdefine_line|#define IXGB_MACA    0x00738&t;/* MDI Autoscan Command and Address - RW */
DECL|macro|IXGB_APAE
mdefine_line|#define IXGB_APAE    0x00740&t;/* Autoscan PHY Address Enable - RW */
DECL|macro|IXGB_ARD
mdefine_line|#define IXGB_ARD     0x00748&t;/* Autoscan Read Data - RO */
DECL|macro|IXGB_AIS
mdefine_line|#define IXGB_AIS     0x00750&t;/* Autoscan Interrupt Status - RO */
DECL|macro|IXGB_MSCA
mdefine_line|#define IXGB_MSCA    0x00758&t;/* MDI Single Command and Address - RW */
DECL|macro|IXGB_MSRWD
mdefine_line|#define IXGB_MSRWD   0x00760&t;/* MDI Single Read and Write Data - RW, RO */
multiline_comment|/* Wake-up */
DECL|macro|IXGB_WUFC
mdefine_line|#define IXGB_WUFC    0x00808&t;/* Wake Up Filter Control - RW */
DECL|macro|IXGB_WUS
mdefine_line|#define IXGB_WUS     0x00810&t;/* Wake Up Status - RO */
DECL|macro|IXGB_FFLT
mdefine_line|#define IXGB_FFLT    0x01000&t;/* Flexible Filter Length Table - RW */
DECL|macro|IXGB_FFMT
mdefine_line|#define IXGB_FFMT    0x01020&t;/* Flexible Filter Mask Table - RW */
DECL|macro|IXGB_FTVT
mdefine_line|#define IXGB_FTVT    0x01420&t;/* Flexible Filter Value Table - RW */
multiline_comment|/* Statistics */
DECL|macro|IXGB_TPRL
mdefine_line|#define IXGB_TPRL    0x02000&t;/* Total Packets Received (Low) */
DECL|macro|IXGB_TPRH
mdefine_line|#define IXGB_TPRH    0x02004&t;/* Total Packets Received (High) */
DECL|macro|IXGB_GPRCL
mdefine_line|#define IXGB_GPRCL   0x02008&t;/* Good Packets Received Count (Low) */
DECL|macro|IXGB_GPRCH
mdefine_line|#define IXGB_GPRCH   0x0200C&t;/* Good Packets Received Count (High) */
DECL|macro|IXGB_BPRCL
mdefine_line|#define IXGB_BPRCL   0x02010&t;/* Broadcast Packets Received Count (Low) */
DECL|macro|IXGB_BPRCH
mdefine_line|#define IXGB_BPRCH   0x02014&t;/* Broadcast Packets Received Count (High) */
DECL|macro|IXGB_MPRCL
mdefine_line|#define IXGB_MPRCL   0x02018&t;/* Multicast Packets Received Count (Low) */
DECL|macro|IXGB_MPRCH
mdefine_line|#define IXGB_MPRCH   0x0201C&t;/* Multicast Packets Received Count (High) */
DECL|macro|IXGB_UPRCL
mdefine_line|#define IXGB_UPRCL   0x02020&t;/* Unicast Packets Received Count (Low) */
DECL|macro|IXGB_UPRCH
mdefine_line|#define IXGB_UPRCH   0x02024&t;/* Unicast Packets Received Count (High) */
DECL|macro|IXGB_VPRCL
mdefine_line|#define IXGB_VPRCL   0x02028&t;/* VLAN Packets Received Count (Low) */
DECL|macro|IXGB_VPRCH
mdefine_line|#define IXGB_VPRCH   0x0202C&t;/* VLAN Packets Received Count (High) */
DECL|macro|IXGB_JPRCL
mdefine_line|#define IXGB_JPRCL   0x02030&t;/* Jumbo Packets Received Count (Low) */
DECL|macro|IXGB_JPRCH
mdefine_line|#define IXGB_JPRCH   0x02034&t;/* Jumbo Packets Received Count (High) */
DECL|macro|IXGB_GORCL
mdefine_line|#define IXGB_GORCL   0x02038&t;/* Good Octets Received Count (Low) */
DECL|macro|IXGB_GORCH
mdefine_line|#define IXGB_GORCH   0x0203C&t;/* Good Octets Received Count (High) */
DECL|macro|IXGB_TORL
mdefine_line|#define IXGB_TORL    0x02040&t;/* Total Octets Received (Low) */
DECL|macro|IXGB_TORH
mdefine_line|#define IXGB_TORH    0x02044&t;/* Total Octets Received (High) */
DECL|macro|IXGB_RNBC
mdefine_line|#define IXGB_RNBC    0x02048&t;/* Receive No Buffers Count */
DECL|macro|IXGB_RUC
mdefine_line|#define IXGB_RUC     0x02050&t;/* Receive Undersize Count */
DECL|macro|IXGB_ROC
mdefine_line|#define IXGB_ROC     0x02058&t;/* Receive Oversize Count */
DECL|macro|IXGB_RLEC
mdefine_line|#define IXGB_RLEC    0x02060&t;/* Receive Length Error Count */
DECL|macro|IXGB_CRCERRS
mdefine_line|#define IXGB_CRCERRS 0x02068&t;/* CRC Error Count */
DECL|macro|IXGB_ICBC
mdefine_line|#define IXGB_ICBC    0x02070&t;/* Illegal control byte in mid-packet Count */
DECL|macro|IXGB_ECBC
mdefine_line|#define IXGB_ECBC    0x02078&t;/* Error Control byte in mid-packet Count */
DECL|macro|IXGB_MPC
mdefine_line|#define IXGB_MPC     0x02080&t;/* Missed Packets Count */
DECL|macro|IXGB_TPTL
mdefine_line|#define IXGB_TPTL    0x02100&t;/* Total Packets Transmitted (Low) */
DECL|macro|IXGB_TPTH
mdefine_line|#define IXGB_TPTH    0x02104&t;/* Total Packets Transmitted (High) */
DECL|macro|IXGB_GPTCL
mdefine_line|#define IXGB_GPTCL   0x02108&t;/* Good Packets Transmitted Count (Low) */
DECL|macro|IXGB_GPTCH
mdefine_line|#define IXGB_GPTCH   0x0210C&t;/* Good Packets Transmitted Count (High) */
DECL|macro|IXGB_BPTCL
mdefine_line|#define IXGB_BPTCL   0x02110&t;/* Broadcast Packets Transmitted Count (Low) */
DECL|macro|IXGB_BPTCH
mdefine_line|#define IXGB_BPTCH   0x02114&t;/* Broadcast Packets Transmitted Count (High) */
DECL|macro|IXGB_MPTCL
mdefine_line|#define IXGB_MPTCL   0x02118&t;/* Multicast Packets Transmitted Count (Low) */
DECL|macro|IXGB_MPTCH
mdefine_line|#define IXGB_MPTCH   0x0211C&t;/* Multicast Packets Transmitted Count (High) */
DECL|macro|IXGB_UPTCL
mdefine_line|#define IXGB_UPTCL   0x02120&t;/* Unicast Packets Transmitted Count (Low) */
DECL|macro|IXGB_UPTCH
mdefine_line|#define IXGB_UPTCH   0x02124&t;/* Unicast Packets Transmitted Count (High) */
DECL|macro|IXGB_VPTCL
mdefine_line|#define IXGB_VPTCL   0x02128&t;/* VLAN Packets Transmitted Count (Low) */
DECL|macro|IXGB_VPTCH
mdefine_line|#define IXGB_VPTCH   0x0212C&t;/* VLAN Packets Transmitted Count (High) */
DECL|macro|IXGB_JPTCL
mdefine_line|#define IXGB_JPTCL   0x02130&t;/* Jumbo Packets Transmitted Count (Low) */
DECL|macro|IXGB_JPTCH
mdefine_line|#define IXGB_JPTCH   0x02134&t;/* Jumbo Packets Transmitted Count (High) */
DECL|macro|IXGB_GOTCL
mdefine_line|#define IXGB_GOTCL   0x02138&t;/* Good Octets Transmitted Count (Low) */
DECL|macro|IXGB_GOTCH
mdefine_line|#define IXGB_GOTCH   0x0213C&t;/* Good Octets Transmitted Count (High) */
DECL|macro|IXGB_TOTL
mdefine_line|#define IXGB_TOTL    0x02140&t;/* Total Octets Transmitted Count (Low) */
DECL|macro|IXGB_TOTH
mdefine_line|#define IXGB_TOTH    0x02144&t;/* Total Octets Transmitted Count (High) */
DECL|macro|IXGB_DC
mdefine_line|#define IXGB_DC      0x02148&t;/* Defer Count */
DECL|macro|IXGB_PLT64C
mdefine_line|#define IXGB_PLT64C  0x02150&t;/* Packet Transmitted was less than 64 bytes Count */
DECL|macro|IXGB_TSCTC
mdefine_line|#define IXGB_TSCTC   0x02170&t;/* TCP Segmentation Context Transmitted Count */
DECL|macro|IXGB_TSCTFC
mdefine_line|#define IXGB_TSCTFC  0x02178&t;/* TCP Segmentation Context Tx Fail Count */
DECL|macro|IXGB_IBIC
mdefine_line|#define IXGB_IBIC    0x02180&t;/* Illegal byte during Idle stream count */
DECL|macro|IXGB_RFC
mdefine_line|#define IXGB_RFC     0x02188&t;/* Remote Fault Count */
DECL|macro|IXGB_LFC
mdefine_line|#define IXGB_LFC     0x02190&t;/* Local Fault Count */
DECL|macro|IXGB_PFRC
mdefine_line|#define IXGB_PFRC    0x02198&t;/* Pause Frame Receive Count */
DECL|macro|IXGB_PFTC
mdefine_line|#define IXGB_PFTC    0x021A0&t;/* Pause Frame Transmit Count */
DECL|macro|IXGB_MCFRC
mdefine_line|#define IXGB_MCFRC   0x021A8&t;/* MAC Control Frames (non-Pause) Received Count */
DECL|macro|IXGB_MCFTC
mdefine_line|#define IXGB_MCFTC   0x021B0&t;/* MAC Control Frames (non-Pause) Transmitted Count */
DECL|macro|IXGB_XONRXC
mdefine_line|#define IXGB_XONRXC  0x021B8&t;/* XON Received Count */
DECL|macro|IXGB_XONTXC
mdefine_line|#define IXGB_XONTXC  0x021C0&t;/* XON Transmitted Count */
DECL|macro|IXGB_XOFFRXC
mdefine_line|#define IXGB_XOFFRXC 0x021C8&t;/* XOFF Received Count */
DECL|macro|IXGB_XOFFTXC
mdefine_line|#define IXGB_XOFFTXC 0x021D0&t;/* XOFF Transmitted Count */
DECL|macro|IXGB_RJC
mdefine_line|#define IXGB_RJC     0x021D8&t;/* Receive Jabber Count */
multiline_comment|/* CTRL0 Bit Masks */
DECL|macro|IXGB_CTRL0_LRST
mdefine_line|#define IXGB_CTRL0_LRST     0x00000008
DECL|macro|IXGB_CTRL0_JFE
mdefine_line|#define IXGB_CTRL0_JFE      0x00000010
DECL|macro|IXGB_CTRL0_XLE
mdefine_line|#define IXGB_CTRL0_XLE      0x00000020
DECL|macro|IXGB_CTRL0_MDCS
mdefine_line|#define IXGB_CTRL0_MDCS     0x00000040
DECL|macro|IXGB_CTRL0_CMDC
mdefine_line|#define IXGB_CTRL0_CMDC     0x00000080
DECL|macro|IXGB_CTRL0_SDP0
mdefine_line|#define IXGB_CTRL0_SDP0     0x00040000
DECL|macro|IXGB_CTRL0_SDP1
mdefine_line|#define IXGB_CTRL0_SDP1     0x00080000
DECL|macro|IXGB_CTRL0_SDP2
mdefine_line|#define IXGB_CTRL0_SDP2     0x00100000
DECL|macro|IXGB_CTRL0_SDP3
mdefine_line|#define IXGB_CTRL0_SDP3     0x00200000
DECL|macro|IXGB_CTRL0_SDP0_DIR
mdefine_line|#define IXGB_CTRL0_SDP0_DIR 0x00400000
DECL|macro|IXGB_CTRL0_SDP1_DIR
mdefine_line|#define IXGB_CTRL0_SDP1_DIR 0x00800000
DECL|macro|IXGB_CTRL0_SDP2_DIR
mdefine_line|#define IXGB_CTRL0_SDP2_DIR 0x01000000
DECL|macro|IXGB_CTRL0_SDP3_DIR
mdefine_line|#define IXGB_CTRL0_SDP3_DIR 0x02000000
DECL|macro|IXGB_CTRL0_RST
mdefine_line|#define IXGB_CTRL0_RST      0x04000000
DECL|macro|IXGB_CTRL0_RPE
mdefine_line|#define IXGB_CTRL0_RPE      0x08000000
DECL|macro|IXGB_CTRL0_TPE
mdefine_line|#define IXGB_CTRL0_TPE      0x10000000
DECL|macro|IXGB_CTRL0_VME
mdefine_line|#define IXGB_CTRL0_VME      0x40000000
multiline_comment|/* CTRL1 Bit Masks */
DECL|macro|IXGB_CTRL1_GPI0_EN
mdefine_line|#define IXGB_CTRL1_GPI0_EN     0x00000001
DECL|macro|IXGB_CTRL1_GPI1_EN
mdefine_line|#define IXGB_CTRL1_GPI1_EN     0x00000002
DECL|macro|IXGB_CTRL1_GPI2_EN
mdefine_line|#define IXGB_CTRL1_GPI2_EN     0x00000004
DECL|macro|IXGB_CTRL1_GPI3_EN
mdefine_line|#define IXGB_CTRL1_GPI3_EN     0x00000008
DECL|macro|IXGB_CTRL1_SDP4
mdefine_line|#define IXGB_CTRL1_SDP4        0x00000010
DECL|macro|IXGB_CTRL1_SDP5
mdefine_line|#define IXGB_CTRL1_SDP5        0x00000020
DECL|macro|IXGB_CTRL1_SDP6
mdefine_line|#define IXGB_CTRL1_SDP6        0x00000040
DECL|macro|IXGB_CTRL1_SDP7
mdefine_line|#define IXGB_CTRL1_SDP7        0x00000080
DECL|macro|IXGB_CTRL1_SDP4_DIR
mdefine_line|#define IXGB_CTRL1_SDP4_DIR    0x00000100
DECL|macro|IXGB_CTRL1_SDP5_DIR
mdefine_line|#define IXGB_CTRL1_SDP5_DIR    0x00000200
DECL|macro|IXGB_CTRL1_SDP6_DIR
mdefine_line|#define IXGB_CTRL1_SDP6_DIR    0x00000400
DECL|macro|IXGB_CTRL1_SDP7_DIR
mdefine_line|#define IXGB_CTRL1_SDP7_DIR    0x00000800
DECL|macro|IXGB_CTRL1_EE_RST
mdefine_line|#define IXGB_CTRL1_EE_RST      0x00002000
DECL|macro|IXGB_CTRL1_RO_DIS
mdefine_line|#define IXGB_CTRL1_RO_DIS      0x00020000
DECL|macro|IXGB_CTRL1_PCIXHM_MASK
mdefine_line|#define IXGB_CTRL1_PCIXHM_MASK 0x00C00000
DECL|macro|IXGB_CTRL1_PCIXHM_1_2
mdefine_line|#define IXGB_CTRL1_PCIXHM_1_2  0x00000000
DECL|macro|IXGB_CTRL1_PCIXHM_5_8
mdefine_line|#define IXGB_CTRL1_PCIXHM_5_8  0x00400000
DECL|macro|IXGB_CTRL1_PCIXHM_3_4
mdefine_line|#define IXGB_CTRL1_PCIXHM_3_4  0x00800000
DECL|macro|IXGB_CTRL1_PCIXHM_7_8
mdefine_line|#define IXGB_CTRL1_PCIXHM_7_8  0x00C00000
multiline_comment|/* STATUS Bit Masks */
DECL|macro|IXGB_STATUS_LU
mdefine_line|#define IXGB_STATUS_LU            0x00000002
DECL|macro|IXGB_STATUS_AIP
mdefine_line|#define IXGB_STATUS_AIP           0x00000004
DECL|macro|IXGB_STATUS_TXOFF
mdefine_line|#define IXGB_STATUS_TXOFF         0x00000010
DECL|macro|IXGB_STATUS_XAUIME
mdefine_line|#define IXGB_STATUS_XAUIME        0x00000020
DECL|macro|IXGB_STATUS_RES
mdefine_line|#define IXGB_STATUS_RES           0x00000040
DECL|macro|IXGB_STATUS_RIS
mdefine_line|#define IXGB_STATUS_RIS           0x00000080
DECL|macro|IXGB_STATUS_RIE
mdefine_line|#define IXGB_STATUS_RIE           0x00000100
DECL|macro|IXGB_STATUS_RLF
mdefine_line|#define IXGB_STATUS_RLF           0x00000200
DECL|macro|IXGB_STATUS_RRF
mdefine_line|#define IXGB_STATUS_RRF           0x00000400
DECL|macro|IXGB_STATUS_PCI_SPD
mdefine_line|#define IXGB_STATUS_PCI_SPD       0x00000800
DECL|macro|IXGB_STATUS_BUS64
mdefine_line|#define IXGB_STATUS_BUS64         0x00001000
DECL|macro|IXGB_STATUS_PCIX_MODE
mdefine_line|#define IXGB_STATUS_PCIX_MODE     0x00002000
DECL|macro|IXGB_STATUS_PCIX_SPD_MASK
mdefine_line|#define IXGB_STATUS_PCIX_SPD_MASK 0x0000C000
DECL|macro|IXGB_STATUS_PCIX_SPD_66
mdefine_line|#define IXGB_STATUS_PCIX_SPD_66   0x00000000
DECL|macro|IXGB_STATUS_PCIX_SPD_100
mdefine_line|#define IXGB_STATUS_PCIX_SPD_100  0x00004000
DECL|macro|IXGB_STATUS_PCIX_SPD_133
mdefine_line|#define IXGB_STATUS_PCIX_SPD_133  0x00008000
DECL|macro|IXGB_STATUS_REV_ID_MASK
mdefine_line|#define IXGB_STATUS_REV_ID_MASK   0x000F0000
DECL|macro|IXGB_STATUS_REV_ID_SHIFT
mdefine_line|#define IXGB_STATUS_REV_ID_SHIFT  16
multiline_comment|/* EECD Bit Masks */
DECL|macro|IXGB_EECD_SK
mdefine_line|#define IXGB_EECD_SK       0x00000001
DECL|macro|IXGB_EECD_CS
mdefine_line|#define IXGB_EECD_CS       0x00000002
DECL|macro|IXGB_EECD_DI
mdefine_line|#define IXGB_EECD_DI       0x00000004
DECL|macro|IXGB_EECD_DO
mdefine_line|#define IXGB_EECD_DO       0x00000008
DECL|macro|IXGB_EECD_FWE_MASK
mdefine_line|#define IXGB_EECD_FWE_MASK 0x00000030
DECL|macro|IXGB_EECD_FWE_DIS
mdefine_line|#define IXGB_EECD_FWE_DIS  0x00000010
DECL|macro|IXGB_EECD_FWE_EN
mdefine_line|#define IXGB_EECD_FWE_EN   0x00000020
multiline_comment|/* MFS */
DECL|macro|IXGB_MFS_SHIFT
mdefine_line|#define IXGB_MFS_SHIFT 16
multiline_comment|/* Interrupt Register Bit Masks (used for ICR, ICS, IMS, and IMC) */
DECL|macro|IXGB_INT_TXDW
mdefine_line|#define IXGB_INT_TXDW     0x00000001
DECL|macro|IXGB_INT_TXQE
mdefine_line|#define IXGB_INT_TXQE     0x00000002
DECL|macro|IXGB_INT_LSC
mdefine_line|#define IXGB_INT_LSC      0x00000004
DECL|macro|IXGB_INT_RXSEQ
mdefine_line|#define IXGB_INT_RXSEQ    0x00000008
DECL|macro|IXGB_INT_RXDMT0
mdefine_line|#define IXGB_INT_RXDMT0   0x00000010
DECL|macro|IXGB_INT_RXO
mdefine_line|#define IXGB_INT_RXO      0x00000040
DECL|macro|IXGB_INT_RXT0
mdefine_line|#define IXGB_INT_RXT0     0x00000080
DECL|macro|IXGB_INT_AUTOSCAN
mdefine_line|#define IXGB_INT_AUTOSCAN 0x00000200
DECL|macro|IXGB_INT_GPI0
mdefine_line|#define IXGB_INT_GPI0     0x00000800
DECL|macro|IXGB_INT_GPI1
mdefine_line|#define IXGB_INT_GPI1     0x00001000
DECL|macro|IXGB_INT_GPI2
mdefine_line|#define IXGB_INT_GPI2     0x00002000
DECL|macro|IXGB_INT_GPI3
mdefine_line|#define IXGB_INT_GPI3     0x00004000
multiline_comment|/* RCTL Bit Masks */
DECL|macro|IXGB_RCTL_RXEN
mdefine_line|#define IXGB_RCTL_RXEN        0x00000002
DECL|macro|IXGB_RCTL_SBP
mdefine_line|#define IXGB_RCTL_SBP         0x00000004
DECL|macro|IXGB_RCTL_UPE
mdefine_line|#define IXGB_RCTL_UPE         0x00000008
DECL|macro|IXGB_RCTL_MPE
mdefine_line|#define IXGB_RCTL_MPE         0x00000010
DECL|macro|IXGB_RCTL_RDMTS_MASK
mdefine_line|#define IXGB_RCTL_RDMTS_MASK  0x00000300
DECL|macro|IXGB_RCTL_RDMTS_1_2
mdefine_line|#define IXGB_RCTL_RDMTS_1_2   0x00000000
DECL|macro|IXGB_RCTL_RDMTS_1_4
mdefine_line|#define IXGB_RCTL_RDMTS_1_4   0x00000100
DECL|macro|IXGB_RCTL_RDMTS_1_8
mdefine_line|#define IXGB_RCTL_RDMTS_1_8   0x00000200
DECL|macro|IXGB_RCTL_MO_MASK
mdefine_line|#define IXGB_RCTL_MO_MASK     0x00003000
DECL|macro|IXGB_RCTL_MO_47_36
mdefine_line|#define IXGB_RCTL_MO_47_36    0x00000000
DECL|macro|IXGB_RCTL_MO_46_35
mdefine_line|#define IXGB_RCTL_MO_46_35    0x00001000
DECL|macro|IXGB_RCTL_MO_45_34
mdefine_line|#define IXGB_RCTL_MO_45_34    0x00002000
DECL|macro|IXGB_RCTL_MO_43_32
mdefine_line|#define IXGB_RCTL_MO_43_32    0x00003000
DECL|macro|IXGB_RCTL_MO_SHIFT
mdefine_line|#define IXGB_RCTL_MO_SHIFT    12
DECL|macro|IXGB_RCTL_BAM
mdefine_line|#define IXGB_RCTL_BAM         0x00008000
DECL|macro|IXGB_RCTL_BSIZE_MASK
mdefine_line|#define IXGB_RCTL_BSIZE_MASK  0x00030000
DECL|macro|IXGB_RCTL_BSIZE_2048
mdefine_line|#define IXGB_RCTL_BSIZE_2048  0x00000000
DECL|macro|IXGB_RCTL_BSIZE_4096
mdefine_line|#define IXGB_RCTL_BSIZE_4096  0x00010000
DECL|macro|IXGB_RCTL_BSIZE_8192
mdefine_line|#define IXGB_RCTL_BSIZE_8192  0x00020000
DECL|macro|IXGB_RCTL_BSIZE_16384
mdefine_line|#define IXGB_RCTL_BSIZE_16384 0x00030000
DECL|macro|IXGB_RCTL_VFE
mdefine_line|#define IXGB_RCTL_VFE         0x00040000
DECL|macro|IXGB_RCTL_CFIEN
mdefine_line|#define IXGB_RCTL_CFIEN       0x00080000
DECL|macro|IXGB_RCTL_CFI
mdefine_line|#define IXGB_RCTL_CFI         0x00100000
DECL|macro|IXGB_RCTL_RPDA_MASK
mdefine_line|#define IXGB_RCTL_RPDA_MASK   0x00600000
DECL|macro|IXGB_RCTL_RPDA_MC_MAC
mdefine_line|#define IXGB_RCTL_RPDA_MC_MAC 0x00000000
DECL|macro|IXGB_RCTL_MC_ONLY
mdefine_line|#define IXGB_RCTL_MC_ONLY     0x00400000
DECL|macro|IXGB_RCTL_CFF
mdefine_line|#define IXGB_RCTL_CFF         0x00800000
DECL|macro|IXGB_RCTL_SECRC
mdefine_line|#define IXGB_RCTL_SECRC       0x04000000
DECL|macro|IXGB_RDT_FPDB
mdefine_line|#define IXGB_RDT_FPDB         0x80000000
DECL|macro|IXGB_RCTL_IDLE_RX_UNIT
mdefine_line|#define IXGB_RCTL_IDLE_RX_UNIT 0
multiline_comment|/* FCRTL Bit Masks */
DECL|macro|IXGB_FCRTL_XONE
mdefine_line|#define IXGB_FCRTL_XONE       0x80000000
multiline_comment|/* RXDCTL Bit Masks */
DECL|macro|IXGB_RXDCTL_PTHRESH_MASK
mdefine_line|#define IXGB_RXDCTL_PTHRESH_MASK  0x000001FF
DECL|macro|IXGB_RXDCTL_PTHRESH_SHIFT
mdefine_line|#define IXGB_RXDCTL_PTHRESH_SHIFT 0
DECL|macro|IXGB_RXDCTL_HTHRESH_MASK
mdefine_line|#define IXGB_RXDCTL_HTHRESH_MASK  0x0003FE00
DECL|macro|IXGB_RXDCTL_HTHRESH_SHIFT
mdefine_line|#define IXGB_RXDCTL_HTHRESH_SHIFT 9
DECL|macro|IXGB_RXDCTL_WTHRESH_MASK
mdefine_line|#define IXGB_RXDCTL_WTHRESH_MASK  0x07FC0000
DECL|macro|IXGB_RXDCTL_WTHRESH_SHIFT
mdefine_line|#define IXGB_RXDCTL_WTHRESH_SHIFT 18
multiline_comment|/* RAIDC Bit Masks */
DECL|macro|IXGB_RAIDC_HIGHTHRS_MASK
mdefine_line|#define IXGB_RAIDC_HIGHTHRS_MASK 0x0000003F
DECL|macro|IXGB_RAIDC_DELAY_MASK
mdefine_line|#define IXGB_RAIDC_DELAY_MASK    0x000FF800
DECL|macro|IXGB_RAIDC_DELAY_SHIFT
mdefine_line|#define IXGB_RAIDC_DELAY_SHIFT   11
DECL|macro|IXGB_RAIDC_POLL_MASK
mdefine_line|#define IXGB_RAIDC_POLL_MASK     0x1FF00000
DECL|macro|IXGB_RAIDC_POLL_SHIFT
mdefine_line|#define IXGB_RAIDC_POLL_SHIFT    20
DECL|macro|IXGB_RAIDC_RXT_GATE
mdefine_line|#define IXGB_RAIDC_RXT_GATE      0x40000000
DECL|macro|IXGB_RAIDC_EN
mdefine_line|#define IXGB_RAIDC_EN            0x80000000
DECL|macro|IXGB_RAIDC_POLL_1000_INTERRUPTS_PER_SECOND
mdefine_line|#define IXGB_RAIDC_POLL_1000_INTERRUPTS_PER_SECOND      1220
DECL|macro|IXGB_RAIDC_POLL_5000_INTERRUPTS_PER_SECOND
mdefine_line|#define IXGB_RAIDC_POLL_5000_INTERRUPTS_PER_SECOND      244
DECL|macro|IXGB_RAIDC_POLL_10000_INTERRUPTS_PER_SECOND
mdefine_line|#define IXGB_RAIDC_POLL_10000_INTERRUPTS_PER_SECOND     122
DECL|macro|IXGB_RAIDC_POLL_20000_INTERRUPTS_PER_SECOND
mdefine_line|#define IXGB_RAIDC_POLL_20000_INTERRUPTS_PER_SECOND     61
multiline_comment|/* RXCSUM Bit Masks */
DECL|macro|IXGB_RXCSUM_IPOFL
mdefine_line|#define IXGB_RXCSUM_IPOFL 0x00000100
DECL|macro|IXGB_RXCSUM_TUOFL
mdefine_line|#define IXGB_RXCSUM_TUOFL 0x00000200
multiline_comment|/* RAH Bit Masks */
DECL|macro|IXGB_RAH_ASEL_MASK
mdefine_line|#define IXGB_RAH_ASEL_MASK 0x00030000
DECL|macro|IXGB_RAH_ASEL_DEST
mdefine_line|#define IXGB_RAH_ASEL_DEST 0x00000000
DECL|macro|IXGB_RAH_ASEL_SRC
mdefine_line|#define IXGB_RAH_ASEL_SRC  0x00010000
DECL|macro|IXGB_RAH_AV
mdefine_line|#define IXGB_RAH_AV        0x80000000
multiline_comment|/* TCTL Bit Masks */
DECL|macro|IXGB_TCTL_TCE
mdefine_line|#define IXGB_TCTL_TCE  0x00000001
DECL|macro|IXGB_TCTL_TXEN
mdefine_line|#define IXGB_TCTL_TXEN 0x00000002
DECL|macro|IXGB_TCTL_TPDE
mdefine_line|#define IXGB_TCTL_TPDE 0x00000004
DECL|macro|IXGB_TCTL_IDLE_TX_UNIT
mdefine_line|#define IXGB_TCTL_IDLE_TX_UNIT  0
multiline_comment|/* TXDCTL Bit Masks */
DECL|macro|IXGB_TXDCTL_PTHRESH_MASK
mdefine_line|#define IXGB_TXDCTL_PTHRESH_MASK  0x0000007F
DECL|macro|IXGB_TXDCTL_HTHRESH_MASK
mdefine_line|#define IXGB_TXDCTL_HTHRESH_MASK  0x00007F00
DECL|macro|IXGB_TXDCTL_HTHRESH_SHIFT
mdefine_line|#define IXGB_TXDCTL_HTHRESH_SHIFT 8
DECL|macro|IXGB_TXDCTL_WTHRESH_MASK
mdefine_line|#define IXGB_TXDCTL_WTHRESH_MASK  0x007F0000
DECL|macro|IXGB_TXDCTL_WTHRESH_SHIFT
mdefine_line|#define IXGB_TXDCTL_WTHRESH_SHIFT 16
multiline_comment|/* TSPMT Bit Masks */
DECL|macro|IXGB_TSPMT_TSMT_MASK
mdefine_line|#define IXGB_TSPMT_TSMT_MASK   0x0000FFFF
DECL|macro|IXGB_TSPMT_TSPBP_MASK
mdefine_line|#define IXGB_TSPMT_TSPBP_MASK  0xFFFF0000
DECL|macro|IXGB_TSPMT_TSPBP_SHIFT
mdefine_line|#define IXGB_TSPMT_TSPBP_SHIFT 16
multiline_comment|/* PAP Bit Masks */
DECL|macro|IXGB_PAP_TXPC_MASK
mdefine_line|#define IXGB_PAP_TXPC_MASK 0x0000FFFF
DECL|macro|IXGB_PAP_TXPV_MASK
mdefine_line|#define IXGB_PAP_TXPV_MASK 0x000F0000
DECL|macro|IXGB_PAP_TXPV_10G
mdefine_line|#define IXGB_PAP_TXPV_10G  0x00000000
DECL|macro|IXGB_PAP_TXPV_1G
mdefine_line|#define IXGB_PAP_TXPV_1G   0x00010000
DECL|macro|IXGB_PAP_TXPV_2G
mdefine_line|#define IXGB_PAP_TXPV_2G   0x00020000
DECL|macro|IXGB_PAP_TXPV_3G
mdefine_line|#define IXGB_PAP_TXPV_3G   0x00030000
DECL|macro|IXGB_PAP_TXPV_4G
mdefine_line|#define IXGB_PAP_TXPV_4G   0x00040000
DECL|macro|IXGB_PAP_TXPV_5G
mdefine_line|#define IXGB_PAP_TXPV_5G   0x00050000
DECL|macro|IXGB_PAP_TXPV_6G
mdefine_line|#define IXGB_PAP_TXPV_6G   0x00060000
DECL|macro|IXGB_PAP_TXPV_7G
mdefine_line|#define IXGB_PAP_TXPV_7G   0x00070000
DECL|macro|IXGB_PAP_TXPV_8G
mdefine_line|#define IXGB_PAP_TXPV_8G   0x00080000
DECL|macro|IXGB_PAP_TXPV_9G
mdefine_line|#define IXGB_PAP_TXPV_9G   0x00090000
DECL|macro|IXGB_PAP_TXPV_WAN
mdefine_line|#define IXGB_PAP_TXPV_WAN  0x000F0000
multiline_comment|/* PCSC1 Bit Masks */
DECL|macro|IXGB_PCSC1_LOOPBACK
mdefine_line|#define IXGB_PCSC1_LOOPBACK 0x00004000
multiline_comment|/* PCSC2 Bit Masks */
DECL|macro|IXGB_PCSC2_PCS_TYPE_MASK
mdefine_line|#define IXGB_PCSC2_PCS_TYPE_MASK  0x00000003
DECL|macro|IXGB_PCSC2_PCS_TYPE_10GBX
mdefine_line|#define IXGB_PCSC2_PCS_TYPE_10GBX 0x00000001
multiline_comment|/* PCSS1 Bit Masks */
DECL|macro|IXGB_PCSS1_LOCAL_FAULT
mdefine_line|#define IXGB_PCSS1_LOCAL_FAULT    0x00000080
DECL|macro|IXGB_PCSS1_RX_LINK_STATUS
mdefine_line|#define IXGB_PCSS1_RX_LINK_STATUS 0x00000004
multiline_comment|/* PCSS2 Bit Masks */
DECL|macro|IXGB_PCSS2_DEV_PRES_MASK
mdefine_line|#define IXGB_PCSS2_DEV_PRES_MASK 0x0000C000
DECL|macro|IXGB_PCSS2_DEV_PRES
mdefine_line|#define IXGB_PCSS2_DEV_PRES      0x00004000
DECL|macro|IXGB_PCSS2_TX_LF
mdefine_line|#define IXGB_PCSS2_TX_LF         0x00000800
DECL|macro|IXGB_PCSS2_RX_LF
mdefine_line|#define IXGB_PCSS2_RX_LF         0x00000400
DECL|macro|IXGB_PCSS2_10GBW
mdefine_line|#define IXGB_PCSS2_10GBW         0x00000004
DECL|macro|IXGB_PCSS2_10GBX
mdefine_line|#define IXGB_PCSS2_10GBX         0x00000002
DECL|macro|IXGB_PCSS2_10GBR
mdefine_line|#define IXGB_PCSS2_10GBR         0x00000001
multiline_comment|/* XPCSS Bit Masks */
DECL|macro|IXGB_XPCSS_ALIGN_STATUS
mdefine_line|#define IXGB_XPCSS_ALIGN_STATUS 0x00001000
DECL|macro|IXGB_XPCSS_PATTERN_TEST
mdefine_line|#define IXGB_XPCSS_PATTERN_TEST 0x00000800
DECL|macro|IXGB_XPCSS_LANE_3_SYNC
mdefine_line|#define IXGB_XPCSS_LANE_3_SYNC  0x00000008
DECL|macro|IXGB_XPCSS_LANE_2_SYNC
mdefine_line|#define IXGB_XPCSS_LANE_2_SYNC  0x00000004
DECL|macro|IXGB_XPCSS_LANE_1_SYNC
mdefine_line|#define IXGB_XPCSS_LANE_1_SYNC  0x00000002
DECL|macro|IXGB_XPCSS_LANE_0_SYNC
mdefine_line|#define IXGB_XPCSS_LANE_0_SYNC  0x00000001
multiline_comment|/* XPCSTC Bit Masks */
DECL|macro|IXGB_XPCSTC_BERT_TRIG
mdefine_line|#define IXGB_XPCSTC_BERT_TRIG       0x00200000
DECL|macro|IXGB_XPCSTC_BERT_SST
mdefine_line|#define IXGB_XPCSTC_BERT_SST        0x00100000
DECL|macro|IXGB_XPCSTC_BERT_PSZ_MASK
mdefine_line|#define IXGB_XPCSTC_BERT_PSZ_MASK   0x000C0000
DECL|macro|IXGB_XPCSTC_BERT_PSZ_SHIFT
mdefine_line|#define IXGB_XPCSTC_BERT_PSZ_SHIFT  17
DECL|macro|IXGB_XPCSTC_BERT_PSZ_INF
mdefine_line|#define IXGB_XPCSTC_BERT_PSZ_INF    0x00000003
DECL|macro|IXGB_XPCSTC_BERT_PSZ_68
mdefine_line|#define IXGB_XPCSTC_BERT_PSZ_68     0x00000001
DECL|macro|IXGB_XPCSTC_BERT_PSZ_1028
mdefine_line|#define IXGB_XPCSTC_BERT_PSZ_1028   0x00000000
multiline_comment|/* MSCA bit Masks */
multiline_comment|/* New Protocol Address */
DECL|macro|IXGB_MSCA_NP_ADDR_MASK
mdefine_line|#define IXGB_MSCA_NP_ADDR_MASK      0x0000FFFF
DECL|macro|IXGB_MSCA_NP_ADDR_SHIFT
mdefine_line|#define IXGB_MSCA_NP_ADDR_SHIFT     0
multiline_comment|/* Either Device Type or Register Address,depending on ST_CODE */
DECL|macro|IXGB_MSCA_DEV_TYPE_MASK
mdefine_line|#define IXGB_MSCA_DEV_TYPE_MASK     0x001F0000
DECL|macro|IXGB_MSCA_DEV_TYPE_SHIFT
mdefine_line|#define IXGB_MSCA_DEV_TYPE_SHIFT    16
DECL|macro|IXGB_MSCA_PHY_ADDR_MASK
mdefine_line|#define IXGB_MSCA_PHY_ADDR_MASK     0x03E00000
DECL|macro|IXGB_MSCA_PHY_ADDR_SHIFT
mdefine_line|#define IXGB_MSCA_PHY_ADDR_SHIFT    21
DECL|macro|IXGB_MSCA_OP_CODE_MASK
mdefine_line|#define IXGB_MSCA_OP_CODE_MASK      0x0C000000
multiline_comment|/* OP_CODE == 00, Address cycle, New Protocol           */
multiline_comment|/* OP_CODE == 01, Write operation                       */
multiline_comment|/* OP_CODE == 10, Read operation                        */
multiline_comment|/* OP_CODE == 11, Read, auto increment, New Protocol    */
DECL|macro|IXGB_MSCA_ADDR_CYCLE
mdefine_line|#define IXGB_MSCA_ADDR_CYCLE        0x00000000
DECL|macro|IXGB_MSCA_WRITE
mdefine_line|#define IXGB_MSCA_WRITE             0x04000000
DECL|macro|IXGB_MSCA_READ
mdefine_line|#define IXGB_MSCA_READ              0x08000000
DECL|macro|IXGB_MSCA_READ_AUTOINC
mdefine_line|#define IXGB_MSCA_READ_AUTOINC      0x0C000000
DECL|macro|IXGB_MSCA_OP_CODE_SHIFT
mdefine_line|#define IXGB_MSCA_OP_CODE_SHIFT     26
DECL|macro|IXGB_MSCA_ST_CODE_MASK
mdefine_line|#define IXGB_MSCA_ST_CODE_MASK      0x30000000
multiline_comment|/* ST_CODE == 00, New Protocol  */
multiline_comment|/* ST_CODE == 01, Old Protocol  */
DECL|macro|IXGB_MSCA_NEW_PROTOCOL
mdefine_line|#define IXGB_MSCA_NEW_PROTOCOL      0x00000000
DECL|macro|IXGB_MSCA_OLD_PROTOCOL
mdefine_line|#define IXGB_MSCA_OLD_PROTOCOL      0x10000000
DECL|macro|IXGB_MSCA_ST_CODE_SHIFT
mdefine_line|#define IXGB_MSCA_ST_CODE_SHIFT     28
multiline_comment|/* Initiate command, self-clearing when command completes */
DECL|macro|IXGB_MSCA_MDI_COMMAND
mdefine_line|#define IXGB_MSCA_MDI_COMMAND       0x40000000
multiline_comment|/*MDI In Progress Enable. */
DECL|macro|IXGB_MSCA_MDI_IN_PROG_EN
mdefine_line|#define IXGB_MSCA_MDI_IN_PROG_EN    0x80000000
multiline_comment|/* MSRWD bit masks */
DECL|macro|IXGB_MSRWD_WRITE_DATA_MASK
mdefine_line|#define IXGB_MSRWD_WRITE_DATA_MASK  0x0000FFFF
DECL|macro|IXGB_MSRWD_WRITE_DATA_SHIFT
mdefine_line|#define IXGB_MSRWD_WRITE_DATA_SHIFT 0
DECL|macro|IXGB_MSRWD_READ_DATA_MASK
mdefine_line|#define IXGB_MSRWD_READ_DATA_MASK   0xFFFF0000
DECL|macro|IXGB_MSRWD_READ_DATA_SHIFT
mdefine_line|#define IXGB_MSRWD_READ_DATA_SHIFT  16
multiline_comment|/* Definitions for the optics devices on the MDIO bus. */
DECL|macro|IXGB_PHY_ADDRESS
mdefine_line|#define IXGB_PHY_ADDRESS             0x0&t;/* Single PHY, multiple &quot;Devices&quot; */
multiline_comment|/* Standard five-bit Device IDs.  See IEEE 802.3ae, clause 45 */
DECL|macro|MDIO_PMA_PMD_DID
mdefine_line|#define MDIO_PMA_PMD_DID        0x01
DECL|macro|MDIO_WIS_DID
mdefine_line|#define MDIO_WIS_DID            0x02
DECL|macro|MDIO_PCS_DID
mdefine_line|#define MDIO_PCS_DID            0x03
DECL|macro|MDIO_XGXS_DID
mdefine_line|#define MDIO_XGXS_DID           0x04
multiline_comment|/* Standard PMA/PMD registers and bit definitions. */
multiline_comment|/* Note: This is a very limited set of definitions,      */
multiline_comment|/* only implemented features are defined.                */
DECL|macro|MDIO_PMA_PMD_CR1
mdefine_line|#define MDIO_PMA_PMD_CR1        0x0000
DECL|macro|MDIO_PMA_PMD_CR1_RESET
mdefine_line|#define MDIO_PMA_PMD_CR1_RESET  0x8000
DECL|macro|MDIO_PMA_PMD_XPAK_VENDOR_NAME
mdefine_line|#define MDIO_PMA_PMD_XPAK_VENDOR_NAME       0x803A&t;/* XPAK/XENPAK devices only */
multiline_comment|/* Vendor-specific MDIO registers */
DECL|macro|G6XXX_PMA_PMD_VS1
mdefine_line|#define G6XXX_PMA_PMD_VS1                   0xC001&t;/* Vendor-specific register */
DECL|macro|G6XXX_XGXS_XAUI_VS2
mdefine_line|#define G6XXX_XGXS_XAUI_VS2                 0x18&t;/* Vendor-specific register */
DECL|macro|G6XXX_PMA_PMD_VS1_PLL_RESET
mdefine_line|#define G6XXX_PMA_PMD_VS1_PLL_RESET         0x80
DECL|macro|G6XXX_PMA_PMD_VS1_REMOVE_PLL_RESET
mdefine_line|#define G6XXX_PMA_PMD_VS1_REMOVE_PLL_RESET  0x00
DECL|macro|G6XXX_XGXS_XAUI_VS2_INPUT_MASK
mdefine_line|#define G6XXX_XGXS_XAUI_VS2_INPUT_MASK      0x0F&t;/* XAUI lanes synchronized */
multiline_comment|/* Layout of a single receive descriptor.  The controller assumes that this&n; * structure is packed into 16 bytes, which is a safe assumption with most&n; * compilers.  However, some compilers may insert padding between the fields,&n; * in which case the structure must be packed in some compiler-specific&n; * manner. */
DECL|struct|ixgb_rx_desc
r_struct
id|ixgb_rx_desc
(brace
DECL|member|buff_addr
r_uint64
id|buff_addr
suffix:semicolon
DECL|member|length
r_uint16
id|length
suffix:semicolon
DECL|member|reserved
r_uint16
id|reserved
suffix:semicolon
DECL|member|status
r_uint8
id|status
suffix:semicolon
DECL|member|errors
r_uint8
id|errors
suffix:semicolon
DECL|member|special
r_uint16
id|special
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IXGB_RX_DESC_STATUS_DD
mdefine_line|#define IXGB_RX_DESC_STATUS_DD    0x01
DECL|macro|IXGB_RX_DESC_STATUS_EOP
mdefine_line|#define IXGB_RX_DESC_STATUS_EOP   0x02
DECL|macro|IXGB_RX_DESC_STATUS_IXSM
mdefine_line|#define IXGB_RX_DESC_STATUS_IXSM  0x04
DECL|macro|IXGB_RX_DESC_STATUS_VP
mdefine_line|#define IXGB_RX_DESC_STATUS_VP    0x08
DECL|macro|IXGB_RX_DESC_STATUS_TCPCS
mdefine_line|#define IXGB_RX_DESC_STATUS_TCPCS 0x20
DECL|macro|IXGB_RX_DESC_STATUS_IPCS
mdefine_line|#define IXGB_RX_DESC_STATUS_IPCS  0x40
DECL|macro|IXGB_RX_DESC_STATUS_PIF
mdefine_line|#define IXGB_RX_DESC_STATUS_PIF   0x80
DECL|macro|IXGB_RX_DESC_ERRORS_CE
mdefine_line|#define IXGB_RX_DESC_ERRORS_CE   0x01
DECL|macro|IXGB_RX_DESC_ERRORS_SE
mdefine_line|#define IXGB_RX_DESC_ERRORS_SE   0x02
DECL|macro|IXGB_RX_DESC_ERRORS_P
mdefine_line|#define IXGB_RX_DESC_ERRORS_P    0x08
DECL|macro|IXGB_RX_DESC_ERRORS_TCPE
mdefine_line|#define IXGB_RX_DESC_ERRORS_TCPE 0x20
DECL|macro|IXGB_RX_DESC_ERRORS_IPE
mdefine_line|#define IXGB_RX_DESC_ERRORS_IPE  0x40
DECL|macro|IXGB_RX_DESC_ERRORS_RXE
mdefine_line|#define IXGB_RX_DESC_ERRORS_RXE  0x80
DECL|macro|IXGB_RX_DESC_SPECIAL_VLAN_MASK
mdefine_line|#define IXGB_RX_DESC_SPECIAL_VLAN_MASK  0x0FFF&t;/* VLAN ID is in lower 12 bits */
DECL|macro|IXGB_RX_DESC_SPECIAL_PRI_MASK
mdefine_line|#define IXGB_RX_DESC_SPECIAL_PRI_MASK   0xE000&t;/* Priority is in upper 3 bits */
DECL|macro|IXGB_RX_DESC_SPECIAL_PRI_SHIFT
mdefine_line|#define IXGB_RX_DESC_SPECIAL_PRI_SHIFT  0x000D&t;/* Priority is in upper 3 of 16 */
multiline_comment|/* Layout of a single transmit descriptor.  The controller assumes that this&n; * structure is packed into 16 bytes, which is a safe assumption with most&n; * compilers.  However, some compilers may insert padding between the fields,&n; * in which case the structure must be packed in some compiler-specific&n; * manner. */
DECL|struct|ixgb_tx_desc
r_struct
id|ixgb_tx_desc
(brace
DECL|member|buff_addr
r_uint64
id|buff_addr
suffix:semicolon
DECL|member|cmd_type_len
r_uint32
id|cmd_type_len
suffix:semicolon
DECL|member|status
r_uint8
id|status
suffix:semicolon
DECL|member|popts
r_uint8
id|popts
suffix:semicolon
DECL|member|vlan
r_uint16
id|vlan
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IXGB_TX_DESC_LENGTH_MASK
mdefine_line|#define IXGB_TX_DESC_LENGTH_MASK    0x000FFFFF
DECL|macro|IXGB_TX_DESC_TYPE_MASK
mdefine_line|#define IXGB_TX_DESC_TYPE_MASK      0x00F00000
DECL|macro|IXGB_TX_DESC_TYPE_SHIFT
mdefine_line|#define IXGB_TX_DESC_TYPE_SHIFT     20
DECL|macro|IXGB_TX_DESC_CMD_MASK
mdefine_line|#define IXGB_TX_DESC_CMD_MASK       0xFF000000
DECL|macro|IXGB_TX_DESC_CMD_SHIFT
mdefine_line|#define IXGB_TX_DESC_CMD_SHIFT      24
DECL|macro|IXGB_TX_DESC_CMD_EOP
mdefine_line|#define IXGB_TX_DESC_CMD_EOP        0x01000000
DECL|macro|IXGB_TX_DESC_CMD_TSE
mdefine_line|#define IXGB_TX_DESC_CMD_TSE        0x04000000
DECL|macro|IXGB_TX_DESC_CMD_RS
mdefine_line|#define IXGB_TX_DESC_CMD_RS         0x08000000
DECL|macro|IXGB_TX_DESC_CMD_VLE
mdefine_line|#define IXGB_TX_DESC_CMD_VLE        0x40000000
DECL|macro|IXGB_TX_DESC_CMD_IDE
mdefine_line|#define IXGB_TX_DESC_CMD_IDE        0x80000000
DECL|macro|IXGB_TX_DESC_TYPE
mdefine_line|#define IXGB_TX_DESC_TYPE           0x00100000
DECL|macro|IXGB_TX_DESC_STATUS_DD
mdefine_line|#define IXGB_TX_DESC_STATUS_DD  0x01
DECL|macro|IXGB_TX_DESC_POPTS_IXSM
mdefine_line|#define IXGB_TX_DESC_POPTS_IXSM 0x01
DECL|macro|IXGB_TX_DESC_POPTS_TXSM
mdefine_line|#define IXGB_TX_DESC_POPTS_TXSM 0x02
DECL|macro|IXGB_TX_DESC_SPECIAL_PRI_SHIFT
mdefine_line|#define IXGB_TX_DESC_SPECIAL_PRI_SHIFT  IXGB_RX_DESC_SPECIAL_PRI_SHIFT&t;/* Priority is in upper 3 of 16 */
DECL|struct|ixgb_context_desc
r_struct
id|ixgb_context_desc
(brace
DECL|member|ipcss
r_uint8
id|ipcss
suffix:semicolon
DECL|member|ipcso
r_uint8
id|ipcso
suffix:semicolon
DECL|member|ipcse
r_uint16
id|ipcse
suffix:semicolon
DECL|member|tucss
r_uint8
id|tucss
suffix:semicolon
DECL|member|tucso
r_uint8
id|tucso
suffix:semicolon
DECL|member|tucse
r_uint16
id|tucse
suffix:semicolon
DECL|member|cmd_type_len
r_uint32
id|cmd_type_len
suffix:semicolon
DECL|member|status
r_uint8
id|status
suffix:semicolon
DECL|member|hdr_len
r_uint8
id|hdr_len
suffix:semicolon
DECL|member|mss
r_uint16
id|mss
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IXGB_CONTEXT_DESC_CMD_TCP
mdefine_line|#define IXGB_CONTEXT_DESC_CMD_TCP 0x01000000
DECL|macro|IXGB_CONTEXT_DESC_CMD_IP
mdefine_line|#define IXGB_CONTEXT_DESC_CMD_IP  0x02000000
DECL|macro|IXGB_CONTEXT_DESC_CMD_TSE
mdefine_line|#define IXGB_CONTEXT_DESC_CMD_TSE 0x04000000
DECL|macro|IXGB_CONTEXT_DESC_CMD_RS
mdefine_line|#define IXGB_CONTEXT_DESC_CMD_RS  0x08000000
DECL|macro|IXGB_CONTEXT_DESC_CMD_IDE
mdefine_line|#define IXGB_CONTEXT_DESC_CMD_IDE 0x80000000
DECL|macro|IXGB_CONTEXT_DESC_TYPE
mdefine_line|#define IXGB_CONTEXT_DESC_TYPE 0x00000000
DECL|macro|IXGB_CONTEXT_DESC_STATUS_DD
mdefine_line|#define IXGB_CONTEXT_DESC_STATUS_DD 0x01
multiline_comment|/* Filters */
DECL|macro|IXGB_MC_TBL_SIZE
mdefine_line|#define IXGB_MC_TBL_SIZE          128&t;/* Multicast Filter Table (4096 bits) */
DECL|macro|IXGB_VLAN_FILTER_TBL_SIZE
mdefine_line|#define IXGB_VLAN_FILTER_TBL_SIZE 128&t;/* VLAN Filter Table (4096 bits) */
DECL|macro|IXGB_RAR_ENTRIES
mdefine_line|#define IXGB_RAR_ENTRIES&t;&t;  3&t;/* Number of entries in Rx Address array */
DECL|macro|IXGB_MEMORY_REGISTER_BASE_ADDRESS
mdefine_line|#define IXGB_MEMORY_REGISTER_BASE_ADDRESS   0
DECL|macro|ENET_HEADER_SIZE
mdefine_line|#define ENET_HEADER_SIZE            14
DECL|macro|ENET_FCS_LENGTH
mdefine_line|#define ENET_FCS_LENGTH             4
DECL|macro|IXGB_MAX_NUM_MULTICAST_ADDRESSES
mdefine_line|#define IXGB_MAX_NUM_MULTICAST_ADDRESSES    128
DECL|macro|IXGB_MIN_ENET_FRAME_SIZE_WITHOUT_FCS
mdefine_line|#define IXGB_MIN_ENET_FRAME_SIZE_WITHOUT_FCS    60
DECL|macro|IXGB_MAX_ENET_FRAME_SIZE_WITHOUT_FCS
mdefine_line|#define IXGB_MAX_ENET_FRAME_SIZE_WITHOUT_FCS    1514
DECL|macro|IXGB_MAX_JUMBO_FRAME_SIZE
mdefine_line|#define IXGB_MAX_JUMBO_FRAME_SIZE       0x3F00
multiline_comment|/* Phy Addresses */
DECL|macro|IXGB_OPTICAL_PHY_ADDR
mdefine_line|#define IXGB_OPTICAL_PHY_ADDR 0x0&t;/* Optical Module phy address */
DECL|macro|IXGB_XAUII_PHY_ADDR
mdefine_line|#define IXGB_XAUII_PHY_ADDR   0x1&t;/* Xauii transceiver phy address */
DECL|macro|IXGB_DIAG_PHY_ADDR
mdefine_line|#define IXGB_DIAG_PHY_ADDR    0x1F&t;/* Diagnostic Device phy address */
multiline_comment|/* This structure takes a 64k flash and maps it for identification commands */
DECL|struct|ixgb_flash_buffer
r_struct
id|ixgb_flash_buffer
(brace
DECL|member|manufacturer_id
r_uint8
id|manufacturer_id
suffix:semicolon
DECL|member|device_id
r_uint8
id|device_id
suffix:semicolon
DECL|member|filler1
r_uint8
id|filler1
(braket
l_int|0x2AA8
)braket
suffix:semicolon
DECL|member|cmd2
r_uint8
id|cmd2
suffix:semicolon
DECL|member|filler2
r_uint8
id|filler2
(braket
l_int|0x2AAA
)braket
suffix:semicolon
DECL|member|cmd1
r_uint8
id|cmd1
suffix:semicolon
DECL|member|filler3
r_uint8
id|filler3
(braket
l_int|0xAAAA
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is a little-endian specific check.&n; */
DECL|macro|IS_MULTICAST
mdefine_line|#define IS_MULTICAST(Address) &bslash;&n;    (boolean_t)(((uint8_t *)(Address))[0] &amp; ((uint8_t)0x01))
multiline_comment|/*&n; * Check whether an address is broadcast.&n; */
DECL|macro|IS_BROADCAST
mdefine_line|#define IS_BROADCAST(Address)               &bslash;&n;    ((((uint8_t *)(Address))[0] == ((uint8_t)0xff)) &amp;&amp; (((uint8_t *)(Address))[1] == ((uint8_t)0xff)))
multiline_comment|/* Flow control parameters */
DECL|struct|ixgb_fc
r_struct
id|ixgb_fc
(brace
DECL|member|high_water
r_uint32
id|high_water
suffix:semicolon
multiline_comment|/* Flow Control High-water          */
DECL|member|low_water
r_uint32
id|low_water
suffix:semicolon
multiline_comment|/* Flow Control Low-water           */
DECL|member|pause_time
r_uint16
id|pause_time
suffix:semicolon
multiline_comment|/* Flow Control Pause timer         */
DECL|member|send_xon
id|boolean_t
id|send_xon
suffix:semicolon
multiline_comment|/* Flow control send XON            */
DECL|member|type
id|ixgb_fc_type
id|type
suffix:semicolon
multiline_comment|/* Type of flow control             */
)brace
suffix:semicolon
multiline_comment|/* The historical defaults for the flow control values are given below. */
DECL|macro|FC_DEFAULT_HI_THRESH
mdefine_line|#define FC_DEFAULT_HI_THRESH        (0x8000)&t;/* 32KB */
DECL|macro|FC_DEFAULT_LO_THRESH
mdefine_line|#define FC_DEFAULT_LO_THRESH        (0x4000)&t;/* 16KB */
DECL|macro|FC_DEFAULT_TX_TIMER
mdefine_line|#define FC_DEFAULT_TX_TIMER         (0x100)&t;/* ~130 us */
multiline_comment|/* Phy definitions */
DECL|macro|IXGB_MAX_PHY_REG_ADDRESS
mdefine_line|#define IXGB_MAX_PHY_REG_ADDRESS    0xFFFF
DECL|macro|IXGB_MAX_PHY_ADDRESS
mdefine_line|#define IXGB_MAX_PHY_ADDRESS        31
DECL|macro|IXGB_MAX_PHY_DEV_TYPE
mdefine_line|#define IXGB_MAX_PHY_DEV_TYPE       31
multiline_comment|/* Bus parameters */
DECL|struct|ixgb_bus
r_struct
id|ixgb_bus
(brace
DECL|member|speed
id|ixgb_bus_speed
id|speed
suffix:semicolon
DECL|member|width
id|ixgb_bus_width
id|width
suffix:semicolon
DECL|member|type
id|ixgb_bus_type
id|type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ixgb_hw
r_struct
id|ixgb_hw
(brace
DECL|member|hw_addr
r_uint8
id|__iomem
op_star
id|hw_addr
suffix:semicolon
multiline_comment|/* Base Address of the hardware     */
DECL|member|back
r_void
op_star
id|back
suffix:semicolon
multiline_comment|/* Pointer to OS-dependent struct   */
DECL|member|fc
r_struct
id|ixgb_fc
id|fc
suffix:semicolon
multiline_comment|/* Flow control parameters          */
DECL|member|bus
r_struct
id|ixgb_bus
id|bus
suffix:semicolon
multiline_comment|/* Bus parameters                   */
DECL|member|phy_id
r_uint32
id|phy_id
suffix:semicolon
multiline_comment|/* Phy Identifier                   */
DECL|member|phy_addr
r_uint32
id|phy_addr
suffix:semicolon
multiline_comment|/* XGMII address of Phy             */
DECL|member|mac_type
id|ixgb_mac_type
id|mac_type
suffix:semicolon
multiline_comment|/* Identifier for MAC controller    */
DECL|member|phy_type
id|ixgb_phy_type
id|phy_type
suffix:semicolon
multiline_comment|/* Transceiver/phy identifier       */
DECL|member|max_frame_size
r_uint32
id|max_frame_size
suffix:semicolon
multiline_comment|/* Maximum frame size supported     */
DECL|member|mc_filter_type
r_uint32
id|mc_filter_type
suffix:semicolon
multiline_comment|/* Multicast filter hash type       */
DECL|member|num_mc_addrs
r_uint32
id|num_mc_addrs
suffix:semicolon
multiline_comment|/* Number of current Multicast addrs */
DECL|member|curr_mac_addr
r_uint8
id|curr_mac_addr
(braket
id|IXGB_ETH_LENGTH_OF_ADDRESS
)braket
suffix:semicolon
multiline_comment|/* Individual address currently programmed in MAC */
DECL|member|num_tx_desc
r_uint32
id|num_tx_desc
suffix:semicolon
multiline_comment|/* Number of Transmit descriptors   */
DECL|member|num_rx_desc
r_uint32
id|num_rx_desc
suffix:semicolon
multiline_comment|/* Number of Receive descriptors    */
DECL|member|rx_buffer_size
r_uint32
id|rx_buffer_size
suffix:semicolon
multiline_comment|/* Size of Receive buffer           */
DECL|member|link_up
id|boolean_t
id|link_up
suffix:semicolon
multiline_comment|/* TRUE if link is valid            */
DECL|member|adapter_stopped
id|boolean_t
id|adapter_stopped
suffix:semicolon
multiline_comment|/* State of adapter                 */
DECL|member|device_id
r_uint16
id|device_id
suffix:semicolon
multiline_comment|/* device id from PCI configuration space */
DECL|member|vendor_id
r_uint16
id|vendor_id
suffix:semicolon
multiline_comment|/* vendor id from PCI configuration space */
DECL|member|revision_id
r_uint8
id|revision_id
suffix:semicolon
multiline_comment|/* revision id from PCI configuration space */
DECL|member|subsystem_vendor_id
r_uint16
id|subsystem_vendor_id
suffix:semicolon
multiline_comment|/* subsystem vendor id from PCI configuration space */
DECL|member|subsystem_id
r_uint16
id|subsystem_id
suffix:semicolon
multiline_comment|/* subsystem id from PCI configuration space */
DECL|member|bar0
r_uint32
id|bar0
suffix:semicolon
multiline_comment|/* Base Address registers           */
DECL|member|bar1
r_uint32
id|bar1
suffix:semicolon
DECL|member|bar2
r_uint32
id|bar2
suffix:semicolon
DECL|member|bar3
r_uint32
id|bar3
suffix:semicolon
DECL|member|pci_cmd_word
r_uint16
id|pci_cmd_word
suffix:semicolon
multiline_comment|/* PCI command register id from PCI configuration space */
DECL|member|eeprom
r_uint16
id|eeprom
(braket
id|IXGB_EEPROM_SIZE
)braket
suffix:semicolon
multiline_comment|/* EEPROM contents read at init time  */
DECL|member|io_base
r_int
r_int
id|io_base
suffix:semicolon
multiline_comment|/* Our I/O mapped location */
DECL|member|lastLFC
r_uint32
id|lastLFC
suffix:semicolon
DECL|member|lastRFC
r_uint32
id|lastRFC
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Statistics reported by the hardware */
DECL|struct|ixgb_hw_stats
r_struct
id|ixgb_hw_stats
(brace
DECL|member|tprl
r_uint64
id|tprl
suffix:semicolon
DECL|member|tprh
r_uint64
id|tprh
suffix:semicolon
DECL|member|gprcl
r_uint64
id|gprcl
suffix:semicolon
DECL|member|gprch
r_uint64
id|gprch
suffix:semicolon
DECL|member|bprcl
r_uint64
id|bprcl
suffix:semicolon
DECL|member|bprch
r_uint64
id|bprch
suffix:semicolon
DECL|member|mprcl
r_uint64
id|mprcl
suffix:semicolon
DECL|member|mprch
r_uint64
id|mprch
suffix:semicolon
DECL|member|uprcl
r_uint64
id|uprcl
suffix:semicolon
DECL|member|uprch
r_uint64
id|uprch
suffix:semicolon
DECL|member|vprcl
r_uint64
id|vprcl
suffix:semicolon
DECL|member|vprch
r_uint64
id|vprch
suffix:semicolon
DECL|member|jprcl
r_uint64
id|jprcl
suffix:semicolon
DECL|member|jprch
r_uint64
id|jprch
suffix:semicolon
DECL|member|gorcl
r_uint64
id|gorcl
suffix:semicolon
DECL|member|gorch
r_uint64
id|gorch
suffix:semicolon
DECL|member|torl
r_uint64
id|torl
suffix:semicolon
DECL|member|torh
r_uint64
id|torh
suffix:semicolon
DECL|member|rnbc
r_uint64
id|rnbc
suffix:semicolon
DECL|member|ruc
r_uint64
id|ruc
suffix:semicolon
DECL|member|roc
r_uint64
id|roc
suffix:semicolon
DECL|member|rlec
r_uint64
id|rlec
suffix:semicolon
DECL|member|crcerrs
r_uint64
id|crcerrs
suffix:semicolon
DECL|member|icbc
r_uint64
id|icbc
suffix:semicolon
DECL|member|ecbc
r_uint64
id|ecbc
suffix:semicolon
DECL|member|mpc
r_uint64
id|mpc
suffix:semicolon
DECL|member|tptl
r_uint64
id|tptl
suffix:semicolon
DECL|member|tpth
r_uint64
id|tpth
suffix:semicolon
DECL|member|gptcl
r_uint64
id|gptcl
suffix:semicolon
DECL|member|gptch
r_uint64
id|gptch
suffix:semicolon
DECL|member|bptcl
r_uint64
id|bptcl
suffix:semicolon
DECL|member|bptch
r_uint64
id|bptch
suffix:semicolon
DECL|member|mptcl
r_uint64
id|mptcl
suffix:semicolon
DECL|member|mptch
r_uint64
id|mptch
suffix:semicolon
DECL|member|uptcl
r_uint64
id|uptcl
suffix:semicolon
DECL|member|uptch
r_uint64
id|uptch
suffix:semicolon
DECL|member|vptcl
r_uint64
id|vptcl
suffix:semicolon
DECL|member|vptch
r_uint64
id|vptch
suffix:semicolon
DECL|member|jptcl
r_uint64
id|jptcl
suffix:semicolon
DECL|member|jptch
r_uint64
id|jptch
suffix:semicolon
DECL|member|gotcl
r_uint64
id|gotcl
suffix:semicolon
DECL|member|gotch
r_uint64
id|gotch
suffix:semicolon
DECL|member|totl
r_uint64
id|totl
suffix:semicolon
DECL|member|toth
r_uint64
id|toth
suffix:semicolon
DECL|member|dc
r_uint64
id|dc
suffix:semicolon
DECL|member|plt64c
r_uint64
id|plt64c
suffix:semicolon
DECL|member|tsctc
r_uint64
id|tsctc
suffix:semicolon
DECL|member|tsctfc
r_uint64
id|tsctfc
suffix:semicolon
DECL|member|ibic
r_uint64
id|ibic
suffix:semicolon
DECL|member|rfc
r_uint64
id|rfc
suffix:semicolon
DECL|member|lfc
r_uint64
id|lfc
suffix:semicolon
DECL|member|pfrc
r_uint64
id|pfrc
suffix:semicolon
DECL|member|pftc
r_uint64
id|pftc
suffix:semicolon
DECL|member|mcfrc
r_uint64
id|mcfrc
suffix:semicolon
DECL|member|mcftc
r_uint64
id|mcftc
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
DECL|member|rjc
r_uint64
id|rjc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Function Prototypes */
r_extern
id|boolean_t
id|ixgb_adapter_stop
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_extern
id|boolean_t
id|ixgb_init_hw
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_extern
id|boolean_t
id|ixgb_adapter_start
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_extern
r_void
id|ixgb_init_rx_addrs
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_extern
r_void
id|ixgb_check_for_link
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_extern
id|boolean_t
id|ixgb_check_for_bad_link
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_extern
id|boolean_t
id|ixgb_setup_fc
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_extern
r_void
id|ixgb_clear_hw_cntrs
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_extern
id|boolean_t
id|mac_addr_valid
c_func
(paren
r_uint8
op_star
id|mac_addr
)paren
suffix:semicolon
r_extern
r_uint16
id|ixgb_read_phy_reg
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint32
id|reg_addr
comma
r_uint32
id|phy_addr
comma
r_uint32
id|device_type
)paren
suffix:semicolon
r_extern
r_void
id|ixgb_write_phy_reg
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint32
id|reg_addr
comma
r_uint32
id|phy_addr
comma
r_uint32
id|device_type
comma
r_uint16
id|data
)paren
suffix:semicolon
r_extern
r_void
id|ixgb_rar_set
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint8
op_star
id|addr
comma
r_uint32
id|index
)paren
suffix:semicolon
multiline_comment|/* Filters (multicast, vlan, receive) */
r_extern
r_void
id|ixgb_mc_addr_list_update
c_func
(paren
r_struct
id|ixgb_hw
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
multiline_comment|/* Vfta functions */
r_extern
r_void
id|ixgb_write_vfta
c_func
(paren
r_struct
id|ixgb_hw
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
r_extern
r_void
id|ixgb_clear_vfta
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
multiline_comment|/* Access functions to eeprom data */
r_void
id|ixgb_get_ee_mac_addr
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint8
op_star
id|mac_addr
)paren
suffix:semicolon
r_uint16
id|ixgb_get_ee_compatibility
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_uint32
id|ixgb_get_ee_pba_number
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_uint16
id|ixgb_get_ee_init_ctrl_reg_1
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_uint16
id|ixgb_get_ee_init_ctrl_reg_2
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_uint16
id|ixgb_get_ee_subsystem_id
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_uint16
id|ixgb_get_ee_subvendor_id
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_uint16
id|ixgb_get_ee_device_id
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_uint16
id|ixgb_get_ee_vendor_id
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_uint16
id|ixgb_get_ee_swdpins_reg
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_uint8
id|ixgb_get_ee_d3_power
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_uint8
id|ixgb_get_ee_d0_power
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
id|boolean_t
id|ixgb_get_eeprom_data
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_uint16
id|ixgb_get_eeprom_word
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint16
id|index
)paren
suffix:semicolon
multiline_comment|/* Everything else */
r_void
id|ixgb_led_on
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_void
id|ixgb_led_off
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_void
id|ixgb_write_pci_cfg
c_func
(paren
r_struct
id|ixgb_hw
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
macro_line|#endif&t;&t;&t;&t;/* _IXGB_HW_H_ */
eof
