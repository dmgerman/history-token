multiline_comment|/* soc.h: Definitions for Sparc SUNW,soc Fibre Channel Sbus driver.&n; *&n; * Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#ifndef __SOC_H
DECL|macro|__SOC_H
mdefine_line|#define __SOC_H
macro_line|#include &quot;fc.h&quot;
macro_line|#include &quot;fcp.h&quot;
macro_line|#include &quot;fcp_impl.h&quot;
multiline_comment|/* Hardware register offsets and constants first {{{ */
DECL|macro|CFG
mdefine_line|#define CFG&t;0x00UL&t;&t;/* Config Register */
DECL|macro|SAE
mdefine_line|#define SAE&t;0x04UL&t;&t;/* Slave Access Error Register */
DECL|macro|CMD
mdefine_line|#define CMD&t;0x08UL&t;&t;/* Command and Status Register */
DECL|macro|IMASK
mdefine_line|#define IMASK&t;0x0cUL&t;&t;/* Interrupt Mask Register */
multiline_comment|/* Config Register */
DECL|macro|SOC_CFG_EXT_RAM_BANK_MASK
mdefine_line|#define SOC_CFG_EXT_RAM_BANK_MASK&t;0x07000000
DECL|macro|SOC_CFG_EEPROM_BANK_MASK
mdefine_line|#define SOC_CFG_EEPROM_BANK_MASK&t;0x00030000
DECL|macro|SOC_CFG_BURST64_MASK
mdefine_line|#define SOC_CFG_BURST64_MASK&t;&t;0x00000700
DECL|macro|SOC_CFG_SBUS_PARITY_TEST
mdefine_line|#define SOC_CFG_SBUS_PARITY_TEST&t;0x00000020
DECL|macro|SOC_CFG_SBUS_PARITY_CHECK
mdefine_line|#define SOC_CFG_SBUS_PARITY_CHECK&t;0x00000010
DECL|macro|SOC_CFG_SBUS_ENHANCED
mdefine_line|#define SOC_CFG_SBUS_ENHANCED&t;&t;0x00000008
DECL|macro|SOC_CFG_BURST_MASK
mdefine_line|#define SOC_CFG_BURST_MASK&t;&t;0x00000007
multiline_comment|/* Bursts */
DECL|macro|SOC_CFG_BURST_4
mdefine_line|#define SOC_CFG_BURST_4&t;&t;&t;0x00000000
DECL|macro|SOC_CFG_BURST_16
mdefine_line|#define SOC_CFG_BURST_16&t;&t;0x00000004
DECL|macro|SOC_CFG_BURST_32
mdefine_line|#define SOC_CFG_BURST_32&t;&t;0x00000005
DECL|macro|SOC_CFG_BURST_64
mdefine_line|#define SOC_CFG_BURST_64&t;&t;0x00000006
multiline_comment|/* Slave Access Error Register */
DECL|macro|SOC_SAE_ALIGNMENT
mdefine_line|#define SOC_SAE_ALIGNMENT&t;&t;0x00000004
DECL|macro|SOC_SAE_UNSUPPORTED
mdefine_line|#define SOC_SAE_UNSUPPORTED&t;&t;0x00000002
DECL|macro|SOC_SAE_PARITY
mdefine_line|#define SOC_SAE_PARITY&t;&t;&t;0x00000001
multiline_comment|/* Command &amp; Status Register */
DECL|macro|SOC_CMD_RSP_QALL
mdefine_line|#define SOC_CMD_RSP_QALL&t;&t;0x000f0000
DECL|macro|SOC_CMD_RSP_Q0
mdefine_line|#define SOC_CMD_RSP_Q0&t;&t;&t;0x00010000
DECL|macro|SOC_CMD_RSP_Q1
mdefine_line|#define SOC_CMD_RSP_Q1&t;&t;&t;0x00020000
DECL|macro|SOC_CMD_RSP_Q2
mdefine_line|#define SOC_CMD_RSP_Q2&t;&t;&t;0x00040000
DECL|macro|SOC_CMD_RSP_Q3
mdefine_line|#define SOC_CMD_RSP_Q3&t;&t;&t;0x00080000
DECL|macro|SOC_CMD_REQ_QALL
mdefine_line|#define SOC_CMD_REQ_QALL&t;&t;0x00000f00
DECL|macro|SOC_CMD_REQ_Q0
mdefine_line|#define SOC_CMD_REQ_Q0&t;&t;&t;0x00000100
DECL|macro|SOC_CMD_REQ_Q1
mdefine_line|#define SOC_CMD_REQ_Q1&t;&t;&t;0x00000200
DECL|macro|SOC_CMD_REQ_Q2
mdefine_line|#define SOC_CMD_REQ_Q2&t;&t;&t;0x00000400
DECL|macro|SOC_CMD_REQ_Q3
mdefine_line|#define SOC_CMD_REQ_Q3&t;&t;&t;0x00000800
DECL|macro|SOC_CMD_SAE
mdefine_line|#define SOC_CMD_SAE&t;&t;&t;0x00000080
DECL|macro|SOC_CMD_INTR_PENDING
mdefine_line|#define SOC_CMD_INTR_PENDING&t;&t;0x00000008
DECL|macro|SOC_CMD_NON_QUEUED
mdefine_line|#define SOC_CMD_NON_QUEUED&t;&t;0x00000004
DECL|macro|SOC_CMD_IDLE
mdefine_line|#define SOC_CMD_IDLE&t;&t;&t;0x00000002
DECL|macro|SOC_CMD_SOFT_RESET
mdefine_line|#define SOC_CMD_SOFT_RESET&t;&t;0x00000001
multiline_comment|/* Interrupt Mask Register */
DECL|macro|SOC_IMASK_RSP_QALL
mdefine_line|#define SOC_IMASK_RSP_QALL&t;&t;0x000f0000
DECL|macro|SOC_IMASK_RSP_Q0
mdefine_line|#define SOC_IMASK_RSP_Q0&t;&t;0x00010000
DECL|macro|SOC_IMASK_RSP_Q1
mdefine_line|#define SOC_IMASK_RSP_Q1&t;&t;0x00020000
DECL|macro|SOC_IMASK_RSP_Q2
mdefine_line|#define SOC_IMASK_RSP_Q2&t;&t;0x00040000
DECL|macro|SOC_IMASK_RSP_Q3
mdefine_line|#define SOC_IMASK_RSP_Q3&t;&t;0x00080000
DECL|macro|SOC_IMASK_REQ_QALL
mdefine_line|#define SOC_IMASK_REQ_QALL&t;&t;0x00000f00
DECL|macro|SOC_IMASK_REQ_Q0
mdefine_line|#define SOC_IMASK_REQ_Q0&t;&t;0x00000100
DECL|macro|SOC_IMASK_REQ_Q1
mdefine_line|#define SOC_IMASK_REQ_Q1&t;&t;0x00000200
DECL|macro|SOC_IMASK_REQ_Q2
mdefine_line|#define SOC_IMASK_REQ_Q2&t;&t;0x00000400
DECL|macro|SOC_IMASK_REQ_Q3
mdefine_line|#define SOC_IMASK_REQ_Q3&t;&t;0x00000800
DECL|macro|SOC_IMASK_SAE
mdefine_line|#define SOC_IMASK_SAE&t;&t;&t;0x00000080
DECL|macro|SOC_IMASK_NON_QUEUED
mdefine_line|#define SOC_IMASK_NON_QUEUED&t;&t;0x00000004
DECL|macro|SOC_INTR
mdefine_line|#define SOC_INTR(s, cmd) &bslash;&n;&t;(((cmd &amp; SOC_CMD_RSP_QALL) | ((~cmd) &amp; SOC_CMD_REQ_QALL)) &bslash;&n;&t; &amp; s-&gt;imask)
DECL|macro|SOC_SETIMASK
mdefine_line|#define SOC_SETIMASK(s, i) &bslash;&n;do {&t;(s)-&gt;imask = (i); &bslash;&n;&t;sbus_writel((i), (s)-&gt;regs + IMASK); &bslash;&n;} while(0)
multiline_comment|/* XRAM&n; *&n; * This is a 64KB register area. It accepts only halfword access.&n; * That&squot;s why here are the following inline functions...&n; */
DECL|typedef|xram_p
r_typedef
r_int
r_int
id|xram_p
suffix:semicolon
multiline_comment|/* Get 32bit number from XRAM */
DECL|function|xram_get_32
r_static
r_inline
id|u32
id|xram_get_32
(paren
id|xram_p
id|x
)paren
(brace
r_return
(paren
(paren
id|sbus_readw
c_func
(paren
id|x
op_plus
l_int|0x00UL
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|sbus_readw
c_func
(paren
id|x
op_plus
l_int|0x02UL
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Like the above, but when we don&squot;t care about the high 16 bits */
DECL|function|xram_get_32low
r_static
r_inline
id|u32
id|xram_get_32low
(paren
id|xram_p
id|x
)paren
(brace
r_return
(paren
id|u32
)paren
id|sbus_readw
c_func
(paren
id|x
op_plus
l_int|0x02UL
)paren
suffix:semicolon
)brace
DECL|function|xram_get_16
r_static
r_inline
id|u16
id|xram_get_16
(paren
id|xram_p
id|x
)paren
(brace
r_return
id|sbus_readw
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
DECL|function|xram_get_8
r_static
r_inline
id|u8
id|xram_get_8
(paren
id|xram_p
id|x
)paren
(brace
r_if
c_cond
(paren
id|x
op_amp
(paren
id|xram_p
)paren
l_int|0x1
)paren
(brace
id|x
op_assign
id|x
op_minus
l_int|1
suffix:semicolon
r_return
(paren
id|u8
)paren
id|sbus_readw
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
(paren
id|u8
)paren
(paren
id|sbus_readw
c_func
(paren
id|x
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
)brace
DECL|function|xram_copy_from
r_static
r_inline
r_void
id|xram_copy_from
(paren
r_void
op_star
id|p
comma
id|xram_p
id|x
comma
r_int
id|len
)paren
(brace
r_for
c_loop
(paren
id|len
op_rshift_assign
l_int|2
suffix:semicolon
id|len
OG
l_int|0
suffix:semicolon
id|len
op_decrement
comma
id|x
op_add_assign
r_sizeof
(paren
id|u32
)paren
)paren
(brace
id|u32
id|val
suffix:semicolon
id|val
op_assign
(paren
(paren
id|sbus_readw
c_func
(paren
id|x
op_plus
l_int|0x00UL
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|sbus_readw
c_func
(paren
id|x
op_plus
l_int|0x02UL
)paren
)paren
)paren
suffix:semicolon
op_star
(paren
(paren
id|u32
op_star
)paren
id|p
)paren
op_increment
op_assign
id|val
suffix:semicolon
)brace
)brace
DECL|function|xram_copy_to
r_static
r_inline
r_void
id|xram_copy_to
(paren
id|xram_p
id|x
comma
r_void
op_star
id|p
comma
r_int
id|len
)paren
(brace
r_for
c_loop
(paren
id|len
op_rshift_assign
l_int|2
suffix:semicolon
id|len
OG
l_int|0
suffix:semicolon
id|len
op_decrement
comma
id|x
op_add_assign
r_sizeof
(paren
id|u32
)paren
)paren
(brace
id|u32
id|tmp
op_assign
op_star
(paren
(paren
id|u32
op_star
)paren
id|p
)paren
op_increment
suffix:semicolon
id|sbus_writew
c_func
(paren
id|tmp
op_rshift
l_int|16
comma
id|x
op_plus
l_int|0x00UL
)paren
suffix:semicolon
id|sbus_writew
c_func
(paren
id|tmp
comma
id|x
op_plus
l_int|0x02UL
)paren
suffix:semicolon
)brace
)brace
DECL|function|xram_bzero
r_static
r_inline
r_void
id|xram_bzero
(paren
id|xram_p
id|x
comma
r_int
id|len
)paren
(brace
r_for
c_loop
(paren
id|len
op_rshift_assign
l_int|1
suffix:semicolon
id|len
OG
l_int|0
suffix:semicolon
id|len
op_decrement
comma
id|x
op_add_assign
r_sizeof
(paren
id|u16
)paren
)paren
id|sbus_writew
c_func
(paren
l_int|0
comma
id|x
)paren
suffix:semicolon
)brace
multiline_comment|/* Circular Queue */
DECL|macro|SOC_CQ_REQ_OFFSET
mdefine_line|#define SOC_CQ_REQ_OFFSET&t;(0x100 * sizeof(u16))
DECL|macro|SOC_CQ_RSP_OFFSET
mdefine_line|#define SOC_CQ_RSP_OFFSET&t;(0x110 * sizeof(u16))
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
DECL|typedef|soc_hw_cq
)brace
id|soc_hw_cq
suffix:semicolon
DECL|macro|SOC_PORT_A
mdefine_line|#define SOC_PORT_A&t;0x0000&t;/* From/To Port A */
DECL|macro|SOC_PORT_B
mdefine_line|#define SOC_PORT_B&t;0x0001&t;/* From/To Port A */
DECL|macro|SOC_FC_HDR
mdefine_line|#define SOC_FC_HDR&t;0x0002  /* Contains FC Header */
DECL|macro|SOC_NORSP
mdefine_line|#define SOC_NORSP&t;0x0004  /* Don&squot;t generate response nor interrupt */
DECL|macro|SOC_NOINT
mdefine_line|#define SOC_NOINT&t;0x0008  /* Generate response but not interrupt */
DECL|macro|SOC_XFERRDY
mdefine_line|#define SOC_XFERRDY&t;0x0010  /* Generate XFERRDY */
DECL|macro|SOC_IGNOREPARAM
mdefine_line|#define SOC_IGNOREPARAM&t;0x0020&t;/* Ignore PARAM field in the FC header */
DECL|macro|SOC_COMPLETE
mdefine_line|#define SOC_COMPLETE&t;0x0040  /* Command completed */
DECL|macro|SOC_UNSOLICITED
mdefine_line|#define SOC_UNSOLICITED&t;0x0080&t;/* For request this is the packet to establish unsolicited pools, */
multiline_comment|/* for rsp this is unsolicited packet */
DECL|macro|SOC_STATUS
mdefine_line|#define SOC_STATUS&t;0x0100&t;/* State change (on/off line) */
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
DECL|typedef|soc_hdr
)brace
id|soc_hdr
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
DECL|typedef|soc_data
)brace
id|soc_data
suffix:semicolon
DECL|macro|SOC_CQTYPE_OUTBOUND
mdefine_line|#define SOC_CQTYPE_OUTBOUND&t;0x01
DECL|macro|SOC_CQTYPE_INBOUND
mdefine_line|#define SOC_CQTYPE_INBOUND&t;0x02
DECL|macro|SOC_CQTYPE_SIMPLE
mdefine_line|#define SOC_CQTYPE_SIMPLE&t;0x03
DECL|macro|SOC_CQTYPE_IO_WRITE
mdefine_line|#define SOC_CQTYPE_IO_WRITE&t;0x04
DECL|macro|SOC_CQTYPE_IO_READ
mdefine_line|#define SOC_CQTYPE_IO_READ&t;0x05
DECL|macro|SOC_CQTYPE_UNSOLICITED
mdefine_line|#define SOC_CQTYPE_UNSOLICITED&t;0x06
DECL|macro|SOC_CQTYPE_DIAG
mdefine_line|#define SOC_CQTYPE_DIAG&t;&t;0x07
DECL|macro|SOC_CQTYPE_OFFLINE
mdefine_line|#define SOC_CQTYPE_OFFLINE&t;0x08
DECL|macro|SOC_CQTYPE_RESPONSE
mdefine_line|#define SOC_CQTYPE_RESPONSE&t;0x10
DECL|macro|SOC_CQTYPE_INLINE
mdefine_line|#define SOC_CQTYPE_INLINE&t;0x20
DECL|macro|SOC_CQFLAGS_CONT
mdefine_line|#define SOC_CQFLAGS_CONT&t;0x01
DECL|macro|SOC_CQFLAGS_FULL
mdefine_line|#define SOC_CQFLAGS_FULL&t;0x02
DECL|macro|SOC_CQFLAGS_BADHDR
mdefine_line|#define SOC_CQFLAGS_BADHDR&t;0x04
DECL|macro|SOC_CQFLAGS_BADPKT
mdefine_line|#define SOC_CQFLAGS_BADPKT&t;0x08
r_typedef
r_struct
(brace
DECL|member|shdr
id|soc_hdr
id|shdr
suffix:semicolon
DECL|member|data
id|soc_data
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
DECL|typedef|soc_req
)brace
id|soc_req
suffix:semicolon
DECL|macro|SOC_OK
mdefine_line|#define SOC_OK&t;&t;&t;0
DECL|macro|SOC_P_RJT
mdefine_line|#define SOC_P_RJT&t;&t;2
DECL|macro|SOC_F_RJT
mdefine_line|#define SOC_F_RJT&t;&t;3
DECL|macro|SOC_P_BSY
mdefine_line|#define SOC_P_BSY&t;&t;4
DECL|macro|SOC_F_BSY
mdefine_line|#define SOC_F_BSY&t;&t;5
DECL|macro|SOC_ONLINE
mdefine_line|#define SOC_ONLINE&t;&t;0x10
DECL|macro|SOC_OFFLINE
mdefine_line|#define SOC_OFFLINE&t;&t;0x11
DECL|macro|SOC_TIMEOUT
mdefine_line|#define SOC_TIMEOUT&t;&t;0x12
DECL|macro|SOC_OVERRUN
mdefine_line|#define SOC_OVERRUN&t;&t;0x13
DECL|macro|SOC_UNKOWN_CQ_TYPE
mdefine_line|#define SOC_UNKOWN_CQ_TYPE&t;0x20
DECL|macro|SOC_BAD_SEG_CNT
mdefine_line|#define SOC_BAD_SEG_CNT&t;&t;0x21
DECL|macro|SOC_MAX_XCHG_EXCEEDED
mdefine_line|#define SOC_MAX_XCHG_EXCEEDED&t;0x22
DECL|macro|SOC_BAD_XID
mdefine_line|#define SOC_BAD_XID&t;&t;0x23
DECL|macro|SOC_XCHG_BUSY
mdefine_line|#define SOC_XCHG_BUSY&t;&t;0x24
DECL|macro|SOC_BAD_POOL_ID
mdefine_line|#define SOC_BAD_POOL_ID&t;&t;0x25
DECL|macro|SOC_INSUFFICIENT_CQES
mdefine_line|#define SOC_INSUFFICIENT_CQES&t;0x26
DECL|macro|SOC_ALLOC_FAIL
mdefine_line|#define SOC_ALLOC_FAIL&t;&t;0x27
DECL|macro|SOC_BAD_SID
mdefine_line|#define SOC_BAD_SID&t;&t;0x28
DECL|macro|SOC_NO_SEG_INIT
mdefine_line|#define SOC_NO_SEG_INIT&t;&t;0x29
r_typedef
r_struct
(brace
DECL|member|shdr
id|soc_hdr
id|shdr
suffix:semicolon
DECL|member|status
id|u32
id|status
suffix:semicolon
DECL|member|data
id|soc_data
id|data
suffix:semicolon
DECL|member|xxx1
id|u8
id|xxx1
(braket
l_int|12
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
DECL|typedef|soc_rsp
)brace
id|soc_rsp
suffix:semicolon
multiline_comment|/* }}} */
multiline_comment|/* Now our software structures and constants we use to drive the beast {{{ */
DECL|macro|SOC_CQ_REQ0_SIZE
mdefine_line|#define SOC_CQ_REQ0_SIZE&t;4
DECL|macro|SOC_CQ_REQ1_SIZE
mdefine_line|#define SOC_CQ_REQ1_SIZE&t;64
DECL|macro|SOC_CQ_RSP0_SIZE
mdefine_line|#define SOC_CQ_RSP0_SIZE&t;8
DECL|macro|SOC_CQ_RSP1_SIZE
mdefine_line|#define SOC_CQ_RSP1_SIZE&t;4
DECL|macro|SOC_SOLICITED_RSP_Q
mdefine_line|#define SOC_SOLICITED_RSP_Q&t;0
DECL|macro|SOC_UNSOLICITED_RSP_Q
mdefine_line|#define SOC_UNSOLICITED_RSP_Q&t;1
r_struct
id|soc
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
id|soc
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
DECL|typedef|soc_port
)brace
id|soc_port
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|hw_cq
id|soc_hw_cq
op_star
id|hw_cq
suffix:semicolon
multiline_comment|/* Related XRAM cq */
DECL|member|pool
id|soc_req
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
DECL|typedef|soc_cq
)brace
id|soc_cq
suffix:semicolon
DECL|struct|soc
r_struct
id|soc
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|port
id|soc_port
id|port
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Every SOC has one or two FC ports */
DECL|member|req
id|soc_cq
id|req
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Request CQs */
DECL|member|rsp
id|soc_cq
id|rsp
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Response CQs */
DECL|member|soc_no
r_int
id|soc_no
suffix:semicolon
DECL|member|regs
r_int
r_int
id|regs
suffix:semicolon
DECL|member|xram
id|xram_p
id|xram
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
id|soc
op_star
id|next
suffix:semicolon
DECL|member|curr_port
r_int
id|curr_port
suffix:semicolon
multiline_comment|/* Which port will have priority to fcp_queue_empty */
DECL|member|req_cpu
id|soc_req
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
macro_line|#endif /* !(__SOC_H) */
eof
