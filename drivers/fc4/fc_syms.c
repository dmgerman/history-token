multiline_comment|/*&n; * We should not even be trying to compile this if we are not doing&n; * a module.&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#ifdef CONFIG_MODULES
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &quot;fcp_impl.h&quot;
DECL|variable|fcp_init
id|EXPORT_SYMBOL
c_func
(paren
id|fcp_init
)paren
suffix:semicolon
DECL|variable|fcp_release
id|EXPORT_SYMBOL
c_func
(paren
id|fcp_release
)paren
suffix:semicolon
DECL|variable|fcp_queue_empty
id|EXPORT_SYMBOL
c_func
(paren
id|fcp_queue_empty
)paren
suffix:semicolon
DECL|variable|fcp_receive_solicited
id|EXPORT_SYMBOL
c_func
(paren
id|fcp_receive_solicited
)paren
suffix:semicolon
DECL|variable|fc_channels
id|EXPORT_SYMBOL
c_func
(paren
id|fc_channels
)paren
suffix:semicolon
DECL|variable|fcp_state_change
id|EXPORT_SYMBOL
c_func
(paren
id|fcp_state_change
)paren
suffix:semicolon
DECL|variable|fc_do_plogi
id|EXPORT_SYMBOL
c_func
(paren
id|fc_do_plogi
)paren
suffix:semicolon
DECL|variable|fc_do_prli
id|EXPORT_SYMBOL
c_func
(paren
id|fc_do_prli
)paren
suffix:semicolon
multiline_comment|/* SCSI stuff */
DECL|variable|fcp_scsi_queuecommand
id|EXPORT_SYMBOL
c_func
(paren
id|fcp_scsi_queuecommand
)paren
suffix:semicolon
DECL|variable|fcp_old_abort
id|EXPORT_SYMBOL
c_func
(paren
id|fcp_old_abort
)paren
suffix:semicolon
DECL|variable|fcp_scsi_abort
id|EXPORT_SYMBOL
c_func
(paren
id|fcp_scsi_abort
)paren
suffix:semicolon
DECL|variable|fcp_scsi_dev_reset
id|EXPORT_SYMBOL
c_func
(paren
id|fcp_scsi_dev_reset
)paren
suffix:semicolon
DECL|variable|fcp_scsi_bus_reset
id|EXPORT_SYMBOL
c_func
(paren
id|fcp_scsi_bus_reset
)paren
suffix:semicolon
DECL|variable|fcp_scsi_host_reset
id|EXPORT_SYMBOL
c_func
(paren
id|fcp_scsi_host_reset
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_MODULES */
eof
