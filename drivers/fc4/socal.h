multiline_comment|/* socal.h: Definitions for Sparc SUNW,socal (SOC+) Fibre Channel Sbus driver.&n; *&n; * Copyright (C) 1998,1999 Jakub Jelinek (jj@ultra.linux.cz)&n; */
macro_line|#ifndef __SOCAL_H
DECL|macro|__SOCAL_H
mdefine_line|#define __SOCAL_H
macro_line|#include &quot;fc.h&quot;
macro_line|#include &quot;fcp.h&quot;
macro_line|#include &quot;fcp_impl.h&quot;
multiline_comment|/* Hardware register offsets and constants first {{{ */
DECL|macro|CFG
mdefine_line|#define CFG&t;0x00UL
DECL|macro|SAE
mdefine_line|#define SAE&t;0x04UL
DECL|macro|CMD
mdefine_line|#define CMD&t;0x08UL
DECL|macro|IMASK
mdefine_line|#define IMASK&t;0x0cUL
DECL|macro|REQP
mdefine_line|#define REQP&t;0x10UL
DECL|macro|RESP
mdefine_line|#define RESP&t;0x14UL
multiline_comment|/* Config Register */
DECL|macro|SOCAL_CFG_EXT_RAM_BANK_MASK
mdefine_line|#define SOCAL_CFG_EXT_RAM_BANK_MASK&t;0x07000000
DECL|macro|SOCAL_CFG_EEPROM_BANK_MASK
mdefine_line|#define SOCAL_CFG_EEPROM_BANK_MASK&t;0x00030000
DECL|macro|SOCAL_CFG_BURST64_MASK
mdefine_line|#define SOCAL_CFG_BURST64_MASK&t;&t;0x00000700
DECL|macro|SOCAL_CFG_SBUS_PARITY_TEST
mdefine_line|#define SOCAL_CFG_SBUS_PARITY_TEST&t;0x00000020
DECL|macro|SOCAL_CFG_SBUS_PARITY_CHECK
mdefine_line|#define SOCAL_CFG_SBUS_PARITY_CHECK&t;0x00000010
DECL|macro|SOCAL_CFG_SBUS_ENHANCED
mdefine_line|#define SOCAL_CFG_SBUS_ENHANCED&t;&t;0x00000008
DECL|macro|SOCAL_CFG_BURST_MASK
mdefine_line|#define SOCAL_CFG_BURST_MASK&t;&t;0x00000007
multiline_comment|/* Bursts */
DECL|macro|SOCAL_CFG_BURST_4
mdefine_line|#define SOCAL_CFG_BURST_4&t;&t;0x00000000
DECL|macro|SOCAL_CFG_BURST_8
mdefine_line|#define SOCAL_CFG_BURST_8&t;&t;0x00000003
DECL|macro|SOCAL_CFG_BURST_16
mdefine_line|#define SOCAL_CFG_BURST_16&t;&t;0x00000004
DECL|macro|SOCAL_CFG_BURST_32
mdefine_line|#define SOCAL_CFG_BURST_32&t;&t;0x00000005
DECL|macro|SOCAL_CFG_BURST_64
mdefine_line|#define SOCAL_CFG_BURST_64&t;&t;0x00000006
DECL|macro|SOCAL_CFG_BURST_128
mdefine_line|#define SOCAL_CFG_BURST_128&t;&t;0x00000007
multiline_comment|/* Slave Access Error Register */
DECL|macro|SOCAL_SAE_ALIGNMENT
mdefine_line|#define SOCAL_SAE_ALIGNMENT&t;&t;0x00000004
DECL|macro|SOCAL_SAE_UNSUPPORTED
mdefine_line|#define SOCAL_SAE_UNSUPPORTED&t;&t;0x00000002
DECL|macro|SOCAL_SAE_PARITY
mdefine_line|#define SOCAL_SAE_PARITY&t;&t;0x00000001
multiline_comment|/* Command &amp; Status Register */
DECL|macro|SOCAL_CMD_RSP_QALL
mdefine_line|#define SOCAL_CMD_RSP_QALL&t;&t;0x000f0000
DECL|macro|SOCAL_CMD_RSP_Q0
mdefine_line|#define SOCAL_CMD_RSP_Q0&t;&t;0x00010000
DECL|macro|SOCAL_CMD_RSP_Q1
mdefine_line|#define SOCAL_CMD_RSP_Q1&t;&t;0x00020000
DECL|macro|SOCAL_CMD_RSP_Q2
mdefine_line|#define SOCAL_CMD_RSP_Q2&t;&t;0x00040000
DECL|macro|SOCAL_CMD_RSP_Q3
mdefine_line|#define SOCAL_CMD_RSP_Q3&t;&t;0x00080000
DECL|macro|SOCAL_CMD_REQ_QALL
mdefine_line|#define SOCAL_CMD_REQ_QALL&t;&t;0x00000f00
DECL|macro|SOCAL_CMD_REQ_Q0
mdefine_line|#define SOCAL_CMD_REQ_Q0&t;&t;0x00000100
DECL|macro|SOCAL_CMD_REQ_Q1
mdefine_line|#define SOCAL_CMD_REQ_Q1&t;&t;0x00000200
DECL|macro|SOCAL_CMD_REQ_Q2
mdefine_line|#define SOCAL_CMD_REQ_Q2&t;&t;0x00000400
DECL|macro|SOCAL_CMD_REQ_Q3
mdefine_line|#define SOCAL_CMD_REQ_Q3&t;&t;0x00000800
DECL|macro|SOCAL_CMD_SAE
mdefine_line|#define SOCAL_CMD_SAE&t;&t;&t;0x00000080
DECL|macro|SOCAL_CMD_INTR_PENDING
mdefine_line|#define SOCAL_CMD_INTR_PENDING&t;&t;0x00000008
DECL|macro|SOCAL_CMD_NON_QUEUED
mdefine_line|#define SOCAL_CMD_NON_QUEUED&t;&t;0x00000004
DECL|macro|SOCAL_CMD_IDLE
mdefine_line|#define SOCAL_CMD_IDLE&t;&t;&t;0x00000002
DECL|macro|SOCAL_CMD_SOFT_RESET
mdefine_line|#define SOCAL_CMD_SOFT_RESET&t;&t;0x00000001
multiline_comment|/* Interrupt Mask Register */
DECL|macro|SOCAL_IMASK_RSP_QALL
mdefine_line|#define SOCAL_IMASK_RSP_QALL&t;&t;0x000f0000
DECL|macro|SOCAL_IMASK_RSP_Q0
mdefine_line|#define SOCAL_IMASK_RSP_Q0&t;&t;0x00010000
DECL|macro|SOCAL_IMASK_RSP_Q1
mdefine_line|#define SOCAL_IMASK_RSP_Q1&t;&t;0x00020000
DECL|macro|SOCAL_IMASK_RSP_Q2
mdefine_line|#define SOCAL_IMASK_RSP_Q2&t;&t;0x00040000
DECL|macro|SOCAL_IMASK_RSP_Q3
mdefine_line|#define SOCAL_IMASK_RSP_Q3&t;&t;0x00080000
DECL|macro|SOCAL_IMASK_REQ_QALL
mdefine_line|#define SOCAL_IMASK_REQ_QALL&t;&t;0x00000f00
DECL|macro|SOCAL_IMASK_REQ_Q0
mdefine_line|#define SOCAL_IMASK_REQ_Q0&t;&t;0x00000100
DECL|macro|SOCAL_IMASK_REQ_Q1
mdefine_line|#define SOCAL_IMASK_REQ_Q1&t;&t;0x00000200
DECL|macro|SOCAL_IMASK_REQ_Q2
mdefine_line|#define SOCAL_IMASK_REQ_Q2&t;&t;0x00000400
DECL|macro|SOCAL_IMASK_REQ_Q3
mdefine_line|#define SOCAL_IMASK_REQ_Q3&t;&t;0x00000800
DECL|macro|SOCAL_IMASK_SAE
mdefine_line|#define SOCAL_IMASK_SAE&t;&t;&t;0x00000080
DECL|macro|SOCAL_IMASK_NON_QUEUED
mdefine_line|#define SOCAL_IMASK_NON_QUEUED&t;&t;0x00000004
DECL|macro|SOCAL_INTR
mdefine_line|#define SOCAL_INTR(s, cmd) &bslash;&n;&t;(((cmd &amp; SOCAL_CMD_RSP_QALL) | ((~cmd) &amp; SOCAL_CMD_REQ_QALL)) &bslash;&n;&t; &amp; s-&gt;imask)
DECL|macro|SOCAL_SETIMASK
mdefine_line|#define SOCAL_SETIMASK(s, i) &bslash;&n;do {&t;(s)-&gt;imask = (i); &bslash;&n;&t;sbus_writel((i), (s)-&gt;regs + IMASK); &bslash;&n;} while (0)
DECL|macro|SOCAL_MAX_EXCHANGES
mdefine_line|#define SOCAL_MAX_EXCHANGES&t;&t;1024
multiline_comment|/* XRAM&n; *&n; * This is a 64KB register area.&n; * From the documentation, it seems like it is finally able to cope&n; * at least with 1,2,4 byte accesses for read and 2,4 byte accesses for write.&n; */
multiline_comment|/* Circular Queue */
DECL|macro|SOCAL_CQ_REQ_OFFSET
mdefine_line|#define SOCAL_CQ_REQ_OFFSET&t;0x200
DECL|macro|SOCAL_CQ_RSP_OFFSET
mdefine_line|#define SOCAL_CQ_RSP_OFFSET&t;0x220
r_typedef
r_struct
(brace
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|in
id|u8
id|in
suffix:semicolon
DECL|member|out
id|u8
id|out
suffix:semicolon
DECL|member|last
id|u8
id|last
suffix:semicolon
DECL|member|seqno
id|u8
id|seqno
suffix:semicolon
DECL|typedef|socal_hw_cq
)brace
id|socal_hw_cq
suffix:semicolon
DECL|macro|SOCAL_PORT_A
mdefine_line|#define SOCAL_PORT_A&t;0x0000&t;/* From/To Port A */
DECL|macro|SOCAL_PORT_B
mdefine_line|#define SOCAL_PORT_B&t;0x0001&t;/* From/To Port A */
DECL|macro|SOCAL_FC_HDR
mdefine_line|#define SOCAL_FC_HDR&t;0x0002  /* Contains FC Header */
DECL|macro|SOCAL_NORSP
mdefine_line|#define SOCAL_NORSP&t;0x0004  /* Don&squot;t generate response nor interrupt */
DECL|macro|SOCAL_NOINT
mdefine_line|#define SOCAL_NOINT&t;0x0008  /* Generate response but not interrupt */
DECL|macro|SOCAL_XFERRDY
mdefine_line|#define SOCAL_XFERRDY&t;0x0010  /* Generate XFERRDY */
DECL|macro|SOCAL_IGNOREPARAM
mdefine_line|#define SOCAL_IGNOREPARAM 0x0020 /* Ignore PARAM field in the FC header */
DECL|macro|SOCAL_COMPLETE
mdefine_line|#define SOCAL_COMPLETE&t;0x0040  /* Command completed */
DECL|macro|SOCAL_UNSOLICITED
mdefine_line|#define SOCAL_UNSOLICITED 0x0080 /* For request this is the packet to establish unsolicited pools, */
multiline_comment|/* for rsp this is unsolicited packet */
DECL|macro|SOCAL_STATUS
mdefine_line|#define SOCAL_STATUS&t;0x0100&t;/* State change (on/off line) */
DECL|macro|SOCAL_RSP_HDR
mdefine_line|#define SOCAL_RSP_HDR&t;0x0200&t;/* Return frame header in any case */
r_typedef
r_struct
(brace
DECL|member|token
id|u32
id|token
suffix:semicolon
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|member|class
id|u8
r_class
suffix:semicolon
DECL|member|segcnt
id|u8
id|segcnt
suffix:semicolon
DECL|member|bytecnt
id|u32
id|bytecnt
suffix:semicolon
DECL|typedef|socal_hdr
)brace
id|socal_hdr
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|base
id|u32
id|base
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|typedef|socal_data
)brace
id|socal_data
suffix:semicolon
DECL|macro|SOCAL_CQTYPE_NOP
mdefine_line|#define SOCAL_CQTYPE_NOP&t;0x00
DECL|macro|SOCAL_CQTYPE_OUTBOUND
mdefine_line|#define SOCAL_CQTYPE_OUTBOUND&t;0x01
DECL|macro|SOCAL_CQTYPE_INBOUND
mdefine_line|#define SOCAL_CQTYPE_INBOUND&t;0x02
DECL|macro|SOCAL_CQTYPE_SIMPLE
mdefine_line|#define SOCAL_CQTYPE_SIMPLE&t;0x03
DECL|macro|SOCAL_CQTYPE_IO_WRITE
mdefine_line|#define SOCAL_CQTYPE_IO_WRITE&t;0x04
DECL|macro|SOCAL_CQTYPE_IO_READ
mdefine_line|#define SOCAL_CQTYPE_IO_READ&t;0x05
DECL|macro|SOCAL_CQTYPE_UNSOLICITED
mdefine_line|#define SOCAL_CQTYPE_UNSOLICITED 0x06
DECL|macro|SOCAL_CQTYPE_BYPASS_DEV
mdefine_line|#define SOCAL_CQTYPE_BYPASS_DEV&t;0x06
DECL|macro|SOCAL_CQTYPE_DIAG
mdefine_line|#define SOCAL_CQTYPE_DIAG&t;0x07
DECL|macro|SOCAL_CQTYPE_OFFLINE
mdefine_line|#define SOCAL_CQTYPE_OFFLINE&t;0x08
DECL|macro|SOCAL_CQTYPE_ADD_POOL
mdefine_line|#define SOCAL_CQTYPE_ADD_POOL&t;0x09
DECL|macro|SOCAL_CQTYPE_DELETE_POOL
mdefine_line|#define SOCAL_CQTYPE_DELETE_POOL 0x0a
DECL|macro|SOCAL_CQTYPE_ADD_BUFFER
mdefine_line|#define SOCAL_CQTYPE_ADD_BUFFER&t;0x0b
DECL|macro|SOCAL_CQTYPE_ADD_POOL_BUFFER
mdefine_line|#define SOCAL_CQTYPE_ADD_POOL_BUFFER 0x0c
DECL|macro|SOCAL_CQTYPE_REQUEST_ABORT
mdefine_line|#define SOCAL_CQTYPE_REQUEST_ABORT 0x0d
DECL|macro|SOCAL_CQTYPE_REQUEST_LIP
mdefine_line|#define SOCAL_CQTYPE_REQUEST_LIP 0x0e
DECL|macro|SOCAL_CQTYPE_REPORT_MAP
mdefine_line|#define SOCAL_CQTYPE_REPORT_MAP&t;0x0f
DECL|macro|SOCAL_CQTYPE_RESPONSE
mdefine_line|#define SOCAL_CQTYPE_RESPONSE&t;0x10
DECL|macro|SOCAL_CQTYPE_INLINE
mdefine_line|#define SOCAL_CQTYPE_INLINE&t;0x20
DECL|macro|SOCAL_CQFLAGS_CONT
mdefine_line|#define SOCAL_CQFLAGS_CONT&t;0x01
DECL|macro|SOCAL_CQFLAGS_FULL
mdefine_line|#define SOCAL_CQFLAGS_FULL&t;0x02
DECL|macro|SOCAL_CQFLAGS_BADHDR
mdefine_line|#define SOCAL_CQFLAGS_BADHDR&t;0x04
DECL|macro|SOCAL_CQFLAGS_BADPKT
mdefine_line|#define SOCAL_CQFLAGS_BADPKT&t;0x08
r_typedef
r_struct
(brace
DECL|member|shdr
id|socal_hdr
id|shdr
suffix:semicolon
DECL|member|data
id|socal_data
id|data
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|fchdr
id|fc_hdr
id|fchdr
suffix:semicolon
DECL|member|count
id|u8
id|count
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|seqno
id|u8
id|seqno
suffix:semicolon
DECL|typedef|socal_req
)brace
id|socal_req
suffix:semicolon
DECL|macro|SOCAL_OK
mdefine_line|#define SOCAL_OK&t;&t;0
DECL|macro|SOCAL_P_RJT
mdefine_line|#define SOCAL_P_RJT&t;&t;2
DECL|macro|SOCAL_F_RJT
mdefine_line|#define SOCAL_F_RJT&t;&t;3
DECL|macro|SOCAL_P_BSY
mdefine_line|#define SOCAL_P_BSY&t;&t;4
DECL|macro|SOCAL_F_BSY
mdefine_line|#define SOCAL_F_BSY&t;&t;5
DECL|macro|SOCAL_ONLINE
mdefine_line|#define SOCAL_ONLINE&t;&t;0x10
DECL|macro|SOCAL_OFFLINE
mdefine_line|#define SOCAL_OFFLINE&t;&t;0x11
DECL|macro|SOCAL_TIMEOUT
mdefine_line|#define SOCAL_TIMEOUT&t;&t;0x12
DECL|macro|SOCAL_OVERRUN
mdefine_line|#define SOCAL_OVERRUN&t;&t;0x13
DECL|macro|SOCAL_ONLINE_LOOP
mdefine_line|#define SOCAL_ONLINE_LOOP&t;0x14
DECL|macro|SOCAL_OLD_PORT
mdefine_line|#define SOCAL_OLD_PORT&t;&t;0x15
DECL|macro|SOCAL_AL_PORT
mdefine_line|#define SOCAL_AL_PORT&t;&t;0x16
DECL|macro|SOCAL_UNKOWN_CQ_TYPE
mdefine_line|#define SOCAL_UNKOWN_CQ_TYPE&t;0x20
DECL|macro|SOCAL_BAD_SEG_CNT
mdefine_line|#define SOCAL_BAD_SEG_CNT&t;0x21
DECL|macro|SOCAL_MAX_XCHG_EXCEEDED
mdefine_line|#define SOCAL_MAX_XCHG_EXCEEDED&t;0x22
DECL|macro|SOCAL_BAD_XID
mdefine_line|#define SOCAL_BAD_XID&t;&t;0x23
DECL|macro|SOCAL_XCHG_BUSY
mdefine_line|#define SOCAL_XCHG_BUSY&t;&t;0x24
DECL|macro|SOCAL_BAD_POOL_ID
mdefine_line|#define SOCAL_BAD_POOL_ID&t;0x25
DECL|macro|SOCAL_INSUFFICIENT_CQES
mdefine_line|#define SOCAL_INSUFFICIENT_CQES&t;0x26
DECL|macro|SOCAL_ALLOC_FAIL
mdefine_line|#define SOCAL_ALLOC_FAIL&t;0x27
DECL|macro|SOCAL_BAD_SID
mdefine_line|#define SOCAL_BAD_SID&t;&t;0x28
DECL|macro|SOCAL_NO_SEG_INIT
mdefine_line|#define SOCAL_NO_SEG_INIT&t;0x29
DECL|macro|SOCAL_BAD_DID
mdefine_line|#define SOCAL_BAD_DID&t;&t;0x2a
DECL|macro|SOCAL_ABORTED
mdefine_line|#define SOCAL_ABORTED&t;&t;0x30
DECL|macro|SOCAL_ABORT_FAILED
mdefine_line|#define SOCAL_ABORT_FAILED&t;0x31
r_typedef
r_struct
(brace
DECL|member|shdr
id|socal_hdr
id|shdr
suffix:semicolon
DECL|member|status
id|u32
id|status
suffix:semicolon
DECL|member|data
id|socal_data
id|data
suffix:semicolon
DECL|member|xxx1
id|u8
id|xxx1
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|ncmds
id|u16
id|ncmds
suffix:semicolon
DECL|member|fchdr
id|fc_hdr
id|fchdr
suffix:semicolon
DECL|member|count
id|u8
id|count
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|seqno
id|u8
id|seqno
suffix:semicolon
DECL|typedef|socal_rsp
)brace
id|socal_rsp
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|shdr
id|socal_hdr
id|shdr
suffix:semicolon
DECL|member|xxx1
id|u8
id|xxx1
(braket
l_int|48
)braket
suffix:semicolon
DECL|member|count
id|u8
id|count
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|seqno
id|u8
id|seqno
suffix:semicolon
DECL|typedef|socal_cmdonly
)brace
id|socal_cmdonly
suffix:semicolon
DECL|macro|SOCAL_DIAG_NOP
mdefine_line|#define SOCAL_DIAG_NOP&t;&t;0x00
DECL|macro|SOCAL_DIAG_INT_LOOP
mdefine_line|#define SOCAL_DIAG_INT_LOOP&t;0x01
DECL|macro|SOCAL_DIAG_EXT_LOOP
mdefine_line|#define SOCAL_DIAG_EXT_LOOP&t;0x02
DECL|macro|SOCAL_DIAG_REM_LOOP
mdefine_line|#define SOCAL_DIAG_REM_LOOP&t;0x03
DECL|macro|SOCAL_DIAG_XRAM_TEST
mdefine_line|#define SOCAL_DIAG_XRAM_TEST&t;0x04
DECL|macro|SOCAL_DIAG_SOC_TEST
mdefine_line|#define SOCAL_DIAG_SOC_TEST&t;0x05
DECL|macro|SOCAL_DIAG_HCB_TEST
mdefine_line|#define SOCAL_DIAG_HCB_TEST&t;0x06
DECL|macro|SOCAL_DIAG_SOCLB_TEST
mdefine_line|#define SOCAL_DIAG_SOCLB_TEST&t;0x07
DECL|macro|SOCAL_DIAG_SRDSLB_TEST
mdefine_line|#define SOCAL_DIAG_SRDSLB_TEST&t;0x08
DECL|macro|SOCAL_DIAG_EXTOE_TEST
mdefine_line|#define SOCAL_DIAG_EXTOE_TEST&t;0x09
r_typedef
r_struct
(brace
DECL|member|shdr
id|socal_hdr
id|shdr
suffix:semicolon
DECL|member|cmd
id|u32
id|cmd
suffix:semicolon
DECL|member|xxx1
id|u8
id|xxx1
(braket
l_int|44
)braket
suffix:semicolon
DECL|member|count
id|u8
id|count
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|seqno
id|u8
id|seqno
suffix:semicolon
DECL|typedef|socal_diag_req
)brace
id|socal_diag_req
suffix:semicolon
DECL|macro|SOCAL_POOL_MASK_RCTL
mdefine_line|#define SOCAL_POOL_MASK_RCTL&t;0x800000
DECL|macro|SOCAL_POOL_MASK_DID
mdefine_line|#define SOCAL_POOL_MASK_DID&t;0x700000
DECL|macro|SOCAL_POOL_MASK_SID
mdefine_line|#define SOCAL_POOL_MASK_SID&t;0x070000
DECL|macro|SOCAL_POOL_MASK_TYPE
mdefine_line|#define SOCAL_POOL_MASK_TYPE&t;0x008000
DECL|macro|SOCAL_POOL_MASK_F_CTL
mdefine_line|#define SOCAL_POOL_MASK_F_CTL&t;0x007000
DECL|macro|SOCAL_POOL_MASK_SEQ_ID
mdefine_line|#define SOCAL_POOL_MASK_SEQ_ID&t;0x000800
DECL|macro|SOCAL_POOL_MASK_D_CTL
mdefine_line|#define SOCAL_POOL_MASK_D_CTL&t;0x000400
DECL|macro|SOCAL_POOL_MASK_SEQ_CNT
mdefine_line|#define SOCAL_POOL_MASK_SEQ_CNT&t;0x000300
DECL|macro|SOCAL_POOL_MASK_OX_ID
mdefine_line|#define SOCAL_POOL_MASK_OX_ID&t;0x0000f0
DECL|macro|SOCAL_POOL_MASK_PARAM
mdefine_line|#define SOCAL_POOL_MASK_PARAM&t;0x00000f
r_typedef
r_struct
(brace
DECL|member|shdr
id|socal_hdr
id|shdr
suffix:semicolon
DECL|member|pool_id
id|u32
id|pool_id
suffix:semicolon
DECL|member|header_mask
id|u32
id|header_mask
suffix:semicolon
DECL|member|buf_size
id|u32
id|buf_size
suffix:semicolon
DECL|member|entries
id|u32
id|entries
suffix:semicolon
DECL|member|xxx1
id|u8
id|xxx1
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|fchdr
id|fc_hdr
id|fchdr
suffix:semicolon
DECL|member|count
id|u8
id|count
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|seqno
id|u8
id|seqno
suffix:semicolon
DECL|typedef|socal_pool_req
)brace
id|socal_pool_req
suffix:semicolon
multiline_comment|/* }}} */
multiline_comment|/* Now our software structures and constants we use to drive the beast {{{ */
DECL|macro|SOCAL_CQ_REQ0_SIZE
mdefine_line|#define SOCAL_CQ_REQ0_SIZE&t;4
DECL|macro|SOCAL_CQ_REQ1_SIZE
mdefine_line|#define SOCAL_CQ_REQ1_SIZE&t;256
DECL|macro|SOCAL_CQ_RSP0_SIZE
mdefine_line|#define SOCAL_CQ_RSP0_SIZE&t;8
DECL|macro|SOCAL_CQ_RSP1_SIZE
mdefine_line|#define SOCAL_CQ_RSP1_SIZE&t;4
DECL|macro|SOCAL_CQ_RSP2_SIZE
mdefine_line|#define SOCAL_CQ_RSP2_SIZE&t;4
DECL|macro|SOCAL_SOLICITED_RSP_Q
mdefine_line|#define SOCAL_SOLICITED_RSP_Q&t;0
DECL|macro|SOCAL_SOLICITED_BAD_RSP_Q
mdefine_line|#define SOCAL_SOLICITED_BAD_RSP_Q 1
DECL|macro|SOCAL_UNSOLICITED_RSP_Q
mdefine_line|#define SOCAL_UNSOLICITED_RSP_Q&t;2
r_struct
id|socal
suffix:semicolon
r_typedef
r_struct
(brace
multiline_comment|/* This must come first */
DECL|member|fc
id|fc_channel
id|fc
suffix:semicolon
DECL|member|s
r_struct
id|socal
op_star
id|s
suffix:semicolon
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|member|mask
id|u16
id|mask
suffix:semicolon
DECL|typedef|socal_port
)brace
id|socal_port
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|hw_cq
id|socal_hw_cq
op_star
id|hw_cq
suffix:semicolon
multiline_comment|/* Related XRAM cq */
DECL|member|pool
id|socal_req
op_star
id|pool
suffix:semicolon
DECL|member|in
id|u8
id|in
suffix:semicolon
DECL|member|out
id|u8
id|out
suffix:semicolon
DECL|member|last
id|u8
id|last
suffix:semicolon
DECL|member|seqno
id|u8
id|seqno
suffix:semicolon
DECL|typedef|socal_cq
)brace
id|socal_cq
suffix:semicolon
DECL|struct|socal
r_struct
id|socal
(brace
DECL|member|port
id|socal_port
id|port
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Every SOCAL has one or two FC ports */
DECL|member|req
id|socal_cq
id|req
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Request CQs */
DECL|member|rsp
id|socal_cq
id|rsp
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Response CQs */
DECL|member|socal_no
r_int
id|socal_no
suffix:semicolon
DECL|member|regs
r_int
r_int
id|regs
suffix:semicolon
DECL|member|xram
r_int
r_int
id|xram
suffix:semicolon
DECL|member|eeprom
r_int
r_int
id|eeprom
suffix:semicolon
DECL|member|wwn
id|fc_wwn
id|wwn
suffix:semicolon
DECL|member|imask
id|u32
id|imask
suffix:semicolon
multiline_comment|/* Our copy of regs-&gt;imask */
DECL|member|cfg
id|u32
id|cfg
suffix:semicolon
multiline_comment|/* Our copy of regs-&gt;cfg */
DECL|member|serv_params
r_char
id|serv_params
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|next
r_struct
id|socal
op_star
id|next
suffix:semicolon
DECL|member|curr_port
r_int
id|curr_port
suffix:semicolon
multiline_comment|/* Which port will have priority to fcp_queue_empty */
DECL|member|req_cpu
id|socal_req
op_star
id|req_cpu
suffix:semicolon
DECL|member|req_dvma
id|u32
id|req_dvma
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* }}} */
macro_line|#endif /* !(__SOCAL_H) */
eof
