multiline_comment|/*&n; * arch/ppc/platforms/katana.h&n; *&n; * Definitions for Artesyn Katana750i/3750 board.&n; *&n; * Author: Tim Montgomery &lt;timm@artesyncp.com&gt;&n; * Maintained by: Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * Based on code done by Rabeeh Khoury - rabeeh@galileo.co.il&n; * Based on code done by Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; */
multiline_comment|/*&n; * The MV64360 has 2 PCI buses each with 1 window from the CPU bus to&n; * PCI I/O space and 4 windows from the CPU bus to PCI MEM space.&n; * We&squot;ll only use one PCI MEM window on each PCI bus.&n; *&n; * This is the CPU physical memory map (windows must be at least 64 KB and start&n; * on a boundary that is a multiple of the window size):&n; *&n; *    0xff800000-0xffffffff      - Boot window&n; *    0xf8400000-0xf85fffff      - Internal SRAM&n; *    0xf8200000-0xf83fffff      - CPLD&n; *    0xf8100000-0xf810ffff      - MV64360 Registers (CONFIG_MV64X60_NEW_BASE)&n; *    0xf8000000-0xf80fffff      - Socketed FLASH&n; *    0xe0000000-0xefffffff      - Soldered FLASH&n; *    0xc0000000-0xc3ffffff      - PCI I/O (second hose)&n; *    0x80000000-0xbfffffff      - PCI MEM (second hose)&n; */
macro_line|#ifndef __PPC_PLATFORMS_KATANA_H
DECL|macro|__PPC_PLATFORMS_KATANA_H
mdefine_line|#define __PPC_PLATFORMS_KATANA_H
multiline_comment|/* CPU Physical Memory Map setup. */
DECL|macro|KATANA_BOOT_WINDOW_BASE
mdefine_line|#define KATANA_BOOT_WINDOW_BASE&t;&t;&t;0xff800000
DECL|macro|KATANA_BOOT_WINDOW_SIZE
mdefine_line|#define KATANA_BOOT_WINDOW_SIZE&t;&t;&t;0x00800000 /* 8 MB */
DECL|macro|KATANA_INTERNAL_SRAM_BASE
mdefine_line|#define KATANA_INTERNAL_SRAM_BASE&t;&t;0xf8400000
DECL|macro|KATANA_CPLD_BASE
mdefine_line|#define KATANA_CPLD_BASE&t;&t;&t;0xf8200000
DECL|macro|KATANA_CPLD_SIZE
mdefine_line|#define KATANA_CPLD_SIZE&t;&t;&t;0x00200000 /* 2 MB */
DECL|macro|KATANA_SOCKET_BASE
mdefine_line|#define KATANA_SOCKET_BASE&t;&t;&t;0xf8000000
DECL|macro|KATANA_SOCKETED_FLASH_SIZE
mdefine_line|#define KATANA_SOCKETED_FLASH_SIZE&t;&t;0x00100000 /* 1 MB */
DECL|macro|KATANA_SOLDERED_FLASH_BASE
mdefine_line|#define KATANA_SOLDERED_FLASH_BASE&t;&t;0xe0000000
DECL|macro|KATANA_SOLDERED_FLASH_SIZE
mdefine_line|#define KATANA_SOLDERED_FLASH_SIZE&t;&t;0x10000000 /* 256 MB */
DECL|macro|KATANA_PCI1_MEM_START_PROC_ADDR
mdefine_line|#define KATANA_PCI1_MEM_START_PROC_ADDR         0x80000000
DECL|macro|KATANA_PCI1_MEM_START_PCI_HI_ADDR
mdefine_line|#define KATANA_PCI1_MEM_START_PCI_HI_ADDR       0x00000000
DECL|macro|KATANA_PCI1_MEM_START_PCI_LO_ADDR
mdefine_line|#define KATANA_PCI1_MEM_START_PCI_LO_ADDR       0x80000000
DECL|macro|KATANA_PCI1_MEM_SIZE
mdefine_line|#define KATANA_PCI1_MEM_SIZE                    0x40000000 /* 1 GB */
DECL|macro|KATANA_PCI1_IO_START_PROC_ADDR
mdefine_line|#define KATANA_PCI1_IO_START_PROC_ADDR          0xc0000000
DECL|macro|KATANA_PCI1_IO_START_PCI_ADDR
mdefine_line|#define KATANA_PCI1_IO_START_PCI_ADDR           0x00000000
DECL|macro|KATANA_PCI1_IO_SIZE
mdefine_line|#define KATANA_PCI1_IO_SIZE                     0x04000000 /* 64 MB */
multiline_comment|/* Board-specific IRQ info */
DECL|macro|KATANA_PCI_INTA_IRQ_3750
mdefine_line|#define  KATANA_PCI_INTA_IRQ_3750&t;&t;64+8
DECL|macro|KATANA_PCI_INTB_IRQ_3750
mdefine_line|#define  KATANA_PCI_INTB_IRQ_3750&t;&t;64+9
DECL|macro|KATANA_PCI_INTC_IRQ_3750
mdefine_line|#define  KATANA_PCI_INTC_IRQ_3750&t;&t;64+10
DECL|macro|KATANA_PCI_INTA_IRQ_750i
mdefine_line|#define  KATANA_PCI_INTA_IRQ_750i&t;&t;64+8
DECL|macro|KATANA_PCI_INTB_IRQ_750i
mdefine_line|#define  KATANA_PCI_INTB_IRQ_750i&t;&t;64+9
DECL|macro|KATANA_PCI_INTC_IRQ_750i
mdefine_line|#define  KATANA_PCI_INTC_IRQ_750i&t;&t;64+10
DECL|macro|KATANA_PCI_INTD_IRQ_750i
mdefine_line|#define  KATANA_PCI_INTD_IRQ_750i&t;&t;64+14
DECL|macro|KATANA_CPLD_RST_EVENT
mdefine_line|#define KATANA_CPLD_RST_EVENT&t;&t;&t;0x00000000
DECL|macro|KATANA_CPLD_RST_CMD
mdefine_line|#define KATANA_CPLD_RST_CMD&t;&t;&t;0x00001000
DECL|macro|KATANA_CPLD_PCI_ERR_INT_EN
mdefine_line|#define KATANA_CPLD_PCI_ERR_INT_EN&t;&t;0x00002000
DECL|macro|KATANA_CPLD_PCI_ERR_INT_PEND
mdefine_line|#define KATANA_CPLD_PCI_ERR_INT_PEND&t;&t;0x00003000
DECL|macro|KATANA_CPLD_PRODUCT_ID
mdefine_line|#define KATANA_CPLD_PRODUCT_ID&t;&t;&t;0x00004000
DECL|macro|KATANA_CPLD_EREADY
mdefine_line|#define KATANA_CPLD_EREADY&t;&t;&t;0x00005000
DECL|macro|KATANA_CPLD_HARDWARE_VER
mdefine_line|#define KATANA_CPLD_HARDWARE_VER&t;&t;0x00007000
DECL|macro|KATANA_CPLD_PLD_VER
mdefine_line|#define KATANA_CPLD_PLD_VER&t;&t;&t;0x00008000
DECL|macro|KATANA_CPLD_BD_CFG_0
mdefine_line|#define KATANA_CPLD_BD_CFG_0&t;&t;&t;0x00009000
DECL|macro|KATANA_CPLD_BD_CFG_1
mdefine_line|#define KATANA_CPLD_BD_CFG_1&t;&t;&t;0x0000a000
DECL|macro|KATANA_CPLD_BD_CFG_3
mdefine_line|#define KATANA_CPLD_BD_CFG_3&t;&t;&t;0x0000c000
DECL|macro|KATANA_CPLD_LED
mdefine_line|#define KATANA_CPLD_LED&t;&t;&t;&t;0x0000d000
DECL|macro|KATANA_CPLD_RESET_OUT
mdefine_line|#define KATANA_CPLD_RESET_OUT&t;&t;&t;0x0000e000
DECL|macro|KATANA_CPLD_RST_EVENT_INITACT
mdefine_line|#define KATANA_CPLD_RST_EVENT_INITACT&t;&t;0x80
DECL|macro|KATANA_CPLD_RST_EVENT_SW
mdefine_line|#define KATANA_CPLD_RST_EVENT_SW&t;&t;0x40
DECL|macro|KATANA_CPLD_RST_EVENT_WD
mdefine_line|#define KATANA_CPLD_RST_EVENT_WD&t;&t;0x20
DECL|macro|KATANA_CPLD_RST_EVENT_COPS
mdefine_line|#define KATANA_CPLD_RST_EVENT_COPS&t;&t;0x10
DECL|macro|KATANA_CPLD_RST_EVENT_COPH
mdefine_line|#define KATANA_CPLD_RST_EVENT_COPH&t;&t;0x08
DECL|macro|KATANA_CPLD_RST_EVENT_CPCI
mdefine_line|#define KATANA_CPLD_RST_EVENT_CPCI&t;&t;0x02
DECL|macro|KATANA_CPLD_RST_EVENT_FP
mdefine_line|#define KATANA_CPLD_RST_EVENT_FP&t;&t;0x01
DECL|macro|KATANA_CPLD_RST_CMD_SCL
mdefine_line|#define KATANA_CPLD_RST_CMD_SCL&t;&t;&t;0x80
DECL|macro|KATANA_CPLD_RST_CMD_SDA
mdefine_line|#define KATANA_CPLD_RST_CMD_SDA&t;&t;&t;0x40
DECL|macro|KATANA_CPLD_RST_CMD_I2C
mdefine_line|#define KATANA_CPLD_RST_CMD_I2C&t;&t;&t;0x10
DECL|macro|KATANA_CPLD_RST_CMD_FR
mdefine_line|#define KATANA_CPLD_RST_CMD_FR&t;&t;&t;0x08
DECL|macro|KATANA_CPLD_RST_CMD_SR
mdefine_line|#define KATANA_CPLD_RST_CMD_SR&t;&t;&t;0x04
DECL|macro|KATANA_CPLD_RST_CMD_HR
mdefine_line|#define KATANA_CPLD_RST_CMD_HR&t;&t;&t;0x01
DECL|macro|KATANA_CPLD_BD_CFG_0_SYSCLK_MASK
mdefine_line|#define KATANA_CPLD_BD_CFG_0_SYSCLK_MASK&t;0xc0
DECL|macro|KATANA_CPLD_BD_CFG_0_SYSCLK_200
mdefine_line|#define KATANA_CPLD_BD_CFG_0_SYSCLK_200&t;&t;0x00
DECL|macro|KATANA_CPLD_BD_CFG_0_SYSCLK_166
mdefine_line|#define KATANA_CPLD_BD_CFG_0_SYSCLK_166&t;&t;0x80
DECL|macro|KATANA_CPLD_BD_CFG_0_SYSCLK_133
mdefine_line|#define KATANA_CPLD_BD_CFG_0_SYSCLK_133&t;&t;0xc0
DECL|macro|KATANA_CPLD_BD_CFG_0_SYSCLK_100
mdefine_line|#define KATANA_CPLD_BD_CFG_0_SYSCLK_100&t;&t;0x40
DECL|macro|KATANA_CPLD_BD_CFG_1_FL_BANK_MASK
mdefine_line|#define KATANA_CPLD_BD_CFG_1_FL_BANK_MASK&t;0x03
DECL|macro|KATANA_CPLD_BD_CFG_1_FL_BANK_16MB
mdefine_line|#define KATANA_CPLD_BD_CFG_1_FL_BANK_16MB&t;0x00
DECL|macro|KATANA_CPLD_BD_CFG_1_FL_BANK_32MB
mdefine_line|#define KATANA_CPLD_BD_CFG_1_FL_BANK_32MB&t;0x01
DECL|macro|KATANA_CPLD_BD_CFG_1_FL_BANK_64MB
mdefine_line|#define KATANA_CPLD_BD_CFG_1_FL_BANK_64MB&t;0x02
DECL|macro|KATANA_CPLD_BD_CFG_1_FL_BANK_128MB
mdefine_line|#define KATANA_CPLD_BD_CFG_1_FL_BANK_128MB&t;0x03
DECL|macro|KATANA_CPLD_BD_CFG_1_FL_NUM_BANKS_MASK
mdefine_line|#define KATANA_CPLD_BD_CFG_1_FL_NUM_BANKS_MASK&t;0x04
DECL|macro|KATANA_CPLD_BD_CFG_1_FL_NUM_BANKS_ONE
mdefine_line|#define KATANA_CPLD_BD_CFG_1_FL_NUM_BANKS_ONE&t;0x00
DECL|macro|KATANA_CPLD_BD_CFG_1_FL_NUM_BANKS_TWO
mdefine_line|#define KATANA_CPLD_BD_CFG_1_FL_NUM_BANKS_TWO&t;0x04
DECL|macro|KATANA_CPLD_BD_CFG_3_MONARCH
mdefine_line|#define KATANA_CPLD_BD_CFG_3_MONARCH&t;&t;0x04
DECL|macro|KATANA_CPLD_RESET_OUT_PORTSEL
mdefine_line|#define KATANA_CPLD_RESET_OUT_PORTSEL&t;&t;0x80
DECL|macro|KATANA_CPLD_RESET_OUT_WD
mdefine_line|#define KATANA_CPLD_RESET_OUT_WD&t;&t;0x20
DECL|macro|KATANA_CPLD_RESET_OUT_COPH
mdefine_line|#define KATANA_CPLD_RESET_OUT_COPH&t;&t;0x08
DECL|macro|KATANA_CPLD_RESET_OUT_PCI_RST_PCI
mdefine_line|#define KATANA_CPLD_RESET_OUT_PCI_RST_PCI&t;0x02
DECL|macro|KATANA_CPLD_RESET_OUT_PCI_RST_FP
mdefine_line|#define KATANA_CPLD_RESET_OUT_PCI_RST_FP&t;0x01
DECL|macro|KATANA_MBOX_RESET_REQUEST
mdefine_line|#define KATANA_MBOX_RESET_REQUEST&t;&t;0xC83A
DECL|macro|KATANA_MBOX_RESET_ACK
mdefine_line|#define KATANA_MBOX_RESET_ACK&t;&t;&t;0xE430
DECL|macro|KATANA_MBOX_RESET_DONE
mdefine_line|#define KATANA_MBOX_RESET_DONE&t;&t;&t;0x32E5
DECL|macro|HSL_PLD_BASE
mdefine_line|#define HSL_PLD_BASE&t;&t;&t;&t;0x00010000
DECL|macro|HSL_PLD_J4SGA_REG_OFF
mdefine_line|#define HSL_PLD_J4SGA_REG_OFF&t;&t;&t;0
DECL|macro|HSL_PLD_J4GA_REG_OFF
mdefine_line|#define HSL_PLD_J4GA_REG_OFF&t;&t;&t;1
DECL|macro|HSL_PLD_J2GA_REG_OFF
mdefine_line|#define HSL_PLD_J2GA_REG_OFF&t;&t;&t;2
DECL|macro|HSL_PLD_HOT_SWAP_OFF
mdefine_line|#define HSL_PLD_HOT_SWAP_OFF&t;&t;&t;6
DECL|macro|HSL_PLD_HOT_SWAP_LED_BIT
mdefine_line|#define HSL_PLD_HOT_SWAP_LED_BIT&t;&t;0x1
DECL|macro|GA_MASK
mdefine_line|#define GA_MASK&t;&t;&t;&t;&t;0x1f
DECL|macro|HSL_PLD_SIZE
mdefine_line|#define HSL_PLD_SIZE&t;&t;&t;&t;0x1000
DECL|macro|K3750_GPP_GEO_ADDR_PINS
mdefine_line|#define K3750_GPP_GEO_ADDR_PINS&t;&t;&t;0xf8000000
DECL|macro|K3750_GPP_GEO_ADDR_SHIFT
mdefine_line|#define K3750_GPP_GEO_ADDR_SHIFT&t;&t;27
DECL|macro|K3750_GPP_EVENT_PROC_0
mdefine_line|#define K3750_GPP_EVENT_PROC_0&t;&t;&t;(1 &lt;&lt; 21)
DECL|macro|K3750_GPP_EVENT_PROC_1_2
mdefine_line|#define K3750_GPP_EVENT_PROC_1_2&t;&t;(1 &lt;&lt; 2)
DECL|macro|PCI_VENDOR_ID_ARTESYN
mdefine_line|#define PCI_VENDOR_ID_ARTESYN&t;&t;&t;0x1223
DECL|macro|PCI_DEVICE_ID_KATANA_3750_PROC0
mdefine_line|#define PCI_DEVICE_ID_KATANA_3750_PROC0&t;&t;0x0041
DECL|macro|PCI_DEVICE_ID_KATANA_3750_PROC1
mdefine_line|#define PCI_DEVICE_ID_KATANA_3750_PROC1&t;&t;0x0042
DECL|macro|PCI_DEVICE_ID_KATANA_3750_PROC2
mdefine_line|#define PCI_DEVICE_ID_KATANA_3750_PROC2&t;&t;0x0043
DECL|macro|COPROC_MEM_FUNCTION
mdefine_line|#define COPROC_MEM_FUNCTION&t;&t;&t;0
DECL|macro|COPROC_MEM_BAR
mdefine_line|#define COPROC_MEM_BAR&t;&t;&t;&t;0
DECL|macro|COPROC_REGS_FUNCTION
mdefine_line|#define COPROC_REGS_FUNCTION&t;&t;&t;0
DECL|macro|COPROC_REGS_BAR
mdefine_line|#define COPROC_REGS_BAR&t;&t;&t;&t;4
DECL|macro|COPROC_FLASH_FUNCTION
mdefine_line|#define COPROC_FLASH_FUNCTION&t;&t;&t;2
DECL|macro|COPROC_FLASH_BAR
mdefine_line|#define COPROC_FLASH_BAR&t;&t;&t;4
DECL|macro|KATANA_IPMB_LOCAL_I2C_ADDR
mdefine_line|#define KATANA_IPMB_LOCAL_I2C_ADDR&t;&t;0x08
DECL|macro|KATANA_DEFAULT_BAUD
mdefine_line|#define&t;KATANA_DEFAULT_BAUD&t;&t;&t;9600
DECL|macro|KATANA_MPSC_CLK_SRC
mdefine_line|#define&t;KATANA_MPSC_CLK_SRC&t;&t;&t;8&t;  /* TCLK */
DECL|macro|KATANA_MTD_MONITOR_SIZE
mdefine_line|#define&t;KATANA_MTD_MONITOR_SIZE&t;&t;&t;(1 &lt;&lt; 20) /* 1 MB */
DECL|macro|KATANA_ETH0_PHY_ADDR
mdefine_line|#define&t;KATANA_ETH0_PHY_ADDR&t;&t;&t;12
DECL|macro|KATANA_ETH1_PHY_ADDR
mdefine_line|#define&t;KATANA_ETH1_PHY_ADDR&t;&t;&t;11
DECL|macro|KATANA_ETH2_PHY_ADDR
mdefine_line|#define&t;KATANA_ETH2_PHY_ADDR&t;&t;&t;4
DECL|macro|KATANA_PRODUCT_ID_3750
mdefine_line|#define KATANA_PRODUCT_ID_3750&t;&t;&t;0x01
DECL|macro|KATANA_PRODUCT_ID_750i
mdefine_line|#define KATANA_PRODUCT_ID_750i&t;&t;&t;0x02
DECL|macro|KATANA_PRODUCT_ID_752i
mdefine_line|#define KATANA_PRODUCT_ID_752i&t;&t;&t;0x04
DECL|macro|KATANA_ETH_TX_QUEUE_SIZE
mdefine_line|#define KATANA_ETH_TX_QUEUE_SIZE&t;&t;800
DECL|macro|KATANA_ETH_RX_QUEUE_SIZE
mdefine_line|#define KATANA_ETH_RX_QUEUE_SIZE&t;&t;400
DECL|macro|KATANA_ETH_PORT_CONFIG_VALUE
mdefine_line|#define&t;KATANA_ETH_PORT_CONFIG_VALUE&t;&t;&t;&bslash;&n;&t;ETH_UNICAST_NORMAL_MODE&t;&t;&t;|&t;&bslash;&n;&t;ETH_DEFAULT_RX_QUEUE_0&t;&t;&t;|&t;&bslash;&n;&t;ETH_DEFAULT_RX_ARP_QUEUE_0&t;&t;|&t;&bslash;&n;&t;ETH_RECEIVE_BC_IF_NOT_IP_OR_ARP&t;&t;|&t;&bslash;&n;&t;ETH_RECEIVE_BC_IF_IP&t;&t;&t;|&t;&bslash;&n;&t;ETH_RECEIVE_BC_IF_ARP&t;&t;&t;|&t;&bslash;&n;&t;ETH_CAPTURE_TCP_FRAMES_DIS&t;&t;|&t;&bslash;&n;&t;ETH_CAPTURE_UDP_FRAMES_DIS&t;&t;|&t;&bslash;&n;&t;ETH_DEFAULT_RX_TCP_QUEUE_0&t;&t;|&t;&bslash;&n;&t;ETH_DEFAULT_RX_UDP_QUEUE_0&t;&t;|&t;&bslash;&n;&t;ETH_DEFAULT_RX_BPDU_QUEUE_0
DECL|macro|KATANA_ETH_PORT_CONFIG_EXTEND_VALUE
mdefine_line|#define&t;KATANA_ETH_PORT_CONFIG_EXTEND_VALUE&t;&t;&bslash;&n;&t;ETH_SPAN_BPDU_PACKETS_AS_NORMAL&t;&t;|&t;&bslash;&n;&t;ETH_PARTITION_DISABLE
DECL|macro|GT_ETH_IPG_INT_RX
mdefine_line|#define&t;GT_ETH_IPG_INT_RX(value)&t;&t;&t;&bslash;&n;&t;((value &amp; 0x3fff) &lt;&lt; 8)
DECL|macro|KATANA_ETH_PORT_SDMA_CONFIG_VALUE
mdefine_line|#define&t;KATANA_ETH_PORT_SDMA_CONFIG_VALUE&t;&t;&bslash;&n;&t;ETH_RX_BURST_SIZE_4_64BIT&t;&t;|&t;&bslash;&n;&t;GT_ETH_IPG_INT_RX(0)&t;&t;&t;|&t;&bslash;&n;&t;ETH_TX_BURST_SIZE_4_64BIT
DECL|macro|KATANA_ETH_PORT_SERIAL_CONTROL_VALUE
mdefine_line|#define&t;KATANA_ETH_PORT_SERIAL_CONTROL_VALUE&t;&t;&bslash;&n;&t;ETH_FORCE_LINK_PASS&t;&t;&t;|&t;&bslash;&n;&t;ETH_ENABLE_AUTO_NEG_FOR_DUPLX&t;&t;|&t;&bslash;&n;&t;ETH_DISABLE_AUTO_NEG_FOR_FLOW_CTRL&t;|&t;&bslash;&n;&t;ETH_ADV_SYMMETRIC_FLOW_CTRL&t;&t;|&t;&bslash;&n;&t;ETH_FORCE_FC_MODE_NO_PAUSE_DIS_TX&t;|&t;&bslash;&n;&t;ETH_FORCE_BP_MODE_NO_JAM&t;&t;|&t;&bslash;&n;&t;BIT9&t;&t;&t;&t;&t;|&t;&bslash;&n;&t;ETH_DO_NOT_FORCE_LINK_FAIL&t;&t;|&t;&bslash;&n;&t;ETH_RETRANSMIT_16_ATTEMPTS&t;&t;|&t;&bslash;&n;&t;ETH_ENABLE_AUTO_NEG_SPEED_GMII&t;&t;|&t;&bslash;&n;&t;ETH_DTE_ADV_0&t;&t;&t;&t;|&t;&bslash;&n;&t;ETH_DISABLE_AUTO_NEG_BYPASS&t;&t;|&t;&bslash;&n;&t;ETH_AUTO_NEG_NO_CHANGE&t;&t;&t;|&t;&bslash;&n;&t;ETH_MAX_RX_PACKET_9700BYTE&t;&t;|&t;&bslash;&n;&t;ETH_CLR_EXT_LOOPBACK&t;&t;&t;|&t;&bslash;&n;&t;ETH_SET_FULL_DUPLEX_MODE&t;&t;|&t;&bslash;&n;&t;ETH_ENABLE_FLOW_CTRL_TX_RX_IN_FULL_DUPLEX
macro_line|#ifndef __ASSEMBLY__
r_typedef
r_enum
(brace
DECL|enumerator|KATANA_ID_3750
id|KATANA_ID_3750
comma
DECL|enumerator|KATANA_ID_750I
id|KATANA_ID_750I
comma
DECL|enumerator|KATANA_ID_752I
id|KATANA_ID_752I
comma
DECL|enumerator|KATANA_ID_MAX
id|KATANA_ID_MAX
DECL|typedef|katana_id_t
)brace
id|katana_id_t
suffix:semicolon
macro_line|#endif
r_static
r_inline
id|u32
DECL|function|katana_bus_freq
id|katana_bus_freq
c_func
(paren
r_void
id|__iomem
op_star
id|cpld_base
)paren
(brace
id|u8
id|bd_cfg_0
suffix:semicolon
id|bd_cfg_0
op_assign
id|in_8
c_func
(paren
id|cpld_base
op_plus
id|KATANA_CPLD_BD_CFG_0
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|bd_cfg_0
op_amp
id|KATANA_CPLD_BD_CFG_0_SYSCLK_MASK
)paren
(brace
r_case
id|KATANA_CPLD_BD_CFG_0_SYSCLK_200
suffix:colon
r_return
l_int|200000000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KATANA_CPLD_BD_CFG_0_SYSCLK_166
suffix:colon
r_return
l_int|166666666
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KATANA_CPLD_BD_CFG_0_SYSCLK_133
suffix:colon
r_return
l_int|133333333
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KATANA_CPLD_BD_CFG_0_SYSCLK_100
suffix:colon
r_return
l_int|100000000
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|133333333
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
macro_line|#endif&t;/* __PPC_PLATFORMS_KATANA_H */
eof
