multiline_comment|/*&n; * Workbit NinjaSCSI-32Bi/UDE PCI/Cardbus SCSI Host Bus Adapter driver&n; * Basic data header&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n;*/
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
mdefine_line|#define PCI_DEVICE_ID_NINJASCSI_32BI_CBSC_II  0x0005
DECL|macro|PCI_DEVICE_ID_NINJASCSI_32BI_KME
mdefine_line|#define PCI_DEVICE_ID_NINJASCSI_32BI_KME      0xf007
DECL|macro|PCI_DEVICE_ID_NINJASCSI_32BI_WBT
mdefine_line|#define PCI_DEVICE_ID_NINJASCSI_32BI_WBT      0x8007
DECL|macro|PCI_DEVICE_ID_WORKBIT_STANDARD
mdefine_line|#define PCI_DEVICE_ID_WORKBIT_STANDARD        0xf010
DECL|macro|PCI_DEVICE_ID_WORKBIT_DUALEDGE
mdefine_line|#define PCI_DEVICE_ID_WORKBIT_DUALEDGE        0xf011
DECL|macro|PCI_DEVICE_ID_NINJASCSI_32BI_LOGITEC
mdefine_line|#define PCI_DEVICE_ID_NINJASCSI_32BI_LOGITEC  0xf012
DECL|macro|PCI_DEVICE_ID_NINJASCSI_32BIB_LOGITEC
mdefine_line|#define PCI_DEVICE_ID_NINJASCSI_32BIB_LOGITEC 0xf013
DECL|macro|PCI_DEVICE_ID_NINJASCSI_32UDE_MELCO
mdefine_line|#define PCI_DEVICE_ID_NINJASCSI_32UDE_MELCO   0xf015
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
DECL|enumerator|MODEL_EXT_ROM
id|MODEL_EXT_ROM
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
l_string|&quot;I-O DATA CBSC-II&quot;
comma
l_string|&quot;KME SCSI card&quot;
comma
l_string|&quot;Workbit duo SCSI card&quot;
comma
l_string|&quot;External ROM&quot;
comma
l_string|&quot;Workbit Standard/IO Data PCI card&quot;
comma
l_string|&quot;Logitec PCI card&quot;
comma
l_string|&quot;Melco PCI card&quot;
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * SCSI Generic Definitions&n; */
DECL|macro|EXTENDED_SDTR_LEN
mdefine_line|#define EXTENDED_SDTR_LEN&t;0x03
multiline_comment|/*&n; * MACRO&n; */
DECL|macro|BIT
mdefine_line|#define BIT(x)    (1UL &lt;&lt; (x))
macro_line|#ifndef MIN
DECL|macro|MIN
macro_line|# define MIN(a,b)  ((a) &gt; (b) ? (b) : (a))
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
macro_line|# define IRQ_CONTROL_ALL_IRQ_MASK   0xf000
DECL|macro|IRQSTATUS_ANY_IRQ
macro_line|# define IRQSTATUS_ANY_IRQ          (IRQSTATUS_RESELECT_OCCUER&t;| &bslash;&n;&t;&t;&t;&t;     IRQSTATUS_PHASE_CHANGE_IRQ&t;| &bslash;&n;&t;&t;&t;&t;     IRQSTATUS_SCSIRESET_IRQ&t;| &bslash;&n;&t;&t;&t;&t;     IRQSTATUS_TIMER_IRQ&t;| &bslash;&n;&t;&t;&t;&t;     IRQSTATUS_FIFO_SHLD_IRQ&t;| &bslash;&n;&t;&t;&t;&t;     IRQSTATUS_PCI_IRQ&t;&t;| &bslash;&n;&t;&t;&t;&t;     IRQSTATUS_BMCNTERR_IRQ&t;| &bslash;&n;&t;&t;&t;&t;     IRQSTATUS_AUTOSCSI_IRQ&t;)
DECL|macro|TRANSFER_CONTROL
mdefine_line|#define TRANSFER_CONTROL 0x02&t;/* BASE+02, W, W */
DECL|macro|TRANSFER_STATUS
mdefine_line|#define TRANSFER_STATUS  0x02&t;/* BASE+02, W, R */
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
mdefine_line|#define INDEX_REG 0x04&t;&t;/* BASE+04, Byte(R/W), Word(R) */
DECL|macro|TIMER_SET
mdefine_line|#define TIMER_SET 0x06&t;&t;/* BASE+06, W, R/W */
DECL|macro|TIMER_CNT_MASK
macro_line|# define TIMER_CNT_MASK 0xff
DECL|macro|TIMER_STOP
macro_line|# define TIMER_STOP     BIT(8)
DECL|macro|DATA_REG_LOW
mdefine_line|#define DATA_REG_LOW 0x08&t;/* BASE+08, LowW, R/W */
DECL|macro|DATA_REG_HI
mdefine_line|#define DATA_REG_HI  0x0a&t;/* BASE+0a, Hi-W, R/W */
DECL|macro|FIFO_REST_CNT
mdefine_line|#define FIFO_REST_CNT 0x0c&t;/* BASE+0c, W, R/W */
DECL|macro|FIFO_REST_MASK
macro_line|# define FIFO_REST_MASK       0x1ff
DECL|macro|FIFO_EMPTY_SHLD_FLAG
macro_line|# define FIFO_EMPTY_SHLD_FLAG BIT(14)
DECL|macro|FIFO_FULL_SHLD_FLAG
macro_line|# define FIFO_FULL_SHLD_FLAG  BIT(15)
DECL|macro|SREQ_SMPL_RATE
mdefine_line|#define SREQ_SMPL_RATE 0x0f&t;/* BASE+0f, B, R/W */
DECL|macro|SREQSMPLRATE_RATE0
macro_line|# define SREQSMPLRATE_RATE0 BIT(0)
DECL|macro|SREQSMPLRATE_RATE1
macro_line|# define SREQSMPLRATE_RATE1 BIT(1)
DECL|macro|SAMPLING_ENABLE
macro_line|# define SAMPLING_ENABLE    BIT(2)
DECL|macro|SCSI_BUS_CONTROL
mdefine_line|#define SCSI_BUS_CONTROL 0x10&t;/* BASE+10, B, R/W */
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
mdefine_line|#define CLR_COUNTER 0x12&t;/* BASE+12, B, W */
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
macro_line|# define CLRCOUNTER_ALLMASK    (BIT(0) | BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5))
DECL|macro|SCSI_BUS_MONITOR
mdefine_line|#define SCSI_BUS_MONITOR 0x12&t;/* BASE+12, B, R */
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
mdefine_line|#define COMMAND_DATA 0x14&t;/* BASE+14, B, R/W */
DECL|macro|PARITY_CONTROL
mdefine_line|#define PARITY_CONTROL 0x16&t;/* BASE+16, B, R/W */
DECL|macro|PARITY_CHECK_ENABLE
macro_line|# define PARITY_CHECK_ENABLE BIT(0)
DECL|macro|PARITY_ERROR_CLEAR
macro_line|# define PARITY_ERROR_CLEAR  BIT(1)
DECL|macro|PARITY_STATUS
mdefine_line|#define PARITY_STATUS  0x16
singleline_comment|//# define PARITY_CHECK_ENABLE BIT(0)
DECL|macro|PARITY_ERROR_NORMAL
macro_line|# define PARITY_ERROR_NORMAL BIT(1)
DECL|macro|PARITY_ERROR_LSB
macro_line|# define PARITY_ERROR_LSB    BIT(1)
DECL|macro|PARITY_ERROR_MSB
macro_line|# define PARITY_ERROR_MSB    BIT(2)
DECL|macro|RESELECT_ID
mdefine_line|#define RESELECT_ID 0x18&t;/* BASE+18, B, R */
DECL|macro|COMMAND_CONTROL
mdefine_line|#define COMMAND_CONTROL 0x18&t;/* BASE+18, W, W */
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
mdefine_line|#define SET_ARBIT 0x1a&t;&t;/* BASE+1a, B, W */
DECL|macro|ARBIT_GO
macro_line|# define ARBIT_GO    BIT(0)
DECL|macro|ARBIT_CLEAR
macro_line|# define ARBIT_CLEAR BIT(1)
DECL|macro|ARBIT_STATUS
mdefine_line|#define ARBIT_STATUS 0x1a&t;/* BASE+1a, B, R */
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
mdefine_line|#define SYNC_REG 0x1c&t;/* BASE+1c, B, R/W */
DECL|macro|ACK_WIDTH
mdefine_line|#define ACK_WIDTH 0x1d&t;/* BASE+1d, B, R/W */
DECL|macro|SCSI_DATA_WITH_ACK
mdefine_line|#define SCSI_DATA_WITH_ACK 0x20&t;/* BASE+20, B, R/W */
DECL|macro|SCSI_OUT_LATCH_TARGET_ID
mdefine_line|#define SCSI_OUT_LATCH_TARGET_ID 0x22&t;/* BASE+22, B, W */
DECL|macro|SCSI_DATA_IN
mdefine_line|#define SCSI_DATA_IN 0x22&t;/* BASE+22, B, R */
DECL|macro|SCAM_CONTROL
mdefine_line|#define SCAM_CONTROL 0x24&t;/* BASE+24, B, W */
DECL|macro|SCAM_STATUS
mdefine_line|#define SCAM_STATUS  0x24&t;/* BASE+24, B, R */
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
mdefine_line|#define SCAM_DATA 0x26&t;/* BASE+26, B, R/W */
DECL|macro|SD0
macro_line|# define SD0&t;&t;&t;&t;&t;BIT(0)
DECL|macro|SD1
macro_line|# define SD1&t;&t;&t;&t;&t;BIT(1)
DECL|macro|SD2
macro_line|# define SD2&t;&t;&t;&t;&t;BIT(2)
DECL|macro|SD3
macro_line|# define SD3&t;&t;&t;&t;&t;BIT(3)
DECL|macro|SD4
macro_line|# define SD4&t;&t;&t;&t;&t;BIT(4)
DECL|macro|SD5
macro_line|# define SD5&t;&t;&t;&t;&t;BIT(5)
DECL|macro|SD6
macro_line|# define SD6&t;&t;&t;&t;&t;BIT(6)
DECL|macro|SD7
macro_line|# define SD7&t;&t;&t;&t;&t;BIT(7)
DECL|macro|SACK_CNT
mdefine_line|#define SACK_CNT 0x28&t;/* BASE+28, DW, R/W */
DECL|macro|SREQ_CNT
mdefine_line|#define SREQ_CNT 0x2c&t;/* BASE+2c, DW, R/W */
DECL|macro|FIFO_DATA_LOW
mdefine_line|#define FIFO_DATA_LOW 0x30&t;/* BASE+30, B/W/DW, R/W */
DECL|macro|FIFO_DATA_HIGH
mdefine_line|#define FIFO_DATA_HIGH 0x32&t;/* BASE+32, B/W, R/W */
DECL|macro|BM_START_ADR
mdefine_line|#define BM_START_ADR 0x34&t;/* BASE+34, DW, R/W */
DECL|macro|BM_CNT
mdefine_line|#define BM_CNT 0x38&t;/* BASE+38, DW, R/W */
DECL|macro|BM_COUNT_MASK
macro_line|# define BM_COUNT_MASK 0x0001ffff
DECL|macro|SGTEND
macro_line|# define SGTEND        BIT(31)
DECL|macro|SGT_ADR
mdefine_line|#define SGT_ADR 0x3c&t;/* BASE+3c, DW, R/W */
DECL|macro|WAIT_REG
mdefine_line|#define WAIT_REG 0x40&t;/* Bi only */
DECL|macro|SCSI_EXECUTE_PHASE
mdefine_line|#define SCSI_EXECUTE_PHASE 0x40&t;/* BASE+40, W, R */
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
mdefine_line|#define SCSI_CSB_IN 0x42&t;/* BASE+42, B, R */
DECL|macro|SCSI_MSG_OUT
mdefine_line|#define SCSI_MSG_OUT 0x44&t;/* BASE+44, DW, R/W */
DECL|macro|MSGOUT_COUNT_MASK
macro_line|# define MSGOUT_COUNT_MASK (BIT(0)|BIT(1))
DECL|macro|MV_VALID
macro_line|# define MV_VALID&t;      BIT(7)
DECL|macro|SEL_TIME_OUT
mdefine_line|#define SEL_TIME_OUT 0x48&t;/* BASE+48, W, R/W */
DECL|macro|SAVED_SACK_CNT
mdefine_line|#define SAVED_SACK_CNT 0x4c&t;/* BASE+4c, DW, R */
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
mdefine_line|#define CLOCK_DIV 0x00&t;/* BASE+08, IDX+00, B, R/W */
DECL|macro|CLOCK_2
macro_line|# define CLOCK_2&t;&t;BIT(0)&t;/* MCLK/2 */
DECL|macro|CLOCK_4
macro_line|# define CLOCK_4&t;&t;BIT(1)&t;/* MCLK/4 */
DECL|macro|PCICLK
macro_line|# define PCICLK&t;&t;&t;BIT(7)&t;/* PCICLK (33MHz) */
DECL|macro|TERM_PWR_CONTROL
mdefine_line|#define TERM_PWR_CONTROL 0x01&t;/* BASE+08, IDX+01, B, R/W */
DECL|macro|BPWR
macro_line|# define BPWR  BIT(0)
DECL|macro|SENSE
macro_line|# define SENSE BIT(1)&t;/* Read Only */
DECL|macro|EXT_PORT_DDR
mdefine_line|#define EXT_PORT_DDR 0x02&t;/* BASE+08, IDX+02, B, R/W */
DECL|macro|EXT_PORT
mdefine_line|#define EXT_PORT     0x03&t;/* BASE+08, IDX+03, B, R/W */
DECL|macro|LED_ON
macro_line|# define LED_ON&t; 0
DECL|macro|LED_OFF
macro_line|# define LED_OFF 1
DECL|macro|IRQ_SELECT
mdefine_line|#define IRQ_SELECT 0x04&t;/* BASE+08, IDX+04, W, R/W */
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
mdefine_line|#define OLD_SCSI_PHASE 0x05&t;/* BASE+08, IDX+05, B, R */
DECL|macro|OLD_MSG
macro_line|# define OLD_MSG  BIT(0)
DECL|macro|OLD_IO
macro_line|# define OLD_IO   BIT(1)
DECL|macro|OLD_CD
macro_line|# define OLD_CD   BIT(2)
DECL|macro|OLD_BUSY
macro_line|# define OLD_BUSY BIT(3)
DECL|macro|FIFO_FULL_SHLD_COUNT
mdefine_line|#define FIFO_FULL_SHLD_COUNT 0x06&t;/* BASE+08, IDX+06, B, R/W */
DECL|macro|FIFO_EMPTY_SHLD_COUNT
mdefine_line|#define FIFO_EMPTY_SHLD_COUNT 0x07&t;/* BASE+08, IDX+07, B, R/W */
DECL|macro|EXP_ROM_CONTROL
mdefine_line|#define EXP_ROM_CONTROL 0x08&t;/* BASE+08, IDX+08, B, R/W */
DECL|macro|EXP_ROM_ADRL
mdefine_line|#define EXP_ROM_ADRL&t;&t;0x09&t;/* BASE+08, IDX+09, W, R/W */
DECL|macro|EXP_ROM_DATA
mdefine_line|#define EXP_ROM_DATA&t;&t;0x0a&t;/* BASE+08, IDX+0a, B, R/W */
DECL|macro|CHIP_MODE
mdefine_line|#define CHIP_MODE 0x0b&t;/* Bi only */
DECL|macro|OEM0
macro_line|# define OEM0 BIT(1)
DECL|macro|OEM1
macro_line|# define OEM1 BIT(2)
DECL|macro|OPTB
macro_line|# define OPTB BIT(3)
DECL|macro|OPTC
macro_line|# define OPTC BIT(4)
DECL|macro|OPTD
macro_line|# define OPTD BIT(5)
DECL|macro|OPTE
macro_line|# define OPTE BIT(6)
DECL|macro|OPTF
macro_line|# define OPTF BIT(7)
DECL|macro|MISC_WR
mdefine_line|#define MISC_WR 0x0c&t;/* BASE+08, IDX+0c, W, R/W */
DECL|macro|MISC_RD
mdefine_line|#define MISC_RD 0x0c
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
mdefine_line|#define BM_CYCLE 0x0d&t;/* BASE+08, IDX+0d, B, R/W */
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
mdefine_line|#define SREQ_EDGH 0x0e&t;/* BASE+08, IDX+0e, B, W */
DECL|macro|SREQ_EDGH_SELECT
macro_line|# define SREQ_EDGH_SELECT BIT(0)
DECL|macro|UP_CNT
mdefine_line|#define UP_CNT&t;&t;0x0f&t;/* BASE+08, IDX+0f, B, W */
DECL|macro|CFG_CMD_STR
mdefine_line|#define CFG_CMD_STR      0x10&t;/* BASE+08, IDX+10, W, R */
DECL|macro|CFG_LATE_CACHE
mdefine_line|#define CFG_LATE_CACHE   0x11&t;/* BASE+08, IDX+11, W, R/W */
DECL|macro|CFG_BASE_ADR_1
mdefine_line|#define CFG_BASE_ADR_1   0x12&t;/* BASE+08, IDX+12, W, R */
DECL|macro|CFG_BASE_ADR_2
mdefine_line|#define CFG_BASE_ADR_2   0x13&t;/* BASE+08, IDX+13, W, R */
DECL|macro|CFG_INLINE
mdefine_line|#define CFG_INLINE       0x14&t;/* BASE+08, IDX+14, W, R */
DECL|macro|SERIAL_ROM_CTL
mdefine_line|#define SERIAL_ROM_CTL&t;0x15&t;/* BASE+08, IDX+15, B, R */
DECL|macro|SCL
macro_line|# define SCL &t;&t;&t;&t;&t;BIT(0)
DECL|macro|ENA
macro_line|# define ENA&t;&t;&t;&t;&t;BIT(1)
DECL|macro|SDA
macro_line|# define SDA&t;&t;&t;&t;&t;BIT(2)
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
macro_line|#endif _NSP32_H
multiline_comment|/* end */
eof
