multiline_comment|/*&n; *  linux/fs/ufs/cylinder.c&n; *&n; * Copyright (C) 1998&n; * Daniel Pirkl &lt;daniel.pirkl@email.cz&gt;&n; * Charles University, Faculty of Mathematics and Physics&n; *&n; *  ext2 - inode (block) bitmap caching inspired&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;swab.h&quot;
macro_line|#include &quot;util.h&quot;
DECL|macro|UFS_CYLINDER_DEBUG
macro_line|#undef UFS_CYLINDER_DEBUG
macro_line|#ifdef UFS_CYLINDER_DEBUG
DECL|macro|UFSD
mdefine_line|#define UFSD(x) printk(&quot;(%s, %d), %s:&quot;, __FILE__, __LINE__, __FUNCTION__); printk x;
macro_line|#else
DECL|macro|UFSD
mdefine_line|#define UFSD(x)
macro_line|#endif
multiline_comment|/*&n; * Read cylinder group into cache. The memory space for ufs_cg_private_info&n; * structure is already allocated during ufs_read_super.&n; */
DECL|function|ufs_read_cylinder
r_static
r_void
id|ufs_read_cylinder
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|cgno
comma
r_int
id|bitmap_nr
)paren
(brace
r_struct
id|ufs_sb_private_info
op_star
id|uspi
suffix:semicolon
r_struct
id|ufs_cg_private_info
op_star
id|ucpi
suffix:semicolon
r_struct
id|ufs_cylinder_group
op_star
id|ucg
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ENTER, cgno %u, bitmap_nr %u&bslash;n&quot;
comma
id|cgno
comma
id|bitmap_nr
)paren
)paren
id|uspi
op_assign
id|sb-&gt;u.ufs_sb.s_uspi
suffix:semicolon
id|ucpi
op_assign
id|sb-&gt;u.ufs_sb.s_ucpi
(braket
id|bitmap_nr
)braket
suffix:semicolon
id|ucg
op_assign
(paren
r_struct
id|ufs_cylinder_group
op_star
)paren
id|sb-&gt;u.ufs_sb.s_ucg
(braket
id|cgno
)braket
op_member_access_from_pointer
id|b_data
suffix:semicolon
id|UCPI_UBH-&gt;fragment
op_assign
id|ufs_cgcmin
c_func
(paren
id|cgno
)paren
suffix:semicolon
id|UCPI_UBH-&gt;count
op_assign
id|uspi-&gt;s_cgsize
op_rshift
id|sb-&gt;s_blocksize_bits
suffix:semicolon
multiline_comment|/*&n;&t; * We have already the first fragment of cylinder group block in buffer&n;&t; */
id|UCPI_UBH-&gt;bh
(braket
l_int|0
)braket
op_assign
id|sb-&gt;u.ufs_sb.s_ucg
(braket
id|cgno
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|UCPI_UBH-&gt;count
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|UCPI_UBH-&gt;bh
(braket
id|i
)braket
op_assign
id|bread
(paren
id|sb-&gt;s_dev
comma
id|UCPI_UBH-&gt;fragment
op_plus
id|i
comma
id|sb-&gt;s_blocksize
)paren
)paren
)paren
r_goto
id|failed
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_cgno
(braket
id|bitmap_nr
)braket
op_assign
id|cgno
suffix:semicolon
id|ucpi-&gt;c_cgx
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_cgx
)paren
suffix:semicolon
id|ucpi-&gt;c_ncyl
op_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_ncyl
)paren
suffix:semicolon
id|ucpi-&gt;c_niblk
op_assign
id|fs16_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_niblk
)paren
suffix:semicolon
id|ucpi-&gt;c_ndblk
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_ndblk
)paren
suffix:semicolon
id|ucpi-&gt;c_rotor
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_rotor
)paren
suffix:semicolon
id|ucpi-&gt;c_frotor
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_frotor
)paren
suffix:semicolon
id|ucpi-&gt;c_irotor
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_irotor
)paren
suffix:semicolon
id|ucpi-&gt;c_btotoff
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_btotoff
)paren
suffix:semicolon
id|ucpi-&gt;c_boff
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_boff
)paren
suffix:semicolon
id|ucpi-&gt;c_iusedoff
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_iusedoff
)paren
suffix:semicolon
id|ucpi-&gt;c_freeoff
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_freeoff
)paren
suffix:semicolon
id|ucpi-&gt;c_nextfreeoff
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_nextfreeoff
)paren
suffix:semicolon
id|ucpi-&gt;c_clustersumoff
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_u.cg_44.cg_clustersumoff
)paren
suffix:semicolon
id|ucpi-&gt;c_clusteroff
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_u.cg_44.cg_clusteroff
)paren
suffix:semicolon
id|ucpi-&gt;c_nclusterblks
op_assign
id|fs32_to_cpu
c_func
(paren
id|sb
comma
id|ucg-&gt;cg_u.cg_44.cg_nclusterblks
)paren
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
r_return
suffix:semicolon
id|failed
suffix:colon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
id|i
suffix:semicolon
id|j
op_increment
)paren
id|brelse
(paren
id|sb-&gt;u.ufs_sb.s_ucg
(braket
id|j
)braket
)paren
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_cgno
(braket
id|bitmap_nr
)braket
op_assign
id|UFS_CGNO_EMPTY
suffix:semicolon
id|ufs_error
(paren
id|sb
comma
l_string|&quot;ufs_read_cylinder&quot;
comma
l_string|&quot;can&squot;t read cylinder group block %u&quot;
comma
id|cgno
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove cylinder group from cache, doesn&squot;t release memory&n; * allocated for cylinder group (this is done at ufs_put_super only).&n; */
DECL|function|ufs_put_cylinder
r_void
id|ufs_put_cylinder
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|bitmap_nr
)paren
(brace
r_struct
id|ufs_sb_private_info
op_star
id|uspi
suffix:semicolon
r_struct
id|ufs_cg_private_info
op_star
id|ucpi
suffix:semicolon
r_struct
id|ufs_cylinder_group
op_star
id|ucg
suffix:semicolon
r_int
id|i
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ENTER, bitmap_nr %u&bslash;n&quot;
comma
id|bitmap_nr
)paren
)paren
id|uspi
op_assign
id|sb-&gt;u.ufs_sb.s_uspi
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;u.ufs_sb.s_cgno
(braket
id|bitmap_nr
)braket
op_eq
id|UFS_CGNO_EMPTY
)paren
(brace
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
r_return
suffix:semicolon
)brace
id|ucpi
op_assign
id|sb-&gt;u.ufs_sb.s_ucpi
(braket
id|bitmap_nr
)braket
suffix:semicolon
id|ucg
op_assign
id|ubh_get_ucg
c_func
(paren
id|UCPI_UBH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uspi-&gt;s_ncg
OG
id|UFS_MAX_GROUP_LOADED
op_logical_and
id|bitmap_nr
op_ge
id|sb-&gt;u.ufs_sb.s_cg_loaded
)paren
(brace
id|ufs_panic
(paren
id|sb
comma
l_string|&quot;ufs_put_cylinder&quot;
comma
l_string|&quot;internal error&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * rotor is not so important data, so we put it to disk &n;&t; * at the end of working with cylinder&n;&t; */
id|ucg-&gt;cg_rotor
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|ucpi-&gt;c_rotor
)paren
suffix:semicolon
id|ucg-&gt;cg_frotor
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|ucpi-&gt;c_frotor
)paren
suffix:semicolon
id|ucg-&gt;cg_irotor
op_assign
id|cpu_to_fs32
c_func
(paren
id|sb
comma
id|ucpi-&gt;c_irotor
)paren
suffix:semicolon
id|ubh_mark_buffer_dirty
(paren
id|UCPI_UBH
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|UCPI_UBH-&gt;count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|brelse
(paren
id|UCPI_UBH-&gt;bh
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|sb-&gt;u.ufs_sb.s_cgno
(braket
id|bitmap_nr
)braket
op_assign
id|UFS_CGNO_EMPTY
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
)brace
multiline_comment|/*&n; * Find cylinder group in cache and return it as pointer.&n; * If cylinder group is not in cache, we will load it from disk.&n; *&n; * The cache is managed by LRU algorithm. &n; */
DECL|function|ufs_load_cylinder
r_struct
id|ufs_cg_private_info
op_star
id|ufs_load_cylinder
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|cgno
)paren
(brace
r_struct
id|ufs_sb_private_info
op_star
id|uspi
suffix:semicolon
r_struct
id|ufs_cg_private_info
op_star
id|ucpi
suffix:semicolon
r_int
id|cg
comma
id|i
comma
id|j
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;ENTER, cgno %u&bslash;n&quot;
comma
id|cgno
)paren
)paren
id|uspi
op_assign
id|sb-&gt;u.ufs_sb.s_uspi
suffix:semicolon
r_if
c_cond
(paren
id|cgno
op_ge
id|uspi-&gt;s_ncg
)paren
(brace
id|ufs_panic
(paren
id|sb
comma
l_string|&quot;ufs_load_cylinder&quot;
comma
l_string|&quot;internal error, high number of cg&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Cylinder group number cg it in cache and it was last used&n;&t; */
r_if
c_cond
(paren
id|sb-&gt;u.ufs_sb.s_cgno
(braket
l_int|0
)braket
op_eq
id|cgno
)paren
(brace
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
r_return
id|sb-&gt;u.ufs_sb.s_ucpi
(braket
l_int|0
)braket
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Number of cylinder groups is not higher than UFS_MAX_GROUP_LOADED&n;&t; */
r_if
c_cond
(paren
id|uspi-&gt;s_ncg
op_le
id|UFS_MAX_GROUP_LOADED
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;u.ufs_sb.s_cgno
(braket
id|cgno
)braket
op_ne
id|UFS_CGNO_EMPTY
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;u.ufs_sb.s_cgno
(braket
id|cgno
)braket
op_ne
id|cgno
)paren
(brace
id|ufs_panic
(paren
id|sb
comma
l_string|&quot;ufs_load_cylinder&quot;
comma
l_string|&quot;internal error, wrong number of cg in cache&quot;
)paren
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT (FAILED)&bslash;n&quot;
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
r_return
id|sb-&gt;u.ufs_sb.s_ucpi
(braket
id|cgno
)braket
suffix:semicolon
)brace
)brace
r_else
(brace
id|ufs_read_cylinder
(paren
id|sb
comma
id|cgno
comma
id|cgno
)paren
suffix:semicolon
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
r_return
id|sb-&gt;u.ufs_sb.s_ucpi
(braket
id|cgno
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Cylinder group number cg is in cache but it was not last used, &n;&t; * we will move to the first position&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sb-&gt;u.ufs_sb.s_cg_loaded
op_logical_and
id|sb-&gt;u.ufs_sb.s_cgno
(braket
id|i
)braket
op_ne
id|cgno
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|sb-&gt;u.ufs_sb.s_cg_loaded
op_logical_and
id|sb-&gt;u.ufs_sb.s_cgno
(braket
id|i
)braket
op_eq
id|cgno
)paren
(brace
id|cg
op_assign
id|sb-&gt;u.ufs_sb.s_cgno
(braket
id|i
)braket
suffix:semicolon
id|ucpi
op_assign
id|sb-&gt;u.ufs_sb.s_ucpi
(braket
id|i
)braket
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|i
suffix:semicolon
id|j
OG
l_int|0
suffix:semicolon
id|j
op_decrement
)paren
(brace
id|sb-&gt;u.ufs_sb.s_cgno
(braket
id|j
)braket
op_assign
id|sb-&gt;u.ufs_sb.s_cgno
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_ucpi
(braket
id|j
)braket
op_assign
id|sb-&gt;u.ufs_sb.s_ucpi
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
)brace
id|sb-&gt;u.ufs_sb.s_cgno
(braket
l_int|0
)braket
op_assign
id|cg
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_ucpi
(braket
l_int|0
)braket
op_assign
id|ucpi
suffix:semicolon
multiline_comment|/*&n;&t; * Cylinder group number cg is not in cache, we will read it from disk&n;&t; * and put it to the first position&n;&t; */
)brace
r_else
(brace
r_if
c_cond
(paren
id|sb-&gt;u.ufs_sb.s_cg_loaded
OL
id|UFS_MAX_GROUP_LOADED
)paren
id|sb-&gt;u.ufs_sb.s_cg_loaded
op_increment
suffix:semicolon
r_else
id|ufs_put_cylinder
(paren
id|sb
comma
id|UFS_MAX_GROUP_LOADED
op_minus
l_int|1
)paren
suffix:semicolon
id|ucpi
op_assign
id|sb-&gt;u.ufs_sb.s_ucpi
(braket
id|sb-&gt;u.ufs_sb.s_cg_loaded
op_minus
l_int|1
)braket
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|sb-&gt;u.ufs_sb.s_cg_loaded
op_minus
l_int|1
suffix:semicolon
id|j
OG
l_int|0
suffix:semicolon
id|j
op_decrement
)paren
(brace
id|sb-&gt;u.ufs_sb.s_cgno
(braket
id|j
)braket
op_assign
id|sb-&gt;u.ufs_sb.s_cgno
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_ucpi
(braket
id|j
)braket
op_assign
id|sb-&gt;u.ufs_sb.s_ucpi
(braket
id|j
op_minus
l_int|1
)braket
suffix:semicolon
)brace
id|sb-&gt;u.ufs_sb.s_ucpi
(braket
l_int|0
)braket
op_assign
id|ucpi
suffix:semicolon
id|ufs_read_cylinder
(paren
id|sb
comma
id|cgno
comma
l_int|0
)paren
suffix:semicolon
)brace
id|UFSD
c_func
(paren
(paren
l_string|&quot;EXIT&bslash;n&quot;
)paren
)paren
r_return
id|sb-&gt;u.ufs_sb.s_ucpi
(braket
l_int|0
)braket
suffix:semicolon
)brace
eof
