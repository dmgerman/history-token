multiline_comment|/*&n; * upcase.c - Generate the full NTFS Unicode upcase table in little endian.&n; *&t;      Part of the Linux-NTFS project.&n; *&n; * Copyright (c) 2001 Richard Russon &lt;ntfs@flatcap.org&gt;&n; * Copyright (c) 2001-2003 Anton Altaparmakov&n; *&n; * Modified for mkntfs inclusion 9 June 2001 by Anton Altaparmakov.&n; * Modified for kernel inclusion 10 September 2001 by Anton Altparmakov.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS source&n; * in the file COPYING); if not, write to the Free Software Foundation,&n; * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;ntfs.h&quot;
DECL|function|generate_default_upcase
id|ntfschar
op_star
id|generate_default_upcase
c_func
(paren
r_void
)paren
(brace
r_static
r_const
r_int
id|uc_run_table
(braket
)braket
(braket
l_int|3
)braket
op_assign
(brace
multiline_comment|/* Start, End, Add */
(brace
l_int|0x0061
comma
l_int|0x007B
comma
op_minus
l_int|32
)brace
comma
(brace
l_int|0x0451
comma
l_int|0x045D
comma
op_minus
l_int|80
)brace
comma
(brace
l_int|0x1F70
comma
l_int|0x1F72
comma
l_int|74
)brace
comma
(brace
l_int|0x00E0
comma
l_int|0x00F7
comma
op_minus
l_int|32
)brace
comma
(brace
l_int|0x045E
comma
l_int|0x0460
comma
op_minus
l_int|80
)brace
comma
(brace
l_int|0x1F72
comma
l_int|0x1F76
comma
l_int|86
)brace
comma
(brace
l_int|0x00F8
comma
l_int|0x00FF
comma
op_minus
l_int|32
)brace
comma
(brace
l_int|0x0561
comma
l_int|0x0587
comma
op_minus
l_int|48
)brace
comma
(brace
l_int|0x1F76
comma
l_int|0x1F78
comma
l_int|100
)brace
comma
(brace
l_int|0x0256
comma
l_int|0x0258
comma
op_minus
l_int|205
)brace
comma
(brace
l_int|0x1F00
comma
l_int|0x1F08
comma
l_int|8
)brace
comma
(brace
l_int|0x1F78
comma
l_int|0x1F7A
comma
l_int|128
)brace
comma
(brace
l_int|0x028A
comma
l_int|0x028C
comma
op_minus
l_int|217
)brace
comma
(brace
l_int|0x1F10
comma
l_int|0x1F16
comma
l_int|8
)brace
comma
(brace
l_int|0x1F7A
comma
l_int|0x1F7C
comma
l_int|112
)brace
comma
(brace
l_int|0x03AC
comma
l_int|0x03AD
comma
op_minus
l_int|38
)brace
comma
(brace
l_int|0x1F20
comma
l_int|0x1F28
comma
l_int|8
)brace
comma
(brace
l_int|0x1F7C
comma
l_int|0x1F7E
comma
l_int|126
)brace
comma
(brace
l_int|0x03AD
comma
l_int|0x03B0
comma
op_minus
l_int|37
)brace
comma
(brace
l_int|0x1F30
comma
l_int|0x1F38
comma
l_int|8
)brace
comma
(brace
l_int|0x1FB0
comma
l_int|0x1FB2
comma
l_int|8
)brace
comma
(brace
l_int|0x03B1
comma
l_int|0x03C2
comma
op_minus
l_int|32
)brace
comma
(brace
l_int|0x1F40
comma
l_int|0x1F46
comma
l_int|8
)brace
comma
(brace
l_int|0x1FD0
comma
l_int|0x1FD2
comma
l_int|8
)brace
comma
(brace
l_int|0x03C2
comma
l_int|0x03C3
comma
op_minus
l_int|31
)brace
comma
(brace
l_int|0x1F51
comma
l_int|0x1F52
comma
l_int|8
)brace
comma
(brace
l_int|0x1FE0
comma
l_int|0x1FE2
comma
l_int|8
)brace
comma
(brace
l_int|0x03C3
comma
l_int|0x03CC
comma
op_minus
l_int|32
)brace
comma
(brace
l_int|0x1F53
comma
l_int|0x1F54
comma
l_int|8
)brace
comma
(brace
l_int|0x1FE5
comma
l_int|0x1FE6
comma
l_int|7
)brace
comma
(brace
l_int|0x03CC
comma
l_int|0x03CD
comma
op_minus
l_int|64
)brace
comma
(brace
l_int|0x1F55
comma
l_int|0x1F56
comma
l_int|8
)brace
comma
(brace
l_int|0x2170
comma
l_int|0x2180
comma
op_minus
l_int|16
)brace
comma
(brace
l_int|0x03CD
comma
l_int|0x03CF
comma
op_minus
l_int|63
)brace
comma
(brace
l_int|0x1F57
comma
l_int|0x1F58
comma
l_int|8
)brace
comma
(brace
l_int|0x24D0
comma
l_int|0x24EA
comma
op_minus
l_int|26
)brace
comma
(brace
l_int|0x0430
comma
l_int|0x0450
comma
op_minus
l_int|32
)brace
comma
(brace
l_int|0x1F60
comma
l_int|0x1F68
comma
l_int|8
)brace
comma
(brace
l_int|0xFF41
comma
l_int|0xFF5B
comma
op_minus
l_int|32
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
r_static
r_const
r_int
id|uc_dup_table
(braket
)braket
(braket
l_int|2
)braket
op_assign
(brace
multiline_comment|/* Start, End */
(brace
l_int|0x0100
comma
l_int|0x012F
)brace
comma
(brace
l_int|0x01A0
comma
l_int|0x01A6
)brace
comma
(brace
l_int|0x03E2
comma
l_int|0x03EF
)brace
comma
(brace
l_int|0x04CB
comma
l_int|0x04CC
)brace
comma
(brace
l_int|0x0132
comma
l_int|0x0137
)brace
comma
(brace
l_int|0x01B3
comma
l_int|0x01B7
)brace
comma
(brace
l_int|0x0460
comma
l_int|0x0481
)brace
comma
(brace
l_int|0x04D0
comma
l_int|0x04EB
)brace
comma
(brace
l_int|0x0139
comma
l_int|0x0149
)brace
comma
(brace
l_int|0x01CD
comma
l_int|0x01DD
)brace
comma
(brace
l_int|0x0490
comma
l_int|0x04BF
)brace
comma
(brace
l_int|0x04EE
comma
l_int|0x04F5
)brace
comma
(brace
l_int|0x014A
comma
l_int|0x0178
)brace
comma
(brace
l_int|0x01DE
comma
l_int|0x01EF
)brace
comma
(brace
l_int|0x04BF
comma
l_int|0x04BF
)brace
comma
(brace
l_int|0x04F8
comma
l_int|0x04F9
)brace
comma
(brace
l_int|0x0179
comma
l_int|0x017E
)brace
comma
(brace
l_int|0x01F4
comma
l_int|0x01F5
)brace
comma
(brace
l_int|0x04C1
comma
l_int|0x04C4
)brace
comma
(brace
l_int|0x1E00
comma
l_int|0x1E95
)brace
comma
(brace
l_int|0x018B
comma
l_int|0x018B
)brace
comma
(brace
l_int|0x01FA
comma
l_int|0x0218
)brace
comma
(brace
l_int|0x04C7
comma
l_int|0x04C8
)brace
comma
(brace
l_int|0x1EA0
comma
l_int|0x1EF9
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
r_static
r_const
r_int
id|uc_word_table
(braket
)braket
(braket
l_int|2
)braket
op_assign
(brace
multiline_comment|/* Offset, Value */
(brace
l_int|0x00FF
comma
l_int|0x0178
)brace
comma
(brace
l_int|0x01AD
comma
l_int|0x01AC
)brace
comma
(brace
l_int|0x01F3
comma
l_int|0x01F1
)brace
comma
(brace
l_int|0x0269
comma
l_int|0x0196
)brace
comma
(brace
l_int|0x0183
comma
l_int|0x0182
)brace
comma
(brace
l_int|0x01B0
comma
l_int|0x01AF
)brace
comma
(brace
l_int|0x0253
comma
l_int|0x0181
)brace
comma
(brace
l_int|0x026F
comma
l_int|0x019C
)brace
comma
(brace
l_int|0x0185
comma
l_int|0x0184
)brace
comma
(brace
l_int|0x01B9
comma
l_int|0x01B8
)brace
comma
(brace
l_int|0x0254
comma
l_int|0x0186
)brace
comma
(brace
l_int|0x0272
comma
l_int|0x019D
)brace
comma
(brace
l_int|0x0188
comma
l_int|0x0187
)brace
comma
(brace
l_int|0x01BD
comma
l_int|0x01BC
)brace
comma
(brace
l_int|0x0259
comma
l_int|0x018F
)brace
comma
(brace
l_int|0x0275
comma
l_int|0x019F
)brace
comma
(brace
l_int|0x018C
comma
l_int|0x018B
)brace
comma
(brace
l_int|0x01C6
comma
l_int|0x01C4
)brace
comma
(brace
l_int|0x025B
comma
l_int|0x0190
)brace
comma
(brace
l_int|0x0283
comma
l_int|0x01A9
)brace
comma
(brace
l_int|0x0192
comma
l_int|0x0191
)brace
comma
(brace
l_int|0x01C9
comma
l_int|0x01C7
)brace
comma
(brace
l_int|0x0260
comma
l_int|0x0193
)brace
comma
(brace
l_int|0x0288
comma
l_int|0x01AE
)brace
comma
(brace
l_int|0x0199
comma
l_int|0x0198
)brace
comma
(brace
l_int|0x01CC
comma
l_int|0x01CA
)brace
comma
(brace
l_int|0x0263
comma
l_int|0x0194
)brace
comma
(brace
l_int|0x0292
comma
l_int|0x01B7
)brace
comma
(brace
l_int|0x01A8
comma
l_int|0x01A7
)brace
comma
(brace
l_int|0x01DD
comma
l_int|0x018E
)brace
comma
(brace
l_int|0x0268
comma
l_int|0x0197
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
r_int
id|i
comma
id|r
suffix:semicolon
id|ntfschar
op_star
id|uc
suffix:semicolon
id|uc
op_assign
id|ntfs_malloc_nofs
c_func
(paren
id|default_upcase_len
op_star
r_sizeof
(paren
id|ntfschar
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uc
)paren
r_return
id|uc
suffix:semicolon
id|memset
c_func
(paren
id|uc
comma
l_int|0
comma
id|default_upcase_len
op_star
r_sizeof
(paren
id|ntfschar
)paren
)paren
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
id|default_upcase_len
suffix:semicolon
id|i
op_increment
)paren
id|uc
(braket
id|i
)braket
op_assign
id|cpu_to_le16
c_func
(paren
id|i
)paren
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
l_int|0
suffix:semicolon
id|uc_run_table
(braket
id|r
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|r
op_increment
)paren
r_for
c_loop
(paren
id|i
op_assign
id|uc_run_table
(braket
id|r
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|i
OL
id|uc_run_table
(braket
id|r
)braket
(braket
l_int|1
)braket
suffix:semicolon
id|i
op_increment
)paren
id|uc
(braket
id|i
)braket
op_assign
id|cpu_to_le16
c_func
(paren
(paren
id|le16_to_cpu
c_func
(paren
id|uc
(braket
id|i
)braket
)paren
op_plus
id|uc_run_table
(braket
id|r
)braket
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
l_int|0
suffix:semicolon
id|uc_dup_table
(braket
id|r
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|r
op_increment
)paren
r_for
c_loop
(paren
id|i
op_assign
id|uc_dup_table
(braket
id|r
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|i
OL
id|uc_dup_table
(braket
id|r
)braket
(braket
l_int|1
)braket
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
id|uc
(braket
id|i
op_plus
l_int|1
)braket
op_assign
id|cpu_to_le16
c_func
(paren
id|le16_to_cpu
c_func
(paren
id|uc
(braket
id|i
op_plus
l_int|1
)braket
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|r
op_assign
l_int|0
suffix:semicolon
id|uc_word_table
(braket
id|r
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|r
op_increment
)paren
id|uc
(braket
id|uc_word_table
(braket
id|r
)braket
(braket
l_int|0
)braket
)braket
op_assign
id|cpu_to_le16
c_func
(paren
id|uc_word_table
(braket
id|r
)braket
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
id|uc
suffix:semicolon
)brace
eof
