multiline_comment|/*+M*************************************************************************&n; * Perceptive Solutions, Inc. PSI-240I device driver proc support for Linux.&n; *&n; * Copyright (c) 1997 Perceptive Solutions, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *&n; *&t;File Name:&t;psi_chip.h&n; *&n; *&t;Description:&t;This file contains the interface defines and&n; *&t;&t;&t;&t;&t;error codes.&n; *&n; *-M*************************************************************************/
macro_line|#ifndef PSI_CHIP
DECL|macro|PSI_CHIP
mdefine_line|#define PSI_CHIP
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Misc konstants&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|CHIP_MAXDRIVES
mdefine_line|#define&t;CHIP_MAXDRIVES&t;&t;&t;8
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Chip I/O addresses&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|CHIP_ADRS_0
mdefine_line|#define&t;CHIP_ADRS_0&t;&t;&t;&t;0x0130
DECL|macro|CHIP_ADRS_1
mdefine_line|#define&t;CHIP_ADRS_1&t;&t;&t;&t;0x0150
DECL|macro|CHIP_ADRS_2
mdefine_line|#define&t;CHIP_ADRS_2&t;&t;&t;&t;0x0190
DECL|macro|CHIP_ADRS_3
mdefine_line|#define&t;CHIP_ADRS_3&t;&t;&t;&t;0x0210
DECL|macro|CHIP_ADRS_4
mdefine_line|#define&t;CHIP_ADRS_4&t;&t;&t;&t;0x0230
DECL|macro|CHIP_ADRS_5
mdefine_line|#define&t;CHIP_ADRS_5&t;&t;&t;&t;0x0250
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;EEPROM locations&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|CHIP_EEPROM_BIOS
mdefine_line|#define&t;CHIP_EEPROM_BIOS&t;&t;0x0000&t;&t;
singleline_comment|// BIOS base address
DECL|macro|CHIP_EEPROM_DATA
mdefine_line|#define&t;CHIP_EEPROM_DATA&t;&t;0x2000&t;   &t;
singleline_comment|// SETUP data base address
DECL|macro|CHIP_EEPROM_FACTORY
mdefine_line|#define&t;CHIP_EEPROM_FACTORY&t;&t;0x2400&t;   &t;
singleline_comment|// FACTORY data base address
DECL|macro|CHIP_EEPROM_SETUP
mdefine_line|#define&t;CHIP_EEPROM_SETUP&t;&t;0x3000&t;   &t;
singleline_comment|// SETUP PROGRAM base address
DECL|macro|CHIP_EEPROM_SIZE
mdefine_line|#define&t;CHIP_EEPROM_SIZE&t;&t;32768U&t;   &t;
singleline_comment|// size of the entire EEPROM
DECL|macro|CHIP_EEPROM_BIOS_SIZE
mdefine_line|#define&t;CHIP_EEPROM_BIOS_SIZE&t;8192&t;   &t;
singleline_comment|// size of the BIOS in bytes
DECL|macro|CHIP_EEPROM_DATA_SIZE
mdefine_line|#define&t;CHIP_EEPROM_DATA_SIZE&t;4096&t;   &t;
singleline_comment|// size of factory, setup, log data block in bytes
DECL|macro|CHIP_EEPROM_SETUP_SIZE
mdefine_line|#define&t;CHIP_EEPROM_SETUP_SIZE&t;20480U&t;   &t;
singleline_comment|// size of the setup program in bytes
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Chip Interrupts&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|CHIP_IRQ_10
mdefine_line|#define&t;CHIP_IRQ_10&t;&t;&t;&t;0x72
DECL|macro|CHIP_IRQ_11
mdefine_line|#define&t;CHIP_IRQ_11&t;&t;&t;&t;0x73
DECL|macro|CHIP_IRQ_12
mdefine_line|#define&t;CHIP_IRQ_12&t;&t;&t;&t;0x74
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Chip Setup addresses&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|CHIP_SETUP_BASE
mdefine_line|#define&t;CHIP_SETUP_BASE&t;&t;&t;0x0000C000L
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Chip Register address offsets&t;*/
multiline_comment|/************************************************/
DECL|macro|REG_DATA
mdefine_line|#define&t;REG_DATA&t;&t;&t;&t;0x00
DECL|macro|REG_ERROR
mdefine_line|#define&t;REG_ERROR&t;&t;&t;&t;0x01
DECL|macro|REG_SECTOR_COUNT
mdefine_line|#define&t;REG_SECTOR_COUNT&t;&t;0x02
DECL|macro|REG_LBA_0
mdefine_line|#define&t;REG_LBA_0&t;&t;&t;&t;0x03
DECL|macro|REG_LBA_8
mdefine_line|#define&t;REG_LBA_8&t;&t;&t;&t;0x04
DECL|macro|REG_LBA_16
mdefine_line|#define&t;REG_LBA_16&t;&t;&t;&t;0x05
DECL|macro|REG_LBA_24
mdefine_line|#define&t;REG_LBA_24&t;&t;&t;&t;0x06
DECL|macro|REG_STAT_CMD
mdefine_line|#define&t;REG_STAT_CMD&t;&t;&t;0x07
DECL|macro|REG_SEL_FAIL
mdefine_line|#define&t;REG_SEL_FAIL&t;&t;&t;0x08
DECL|macro|REG_IRQ_STATUS
mdefine_line|#define&t;REG_IRQ_STATUS&t;&t;&t;0x09
DECL|macro|REG_ADDRESS
mdefine_line|#define&t;REG_ADDRESS&t;&t;&t;&t;0x0A
DECL|macro|REG_FAIL
mdefine_line|#define&t;REG_FAIL&t;&t;&t;&t;0x0C
DECL|macro|REG_ALT_STAT
mdefine_line|#define&t;REG_ALT_STAT&t;&t;   &t;0x0E
DECL|macro|REG_DRIVE_ADRS
mdefine_line|#define&t;REG_DRIVE_ADRS&t;&t;&t;0x0F
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Chip RAM locations&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|CHIP_DEVICE
mdefine_line|#define&t;CHIP_DEVICE&t;&t;&t;&t;0x8000
DECL|macro|CHIP_DEVICE_0
mdefine_line|#define&t;CHIP_DEVICE_0&t;&t;&t;0x8000
DECL|macro|CHIP_DEVICE_1
mdefine_line|#define CHIP_DEVICE_1&t;&t;&t;0x8008
DECL|macro|CHIP_DEVICE_2
mdefine_line|#define&t;CHIP_DEVICE_2&t;&t;&t;0x8010
DECL|macro|CHIP_DEVICE_3
mdefine_line|#define&t;CHIP_DEVICE_3&t;&t;&t;0x8018
DECL|macro|CHIP_DEVICE_4
mdefine_line|#define&t;CHIP_DEVICE_4&t;&t;&t;0x8020
DECL|macro|CHIP_DEVICE_5
mdefine_line|#define&t;CHIP_DEVICE_5&t;&t;&t;0x8028
DECL|macro|CHIP_DEVICE_6
mdefine_line|#define&t;CHIP_DEVICE_6&t;&t;&t;0x8030
DECL|macro|CHIP_DEVICE_7
mdefine_line|#define&t;CHIP_DEVICE_7&t;&t;&t;0x8038
r_typedef
r_struct
(brace
DECL|member|channel
id|UCHAR
id|channel
suffix:semicolon
singleline_comment|// channel of this device (0-8).
DECL|member|spt
id|UCHAR
id|spt
suffix:semicolon
singleline_comment|// Sectors Per Track.
DECL|member|spc
id|ULONG
id|spc
suffix:semicolon
singleline_comment|// Sectors Per Cylinder.
DECL|typedef|CHIP_DEVICE_N
)brace
id|CHIP_DEVICE_N
suffix:semicolon
DECL|macro|CHIP_CONFIG
mdefine_line|#define&t;CHIP_CONFIG&t;&t;&t;&t;0x8100&t;&t;
singleline_comment|// address of boards configuration.
r_typedef
r_struct
(brace
DECL|member|irq
id|UCHAR
id|irq
suffix:semicolon
singleline_comment|// interrupt request channel number
DECL|member|numDrives
id|UCHAR
id|numDrives
suffix:semicolon
singleline_comment|// Number of accessable drives
DECL|member|fastFormat
id|UCHAR
id|fastFormat
suffix:semicolon
singleline_comment|// Boolean for fast format enable
DECL|typedef|CHIP_CONFIG_N
)brace
id|CHIP_CONFIG_N
suffix:semicolon
DECL|macro|CHIP_MAP
mdefine_line|#define&t;CHIP_MAP&t;&t;&t;&t;0x8108 &t;&t;
singleline_comment|// eight byte device type map.
DECL|macro|CHIP_RAID
mdefine_line|#define&t;CHIP_RAID&t;&t;&t;&t;0x8120 &t;&t;
singleline_comment|// array of RAID signature structures and LBA
DECL|macro|CHIP_RAID_1
mdefine_line|#define&t;CHIP_RAID_1&t;&t;&t;&t;0x8120
DECL|macro|CHIP_RAID_2
mdefine_line|#define CHIP_RAID_2&t;&t;&t;&t;0x8130
DECL|macro|CHIP_RAID_3
mdefine_line|#define&t;CHIP_RAID_3&t;&t;&t;&t;0x8140
DECL|macro|CHIP_RAID_4
mdefine_line|#define&t;CHIP_RAID_4&t;&t;&t;&t;0x8150
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Chip Register Masks&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|CHIP_ID
mdefine_line|#define&t;CHIP_ID&t;&t;&t;&t;&t;0x7B
DECL|macro|SEL_RAM
mdefine_line|#define&t;SEL_RAM&t;&t;&t;&t;&t;0x8000
DECL|macro|MASK_FAIL
mdefine_line|#define&t;MASK_FAIL&t;&t;&t;&t;0x80
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Chip cable select bits&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|SECTORSXFER
mdefine_line|#define&t;SECTORSXFER&t;&t;&t;&t;8
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Chip cable select bits&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|SEL_NONE
mdefine_line|#define&t;SEL_NONE&t;&t;&t;&t;0x00
DECL|macro|SEL_1
mdefine_line|#define&t;SEL_1&t;&t;&t;&t;&t;0x01
DECL|macro|SEL_2
mdefine_line|#define&t;SEL_2&t;&t;&t;&t;&t;0x02
DECL|macro|SEL_3
mdefine_line|#define&t;SEL_3&t;&t;&t;&t;&t;0x04
DECL|macro|SEL_4
mdefine_line|#define&t;SEL_4&t;&t;&t;&t;&t;0x08
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Programmable Interrupt Controller*/
multiline_comment|/************************************************/
DECL|macro|PIC1
mdefine_line|#define&t;PIC1&t;&t;&t;&t;&t;0x20&t;&t;
singleline_comment|// first 8259 base port address
DECL|macro|PIC2
mdefine_line|#define&t;PIC2&t;&t;&t;&t;&t;0xA0&t;&t;
singleline_comment|// second 8259 base port address
DECL|macro|INT_OCW1
mdefine_line|#define&t;INT_OCW1&t;&t;&t;&t;1&t;&t;&t;
singleline_comment|// Operation Control Word 1: IRQ mask
DECL|macro|EOI
mdefine_line|#define&t;EOI&t;&t;&t;&t;&t;&t;0x20&t;&t;
singleline_comment|// non-specific end-of-interrupt
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Device/Geometry controls&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|GEOMETRY_NONE
mdefine_line|#define GEOMETRY_NONE&t;&t; &t;0x0&t;&t;&t;
singleline_comment|// No device
DECL|macro|GEOMETRY_AUTO
mdefine_line|#define GEOMETRY_AUTO&t;&t;&t;0x1&t;&t;&t;
singleline_comment|// Geometry set automatically
DECL|macro|GEOMETRY_USER
mdefine_line|#define GEOMETRY_USER&t;&t; &t;0x2&t;&t;&t;
singleline_comment|// User supplied geometry
DECL|macro|DEVICE_NONE
mdefine_line|#define&t;DEVICE_NONE&t;&t;&t;&t;0x0&t;&t;&t;
singleline_comment|// No device present
DECL|macro|DEVICE_INACTIVE
mdefine_line|#define&t;DEVICE_INACTIVE&t;&t;&t;0x1&t;&t;&t;
singleline_comment|// device present but not registered active
DECL|macro|DEVICE_ATAPI
mdefine_line|#define&t;DEVICE_ATAPI&t;&t;&t;0x2&t;&t;&t;
singleline_comment|// ATAPI device (CD_ROM, Tape, Etc...)
DECL|macro|DEVICE_DASD_NONLBA
mdefine_line|#define&t;DEVICE_DASD_NONLBA&t;&t;0x3&t;&t;&t;
singleline_comment|// Non LBA incompatible device
DECL|macro|DEVICE_DASD_LBA
mdefine_line|#define&t;DEVICE_DASD_LBA&t;&t;&t;0x4&t;&t;&t;
singleline_comment|// LBA compatible device
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Setup Structure Definitions&t;*/
multiline_comment|/************************************************/
r_typedef
r_struct
singleline_comment|// device setup parameters
(brace
DECL|member|geometryControl
id|UCHAR
id|geometryControl
suffix:semicolon
singleline_comment|// geometry control flags
DECL|member|device
id|UCHAR
id|device
suffix:semicolon
singleline_comment|// device code
DECL|member|sectors
id|USHORT
id|sectors
suffix:semicolon
singleline_comment|// number of sectors per track
DECL|member|heads
id|USHORT
id|heads
suffix:semicolon
singleline_comment|// number of heads
DECL|member|cylinders
id|USHORT
id|cylinders
suffix:semicolon
singleline_comment|// number of cylinders for this device
DECL|member|blocks
id|ULONG
id|blocks
suffix:semicolon
singleline_comment|// number of blocks on device
DECL|member|spare1
id|USHORT
id|spare1
suffix:semicolon
DECL|member|spare2
id|USHORT
id|spare2
suffix:semicolon
DECL|typedef|SETUP_DEVICE
DECL|typedef|PSETUP_DEVICE
)brace
id|SETUP_DEVICE
comma
op_star
id|PSETUP_DEVICE
suffix:semicolon
r_typedef
r_struct
singleline_comment|// master setup structure
(brace
DECL|member|startupDelay
id|USHORT
id|startupDelay
suffix:semicolon
DECL|member|promptBIOS
id|USHORT
id|promptBIOS
suffix:semicolon
DECL|member|fastFormat
id|USHORT
id|fastFormat
suffix:semicolon
DECL|member|spare2
id|USHORT
id|spare2
suffix:semicolon
DECL|member|spare3
id|USHORT
id|spare3
suffix:semicolon
DECL|member|spare4
id|USHORT
id|spare4
suffix:semicolon
DECL|member|spare5
id|USHORT
id|spare5
suffix:semicolon
DECL|member|spare6
id|USHORT
id|spare6
suffix:semicolon
DECL|member|setupDevice
id|SETUP_DEVICE
id|setupDevice
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|SETUP
DECL|typedef|PSETUP
)brace
id|SETUP
comma
op_star
id|PSETUP
suffix:semicolon
macro_line|#endif
eof
