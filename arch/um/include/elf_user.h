multiline_comment|/*&n; * Copyright (C) 2004 Fujitsu Siemens Computers GmbH&n; * Author: Bodo Stroesser &lt;bstroesser@fujitsu-siemens.com&gt;&n; * Licensed under the GPL&n; */
macro_line|#ifndef __ELF_USER_H__
DECL|macro|__ELF_USER_H__
mdefine_line|#define __ELF_USER_H__
multiline_comment|/* For compilation on a host that doesn&squot;t support AT_SYSINFO (Linux 2.4)  */
macro_line|#ifndef AT_SYSINFO
DECL|macro|AT_SYSINFO
mdefine_line|#define AT_SYSINFO 32
macro_line|#endif
macro_line|#ifndef AT_SYSINFO_EHDR
DECL|macro|AT_SYSINFO_EHDR
mdefine_line|#define AT_SYSINFO_EHDR 33
macro_line|#endif
macro_line|#endif
eof
