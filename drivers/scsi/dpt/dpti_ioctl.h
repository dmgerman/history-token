multiline_comment|/***************************************************************************&n;                          dpti_ioctl.h  -  description&n;                             -------------------&n;    begin                : Thu Sep 7 2000&n;    copyright            : (C) 2001 by Adaptec&n;    email                : deanna_bonds@adaptec.com&n;&n;    See README.dpti for history, notes, license info, and credits&n; ***************************************************************************/
multiline_comment|/***************************************************************************&n; *                                                                         *&n; *   This program is free software; you can redistribute it and/or modify  *&n; *   it under the terms of the GNU General Public License as published by  *&n; *   the Free Software Foundation; either version 2 of the License, or     *&n; *   (at your option) any later version.                                   *&n; *                                                                         *&n; ***************************************************************************/
multiline_comment|/***************************************************************************&n; * This file is generated from  osd_unix.h                                 *&n; * *************************************************************************/
macro_line|#ifndef _dpti_ioctl_h
DECL|macro|_dpti_ioctl_h
mdefine_line|#define _dpti_ioctl_h
singleline_comment|// IOCTL interface commands
macro_line|#ifndef _IOWR
DECL|macro|_IOWR
macro_line|# define _IOWR(x,y,z)&t;(((x)&lt;&lt;8)|y)
macro_line|#endif
macro_line|#ifndef _IOW
DECL|macro|_IOW
macro_line|# define _IOW(x,y,z)&t;(((x)&lt;&lt;8)|y)
macro_line|#endif
macro_line|#ifndef _IOR
DECL|macro|_IOR
macro_line|# define _IOR(x,y,z)&t;(((x)&lt;&lt;8)|y)
macro_line|#endif
macro_line|#ifndef _IO
DECL|macro|_IO
macro_line|# define _IO(x,y)&t;(((x)&lt;&lt;8)|y)
macro_line|#endif
multiline_comment|/* EATA PassThrough Command&t;*/
DECL|macro|EATAUSRCMD
mdefine_line|#define EATAUSRCMD      _IOWR(&squot;D&squot;,65,EATA_CP)
multiline_comment|/* Set Debug Level If Enabled&t;*/
DECL|macro|DPT_DEBUG
mdefine_line|#define DPT_DEBUG       _IOW(&squot;D&squot;,66,int)
multiline_comment|/* Get Signature Structure&t;*/
DECL|macro|DPT_SIGNATURE
mdefine_line|#define DPT_SIGNATURE   _IOR(&squot;D&squot;,67,dpt_sig_S)
macro_line|#if defined __bsdi__
DECL|macro|DPT_SIGNATURE_PACKED
mdefine_line|#define DPT_SIGNATURE_PACKED   _IOR(&squot;D&squot;,67,dpt_sig_S_Packed)
macro_line|#endif
multiline_comment|/* Get Number Of DPT Adapters&t;*/
DECL|macro|DPT_NUMCTRLS
mdefine_line|#define DPT_NUMCTRLS    _IOR(&squot;D&squot;,68,int)
multiline_comment|/* Get Adapter Info Structure&t;*/
DECL|macro|DPT_CTRLINFO
mdefine_line|#define DPT_CTRLINFO    _IOR(&squot;D&squot;,69,CtrlInfo)
multiline_comment|/* Get Statistics If Enabled&t;*/
DECL|macro|DPT_STATINFO
mdefine_line|#define DPT_STATINFO    _IO(&squot;D&squot;,70)
multiline_comment|/* Clear Stats If Enabled&t;*/
DECL|macro|DPT_CLRSTAT
mdefine_line|#define DPT_CLRSTAT     _IO(&squot;D&squot;,71)
multiline_comment|/* Get System Info Structure&t;*/
DECL|macro|DPT_SYSINFO
mdefine_line|#define DPT_SYSINFO     _IOR(&squot;D&squot;,72,sysInfo_S)
multiline_comment|/* Set Timeout Value&t;&t;*/
DECL|macro|DPT_TIMEOUT
mdefine_line|#define DPT_TIMEOUT     _IO(&squot;D&squot;,73)
multiline_comment|/* Get config Data  &t;&t;*/
DECL|macro|DPT_CONFIG
mdefine_line|#define DPT_CONFIG      _IO(&squot;D&squot;,74)
multiline_comment|/* Get Blink LED Code&t;        */
DECL|macro|DPT_BLINKLED
mdefine_line|#define DPT_BLINKLED    _IOR(&squot;D&squot;,75,int)
multiline_comment|/* Get Statistical information (if available) */
DECL|macro|DPT_STATS_INFO
mdefine_line|#define DPT_STATS_INFO        _IOR(&squot;D&squot;,80,STATS_DATA)
multiline_comment|/* Clear the statistical information          */
DECL|macro|DPT_STATS_CLEAR
mdefine_line|#define DPT_STATS_CLEAR       _IO(&squot;D&squot;,81)
multiline_comment|/* Get Performance metrics */
DECL|macro|DPT_PERF_INFO
mdefine_line|#define DPT_PERF_INFO        _IOR(&squot;D&squot;,82,dpt_perf_t)
multiline_comment|/* Send an I2O command */
DECL|macro|I2OUSRCMD
mdefine_line|#define I2OUSRCMD&t;_IO(&squot;D&squot;,76)
multiline_comment|/* Inform driver to re-acquire LCT information */
DECL|macro|I2ORESCANCMD
mdefine_line|#define I2ORESCANCMD&t;_IO(&squot;D&squot;,77)
multiline_comment|/* Inform driver to reset adapter */
DECL|macro|I2ORESETCMD
mdefine_line|#define I2ORESETCMD&t;_IO(&squot;D&squot;,78)
multiline_comment|/* See if the target is mounted */
DECL|macro|DPT_TARGET_BUSY
mdefine_line|#define DPT_TARGET_BUSY&t;_IOR(&squot;D&squot;,79, TARGET_BUSY_T)
multiline_comment|/* Structure Returned From Get Controller Info                             */
r_typedef
r_struct
(brace
DECL|member|state
id|uCHAR
id|state
suffix:semicolon
multiline_comment|/* Operational state               */
DECL|member|id
id|uCHAR
id|id
suffix:semicolon
multiline_comment|/* Host adapter SCSI id            */
DECL|member|vect
r_int
id|vect
suffix:semicolon
multiline_comment|/* Interrupt vector number         */
DECL|member|base
r_int
id|base
suffix:semicolon
multiline_comment|/* Base I/O address                */
DECL|member|njobs
r_int
id|njobs
suffix:semicolon
multiline_comment|/* # of jobs sent to HA            */
DECL|member|qdepth
r_int
id|qdepth
suffix:semicolon
multiline_comment|/* Controller queue depth.         */
DECL|member|wakebase
r_int
id|wakebase
suffix:semicolon
multiline_comment|/* mpx wakeup base index.          */
DECL|member|SGsize
id|uLONG
id|SGsize
suffix:semicolon
multiline_comment|/* Scatter/Gather list size.       */
DECL|member|heads
r_int
id|heads
suffix:semicolon
multiline_comment|/* heads for drives on cntlr.      */
DECL|member|sectors
r_int
id|sectors
suffix:semicolon
multiline_comment|/* sectors for drives on cntlr.    */
DECL|member|do_drive32
id|uCHAR
id|do_drive32
suffix:semicolon
multiline_comment|/* Flag for Above 16 MB Ability    */
DECL|member|BusQuiet
id|uCHAR
id|BusQuiet
suffix:semicolon
multiline_comment|/* SCSI Bus Quiet Flag             */
DECL|member|idPAL
r_char
id|idPAL
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 4 Bytes Of The ID Pal           */
DECL|member|primary
id|uCHAR
id|primary
suffix:semicolon
multiline_comment|/* 1 For Primary, 0 For Secondary  */
DECL|member|eataVersion
id|uCHAR
id|eataVersion
suffix:semicolon
multiline_comment|/* EATA Version                    */
DECL|member|cpLength
id|uLONG
id|cpLength
suffix:semicolon
multiline_comment|/* EATA Command Packet Length      */
DECL|member|spLength
id|uLONG
id|spLength
suffix:semicolon
multiline_comment|/* EATA Status Packet Length       */
DECL|member|drqNum
id|uCHAR
id|drqNum
suffix:semicolon
multiline_comment|/* DRQ Index (0,5,6,7)             */
DECL|member|flag1
id|uCHAR
id|flag1
suffix:semicolon
multiline_comment|/* EATA Flags 1 (Byte 9)           */
DECL|member|flag2
id|uCHAR
id|flag2
suffix:semicolon
multiline_comment|/* EATA Flags 2 (Byte 30)          */
DECL|typedef|CtrlInfo
)brace
id|CtrlInfo
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|length
id|uSHORT
id|length
suffix:semicolon
singleline_comment|// Remaining length of this
DECL|member|drvrHBAnum
id|uSHORT
id|drvrHBAnum
suffix:semicolon
singleline_comment|// Relative HBA # used by the driver
DECL|member|baseAddr
id|uLONG
id|baseAddr
suffix:semicolon
singleline_comment|// Base I/O address
DECL|member|blinkState
id|uSHORT
id|blinkState
suffix:semicolon
singleline_comment|// Blink LED state (0=Not in blink LED)
DECL|member|pciBusNum
id|uCHAR
id|pciBusNum
suffix:semicolon
singleline_comment|// PCI Bus # (Optional)
DECL|member|pciDeviceNum
id|uCHAR
id|pciDeviceNum
suffix:semicolon
singleline_comment|// PCI Device # (Optional)
DECL|member|hbaFlags
id|uSHORT
id|hbaFlags
suffix:semicolon
singleline_comment|// Miscellaneous HBA flags
DECL|member|Interrupt
id|uSHORT
id|Interrupt
suffix:semicolon
singleline_comment|// Interrupt set for this device.
macro_line|#   if (defined(_DPT_ARC))
DECL|member|baseLength
id|uLONG
id|baseLength
suffix:semicolon
DECL|member|AdapterObject
id|ADAPTER_OBJECT
op_star
id|AdapterObject
suffix:semicolon
DECL|member|DmaLogicalAddress
id|LARGE_INTEGER
id|DmaLogicalAddress
suffix:semicolon
DECL|member|DmaVirtualAddress
id|PVOID
id|DmaVirtualAddress
suffix:semicolon
DECL|member|ReplyLogicalAddress
id|LARGE_INTEGER
id|ReplyLogicalAddress
suffix:semicolon
DECL|member|ReplyVirtualAddress
id|PVOID
id|ReplyVirtualAddress
suffix:semicolon
macro_line|#   else
DECL|member|reserved1
id|uLONG
id|reserved1
suffix:semicolon
singleline_comment|// Reserved for future expansion
DECL|member|reserved2
id|uLONG
id|reserved2
suffix:semicolon
singleline_comment|// Reserved for future expansion
DECL|member|reserved3
id|uLONG
id|reserved3
suffix:semicolon
singleline_comment|// Reserved for future expansion
macro_line|#   endif
DECL|typedef|drvrHBAinfo_S
)brace
id|drvrHBAinfo_S
suffix:semicolon
DECL|struct|TARGET_BUSY
r_typedef
r_struct
id|TARGET_BUSY
(brace
DECL|member|channel
id|uLONG
id|channel
suffix:semicolon
DECL|member|id
id|uLONG
id|id
suffix:semicolon
DECL|member|lun
id|uLONG
id|lun
suffix:semicolon
DECL|member|isBusy
id|uLONG
id|isBusy
suffix:semicolon
DECL|typedef|TARGET_BUSY_T
)brace
id|TARGET_BUSY_T
suffix:semicolon
macro_line|#endif
eof
