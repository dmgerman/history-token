multiline_comment|/*&n; *  &n; *  Copyright (C) 2002 Intersil Americas Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#ifndef _ISL_38XX_H
DECL|macro|_ISL_38XX_H
mdefine_line|#define _ISL_38XX_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|ISL38XX_CB_RX_QSIZE
mdefine_line|#define ISL38XX_CB_RX_QSIZE                     8
DECL|macro|ISL38XX_CB_TX_QSIZE
mdefine_line|#define ISL38XX_CB_TX_QSIZE                     32
multiline_comment|/* ISL38XX Access Point Specific definitions */
DECL|macro|ISL38XX_MAX_WDS_LINKS
mdefine_line|#define ISL38XX_MAX_WDS_LINKS                   8
multiline_comment|/* ISL38xx Client Specific definitions */
DECL|macro|ISL38XX_PSM_ACTIVE_STATE
mdefine_line|#define ISL38XX_PSM_ACTIVE_STATE                0
DECL|macro|ISL38XX_PSM_POWERSAVE_STATE
mdefine_line|#define ISL38XX_PSM_POWERSAVE_STATE             1
multiline_comment|/* ISL38XX Host Interface Definitions */
DECL|macro|ISL38XX_PCI_MEM_SIZE
mdefine_line|#define ISL38XX_PCI_MEM_SIZE                    0x02000
DECL|macro|ISL38XX_MEMORY_WINDOW_SIZE
mdefine_line|#define ISL38XX_MEMORY_WINDOW_SIZE              0x01000
DECL|macro|ISL38XX_DEV_FIRMWARE_ADDRES
mdefine_line|#define ISL38XX_DEV_FIRMWARE_ADDRES             0x20000
DECL|macro|ISL38XX_WRITEIO_DELAY
mdefine_line|#define ISL38XX_WRITEIO_DELAY                   10&t;/* in us */
DECL|macro|ISL38XX_RESET_DELAY
mdefine_line|#define ISL38XX_RESET_DELAY                     50&t;/* in ms */
DECL|macro|ISL38XX_WAIT_CYCLE
mdefine_line|#define ISL38XX_WAIT_CYCLE                      10&t;/* in 10ms */
DECL|macro|ISL38XX_MAX_WAIT_CYCLES
mdefine_line|#define ISL38XX_MAX_WAIT_CYCLES                 10
multiline_comment|/* PCI Memory Area */
DECL|macro|ISL38XX_HARDWARE_REG
mdefine_line|#define ISL38XX_HARDWARE_REG                    0x0000
DECL|macro|ISL38XX_CARDBUS_CIS
mdefine_line|#define ISL38XX_CARDBUS_CIS                     0x0800
DECL|macro|ISL38XX_DIRECT_MEM_WIN
mdefine_line|#define ISL38XX_DIRECT_MEM_WIN                  0x1000
multiline_comment|/* Hardware registers */
DECL|macro|ISL38XX_DEV_INT_REG
mdefine_line|#define ISL38XX_DEV_INT_REG                     0x0000
DECL|macro|ISL38XX_INT_IDENT_REG
mdefine_line|#define ISL38XX_INT_IDENT_REG                   0x0010
DECL|macro|ISL38XX_INT_ACK_REG
mdefine_line|#define ISL38XX_INT_ACK_REG                     0x0014
DECL|macro|ISL38XX_INT_EN_REG
mdefine_line|#define ISL38XX_INT_EN_REG                      0x0018
DECL|macro|ISL38XX_GEN_PURP_COM_REG_1
mdefine_line|#define ISL38XX_GEN_PURP_COM_REG_1              0x0020
DECL|macro|ISL38XX_GEN_PURP_COM_REG_2
mdefine_line|#define ISL38XX_GEN_PURP_COM_REG_2              0x0024
DECL|macro|ISL38XX_CTRL_BLK_BASE_REG
mdefine_line|#define ISL38XX_CTRL_BLK_BASE_REG               ISL38XX_GEN_PURP_COM_REG_1
DECL|macro|ISL38XX_DIR_MEM_BASE_REG
mdefine_line|#define ISL38XX_DIR_MEM_BASE_REG                0x0030
DECL|macro|ISL38XX_CTRL_STAT_REG
mdefine_line|#define ISL38XX_CTRL_STAT_REG                   0x0078
multiline_comment|/* High end mobos queue up pci writes, the following&n; * is used to &quot;read&quot; from after a write to force flush */
DECL|macro|ISL38XX_PCI_POSTING_FLUSH
mdefine_line|#define ISL38XX_PCI_POSTING_FLUSH&t;&t;ISL38XX_INT_EN_REG
multiline_comment|/**&n; * isl38xx_w32_flush - PCI iomem write helper&n; * @base: (host) memory base address of the device&n; * @val: 32bit value (host order) to write&n; * @offset: byte offset into @base to write value to&n; * &n; *  This helper takes care of writing a 32bit datum to the&n; *  specified offset into the device&squot;s pci memory space, and making sure &n; *  the pci memory buffers get flushed by performing one harmless read &n; *  from the %ISL38XX_PCI_POSTING_FLUSH offset.&n; */
r_static
r_inline
r_void
DECL|function|isl38xx_w32_flush
id|isl38xx_w32_flush
c_func
(paren
r_void
op_star
id|base
comma
id|u32
id|val
comma
r_int
r_int
id|offset
)paren
(brace
id|writel
c_func
(paren
id|val
comma
id|base
op_plus
id|offset
)paren
suffix:semicolon
(paren
r_void
)paren
id|readl
c_func
(paren
id|base
op_plus
id|ISL38XX_PCI_POSTING_FLUSH
)paren
suffix:semicolon
)brace
multiline_comment|/* Device Interrupt register bits */
DECL|macro|ISL38XX_DEV_INT_RESET
mdefine_line|#define ISL38XX_DEV_INT_RESET                   0x0001
DECL|macro|ISL38XX_DEV_INT_UPDATE
mdefine_line|#define ISL38XX_DEV_INT_UPDATE                  0x0002
DECL|macro|ISL38XX_DEV_INT_WAKEUP
mdefine_line|#define ISL38XX_DEV_INT_WAKEUP                  0x0008
DECL|macro|ISL38XX_DEV_INT_SLEEP
mdefine_line|#define ISL38XX_DEV_INT_SLEEP                   0x0010
multiline_comment|/* Interrupt Identification/Acknowledge/Enable register bits */
DECL|macro|ISL38XX_INT_IDENT_UPDATE
mdefine_line|#define ISL38XX_INT_IDENT_UPDATE                0x0002
DECL|macro|ISL38XX_INT_IDENT_INIT
mdefine_line|#define ISL38XX_INT_IDENT_INIT                  0x0004
DECL|macro|ISL38XX_INT_IDENT_WAKEUP
mdefine_line|#define ISL38XX_INT_IDENT_WAKEUP                0x0008
DECL|macro|ISL38XX_INT_IDENT_SLEEP
mdefine_line|#define ISL38XX_INT_IDENT_SLEEP                 0x0010
DECL|macro|ISL38XX_INT_SOURCES
mdefine_line|#define ISL38XX_INT_SOURCES                     0x001E
multiline_comment|/* Control/Status register bits */
multiline_comment|/* Looks like there are other meaningful bits&n;    0x20004400 seen in normal operation,&n;    0x200044db at &squot;timeout waiting for mgmt response&squot;&n;*/
DECL|macro|ISL38XX_CTRL_STAT_SLEEPMODE
mdefine_line|#define ISL38XX_CTRL_STAT_SLEEPMODE             0x00000200
DECL|macro|ISL38XX_CTRL_STAT_CLKRUN
mdefine_line|#define&t;ISL38XX_CTRL_STAT_CLKRUN&t;&t;0x00800000
DECL|macro|ISL38XX_CTRL_STAT_RESET
mdefine_line|#define ISL38XX_CTRL_STAT_RESET                 0x10000000
DECL|macro|ISL38XX_CTRL_STAT_RAMBOOT
mdefine_line|#define ISL38XX_CTRL_STAT_RAMBOOT               0x20000000
DECL|macro|ISL38XX_CTRL_STAT_STARTHALTED
mdefine_line|#define ISL38XX_CTRL_STAT_STARTHALTED           0x40000000
DECL|macro|ISL38XX_CTRL_STAT_HOST_OVERRIDE
mdefine_line|#define ISL38XX_CTRL_STAT_HOST_OVERRIDE         0x80000000
multiline_comment|/* Control Block definitions */
DECL|macro|ISL38XX_CB_RX_DATA_LQ
mdefine_line|#define ISL38XX_CB_RX_DATA_LQ                   0
DECL|macro|ISL38XX_CB_TX_DATA_LQ
mdefine_line|#define ISL38XX_CB_TX_DATA_LQ                   1
DECL|macro|ISL38XX_CB_RX_DATA_HQ
mdefine_line|#define ISL38XX_CB_RX_DATA_HQ                   2
DECL|macro|ISL38XX_CB_TX_DATA_HQ
mdefine_line|#define ISL38XX_CB_TX_DATA_HQ                   3
DECL|macro|ISL38XX_CB_RX_MGMTQ
mdefine_line|#define ISL38XX_CB_RX_MGMTQ                     4
DECL|macro|ISL38XX_CB_TX_MGMTQ
mdefine_line|#define ISL38XX_CB_TX_MGMTQ                     5
DECL|macro|ISL38XX_CB_QCOUNT
mdefine_line|#define ISL38XX_CB_QCOUNT                       6
DECL|macro|ISL38XX_CB_MGMT_QSIZE
mdefine_line|#define ISL38XX_CB_MGMT_QSIZE                   4
DECL|macro|ISL38XX_MIN_QTHRESHOLD
mdefine_line|#define ISL38XX_MIN_QTHRESHOLD                  4&t;/* fragments */
multiline_comment|/* Memory Manager definitions */
DECL|macro|MGMT_FRAME_SIZE
mdefine_line|#define MGMT_FRAME_SIZE                         1500&t;/* &gt;= size struct obj_bsslist */
DECL|macro|MGMT_TX_FRAME_COUNT
mdefine_line|#define MGMT_TX_FRAME_COUNT                     24&t;/* max 4 + spare 4 + 8 init */
DECL|macro|MGMT_RX_FRAME_COUNT
mdefine_line|#define MGMT_RX_FRAME_COUNT                     24&t;/* 4*4 + spare 8 */
DECL|macro|MGMT_FRAME_COUNT
mdefine_line|#define MGMT_FRAME_COUNT                        (MGMT_TX_FRAME_COUNT + MGMT_RX_FRAME_COUNT)
DECL|macro|CONTROL_BLOCK_SIZE
mdefine_line|#define CONTROL_BLOCK_SIZE                      1024&t;/* should be enough */
DECL|macro|PSM_FRAME_SIZE
mdefine_line|#define PSM_FRAME_SIZE                          1536
DECL|macro|PSM_MINIMAL_STATION_COUNT
mdefine_line|#define PSM_MINIMAL_STATION_COUNT               64
DECL|macro|PSM_FRAME_COUNT
mdefine_line|#define PSM_FRAME_COUNT                         PSM_MINIMAL_STATION_COUNT
DECL|macro|PSM_BUFFER_SIZE
mdefine_line|#define PSM_BUFFER_SIZE                         PSM_FRAME_SIZE * PSM_FRAME_COUNT
DECL|macro|MAX_TRAP_RX_QUEUE
mdefine_line|#define MAX_TRAP_RX_QUEUE                       4
DECL|macro|HOST_MEM_BLOCK
mdefine_line|#define HOST_MEM_BLOCK                          CONTROL_BLOCK_SIZE + PSM_BUFFER_SIZE
multiline_comment|/* Fragment package definitions */
DECL|macro|FRAGMENT_FLAG_MF
mdefine_line|#define FRAGMENT_FLAG_MF                        0x0001
DECL|macro|MAX_FRAGMENT_SIZE
mdefine_line|#define MAX_FRAGMENT_SIZE                       1536
multiline_comment|/* In monitor mode frames have a header. I don&squot;t know exactly how big those&n; * frame can be but I&squot;ve never seen any frame bigger than 1584... :&n; */
DECL|macro|MAX_FRAGMENT_SIZE_RX
mdefine_line|#define MAX_FRAGMENT_SIZE_RX&t;                1600
r_typedef
r_struct
(brace
DECL|member|address
id|u32
id|address
suffix:semicolon
multiline_comment|/* physical address on host */
DECL|member|size
id|u16
id|size
suffix:semicolon
multiline_comment|/* packet size */
DECL|member|flags
id|u16
id|flags
suffix:semicolon
multiline_comment|/* set of bit-wise flags */
DECL|typedef|isl38xx_fragment
)brace
id|isl38xx_fragment
suffix:semicolon
DECL|struct|isl38xx_cb
r_struct
id|isl38xx_cb
(brace
DECL|member|driver_curr_frag
id|u32
id|driver_curr_frag
(braket
id|ISL38XX_CB_QCOUNT
)braket
suffix:semicolon
DECL|member|device_curr_frag
id|u32
id|device_curr_frag
(braket
id|ISL38XX_CB_QCOUNT
)braket
suffix:semicolon
DECL|member|rx_data_low
id|isl38xx_fragment
id|rx_data_low
(braket
id|ISL38XX_CB_RX_QSIZE
)braket
suffix:semicolon
DECL|member|tx_data_low
id|isl38xx_fragment
id|tx_data_low
(braket
id|ISL38XX_CB_TX_QSIZE
)braket
suffix:semicolon
DECL|member|rx_data_high
id|isl38xx_fragment
id|rx_data_high
(braket
id|ISL38XX_CB_RX_QSIZE
)braket
suffix:semicolon
DECL|member|tx_data_high
id|isl38xx_fragment
id|tx_data_high
(braket
id|ISL38XX_CB_TX_QSIZE
)braket
suffix:semicolon
DECL|member|rx_data_mgmt
id|isl38xx_fragment
id|rx_data_mgmt
(braket
id|ISL38XX_CB_MGMT_QSIZE
)braket
suffix:semicolon
DECL|member|tx_data_mgmt
id|isl38xx_fragment
id|tx_data_mgmt
(braket
id|ISL38XX_CB_MGMT_QSIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|isl38xx_control_block
r_typedef
r_struct
id|isl38xx_cb
id|isl38xx_control_block
suffix:semicolon
multiline_comment|/* determine number of entries currently in queue */
r_int
id|isl38xx_in_queue
c_func
(paren
id|isl38xx_control_block
op_star
id|cb
comma
r_int
id|queue
)paren
suffix:semicolon
r_void
id|isl38xx_disable_interrupts
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_void
id|isl38xx_enable_common_interrupts
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_void
id|isl38xx_handle_sleep_request
c_func
(paren
id|isl38xx_control_block
op_star
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_void
id|isl38xx_handle_wakeup
c_func
(paren
id|isl38xx_control_block
op_star
comma
r_int
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_void
id|isl38xx_trigger_device
c_func
(paren
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_void
id|isl38xx_interface_reset
c_func
(paren
r_void
op_star
comma
id|dma_addr_t
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _ISL_38XX_H */
eof
