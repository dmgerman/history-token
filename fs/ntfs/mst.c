multiline_comment|/*&n; * mst.c - NTFS multi sector transfer protection handling code. Part of the&n; *&t;   Linux-NTFS project.&n; *&n; * Copyright (c) 2001-2004 Anton Altaparmakov&n; *&n; * This program/include file is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as published&n; * by the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program/include file is distributed in the hope that it will be&n; * useful, but WITHOUT ANY WARRANTY; without even the implied warranty&n; * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program (in the main directory of the Linux-NTFS&n; * distribution in the file COPYING); if not, write to the Free Software&n; * Foundation,Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;ntfs.h&quot;
multiline_comment|/**&n; * post_read_mst_fixup - deprotect multi sector transfer protected data&n; * @b:&t;&t;pointer to the data to deprotect&n; * @size:&t;size in bytes of @b&n; *&n; * Perform the necessary post read multi sector transfer fixup and detect the&n; * presence of incomplete multi sector transfers. - In that case, overwrite the&n; * magic of the ntfs record header being processed with &quot;BAAD&quot; (in memory only!)&n; * and abort processing.&n; *&n; * Return 0 on success and -EINVAL on error (&quot;BAAD&quot; magic will be present).&n; *&n; * NOTE: We consider the absence / invalidity of an update sequence array to&n; * mean that the structure is not protected at all and hence doesn&squot;t need to&n; * be fixed up. Thus, we return success and not failure in this case. This is&n; * in contrast to pre_write_mst_fixup(), see below.&n; */
DECL|function|post_read_mst_fixup
r_int
id|post_read_mst_fixup
c_func
(paren
id|NTFS_RECORD
op_star
id|b
comma
r_const
id|u32
id|size
)paren
(brace
id|u16
id|usa_ofs
comma
id|usa_count
comma
id|usn
suffix:semicolon
id|u16
op_star
id|usa_pos
comma
op_star
id|data_pos
suffix:semicolon
multiline_comment|/* Setup the variables. */
id|usa_ofs
op_assign
id|le16_to_cpu
c_func
(paren
id|b-&gt;usa_ofs
)paren
suffix:semicolon
multiline_comment|/* Decrement usa_count to get number of fixups. */
id|usa_count
op_assign
id|le16_to_cpu
c_func
(paren
id|b-&gt;usa_count
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Size and alignment checks. */
r_if
c_cond
(paren
id|size
op_amp
(paren
id|NTFS_BLOCK_SIZE
op_minus
l_int|1
)paren
op_logical_or
id|usa_ofs
op_amp
l_int|1
op_logical_or
id|usa_ofs
op_plus
(paren
id|usa_count
op_star
l_int|2
)paren
OG
id|size
op_logical_or
(paren
id|size
op_rshift
id|NTFS_BLOCK_SIZE_BITS
)paren
op_ne
id|usa_count
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Position of usn in update sequence array. */
id|usa_pos
op_assign
(paren
id|u16
op_star
)paren
id|b
op_plus
id|usa_ofs
op_div
r_sizeof
(paren
id|u16
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The update sequence number which has to be equal to each of the&n;&t; * u16 values before they are fixed up. Note no need to care for&n;&t; * endianness since we are comparing and moving data for on disk&n;&t; * structures which means the data is consistent. - If it is&n;&t; * consistenty the wrong endianness it doesn&squot;t make any difference.&n;&t; */
id|usn
op_assign
op_star
id|usa_pos
suffix:semicolon
multiline_comment|/*&n;&t; * Position in protected data of first u16 that needs fixing up.&n;&t; */
id|data_pos
op_assign
(paren
id|u16
op_star
)paren
id|b
op_plus
id|NTFS_BLOCK_SIZE
op_div
r_sizeof
(paren
id|u16
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Check for incomplete multi sector transfer(s).&n;&t; */
r_while
c_loop
(paren
id|usa_count
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_star
id|data_pos
op_ne
id|usn
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Incomplete multi sector transfer detected! )-:&n;&t;&t;&t; * Set the magic to &quot;BAAD&quot; and return failure.&n;&t;&t;&t; * Note that magic_BAAD is already converted to le32.&n;&t;&t;&t; */
id|b-&gt;magic
op_assign
id|magic_BAAD
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|data_pos
op_add_assign
id|NTFS_BLOCK_SIZE
op_div
r_sizeof
(paren
id|u16
)paren
suffix:semicolon
)brace
multiline_comment|/* Re-setup the variables. */
id|usa_count
op_assign
id|le16_to_cpu
c_func
(paren
id|b-&gt;usa_count
)paren
op_minus
l_int|1
suffix:semicolon
id|data_pos
op_assign
(paren
id|u16
op_star
)paren
id|b
op_plus
id|NTFS_BLOCK_SIZE
op_div
r_sizeof
(paren
id|u16
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Fixup all sectors. */
r_while
c_loop
(paren
id|usa_count
op_decrement
)paren
(brace
multiline_comment|/*&n;&t;&t; * Increment position in usa and restore original data from&n;&t;&t; * the usa into the data buffer.&n;&t;&t; */
op_star
id|data_pos
op_assign
op_star
(paren
op_increment
id|usa_pos
)paren
suffix:semicolon
multiline_comment|/* Increment position in data as well. */
id|data_pos
op_add_assign
id|NTFS_BLOCK_SIZE
op_div
r_sizeof
(paren
id|u16
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * pre_write_mst_fixup - apply multi sector transfer protection&n; * @b:&t;&t;pointer to the data to protect&n; * @size:&t;size in bytes of @b&n; *&n; * Perform the necessary pre write multi sector transfer fixup on the data&n; * pointer to by @b of @size.&n; *&n; * Return 0 if fixup applied (success) or -EINVAL if no fixup was performed&n; * (assumed not needed). This is in contrast to post_read_mst_fixup() above.&n; *&n; * NOTE: We consider the absence / invalidity of an update sequence array to&n; * mean that the structure is not subject to protection and hence doesn&squot;t need&n; * to be fixed up. This means that you have to create a valid update sequence&n; * array header in the ntfs record before calling this function, otherwise it&n; * will fail (the header needs to contain the position of the update sequence&n; * array together with the number of elements in the array). You also need to&n; * initialise the update sequence number before calling this function&n; * otherwise a random word will be used (whatever was in the record at that&n; * position at that time).&n; */
DECL|function|pre_write_mst_fixup
r_int
id|pre_write_mst_fixup
c_func
(paren
id|NTFS_RECORD
op_star
id|b
comma
r_const
id|u32
id|size
)paren
(brace
id|le16
op_star
id|usa_pos
comma
op_star
id|data_pos
suffix:semicolon
id|u16
id|usa_ofs
comma
id|usa_count
comma
id|usn
suffix:semicolon
id|le16
id|le_usn
suffix:semicolon
multiline_comment|/* Sanity check + only fixup if it makes sense. */
r_if
c_cond
(paren
op_logical_neg
id|b
op_logical_or
id|ntfs_is_baad_record
c_func
(paren
id|b-&gt;magic
)paren
op_logical_or
id|ntfs_is_hole_record
c_func
(paren
id|b-&gt;magic
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Setup the variables. */
id|usa_ofs
op_assign
id|le16_to_cpu
c_func
(paren
id|b-&gt;usa_ofs
)paren
suffix:semicolon
multiline_comment|/* Decrement usa_count to get number of fixups. */
id|usa_count
op_assign
id|le16_to_cpu
c_func
(paren
id|b-&gt;usa_count
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Size and alignment checks. */
r_if
c_cond
(paren
id|size
op_amp
(paren
id|NTFS_BLOCK_SIZE
op_minus
l_int|1
)paren
op_logical_or
id|usa_ofs
op_amp
l_int|1
op_logical_or
id|usa_ofs
op_plus
(paren
id|usa_count
op_star
l_int|2
)paren
OG
id|size
op_logical_or
(paren
id|size
op_rshift
id|NTFS_BLOCK_SIZE_BITS
)paren
op_ne
id|usa_count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Position of usn in update sequence array. */
id|usa_pos
op_assign
(paren
id|le16
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
id|b
op_plus
id|usa_ofs
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Cyclically increment the update sequence number&n;&t; * (skipping 0 and -1, i.e. 0xffff).&n;&t; */
id|usn
op_assign
id|le16_to_cpup
c_func
(paren
id|usa_pos
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|usn
op_eq
l_int|0xffff
op_logical_or
op_logical_neg
id|usn
)paren
id|usn
op_assign
l_int|1
suffix:semicolon
id|le_usn
op_assign
id|cpu_to_le16
c_func
(paren
id|usn
)paren
suffix:semicolon
op_star
id|usa_pos
op_assign
id|le_usn
suffix:semicolon
multiline_comment|/* Position in data of first u16 that needs fixing up. */
id|data_pos
op_assign
(paren
id|le16
op_star
)paren
id|b
op_plus
id|NTFS_BLOCK_SIZE
op_div
r_sizeof
(paren
id|le16
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Fixup all sectors. */
r_while
c_loop
(paren
id|usa_count
op_decrement
)paren
(brace
multiline_comment|/*&n;&t;&t; * Increment the position in the usa and save the&n;&t;&t; * original data from the data buffer into the usa.&n;&t;&t; */
op_star
(paren
op_increment
id|usa_pos
)paren
op_assign
op_star
id|data_pos
suffix:semicolon
multiline_comment|/* Apply fixup to data. */
op_star
id|data_pos
op_assign
id|le_usn
suffix:semicolon
multiline_comment|/* Increment position in data as well. */
id|data_pos
op_add_assign
id|NTFS_BLOCK_SIZE
op_div
r_sizeof
(paren
id|le16
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * post_write_mst_fixup - fast deprotect multi sector transfer protected data&n; * @b:&t;&t;pointer to the data to deprotect&n; *&n; * Perform the necessary post write multi sector transfer fixup, not checking&n; * for any errors, because we assume we have just used pre_write_mst_fixup(),&n; * thus the data will be fine or we would never have gotten here.&n; */
DECL|function|post_write_mst_fixup
r_void
id|post_write_mst_fixup
c_func
(paren
id|NTFS_RECORD
op_star
id|b
)paren
(brace
id|le16
op_star
id|usa_pos
comma
op_star
id|data_pos
suffix:semicolon
id|u16
id|usa_ofs
op_assign
id|le16_to_cpu
c_func
(paren
id|b-&gt;usa_ofs
)paren
suffix:semicolon
id|u16
id|usa_count
op_assign
id|le16_to_cpu
c_func
(paren
id|b-&gt;usa_count
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Position of usn in update sequence array. */
id|usa_pos
op_assign
(paren
id|le16
op_star
)paren
id|b
op_plus
id|usa_ofs
op_div
r_sizeof
(paren
id|le16
)paren
suffix:semicolon
multiline_comment|/* Position in protected data of first u16 that needs fixing up. */
id|data_pos
op_assign
(paren
id|le16
op_star
)paren
id|b
op_plus
id|NTFS_BLOCK_SIZE
op_div
r_sizeof
(paren
id|le16
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Fixup all sectors. */
r_while
c_loop
(paren
id|usa_count
op_decrement
)paren
(brace
multiline_comment|/*&n;&t;&t; * Increment position in usa and restore original data from&n;&t;&t; * the usa into the data buffer.&n;&t;&t; */
op_star
id|data_pos
op_assign
op_star
(paren
op_increment
id|usa_pos
)paren
suffix:semicolon
multiline_comment|/* Increment position in data as well. */
id|data_pos
op_add_assign
id|NTFS_BLOCK_SIZE
op_div
r_sizeof
(paren
id|le16
)paren
suffix:semicolon
)brace
)brace
eof
