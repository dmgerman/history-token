multiline_comment|/*=======================================================/&n;  Header file for nsp_cs.c&n;      By: YOKOTA Hiroshi &lt;yokota@netlab.is.tsukuba.ac.jp&gt;&n;&n;    Ver.1.0 : Cut unused lines.&n;    Ver 0.1 : Initial version.&n;&n;    This software may be used and distributed according to the terms of&n;    the GNU General Public License.&n;&n;=========================================================*/
multiline_comment|/* $Id: nsp_cs.h,v 1.27 2001/09/10 10:31:13 elca Exp $ */
macro_line|#ifndef  __nsp_cs__
DECL|macro|__nsp_cs__
mdefine_line|#define  __nsp_cs__
multiline_comment|/* for debugging */
multiline_comment|/*#define PCMCIA_DEBUG 9*/
multiline_comment|/*&n;#define static&n;#define inline&n;*/
multiline_comment|/************************************&n; * Some useful macros...&n; */
DECL|macro|Number
mdefine_line|#define Number(arr) ((int) (sizeof(arr) / sizeof(arr[0])))
DECL|macro|BIT
mdefine_line|#define BIT(x)      (1&lt;&lt;(x))
DECL|macro|MIN
mdefine_line|#define MIN(a,b)    ((a) &gt; (b) ? (b) : (a))
multiline_comment|/* SCSI initiator must be 7 */
DECL|macro|SCSI_INITIATOR_ID
mdefine_line|#define SCSI_INITIATOR_ID  7
DECL|macro|NSP_SELTIMEOUT
mdefine_line|#define NSP_SELTIMEOUT 200
multiline_comment|/* base register */
DECL|macro|IRQCONTROL
mdefine_line|#define&t;IRQCONTROL&t;0x00
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
macro_line|#  define IRQCONTROL_ALLCLEAR           0x0f
DECL|macro|IRQCONTROL_IRQDISABLE
macro_line|#  define IRQCONTROL_IRQDISABLE         0xf0
DECL|macro|IRQSTATUS
mdefine_line|#define&t;IRQSTATUS&t;0x00
DECL|macro|IRQSTATUS_SCSI
macro_line|#  define IRQSTATUS_SCSI  BIT(0)
DECL|macro|IRQSTATUS_TIMER
macro_line|#  define IRQSTATUS_TIMER BIT(2)
DECL|macro|IRQSTATUS_FIFO
macro_line|#  define IRQSTATUS_FIFO  BIT(3)
DECL|macro|IRQSTATUS_MASK
macro_line|#  define IRQSTATUS_MASK  0x0f
DECL|macro|IFSELECT
mdefine_line|#define&t;IFSELECT&t;0x01
DECL|macro|IF_IFSEL
macro_line|#  define IF_IFSEL    BIT(0)
DECL|macro|IF_REGSEL
macro_line|#  define IF_REGSEL   BIT(2)
DECL|macro|FIFOSTATUS
mdefine_line|#define&t;FIFOSTATUS&t;0x01
DECL|macro|FIFOSTATUS_CHIP_REVISION
macro_line|#  define FIFOSTATUS_CHIP_REVISION 0x0f
DECL|macro|FIFOSTATUS_CHIP_ID
macro_line|#  define FIFOSTATUS_CHIP_ID       0x70
DECL|macro|FIFOSTATUS_FULL_EMPTY
macro_line|#  define FIFOSTATUS_FULL_EMPTY    0x80
DECL|macro|INDEXREG
mdefine_line|#define&t;INDEXREG&t;0x02
DECL|macro|DATAREG
mdefine_line|#define&t;DATAREG&t;&t;0x03
DECL|macro|FIFODATA
mdefine_line|#define&t;FIFODATA&t;0x04
DECL|macro|FIFODATA1
mdefine_line|#define&t;FIFODATA1&t;0x05
DECL|macro|FIFODATA2
mdefine_line|#define&t;FIFODATA2&t;0x06
DECL|macro|FIFODATA3
mdefine_line|#define&t;FIFODATA3&t;0x07
multiline_comment|/* indexed register */
DECL|macro|EXTBUSCTRL
mdefine_line|#define EXTBUSCTRL&t;0x10
DECL|macro|CLOCKDIV
mdefine_line|#define CLOCKDIV&t;0x11
DECL|macro|CLOCK_40M
macro_line|#  define CLOCK_40M 0x02
DECL|macro|CLOCK_20M
macro_line|#  define CLOCK_20M 0x01
DECL|macro|TERMPWRCTRL
mdefine_line|#define TERMPWRCTRL&t;0x13
DECL|macro|POWER_ON
macro_line|#  define POWER_ON BIT(0)
DECL|macro|SCSIIRQMODE
mdefine_line|#define SCSIIRQMODE&t;0x15
DECL|macro|SCSI_PHASE_CHANGE_EI
macro_line|#  define SCSI_PHASE_CHANGE_EI BIT(0)
DECL|macro|RESELECT_EI
macro_line|#  define RESELECT_EI          BIT(4)
DECL|macro|FIFO_IRQ_EI
macro_line|#  define FIFO_IRQ_EI          BIT(5)
DECL|macro|SCSI_RESET_IRQ_EI
macro_line|#  define SCSI_RESET_IRQ_EI    BIT(6)
DECL|macro|IRQPHASESENCE
mdefine_line|#define IRQPHASESENCE&t;0x16
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
mdefine_line|#define TIMERCOUNT&t;0x17
DECL|macro|SCSIBUSCTRL
mdefine_line|#define SCSIBUSCTRL&t;0x18
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
mdefine_line|#define SCSIBUSMON&t;0x19
DECL|macro|SETARBIT
mdefine_line|#define SETARBIT&t;0x1A
DECL|macro|ARBIT_GO
macro_line|#  define ARBIT_GO         BIT(0)
DECL|macro|ARBIT_FLAG_CLEAR
macro_line|#  define ARBIT_FLAG_CLEAR BIT(1)
DECL|macro|ARBITSTATUS
mdefine_line|#define ARBITSTATUS&t;0x1A
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
mdefine_line|#define RESELECTID&t;0x1C  /* R */
DECL|macro|COMMANDDATA
mdefine_line|#define COMMANDDATA&t;0x1D
DECL|macro|POINTERCLR
mdefine_line|#define POINTERCLR&t;0x1E  /* W */
DECL|macro|POINTER_CLEAR
macro_line|#  define POINTER_CLEAR      BIT(0)
DECL|macro|ACK_COUNTER_CLEAR
macro_line|#  define ACK_COUNTER_CLEAR  BIT(1)
DECL|macro|REQ_COUNTER_CLEAR
macro_line|#  define REQ_COUNTER_CLEAR  BIT(2)
DECL|macro|HOST_COUNTER_CLEAR
macro_line|#  define HOST_COUNTER_CLEAR BIT(3)
DECL|macro|READ_SOURCE
macro_line|#  define READ_SOURCE        0x30
DECL|macro|TRANSFERCOUNT
mdefine_line|#define TRANSFERCOUNT&t;0x1E  /* R */
DECL|macro|TRANSFERMODE
mdefine_line|#define TRANSFERMODE&t;0x20
DECL|macro|MODE_MEM8
macro_line|#   define MODE_MEM8   BIT(0)
DECL|macro|MODE_MEM32
macro_line|#   define MODE_MEM32  BIT(1)
DECL|macro|MODE_ADR24
macro_line|#   define MODE_ADR24  BIT(2)
DECL|macro|MODE_ADR32
macro_line|#   define MODE_ADR32  BIT(3)
DECL|macro|MODE_IO8
macro_line|#   define MODE_IO8    BIT(4)
DECL|macro|MODE_IO32
macro_line|#   define MODE_IO32   BIT(5)
DECL|macro|TRANSFER_GO
macro_line|#   define TRANSFER_GO BIT(6)
DECL|macro|BRAIND
macro_line|#   define BRAIND      BIT(7)
DECL|macro|SYNCREG
mdefine_line|#define SYNCREG&t;&t;0x21
DECL|macro|SYNCREG_OFFSET_MASK
macro_line|#  define SYNCREG_OFFSET_MASK  0x0f
DECL|macro|SYNCREG_PERIOD_MASK
macro_line|#  define SYNCREG_PERIOD_MASK  0xf0
DECL|macro|SYNCREG_PERIOD_SHIFT
macro_line|#  define SYNCREG_PERIOD_SHIFT 4
DECL|macro|SCSIDATALATCH
mdefine_line|#define SCSIDATALATCH&t;0x22
DECL|macro|SCSIDATAIN
mdefine_line|#define SCSIDATAIN&t;0x22
DECL|macro|SCSIDATAWITHACK
mdefine_line|#define SCSIDATAWITHACK&t;0x23
DECL|macro|SCAMCONTROL
mdefine_line|#define SCAMCONTROL&t;0x24
DECL|macro|SCAMSTATUS
mdefine_line|#define SCAMSTATUS&t;0x24
DECL|macro|SCAMDATA
mdefine_line|#define SCAMDATA&t;0x25
DECL|macro|OTHERCONTROL
mdefine_line|#define OTHERCONTROL&t;0x26
DECL|macro|TPL_ROM_WRITE_EN
macro_line|#  define TPL_ROM_WRITE_EN BIT(0)
DECL|macro|TPWR_OUT
macro_line|#  define TPWR_OUT         BIT(1)
DECL|macro|TPWR_SENSE
macro_line|#  define TPWR_SENSE       BIT(2)
DECL|macro|RA8_CONTROL
macro_line|#  define RA8_CONTROL      BIT(3)
DECL|macro|ACKWIDTH
mdefine_line|#define ACKWIDTH&t;0x27
DECL|macro|CLRTESTPNT
mdefine_line|#define CLRTESTPNT&t;0x28
DECL|macro|ACKCNTLD
mdefine_line|#define ACKCNTLD&t;0x29
DECL|macro|REQCNTLD
mdefine_line|#define REQCNTLD&t;0x2A
DECL|macro|HSTCNTLD
mdefine_line|#define HSTCNTLD&t;0x2B
DECL|macro|CHECKSUM
mdefine_line|#define CHECKSUM&t;0x2C
multiline_comment|/*&n; * Input status bit definitions.&n; */
DECL|macro|S_ATN
mdefine_line|#define S_ATN&t;&t;0x80&t;/**/
DECL|macro|S_SELECT
mdefine_line|#define S_SELECT&t;0x40&t;/**/
DECL|macro|S_REQUEST
mdefine_line|#define S_REQUEST&t;0x20    /* Request line from SCSI bus*/
DECL|macro|S_ACK
mdefine_line|#define S_ACK&t;&t;0x10    /* Acknowlege line from SCSI bus*/
DECL|macro|S_BUSY
mdefine_line|#define S_BUSY&t;&t;0x08    /* Busy line from SCSI bus*/
DECL|macro|S_CD
mdefine_line|#define S_CD&t;&t;0x04    /* Command/Data line from SCSI bus*/
DECL|macro|S_IO
mdefine_line|#define S_IO&t;&t;0x02    /* Input/Output line from SCSI bus*/
DECL|macro|S_MESSAGE
mdefine_line|#define S_MESSAGE&t;0x01    /* Message line from SCSI bus*/
multiline_comment|/*&n; * Useful Bus Monitor status combinations.&n; */
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
mdefine_line|#define BUSMON_COMMAND     ( S_BUSY | S_CD | S_REQUEST )
DECL|macro|BUSMON_MESSAGE_IN
mdefine_line|#define BUSMON_MESSAGE_IN  ( S_BUSY | S_MESSAGE | S_IO | S_CD | S_REQUEST )
DECL|macro|BUSMON_MESSAGE_OUT
mdefine_line|#define BUSMON_MESSAGE_OUT ( S_BUSY | S_MESSAGE | S_CD | S_REQUEST )
DECL|macro|BUSMON_DATA_IN
mdefine_line|#define BUSMON_DATA_IN     ( S_BUSY | S_IO | S_REQUEST )
DECL|macro|BUSMON_DATA_OUT
mdefine_line|#define BUSMON_DATA_OUT    ( S_BUSY | S_REQUEST )
DECL|macro|BUSMON_STATUS
mdefine_line|#define BUSMON_STATUS      ( S_BUSY | S_IO | S_CD | S_REQUEST )
DECL|macro|BUSMON_RESELECT
mdefine_line|#define BUSMON_RESELECT    ( S_SELECT | S_IO )
DECL|macro|BUSMON_PHASE_MASK
mdefine_line|#define BUSMON_PHASE_MASK  ( S_SELECT | S_CD | S_MESSAGE | S_IO )
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
DECL|macro|BUSPHASE_SELECT
mdefine_line|#define BUSPHASE_SELECT      ( S_SELECT | S_IO )
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
DECL|struct|_nsp_data
r_typedef
r_struct
id|_nsp_data
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
DECL|member|FifoCount
r_int
id|FifoCount
suffix:semicolon
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,4,0))
DECL|member|Residual
r_int
id|Residual
suffix:semicolon
DECL|macro|RESID
mdefine_line|#define RESID data-&gt;Residual
macro_line|#else
DECL|macro|RESID
mdefine_line|#define RESID SCpnt-&gt;resid
macro_line|#endif
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
DECL|macro|N_LUN
mdefine_line|#define N_LUN    8
DECL|member|Sync
id|sync_data
id|Sync
(braket
id|N_TARGET
)braket
(braket
id|N_LUN
)braket
suffix:semicolon
DECL|typedef|nsp_hw_data
)brace
id|nsp_hw_data
suffix:semicolon
r_static
r_void
id|nsp_cs_release
c_func
(paren
id|u_long
id|arg
)paren
suffix:semicolon
r_static
r_int
id|nsp_cs_event
c_func
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
r_static
id|dev_link_t
op_star
id|nsp_cs_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|nsp_cs_detach
c_func
(paren
id|dev_link_t
op_star
)paren
suffix:semicolon
r_static
r_int
r_int
id|nsphw_start_selection
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
id|nsp_hw_data
op_star
id|data
)paren
suffix:semicolon
r_static
r_void
id|nsp_start_timer
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
id|nsp_hw_data
op_star
id|data
comma
r_int
id|time
)paren
suffix:semicolon
r_static
r_int
id|nsp_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_static
r_int
id|nsp_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shpnt
)paren
suffix:semicolon
r_static
r_const
r_char
op_star
id|nsp_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shpnt
)paren
suffix:semicolon
r_static
r_int
id|nsp_queuecommand
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_static
r_int
id|nsp_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|nsp_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_int
id|nsp_eh_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|nsp_eh_device_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|nsp_eh_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|nsp_eh_host_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_int
id|nsp_fifo_count
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_static
r_void
id|nsp_pio_read
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
id|nsp_hw_data
op_star
id|data
)paren
suffix:semicolon
r_static
r_int
id|nsp_nexus
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
id|nsp_hw_data
op_star
id|data
)paren
suffix:semicolon
macro_line|#ifdef PCMCIA_DEBUG
r_static
r_void
id|show_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|ptr
)paren
suffix:semicolon
r_static
r_void
id|show_phase
c_func
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
c_func
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
multiline_comment|/* SCSI messaage */
DECL|macro|MSG_COMMAND_COMPLETE
mdefine_line|#define MSG_COMMAND_COMPLETE 0x00
DECL|macro|MSG_EXTENDED
mdefine_line|#define MSG_EXTENDED         0x01
DECL|macro|MSG_NO_OPERATION
mdefine_line|#define MSG_NO_OPERATION     0x08
DECL|macro|MSG_EXT_SDTR
mdefine_line|#define MSG_EXT_SDTR         0x01
macro_line|#endif  /*__nsp_cs__*/
eof
