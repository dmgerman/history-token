multiline_comment|/*&n;  Madge Horizon ATM Adapter driver.&n;  Copyright (C) 1995-1999  Madge Networks Ltd.&n;&n;  This program is free software; you can redistribute it and/or modify&n;  it under the terms of the GNU General Public License as published by&n;  the Free Software Foundation; either version 2 of the License, or&n;  (at your option) any later version.&n;&n;  This program is distributed in the hope that it will be useful,&n;  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;  GNU General Public License for more details.&n;&n;  You should have received a copy of the GNU General Public License&n;  along with this program; if not, write to the Free Software&n;  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;&n;  The GNU GPL is contained in /usr/doc/copyright/GPL on a Debian&n;  system and in the file COPYING in the Linux kernel source.&n;*/
multiline_comment|/*&n;  IMPORTANT NOTE: Madge Networks no longer makes the adapters&n;  supported by this driver and makes no commitment to maintain it.&n;*/
multiline_comment|/* too many macros - change to inline functions */
macro_line|#ifndef DRIVER_ATM_HORIZON_H
DECL|macro|DRIVER_ATM_HORIZON_H
mdefine_line|#define DRIVER_ATM_HORIZON_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifdef CONFIG_ATM_HORIZON_DEBUG
DECL|macro|DEBUG_HORIZON
mdefine_line|#define DEBUG_HORIZON
macro_line|#endif
DECL|macro|DEV_LABEL
mdefine_line|#define DEV_LABEL                         &quot;hrz&quot;
macro_line|#ifndef PCI_VENDOR_ID_MADGE
DECL|macro|PCI_VENDOR_ID_MADGE
mdefine_line|#define PCI_VENDOR_ID_MADGE               0x10B6
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_MADGE_HORIZON
DECL|macro|PCI_DEVICE_ID_MADGE_HORIZON
mdefine_line|#define PCI_DEVICE_ID_MADGE_HORIZON       0x1000
macro_line|#endif
singleline_comment|// diagnostic output
DECL|macro|PRINTK
mdefine_line|#define PRINTK(severity,format,args...) &bslash;&n;  printk(severity DEV_LABEL &quot;: &quot; format &quot;&bslash;n&quot; , ## args)
macro_line|#ifdef DEBUG_HORIZON
DECL|macro|DBG_ERR
mdefine_line|#define DBG_ERR  0x0001
DECL|macro|DBG_WARN
mdefine_line|#define DBG_WARN 0x0002
DECL|macro|DBG_INFO
mdefine_line|#define DBG_INFO 0x0004
DECL|macro|DBG_VCC
mdefine_line|#define DBG_VCC  0x0008
DECL|macro|DBG_QOS
mdefine_line|#define DBG_QOS  0x0010
DECL|macro|DBG_TX
mdefine_line|#define DBG_TX   0x0020
DECL|macro|DBG_RX
mdefine_line|#define DBG_RX   0x0040
DECL|macro|DBG_SKB
mdefine_line|#define DBG_SKB  0x0080
DECL|macro|DBG_IRQ
mdefine_line|#define DBG_IRQ  0x0100
DECL|macro|DBG_FLOW
mdefine_line|#define DBG_FLOW 0x0200
DECL|macro|DBG_BUS
mdefine_line|#define DBG_BUS  0x0400
DECL|macro|DBG_REGS
mdefine_line|#define DBG_REGS 0x0800
DECL|macro|DBG_DATA
mdefine_line|#define DBG_DATA 0x1000
DECL|macro|DBG_MASK
mdefine_line|#define DBG_MASK 0x1fff
multiline_comment|/* the ## prevents the annoying double expansion of the macro arguments */
multiline_comment|/* KERN_INFO is used since KERN_DEBUG often does not make it to the console */
DECL|macro|PRINTDB
mdefine_line|#define PRINTDB(bits,format,args...) &bslash;&n;  ( (debug &amp; (bits)) ? printk (KERN_INFO DEV_LABEL &quot;: &quot; format , ## args) : 1 )
DECL|macro|PRINTDM
mdefine_line|#define PRINTDM(bits,format,args...) &bslash;&n;  ( (debug &amp; (bits)) ? printk (format , ## args) : 1 )
DECL|macro|PRINTDE
mdefine_line|#define PRINTDE(bits,format,args...) &bslash;&n;  ( (debug &amp; (bits)) ? printk (format &quot;&bslash;n&quot; , ## args) : 1 )
DECL|macro|PRINTD
mdefine_line|#define PRINTD(bits,format,args...) &bslash;&n;  ( (debug &amp; (bits)) ? printk (KERN_INFO DEV_LABEL &quot;: &quot; format &quot;&bslash;n&quot; , ## args) : 1 )
macro_line|#else
DECL|macro|PRINTD
mdefine_line|#define PRINTD(bits,format,args...)
DECL|macro|PRINTDB
mdefine_line|#define PRINTDB(bits,format,args...)
DECL|macro|PRINTDM
mdefine_line|#define PRINTDM(bits,format,args...)
DECL|macro|PRINTDE
mdefine_line|#define PRINTDE(bits,format,args...)
macro_line|#endif
DECL|macro|PRINTDD
mdefine_line|#define PRINTDD(sec,fmt,args...)
DECL|macro|PRINTDDB
mdefine_line|#define PRINTDDB(sec,fmt,args...)
DECL|macro|PRINTDDM
mdefine_line|#define PRINTDDM(sec,fmt,args...)
DECL|macro|PRINTDDE
mdefine_line|#define PRINTDDE(sec,fmt,args...)
singleline_comment|// fixed constants
DECL|macro|SPARE_BUFFER_POOL_SIZE
mdefine_line|#define SPARE_BUFFER_POOL_SIZE            MAX_VCS
DECL|macro|HRZ_MAX_VPI
mdefine_line|#define HRZ_MAX_VPI                       4
DECL|macro|MIN_PCI_LATENCY
mdefine_line|#define MIN_PCI_LATENCY                   48 
singleline_comment|// 24 IS TOO SMALL
multiline_comment|/*  Horizon specific bits */
multiline_comment|/*  Register offsets */
DECL|macro|HRZ_IO_EXTENT
mdefine_line|#define HRZ_IO_EXTENT                     0x80
DECL|macro|DATA_PORT_OFF
mdefine_line|#define DATA_PORT_OFF                     0x00
DECL|macro|TX_CHANNEL_PORT_OFF
mdefine_line|#define TX_CHANNEL_PORT_OFF               0x04
DECL|macro|TX_DESCRIPTOR_PORT_OFF
mdefine_line|#define TX_DESCRIPTOR_PORT_OFF            0x08
DECL|macro|MEMORY_PORT_OFF
mdefine_line|#define MEMORY_PORT_OFF                   0x0C
DECL|macro|MEM_WR_ADDR_REG_OFF
mdefine_line|#define MEM_WR_ADDR_REG_OFF               0x14
DECL|macro|MEM_RD_ADDR_REG_OFF
mdefine_line|#define MEM_RD_ADDR_REG_OFF               0x18
DECL|macro|CONTROL_0_REG
mdefine_line|#define CONTROL_0_REG                     0x1C
DECL|macro|INT_SOURCE_REG_OFF
mdefine_line|#define INT_SOURCE_REG_OFF                0x20
DECL|macro|INT_ENABLE_REG_OFF
mdefine_line|#define INT_ENABLE_REG_OFF                0x24
DECL|macro|MASTER_RX_ADDR_REG_OFF
mdefine_line|#define MASTER_RX_ADDR_REG_OFF            0x28
DECL|macro|MASTER_RX_COUNT_REG_OFF
mdefine_line|#define MASTER_RX_COUNT_REG_OFF           0x2C
DECL|macro|MASTER_TX_ADDR_REG_OFF
mdefine_line|#define MASTER_TX_ADDR_REG_OFF            0x30
DECL|macro|MASTER_TX_COUNT_REG_OFF
mdefine_line|#define MASTER_TX_COUNT_REG_OFF           0x34
DECL|macro|TX_DESCRIPTOR_REG_OFF
mdefine_line|#define TX_DESCRIPTOR_REG_OFF             0x38
DECL|macro|TX_CHANNEL_CONFIG_COMMAND_OFF
mdefine_line|#define TX_CHANNEL_CONFIG_COMMAND_OFF     0x40
DECL|macro|TX_CHANNEL_CONFIG_DATA_OFF
mdefine_line|#define TX_CHANNEL_CONFIG_DATA_OFF        0x44
DECL|macro|TX_FREE_BUFFER_COUNT_OFF
mdefine_line|#define TX_FREE_BUFFER_COUNT_OFF          0x48
DECL|macro|RX_FREE_BUFFER_COUNT_OFF
mdefine_line|#define RX_FREE_BUFFER_COUNT_OFF          0x4C
DECL|macro|TX_CONFIG_OFF
mdefine_line|#define TX_CONFIG_OFF                     0x50
DECL|macro|TX_STATUS_OFF
mdefine_line|#define TX_STATUS_OFF                     0x54
DECL|macro|RX_CONFIG_OFF
mdefine_line|#define RX_CONFIG_OFF                     0x58
DECL|macro|RX_LINE_CONFIG_OFF
mdefine_line|#define RX_LINE_CONFIG_OFF                0x5C
DECL|macro|RX_QUEUE_RD_PTR_OFF
mdefine_line|#define RX_QUEUE_RD_PTR_OFF               0x60
DECL|macro|RX_QUEUE_WR_PTR_OFF
mdefine_line|#define RX_QUEUE_WR_PTR_OFF               0x64
DECL|macro|MAX_AAL5_CELL_COUNT_OFF
mdefine_line|#define MAX_AAL5_CELL_COUNT_OFF           0x68
DECL|macro|RX_CHANNEL_PORT_OFF
mdefine_line|#define RX_CHANNEL_PORT_OFF               0x6C
DECL|macro|TX_CELL_COUNT_OFF
mdefine_line|#define TX_CELL_COUNT_OFF                 0x70
DECL|macro|RX_CELL_COUNT_OFF
mdefine_line|#define RX_CELL_COUNT_OFF                 0x74
DECL|macro|HEC_ERROR_COUNT_OFF
mdefine_line|#define HEC_ERROR_COUNT_OFF               0x78
DECL|macro|UNASSIGNED_CELL_COUNT_OFF
mdefine_line|#define UNASSIGNED_CELL_COUNT_OFF         0x7C
multiline_comment|/*  Register bit definitions */
multiline_comment|/* Control 0 register */
DECL|macro|SEEPROM_DO
mdefine_line|#define SEEPROM_DO                        0x00000001
DECL|macro|SEEPROM_DI
mdefine_line|#define SEEPROM_DI                        0x00000002
DECL|macro|SEEPROM_SK
mdefine_line|#define SEEPROM_SK                        0x00000004
DECL|macro|SEEPROM_CS
mdefine_line|#define SEEPROM_CS                        0x00000008
DECL|macro|DEBUG_BIT_0
mdefine_line|#define DEBUG_BIT_0                       0x00000010
DECL|macro|DEBUG_BIT_1
mdefine_line|#define DEBUG_BIT_1                       0x00000020
DECL|macro|DEBUG_BIT_2
mdefine_line|#define DEBUG_BIT_2                       0x00000040
singleline_comment|//      RESERVED                          0x00000080
DECL|macro|DEBUG_BIT_0_OE
mdefine_line|#define DEBUG_BIT_0_OE                    0x00000100
DECL|macro|DEBUG_BIT_1_OE
mdefine_line|#define DEBUG_BIT_1_OE                    0x00000200
DECL|macro|DEBUG_BIT_2_OE
mdefine_line|#define DEBUG_BIT_2_OE                    0x00000400
singleline_comment|//      RESERVED                          0x00000800
DECL|macro|DEBUG_BIT_0_STATE
mdefine_line|#define DEBUG_BIT_0_STATE                 0x00001000
DECL|macro|DEBUG_BIT_1_STATE
mdefine_line|#define DEBUG_BIT_1_STATE                 0x00002000
DECL|macro|DEBUG_BIT_2_STATE
mdefine_line|#define DEBUG_BIT_2_STATE                 0x00004000
singleline_comment|//      RESERVED                          0x00008000
DECL|macro|GENERAL_BIT_0
mdefine_line|#define GENERAL_BIT_0                     0x00010000
DECL|macro|GENERAL_BIT_1
mdefine_line|#define GENERAL_BIT_1                     0x00020000
DECL|macro|GENERAL_BIT_2
mdefine_line|#define GENERAL_BIT_2                     0x00040000
DECL|macro|GENERAL_BIT_3
mdefine_line|#define GENERAL_BIT_3                     0x00080000
DECL|macro|RESET_HORIZON
mdefine_line|#define RESET_HORIZON                     0x00100000
DECL|macro|RESET_ATM
mdefine_line|#define RESET_ATM                         0x00200000
DECL|macro|RESET_RX
mdefine_line|#define RESET_RX                          0x00400000
DECL|macro|RESET_TX
mdefine_line|#define RESET_TX                          0x00800000
DECL|macro|RESET_HOST
mdefine_line|#define RESET_HOST                        0x01000000
singleline_comment|//      RESERVED                          0x02000000
DECL|macro|TARGET_RETRY_DISABLE
mdefine_line|#define TARGET_RETRY_DISABLE              0x04000000
DECL|macro|ATM_LAYER_SELECT
mdefine_line|#define ATM_LAYER_SELECT                  0x08000000
DECL|macro|ATM_LAYER_STATUS
mdefine_line|#define ATM_LAYER_STATUS                  0x10000000
singleline_comment|//      RESERVED                          0xE0000000
multiline_comment|/* Interrupt source and enable registers */
DECL|macro|RX_DATA_AV
mdefine_line|#define RX_DATA_AV                        0x00000001
DECL|macro|RX_DISABLED
mdefine_line|#define RX_DISABLED                       0x00000002
DECL|macro|TIMING_MARKER
mdefine_line|#define TIMING_MARKER                     0x00000004
DECL|macro|FORCED
mdefine_line|#define FORCED                            0x00000008
DECL|macro|RX_BUS_MASTER_COMPLETE
mdefine_line|#define RX_BUS_MASTER_COMPLETE            0x00000010
DECL|macro|TX_BUS_MASTER_COMPLETE
mdefine_line|#define TX_BUS_MASTER_COMPLETE            0x00000020
DECL|macro|ABR_TX_CELL_COUNT_INT
mdefine_line|#define ABR_TX_CELL_COUNT_INT             0x00000040
DECL|macro|DEBUG_INT
mdefine_line|#define DEBUG_INT                         0x00000080
singleline_comment|//      RESERVED                          0xFFFFFF00
multiline_comment|/* PIO and Bus Mastering */
DECL|macro|MAX_PIO_COUNT
mdefine_line|#define MAX_PIO_COUNT                     0x000000ff 
singleline_comment|// 255 - make tunable?
singleline_comment|// 8188 is a hard limit for bus mastering
DECL|macro|MAX_TRANSFER_COUNT
mdefine_line|#define MAX_TRANSFER_COUNT                0x00001ffc 
singleline_comment|// 8188
DECL|macro|MASTER_TX_AUTO_APPEND_DESC
mdefine_line|#define MASTER_TX_AUTO_APPEND_DESC        0x80000000
multiline_comment|/* TX channel config command port */
DECL|macro|PCR_TIMER_ACCESS
mdefine_line|#define PCR_TIMER_ACCESS                      0x0000
DECL|macro|SCR_TIMER_ACCESS
mdefine_line|#define SCR_TIMER_ACCESS                      0x0001
DECL|macro|BUCKET_CAPACITY_ACCESS
mdefine_line|#define BUCKET_CAPACITY_ACCESS                0x0002
DECL|macro|BUCKET_FULLNESS_ACCESS
mdefine_line|#define BUCKET_FULLNESS_ACCESS                0x0003
DECL|macro|RATE_TYPE_ACCESS
mdefine_line|#define RATE_TYPE_ACCESS                      0x0004
singleline_comment|//      UNUSED                                0x00F8
DECL|macro|TX_CHANNEL_CONFIG_MULT
mdefine_line|#define TX_CHANNEL_CONFIG_MULT                0x0100
singleline_comment|//      UNUSED                                0xF800
DECL|macro|BUCKET_MAX_SIZE
mdefine_line|#define BUCKET_MAX_SIZE                       0x003f
multiline_comment|/* TX channel config data port */
DECL|macro|CLOCK_SELECT_SHIFT
mdefine_line|#define CLOCK_SELECT_SHIFT                    4
DECL|macro|CLOCK_DISABLE
mdefine_line|#define CLOCK_DISABLE                         0x00ff
DECL|macro|IDLE_RATE_TYPE
mdefine_line|#define IDLE_RATE_TYPE                       0x0
DECL|macro|ABR_RATE_TYPE
mdefine_line|#define ABR_RATE_TYPE                        0x1
DECL|macro|VBR_RATE_TYPE
mdefine_line|#define VBR_RATE_TYPE                        0x2
DECL|macro|CBR_RATE_TYPE
mdefine_line|#define CBR_RATE_TYPE                        0x3
multiline_comment|/* TX config register */
DECL|macro|DRVR_DRVRBAR_ENABLE
mdefine_line|#define DRVR_DRVRBAR_ENABLE                   0x0001
DECL|macro|TXCLK_MUX_SELECT_RCLK
mdefine_line|#define TXCLK_MUX_SELECT_RCLK                 0x0002
DECL|macro|TRANSMIT_TIMING_MARKER
mdefine_line|#define TRANSMIT_TIMING_MARKER                0x0004
DECL|macro|LOOPBACK_TIMING_MARKER
mdefine_line|#define LOOPBACK_TIMING_MARKER                0x0008
DECL|macro|TX_TEST_MODE_16MHz
mdefine_line|#define TX_TEST_MODE_16MHz                    0x0000
DECL|macro|TX_TEST_MODE_8MHz
mdefine_line|#define TX_TEST_MODE_8MHz                     0x0010
DECL|macro|TX_TEST_MODE_5_33MHz
mdefine_line|#define TX_TEST_MODE_5_33MHz                  0x0020
DECL|macro|TX_TEST_MODE_4MHz
mdefine_line|#define TX_TEST_MODE_4MHz                     0x0030
DECL|macro|TX_TEST_MODE_3_2MHz
mdefine_line|#define TX_TEST_MODE_3_2MHz                   0x0040
DECL|macro|TX_TEST_MODE_2_66MHz
mdefine_line|#define TX_TEST_MODE_2_66MHz                  0x0050
DECL|macro|TX_TEST_MODE_2_29MHz
mdefine_line|#define TX_TEST_MODE_2_29MHz                  0x0060
DECL|macro|TX_NORMAL_OPERATION
mdefine_line|#define TX_NORMAL_OPERATION                   0x0070
DECL|macro|ABR_ROUND_ROBIN
mdefine_line|#define ABR_ROUND_ROBIN                       0x0080
multiline_comment|/* TX status register */
DECL|macro|IDLE_CHANNELS_MASK
mdefine_line|#define IDLE_CHANNELS_MASK                    0x00FF
DECL|macro|ABR_CELL_COUNT_REACHED_MULT
mdefine_line|#define ABR_CELL_COUNT_REACHED_MULT           0x0100 
DECL|macro|ABR_CELL_COUNT_REACHED_MASK
mdefine_line|#define ABR_CELL_COUNT_REACHED_MASK           0xFF
multiline_comment|/* RX config register */
DECL|macro|NON_USER_CELLS_IN_ONE_CHANNEL
mdefine_line|#define NON_USER_CELLS_IN_ONE_CHANNEL         0x0008
DECL|macro|RX_ENABLE
mdefine_line|#define RX_ENABLE                             0x0010
DECL|macro|IGNORE_UNUSED_VPI_VCI_BITS_SET
mdefine_line|#define IGNORE_UNUSED_VPI_VCI_BITS_SET        0x0000
DECL|macro|NON_USER_UNUSED_VPI_VCI_BITS_SET
mdefine_line|#define NON_USER_UNUSED_VPI_VCI_BITS_SET      0x0020
DECL|macro|DISCARD_UNUSED_VPI_VCI_BITS_SET
mdefine_line|#define DISCARD_UNUSED_VPI_VCI_BITS_SET       0x0040
multiline_comment|/* RX line config register */
DECL|macro|SIGNAL_LOSS
mdefine_line|#define SIGNAL_LOSS                           0x0001
DECL|macro|FREQUENCY_DETECT_ERROR
mdefine_line|#define FREQUENCY_DETECT_ERROR                0x0002
DECL|macro|LOCK_DETECT_ERROR
mdefine_line|#define LOCK_DETECT_ERROR                     0x0004
DECL|macro|SELECT_INTERNAL_LOOPBACK
mdefine_line|#define SELECT_INTERNAL_LOOPBACK              0x0008
DECL|macro|LOCK_DETECT_ENABLE
mdefine_line|#define LOCK_DETECT_ENABLE                    0x0010
DECL|macro|FREQUENCY_DETECT_ENABLE
mdefine_line|#define FREQUENCY_DETECT_ENABLE               0x0020
DECL|macro|USER_FRAQ
mdefine_line|#define USER_FRAQ                             0x0040
DECL|macro|GXTALOUT_SELECT_DIV4
mdefine_line|#define GXTALOUT_SELECT_DIV4                  0x0080
DECL|macro|GXTALOUT_SELECT_NO_GATING
mdefine_line|#define GXTALOUT_SELECT_NO_GATING             0x0100
DECL|macro|TIMING_MARKER_RECEIVED
mdefine_line|#define TIMING_MARKER_RECEIVED                0x0200
multiline_comment|/* RX channel port */
DECL|macro|RX_CHANNEL_MASK
mdefine_line|#define RX_CHANNEL_MASK                       0x03FF
singleline_comment|// UNUSED                                     0x3C00
DECL|macro|FLUSH_CHANNEL
mdefine_line|#define FLUSH_CHANNEL                         0x4000
DECL|macro|RX_CHANNEL_UPDATE_IN_PROGRESS
mdefine_line|#define RX_CHANNEL_UPDATE_IN_PROGRESS         0x8000
multiline_comment|/* Receive queue entry */
DECL|macro|RX_Q_ENTRY_LENGTH_MASK
mdefine_line|#define RX_Q_ENTRY_LENGTH_MASK            0x0000FFFF
DECL|macro|RX_Q_ENTRY_CHANNEL_SHIFT
mdefine_line|#define RX_Q_ENTRY_CHANNEL_SHIFT          16
DECL|macro|SIMONS_DODGEY_MARKER
mdefine_line|#define SIMONS_DODGEY_MARKER              0x08000000
DECL|macro|RX_CONGESTION_EXPERIENCED
mdefine_line|#define RX_CONGESTION_EXPERIENCED         0x10000000
DECL|macro|RX_CRC_10_OK
mdefine_line|#define RX_CRC_10_OK                      0x20000000
DECL|macro|RX_CRC_32_OK
mdefine_line|#define RX_CRC_32_OK                      0x40000000
DECL|macro|RX_COMPLETE_FRAME
mdefine_line|#define RX_COMPLETE_FRAME                 0x80000000
multiline_comment|/*  Offsets and constants for use with the buffer memory         */
multiline_comment|/* Buffer pointers and channel types */
DECL|macro|BUFFER_PTR_MASK
mdefine_line|#define BUFFER_PTR_MASK                   0x0000FFFF
DECL|macro|RX_INT_THRESHOLD_MULT
mdefine_line|#define RX_INT_THRESHOLD_MULT             0x00010000
DECL|macro|RX_INT_THRESHOLD_MASK
mdefine_line|#define RX_INT_THRESHOLD_MASK             0x07FF
DECL|macro|INT_EVERY_N_CELLS
mdefine_line|#define INT_EVERY_N_CELLS                 0x08000000
DECL|macro|CONGESTION_EXPERIENCED
mdefine_line|#define CONGESTION_EXPERIENCED            0x10000000
DECL|macro|FIRST_CELL_OF_AAL5_FRAME
mdefine_line|#define FIRST_CELL_OF_AAL5_FRAME          0x20000000
DECL|macro|CHANNEL_TYPE_AAL5
mdefine_line|#define CHANNEL_TYPE_AAL5                 0x00000000
DECL|macro|CHANNEL_TYPE_RAW_CELLS
mdefine_line|#define CHANNEL_TYPE_RAW_CELLS            0x40000000
DECL|macro|CHANNEL_TYPE_AAL3_4
mdefine_line|#define CHANNEL_TYPE_AAL3_4               0x80000000
multiline_comment|/* Buffer status stuff */
DECL|macro|BUFF_STATUS_MASK
mdefine_line|#define BUFF_STATUS_MASK                  0x00030000
DECL|macro|BUFF_STATUS_EMPTY
mdefine_line|#define BUFF_STATUS_EMPTY                 0x00000000
DECL|macro|BUFF_STATUS_CELL_AV
mdefine_line|#define BUFF_STATUS_CELL_AV               0x00010000
DECL|macro|BUFF_STATUS_LAST_CELL_AV
mdefine_line|#define BUFF_STATUS_LAST_CELL_AV          0x00020000
multiline_comment|/* Transmit channel stuff */
multiline_comment|/* Receive channel stuff */
DECL|macro|RX_CHANNEL_DISABLED
mdefine_line|#define RX_CHANNEL_DISABLED               0x00000000
DECL|macro|RX_CHANNEL_IDLE
mdefine_line|#define RX_CHANNEL_IDLE                   0x00000001
multiline_comment|/*  General things */
DECL|macro|INITIAL_CRC
mdefine_line|#define INITIAL_CRC                       0xFFFFFFFF
singleline_comment|// A Horizon u32, a byte! Really nasty. Horizon pointers are (32 bit)
singleline_comment|// word addresses and so standard C pointer operations break (as they
singleline_comment|// assume byte addresses); so we pretend that Horizon words (and word
singleline_comment|// pointers) are bytes (and byte pointers) for the purposes of having
singleline_comment|// a memory map that works.
DECL|typedef|HDW
r_typedef
id|u8
id|HDW
suffix:semicolon
DECL|struct|cell_buf
r_typedef
r_struct
id|cell_buf
(brace
DECL|member|payload
id|HDW
id|payload
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|next
id|HDW
id|next
suffix:semicolon
DECL|member|cell_count
id|HDW
id|cell_count
suffix:semicolon
singleline_comment|// AAL5 rx bufs
DECL|member|res
id|HDW
id|res
suffix:semicolon
r_union
(brace
DECL|member|partial_crc
id|HDW
id|partial_crc
suffix:semicolon
singleline_comment|// AAL5 rx bufs
DECL|member|cell_header
id|HDW
id|cell_header
suffix:semicolon
singleline_comment|// RAW     bufs
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|typedef|cell_buf
)brace
id|cell_buf
suffix:semicolon
DECL|struct|tx_ch_desc
r_typedef
r_struct
id|tx_ch_desc
(brace
DECL|member|rd_buf_type
id|HDW
id|rd_buf_type
suffix:semicolon
DECL|member|wr_buf_type
id|HDW
id|wr_buf_type
suffix:semicolon
DECL|member|partial_crc
id|HDW
id|partial_crc
suffix:semicolon
DECL|member|cell_header
id|HDW
id|cell_header
suffix:semicolon
DECL|typedef|tx_ch_desc
)brace
id|tx_ch_desc
suffix:semicolon
DECL|struct|rx_ch_desc
r_typedef
r_struct
id|rx_ch_desc
(brace
DECL|member|wr_buf_type
id|HDW
id|wr_buf_type
suffix:semicolon
DECL|member|rd_buf_type
id|HDW
id|rd_buf_type
suffix:semicolon
DECL|typedef|rx_ch_desc
)brace
id|rx_ch_desc
suffix:semicolon
DECL|struct|rx_q_entry
r_typedef
r_struct
id|rx_q_entry
(brace
DECL|member|entry
id|HDW
id|entry
suffix:semicolon
DECL|typedef|rx_q_entry
)brace
id|rx_q_entry
suffix:semicolon
DECL|macro|TX_CHANS
mdefine_line|#define TX_CHANS 8
DECL|macro|RX_CHANS
mdefine_line|#define RX_CHANS 1024
DECL|macro|RX_QS
mdefine_line|#define RX_QS 1024
DECL|macro|MAX_VCS
mdefine_line|#define MAX_VCS RX_CHANS
multiline_comment|/* Horizon buffer memory map */
singleline_comment|// TX Channel Descriptors         2
singleline_comment|// TX Initial Buffers             8 // TX_CHANS
DECL|macro|BUFN1_SIZE
mdefine_line|#define BUFN1_SIZE              118 
singleline_comment|// (126 - TX_CHANS)
singleline_comment|//      RX/TX Start/End Buffers   4
DECL|macro|BUFN2_SIZE
mdefine_line|#define BUFN2_SIZE              124
singleline_comment|//      RX Queue Entries         64
DECL|macro|BUFN3_SIZE
mdefine_line|#define BUFN3_SIZE              192
singleline_comment|//      RX Channel Descriptors  128
DECL|macro|BUFN4_SIZE
mdefine_line|#define BUFN4_SIZE             1408
singleline_comment|//      TOTAL cell_buff chunks 2048
singleline_comment|//    cell_buf             bufs[2048];
singleline_comment|//    HDW                  dws[32768];
DECL|struct|MEMMAP
r_typedef
r_struct
id|MEMMAP
(brace
DECL|member|tx_descs
id|tx_ch_desc
id|tx_descs
(braket
id|TX_CHANS
)braket
suffix:semicolon
singleline_comment|//  8 *    4 =    32 , 0x0020
DECL|member|inittxbufs
id|cell_buf
id|inittxbufs
(braket
id|TX_CHANS
)braket
suffix:semicolon
singleline_comment|// these are really
DECL|member|bufn1
id|cell_buf
id|bufn1
(braket
id|BUFN1_SIZE
)braket
suffix:semicolon
singleline_comment|// part of this pool
DECL|member|txfreebufstart
id|cell_buf
id|txfreebufstart
suffix:semicolon
DECL|member|txfreebufend
id|cell_buf
id|txfreebufend
suffix:semicolon
DECL|member|rxfreebufstart
id|cell_buf
id|rxfreebufstart
suffix:semicolon
DECL|member|rxfreebufend
id|cell_buf
id|rxfreebufend
suffix:semicolon
singleline_comment|// 8+118+1+1+1+1+124 = 254
DECL|member|bufn2
id|cell_buf
id|bufn2
(braket
id|BUFN2_SIZE
)braket
suffix:semicolon
singleline_comment|// 16 *  254 =  4064 , 0x1000
DECL|member|rx_q_entries
id|rx_q_entry
id|rx_q_entries
(braket
id|RX_QS
)braket
suffix:semicolon
singleline_comment|//  1 * 1024 =  1024 , 0x1400
DECL|member|bufn3
id|cell_buf
id|bufn3
(braket
id|BUFN3_SIZE
)braket
suffix:semicolon
singleline_comment|// 16 *  192 =  3072 , 0x2000
DECL|member|rx_descs
id|rx_ch_desc
id|rx_descs
(braket
id|MAX_VCS
)braket
suffix:semicolon
singleline_comment|//  2 * 1024 =  2048 , 0x2800
DECL|member|bufn4
id|cell_buf
id|bufn4
(braket
id|BUFN4_SIZE
)braket
suffix:semicolon
singleline_comment|// 16 * 1408 = 22528 , 0x8000
DECL|typedef|MEMMAP
)brace
id|MEMMAP
suffix:semicolon
DECL|macro|memmap
mdefine_line|#define memmap ((MEMMAP *)0)
multiline_comment|/* end horizon specific bits */
r_typedef
r_enum
(brace
DECL|enumerator|aal0
id|aal0
comma
DECL|enumerator|aal34
id|aal34
comma
DECL|enumerator|aal5
id|aal5
DECL|typedef|hrz_aal
)brace
id|hrz_aal
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|tx_busy
id|tx_busy
comma
DECL|enumerator|rx_busy
id|rx_busy
comma
DECL|enumerator|ultra
id|ultra
DECL|typedef|hrz_flags
)brace
id|hrz_flags
suffix:semicolon
singleline_comment|// a single struct pointed to by atm_vcc-&gt;dev_data
r_typedef
r_struct
(brace
DECL|member|tx_rate
r_int
r_int
id|tx_rate
suffix:semicolon
DECL|member|rx_rate
r_int
r_int
id|rx_rate
suffix:semicolon
DECL|member|channel
id|u16
id|channel
suffix:semicolon
DECL|member|tx_xbr_bits
id|u16
id|tx_xbr_bits
suffix:semicolon
DECL|member|tx_pcr_bits
id|u16
id|tx_pcr_bits
suffix:semicolon
macro_line|#if 0
id|u16
id|tx_scr_bits
suffix:semicolon
id|u16
id|tx_bucket_bits
suffix:semicolon
macro_line|#endif
DECL|member|aal
id|hrz_aal
id|aal
suffix:semicolon
DECL|typedef|hrz_vcc
)brace
id|hrz_vcc
suffix:semicolon
DECL|struct|hrz_dev
r_struct
id|hrz_dev
(brace
DECL|member|iobase
id|u32
id|iobase
suffix:semicolon
DECL|member|membase
id|u32
op_star
id|membase
suffix:semicolon
DECL|member|rx_skb
r_struct
id|sk_buff
op_star
id|rx_skb
suffix:semicolon
singleline_comment|// skb being RXed
DECL|member|rx_bytes
r_int
r_int
id|rx_bytes
suffix:semicolon
singleline_comment|// bytes remaining to RX within region
DECL|member|rx_addr
r_void
op_star
id|rx_addr
suffix:semicolon
singleline_comment|// addr to send bytes to (for PIO)
DECL|member|rx_channel
r_int
r_int
id|rx_channel
suffix:semicolon
singleline_comment|// channel that the skb is going out on
DECL|member|tx_skb
r_struct
id|sk_buff
op_star
id|tx_skb
suffix:semicolon
singleline_comment|// skb being TXed
DECL|member|tx_bytes
r_int
r_int
id|tx_bytes
suffix:semicolon
singleline_comment|// bytes remaining to TX within region
DECL|member|tx_addr
r_void
op_star
id|tx_addr
suffix:semicolon
singleline_comment|// addr to send bytes from (for PIO)
DECL|member|tx_iovec
r_struct
id|iovec
op_star
id|tx_iovec
suffix:semicolon
singleline_comment|// remaining regions
DECL|member|tx_regions
r_int
r_int
id|tx_regions
suffix:semicolon
singleline_comment|// number of remaining regions
DECL|member|mem_lock
id|spinlock_t
id|mem_lock
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x20303
DECL|member|tx_queue
id|wait_queue_head_t
id|tx_queue
suffix:semicolon
macro_line|#else
DECL|member|tx_queue
r_struct
id|wait_queue
op_star
id|tx_queue
suffix:semicolon
macro_line|#endif
DECL|member|irq
id|u8
id|irq
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|tx_last
id|u8
id|tx_last
suffix:semicolon
DECL|member|tx_idle
id|u8
id|tx_idle
suffix:semicolon
DECL|member|rx_q_reset
id|rx_q_entry
op_star
id|rx_q_reset
suffix:semicolon
DECL|member|rx_q_entry
id|rx_q_entry
op_star
id|rx_q_entry
suffix:semicolon
DECL|member|rx_q_wrap
id|rx_q_entry
op_star
id|rx_q_wrap
suffix:semicolon
DECL|member|atm_dev
r_struct
id|atm_dev
op_star
id|atm_dev
suffix:semicolon
DECL|member|last_vc
id|u32
id|last_vc
suffix:semicolon
DECL|member|noof_spare_buffers
r_int
id|noof_spare_buffers
suffix:semicolon
DECL|member|spare_buffers
id|u16
id|spare_buffers
(braket
id|SPARE_BUFFER_POOL_SIZE
)braket
suffix:semicolon
DECL|member|tx_channel_record
id|u16
id|tx_channel_record
(braket
id|TX_CHANS
)braket
suffix:semicolon
singleline_comment|// this is what we follow when we get incoming data
DECL|member|txer
id|u32
id|txer
(braket
id|MAX_VCS
op_div
l_int|32
)braket
suffix:semicolon
DECL|member|rxer
r_struct
id|atm_vcc
op_star
id|rxer
(braket
id|MAX_VCS
)braket
suffix:semicolon
singleline_comment|// cell rate allocation
DECL|member|rate_lock
id|spinlock_t
id|rate_lock
suffix:semicolon
DECL|member|rx_avail
r_int
r_int
id|rx_avail
suffix:semicolon
DECL|member|tx_avail
r_int
r_int
id|tx_avail
suffix:semicolon
singleline_comment|// dev stats
DECL|member|tx_cell_count
r_int
r_int
id|tx_cell_count
suffix:semicolon
DECL|member|rx_cell_count
r_int
r_int
id|rx_cell_count
suffix:semicolon
DECL|member|hec_error_count
r_int
r_int
id|hec_error_count
suffix:semicolon
DECL|member|unassigned_cell_count
r_int
r_int
id|unassigned_cell_count
suffix:semicolon
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
DECL|member|prev
r_struct
id|hrz_dev
op_star
id|prev
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|hrz_dev
r_typedef
r_struct
id|hrz_dev
id|hrz_dev
suffix:semicolon
multiline_comment|/* macros for use later */
DECL|macro|BUF_PTR
mdefine_line|#define BUF_PTR(cbptr) ((cbptr) - (cell_buf *) 0)
DECL|macro|INTERESTING_INTERRUPTS
mdefine_line|#define INTERESTING_INTERRUPTS &bslash;&n;  (RX_DATA_AV | RX_DISABLED | TX_BUS_MASTER_COMPLETE | RX_BUS_MASTER_COMPLETE)
singleline_comment|// 190 cells by default (192 TX buffers - 2 elbow room, see docs)
DECL|macro|TX_AAL5_LIMIT
mdefine_line|#define TX_AAL5_LIMIT (190*ATM_CELL_PAYLOAD-ATM_AAL5_TRAILER) 
singleline_comment|// 9112
singleline_comment|// Have enough RX buffers (unless we allow other buffer splits)
DECL|macro|RX_AAL5_LIMIT
mdefine_line|#define RX_AAL5_LIMIT ATM_MAX_AAL5_PDU
multiline_comment|/* multi-statement macro protector */
DECL|macro|DW
mdefine_line|#define DW(x) do{ x } while(0)
DECL|macro|HRZ_DEV
mdefine_line|#define HRZ_DEV(atm_dev) ((hrz_dev *) (atm_dev)-&gt;dev_data)
DECL|macro|HRZ_VCC
mdefine_line|#define HRZ_VCC(atm_vcc) ((hrz_vcc *) (atm_vcc)-&gt;dev_data)
multiline_comment|/* Turn the LEDs on and off                                                 */
singleline_comment|// The LEDs bits are upside down in that setting the bit in the debug
singleline_comment|// register will turn the appropriate LED off.
DECL|macro|YELLOW_LED
mdefine_line|#define YELLOW_LED    DEBUG_BIT_0
DECL|macro|GREEN_LED
mdefine_line|#define GREEN_LED     DEBUG_BIT_1
DECL|macro|YELLOW_LED_OE
mdefine_line|#define YELLOW_LED_OE DEBUG_BIT_0_OE
DECL|macro|GREEN_LED_OE
mdefine_line|#define GREEN_LED_OE  DEBUG_BIT_1_OE
DECL|macro|GREEN_LED_OFF
mdefine_line|#define GREEN_LED_OFF(dev)                      &bslash;&n;  wr_regl (dev, CONTROL_0_REG, rd_regl (dev, CONTROL_0_REG) | GREEN_LED)
DECL|macro|GREEN_LED_ON
mdefine_line|#define GREEN_LED_ON(dev)                       &bslash;&n;  wr_regl (dev, CONTROL_0_REG, rd_regl (dev, CONTROL_0_REG) &amp;~ GREEN_LED)
DECL|macro|YELLOW_LED_OFF
mdefine_line|#define YELLOW_LED_OFF(dev)                     &bslash;&n;  wr_regl (dev, CONTROL_0_REG, rd_regl (dev, CONTROL_0_REG) | YELLOW_LED)
DECL|macro|YELLOW_LED_ON
mdefine_line|#define YELLOW_LED_ON(dev)                      &bslash;&n;  wr_regl (dev, CONTROL_0_REG, rd_regl (dev, CONTROL_0_REG) &amp;~ YELLOW_LED)
r_typedef
r_enum
(brace
DECL|enumerator|round_up
id|round_up
comma
DECL|enumerator|round_down
id|round_down
comma
DECL|enumerator|round_nearest
id|round_nearest
DECL|typedef|rounding
)brace
id|rounding
suffix:semicolon
macro_line|#endif /* DRIVER_ATM_HORIZON_H */
eof
