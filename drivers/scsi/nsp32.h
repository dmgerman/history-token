multiline_comment|/*&n; * Workbit NinjaSCSI-32Bi/UDE PCI/CardBus SCSI Host Bus Adapter driver&n; * Basic data header&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n;*/
macro_line|#ifndef _NSP32_H
DECL|macro|_NSP32_H
mdefine_line|#define _NSP32_H
singleline_comment|//#define NSP32_DEBUG 9
multiline_comment|/*&n; * VENDOR/DEVICE ID&n; */
DECL|macro|PCI_VENDOR_ID_IODATA
mdefine_line|#define PCI_VENDOR_ID_IODATA  0x10fc
DECL|macro|PCI_VENDOR_ID_WORKBIT
mdefine_line|#define PCI_VENDOR_ID_WORKBIT 0x1145
DECL|macro|PCI_DEVICE_ID_NINJASCSI_32BI_CBSC_II
mdefine_line|#define PCI_DEVICE_ID_NINJASCSI_32BI_CBSC_II   0x0005
DECL|macro|PCI_DEVICE_ID_NINJASCSI_32BI_KME
mdefine_line|#define PCI_DEVICE_ID_NINJASCSI_32BI_KME       0xf007
DECL|macro|PCI_DEVICE_ID_NINJASCSI_32BI_WBT
mdefine_line|#define PCI_DEVICE_ID_NINJASCSI_32BI_WBT       0x8007
DECL|macro|PCI_DEVICE_ID_WORKBIT_STANDARD
mdefine_line|#define PCI_DEVICE_ID_WORKBIT_STANDARD         0xf010
DECL|macro|PCI_DEVICE_ID_WORKBIT_DUALEDGE
mdefine_line|#define PCI_DEVICE_ID_WORKBIT_DUALEDGE         0xf011
DECL|macro|PCI_DEVICE_ID_NINJASCSI_32BI_LOGITEC
mdefine_line|#define PCI_DEVICE_ID_NINJASCSI_32BI_LOGITEC   0xf012
DECL|macro|PCI_DEVICE_ID_NINJASCSI_32BIB_LOGITEC
mdefine_line|#define PCI_DEVICE_ID_NINJASCSI_32BIB_LOGITEC  0xf013
DECL|macro|PCI_DEVICE_ID_NINJASCSI_32UDE_MELCO
mdefine_line|#define PCI_DEVICE_ID_NINJASCSI_32UDE_MELCO    0xf015
DECL|macro|PCI_DEVICE_ID_NINJASCSI_32UDE_MELCO_II
mdefine_line|#define PCI_DEVICE_ID_NINJASCSI_32UDE_MELCO_II 0x8009
multiline_comment|/*&n; * MODEL&n; */
r_enum
(brace
DECL|enumerator|MODEL_IODATA
id|MODEL_IODATA
op_assign
l_int|0
comma
DECL|enumerator|MODEL_KME
id|MODEL_KME
op_assign
l_int|1
comma
DECL|enumerator|MODEL_WORKBIT
id|MODEL_WORKBIT
op_assign
l_int|2
comma
DECL|enumerator|MODEL_LOGITEC
id|MODEL_LOGITEC
op_assign
l_int|3
comma
DECL|enumerator|MODEL_PCI_WORKBIT
id|MODEL_PCI_WORKBIT
op_assign
l_int|4
comma
DECL|enumerator|MODEL_PCI_LOGITEC
id|MODEL_PCI_LOGITEC
op_assign
l_int|5
comma
DECL|enumerator|MODEL_PCI_MELCO
id|MODEL_PCI_MELCO
op_assign
l_int|6
comma
)brace
suffix:semicolon
DECL|variable|nsp32_model
r_static
r_char
op_star
id|nsp32_model
(braket
)braket
op_assign
(brace
l_string|&quot;I-O DATA CBSC-II CardBus card&quot;
comma
l_string|&quot;KME SCSI CardBus card&quot;
comma
l_string|&quot;Workbit duo SCSI CardBus card&quot;
comma
l_string|&quot;Logitec CardBus card with external ROM&quot;
comma
l_string|&quot;Workbit / I-O DATA PCI card&quot;
comma
l_string|&quot;Logitec PCI card with external ROM&quot;
comma
l_string|&quot;Melco CardBus/PCI card with external ROM&quot;
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * SCSI Generic Definitions&n; */
DECL|macro|EXTENDED_SDTR_LEN
mdefine_line|#define EXTENDED_SDTR_LEN&t;0x03
multiline_comment|/* Little Endian */
DECL|typedef|u32_le
r_typedef
id|u32
id|u32_le
suffix:semicolon
DECL|typedef|u16_le
r_typedef
id|u16
id|u16_le
suffix:semicolon
multiline_comment|/*&n; * MACRO&n; */
DECL|macro|NUMBER
mdefine_line|#define NUMBER(arr) ((int) (sizeof(arr) / sizeof(arr[0])))
DECL|macro|BIT
mdefine_line|#define BIT(x)      (1UL &lt;&lt; (x))
macro_line|#ifndef MIN
DECL|macro|MIN
macro_line|# define MIN(a,b)   ((a) &gt; (b) ? (b) : (a))
macro_line|#endif
multiline_comment|/*&n; * BASIC Definitions&n; */
macro_line|#ifndef TRUE
DECL|macro|TRUE
macro_line|# define TRUE  1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
macro_line|# define FALSE 0
macro_line|#endif
DECL|macro|ASSERT
mdefine_line|#define ASSERT 1
DECL|macro|NEGATE
mdefine_line|#define NEGATE 0
multiline_comment|/*******************/
multiline_comment|/* normal register */
multiline_comment|/*******************/
multiline_comment|/*&n; * Don&squot;t access below register with Double Word:&n; * +00, +04, +08, +0c, +64, +80, +84, +88, +90, +c4, +c8, +cc, +d0.&n; */
DECL|macro|IRQ_CONTROL
mdefine_line|#define IRQ_CONTROL 0x00&t;/* BASE+00, W, W */
DECL|macro|IRQ_STATUS
mdefine_line|#define IRQ_STATUS  0x00&t;/* BASE+00, W, R */
DECL|macro|IRQSTATUS_LATCHED_MSG
macro_line|# define IRQSTATUS_LATCHED_MSG      BIT(0)
DECL|macro|IRQSTATUS_LATCHED_IO
macro_line|# define IRQSTATUS_LATCHED_IO       BIT(1)
DECL|macro|IRQSTATUS_LATCHED_CD
macro_line|# define IRQSTATUS_LATCHED_CD       BIT(2)
DECL|macro|IRQSTATUS_LATCHED_BUS_FREE
macro_line|# define IRQSTATUS_LATCHED_BUS_FREE BIT(3)
DECL|macro|IRQSTATUS_RESELECT_OCCUER
macro_line|# define IRQSTATUS_RESELECT_OCCUER  BIT(4)
DECL|macro|IRQSTATUS_PHASE_CHANGE_IRQ
macro_line|# define IRQSTATUS_PHASE_CHANGE_IRQ BIT(5)
DECL|macro|IRQSTATUS_SCSIRESET_IRQ
macro_line|# define IRQSTATUS_SCSIRESET_IRQ    BIT(6)
DECL|macro|IRQSTATUS_TIMER_IRQ
macro_line|# define IRQSTATUS_TIMER_IRQ        BIT(7)
DECL|macro|IRQSTATUS_FIFO_SHLD_IRQ
macro_line|# define IRQSTATUS_FIFO_SHLD_IRQ    BIT(8)
DECL|macro|IRQSTATUS_PCI_IRQ
macro_line|# define IRQSTATUS_PCI_IRQ&t;    BIT(9)
DECL|macro|IRQSTATUS_BMCNTERR_IRQ
macro_line|# define IRQSTATUS_BMCNTERR_IRQ     BIT(10)
DECL|macro|IRQSTATUS_AUTOSCSI_IRQ
macro_line|# define IRQSTATUS_AUTOSCSI_IRQ     BIT(11)
DECL|macro|PCI_IRQ_MASK
macro_line|# define PCI_IRQ_MASK               BIT(12)
DECL|macro|TIMER_IRQ_MASK
macro_line|# define TIMER_IRQ_MASK             BIT(13)
DECL|macro|FIFO_IRQ_MASK
macro_line|# define FIFO_IRQ_MASK              BIT(14)
DECL|macro|SCSI_IRQ_MASK
macro_line|# define SCSI_IRQ_MASK              BIT(15)
DECL|macro|IRQ_CONTROL_ALL_IRQ_MASK
macro_line|# define IRQ_CONTROL_ALL_IRQ_MASK   (PCI_IRQ_MASK   | &bslash;&n;                                     TIMER_IRQ_MASK | &bslash;&n;                                     FIFO_IRQ_MASK  | &bslash;&n;                                     SCSI_IRQ_MASK  )
DECL|macro|IRQSTATUS_ANY_IRQ
macro_line|# define IRQSTATUS_ANY_IRQ          (IRQSTATUS_RESELECT_OCCUER&t;| &bslash;&n;&t;&t;&t;&t;     IRQSTATUS_PHASE_CHANGE_IRQ&t;| &bslash;&n;&t;&t;&t;&t;     IRQSTATUS_SCSIRESET_IRQ&t;| &bslash;&n;&t;&t;&t;&t;     IRQSTATUS_TIMER_IRQ&t;| &bslash;&n;&t;&t;&t;&t;     IRQSTATUS_FIFO_SHLD_IRQ&t;| &bslash;&n;&t;&t;&t;&t;     IRQSTATUS_PCI_IRQ&t;&t;| &bslash;&n;&t;&t;&t;&t;     IRQSTATUS_BMCNTERR_IRQ&t;| &bslash;&n;&t;&t;&t;&t;     IRQSTATUS_AUTOSCSI_IRQ&t;)
DECL|macro|TRANSFER_CONTROL
mdefine_line|#define TRANSFER_CONTROL&t;0x02&t;/* BASE+02, W, W */
DECL|macro|TRANSFER_STATUS
mdefine_line|#define TRANSFER_STATUS&t;&t;0x02&t;/* BASE+02, W, R */
DECL|macro|CB_MMIO_MODE
macro_line|# define CB_MMIO_MODE        BIT(0)
DECL|macro|CB_IO_MODE
macro_line|# define CB_IO_MODE          BIT(1)
DECL|macro|BM_TEST
macro_line|# define BM_TEST             BIT(2)
DECL|macro|BM_TEST_DIR
macro_line|# define BM_TEST_DIR         BIT(3)
DECL|macro|DUAL_EDGE_ENABLE
macro_line|# define DUAL_EDGE_ENABLE    BIT(4)
DECL|macro|NO_TRANSFER_TO_HOST
macro_line|# define NO_TRANSFER_TO_HOST BIT(5)
DECL|macro|TRANSFER_GO
macro_line|# define TRANSFER_GO         BIT(7)
DECL|macro|BLIEND_MODE
macro_line|# define BLIEND_MODE         BIT(8)
DECL|macro|BM_START
macro_line|# define BM_START            BIT(9)
DECL|macro|ADVANCED_BM_WRITE
macro_line|# define ADVANCED_BM_WRITE   BIT(10)
DECL|macro|BM_SINGLE_MODE
macro_line|# define BM_SINGLE_MODE      BIT(11)
DECL|macro|FIFO_TRUE_FULL
macro_line|# define FIFO_TRUE_FULL      BIT(12)
DECL|macro|FIFO_TRUE_EMPTY
macro_line|# define FIFO_TRUE_EMPTY     BIT(13)
DECL|macro|ALL_COUNTER_CLR
macro_line|# define ALL_COUNTER_CLR     BIT(14)
DECL|macro|FIFOTEST
macro_line|# define FIFOTEST            BIT(15)
DECL|macro|INDEX_REG
mdefine_line|#define INDEX_REG&t;&t;0x04&t;/* BASE+04, Byte(R/W), Word(R) */
DECL|macro|TIMER_SET
mdefine_line|#define TIMER_SET&t;&t;0x06&t;/* BASE+06, W, R/W */
DECL|macro|TIMER_CNT_MASK
macro_line|# define TIMER_CNT_MASK (0xff)
DECL|macro|TIMER_STOP
macro_line|# define TIMER_STOP     BIT(8)
DECL|macro|DATA_REG_LOW
mdefine_line|#define DATA_REG_LOW&t;&t;0x08&t;/* BASE+08, LowW, R/W */
DECL|macro|DATA_REG_HI
mdefine_line|#define DATA_REG_HI&t;&t;0x0a&t;/* BASE+0a, Hi-W, R/W */
DECL|macro|FIFO_REST_CNT
mdefine_line|#define FIFO_REST_CNT&t;&t;0x0c&t;/* BASE+0c, W, R/W */
DECL|macro|FIFO_REST_MASK
macro_line|# define FIFO_REST_MASK       0x1ff
DECL|macro|FIFO_EMPTY_SHLD_FLAG
macro_line|# define FIFO_EMPTY_SHLD_FLAG BIT(14)
DECL|macro|FIFO_FULL_SHLD_FLAG
macro_line|# define FIFO_FULL_SHLD_FLAG  BIT(15)
DECL|macro|SREQ_SMPL_RATE
mdefine_line|#define SREQ_SMPL_RATE&t;&t;0x0f&t;/* BASE+0f, B, R/W */
DECL|macro|SREQSMPLRATE_RATE0
macro_line|# define SREQSMPLRATE_RATE0 BIT(0)
DECL|macro|SREQSMPLRATE_RATE1
macro_line|# define SREQSMPLRATE_RATE1 BIT(1)
DECL|macro|SAMPLING_ENABLE
macro_line|# define SAMPLING_ENABLE    BIT(2)
DECL|macro|SMPL_40M
macro_line|#  define SMPL_40M (0)                   /* 40MHz:   0-100ns/period */
DECL|macro|SMPL_20M
macro_line|#  define SMPL_20M (SREQSMPLRATE_RATE0)  /* 20MHz: 100-200ns/period */
DECL|macro|SMPL_10M
macro_line|#  define SMPL_10M (SREQSMPLRATE_RATE1)  /* 10Mhz: 200-   ns/period */
DECL|macro|SCSI_BUS_CONTROL
mdefine_line|#define SCSI_BUS_CONTROL&t;0x10&t;/* BASE+10, B, R/W */
DECL|macro|BUSCTL_SEL
macro_line|# define BUSCTL_SEL         BIT(0)
DECL|macro|BUSCTL_RST
macro_line|# define BUSCTL_RST         BIT(1)
DECL|macro|BUSCTL_DATAOUT_ENB
macro_line|# define BUSCTL_DATAOUT_ENB BIT(2)
DECL|macro|BUSCTL_ATN
macro_line|# define BUSCTL_ATN         BIT(3)
DECL|macro|BUSCTL_ACK
macro_line|# define BUSCTL_ACK         BIT(4)
DECL|macro|BUSCTL_BSY
macro_line|# define BUSCTL_BSY         BIT(5)
DECL|macro|AUTODIRECTION
macro_line|# define AUTODIRECTION      BIT(6)
DECL|macro|ACKENB
macro_line|# define ACKENB             BIT(7)
DECL|macro|CLR_COUNTER
mdefine_line|#define CLR_COUNTER&t;&t;0x12&t;/* BASE+12, B, W */
DECL|macro|ACK_COUNTER_CLR
macro_line|# define ACK_COUNTER_CLR       BIT(0)
DECL|macro|SREQ_COUNTER_CLR
macro_line|# define SREQ_COUNTER_CLR      BIT(1)
DECL|macro|FIFO_HOST_POINTER_CLR
macro_line|# define FIFO_HOST_POINTER_CLR BIT(2)
DECL|macro|FIFO_REST_COUNT_CLR
macro_line|# define FIFO_REST_COUNT_CLR   BIT(3)
DECL|macro|BM_COUNTER_CLR
macro_line|# define BM_COUNTER_CLR        BIT(4)
DECL|macro|SAVED_ACK_CLR
macro_line|# define SAVED_ACK_CLR         BIT(5)
DECL|macro|CLRCOUNTER_ALLMASK
macro_line|# define CLRCOUNTER_ALLMASK    (ACK_COUNTER_CLR       | &bslash;&n;                                SREQ_COUNTER_CLR      | &bslash;&n;                                FIFO_HOST_POINTER_CLR | &bslash;&n;                                FIFO_REST_COUNT_CLR   | &bslash;&n;                                BM_COUNTER_CLR        | &bslash;&n;                                SAVED_ACK_CLR         )
DECL|macro|SCSI_BUS_MONITOR
mdefine_line|#define SCSI_BUS_MONITOR&t;0x12&t;/* BASE+12, B, R */
DECL|macro|BUSMON_MSG
macro_line|# define BUSMON_MSG BIT(0)
DECL|macro|BUSMON_IO
macro_line|# define BUSMON_IO  BIT(1)
DECL|macro|BUSMON_CD
macro_line|# define BUSMON_CD  BIT(2)
DECL|macro|BUSMON_BSY
macro_line|# define BUSMON_BSY BIT(3)
DECL|macro|BUSMON_ACK
macro_line|# define BUSMON_ACK BIT(4)
DECL|macro|BUSMON_REQ
macro_line|# define BUSMON_REQ BIT(5)
DECL|macro|BUSMON_SEL
macro_line|# define BUSMON_SEL BIT(6)
DECL|macro|BUSMON_ATN
macro_line|# define BUSMON_ATN BIT(7)
DECL|macro|COMMAND_DATA
mdefine_line|#define COMMAND_DATA&t;&t;0x14&t;/* BASE+14, B, R/W */
DECL|macro|PARITY_CONTROL
mdefine_line|#define PARITY_CONTROL&t;&t;0x16&t;/* BASE+16, B, W */
DECL|macro|PARITY_CHECK_ENABLE
macro_line|# define PARITY_CHECK_ENABLE BIT(0)
DECL|macro|PARITY_ERROR_CLEAR
macro_line|# define PARITY_ERROR_CLEAR  BIT(1)
DECL|macro|PARITY_STATUS
mdefine_line|#define PARITY_STATUS&t;&t;0x16&t;/* BASE+16, B, R */
singleline_comment|//# define PARITY_CHECK_ENABLE BIT(0)
DECL|macro|PARITY_ERROR_NORMAL
macro_line|# define PARITY_ERROR_NORMAL BIT(1)
DECL|macro|PARITY_ERROR_LSB
macro_line|# define PARITY_ERROR_LSB    BIT(1)
DECL|macro|PARITY_ERROR_MSB
macro_line|# define PARITY_ERROR_MSB    BIT(2)
DECL|macro|RESELECT_ID
mdefine_line|#define RESELECT_ID&t;&t;0x18&t;/* BASE+18, B, R */
DECL|macro|COMMAND_CONTROL
mdefine_line|#define COMMAND_CONTROL&t;&t;0x18&t;/* BASE+18, W, W */
DECL|macro|CLEAR_CDB_FIFO_POINTER
macro_line|# define CLEAR_CDB_FIFO_POINTER BIT(0)
DECL|macro|AUTO_COMMAND_PHASE
macro_line|# define AUTO_COMMAND_PHASE     BIT(1)
DECL|macro|AUTOSCSI_START
macro_line|# define AUTOSCSI_START         BIT(2)
DECL|macro|AUTOSCSI_RESTART
macro_line|# define AUTOSCSI_RESTART       BIT(3)
DECL|macro|AUTO_PARAMETER
macro_line|# define AUTO_PARAMETER         BIT(4)
DECL|macro|AUTO_ATN
macro_line|# define AUTO_ATN               BIT(5)
DECL|macro|AUTO_MSGIN_00_OR_04
macro_line|# define AUTO_MSGIN_00_OR_04    BIT(6)
DECL|macro|AUTO_MSGIN_02
macro_line|# define AUTO_MSGIN_02          BIT(7)
DECL|macro|AUTO_MSGIN_03
macro_line|# define AUTO_MSGIN_03          BIT(8)
DECL|macro|SET_ARBIT
mdefine_line|#define SET_ARBIT&t;&t;0x1a&t;/* BASE+1a, B, W */
DECL|macro|ARBIT_GO
macro_line|# define ARBIT_GO    BIT(0)
DECL|macro|ARBIT_CLEAR
macro_line|# define ARBIT_CLEAR BIT(1)
DECL|macro|ARBIT_STATUS
mdefine_line|#define ARBIT_STATUS&t;&t;0x1a&t;/* BASE+1a, B, R */
singleline_comment|//# define ARBIT_GO             BIT(0)
DECL|macro|ARBIT_WIN
macro_line|# define ARBIT_WIN            BIT(1)
DECL|macro|ARBIT_FAIL
macro_line|# define ARBIT_FAIL           BIT(2)
DECL|macro|AUTO_PARAMETER_VALID
macro_line|# define AUTO_PARAMETER_VALID BIT(3)
DECL|macro|SGT_VALID
macro_line|# define SGT_VALID            BIT(4)
DECL|macro|SYNC_REG
mdefine_line|#define SYNC_REG&t;&t;0x1c&t;/* BASE+1c, B, R/W */
DECL|macro|ACK_WIDTH
mdefine_line|#define ACK_WIDTH&t;&t;0x1d&t;/* BASE+1d, B, R/W */
DECL|macro|SCSI_DATA_WITH_ACK
mdefine_line|#define SCSI_DATA_WITH_ACK&t;0x20&t;/* BASE+20, B, R/W */
DECL|macro|SCSI_OUT_LATCH_TARGET_ID
mdefine_line|#define SCSI_OUT_LATCH_TARGET_ID 0x22&t;/* BASE+22, B, W */
DECL|macro|SCSI_DATA_IN
mdefine_line|#define SCSI_DATA_IN&t;&t;0x22&t;/* BASE+22, B, R */
DECL|macro|SCAM_CONTROL
mdefine_line|#define SCAM_CONTROL&t;&t;0x24&t;/* BASE+24, B, W */
DECL|macro|SCAM_STATUS
mdefine_line|#define SCAM_STATUS&t;&t;0x24&t;/* BASE+24, B, R */
DECL|macro|SCAM_MSG
macro_line|# define SCAM_MSG    BIT(0)
DECL|macro|SCAM_IO
macro_line|# define SCAM_IO     BIT(1)
DECL|macro|SCAM_CD
macro_line|# define SCAM_CD     BIT(2)
DECL|macro|SCAM_BSY
macro_line|# define SCAM_BSY    BIT(3)
DECL|macro|SCAM_SEL
macro_line|# define SCAM_SEL    BIT(4)
DECL|macro|SCAM_XFEROK
macro_line|# define SCAM_XFEROK BIT(5)
DECL|macro|SCAM_DATA
mdefine_line|#define SCAM_DATA&t;&t;0x26&t;/* BASE+26, B, R/W */
DECL|macro|SD0
macro_line|# define SD0&t;BIT(0)
DECL|macro|SD1
macro_line|# define SD1&t;BIT(1)
DECL|macro|SD2
macro_line|# define SD2&t;BIT(2)
DECL|macro|SD3
macro_line|# define SD3&t;BIT(3)
DECL|macro|SD4
macro_line|# define SD4&t;BIT(4)
DECL|macro|SD5
macro_line|# define SD5&t;BIT(5)
DECL|macro|SD6
macro_line|# define SD6&t;BIT(6)
DECL|macro|SD7
macro_line|# define SD7&t;BIT(7)
DECL|macro|SACK_CNT
mdefine_line|#define SACK_CNT&t;&t;0x28&t;/* BASE+28, DW, R/W */
DECL|macro|SREQ_CNT
mdefine_line|#define SREQ_CNT&t;&t;0x2c&t;/* BASE+2c, DW, R/W */
DECL|macro|FIFO_DATA_LOW
mdefine_line|#define FIFO_DATA_LOW&t;&t;0x30&t;/* BASE+30, B/W/DW, R/W */
DECL|macro|FIFO_DATA_HIGH
mdefine_line|#define FIFO_DATA_HIGH&t;&t;0x32&t;/* BASE+32, B/W, R/W */
DECL|macro|BM_START_ADR
mdefine_line|#define BM_START_ADR&t;&t;0x34&t;/* BASE+34, DW, R/W */
DECL|macro|BM_CNT
mdefine_line|#define BM_CNT&t;&t;&t;0x38&t;/* BASE+38, DW, R/W */
DECL|macro|BM_COUNT_MASK
macro_line|# define BM_COUNT_MASK 0x0001ffffUL
DECL|macro|SGTEND
macro_line|# define SGTEND        BIT(31)      /* Last SGT marker */
DECL|macro|SGT_ADR
mdefine_line|#define SGT_ADR&t;&t;&t;0x3c&t;/* BASE+3c, DW, R/W */
DECL|macro|WAIT_REG
mdefine_line|#define WAIT_REG&t;&t;0x40&t;/* Bi only */
DECL|macro|SCSI_EXECUTE_PHASE
mdefine_line|#define SCSI_EXECUTE_PHASE&t;0x40&t;/* BASE+40, W, R */
DECL|macro|COMMAND_PHASE
macro_line|# define COMMAND_PHASE     BIT(0)
DECL|macro|DATA_IN_PHASE
macro_line|# define DATA_IN_PHASE     BIT(1)
DECL|macro|DATA_OUT_PHASE
macro_line|# define DATA_OUT_PHASE    BIT(2)
DECL|macro|MSGOUT_PHASE
macro_line|# define MSGOUT_PHASE      BIT(3)
DECL|macro|STATUS_PHASE
macro_line|# define STATUS_PHASE      BIT(4)
DECL|macro|ILLEGAL_PHASE
macro_line|# define ILLEGAL_PHASE     BIT(5)
DECL|macro|BUS_FREE_OCCUER
macro_line|# define BUS_FREE_OCCUER   BIT(6)
DECL|macro|MSG_IN_OCCUER
macro_line|# define MSG_IN_OCCUER     BIT(7)
DECL|macro|MSG_OUT_OCCUER
macro_line|# define MSG_OUT_OCCUER    BIT(8)
DECL|macro|SELECTION_TIMEOUT
macro_line|# define SELECTION_TIMEOUT BIT(9)
DECL|macro|MSGIN_00_VALID
macro_line|# define MSGIN_00_VALID    BIT(10)
DECL|macro|MSGIN_02_VALID
macro_line|# define MSGIN_02_VALID    BIT(11)
DECL|macro|MSGIN_03_VALID
macro_line|# define MSGIN_03_VALID    BIT(12)
DECL|macro|MSGIN_04_VALID
macro_line|# define MSGIN_04_VALID    BIT(13)
DECL|macro|AUTOSCSI_BUSY
macro_line|# define AUTOSCSI_BUSY     BIT(15)
DECL|macro|SCSI_CSB_IN
mdefine_line|#define SCSI_CSB_IN&t;&t;0x42&t;/* BASE+42, B, R */
DECL|macro|SCSI_MSG_OUT
mdefine_line|#define SCSI_MSG_OUT&t;&t;0x44&t;/* BASE+44, DW, R/W */
DECL|macro|MSGOUT_COUNT_MASK
macro_line|# define MSGOUT_COUNT_MASK (BIT(0)|BIT(1))
DECL|macro|MV_VALID
macro_line|# define MV_VALID&t;    BIT(7)
DECL|macro|SEL_TIME_OUT
mdefine_line|#define SEL_TIME_OUT&t;&t;0x48&t;/* BASE+48, W, R/W */
DECL|macro|SAVED_SACK_CNT
mdefine_line|#define SAVED_SACK_CNT&t;&t;0x4c&t;/* BASE+4c, DW, R */
DECL|macro|HTOSDATADELAY
mdefine_line|#define HTOSDATADELAY&t;&t;0x50&t;/* BASE+50, B, R/W */
DECL|macro|STOHDATADELAY
mdefine_line|#define STOHDATADELAY&t;&t;0x54&t;/* BASE+54, B, R/W */
DECL|macro|ACKSUMCHECKRD
mdefine_line|#define ACKSUMCHECKRD&t;&t;0x58&t;/* BASE+58, W, R */
DECL|macro|REQSUMCHECKRD
mdefine_line|#define REQSUMCHECKRD&t;&t;0x5c&t;/* BASE+5c, W, R */
multiline_comment|/********************/
multiline_comment|/* indexed register */
multiline_comment|/********************/
DECL|macro|CLOCK_DIV
mdefine_line|#define CLOCK_DIV&t;&t;0x00&t;/* BASE+08, IDX+00, B, R/W */
DECL|macro|CLOCK_2
macro_line|# define CLOCK_2  BIT(0)&t;/* MCLK/2 */
DECL|macro|CLOCK_4
macro_line|# define CLOCK_4  BIT(1)&t;/* MCLK/4 */
DECL|macro|PCICLK
macro_line|# define PCICLK&t;  BIT(7)&t;/* PCICLK (33MHz) */
DECL|macro|TERM_PWR_CONTROL
mdefine_line|#define TERM_PWR_CONTROL&t;0x01&t;/* BASE+08, IDX+01, B, R/W */
DECL|macro|BPWR
macro_line|# define BPWR  BIT(0)
DECL|macro|SENSE
macro_line|# define SENSE BIT(1)&t;/* Read Only */
DECL|macro|EXT_PORT_DDR
mdefine_line|#define EXT_PORT_DDR&t;&t;0x02&t;/* BASE+08, IDX+02, B, R/W */
DECL|macro|EXT_PORT
mdefine_line|#define EXT_PORT&t;&t;0x03&t;/* BASE+08, IDX+03, B, R/W */
DECL|macro|LED_ON
macro_line|# define LED_ON&t; (0)
DECL|macro|LED_OFF
macro_line|# define LED_OFF BIT(0)
DECL|macro|IRQ_SELECT
mdefine_line|#define IRQ_SELECT&t;&t;0x04&t;/* BASE+08, IDX+04, W, R/W */
DECL|macro|IRQSELECT_RESELECT_IRQ
macro_line|# define IRQSELECT_RESELECT_IRQ      BIT(0)
DECL|macro|IRQSELECT_PHASE_CHANGE_IRQ
macro_line|# define IRQSELECT_PHASE_CHANGE_IRQ  BIT(1)
DECL|macro|IRQSELECT_SCSIRESET_IRQ
macro_line|# define IRQSELECT_SCSIRESET_IRQ     BIT(2)
DECL|macro|IRQSELECT_TIMER_IRQ
macro_line|# define IRQSELECT_TIMER_IRQ         BIT(3)
DECL|macro|IRQSELECT_FIFO_SHLD_IRQ
macro_line|# define IRQSELECT_FIFO_SHLD_IRQ     BIT(4)
DECL|macro|IRQSELECT_TARGET_ABORT_IRQ
macro_line|# define IRQSELECT_TARGET_ABORT_IRQ  BIT(5)
DECL|macro|IRQSELECT_MASTER_ABORT_IRQ
macro_line|# define IRQSELECT_MASTER_ABORT_IRQ  BIT(6)
DECL|macro|IRQSELECT_SERR_IRQ
macro_line|# define IRQSELECT_SERR_IRQ          BIT(7)
DECL|macro|IRQSELECT_PERR_IRQ
macro_line|# define IRQSELECT_PERR_IRQ          BIT(8)
DECL|macro|IRQSELECT_BMCNTERR_IRQ
macro_line|# define IRQSELECT_BMCNTERR_IRQ      BIT(9)
DECL|macro|IRQSELECT_AUTO_SCSI_SEQ_IRQ
macro_line|# define IRQSELECT_AUTO_SCSI_SEQ_IRQ BIT(10)
DECL|macro|OLD_SCSI_PHASE
mdefine_line|#define OLD_SCSI_PHASE&t;&t;0x05&t;/* BASE+08, IDX+05, B, R */
DECL|macro|OLD_MSG
macro_line|# define OLD_MSG  BIT(0)
DECL|macro|OLD_IO
macro_line|# define OLD_IO   BIT(1)
DECL|macro|OLD_CD
macro_line|# define OLD_CD   BIT(2)
DECL|macro|OLD_BUSY
macro_line|# define OLD_BUSY BIT(3)
DECL|macro|FIFO_FULL_SHLD_COUNT
mdefine_line|#define FIFO_FULL_SHLD_COUNT&t;0x06&t;/* BASE+08, IDX+06, B, R/W */
DECL|macro|FIFO_EMPTY_SHLD_COUNT
mdefine_line|#define FIFO_EMPTY_SHLD_COUNT&t;0x07&t;/* BASE+08, IDX+07, B, R/W */
DECL|macro|EXP_ROM_CONTROL
mdefine_line|#define EXP_ROM_CONTROL&t;&t;0x08&t;/* BASE+08, IDX+08, B, R/W */ /* external ROM control */
DECL|macro|ROM_WRITE_ENB
macro_line|# define ROM_WRITE_ENB BIT(0)
DECL|macro|IO_ACCESS_ENB
macro_line|# define IO_ACCESS_ENB BIT(1)
DECL|macro|ROM_ADR_CLEAR
macro_line|# define ROM_ADR_CLEAR BIT(2)
DECL|macro|EXP_ROM_ADR
mdefine_line|#define EXP_ROM_ADR&t;&t;0x09&t;/* BASE+08, IDX+09, W, R/W */
DECL|macro|EXP_ROM_DATA
mdefine_line|#define EXP_ROM_DATA&t;&t;0x0a&t;/* BASE+08, IDX+0a, B, R/W */
DECL|macro|CHIP_MODE
mdefine_line|#define CHIP_MODE&t;&t;0x0b&t;/* BASE+08, IDX+0b, B, R   */ /* NinjaSCSI-32Bi only */
DECL|macro|OEM0
macro_line|# define OEM0 BIT(1)  /* OEM select */ /* 00=I-O DATA, 01=KME, 10=Workbit, 11=Ext ROM */
DECL|macro|OEM1
macro_line|# define OEM1 BIT(2)  /* OEM select */
DECL|macro|OPTB
macro_line|# define OPTB BIT(3)  /* KME mode select */
DECL|macro|OPTC
macro_line|# define OPTC BIT(4)  /* KME mode select */
DECL|macro|OPTD
macro_line|# define OPTD BIT(5)  /* KME mode select */
DECL|macro|OPTE
macro_line|# define OPTE BIT(6)  /* KME mode select */
DECL|macro|OPTF
macro_line|# define OPTF BIT(7)  /* Power management */
DECL|macro|MISC_WR
mdefine_line|#define MISC_WR&t;&t;&t;0x0c&t;/* BASE+08, IDX+0c, W, R/W */
DECL|macro|MISC_RD
mdefine_line|#define MISC_RD&t;&t;&t;0x0c
DECL|macro|SCSI_DIRECTION_DETECTOR_SELECT
macro_line|# define SCSI_DIRECTION_DETECTOR_SELECT BIT(0)
DECL|macro|SCSI2_HOST_DIRECTION_VALID
macro_line|# define SCSI2_HOST_DIRECTION_VALID&t;BIT(1)&t;/* Read only */
DECL|macro|HOST2_SCSI_DIRECTION_VALID
macro_line|# define HOST2_SCSI_DIRECTION_VALID&t;BIT(2)&t;/* Read only */
DECL|macro|DELAYED_BMSTART
macro_line|# define DELAYED_BMSTART                BIT(3)
DECL|macro|MASTER_TERMINATION_SELECT
macro_line|# define MASTER_TERMINATION_SELECT      BIT(4)
DECL|macro|BMREQ_NEGATE_TIMING_SEL
macro_line|# define BMREQ_NEGATE_TIMING_SEL        BIT(5)
DECL|macro|AUTOSEL_TIMING_SEL
macro_line|# define AUTOSEL_TIMING_SEL             BIT(6)
DECL|macro|MISC_MABORT_MASK
macro_line|# define MISC_MABORT_MASK&t;&t;BIT(7)
DECL|macro|BMSTOP_CHANGE2_NONDATA_PHASE
macro_line|# define BMSTOP_CHANGE2_NONDATA_PHASE&t;BIT(8)
DECL|macro|BM_CYCLE
mdefine_line|#define BM_CYCLE&t;&t;0x0d&t;/* BASE+08, IDX+0d, B, R/W */
DECL|macro|BM_CYCLE0
macro_line|# define BM_CYCLE0&t;&t; BIT(0)
DECL|macro|BM_CYCLE1
macro_line|# define BM_CYCLE1&t;&t; BIT(1)
DECL|macro|BM_FRAME_ASSERT_TIMING
macro_line|# define BM_FRAME_ASSERT_TIMING&t; BIT(2)
DECL|macro|BM_IRDY_ASSERT_TIMING
macro_line|# define BM_IRDY_ASSERT_TIMING&t; BIT(3)
DECL|macro|BM_SINGLE_BUS_MASTER
macro_line|# define BM_SINGLE_BUS_MASTER&t; BIT(4)
DECL|macro|MEMRD_CMD0
macro_line|# define MEMRD_CMD0              BIT(5)
DECL|macro|SGT_AUTO_PARA_MEMED_CMD
macro_line|# define SGT_AUTO_PARA_MEMED_CMD BIT(6)
DECL|macro|MEMRD_CMD1
macro_line|# define MEMRD_CMD1              BIT(7)
DECL|macro|SREQ_EDGH
mdefine_line|#define SREQ_EDGH&t;&t;0x0e&t;/* BASE+08, IDX+0e, B, W */
DECL|macro|SREQ_EDGH_SELECT
macro_line|# define SREQ_EDGH_SELECT BIT(0)
DECL|macro|UP_CNT
mdefine_line|#define UP_CNT&t;&t;&t;0x0f&t;/* BASE+08, IDX+0f, B, W */
DECL|macro|REQCNT_UP
macro_line|# define REQCNT_UP  BIT(0)
DECL|macro|ACKCNT_UP
macro_line|# define ACKCNT_UP  BIT(1)
DECL|macro|BMADR_UP
macro_line|# define BMADR_UP   BIT(4)
DECL|macro|BMCNT_UP
macro_line|# define BMCNT_UP   BIT(5)
DECL|macro|SGT_CNT_UP
macro_line|# define SGT_CNT_UP BIT(7)
DECL|macro|CFG_CMD_STR
mdefine_line|#define CFG_CMD_STR&t;&t;0x10&t;/* BASE+08, IDX+10, W, R */
DECL|macro|CFG_LATE_CACHE
mdefine_line|#define CFG_LATE_CACHE&t;&t;0x11&t;/* BASE+08, IDX+11, W, R/W */
DECL|macro|CFG_BASE_ADR_1
mdefine_line|#define CFG_BASE_ADR_1&t;&t;0x12&t;/* BASE+08, IDX+12, W, R */
DECL|macro|CFG_BASE_ADR_2
mdefine_line|#define CFG_BASE_ADR_2&t;&t;0x13&t;/* BASE+08, IDX+13, W, R */
DECL|macro|CFG_INLINE
mdefine_line|#define CFG_INLINE&t;&t;0x14&t;/* BASE+08, IDX+14, W, R */
DECL|macro|SERIAL_ROM_CTL
mdefine_line|#define SERIAL_ROM_CTL&t;&t;0x15&t;/* BASE+08, IDX+15, B, R */
DECL|macro|SCL
macro_line|# define SCL BIT(0)
DECL|macro|ENA
macro_line|# define ENA BIT(1)
DECL|macro|SDA
macro_line|# define SDA BIT(2)
DECL|macro|FIFO_HST_POINTER
mdefine_line|#define FIFO_HST_POINTER&t;0x16&t;/* BASE+08, IDX+16, B, R/W */
DECL|macro|SREQ_DELAY
mdefine_line|#define SREQ_DELAY&t;&t;0x17&t;/* BASE+08, IDX+17, B, R/W */
DECL|macro|SACK_DELAY
mdefine_line|#define SACK_DELAY&t;&t;0x18&t;/* BASE+08, IDX+18, B, R/W */
DECL|macro|SREQ_NOISE_CANCEL
mdefine_line|#define SREQ_NOISE_CANCEL&t;0x19&t;/* BASE+08, IDX+19, B, R/W */
DECL|macro|SDP_NOISE_CANCEL
mdefine_line|#define SDP_NOISE_CANCEL&t;0x1a&t;/* BASE+08, IDX+1a, B, R/W */
DECL|macro|DELAY_TEST
mdefine_line|#define DELAY_TEST&t;&t;0x1b&t;/* BASE+08, IDX+1b, B, R/W */
DECL|macro|SD0_NOISE_CANCEL
mdefine_line|#define SD0_NOISE_CANCEL&t;0x20&t;/* BASE+08, IDX+20, B, R/W */
DECL|macro|SD1_NOISE_CANCEL
mdefine_line|#define SD1_NOISE_CANCEL&t;0x21&t;/* BASE+08, IDX+21, B, R/W */
DECL|macro|SD2_NOISE_CANCEL
mdefine_line|#define SD2_NOISE_CANCEL&t;0x22&t;/* BASE+08, IDX+22, B, R/W */
DECL|macro|SD3_NOISE_CANCEL
mdefine_line|#define SD3_NOISE_CANCEL&t;0x23&t;/* BASE+08, IDX+23, B, R/W */
DECL|macro|SD4_NOISE_CANCEL
mdefine_line|#define SD4_NOISE_CANCEL&t;0x24&t;/* BASE+08, IDX+24, B, R/W */
DECL|macro|SD5_NOISE_CANCEL
mdefine_line|#define SD5_NOISE_CANCEL&t;0x25&t;/* BASE+08, IDX+25, B, R/W */
DECL|macro|SD6_NOISE_CANCEL
mdefine_line|#define SD6_NOISE_CANCEL&t;0x26&t;/* BASE+08, IDX+26, B, R/W */
DECL|macro|SD7_NOISE_CANCEL
mdefine_line|#define SD7_NOISE_CANCEL&t;0x27&t;/* BASE+08, IDX+27, B, R/W */
multiline_comment|/*&n; * Useful Bus Monitor status combinations.&n; */
DECL|macro|BUSMON_BUS_FREE
mdefine_line|#define BUSMON_BUS_FREE    0
DECL|macro|BUSMON_COMMAND
mdefine_line|#define BUSMON_COMMAND     ( BUSMON_BSY |                          BUSMON_CD | BUSMON_REQ )
DECL|macro|BUSMON_MESSAGE_IN
mdefine_line|#define BUSMON_MESSAGE_IN  ( BUSMON_BSY | BUSMON_MSG | BUSMON_IO | BUSMON_CD | BUSMON_REQ )
DECL|macro|BUSMON_MESSAGE_OUT
mdefine_line|#define BUSMON_MESSAGE_OUT ( BUSMON_BSY | BUSMON_MSG |             BUSMON_CD | BUSMON_REQ )
DECL|macro|BUSMON_DATA_IN
mdefine_line|#define BUSMON_DATA_IN     ( BUSMON_BSY |              BUSMON_IO |             BUSMON_REQ )
DECL|macro|BUSMON_DATA_OUT
mdefine_line|#define BUSMON_DATA_OUT    ( BUSMON_BSY |                                      BUSMON_REQ )
DECL|macro|BUSMON_STATUS
mdefine_line|#define BUSMON_STATUS      ( BUSMON_BSY |              BUSMON_IO | BUSMON_CD | BUSMON_REQ )
DECL|macro|BUSMON_RESELECT
mdefine_line|#define BUSMON_RESELECT    (                           BUSMON_IO                          | BUSMON_SEL)
DECL|macro|BUSMON_PHASE_MASK
mdefine_line|#define BUSMON_PHASE_MASK  (              BUSMON_MSG | BUSMON_IO | BUSMON_CD              | BUSMON_SEL)
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
mdefine_line|#define BUSPHASE_SELECT      ( BUSMON_SEL | BUSMON_IO )
multiline_comment|/************************************************************************&n; * structure for DMA/Scatter Gather list&n; */
DECL|macro|NSP32_SG_SIZE
mdefine_line|#define NSP32_SG_SIZE&t;&t;SG_ALL
DECL|struct|_nsp32_sgtable
r_typedef
r_struct
id|_nsp32_sgtable
(brace
multiline_comment|/* values must be little endian */
DECL|member|addr
id|u32_le
id|addr
suffix:semicolon
multiline_comment|/* transfer address */
DECL|member|len
id|u32_le
id|len
suffix:semicolon
multiline_comment|/* transfer length. BIT(31) is for SGT_END mark */
DECL|typedef|nsp32_sgtable
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|nsp32_sgtable
suffix:semicolon
DECL|struct|_nsp32_sglun
r_typedef
r_struct
id|_nsp32_sglun
(brace
DECL|member|sgt
id|nsp32_sgtable
id|sgt
(braket
id|NSP32_SG_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* SG table */
DECL|typedef|nsp32_sglun
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|nsp32_sglun
suffix:semicolon
DECL|macro|NSP32_SG_TABLE_SIZE
mdefine_line|#define NSP32_SG_TABLE_SIZE (sizeof(nsp32_sgtable) * NSP32_SG_SIZE * MAX_TARGET * MAX_LUN)
multiline_comment|/* Auto parameter mode memory map.   */
multiline_comment|/* All values must be little endian. */
DECL|struct|_nsp32_autoparam
r_typedef
r_struct
id|_nsp32_autoparam
(brace
DECL|member|cdb
id|u8
id|cdb
(braket
l_int|4
op_star
l_int|0x10
)braket
suffix:semicolon
multiline_comment|/* SCSI Command                      */
DECL|member|msgout
id|u32_le
id|msgout
suffix:semicolon
multiline_comment|/* outgoing messages                 */
DECL|member|syncreg
id|u8
id|syncreg
suffix:semicolon
multiline_comment|/* sync register value               */
DECL|member|ackwidth
id|u8
id|ackwidth
suffix:semicolon
multiline_comment|/* ack width register value          */
DECL|member|target_id
id|u8
id|target_id
suffix:semicolon
multiline_comment|/* target/host device id             */
DECL|member|sample_reg
id|u8
id|sample_reg
suffix:semicolon
multiline_comment|/* hazard killer sampling rate       */
DECL|member|command_control
id|u16_le
id|command_control
suffix:semicolon
multiline_comment|/* command control register          */
DECL|member|transfer_control
id|u16_le
id|transfer_control
suffix:semicolon
multiline_comment|/* transfer control register         */
DECL|member|sgt_pointer
id|u32_le
id|sgt_pointer
suffix:semicolon
multiline_comment|/* SG table physical address for DMA */
DECL|member|dummy
id|u32_le
id|dummy
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|nsp32_autoparam
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|nsp32_autoparam
suffix:semicolon
multiline_comment|/* must be packed struct */
multiline_comment|/*&n; * host data structure&n; */
multiline_comment|/* message in/out buffer */
DECL|macro|MSGOUTBUF_MAX
mdefine_line|#define MSGOUTBUF_MAX&t;&t;20
DECL|macro|MSGINBUF_MAX
mdefine_line|#define MSGINBUF_MAX&t;&t;20
multiline_comment|/* flag for trans_method */
DECL|macro|NSP32_TRANSFER_BUSMASTER
mdefine_line|#define NSP32_TRANSFER_BUSMASTER&t;BIT(0)
DECL|macro|NSP32_TRANSFER_MMIO
mdefine_line|#define NSP32_TRANSFER_MMIO&t;&t;BIT(1)&t;/* Not supported yet */
DECL|macro|NSP32_TRANSFER_PIO
mdefine_line|#define NSP32_TRANSFER_PIO&t;&t;BIT(2)&t;/* Not supported yet */
multiline_comment|/*&n; * structure for connected LUN dynamic data&n; *&n; * Note: Currently tagged queuing is disabled, each nsp32_lunt holds&n; *       one SCSI command and one state.&n; */
DECL|macro|DISCPRIV_OK
mdefine_line|#define DISCPRIV_OK&t;&t;BIT(0)&t;&t;/* DISCPRIV Enable mode */
DECL|macro|MSGIN03
mdefine_line|#define MSGIN03&t;&t;&t;BIT(1)&t;&t;/* Auto Msg In 03 Flag  */
DECL|struct|_nsp32_lunt
r_typedef
r_struct
id|_nsp32_lunt
(brace
DECL|member|SCpnt
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
multiline_comment|/* Current Handling Scsi_Cmnd */
DECL|member|save_datp
r_int
r_int
id|save_datp
suffix:semicolon
multiline_comment|/* Save Data Pointer - saved position from initial address */
DECL|member|msgin03
r_int
id|msgin03
suffix:semicolon
multiline_comment|/* auto msg in 03 flag     */
DECL|member|sg_num
r_int
r_int
id|sg_num
suffix:semicolon
multiline_comment|/* Total number of SG entries */
DECL|member|cur_entry
r_int
id|cur_entry
suffix:semicolon
multiline_comment|/* Current SG entry number */
DECL|member|sglun
id|nsp32_sglun
op_star
id|sglun
suffix:semicolon
multiline_comment|/* sg table per lun        */
DECL|member|sglun_paddr
id|dma_addr_t
id|sglun_paddr
suffix:semicolon
multiline_comment|/* sglun physical address  */
DECL|typedef|nsp32_lunt
)brace
id|nsp32_lunt
suffix:semicolon
multiline_comment|/*&n; * SCSI TARGET/LUN definition&n; */
DECL|macro|NSP32_HOST_SCSIID
mdefine_line|#define NSP32_HOST_SCSIID    7  /* SCSI initiator is everytime defined as 7 */
DECL|macro|MAX_TARGET
mdefine_line|#define MAX_TARGET&t;     8
DECL|macro|MAX_LUN
mdefine_line|#define MAX_LUN&t;&t;     8&t;/* XXX: In SPI3, max number of LUN is 64. */
DECL|struct|_nsp32_sync_table
r_typedef
r_struct
id|_nsp32_sync_table
(brace
DECL|member|period_num
r_int
r_char
id|period_num
suffix:semicolon
multiline_comment|/* period number                  */
DECL|member|ackwidth
r_int
r_char
id|ackwidth
suffix:semicolon
multiline_comment|/* ack width designated by period */
DECL|member|start_period
r_int
r_char
id|start_period
suffix:semicolon
multiline_comment|/* search range - start period    */
DECL|member|end_period
r_int
r_char
id|end_period
suffix:semicolon
multiline_comment|/* search range - end period      */
DECL|member|sample_rate
r_int
r_char
id|sample_rate
suffix:semicolon
multiline_comment|/* hazard killer parameter        */
DECL|typedef|nsp32_sync_table
)brace
id|nsp32_sync_table
suffix:semicolon
multiline_comment|/*&n; * structure for target device static data&n; */
multiline_comment|/* flag for nsp32_target.sync_flag */
DECL|macro|SDTR_INITIATOR
mdefine_line|#define SDTR_INITIATOR&t;  BIT(0)    /* sending SDTR from initiator        */
DECL|macro|SDTR_TARGET
mdefine_line|#define SDTR_TARGET&t;  BIT(1)    /* sending SDTR from target           */
DECL|macro|SDTR_DONE
mdefine_line|#define SDTR_DONE&t;  BIT(2)    /* exchanging SDTR has been processed */
multiline_comment|/* syncronous period value for nsp32_target.config_max */
DECL|macro|FAST5M
mdefine_line|#define FAST5M&t;&t;&t;0x32
DECL|macro|FAST10M
mdefine_line|#define FAST10M&t;&t;&t;0x19
DECL|macro|ULTRA20M
mdefine_line|#define ULTRA20M&t;&t;0x0c
multiline_comment|/* flag for nsp32_target.{sync_offset}, period */
DECL|macro|ASYNC_OFFSET
mdefine_line|#define ASYNC_OFFSET&t;&t;0&t;/* asynchronous transfer           */
DECL|macro|SYNC_OFFSET
mdefine_line|#define SYNC_OFFSET&t;&t;0xf&t;/* synchronous transfer max offset */
multiline_comment|/* syncreg:&n;  bit:07 06 05 04 03 02 01 00&n;      ---PERIOD-- ---OFFSET--   */
DECL|macro|TO_SYNCREG
mdefine_line|#define TO_SYNCREG(period, offset) (((period) &amp; 0x0f) &lt;&lt; 4 | ((offset) &amp; 0x0f))
DECL|struct|_nsp32_target
r_typedef
r_struct
id|_nsp32_target
(brace
DECL|member|syncreg
r_int
r_char
id|syncreg
suffix:semicolon
multiline_comment|/* value for SYNCREG   */
DECL|member|ackwidth
r_int
r_char
id|ackwidth
suffix:semicolon
multiline_comment|/* value for ACKWIDTH  */
DECL|member|period
r_int
r_char
id|period
suffix:semicolon
multiline_comment|/* sync period (0-255) */
DECL|member|offset
r_int
r_char
id|offset
suffix:semicolon
multiline_comment|/* sync offset (0-15)  */
DECL|member|sync_flag
r_int
id|sync_flag
suffix:semicolon
multiline_comment|/* SDTR_*, 0           */
DECL|member|limit_entry
r_int
id|limit_entry
suffix:semicolon
multiline_comment|/* max speed limit entry designated&n;&t;&t;&t;&t;&t;   by EEPROM configuration */
DECL|member|sample_reg
r_int
r_char
id|sample_reg
suffix:semicolon
multiline_comment|/* SREQ hazard killer register */
DECL|typedef|nsp32_target
)brace
id|nsp32_target
suffix:semicolon
DECL|struct|_nsp32_hw_data
r_typedef
r_struct
id|_nsp32_hw_data
(brace
DECL|member|IrqNumber
r_int
id|IrqNumber
suffix:semicolon
DECL|member|BaseAddress
r_int
id|BaseAddress
suffix:semicolon
DECL|member|NumAddress
r_int
id|NumAddress
suffix:semicolon
DECL|member|MmioAddress
r_int
r_int
id|MmioAddress
suffix:semicolon
DECL|macro|NSP32_MMIO_OFFSET
mdefine_line|#define NSP32_MMIO_OFFSET 0x0800
DECL|member|MmioLength
r_int
r_int
id|MmioLength
suffix:semicolon
DECL|member|CurrentSC
id|Scsi_Cmnd
op_star
id|CurrentSC
suffix:semicolon
DECL|member|Pci
r_struct
id|pci_dev
op_star
id|Pci
suffix:semicolon
DECL|member|pci_devid
r_const
r_struct
id|pci_device_id
op_star
id|pci_devid
suffix:semicolon
DECL|member|Host
r_struct
id|Scsi_Host
op_star
id|Host
suffix:semicolon
DECL|member|Lock
id|spinlock_t
id|Lock
suffix:semicolon
DECL|member|info_str
r_char
id|info_str
(braket
l_int|100
)braket
suffix:semicolon
multiline_comment|/* allocated memory region */
DECL|member|sg_list
id|nsp32_sglun
op_star
id|sg_list
suffix:semicolon
multiline_comment|/* sglist virtuxal address         */
DECL|member|sg_paddr
id|dma_addr_t
id|sg_paddr
suffix:semicolon
multiline_comment|/* physical address of hw_sg_table */
DECL|member|autoparam
id|nsp32_autoparam
op_star
id|autoparam
suffix:semicolon
multiline_comment|/* auto parameter transfer region  */
DECL|member|auto_paddr
id|dma_addr_t
id|auto_paddr
suffix:semicolon
multiline_comment|/* physical address of autoparam   */
DECL|member|cur_entry
r_int
id|cur_entry
suffix:semicolon
multiline_comment|/* current sgt entry               */
multiline_comment|/* target/LUN */
DECL|member|cur_lunt
id|nsp32_lunt
op_star
id|cur_lunt
suffix:semicolon
multiline_comment|/* Current connected LUN table */
DECL|member|lunt
id|nsp32_lunt
id|lunt
(braket
id|MAX_TARGET
)braket
(braket
id|MAX_LUN
)braket
suffix:semicolon
multiline_comment|/* All LUN table */
DECL|member|cur_target
id|nsp32_target
op_star
id|cur_target
suffix:semicolon
multiline_comment|/* Current connected SCSI ID    */
DECL|member|target
id|nsp32_target
id|target
(braket
id|MAX_TARGET
)braket
suffix:semicolon
multiline_comment|/* SCSI ID */
DECL|member|cur_id
r_int
id|cur_id
suffix:semicolon
multiline_comment|/* Current connected target ID  */
DECL|member|cur_lun
r_int
id|cur_lun
suffix:semicolon
multiline_comment|/* Current connected target LUN */
multiline_comment|/* behavior setting parameters */
DECL|member|trans_method
r_int
id|trans_method
suffix:semicolon
multiline_comment|/* transfer method flag            */
DECL|member|resettime
r_int
id|resettime
suffix:semicolon
multiline_comment|/* Reset time                      */
DECL|member|clock
r_int
id|clock
suffix:semicolon
multiline_comment|/* clock dividing flag             */
DECL|member|synct
id|nsp32_sync_table
op_star
id|synct
suffix:semicolon
multiline_comment|/* sync_table determined by clock  */
DECL|member|syncnum
r_int
id|syncnum
suffix:semicolon
multiline_comment|/* the max number of synct element */
multiline_comment|/* message buffer */
DECL|member|msgoutbuf
r_int
r_char
id|msgoutbuf
(braket
id|MSGOUTBUF_MAX
)braket
suffix:semicolon
multiline_comment|/* msgout buffer    */
DECL|member|msgout_len
r_char
id|msgout_len
suffix:semicolon
multiline_comment|/* msgoutbuf length */
DECL|member|msginbuf
r_int
r_char
id|msginbuf
(braket
id|MSGINBUF_MAX
)braket
suffix:semicolon
multiline_comment|/* megin buffer     */
DECL|member|msgin_len
r_char
id|msgin_len
suffix:semicolon
multiline_comment|/* msginbuf length  */
macro_line|#ifdef CONFIG_PM
DECL|member|PciState
id|u32
id|PciState
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* save PCI state to this area */
macro_line|#endif
DECL|typedef|nsp32_hw_data
)brace
id|nsp32_hw_data
suffix:semicolon
multiline_comment|/*&n; * TIME definition&n; */
DECL|macro|RESET_HOLD_TIME
mdefine_line|#define RESET_HOLD_TIME&t;&t;10000&t;/* reset time in us (SCSI-2 says the&n;&t;&t;&t;&t;&t;   minimum is 25us) */
DECL|macro|SEL_TIMEOUT_TIME
mdefine_line|#define SEL_TIMEOUT_TIME&t;10000&t;/* 250ms defined in SCSI specification&n;&t;&t;&t;&t;&t;   (25.6us/1unit) */
DECL|macro|ARBIT_TIMEOUT_TIME
mdefine_line|#define ARBIT_TIMEOUT_TIME&t;100&t;/* 100us */
DECL|macro|REQSACK_TIMEOUT_TIME
mdefine_line|#define REQSACK_TIMEOUT_TIME&t;10000&t;/* max wait time for REQ/SACK assertion&n;&t;&t;&t;&t;&t;   or negation, 10000us == 10ms */
multiline_comment|/**************************************************************************&n; * Compatibility functions&n; */
multiline_comment|/* for Kernel 2.4 */
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,6,0))
DECL|macro|scsi_register_host
macro_line|# define scsi_register_host(template) &t;scsi_register_module(MODULE_SCSI_HA, template)
DECL|macro|scsi_unregister_host
macro_line|# define scsi_unregister_host(template) scsi_unregister_module(MODULE_SCSI_HA, template)
DECL|macro|scsi_host_put
macro_line|# define scsi_host_put(host)            scsi_unregister(host)
DECL|macro|pci_name
macro_line|# define pci_name(pci_dev)              ((pci_dev)-&gt;slot_name)
DECL|typedef|irqreturn_t
r_typedef
r_void
id|irqreturn_t
suffix:semicolon
DECL|macro|IRQ_NONE
macro_line|# define IRQ_NONE      /* */
DECL|macro|IRQ_HANDLED
macro_line|# define IRQ_HANDLED   /* */
DECL|macro|IRQ_RETVAL
macro_line|# define IRQ_RETVAL(x) /* */
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
macro_line|#endif
multiline_comment|/* for Kernel 2.6 */
macro_line|#if (LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,6,0))
DECL|macro|__devinitdata
macro_line|# define __devinitdata /* */
macro_line|#endif
macro_line|#endif /* _NSP32_H */
multiline_comment|/* end */
eof
