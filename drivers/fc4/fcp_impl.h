multiline_comment|/* fcp_impl.h: Generic SCSI on top of FC4 - our interface defines.&n; *&n; * Copyright (C) 1997-1999 Jakub Jelinek (jj@ultra.linux.cz)&n; * Copyright (C) 1998 Jirka Hanika (geo@ff.cuni.cz)&n; */
macro_line|#ifndef _FCP_SCSI_H
DECL|macro|_FCP_SCSI_H
mdefine_line|#define _FCP_SCSI_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;../scsi/scsi.h&quot;
macro_line|#include &quot;fc.h&quot;
macro_line|#include &quot;fcp.h&quot;
macro_line|#include &quot;fc-al.h&quot;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef __sparc__
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#endif
multiline_comment|/* 0 or 1 */
DECL|macro|FCP_SCSI_USE_NEW_EH_CODE
mdefine_line|#define&t;FCP_SCSI_USE_NEW_EH_CODE&t;0
DECL|macro|FC_CLASS_OUTBOUND
mdefine_line|#define FC_CLASS_OUTBOUND&t;0x01
DECL|macro|FC_CLASS_INBOUND
mdefine_line|#define FC_CLASS_INBOUND&t;0x02
DECL|macro|FC_CLASS_SIMPLE
mdefine_line|#define FC_CLASS_SIMPLE&t;&t;0x03
DECL|macro|FC_CLASS_IO_WRITE
mdefine_line|#define FC_CLASS_IO_WRITE&t;0x04
DECL|macro|FC_CLASS_IO_READ
mdefine_line|#define FC_CLASS_IO_READ&t;0x05
DECL|macro|FC_CLASS_UNSOLICITED
mdefine_line|#define FC_CLASS_UNSOLICITED&t;0x06
DECL|macro|FC_CLASS_OFFLINE
mdefine_line|#define FC_CLASS_OFFLINE&t;0x08
DECL|macro|PROTO_OFFLINE
mdefine_line|#define PROTO_OFFLINE&t;&t;0x02
DECL|macro|PROTO_REPORT_AL_MAP
mdefine_line|#define PROTO_REPORT_AL_MAP&t;0x03
DECL|macro|PROTO_FORCE_LIP
mdefine_line|#define PROTO_FORCE_LIP&t;&t;0x06
r_struct
id|_fc_channel
suffix:semicolon
DECL|struct|fcp_cmnd
r_typedef
r_struct
id|fcp_cmnd
(brace
DECL|member|next
r_struct
id|fcp_cmnd
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|fcp_cmnd
op_star
id|prev
suffix:semicolon
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
DECL|member|proto
r_int
r_int
id|proto
suffix:semicolon
DECL|member|token
r_int
r_int
id|token
suffix:semicolon
DECL|member|did
r_int
r_int
id|did
suffix:semicolon
multiline_comment|/* FCP SCSI stuff */
DECL|member|data
id|dma_addr_t
id|data
suffix:semicolon
multiline_comment|/* From now on this cannot be touched for proto == TYPE_SCSI_FCP */
DECL|member|fch
id|fc_hdr
id|fch
suffix:semicolon
DECL|member|cmd
id|dma_addr_t
id|cmd
suffix:semicolon
DECL|member|rsp
id|dma_addr_t
id|rsp
suffix:semicolon
DECL|member|cmdlen
r_int
id|cmdlen
suffix:semicolon
DECL|member|rsplen
r_int
id|rsplen
suffix:semicolon
DECL|member|class
r_int
r_class
suffix:semicolon
DECL|member|datalen
r_int
id|datalen
suffix:semicolon
multiline_comment|/* This is just used as a verification during login */
DECL|member|fc
r_struct
id|_fc_channel
op_star
id|fc
suffix:semicolon
DECL|member|ls
r_void
op_star
id|ls
suffix:semicolon
DECL|typedef|fcp_cmnd
)brace
id|fcp_cmnd
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|list
r_int
r_char
id|list
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|fcp_posmap
)brace
id|fcp_posmap
suffix:semicolon
DECL|struct|_fc_channel
r_typedef
r_struct
id|_fc_channel
(brace
DECL|member|next
r_struct
id|_fc_channel
op_star
id|next
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|sid
r_int
id|sid
suffix:semicolon
DECL|member|did
r_int
id|did
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|fcp_register
r_void
(paren
op_star
id|fcp_register
)paren
(paren
r_struct
id|_fc_channel
op_star
comma
id|u8
comma
r_int
)paren
suffix:semicolon
DECL|member|reset
r_void
(paren
op_star
id|reset
)paren
(paren
r_struct
id|_fc_channel
op_star
)paren
suffix:semicolon
DECL|member|hw_enque
r_int
(paren
op_star
id|hw_enque
)paren
(paren
r_struct
id|_fc_channel
op_star
comma
id|fcp_cmnd
op_star
)paren
suffix:semicolon
DECL|member|wwn_node
id|fc_wwn
id|wwn_node
suffix:semicolon
DECL|member|wwn_nport
id|fc_wwn
id|wwn_nport
suffix:semicolon
DECL|member|wwn_dest
id|fc_wwn
id|wwn_dest
suffix:semicolon
DECL|member|common_svc
id|common_svc_parm
op_star
id|common_svc
suffix:semicolon
DECL|member|class_svcs
id|svc_parm
op_star
id|class_svcs
suffix:semicolon
macro_line|#ifdef __sparc__&t;
DECL|member|dev
r_struct
id|sbus_dev
op_star
id|dev
suffix:semicolon
macro_line|#else
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
macro_line|#endif
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
multiline_comment|/* FCP SCSI stuff */
DECL|member|can_queue
r_int
id|can_queue
suffix:semicolon
DECL|member|abort_count
r_int
id|abort_count
suffix:semicolon
DECL|member|rsp_size
r_int
id|rsp_size
suffix:semicolon
DECL|member|scsi_cmd_pool
id|fcp_cmd
op_star
id|scsi_cmd_pool
suffix:semicolon
DECL|member|scsi_rsp_pool
r_char
op_star
id|scsi_rsp_pool
suffix:semicolon
DECL|member|dma_scsi_cmd
DECL|member|dma_scsi_rsp
id|dma_addr_t
id|dma_scsi_cmd
comma
id|dma_scsi_rsp
suffix:semicolon
DECL|member|scsi_bitmap
r_int
op_star
id|scsi_bitmap
suffix:semicolon
DECL|member|scsi_bitmap_end
r_int
id|scsi_bitmap_end
suffix:semicolon
DECL|member|scsi_free
r_int
id|scsi_free
suffix:semicolon
DECL|member|encode_addr
r_int
(paren
op_star
id|encode_addr
)paren
(paren
id|Scsi_Cmnd
op_star
comma
id|u16
op_star
comma
r_struct
id|_fc_channel
op_star
comma
id|fcp_cmnd
op_star
)paren
suffix:semicolon
DECL|member|scsi_que
id|fcp_cmnd
op_star
id|scsi_que
suffix:semicolon
DECL|member|scsi_name
r_char
id|scsi_name
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|cmd_slots
id|fcp_cmnd
op_star
op_star
id|cmd_slots
suffix:semicolon
DECL|member|channels
r_int
id|channels
suffix:semicolon
DECL|member|targets
r_int
id|targets
suffix:semicolon
DECL|member|ages
r_int
op_star
id|ages
suffix:semicolon
DECL|member|rst_pkt
id|Scsi_Cmnd
op_star
id|rst_pkt
suffix:semicolon
DECL|member|posmap
id|fcp_posmap
op_star
id|posmap
suffix:semicolon
multiline_comment|/* LOGIN stuff */
DECL|member|login
id|fcp_cmnd
op_star
id|login
suffix:semicolon
DECL|member|ls
r_void
op_star
id|ls
suffix:semicolon
DECL|typedef|fc_channel
)brace
id|fc_channel
suffix:semicolon
r_extern
id|fc_channel
op_star
id|fc_channels
suffix:semicolon
DECL|macro|FC_STATE_UNINITED
mdefine_line|#define FC_STATE_UNINITED&t;0
DECL|macro|FC_STATE_ONLINE
mdefine_line|#define FC_STATE_ONLINE&t;&t;1
DECL|macro|FC_STATE_OFFLINE
mdefine_line|#define FC_STATE_OFFLINE&t;2
DECL|macro|FC_STATE_RESETING
mdefine_line|#define FC_STATE_RESETING&t;3
DECL|macro|FC_STATE_FPORT_OK
mdefine_line|#define FC_STATE_FPORT_OK&t;4
DECL|macro|FC_STATE_MAYBEOFFLINE
mdefine_line|#define FC_STATE_MAYBEOFFLINE&t;5
DECL|macro|FC_STATUS_OK
mdefine_line|#define FC_STATUS_OK&t;&t;&t;0
DECL|macro|FC_STATUS_P_RJT
mdefine_line|#define FC_STATUS_P_RJT&t;&t;&t;2
DECL|macro|FC_STATUS_F_RJT
mdefine_line|#define FC_STATUS_F_RJT&t;&t;&t;3
DECL|macro|FC_STATUS_P_BSY
mdefine_line|#define FC_STATUS_P_BSY&t;&t;&t;4
DECL|macro|FC_STATUS_F_BSY
mdefine_line|#define FC_STATUS_F_BSY&t;&t;&t;5
DECL|macro|FC_STATUS_ERR_OFFLINE
mdefine_line|#define FC_STATUS_ERR_OFFLINE&t;&t;0x11
DECL|macro|FC_STATUS_TIMEOUT
mdefine_line|#define FC_STATUS_TIMEOUT&t;&t;0x12
DECL|macro|FC_STATUS_ERR_OVERRUN
mdefine_line|#define FC_STATUS_ERR_OVERRUN&t;&t;0x13
DECL|macro|FC_STATUS_POINTTOPOINT
mdefine_line|#define FC_STATUS_POINTTOPOINT&t;&t;0x15
DECL|macro|FC_STATUS_AL
mdefine_line|#define FC_STATUS_AL&t;&t;&t;0x16
DECL|macro|FC_STATUS_UNKNOWN_CQ_TYPE
mdefine_line|#define FC_STATUS_UNKNOWN_CQ_TYPE&t;0x20
DECL|macro|FC_STATUS_BAD_SEG_CNT
mdefine_line|#define FC_STATUS_BAD_SEG_CNT&t;&t;0x21
DECL|macro|FC_STATUS_MAX_XCHG_EXCEEDED
mdefine_line|#define FC_STATUS_MAX_XCHG_EXCEEDED&t;0x22
DECL|macro|FC_STATUS_BAD_XID
mdefine_line|#define FC_STATUS_BAD_XID&t;&t;0x23
DECL|macro|FC_STATUS_XCHG_BUSY
mdefine_line|#define FC_STATUS_XCHG_BUSY&t;&t;0x24
DECL|macro|FC_STATUS_BAD_POOL_ID
mdefine_line|#define FC_STATUS_BAD_POOL_ID&t;&t;0x25
DECL|macro|FC_STATUS_INSUFFICIENT_CQES
mdefine_line|#define FC_STATUS_INSUFFICIENT_CQES&t;0x26
DECL|macro|FC_STATUS_ALLOC_FAIL
mdefine_line|#define FC_STATUS_ALLOC_FAIL&t;&t;0x27
DECL|macro|FC_STATUS_BAD_SID
mdefine_line|#define FC_STATUS_BAD_SID&t;&t;0x28
DECL|macro|FC_STATUS_NO_SEQ_INIT
mdefine_line|#define FC_STATUS_NO_SEQ_INIT&t;&t;0x29
DECL|macro|FC_STATUS_TIMED_OUT
mdefine_line|#define FC_STATUS_TIMED_OUT&t;&t;-1
DECL|macro|FC_STATUS_BAD_RSP
mdefine_line|#define FC_STATUS_BAD_RSP&t;&t;-2
r_void
id|fcp_queue_empty
c_func
(paren
id|fc_channel
op_star
)paren
suffix:semicolon
r_int
id|fcp_init
c_func
(paren
id|fc_channel
op_star
)paren
suffix:semicolon
r_void
id|fcp_release
c_func
(paren
id|fc_channel
op_star
id|fc_chain
comma
r_int
id|count
)paren
suffix:semicolon
r_void
id|fcp_receive_solicited
c_func
(paren
id|fc_channel
op_star
comma
r_int
comma
r_int
comma
r_int
comma
id|fc_hdr
op_star
)paren
suffix:semicolon
r_void
id|fcp_state_change
c_func
(paren
id|fc_channel
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|fc_do_plogi
c_func
(paren
id|fc_channel
op_star
comma
r_int
r_char
comma
id|fc_wwn
op_star
comma
id|fc_wwn
op_star
)paren
suffix:semicolon
r_int
id|fc_do_prli
c_func
(paren
id|fc_channel
op_star
comma
r_int
r_char
)paren
suffix:semicolon
DECL|macro|for_each_fc_channel
mdefine_line|#define for_each_fc_channel(fc)&t;&t;&t;&t;&bslash;&n;&t;for (fc = fc_channels; fc; fc = fc-&gt;next)
DECL|macro|for_each_online_fc_channel
mdefine_line|#define for_each_online_fc_channel(fc) &t;&t;&t;&bslash;&n;&t;for_each_fc_channel(fc)&t;&t;&t;&t;&bslash;&n;&t;&t;if (fc-&gt;state == FC_STATE_ONLINE)
r_int
id|fcp_scsi_queuecommand
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
id|fcp_old_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|fcp_scsi_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|fcp_scsi_dev_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|fcp_scsi_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|fcp_scsi_host_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
macro_line|#endif /* !(_FCP_SCSI_H) */
eof
