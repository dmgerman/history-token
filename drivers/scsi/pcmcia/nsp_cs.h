multiline_comment|/*=======================================================/&n;  Header file for nsp_cs.c&n;      By: YOKOTA Hiroshi &lt;yokota@netlab.is.tsukuba.ac.jp&gt;&n;&n;    Ver.1.0 : Cut unused lines.&n;    Ver 0.1 : Initial version.&n;&n;    This software may be used and distributed according to the terms of&n;    the GNU General Public License.&n;&n;=========================================================*/
multiline_comment|/* $Id: nsp_cs.h,v 1.19 2003/08/18 11:09:19 elca Exp $ */
macro_line|#ifndef  __nsp_cs__
DECL|macro|__nsp_cs__
mdefine_line|#define  __nsp_cs__
multiline_comment|/* for debugging */
singleline_comment|//#define NSP_DEBUG 9
multiline_comment|/*&n;#define static&n;#define inline&n;*/
multiline_comment|/************************************&n; * Some useful macros...&n; */
DECL|macro|NUMBER
mdefine_line|#define NUMBER(arr) ((int) (sizeof(arr) / sizeof(arr[0]))) /* from XtNumber() in /usr/X11R6/include/X11/Intrinsic.h */
DECL|macro|BIT
mdefine_line|#define BIT(x)      (1L &lt;&lt; (x))
DECL|macro|MIN
mdefine_line|#define MIN(a,b)    ((a) &gt; (b) ? (b) : (a))
multiline_comment|/* SCSI initiator must be ID 7 */
DECL|macro|NSP_INITIATOR_ID
mdefine_line|#define NSP_INITIATOR_ID  7
DECL|macro|NSP_SELTIMEOUT
mdefine_line|#define NSP_SELTIMEOUT 200
multiline_comment|/***************************************************************************&n; * register definitions&n; ***************************************************************************/
multiline_comment|/*========================================================================&n; * base register&n; ========================================================================*/
DECL|macro|IRQCONTROL
mdefine_line|#define&t;IRQCONTROL&t;0x00  /* R */
DECL|macro|IRQCONTROL_RESELECT_CLEAR
macro_line|#  define IRQCONTROL_RESELECT_CLEAR     BIT(0)
DECL|macro|IRQCONTROL_PHASE_CHANGE_CLEAR
macro_line|#  define IRQCONTROL_PHASE_CHANGE_CLEAR BIT(1)
DECL|macro|IRQCONTROL_TIMER_CLEAR
macro_line|#  define IRQCONTROL_TIMER_CLEAR        BIT(2)
DECL|macro|IRQCONTROL_FIFO_CLEAR
macro_line|#  define IRQCONTROL_FIFO_CLEAR         BIT(3)
DECL|macro|IRQCONTROL_ALLMASK
macro_line|#  define IRQCONTROL_ALLMASK            0xff
DECL|macro|IRQCONTROL_ALLCLEAR
macro_line|#  define IRQCONTROL_ALLCLEAR           (IRQCONTROL_RESELECT_CLEAR     | &bslash;&n;&t;&t;&t;&t;&t; IRQCONTROL_PHASE_CHANGE_CLEAR | &bslash;&n;&t;&t;&t;&t;&t; IRQCONTROL_TIMER_CLEAR        | &bslash;&n;&t;&t;&t;&t;&t; IRQCONTROL_FIFO_CLEAR          )
DECL|macro|IRQCONTROL_IRQDISABLE
macro_line|#  define IRQCONTROL_IRQDISABLE         0xf0
DECL|macro|IRQSTATUS
mdefine_line|#define&t;IRQSTATUS&t;0x00  /* W */
DECL|macro|IRQSTATUS_SCSI
macro_line|#  define IRQSTATUS_SCSI  BIT(0)
DECL|macro|IRQSTATUS_TIMER
macro_line|#  define IRQSTATUS_TIMER BIT(2)
DECL|macro|IRQSTATUS_FIFO
macro_line|#  define IRQSTATUS_FIFO  BIT(3)
DECL|macro|IRQSTATUS_MASK
macro_line|#  define IRQSTATUS_MASK  0x0f
DECL|macro|IFSELECT
mdefine_line|#define&t;IFSELECT&t;0x01 /* W */
DECL|macro|IF_IFSEL
macro_line|#  define IF_IFSEL    BIT(0)
DECL|macro|IF_REGSEL
macro_line|#  define IF_REGSEL   BIT(2)
DECL|macro|FIFOSTATUS
mdefine_line|#define&t;FIFOSTATUS&t;0x01 /* R */
DECL|macro|FIFOSTATUS_CHIP_REVISION_MASK
macro_line|#  define FIFOSTATUS_CHIP_REVISION_MASK 0x0f
DECL|macro|FIFOSTATUS_CHIP_ID_MASK
macro_line|#  define FIFOSTATUS_CHIP_ID_MASK       0x70
DECL|macro|FIFOSTATUS_FULL_EMPTY
macro_line|#  define FIFOSTATUS_FULL_EMPTY         BIT(7)
DECL|macro|INDEXREG
mdefine_line|#define&t;INDEXREG&t;0x02 /* R/W */
DECL|macro|DATAREG
mdefine_line|#define&t;DATAREG&t;&t;0x03 /* R/W */
DECL|macro|FIFODATA
mdefine_line|#define&t;FIFODATA&t;0x04 /* R/W */
DECL|macro|FIFODATA1
mdefine_line|#define&t;FIFODATA1&t;0x05 /* R/W */
DECL|macro|FIFODATA2
mdefine_line|#define&t;FIFODATA2&t;0x06 /* R/W */
DECL|macro|FIFODATA3
mdefine_line|#define&t;FIFODATA3&t;0x07 /* R/W */
multiline_comment|/*====================================================================&n; * indexed register&n; ====================================================================*/
DECL|macro|EXTBUSCTRL
mdefine_line|#define EXTBUSCTRL&t;0x10 /* R/W,deleted */
DECL|macro|CLOCKDIV
mdefine_line|#define CLOCKDIV&t;0x11 /* R/W */
DECL|macro|CLOCK_40M
macro_line|#  define CLOCK_40M 0x02
DECL|macro|CLOCK_20M
macro_line|#  define CLOCK_20M 0x01
DECL|macro|FAST_20
macro_line|#  define FAST_20   BIT(2)
DECL|macro|TERMPWRCTRL
mdefine_line|#define TERMPWRCTRL&t;0x13 /* R/W */
DECL|macro|POWER_ON
macro_line|#  define POWER_ON BIT(0)
DECL|macro|SCSIIRQMODE
mdefine_line|#define SCSIIRQMODE&t;0x15 /* R/W */
DECL|macro|SCSI_PHASE_CHANGE_EI
macro_line|#  define SCSI_PHASE_CHANGE_EI BIT(0)
DECL|macro|RESELECT_EI
macro_line|#  define RESELECT_EI          BIT(4)
DECL|macro|FIFO_IRQ_EI
macro_line|#  define FIFO_IRQ_EI          BIT(5)
DECL|macro|SCSI_RESET_IRQ_EI
macro_line|#  define SCSI_RESET_IRQ_EI    BIT(6)
DECL|macro|IRQPHASESENCE
mdefine_line|#define IRQPHASESENCE&t;0x16 /* R */
DECL|macro|LATCHED_MSG
macro_line|#  define LATCHED_MSG      BIT(0)
DECL|macro|LATCHED_IO
macro_line|#  define LATCHED_IO       BIT(1)
DECL|macro|LATCHED_CD
macro_line|#  define LATCHED_CD       BIT(2)
DECL|macro|LATCHED_BUS_FREE
macro_line|#  define LATCHED_BUS_FREE BIT(3)
DECL|macro|PHASE_CHANGE_IRQ
macro_line|#  define PHASE_CHANGE_IRQ BIT(4)
DECL|macro|RESELECT_IRQ
macro_line|#  define RESELECT_IRQ     BIT(5)
DECL|macro|FIFO_IRQ
macro_line|#  define FIFO_IRQ         BIT(6)
DECL|macro|SCSI_RESET_IRQ
macro_line|#  define SCSI_RESET_IRQ   BIT(7)
DECL|macro|TIMERCOUNT
mdefine_line|#define TIMERCOUNT&t;0x17 /* R/W */
DECL|macro|SCSIBUSCTRL
mdefine_line|#define SCSIBUSCTRL&t;0x18 /* R/W */
DECL|macro|SCSI_SEL
macro_line|#  define SCSI_SEL         BIT(0)
DECL|macro|SCSI_RST
macro_line|#  define SCSI_RST         BIT(1)
DECL|macro|SCSI_DATAOUT_ENB
macro_line|#  define SCSI_DATAOUT_ENB BIT(2)
DECL|macro|SCSI_ATN
macro_line|#  define SCSI_ATN         BIT(3)
DECL|macro|SCSI_ACK
macro_line|#  define SCSI_ACK         BIT(4)
DECL|macro|SCSI_BSY
macro_line|#  define SCSI_BSY         BIT(5)
DECL|macro|AUTODIRECTION
macro_line|#  define AUTODIRECTION    BIT(6)
DECL|macro|ACKENB
macro_line|#  define ACKENB           BIT(7)
DECL|macro|SCSIBUSMON
mdefine_line|#define SCSIBUSMON&t;0x19 /* R */
DECL|macro|SETARBIT
mdefine_line|#define SETARBIT&t;0x1A /* W */
DECL|macro|ARBIT_GO
macro_line|#  define ARBIT_GO         BIT(0)
DECL|macro|ARBIT_FLAG_CLEAR
macro_line|#  define ARBIT_FLAG_CLEAR BIT(1)
DECL|macro|ARBITSTATUS
mdefine_line|#define ARBITSTATUS&t;0x1A /* R */
multiline_comment|/*#  define ARBIT_GO        BIT(0)*/
DECL|macro|ARBIT_WIN
macro_line|#  define ARBIT_WIN        BIT(1)
DECL|macro|ARBIT_FAIL
macro_line|#  define ARBIT_FAIL       BIT(2)
DECL|macro|RESELECT_FLAG
macro_line|#  define RESELECT_FLAG    BIT(3)
DECL|macro|PARITYCTRL
mdefine_line|#define PARITYCTRL&t;0x1B  /* W */
DECL|macro|PARITYSTATUS
mdefine_line|#define PARITYSTATUS&t;0x1B  /* R */
DECL|macro|COMMANDCTRL
mdefine_line|#define COMMANDCTRL&t;0x1C  /* W */
DECL|macro|CLEAR_COMMAND_POINTER
macro_line|#  define CLEAR_COMMAND_POINTER BIT(0)
DECL|macro|AUTO_COMMAND_GO
macro_line|#  define AUTO_COMMAND_GO       BIT(1)
DECL|macro|RESELECTID
mdefine_line|#define RESELECTID&t;0x1C  /* R   */
DECL|macro|COMMANDDATA
mdefine_line|#define COMMANDDATA&t;0x1D  /* R/W */
DECL|macro|POINTERCLR
mdefine_line|#define POINTERCLR&t;0x1E  /*   W */
DECL|macro|POINTER_CLEAR
macro_line|#  define POINTER_CLEAR      BIT(0)
DECL|macro|ACK_COUNTER_CLEAR
macro_line|#  define ACK_COUNTER_CLEAR  BIT(1)
DECL|macro|REQ_COUNTER_CLEAR
macro_line|#  define REQ_COUNTER_CLEAR  BIT(2)
DECL|macro|HOST_COUNTER_CLEAR
macro_line|#  define HOST_COUNTER_CLEAR BIT(3)
DECL|macro|READ_SOURCE
macro_line|#  define READ_SOURCE        (BIT(4) | BIT(5))
DECL|macro|ACK_COUNTER
macro_line|#    define ACK_COUNTER        (0)
DECL|macro|REQ_COUNTER
macro_line|#    define REQ_COUNTER        (BIT(4))
DECL|macro|HOST_COUNTER
macro_line|#    define HOST_COUNTER       (BIT(5))
DECL|macro|TRANSFERCOUNT
mdefine_line|#define TRANSFERCOUNT&t;0x1E  /* R   */
DECL|macro|TRANSFERMODE
mdefine_line|#define TRANSFERMODE&t;0x20  /* R/W */
DECL|macro|MODE_MEM8
macro_line|#  define MODE_MEM8   BIT(0)
DECL|macro|MODE_MEM32
macro_line|#  define MODE_MEM32  BIT(1)
DECL|macro|MODE_ADR24
macro_line|#  define MODE_ADR24  BIT(2)
DECL|macro|MODE_ADR32
macro_line|#  define MODE_ADR32  BIT(3)
DECL|macro|MODE_IO8
macro_line|#  define MODE_IO8    BIT(4)
DECL|macro|MODE_IO32
macro_line|#  define MODE_IO32   BIT(5)
DECL|macro|TRANSFER_GO
macro_line|#  define TRANSFER_GO BIT(6)
DECL|macro|BRAIND
macro_line|#  define BRAIND      BIT(7)
DECL|macro|SYNCREG
mdefine_line|#define SYNCREG&t;&t;0x21 /* R/W */
DECL|macro|SYNCREG_OFFSET_MASK
macro_line|#  define SYNCREG_OFFSET_MASK  0x0f
DECL|macro|SYNCREG_PERIOD_MASK
macro_line|#  define SYNCREG_PERIOD_MASK  0xf0
DECL|macro|SYNCREG_PERIOD_SHIFT
macro_line|#  define SYNCREG_PERIOD_SHIFT 4
DECL|macro|SCSIDATALATCH
mdefine_line|#define SCSIDATALATCH&t;0x22 /*   W */
DECL|macro|SCSIDATAIN
mdefine_line|#define SCSIDATAIN&t;0x22 /* R   */
DECL|macro|SCSIDATAWITHACK
mdefine_line|#define SCSIDATAWITHACK&t;0x23 /* R/W */
DECL|macro|SCAMCONTROL
mdefine_line|#define SCAMCONTROL&t;0x24 /*   W */
DECL|macro|SCAMSTATUS
mdefine_line|#define SCAMSTATUS&t;0x24 /* R   */
DECL|macro|SCAMDATA
mdefine_line|#define SCAMDATA&t;0x25 /* R/W */
DECL|macro|OTHERCONTROL
mdefine_line|#define OTHERCONTROL&t;0x26 /* R/W */
DECL|macro|TPL_ROM_WRITE_EN
macro_line|#  define TPL_ROM_WRITE_EN BIT(0)
DECL|macro|TPWR_OUT
macro_line|#  define TPWR_OUT         BIT(1)
DECL|macro|TPWR_SENSE
macro_line|#  define TPWR_SENSE       BIT(2)
DECL|macro|RA8_CONTROL
macro_line|#  define RA8_CONTROL      BIT(3)
DECL|macro|ACKWIDTH
mdefine_line|#define ACKWIDTH&t;0x27 /* R/W */
DECL|macro|CLRTESTPNT
mdefine_line|#define CLRTESTPNT&t;0x28 /*   W */
DECL|macro|ACKCNTLD
mdefine_line|#define ACKCNTLD&t;0x29 /*   W */
DECL|macro|REQCNTLD
mdefine_line|#define REQCNTLD&t;0x2A /*   W */
DECL|macro|HSTCNTLD
mdefine_line|#define HSTCNTLD&t;0x2B /*   W */
DECL|macro|CHECKSUM
mdefine_line|#define CHECKSUM&t;0x2C /* R/W */
multiline_comment|/************************************************************************&n; * Input status bit definitions.&n; ************************************************************************/
DECL|macro|S_MESSAGE
mdefine_line|#define S_MESSAGE&t;BIT(0)    /* Message line from SCSI bus      */
DECL|macro|S_IO
mdefine_line|#define S_IO&t;&t;BIT(1)    /* Input/Output line from SCSI bus */
DECL|macro|S_CD
mdefine_line|#define S_CD&t;&t;BIT(2)    /* Command/Data line from SCSI bus */
DECL|macro|S_BUSY
mdefine_line|#define S_BUSY&t;&t;BIT(3)    /* Busy line from SCSI bus         */
DECL|macro|S_ACK
mdefine_line|#define S_ACK&t;&t;BIT(4)    /* Acknowlege line from SCSI bus   */
DECL|macro|S_REQUEST
mdefine_line|#define S_REQUEST&t;BIT(5)    /* Request line from SCSI bus      */
DECL|macro|S_SELECT
mdefine_line|#define S_SELECT&t;BIT(6)&t;  /*                                 */
DECL|macro|S_ATN
mdefine_line|#define S_ATN&t;&t;BIT(7)&t;  /*                                 */
multiline_comment|/***********************************************************************&n; * Useful Bus Monitor status combinations.&n; ***********************************************************************/
DECL|macro|BUSMON_SEL
mdefine_line|#define BUSMON_SEL         S_SELECT
DECL|macro|BUSMON_BSY
mdefine_line|#define BUSMON_BSY         S_BUSY
DECL|macro|BUSMON_REQ
mdefine_line|#define BUSMON_REQ         S_REQUEST
DECL|macro|BUSMON_IO
mdefine_line|#define BUSMON_IO          S_IO
DECL|macro|BUSMON_ACK
mdefine_line|#define BUSMON_ACK         S_ACK
DECL|macro|BUSMON_BUS_FREE
mdefine_line|#define BUSMON_BUS_FREE    0
DECL|macro|BUSMON_COMMAND
mdefine_line|#define BUSMON_COMMAND     ( S_BUSY | S_CD |                    S_REQUEST )
DECL|macro|BUSMON_MESSAGE_IN
mdefine_line|#define BUSMON_MESSAGE_IN  ( S_BUSY | S_CD | S_IO | S_MESSAGE | S_REQUEST )
DECL|macro|BUSMON_MESSAGE_OUT
mdefine_line|#define BUSMON_MESSAGE_OUT ( S_BUSY | S_CD |        S_MESSAGE | S_REQUEST )
DECL|macro|BUSMON_DATA_IN
mdefine_line|#define BUSMON_DATA_IN     ( S_BUSY |        S_IO |             S_REQUEST )
DECL|macro|BUSMON_DATA_OUT
mdefine_line|#define BUSMON_DATA_OUT    ( S_BUSY |                           S_REQUEST )
DECL|macro|BUSMON_STATUS
mdefine_line|#define BUSMON_STATUS      ( S_BUSY | S_CD | S_IO |             S_REQUEST )
DECL|macro|BUSMON_SELECT
mdefine_line|#define BUSMON_SELECT      (                 S_IO |                        S_SELECT )
DECL|macro|BUSMON_RESELECT
mdefine_line|#define BUSMON_RESELECT    (                 S_IO |                        S_SELECT )
DECL|macro|BUSMON_PHASE_MASK
mdefine_line|#define BUSMON_PHASE_MASK  (          S_CD | S_IO | S_MESSAGE |            S_SELECT )
DECL|macro|BUSPHASE_SELECT
mdefine_line|#define BUSPHASE_SELECT      ( BUSMON_SELECT      &amp; BUSMON_PHASE_MASK )
DECL|macro|BUSPHASE_COMMAND
mdefine_line|#define BUSPHASE_COMMAND     ( BUSMON_COMMAND     &amp; BUSMON_PHASE_MASK )
DECL|macro|BUSPHASE_MESSAGE_IN
mdefine_line|#define BUSPHASE_MESSAGE_IN  ( BUSMON_MESSAGE_IN  &amp; BUSMON_PHASE_MASK )
DECL|macro|BUSPHASE_MESSAGE_OUT
mdefine_line|#define BUSPHASE_MESSAGE_OUT ( BUSMON_MESSAGE_OUT &amp; BUSMON_PHASE_MASK )
DECL|macro|BUSPHASE_DATA_IN
mdefine_line|#define BUSPHASE_DATA_IN     ( BUSMON_DATA_IN     &amp; BUSMON_PHASE_MASK )
DECL|macro|BUSPHASE_DATA_OUT
mdefine_line|#define BUSPHASE_DATA_OUT    ( BUSMON_DATA_OUT    &amp; BUSMON_PHASE_MASK )
DECL|macro|BUSPHASE_STATUS
mdefine_line|#define BUSPHASE_STATUS      ( BUSMON_STATUS      &amp; BUSMON_PHASE_MASK )
multiline_comment|/*====================================================================*/
DECL|struct|scsi_info_t
r_typedef
r_struct
id|scsi_info_t
(brace
DECL|member|link
id|dev_link_t
id|link
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
macro_line|#if (LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,74))
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
macro_line|#else
DECL|member|ndev
r_int
id|ndev
suffix:semicolon
DECL|member|node
id|dev_node_t
id|node
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|bus
r_struct
id|bus_operations
op_star
id|bus
suffix:semicolon
macro_line|#endif
DECL|member|stop
r_int
id|stop
suffix:semicolon
DECL|typedef|scsi_info_t
)brace
id|scsi_info_t
suffix:semicolon
multiline_comment|/* synchronous transfer negotiation data */
DECL|struct|_sync_data
r_typedef
r_struct
id|_sync_data
(brace
DECL|member|SyncNegotiation
r_int
r_int
id|SyncNegotiation
suffix:semicolon
DECL|macro|SYNC_NOT_YET
mdefine_line|#define SYNC_NOT_YET 0
DECL|macro|SYNC_OK
mdefine_line|#define SYNC_OK      1
DECL|macro|SYNC_NG
mdefine_line|#define SYNC_NG      2
DECL|member|SyncPeriod
r_int
r_int
id|SyncPeriod
suffix:semicolon
DECL|member|SyncOffset
r_int
r_int
id|SyncOffset
suffix:semicolon
DECL|member|SyncRegister
r_int
r_char
id|SyncRegister
suffix:semicolon
DECL|member|AckWidth
r_int
r_char
id|AckWidth
suffix:semicolon
DECL|typedef|sync_data
)brace
id|sync_data
suffix:semicolon
DECL|struct|_nsp_hw_data
r_typedef
r_struct
id|_nsp_hw_data
(brace
DECL|member|BaseAddress
r_int
r_int
id|BaseAddress
suffix:semicolon
DECL|member|NumAddress
r_int
r_int
id|NumAddress
suffix:semicolon
DECL|member|IrqNumber
r_int
r_int
id|IrqNumber
suffix:semicolon
DECL|member|MmioAddress
r_int
r_int
id|MmioAddress
suffix:semicolon
DECL|macro|NSP_MMIO_OFFSET
mdefine_line|#define NSP_MMIO_OFFSET 0x0800
DECL|member|MmioLength
r_int
r_int
id|MmioLength
suffix:semicolon
DECL|member|ScsiClockDiv
r_int
r_char
id|ScsiClockDiv
suffix:semicolon
DECL|member|TransferMode
r_int
r_char
id|TransferMode
suffix:semicolon
DECL|member|TimerCount
r_int
id|TimerCount
suffix:semicolon
DECL|member|SelectionTimeOut
r_int
id|SelectionTimeOut
suffix:semicolon
DECL|member|CurrentSC
id|Scsi_Cmnd
op_star
id|CurrentSC
suffix:semicolon
singleline_comment|//int           CurrnetTarget;
DECL|member|FifoCount
r_int
id|FifoCount
suffix:semicolon
DECL|macro|MSGBUF_SIZE
mdefine_line|#define MSGBUF_SIZE 20
DECL|member|MsgBuffer
r_int
r_char
id|MsgBuffer
(braket
id|MSGBUF_SIZE
)braket
suffix:semicolon
DECL|member|MsgLen
r_int
id|MsgLen
suffix:semicolon
DECL|macro|N_TARGET
mdefine_line|#define N_TARGET 8
DECL|member|Sync
id|sync_data
id|Sync
(braket
id|N_TARGET
)braket
suffix:semicolon
DECL|member|nspinfo
r_char
id|nspinfo
(braket
l_int|110
)braket
suffix:semicolon
multiline_comment|/* description */
DECL|member|Lock
id|spinlock_t
id|Lock
suffix:semicolon
DECL|member|ScsiInfo
id|scsi_info_t
op_star
id|ScsiInfo
suffix:semicolon
multiline_comment|/* attach &lt;-&gt; detect glue */
macro_line|#ifdef NSP_DEBUG
DECL|member|CmdId
r_int
id|CmdId
suffix:semicolon
multiline_comment|/* Accepted command serial number.&n;&t;&t;      Used for debugging.             */
macro_line|#endif
DECL|typedef|nsp_hw_data
)brace
id|nsp_hw_data
suffix:semicolon
multiline_comment|/****************************************************************************&n; *&n; */
multiline_comment|/* Card service functions */
r_static
id|dev_link_t
op_star
id|nsp_cs_attach
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|nsp_cs_detach
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_void
id|nsp_cs_release
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_void
id|nsp_cs_config
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_int
id|nsp_cs_event
(paren
id|event_t
id|event
comma
r_int
id|priority
comma
id|event_callback_args_t
op_star
id|args
)paren
suffix:semicolon
multiline_comment|/* Linux SCSI subsystem specific functions */
r_static
r_struct
id|Scsi_Host
op_star
id|nsp_detect
(paren
id|Scsi_Host_Template
op_star
id|sht
)paren
suffix:semicolon
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,5,0))
r_static
r_int
id|nsp_detect_old
(paren
id|Scsi_Host_Template
op_star
id|sht
)paren
suffix:semicolon
r_static
r_int
id|nsp_release_old
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shpnt
)paren
suffix:semicolon
macro_line|#endif
r_static
r_const
r_char
op_star
id|nsp_info
(paren
r_struct
id|Scsi_Host
op_star
id|shpnt
)paren
suffix:semicolon
r_static
r_int
id|nsp_proc_info
(paren
macro_line|#if (LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,5,73))
r_struct
id|Scsi_Host
op_star
id|host
comma
macro_line|#endif
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
macro_line|#if !(LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,5,73))
r_int
id|hostno
comma
macro_line|#endif
r_int
id|inout
)paren
suffix:semicolon
r_static
r_int
id|nsp_queuecommand
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
)paren
suffix:semicolon
multiline_comment|/* Error handler */
multiline_comment|/*static int nsp_eh_abort       (Scsi_Cmnd *SCpnt);*/
multiline_comment|/*static int nsp_eh_device_reset(Scsi_Cmnd *SCpnt);*/
r_static
r_int
id|nsp_eh_bus_reset
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|nsp_eh_host_reset
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|nsp_bus_reset
(paren
id|nsp_hw_data
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* */
r_static
r_int
id|nsphw_init
(paren
id|nsp_hw_data
op_star
id|data
)paren
suffix:semicolon
r_static
r_int
id|nsphw_start_selection
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_void
id|nsp_start_timer
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
id|time
)paren
suffix:semicolon
r_static
r_int
id|nsp_fifo_count
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_void
id|nsp_pio_read
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_void
id|nsp_pio_write
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|nsp_nexus
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_void
id|nsp_scsi_done
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|nsp_analyze_sdtr
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|nsp_negate_signal
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
r_char
id|mask
comma
r_char
op_star
id|str
)paren
suffix:semicolon
r_static
r_int
id|nsp_expect_signal
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
r_char
id|current_phase
comma
r_int
r_char
id|mask
)paren
suffix:semicolon
r_static
r_int
id|nsp_xfer
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
id|phase
)paren
suffix:semicolon
r_static
r_int
id|nsp_dataphase_bypass
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|nsp_reselected
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_struct
id|Scsi_Host
op_star
id|nsp_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|sht
)paren
suffix:semicolon
multiline_comment|/* Interrupt handler */
singleline_comment|//static irqreturn_t nspintr(int irq, void *dev_id, struct pt_regs *regs);
multiline_comment|/* Module entry point*/
r_static
r_int
id|__init
id|nsp_cs_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|__exit
id|nsp_cs_exit
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Debug */
macro_line|#ifdef NSP_DEBUG
r_static
r_void
id|show_command
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_void
id|show_phase
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_void
id|show_busphase
c_func
(paren
r_int
r_char
id|stat
)paren
suffix:semicolon
r_static
r_void
id|show_message
(paren
id|nsp_hw_data
op_star
id|data
)paren
suffix:semicolon
macro_line|#else
DECL|macro|show_command
macro_line|# define show_command(ptr)   /* */
DECL|macro|show_phase
macro_line|# define show_phase(SCpnt)   /* */
DECL|macro|show_busphase
macro_line|# define show_busphase(stat) /* */
DECL|macro|show_message
macro_line|# define show_message(data)  /* */
macro_line|#endif
multiline_comment|/*&n; * SCSI phase&n; */
DECL|enum|_scsi_phase
r_enum
id|_scsi_phase
(brace
DECL|enumerator|PH_UNDETERMINED
id|PH_UNDETERMINED
comma
DECL|enumerator|PH_ARBSTART
id|PH_ARBSTART
comma
DECL|enumerator|PH_SELSTART
id|PH_SELSTART
comma
DECL|enumerator|PH_SELECTED
id|PH_SELECTED
comma
DECL|enumerator|PH_COMMAND
id|PH_COMMAND
comma
DECL|enumerator|PH_DATA
id|PH_DATA
comma
DECL|enumerator|PH_STATUS
id|PH_STATUS
comma
DECL|enumerator|PH_MSG_IN
id|PH_MSG_IN
comma
DECL|enumerator|PH_MSG_OUT
id|PH_MSG_OUT
comma
DECL|enumerator|PH_DISCONNECT
id|PH_DISCONNECT
comma
DECL|enumerator|PH_RESELECT
id|PH_RESELECT
comma
DECL|enumerator|PH_ABORT
id|PH_ABORT
comma
DECL|enumerator|PH_RESET
id|PH_RESET
)brace
suffix:semicolon
DECL|enum|_data_in_out
r_enum
id|_data_in_out
(brace
DECL|enumerator|IO_UNKNOWN
id|IO_UNKNOWN
comma
DECL|enumerator|IO_IN
id|IO_IN
comma
DECL|enumerator|IO_OUT
id|IO_OUT
)brace
suffix:semicolon
DECL|enum|_burst_mode
r_enum
id|_burst_mode
(brace
DECL|enumerator|BURST_IO8
id|BURST_IO8
op_assign
l_int|0
comma
DECL|enumerator|BURST_IO32
id|BURST_IO32
op_assign
l_int|1
comma
DECL|enumerator|BURST_MEM32
id|BURST_MEM32
op_assign
l_int|2
comma
)brace
suffix:semicolon
multiline_comment|/**************************************************************************&n; * SCSI messaage&n; */
DECL|macro|MSG_COMMAND_COMPLETE
mdefine_line|#define MSG_COMMAND_COMPLETE 0x00
DECL|macro|MSG_EXTENDED
mdefine_line|#define MSG_EXTENDED         0x01
DECL|macro|MSG_ABORT
mdefine_line|#define MSG_ABORT            0x06
DECL|macro|MSG_NO_OPERATION
mdefine_line|#define MSG_NO_OPERATION     0x08
DECL|macro|MSG_BUS_DEVICE_RESET
mdefine_line|#define MSG_BUS_DEVICE_RESET 0x0c
DECL|macro|MSG_EXT_SDTR
mdefine_line|#define MSG_EXT_SDTR         0x01
multiline_comment|/**************************************************************************&n; * Compatibility functions&n; */
multiline_comment|/* for Kernel 2.4 */
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,6,0))
DECL|macro|scsi_register_host
macro_line|#  define scsi_register_host(template)   scsi_register_module(MODULE_SCSI_HA, template)
DECL|macro|scsi_unregister_host
macro_line|#  define scsi_unregister_host(template) scsi_unregister_module(MODULE_SCSI_HA, template)
DECL|macro|scsi_host_put
macro_line|#  define scsi_host_put(host)            scsi_unregister(host)
DECL|typedef|irqreturn_t
r_typedef
r_void
id|irqreturn_t
suffix:semicolon
DECL|macro|IRQ_NONE
macro_line|#  define IRQ_NONE      /* */
DECL|macro|IRQ_HANDLED
macro_line|#  define IRQ_HANDLED   /* */
DECL|macro|IRQ_RETVAL
macro_line|#  define IRQ_RETVAL(x) /* */
multiline_comment|/* This is ad-hoc version of scsi_host_get_next() */
DECL|function|scsi_host_get_next
r_static
r_inline
r_struct
id|Scsi_Host
op_star
id|scsi_host_get_next
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
(brace
r_if
c_cond
(paren
id|host
op_eq
l_int|NULL
)paren
(brace
r_return
id|scsi_hostlist
suffix:semicolon
)brace
r_else
(brace
r_return
id|host-&gt;next
suffix:semicolon
)brace
)brace
multiline_comment|/* This is ad-hoc version of scsi_host_hn_get() */
DECL|function|scsi_host_hn_get
r_static
r_inline
r_struct
id|Scsi_Host
op_star
id|scsi_host_hn_get
c_func
(paren
r_int
r_int
id|hostno
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
r_for
c_loop
(paren
id|host
op_assign
id|scsi_host_get_next
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|host
op_ne
l_int|NULL
suffix:semicolon
id|host
op_assign
id|scsi_host_get_next
c_func
(paren
id|host
)paren
)paren
(brace
r_if
c_cond
(paren
id|host-&gt;host_no
op_eq
id|hostno
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_return
id|host
suffix:semicolon
)brace
DECL|function|cs_error
r_static
r_void
id|cs_error
c_func
(paren
id|client_handle_t
id|handle
comma
r_int
id|func
comma
r_int
id|ret
)paren
(brace
id|error_info_t
id|err
op_assign
(brace
id|func
comma
id|ret
)brace
suffix:semicolon
id|CardServices
c_func
(paren
id|ReportError
comma
id|handle
comma
op_amp
id|err
)paren
suffix:semicolon
)brace
multiline_comment|/* scatter-gather table */
DECL|macro|BUFFER_ADDR
macro_line|#  define BUFFER_ADDR (SCpnt-&gt;SCp.buffer-&gt;address)
macro_line|#endif
multiline_comment|/* for Kernel 2.6 */
macro_line|#if (LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,6,0))
multiline_comment|/* scatter-gather table */
DECL|macro|BUFFER_ADDR
macro_line|#  define BUFFER_ADDR ((char *)((unsigned int)(SCpnt-&gt;SCp.buffer-&gt;page) + SCpnt-&gt;SCp.buffer-&gt;offset))
macro_line|#endif
macro_line|#endif  /*__nsp_cs__*/
multiline_comment|/* end */
eof
