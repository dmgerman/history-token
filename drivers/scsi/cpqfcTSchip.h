multiline_comment|/* Copyright(c) 2000, Compaq Computer Corporation &n; * Fibre Channel Host Bus Adapter &n; * 64-bit, 66MHz PCI &n; * Originally developed and tested on:&n; * (front): [chip] Tachyon TS HPFC-5166A/1.2  L2C1090 ...&n; *          SP# P225CXCBFIEL6T, Rev XC&n; *          SP# 161290-001, Rev XD&n; * (back): Board No. 010008-001 A/W Rev X5, FAB REV X5&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; * Written by Don Zimmerman&n;*/
macro_line|#ifndef CPQFCTSCHIP_H
DECL|macro|CPQFCTSCHIP_H
mdefine_line|#define CPQFCTSCHIP_H
macro_line|#ifndef TACHYON_CHIP_INC
singleline_comment|// FC-PH (Physical) specification levels for Login payloads
singleline_comment|// NOTE: These are NOT strictly complied with by any FC vendors
DECL|macro|FC_PH42
mdefine_line|#define FC_PH42&t;&t;&t;0x08
DECL|macro|FC_PH43
mdefine_line|#define FC_PH43&t;&t;&t;0x09
DECL|macro|FC_PH3
mdefine_line|#define FC_PH3&t;&t;&t;0x20
DECL|macro|TACHLITE_TS_RX_SIZE
mdefine_line|#define TACHLITE_TS_RX_SIZE     1024  
singleline_comment|// max inbound frame size
singleline_comment|// &quot;I&quot; prefix is for Include
DECL|macro|IVENDID
mdefine_line|#define IVENDID    0x00  
singleline_comment|// word
DECL|macro|IDEVID
mdefine_line|#define IDEVID     0x02
DECL|macro|ITLCFGCMD
mdefine_line|#define ITLCFGCMD 0x04
DECL|macro|IMEMBASE
mdefine_line|#define IMEMBASE   0x18    
singleline_comment|// Tachyon
DECL|macro|ITLMEMBASE
mdefine_line|#define ITLMEMBASE   0x1C  
singleline_comment|// Tachlite
DECL|macro|IIOBASEL
mdefine_line|#define IIOBASEL   0x10    
singleline_comment|// Tachyon I/O base address, lower 256 bytes
DECL|macro|IIOBASEU
mdefine_line|#define IIOBASEU   0x14    
singleline_comment|// Tachyon I/O base address, upper 256 bytes
DECL|macro|ITLIOBASEL
mdefine_line|#define ITLIOBASEL   0x14  
singleline_comment|// TachLite I/O base address, lower 256 bytes
DECL|macro|ITLIOBASEU
mdefine_line|#define ITLIOBASEU   0x18  
singleline_comment|// TachLite I/O base address, upper 256 bytes
DECL|macro|ITLRAMBASE
mdefine_line|#define ITLRAMBASE   0x20  
singleline_comment|// TL on-board RAM start
DECL|macro|ISROMBASE
mdefine_line|#define ISROMBASE  0x24
DECL|macro|IROMBASE
mdefine_line|#define IROMBASE   0x30
DECL|macro|ICFGCMD
mdefine_line|#define ICFGCMD    0x04    
singleline_comment|// PCI config - PCI config access (word)
DECL|macro|ICFGSTAT
mdefine_line|#define ICFGSTAT   0x06    
singleline_comment|// PCI status (R - word)
DECL|macro|IRCTR_WCTR
mdefine_line|#define IRCTR_WCTR 0x1F2   
singleline_comment|// ROM control / pre-fetch wait counter
DECL|macro|IPCIMCTR
mdefine_line|#define IPCIMCTR   0x1F3   
singleline_comment|// PCI master control register
DECL|macro|IINTPEND
mdefine_line|#define IINTPEND   0x1FD   
singleline_comment|// Interrupt pending (I/O Upper - Tachyon &amp; TL)
DECL|macro|IINTEN
mdefine_line|#define IINTEN     0x1FE   
singleline_comment|// Interrupt enable  (I/O Upper - Tachyon &amp; TL)
DECL|macro|IINTSTAT
mdefine_line|#define IINTSTAT   0x1FF   
singleline_comment|// Interrupt status  (I/O Upper - Tachyon &amp; TL)
DECL|macro|IMQ_BASE
mdefine_line|#define IMQ_BASE            0x80
DECL|macro|IMQ_LENGTH
mdefine_line|#define IMQ_LENGTH          0x84
DECL|macro|IMQ_CONSUMER_INDEX
mdefine_line|#define IMQ_CONSUMER_INDEX  0x88
DECL|macro|IMQ_PRODUCER_INDEX
mdefine_line|#define IMQ_PRODUCER_INDEX  0x8C   
singleline_comment|// Tach copies its INDX to bits 0-7 of value
multiline_comment|/*&n;// IOBASE UPPER&n;#define SFSBQ_BASE            0x00   // single-frame sequences&n;#define SFSBQ_LENGTH          0x04&n;#define SFSBQ_PRODUCER_INDEX  0x08&n;#define SFSBQ_CONSUMER_INDEX  0x0C   // (R)&n;#define SFS_BUFFER_LENGTH     0X10&n;                              // SCSI-FCP hardware assists&n;#define SEST_BASE             0x40   // SSCI Exchange State Table&n;#define SEST_LENGTH           0x44&n;#define SCSI_BUFFER_LENGTH    0x48&n;#define SEST_LINKED_LIST      0x4C&n;&n;#define TACHYON_My_ID         0x6C&n;#define TACHYON_CONFIGURATION 0x84   // (R/W) reset val 2&n;#define TACHYON_CONTROL       0x88&n;#define TACHYON_STATUS        0x8C   // (R)&n;#define TACHYON_FLUSH_SEST    0x90   // (R/W)&n;#define TACHYON_EE_CREDIT_TMR 0x94   // (R)&n;#define TACHYON_BB_CREDIT_TMR 0x98   // (R)&n;#define TACHYON_RCV_FRAME_ERR 0x9C   // (R)&n;#define FRAME_MANAGER_CONFIG  0xC0   // (R/W)&n;#define FRAME_MANAGER_CONTROL 0xC4&n;#define FRAME_MANAGER_STATUS  0xC8   // (R)&n;#define FRAME_MANAGER_ED_TOV  0xCC&n;#define FRAME_MANAGER_LINK_ERR1 0xD0   // (R)&n;#define FRAME_MANAGER_LINK_ERR2 0xD4   // (R)&n;#define FRAME_MANAGER_TIMEOUT2  0xD8   // (W)&n;#define FRAME_MANAGER_BB_CREDIT 0xDC   // (R)&n;#define FRAME_MANAGER_WWN_HI    0xE0   // (R/W)&n;#define FRAME_MANAGER_WWN_LO    0xE4   // (R/W)&n;#define FRAME_MANAGER_RCV_AL_PA 0xE8   // (R)&n;#define FRAME_MANAGER_PRIMITIVE 0xEC   // {K28.5} byte1 byte2 byte3&n;*/
DECL|macro|TL_MEM_ERQ_BASE
mdefine_line|#define TL_MEM_ERQ_BASE                    0x0 
singleline_comment|//ERQ Base
DECL|macro|TL_IO_ERQ_BASE
mdefine_line|#define TL_IO_ERQ_BASE                     0x0 
singleline_comment|//ERQ base
DECL|macro|TL_MEM_ERQ_LENGTH
mdefine_line|#define TL_MEM_ERQ_LENGTH                  0x4 
singleline_comment|//ERQ Length
DECL|macro|TL_IO_ERQ_LENGTH
mdefine_line|#define TL_IO_ERQ_LENGTH                   0x4 
singleline_comment|//ERQ Length
DECL|macro|TL_MEM_ERQ_PRODUCER_INDEX
mdefine_line|#define TL_MEM_ERQ_PRODUCER_INDEX          0x8 
singleline_comment|//ERQ Producer Index  register
DECL|macro|TL_IO_ERQ_PRODUCER_INDEX
mdefine_line|#define TL_IO_ERQ_PRODUCER_INDEX           0x8 
singleline_comment|//ERQ Producer Index  register
DECL|macro|TL_MEM_ERQ_CONSUMER_INDEX_ADR
mdefine_line|#define TL_MEM_ERQ_CONSUMER_INDEX_ADR 0xC 
singleline_comment|//ERQ Consumer Index address register
DECL|macro|TL_IO_ERQ_CONSUMER_INDEX_ADR
mdefine_line|#define TL_IO_ERQ_CONSUMER_INDEX_ADR  0xC 
singleline_comment|//ERQ Consumer Index address register
DECL|macro|TL_MEM_ERQ_CONSUMER_INDEX
mdefine_line|#define TL_MEM_ERQ_CONSUMER_INDEX     0xC 
singleline_comment|//ERQ Consumer Index 
DECL|macro|TL_IO_ERQ_CONSUMER_INDEX
mdefine_line|#define TL_IO_ERQ_CONSUMER_INDEX      0xC 
singleline_comment|//ERQ Consumer Index 
DECL|macro|TL_MEM_SFQ_BASE
mdefine_line|#define TL_MEM_SFQ_BASE               0x50 
singleline_comment|//SFQ Base
DECL|macro|TL_IO_SFQ_BASE
mdefine_line|#define TL_IO_SFQ_BASE                0x50 
singleline_comment|//SFQ base
DECL|macro|TL_MEM_SFQ_LENGTH
mdefine_line|#define TL_MEM_SFQ_LENGTH             0x54 
singleline_comment|//SFQ Length
DECL|macro|TL_IO_SFQ_LENGTH
mdefine_line|#define TL_IO_SFQ_LENGTH              0x54 
singleline_comment|//SFQ Length
DECL|macro|TL_MEM_SFQ_CONSUMER_INDEX
mdefine_line|#define TL_MEM_SFQ_CONSUMER_INDEX     0x58 
singleline_comment|//SFQ Consumer Index
DECL|macro|TL_IO_SFQ_CONSUMER_INDEX
mdefine_line|#define TL_IO_SFQ_CONSUMER_INDEX      0x58 
singleline_comment|//SFQ Consumer Index
DECL|macro|TL_MEM_IMQ_BASE
mdefine_line|#define TL_MEM_IMQ_BASE               0x80 
singleline_comment|//IMQ Base
DECL|macro|TL_IO_IMQ_BASE
mdefine_line|#define TL_IO_IMQ_BASE                0x80 
singleline_comment|//IMQ base
DECL|macro|TL_MEM_IMQ_LENGTH
mdefine_line|#define TL_MEM_IMQ_LENGTH             0x84 
singleline_comment|//IMQ Length
DECL|macro|TL_IO_IMQ_LENGTH
mdefine_line|#define TL_IO_IMQ_LENGTH              0x84 
singleline_comment|//IMQ Length
DECL|macro|TL_MEM_IMQ_CONSUMER_INDEX
mdefine_line|#define TL_MEM_IMQ_CONSUMER_INDEX     0x88 
singleline_comment|//IMQ Consumer Index
DECL|macro|TL_IO_IMQ_CONSUMER_INDEX
mdefine_line|#define TL_IO_IMQ_CONSUMER_INDEX      0x88 
singleline_comment|//IMQ Consumer Index
DECL|macro|TL_MEM_IMQ_PRODUCER_INDEX_ADR
mdefine_line|#define TL_MEM_IMQ_PRODUCER_INDEX_ADR 0x8C 
singleline_comment|//IMQ Producer Index address register
DECL|macro|TL_IO_IMQ_PRODUCER_INDEX_ADR
mdefine_line|#define TL_IO_IMQ_PRODUCER_INDEX_ADR  0x8C 
singleline_comment|//IMQ Producer Index address register
DECL|macro|TL_MEM_SEST_BASE
mdefine_line|#define TL_MEM_SEST_BASE              0x140 
singleline_comment|//SFQ Base
DECL|macro|TL_IO_SEST_BASE
mdefine_line|#define TL_IO_SEST_BASE               0x40 
singleline_comment|//SFQ base
DECL|macro|TL_MEM_SEST_LENGTH
mdefine_line|#define TL_MEM_SEST_LENGTH            0x144 
singleline_comment|//SFQ Length
DECL|macro|TL_IO_SEST_LENGTH
mdefine_line|#define TL_IO_SEST_LENGTH             0x44 
singleline_comment|//SFQ Length
DECL|macro|TL_MEM_SEST_LINKED_LIST
mdefine_line|#define TL_MEM_SEST_LINKED_LIST       0x14C
DECL|macro|TL_MEM_SEST_SG_PAGE
mdefine_line|#define TL_MEM_SEST_SG_PAGE           0x168  
singleline_comment|// Extended Scatter/Gather page size
DECL|macro|TL_MEM_TACH_My_ID
mdefine_line|#define TL_MEM_TACH_My_ID             0x16C
DECL|macro|TL_IO_TACH_My_ID
mdefine_line|#define TL_IO_TACH_My_ID              0x6C 
singleline_comment|//My AL_PA ID
DECL|macro|TL_MEM_TACH_CONFIG
mdefine_line|#define TL_MEM_TACH_CONFIG            0x184 
singleline_comment|//Tachlite Configuration register
DECL|macro|TL_IO_CONFIG
mdefine_line|#define TL_IO_CONFIG                  0x84 
singleline_comment|//Tachlite Configuration register
DECL|macro|TL_MEM_TACH_CONTROL
mdefine_line|#define TL_MEM_TACH_CONTROL           0x188 
singleline_comment|//Tachlite Control register
DECL|macro|TL_IO_CTR
mdefine_line|#define TL_IO_CTR                     0x88 
singleline_comment|//Tachlite Control register
DECL|macro|TL_MEM_TACH_STATUS
mdefine_line|#define TL_MEM_TACH_STATUS            0x18C 
singleline_comment|//Tachlite Status register
DECL|macro|TL_IO_STAT
mdefine_line|#define TL_IO_STAT                    0x8C 
singleline_comment|//Tachlite Status register
DECL|macro|TL_MEM_FM_CONFIG
mdefine_line|#define TL_MEM_FM_CONFIG        0x1C0 
singleline_comment|//Frame Manager Configuration register
DECL|macro|TL_IO_FM_CONFIG
mdefine_line|#define TL_IO_FM_CONFIG         0xC0 
singleline_comment|//Frame Manager Configuration register
DECL|macro|TL_MEM_FM_CONTROL
mdefine_line|#define TL_MEM_FM_CONTROL       0x1C4 
singleline_comment|//Frame Manager Control
DECL|macro|TL_IO_FM_CTL
mdefine_line|#define TL_IO_FM_CTL            0xC4 
singleline_comment|//Frame Manager Control
DECL|macro|TL_MEM_FM_STATUS
mdefine_line|#define TL_MEM_FM_STATUS        0x1C8 
singleline_comment|//Frame Manager Status
DECL|macro|TL_IO_FM_STAT
mdefine_line|#define TL_IO_FM_STAT           0xC8 
singleline_comment|//Frame Manager Status
DECL|macro|TL_MEM_FM_LINK_STAT1
mdefine_line|#define TL_MEM_FM_LINK_STAT1    0x1D0 
singleline_comment|//Frame Manager Link Status 1
DECL|macro|TL_IO_FM_LINK_STAT1
mdefine_line|#define TL_IO_FM_LINK_STAT1     0xD0 
singleline_comment|//Frame Manager Link Status 1
DECL|macro|TL_MEM_FM_LINK_STAT2
mdefine_line|#define TL_MEM_FM_LINK_STAT2    0x1D4 
singleline_comment|//Frame Manager Link Status 2
DECL|macro|TL_IO_FM_LINK_STAT2
mdefine_line|#define TL_IO_FM_LINK_STAT2     0xD4 
singleline_comment|//Frame Manager Link Status 2
DECL|macro|TL_MEM_FM_TIMEOUT2
mdefine_line|#define TL_MEM_FM_TIMEOUT2      0x1D8   
singleline_comment|// (W)
DECL|macro|TL_MEM_FM_BB_CREDIT0
mdefine_line|#define TL_MEM_FM_BB_CREDIT0    0x1DC
DECL|macro|TL_MEM_FM_WWN_HI
mdefine_line|#define TL_MEM_FM_WWN_HI        0x1E0 
singleline_comment|//Frame Manager World Wide Name High
DECL|macro|TL_IO_FM_WWN_HI
mdefine_line|#define TL_IO_FM_WWN_HI         0xE0 
singleline_comment|//Frame Manager World Wide Name High
DECL|macro|TL_MEM_FM_WWN_LO
mdefine_line|#define TL_MEM_FM_WWN_LO        0x1E4 
singleline_comment|//Frame Manager World Wide Name LOW
DECL|macro|TL_IO_FM_WWN_LO
mdefine_line|#define TL_IO_FM_WWN_LO         0xE4 
singleline_comment|//Frame Manager World Wide Name Low
DECL|macro|TL_MEM_FM_RCV_AL_PA
mdefine_line|#define TL_MEM_FM_RCV_AL_PA     0x1E8 
singleline_comment|//Frame Manager AL_PA Received register
DECL|macro|TL_IO_FM_ALPA
mdefine_line|#define TL_IO_FM_ALPA           0xE8 
singleline_comment|//Frame Manager AL_PA Received register
DECL|macro|TL_MEM_FM_ED_TOV
mdefine_line|#define TL_MEM_FM_ED_TOV           0x1CC
DECL|macro|TL_IO_ROMCTR
mdefine_line|#define TL_IO_ROMCTR            0xFA 
singleline_comment|//TL PCI ROM Control Register
DECL|macro|TL_IO_PCIMCTR
mdefine_line|#define TL_IO_PCIMCTR           0xFB 
singleline_comment|//TL PCI Master Control Register
DECL|macro|TL_IO_SOFTRST
mdefine_line|#define TL_IO_SOFTRST           0xFC 
singleline_comment|//Tachlite Configuration register
DECL|macro|TL_MEM_SOFTRST
mdefine_line|#define TL_MEM_SOFTRST          0x1FC 
singleline_comment|//Tachlite Configuration register
singleline_comment|// completion message types (bit 8 set means Interrupt generated)
singleline_comment|// CM_Type
DECL|macro|OUTBOUND_COMPLETION
mdefine_line|#define OUTBOUND_COMPLETION        0
DECL|macro|ERROR_IDLE_COMPLETION
mdefine_line|#define ERROR_IDLE_COMPLETION   0x01
DECL|macro|OUT_HI_PRI_COMPLETION
mdefine_line|#define OUT_HI_PRI_COMPLETION   0x01
DECL|macro|INBOUND_MFS_COMPLETION
mdefine_line|#define INBOUND_MFS_COMPLETION  0x02
DECL|macro|INBOUND_000_COMPLETION
mdefine_line|#define INBOUND_000_COMPLETION  0x03
DECL|macro|INBOUND_SFS_COMPLETION
mdefine_line|#define INBOUND_SFS_COMPLETION  0x04  
singleline_comment|// Tachyon &amp; TachLite
DECL|macro|ERQ_FROZEN_COMPLETION
mdefine_line|#define ERQ_FROZEN_COMPLETION   0x06  
singleline_comment|// TachLite
DECL|macro|INBOUND_C1_TIMEOUT
mdefine_line|#define INBOUND_C1_TIMEOUT      0x05
DECL|macro|INBOUND_BUSIED_FRAME
mdefine_line|#define INBOUND_BUSIED_FRAME    0x06
DECL|macro|SFS_BUF_WARN
mdefine_line|#define SFS_BUF_WARN            0x07
DECL|macro|FCP_FROZEN_COMPLETION
mdefine_line|#define FCP_FROZEN_COMPLETION   0x07  
singleline_comment|// TachLite
DECL|macro|MFS_BUF_WARN
mdefine_line|#define MFS_BUF_WARN            0x08
DECL|macro|IMQ_BUF_WARN
mdefine_line|#define IMQ_BUF_WARN            0x09
DECL|macro|FRAME_MGR_INTERRUPT
mdefine_line|#define FRAME_MGR_INTERRUPT     0x0A
DECL|macro|READ_STATUS
mdefine_line|#define READ_STATUS             0x0B
DECL|macro|INBOUND_SCSI_DATA_COMPLETION
mdefine_line|#define INBOUND_SCSI_DATA_COMPLETION  0x0C
DECL|macro|INBOUND_FCP_XCHG_COMPLETION
mdefine_line|#define INBOUND_FCP_XCHG_COMPLETION   0x0C  
singleline_comment|// TachLite
DECL|macro|INBOUND_SCSI_DATA_COMMAND
mdefine_line|#define INBOUND_SCSI_DATA_COMMAND     0x0D
DECL|macro|BAD_SCSI_FRAME
mdefine_line|#define BAD_SCSI_FRAME                0x0E
DECL|macro|INB_SCSI_STATUS_COMPLETION
mdefine_line|#define INB_SCSI_STATUS_COMPLETION    0x0F
DECL|macro|BUFFER_PROCESSED_COMPLETION
mdefine_line|#define BUFFER_PROCESSED_COMPLETION   0x11
singleline_comment|// FC-AL (Tachyon) Loop Port State Machine defs
singleline_comment|// (loop &quot;Up&quot; states)
DECL|macro|MONITORING
mdefine_line|#define MONITORING 0x0
DECL|macro|ARBITRATING
mdefine_line|#define ARBITRATING 0x1
DECL|macro|ARBITRAT_WON
mdefine_line|#define ARBITRAT_WON 0x2
DECL|macro|OPEN
mdefine_line|#define OPEN 0x3
DECL|macro|OPENED
mdefine_line|#define OPENED 0x4
DECL|macro|XMITTD_CLOSE
mdefine_line|#define XMITTD_CLOSE 0x5
DECL|macro|RCVD_CLOSE
mdefine_line|#define RCVD_CLOSE 0x6
DECL|macro|TRANSFER
mdefine_line|#define TRANSFER 0x7
singleline_comment|// (loop &quot;Down&quot; states)
DECL|macro|INITIALIZING
mdefine_line|#define INITIALIZING 0x8
DECL|macro|O_I_INIT
mdefine_line|#define O_I_INIT 0x9
DECL|macro|O_I_PROTOCOL
mdefine_line|#define O_I_PROTOCOL 0xa
DECL|macro|O_I_LIP_RCVD
mdefine_line|#define O_I_LIP_RCVD 0xb
DECL|macro|HOST_CONTROL
mdefine_line|#define HOST_CONTROL 0xc
DECL|macro|LOOP_FAIL
mdefine_line|#define LOOP_FAIL 0xd
singleline_comment|// (no 0xe)
DECL|macro|OLD_PORT
mdefine_line|#define OLD_PORT 0xf
DECL|macro|TACHYON_CHIP_INC
mdefine_line|#define TACHYON_CHIP_INC
macro_line|#endif
macro_line|#endif /* CPQFCTSCHIP_H */
eof
