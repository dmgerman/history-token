multiline_comment|/*  devfs (Device FileSystem) utilities.&n;&n;    Copyright (C) 1999-2002  Richard Gooch&n;&n;    This library is free software; you can redistribute it and/or&n;    modify it under the terms of the GNU Library General Public&n;    License as published by the Free Software Foundation; either&n;    version 2 of the License, or (at your option) any later version.&n;&n;    This library is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;    Library General Public License for more details.&n;&n;    You should have received a copy of the GNU Library General Public&n;    License along with this library; if not, write to the Free&n;    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;    Richard Gooch may be reached by email at  rgooch@atnf.csiro.au&n;    The postal address is:&n;      Richard Gooch, c/o ATNF, P. O. Box 76, Epping, N.S.W., 2121, Australia.&n;&n;    ChangeLog&n;&n;    19991031   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Created.&n;    19991103   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Created &lt;_devfs_convert_name&gt; and supported SCSI and IDE CD-ROMs&n;    20000203   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Changed operations pointer type to void *.&n;    20000621   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Changed interface to &lt;devfs_register_series&gt;.&n;    20000622   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Took account of interface change to &lt;devfs_mk_symlink&gt;.&n;               Took account of interface change to &lt;devfs_mk_dir&gt;.&n;    20010519   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Documentation cleanup.&n;    20010709   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Created &lt;devfs_*alloc_major&gt; and &lt;devfs_*alloc_devnum&gt;.&n;    20010710   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Created &lt;devfs_*alloc_unique_number&gt;.&n;    20010730   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Documentation typo fix.&n;    20010806   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Made &lt;block_semaphore&gt; and &lt;char_semaphore&gt; private.&n;    20010813   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Fixed bug in &lt;devfs_alloc_unique_number&gt;: limited to 128 numbers&n;    20010818   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Updated major masks up to Linus&squot; &quot;no new majors&quot; proclamation.&n;&t;       Block: were 126 now 122 free, char: were 26 now 19 free.&n;    20020324   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Fixed bug in &lt;devfs_alloc_unique_number&gt;: was clearing beyond&n;&t;       bitfield.&n;    20020326   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Fixed bitfield data type for &lt;devfs_*alloc_devnum&gt;.&n;               Made major bitfield type and initialiser 64 bit safe.&n;    20020413   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Fixed shift warning on 64 bit machines.&n;    20020428   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Copied and used macro for error messages from fs/devfs/base.c &n;    20021013   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Documentation fix.&n;    20030101   Adam J. Richter &lt;adam@yggdrasil.com&gt;&n;               Eliminate DEVFS_SPECIAL_{CHR,BLK}.  Use mode_t instead.&n;    20030106   Christoph Hellwig &lt;hch@infradead.org&gt;&n;               Rewrite devfs_{,de}alloc_devnum to look like C code.&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
DECL|function|devfs_register_tape
r_int
id|devfs_register_tape
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_char
id|tname
(braket
l_int|32
)braket
comma
id|dest
(braket
l_int|64
)braket
suffix:semicolon
r_static
r_int
r_int
id|tape_counter
suffix:semicolon
r_int
r_int
id|n
op_assign
id|tape_counter
op_increment
suffix:semicolon
id|sprintf
c_func
(paren
id|dest
comma
l_string|&quot;../%s&quot;
comma
id|name
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|tname
comma
l_string|&quot;tapes/tape%u&quot;
comma
id|n
)paren
suffix:semicolon
id|devfs_mk_symlink
c_func
(paren
id|tname
comma
id|dest
)paren
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
DECL|variable|devfs_register_tape
id|EXPORT_SYMBOL
c_func
(paren
id|devfs_register_tape
)paren
suffix:semicolon
DECL|function|devfs_unregister_tape
r_void
id|devfs_unregister_tape
c_func
(paren
r_int
id|num
)paren
(brace
r_if
c_cond
(paren
id|num
op_ge
l_int|0
)paren
id|devfs_remove
c_func
(paren
l_string|&quot;tapes/tape%u&quot;
comma
id|num
)paren
suffix:semicolon
)brace
DECL|variable|devfs_unregister_tape
id|EXPORT_SYMBOL
c_func
(paren
id|devfs_unregister_tape
)paren
suffix:semicolon
eof
