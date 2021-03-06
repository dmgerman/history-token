multiline_comment|/* &n; * &n; * linux/drivers/s390/scsi/zfcp_ext.h&n; * &n; * FCP adapter driver for IBM eServer zSeries &n; * &n; * (C) Copyright IBM Corp. 2002, 2004&n; *&n; * Author(s): Martin Peschke &lt;mpeschke@de.ibm.com&gt; &n; *            Raimund Schroeder &lt;raimund.schroeder@de.ibm.com&gt; &n; *            Aron Zeh&n; *            Wolfgang Taphorn&n; *            Stefan Bader &lt;stefan.bader@de.ibm.com&gt; &n; *            Heiko Carstens &lt;heiko.carstens@de.ibm.com&gt; &n; *            Andreas Herrmann &lt;aherrman@de.ibm.com&gt;&n; * &n; * This program is free software; you can redistribute it and/or modify &n; * it under the terms of the GNU General Public License as published by &n; * the Free Software Foundation; either version 2, or (at your option) &n; * any later version. &n; * &n; * This program is distributed in the hope that it will be useful, &n; * but WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the &n; * GNU General Public License for more details. &n; * &n; * You should have received a copy of the GNU General Public License &n; * along with this program; if not, write to the Free Software &n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; */
macro_line|#ifndef ZFCP_EXT_H
DECL|macro|ZFCP_EXT_H
mdefine_line|#define ZFCP_EXT_H
DECL|macro|ZFCP_EXT_REVISION
mdefine_line|#define ZFCP_EXT_REVISION &quot;$Revision: 1.62 $&quot;
macro_line|#include &quot;zfcp_def.h&quot;
r_extern
r_struct
id|zfcp_data
id|zfcp_data
suffix:semicolon
multiline_comment|/******************************** SYSFS  *************************************/
r_extern
r_int
id|zfcp_sysfs_driver_create_files
c_func
(paren
r_struct
id|device_driver
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_sysfs_driver_remove_files
c_func
(paren
r_struct
id|device_driver
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_sysfs_adapter_create_files
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_sysfs_adapter_remove_files
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_sysfs_port_create_files
c_func
(paren
r_struct
id|device
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_sysfs_port_remove_files
c_func
(paren
r_struct
id|device
op_star
comma
id|u32
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_sysfs_unit_create_files
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_sysfs_unit_remove_files
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_sysfs_port_release
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_sysfs_unit_release
c_func
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/**************************** CONFIGURATION  *********************************/
r_extern
r_struct
id|zfcp_unit
op_star
id|zfcp_get_unit_by_lun
c_func
(paren
r_struct
id|zfcp_port
op_star
comma
id|fcp_lun_t
)paren
suffix:semicolon
r_extern
r_struct
id|zfcp_port
op_star
id|zfcp_get_port_by_wwpn
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
id|wwn_t
)paren
suffix:semicolon
r_extern
r_struct
id|zfcp_port
op_star
id|zfcp_get_port_by_did
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
id|u32
)paren
suffix:semicolon
r_struct
id|zfcp_adapter
op_star
id|zfcp_get_adapter_by_busid
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|zfcp_adapter
op_star
id|zfcp_adapter_enqueue
c_func
(paren
r_struct
id|ccw_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_adapter_debug_register
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_adapter_dequeue
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_adapter_debug_unregister
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|zfcp_port
op_star
id|zfcp_port_enqueue
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
id|wwn_t
comma
id|u32
comma
id|u32
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_port_dequeue
c_func
(paren
r_struct
id|zfcp_port
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|zfcp_unit
op_star
id|zfcp_unit_enqueue
c_func
(paren
r_struct
id|zfcp_port
op_star
comma
id|fcp_lun_t
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_unit_dequeue
c_func
(paren
r_struct
id|zfcp_unit
op_star
)paren
suffix:semicolon
multiline_comment|/******************************* S/390 IO ************************************/
r_extern
r_int
id|zfcp_ccw_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_ccw_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_qdio_zero_sbals
c_func
(paren
r_struct
id|qdio_buffer
op_star
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_qdio_allocate
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_qdio_allocate_queues
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_qdio_free_queues
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_qdio_determine_pci
c_func
(paren
r_struct
id|zfcp_qdio_queue
op_star
comma
r_struct
id|zfcp_fsf_req
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_qdio_reqid_check
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_volatile
r_struct
id|qdio_buffer_element
op_star
id|zfcp_qdio_sbale_req
(paren
r_struct
id|zfcp_fsf_req
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_volatile
r_struct
id|qdio_buffer_element
op_star
id|zfcp_qdio_sbale_curr
(paren
r_struct
id|zfcp_fsf_req
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_qdio_sbals_from_sg
(paren
r_struct
id|zfcp_fsf_req
op_star
comma
r_int
r_int
comma
r_struct
id|scatterlist
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_qdio_sbals_from_scsicmnd
(paren
r_struct
id|zfcp_fsf_req
op_star
comma
r_int
r_int
comma
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/******************************** FSF ****************************************/
r_extern
r_int
id|zfcp_fsf_open_port
c_func
(paren
r_struct
id|zfcp_erp_action
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_close_port
c_func
(paren
r_struct
id|zfcp_erp_action
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_close_physical_port
c_func
(paren
r_struct
id|zfcp_erp_action
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_open_unit
c_func
(paren
r_struct
id|zfcp_erp_action
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_close_unit
c_func
(paren
r_struct
id|zfcp_erp_action
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_exchange_config_data
c_func
(paren
r_struct
id|zfcp_erp_action
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_exchange_port_data
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
r_struct
id|fsf_qtcb_bottom_port
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_control_file
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
r_struct
id|zfcp_fsf_req
op_star
op_star
comma
id|u32
comma
id|u32
comma
r_struct
id|zfcp_sg_list
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_fsf_request_timeout_handler
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_fsf_scsi_er_timeout_handler
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_req_dismiss_all
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_status_read
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_req_create
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
id|u32
comma
r_int
comma
id|mempool_t
op_star
comma
r_int
r_int
op_star
comma
r_struct
id|zfcp_fsf_req
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_send_ct
c_func
(paren
r_struct
id|zfcp_send_ct
op_star
comma
id|mempool_t
op_star
comma
r_struct
id|zfcp_erp_action
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_send_els
c_func
(paren
r_struct
id|zfcp_send_els
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_req_wait_and_cleanup
c_func
(paren
r_struct
id|zfcp_fsf_req
op_star
comma
r_int
comma
id|u32
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_send_fcp_command_task
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
r_struct
id|zfcp_unit
op_star
comma
r_struct
id|scsi_cmnd
op_star
comma
r_struct
id|timer_list
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_fsf_req_complete
c_func
(paren
r_struct
id|zfcp_fsf_req
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_fsf_incoming_els
c_func
(paren
r_struct
id|zfcp_fsf_req
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_fsf_req_cleanup
c_func
(paren
r_struct
id|zfcp_fsf_req
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|zfcp_fsf_req
op_star
id|zfcp_fsf_send_fcp_command_task_management
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
r_struct
id|zfcp_unit
op_star
comma
id|u8
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|zfcp_fsf_req
op_star
id|zfcp_fsf_abort_fcp_command
c_func
(paren
r_int
r_int
comma
r_struct
id|zfcp_adapter
op_star
comma
r_struct
id|zfcp_unit
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/******************************* FC/FCP **************************************/
r_extern
r_int
id|zfcp_nameserver_enqueue
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_ns_gid_pn_request
c_func
(paren
r_struct
id|zfcp_erp_action
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_check_ct_response
c_func
(paren
r_struct
id|ct_hdr
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_handle_els_rjt
c_func
(paren
id|u32
comma
r_struct
id|zfcp_ls_rjt_par
op_star
)paren
suffix:semicolon
multiline_comment|/******************************* SCSI ****************************************/
r_extern
r_int
id|zfcp_adapter_scsi_register
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_adapter_scsi_unregister
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_set_fcp_dl
c_func
(paren
r_struct
id|fcp_cmnd_iu
op_star
comma
id|fcp_dl_t
)paren
suffix:semicolon
r_extern
r_char
op_star
id|zfcp_get_fcp_rsp_info_ptr
c_func
(paren
r_struct
id|fcp_rsp_iu
op_star
)paren
suffix:semicolon
r_extern
r_void
id|set_host_byte
c_func
(paren
id|u32
op_star
comma
r_char
)paren
suffix:semicolon
r_extern
r_void
id|set_driver_byte
c_func
(paren
id|u32
op_star
comma
r_char
)paren
suffix:semicolon
r_extern
r_char
op_star
id|zfcp_get_fcp_sns_info_ptr
c_func
(paren
r_struct
id|fcp_rsp_iu
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_fsf_start_scsi_er_timer
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
id|fcp_dl_t
id|zfcp_get_fcp_dl
c_func
(paren
r_struct
id|fcp_cmnd_iu
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_scsi_command_async
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
r_struct
id|zfcp_unit
op_star
comma
r_struct
id|scsi_cmnd
op_star
comma
r_struct
id|timer_list
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_scsi_command_sync
c_func
(paren
r_struct
id|zfcp_unit
op_star
comma
r_struct
id|scsi_cmnd
op_star
comma
r_struct
id|timer_list
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|scsi_transport_template
op_star
id|zfcp_transport_template
suffix:semicolon
r_extern
r_struct
id|fc_function_template
id|zfcp_transport_functions
suffix:semicolon
multiline_comment|/******************************** ERP ****************************************/
r_extern
r_void
id|zfcp_erp_modify_adapter_status
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
id|u32
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_erp_adapter_reopen
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_erp_adapter_shutdown
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_erp_adapter_failed
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_erp_modify_port_status
c_func
(paren
r_struct
id|zfcp_port
op_star
comma
id|u32
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_erp_port_reopen
c_func
(paren
r_struct
id|zfcp_port
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_erp_port_shutdown
c_func
(paren
r_struct
id|zfcp_port
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_erp_port_forced_reopen
c_func
(paren
r_struct
id|zfcp_port
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_erp_port_failed
c_func
(paren
r_struct
id|zfcp_port
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_erp_port_reopen_all
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_erp_modify_unit_status
c_func
(paren
r_struct
id|zfcp_unit
op_star
comma
id|u32
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_erp_unit_reopen
c_func
(paren
r_struct
id|zfcp_unit
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_erp_unit_shutdown
c_func
(paren
r_struct
id|zfcp_unit
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_erp_unit_failed
c_func
(paren
r_struct
id|zfcp_unit
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_erp_thread_setup
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_erp_thread_kill
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_erp_wait
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_erp_async_handler
c_func
(paren
r_struct
id|zfcp_erp_action
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|zfcp_test_link
c_func
(paren
r_struct
id|zfcp_port
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_erp_port_access_denied
c_func
(paren
r_struct
id|zfcp_port
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_erp_unit_access_denied
c_func
(paren
r_struct
id|zfcp_unit
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_erp_adapter_access_changed
c_func
(paren
r_struct
id|zfcp_adapter
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_erp_port_access_changed
c_func
(paren
r_struct
id|zfcp_port
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_erp_unit_access_changed
c_func
(paren
r_struct
id|zfcp_unit
op_star
)paren
suffix:semicolon
multiline_comment|/******************************** AUX ****************************************/
r_extern
r_void
id|zfcp_cmd_dbf_event_fsf
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|zfcp_fsf_req
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_cmd_dbf_event_scsi
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
r_extern
r_void
id|zfcp_in_els_dbf_event
c_func
(paren
r_struct
id|zfcp_adapter
op_star
comma
r_const
r_char
op_star
comma
r_struct
id|fsf_status_read_buffer
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif&t;/* ZFCP_EXT_H */
eof
