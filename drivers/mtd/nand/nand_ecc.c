multiline_comment|/*&n; *  drivers/mtd/nand_ecc.c&n; *&n; *  Copyright (C) 2000 Steven J. Hill (sjhill@cotw.com)&n; *                     Toshiba America Electronics Components, Inc.&n; *&n; * $Id: nand_ecc.c,v 1.6 2001/06/28 10:52:26 dwmw2 Exp $&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This file contains an ECC algorithm from Toshiba that detects and&n; * corrects 1 bit errors in a 256 byte block of data.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/*&n; * Pre-calculated 256-way 1 byte column parity&n; */
DECL|variable|nand_ecc_precalc_table
r_static
r_const
id|u_char
id|nand_ecc_precalc_table
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x55
comma
l_int|0x56
comma
l_int|0x03
comma
l_int|0x59
comma
l_int|0x0c
comma
l_int|0x0f
comma
l_int|0x5a
comma
l_int|0x5a
comma
l_int|0x0f
comma
l_int|0x0c
comma
l_int|0x59
comma
l_int|0x03
comma
l_int|0x56
comma
l_int|0x55
comma
l_int|0x00
comma
l_int|0x65
comma
l_int|0x30
comma
l_int|0x33
comma
l_int|0x66
comma
l_int|0x3c
comma
l_int|0x69
comma
l_int|0x6a
comma
l_int|0x3f
comma
l_int|0x3f
comma
l_int|0x6a
comma
l_int|0x69
comma
l_int|0x3c
comma
l_int|0x66
comma
l_int|0x33
comma
l_int|0x30
comma
l_int|0x65
comma
l_int|0x66
comma
l_int|0x33
comma
l_int|0x30
comma
l_int|0x65
comma
l_int|0x3f
comma
l_int|0x6a
comma
l_int|0x69
comma
l_int|0x3c
comma
l_int|0x3c
comma
l_int|0x69
comma
l_int|0x6a
comma
l_int|0x3f
comma
l_int|0x65
comma
l_int|0x30
comma
l_int|0x33
comma
l_int|0x66
comma
l_int|0x03
comma
l_int|0x56
comma
l_int|0x55
comma
l_int|0x00
comma
l_int|0x5a
comma
l_int|0x0f
comma
l_int|0x0c
comma
l_int|0x59
comma
l_int|0x59
comma
l_int|0x0c
comma
l_int|0x0f
comma
l_int|0x5a
comma
l_int|0x00
comma
l_int|0x55
comma
l_int|0x56
comma
l_int|0x03
comma
l_int|0x69
comma
l_int|0x3c
comma
l_int|0x3f
comma
l_int|0x6a
comma
l_int|0x30
comma
l_int|0x65
comma
l_int|0x66
comma
l_int|0x33
comma
l_int|0x33
comma
l_int|0x66
comma
l_int|0x65
comma
l_int|0x30
comma
l_int|0x6a
comma
l_int|0x3f
comma
l_int|0x3c
comma
l_int|0x69
comma
l_int|0x0c
comma
l_int|0x59
comma
l_int|0x5a
comma
l_int|0x0f
comma
l_int|0x55
comma
l_int|0x00
comma
l_int|0x03
comma
l_int|0x56
comma
l_int|0x56
comma
l_int|0x03
comma
l_int|0x00
comma
l_int|0x55
comma
l_int|0x0f
comma
l_int|0x5a
comma
l_int|0x59
comma
l_int|0x0c
comma
l_int|0x0f
comma
l_int|0x5a
comma
l_int|0x59
comma
l_int|0x0c
comma
l_int|0x56
comma
l_int|0x03
comma
l_int|0x00
comma
l_int|0x55
comma
l_int|0x55
comma
l_int|0x00
comma
l_int|0x03
comma
l_int|0x56
comma
l_int|0x0c
comma
l_int|0x59
comma
l_int|0x5a
comma
l_int|0x0f
comma
l_int|0x6a
comma
l_int|0x3f
comma
l_int|0x3c
comma
l_int|0x69
comma
l_int|0x33
comma
l_int|0x66
comma
l_int|0x65
comma
l_int|0x30
comma
l_int|0x30
comma
l_int|0x65
comma
l_int|0x66
comma
l_int|0x33
comma
l_int|0x69
comma
l_int|0x3c
comma
l_int|0x3f
comma
l_int|0x6a
comma
l_int|0x6a
comma
l_int|0x3f
comma
l_int|0x3c
comma
l_int|0x69
comma
l_int|0x33
comma
l_int|0x66
comma
l_int|0x65
comma
l_int|0x30
comma
l_int|0x30
comma
l_int|0x65
comma
l_int|0x66
comma
l_int|0x33
comma
l_int|0x69
comma
l_int|0x3c
comma
l_int|0x3f
comma
l_int|0x6a
comma
l_int|0x0f
comma
l_int|0x5a
comma
l_int|0x59
comma
l_int|0x0c
comma
l_int|0x56
comma
l_int|0x03
comma
l_int|0x00
comma
l_int|0x55
comma
l_int|0x55
comma
l_int|0x00
comma
l_int|0x03
comma
l_int|0x56
comma
l_int|0x0c
comma
l_int|0x59
comma
l_int|0x5a
comma
l_int|0x0f
comma
l_int|0x0c
comma
l_int|0x59
comma
l_int|0x5a
comma
l_int|0x0f
comma
l_int|0x55
comma
l_int|0x00
comma
l_int|0x03
comma
l_int|0x56
comma
l_int|0x56
comma
l_int|0x03
comma
l_int|0x00
comma
l_int|0x55
comma
l_int|0x0f
comma
l_int|0x5a
comma
l_int|0x59
comma
l_int|0x0c
comma
l_int|0x69
comma
l_int|0x3c
comma
l_int|0x3f
comma
l_int|0x6a
comma
l_int|0x30
comma
l_int|0x65
comma
l_int|0x66
comma
l_int|0x33
comma
l_int|0x33
comma
l_int|0x66
comma
l_int|0x65
comma
l_int|0x30
comma
l_int|0x6a
comma
l_int|0x3f
comma
l_int|0x3c
comma
l_int|0x69
comma
l_int|0x03
comma
l_int|0x56
comma
l_int|0x55
comma
l_int|0x00
comma
l_int|0x5a
comma
l_int|0x0f
comma
l_int|0x0c
comma
l_int|0x59
comma
l_int|0x59
comma
l_int|0x0c
comma
l_int|0x0f
comma
l_int|0x5a
comma
l_int|0x00
comma
l_int|0x55
comma
l_int|0x56
comma
l_int|0x03
comma
l_int|0x66
comma
l_int|0x33
comma
l_int|0x30
comma
l_int|0x65
comma
l_int|0x3f
comma
l_int|0x6a
comma
l_int|0x69
comma
l_int|0x3c
comma
l_int|0x3c
comma
l_int|0x69
comma
l_int|0x6a
comma
l_int|0x3f
comma
l_int|0x65
comma
l_int|0x30
comma
l_int|0x33
comma
l_int|0x66
comma
l_int|0x65
comma
l_int|0x30
comma
l_int|0x33
comma
l_int|0x66
comma
l_int|0x3c
comma
l_int|0x69
comma
l_int|0x6a
comma
l_int|0x3f
comma
l_int|0x3f
comma
l_int|0x6a
comma
l_int|0x69
comma
l_int|0x3c
comma
l_int|0x66
comma
l_int|0x33
comma
l_int|0x30
comma
l_int|0x65
comma
l_int|0x00
comma
l_int|0x55
comma
l_int|0x56
comma
l_int|0x03
comma
l_int|0x59
comma
l_int|0x0c
comma
l_int|0x0f
comma
l_int|0x5a
comma
l_int|0x5a
comma
l_int|0x0f
comma
l_int|0x0c
comma
l_int|0x59
comma
l_int|0x03
comma
l_int|0x56
comma
l_int|0x55
comma
l_int|0x00
)brace
suffix:semicolon
multiline_comment|/*&n; * Creates non-inverted ECC code from line parity&n; */
DECL|function|nand_trans_result
r_static
r_void
id|nand_trans_result
c_func
(paren
id|u_char
id|reg2
comma
id|u_char
id|reg3
comma
id|u_char
op_star
id|ecc_code
)paren
(brace
id|u_char
id|a
comma
id|b
comma
id|i
comma
id|tmp1
comma
id|tmp2
suffix:semicolon
multiline_comment|/* Initialize variables */
id|a
op_assign
id|b
op_assign
l_int|0x80
suffix:semicolon
id|tmp1
op_assign
id|tmp2
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Calculate first ECC byte */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|reg3
op_amp
id|a
)paren
multiline_comment|/* LP15,13,11,9 --&gt; ecc_code[0] */
id|tmp1
op_or_assign
id|b
suffix:semicolon
id|b
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|reg2
op_amp
id|a
)paren
multiline_comment|/* LP14,12,10,8 --&gt; ecc_code[0] */
id|tmp1
op_or_assign
id|b
suffix:semicolon
id|b
op_rshift_assign
l_int|1
suffix:semicolon
id|a
op_rshift_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Calculate second ECC byte */
id|b
op_assign
l_int|0x80
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|reg3
op_amp
id|a
)paren
multiline_comment|/* LP7,5,3,1 --&gt; ecc_code[1] */
id|tmp2
op_or_assign
id|b
suffix:semicolon
id|b
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|reg2
op_amp
id|a
)paren
multiline_comment|/* LP6,4,2,0 --&gt; ecc_code[1] */
id|tmp2
op_or_assign
id|b
suffix:semicolon
id|b
op_rshift_assign
l_int|1
suffix:semicolon
id|a
op_rshift_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Store two of the ECC bytes */
id|ecc_code
(braket
l_int|0
)braket
op_assign
id|tmp1
suffix:semicolon
id|ecc_code
(braket
l_int|1
)braket
op_assign
id|tmp2
suffix:semicolon
)brace
multiline_comment|/*&n; * Calculate 3 byte ECC code for 256 byte block&n; */
DECL|function|nand_calculate_ecc
r_void
id|nand_calculate_ecc
(paren
r_const
id|u_char
op_star
id|dat
comma
id|u_char
op_star
id|ecc_code
)paren
(brace
id|u_char
id|idx
comma
id|reg1
comma
id|reg2
comma
id|reg3
suffix:semicolon
r_int
id|j
suffix:semicolon
multiline_comment|/* Initialize variables */
id|reg1
op_assign
id|reg2
op_assign
id|reg3
op_assign
l_int|0
suffix:semicolon
id|ecc_code
(braket
l_int|0
)braket
op_assign
id|ecc_code
(braket
l_int|1
)braket
op_assign
id|ecc_code
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Build up column parity */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|256
suffix:semicolon
id|j
op_increment
)paren
(brace
multiline_comment|/* Get CP0 - CP5 from table */
id|idx
op_assign
id|nand_ecc_precalc_table
(braket
id|dat
(braket
id|j
)braket
)braket
suffix:semicolon
id|reg1
op_xor_assign
(paren
id|idx
op_amp
l_int|0x3f
)paren
suffix:semicolon
multiline_comment|/* All bit XOR = 1 ? */
r_if
c_cond
(paren
id|idx
op_amp
l_int|0x40
)paren
(brace
id|reg3
op_xor_assign
(paren
id|u_char
)paren
id|j
suffix:semicolon
id|reg2
op_xor_assign
op_complement
(paren
(paren
id|u_char
)paren
id|j
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Create non-inverted ECC code from line parity */
id|nand_trans_result
c_func
(paren
id|reg2
comma
id|reg3
comma
id|ecc_code
)paren
suffix:semicolon
multiline_comment|/* Calculate final ECC code */
id|ecc_code
(braket
l_int|0
)braket
op_assign
op_complement
id|ecc_code
(braket
l_int|0
)braket
suffix:semicolon
id|ecc_code
(braket
l_int|1
)braket
op_assign
op_complement
id|ecc_code
(braket
l_int|1
)braket
suffix:semicolon
id|ecc_code
(braket
l_int|2
)braket
op_assign
(paren
(paren
op_complement
id|reg1
)paren
op_lshift
l_int|2
)paren
op_or
l_int|0x03
suffix:semicolon
)brace
multiline_comment|/*&n; * Detect and correct a 1 bit error for 256 byte block&n; */
DECL|function|nand_correct_data
r_int
id|nand_correct_data
(paren
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
(brace
id|u_char
id|a
comma
id|b
comma
id|c
comma
id|d1
comma
id|d2
comma
id|d3
comma
id|add
comma
id|bit
comma
id|i
suffix:semicolon
multiline_comment|/* Do error detection */
id|d1
op_assign
id|calc_ecc
(braket
l_int|0
)braket
op_xor
id|read_ecc
(braket
l_int|0
)braket
suffix:semicolon
id|d2
op_assign
id|calc_ecc
(braket
l_int|1
)braket
op_xor
id|read_ecc
(braket
l_int|1
)braket
suffix:semicolon
id|d3
op_assign
id|calc_ecc
(braket
l_int|2
)braket
op_xor
id|read_ecc
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|d1
op_or
id|d2
op_or
id|d3
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* No errors */
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|a
op_assign
(paren
id|d1
op_xor
(paren
id|d1
op_rshift
l_int|1
)paren
)paren
op_amp
l_int|0x55
suffix:semicolon
id|b
op_assign
(paren
id|d2
op_xor
(paren
id|d2
op_rshift
l_int|1
)paren
)paren
op_amp
l_int|0x55
suffix:semicolon
id|c
op_assign
(paren
id|d3
op_xor
(paren
id|d3
op_rshift
l_int|1
)paren
)paren
op_amp
l_int|0x54
suffix:semicolon
multiline_comment|/* Found and will correct single bit error in the data */
r_if
c_cond
(paren
(paren
id|a
op_eq
l_int|0x55
)paren
op_logical_and
(paren
id|b
op_eq
l_int|0x55
)paren
op_logical_and
(paren
id|c
op_eq
l_int|0x54
)paren
)paren
(brace
id|c
op_assign
l_int|0x80
suffix:semicolon
id|add
op_assign
l_int|0
suffix:semicolon
id|a
op_assign
l_int|0x80
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|d1
op_amp
id|c
)paren
id|add
op_or_assign
id|a
suffix:semicolon
id|c
op_rshift_assign
l_int|2
suffix:semicolon
id|a
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|c
op_assign
l_int|0x80
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|d2
op_amp
id|c
)paren
id|add
op_or_assign
id|a
suffix:semicolon
id|c
op_rshift_assign
l_int|2
suffix:semicolon
id|a
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|bit
op_assign
l_int|0
suffix:semicolon
id|b
op_assign
l_int|0x04
suffix:semicolon
id|c
op_assign
l_int|0x80
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|d3
op_amp
id|c
)paren
id|bit
op_or_assign
id|b
suffix:semicolon
id|c
op_rshift_assign
l_int|2
suffix:semicolon
id|b
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|b
op_assign
l_int|0x01
suffix:semicolon
id|a
op_assign
id|dat
(braket
id|add
)braket
suffix:semicolon
id|a
op_xor_assign
(paren
id|b
op_lshift
id|bit
)paren
suffix:semicolon
id|dat
(braket
id|add
)braket
op_assign
id|a
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|d1
)paren
(brace
r_if
c_cond
(paren
id|d1
op_amp
l_int|0x01
)paren
op_increment
id|i
suffix:semicolon
id|d1
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|d2
)paren
(brace
r_if
c_cond
(paren
id|d2
op_amp
l_int|0x01
)paren
op_increment
id|i
suffix:semicolon
id|d2
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|d3
)paren
(brace
r_if
c_cond
(paren
id|d3
op_amp
l_int|0x01
)paren
op_increment
id|i
suffix:semicolon
id|d3
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|1
)paren
(brace
multiline_comment|/* ECC Code Error Correction */
id|read_ecc
(braket
l_int|0
)braket
op_assign
id|calc_ecc
(braket
l_int|0
)braket
suffix:semicolon
id|read_ecc
(braket
l_int|1
)braket
op_assign
id|calc_ecc
(braket
l_int|1
)braket
suffix:semicolon
id|read_ecc
(braket
l_int|2
)braket
op_assign
id|calc_ecc
(braket
l_int|2
)braket
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Uncorrectable Error */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Should never happen */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|variable|nand_calculate_ecc
id|EXPORT_SYMBOL
c_func
(paren
id|nand_calculate_ecc
)paren
suffix:semicolon
DECL|variable|nand_correct_data
id|EXPORT_SYMBOL
c_func
(paren
id|nand_correct_data
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
