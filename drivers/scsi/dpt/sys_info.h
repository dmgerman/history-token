multiline_comment|/*&t;BSDI sys_info.h,v 1.6 1998/06/03 19:14:59 karels Exp&t;*/
multiline_comment|/*&n; * Copyright (c) 1996-1999 Distributed Processing Technology Corporation&n; * All rights reserved.&n; *&n; * Redistribution and use in source form, with or without modification, are&n; * permitted provided that redistributions of source code must retain the&n; * above copyright notice, this list of conditions and the following disclaimer.&n; *&n; * This software is provided `as is&squot; by Distributed Processing Technology and&n; * any express or implied warranties, including, but not limited to, the&n; * implied warranties of merchantability and fitness for a particular purpose,&n; * are disclaimed. In no event shall Distributed Processing Technology be&n; * liable for any direct, indirect, incidental, special, exemplary or&n; * consequential damages (including, but not limited to, procurement of&n; * substitute goods or services; loss of use, data, or profits; or business&n; * interruptions) however caused and on any theory of liability, whether in&n; * contract, strict liability, or tort (including negligence or otherwise)&n; * arising in any way out of the use of this driver software, even if advised&n; * of the possibility of such damage.&n; *&n; */
macro_line|#ifndef         __SYS_INFO_H
DECL|macro|__SYS_INFO_H
mdefine_line|#define         __SYS_INFO_H
multiline_comment|/*File - SYS_INFO.H&n; ****************************************************************************&n; *&n; *Description:&n; *&n; *      This file contains structure definitions for the OS dependent&n; *layer system information buffers.&n; *&n; *Copyright Distributed Processing Technology, Corp.&n; *        140 Candace Dr.&n; *        Maitland, Fl. 32751   USA&n; *        Phone: (407) 830-5522  Fax: (407) 260-5366&n; *        All Rights Reserved&n; *&n; *Author:       Don Kemper&n; *Date:         5/10/94&n; *&n; *Editors:&n; *&n; *Remarks:&n; *&n; *&n; *****************************************************************************/
multiline_comment|/*Include Files ------------------------------------------------------------- */
macro_line|#include        &quot;osd_util.h&quot;
macro_line|#ifndef NO_PACK
macro_line|#if defined (_DPT_AIX)
macro_line|#pragma options align=packed
macro_line|#else
macro_line|#pragma pack(1)
macro_line|#endif  /* aix */
macro_line|#endif  
singleline_comment|// no unpack
multiline_comment|/*struct - driveParam_S - start&n; *===========================================================================&n; *&n; *Description:&n; *&n; *      This structure defines the drive parameters seen during&n; *booting.&n; *&n; *---------------------------------------------------------------------------*/
macro_line|#ifdef  __cplusplus
DECL|struct|driveParam_S
r_struct
id|driveParam_S
(brace
macro_line|#else
r_typedef
r_struct
(brace
macro_line|#endif
DECL|member|cylinders
id|uSHORT
id|cylinders
suffix:semicolon
multiline_comment|/* Upto 1024 */
DECL|member|heads
id|uCHAR
id|heads
suffix:semicolon
multiline_comment|/* Upto 255 */
DECL|member|sectors
id|uCHAR
id|sectors
suffix:semicolon
multiline_comment|/* Upto 63 */
macro_line|#ifdef  __cplusplus
singleline_comment|//---------- Portability Additions ----------- in sp_sinfo.cpp
macro_line|#ifdef DPT_PORTABLE
id|uSHORT
id|netInsert
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
id|uSHORT
id|netExtract
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// DPT PORTABLE
singleline_comment|//--------------------------------------------
)brace
suffix:semicolon
macro_line|#else
DECL|variable|driveParam_S
)brace
id|driveParam_S
suffix:semicolon
macro_line|#endif
multiline_comment|/*driveParam_S - end */
multiline_comment|/*struct - sysInfo_S - start&n; *===========================================================================&n; *&n; *Description:&n; *&n; *      This structure defines the command system information that&n; *should be returned by every OS dependent layer.&n; *&n; *---------------------------------------------------------------------------*/
multiline_comment|/*flags - bit definitions */
DECL|macro|SI_CMOS_Valid
mdefine_line|#define SI_CMOS_Valid           0x0001
DECL|macro|SI_NumDrivesValid
mdefine_line|#define SI_NumDrivesValid       0x0002
DECL|macro|SI_ProcessorValid
mdefine_line|#define SI_ProcessorValid       0x0004
DECL|macro|SI_MemorySizeValid
mdefine_line|#define SI_MemorySizeValid      0x0008
DECL|macro|SI_DriveParamsValid
mdefine_line|#define SI_DriveParamsValid     0x0010
DECL|macro|SI_SmartROMverValid
mdefine_line|#define SI_SmartROMverValid     0x0020
DECL|macro|SI_OSversionValid
mdefine_line|#define SI_OSversionValid       0x0040
DECL|macro|SI_OSspecificValid
mdefine_line|#define SI_OSspecificValid      0x0080  /* 1 if OS structure returned */
DECL|macro|SI_BusTypeValid
mdefine_line|#define SI_BusTypeValid         0x0100
DECL|macro|SI_ALL_VALID
mdefine_line|#define SI_ALL_VALID            0x0FFF  /* All Std SysInfo is valid */
DECL|macro|SI_NO_SmartROM
mdefine_line|#define SI_NO_SmartROM          0x8000
multiline_comment|/*busType - definitions */
DECL|macro|SI_ISA_BUS
mdefine_line|#define SI_ISA_BUS      0x00
DECL|macro|SI_MCA_BUS
mdefine_line|#define SI_MCA_BUS      0x01
DECL|macro|SI_EISA_BUS
mdefine_line|#define SI_EISA_BUS     0x02
DECL|macro|SI_PCI_BUS
mdefine_line|#define SI_PCI_BUS      0x04
macro_line|#ifdef  __cplusplus
DECL|struct|sysInfo_S
r_struct
id|sysInfo_S
(brace
macro_line|#else
r_typedef
r_struct
(brace
macro_line|#endif
DECL|member|drive0CMOS
id|uCHAR
id|drive0CMOS
suffix:semicolon
multiline_comment|/* CMOS Drive 0 Type */
DECL|member|drive1CMOS
id|uCHAR
id|drive1CMOS
suffix:semicolon
multiline_comment|/* CMOS Drive 1 Type */
DECL|member|numDrives
id|uCHAR
id|numDrives
suffix:semicolon
multiline_comment|/* 0040:0075 contents */
DECL|member|processorFamily
id|uCHAR
id|processorFamily
suffix:semicolon
multiline_comment|/* Same as DPTSIG&squot;s definition */
DECL|member|processorType
id|uCHAR
id|processorType
suffix:semicolon
multiline_comment|/* Same as DPTSIG&squot;s definition */
DECL|member|smartROMMajorVersion
id|uCHAR
id|smartROMMajorVersion
suffix:semicolon
DECL|member|smartROMMinorVersion
id|uCHAR
id|smartROMMinorVersion
suffix:semicolon
multiline_comment|/* SmartROM version */
DECL|member|smartROMRevision
id|uCHAR
id|smartROMRevision
suffix:semicolon
DECL|member|flags
id|uSHORT
id|flags
suffix:semicolon
multiline_comment|/* See bit definitions above */
DECL|member|conventionalMemSize
id|uSHORT
id|conventionalMemSize
suffix:semicolon
multiline_comment|/* in KB */
DECL|member|extendedMemSize
id|uLONG
id|extendedMemSize
suffix:semicolon
multiline_comment|/* in KB */
DECL|member|osType
id|uLONG
id|osType
suffix:semicolon
multiline_comment|/* Same as DPTSIG&squot;s definition */
DECL|member|osMajorVersion
id|uCHAR
id|osMajorVersion
suffix:semicolon
DECL|member|osMinorVersion
id|uCHAR
id|osMinorVersion
suffix:semicolon
multiline_comment|/* The OS version */
DECL|member|osRevision
id|uCHAR
id|osRevision
suffix:semicolon
macro_line|#ifdef _SINIX_ADDON
DECL|member|busType
id|uCHAR
id|busType
suffix:semicolon
multiline_comment|/* See defininitions above */
DECL|member|osSubRevision
id|uSHORT
id|osSubRevision
suffix:semicolon
DECL|member|pad
id|uCHAR
id|pad
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* For alignment */
macro_line|#else
DECL|member|osSubRevision
id|uCHAR
id|osSubRevision
suffix:semicolon
DECL|member|busType
id|uCHAR
id|busType
suffix:semicolon
multiline_comment|/* See defininitions above */
DECL|member|pad
id|uCHAR
id|pad
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* For alignment */
macro_line|#endif
DECL|member|drives
id|driveParam_S
id|drives
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* SmartROM Logical Drives */
macro_line|#ifdef  __cplusplus
singleline_comment|//---------- Portability Additions ----------- in sp_sinfo.cpp
macro_line|#ifdef DPT_PORTABLE
id|uSHORT
id|netInsert
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
id|uSHORT
id|netExtract
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// DPT PORTABLE
singleline_comment|//--------------------------------------------
)brace
suffix:semicolon
macro_line|#else
DECL|variable|sysInfo_S
)brace
id|sysInfo_S
suffix:semicolon
macro_line|#endif
multiline_comment|/*sysInfo_S - end */
multiline_comment|/*struct - DOS_Info_S - start&n; *===========================================================================&n; *&n; *Description:&n; *&n; *      This structure defines the system information specific to a&n; *DOS workstation.&n; *&n; *---------------------------------------------------------------------------*/
multiline_comment|/*flags - bit definitions */
DECL|macro|DI_DOS_HIGH
mdefine_line|#define DI_DOS_HIGH             0x01    /* DOS is loaded high */
DECL|macro|DI_DPMI_VALID
mdefine_line|#define DI_DPMI_VALID           0x02    /* DPMI version is valid */
macro_line|#ifdef  __cplusplus
DECL|struct|DOS_Info_S
r_struct
id|DOS_Info_S
(brace
macro_line|#else
r_typedef
r_struct
(brace
macro_line|#endif
DECL|member|flags
id|uCHAR
id|flags
suffix:semicolon
multiline_comment|/* See bit definitions above */
DECL|member|driverLocation
id|uSHORT
id|driverLocation
suffix:semicolon
multiline_comment|/* SmartROM BIOS address */
DECL|member|DOS_version
id|uSHORT
id|DOS_version
suffix:semicolon
DECL|member|DPMI_version
id|uSHORT
id|DPMI_version
suffix:semicolon
macro_line|#ifdef  __cplusplus
singleline_comment|//---------- Portability Additions ----------- in sp_sinfo.cpp
macro_line|#ifdef DPT_PORTABLE
id|uSHORT
id|netInsert
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
id|uSHORT
id|netExtract
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// DPT PORTABLE
singleline_comment|//--------------------------------------------
)brace
suffix:semicolon
macro_line|#else
DECL|variable|DOS_Info_S
)brace
id|DOS_Info_S
suffix:semicolon
macro_line|#endif
multiline_comment|/*DOS_Info_S - end */
multiline_comment|/*struct - Netware_Info_S - start&n; *===========================================================================&n; *&n; *Description:&n; *&n; *      This structure defines the system information specific to a&n; *Netware machine.&n; *&n; *---------------------------------------------------------------------------*/
macro_line|#ifdef  __cplusplus
DECL|struct|Netware_Info_S
r_struct
id|Netware_Info_S
(brace
macro_line|#else
r_typedef
r_struct
(brace
macro_line|#endif
DECL|member|driverName
id|uCHAR
id|driverName
(braket
l_int|13
)braket
suffix:semicolon
multiline_comment|/* ie PM12NW31.DSK */
DECL|member|serverName
id|uCHAR
id|serverName
(braket
l_int|48
)braket
suffix:semicolon
DECL|member|netwareVersion
id|uCHAR
id|netwareVersion
suffix:semicolon
multiline_comment|/* The Netware OS version */
DECL|member|netwareSubVersion
id|uCHAR
id|netwareSubVersion
suffix:semicolon
DECL|member|netwareRevision
id|uCHAR
id|netwareRevision
suffix:semicolon
DECL|member|maxConnections
id|uSHORT
id|maxConnections
suffix:semicolon
multiline_comment|/* Probably  250 or 1000 */
DECL|member|connectionsInUse
id|uSHORT
id|connectionsInUse
suffix:semicolon
DECL|member|maxVolumes
id|uSHORT
id|maxVolumes
suffix:semicolon
DECL|member|unused
id|uCHAR
id|unused
suffix:semicolon
DECL|member|SFTlevel
id|uCHAR
id|SFTlevel
suffix:semicolon
DECL|member|TTSlevel
id|uCHAR
id|TTSlevel
suffix:semicolon
DECL|member|clibMajorVersion
id|uCHAR
id|clibMajorVersion
suffix:semicolon
multiline_comment|/* The CLIB.NLM version */
DECL|member|clibMinorVersion
id|uCHAR
id|clibMinorVersion
suffix:semicolon
DECL|member|clibRevision
id|uCHAR
id|clibRevision
suffix:semicolon
macro_line|#ifdef  __cplusplus
singleline_comment|//---------- Portability Additions ----------- in sp_sinfo.cpp
macro_line|#ifdef DPT_PORTABLE
id|uSHORT
id|netInsert
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
id|uSHORT
id|netExtract
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// DPT PORTABLE
singleline_comment|//--------------------------------------------
)brace
suffix:semicolon
macro_line|#else
DECL|variable|Netware_Info_S
)brace
id|Netware_Info_S
suffix:semicolon
macro_line|#endif
multiline_comment|/*Netware_Info_S - end */
multiline_comment|/*struct - OS2_Info_S - start&n; *===========================================================================&n; *&n; *Description:&n; *&n; *      This structure defines the system information specific to an&n; *OS/2 machine.&n; *&n; *---------------------------------------------------------------------------*/
macro_line|#ifdef  __cplusplus
DECL|struct|OS2_Info_S
r_struct
id|OS2_Info_S
(brace
macro_line|#else
r_typedef
r_struct
(brace
macro_line|#endif
DECL|member|something
id|uCHAR
id|something
suffix:semicolon
macro_line|#ifdef  __cplusplus
singleline_comment|//---------- Portability Additions ----------- in sp_sinfo.cpp
macro_line|#ifdef DPT_PORTABLE
id|uSHORT
id|netInsert
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
id|uSHORT
id|netExtract
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// DPT PORTABLE
singleline_comment|//--------------------------------------------
)brace
suffix:semicolon
macro_line|#else
DECL|variable|OS2_Info_S
)brace
id|OS2_Info_S
suffix:semicolon
macro_line|#endif
multiline_comment|/*OS2_Info_S - end */
multiline_comment|/*struct - WinNT_Info_S - start&n; *===========================================================================&n; *&n; *Description:&n; *&n; *      This structure defines the system information specific to a&n; *Windows NT machine.&n; *&n; *---------------------------------------------------------------------------*/
macro_line|#ifdef  __cplusplus
DECL|struct|WinNT_Info_S
r_struct
id|WinNT_Info_S
(brace
macro_line|#else
r_typedef
r_struct
(brace
macro_line|#endif
DECL|member|something
id|uCHAR
id|something
suffix:semicolon
macro_line|#ifdef  __cplusplus
singleline_comment|//---------- Portability Additions ----------- in sp_sinfo.cpp
macro_line|#ifdef DPT_PORTABLE
id|uSHORT
id|netInsert
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
id|uSHORT
id|netExtract
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// DPT PORTABLE
singleline_comment|//--------------------------------------------
)brace
suffix:semicolon
macro_line|#else
DECL|variable|WinNT_Info_S
)brace
id|WinNT_Info_S
suffix:semicolon
macro_line|#endif
multiline_comment|/*WinNT_Info_S - end */
multiline_comment|/*struct - SCO_Info_S - start&n; *===========================================================================&n; *&n; *Description:&n; *&n; *      This structure defines the system information specific to an&n; *SCO UNIX machine.&n; *&n; *---------------------------------------------------------------------------*/
macro_line|#ifdef  __cplusplus
DECL|struct|SCO_Info_S
r_struct
id|SCO_Info_S
(brace
macro_line|#else
r_typedef
r_struct
(brace
macro_line|#endif
DECL|member|something
id|uCHAR
id|something
suffix:semicolon
macro_line|#ifdef  __cplusplus
singleline_comment|//---------- Portability Additions ----------- in sp_sinfo.cpp
macro_line|#ifdef DPT_PORTABLE
id|uSHORT
id|netInsert
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
id|uSHORT
id|netExtract
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// DPT PORTABLE
singleline_comment|//--------------------------------------------
)brace
suffix:semicolon
macro_line|#else
DECL|variable|SCO_Info_S
)brace
id|SCO_Info_S
suffix:semicolon
macro_line|#endif
multiline_comment|/*SCO_Info_S - end */
multiline_comment|/*struct - USL_Info_S - start&n; *===========================================================================&n; *&n; *Description:&n; *&n; *      This structure defines the system information specific to a&n; *USL UNIX machine.&n; *&n; *---------------------------------------------------------------------------*/
macro_line|#ifdef  __cplusplus
DECL|struct|USL_Info_S
r_struct
id|USL_Info_S
(brace
macro_line|#else
r_typedef
r_struct
(brace
macro_line|#endif
DECL|member|something
id|uCHAR
id|something
suffix:semicolon
macro_line|#ifdef  __cplusplus
singleline_comment|//---------- Portability Additions ----------- in sp_sinfo.cpp
macro_line|#ifdef DPT_PORTABLE
id|uSHORT
id|netInsert
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
id|uSHORT
id|netExtract
c_func
(paren
id|dptBuffer_S
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|// DPT PORTABLE
singleline_comment|//--------------------------------------------
)brace
suffix:semicolon
macro_line|#else
DECL|variable|USL_Info_S
)brace
id|USL_Info_S
suffix:semicolon
macro_line|#endif
multiline_comment|/*USL_Info_S - end */
multiline_comment|/* Restore default structure packing */
macro_line|#ifndef NO_UNPACK
macro_line|#if defined (_DPT_AIX)
macro_line|#pragma options align=reset
macro_line|#elif defined (UNPACK_FOUR)
macro_line|#pragma pack(4)
macro_line|#else
macro_line|#pragma pack()
macro_line|#endif  /* aix */
macro_line|#endif  
singleline_comment|// no unpack
macro_line|#endif  
singleline_comment|// __SYS_INFO_H
eof
