multiline_comment|/***********************************************************************&n;;*&t;File Name : TMSCSIM.H&t;&t;&t;&t;&t;       *&n;;*&t;&t;    TEKRAM DC-390(T) PCI SCSI Bus Master Host Adapter  *&n;;*&t;&t;    Device Driver&t;&t;&t;&t;       *&n;;***********************************************************************/
multiline_comment|/* $Id: tmscsim.h,v 2.15.2.3 2000/11/17 20:52:27 garloff Exp $ */
macro_line|#ifndef _TMSCSIM_H
DECL|macro|_TMSCSIM_H
mdefine_line|#define _TMSCSIM_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|IRQ_NONE
mdefine_line|#define IRQ_NONE 255
DECL|macro|MAX_ADAPTER_NUM
mdefine_line|#define MAX_ADAPTER_NUM &t;4
DECL|macro|MAX_SG_LIST_BUF
mdefine_line|#define MAX_SG_LIST_BUF &t;16&t;/* Not used */
DECL|macro|MAX_CMD_PER_LUN
mdefine_line|#define MAX_CMD_PER_LUN &t;32
DECL|macro|MAX_CMD_QUEUE
mdefine_line|#define MAX_CMD_QUEUE&t;&t;MAX_CMD_PER_LUN+MAX_CMD_PER_LUN/2+1&t;
DECL|macro|MAX_SCSI_ID
mdefine_line|#define MAX_SCSI_ID&t;&t;8
DECL|macro|MAX_SRB_CNT
mdefine_line|#define MAX_SRB_CNT&t;&t;MAX_CMD_QUEUE+1&t;/* Max number of started commands */
DECL|macro|SEL_TIMEOUT
mdefine_line|#define SEL_TIMEOUT&t;&t;153&t;/* 250 ms selection timeout (@ 40 MHz) */
DECL|macro|END_SCAN
mdefine_line|#define END_SCAN&t;&t;2
DECL|typedef|UCHAR
r_typedef
id|u8
id|UCHAR
suffix:semicolon
multiline_comment|/*  8 bits */
DECL|typedef|USHORT
r_typedef
id|u16
id|USHORT
suffix:semicolon
multiline_comment|/* 16 bits */
DECL|typedef|UINT
r_typedef
id|u32
id|UINT
suffix:semicolon
multiline_comment|/* 32 bits */
DECL|typedef|ULONG
r_typedef
r_int
r_int
id|ULONG
suffix:semicolon
multiline_comment|/* 32/64 bits */
DECL|typedef|PUCHAR
r_typedef
id|UCHAR
op_star
id|PUCHAR
suffix:semicolon
DECL|typedef|PUSHORT
r_typedef
id|USHORT
op_star
id|PUSHORT
suffix:semicolon
DECL|typedef|PUINT
r_typedef
id|UINT
op_star
id|PUINT
suffix:semicolon
DECL|typedef|PULONG
r_typedef
id|ULONG
op_star
id|PULONG
suffix:semicolon
DECL|typedef|PSHT
r_typedef
id|Scsi_Host_Template
op_star
id|PSHT
suffix:semicolon
DECL|typedef|PSH
r_typedef
r_struct
id|Scsi_Host
op_star
id|PSH
suffix:semicolon
DECL|typedef|PSCSIDEV
r_typedef
id|Scsi_Device
op_star
id|PSCSIDEV
suffix:semicolon
DECL|typedef|PSCSICMD
r_typedef
id|Scsi_Cmnd
op_star
id|PSCSICMD
suffix:semicolon
DECL|typedef|PVOID
r_typedef
r_void
op_star
id|PVOID
suffix:semicolon
DECL|typedef|PSGL
DECL|typedef|SGL
r_typedef
r_struct
id|scatterlist
op_star
id|PSGL
comma
id|SGL
suffix:semicolon
multiline_comment|/*;-----------------------------------------------------------------------*/
DECL|struct|_SyncMsg
r_typedef
r_struct
id|_SyncMsg
(brace
DECL|member|ExtendMsg
id|UCHAR
id|ExtendMsg
suffix:semicolon
DECL|member|ExtMsgLen
id|UCHAR
id|ExtMsgLen
suffix:semicolon
DECL|member|SyncXferReq
id|UCHAR
id|SyncXferReq
suffix:semicolon
DECL|member|Period
id|UCHAR
id|Period
suffix:semicolon
DECL|member|ReqOffset
id|UCHAR
id|ReqOffset
suffix:semicolon
DECL|typedef|SyncMsg
)brace
id|SyncMsg
suffix:semicolon
multiline_comment|/*;-----------------------------------------------------------------------*/
DECL|struct|_Capacity
r_typedef
r_struct
id|_Capacity
(brace
DECL|member|BlockCount
id|ULONG
id|BlockCount
suffix:semicolon
DECL|member|BlockLength
id|ULONG
id|BlockLength
suffix:semicolon
DECL|typedef|Capacity
)brace
id|Capacity
suffix:semicolon
multiline_comment|/*;-----------------------------------------------------------------------*/
DECL|struct|_SGentry
r_typedef
r_struct
id|_SGentry
(brace
DECL|member|SGXferDataPtr
id|ULONG
id|SGXferDataPtr
suffix:semicolon
DECL|member|SGXferDataLen
id|ULONG
id|SGXferDataLen
suffix:semicolon
DECL|typedef|SGentry
)brace
id|SGentry
suffix:semicolon
DECL|struct|_SGentry1
r_typedef
r_struct
id|_SGentry1
(brace
DECL|member|SGXLen
id|ULONG
id|SGXLen
suffix:semicolon
DECL|member|SGXPtr
id|ULONG
id|SGXPtr
suffix:semicolon
DECL|typedef|SGentry1
DECL|typedef|PSGE
)brace
id|SGentry1
comma
op_star
id|PSGE
suffix:semicolon
multiline_comment|/*&n;;-----------------------------------------------------------------------&n;; SCSI Request Block&n;;-----------------------------------------------------------------------&n;*/
DECL|struct|_SRB
r_struct
id|_SRB
(brace
singleline_comment|//UCHAR&t;&t;CmdBlock[12];
DECL|member|pNextSRB
r_struct
id|_SRB
op_star
id|pNextSRB
suffix:semicolon
DECL|member|pSRBDCB
r_struct
id|_DCB
op_star
id|pSRBDCB
suffix:semicolon
DECL|member|pcmd
id|PSCSICMD
id|pcmd
suffix:semicolon
DECL|member|pSegmentList
id|PSGL
id|pSegmentList
suffix:semicolon
multiline_comment|/* 0x10: */
DECL|member|Segmentx
id|SGL
id|Segmentx
suffix:semicolon
multiline_comment|/* make a one entry of S/G list table */
multiline_comment|/* 0x1c: */
DECL|member|SGBusAddr
id|ULONG
id|SGBusAddr
suffix:semicolon
multiline_comment|/*;a segment starting address as seen by AM53C974A*/
DECL|member|SGToBeXferLen
id|ULONG
id|SGToBeXferLen
suffix:semicolon
multiline_comment|/*; to be xfer length */
DECL|member|TotalXferredLen
id|ULONG
id|TotalXferredLen
suffix:semicolon
DECL|member|SavedTotXLen
id|ULONG
id|SavedTotXLen
suffix:semicolon
DECL|member|SRBState
id|UINT
id|SRBState
suffix:semicolon
multiline_comment|/* 0x30: */
DECL|member|SRBStatus
id|UCHAR
id|SRBStatus
suffix:semicolon
DECL|member|SRBFlag
id|UCHAR
id|SRBFlag
suffix:semicolon
multiline_comment|/*; b0-AutoReqSense,b6-Read,b7-write */
multiline_comment|/*; b4-settimeout,b5-Residual valid */
DECL|member|AdaptStatus
id|UCHAR
id|AdaptStatus
suffix:semicolon
DECL|member|TargetStatus
id|UCHAR
id|TargetStatus
suffix:semicolon
DECL|member|ScsiPhase
id|UCHAR
id|ScsiPhase
suffix:semicolon
DECL|member|TagNumber
id|UCHAR
id|TagNumber
suffix:semicolon
DECL|member|SGIndex
id|UCHAR
id|SGIndex
suffix:semicolon
DECL|member|SGcount
id|UCHAR
id|SGcount
suffix:semicolon
multiline_comment|/* 0x38: */
DECL|member|MsgCnt
id|UCHAR
id|MsgCnt
suffix:semicolon
DECL|member|EndMessage
id|UCHAR
id|EndMessage
suffix:semicolon
DECL|member|RetryCnt
id|UCHAR
id|RetryCnt
suffix:semicolon
DECL|member|SavedSGCount
id|UCHAR
id|SavedSGCount
suffix:semicolon
DECL|member|Saved_Ptr
id|ULONG
id|Saved_Ptr
suffix:semicolon
multiline_comment|/* 0x40: */
DECL|member|MsgInBuf
id|UCHAR
id|MsgInBuf
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|MsgOutBuf
id|UCHAR
id|MsgOutBuf
(braket
l_int|6
)braket
suffix:semicolon
singleline_comment|//UCHAR&t;&t;IORBFlag;&t;/*;81h-Reset, 2-retry */
multiline_comment|/* 0x4c: */
)brace
suffix:semicolon
DECL|typedef|DC390_SRB
DECL|typedef|PSRB
r_typedef
r_struct
id|_SRB
id|DC390_SRB
comma
op_star
id|PSRB
suffix:semicolon
multiline_comment|/*&n;;-----------------------------------------------------------------------&n;; Device Control Block&n;;-----------------------------------------------------------------------&n;*/
DECL|struct|_DCB
r_struct
id|_DCB
(brace
DECL|member|pNextDCB
r_struct
id|_DCB
op_star
id|pNextDCB
suffix:semicolon
DECL|member|pDCBACB
r_struct
id|_ACB
op_star
id|pDCBACB
suffix:semicolon
multiline_comment|/* Aborted Commands */
singleline_comment|//PSCSICMD&t;AboIORBhead;
singleline_comment|//PSCSICMD&t;AboIORBtail;
singleline_comment|//ULONG&t;&t;AboIORBcnt;
multiline_comment|/* 0x08: */
multiline_comment|/* Queued SRBs */
DECL|member|pWaitingSRB
id|PSRB
id|pWaitingSRB
suffix:semicolon
DECL|member|pWaitLast
id|PSRB
id|pWaitLast
suffix:semicolon
DECL|member|pGoingSRB
id|PSRB
id|pGoingSRB
suffix:semicolon
DECL|member|pGoingLast
id|PSRB
id|pGoingLast
suffix:semicolon
DECL|member|pActiveSRB
id|PSRB
id|pActiveSRB
suffix:semicolon
DECL|member|WaitSRBCnt
id|UCHAR
id|WaitSRBCnt
suffix:semicolon
multiline_comment|/* Not used */
DECL|member|GoingSRBCnt
id|UCHAR
id|GoingSRBCnt
suffix:semicolon
DECL|member|DevType
id|UCHAR
id|DevType
suffix:semicolon
DECL|member|MaxCommand
id|UCHAR
id|MaxCommand
suffix:semicolon
multiline_comment|/* 0x20: */
DECL|member|TagMask
id|UINT
id|TagMask
suffix:semicolon
DECL|member|TargetID
id|UCHAR
id|TargetID
suffix:semicolon
multiline_comment|/*; SCSI Target ID  (SCSI Only) */
DECL|member|TargetLUN
id|UCHAR
id|TargetLUN
suffix:semicolon
multiline_comment|/*; SCSI Log.  Unit (SCSI Only) */
DECL|member|DevMode
id|UCHAR
id|DevMode
suffix:semicolon
DECL|member|DCBFlag
id|UCHAR
id|DCBFlag
suffix:semicolon
DECL|member|CtrlR1
id|UCHAR
id|CtrlR1
suffix:semicolon
DECL|member|CtrlR3
id|UCHAR
id|CtrlR3
suffix:semicolon
DECL|member|CtrlR4
id|UCHAR
id|CtrlR4
suffix:semicolon
DECL|member|Inquiry7
id|UCHAR
id|Inquiry7
suffix:semicolon
multiline_comment|/* 0x2c: */
DECL|member|SyncMode
id|UCHAR
id|SyncMode
suffix:semicolon
multiline_comment|/*; 0:async mode */
DECL|member|NegoPeriod
id|UCHAR
id|NegoPeriod
suffix:semicolon
multiline_comment|/*;for nego. */
DECL|member|SyncPeriod
id|UCHAR
id|SyncPeriod
suffix:semicolon
multiline_comment|/*;for reg. */
DECL|member|SyncOffset
id|UCHAR
id|SyncOffset
suffix:semicolon
multiline_comment|/*;for reg. and nego.(low nibble) */
multiline_comment|/* 0x30:*/
singleline_comment|//UCHAR&t;&t;InqDataBuf[8];
singleline_comment|//UCHAR&t;&t;CapacityBuf[8];
singleline_comment|///* 0x40: */
)brace
suffix:semicolon
DECL|typedef|DC390_DCB
DECL|typedef|PDCB
r_typedef
r_struct
id|_DCB
id|DC390_DCB
comma
op_star
id|PDCB
suffix:semicolon
multiline_comment|/*&n;;-----------------------------------------------------------------------&n;; Adapter Control Block&n;;-----------------------------------------------------------------------&n;*/
DECL|struct|_ACB
r_struct
id|_ACB
(brace
DECL|member|pScsiHost
id|PSH
id|pScsiHost
suffix:semicolon
DECL|member|pNextACB
r_struct
id|_ACB
op_star
id|pNextACB
suffix:semicolon
DECL|member|IOPortBase
id|USHORT
id|IOPortBase
suffix:semicolon
DECL|member|IRQLevel
id|UCHAR
id|IRQLevel
suffix:semicolon
DECL|member|status
id|UCHAR
id|status
suffix:semicolon
DECL|member|SRBCount
id|UCHAR
id|SRBCount
suffix:semicolon
DECL|member|AdapterIndex
id|UCHAR
id|AdapterIndex
suffix:semicolon
multiline_comment|/*; nth Adapter this driver */
DECL|member|DeviceCnt
id|UCHAR
id|DeviceCnt
suffix:semicolon
DECL|member|DCBCnt
id|UCHAR
id|DCBCnt
suffix:semicolon
multiline_comment|/* 0x10: */
DECL|member|TagMaxNum
id|UCHAR
id|TagMaxNum
suffix:semicolon
DECL|member|ACBFlag
id|UCHAR
id|ACBFlag
suffix:semicolon
DECL|member|Gmode2
id|UCHAR
id|Gmode2
suffix:semicolon
DECL|member|scan_devices
id|UCHAR
id|scan_devices
suffix:semicolon
DECL|member|pLinkDCB
id|PDCB
id|pLinkDCB
suffix:semicolon
DECL|member|pLastDCB
id|PDCB
id|pLastDCB
suffix:semicolon
DECL|member|pDCBRunRobin
id|PDCB
id|pDCBRunRobin
suffix:semicolon
DECL|member|pActiveDCB
id|PDCB
id|pActiveDCB
suffix:semicolon
DECL|member|pFreeSRB
id|PSRB
id|pFreeSRB
suffix:semicolon
DECL|member|pTmpSRB
id|PSRB
id|pTmpSRB
suffix:semicolon
multiline_comment|/* 0x2c: */
DECL|member|QueryCnt
id|ULONG
id|QueryCnt
suffix:semicolon
DECL|member|pQueryHead
id|PSCSICMD
id|pQueryHead
suffix:semicolon
DECL|member|pQueryTail
id|PSCSICMD
id|pQueryTail
suffix:semicolon
multiline_comment|/* 0x38: */
DECL|member|msgin123
id|UCHAR
id|msgin123
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|DCBmap
id|UCHAR
id|DCBmap
(braket
id|MAX_SCSI_ID
)braket
suffix:semicolon
DECL|member|Connected
id|UCHAR
id|Connected
suffix:semicolon
DECL|member|pad
id|UCHAR
id|pad
suffix:semicolon
multiline_comment|/* 0x3c: */
macro_line|#if defined(USE_SPINLOCKS) &amp;&amp; USE_SPINLOCKS &gt; 1 &amp;&amp; (defined(CONFIG_SMP) || DEBUG_SPINLOCKS &gt; 0)
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
macro_line|#endif
DECL|member|sel_timeout
id|UCHAR
id|sel_timeout
suffix:semicolon
DECL|member|glitch_cfg
id|UCHAR
id|glitch_cfg
suffix:semicolon
DECL|member|MsgLen
id|UCHAR
id|MsgLen
suffix:semicolon
DECL|member|Ignore_IRQ
id|UCHAR
id|Ignore_IRQ
suffix:semicolon
multiline_comment|/* Not used */
DECL|member|PDEVDECL1
id|PDEVDECL1
suffix:semicolon
multiline_comment|/* Pointer to PCI cfg. space */
multiline_comment|/* 0x4c/0x48: */
DECL|member|Cmds
id|ULONG
id|Cmds
suffix:semicolon
DECL|member|SelLost
id|UINT
id|SelLost
suffix:semicolon
DECL|member|SelConn
id|UINT
id|SelConn
suffix:semicolon
DECL|member|CmdInQ
id|UINT
id|CmdInQ
suffix:semicolon
DECL|member|CmdOutOfSRB
id|UINT
id|CmdOutOfSRB
suffix:semicolon
multiline_comment|/* 0x60/0x5c: */
DECL|member|Waiting_Timer
r_struct
id|timer_list
id|Waiting_Timer
suffix:semicolon
multiline_comment|/* 0x74/0x70: */
DECL|member|TmpSRB
id|DC390_SRB
id|TmpSRB
suffix:semicolon
multiline_comment|/* 0xd8/0xd4: */
DECL|member|SRB_array
id|DC390_SRB
id|SRB_array
(braket
id|MAX_SRB_CNT
)braket
suffix:semicolon
multiline_comment|/* 50 SRBs */
multiline_comment|/* 0xfb0/0xfac: */
)brace
suffix:semicolon
DECL|typedef|DC390_ACB
DECL|typedef|PACB
r_typedef
r_struct
id|_ACB
id|DC390_ACB
comma
op_star
id|PACB
suffix:semicolon
multiline_comment|/*;-----------------------------------------------------------------------*/
DECL|macro|BIT31
mdefine_line|#define BIT31&t;0x80000000
DECL|macro|BIT30
mdefine_line|#define BIT30&t;0x40000000
DECL|macro|BIT29
mdefine_line|#define BIT29&t;0x20000000
DECL|macro|BIT28
mdefine_line|#define BIT28&t;0x10000000
DECL|macro|BIT27
mdefine_line|#define BIT27&t;0x08000000
DECL|macro|BIT26
mdefine_line|#define BIT26&t;0x04000000
DECL|macro|BIT25
mdefine_line|#define BIT25&t;0x02000000
DECL|macro|BIT24
mdefine_line|#define BIT24&t;0x01000000
DECL|macro|BIT23
mdefine_line|#define BIT23&t;0x00800000
DECL|macro|BIT22
mdefine_line|#define BIT22&t;0x00400000
DECL|macro|BIT21
mdefine_line|#define BIT21&t;0x00200000
DECL|macro|BIT20
mdefine_line|#define BIT20&t;0x00100000
DECL|macro|BIT19
mdefine_line|#define BIT19&t;0x00080000
DECL|macro|BIT18
mdefine_line|#define BIT18&t;0x00040000
DECL|macro|BIT17
mdefine_line|#define BIT17&t;0x00020000
DECL|macro|BIT16
mdefine_line|#define BIT16&t;0x00010000
DECL|macro|BIT15
mdefine_line|#define BIT15&t;0x00008000
DECL|macro|BIT14
mdefine_line|#define BIT14&t;0x00004000
DECL|macro|BIT13
mdefine_line|#define BIT13&t;0x00002000
DECL|macro|BIT12
mdefine_line|#define BIT12&t;0x00001000
DECL|macro|BIT11
mdefine_line|#define BIT11&t;0x00000800
DECL|macro|BIT10
mdefine_line|#define BIT10&t;0x00000400
DECL|macro|BIT9
mdefine_line|#define BIT9&t;0x00000200
DECL|macro|BIT8
mdefine_line|#define BIT8&t;0x00000100
DECL|macro|BIT7
mdefine_line|#define BIT7&t;0x00000080
DECL|macro|BIT6
mdefine_line|#define BIT6&t;0x00000040
DECL|macro|BIT5
mdefine_line|#define BIT5&t;0x00000020
DECL|macro|BIT4
mdefine_line|#define BIT4&t;0x00000010
DECL|macro|BIT3
mdefine_line|#define BIT3&t;0x00000008
DECL|macro|BIT2
mdefine_line|#define BIT2&t;0x00000004
DECL|macro|BIT1
mdefine_line|#define BIT1&t;0x00000002
DECL|macro|BIT0
mdefine_line|#define BIT0&t;0x00000001
multiline_comment|/*;---UnitCtrlFlag */
DECL|macro|UNIT_ALLOCATED
mdefine_line|#define UNIT_ALLOCATED&t;BIT0
DECL|macro|UNIT_INFO_CHANGED
mdefine_line|#define UNIT_INFO_CHANGED BIT1
DECL|macro|FORMATING_MEDIA
mdefine_line|#define FORMATING_MEDIA BIT2
DECL|macro|UNIT_RETRY
mdefine_line|#define UNIT_RETRY&t;BIT3
multiline_comment|/*;---UnitFlags */
DECL|macro|DASD_SUPPORT
mdefine_line|#define DASD_SUPPORT&t;BIT0
DECL|macro|SCSI_SUPPORT
mdefine_line|#define SCSI_SUPPORT&t;BIT1
DECL|macro|ASPI_SUPPORT
mdefine_line|#define ASPI_SUPPORT&t;BIT2
multiline_comment|/*;----SRBState machine definition */
DECL|macro|SRB_FREE
mdefine_line|#define SRB_FREE&t;0
DECL|macro|SRB_WAIT
mdefine_line|#define SRB_WAIT&t;BIT0
DECL|macro|SRB_READY
mdefine_line|#define SRB_READY&t;BIT1
DECL|macro|SRB_MSGOUT
mdefine_line|#define SRB_MSGOUT&t;BIT2&t;/*;arbitration+msg_out 1st byte*/
DECL|macro|SRB_MSGIN
mdefine_line|#define SRB_MSGIN&t;BIT3
DECL|macro|SRB_MSGIN_MULTI
mdefine_line|#define SRB_MSGIN_MULTI BIT4
DECL|macro|SRB_COMMAND
mdefine_line|#define SRB_COMMAND&t;BIT5
DECL|macro|SRB_START_
mdefine_line|#define SRB_START_&t;BIT6&t;/*;arbitration+msg_out+command_out*/
DECL|macro|SRB_DISCONNECT
mdefine_line|#define SRB_DISCONNECT&t;BIT7
DECL|macro|SRB_DATA_XFER
mdefine_line|#define SRB_DATA_XFER&t;BIT8
DECL|macro|SRB_XFERPAD
mdefine_line|#define SRB_XFERPAD&t;BIT9
DECL|macro|SRB_STATUS
mdefine_line|#define SRB_STATUS&t;BIT10
DECL|macro|SRB_COMPLETED
mdefine_line|#define SRB_COMPLETED&t;BIT11
DECL|macro|SRB_ABORT_SENT
mdefine_line|#define SRB_ABORT_SENT&t;BIT12
DECL|macro|DO_SYNC_NEGO
mdefine_line|#define DO_SYNC_NEGO&t;BIT13
DECL|macro|SRB_UNEXPECT_RESEL
mdefine_line|#define SRB_UNEXPECT_RESEL BIT14
multiline_comment|/*;---SRBstatus */
DECL|macro|SRB_OK
mdefine_line|#define SRB_OK&t;&t;BIT0
DECL|macro|ABORTION
mdefine_line|#define ABORTION&t;BIT1
DECL|macro|OVER_RUN
mdefine_line|#define OVER_RUN&t;BIT2
DECL|macro|UNDER_RUN
mdefine_line|#define UNDER_RUN&t;BIT3
DECL|macro|PARITY_ERROR
mdefine_line|#define PARITY_ERROR&t;BIT4
DECL|macro|SRB_ERROR
mdefine_line|#define SRB_ERROR&t;BIT5
multiline_comment|/*;---ACBFlag */
DECL|macro|RESET_DEV
mdefine_line|#define RESET_DEV&t;BIT0
DECL|macro|RESET_DETECT
mdefine_line|#define RESET_DETECT&t;BIT1
DECL|macro|RESET_DONE
mdefine_line|#define RESET_DONE&t;BIT2
multiline_comment|/*;---DCBFlag */
DECL|macro|ABORT_DEV_
mdefine_line|#define ABORT_DEV_&t;BIT0
multiline_comment|/*;---SRBFlag */
DECL|macro|DATAOUT
mdefine_line|#define DATAOUT &t;BIT7
DECL|macro|DATAIN
mdefine_line|#define DATAIN&t;&t;BIT6
DECL|macro|RESIDUAL_VALID
mdefine_line|#define RESIDUAL_VALID&t;BIT5
DECL|macro|ENABLE_TIMER
mdefine_line|#define ENABLE_TIMER&t;BIT4
DECL|macro|RESET_DEV0
mdefine_line|#define RESET_DEV0&t;BIT2
DECL|macro|ABORT_DEV
mdefine_line|#define ABORT_DEV&t;BIT1
DECL|macro|AUTO_REQSENSE
mdefine_line|#define AUTO_REQSENSE&t;BIT0
multiline_comment|/*;---Adapter status */
DECL|macro|H_STATUS_GOOD
mdefine_line|#define H_STATUS_GOOD&t; 0
DECL|macro|H_SEL_TIMEOUT
mdefine_line|#define H_SEL_TIMEOUT&t; 0x11
DECL|macro|H_OVER_UNDER_RUN
mdefine_line|#define H_OVER_UNDER_RUN 0x12
DECL|macro|H_UNEXP_BUS_FREE
mdefine_line|#define H_UNEXP_BUS_FREE 0x13
DECL|macro|H_TARGET_PHASE_F
mdefine_line|#define H_TARGET_PHASE_F 0x14
DECL|macro|H_INVALID_CCB_OP
mdefine_line|#define H_INVALID_CCB_OP 0x16
DECL|macro|H_LINK_CCB_BAD
mdefine_line|#define H_LINK_CCB_BAD&t; 0x17
DECL|macro|H_BAD_TARGET_DIR
mdefine_line|#define H_BAD_TARGET_DIR 0x18
DECL|macro|H_DUPLICATE_CCB
mdefine_line|#define H_DUPLICATE_CCB  0x19
DECL|macro|H_BAD_CCB_OR_SG
mdefine_line|#define H_BAD_CCB_OR_SG  0x1A
DECL|macro|H_ABORT
mdefine_line|#define H_ABORT &t; 0x0FF
multiline_comment|/*; SCSI Status byte codes*/
multiline_comment|/* The values defined in include/scsi/scsi.h, to be shifted &lt;&lt; 1 */
DECL|macro|SCSI_STAT_UNEXP_BUS_F
mdefine_line|#define SCSI_STAT_UNEXP_BUS_F&t;0xFD&t;/*;  Unexpect Bus Free */
DECL|macro|SCSI_STAT_BUS_RST_DETECT
mdefine_line|#define SCSI_STAT_BUS_RST_DETECT 0xFE&t;/*;  Scsi Bus Reset detected */
DECL|macro|SCSI_STAT_SEL_TIMEOUT
mdefine_line|#define SCSI_STAT_SEL_TIMEOUT&t;0xFF&t;/*;  Selection Time out */
multiline_comment|/* cmd-&gt;result */
DECL|macro|RES_TARGET
mdefine_line|#define RES_TARGET&t;&t;0x000000FF&t;/* Target State */
DECL|macro|RES_TARGET_LNX
mdefine_line|#define RES_TARGET_LNX&t;&t;STATUS_MASK&t;/* Only official ... */
DECL|macro|RES_ENDMSG
mdefine_line|#define RES_ENDMSG&t;&t;0x0000FF00&t;/* End Message */
DECL|macro|RES_DID
mdefine_line|#define RES_DID&t;&t;&t;0x00FF0000&t;/* DID_ codes */
DECL|macro|RES_DRV
mdefine_line|#define RES_DRV&t;&t;&t;0xFF000000&t;/* DRIVER_ codes */
DECL|macro|MK_RES
mdefine_line|#define MK_RES(drv,did,msg,tgt) ((int)(drv)&lt;&lt;24 | (int)(did)&lt;&lt;16 | (int)(msg)&lt;&lt;8 | (int)(tgt))
DECL|macro|MK_RES_LNX
mdefine_line|#define MK_RES_LNX(drv,did,msg,tgt) ((int)(drv)&lt;&lt;24 | (int)(did)&lt;&lt;16 | (int)(msg)&lt;&lt;8 | (int)(tgt)&lt;&lt;1)
DECL|macro|SET_RES_TARGET
mdefine_line|#define SET_RES_TARGET(who,tgt) { who &amp;= ~RES_TARGET; who |= (int)(tgt); }
DECL|macro|SET_RES_TARGET_LNX
mdefine_line|#define SET_RES_TARGET_LNX(who,tgt) { who &amp;= ~RES_TARGET_LNX; who |= (int)(tgt) &lt;&lt; 1; }
DECL|macro|SET_RES_MSG
mdefine_line|#define SET_RES_MSG(who,msg) { who &amp;= ~RES_ENDMSG; who |= (int)(msg) &lt;&lt; 8; }
DECL|macro|SET_RES_DID
mdefine_line|#define SET_RES_DID(who,did) { who &amp;= ~RES_DID; who |= (int)(did) &lt;&lt; 16; }
DECL|macro|SET_RES_DRV
mdefine_line|#define SET_RES_DRV(who,drv) { who &amp;= ~RES_DRV; who |= (int)(drv) &lt;&lt; 24; }
multiline_comment|/*;---Sync_Mode */
DECL|macro|SYNC_DISABLE
mdefine_line|#define SYNC_DISABLE&t;0
DECL|macro|SYNC_ENABLE
mdefine_line|#define SYNC_ENABLE&t;BIT0
DECL|macro|SYNC_NEGO_DONE
mdefine_line|#define SYNC_NEGO_DONE&t;BIT1
DECL|macro|WIDE_ENABLE
mdefine_line|#define WIDE_ENABLE&t;BIT2&t;/* Not used ;-) */
DECL|macro|WIDE_NEGO_DONE
mdefine_line|#define WIDE_NEGO_DONE&t;BIT3&t;/* Not used ;-) */
DECL|macro|EN_TAG_QUEUEING
mdefine_line|#define EN_TAG_QUEUEING&t;BIT4
DECL|macro|EN_ATN_STOP
mdefine_line|#define EN_ATN_STOP&t;BIT5
DECL|macro|SYNC_NEGO_OFFSET
mdefine_line|#define SYNC_NEGO_OFFSET 15
multiline_comment|/*;---SCSI bus phase*/
DECL|macro|SCSI_DATA_OUT
mdefine_line|#define SCSI_DATA_OUT&t;0
DECL|macro|SCSI_DATA_IN
mdefine_line|#define SCSI_DATA_IN&t;1
DECL|macro|SCSI_COMMAND
mdefine_line|#define SCSI_COMMAND&t;2
DECL|macro|SCSI_STATUS_
mdefine_line|#define SCSI_STATUS_&t;3
DECL|macro|SCSI_NOP0
mdefine_line|#define SCSI_NOP0&t;4
DECL|macro|SCSI_NOP1
mdefine_line|#define SCSI_NOP1&t;5
DECL|macro|SCSI_MSG_OUT
mdefine_line|#define SCSI_MSG_OUT&t;6
DECL|macro|SCSI_MSG_IN
mdefine_line|#define SCSI_MSG_IN&t;7
multiline_comment|/*;----SCSI MSG BYTE*/
multiline_comment|/* see scsi/scsi.h */
multiline_comment|/* One is missing ! */
DECL|macro|ABORT_TAG
mdefine_line|#define ABORT_TAG&t;0x0d
multiline_comment|/*&n;**  Inquiry Data format&n;*/
DECL|struct|_SCSIInqData
r_typedef
r_struct
id|_SCSIInqData
(brace
multiline_comment|/* INQUIRY */
DECL|member|DevType
id|UCHAR
id|DevType
suffix:semicolon
multiline_comment|/* Periph Qualifier &amp; Periph Dev Type*/
DECL|member|RMB_TypeMod
id|UCHAR
id|RMB_TypeMod
suffix:semicolon
multiline_comment|/* rem media bit &amp; Dev Type Modifier */
DECL|member|Vers
id|UCHAR
id|Vers
suffix:semicolon
multiline_comment|/* ISO, ECMA, &amp; ANSI versions&t;     */
DECL|member|RDF
id|UCHAR
id|RDF
suffix:semicolon
multiline_comment|/* AEN, TRMIOP, &amp; response data format*/
DECL|member|AddLen
id|UCHAR
id|AddLen
suffix:semicolon
multiline_comment|/* length of additional data&t;     */
DECL|member|Res1
id|UCHAR
id|Res1
suffix:semicolon
multiline_comment|/* reserved&t;&t;&t;     */
DECL|member|Res2
id|UCHAR
id|Res2
suffix:semicolon
multiline_comment|/* reserved&t;&t;&t;     */
DECL|member|Flags
id|UCHAR
id|Flags
suffix:semicolon
multiline_comment|/* RelADr,Wbus32,Wbus16,Sync,etc.    */
DECL|member|VendorID
id|UCHAR
id|VendorID
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Vendor Identification&t;     */
DECL|member|ProductID
id|UCHAR
id|ProductID
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Product Identification&t;     */
DECL|member|ProductRev
id|UCHAR
id|ProductRev
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Product Revision&t;&t;     */
DECL|typedef|SCSI_INQDATA
DECL|typedef|PSCSI_INQDATA
)brace
id|SCSI_INQDATA
comma
op_star
id|PSCSI_INQDATA
suffix:semicolon
multiline_comment|/*  Inquiry byte 0 masks */
DECL|macro|SCSI_DEVTYPE
mdefine_line|#define SCSI_DEVTYPE&t;    0x1F      /* Peripheral Device Type &t;    */
DECL|macro|SCSI_PERIPHQUAL
mdefine_line|#define SCSI_PERIPHQUAL     0xE0      /* Peripheral Qualifier&t;&t;    */
DECL|macro|TYPE_NODEV
mdefine_line|#define TYPE_NODEV&t;    SCSI_DEVTYPE    /* Unknown or no device type    */
multiline_comment|/*  Inquiry byte 1 mask */
DECL|macro|SCSI_REMOVABLE_MEDIA
mdefine_line|#define SCSI_REMOVABLE_MEDIA  0x80    /* Removable Media bit (1=removable)  */
multiline_comment|/*  Peripheral Device Type definitions */
multiline_comment|/*  see include/scsi/scsi.h for the rest */
macro_line|#ifndef TYPE_PRINTER
DECL|macro|TYPE_PRINTER
macro_line|# define TYPE_PRINTER&t;&t; 0x02&t;   /* Printer device&t;&t;   */
macro_line|#endif
macro_line|#ifndef TYPE_COMM
DECL|macro|TYPE_COMM
macro_line|# define TYPE_COMM&t;&t; 0x09&t;   /* Communications device&t;   */
macro_line|#endif
multiline_comment|/*&n;** Inquiry flag definitions (Inq data byte 7)&n;*/
DECL|macro|SCSI_INQ_RELADR
mdefine_line|#define SCSI_INQ_RELADR       0x80    /* device supports relative addressing*/
DECL|macro|SCSI_INQ_WBUS32
mdefine_line|#define SCSI_INQ_WBUS32       0x40    /* device supports 32 bit data xfers  */
DECL|macro|SCSI_INQ_WBUS16
mdefine_line|#define SCSI_INQ_WBUS16       0x20    /* device supports 16 bit data xfers  */
DECL|macro|SCSI_INQ_SYNC
mdefine_line|#define SCSI_INQ_SYNC&t;      0x10    /* device supports synchronous xfer   */
DECL|macro|SCSI_INQ_LINKED
mdefine_line|#define SCSI_INQ_LINKED       0x08    /* device supports linked commands    */
DECL|macro|SCSI_INQ_CMDQUEUE
mdefine_line|#define SCSI_INQ_CMDQUEUE     0x02    /* device supports command queueing   */
DECL|macro|SCSI_INQ_SFTRE
mdefine_line|#define SCSI_INQ_SFTRE&t;      0x01    /* device supports soft resets */
multiline_comment|/*&n;;==========================================================&n;; EEPROM byte offset&n;;==========================================================&n;*/
DECL|struct|_EEprom
r_typedef
r_struct
id|_EEprom
(brace
DECL|member|EE_MODE1
id|UCHAR
id|EE_MODE1
suffix:semicolon
DECL|member|EE_SPEED
id|UCHAR
id|EE_SPEED
suffix:semicolon
DECL|member|xx1
id|UCHAR
id|xx1
suffix:semicolon
DECL|member|xx2
id|UCHAR
id|xx2
suffix:semicolon
DECL|typedef|EEprom
DECL|typedef|PEEprom
)brace
id|EEprom
comma
op_star
id|PEEprom
suffix:semicolon
DECL|macro|REAL_EE_ADAPT_SCSI_ID
mdefine_line|#define REAL_EE_ADAPT_SCSI_ID 64
DECL|macro|REAL_EE_MODE2
mdefine_line|#define REAL_EE_MODE2&t;65
DECL|macro|REAL_EE_DELAY
mdefine_line|#define REAL_EE_DELAY&t;66
DECL|macro|REAL_EE_TAG_CMD_NUM
mdefine_line|#define REAL_EE_TAG_CMD_NUM&t;67
DECL|macro|EE_ADAPT_SCSI_ID
mdefine_line|#define EE_ADAPT_SCSI_ID 32
DECL|macro|EE_MODE2
mdefine_line|#define EE_MODE2&t;33
DECL|macro|EE_DELAY
mdefine_line|#define EE_DELAY&t;34
DECL|macro|EE_TAG_CMD_NUM
mdefine_line|#define EE_TAG_CMD_NUM&t;35
DECL|macro|EE_LEN
mdefine_line|#define EE_LEN&t;&t;40
multiline_comment|/*; EE_MODE1 bits definition*/
DECL|macro|PARITY_CHK_
mdefine_line|#define PARITY_CHK_&t;BIT0
DECL|macro|SYNC_NEGO_
mdefine_line|#define SYNC_NEGO_&t;BIT1
DECL|macro|EN_DISCONNECT_
mdefine_line|#define EN_DISCONNECT_&t;BIT2
DECL|macro|SEND_START_
mdefine_line|#define SEND_START_&t;BIT3
DECL|macro|TAG_QUEUEING_
mdefine_line|#define TAG_QUEUEING_&t;BIT4
multiline_comment|/*; EE_MODE2 bits definition*/
DECL|macro|MORE2_DRV
mdefine_line|#define MORE2_DRV&t;BIT0
DECL|macro|GREATER_1G
mdefine_line|#define GREATER_1G&t;BIT1
DECL|macro|RST_SCSI_BUS
mdefine_line|#define RST_SCSI_BUS&t;BIT2
DECL|macro|ACTIVE_NEGATION
mdefine_line|#define ACTIVE_NEGATION BIT3
DECL|macro|NO_SEEK
mdefine_line|#define NO_SEEK &t;BIT4
DECL|macro|LUN_CHECK
mdefine_line|#define LUN_CHECK&t;BIT5
DECL|macro|ENABLE_CE
mdefine_line|#define ENABLE_CE&t;1
DECL|macro|DISABLE_CE
mdefine_line|#define DISABLE_CE&t;0
DECL|macro|EEPROM_READ
mdefine_line|#define EEPROM_READ&t;0x80
multiline_comment|/*&n;;==========================================================&n;;&t;AMD 53C974 Registers bit Definition&n;;==========================================================&n;*/
multiline_comment|/*&n;;====================&n;; SCSI Register&n;;====================&n;*/
multiline_comment|/*; Command Reg.(+0CH) (rw) */
DECL|macro|DMA_COMMAND
mdefine_line|#define DMA_COMMAND&t;&t;BIT7
DECL|macro|NOP_CMD
mdefine_line|#define NOP_CMD &t;&t;0
DECL|macro|CLEAR_FIFO_CMD
mdefine_line|#define CLEAR_FIFO_CMD&t;&t;1
DECL|macro|RST_DEVICE_CMD
mdefine_line|#define RST_DEVICE_CMD&t;&t;2
DECL|macro|RST_SCSI_BUS_CMD
mdefine_line|#define RST_SCSI_BUS_CMD&t;3
DECL|macro|INFO_XFER_CMD
mdefine_line|#define INFO_XFER_CMD&t;&t;0x10
DECL|macro|INITIATOR_CMD_CMPLTE
mdefine_line|#define INITIATOR_CMD_CMPLTE&t;0x11
DECL|macro|MSG_ACCEPTED_CMD
mdefine_line|#define MSG_ACCEPTED_CMD&t;0x12
DECL|macro|XFER_PAD_BYTE
mdefine_line|#define XFER_PAD_BYTE&t;&t;0x18
DECL|macro|SET_ATN_CMD
mdefine_line|#define SET_ATN_CMD&t;&t;0x1A
DECL|macro|RESET_ATN_CMD
mdefine_line|#define RESET_ATN_CMD&t;&t;0x1B
DECL|macro|SEL_WO_ATN
mdefine_line|#define SEL_WO_ATN&t;&t;0x41&t;/* currently not used */
DECL|macro|SEL_W_ATN
mdefine_line|#define SEL_W_ATN&t;&t;0x42
DECL|macro|SEL_W_ATN_STOP
mdefine_line|#define SEL_W_ATN_STOP&t;&t;0x43
DECL|macro|SEL_W_ATN3
mdefine_line|#define SEL_W_ATN3&t;&t;0x46
DECL|macro|EN_SEL_RESEL
mdefine_line|#define EN_SEL_RESEL&t;&t;0x44
DECL|macro|DIS_SEL_RESEL
mdefine_line|#define DIS_SEL_RESEL&t;&t;0x45&t;/* currently not used */
DECL|macro|RESEL
mdefine_line|#define RESEL&t;&t;&t;0x40&t;/* &quot; */
DECL|macro|RESEL_ATN3
mdefine_line|#define RESEL_ATN3&t;&t;0x47&t;/* &quot; */
DECL|macro|DATA_XFER_CMD
mdefine_line|#define DATA_XFER_CMD&t;&t;INFO_XFER_CMD
multiline_comment|/*; SCSI Status Reg.(+10H) (r) */
DECL|macro|INTERRUPT
mdefine_line|#define INTERRUPT&t;&t;BIT7
DECL|macro|ILLEGAL_OP_ERR
mdefine_line|#define ILLEGAL_OP_ERR&t;&t;BIT6
DECL|macro|PARITY_ERR
mdefine_line|#define PARITY_ERR&t;&t;BIT5
DECL|macro|COUNT_2_ZERO
mdefine_line|#define COUNT_2_ZERO&t;&t;BIT4
DECL|macro|GROUP_CODE_VALID
mdefine_line|#define GROUP_CODE_VALID&t;BIT3
DECL|macro|SCSI_PHASE_MASK
mdefine_line|#define SCSI_PHASE_MASK &t;(BIT2+BIT1+BIT0) 
multiline_comment|/* BIT2: MSG phase; BIT1: C/D physe; BIT0: I/O phase */
multiline_comment|/*; Interrupt Status Reg.(+14H) (r) */
DECL|macro|SCSI_RESET
mdefine_line|#define SCSI_RESET&t;&t;BIT7
DECL|macro|INVALID_CMD
mdefine_line|#define INVALID_CMD&t;&t;BIT6
DECL|macro|DISCONNECTED
mdefine_line|#define DISCONNECTED&t;&t;BIT5
DECL|macro|SERVICE_REQUEST
mdefine_line|#define SERVICE_REQUEST &t;BIT4
DECL|macro|SUCCESSFUL_OP
mdefine_line|#define SUCCESSFUL_OP&t;&t;BIT3
DECL|macro|RESELECTED
mdefine_line|#define RESELECTED&t;&t;BIT2
DECL|macro|SEL_ATTENTION
mdefine_line|#define SEL_ATTENTION&t;&t;BIT1
DECL|macro|SELECTED
mdefine_line|#define SELECTED&t;&t;BIT0
multiline_comment|/*; Internal State Reg.(+18H) (r) */
DECL|macro|SYNC_OFFSET_FLAG
mdefine_line|#define SYNC_OFFSET_FLAG&t;BIT3
DECL|macro|INTRN_STATE_MASK
mdefine_line|#define INTRN_STATE_MASK&t;(BIT2+BIT1+BIT0)
multiline_comment|/* 0x04: Sel. successful (w/o stop), 0x01: Sel. successful (w/ stop) */
multiline_comment|/*; Clock Factor Reg.(+24H) (w) */
DECL|macro|CLK_FREQ_40MHZ
mdefine_line|#define CLK_FREQ_40MHZ&t;&t;0
DECL|macro|CLK_FREQ_35MHZ
mdefine_line|#define CLK_FREQ_35MHZ&t;&t;(BIT2+BIT1+BIT0)
DECL|macro|CLK_FREQ_30MHZ
mdefine_line|#define CLK_FREQ_30MHZ&t;&t;(BIT2+BIT1)
DECL|macro|CLK_FREQ_25MHZ
mdefine_line|#define CLK_FREQ_25MHZ&t;&t;(BIT2+BIT0)
DECL|macro|CLK_FREQ_20MHZ
mdefine_line|#define CLK_FREQ_20MHZ&t;&t;BIT2
DECL|macro|CLK_FREQ_15MHZ
mdefine_line|#define CLK_FREQ_15MHZ&t;&t;(BIT1+BIT0)
DECL|macro|CLK_FREQ_10MHZ
mdefine_line|#define CLK_FREQ_10MHZ&t;&t;BIT1
multiline_comment|/*; Control Reg. 1(+20H) (rw) */
DECL|macro|EXTENDED_TIMING
mdefine_line|#define EXTENDED_TIMING &t;BIT7
DECL|macro|DIS_INT_ON_SCSI_RST
mdefine_line|#define DIS_INT_ON_SCSI_RST&t;BIT6
DECL|macro|PARITY_ERR_REPO
mdefine_line|#define PARITY_ERR_REPO &t;BIT4
DECL|macro|SCSI_ID_ON_BUS
mdefine_line|#define SCSI_ID_ON_BUS&t;&t;(BIT2+BIT1+BIT0) /* host adapter ID */
multiline_comment|/*; Control Reg. 2(+2CH) (rw) */
DECL|macro|EN_FEATURE
mdefine_line|#define EN_FEATURE&t;&t;BIT6
DECL|macro|EN_SCSI2_CMD
mdefine_line|#define EN_SCSI2_CMD&t;&t;BIT3
multiline_comment|/*; Control Reg. 3(+30H) (rw) */
DECL|macro|ID_MSG_CHECK
mdefine_line|#define ID_MSG_CHECK&t;&t;BIT7
DECL|macro|EN_QTAG_MSG
mdefine_line|#define EN_QTAG_MSG&t;&t;BIT6
DECL|macro|EN_GRP2_CMD
mdefine_line|#define EN_GRP2_CMD&t;&t;BIT5
DECL|macro|FAST_SCSI
mdefine_line|#define FAST_SCSI&t;&t;BIT4&t;/* ;10MB/SEC */
DECL|macro|FAST_CLK
mdefine_line|#define FAST_CLK&t;&t;BIT3&t;/* ;25 - 40 MHZ */
multiline_comment|/*; Control Reg. 4(+34H) (rw) */
DECL|macro|EATER_12NS
mdefine_line|#define EATER_12NS&t;&t;0
DECL|macro|EATER_25NS
mdefine_line|#define EATER_25NS&t;&t;BIT7
DECL|macro|EATER_35NS
mdefine_line|#define EATER_35NS&t;&t;BIT6
DECL|macro|EATER_0NS
mdefine_line|#define EATER_0NS&t;&t;(BIT7+BIT6)
DECL|macro|REDUCED_POWER
mdefine_line|#define REDUCED_POWER&t;&t;BIT5
DECL|macro|CTRL4_RESERVED
mdefine_line|#define CTRL4_RESERVED&t;&t;BIT4&t;/* must be 1 acc. to AM53C974.c */
DECL|macro|NEGATE_REQACKDATA
mdefine_line|#define NEGATE_REQACKDATA&t;BIT2
DECL|macro|NEGATE_REQACK
mdefine_line|#define NEGATE_REQACK&t;&t;BIT3
DECL|macro|GLITCH_TO_NS
mdefine_line|#define GLITCH_TO_NS(x) (((~x&gt;&gt;6 &amp; 2) &gt;&gt; 1) | ((x&gt;&gt;6 &amp; 1) &lt;&lt; 1 ^ (x&gt;&gt;6 &amp; 2)))
DECL|macro|NS_TO_GLITCH
mdefine_line|#define NS_TO_GLITCH(y) (((~y&lt;&lt;7) | ~((y&lt;&lt;6) ^ ((y&lt;&lt;5 &amp; 1&lt;&lt;6) | ~0x40))) &amp; 0xc0)
multiline_comment|/*&n;;====================&n;; DMA Register&n;;====================&n;*/
multiline_comment|/*; DMA Command Reg.(+40H) (rw) */
DECL|macro|READ_DIRECTION
mdefine_line|#define READ_DIRECTION&t;&t;BIT7
DECL|macro|WRITE_DIRECTION
mdefine_line|#define WRITE_DIRECTION &t;0
DECL|macro|EN_DMA_INT
mdefine_line|#define EN_DMA_INT&t;&t;BIT6
DECL|macro|EN_PAGE_INT
mdefine_line|#define EN_PAGE_INT&t;&t;BIT5&t;/* page transfer interrupt enable */
DECL|macro|MAP_TO_MDL
mdefine_line|#define MAP_TO_MDL&t;&t;BIT4
DECL|macro|DIAGNOSTIC
mdefine_line|#define DIAGNOSTIC&t;&t;BIT2
DECL|macro|DMA_IDLE_CMD
mdefine_line|#define DMA_IDLE_CMD&t;&t;0
DECL|macro|DMA_BLAST_CMD
mdefine_line|#define DMA_BLAST_CMD&t;&t;BIT0
DECL|macro|DMA_ABORT_CMD
mdefine_line|#define DMA_ABORT_CMD&t;&t;BIT1
DECL|macro|DMA_START_CMD
mdefine_line|#define DMA_START_CMD&t;&t;(BIT1+BIT0)
multiline_comment|/*; DMA Status Reg.(+54H) (r) */
DECL|macro|PCI_MS_ABORT
mdefine_line|#define PCI_MS_ABORT&t;&t;BIT6
DECL|macro|BLAST_COMPLETE
mdefine_line|#define BLAST_COMPLETE&t;&t;BIT5
DECL|macro|SCSI_INTERRUPT
mdefine_line|#define SCSI_INTERRUPT&t;&t;BIT4
DECL|macro|DMA_XFER_DONE
mdefine_line|#define DMA_XFER_DONE&t;&t;BIT3
DECL|macro|DMA_XFER_ABORT
mdefine_line|#define DMA_XFER_ABORT&t;&t;BIT2
DECL|macro|DMA_XFER_ERROR
mdefine_line|#define DMA_XFER_ERROR&t;&t;BIT1
DECL|macro|POWER_DOWN
mdefine_line|#define POWER_DOWN&t;&t;BIT0
multiline_comment|/*; DMA SCSI Bus and Ctrl.(+70H) */
DECL|macro|EN_INT_ON_PCI_ABORT
mdefine_line|#define EN_INT_ON_PCI_ABORT&t;BIT25
DECL|macro|WRT_ERASE_DMA_STAT
mdefine_line|#define WRT_ERASE_DMA_STAT&t;BIT24
DECL|macro|PW_DOWN_CTRL
mdefine_line|#define PW_DOWN_CTRL&t;&t;BIT21
DECL|macro|SCSI_BUSY
mdefine_line|#define SCSI_BUSY&t;&t;BIT20
DECL|macro|SCLK
mdefine_line|#define SCLK&t;&t;&t;BIT19
DECL|macro|SCAM
mdefine_line|#define SCAM&t;&t;&t;BIT18
DECL|macro|SCSI_LINES
mdefine_line|#define SCSI_LINES&t;&t;0x0003ffff
multiline_comment|/*&n;;==========================================================&n;; SCSI Chip register address offset&n;;==========================================================&n;;Registers are rw unless declared otherwise &n;*/
DECL|macro|CtcReg_Low
mdefine_line|#define CtcReg_Low&t;0x00&t;/* r&t;curr. transfer count */
DECL|macro|CtcReg_Mid
mdefine_line|#define CtcReg_Mid&t;0x04&t;/* r */
DECL|macro|CtcReg_High
mdefine_line|#define CtcReg_High&t;0x38&t;/* r */
DECL|macro|ScsiFifo
mdefine_line|#define ScsiFifo&t;0x08
DECL|macro|ScsiCmd
mdefine_line|#define ScsiCmd &t;0x0C
DECL|macro|Scsi_Status
mdefine_line|#define Scsi_Status&t;0x10&t;/* r */
DECL|macro|INT_Status
mdefine_line|#define INT_Status&t;0x14&t;/* r */
DECL|macro|Sync_Period
mdefine_line|#define Sync_Period&t;0x18&t;/* w */
DECL|macro|Sync_Offset
mdefine_line|#define Sync_Offset&t;0x1C&t;/* w */
DECL|macro|Clk_Factor
mdefine_line|#define Clk_Factor&t;0x24&t;/* w */
DECL|macro|CtrlReg1
mdefine_line|#define CtrlReg1&t;0x20&t;
DECL|macro|CtrlReg2
mdefine_line|#define CtrlReg2&t;0x2C
DECL|macro|CtrlReg3
mdefine_line|#define CtrlReg3&t;0x30
DECL|macro|CtrlReg4
mdefine_line|#define CtrlReg4&t;0x34
DECL|macro|DMA_Cmd
mdefine_line|#define DMA_Cmd &t;0x40
DECL|macro|DMA_XferCnt
mdefine_line|#define DMA_XferCnt&t;0x44&t;/* rw&t;starting transfer count (32 bit) */
DECL|macro|DMA_XferAddr
mdefine_line|#define DMA_XferAddr&t;0x48&t;/* rw&t;starting physical address (32 bit) */
DECL|macro|DMA_Wk_ByteCntr
mdefine_line|#define DMA_Wk_ByteCntr 0x4C&t;/* r&t;working byte counter */
DECL|macro|DMA_Wk_AddrCntr
mdefine_line|#define DMA_Wk_AddrCntr 0x50&t;/* r&t;working address counter */
DECL|macro|DMA_Status
mdefine_line|#define DMA_Status&t;0x54&t;/* r */
DECL|macro|DMA_MDL_Addr
mdefine_line|#define DMA_MDL_Addr&t;0x58&t;/* rw&t;starting MDL address */
DECL|macro|DMA_Wk_MDL_Cntr
mdefine_line|#define DMA_Wk_MDL_Cntr 0x5C&t;/* r&t;working MDL counter */
DECL|macro|DMA_ScsiBusCtrl
mdefine_line|#define DMA_ScsiBusCtrl 0x70&t;/* rw&t;SCSI Bus, PCI/DMA Ctrl */
DECL|macro|StcReg_Low
mdefine_line|#define StcReg_Low&t;CtcReg_Low&t;/* w&t;start transfer count */
DECL|macro|StcReg_Mid
mdefine_line|#define StcReg_Mid&t;CtcReg_Mid&t;/* w */
DECL|macro|StcReg_High
mdefine_line|#define StcReg_High&t;CtcReg_High&t;/* w */
DECL|macro|Scsi_Dest_ID
mdefine_line|#define Scsi_Dest_ID&t;Scsi_Status&t;/* w */
DECL|macro|Scsi_TimeOut
mdefine_line|#define Scsi_TimeOut&t;INT_Status&t;/* w */
DECL|macro|Intern_State
mdefine_line|#define Intern_State&t;Sync_Period&t;/* r */
DECL|macro|Current_Fifo
mdefine_line|#define Current_Fifo&t;Sync_Offset&t;/* r&t;Curr. FIFO / int. state */
DECL|macro|DC390_read8
mdefine_line|#define DC390_read8(address)&t;&t;&t;&bslash;&n;&t;(inb (pACB-&gt;IOPortBase + (address)))
DECL|macro|DC390_read8_
mdefine_line|#define DC390_read8_(address, base)&t;&t;&bslash;&n;&t;(inb ((USHORT)(base) + (address)))
DECL|macro|DC390_read16
mdefine_line|#define DC390_read16(address)&t;&t;&t;&bslash;&n;&t;(inw (pACB-&gt;IOPortBase + (address)))
DECL|macro|DC390_read32
mdefine_line|#define DC390_read32(address)&t;&t;&t;&bslash;&n;&t;(inl (pACB-&gt;IOPortBase + (address)))
DECL|macro|DC390_write8
mdefine_line|#define DC390_write8(address,value)&t;&t;&bslash;&n;&t;outb ((value), pACB-&gt;IOPortBase + (address))
DECL|macro|DC390_write8_
mdefine_line|#define DC390_write8_(address,value,base)&t;&bslash;&n;&t;outb ((value), (USHORT)(base) + (address))
DECL|macro|DC390_write16
mdefine_line|#define DC390_write16(address,value)&t;&t;&bslash;&n;&t;outw ((value), pACB-&gt;IOPortBase + (address))
DECL|macro|DC390_write32
mdefine_line|#define DC390_write32(address,value)&t;&t;&bslash;&n;&t;outl ((value), pACB-&gt;IOPortBase + (address))
macro_line|#endif /* _TMSCSIM_H */
eof
