multiline_comment|/****************************************************************************&n; * Perceptive Solutions, Inc. PCI-2000 device driver for Linux.&n; *&n; * psi_roy.h - Linux Host Driver for PCI-2000 IntelliCache SCSI Adapters&n; *&n; * Copyright (c) 1997-1999 Perceptive Solutions, Inc.&n; * All Rights Reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that redistributions of source&n; * code retain the above copyright notice and this comment without&n; * modification.&n; *&n; * Technical updates and product information at:&n; *  http://www.psidisk.com&n; *&n; * Please send questions, comments, bug reports to:&n; *  tech@psidisk.com Technical Support&n; *&n; ****************************************************************************/
macro_line|#ifndef&t;ROY_HOST
DECL|macro|ROY_HOST
mdefine_line|#define&t;ROY_HOST
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;PCI setup&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|VENDOR_PSI
mdefine_line|#define&t;VENDOR_PSI&t;&t;&t;0x1256
DECL|macro|DEVICE_ROY_1
mdefine_line|#define&t;DEVICE_ROY_1&t;&t;0x5201&t;&t;/* &squot;R1&squot; */
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;controller constants&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|MAXADAPTER
mdefine_line|#define MAXADAPTER&t;&t;&t;4&t;&t;&t;
singleline_comment|// Increase this and the sizes of the arrays below, if you need more.
DECL|macro|MAX_BUS
mdefine_line|#define&t;MAX_BUS&t;&t;&t;&t;2
DECL|macro|MAX_UNITS
mdefine_line|#define&t;MAX_UNITS&t;&t;&t;16
DECL|macro|TIMEOUT_COMMAND
mdefine_line|#define&t;TIMEOUT_COMMAND&t;&t;400&t;&t;&t;
singleline_comment|// number of milliSecondos for command busy timeout
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;I/O address offsets&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|RTR_MAILBOX
mdefine_line|#define RTR_MAILBOX&t;&t;&t;&t;&t;&t;0x040
DECL|macro|RTR_LOCAL_DOORBELL
mdefine_line|#define RTR_LOCAL_DOORBELL&t;&t;&t;&t;0x060
DECL|macro|RTR_PCI_DOORBELL
mdefine_line|#define RTR_PCI_DOORBELL&t;&t;&t;&t;0x064
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;Host command codes&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|CMD_READ_CHS
mdefine_line|#define&t;CMD_READ_CHS&t;&t;0x01&t;&t;/* read sectors as specified (CHS mode) */
DECL|macro|CMD_READ
mdefine_line|#define&t;CMD_READ&t;&t;&t;0x02&t;&t;/* read sectors as specified (RBA mode) */
DECL|macro|CMD_READ_SG
mdefine_line|#define&t;CMD_READ_SG&t;&t;&t;0x03&t;&t;/* read sectors using scatter/gather list */
DECL|macro|CMD_WRITE_CHS
mdefine_line|#define&t;CMD_WRITE_CHS&t;&t;0x04&t;&t;/* write sectors as specified (CHS mode) */
DECL|macro|CMD_WRITE
mdefine_line|#define&t;CMD_WRITE&t;&t;&t;0x05&t;&t;/* write sectors as specified (RBA mode) */
DECL|macro|CMD_WRITE_SG
mdefine_line|#define&t;CMD_WRITE_SG&t;&t;0x06&t;&t;/* write sectors using scatter/gather list (LBA mode) */
DECL|macro|CMD_READ_CHS_SG
mdefine_line|#define&t;CMD_READ_CHS_SG&t;&t;0x07&t;&t;/* read sectors using scatter/gather list (CHS mode) */
DECL|macro|CMD_WRITE_CHS_SG
mdefine_line|#define&t;CMD_WRITE_CHS_SG&t;0x08&t;&t;/* write sectors using scatter/gather list (CHS mode) */
DECL|macro|CMD_VERIFY_CHS
mdefine_line|#define&t;CMD_VERIFY_CHS&t;&t;0x09&t;&t;/* verify data on sectors as specified (CHS mode) */
DECL|macro|CMD_VERIFY
mdefine_line|#define&t;CMD_VERIFY&t;&t;&t;0x0A&t;&t;/* verify data on sectors as specified (RBA mode) */
DECL|macro|CMD_DASD_CDB
mdefine_line|#define&t;CMD_DASD_CDB&t;&t;0x0B&t;&t;/* process CDB for a DASD device */
DECL|macro|CMD_DASD_CDB_SG
mdefine_line|#define&t;CMD_DASD_CDB_SG&t;&t;0x0C&t;&t;/* process CDB for a DASD device with scatter/gather */
DECL|macro|CMD_READ_ABS
mdefine_line|#define&t;CMD_READ_ABS&t;&t;0x10&t;&t;/* read absolute disk */
DECL|macro|CMD_WRITE_ABS
mdefine_line|#define&t;CMD_WRITE_ABS&t;&t;0x11&t;&t;/* write absolute disk */
DECL|macro|CMD_VERIFY_ABS
mdefine_line|#define&t;CMD_VERIFY_ABS&t;&t;0x12&t;&t;/* verify absolute disk */
DECL|macro|CMD_TEST_READY
mdefine_line|#define&t;CMD_TEST_READY&t;&t;0x13&t;&t;/* test unit ready and return status code */
DECL|macro|CMD_LOCK_DOOR
mdefine_line|#define&t;CMD_LOCK_DOOR&t;&t;0x14&t;&t;/* lock device door */
DECL|macro|CMD_UNLOCK_DOOR
mdefine_line|#define&t;CMD_UNLOCK_DOOR&t;&t;0x15&t;&t;/* unlock device door */
DECL|macro|CMD_EJECT_MEDIA
mdefine_line|#define&t;CMD_EJECT_MEDIA&t;&t;0x16&t;&t;/* eject the media */
DECL|macro|CMD_UPDATE_CAP
mdefine_line|#define&t;CMD_UPDATE_CAP&t;&t;0x17&t;&t;/* update capacity information */
DECL|macro|CMD_TEST_PRIV
mdefine_line|#define&t;CMD_TEST_PRIV&t;&t;0x18&t;&t;/* test and setup private format media */
DECL|macro|CMD_SCSI_THRU
mdefine_line|#define&t;CMD_SCSI_THRU&t;&t;0x30&t;&t;/* SCSI pass through CDB */
DECL|macro|CMD_SCSI_THRU_SG
mdefine_line|#define&t;CMD_SCSI_THRU_SG&t;0x31&t;&t;/* SCSI pass through CDB with scatter/gather */
DECL|macro|CMD_SCSI_REQ_SENSE
mdefine_line|#define&t;CMD_SCSI_REQ_SENSE&t;0x32&t;&t;/* SCSI pass through request sense after check condition */
DECL|macro|CMD_DASD_RAID_RQ
mdefine_line|#define&t;CMD_DASD_RAID_RQ&t;0x35&t;&t;/* request DASD RAID drive data */
DECL|macro|CMD_DASD_RAID_RQ0
mdefine_line|#define&t;CMD_DASD_RAID_RQ0&t;0x31&t;&t;&t;/* byte 1 subcommand to query for RAID 0 informatation */
DECL|macro|CMD_DASD_RAID_RQ1
mdefine_line|#define&t;CMD_DASD_RAID_RQ1&t;0x32&t;&t;&t;/* byte 1 subcommand to query for RAID 1 informatation */
DECL|macro|CMD_DASD_RAID_RQ5
mdefine_line|#define&t;CMD_DASD_RAID_RQ5&t;0x33&t;&t;&t;/* byte 1 subcommand to query for RAID 5 informatation */
DECL|macro|CMD_DASD_SCSI_INQ
mdefine_line|#define&t;CMD_DASD_SCSI_INQ&t;0x36&t;&t;/* do DASD inquire and return in SCSI format */
DECL|macro|CMD_DASD_CAP
mdefine_line|#define&t;CMD_DASD_CAP&t;&t;0x37&t;&t;/* read DASD capacity */
DECL|macro|CMD_DASD_INQ
mdefine_line|#define&t;CMD_DASD_INQ&t;&t;0x38&t;&t;/* do DASD inquire for type data and return SCSI/EIDE inquiry */
DECL|macro|CMD_SCSI_INQ
mdefine_line|#define&t;CMD_SCSI_INQ&t;&t;0x39&t;&t;/* do SCSI inquire */
DECL|macro|CMD_READ_SETUP
mdefine_line|#define&t;CMD_READ_SETUP&t;&t;0x3A&t;&t;/* Get setup structures from controller */
DECL|macro|CMD_WRITE_SETUP
mdefine_line|#define&t;CMD_WRITE_SETUP&t;&t;0x3B&t;&t;/* Put setup structures in controller and burn in flash */
DECL|macro|CMD_READ_CONFIG
mdefine_line|#define&t;CMD_READ_CONFIG&t;&t;0x3C&t;&t;/* Get the entire configuration and setup structures */
DECL|macro|CMD_WRITE_CONFIG
mdefine_line|#define&t;CMD_WRITE_CONFIG&t;0x3D&t;&t;/* Put the entire configuration and setup structures in flash */
DECL|macro|CMD_TEXT_DEVICE
mdefine_line|#define&t;CMD_TEXT_DEVICE&t;&t;0x3E&t;&t;/* obtain device text */
DECL|macro|CMD_TEXT_SIGNON
mdefine_line|#define&t;CMD_TEXT_SIGNON&t;&t;0x3F&t;&t;/* get sign on banner */
DECL|macro|CMD_QUEUE
mdefine_line|#define&t;CMD_QUEUE&t;&t;&t;0x40&t;&t;/* any command below this generates a queue tag interrupt to host*/
DECL|macro|CMD_PREFETCH
mdefine_line|#define&t;CMD_PREFETCH&t;&t;0x40&t;&t;/* prefetch sectors as specified */
DECL|macro|CMD_TEST_WRITE
mdefine_line|#define&t;CMD_TEST_WRITE&t;&t;0x41&t;&t;/* Test a device for write protect */
DECL|macro|CMD_LAST_STATUS
mdefine_line|#define&t;CMD_LAST_STATUS&t;&t;0x42&t;&t;/* get last command status and error data*/
DECL|macro|CMD_ABORT
mdefine_line|#define&t;CMD_ABORT&t;&t;&t;0x43&t;&t;/* abort command as specified */
DECL|macro|CMD_ERROR
mdefine_line|#define&t;CMD_ERROR&t;&t;&t;0x44&t;&t;/* fetch error code from a tagged op */
DECL|macro|CMD_DONE
mdefine_line|#define&t;CMD_DONE&t;&t;&t;0x45&t;&t;/* done with operation */
DECL|macro|CMD_DIAGNOSTICS
mdefine_line|#define&t;CMD_DIAGNOSTICS&t;&t;0x46&t;&t;/* execute controller diagnostics and wait for results */
DECL|macro|CMD_FEATURE_MODE
mdefine_line|#define&t;CMD_FEATURE_MODE&t;0x47&t;&t;/* feature mode control word */
DECL|macro|CMD_DASD_INQUIRE
mdefine_line|#define&t;CMD_DASD_INQUIRE&t;0x48&t;&t;/* inquire as to DASD SCSI device (32 possible) */
DECL|macro|CMD_FEATURE_QUERY
mdefine_line|#define&t;CMD_FEATURE_QUERY&t;0x49&t;&t;/* query the feature control word */
DECL|macro|CMD_DASD_EJECT
mdefine_line|#define&t;CMD_DASD_EJECT&t;&t;0x4A&t;&t;/* Eject removable media for DASD type */
DECL|macro|CMD_DASD_LOCK
mdefine_line|#define&t;CMD_DASD_LOCK&t;&t;0x4B&t;&t;/* Lock removable media for DASD type */
DECL|macro|CMD_DASD_TYPE
mdefine_line|#define&t;CMD_DASD_TYPE&t;&t;0x4C&t;&t;/* obtain DASD device type */
DECL|macro|CMD_NUM_DEV
mdefine_line|#define&t;CMD_NUM_DEV&t;&t;&t;0x4D&t;&t;/* obtain the number of devices connected to the controller */
DECL|macro|CMD_GET_PARMS
mdefine_line|#define&t;CMD_GET_PARMS&t;&t;0x4E&t;&t;/* obtain device parameters */
DECL|macro|CMD_SPECIFY
mdefine_line|#define&t;CMD_SPECIFY&t;&t;&t;0x4F&t;&t;/* specify operating system for scatter/gather operations */
DECL|macro|CMD_RAID_GET_DEV
mdefine_line|#define&t;CMD_RAID_GET_DEV&t;0x50&t;&t;/* read RAID device geometry */
DECL|macro|CMD_RAID_READ
mdefine_line|#define CMD_RAID_READ&t;&t;0x51&t;&t;/* read RAID 1 parameter block */
DECL|macro|CMD_RAID_WRITE
mdefine_line|#define&t;CMD_RAID_WRITE&t;&t;0x52&t;&t;/* write RAID 1 parameter block */
DECL|macro|CMD_RAID_LITEUP
mdefine_line|#define&t;CMD_RAID_LITEUP&t;&t;0x53&t;&t;/* Light up the drive light for identification */
DECL|macro|CMD_RAID_REBUILD
mdefine_line|#define&t;CMD_RAID_REBUILD&t;0x54&t;&t;/* issue a RAID 1 pair rebuild */
DECL|macro|CMD_RAID_MUTE
mdefine_line|#define&t;CMD_RAID_MUTE&t;&t;0x55&t;&t;/* mute RAID failure alarm */
DECL|macro|CMD_RAID_FAIL
mdefine_line|#define&t;CMD_RAID_FAIL&t;&t;0x56&t;&t;/* induce a RAID failure */
DECL|macro|CMD_RAID_STATUS
mdefine_line|#define&t;CMD_RAID_STATUS&t;&t;0x57&t;&t;/* get status of RAID pair */
DECL|macro|CMD_RAID_STOP
mdefine_line|#define&t;CMD_RAID_STOP&t;&t;0x58&t;&t;/* stop any reconstruct in progress */
DECL|macro|CMD_RAID_START
mdefine_line|#define CMD_RAID_START&t;&t;0x59&t;&t;/* start reconstruct */
DECL|macro|CMD_RAID0_READ
mdefine_line|#define&t;CMD_RAID0_READ&t;&t;0x5A&t;&t;/* read RAID 0 parameter block */
DECL|macro|CMD_RAID0_WRITE
mdefine_line|#define&t;CMD_RAID0_WRITE&t;&t;0x5B&t;&t;/* write RAID 0 parameter block */
DECL|macro|CMD_RAID5_READ
mdefine_line|#define&t;CMD_RAID5_READ&t;&t;0x5C&t;&t;/* read RAID 5 parameter block */
DECL|macro|CMD_RAID5_WRITE
mdefine_line|#define&t;CMD_RAID5_WRITE&t;&t;0x5D&t;&t;/* write RAID 5 parameter block */
DECL|macro|CMD_ERASE_TABLES
mdefine_line|#define&t;CMD_ERASE_TABLES&t;0x5F&t;&t;/* erase partition table and RAID signatutures */
DECL|macro|CMD_SCSI_GET
mdefine_line|#define&t;CMD_SCSI_GET&t;&t;0x60&t;&t;/* get SCSI pass through devices */
DECL|macro|CMD_SCSI_TIMEOUT
mdefine_line|#define&t;CMD_SCSI_TIMEOUT&t;0x61&t;&t;/* set SCSI pass through timeout */
DECL|macro|CMD_SCSI_ERROR
mdefine_line|#define&t;CMD_SCSI_ERROR&t;&t;0x62&t;&t;/* get SCSI pass through request sense length and residual data count */
DECL|macro|CMD_GET_SPARMS
mdefine_line|#define&t;CMD_GET_SPARMS&t;&t;0x63&t;&t;/* get SCSI bus and user parms */
DECL|macro|CMD_SCSI_ABORT
mdefine_line|#define&t;CMD_SCSI_ABORT&t;&t;0x64&t;&t;/* abort by setting time-out to zero */
DECL|macro|CMD_CHIRP_CHIRP
mdefine_line|#define&t;CMD_CHIRP_CHIRP&t;&t;0x77&t;&t;/* make a chirp chirp sound */
DECL|macro|CMD_GET_LAST_DONE
mdefine_line|#define&t;CMD_GET_LAST_DONE&t;0x78&t;&t;/* get tag of last done in progress */
DECL|macro|CMD_GET_FEATURES
mdefine_line|#define&t;CMD_GET_FEATURES&t;0x79&t;&t;/* get feature code and ESN */
DECL|macro|CMD_CLEAR_CACHE
mdefine_line|#define CMD_CLEAR_CACHE&t;&t;0x7A&t;&t;/* Clear cache on specified device */
DECL|macro|CMD_BIOS_TEST
mdefine_line|#define&t;CMD_BIOS_TEST&t;&t;0x7B&t;&t;/* Test whether or not to load BIOS */
DECL|macro|CMD_WAIT_FLUSH
mdefine_line|#define&t;CMD_WAIT_FLUSH&t;&t;0x7C&t;&t;/* wait for cache flushed and invalidate read cache */
DECL|macro|CMD_RESET_BUS
mdefine_line|#define&t;CMD_RESET_BUS&t;&t;0x7D&t;&t;/* reset the SCSI bus */
DECL|macro|CMD_STARTUP_QRY
mdefine_line|#define&t;CMD_STARTUP_QRY&t;&t;0x7E&t;&t;/* startup in progress query */
DECL|macro|CMD_RESET
mdefine_line|#define&t;CMD_RESET&t;&t;&t;0x7F&t;&t;/* reset the controller */
DECL|macro|CMD_RESTART_RESET
mdefine_line|#define&t;CMD_RESTART_RESET&t;0x80&t;&t;/* reload and restart the controller at any reset issued */
DECL|macro|CMD_SOFT_RESET
mdefine_line|#define&t;CMD_SOFT_RESET&t;&t;0x81&t;&t;/* do a soft reset NOW! */
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;Host return errors&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|ERR08_TAGGED
mdefine_line|#define&t;ERR08_TAGGED&t;&t;0x80&t;&t;/* doorbell error ored with tag */
DECL|macro|ERR16_NONE
mdefine_line|#define&t;ERR16_NONE&t;&t;&t;0x0000&t;&t;/* no errors */
DECL|macro|ERR16_SC_COND_MET
mdefine_line|#define&t;ERR16_SC_COND_MET&t;0x0004&t;&t;/* SCSI status - Condition Met */
DECL|macro|ERR16_CMD
mdefine_line|#define&t;ERR16_CMD&t;&t;&t;0x0101&t;&t;/* command error */
DECL|macro|ERR16_SC_CHECK_COND
mdefine_line|#define&t;ERR16_SC_CHECK_COND&t;0x0002&t;&t;/* SCSI status - Check Condition */
DECL|macro|ERR16_CMD_NOT
mdefine_line|#define&t;ERR16_CMD_NOT&t;&t;0x0201&t;&t;/* command not supported */
DECL|macro|ERR16_NO_DEVICE
mdefine_line|#define ERR16_NO_DEVICE     0x0301&t;&t;/* invalid device selection */
DECL|macro|ERR16_SECTOR
mdefine_line|#define&t;ERR16_SECTOR&t;&t;0x0202&t;&t;/* bad sector */
DECL|macro|ERR16_PROTECT
mdefine_line|#define&t;ERR16_PROTECT&t;&t;0x0303&t;&t;/* write protected */
DECL|macro|ERR16_NOSECTOR
mdefine_line|#define&t;ERR16_NOSECTOR&t;&t;0x0404&t;&t;/* sector not found */
DECL|macro|ERR16_MEDIA
mdefine_line|#define&t;ERR16_MEDIA&t;&t;&t;0x0C0C&t;&t;/* invalid media */
DECL|macro|ERR16_CONTROL
mdefine_line|#define&t;ERR16_CONTROL&t;&t;0x2020&t;&t;/* controller error */
DECL|macro|ERR16_CONTROL_DMA
mdefine_line|#define&t;ERR16_CONTROL_DMA&t;0x2120&t;&t;/* controller DMA engine error */
DECL|macro|ERR16_NO_ALARM
mdefine_line|#define&t;ERR16_NO_ALARM&t;&t;0x2220&t;&t;/* alarm is not active */
DECL|macro|ERR16_OP_BUSY
mdefine_line|#define&t;ERR16_OP_BUSY&t;&t;0x2320&t;&t;/* operation busy */
DECL|macro|ERR16_SEEK
mdefine_line|#define&t;ERR16_SEEK&t;&t;&t;0x4040&t;&t;/* seek failure */
DECL|macro|ERR16_DEVICE_FAIL
mdefine_line|#define&t;ERR16_DEVICE_FAIL&t;0x4140&t;&t;/* device has failed */
DECL|macro|ERR16_TIMEOUT
mdefine_line|#define ERR16_TIMEOUT&t;&t;0x8080&t;&t;/* timeout error */
DECL|macro|ERR16_DEV_NOT_READY
mdefine_line|#define&t;ERR16_DEV_NOT_READY&t;0xAAAA&t;&t;/* drive not ready */
DECL|macro|ERR16_UNDEFINED
mdefine_line|#define&t;ERR16_UNDEFINED&t;&t;0xBBBB&t;&t;/* undefined error */
DECL|macro|ERR16_WRITE_FAULT
mdefine_line|#define&t;ERR16_WRITE_FAULT&t;0xCCCC&t;&t;/* write fault */
DECL|macro|ERR16_INVALID_DEV
mdefine_line|#define ERR16_INVALID_DEV&t;0x4001&t;&t;/* invalid device access */
DECL|macro|ERR16_DEVICE_BUSY
mdefine_line|#define&t;ERR16_DEVICE_BUSY&t;0x4002&t;&t;/* device is busy */
DECL|macro|ERR16_MEMORY
mdefine_line|#define&t;ERR16_MEMORY&t;&t;0x4003&t;&t;/* device pass thru requires too much memory */
DECL|macro|ERR16_NO_FEATURE
mdefine_line|#define&t;ERR16_NO_FEATURE&t;0x40FA&t;&t;/* feature no implemented */
DECL|macro|ERR16_NOTAG
mdefine_line|#define&t;ERR16_NOTAG&t;&t;&t;0x40FD&t;&t;/* no tag space available */
DECL|macro|ERR16_NOT_READY
mdefine_line|#define&t;ERR16_NOT_READY&t;&t;0x40FE&t;&t;/* controller not ready error */
DECL|macro|ERR16_SETUP_FLASH
mdefine_line|#define&t;ERR16_SETUP_FLASH&t;0x5050&t;&t;/* error when writing setup to flash memory */
DECL|macro|ERR16_SETUP_SIZE
mdefine_line|#define&t;ERR16_SETUP_SIZE&t;0x5051&t;&t;/* setup block size error */
DECL|macro|ERR16_SENSE
mdefine_line|#define&t;ERR16_SENSE&t;&t;&t;0xFFFF&t;&t;/* sense opereration failed */
DECL|macro|ERR16_SC_BUSY
mdefine_line|#define&t;ERR16_SC_BUSY&t;&t;0x0008&t;&t;/* SCSI status - Busy */
DECL|macro|ERR16_SC_RES_CONFL
mdefine_line|#define&t;ERR16_SC_RES_CONFL&t;0x0018&t;&t;/* SCSI status - Reservation Conflict */
DECL|macro|ERR16_SC_CMD_TERM
mdefine_line|#define&t;ERR16_SC_CMD_TERM&t;0x0022&t;&t;/* SCSI status - Command Terminated */
DECL|macro|ERR16_SC_OTHER
mdefine_line|#define&t;ERR16_SC_OTHER&t;&t;0x00FF&t;&t;/* SCSI status - not recognized (any value masked) */
DECL|macro|ERR16_MEDIA_CHANGED
mdefine_line|#define&t;ERR16_MEDIA_CHANGED&t;0x8001&t;&t;/* devices media has been changed */
DECL|macro|ERR32_NONE
mdefine_line|#define&t;ERR32_NONE&t;&t;&t;0x00000000&t;/* no errors */
DECL|macro|ERR32_SC_COND_MET
mdefine_line|#define&t;ERR32_SC_COND_MET&t;0x00000004&t;/* SCSI status - Condition Met */
DECL|macro|ERR32_CMD
mdefine_line|#define&t;ERR32_CMD&t;&t;&t;0x00010101&t;/* command error */
DECL|macro|ERR32_SC_CHECK_COND
mdefine_line|#define&t;ERR32_SC_CHECK_COND&t;0x00020002&t;/* SCSI status - Check Condition */
DECL|macro|ERR32_CMD_NOT
mdefine_line|#define&t;ERR32_CMD_NOT&t;&t;0x00030201&t;/* command not supported */
DECL|macro|ERR32_NO_DEVICE
mdefine_line|#define ERR32_NO_DEVICE     0x00040301&t;/* invalid device selection */
DECL|macro|ERR32_SECTOR
mdefine_line|#define&t;ERR32_SECTOR&t;&t;0x00050202&t;/* bad sector */
DECL|macro|ERR32_PROTECT
mdefine_line|#define&t;ERR32_PROTECT&t;&t;0x00060303&t;/* write protected */
DECL|macro|ERR32_NOSECTOR
mdefine_line|#define&t;ERR32_NOSECTOR&t;&t;0x00070404&t;/* sector not found */
DECL|macro|ERR32_MEDIA
mdefine_line|#define&t;ERR32_MEDIA&t;&t;&t;0x00080C0C&t;/* invalid media */
DECL|macro|ERR32_CONTROL
mdefine_line|#define&t;ERR32_CONTROL&t;&t;0x00092020&t;/* controller error */
DECL|macro|ERR32_CONTROL_DMA
mdefine_line|#define&t;ERR32_CONTROL_DMA&t;0x000A2120&t;/* Controller DMA error */
DECL|macro|ERR32_NO_ALARM
mdefine_line|#define&t;ERR32_NO_ALARM&t;&t;0x000B2220 &t;/* alarm is not active */
DECL|macro|ERR32_OP_BUSY
mdefine_line|#define&t;ERR32_OP_BUSY&t;&t;0x000C2320&t;/* operation busy */
DECL|macro|ERR32_SEEK
mdefine_line|#define&t;ERR32_SEEK&t;&t;&t;0x000D4040&t;/* seek failure */
DECL|macro|ERR32_DEVICE_FAIL
mdefine_line|#define&t;ERR32_DEVICE_FAIL&t;0x000E4140&t;/* device has failed */
DECL|macro|ERR32_TIMEOUT
mdefine_line|#define ERR32_TIMEOUT&t;&t;0x000F8080&t;/* timeout error */
DECL|macro|ERR32_DEV_NOT_READY
mdefine_line|#define&t;ERR32_DEV_NOT_READY&t;0x0010AAAA&t;/* drive not ready */
DECL|macro|ERR32_UNDEFINED
mdefine_line|#define&t;ERR32_UNDEFINED&t;&t;0x0011BBBB&t;/* undefined error */
DECL|macro|ERR32_WRITE_FAULT
mdefine_line|#define&t;ERR32_WRITE_FAULT&t;0x0012CCCC&t;/* write fault */
DECL|macro|ERR32_INVALID_DEV
mdefine_line|#define ERR32_INVALID_DEV&t;0x00134001&t;/* invalid device access */
DECL|macro|ERR32_DEVICE_BUSY
mdefine_line|#define&t;ERR32_DEVICE_BUSY&t;0x00144002&t;/* device is busy */
DECL|macro|ERR32_MEMORY
mdefine_line|#define&t;ERR32_MEMORY&t;&t;0x00154003&t;/* device pass thru requires too much memory */
DECL|macro|ERR32_NO_FEATURE
mdefine_line|#define&t;ERR32_NO_FEATURE&t;0x001640FA&t;/* feature no implemented */
DECL|macro|ERR32_NOTAG
mdefine_line|#define&t;ERR32_NOTAG&t;&t;&t;0x001740FD&t;/* no tag space available */
DECL|macro|ERR32_NOT_READY
mdefine_line|#define&t;ERR32_NOT_READY&t;&t;0x001840FE&t;/* controller not ready error */
DECL|macro|ERR32_SETUP_FLASH
mdefine_line|#define&t;ERR32_SETUP_FLASH&t;0x00195050&t;/* error when writing setup to flash memory */
DECL|macro|ERR32_SETUP_SIZE
mdefine_line|#define&t;ERR32_SETUP_SIZE&t;0x001A5051&t;/* setup block size error */
DECL|macro|ERR32_SENSE
mdefine_line|#define&t;ERR32_SENSE&t;&t;&t;0x001BFFFF&t;/* sense opereration failed */
DECL|macro|ERR32_SC_BUSY
mdefine_line|#define&t;ERR32_SC_BUSY&t;&t;0x001C0008&t;/* SCSI status - Busy */
DECL|macro|ERR32_SC_RES_CONFL
mdefine_line|#define&t;ERR32_SC_RES_CONFL&t;0x001D0018&t;/* SCSI status - Reservation Conflict */
DECL|macro|ERR32_SC_CMD_TERM
mdefine_line|#define&t;ERR32_SC_CMD_TERM&t;0x001E0022&t;/* SCSI status - Command Terminated */
DECL|macro|ERR32_SC_OTHER
mdefine_line|#define&t;ERR32_SC_OTHER&t;&t;0x001F00FF&t;/* SCSI status - not recognized (any value masked) */
DECL|macro|ERR32_MEDIA_CHANGED
mdefine_line|#define&t;ERR32_MEDIA_CHANGED&t;0x00208001&t;/* devices media has been changed */
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Host Operating System specification codes&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|SPEC_INTERRUPT
mdefine_line|#define&t;SPEC_INTERRUPT&t;&t;0x80&t;&t;/* specification requires host interrupt */
DECL|macro|SPEC_BACKWARD_SG
mdefine_line|#define&t;SPEC_BACKWARD_SG&t;0x40&t;&t;/* specification requires scatter/gather items reversed */
DECL|macro|SPEC_DOS_BLOCK
mdefine_line|#define&t;SPEC_DOS_BLOCK&t;&t;0x01&t;&t;/* DOS DASD blocking on pass through */
DECL|macro|SPEC_OS2_V3
mdefine_line|#define&t;SPEC_OS2_V3&t;&t;&t;0x02&t;&t;/* OS/2 Warp */
DECL|macro|SPCE_SCO_3242
mdefine_line|#define&t;SPCE_SCO_3242&t;&t;0x04&t;&t;/* SCO 3.4.2.2 */
DECL|macro|SPEC_QNX_4X
mdefine_line|#define&t;SPEC_QNX_4X&t;&t;&t;0x05&t;&t;/* QNX 4.XX */
DECL|macro|SPEC_NOVELL_NWPA
mdefine_line|#define&t;SPEC_NOVELL_NWPA&t;0x08&t;&t;/* Novell NWPA scatter/gather support */
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Inquire structures&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|struct|_CNT_SCSI_INQ
r_typedef
r_struct
id|_CNT_SCSI_INQ
(brace
DECL|member|devt
id|UCHAR
id|devt
suffix:semicolon
multiline_comment|/* 00: device type */
DECL|member|devtm
id|UCHAR
id|devtm
suffix:semicolon
multiline_comment|/* 01: device type modifier */
DECL|member|svers
id|UCHAR
id|svers
suffix:semicolon
multiline_comment|/* 02: SCSI version */
DECL|member|rfmt
id|UCHAR
id|rfmt
suffix:semicolon
multiline_comment|/* 03: response data format */
DECL|member|adlen
id|UCHAR
id|adlen
suffix:semicolon
multiline_comment|/* 04: additional length of data */
DECL|member|res1
id|UCHAR
id|res1
suffix:semicolon
multiline_comment|/* 05: */
DECL|member|res2
id|UCHAR
id|res2
suffix:semicolon
multiline_comment|/* 06: */
DECL|member|fncs
id|UCHAR
id|fncs
suffix:semicolon
multiline_comment|/* 07: functional capabilities */
DECL|member|vid
id|UCHAR
id|vid
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 08: vendor ID */
DECL|member|pid
id|UCHAR
id|pid
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 10: product ID */
DECL|member|rev
id|UCHAR
id|rev
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 20: product revision */
DECL|typedef|CNT_SCSI_INQ
)brace
id|CNT_SCSI_INQ
suffix:semicolon
DECL|struct|_CNT_IDE_INQ
r_typedef
r_struct
id|_CNT_IDE_INQ
(brace
DECL|member|GeneralConfiguration
id|USHORT
id|GeneralConfiguration
suffix:semicolon
multiline_comment|/* 00 */
DECL|member|NumberOfCylinders
id|USHORT
id|NumberOfCylinders
suffix:semicolon
multiline_comment|/* 02 */
DECL|member|Reserved1
id|USHORT
id|Reserved1
suffix:semicolon
multiline_comment|/* 04 */
DECL|member|NumberOfHeads
id|USHORT
id|NumberOfHeads
suffix:semicolon
multiline_comment|/* 06 */
DECL|member|UnformattedBytesPerTrack
id|USHORT
id|UnformattedBytesPerTrack
suffix:semicolon
multiline_comment|/* 08 */
DECL|member|UnformattedBytesPerSector
id|USHORT
id|UnformattedBytesPerSector
suffix:semicolon
multiline_comment|/* 0A */
DECL|member|SectorsPerTrack
id|USHORT
id|SectorsPerTrack
suffix:semicolon
multiline_comment|/* 0C */
DECL|member|VendorUnique1
id|USHORT
id|VendorUnique1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 0E */
DECL|member|SerialNumber
id|USHORT
id|SerialNumber
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* 14 */
DECL|member|BufferType
id|USHORT
id|BufferType
suffix:semicolon
multiline_comment|/* 28 */
DECL|member|BufferSectorSize
id|USHORT
id|BufferSectorSize
suffix:semicolon
multiline_comment|/* 2A */
DECL|member|NumberOfEccBytes
id|USHORT
id|NumberOfEccBytes
suffix:semicolon
multiline_comment|/* 2C */
DECL|member|FirmwareRevision
id|USHORT
id|FirmwareRevision
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 2E */
DECL|member|ModelNumber
id|USHORT
id|ModelNumber
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* 36 */
DECL|member|MaximumBlockTransfer
id|UCHAR
id|MaximumBlockTransfer
suffix:semicolon
multiline_comment|/* 5E */
DECL|member|VendorUnique2
id|UCHAR
id|VendorUnique2
suffix:semicolon
multiline_comment|/* 5F */
DECL|member|DoubleWordIo
id|USHORT
id|DoubleWordIo
suffix:semicolon
multiline_comment|/* 60 */
DECL|member|Capabilities
id|USHORT
id|Capabilities
suffix:semicolon
multiline_comment|/* 62 */
DECL|member|Reserved2
id|USHORT
id|Reserved2
suffix:semicolon
multiline_comment|/* 64 */
DECL|member|VendorUnique3
id|UCHAR
id|VendorUnique3
suffix:semicolon
multiline_comment|/* 66 */
DECL|member|PioCycleTimingMode
id|UCHAR
id|PioCycleTimingMode
suffix:semicolon
multiline_comment|/* 67 */
DECL|member|VendorUnique4
id|UCHAR
id|VendorUnique4
suffix:semicolon
multiline_comment|/* 68 */
DECL|member|DmaCycleTimingMode
id|UCHAR
id|DmaCycleTimingMode
suffix:semicolon
multiline_comment|/* 69 */
DECL|member|TranslationFieldsValid
id|USHORT
id|TranslationFieldsValid
suffix:semicolon
multiline_comment|/* 6A */
DECL|member|NumberOfCurrentCylinders
id|USHORT
id|NumberOfCurrentCylinders
suffix:semicolon
multiline_comment|/* 6C */
DECL|member|NumberOfCurrentHeads
id|USHORT
id|NumberOfCurrentHeads
suffix:semicolon
multiline_comment|/* 6E */
DECL|member|CurrentSectorsPerTrack
id|USHORT
id|CurrentSectorsPerTrack
suffix:semicolon
multiline_comment|/* 70 */
DECL|member|CurrentSectorCapacity
id|ULONG
id|CurrentSectorCapacity
suffix:semicolon
multiline_comment|/* 72 */
DECL|typedef|CNT_IDE_INQ
)brace
id|CNT_IDE_INQ
suffix:semicolon
DECL|struct|_DASD_INQUIRE
r_typedef
r_struct
id|_DASD_INQUIRE
(brace
DECL|member|type
id|ULONG
id|type
suffix:semicolon
multiline_comment|/* 0 = SCSI, 1 = IDE */
r_union
(brace
DECL|member|scsi
id|CNT_SCSI_INQ
id|scsi
suffix:semicolon
multiline_comment|/* SCSI inquire data */
DECL|member|ide
id|CNT_IDE_INQ
id|ide
suffix:semicolon
multiline_comment|/* IDE inquire data */
DECL|member|inq
)brace
id|inq
suffix:semicolon
DECL|typedef|DASD_INQUIRE
)brace
id|DASD_INQUIRE
suffix:semicolon
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Device Codes&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|DEVC_DASD
mdefine_line|#define DEVC_DASD&t;&t;&t;0x00&t;&t;/* Direct-access Storage Device */
DECL|macro|DEVC_SEQACESS
mdefine_line|#define DEVC_SEQACESS&t;&t;0x01&t;&t;/* Sequential-access device */
DECL|macro|DEVC_PRINTER
mdefine_line|#define DEVC_PRINTER&t;&t;0x02&t;&t;/* Printer device */
DECL|macro|DEVC_PROCESSOR
mdefine_line|#define DEVC_PROCESSOR&t;&t;0x03&t;&t;/* Processor device */
DECL|macro|DEVC_WRITEONCE
mdefine_line|#define DEVC_WRITEONCE&t;&t;0x04&t;&t;/* Write-once device */
DECL|macro|DEVC_CDROM
mdefine_line|#define DEVC_CDROM&t;&t;&t;0x05&t;&t;/* CD-ROM device */
DECL|macro|DEVC_SCANNER
mdefine_line|#define DEVC_SCANNER&t;&t;0x06&t;&t;/* Scanner device */
DECL|macro|DEVC_OPTICAL
mdefine_line|#define DEVC_OPTICAL&t;&t;0x07&t;&t;/* Optical memory device */
DECL|macro|DEVC_MEDCHGR
mdefine_line|#define DEVC_MEDCHGR&t;&t;0x08&t;&t;/* Medium changer device */
DECL|macro|DEVC_DASD_REMOVABLE
mdefine_line|#define&t;DEVC_DASD_REMOVABLE&t;0x80&t;&t;/* Direct-access storage device, Removable */
DECL|macro|DEVC_NONE
mdefine_line|#define&t;DEVC_NONE&t;&t;&t;0xFF&t;&t;/* no device */
singleline_comment|// SCSI controls for RAID
DECL|macro|SC_MY_RAID
mdefine_line|#define&t;SC_MY_RAID&t;&t;&t;0xBF&t;&t;&t;
singleline_comment|// our special CDB command byte for Win95... interface
DECL|macro|MY_SCSI_QUERY0
mdefine_line|#define&t;MY_SCSI_QUERY0&t;&t;0x31&t;&t;&t;
singleline_comment|// byte 1 subcommand to query driver for RAID 0 informatation
DECL|macro|MY_SCSI_QUERY1
mdefine_line|#define&t;MY_SCSI_QUERY1&t;&t;0x32&t;&t;&t;
singleline_comment|// byte 1 subcommand to query driver for RAID 1 informatation
DECL|macro|MY_SCSI_QUERY5
mdefine_line|#define&t;MY_SCSI_QUERY5&t;&t;0x33&t;&t;&t;
singleline_comment|// byte 1 subcommand to query driver for RAID 5 informatation
DECL|macro|MY_SCSI_REBUILD
mdefine_line|#define&t;MY_SCSI_REBUILD&t;&t;0x40&t;&t;&t;
singleline_comment|// byte 1 subcommand to reconstruct a mirrored pair
DECL|macro|MY_SCSI_DEMOFAIL
mdefine_line|#define MY_SCSI_DEMOFAIL&t;0x54&t;&t;&t;
singleline_comment|// byte 1 subcommand for RAID failure demonstration
DECL|macro|MY_SCSI_ALARMMUTE
mdefine_line|#define&t;MY_SCSI_ALARMMUTE&t;0x60&t;&t;&t;
singleline_comment|// byte 1 subcommand to mute any alarm currently on
macro_line|#endif
eof
