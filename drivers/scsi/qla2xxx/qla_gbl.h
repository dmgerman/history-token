multiline_comment|/********************************************************************************&n;*                  QLOGIC LINUX SOFTWARE&n;*&n;* QLogic ISP2x00 device driver for Linux 2.6.x&n;* Copyright (C) 2003-2004 QLogic Corporation&n;* (www.qlogic.com)&n;*&n;* This program is free software; you can redistribute it and/or modify it&n;* under the terms of the GNU General Public License as published by the&n;* Free Software Foundation; either version 2, or (at your option) any&n;* later version.&n;*&n;* This program is distributed in the hope that it will be useful, but&n;* WITHOUT ANY WARRANTY; without even the implied warranty of&n;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;* General Public License for more details.&n;*&n;******************************************************************************&n;* Global include file.&n;******************************************************************************/
macro_line|#ifndef __QLA_GBL_H
DECL|macro|__QLA_GBL_H
mdefine_line|#define&t;__QLA_GBL_H
macro_line|#include &lt;linux/interrupt.h&gt;
r_extern
r_void
id|qla2x00_remove_one
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_probe_one
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_struct
id|qla_board_info
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Global Function Prototypes in qla_init.c source file.&n; */
r_extern
r_int
id|qla2x00_initialize_adapter
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
id|fc_port_t
op_star
id|qla2x00_alloc_fcport
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_loop_resync
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_find_new_loop_id
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|fc_port_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_fabric_login
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|fc_port_t
op_star
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_local_device_login
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_restart_queues
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint8
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_rescan_fcports
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_tgt_free
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint16
id|t
)paren
suffix:semicolon
r_extern
id|os_tgt_t
op_star
id|qla2x00_tgt_alloc
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
)paren
suffix:semicolon
r_extern
id|os_lun_t
op_star
id|qla2x00_lun_alloc
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
comma
r_uint16
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_abort_isp
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Global Data in qla_os.c source file.&n; */
r_extern
r_char
id|qla2x00_version_str
(braket
)braket
suffix:semicolon
r_extern
r_int
id|num_hosts
suffix:semicolon
r_extern
r_int
id|apiHBAInstance
suffix:semicolon
r_extern
r_struct
id|_qla2x00stats
id|qla2x00_stats
suffix:semicolon
r_extern
r_int
id|ql2xretrycount
suffix:semicolon
r_extern
r_int
id|ql2xlogintimeout
suffix:semicolon
r_extern
r_int
id|qlport_down_retry
suffix:semicolon
r_extern
r_int
id|ql2xmaxqdepth
suffix:semicolon
r_extern
r_int
id|displayConfig
suffix:semicolon
r_extern
r_int
id|ql2xplogiabsentdevice
suffix:semicolon
r_extern
r_int
id|ql2xenablezio
suffix:semicolon
r_extern
r_int
id|ql2xintrdelaytimer
suffix:semicolon
r_extern
r_int
id|ql2xloginretrycount
suffix:semicolon
r_extern
r_int
id|ConfigRequired
suffix:semicolon
r_extern
r_int
id|Bind
suffix:semicolon
r_extern
r_int
id|ql2xsuspendcount
suffix:semicolon
macro_line|#if defined(MODULE)
r_extern
r_char
op_star
id|ql2xopts
suffix:semicolon
macro_line|#endif
r_extern
r_char
op_star
id|qla2x00_get_fw_version_str
c_func
(paren
r_struct
id|scsi_qla_host
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_cmd_timeout
c_func
(paren
id|srb_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_queuecommand
c_func
(paren
r_struct
id|scsi_cmnd
op_star
comma
r_void
(paren
op_star
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|__qla2x00_suspend_lun
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|os_lun_t
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_done
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_next
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_flush_failover_q
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|os_lun_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_reset_lun_fo_counts
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|os_lun_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_check_tgt_status
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_check_port_status
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|fc_port_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_extend_timeout
c_func
(paren
r_struct
id|scsi_cmnd
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
id|srb_t
op_star
id|qla2x00_get_new_sp
(paren
id|scsi_qla_host_t
op_star
id|ha
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_mark_device_lost
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|fc_port_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_mark_all_devices_lost
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_get_prop_xstr
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_char
op_star
comma
r_uint8
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_abort_queues
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint8
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_blink_led
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_down_timeout
c_func
(paren
r_struct
id|semaphore
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Global Function Prototypes in qla_iocb.c source file.&n; */
r_extern
id|request_t
op_star
id|qla2x00_req_pkt
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
id|request_t
op_star
id|qla2x00_ms_req_pkt
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|srb_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_isp_cmd
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_uint16
id|qla2x00_calc_iocbs_32
c_func
(paren
r_uint16
)paren
suffix:semicolon
r_extern
r_uint16
id|qla2x00_calc_iocbs_64
c_func
(paren
r_uint16
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_build_scsi_iocbs_32
c_func
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
r_extern
r_void
id|qla2x00_build_scsi_iocbs_64
c_func
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
r_extern
r_int
id|qla2x00_start_scsi
c_func
(paren
id|srb_t
op_star
id|sp
)paren
suffix:semicolon
r_int
id|qla2x00_marker
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
comma
r_uint16
comma
r_uint8
)paren
suffix:semicolon
r_int
id|__qla2x00_marker
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
comma
r_uint16
comma
r_uint8
)paren
suffix:semicolon
multiline_comment|/*&n; * Global Function Prototypes in qla_mbx.c source file.&n; */
r_extern
r_int
id|qla2x00_mailbox_command
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|mbx_cmd_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_load_ram
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|dma_addr_t
comma
r_uint16
comma
r_uint16
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_load_ram_ext
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|dma_addr_t
comma
r_uint32
comma
r_uint16
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_execute_fw
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_get_fw_version
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
op_star
comma
r_uint16
op_star
comma
r_uint16
op_star
comma
r_uint16
op_star
comma
r_uint32
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_get_fw_options
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_set_fw_options
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_read_ram_word
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_write_ram_word
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
comma
r_uint16
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_write_ram_word_ext
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint32
comma
r_uint16
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_mbx_reg_test
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_verify_checksum
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_issue_iocb
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_void
op_star
comma
id|dma_addr_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_abort_command
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|srb_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_abort_device
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
comma
r_uint16
)paren
suffix:semicolon
macro_line|#if USE_ABORT_TGT
r_extern
r_int
id|qla2x00_abort_target
c_func
(paren
id|fc_port_t
op_star
id|fcport
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|qla2x00_target_reset
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
comma
r_uint16
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_get_adapter_id
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
op_star
comma
r_uint8
op_star
comma
r_uint8
op_star
comma
r_uint8
op_star
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_get_retry_cnt
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint8
op_star
comma
r_uint8
op_star
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_init_firmware
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_get_port_database
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|fc_port_t
op_star
comma
r_uint8
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_get_firmware_state
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_get_port_name
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
comma
r_uint8
op_star
comma
r_uint8
)paren
suffix:semicolon
r_extern
r_uint8
id|qla2x00_get_link_status
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
comma
id|link_stat_t
op_star
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_lip_reset
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_send_sns
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|dma_addr_t
comma
r_uint16
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_login_fabric
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
comma
r_uint8
comma
r_uint8
comma
r_uint8
comma
r_uint16
op_star
comma
r_uint8
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_login_local_device
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
comma
r_uint16
op_star
comma
r_uint8
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_fabric_logout
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_uint16
id|loop_id
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_full_login_lip
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_get_id_list
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_void
op_star
comma
id|dma_addr_t
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_lun_reset
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
comma
r_uint16
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_send_rnid_mbx
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
comma
r_uint8
comma
id|dma_addr_t
comma
r_int
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_set_rnid_params_mbx
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|dma_addr_t
comma
r_int
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_get_rnid_params_mbx
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|dma_addr_t
comma
r_int
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_get_resource_cnts
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint16
op_star
comma
r_uint16
op_star
comma
r_uint16
op_star
comma
r_uint16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_get_fcal_position_map
c_func
(paren
id|scsi_qla_host_t
op_star
id|ha
comma
r_char
op_star
id|pos_map
)paren
suffix:semicolon
multiline_comment|/*&n; * Global Function Prototypes in qla_isr.c source file.&n; */
r_extern
id|irqreturn_t
id|qla2100_intr_handler
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
r_extern
id|irqreturn_t
id|qla2300_intr_handler
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
r_extern
r_void
id|qla2x00_process_response_queue
c_func
(paren
r_struct
id|scsi_qla_host
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Global Function Prototypes in qla_sup.c source file.&n; */
r_extern
r_void
id|qla2x00_lock_nvram_access
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_unlock_nvram_access
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_uint16
id|qla2x00_get_nvram_word
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint32
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_write_nvram_word
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint32
comma
r_uint16
)paren
suffix:semicolon
multiline_comment|/*&n; * Global Function Prototypes in qla_dbg.c source file.&n; */
r_extern
r_void
id|qla2100_fw_dump
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|qla2300_fw_dump
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|qla2100_ascii_fw_dump
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|qla2300_ascii_fw_dump
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_dump_regs
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_dump_buffer
c_func
(paren
r_uint8
op_star
comma
r_uint32
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_print_scsi_cmd
c_func
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Global Function Prototypes in qla_gs.c source file.&n; */
r_extern
r_int
id|qla2x00_ga_nxt
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|fc_port_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_gid_pt
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|sw_info_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_gpn_id
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|sw_info_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_gnn_id
c_func
(paren
id|scsi_qla_host_t
op_star
comma
id|sw_info_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_rft_id
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_rff_id
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_rnn_id
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_rsnn_nn
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Global Function Prototypes in qla_rscn.c source file.&n; */
r_extern
id|fc_port_t
op_star
id|qla2x00_alloc_rscn_fcport
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|qla2x00_handle_port_rscn
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_uint32
comma
id|fc_port_t
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_process_iodesc
c_func
(paren
id|scsi_qla_host_t
op_star
comma
r_struct
id|mbx_entry
op_star
)paren
suffix:semicolon
r_extern
r_void
id|qla2x00_cancel_io_descriptors
c_func
(paren
id|scsi_qla_host_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Global Function Prototypes in qla_xioctl.c source file.&n; */
DECL|macro|qla2x00_enqueue_aen
mdefine_line|#define qla2x00_enqueue_aen(ha, cmd, mode)&t;do { } while (0)
DECL|macro|qla2x00_alloc_ioctl_mem
mdefine_line|#define qla2x00_alloc_ioctl_mem(ha)&t;&t;(0)
DECL|macro|qla2x00_free_ioctl_mem
mdefine_line|#define qla2x00_free_ioctl_mem(ha)&t;&t;do { } while (0)
macro_line|#endif /* _QLA_GBL_H */
eof
