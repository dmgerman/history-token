multiline_comment|/******************************************************************************&n;*                  QLOGIC LINUX SOFTWARE&n;*&n;* QLogic ISP1280 (Ultra2) /12160 (Ultra3) SCSI driver&n;* Copyright (C) 2000 Qlogic Corporation&n;* (www.qlogic.com)&n;*&n;* This program is free software; you can redistribute it and/or modify it&n;* under the terms of the GNU General Public License as published by the&n;* Free Software Foundation; either version 2, or (at your option) any&n;* later version.&n;*&n;* This program is distributed in the hope that it will be useful, but&n;* WITHOUT ANY WARRANTY; without even the implied warranty of&n;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;* General Public License for more details.&n;*&n;******************************************************************************/
macro_line|#ifndef&t;_IO_HBA_QLA1280_H&t;/* wrapper symbol for kernel use */
DECL|macro|_IO_HBA_QLA1280_H
mdefine_line|#define&t;_IO_HBA_QLA1280_H&t;/* subject to change without notice */
macro_line|#ifndef HOSTS_C&t;&t;&t;/* included in hosts.c */
multiline_comment|/*&n; * Enable define statement to ignore Data Underrun Errors,&n; * remove define statement to enable detection.&n; */
multiline_comment|/* #define  DATA_UNDERRUN_ERROR_DISABLE */
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
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
multiline_comment|/*&n; *  Local Macro Definitions.&n; */
macro_line|#if defined(QL_DEBUG_LEVEL_1) || defined(QL_DEBUG_LEVEL_2) || &bslash;&n;    defined(QL_DEBUG_LEVEL_3) || defined(QL_DEBUG_LEVEL_4) || &bslash;&n;    defined(QL_DEBUG_LEVEL_5) || defined(QL_DEBUG_LEVEL_6) || &bslash;&n;    defined(QL_DEBUG_LEVEL_7)
DECL|macro|QL_DEBUG_ROUTINES
mdefine_line|#define QL_DEBUG_ROUTINES
macro_line|#endif
multiline_comment|/*&n; * I/O port macros&n;*/
multiline_comment|/* #define MEMORY_MAPPED_IO */
multiline_comment|/* Enable memory mapped I/O */
DECL|macro|MEMORY_MAPPED_IO
macro_line|#undef MEMORY_MAPPED_IO&t;&t;/* Disable memory mapped I/O */
macro_line|#ifdef QL_DEBUG_LEVEL_1
DECL|macro|RD_REG_BYTE
mdefine_line|#define RD_REG_BYTE(addr)&t;&t;qla1280_getbyte((u8 *)addr)
DECL|macro|RD_REG_WORD
mdefine_line|#define RD_REG_WORD(addr)&t;&t;qla1280_getword((u16 *)addr)
DECL|macro|RD_REG_DWORD
mdefine_line|#define RD_REG_DWORD(addr)&t;&t;qla1280_getdword((u32 *)addr)
DECL|macro|WRT_REG_BYTE
mdefine_line|#define WRT_REG_BYTE(addr, data)&t;qla1280_putbyte((u8 *)addr, data)
DECL|macro|WRT_REG_WORD
mdefine_line|#define WRT_REG_WORD(addr, data)&t;qla1280_putword((u16 *)addr, data)
DECL|macro|WRT_REG_DWORD
mdefine_line|#define WRT_REG_DWORD(addr, data)&t;qla1280_putdword((u32 *)addr, data)
macro_line|#else&t;&t;&t;&t;/* QL_DEBUG_LEVEL_1 */
macro_line|#ifdef MEMORY_MAPPED_IO
DECL|macro|RD_REG_BYTE
mdefine_line|#define RD_REG_BYTE(addr)&t;&t;readb(addr)
DECL|macro|RD_REG_WORD
mdefine_line|#define RD_REG_WORD(addr)&t;&t;readw(addr)
DECL|macro|RD_REG_DWORD
mdefine_line|#define RD_REG_DWORD(addr)&t;&t;readl(addr)
DECL|macro|WRT_REG_BYTE
mdefine_line|#define WRT_REG_BYTE(addr, data)&t;writeb(data, addr)
DECL|macro|WRT_REG_WORD
mdefine_line|#define WRT_REG_WORD(addr, data)&t;writew(data, addr)
DECL|macro|WRT_REG_DWORD
mdefine_line|#define WRT_REG_DWORD(addr, data)&t;writel(data, addr)
macro_line|#else&t;&t;&t;&t;/* MEMORY_MAPPED_IO */
DECL|macro|RD_REG_BYTE
mdefine_line|#define RD_REG_BYTE(addr)&t;&t;inb((unsigned long)addr)
DECL|macro|RD_REG_WORD
mdefine_line|#define RD_REG_WORD(addr)&t;&t;inw((unsigned long)addr)
DECL|macro|RD_REG_DWORD
mdefine_line|#define RD_REG_DWORD(addr)&t;&t;inl((unsigned long)addr)
multiline_comment|/* Parameters are reversed in Linux */
DECL|macro|WRT_REG_BYTE
mdefine_line|#define WRT_REG_BYTE(addr, data)&t;outb(data, (unsigned long)addr)
DECL|macro|WRT_REG_WORD
mdefine_line|#define WRT_REG_WORD(addr, data)&t;outw(data, (unsigned long)addr)
DECL|macro|WRT_REG_DWORD
mdefine_line|#define WRT_REG_DWORD(addr, data)&t;outl(data, (unsigned long)addr)
macro_line|#endif&t;&t;&t;&t;/* MEMORY_MAPPED_IO */
macro_line|#endif&t;&t;&t;&t;/* QL_DEBUG_LEVEL_1 */
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
multiline_comment|/* Maximum outstanding commands in ISP queues (1-65535) */
DECL|macro|MAX_OUTSTANDING_COMMANDS
mdefine_line|#define MAX_OUTSTANDING_COMMANDS&t;512
multiline_comment|/* ISP request and response entry counts (37-65535) */
DECL|macro|REQUEST_ENTRY_CNT
mdefine_line|#define REQUEST_ENTRY_CNT&t;&t;256 /* Number of request entries. */
DECL|macro|RESPONSE_ENTRY_CNT
mdefine_line|#define RESPONSE_ENTRY_CNT&t;&t;16  /* Number of response entries. */
multiline_comment|/* Maximum equipage per controller */
DECL|macro|MAX_EQ
mdefine_line|#define MAX_EQ&t;&t;&t;&t;(MAX_BUSES * MAX_TARGETS * MAX_LUNS)
multiline_comment|/* Number of segments 1 - 65535 */
DECL|macro|SG_SEGMENTS
mdefine_line|#define SG_SEGMENTS&t;&t;&t;32  /* Cmd entry + 6 continuations */
multiline_comment|/*&n; * SCSI Request Block structure  (sp)  that is placed&n; * on cmd-&gt;SCp location of every I/O&n; */
DECL|struct|srb
r_typedef
r_struct
id|srb
(brace
DECL|member|cmd
id|Scsi_Cmnd
op_star
id|cmd
suffix:semicolon
multiline_comment|/* (4/8) SCSI command block */
DECL|member|s_next
r_struct
id|srb
op_star
id|s_next
suffix:semicolon
multiline_comment|/* (4/8) Next block on LU queue */
DECL|member|s_prev
r_struct
id|srb
op_star
id|s_prev
suffix:semicolon
multiline_comment|/* (4/8) Previous block on LU queue */
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
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,18)
DECL|member|saved_dma_handle
id|dma_addr_t
id|saved_dma_handle
suffix:semicolon
multiline_comment|/* for unmap of single transfers */
macro_line|#endif
DECL|typedef|srb_t
)brace
id|srb_t
suffix:semicolon
multiline_comment|/*&n; * SRB flag definitions&n; */
DECL|macro|SRB_TIMEOUT
mdefine_line|#define SRB_TIMEOUT&t;&t;BIT_0&t;/* Command timed out */
DECL|macro|SRB_SENT
mdefine_line|#define SRB_SENT&t;&t;BIT_1&t;/* Command sent to ISP */
DECL|macro|SRB_ABORT_PENDING
mdefine_line|#define SRB_ABORT_PENDING&t;BIT_2&t;/* Command abort sent to device */
DECL|macro|SRB_ABORTED
mdefine_line|#define SRB_ABORTED&t;&t;BIT_3&t;/* Command aborted command already */
multiline_comment|/*&n; * Logical Unit Queue structure&n; */
DECL|struct|scsi_lu
r_typedef
r_struct
id|scsi_lu
(brace
DECL|member|q_first
id|srb_t
op_star
id|q_first
suffix:semicolon
multiline_comment|/* First block on LU queue */
DECL|member|q_last
id|srb_t
op_star
id|q_last
suffix:semicolon
multiline_comment|/* Last block on LU queue */
DECL|member|q_flag
r_uint8
id|q_flag
suffix:semicolon
multiline_comment|/* LU queue state flags */
DECL|member|q_sense
r_uint8
id|q_sense
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* sense data */
DECL|member|io_cnt
r_int
r_int
id|io_cnt
suffix:semicolon
multiline_comment|/* total xfer count */
DECL|member|resp_time
r_int
r_int
id|resp_time
suffix:semicolon
multiline_comment|/* total response time (start - finish) */
DECL|member|act_time
r_int
r_int
id|act_time
suffix:semicolon
multiline_comment|/* total actived time (minus queuing time) */
DECL|member|w_cnt
r_int
r_int
id|w_cnt
suffix:semicolon
multiline_comment|/* total writes */
DECL|member|r_cnt
r_int
r_int
id|r_cnt
suffix:semicolon
multiline_comment|/* total reads */
DECL|member|q_outcnt
r_uint16
id|q_outcnt
suffix:semicolon
multiline_comment|/* Pending jobs for this LU */
macro_line|#if QL1280_TARGET_MODE_SUPPORT
DECL|member|q_func
r_void
(paren
op_star
id|q_func
)paren
(paren
)paren
suffix:semicolon
multiline_comment|/* Target driver event handler */
DECL|member|q_param
r_int32
id|q_param
suffix:semicolon
multiline_comment|/* Target driver event param */
DECL|member|q_lock
r_uint8
id|q_lock
suffix:semicolon
multiline_comment|/* Device Queue Lock */
macro_line|#endif
DECL|typedef|scsi_lu_t
)brace
id|scsi_lu_t
suffix:semicolon
multiline_comment|/*&n; * Logical Unit flags&n; */
DECL|macro|QLA1280_QBUSY
mdefine_line|#define QLA1280_QBUSY&t;BIT_0
DECL|macro|QLA1280_QWAIT
mdefine_line|#define QLA1280_QWAIT&t;BIT_1
DECL|macro|QLA1280_QSUSP
mdefine_line|#define QLA1280_QSUSP&t;BIT_2
DECL|macro|QLA1280_QSENSE
mdefine_line|#define QLA1280_QSENSE&t;BIT_3&t;/* Sense data cache valid */
DECL|macro|QLA1280_QRESET
mdefine_line|#define QLA1280_QRESET&t;BIT_4
DECL|macro|QLA1280_QHBA
mdefine_line|#define QLA1280_QHBA&t;BIT_5
DECL|macro|QLA1280_BSUSP
mdefine_line|#define QLA1280_BSUSP&t;BIT_6&t;/* controller is suspended */
DECL|macro|QLA1280_BREM
mdefine_line|#define QLA1280_BREM&t;BIT_7&t;/* controller is removed */
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
DECL|member|cfg_1
r_uint16
id|cfg_1
suffix:semicolon
multiline_comment|/* Configuration 1 */
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
l_int|0x2e
)braket
suffix:semicolon
multiline_comment|/* 0x14-0x6f Gap */
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
DECL|member|unused_2
r_uint16
id|unused_2
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
DECL|member|unused_6
r_uint16
id|unused_6
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
DECL|member|unused_7
r_uint16
id|unused_7
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
mdefine_line|#define MBC_NOP                     0&t;/* No Operation. */
DECL|macro|MBC_LOAD_RAM
mdefine_line|#define MBC_LOAD_RAM                1&t;/* Load RAM. */
DECL|macro|MBC_EXECUTE_FIRMWARE
mdefine_line|#define MBC_EXECUTE_FIRMWARE        2&t;/* Execute firmware. */
DECL|macro|MBC_WRITE_RAM_WORD
mdefine_line|#define MBC_WRITE_RAM_WORD          4&t;/* Write ram word. */
DECL|macro|MBC_READ_RAM_WORD
mdefine_line|#define MBC_READ_RAM_WORD           5&t;/* Read ram word. */
DECL|macro|MBC_MAILBOX_REGISTER_TEST
mdefine_line|#define MBC_MAILBOX_REGISTER_TEST   6&t;/* Wrap incoming mailboxes */
DECL|macro|MBC_VERIFY_CHECKSUM
mdefine_line|#define MBC_VERIFY_CHECKSUM         7&t;/* Verify checksum. */
DECL|macro|MBC_ABOUT_FIRMWARE
mdefine_line|#define MBC_ABOUT_FIRMWARE          8&t;/* Get firmware revision. */
DECL|macro|MBC_INIT_REQUEST_QUEUE
mdefine_line|#define MBC_INIT_REQUEST_QUEUE      0x10&t;/* Initialize request queue. */
DECL|macro|MBC_INIT_RESPONSE_QUEUE
mdefine_line|#define MBC_INIT_RESPONSE_QUEUE     0x11&t;/* Initialize response queue. */
DECL|macro|MBC_EXECUTE_IOCB
mdefine_line|#define MBC_EXECUTE_IOCB            0x12&t;/* Execute IOCB command. */
DECL|macro|MBC_ABORT_COMMAND
mdefine_line|#define MBC_ABORT_COMMAND           0x15&t;/* Abort IOCB command. */
DECL|macro|MBC_ABORT_DEVICE
mdefine_line|#define MBC_ABORT_DEVICE            0x16&t;/* Abort device (ID/LUN). */
DECL|macro|MBC_ABORT_TARGET
mdefine_line|#define MBC_ABORT_TARGET            0x17&t;/* Abort target (ID). */
DECL|macro|MBC_BUS_RESET
mdefine_line|#define MBC_BUS_RESET               0x18&t;/* SCSI bus reset. */
DECL|macro|MBC_GET_RETRY_COUNT
mdefine_line|#define MBC_GET_RETRY_COUNT         0x22&t;/* Get retry count and delay. */
DECL|macro|MBC_GET_TARGET_PARAMETERS
mdefine_line|#define MBC_GET_TARGET_PARAMETERS   0x28&t;/* Get target parameters. */
DECL|macro|MBC_SET_INITIATOR_ID
mdefine_line|#define MBC_SET_INITIATOR_ID        0x30&t;/* Set initiator SCSI ID. */
DECL|macro|MBC_SET_SELECTION_TIMEOUT
mdefine_line|#define MBC_SET_SELECTION_TIMEOUT   0x31&t;/* Set selection timeout. */
DECL|macro|MBC_SET_RETRY_COUNT
mdefine_line|#define MBC_SET_RETRY_COUNT         0x32&t;/* Set retry count and delay. */
DECL|macro|MBC_SET_TAG_AGE_LIMIT
mdefine_line|#define MBC_SET_TAG_AGE_LIMIT       0x33&t;/* Set tag age limit. */
DECL|macro|MBC_SET_CLOCK_RATE
mdefine_line|#define MBC_SET_CLOCK_RATE          0x34&t;/* Set clock rate. */
DECL|macro|MBC_SET_ACTIVE_NEGATION
mdefine_line|#define MBC_SET_ACTIVE_NEGATION     0x35&t;/* Set active negation state. */
DECL|macro|MBC_SET_ASYNC_DATA_SETUP
mdefine_line|#define MBC_SET_ASYNC_DATA_SETUP    0x36&t;/* Set async data setup time. */
DECL|macro|MBC_SET_PCI_CONTROL
mdefine_line|#define MBC_SET_PCI_CONTROL         0x37&t;/* Set BUS control parameters. */
DECL|macro|MBC_SET_TARGET_PARAMETERS
mdefine_line|#define MBC_SET_TARGET_PARAMETERS   0x38&t;/* Set target parameters. */
DECL|macro|MBC_SET_DEVICE_QUEUE
mdefine_line|#define MBC_SET_DEVICE_QUEUE        0x39&t;/* Set device queue parameters */
DECL|macro|MBC_SET_SYSTEM_PARAMETER
mdefine_line|#define MBC_SET_SYSTEM_PARAMETER    0x45&t;/* Set system parameter word. */
DECL|macro|MBC_SET_FIRMWARE_FEATURES
mdefine_line|#define MBC_SET_FIRMWARE_FEATURES   0x4A&t;/* Set firmware feature word. */
DECL|macro|MBC_INIT_REQUEST_QUEUE_A64
mdefine_line|#define MBC_INIT_REQUEST_QUEUE_A64  0x52&t;/* Initialize request queue A64 */
DECL|macro|MBC_INIT_RESPONSE_QUEUE_A64
mdefine_line|#define MBC_INIT_RESPONSE_QUEUE_A64 0x53&t;/* Initialize response q A64. */
DECL|macro|MBC_ENABLE_TARGET_MODE
mdefine_line|#define MBC_ENABLE_TARGET_MODE      0x55&t;/* Enable target mode. */
multiline_comment|/*&n; * ISP Get/Set Target Parameters mailbox command control flags.&n; */
DECL|macro|TP_RENEGOTIATE
mdefine_line|#define TP_RENEGOTIATE          BIT_8&t;/* Renegotiate on error. */
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
multiline_comment|/*&n; *  QLogic ISP1280 NVRAM structure definition.&n; */
r_typedef
r_struct
(brace
DECL|member|id
r_uint8
id|id
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0, 1, 2, 3 */
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
DECL|member|cntr_flags_2
)brace
id|cntr_flags_2
suffix:semicolon
multiline_comment|/* 6, 7 */
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
r_uint8
id|enable_fast_posting
suffix:colon
l_int|1
suffix:semicolon
DECL|member|report_lvd_bus_transition
r_uint8
id|report_lvd_bus_transition
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_2
r_uint8
id|unused_2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_3
r_uint8
id|unused_3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_4
r_uint8
id|unused_4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_5
r_uint8
id|unused_5
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
DECL|member|unused_8
r_uint8
id|unused_8
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_9
r_uint8
id|unused_9
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_10
r_uint8
id|unused_10
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_11
r_uint8
id|unused_11
suffix:colon
l_int|1
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
DECL|member|sync_data_transfers
r_uint8
id|sync_data_transfers
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wide_data_transfers
r_uint8
id|wide_data_transfers
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
DECL|member|flags
)brace
id|flags
suffix:semicolon
multiline_comment|/* 43 */
DECL|member|unused_44
r_uint16
id|unused_44
suffix:semicolon
multiline_comment|/* 44, 45 */
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
DECL|member|unused_254
r_uint8
id|unused_254
suffix:semicolon
multiline_comment|/* 254 */
DECL|member|chksum
r_uint8
id|chksum
suffix:semicolon
multiline_comment|/* 255 */
DECL|typedef|nvram_t
)brace
id|nvram_t
suffix:semicolon
multiline_comment|/*&n; *  QLogic ISP12160 NVRAM structure definition.&n; */
r_typedef
r_struct
(brace
DECL|member|id
r_uint8
id|id
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0, 1, 2, 3 */
DECL|member|version
r_uint8
id|version
suffix:semicolon
multiline_comment|/* 4 */
multiline_comment|/* Host/Bios Flags */
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
DECL|member|cntr_flags_1
)brace
id|cntr_flags_1
suffix:semicolon
multiline_comment|/* 5 */
multiline_comment|/* Selectable Boot Support */
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
DECL|member|cntr_flags_2
)brace
id|cntr_flags_2
suffix:semicolon
multiline_comment|/* 6, 7 */
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
multiline_comment|/* ISP Config Parameters */
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
multiline_comment|/* Auto Term - 3                          */
multiline_comment|/* High Only - 1 (GPIO2 = 1 &amp; GPIO3 = 0)  */
multiline_comment|/* Disable - 0 (GPIO2 = 0 &amp; GPIO3 = X)    */
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
r_uint8
id|enable_fast_posting
suffix:colon
l_int|1
suffix:semicolon
DECL|member|report_lvd_bus_transition
r_uint8
id|report_lvd_bus_transition
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_2
r_uint8
id|unused_2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_3
r_uint8
id|unused_3
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_4
r_uint8
id|unused_4
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_5
r_uint8
id|unused_5
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
DECL|member|unused_8
r_uint8
id|unused_8
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_9
r_uint8
id|unused_9
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_10
r_uint8
id|unused_10
suffix:colon
l_int|1
suffix:semicolon
DECL|member|unused_11
r_uint8
id|unused_11
suffix:colon
l_int|1
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
multiline_comment|/* Adapter Capabilities bits */
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
DECL|member|sync_data_transfers
r_uint8
id|sync_data_transfers
suffix:colon
l_int|1
suffix:semicolon
DECL|member|wide_data_transfers
r_uint8
id|wide_data_transfers
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
multiline_comment|/* 43, 44 */
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
DECL|member|System_Id_Pointer
r_uint8
id|System_Id_Pointer
suffix:semicolon
multiline_comment|/* 254 */
DECL|member|chksum
r_uint8
id|chksum
suffix:semicolon
multiline_comment|/* 255 */
DECL|typedef|nvram160_t
)brace
id|nvram160_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - command entry structure definition.&n; */
DECL|macro|MAX_CMDSZ
mdefine_line|#define MAX_CMDSZ&t;12&t;&t;/* SCSI maximum CDB size. */
r_typedef
r_struct
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
DECL|typedef|cmd_entry_t
)brace
id|cmd_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - continuation entry structure definition.&n; */
r_typedef
r_struct
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
DECL|typedef|cont_entry_t
)brace
id|cont_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - status entry structure definition.&n; */
r_typedef
r_struct
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
DECL|typedef|sts_entry_t
DECL|typedef|response_t
)brace
id|sts_entry_t
comma
id|response_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - marker entry structure definition.&n; */
r_typedef
r_struct
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
DECL|typedef|mrk_entry_t
)brace
id|mrk_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - extended command entry structure definition.&n; */
r_typedef
r_struct
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
DECL|typedef|ecmd_entry_t
)brace
id|ecmd_entry_t
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
r_typedef
r_struct
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
DECL|typedef|cont_a64_entry_t
)brace
id|cont_a64_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - enable LUN entry structure definition.&n; */
r_typedef
r_struct
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
DECL|typedef|elun_entry_t
)brace
id|elun_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - modify LUN entry structure definition.&n; */
r_typedef
r_struct
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
DECL|typedef|modify_lun_entry_t
)brace
id|modify_lun_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - immediate notify entry structure definition.&n; */
r_typedef
r_struct
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
DECL|typedef|notify_entry_t
)brace
id|notify_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - notify acknowledge entry structure definition.&n; */
r_typedef
r_struct
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
DECL|typedef|nack_entry_t
)brace
id|nack_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - Accept Target I/O (ATIO) entry structure definition.&n; */
r_typedef
r_struct
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
DECL|typedef|atio_entry_t
)brace
id|atio_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - Continue Target I/O (CTIO) entry structure definition.&n; */
r_typedef
r_struct
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
DECL|typedef|ctio_entry_t
)brace
id|ctio_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - CTIO returned entry structure definition.&n; */
r_typedef
r_struct
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
DECL|typedef|ctio_ret_entry_t
)brace
id|ctio_ret_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - CTIO A64 entry structure definition.&n; */
r_typedef
r_struct
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
DECL|typedef|ctio_a64_entry_t
)brace
id|ctio_a64_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - CTIO returned entry structure definition.&n; */
r_typedef
r_struct
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
DECL|typedef|ctio_a64_ret_entry_t
)brace
id|ctio_a64_ret_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP request and response queue entry sizes&n; */
DECL|macro|RESPONSE_ENTRY_SIZE
mdefine_line|#define RESPONSE_ENTRY_SIZE&t;(sizeof(response_t))
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
macro_line|#if QL1280_TARGET_MODE_SUPPORT
multiline_comment|/*&n; * Target Read/Write buffer structure.&n; */
DECL|macro|TARGET_DATA_OFFSET
mdefine_line|#define TARGET_DATA_OFFSET&t;4
DECL|macro|TARGET_DATA_SIZE
mdefine_line|#define TARGET_DATA_SIZE&t;0x2000&t;/* 8K */
DECL|macro|TARGET_INQ_OFFSET
mdefine_line|#define TARGET_INQ_OFFSET&t;(TARGET_DATA_OFFSET + TARGET_DATA_SIZE)
DECL|macro|TARGET_SENSE_SIZE
mdefine_line|#define TARGET_SENSE_SIZE&t;18
DECL|macro|TARGET_BUF_SIZE
mdefine_line|#define TARGET_BUF_SIZE&t;&t;36
r_typedef
r_struct
(brace
DECL|member|hdr
r_uint8
id|hdr
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|data
r_uint8
id|data
(braket
id|TARGET_DATA_SIZE
)braket
suffix:semicolon
DECL|member|inq
r_struct
id|ident
id|inq
suffix:semicolon
DECL|typedef|tgt_t
)brace
id|tgt_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * BUS parameters/settings structure&n; */
r_typedef
r_struct
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
DECL|typedef|bus_param_t
)brace
id|bus_param_t
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
DECL|member|pci_bus
r_uint8
id|pci_bus
suffix:semicolon
DECL|member|pci_device_fn
r_uint8
id|pci_device_fn
suffix:semicolon
DECL|member|devnum
r_uint8
id|devnum
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|mmpbase
r_volatile
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
DECL|member|instance
r_int
r_int
id|instance
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
DECL|member|qthreads
r_int
r_int
id|qthreads
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
DECL|member|device_id
r_uint32
id|device_id
suffix:semicolon
multiline_comment|/* Outstandings ISP commands. */
DECL|member|outstanding_cmds
id|srb_t
op_star
id|outstanding_cmds
(braket
id|MAX_OUTSTANDING_COMMANDS
)braket
suffix:semicolon
multiline_comment|/* BUS configuration data */
DECL|member|bus_settings
id|bus_param_t
id|bus_settings
(braket
id|MAX_BUSES
)braket
suffix:semicolon
multiline_comment|/* Device LUN queues. */
DECL|member|dev
r_struct
id|scsi_lu
op_star
id|dev
(braket
id|MAX_EQ
)braket
suffix:semicolon
multiline_comment|/* Logical unit queues */
multiline_comment|/* bottom half run queue */
DECL|member|run_qla_bh
r_struct
id|tq_struct
id|run_qla_bh
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
macro_line|#ifdef UNUSED
DECL|member|dev_timer
r_struct
id|timer_list
id|dev_timer
(braket
id|MAX_TARGETS
)braket
suffix:semicolon
macro_line|#endif
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
id|response_t
op_star
id|response_ring
suffix:semicolon
multiline_comment|/* Base virtual address */
DECL|member|response_ring_ptr
id|response_t
op_star
id|response_ring_ptr
suffix:semicolon
multiline_comment|/* Current address. */
DECL|member|rsp_ring_index
r_uint16
id|rsp_ring_index
suffix:semicolon
multiline_comment|/* Current index. */
macro_line|#if QL1280_TARGET_MODE_SUPPORT
multiline_comment|/* Target buffer and sense data. */
DECL|member|tbuf_dma
id|dma_addr_t
id|tbuf_dma
suffix:semicolon
multiline_comment|/* Physical address. */
DECL|member|tsense_dma
id|dma_addr_t
id|tsense_dma
suffix:semicolon
multiline_comment|/* Physical address. */
DECL|member|tbuf
id|tgt_t
op_star
id|tbuf
suffix:semicolon
DECL|member|tsense
r_uint8
op_star
id|tsense
suffix:semicolon
macro_line|#endif
macro_line|#if WATCHDOGTIMER
multiline_comment|/* Watchdog queue, lock and total timer */
DECL|member|watchdog_q_lock
r_uint8
id|watchdog_q_lock
suffix:semicolon
multiline_comment|/* Lock for watchdog queue */
DECL|member|wdg_q_first
id|srb_t
op_star
id|wdg_q_first
suffix:semicolon
multiline_comment|/* First job on watchdog queue */
DECL|member|wdg_q_last
id|srb_t
op_star
id|wdg_q_last
suffix:semicolon
multiline_comment|/* Last job on watchdog queue */
DECL|member|total_timeout
r_uint32
id|total_timeout
suffix:semicolon
multiline_comment|/* Total timeout (quantum count) */
DECL|member|watchdogactive
r_uint32
id|watchdogactive
suffix:semicolon
macro_line|#endif
DECL|member|done_q_first
id|srb_t
op_star
id|done_q_first
suffix:semicolon
multiline_comment|/* First job on done queue */
DECL|member|done_q_last
id|srb_t
op_star
id|done_q_last
suffix:semicolon
multiline_comment|/* Last job on done queue */
r_volatile
r_struct
(brace
DECL|member|mbox_int
r_uint32
id|mbox_int
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|mbox_busy
r_uint32
id|mbox_busy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|online
r_uint32
id|online
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 2 */
DECL|member|reset_marker
r_uint32
id|reset_marker
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 3 */
DECL|member|isp_abort_needed
r_uint32
id|isp_abort_needed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 4 */
DECL|member|disable_host_adapter
r_uint32
id|disable_host_adapter
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 5 */
DECL|member|reset_active
r_uint32
id|reset_active
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 6 */
DECL|member|abort_isp_active
r_uint32
id|abort_isp_active
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 7 */
DECL|member|disable_risc_code_load
r_uint32
id|disable_risc_code_load
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 8 */
DECL|member|enable_64bit_addressing
r_uint32
id|enable_64bit_addressing
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 9 */
DECL|member|in_reset
r_uint32
id|in_reset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 10 */
DECL|member|ints_enabled
r_uint32
id|ints_enabled
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flags
)brace
id|flags
suffix:semicolon
multiline_comment|/* needed holders for PCI ordered list of hosts */
DECL|member|io_port
r_int
r_int
id|io_port
suffix:semicolon
DECL|member|irq
r_uint32
id|irq
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Macros to help code, maintain, etc.&n; */
DECL|macro|SUBDEV
mdefine_line|#define SUBDEV(b, t, l)&t;&t;((b &lt;&lt; (MAX_T_BITS + MAX_L_BITS)) | (t &lt;&lt; MAX_L_BITS) | l)
DECL|macro|LU_Q
mdefine_line|#define LU_Q(ha, b, t, l)&t;(ha-&gt;dev[SUBDEV(b, t, l)])
macro_line|#endif&t;&t;&t;&t;/* HOSTS_C */
multiline_comment|/*&n; *  Linux - SCSI Driver Interface Function Prototypes.&n; */
r_int
id|qla1280_proc_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_const
r_char
op_star
id|qla1280_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
r_int
id|qla1280_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|qla1280_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|qla1280_queuecommand
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
r_int
id|qla1280_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|qla1280_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|qla1280_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
(braket
)braket
)paren
suffix:semicolon
r_void
id|qla1280_intr_handler
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_void
id|qla1280_setup
c_func
(paren
r_char
op_star
id|s
comma
r_int
op_star
id|dummy
)paren
suffix:semicolon
multiline_comment|/*&n; * Scsi_Host_template (see hosts.h)&n; * Device driver Interfaces to mid-level SCSI driver.&n; */
DECL|macro|QLA1280_LINUX_TEMPLATE
mdefine_line|#define QLA1280_LINUX_TEMPLATE {&t;&t;&t;&t;&bslash;&n;&t;next: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;module: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;proc_dir: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;proc_info: qla1280_proc_info,&t;&t;&t;&t;&bslash;&n;&t;name: &quot;Qlogic ISP 1280/12160&quot;,&t;&t;&t;&t;&bslash;&n;&t;detect: qla1280_detect,&t;&t;&t;&t;&t;&bslash;&n;&t;release: qla1280_release,&t;&t;&t;&t;&bslash;&n;&t;info: qla1280_info,&t;&t;&t;&t;&t;&bslash;&n;&t;ioctl: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;command: NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;queuecommand: qla1280_queuecommand,&t;&t;&t;&bslash;&n;&t;eh_strategy_handler: NULL,&t;&t;&t;&t;&bslash;&n;&t;eh_abort_handler: NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;eh_device_reset_handler: NULL,&t;&t;&t;&t;&bslash;&n;&t;eh_bus_reset_handler: NULL,&t;&t;&t;&t;&bslash;&n;&t;eh_host_reset_handler: NULL,&t;&t;&t;&t;&bslash;&n;/*&t;use_new_eh_code: 0, */&t;&t;&t;&t;&t;&bslash;&n;&t;abort: qla1280_abort,&t;&t;&t;&t;&t;&bslash;&n;&t;reset: qla1280_reset,&t;&t;&t;&t;&t;&bslash;&n;&t;slave_attach: NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;bios_param: qla1280_biosparam,&t;&t;&t;&t;&bslash;&n;&t;can_queue: 255,&t;&t;/* max simultaneous cmds      */&bslash;&n;&t;this_id: -1,&t;&t;/* scsi id of host adapter    */&bslash;&n;&t;sg_tablesize: SG_ALL,&t;/* max scatter-gather cmds    */&bslash;&n;&t;cmd_per_lun: 3,&t;&t;/* cmds per lun (linked cmds) */&bslash;&n;&t;present: 0,&t;&t;/* number of 1280&squot;s present   */&bslash;&n;&t;unchecked_isa_dma: 0,&t;/* no memory DMA restrictions */&bslash;&n;&t;use_clustering: ENABLE_CLUSTERING,&t;&t;&t;&bslash;&n;&t;emulated: 0&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif&t;&t;&t;&t;/* _IO_HBA_QLA1280_H */
eof
