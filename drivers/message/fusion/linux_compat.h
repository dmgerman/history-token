multiline_comment|/* drivers/message/fusion/linux_compat.h */
macro_line|#ifndef FUSION_LINUX_COMPAT_H
DECL|macro|FUSION_LINUX_COMPAT_H
mdefine_line|#define FUSION_LINUX_COMPAT_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#if (LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,6,6))
DECL|function|scsi_device_online
r_static
r_int
r_inline
id|scsi_device_online
c_func
(paren
r_struct
id|scsi_device
op_star
id|sdev
)paren
(brace
r_return
id|sdev-&gt;online
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*}-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#endif /* _LINUX_COMPAT_H */
eof
