multiline_comment|/*&n; * Copyright (C) 2003 Sistina Software (UK) Limited.&n; *&n; * This file is released under the LGPL.&n; */
macro_line|#ifndef _LINUX_DM_IOCTL_H
DECL|macro|_LINUX_DM_IOCTL_H
mdefine_line|#define _LINUX_DM_IOCTL_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DM_IOCTL_V4
macro_line|#include &quot;dm-ioctl-v4.h&quot;
macro_line|#else
macro_line|#include &quot;dm-ioctl-v1.h&quot;
macro_line|#endif
macro_line|#endif
eof
