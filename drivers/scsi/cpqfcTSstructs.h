multiline_comment|/* Copyright(c) 2000, Compaq Computer Corporation&n; * Fibre Channel Host Bus Adapter 64-bit, 66MHz PCI &n; * Originally developed and tested on:&n; * (front): [chip] Tachyon TS HPFC-5166A/1.2  L2C1090 ...&n; *          SP# P225CXCBFIEL6T, Rev XC&n; *          SP# 161290-001, Rev XD&n; * (back): Board No. 010008-001 A/W Rev X5, FAB REV X5&n; *  &n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; * Written by Don Zimmerman&n;*/
macro_line|#ifndef CPQFCTSSTRUCTS_H
DECL|macro|CPQFCTSSTRUCTS_H
mdefine_line|#define CPQFCTSSTRUCTS_H
macro_line|#include &lt;linux/timer.h&gt;  
singleline_comment|// timer declaration in our host data
macro_line|#include &lt;linux/tqueue.h&gt; 
singleline_comment|// task queue sched
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &quot;cpqfcTSioctl.h&quot;
DECL|macro|DbgDelay
mdefine_line|#define DbgDelay(secs) { int wait_time; printk( &quot; DbgDelay %ds &quot;, secs); &bslash;&n;                         for( wait_time=jiffies + (secs*HZ); &bslash;&n;&t;&t;         wait_time &gt; jiffies ;) ; }
DECL|macro|CPQFCTS_DRIVER_VER
mdefine_line|#define CPQFCTS_DRIVER_VER(maj,min,submin) ((maj&lt;&lt;16)|(min&lt;&lt;8)|(submin))
DECL|macro|VER_MAJOR
mdefine_line|#define VER_MAJOR 1
DECL|macro|VER_MINOR
mdefine_line|#define VER_MINOR 3
DECL|macro|VER_SUBMINOR
mdefine_line|#define VER_SUBMINOR 4
singleline_comment|// Macros for kernel (esp. SMP) tracing using a PCI analyzer
singleline_comment|// (e.g. x86).
singleline_comment|//#define PCI_KERNEL_TRACE
macro_line|#ifdef PCI_KERNEL_TRACE
DECL|macro|PCI_TRACE
mdefine_line|#define PCI_TRACE(x) inl( fcChip-&gt;Registers.IOBaseL +x);
DECL|macro|PCI_TRACEO
mdefine_line|#define PCI_TRACEO(x,y) outl( x, (fcChip-&gt;Registers.IOBaseL +y));
macro_line|#else
DECL|macro|PCI_TRACE
mdefine_line|#define PCI_TRACE(x) 
DECL|macro|PCI_TRACEO
mdefine_line|#define PCI_TRACEO(x,y)
macro_line|#endif
singleline_comment|//#define DEBUG_CMND 1   // debug output for Linux Scsi CDBs
singleline_comment|//#define DUMMYCMND_DBG 1
singleline_comment|//#define DEBUG_CPQFCTS 1
singleline_comment|//#undef DEBUG_CPQFCTS 
macro_line|#ifdef DEBUG_CPQFCTS
DECL|macro|ENTER
mdefine_line|#define ENTER(x)&t;printk(&quot;cpqfcts : entering %s()&bslash;n&quot;, x);
DECL|macro|LEAVE
mdefine_line|#define LEAVE(x)&t;printk(&quot;cpqfcts : leaving %s()&bslash;n&quot;, x);
DECL|macro|DEBUG
mdefine_line|#define DEBUG(x)&t;x
macro_line|#else
DECL|macro|ENTER
mdefine_line|#define ENTER(x)
DECL|macro|LEAVE
mdefine_line|#define LEAVE(x)
DECL|macro|DEBUG
mdefine_line|#define DEBUG(x)
macro_line|#endif&t;&t;&t;&t;/* DEBUG_CPQFCTS */
singleline_comment|//#define DEBUG_CPQFCTS_PCI 1
singleline_comment|//#undef DEBUG_CPQFCTS_PCI
macro_line|#if DEBUG_CPQFCTS_PCI
DECL|macro|DEBUG_PCI
mdefine_line|#define DEBUG_PCI(x)&t;x
macro_line|#else
DECL|macro|DEBUG_PCI
mdefine_line|#define DEBUG_PCI(x)
macro_line|#endif&t;&t;&t;&t;/* DEBUG_CPQFCTS_PCI */
DECL|macro|STACHLITE66_TS12
mdefine_line|#define STACHLITE66_TS12  &quot;Compaq FibreChannel HBA Tachyon TS HPFC-5166A/1.2&quot;
DECL|macro|STACHLITE66_TS13
mdefine_line|#define STACHLITE66_TS13  &quot;Compaq FibreChannel HBA Tachyon TS HPFC-5166A/1.3&quot;
DECL|macro|STACHLITE_UNKNOWN
mdefine_line|#define STACHLITE_UNKNOWN &quot;Compaq FibreChannel HBA Tachyon Chip/Board Ver??&quot;
DECL|macro|SAGILENT_XL2_21
mdefine_line|#define SAGILENT_XL2_21   &quot;Agilent FC HBA, Tachyon XL2 HPFC-5200B/2.1&quot;
singleline_comment|// PDA is Peripheral Device Address, VSA is Volume Set Addressing
singleline_comment|// Linux SCSI parameters
DECL|macro|CPQFCTS_MAX_TARGET_ID
mdefine_line|#define CPQFCTS_MAX_TARGET_ID 64
DECL|macro|CPQFCTS_MAX_LUN
mdefine_line|#define CPQFCTS_MAX_LUN 8    
singleline_comment|// The RA-4x00 supports 32 (Linux SCSI supports 8)
DECL|macro|CPQFCTS_MAX_CHANNEL
mdefine_line|#define CPQFCTS_MAX_CHANNEL 0 
singleline_comment|// One FC port on cpqfcTS HBA
DECL|macro|CPQFCTS_CMD_PER_LUN
mdefine_line|#define CPQFCTS_CMD_PER_LUN 15 
singleline_comment|// power of 2 -1, must be &gt;0 
DECL|macro|CPQFCTS_REQ_QUEUE_LEN
mdefine_line|#define CPQFCTS_REQ_QUEUE_LEN (TACH_SEST_LEN/2) 
singleline_comment|// must be &lt; TACH_SEST_LEN
DECL|macro|LinuxVersionCode
mdefine_line|#define LinuxVersionCode(v, p, s) (((v)&lt;&lt;16)+((p)&lt;&lt;8)+(s))
macro_line|#ifndef DECLARE_MUTEX_LOCKED
DECL|macro|DECLARE_MUTEX_LOCKED
mdefine_line|#define DECLARE_MUTEX_LOCKED(sem) struct semaphore sem = MUTEX_LOCKED
macro_line|#endif
DECL|macro|DEV_NAME
mdefine_line|#define DEV_NAME &quot;cpqfcTS&quot;
DECL|macro|CPQ_DEVICE_ID
mdefine_line|#define CPQ_DEVICE_ID     0xA0FC
DECL|macro|AGILENT_XL2_ID
mdefine_line|#define AGILENT_XL2_ID    0x1029
r_typedef
r_struct
(brace
DECL|member|vendor_id
id|__u16
id|vendor_id
suffix:semicolon
DECL|member|device_id
id|__u16
id|device_id
suffix:semicolon
DECL|typedef|SupportedPCIcards
)brace
id|SupportedPCIcards
suffix:semicolon
singleline_comment|// nn:nn denotes bit field
singleline_comment|// TachyonHeader struct def.
singleline_comment|// the fields shared with ODB
singleline_comment|// need to have same value
macro_line|#ifndef BYTE
singleline_comment|//typedef UCHAR BYTE;
DECL|typedef|BYTE
r_typedef
id|__u8
id|BYTE
suffix:semicolon
macro_line|#endif
macro_line|#ifndef UCHAR
DECL|typedef|UCHAR
r_typedef
id|__u8
id|UCHAR
suffix:semicolon
macro_line|#endif
macro_line|#ifndef LONG
DECL|typedef|LONG
r_typedef
id|__s32
id|LONG
suffix:semicolon
macro_line|#endif
macro_line|#ifndef ULONG
DECL|typedef|ULONG
r_typedef
id|__u32
id|ULONG
suffix:semicolon
macro_line|#endif
macro_line|#ifndef PVOID
DECL|typedef|PVOID
r_typedef
r_void
op_star
id|PVOID
suffix:semicolon
macro_line|#endif
macro_line|#ifndef USHORT
DECL|typedef|USHORT
r_typedef
id|__u16
id|USHORT
suffix:semicolon
macro_line|#endif
macro_line|#ifndef BOOLEAN
DECL|typedef|BOOLEAN
r_typedef
id|__u8
id|BOOLEAN
suffix:semicolon
macro_line|#endif
singleline_comment|// macro for FC-PH reject codes
singleline_comment|// payload format for LS_RJT (FC payloads are big endian):
singleline_comment|//     byte  0         1         2         3  (MSB)
singleline_comment|// DWORD 0   01        00        00        00
singleline_comment|// DWORD 1   resvd     code      expl.     vendor
DECL|macro|LS_RJT_REASON
mdefine_line|#define LS_RJT_REASON( code, expl) (( code&lt;&lt;8) | (expl &lt;&lt;16))
DECL|macro|TachLiteSTATUS
mdefine_line|#define TachLiteSTATUS 0x12
singleline_comment|// Fibre Channel EXCHANGE status codes for Tachyon chips/ driver software
singleline_comment|// 32-bit ERROR word defines
DECL|macro|INVALID_ARGS
mdefine_line|#define INVALID_ARGS 0x1
DECL|macro|LNKDWN_OSLS
mdefine_line|#define LNKDWN_OSLS  0x2
DECL|macro|LNKDWN_LASER
mdefine_line|#define LNKDWN_LASER 0x4
DECL|macro|OUTQUE_FULL
mdefine_line|#define OUTQUE_FULL  0x8
DECL|macro|DRIVERQ_FULL
mdefine_line|#define DRIVERQ_FULL 0x10
DECL|macro|SEST_FULL
mdefine_line|#define SEST_FULL    0x20
DECL|macro|BAD_ALPA
mdefine_line|#define BAD_ALPA     0x40
DECL|macro|OVERFLOW
mdefine_line|#define OVERFLOW     0x80  
singleline_comment|// inbound CM
DECL|macro|COUNT_ERROR
mdefine_line|#define COUNT_ERROR     0x100  
singleline_comment|// inbound CM
DECL|macro|LINKFAIL_RX
mdefine_line|#define LINKFAIL_RX     0x200  
singleline_comment|// inbound CM
DECL|macro|ABORTSEQ_NOTIFY
mdefine_line|#define ABORTSEQ_NOTIFY 0x400  
singleline_comment|// outbound CM
DECL|macro|LINKFAIL_TX
mdefine_line|#define LINKFAIL_TX     0x800  
singleline_comment|// outbound CM
DECL|macro|HOSTPROG_ERR
mdefine_line|#define HOSTPROG_ERR     0x1000  
singleline_comment|// outbound CM
DECL|macro|FRAME_TO
mdefine_line|#define FRAME_TO         0x2000  
singleline_comment|// outbound CM
DECL|macro|INV_ENTRY
mdefine_line|#define INV_ENTRY        0x4000  
singleline_comment|// outbound CM
DECL|macro|SESTPROG_ERR
mdefine_line|#define SESTPROG_ERR     0x8000  
singleline_comment|// outbound CM
DECL|macro|OUTBOUND_TIMEOUT
mdefine_line|#define OUTBOUND_TIMEOUT 0x10000L 
singleline_comment|// timeout waiting for Tachyon outbound CM
DECL|macro|INITIATOR_ABORT
mdefine_line|#define INITIATOR_ABORT  0x20000L 
singleline_comment|// initiator exchange timeout or O/S ABORT
DECL|macro|MEMPOOL_FAIL
mdefine_line|#define MEMPOOL_FAIL     0x40000L 
singleline_comment|// O/S memory pool allocation failed
DECL|macro|FC2_TIMEOUT
mdefine_line|#define FC2_TIMEOUT      0x80000L 
singleline_comment|// driver timeout for lost frames
DECL|macro|TARGET_ABORT
mdefine_line|#define TARGET_ABORT     0x100000L 
singleline_comment|// ABTS received from FC port
DECL|macro|EXCHANGE_QUEUED
mdefine_line|#define EXCHANGE_QUEUED  0x200000L 
singleline_comment|// e.g. Link State was LDn on fcStart
DECL|macro|PORTID_CHANGED
mdefine_line|#define PORTID_CHANGED   0x400000L 
singleline_comment|// fc Port address changed
DECL|macro|DEVICE_REMOVED
mdefine_line|#define DEVICE_REMOVED   0x800000L 
singleline_comment|// fc Port address changed
singleline_comment|// Several error scenarios result in SEST Exchange frames 
singleline_comment|// unexpectedly arriving in the SFQ
DECL|macro|SFQ_FRAME
mdefine_line|#define SFQ_FRAME        0x1000000L 
singleline_comment|// SFQ frames from open Exchange
singleline_comment|// Maximum number of Host Bus Adapters (HBA) / controllers supported
singleline_comment|// only important for mem allocation dimensions - increase as necessary
DECL|macro|MAX_ADAPTERS
mdefine_line|#define MAX_ADAPTERS 8
DECL|macro|MAX_RX_PAYLOAD
mdefine_line|#define MAX_RX_PAYLOAD 1024  
singleline_comment|// hardware dependent max frame payload
singleline_comment|// Tach header struc defines
DECL|macro|SOFi3
mdefine_line|#define SOFi3 0x7
DECL|macro|SOFf
mdefine_line|#define SOFf  0x8
DECL|macro|SOFn3
mdefine_line|#define SOFn3 0xB
DECL|macro|EOFn
mdefine_line|#define EOFn  0x5
DECL|macro|EOFt
mdefine_line|#define EOFt  0x6
singleline_comment|// FCP R_CTL defines
DECL|macro|FCP_CMND
mdefine_line|#define FCP_CMND 0x6
DECL|macro|FCP_XFER_RDY
mdefine_line|#define FCP_XFER_RDY 0x5
DECL|macro|FCP_RSP
mdefine_line|#define FCP_RSP 0x7
DECL|macro|FCP_RESPONSE
mdefine_line|#define FCP_RESPONSE 0x777 
singleline_comment|// (arbitrary #)
DECL|macro|NEED_FCP_RSP
mdefine_line|#define NEED_FCP_RSP 0x77  
singleline_comment|// (arbitrary #)
DECL|macro|FCP_DATA
mdefine_line|#define FCP_DATA 0x1
DECL|macro|RESET_TACH
mdefine_line|#define RESET_TACH 0x100 
singleline_comment|// Reset Tachyon/TachLite
DECL|macro|SCSI_IWE
mdefine_line|#define SCSI_IWE 0x2000  
singleline_comment|// initiator write entry (for SEST)
DECL|macro|SCSI_IRE
mdefine_line|#define SCSI_IRE 0x3000  
singleline_comment|// initiator read entry (for SEST)
DECL|macro|SCSI_TRE
mdefine_line|#define SCSI_TRE 0x400  
singleline_comment|// target read entry (for SEST)
DECL|macro|SCSI_TWE
mdefine_line|#define SCSI_TWE 0x500  
singleline_comment|// target write entry (for SEST)
DECL|macro|TOGGLE_LASER
mdefine_line|#define TOGGLE_LASER 0x800
DECL|macro|LIP
mdefine_line|#define LIP 0x900
DECL|macro|CLEAR_FCPORTS
mdefine_line|#define CLEAR_FCPORTS 99 
singleline_comment|// (arbitrary #) free mem for Logged in ports
DECL|macro|FMINIT
mdefine_line|#define FMINIT 0x707     
singleline_comment|// (arbitrary) for Frame Manager Init command
singleline_comment|// BLS == Basic Link Service
singleline_comment|// ELS == Extended Link Service
DECL|macro|BLS_NOP
mdefine_line|#define BLS_NOP 4
DECL|macro|BLS_ABTS
mdefine_line|#define BLS_ABTS 0x10   
singleline_comment|// FC-PH Basic Link Service Abort Sequence
DECL|macro|BLS_ABTS_ACC
mdefine_line|#define BLS_ABTS_ACC 0x100  
singleline_comment|// FC-PH Basic Link Service Abort Sequence Accept
DECL|macro|BLS_ABTS_RJT
mdefine_line|#define BLS_ABTS_RJT 0x101  
singleline_comment|// FC-PH Basic Link Service Abort Sequence Reject
DECL|macro|ELS_PLOGI
mdefine_line|#define ELS_PLOGI 0x03  
singleline_comment|// FC-PH Port Login (arbitrary assign)
DECL|macro|ELS_SCR
mdefine_line|#define ELS_SCR   0x70  
singleline_comment|// (arb assign) State Change Registration (Fabric)
DECL|macro|FCS_NSR
mdefine_line|#define FCS_NSR   0x72  
singleline_comment|// (arb assign) Name Service Request (Fabric)
DECL|macro|ELS_FLOGI
mdefine_line|#define ELS_FLOGI 0x44  
singleline_comment|// (arb assign) Fabric Login
DECL|macro|ELS_FDISC
mdefine_line|#define ELS_FDISC 0x41  
singleline_comment|// (arb assign) Fabric Discovery (Login)
DECL|macro|ELS_PDISC
mdefine_line|#define ELS_PDISC 0x50  
singleline_comment|// FC-PH2 Port Discovery
DECL|macro|ELS_ABTX
mdefine_line|#define ELS_ABTX  0x06  
singleline_comment|// FC-PH Abort Exchange 
DECL|macro|ELS_LOGO
mdefine_line|#define ELS_LOGO 0x05   
singleline_comment|// FC-PH Port Logout
DECL|macro|ELS_PRLI
mdefine_line|#define ELS_PRLI 0x20   
singleline_comment|// FCP-SCSI Process Login
DECL|macro|ELS_PRLO
mdefine_line|#define ELS_PRLO 0x21   
singleline_comment|// FCP-SCSI Process Logout
DECL|macro|ELS_LOGO_ACC
mdefine_line|#define ELS_LOGO_ACC 0x07   
singleline_comment|// {FC-PH} Port Logout Accept
DECL|macro|ELS_PLOGI_ACC
mdefine_line|#define ELS_PLOGI_ACC 0x08  
singleline_comment|// {FC-PH} Port Login Accept
DECL|macro|ELS_ACC
mdefine_line|#define ELS_ACC 0x18        
singleline_comment|// {FC-PH} (generic) ACCept
DECL|macro|ELS_PRLI_ACC
mdefine_line|#define ELS_PRLI_ACC 0x22  
singleline_comment|// {FCP-SCSI} Process Login Accept
DECL|macro|ELS_RJT
mdefine_line|#define ELS_RJT 0x1000000
DECL|macro|SCSI_REPORT_LUNS
mdefine_line|#define SCSI_REPORT_LUNS 0x0A0
DECL|macro|REPORT_LUNS
mdefine_line|#define REPORT_LUNS 0xA0 
singleline_comment|// SCSI-3 command op-code
DECL|macro|ELS_LILP_FRAME
mdefine_line|#define ELS_LILP_FRAME 0x00000711 
singleline_comment|// 1st payload word of LILP frame
DECL|macro|SFQ_UNASSISTED_FCP
mdefine_line|#define SFQ_UNASSISTED_FCP  1  
singleline_comment|// ICM, DWord3, &quot;Type&quot; unassisted FCP
DECL|macro|SFQ_UNKNOWN
mdefine_line|#define SFQ_UNKNOWN         0x31 
singleline_comment|// (arbitrary) ICM, DWord3, &quot;Type&quot; unknown
singleline_comment|// these &quot;LINK&quot; bits refer to loop or non-loop
DECL|macro|LINKACTIVE
mdefine_line|#define LINKACTIVE 0x2    
singleline_comment|// fcLinkQ type - LINK UP Tachyon FM &squot;Lup&squot; bit set
DECL|macro|LINKDOWN
mdefine_line|#define LINKDOWN 0xf2     
singleline_comment|// fcLinkQ type - LINK DOWN Tachyon FM &squot;Ldn&squot; bit set
singleline_comment|//#define VOLUME_SET_ADDRESSING 1 // &quot;channel&quot; or &quot;bus&quot; 1
r_typedef
r_struct
singleline_comment|// 32 bytes hdr ONLY (e.g. FCP_DATA buffer for SEST)
(brace
DECL|member|reserved
id|ULONG
id|reserved
suffix:semicolon
singleline_comment|// dword 0 (don&squot;t use)
DECL|member|sof_eof
id|ULONG
id|sof_eof
suffix:semicolon
DECL|member|d_id
id|ULONG
id|d_id
suffix:semicolon
singleline_comment|// dword 2 - 31:24 R_CTL, 23:0 D_ID
DECL|member|s_id
id|ULONG
id|s_id
suffix:semicolon
singleline_comment|// dword 3 - 31:24 CS_CTL, 23:0 S_ID
DECL|member|f_ctl
id|ULONG
id|f_ctl
suffix:semicolon
singleline_comment|// dword 4 - 31:24 Type,  23:0 F_CTL
DECL|member|seq_cnt
id|ULONG
id|seq_cnt
suffix:semicolon
singleline_comment|// dword 5 - 31:24 SEQ_ID, 23:16 DF_CTL, 15:0 SEQ_CNT
DECL|member|ox_rx_id
id|ULONG
id|ox_rx_id
suffix:semicolon
singleline_comment|// dword 6 - 31:16 OX_ID,  15:0 RX_ID
DECL|member|ro
id|ULONG
id|ro
suffix:semicolon
singleline_comment|// dword 7 - relative offset
DECL|typedef|TachFCHDR
)brace
id|TachFCHDR
suffix:semicolon
singleline_comment|// NOTE!! the following struct MUST be 64 bytes.
r_typedef
r_struct
singleline_comment|// 32 bytes hdr + 32 bytes payload
(brace
DECL|member|reserved
id|ULONG
id|reserved
suffix:semicolon
singleline_comment|// dword 0 (don&squot;t use - must clear to 0)
DECL|member|sof_eof
id|ULONG
id|sof_eof
suffix:semicolon
singleline_comment|// dword 1 - 31:24 SOF:EOF, UAM,CLS, LCr, TFV, TimeStamp
DECL|member|d_id
id|ULONG
id|d_id
suffix:semicolon
singleline_comment|// dword 2 - 31:24 R_CTL, 23:0 D_ID
DECL|member|s_id
id|ULONG
id|s_id
suffix:semicolon
singleline_comment|// dword 3 - 31:24 CS_CTL, 23:0 S_ID
DECL|member|f_ctl
id|ULONG
id|f_ctl
suffix:semicolon
singleline_comment|// dword 4 - 31:24 Type,  23:0 F_CTL
DECL|member|seq_cnt
id|ULONG
id|seq_cnt
suffix:semicolon
singleline_comment|// dword 5 - 31:24 SEQ_ID, 23:16 DF_CTL, 15:0 SEQ_CNT
DECL|member|ox_rx_id
id|ULONG
id|ox_rx_id
suffix:semicolon
singleline_comment|// dword 6 - 31:16 OX_ID,  15:0 RX_ID
DECL|member|ro
id|ULONG
id|ro
suffix:semicolon
singleline_comment|// dword 7 - relative offset
singleline_comment|//---------
DECL|member|pl
id|__u32
id|pl
(braket
l_int|8
)braket
suffix:semicolon
singleline_comment|// dwords 8-15 frame data payload
DECL|typedef|TachFCHDR_CMND
)brace
id|TachFCHDR_CMND
suffix:semicolon
r_typedef
r_struct
singleline_comment|// 32 bytes hdr + 120 bytes payload
(brace
DECL|member|reserved
id|ULONG
id|reserved
suffix:semicolon
singleline_comment|// dword 0 (don&squot;t use - must clear to 0)
DECL|member|sof_eof
id|ULONG
id|sof_eof
suffix:semicolon
singleline_comment|// dword 1 - 31:24 SOF:EOF, UAM,CLS, LCr, TFV, TimeStamp
DECL|member|d_id
id|ULONG
id|d_id
suffix:semicolon
singleline_comment|// dword 2 - 31:24 R_CTL, 23:0 D_ID
DECL|member|s_id
id|ULONG
id|s_id
suffix:semicolon
singleline_comment|// dword 3 - 31:24 CS_CTL, 23:0 S_ID
DECL|member|f_ctl
id|ULONG
id|f_ctl
suffix:semicolon
singleline_comment|// dword 4 - 31:24 Type,  23:0 F_CTL
DECL|member|seq_cnt
id|ULONG
id|seq_cnt
suffix:semicolon
singleline_comment|// dword 5 - 31:24 SEQ_ID, 23:16 DF_CTL, 15:0 SEQ_CNT
DECL|member|ox_rx_id
id|ULONG
id|ox_rx_id
suffix:semicolon
singleline_comment|// dword 6 - 31:16 OX_ID,  15:0 RX_ID
DECL|member|ro
id|ULONG
id|ro
suffix:semicolon
singleline_comment|// dword 7 - relative offset
singleline_comment|//---------
DECL|member|pl
id|__u32
id|pl
(braket
l_int|30
)braket
suffix:semicolon
singleline_comment|// largest necessary payload (for LOGIN cmnds)
DECL|typedef|TachFCHDR_GCMND
)brace
id|TachFCHDR_GCMND
suffix:semicolon
r_typedef
r_struct
singleline_comment|// 32 bytes hdr + 64 bytes payload
(brace
DECL|member|reserved
id|ULONG
id|reserved
suffix:semicolon
singleline_comment|// dword 0 (don&squot;t use)
DECL|member|sof_eof
id|ULONG
id|sof_eof
suffix:semicolon
DECL|member|d_id
id|ULONG
id|d_id
suffix:semicolon
singleline_comment|// dword 2 - 31:24 R_CTL, 23:0 D_ID
DECL|member|s_id
id|ULONG
id|s_id
suffix:semicolon
singleline_comment|// dword 3 - 31:24 CS_CTL, 23:0 S_ID
DECL|member|f_ctl
id|ULONG
id|f_ctl
suffix:semicolon
singleline_comment|// dword 4 - 31:24 Type,  23:0 F_CTL
DECL|member|seq_cnt
id|ULONG
id|seq_cnt
suffix:semicolon
singleline_comment|// dword 5 - 31:24 SEQ_ID, 23:16 DF_CTL, 15:0 SEQ_CNT
DECL|member|ox_rx_id
id|ULONG
id|ox_rx_id
suffix:semicolon
singleline_comment|// dword 6 - 31:16 OX_ID,  15:0 RX_ID
DECL|member|ro
id|ULONG
id|ro
suffix:semicolon
singleline_comment|// dword 7 - relative offset
singleline_comment|//---------
DECL|member|pl
id|__u32
id|pl
(braket
l_int|18
)braket
suffix:semicolon
singleline_comment|// payload for FCP-RSP (response buffer) RA-4x00 is 72bytes
DECL|typedef|TachFCHDR_RSP
)brace
id|TachFCHDR_RSP
suffix:semicolon
singleline_comment|// Inbound Message Queue structures...
r_typedef
r_struct
singleline_comment|// each entry 8 words (32 bytes)
(brace
DECL|member|type
id|ULONG
id|type
suffix:semicolon
singleline_comment|// IMQ completion message types
DECL|member|word
id|ULONG
id|word
(braket
l_int|7
)braket
suffix:semicolon
singleline_comment|// remainder of structure
singleline_comment|// interpreted by IMQ type
DECL|typedef|TachyonIMQE
)brace
id|TachyonIMQE
suffix:semicolon
singleline_comment|// Queues for TachLite not in original Tachyon
singleline_comment|// ERQ       - Exchange Request Queue (for outbound commands)
singleline_comment|// SFQ       - Single Frame Queue (for incoming frames)
singleline_comment|// Define Tachyon Outbound Command Que
singleline_comment|// (Since many Tachyon registers are Read
singleline_comment|// only, maintain copies for debugging)
singleline_comment|// most Tach ques need power-of-2 sizes,
singleline_comment|// where registers are loaded with po2 -1
DECL|macro|TACH_SEST_LEN
mdefine_line|#define TACH_SEST_LEN 512   
singleline_comment|// TachLite SEST
DECL|macro|ELS_EXCHANGES
mdefine_line|#define ELS_EXCHANGES 64    
singleline_comment|// e.g. PLOGI, RSCN, ...
singleline_comment|// define the total number of outstanding (simultaneous) exchanges
DECL|macro|TACH_MAX_XID
mdefine_line|#define TACH_MAX_XID (TACH_SEST_LEN + ELS_EXCHANGES)  
singleline_comment|// ELS exchanges
DECL|macro|ERQ_LEN
mdefine_line|#define ERQ_LEN 128         
singleline_comment|// power of 2, max 4096
singleline_comment|// Inbound Message Queue structures...
DECL|macro|IMQ_LEN
mdefine_line|#define IMQ_LEN 512              
singleline_comment|// minimum 4 entries [(power of 2) - 1]
r_typedef
r_struct
singleline_comment|// 8 words - 32 bytes
(brace
DECL|member|QEntry
id|TachyonIMQE
id|QEntry
(braket
id|IMQ_LEN
)braket
suffix:semicolon
DECL|member|producerIndex
id|ULONG
id|producerIndex
suffix:semicolon
singleline_comment|// IMQ Producer Index register
singleline_comment|// @32 byte align
DECL|member|consumerIndex
id|ULONG
id|consumerIndex
suffix:semicolon
singleline_comment|// Consumer Index register (in Tachyon)
DECL|member|length
id|ULONG
id|length
suffix:semicolon
singleline_comment|// Length register
DECL|member|base
id|ULONG
id|base
suffix:semicolon
DECL|typedef|TachyonIMQ
)brace
id|TachyonIMQ
suffix:semicolon
singleline_comment|// @ 32 * IMQ_LEN align
r_typedef
r_struct
singleline_comment|// inbound completion message
(brace
DECL|member|Type
id|ULONG
id|Type
suffix:semicolon
DECL|member|Index
id|ULONG
id|Index
suffix:semicolon
DECL|member|TransferLength
id|ULONG
id|TransferLength
suffix:semicolon
DECL|typedef|TachyonInbCM
)brace
id|TachyonInbCM
suffix:semicolon
singleline_comment|// arbitrary numeric tags for TL structures
DECL|macro|TL_FCHS
mdefine_line|#define TL_FCHS 1  
singleline_comment|// TachLite Fibre Channel Header Structure
DECL|macro|TL_IWE
mdefine_line|#define TL_IWE 2  
singleline_comment|// initiator write entry (for SEST)
DECL|macro|TL_TWE
mdefine_line|#define TL_TWE 3  
singleline_comment|// target write entry (for SEST)
DECL|macro|TL_IRE
mdefine_line|#define TL_IRE 4  
singleline_comment|// initiator read entry (for SEST)
DECL|macro|TL_TRE
mdefine_line|#define TL_TRE 5  
singleline_comment|// target read entry (for SEST)
DECL|macro|TL_IRB
mdefine_line|#define TL_IRB 6  
singleline_comment|// I/O request block
singleline_comment|// for INCOMING frames
DECL|macro|SFQ_LEN
mdefine_line|#define SFQ_LEN 32              
singleline_comment|// minimum 32 entries, max 4096
r_typedef
r_struct
singleline_comment|// Single Frame Que
(brace
DECL|member|QEntry
id|TachFCHDR_CMND
id|QEntry
(braket
id|SFQ_LEN
)braket
suffix:semicolon
singleline_comment|// must be 64 bytes!!
DECL|member|producerIndex
id|ULONG
id|producerIndex
suffix:semicolon
singleline_comment|// IMQ Producer Index register
singleline_comment|// @32 byte align
DECL|member|consumerIndex
id|ULONG
id|consumerIndex
suffix:semicolon
singleline_comment|// Consumer Index register (in Tachyon)
DECL|member|length
id|ULONG
id|length
suffix:semicolon
singleline_comment|// Length register
DECL|member|base
id|ULONG
id|base
suffix:semicolon
DECL|typedef|TachLiteSFQ
)brace
id|TachLiteSFQ
suffix:semicolon
r_typedef
r_struct
singleline_comment|// I/O Request Block flags
(brace
DECL|member|BRD
id|UCHAR
id|BRD
suffix:colon
l_int|1
suffix:semicolon
DECL|member|UCHAR
id|UCHAR
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// reserved
DECL|member|SFA
id|UCHAR
id|SFA
suffix:colon
l_int|1
suffix:semicolon
DECL|member|DNC
id|UCHAR
id|DNC
suffix:colon
l_int|1
suffix:semicolon
DECL|member|DIN
id|UCHAR
id|DIN
suffix:colon
l_int|1
suffix:semicolon
DECL|member|DCM
id|UCHAR
id|DCM
suffix:colon
l_int|1
suffix:semicolon
DECL|member|CTS
id|UCHAR
id|CTS
suffix:colon
l_int|1
suffix:semicolon
DECL|member|SBV
id|UCHAR
id|SBV
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// IRB entry valid - IRB&squot;B&squot; only
DECL|typedef|IRBflags
)brace
id|IRBflags
suffix:semicolon
r_typedef
r_struct
singleline_comment|// I/O Request Block
(brace
singleline_comment|// Request &squot;A&squot;
DECL|member|Req_A_SFS_Len
id|ULONG
id|Req_A_SFS_Len
suffix:semicolon
singleline_comment|// total frame len (hdr + payload), min 32
DECL|member|Req_A_SFS_Addr
id|ULONG
id|Req_A_SFS_Addr
suffix:semicolon
singleline_comment|// 32-bit pointer to FCHS struct (to be sent)
DECL|member|Req_A_SFS_D_ID
id|ULONG
id|Req_A_SFS_D_ID
suffix:semicolon
singleline_comment|// 24-bit FC destination (i.e. 8 bit al_pa)
DECL|member|Req_A_Trans_ID
id|ULONG
id|Req_A_Trans_ID
suffix:semicolon
singleline_comment|// X_ID (OX_ID or RX_ID) and/or Index in SEST
singleline_comment|// Request &squot;B&squot;
DECL|member|Req_B_SFS_Len
id|ULONG
id|Req_B_SFS_Len
suffix:semicolon
singleline_comment|// total frame len (hdr + payload), min 32
DECL|member|Req_B_SFS_Addr
id|ULONG
id|Req_B_SFS_Addr
suffix:semicolon
singleline_comment|// 32-bit pointer to FCHS struct (to be sent)
DECL|member|Req_B_SFS_D_ID
id|ULONG
id|Req_B_SFS_D_ID
suffix:semicolon
singleline_comment|// 24-bit FC destination (i.e. 8 bit al_pa)
DECL|member|Req_B_Trans_ID
id|ULONG
id|Req_B_Trans_ID
suffix:semicolon
singleline_comment|// X_ID (OX_ID or RX_ID) and/or Index in SEST
DECL|typedef|TachLiteIRB
)brace
id|TachLiteIRB
suffix:semicolon
r_typedef
r_struct
singleline_comment|// TachLite placeholder for IRBs
(brace
singleline_comment|// aligned @sizeof(ERQ) for TachLite
singleline_comment|// MAX commands is sum of SEST len and ERQ
singleline_comment|// we know that each SEST entry requires an
singleline_comment|// IRB (ERQ) entry; in addition, we provide
singleline_comment|// ERQ_LEN
DECL|member|QEntry
id|TachLiteIRB
id|QEntry
(braket
id|ERQ_LEN
)braket
suffix:semicolon
singleline_comment|// Base register; entries 32 bytes ea.
DECL|member|consumerIndex
id|ULONG
id|consumerIndex
suffix:semicolon
singleline_comment|// Consumer Index register
DECL|member|producerIndex
id|ULONG
id|producerIndex
suffix:semicolon
singleline_comment|// ERQ Producer Index register
DECL|member|length
id|ULONG
id|length
suffix:semicolon
singleline_comment|// Length register
DECL|member|base
id|ULONG
id|base
suffix:semicolon
singleline_comment|// copy of base ptr for debug
singleline_comment|// struct is sized for largest expected cmnd (LOGIN)
DECL|typedef|TachLiteERQ
)brace
id|TachLiteERQ
suffix:semicolon
DECL|macro|TL_MAX_SGPAGES
mdefine_line|#define TL_MAX_SGPAGES 4  
singleline_comment|// arbitrary limit to # of TL Ext. S/G pages
singleline_comment|// stores array of allocated page blocks used
singleline_comment|// in extended S/G lists.  Affects amount of static
singleline_comment|// memory consumed by driver.
DECL|macro|TL_EXT_SG_PAGE_COUNT
mdefine_line|#define TL_EXT_SG_PAGE_COUNT 256  
singleline_comment|// Number of Extended Scatter/Gather a/l PAIRS
singleline_comment|// Tachyon register (IOBaseU 0x68)
singleline_comment|// power-of-2 value ONLY!  4 min, 256 max
singleline_comment|// byte len is #Pairs * 2 ULONG/Pair * 4 bytes/ULONG
DECL|macro|TL_EXT_SG_PAGE_BYTELEN
mdefine_line|#define TL_EXT_SG_PAGE_BYTELEN (TL_EXT_SG_PAGE_COUNT *2 *4)
singleline_comment|// SEST entry types: IWE, IRE, TWE, TRE
r_typedef
r_struct
(brace
DECL|member|Hdr_Len
id|ULONG
id|Hdr_Len
suffix:semicolon
DECL|member|Hdr_Addr
id|ULONG
id|Hdr_Addr
suffix:semicolon
DECL|member|RSP_Len
id|ULONG
id|RSP_Len
suffix:semicolon
DECL|member|RSP_Addr
id|ULONG
id|RSP_Addr
suffix:semicolon
DECL|member|Buff_Off
id|ULONG
id|Buff_Off
suffix:semicolon
DECL|member|Link
id|ULONG
id|Link
suffix:semicolon
DECL|member|RX_ID
id|ULONG
id|RX_ID
suffix:semicolon
DECL|member|Data_Len
id|ULONG
id|Data_Len
suffix:semicolon
DECL|member|Exp_RO
id|ULONG
id|Exp_RO
suffix:semicolon
DECL|member|Exp_Byte_Cnt
id|ULONG
id|Exp_Byte_Cnt
suffix:semicolon
singleline_comment|// --- extended/local Gather Len/Address pairs
DECL|member|GLen1
id|ULONG
id|GLen1
suffix:semicolon
DECL|member|GAddr1
id|ULONG
id|GAddr1
suffix:semicolon
DECL|member|GLen2
id|ULONG
id|GLen2
suffix:semicolon
DECL|member|GAddr2
id|ULONG
id|GAddr2
suffix:semicolon
DECL|member|GLen3
id|ULONG
id|GLen3
suffix:semicolon
DECL|member|GAddr3
id|ULONG
id|GAddr3
suffix:semicolon
DECL|typedef|TachLiteIWE
)brace
id|TachLiteIWE
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|Seq_Accum
id|ULONG
id|Seq_Accum
suffix:semicolon
DECL|member|reserved
id|ULONG
id|reserved
suffix:semicolon
singleline_comment|// must clear to 0
DECL|member|RSP_Len
id|ULONG
id|RSP_Len
suffix:semicolon
DECL|member|RSP_Addr
id|ULONG
id|RSP_Addr
suffix:semicolon
DECL|member|Buff_Off
id|ULONG
id|Buff_Off
suffix:semicolon
DECL|member|Buff_Index
id|ULONG
id|Buff_Index
suffix:semicolon
singleline_comment|// ULONG 5
DECL|member|Exp_RO
id|ULONG
id|Exp_RO
suffix:semicolon
DECL|member|Byte_Count
id|ULONG
id|Byte_Count
suffix:semicolon
DECL|member|reserved_
id|ULONG
id|reserved_
suffix:semicolon
singleline_comment|// ULONG 8
DECL|member|Exp_Byte_Cnt
id|ULONG
id|Exp_Byte_Cnt
suffix:semicolon
singleline_comment|// --- extended/local Scatter Len/Address pairs
DECL|member|SLen1
id|ULONG
id|SLen1
suffix:semicolon
DECL|member|SAddr1
id|ULONG
id|SAddr1
suffix:semicolon
DECL|member|SLen2
id|ULONG
id|SLen2
suffix:semicolon
DECL|member|SAddr2
id|ULONG
id|SAddr2
suffix:semicolon
DECL|member|SLen3
id|ULONG
id|SLen3
suffix:semicolon
DECL|member|SAddr3
id|ULONG
id|SAddr3
suffix:semicolon
DECL|typedef|TachLiteIRE
)brace
id|TachLiteIRE
suffix:semicolon
r_typedef
r_struct
singleline_comment|// Target Write Entry
(brace
DECL|member|Seq_Accum
id|ULONG
id|Seq_Accum
suffix:semicolon
singleline_comment|// dword 0
DECL|member|reserved
id|ULONG
id|reserved
suffix:semicolon
singleline_comment|// dword 1  must clear to 0
DECL|member|Remote_Node_ID
id|ULONG
id|Remote_Node_ID
suffix:semicolon
DECL|member|reserved1
id|ULONG
id|reserved1
suffix:semicolon
singleline_comment|// dword 3  must clear to 0
DECL|member|Buff_Off
id|ULONG
id|Buff_Off
suffix:semicolon
DECL|member|Buff_Index
id|ULONG
id|Buff_Index
suffix:semicolon
singleline_comment|// ULONG 5
DECL|member|Exp_RO
id|ULONG
id|Exp_RO
suffix:semicolon
DECL|member|Byte_Count
id|ULONG
id|Byte_Count
suffix:semicolon
DECL|member|reserved_
id|ULONG
id|reserved_
suffix:semicolon
singleline_comment|// ULONG 8
DECL|member|Exp_Byte_Cnt
id|ULONG
id|Exp_Byte_Cnt
suffix:semicolon
singleline_comment|// --- extended/local Scatter Len/Address pairs
DECL|member|SLen1
id|ULONG
id|SLen1
suffix:semicolon
DECL|member|SAddr1
id|ULONG
id|SAddr1
suffix:semicolon
DECL|member|SLen2
id|ULONG
id|SLen2
suffix:semicolon
DECL|member|SAddr2
id|ULONG
id|SAddr2
suffix:semicolon
DECL|member|SLen3
id|ULONG
id|SLen3
suffix:semicolon
DECL|member|SAddr3
id|ULONG
id|SAddr3
suffix:semicolon
DECL|typedef|TachLiteTWE
)brace
id|TachLiteTWE
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|Hdr_Len
id|ULONG
id|Hdr_Len
suffix:semicolon
DECL|member|Hdr_Addr
id|ULONG
id|Hdr_Addr
suffix:semicolon
DECL|member|RSP_Len
id|ULONG
id|RSP_Len
suffix:semicolon
singleline_comment|// DWord 2
DECL|member|RSP_Addr
id|ULONG
id|RSP_Addr
suffix:semicolon
DECL|member|Buff_Off
id|ULONG
id|Buff_Off
suffix:semicolon
DECL|member|Buff_Index
id|ULONG
id|Buff_Index
suffix:semicolon
singleline_comment|// DWord 5
DECL|member|reserved
id|ULONG
id|reserved
suffix:semicolon
DECL|member|Data_Len
id|ULONG
id|Data_Len
suffix:semicolon
DECL|member|reserved_
id|ULONG
id|reserved_
suffix:semicolon
DECL|member|reserved__
id|ULONG
id|reserved__
suffix:semicolon
singleline_comment|// --- extended/local Gather Len/Address pairs
DECL|member|GLen1
id|ULONG
id|GLen1
suffix:semicolon
singleline_comment|// DWord A
DECL|member|GAddr1
id|ULONG
id|GAddr1
suffix:semicolon
DECL|member|GLen2
id|ULONG
id|GLen2
suffix:semicolon
DECL|member|GAddr2
id|ULONG
id|GAddr2
suffix:semicolon
DECL|member|GLen3
id|ULONG
id|GLen3
suffix:semicolon
DECL|member|GAddr3
id|ULONG
id|GAddr3
suffix:semicolon
DECL|typedef|TachLiteTRE
)brace
id|TachLiteTRE
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|PoolPage
r_void
op_star
id|PoolPage
(braket
id|TL_MAX_SGPAGES
)braket
suffix:semicolon
DECL|typedef|SGPAGES
DECL|typedef|PSGPAGES
)brace
id|SGPAGES
comma
op_star
id|PSGPAGES
suffix:semicolon
singleline_comment|// linked list of S/G pairs, by Exchange
r_typedef
r_struct
singleline_comment|// SCSI Exchange State Table
(brace
r_union
singleline_comment|// Entry can be IWE, IRE, TWE, TRE
(brace
singleline_comment|// 64 bytes per entry
DECL|member|IWE
id|TachLiteIWE
id|IWE
suffix:semicolon
DECL|member|IRE
id|TachLiteIRE
id|IRE
suffix:semicolon
DECL|member|TWE
id|TachLiteTWE
id|TWE
suffix:semicolon
DECL|member|TRE
id|TachLiteTRE
id|TRE
suffix:semicolon
DECL|member|u
)brace
id|u
(braket
id|TACH_SEST_LEN
)braket
suffix:semicolon
DECL|member|DataHDR
id|TachFCHDR
id|DataHDR
(braket
id|TACH_SEST_LEN
)braket
suffix:semicolon
singleline_comment|// for SEST FCP_DATA frame hdr (no pl)
DECL|member|RspHDR
id|TachFCHDR_RSP
id|RspHDR
(braket
id|TACH_SEST_LEN
)braket
suffix:semicolon
singleline_comment|// space for SEST FCP_RSP frame
DECL|member|sgPages
id|SGPAGES
id|sgPages
(braket
id|TACH_SEST_LEN
)braket
suffix:semicolon
singleline_comment|// array of Pool-allocations
DECL|member|length
id|ULONG
id|length
suffix:semicolon
singleline_comment|// Length register
DECL|member|base
id|ULONG
id|base
suffix:semicolon
singleline_comment|// copy of base ptr for debug
DECL|typedef|TachSEST
)brace
id|TachSEST
suffix:semicolon
r_typedef
r_struct
singleline_comment|// each register has it&squot;s own address
singleline_comment|// and value (used for write-only regs)
(brace
DECL|member|address
r_void
op_star
id|address
suffix:semicolon
DECL|member|value
r_volatile
id|ULONG
id|value
suffix:semicolon
DECL|typedef|FCREGISTER
)brace
id|FCREGISTER
suffix:semicolon
r_typedef
r_struct
singleline_comment|// Host copy - TachLite Registers
(brace
DECL|member|IOBaseL
DECL|member|IOBaseU
id|ULONG
id|IOBaseL
comma
id|IOBaseU
suffix:semicolon
singleline_comment|// I/O port lower and upper TL register addresses
DECL|member|MemBase
id|ULONG
id|MemBase
suffix:semicolon
singleline_comment|// memory mapped register addresses
DECL|member|ReMapMemBase
r_void
op_star
id|ReMapMemBase
suffix:semicolon
singleline_comment|// O/S VM reference for MemBase
DECL|member|wwn_hi
id|ULONG
id|wwn_hi
suffix:semicolon
singleline_comment|// WWN is set once at startup
DECL|member|wwn_lo
id|ULONG
id|wwn_lo
suffix:semicolon
DECL|member|my_al_pa
id|ULONG
id|my_al_pa
suffix:semicolon
singleline_comment|// al_pa received after LIP()
DECL|member|ROMCTR
id|ULONG
id|ROMCTR
suffix:semicolon
singleline_comment|// flags for on-board RAM/ROM
DECL|member|RAMBase
id|ULONG
id|RAMBase
suffix:semicolon
singleline_comment|// on-board RAM (i.e. some Tachlites)
DECL|member|SROMBase
id|ULONG
id|SROMBase
suffix:semicolon
singleline_comment|// on-board EEPROM (some Tachlites)
DECL|member|PCIMCTR
id|ULONG
id|PCIMCTR
suffix:semicolon
singleline_comment|// PCI Master Control Reg (has bus width)
DECL|member|INTEN
id|FCREGISTER
id|INTEN
suffix:semicolon
singleline_comment|// copy of interrupt enable mask
DECL|member|INTPEND
id|FCREGISTER
id|INTPEND
suffix:semicolon
singleline_comment|// interrupt pending
DECL|member|INTSTAT
id|FCREGISTER
id|INTSTAT
suffix:semicolon
singleline_comment|// interrupt status
DECL|member|SFQconsumerIndex
id|FCREGISTER
id|SFQconsumerIndex
suffix:semicolon
DECL|member|ERQproducerIndex
id|FCREGISTER
id|ERQproducerIndex
suffix:semicolon
DECL|member|TYconfig
id|FCREGISTER
id|TYconfig
suffix:semicolon
singleline_comment|// TachYon (chip level)
DECL|member|TYcontrol
id|FCREGISTER
id|TYcontrol
suffix:semicolon
DECL|member|TYstatus
id|FCREGISTER
id|TYstatus
suffix:semicolon
DECL|member|FMconfig
id|FCREGISTER
id|FMconfig
suffix:semicolon
singleline_comment|// Frame Manager (FC loop level)
DECL|member|FMcontrol
id|FCREGISTER
id|FMcontrol
suffix:semicolon
DECL|member|FMstatus
id|FCREGISTER
id|FMstatus
suffix:semicolon
DECL|member|FMLinkStatus1
id|FCREGISTER
id|FMLinkStatus1
suffix:semicolon
DECL|member|FMLinkStatus2
id|FCREGISTER
id|FMLinkStatus2
suffix:semicolon
DECL|member|FMBB_CreditZero
id|FCREGISTER
id|FMBB_CreditZero
suffix:semicolon
DECL|member|status
id|FCREGISTER
id|status
suffix:semicolon
DECL|member|ed_tov
id|FCREGISTER
id|ed_tov
suffix:semicolon
singleline_comment|// error detect time-out value
DECL|member|rcv_al_pa
id|FCREGISTER
id|rcv_al_pa
suffix:semicolon
singleline_comment|// received arb. loop physical address
DECL|member|primitive
id|FCREGISTER
id|primitive
suffix:semicolon
singleline_comment|// e.g. LIP(), OPN(), ...
DECL|typedef|TL_REGISTERS
)brace
id|TL_REGISTERS
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ok
id|ULONG
id|ok
suffix:semicolon
DECL|member|invalidArgs
id|ULONG
id|invalidArgs
suffix:semicolon
DECL|member|linkDown
id|ULONG
id|linkDown
suffix:semicolon
DECL|member|linkUp
id|ULONG
id|linkUp
suffix:semicolon
DECL|member|outQueFull
id|ULONG
id|outQueFull
suffix:semicolon
DECL|member|SESTFull
id|ULONG
id|SESTFull
suffix:semicolon
DECL|member|hpe
id|ULONG
id|hpe
suffix:semicolon
singleline_comment|// host programming err (from Tach)
DECL|member|FC4aborted
id|ULONG
id|FC4aborted
suffix:semicolon
singleline_comment|// aborts from Application or upper driver layer
DECL|member|FC2aborted
id|ULONG
id|FC2aborted
suffix:semicolon
singleline_comment|// aborts from our driver&squot;s timeouts
DECL|member|timeouts
id|ULONG
id|timeouts
suffix:semicolon
singleline_comment|// our driver timeout (on individual exchanges)
DECL|member|logouts
id|ULONG
id|logouts
suffix:semicolon
singleline_comment|// explicit - sent LOGO; implicit - device removed
DECL|member|retries
id|ULONG
id|retries
suffix:semicolon
DECL|member|linkFailTX
id|ULONG
id|linkFailTX
suffix:semicolon
DECL|member|linkFailRX
id|ULONG
id|linkFailRX
suffix:semicolon
DECL|member|CntErrors
id|ULONG
id|CntErrors
suffix:semicolon
singleline_comment|// byte count expected != count received (typ. SEST)
DECL|member|e_stores
id|ULONG
id|e_stores
suffix:semicolon
singleline_comment|// elastic store errs
DECL|member|resets
id|ULONG
id|resets
suffix:semicolon
singleline_comment|// hard or soft controller resets
DECL|member|FMinits
id|ULONG
id|FMinits
suffix:semicolon
singleline_comment|// TACH Frame Manager Init (e.g. LIPs)
DECL|member|lnkQueFull
id|ULONG
id|lnkQueFull
suffix:semicolon
singleline_comment|// too many LOGIN, loop commands
DECL|member|ScsiQueFull
id|ULONG
id|ScsiQueFull
suffix:semicolon
singleline_comment|// too many FCP-SCSI inbound frames
DECL|member|LossofSignal
id|ULONG
id|LossofSignal
suffix:semicolon
singleline_comment|// FM link status 1 regs
DECL|member|BadRXChar
id|ULONG
id|BadRXChar
suffix:semicolon
singleline_comment|// FM link status 1 regs
DECL|member|LossofSync
id|ULONG
id|LossofSync
suffix:semicolon
singleline_comment|// FM link status 1 regs
DECL|member|Rx_EOFa
id|ULONG
id|Rx_EOFa
suffix:semicolon
singleline_comment|// FM link status 2 regs (received EOFa)
DECL|member|Dis_Frm
id|ULONG
id|Dis_Frm
suffix:semicolon
singleline_comment|// FM link status 2 regs (discarded frames)
DECL|member|Bad_CRC
id|ULONG
id|Bad_CRC
suffix:semicolon
singleline_comment|// FM link status 2 regs
DECL|member|BB0_Timer
id|ULONG
id|BB0_Timer
suffix:semicolon
singleline_comment|//  FM BB_Credit Zero Timer Reg
DECL|member|loopBreaks
id|ULONG
id|loopBreaks
suffix:semicolon
singleline_comment|// infinite loop exits
DECL|member|lastBB0timer
id|ULONG
id|lastBB0timer
suffix:semicolon
singleline_comment|// static accum. buffer needed by Tachlite
DECL|typedef|FCSTATS
)brace
id|FCSTATS
suffix:semicolon
r_typedef
r_struct
singleline_comment|// Config Options
(brace
singleline_comment|// LS Bit first
DECL|member|USHORT
id|USHORT
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit0:
DECL|member|flogi
id|USHORT
id|flogi
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit1: We sent FLOGI - wait for Fabric logins
DECL|member|fabric
id|USHORT
id|fabric
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit2: Tachyon detected Fabric (FM stat LG)
DECL|member|LILPin
id|USHORT
id|LILPin
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit3: We can use an FC-AL LILP frame
DECL|member|target
id|USHORT
id|target
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit4: this Port has SCSI target capability
DECL|member|initiator
id|USHORT
id|initiator
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit5: this Port has SCSI initiator capability
DECL|member|extLoopback
id|USHORT
id|extLoopback
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit6: loopback at GBIC
DECL|member|intLoopback
id|USHORT
id|intLoopback
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit7: loopback in HP silicon
DECL|member|USHORT
id|USHORT
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit8:
DECL|member|USHORT
id|USHORT
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit9:
DECL|member|USHORT
id|USHORT
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit10:
DECL|member|USHORT
id|USHORT
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit11:
DECL|member|USHORT
id|USHORT
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit12:
DECL|member|USHORT
id|USHORT
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit13:
DECL|member|USHORT
id|USHORT
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit14:
DECL|member|USHORT
id|USHORT
suffix:colon
l_int|1
suffix:semicolon
singleline_comment|// bit15:
DECL|typedef|FC_OPTIONS
)brace
id|FC_OPTIONS
suffix:semicolon
DECL|struct|dyn_mem_pair
r_typedef
r_struct
id|dyn_mem_pair
(brace
DECL|member|BaseAllocated
r_void
op_star
id|BaseAllocated
suffix:semicolon
singleline_comment|// address as allocated from O/S;
DECL|member|AlignedAddress
r_int
r_int
id|AlignedAddress
suffix:semicolon
singleline_comment|// aligned address (used by Tachyon DMA)
DECL|typedef|ALIGNED_MEM
)brace
id|ALIGNED_MEM
suffix:semicolon
singleline_comment|// these structs contain only CRUCIAL (stuff we actually use) parameters
singleline_comment|// from FC-PH(n) logins.  (Don&squot;t save entire LOGIN payload to save mem.)
singleline_comment|// Implicit logout happens when the loop goes down - we require PDISC
singleline_comment|// to restore.  Explicit logout is when WE decide never to talk to someone,
singleline_comment|// or when a target refuses to talk to us, i.e. sends us a LOGO frame or
singleline_comment|// LS_RJT reject in response to our PLOGI request.
DECL|macro|IMPLICIT_LOGOUT
mdefine_line|#define IMPLICIT_LOGOUT 1
DECL|macro|EXPLICIT_LOGOUT
mdefine_line|#define EXPLICIT_LOGOUT 2
r_typedef
r_struct
(brace
DECL|member|channel
id|UCHAR
id|channel
suffix:semicolon
singleline_comment|// SCSI &quot;bus&quot;
DECL|member|target
id|UCHAR
id|target
suffix:semicolon
DECL|member|InqDeviceType
id|UCHAR
id|InqDeviceType
suffix:semicolon
singleline_comment|// byte 0 from SCSI Inquiry response
DECL|member|VolumeSetAddressing
id|UCHAR
id|VolumeSetAddressing
suffix:semicolon
singleline_comment|// FCP-SCSI LUN coding (40h for VSA)
DECL|member|LunMasking
id|UCHAR
id|LunMasking
suffix:semicolon
singleline_comment|// True if selective presentation supported
DECL|member|lun
id|UCHAR
id|lun
(braket
id|CPQFCTS_MAX_LUN
)braket
suffix:semicolon
DECL|typedef|SCSI_NEXUS
)brace
id|SCSI_NEXUS
suffix:semicolon
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|ucWWN
id|UCHAR
id|ucWWN
(braket
l_int|8
)braket
suffix:semicolon
singleline_comment|// a FC 64-bit World Wide Name/ PortID of target
singleline_comment|// addressing of single target on single loop...
DECL|member|liWWN
id|u64
id|liWWN
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|port_id
id|ULONG
id|port_id
suffix:semicolon
singleline_comment|// a FC 24-bit address of port (lower 8 bits = al_pa)
DECL|member|ScsiCmnd
id|Scsi_Cmnd
id|ScsiCmnd
suffix:semicolon
singleline_comment|// command buffer for Report Luns
DECL|macro|REPORT_LUNS_PL
mdefine_line|#define REPORT_LUNS_PL 256  
DECL|member|ReportLunsPayload
id|UCHAR
id|ReportLunsPayload
(braket
id|REPORT_LUNS_PL
)braket
suffix:semicolon
DECL|member|ScsiNexus
id|SCSI_NEXUS
id|ScsiNexus
suffix:semicolon
singleline_comment|// LUNs per FC device
DECL|member|LOGO_counter
id|ULONG
id|LOGO_counter
suffix:semicolon
singleline_comment|// might try several times before logging out for good
DECL|member|LOGO_timer
id|ULONG
id|LOGO_timer
suffix:semicolon
singleline_comment|// after LIP, ports expecting PDISC must time-out and
singleline_comment|// LOGOut if successful PDISC not completed in 2 secs
DECL|member|concurrent_seq
id|ULONG
id|concurrent_seq
suffix:semicolon
singleline_comment|// must be 1 or greater
DECL|member|rx_data_size
id|ULONG
id|rx_data_size
suffix:semicolon
singleline_comment|// e.g. 128, 256, 1024, 2048 per FC-PH spec
DECL|member|BB_credit
id|ULONG
id|BB_credit
suffix:semicolon
DECL|member|EE_credit
id|ULONG
id|EE_credit
suffix:semicolon
DECL|member|fcp_info
id|ULONG
id|fcp_info
suffix:semicolon
singleline_comment|// from PRLI (i.e. INITIATOR/ TARGET flags)
singleline_comment|// flags for login process
DECL|member|Originator
id|BOOLEAN
id|Originator
suffix:semicolon
singleline_comment|// Login sequence Originated (if false, we
singleline_comment|// responded to another port&squot;s login sequence)
DECL|member|plogi
id|BOOLEAN
id|plogi
suffix:semicolon
singleline_comment|// PLOGI frame ACCepted (originated or responded)
DECL|member|pdisc
id|BOOLEAN
id|pdisc
suffix:semicolon
singleline_comment|// PDISC frame was ORIGINATED (self-login logic)
DECL|member|prli
id|BOOLEAN
id|prli
suffix:semicolon
singleline_comment|// PRLI frame ACCepted (originated or responded)
DECL|member|flogi
id|BOOLEAN
id|flogi
suffix:semicolon
singleline_comment|// FLOGI frame ACCepted (originated or responded)
DECL|member|logo
id|BOOLEAN
id|logo
suffix:semicolon
singleline_comment|// port permanently logged out (invalid login param)
DECL|member|flogiReq
id|BOOLEAN
id|flogiReq
suffix:semicolon
singleline_comment|// Fabric login required (set in LIP process)
DECL|member|highest_ver
id|UCHAR
id|highest_ver
suffix:semicolon
DECL|member|lowest_ver
id|UCHAR
id|lowest_ver
suffix:semicolon
singleline_comment|// when the &quot;target&quot; (actually FC Port) is waiting for login
singleline_comment|// (e.g. after Link reset), set the device_blocked bit;
singleline_comment|// after Port completes login, un-block target.
DECL|member|device_blocked
id|UCHAR
id|device_blocked
suffix:semicolon
singleline_comment|// see Scsi_Device struct
singleline_comment|// define singly-linked list of logged-in ports
singleline_comment|// once a port_id is identified, it is remembered,
singleline_comment|// even if the port is removed indefinitely
DECL|member|pNextPort
id|PVOID
id|pNextPort
suffix:semicolon
singleline_comment|// actually, type PFC_LOGGEDIN_PORT; void for Compiler
DECL|typedef|FC_LOGGEDIN_PORT
DECL|typedef|PFC_LOGGEDIN_PORT
)brace
id|FC_LOGGEDIN_PORT
comma
op_star
id|PFC_LOGGEDIN_PORT
suffix:semicolon
singleline_comment|// This serves as the ESB (Exchange Status Block),
singleline_comment|// and has timeout counter; used for ABORTs
r_typedef
r_struct
(brace
singleline_comment|// FC-1 X_IDs
DECL|member|type
id|ULONG
id|type
suffix:semicolon
singleline_comment|// ELS_PLOGI, SCSI_IWE, ... (0 if free)
DECL|member|pLoggedInPort
id|PFC_LOGGEDIN_PORT
id|pLoggedInPort
suffix:semicolon
singleline_comment|// FC device on other end of Exchange
DECL|member|Cmnd
id|Scsi_Cmnd
op_star
id|Cmnd
suffix:semicolon
singleline_comment|// Linux SCSI command packet includes S/G list
DECL|member|timeOut
id|ULONG
id|timeOut
suffix:semicolon
singleline_comment|// units of ??, DEC by driver, Abort when 0
DECL|member|reTries
id|ULONG
id|reTries
suffix:semicolon
singleline_comment|// need one or more retries?
DECL|member|status
id|ULONG
id|status
suffix:semicolon
singleline_comment|// flags indicating errors (0 if none)
DECL|member|IRB
id|TachLiteIRB
id|IRB
suffix:semicolon
singleline_comment|// I/O Request Block, gets copied to ERQ
DECL|member|fchs
id|TachFCHDR_GCMND
id|fchs
suffix:semicolon
singleline_comment|// location of IRB&squot;s Req_A_SFS_Addr
DECL|typedef|FC_EXCHANGE
DECL|typedef|PFC_EXCHANGE
)brace
id|FC_EXCHANGE
comma
op_star
id|PFC_EXCHANGE
suffix:semicolon
singleline_comment|// Unfortunately, Linux limits our kmalloc() allocations to 128k.
singleline_comment|// Because of this and the fact that our ScsiRegister allocation
singleline_comment|// is also constrained, we move this large structure out for
singleline_comment|// allocation after Scsi Register.
singleline_comment|// (In other words, this cumbersome indirection is necessary
singleline_comment|// because of kernel memory allocation constraints!)
r_typedef
r_struct
singleline_comment|// we will allocate this dynamically
(brace
DECL|member|fcExchange
id|FC_EXCHANGE
id|fcExchange
(braket
id|TACH_MAX_XID
)braket
suffix:semicolon
DECL|typedef|FC_EXCHANGES
)brace
id|FC_EXCHANGES
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|Name
r_char
id|Name
(braket
l_int|64
)braket
suffix:semicolon
singleline_comment|// name of controller (&quot;HP Tachlite TL Rev2.0, 33MHz, 64bit bus&quot;)
singleline_comment|//PVOID  pAdapterDevExt; // back pointer to device object/extension
DECL|member|ChipType
id|ULONG
id|ChipType
suffix:semicolon
singleline_comment|// local numeric key for Tachyon Type / Rev.
DECL|member|status
id|ULONG
id|status
suffix:semicolon
singleline_comment|// our Driver - logical status
DECL|member|Registers
id|TL_REGISTERS
id|Registers
suffix:semicolon
singleline_comment|// reg addresses &amp; host memory copies
singleline_comment|// FC-4 mapping of &squot;transaction&squot; to X_IDs
DECL|member|LILPmap
id|UCHAR
id|LILPmap
(braket
l_int|32
op_star
l_int|4
)braket
suffix:semicolon
singleline_comment|// Loop Position Map of ALPAs (late FC-AL only)
DECL|member|Options
id|FC_OPTIONS
id|Options
suffix:semicolon
singleline_comment|// e.g. Target, Initiator, loopback...
DECL|member|highest_FCPH_ver
id|UCHAR
id|highest_FCPH_ver
suffix:semicolon
singleline_comment|// FC-PH version limits
DECL|member|lowest_FCPH_ver
id|UCHAR
id|lowest_FCPH_ver
suffix:semicolon
singleline_comment|// FC-PH version limits
DECL|member|Exchanges
id|FC_EXCHANGES
op_star
id|Exchanges
suffix:semicolon
DECL|member|fcLsExchangeLRU
id|ULONG
id|fcLsExchangeLRU
suffix:semicolon
singleline_comment|// Least Recently Used counter (Link Service)
DECL|member|fcSestExchangeLRU
id|ULONG
id|fcSestExchangeLRU
suffix:semicolon
singleline_comment|// Least Recently Used counter (FCP-SCSI)
DECL|member|fcPorts
id|FC_LOGGEDIN_PORT
id|fcPorts
suffix:semicolon
singleline_comment|// linked list of every FC port ever seen
DECL|member|fcStats
id|FCSTATS
id|fcStats
suffix:semicolon
singleline_comment|// FC comm err counters
singleline_comment|// Host memory QUEUE pointers
DECL|member|ERQ
id|TachLiteERQ
op_star
id|ERQ
suffix:semicolon
singleline_comment|// Exchange Request Que 
DECL|member|IMQ
id|TachyonIMQ
op_star
id|IMQ
suffix:semicolon
singleline_comment|// Inbound Message Que 
DECL|member|SFQ
id|TachLiteSFQ
op_star
id|SFQ
suffix:semicolon
singleline_comment|// Single Frame Queue
DECL|member|SEST
id|TachSEST
op_star
id|SEST
suffix:semicolon
singleline_comment|// SCSI Exchange State Table
singleline_comment|// these function pointers are for &quot;generic&quot; functions, which are
singleline_comment|// replaced with Host Bus Adapter types at
singleline_comment|// runtime.
DECL|member|CreateTachyonQues
r_int
(paren
op_star
id|CreateTachyonQues
)paren
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|DestroyTachyonQues
r_int
(paren
op_star
id|DestroyTachyonQues
)paren
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|LaserControl
r_int
(paren
op_star
id|LaserControl
)paren
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
singleline_comment|// e.g. On/Off
DECL|member|ResetTachyon
r_int
(paren
op_star
id|ResetTachyon
)paren
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|FreezeTachyon
r_void
(paren
op_star
id|FreezeTachyon
)paren
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|UnFreezeTachyon
r_void
(paren
op_star
id|UnFreezeTachyon
)paren
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|InitializeTachyon
r_int
(paren
op_star
id|InitializeTachyon
)paren
(paren
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|InitializeFrameManager
r_int
(paren
op_star
id|InitializeFrameManager
)paren
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|ProcessIMQEntry
r_int
(paren
op_star
id|ProcessIMQEntry
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|ReadWriteWWN
r_int
(paren
op_star
id|ReadWriteWWN
)paren
(paren
r_void
op_star
comma
r_int
id|ReadWrite
)paren
suffix:semicolon
DECL|member|ReadWriteNVRAM
r_int
(paren
op_star
id|ReadWriteNVRAM
)paren
(paren
r_void
op_star
comma
r_void
op_star
comma
r_int
id|ReadWrite
)paren
suffix:semicolon
DECL|typedef|TACHYON
DECL|typedef|PTACHYON
)brace
id|TACHYON
comma
op_star
id|PTACHYON
suffix:semicolon
r_void
id|cpqfcTSClearLinkStatusCounters
c_func
(paren
id|TACHYON
op_star
id|fcChip
)paren
suffix:semicolon
r_int
id|CpqTsCreateTachLiteQues
c_func
(paren
r_void
op_star
id|pHBA
comma
r_int
id|opcode
)paren
suffix:semicolon
r_int
id|CpqTsDestroyTachLiteQues
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|CpqTsInitializeTachLite
c_func
(paren
r_void
op_star
id|pHBA
comma
r_int
id|opcode1
comma
r_int
id|opcode2
)paren
suffix:semicolon
r_int
id|CpqTsProcessIMQEntry
c_func
(paren
r_void
op_star
id|pHBA
)paren
suffix:semicolon
r_int
id|CpqTsResetTachLite
c_func
(paren
r_void
op_star
id|pHBA
comma
r_int
id|type
)paren
suffix:semicolon
r_void
id|CpqTsFreezeTachlite
c_func
(paren
r_void
op_star
id|pHBA
comma
r_int
id|type
)paren
suffix:semicolon
r_void
id|CpqTsUnFreezeTachlite
c_func
(paren
r_void
op_star
id|pHBA
comma
r_int
id|type
)paren
suffix:semicolon
r_int
id|CpqTsInitializeFrameManager
c_func
(paren
r_void
op_star
id|pHBA
comma
r_int
)paren
suffix:semicolon
r_int
id|CpqTsLaserControl
c_func
(paren
r_void
op_star
id|addrBase
comma
r_int
id|opcode
)paren
suffix:semicolon
r_int
id|CpqTsReadWriteWWN
c_func
(paren
r_void
op_star
comma
r_int
id|ReadWrite
)paren
suffix:semicolon
r_int
id|CpqTsReadWriteNVRAM
c_func
(paren
r_void
op_star
comma
r_void
op_star
id|data
comma
r_int
id|ReadWrite
)paren
suffix:semicolon
r_void
id|cpqfcTS_WorkTask
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|HostAdapter
)paren
suffix:semicolon
r_void
id|cpqfcTSWorkerThread
c_func
(paren
r_void
op_star
id|host
)paren
suffix:semicolon
r_int
id|cpqfcTS_GetNVRAM_data
c_func
(paren
id|UCHAR
op_star
id|wwnbuf
comma
id|UCHAR
op_star
id|buf
)paren
suffix:semicolon
id|ULONG
id|cpqfcTS_ReadNVRAM
c_func
(paren
r_void
op_star
id|GPIOin
comma
r_void
op_star
id|GPIOout
comma
id|USHORT
id|count
comma
id|UCHAR
op_star
id|buf
)paren
suffix:semicolon
id|BOOLEAN
id|tl_write_i2c_nvram
c_func
(paren
r_void
op_star
id|GPIOin
comma
r_void
op_star
id|GPIOout
comma
id|USHORT
id|startOffset
comma
singleline_comment|// e.g. 0x2f for WWN start
id|USHORT
id|count
comma
id|UCHAR
op_star
id|buf
)paren
suffix:semicolon
singleline_comment|// define misc functions 
r_int
id|cpqfcTSGetLPSM
c_func
(paren
id|PTACHYON
id|fcChip
comma
r_char
id|cErrorString
(braket
)braket
)paren
suffix:semicolon
r_int
id|cpqfcTSDecodeGBICtype
c_func
(paren
id|PTACHYON
id|fcChip
comma
r_char
id|cErrorString
(braket
)braket
)paren
suffix:semicolon
r_void
op_star
id|fcMemManager
c_func
(paren
id|ALIGNED_MEM
op_star
id|dyn_mem_pair
comma
id|ULONG
id|n_alloc
comma
id|ULONG
id|ab
comma
id|ULONG
id|ulAlignedAddress
)paren
suffix:semicolon
r_void
id|BigEndianSwap
c_func
(paren
id|UCHAR
op_star
id|source
comma
id|UCHAR
op_star
id|dest
comma
id|USHORT
id|cnt
)paren
suffix:semicolon
singleline_comment|//ULONG virt_to_phys( PVOID virtaddr );
singleline_comment|// Linux interrupt handler
r_void
id|cpqfcTS_intr_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_void
id|cpqfcTSheartbeat
c_func
(paren
r_int
r_int
id|ptr
)paren
suffix:semicolon
singleline_comment|// The biggest Q element we deal with is Aborts - we
singleline_comment|// need 4 bytes for x_ID, and a Scsi_Cmnd (~284 bytes)
singleline_comment|//#define LINKQ_ITEM_SIZE ((4+sizeof(Scsi_Cmnd)+3)/4)
DECL|macro|LINKQ_ITEM_SIZE
mdefine_line|#define LINKQ_ITEM_SIZE (3*16)
r_typedef
r_struct
(brace
DECL|member|Type
id|ULONG
id|Type
suffix:semicolon
singleline_comment|// e.g. LINKUP, SFQENTRY, PDISC, BLS_ABTS, ...
DECL|member|ulBuff
id|ULONG
id|ulBuff
(braket
id|LINKQ_ITEM_SIZE
)braket
suffix:semicolon
DECL|typedef|LINKQ_ITEM
)brace
id|LINKQ_ITEM
suffix:semicolon
DECL|macro|FC_LINKQ_DEPTH
mdefine_line|#define FC_LINKQ_DEPTH TACH_MAX_XID
r_typedef
r_struct
(brace
DECL|member|producer
id|ULONG
id|producer
suffix:semicolon
DECL|member|consumer
id|ULONG
id|consumer
suffix:semicolon
singleline_comment|// when producer equals consumer, Q empty
DECL|member|Qitem
id|LINKQ_ITEM
id|Qitem
(braket
id|FC_LINKQ_DEPTH
)braket
suffix:semicolon
DECL|typedef|FC_LINK_QUE
DECL|typedef|PFC_LINK_QUE
)brace
id|FC_LINK_QUE
comma
op_star
id|PFC_LINK_QUE
suffix:semicolon
singleline_comment|// DPC routines post to here on Inbound SCSI frames
singleline_comment|// User thread processes
DECL|macro|FC_SCSIQ_DEPTH
mdefine_line|#define FC_SCSIQ_DEPTH 32
r_typedef
r_struct
(brace
DECL|member|Type
r_int
id|Type
suffix:semicolon
singleline_comment|// e.g. SCSI
DECL|member|ulBuff
id|ULONG
id|ulBuff
(braket
l_int|3
op_star
l_int|16
)braket
suffix:semicolon
DECL|typedef|SCSIQ_ITEM
)brace
id|SCSIQ_ITEM
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|producer
id|ULONG
id|producer
suffix:semicolon
DECL|member|consumer
id|ULONG
id|consumer
suffix:semicolon
singleline_comment|// when producer equals consumer, Q empty
DECL|member|Qitem
id|SCSIQ_ITEM
id|Qitem
(braket
id|FC_SCSIQ_DEPTH
)braket
suffix:semicolon
DECL|typedef|FC_SCSI_QUE
DECL|typedef|PFC_SCSI_QUE
)brace
id|FC_SCSI_QUE
comma
op_star
id|PFC_SCSI_QUE
suffix:semicolon
DECL|macro|DYNAMIC_ALLOCATIONS
mdefine_line|#define DYNAMIC_ALLOCATIONS 4  
singleline_comment|// Tachyon aligned allocations: ERQ,IMQ,SFQ,SEST
singleline_comment|// Linux space allocated per HBA (chip state, etc.)
r_typedef
r_struct
(brace
DECL|member|HostAdapter
r_struct
id|Scsi_Host
op_star
id|HostAdapter
suffix:semicolon
singleline_comment|// back pointer to Linux Scsi struct
DECL|member|fcChip
id|TACHYON
id|fcChip
suffix:semicolon
singleline_comment|// All Tachyon registers, Queues, functions
DECL|member|dynamic_mem
id|ALIGNED_MEM
id|dynamic_mem
(braket
id|DYNAMIC_ALLOCATIONS
)braket
suffix:semicolon
DECL|member|PciDev
r_struct
id|pci_dev
op_star
id|PciDev
suffix:semicolon
DECL|member|LinkDnCmnd
id|Scsi_Cmnd
op_star
id|LinkDnCmnd
(braket
id|CPQFCTS_REQ_QUEUE_LEN
)braket
suffix:semicolon
singleline_comment|// collects Cmnds during LDn
singleline_comment|// (for Acceptable targets)
DECL|member|BoardLockCmnd
id|Scsi_Cmnd
op_star
id|BoardLockCmnd
(braket
id|CPQFCTS_REQ_QUEUE_LEN
)braket
suffix:semicolon
singleline_comment|// SEST was full
DECL|member|BadTargetCmnd
id|Scsi_Cmnd
op_star
id|BadTargetCmnd
(braket
id|CPQFCTS_MAX_TARGET_ID
)braket
suffix:semicolon
singleline_comment|// missing targets
DECL|member|HBAnum
id|u_char
id|HBAnum
suffix:semicolon
singleline_comment|// 0-based host number
DECL|member|cpqfcTStimer
r_struct
id|timer_list
id|cpqfcTStimer
suffix:semicolon
singleline_comment|// FC utility timer for implicit
singleline_comment|// logouts, FC protocol timeouts, etc.
DECL|member|fcStatsTime
r_int
id|fcStatsTime
suffix:semicolon
singleline_comment|// Statistics delta reporting time
DECL|member|worker_thread
r_struct
id|task_struct
op_star
id|worker_thread
suffix:semicolon
singleline_comment|// our kernel thread
DECL|member|PortDiscDone
r_int
id|PortDiscDone
suffix:semicolon
singleline_comment|// set by SendLogins(), cleared by LDn
DECL|member|TachFrozen
r_struct
id|semaphore
op_star
id|TachFrozen
suffix:semicolon
DECL|member|TYOBcomplete
r_struct
id|semaphore
op_star
id|TYOBcomplete
suffix:semicolon
singleline_comment|// handshake for Tach outbound frames
DECL|member|fcQueReady
r_struct
id|semaphore
op_star
id|fcQueReady
suffix:semicolon
singleline_comment|// FibreChannel work for our kernel thread
DECL|member|notify_wt
r_struct
id|semaphore
op_star
id|notify_wt
suffix:semicolon
singleline_comment|// synchronizes kernel thread kill
DECL|member|BoardLock
r_struct
id|semaphore
op_star
id|BoardLock
suffix:semicolon
DECL|member|fcLQ
id|PFC_LINK_QUE
id|fcLQ
suffix:semicolon
singleline_comment|// the WorkerThread operates on this
DECL|member|hba_spinlock
id|spinlock_t
id|hba_spinlock
suffix:semicolon
singleline_comment|// held/released by WorkerThread
DECL|typedef|CPQFCHBA
)brace
id|CPQFCHBA
suffix:semicolon
DECL|macro|CPQ_SPINLOCK_HBA
mdefine_line|#define&t;CPQ_SPINLOCK_HBA( x )   spin_lock(&amp;x-&gt;hba_spinlock);
DECL|macro|CPQ_SPINUNLOCK_HBA
mdefine_line|#define CPQ_SPINUNLOCK_HBA(x)   spin_unlock(&amp;x-&gt;hba_spinlock);
r_void
id|cpqfcTSImplicitLogout
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|PFC_LOGGEDIN_PORT
id|pFcPort
)paren
suffix:semicolon
r_void
id|cpqfcTSTerminateExchange
c_func
(paren
id|CPQFCHBA
op_star
comma
id|SCSI_NEXUS
op_star
id|target
comma
r_int
)paren
suffix:semicolon
id|PFC_LOGGEDIN_PORT
id|fcPortLoggedIn
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|TachFCHDR_GCMND
op_star
id|fchs
comma
id|BOOLEAN
comma
id|BOOLEAN
)paren
suffix:semicolon
r_void
id|fcProcessLoggedIn
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|TachFCHDR_GCMND
op_star
id|fchs
)paren
suffix:semicolon
id|ULONG
id|cpqfcTSBuildExchange
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|ULONG
id|type
comma
singleline_comment|// e.g. PLOGI
id|TachFCHDR_GCMND
op_star
id|InFCHS
comma
singleline_comment|// incoming FCHS
r_void
op_star
id|Data
comma
singleline_comment|// the CDB, scatter/gather, etc.  
id|LONG
op_star
id|ExchangeID
)paren
suffix:semicolon
singleline_comment|// allocated exchange ID
id|ULONG
id|cpqfcTSStartExchange
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
id|LONG
id|ExchangeID
)paren
suffix:semicolon
r_void
id|cpqfcTSCompleteExchange
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|ULONG
id|exchange_ID
)paren
suffix:semicolon
id|PFC_LOGGEDIN_PORT
id|fcFindLoggedInPort
c_func
(paren
id|PTACHYON
id|fcChip
comma
id|Scsi_Cmnd
op_star
id|Cmnd
comma
singleline_comment|// (We want the channel/target/lun Nexus from Cmnd)
id|ULONG
id|port_id
comma
singleline_comment|// search linked list for al_pa, or
id|UCHAR
id|wwn
(braket
l_int|8
)braket
comma
singleline_comment|// search linked list for WWN, or...
id|PFC_LOGGEDIN_PORT
op_star
id|pLastLoggedInPort
)paren
suffix:semicolon
singleline_comment|// don&squot;t do this unless you have the right hardware!
DECL|macro|TRIGGERABLE_HBA
mdefine_line|#define TRIGGERABLE_HBA 1
macro_line|#ifdef TRIGGERABLE_HBA
r_void
id|TriggerHBA
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
r_void
id|cpqfcTSPutLinkQue
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
r_int
id|Type
comma
r_void
op_star
id|QueContent
)paren
suffix:semicolon
r_void
id|fcPutScsiQue
c_func
(paren
id|CPQFCHBA
op_star
id|cpqfcHBAdata
comma
r_int
id|Type
comma
r_void
op_star
id|QueContent
)paren
suffix:semicolon
r_void
id|fcLinkQReset
c_func
(paren
id|CPQFCHBA
op_star
)paren
suffix:semicolon
r_void
id|fcScsiQReset
c_func
(paren
id|CPQFCHBA
op_star
)paren
suffix:semicolon
r_void
id|fcSestReset
c_func
(paren
id|CPQFCHBA
op_star
)paren
suffix:semicolon
r_extern
r_const
id|UCHAR
id|valid_al_pa
(braket
)braket
suffix:semicolon
r_extern
r_const
r_int
id|number_of_al_pa
suffix:semicolon
DECL|macro|FCP_RESID_UNDER
mdefine_line|#define FCP_RESID_UNDER   0x80000
DECL|macro|FCP_RESID_OVER
mdefine_line|#define FCP_RESID_OVER    0x40000
DECL|macro|FCP_SNS_LEN_VALID
mdefine_line|#define FCP_SNS_LEN_VALID 0x20000
DECL|macro|FCP_RSP_LEN_VALID
mdefine_line|#define FCP_RSP_LEN_VALID 0x10000
singleline_comment|// RSP_CODE definitions (dpANS Fibre Channel Protocol for SCSI, pg 34)
DECL|macro|FCP_DATA_LEN_NOT_BURST_LEN
mdefine_line|#define FCP_DATA_LEN_NOT_BURST_LEN 0x1000000
DECL|macro|FCP_CMND_FIELD_INVALID
mdefine_line|#define FCP_CMND_FIELD_INVALID     0x2000000
DECL|macro|FCP_DATA_RO_NOT_XRDY_RO
mdefine_line|#define FCP_DATA_RO_NOT_XRDY_RO    0x3000000
DECL|macro|FCP_TASKFUNCTION_NS
mdefine_line|#define FCP_TASKFUNCTION_NS        0x4000000
DECL|macro|FCP_TASKFUNCTION_FAIL
mdefine_line|#define FCP_TASKFUNCTION_FAIL      0x5000000
singleline_comment|// FCP-SCSI response status struct
r_typedef
r_struct
singleline_comment|// see &quot;TachFCHDR_RSP&quot; definition - 64 bytes
(brace
DECL|member|reserved
id|__u32
id|reserved
suffix:semicolon
DECL|member|reserved1
id|__u32
id|reserved1
suffix:semicolon
DECL|member|fcp_status
id|__u32
id|fcp_status
suffix:semicolon
singleline_comment|// field validity and SCSI status
DECL|member|fcp_resid
id|__u32
id|fcp_resid
suffix:semicolon
DECL|member|fcp_sns_len
id|__u32
id|fcp_sns_len
suffix:semicolon
singleline_comment|// length of FCP_SNS_INFO field
DECL|member|fcp_rsp_len
id|__u32
id|fcp_rsp_len
suffix:semicolon
singleline_comment|// length of FCP_RSP_INFO field (expect 8)
DECL|member|fcp_rsp_info
id|__u32
id|fcp_rsp_info
suffix:semicolon
singleline_comment|// 4 bytes of FCP protocol response information
DECL|member|fcp_rsp_info2
id|__u32
id|fcp_rsp_info2
suffix:semicolon
singleline_comment|// (4 more bytes, since most implementations use 8)
DECL|member|fcp_sns_info
id|__u8
id|fcp_sns_info
(braket
l_int|36
)braket
suffix:semicolon
singleline_comment|// bytes for SCSI sense (ASC, ASCQ)
DECL|typedef|FCP_STATUS_RESPONSE
DECL|typedef|PFCP_STATUS_RESPONSE
)brace
id|FCP_STATUS_RESPONSE
comma
op_star
id|PFCP_STATUS_RESPONSE
suffix:semicolon
singleline_comment|// Fabric State Change Registration
DECL|struct|scrpl
r_typedef
r_struct
id|scrpl
(brace
DECL|member|command
id|__u32
id|command
suffix:semicolon
DECL|member|function
id|__u32
id|function
suffix:semicolon
DECL|typedef|SCR_PL
)brace
id|SCR_PL
suffix:semicolon
singleline_comment|// Fabric Name Service Request
DECL|struct|nsrpl
r_typedef
r_struct
id|nsrpl
(brace
DECL|member|CT_Rev
id|__u32
id|CT_Rev
suffix:semicolon
singleline_comment|// (&amp; IN_ID)   WORD 0
DECL|member|FCS_Type
id|__u32
id|FCS_Type
suffix:semicolon
singleline_comment|// WORD 1
DECL|member|Command_code
id|__u32
id|Command_code
suffix:semicolon
singleline_comment|// WORD 2
DECL|member|reason_code
id|__u32
id|reason_code
suffix:semicolon
singleline_comment|// WORD 3
DECL|member|FCP
id|__u32
id|FCP
suffix:semicolon
singleline_comment|// WORD 4 (lower byte)
DECL|typedef|NSR_PL
)brace
id|NSR_PL
suffix:semicolon
singleline_comment|// &quot;FC.H&quot;
DECL|macro|MAX_RX_SIZE
mdefine_line|#define MAX_RX_SIZE&t;&t;0x800&t;
singleline_comment|// Max Receive Buffer Size is 2048
DECL|macro|MIN_RX_SIZE
mdefine_line|#define MIN_RX_SIZE&t;&t;0x100&t;
singleline_comment|// Min Size is 256, per FC-PLDA Spec
DECL|macro|MAX_TARGET_RXIDS
mdefine_line|#define&t;MAX_TARGET_RXIDS&t;SEST_DEPTH
DECL|macro|TARGET_RX_SIZE
mdefine_line|#define TARGET_RX_SIZE&t;&t;SEST_BUFFER_LENGTH
DECL|macro|CLASS_1
mdefine_line|#define CLASS_1&t;&t;&t;0x01
DECL|macro|CLASS_2
mdefine_line|#define CLASS_2&t;&t;&t;0x02
DECL|macro|CLASS_3
mdefine_line|#define CLASS_3&t;&t;&t;0x03
DECL|macro|FC_PH42
mdefine_line|#define FC_PH42&t;&t;&t;0x08
DECL|macro|FC_PH43
mdefine_line|#define FC_PH43&t;&t;&t;0x09
DECL|macro|FC_PH3
mdefine_line|#define FC_PH3&t;&t;&t;0x20
DECL|macro|RR_TOV
mdefine_line|#define RR_TOV&t;&t;&t;2&t;
singleline_comment|// Minimum Time for target to wait for
singleline_comment|// PDISC after a LIP.
DECL|macro|E_D_TOV
mdefine_line|#define E_D_TOV&t;&t;&t;2&t;
singleline_comment|// Minimum Time to wait for Sequence
singleline_comment|// Completion.
DECL|macro|R_A_TOV
mdefine_line|#define R_A_TOV&t;&t;&t;0&t;
singleline_comment|// Minimum Time for Target to wait 
singleline_comment|// before reclaiming resources.
singleline_comment|//
singleline_comment|//&t;R_CTL Field
singleline_comment|//
singleline_comment|//&t;Routing Bits (31-28)
singleline_comment|//
DECL|macro|FC4_DEVICE_DATA
mdefine_line|#define FC4_DEVICE_DATA&t;&t;0x00000000
DECL|macro|EXT_LINK_DATA
mdefine_line|#define EXT_LINK_DATA&t;&t;0x20000000
DECL|macro|FC4_LINK_DATA
mdefine_line|#define FC4_LINK_DATA&t;&t;0x30000000
DECL|macro|VIDEO_DATA
mdefine_line|#define VIDEO_DATA&t;&t;0x40000000
DECL|macro|BASIC_LINK_DATA
mdefine_line|#define BASIC_LINK_DATA&t;&t;0x80000000
DECL|macro|LINK_CONTROL
mdefine_line|#define LINK_CONTROL&t;&t;0xC0000000
DECL|macro|ROUTING_MASK
mdefine_line|#define ROUTING_MASK&t;&t;0xF0000000
singleline_comment|//
singleline_comment|//&t;Information Bits (27-24)
singleline_comment|//
DECL|macro|UNCAT_INFORMATION
mdefine_line|#define UNCAT_INFORMATION&t;0x00000000
DECL|macro|SOLICITED_DATA
mdefine_line|#define SOLICITED_DATA&t;&t;0x01000000
DECL|macro|UNSOLICITED_CONTROL
mdefine_line|#define UNSOLICITED_CONTROL&t;0x02000000
DECL|macro|SOLICITED_CONTROL
mdefine_line|#define SOLICITED_CONTROL&t;0x03000000
DECL|macro|UNSOLICITED_DATA
mdefine_line|#define UNSOLICITED_DATA&t;0x04000000
DECL|macro|DATA_DESCRIPTOR
mdefine_line|#define DATA_DESCRIPTOR&t;&t;0x05000000
DECL|macro|UNSOLICITED_COMMAND
mdefine_line|#define UNSOLICITED_COMMAND&t;0x06000000
DECL|macro|COMMAND_STATUS
mdefine_line|#define COMMAND_STATUS&t;&t;0x07000000
DECL|macro|INFO_MASK
mdefine_line|#define INFO_MASK&t;&t;0x0F000000
singleline_comment|//
singleline_comment|//&t;(Link Control Codes)
singleline_comment|//
DECL|macro|ACK_1
mdefine_line|#define ACK_1&t;&t;&t;0x00000000
DECL|macro|ACK_0_OR_N
mdefine_line|#define ACK_0_OR_N&t;&t;0x01000000
DECL|macro|P_RJT
mdefine_line|#define P_RJT&t;&t;&t;0x02000000 
DECL|macro|F_RJT
mdefine_line|#define F_RJT&t;&t;&t;0x03000000 
DECL|macro|P_BSY
mdefine_line|#define P_BSY&t;&t;&t;0x04000000
DECL|macro|FABRIC_BUSY_TO_DF
mdefine_line|#define FABRIC_BUSY_TO_DF&t;0x05000000&t;
singleline_comment|// Fabric Busy to Data Frame
DECL|macro|FABRIC_BUSY_TO_LC
mdefine_line|#define FABRIC_BUSY_TO_LC&t;0x06000000&t;
singleline_comment|// Fabric Busy to Link Ctl Frame
DECL|macro|LINK_CREDIT_RESET
mdefine_line|#define LINK_CREDIT_RESET&t;0x07000000
singleline_comment|//
singleline_comment|//&t;(Link Service Command Codes)
singleline_comment|//
singleline_comment|//#define LS_RJT&t;&t;&t;0x01000000&t;// LS Reject
DECL|macro|LS_ACC
mdefine_line|#define LS_ACC&t;&t;&t;0x02000000&t;
singleline_comment|// LS Accept
DECL|macro|LS_PLOGI
mdefine_line|#define LS_PLOGI&t;&t;0x03000000&t;
singleline_comment|// N_PORT Login
DECL|macro|LS_FLOGI
mdefine_line|#define LS_FLOGI&t;&t;0x04000000&t;
singleline_comment|// F_PORT Login
DECL|macro|LS_LOGO
mdefine_line|#define LS_LOGO&t;&t;&t;0x05000000&t;
singleline_comment|// Logout
DECL|macro|LS_ABTX
mdefine_line|#define LS_ABTX&t;&t;&t;0x06000000&t;
singleline_comment|// Abort Exchange
DECL|macro|LS_RCS
mdefine_line|#define LS_RCS&t;&t;&t;0x07000000&t;
singleline_comment|// Read Connection Status
DECL|macro|LS_RES
mdefine_line|#define LS_RES&t;&t;&t;0x08000000&t;
singleline_comment|// Read Exchange Status
DECL|macro|LS_RSS
mdefine_line|#define LS_RSS&t;&t;&t;0x09000000&t;
singleline_comment|// Read Sequence Status
DECL|macro|LS_RSI
mdefine_line|#define LS_RSI&t;&t;&t;0x0A000000&t;
singleline_comment|// Request Seq Initiative
DECL|macro|LS_ESTS
mdefine_line|#define LS_ESTS&t;&t;&t;0x0B000000&t;
singleline_comment|// Establish Steaming
DECL|macro|LS_ESTC
mdefine_line|#define LS_ESTC&t;&t;&t;0x0C000000&t;
singleline_comment|// Estimate Credit
DECL|macro|LS_ADVC
mdefine_line|#define LS_ADVC&t;&t;&t;0x0D000000&t;
singleline_comment|// Advice Credit
DECL|macro|LS_RTV
mdefine_line|#define LS_RTV&t;&t;&t;0x0E000000&t;
singleline_comment|// Read Timeout Value
DECL|macro|LS_RLS
mdefine_line|#define LS_RLS&t;&t;&t;0x0F000000&t;
singleline_comment|// Read Link Status
DECL|macro|LS_ECHO
mdefine_line|#define LS_ECHO&t;&t;&t;0x10000000&t;
singleline_comment|// Echo
DECL|macro|LS_TEST
mdefine_line|#define LS_TEST&t;&t;&t;0x11000000&t;
singleline_comment|// Test
DECL|macro|LS_RRQ
mdefine_line|#define LS_RRQ&t;&t;&t;0x12000000&t;
singleline_comment|// Reinstate Rec. Qual.
DECL|macro|LS_PRLI
mdefine_line|#define LS_PRLI&t;&t;&t;0x20000000&t;
singleline_comment|// Process Login
DECL|macro|LS_PRLO
mdefine_line|#define LS_PRLO&t;&t;&t;0x21000000&t;
singleline_comment|// Process Logout
DECL|macro|LS_TPRLO
mdefine_line|#define LS_TPRLO&t;&t;0x24000000&t;
singleline_comment|// 3rd Party Process Logout
DECL|macro|LS_PDISC
mdefine_line|#define LS_PDISC&t;&t;0x50000000&t;
singleline_comment|// Process Discovery
DECL|macro|LS_FDISC
mdefine_line|#define LS_FDISC&t;&t;0x51000000&t;
singleline_comment|// Fabric Discovery
DECL|macro|LS_ADISC
mdefine_line|#define LS_ADISC&t;&t;0x52000000&t;
singleline_comment|// Discover Address
DECL|macro|LS_RNC
mdefine_line|#define LS_RNC&t;&t;&t;0x53000000&t;
singleline_comment|// Report Node Capability
DECL|macro|LS_SCR
mdefine_line|#define LS_SCR                  0x62000000      
singleline_comment|// State Change Registration
DECL|macro|LS_MASK
mdefine_line|#define LS_MASK&t;&t;&t;0xFF000000&t;
singleline_comment|//
singleline_comment|// &t;TYPE Bit Masks
singleline_comment|//
DECL|macro|BASIC_LINK_SERVICE
mdefine_line|#define BASIC_LINK_SERVICE&t;0x00000000
DECL|macro|EXT_LINK_SERVICE
mdefine_line|#define EXT_LINK_SERVICE&t;0x01000000
DECL|macro|LLC
mdefine_line|#define LLC&t;&t;&t;0x04000000
DECL|macro|LLC_SNAP
mdefine_line|#define LLC_SNAP&t;&t;0x05000000
DECL|macro|SCSI_FCP
mdefine_line|#define SCSI_FCP&t;&t;0x08000000
DECL|macro|SCSI_GPP
mdefine_line|#define SCSI_GPP&t;&t;0x09000000
DECL|macro|IPI3_MASTER
mdefine_line|#define IPI3_MASTER&t;&t;0x11000000
DECL|macro|IPI3_SLAVE
mdefine_line|#define IPI3_SLAVE&t;&t;0x12000000
DECL|macro|IPI3_PEER
mdefine_line|#define IPI3_PEER&t;&t;0x13000000
DECL|macro|CP_IPI3_MASTER
mdefine_line|#define CP_IPI3_MASTER&t;&t;0x15000000
DECL|macro|CP_IPI3_SLAVE
mdefine_line|#define CP_IPI3_SLAVE&t;&t;0x16000000
DECL|macro|CP_IPI3_PEER
mdefine_line|#define CP_IPI3_PEER&t;&t;0x17000000
DECL|macro|SBCCS_CHANNEL
mdefine_line|#define SBCCS_CHANNEL&t;&t;0x19000000
DECL|macro|SBCCS_CONTROL
mdefine_line|#define SBCCS_CONTROL&t;&t;0x1A000000
DECL|macro|FIBRE_SERVICES
mdefine_line|#define FIBRE_SERVICES&t;&t;0x20000000
DECL|macro|FC_FG
mdefine_line|#define FC_FG&t;&t;&t;0x21000000
DECL|macro|FC_XS
mdefine_line|#define FC_XS&t;&t;&t;0x22000000
DECL|macro|FC_AL
mdefine_line|#define FC_AL&t;&t;&t;0x23000000
DECL|macro|SNMP
mdefine_line|#define SNMP&t;&t;&t;0x24000000
DECL|macro|HIPPI_FP
mdefine_line|#define HIPPI_FP&t;&t;0x40000000
DECL|macro|TYPE_MASK
mdefine_line|#define TYPE_MASK&t;&t;0xFF000000
r_typedef
r_struct
(brace
DECL|member|seq_id_valid
id|UCHAR
id|seq_id_valid
suffix:semicolon
DECL|member|seq_id
id|UCHAR
id|seq_id
suffix:semicolon
DECL|member|reserved
id|USHORT
id|reserved
suffix:semicolon
singleline_comment|// 2 bytes reserved
DECL|member|ox_rx_id
id|ULONG
id|ox_rx_id
suffix:semicolon
DECL|member|low_seq_cnt
id|USHORT
id|low_seq_cnt
suffix:semicolon
DECL|member|high_seq_cnt
id|USHORT
id|high_seq_cnt
suffix:semicolon
DECL|typedef|BA_ACC_PAYLOAD
)brace
id|BA_ACC_PAYLOAD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|reserved
id|UCHAR
id|reserved
suffix:semicolon
DECL|member|reason_code
id|UCHAR
id|reason_code
suffix:semicolon
DECL|member|reason_explain
id|UCHAR
id|reason_explain
suffix:semicolon
DECL|member|vendor_unique
id|UCHAR
id|vendor_unique
suffix:semicolon
DECL|typedef|BA_RJT_PAYLOAD
)brace
id|BA_RJT_PAYLOAD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|command_code
id|ULONG
id|command_code
suffix:semicolon
DECL|member|sid
id|ULONG
id|sid
suffix:semicolon
DECL|member|ox_id
id|USHORT
id|ox_id
suffix:semicolon
DECL|member|rx_id
id|USHORT
id|rx_id
suffix:semicolon
DECL|typedef|RRQ_MESSAGE
)brace
id|RRQ_MESSAGE
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|command_code
id|ULONG
id|command_code
suffix:semicolon
DECL|member|vendor
id|UCHAR
id|vendor
suffix:semicolon
DECL|member|explain
id|UCHAR
id|explain
suffix:semicolon
DECL|member|reason
id|UCHAR
id|reason
suffix:semicolon
DECL|member|reserved
id|UCHAR
id|reserved
suffix:semicolon
DECL|typedef|REJECT_MESSAGE
)brace
id|REJECT_MESSAGE
suffix:semicolon
DECL|macro|N_OR_F_PORT
mdefine_line|#define&t;N_OR_F_PORT&t;&t;0x1000
DECL|macro|RANDOM_RELATIVE_OFFSET
mdefine_line|#define RANDOM_RELATIVE_OFFSET&t;0x4000
DECL|macro|CONTINUOSLY_INCREASING
mdefine_line|#define CONTINUOSLY_INCREASING&t;0x8000
DECL|macro|CLASS_VALID
mdefine_line|#define CLASS_VALID&t;&t;0x8000
DECL|macro|INTERMIX_MODE
mdefine_line|#define INTERMIX_MODE&t;&t;0x4000
DECL|macro|TRANSPARENT_STACKED
mdefine_line|#define TRANSPARENT_STACKED&t;0x2000
DECL|macro|LOCKDOWN_STACKED
mdefine_line|#define LOCKDOWN_STACKED&t;0x1000
DECL|macro|SEQ_DELIVERY
mdefine_line|#define SEQ_DELIVERY&t;&t;0x800
DECL|macro|XID_NOT_SUPPORTED
mdefine_line|#define XID_NOT_SUPPORTED&t;0x00
DECL|macro|XID_SUPPORTED
mdefine_line|#define XID_SUPPORTED&t;&t;0x4000
DECL|macro|XID_REQUIRED
mdefine_line|#define XID_REQUIRED&t;&t;0xC000
DECL|macro|ASSOCIATOR_NOT_SUPPORTED
mdefine_line|#define ASSOCIATOR_NOT_SUPPORTED&t;0x00
DECL|macro|ASSOCIATOR_SUPPORTED
mdefine_line|#define ASSOCIATOR_SUPPORTED&t;0x1000
DECL|macro|ASSOCIATOR_REQUIRED
mdefine_line|#define ASSOCIATOR_REQUIRED&t;0x3000
DECL|macro|INIT_ACK0_SUPPORT
mdefine_line|#define&t;INIT_ACK0_SUPPORT&t;0x800
DECL|macro|INIT_ACKN_SUPPORT
mdefine_line|#define INIT_ACKN_SUPPORT&t;0x400
DECL|macro|RECIP_ACK0_SUPPORT
mdefine_line|#define&t;RECIP_ACK0_SUPPORT&t;0x8000
DECL|macro|RECIP_ACKN_SUPPORT
mdefine_line|#define RECIP_ACKN_SUPPORT&t;0x4000
DECL|macro|X_ID_INTERLOCK
mdefine_line|#define X_ID_INTERLOCK&t;&t;0x2000
DECL|macro|ERROR_POLICY
mdefine_line|#define ERROR_POLICY&t;&t;0x1800&t;&t;
singleline_comment|// Error Policy Supported
DECL|macro|ERROR_DISCARD
mdefine_line|#define ERROR_DISCARD&t;&t;0x00&t;&t;
singleline_comment|// Only Discard Supported
DECL|macro|ERROR_DISC_PROCESS
mdefine_line|#define ERROR_DISC_PROCESS&t;0x02&t;&t;
singleline_comment|// Discard and process supported
DECL|macro|NODE_ID
mdefine_line|#define NODE_ID&t;&t;&t;0x01
DECL|macro|IEEE_EXT
mdefine_line|#define IEEE_EXT&t;&t;0x20
singleline_comment|//
singleline_comment|// Categories Supported Per Sequence
singleline_comment|//
DECL|macro|CATEGORIES_PER_SEQUENCE
mdefine_line|#define&t;CATEGORIES_PER_SEQUENCE&t;0x300
DECL|macro|ONE_CATEGORY_SEQUENCE
mdefine_line|#define ONE_CATEGORY_SEQUENCE&t;0x00&t;&t;
singleline_comment|// 1 Category per Sequence
DECL|macro|TWO_CATEGORY_SEQUENCE
mdefine_line|#define TWO_CATEGORY_SEQUENCE&t;0x01&t;&t;
singleline_comment|// 2 Categories per Sequence
DECL|macro|MANY_CATEGORY_SEQUENCE
mdefine_line|#define MANY_CATEGORY_SEQUENCE&t;0x03&t;&t;
singleline_comment|// &gt; 2 Categories/Sequence
r_typedef
r_struct
(brace
DECL|member|initiator_control
id|USHORT
id|initiator_control
suffix:semicolon
DECL|member|service_options
id|USHORT
id|service_options
suffix:semicolon
DECL|member|rx_data_size
id|USHORT
id|rx_data_size
suffix:semicolon
DECL|member|recipient_control
id|USHORT
id|recipient_control
suffix:semicolon
DECL|member|ee_credit
id|USHORT
id|ee_credit
suffix:semicolon
DECL|member|concurrent_sequences
id|USHORT
id|concurrent_sequences
suffix:semicolon
DECL|member|reserved
id|USHORT
id|reserved
suffix:semicolon
DECL|member|open_sequences
id|USHORT
id|open_sequences
suffix:semicolon
DECL|typedef|CLASS_PARAMETERS
)brace
id|CLASS_PARAMETERS
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|login_cmd
id|ULONG
id|login_cmd
suffix:semicolon
singleline_comment|//
singleline_comment|// Common Service Parameters
singleline_comment|//
r_struct
(brace
DECL|member|bb_credit
id|USHORT
id|bb_credit
suffix:semicolon
DECL|member|lowest_ver
id|UCHAR
id|lowest_ver
suffix:semicolon
DECL|member|highest_ver
id|UCHAR
id|highest_ver
suffix:semicolon
DECL|member|bb_rx_size
id|USHORT
id|bb_rx_size
suffix:semicolon
DECL|member|common_features
id|USHORT
id|common_features
suffix:semicolon
DECL|member|rel_offset
id|USHORT
id|rel_offset
suffix:semicolon
DECL|member|concurrent_seq
id|USHORT
id|concurrent_seq
suffix:semicolon
DECL|member|e_d_tov
id|ULONG
id|e_d_tov
suffix:semicolon
DECL|member|cmn_services
)brace
id|cmn_services
suffix:semicolon
singleline_comment|//
singleline_comment|// Port Name
singleline_comment|//
DECL|member|port_name
id|UCHAR
id|port_name
(braket
l_int|8
)braket
suffix:semicolon
singleline_comment|//
singleline_comment|// Node/Fabric Name
singleline_comment|//
DECL|member|node_name
id|UCHAR
id|node_name
(braket
l_int|8
)braket
suffix:semicolon
singleline_comment|//
singleline_comment|// Class 1, 2 and 3 Service Parameters
singleline_comment|//
DECL|member|class1
id|CLASS_PARAMETERS
id|class1
suffix:semicolon
DECL|member|class2
id|CLASS_PARAMETERS
id|class2
suffix:semicolon
DECL|member|class3
id|CLASS_PARAMETERS
id|class3
suffix:semicolon
DECL|member|reserved
id|ULONG
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
singleline_comment|//
singleline_comment|// Vendor Version Level
singleline_comment|//
DECL|member|vendor_id
id|UCHAR
id|vendor_id
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|vendor_version
id|UCHAR
id|vendor_version
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|buffer_size
id|ULONG
id|buffer_size
suffix:semicolon
DECL|member|rxid_start
id|USHORT
id|rxid_start
suffix:semicolon
DECL|member|total_rxids
id|USHORT
id|total_rxids
suffix:semicolon
DECL|typedef|LOGIN_PAYLOAD
)brace
id|LOGIN_PAYLOAD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|cmd
id|ULONG
id|cmd
suffix:semicolon
singleline_comment|// 4 bytes
DECL|member|n_port_identifier
id|UCHAR
id|n_port_identifier
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|reserved
id|UCHAR
id|reserved
suffix:semicolon
DECL|member|port_name
id|UCHAR
id|port_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|LOGOUT_PAYLOAD
)brace
id|LOGOUT_PAYLOAD
suffix:semicolon
singleline_comment|//
singleline_comment|//&t;PRLI Request Service Parameter Defines
singleline_comment|//
DECL|macro|PRLI_ACC
mdefine_line|#define PRLI_ACC&t;&t;&t;0x01
DECL|macro|PRLI_REQ
mdefine_line|#define PRLI_REQ&t;&t;&t;0x02
DECL|macro|ORIG_PROCESS_ASSOC_VALID
mdefine_line|#define ORIG_PROCESS_ASSOC_VALID&t;0x8000
DECL|macro|RESP_PROCESS_ASSOC_VALID
mdefine_line|#define RESP_PROCESS_ASSOC_VALID&t;0x4000
DECL|macro|ESTABLISH_PAIR
mdefine_line|#define ESTABLISH_PAIR&t;&t;&t;0x2000
DECL|macro|DATA_OVERLAY_ALLOWED
mdefine_line|#define DATA_OVERLAY_ALLOWED&t;&t;0x40
DECL|macro|INITIATOR_FUNCTION
mdefine_line|#define&t;INITIATOR_FUNCTION&t;&t;0x20
DECL|macro|TARGET_FUNCTION
mdefine_line|#define&t;TARGET_FUNCTION&t;&t;&t;0x10
DECL|macro|CMD_DATA_MIXED
mdefine_line|#define CMD_DATA_MIXED&t;&t;&t;0x08
DECL|macro|DATA_RESP_MIXED
mdefine_line|#define DATA_RESP_MIXED&t;&t;&t;0x04
DECL|macro|READ_XFER_RDY
mdefine_line|#define READ_XFER_RDY&t;&t;&t;0x02
DECL|macro|WRITE_XFER_RDY
mdefine_line|#define WRITE_XFER_RDY&t;&t;&t;0x01
DECL|macro|RESPONSE_CODE_MASK
mdefine_line|#define RESPONSE_CODE_MASK&t;0xF00
DECL|macro|REQUEST_EXECUTED
mdefine_line|#define REQUEST_EXECUTED&t;0x100
DECL|macro|NO_RESOURCES
mdefine_line|#define NO_RESOURCES&t;&t;0x200
DECL|macro|INIT_NOT_COMPLETE
mdefine_line|#define INIT_NOT_COMPLETE&t;0x300
DECL|macro|IMAGE_DOES_NOT_EXIST
mdefine_line|#define IMAGE_DOES_NOT_EXIST&t;0x400
DECL|macro|BAD_PREDEFINED_COND
mdefine_line|#define BAD_PREDEFINED_COND&t;0x500
DECL|macro|REQ_EXEC_COND
mdefine_line|#define REQ_EXEC_COND&t;&t;0x600
DECL|macro|NO_MULTI_PAGE
mdefine_line|#define NO_MULTI_PAGE&t;&t;0x700
r_typedef
r_struct
(brace
DECL|member|payload_length
id|USHORT
id|payload_length
suffix:semicolon
DECL|member|page_length
id|UCHAR
id|page_length
suffix:semicolon
DECL|member|cmd
id|UCHAR
id|cmd
suffix:semicolon
DECL|member|valid
id|ULONG
id|valid
suffix:semicolon
DECL|member|orig_process_associator
id|ULONG
id|orig_process_associator
suffix:semicolon
DECL|member|resp_process_associator
id|ULONG
id|resp_process_associator
suffix:semicolon
DECL|member|fcp_info
id|ULONG
id|fcp_info
suffix:semicolon
DECL|typedef|PRLI_REQUEST
)brace
id|PRLI_REQUEST
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|payload_length
id|USHORT
id|payload_length
suffix:semicolon
DECL|member|page_length
id|UCHAR
id|page_length
suffix:semicolon
DECL|member|cmd
id|UCHAR
id|cmd
suffix:semicolon
DECL|member|valid
id|ULONG
id|valid
suffix:semicolon
DECL|member|orig_process_associator
id|ULONG
id|orig_process_associator
suffix:semicolon
DECL|member|resp_process_associator
id|ULONG
id|resp_process_associator
suffix:semicolon
DECL|member|reserved
id|ULONG
id|reserved
suffix:semicolon
DECL|typedef|PRLO_REQUEST
)brace
id|PRLO_REQUEST
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|cmd
id|ULONG
id|cmd
suffix:semicolon
DECL|member|hard_address
id|ULONG
id|hard_address
suffix:semicolon
DECL|member|port_name
id|UCHAR
id|port_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|node_name
id|UCHAR
id|node_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|s_id
id|ULONG
id|s_id
suffix:semicolon
DECL|typedef|ADISC_PAYLOAD
)brace
id|ADISC_PAYLOAD
suffix:semicolon
singleline_comment|// J. McCarty&squot;s LINK.H
singleline_comment|//
singleline_comment|//&t;LS_RJT Reason Codes
singleline_comment|//
DECL|macro|INVALID_COMMAND_CODE
mdefine_line|#define INVALID_COMMAND_CODE&t;0x01
DECL|macro|LOGICAL_ERROR
mdefine_line|#define LOGICAL_ERROR&t;&t;0x03
DECL|macro|LOGICAL_BUSY
mdefine_line|#define LOGICAL_BUSY&t;&t;0x05
DECL|macro|PROTOCOL_ERROR
mdefine_line|#define PROTOCOL_ERROR&t;&t;0x07
DECL|macro|UNABLE_TO_PERFORM
mdefine_line|#define UNABLE_TO_PERFORM&t;0x09
DECL|macro|COMMAND_NOT_SUPPORTED
mdefine_line|#define COMMAND_NOT_SUPPORTED&t;0x0B
DECL|macro|LS_VENDOR_UNIQUE
mdefine_line|#define LS_VENDOR_UNIQUE&t;0xFF
singleline_comment|//
singleline_comment|// &t;LS_RJT Reason Codes Explanations
singleline_comment|//
DECL|macro|NO_REASON
mdefine_line|#define NO_REASON&t;&t;0x00
DECL|macro|OPTIONS_ERROR
mdefine_line|#define OPTIONS_ERROR&t;&t;0x01
DECL|macro|INITIATOR_CTL_ERROR
mdefine_line|#define INITIATOR_CTL_ERROR&t;0x03
DECL|macro|RECIPIENT_CTL_ERROR
mdefine_line|#define RECIPIENT_CTL_ERROR&t;0x05
DECL|macro|DATA_FIELD_SIZE_ERROR
mdefine_line|#define DATA_FIELD_SIZE_ERROR&t;0x07
DECL|macro|CONCURRENT_SEQ_ERROR
mdefine_line|#define CONCURRENT_SEQ_ERROR&t;0x09
DECL|macro|CREDIT_ERROR
mdefine_line|#define CREDIT_ERROR&t;&t;0x0B
DECL|macro|INVALID_PORT_NAME
mdefine_line|#define INVALID_PORT_NAME&t;0x0D
DECL|macro|INVALID_NODE_NAME
mdefine_line|#define INVALID_NODE_NAME&t;0x0E
DECL|macro|INVALID_CSP
mdefine_line|#define INVALID_CSP&t;&t;0x0F&t;
singleline_comment|// Invalid Service Parameters
DECL|macro|INVALID_ASSOC_HDR
mdefine_line|#define INVALID_ASSOC_HDR&t;0x11&t;
singleline_comment|// Invalid Association Header
DECL|macro|ASSOC_HDR_REQUIRED
mdefine_line|#define ASSOC_HDR_REQUIRED&t;0x13&t;
singleline_comment|// Association Header Required
DECL|macro|LS_INVALID_S_ID
mdefine_line|#define LS_INVALID_S_ID&t;&t;0x15
DECL|macro|INVALID_OX_RX_ID
mdefine_line|#define INVALID_OX_RX_ID&t;0x17&t;
singleline_comment|// Invalid OX_ID RX_ID Combination
DECL|macro|CMD_IN_PROCESS
mdefine_line|#define CMD_IN_PROCESS&t;&t;0x19
DECL|macro|INVALID_IDENTIFIER
mdefine_line|#define INVALID_IDENTIFIER&t;0x1F&t;
singleline_comment|// Invalid N_PORT Identifier
DECL|macro|INVALID_SEQ_ID
mdefine_line|#define INVALID_SEQ_ID&t;&t;0x21
DECL|macro|ABT_INVALID_XCHNG
mdefine_line|#define ABT_INVALID_XCHNG&t;0x23 &t;
singleline_comment|// Attempt to Abort an invalid Exchange
DECL|macro|ABT_INACTIVE_XCHNG
mdefine_line|#define ABT_INACTIVE_XCHNG&t;0x25 &t;
singleline_comment|// Attempt to Abort an inactive Exchange
DECL|macro|NEED_REC_QUAL
mdefine_line|#define NEED_REC_QUAL&t;&t;0x27&t;
singleline_comment|// Recovery Qualifier required
DECL|macro|NO_LOGIN_RESOURCES
mdefine_line|#define NO_LOGIN_RESOURCES&t;0x29&t;
singleline_comment|// No resources to support login
DECL|macro|NO_DATA
mdefine_line|#define NO_DATA&t;&t;&t;0x2A&t;
singleline_comment|// Unable to supply requested data
DECL|macro|REQUEST_NOT_SUPPORTED
mdefine_line|#define&t;REQUEST_NOT_SUPPORTED&t;0x2C&t;
singleline_comment|// Request Not Supported
singleline_comment|//
singleline_comment|//&t;Link Control Codes
singleline_comment|//
singleline_comment|//
singleline_comment|//&t;P_BSY Action Codes
singleline_comment|//
DECL|macro|SEQUENCE_TERMINATED
mdefine_line|#define SEQUENCE_TERMINATED&t;0x01000000
DECL|macro|SEQUENCE_ACTIVE
mdefine_line|#define SEQUENCE_ACTIVE&t;&t;0x02000000
singleline_comment|//
singleline_comment|//&t;P_BSY Reason Codes
singleline_comment|//
DECL|macro|PHYS_NPORT_BUSY
mdefine_line|#define PHYS_NPORT_BUSY&t;&t;0x010000
DECL|macro|NPORT_RESOURCE_BUSY
mdefine_line|#define NPORT_RESOURCE_BUSY&t;0x020000
singleline_comment|//
singleline_comment|// &t;P_RJT, F_RJT Action Codes
singleline_comment|//
DECL|macro|RETRYABLE_ERROR
mdefine_line|#define RETRYABLE_ERROR&t;&t;0x01000000
DECL|macro|NON_RETRYABLE_ERROR
mdefine_line|#define NON_RETRYABLE_ERROR&t;0x02000000
singleline_comment|//
singleline_comment|// &t;P_RJT, F_RJT Reason Codes
singleline_comment|//
DECL|macro|INVALID_D_ID
mdefine_line|#define INVALID_D_ID&t;&t;0x010000
DECL|macro|INVALID_S_ID
mdefine_line|#define INVALID_S_ID&t;&t;0x020000
DECL|macro|NPORT_NOT_AVAIL_TMP
mdefine_line|#define NPORT_NOT_AVAIL_TMP&t;0x030000
DECL|macro|NPORT_NOT_AVAIL_PERM
mdefine_line|#define NPORT_NOT_AVAIL_PERM&t;0x040000
DECL|macro|CLASS_NOT_SUPPORTED
mdefine_line|#define CLASS_NOT_SUPPORTED&t;0x050000
DECL|macro|USAGE_ERROR
mdefine_line|#define USAGE_ERROR&t;&t;0x060000
DECL|macro|TYPE_NOT_SUPPORTED
mdefine_line|#define TYPE_NOT_SUPPORTED&t;0x070000
DECL|macro|INVAL_LINK_CONTROL
mdefine_line|#define INVAL_LINK_CONTROL&t;0x080000
DECL|macro|INVAL_R_CTL
mdefine_line|#define INVAL_R_CTL&t;&t;0x090000
DECL|macro|INVAL_F_CTL
mdefine_line|#define INVAL_F_CTL&t;&t;0x0A0000
DECL|macro|INVAL_OX_ID
mdefine_line|#define INVAL_OX_ID&t;&t;0x0B0000
DECL|macro|INVAL_RX_ID
mdefine_line|#define INVAL_RX_ID&t;&t;0x0C0000
DECL|macro|INVAL_SEQ_ID
mdefine_line|#define INVAL_SEQ_ID&t;&t;0x0D0000
DECL|macro|INVAL_DF_CTL
mdefine_line|#define INVAL_DF_CTL&t;&t;0x0E0000
DECL|macro|INVAL_SEQ_CNT
mdefine_line|#define INVAL_SEQ_CNT&t;&t;0x0F0000
DECL|macro|INVAL_PARAMS
mdefine_line|#define INVAL_PARAMS&t;&t;0x100000
DECL|macro|EXCHANGE_ERROR
mdefine_line|#define EXCHANGE_ERROR&t;&t;0x110000
DECL|macro|LS_PROTOCOL_ERROR
mdefine_line|#define LS_PROTOCOL_ERROR&t;0x120000
DECL|macro|INCORRECT_LENGTH
mdefine_line|#define INCORRECT_LENGTH&t;0x130000
DECL|macro|UNEXPECTED_ACK
mdefine_line|#define UNEXPECTED_ACK&t;&t;0x140000
DECL|macro|LOGIN_REQ
mdefine_line|#define LOGIN_REQ&t;&t;0x160000
DECL|macro|EXCESSIVE_SEQ
mdefine_line|#define EXCESSIVE_SEQ&t;&t;0x170000
DECL|macro|NO_EXCHANGE
mdefine_line|#define NO_EXCHANGE&t;&t;0x180000
DECL|macro|SEC_HDR_NOT_SUPPORTED
mdefine_line|#define SEC_HDR_NOT_SUPPORTED&t;0x190000
DECL|macro|NO_FABRIC
mdefine_line|#define NO_FABRIC&t;&t;0x1A0000
DECL|macro|P_VENDOR_UNIQUE
mdefine_line|#define P_VENDOR_UNIQUE&t;&t;0xFF0000
singleline_comment|//
singleline_comment|// &t;BA_RJT Reason Codes
singleline_comment|//
DECL|macro|BA_INVALID_COMMAND
mdefine_line|#define BA_INVALID_COMMAND&t;0x00010000
DECL|macro|BA_LOGICAL_ERROR
mdefine_line|#define BA_LOGICAL_ERROR&t;0x00030000
DECL|macro|BA_LOGICAL_BUSY
mdefine_line|#define BA_LOGICAL_BUSY&t;&t;0x00050000
DECL|macro|BA_PROTOCOL_ERROR
mdefine_line|#define BA_PROTOCOL_ERROR&t;0x00070000
DECL|macro|BA_UNABLE_TO_PERFORM
mdefine_line|#define BA_UNABLE_TO_PERFORM&t;0x00090000
singleline_comment|//
singleline_comment|// &t;BA_RJT Reason Explanation Codes
singleline_comment|//
DECL|macro|BA_NO_REASON
mdefine_line|#define BA_NO_REASON&t;&t;0x00000000
DECL|macro|BA_INVALID_OX_RX
mdefine_line|#define BA_INVALID_OX_RX&t;0x00000300
DECL|macro|BA_SEQUENCE_ABORTED
mdefine_line|#define BA_SEQUENCE_ABORTED&t;0x00000500
macro_line|#endif /* CPQFCTSSTRUCTS_H&t;*/
eof
