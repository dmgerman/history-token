multiline_comment|/****************************************************************************&n; * Perceptive Solutions, Inc. PCI-2220I device driver for Linux.&n; *&n; * psi_dalei.h - Linux Host Driver for PCI-2220i EIDE Adapters&n; *&n; * Copyright (c) 1997-1999 Perceptive Solutions, Inc.&n; * All Rights Reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that redistributions of source&n; * code retain the above copyright notice and this comment without&n; * modification.&n; *&n; * Technical updates and product information at:&n; *  http://www.psidisk.com&n; *&n; * Please send questions, comments, bug reports to:&n; *  tech@psidisk.com Technical Support&n; *&n; ****************************************************************************/
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Some defines that we like &t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|CHAR
mdefine_line|#define&t;CHAR&t;&t;char
DECL|macro|UCHAR
mdefine_line|#define&t;UCHAR&t;&t;unsigned char
DECL|macro|SHORT
mdefine_line|#define&t;SHORT&t;&t;short
DECL|macro|USHORT
mdefine_line|#define&t;USHORT&t;&t;unsigned short
DECL|macro|BOOL
mdefine_line|#define&t;BOOL&t;&t;unsigned short
DECL|macro|LONG
mdefine_line|#define&t;LONG&t;&t;long
DECL|macro|ULONG
mdefine_line|#define&t;ULONG&t;&t;unsigned long
DECL|macro|VOID
mdefine_line|#define&t;VOID&t;&t;void
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Dale PCI setup&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|VENDOR_PSI
mdefine_line|#define&t;VENDOR_PSI&t;&t;&t;0x1256
DECL|macro|DEVICE_DALE_1
mdefine_line|#define&t;DEVICE_DALE_1&t;&t;0x4401&t;&t;/* &squot;D1&squot; */
DECL|macro|DEVICE_BIGD_1
mdefine_line|#define&t;DEVICE_BIGD_1&t;&t;0x4201&t;&t;/* &squot;B1&squot; */
DECL|macro|DEVICE_BIGD_2
mdefine_line|#define&t;DEVICE_BIGD_2&t;&t;0x4202&t;&t;/* &squot;B2&squot; */
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Misc konstants&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|DALE_MAXDRIVES
mdefine_line|#define&t;DALE_MAXDRIVES&t;&t;&t;4
DECL|macro|BIGD_MAXDRIVES
mdefine_line|#define&t;BIGD_MAXDRIVES&t;&t;&t;8
DECL|macro|SECTORSXFER
mdefine_line|#define&t;SECTORSXFER&t;&t;&t;&t;8
DECL|macro|ATAPI_TRANSFER
mdefine_line|#define&t;ATAPI_TRANSFER&t;&t;&t;8192
DECL|macro|BYTES_PER_SECTOR
mdefine_line|#define&t;BYTES_PER_SECTOR&t;&t;512
DECL|macro|DEFAULT_TIMING_MODE
mdefine_line|#define&t;DEFAULT_TIMING_MODE&t;&t;5
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;EEPROM locations&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|DALE_FLASH_PAGE_SIZE
mdefine_line|#define&t;DALE_FLASH_PAGE_SIZE&t;128&t;&t;&t;&t;
singleline_comment|// number of bytes per page
DECL|macro|DALE_FLASH_SIZE
mdefine_line|#define&t;DALE_FLASH_SIZE&t;&t;&t;65536L
DECL|macro|DALE_FLASH_BIOS
mdefine_line|#define&t;DALE_FLASH_BIOS&t;&t;&t;0x00080000L&t;&t;
singleline_comment|// BIOS base address
DECL|macro|DALE_FLASH_SETUP
mdefine_line|#define&t;DALE_FLASH_SETUP&t;&t;0x00088000L&t;&t;
singleline_comment|// SETUP PROGRAM base address offset from BIOS
DECL|macro|DALE_FLASH_RAID
mdefine_line|#define&t;DALE_FLASH_RAID&t;&t;&t;0x00088400L&t;&t;
singleline_comment|// RAID signature storage
DECL|macro|DALE_FLASH_FACTORY
mdefine_line|#define&t;DALE_FLASH_FACTORY&t;&t;0x00089000L&t;&t;
singleline_comment|// FACTORY data base address offset from BIOS
DECL|macro|DALE_FLASH_BIOS_SIZE
mdefine_line|#define&t;DALE_FLASH_BIOS_SIZE&t;32768U&t;&t;&t;
singleline_comment|// size of FLASH BIOS REGION
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;DALE Register address offsets&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|REG_DATA
mdefine_line|#define&t;REG_DATA&t;&t;&t;&t;&t;0x80
DECL|macro|REG_ERROR
mdefine_line|#define&t;REG_ERROR&t;&t;&t;&t;&t;0x84
DECL|macro|REG_SECTOR_COUNT
mdefine_line|#define&t;REG_SECTOR_COUNT&t;&t;&t;0x88
DECL|macro|REG_LBA_0
mdefine_line|#define&t;REG_LBA_0&t;&t;&t;&t;&t;0x8C
DECL|macro|REG_LBA_8
mdefine_line|#define&t;REG_LBA_8&t;&t;&t;&t;&t;0x90
DECL|macro|REG_LBA_16
mdefine_line|#define&t;REG_LBA_16&t;&t;&t;&t;&t;0x94
DECL|macro|REG_LBA_24
mdefine_line|#define&t;REG_LBA_24&t;&t;&t;&t;&t;0x98
DECL|macro|REG_STAT_CMD
mdefine_line|#define&t;REG_STAT_CMD&t;&t;&t;&t;0x9C
DECL|macro|REG_STAT_SEL
mdefine_line|#define&t;REG_STAT_SEL&t;&t;&t;&t;0xA0
DECL|macro|REG_FAIL
mdefine_line|#define&t;REG_FAIL&t;&t;&t;&t;&t;0xB0
DECL|macro|REG_ALT_STAT
mdefine_line|#define&t;REG_ALT_STAT&t;&t;&t;&t;0xB8
DECL|macro|REG_DRIVE_ADRS
mdefine_line|#define&t;REG_DRIVE_ADRS&t;&t;&t;&t;0xBC
DECL|macro|DALE_DATA_SLOW
mdefine_line|#define&t;DALE_DATA_SLOW&t;&t;&t;&t;0x00040000L
DECL|macro|DALE_DATA_MODE2
mdefine_line|#define&t;DALE_DATA_MODE2&t;&t;&t;&t;0x00040000L
DECL|macro|DALE_DATA_MODE3
mdefine_line|#define&t;DALE_DATA_MODE3&t;&t;&t;&t;0x00050000L
DECL|macro|DALE_DATA_MODE4
mdefine_line|#define&t;DALE_DATA_MODE4&t;&t;&t;&t;0x00060000L
DECL|macro|DALE_DATA_MODE5
mdefine_line|#define&t;DALE_DATA_MODE5&t;&t;&t;&t;0x00070000L
DECL|macro|BIGD_DATA_SLOW
mdefine_line|#define&t;BIGD_DATA_SLOW&t;&t;&t;&t;0x00000000L
DECL|macro|BIGD_DATA_MODE0
mdefine_line|#define&t;BIGD_DATA_MODE0&t;&t;&t;&t;0x00000000L
DECL|macro|BIGD_DATA_MODE2
mdefine_line|#define&t;BIGD_DATA_MODE2&t;&t;&t;&t;0x00000000L
DECL|macro|BIGD_DATA_MODE3
mdefine_line|#define&t;BIGD_DATA_MODE3&t;&t;&t;&t;0x00000008L
DECL|macro|BIGD_DATA_MODE4
mdefine_line|#define&t;BIGD_DATA_MODE4&t;&t;&t;&t;0x00000010L
DECL|macro|BIGD_DATA_MODE5
mdefine_line|#define&t;BIGD_DATA_MODE5&t;&t;&t;&t;0x00000020L
DECL|macro|RTR_LOCAL_RANGE
mdefine_line|#define RTR_LOCAL_RANGE&t;&t;&t;&t;0x000
DECL|macro|RTR_LOCAL_REMAP
mdefine_line|#define RTR_LOCAL_REMAP&t;&t;&t;&t;0x004
DECL|macro|RTR_EXP_RANGE
mdefine_line|#define RTR_EXP_RANGE&t;&t;&t;&t;0x010
DECL|macro|RTR_EXP_REMAP
mdefine_line|#define RTR_EXP_REMAP&t;&t;&t;&t;0x014
DECL|macro|RTR_REGIONS
mdefine_line|#define RTR_REGIONS&t;&t;&t;&t;&t;0x018
DECL|macro|RTR_DM_MASK
mdefine_line|#define RTR_DM_MASK&t;&t;&t;&t;&t;0x01C
DECL|macro|RTR_DM_LOCAL_BASE
mdefine_line|#define RTR_DM_LOCAL_BASE&t;&t;&t;0x020
DECL|macro|RTR_DM_IO_BASE
mdefine_line|#define RTR_DM_IO_BASE&t;&t;&t;&t;0x024
DECL|macro|RTR_DM_PCI_REMAP
mdefine_line|#define RTR_DM_PCI_REMAP&t;&t;&t;0x028
DECL|macro|RTR_DM_IO_CONFIG
mdefine_line|#define RTR_DM_IO_CONFIG&t;&t;&t;0x02C
DECL|macro|RTR_MAILBOX
mdefine_line|#define RTR_MAILBOX&t;&t;&t;&t;&t;0x040
DECL|macro|RTR_LOCAL_DOORBELL
mdefine_line|#define RTR_LOCAL_DOORBELL&t;&t;&t;0x060
DECL|macro|RTR_PCI_DOORBELL
mdefine_line|#define RTR_PCI_DOORBELL&t;&t;&t;0x064
DECL|macro|RTR_INT_CONTROL_STATUS
mdefine_line|#define RTR_INT_CONTROL_STATUS &t;&t;0x068
DECL|macro|RTR_EEPROM_CONTROL_STATUS
mdefine_line|#define RTR_EEPROM_CONTROL_STATUS&t;0x06C
DECL|macro|RTR_DMA0_MODE
mdefine_line|#define RTR_DMA0_MODE&t;&t;&t;&t;0x0080
DECL|macro|RTR_DMA0_PCI_ADDR
mdefine_line|#define RTR_DMA0_PCI_ADDR&t;&t;&t;0x0084
DECL|macro|RTR_DMA0_LOCAL_ADDR
mdefine_line|#define RTR_DMA0_LOCAL_ADDR&t;&t;&t;0x0088
DECL|macro|RTR_DMA0_COUNT
mdefine_line|#define RTR_DMA0_COUNT&t;&t;&t;&t;0x008C
DECL|macro|RTR_DMA0_DESC_PTR
mdefine_line|#define RTR_DMA0_DESC_PTR&t;&t;&t;0x0090
DECL|macro|RTR_DMA1_MODE
mdefine_line|#define RTR_DMA1_MODE&t;&t;&t;&t;0x0094
DECL|macro|RTR_DMA1_PCI_ADDR
mdefine_line|#define RTR_DMA1_PCI_ADDR&t;&t;&t;0x0098
DECL|macro|RTR_DMA1_LOCAL_ADDR
mdefine_line|#define RTR_DMA1_LOCAL_ADDR&t;&t;&t;0x009C
DECL|macro|RTR_DMA1_COUNT
mdefine_line|#define RTR_DMA1_COUNT&t;&t;&t;&t;0x00A0
DECL|macro|RTR_DMA1_DESC_PTR
mdefine_line|#define RTR_DMA1_DESC_PTR&t;&t;&t;0x00A4
DECL|macro|RTR_DMA_COMMAND_STATUS
mdefine_line|#define RTR_DMA_COMMAND_STATUS&t;&t;0x00A8
DECL|macro|RTR_DMA_ARB0
mdefine_line|#define RTR_DMA_ARB0&t;&t;&t;&t;0x00AC
DECL|macro|RTR_DMA_ARB1
mdefine_line|#define RTR_DMA_ARB1&t;&t;&t;&t;0x00B0
DECL|macro|RTL_DMA0_MODE
mdefine_line|#define RTL_DMA0_MODE&t;&t;&t;&t;0x00
DECL|macro|RTL_DMA0_PCI_ADDR
mdefine_line|#define RTL_DMA0_PCI_ADDR&t;&t;&t;0x04
DECL|macro|RTL_DMA0_LOCAL_ADDR
mdefine_line|#define RTL_DMA0_LOCAL_ADDR&t;&t;&t;0x08
DECL|macro|RTL_DMA0_COUNT
mdefine_line|#define RTL_DMA0_COUNT&t;&t;&t;&t;0x0C
DECL|macro|RTL_DMA0_DESC_PTR
mdefine_line|#define RTL_DMA0_DESC_PTR&t;&t;&t;0x10
DECL|macro|RTL_DMA1_MODE
mdefine_line|#define RTL_DMA1_MODE&t;&t;&t;&t;0x14
DECL|macro|RTL_DMA1_PCI_ADDR
mdefine_line|#define RTL_DMA1_PCI_ADDR&t;&t;&t;0x18
DECL|macro|RTL_DMA1_LOCAL_ADDR
mdefine_line|#define RTL_DMA1_LOCAL_ADDR&t;&t;&t;0x1C
DECL|macro|RTL_DMA1_COUNT
mdefine_line|#define RTL_DMA1_COUNT&t;&t;&t;&t;0x20
DECL|macro|RTL_DMA1_DESC_PTR
mdefine_line|#define RTL_DMA1_DESC_PTR&t;&t;&t;0x24
DECL|macro|RTL_DMA_COMMAND_STATUS
mdefine_line|#define RTL_DMA_COMMAND_STATUS&t;&t;0x28
DECL|macro|RTL_DMA_ARB0
mdefine_line|#define RTL_DMA_ARB0&t;&t;&t;&t;0x2C
DECL|macro|RTL_DMA_ARB1
mdefine_line|#define RTL_DMA_ARB1&t;&t;&t;&t;0x30
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Dale Scratchpad locations&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|DALE_CHANNEL_DEVICE_0
mdefine_line|#define&t;DALE_CHANNEL_DEVICE_0&t;&t;0&t;&t;
singleline_comment|// device channel locations
DECL|macro|DALE_CHANNEL_DEVICE_1
mdefine_line|#define&t;DALE_CHANNEL_DEVICE_1&t;&t;1
DECL|macro|DALE_CHANNEL_DEVICE_2
mdefine_line|#define&t;DALE_CHANNEL_DEVICE_2&t;&t;2
DECL|macro|DALE_CHANNEL_DEVICE_3
mdefine_line|#define&t;DALE_CHANNEL_DEVICE_3&t;&t;3
DECL|macro|DALE_SCRATCH_DEVICE_0
mdefine_line|#define&t;DALE_SCRATCH_DEVICE_0&t;&t;4&t;&t;
singleline_comment|// device type codes
DECL|macro|DALE_SCRATCH_DEVICE_1
mdefine_line|#define&t;DALE_SCRATCH_DEVICE_1&t;&t;5
DECL|macro|DALE_SCRATCH_DEVICE_2
mdefine_line|#define DALE_SCRATCH_DEVICE_2&t;&t;6
DECL|macro|DALE_SCRATCH_DEVICE_3
mdefine_line|#define&t;DALE_SCRATCH_DEVICE_3&t;&t;7
DECL|macro|DALE_RAID_0_STATUS
mdefine_line|#define&t;DALE_RAID_0_STATUS&t;&t;&t;8
DECL|macro|DALE_RAID_1_STATUS
mdefine_line|#define DALE_RAID_1_STATUS&t;&t;&t;9
DECL|macro|DALE_TIMING_MODE
mdefine_line|#define&t;DALE_TIMING_MODE&t;&t;&t;12&t;&t;
singleline_comment|// bus master timing mode (2, 3, 4, 5)
DECL|macro|DALE_NUM_DRIVES
mdefine_line|#define&t;DALE_NUM_DRIVES&t;&t;&t;&t;13&t;&t;
singleline_comment|// number of addressable drives on this board
DECL|macro|DALE_RAID_ON
mdefine_line|#define&t;DALE_RAID_ON&t;&t;&t;&t;14 &t;&t;
singleline_comment|// RAID status On
DECL|macro|DALE_LAST_ERROR
mdefine_line|#define&t;DALE_LAST_ERROR&t;&t;&t;&t;15&t;&t;
singleline_comment|// Last error code from BIOS
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;BigD Scratchpad locations&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|BIGD_DEVICE_0
mdefine_line|#define&t;BIGD_DEVICE_0&t;&t;&t;0&t;&t;
singleline_comment|// device channel locations
DECL|macro|BIGD_DEVICE_1
mdefine_line|#define&t;BIGD_DEVICE_1&t;&t;&t;1
DECL|macro|BIGD_DEVICE_2
mdefine_line|#define&t;BIGD_DEVICE_2&t;&t;&t;2
DECL|macro|BIGD_DEVICE_3
mdefine_line|#define&t;BIGD_DEVICE_3&t;&t;&t;3
DECL|macro|BIGD_DEVICE_4
mdefine_line|#define&t;BIGD_DEVICE_4&t;&t;&t;4&t;&t;
singleline_comment|// device type codes
DECL|macro|BIGD_DEVICE_5
mdefine_line|#define&t;BIGD_DEVICE_5&t;&t;&t;5
DECL|macro|BIGD_DEVICE_6
mdefine_line|#define BIGD_DEVICE_6&t;&t;&t;6
DECL|macro|BIGD_DEVICE_7
mdefine_line|#define&t;BIGD_DEVICE_7&t;&t;&t;7
DECL|macro|BIGD_ALARM_IMAGE
mdefine_line|#define&t;BIGD_ALARM_IMAGE&t;&t;11&t;&t;
singleline_comment|// ~image of alarm fail register&t;&t;
DECL|macro|BIGD_TIMING_MODE
mdefine_line|#define&t;BIGD_TIMING_MODE&t;&t;12&t;&t;
singleline_comment|// bus master timing mode (2, 3, 4, 5)
DECL|macro|BIGD_NUM_DRIVES
mdefine_line|#define&t;BIGD_NUM_DRIVES&t;&t;&t;13&t;&t;
singleline_comment|// number of addressable drives on this board
DECL|macro|BIGD_RAID_ON
mdefine_line|#define&t;BIGD_RAID_ON&t;&t;&t;14 &t;&t;
singleline_comment|// RAID status is on for the whole board
DECL|macro|BIGD_LAST_ERROR
mdefine_line|#define&t;BIGD_LAST_ERROR&t;&t;&t;15&t;&t;
singleline_comment|// Last error code from BIOS
DECL|macro|BIGD_RAID_0_STATUS
mdefine_line|#define&t;BIGD_RAID_0_STATUS&t;&t;16
DECL|macro|BIGD_RAID_1_STATUS
mdefine_line|#define BIGD_RAID_1_STATUS&t;&t;17
DECL|macro|BIGD_RAID_2_STATUS
mdefine_line|#define&t;BIGD_RAID_2_STATUS&t;&t;18
DECL|macro|BIGD_RAID_3_STATUS
mdefine_line|#define&t;BIGD_RAID_3_STATUS&t;&t;19
DECL|macro|BIGD_RAID_4_STATUS
mdefine_line|#define&t;BIGD_RAID_4_STATUS&t;&t;20
DECL|macro|BIGD_RAID_5_STATUS
mdefine_line|#define BIGD_RAID_5_STATUS&t;&t;21
DECL|macro|BIGD_RAID_6_STATUS
mdefine_line|#define&t;BIGD_RAID_6_STATUS&t;&t;22
DECL|macro|BIGD_RAID_7_STATUS
mdefine_line|#define&t;BIGD_RAID_7_STATUS&t;&t;23
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Dale cable select bits&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|SEL_NONE
mdefine_line|#define&t;SEL_NONE&t;&t;&t;&t;&t;0x00
DECL|macro|SEL_1
mdefine_line|#define&t;SEL_1&t;&t;&t;&t;&t;&t;0x01
DECL|macro|SEL_2
mdefine_line|#define&t;SEL_2&t;&t;&t;&t;&t;&t;0x02
DECL|macro|SEL_3
mdefine_line|#define&t;SEL_3&t;&t;&t;&t;&t;&t;0x04
DECL|macro|SEL_4
mdefine_line|#define&t;SEL_4&t;&t;&t;&t;&t;&t;0x08
DECL|macro|SEL_NEW_SPEED_1
mdefine_line|#define&t;SEL_NEW_SPEED_1&t;&t;&t;&t;0x20
DECL|macro|SEL_COPY
mdefine_line|#define&t;SEL_COPY&t;&t;&t;&t;&t;0x40
DECL|macro|SEL_IRQ_OFF
mdefine_line|#define&t;SEL_IRQ_OFF&t;&t;&t;&t;&t;0x80
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Device/Geometry controls&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|GEOMETRY_NONE
mdefine_line|#define GEOMETRY_NONE&t; &t;&t;&t;0x0&t;&t;&t;&t;
singleline_comment|// No device
DECL|macro|GEOMETRY_SET
mdefine_line|#define GEOMETRY_SET&t;&t;&t;&t;0x1&t;&t;&t;&t;
singleline_comment|// Geometry set
DECL|macro|GEOMETRY_LBA
mdefine_line|#define&t;GEOMETRY_LBA&t;&t;&t;&t;0x2&t;&t;&t;&t;
singleline_comment|// Geometry set in default LBA mode
DECL|macro|GEOMETRY_PHOENIX
mdefine_line|#define&t;GEOMETRY_PHOENIX&t;&t;&t;0x3&t;&t;&t;&t;
singleline_comment|// Geometry set in Pheonix BIOS compatibility mode
DECL|macro|DEVICE_NONE
mdefine_line|#define&t;DEVICE_NONE&t;&t;&t;&t;&t;0x0&t;&t;&t;&t;
singleline_comment|// No device present
DECL|macro|DEVICE_INACTIVE
mdefine_line|#define&t;DEVICE_INACTIVE&t;&t;&t;&t;0x1&t;&t;&t;&t;
singleline_comment|// device present but not registered active
DECL|macro|DEVICE_ATAPI
mdefine_line|#define&t;DEVICE_ATAPI&t;&t;&t;&t;0x2&t;&t;&t;&t;
singleline_comment|// ATAPI device (CD_ROM, Tape, Etc...)
DECL|macro|DEVICE_DASD_NONLBA
mdefine_line|#define&t;DEVICE_DASD_NONLBA&t;&t;&t;0x3&t;&t;&t;&t;
singleline_comment|// Non LBA incompatible device
DECL|macro|DEVICE_DASD_LBA
mdefine_line|#define&t;DEVICE_DASD_LBA&t;&t;&t;&t;0x4&t;&t;&t;&t;
singleline_comment|// LBA compatible device
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;BigD fail register bits&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|FAIL_NONE
mdefine_line|#define&t;FAIL_NONE&t;&t;&t;&t;0x00
DECL|macro|FAIL_0
mdefine_line|#define&t;FAIL_0&t;&t;&t;&t;&t;0x01
DECL|macro|FAIL_1
mdefine_line|#define&t;FAIL_1&t;&t;&t;&t;&t;0x02
DECL|macro|FAIL_2
mdefine_line|#define&t;FAIL_2&t;&t;&t;&t;&t;0x04
DECL|macro|FAIL_MULTIPLE
mdefine_line|#define&t;FAIL_MULTIPLE&t;&t;&t;0x08
DECL|macro|FAIL_GOOD
mdefine_line|#define&t;FAIL_GOOD&t;&t;&t;&t;0x20
DECL|macro|FAIL_AUDIBLE
mdefine_line|#define&t;FAIL_AUDIBLE&t;&t;&t;0x40
DECL|macro|FAIL_ANY
mdefine_line|#define&t;FAIL_ANY&t;&t;&t;&t;0x80
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Setup Structure Definitions&t;&t;&t;&t;*/
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
DECL|member|realCapacity
id|ULONG
id|realCapacity
suffix:semicolon
singleline_comment|// number of real blocks on this device for drive changed testing
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
id|BOOL
id|promptBIOS
suffix:semicolon
DECL|member|fastFormat
id|BOOL
id|fastFormat
suffix:semicolon
DECL|member|shareInterrupt
id|BOOL
id|shareInterrupt
suffix:semicolon
DECL|member|rebootRebuild
id|BOOL
id|rebootRebuild
suffix:semicolon
DECL|member|timingMode
id|USHORT
id|timingMode
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
id|BIGD_MAXDRIVES
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
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;RAID Structure Definitions&t;&t;&t;&t;*/
multiline_comment|/************************************************/
r_typedef
r_struct
(brace
DECL|member|signature
id|UCHAR
id|signature
suffix:semicolon
singleline_comment|// 0x55 our mirror signature
DECL|member|status
id|UCHAR
id|status
suffix:semicolon
singleline_comment|// current status bits
DECL|member|pairIdentifier
id|UCHAR
id|pairIdentifier
suffix:semicolon
singleline_comment|// unique identifier for pair
DECL|member|reconstructPoint
id|ULONG
id|reconstructPoint
suffix:semicolon
singleline_comment|// recontruction point for hot reconstruct
DECL|typedef|DISK_MIRROR
)brace
id|DISK_MIRROR
suffix:semicolon
DECL|struct|DEVICE_RAID1
r_typedef
r_struct
id|DEVICE_RAID1
(brace
DECL|member|TotalSectors
r_int
id|TotalSectors
suffix:semicolon
DECL|member|DiskRaid1
id|DISK_MIRROR
id|DiskRaid1
suffix:semicolon
DECL|typedef|DEVICE_RAID1
DECL|typedef|PDEVICE_RAID1
)brace
id|DEVICE_RAID1
comma
op_star
id|PDEVICE_RAID1
suffix:semicolon
DECL|macro|DISK_MIRROR_POSITION
mdefine_line|#define&t;DISK_MIRROR_POSITION&t;0x01A8
DECL|macro|SIGNATURE
mdefine_line|#define&t;SIGNATURE&t;&t;&t;&t;0x55
DECL|macro|MASK_SERIAL_NUMBER
mdefine_line|#define&t;MASK_SERIAL_NUMBER&t;0x0FFE&t;&t;&t;
singleline_comment|// mask for serial number matching
DECL|macro|MASK_SERIAL_UNIT
mdefine_line|#define&t;MASK_SERIAL_UNIT&t;0x0001&t;&t;&t;
singleline_comment|// mask for unit portion of serial number
singleline_comment|// Status bits
DECL|macro|UCBF_MIRRORED
mdefine_line|#define&t;UCBF_MIRRORED&t;&t;0x0010&t;&t;&t;&t;&t;&t;&t;&t;
singleline_comment|// drive has a pair
DECL|macro|UCBF_MATCHED
mdefine_line|#define&t;UCBF_MATCHED&t;&t;0x0020&t;&t;&t;&t;&t;&t;&t;&t;
singleline_comment|// drive pair is matched
DECL|macro|UCBF_SURVIVOR
mdefine_line|#define&t;UCBF_SURVIVOR&t;&t;0x0040&t;&t;&t;&t;&t;&t;&t;&t;
singleline_comment|// this unit is a survivor of a pair
DECL|macro|UCBF_REBUILD
mdefine_line|#define&t;UCBF_REBUILD&t;&t;0x0080&t;&t;&t;&t;&t;&t;&t;&t;
singleline_comment|// rebuild in progress on this device
singleline_comment|// SCSI controls for RAID
DECL|macro|SC_MY_RAID
mdefine_line|#define&t;SC_MY_RAID&t;&t;&t;0xBF&t;&t;&t;
singleline_comment|// our special CDB command byte for Win95... interface
DECL|macro|MY_SCSI_QUERY1
mdefine_line|#define&t;MY_SCSI_QUERY1&t;&t;0x32&t;&t;&t;
singleline_comment|// byte 1 subcommand to query driver for RAID 1 informatation
DECL|macro|MY_SCSI_REBUILD
mdefine_line|#define&t;MY_SCSI_REBUILD&t;&t;0x40&t;&t;&t;
singleline_comment|// byte 1 subcommand to reconstruct a mirrored pair
DECL|macro|MY_SCSI_DEMOFAIL
mdefine_line|#define MY_SCSI_DEMOFAIL&t;0x54&t;&t;&t;
singleline_comment|// byte 1 subcommand for RAID failure demonstration
DECL|macro|MY_SCSI_ALARMMUTE
mdefine_line|#define&t;MY_SCSI_ALARMMUTE&t;0x60&t;&t;&t;
singleline_comment|// byte 1 subcommand to mute any alarm currently on
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Timeout konstants&t;&t; &t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|TIMEOUT_READY
mdefine_line|#define&t;TIMEOUT_READY&t;&t;&t;&t;100&t;&t;&t;
singleline_comment|// 100 mSec
DECL|macro|TIMEOUT_DRQ
mdefine_line|#define&t;TIMEOUT_DRQ&t;&t;&t;&t;&t;300&t;&t;&t;
singleline_comment|// 300 mSec
DECL|macro|TIMEOUT_DATA
mdefine_line|#define&t;TIMEOUT_DATA&t;&t;&t;&t;(3 * HZ)&t;
singleline_comment|// 3 seconds
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Misc. macros&t;&t;&t; &t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|ANY2SCSI
mdefine_line|#define ANY2SCSI(up, p)&t;&t;&t;&t;&t;&bslash;&n;((UCHAR *)up)[0] = (((ULONG)(p)) &gt;&gt; 8);&t;&bslash;&n;((UCHAR *)up)[1] = ((ULONG)(p));
DECL|macro|SCSI2LONG
mdefine_line|#define SCSI2LONG(up)&t;&t;&t;&t;&t;&bslash;&n;( (((long)*(((UCHAR *)up))) &lt;&lt; 16)&t;&t;&bslash;&n;+ (((long)(((UCHAR *)up)[1])) &lt;&lt; 8)&t;&t;&bslash;&n;+ ((long)(((UCHAR *)up)[2])) )
DECL|macro|XANY2SCSI
mdefine_line|#define XANY2SCSI(up, p)&t;&t;&t;&t;&bslash;&n;((UCHAR *)up)[0] = ((long)(p)) &gt;&gt; 24;&t;&bslash;&n;((UCHAR *)up)[1] = ((long)(p)) &gt;&gt; 16;&t;&bslash;&n;((UCHAR *)up)[2] = ((long)(p)) &gt;&gt; 8;&t;&bslash;&n;((UCHAR *)up)[3] = ((long)(p));
DECL|macro|XSCSI2LONG
mdefine_line|#define XSCSI2LONG(up)&t;&t;&t;&t;&t;&bslash;&n;( (((long)(((UCHAR *)up)[0])) &lt;&lt; 24)&t;&bslash;&n;+ (((long)(((UCHAR *)up)[1])) &lt;&lt; 16)&t;&bslash;&n;+ (((long)(((UCHAR *)up)[2])) &lt;&lt;  8)&t;&bslash;&n;+ ((long)(((UCHAR *)up)[3])) )
DECL|macro|SelectSpigot
mdefine_line|#define&t;SelectSpigot(padapter,spigot)&t;outb_p (spigot, padapter-&gt;regStatSel)
DECL|macro|WriteCommand
mdefine_line|#define WriteCommand(padapter,cmd)&t;&t;outb_p (cmd, padapter-&gt;regStatCmd)
DECL|macro|AtapiDevice
mdefine_line|#define&t;AtapiDevice(padapter,b)&t;&t;&t;outb_p (b, padapter-&gt;regLba24);
DECL|macro|AtapiCountLo
mdefine_line|#define&t;AtapiCountLo(padapter,b)&t;&t;outb_p (b, padapter-&gt;regLba8)
DECL|macro|AtapiCountHi
mdefine_line|#define&t;AtapiCountHi(padapter,b)&t;&t;outb_p (b, padapter-&gt;regLba16)
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;SCSI CDB operation codes &t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|SCSIOP_TEST_UNIT_READY
mdefine_line|#define SCSIOP_TEST_UNIT_READY&t;&t;0x00
DECL|macro|SCSIOP_REZERO_UNIT
mdefine_line|#define SCSIOP_REZERO_UNIT&t;&t;&t;0x01
DECL|macro|SCSIOP_REWIND
mdefine_line|#define SCSIOP_REWIND&t;&t;&t;&t;0x01
DECL|macro|SCSIOP_REQUEST_BLOCK_ADDR
mdefine_line|#define SCSIOP_REQUEST_BLOCK_ADDR&t;0x02
DECL|macro|SCSIOP_REQUEST_SENSE
mdefine_line|#define SCSIOP_REQUEST_SENSE&t;&t;0x03
DECL|macro|SCSIOP_FORMAT_UNIT
mdefine_line|#define SCSIOP_FORMAT_UNIT&t;&t;&t;0x04
DECL|macro|SCSIOP_READ_BLOCK_LIMITS
mdefine_line|#define SCSIOP_READ_BLOCK_LIMITS&t;0x05
DECL|macro|SCSIOP_REASSIGN_BLOCKS
mdefine_line|#define SCSIOP_REASSIGN_BLOCKS&t;&t;0x07
DECL|macro|SCSIOP_READ6
mdefine_line|#define SCSIOP_READ6&t;&t;&t;&t;0x08
DECL|macro|SCSIOP_RECEIVE
mdefine_line|#define SCSIOP_RECEIVE&t;&t;&t;&t;0x08
DECL|macro|SCSIOP_WRITE6
mdefine_line|#define SCSIOP_WRITE6&t;&t;&t;&t;0x0A
DECL|macro|SCSIOP_PRINT
mdefine_line|#define SCSIOP_PRINT&t;&t;&t;&t;0x0A
DECL|macro|SCSIOP_SEND
mdefine_line|#define SCSIOP_SEND&t;&t;&t;&t;&t;0x0A
DECL|macro|SCSIOP_SEEK6
mdefine_line|#define SCSIOP_SEEK6&t;&t;&t;&t;0x0B
DECL|macro|SCSIOP_TRACK_SELECT
mdefine_line|#define SCSIOP_TRACK_SELECT&t;&t;&t;0x0B
DECL|macro|SCSIOP_SLEW_PRINT
mdefine_line|#define SCSIOP_SLEW_PRINT&t;&t;&t;0x0B
DECL|macro|SCSIOP_SEEK_BLOCK
mdefine_line|#define SCSIOP_SEEK_BLOCK&t;&t;&t;0x0C
DECL|macro|SCSIOP_PARTITION
mdefine_line|#define SCSIOP_PARTITION&t;&t;&t;0x0D
DECL|macro|SCSIOP_READ_REVERSE
mdefine_line|#define SCSIOP_READ_REVERSE&t;&t;&t;0x0F
DECL|macro|SCSIOP_WRITE_FILEMARKS
mdefine_line|#define SCSIOP_WRITE_FILEMARKS&t;&t;0x10
DECL|macro|SCSIOP_FLUSH_BUFFER
mdefine_line|#define SCSIOP_FLUSH_BUFFER&t;&t;&t;0x10
DECL|macro|SCSIOP_SPACE
mdefine_line|#define SCSIOP_SPACE&t;&t;&t;&t;0x11
DECL|macro|SCSIOP_INQUIRY
mdefine_line|#define SCSIOP_INQUIRY&t;&t;&t;&t;0x12
DECL|macro|SCSIOP_VERIFY6
mdefine_line|#define SCSIOP_VERIFY6&t;&t;&t;&t;0x13
DECL|macro|SCSIOP_RECOVER_BUF_DATA
mdefine_line|#define SCSIOP_RECOVER_BUF_DATA&t;&t;0x14
DECL|macro|SCSIOP_MODE_SELECT
mdefine_line|#define SCSIOP_MODE_SELECT&t;&t;&t;0x15
DECL|macro|SCSIOP_RESERVE_UNIT
mdefine_line|#define SCSIOP_RESERVE_UNIT&t;&t;&t;0x16
DECL|macro|SCSIOP_RELEASE_UNIT
mdefine_line|#define SCSIOP_RELEASE_UNIT&t;&t;&t;0x17
DECL|macro|SCSIOP_COPY
mdefine_line|#define SCSIOP_COPY&t;&t;&t;&t;&t;0x18
DECL|macro|SCSIOP_ERASE
mdefine_line|#define SCSIOP_ERASE&t;&t;&t;&t;0x19
DECL|macro|SCSIOP_MODE_SENSE
mdefine_line|#define SCSIOP_MODE_SENSE&t;&t;&t;0x1A
DECL|macro|SCSIOP_START_STOP_UNIT
mdefine_line|#define SCSIOP_START_STOP_UNIT&t;&t;0x1B
DECL|macro|SCSIOP_STOP_PRINT
mdefine_line|#define SCSIOP_STOP_PRINT&t;&t;&t;0x1B
DECL|macro|SCSIOP_LOAD_UNLOAD
mdefine_line|#define SCSIOP_LOAD_UNLOAD&t;&t;&t;0x1B
DECL|macro|SCSIOP_RECEIVE_DIAGNOSTIC
mdefine_line|#define SCSIOP_RECEIVE_DIAGNOSTIC&t;0x1C
DECL|macro|SCSIOP_SEND_DIAGNOSTIC
mdefine_line|#define SCSIOP_SEND_DIAGNOSTIC&t;&t;0x1D
DECL|macro|SCSIOP_MEDIUM_REMOVAL
mdefine_line|#define SCSIOP_MEDIUM_REMOVAL&t;&t;0x1E
DECL|macro|SCSIOP_READ_CAPACITY
mdefine_line|#define SCSIOP_READ_CAPACITY&t;&t;0x25
DECL|macro|SCSIOP_READ
mdefine_line|#define SCSIOP_READ&t;&t;&t;&t;&t;0x28
DECL|macro|SCSIOP_WRITE
mdefine_line|#define SCSIOP_WRITE&t;&t;&t;&t;0x2A
DECL|macro|SCSIOP_SEEK
mdefine_line|#define SCSIOP_SEEK&t;&t;&t;&t;&t;0x2B
DECL|macro|SCSIOP_LOCATE
mdefine_line|#define SCSIOP_LOCATE&t;&t;&t;&t;0x2B
DECL|macro|SCSIOP_WRITE_VERIFY
mdefine_line|#define SCSIOP_WRITE_VERIFY&t;&t;&t;0x2E
DECL|macro|SCSIOP_VERIFY
mdefine_line|#define SCSIOP_VERIFY&t;&t;&t;&t;0x2F
DECL|macro|SCSIOP_SEARCH_DATA_HIGH
mdefine_line|#define SCSIOP_SEARCH_DATA_HIGH&t;&t;0x30
DECL|macro|SCSIOP_SEARCH_DATA_EQUAL
mdefine_line|#define SCSIOP_SEARCH_DATA_EQUAL&t;0x31
DECL|macro|SCSIOP_SEARCH_DATA_LOW
mdefine_line|#define SCSIOP_SEARCH_DATA_LOW&t;&t;0x32
DECL|macro|SCSIOP_SET_LIMITS
mdefine_line|#define SCSIOP_SET_LIMITS&t;&t;&t;0x33
DECL|macro|SCSIOP_READ_POSITION
mdefine_line|#define SCSIOP_READ_POSITION&t;&t;0x34
DECL|macro|SCSIOP_SYNCHRONIZE_CACHE
mdefine_line|#define SCSIOP_SYNCHRONIZE_CACHE&t;0x35
DECL|macro|SCSIOP_COMPARE
mdefine_line|#define SCSIOP_COMPARE&t;&t;&t;&t;0x39
DECL|macro|SCSIOP_COPY_COMPARE
mdefine_line|#define SCSIOP_COPY_COMPARE&t;&t;&t;0x3A
DECL|macro|SCSIOP_WRITE_DATA_BUFF
mdefine_line|#define SCSIOP_WRITE_DATA_BUFF&t;&t;0x3B
DECL|macro|SCSIOP_READ_DATA_BUFF
mdefine_line|#define SCSIOP_READ_DATA_BUFF&t;&t;0x3C
DECL|macro|SCSIOP_CHANGE_DEFINITION
mdefine_line|#define SCSIOP_CHANGE_DEFINITION&t;0x40
DECL|macro|SCSIOP_READ_SUB_CHANNEL
mdefine_line|#define SCSIOP_READ_SUB_CHANNEL&t;&t;0x42
DECL|macro|SCSIOP_READ_TOC
mdefine_line|#define SCSIOP_READ_TOC&t;&t;&t;&t;0x43
DECL|macro|SCSIOP_READ_HEADER
mdefine_line|#define SCSIOP_READ_HEADER&t;&t;&t;0x44
DECL|macro|SCSIOP_PLAY_AUDIO
mdefine_line|#define SCSIOP_PLAY_AUDIO&t;&t;&t;0x45
DECL|macro|SCSIOP_PLAY_AUDIO_MSF
mdefine_line|#define SCSIOP_PLAY_AUDIO_MSF&t;&t;0x47
DECL|macro|SCSIOP_PLAY_TRACK_INDEX
mdefine_line|#define SCSIOP_PLAY_TRACK_INDEX&t;&t;0x48
DECL|macro|SCSIOP_PLAY_TRACK_RELATIVE
mdefine_line|#define SCSIOP_PLAY_TRACK_RELATIVE&t;0x49
DECL|macro|SCSIOP_PAUSE_RESUME
mdefine_line|#define SCSIOP_PAUSE_RESUME&t;&t;&t;0x4B
DECL|macro|SCSIOP_LOG_SELECT
mdefine_line|#define SCSIOP_LOG_SELECT&t;&t;&t;0x4C
DECL|macro|SCSIOP_LOG_SENSE
mdefine_line|#define SCSIOP_LOG_SENSE&t;&t;&t;0x4D
DECL|macro|SCSIOP_MODE_SELECT10
mdefine_line|#define SCSIOP_MODE_SELECT10&t;&t;0x55
DECL|macro|SCSIOP_MODE_SENSE10
mdefine_line|#define SCSIOP_MODE_SENSE10&t;&t;&t;0x5A
DECL|macro|SCSIOP_LOAD_UNLOAD_SLOT
mdefine_line|#define SCSIOP_LOAD_UNLOAD_SLOT&t;&t;0xA6
DECL|macro|SCSIOP_MECHANISM_STATUS
mdefine_line|#define SCSIOP_MECHANISM_STATUS&t;&t;0xBD
DECL|macro|SCSIOP_READ_CD
mdefine_line|#define SCSIOP_READ_CD&t;&t;&t;&t;0xBE
singleline_comment|// IDE command definitions
DECL|macro|IDE_COMMAND_ATAPI_RESET
mdefine_line|#define IDE_COMMAND_ATAPI_RESET&t;&t;0x08
DECL|macro|IDE_COMMAND_READ
mdefine_line|#define IDE_COMMAND_READ&t;&t;&t;0x20
DECL|macro|IDE_COMMAND_WRITE
mdefine_line|#define IDE_COMMAND_WRITE&t;&t;&t;0x30
DECL|macro|IDE_COMMAND_RECALIBRATE
mdefine_line|#define IDE_COMMAND_RECALIBRATE&t;&t;0x10
DECL|macro|IDE_COMMAND_SEEK
mdefine_line|#define IDE_COMMAND_SEEK&t;&t;&t;0x70
DECL|macro|IDE_COMMAND_SET_PARAMETERS
mdefine_line|#define IDE_COMMAND_SET_PARAMETERS&t;0x91
DECL|macro|IDE_COMMAND_VERIFY
mdefine_line|#define IDE_COMMAND_VERIFY&t;&t;&t;0x40
DECL|macro|IDE_COMMAND_ATAPI_PACKET
mdefine_line|#define IDE_COMMAND_ATAPI_PACKET&t;0xA0
DECL|macro|IDE_COMMAND_ATAPI_IDENTIFY
mdefine_line|#define IDE_COMMAND_ATAPI_IDENTIFY&t;0xA1
DECL|macro|IDE_CMD_READ_MULTIPLE
mdefine_line|#define&t;IDE_CMD_READ_MULTIPLE&t;&t;0xC4
DECL|macro|IDE_CMD_WRITE_MULTIPLE
mdefine_line|#define&t;IDE_CMD_WRITE_MULTIPLE&t;&t;0xC5
DECL|macro|IDE_CMD_SET_MULTIPLE
mdefine_line|#define&t;IDE_CMD_SET_MULTIPLE&t;&t;0xC6
DECL|macro|IDE_COMMAND_IDENTIFY
mdefine_line|#define IDE_COMMAND_IDENTIFY&t;&t;0xEC
singleline_comment|// IDE status definitions
DECL|macro|IDE_STATUS_ERROR
mdefine_line|#define IDE_STATUS_ERROR&t;&t;&t;0x01
DECL|macro|IDE_STATUS_INDEX
mdefine_line|#define IDE_STATUS_INDEX&t;&t;&t;0x02
DECL|macro|IDE_STATUS_CORRECTED_ERROR
mdefine_line|#define IDE_STATUS_CORRECTED_ERROR&t;0x04
DECL|macro|IDE_STATUS_DRQ
mdefine_line|#define IDE_STATUS_DRQ&t;&t;&t;&t;0x08
DECL|macro|IDE_STATUS_DSC
mdefine_line|#define IDE_STATUS_DSC&t;&t;&t;&t;0x10
DECL|macro|IDE_STATUS_WRITE_FAULT
mdefine_line|#define&t;IDE_STATUS_WRITE_FAULT&t;&t;0x20
DECL|macro|IDE_STATUS_DRDY
mdefine_line|#define IDE_STATUS_DRDY&t;&t;&t;&t;0x40
DECL|macro|IDE_STATUS_BUSY
mdefine_line|#define IDE_STATUS_BUSY&t;&t;&t;&t;0x80
DECL|struct|_ATAPI_STATUS
r_typedef
r_struct
id|_ATAPI_STATUS
(brace
DECL|member|check
id|CHAR
id|check
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|CHAR
id|reserved1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|corr
id|CHAR
id|corr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|drq
id|CHAR
id|drq
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dsc
id|CHAR
id|dsc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
id|CHAR
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|drdy
id|CHAR
id|drdy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|bsy
id|CHAR
id|bsy
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|ATAPI_STATUS
)brace
id|ATAPI_STATUS
suffix:semicolon
DECL|struct|_ATAPI_REASON
r_typedef
r_struct
id|_ATAPI_REASON
(brace
DECL|member|cod
id|CHAR
id|cod
suffix:colon
l_int|1
suffix:semicolon
DECL|member|io
id|CHAR
id|io
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|CHAR
id|reserved1
suffix:colon
l_int|6
suffix:semicolon
DECL|typedef|ATAPI_REASON
)brace
id|ATAPI_REASON
suffix:semicolon
DECL|struct|_ATAPI_ERROR
r_typedef
r_struct
id|_ATAPI_ERROR
(brace
DECL|member|ili
id|CHAR
id|ili
suffix:colon
l_int|1
suffix:semicolon
DECL|member|eom
id|CHAR
id|eom
suffix:colon
l_int|1
suffix:semicolon
DECL|member|abort
id|CHAR
m_abort
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mcr
id|CHAR
id|mcr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|senseKey
id|CHAR
id|senseKey
suffix:colon
l_int|4
suffix:semicolon
DECL|typedef|ATAPI_ERROR
)brace
id|ATAPI_ERROR
suffix:semicolon
singleline_comment|// IDE error definitions
DECL|macro|IDE_ERROR_AMNF
mdefine_line|#define&t;IDE_ERROR_AMNF&t;&t;&t;&t;0x01
DECL|macro|IDE_ERROR_TKONF
mdefine_line|#define&t;IDE_ERROR_TKONF&t;&t;&t;&t;0x02
DECL|macro|IDE_ERROR_ABRT
mdefine_line|#define&t;IDE_ERROR_ABRT&t;&t;&t;&t;0x04
DECL|macro|IDE_ERROR_MCR
mdefine_line|#define&t;IDE_ERROR_MCR&t;&t;&t;&t;0x08
DECL|macro|IDE_ERROR_IDFN
mdefine_line|#define&t;IDE_ERROR_IDFN&t;&t;&t;&t;0x10
DECL|macro|IDE_ERROR_MC
mdefine_line|#define&t;IDE_ERROR_MC&t;&t;&t;&t;0x20
DECL|macro|IDE_ERROR_UNC
mdefine_line|#define&t;IDE_ERROR_UNC&t;&t;&t;&t;0x40
DECL|macro|IDE_ERROR_BBK
mdefine_line|#define&t;IDE_ERROR_BBK&t;&t;&t;&t;0x80
singleline_comment|// SCSI read capacity structure
DECL|struct|_READ_CAPACITY_DATA
r_typedef
r_struct
id|_READ_CAPACITY_DATA
(brace
DECL|member|blks
id|ULONG
id|blks
suffix:semicolon
multiline_comment|/* total blocks (converted to little endian) */
DECL|member|blksiz
id|ULONG
id|blksiz
suffix:semicolon
multiline_comment|/* size of each (converted to little endian) */
DECL|typedef|READ_CAPACITY_DATA
DECL|typedef|PREAD_CAPACITY_DATA
)brace
id|READ_CAPACITY_DATA
comma
op_star
id|PREAD_CAPACITY_DATA
suffix:semicolon
singleline_comment|// SCSI inquiry data
DECL|struct|_INQUIRYDATA
r_typedef
r_struct
id|_INQUIRYDATA
(brace
DECL|member|DeviceType
id|UCHAR
id|DeviceType
suffix:colon
l_int|5
suffix:semicolon
DECL|member|DeviceTypeQualifier
id|UCHAR
id|DeviceTypeQualifier
suffix:colon
l_int|3
suffix:semicolon
DECL|member|DeviceTypeModifier
id|UCHAR
id|DeviceTypeModifier
suffix:colon
l_int|7
suffix:semicolon
DECL|member|RemovableMedia
id|UCHAR
id|RemovableMedia
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Versions
id|UCHAR
id|Versions
suffix:semicolon
DECL|member|ResponseDataFormat
id|UCHAR
id|ResponseDataFormat
suffix:semicolon
DECL|member|AdditionalLength
id|UCHAR
id|AdditionalLength
suffix:semicolon
DECL|member|Reserved
id|UCHAR
id|Reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|SoftReset
id|UCHAR
id|SoftReset
suffix:colon
l_int|1
suffix:semicolon
DECL|member|CommandQueue
id|UCHAR
id|CommandQueue
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Reserved2
id|UCHAR
id|Reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|LinkedCommands
id|UCHAR
id|LinkedCommands
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Synchronous
id|UCHAR
id|Synchronous
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Wide16Bit
id|UCHAR
id|Wide16Bit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Wide32Bit
id|UCHAR
id|Wide32Bit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|RelativeAddressing
id|UCHAR
id|RelativeAddressing
suffix:colon
l_int|1
suffix:semicolon
DECL|member|VendorId
id|UCHAR
id|VendorId
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ProductId
id|UCHAR
id|ProductId
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|ProductRevisionLevel
id|UCHAR
id|ProductRevisionLevel
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|VendorSpecific
id|UCHAR
id|VendorSpecific
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|Reserved3
id|UCHAR
id|Reserved3
(braket
l_int|40
)braket
suffix:semicolon
DECL|typedef|INQUIRYDATA
DECL|typedef|PINQUIRYDATA
)brace
id|INQUIRYDATA
comma
op_star
id|PINQUIRYDATA
suffix:semicolon
singleline_comment|// IDE IDENTIFY data
macro_line|#pragma pack (1)
DECL|struct|_IDENTIFY_DATA
r_typedef
r_struct
id|_IDENTIFY_DATA
(brace
DECL|member|GeneralConfiguration
id|USHORT
id|GeneralConfiguration
suffix:semicolon
singleline_comment|//  0
DECL|member|NumberOfCylinders
id|USHORT
id|NumberOfCylinders
suffix:semicolon
singleline_comment|//  1
DECL|member|Reserved1
id|USHORT
id|Reserved1
suffix:semicolon
singleline_comment|//  2
DECL|member|NumberOfHeads
id|USHORT
id|NumberOfHeads
suffix:semicolon
singleline_comment|//  3
DECL|member|UnformattedBytesPerTrack
id|USHORT
id|UnformattedBytesPerTrack
suffix:semicolon
singleline_comment|//  4
DECL|member|UnformattedBytesPerSector
id|USHORT
id|UnformattedBytesPerSector
suffix:semicolon
singleline_comment|//  5
DECL|member|SectorsPerTrack
id|USHORT
id|SectorsPerTrack
suffix:semicolon
singleline_comment|//  6
DECL|member|NumBytesISG
id|USHORT
id|NumBytesISG
suffix:semicolon
singleline_comment|//  7 Byte Len - inter-sector gap
DECL|member|NumBytesSync
id|USHORT
id|NumBytesSync
suffix:semicolon
singleline_comment|//  8          - sync field
DECL|member|NumWordsVUS
id|USHORT
id|NumWordsVUS
suffix:semicolon
singleline_comment|//  9 Len - Vendor Unique Info
DECL|member|SerialNumber
id|USHORT
id|SerialNumber
(braket
l_int|10
)braket
suffix:semicolon
singleline_comment|// 10
DECL|member|BufferType
id|USHORT
id|BufferType
suffix:semicolon
singleline_comment|// 20
DECL|member|BufferSectorSize
id|USHORT
id|BufferSectorSize
suffix:semicolon
singleline_comment|// 21
DECL|member|NumberOfEccBytes
id|USHORT
id|NumberOfEccBytes
suffix:semicolon
singleline_comment|// 22
DECL|member|FirmwareRevision
id|USHORT
id|FirmwareRevision
(braket
l_int|4
)braket
suffix:semicolon
singleline_comment|// 23
DECL|member|ModelNumber
id|USHORT
id|ModelNumber
(braket
l_int|20
)braket
suffix:semicolon
singleline_comment|// 27
DECL|member|NumSectorsPerInt
id|USHORT
id|NumSectorsPerInt
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// 47 Multiple Mode - Sec/Blk
DECL|member|Reserved2
id|USHORT
id|Reserved2
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// 47
DECL|member|DoubleWordMode
id|USHORT
id|DoubleWordMode
suffix:semicolon
singleline_comment|// 48 flag for double word mode capable
DECL|member|VendorUnique1
id|USHORT
id|VendorUnique1
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// 49
DECL|member|SupportDMA
id|USHORT
id|SupportDMA
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 49 DMA supported
DECL|member|SupportLBA
id|USHORT
id|SupportLBA
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 49 LBA supported
DECL|member|SupportIORDYDisable
id|USHORT
id|SupportIORDYDisable
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 49 IORDY can be disabled
DECL|member|SupportIORDY
id|USHORT
id|SupportIORDY
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 49 IORDY supported
DECL|member|ReservedPsuedoDMA
id|USHORT
id|ReservedPsuedoDMA
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 49 reserved for pseudo DMA mode support
DECL|member|Reserved3
id|USHORT
id|Reserved3
suffix:colon
l_int|3
suffix:semicolon
singleline_comment|// 49
DECL|member|Reserved4
id|USHORT
id|Reserved4
suffix:semicolon
singleline_comment|// 50
DECL|member|Reserved5
id|USHORT
id|Reserved5
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// 51 Transfer Cycle Timing - PIO
DECL|member|PIOCycleTime
id|USHORT
id|PIOCycleTime
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// 51 Transfer Cycle Timing - PIO
DECL|member|Reserved6
id|USHORT
id|Reserved6
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// 52                       - DMA
DECL|member|DMACycleTime
id|USHORT
id|DMACycleTime
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// 52                       - DMA
DECL|member|Valid_54_58
id|USHORT
id|Valid_54_58
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 53 words 54 - 58 are valid
DECL|member|Valid_64_70
id|USHORT
id|Valid_64_70
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 53 words 64 - 70 are valid
DECL|member|Reserved7
id|USHORT
id|Reserved7
suffix:colon
l_int|14
suffix:semicolon
singleline_comment|// 53
DECL|member|LogNumCyl
id|USHORT
id|LogNumCyl
suffix:semicolon
singleline_comment|// 54 Current Translation - Num Cyl
DECL|member|LogNumHeads
id|USHORT
id|LogNumHeads
suffix:semicolon
singleline_comment|// 55                       Num Heads
DECL|member|LogSectorsPerTrack
id|USHORT
id|LogSectorsPerTrack
suffix:semicolon
singleline_comment|// 56                       Sec/Trk
DECL|member|LogTotalSectors
id|ULONG
id|LogTotalSectors
suffix:semicolon
singleline_comment|// 57                       Total Sec
DECL|member|CurrentNumSecPerInt
id|USHORT
id|CurrentNumSecPerInt
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// 59 current setting for number of sectors per interrupt
DECL|member|ValidNumSecPerInt
id|USHORT
id|ValidNumSecPerInt
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// 59 Current setting is valid for number of sectors per interrupt
DECL|member|Reserved8
id|USHORT
id|Reserved8
suffix:colon
l_int|7
suffix:semicolon
singleline_comment|// 59
DECL|member|LBATotalSectors
id|ULONG
id|LBATotalSectors
suffix:semicolon
singleline_comment|// 60 LBA Mode - Sectors
DECL|member|DMASWordFlags
id|USHORT
id|DMASWordFlags
suffix:semicolon
singleline_comment|// 62
DECL|member|DMAMWordFlags
id|USHORT
id|DMAMWordFlags
suffix:semicolon
singleline_comment|// 63
DECL|member|AdvancedPIOSupport
id|USHORT
id|AdvancedPIOSupport
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// 64 Flow control PIO transfer modes supported
DECL|member|Reserved9
id|USHORT
id|Reserved9
suffix:colon
l_int|8
suffix:semicolon
singleline_comment|// 64
DECL|member|MinMultiDMACycle
id|USHORT
id|MinMultiDMACycle
suffix:semicolon
singleline_comment|// 65 minimum multiword DMA transfer cycle time per word
DECL|member|RecomendDMACycle
id|USHORT
id|RecomendDMACycle
suffix:semicolon
singleline_comment|// 66 Manufacturer&squot;s recommende multiword DMA transfer cycle time
DECL|member|MinPIOCycleWithoutFlow
id|USHORT
id|MinPIOCycleWithoutFlow
suffix:semicolon
singleline_comment|// 67 Minimum PIO transfer cycle time without flow control
DECL|member|MinPIOCylceWithFlow
id|USHORT
id|MinPIOCylceWithFlow
suffix:semicolon
singleline_comment|// 68 Minimum PIO transfer cycle time with IORDY flow control
DECL|member|ReservedSpace
id|USHORT
id|ReservedSpace
(braket
l_int|256
op_minus
l_int|69
)braket
suffix:semicolon
singleline_comment|// 69
DECL|typedef|IDENTIFY_DATA
DECL|typedef|PIDENTIFY_DATA
)brace
id|IDENTIFY_DATA
comma
op_star
id|PIDENTIFY_DATA
suffix:semicolon
singleline_comment|// ATAPI configuration bits
DECL|struct|_ATAPI_GENERAL_0
r_typedef
r_struct
id|_ATAPI_GENERAL_0
(brace
DECL|member|CmdPacketSize
id|USHORT
id|CmdPacketSize
suffix:colon
l_int|2
suffix:semicolon
singleline_comment|// Command packet size
DECL|member|Reserved1
id|USHORT
id|Reserved1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|CmdDrqType
id|USHORT
id|CmdDrqType
suffix:colon
l_int|2
suffix:semicolon
DECL|member|Removable
id|USHORT
id|Removable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|DeviceType
id|USHORT
id|DeviceType
suffix:colon
l_int|5
suffix:semicolon
DECL|member|Reserved2
id|USHORT
id|Reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ProtocolType
id|USHORT
id|ProtocolType
suffix:colon
l_int|2
suffix:semicolon
DECL|typedef|ATAPI_GENERAL_0
)brace
id|ATAPI_GENERAL_0
suffix:semicolon
macro_line|#pragma pack ()
eof
