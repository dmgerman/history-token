multiline_comment|/*&n; * $Id: mtd-user.h,v 1.2 2004/05/05 14:44:57 dwmw2 Exp $&n; *&n; * MTD ABI header for use by user space only.&n; */
macro_line|#ifndef __MTD_USER_H__
DECL|macro|__MTD_USER_H__
mdefine_line|#define __MTD_USER_H__
macro_line|#include &lt;stdint.h&gt;
multiline_comment|/* This file is blessed for inclusion by userspace */
macro_line|#include &lt;mtd/mtd-abi.h&gt;
DECL|typedef|mtd_info_t
r_typedef
r_struct
id|mtd_info_user
id|mtd_info_t
suffix:semicolon
DECL|typedef|erase_info_t
r_typedef
r_struct
id|erase_info_user
id|erase_info_t
suffix:semicolon
DECL|typedef|region_info_t
r_typedef
r_struct
id|region_info_user
id|region_info_t
suffix:semicolon
DECL|typedef|nand_oobinfo_t
r_typedef
r_struct
id|nand_oobinfo
id|nand_oobinfo_t
suffix:semicolon
macro_line|#endif /* __MTD_USER_H__ */
eof
