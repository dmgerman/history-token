multiline_comment|/*******************************************************************************&n;&n;  &n;  Copyright(c) 1999 - 2004 Intel Corporation. All rights reserved.&n;  &n;  This program is free software; you can redistribute it and/or modify it &n;  under the terms of the GNU General Public License as published by the Free &n;  Software Foundation; either version 2 of the License, or (at your option) &n;  any later version.&n;  &n;  This program is distributed in the hope that it will be useful, but WITHOUT &n;  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or &n;  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for &n;  more details.&n;  &n;  You should have received a copy of the GNU General Public License along with&n;  this program; if not, write to the Free Software Foundation, Inc., 59 &n;  Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n;  &n;  The full GNU General Public License is included in this distribution in the&n;  file called LICENSE.&n;  &n;  Contact Information:&n;  Linux NICS &lt;linux.nics@intel.com&gt;&n;  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497&n;&n;*******************************************************************************/
macro_line|#ifndef _IXGB_EE_H_
DECL|macro|_IXGB_EE_H_
mdefine_line|#define _IXGB_EE_H_
DECL|macro|IXGB_EEPROM_SIZE
mdefine_line|#define IXGB_EEPROM_SIZE    64&t;/* Size in words */
DECL|macro|IXGB_ETH_LENGTH_OF_ADDRESS
mdefine_line|#define IXGB_ETH_LENGTH_OF_ADDRESS   6
multiline_comment|/* EEPROM Commands */
DECL|macro|EEPROM_READ_OPCODE
mdefine_line|#define EEPROM_READ_OPCODE  0x6&t;/* EERPOM read opcode */
DECL|macro|EEPROM_WRITE_OPCODE
mdefine_line|#define EEPROM_WRITE_OPCODE 0x5&t;/* EERPOM write opcode */
DECL|macro|EEPROM_ERASE_OPCODE
mdefine_line|#define EEPROM_ERASE_OPCODE 0x7&t;/* EERPOM erase opcode */
DECL|macro|EEPROM_EWEN_OPCODE
mdefine_line|#define EEPROM_EWEN_OPCODE  0x13&t;/* EERPOM erase/write enable */
DECL|macro|EEPROM_EWDS_OPCODE
mdefine_line|#define EEPROM_EWDS_OPCODE  0x10&t;/* EERPOM erast/write disable */
multiline_comment|/* EEPROM MAP (Word Offsets) */
DECL|macro|EEPROM_IA_1_2_REG
mdefine_line|#define EEPROM_IA_1_2_REG        0x0000
DECL|macro|EEPROM_IA_3_4_REG
mdefine_line|#define EEPROM_IA_3_4_REG        0x0001
DECL|macro|EEPROM_IA_5_6_REG
mdefine_line|#define EEPROM_IA_5_6_REG        0x0002
DECL|macro|EEPROM_COMPATIBILITY_REG
mdefine_line|#define EEPROM_COMPATIBILITY_REG 0x0003
DECL|macro|EEPROM_PBA_1_2_REG
mdefine_line|#define EEPROM_PBA_1_2_REG       0x0008
DECL|macro|EEPROM_PBA_3_4_REG
mdefine_line|#define EEPROM_PBA_3_4_REG       0x0009
DECL|macro|EEPROM_INIT_CONTROL1_REG
mdefine_line|#define EEPROM_INIT_CONTROL1_REG 0x000A
DECL|macro|EEPROM_SUBSYS_ID_REG
mdefine_line|#define EEPROM_SUBSYS_ID_REG     0x000B
DECL|macro|EEPROM_SUBVEND_ID_REG
mdefine_line|#define EEPROM_SUBVEND_ID_REG    0x000C
DECL|macro|EEPROM_DEVICE_ID_REG
mdefine_line|#define EEPROM_DEVICE_ID_REG     0x000D
DECL|macro|EEPROM_VENDOR_ID_REG
mdefine_line|#define EEPROM_VENDOR_ID_REG     0x000E
DECL|macro|EEPROM_INIT_CONTROL2_REG
mdefine_line|#define EEPROM_INIT_CONTROL2_REG 0x000F
DECL|macro|EEPROM_SWDPINS_REG
mdefine_line|#define EEPROM_SWDPINS_REG       0x0020
DECL|macro|EEPROM_CIRCUIT_CTRL_REG
mdefine_line|#define EEPROM_CIRCUIT_CTRL_REG  0x0021
DECL|macro|EEPROM_D0_D3_POWER_REG
mdefine_line|#define EEPROM_D0_D3_POWER_REG   0x0022
DECL|macro|EEPROM_FLASH_VERSION
mdefine_line|#define EEPROM_FLASH_VERSION     0x0032
DECL|macro|EEPROM_CHECKSUM_REG
mdefine_line|#define EEPROM_CHECKSUM_REG      0x003F
multiline_comment|/* Mask bits for fields in Word 0x0a of the EEPROM */
DECL|macro|EEPROM_ICW1_SIGNATURE_MASK
mdefine_line|#define EEPROM_ICW1_SIGNATURE_MASK  0xC000
DECL|macro|EEPROM_ICW1_SIGNATURE_VALID
mdefine_line|#define EEPROM_ICW1_SIGNATURE_VALID 0x4000
DECL|macro|EEPROM_ICW1_SIGNATURE_CLEAR
mdefine_line|#define EEPROM_ICW1_SIGNATURE_CLEAR 0x0000
multiline_comment|/* For checksumming, the sum of all words in the EEPROM should equal 0xBABA. */
DECL|macro|EEPROM_SUM
mdefine_line|#define EEPROM_SUM 0xBABA
multiline_comment|/* EEPROM Map Sizes (Byte Counts) */
DECL|macro|PBA_SIZE
mdefine_line|#define PBA_SIZE 4
multiline_comment|/* EEPROM Map defines (WORD OFFSETS)*/
multiline_comment|/* EEPROM structure */
DECL|struct|ixgb_ee_map_type
r_struct
id|ixgb_ee_map_type
(brace
DECL|member|mac_addr
r_uint8
id|mac_addr
(braket
id|IXGB_ETH_LENGTH_OF_ADDRESS
)braket
suffix:semicolon
DECL|member|compatibility
r_uint16
id|compatibility
suffix:semicolon
DECL|member|reserved1
r_uint16
id|reserved1
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|pba_number
r_uint32
id|pba_number
suffix:semicolon
DECL|member|init_ctrl_reg_1
r_uint16
id|init_ctrl_reg_1
suffix:semicolon
DECL|member|subsystem_id
r_uint16
id|subsystem_id
suffix:semicolon
DECL|member|subvendor_id
r_uint16
id|subvendor_id
suffix:semicolon
DECL|member|device_id
r_uint16
id|device_id
suffix:semicolon
DECL|member|vendor_id
r_uint16
id|vendor_id
suffix:semicolon
DECL|member|init_ctrl_reg_2
r_uint16
id|init_ctrl_reg_2
suffix:semicolon
DECL|member|oem_reserved
r_uint16
id|oem_reserved
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|swdpins_reg
r_uint16
id|swdpins_reg
suffix:semicolon
DECL|member|circuit_ctrl_reg
r_uint16
id|circuit_ctrl_reg
suffix:semicolon
DECL|member|d3_power
r_uint8
id|d3_power
suffix:semicolon
DECL|member|d0_power
r_uint8
id|d0_power
suffix:semicolon
DECL|member|reserved2
r_uint16
id|reserved2
(braket
l_int|28
)braket
suffix:semicolon
DECL|member|checksum
r_uint16
id|checksum
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* EEPROM Functions */
r_uint16
id|ixgb_read_eeprom
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint16
id|reg
)paren
suffix:semicolon
id|boolean_t
id|ixgb_validate_eeprom_checksum
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_void
id|ixgb_update_eeprom_checksum
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_void
id|ixgb_write_eeprom
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint16
id|reg
comma
r_uint16
id|data
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* IXGB_EE_H */
eof
