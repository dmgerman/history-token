multiline_comment|/********************************************************************************&n;*                  QLOGIC LINUX SOFTWARE&n;*&n;* QLogic ISP2x00 device driver for Linux 2.6.x&n;* Copyright (C) 2003-2004 QLogic Corporation&n;* (www.qlogic.com)&n;*&n;* This program is free software; you can redistribute it and/or modify it&n;* under the terms of the GNU General Public License as published by the&n;* Free Software Foundation; either version 2, or (at your option) any&n;* later version.&n;*&n;* This program is distributed in the hope that it will be useful, but&n;* WITHOUT ANY WARRANTY; without even the implied warranty of&n;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;* General Public License for more details.&n;**&n;******************************************************************************/
macro_line|#ifndef __QLA_DEF_H
DECL|macro|__QLA_DEF_H
mdefine_line|#define __QLA_DEF_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/dma-mapping.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/dmapool.h&gt;
macro_line|#include &lt;linux/mempool.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_cmnd.h&gt;
multiline_comment|/* XXX(hch): move to pci_ids.h */
macro_line|#ifndef PCI_DEVICE_ID_QLOGIC_ISP2300
DECL|macro|PCI_DEVICE_ID_QLOGIC_ISP2300
mdefine_line|#define PCI_DEVICE_ID_QLOGIC_ISP2300&t;0x2300
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_QLOGIC_ISP2312
DECL|macro|PCI_DEVICE_ID_QLOGIC_ISP2312
mdefine_line|#define PCI_DEVICE_ID_QLOGIC_ISP2312&t;0x2312
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_QLOGIC_ISP2322
DECL|macro|PCI_DEVICE_ID_QLOGIC_ISP2322
mdefine_line|#define PCI_DEVICE_ID_QLOGIC_ISP2322&t;0x2322
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_QLOGIC_ISP6312
DECL|macro|PCI_DEVICE_ID_QLOGIC_ISP6312
mdefine_line|#define PCI_DEVICE_ID_QLOGIC_ISP6312&t;0x6312
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_QLOGIC_ISP6322
DECL|macro|PCI_DEVICE_ID_QLOGIC_ISP6322
mdefine_line|#define PCI_DEVICE_ID_QLOGIC_ISP6322&t;0x6322
macro_line|#endif
macro_line|#if defined(CONFIG_SCSI_QLA21XX) || defined(CONFIG_SCSI_QLA21XX_MODULE)
DECL|macro|IS_QLA2100
mdefine_line|#define IS_QLA2100(ha)&t;((ha)-&gt;pdev-&gt;device == PCI_DEVICE_ID_QLOGIC_ISP2100)
macro_line|#else
DECL|macro|IS_QLA2100
mdefine_line|#define IS_QLA2100(ha)&t;0
macro_line|#endif
macro_line|#if defined(CONFIG_SCSI_QLA22XX) || defined(CONFIG_SCSI_QLA22XX_MODULE)
DECL|macro|IS_QLA2200
mdefine_line|#define IS_QLA2200(ha)&t;((ha)-&gt;pdev-&gt;device == PCI_DEVICE_ID_QLOGIC_ISP2200)
macro_line|#else
DECL|macro|IS_QLA2200
mdefine_line|#define IS_QLA2200(ha)&t;0
macro_line|#endif
macro_line|#if defined(CONFIG_SCSI_QLA2300) || defined(CONFIG_SCSI_QLA2300_MODULE)
DECL|macro|IS_QLA2300
mdefine_line|#define IS_QLA2300(ha)&t;((ha)-&gt;pdev-&gt;device == PCI_DEVICE_ID_QLOGIC_ISP2300)
DECL|macro|IS_QLA2312
mdefine_line|#define IS_QLA2312(ha)&t;((ha)-&gt;pdev-&gt;device == PCI_DEVICE_ID_QLOGIC_ISP2312)
macro_line|#else
DECL|macro|IS_QLA2300
mdefine_line|#define IS_QLA2300(ha)&t;0
DECL|macro|IS_QLA2312
mdefine_line|#define IS_QLA2312(ha)&t;0
macro_line|#endif
macro_line|#if defined(CONFIG_SCSI_QLA2322) || defined(CONFIG_SCSI_QLA2322_MODULE)
DECL|macro|IS_QLA2322
mdefine_line|#define IS_QLA2322(ha)&t;((ha)-&gt;pdev-&gt;device == PCI_DEVICE_ID_QLOGIC_ISP2322)
macro_line|#else
DECL|macro|IS_QLA2322
mdefine_line|#define IS_QLA2322(ha)&t;0
macro_line|#endif
macro_line|#if defined(CONFIG_SCSI_QLA6312) || defined(CONFIG_SCSI_QLA6312_MODULE)
DECL|macro|IS_QLA6312
mdefine_line|#define IS_QLA6312(ha)&t;((ha)-&gt;pdev-&gt;device == PCI_DEVICE_ID_QLOGIC_ISP6312)
DECL|macro|IS_QLA6322
mdefine_line|#define IS_QLA6322(ha)&t;((ha)-&gt;pdev-&gt;device == PCI_DEVICE_ID_QLOGIC_ISP6322)
macro_line|#else
DECL|macro|IS_QLA6312
mdefine_line|#define IS_QLA6312(ha)&t;0
DECL|macro|IS_QLA6322
mdefine_line|#define IS_QLA6322(ha)&t;0
macro_line|#endif
DECL|macro|IS_QLA23XX
mdefine_line|#define IS_QLA23XX(ha)&t;(IS_QLA2300(ha) || IS_QLA2312(ha) || IS_QLA2322(ha) || &bslash;&n;    &t;&t;&t; IS_QLA6312(ha) || IS_QLA6322(ha))
multiline_comment|/*&n; * Only non-ISP2[12]00 have extended addressing support in the firmware.&n; */
DECL|macro|HAS_EXTENDED_IDS
mdefine_line|#define HAS_EXTENDED_IDS(ha)&t;(!IS_QLA2100(ha) &amp;&amp; !IS_QLA2200(ha))
multiline_comment|/*&n; * We have MAILBOX_REGISTER_COUNT sized arrays in a few places,&n; * but that&squot;s fine as we don&squot;t look at the last 24 ones for&n; * ISP2100 HBAs.&n; */
DECL|macro|MAILBOX_REGISTER_COUNT_2100
mdefine_line|#define MAILBOX_REGISTER_COUNT_2100&t;8
DECL|macro|MAILBOX_REGISTER_COUNT
mdefine_line|#define MAILBOX_REGISTER_COUNT&t;&t;32
DECL|macro|QLA2200A_RISC_ROM_VER
mdefine_line|#define QLA2200A_RISC_ROM_VER&t;4
DECL|macro|FPM_2300
mdefine_line|#define FPM_2300&t;&t;6
DECL|macro|FPM_2310
mdefine_line|#define FPM_2310&t;&t;7
macro_line|#include &quot;qla_settings.h&quot;
multiline_comment|/* &n; * Data bit definitions&n; */
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
DECL|macro|LSB
mdefine_line|#define LSB(x)&t;((uint8_t)(x))
DECL|macro|MSB
mdefine_line|#define MSB(x)&t;((uint8_t)((uint16_t)(x) &gt;&gt; 8))
DECL|macro|LSW
mdefine_line|#define LSW(x)&t;((uint16_t)(x))
DECL|macro|MSW
mdefine_line|#define MSW(x)&t;((uint16_t)((uint32_t)(x) &gt;&gt; 16))
DECL|macro|LSD
mdefine_line|#define LSD(x)&t;((uint32_t)((uint64_t)(x)))
DECL|macro|MSD
mdefine_line|#define MSD(x)&t;((uint32_t)((((uint64_t)(x)) &gt;&gt; 16) &gt;&gt; 16))
multiline_comment|/*&n; * I/O register&n;*/
DECL|macro|RD_REG_BYTE
mdefine_line|#define RD_REG_BYTE(addr)&t;&t;readb(addr)
DECL|macro|RD_REG_WORD
mdefine_line|#define RD_REG_WORD(addr)&t;&t;readw(addr)
DECL|macro|RD_REG_DWORD
mdefine_line|#define RD_REG_DWORD(addr)&t;&t;readl(addr)
DECL|macro|RD_REG_BYTE_RELAXED
mdefine_line|#define RD_REG_BYTE_RELAXED(addr)&t;readb_relaxed(addr)
DECL|macro|RD_REG_WORD_RELAXED
mdefine_line|#define RD_REG_WORD_RELAXED(addr)&t;readw_relaxed(addr)
DECL|macro|RD_REG_DWORD_RELAXED
mdefine_line|#define RD_REG_DWORD_RELAXED(addr)&t;readl_relaxed(addr)
DECL|macro|WRT_REG_BYTE
mdefine_line|#define WRT_REG_BYTE(addr, data)&t;writeb(data,addr)
DECL|macro|WRT_REG_WORD
mdefine_line|#define WRT_REG_WORD(addr, data)&t;writew(data,addr)
DECL|macro|WRT_REG_DWORD
mdefine_line|#define WRT_REG_DWORD(addr, data)&t;writel(data,addr)
multiline_comment|/*&n; * Fibre Channel device definitions.&n; */
DECL|macro|WWN_SIZE
mdefine_line|#define WWN_SIZE&t;&t;8&t;/* Size of WWPN, WWN &amp; WWNN */
DECL|macro|MAX_FIBRE_DEVICES
mdefine_line|#define MAX_FIBRE_DEVICES&t;512
DECL|macro|MAX_FIBRE_LUNS
mdefine_line|#define MAX_FIBRE_LUNS  &t;256
DECL|macro|MAX_RSCN_COUNT
mdefine_line|#define&t;MAX_RSCN_COUNT&t;&t;32
DECL|macro|MAX_HOST_COUNT
mdefine_line|#define&t;MAX_HOST_COUNT&t;&t;16
multiline_comment|/*&n; * Host adapter default definitions.&n; */
DECL|macro|MAX_BUSES
mdefine_line|#define MAX_BUSES&t;&t;1  /* We only have one bus today */
DECL|macro|MAX_TARGETS_2100
mdefine_line|#define MAX_TARGETS_2100&t;MAX_FIBRE_DEVICES
DECL|macro|MAX_TARGETS_2200
mdefine_line|#define MAX_TARGETS_2200&t;MAX_FIBRE_DEVICES
DECL|macro|MAX_TARGETS
mdefine_line|#define MAX_TARGETS&t;&t;MAX_FIBRE_DEVICES
DECL|macro|MIN_LUNS
mdefine_line|#define MIN_LUNS&t;&t;8
DECL|macro|MAX_LUNS
mdefine_line|#define MAX_LUNS&t;&t;MAX_FIBRE_LUNS
DECL|macro|MAX_CMDS_PER_LUN
mdefine_line|#define MAX_CMDS_PER_LUN&t;255 
multiline_comment|/*&n; * Fibre Channel device definitions.&n; */
DECL|macro|SNS_LAST_LOOP_ID_2100
mdefine_line|#define SNS_LAST_LOOP_ID_2100&t;0xfe
DECL|macro|SNS_LAST_LOOP_ID_2300
mdefine_line|#define SNS_LAST_LOOP_ID_2300&t;0x7ff
DECL|macro|LAST_LOCAL_LOOP_ID
mdefine_line|#define LAST_LOCAL_LOOP_ID&t;0x7d
DECL|macro|SNS_FL_PORT
mdefine_line|#define SNS_FL_PORT&t;&t;0x7e
DECL|macro|FABRIC_CONTROLLER
mdefine_line|#define FABRIC_CONTROLLER&t;0x7f
DECL|macro|SIMPLE_NAME_SERVER
mdefine_line|#define SIMPLE_NAME_SERVER&t;0x80
DECL|macro|SNS_FIRST_LOOP_ID
mdefine_line|#define SNS_FIRST_LOOP_ID&t;0x81
DECL|macro|MANAGEMENT_SERVER
mdefine_line|#define MANAGEMENT_SERVER&t;0xfe
DECL|macro|BROADCAST
mdefine_line|#define BROADCAST&t;&t;0xff
DECL|macro|RESERVED_LOOP_ID
mdefine_line|#define RESERVED_LOOP_ID(x)&t;((x &gt; LAST_LOCAL_LOOP_ID &amp;&amp; &bslash;&n;&t;&t;&t;&t; x &lt; SNS_FIRST_LOOP_ID) || &bslash;&n;&t;&t;&t;&t; x == MANAGEMENT_SERVER || &bslash;&n;&t;&t;&t;&t; x == BROADCAST)
multiline_comment|/*&n; * Timeout timer counts in seconds&n; */
DECL|macro|PORT_RETRY_TIME
mdefine_line|#define PORT_RETRY_TIME&t;&t;&t;2
DECL|macro|LOOP_DOWN_TIMEOUT
mdefine_line|#define LOOP_DOWN_TIMEOUT&t;&t;60
DECL|macro|LOOP_DOWN_TIME
mdefine_line|#define LOOP_DOWN_TIME&t;&t;&t;255&t;/* 240 */
DECL|macro|LOOP_DOWN_RESET
mdefine_line|#define&t;LOOP_DOWN_RESET&t;&t;&t;(LOOP_DOWN_TIME - 30)
multiline_comment|/* Maximum outstanding commands in ISP queues (1-65535) */
DECL|macro|MAX_OUTSTANDING_COMMANDS
mdefine_line|#define MAX_OUTSTANDING_COMMANDS&t;1024
multiline_comment|/* ISP request and response entry counts (37-65535) */
DECL|macro|REQUEST_ENTRY_CNT_2100
mdefine_line|#define REQUEST_ENTRY_CNT_2100&t;&t;128&t;/* Number of request entries. */
DECL|macro|REQUEST_ENTRY_CNT_2200
mdefine_line|#define REQUEST_ENTRY_CNT_2200&t;&t;2048&t;/* Number of request entries. */
DECL|macro|REQUEST_ENTRY_CNT_2XXX_EXT_MEM
mdefine_line|#define REQUEST_ENTRY_CNT_2XXX_EXT_MEM&t;4096&t;/* Number of request entries. */
DECL|macro|RESPONSE_ENTRY_CNT_2100
mdefine_line|#define RESPONSE_ENTRY_CNT_2100&t;&t;64&t;/* Number of response entries.*/
DECL|macro|RESPONSE_ENTRY_CNT_2300
mdefine_line|#define RESPONSE_ENTRY_CNT_2300&t;&t;512&t;/* Number of response entries.*/
multiline_comment|/*&n; * SCSI Request Block &n; */
DECL|struct|srb
r_typedef
r_struct
id|srb
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|ha
r_struct
id|scsi_qla_host
op_star
id|ha
suffix:semicolon
multiline_comment|/* HA the SP is queued on */
DECL|member|cmd
r_struct
id|scsi_cmnd
op_star
id|cmd
suffix:semicolon
multiline_comment|/* Linux SCSI command pkt */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* Command timer */
DECL|member|ref_count
id|atomic_t
id|ref_count
suffix:semicolon
multiline_comment|/* Reference count for this structure */
DECL|member|flags
r_uint16
id|flags
suffix:semicolon
multiline_comment|/* Request state */
DECL|member|state
r_uint16
id|state
suffix:semicolon
multiline_comment|/* Target/LUN queue pointers. */
DECL|member|tgt_queue
r_struct
id|os_tgt
op_star
id|tgt_queue
suffix:semicolon
multiline_comment|/* ptr to visible ha&squot;s target */
DECL|member|lun_queue
r_struct
id|os_lun
op_star
id|lun_queue
suffix:semicolon
multiline_comment|/* ptr to visible ha&squot;s lun */
DECL|member|fclun
r_struct
id|fc_lun
op_star
id|fclun
suffix:semicolon
multiline_comment|/* FC LUN context pointer. */
multiline_comment|/* Timing counts. */
DECL|member|e_start
r_int
r_int
id|e_start
suffix:semicolon
multiline_comment|/* Start of extend timeout */
DECL|member|r_start
r_int
r_int
id|r_start
suffix:semicolon
multiline_comment|/* Start of request */
DECL|member|u_start
r_int
r_int
id|u_start
suffix:semicolon
multiline_comment|/* When sent to RISC */
DECL|member|f_start
r_int
r_int
id|f_start
suffix:semicolon
multiline_comment|/* When placed in FO queue*/
multiline_comment|/* Single transfer DMA context */
DECL|member|dma_handle
id|dma_addr_t
id|dma_handle
suffix:semicolon
DECL|member|request_sense_length
r_uint32
id|request_sense_length
suffix:semicolon
DECL|member|request_sense_ptr
r_uint8
op_star
id|request_sense_ptr
suffix:semicolon
DECL|member|ext_history
r_int
id|ext_history
suffix:semicolon
multiline_comment|/* Suspend delay */
DECL|member|delay
r_int
id|delay
suffix:semicolon
multiline_comment|/* Raw completion info for use by failover ? */
DECL|member|fo_retry_cnt
r_uint8
id|fo_retry_cnt
suffix:semicolon
multiline_comment|/* Retry count this request */
DECL|member|err_id
r_uint8
id|err_id
suffix:semicolon
multiline_comment|/* error id */
DECL|macro|SRB_ERR_PORT
mdefine_line|#define SRB_ERR_PORT&t;1&t;&t;/* Request failed -- &quot;port down&quot; */
DECL|macro|SRB_ERR_LOOP
mdefine_line|#define SRB_ERR_LOOP&t;2&t;&t;/* Request failed -- &quot;loop down&quot; */
DECL|macro|SRB_ERR_DEVICE
mdefine_line|#define SRB_ERR_DEVICE&t;3&t;&t;/* Request failed -- &quot;device error&quot; */
DECL|macro|SRB_ERR_OTHER
mdefine_line|#define SRB_ERR_OTHER&t;4
multiline_comment|/* SRB magic number */
DECL|member|magic
r_uint16
id|magic
suffix:semicolon
DECL|macro|SRB_MAGIC
mdefine_line|#define SRB_MAGIC       0x10CB
DECL|typedef|srb_t
)brace
id|srb_t
suffix:semicolon
multiline_comment|/*&n; * SRB flag definitions&n; */
DECL|macro|SRB_TIMEOUT
mdefine_line|#define SRB_TIMEOUT&t;&t;BIT_0&t;/* Command timed out */
DECL|macro|SRB_DMA_VALID
mdefine_line|#define SRB_DMA_VALID&t;&t;BIT_1&t;/* Command sent to ISP */
DECL|macro|SRB_WATCHDOG
mdefine_line|#define SRB_WATCHDOG&t;&t;BIT_2&t;/* Command on watchdog list */
DECL|macro|SRB_ABORT_PENDING
mdefine_line|#define SRB_ABORT_PENDING&t;BIT_3&t;/* Command abort sent to device */
DECL|macro|SRB_ABORTED
mdefine_line|#define SRB_ABORTED&t;&t;BIT_4&t;/* Command aborted command already */
DECL|macro|SRB_RETRY
mdefine_line|#define SRB_RETRY&t;&t;BIT_5&t;/* Command needs retrying */
DECL|macro|SRB_GOT_SENSE
mdefine_line|#define SRB_GOT_SENSE&t;&t;BIT_6&t;/* Command has sense data */
DECL|macro|SRB_FAILOVER
mdefine_line|#define SRB_FAILOVER&t;&t;BIT_7&t;/* Command in failover state */
DECL|macro|SRB_BUSY
mdefine_line|#define SRB_BUSY&t;&t;BIT_8&t;/* Command is in busy retry state */
DECL|macro|SRB_FO_CANCEL
mdefine_line|#define SRB_FO_CANCEL&t;&t;BIT_9&t;/* Command don&squot;t need to do failover */
DECL|macro|SRB_IOCTL
mdefine_line|#define SRB_IOCTL&t;&t;BIT_10&t;/* IOCTL command. */
DECL|macro|SRB_TAPE
mdefine_line|#define SRB_TAPE&t;&t;BIT_11&t;/* FCP2 (Tape) command. */
multiline_comment|/*&n; * SRB state definitions&n; */
DECL|macro|SRB_FREE_STATE
mdefine_line|#define SRB_FREE_STATE&t;&t;0&t;/*   returned back */
DECL|macro|SRB_PENDING_STATE
mdefine_line|#define SRB_PENDING_STATE&t;1&t;/*   queued in LUN Q */
DECL|macro|SRB_ACTIVE_STATE
mdefine_line|#define SRB_ACTIVE_STATE&t;2&t;/*   in Active Array */
DECL|macro|SRB_DONE_STATE
mdefine_line|#define SRB_DONE_STATE&t;&t;3&t;/*   queued in Done Queue */
DECL|macro|SRB_RETRY_STATE
mdefine_line|#define SRB_RETRY_STATE&t;&t;4&t;/*   in Retry Queue */
DECL|macro|SRB_SUSPENDED_STATE
mdefine_line|#define SRB_SUSPENDED_STATE&t;5&t;/*   in suspended state */
DECL|macro|SRB_NO_QUEUE_STATE
mdefine_line|#define SRB_NO_QUEUE_STATE&t;6&t;/*   is in between states */
DECL|macro|SRB_ACTIVE_TIMEOUT_STATE
mdefine_line|#define SRB_ACTIVE_TIMEOUT_STATE 7&t;/*   in Active Array but timed out */
DECL|macro|SRB_FAILOVER_STATE
mdefine_line|#define SRB_FAILOVER_STATE&t;8&t;/*   in Failover Queue */
DECL|macro|SRB_SCSI_RETRY_STATE
mdefine_line|#define SRB_SCSI_RETRY_STATE&t;9&t;/*   in Scsi Retry Queue */
multiline_comment|/*&n; * ISP I/O Register Set structure definitions.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|flash_address
r_volatile
r_uint16
id|flash_address
suffix:semicolon
multiline_comment|/* Flash BIOS address */
DECL|member|flash_data
r_volatile
r_uint16
id|flash_data
suffix:semicolon
multiline_comment|/* Flash BIOS data */
DECL|member|unused_1
r_uint16
id|unused_1
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Gap */
DECL|member|ctrl_status
r_volatile
r_uint16
id|ctrl_status
suffix:semicolon
multiline_comment|/* Control/Status */
DECL|macro|CSR_FLASH_64K_BANK
mdefine_line|#define CSR_FLASH_64K_BANK&t;BIT_3&t;/* Flash upper 64K bank select */ 
DECL|macro|CSR_FLASH_ENABLE
mdefine_line|#define CSR_FLASH_ENABLE&t;BIT_1&t;/* Flash BIOS Read/Write enable */
DECL|macro|CSR_ISP_SOFT_RESET
mdefine_line|#define CSR_ISP_SOFT_RESET&t;BIT_0&t;/* ISP soft reset */
DECL|member|ictrl
r_volatile
r_uint16
id|ictrl
suffix:semicolon
multiline_comment|/* Interrupt control */
DECL|macro|ICR_EN_INT
mdefine_line|#define ICR_EN_INT&t;&t;BIT_15&t;/* ISP enable interrupts. */
DECL|macro|ICR_EN_RISC
mdefine_line|#define ICR_EN_RISC&t;&t;BIT_3&t;/* ISP enable RISC interrupts. */
DECL|member|istatus
r_volatile
r_uint16
id|istatus
suffix:semicolon
multiline_comment|/* Interrupt status */
DECL|macro|ISR_RISC_INT
mdefine_line|#define ISR_RISC_INT&t;&t;BIT_3&t;/* RISC interrupt */
DECL|member|semaphore
r_volatile
r_uint16
id|semaphore
suffix:semicolon
multiline_comment|/* Semaphore */
DECL|member|nvram
r_volatile
r_uint16
id|nvram
suffix:semicolon
multiline_comment|/* NVRAM register. */
DECL|macro|NVR_DESELECT
mdefine_line|#define NVR_DESELECT&t;&t;0
DECL|macro|NVR_BUSY
mdefine_line|#define NVR_BUSY&t;&t;BIT_15
DECL|macro|NVR_WRT_ENABLE
mdefine_line|#define NVR_WRT_ENABLE&t;&t;BIT_14&t;/* Write enable */
DECL|macro|NVR_PR_ENABLE
mdefine_line|#define NVR_PR_ENABLE&t;&t;BIT_13&t;/* Protection register enable */
DECL|macro|NVR_DATA_IN
mdefine_line|#define NVR_DATA_IN&t;&t;BIT_3
DECL|macro|NVR_DATA_OUT
mdefine_line|#define NVR_DATA_OUT&t;&t;BIT_2
DECL|macro|NVR_SELECT
mdefine_line|#define NVR_SELECT&t;&t;BIT_1
DECL|macro|NVR_CLOCK
mdefine_line|#define NVR_CLOCK&t;&t;BIT_0
r_union
(brace
r_struct
(brace
DECL|member|mailbox0
r_volatile
r_uint16
id|mailbox0
suffix:semicolon
DECL|member|mailbox1
r_volatile
r_uint16
id|mailbox1
suffix:semicolon
DECL|member|mailbox2
r_volatile
r_uint16
id|mailbox2
suffix:semicolon
DECL|member|mailbox3
r_volatile
r_uint16
id|mailbox3
suffix:semicolon
DECL|member|mailbox4
r_volatile
r_uint16
id|mailbox4
suffix:semicolon
DECL|member|mailbox5
r_volatile
r_uint16
id|mailbox5
suffix:semicolon
DECL|member|mailbox6
r_volatile
r_uint16
id|mailbox6
suffix:semicolon
DECL|member|mailbox7
r_volatile
r_uint16
id|mailbox7
suffix:semicolon
DECL|member|unused_2
r_uint16
id|unused_2
(braket
l_int|59
)braket
suffix:semicolon
multiline_comment|/* Gap */
DECL|member|isp2100
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|isp2100
suffix:semicolon
r_struct
(brace
multiline_comment|/* Request Queue */
DECL|member|req_q_in
r_volatile
r_uint16
id|req_q_in
suffix:semicolon
multiline_comment|/*  In-Pointer */
DECL|member|req_q_out
r_volatile
r_uint16
id|req_q_out
suffix:semicolon
multiline_comment|/*  Out-Pointer */
multiline_comment|/* Response Queue */
DECL|member|rsp_q_in
r_volatile
r_uint16
id|rsp_q_in
suffix:semicolon
multiline_comment|/*  In-Pointer */
DECL|member|rsp_q_out
r_volatile
r_uint16
id|rsp_q_out
suffix:semicolon
multiline_comment|/*  Out-Pointer */
multiline_comment|/* RISC to Host Status */
DECL|member|host_status
r_volatile
r_uint32
id|host_status
suffix:semicolon
DECL|macro|HSR_RISC_INT
mdefine_line|#define HSR_RISC_INT&t;&t;BIT_15&t;/* RISC interrupt */
DECL|macro|HSR_RISC_PAUSED
mdefine_line|#define HSR_RISC_PAUSED&t;&t;BIT_8&t;/* RISC Paused */
multiline_comment|/* Host to Host Semaphore */
DECL|member|host_semaphore
r_volatile
r_uint16
id|host_semaphore
suffix:semicolon
DECL|member|unused_3
r_uint16
id|unused_3
(braket
l_int|17
)braket
suffix:semicolon
multiline_comment|/* Gap */
DECL|member|mailbox0
r_volatile
r_uint16
id|mailbox0
suffix:semicolon
DECL|member|mailbox1
r_volatile
r_uint16
id|mailbox1
suffix:semicolon
DECL|member|mailbox2
r_volatile
r_uint16
id|mailbox2
suffix:semicolon
DECL|member|mailbox3
r_volatile
r_uint16
id|mailbox3
suffix:semicolon
DECL|member|mailbox4
r_volatile
r_uint16
id|mailbox4
suffix:semicolon
DECL|member|mailbox5
r_volatile
r_uint16
id|mailbox5
suffix:semicolon
DECL|member|mailbox6
r_volatile
r_uint16
id|mailbox6
suffix:semicolon
DECL|member|mailbox7
r_volatile
r_uint16
id|mailbox7
suffix:semicolon
DECL|member|mailbox8
r_volatile
r_uint16
id|mailbox8
suffix:semicolon
DECL|member|mailbox9
r_volatile
r_uint16
id|mailbox9
suffix:semicolon
DECL|member|mailbox10
r_volatile
r_uint16
id|mailbox10
suffix:semicolon
DECL|member|mailbox11
r_volatile
r_uint16
id|mailbox11
suffix:semicolon
DECL|member|mailbox12
r_volatile
r_uint16
id|mailbox12
suffix:semicolon
DECL|member|mailbox13
r_volatile
r_uint16
id|mailbox13
suffix:semicolon
DECL|member|mailbox14
r_volatile
r_uint16
id|mailbox14
suffix:semicolon
DECL|member|mailbox15
r_volatile
r_uint16
id|mailbox15
suffix:semicolon
DECL|member|mailbox16
r_volatile
r_uint16
id|mailbox16
suffix:semicolon
DECL|member|mailbox17
r_volatile
r_uint16
id|mailbox17
suffix:semicolon
DECL|member|mailbox18
r_volatile
r_uint16
id|mailbox18
suffix:semicolon
DECL|member|mailbox19
r_volatile
r_uint16
id|mailbox19
suffix:semicolon
DECL|member|mailbox20
r_volatile
r_uint16
id|mailbox20
suffix:semicolon
DECL|member|mailbox21
r_volatile
r_uint16
id|mailbox21
suffix:semicolon
DECL|member|mailbox22
r_volatile
r_uint16
id|mailbox22
suffix:semicolon
DECL|member|mailbox23
r_volatile
r_uint16
id|mailbox23
suffix:semicolon
DECL|member|mailbox24
r_volatile
r_uint16
id|mailbox24
suffix:semicolon
DECL|member|mailbox25
r_volatile
r_uint16
id|mailbox25
suffix:semicolon
DECL|member|mailbox26
r_volatile
r_uint16
id|mailbox26
suffix:semicolon
DECL|member|mailbox27
r_volatile
r_uint16
id|mailbox27
suffix:semicolon
DECL|member|mailbox28
r_volatile
r_uint16
id|mailbox28
suffix:semicolon
DECL|member|mailbox29
r_volatile
r_uint16
id|mailbox29
suffix:semicolon
DECL|member|mailbox30
r_volatile
r_uint16
id|mailbox30
suffix:semicolon
DECL|member|mailbox31
r_volatile
r_uint16
id|mailbox31
suffix:semicolon
DECL|member|fb_cmd
r_volatile
r_uint16
id|fb_cmd
suffix:semicolon
DECL|member|unused_4
r_uint16
id|unused_4
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Gap */
DECL|member|isp2300
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|isp2300
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|fpm_diag_config
r_volatile
r_uint16
id|fpm_diag_config
suffix:semicolon
DECL|member|unused_5
r_uint16
id|unused_5
(braket
l_int|0x6
)braket
suffix:semicolon
multiline_comment|/* Gap */
DECL|member|pcr
r_volatile
r_uint16
id|pcr
suffix:semicolon
multiline_comment|/* Processor Control Register. */
DECL|member|unused_6
r_uint16
id|unused_6
(braket
l_int|0x5
)braket
suffix:semicolon
multiline_comment|/* Gap */
DECL|member|mctr
r_volatile
r_uint16
id|mctr
suffix:semicolon
multiline_comment|/* Memory Configuration and Timing. */
DECL|member|unused_7
r_uint16
id|unused_7
(braket
l_int|0x3
)braket
suffix:semicolon
multiline_comment|/* Gap */
DECL|member|fb_cmd_2100
r_volatile
r_uint16
id|fb_cmd_2100
suffix:semicolon
multiline_comment|/* Unused on 23XX */
DECL|member|unused_8
r_uint16
id|unused_8
(braket
l_int|0x3
)braket
suffix:semicolon
multiline_comment|/* Gap */
DECL|member|hccr
r_volatile
r_uint16
id|hccr
suffix:semicolon
multiline_comment|/* Host command &amp; control register. */
DECL|macro|HCCR_HOST_INT
mdefine_line|#define HCCR_HOST_INT&t;&t;BIT_7&t;/* Host interrupt bit */
DECL|macro|HCCR_RISC_PAUSE
mdefine_line|#define HCCR_RISC_PAUSE&t;&t;BIT_5&t;/* Pause mode bit */
multiline_comment|/* HCCR commands */
DECL|macro|HCCR_RESET_RISC
mdefine_line|#define HCCR_RESET_RISC&t;&t;0x1000&t;/* Reset RISC */
DECL|macro|HCCR_PAUSE_RISC
mdefine_line|#define HCCR_PAUSE_RISC&t;&t;0x2000&t;/* Pause RISC */
DECL|macro|HCCR_RELEASE_RISC
mdefine_line|#define HCCR_RELEASE_RISC&t;0x3000&t;/* Release RISC from reset. */
DECL|macro|HCCR_SET_HOST_INT
mdefine_line|#define HCCR_SET_HOST_INT&t;0x5000&t;/* Set host interrupt */
DECL|macro|HCCR_CLR_HOST_INT
mdefine_line|#define HCCR_CLR_HOST_INT&t;0x6000&t;/* Clear HOST interrupt */
DECL|macro|HCCR_CLR_RISC_INT
mdefine_line|#define HCCR_CLR_RISC_INT&t;0x7000&t;/* Clear RISC interrupt */
DECL|macro|HCCR_DISABLE_PARITY_PAUSE
mdefine_line|#define&t;HCCR_DISABLE_PARITY_PAUSE 0x4001 /* Disable parity error RISC pause. */
DECL|macro|HCCR_ENABLE_PARITY
mdefine_line|#define HCCR_ENABLE_PARITY&t;0xA000&t;/* Enable PARITY interrupt */
DECL|member|unused_9
r_uint16
id|unused_9
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Gap */
DECL|member|gpiod
r_volatile
r_uint16
id|gpiod
suffix:semicolon
multiline_comment|/* GPIO Data register. */
DECL|member|gpioe
r_volatile
r_uint16
id|gpioe
suffix:semicolon
multiline_comment|/* GPIO Enable register. */
DECL|macro|GPIO_LED_MASK
mdefine_line|#define GPIO_LED_MASK&t;&t;&t;0x00C0
DECL|macro|GPIO_LED_GREEN_OFF_AMBER_OFF
mdefine_line|#define GPIO_LED_GREEN_OFF_AMBER_OFF&t;0x0000
DECL|macro|GPIO_LED_GREEN_ON_AMBER_OFF
mdefine_line|#define GPIO_LED_GREEN_ON_AMBER_OFF&t;0x0040
DECL|macro|GPIO_LED_GREEN_OFF_AMBER_ON
mdefine_line|#define GPIO_LED_GREEN_OFF_AMBER_ON&t;0x0080
DECL|macro|GPIO_LED_GREEN_ON_AMBER_ON
mdefine_line|#define GPIO_LED_GREEN_ON_AMBER_ON&t;0x00C0
r_union
(brace
r_struct
(brace
DECL|member|unused_10
r_uint16
id|unused_10
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Gap */
DECL|member|mailbox8
r_volatile
r_uint16
id|mailbox8
suffix:semicolon
DECL|member|mailbox9
r_volatile
r_uint16
id|mailbox9
suffix:semicolon
DECL|member|mailbox10
r_volatile
r_uint16
id|mailbox10
suffix:semicolon
DECL|member|mailbox11
r_volatile
r_uint16
id|mailbox11
suffix:semicolon
DECL|member|mailbox12
r_volatile
r_uint16
id|mailbox12
suffix:semicolon
DECL|member|mailbox13
r_volatile
r_uint16
id|mailbox13
suffix:semicolon
DECL|member|mailbox14
r_volatile
r_uint16
id|mailbox14
suffix:semicolon
DECL|member|mailbox15
r_volatile
r_uint16
id|mailbox15
suffix:semicolon
DECL|member|mailbox16
r_volatile
r_uint16
id|mailbox16
suffix:semicolon
DECL|member|mailbox17
r_volatile
r_uint16
id|mailbox17
suffix:semicolon
DECL|member|mailbox18
r_volatile
r_uint16
id|mailbox18
suffix:semicolon
DECL|member|mailbox19
r_volatile
r_uint16
id|mailbox19
suffix:semicolon
DECL|member|mailbox20
r_volatile
r_uint16
id|mailbox20
suffix:semicolon
DECL|member|mailbox21
r_volatile
r_uint16
id|mailbox21
suffix:semicolon
DECL|member|mailbox22
r_volatile
r_uint16
id|mailbox22
suffix:semicolon
DECL|member|mailbox23
r_volatile
r_uint16
id|mailbox23
suffix:semicolon
multiline_comment|/* Also probe reg. */
DECL|member|isp2200
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
id|isp2200
suffix:semicolon
DECL|member|u_end
)brace
id|u_end
suffix:semicolon
DECL|typedef|device_reg_t
)brace
id|device_reg_t
suffix:semicolon
DECL|macro|ISP_REQ_Q_IN
mdefine_line|#define ISP_REQ_Q_IN(ha, reg) &bslash;&n;&t;(IS_QLA2100(ha) || IS_QLA2200(ha) ? &bslash;&n;&t; &amp;(reg)-&gt;u.isp2100.mailbox4 : &bslash;&n;&t; &amp;(reg)-&gt;u.isp2300.req_q_in)
DECL|macro|ISP_REQ_Q_OUT
mdefine_line|#define ISP_REQ_Q_OUT(ha, reg) &bslash;&n;&t;(IS_QLA2100(ha) || IS_QLA2200(ha) ? &bslash;&n;&t; &amp;(reg)-&gt;u.isp2100.mailbox4 : &bslash;&n;&t; &amp;(reg)-&gt;u.isp2300.req_q_out)
DECL|macro|ISP_RSP_Q_IN
mdefine_line|#define ISP_RSP_Q_IN(ha, reg) &bslash;&n;&t;(IS_QLA2100(ha) || IS_QLA2200(ha) ? &bslash;&n;&t; &amp;(reg)-&gt;u.isp2100.mailbox5 : &bslash;&n;&t; &amp;(reg)-&gt;u.isp2300.rsp_q_in)
DECL|macro|ISP_RSP_Q_OUT
mdefine_line|#define ISP_RSP_Q_OUT(ha, reg) &bslash;&n;&t;(IS_QLA2100(ha) || IS_QLA2200(ha) ? &bslash;&n;&t; &amp;(reg)-&gt;u.isp2100.mailbox5 : &bslash;&n;&t; &amp;(reg)-&gt;u.isp2300.rsp_q_out)
DECL|macro|MAILBOX_REG
mdefine_line|#define MAILBOX_REG(ha, reg, num) &bslash;&n;&t;(IS_QLA2100(ha) || IS_QLA2200(ha) ? &bslash;&n;&t; (num &lt; 8 ? &bslash;&n;&t;  &amp;(reg)-&gt;u.isp2100.mailbox0 + (num) : &bslash;&n;&t;  &amp;(reg)-&gt;u_end.isp2200.mailbox8 + (num) - 8) : &bslash;&n;&t; &amp;(reg)-&gt;u.isp2300.mailbox0 + (num))
DECL|macro|RD_MAILBOX_REG
mdefine_line|#define RD_MAILBOX_REG(ha, reg, num) &bslash;&n;&t;RD_REG_WORD(MAILBOX_REG(ha, reg, num))
DECL|macro|WRT_MAILBOX_REG
mdefine_line|#define WRT_MAILBOX_REG(ha, reg, num, data) &bslash;&n;&t;WRT_REG_WORD(MAILBOX_REG(ha, reg, num), data)
DECL|macro|FB_CMD_REG
mdefine_line|#define FB_CMD_REG(ha, reg) &bslash;&n;&t;(IS_QLA2100(ha) || IS_QLA2200(ha) ? &bslash;&n;&t; &amp;(reg)-&gt;fb_cmd_2100 : &bslash;&n;&t; &amp;(reg)-&gt;u.isp2300.fb_cmd)
DECL|macro|RD_FB_CMD_REG
mdefine_line|#define RD_FB_CMD_REG(ha, reg) &bslash;&n;&t;RD_REG_WORD(FB_CMD_REG(ha, reg))
DECL|macro|WRT_FB_CMD_REG
mdefine_line|#define WRT_FB_CMD_REG(ha, reg, data) &bslash;&n;&t;WRT_REG_WORD(FB_CMD_REG(ha, reg), data)
r_typedef
r_struct
(brace
DECL|member|out_mb
r_uint32
id|out_mb
suffix:semicolon
multiline_comment|/* outbound from driver */
DECL|member|in_mb
r_uint32
id|in_mb
suffix:semicolon
multiline_comment|/* Incoming from RISC */
DECL|member|mb
r_uint16
id|mb
(braket
id|MAILBOX_REGISTER_COUNT
)braket
suffix:semicolon
DECL|member|buf_size
r_int
id|buf_size
suffix:semicolon
DECL|member|bufp
r_void
op_star
id|bufp
suffix:semicolon
DECL|member|tov
r_uint32
id|tov
suffix:semicolon
DECL|member|flags
r_uint8
id|flags
suffix:semicolon
DECL|macro|MBX_DMA_IN
mdefine_line|#define MBX_DMA_IN&t;BIT_0
DECL|macro|MBX_DMA_OUT
mdefine_line|#define&t;MBX_DMA_OUT&t;BIT_1
DECL|macro|IOCTL_CMD
mdefine_line|#define IOCTL_CMD&t;BIT_2
DECL|typedef|mbx_cmd_t
)brace
id|mbx_cmd_t
suffix:semicolon
DECL|macro|MBX_TOV_SECONDS
mdefine_line|#define&t;MBX_TOV_SECONDS&t;30
multiline_comment|/*&n; *  ISP product identification definitions in mailboxes after reset.&n; */
DECL|macro|PROD_ID_1
mdefine_line|#define PROD_ID_1&t;&t;0x4953
DECL|macro|PROD_ID_2
mdefine_line|#define PROD_ID_2&t;&t;0x0000
DECL|macro|PROD_ID_2a
mdefine_line|#define PROD_ID_2a&t;&t;0x5020
DECL|macro|PROD_ID_3
mdefine_line|#define PROD_ID_3&t;&t;0x2020
multiline_comment|/*&n; * ISP mailbox Self-Test status codes&n; */
DECL|macro|MBS_FRM_ALIVE
mdefine_line|#define MBS_FRM_ALIVE&t;&t;0&t;/* Firmware Alive. */
DECL|macro|MBS_CHKSUM_ERR
mdefine_line|#define MBS_CHKSUM_ERR&t;&t;1&t;/* Checksum Error. */
DECL|macro|MBS_BUSY
mdefine_line|#define MBS_BUSY&t;&t;4&t;/* Busy. */
multiline_comment|/*&n; * ISP mailbox command complete status codes&n; */
DECL|macro|MBS_COMMAND_COMPLETE
mdefine_line|#define MBS_COMMAND_COMPLETE&t;&t;0x4000
DECL|macro|MBS_INVALID_COMMAND
mdefine_line|#define MBS_INVALID_COMMAND&t;&t;0x4001
DECL|macro|MBS_HOST_INTERFACE_ERROR
mdefine_line|#define MBS_HOST_INTERFACE_ERROR&t;0x4002
DECL|macro|MBS_TEST_FAILED
mdefine_line|#define MBS_TEST_FAILED&t;&t;&t;0x4003
DECL|macro|MBS_COMMAND_ERROR
mdefine_line|#define MBS_COMMAND_ERROR&t;&t;0x4005
DECL|macro|MBS_COMMAND_PARAMETER_ERROR
mdefine_line|#define MBS_COMMAND_PARAMETER_ERROR&t;0x4006
DECL|macro|MBS_PORT_ID_USED
mdefine_line|#define MBS_PORT_ID_USED&t;&t;0x4007
DECL|macro|MBS_LOOP_ID_USED
mdefine_line|#define MBS_LOOP_ID_USED&t;&t;0x4008
DECL|macro|MBS_ALL_IDS_IN_USE
mdefine_line|#define MBS_ALL_IDS_IN_USE&t;&t;0x4009
DECL|macro|MBS_NOT_LOGGED_IN
mdefine_line|#define MBS_NOT_LOGGED_IN&t;&t;0x400A
multiline_comment|/*&n; * ISP mailbox asynchronous event status codes&n; */
DECL|macro|MBA_ASYNC_EVENT
mdefine_line|#define MBA_ASYNC_EVENT&t;&t;0x8000&t;/* Asynchronous event. */
DECL|macro|MBA_RESET
mdefine_line|#define MBA_RESET&t;&t;0x8001&t;/* Reset Detected. */
DECL|macro|MBA_SYSTEM_ERR
mdefine_line|#define MBA_SYSTEM_ERR&t;&t;0x8002&t;/* System Error. */
DECL|macro|MBA_REQ_TRANSFER_ERR
mdefine_line|#define MBA_REQ_TRANSFER_ERR&t;0x8003&t;/* Request Transfer Error. */
DECL|macro|MBA_RSP_TRANSFER_ERR
mdefine_line|#define MBA_RSP_TRANSFER_ERR&t;0x8004&t;/* Response Transfer Error. */
DECL|macro|MBA_WAKEUP_THRES
mdefine_line|#define MBA_WAKEUP_THRES&t;0x8005&t;/* Request Queue Wake-up. */
DECL|macro|MBA_LIP_OCCURRED
mdefine_line|#define MBA_LIP_OCCURRED&t;0x8010&t;/* Loop Initialization Procedure */
multiline_comment|/* occurred. */
DECL|macro|MBA_LOOP_UP
mdefine_line|#define MBA_LOOP_UP&t;&t;0x8011&t;/* FC Loop UP. */
DECL|macro|MBA_LOOP_DOWN
mdefine_line|#define MBA_LOOP_DOWN&t;&t;0x8012&t;/* FC Loop Down. */
DECL|macro|MBA_LIP_RESET
mdefine_line|#define MBA_LIP_RESET&t;&t;0x8013&t;/* LIP reset occurred. */
DECL|macro|MBA_PORT_UPDATE
mdefine_line|#define MBA_PORT_UPDATE&t;&t;0x8014&t;/* Port Database update. */
DECL|macro|MBA_RSCN_UPDATE
mdefine_line|#define MBA_RSCN_UPDATE&t;&t;0x8015&t;/* Register State Chg Notification. */
DECL|macro|MBA_LIP_F8
mdefine_line|#define MBA_LIP_F8&t;&t;0x8016&t;/* Received a LIP F8. */
DECL|macro|MBA_LOOP_INIT_ERR
mdefine_line|#define MBA_LOOP_INIT_ERR&t;0x8017&t;/* Loop Initialization Error. */
DECL|macro|MBA_FABRIC_AUTH_REQ
mdefine_line|#define MBA_FABRIC_AUTH_REQ&t;0x801b&t;/* Fabric Authentication Required. */
DECL|macro|MBA_SCSI_COMPLETION
mdefine_line|#define MBA_SCSI_COMPLETION&t;0x8020&t;/* SCSI Command Complete. */
DECL|macro|MBA_CTIO_COMPLETION
mdefine_line|#define MBA_CTIO_COMPLETION&t;0x8021&t;/* CTIO Complete. */
DECL|macro|MBA_IP_COMPLETION
mdefine_line|#define MBA_IP_COMPLETION&t;0x8022&t;/* IP Transmit Command Complete. */
DECL|macro|MBA_IP_RECEIVE
mdefine_line|#define MBA_IP_RECEIVE&t;&t;0x8023&t;/* IP Received. */
DECL|macro|MBA_IP_BROADCAST
mdefine_line|#define MBA_IP_BROADCAST&t;0x8024&t;/* IP Broadcast Received. */
DECL|macro|MBA_IP_LOW_WATER_MARK
mdefine_line|#define MBA_IP_LOW_WATER_MARK&t;0x8025&t;/* IP Low Water Mark reached. */
DECL|macro|MBA_IP_RCV_BUFFER_EMPTY
mdefine_line|#define MBA_IP_RCV_BUFFER_EMPTY 0x8026&t;/* IP receive buffer queue empty. */
DECL|macro|MBA_IP_HDR_DATA_SPLIT
mdefine_line|#define MBA_IP_HDR_DATA_SPLIT&t;0x8027&t;/* IP header/data splitting feature */
multiline_comment|/* used. */
DECL|macro|MBA_POINT_TO_POINT
mdefine_line|#define MBA_POINT_TO_POINT&t;0x8030&t;/* Point to point mode. */
DECL|macro|MBA_CMPLT_1_16BIT
mdefine_line|#define MBA_CMPLT_1_16BIT&t;0x8031&t;/* Completion 1 16bit IOSB. */
DECL|macro|MBA_CMPLT_2_16BIT
mdefine_line|#define MBA_CMPLT_2_16BIT&t;0x8032&t;/* Completion 2 16bit IOSB. */
DECL|macro|MBA_CMPLT_3_16BIT
mdefine_line|#define MBA_CMPLT_3_16BIT&t;0x8033&t;/* Completion 3 16bit IOSB. */
DECL|macro|MBA_CMPLT_4_16BIT
mdefine_line|#define MBA_CMPLT_4_16BIT&t;0x8034&t;/* Completion 4 16bit IOSB. */
DECL|macro|MBA_CMPLT_5_16BIT
mdefine_line|#define MBA_CMPLT_5_16BIT&t;0x8035&t;/* Completion 5 16bit IOSB. */
DECL|macro|MBA_CHG_IN_CONNECTION
mdefine_line|#define MBA_CHG_IN_CONNECTION&t;0x8036&t;/* Change in connection mode. */
DECL|macro|MBA_RIO_RESPONSE
mdefine_line|#define MBA_RIO_RESPONSE&t;0x8040&t;/* RIO response queue update. */
DECL|macro|MBA_ZIO_RESPONSE
mdefine_line|#define MBA_ZIO_RESPONSE&t;0x8040&t;/* ZIO response queue update. */
DECL|macro|MBA_CMPLT_2_32BIT
mdefine_line|#define MBA_CMPLT_2_32BIT&t;0x8042&t;/* Completion 2 32bit IOSB. */
DECL|macro|MBA_BYPASS_NOTIFICATION
mdefine_line|#define MBA_BYPASS_NOTIFICATION&t;0x8043&t;/* Auto bypass notification. */
DECL|macro|MBA_DISCARD_RND_FRAME
mdefine_line|#define MBA_DISCARD_RND_FRAME&t;0x8048&t;/* discard RND frame due to error. */
DECL|macro|MBA_REJECTED_FCP_CMD
mdefine_line|#define MBA_REJECTED_FCP_CMD&t;0x8049&t;/* rejected FCP_CMD. */
multiline_comment|/*&n; * Firmware options 1, 2, 3.&n; */
DECL|macro|FO1_AE_ON_LIPF8
mdefine_line|#define FO1_AE_ON_LIPF8&t;&t;&t;BIT_0
DECL|macro|FO1_AE_ALL_LIP_RESET
mdefine_line|#define FO1_AE_ALL_LIP_RESET&t;&t;BIT_1
DECL|macro|FO1_CTIO_RETRY
mdefine_line|#define FO1_CTIO_RETRY&t;&t;&t;BIT_3
DECL|macro|FO1_DISABLE_LIP_F7_SW
mdefine_line|#define FO1_DISABLE_LIP_F7_SW&t;&t;BIT_4
DECL|macro|FO1_DISABLE_100MS_LOS_WAIT
mdefine_line|#define FO1_DISABLE_100MS_LOS_WAIT&t;BIT_5
DECL|macro|FO1_DISABLE_GPIO6_7
mdefine_line|#define FO1_DISABLE_GPIO6_7&t;&t;BIT_6
DECL|macro|FO1_AE_ON_LOOP_INIT_ERR
mdefine_line|#define FO1_AE_ON_LOOP_INIT_ERR&t;&t;BIT_7
DECL|macro|FO1_SET_EMPHASIS_SWING
mdefine_line|#define FO1_SET_EMPHASIS_SWING&t;&t;BIT_8
DECL|macro|FO1_AE_AUTO_BYPASS
mdefine_line|#define FO1_AE_AUTO_BYPASS&t;&t;BIT_9
DECL|macro|FO1_ENABLE_PURE_IOCB
mdefine_line|#define FO1_ENABLE_PURE_IOCB&t;&t;BIT_10
DECL|macro|FO1_AE_PLOGI_RJT
mdefine_line|#define FO1_AE_PLOGI_RJT&t;&t;BIT_11
DECL|macro|FO1_ENABLE_ABORT_SEQUENCE
mdefine_line|#define FO1_ENABLE_ABORT_SEQUENCE&t;BIT_12
DECL|macro|FO1_AE_QUEUE_FULL
mdefine_line|#define FO1_AE_QUEUE_FULL&t;&t;BIT_13
DECL|macro|FO2_ENABLE_ATIO_TYPE_3
mdefine_line|#define FO2_ENABLE_ATIO_TYPE_3&t;&t;BIT_0
DECL|macro|FO2_REV_LOOPBACK
mdefine_line|#define FO2_REV_LOOPBACK&t;&t;BIT_1
DECL|macro|FO3_ENABLE_EMERG_IOCB
mdefine_line|#define FO3_ENABLE_EMERG_IOCB&t;&t;BIT_0
DECL|macro|FO3_AE_RND_ERROR
mdefine_line|#define FO3_AE_RND_ERROR&t;&t;BIT_1
multiline_comment|/*&n; * ISP mailbox commands&n; */
DECL|macro|MBC_LOAD_RAM
mdefine_line|#define MBC_LOAD_RAM&t;&t;&t;1&t;/* Load RAM. */
DECL|macro|MBC_EXECUTE_FIRMWARE
mdefine_line|#define MBC_EXECUTE_FIRMWARE&t;&t;2&t;/* Execute firmware. */
DECL|macro|MBC_WRITE_RAM_WORD
mdefine_line|#define MBC_WRITE_RAM_WORD&t;&t;4&t;/* Write RAM word. */
DECL|macro|MBC_READ_RAM_WORD
mdefine_line|#define MBC_READ_RAM_WORD&t;&t;5&t;/* Read RAM word. */
DECL|macro|MBC_MAILBOX_REGISTER_TEST
mdefine_line|#define MBC_MAILBOX_REGISTER_TEST&t;6&t;/* Wrap incoming mailboxes */
DECL|macro|MBC_VERIFY_CHECKSUM
mdefine_line|#define MBC_VERIFY_CHECKSUM&t;&t;7&t;/* Verify checksum. */
DECL|macro|MBC_GET_FIRMWARE_VERSION
mdefine_line|#define MBC_GET_FIRMWARE_VERSION&t;8&t;/* Get firmware revision. */
DECL|macro|MBC_LOAD_RISC_RAM
mdefine_line|#define MBC_LOAD_RISC_RAM&t;&t;9&t;/* Load RAM command. */
DECL|macro|MBC_DUMP_RISC_RAM
mdefine_line|#define MBC_DUMP_RISC_RAM&t;&t;0xa&t;/* Dump RAM command. */
DECL|macro|MBC_LOAD_RISC_RAM_EXTENDED
mdefine_line|#define MBC_LOAD_RISC_RAM_EXTENDED&t;0xb&t;/* Load RAM extended. */
DECL|macro|MBC_DUMP_RISC_RAM_EXTENDED
mdefine_line|#define MBC_DUMP_RISC_RAM_EXTENDED&t;0xc&t;/* Dump RAM extended. */
DECL|macro|MBC_WRITE_RAM_WORD_EXTENDED
mdefine_line|#define MBC_WRITE_RAM_WORD_EXTENDED&t;0xd&t;/* Write RAM word extended */
DECL|macro|MBC_READ_RAM_EXTENDED
mdefine_line|#define MBC_READ_RAM_EXTENDED&t;&t;0xf&t;/* Read RAM extended. */
DECL|macro|MBC_IOCB_COMMAND
mdefine_line|#define MBC_IOCB_COMMAND&t;&t;0x12&t;/* Execute IOCB command. */
DECL|macro|MBC_ABORT_COMMAND
mdefine_line|#define MBC_ABORT_COMMAND&t;&t;0x15&t;/* Abort IOCB command. */
DECL|macro|MBC_ABORT_DEVICE
mdefine_line|#define MBC_ABORT_DEVICE&t;&t;0x16&t;/* Abort device (ID/LUN). */
DECL|macro|MBC_ABORT_TARGET
mdefine_line|#define MBC_ABORT_TARGET&t;&t;0x17&t;/* Abort target (ID). */
DECL|macro|MBC_RESET
mdefine_line|#define MBC_RESET&t;&t;&t;0x18&t;/* Reset. */
DECL|macro|MBC_GET_ADAPTER_LOOP_ID
mdefine_line|#define MBC_GET_ADAPTER_LOOP_ID&t;&t;0x20&t;/* Get loop id of ISP2200. */
DECL|macro|MBC_GET_RETRY_COUNT
mdefine_line|#define MBC_GET_RETRY_COUNT&t;&t;0x22&t;/* Get f/w retry cnt/delay. */
DECL|macro|MBC_DISABLE_VI
mdefine_line|#define MBC_DISABLE_VI&t;&t;&t;0x24&t;/* Disable VI operation. */
DECL|macro|MBC_ENABLE_VI
mdefine_line|#define MBC_ENABLE_VI&t;&t;&t;0x25&t;/* Enable VI operation. */
DECL|macro|MBC_GET_FIRMWARE_OPTION
mdefine_line|#define MBC_GET_FIRMWARE_OPTION&t;&t;0x28&t;/* Get Firmware Options. */
DECL|macro|MBC_SET_FIRMWARE_OPTION
mdefine_line|#define MBC_SET_FIRMWARE_OPTION&t;&t;0x38&t;/* Set Firmware Options. */
DECL|macro|MBC_LOOP_PORT_BYPASS
mdefine_line|#define MBC_LOOP_PORT_BYPASS&t;&t;0x40&t;/* Loop Port Bypass. */
DECL|macro|MBC_LOOP_PORT_ENABLE
mdefine_line|#define MBC_LOOP_PORT_ENABLE&t;&t;0x41&t;/* Loop Port Enable. */
DECL|macro|MBC_GET_RESOURCE_COUNTS
mdefine_line|#define MBC_GET_RESOURCE_COUNTS&t;&t;0x42&t;/* Get Resource Counts. */
DECL|macro|MBC_NON_PARTICIPATE
mdefine_line|#define MBC_NON_PARTICIPATE&t;&t;0x43&t;/* Non-Participating Mode. */
DECL|macro|MBC_DIAGNOSTIC_ECHO
mdefine_line|#define MBC_DIAGNOSTIC_ECHO&t;&t;0x44&t;/* Diagnostic echo. */
DECL|macro|MBC_DIAGNOSTIC_LOOP_BACK
mdefine_line|#define MBC_DIAGNOSTIC_LOOP_BACK&t;0x45&t;/* Diagnostic loop back. */
DECL|macro|MBC_ONLINE_SELF_TEST
mdefine_line|#define MBC_ONLINE_SELF_TEST&t;&t;0x46&t;/* Online self-test. */
DECL|macro|MBC_ENHANCED_GET_PORT_DATABASE
mdefine_line|#define MBC_ENHANCED_GET_PORT_DATABASE&t;0x47&t;/* Get port database + login */
DECL|macro|MBC_RESET_LINK_STATUS
mdefine_line|#define MBC_RESET_LINK_STATUS&t;&t;0x52&t;/* Reset Link Error Status */
DECL|macro|MBC_IOCB_COMMAND_A64
mdefine_line|#define MBC_IOCB_COMMAND_A64&t;&t;0x54&t;/* Execute IOCB command (64) */
DECL|macro|MBC_SEND_RNID_ELS
mdefine_line|#define MBC_SEND_RNID_ELS&t;&t;0x57&t;/* Send RNID ELS request */
DECL|macro|MBC_SET_RNID_PARAMS
mdefine_line|#define MBC_SET_RNID_PARAMS&t;&t;0x59&t;/* Set RNID parameters */
DECL|macro|MBC_GET_RNID_PARAMS
mdefine_line|#define MBC_GET_RNID_PARAMS&t;&t;0x5a&t;/* Data Rate */
DECL|macro|MBC_DATA_RATE
mdefine_line|#define MBC_DATA_RATE&t;&t;&t;0x5d&t;/* Get RNID parameters */
DECL|macro|MBC_INITIALIZE_FIRMWARE
mdefine_line|#define MBC_INITIALIZE_FIRMWARE&t;&t;0x60&t;/* Initialize firmware */
DECL|macro|MBC_INITIATE_LIP
mdefine_line|#define MBC_INITIATE_LIP&t;&t;0x62&t;/* Initiate Loop */
multiline_comment|/* Initialization Procedure */
DECL|macro|MBC_GET_FC_AL_POSITION_MAP
mdefine_line|#define MBC_GET_FC_AL_POSITION_MAP&t;0x63&t;/* Get FC_AL Position Map. */
DECL|macro|MBC_GET_PORT_DATABASE
mdefine_line|#define MBC_GET_PORT_DATABASE&t;&t;0x64&t;/* Get Port Database. */
DECL|macro|MBC_CLEAR_ACA
mdefine_line|#define MBC_CLEAR_ACA&t;&t;&t;0x65&t;/* Clear ACA. */
DECL|macro|MBC_TARGET_RESET
mdefine_line|#define MBC_TARGET_RESET&t;&t;0x66&t;/* Target Reset. */
DECL|macro|MBC_CLEAR_TASK_SET
mdefine_line|#define MBC_CLEAR_TASK_SET&t;&t;0x67&t;/* Clear Task Set. */
DECL|macro|MBC_ABORT_TASK_SET
mdefine_line|#define MBC_ABORT_TASK_SET&t;&t;0x68&t;/* Abort Task Set. */
DECL|macro|MBC_GET_FIRMWARE_STATE
mdefine_line|#define MBC_GET_FIRMWARE_STATE&t;&t;0x69&t;/* Get firmware state. */
DECL|macro|MBC_GET_PORT_NAME
mdefine_line|#define MBC_GET_PORT_NAME&t;&t;0x6a&t;/* Get port name. */
DECL|macro|MBC_GET_LINK_STATUS
mdefine_line|#define MBC_GET_LINK_STATUS&t;&t;0x6b&t;/* Get port link status. */
DECL|macro|MBC_LIP_RESET
mdefine_line|#define MBC_LIP_RESET&t;&t;&t;0x6c&t;/* LIP reset. */
DECL|macro|MBC_SEND_SNS_COMMAND
mdefine_line|#define MBC_SEND_SNS_COMMAND&t;&t;0x6e&t;/* Send Simple Name Server */
multiline_comment|/* commandd. */
DECL|macro|MBC_LOGIN_FABRIC_PORT
mdefine_line|#define MBC_LOGIN_FABRIC_PORT&t;&t;0x6f&t;/* Login fabric port. */
DECL|macro|MBC_SEND_CHANGE_REQUEST
mdefine_line|#define MBC_SEND_CHANGE_REQUEST&t;&t;0x70&t;/* Send Change Request. */
DECL|macro|MBC_LOGOUT_FABRIC_PORT
mdefine_line|#define MBC_LOGOUT_FABRIC_PORT&t;&t;0x71&t;/* Logout fabric port. */
DECL|macro|MBC_LIP_FULL_LOGIN
mdefine_line|#define MBC_LIP_FULL_LOGIN&t;&t;0x72&t;/* Full login LIP. */
DECL|macro|MBC_LOGIN_LOOP_PORT
mdefine_line|#define MBC_LOGIN_LOOP_PORT&t;&t;0x74&t;/* Login Loop Port. */
DECL|macro|MBC_PORT_NODE_NAME_LIST
mdefine_line|#define MBC_PORT_NODE_NAME_LIST&t;&t;0x75&t;/* Get port/node name list. */
DECL|macro|MBC_INITIALIZE_RECEIVE_QUEUE
mdefine_line|#define MBC_INITIALIZE_RECEIVE_QUEUE&t;0x77&t;/* Initialize receive queue */
DECL|macro|MBC_UNLOAD_IP
mdefine_line|#define MBC_UNLOAD_IP&t;&t;&t;0x79&t;/* Shutdown IP */
DECL|macro|MBC_GET_ID_LIST
mdefine_line|#define MBC_GET_ID_LIST&t;&t;&t;0x7C&t;/* Get Port ID list. */
DECL|macro|MBC_SEND_LFA_COMMAND
mdefine_line|#define MBC_SEND_LFA_COMMAND&t;&t;0x7D&t;/* Send Loop Fabric Address */
DECL|macro|MBC_LUN_RESET
mdefine_line|#define MBC_LUN_RESET&t;&t;&t;0x7E&t;/* Send LUN reset */
multiline_comment|/* Firmware return data sizes */
DECL|macro|FCAL_MAP_SIZE
mdefine_line|#define FCAL_MAP_SIZE&t;128
multiline_comment|/* Mailbox bit definitions for out_mb and in_mb */
DECL|macro|MBX_31
mdefine_line|#define&t;MBX_31&t;&t;BIT_31
DECL|macro|MBX_30
mdefine_line|#define&t;MBX_30&t;&t;BIT_30
DECL|macro|MBX_29
mdefine_line|#define&t;MBX_29&t;&t;BIT_29
DECL|macro|MBX_28
mdefine_line|#define&t;MBX_28&t;&t;BIT_28
DECL|macro|MBX_27
mdefine_line|#define&t;MBX_27&t;&t;BIT_27
DECL|macro|MBX_26
mdefine_line|#define&t;MBX_26&t;&t;BIT_26
DECL|macro|MBX_25
mdefine_line|#define&t;MBX_25&t;&t;BIT_25
DECL|macro|MBX_24
mdefine_line|#define&t;MBX_24&t;&t;BIT_24
DECL|macro|MBX_23
mdefine_line|#define&t;MBX_23&t;&t;BIT_23
DECL|macro|MBX_22
mdefine_line|#define&t;MBX_22&t;&t;BIT_22
DECL|macro|MBX_21
mdefine_line|#define&t;MBX_21&t;&t;BIT_21
DECL|macro|MBX_20
mdefine_line|#define&t;MBX_20&t;&t;BIT_20
DECL|macro|MBX_19
mdefine_line|#define&t;MBX_19&t;&t;BIT_19
DECL|macro|MBX_18
mdefine_line|#define&t;MBX_18&t;&t;BIT_18
DECL|macro|MBX_17
mdefine_line|#define&t;MBX_17&t;&t;BIT_17
DECL|macro|MBX_16
mdefine_line|#define&t;MBX_16&t;&t;BIT_16
DECL|macro|MBX_15
mdefine_line|#define&t;MBX_15&t;&t;BIT_15
DECL|macro|MBX_14
mdefine_line|#define&t;MBX_14&t;&t;BIT_14
DECL|macro|MBX_13
mdefine_line|#define&t;MBX_13&t;&t;BIT_13
DECL|macro|MBX_12
mdefine_line|#define&t;MBX_12&t;&t;BIT_12
DECL|macro|MBX_11
mdefine_line|#define&t;MBX_11&t;&t;BIT_11
DECL|macro|MBX_10
mdefine_line|#define&t;MBX_10&t;&t;BIT_10
DECL|macro|MBX_9
mdefine_line|#define&t;MBX_9&t;&t;BIT_9
DECL|macro|MBX_8
mdefine_line|#define&t;MBX_8&t;&t;BIT_8
DECL|macro|MBX_7
mdefine_line|#define&t;MBX_7&t;&t;BIT_7
DECL|macro|MBX_6
mdefine_line|#define&t;MBX_6&t;&t;BIT_6
DECL|macro|MBX_5
mdefine_line|#define&t;MBX_5&t;&t;BIT_5
DECL|macro|MBX_4
mdefine_line|#define&t;MBX_4&t;&t;BIT_4
DECL|macro|MBX_3
mdefine_line|#define&t;MBX_3&t;&t;BIT_3
DECL|macro|MBX_2
mdefine_line|#define&t;MBX_2&t;&t;BIT_2
DECL|macro|MBX_1
mdefine_line|#define&t;MBX_1&t;&t;BIT_1
DECL|macro|MBX_0
mdefine_line|#define&t;MBX_0&t;&t;BIT_0
multiline_comment|/*&n; * Firmware state codes from get firmware state mailbox command&n; */
DECL|macro|FSTATE_CONFIG_WAIT
mdefine_line|#define FSTATE_CONFIG_WAIT      0
DECL|macro|FSTATE_WAIT_AL_PA
mdefine_line|#define FSTATE_WAIT_AL_PA       1
DECL|macro|FSTATE_WAIT_LOGIN
mdefine_line|#define FSTATE_WAIT_LOGIN       2
DECL|macro|FSTATE_READY
mdefine_line|#define FSTATE_READY            3
DECL|macro|FSTATE_LOSS_OF_SYNC
mdefine_line|#define FSTATE_LOSS_OF_SYNC     4
DECL|macro|FSTATE_ERROR
mdefine_line|#define FSTATE_ERROR            5
DECL|macro|FSTATE_REINIT
mdefine_line|#define FSTATE_REINIT           6
DECL|macro|FSTATE_NON_PART
mdefine_line|#define FSTATE_NON_PART         7
DECL|macro|FSTATE_CONFIG_CORRECT
mdefine_line|#define FSTATE_CONFIG_CORRECT      0
DECL|macro|FSTATE_P2P_RCV_LIP
mdefine_line|#define FSTATE_P2P_RCV_LIP         1
DECL|macro|FSTATE_P2P_CHOOSE_LOOP
mdefine_line|#define FSTATE_P2P_CHOOSE_LOOP     2
DECL|macro|FSTATE_P2P_RCV_UNIDEN_LIP
mdefine_line|#define FSTATE_P2P_RCV_UNIDEN_LIP  3
DECL|macro|FSTATE_FATAL_ERROR
mdefine_line|#define FSTATE_FATAL_ERROR         4
DECL|macro|FSTATE_LOOP_BACK_CONN
mdefine_line|#define FSTATE_LOOP_BACK_CONN      5
multiline_comment|/*&n; * Port Database structure definition&n; * Little endian except where noted.&n; */
DECL|macro|PORT_DATABASE_SIZE
mdefine_line|#define&t;PORT_DATABASE_SIZE&t;128&t;/* bytes */
r_typedef
r_struct
(brace
DECL|member|options
r_uint8
id|options
suffix:semicolon
DECL|member|control
r_uint8
id|control
suffix:semicolon
DECL|member|master_state
r_uint8
id|master_state
suffix:semicolon
DECL|member|slave_state
r_uint8
id|slave_state
suffix:semicolon
DECL|member|reserved
r_uint8
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|hard_address
r_uint8
id|hard_address
suffix:semicolon
DECL|member|reserved_1
r_uint8
id|reserved_1
suffix:semicolon
DECL|member|port_id
r_uint8
id|port_id
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|node_name
r_uint8
id|node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|port_name
r_uint8
id|port_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|execution_throttle
r_uint16
id|execution_throttle
suffix:semicolon
DECL|member|execution_count
r_uint16
id|execution_count
suffix:semicolon
DECL|member|reset_count
r_uint8
id|reset_count
suffix:semicolon
DECL|member|reserved_2
r_uint8
id|reserved_2
suffix:semicolon
DECL|member|resource_allocation
r_uint16
id|resource_allocation
suffix:semicolon
DECL|member|current_allocation
r_uint16
id|current_allocation
suffix:semicolon
DECL|member|queue_head
r_uint16
id|queue_head
suffix:semicolon
DECL|member|queue_tail
r_uint16
id|queue_tail
suffix:semicolon
DECL|member|transmit_execution_list_next
r_uint16
id|transmit_execution_list_next
suffix:semicolon
DECL|member|transmit_execution_list_previous
r_uint16
id|transmit_execution_list_previous
suffix:semicolon
DECL|member|common_features
r_uint16
id|common_features
suffix:semicolon
DECL|member|total_concurrent_sequences
r_uint16
id|total_concurrent_sequences
suffix:semicolon
DECL|member|RO_by_information_category
r_uint16
id|RO_by_information_category
suffix:semicolon
DECL|member|recipient
r_uint8
id|recipient
suffix:semicolon
DECL|member|initiator
r_uint8
id|initiator
suffix:semicolon
DECL|member|receive_data_size
r_uint16
id|receive_data_size
suffix:semicolon
DECL|member|concurrent_sequences
r_uint16
id|concurrent_sequences
suffix:semicolon
DECL|member|open_sequences_per_exchange
r_uint16
id|open_sequences_per_exchange
suffix:semicolon
DECL|member|lun_abort_flags
r_uint16
id|lun_abort_flags
suffix:semicolon
DECL|member|lun_stop_flags
r_uint16
id|lun_stop_flags
suffix:semicolon
DECL|member|stop_queue_head
r_uint16
id|stop_queue_head
suffix:semicolon
DECL|member|stop_queue_tail
r_uint16
id|stop_queue_tail
suffix:semicolon
DECL|member|port_retry_timer
r_uint16
id|port_retry_timer
suffix:semicolon
DECL|member|next_sequence_id
r_uint16
id|next_sequence_id
suffix:semicolon
DECL|member|frame_count
r_uint16
id|frame_count
suffix:semicolon
DECL|member|PRLI_payload_length
r_uint16
id|PRLI_payload_length
suffix:semicolon
DECL|member|prli_svc_param_word_0
r_uint8
id|prli_svc_param_word_0
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Big endian */
multiline_comment|/* Bits 15-0 of word 0 */
DECL|member|prli_svc_param_word_3
r_uint8
id|prli_svc_param_word_3
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Big endian */
multiline_comment|/* Bits 15-0 of word 3 */
DECL|member|loop_id
r_uint16
id|loop_id
suffix:semicolon
DECL|member|extended_lun_info_list_pointer
r_uint16
id|extended_lun_info_list_pointer
suffix:semicolon
DECL|member|extended_lun_stop_list_pointer
r_uint16
id|extended_lun_stop_list_pointer
suffix:semicolon
DECL|typedef|port_database_t
)brace
id|port_database_t
suffix:semicolon
multiline_comment|/*&n; * Port database slave/master states&n; */
DECL|macro|PD_STATE_DISCOVERY
mdefine_line|#define PD_STATE_DISCOVERY&t;&t;&t;0
DECL|macro|PD_STATE_WAIT_DISCOVERY_ACK
mdefine_line|#define PD_STATE_WAIT_DISCOVERY_ACK&t;&t;1
DECL|macro|PD_STATE_PORT_LOGIN
mdefine_line|#define PD_STATE_PORT_LOGIN&t;&t;&t;2
DECL|macro|PD_STATE_WAIT_PORT_LOGIN_ACK
mdefine_line|#define PD_STATE_WAIT_PORT_LOGIN_ACK&t;&t;3
DECL|macro|PD_STATE_PROCESS_LOGIN
mdefine_line|#define PD_STATE_PROCESS_LOGIN&t;&t;&t;4
DECL|macro|PD_STATE_WAIT_PROCESS_LOGIN_ACK
mdefine_line|#define PD_STATE_WAIT_PROCESS_LOGIN_ACK&t;&t;5
DECL|macro|PD_STATE_PORT_LOGGED_IN
mdefine_line|#define PD_STATE_PORT_LOGGED_IN&t;&t;&t;6
DECL|macro|PD_STATE_PORT_UNAVAILABLE
mdefine_line|#define PD_STATE_PORT_UNAVAILABLE&t;&t;7
DECL|macro|PD_STATE_PROCESS_LOGOUT
mdefine_line|#define PD_STATE_PROCESS_LOGOUT&t;&t;&t;8
DECL|macro|PD_STATE_WAIT_PROCESS_LOGOUT_ACK
mdefine_line|#define PD_STATE_WAIT_PROCESS_LOGOUT_ACK&t;9
DECL|macro|PD_STATE_PORT_LOGOUT
mdefine_line|#define PD_STATE_PORT_LOGOUT&t;&t;&t;10
DECL|macro|PD_STATE_WAIT_PORT_LOGOUT_ACK
mdefine_line|#define PD_STATE_WAIT_PORT_LOGOUT_ACK&t;&t;11
multiline_comment|/*&n; * ISP Initialization Control Block.&n; * Little endian except where noted.&n; */
DECL|macro|ICB_VERSION
mdefine_line|#define&t;ICB_VERSION 1
r_typedef
r_struct
(brace
DECL|member|version
r_uint8
id|version
suffix:semicolon
DECL|member|reserved_1
r_uint8
id|reserved_1
suffix:semicolon
multiline_comment|/*&n;&t; * LSB BIT 0  = Enable Hard Loop Id&n;&t; * LSB BIT 1  = Enable Fairness&n;&t; * LSB BIT 2  = Enable Full-Duplex&n;&t; * LSB BIT 3  = Enable Fast Posting&n;&t; * LSB BIT 4  = Enable Target Mode&n;&t; * LSB BIT 5  = Disable Initiator Mode&n;&t; * LSB BIT 6  = Enable ADISC&n;&t; * LSB BIT 7  = Enable Target Inquiry Data&n;&t; *&n;&t; * MSB BIT 0  = Enable PDBC Notify&n;&t; * MSB BIT 1  = Non Participating LIP&n;&t; * MSB BIT 2  = Descending Loop ID Search&n;&t; * MSB BIT 3  = Acquire Loop ID in LIPA&n;&t; * MSB BIT 4  = Stop PortQ on Full Status&n;&t; * MSB BIT 5  = Full Login after LIP&n;&t; * MSB BIT 6  = Node Name Option&n;&t; * MSB BIT 7  = Ext IFWCB enable bit&n;&t; */
DECL|member|firmware_options
r_uint8
id|firmware_options
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|frame_payload_size
r_uint16
id|frame_payload_size
suffix:semicolon
DECL|member|max_iocb_allocation
r_uint16
id|max_iocb_allocation
suffix:semicolon
DECL|member|execution_throttle
r_uint16
id|execution_throttle
suffix:semicolon
DECL|member|retry_count
r_uint8
id|retry_count
suffix:semicolon
DECL|member|retry_delay
r_uint8
id|retry_delay
suffix:semicolon
multiline_comment|/* unused */
DECL|member|port_name
r_uint8
id|port_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
multiline_comment|/* Big endian. */
DECL|member|hard_address
r_uint16
id|hard_address
suffix:semicolon
DECL|member|inquiry_data
r_uint8
id|inquiry_data
suffix:semicolon
DECL|member|login_timeout
r_uint8
id|login_timeout
suffix:semicolon
DECL|member|node_name
r_uint8
id|node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
multiline_comment|/* Big endian. */
DECL|member|request_q_outpointer
r_uint16
id|request_q_outpointer
suffix:semicolon
DECL|member|response_q_inpointer
r_uint16
id|response_q_inpointer
suffix:semicolon
DECL|member|request_q_length
r_uint16
id|request_q_length
suffix:semicolon
DECL|member|response_q_length
r_uint16
id|response_q_length
suffix:semicolon
DECL|member|request_q_address
r_uint32
id|request_q_address
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|response_q_address
r_uint32
id|response_q_address
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|lun_enables
r_uint16
id|lun_enables
suffix:semicolon
DECL|member|command_resource_count
r_uint8
id|command_resource_count
suffix:semicolon
DECL|member|immediate_notify_resource_count
r_uint8
id|immediate_notify_resource_count
suffix:semicolon
DECL|member|timeout
r_uint16
id|timeout
suffix:semicolon
DECL|member|reserved_2
r_uint8
id|reserved_2
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * LSB BIT 0 = Timer Operation mode bit 0&n;&t; * LSB BIT 1 = Timer Operation mode bit 1&n;&t; * LSB BIT 2 = Timer Operation mode bit 2&n;&t; * LSB BIT 3 = Timer Operation mode bit 3&n;&t; * LSB BIT 4 = Init Config Mode bit 0&n;&t; * LSB BIT 5 = Init Config Mode bit 1&n;&t; * LSB BIT 6 = Init Config Mode bit 2&n;&t; * LSB BIT 7 = Enable Non part on LIHA failure&n;&t; *&n;&t; * MSB BIT 0 = Enable class 2&n;&t; * MSB BIT 1 = Enable ACK0&n;&t; * MSB BIT 2 =&n;&t; * MSB BIT 3 =&n;&t; * MSB BIT 4 = FC Tape Enable&n;&t; * MSB BIT 5 = Enable FC Confirm&n;&t; * MSB BIT 6 = Enable command queuing in target mode&n;&t; * MSB BIT 7 = No Logo On Link Down&n;&t; */
DECL|member|add_firmware_options
r_uint8
id|add_firmware_options
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|response_accumulation_timer
r_uint8
id|response_accumulation_timer
suffix:semicolon
DECL|member|interrupt_delay_timer
r_uint8
id|interrupt_delay_timer
suffix:semicolon
multiline_comment|/*&n;&t; * LSB BIT 0 = Enable Read xfr_rdy&n;&t; * LSB BIT 1 = Soft ID only&n;&t; * LSB BIT 2 =&n;&t; * LSB BIT 3 =&n;&t; * LSB BIT 4 = FCP RSP Payload [0]&n;&t; * LSB BIT 5 = FCP RSP Payload [1] / Sbus enable - 2200&n;&t; * LSB BIT 6 = Enable Out-of-Order frame handling&n;&t; * LSB BIT 7 = Disable Automatic PLOGI on Local Loop&n;&t; *&n;&t; * MSB BIT 0 = Sbus enable - 2300&n;&t; * MSB BIT 1 =&n;&t; * MSB BIT 2 =&n;&t; * MSB BIT 3 =&n;&t; * MSB BIT 4 =&n;&t; * MSB BIT 5 = enable 50 ohm termination&n;&t; * MSB BIT 6 = Data Rate (2300 only)&n;&t; * MSB BIT 7 = Data Rate (2300 only)&n;&t; */
DECL|member|special_options
r_uint8
id|special_options
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|reserved_3
r_uint8
id|reserved_3
(braket
l_int|26
)braket
suffix:semicolon
DECL|typedef|init_cb_t
)brace
id|init_cb_t
suffix:semicolon
multiline_comment|/*&n; * Get Link Status mailbox command return buffer.&n; */
r_typedef
r_struct
(brace
DECL|member|link_fail_cnt
r_uint32
id|link_fail_cnt
suffix:semicolon
DECL|member|loss_sync_cnt
r_uint32
id|loss_sync_cnt
suffix:semicolon
DECL|member|loss_sig_cnt
r_uint32
id|loss_sig_cnt
suffix:semicolon
DECL|member|prim_seq_err_cnt
r_uint32
id|prim_seq_err_cnt
suffix:semicolon
DECL|member|inval_xmit_word_cnt
r_uint32
id|inval_xmit_word_cnt
suffix:semicolon
DECL|member|inval_crc_cnt
r_uint32
id|inval_crc_cnt
suffix:semicolon
DECL|typedef|link_stat_t
)brace
id|link_stat_t
suffix:semicolon
multiline_comment|/*&n; * NVRAM Command values.&n; */
DECL|macro|NV_START_BIT
mdefine_line|#define NV_START_BIT            BIT_2
DECL|macro|NV_WRITE_OP
mdefine_line|#define NV_WRITE_OP             (BIT_26+BIT_24)
DECL|macro|NV_READ_OP
mdefine_line|#define NV_READ_OP              (BIT_26+BIT_25)
DECL|macro|NV_ERASE_OP
mdefine_line|#define NV_ERASE_OP             (BIT_26+BIT_25+BIT_24)
DECL|macro|NV_MASK_OP
mdefine_line|#define NV_MASK_OP              (BIT_26+BIT_25+BIT_24)
DECL|macro|NV_DELAY_COUNT
mdefine_line|#define NV_DELAY_COUNT          10
multiline_comment|/*&n; * QLogic ISP2100, ISP2200 and ISP2300 NVRAM structure definition.&n; */
r_typedef
r_struct
(brace
multiline_comment|/*&n;&t; * NVRAM header&n;&t; */
DECL|member|id
r_uint8
id|id
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|nvram_version
r_uint8
id|nvram_version
suffix:semicolon
DECL|member|reserved_0
r_uint8
id|reserved_0
suffix:semicolon
multiline_comment|/*&n;&t; * NVRAM RISC parameter block&n;&t; */
DECL|member|parameter_block_version
r_uint8
id|parameter_block_version
suffix:semicolon
DECL|member|reserved_1
r_uint8
id|reserved_1
suffix:semicolon
multiline_comment|/*&n;&t; * LSB BIT 0  = Enable Hard Loop Id&n;&t; * LSB BIT 1  = Enable Fairness&n;&t; * LSB BIT 2  = Enable Full-Duplex&n;&t; * LSB BIT 3  = Enable Fast Posting&n;&t; * LSB BIT 4  = Enable Target Mode&n;&t; * LSB BIT 5  = Disable Initiator Mode&n;&t; * LSB BIT 6  = Enable ADISC&n;&t; * LSB BIT 7  = Enable Target Inquiry Data&n;&t; *&n;&t; * MSB BIT 0  = Enable PDBC Notify&n;&t; * MSB BIT 1  = Non Participating LIP&n;&t; * MSB BIT 2  = Descending Loop ID Search&n;&t; * MSB BIT 3  = Acquire Loop ID in LIPA&n;&t; * MSB BIT 4  = Stop PortQ on Full Status&n;&t; * MSB BIT 5  = Full Login after LIP&n;&t; * MSB BIT 6  = Node Name Option&n;&t; * MSB BIT 7  = Ext IFWCB enable bit&n;&t; */
DECL|member|firmware_options
r_uint8
id|firmware_options
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|frame_payload_size
r_uint16
id|frame_payload_size
suffix:semicolon
DECL|member|max_iocb_allocation
r_uint16
id|max_iocb_allocation
suffix:semicolon
DECL|member|execution_throttle
r_uint16
id|execution_throttle
suffix:semicolon
DECL|member|retry_count
r_uint8
id|retry_count
suffix:semicolon
DECL|member|retry_delay
r_uint8
id|retry_delay
suffix:semicolon
multiline_comment|/* unused */
DECL|member|port_name
r_uint8
id|port_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
multiline_comment|/* Big endian. */
DECL|member|hard_address
r_uint16
id|hard_address
suffix:semicolon
DECL|member|inquiry_data
r_uint8
id|inquiry_data
suffix:semicolon
DECL|member|login_timeout
r_uint8
id|login_timeout
suffix:semicolon
DECL|member|node_name
r_uint8
id|node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
multiline_comment|/* Big endian. */
multiline_comment|/*&n;&t; * LSB BIT 0 = Timer Operation mode bit 0&n;&t; * LSB BIT 1 = Timer Operation mode bit 1&n;&t; * LSB BIT 2 = Timer Operation mode bit 2&n;&t; * LSB BIT 3 = Timer Operation mode bit 3&n;&t; * LSB BIT 4 = Init Config Mode bit 0&n;&t; * LSB BIT 5 = Init Config Mode bit 1&n;&t; * LSB BIT 6 = Init Config Mode bit 2&n;&t; * LSB BIT 7 = Enable Non part on LIHA failure&n;&t; *&n;&t; * MSB BIT 0 = Enable class 2&n;&t; * MSB BIT 1 = Enable ACK0&n;&t; * MSB BIT 2 =&n;&t; * MSB BIT 3 =&n;&t; * MSB BIT 4 = FC Tape Enable&n;&t; * MSB BIT 5 = Enable FC Confirm&n;&t; * MSB BIT 6 = Enable command queuing in target mode&n;&t; * MSB BIT 7 = No Logo On Link Down&n;&t; */
DECL|member|add_firmware_options
r_uint8
id|add_firmware_options
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|response_accumulation_timer
r_uint8
id|response_accumulation_timer
suffix:semicolon
DECL|member|interrupt_delay_timer
r_uint8
id|interrupt_delay_timer
suffix:semicolon
multiline_comment|/*&n;&t; * LSB BIT 0 = Enable Read xfr_rdy&n;&t; * LSB BIT 1 = Soft ID only&n;&t; * LSB BIT 2 =&n;&t; * LSB BIT 3 =&n;&t; * LSB BIT 4 = FCP RSP Payload [0]&n;&t; * LSB BIT 5 = FCP RSP Payload [1] / Sbus enable - 2200&n;&t; * LSB BIT 6 = Enable Out-of-Order frame handling&n;&t; * LSB BIT 7 = Disable Automatic PLOGI on Local Loop&n;&t; *&n;&t; * MSB BIT 0 = Sbus enable - 2300&n;&t; * MSB BIT 1 =&n;&t; * MSB BIT 2 =&n;&t; * MSB BIT 3 =&n;&t; * MSB BIT 4 =&n;&t; * MSB BIT 5 = enable 50 ohm termination&n;&t; * MSB BIT 6 = Data Rate (2300 only)&n;&t; * MSB BIT 7 = Data Rate (2300 only)&n;&t; */
DECL|member|special_options
r_uint8
id|special_options
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Reserved for expanded RISC parameter block */
DECL|member|reserved_2
r_uint8
id|reserved_2
(braket
l_int|22
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * LSB BIT 0 = Tx Sensitivity 1G bit 0&n;&t; * LSB BIT 1 = Tx Sensitivity 1G bit 1&n;&t; * LSB BIT 2 = Tx Sensitivity 1G bit 2&n;&t; * LSB BIT 3 = Tx Sensitivity 1G bit 3&n;&t; * LSB BIT 4 = Rx Sensitivity 1G bit 0&n;&t; * LSB BIT 5 = Rx Sensitivity 1G bit 1&n;&t; * LSB BIT 6 = Rx Sensitivity 1G bit 2&n;&t; * LSB BIT 7 = Rx Sensitivity 1G bit 3&n;&t; *            &n;&t; * MSB BIT 0 = Tx Sensitivity 2G bit 0&n;&t; * MSB BIT 1 = Tx Sensitivity 2G bit 1&n;&t; * MSB BIT 2 = Tx Sensitivity 2G bit 2&n;&t; * MSB BIT 3 = Tx Sensitivity 2G bit 3&n;&t; * MSB BIT 4 = Rx Sensitivity 2G bit 0&n;&t; * MSB BIT 5 = Rx Sensitivity 2G bit 1&n;&t; * MSB BIT 6 = Rx Sensitivity 2G bit 2&n;&t; * MSB BIT 7 = Rx Sensitivity 2G bit 3&n;&t; *&n;&t; * LSB BIT 0 = Output Swing 1G bit 0&n;&t; * LSB BIT 1 = Output Swing 1G bit 1&n;&t; * LSB BIT 2 = Output Swing 1G bit 2&n;&t; * LSB BIT 3 = Output Emphasis 1G bit 0&n;&t; * LSB BIT 4 = Output Emphasis 1G bit 1&n;&t; * LSB BIT 5 = Output Swing 2G bit 0&n;&t; * LSB BIT 6 = Output Swing 2G bit 1&n;&t; * LSB BIT 7 = Output Swing 2G bit 2&n;&t; *            &n;&t; * MSB BIT 0 = Output Emphasis 2G bit 0&n;&t; * MSB BIT 1 = Output Emphasis 2G bit 1&n;&t; * MSB BIT 2 = Output Enable&n;&t; * MSB BIT 3 =&n;&t; * MSB BIT 4 =&n;&t; * MSB BIT 5 =&n;&t; * MSB BIT 6 =&n;&t; * MSB BIT 7 =&n;&t; */
DECL|member|seriallink_options
r_uint8
id|seriallink_options
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * NVRAM host parameter block&n;&t; *&n;&t; * LSB BIT 0 = Enable spinup delay&n;&t; * LSB BIT 1 = Disable BIOS&n;&t; * LSB BIT 2 = Enable Memory Map BIOS&n;&t; * LSB BIT 3 = Enable Selectable Boot&n;&t; * LSB BIT 4 = Disable RISC code load&n;&t; * LSB BIT 5 = Set cache line size 1&n;&t; * LSB BIT 6 = PCI Parity Disable&n;&t; * LSB BIT 7 = Enable extended logging&n;&t; *&n;&t; * MSB BIT 0 = Enable 64bit addressing&n;&t; * MSB BIT 1 = Enable lip reset&n;&t; * MSB BIT 2 = Enable lip full login&n;&t; * MSB BIT 3 = Enable target reset&n;&t; * MSB BIT 4 = Enable database storage&n;&t; * MSB BIT 5 = Enable cache flush read&n;&t; * MSB BIT 6 = Enable database load&n;&t; * MSB BIT 7 = Enable alternate WWN&n;&t; */
DECL|member|host_p
r_uint8
id|host_p
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|boot_node_name
r_uint8
id|boot_node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|boot_lun_number
r_uint8
id|boot_lun_number
suffix:semicolon
DECL|member|reset_delay
r_uint8
id|reset_delay
suffix:semicolon
DECL|member|port_down_retry_count
r_uint8
id|port_down_retry_count
suffix:semicolon
DECL|member|boot_id_number
r_uint8
id|boot_id_number
suffix:semicolon
DECL|member|max_luns_per_target
r_uint16
id|max_luns_per_target
suffix:semicolon
DECL|member|fcode_boot_port_name
r_uint8
id|fcode_boot_port_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|alternate_port_name
r_uint8
id|alternate_port_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|alternate_node_name
r_uint8
id|alternate_node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * BIT 0 = Selective Login&n;&t; * BIT 1 = Alt-Boot Enable&n;&t; * BIT 2 =&n;&t; * BIT 3 = Boot Order List&n;&t; * BIT 4 =&n;&t; * BIT 5 = Selective LUN&n;&t; * BIT 6 =&n;&t; * BIT 7 = unused&n;&t; */
DECL|member|efi_parameters
r_uint8
id|efi_parameters
suffix:semicolon
DECL|member|link_down_timeout
r_uint8
id|link_down_timeout
suffix:semicolon
DECL|member|adapter_id_0
r_uint8
id|adapter_id_0
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|adapter_id_1
r_uint8
id|adapter_id_1
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|adapter_id_2
r_uint8
id|adapter_id_2
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|adapter_id_3
r_uint8
id|adapter_id_3
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|alt1_boot_node_name
r_uint8
id|alt1_boot_node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|alt1_boot_lun_number
r_uint16
id|alt1_boot_lun_number
suffix:semicolon
DECL|member|alt2_boot_node_name
r_uint8
id|alt2_boot_node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|alt2_boot_lun_number
r_uint16
id|alt2_boot_lun_number
suffix:semicolon
DECL|member|alt3_boot_node_name
r_uint8
id|alt3_boot_node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|alt3_boot_lun_number
r_uint16
id|alt3_boot_lun_number
suffix:semicolon
DECL|member|alt4_boot_node_name
r_uint8
id|alt4_boot_node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|alt4_boot_lun_number
r_uint16
id|alt4_boot_lun_number
suffix:semicolon
DECL|member|alt5_boot_node_name
r_uint8
id|alt5_boot_node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|alt5_boot_lun_number
r_uint16
id|alt5_boot_lun_number
suffix:semicolon
DECL|member|alt6_boot_node_name
r_uint8
id|alt6_boot_node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|alt6_boot_lun_number
r_uint16
id|alt6_boot_lun_number
suffix:semicolon
DECL|member|alt7_boot_node_name
r_uint8
id|alt7_boot_node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|alt7_boot_lun_number
r_uint16
id|alt7_boot_lun_number
suffix:semicolon
DECL|member|reserved_3
r_uint8
id|reserved_3
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Offset 200-215 : Model Number */
DECL|member|model_number
r_uint8
id|model_number
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* OEM related items */
DECL|member|oem_specific
r_uint8
id|oem_specific
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * NVRAM Adapter Features offset 232-239&n;&t; *&n;&t; * LSB BIT 0 = External GBIC&n;&t; * LSB BIT 1 = Risc RAM parity&n;&t; * LSB BIT 2 = Buffer Plus Module&n;&t; * LSB BIT 3 = Multi Chip Adapter&n;&t; * LSB BIT 4 = Internal connector&n;&t; * LSB BIT 5 =&n;&t; * LSB BIT 6 =&n;&t; * LSB BIT 7 =&n;&t; *&n;&t; * MSB BIT 0 =&n;&t; * MSB BIT 1 =&n;&t; * MSB BIT 2 =&n;&t; * MSB BIT 3 =&n;&t; * MSB BIT 4 =&n;&t; * MSB BIT 5 =&n;&t; * MSB BIT 6 =&n;&t; * MSB BIT 7 =&n;&t; */
DECL|member|adapter_features
r_uint8
id|adapter_features
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|reserved_4
r_uint8
id|reserved_4
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Subsystem vendor ID for ISP2200 */
DECL|member|subsystem_vendor_id_2200
r_uint16
id|subsystem_vendor_id_2200
suffix:semicolon
multiline_comment|/* Subsystem device ID for ISP2200 */
DECL|member|subsystem_device_id_2200
r_uint16
id|subsystem_device_id_2200
suffix:semicolon
DECL|member|reserved_5
r_uint8
id|reserved_5
suffix:semicolon
DECL|member|checksum
r_uint8
id|checksum
suffix:semicolon
DECL|typedef|nvram_t
)brace
id|nvram_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - response queue entry definition.&n; */
r_typedef
r_struct
(brace
DECL|member|data
r_uint8
id|data
(braket
l_int|60
)braket
suffix:semicolon
DECL|member|signature
r_uint32
id|signature
suffix:semicolon
DECL|macro|RESPONSE_PROCESSED
mdefine_line|#define RESPONSE_PROCESSED&t;0xDEADDEAD&t;/* Signature */
DECL|typedef|response_t
)brace
id|response_t
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|extended
r_uint16
id|extended
suffix:semicolon
r_struct
(brace
DECL|member|reserved
r_uint8
id|reserved
suffix:semicolon
DECL|member|standard
r_uint8
id|standard
suffix:semicolon
DECL|member|id
)brace
id|id
suffix:semicolon
DECL|typedef|target_id_t
)brace
id|target_id_t
suffix:semicolon
DECL|macro|SET_TARGET_ID
mdefine_line|#define SET_TARGET_ID(ha, to, from)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (HAS_EXTENDED_IDS(ha))&t;&t;&t;&bslash;&n;&t;&t;to.extended = cpu_to_le16(from);&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;to.id.standard = (uint8_t)from;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; * ISP queue - command entry structure definition.&n; */
DECL|macro|COMMAND_TYPE
mdefine_line|#define COMMAND_TYPE&t;0x11&t;&t;/* Command entry */
DECL|macro|MAX_CMDSZ
mdefine_line|#define MAX_CMDSZ&t;16&t;&t;/* SCSI maximum CDB size. */
r_typedef
r_struct
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
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
DECL|member|target
id|target_id_t
id|target
suffix:semicolon
multiline_comment|/* SCSI ID */
DECL|member|lun
r_uint16
id|lun
suffix:semicolon
multiline_comment|/* SCSI LUN */
DECL|member|control_flags
r_uint16
id|control_flags
suffix:semicolon
multiline_comment|/* Control flags. */
DECL|macro|CF_WRITE
mdefine_line|#define CF_WRITE&t;BIT_6
DECL|macro|CF_READ
mdefine_line|#define CF_READ&t;&t;BIT_5
DECL|macro|CF_SIMPLE_TAG
mdefine_line|#define CF_SIMPLE_TAG&t;BIT_3
DECL|macro|CF_ORDERED_TAG
mdefine_line|#define CF_ORDERED_TAG&t;BIT_2
DECL|macro|CF_HEAD_TAG
mdefine_line|#define CF_HEAD_TAG&t;BIT_1
DECL|member|reserved_1
r_uint16
id|reserved_1
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
DECL|member|byte_count
r_uint32
id|byte_count
suffix:semicolon
multiline_comment|/* Total byte count. */
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
DECL|typedef|cmd_entry_t
)brace
id|cmd_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - 64-Bit addressing, command entry structure definition.&n; */
DECL|macro|COMMAND_A64_TYPE
mdefine_line|#define COMMAND_A64_TYPE&t;0x19&t;/* Command A64 entry */
r_typedef
r_struct
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
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
DECL|member|target
id|target_id_t
id|target
suffix:semicolon
multiline_comment|/* SCSI ID */
DECL|member|lun
r_uint16
id|lun
suffix:semicolon
multiline_comment|/* SCSI LUN */
DECL|member|control_flags
r_uint16
id|control_flags
suffix:semicolon
multiline_comment|/* Control flags. */
DECL|member|reserved_1
r_uint16
id|reserved_1
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
DECL|member|byte_count
r_uint32
id|byte_count
suffix:semicolon
multiline_comment|/* Total byte count. */
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
multiline_comment|/*&n; * ISP queue - continuation entry structure definition.&n; */
DECL|macro|CONTINUE_TYPE
mdefine_line|#define CONTINUE_TYPE&t;&t;0x02&t;/* Continuation entry. */
r_typedef
r_struct
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
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
multiline_comment|/*&n; * ISP queue - 64-Bit addressing, continuation entry structure definition.&n; */
DECL|macro|CONTINUE_A64_TYPE
mdefine_line|#define CONTINUE_A64_TYPE&t;0x0A&t;/* Continuation A64 entry. */
r_typedef
r_struct
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
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
multiline_comment|/*&n; * ISP queue - status entry structure definition.&n; */
DECL|macro|STATUS_TYPE
mdefine_line|#define&t;STATUS_TYPE&t;0x03&t;&t;/* Status entry. */
r_typedef
r_struct
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
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
DECL|member|status_flags
r_uint16
id|status_flags
suffix:semicolon
multiline_comment|/* Status flags. */
DECL|member|rsp_info_len
r_uint16
id|rsp_info_len
suffix:semicolon
multiline_comment|/* Response Info Length. */
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
DECL|member|rsp_info
r_uint8
id|rsp_info
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* FCP response information. */
DECL|member|req_sense_data
r_uint8
id|req_sense_data
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Request sense data. */
DECL|typedef|sts_entry_t
)brace
id|sts_entry_t
suffix:semicolon
multiline_comment|/*&n; * Status entry entry status&n; */
DECL|macro|RF_INV_E_ORDER
mdefine_line|#define RF_INV_E_ORDER&t;BIT_5&t;&t;/* Invalid entry order. */
DECL|macro|RF_INV_E_COUNT
mdefine_line|#define RF_INV_E_COUNT&t;BIT_4&t;&t;/* Invalid entry count. */
DECL|macro|RF_INV_E_PARAM
mdefine_line|#define RF_INV_E_PARAM&t;BIT_3&t;&t;/* Invalid entry parameter. */
DECL|macro|RF_INV_E_TYPE
mdefine_line|#define RF_INV_E_TYPE&t;BIT_2&t;&t;/* Invalid entry type. */
DECL|macro|RF_BUSY
mdefine_line|#define RF_BUSY&t;&t;BIT_1&t;&t;/* Busy */
multiline_comment|/*&n; * Status entry SCSI status bit definitions.&n; */
DECL|macro|SS_MASK
mdefine_line|#define SS_MASK&t;&t;&t;&t;0xfff&t;/* Reserved bits BIT_12-BIT_15*/
DECL|macro|SS_RESIDUAL_UNDER
mdefine_line|#define SS_RESIDUAL_UNDER&t;&t;BIT_11
DECL|macro|SS_RESIDUAL_OVER
mdefine_line|#define SS_RESIDUAL_OVER&t;&t;BIT_10
DECL|macro|SS_SENSE_LEN_VALID
mdefine_line|#define SS_SENSE_LEN_VALID&t;&t;BIT_9
DECL|macro|SS_RESPONSE_INFO_LEN_VALID
mdefine_line|#define SS_RESPONSE_INFO_LEN_VALID&t;BIT_8
DECL|macro|SS_RESERVE_CONFLICT
mdefine_line|#define SS_RESERVE_CONFLICT&t;&t;(BIT_4 | BIT_3)
DECL|macro|SS_BUSY_CONDITION
mdefine_line|#define SS_BUSY_CONDITION&t;&t;BIT_3
DECL|macro|SS_CONDITION_MET
mdefine_line|#define SS_CONDITION_MET&t;&t;BIT_2
DECL|macro|SS_CHECK_CONDITION
mdefine_line|#define SS_CHECK_CONDITION&t;&t;BIT_1
multiline_comment|/*&n; * Status entry completion status&n; */
DECL|macro|CS_COMPLETE
mdefine_line|#define CS_COMPLETE&t;&t;0x0&t;/* No errors */
DECL|macro|CS_INCOMPLETE
mdefine_line|#define CS_INCOMPLETE&t;&t;0x1&t;/* Incomplete transfer of cmd. */
DECL|macro|CS_DMA
mdefine_line|#define CS_DMA&t;&t;&t;0x2&t;/* A DMA direction error. */
DECL|macro|CS_TRANSPORT
mdefine_line|#define CS_TRANSPORT&t;&t;0x3&t;/* Transport error. */
DECL|macro|CS_RESET
mdefine_line|#define CS_RESET&t;&t;0x4&t;/* SCSI bus reset occurred */
DECL|macro|CS_ABORTED
mdefine_line|#define CS_ABORTED&t;&t;0x5&t;/* System aborted command. */
DECL|macro|CS_TIMEOUT
mdefine_line|#define CS_TIMEOUT&t;&t;0x6&t;/* Timeout error. */
DECL|macro|CS_DATA_OVERRUN
mdefine_line|#define CS_DATA_OVERRUN&t;&t;0x7&t;/* Data overrun. */
DECL|macro|CS_DATA_UNDERRUN
mdefine_line|#define CS_DATA_UNDERRUN&t;0x15&t;/* Data Underrun. */
DECL|macro|CS_QUEUE_FULL
mdefine_line|#define CS_QUEUE_FULL&t;&t;0x1C&t;/* Queue Full. */
DECL|macro|CS_PORT_UNAVAILABLE
mdefine_line|#define CS_PORT_UNAVAILABLE&t;0x28&t;/* Port unavailable */
multiline_comment|/* (selection timeout) */
DECL|macro|CS_PORT_LOGGED_OUT
mdefine_line|#define CS_PORT_LOGGED_OUT&t;0x29&t;/* Port Logged Out */
DECL|macro|CS_PORT_CONFIG_CHG
mdefine_line|#define CS_PORT_CONFIG_CHG&t;0x2A&t;/* Port Configuration Changed */
DECL|macro|CS_PORT_BUSY
mdefine_line|#define CS_PORT_BUSY&t;&t;0x2B&t;/* Port Busy */
DECL|macro|CS_COMPLETE_CHKCOND
mdefine_line|#define CS_COMPLETE_CHKCOND&t;0x30&t;/* Error? */
DECL|macro|CS_BAD_PAYLOAD
mdefine_line|#define CS_BAD_PAYLOAD&t;&t;0x80&t;/* Driver defined */
DECL|macro|CS_UNKNOWN
mdefine_line|#define CS_UNKNOWN&t;&t;0x81&t;/* Driver defined */
DECL|macro|CS_RETRY
mdefine_line|#define CS_RETRY&t;&t;0x82&t;/* Driver defined */
DECL|macro|CS_LOOP_DOWN_ABORT
mdefine_line|#define CS_LOOP_DOWN_ABORT&t;0x83&t;/* Driver defined */
multiline_comment|/*&n; * Status entry status flags&n; */
DECL|macro|SF_ABTS_TERMINATED
mdefine_line|#define SF_ABTS_TERMINATED&t;BIT_10
DECL|macro|SF_LOGOUT_SENT
mdefine_line|#define SF_LOGOUT_SENT&t;&t;BIT_13
multiline_comment|/*&n; * ISP queue - status continuation entry structure definition.&n; */
DECL|macro|STATUS_CONT_TYPE
mdefine_line|#define&t;STATUS_CONT_TYPE&t;0x10&t;/* Status continuation entry. */
r_typedef
r_struct
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
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
DECL|member|data
r_uint8
id|data
(braket
l_int|60
)braket
suffix:semicolon
multiline_comment|/* data */
DECL|typedef|sts_cont_entry_t
)brace
id|sts_cont_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue -&t;RIO Type 1 status entry (32 bit I/O entry handles)&n; *&t;&t;structure definition.&n; */
DECL|macro|STATUS_TYPE_21
mdefine_line|#define&t;STATUS_TYPE_21 0x21&t;&t;/* Status entry. */
r_typedef
r_struct
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|handle_count
r_uint8
id|handle_count
suffix:semicolon
multiline_comment|/* Handle count. */
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|handle
r_uint32
id|handle
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* System handles. */
DECL|typedef|sts21_entry_t
)brace
id|sts21_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue -&t;RIO Type 2 status entry (16 bit I/O entry handles)&n; *&t;&t;structure definition.&n; */
DECL|macro|STATUS_TYPE_22
mdefine_line|#define&t;STATUS_TYPE_22&t;0x22&t;&t;/* Status entry. */
r_typedef
r_struct
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|handle_count
r_uint8
id|handle_count
suffix:semicolon
multiline_comment|/* Handle count. */
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|handle
r_uint16
id|handle
(braket
l_int|30
)braket
suffix:semicolon
multiline_comment|/* System handles. */
DECL|typedef|sts22_entry_t
)brace
id|sts22_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - marker entry structure definition.&n; */
DECL|macro|MARKER_TYPE
mdefine_line|#define MARKER_TYPE&t;0x04&t;&t;/* Marker entry. */
r_typedef
r_struct
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|handle_count
r_uint8
id|handle_count
suffix:semicolon
multiline_comment|/* Handle count. */
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|sys_define_2
r_uint32
id|sys_define_2
suffix:semicolon
multiline_comment|/* System defined. */
DECL|member|target
id|target_id_t
id|target
suffix:semicolon
multiline_comment|/* SCSI ID */
DECL|member|modifier
r_uint8
id|modifier
suffix:semicolon
multiline_comment|/* Modifier (7-0). */
DECL|macro|MK_SYNC_ID_LUN
mdefine_line|#define MK_SYNC_ID_LUN&t;0&t;&t;/* Synchronize ID/LUN */
DECL|macro|MK_SYNC_ID
mdefine_line|#define MK_SYNC_ID&t;1&t;&t;/* Synchronize ID */
DECL|macro|MK_SYNC_ALL
mdefine_line|#define MK_SYNC_ALL&t;2&t;&t;/* Synchronize all ID/LUN */
DECL|macro|MK_SYNC_LIP
mdefine_line|#define MK_SYNC_LIP&t;3&t;&t;/* Synchronize all ID/LUN, */
multiline_comment|/* clear port changed, */
multiline_comment|/* use sequence number. */
DECL|member|reserved_1
r_uint8
id|reserved_1
suffix:semicolon
DECL|member|sequence_number
r_uint16
id|sequence_number
suffix:semicolon
multiline_comment|/* Sequence number of event */
DECL|member|lun
r_uint16
id|lun
suffix:semicolon
multiline_comment|/* SCSI LUN */
DECL|member|reserved_2
r_uint8
id|reserved_2
(braket
l_int|48
)braket
suffix:semicolon
DECL|typedef|mrk_entry_t
)brace
id|mrk_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - Management Server entry structure definition.&n; */
DECL|macro|MS_IOCB_TYPE
mdefine_line|#define MS_IOCB_TYPE&t;&t;0x29&t;/* Management Server IOCB entry */
r_typedef
r_struct
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
multiline_comment|/* Entry type. */
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
multiline_comment|/* Entry count. */
DECL|member|handle_count
r_uint8
id|handle_count
suffix:semicolon
multiline_comment|/* Handle count. */
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
multiline_comment|/* Entry Status. */
DECL|member|handle1
r_uint32
id|handle1
suffix:semicolon
multiline_comment|/* System handle. */
DECL|member|loop_id
id|target_id_t
id|loop_id
suffix:semicolon
DECL|member|status
r_uint16
id|status
suffix:semicolon
DECL|member|control_flags
r_uint16
id|control_flags
suffix:semicolon
multiline_comment|/* Control flags. */
DECL|member|reserved2
r_uint16
id|reserved2
suffix:semicolon
DECL|member|timeout
r_uint16
id|timeout
suffix:semicolon
DECL|member|cmd_dsd_count
r_uint16
id|cmd_dsd_count
suffix:semicolon
DECL|member|total_dsd_count
r_uint16
id|total_dsd_count
suffix:semicolon
DECL|member|type
r_uint8
id|type
suffix:semicolon
DECL|member|r_ctl
r_uint8
id|r_ctl
suffix:semicolon
DECL|member|rx_id
r_uint16
id|rx_id
suffix:semicolon
DECL|member|reserved3
r_uint16
id|reserved3
suffix:semicolon
DECL|member|handle2
r_uint32
id|handle2
suffix:semicolon
DECL|member|rsp_bytecount
r_uint32
id|rsp_bytecount
suffix:semicolon
DECL|member|req_bytecount
r_uint32
id|req_bytecount
suffix:semicolon
DECL|member|dseg_req_address
r_uint32
id|dseg_req_address
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Data segment 0 address. */
DECL|member|dseg_req_length
r_uint32
id|dseg_req_length
suffix:semicolon
multiline_comment|/* Data segment 0 length. */
DECL|member|dseg_rsp_address
r_uint32
id|dseg_rsp_address
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Data segment 1 address. */
DECL|member|dseg_rsp_length
r_uint32
id|dseg_rsp_length
suffix:semicolon
multiline_comment|/* Data segment 1 length. */
DECL|typedef|ms_iocb_entry_t
)brace
id|ms_iocb_entry_t
suffix:semicolon
multiline_comment|/*&n; * ISP queue - Mailbox Command entry structure definition.&n; */
DECL|macro|MBX_IOCB_TYPE
mdefine_line|#define MBX_IOCB_TYPE&t;0x39
DECL|struct|mbx_entry
r_struct
id|mbx_entry
(brace
DECL|member|entry_type
r_uint8
id|entry_type
suffix:semicolon
DECL|member|entry_count
r_uint8
id|entry_count
suffix:semicolon
DECL|member|sys_define1
r_uint8
id|sys_define1
suffix:semicolon
multiline_comment|/* Use sys_define1 for source type */
DECL|macro|SOURCE_SCSI
mdefine_line|#define SOURCE_SCSI&t;0x00
DECL|macro|SOURCE_IP
mdefine_line|#define SOURCE_IP&t;0x01
DECL|macro|SOURCE_VI
mdefine_line|#define SOURCE_VI&t;0x02
DECL|macro|SOURCE_SCTP
mdefine_line|#define SOURCE_SCTP&t;0x03
DECL|macro|SOURCE_MP
mdefine_line|#define SOURCE_MP&t;0x04
DECL|macro|SOURCE_MPIOCTL
mdefine_line|#define SOURCE_MPIOCTL&t;0x05
DECL|macro|SOURCE_ASYNC_IOCB
mdefine_line|#define SOURCE_ASYNC_IOCB 0x07
DECL|member|entry_status
r_uint8
id|entry_status
suffix:semicolon
DECL|member|handle
r_uint32
id|handle
suffix:semicolon
DECL|member|loop_id
id|target_id_t
id|loop_id
suffix:semicolon
DECL|member|status
r_uint16
id|status
suffix:semicolon
DECL|member|state_flags
r_uint16
id|state_flags
suffix:semicolon
DECL|member|status_flags
r_uint16
id|status_flags
suffix:semicolon
DECL|member|sys_define2
r_uint32
id|sys_define2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|mb0
r_uint16
id|mb0
suffix:semicolon
DECL|member|mb1
r_uint16
id|mb1
suffix:semicolon
DECL|member|mb2
r_uint16
id|mb2
suffix:semicolon
DECL|member|mb3
r_uint16
id|mb3
suffix:semicolon
DECL|member|mb6
r_uint16
id|mb6
suffix:semicolon
DECL|member|mb7
r_uint16
id|mb7
suffix:semicolon
DECL|member|mb9
r_uint16
id|mb9
suffix:semicolon
DECL|member|mb10
r_uint16
id|mb10
suffix:semicolon
DECL|member|reserved_2
r_uint32
id|reserved_2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|node_name
r_uint8
id|node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|port_name
r_uint8
id|port_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ISP request and response queue entry sizes&n; */
DECL|macro|RESPONSE_ENTRY_SIZE
mdefine_line|#define RESPONSE_ENTRY_SIZE&t;(sizeof(response_t))
DECL|macro|REQUEST_ENTRY_SIZE
mdefine_line|#define REQUEST_ENTRY_SIZE&t;(sizeof(request_t))
multiline_comment|/*&n; * 24 bit port ID type definition.&n; */
r_typedef
r_union
(brace
r_uint32
id|b24
suffix:colon
l_int|24
suffix:semicolon
r_struct
(brace
DECL|member|d_id
r_uint8
id|d_id
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|rsvd_1
r_uint8
id|rsvd_1
suffix:semicolon
DECL|member|r
)brace
id|r
suffix:semicolon
r_struct
(brace
DECL|member|al_pa
r_uint8
id|al_pa
suffix:semicolon
DECL|member|area
r_uint8
id|area
suffix:semicolon
DECL|member|domain
r_uint8
id|domain
suffix:semicolon
DECL|member|rsvd_1
r_uint8
id|rsvd_1
suffix:semicolon
DECL|member|b
)brace
id|b
suffix:semicolon
DECL|typedef|port_id_t
)brace
id|port_id_t
suffix:semicolon
DECL|macro|INVALID_PORT_ID
mdefine_line|#define INVALID_PORT_ID&t;0xFFFFFF
multiline_comment|/*&n; * Switch info gathering structure.&n; */
r_typedef
r_struct
(brace
DECL|member|d_id
id|port_id_t
id|d_id
suffix:semicolon
DECL|member|node_name
r_uint8
id|node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|port_name
r_uint8
id|port_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|type
r_uint32
id|type
suffix:semicolon
DECL|macro|SW_TYPE_IP
mdefine_line|#define SW_TYPE_IP&t;BIT_1
DECL|macro|SW_TYPE_SCSI
mdefine_line|#define SW_TYPE_SCSI&t;BIT_0
DECL|typedef|sw_info_t
)brace
id|sw_info_t
suffix:semicolon
multiline_comment|/*&n; * Inquiry command structure.&n; */
DECL|macro|INQ_DATA_SIZE
mdefine_line|#define INQ_DATA_SIZE&t;36
multiline_comment|/*&n; * Inquiry mailbox IOCB packet definition.&n; */
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|cmd
id|cmd_a64_entry_t
id|cmd
suffix:semicolon
DECL|member|rsp
id|sts_entry_t
id|rsp
suffix:semicolon
DECL|member|p
)brace
id|p
suffix:semicolon
DECL|member|inq
r_uint8
id|inq
(braket
id|INQ_DATA_SIZE
)braket
suffix:semicolon
DECL|typedef|inq_cmd_rsp_t
)brace
id|inq_cmd_rsp_t
suffix:semicolon
multiline_comment|/*&n; * Report LUN command structure.&n; */
DECL|macro|CHAR_TO_SHORT
mdefine_line|#define CHAR_TO_SHORT(a, b)&t;(uint16_t)((uint8_t)b &lt;&lt; 8 | (uint8_t)a)
r_typedef
r_struct
(brace
DECL|member|len
r_uint32
id|len
suffix:semicolon
DECL|member|rsrv
r_uint32
id|rsrv
suffix:semicolon
DECL|typedef|rpt_hdr_t
)brace
id|rpt_hdr_t
suffix:semicolon
r_typedef
r_struct
(brace
r_struct
(brace
DECL|member|b
r_uint8
id|b
suffix:colon
l_int|6
suffix:semicolon
DECL|member|address_method
r_uint8
id|address_method
suffix:colon
l_int|2
suffix:semicolon
DECL|member|msb
)brace
id|msb
suffix:semicolon
DECL|member|lsb
r_uint8
id|lsb
suffix:semicolon
DECL|member|unused
r_uint8
id|unused
(braket
l_int|6
)braket
suffix:semicolon
DECL|typedef|rpt_lun_t
)brace
id|rpt_lun_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|hdr
id|rpt_hdr_t
id|hdr
suffix:semicolon
DECL|member|lst
id|rpt_lun_t
id|lst
(braket
id|MAX_LUNS
)braket
suffix:semicolon
DECL|typedef|rpt_lun_lst_t
)brace
id|rpt_lun_lst_t
suffix:semicolon
multiline_comment|/*&n; * Report Lun mailbox IOCB packet definition.&n; */
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|cmd
id|cmd_a64_entry_t
id|cmd
suffix:semicolon
DECL|member|rsp
id|sts_entry_t
id|rsp
suffix:semicolon
DECL|member|p
)brace
id|p
suffix:semicolon
DECL|member|list
id|rpt_lun_lst_t
id|list
suffix:semicolon
DECL|typedef|rpt_lun_cmd_rsp_t
)brace
id|rpt_lun_cmd_rsp_t
suffix:semicolon
multiline_comment|/*&n; * SCSI Target Queue structure&n; */
DECL|struct|os_tgt
r_typedef
r_struct
id|os_tgt
(brace
DECL|member|olun
r_struct
id|os_lun
op_star
id|olun
(braket
id|MAX_LUNS
)braket
suffix:semicolon
multiline_comment|/* LUN context pointer. */
DECL|member|fcport
r_struct
id|fc_port
op_star
id|fcport
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|port_down_retry_count
r_uint8
id|port_down_retry_count
suffix:semicolon
DECL|member|down_timer
r_uint32
id|down_timer
suffix:semicolon
DECL|member|ha
r_struct
id|scsi_qla_host
op_star
id|ha
suffix:semicolon
multiline_comment|/* Persistent binding information */
DECL|member|d_id
id|port_id_t
id|d_id
suffix:semicolon
DECL|member|node_name
r_uint8
id|node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|port_name
r_uint8
id|port_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|typedef|os_tgt_t
)brace
id|os_tgt_t
suffix:semicolon
multiline_comment|/*&n; * SCSI Target Queue flags&n; */
DECL|macro|TQF_ONLINE
mdefine_line|#define TQF_ONLINE&t;&t;0&t;&t;/* Device online to OS. */
DECL|macro|TQF_SUSPENDED
mdefine_line|#define TQF_SUSPENDED&t;&t;1
DECL|macro|TQF_RETRY_CMDS
mdefine_line|#define TQF_RETRY_CMDS&t;&t;2
multiline_comment|/*&n; * SCSI LUN Queue structure&n; */
DECL|struct|os_lun
r_typedef
r_struct
id|os_lun
(brace
DECL|member|fclun
r_struct
id|fc_lun
op_star
id|fclun
suffix:semicolon
multiline_comment|/* FC LUN context pointer. */
DECL|member|q_lock
id|spinlock_t
id|q_lock
suffix:semicolon
multiline_comment|/* Lun Lock */
DECL|member|q_flag
r_int
r_int
id|q_flag
suffix:semicolon
DECL|macro|LUN_MPIO_RESET_CNTS
mdefine_line|#define LUN_MPIO_RESET_CNTS&t;1&t;/* Lun */
DECL|macro|LUN_MPIO_BUSY
mdefine_line|#define LUN_MPIO_BUSY&t;&t;2&t;/* Lun is changing paths  */
DECL|macro|LUN_EXEC_DELAYED
mdefine_line|#define LUN_EXEC_DELAYED&t;7&t;/* Lun execution is delayed */
DECL|member|q_timeout
id|u_long
id|q_timeout
suffix:semicolon
multiline_comment|/* total command timeouts */
DECL|member|q_timer
id|atomic_t
id|q_timer
suffix:semicolon
multiline_comment|/* suspend timer */
DECL|member|q_count
r_uint32
id|q_count
suffix:semicolon
multiline_comment|/* current count */
DECL|member|q_max
r_uint32
id|q_max
suffix:semicolon
multiline_comment|/* maxmum count lun can be suspended */
DECL|member|q_state
r_uint8
id|q_state
suffix:semicolon
multiline_comment|/* lun State */
DECL|macro|LUN_STATE_READY
mdefine_line|#define LUN_STATE_READY&t;&t;1&t;/* lun is ready for i/o */
DECL|macro|LUN_STATE_RUN
mdefine_line|#define LUN_STATE_RUN&t;&t;2&t;/* lun has a timer running */
DECL|macro|LUN_STATE_WAIT
mdefine_line|#define LUN_STATE_WAIT&t;&t;3&t;/* lun is suspended */
DECL|macro|LUN_STATE_TIMEOUT
mdefine_line|#define LUN_STATE_TIMEOUT&t;4&t;/* lun has timed out */
DECL|member|io_cnt
id|u_long
id|io_cnt
suffix:semicolon
multiline_comment|/* total xfer count since boot */
DECL|member|out_cnt
id|u_long
id|out_cnt
suffix:semicolon
multiline_comment|/* total outstanding IO count */
DECL|member|w_cnt
id|u_long
id|w_cnt
suffix:semicolon
multiline_comment|/* total writes */
DECL|member|r_cnt
id|u_long
id|r_cnt
suffix:semicolon
multiline_comment|/* total reads */
DECL|member|avg_time
id|u_long
id|avg_time
suffix:semicolon
multiline_comment|/*  */
DECL|typedef|os_lun_t
)brace
id|os_lun_t
suffix:semicolon
multiline_comment|/* LUN BitMask structure definition, array of 32bit words,&n; * 1 bit per lun.  When bit == 1, the lun is masked.&n; * Most significant bit of mask[0] is lun 0, bit 24 is lun 7.&n; */
DECL|struct|lun_bit_mask
r_typedef
r_struct
id|lun_bit_mask
(brace
multiline_comment|/* Must allocate at least enough bits to accomodate all LUNs */
macro_line|#if ((MAX_FIBRE_LUNS &amp; 0x7) == 0)
DECL|member|mask
r_uint8
id|mask
(braket
id|MAX_FIBRE_LUNS
op_rshift
l_int|3
)braket
suffix:semicolon
macro_line|#else
r_uint8
id|mask
(braket
(paren
id|MAX_FIBRE_LUNS
op_plus
l_int|8
)paren
op_rshift
l_int|3
)braket
suffix:semicolon
macro_line|#endif
DECL|typedef|lun_bit_mask_t
)brace
id|lun_bit_mask_t
suffix:semicolon
multiline_comment|/*&n; * Fibre channel port type.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|FCT_UNKNOWN
id|FCT_UNKNOWN
comma
DECL|enumerator|FCT_RSCN
id|FCT_RSCN
comma
DECL|enumerator|FCT_SWITCH
id|FCT_SWITCH
comma
DECL|enumerator|FCT_BROADCAST
id|FCT_BROADCAST
comma
DECL|enumerator|FCT_INITIATOR
id|FCT_INITIATOR
comma
DECL|enumerator|FCT_TARGET
id|FCT_TARGET
DECL|typedef|fc_port_type_t
)brace
id|fc_port_type_t
suffix:semicolon
multiline_comment|/*&n; * Fibre channel port structure.&n; */
DECL|struct|fc_port
r_typedef
r_struct
id|fc_port
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|fcluns
r_struct
id|list_head
id|fcluns
suffix:semicolon
DECL|member|ha
r_struct
id|scsi_qla_host
op_star
id|ha
suffix:semicolon
DECL|member|vis_ha
r_struct
id|scsi_qla_host
op_star
id|vis_ha
suffix:semicolon
multiline_comment|/* only used when suspending lun */
DECL|member|node_name
r_uint8
id|node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|port_name
r_uint8
id|port_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|d_id
id|port_id_t
id|d_id
suffix:semicolon
DECL|member|loop_id
r_uint16
id|loop_id
suffix:semicolon
DECL|member|old_loop_id
r_uint16
id|old_loop_id
suffix:semicolon
DECL|member|port_type
id|fc_port_type_t
id|port_type
suffix:semicolon
DECL|member|state
id|atomic_t
id|state
suffix:semicolon
DECL|member|flags
r_uint32
id|flags
suffix:semicolon
DECL|member|tgt_queue
id|os_tgt_t
op_star
id|tgt_queue
suffix:semicolon
DECL|member|os_target_id
r_uint16
id|os_target_id
suffix:semicolon
DECL|member|iodesc_idx_sent
r_uint16
id|iodesc_idx_sent
suffix:semicolon
DECL|member|port_login_retry_count
r_int
id|port_login_retry_count
suffix:semicolon
DECL|member|login_retry
r_int
id|login_retry
suffix:semicolon
DECL|member|port_down_timer
id|atomic_t
id|port_down_timer
suffix:semicolon
DECL|member|device_type
r_uint8
id|device_type
suffix:semicolon
DECL|member|unused
r_uint8
id|unused
suffix:semicolon
DECL|member|mp_byte
r_uint8
id|mp_byte
suffix:semicolon
multiline_comment|/* multi-path byte (not used) */
DECL|member|cur_path
r_uint8
id|cur_path
suffix:semicolon
multiline_comment|/* current path id */
DECL|member|lun_mask
id|lun_bit_mask_t
id|lun_mask
suffix:semicolon
DECL|typedef|fc_port_t
)brace
id|fc_port_t
suffix:semicolon
multiline_comment|/*&n; * Fibre channel port/lun states.&n; */
DECL|macro|FCS_UNCONFIGURED
mdefine_line|#define FCS_UNCONFIGURED&t;1
DECL|macro|FCS_DEVICE_DEAD
mdefine_line|#define FCS_DEVICE_DEAD&t;&t;2
DECL|macro|FCS_DEVICE_LOST
mdefine_line|#define FCS_DEVICE_LOST&t;&t;3
DECL|macro|FCS_ONLINE
mdefine_line|#define FCS_ONLINE&t;&t;4
DECL|macro|FCS_NOT_SUPPORTED
mdefine_line|#define FCS_NOT_SUPPORTED&t;5
DECL|macro|FCS_FAILOVER
mdefine_line|#define FCS_FAILOVER&t;&t;6
DECL|macro|FCS_FAILOVER_FAILED
mdefine_line|#define FCS_FAILOVER_FAILED&t;7
multiline_comment|/*&n; * FC port flags.&n; */
DECL|macro|FCF_FABRIC_DEVICE
mdefine_line|#define FCF_FABRIC_DEVICE&t;BIT_0
DECL|macro|FCF_LOGIN_NEEDED
mdefine_line|#define FCF_LOGIN_NEEDED&t;BIT_1
DECL|macro|FCF_FO_MASKED
mdefine_line|#define FCF_FO_MASKED&t;&t;BIT_2
DECL|macro|FCF_FAILOVER_NEEDED
mdefine_line|#define FCF_FAILOVER_NEEDED&t;BIT_3
DECL|macro|FCF_RESET_NEEDED
mdefine_line|#define FCF_RESET_NEEDED&t;BIT_4
DECL|macro|FCF_PERSISTENT_BOUND
mdefine_line|#define FCF_PERSISTENT_BOUND&t;BIT_5
DECL|macro|FCF_TAPE_PRESENT
mdefine_line|#define FCF_TAPE_PRESENT&t;BIT_6
DECL|macro|FCF_FARP_DONE
mdefine_line|#define FCF_FARP_DONE&t;&t;BIT_7
DECL|macro|FCF_FARP_FAILED
mdefine_line|#define FCF_FARP_FAILED&t;&t;BIT_8
DECL|macro|FCF_FARP_REPLY_NEEDED
mdefine_line|#define FCF_FARP_REPLY_NEEDED&t;BIT_9
DECL|macro|FCF_AUTH_REQ
mdefine_line|#define FCF_AUTH_REQ&t;&t;BIT_10
DECL|macro|FCF_SEND_AUTH_REQ
mdefine_line|#define FCF_SEND_AUTH_REQ&t;BIT_11
DECL|macro|FCF_RECEIVE_AUTH_REQ
mdefine_line|#define FCF_RECEIVE_AUTH_REQ&t;BIT_12
DECL|macro|FCF_AUTH_SUCCESS
mdefine_line|#define FCF_AUTH_SUCCESS&t;BIT_13
DECL|macro|FCF_RLC_SUPPORT
mdefine_line|#define FCF_RLC_SUPPORT&t;&t;BIT_14
DECL|macro|FCF_CONFIG
mdefine_line|#define FCF_CONFIG&t;&t;BIT_15&t;/* Needed? */
DECL|macro|FCF_RESCAN_NEEDED
mdefine_line|#define FCF_RESCAN_NEEDED&t;BIT_16
DECL|macro|FCF_XP_DEVICE
mdefine_line|#define FCF_XP_DEVICE&t;&t;BIT_17
DECL|macro|FCF_MSA_DEVICE
mdefine_line|#define FCF_MSA_DEVICE&t;&t;BIT_18
DECL|macro|FCF_EVA_DEVICE
mdefine_line|#define FCF_EVA_DEVICE&t;&t;BIT_19
DECL|macro|FCF_MSA_PORT_ACTIVE
mdefine_line|#define FCF_MSA_PORT_ACTIVE&t;BIT_20
DECL|macro|FCF_FAILBACK_DISABLE
mdefine_line|#define FCF_FAILBACK_DISABLE&t;BIT_21
DECL|macro|FCF_FAILOVER_DISABLE
mdefine_line|#define FCF_FAILOVER_DISABLE&t;BIT_22
DECL|macro|FCF_DSXXX_DEVICE
mdefine_line|#define FCF_DSXXX_DEVICE&t;BIT_23
DECL|macro|FCF_AA_EVA_DEVICE
mdefine_line|#define FCF_AA_EVA_DEVICE&t;BIT_24
multiline_comment|/* No loop ID flag. */
DECL|macro|FC_NO_LOOP_ID
mdefine_line|#define FC_NO_LOOP_ID&t;&t;0x1000
multiline_comment|/*&n; * Fibre channel LUN structure.&n; */
DECL|struct|fc_lun
r_typedef
r_struct
id|fc_lun
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|fcport
id|fc_port_t
op_star
id|fcport
suffix:semicolon
DECL|member|o_fcport
id|fc_port_t
op_star
id|o_fcport
suffix:semicolon
DECL|member|lun
r_uint16
id|lun
suffix:semicolon
DECL|member|state
id|atomic_t
id|state
suffix:semicolon
DECL|member|device_type
r_uint8
id|device_type
suffix:semicolon
DECL|member|max_path_retries
r_uint8
id|max_path_retries
suffix:semicolon
DECL|member|flags
r_uint32
id|flags
suffix:semicolon
DECL|typedef|fc_lun_t
)brace
id|fc_lun_t
suffix:semicolon
DECL|macro|FLF_VISIBLE_LUN
mdefine_line|#define&t;FLF_VISIBLE_LUN&t;&t;BIT_0
DECL|macro|FLF_ACTIVE_LUN
mdefine_line|#define&t;FLF_ACTIVE_LUN&t;&t;BIT_1
multiline_comment|/*&n; * FC-CT interface&n; *&n; * NOTE: All structures are big-endian in form.&n; */
DECL|macro|CT_REJECT_RESPONSE
mdefine_line|#define CT_REJECT_RESPONSE&t;0x8001
DECL|macro|CT_ACCEPT_RESPONSE
mdefine_line|#define CT_ACCEPT_RESPONSE&t;0x8002
DECL|macro|NS_N_PORT_TYPE
mdefine_line|#define NS_N_PORT_TYPE&t;0x01
DECL|macro|NS_NL_PORT_TYPE
mdefine_line|#define NS_NL_PORT_TYPE&t;0x02
DECL|macro|NS_NX_PORT_TYPE
mdefine_line|#define NS_NX_PORT_TYPE&t;0x7F
DECL|macro|GA_NXT_CMD
mdefine_line|#define&t;GA_NXT_CMD&t;0x100
DECL|macro|GA_NXT_REQ_SIZE
mdefine_line|#define&t;GA_NXT_REQ_SIZE&t;(16 + 4)
DECL|macro|GA_NXT_RSP_SIZE
mdefine_line|#define&t;GA_NXT_RSP_SIZE&t;(16 + 620)
DECL|macro|GID_PT_CMD
mdefine_line|#define&t;GID_PT_CMD&t;0x1A1
DECL|macro|GID_PT_REQ_SIZE
mdefine_line|#define&t;GID_PT_REQ_SIZE&t;(16 + 4)
DECL|macro|GID_PT_RSP_SIZE
mdefine_line|#define&t;GID_PT_RSP_SIZE&t;(16 + (MAX_FIBRE_DEVICES * 4))
DECL|macro|GPN_ID_CMD
mdefine_line|#define&t;GPN_ID_CMD&t;0x112
DECL|macro|GPN_ID_REQ_SIZE
mdefine_line|#define&t;GPN_ID_REQ_SIZE&t;(16 + 4)
DECL|macro|GPN_ID_RSP_SIZE
mdefine_line|#define&t;GPN_ID_RSP_SIZE&t;(16 + 8)
DECL|macro|GNN_ID_CMD
mdefine_line|#define&t;GNN_ID_CMD&t;0x113
DECL|macro|GNN_ID_REQ_SIZE
mdefine_line|#define&t;GNN_ID_REQ_SIZE&t;(16 + 4)
DECL|macro|GNN_ID_RSP_SIZE
mdefine_line|#define&t;GNN_ID_RSP_SIZE&t;(16 + 8)
DECL|macro|GFT_ID_CMD
mdefine_line|#define&t;GFT_ID_CMD&t;0x117
DECL|macro|GFT_ID_REQ_SIZE
mdefine_line|#define&t;GFT_ID_REQ_SIZE&t;(16 + 4)
DECL|macro|GFT_ID_RSP_SIZE
mdefine_line|#define&t;GFT_ID_RSP_SIZE&t;(16 + 32)
DECL|macro|RFT_ID_CMD
mdefine_line|#define&t;RFT_ID_CMD&t;0x217
DECL|macro|RFT_ID_REQ_SIZE
mdefine_line|#define&t;RFT_ID_REQ_SIZE&t;(16 + 4 + 32)
DECL|macro|RFT_ID_RSP_SIZE
mdefine_line|#define&t;RFT_ID_RSP_SIZE&t;16
DECL|macro|RFF_ID_CMD
mdefine_line|#define&t;RFF_ID_CMD&t;0x21F
DECL|macro|RFF_ID_REQ_SIZE
mdefine_line|#define&t;RFF_ID_REQ_SIZE&t;(16 + 4 + 2 + 1 + 1)
DECL|macro|RFF_ID_RSP_SIZE
mdefine_line|#define&t;RFF_ID_RSP_SIZE&t;16
DECL|macro|RNN_ID_CMD
mdefine_line|#define&t;RNN_ID_CMD&t;0x213
DECL|macro|RNN_ID_REQ_SIZE
mdefine_line|#define&t;RNN_ID_REQ_SIZE&t;(16 + 4 + 8)
DECL|macro|RNN_ID_RSP_SIZE
mdefine_line|#define&t;RNN_ID_RSP_SIZE&t;16
DECL|macro|RSNN_NN_CMD
mdefine_line|#define&t;RSNN_NN_CMD&t; 0x239
DECL|macro|RSNN_NN_REQ_SIZE
mdefine_line|#define&t;RSNN_NN_REQ_SIZE (16 + 8 + 1 + 255)
DECL|macro|RSNN_NN_RSP_SIZE
mdefine_line|#define&t;RSNN_NN_RSP_SIZE 16
multiline_comment|/* CT command header -- request/response common fields */
DECL|struct|ct_cmd_hdr
r_struct
id|ct_cmd_hdr
(brace
DECL|member|revision
r_uint8
id|revision
suffix:semicolon
DECL|member|in_id
r_uint8
id|in_id
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|gs_type
r_uint8
id|gs_type
suffix:semicolon
DECL|member|gs_subtype
r_uint8
id|gs_subtype
suffix:semicolon
DECL|member|options
r_uint8
id|options
suffix:semicolon
DECL|member|reserved
r_uint8
id|reserved
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* CT command request */
DECL|struct|ct_sns_req
r_struct
id|ct_sns_req
(brace
DECL|member|header
r_struct
id|ct_cmd_hdr
id|header
suffix:semicolon
DECL|member|command
r_uint16
id|command
suffix:semicolon
DECL|member|max_rsp_size
r_uint16
id|max_rsp_size
suffix:semicolon
DECL|member|fragment_id
r_uint8
id|fragment_id
suffix:semicolon
DECL|member|reserved
r_uint8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
r_union
(brace
multiline_comment|/* GA_NXT, GPN_ID, GNN_ID, GFT_ID */
r_struct
(brace
DECL|member|reserved
r_uint8
id|reserved
suffix:semicolon
DECL|member|port_id
r_uint8
id|port_id
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|port_id
)brace
id|port_id
suffix:semicolon
r_struct
(brace
DECL|member|port_type
r_uint8
id|port_type
suffix:semicolon
DECL|member|domain
r_uint8
id|domain
suffix:semicolon
DECL|member|area
r_uint8
id|area
suffix:semicolon
DECL|member|reserved
r_uint8
id|reserved
suffix:semicolon
DECL|member|gid_pt
)brace
id|gid_pt
suffix:semicolon
r_struct
(brace
DECL|member|reserved
r_uint8
id|reserved
suffix:semicolon
DECL|member|port_id
r_uint8
id|port_id
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|fc4_types
r_uint8
id|fc4_types
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|rft_id
)brace
id|rft_id
suffix:semicolon
r_struct
(brace
DECL|member|reserved
r_uint8
id|reserved
suffix:semicolon
DECL|member|port_id
r_uint8
id|port_id
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|reserved2
r_uint16
id|reserved2
suffix:semicolon
DECL|member|fc4_feature
r_uint8
id|fc4_feature
suffix:semicolon
DECL|member|fc4_type
r_uint8
id|fc4_type
suffix:semicolon
DECL|member|rff_id
)brace
id|rff_id
suffix:semicolon
r_struct
(brace
DECL|member|reserved
r_uint8
id|reserved
suffix:semicolon
DECL|member|port_id
r_uint8
id|port_id
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|node_name
r_uint8
id|node_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|rnn_id
)brace
id|rnn_id
suffix:semicolon
r_struct
(brace
DECL|member|node_name
r_uint8
id|node_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|name_len
r_uint8
id|name_len
suffix:semicolon
DECL|member|sym_node_name
r_uint8
id|sym_node_name
(braket
l_int|255
)braket
suffix:semicolon
DECL|member|rsnn_nn
)brace
id|rsnn_nn
suffix:semicolon
DECL|member|req
)brace
id|req
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* CT command response header */
DECL|struct|ct_rsp_hdr
r_struct
id|ct_rsp_hdr
(brace
DECL|member|header
r_struct
id|ct_cmd_hdr
id|header
suffix:semicolon
DECL|member|response
r_uint16
id|response
suffix:semicolon
DECL|member|residual
r_uint16
id|residual
suffix:semicolon
DECL|member|fragment_id
r_uint8
id|fragment_id
suffix:semicolon
DECL|member|reason_code
r_uint8
id|reason_code
suffix:semicolon
DECL|member|explanation_code
r_uint8
id|explanation_code
suffix:semicolon
DECL|member|vendor_unique
r_uint8
id|vendor_unique
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ct_sns_gid_pt_data
r_struct
id|ct_sns_gid_pt_data
(brace
DECL|member|control_byte
r_uint8
id|control_byte
suffix:semicolon
DECL|member|port_id
r_uint8
id|port_id
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ct_sns_rsp
r_struct
id|ct_sns_rsp
(brace
DECL|member|header
r_struct
id|ct_rsp_hdr
id|header
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|port_type
r_uint8
id|port_type
suffix:semicolon
DECL|member|port_id
r_uint8
id|port_id
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|port_name
r_uint8
id|port_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|sym_port_name_len
r_uint8
id|sym_port_name_len
suffix:semicolon
DECL|member|sym_port_name
r_uint8
id|sym_port_name
(braket
l_int|255
)braket
suffix:semicolon
DECL|member|node_name
r_uint8
id|node_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|sym_node_name_len
r_uint8
id|sym_node_name_len
suffix:semicolon
DECL|member|sym_node_name
r_uint8
id|sym_node_name
(braket
l_int|255
)braket
suffix:semicolon
DECL|member|init_proc_assoc
r_uint8
id|init_proc_assoc
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|node_ip_addr
r_uint8
id|node_ip_addr
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|class_of_service
r_uint8
id|class_of_service
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|fc4_types
r_uint8
id|fc4_types
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|ip_address
r_uint8
id|ip_address
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|fabric_port_name
r_uint8
id|fabric_port_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|reserved
r_uint8
id|reserved
suffix:semicolon
DECL|member|hard_address
r_uint8
id|hard_address
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ga_nxt
)brace
id|ga_nxt
suffix:semicolon
r_struct
(brace
DECL|member|entries
r_struct
id|ct_sns_gid_pt_data
id|entries
(braket
id|MAX_FIBRE_DEVICES
)braket
suffix:semicolon
DECL|member|gid_pt
)brace
id|gid_pt
suffix:semicolon
r_struct
(brace
DECL|member|port_name
r_uint8
id|port_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|gpn_id
)brace
id|gpn_id
suffix:semicolon
r_struct
(brace
DECL|member|node_name
r_uint8
id|node_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|gnn_id
)brace
id|gnn_id
suffix:semicolon
r_struct
(brace
DECL|member|fc4_types
r_uint8
id|fc4_types
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|gft_id
)brace
id|gft_id
suffix:semicolon
DECL|member|rsp
)brace
id|rsp
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ct_sns_pkt
r_struct
id|ct_sns_pkt
(brace
r_union
(brace
DECL|member|req
r_struct
id|ct_sns_req
id|req
suffix:semicolon
DECL|member|rsp
r_struct
id|ct_sns_rsp
id|rsp
suffix:semicolon
DECL|member|p
)brace
id|p
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * SNS command structures -- for 2200 compatability.&n; */
DECL|macro|RFT_ID_SNS_SCMD_LEN
mdefine_line|#define&t;RFT_ID_SNS_SCMD_LEN&t;22
DECL|macro|RFT_ID_SNS_CMD_SIZE
mdefine_line|#define&t;RFT_ID_SNS_CMD_SIZE&t;60
DECL|macro|RFT_ID_SNS_DATA_SIZE
mdefine_line|#define&t;RFT_ID_SNS_DATA_SIZE&t;16
DECL|macro|RNN_ID_SNS_SCMD_LEN
mdefine_line|#define&t;RNN_ID_SNS_SCMD_LEN&t;10
DECL|macro|RNN_ID_SNS_CMD_SIZE
mdefine_line|#define&t;RNN_ID_SNS_CMD_SIZE&t;36
DECL|macro|RNN_ID_SNS_DATA_SIZE
mdefine_line|#define&t;RNN_ID_SNS_DATA_SIZE&t;16
DECL|macro|GA_NXT_SNS_SCMD_LEN
mdefine_line|#define&t;GA_NXT_SNS_SCMD_LEN&t;6
DECL|macro|GA_NXT_SNS_CMD_SIZE
mdefine_line|#define&t;GA_NXT_SNS_CMD_SIZE&t;28
DECL|macro|GA_NXT_SNS_DATA_SIZE
mdefine_line|#define&t;GA_NXT_SNS_DATA_SIZE&t;(620 + 16)
DECL|macro|GID_PT_SNS_SCMD_LEN
mdefine_line|#define&t;GID_PT_SNS_SCMD_LEN&t;6
DECL|macro|GID_PT_SNS_CMD_SIZE
mdefine_line|#define&t;GID_PT_SNS_CMD_SIZE&t;28
DECL|macro|GID_PT_SNS_DATA_SIZE
mdefine_line|#define&t;GID_PT_SNS_DATA_SIZE&t;(MAX_FIBRE_DEVICES * 4 + 16)
DECL|macro|GPN_ID_SNS_SCMD_LEN
mdefine_line|#define&t;GPN_ID_SNS_SCMD_LEN&t;6
DECL|macro|GPN_ID_SNS_CMD_SIZE
mdefine_line|#define&t;GPN_ID_SNS_CMD_SIZE&t;28
DECL|macro|GPN_ID_SNS_DATA_SIZE
mdefine_line|#define&t;GPN_ID_SNS_DATA_SIZE&t;(8 + 16)
DECL|macro|GNN_ID_SNS_SCMD_LEN
mdefine_line|#define&t;GNN_ID_SNS_SCMD_LEN&t;6
DECL|macro|GNN_ID_SNS_CMD_SIZE
mdefine_line|#define&t;GNN_ID_SNS_CMD_SIZE&t;28
DECL|macro|GNN_ID_SNS_DATA_SIZE
mdefine_line|#define&t;GNN_ID_SNS_DATA_SIZE&t;(8 + 16)
DECL|struct|sns_cmd_pkt
r_struct
id|sns_cmd_pkt
(brace
r_union
(brace
r_struct
(brace
DECL|member|buffer_length
r_uint16
id|buffer_length
suffix:semicolon
DECL|member|reserved_1
r_uint16
id|reserved_1
suffix:semicolon
DECL|member|buffer_address
r_uint32
id|buffer_address
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|subcommand_length
r_uint16
id|subcommand_length
suffix:semicolon
DECL|member|reserved_2
r_uint16
id|reserved_2
suffix:semicolon
DECL|member|subcommand
r_uint16
id|subcommand
suffix:semicolon
DECL|member|size
r_uint16
id|size
suffix:semicolon
DECL|member|reserved_3
r_uint32
id|reserved_3
suffix:semicolon
DECL|member|param
r_uint8
id|param
(braket
l_int|36
)braket
suffix:semicolon
DECL|member|cmd
)brace
id|cmd
suffix:semicolon
DECL|member|rft_data
r_uint8
id|rft_data
(braket
id|RFT_ID_SNS_DATA_SIZE
)braket
suffix:semicolon
DECL|member|rnn_data
r_uint8
id|rnn_data
(braket
id|RNN_ID_SNS_DATA_SIZE
)braket
suffix:semicolon
DECL|member|gan_data
r_uint8
id|gan_data
(braket
id|GA_NXT_SNS_DATA_SIZE
)braket
suffix:semicolon
DECL|member|gid_data
r_uint8
id|gid_data
(braket
id|GID_PT_SNS_DATA_SIZE
)braket
suffix:semicolon
DECL|member|gpn_data
r_uint8
id|gpn_data
(braket
id|GPN_ID_SNS_DATA_SIZE
)braket
suffix:semicolon
DECL|member|gnn_data
r_uint8
id|gnn_data
(braket
id|GNN_ID_SNS_DATA_SIZE
)braket
suffix:semicolon
DECL|member|p
)brace
id|p
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* IO descriptors */
DECL|macro|MAX_IO_DESCRIPTORS
mdefine_line|#define MAX_IO_DESCRIPTORS&t;32
DECL|macro|ABORT_IOCB_CB
mdefine_line|#define ABORT_IOCB_CB&t;&t;0
DECL|macro|ADISC_PORT_IOCB_CB
mdefine_line|#define ADISC_PORT_IOCB_CB&t;1
DECL|macro|LOGOUT_PORT_IOCB_CB
mdefine_line|#define LOGOUT_PORT_IOCB_CB&t;2
DECL|macro|LOGIN_PORT_IOCB_CB
mdefine_line|#define LOGIN_PORT_IOCB_CB&t;3
DECL|macro|LAST_IOCB_CB
mdefine_line|#define LAST_IOCB_CB&t;&t;4
DECL|macro|IODESC_INVALID_INDEX
mdefine_line|#define IODESC_INVALID_INDEX&t;0xFFFF
DECL|macro|IODESC_ADISC_NEEDED
mdefine_line|#define IODESC_ADISC_NEEDED&t;0xFFFE
DECL|macro|IODESC_LOGIN_NEEDED
mdefine_line|#define IODESC_LOGIN_NEEDED&t;0xFFFD
DECL|struct|io_descriptor
r_struct
id|io_descriptor
(brace
DECL|member|used
r_uint16
id|used
suffix:colon
l_int|1
suffix:semicolon
DECL|member|idx
r_uint16
id|idx
suffix:colon
l_int|11
suffix:semicolon
DECL|member|cb_idx
r_uint16
id|cb_idx
suffix:colon
l_int|4
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|ha
r_struct
id|scsi_qla_host
op_star
id|ha
suffix:semicolon
DECL|member|d_id
id|port_id_t
id|d_id
suffix:semicolon
DECL|member|remote_fcport
id|fc_port_t
op_star
id|remote_fcport
suffix:semicolon
DECL|member|signature
r_uint32
id|signature
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|qla_fw_info
r_struct
id|qla_fw_info
(brace
DECL|member|addressing
r_int
r_int
id|addressing
suffix:semicolon
multiline_comment|/* addressing method used to load fw */
DECL|macro|FW_INFO_ADDR_NORMAL
mdefine_line|#define FW_INFO_ADDR_NORMAL&t;0
DECL|macro|FW_INFO_ADDR_EXTENDED
mdefine_line|#define FW_INFO_ADDR_EXTENDED&t;1
DECL|macro|FW_INFO_ADDR_NOMORE
mdefine_line|#define FW_INFO_ADDR_NOMORE&t;0xffff
DECL|member|fwcode
r_int
r_int
op_star
id|fwcode
suffix:semicolon
multiline_comment|/* pointer to FW array */
DECL|member|fwlen
r_int
r_int
op_star
id|fwlen
suffix:semicolon
multiline_comment|/* number of words in array */
DECL|member|fwstart
r_int
r_int
op_star
id|fwstart
suffix:semicolon
multiline_comment|/* start address for F/W */
DECL|member|lfwstart
r_int
r_int
op_star
id|lfwstart
suffix:semicolon
multiline_comment|/* start address (long) for F/W */
)brace
suffix:semicolon
DECL|struct|qla_board_info
r_struct
id|qla_board_info
(brace
DECL|member|drv_name
r_char
op_star
id|drv_name
suffix:semicolon
DECL|member|isp_name
r_char
id|isp_name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|fw_info
r_struct
id|qla_fw_info
op_star
id|fw_info
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Return data from MBC_GET_ID_LIST call. */
DECL|struct|gid_list_info
r_struct
id|gid_list_info
(brace
DECL|member|al_pa
r_uint8
id|al_pa
suffix:semicolon
DECL|member|area
r_uint8
id|area
suffix:semicolon
DECL|member|domain
r_uint8
id|domain
suffix:semicolon
DECL|member|loop_id_2100
r_uint8
id|loop_id_2100
suffix:semicolon
multiline_comment|/* ISP2100/ISP2200 -- 4 bytes. */
DECL|member|loop_id
r_uint16
id|loop_id
suffix:semicolon
multiline_comment|/* ISP23XX         -- 6 bytes. */
)brace
suffix:semicolon
DECL|macro|GID_LIST_SIZE
mdefine_line|#define GID_LIST_SIZE (sizeof(struct gid_list_info) * MAX_FIBRE_DEVICES)
multiline_comment|/*&n; * Linux Host Adapter structure&n; */
DECL|struct|scsi_qla_host
r_typedef
r_struct
id|scsi_qla_host
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* Commonly used flags and state information. */
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
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
r_volatile
r_struct
(brace
DECL|member|init_done
r_uint32
id|init_done
suffix:colon
l_int|1
suffix:semicolon
DECL|member|online
r_uint32
id|online
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mbox_int
r_uint32
id|mbox_int
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mbox_busy
r_uint32
id|mbox_busy
suffix:colon
l_int|1
suffix:semicolon
DECL|member|rscn_queue_overflow
r_uint32
id|rscn_queue_overflow
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reset_active
r_uint32
id|reset_active
suffix:colon
l_int|1
suffix:semicolon
DECL|member|management_server_logged_in
r_uint32
id|management_server_logged_in
suffix:colon
l_int|1
suffix:semicolon
DECL|member|process_response_queue
r_uint32
id|process_response_queue
suffix:colon
l_int|1
suffix:semicolon
DECL|member|disable_risc_code_load
r_uint32
id|disable_risc_code_load
suffix:colon
l_int|1
suffix:semicolon
DECL|member|enable_64bit_addressing
r_uint32
id|enable_64bit_addressing
suffix:colon
l_int|1
suffix:semicolon
DECL|member|enable_lip_reset
r_uint32
id|enable_lip_reset
suffix:colon
l_int|1
suffix:semicolon
DECL|member|enable_lip_full_login
r_uint32
id|enable_lip_full_login
suffix:colon
l_int|1
suffix:semicolon
DECL|member|enable_target_reset
r_uint32
id|enable_target_reset
suffix:colon
l_int|1
suffix:semicolon
DECL|member|enable_led_scheme
r_uint32
id|enable_led_scheme
suffix:colon
l_int|1
suffix:semicolon
DECL|member|flags
)brace
id|flags
suffix:semicolon
DECL|member|loop_state
id|atomic_t
id|loop_state
suffix:semicolon
DECL|macro|LOOP_TIMEOUT
mdefine_line|#define LOOP_TIMEOUT&t;1
DECL|macro|LOOP_DOWN
mdefine_line|#define LOOP_DOWN&t;2
DECL|macro|LOOP_UP
mdefine_line|#define LOOP_UP&t;&t;3
DECL|macro|LOOP_UPDATE
mdefine_line|#define LOOP_UPDATE&t;4
DECL|macro|LOOP_READY
mdefine_line|#define LOOP_READY&t;5
DECL|macro|LOOP_DEAD
mdefine_line|#define LOOP_DEAD&t;6
DECL|member|dpc_flags
r_int
r_int
id|dpc_flags
suffix:semicolon
DECL|macro|RESET_MARKER_NEEDED
mdefine_line|#define&t;RESET_MARKER_NEEDED&t;0&t;/* Send marker to ISP. */
DECL|macro|RESET_ACTIVE
mdefine_line|#define&t;RESET_ACTIVE&t;&t;1
DECL|macro|ISP_ABORT_NEEDED
mdefine_line|#define&t;ISP_ABORT_NEEDED&t;2&t;/* Initiate ISP abort. */
DECL|macro|ABORT_ISP_ACTIVE
mdefine_line|#define&t;ABORT_ISP_ACTIVE&t;3&t;/* ISP abort in progress. */
DECL|macro|LOOP_RESYNC_NEEDED
mdefine_line|#define&t;LOOP_RESYNC_NEEDED&t;4&t;/* Device Resync needed. */
DECL|macro|LOOP_RESYNC_ACTIVE
mdefine_line|#define&t;LOOP_RESYNC_ACTIVE&t;5
DECL|macro|LOCAL_LOOP_UPDATE
mdefine_line|#define LOCAL_LOOP_UPDATE       6&t;/* Perform a local loop update. */
DECL|macro|RSCN_UPDATE
mdefine_line|#define RSCN_UPDATE             7&t;/* Perform an RSCN update. */
DECL|macro|MAILBOX_RETRY
mdefine_line|#define MAILBOX_RETRY           8
DECL|macro|ISP_RESET_NEEDED
mdefine_line|#define ISP_RESET_NEEDED        9&t;/* Initiate a ISP reset. */
DECL|macro|FAILOVER_EVENT_NEEDED
mdefine_line|#define FAILOVER_EVENT_NEEDED   10
DECL|macro|FAILOVER_EVENT
mdefine_line|#define FAILOVER_EVENT&t;&t;11
DECL|macro|FAILOVER_NEEDED
mdefine_line|#define FAILOVER_NEEDED   &t;12
DECL|macro|SCSI_RESTART_NEEDED
mdefine_line|#define SCSI_RESTART_NEEDED&t;13&t;/* Processes SCSI retry queue. */
DECL|macro|PORT_RESTART_NEEDED
mdefine_line|#define PORT_RESTART_NEEDED&t;14&t;/* Processes Retry queue. */
DECL|macro|RESTART_QUEUES_NEEDED
mdefine_line|#define RESTART_QUEUES_NEEDED&t;15&t;/* Restarts the Lun queue. */
DECL|macro|ABORT_QUEUES_NEEDED
mdefine_line|#define ABORT_QUEUES_NEEDED&t;16
DECL|macro|RELOGIN_NEEDED
mdefine_line|#define RELOGIN_NEEDED&t;        17
DECL|macro|LOGIN_RETRY_NEEDED
mdefine_line|#define LOGIN_RETRY_NEEDED&t;18&t;/* Initiate required fabric logins. */
DECL|macro|REGISTER_FC4_NEEDED
mdefine_line|#define REGISTER_FC4_NEEDED&t;19&t;/* SNS FC4 registration required. */
DECL|macro|ISP_ABORT_RETRY
mdefine_line|#define ISP_ABORT_RETRY         20      /* ISP aborted. */
DECL|macro|FCPORT_RESCAN_NEEDED
mdefine_line|#define FCPORT_RESCAN_NEEDED&t;21      /* IO descriptor processing needed */
DECL|macro|IODESC_PROCESS_NEEDED
mdefine_line|#define IODESC_PROCESS_NEEDED&t;22      /* IO descriptor processing needed */
DECL|macro|IOCTL_ERROR_RECOVERY
mdefine_line|#define IOCTL_ERROR_RECOVERY&t;23      
DECL|macro|LOOP_RESET_NEEDED
mdefine_line|#define LOOP_RESET_NEEDED&t;24
DECL|member|device_flags
r_uint32
id|device_flags
suffix:semicolon
DECL|macro|DFLG_LOCAL_DEVICES
mdefine_line|#define DFLG_LOCAL_DEVICES&t;&t;BIT_0
DECL|macro|DFLG_RETRY_LOCAL_DEVICES
mdefine_line|#define DFLG_RETRY_LOCAL_DEVICES&t;BIT_1
DECL|macro|DFLG_FABRIC_DEVICES
mdefine_line|#define DFLG_FABRIC_DEVICES&t;&t;BIT_2
DECL|macro|SWITCH_FOUND
mdefine_line|#define&t;SWITCH_FOUND&t;&t;&t;BIT_3
DECL|macro|DFLG_NO_CABLE
mdefine_line|#define&t;DFLG_NO_CABLE&t;&t;&t;BIT_4
multiline_comment|/* SRB cache. */
DECL|macro|SRB_MIN_REQ
mdefine_line|#define SRB_MIN_REQ&t;128
DECL|member|srb_mempool
id|mempool_t
op_star
id|srb_mempool
suffix:semicolon
multiline_comment|/* This spinlock is used to protect &quot;io transactions&quot;, you must&t;&n;&t; * aquire it before doing any IO to the card, eg with RD_REG*() and&n;&t; * WRT_REG*() for the duration of your entire commandtransaction.&n;&t; *&n;&t; * This spinlock is of lower priority than the io request lock.&n;&t; */
DECL|member|____cacheline_aligned
id|spinlock_t
id|hardware_lock
id|____cacheline_aligned
suffix:semicolon
DECL|member|iobase
id|device_reg_t
id|__iomem
op_star
id|iobase
suffix:semicolon
multiline_comment|/* Base I/O address */
DECL|member|pio_address
r_int
r_int
id|pio_address
suffix:semicolon
DECL|member|pio_length
r_int
r_int
id|pio_length
suffix:semicolon
DECL|macro|MIN_IOBASE_LEN
mdefine_line|#define MIN_IOBASE_LEN&t;&t;0x100
multiline_comment|/* ISP ring lock, rings, and indexes */
DECL|member|request_dma
id|dma_addr_t
id|request_dma
suffix:semicolon
multiline_comment|/* Physical address. */
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
DECL|member|request_q_length
r_uint16
id|request_q_length
suffix:semicolon
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
DECL|member|response_q_length
r_uint16
id|response_q_length
suffix:semicolon
DECL|member|calc_request_entries
r_uint16
(paren
op_star
id|calc_request_entries
)paren
(paren
r_uint16
)paren
suffix:semicolon
DECL|member|build_scsi_iocbs
r_void
(paren
op_star
id|build_scsi_iocbs
)paren
(paren
id|srb_t
op_star
comma
id|cmd_entry_t
op_star
comma
r_uint16
)paren
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
DECL|member|current_outstanding_cmd
r_uint32
id|current_outstanding_cmd
suffix:semicolon
DECL|member|status_srb
id|srb_t
op_star
id|status_srb
suffix:semicolon
multiline_comment|/* Status continuation entry. */
multiline_comment|/*&n;&t; * Need to hold the list_lock with irq&squot;s disabled in order to access&n;&t; * the following list.&n;&t; *&n;&t; * This list_lock is of lower priority than the host_lock.&n;&t; */
DECL|member|____cacheline_aligned
id|spinlock_t
id|list_lock
id|____cacheline_aligned
suffix:semicolon
multiline_comment|/* lock to guard lists which&n;&t;&t;&t;&t;&t;&t; * hold srb_t&squot;s */
DECL|member|retry_queue
r_struct
id|list_head
id|retry_queue
suffix:semicolon
multiline_comment|/* watchdog queue */
DECL|member|done_queue
r_struct
id|list_head
id|done_queue
suffix:semicolon
multiline_comment|/* job on done queue */
DECL|member|failover_queue
r_struct
id|list_head
id|failover_queue
suffix:semicolon
multiline_comment|/* failover list link. */
DECL|member|scsi_retry_queue
r_struct
id|list_head
id|scsi_retry_queue
suffix:semicolon
multiline_comment|/* SCSI retry queue */
DECL|member|pending_queue
r_struct
id|list_head
id|pending_queue
suffix:semicolon
multiline_comment|/* SCSI command pending queue */
DECL|member|done_q_cnt
r_int
r_int
id|done_q_cnt
suffix:semicolon
DECL|member|pending_in_q
r_int
r_int
id|pending_in_q
suffix:semicolon
DECL|member|retry_q_cnt
r_uint32
id|retry_q_cnt
suffix:semicolon
DECL|member|scsi_retry_q_cnt
r_uint32
id|scsi_retry_q_cnt
suffix:semicolon
DECL|member|failover_cnt
r_uint32
id|failover_cnt
suffix:semicolon
DECL|member|last_irq_cpu
r_int
r_int
id|last_irq_cpu
suffix:semicolon
multiline_comment|/* cpu where we got our last irq */
DECL|member|revision
r_uint16
id|revision
suffix:semicolon
DECL|member|ports
r_uint8
id|ports
suffix:semicolon
DECL|member|actthreads
id|u_long
id|actthreads
suffix:semicolon
DECL|member|ipreq_cnt
id|u_long
id|ipreq_cnt
suffix:semicolon
DECL|member|qthreads
id|u_long
id|qthreads
suffix:semicolon
DECL|member|total_isr_cnt
r_uint32
id|total_isr_cnt
suffix:semicolon
multiline_comment|/* Interrupt count */
DECL|member|total_isp_aborts
r_uint32
id|total_isp_aborts
suffix:semicolon
multiline_comment|/* controller err cnt */
DECL|member|total_lip_cnt
r_uint32
id|total_lip_cnt
suffix:semicolon
multiline_comment|/* LIP cnt */
DECL|member|total_dev_errs
r_uint32
id|total_dev_errs
suffix:semicolon
multiline_comment|/* device error cnt */
DECL|member|total_ios
r_uint32
id|total_ios
suffix:semicolon
multiline_comment|/* IO cnt */
DECL|member|total_bytes
r_uint64
id|total_bytes
suffix:semicolon
multiline_comment|/* xfr byte cnt */
DECL|member|total_mbx_timeout
r_uint32
id|total_mbx_timeout
suffix:semicolon
multiline_comment|/* mailbox timeout cnt */
DECL|member|total_loop_resync
r_uint32
id|total_loop_resync
suffix:semicolon
multiline_comment|/* loop resyn cnt */
DECL|member|dropped_frame_error_cnt
r_uint32
id|dropped_frame_error_cnt
suffix:semicolon
multiline_comment|/* ISP configuration data. */
DECL|member|loop_id
r_uint16
id|loop_id
suffix:semicolon
multiline_comment|/* Host adapter loop id */
DECL|member|fb_rev
r_uint16
id|fb_rev
suffix:semicolon
DECL|member|d_id
id|port_id_t
id|d_id
suffix:semicolon
multiline_comment|/* Host adapter port id */
DECL|member|max_public_loop_ids
r_uint16
id|max_public_loop_ids
suffix:semicolon
DECL|member|min_external_loopid
r_uint16
id|min_external_loopid
suffix:semicolon
multiline_comment|/* First external loop Id */
DECL|member|link_data_rate
r_uint16
id|link_data_rate
suffix:semicolon
multiline_comment|/* F/W operating speed */
DECL|member|current_topology
r_uint8
id|current_topology
suffix:semicolon
DECL|member|prev_topology
r_uint8
id|prev_topology
suffix:semicolon
DECL|macro|ISP_CFG_NL
mdefine_line|#define ISP_CFG_NL&t;1
DECL|macro|ISP_CFG_N
mdefine_line|#define ISP_CFG_N&t;2
DECL|macro|ISP_CFG_FL
mdefine_line|#define ISP_CFG_FL&t;4
DECL|macro|ISP_CFG_F
mdefine_line|#define ISP_CFG_F&t;8
DECL|member|operating_mode
r_uint8
id|operating_mode
suffix:semicolon
multiline_comment|/* F/W operating mode */
DECL|macro|LOOP
mdefine_line|#define LOOP      0
DECL|macro|P2P
mdefine_line|#define P2P       1
DECL|macro|LOOP_P2P
mdefine_line|#define LOOP_P2P  2
DECL|macro|P2P_LOOP
mdefine_line|#define P2P_LOOP  3
DECL|member|marker_needed
r_uint8
id|marker_needed
suffix:semicolon
DECL|member|sns_retry_cnt
r_uint8
id|sns_retry_cnt
suffix:semicolon
DECL|member|mem_err
r_uint8
id|mem_err
suffix:semicolon
DECL|member|interrupts_on
r_uint8
id|interrupts_on
suffix:semicolon
multiline_comment|/* HBA serial number */
DECL|member|serial0
r_uint8
id|serial0
suffix:semicolon
DECL|member|serial1
r_uint8
id|serial1
suffix:semicolon
DECL|member|serial2
r_uint8
id|serial2
suffix:semicolon
multiline_comment|/* NVRAM configuration data */
DECL|member|nvram_base
r_uint16
id|nvram_base
suffix:semicolon
DECL|member|loop_reset_delay
r_uint16
id|loop_reset_delay
suffix:semicolon
DECL|member|minimum_timeout
r_uint16
id|minimum_timeout
suffix:semicolon
DECL|member|retry_count
r_uint8
id|retry_count
suffix:semicolon
DECL|member|login_timeout
r_uint8
id|login_timeout
suffix:semicolon
DECL|member|r_a_tov
r_uint16
id|r_a_tov
suffix:semicolon
DECL|member|port_down_retry_count
r_int
id|port_down_retry_count
suffix:semicolon
DECL|member|loop_down_timeout
r_uint8
id|loop_down_timeout
suffix:semicolon
DECL|member|mbx_count
r_uint8
id|mbx_count
suffix:semicolon
DECL|member|max_probe_luns
r_uint16
id|max_probe_luns
suffix:semicolon
DECL|member|max_luns
r_uint16
id|max_luns
suffix:semicolon
DECL|member|max_targets
r_uint16
id|max_targets
suffix:semicolon
DECL|member|last_loop_id
r_uint16
id|last_loop_id
suffix:semicolon
DECL|member|login_retry_count
r_uint32
id|login_retry_count
suffix:semicolon
multiline_comment|/* Fibre Channel Device List. */
DECL|member|fcports
r_struct
id|list_head
id|fcports
suffix:semicolon
DECL|member|rscn_fcports
r_struct
id|list_head
id|rscn_fcports
suffix:semicolon
DECL|member|io_descriptors
r_struct
id|io_descriptor
id|io_descriptors
(braket
id|MAX_IO_DESCRIPTORS
)braket
suffix:semicolon
DECL|member|iodesc_signature
r_uint16
id|iodesc_signature
suffix:semicolon
multiline_comment|/* OS target queue pointers. */
DECL|member|otgt
id|os_tgt_t
op_star
id|otgt
(braket
id|MAX_FIBRE_DEVICES
)braket
suffix:semicolon
multiline_comment|/* RSCN queue. */
DECL|member|rscn_queue
r_uint32
id|rscn_queue
(braket
id|MAX_RSCN_COUNT
)braket
suffix:semicolon
DECL|member|rscn_in_ptr
r_uint8
id|rscn_in_ptr
suffix:semicolon
DECL|member|rscn_out_ptr
r_uint8
id|rscn_out_ptr
suffix:semicolon
multiline_comment|/* SNS command interfaces. */
DECL|member|ms_iocb
id|ms_iocb_entry_t
op_star
id|ms_iocb
suffix:semicolon
DECL|member|ms_iocb_dma
id|dma_addr_t
id|ms_iocb_dma
suffix:semicolon
DECL|member|ct_sns
r_struct
id|ct_sns_pkt
op_star
id|ct_sns
suffix:semicolon
DECL|member|ct_sns_dma
id|dma_addr_t
id|ct_sns_dma
suffix:semicolon
multiline_comment|/* SNS command interfaces for 2200. */
DECL|member|sns_cmd
r_struct
id|sns_cmd_pkt
op_star
id|sns_cmd
suffix:semicolon
DECL|member|sns_cmd_dma
id|dma_addr_t
id|sns_cmd_dma
suffix:semicolon
DECL|member|dpc_pid
id|pid_t
id|dpc_pid
suffix:semicolon
DECL|member|dpc_should_die
r_int
id|dpc_should_die
suffix:semicolon
DECL|member|dpc_inited
r_struct
id|completion
id|dpc_inited
suffix:semicolon
DECL|member|dpc_exited
r_struct
id|completion
id|dpc_exited
suffix:semicolon
DECL|member|dpc_wait
r_struct
id|semaphore
op_star
id|dpc_wait
suffix:semicolon
DECL|member|dpc_active
r_uint8
id|dpc_active
suffix:semicolon
multiline_comment|/* DPC routine is active */
multiline_comment|/* Timeout timers. */
DECL|member|queue_restart_timer
r_uint8
id|queue_restart_timer
suffix:semicolon
DECL|member|loop_down_abort_time
r_uint8
id|loop_down_abort_time
suffix:semicolon
multiline_comment|/* port down timer */
DECL|member|loop_down_timer
id|atomic_t
id|loop_down_timer
suffix:semicolon
multiline_comment|/* loop down timer */
DECL|member|link_down_timeout
r_uint8
id|link_down_timeout
suffix:semicolon
multiline_comment|/* link down timeout */
DECL|member|timer_active
r_uint32
id|timer_active
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|gid_list_dma
id|dma_addr_t
id|gid_list_dma
suffix:semicolon
DECL|member|gid_list
r_struct
id|gid_list_info
op_star
id|gid_list
suffix:semicolon
DECL|member|rlc_rsp_dma
id|dma_addr_t
id|rlc_rsp_dma
suffix:semicolon
DECL|member|rlc_rsp
id|rpt_lun_cmd_rsp_t
op_star
id|rlc_rsp
suffix:semicolon
multiline_comment|/* Small DMA pool allocations -- maximum 256 bytes in length. */
DECL|macro|DMA_POOL_SIZE
mdefine_line|#define DMA_POOL_SIZE&t;256
DECL|member|s_dma_pool
r_struct
id|dma_pool
op_star
id|s_dma_pool
suffix:semicolon
DECL|member|init_cb_dma
id|dma_addr_t
id|init_cb_dma
suffix:semicolon
DECL|member|init_cb
id|init_cb_t
op_star
id|init_cb
suffix:semicolon
DECL|member|iodesc_pd_dma
id|dma_addr_t
id|iodesc_pd_dma
suffix:semicolon
DECL|member|iodesc_pd
id|port_database_t
op_star
id|iodesc_pd
suffix:semicolon
multiline_comment|/* These are used by mailbox operations. */
DECL|member|mailbox_out
r_volatile
r_uint16
id|mailbox_out
(braket
id|MAILBOX_REGISTER_COUNT
)braket
suffix:semicolon
DECL|member|mcp
id|mbx_cmd_t
op_star
id|mcp
suffix:semicolon
DECL|member|mbx_cmd_flags
r_int
r_int
id|mbx_cmd_flags
suffix:semicolon
DECL|macro|MBX_INTERRUPT
mdefine_line|#define MBX_INTERRUPT&t;1
DECL|macro|MBX_INTR_WAIT
mdefine_line|#define MBX_INTR_WAIT&t;2
DECL|macro|MBX_UPDATE_FLASH_ACTIVE
mdefine_line|#define MBX_UPDATE_FLASH_ACTIVE&t;3
DECL|member|mbx_reg_lock
id|spinlock_t
id|mbx_reg_lock
suffix:semicolon
multiline_comment|/* Mbx Cmd Register Lock */
DECL|member|mbx_cmd_sem
r_struct
id|semaphore
id|mbx_cmd_sem
suffix:semicolon
multiline_comment|/* Serialialize mbx access */
DECL|member|mbx_intr_sem
r_struct
id|semaphore
id|mbx_intr_sem
suffix:semicolon
multiline_comment|/* Used for completion notification */
DECL|member|mbx_flags
r_uint32
id|mbx_flags
suffix:semicolon
DECL|macro|MBX_IN_PROGRESS
mdefine_line|#define  MBX_IN_PROGRESS&t;BIT_0
DECL|macro|MBX_BUSY
mdefine_line|#define  MBX_BUSY&t;&t;BIT_1&t;/* Got the Access */
DECL|macro|MBX_SLEEPING_ON_SEM
mdefine_line|#define  MBX_SLEEPING_ON_SEM&t;BIT_2 
DECL|macro|MBX_POLLING_FOR_COMP
mdefine_line|#define  MBX_POLLING_FOR_COMP&t;BIT_3
DECL|macro|MBX_COMPLETED
mdefine_line|#define  MBX_COMPLETED&t;&t;BIT_4
DECL|macro|MBX_TIMEDOUT
mdefine_line|#define  MBX_TIMEDOUT&t;&t;BIT_5 
DECL|macro|MBX_ACCESS_TIMEDOUT
mdefine_line|#define  MBX_ACCESS_TIMEDOUT&t;BIT_6
DECL|member|mc
id|mbx_cmd_t
id|mc
suffix:semicolon
DECL|member|cmdline
r_uint8
op_star
id|cmdline
suffix:semicolon
DECL|member|failover_type
r_uint32
id|failover_type
suffix:semicolon
DECL|member|failback_delay
r_uint32
id|failback_delay
suffix:semicolon
DECL|member|cfg_flags
r_int
r_int
id|cfg_flags
suffix:semicolon
DECL|macro|CFG_ACTIVE
mdefine_line|#define&t;CFG_ACTIVE&t;0&t;/* CFG during a failover, event update, or ioctl */
DECL|macro|CFG_FAILOVER
mdefine_line|#define&t;CFG_FAILOVER&t;1&t;/* CFG during path change */
DECL|member|binding_type
r_uint32
id|binding_type
suffix:semicolon
DECL|macro|BIND_BY_PORT_NAME
mdefine_line|#define BIND_BY_PORT_NAME&t;0
DECL|macro|BIND_BY_PORT_ID
mdefine_line|#define BIND_BY_PORT_ID&t;&t;1
multiline_comment|/* Basic firmware related information. */
DECL|member|brd_info
r_struct
id|qla_board_info
op_star
id|brd_info
suffix:semicolon
DECL|member|fw_major_version
r_uint16
id|fw_major_version
suffix:semicolon
DECL|member|fw_minor_version
r_uint16
id|fw_minor_version
suffix:semicolon
DECL|member|fw_subminor_version
r_uint16
id|fw_subminor_version
suffix:semicolon
DECL|member|fw_attributes
r_uint16
id|fw_attributes
suffix:semicolon
DECL|member|fw_memory_size
r_uint32
id|fw_memory_size
suffix:semicolon
DECL|member|fw_transfer_size
r_uint32
id|fw_transfer_size
suffix:semicolon
DECL|member|fw_options
r_uint16
id|fw_options
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* slots: 1,2,3,10,11 */
DECL|member|fw_seriallink_options
r_uint8
id|fw_seriallink_options
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Firmware dump information. */
DECL|member|fw_dump
r_void
op_star
id|fw_dump
suffix:semicolon
DECL|member|fw_dump_order
r_int
id|fw_dump_order
suffix:semicolon
DECL|member|fw_dump_reading
r_int
id|fw_dump_reading
suffix:semicolon
DECL|member|fw_dump_buffer
r_char
op_star
id|fw_dump_buffer
suffix:semicolon
DECL|member|fw_dump_buffer_len
r_int
id|fw_dump_buffer_len
suffix:semicolon
DECL|member|host_str
r_uint8
id|host_str
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|pci_attr
r_uint16
id|pci_attr
suffix:semicolon
DECL|member|product_id
r_uint16
id|product_id
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|model_number
r_uint8
id|model_number
(braket
l_int|16
op_plus
l_int|1
)braket
suffix:semicolon
DECL|macro|BINZERO
mdefine_line|#define BINZERO&t;&t;&quot;&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&quot;
DECL|member|model_desc
r_char
op_star
id|model_desc
suffix:semicolon
DECL|member|node_name
r_uint8
id|node_name
(braket
id|WWN_SIZE
)braket
suffix:semicolon
DECL|member|nvram_version
r_uint8
id|nvram_version
suffix:semicolon
DECL|member|isp_abort_cnt
r_uint32
id|isp_abort_cnt
suffix:semicolon
multiline_comment|/* Adapter I/O statistics for failover */
DECL|member|IosRequested
r_uint64
id|IosRequested
suffix:semicolon
DECL|member|BytesRequested
r_uint64
id|BytesRequested
suffix:semicolon
DECL|member|IosExecuted
r_uint64
id|IosExecuted
suffix:semicolon
DECL|member|BytesExecuted
r_uint64
id|BytesExecuted
suffix:semicolon
multiline_comment|/* Needed for BEACON */
DECL|member|beacon_blink_led
r_uint16
id|beacon_blink_led
suffix:semicolon
DECL|member|beacon_green_on
r_uint16
id|beacon_green_on
suffix:semicolon
DECL|typedef|scsi_qla_host_t
)brace
id|scsi_qla_host_t
suffix:semicolon
multiline_comment|/*&n; * Macros to help code, maintain, etc.&n; */
DECL|macro|LOOP_TRANSITION
mdefine_line|#define LOOP_TRANSITION(ha) &bslash;&n;&t;(test_bit(ISP_ABORT_NEEDED, &amp;ha-&gt;dpc_flags) || &bslash;&n;&t; test_bit(LOOP_RESYNC_NEEDED, &amp;ha-&gt;dpc_flags))
DECL|macro|LOOP_NOT_READY
mdefine_line|#define LOOP_NOT_READY(ha) &bslash;&n;&t;((test_bit(ISP_ABORT_NEEDED, &amp;ha-&gt;dpc_flags) || &bslash;&n;&t;  test_bit(ABORT_ISP_ACTIVE, &amp;ha-&gt;dpc_flags) || &bslash;&n;&t;  test_bit(LOOP_RESYNC_NEEDED, &amp;ha-&gt;dpc_flags) || &bslash;&n;&t;  test_bit(LOOP_RESYNC_ACTIVE, &amp;ha-&gt;dpc_flags)) || &bslash;&n;&t; atomic_read(&amp;ha-&gt;loop_state) == LOOP_DOWN)
DECL|macro|LOOP_RDY
mdefine_line|#define LOOP_RDY(ha)&t;(!LOOP_NOT_READY(ha))
DECL|macro|TGT_Q
mdefine_line|#define TGT_Q(ha, t) (ha-&gt;otgt[t])
DECL|macro|LUN_Q
mdefine_line|#define LUN_Q(ha, t, l)&t;(TGT_Q(ha, t)-&gt;olun[l])
DECL|macro|GET_LU_Q
mdefine_line|#define GET_LU_Q(ha, t, l) ((TGT_Q(ha,t) != NULL)? TGT_Q(ha, t)-&gt;olun[l] : NULL)
DECL|macro|to_qla_host
mdefine_line|#define to_qla_host(x)&t;&t;((scsi_qla_host_t *) (x)-&gt;hostdata)
DECL|macro|qla_printk
mdefine_line|#define qla_printk(level, ha, format, arg...) &bslash;&n;&t;dev_printk(level , &amp;((ha)-&gt;pdev-&gt;dev) , format , ## arg)
multiline_comment|/*&n; * qla2x00 local function return status codes&n; */
DECL|macro|MBS_MASK
mdefine_line|#define MBS_MASK&t;&t;0x3fff
DECL|macro|QLA_SUCCESS
mdefine_line|#define QLA_SUCCESS&t;&t;(MBS_COMMAND_COMPLETE &amp; MBS_MASK)
DECL|macro|QLA_INVALID_COMMAND
mdefine_line|#define QLA_INVALID_COMMAND&t;(MBS_INVALID_COMMAND &amp; MBS_MASK)
DECL|macro|QLA_INTERFACE_ERROR
mdefine_line|#define QLA_INTERFACE_ERROR&t;(MBS_HOST_INTERFACE_ERROR &amp; MBS_MASK)
DECL|macro|QLA_TEST_FAILED
mdefine_line|#define QLA_TEST_FAILED&t;&t;(MBS_TEST_FAILED &amp; MBS_MASK)
DECL|macro|QLA_COMMAND_ERROR
mdefine_line|#define QLA_COMMAND_ERROR&t;(MBS_COMMAND_ERROR &amp; MBS_MASK)
DECL|macro|QLA_PARAMETER_ERROR
mdefine_line|#define QLA_PARAMETER_ERROR&t;(MBS_COMMAND_PARAMETER_ERROR &amp; MBS_MASK)
DECL|macro|QLA_PORT_ID_USED
mdefine_line|#define QLA_PORT_ID_USED&t;(MBS_PORT_ID_USED &amp; MBS_MASK)
DECL|macro|QLA_LOOP_ID_USED
mdefine_line|#define QLA_LOOP_ID_USED&t;(MBS_LOOP_ID_USED &amp; MBS_MASK)
DECL|macro|QLA_ALL_IDS_IN_USE
mdefine_line|#define QLA_ALL_IDS_IN_USE&t;(MBS_ALL_IDS_IN_USE &amp; MBS_MASK)
DECL|macro|QLA_NOT_LOGGED_IN
mdefine_line|#define QLA_NOT_LOGGED_IN&t;(MBS_NOT_LOGGED_IN &amp; MBS_MASK)
DECL|macro|QLA_FUNCTION_TIMEOUT
mdefine_line|#define QLA_FUNCTION_TIMEOUT&t;&t;0x100
DECL|macro|QLA_FUNCTION_PARAMETER_ERROR
mdefine_line|#define QLA_FUNCTION_PARAMETER_ERROR&t;0x101
DECL|macro|QLA_FUNCTION_FAILED
mdefine_line|#define QLA_FUNCTION_FAILED&t;&t;0x102
DECL|macro|QLA_MEMORY_ALLOC_FAILED
mdefine_line|#define QLA_MEMORY_ALLOC_FAILED&t;&t;0x103
DECL|macro|QLA_LOCK_TIMEOUT
mdefine_line|#define QLA_LOCK_TIMEOUT&t;&t;0x104
DECL|macro|QLA_ABORTED
mdefine_line|#define QLA_ABORTED&t;&t;&t;0x105
DECL|macro|QLA_SUSPENDED
mdefine_line|#define QLA_SUSPENDED&t;&t;&t;0x106
DECL|macro|QLA_BUSY
mdefine_line|#define QLA_BUSY&t;&t;&t;0x107
DECL|macro|QLA_RSCNS_HANDLED
mdefine_line|#define QLA_RSCNS_HANDLED&t;&t;0x108
multiline_comment|/*&n;* Stat info for all adpaters&n;*/
DECL|struct|_qla2x00stats
r_struct
id|_qla2x00stats
(brace
DECL|member|mboxtout
r_int
r_int
id|mboxtout
suffix:semicolon
multiline_comment|/* mailbox timeouts */
DECL|member|mboxerr
r_int
r_int
id|mboxerr
suffix:semicolon
multiline_comment|/* mailbox errors */
DECL|member|ispAbort
r_int
r_int
id|ispAbort
suffix:semicolon
multiline_comment|/* ISP aborts */
DECL|member|debugNo
r_int
r_int
id|debugNo
suffix:semicolon
DECL|member|loop_resync
r_int
r_int
id|loop_resync
suffix:semicolon
DECL|member|outarray_full
r_int
r_int
id|outarray_full
suffix:semicolon
DECL|member|retry_q_cnt
r_int
r_int
id|retry_q_cnt
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NVRAM_DELAY
mdefine_line|#define NVRAM_DELAY()&t;&t;udelay(10)
DECL|macro|INVALID_HANDLE
mdefine_line|#define INVALID_HANDLE&t;(MAX_OUTSTANDING_COMMANDS+1)
multiline_comment|/*&n; * Flash support definitions&n; */
DECL|macro|FLASH_IMAGE_SIZE
mdefine_line|#define FLASH_IMAGE_SIZE&t;131072
macro_line|#include &quot;qla_gbl.h&quot;
macro_line|#include &quot;qla_dbg.h&quot;
macro_line|#include &quot;qla_inline.h&quot;
macro_line|#include &quot;qla_listops.h&quot;
multiline_comment|/*&n;* String arrays&n;*/
DECL|macro|LINESIZE
mdefine_line|#define LINESIZE    256
DECL|macro|MAXARGS
mdefine_line|#define MAXARGS      26
DECL|macro|CMD_SP
mdefine_line|#define CMD_SP(Cmnd)&t;&t;((Cmnd)-&gt;SCp.ptr)
DECL|macro|CMD_COMPL_STATUS
mdefine_line|#define CMD_COMPL_STATUS(Cmnd)  ((Cmnd)-&gt;SCp.this_residual)
DECL|macro|CMD_RESID_LEN
mdefine_line|#define CMD_RESID_LEN(Cmnd)&t;((Cmnd)-&gt;SCp.buffers_residual)
DECL|macro|CMD_SCSI_STATUS
mdefine_line|#define CMD_SCSI_STATUS(Cmnd)&t;((Cmnd)-&gt;SCp.Status)
DECL|macro|CMD_ACTUAL_SNSLEN
mdefine_line|#define CMD_ACTUAL_SNSLEN(Cmnd)&t;((Cmnd)-&gt;SCp.Message)
DECL|macro|CMD_ENTRY_STATUS
mdefine_line|#define CMD_ENTRY_STATUS(Cmnd)&t;((Cmnd)-&gt;SCp.have_data_in)
macro_line|#endif
eof
