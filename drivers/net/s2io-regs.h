multiline_comment|/************************************************************************&n; * regs.h: A Linux PCI-X Ethernet driver for S2IO 10GbE Server NIC&n; * Copyright 2002 Raghavendra Koushik (raghavendra.koushik@s2io.com)&n;&n; * This software may be used and distributed according to the terms of&n; * the GNU General Public License (GPL), incorporated herein by reference.&n; * Drivers based on or derived from this code fall under the GPL and must&n; * retain the authorship, copyright and license notice.  This file is not&n; * a complete program and may only be used when the entire operating&n; * system is licensed under the GPL.&n; * See the file COPYING in this distribution for more information.&n; ************************************************************************/
macro_line|#ifndef _REGS_H
DECL|macro|_REGS_H
mdefine_line|#define _REGS_H
DECL|macro|TBD
mdefine_line|#define TBD 0
DECL|struct|_XENA_dev_config
r_typedef
r_struct
id|_XENA_dev_config
(brace
multiline_comment|/* Convention: mHAL_XXX is mask, vHAL_XXX is value */
multiline_comment|/* General Control-Status Registers */
DECL|member|general_int_status
id|u64
id|general_int_status
suffix:semicolon
DECL|macro|GEN_INTR_TXPIC
mdefine_line|#define GEN_INTR_TXPIC             BIT(0)
DECL|macro|GEN_INTR_TXDMA
mdefine_line|#define GEN_INTR_TXDMA             BIT(1)
DECL|macro|GEN_INTR_TXMAC
mdefine_line|#define GEN_INTR_TXMAC             BIT(2)
DECL|macro|GEN_INTR_TXXGXS
mdefine_line|#define GEN_INTR_TXXGXS            BIT(3)
DECL|macro|GEN_INTR_TXTRAFFIC
mdefine_line|#define GEN_INTR_TXTRAFFIC         BIT(8)
DECL|macro|GEN_INTR_RXPIC
mdefine_line|#define GEN_INTR_RXPIC             BIT(32)
DECL|macro|GEN_INTR_RXDMA
mdefine_line|#define GEN_INTR_RXDMA             BIT(33)
DECL|macro|GEN_INTR_RXMAC
mdefine_line|#define GEN_INTR_RXMAC             BIT(34)
DECL|macro|GEN_INTR_MC
mdefine_line|#define GEN_INTR_MC                BIT(35)
DECL|macro|GEN_INTR_RXXGXS
mdefine_line|#define GEN_INTR_RXXGXS            BIT(36)
DECL|macro|GEN_INTR_RXTRAFFIC
mdefine_line|#define GEN_INTR_RXTRAFFIC         BIT(40)
DECL|macro|GEN_ERROR_INTR
mdefine_line|#define GEN_ERROR_INTR             GEN_INTR_TXPIC | GEN_INTR_RXPIC | &bslash;&n;                                   GEN_INTR_TXDMA | GEN_INTR_RXDMA | &bslash;&n;                                   GEN_INTR_TXMAC | GEN_INTR_RXMAC | &bslash;&n;                                   GEN_INTR_TXXGXS| GEN_INTR_RXXGXS| &bslash;&n;                                   GEN_INTR_MC
DECL|member|general_int_mask
id|u64
id|general_int_mask
suffix:semicolon
DECL|member|unused0
id|u8
id|unused0
(braket
l_int|0x100
op_minus
l_int|0x10
)braket
suffix:semicolon
DECL|member|sw_reset
id|u64
id|sw_reset
suffix:semicolon
multiline_comment|/* XGXS must be removed from reset only once. */
DECL|macro|SW_RESET_XENA
mdefine_line|#define SW_RESET_XENA              vBIT(0xA5,0,8)
DECL|macro|SW_RESET_FLASH
mdefine_line|#define SW_RESET_FLASH             vBIT(0xA5,8,8)
DECL|macro|SW_RESET_EOI
mdefine_line|#define SW_RESET_EOI               vBIT(0xA5,16,8)
DECL|macro|SW_RESET_ALL
mdefine_line|#define SW_RESET_ALL               (SW_RESET_XENA     |   &bslash;&n;                                    SW_RESET_FLASH    |   &bslash;&n;                                    SW_RESET_EOI)
multiline_comment|/* The SW_RESET register must read this value after a successful reset. */
DECL|macro|SW_RESET_RAW_VAL
mdefine_line|#define&t;SW_RESET_RAW_VAL&t;&t;&t;0xA5000000
DECL|member|adapter_status
id|u64
id|adapter_status
suffix:semicolon
DECL|macro|ADAPTER_STATUS_TDMA_READY
mdefine_line|#define ADAPTER_STATUS_TDMA_READY          BIT(0)
DECL|macro|ADAPTER_STATUS_RDMA_READY
mdefine_line|#define ADAPTER_STATUS_RDMA_READY          BIT(1)
DECL|macro|ADAPTER_STATUS_PFC_READY
mdefine_line|#define ADAPTER_STATUS_PFC_READY           BIT(2)
DECL|macro|ADAPTER_STATUS_TMAC_BUF_EMPTY
mdefine_line|#define ADAPTER_STATUS_TMAC_BUF_EMPTY      BIT(3)
DECL|macro|ADAPTER_STATUS_PIC_QUIESCENT
mdefine_line|#define ADAPTER_STATUS_PIC_QUIESCENT       BIT(5)
DECL|macro|ADAPTER_STATUS_RMAC_REMOTE_FAULT
mdefine_line|#define ADAPTER_STATUS_RMAC_REMOTE_FAULT   BIT(6)
DECL|macro|ADAPTER_STATUS_RMAC_LOCAL_FAULT
mdefine_line|#define ADAPTER_STATUS_RMAC_LOCAL_FAULT    BIT(7)
DECL|macro|ADAPTER_STATUS_RMAC_PCC_IDLE
mdefine_line|#define ADAPTER_STATUS_RMAC_PCC_IDLE       vBIT(0xFF,8,8)
DECL|macro|ADAPTER_STATUS_RC_PRC_QUIESCENT
mdefine_line|#define ADAPTER_STATUS_RC_PRC_QUIESCENT    vBIT(0xFF,16,8)
DECL|macro|ADAPTER_STATUS_MC_DRAM_READY
mdefine_line|#define ADAPTER_STATUS_MC_DRAM_READY       BIT(24)
DECL|macro|ADAPTER_STATUS_MC_QUEUES_READY
mdefine_line|#define ADAPTER_STATUS_MC_QUEUES_READY     BIT(25)
DECL|macro|ADAPTER_STATUS_M_PLL_LOCK
mdefine_line|#define ADAPTER_STATUS_M_PLL_LOCK          BIT(30)
DECL|macro|ADAPTER_STATUS_P_PLL_LOCK
mdefine_line|#define ADAPTER_STATUS_P_PLL_LOCK          BIT(31)
DECL|member|adapter_control
id|u64
id|adapter_control
suffix:semicolon
DECL|macro|ADAPTER_CNTL_EN
mdefine_line|#define ADAPTER_CNTL_EN                    BIT(7)
DECL|macro|ADAPTER_EOI_TX_ON
mdefine_line|#define ADAPTER_EOI_TX_ON                  BIT(15)
DECL|macro|ADAPTER_LED_ON
mdefine_line|#define ADAPTER_LED_ON                     BIT(23)
DECL|macro|ADAPTER_UDPI
mdefine_line|#define ADAPTER_UDPI(val)                  vBIT(val,36,4)
DECL|macro|ADAPTER_WAIT_INT
mdefine_line|#define ADAPTER_WAIT_INT                   BIT(48)
DECL|macro|ADAPTER_ECC_EN
mdefine_line|#define ADAPTER_ECC_EN                     BIT(55)
DECL|member|serr_source
id|u64
id|serr_source
suffix:semicolon
DECL|macro|SERR_SOURCE_PIC
mdefine_line|#define SERR_SOURCE_PIC&t;&t;&t;&t;&t;BIT(0)
DECL|macro|SERR_SOURCE_TXDMA
mdefine_line|#define SERR_SOURCE_TXDMA&t;&t;&t;&t;BIT(1)
DECL|macro|SERR_SOURCE_RXDMA
mdefine_line|#define SERR_SOURCE_RXDMA&t;&t;&t;&t;BIT(2)
DECL|macro|SERR_SOURCE_MAC
mdefine_line|#define SERR_SOURCE_MAC                 BIT(3)
DECL|macro|SERR_SOURCE_MC
mdefine_line|#define SERR_SOURCE_MC                  BIT(4)
DECL|macro|SERR_SOURCE_XGXS
mdefine_line|#define SERR_SOURCE_XGXS                BIT(5)
DECL|macro|SERR_SOURCE_ANY
mdefine_line|#define&t;SERR_SOURCE_ANY&t;&t;&t;&t;&t;(SERR_SOURCE_PIC&t;&t;| &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;SERR_SOURCE_TXDMA&t;| &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;SERR_SOURCE_RXDMA&t;| &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;SERR_SOURCE_MAC&t;&t;| &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;SERR_SOURCE_MC      | &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;SERR_SOURCE_XGXS)
DECL|member|unused_0
id|u8
id|unused_0
(braket
l_int|0x800
op_minus
l_int|0x120
)braket
suffix:semicolon
multiline_comment|/* PCI-X Controller registers */
DECL|member|pic_int_status
id|u64
id|pic_int_status
suffix:semicolon
DECL|member|pic_int_mask
id|u64
id|pic_int_mask
suffix:semicolon
DECL|macro|PIC_INT_TX
mdefine_line|#define PIC_INT_TX                     BIT(0)
DECL|macro|PIC_INT_FLSH
mdefine_line|#define PIC_INT_FLSH                   BIT(1)
DECL|macro|PIC_INT_MDIO
mdefine_line|#define PIC_INT_MDIO                   BIT(2)
DECL|macro|PIC_INT_IIC
mdefine_line|#define PIC_INT_IIC                    BIT(3)
DECL|macro|PIC_INT_GPIO
mdefine_line|#define PIC_INT_GPIO                   BIT(4)
DECL|macro|PIC_INT_RX
mdefine_line|#define PIC_INT_RX                     BIT(32)
DECL|member|txpic_int_reg
id|u64
id|txpic_int_reg
suffix:semicolon
DECL|member|txpic_int_mask
id|u64
id|txpic_int_mask
suffix:semicolon
DECL|macro|PCIX_INT_REG_ECC_SG_ERR
mdefine_line|#define PCIX_INT_REG_ECC_SG_ERR                BIT(0)
DECL|macro|PCIX_INT_REG_ECC_DB_ERR
mdefine_line|#define PCIX_INT_REG_ECC_DB_ERR                BIT(1)
DECL|macro|PCIX_INT_REG_FLASHR_R_FSM_ERR
mdefine_line|#define PCIX_INT_REG_FLASHR_R_FSM_ERR          BIT(8)
DECL|macro|PCIX_INT_REG_FLASHR_W_FSM_ERR
mdefine_line|#define PCIX_INT_REG_FLASHR_W_FSM_ERR          BIT(9)
DECL|macro|PCIX_INT_REG_INI_TX_FSM_SERR
mdefine_line|#define PCIX_INT_REG_INI_TX_FSM_SERR           BIT(10)
DECL|macro|PCIX_INT_REG_INI_TXO_FSM_ERR
mdefine_line|#define PCIX_INT_REG_INI_TXO_FSM_ERR           BIT(11)
DECL|macro|PCIX_INT_REG_TRT_FSM_SERR
mdefine_line|#define PCIX_INT_REG_TRT_FSM_SERR              BIT(13)
DECL|macro|PCIX_INT_REG_SRT_FSM_SERR
mdefine_line|#define PCIX_INT_REG_SRT_FSM_SERR              BIT(14)
DECL|macro|PCIX_INT_REG_PIFR_FSM_SERR
mdefine_line|#define PCIX_INT_REG_PIFR_FSM_SERR             BIT(15)
DECL|macro|PCIX_INT_REG_WRC_TX_SEND_FSM_SERR
mdefine_line|#define PCIX_INT_REG_WRC_TX_SEND_FSM_SERR      BIT(21)
DECL|macro|PCIX_INT_REG_RRC_TX_REQ_FSM_SERR
mdefine_line|#define PCIX_INT_REG_RRC_TX_REQ_FSM_SERR       BIT(23)
DECL|macro|PCIX_INT_REG_INI_RX_FSM_SERR
mdefine_line|#define PCIX_INT_REG_INI_RX_FSM_SERR           BIT(48)
DECL|macro|PCIX_INT_REG_RA_RX_FSM_SERR
mdefine_line|#define PCIX_INT_REG_RA_RX_FSM_SERR            BIT(50)
multiline_comment|/*&n;#define PCIX_INT_REG_WRC_RX_SEND_FSM_SERR      BIT(52)&n;#define PCIX_INT_REG_RRC_RX_REQ_FSM_SERR       BIT(54)&n;#define PCIX_INT_REG_RRC_RX_SPLIT_FSM_SERR     BIT(58)&n;*/
DECL|member|txpic_alarms
id|u64
id|txpic_alarms
suffix:semicolon
DECL|member|rxpic_int_reg
id|u64
id|rxpic_int_reg
suffix:semicolon
DECL|member|rxpic_int_mask
id|u64
id|rxpic_int_mask
suffix:semicolon
DECL|member|rxpic_alarms
id|u64
id|rxpic_alarms
suffix:semicolon
DECL|member|flsh_int_reg
id|u64
id|flsh_int_reg
suffix:semicolon
DECL|member|flsh_int_mask
id|u64
id|flsh_int_mask
suffix:semicolon
DECL|macro|PIC_FLSH_INT_REG_CYCLE_FSM_ERR
mdefine_line|#define PIC_FLSH_INT_REG_CYCLE_FSM_ERR         BIT(63)
DECL|macro|PIC_FLSH_INT_REG_ERR
mdefine_line|#define PIC_FLSH_INT_REG_ERR                   BIT(62)
DECL|member|flash_alarms
id|u64
id|flash_alarms
suffix:semicolon
DECL|member|mdio_int_reg
id|u64
id|mdio_int_reg
suffix:semicolon
DECL|member|mdio_int_mask
id|u64
id|mdio_int_mask
suffix:semicolon
DECL|macro|MDIO_INT_REG_MDIO_BUS_ERR
mdefine_line|#define MDIO_INT_REG_MDIO_BUS_ERR              BIT(0)
DECL|macro|MDIO_INT_REG_DTX_BUS_ERR
mdefine_line|#define MDIO_INT_REG_DTX_BUS_ERR               BIT(8)
DECL|macro|MDIO_INT_REG_LASI
mdefine_line|#define MDIO_INT_REG_LASI                      BIT(39)
DECL|member|mdio_alarms
id|u64
id|mdio_alarms
suffix:semicolon
DECL|member|iic_int_reg
id|u64
id|iic_int_reg
suffix:semicolon
DECL|member|iic_int_mask
id|u64
id|iic_int_mask
suffix:semicolon
DECL|macro|IIC_INT_REG_BUS_FSM_ERR
mdefine_line|#define IIC_INT_REG_BUS_FSM_ERR                BIT(4)
DECL|macro|IIC_INT_REG_BIT_FSM_ERR
mdefine_line|#define IIC_INT_REG_BIT_FSM_ERR                BIT(5)
DECL|macro|IIC_INT_REG_CYCLE_FSM_ERR
mdefine_line|#define IIC_INT_REG_CYCLE_FSM_ERR              BIT(6)
DECL|macro|IIC_INT_REG_REQ_FSM_ERR
mdefine_line|#define IIC_INT_REG_REQ_FSM_ERR                BIT(7)
DECL|macro|IIC_INT_REG_ACK_ERR
mdefine_line|#define IIC_INT_REG_ACK_ERR                    BIT(8)
DECL|member|iic_alarms
id|u64
id|iic_alarms
suffix:semicolon
DECL|member|unused4
id|u8
id|unused4
(braket
l_int|0x08
)braket
suffix:semicolon
DECL|member|gpio_int_reg
id|u64
id|gpio_int_reg
suffix:semicolon
DECL|member|gpio_int_mask
id|u64
id|gpio_int_mask
suffix:semicolon
DECL|member|gpio_alarms
id|u64
id|gpio_alarms
suffix:semicolon
DECL|member|unused5
id|u8
id|unused5
(braket
l_int|0x38
)braket
suffix:semicolon
DECL|member|tx_traffic_int
id|u64
id|tx_traffic_int
suffix:semicolon
DECL|macro|TX_TRAFFIC_INT_n
mdefine_line|#define TX_TRAFFIC_INT_n(n)                    BIT(n)
DECL|member|tx_traffic_mask
id|u64
id|tx_traffic_mask
suffix:semicolon
DECL|member|rx_traffic_int
id|u64
id|rx_traffic_int
suffix:semicolon
DECL|macro|RX_TRAFFIC_INT_n
mdefine_line|#define RX_TRAFFIC_INT_n(n)                    BIT(n)
DECL|member|rx_traffic_mask
id|u64
id|rx_traffic_mask
suffix:semicolon
multiline_comment|/* PIC Control registers */
DECL|member|pic_control
id|u64
id|pic_control
suffix:semicolon
DECL|macro|PIC_CNTL_RX_ALARM_MAP_1
mdefine_line|#define PIC_CNTL_RX_ALARM_MAP_1                BIT(0)
DECL|macro|PIC_CNTL_SHARED_SPLITS
mdefine_line|#define PIC_CNTL_SHARED_SPLITS(n)              vBIT(n,11,4)
DECL|member|swapper_ctrl
id|u64
id|swapper_ctrl
suffix:semicolon
DECL|macro|SWAPPER_CTRL_PIF_R_FE
mdefine_line|#define SWAPPER_CTRL_PIF_R_FE                  BIT(0)
DECL|macro|SWAPPER_CTRL_PIF_R_SE
mdefine_line|#define SWAPPER_CTRL_PIF_R_SE                  BIT(1)
DECL|macro|SWAPPER_CTRL_PIF_W_FE
mdefine_line|#define SWAPPER_CTRL_PIF_W_FE                  BIT(8)
DECL|macro|SWAPPER_CTRL_PIF_W_SE
mdefine_line|#define SWAPPER_CTRL_PIF_W_SE                  BIT(9)
DECL|macro|SWAPPER_CTRL_TXP_FE
mdefine_line|#define SWAPPER_CTRL_TXP_FE                    BIT(16)
DECL|macro|SWAPPER_CTRL_TXP_SE
mdefine_line|#define SWAPPER_CTRL_TXP_SE                    BIT(17)
DECL|macro|SWAPPER_CTRL_TXD_R_FE
mdefine_line|#define SWAPPER_CTRL_TXD_R_FE                  BIT(18)
DECL|macro|SWAPPER_CTRL_TXD_R_SE
mdefine_line|#define SWAPPER_CTRL_TXD_R_SE                  BIT(19)
DECL|macro|SWAPPER_CTRL_TXD_W_FE
mdefine_line|#define SWAPPER_CTRL_TXD_W_FE                  BIT(20)
DECL|macro|SWAPPER_CTRL_TXD_W_SE
mdefine_line|#define SWAPPER_CTRL_TXD_W_SE                  BIT(21)
DECL|macro|SWAPPER_CTRL_TXF_R_FE
mdefine_line|#define SWAPPER_CTRL_TXF_R_FE                  BIT(22)
DECL|macro|SWAPPER_CTRL_TXF_R_SE
mdefine_line|#define SWAPPER_CTRL_TXF_R_SE                  BIT(23)
DECL|macro|SWAPPER_CTRL_RXD_R_FE
mdefine_line|#define SWAPPER_CTRL_RXD_R_FE                  BIT(32)
DECL|macro|SWAPPER_CTRL_RXD_R_SE
mdefine_line|#define SWAPPER_CTRL_RXD_R_SE                  BIT(33)
DECL|macro|SWAPPER_CTRL_RXD_W_FE
mdefine_line|#define SWAPPER_CTRL_RXD_W_FE                  BIT(34)
DECL|macro|SWAPPER_CTRL_RXD_W_SE
mdefine_line|#define SWAPPER_CTRL_RXD_W_SE                  BIT(35)
DECL|macro|SWAPPER_CTRL_RXF_W_FE
mdefine_line|#define SWAPPER_CTRL_RXF_W_FE                  BIT(36)
DECL|macro|SWAPPER_CTRL_RXF_W_SE
mdefine_line|#define SWAPPER_CTRL_RXF_W_SE                  BIT(37)
DECL|macro|SWAPPER_CTRL_XMSI_FE
mdefine_line|#define SWAPPER_CTRL_XMSI_FE                   BIT(40)
DECL|macro|SWAPPER_CTRL_XMSI_SE
mdefine_line|#define SWAPPER_CTRL_XMSI_SE                   BIT(41)
DECL|macro|SWAPPER_CTRL_STATS_FE
mdefine_line|#define SWAPPER_CTRL_STATS_FE                  BIT(48)
DECL|macro|SWAPPER_CTRL_STATS_SE
mdefine_line|#define SWAPPER_CTRL_STATS_SE                  BIT(49)
DECL|member|pif_rd_swapper_fb
id|u64
id|pif_rd_swapper_fb
suffix:semicolon
DECL|macro|IF_RD_SWAPPER_FB
mdefine_line|#define IF_RD_SWAPPER_FB                            0x0123456789ABCDEF
DECL|member|scheduled_int_ctrl
id|u64
id|scheduled_int_ctrl
suffix:semicolon
DECL|macro|SCHED_INT_CTRL_TIMER_EN
mdefine_line|#define SCHED_INT_CTRL_TIMER_EN                BIT(0)
DECL|macro|SCHED_INT_CTRL_ONE_SHOT
mdefine_line|#define SCHED_INT_CTRL_ONE_SHOT                BIT(1)
DECL|macro|SCHED_INT_CTRL_INT2MSI
mdefine_line|#define SCHED_INT_CTRL_INT2MSI                 TBD
DECL|macro|SCHED_INT_PERIOD
mdefine_line|#define SCHED_INT_PERIOD                       TBD
DECL|member|txreqtimeout
id|u64
id|txreqtimeout
suffix:semicolon
DECL|macro|TXREQTO_VAL
mdefine_line|#define TXREQTO_VAL(val)&t;&t;&t;&t;&t;&t;vBIT(val,0,32)
DECL|macro|TXREQTO_EN
mdefine_line|#define TXREQTO_EN&t;&t;&t;&t;&t;&t;&t;&t;BIT(63)
DECL|member|statsreqtimeout
id|u64
id|statsreqtimeout
suffix:semicolon
DECL|macro|STATREQTO_VAL
mdefine_line|#define STATREQTO_VAL(n)                       TBD
DECL|macro|STATREQTO_EN
mdefine_line|#define STATREQTO_EN                           BIT(63)
DECL|member|read_retry_delay
id|u64
id|read_retry_delay
suffix:semicolon
DECL|member|read_retry_acceleration
id|u64
id|read_retry_acceleration
suffix:semicolon
DECL|member|write_retry_delay
id|u64
id|write_retry_delay
suffix:semicolon
DECL|member|write_retry_acceleration
id|u64
id|write_retry_acceleration
suffix:semicolon
DECL|member|xmsi_control
id|u64
id|xmsi_control
suffix:semicolon
DECL|member|xmsi_access
id|u64
id|xmsi_access
suffix:semicolon
DECL|member|xmsi_address
id|u64
id|xmsi_address
suffix:semicolon
DECL|member|xmsi_data
id|u64
id|xmsi_data
suffix:semicolon
DECL|member|rx_mat
id|u64
id|rx_mat
suffix:semicolon
DECL|member|unused6
id|u8
id|unused6
(braket
l_int|0x8
)braket
suffix:semicolon
DECL|member|tx_mat0_7
id|u64
id|tx_mat0_7
suffix:semicolon
DECL|member|tx_mat8_15
id|u64
id|tx_mat8_15
suffix:semicolon
DECL|member|tx_mat16_23
id|u64
id|tx_mat16_23
suffix:semicolon
DECL|member|tx_mat24_31
id|u64
id|tx_mat24_31
suffix:semicolon
DECL|member|tx_mat32_39
id|u64
id|tx_mat32_39
suffix:semicolon
DECL|member|tx_mat40_47
id|u64
id|tx_mat40_47
suffix:semicolon
DECL|member|tx_mat48_55
id|u64
id|tx_mat48_55
suffix:semicolon
DECL|member|tx_mat56_63
id|u64
id|tx_mat56_63
suffix:semicolon
DECL|member|unused_1
id|u8
id|unused_1
(braket
l_int|0x10
)braket
suffix:semicolon
multiline_comment|/* Automated statistics collection */
DECL|member|stat_cfg
id|u64
id|stat_cfg
suffix:semicolon
DECL|macro|STAT_CFG_STAT_EN
mdefine_line|#define STAT_CFG_STAT_EN           BIT(0)
DECL|macro|STAT_CFG_ONE_SHOT_EN
mdefine_line|#define STAT_CFG_ONE_SHOT_EN       BIT(1)
DECL|macro|STAT_CFG_STAT_NS_EN
mdefine_line|#define STAT_CFG_STAT_NS_EN        BIT(8)
DECL|macro|STAT_CFG_STAT_RO
mdefine_line|#define STAT_CFG_STAT_RO           BIT(9)
DECL|macro|STAT_TRSF_PER
mdefine_line|#define STAT_TRSF_PER(n)           TBD
DECL|macro|PER_SEC
mdefine_line|#define&t;PER_SEC&t;&t;&t;&t;&t;   0x208d5
DECL|macro|SET_UPDT_PERIOD
mdefine_line|#define&t;SET_UPDT_PERIOD(n)&t;&t;   vBIT((PER_SEC*n),32,32)
DECL|member|stat_addr
id|u64
id|stat_addr
suffix:semicolon
multiline_comment|/* General Configuration */
DECL|member|mdio_control
id|u64
id|mdio_control
suffix:semicolon
DECL|member|dtx_control
id|u64
id|dtx_control
suffix:semicolon
DECL|member|i2c_control
id|u64
id|i2c_control
suffix:semicolon
DECL|macro|I2C_CONTROL_DEV_ID
mdefine_line|#define&t;I2C_CONTROL_DEV_ID(id)&t;&t;vBIT(id,1,3)
DECL|macro|I2C_CONTROL_ADDR
mdefine_line|#define&t;I2C_CONTROL_ADDR(addr)&t;&t;vBIT(addr,5,11)
DECL|macro|I2C_CONTROL_BYTE_CNT
mdefine_line|#define&t;I2C_CONTROL_BYTE_CNT(cnt)&t;vBIT(cnt,22,2)
DECL|macro|I2C_CONTROL_READ
mdefine_line|#define&t;I2C_CONTROL_READ&t;&t;&t;BIT(24)
DECL|macro|I2C_CONTROL_NACK
mdefine_line|#define&t;I2C_CONTROL_NACK&t;&t;&t;BIT(25)
DECL|macro|I2C_CONTROL_CNTL_START
mdefine_line|#define&t;I2C_CONTROL_CNTL_START&t;&t;vBIT(0xE,28,4)
DECL|macro|I2C_CONTROL_CNTL_END
mdefine_line|#define&t;I2C_CONTROL_CNTL_END(val)&t;(val &amp; vBIT(0x1,28,4))
DECL|macro|I2C_CONTROL_GET_DATA
mdefine_line|#define&t;I2C_CONTROL_GET_DATA(val)&t;(u32)(val &amp; 0xFFFFFFFF)
DECL|macro|I2C_CONTROL_SET_DATA
mdefine_line|#define&t;I2C_CONTROL_SET_DATA(val)&t;vBIT(val,32,32)
DECL|member|gpio_control
id|u64
id|gpio_control
suffix:semicolon
DECL|macro|GPIO_CTRL_GPIO_0
mdefine_line|#define GPIO_CTRL_GPIO_0&t;&t;BIT(8)
DECL|member|unused7
id|u8
id|unused7
(braket
l_int|0x600
)braket
suffix:semicolon
multiline_comment|/* TxDMA registers */
DECL|member|txdma_int_status
id|u64
id|txdma_int_status
suffix:semicolon
DECL|member|txdma_int_mask
id|u64
id|txdma_int_mask
suffix:semicolon
DECL|macro|TXDMA_PFC_INT
mdefine_line|#define TXDMA_PFC_INT                  BIT(0)
DECL|macro|TXDMA_TDA_INT
mdefine_line|#define TXDMA_TDA_INT                  BIT(1)
DECL|macro|TXDMA_PCC_INT
mdefine_line|#define TXDMA_PCC_INT                  BIT(2)
DECL|macro|TXDMA_TTI_INT
mdefine_line|#define TXDMA_TTI_INT                  BIT(3)
DECL|macro|TXDMA_LSO_INT
mdefine_line|#define TXDMA_LSO_INT                  BIT(4)
DECL|macro|TXDMA_TPA_INT
mdefine_line|#define TXDMA_TPA_INT                  BIT(5)
DECL|macro|TXDMA_SM_INT
mdefine_line|#define TXDMA_SM_INT                   BIT(6)
DECL|member|pfc_err_reg
id|u64
id|pfc_err_reg
suffix:semicolon
DECL|member|pfc_err_mask
id|u64
id|pfc_err_mask
suffix:semicolon
DECL|member|pfc_err_alarm
id|u64
id|pfc_err_alarm
suffix:semicolon
DECL|member|tda_err_reg
id|u64
id|tda_err_reg
suffix:semicolon
DECL|member|tda_err_mask
id|u64
id|tda_err_mask
suffix:semicolon
DECL|member|tda_err_alarm
id|u64
id|tda_err_alarm
suffix:semicolon
DECL|member|pcc_err_reg
id|u64
id|pcc_err_reg
suffix:semicolon
DECL|macro|PCC_FB_ECC_DB_ERR
mdefine_line|#define PCC_FB_ECC_DB_ERR&t;&t;vBIT(0xFF, 16, 8)
DECL|member|pcc_err_mask
id|u64
id|pcc_err_mask
suffix:semicolon
DECL|member|pcc_err_alarm
id|u64
id|pcc_err_alarm
suffix:semicolon
DECL|member|tti_err_reg
id|u64
id|tti_err_reg
suffix:semicolon
DECL|member|tti_err_mask
id|u64
id|tti_err_mask
suffix:semicolon
DECL|member|tti_err_alarm
id|u64
id|tti_err_alarm
suffix:semicolon
DECL|member|lso_err_reg
id|u64
id|lso_err_reg
suffix:semicolon
DECL|member|lso_err_mask
id|u64
id|lso_err_mask
suffix:semicolon
DECL|member|lso_err_alarm
id|u64
id|lso_err_alarm
suffix:semicolon
DECL|member|tpa_err_reg
id|u64
id|tpa_err_reg
suffix:semicolon
DECL|member|tpa_err_mask
id|u64
id|tpa_err_mask
suffix:semicolon
DECL|member|tpa_err_alarm
id|u64
id|tpa_err_alarm
suffix:semicolon
DECL|member|sm_err_reg
id|u64
id|sm_err_reg
suffix:semicolon
DECL|member|sm_err_mask
id|u64
id|sm_err_mask
suffix:semicolon
DECL|member|sm_err_alarm
id|u64
id|sm_err_alarm
suffix:semicolon
DECL|member|unused8
id|u8
id|unused8
(braket
l_int|0x100
op_minus
l_int|0xB8
)braket
suffix:semicolon
multiline_comment|/* TxDMA arbiter */
DECL|member|tx_dma_wrap_stat
id|u64
id|tx_dma_wrap_stat
suffix:semicolon
multiline_comment|/* Tx FIFO controller */
DECL|macro|X_MAX_FIFOS
mdefine_line|#define X_MAX_FIFOS                        8
DECL|macro|X_FIFO_MAX_LEN
mdefine_line|#define X_FIFO_MAX_LEN                     0x1FFF&t;/*8191 */
DECL|member|tx_fifo_partition_0
id|u64
id|tx_fifo_partition_0
suffix:semicolon
DECL|macro|TX_FIFO_PARTITION_EN
mdefine_line|#define TX_FIFO_PARTITION_EN               BIT(0)
DECL|macro|TX_FIFO_PARTITION_0_PRI
mdefine_line|#define TX_FIFO_PARTITION_0_PRI(val)       vBIT(val,5,3)
DECL|macro|TX_FIFO_PARTITION_0_LEN
mdefine_line|#define TX_FIFO_PARTITION_0_LEN(val)       vBIT(val,19,13)
DECL|macro|TX_FIFO_PARTITION_1_PRI
mdefine_line|#define TX_FIFO_PARTITION_1_PRI(val)       vBIT(val,37,3)
DECL|macro|TX_FIFO_PARTITION_1_LEN
mdefine_line|#define TX_FIFO_PARTITION_1_LEN(val)       vBIT(val,51,13  )
DECL|member|tx_fifo_partition_1
id|u64
id|tx_fifo_partition_1
suffix:semicolon
DECL|macro|TX_FIFO_PARTITION_2_PRI
mdefine_line|#define TX_FIFO_PARTITION_2_PRI(val)       vBIT(val,5,3)
DECL|macro|TX_FIFO_PARTITION_2_LEN
mdefine_line|#define TX_FIFO_PARTITION_2_LEN(val)       vBIT(val,19,13)
DECL|macro|TX_FIFO_PARTITION_3_PRI
mdefine_line|#define TX_FIFO_PARTITION_3_PRI(val)       vBIT(val,37,3)
DECL|macro|TX_FIFO_PARTITION_3_LEN
mdefine_line|#define TX_FIFO_PARTITION_3_LEN(val)       vBIT(val,51,13)
DECL|member|tx_fifo_partition_2
id|u64
id|tx_fifo_partition_2
suffix:semicolon
DECL|macro|TX_FIFO_PARTITION_4_PRI
mdefine_line|#define TX_FIFO_PARTITION_4_PRI(val)       vBIT(val,5,3)
DECL|macro|TX_FIFO_PARTITION_4_LEN
mdefine_line|#define TX_FIFO_PARTITION_4_LEN(val)       vBIT(val,19,13)
DECL|macro|TX_FIFO_PARTITION_5_PRI
mdefine_line|#define TX_FIFO_PARTITION_5_PRI(val)       vBIT(val,37,3)
DECL|macro|TX_FIFO_PARTITION_5_LEN
mdefine_line|#define TX_FIFO_PARTITION_5_LEN(val)       vBIT(val,51,13)
DECL|member|tx_fifo_partition_3
id|u64
id|tx_fifo_partition_3
suffix:semicolon
DECL|macro|TX_FIFO_PARTITION_6_PRI
mdefine_line|#define TX_FIFO_PARTITION_6_PRI(val)       vBIT(val,5,3)
DECL|macro|TX_FIFO_PARTITION_6_LEN
mdefine_line|#define TX_FIFO_PARTITION_6_LEN(val)       vBIT(val,19,13)
DECL|macro|TX_FIFO_PARTITION_7_PRI
mdefine_line|#define TX_FIFO_PARTITION_7_PRI(val)       vBIT(val,37,3)
DECL|macro|TX_FIFO_PARTITION_7_LEN
mdefine_line|#define TX_FIFO_PARTITION_7_LEN(val)       vBIT(val,51,13)
DECL|macro|TX_FIFO_PARTITION_PRI_0
mdefine_line|#define TX_FIFO_PARTITION_PRI_0                 0&t;/* highest */
DECL|macro|TX_FIFO_PARTITION_PRI_1
mdefine_line|#define TX_FIFO_PARTITION_PRI_1                 1
DECL|macro|TX_FIFO_PARTITION_PRI_2
mdefine_line|#define TX_FIFO_PARTITION_PRI_2                 2
DECL|macro|TX_FIFO_PARTITION_PRI_3
mdefine_line|#define TX_FIFO_PARTITION_PRI_3                 3
DECL|macro|TX_FIFO_PARTITION_PRI_4
mdefine_line|#define TX_FIFO_PARTITION_PRI_4                 4
DECL|macro|TX_FIFO_PARTITION_PRI_5
mdefine_line|#define TX_FIFO_PARTITION_PRI_5                 5
DECL|macro|TX_FIFO_PARTITION_PRI_6
mdefine_line|#define TX_FIFO_PARTITION_PRI_6                 6
DECL|macro|TX_FIFO_PARTITION_PRI_7
mdefine_line|#define TX_FIFO_PARTITION_PRI_7                 7&t;/* lowest */
DECL|member|tx_w_round_robin_0
id|u64
id|tx_w_round_robin_0
suffix:semicolon
DECL|member|tx_w_round_robin_1
id|u64
id|tx_w_round_robin_1
suffix:semicolon
DECL|member|tx_w_round_robin_2
id|u64
id|tx_w_round_robin_2
suffix:semicolon
DECL|member|tx_w_round_robin_3
id|u64
id|tx_w_round_robin_3
suffix:semicolon
DECL|member|tx_w_round_robin_4
id|u64
id|tx_w_round_robin_4
suffix:semicolon
DECL|member|tti_command_mem
id|u64
id|tti_command_mem
suffix:semicolon
DECL|macro|TTI_CMD_MEM_WE
mdefine_line|#define TTI_CMD_MEM_WE                     BIT(7)
DECL|macro|TTI_CMD_MEM_STROBE_NEW_CMD
mdefine_line|#define TTI_CMD_MEM_STROBE_NEW_CMD         BIT(15)
DECL|macro|TTI_CMD_MEM_STROBE_BEING_EXECUTED
mdefine_line|#define TTI_CMD_MEM_STROBE_BEING_EXECUTED  BIT(15)
DECL|macro|TTI_CMD_MEM_OFFSET
mdefine_line|#define TTI_CMD_MEM_OFFSET(n)              vBIT(n,26,6)
DECL|member|tti_data1_mem
id|u64
id|tti_data1_mem
suffix:semicolon
DECL|macro|TTI_DATA1_MEM_TX_TIMER_VAL
mdefine_line|#define TTI_DATA1_MEM_TX_TIMER_VAL(n)      vBIT(n,6,26)
DECL|macro|TTI_DATA1_MEM_TX_TIMER_AC_CI
mdefine_line|#define TTI_DATA1_MEM_TX_TIMER_AC_CI(n)    vBIT(n,38,2)
DECL|macro|TTI_DATA1_MEM_TX_TIMER_AC_EN
mdefine_line|#define TTI_DATA1_MEM_TX_TIMER_AC_EN       BIT(38)
DECL|macro|TTI_DATA1_MEM_TX_TIMER_CI_EN
mdefine_line|#define TTI_DATA1_MEM_TX_TIMER_CI_EN       BIT(39)
DECL|macro|TTI_DATA1_MEM_TX_URNG_A
mdefine_line|#define TTI_DATA1_MEM_TX_URNG_A(n)         vBIT(n,41,7)
DECL|macro|TTI_DATA1_MEM_TX_URNG_B
mdefine_line|#define TTI_DATA1_MEM_TX_URNG_B(n)         vBIT(n,49,7)
DECL|macro|TTI_DATA1_MEM_TX_URNG_C
mdefine_line|#define TTI_DATA1_MEM_TX_URNG_C(n)         vBIT(n,57,7)
DECL|member|tti_data2_mem
id|u64
id|tti_data2_mem
suffix:semicolon
DECL|macro|TTI_DATA2_MEM_TX_UFC_A
mdefine_line|#define TTI_DATA2_MEM_TX_UFC_A(n)          vBIT(n,0,16)
DECL|macro|TTI_DATA2_MEM_TX_UFC_B
mdefine_line|#define TTI_DATA2_MEM_TX_UFC_B(n)          vBIT(n,16,16)
DECL|macro|TTI_DATA2_MEM_TX_UFC_C
mdefine_line|#define TTI_DATA2_MEM_TX_UFC_C(n)          vBIT(n,32,16)
DECL|macro|TTI_DATA2_MEM_TX_UFC_D
mdefine_line|#define TTI_DATA2_MEM_TX_UFC_D(n)          vBIT(n,48,16)
multiline_comment|/* Tx Protocol assist */
DECL|member|tx_pa_cfg
id|u64
id|tx_pa_cfg
suffix:semicolon
DECL|macro|TX_PA_CFG_IGNORE_FRM_ERR
mdefine_line|#define TX_PA_CFG_IGNORE_FRM_ERR           BIT(1)
DECL|macro|TX_PA_CFG_IGNORE_SNAP_OUI
mdefine_line|#define TX_PA_CFG_IGNORE_SNAP_OUI          BIT(2)
DECL|macro|TX_PA_CFG_IGNORE_LLC_CTRL
mdefine_line|#define TX_PA_CFG_IGNORE_LLC_CTRL          BIT(3)
DECL|macro|TX_PA_CFG_IGNORE_L2_ERR
mdefine_line|#define&t;TX_PA_CFG_IGNORE_L2_ERR&t;&t;&t;   BIT(6)
multiline_comment|/* Recent add, used only debug purposes. */
DECL|member|pcc_enable
id|u64
id|pcc_enable
suffix:semicolon
DECL|member|unused9
id|u8
id|unused9
(braket
l_int|0x700
op_minus
l_int|0x178
)braket
suffix:semicolon
DECL|member|txdma_debug_ctrl
id|u64
id|txdma_debug_ctrl
suffix:semicolon
DECL|member|unused10
id|u8
id|unused10
(braket
l_int|0x1800
op_minus
l_int|0x1708
)braket
suffix:semicolon
multiline_comment|/* RxDMA Registers */
DECL|member|rxdma_int_status
id|u64
id|rxdma_int_status
suffix:semicolon
DECL|member|rxdma_int_mask
id|u64
id|rxdma_int_mask
suffix:semicolon
DECL|macro|RXDMA_INT_RC_INT_M
mdefine_line|#define RXDMA_INT_RC_INT_M             BIT(0)
DECL|macro|RXDMA_INT_RPA_INT_M
mdefine_line|#define RXDMA_INT_RPA_INT_M            BIT(1)
DECL|macro|RXDMA_INT_RDA_INT_M
mdefine_line|#define RXDMA_INT_RDA_INT_M            BIT(2)
DECL|macro|RXDMA_INT_RTI_INT_M
mdefine_line|#define RXDMA_INT_RTI_INT_M            BIT(3)
DECL|member|rda_err_reg
id|u64
id|rda_err_reg
suffix:semicolon
DECL|member|rda_err_mask
id|u64
id|rda_err_mask
suffix:semicolon
DECL|member|rda_err_alarm
id|u64
id|rda_err_alarm
suffix:semicolon
DECL|member|rc_err_reg
id|u64
id|rc_err_reg
suffix:semicolon
DECL|member|rc_err_mask
id|u64
id|rc_err_mask
suffix:semicolon
DECL|member|rc_err_alarm
id|u64
id|rc_err_alarm
suffix:semicolon
DECL|member|prc_pcix_err_reg
id|u64
id|prc_pcix_err_reg
suffix:semicolon
DECL|member|prc_pcix_err_mask
id|u64
id|prc_pcix_err_mask
suffix:semicolon
DECL|member|prc_pcix_err_alarm
id|u64
id|prc_pcix_err_alarm
suffix:semicolon
DECL|member|rpa_err_reg
id|u64
id|rpa_err_reg
suffix:semicolon
DECL|member|rpa_err_mask
id|u64
id|rpa_err_mask
suffix:semicolon
DECL|member|rpa_err_alarm
id|u64
id|rpa_err_alarm
suffix:semicolon
DECL|member|rti_err_reg
id|u64
id|rti_err_reg
suffix:semicolon
DECL|member|rti_err_mask
id|u64
id|rti_err_mask
suffix:semicolon
DECL|member|rti_err_alarm
id|u64
id|rti_err_alarm
suffix:semicolon
DECL|member|unused11
id|u8
id|unused11
(braket
l_int|0x100
op_minus
l_int|0x88
)braket
suffix:semicolon
multiline_comment|/* DMA arbiter */
DECL|member|rx_queue_priority
id|u64
id|rx_queue_priority
suffix:semicolon
DECL|macro|RX_QUEUE_0_PRIORITY
mdefine_line|#define RX_QUEUE_0_PRIORITY(val)       vBIT(val,5,3)
DECL|macro|RX_QUEUE_1_PRIORITY
mdefine_line|#define RX_QUEUE_1_PRIORITY(val)       vBIT(val,13,3)
DECL|macro|RX_QUEUE_2_PRIORITY
mdefine_line|#define RX_QUEUE_2_PRIORITY(val)       vBIT(val,21,3)
DECL|macro|RX_QUEUE_3_PRIORITY
mdefine_line|#define RX_QUEUE_3_PRIORITY(val)       vBIT(val,29,3)
DECL|macro|RX_QUEUE_4_PRIORITY
mdefine_line|#define RX_QUEUE_4_PRIORITY(val)       vBIT(val,37,3)
DECL|macro|RX_QUEUE_5_PRIORITY
mdefine_line|#define RX_QUEUE_5_PRIORITY(val)       vBIT(val,45,3)
DECL|macro|RX_QUEUE_6_PRIORITY
mdefine_line|#define RX_QUEUE_6_PRIORITY(val)       vBIT(val,53,3)
DECL|macro|RX_QUEUE_7_PRIORITY
mdefine_line|#define RX_QUEUE_7_PRIORITY(val)       vBIT(val,61,3)
DECL|macro|RX_QUEUE_PRI_0
mdefine_line|#define RX_QUEUE_PRI_0                 0&t;/* highest */
DECL|macro|RX_QUEUE_PRI_1
mdefine_line|#define RX_QUEUE_PRI_1                 1
DECL|macro|RX_QUEUE_PRI_2
mdefine_line|#define RX_QUEUE_PRI_2                 2
DECL|macro|RX_QUEUE_PRI_3
mdefine_line|#define RX_QUEUE_PRI_3                 3
DECL|macro|RX_QUEUE_PRI_4
mdefine_line|#define RX_QUEUE_PRI_4                 4
DECL|macro|RX_QUEUE_PRI_5
mdefine_line|#define RX_QUEUE_PRI_5                 5
DECL|macro|RX_QUEUE_PRI_6
mdefine_line|#define RX_QUEUE_PRI_6                 6
DECL|macro|RX_QUEUE_PRI_7
mdefine_line|#define RX_QUEUE_PRI_7                 7&t;/* lowest */
DECL|member|rx_w_round_robin_0
id|u64
id|rx_w_round_robin_0
suffix:semicolon
DECL|member|rx_w_round_robin_1
id|u64
id|rx_w_round_robin_1
suffix:semicolon
DECL|member|rx_w_round_robin_2
id|u64
id|rx_w_round_robin_2
suffix:semicolon
DECL|member|rx_w_round_robin_3
id|u64
id|rx_w_round_robin_3
suffix:semicolon
DECL|member|rx_w_round_robin_4
id|u64
id|rx_w_round_robin_4
suffix:semicolon
multiline_comment|/* Per-ring controller regs */
DECL|macro|RX_MAX_RINGS
mdefine_line|#define RX_MAX_RINGS                8
macro_line|#if 0
mdefine_line|#define RX_MAX_RINGS_SZ             0xFFFF&t;/* 65536 */
mdefine_line|#define RX_MIN_RINGS_SZ             0x3F&t;/* 63 */
macro_line|#endif
DECL|member|prc_rxd0_n
id|u64
id|prc_rxd0_n
(braket
id|RX_MAX_RINGS
)braket
suffix:semicolon
DECL|member|prc_ctrl_n
id|u64
id|prc_ctrl_n
(braket
id|RX_MAX_RINGS
)braket
suffix:semicolon
DECL|macro|PRC_CTRL_RC_ENABLED
mdefine_line|#define PRC_CTRL_RC_ENABLED                    BIT(7)
DECL|macro|PRC_CTRL_RING_MODE
mdefine_line|#define PRC_CTRL_RING_MODE                     (BIT(14)|BIT(15))
DECL|macro|PRC_CTRL_RING_MODE_1
mdefine_line|#define PRC_CTRL_RING_MODE_1                   vBIT(0,14,2)
DECL|macro|PRC_CTRL_RING_MODE_3
mdefine_line|#define PRC_CTRL_RING_MODE_3                   vBIT(1,14,2)
DECL|macro|PRC_CTRL_RING_MODE_5
mdefine_line|#define PRC_CTRL_RING_MODE_5                   vBIT(2,14,2)
DECL|macro|PRC_CTRL_RING_MODE_x
mdefine_line|#define PRC_CTRL_RING_MODE_x                   vBIT(3,14,2)
DECL|macro|PRC_CTRL_NO_SNOOP
mdefine_line|#define PRC_CTRL_NO_SNOOP                      (BIT(22)|BIT(23))
DECL|macro|PRC_CTRL_NO_SNOOP_DESC
mdefine_line|#define PRC_CTRL_NO_SNOOP_DESC                 BIT(22)
DECL|macro|PRC_CTRL_NO_SNOOP_BUFF
mdefine_line|#define PRC_CTRL_NO_SNOOP_BUFF                 BIT(23)
DECL|macro|PRC_CTRL_RXD_BACKOFF_INTERVAL
mdefine_line|#define PRC_CTRL_RXD_BACKOFF_INTERVAL(val)     vBIT(val,40,24)
DECL|member|prc_alarm_action
id|u64
id|prc_alarm_action
suffix:semicolon
DECL|macro|PRC_ALARM_ACTION_RR_R0_STOP
mdefine_line|#define PRC_ALARM_ACTION_RR_R0_STOP            BIT(3)
DECL|macro|PRC_ALARM_ACTION_RW_R0_STOP
mdefine_line|#define PRC_ALARM_ACTION_RW_R0_STOP            BIT(7)
DECL|macro|PRC_ALARM_ACTION_RR_R1_STOP
mdefine_line|#define PRC_ALARM_ACTION_RR_R1_STOP            BIT(11)
DECL|macro|PRC_ALARM_ACTION_RW_R1_STOP
mdefine_line|#define PRC_ALARM_ACTION_RW_R1_STOP            BIT(15)
DECL|macro|PRC_ALARM_ACTION_RR_R2_STOP
mdefine_line|#define PRC_ALARM_ACTION_RR_R2_STOP            BIT(19)
DECL|macro|PRC_ALARM_ACTION_RW_R2_STOP
mdefine_line|#define PRC_ALARM_ACTION_RW_R2_STOP            BIT(23)
DECL|macro|PRC_ALARM_ACTION_RR_R3_STOP
mdefine_line|#define PRC_ALARM_ACTION_RR_R3_STOP            BIT(27)
DECL|macro|PRC_ALARM_ACTION_RW_R3_STOP
mdefine_line|#define PRC_ALARM_ACTION_RW_R3_STOP            BIT(31)
DECL|macro|PRC_ALARM_ACTION_RR_R4_STOP
mdefine_line|#define PRC_ALARM_ACTION_RR_R4_STOP            BIT(35)
DECL|macro|PRC_ALARM_ACTION_RW_R4_STOP
mdefine_line|#define PRC_ALARM_ACTION_RW_R4_STOP            BIT(39)
DECL|macro|PRC_ALARM_ACTION_RR_R5_STOP
mdefine_line|#define PRC_ALARM_ACTION_RR_R5_STOP            BIT(43)
DECL|macro|PRC_ALARM_ACTION_RW_R5_STOP
mdefine_line|#define PRC_ALARM_ACTION_RW_R5_STOP            BIT(47)
DECL|macro|PRC_ALARM_ACTION_RR_R6_STOP
mdefine_line|#define PRC_ALARM_ACTION_RR_R6_STOP            BIT(51)
DECL|macro|PRC_ALARM_ACTION_RW_R6_STOP
mdefine_line|#define PRC_ALARM_ACTION_RW_R6_STOP            BIT(55)
DECL|macro|PRC_ALARM_ACTION_RR_R7_STOP
mdefine_line|#define PRC_ALARM_ACTION_RR_R7_STOP            BIT(59)
DECL|macro|PRC_ALARM_ACTION_RW_R7_STOP
mdefine_line|#define PRC_ALARM_ACTION_RW_R7_STOP            BIT(63)
multiline_comment|/* Receive traffic interrupts */
DECL|member|rti_command_mem
id|u64
id|rti_command_mem
suffix:semicolon
DECL|macro|RTI_CMD_MEM_WE
mdefine_line|#define RTI_CMD_MEM_WE                          BIT(7)
DECL|macro|RTI_CMD_MEM_STROBE
mdefine_line|#define RTI_CMD_MEM_STROBE                      BIT(15)
DECL|macro|RTI_CMD_MEM_STROBE_NEW_CMD
mdefine_line|#define RTI_CMD_MEM_STROBE_NEW_CMD              BIT(15)
DECL|macro|RTI_CMD_MEM_STROBE_CMD_BEING_EXECUTED
mdefine_line|#define RTI_CMD_MEM_STROBE_CMD_BEING_EXECUTED   BIT(15)
DECL|macro|RTI_CMD_MEM_OFFSET
mdefine_line|#define RTI_CMD_MEM_OFFSET(n)                   vBIT(n,29,3)
DECL|member|rti_data1_mem
id|u64
id|rti_data1_mem
suffix:semicolon
DECL|macro|RTI_DATA1_MEM_RX_TIMER_VAL
mdefine_line|#define RTI_DATA1_MEM_RX_TIMER_VAL(n)      vBIT(n,3,29)
DECL|macro|RTI_DATA1_MEM_RX_TIMER_AC_EN
mdefine_line|#define RTI_DATA1_MEM_RX_TIMER_AC_EN       BIT(38)
DECL|macro|RTI_DATA1_MEM_RX_TIMER_CI_EN
mdefine_line|#define RTI_DATA1_MEM_RX_TIMER_CI_EN       BIT(39)
DECL|macro|RTI_DATA1_MEM_RX_URNG_A
mdefine_line|#define RTI_DATA1_MEM_RX_URNG_A(n)         vBIT(n,41,7)
DECL|macro|RTI_DATA1_MEM_RX_URNG_B
mdefine_line|#define RTI_DATA1_MEM_RX_URNG_B(n)         vBIT(n,49,7)
DECL|macro|RTI_DATA1_MEM_RX_URNG_C
mdefine_line|#define RTI_DATA1_MEM_RX_URNG_C(n)         vBIT(n,57,7)
DECL|member|rti_data2_mem
id|u64
id|rti_data2_mem
suffix:semicolon
DECL|macro|RTI_DATA2_MEM_RX_UFC_A
mdefine_line|#define RTI_DATA2_MEM_RX_UFC_A(n)          vBIT(n,0,16)
DECL|macro|RTI_DATA2_MEM_RX_UFC_B
mdefine_line|#define RTI_DATA2_MEM_RX_UFC_B(n)          vBIT(n,16,16)
DECL|macro|RTI_DATA2_MEM_RX_UFC_C
mdefine_line|#define RTI_DATA2_MEM_RX_UFC_C(n)          vBIT(n,32,16)
DECL|macro|RTI_DATA2_MEM_RX_UFC_D
mdefine_line|#define RTI_DATA2_MEM_RX_UFC_D(n)          vBIT(n,48,16)
DECL|member|rx_pa_cfg
id|u64
id|rx_pa_cfg
suffix:semicolon
DECL|macro|RX_PA_CFG_IGNORE_FRM_ERR
mdefine_line|#define RX_PA_CFG_IGNORE_FRM_ERR           BIT(1)
DECL|macro|RX_PA_CFG_IGNORE_SNAP_OUI
mdefine_line|#define RX_PA_CFG_IGNORE_SNAP_OUI          BIT(2)
DECL|macro|RX_PA_CFG_IGNORE_LLC_CTRL
mdefine_line|#define RX_PA_CFG_IGNORE_LLC_CTRL          BIT(3)
DECL|macro|RX_PA_CFG_IGNORE_L2_ERR
mdefine_line|#define RX_PA_CFG_IGNORE_L2_ERR            BIT(6)
DECL|member|unused12
id|u8
id|unused12
(braket
l_int|0x700
op_minus
l_int|0x1D8
)braket
suffix:semicolon
DECL|member|rxdma_debug_ctrl
id|u64
id|rxdma_debug_ctrl
suffix:semicolon
DECL|member|unused13
id|u8
id|unused13
(braket
l_int|0x2000
op_minus
l_int|0x1f08
)braket
suffix:semicolon
multiline_comment|/* Media Access Controller Register */
DECL|member|mac_int_status
id|u64
id|mac_int_status
suffix:semicolon
DECL|member|mac_int_mask
id|u64
id|mac_int_mask
suffix:semicolon
DECL|macro|MAC_INT_STATUS_TMAC_INT
mdefine_line|#define MAC_INT_STATUS_TMAC_INT            BIT(0)
DECL|macro|MAC_INT_STATUS_RMAC_INT
mdefine_line|#define MAC_INT_STATUS_RMAC_INT            BIT(1)
DECL|member|mac_tmac_err_reg
id|u64
id|mac_tmac_err_reg
suffix:semicolon
DECL|macro|TMAC_ERR_REG_TMAC_ECC_DB_ERR
mdefine_line|#define TMAC_ERR_REG_TMAC_ECC_DB_ERR       BIT(15)
DECL|macro|TMAC_ERR_REG_TMAC_TX_BUF_OVRN
mdefine_line|#define TMAC_ERR_REG_TMAC_TX_BUF_OVRN      BIT(23)
DECL|macro|TMAC_ERR_REG_TMAC_TX_CRI_ERR
mdefine_line|#define TMAC_ERR_REG_TMAC_TX_CRI_ERR       BIT(31)
DECL|member|mac_tmac_err_mask
id|u64
id|mac_tmac_err_mask
suffix:semicolon
DECL|member|mac_tmac_err_alarm
id|u64
id|mac_tmac_err_alarm
suffix:semicolon
DECL|member|mac_rmac_err_reg
id|u64
id|mac_rmac_err_reg
suffix:semicolon
DECL|macro|RMAC_ERR_REG_RX_BUFF_OVRN
mdefine_line|#define RMAC_ERR_REG_RX_BUFF_OVRN          BIT(0)
DECL|macro|RMAC_ERR_REG_RTS_ECC_DB_ERR
mdefine_line|#define RMAC_ERR_REG_RTS_ECC_DB_ERR        BIT(14)
DECL|macro|RMAC_ERR_REG_ECC_DB_ERR
mdefine_line|#define RMAC_ERR_REG_ECC_DB_ERR            BIT(15)
DECL|macro|RMAC_LINK_STATE_CHANGE_INT
mdefine_line|#define RMAC_LINK_STATE_CHANGE_INT         BIT(31)
DECL|member|mac_rmac_err_mask
id|u64
id|mac_rmac_err_mask
suffix:semicolon
DECL|member|mac_rmac_err_alarm
id|u64
id|mac_rmac_err_alarm
suffix:semicolon
DECL|member|unused14
id|u8
id|unused14
(braket
l_int|0x100
op_minus
l_int|0x40
)braket
suffix:semicolon
DECL|member|mac_cfg
id|u64
id|mac_cfg
suffix:semicolon
DECL|macro|MAC_CFG_TMAC_ENABLE
mdefine_line|#define MAC_CFG_TMAC_ENABLE             BIT(0)
DECL|macro|MAC_CFG_RMAC_ENABLE
mdefine_line|#define MAC_CFG_RMAC_ENABLE             BIT(1)
DECL|macro|MAC_CFG_LAN_NOT_WAN
mdefine_line|#define MAC_CFG_LAN_NOT_WAN             BIT(2)
DECL|macro|MAC_CFG_TMAC_LOOPBACK
mdefine_line|#define MAC_CFG_TMAC_LOOPBACK           BIT(3)
DECL|macro|MAC_CFG_TMAC_APPEND_PAD
mdefine_line|#define MAC_CFG_TMAC_APPEND_PAD         BIT(4)
DECL|macro|MAC_CFG_RMAC_STRIP_FCS
mdefine_line|#define MAC_CFG_RMAC_STRIP_FCS          BIT(5)
DECL|macro|MAC_CFG_RMAC_STRIP_PAD
mdefine_line|#define MAC_CFG_RMAC_STRIP_PAD          BIT(6)
DECL|macro|MAC_CFG_RMAC_PROM_ENABLE
mdefine_line|#define MAC_CFG_RMAC_PROM_ENABLE        BIT(7)
DECL|macro|MAC_RMAC_DISCARD_PFRM
mdefine_line|#define MAC_RMAC_DISCARD_PFRM           BIT(8)
DECL|macro|MAC_RMAC_BCAST_ENABLE
mdefine_line|#define MAC_RMAC_BCAST_ENABLE           BIT(9)
DECL|macro|MAC_RMAC_ALL_ADDR_ENABLE
mdefine_line|#define MAC_RMAC_ALL_ADDR_ENABLE        BIT(10)
DECL|macro|MAC_RMAC_INVLD_IPG_THR
mdefine_line|#define MAC_RMAC_INVLD_IPG_THR(val)     vBIT(val,16,8)
DECL|member|tmac_avg_ipg
id|u64
id|tmac_avg_ipg
suffix:semicolon
DECL|macro|TMAC_AVG_IPG
mdefine_line|#define TMAC_AVG_IPG(val)           vBIT(val,0,8)
DECL|member|rmac_max_pyld_len
id|u64
id|rmac_max_pyld_len
suffix:semicolon
DECL|macro|RMAC_MAX_PYLD_LEN
mdefine_line|#define RMAC_MAX_PYLD_LEN(val)      vBIT(val,2,14)
DECL|macro|RMAC_MAX_PYLD_LEN_DEF
mdefine_line|#define RMAC_MAX_PYLD_LEN_DEF       vBIT(1500,2,14)
DECL|macro|RMAC_MAX_PYLD_LEN_JUMBO_DEF
mdefine_line|#define RMAC_MAX_PYLD_LEN_JUMBO_DEF vBIT(9600,2,14)
DECL|member|rmac_err_cfg
id|u64
id|rmac_err_cfg
suffix:semicolon
DECL|macro|RMAC_ERR_FCS
mdefine_line|#define RMAC_ERR_FCS                    BIT(0)
DECL|macro|RMAC_ERR_FCS_ACCEPT
mdefine_line|#define RMAC_ERR_FCS_ACCEPT             BIT(1)
DECL|macro|RMAC_ERR_TOO_LONG
mdefine_line|#define RMAC_ERR_TOO_LONG               BIT(1)
DECL|macro|RMAC_ERR_TOO_LONG_ACCEPT
mdefine_line|#define RMAC_ERR_TOO_LONG_ACCEPT        BIT(1)
DECL|macro|RMAC_ERR_RUNT
mdefine_line|#define RMAC_ERR_RUNT                   BIT(2)
DECL|macro|RMAC_ERR_RUNT_ACCEPT
mdefine_line|#define RMAC_ERR_RUNT_ACCEPT            BIT(2)
DECL|macro|RMAC_ERR_LEN_MISMATCH
mdefine_line|#define RMAC_ERR_LEN_MISMATCH           BIT(3)
DECL|macro|RMAC_ERR_LEN_MISMATCH_ACCEPT
mdefine_line|#define RMAC_ERR_LEN_MISMATCH_ACCEPT    BIT(3)
DECL|member|rmac_cfg_key
id|u64
id|rmac_cfg_key
suffix:semicolon
DECL|macro|RMAC_CFG_KEY
mdefine_line|#define RMAC_CFG_KEY(val)               vBIT(val,0,16)
DECL|macro|MAX_MAC_ADDRESSES
mdefine_line|#define MAX_MAC_ADDRESSES           16
DECL|macro|MAX_MC_ADDRESSES
mdefine_line|#define MAX_MC_ADDRESSES            32&t;/* Multicast addresses */
DECL|macro|MAC_MAC_ADDR_START_OFFSET
mdefine_line|#define MAC_MAC_ADDR_START_OFFSET   0
DECL|macro|MAC_MC_ADDR_START_OFFSET
mdefine_line|#define MAC_MC_ADDR_START_OFFSET    16
DECL|macro|MAC_MC_ALL_MC_ADDR_OFFSET
mdefine_line|#define MAC_MC_ALL_MC_ADDR_OFFSET   63&t;/* enables all multicast pkts */
DECL|member|rmac_addr_cmd_mem
id|u64
id|rmac_addr_cmd_mem
suffix:semicolon
DECL|macro|RMAC_ADDR_CMD_MEM_WE
mdefine_line|#define RMAC_ADDR_CMD_MEM_WE                    BIT(7)
DECL|macro|RMAC_ADDR_CMD_MEM_RD
mdefine_line|#define RMAC_ADDR_CMD_MEM_RD                    0
DECL|macro|RMAC_ADDR_CMD_MEM_STROBE_NEW_CMD
mdefine_line|#define RMAC_ADDR_CMD_MEM_STROBE_NEW_CMD        BIT(15)
DECL|macro|RMAC_ADDR_CMD_MEM_STROBE_CMD_EXECUTING
mdefine_line|#define RMAC_ADDR_CMD_MEM_STROBE_CMD_EXECUTING  BIT(15)
DECL|macro|RMAC_ADDR_CMD_MEM_OFFSET
mdefine_line|#define RMAC_ADDR_CMD_MEM_OFFSET(n)             vBIT(n,26,6)
DECL|member|rmac_addr_data0_mem
id|u64
id|rmac_addr_data0_mem
suffix:semicolon
DECL|macro|RMAC_ADDR_DATA0_MEM_ADDR
mdefine_line|#define RMAC_ADDR_DATA0_MEM_ADDR(n)    vBIT(n,0,48)
DECL|macro|RMAC_ADDR_DATA0_MEM_USER
mdefine_line|#define RMAC_ADDR_DATA0_MEM_USER       BIT(48)
DECL|member|rmac_addr_data1_mem
id|u64
id|rmac_addr_data1_mem
suffix:semicolon
DECL|macro|RMAC_ADDR_DATA1_MEM_MASK
mdefine_line|#define RMAC_ADDR_DATA1_MEM_MASK(n)    vBIT(n,0,48)
DECL|member|unused15
id|u8
id|unused15
(braket
l_int|0x8
)braket
suffix:semicolon
multiline_comment|/*&n;        u64 rmac_addr_cfg;&n;#define RMAC_ADDR_UCASTn_EN(n)     mBIT(0)_n(n)&n;#define RMAC_ADDR_MCASTn_EN(n)     mBIT(0)_n(n)&n;#define RMAC_ADDR_BCAST_EN         vBIT(0)_48 &n;#define RMAC_ADDR_ALL_ADDR_EN      vBIT(0)_49 &n;*/
DECL|member|tmac_ipg_cfg
id|u64
id|tmac_ipg_cfg
suffix:semicolon
DECL|member|rmac_pause_cfg
id|u64
id|rmac_pause_cfg
suffix:semicolon
DECL|macro|RMAC_PAUSE_GEN
mdefine_line|#define RMAC_PAUSE_GEN             BIT(0)
DECL|macro|RMAC_PAUSE_GEN_ENABLE
mdefine_line|#define RMAC_PAUSE_GEN_ENABLE      BIT(0)
DECL|macro|RMAC_PAUSE_RX
mdefine_line|#define RMAC_PAUSE_RX              BIT(1)
DECL|macro|RMAC_PAUSE_RX_ENABLE
mdefine_line|#define RMAC_PAUSE_RX_ENABLE       BIT(1)
DECL|macro|RMAC_PAUSE_HG_PTIME_DEF
mdefine_line|#define RMAC_PAUSE_HG_PTIME_DEF    vBIT(0xFFFF,16,16)
DECL|macro|RMAC_PAUSE_HG_PTIME
mdefine_line|#define RMAC_PAUSE_HG_PTIME(val)    vBIT(val,16,16)
DECL|member|rmac_red_cfg
id|u64
id|rmac_red_cfg
suffix:semicolon
DECL|member|rmac_red_rate_q0q3
id|u64
id|rmac_red_rate_q0q3
suffix:semicolon
DECL|member|rmac_red_rate_q4q7
id|u64
id|rmac_red_rate_q4q7
suffix:semicolon
DECL|member|mac_link_util
id|u64
id|mac_link_util
suffix:semicolon
DECL|macro|MAC_TX_LINK_UTIL
mdefine_line|#define MAC_TX_LINK_UTIL           vBIT(0xFE,1,7)
DECL|macro|MAC_TX_LINK_UTIL_DISABLE
mdefine_line|#define MAC_TX_LINK_UTIL_DISABLE   vBIT(0xF, 8,4)
DECL|macro|MAC_TX_LINK_UTIL_VAL
mdefine_line|#define MAC_TX_LINK_UTIL_VAL( n )  vBIT(n,8,4)
DECL|macro|MAC_RX_LINK_UTIL
mdefine_line|#define MAC_RX_LINK_UTIL           vBIT(0xFE,33,7)
DECL|macro|MAC_RX_LINK_UTIL_DISABLE
mdefine_line|#define MAC_RX_LINK_UTIL_DISABLE   vBIT(0xF,40,4)
DECL|macro|MAC_RX_LINK_UTIL_VAL
mdefine_line|#define MAC_RX_LINK_UTIL_VAL( n )  vBIT(n,40,4)
DECL|macro|MAC_LINK_UTIL_DISABLE
mdefine_line|#define MAC_LINK_UTIL_DISABLE      MAC_TX_LINK_UTIL_DISABLE | &bslash;&n;                                   MAC_RX_LINK_UTIL_DISABLE
DECL|member|rmac_invalid_ipg
id|u64
id|rmac_invalid_ipg
suffix:semicolon
multiline_comment|/* rx traffic steering */
DECL|macro|MAC_RTS_FRM_LEN_SET
mdefine_line|#define&t;MAC_RTS_FRM_LEN_SET(len)&t;vBIT(len,2,14)
DECL|member|rts_frm_len_n
id|u64
id|rts_frm_len_n
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|rts_qos_steering
id|u64
id|rts_qos_steering
suffix:semicolon
DECL|macro|MAX_DIX_MAP
mdefine_line|#define MAX_DIX_MAP                         4
DECL|member|rts_dix_map_n
id|u64
id|rts_dix_map_n
(braket
id|MAX_DIX_MAP
)braket
suffix:semicolon
DECL|macro|RTS_DIX_MAP_ETYPE
mdefine_line|#define RTS_DIX_MAP_ETYPE(val)             vBIT(val,0,16)
DECL|macro|RTS_DIX_MAP_SCW
mdefine_line|#define RTS_DIX_MAP_SCW(val)               BIT(val,21)
DECL|member|rts_q_alternates
id|u64
id|rts_q_alternates
suffix:semicolon
DECL|member|rts_default_q
id|u64
id|rts_default_q
suffix:semicolon
DECL|member|rts_ctrl
id|u64
id|rts_ctrl
suffix:semicolon
DECL|macro|RTS_CTRL_IGNORE_SNAP_OUI
mdefine_line|#define RTS_CTRL_IGNORE_SNAP_OUI           BIT(2)
DECL|macro|RTS_CTRL_IGNORE_LLC_CTRL
mdefine_line|#define RTS_CTRL_IGNORE_LLC_CTRL           BIT(3)
DECL|member|rts_pn_cam_ctrl
id|u64
id|rts_pn_cam_ctrl
suffix:semicolon
DECL|macro|RTS_PN_CAM_CTRL_WE
mdefine_line|#define RTS_PN_CAM_CTRL_WE                 BIT(7)
DECL|macro|RTS_PN_CAM_CTRL_STROBE_NEW_CMD
mdefine_line|#define RTS_PN_CAM_CTRL_STROBE_NEW_CMD     BIT(15)
DECL|macro|RTS_PN_CAM_CTRL_STROBE_BEING_EXECUTED
mdefine_line|#define RTS_PN_CAM_CTRL_STROBE_BEING_EXECUTED   BIT(15)
DECL|macro|RTS_PN_CAM_CTRL_OFFSET
mdefine_line|#define RTS_PN_CAM_CTRL_OFFSET(n)          vBIT(n,24,8)
DECL|member|rts_pn_cam_data
id|u64
id|rts_pn_cam_data
suffix:semicolon
DECL|macro|RTS_PN_CAM_DATA_TCP_SELECT
mdefine_line|#define RTS_PN_CAM_DATA_TCP_SELECT         BIT(7)
DECL|macro|RTS_PN_CAM_DATA_PORT
mdefine_line|#define RTS_PN_CAM_DATA_PORT(val)          vBIT(val,8,16)
DECL|macro|RTS_PN_CAM_DATA_SCW
mdefine_line|#define RTS_PN_CAM_DATA_SCW(val)           vBIT(val,24,8)
DECL|member|rts_ds_mem_ctrl
id|u64
id|rts_ds_mem_ctrl
suffix:semicolon
DECL|macro|RTS_DS_MEM_CTRL_WE
mdefine_line|#define RTS_DS_MEM_CTRL_WE                 BIT(7)
DECL|macro|RTS_DS_MEM_CTRL_STROBE_NEW_CMD
mdefine_line|#define RTS_DS_MEM_CTRL_STROBE_NEW_CMD     BIT(15)
DECL|macro|RTS_DS_MEM_CTRL_STROBE_CMD_BEING_EXECUTED
mdefine_line|#define RTS_DS_MEM_CTRL_STROBE_CMD_BEING_EXECUTED   BIT(15)
DECL|macro|RTS_DS_MEM_CTRL_OFFSET
mdefine_line|#define RTS_DS_MEM_CTRL_OFFSET(n)          vBIT(n,26,6)
DECL|member|rts_ds_mem_data
id|u64
id|rts_ds_mem_data
suffix:semicolon
DECL|macro|RTS_DS_MEM_DATA
mdefine_line|#define RTS_DS_MEM_DATA(n)                 vBIT(n,0,8)
DECL|member|unused16
id|u8
id|unused16
(braket
l_int|0x700
op_minus
l_int|0x220
)braket
suffix:semicolon
DECL|member|mac_debug_ctrl
id|u64
id|mac_debug_ctrl
suffix:semicolon
DECL|macro|MAC_DBG_ACTIVITY_VALUE
mdefine_line|#define MAC_DBG_ACTIVITY_VALUE&t;&t;   0x411040400000000ULL
DECL|member|unused17
id|u8
id|unused17
(braket
l_int|0x2800
op_minus
l_int|0x2708
)braket
suffix:semicolon
multiline_comment|/* memory controller registers */
DECL|member|mc_int_status
id|u64
id|mc_int_status
suffix:semicolon
DECL|macro|MC_INT_STATUS_MC_INT
mdefine_line|#define MC_INT_STATUS_MC_INT               BIT(0)
DECL|member|mc_int_mask
id|u64
id|mc_int_mask
suffix:semicolon
DECL|macro|MC_INT_MASK_MC_INT
mdefine_line|#define MC_INT_MASK_MC_INT                 BIT(0)
DECL|member|mc_err_reg
id|u64
id|mc_err_reg
suffix:semicolon
DECL|macro|MC_ERR_REG_ECC_DB_ERR_L
mdefine_line|#define MC_ERR_REG_ECC_DB_ERR_L            BIT(14)
DECL|macro|MC_ERR_REG_ECC_DB_ERR_U
mdefine_line|#define MC_ERR_REG_ECC_DB_ERR_U            BIT(15)
DECL|macro|MC_ERR_REG_MIRI_CRI_ERR_0
mdefine_line|#define MC_ERR_REG_MIRI_CRI_ERR_0          BIT(22)
DECL|macro|MC_ERR_REG_MIRI_CRI_ERR_1
mdefine_line|#define MC_ERR_REG_MIRI_CRI_ERR_1          BIT(23)
DECL|macro|MC_ERR_REG_SM_ERR
mdefine_line|#define MC_ERR_REG_SM_ERR                  BIT(31)
DECL|member|mc_err_mask
id|u64
id|mc_err_mask
suffix:semicolon
DECL|member|mc_err_alarm
id|u64
id|mc_err_alarm
suffix:semicolon
DECL|member|unused18
id|u8
id|unused18
(braket
l_int|0x100
op_minus
l_int|0x28
)braket
suffix:semicolon
multiline_comment|/* MC configuration */
DECL|member|rx_queue_cfg
id|u64
id|rx_queue_cfg
suffix:semicolon
DECL|macro|RX_QUEUE_CFG_Q0_SZ
mdefine_line|#define RX_QUEUE_CFG_Q0_SZ(n)              vBIT(n,0,8)
DECL|macro|RX_QUEUE_CFG_Q1_SZ
mdefine_line|#define RX_QUEUE_CFG_Q1_SZ(n)              vBIT(n,8,8)
DECL|macro|RX_QUEUE_CFG_Q2_SZ
mdefine_line|#define RX_QUEUE_CFG_Q2_SZ(n)              vBIT(n,16,8)
DECL|macro|RX_QUEUE_CFG_Q3_SZ
mdefine_line|#define RX_QUEUE_CFG_Q3_SZ(n)              vBIT(n,24,8)
DECL|macro|RX_QUEUE_CFG_Q4_SZ
mdefine_line|#define RX_QUEUE_CFG_Q4_SZ(n)              vBIT(n,32,8)
DECL|macro|RX_QUEUE_CFG_Q5_SZ
mdefine_line|#define RX_QUEUE_CFG_Q5_SZ(n)              vBIT(n,40,8)
DECL|macro|RX_QUEUE_CFG_Q6_SZ
mdefine_line|#define RX_QUEUE_CFG_Q6_SZ(n)              vBIT(n,48,8)
DECL|macro|RX_QUEUE_CFG_Q7_SZ
mdefine_line|#define RX_QUEUE_CFG_Q7_SZ(n)              vBIT(n,56,8)
DECL|member|mc_rldram_mrs
id|u64
id|mc_rldram_mrs
suffix:semicolon
DECL|macro|MC_RLDRAM_QUEUE_SIZE_ENABLE
mdefine_line|#define&t;MC_RLDRAM_QUEUE_SIZE_ENABLE&t;&t;&t;BIT(39)
DECL|macro|MC_RLDRAM_MRS_ENABLE
mdefine_line|#define&t;MC_RLDRAM_MRS_ENABLE&t;&t;&t;&t;BIT(47)
DECL|member|mc_rldram_interleave
id|u64
id|mc_rldram_interleave
suffix:semicolon
DECL|member|mc_pause_thresh_q0q3
id|u64
id|mc_pause_thresh_q0q3
suffix:semicolon
DECL|member|mc_pause_thresh_q4q7
id|u64
id|mc_pause_thresh_q4q7
suffix:semicolon
DECL|member|mc_red_thresh_q
id|u64
id|mc_red_thresh_q
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|unused19
id|u8
id|unused19
(braket
l_int|0x200
op_minus
l_int|0x168
)braket
suffix:semicolon
DECL|member|mc_rldram_ref_per
id|u64
id|mc_rldram_ref_per
suffix:semicolon
DECL|member|unused20
id|u8
id|unused20
(braket
l_int|0x220
op_minus
l_int|0x208
)braket
suffix:semicolon
DECL|member|mc_rldram_test_ctrl
id|u64
id|mc_rldram_test_ctrl
suffix:semicolon
DECL|macro|MC_RLDRAM_TEST_MODE
mdefine_line|#define MC_RLDRAM_TEST_MODE&t;&t;BIT(47)
DECL|macro|MC_RLDRAM_TEST_WRITE
mdefine_line|#define MC_RLDRAM_TEST_WRITE&t;BIT(7)
DECL|macro|MC_RLDRAM_TEST_GO
mdefine_line|#define MC_RLDRAM_TEST_GO&t;&t;BIT(15)
DECL|macro|MC_RLDRAM_TEST_DONE
mdefine_line|#define MC_RLDRAM_TEST_DONE&t;&t;BIT(23)
DECL|macro|MC_RLDRAM_TEST_PASS
mdefine_line|#define MC_RLDRAM_TEST_PASS&t;&t;BIT(31)
DECL|member|unused21
id|u8
id|unused21
(braket
l_int|0x240
op_minus
l_int|0x228
)braket
suffix:semicolon
DECL|member|mc_rldram_test_add
id|u64
id|mc_rldram_test_add
suffix:semicolon
DECL|member|unused22
id|u8
id|unused22
(braket
l_int|0x260
op_minus
l_int|0x248
)braket
suffix:semicolon
DECL|member|mc_rldram_test_d0
id|u64
id|mc_rldram_test_d0
suffix:semicolon
DECL|member|unused23
id|u8
id|unused23
(braket
l_int|0x280
op_minus
l_int|0x268
)braket
suffix:semicolon
DECL|member|mc_rldram_test_d1
id|u64
id|mc_rldram_test_d1
suffix:semicolon
DECL|member|unused24
id|u8
id|unused24
(braket
l_int|0x300
op_minus
l_int|0x288
)braket
suffix:semicolon
DECL|member|mc_rldram_test_d2
id|u64
id|mc_rldram_test_d2
suffix:semicolon
DECL|member|unused25
id|u8
id|unused25
(braket
l_int|0x700
op_minus
l_int|0x308
)braket
suffix:semicolon
DECL|member|mc_debug_ctrl
id|u64
id|mc_debug_ctrl
suffix:semicolon
DECL|member|unused26
id|u8
id|unused26
(braket
l_int|0x3000
op_minus
l_int|0x2f08
)braket
suffix:semicolon
multiline_comment|/* XGXG */
multiline_comment|/* XGXS control registers */
DECL|member|xgxs_int_status
id|u64
id|xgxs_int_status
suffix:semicolon
DECL|macro|XGXS_INT_STATUS_TXGXS
mdefine_line|#define XGXS_INT_STATUS_TXGXS              BIT(0)
DECL|macro|XGXS_INT_STATUS_RXGXS
mdefine_line|#define XGXS_INT_STATUS_RXGXS              BIT(1)
DECL|member|xgxs_int_mask
id|u64
id|xgxs_int_mask
suffix:semicolon
DECL|macro|XGXS_INT_MASK_TXGXS
mdefine_line|#define XGXS_INT_MASK_TXGXS                BIT(0)
DECL|macro|XGXS_INT_MASK_RXGXS
mdefine_line|#define XGXS_INT_MASK_RXGXS                BIT(1)
DECL|member|xgxs_txgxs_err_reg
id|u64
id|xgxs_txgxs_err_reg
suffix:semicolon
DECL|macro|TXGXS_ECC_DB_ERR
mdefine_line|#define TXGXS_ECC_DB_ERR                   BIT(15)
DECL|member|xgxs_txgxs_err_mask
id|u64
id|xgxs_txgxs_err_mask
suffix:semicolon
DECL|member|xgxs_txgxs_err_alarm
id|u64
id|xgxs_txgxs_err_alarm
suffix:semicolon
DECL|member|xgxs_rxgxs_err_reg
id|u64
id|xgxs_rxgxs_err_reg
suffix:semicolon
DECL|member|xgxs_rxgxs_err_mask
id|u64
id|xgxs_rxgxs_err_mask
suffix:semicolon
DECL|member|xgxs_rxgxs_err_alarm
id|u64
id|xgxs_rxgxs_err_alarm
suffix:semicolon
DECL|member|unused27
id|u8
id|unused27
(braket
l_int|0x100
op_minus
l_int|0x40
)braket
suffix:semicolon
DECL|member|xgxs_cfg
id|u64
id|xgxs_cfg
suffix:semicolon
DECL|member|xgxs_status
id|u64
id|xgxs_status
suffix:semicolon
DECL|member|xgxs_cfg_key
id|u64
id|xgxs_cfg_key
suffix:semicolon
DECL|member|xgxs_efifo_cfg
id|u64
id|xgxs_efifo_cfg
suffix:semicolon
multiline_comment|/* CHANGED */
DECL|member|rxgxs_ber_0
id|u64
id|rxgxs_ber_0
suffix:semicolon
multiline_comment|/* CHANGED */
DECL|member|rxgxs_ber_1
id|u64
id|rxgxs_ber_1
suffix:semicolon
multiline_comment|/* CHANGED */
DECL|typedef|XENA_dev_config_t
)brace
id|XENA_dev_config_t
suffix:semicolon
DECL|macro|XENA_REG_SPACE
mdefine_line|#define XENA_REG_SPACE&t;sizeof(XENA_dev_config_t)
DECL|macro|XENA_EEPROM_SPACE
mdefine_line|#define&t;XENA_EEPROM_SPACE (0x01 &lt;&lt; 11)
macro_line|#endif&t;&t;&t;&t;/* _REGS_H */
eof
