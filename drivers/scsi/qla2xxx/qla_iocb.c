multiline_comment|/******************************************************************************&n; *                  QLOGIC LINUX SOFTWARE&n; *&n; * QLogic ISP2x00 device driver for Linux 2.6.x&n; * Copyright (C) 2003-2004 QLogic Corporation&n; * (www.qlogic.com)&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; *&n; ******************************************************************************/
macro_line|#include &quot;qla_os.h&quot;
macro_line|#include &quot;qla_def.h&quot;
r_static
r_inline
r_uint16
id|qla2x00_get_cmd_direction
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_static
r_inline
id|cont_entry_t
op_star
id|qla2x00_prep_cont_type0_iocb
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_static
r_inline
id|cont_a64_entry_t
op_star
id|qla2x00_prep_cont_type1_iocb
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
multiline_comment|/**&n; * qla2x00_get_cmd_direction() - Determine control_flag data direction.&n; * @cmd: SCSI command&n; *&n; * Returns the proper CF_* direction based on CDB.&n; */
r_static
r_inline
r_uint16
DECL|function|qla2x00_get_cmd_direction
id|qla2x00_get_cmd_direction
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
)paren
(brace
r_uint16
id|cflags
suffix:semicolon
id|cflags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set transfer direction */
r_if
c_cond
(paren
id|cmd-&gt;sc_data_direction
op_eq
id|DMA_TO_DEVICE
)paren
id|cflags
op_assign
id|CF_WRITE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cmd-&gt;sc_data_direction
op_eq
id|DMA_FROM_DEVICE
)paren
id|cflags
op_assign
id|CF_READ
suffix:semicolon
r_else
(brace
r_switch
c_cond
(paren
id|cmd-&gt;data_cmnd
(braket
l_int|0
)braket
)paren
(brace
r_case
id|WRITE_6
suffix:colon
r_case
id|WRITE_10
suffix:colon
r_case
id|WRITE_12
suffix:colon
r_case
id|WRITE_BUFFER
suffix:colon
r_case
id|WRITE_LONG
suffix:colon
r_case
id|WRITE_SAME
suffix:colon
r_case
id|WRITE_VERIFY
suffix:colon
r_case
id|WRITE_VERIFY_12
suffix:colon
r_case
id|FORMAT_UNIT
suffix:colon
r_case
id|SEND_VOLUME_TAG
suffix:colon
r_case
id|MODE_SELECT
suffix:colon
r_case
id|SEND_DIAGNOSTIC
suffix:colon
r_case
id|MODE_SELECT_10
suffix:colon
id|cflags
op_assign
id|CF_WRITE
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|cflags
op_assign
id|CF_READ
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
(paren
id|cflags
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_calc_iocbs_32() - Determine number of Command Type 2 and&n; * Continuation Type 0 IOCBs to allocate.&n; *&n; * @dsds: number of data segment decriptors needed&n; *&n; * Returns the number of IOCB entries needed to store @dsds.&n; */
r_uint16
DECL|function|qla2x00_calc_iocbs_32
id|qla2x00_calc_iocbs_32
c_func
(paren
r_uint16
id|dsds
)paren
(brace
r_uint16
id|iocbs
suffix:semicolon
id|iocbs
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|dsds
OG
l_int|3
)paren
(brace
id|iocbs
op_add_assign
(paren
id|dsds
op_minus
l_int|3
)paren
op_div
l_int|7
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dsds
op_minus
l_int|3
)paren
op_mod
l_int|7
)paren
id|iocbs
op_increment
suffix:semicolon
)brace
r_return
(paren
id|iocbs
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_calc_iocbs_64() - Determine number of Command Type 3 and&n; * Continuation Type 1 IOCBs to allocate.&n; *&n; * @dsds: number of data segment decriptors needed&n; *&n; * Returns the number of IOCB entries needed to store @dsds.&n; */
r_uint16
DECL|function|qla2x00_calc_iocbs_64
id|qla2x00_calc_iocbs_64
c_func
(paren
r_uint16
id|dsds
)paren
(brace
r_uint16
id|iocbs
suffix:semicolon
id|iocbs
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|dsds
OG
l_int|2
)paren
(brace
id|iocbs
op_add_assign
(paren
id|dsds
op_minus
l_int|2
)paren
op_div
l_int|5
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dsds
op_minus
l_int|2
)paren
op_mod
l_int|5
)paren
id|iocbs
op_increment
suffix:semicolon
)brace
r_return
(paren
id|iocbs
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_prep_cont_type0_iocb() - Initialize a Continuation Type 0 IOCB.&n; * @ha: HA context&n; *&n; * Returns a pointer to the Continuation Type 0 IOCB packet.&n; */
r_static
r_inline
id|cont_entry_t
op_star
DECL|function|qla2x00_prep_cont_type0_iocb
id|qla2x00_prep_cont_type0_iocb
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
)paren
(brace
id|cont_entry_t
op_star
id|cont_pkt
suffix:semicolon
multiline_comment|/* Adjust ring index. */
id|ha-&gt;req_ring_index
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ha-&gt;req_ring_index
op_eq
id|REQUEST_ENTRY_CNT
)paren
(brace
id|ha-&gt;req_ring_index
op_assign
l_int|0
suffix:semicolon
id|ha-&gt;request_ring_ptr
op_assign
id|ha-&gt;request_ring
suffix:semicolon
)brace
r_else
(brace
id|ha-&gt;request_ring_ptr
op_increment
suffix:semicolon
)brace
id|cont_pkt
op_assign
(paren
id|cont_entry_t
op_star
)paren
id|ha-&gt;request_ring_ptr
suffix:semicolon
multiline_comment|/* Load packet defaults. */
op_star
(paren
(paren
r_uint32
op_star
)paren
(paren
op_amp
id|cont_pkt-&gt;entry_type
)paren
)paren
op_assign
id|__constant_cpu_to_le32
c_func
(paren
id|CONTINUE_TYPE
)paren
suffix:semicolon
r_return
(paren
id|cont_pkt
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_prep_cont_type1_iocb() - Initialize a Continuation Type 1 IOCB.&n; * @ha: HA context&n; *&n; * Returns a pointer to the continuation type 1 IOCB packet.&n; */
r_static
r_inline
id|cont_a64_entry_t
op_star
DECL|function|qla2x00_prep_cont_type1_iocb
id|qla2x00_prep_cont_type1_iocb
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
)paren
(brace
id|cont_a64_entry_t
op_star
id|cont_pkt
suffix:semicolon
multiline_comment|/* Adjust ring index. */
id|ha-&gt;req_ring_index
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ha-&gt;req_ring_index
op_eq
id|REQUEST_ENTRY_CNT
)paren
(brace
id|ha-&gt;req_ring_index
op_assign
l_int|0
suffix:semicolon
id|ha-&gt;request_ring_ptr
op_assign
id|ha-&gt;request_ring
suffix:semicolon
)brace
r_else
(brace
id|ha-&gt;request_ring_ptr
op_increment
suffix:semicolon
)brace
id|cont_pkt
op_assign
(paren
id|cont_a64_entry_t
op_star
)paren
id|ha-&gt;request_ring_ptr
suffix:semicolon
multiline_comment|/* Load packet defaults. */
op_star
(paren
(paren
r_uint32
op_star
)paren
(paren
op_amp
id|cont_pkt-&gt;entry_type
)paren
)paren
op_assign
id|__constant_cpu_to_le32
c_func
(paren
id|CONTINUE_A64_TYPE
)paren
suffix:semicolon
r_return
(paren
id|cont_pkt
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_build_scsi_iocbs_32() - Build IOCB command utilizing 32bit&n; * capable IOCB types.&n; *&n; * @sp: SRB command to process&n; * @cmd_pkt: Command type 2 IOCB&n; * @tot_dsds: Total number of segments to transfer&n; */
DECL|function|qla2x00_build_scsi_iocbs_32
r_void
id|qla2x00_build_scsi_iocbs_32
c_func
(paren
id|srb_t
op_star
id|sp
comma
id|cmd_entry_t
op_star
id|cmd_pkt
comma
r_uint16
id|tot_dsds
)paren
(brace
r_uint16
id|avail_dsds
suffix:semicolon
r_uint32
op_star
id|cur_dsd
suffix:semicolon
id|scsi_qla_host_t
op_star
id|ha
suffix:semicolon
r_struct
id|scsi_cmnd
op_star
id|cmd
suffix:semicolon
id|cmd
op_assign
id|sp-&gt;cmd
suffix:semicolon
multiline_comment|/* Update entry type to indicate Command Type 2 IOCB */
op_star
(paren
(paren
r_uint32
op_star
)paren
(paren
op_amp
id|cmd_pkt-&gt;entry_type
)paren
)paren
op_assign
id|__constant_cpu_to_le32
c_func
(paren
id|COMMAND_TYPE
)paren
suffix:semicolon
multiline_comment|/* No data transfer */
r_if
c_cond
(paren
id|cmd-&gt;request_bufflen
op_eq
l_int|0
op_logical_or
id|cmd-&gt;sc_data_direction
op_eq
id|DMA_NONE
)paren
(brace
id|cmd_pkt-&gt;byte_count
op_assign
id|__constant_cpu_to_le32
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ha
op_assign
id|sp-&gt;ha
suffix:semicolon
id|cmd_pkt-&gt;control_flags
op_or_assign
id|cpu_to_le16
c_func
(paren
id|qla2x00_get_cmd_direction
c_func
(paren
id|cmd
)paren
)paren
suffix:semicolon
multiline_comment|/* Three DSDs are available in the Command Type 2 IOCB */
id|avail_dsds
op_assign
l_int|3
suffix:semicolon
id|cur_dsd
op_assign
(paren
r_uint32
op_star
)paren
op_amp
id|cmd_pkt-&gt;dseg_0_address
suffix:semicolon
multiline_comment|/* Load data segments */
r_if
c_cond
(paren
id|cmd-&gt;use_sg
op_ne
l_int|0
)paren
(brace
r_struct
id|scatterlist
op_star
id|cur_seg
suffix:semicolon
r_struct
id|scatterlist
op_star
id|end_seg
suffix:semicolon
id|cur_seg
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|cmd-&gt;request_buffer
suffix:semicolon
id|end_seg
op_assign
id|cur_seg
op_plus
id|tot_dsds
suffix:semicolon
r_while
c_loop
(paren
id|cur_seg
OL
id|end_seg
)paren
(brace
id|cont_entry_t
op_star
id|cont_pkt
suffix:semicolon
multiline_comment|/* Allocate additional continuation packets? */
r_if
c_cond
(paren
id|avail_dsds
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Seven DSDs are available in the Continuation&n;&t;&t;&t;&t; * Type 0 IOCB.&n;&t;&t;&t;&t; */
id|cont_pkt
op_assign
id|qla2x00_prep_cont_type0_iocb
c_func
(paren
id|ha
)paren
suffix:semicolon
id|cur_dsd
op_assign
(paren
r_uint32
op_star
)paren
op_amp
id|cont_pkt-&gt;dseg_0_address
suffix:semicolon
id|avail_dsds
op_assign
l_int|7
suffix:semicolon
)brace
op_star
id|cur_dsd
op_increment
op_assign
id|cpu_to_le32
c_func
(paren
id|sg_dma_address
c_func
(paren
id|cur_seg
)paren
)paren
suffix:semicolon
op_star
id|cur_dsd
op_increment
op_assign
id|cpu_to_le32
c_func
(paren
id|sg_dma_len
c_func
(paren
id|cur_seg
)paren
)paren
suffix:semicolon
id|avail_dsds
op_decrement
suffix:semicolon
id|cur_seg
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
id|dma_addr_t
id|req_dma
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|cmd-&gt;request_buffer
)paren
suffix:semicolon
id|offset
op_assign
(paren
(paren
r_int
r_int
)paren
id|cmd-&gt;request_buffer
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
id|req_dma
op_assign
id|pci_map_page
c_func
(paren
id|ha-&gt;pdev
comma
id|page
comma
id|offset
comma
id|cmd-&gt;request_bufflen
comma
id|cmd-&gt;sc_data_direction
)paren
suffix:semicolon
id|sp-&gt;dma_handle
op_assign
id|req_dma
suffix:semicolon
op_star
id|cur_dsd
op_increment
op_assign
id|cpu_to_le32
c_func
(paren
id|req_dma
)paren
suffix:semicolon
op_star
id|cur_dsd
op_increment
op_assign
id|cpu_to_le32
c_func
(paren
id|cmd-&gt;request_bufflen
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * qla2x00_build_scsi_iocbs_64() - Build IOCB command utilizing 64bit&n; * capable IOCB types.&n; *&n; * @sp: SRB command to process&n; * @cmd_pkt: Command type 3 IOCB&n; * @tot_dsds: Total number of segments to transfer&n; */
DECL|function|qla2x00_build_scsi_iocbs_64
r_void
id|qla2x00_build_scsi_iocbs_64
c_func
(paren
id|srb_t
op_star
id|sp
comma
id|cmd_entry_t
op_star
id|cmd_pkt
comma
r_uint16
id|tot_dsds
)paren
(brace
r_uint16
id|avail_dsds
suffix:semicolon
r_uint32
op_star
id|cur_dsd
suffix:semicolon
id|scsi_qla_host_t
op_star
id|ha
suffix:semicolon
r_struct
id|scsi_cmnd
op_star
id|cmd
suffix:semicolon
id|cmd
op_assign
id|sp-&gt;cmd
suffix:semicolon
multiline_comment|/* Update entry type to indicate Command Type 3 IOCB */
op_star
(paren
(paren
r_uint32
op_star
)paren
(paren
op_amp
id|cmd_pkt-&gt;entry_type
)paren
)paren
op_assign
id|__constant_cpu_to_le32
c_func
(paren
id|COMMAND_A64_TYPE
)paren
suffix:semicolon
multiline_comment|/* No data transfer */
r_if
c_cond
(paren
id|cmd-&gt;request_bufflen
op_eq
l_int|0
op_logical_or
id|cmd-&gt;sc_data_direction
op_eq
id|DMA_NONE
)paren
(brace
id|cmd_pkt-&gt;byte_count
op_assign
id|__constant_cpu_to_le32
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ha
op_assign
id|sp-&gt;ha
suffix:semicolon
id|cmd_pkt-&gt;control_flags
op_or_assign
id|cpu_to_le16
c_func
(paren
id|qla2x00_get_cmd_direction
c_func
(paren
id|cmd
)paren
)paren
suffix:semicolon
multiline_comment|/* Two DSDs are available in the Command Type 3 IOCB */
id|avail_dsds
op_assign
l_int|2
suffix:semicolon
id|cur_dsd
op_assign
(paren
r_uint32
op_star
)paren
op_amp
id|cmd_pkt-&gt;dseg_0_address
suffix:semicolon
multiline_comment|/* Load data segments */
r_if
c_cond
(paren
id|cmd-&gt;use_sg
op_ne
l_int|0
)paren
(brace
r_struct
id|scatterlist
op_star
id|cur_seg
suffix:semicolon
r_struct
id|scatterlist
op_star
id|end_seg
suffix:semicolon
id|cur_seg
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|cmd-&gt;request_buffer
suffix:semicolon
id|end_seg
op_assign
id|cur_seg
op_plus
id|tot_dsds
suffix:semicolon
r_while
c_loop
(paren
id|cur_seg
OL
id|end_seg
)paren
(brace
id|dma_addr_t
id|sle_dma
suffix:semicolon
id|cont_a64_entry_t
op_star
id|cont_pkt
suffix:semicolon
multiline_comment|/* Allocate additional continuation packets? */
r_if
c_cond
(paren
id|avail_dsds
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Five DSDs are available in the Continuation&n;&t;&t;&t;&t; * Type 1 IOCB.&n;&t;&t;&t;&t; */
id|cont_pkt
op_assign
id|qla2x00_prep_cont_type1_iocb
c_func
(paren
id|ha
)paren
suffix:semicolon
id|cur_dsd
op_assign
(paren
r_uint32
op_star
)paren
id|cont_pkt-&gt;dseg_0_address
suffix:semicolon
id|avail_dsds
op_assign
l_int|5
suffix:semicolon
)brace
id|sle_dma
op_assign
id|sg_dma_address
c_func
(paren
id|cur_seg
)paren
suffix:semicolon
op_star
id|cur_dsd
op_increment
op_assign
id|cpu_to_le32
c_func
(paren
id|LSD
c_func
(paren
id|sle_dma
)paren
)paren
suffix:semicolon
op_star
id|cur_dsd
op_increment
op_assign
id|cpu_to_le32
c_func
(paren
id|MSD
c_func
(paren
id|sle_dma
)paren
)paren
suffix:semicolon
op_star
id|cur_dsd
op_increment
op_assign
id|cpu_to_le32
c_func
(paren
id|sg_dma_len
c_func
(paren
id|cur_seg
)paren
)paren
suffix:semicolon
id|avail_dsds
op_decrement
suffix:semicolon
id|cur_seg
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
id|dma_addr_t
id|req_dma
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|cmd-&gt;request_buffer
)paren
suffix:semicolon
id|offset
op_assign
(paren
(paren
r_int
r_int
)paren
id|cmd-&gt;request_buffer
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
id|req_dma
op_assign
id|pci_map_page
c_func
(paren
id|ha-&gt;pdev
comma
id|page
comma
id|offset
comma
id|cmd-&gt;request_bufflen
comma
id|cmd-&gt;sc_data_direction
)paren
suffix:semicolon
id|sp-&gt;dma_handle
op_assign
id|req_dma
suffix:semicolon
op_star
id|cur_dsd
op_increment
op_assign
id|cpu_to_le32
c_func
(paren
id|LSD
c_func
(paren
id|req_dma
)paren
)paren
suffix:semicolon
op_star
id|cur_dsd
op_increment
op_assign
id|cpu_to_le32
c_func
(paren
id|MSD
c_func
(paren
id|req_dma
)paren
)paren
suffix:semicolon
op_star
id|cur_dsd
op_increment
op_assign
id|cpu_to_le32
c_func
(paren
id|cmd-&gt;request_bufflen
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * qla2x00_start_scsi() - Send a SCSI command to the ISP&n; * @sp: command to send to the ISP&n; *&n; * Returns non-zero if a failure occured, else zero.&n; */
r_int
DECL|function|qla2x00_start_scsi
id|qla2x00_start_scsi
c_func
(paren
id|srb_t
op_star
id|sp
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|scsi_qla_host_t
op_star
id|ha
suffix:semicolon
id|fc_lun_t
op_star
id|fclun
suffix:semicolon
r_struct
id|scsi_cmnd
op_star
id|cmd
suffix:semicolon
r_uint32
op_star
id|clr_ptr
suffix:semicolon
r_uint32
id|index
suffix:semicolon
r_uint32
id|handle
suffix:semicolon
r_uint16
id|cnt
suffix:semicolon
id|cmd_entry_t
op_star
id|cmd_pkt
suffix:semicolon
r_uint32
id|timeout
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sg
suffix:semicolon
id|device_reg_t
op_star
id|reg
suffix:semicolon
multiline_comment|/* Setup device pointers. */
id|ret
op_assign
l_int|0
suffix:semicolon
id|fclun
op_assign
id|sp-&gt;lun_queue-&gt;fclun
suffix:semicolon
id|ha
op_assign
id|fclun-&gt;fcport-&gt;ha
suffix:semicolon
id|cmd
op_assign
id|sp-&gt;cmd
suffix:semicolon
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
multiline_comment|/* Send marker if required */
r_if
c_cond
(paren
id|ha-&gt;marker_needed
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|qla2x00_marker
c_func
(paren
id|ha
comma
l_int|0
comma
l_int|0
comma
id|MK_SYNC_ALL
)paren
op_ne
id|QLA_SUCCESS
)paren
(brace
r_return
(paren
id|QLA_FUNCTION_FAILED
)paren
suffix:semicolon
)brace
id|ha-&gt;marker_needed
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Calculate number of segments and entries required. */
r_if
c_cond
(paren
id|sp-&gt;req_cnt
op_eq
l_int|0
)paren
(brace
id|sp-&gt;tot_dsds
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;use_sg
)paren
(brace
id|sg
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|cmd-&gt;request_buffer
suffix:semicolon
id|sp-&gt;tot_dsds
op_assign
id|pci_map_sg
c_func
(paren
id|ha-&gt;pdev
comma
id|sg
comma
id|cmd-&gt;use_sg
comma
id|cmd-&gt;sc_data_direction
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmd-&gt;request_bufflen
)paren
(brace
id|sp-&gt;tot_dsds
op_increment
suffix:semicolon
)brace
id|sp-&gt;req_cnt
op_assign
(paren
id|ha-&gt;calc_request_entries
)paren
(paren
id|sp-&gt;tot_dsds
)paren
suffix:semicolon
)brace
multiline_comment|/* Acquire ring specific lock */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ha-&gt;hardware_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ha-&gt;req_q_cnt
OL
(paren
id|sp-&gt;req_cnt
op_plus
l_int|2
)paren
)paren
(brace
multiline_comment|/* Calculate number of free request entries */
id|cnt
op_assign
id|RD_REG_WORD
c_func
(paren
id|ISP_REQ_Q_OUT
c_func
(paren
id|ha
comma
id|reg
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ha-&gt;req_ring_index
OL
id|cnt
)paren
id|ha-&gt;req_q_cnt
op_assign
id|cnt
op_minus
id|ha-&gt;req_ring_index
suffix:semicolon
r_else
id|ha-&gt;req_q_cnt
op_assign
id|REQUEST_ENTRY_CNT
op_minus
(paren
id|ha-&gt;req_ring_index
op_minus
id|cnt
)paren
suffix:semicolon
)brace
multiline_comment|/* If no room for request in request ring */
r_if
c_cond
(paren
id|ha-&gt;req_q_cnt
OL
(paren
id|sp-&gt;req_cnt
op_plus
l_int|2
)paren
)paren
(brace
id|DEBUG5
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;scsi(%ld): in-ptr=%x req_q_cnt=%x &quot;
l_string|&quot;tot_dsds=%x.&bslash;n&quot;
comma
id|ha-&gt;host_no
comma
id|ha-&gt;req_ring_index
comma
id|ha-&gt;req_q_cnt
comma
id|sp-&gt;tot_dsds
)paren
)paren
suffix:semicolon
r_goto
id|queuing_error
suffix:semicolon
)brace
multiline_comment|/* Check for room in outstanding command list. */
id|handle
op_assign
id|ha-&gt;current_outstanding_cmd
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|1
suffix:semicolon
id|index
OL
id|MAX_OUTSTANDING_COMMANDS
suffix:semicolon
id|index
op_increment
)paren
(brace
id|handle
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|handle
op_eq
id|MAX_OUTSTANDING_COMMANDS
)paren
id|handle
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ha-&gt;outstanding_cmds
(braket
id|handle
)braket
op_eq
l_int|0
)paren
(brace
id|ha-&gt;current_outstanding_cmd
op_assign
id|handle
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|index
op_eq
id|MAX_OUTSTANDING_COMMANDS
)paren
(brace
id|DEBUG5
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;scsi(%ld): Unable to queue command -- NO ROOM &quot;
l_string|&quot;IN OUTSTANDING ARRAY (req_q_cnt=%x).&bslash;n&quot;
comma
id|ha-&gt;host_no
comma
id|ha-&gt;req_q_cnt
)paren
)paren
suffix:semicolon
r_goto
id|queuing_error
suffix:semicolon
)brace
multiline_comment|/* Build command packet */
id|ha-&gt;outstanding_cmds
(braket
id|handle
)braket
op_assign
id|sp
suffix:semicolon
id|sp-&gt;ha
op_assign
id|ha
suffix:semicolon
id|sp-&gt;cmd-&gt;host_scribble
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
r_int
r_int
)paren
id|handle
suffix:semicolon
id|ha-&gt;req_q_cnt
op_sub_assign
id|sp-&gt;req_cnt
suffix:semicolon
id|cmd_pkt
op_assign
(paren
id|cmd_entry_t
op_star
)paren
id|ha-&gt;request_ring_ptr
suffix:semicolon
id|cmd_pkt-&gt;handle
op_assign
id|handle
suffix:semicolon
multiline_comment|/* Zero out remaining portion of packet. */
id|clr_ptr
op_assign
(paren
r_uint32
op_star
)paren
id|cmd_pkt
op_plus
l_int|2
suffix:semicolon
id|memset
c_func
(paren
id|clr_ptr
comma
l_int|0
comma
id|REQUEST_ENTRY_SIZE
op_minus
l_int|8
)paren
suffix:semicolon
id|cmd_pkt-&gt;dseg_count
op_assign
id|cpu_to_le16
c_func
(paren
id|sp-&gt;tot_dsds
)paren
suffix:semicolon
multiline_comment|/* Set target ID */
id|SET_TARGET_ID
c_func
(paren
id|ha
comma
id|cmd_pkt-&gt;target
comma
id|fclun-&gt;fcport-&gt;loop_id
)paren
suffix:semicolon
multiline_comment|/* Set LUN number*/
id|cmd_pkt-&gt;lun
op_assign
id|cpu_to_le16
c_func
(paren
id|fclun-&gt;lun
)paren
suffix:semicolon
multiline_comment|/* Update tagged queuing modifier */
id|cmd_pkt-&gt;control_flags
op_assign
id|__constant_cpu_to_le16
c_func
(paren
id|CF_SIMPLE_TAG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;device-&gt;tagged_supported
)paren
(brace
r_switch
c_cond
(paren
id|cmd-&gt;tag
)paren
(brace
r_case
id|HEAD_OF_QUEUE_TAG
suffix:colon
id|cmd_pkt-&gt;control_flags
op_assign
id|__constant_cpu_to_le16
c_func
(paren
id|CF_HEAD_TAG
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ORDERED_QUEUE_TAG
suffix:colon
id|cmd_pkt-&gt;control_flags
op_assign
id|__constant_cpu_to_le16
c_func
(paren
id|CF_ORDERED_TAG
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Allocate at least 5 (+ QLA_CMD_TIMER_DELTA) seconds for RISC timeout.&n;&t; */
id|timeout
op_assign
(paren
r_uint32
)paren
(paren
id|cmd-&gt;timeout_per_command
op_div
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|timeout
OG
l_int|65535
)paren
id|cmd_pkt-&gt;timeout
op_assign
id|__constant_cpu_to_le16
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|timeout
OG
l_int|25
)paren
id|cmd_pkt-&gt;timeout
op_assign
id|cpu_to_le16
c_func
(paren
(paren
r_uint16
)paren
id|timeout
op_minus
(paren
l_int|5
op_plus
id|QLA_CMD_TIMER_DELTA
)paren
)paren
suffix:semicolon
r_else
id|cmd_pkt-&gt;timeout
op_assign
id|cpu_to_le16
c_func
(paren
(paren
r_uint16
)paren
id|timeout
)paren
suffix:semicolon
multiline_comment|/* Load SCSI command packet. */
id|memcpy
c_func
(paren
id|cmd_pkt-&gt;scsi_cdb
comma
id|cmd-&gt;cmnd
comma
id|cmd-&gt;cmd_len
)paren
suffix:semicolon
id|cmd_pkt-&gt;byte_count
op_assign
id|cpu_to_le32
c_func
(paren
(paren
r_uint32
)paren
id|cmd-&gt;request_bufflen
)paren
suffix:semicolon
multiline_comment|/* Build IOCB segments */
(paren
id|ha-&gt;build_scsi_iocbs
)paren
(paren
id|sp
comma
id|cmd_pkt
comma
id|sp-&gt;tot_dsds
)paren
suffix:semicolon
multiline_comment|/* Set total data segment count. */
id|cmd_pkt-&gt;entry_count
op_assign
(paren
r_uint8
)paren
id|sp-&gt;req_cnt
suffix:semicolon
multiline_comment|/* Adjust ring index. */
id|ha-&gt;req_ring_index
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ha-&gt;req_ring_index
op_eq
id|REQUEST_ENTRY_CNT
)paren
(brace
id|ha-&gt;req_ring_index
op_assign
l_int|0
suffix:semicolon
id|ha-&gt;request_ring_ptr
op_assign
id|ha-&gt;request_ring
suffix:semicolon
)brace
r_else
id|ha-&gt;request_ring_ptr
op_increment
suffix:semicolon
id|ha-&gt;actthreads
op_increment
suffix:semicolon
id|ha-&gt;total_ios
op_increment
suffix:semicolon
id|sp-&gt;lun_queue-&gt;out_cnt
op_increment
suffix:semicolon
id|sp-&gt;flags
op_or_assign
id|SRB_DMA_VALID
suffix:semicolon
id|sp-&gt;state
op_assign
id|SRB_ACTIVE_STATE
suffix:semicolon
id|sp-&gt;u_start
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/* Set chip new ring index. */
id|WRT_REG_WORD
c_func
(paren
id|ISP_REQ_Q_IN
c_func
(paren
id|ha
comma
id|reg
)paren
comma
id|ha-&gt;req_ring_index
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
id|ISP_REQ_Q_IN
c_func
(paren
id|ha
comma
id|reg
)paren
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ha-&gt;hardware_lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
id|QLA_SUCCESS
)paren
suffix:semicolon
id|queuing_error
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ha-&gt;hardware_lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
id|QLA_FUNCTION_FAILED
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_marker() - Send a marker IOCB to the firmware.&n; * @ha: HA context&n; * @loop_id: loop ID&n; * @lun: LUN&n; * @type: marker modifier&n; *&n; * Can be called from both normal and interrupt context.&n; *&n; * Returns non-zero if a failure occured, else zero.&n; */
r_int
DECL|function|__qla2x00_marker
id|__qla2x00_marker
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint16
id|loop_id
comma
r_uint16
id|lun
comma
r_uint8
id|type
)paren
(brace
id|mrk_entry_t
op_star
id|pkt
suffix:semicolon
id|pkt
op_assign
(paren
id|mrk_entry_t
op_star
)paren
id|qla2x00_req_pkt
c_func
(paren
id|ha
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pkt
op_eq
l_int|NULL
)paren
(brace
id|DEBUG2_3
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;%s(): **** FAILED ****&bslash;n&quot;
comma
id|__func__
)paren
)paren
suffix:semicolon
r_return
(paren
id|QLA_FUNCTION_FAILED
)paren
suffix:semicolon
)brace
id|pkt-&gt;entry_type
op_assign
id|MARKER_TYPE
suffix:semicolon
id|pkt-&gt;modifier
op_assign
id|type
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|MK_SYNC_ALL
)paren
(brace
id|pkt-&gt;lun
op_assign
id|cpu_to_le16
c_func
(paren
id|lun
)paren
suffix:semicolon
id|SET_TARGET_ID
c_func
(paren
id|ha
comma
id|pkt-&gt;target
comma
id|loop_id
)paren
suffix:semicolon
)brace
multiline_comment|/* Issue command to ISP */
id|qla2x00_isp_cmd
c_func
(paren
id|ha
)paren
suffix:semicolon
r_return
(paren
id|QLA_SUCCESS
)paren
suffix:semicolon
)brace
r_int
DECL|function|qla2x00_marker
id|qla2x00_marker
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint16
id|loop_id
comma
r_uint16
id|lun
comma
r_uint8
id|type
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ha-&gt;hardware_lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
id|__qla2x00_marker
c_func
(paren
id|ha
comma
id|loop_id
comma
id|lun
comma
id|type
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ha-&gt;hardware_lock
comma
id|flags
)paren
suffix:semicolon
r_return
(paren
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_req_pkt() - Retrieve a request packet from the request ring.&n; * @ha: HA context&n; *&n; * Note: The caller must hold the hardware lock before calling this routine.&n; *&n; * Returns NULL if function failed, else, a pointer to the request packet.&n; */
id|request_t
op_star
DECL|function|qla2x00_req_pkt
id|qla2x00_req_pkt
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
)paren
(brace
id|device_reg_t
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
id|request_t
op_star
id|pkt
op_assign
l_int|NULL
suffix:semicolon
r_uint16
id|cnt
suffix:semicolon
r_uint32
op_star
id|dword_ptr
suffix:semicolon
r_uint32
id|timer
suffix:semicolon
r_uint16
id|req_cnt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Wait 1 second for slot. */
r_for
c_loop
(paren
id|timer
op_assign
id|HZ
suffix:semicolon
id|timer
suffix:semicolon
id|timer
op_decrement
)paren
(brace
r_if
c_cond
(paren
(paren
id|req_cnt
op_plus
l_int|2
)paren
op_ge
id|ha-&gt;req_q_cnt
)paren
(brace
multiline_comment|/* Calculate number of free request entries. */
id|cnt
op_assign
id|qla2x00_debounce_register
c_func
(paren
id|ISP_REQ_Q_OUT
c_func
(paren
id|ha
comma
id|reg
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ha-&gt;req_ring_index
OL
id|cnt
)paren
id|ha-&gt;req_q_cnt
op_assign
id|cnt
op_minus
id|ha-&gt;req_ring_index
suffix:semicolon
r_else
id|ha-&gt;req_q_cnt
op_assign
id|REQUEST_ENTRY_CNT
op_minus
(paren
id|ha-&gt;req_ring_index
op_minus
id|cnt
)paren
suffix:semicolon
)brace
multiline_comment|/* If room for request in request ring. */
r_if
c_cond
(paren
(paren
id|req_cnt
op_plus
l_int|2
)paren
OL
id|ha-&gt;req_q_cnt
)paren
(brace
id|ha-&gt;req_q_cnt
op_decrement
suffix:semicolon
id|pkt
op_assign
id|ha-&gt;request_ring_ptr
suffix:semicolon
multiline_comment|/* Zero out packet. */
id|dword_ptr
op_assign
(paren
r_uint32
op_star
)paren
id|pkt
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|REQUEST_ENTRY_SIZE
op_div
l_int|4
suffix:semicolon
id|cnt
op_increment
)paren
op_star
id|dword_ptr
op_increment
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set system defined field. */
id|pkt-&gt;sys_define
op_assign
(paren
r_uint8
)paren
id|ha-&gt;req_ring_index
suffix:semicolon
multiline_comment|/* Set entry count. */
id|pkt-&gt;entry_count
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Release ring specific lock */
id|spin_unlock
c_func
(paren
op_amp
id|ha-&gt;hardware_lock
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|2
)paren
suffix:semicolon
multiline_comment|/* 2 us */
multiline_comment|/* Check for pending interrupts. */
multiline_comment|/* During init we issue marker directly */
r_if
c_cond
(paren
op_logical_neg
id|ha-&gt;marker_needed
)paren
id|qla2x00_poll
c_func
(paren
id|ha
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|ha-&gt;hardware_lock
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pkt
)paren
(brace
id|DEBUG2_3
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;%s(): **** FAILED ****&bslash;n&quot;
comma
id|__func__
)paren
)paren
suffix:semicolon
)brace
r_return
(paren
id|pkt
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_ms_req_pkt() - Retrieve a Management Server request packet from&n; * &t;&t;&t;&t;the request ring.&n; * @ha: HA context&n; * @sp: pointer to handle post function call&n; *&n; * Note: The caller must hold the hardware lock before calling this routine.&n; *&n; * Returns NULL if function failed, else, a pointer to the request packet.&n; */
id|request_t
op_star
DECL|function|qla2x00_ms_req_pkt
id|qla2x00_ms_req_pkt
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
id|srb_t
op_star
id|sp
)paren
(brace
id|device_reg_t
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
id|request_t
op_star
id|pkt
op_assign
l_int|NULL
suffix:semicolon
r_uint16
id|cnt
comma
id|i
comma
id|index
suffix:semicolon
r_uint32
op_star
id|dword_ptr
suffix:semicolon
r_uint32
id|timer
suffix:semicolon
r_uint8
id|found
op_assign
l_int|0
suffix:semicolon
r_uint16
id|req_cnt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Wait 1 second for slot. */
r_for
c_loop
(paren
id|timer
op_assign
id|HZ
suffix:semicolon
id|timer
suffix:semicolon
id|timer
op_decrement
)paren
(brace
r_if
c_cond
(paren
(paren
id|req_cnt
op_plus
l_int|2
)paren
op_ge
id|ha-&gt;req_q_cnt
)paren
(brace
multiline_comment|/* Calculate number of free request entries. */
id|cnt
op_assign
id|qla2x00_debounce_register
c_func
(paren
id|ISP_REQ_Q_OUT
c_func
(paren
id|ha
comma
id|reg
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ha-&gt;req_ring_index
OL
id|cnt
)paren
(brace
id|ha-&gt;req_q_cnt
op_assign
id|cnt
op_minus
id|ha-&gt;req_ring_index
suffix:semicolon
)brace
r_else
(brace
id|ha-&gt;req_q_cnt
op_assign
id|REQUEST_ENTRY_CNT
op_minus
(paren
id|ha-&gt;req_ring_index
op_minus
id|cnt
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Check for room in outstanding command list. */
id|cnt
op_assign
id|ha-&gt;current_outstanding_cmd
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
l_int|1
suffix:semicolon
id|index
OL
id|MAX_OUTSTANDING_COMMANDS
suffix:semicolon
id|index
op_increment
)paren
(brace
id|cnt
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|cnt
op_eq
id|MAX_OUTSTANDING_COMMANDS
)paren
id|cnt
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ha-&gt;outstanding_cmds
(braket
id|cnt
)braket
op_eq
l_int|0
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
id|ha-&gt;current_outstanding_cmd
op_assign
id|cnt
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* If room for request in request ring. */
r_if
c_cond
(paren
id|found
op_logical_and
(paren
id|req_cnt
op_plus
l_int|2
)paren
OL
id|ha-&gt;req_q_cnt
)paren
(brace
id|pkt
op_assign
id|ha-&gt;request_ring_ptr
suffix:semicolon
multiline_comment|/* Zero out packet. */
id|dword_ptr
op_assign
(paren
r_uint32
op_star
)paren
id|pkt
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|REQUEST_ENTRY_SIZE
op_div
l_int|4
suffix:semicolon
id|i
op_increment
)paren
op_star
id|dword_ptr
op_increment
op_assign
l_int|0
suffix:semicolon
id|DEBUG5
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;%s(): putting sp=%p in &quot;
l_string|&quot;outstanding_cmds[%x]&bslash;n&quot;
comma
id|__func__
comma
id|sp
comma
id|cnt
)paren
)paren
suffix:semicolon
id|ha-&gt;outstanding_cmds
(braket
id|cnt
)braket
op_assign
id|sp
suffix:semicolon
multiline_comment|/* save the handle */
id|sp-&gt;cmd-&gt;host_scribble
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|u_long
)paren
id|cnt
suffix:semicolon
id|CMD_SP
c_func
(paren
id|sp-&gt;cmd
)paren
op_assign
(paren
r_void
op_star
)paren
id|sp
suffix:semicolon
id|ha-&gt;req_q_cnt
op_decrement
suffix:semicolon
id|pkt-&gt;handle
op_assign
(paren
r_uint32
)paren
id|cnt
suffix:semicolon
multiline_comment|/* Set system defined field. */
id|pkt-&gt;sys_define
op_assign
(paren
r_uint8
)paren
id|ha-&gt;req_ring_index
suffix:semicolon
id|pkt-&gt;entry_status
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Release ring specific lock */
id|spin_unlock
c_func
(paren
op_amp
id|ha-&gt;hardware_lock
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|20
)paren
suffix:semicolon
multiline_comment|/* Check for pending interrupts. */
id|qla2x00_poll
c_func
(paren
id|ha
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|ha-&gt;hardware_lock
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pkt
)paren
(brace
id|DEBUG2_3
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;%s(): **** FAILED ****&bslash;n&quot;
comma
id|__func__
)paren
)paren
suffix:semicolon
)brace
r_return
(paren
id|pkt
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * qla2x00_isp_cmd() - Modify the request ring pointer.&n; * @ha: HA context&n; *&n; * Note: The caller must hold the hardware lock before calling this routine.&n; */
r_void
DECL|function|qla2x00_isp_cmd
id|qla2x00_isp_cmd
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
)paren
(brace
id|device_reg_t
op_star
id|reg
op_assign
id|ha-&gt;iobase
suffix:semicolon
id|DEBUG5
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;%s(): IOCB data:&bslash;n&quot;
comma
id|__func__
)paren
)paren
suffix:semicolon
id|DEBUG5
c_func
(paren
id|qla2x00_dump_buffer
c_func
(paren
(paren
r_uint8
op_star
)paren
id|ha-&gt;request_ring_ptr
comma
id|REQUEST_ENTRY_SIZE
)paren
)paren
suffix:semicolon
multiline_comment|/* Adjust ring index. */
id|ha-&gt;req_ring_index
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ha-&gt;req_ring_index
op_eq
id|REQUEST_ENTRY_CNT
)paren
(brace
id|ha-&gt;req_ring_index
op_assign
l_int|0
suffix:semicolon
id|ha-&gt;request_ring_ptr
op_assign
id|ha-&gt;request_ring
suffix:semicolon
)brace
r_else
id|ha-&gt;request_ring_ptr
op_increment
suffix:semicolon
multiline_comment|/* Set chip new ring index. */
id|WRT_REG_WORD
c_func
(paren
id|ISP_REQ_Q_IN
c_func
(paren
id|ha
comma
id|reg
)paren
comma
id|ha-&gt;req_ring_index
)paren
suffix:semicolon
id|RD_REG_WORD
c_func
(paren
id|ISP_REQ_Q_IN
c_func
(paren
id|ha
comma
id|reg
)paren
)paren
suffix:semicolon
multiline_comment|/* PCI Posting. */
)brace
eof
