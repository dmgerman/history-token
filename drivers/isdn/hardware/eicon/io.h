multiline_comment|/*&n; *&n;  Copyright (c) Eicon Networks, 2002.&n; *&n;  This source file is supplied for the use with&n;  Eicon Networks range of DIVA Server Adapters.&n; *&n;  Eicon File Revision :    2.1&n; *&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2, or (at your option)&n;  any later version.&n; *&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY&n;  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n;  See the GNU General Public License for more details.&n; *&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifndef __DIVA_XDI_COMMON_IO_H_INC__ /* { */
DECL|macro|__DIVA_XDI_COMMON_IO_H_INC__
mdefine_line|#define __DIVA_XDI_COMMON_IO_H_INC__
multiline_comment|/*&n; maximum = 16 adapters&n; */
DECL|macro|DI_MAX_LINKS
mdefine_line|#define DI_MAX_LINKS    MAX_ADAPTER
DECL|macro|ISDN_MAX_NUM_LEN
mdefine_line|#define ISDN_MAX_NUM_LEN 60
multiline_comment|/* --------------------------------------------------------------------------&n;  structure for quadro card management (obsolete for&n;  systems that do provide per card load event)&n;  -------------------------------------------------------------------------- */
r_typedef
r_struct
(brace
DECL|member|Num
id|dword
id|Num
suffix:semicolon
DECL|member|DeviceName
id|DEVICE_NAME
id|DeviceName
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|QuadroAdapter
id|PISDN_ADAPTER
id|QuadroAdapter
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|ADAPTER_LIST_ENTRY
DECL|typedef|PADAPTER_LIST_ENTRY
)brace
id|ADAPTER_LIST_ENTRY
comma
op_star
id|PADAPTER_LIST_ENTRY
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;  Special OS memory support structures&n;  -------------------------------------------------------------------------- */
DECL|macro|MAX_MAPPED_ENTRIES
mdefine_line|#define MAX_MAPPED_ENTRIES 8
r_typedef
r_struct
(brace
DECL|member|Address
r_void
op_star
id|Address
suffix:semicolon
DECL|member|Length
id|dword
id|Length
suffix:semicolon
DECL|typedef|ADAPTER_MEMORY
)brace
id|ADAPTER_MEMORY
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;  Configuration of XDI clients carried by XDI&n;  -------------------------------------------------------------------------- */
DECL|macro|DIVA_XDI_CAPI_CFG_1_DYNAMIC_L1_ON
mdefine_line|#define DIVA_XDI_CAPI_CFG_1_DYNAMIC_L1_ON      0x01
DECL|macro|DIVA_XDI_CAPI_CFG_1_GROUP_POPTIMIZATION_ON
mdefine_line|#define DIVA_XDI_CAPI_CFG_1_GROUP_POPTIMIZATION_ON 0x02
DECL|struct|_diva_xdi_capi_cfg
r_typedef
r_struct
id|_diva_xdi_capi_cfg
(brace
DECL|member|cfg_1
id|byte
id|cfg_1
suffix:semicolon
DECL|typedef|diva_xdi_capi_cfg_t
)brace
id|diva_xdi_capi_cfg_t
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;  Main data structure kept per adapter&n;  -------------------------------------------------------------------------- */
DECL|struct|_ISDN_ADAPTER
r_struct
id|_ISDN_ADAPTER
(brace
DECL|member|DIRequest
r_void
(paren
op_star
id|DIRequest
)paren
(paren
id|PISDN_ADAPTER
comma
id|ENTITY
op_star
)paren
suffix:semicolon
DECL|member|State
r_int
id|State
suffix:semicolon
multiline_comment|/* from NT4 1.srv, a good idea, but  a poor achievment */
DECL|member|Initialized
r_int
id|Initialized
suffix:semicolon
DECL|member|RegisteredWithDidd
r_int
id|RegisteredWithDidd
suffix:semicolon
DECL|member|Unavailable
r_int
id|Unavailable
suffix:semicolon
multiline_comment|/* callback function possible? */
DECL|member|ResourcesClaimed
r_int
id|ResourcesClaimed
suffix:semicolon
DECL|member|PnpBiosConfigUsed
r_int
id|PnpBiosConfigUsed
suffix:semicolon
DECL|member|Logging
id|dword
id|Logging
suffix:semicolon
DECL|member|features
id|dword
id|features
suffix:semicolon
DECL|member|ProtocolIdString
r_char
id|ProtocolIdString
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/*&n;  remember mapped memory areas&n; */
DECL|member|MappedMemory
id|ADAPTER_MEMORY
id|MappedMemory
(braket
id|MAX_MAPPED_ENTRIES
)braket
suffix:semicolon
DECL|member|Properties
id|CARD_PROPERTIES
id|Properties
suffix:semicolon
DECL|member|cardType
id|dword
id|cardType
suffix:semicolon
DECL|member|protocol_id
id|dword
id|protocol_id
suffix:semicolon
multiline_comment|/* configured protocol identifier */
DECL|member|protocol_name
r_char
id|protocol_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* readable name of protocol */
DECL|member|BusType
id|dword
id|BusType
suffix:semicolon
DECL|member|BusNumber
id|dword
id|BusNumber
suffix:semicolon
DECL|member|slotNumber
id|dword
id|slotNumber
suffix:semicolon
DECL|member|slotId
id|dword
id|slotId
suffix:semicolon
DECL|member|ControllerNumber
id|dword
id|ControllerNumber
suffix:semicolon
multiline_comment|/* for QUADRO cards only */
DECL|member|MultiMaster
id|PISDN_ADAPTER
id|MultiMaster
suffix:semicolon
multiline_comment|/* for 4-BRI card only - use MultiMaster or QuadroList */
DECL|member|QuadroList
id|PADAPTER_LIST_ENTRY
id|QuadroList
suffix:semicolon
multiline_comment|/* for QUADRO card  only */
DECL|member|DeviceObject
id|PDEVICE_OBJECT
id|DeviceObject
suffix:semicolon
DECL|member|DeviceId
id|dword
id|DeviceId
suffix:semicolon
DECL|member|irq_info
id|diva_os_adapter_irq_info_t
id|irq_info
suffix:semicolon
DECL|member|IrqCount
id|dword
r_volatile
id|IrqCount
suffix:semicolon
DECL|member|trapped
r_int
id|trapped
suffix:semicolon
DECL|member|DspCodeBaseAddr
id|dword
id|DspCodeBaseAddr
suffix:semicolon
DECL|member|MaxDspCodeSize
id|dword
id|MaxDspCodeSize
suffix:semicolon
DECL|member|downloadAddr
id|dword
id|downloadAddr
suffix:semicolon
DECL|member|DspCodeBaseAddrTable
id|dword
id|DspCodeBaseAddrTable
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* add. for MultiMaster */
DECL|member|MaxDspCodeSizeTable
id|dword
id|MaxDspCodeSizeTable
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* add. for MultiMaster */
DECL|member|downloadAddrTable
id|dword
id|downloadAddrTable
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* add. for MultiMaster */
DECL|member|MemoryBase
id|dword
id|MemoryBase
suffix:semicolon
DECL|member|MemorySize
id|dword
id|MemorySize
suffix:semicolon
DECL|member|Address
id|byte
id|__iomem
op_star
id|Address
suffix:semicolon
DECL|member|Config
id|byte
id|__iomem
op_star
id|Config
suffix:semicolon
DECL|member|Control
id|byte
id|__iomem
op_star
id|Control
suffix:semicolon
DECL|member|reset
id|byte
id|__iomem
op_star
id|reset
suffix:semicolon
DECL|member|port
id|byte
id|__iomem
op_star
id|port
suffix:semicolon
DECL|member|ram
id|byte
id|__iomem
op_star
id|ram
suffix:semicolon
DECL|member|cfg
id|byte
id|__iomem
op_star
id|cfg
suffix:semicolon
DECL|member|prom
id|byte
id|__iomem
op_star
id|prom
suffix:semicolon
DECL|member|ctlReg
id|byte
id|__iomem
op_star
id|ctlReg
suffix:semicolon
DECL|member|pcm
r_struct
id|pc_maint
op_star
id|pcm
suffix:semicolon
DECL|member|os_name
id|diva_os_dependent_devica_name_t
id|os_name
suffix:semicolon
DECL|member|Name
id|byte
id|Name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|serialNo
id|dword
id|serialNo
suffix:semicolon
DECL|member|ANum
id|dword
id|ANum
suffix:semicolon
DECL|member|ArchiveType
id|dword
id|ArchiveType
suffix:semicolon
multiline_comment|/* ARCHIVE_TYPE_NONE ..._SINGLE ..._USGEN ..._MULTI */
DECL|member|ProtocolSuffix
r_char
op_star
id|ProtocolSuffix
suffix:semicolon
multiline_comment|/* internal protocolfile table */
DECL|member|Archive
r_char
id|Archive
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|Protocol
r_char
id|Protocol
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|AddDownload
r_char
id|AddDownload
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Dsp- or other additional download files */
DECL|member|Oad1
r_char
id|Oad1
(braket
id|ISDN_MAX_NUM_LEN
)braket
suffix:semicolon
DECL|member|Osa1
r_char
id|Osa1
(braket
id|ISDN_MAX_NUM_LEN
)braket
suffix:semicolon
DECL|member|Oad2
r_char
id|Oad2
(braket
id|ISDN_MAX_NUM_LEN
)braket
suffix:semicolon
DECL|member|Osa2
r_char
id|Osa2
(braket
id|ISDN_MAX_NUM_LEN
)braket
suffix:semicolon
DECL|member|Spid1
r_char
id|Spid1
(braket
id|ISDN_MAX_NUM_LEN
)braket
suffix:semicolon
DECL|member|Spid2
r_char
id|Spid2
(braket
id|ISDN_MAX_NUM_LEN
)braket
suffix:semicolon
DECL|member|nosig
id|byte
id|nosig
suffix:semicolon
DECL|member|BriLayer2LinkCount
id|byte
id|BriLayer2LinkCount
suffix:semicolon
multiline_comment|/* amount of TEI&squot;s that adapter will support in P2MP mode */
DECL|member|Channels
id|dword
id|Channels
suffix:semicolon
DECL|member|tei
id|dword
id|tei
suffix:semicolon
DECL|member|nt2
id|dword
id|nt2
suffix:semicolon
DECL|member|TerminalCount
id|dword
id|TerminalCount
suffix:semicolon
DECL|member|WatchDog
id|dword
id|WatchDog
suffix:semicolon
DECL|member|Permanent
id|dword
id|Permanent
suffix:semicolon
DECL|member|BChMask
id|dword
id|BChMask
suffix:semicolon
multiline_comment|/* B channel mask for unchannelized modes */
DECL|member|StableL2
id|dword
id|StableL2
suffix:semicolon
DECL|member|DidLen
id|dword
id|DidLen
suffix:semicolon
DECL|member|NoOrderCheck
id|dword
id|NoOrderCheck
suffix:semicolon
DECL|member|ForceLaw
id|dword
id|ForceLaw
suffix:semicolon
multiline_comment|/* VoiceCoding - default:0, a-law: 1, my-law: 2 */
DECL|member|SigFlags
id|dword
id|SigFlags
suffix:semicolon
DECL|member|LowChannel
id|dword
id|LowChannel
suffix:semicolon
DECL|member|NoHscx30
id|dword
id|NoHscx30
suffix:semicolon
DECL|member|ProtVersion
id|dword
id|ProtVersion
suffix:semicolon
DECL|member|crc4
id|dword
id|crc4
suffix:semicolon
DECL|member|L1TristateOrQsig
id|dword
id|L1TristateOrQsig
suffix:semicolon
multiline_comment|/* enable Layer 1 Tristate (bit 2)Or Qsig params (bit 0,1)*/
DECL|member|InitialDspInfo
id|dword
id|InitialDspInfo
suffix:semicolon
DECL|member|ModemGuardTone
id|dword
id|ModemGuardTone
suffix:semicolon
DECL|member|ModemMinSpeed
id|dword
id|ModemMinSpeed
suffix:semicolon
DECL|member|ModemMaxSpeed
id|dword
id|ModemMaxSpeed
suffix:semicolon
DECL|member|ModemOptions
id|dword
id|ModemOptions
suffix:semicolon
DECL|member|ModemOptions2
id|dword
id|ModemOptions2
suffix:semicolon
DECL|member|ModemNegotiationMode
id|dword
id|ModemNegotiationMode
suffix:semicolon
DECL|member|ModemModulationsMask
id|dword
id|ModemModulationsMask
suffix:semicolon
DECL|member|ModemTransmitLevel
id|dword
id|ModemTransmitLevel
suffix:semicolon
DECL|member|FaxOptions
id|dword
id|FaxOptions
suffix:semicolon
DECL|member|FaxMaxSpeed
id|dword
id|FaxMaxSpeed
suffix:semicolon
DECL|member|Part68LevelLimiter
id|dword
id|Part68LevelLimiter
suffix:semicolon
DECL|member|UsEktsNumCallApp
id|dword
id|UsEktsNumCallApp
suffix:semicolon
DECL|member|UsEktsFeatAddConf
id|byte
id|UsEktsFeatAddConf
suffix:semicolon
DECL|member|UsEktsFeatRemoveConf
id|byte
id|UsEktsFeatRemoveConf
suffix:semicolon
DECL|member|UsEktsFeatCallTransfer
id|byte
id|UsEktsFeatCallTransfer
suffix:semicolon
DECL|member|UsEktsFeatMsgWaiting
id|byte
id|UsEktsFeatMsgWaiting
suffix:semicolon
DECL|member|QsigDialect
id|byte
id|QsigDialect
suffix:semicolon
DECL|member|ForceVoiceMailAlert
id|byte
id|ForceVoiceMailAlert
suffix:semicolon
DECL|member|DisableAutoSpid
id|byte
id|DisableAutoSpid
suffix:semicolon
DECL|member|ModemCarrierWaitTimeSec
id|byte
id|ModemCarrierWaitTimeSec
suffix:semicolon
DECL|member|ModemCarrierLossWaitTimeTenthSec
id|byte
id|ModemCarrierLossWaitTimeTenthSec
suffix:semicolon
DECL|member|PiafsLinkTurnaroundInFrames
id|byte
id|PiafsLinkTurnaroundInFrames
suffix:semicolon
DECL|member|DiscAfterProgress
id|byte
id|DiscAfterProgress
suffix:semicolon
DECL|member|AniDniLimiter
id|byte
id|AniDniLimiter
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|TxAttenuation
id|byte
id|TxAttenuation
suffix:semicolon
multiline_comment|/* PRI/E1 only: attenuate TX signal */
DECL|member|QsigFeatures
id|word
id|QsigFeatures
suffix:semicolon
DECL|member|GenerateRingtone
id|dword
id|GenerateRingtone
suffix:semicolon
DECL|member|SupplementaryServicesFeatures
id|dword
id|SupplementaryServicesFeatures
suffix:semicolon
DECL|member|R2Dialect
id|dword
id|R2Dialect
suffix:semicolon
DECL|member|R2CasOptions
id|dword
id|R2CasOptions
suffix:semicolon
DECL|member|FaxV34Options
id|dword
id|FaxV34Options
suffix:semicolon
DECL|member|DisabledDspMask
id|dword
id|DisabledDspMask
suffix:semicolon
DECL|member|AdapterTestMask
id|dword
id|AdapterTestMask
suffix:semicolon
DECL|member|DspImageLength
id|dword
id|DspImageLength
suffix:semicolon
DECL|member|AlertToIn20mSecTicks
id|word
id|AlertToIn20mSecTicks
suffix:semicolon
DECL|member|ModemEyeSetup
id|word
id|ModemEyeSetup
suffix:semicolon
DECL|member|R2CtryLength
id|byte
id|R2CtryLength
suffix:semicolon
DECL|member|CCBSRelTimer
id|byte
id|CCBSRelTimer
suffix:semicolon
DECL|member|PcCfgBufferFile
id|byte
op_star
id|PcCfgBufferFile
suffix:semicolon
multiline_comment|/* flexible parameter via file */
DECL|member|PcCfgBuffer
id|byte
op_star
id|PcCfgBuffer
suffix:semicolon
multiline_comment|/* flexible parameter via multistring */
DECL|member|dump_file
id|diva_os_dump_file_t
id|dump_file
suffix:semicolon
multiline_comment|/* dump memory to file at lowest irq level */
DECL|member|board_trace
id|diva_os_board_trace_t
id|board_trace
suffix:semicolon
multiline_comment|/* traces from the board */
DECL|member|isr_spin_lock
id|diva_os_spin_lock_t
id|isr_spin_lock
suffix:semicolon
DECL|member|data_spin_lock
id|diva_os_spin_lock_t
id|data_spin_lock
suffix:semicolon
DECL|member|req_soft_isr
id|diva_os_soft_isr_t
id|req_soft_isr
suffix:semicolon
DECL|member|isr_soft_isr
id|diva_os_soft_isr_t
id|isr_soft_isr
suffix:semicolon
DECL|member|in_dpc
id|diva_os_atomic_t
id|in_dpc
suffix:semicolon
DECL|member|RBuffer
id|PBUFFER
id|RBuffer
suffix:semicolon
multiline_comment|/* Copy of receive lookahead buffer */
DECL|member|e_max
id|word
id|e_max
suffix:semicolon
DECL|member|e_count
id|word
id|e_count
suffix:semicolon
DECL|member|e_tbl
id|E_INFO
op_star
id|e_tbl
suffix:semicolon
DECL|member|assign
id|word
id|assign
suffix:semicolon
multiline_comment|/* list of pending ASSIGNs  */
DECL|member|head
id|word
id|head
suffix:semicolon
multiline_comment|/* head of request queue    */
DECL|member|tail
id|word
id|tail
suffix:semicolon
multiline_comment|/* tail of request queue    */
DECL|member|a
id|ADAPTER
id|a
suffix:semicolon
multiline_comment|/* not a separate structure */
DECL|member|out
r_void
(paren
op_star
id|out
)paren
(paren
id|ADAPTER
op_star
id|a
)paren
suffix:semicolon
DECL|member|dpc
id|byte
(paren
op_star
id|dpc
)paren
(paren
id|ADAPTER
op_star
id|a
)paren
suffix:semicolon
DECL|member|tst_irq
id|byte
(paren
op_star
id|tst_irq
)paren
(paren
id|ADAPTER
op_star
id|a
)paren
suffix:semicolon
DECL|member|clr_irq
r_void
(paren
op_star
id|clr_irq
)paren
(paren
id|ADAPTER
op_star
id|a
)paren
suffix:semicolon
DECL|member|load
r_int
(paren
op_star
id|load
)paren
(paren
id|PISDN_ADAPTER
)paren
suffix:semicolon
DECL|member|mapmem
r_int
(paren
op_star
id|mapmem
)paren
(paren
id|PISDN_ADAPTER
)paren
suffix:semicolon
DECL|member|chkIrq
r_int
(paren
op_star
id|chkIrq
)paren
(paren
id|PISDN_ADAPTER
)paren
suffix:semicolon
DECL|member|disIrq
r_void
(paren
op_star
id|disIrq
)paren
(paren
id|PISDN_ADAPTER
)paren
suffix:semicolon
DECL|member|start
r_void
(paren
op_star
id|start
)paren
(paren
id|PISDN_ADAPTER
)paren
suffix:semicolon
DECL|member|stop
r_void
(paren
op_star
id|stop
)paren
(paren
id|PISDN_ADAPTER
)paren
suffix:semicolon
DECL|member|rstFnc
r_void
(paren
op_star
id|rstFnc
)paren
(paren
id|PISDN_ADAPTER
)paren
suffix:semicolon
DECL|member|trapFnc
r_void
(paren
op_star
id|trapFnc
)paren
(paren
id|PISDN_ADAPTER
)paren
suffix:semicolon
DECL|member|DetectDsps
id|dword
(paren
op_star
id|DetectDsps
)paren
(paren
id|PISDN_ADAPTER
)paren
suffix:semicolon
DECL|member|os_trap_nfy_Fnc
r_void
(paren
op_star
id|os_trap_nfy_Fnc
)paren
(paren
id|PISDN_ADAPTER
comma
id|dword
)paren
suffix:semicolon
DECL|member|diva_isr_handler
id|diva_os_isr_callback_t
id|diva_isr_handler
suffix:semicolon
DECL|member|sdram_bar
id|dword
id|sdram_bar
suffix:semicolon
multiline_comment|/* must be 32 bit */
DECL|member|fpga_features
id|dword
id|fpga_features
suffix:semicolon
DECL|member|pcm_pending
r_volatile
r_int
id|pcm_pending
suffix:semicolon
DECL|member|pcm_data
r_volatile
r_void
op_star
id|pcm_data
suffix:semicolon
DECL|member|capi_cfg
id|diva_xdi_capi_cfg_t
id|capi_cfg
suffix:semicolon
DECL|member|tasks
id|dword
id|tasks
suffix:semicolon
DECL|member|dma_map
r_void
op_star
id|dma_map
suffix:semicolon
DECL|member|DivaAdapterTestProc
r_int
(paren
op_star
id|DivaAdapterTestProc
)paren
(paren
id|PISDN_ADAPTER
)paren
suffix:semicolon
DECL|member|AdapterTestMemoryStart
r_void
op_star
id|AdapterTestMemoryStart
suffix:semicolon
DECL|member|AdapterTestMemoryLength
id|dword
id|AdapterTestMemoryLength
suffix:semicolon
DECL|member|cfg_lib_memory_init
r_const
id|byte
op_star
id|cfg_lib_memory_init
suffix:semicolon
DECL|member|cfg_lib_memory_init_length
id|dword
id|cfg_lib_memory_init_length
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------&n;  Entity table&n;   --------------------------------------------------------------------- */
DECL|struct|e_info_s
r_struct
id|e_info_s
(brace
DECL|member|e
id|ENTITY
op_star
id|e
suffix:semicolon
DECL|member|next
id|byte
id|next
suffix:semicolon
multiline_comment|/* chaining index           */
DECL|member|assign_ref
id|word
id|assign_ref
suffix:semicolon
multiline_comment|/* assign reference         */
)brace
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------&n;  S-cards shared ram structure for loading&n;   --------------------------------------------------------------------- */
DECL|struct|s_load
r_struct
id|s_load
(brace
DECL|member|ctrl
id|byte
id|ctrl
suffix:semicolon
DECL|member|card
id|byte
id|card
suffix:semicolon
DECL|member|msize
id|byte
id|msize
suffix:semicolon
DECL|member|fill0
id|byte
id|fill0
suffix:semicolon
DECL|member|ebit
id|word
id|ebit
suffix:semicolon
DECL|member|elocl
id|word
id|elocl
suffix:semicolon
DECL|member|eloch
id|word
id|eloch
suffix:semicolon
DECL|member|reserved
id|byte
id|reserved
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|signature
id|word
id|signature
suffix:semicolon
DECL|member|fill
id|byte
id|fill
(braket
l_int|224
)braket
suffix:semicolon
DECL|member|b
id|byte
id|b
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PR_RAM
mdefine_line|#define PR_RAM  ((struct pr_ram *)0)
DECL|macro|RAM
mdefine_line|#define RAM ((struct dual *)0)
multiline_comment|/* ---------------------------------------------------------------------&n;  Functions for port io&n;   --------------------------------------------------------------------- */
r_void
id|outp_words_from_buffer
(paren
id|word
id|__iomem
op_star
id|adr
comma
id|byte
op_star
id|P
comma
id|dword
id|len
)paren
suffix:semicolon
r_void
id|inp_words_to_buffer
(paren
id|word
id|__iomem
op_star
id|adr
comma
id|byte
op_star
id|P
comma
id|dword
id|len
)paren
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------&n;  platform specific conversions&n;   --------------------------------------------------------------------- */
r_extern
r_void
op_star
id|PTR_P
c_func
(paren
id|ADAPTER
op_star
id|a
comma
id|ENTITY
op_star
id|e
comma
r_void
op_star
id|P
)paren
suffix:semicolon
r_extern
r_void
op_star
id|PTR_X
c_func
(paren
id|ADAPTER
op_star
id|a
comma
id|ENTITY
op_star
id|e
)paren
suffix:semicolon
r_extern
r_void
op_star
id|PTR_R
c_func
(paren
id|ADAPTER
op_star
id|a
comma
id|ENTITY
op_star
id|e
)paren
suffix:semicolon
r_extern
r_void
id|CALLBACK
c_func
(paren
id|ADAPTER
op_star
id|a
comma
id|ENTITY
op_star
id|e
)paren
suffix:semicolon
r_extern
r_void
id|set_ram
c_func
(paren
r_void
op_star
op_star
id|adr_ptr
)paren
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------&n;  ram access functions for io mapped cards&n;   --------------------------------------------------------------------- */
id|byte
id|io_in
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
suffix:semicolon
id|word
id|io_inw
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
suffix:semicolon
r_void
id|io_in_buffer
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
r_void
op_star
id|P
comma
id|word
id|length
)paren
suffix:semicolon
r_void
id|io_look_ahead
c_func
(paren
id|ADAPTER
op_star
id|a
comma
id|PBUFFER
op_star
id|RBuffer
comma
id|ENTITY
op_star
id|e
)paren
suffix:semicolon
r_void
id|io_out
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
id|byte
id|data
)paren
suffix:semicolon
r_void
id|io_outw
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
id|word
id|data
)paren
suffix:semicolon
r_void
id|io_out_buffer
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
r_void
op_star
id|P
comma
id|word
id|length
)paren
suffix:semicolon
r_void
id|io_inc
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
suffix:semicolon
r_void
id|bri_in_buffer
(paren
id|PISDN_ADAPTER
id|IoAdapter
comma
id|dword
id|Pos
comma
r_void
op_star
id|Buf
comma
id|dword
id|Len
)paren
suffix:semicolon
r_int
id|bri_out_buffer
(paren
id|PISDN_ADAPTER
id|IoAdapter
comma
id|dword
id|Pos
comma
r_void
op_star
id|Buf
comma
id|dword
id|Len
comma
r_int
id|Verify
)paren
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------&n;  ram access functions for memory mapped cards&n;   --------------------------------------------------------------------- */
id|byte
id|mem_in
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
suffix:semicolon
id|word
id|mem_inw
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
suffix:semicolon
r_void
id|mem_in_buffer
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
r_void
op_star
id|P
comma
id|word
id|length
)paren
suffix:semicolon
r_void
id|mem_look_ahead
c_func
(paren
id|ADAPTER
op_star
id|a
comma
id|PBUFFER
op_star
id|RBuffer
comma
id|ENTITY
op_star
id|e
)paren
suffix:semicolon
r_void
id|mem_out
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
id|byte
id|data
)paren
suffix:semicolon
r_void
id|mem_outw
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
id|word
id|data
)paren
suffix:semicolon
r_void
id|mem_out_buffer
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
comma
r_void
op_star
id|P
comma
id|word
id|length
)paren
suffix:semicolon
r_void
id|mem_inc
c_func
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|adr
)paren
suffix:semicolon
r_void
id|mem_in_dw
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|addr
comma
id|dword
op_star
id|data
comma
r_int
id|dwords
)paren
suffix:semicolon
r_void
id|mem_out_dw
(paren
id|ADAPTER
op_star
id|a
comma
r_void
op_star
id|addr
comma
r_const
id|dword
op_star
id|data
comma
r_int
id|dwords
)paren
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------&n;  functions exported by io.c&n;   --------------------------------------------------------------------- */
r_extern
id|IDI_CALL
id|Requests
(braket
id|MAX_ADAPTER
)braket
suffix:semicolon
r_extern
r_void
id|DIDpcRoutine
(paren
r_struct
id|_diva_os_soft_isr
op_star
id|psoft_isr
comma
r_void
op_star
id|context
)paren
suffix:semicolon
r_extern
r_void
id|request
(paren
id|PISDN_ADAPTER
comma
id|ENTITY
op_star
)paren
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------&n;  trapFn helpers, used to recover debug trace from dead card&n;   --------------------------------------------------------------------- */
r_typedef
r_struct
(brace
DECL|member|buf
id|word
op_star
id|buf
suffix:semicolon
DECL|member|cnt
id|word
id|cnt
suffix:semicolon
DECL|member|out
id|word
id|out
suffix:semicolon
DECL|typedef|Xdesc
)brace
id|Xdesc
suffix:semicolon
r_extern
r_void
id|dump_trap_frame
(paren
id|PISDN_ADAPTER
id|IoAdapter
comma
id|byte
id|__iomem
op_star
id|exception
)paren
suffix:semicolon
r_extern
r_void
id|dump_xlog_buffer
(paren
id|PISDN_ADAPTER
id|IoAdapter
comma
id|Xdesc
op_star
id|xlogDesc
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
macro_line|#endif  /* } __DIVA_XDI_COMMON_IO_H_INC__ */
eof
