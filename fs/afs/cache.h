multiline_comment|/* cache.h: AFS local cache management interface&n; *&n; * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef _LINUX_AFS_CACHE_H
DECL|macro|_LINUX_AFS_CACHE_H
mdefine_line|#define _LINUX_AFS_CACHE_H
DECL|macro|AFS_CACHING_SUPPORT
macro_line|#undef AFS_CACHING_SUPPORT
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#ifdef AFS_CACHING_SUPPORT
macro_line|#include &lt;linux/cachefs.h&gt;
macro_line|#endif
macro_line|#include &quot;types.h&quot;
macro_line|#ifdef __KERNEL__
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_AFS_CACHE_H */
eof
