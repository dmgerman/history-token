multiline_comment|/*&n; *  Copyright (c) 2000-2001 LSI Logic Corporation.&n; *&n; *&n; *           Name:  MPI_CNFG.H&n; *          Title:  MPI Config message, structures, and Pages&n; *  Creation Date:  July 27, 2000&n; *&n; *    MPI Version:  01.01.09&n; *&n; *  Version History&n; *  ---------------&n; *&n; *  Date      Version   Description&n; *  --------  --------  ------------------------------------------------------&n; *  05-08-00  00.10.01  Original release for 0.10 spec dated 4/26/2000.&n; *  06-06-00  01.00.01  Update version number for 1.0 release.&n; *  06-08-00  01.00.02  Added _PAGEVERSION definitions for all pages.&n; *                      Added FcPhLowestVersion, FcPhHighestVersion, Reserved2&n; *                      fields to FC_DEVICE_0 page, updated the page version.&n; *                      Changed _FREE_RUNNING_CLOCK to _PACING_TRANSFERS in&n; *                      SCSI_PORT_0, SCSI_DEVICE_0 and SCSI_DEVICE_1 pages&n; *                      and updated the page versions.&n; *                      Added _RESPONSE_ID_MASK definition to SCSI_PORT_1&n; *                      page and updated the page version.&n; *                      Added Information field and _INFO_PARAMS_NEGOTIATED&n; *                      definitionto SCSI_DEVICE_0 page.&n; *  06-22-00  01.00.03  Removed batch controls from LAN_0 page and updated the&n; *                      page version.&n; *                      Added BucketsRemaining to LAN_1 page, redefined the&n; *                      state values, and updated the page version.&n; *                      Revised bus width definitions in SCSI_PORT_0,&n; *                      SCSI_DEVICE_0 and SCSI_DEVICE_1 pages.&n; *  06-30-00  01.00.04  Added MaxReplySize to LAN_1 page and updated the page&n; *                      version.&n; *                      Moved FC_DEVICE_0 PageAddress description to spec.&n; *  07-27-00  01.00.05  Corrected the SubsystemVendorID and SubsystemID field&n; *                      widths in IOC_0 page and updated the page version.&n; *  11-02-00  01.01.01  Original release for post 1.0 work&n; *                      Added Manufacturing pages, IO Unit Page 2, SCSI SPI&n; *                      Port Page 2, FC Port Page 4, FC Port Page 5&n; *  11-15-00  01.01.02  Interim changes to match proposals&n; *  12-04-00  01.01.03  Config page changes to match MPI rev 1.00.01.&n; *  12-05-00  01.01.04  Modified config page actions.&n; *  01-09-01  01.01.05  Added defines for page address formats.&n; *                      Data size for Manufacturing pages 2 and 3 no longer&n; *                      defined here.&n; *                      Io Unit Page 2 size is fixed at 4 adapters and some&n; *                      flags were changed.&n; *                      SCSI Port Page 2 Device Settings modified.&n; *                      New fields added to FC Port Page 0 and some flags&n; *                      cleaned up.&n; *                      Removed impedance flash from FC Port Page 1.&n; *                      Added FC Port pages 6 and 7.&n; *  01-25-01  01.01.06  Added MaxInitiators field to FcPortPage0.&n; *  01-29-01  01.01.07  Changed some defines to make them 32 character unique.&n; *                      Added some LinkType defines for FcPortPage0.&n; *  02-20-01  01.01.08  Started using MPI_POINTER.&n; *  02-27-01  01.01.09  Replaced MPI_CONFIG_PAGETYPE_SCSI_LUN with&n; *                      MPI_CONFIG_PAGETYPE_RAID_VOLUME.&n; *                      Added definitions and structures for IOC Page 2 and&n; *                      RAID Volume Page 2.&n; *  --------------------------------------------------------------------------&n; */
macro_line|#ifndef MPI_CNFG_H
DECL|macro|MPI_CNFG_H
mdefine_line|#define MPI_CNFG_H
multiline_comment|/*****************************************************************************&n;*&n;*       C o n f i g    M e s s a g e    a n d    S t r u c t u r e s&n;*&n;*****************************************************************************/
DECL|struct|_CONFIG_PAGE_HEADER
r_typedef
r_struct
id|_CONFIG_PAGE_HEADER
(brace
DECL|member|PageVersion
id|U8
id|PageVersion
suffix:semicolon
DECL|member|PageLength
id|U8
id|PageLength
suffix:semicolon
DECL|member|PageNumber
id|U8
id|PageNumber
suffix:semicolon
DECL|member|PageType
id|U8
id|PageType
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_HEADER
DECL|typedef|PTR_CONFIG_PAGE_HEADER
)brace
id|fCONFIG_PAGE_HEADER
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_HEADER
comma
DECL|typedef|ConfigPageHeader_t
DECL|typedef|pConfigPageHeader_t
id|ConfigPageHeader_t
comma
id|MPI_POINTER
id|pConfigPageHeader_t
suffix:semicolon
DECL|union|_CONFIG_PAGE_HEADER_UNION
r_typedef
r_union
id|_CONFIG_PAGE_HEADER_UNION
(brace
DECL|member|Struct
id|ConfigPageHeader_t
id|Struct
suffix:semicolon
DECL|member|Bytes
id|U8
id|Bytes
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|Word16
id|U16
id|Word16
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|Word32
id|U32
id|Word32
suffix:semicolon
DECL|typedef|ConfigPageHeaderUnion
DECL|typedef|pConfigPageHeaderUnion
)brace
id|ConfigPageHeaderUnion
comma
id|MPI_POINTER
id|pConfigPageHeaderUnion
comma
DECL|typedef|fCONFIG_PAGE_HEADER_UNION
DECL|typedef|PTR_CONFIG_PAGE_HEADER_UNION
id|fCONFIG_PAGE_HEADER_UNION
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_HEADER_UNION
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*  PageType field values                                                   */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_CONFIG_PAGEATTR_READ_ONLY
mdefine_line|#define MPI_CONFIG_PAGEATTR_READ_ONLY               (0x00)
DECL|macro|MPI_CONFIG_PAGEATTR_CHANGEABLE
mdefine_line|#define MPI_CONFIG_PAGEATTR_CHANGEABLE              (0x10)
DECL|macro|MPI_CONFIG_PAGEATTR_PERSISTENT
mdefine_line|#define MPI_CONFIG_PAGEATTR_PERSISTENT              (0x20)
DECL|macro|MPI_CONFIG_PAGEATTR_MASK
mdefine_line|#define MPI_CONFIG_PAGEATTR_MASK                    (0xF0)
DECL|macro|MPI_CONFIG_PAGETYPE_IO_UNIT
mdefine_line|#define MPI_CONFIG_PAGETYPE_IO_UNIT                 (0x00)
DECL|macro|MPI_CONFIG_PAGETYPE_IOC
mdefine_line|#define MPI_CONFIG_PAGETYPE_IOC                     (0x01)
DECL|macro|MPI_CONFIG_PAGETYPE_BIOS
mdefine_line|#define MPI_CONFIG_PAGETYPE_BIOS                    (0x02)
DECL|macro|MPI_CONFIG_PAGETYPE_SCSI_PORT
mdefine_line|#define MPI_CONFIG_PAGETYPE_SCSI_PORT               (0x03)
DECL|macro|MPI_CONFIG_PAGETYPE_SCSI_DEVICE
mdefine_line|#define MPI_CONFIG_PAGETYPE_SCSI_DEVICE             (0x04)
DECL|macro|MPI_CONFIG_PAGETYPE_FC_PORT
mdefine_line|#define MPI_CONFIG_PAGETYPE_FC_PORT                 (0x05)
DECL|macro|MPI_CONFIG_PAGETYPE_FC_DEVICE
mdefine_line|#define MPI_CONFIG_PAGETYPE_FC_DEVICE               (0x06)
DECL|macro|MPI_CONFIG_PAGETYPE_LAN
mdefine_line|#define MPI_CONFIG_PAGETYPE_LAN                     (0x07)
DECL|macro|MPI_CONFIG_PAGETYPE_RAID_VOLUME
mdefine_line|#define MPI_CONFIG_PAGETYPE_RAID_VOLUME             (0x08)
DECL|macro|MPI_CONFIG_PAGETYPE_MANUFACTURING
mdefine_line|#define MPI_CONFIG_PAGETYPE_MANUFACTURING           (0x09)
DECL|macro|MPI_CONFIG_PAGETYPE_MASK
mdefine_line|#define MPI_CONFIG_PAGETYPE_MASK                    (0x0F)
DECL|macro|MPI_CONFIG_TYPENUM_MASK
mdefine_line|#define MPI_CONFIG_TYPENUM_MASK                     (0x0FFF)
multiline_comment|/****************************************************************************&n; *  PageAddres field values&n; ****************************************************************************/
DECL|macro|MPI_SCSI_PORT_PGAD_PORT_MASK
mdefine_line|#define MPI_SCSI_PORT_PGAD_PORT_MASK                (0x000000FF)
DECL|macro|MPI_SCSI_DEVICE_TARGET_ID_MASK
mdefine_line|#define MPI_SCSI_DEVICE_TARGET_ID_MASK              (0x000000FF)
DECL|macro|MPI_SCSI_DEVICE_TARGET_ID_SHIFT
mdefine_line|#define MPI_SCSI_DEVICE_TARGET_ID_SHIFT             (0)
DECL|macro|MPI_SCSI_DEVICE_BUS_MASK
mdefine_line|#define MPI_SCSI_DEVICE_BUS_MASK                    (0x0000FF00)
DECL|macro|MPI_SCSI_DEVICE_BUS_SHIFT
mdefine_line|#define MPI_SCSI_DEVICE_BUS_SHIFT                   (8)
DECL|macro|MPI_SCSI_LUN_TARGET_ID_MASK
mdefine_line|#define MPI_SCSI_LUN_TARGET_ID_MASK                 (0x000000FF)
DECL|macro|MPI_SCSI_LUN_TARGET_ID_SHIFT
mdefine_line|#define MPI_SCSI_LUN_TARGET_ID_SHIFT                (0)
DECL|macro|MPI_SCSI_LUN_BUS_MASK
mdefine_line|#define MPI_SCSI_LUN_BUS_MASK                       (0x0000FF00)
DECL|macro|MPI_SCSI_LUN_BUS_SHIFT
mdefine_line|#define MPI_SCSI_LUN_BUS_SHIFT                      (8)
DECL|macro|MPI_SCSI_LUN_LUN_MASK
mdefine_line|#define MPI_SCSI_LUN_LUN_MASK                       (0x00FF0000)
DECL|macro|MPI_SCSI_LUN_LUN_SHIFT
mdefine_line|#define MPI_SCSI_LUN_LUN_SHIFT                      (16)
DECL|macro|MPI_FC_PORT_PGAD_PORT_MASK
mdefine_line|#define MPI_FC_PORT_PGAD_PORT_MASK                  (0xF0000000)
DECL|macro|MPI_FC_PORT_PGAD_PORT_SHIFT
mdefine_line|#define MPI_FC_PORT_PGAD_PORT_SHIFT                 (28)
DECL|macro|MPI_FC_PORT_PGAD_FORM_MASK
mdefine_line|#define MPI_FC_PORT_PGAD_FORM_MASK                  (0x0F000000)
DECL|macro|MPI_FC_PORT_PGAD_FORM_INDEX
mdefine_line|#define MPI_FC_PORT_PGAD_FORM_INDEX                 (0x01000000)
DECL|macro|MPI_FC_PORT_PGAD_INDEX_MASK
mdefine_line|#define MPI_FC_PORT_PGAD_INDEX_MASK                 (0x0000FFFF)
DECL|macro|MPI_FC_PORT_PGAD_INDEX_SHIFT
mdefine_line|#define MPI_FC_PORT_PGAD_INDEX_SHIFT                (0)
DECL|macro|MPI_FC_DEVICE_PGAD_PORT_MASK
mdefine_line|#define MPI_FC_DEVICE_PGAD_PORT_MASK                (0xF0000000)
DECL|macro|MPI_FC_DEVICE_PGAD_PORT_SHIFT
mdefine_line|#define MPI_FC_DEVICE_PGAD_PORT_SHIFT               (28)
DECL|macro|MPI_FC_DEVICE_PGAD_FORM_MASK
mdefine_line|#define MPI_FC_DEVICE_PGAD_FORM_MASK                (0x0F000000)
DECL|macro|MPI_FC_DEVICE_PGAD_FORM_NEXT_DID
mdefine_line|#define MPI_FC_DEVICE_PGAD_FORM_NEXT_DID            (0x00000000)
DECL|macro|MPI_FC_DEVICE_PGAD_ND_PORT_MASK
mdefine_line|#define MPI_FC_DEVICE_PGAD_ND_PORT_MASK             (0xF0000000)
DECL|macro|MPI_FC_DEVICE_PGAD_ND_PORT_SHIFT
mdefine_line|#define MPI_FC_DEVICE_PGAD_ND_PORT_SHIFT            (28)
DECL|macro|MPI_FC_DEVICE_PGAD_ND_DID_MASK
mdefine_line|#define MPI_FC_DEVICE_PGAD_ND_DID_MASK              (0x00FFFFFF)
DECL|macro|MPI_FC_DEVICE_PGAD_ND_DID_SHIFT
mdefine_line|#define MPI_FC_DEVICE_PGAD_ND_DID_SHIFT             (0)
DECL|macro|MPI_FC_DEVICE_PGAD_FORM_BUS_TID
mdefine_line|#define MPI_FC_DEVICE_PGAD_FORM_BUS_TID             (0x01000000)
DECL|macro|MPI_FC_DEVICE_PGAD_BT_BUS_MASK
mdefine_line|#define MPI_FC_DEVICE_PGAD_BT_BUS_MASK              (0x0000FF00)
DECL|macro|MPI_FC_DEVICE_PGAD_BT_BUS_SHIFT
mdefine_line|#define MPI_FC_DEVICE_PGAD_BT_BUS_SHIFT             (8)
DECL|macro|MPI_FC_DEVICE_PGAD_BT_TID_MASK
mdefine_line|#define MPI_FC_DEVICE_PGAD_BT_TID_MASK              (0x000000FF)
DECL|macro|MPI_FC_DEVICE_PGAD_BT_TID_SHIFT
mdefine_line|#define MPI_FC_DEVICE_PGAD_BT_TID_SHIFT             (0)
multiline_comment|/****************************************************************************/
multiline_comment|/*  Config Request Message                                                          */
multiline_comment|/****************************************************************************/
DECL|struct|_MSG_CONFIG
r_typedef
r_struct
id|_MSG_CONFIG
(brace
DECL|member|Action
id|U8
id|Action
suffix:semicolon
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
DECL|member|ChainOffset
id|U8
id|ChainOffset
suffix:semicolon
DECL|member|Function
id|U8
id|Function
suffix:semicolon
DECL|member|Reserved1
id|U8
id|Reserved1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
DECL|member|Reserved2
id|U8
id|Reserved2
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|PageAddress
id|U32
id|PageAddress
suffix:semicolon
DECL|member|PageBufferSGE
id|SGE_IO_UNION
id|PageBufferSGE
suffix:semicolon
DECL|typedef|MSG_CONFIG
DECL|typedef|PTR_MSG_CONFIG
)brace
id|MSG_CONFIG
comma
id|MPI_POINTER
id|PTR_MSG_CONFIG
comma
DECL|typedef|Config_t
DECL|typedef|pConfig_t
id|Config_t
comma
id|MPI_POINTER
id|pConfig_t
suffix:semicolon
multiline_comment|/****************************************************************************/
multiline_comment|/*  Action field values                                                     */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_CONFIG_ACTION_PAGE_HEADER
mdefine_line|#define MPI_CONFIG_ACTION_PAGE_HEADER               (0x00)
multiline_comment|/*#define MPI_CONFIG_ACTION_PAGE_READ                 (0x01) */
multiline_comment|/* obsolete */
DECL|macro|MPI_CONFIG_ACTION_PAGE_READ_CURRENT
mdefine_line|#define MPI_CONFIG_ACTION_PAGE_READ_CURRENT         (0x01)
multiline_comment|/*#define MPI_CONFIG_ACTION_PAGE_WRITE                (0x02) */
multiline_comment|/* obsolete */
DECL|macro|MPI_CONFIG_ACTION_PAGE_WRITE_CURRENT
mdefine_line|#define MPI_CONFIG_ACTION_PAGE_WRITE_CURRENT        (0x02)
DECL|macro|MPI_CONFIG_ACTION_PAGE_DEFAULT
mdefine_line|#define MPI_CONFIG_ACTION_PAGE_DEFAULT              (0x03)
multiline_comment|/*#define MPI_CONFIG_ACTION_PAGE_WRITE_COMMIT         (0x04) */
multiline_comment|/* obsolete */
DECL|macro|MPI_CONFIG_ACTION_PAGE_WRITE_NVRAM
mdefine_line|#define MPI_CONFIG_ACTION_PAGE_WRITE_NVRAM          (0x04)
DECL|macro|MPI_CONFIG_ACTION_PAGE_READ_DEFAULT
mdefine_line|#define MPI_CONFIG_ACTION_PAGE_READ_DEFAULT         (0x05)
DECL|macro|MPI_CONFIG_ACTION_PAGE_READ_NVRAM
mdefine_line|#define MPI_CONFIG_ACTION_PAGE_READ_NVRAM           (0x06)
multiline_comment|/* Config Reply Message */
DECL|struct|_MSG_CONFIG_REPLY
r_typedef
r_struct
id|_MSG_CONFIG_REPLY
(brace
DECL|member|Action
id|U8
id|Action
suffix:semicolon
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
DECL|member|MsgLength
id|U8
id|MsgLength
suffix:semicolon
DECL|member|Function
id|U8
id|Function
suffix:semicolon
DECL|member|Reserved1
id|U8
id|Reserved1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|MsgFlags
id|U8
id|MsgFlags
suffix:semicolon
DECL|member|MsgContext
id|U32
id|MsgContext
suffix:semicolon
DECL|member|Reserved2
id|U8
id|Reserved2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|IOCStatus
id|U16
id|IOCStatus
suffix:semicolon
DECL|member|IOCLogInfo
id|U32
id|IOCLogInfo
suffix:semicolon
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|typedef|MSG_CONFIG_REPLY
DECL|typedef|PTR_MSG_CONFIG_REPLY
)brace
id|MSG_CONFIG_REPLY
comma
id|MPI_POINTER
id|PTR_MSG_CONFIG_REPLY
comma
DECL|typedef|ConfigReply_t
DECL|typedef|pConfigReply_t
id|ConfigReply_t
comma
id|MPI_POINTER
id|pConfigReply_t
suffix:semicolon
multiline_comment|/*****************************************************************************&n;*&n;*               C o n f i g u r a t i o n    P a g e s&n;*&n;*****************************************************************************/
multiline_comment|/****************************************************************************/
multiline_comment|/*  Manufacturing Config pages                                              */
multiline_comment|/****************************************************************************/
DECL|macro|MPI_MANUFACTPAGE_DEVICEID_FC909
mdefine_line|#define MPI_MANUFACTPAGE_DEVICEID_FC909             (0x0621)
DECL|macro|MPI_MANUFACTPAGE_DEVICEID_FC919
mdefine_line|#define MPI_MANUFACTPAGE_DEVICEID_FC919             (0x0624)
DECL|macro|MPI_MANUFACTPAGE_DEVICEID_FC929
mdefine_line|#define MPI_MANUFACTPAGE_DEVICEID_FC929             (0x0622)
DECL|macro|MPI_MANUFACTPAGE_DEVID_53C1030
mdefine_line|#define MPI_MANUFACTPAGE_DEVID_53C1030              (0x0030)
DECL|macro|MPI_MANUFACTPAGE_DEVID_53C1030ZC
mdefine_line|#define MPI_MANUFACTPAGE_DEVID_53C1030ZC            (0x0031)
DECL|macro|MPI_MANUFACTPAGE_DEVID_53C1035
mdefine_line|#define MPI_MANUFACTPAGE_DEVID_53C1035              (0x0035)
DECL|struct|_CONFIG_PAGE_MANUFACTURING_0
r_typedef
r_struct
id|_CONFIG_PAGE_MANUFACTURING_0
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|ChipName
id|U8
id|ChipName
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|ChipRevision
id|U8
id|ChipRevision
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|BoardName
id|U8
id|BoardName
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|BoardAssembly
id|U8
id|BoardAssembly
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|BoardTracerNumber
id|U8
id|BoardTracerNumber
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_MANUFACTURING_0
DECL|typedef|PTR_CONFIG_PAGE_MANUFACTURING_0
)brace
id|fCONFIG_PAGE_MANUFACTURING_0
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_MANUFACTURING_0
comma
DECL|typedef|ManufacturingPage0_t
DECL|typedef|pManufacturingPage0_t
id|ManufacturingPage0_t
comma
id|MPI_POINTER
id|pManufacturingPage0_t
suffix:semicolon
DECL|macro|MPI_MANUFACTURING0_PAGEVERSION
mdefine_line|#define MPI_MANUFACTURING0_PAGEVERSION                 (0x00)
DECL|struct|_CONFIG_PAGE_MANUFACTURING_1
r_typedef
r_struct
id|_CONFIG_PAGE_MANUFACTURING_1
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|VPD
id|U8
id|VPD
(braket
l_int|256
)braket
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_MANUFACTURING_1
DECL|typedef|PTR_CONFIG_PAGE_MANUFACTURING_1
)brace
id|fCONFIG_PAGE_MANUFACTURING_1
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_MANUFACTURING_1
comma
DECL|typedef|ManufacturingPage1_t
DECL|typedef|pManufacturingPage1_t
id|ManufacturingPage1_t
comma
id|MPI_POINTER
id|pManufacturingPage1_t
suffix:semicolon
DECL|macro|MPI_MANUFACTURING1_PAGEVERSION
mdefine_line|#define MPI_MANUFACTURING1_PAGEVERSION                 (0x00)
DECL|struct|_MPI_CHIP_REVISION_ID
r_typedef
r_struct
id|_MPI_CHIP_REVISION_ID
(brace
DECL|member|DeviceID
id|U16
id|DeviceID
suffix:semicolon
DECL|member|PCIRevisionID
id|U8
id|PCIRevisionID
suffix:semicolon
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
DECL|typedef|MPI_CHIP_REVISION_ID
DECL|typedef|PTR_MPI_CHIP_REVISION_ID
)brace
id|MPI_CHIP_REVISION_ID
comma
id|MPI_POINTER
id|PTR_MPI_CHIP_REVISION_ID
comma
DECL|typedef|MpiChipRevisionId_t
DECL|typedef|pMpiChipRevisionId_t
id|MpiChipRevisionId_t
comma
id|MPI_POINTER
id|pMpiChipRevisionId_t
suffix:semicolon
DECL|struct|_CONFIG_PAGE_MANUFACTURING_2
r_typedef
r_struct
id|_CONFIG_PAGE_MANUFACTURING_2
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|ChipId
id|MPI_CHIP_REVISION_ID
id|ChipId
suffix:semicolon
DECL|member|HwSettings
id|U32
id|HwSettings
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_MANUFACTURING_2
DECL|typedef|PTR_CONFIG_PAGE_MANUFACTURING_2
)brace
id|fCONFIG_PAGE_MANUFACTURING_2
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_MANUFACTURING_2
comma
DECL|typedef|ManufacturingPage2_t
DECL|typedef|pManufacturingPage2_t
id|ManufacturingPage2_t
comma
id|MPI_POINTER
id|pManufacturingPage2_t
suffix:semicolon
DECL|macro|MPI_MANUFACTURING2_PAGEVERSION
mdefine_line|#define MPI_MANUFACTURING2_PAGEVERSION                  (0x00)
DECL|struct|_CONFIG_PAGE_MANUFACTURING_3
r_typedef
r_struct
id|_CONFIG_PAGE_MANUFACTURING_3
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|ChipId
id|MPI_CHIP_REVISION_ID
id|ChipId
suffix:semicolon
DECL|member|Info
id|U32
id|Info
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_MANUFACTURING_3
DECL|typedef|PTR_CONFIG_PAGE_MANUFACTURING_3
)brace
id|fCONFIG_PAGE_MANUFACTURING_3
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_MANUFACTURING_3
comma
DECL|typedef|ManufacturingPage3_t
DECL|typedef|pManufacturingPage3_t
id|ManufacturingPage3_t
comma
id|MPI_POINTER
id|pManufacturingPage3_t
suffix:semicolon
DECL|macro|MPI_MANUFACTURING3_PAGEVERSION
mdefine_line|#define MPI_MANUFACTURING3_PAGEVERSION                  (0x00)
multiline_comment|/****************************************************************************/
multiline_comment|/*  IO Unit Config Pages                                                    */
multiline_comment|/****************************************************************************/
DECL|struct|_CONFIG_PAGE_IO_UNIT_0
r_typedef
r_struct
id|_CONFIG_PAGE_IO_UNIT_0
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|UniqueValue
id|U64
id|UniqueValue
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_IO_UNIT_0
DECL|typedef|PTR_CONFIG_PAGE_IO_UNIT_0
)brace
id|fCONFIG_PAGE_IO_UNIT_0
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_IO_UNIT_0
comma
DECL|typedef|IOUnitPage0_t
DECL|typedef|pIOUnitPage0_t
id|IOUnitPage0_t
comma
id|MPI_POINTER
id|pIOUnitPage0_t
suffix:semicolon
DECL|macro|MPI_IOUNITPAGE0_PAGEVERSION
mdefine_line|#define MPI_IOUNITPAGE0_PAGEVERSION                     (0x00)
DECL|struct|_CONFIG_PAGE_IO_UNIT_1
r_typedef
r_struct
id|_CONFIG_PAGE_IO_UNIT_1
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|Flags
id|U32
id|Flags
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_IO_UNIT_1
DECL|typedef|PTR_CONFIG_PAGE_IO_UNIT_1
)brace
id|fCONFIG_PAGE_IO_UNIT_1
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_IO_UNIT_1
comma
DECL|typedef|IOUnitPage1_t
DECL|typedef|pIOUnitPage1_t
id|IOUnitPage1_t
comma
id|MPI_POINTER
id|pIOUnitPage1_t
suffix:semicolon
DECL|macro|MPI_IOUNITPAGE1_PAGEVERSION
mdefine_line|#define MPI_IOUNITPAGE1_PAGEVERSION                     (0x00)
DECL|macro|MPI_IOUNITPAGE1_MULTI_FUNCTION
mdefine_line|#define MPI_IOUNITPAGE1_MULTI_FUNCTION                  (0x00000000)
DECL|macro|MPI_IOUNITPAGE1_SINGLE_FUNCTION
mdefine_line|#define MPI_IOUNITPAGE1_SINGLE_FUNCTION                 (0x00000001)
DECL|macro|MPI_IOUNITPAGE1_MULTI_PATHING
mdefine_line|#define MPI_IOUNITPAGE1_MULTI_PATHING                   (0x00000002)
DECL|macro|MPI_IOUNITPAGE1_SINGLE_PATHING
mdefine_line|#define MPI_IOUNITPAGE1_SINGLE_PATHING                  (0x00000000)
DECL|macro|MPI_IOUNITPAGE1_FORCE_32
mdefine_line|#define MPI_IOUNITPAGE1_FORCE_32                        (0x00000080)
DECL|struct|_MPI_ADAPTER_INFO
r_typedef
r_struct
id|_MPI_ADAPTER_INFO
(brace
DECL|member|PciBusNumber
id|U8
id|PciBusNumber
suffix:semicolon
DECL|member|PciDeviceAndFunctionNumber
id|U8
id|PciDeviceAndFunctionNumber
suffix:semicolon
DECL|member|AdapterFlags
id|U16
id|AdapterFlags
suffix:semicolon
DECL|typedef|MPI_ADAPTER_INFO
DECL|typedef|PTR_MPI_ADAPTER_INFO
)brace
id|MPI_ADAPTER_INFO
comma
id|MPI_POINTER
id|PTR_MPI_ADAPTER_INFO
comma
DECL|typedef|MpiAdapterInfo_t
DECL|typedef|pMpiAdapterInfo_t
id|MpiAdapterInfo_t
comma
id|MPI_POINTER
id|pMpiAdapterInfo_t
suffix:semicolon
DECL|macro|MPI_ADAPTER_INFO_FLAGS_EMBEDDED
mdefine_line|#define MPI_ADAPTER_INFO_FLAGS_EMBEDDED                 (0x0001)
DECL|macro|MPI_ADAPTER_INFO_FLAGS_INIT_STATUS
mdefine_line|#define MPI_ADAPTER_INFO_FLAGS_INIT_STATUS              (0x0002)
DECL|struct|_CONFIG_PAGE_IO_UNIT_2
r_typedef
r_struct
id|_CONFIG_PAGE_IO_UNIT_2
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|Flags
id|U32
id|Flags
suffix:semicolon
DECL|member|BiosVersion
id|U32
id|BiosVersion
suffix:semicolon
DECL|member|AdapterOrder
id|MPI_ADAPTER_INFO
id|AdapterOrder
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_IO_UNIT_2
DECL|typedef|PTR_CONFIG_PAGE_IO_UNIT_2
)brace
id|fCONFIG_PAGE_IO_UNIT_2
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_IO_UNIT_2
comma
DECL|typedef|IOUnitPage2_t
DECL|typedef|pIOUnitPage2_t
id|IOUnitPage2_t
comma
id|MPI_POINTER
id|pIOUnitPage2_t
suffix:semicolon
DECL|macro|MPI_IOUNITPAGE2_PAGEVERSION
mdefine_line|#define MPI_IOUNITPAGE2_PAGEVERSION                     (0x00)
DECL|macro|MPI_IOUNITPAGE2_FLAGS_RAID_DISABLE
mdefine_line|#define MPI_IOUNITPAGE2_FLAGS_RAID_DISABLE              (0x00000001)
DECL|macro|MPI_IOUNITPAGE2_FLAGS_PAUSE_ON_ERROR
mdefine_line|#define MPI_IOUNITPAGE2_FLAGS_PAUSE_ON_ERROR            (0x00000002)
DECL|macro|MPI_IOUNITPAGE2_FLAGS_VERBOSE_ENABLE
mdefine_line|#define MPI_IOUNITPAGE2_FLAGS_VERBOSE_ENABLE            (0x00000004)
DECL|macro|MPI_IOUNITPAGE2_FLAGS_COLOR_VIDEO_DISABLE
mdefine_line|#define MPI_IOUNITPAGE2_FLAGS_COLOR_VIDEO_DISABLE       (0x00000008)
DECL|macro|MPI_IOUNITPAGE2_FLAGS_DONT_HOOK_INT_40
mdefine_line|#define MPI_IOUNITPAGE2_FLAGS_DONT_HOOK_INT_40          (0x00000010)
multiline_comment|/****************************************************************************/
multiline_comment|/*  IOC Config Pages                                                        */
multiline_comment|/****************************************************************************/
DECL|struct|_CONFIG_PAGE_IOC_0
r_typedef
r_struct
id|_CONFIG_PAGE_IOC_0
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|TotalNVStore
id|U32
id|TotalNVStore
suffix:semicolon
DECL|member|FreeNVStore
id|U32
id|FreeNVStore
suffix:semicolon
DECL|member|VendorID
id|U16
id|VendorID
suffix:semicolon
DECL|member|DeviceID
id|U16
id|DeviceID
suffix:semicolon
DECL|member|RevisionID
id|U8
id|RevisionID
suffix:semicolon
DECL|member|Reserved
id|U8
id|Reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ClassCode
id|U32
id|ClassCode
suffix:semicolon
DECL|member|SubsystemVendorID
id|U16
id|SubsystemVendorID
suffix:semicolon
DECL|member|SubsystemID
id|U16
id|SubsystemID
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_IOC_0
DECL|typedef|PTR_CONFIG_PAGE_IOC_0
)brace
id|fCONFIG_PAGE_IOC_0
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_IOC_0
comma
DECL|typedef|IOCPage0_t
DECL|typedef|pIOCPage0_t
id|IOCPage0_t
comma
id|MPI_POINTER
id|pIOCPage0_t
suffix:semicolon
DECL|macro|MPI_IOCPAGE0_PAGEVERSION
mdefine_line|#define MPI_IOCPAGE0_PAGEVERSION                        (0x01)
DECL|struct|_CONFIG_PAGE_IOC_1
r_typedef
r_struct
id|_CONFIG_PAGE_IOC_1
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|Flags
id|U32
id|Flags
suffix:semicolon
DECL|member|CoalescingTimeout
id|U32
id|CoalescingTimeout
suffix:semicolon
DECL|member|CoalescingDepth
id|U8
id|CoalescingDepth
suffix:semicolon
DECL|member|Reserved
id|U8
id|Reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_IOC_1
DECL|typedef|PTR_CONFIG_PAGE_IOC_1
)brace
id|fCONFIG_PAGE_IOC_1
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_IOC_1
comma
DECL|typedef|IOCPage1_t
DECL|typedef|pIOCPage1_t
id|IOCPage1_t
comma
id|MPI_POINTER
id|pIOCPage1_t
suffix:semicolon
DECL|macro|MPI_IOCPAGE1_PAGEVERSION
mdefine_line|#define MPI_IOCPAGE1_PAGEVERSION                        (0x00)
DECL|macro|MPI_IOCPAGE1_REPLY_COALESCING
mdefine_line|#define MPI_IOCPAGE1_REPLY_COALESCING                   (0x00000001)
DECL|struct|_CONFIG_PAGE_IOC_2_RAID_VOL
r_typedef
r_struct
id|_CONFIG_PAGE_IOC_2_RAID_VOL
(brace
DECL|member|VolumeTargetID
id|U8
id|VolumeTargetID
suffix:semicolon
DECL|member|VolumeBus
id|U8
id|VolumeBus
suffix:semicolon
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
DECL|member|VolumeVersionMinor
id|U8
id|VolumeVersionMinor
suffix:semicolon
DECL|member|VolumeVersionMajor
id|U8
id|VolumeVersionMajor
suffix:semicolon
DECL|member|VolumeRaidType
id|U8
id|VolumeRaidType
suffix:semicolon
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_IOC_2_RAID_VOL
DECL|typedef|PTR_CONFIG_PAGE_IOC_2_RAID_VOL
)brace
id|fCONFIG_PAGE_IOC_2_RAID_VOL
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_IOC_2_RAID_VOL
comma
DECL|typedef|ConfigPageIoc2RaidVol_t
DECL|typedef|pConfigPageIoc2RaidVol_t
id|ConfigPageIoc2RaidVol_t
comma
id|MPI_POINTER
id|pConfigPageIoc2RaidVol_t
suffix:semicolon
DECL|struct|_CONFIG_PAGE_IOC_2
r_typedef
r_struct
id|_CONFIG_PAGE_IOC_2
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|CapabilitiesFlags
id|U32
id|CapabilitiesFlags
suffix:semicolon
DECL|member|NumActiveVolumes
id|U8
id|NumActiveVolumes
suffix:semicolon
DECL|member|MaxVolumes
id|U8
id|MaxVolumes
suffix:semicolon
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
DECL|member|RaidVolume
id|fCONFIG_PAGE_IOC_2_RAID_VOL
id|RaidVolume
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_IOC_2
DECL|typedef|PTR_CONFIG_PAGE_IOC_2
)brace
id|fCONFIG_PAGE_IOC_2
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_IOC_2
comma
DECL|typedef|IOCPage2_t
DECL|typedef|pIOCPage2_t
id|IOCPage2_t
comma
id|MPI_POINTER
id|pIOCPage2_t
suffix:semicolon
DECL|macro|MPI_IOCPAGE2_PAGEVERSION
mdefine_line|#define MPI_IOCPAGE2_PAGEVERSION                        (0x00)
multiline_comment|/* IOC Page 2 Capabilities flags */
DECL|macro|MPI_IOCPAGE2_CAP_FLAGS_RAID_0_SUPPORT
mdefine_line|#define MPI_IOCPAGE2_CAP_FLAGS_RAID_0_SUPPORT           (0x00000001)
DECL|macro|MPI_IOCPAGE2_CAP_FLAGS_RAID_1_SUPPORT
mdefine_line|#define MPI_IOCPAGE2_CAP_FLAGS_RAID_1_SUPPORT           (0x00000002)
DECL|macro|MPI_IOCPAGE2_CAP_FLAGS_LSI_MIRROR_SUPPORT
mdefine_line|#define MPI_IOCPAGE2_CAP_FLAGS_LSI_MIRROR_SUPPORT       (0x00000004)
DECL|macro|MPI_IOCPAGE2_CAP_FLAGS_RAID_5_SUPPORT
mdefine_line|#define MPI_IOCPAGE2_CAP_FLAGS_RAID_5_SUPPORT           (0x00000008)
DECL|macro|MPI_IOCPAGE2_CAP_FLAGS_RAID_10_SUPPORT
mdefine_line|#define MPI_IOCPAGE2_CAP_FLAGS_RAID_10_SUPPORT          (0x00000010)
multiline_comment|/* IOC Page 2 Volume RAID Type values */
DECL|macro|MPI_IOCPAGE2_VOL_TYPE_RAID_0
mdefine_line|#define MPI_IOCPAGE2_VOL_TYPE_RAID_0                    (0x00)
DECL|macro|MPI_IOCPAGE2_VOL_TYPE_RAID_1
mdefine_line|#define MPI_IOCPAGE2_VOL_TYPE_RAID_1                    (0x01)
DECL|macro|MPI_IOCPAGE2_VOL_TYPE_LSI_MIRROR
mdefine_line|#define MPI_IOCPAGE2_VOL_TYPE_LSI_MIRROR                (0x02)
DECL|macro|MPI_IOCPAGE2_VOL_TYPE_RAID_5
mdefine_line|#define MPI_IOCPAGE2_VOL_TYPE_RAID_5                    (0x05)
DECL|macro|MPI_IOCPAGE2_VOL_TYPE_RAID_10
mdefine_line|#define MPI_IOCPAGE2_VOL_TYPE_RAID_10                   (0x0A)
multiline_comment|/****************************************************************************/
multiline_comment|/*  SCSI Port Config Pages                                                  */
multiline_comment|/****************************************************************************/
DECL|struct|_CONFIG_PAGE_SCSI_PORT_0
r_typedef
r_struct
id|_CONFIG_PAGE_SCSI_PORT_0
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|Capabilities
id|U32
id|Capabilities
suffix:semicolon
DECL|member|PhysicalInterface
id|U32
id|PhysicalInterface
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_SCSI_PORT_0
DECL|typedef|PTR_CONFIG_PAGE_SCSI_PORT_0
)brace
id|fCONFIG_PAGE_SCSI_PORT_0
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_SCSI_PORT_0
comma
DECL|typedef|SCSIPortPage0_t
DECL|typedef|pSCSIPortPage0_t
id|SCSIPortPage0_t
comma
id|MPI_POINTER
id|pSCSIPortPage0_t
suffix:semicolon
DECL|macro|MPI_SCSIPORTPAGE0_PAGEVERSION
mdefine_line|#define MPI_SCSIPORTPAGE0_PAGEVERSION                   (0x01)
DECL|macro|MPI_SCSIPORTPAGE0_CAP_IU
mdefine_line|#define MPI_SCSIPORTPAGE0_CAP_IU                        (0x00000001)
DECL|macro|MPI_SCSIPORTPAGE0_CAP_DT
mdefine_line|#define MPI_SCSIPORTPAGE0_CAP_DT                        (0x00000002)
DECL|macro|MPI_SCSIPORTPAGE0_CAP_QAS
mdefine_line|#define MPI_SCSIPORTPAGE0_CAP_QAS                       (0x00000004)
DECL|macro|MPI_SCSIPORTPAGE0_CAP_PACING_TRANSFERS
mdefine_line|#define MPI_SCSIPORTPAGE0_CAP_PACING_TRANSFERS          (0x00000008)
DECL|macro|MPI_SCSIPORTPAGE0_CAP_MIN_SYNC_PERIOD_MASK
mdefine_line|#define MPI_SCSIPORTPAGE0_CAP_MIN_SYNC_PERIOD_MASK      (0x0000FF00)
DECL|macro|MPI_SCSIPORTPAGE0_CAP_MAX_SYNC_OFFSET_MASK
mdefine_line|#define MPI_SCSIPORTPAGE0_CAP_MAX_SYNC_OFFSET_MASK      (0x00FF0000)
DECL|macro|MPI_SCSIPORTPAGE0_CAP_WIDE
mdefine_line|#define MPI_SCSIPORTPAGE0_CAP_WIDE                      (0x20000000)
DECL|macro|MPI_SCSIPORTPAGE0_CAP_AIP
mdefine_line|#define MPI_SCSIPORTPAGE0_CAP_AIP                       (0x80000000)
DECL|macro|MPI_SCSIPORTPAGE0_PHY_SIGNAL_TYPE_MASK
mdefine_line|#define MPI_SCSIPORTPAGE0_PHY_SIGNAL_TYPE_MASK          (0x00000003)
DECL|macro|MPI_SCSIPORTPAGE0_PHY_SIGNAL_HVD
mdefine_line|#define MPI_SCSIPORTPAGE0_PHY_SIGNAL_HVD                (0x01)
DECL|macro|MPI_SCSIPORTPAGE0_PHY_SIGNAL_SE
mdefine_line|#define MPI_SCSIPORTPAGE0_PHY_SIGNAL_SE                 (0x02)
DECL|macro|MPI_SCSIPORTPAGE0_PHY_SIGNAL_LVD
mdefine_line|#define MPI_SCSIPORTPAGE0_PHY_SIGNAL_LVD                (0x03)
DECL|struct|_CONFIG_PAGE_SCSI_PORT_1
r_typedef
r_struct
id|_CONFIG_PAGE_SCSI_PORT_1
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|Configuration
id|U32
id|Configuration
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_SCSI_PORT_1
DECL|typedef|PTR_CONFIG_PAGE_SCSI_PORT_1
)brace
id|fCONFIG_PAGE_SCSI_PORT_1
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_SCSI_PORT_1
comma
DECL|typedef|SCSIPortPage1_t
DECL|typedef|pSCSIPortPage1_t
id|SCSIPortPage1_t
comma
id|MPI_POINTER
id|pSCSIPortPage1_t
suffix:semicolon
DECL|macro|MPI_SCSIPORTPAGE1_PAGEVERSION
mdefine_line|#define MPI_SCSIPORTPAGE1_PAGEVERSION                   (0x01)
DECL|macro|MPI_SCSIPORTPAGE1_CFG_PORT_SCSI_ID_MASK
mdefine_line|#define MPI_SCSIPORTPAGE1_CFG_PORT_SCSI_ID_MASK         (0x000000FF)
DECL|macro|MPI_SCSIPORTPAGE1_CFG_PORT_RESPONSE_ID_MASK
mdefine_line|#define MPI_SCSIPORTPAGE1_CFG_PORT_RESPONSE_ID_MASK     (0xFFFF0000)
DECL|struct|_MPI_DEVICE_INFO
r_typedef
r_struct
id|_MPI_DEVICE_INFO
(brace
DECL|member|Timeout
id|U8
id|Timeout
suffix:semicolon
DECL|member|SyncFactor
id|U8
id|SyncFactor
suffix:semicolon
DECL|member|DeviceFlags
id|U16
id|DeviceFlags
suffix:semicolon
DECL|typedef|MPI_DEVICE_INFO
DECL|typedef|PTR_MPI_DEVICE_INFO
)brace
id|MPI_DEVICE_INFO
comma
id|MPI_POINTER
id|PTR_MPI_DEVICE_INFO
comma
DECL|typedef|MpiDeviceInfo_t
DECL|typedef|pMpiDeviceInfo_t
id|MpiDeviceInfo_t
comma
id|MPI_POINTER
id|pMpiDeviceInfo_t
suffix:semicolon
DECL|struct|_CONFIG_PAGE_SCSI_PORT_2
r_typedef
r_struct
id|_CONFIG_PAGE_SCSI_PORT_2
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|PortFlags
id|U32
id|PortFlags
suffix:semicolon
DECL|member|PortSettings
id|U32
id|PortSettings
suffix:semicolon
DECL|member|DeviceSettings
id|MPI_DEVICE_INFO
id|DeviceSettings
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_SCSI_PORT_2
DECL|typedef|PTR_CONFIG_PAGE_SCSI_PORT_2
)brace
id|fCONFIG_PAGE_SCSI_PORT_2
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_SCSI_PORT_2
comma
DECL|typedef|SCSIPortPage2_t
DECL|typedef|pSCSIPortPage2_t
id|SCSIPortPage2_t
comma
id|MPI_POINTER
id|pSCSIPortPage2_t
suffix:semicolon
DECL|macro|MPI_SCSIPORTPAGE2_PAGEVERSION
mdefine_line|#define MPI_SCSIPORTPAGE2_PAGEVERSION                       (0x01)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_FLAGS_SCAN_HIGH_TO_LOW
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_FLAGS_SCAN_HIGH_TO_LOW       (0x00000001)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_FLAGS_PARITY_ENABLE
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_FLAGS_PARITY_ENABLE          (0x00000002)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_FLAGS_AVOID_SCSI_RESET
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_FLAGS_AVOID_SCSI_RESET       (0x00000004)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_FLAGS_ALTERNATE_CHS
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_FLAGS_ALTERNATE_CHS          (0x00000008)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_FLAGS_TERMINATION_DISABLE
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_FLAGS_TERMINATION_DISABLE    (0x00000010)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_HOST_ID_MASK
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_HOST_ID_MASK                 (0x0000000F)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_MASK_INIT_HBA
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_MASK_INIT_HBA                (0x00000030)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_DISABLE_INIT_HBA
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_DISABLE_INIT_HBA             (0x00000000)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_BIOS_INIT_HBA
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_BIOS_INIT_HBA                (0x00000010)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_OS_INIT_HBA
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_OS_INIT_HBA                  (0x00000020)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_BIOS_OS_INIT_HBA
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_BIOS_OS_INIT_HBA             (0x00000030)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_REMOVABLE_MEDIA
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_REMOVABLE_MEDIA              (0x000000C0)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_SPINUP_DELAY_MASK
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_SPINUP_DELAY_MASK            (0x00000F00)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_MASK_NEGO_MASTER_SETTINGS
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_MASK_NEGO_MASTER_SETTINGS    (0x00003000)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_NEGO_MASTER_SETTINGS
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_NEGO_MASTER_SETTINGS         (0x00000000)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_NONE_MASTER_SETTINGS
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_NONE_MASTER_SETTINGS         (0x00000001)
DECL|macro|MPI_SCSIPORTPAGE2_PORT_ALL_MASTER_SETTINGS
mdefine_line|#define MPI_SCSIPORTPAGE2_PORT_ALL_MASTER_SETTINGS          (0x00000003)
DECL|macro|MPI_SCSIPORTPAGE2_DEVICE_DISCONNECT_ENABLE
mdefine_line|#define MPI_SCSIPORTPAGE2_DEVICE_DISCONNECT_ENABLE          (0x00000001)
DECL|macro|MPI_SCSIPORTPAGE2_DEVICE_ID_SCAN_ENABLE
mdefine_line|#define MPI_SCSIPORTPAGE2_DEVICE_ID_SCAN_ENABLE             (0x00000002)
DECL|macro|MPI_SCSIPORTPAGE2_DEVICE_LUN_SCAN_ENABLE
mdefine_line|#define MPI_SCSIPORTPAGE2_DEVICE_LUN_SCAN_ENABLE            (0x00000004)
DECL|macro|MPI_SCSIPORTPAGE2_DEVICE_TAG_QUEUE_ENABLE
mdefine_line|#define MPI_SCSIPORTPAGE2_DEVICE_TAG_QUEUE_ENABLE           (0x00000008)
DECL|macro|MPI_SCSIPORTPAGE2_DEVICE_WIDE_DISABLE
mdefine_line|#define MPI_SCSIPORTPAGE2_DEVICE_WIDE_DISABLE               (0x00000010)
DECL|macro|MPI_SCSIPORTPAGE2_DEVICE_BOOT_CHOICE
mdefine_line|#define MPI_SCSIPORTPAGE2_DEVICE_BOOT_CHOICE                (0x00000020)
multiline_comment|/****************************************************************************/
multiline_comment|/*  SCSI Target Device Config Pages                                         */
multiline_comment|/****************************************************************************/
DECL|struct|_CONFIG_PAGE_SCSI_DEVICE_0
r_typedef
r_struct
id|_CONFIG_PAGE_SCSI_DEVICE_0
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|NegotiatedParameters
id|U32
id|NegotiatedParameters
suffix:semicolon
DECL|member|Information
id|U32
id|Information
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_SCSI_DEVICE_0
DECL|typedef|PTR_CONFIG_PAGE_SCSI_DEVICE_0
)brace
id|fCONFIG_PAGE_SCSI_DEVICE_0
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_SCSI_DEVICE_0
comma
DECL|typedef|SCSIDevicePage0_t
DECL|typedef|pSCSIDevicePage0_t
id|SCSIDevicePage0_t
comma
id|MPI_POINTER
id|pSCSIDevicePage0_t
suffix:semicolon
DECL|macro|MPI_SCSIDEVPAGE0_PAGEVERSION
mdefine_line|#define MPI_SCSIDEVPAGE0_PAGEVERSION                    (0x01)
DECL|macro|MPI_SCSIDEVPAGE0_NP_IU
mdefine_line|#define MPI_SCSIDEVPAGE0_NP_IU                          (0x00000001)
DECL|macro|MPI_SCSIDEVPAGE0_NP_DT
mdefine_line|#define MPI_SCSIDEVPAGE0_NP_DT                          (0x00000002)
DECL|macro|MPI_SCSIDEVPAGE0_NP_QAS
mdefine_line|#define MPI_SCSIDEVPAGE0_NP_QAS                         (0x00000004)
DECL|macro|MPI_SCSIDEVPAGE0_NP_PACING_TRANSFERS
mdefine_line|#define MPI_SCSIDEVPAGE0_NP_PACING_TRANSFERS            (0x00000008)
DECL|macro|MPI_SCSIDEVPAGE0_NP_NEG_SYNC_PERIOD_MASK
mdefine_line|#define MPI_SCSIDEVPAGE0_NP_NEG_SYNC_PERIOD_MASK        (0x0000FF00)
DECL|macro|MPI_SCSIDEVPAGE0_NP_NEG_SYNC_OFFSET_MASK
mdefine_line|#define MPI_SCSIDEVPAGE0_NP_NEG_SYNC_OFFSET_MASK        (0x00FF0000)
DECL|macro|MPI_SCSIDEVPAGE0_NP_WIDE
mdefine_line|#define MPI_SCSIDEVPAGE0_NP_WIDE                        (0x20000000)
DECL|macro|MPI_SCSIDEVPAGE0_NP_AIP
mdefine_line|#define MPI_SCSIDEVPAGE0_NP_AIP                         (0x80000000)
DECL|macro|MPI_SCSIDEVPAGE0_INFO_PARAMS_NEGOTIATED
mdefine_line|#define MPI_SCSIDEVPAGE0_INFO_PARAMS_NEGOTIATED         (0x00000001)
DECL|struct|_CONFIG_PAGE_SCSI_DEVICE_1
r_typedef
r_struct
id|_CONFIG_PAGE_SCSI_DEVICE_1
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|RequestedParameters
id|U32
id|RequestedParameters
suffix:semicolon
DECL|member|DomainValidation
id|U32
id|DomainValidation
suffix:semicolon
DECL|member|Configuration
id|U32
id|Configuration
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_SCSI_DEVICE_1
DECL|typedef|PTR_CONFIG_PAGE_SCSI_DEVICE_1
)brace
id|fCONFIG_PAGE_SCSI_DEVICE_1
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_SCSI_DEVICE_1
comma
DECL|typedef|SCSIDevicePage1_t
DECL|typedef|pSCSIDevicePage1_t
id|SCSIDevicePage1_t
comma
id|MPI_POINTER
id|pSCSIDevicePage1_t
suffix:semicolon
DECL|macro|MPI_SCSIDEVPAGE1_PAGEVERSION
mdefine_line|#define MPI_SCSIDEVPAGE1_PAGEVERSION                    (0x01)
DECL|macro|MPI_SCSIDEVPAGE1_RP_IU
mdefine_line|#define MPI_SCSIDEVPAGE1_RP_IU                          (0x00000001)
DECL|macro|MPI_SCSIDEVPAGE1_RP_DT
mdefine_line|#define MPI_SCSIDEVPAGE1_RP_DT                          (0x00000002)
DECL|macro|MPI_SCSIDEVPAGE1_RP_QAS
mdefine_line|#define MPI_SCSIDEVPAGE1_RP_QAS                         (0x00000004)
DECL|macro|MPI_SCSIDEVPAGE1_RP_PACING_TRANSFERS
mdefine_line|#define MPI_SCSIDEVPAGE1_RP_PACING_TRANSFERS            (0x00000008)
DECL|macro|MPI_SCSIDEVPAGE1_RP_MIN_SYNC_PERIOD_MASK
mdefine_line|#define MPI_SCSIDEVPAGE1_RP_MIN_SYNC_PERIOD_MASK        (0x0000FF00)
DECL|macro|MPI_SCSIDEVPAGE1_RP_MAX_SYNC_OFFSET_MASK
mdefine_line|#define MPI_SCSIDEVPAGE1_RP_MAX_SYNC_OFFSET_MASK        (0x00FF0000)
DECL|macro|MPI_SCSIDEVPAGE1_RP_WIDE
mdefine_line|#define MPI_SCSIDEVPAGE1_RP_WIDE                        (0x20000000)
DECL|macro|MPI_SCSIDEVPAGE1_RP_AIP
mdefine_line|#define MPI_SCSIDEVPAGE1_RP_AIP                         (0x80000000)
DECL|macro|MPI_SCSIDEVPAGE1_DV_LVD_DRIVE_STRENGTH_MASK
mdefine_line|#define MPI_SCSIDEVPAGE1_DV_LVD_DRIVE_STRENGTH_MASK     (0x00000003)
DECL|macro|MPI_SCSIDEVPAGE1_DV_SE_SLEW_RATE_MASK
mdefine_line|#define MPI_SCSIDEVPAGE1_DV_SE_SLEW_RATE_MASK           (0x00000300)
DECL|macro|MPI_SCSIDEVPAGE1_CONF_PPR_ALLOWED
mdefine_line|#define MPI_SCSIDEVPAGE1_CONF_PPR_ALLOWED               (0x00000001)
multiline_comment|/****************************************************************************/
multiline_comment|/*  FC Port Config Pages                                                    */
multiline_comment|/****************************************************************************/
DECL|struct|_CONFIG_PAGE_FC_PORT_0
r_typedef
r_struct
id|_CONFIG_PAGE_FC_PORT_0
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|Flags
id|U32
id|Flags
suffix:semicolon
DECL|member|MPIPortNumber
id|U8
id|MPIPortNumber
suffix:semicolon
DECL|member|LinkType
id|U8
id|LinkType
suffix:semicolon
DECL|member|PortState
id|U8
id|PortState
suffix:semicolon
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
DECL|member|PortIdentifier
id|U32
id|PortIdentifier
suffix:semicolon
DECL|member|WWNN
id|U64
id|WWNN
suffix:semicolon
DECL|member|WWPN
id|U64
id|WWPN
suffix:semicolon
DECL|member|SupportedServiceClass
id|U32
id|SupportedServiceClass
suffix:semicolon
DECL|member|SupportedSpeeds
id|U32
id|SupportedSpeeds
suffix:semicolon
DECL|member|CurrentSpeed
id|U32
id|CurrentSpeed
suffix:semicolon
DECL|member|MaxFrameSize
id|U32
id|MaxFrameSize
suffix:semicolon
DECL|member|FabricWWNN
id|U64
id|FabricWWNN
suffix:semicolon
DECL|member|FabricWWPN
id|U64
id|FabricWWPN
suffix:semicolon
DECL|member|DiscoveredPortsCount
id|U32
id|DiscoveredPortsCount
suffix:semicolon
DECL|member|MaxInitiators
id|U32
id|MaxInitiators
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_FC_PORT_0
DECL|typedef|PTR_CONFIG_PAGE_FC_PORT_0
)brace
id|fCONFIG_PAGE_FC_PORT_0
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_FC_PORT_0
comma
DECL|typedef|FCPortPage0_t
DECL|typedef|pFCPortPage0_t
id|FCPortPage0_t
comma
id|MPI_POINTER
id|pFCPortPage0_t
suffix:semicolon
DECL|macro|MPI_FCPORTPAGE0_PAGEVERSION
mdefine_line|#define MPI_FCPORTPAGE0_PAGEVERSION                     (0x01)
DECL|macro|MPI_FCPORTPAGE0_FLAGS_PROT_MASK
mdefine_line|#define MPI_FCPORTPAGE0_FLAGS_PROT_MASK                 (0x0000000F)
DECL|macro|MPI_FCPORTPAGE0_FLAGS_PROT_FCP_INIT
mdefine_line|#define MPI_FCPORTPAGE0_FLAGS_PROT_FCP_INIT             (MPI_PORTFACTS_PROTOCOL_INITIATOR)
DECL|macro|MPI_FCPORTPAGE0_FLAGS_PROT_FCP_TARG
mdefine_line|#define MPI_FCPORTPAGE0_FLAGS_PROT_FCP_TARG             (MPI_PORTFACTS_PROTOCOL_TARGET)
DECL|macro|MPI_FCPORTPAGE0_FLAGS_PROT_LAN
mdefine_line|#define MPI_FCPORTPAGE0_FLAGS_PROT_LAN                  (MPI_PORTFACTS_PROTOCOL_LAN)
DECL|macro|MPI_FCPORTPAGE0_FLAGS_PROT_LOGBUSADDR
mdefine_line|#define MPI_FCPORTPAGE0_FLAGS_PROT_LOGBUSADDR           (MPI_PORTFACTS_PROTOCOL_LOGBUSADDR)
DECL|macro|MPI_FCPORTPAGE0_FLAGS_ALIAS_ALPA_SUPPORTED
mdefine_line|#define MPI_FCPORTPAGE0_FLAGS_ALIAS_ALPA_SUPPORTED      (0x00000010)
DECL|macro|MPI_FCPORTPAGE0_FLAGS_ALIAS_WWN_SUPPORTED
mdefine_line|#define MPI_FCPORTPAGE0_FLAGS_ALIAS_WWN_SUPPORTED       (0x00000020)
DECL|macro|MPI_FCPORTPAGE0_FLAGS_FABRIC_WWN_VALID
mdefine_line|#define MPI_FCPORTPAGE0_FLAGS_FABRIC_WWN_VALID          (0x00000030)
DECL|macro|MPI_FCPORTPAGE0_FLAGS_ATTACH_TYPE_MASK
mdefine_line|#define MPI_FCPORTPAGE0_FLAGS_ATTACH_TYPE_MASK          (0x00000700)
DECL|macro|MPI_FCPORTPAGE0_FLAGS_ATTACH_POINT_TO_POINT
mdefine_line|#define MPI_FCPORTPAGE0_FLAGS_ATTACH_POINT_TO_POINT     (0x00000000)
DECL|macro|MPI_FCPORTPAGE0_FLAGS_ATTACH_PRIVATE_LOOP
mdefine_line|#define MPI_FCPORTPAGE0_FLAGS_ATTACH_PRIVATE_LOOP       (0x00000100)
DECL|macro|MPI_FCPORTPAGE0_FLAGS_ATTACH_FABRIC_DIRECT
mdefine_line|#define MPI_FCPORTPAGE0_FLAGS_ATTACH_FABRIC_DIRECT      (0x00000200)
DECL|macro|MPI_FCPORTPAGE0_FLAGS_ATTACH_PUBLIC_LOOP
mdefine_line|#define MPI_FCPORTPAGE0_FLAGS_ATTACH_PUBLIC_LOOP        (0x00000300)
DECL|macro|MPI_FCPORTPAGE0_FLAGS_ATTACH_NO_INIT
mdefine_line|#define MPI_FCPORTPAGE0_FLAGS_ATTACH_NO_INIT            (0x00000700)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_RESERVED
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_RESERVED                  (0x00)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_OTHER
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_OTHER                     (0x01)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_UNKNOWN
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_UNKNOWN                   (0x02)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_COPPER
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_COPPER                    (0x03)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_SINGLE_1300
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_SINGLE_1300               (0x04)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_SINGLE_1500
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_SINGLE_1500               (0x05)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_50_LASER_MULTI
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_50_LASER_MULTI            (0x06)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_50_LED_MULTI
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_50_LED_MULTI              (0x07)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_62_LASER_MULTI
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_62_LASER_MULTI            (0x08)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_62_LED_MULTI
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_62_LED_MULTI              (0x09)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_MULTI_LONG_WAVE
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_MULTI_LONG_WAVE           (0x0A)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_MULTI_SHORT_WAVE
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_MULTI_SHORT_WAVE          (0x0B)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_LASER_SHORT_WAVE
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_LASER_SHORT_WAVE          (0x0C)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_LED_SHORT_WAVE
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_LED_SHORT_WAVE            (0x0D)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_1300_LONG_WAVE
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_1300_LONG_WAVE            (0x0E)
DECL|macro|MPI_FCPORTPAGE0_LTYPE_1500_LONG_WAVE
mdefine_line|#define MPI_FCPORTPAGE0_LTYPE_1500_LONG_WAVE            (0x0F)
DECL|macro|MPI_FCPORTPAGE0_PORTSTATE_UNKNOWN
mdefine_line|#define MPI_FCPORTPAGE0_PORTSTATE_UNKNOWN               (0x01)      /*(SNIA)HBA_PORTSTATE_UNKNOWN       1 Unknown */
DECL|macro|MPI_FCPORTPAGE0_PORTSTATE_ONLINE
mdefine_line|#define MPI_FCPORTPAGE0_PORTSTATE_ONLINE                (0x02)      /*(SNIA)HBA_PORTSTATE_ONLINE        2 Operational */
DECL|macro|MPI_FCPORTPAGE0_PORTSTATE_OFFLINE
mdefine_line|#define MPI_FCPORTPAGE0_PORTSTATE_OFFLINE               (0x03)      /*(SNIA)HBA_PORTSTATE_OFFLINE       3 User Offline */
DECL|macro|MPI_FCPORTPAGE0_PORTSTATE_BYPASSED
mdefine_line|#define MPI_FCPORTPAGE0_PORTSTATE_BYPASSED              (0x04)      /*(SNIA)HBA_PORTSTATE_BYPASSED      4 Bypassed */
DECL|macro|MPI_FCPORTPAGE0_PORTSTATE_DIAGNOST
mdefine_line|#define MPI_FCPORTPAGE0_PORTSTATE_DIAGNOST              (0x05)      /*(SNIA)HBA_PORTSTATE_DIAGNOSTICS   5 In diagnostics mode */
DECL|macro|MPI_FCPORTPAGE0_PORTSTATE_LINKDOWN
mdefine_line|#define MPI_FCPORTPAGE0_PORTSTATE_LINKDOWN              (0x06)      /*(SNIA)HBA_PORTSTATE_LINKDOWN      6 Link Down */
DECL|macro|MPI_FCPORTPAGE0_PORTSTATE_ERROR
mdefine_line|#define MPI_FCPORTPAGE0_PORTSTATE_ERROR                 (0x07)      /*(SNIA)HBA_PORTSTATE_ERROR         7 Port Error */
DECL|macro|MPI_FCPORTPAGE0_PORTSTATE_LOOPBACK
mdefine_line|#define MPI_FCPORTPAGE0_PORTSTATE_LOOPBACK              (0x08)      /*(SNIA)HBA_PORTSTATE_LOOPBACK      8 Loopback */
DECL|macro|MPI_FCPORTPAGE0_SUPPORT_CLASS_1
mdefine_line|#define MPI_FCPORTPAGE0_SUPPORT_CLASS_1                 (0x00000001)
DECL|macro|MPI_FCPORTPAGE0_SUPPORT_CLASS_2
mdefine_line|#define MPI_FCPORTPAGE0_SUPPORT_CLASS_2                 (0x00000002)
DECL|macro|MPI_FCPORTPAGE0_SUPPORT_CLASS_3
mdefine_line|#define MPI_FCPORTPAGE0_SUPPORT_CLASS_3                 (0x00000004)
DECL|macro|MPI_FCPORTPAGE0_SUPPORT_1GBIT_SPEED
mdefine_line|#define MPI_FCPORTPAGE0_SUPPORT_1GBIT_SPEED             (0x00000001) /* (SNIA)HBA_PORTSPEED_1GBIT 1  1 GBit/sec  */
DECL|macro|MPI_FCPORTPAGE0_SUPPORT_2GBIT_SPEED
mdefine_line|#define MPI_FCPORTPAGE0_SUPPORT_2GBIT_SPEED             (0x00000002) /* (SNIA)HBA_PORTSPEED_2GBIT 2  2 GBit/sec  */
DECL|macro|MPI_FCPORTPAGE0_SUPPORT_10GBIT_SPEED
mdefine_line|#define MPI_FCPORTPAGE0_SUPPORT_10GBIT_SPEED            (0x00000004) /* (SNIA)HBA_PORTSPEED_10GBIT 4 10 GBit/sec */
DECL|macro|MPI_FCPORTPAGE0_CURRENT_SPEED_1GBIT
mdefine_line|#define MPI_FCPORTPAGE0_CURRENT_SPEED_1GBIT             MPI_FCPORTPAGE0_SUPPORT_1GBIT_SPEED
DECL|macro|MPI_FCPORTPAGE0_CURRENT_SPEED_2GBIT
mdefine_line|#define MPI_FCPORTPAGE0_CURRENT_SPEED_2GBIT             MPI_FCPORTPAGE0_SUPPORT_2GBIT_SPEED
DECL|macro|MPI_FCPORTPAGE0_CURRENT_SPEED_10GBIT
mdefine_line|#define MPI_FCPORTPAGE0_CURRENT_SPEED_10GBIT            MPI_FCPORTPAGE0_SUPPORT_10GBIT_SPEED
DECL|struct|_CONFIG_PAGE_FC_PORT_1
r_typedef
r_struct
id|_CONFIG_PAGE_FC_PORT_1
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|Flags
id|U32
id|Flags
suffix:semicolon
DECL|member|NoSEEPROMWWNN
id|U64
id|NoSEEPROMWWNN
suffix:semicolon
DECL|member|NoSEEPROMWWPN
id|U64
id|NoSEEPROMWWPN
suffix:semicolon
DECL|member|HardALPA
id|U8
id|HardALPA
suffix:semicolon
DECL|member|LinkConfig
id|U8
id|LinkConfig
suffix:semicolon
DECL|member|TopologyConfig
id|U8
id|TopologyConfig
suffix:semicolon
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_FC_PORT_1
DECL|typedef|PTR_CONFIG_PAGE_FC_PORT_1
)brace
id|fCONFIG_PAGE_FC_PORT_1
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_FC_PORT_1
comma
DECL|typedef|FCPortPage1_t
DECL|typedef|pFCPortPage1_t
id|FCPortPage1_t
comma
id|MPI_POINTER
id|pFCPortPage1_t
suffix:semicolon
DECL|macro|MPI_FCPORTPAGE1_PAGEVERSION
mdefine_line|#define MPI_FCPORTPAGE1_PAGEVERSION                     (0x01)
DECL|macro|MPI_FCPORTPAGE1_FLAGS_SORT_BY_DID
mdefine_line|#define MPI_FCPORTPAGE1_FLAGS_SORT_BY_DID               (0x00000001)
DECL|macro|MPI_FCPORTPAGE1_FLAGS_SORT_BY_WWN
mdefine_line|#define MPI_FCPORTPAGE1_FLAGS_SORT_BY_WWN               (0x00000000)
DECL|macro|MPI_FCPORTPAGE1_FLAGS_PROT_MASK
mdefine_line|#define MPI_FCPORTPAGE1_FLAGS_PROT_MASK                 (0xF0000000)
DECL|macro|MPI_FCPORTPAGE1_FLAGS_PROT_SHIFT
mdefine_line|#define MPI_FCPORTPAGE1_FLAGS_PROT_SHIFT                (28)
DECL|macro|MPI_FCPORTPAGE1_FLAGS_PROT_FCP_INIT
mdefine_line|#define MPI_FCPORTPAGE1_FLAGS_PROT_FCP_INIT             ((U32)MPI_PORTFACTS_PROTOCOL_INITIATOR &lt;&lt; MPI_FCPORTPAGE1_FLAGS_PROT_SHIFT)
DECL|macro|MPI_FCPORTPAGE1_FLAGS_PROT_FCP_TARG
mdefine_line|#define MPI_FCPORTPAGE1_FLAGS_PROT_FCP_TARG             ((U32)MPI_PORTFACTS_PROTOCOL_TARGET &lt;&lt; MPI_FCPORTPAGE1_FLAGS_PROT_SHIFT)
DECL|macro|MPI_FCPORTPAGE1_FLAGS_PROT_LAN
mdefine_line|#define MPI_FCPORTPAGE1_FLAGS_PROT_LAN                  ((U32)MPI_PORTFACTS_PROTOCOL_LAN &lt;&lt; MPI_FCPORTPAGE1_FLAGS_PROT_SHIFT)
DECL|macro|MPI_FCPORTPAGE1_FLAGS_PROT_LOGBUSADDR
mdefine_line|#define MPI_FCPORTPAGE1_FLAGS_PROT_LOGBUSADDR           ((U32)MPI_PORTFACTS_PROTOCOL_LOGBUSADDR &lt;&lt; MPI_FCPORTPAGE1_FLAGS_PROT_SHIFT)
DECL|macro|MPI_FCPORTPAGE1_HARD_ALPA_NOT_USED
mdefine_line|#define MPI_FCPORTPAGE1_HARD_ALPA_NOT_USED              (0xFF)
DECL|macro|MPI_FCPORTPAGE1_LCONFIG_SPEED_MASK
mdefine_line|#define MPI_FCPORTPAGE1_LCONFIG_SPEED_MASK              (0x0F)
DECL|macro|MPI_FCPORTPAGE1_LCONFIG_SPEED_1GIG
mdefine_line|#define MPI_FCPORTPAGE1_LCONFIG_SPEED_1GIG              (0x00)
DECL|macro|MPI_FCPORTPAGE1_LCONFIG_SPEED_2GIG
mdefine_line|#define MPI_FCPORTPAGE1_LCONFIG_SPEED_2GIG              (0x01)
DECL|macro|MPI_FCPORTPAGE1_LCONFIG_SPEED_4GIG
mdefine_line|#define MPI_FCPORTPAGE1_LCONFIG_SPEED_4GIG              (0x02)
DECL|macro|MPI_FCPORTPAGE1_LCONFIG_SPEED_10GIG
mdefine_line|#define MPI_FCPORTPAGE1_LCONFIG_SPEED_10GIG             (0x03)
DECL|macro|MPI_FCPORTPAGE1_LCONFIG_SPEED_AUTO
mdefine_line|#define MPI_FCPORTPAGE1_LCONFIG_SPEED_AUTO              (0x0F)
DECL|macro|MPI_FCPORTPAGE1_TOPOLGY_MASK
mdefine_line|#define MPI_FCPORTPAGE1_TOPOLGY_MASK                    (0x0F)
DECL|macro|MPI_FCPORTPAGE1_TOPOLGY_NLPORT
mdefine_line|#define MPI_FCPORTPAGE1_TOPOLGY_NLPORT                  (0x01)
DECL|macro|MPI_FCPORTPAGE1_TOPOLGY_NPORT
mdefine_line|#define MPI_FCPORTPAGE1_TOPOLGY_NPORT                   (0x02)
DECL|macro|MPI_FCPORTPAGE1_TOPOLGY_AUTO
mdefine_line|#define MPI_FCPORTPAGE1_TOPOLGY_AUTO                    (0x0F)
DECL|struct|_CONFIG_PAGE_FC_PORT_2
r_typedef
r_struct
id|_CONFIG_PAGE_FC_PORT_2
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|NumberActive
id|U8
id|NumberActive
suffix:semicolon
DECL|member|ALPA
id|U8
id|ALPA
(braket
l_int|126
)braket
suffix:semicolon
DECL|member|Reserved
id|U8
id|Reserved
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_FC_PORT_2
DECL|typedef|PTR_CONFIG_PAGE_FC_PORT_2
)brace
id|fCONFIG_PAGE_FC_PORT_2
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_FC_PORT_2
comma
DECL|typedef|FCPortPage2_t
DECL|typedef|pFCPortPage2_t
id|FCPortPage2_t
comma
id|MPI_POINTER
id|pFCPortPage2_t
suffix:semicolon
DECL|macro|MPI_FCPORTPAGE2_PAGEVERSION
mdefine_line|#define MPI_FCPORTPAGE2_PAGEVERSION                     (0x00)
DECL|struct|_FC_PORT_PERSISTENT
r_typedef
r_struct
id|_FC_PORT_PERSISTENT
(brace
DECL|member|WWNN
id|U64
id|WWNN
suffix:semicolon
DECL|member|WWPN
id|U64
id|WWPN
suffix:semicolon
DECL|member|TargetID
id|U8
id|TargetID
suffix:semicolon
DECL|member|Bus
id|U8
id|Bus
suffix:semicolon
DECL|member|Flags
id|U16
id|Flags
suffix:semicolon
DECL|typedef|FC_PORT_PERSISTENT
DECL|typedef|PTR_FC_PORT_PERSISTENT
)brace
id|FC_PORT_PERSISTENT
comma
id|MPI_POINTER
id|PTR_FC_PORT_PERSISTENT
comma
DECL|typedef|PersistentData_t
DECL|typedef|pPersistentData_t
id|PersistentData_t
comma
id|MPI_POINTER
id|pPersistentData_t
suffix:semicolon
DECL|macro|MPI_PERSISTENT_FLAGS_SHIFT
mdefine_line|#define MPI_PERSISTENT_FLAGS_SHIFT                      (16)
DECL|macro|MPI_PERSISTENT_FLAGS_ENTRY_VALID
mdefine_line|#define MPI_PERSISTENT_FLAGS_ENTRY_VALID                (0x0001)
DECL|macro|MPI_PERSISTENT_FLAGS_SCAN_ID
mdefine_line|#define MPI_PERSISTENT_FLAGS_SCAN_ID                    (0x0002)
DECL|macro|MPI_PERSISTENT_FLAGS_SCAN_LUNS
mdefine_line|#define MPI_PERSISTENT_FLAGS_SCAN_LUNS                  (0x0004)
DECL|macro|MPI_PERSISTENT_FLAGS_BOOT_DEVICE
mdefine_line|#define MPI_PERSISTENT_FLAGS_BOOT_DEVICE                (0x0008)
DECL|struct|_CONFIG_PAGE_FC_PORT_3
r_typedef
r_struct
id|_CONFIG_PAGE_FC_PORT_3
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|Entry
id|FC_PORT_PERSISTENT
id|Entry
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_FC_PORT_3
DECL|typedef|PTR_CONFIG_PAGE_FC_PORT_3
)brace
id|fCONFIG_PAGE_FC_PORT_3
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_FC_PORT_3
comma
DECL|typedef|FCPortPage3_t
DECL|typedef|pFCPortPage3_t
id|FCPortPage3_t
comma
id|MPI_POINTER
id|pFCPortPage3_t
suffix:semicolon
DECL|macro|MPI_FCPORTPAGE3_PAGEVERSION
mdefine_line|#define MPI_FCPORTPAGE3_PAGEVERSION                     (0x00)
DECL|struct|_CONFIG_PAGE_FC_PORT_4
r_typedef
r_struct
id|_CONFIG_PAGE_FC_PORT_4
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|PortFlags
id|U32
id|PortFlags
suffix:semicolon
DECL|member|PortSettings
id|U32
id|PortSettings
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_FC_PORT_4
DECL|typedef|PTR_CONFIG_PAGE_FC_PORT_4
)brace
id|fCONFIG_PAGE_FC_PORT_4
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_FC_PORT_4
comma
DECL|typedef|FCPortPage4_t
DECL|typedef|pFCPortPage4_t
id|FCPortPage4_t
comma
id|MPI_POINTER
id|pFCPortPage4_t
suffix:semicolon
DECL|macro|MPI_FCPORTPAGE4_PAGEVERSION
mdefine_line|#define MPI_FCPORTPAGE4_PAGEVERSION                     (0x00)
DECL|macro|MPI_FCPORTPAGE4_PORT_FLAGS_ALTERNATE_CHS
mdefine_line|#define MPI_FCPORTPAGE4_PORT_FLAGS_ALTERNATE_CHS        (0x00000008)
DECL|macro|MPI_FCPORTPAGE4_PORT_MASK_INIT_HBA
mdefine_line|#define MPI_FCPORTPAGE4_PORT_MASK_INIT_HBA              (0x00000030)
DECL|macro|MPI_FCPORTPAGE4_PORT_DISABLE_INIT_HBA
mdefine_line|#define MPI_FCPORTPAGE4_PORT_DISABLE_INIT_HBA           (0x00000000)
DECL|macro|MPI_FCPORTPAGE4_PORT_BIOS_INIT_HBA
mdefine_line|#define MPI_FCPORTPAGE4_PORT_BIOS_INIT_HBA              (0x00000010)
DECL|macro|MPI_FCPORTPAGE4_PORT_OS_INIT_HBA
mdefine_line|#define MPI_FCPORTPAGE4_PORT_OS_INIT_HBA                (0x00000020)
DECL|macro|MPI_FCPORTPAGE4_PORT_BIOS_OS_INIT_HBA
mdefine_line|#define MPI_FCPORTPAGE4_PORT_BIOS_OS_INIT_HBA           (0x00000030)
DECL|macro|MPI_FCPORTPAGE4_PORT_REMOVABLE_MEDIA
mdefine_line|#define MPI_FCPORTPAGE4_PORT_REMOVABLE_MEDIA            (0x000000C0)
DECL|macro|MPI_FCPORTPAGE4_PORT_SPINUP_DELAY_MASK
mdefine_line|#define MPI_FCPORTPAGE4_PORT_SPINUP_DELAY_MASK          (0x00000F00)
DECL|struct|_CONFIG_PAGE_FC_PORT_5_ALIAS_INFO
r_typedef
r_struct
id|_CONFIG_PAGE_FC_PORT_5_ALIAS_INFO
(brace
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
DECL|member|AliasAlpa
id|U8
id|AliasAlpa
suffix:semicolon
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
DECL|member|AliasWWNN
id|U64
id|AliasWWNN
suffix:semicolon
DECL|member|AliasWWPN
id|U64
id|AliasWWPN
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_FC_PORT_5_ALIAS_INFO
DECL|typedef|PTR_CONFIG_PAGE_FC_PORT_5_ALIAS_INFO
)brace
id|fCONFIG_PAGE_FC_PORT_5_ALIAS_INFO
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_FC_PORT_5_ALIAS_INFO
comma
DECL|typedef|FcPortPage5AliasInfo_t
DECL|typedef|pFcPortPage5AliasInfo_t
id|FcPortPage5AliasInfo_t
comma
id|MPI_POINTER
id|pFcPortPage5AliasInfo_t
suffix:semicolon
DECL|struct|_CONFIG_PAGE_FC_PORT_5
r_typedef
r_struct
id|_CONFIG_PAGE_FC_PORT_5
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|AliasInfo
id|fCONFIG_PAGE_FC_PORT_5_ALIAS_INFO
id|AliasInfo
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_FC_PORT_5
DECL|typedef|PTR_CONFIG_PAGE_FC_PORT_5
)brace
id|fCONFIG_PAGE_FC_PORT_5
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_FC_PORT_5
comma
DECL|typedef|FCPortPage5_t
DECL|typedef|pFCPortPage5_t
id|FCPortPage5_t
comma
id|MPI_POINTER
id|pFCPortPage5_t
suffix:semicolon
DECL|macro|MPI_FCPORTPAGE5_PAGEVERSION
mdefine_line|#define MPI_FCPORTPAGE5_PAGEVERSION                     (0x00)
DECL|macro|MPI_FCPORTPAGE5_FLAGS_ALIAS_ALPA_VALID
mdefine_line|#define MPI_FCPORTPAGE5_FLAGS_ALIAS_ALPA_VALID          (0x01)
DECL|macro|MPI_FCPORTPAGE5_FLAGS_ALIAS_WWN_VALID
mdefine_line|#define MPI_FCPORTPAGE5_FLAGS_ALIAS_WWN_VALID           (0x02)
DECL|struct|_CONFIG_PAGE_FC_PORT_6
r_typedef
r_struct
id|_CONFIG_PAGE_FC_PORT_6
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|Reserved
id|U32
id|Reserved
suffix:semicolon
DECL|member|TimeSinceReset
id|U64
id|TimeSinceReset
suffix:semicolon
DECL|member|TxFrames
id|U64
id|TxFrames
suffix:semicolon
DECL|member|RxFrames
id|U64
id|RxFrames
suffix:semicolon
DECL|member|TxWords
id|U64
id|TxWords
suffix:semicolon
DECL|member|RxWords
id|U64
id|RxWords
suffix:semicolon
DECL|member|LipCount
id|U64
id|LipCount
suffix:semicolon
DECL|member|NosCount
id|U64
id|NosCount
suffix:semicolon
DECL|member|ErrorFrames
id|U64
id|ErrorFrames
suffix:semicolon
DECL|member|DumpedFrames
id|U64
id|DumpedFrames
suffix:semicolon
DECL|member|LinkFailureCount
id|U64
id|LinkFailureCount
suffix:semicolon
DECL|member|LossOfSyncCount
id|U64
id|LossOfSyncCount
suffix:semicolon
DECL|member|LossOfSignalCount
id|U64
id|LossOfSignalCount
suffix:semicolon
DECL|member|PrimativeSeqErrCount
id|U64
id|PrimativeSeqErrCount
suffix:semicolon
DECL|member|InvalidTxWordCount
id|U64
id|InvalidTxWordCount
suffix:semicolon
DECL|member|InvalidCrcCount
id|U64
id|InvalidCrcCount
suffix:semicolon
DECL|member|FcpInitiatorIoCount
id|U64
id|FcpInitiatorIoCount
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_FC_PORT_6
DECL|typedef|PTR_CONFIG_PAGE_FC_PORT_6
)brace
id|fCONFIG_PAGE_FC_PORT_6
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_FC_PORT_6
comma
DECL|typedef|FCPortPage6_t
DECL|typedef|pFCPortPage6_t
id|FCPortPage6_t
comma
id|MPI_POINTER
id|pFCPortPage6_t
suffix:semicolon
DECL|macro|MPI_FCPORTPAGE6_PAGEVERSION
mdefine_line|#define MPI_FCPORTPAGE6_PAGEVERSION                     (0x00)
DECL|struct|_CONFIG_PAGE_FC_PORT_7
r_typedef
r_struct
id|_CONFIG_PAGE_FC_PORT_7
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|Reserved
id|U32
id|Reserved
suffix:semicolon
DECL|member|PortSymbolicName
id|U8
id|PortSymbolicName
(braket
l_int|256
)braket
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_FC_PORT_7
DECL|typedef|PTR_CONFIG_PAGE_FC_PORT_7
)brace
id|fCONFIG_PAGE_FC_PORT_7
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_FC_PORT_7
comma
DECL|typedef|FCPortPage7_t
DECL|typedef|pFCPortPage7_t
id|FCPortPage7_t
comma
id|MPI_POINTER
id|pFCPortPage7_t
suffix:semicolon
DECL|macro|MPI_FCPORTPAGE7_PAGEVERSION
mdefine_line|#define MPI_FCPORTPAGE7_PAGEVERSION                     (0x00)
multiline_comment|/****************************************************************************/
multiline_comment|/*  FC Device Config Pages                                                  */
multiline_comment|/****************************************************************************/
DECL|struct|_CONFIG_PAGE_FC_DEVICE_0
r_typedef
r_struct
id|_CONFIG_PAGE_FC_DEVICE_0
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|WWNN
id|U64
id|WWNN
suffix:semicolon
DECL|member|WWPN
id|U64
id|WWPN
suffix:semicolon
DECL|member|PortIdentifier
id|U32
id|PortIdentifier
suffix:semicolon
DECL|member|Protocol
id|U8
id|Protocol
suffix:semicolon
DECL|member|Flags
id|U8
id|Flags
suffix:semicolon
DECL|member|BBCredit
id|U16
id|BBCredit
suffix:semicolon
DECL|member|MaxRxFrameSize
id|U16
id|MaxRxFrameSize
suffix:semicolon
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
DECL|member|PortNumber
id|U8
id|PortNumber
suffix:semicolon
DECL|member|FcPhLowestVersion
id|U8
id|FcPhLowestVersion
suffix:semicolon
DECL|member|FcPhHighestVersion
id|U8
id|FcPhHighestVersion
suffix:semicolon
DECL|member|CurrentTargetID
id|U8
id|CurrentTargetID
suffix:semicolon
DECL|member|CurrentBus
id|U8
id|CurrentBus
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_FC_DEVICE_0
DECL|typedef|PTR_CONFIG_PAGE_FC_DEVICE_0
)brace
id|fCONFIG_PAGE_FC_DEVICE_0
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_FC_DEVICE_0
comma
DECL|typedef|FCDevicePage0_t
DECL|typedef|pFCDevicePage0_t
id|FCDevicePage0_t
comma
id|MPI_POINTER
id|pFCDevicePage0_t
suffix:semicolon
DECL|macro|MPI_FC_DEVICE_PAGE0_PAGEVERSION
mdefine_line|#define MPI_FC_DEVICE_PAGE0_PAGEVERSION                 (0x02)
DECL|macro|MPI_FC_DEVICE_PAGE0_FLAGS_TARGETID_BUS_VALID
mdefine_line|#define MPI_FC_DEVICE_PAGE0_FLAGS_TARGETID_BUS_VALID    (0x01)
DECL|macro|MPI_FC_DEVICE_PAGE0_PROT_IP
mdefine_line|#define MPI_FC_DEVICE_PAGE0_PROT_IP                     (0x01)
DECL|macro|MPI_FC_DEVICE_PAGE0_PROT_FCP_TARGET
mdefine_line|#define MPI_FC_DEVICE_PAGE0_PROT_FCP_TARGET             (0x02)
DECL|macro|MPI_FC_DEVICE_PAGE0_PROT_FCP_INITIATOR
mdefine_line|#define MPI_FC_DEVICE_PAGE0_PROT_FCP_INITIATOR          (0x04)
DECL|macro|MPI_FC_DEVICE_PAGE0_PGAD_PORT_MASK
mdefine_line|#define MPI_FC_DEVICE_PAGE0_PGAD_PORT_MASK              (MPI_FC_DEVICE_PGAD_PORT_MASK)
DECL|macro|MPI_FC_DEVICE_PAGE0_PGAD_FORM_MASK
mdefine_line|#define MPI_FC_DEVICE_PAGE0_PGAD_FORM_MASK              (MPI_FC_DEVICE_PGAD_FORM_MASK)
DECL|macro|MPI_FC_DEVICE_PAGE0_PGAD_FORM_NEXT_DID
mdefine_line|#define MPI_FC_DEVICE_PAGE0_PGAD_FORM_NEXT_DID          (MPI_FC_DEVICE_PGAD_FORM_NEXT_DID)
DECL|macro|MPI_FC_DEVICE_PAGE0_PGAD_FORM_BUS_TID
mdefine_line|#define MPI_FC_DEVICE_PAGE0_PGAD_FORM_BUS_TID           (MPI_FC_DEVICE_PGAD_FORM_BUS_TID)
DECL|macro|MPI_FC_DEVICE_PAGE0_PGAD_DID_MASK
mdefine_line|#define MPI_FC_DEVICE_PAGE0_PGAD_DID_MASK               (MPI_FC_DEVICE_PGAD_ND_DID_MASK)
DECL|macro|MPI_FC_DEVICE_PAGE0_PGAD_BUS_MASK
mdefine_line|#define MPI_FC_DEVICE_PAGE0_PGAD_BUS_MASK               (MPI_FC_DEVICE_PGAD_BT_BUS_MASK)
DECL|macro|MPI_FC_DEVICE_PAGE0_PGAD_BUS_SHIFT
mdefine_line|#define MPI_FC_DEVICE_PAGE0_PGAD_BUS_SHIFT              (MPI_FC_DEVICE_PGAD_BT_BUS_SHIFT)
DECL|macro|MPI_FC_DEVICE_PAGE0_PGAD_TID_MASK
mdefine_line|#define MPI_FC_DEVICE_PAGE0_PGAD_TID_MASK               (MPI_FC_DEVICE_PGAD_BT_TID_MASK)
multiline_comment|/****************************************************************************/
multiline_comment|/*  RAID Volume Config Pages                                                  */
multiline_comment|/****************************************************************************/
DECL|struct|_RAIDVOL2_EM_PHYS_ID
r_typedef
r_struct
id|_RAIDVOL2_EM_PHYS_ID
(brace
DECL|member|TargetID
id|U8
id|TargetID
suffix:semicolon
DECL|member|Bus
id|U8
id|Bus
suffix:semicolon
DECL|member|IocNumber
id|U8
id|IocNumber
suffix:semicolon
DECL|member|PhysDiskNumber
id|U8
id|PhysDiskNumber
suffix:semicolon
DECL|member|Reserved
id|U8
id|Reserved
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|PhysicalDiskIdentifier
id|U8
id|PhysicalDiskIdentifier
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|ProductId
id|U8
id|ProductId
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|InfoOffset0
id|U8
id|InfoOffset0
suffix:semicolon
DECL|member|InfoSize0
id|U8
id|InfoSize0
suffix:semicolon
DECL|member|InfoOffset1
id|U8
id|InfoOffset1
suffix:semicolon
DECL|member|InfoSize1
id|U8
id|InfoSize1
suffix:semicolon
DECL|member|Info
id|U8
id|Info
(braket
l_int|32
)braket
suffix:semicolon
DECL|typedef|RAIDVOL2_EM_PHYS_ID
DECL|typedef|PTR_RAIDVOL2_EM_PHYS_ID
)brace
id|RAIDVOL2_EM_PHYS_ID
comma
id|MPI_POINTER
id|PTR_RAIDVOL2_EM_PHYS_ID
comma
DECL|typedef|RaidVol2EmPhysicalID_t
DECL|typedef|pRaidVol2EmPhysicalID_t
id|RaidVol2EmPhysicalID_t
comma
id|MPI_POINTER
id|pRaidVol2EmPhysicalID_t
suffix:semicolon
DECL|struct|_RAIDVOL2_EM_DISK_INFO
r_typedef
r_struct
id|_RAIDVOL2_EM_DISK_INFO
(brace
DECL|member|DiskStatus
id|U32
id|DiskStatus
suffix:semicolon
DECL|member|DeviceSettings
id|U32
id|DeviceSettings
suffix:semicolon
DECL|member|ErrorCount
id|U16
id|ErrorCount
suffix:semicolon
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
DECL|member|ErrorCdbByte
id|U8
id|ErrorCdbByte
suffix:semicolon
DECL|member|ErrorSenseKey
id|U8
id|ErrorSenseKey
suffix:semicolon
DECL|member|ErrorASC
id|U8
id|ErrorASC
suffix:semicolon
DECL|member|ErrorASCQ
id|U8
id|ErrorASCQ
suffix:semicolon
DECL|member|SmartCount
id|U16
id|SmartCount
suffix:semicolon
DECL|member|SmartASC
id|U8
id|SmartASC
suffix:semicolon
DECL|member|SmartASCQ
id|U8
id|SmartASCQ
suffix:semicolon
DECL|typedef|RAIDVOL2_EM_DISK_INFO
DECL|typedef|PTR_RAIDVOL2_EM_DISK_INFO
)brace
id|RAIDVOL2_EM_DISK_INFO
comma
id|MPI_POINTER
id|PTR_RAIDVOL2_EM_DISK_INFO
comma
DECL|typedef|RaidVol2EmDiskInfo_t
DECL|typedef|pRaidVol2EmDiskInfo_t
id|RaidVol2EmDiskInfo_t
comma
id|MPI_POINTER
id|pRaidVol2EmDiskInfo_t
suffix:semicolon
multiline_comment|/* RAID Volume 2 EM Physical Disk DiskStatus flags */
DECL|macro|MPI_RAIDVOLPAGE2_PHYS_DISK_PRIMARY
mdefine_line|#define MPI_RAIDVOLPAGE2_PHYS_DISK_PRIMARY              (0x00000001)
DECL|macro|MPI_RAIDVOLPAGE2_PHYS_DISK_SECONDARY
mdefine_line|#define MPI_RAIDVOLPAGE2_PHYS_DISK_SECONDARY            (0x00000002)
DECL|macro|MPI_RAIDVOLPAGE2_PHYS_DISK_HOT_SPARE
mdefine_line|#define MPI_RAIDVOLPAGE2_PHYS_DISK_HOT_SPARE            (0x00000004)
DECL|macro|MPI_RAIDVOLPAGE2_PHYS_DISK_OUT_OF_SYNC
mdefine_line|#define MPI_RAIDVOLPAGE2_PHYS_DISK_OUT_OF_SYNC          (0x00000008)
DECL|macro|MPI_RAIDVOLPAGE2_PHYS_DISK_OFFLINE
mdefine_line|#define MPI_RAIDVOLPAGE2_PHYS_DISK_OFFLINE              (0x00000010)
DECL|macro|MPI_RAIDVOLPAGE2_PHYS_DISK_NOT_RESPONDING
mdefine_line|#define MPI_RAIDVOLPAGE2_PHYS_DISK_NOT_RESPONDING       (0x00000020)
DECL|struct|_RAIDVOL2_EM_PHYSICAL_DISK
r_typedef
r_struct
id|_RAIDVOL2_EM_PHYSICAL_DISK
(brace
DECL|member|Id
id|RAIDVOL2_EM_PHYS_ID
id|Id
suffix:semicolon
DECL|member|Info
id|RAIDVOL2_EM_DISK_INFO
id|Info
suffix:semicolon
DECL|typedef|RAIDVOL2_EM_PHYSICAL_DISK
DECL|typedef|PTR_RAIDVOL2_EM_PHYSICAL_DISK
)brace
id|RAIDVOL2_EM_PHYSICAL_DISK
comma
id|MPI_POINTER
id|PTR_RAIDVOL2_EM_PHYSICAL_DISK
comma
DECL|typedef|RaidVol2EmPhysicalDisk_t
DECL|typedef|pRaidVol2EmPhysicalDisk_t
id|RaidVol2EmPhysicalDisk_t
comma
id|MPI_POINTER
id|pRaidVol2EmPhysicalDisk_t
suffix:semicolon
DECL|macro|MPI_RAIDVOLPAGE2_MAX_DISKS
mdefine_line|#define MPI_RAIDVOLPAGE2_MAX_DISKS                      (3)
DECL|struct|_CONFIG_PAGE_RAID_VOL_2
r_typedef
r_struct
id|_CONFIG_PAGE_RAID_VOL_2
(brace
DECL|member|Header
id|fCONFIG_PAGE_HEADER
id|Header
suffix:semicolon
DECL|member|VolumeStatus
id|U32
id|VolumeStatus
suffix:semicolon
DECL|member|VolumeSettings
id|U32
id|VolumeSettings
suffix:semicolon
DECL|member|Reserved
id|U32
id|Reserved
suffix:semicolon
DECL|member|MaxLba
id|U64
id|MaxLba
suffix:semicolon
DECL|member|BlockSize
id|U32
id|BlockSize
suffix:semicolon
DECL|member|InquirySize
id|U8
id|InquirySize
suffix:semicolon
DECL|member|NumPhysicalDisks
id|U8
id|NumPhysicalDisks
suffix:semicolon
DECL|member|Reserved1
id|U16
id|Reserved1
suffix:semicolon
DECL|member|InquiryData
id|U8
id|InquiryData
(braket
l_int|56
)braket
suffix:semicolon
DECL|member|EMPhysicalDisk
id|RAIDVOL2_EM_PHYSICAL_DISK
id|EMPhysicalDisk
(braket
id|MPI_RAIDVOLPAGE2_MAX_DISKS
)braket
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_RAID_VOL_2
DECL|typedef|PTR_CONFIG_PAGE_RAID_VOL_2
)brace
id|fCONFIG_PAGE_RAID_VOL_2
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_RAID_VOL_2
comma
DECL|typedef|RaidVolumePage2_t
DECL|typedef|pRaidVolumePage2_t
id|RaidVolumePage2_t
comma
id|MPI_POINTER
id|pRaidVolumePage2_t
suffix:semicolon
DECL|macro|MPI_RAIDVOLPAGE2_PAGEVERSION
mdefine_line|#define MPI_RAIDVOLPAGE2_PAGEVERSION                    (0x00)
multiline_comment|/* RAID Volume Page 2 VolumeStatus defines */
DECL|macro|MPI_RAIDVOLPAGE2_STATUS_ENABLED
mdefine_line|#define MPI_RAIDVOLPAGE2_STATUS_ENABLED                 (0x00000001)
DECL|macro|MPI_RAIDVOLPAGE2_STATUS_QUIESCED
mdefine_line|#define MPI_RAIDVOLPAGE2_STATUS_QUIESCED                (0x00000002)
DECL|macro|MPI_RAIDVOLPAGE2_STATUS_RESYNC_IN_PROGRESS
mdefine_line|#define MPI_RAIDVOLPAGE2_STATUS_RESYNC_IN_PROGRESS      (0x00000004)
DECL|macro|MPI_RAIDVOLPAGE2_STATUS_DEGRADED
mdefine_line|#define MPI_RAIDVOLPAGE2_STATUS_DEGRADED                (0x00000008)
multiline_comment|/* RAID Volume Page 2 VolumeSettings defines */
DECL|macro|MPI_RAIDVOLPAGE2_SETTING_WRITE_CACHING_ENABLE
mdefine_line|#define MPI_RAIDVOLPAGE2_SETTING_WRITE_CACHING_ENABLE   (0x00000001)
DECL|macro|MPI_RAIDVOLPAGE2_SETTING_OFFLINE_ON_SMART
mdefine_line|#define MPI_RAIDVOLPAGE2_SETTING_OFFLINE_ON_SMART       (0x00000002)
DECL|macro|MPI_RAIDVOLPAGE2_SETTING_AUTO_CONFIGURE
mdefine_line|#define MPI_RAIDVOLPAGE2_SETTING_AUTO_CONFIGURE         (0x00000004)
multiline_comment|/****************************************************************************/
multiline_comment|/* LAN Config Pages                                                         */
multiline_comment|/****************************************************************************/
DECL|struct|_CONFIG_PAGE_LAN_0
r_typedef
r_struct
id|_CONFIG_PAGE_LAN_0
(brace
DECL|member|Header
id|ConfigPageHeader_t
id|Header
suffix:semicolon
DECL|member|TxRxModes
id|U16
id|TxRxModes
suffix:semicolon
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
DECL|member|PacketPrePad
id|U32
id|PacketPrePad
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_LAN_0
DECL|typedef|PTR_CONFIG_PAGE_LAN_0
)brace
id|fCONFIG_PAGE_LAN_0
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_LAN_0
comma
DECL|typedef|LANPage0_t
DECL|typedef|pLANPage0_t
id|LANPage0_t
comma
id|MPI_POINTER
id|pLANPage0_t
suffix:semicolon
DECL|macro|MPI_LAN_PAGE0_PAGEVERSION
mdefine_line|#define MPI_LAN_PAGE0_PAGEVERSION                       (0x01)
DECL|macro|MPI_LAN_PAGE0_RETURN_LOOPBACK
mdefine_line|#define MPI_LAN_PAGE0_RETURN_LOOPBACK                   (0x0000)
DECL|macro|MPI_LAN_PAGE0_SUPPRESS_LOOPBACK
mdefine_line|#define MPI_LAN_PAGE0_SUPPRESS_LOOPBACK                 (0x0001)
DECL|macro|MPI_LAN_PAGE0_LOOPBACK_MASK
mdefine_line|#define MPI_LAN_PAGE0_LOOPBACK_MASK                     (0x0001)
DECL|struct|_CONFIG_PAGE_LAN_1
r_typedef
r_struct
id|_CONFIG_PAGE_LAN_1
(brace
DECL|member|Header
id|ConfigPageHeader_t
id|Header
suffix:semicolon
DECL|member|Reserved
id|U16
id|Reserved
suffix:semicolon
DECL|member|CurrentDeviceState
id|U8
id|CurrentDeviceState
suffix:semicolon
DECL|member|Reserved1
id|U8
id|Reserved1
suffix:semicolon
DECL|member|MinPacketSize
id|U32
id|MinPacketSize
suffix:semicolon
DECL|member|MaxPacketSize
id|U32
id|MaxPacketSize
suffix:semicolon
DECL|member|HardwareAddressLow
id|U32
id|HardwareAddressLow
suffix:semicolon
DECL|member|HardwareAddressHigh
id|U32
id|HardwareAddressHigh
suffix:semicolon
DECL|member|MaxWireSpeedLow
id|U32
id|MaxWireSpeedLow
suffix:semicolon
DECL|member|MaxWireSpeedHigh
id|U32
id|MaxWireSpeedHigh
suffix:semicolon
DECL|member|BucketsRemaining
id|U32
id|BucketsRemaining
suffix:semicolon
DECL|member|MaxReplySize
id|U32
id|MaxReplySize
suffix:semicolon
DECL|member|NegWireSpeedHigh
id|U32
id|NegWireSpeedHigh
suffix:semicolon
DECL|member|NegWireSpeedLow
id|U32
id|NegWireSpeedLow
suffix:semicolon
DECL|typedef|fCONFIG_PAGE_LAN_1
DECL|typedef|PTR_CONFIG_PAGE_LAN_1
)brace
id|fCONFIG_PAGE_LAN_1
comma
id|MPI_POINTER
id|PTR_CONFIG_PAGE_LAN_1
comma
DECL|typedef|LANPage1_t
DECL|typedef|pLANPage1_t
id|LANPage1_t
comma
id|MPI_POINTER
id|pLANPage1_t
suffix:semicolon
DECL|macro|MPI_LAN_PAGE1_PAGEVERSION
mdefine_line|#define MPI_LAN_PAGE1_PAGEVERSION                       (0x03)
DECL|macro|MPI_LAN_PAGE1_DEV_STATE_RESET
mdefine_line|#define MPI_LAN_PAGE1_DEV_STATE_RESET                   (0x00)
DECL|macro|MPI_LAN_PAGE1_DEV_STATE_OPERATIONAL
mdefine_line|#define MPI_LAN_PAGE1_DEV_STATE_OPERATIONAL             (0x01)
macro_line|#endif
eof
