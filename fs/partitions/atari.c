multiline_comment|/*&n; *  fs/partitions/atari.c&n; *&n; *  Code extracted from drivers/block/genhd.c&n; *&n; *  Copyright (C) 1991-1998  Linus Torvalds&n; *  Re-organised Feb 1998 Russell King&n; */
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &quot;check.h&quot;
macro_line|#include &quot;atari.h&quot;
multiline_comment|/* ++guenther: this should be settable by the user (&quot;make config&quot;)?.&n; */
DECL|macro|ICD_PARTS
mdefine_line|#define ICD_PARTS
multiline_comment|/* check if a partition entry looks valid -- Atari format is assumed if at&n;   least one of the primary entries is ok this way */
DECL|macro|VALID_PARTITION
mdefine_line|#define&t;VALID_PARTITION(pi,hdsiz)&t;&t;&t;&t;&t;     &bslash;&n;    (((pi)-&gt;flg &amp; 1) &amp;&amp;&t;&t;&t;&t;&t;&t;&t;     &bslash;&n;     isalnum((pi)-&gt;id[0]) &amp;&amp; isalnum((pi)-&gt;id[1]) &amp;&amp; isalnum((pi)-&gt;id[2]) &amp;&amp; &bslash;&n;     be32_to_cpu((pi)-&gt;st) &lt;= (hdsiz) &amp;&amp;&t;&t;&t;&t;     &bslash;&n;     be32_to_cpu((pi)-&gt;st) + be32_to_cpu((pi)-&gt;siz) &lt;= (hdsiz))
DECL|function|OK_id
r_static
r_inline
r_int
id|OK_id
c_func
(paren
r_char
op_star
id|s
)paren
(brace
r_return
id|memcmp
(paren
id|s
comma
l_string|&quot;GEM&quot;
comma
l_int|3
)paren
op_eq
l_int|0
op_logical_or
id|memcmp
(paren
id|s
comma
l_string|&quot;BGM&quot;
comma
l_int|3
)paren
op_eq
l_int|0
op_logical_or
id|memcmp
(paren
id|s
comma
l_string|&quot;LNX&quot;
comma
l_int|3
)paren
op_eq
l_int|0
op_logical_or
id|memcmp
(paren
id|s
comma
l_string|&quot;SWP&quot;
comma
l_int|3
)paren
op_eq
l_int|0
op_logical_or
id|memcmp
(paren
id|s
comma
l_string|&quot;RAW&quot;
comma
l_int|3
)paren
op_eq
l_int|0
suffix:semicolon
)brace
DECL|function|atari_partition
r_int
id|atari_partition
c_func
(paren
r_struct
id|parsed_partitions
op_star
id|state
comma
r_struct
id|block_device
op_star
id|bdev
)paren
(brace
id|Sector
id|sect
suffix:semicolon
r_struct
id|rootsector
op_star
id|rs
suffix:semicolon
r_struct
id|partition_info
op_star
id|pi
suffix:semicolon
id|u32
id|extensect
suffix:semicolon
id|u32
id|hd_size
suffix:semicolon
r_int
id|slot
suffix:semicolon
macro_line|#ifdef ICD_PARTS
r_int
id|part_fmt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 0:unknown, 1:AHDI, 2:ICD/Supra */
macro_line|#endif
id|rs
op_assign
(paren
r_struct
id|rootsector
op_star
)paren
id|read_dev_sector
c_func
(paren
id|bdev
comma
l_int|0
comma
op_amp
id|sect
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rs
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Verify this is an Atari rootsector: */
id|hd_size
op_assign
id|bdev-&gt;bd_inode-&gt;i_size
op_rshift
l_int|9
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|VALID_PARTITION
c_func
(paren
op_amp
id|rs-&gt;part
(braket
l_int|0
)braket
comma
id|hd_size
)paren
op_logical_and
op_logical_neg
id|VALID_PARTITION
c_func
(paren
op_amp
id|rs-&gt;part
(braket
l_int|1
)braket
comma
id|hd_size
)paren
op_logical_and
op_logical_neg
id|VALID_PARTITION
c_func
(paren
op_amp
id|rs-&gt;part
(braket
l_int|2
)braket
comma
id|hd_size
)paren
op_logical_and
op_logical_neg
id|VALID_PARTITION
c_func
(paren
op_amp
id|rs-&gt;part
(braket
l_int|3
)braket
comma
id|hd_size
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * if there&squot;s no valid primary partition, assume that no Atari&n;&t;&t; * format partition table (there&squot;s no reliable magic or the like&n;&t;         * :-()&n;&t;&t; */
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pi
op_assign
op_amp
id|rs-&gt;part
(braket
l_int|0
)braket
suffix:semicolon
id|printk
(paren
l_string|&quot; AHDI&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|1
suffix:semicolon
id|pi
OL
op_amp
id|rs-&gt;part
(braket
l_int|4
)braket
op_logical_and
id|slot
OL
id|state-&gt;limit
suffix:semicolon
id|slot
op_increment
comma
id|pi
op_increment
)paren
(brace
r_struct
id|rootsector
op_star
id|xrs
suffix:semicolon
id|Sector
id|sect2
suffix:semicolon
id|ulong
id|partsect
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pi-&gt;flg
op_amp
l_int|1
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* active partition */
r_if
c_cond
(paren
id|memcmp
(paren
id|pi-&gt;id
comma
l_string|&quot;XGM&quot;
comma
l_int|3
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* we don&squot;t care about other id&squot;s */
id|put_partition
(paren
id|state
comma
id|slot
comma
id|be32_to_cpu
c_func
(paren
id|pi-&gt;st
)paren
comma
id|be32_to_cpu
c_func
(paren
id|pi-&gt;siz
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* extension partition */
macro_line|#ifdef ICD_PARTS
id|part_fmt
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot; XGM&lt;&quot;
)paren
suffix:semicolon
id|partsect
op_assign
id|extensect
op_assign
id|be32_to_cpu
c_func
(paren
id|pi-&gt;st
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|xrs
op_assign
(paren
r_struct
id|rootsector
op_star
)paren
id|read_dev_sector
c_func
(paren
id|bdev
comma
id|partsect
comma
op_amp
id|sect2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xrs
)paren
(brace
id|printk
(paren
l_string|&quot; block %ld read failed&bslash;n&quot;
comma
id|partsect
)paren
suffix:semicolon
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ++roman: sanity check: bit 0 of flg field must be set */
r_if
c_cond
(paren
op_logical_neg
(paren
id|xrs-&gt;part
(braket
l_int|0
)braket
dot
id|flg
op_amp
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nFirst sub-partition in extended partition is not valid!&bslash;n&quot;
)paren
suffix:semicolon
id|put_dev_sector
c_func
(paren
id|sect2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|put_partition
c_func
(paren
id|state
comma
id|slot
comma
id|partsect
op_plus
id|be32_to_cpu
c_func
(paren
id|xrs-&gt;part
(braket
l_int|0
)braket
dot
id|st
)paren
comma
id|be32_to_cpu
c_func
(paren
id|xrs-&gt;part
(braket
l_int|0
)braket
dot
id|siz
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|xrs-&gt;part
(braket
l_int|1
)braket
dot
id|flg
op_amp
l_int|1
)paren
)paren
(brace
multiline_comment|/* end of linked partition list */
id|put_dev_sector
c_func
(paren
id|sect2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|xrs-&gt;part
(braket
l_int|1
)braket
dot
id|id
comma
l_string|&quot;XGM&quot;
comma
l_int|3
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nID of extended partition is not XGM!&bslash;n&quot;
)paren
suffix:semicolon
id|put_dev_sector
c_func
(paren
id|sect2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|partsect
op_assign
id|be32_to_cpu
c_func
(paren
id|xrs-&gt;part
(braket
l_int|1
)braket
dot
id|st
)paren
op_plus
id|extensect
suffix:semicolon
id|put_dev_sector
c_func
(paren
id|sect2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|slot
op_eq
id|state-&gt;limit
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nMaximum number of partitions reached!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot; &gt;&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef ICD_PARTS
r_if
c_cond
(paren
id|part_fmt
op_ne
l_int|1
)paren
(brace
multiline_comment|/* no extended partitions -&gt; test ICD-format */
id|pi
op_assign
op_amp
id|rs-&gt;icdpart
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* sanity check: no ICD format if first partition invalid */
r_if
c_cond
(paren
id|OK_id
c_func
(paren
id|pi-&gt;id
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; ICD&lt;&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|pi
OL
op_amp
id|rs-&gt;icdpart
(braket
l_int|8
)braket
op_logical_and
id|slot
OL
id|state-&gt;limit
suffix:semicolon
id|slot
op_increment
comma
id|pi
op_increment
)paren
(brace
multiline_comment|/* accept only GEM,BGM,RAW,LNX,SWP partitions */
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|pi-&gt;flg
op_amp
l_int|1
)paren
op_logical_and
id|OK_id
c_func
(paren
id|pi-&gt;id
)paren
)paren
)paren
r_continue
suffix:semicolon
id|part_fmt
op_assign
l_int|2
suffix:semicolon
id|put_partition
(paren
id|state
comma
id|slot
comma
id|be32_to_cpu
c_func
(paren
id|pi-&gt;st
)paren
comma
id|be32_to_cpu
c_func
(paren
id|pi-&gt;siz
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; &gt;&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
id|put_dev_sector
c_func
(paren
id|sect
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
