multiline_comment|/*&n; * We should not even be trying to compile this if we are not doing&n; * a module.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &lt;scsi/scsi_ioctl.h&gt;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;sd.h&quot;
macro_line|#include &lt;scsi/scsicam.h&gt;
multiline_comment|/*&n; * This source file contains the symbol table used by scsi loadable&n; * modules.&n; */
DECL|variable|scsi_register_device
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_register_device
)paren
suffix:semicolon
DECL|variable|scsi_unregister_device
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_unregister_device
)paren
suffix:semicolon
DECL|variable|scsi_register_host
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_register_host
)paren
suffix:semicolon
DECL|variable|scsi_unregister_host
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_unregister_host
)paren
suffix:semicolon
DECL|variable|scsi_register
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_register
)paren
suffix:semicolon
DECL|variable|scsi_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_unregister
)paren
suffix:semicolon
DECL|variable|scsicam_bios_param
id|EXPORT_SYMBOL
c_func
(paren
id|scsicam_bios_param
)paren
suffix:semicolon
DECL|variable|scsi_partsize
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_partsize
)paren
suffix:semicolon
DECL|variable|scsi_bios_ptable
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_bios_ptable
)paren
suffix:semicolon
DECL|variable|scsi_allocate_device
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_allocate_device
)paren
suffix:semicolon
DECL|variable|scsi_do_cmd
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_do_cmd
)paren
suffix:semicolon
DECL|variable|scsi_command_size
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_command_size
)paren
suffix:semicolon
DECL|variable|scsi_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_ioctl
)paren
suffix:semicolon
DECL|variable|print_command
id|EXPORT_SYMBOL
c_func
(paren
id|print_command
)paren
suffix:semicolon
DECL|variable|print_sense
id|EXPORT_SYMBOL
c_func
(paren
id|print_sense
)paren
suffix:semicolon
DECL|variable|print_req_sense
id|EXPORT_SYMBOL
c_func
(paren
id|print_req_sense
)paren
suffix:semicolon
DECL|variable|print_msg
id|EXPORT_SYMBOL
c_func
(paren
id|print_msg
)paren
suffix:semicolon
DECL|variable|print_status
id|EXPORT_SYMBOL
c_func
(paren
id|print_status
)paren
suffix:semicolon
DECL|variable|scsi_sense_key_string
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_sense_key_string
)paren
suffix:semicolon
DECL|variable|scsi_extd_sense_format
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_extd_sense_format
)paren
suffix:semicolon
DECL|variable|kernel_scsi_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_scsi_ioctl
)paren
suffix:semicolon
DECL|variable|scsi_release_command
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_release_command
)paren
suffix:semicolon
DECL|variable|print_Scsi_Cmnd
id|EXPORT_SYMBOL
c_func
(paren
id|print_Scsi_Cmnd
)paren
suffix:semicolon
DECL|variable|scsi_block_when_processing_errors
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_block_when_processing_errors
)paren
suffix:semicolon
DECL|variable|scsi_ioctl_send_command
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_ioctl_send_command
)paren
suffix:semicolon
DECL|variable|scsi_set_medium_removal
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_set_medium_removal
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SCSI_LOGGING)&t;/* { */
DECL|variable|scsi_logging_level
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_logging_level
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|scsi_allocate_request
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_allocate_request
)paren
suffix:semicolon
DECL|variable|scsi_release_request
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_release_request
)paren
suffix:semicolon
DECL|variable|scsi_wait_req
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_wait_req
)paren
suffix:semicolon
DECL|variable|scsi_do_req
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_do_req
)paren
suffix:semicolon
DECL|variable|scsi_report_bus_reset
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_report_bus_reset
)paren
suffix:semicolon
DECL|variable|scsi_block_requests
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_block_requests
)paren
suffix:semicolon
DECL|variable|scsi_unblock_requests
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_unblock_requests
)paren
suffix:semicolon
DECL|variable|scsi_adjust_queue_depth
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_adjust_queue_depth
)paren
suffix:semicolon
DECL|variable|scsi_get_host_dev
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_get_host_dev
)paren
suffix:semicolon
DECL|variable|scsi_free_host_dev
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_free_host_dev
)paren
suffix:semicolon
DECL|variable|scsi_sleep
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_sleep
)paren
suffix:semicolon
DECL|variable|proc_print_scsidevice
id|EXPORT_SYMBOL
c_func
(paren
id|proc_print_scsidevice
)paren
suffix:semicolon
DECL|variable|proc_scsi
id|EXPORT_SYMBOL
c_func
(paren
id|proc_scsi
)paren
suffix:semicolon
DECL|variable|scsi_io_completion
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_io_completion
)paren
suffix:semicolon
DECL|variable|scsi_end_request
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_end_request
)paren
suffix:semicolon
DECL|variable|scsi_register_blocked_host
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_register_blocked_host
)paren
suffix:semicolon
DECL|variable|scsi_deregister_blocked_host
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_deregister_blocked_host
)paren
suffix:semicolon
multiline_comment|/*&n; * This symbol is for the highlevel drivers (e.g. sg) only.&n; */
DECL|variable|scsi_reset_provider
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_reset_provider
)paren
suffix:semicolon
multiline_comment|/*&n; * These are here only while I debug the rest of the scsi stuff.&n; */
DECL|variable|scsi_host_get_next
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_host_get_next
)paren
suffix:semicolon
DECL|variable|scsi_host_hn_get
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_host_hn_get
)paren
suffix:semicolon
DECL|variable|scsi_host_put
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_host_put
)paren
suffix:semicolon
DECL|variable|scsi_devicelist
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_devicelist
)paren
suffix:semicolon
DECL|variable|scsi_device_types
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_device_types
)paren
suffix:semicolon
multiline_comment|/*&n; * Externalize timers so that HBAs can safely start/restart commands.&n; */
r_extern
r_void
id|scsi_add_timer
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
comma
r_void
(paren
(paren
op_star
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
)paren
suffix:semicolon
r_extern
r_int
id|scsi_delete_timer
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
DECL|variable|scsi_add_timer
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_add_timer
)paren
suffix:semicolon
DECL|variable|scsi_delete_timer
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_delete_timer
)paren
suffix:semicolon
multiline_comment|/*&n; * driverfs support for determining driver types&n; */
DECL|variable|scsi_driverfs_bus_type
id|EXPORT_SYMBOL
c_func
(paren
id|scsi_driverfs_bus_type
)paren
suffix:semicolon
eof
