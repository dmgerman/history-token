multiline_comment|/*&n; *  drivers/mtd/nand_ecc.h&n; *&n; *  Copyright (C) 2000 Steven J. Hill (sjhill@realitydiluted.com)&n; *&n; * $Id: nand_ecc.h,v 1.4 2004/06/17 02:35:02 dbrown Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This file is the header for the ECC algorithm.&n; */
macro_line|#ifndef __MTD_NAND_ECC_H__
DECL|macro|__MTD_NAND_ECC_H__
mdefine_line|#define __MTD_NAND_ECC_H__
r_struct
id|mtd_info
suffix:semicolon
multiline_comment|/*&n; * Calculate 3 byte ECC code for 256 byte block&n; */
r_int
id|nand_calculate_ecc
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
r_const
id|u_char
op_star
id|dat
comma
id|u_char
op_star
id|ecc_code
)paren
suffix:semicolon
multiline_comment|/*&n; * Detect and correct a 1 bit error for 256 byte block&n; */
r_int
id|nand_correct_data
c_func
(paren
r_struct
id|mtd_info
op_star
id|mtd
comma
id|u_char
op_star
id|dat
comma
id|u_char
op_star
id|read_ecc
comma
id|u_char
op_star
id|calc_ecc
)paren
suffix:semicolon
macro_line|#endif /* __MTD_NAND_ECC_H__ */
eof
