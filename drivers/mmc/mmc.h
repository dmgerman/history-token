multiline_comment|/*&n; *  linux/drivers/mmc/mmc.h&n; *&n; *  Copyright (C) 2003 Russell King, All Rights Reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _MMC_H
DECL|macro|_MMC_H
mdefine_line|#define _MMC_H
multiline_comment|/* core-internal functions */
r_void
id|mmc_init_card
c_func
(paren
r_struct
id|mmc_card
op_star
id|card
comma
r_struct
id|mmc_host
op_star
id|host
)paren
suffix:semicolon
r_int
id|mmc_register_card
c_func
(paren
r_struct
id|mmc_card
op_star
id|card
)paren
suffix:semicolon
r_void
id|mmc_remove_card
c_func
(paren
r_struct
id|mmc_card
op_star
id|card
)paren
suffix:semicolon
macro_line|#endif
eof
