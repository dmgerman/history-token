macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/intermezzo_fs.h&gt;
macro_line|#include &lt;linux/intermezzo_upcall.h&gt;
macro_line|#include &lt;linux/intermezzo_psdev.h&gt;
macro_line|#include &lt;linux/intermezzo_kml.h&gt;
DECL|function|kml_getfset
r_static
r_struct
id|presto_file_set
op_star
id|kml_getfset
(paren
r_char
op_star
id|path
)paren
(brace
r_return
id|presto_path2fileset
c_func
(paren
id|path
)paren
suffix:semicolon
)brace
multiline_comment|/* Send the KML buffer and related volume info into kernel */
DECL|function|begin_kml_reint
r_int
id|begin_kml_reint
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
(brace
r_char
op_star
id|volname
suffix:semicolon
r_int
id|namelen
suffix:semicolon
r_char
op_star
id|recbuf
suffix:semicolon
r_int
id|reclen
suffix:semicolon
multiline_comment|/* int   newpos; */
)brace
id|input
suffix:semicolon
r_struct
id|kml_fsdata
op_star
id|kml_fsdata
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fset
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|path
suffix:semicolon
r_int
id|error
suffix:semicolon
id|ENTRY
suffix:semicolon
multiline_comment|/* allocate buffer &amp; copy it to kernel space */
id|error
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|input
comma
(paren
r_char
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|input
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|EXIT
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|input.reclen
OG
id|kml_fsdata-&gt;kml_maxsize
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* we&squot;ll find solution to this in the future */
id|PRESTO_ALLOC
c_func
(paren
id|path
comma
r_char
op_star
comma
id|input.namelen
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|error
op_assign
id|copy_from_user
c_func
(paren
id|path
comma
id|input.volname
comma
id|input.namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|PRESTO_FREE
c_func
(paren
id|path
comma
id|input.namelen
op_plus
l_int|1
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|path
(braket
id|input.namelen
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|fset
op_assign
id|kml_getfset
(paren
id|path
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|path
comma
id|input.namelen
op_plus
l_int|1
)paren
suffix:semicolon
id|kml_fsdata
op_assign
id|FSET_GET_KMLDATA
c_func
(paren
id|fset
)paren
suffix:semicolon
multiline_comment|/* read the buf from user memory here */
id|error
op_assign
id|copy_from_user
c_func
(paren
id|kml_fsdata-&gt;kml_buf
comma
id|input.recbuf
comma
id|input.reclen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|EXIT
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|kml_fsdata-&gt;kml_len
op_assign
id|input.reclen
suffix:semicolon
id|decode_kmlrec
(paren
op_amp
id|kml_fsdata-&gt;kml_reint_cache
comma
id|kml_fsdata-&gt;kml_buf
comma
id|kml_fsdata-&gt;kml_len
)paren
suffix:semicolon
id|kml_fsdata-&gt;kml_reint_current
op_assign
id|kml_fsdata-&gt;kml_reint_cache.next
suffix:semicolon
id|kml_fsdata-&gt;kml_reintpos
op_assign
l_int|0
suffix:semicolon
id|kml_fsdata-&gt;kml_count
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* DO_KML_REINT  */
DECL|function|do_kml_reint
r_int
id|do_kml_reint
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
(brace
r_char
op_star
id|volname
suffix:semicolon
r_int
id|namelen
suffix:semicolon
r_char
op_star
id|path
suffix:semicolon
r_int
id|pathlen
suffix:semicolon
r_int
id|recno
suffix:semicolon
r_int
id|offset
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|generation
suffix:semicolon
id|__u64
id|ino
suffix:semicolon
)brace
id|input
suffix:semicolon
r_int
id|error
suffix:semicolon
r_char
op_star
id|path
suffix:semicolon
r_struct
id|kml_rec
op_star
id|close_rec
suffix:semicolon
r_struct
id|kml_fsdata
op_star
id|kml_fsdata
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fset
suffix:semicolon
id|ENTRY
suffix:semicolon
id|error
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|input
comma
(paren
r_char
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|input
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|EXIT
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|PRESTO_ALLOC
c_func
(paren
id|path
comma
r_char
op_star
comma
id|input.namelen
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|error
op_assign
id|copy_from_user
c_func
(paren
id|path
comma
id|input.volname
comma
id|input.namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|PRESTO_FREE
c_func
(paren
id|path
comma
id|input.namelen
op_plus
l_int|1
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|path
(braket
id|input.namelen
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|fset
op_assign
id|kml_getfset
(paren
id|path
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|path
comma
id|input.namelen
op_plus
l_int|1
)paren
suffix:semicolon
id|kml_fsdata
op_assign
id|FSET_GET_KMLDATA
c_func
(paren
id|fset
)paren
suffix:semicolon
id|error
op_assign
id|kml_reintbuf
c_func
(paren
id|kml_fsdata
comma
id|fset-&gt;fset_mtpt-&gt;d_name.name
comma
op_amp
id|close_rec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
id|KML_CLOSE_BACKFETCH
op_logical_and
id|close_rec
op_ne
l_int|NULL
)paren
(brace
r_struct
id|kml_close
op_star
id|close
op_assign
op_amp
id|close_rec-&gt;rec_kml.close
suffix:semicolon
id|input.ino
op_assign
id|close-&gt;ino
suffix:semicolon
id|input.generation
op_assign
id|close-&gt;generation
suffix:semicolon
r_if
c_cond
(paren
id|strlen
(paren
id|close-&gt;path
)paren
op_plus
l_int|1
OL
id|input.pathlen
)paren
(brace
id|strcpy
(paren
id|input.path
comma
id|close-&gt;path
)paren
suffix:semicolon
id|input.pathlen
op_assign
id|strlen
(paren
id|close-&gt;path
)paren
op_plus
l_int|1
suffix:semicolon
id|input.recno
op_assign
id|close_rec-&gt;rec_tail.recno
suffix:semicolon
id|input.offset
op_assign
id|close_rec-&gt;rec_kml_offset
suffix:semicolon
id|input.len
op_assign
id|close_rec-&gt;rec_size
suffix:semicolon
id|input.generation
op_assign
id|close-&gt;generation
suffix:semicolon
id|input.ino
op_assign
id|close-&gt;ino
suffix:semicolon
)brace
r_else
(brace
id|CDEBUG
c_func
(paren
id|D_KML
comma
l_string|&quot;KML_DO_REINT::no space to save:%d &lt; %d&quot;
comma
id|strlen
(paren
id|close-&gt;path
)paren
op_plus
l_int|1
comma
id|input.pathlen
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
op_amp
id|input
comma
r_sizeof
(paren
id|input
)paren
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* END_KML_REINT */
DECL|function|end_kml_reint
r_int
id|end_kml_reint
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|arg
)paren
(brace
multiline_comment|/* Free KML buffer and related volume info */
r_struct
(brace
r_char
op_star
id|volname
suffix:semicolon
r_int
id|namelen
suffix:semicolon
macro_line|#if 0
r_int
id|count
suffix:semicolon
r_int
id|newpos
suffix:semicolon
macro_line|#endif
)brace
id|input
suffix:semicolon
r_struct
id|presto_file_set
op_star
id|fset
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|kml_fsdata
op_star
id|kml_fsdata
op_assign
l_int|NULL
suffix:semicolon
r_int
id|error
suffix:semicolon
r_char
op_star
id|path
suffix:semicolon
id|ENTRY
suffix:semicolon
id|error
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|input
comma
(paren
r_char
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|input
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|EXIT
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|PRESTO_ALLOC
c_func
(paren
id|path
comma
r_char
op_star
comma
id|input.namelen
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
)paren
(brace
id|EXIT
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|error
op_assign
id|copy_from_user
c_func
(paren
id|path
comma
id|input.volname
comma
id|input.namelen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|PRESTO_FREE
c_func
(paren
id|path
comma
id|input.namelen
op_plus
l_int|1
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|path
(braket
id|input.namelen
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|fset
op_assign
id|kml_getfset
(paren
id|path
)paren
suffix:semicolon
id|PRESTO_FREE
c_func
(paren
id|path
comma
id|input.namelen
op_plus
l_int|1
)paren
suffix:semicolon
id|kml_fsdata
op_assign
id|FSET_GET_KMLDATA
c_func
(paren
id|fset
)paren
suffix:semicolon
id|delete_kmlrec
(paren
op_amp
id|kml_fsdata-&gt;kml_reint_cache
)paren
suffix:semicolon
multiline_comment|/* kml reint support */
id|kml_fsdata-&gt;kml_reint_current
op_assign
l_int|NULL
suffix:semicolon
id|kml_fsdata-&gt;kml_len
op_assign
l_int|0
suffix:semicolon
id|kml_fsdata-&gt;kml_reintpos
op_assign
l_int|0
suffix:semicolon
id|kml_fsdata-&gt;kml_count
op_assign
l_int|0
suffix:semicolon
macro_line|#if 0
id|input.newpos
op_assign
id|kml_upc-&gt;newpos
suffix:semicolon
id|input.count
op_assign
id|kml_upc-&gt;count
suffix:semicolon
id|copy_to_user
c_func
(paren
(paren
r_char
op_star
)paren
id|arg
comma
op_amp
id|input
comma
r_sizeof
(paren
id|input
)paren
)paren
suffix:semicolon
macro_line|#endif
r_return
id|error
suffix:semicolon
)brace
eof