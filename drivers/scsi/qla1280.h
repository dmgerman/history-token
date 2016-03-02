multiline_comment|/******************************************************************************&n;*                  QLOGIC LINUX SOFTWARE&n;*&n;* QLogic ISP1280 (Ultra2) /12160 (Ultra3) SCSI driver&n;* Copyright (C) 2000 Qlogic Corporation&n;* (www.qlogic.com)&n;*&n;* This program is free software; you can redistribute it and/or modify it&n;* under the terms of the GNU General Public License as published by the&n;* Free Software Foundation; either version 2, or (at your option) any&n;* later version.&n;*&n;* This program is distributed in the hope that it will be useful, but&n;* WITHOUT ANY WARRANTY; without even the implied warranty of&n;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;* General Public License for more details.&n;*&n;******************************************************************************/
macro_line|#ifndef&t;_QLA1280_H
DECL|macro|_QLA1280_H
mdefine_line|#define&t;_QLA1280_H
multiline_comment|/*&n; * Data bit definitions.&n; */
DECL|macro|BIT_0
mdefine_line|#define BIT_0&t;0x1
DECL|macro|BIT_1
mdefine_line|#define BIT_1&t;0x2
DECL|macro|BIT_2
mdefine_line|#define BIT_2&t;0x4
DECL|macro|BIT_3
mdefine_line|#define BIT_3&t;0x8
DECL|macro|BIT_4
mdefine_line|#define BIT_4&t;0x10
DECL|macro|BIT_5
mdefine_line|#define BIT_5&t;0x20
DECL|macro|BIT_6
mdefine_line|#define BIT_6&t;0x40
DECL|macro|BIT_7
mdefine_line|#define BIT_7&t;0x80
DECL|macro|BIT_8
mdefine_line|#define BIT_8&t;0x100
DECL|macro|BIT_9
mdefine_line|#define BIT_9&t;0x200
DECL|macro|BIT_10
mdefine_line|#define BIT_10&t;0x400
DECL|macro|BIT_11
mdefine_line|#define BIT_11&t;0x800
DECL|macro|BIT_12
mdefine_line|#define BIT_12&t;0x1000
DECL|macro|BIT_13
mdefine_line|#define BIT_13&t;0x2000
DECL|macro|BIT_14
mdefine_line|#define BIT_14&t;0x4000
DECL|macro|BIT_15
mdefine_line|#define BIT_15&t;0x8000
DECL|macro|BIT_16
mdefine_line|#define BIT_16&t;0x10000
DECL|macro|BIT_17
mdefine_line|#define BIT_17&t;0x20000
DECL|macro|BIT_18
mdefine_line|#define BIT_18&t;0x40000
DECL|macro|BIT_19
mdefine_line|#define BIT_19&t;0x80000
DECL|macro|BIT_20
mdefine_line|#define BIT_20&t;0x100000
DECL|macro|BIT_21
mdefine_line|#define BIT_21&t;0x200000
DECL|macro|BIT_22
mdefine_line|#define BIT_22&t;0x400000
DECL|macro|BIT_23
mdefine_line|#define BIT_23&t;0x800000
DECL|macro|BIT_24
mdefine_line|#define BIT_24&t;0x1000000
DECL|macro|BIT_25
mdefine_line|#define BIT_25&t;0x2000000
DECL|macro|BIT_26
mdefine_line|#define BIT_26&t;0x4000000
DECL|macro|BIT_27
mdefine_line|#define BIT_27&t;0x8000000
DECL|macro|BIT_28
mdefine_line|#define BIT_28&t;0x10000000
DECL|macro|BIT_29
mdefine_line|#define BIT_29&t;0x20000000
DECL|macro|BIT_30
mdefine_line|#define BIT_30&t;0x40000000
DECL|macro|BIT_31
mdefine_line|#define BIT_31&t;0x80000000
macro_line|#if MEMORY_MAPPED_IO
DECL|macro|RD_REG_WORD
mdefine_line|#define RD_REG_WORD(addr)&t;&t;readw_relaxed(addr)
DECL|macro|RD_REG_WORD_dmasync
mdefine_line|#define RD_REG_WORD_dmasync(addr)&t;readw(addr)
DECL|macro|WRT_REG_WORD
mdefine_line|#define WRT_REG_WORD(addr, data)&t;writew(data, addr)
macro_line|#else&t;&t;&t;&t;/* MEMORY_MAPPED_IO */
DECL|macro|RD_REG_WORD
mdefine_line|#define RD_REG_WORD(addr)&t;&t;inw((unsigned long)addr)
DECL|macro|RD_REG_WORD_dmasync
mdefine_line|#define RD_REG_WORD_dmasync(addr)&t;RD_REG_WORD(addr)
DECL|macro|WRT_REG_WORD
mdefine_line|#define WRT_REG_WORD(addr, data)&t;outw(data, (unsigned long)addr)
macro_line|#endif&t;&t;&t;&t;/* MEMORY_MAPPED_IO */
multiline_comment|/*&n; * Host adapter default definitions.&n; */
DECL|macro|MAX_BUSES
mdefine_line|#define MAX_BUSES&t;2&t;/* 2 */
DECL|macro|MAX_B_BITS
mdefine_line|#define MAX_B_BITS&t;1
DECL|macro|MAX_TARGETS
mdefine_line|#define MAX_TARGETS&t;16&t;/* 16 */
DECL|macro|MAX_T_BITS
mdefine_line|#define MAX_T_BITS&t;4&t;/* 4 */
DECL|macro|MAX_LUNS
mdefine_line|#define MAX_LUNS&t;8&t;/* 32 */
DECL|macro|MAX_L_BITS
mdefine_line|#define MAX_L_BITS&t;3&t;/* 5 */
multiline_comment|/*&n; * Watchdog time quantum&n; */
DECL|macro|QLA1280_WDG_TIME_QUANTUM
mdefine_line|#define QLA1280_WDG_TIME_QUANTUM&t;5&t;/* In seconds */
multiline_comment|/* Command retry count (0-65535) */
DECL|macro|COMMAND_RETRY_COUNT
mdefine_line|#define COMMAND_RETRY_COUNT&t;&t;255
multiline_comment|/* Maximum outstanding commands in ISP queues */
DECL|macro|MAX_OUTSTANDING_COMMANDS
mdefine_line|#define MAX_OUTSTANDING_COMMANDS&t;512
DECL|macro|INVALID_HANDLE
mdefine_line|#define INVALID_HANDLE&t;&t;&t;(MAX_OUTSTANDING_COMMANDS + 2)
multiline_comment|/* ISP request and response entry counts (37-65535) */
DECL|macro|REQUEST_ENTRY_CNT
mdefine_line|#define REQUEST_ENTRY_CNT&t;&t;256 /* Number of request entries. */
DECL|macro|RESPONSE_ENTRY_CNT
mdefine_line|#define RESPONSE_ENTRY_CNT&t;&t;16  /* Number of response entries. */
multiline_comment|/* Number of segments 1 - 65535 */
DECL|macro|SG_SEGMENTS
mdefine_line|#define SG_SEGMENTS&t;&t;&t;32  /* Cmd entry + 6 continuations */
multiline_comment|/*&n; * SCSI Request Block structure  (sp)  that is placed&n; * on cmd-&gt;SCp location of every I/O&n; */
DECL|struct|srb
r_struct
id|srb
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* (8/16) LU queue */
DECL|member|cmd
r_struct
id|scsi_cmnd
op_star
id|cmd
suffix:semicolon
multiline_comment|/* (4/8) SCSI command block */
multiline_comment|/* NOTE: the sp-&gt;cmd will be NULL when this completion is&n;&t; * called, so you should know the scsi_cmnd when using this */
DECL|member|wait
r_struct
id|completion
op_star
id|wait
suffix:semicolon
DECL|member|saved_dma_handle
id|dma_addr_t
id|saved_dma_handle
suffix:semicolon
multiline_comment|/* for unmap of single transfers */
DECL|member|flags
r_uint8
id|flags
suffix:semicolon
multiline_comment|/* (1) Status flags. */
DECL|member|dir
r_uint8
id|dir
suffix:semicolon
multiline_comment|/* direction of transfer */
)brace
suffix:semicolon
multiline_comment|/*&n; * SRB flag definitions&n; */
DECL|macro|SRB_TIMEOUT
mdefine_line|#define SRB_TIMEOUT&t;&t;(1 &lt;&lt; 0)&t;/* Command timed out */
DECL|macro|SRB_SENT
mdefine_line|#define SRB_SENT&t;&t;(1 &lt;&lt; 1)&t;/* Command sent to ISP */
DECL|macro|SRB_ABORT_PENDING
mdefine_line|#define SRB_ABORT_PENDING&t;(1 &lt;&lt; 2)&t;/* Command abort sent to device */
DECL|macro|SRB_ABORTED
mdefine_line|#define SRB_ABORTED&t;&t;(1 &lt;&lt; 3)&t;/* Command aborted command already */
multiline_comment|/*&n; *  ISP I/O Register Set structure definitions.&n; */
DECL|struct|device_reg
r_struct
id|device_reg
(brace
DECL|member|id_l
r_uint16
id|id_l
suffix:semicolon
multiline_comment|/* ID low */
DECL|member|id_h
r_uint16
id|id_h
suffix:semicolon
multiline_comment|/* ID high */
DECL|member|cfg_0
r_uint16
id|cfg_0
suffix:semicolon
multiline_comment|/* Configuration 0 */
DECL|macro|ISP_CFG0_HWMSK
mdefine_line|#define ISP_CFG0_HWMSK   0x000f&t;/* Hardware revision mask */
DECL|macro|ISP_CFG0_1020
mdefine_line|#define ISP_CFG0_1020    BIT_0&t;/* ISP1020 */
DECL|macro|ISP_CFG0_1020A
mdefine_line|#define ISP_CFG0_1020A&t; BIT_1&t;/* ISP1020A */
DECL|macro|ISP_CFG0_1040
mdefine_line|#define ISP_CFG0_1040&t; BIT_2&t;/* ISP1040 */
DECL|macro|ISP_CFG0_1040A
mdefine_line|#define ISP_CFG0_1040A&t; BIT_3&t;/* ISP1040A */
DECL|macro|ISP_CFG0_1040B
mdefine_line|#define ISP_CFG0_1040B&t; BIT_4&t;/* ISP1040B */
DECL|macro|ISP_CFG0_1040C
mdefine_line|#define ISP_CFG0_1040C&t; BIT_5&t;/* ISP1040C */
DECL|member|cfg_1
r_uint16
id|cfg_1
suffix:semicolon
multiline_comment|/* Configuration 1 */
DECL|macro|ISP_CFG1_F128
mdefine_line|#define ISP_CFG1_F128    BIT_6  /* 128-byte FIFO threshold */
DECL|macro|ISP_CFG1_F64
mdefine_line|#define ISP_CFG1_F64     BIT_4|BIT_5 /* 128-byte FIFO threshold */
DECL|macro|ISP_CFG1_F32
mdefine_line|#define ISP_CFG1_F32     BIT_5  /* 128-byte FIFO threshold */
DECL|macro|ISP_CFG1_F16
mdefine_line|#define ISP_CFG1_F16     BIT_4  /* 128-byte FIFO threshold */
DECL|macro|ISP_CFG1_BENAB
mdefine_line|#define ISP_CFG1_BENAB   BIT_2  /* Global Bus burst enable */
DECL|macro|ISP_CFG1_SXP
mdefine_line|#define ISP_CFG1_SXP     BIT_0  /* SXP register select */
DECL|member|ictrl
r_uint16
id|ictrl
suffix:semicolon
multiline_comment|/* Interface control */
DECL|macro|ISP_RESET
mdefine_line|#define ISP_RESET        BIT_0&t;/* ISP soft reset */
DECL|macro|ISP_EN_INT
mdefine_line|#define ISP_EN_INT       BIT_1&t;/* ISP enable interrupts. */
DECL|macro|ISP_EN_RISC
mdefine_line|#define ISP_EN_RISC      BIT_2&t;/* ISP enable RISC interrupts. */
DECL|macro|ISP_FLASH_ENABLE
mdefine_line|#define ISP_FLASH_ENABLE BIT_8&t;/* Flash BIOS Read/Write enable */
DECL|macro|ISP_FLASH_UPPER
mdefine_line|#define ISP_FLASH_UPPER  BIT_9&t;/* Flash upper bank select */
DECL|member|istatus
r_uint16
id|istatus
suffix:semicolon
multiline_comment|/* Interface status */
DECL|macro|PCI_64BIT_SLOT
mdefine_line|#define PCI_64BIT_SLOT   BIT_14&t;/* PCI 64-bit slot indicator. */
DECL|macro|RISC_INT
mdefine_line|#define RISC_INT         BIT_2&t;/* RISC interrupt */
DECL|macro|PCI_INT
mdefine_line|#define PCI_INT          BIT_1&t;/* PCI interrupt */
DECL|member|semaphore
r_uint16
id|semaphore
suffix:semicolon
multiline_comment|/* Semaphore */
DECL|member|nvram
r_uint16
id|nvram
suffix:semicolon
multiline_comment|/* NVRAM register. */
DECL|macro|NV_DESELECT
mdefine_line|#define NV_DESELECT     0
DECL|macro|NV_CLOCK
mdefine_line|#define NV_CLOCK        BIT_0
DECL|macro|NV_SELECT
mdefine_line|#define NV_SELECT       BIT_1
DECL|macro|NV_DATA_OUT
mdefine_line|#define NV_DATA_OUT     BIT_2
DECL|macro|NV_DATA_IN
mdefine_line|#define NV_DATA_IN      BIT_3
DECL|member|flash_data
r_uint16
id|flash_data
suffix:semicolon
multiline_comment|/* Flash BIOS data */
DECL|member|flash_address
r_uint16
id|flash_address
suffix:semicolon
multiline_comment|/* Flash BIOS address */
DECL|member|unused_1
r_uint16
id|unused_1
(braket
l_int|0x06
)braket
suffix:semicolon
multiline_comment|/* cdma_* and ddma_* are 1040 only */
DECL|member|cdma_cfg
r_uint16
id|cdma_cfg
suffix:semicolon
DECL|macro|CDMA_CONF_SENAB
mdefine_line|#define CDMA_CONF_SENAB  BIT_3&t;/* SXP to DMA Data enable */
DECL|macro|CDMA_CONF_RIRQ
mdefine_line|#define CDMA_CONF_RIRQ   BIT_2&t;/* RISC interrupt enable */
DECL|macro|CDMA_CONF_BENAB
mdefine_line|#define CDMA_CONF_BENAB  BIT_1&t;/* Bus burst enable */
DECL|macro|CDMA_CONF_DIR
mdefine_line|#define CDMA_CONF_DIR    BIT_0&t;/* DMA direction (0=fifo-&gt;host 1=host-&gt;fifo) */
DECL|member|cdma_ctrl
r_uint16
id|cdma_ctrl
suffix:semicolon
DECL|member|cdma_status
r_uint16
id|cdma_status
suffix:semicolon
DECL|member|cdma_fifo_status
r_uint16
id|cdma_fifo_status
suffix:semicolon
DECL|member|cdma_count
r_uint16
id|cdma_count
suffix:semicolon
DECL|member|cdma_reserved
r_uint16
id|cdma_reserved
suffix:semicolon
DECL|member|cdma_address_count_0
r_uint16
id|cdma_address_count_0
suffix:semicolon
DECL|member|cdma_address_count_1
r_uint16
id|cdma_address_count_1
suffix:semicolon
DECL|member|cdma_address_count_2
r_uint16
id|cdma_address_count_2
suffix:semicolon
DECL|member|cdma_address_count_3
r_uint16
id|cdma_address_count_3
suffix:semicolon
DECL|member|unused_2
r_uint16
id|unused_2
(braket
l_int|0x06
)braket
suffix:semicolon
DECL|member|ddma_cfg
r_uint16
id|ddma_cfg
suffix:semicolon
DECL|macro|DDMA_CONF_SENAB
mdefine_line|#define DDMA_CONF_SENAB  BIT_3&t;/* SXP to DMA Data enable */
DECL|macro|DDMA_CONF_RIRQ
mdefine_line|#define DDMA_CONF_RIRQ   BIT_2&t;/* RISC interrupt enable */
DECL|macro|DDMA_CONF_BENAB
mdefine_line|#define DDMA_CONF_BENAB  BIT_1&t;/* Bus burst enable */
DECL|macro|DDMA_CONF_DIR
mdefine_line|#define DDMA_CONF_DIR    BIT_0&t;/* DMA direction (0=fifo-&gt;host 1=host-&gt;fifo) */
DECL|member|ddma_ctrl
r_uint16
id|ddma_ctrl
suffix:semicolon
DECL|member|ddma_status
r_uint16
id|ddma_status
suffix:semicolon
DECL|member|ddma_fifo_status
r_uint16
id|ddma_fifo_status
suffix:semicolon
DECL|member|ddma_xfer_count_low
r_uint16
id|ddma_xfer_count_low
suffix:semicolon
DECL|member|ddma_xfer_count_high
r_uint16
id|ddma_xfer_count_high
suffix:semicolon
DECL|member|ddma_addr_count_0
r_uint16
id|ddma_addr_count_0
suffix:semicolon
DECL|member|ddma_addr_count_1
r_uint16
id|ddma_addr_count_1
suffix:semicolon
DECL|member|ddma_addr_count_2
r_uint16
id|ddma_addr_count_2
suffix:semicolon
DECL|member|ddma_addr_count_3
r_uint16
id|ddma_addr_count_3
suffix:semicolon
DECL|member|unused_3
r_uint16
id|unused_3
(braket
l_int|0x0e
)braket
suffix:semicolon
DECL|member|mailbox0
r_uint16
id|mailbox0
suffix:semicolon
multiline_comment|/* Mailbox 0 */
DECL|member|mailbox1
r_uint16
id|mailbox1
suffix:semicolon
multiline_comment|/* Mailbox 1 */
DECL|member|mailbox2
r_uint16
id|mailbox2
suffix:semicolon
multiline_comment|/* Mailbox 2 */
DECL|member|mailbox3
r_uint16
id|mailbox3
suffix:semicolon
multiline_comment|/* Mailbox 3 */
DECL|member|mailbox4
r_uint16
id|mailbox4
suffix:semicolon
multiline_comment|/* Mailbox 4 */
DECL|member|mailbox5
r_uint16
id|mailbox5
suffix:semicolon
multiline_comment|/* Mailbox 5 */
DECL|member|mailbox6
r_uint16
id|mailbox6
suffix:semicolon
multiline_comment|/* Mailbox 6 */
DECL|member|mailbox7
r_uint16
id|mailbox7
suffix:semicolon
multiline_comment|/* Mailbox 7 */
DECL|member|unused_4
r_uint16
id|unused_4
(braket
l_int|0x20
)braket
suffix:semicolon
multiline_comment|/* 0x80-0xbf Gap */
DECL|member|host_cmd
r_uint16
id|host_cmd
suffix:semicolon
multiline_comment|/* Host command and control */
DECL|macro|HOST_INT
mdefine_line|#define HOST_INT      BIT_7&t;/* host interrupt bit */
DECL|macro|BIOS_ENABLE
mdefine_line|#define BIOS_ENABLE   BIT_0
DECL|member|unused_5
r_uint16
id|unused_5
(braket
l_int|0x5
)braket
suffix:semicolon
multiline_comment|/* 0xc2-0xcb Gap */
DECL|member|gpio_data
r_uint16
id|gpio_data
suffix:semicolon
DECL|member|gpio_enable
r_uint16
id|gpio_enable
suffix:semicolon
DECL|member|unused_6
r_uint16
id|unused_6
(braket
l_int|0x11
)braket
suffix:semicolon
multiline_comment|/* d0-f0 */
DECL|member|scsiControlPins
r_uint16
id|scsiControlPins
suffix:semicolon
multiline_comment|/* f2 */
)brace
suffix:semicolon
DECL|macro|MAILBOX_REGISTER_COUNT
mdefine_line|#define MAILBOX_REGISTER_COUNT&t;8
multiline_comment|/*&n; *  ISP product identification definitions in mailboxes after reset.&n; */
DECL|macro|PROD_ID_1
mdefine_line|#define PROD_ID_1&t;&t;0x4953
DECL|macro|PROD_ID_2
mdefine_line|#define PROD_ID_2&t;&t;0x0000
DECL|macro|PROD_ID_2a
mdefine_line|#define PROD_ID_2a&t;&t;0x5020
DECL|macro|PROD_ID_3
mdefine_line|#define PROD_ID_3&t;&t;0x2020
DECL|macro|PROD_ID_4
mdefine_line|#define PROD_ID_4&t;&t;0x1
multiline_comment|/*&n; * ISP host command and control register command definitions&n; */
DECL|macro|HC_RESET_RISC
mdefine_line|#define HC_RESET_RISC&t;&t;0x1000&t;/* Reset RISC */
DECL|macro|HC_PAUSE_RISC
mdefine_line|#define HC_PAUSE_RISC&t;&t;0x2000&t;/* Pause RISC */
DECL|macro|HC_RELEASE_RISC
mdefine_line|#define HC_RELEASE_RISC&t;&t;0x3000&t;/* Release RISC from reset. */
DECL|macro|HC_SET_HOST_INT
mdefine_line|#define HC_SET_HOST_INT&t;&t;0x5000&t;/* Set host interrupt */
DECL|macro|HC_CLR_HOST_INT
mdefine_line|#define HC_CLR_HOST_INT&t;&t;0x6000&t;/* Clear HOST interrupt */
DECL|macro|HC_CLR_RISC_INT
mdefine_line|#define HC_CLR_RISC_INT&t;&t;0x7000&t;/* Clear RISC interrupt */
DECL|macro|HC_DISABLE_BIOS
mdefine_line|#define HC_DISABLE_BIOS&t;&t;0x9000&t;/* Disable BIOS. */
multiline_comment|/*&n; * ISP mailbox Self-Test status codes&n; */
DECL|macro|MBS_FRM_ALIVE
mdefine_line|#define MBS_FRM_ALIVE&t;&t;0&t;/* Firmware Alive. */
DECL|macro|MBS_CHKSUM_ERR
mdefine_line|#define MBS_CHKSUM_ERR&t;&t;1&t;/* Checksum Error. */
DECL|macro|MBS_SHADOW_LD_ERR
mdefine_line|#define MBS_SHADOW_LD_ERR&t;2&t;/* Shadow Load Error. */
DECL|macro|MBS_BUSY
mdefine_line|#define MBS_BUSY&t;&t;4&t;/* Busy. */
multiline_comment|/*&n; * ISP mailbox command complete status codes&n; */
DECL|macro|MBS_CMD_CMP
mdefine_line|#define MBS_CMD_CMP&t;&t;0x4000&t;/* Command Complete. */
DECL|macro|MBS_INV_CMD
mdefine_line|#define MBS_INV_CMD&t;&t;0x4001&t;/* Invalid Command. */
DECL|macro|MBS_HOST_INF_ERR
mdefine_line|#define MBS_HOST_INF_ERR&t;0x4002&t;/* Host Interface Error. */
DECL|macro|MBS_TEST_FAILED
mdefine_line|#define MBS_TEST_FAILED&t;&t;0x4003&t;/* Test Failed. */
DECL|macro|MBS_CMD_ERR
mdefine_line|#define MBS_CMD_ERR&t;&t;0x4005&t;/* Command Error. */
DECL|macro|MBS_CMD_PARAM_ERR
mdefine_line|#define MBS_CMD_PARAM_ERR&t;0x4006&t;/* Command Parameter Error. */
multiline_comment|/*&n; * ISP mailbox asynchronous event status codes&n; */
DECL|macro|MBA_ASYNC_EVENT
mdefine_line|#define MBA_ASYNC_EVENT&t;&t;0x8000&t;/* Asynchronous event. */
DECL|macro|MBA_BUS_RESET
mdefine_line|#define MBA_BUS_RESET&t;&t;0x8001&t;/* SCSI Bus Reset. */
DECL|macro|MBA_SYSTEM_ERR
mdefine_line|#define MBA_SYSTEM_ERR&t;&t;0x8002&t;/* System Error. */
DECL|macro|MBA_REQ_TRANSFER_ERR
mdefine_line|#define MBA_REQ_TRANSFER_ERR&t;0x8003&t;/* Request Transfer Error. */
DECL|macro|MBA_RSP_TRANSFER_ERR
mdefine_line|#define MBA_RSP_TRANSFER_ERR&t;0x8004&t;/* Response Transfer Error. */
DECL|macro|MBA_WAKEUP_THRES
mdefine_line|#define MBA_WAKEUP_THRES&t;0x8005&t;/* Request Queue Wake-up. */
DECL|macro|MBA_TIMEOUT_RESET
mdefine_line|#define MBA_TIMEOUT_RESET&t;0x8006&t;/* Execution Timeout Reset. */
DECL|macro|MBA_DEVICE_RESET
mdefine_line|#define MBA_DEVICE_RESET&t;0x8007&t;/* Bus Device Reset. */
DECL|macro|MBA_BUS_MODE_CHANGE
mdefine_line|#define MBA_BUS_MODE_CHANGE&t;0x800E&t;/* SCSI bus mode transition. */
DECL|macro|MBA_SCSI_COMPLETION
mdefine_line|#define MBA_SCSI_COMPLETION&t;0x8020&t;/* Completion response. */
multiline_comment|/*&n; * ISP mailbox commands&n; */
DECL|macro|MBC_NOP
mdefine_line|#define MBC_NOP&t;&t;&t;&t;0&t;/* No Operation */
DECL|macro|MBC_LOAD_RAM
mdefine_line|#define MBC_LOAD_RAM&t;&t;&t;1&t;/* Load RAM */
DECL|macro|MBC_EXECUTE_FIRMWARE
mdefine_line|#define MBC_EXECUTE_FIRMWARE&t;&t;2&t;/* Execute firmware */
DECL|macro|MBC_DUMP_RAM
mdefine_line|#define MBC_DUMP_RAM&t;&t;&t;3&t;/* Dump RAM contents */
DECL|macro|MBC_WRITE_RAM_WORD
mdefine_line|#define MBC_WRITE_RAM_WORD&t;&t;4&t;/* Write ram word */
DECL|macro|MBC_READ_RAM_WORD
mdefine_line|#define MBC_READ_RAM_WORD&t;&t;5&t;/* Read ram word */
DECL|macro|MBC_MAILBOX_REGISTER_TEST
mdefine_line|#define MBC_MAILBOX_REGISTER_TEST&t;6&t;/* Wrap incoming mailboxes */
DECL|macro|MBC_VERIFY_CHECKSUM
mdefine_line|#define MBC_VERIFY_CHECKSUM&t;&t;7&t;/* Verify checksum */
DECL|macro|MBC_ABOUT_FIRMWARE
mdefine_line|#define MBC_ABOUT_FIRMWARE&t;&t;8&t;/* Get firmware revision */
DECL|macro|MBC_INIT_REQUEST_QUEUE
mdefine_line|#define MBC_INIT_REQUEST_QUEUE&t;&t;0x10&t;/* Initialize request queue */
DECL|macro|MBC_INIT_RESPONSE_QUEUE
mdefine_line|#define MBC_INIT_RESPONSE_QUEUE&t;&t;0x11&t;/* Initialize response queue */
DECL|macro|MBC_EXECUTE_IOCB
mdefine_line|#define MBC_EXECUTE_IOCB&t;&t;0x12&t;/* Execute IOCB command */
DECL|macro|MBC_ABORT_COMMAND
mdefine_line|#define MBC_ABORT_COMMAND&t;&t;0x15&t;/* Abort IOCB command */
DECL|macro|MBC_ABORT_DEVICE
mdefine_line|#define MBC_ABORT_DEVICE&t;&t;0x16&t;/* Abort device (ID/LUN) */
DECL|macro|MBC_ABORT_TARGET
mdefine_line|#define MBC_ABORT_TARGET&t;&t;0x17&t;/* Abort target (ID) */
DECL|macro|MBC_BUS_RESET
mdefine_line|#define MBC_BUS_RESET&t;&t;&t;0x18&t;/* SCSI bus reset */
DECL|macro|MBC_GET_RETRY_COUNT
mdefine_line|#define MBC_GET_RETRY_COUNT&t;&t;0x22&t;/* Get retry count and delay */
DECL|macro|MBC_GET_TARGET_PARAMETERS
mdefine_line|#define MBC_GET_TARGET_PARAMETERS&t;0x28&t;/* Get target parameters */
DECL|macro|MBC_SET_INITIATOR_ID
mdefine_line|#define MBC_SET_INITIATOR_ID&t;&t;0x30&t;/* Set initiator SCSI ID */
DECL|macro|MBC_SET_SELECTION_TIMEOUT
mdefine_line|#define MBC_SET_SELECTION_TIMEOUT&t;0x31&t;/* Set selection timeout */
DECL|macro|MBC_SET_RETRY_COUNT
mdefine_line|#define MBC_SET_RETRY_COUNT&t;&t;0x32&t;/* Set retry count and delay */
DECL|macro|MBC_SET_TAG_AGE_LIMIT
mdefine_line|#define MBC_SET_TAG_AGE_LIMIT&t;&t;0x33&t;/* Set tag age limit */
DECL|macro|MBC_SET_CLOCK_RATE
mdefine_line|#define MBC_SET_CLOCK_RATE&t;&t;0x34&t;/* Set clock rate */
DECL|macro|MBC_SET_ACTIVE_NEGATION
mdefine_line|#define MBC_SET_ACTIVE_NEGATION&t;&t;0x35&t;/* Set active negation state */
DECL|macro|MBC_SET_ASYNC_DATA_SETUP
mdefine_line|#define MBC_SET_ASYNC_DATA_SETUP&t;0x36&t;/* Set async data setup time */
DECL|macro|MBC_SET_PCI_CONTROL
mdefine_line|#define MBC_SET_PCI_CONTROL&t;&t;0x37&t;/* Set BUS control parameters */
DECL|macro|MBC_SET_TARGET_PARAMETERS
mdefine_line|#define MBC_SET_TARGET_PARAMETERS&t;0x38&t;/* Set target parameters */
DECL|macro|MBC_SET_DEVICE_QUEUE
mdefine_line|#define MBC_SET_DEVICE_QUEUE&t;&t;0x39&t;/* Set device queue parameters */
DECL|macro|MBC_SET_RESET_DELAY_PARAMETERS
mdefine_line|#define MBC_SET_RESET_DELAY_PARAMETERS&t;0x3A&t;/* Set reset delay parameters */
DECL|macro|MBC_SET_SYSTEM_PARAMETER
mdefine_line|#define MBC_SET_SYSTEM_PARAMETER&t;0x45&t;/* Set system parameter word */
DECL|macro|MBC_SET_FIRMWARE_FEATURES
mdefine_line|#define MBC_SET_FIRMWARE_FEATURES&t;0x4A&t;/* Set firmware feature word */
DECL|macro|MBC_INIT_REQUEST_QUEUE_A64
mdefine_line|#define MBC_INIT_REQUEST_QUEUE_A64&t;0x52&t;/* Initialize request queue A64 */
DECL|macro|MBC_INIT_RESPONSE_QUEUE_A64
mdefine_line|#define MBC_INIT_RESPONSE_QUEUE_A64&t;0x53&t;/* Initialize response q A64 */
DECL|macro|MBC_ENABLE_TARGET_MODE
mdefine_line|#define MBC_ENABLE_TARGET_MODE&t;&t;0x55&t;/* Enable target mode */
DECL|macro|MBC_SET_DATA_OVERRUN_RECOVERY
mdefine_line|#define MBC_SET_DATA_OVERRUN_RECOVERY&t;0x5A&t;/* Set data overrun recovery mode */
multiline_comment|/*&n; * ISP Get/Set Target Parameters mailbox command control flags.&n; */
DECL|macro|TP_PPR
mdefine_line|#define TP_PPR&t;&t;&t;BIT_5&t;/* PPR */
DECL|macro|TP_RENEGOTIATE
mdefine_line|#define TP_RENEGOTIATE&t;&t;BIT_8&t;/* Renegotiate on error. */
DECL|macro|TP_STOP_QUEUE
mdefine_line|#define TP_STOP_QUEUE           BIT_9&t;/* Stop que on check condition */
DECL|macro|TP_AUTO_REQUEST_SENSE
mdefine_line|#define TP_AUTO_REQUEST_SENSE   BIT_10&t;/* Automatic request sense. */
DECL|macro|TP_TAGGED_QUEUE
mdefine_line|#define TP_TAGGED_QUEUE         BIT_11&t;/* Tagged queuing. */
DECL|macro|TP_SYNC
mdefine_line|#define TP_SYNC                 BIT_12&t;/* Synchronous data transfers. */
DECL|macro|TP_WIDE
mdefine_line|#define TP_WIDE                 BIT_13&t;/* Wide data transfers. */
DECL|macro|TP_PARITY
mdefine_line|#define TP_PARITY               BIT_14&t;/* Parity checking. */
DECL|macro|TP_DISCONNECT
mdefine_line|#define TP_DISCONNECT           BIT_15&t;/* Disconnect privilege. */
multiline_comment|/*&n; * NVRAM Command values.&n; */
DECL|macro|NV_START_BIT
mdefine_line|#define NV_START_BIT&t;&t;BIT_2
DECL|macro|NV_WRITE_OP
mdefine_line|#define NV_WRITE_OP&t;&t;(BIT_26 | BIT_24)
DECL|macro|NV_READ_OP
mdefine_line|#define NV_READ_OP&t;&t;(BIT_26 | BIT_25)
DECL|macro|NV_ERASE_OP
mdefine_line|#define NV_ERASE_OP&t;&t;(BIT_26 | BIT_25 | BIT_24)
DECL|macro|NV_MASK_OP
mdefine_line|#define NV_MASK_OP&t;&t;(BIT_26 | BIT_25 | BIT_24)
DECL|macro|NV_DELAY_COUNT
mdefine_line|#define NV_DELAY_COUNT&t;&t;10
multiline_comment|/*&n; *  QLogic ISP1280/ISP12160 NVRAM structure definition.&n; */
DECL|struct|nvram
r_struct
id|nvram
(brace
DECL|member|id0
r_uint8
id|id0
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|id1
r_uint8
id|id1
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|id2
r_uint8
id|id2
suffix:semicolon
multiline_comment|/* 2 */
DECL|member|id3
r_uint8
id|id3
suffix:semicolon
multiline_comment|/* 3 */
DECL|member|version
r_uint8
id|version
suffix:semicolon
multiline_comment|/* 4 */
r_struct
(brace
DECL|member|bios_configuration_mode
r_uint8
id|bios_configuration_mode
suffix:colon
l_int|2
suffix:semicolon
DECL|member|bios_disable
r_uint8
id|bios_disable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|selectable_scsi_boot_enable
r_uint8
id|selectable_scsi_boot_enable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cd_rom_boot_enable
r_uint8
id|cd_rom_boot_enable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|disable_loading_risc_code
r_uint8
id|disable_loading_risc_code
suffix:colon
l_int|1
suffix:semicolon
DECL|member|enable_64bit_addressing
r_uint8
id|enable_64bit_addressing
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_7
r_uint8
id|unused_7
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cntr_flags_1
)brace
id|cntr_flags_1
suffix:semicolon
multiline_comment|/* 5 */
r_struct
(brace
DECL|member|boot_lun_number
r_uint8
id|boot_lun_number
suffix:colon
l_int|5
suffix:semicolon
DECL|member|scsi_bus_number
r_uint8
id|scsi_bus_number
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_6
r_uint8
id|unused_6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_7
r_uint8
id|unused_7
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cntr_flags_2l
)brace
id|cntr_flags_2l
suffix:semicolon
multiline_comment|/* 7 */
r_struct
(brace
DECL|member|boot_target_number
r_uint8
id|boot_target_number
suffix:colon
l_int|4
suffix:semicolon
DECL|member|unused_12
r_uint8
id|unused_12
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_13
r_uint8
id|unused_13
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_14
r_uint8
id|unused_14
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_15
r_uint8
id|unused_15
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cntr_flags_2h
)brace
id|cntr_flags_2h
suffix:semicolon
multiline_comment|/* 8 */
DECL|member|unused_8
r_uint16
id|unused_8
suffix:semicolon
multiline_comment|/* 8, 9 */
DECL|member|unused_10
r_uint16
id|unused_10
suffix:semicolon
multiline_comment|/* 10, 11 */
DECL|member|unused_12
r_uint16
id|unused_12
suffix:semicolon
multiline_comment|/* 12, 13 */
DECL|member|unused_14
r_uint16
id|unused_14
suffix:semicolon
multiline_comment|/* 14, 15 */
r_union
(brace
DECL|member|c
r_uint8
id|c
suffix:semicolon
r_struct
(brace
DECL|member|reserved
r_uint8
id|reserved
suffix:colon
l_int|2
suffix:semicolon
DECL|member|burst_enable
r_uint8
id|burst_enable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved_1
r_uint8
id|reserved_1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fifo_threshold
r_uint8
id|fifo_threshold
suffix:colon
l_int|4
suffix:semicolon
DECL|member|f
)brace
id|f
suffix:semicolon
DECL|member|isp_config
)brace
id|isp_config
suffix:semicolon
multiline_comment|/* 16 */
multiline_comment|/* Termination&n;&t; * 0 = Disable, 1 = high only, 3 = Auto term&n;&t; */
r_union
(brace
DECL|member|c
r_uint8
id|c
suffix:semicolon
r_struct
(brace
DECL|member|scsi_bus_1_control
r_uint8
id|scsi_bus_1_control
suffix:colon
l_int|2
suffix:semicolon
DECL|member|scsi_bus_0_control
r_uint8
id|scsi_bus_0_control
suffix:colon
l_int|2
suffix:semicolon
DECL|member|unused_0
r_uint8
id|unused_0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_1
r_uint8
id|unused_1
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_2
r_uint8
id|unused_2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|auto_term_support
r_uint8
id|auto_term_support
suffix:colon
l_int|1
suffix:semicolon
DECL|member|f
)brace
id|f
suffix:semicolon
DECL|member|termination
)brace
id|termination
suffix:semicolon
multiline_comment|/* 17 */
DECL|member|isp_parameter
r_uint16
id|isp_parameter
suffix:semicolon
multiline_comment|/* 18, 19 */
r_union
(brace
DECL|member|w
r_uint16
id|w
suffix:semicolon
r_struct
(brace
DECL|member|enable_fast_posting
r_uint16
id|enable_fast_posting
suffix:colon
l_int|1
suffix:semicolon
DECL|member|report_lvd_bus_transition
r_uint16
id|report_lvd_bus_transition
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_2
r_uint16
id|unused_2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_3
r_uint16
id|unused_3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|disable_iosbs_with_bus_reset_status
r_uint16
id|disable_iosbs_with_bus_reset_status
suffix:colon
l_int|1
suffix:semicolon
DECL|member|disable_synchronous_backoff
r_uint16
id|disable_synchronous_backoff
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_6
r_uint16
id|unused_6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|synchronous_backoff_reporting
r_uint16
id|synchronous_backoff_reporting
suffix:colon
l_int|1
suffix:semicolon
DECL|member|disable_reselection_fairness
r_uint16
id|disable_reselection_fairness
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_9
r_uint16
id|unused_9
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_10
r_uint16
id|unused_10
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_11
r_uint16
id|unused_11
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_12
r_uint16
id|unused_12
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_13
r_uint16
id|unused_13
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_14
r_uint16
id|unused_14
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_15
r_uint16
id|unused_15
suffix:colon
l_int|1
suffix:semicolon
DECL|member|f
)brace
id|f
suffix:semicolon
DECL|member|firmware_feature
)brace
id|firmware_feature
suffix:semicolon
multiline_comment|/* 20, 21 */
DECL|member|unused_22
r_uint16
id|unused_22
suffix:semicolon
multiline_comment|/* 22, 23 */
r_struct
(brace
r_struct
(brace
DECL|member|initiator_id
r_uint8
id|initiator_id
suffix:colon
l_int|4
suffix:semicolon
DECL|member|scsi_reset_disable
r_uint8
id|scsi_reset_disable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|scsi_bus_size
r_uint8
id|scsi_bus_size
suffix:colon
l_int|1
suffix:semicolon
DECL|member|scsi_bus_type
r_uint8
id|scsi_bus_type
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_7
r_uint8
id|unused_7
suffix:colon
l_int|1
suffix:semicolon
DECL|member|config_1
)brace
id|config_1
suffix:semicolon
multiline_comment|/* 24 */
DECL|member|bus_reset_delay
r_uint8
id|bus_reset_delay
suffix:semicolon
multiline_comment|/* 25 */
DECL|member|retry_count
r_uint8
id|retry_count
suffix:semicolon
multiline_comment|/* 26 */
DECL|member|retry_delay
r_uint8
id|retry_delay
suffix:semicolon
multiline_comment|/* 27 */
r_struct
(brace
DECL|member|async_data_setup_time
r_uint8
id|async_data_setup_time
suffix:colon
l_int|4
suffix:semicolon
DECL|member|req_ack_active_negation
r_uint8
id|req_ack_active_negation
suffix:colon
l_int|1
suffix:semicolon
DECL|member|data_line_active_negation
r_uint8
id|data_line_active_negation
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_6
r_uint8
id|unused_6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_7
r_uint8
id|unused_7
suffix:colon
l_int|1
suffix:semicolon
DECL|member|config_2
)brace
id|config_2
suffix:semicolon
multiline_comment|/* 28 */
DECL|member|unused_29
r_uint8
id|unused_29
suffix:semicolon
multiline_comment|/* 29 */
DECL|member|selection_timeout
r_uint16
id|selection_timeout
suffix:semicolon
multiline_comment|/* 30, 31 */
DECL|member|max_queue_depth
r_uint16
id|max_queue_depth
suffix:semicolon
multiline_comment|/* 32, 33 */
DECL|member|unused_34
r_uint16
id|unused_34
suffix:semicolon
multiline_comment|/* 34, 35 */
DECL|member|unused_36
r_uint16
id|unused_36
suffix:semicolon
multiline_comment|/* 36, 37 */
DECL|member|unused_38
r_uint16
id|unused_38
suffix:semicolon
multiline_comment|/* 38, 39 */
r_struct
(brace
r_union
(brace
DECL|member|c
r_uint8
id|c
suffix:semicolon
r_struct
(brace
DECL|member|renegotiate_on_error
r_uint8
id|renegotiate_on_error
suffix:colon
l_int|1
suffix:semicolon
DECL|member|stop_queue_on_check
r_uint8
id|stop_queue_on_check
suffix:colon
l_int|1
suffix:semicolon
DECL|member|auto_request_sense
r_uint8
id|auto_request_sense
suffix:colon
l_int|1
suffix:semicolon
DECL|member|tag_queuing
r_uint8
id|tag_queuing
suffix:colon
l_int|1
suffix:semicolon
DECL|member|enable_sync
r_uint8
id|enable_sync
suffix:colon
l_int|1
suffix:semicolon
DECL|member|enable_wide
r_uint8
id|enable_wide
suffix:colon
l_int|1
suffix:semicolon
DECL|member|parity_checking
r_uint8
id|parity_checking
suffix:colon
l_int|1
suffix:semicolon
DECL|member|disconnect_allowed
r_uint8
id|disconnect_allowed
suffix:colon
l_int|1
suffix:semicolon
DECL|member|f
)brace
id|f
suffix:semicolon
DECL|member|parameter
)brace
id|parameter
suffix:semicolon
multiline_comment|/* 40 */
DECL|member|execution_throttle
r_uint8
id|execution_throttle
suffix:semicolon
multiline_comment|/* 41 */
DECL|member|sync_period
r_uint8
id|sync_period
suffix:semicolon
multiline_comment|/* 42 */
r_union
(brace
multiline_comment|/* 43 */
DECL|member|flags_43
r_uint8
id|flags_43
suffix:semicolon
r_struct
(brace
DECL|member|sync_offset
r_uint8
id|sync_offset
suffix:colon
l_int|4
suffix:semicolon
DECL|member|device_enable
r_uint8
id|device_enable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|lun_disable
r_uint8
id|lun_disable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_6
r_uint8
id|unused_6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_7
r_uint8
id|unused_7
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flags1x80
)brace
id|flags1x80
suffix:semicolon
r_struct
(brace
DECL|member|sync_offset
r_uint8
id|sync_offset
suffix:colon
l_int|5
suffix:semicolon
DECL|member|device_enable
r_uint8
id|device_enable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_6
r_uint8
id|unused_6
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_7
r_uint8
id|unused_7
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flags1x160
)brace
id|flags1x160
suffix:semicolon
DECL|member|flags
)brace
id|flags
suffix:semicolon
r_union
(brace
multiline_comment|/* PPR flags for the 1x160 controllers */
DECL|member|unused_44
r_uint8
id|unused_44
suffix:semicolon
r_struct
(brace
DECL|member|ppr_options
r_uint8
id|ppr_options
suffix:colon
l_int|4
suffix:semicolon
DECL|member|ppr_bus_width
r_uint8
id|ppr_bus_width
suffix:colon
l_int|2
suffix:semicolon
DECL|member|unused_8
r_uint8
id|unused_8
suffix:colon
l_int|1
suffix:semicolon
DECL|member|enable_ppr
r_uint8
id|enable_ppr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flags
)brace
id|flags
suffix:semicolon
multiline_comment|/* 44 */
DECL|member|ppr_1x160
)brace
id|ppr_1x160
suffix:semicolon
DECL|member|unused_45
r_uint8
id|unused_45
suffix:semicolon
multiline_comment|/* 45 */
DECL|member|target
)brace
id|target
(braket
id|MAX_TARGETS
)braket
suffix:semicolon
DECL|member|bus
)brace
id|bus
(braket
id|MAX_BUSES
)braket
suffix:semicolon
DECL|member|unused_248
r_uint16
id|unused_248
suffix:semicolon
multiline_comment|/* 248, 249 */
DECL|member|subsystem_id
r_uint16
id|subsystem_id
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 250, 251, 252, 253 */
r_union
(brace
multiline_comment|/* 254 */
DECL|member|unused_254
r_uint8
id|unused_254
suffix:semicolon
DECL|member|system_id_pointer
r_uint8
id|system_id_pointer
suffix:semicolon
DECL|member|sysid_1x160
)brace
id|sysid_1x160
suffix:semicolon
DECL|member|chksum
r_uint8
id|chksum
suffix:semicolon
multiline_comment|/* 255 */
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - command entry structure definition.&n; */
DECL|macro|MAX_CMDSZ
mdefine_line|#define MAX_CMDSZ&t;12&t;&t;/* SCSI maximum CDB size. */
DECL|struct|cmd_entry
r_struct
id|cmd_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|COMMAND_TYPE
mdefine_line|#define COMMAND_TYPE    1&t;&t;/* Command entry */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|sys_define
r_uint8
id|sys_define
suffix:semicolon
multiline_comment|/* System defined. */
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|handle
r_uint32
id|handle
suffix:semicolon
multiline_comment|/* System handle. */
DECL|member|lun
r_uint8
id|lun
suffix:semicolon
multiline_comment|/* SCSI LUN */
DECL|member|target
r_uint8
id|target
suffix:semicolon
multiline_comment|/* SCSI ID */
DECL|member|cdb_len
r_uint16
id|cdb_len
suffix:semicolon
multiline_comment|/* SCSI command length. */
DECL|member|control_flags
r_uint16
id|control_flags
suffix:semicolon
multiline_comment|/* Control flags. */
DECL|member|reserved
r_uint16
id|reserved
suffix:semicolon
DECL|member|timeout
r_uint16
id|timeout
suffix:semicolon
multiline_comment|/* Command timeout. */
DECL|member|dseg_count
r_uint16
id|dseg_count
suffix:semicolon
multiline_comment|/* Data segment count. */
DECL|member|scsi_cdb
r_uint8
id|scsi_cdb
(braket
id|MAX_CMDSZ
)braket
suffix:semicolon
multiline_comment|/* SCSI command words. */
DECL|member|dseg_0_address
r_uint32
id|dseg_0_address
suffix:semicolon
multiline_comment|/* Data segment 0 address. */
DECL|member|dseg_0_length
r_uint32
id|dseg_0_length
suffix:semicolon
multiline_comment|/* Data segment 0 length. */
DECL|member|dseg_1_address
r_uint32
id|dseg_1_address
suffix:semicolon
multiline_comment|/* Data segment 1 address. */
DECL|member|dseg_1_length
r_uint32
id|dseg_1_length
suffix:semicolon
multiline_comment|/* Data segment 1 length. */
DECL|member|dseg_2_address
r_uint32
id|dseg_2_address
suffix:semicolon
multiline_comment|/* Data segment 2 address. */
DECL|member|dseg_2_length
r_uint32
id|dseg_2_length
suffix:semicolon
multiline_comment|/* Data segment 2 length. */
DECL|member|dseg_3_address
r_uint32
id|dseg_3_address
suffix:semicolon
multiline_comment|/* Data segment 3 address. */
DECL|member|dseg_3_length
r_uint32
id|dseg_3_length
suffix:semicolon
multiline_comment|/* Data segment 3 length. */
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - continuation entry structure definition.&n; */
DECL|struct|cont_entry
r_struct
id|cont_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|CONTINUE_TYPE
mdefine_line|#define CONTINUE_TYPE   2&t;&t;/* Continuation entry. */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|sys_define
r_uint8
id|sys_define
suffix:semicolon
multiline_comment|/* System defined. */
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|reserved
r_uint32
id|reserved
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|dseg_0_address
r_uint32
id|dseg_0_address
suffix:semicolon
multiline_comment|/* Data segment 0 address. */
DECL|member|dseg_0_length
r_uint32
id|dseg_0_length
suffix:semicolon
multiline_comment|/* Data segment 0 length. */
DECL|member|dseg_1_address
r_uint32
id|dseg_1_address
suffix:semicolon
multiline_comment|/* Data segment 1 address. */
DECL|member|dseg_1_length
r_uint32
id|dseg_1_length
suffix:semicolon
multiline_comment|/* Data segment 1 length. */
DECL|member|dseg_2_address
r_uint32
id|dseg_2_address
suffix:semicolon
multiline_comment|/* Data segment 2 address. */
DECL|member|dseg_2_length
r_uint32
id|dseg_2_length
suffix:semicolon
multiline_comment|/* Data segment 2 length. */
DECL|member|dseg_3_address
r_uint32
id|dseg_3_address
suffix:semicolon
multiline_comment|/* Data segment 3 address. */
DECL|member|dseg_3_length
r_uint32
id|dseg_3_length
suffix:semicolon
multiline_comment|/* Data segment 3 length. */
DECL|member|dseg_4_address
r_uint32
id|dseg_4_address
suffix:semicolon
multiline_comment|/* Data segment 4 address. */
DECL|member|dseg_4_length
r_uint32
id|dseg_4_length
suffix:semicolon
multiline_comment|/* Data segment 4 length. */
DECL|member|dseg_5_address
r_uint32
id|dseg_5_address
suffix:semicolon
multiline_comment|/* Data segment 5 address. */
DECL|member|dseg_5_length
r_uint32
id|dseg_5_length
suffix:semicolon
multiline_comment|/* Data segment 5 length. */
DECL|member|dseg_6_address
r_uint32
id|dseg_6_address
suffix:semicolon
multiline_comment|/* Data segment 6 address. */
DECL|member|dseg_6_length
r_uint32
id|dseg_6_length
suffix:semicolon
multiline_comment|/* Data segment 6 length. */
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - status entry structure definition.&n; */
DECL|struct|response
r_struct
id|response
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|STATUS_TYPE
mdefine_line|#define STATUS_TYPE     3&t;/* Status entry. */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|sys_define
r_uint8
id|sys_define
suffix:semicolon
multiline_comment|/* System defined. */
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|macro|RF_CONT
mdefine_line|#define RF_CONT         BIT_0&t;/* Continuation. */
DECL|macro|RF_FULL
mdefine_line|#define RF_FULL         BIT_1&t;/* Full */
DECL|macro|RF_BAD_HEADER
mdefine_line|#define RF_BAD_HEADER   BIT_2&t;/* Bad header. */
DECL|macro|RF_BAD_PAYLOAD
mdefine_line|#define RF_BAD_PAYLOAD  BIT_3&t;/* Bad payload. */
DECL|member|handle
r_uint32
id|handle
suffix:semicolon
multiline_comment|/* System handle. */
DECL|member|scsi_status
r_uint16
id|scsi_status
suffix:semicolon
multiline_comment|/* SCSI status. */
DECL|member|comp_status
r_uint16
id|comp_status
suffix:semicolon
multiline_comment|/* Completion status. */
DECL|member|state_flags
r_uint16
id|state_flags
suffix:semicolon
multiline_comment|/* State flags. */
DECL|macro|SF_TRANSFER_CMPL
mdefine_line|#define SF_TRANSFER_CMPL BIT_14&t;/* Transfer Complete. */
DECL|macro|SF_GOT_SENSE
mdefine_line|#define SF_GOT_SENSE    BIT_13&t;/* Got Sense */
DECL|macro|SF_GOT_STATUS
mdefine_line|#define SF_GOT_STATUS    BIT_12&t;/* Got Status */
DECL|macro|SF_TRANSFERRED_DATA
mdefine_line|#define SF_TRANSFERRED_DATA BIT_11&t;/* Transferred data */
DECL|macro|SF_SENT_CDB
mdefine_line|#define SF_SENT_CDB   BIT_10&t;/* Send CDB */
DECL|macro|SF_GOT_TARGET
mdefine_line|#define SF_GOT_TARGET  BIT_9&t;/*  */
DECL|macro|SF_GOT_BUS
mdefine_line|#define SF_GOT_BUS     BIT_8&t;/*  */
DECL|member|status_flags
r_uint16
id|status_flags
suffix:semicolon
multiline_comment|/* Status flags. */
DECL|member|time
r_uint16
id|time
suffix:semicolon
multiline_comment|/* Time. */
DECL|member|req_sense_length
r_uint16
id|req_sense_length
suffix:semicolon
multiline_comment|/* Request sense data length. */
DECL|member|residual_length
r_uint32
id|residual_length
suffix:semicolon
multiline_comment|/* Residual transfer length. */
DECL|member|reserved
r_uint16
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|req_sense_data
r_uint8
id|req_sense_data
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Request sense data. */
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - marker entry structure definition.&n; */
DECL|struct|mrk_entry
r_struct
id|mrk_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|MARKER_TYPE
mdefine_line|#define MARKER_TYPE     4&t;/* Marker entry. */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|sys_define
r_uint8
id|sys_define
suffix:semicolon
multiline_comment|/* System defined. */
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|reserved
r_uint32
id|reserved
suffix:semicolon
DECL|member|lun
r_uint8
id|lun
suffix:semicolon
multiline_comment|/* SCSI LUN */
DECL|member|target
r_uint8
id|target
suffix:semicolon
multiline_comment|/* SCSI ID */
DECL|member|modifier
r_uint8
id|modifier
suffix:semicolon
multiline_comment|/* Modifier (7-0). */
DECL|macro|MK_SYNC_ID_LUN
mdefine_line|#define MK_SYNC_ID_LUN      0&t;/* Synchronize ID/LUN */
DECL|macro|MK_SYNC_ID
mdefine_line|#define MK_SYNC_ID          1&t;/* Synchronize ID */
DECL|macro|MK_SYNC_ALL
mdefine_line|#define MK_SYNC_ALL         2&t;/* Synchronize all ID/LUN */
DECL|member|reserved_1
r_uint8
id|reserved_1
(braket
l_int|53
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - extended command entry structure definition.&n; *&n; * Unused by the driver!&n; */
DECL|struct|ecmd_entry
r_struct
id|ecmd_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|EXTENDED_CMD_TYPE
mdefine_line|#define EXTENDED_CMD_TYPE  5&t;/* Extended command entry. */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|sys_define
r_uint8
id|sys_define
suffix:semicolon
multiline_comment|/* System defined. */
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|handle
r_uint32
id|handle
suffix:semicolon
multiline_comment|/* System handle. */
DECL|member|lun
r_uint8
id|lun
suffix:semicolon
multiline_comment|/* SCSI LUN */
DECL|member|target
r_uint8
id|target
suffix:semicolon
multiline_comment|/* SCSI ID */
DECL|member|cdb_len
r_uint16
id|cdb_len
suffix:semicolon
multiline_comment|/* SCSI command length. */
DECL|member|control_flags
r_uint16
id|control_flags
suffix:semicolon
multiline_comment|/* Control flags. */
DECL|member|reserved
r_uint16
id|reserved
suffix:semicolon
DECL|member|timeout
r_uint16
id|timeout
suffix:semicolon
multiline_comment|/* Command timeout. */
DECL|member|dseg_count
r_uint16
id|dseg_count
suffix:semicolon
multiline_comment|/* Data segment count. */
DECL|member|scsi_cdb
r_uint8
id|scsi_cdb
(braket
l_int|88
)braket
suffix:semicolon
multiline_comment|/* SCSI command words. */
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - 64-Bit addressing, command entry structure definition.&n; */
r_typedef
r_struct
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|COMMAND_A64_TYPE
mdefine_line|#define COMMAND_A64_TYPE 9&t;/* Command A64 entry */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|sys_define
r_uint8
id|sys_define
suffix:semicolon
multiline_comment|/* System defined. */
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|handle
r_uint32
id|handle
suffix:semicolon
multiline_comment|/* System handle. */
DECL|member|lun
r_uint8
id|lun
suffix:semicolon
multiline_comment|/* SCSI LUN */
DECL|member|target
r_uint8
id|target
suffix:semicolon
multiline_comment|/* SCSI ID */
DECL|member|cdb_len
r_uint16
id|cdb_len
suffix:semicolon
multiline_comment|/* SCSI command length. */
DECL|member|control_flags
r_uint16
id|control_flags
suffix:semicolon
multiline_comment|/* Control flags. */
DECL|member|reserved
r_uint16
id|reserved
suffix:semicolon
DECL|member|timeout
r_uint16
id|timeout
suffix:semicolon
multiline_comment|/* Command timeout. */
DECL|member|dseg_count
r_uint16
id|dseg_count
suffix:semicolon
multiline_comment|/* Data segment count. */
DECL|member|scsi_cdb
r_uint8
id|scsi_cdb
(braket
id|MAX_CMDSZ
)braket
suffix:semicolon
multiline_comment|/* SCSI command words. */
DECL|member|reserved_1
r_uint32
id|reserved_1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|dseg_0_address
r_uint32
id|dseg_0_address
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Data segment 0 address. */
DECL|member|dseg_0_length
r_uint32
id|dseg_0_length
suffix:semicolon
multiline_comment|/* Data segment 0 length. */
DECL|member|dseg_1_address
r_uint32
id|dseg_1_address
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Data segment 1 address. */
DECL|member|dseg_1_length
r_uint32
id|dseg_1_length
suffix:semicolon
multiline_comment|/* Data segment 1 length. */
DECL|typedef|cmd_a64_entry_t
DECL|typedef|request_t
)brace
id|cmd_a64_entry_t
comma
id|request_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - 64-Bit addressing, continuation entry structure definition.&n; */
DECL|struct|cont_a64_entry
r_struct
id|cont_a64_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|CONTINUE_A64_TYPE
mdefine_line|#define CONTINUE_A64_TYPE 0xA&t;/* Continuation A64 entry. */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|sys_define
r_uint8
id|sys_define
suffix:semicolon
multiline_comment|/* System defined. */
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|dseg_0_address
r_uint32
id|dseg_0_address
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Data segment 0 address. */
DECL|member|dseg_0_length
r_uint32
id|dseg_0_length
suffix:semicolon
multiline_comment|/* Data segment 0 length. */
DECL|member|dseg_1_address
r_uint32
id|dseg_1_address
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Data segment 1 address. */
DECL|member|dseg_1_length
r_uint32
id|dseg_1_length
suffix:semicolon
multiline_comment|/* Data segment 1 length. */
DECL|member|dseg_2_address
r_uint32
id|dseg_2_address
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Data segment 2 address. */
DECL|member|dseg_2_length
r_uint32
id|dseg_2_length
suffix:semicolon
multiline_comment|/* Data segment 2 length. */
DECL|member|dseg_3_address
r_uint32
id|dseg_3_address
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Data segment 3 address. */
DECL|member|dseg_3_length
r_uint32
id|dseg_3_length
suffix:semicolon
multiline_comment|/* Data segment 3 length. */
DECL|member|dseg_4_address
r_uint32
id|dseg_4_address
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Data segment 4 address. */
DECL|member|dseg_4_length
r_uint32
id|dseg_4_length
suffix:semicolon
multiline_comment|/* Data segment 4 length. */
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - enable LUN entry structure definition.&n; */
DECL|struct|elun_entry
r_struct
id|elun_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|ENABLE_LUN_TYPE
mdefine_line|#define ENABLE_LUN_TYPE 0xB&t;/* Enable LUN entry. */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|reserved_1
r_uint8
id|reserved_1
suffix:semicolon
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status not used. */
DECL|member|reserved_2
r_uint32
id|reserved_2
suffix:semicolon
DECL|member|lun
r_uint16
id|lun
suffix:semicolon
multiline_comment|/* Bit 15 is bus number. */
DECL|member|reserved_4
r_uint16
id|reserved_4
suffix:semicolon
DECL|member|option_flags
r_uint32
id|option_flags
suffix:semicolon
DECL|member|status
r_uint8
id|status
suffix:semicolon
DECL|member|reserved_5
r_uint8
id|reserved_5
suffix:semicolon
DECL|member|command_count
r_uint8
id|command_count
suffix:semicolon
multiline_comment|/* Number of ATIOs allocated. */
DECL|member|immed_notify_count
r_uint8
id|immed_notify_count
suffix:semicolon
multiline_comment|/* Number of Immediate Notify */
multiline_comment|/* entries allocated. */
DECL|member|group_6_length
r_uint8
id|group_6_length
suffix:semicolon
multiline_comment|/* SCSI CDB length for group 6 */
multiline_comment|/* commands (2-26). */
DECL|member|group_7_length
r_uint8
id|group_7_length
suffix:semicolon
multiline_comment|/* SCSI CDB length for group 7 */
multiline_comment|/* commands (2-26). */
DECL|member|timeout
r_uint16
id|timeout
suffix:semicolon
multiline_comment|/* 0 = 30 seconds, 0xFFFF = disable */
DECL|member|reserved_6
r_uint16
id|reserved_6
(braket
l_int|20
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - modify LUN entry structure definition.&n; *&n; * Unused by the driver!&n; */
DECL|struct|modify_lun_entry
r_struct
id|modify_lun_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|MODIFY_LUN_TYPE
mdefine_line|#define MODIFY_LUN_TYPE 0xC&t;/* Modify LUN entry. */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|reserved_1
r_uint8
id|reserved_1
suffix:semicolon
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|reserved_2
r_uint32
id|reserved_2
suffix:semicolon
DECL|member|lun
r_uint8
id|lun
suffix:semicolon
multiline_comment|/* SCSI LUN */
DECL|member|reserved_3
r_uint8
id|reserved_3
suffix:semicolon
DECL|member|operators
r_uint8
id|operators
suffix:semicolon
DECL|member|reserved_4
r_uint8
id|reserved_4
suffix:semicolon
DECL|member|option_flags
r_uint32
id|option_flags
suffix:semicolon
DECL|member|status
r_uint8
id|status
suffix:semicolon
DECL|member|reserved_5
r_uint8
id|reserved_5
suffix:semicolon
DECL|member|command_count
r_uint8
id|command_count
suffix:semicolon
multiline_comment|/* Number of ATIOs allocated. */
DECL|member|immed_notify_count
r_uint8
id|immed_notify_count
suffix:semicolon
multiline_comment|/* Number of Immediate Notify */
multiline_comment|/* entries allocated. */
DECL|member|reserved_6
r_uint16
id|reserved_6
suffix:semicolon
DECL|member|timeout
r_uint16
id|timeout
suffix:semicolon
multiline_comment|/* 0 = 30 seconds, 0xFFFF = disable */
DECL|member|reserved_7
r_uint16
id|reserved_7
(braket
l_int|20
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - immediate notify entry structure definition.&n; */
DECL|struct|notify_entry
r_struct
id|notify_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|IMMED_NOTIFY_TYPE
mdefine_line|#define IMMED_NOTIFY_TYPE 0xD&t;/* Immediate notify entry. */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|reserved_1
r_uint8
id|reserved_1
suffix:semicolon
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|reserved_2
r_uint32
id|reserved_2
suffix:semicolon
DECL|member|lun
r_uint8
id|lun
suffix:semicolon
DECL|member|initiator_id
r_uint8
id|initiator_id
suffix:semicolon
DECL|member|reserved_3
r_uint8
id|reserved_3
suffix:semicolon
DECL|member|target_id
r_uint8
id|target_id
suffix:semicolon
DECL|member|option_flags
r_uint32
id|option_flags
suffix:semicolon
DECL|member|status
r_uint8
id|status
suffix:semicolon
DECL|member|reserved_4
r_uint8
id|reserved_4
suffix:semicolon
DECL|member|tag_value
r_uint8
id|tag_value
suffix:semicolon
multiline_comment|/* Received queue tag message value */
DECL|member|tag_type
r_uint8
id|tag_type
suffix:semicolon
multiline_comment|/* Received queue tag message type */
multiline_comment|/* entries allocated. */
DECL|member|seq_id
r_uint16
id|seq_id
suffix:semicolon
DECL|member|scsi_msg
r_uint8
id|scsi_msg
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* SCSI message not handled by ISP */
DECL|member|reserved_5
r_uint16
id|reserved_5
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|sense_data
r_uint8
id|sense_data
(braket
l_int|18
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - notify acknowledge entry structure definition.&n; */
DECL|struct|nack_entry
r_struct
id|nack_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|NOTIFY_ACK_TYPE
mdefine_line|#define NOTIFY_ACK_TYPE 0xE&t;/* Notify acknowledge entry. */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|reserved_1
r_uint8
id|reserved_1
suffix:semicolon
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|reserved_2
r_uint32
id|reserved_2
suffix:semicolon
DECL|member|lun
r_uint8
id|lun
suffix:semicolon
DECL|member|initiator_id
r_uint8
id|initiator_id
suffix:semicolon
DECL|member|reserved_3
r_uint8
id|reserved_3
suffix:semicolon
DECL|member|target_id
r_uint8
id|target_id
suffix:semicolon
DECL|member|option_flags
r_uint32
id|option_flags
suffix:semicolon
DECL|member|status
r_uint8
id|status
suffix:semicolon
DECL|member|event
r_uint8
id|event
suffix:semicolon
DECL|member|seq_id
r_uint16
id|seq_id
suffix:semicolon
DECL|member|reserved_4
r_uint16
id|reserved_4
(braket
l_int|22
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - Accept Target I/O (ATIO) entry structure definition.&n; */
DECL|struct|atio_entry
r_struct
id|atio_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|ACCEPT_TGT_IO_TYPE
mdefine_line|#define ACCEPT_TGT_IO_TYPE 6&t;/* Accept target I/O entry. */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|reserved_1
r_uint8
id|reserved_1
suffix:semicolon
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|reserved_2
r_uint32
id|reserved_2
suffix:semicolon
DECL|member|lun
r_uint8
id|lun
suffix:semicolon
DECL|member|initiator_id
r_uint8
id|initiator_id
suffix:semicolon
DECL|member|cdb_len
r_uint8
id|cdb_len
suffix:semicolon
DECL|member|target_id
r_uint8
id|target_id
suffix:semicolon
DECL|member|option_flags
r_uint32
id|option_flags
suffix:semicolon
DECL|member|status
r_uint8
id|status
suffix:semicolon
DECL|member|scsi_status
r_uint8
id|scsi_status
suffix:semicolon
DECL|member|tag_value
r_uint8
id|tag_value
suffix:semicolon
multiline_comment|/* Received queue tag message value */
DECL|member|tag_type
r_uint8
id|tag_type
suffix:semicolon
multiline_comment|/* Received queue tag message type */
DECL|member|cdb
r_uint8
id|cdb
(braket
l_int|26
)braket
suffix:semicolon
DECL|member|sense_data
r_uint8
id|sense_data
(braket
l_int|18
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - Continue Target I/O (CTIO) entry structure definition.&n; */
DECL|struct|ctio_entry
r_struct
id|ctio_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|CONTINUE_TGT_IO_TYPE
mdefine_line|#define CONTINUE_TGT_IO_TYPE 7&t;/* CTIO entry */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|reserved_1
r_uint8
id|reserved_1
suffix:semicolon
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|reserved_2
r_uint32
id|reserved_2
suffix:semicolon
DECL|member|lun
r_uint8
id|lun
suffix:semicolon
multiline_comment|/* SCSI LUN */
DECL|member|initiator_id
r_uint8
id|initiator_id
suffix:semicolon
DECL|member|reserved_3
r_uint8
id|reserved_3
suffix:semicolon
DECL|member|target_id
r_uint8
id|target_id
suffix:semicolon
DECL|member|option_flags
r_uint32
id|option_flags
suffix:semicolon
DECL|member|status
r_uint8
id|status
suffix:semicolon
DECL|member|scsi_status
r_uint8
id|scsi_status
suffix:semicolon
DECL|member|tag_value
r_uint8
id|tag_value
suffix:semicolon
multiline_comment|/* Received queue tag message value */
DECL|member|tag_type
r_uint8
id|tag_type
suffix:semicolon
multiline_comment|/* Received queue tag message type */
DECL|member|transfer_length
r_uint32
id|transfer_length
suffix:semicolon
DECL|member|residual
r_uint32
id|residual
suffix:semicolon
DECL|member|timeout
r_uint16
id|timeout
suffix:semicolon
multiline_comment|/* 0 = 30 seconds, 0xFFFF = disable */
DECL|member|dseg_count
r_uint16
id|dseg_count
suffix:semicolon
multiline_comment|/* Data segment count. */
DECL|member|dseg_0_address
r_uint32
id|dseg_0_address
suffix:semicolon
multiline_comment|/* Data segment 0 address. */
DECL|member|dseg_0_length
r_uint32
id|dseg_0_length
suffix:semicolon
multiline_comment|/* Data segment 0 length. */
DECL|member|dseg_1_address
r_uint32
id|dseg_1_address
suffix:semicolon
multiline_comment|/* Data segment 1 address. */
DECL|member|dseg_1_length
r_uint32
id|dseg_1_length
suffix:semicolon
multiline_comment|/* Data segment 1 length. */
DECL|member|dseg_2_address
r_uint32
id|dseg_2_address
suffix:semicolon
multiline_comment|/* Data segment 2 address. */
DECL|member|dseg_2_length
r_uint32
id|dseg_2_length
suffix:semicolon
multiline_comment|/* Data segment 2 length. */
DECL|member|dseg_3_address
r_uint32
id|dseg_3_address
suffix:semicolon
multiline_comment|/* Data segment 3 address. */
DECL|member|dseg_3_length
r_uint32
id|dseg_3_length
suffix:semicolon
multiline_comment|/* Data segment 3 length. */
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - CTIO returned entry structure definition.&n; */
DECL|struct|ctio_ret_entry
r_struct
id|ctio_ret_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|CTIO_RET_TYPE
mdefine_line|#define CTIO_RET_TYPE   7&t;/* CTIO return entry */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|reserved_1
r_uint8
id|reserved_1
suffix:semicolon
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|reserved_2
r_uint32
id|reserved_2
suffix:semicolon
DECL|member|lun
r_uint8
id|lun
suffix:semicolon
multiline_comment|/* SCSI LUN */
DECL|member|initiator_id
r_uint8
id|initiator_id
suffix:semicolon
DECL|member|reserved_3
r_uint8
id|reserved_3
suffix:semicolon
DECL|member|target_id
r_uint8
id|target_id
suffix:semicolon
DECL|member|option_flags
r_uint32
id|option_flags
suffix:semicolon
DECL|member|status
r_uint8
id|status
suffix:semicolon
DECL|member|scsi_status
r_uint8
id|scsi_status
suffix:semicolon
DECL|member|tag_value
r_uint8
id|tag_value
suffix:semicolon
multiline_comment|/* Received queue tag message value */
DECL|member|tag_type
r_uint8
id|tag_type
suffix:semicolon
multiline_comment|/* Received queue tag message type */
DECL|member|transfer_length
r_uint32
id|transfer_length
suffix:semicolon
DECL|member|residual
r_uint32
id|residual
suffix:semicolon
DECL|member|timeout
r_uint16
id|timeout
suffix:semicolon
multiline_comment|/* 0 = 30 seconds, 0xFFFF = disable */
DECL|member|dseg_count
r_uint16
id|dseg_count
suffix:semicolon
multiline_comment|/* Data segment count. */
DECL|member|dseg_0_address
r_uint32
id|dseg_0_address
suffix:semicolon
multiline_comment|/* Data segment 0 address. */
DECL|member|dseg_0_length
r_uint32
id|dseg_0_length
suffix:semicolon
multiline_comment|/* Data segment 0 length. */
DECL|member|dseg_1_address
r_uint32
id|dseg_1_address
suffix:semicolon
multiline_comment|/* Data segment 1 address. */
DECL|member|dseg_1_length
r_uint16
id|dseg_1_length
suffix:semicolon
multiline_comment|/* Data segment 1 length. */
DECL|member|sense_data
r_uint8
id|sense_data
(braket
l_int|18
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - CTIO A64 entry structure definition.&n; */
DECL|struct|ctio_a64_entry
r_struct
id|ctio_a64_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|CTIO_A64_TYPE
mdefine_line|#define CTIO_A64_TYPE 0xF&t;/* CTIO A64 entry */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|reserved_1
r_uint8
id|reserved_1
suffix:semicolon
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|reserved_2
r_uint32
id|reserved_2
suffix:semicolon
DECL|member|lun
r_uint8
id|lun
suffix:semicolon
multiline_comment|/* SCSI LUN */
DECL|member|initiator_id
r_uint8
id|initiator_id
suffix:semicolon
DECL|member|reserved_3
r_uint8
id|reserved_3
suffix:semicolon
DECL|member|target_id
r_uint8
id|target_id
suffix:semicolon
DECL|member|option_flags
r_uint32
id|option_flags
suffix:semicolon
DECL|member|status
r_uint8
id|status
suffix:semicolon
DECL|member|scsi_status
r_uint8
id|scsi_status
suffix:semicolon
DECL|member|tag_value
r_uint8
id|tag_value
suffix:semicolon
multiline_comment|/* Received queue tag message value */
DECL|member|tag_type
r_uint8
id|tag_type
suffix:semicolon
multiline_comment|/* Received queue tag message type */
DECL|member|transfer_length
r_uint32
id|transfer_length
suffix:semicolon
DECL|member|residual
r_uint32
id|residual
suffix:semicolon
DECL|member|timeout
r_uint16
id|timeout
suffix:semicolon
multiline_comment|/* 0 = 30 seconds, 0xFFFF = disable */
DECL|member|dseg_count
r_uint16
id|dseg_count
suffix:semicolon
multiline_comment|/* Data segment count. */
DECL|member|reserved_4
r_uint32
id|reserved_4
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|dseg_0_address
r_uint32
id|dseg_0_address
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Data segment 0 address. */
DECL|member|dseg_0_length
r_uint32
id|dseg_0_length
suffix:semicolon
multiline_comment|/* Data segment 0 length. */
DECL|member|dseg_1_address
r_uint32
id|dseg_1_address
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Data segment 1 address. */
DECL|member|dseg_1_length
r_uint32
id|dseg_1_length
suffix:semicolon
multiline_comment|/* Data segment 1 length. */
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP queue - CTIO returned entry structure definition.&n; */
DECL|struct|ctio_a64_ret_entry
r_struct
id|ctio_a64_ret_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|macro|CTIO_A64_RET_TYPE
mdefine_line|#define CTIO_A64_RET_TYPE 0xF&t;/* CTIO A64 returned entry */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|reserved_1
r_uint8
id|reserved_1
suffix:semicolon
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|reserved_2
r_uint32
id|reserved_2
suffix:semicolon
DECL|member|lun
r_uint8
id|lun
suffix:semicolon
multiline_comment|/* SCSI LUN */
DECL|member|initiator_id
r_uint8
id|initiator_id
suffix:semicolon
DECL|member|reserved_3
r_uint8
id|reserved_3
suffix:semicolon
DECL|member|target_id
r_uint8
id|target_id
suffix:semicolon
DECL|member|option_flags
r_uint32
id|option_flags
suffix:semicolon
DECL|member|status
r_uint8
id|status
suffix:semicolon
DECL|member|scsi_status
r_uint8
id|scsi_status
suffix:semicolon
DECL|member|tag_value
r_uint8
id|tag_value
suffix:semicolon
multiline_comment|/* Received queue tag message value */
DECL|member|tag_type
r_uint8
id|tag_type
suffix:semicolon
multiline_comment|/* Received queue tag message type */
DECL|member|transfer_length
r_uint32
id|transfer_length
suffix:semicolon
DECL|member|residual
r_uint32
id|residual
suffix:semicolon
DECL|member|timeout
r_uint16
id|timeout
suffix:semicolon
multiline_comment|/* 0 = 30 seconds, 0xFFFF = disable */
DECL|member|dseg_count
r_uint16
id|dseg_count
suffix:semicolon
multiline_comment|/* Data segment count. */
DECL|member|reserved_4
r_uint16
id|reserved_4
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|sense_data
r_uint8
id|sense_data
(braket
l_int|18
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP request and response queue entry sizes&n; */
DECL|macro|RESPONSE_ENTRY_SIZE
mdefine_line|#define RESPONSE_ENTRY_SIZE&t;(sizeof(struct response))
DECL|macro|REQUEST_ENTRY_SIZE
mdefine_line|#define REQUEST_ENTRY_SIZE&t;(sizeof(request_t))
multiline_comment|/*&n; * ISP status entry - completion status definitions.&n; */
DECL|macro|CS_COMPLETE
mdefine_line|#define CS_COMPLETE         0x0&t;/* No errors */
DECL|macro|CS_INCOMPLETE
mdefine_line|#define CS_INCOMPLETE       0x1&t;/* Incomplete transfer of cmd. */
DECL|macro|CS_DMA
mdefine_line|#define CS_DMA              0x2&t;/* A DMA direction error. */
DECL|macro|CS_TRANSPORT
mdefine_line|#define CS_TRANSPORT        0x3&t;/* Transport error. */
DECL|macro|CS_RESET
mdefine_line|#define CS_RESET            0x4&t;/* SCSI bus reset occurred */
DECL|macro|CS_ABORTED
mdefine_line|#define CS_ABORTED          0x5&t;/* System aborted command. */
DECL|macro|CS_TIMEOUT
mdefine_line|#define CS_TIMEOUT          0x6&t;/* Timeout error. */
DECL|macro|CS_DATA_OVERRUN
mdefine_line|#define CS_DATA_OVERRUN     0x7&t;/* Data overrun. */
DECL|macro|CS_COMMAND_OVERRUN
mdefine_line|#define CS_COMMAND_OVERRUN  0x8&t;/* Command Overrun. */
DECL|macro|CS_STATUS_OVERRUN
mdefine_line|#define CS_STATUS_OVERRUN   0x9&t;/* Status Overrun. */
DECL|macro|CS_BAD_MSG
mdefine_line|#define CS_BAD_MSG          0xA&t;/* Bad msg after status phase. */
DECL|macro|CS_NO_MSG_OUT
mdefine_line|#define CS_NO_MSG_OUT       0xB&t;/* No msg out after selection. */
DECL|macro|CS_EXTENDED_ID
mdefine_line|#define CS_EXTENDED_ID      0xC&t;/* Extended ID failed. */
DECL|macro|CS_IDE_MSG
mdefine_line|#define CS_IDE_MSG          0xD&t;/* Target rejected IDE msg. */
DECL|macro|CS_ABORT_MSG
mdefine_line|#define CS_ABORT_MSG        0xE&t;/* Target rejected abort msg. */
DECL|macro|CS_REJECT_MSG
mdefine_line|#define CS_REJECT_MSG       0xF&t;/* Target rejected reject msg. */
DECL|macro|CS_NOP_MSG
mdefine_line|#define CS_NOP_MSG          0x10&t;/* Target rejected NOP msg. */
DECL|macro|CS_PARITY_MSG
mdefine_line|#define CS_PARITY_MSG       0x11&t;/* Target rejected parity msg. */
DECL|macro|CS_DEV_RESET_MSG
mdefine_line|#define CS_DEV_RESET_MSG    0x12&t;/* Target rejected dev rst msg. */
DECL|macro|CS_ID_MSG
mdefine_line|#define CS_ID_MSG           0x13&t;/* Target rejected ID msg. */
DECL|macro|CS_FREE
mdefine_line|#define CS_FREE             0x14&t;/* Unexpected bus free. */
DECL|macro|CS_DATA_UNDERRUN
mdefine_line|#define CS_DATA_UNDERRUN    0x15&t;/* Data Underrun. */
DECL|macro|CS_TRANACTION_1
mdefine_line|#define CS_TRANACTION_1     0x18&t;/* Transaction error 1 */
DECL|macro|CS_TRANACTION_2
mdefine_line|#define CS_TRANACTION_2     0x19&t;/* Transaction error 2 */
DECL|macro|CS_TRANACTION_3
mdefine_line|#define CS_TRANACTION_3     0x1a&t;/* Transaction error 3 */
DECL|macro|CS_INV_ENTRY_TYPE
mdefine_line|#define CS_INV_ENTRY_TYPE   0x1b&t;/* Invalid entry type */
DECL|macro|CS_DEV_QUEUE_FULL
mdefine_line|#define CS_DEV_QUEUE_FULL   0x1c&t;/* Device queue full */
DECL|macro|CS_PHASED_SKIPPED
mdefine_line|#define CS_PHASED_SKIPPED   0x1d&t;/* SCSI phase skipped */
DECL|macro|CS_ARS_FAILED
mdefine_line|#define CS_ARS_FAILED       0x1e&t;/* ARS failed */
DECL|macro|CS_LVD_BUS_ERROR
mdefine_line|#define CS_LVD_BUS_ERROR    0x21&t;/* LVD bus error */
DECL|macro|CS_BAD_PAYLOAD
mdefine_line|#define CS_BAD_PAYLOAD      0x80&t;/* Driver defined */
DECL|macro|CS_UNKNOWN
mdefine_line|#define CS_UNKNOWN          0x81&t;/* Driver defined */
DECL|macro|CS_RETRY
mdefine_line|#define CS_RETRY            0x82&t;/* Driver defined */
multiline_comment|/*&n; * ISP status entry - SCSI status byte bit definitions.&n; */
DECL|macro|SS_CHECK_CONDITION
mdefine_line|#define SS_CHECK_CONDITION  BIT_1
DECL|macro|SS_CONDITION_MET
mdefine_line|#define SS_CONDITION_MET    BIT_2
DECL|macro|SS_BUSY_CONDITION
mdefine_line|#define SS_BUSY_CONDITION   BIT_3
DECL|macro|SS_RESERVE_CONFLICT
mdefine_line|#define SS_RESERVE_CONFLICT (BIT_4 | BIT_3)
multiline_comment|/*&n; * ISP target entries - Option flags bit definitions.&n; */
DECL|macro|OF_ENABLE_TAG
mdefine_line|#define OF_ENABLE_TAG       BIT_1&t;/* Tagged queue action enable */
DECL|macro|OF_DATA_IN
mdefine_line|#define OF_DATA_IN          BIT_6&t;/* Data in to initiator */
multiline_comment|/*  (data from target to initiator) */
DECL|macro|OF_DATA_OUT
mdefine_line|#define OF_DATA_OUT         BIT_7&t;/* Data out from initiator */
multiline_comment|/*  (data from initiator to target) */
DECL|macro|OF_NO_DATA
mdefine_line|#define OF_NO_DATA          (BIT_7 | BIT_6)
DECL|macro|OF_DISC_DISABLED
mdefine_line|#define OF_DISC_DISABLED    BIT_15&t;/* Disconnects disabled */
DECL|macro|OF_DISABLE_SDP
mdefine_line|#define OF_DISABLE_SDP      BIT_24&t;/* Disable sending save data ptr */
DECL|macro|OF_SEND_RDP
mdefine_line|#define OF_SEND_RDP         BIT_26&t;/* Send restore data pointers msg */
DECL|macro|OF_FORCE_DISC
mdefine_line|#define OF_FORCE_DISC       BIT_30&t;/* Disconnects mandatory */
DECL|macro|OF_SSTS
mdefine_line|#define OF_SSTS             BIT_31&t;/* Send SCSI status */
multiline_comment|/*&n; * BUS parameters/settings structure - UNUSED&n; */
DECL|struct|bus_param
r_struct
id|bus_param
(brace
DECL|member|id
r_uint8
id|id
suffix:semicolon
multiline_comment|/* Host adapter SCSI id */
DECL|member|bus_reset_delay
r_uint8
id|bus_reset_delay
suffix:semicolon
multiline_comment|/* SCSI bus reset delay. */
DECL|member|failed_reset_count
r_uint8
id|failed_reset_count
suffix:semicolon
multiline_comment|/* number of time reset failed */
DECL|member|unused
r_uint8
id|unused
suffix:semicolon
DECL|member|device_enables
r_uint16
id|device_enables
suffix:semicolon
multiline_comment|/* Device enable bits. */
DECL|member|lun_disables
r_uint16
id|lun_disables
suffix:semicolon
multiline_comment|/* LUN disable bits. */
DECL|member|qtag_enables
r_uint16
id|qtag_enables
suffix:semicolon
multiline_comment|/* Tag queue enables. */
DECL|member|hiwat
r_uint16
id|hiwat
suffix:semicolon
multiline_comment|/* High water mark per device. */
DECL|member|reset_marker
r_uint8
id|reset_marker
suffix:colon
l_int|1
suffix:semicolon
DECL|member|disable_scsi_reset
r_uint8
id|disable_scsi_reset
suffix:colon
l_int|1
suffix:semicolon
DECL|member|scsi_bus_dead
r_uint8
id|scsi_bus_dead
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* SCSI Bus is Dead, when 5 back to back resets failed */
)brace
suffix:semicolon
DECL|struct|qla_driver_setup
r_struct
id|qla_driver_setup
(brace
DECL|member|no_sync
r_uint32
id|no_sync
suffix:colon
l_int|1
suffix:semicolon
DECL|member|no_wide
r_uint32
id|no_wide
suffix:colon
l_int|1
suffix:semicolon
DECL|member|no_ppr
r_uint32
id|no_ppr
suffix:colon
l_int|1
suffix:semicolon
DECL|member|no_nvram
r_uint32
id|no_nvram
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sync_mask
r_uint16
id|sync_mask
suffix:semicolon
DECL|member|wide_mask
r_uint16
id|wide_mask
suffix:semicolon
DECL|member|ppr_mask
r_uint16
id|ppr_mask
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Linux Host Adapter structure&n; */
DECL|struct|scsi_qla_host
r_struct
id|scsi_qla_host
(brace
multiline_comment|/* Linux adapter configuration data */
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
multiline_comment|/* pointer to host data */
DECL|member|next
r_struct
id|scsi_qla_host
op_star
id|next
suffix:semicolon
DECL|member|iobase
r_struct
id|device_reg
op_star
id|iobase
suffix:semicolon
multiline_comment|/* Base Memory-mapped I/O address */
DECL|member|mmpbase
r_int
r_char
op_star
id|mmpbase
suffix:semicolon
multiline_comment|/* memory mapped address */
DECL|member|host_no
r_int
r_int
id|host_no
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|devnum
r_uint8
id|devnum
suffix:semicolon
DECL|member|revision
r_uint8
id|revision
suffix:semicolon
DECL|member|ports
r_uint8
id|ports
suffix:semicolon
DECL|member|actthreads
r_int
r_int
id|actthreads
suffix:semicolon
DECL|member|isr_count
r_int
r_int
id|isr_count
suffix:semicolon
multiline_comment|/* Interrupt count */
DECL|member|spurious_int
r_int
r_int
id|spurious_int
suffix:semicolon
multiline_comment|/* Outstandings ISP commands. */
DECL|member|outstanding_cmds
r_struct
id|srb
op_star
id|outstanding_cmds
(braket
id|MAX_OUTSTANDING_COMMANDS
)braket
suffix:semicolon
multiline_comment|/* BUS configuration data */
DECL|member|bus_settings
r_struct
id|bus_param
id|bus_settings
(braket
id|MAX_BUSES
)braket
suffix:semicolon
multiline_comment|/* Received ISP mailbox data. */
DECL|member|mailbox_out
r_volatile
r_uint16
id|mailbox_out
(braket
id|MAILBOX_REGISTER_COUNT
)braket
suffix:semicolon
DECL|member|request_dma
id|dma_addr_t
id|request_dma
suffix:semicolon
multiline_comment|/* Physical Address */
DECL|member|request_ring
id|request_t
op_star
id|request_ring
suffix:semicolon
multiline_comment|/* Base virtual address */
DECL|member|request_ring_ptr
id|request_t
op_star
id|request_ring_ptr
suffix:semicolon
multiline_comment|/* Current address. */
DECL|member|req_ring_index
r_uint16
id|req_ring_index
suffix:semicolon
multiline_comment|/* Current index. */
DECL|member|req_q_cnt
r_uint16
id|req_q_cnt
suffix:semicolon
multiline_comment|/* Number of available entries. */
DECL|member|response_dma
id|dma_addr_t
id|response_dma
suffix:semicolon
multiline_comment|/* Physical address. */
DECL|member|response_ring
r_struct
id|response
op_star
id|response_ring
suffix:semicolon
multiline_comment|/* Base virtual address */
DECL|member|response_ring_ptr
r_struct
id|response
op_star
id|response_ring_ptr
suffix:semicolon
multiline_comment|/* Current address. */
DECL|member|rsp_ring_index
r_uint16
id|rsp_ring_index
suffix:semicolon
multiline_comment|/* Current index. */
DECL|member|done_q
r_struct
id|list_head
id|done_q
suffix:semicolon
multiline_comment|/* Done queue */
DECL|member|mailbox_wait
r_struct
id|completion
op_star
id|mailbox_wait
suffix:semicolon
r_volatile
r_struct
(brace
DECL|member|online
r_uint32
id|online
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|reset_marker
r_uint32
id|reset_marker
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|disable_host_adapter
r_uint32
id|disable_host_adapter
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 2 */
DECL|member|reset_active
r_uint32
id|reset_active
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 3 */
DECL|member|abort_isp_active
r_uint32
id|abort_isp_active
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 4 */
DECL|member|disable_risc_code_load
r_uint32
id|disable_risc_code_load
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 5 */
DECL|member|enable_64bit_addressing
r_uint32
id|enable_64bit_addressing
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 6 */
DECL|member|in_reset
r_uint32
id|in_reset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 7 */
DECL|member|ints_enabled
r_uint32
id|ints_enabled
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ignore_nvram
r_uint32
id|ignore_nvram
suffix:colon
l_int|1
suffix:semicolon
macro_line|#ifdef __ia64__
DECL|member|use_pci_vchannel
r_uint32
id|use_pci_vchannel
suffix:colon
l_int|1
suffix:semicolon
macro_line|#endif
DECL|member|flags
)brace
id|flags
suffix:semicolon
DECL|member|nvram
r_struct
id|nvram
id|nvram
suffix:semicolon
DECL|member|nvram_valid
r_int
id|nvram_valid
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _QLA1280_H */
eof
