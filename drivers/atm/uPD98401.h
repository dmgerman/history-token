multiline_comment|/* drivers/atm/uPD98401.h - NEC uPD98401 (SAR) declarations */
multiline_comment|/* Written 1995 by Werner Almesberger, EPFL LRC */
macro_line|#ifndef DRIVERS_ATM_uPD98401_H
DECL|macro|DRIVERS_ATM_uPD98401_H
mdefine_line|#define DRIVERS_ATM_uPD98401_H
DECL|macro|MAX_CRAM_SIZE
mdefine_line|#define MAX_CRAM_SIZE&t;(1 &lt;&lt; 18)&t;/* 2^18 words */
DECL|macro|RAM_INCREMENT
mdefine_line|#define RAM_INCREMENT&t;1024&t;&t;/* check in 4 kB increments */
DECL|macro|uPD98401_PORTS
mdefine_line|#define uPD98401_PORTS&t;0x24&t;&t;/* probably more ? */
multiline_comment|/*&n; * Commands&n; */
DECL|macro|uPD98401_OPEN_CHAN
mdefine_line|#define uPD98401_OPEN_CHAN&t;0x20000000 /* open channel */
DECL|macro|uPD98401_CHAN_ADDR
mdefine_line|#define uPD98401_CHAN_ADDR&t;0x0003fff8 /*&t;channel address */
DECL|macro|uPD98401_CHAN_ADDR_SHIFT
mdefine_line|#define uPD98401_CHAN_ADDR_SHIFT 3
DECL|macro|uPD98401_CLOSE_CHAN
mdefine_line|#define uPD98401_CLOSE_CHAN&t;0x24000000 /* close channel */
DECL|macro|uPD98401_CHAN_RT
mdefine_line|#define uPD98401_CHAN_RT&t;0x02000000 /*&t;RX/TX (0 TX, 1 RX) */
DECL|macro|uPD98401_DEACT_CHAN
mdefine_line|#define uPD98401_DEACT_CHAN&t;0x28000000 /* deactivate channel */
DECL|macro|uPD98401_TX_READY
mdefine_line|#define uPD98401_TX_READY&t;0x30000000 /* TX ready */
DECL|macro|uPD98401_ADD_BAT
mdefine_line|#define uPD98401_ADD_BAT&t;0x34000000 /* add batches */
DECL|macro|uPD98401_POOL
mdefine_line|#define uPD98401_POOL&t;&t;0x000f0000 /* pool number */
DECL|macro|uPD98401_POOL_SHIFT
mdefine_line|#define uPD98401_POOL_SHIFT&t;16
DECL|macro|uPD98401_POOL_NUMBAT
mdefine_line|#define uPD98401_POOL_NUMBAT&t;0x0000ffff /* number of batches */
DECL|macro|uPD98401_NOP
mdefine_line|#define uPD98401_NOP&t;&t;0x3f000000 /* NOP */
DECL|macro|uPD98401_IND_ACC
mdefine_line|#define uPD98401_IND_ACC&t;0x00000000 /* Indirect Access */
DECL|macro|uPD98401_IA_RW
mdefine_line|#define uPD98401_IA_RW&t;&t;0x10000000 /*&t;Read/Write (0 W, 1 R) */
DECL|macro|uPD98401_IA_B3
mdefine_line|#define uPD98401_IA_B3&t;&t;0x08000000 /*&t;Byte select, 1 enable */
DECL|macro|uPD98401_IA_B2
mdefine_line|#define uPD98401_IA_B2&t;&t;0x04000000
DECL|macro|uPD98401_IA_B1
mdefine_line|#define uPD98401_IA_B1&t;&t;0x02000000
DECL|macro|uPD98401_IA_B0
mdefine_line|#define uPD98401_IA_B0&t;&t;0x01000000
DECL|macro|uPD98401_IA_BALL
mdefine_line|#define uPD98401_IA_BALL&t;0x0f000000 /*   whole longword */
DECL|macro|uPD98401_IA_TGT
mdefine_line|#define uPD98401_IA_TGT&t;&t;0x000c0000 /*&t;Target */
DECL|macro|uPD98401_IA_TGT_SHIFT
mdefine_line|#define uPD98401_IA_TGT_SHIFT&t;18
DECL|macro|uPD98401_IA_TGT_CM
mdefine_line|#define uPD98401_IA_TGT_CM&t;0&t;   /*&t;- Control Memory */
DECL|macro|uPD98401_IA_TGT_SAR
mdefine_line|#define uPD98401_IA_TGT_SAR&t;1&t;   /*&t;- uPD98401 registers */
DECL|macro|uPD98401_IA_TGT_PHY
mdefine_line|#define uPD98401_IA_TGT_PHY&t;3&t;   /*   - PHY device */
DECL|macro|uPD98401_IA_ADDR
mdefine_line|#define uPD98401_IA_ADDR&t;0x0003ffff
multiline_comment|/*&n; * Command Register Status&n; */
DECL|macro|uPD98401_BUSY
mdefine_line|#define uPD98401_BUSY&t;&t;0x80000000 /* SAR is busy */
DECL|macro|uPD98401_LOCKED
mdefine_line|#define uPD98401_LOCKED&t;&t;0x40000000 /* SAR is locked by other CPU */
multiline_comment|/*&n; * Indications&n; */
multiline_comment|/* Normal (AAL5) Receive Indication */
DECL|macro|uPD98401_AAL5_UINFO
mdefine_line|#define uPD98401_AAL5_UINFO&t;0xffff0000 /* user-supplied information */
DECL|macro|uPD98401_AAL5_UINFO_SHIFT
mdefine_line|#define uPD98401_AAL5_UINFO_SHIFT 16
DECL|macro|uPD98401_AAL5_SIZE
mdefine_line|#define uPD98401_AAL5_SIZE&t;0x0000ffff /* PDU size (in _CELLS_ !!) */
DECL|macro|uPD98401_AAL5_CHAN
mdefine_line|#define uPD98401_AAL5_CHAN&t;0x7fff0000 /* Channel number */
DECL|macro|uPD98401_AAL5_CHAN_SHIFT
mdefine_line|#define uPD98401_AAL5_CHAN_SHIFT&t;16
DECL|macro|uPD98401_AAL5_ERR
mdefine_line|#define uPD98401_AAL5_ERR&t;0x00008000 /* Error indication */
DECL|macro|uPD98401_AAL5_CI
mdefine_line|#define uPD98401_AAL5_CI&t;0x00004000 /* Congestion Indication */
DECL|macro|uPD98401_AAL5_CLP
mdefine_line|#define uPD98401_AAL5_CLP&t;0x00002000 /* CLP (&gt;= 1 cell had CLP=1) */
DECL|macro|uPD98401_AAL5_ES
mdefine_line|#define uPD98401_AAL5_ES&t;0x00000f00 /* Error Status */
DECL|macro|uPD98401_AAL5_ES_SHIFT
mdefine_line|#define uPD98401_AAL5_ES_SHIFT&t;8
DECL|macro|uPD98401_AAL5_ES_NONE
mdefine_line|#define uPD98401_AAL5_ES_NONE&t;0&t;   /*&t;No error */
DECL|macro|uPD98401_AAL5_ES_FREE
mdefine_line|#define uPD98401_AAL5_ES_FREE&t;1&t;   /*&t;Receiver free buf underflow */
DECL|macro|uPD98401_AAL5_ES_FIFO
mdefine_line|#define uPD98401_AAL5_ES_FIFO&t;2&t;   /*&t;Receiver FIFO overrun */
DECL|macro|uPD98401_AAL5_ES_TOOBIG
mdefine_line|#define uPD98401_AAL5_ES_TOOBIG&t;3&t;   /*&t;Maximum length violation */
DECL|macro|uPD98401_AAL5_ES_CRC
mdefine_line|#define uPD98401_AAL5_ES_CRC&t;4&t;   /*&t;CRC error */
DECL|macro|uPD98401_AAL5_ES_ABORT
mdefine_line|#define uPD98401_AAL5_ES_ABORT&t;5&t;   /*&t;User abort */
DECL|macro|uPD98401_AAL5_ES_LENGTH
mdefine_line|#define uPD98401_AAL5_ES_LENGTH&t;6&t;   /*   Length violation */
DECL|macro|uPD98401_AAL5_ES_T1
mdefine_line|#define uPD98401_AAL5_ES_T1&t;7&t;   /*&t;T1 error (timeout) */
DECL|macro|uPD98401_AAL5_ES_DEACT
mdefine_line|#define uPD98401_AAL5_ES_DEACT&t;8&t;   /*&t;Deactivated with DEACT_CHAN */
DECL|macro|uPD98401_AAL5_POOL
mdefine_line|#define uPD98401_AAL5_POOL&t;0x0000001f /* Free buffer pool number */
multiline_comment|/* Raw Cell Indication */
DECL|macro|uPD98401_RAW_UINFO
mdefine_line|#define uPD98401_RAW_UINFO&t;uPD98401_AAL5_UINFO
DECL|macro|uPD98401_RAW_UINFO_SHIFT
mdefine_line|#define uPD98401_RAW_UINFO_SHIFT uPD98401_AAL5_UINFO_SHIFT
DECL|macro|uPD98401_RAW_HEC
mdefine_line|#define uPD98401_RAW_HEC&t;0x000000ff /* HEC */
DECL|macro|uPD98401_RAW_CHAN
mdefine_line|#define uPD98401_RAW_CHAN&t;uPD98401_AAL5_CHAN
DECL|macro|uPD98401_RAW_CHAN_SHIFT
mdefine_line|#define uPD98401_RAW_CHAN_SHIFT uPD98401_AAL5_CHAN_SHIFT
multiline_comment|/* Transmit Indication */
DECL|macro|uPD98401_TXI_CONN
mdefine_line|#define uPD98401_TXI_CONN&t;0x7fff0000 /* Connection Number */
DECL|macro|uPD98401_TXI_CONN_SHIFT
mdefine_line|#define uPD98401_TXI_CONN_SHIFT&t;16
DECL|macro|uPD98401_TXI_ACTIVE
mdefine_line|#define uPD98401_TXI_ACTIVE&t;0x00008000 /* Channel remains active */
DECL|macro|uPD98401_TXI_PQP
mdefine_line|#define uPD98401_TXI_PQP&t;0x00007fff /* Packet Queue Pointer */
multiline_comment|/*&n; * Directly Addressable Registers&n; */
DECL|macro|uPD98401_GMR
mdefine_line|#define uPD98401_GMR&t;0x00&t;/* General Mode Register */
DECL|macro|uPD98401_GSR
mdefine_line|#define uPD98401_GSR&t;0x01&t;/* General Status Register */
DECL|macro|uPD98401_IMR
mdefine_line|#define uPD98401_IMR&t;0x02&t;/* Interrupt Mask Register */
DECL|macro|uPD98401_RQU
mdefine_line|#define uPD98401_RQU&t;0x03&t;/* Receive Queue Underrun */
DECL|macro|uPD98401_RQA
mdefine_line|#define uPD98401_RQA&t;0x04&t;/* Receive Queue Alert */
DECL|macro|uPD98401_ADDR
mdefine_line|#define uPD98401_ADDR&t;0x05&t;/* Last Burst Address */
DECL|macro|uPD98401_VER
mdefine_line|#define uPD98401_VER&t;0x06&t;/* Version Number */
DECL|macro|uPD98401_SWR
mdefine_line|#define uPD98401_SWR&t;0x07&t;/* Software Reset */
DECL|macro|uPD98401_CMR
mdefine_line|#define uPD98401_CMR&t;0x08&t;/* Command Register */
DECL|macro|uPD98401_CMR_L
mdefine_line|#define uPD98401_CMR_L&t;0x09&t;/* Command Register and Lock/Unlock */
DECL|macro|uPD98401_CER
mdefine_line|#define uPD98401_CER&t;0x0a&t;/* Command Extension Register */
DECL|macro|uPD98401_CER_L
mdefine_line|#define uPD98401_CER_L&t;0x0b&t;/* Command Ext Reg and Lock/Unlock */
DECL|macro|uPD98401_MSH
mdefine_line|#define uPD98401_MSH(n) (0x10+(n))&t;/* Mailbox n Start Address High */
DECL|macro|uPD98401_MSL
mdefine_line|#define uPD98401_MSL(n) (0x14+(n))&t;/* Mailbox n Start Address High */
DECL|macro|uPD98401_MBA
mdefine_line|#define uPD98401_MBA(n) (0x18+(n))&t;/* Mailbox n Bottom Address */
DECL|macro|uPD98401_MTA
mdefine_line|#define uPD98401_MTA(n) (0x1c+(n))&t;/* Mailbox n Tail Address */
DECL|macro|uPD98401_MWA
mdefine_line|#define uPD98401_MWA(n) (0x20+(n))&t;/* Mailbox n Write Address */
multiline_comment|/* GMR is at 0x00 */
DECL|macro|uPD98401_GMR_ONE
mdefine_line|#define uPD98401_GMR_ONE&t;0x80000000 /* Must be set to one */
DECL|macro|uPD98401_GMR_SLM
mdefine_line|#define uPD98401_GMR_SLM&t;0x40000000 /* Address mode (0 word, 1 byte) */
DECL|macro|uPD98401_GMR_CPE
mdefine_line|#define uPD98401_GMR_CPE&t;0x00008000 /* Control Memory Parity Enable */
DECL|macro|uPD98401_GMR_LP
mdefine_line|#define uPD98401_GMR_LP&t;&t;0x00004000 /* Loopback */
DECL|macro|uPD98401_GMR_WA
mdefine_line|#define uPD98401_GMR_WA&t;&t;0x00002000 /* Early Bus Write Abort/RDY */
DECL|macro|uPD98401_GMR_RA
mdefine_line|#define uPD98401_GMR_RA&t;&t;0x00001000 /* Early Read Abort/RDY */
DECL|macro|uPD98401_GMR_SZ
mdefine_line|#define uPD98401_GMR_SZ&t;&t;0x00000f00 /* Burst Size Enable */
DECL|macro|uPD98401_BURST16
mdefine_line|#define uPD98401_BURST16&t;0x00000800 /*&t;16-word burst */
DECL|macro|uPD98401_BURST8
mdefine_line|#define uPD98401_BURST8&t;&t;0x00000400 /*&t; 8-word burst */
DECL|macro|uPD98401_BURST4
mdefine_line|#define uPD98401_BURST4&t;&t;0x00000200 /*&t; 4-word burst */
DECL|macro|uPD98401_BURST2
mdefine_line|#define uPD98401_BURST2&t;&t;0x00000100 /*&t; 2-word burst */
DECL|macro|uPD98401_GMR_AD
mdefine_line|#define uPD98401_GMR_AD&t;&t;0x00000080 /* Address (burst resolution) Disable */
DECL|macro|uPD98401_GMR_BO
mdefine_line|#define uPD98401_GMR_BO&t;&t;0x00000040 /* Byte Order (0 little, 1 big) */
DECL|macro|uPD98401_GMR_PM
mdefine_line|#define uPD98401_GMR_PM&t;&t;0x00000020 /* Bus Parity Mode (0 byte, 1 word)*/
DECL|macro|uPD98401_GMR_PC
mdefine_line|#define uPD98401_GMR_PC&t;&t;0x00000010 /* Bus Parity Control (0even,1odd) */
DECL|macro|uPD98401_GMR_BPE
mdefine_line|#define uPD98401_GMR_BPE&t;0x00000008 /* Bus Parity Enable */
DECL|macro|uPD98401_GMR_DR
mdefine_line|#define uPD98401_GMR_DR&t;&t;0x00000004 /* Receive Drop Mode (0drop,1don&squot;t)*/
DECL|macro|uPD98401_GMR_SE
mdefine_line|#define uPD98401_GMR_SE&t;&t;0x00000002 /* Shapers Enable */
DECL|macro|uPD98401_GMR_RE
mdefine_line|#define uPD98401_GMR_RE&t;&t;0x00000001 /* Receiver Enable */
multiline_comment|/* GSR is at 0x01, IMR is at 0x02 */
DECL|macro|uPD98401_INT_PI
mdefine_line|#define uPD98401_INT_PI&t;&t;0x80000000 /* PHY interrupt */
DECL|macro|uPD98401_INT_RQA
mdefine_line|#define uPD98401_INT_RQA&t;0x40000000 /* Receive Queue Alert */
DECL|macro|uPD98401_INT_RQU
mdefine_line|#define uPD98401_INT_RQU&t;0x20000000 /* Receive Queue Underrun */
DECL|macro|uPD98401_INT_RD
mdefine_line|#define uPD98401_INT_RD&t;&t;0x10000000 /* Receiver Deactivated */
DECL|macro|uPD98401_INT_SPE
mdefine_line|#define uPD98401_INT_SPE&t;0x08000000 /* System Parity Error */
DECL|macro|uPD98401_INT_CPE
mdefine_line|#define uPD98401_INT_CPE&t;0x04000000 /* Control Memory Parity Error */
DECL|macro|uPD98401_INT_SBE
mdefine_line|#define uPD98401_INT_SBE&t;0x02000000 /* System Bus Error */
DECL|macro|uPD98401_INT_IND
mdefine_line|#define uPD98401_INT_IND&t;0x01000000 /* Initialization Done */
DECL|macro|uPD98401_INT_RCR
mdefine_line|#define uPD98401_INT_RCR&t;0x0000ff00 /* Raw Cell Received */
DECL|macro|uPD98401_INT_RCR_SHIFT
mdefine_line|#define uPD98401_INT_RCR_SHIFT&t;8
DECL|macro|uPD98401_INT_MF
mdefine_line|#define uPD98401_INT_MF&t;&t;0x000000f0 /* Mailbox Full */
DECL|macro|uPD98401_INT_MF_SHIFT
mdefine_line|#define uPD98401_INT_MF_SHIFT&t;4
DECL|macro|uPD98401_INT_MM
mdefine_line|#define uPD98401_INT_MM&t;&t;0x0000000f /* Mailbox Modified */
multiline_comment|/* VER is at 0x06 */
DECL|macro|uPD98401_MAJOR
mdefine_line|#define uPD98401_MAJOR&t;&t;0x0000ff00 /* Major revision */
DECL|macro|uPD98401_MAJOR_SHIFT
mdefine_line|#define uPD98401_MAJOR_SHIFT&t;8
DECL|macro|uPD98401_MINOR
mdefine_line|#define uPD98401_MINOR&t;&t;0x000000ff /* Minor revision */
multiline_comment|/*&n; * Indirectly Addressable Registers&n; */
DECL|macro|uPD98401_IM
mdefine_line|#define uPD98401_IM(n)&t;(0x40000+(n))&t;/* Scheduler n I and M */
DECL|macro|uPD98401_X
mdefine_line|#define uPD98401_X(n)&t;(0x40010+(n))&t;/* Scheduler n X */
DECL|macro|uPD98401_Y
mdefine_line|#define uPD98401_Y(n)&t;(0x40020+(n))&t;/* Scheduler n Y */
DECL|macro|uPD98401_PC
mdefine_line|#define uPD98401_PC(n)&t;(0x40030+(n))&t;/* Scheduler n P, C, p and c */
DECL|macro|uPD98401_PS
mdefine_line|#define uPD98401_PS(n)&t;(0x40040+(n))&t;/* Scheduler n priority and status */
multiline_comment|/* IM contents */
DECL|macro|uPD98401_IM_I
mdefine_line|#define uPD98401_IM_I&t;&t;0xff000000 /* I */
DECL|macro|uPD98401_IM_I_SHIFT
mdefine_line|#define uPD98401_IM_I_SHIFT&t;24
DECL|macro|uPD98401_IM_M
mdefine_line|#define uPD98401_IM_M&t;&t;0x00ffffff /* M */
multiline_comment|/* PC contents */
DECL|macro|uPD98401_PC_P
mdefine_line|#define uPD98401_PC_P&t;&t;0xff000000 /* P */
DECL|macro|uPD98401_PC_P_SHIFT
mdefine_line|#define uPD98401_PC_P_SHIFT&t;24
DECL|macro|uPD98401_PC_C
mdefine_line|#define uPD98401_PC_C&t;&t;0x00ff0000 /* C */
DECL|macro|uPD98401_PC_C_SHIFT
mdefine_line|#define uPD98401_PC_C_SHIFT&t;16
DECL|macro|uPD98401_PC_p
mdefine_line|#define uPD98401_PC_p&t;&t;0x0000ff00 /* p */
DECL|macro|uPD98401_PC_p_SHIFT
mdefine_line|#define uPD98401_PC_p_SHIFT&t;8
DECL|macro|uPD98401_PC_c
mdefine_line|#define uPD98401_PC_c&t;&t;0x000000ff /* c */
multiline_comment|/* PS contents */
DECL|macro|uPD98401_PS_PRIO
mdefine_line|#define uPD98401_PS_PRIO&t;0xf0&t;/* Priority level (0 high, 15 low) */
DECL|macro|uPD98401_PS_PRIO_SHIFT
mdefine_line|#define uPD98401_PS_PRIO_SHIFT&t;4
DECL|macro|uPD98401_PS_S
mdefine_line|#define uPD98401_PS_S&t;&t;0x08&t;/* Scan - must be 0 (internal) */
DECL|macro|uPD98401_PS_R
mdefine_line|#define uPD98401_PS_R&t;&t;0x04&t;/* Round Robin (internal) */
DECL|macro|uPD98401_PS_A
mdefine_line|#define uPD98401_PS_A&t;&t;0x02&t;/* Active (internal) */
DECL|macro|uPD98401_PS_E
mdefine_line|#define uPD98401_PS_E&t;&t;0x01&t;/* Enabled */
DECL|macro|uPD98401_TOS
mdefine_line|#define uPD98401_TOS&t;0x40100&t;/* Top of Stack Control Memory Address */
DECL|macro|uPD98401_SMA
mdefine_line|#define uPD98401_SMA&t;0x40200&t;/* Shapers Control Memory Start Address */
DECL|macro|uPD98401_PMA
mdefine_line|#define uPD98401_PMA&t;0x40201&t;/* Receive Pool Control Memory Start Address */
DECL|macro|uPD98401_T1R
mdefine_line|#define uPD98401_T1R&t;0x40300&t;/* T1 Register */
DECL|macro|uPD98401_VRR
mdefine_line|#define uPD98401_VRR&t;0x40301&t;/* VPI/VCI Reduction Register/Recv. Shutdown */
DECL|macro|uPD98401_TSR
mdefine_line|#define uPD98401_TSR&t;0x40302&t;/* Time-Stamp Register */
multiline_comment|/* VRR is at 0x40301 */
DECL|macro|uPD98401_VRR_SDM
mdefine_line|#define uPD98401_VRR_SDM&t;0x80000000 /* Shutdown Mode */
DECL|macro|uPD98401_VRR_SHIFT
mdefine_line|#define uPD98401_VRR_SHIFT&t;0x000f0000 /* VPI/VCI Shift */
DECL|macro|uPD98401_VRR_SHIFT_SHIFT
mdefine_line|#define uPD98401_VRR_SHIFT_SHIFT 16
DECL|macro|uPD98401_VRR_MASK
mdefine_line|#define uPD98401_VRR_MASK&t;0x0000ffff /* VPI/VCI mask */
multiline_comment|/*&n; * TX packet descriptor&n; */
DECL|macro|uPD98401_TXPD_SIZE
mdefine_line|#define uPD98401_TXPD_SIZE&t;16&t;   /* descriptor size (in bytes) */
DECL|macro|uPD98401_TXPD_V
mdefine_line|#define uPD98401_TXPD_V&t;&t;0x80000000 /* Valid bit */
DECL|macro|uPD98401_TXPD_DP
mdefine_line|#define uPD98401_TXPD_DP&t;0x40000000 /* Descriptor (1) or Pointer (0) */
DECL|macro|uPD98401_TXPD_SM
mdefine_line|#define uPD98401_TXPD_SM&t;0x20000000 /* Single (1) or Multiple (0) */
DECL|macro|uPD98401_TXPD_CLPM
mdefine_line|#define uPD98401_TXPD_CLPM&t;0x18000000 /* CLP mode */
DECL|macro|uPD98401_CLPM_0
mdefine_line|#define uPD98401_CLPM_0&t;&t;0&t;   /*&t;00 CLP = 0 */
DECL|macro|uPD98401_CLPM_1
mdefine_line|#define uPD98401_CLPM_1&t;&t;3&t;   /*&t;11 CLP = 1 */
DECL|macro|uPD98401_CLPM_LAST
mdefine_line|#define uPD98401_CLPM_LAST&t;1&t;   /*&t;01 CLP unless last cell */
DECL|macro|uPD98401_TXPD_CLPM_SHIFT
mdefine_line|#define uPD98401_TXPD_CLPM_SHIFT 27
DECL|macro|uPD98401_TXPD_PTI
mdefine_line|#define uPD98401_TXPD_PTI&t;0x07000000 /* PTI pattern */
DECL|macro|uPD98401_TXPD_PTI_SHIFT
mdefine_line|#define uPD98401_TXPD_PTI_SHIFT&t;24
DECL|macro|uPD98401_TXPD_GFC
mdefine_line|#define uPD98401_TXPD_GFC&t;0x00f00000 /* GFC pattern */
DECL|macro|uPD98401_TXPD_GFC_SHIFT
mdefine_line|#define uPD98401_TXPD_GFC_SHIFT&t;20
DECL|macro|uPD98401_TXPD_C10
mdefine_line|#define uPD98401_TXPD_C10&t;0x00040000 /* insert CRC-10 */
DECL|macro|uPD98401_TXPD_AAL5
mdefine_line|#define uPD98401_TXPD_AAL5&t;0x00020000 /* AAL5 processing */
DECL|macro|uPD98401_TXPD_MB
mdefine_line|#define uPD98401_TXPD_MB&t;0x00010000 /* TX mailbox number */
DECL|macro|uPD98401_TXPD_UU
mdefine_line|#define uPD98401_TXPD_UU&t;0x0000ff00 /* CPCS-UU */
DECL|macro|uPD98401_TXPD_UU_SHIFT
mdefine_line|#define uPD98401_TXPD_UU_SHIFT&t;8
DECL|macro|uPD98401_TXPD_CPI
mdefine_line|#define uPD98401_TXPD_CPI&t;0x000000ff /* CPI */
multiline_comment|/*&n; * TX buffer descriptor&n; */
DECL|macro|uPD98401_TXBD_SIZE
mdefine_line|#define uPD98401_TXBD_SIZE&t;8&t;   /* descriptor size (in bytes) */
DECL|macro|uPD98401_TXBD_LAST
mdefine_line|#define uPD98401_TXBD_LAST&t;0x80000000 /* last buffer in packet */
multiline_comment|/*&n; * TX VC table&n; */
multiline_comment|/* 1st word has the same structure as in a TX packet descriptor */
DECL|macro|uPD98401_TXVC_L
mdefine_line|#define uPD98401_TXVC_L&t;&t;0x80000000 /* last buffer */
DECL|macro|uPD98401_TXVC_SHP
mdefine_line|#define uPD98401_TXVC_SHP&t;0x0f000000 /* shaper number */
DECL|macro|uPD98401_TXVC_SHP_SHIFT
mdefine_line|#define uPD98401_TXVC_SHP_SHIFT&t;24
DECL|macro|uPD98401_TXVC_VPI
mdefine_line|#define uPD98401_TXVC_VPI&t;0x00ff0000 /* VPI */
DECL|macro|uPD98401_TXVC_VPI_SHIFT
mdefine_line|#define uPD98401_TXVC_VPI_SHIFT&t;16
DECL|macro|uPD98401_TXVC_VCI
mdefine_line|#define uPD98401_TXVC_VCI&t;0x0000ffff /* VCI */
DECL|macro|uPD98401_TXVC_QRP
mdefine_line|#define uPD98401_TXVC_QRP&t;6&t;   /* Queue Read Pointer is in word 6 */
multiline_comment|/*&n; * RX free buffer pools descriptor&n; */
DECL|macro|uPD98401_RXFP_ALERT
mdefine_line|#define uPD98401_RXFP_ALERT&t;0x70000000 /* low water mark */
DECL|macro|uPD98401_RXFP_ALERT_SHIFT
mdefine_line|#define uPD98401_RXFP_ALERT_SHIFT 28
DECL|macro|uPD98401_RXFP_BFSZ
mdefine_line|#define uPD98401_RXFP_BFSZ&t;0x0f000000 /* buffer size, 64*2^n */
DECL|macro|uPD98401_RXFP_BFSZ_SHIFT
mdefine_line|#define uPD98401_RXFP_BFSZ_SHIFT 24
DECL|macro|uPD98401_RXFP_BTSZ
mdefine_line|#define uPD98401_RXFP_BTSZ&t;0x00ff0000 /* batch size, n+1 */
DECL|macro|uPD98401_RXFP_BTSZ_SHIFT
mdefine_line|#define uPD98401_RXFP_BTSZ_SHIFT 16
DECL|macro|uPD98401_RXFP_REMAIN
mdefine_line|#define uPD98401_RXFP_REMAIN&t;0x0000ffff /* remaining batches in pool */
multiline_comment|/*&n; * RX VC table&n; */
DECL|macro|uPD98401_RXVC_BTSZ
mdefine_line|#define uPD98401_RXVC_BTSZ&t;0xff000000 /* remaining free buffers in batch */
DECL|macro|uPD98401_RXVC_BTSZ_SHIFT
mdefine_line|#define uPD98401_RXVC_BTSZ_SHIFT 24
DECL|macro|uPD98401_RXVC_MB
mdefine_line|#define uPD98401_RXVC_MB&t;0x00200000 /* RX mailbox number */
DECL|macro|uPD98401_RXVC_POOL
mdefine_line|#define uPD98401_RXVC_POOL&t;0x001f0000 /* free buffer pool number */
DECL|macro|uPD98401_RXVC_POOL_SHIFT
mdefine_line|#define uPD98401_RXVC_POOL_SHIFT 16
DECL|macro|uPD98401_RXVC_UINFO
mdefine_line|#define uPD98401_RXVC_UINFO&t;0x0000ffff /* user-supplied information */
DECL|macro|uPD98401_RXVC_T1
mdefine_line|#define uPD98401_RXVC_T1&t;0xffff0000 /* T1 timestamp */
DECL|macro|uPD98401_RXVC_T1_SHIFT
mdefine_line|#define uPD98401_RXVC_T1_SHIFT&t;16
DECL|macro|uPD98401_RXVC_PR
mdefine_line|#define uPD98401_RXVC_PR&t;0x00008000 /* Packet Reception, 1 if busy */
DECL|macro|uPD98401_RXVC_DR
mdefine_line|#define uPD98401_RXVC_DR&t;0x00004000 /* FIFO Drop */
DECL|macro|uPD98401_RXVC_OD
mdefine_line|#define uPD98401_RXVC_OD&t;0x00001000 /* Drop OAM cells */
DECL|macro|uPD98401_RXVC_AR
mdefine_line|#define uPD98401_RXVC_AR&t;0x00000800 /* AAL5 or raw cell; 1 if AAL5 */
DECL|macro|uPD98401_RXVC_MAXSEG
mdefine_line|#define uPD98401_RXVC_MAXSEG&t;0x000007ff /* max number of segments per PDU */
DECL|macro|uPD98401_RXVC_REM
mdefine_line|#define uPD98401_RXVC_REM&t;0xfffe0000 /* remaining words in curr buffer */
DECL|macro|uPD98401_RXVC_REM_SHIFT
mdefine_line|#define uPD98401_RXVC_REM_SHIFT&t;17
DECL|macro|uPD98401_RXVC_CLP
mdefine_line|#define uPD98401_RXVC_CLP&t;0x00010000 /* CLP received */
DECL|macro|uPD98401_RXVC_BFA
mdefine_line|#define uPD98401_RXVC_BFA&t;0x00008000 /* Buffer Assigned */
DECL|macro|uPD98401_RXVC_BTA
mdefine_line|#define uPD98401_RXVC_BTA&t;0x00004000 /* Batch Assigned */
DECL|macro|uPD98401_RXVC_CI
mdefine_line|#define uPD98401_RXVC_CI&t;0x00002000 /* Congestion Indication */
DECL|macro|uPD98401_RXVC_DD
mdefine_line|#define uPD98401_RXVC_DD&t;0x00001000 /* Dropping incoming cells */
DECL|macro|uPD98401_RXVC_DP
mdefine_line|#define uPD98401_RXVC_DP&t;0x00000800 /* like PR ? */
DECL|macro|uPD98401_RXVC_CURSEG
mdefine_line|#define uPD98401_RXVC_CURSEG&t;0x000007ff /* Current Segment count */
multiline_comment|/*&n; * RX lookup table&n; */
DECL|macro|uPD98401_RXLT_ENBL
mdefine_line|#define uPD98401_RXLT_ENBL&t;0x8000&t;   /* Enable */
macro_line|#endif
eof
