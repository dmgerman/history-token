multiline_comment|/*&n; *&n; * Copyright (C) Eicon Technology Corporation, 2000.&n; *&n; * Eicon File Revision :    1.5  &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY OF ANY KIND WHATSOEVER INCLUDING ANY &n; * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  &n; * See the GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/* External Diva Server driver include file */
macro_line|#if !defined(DIVAS_H)
DECL|macro|DIVAS_H
mdefine_line|#define DIVAS_H
macro_line|#include &quot;sys.h&quot;
multiline_comment|/* IOCTL commands */
DECL|macro|DIA_IOCTL_INIT
mdefine_line|#define&t;DIA_IOCTL_INIT&t;&t;&t;&t;(0)
DECL|macro|DIA_IOCTL_LOAD
mdefine_line|#define&t;DIA_IOCTL_LOAD&t;&t;&t;&t;(1)
DECL|macro|DIA_IOCTL_CONFIG
mdefine_line|#define&t;DIA_IOCTL_CONFIG&t;&t;&t;(2)
DECL|macro|DIA_IOCTL_START
mdefine_line|#define&t;DIA_IOCTL_START&t;&t;&t;&t;(3)
DECL|macro|DIA_IOCTL_GET_NUM
mdefine_line|#define&t;DIA_IOCTL_GET_NUM&t;&t;&t;(4)
DECL|macro|DIA_IOCTL_GET_LIST
mdefine_line|#define&t;DIA_IOCTL_GET_LIST&t;&t;&t;(5)
DECL|macro|DIA_IOCTL_LOG
mdefine_line|#define&t;DIA_IOCTL_LOG&t;&t;&t;&t;(6)
DECL|macro|DIA_IOCTL_DETECT
mdefine_line|#define&t;DIA_IOCTL_DETECT&t;&t;&t;(7)
DECL|macro|DIA_IOCTL_SPACE
mdefine_line|#define&t;DIA_IOCTL_SPACE&t;&t;&t;&t;(8)
DECL|macro|DIA_IOCTL_GET_MEM
mdefine_line|#define DIA_IOCTL_GET_MEM           (9)
DECL|macro|DIA_IOCTL_FLAVOUR
mdefine_line|#define DIA_IOCTL_FLAVOUR&t;&t;&t;(10)
DECL|macro|DIA_IOCTL_XLOG_REQ
mdefine_line|#define&t;DIA_IOCTL_XLOG_REQ&t;&t;&t;(11)
multiline_comment|/* Error codes */
DECL|macro|XLOG_ERR_CARD_NUM
mdefine_line|#define XLOG_ERR_CARD_NUM&t;(13)
DECL|macro|XLOG_ERR_DONE
mdefine_line|#define XLOG_ERR_DONE&t;&t;(14)
DECL|macro|XLOG_ERR_CMD
mdefine_line|#define XLOG_ERR_CMD&t;&t;(15)
DECL|macro|XLOG_ERR_TIMEOUT
mdefine_line|#define XLOG_ERR_TIMEOUT&t;(16)
DECL|macro|XLOG_ERR_CARD_STATE
mdefine_line|#define XLOG_ERR_CARD_STATE&t;(17)
DECL|macro|XLOG_ERR_UNKNOWN
mdefine_line|#define XLOG_ERR_UNKNOWN&t;(18)
DECL|macro|XLOG_OK
mdefine_line|#define XLOG_OK &t;&t;&t;(0)
multiline_comment|/* Adapter states */
DECL|macro|DIA_UNKNOWN
mdefine_line|#define DIA_UNKNOWN&t;&t;(0)
DECL|macro|DIA_RESET
mdefine_line|#define DIA_RESET&t;&t;(1)
DECL|macro|DIA_LOADED
mdefine_line|#define DIA_LOADED&t;&t;(2)
DECL|macro|DIA_CONFIGURED
mdefine_line|#define DIA_CONFIGURED&t;(3)
DECL|macro|DIA_RUNNING
mdefine_line|#define DIA_RUNNING&t;&t;(4)
multiline_comment|/* Stucture for getting card specific information from active cad driver */
r_typedef
r_struct
(brace
DECL|member|card_type
r_int
id|card_type
suffix:semicolon
DECL|member|card_slot
r_int
id|card_slot
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|typedef|dia_card_list_t
)brace
id|dia_card_list_t
suffix:semicolon
multiline_comment|/* use following to select which logging to have active */
DECL|macro|DIVAS_LOG_DEBUG
mdefine_line|#define&t;DIVAS_LOG_DEBUG&t;&t;(1 &lt;&lt; 0)
DECL|macro|DIVAS_LOG_XLOG
mdefine_line|#define&t;DIVAS_LOG_XLOG&t;&t;(1 &lt;&lt; 1)
DECL|macro|DIVAS_LOG_IDI
mdefine_line|#define&t;DIVAS_LOG_IDI&t;&t;(1 &lt;&lt; 2)
DECL|macro|DIVAS_LOG_CAPI
mdefine_line|#define&t;DIVAS_LOG_CAPI&t;&t;(1 &lt;&lt; 3)
multiline_comment|/* stucture for DIA_IOCTL_LOG to get information from adapter */
r_typedef
r_struct
(brace
DECL|member|card_id
r_int
id|card_id
suffix:semicolon
DECL|member|log_types
r_int
id|log_types
suffix:semicolon
multiline_comment|/* bit mask of log types: use DIVAS_LOG_XXX */
DECL|typedef|dia_log_t
)brace
id|dia_log_t
suffix:semicolon
multiline_comment|/* list of cards supported by this driver */
DECL|macro|DIA_CARD_TYPE_DIVA_SERVER
mdefine_line|#define&t;DIA_CARD_TYPE_DIVA_SERVER&t;(0)&t;/* Diva Server PRI */
DECL|macro|DIA_CARD_TYPE_DIVA_SERVER_B
mdefine_line|#define&t;DIA_CARD_TYPE_DIVA_SERVER_B&t;(1)&t;/* Diva Server BRI */
DECL|macro|DIA_CARD_TYPE_DIVA_SERVER_Q
mdefine_line|#define&t;DIA_CARD_TYPE_DIVA_SERVER_Q&t;(2)&t;/* Diva Server 4-BRI */
multiline_comment|/* bus types */
DECL|macro|DIA_BUS_TYPE_ISA
mdefine_line|#define&t;DIA_BUS_TYPE_ISA&t;&t;(0)
DECL|macro|DIA_BUS_TYPE_ISA_PNP
mdefine_line|#define&t;DIA_BUS_TYPE_ISA_PNP&t;(1)
DECL|macro|DIA_BUS_TYPE_PCI
mdefine_line|#define&t;DIA_BUS_TYPE_PCI&t;&t;(2)
DECL|macro|DIA_BUS_TYPE_MCA
mdefine_line|#define&t;DIA_BUS_TYPE_MCA&t;&t;(3)
multiline_comment|/* types of memory used (index for memory array below) */
DECL|macro|DIVAS_RAM_MEMORY
mdefine_line|#define DIVAS_RAM_MEMORY &t;0
DECL|macro|DIVAS_REG_MEMORY
mdefine_line|#define DIVAS_REG_MEMORY &t;1
DECL|macro|DIVAS_CFG_MEMORY
mdefine_line|#define DIVAS_CFG_MEMORY &t;2
DECL|macro|DIVAS_SHARED_MEMORY
mdefine_line|#define DIVAS_SHARED_MEMORY 3
DECL|macro|DIVAS_CTL_MEMORY
mdefine_line|#define DIVAS_CTL_MEMORY&t;4
multiline_comment|/*&n; * card config information&n; * passed as parameter to DIA_IOCTL_INIT ioctl to initialise new card&n; */
r_typedef
r_struct
(brace
DECL|member|card_id
r_int
id|card_id
suffix:semicolon
multiline_comment|/* unique id assigned to this card */
DECL|member|card_type
r_int
id|card_type
suffix:semicolon
multiline_comment|/* use DIA_CARD_TYPE_xxx above */
DECL|member|bus_type
r_int
id|bus_type
suffix:semicolon
multiline_comment|/* use DIA_BUS_TYPE_xxx above */
DECL|member|bus_num
r_int
id|bus_num
suffix:semicolon
multiline_comment|/* bus number (instance number of bus type) */
DECL|member|func_num
r_int
id|func_num
suffix:semicolon
multiline_comment|/* adapter function number (PCI register) */
DECL|member|slot
r_int
id|slot
suffix:semicolon
multiline_comment|/* slot number in bus */
DECL|member|irq
r_int
r_char
id|irq
suffix:semicolon
multiline_comment|/* IRQ number */
DECL|member|reset_base
r_int
id|reset_base
suffix:semicolon
multiline_comment|/* Reset register  for I/O mapped cards */
DECL|member|io_base
r_int
id|io_base
suffix:semicolon
multiline_comment|/* I/O base for I/O mapped cards */
DECL|member|memory
r_void
op_star
id|memory
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* memory base addresses for memory mapped cards */
DECL|member|name
r_char
id|name
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* name of adapter */
DECL|member|serial
r_int
id|serial
suffix:semicolon
multiline_comment|/* serial number */
DECL|member|int_priority
r_int
r_char
id|int_priority
suffix:semicolon
multiline_comment|/* Interrupt priority */
DECL|typedef|dia_card_t
)brace
id|dia_card_t
suffix:semicolon
multiline_comment|/*&n; * protocol configuration information&n; * passed as parameter to DIA_IOCTL_CONFIG ioctl to configure card&n; */
r_typedef
r_struct
(brace
DECL|member|card_id
r_int
id|card_id
suffix:semicolon
multiline_comment|/* to identify particular card */
DECL|member|tei
r_int
r_char
id|tei
suffix:semicolon
DECL|member|nt2
r_int
r_char
id|nt2
suffix:semicolon
DECL|member|watchdog
r_int
r_char
id|watchdog
suffix:semicolon
DECL|member|permanent
r_int
r_char
id|permanent
suffix:semicolon
DECL|member|x_interface
r_int
r_char
id|x_interface
suffix:semicolon
DECL|member|stable_l2
r_int
r_char
id|stable_l2
suffix:semicolon
DECL|member|no_order_check
r_int
r_char
id|no_order_check
suffix:semicolon
DECL|member|handset_type
r_int
r_char
id|handset_type
suffix:semicolon
DECL|member|sig_flags
r_int
r_char
id|sig_flags
suffix:semicolon
DECL|member|low_channel
r_int
r_char
id|low_channel
suffix:semicolon
DECL|member|prot_version
r_int
r_char
id|prot_version
suffix:semicolon
DECL|member|crc4
r_int
r_char
id|crc4
suffix:semicolon
r_struct
(brace
DECL|member|oad
r_int
r_char
id|oad
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|osa
r_int
r_char
id|osa
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|spid
r_int
r_char
id|spid
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|terminal
)brace
id|terminal
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|dia_config_t
)brace
id|dia_config_t
suffix:semicolon
multiline_comment|/*&n; * code configuration &n; * passed as parameter to DIA_IOCTL_LOAD ioctl&n; * one of these ioctl per code file to load&n; */
r_typedef
r_struct
(brace
DECL|member|card_id
r_int
id|card_id
suffix:semicolon
multiline_comment|/* card to load */
r_enum
(brace
DECL|enumerator|DIA_CPU_CODE
id|DIA_CPU_CODE
comma
multiline_comment|/* CPU code */
DECL|enumerator|DIA_DSP_CODE
id|DIA_DSP_CODE
comma
multiline_comment|/* DSP code */
DECL|enumerator|DIA_CONT_CODE
id|DIA_CONT_CODE
comma
multiline_comment|/* continuation of code */
DECL|enumerator|DIA_TABLE_CODE
id|DIA_TABLE_CODE
comma
multiline_comment|/* code table */
DECL|enumerator|DIA_DLOAD_CNT
id|DIA_DLOAD_CNT
comma
multiline_comment|/* number of downloads*/
DECL|enumerator|DIA_FPGA_CODE
id|DIA_FPGA_CODE
DECL|member|code_type
)brace
id|code_type
suffix:semicolon
multiline_comment|/* code for CPU or DSP ? */
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* length of code */
DECL|member|code
r_int
r_char
op_star
id|code
suffix:semicolon
multiline_comment|/* pointer (in user-space) to code */
DECL|typedef|dia_load_t
)brace
id|dia_load_t
suffix:semicolon
multiline_comment|/*&n; * start configuration &n; * passed as parameter to DIA_IOCTL_START ioctl&n; */
r_typedef
r_struct
(brace
DECL|member|card_id
r_int
id|card_id
suffix:semicolon
multiline_comment|/* card to start */
DECL|typedef|dia_start_t
)brace
id|dia_start_t
suffix:semicolon
multiline_comment|/* used for retrieving memory from the card */
r_typedef
r_struct
(brace
DECL|member|card_id
id|word
id|card_id
suffix:semicolon
DECL|member|addr
id|dword
id|addr
suffix:semicolon
DECL|member|data
id|byte
id|data
(braket
l_int|16
op_star
l_int|8
)braket
suffix:semicolon
DECL|typedef|mem_block_t
)brace
id|mem_block_t
suffix:semicolon
multiline_comment|/* DIVA Server specific addresses */
DECL|macro|DIVAS_CPU_START_ADDR
mdefine_line|#define DIVAS_CPU_START_ADDR    (0x0)
DECL|macro|ORG_MAX_PROTOCOL_CODE_SIZE
mdefine_line|#define&t;ORG_MAX_PROTOCOL_CODE_SIZE&t;0x000A0000
DECL|macro|ORG_MAX_DSP_CODE_SIZE
mdefine_line|#define&t;ORG_MAX_DSP_CODE_SIZE&t;&t;(0x000F0000 - ORG_MAX_PROTOCOL_CODE_SIZE)
DECL|macro|ORG_DSP_CODE_BASE
mdefine_line|#define&t;ORG_DSP_CODE_BASE&t;&t;(0xBF7F0000 - ORG_MAX_DSP_CODE_SIZE)
DECL|macro|DIVAS_DSP_START_ADDR
mdefine_line|#define DIVAS_DSP_START_ADDR    (0xBF7A0000)
DECL|macro|DIVAS_SHARED_OFFSET
mdefine_line|#define DIVAS_SHARED_OFFSET     (0x1000)
DECL|macro|MP_DSP_CODE_BASE
mdefine_line|#define MP_DSP_CODE_BASE           0xa03a0000
DECL|macro|MQ_PROTCODE_OFFSET
mdefine_line|#define MQ_PROTCODE_OFFSET  0x100000
DECL|macro|MQ_SM_OFFSET
mdefine_line|#define MQ_SM_OFFSET&t;&t;0X0f0000
DECL|macro|V90D_MAX_PROTOCOL_CODE_SIZE
mdefine_line|#define&t;V90D_MAX_PROTOCOL_CODE_SIZE&t;0x00090000
DECL|macro|V90D_MAX_DSP_CODE_SIZE
mdefine_line|#define V90D_MAX_DSP_CODE_SIZE&t;&t;(0x000F0000 - V90D_MAX_PROTOCOL_CODE_SIZE)
DECL|macro|V90D_DSP_CODE_BASE
mdefine_line|#define&t;V90D_DSP_CODE_BASE&t;&t;(0xBF7F0000 - V90D_MAX_DSP_CODE_SIZE)
DECL|macro|MQ_ORG_MAX_PROTOCOL_CODE_SIZE
mdefine_line|#define MQ_ORG_MAX_PROTOCOL_CODE_SIZE   0x000a0000  /* max 640K Protocol-Code */
DECL|macro|MQ_ORG_MAX_DSP_CODE_SIZE
mdefine_line|#define MQ_ORG_MAX_DSP_CODE_SIZE        0x00050000  /* max 320K DSP-Code */
DECL|macro|MQ_ORG_DSP_CODE_BASE
mdefine_line|#define MQ_ORG_DSP_CODE_BASE           (MQ_MAX_DSP_DOWNLOAD_ADDR &bslash;&n;                                      - MQ_ORG_MAX_DSP_CODE_SIZE)
DECL|macro|MQ_V90D_MAX_PROTOCOL_CODE_SIZE
mdefine_line|#define MQ_V90D_MAX_PROTOCOL_CODE_SIZE  0x00090000  /* max 576K Protocol-Code */
DECL|macro|MQ_V90D_MAX_DSP_CODE_SIZE
mdefine_line|#define MQ_V90D_MAX_DSP_CODE_SIZE       0x00060000  /* max 384K DSP-Code if V.90D included */
DECL|macro|MQ_MAX_DSP_DOWNLOAD_ADDR
mdefine_line|#define&t;MQ_MAX_DSP_DOWNLOAD_ADDR        0xa03f0000
DECL|macro|MQ_V90D_DSP_CODE_BASE
mdefine_line|#define MQ_V90D_DSP_CODE_BASE          (MQ_MAX_DSP_DOWNLOAD_ADDR &bslash;&n;                                      - MQ_V90D_MAX_DSP_CODE_SIZE)
DECL|macro|ALIGNMENT_MASK_MAESTRA
mdefine_line|#define ALIGNMENT_MASK_MAESTRA        0xfffffffc
macro_line|#endif /* DIVAS_H */
eof
