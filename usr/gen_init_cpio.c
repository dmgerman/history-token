macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;time.h&gt;
macro_line|#include &lt;fcntl.h&gt;
DECL|variable|offset
r_static
r_int
r_int
id|offset
suffix:semicolon
DECL|variable|ino
r_static
r_int
r_int
id|ino
op_assign
l_int|721
suffix:semicolon
DECL|function|push_string
r_static
r_void
id|push_string
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_int
r_int
id|name_len
op_assign
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
suffix:semicolon
id|fputs
c_func
(paren
id|name
comma
id|stdout
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|offset
op_add_assign
id|name_len
suffix:semicolon
)brace
DECL|function|push_pad
r_static
r_void
id|push_pad
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|offset
op_amp
l_int|3
)paren
(brace
id|putchar
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|offset
op_increment
suffix:semicolon
)brace
)brace
DECL|function|push_rest
r_static
r_void
id|push_rest
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_int
r_int
id|name_len
op_assign
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
suffix:semicolon
r_int
r_int
id|tmp_ofs
suffix:semicolon
id|fputs
c_func
(paren
id|name
comma
id|stdout
)paren
suffix:semicolon
id|putchar
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|offset
op_add_assign
id|name_len
suffix:semicolon
id|tmp_ofs
op_assign
id|name_len
op_plus
l_int|110
suffix:semicolon
r_while
c_loop
(paren
id|tmp_ofs
op_amp
l_int|3
)paren
(brace
id|putchar
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|offset
op_increment
suffix:semicolon
id|tmp_ofs
op_increment
suffix:semicolon
)brace
)brace
DECL|function|push_hdr
r_static
r_void
id|push_hdr
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
id|fputs
c_func
(paren
id|s
comma
id|stdout
)paren
suffix:semicolon
id|offset
op_add_assign
l_int|110
suffix:semicolon
)brace
DECL|function|cpio_trailer
r_static
r_void
id|cpio_trailer
c_func
(paren
r_void
)paren
(brace
r_char
id|s
(braket
l_int|256
)braket
suffix:semicolon
r_const
r_char
id|name
(braket
)braket
op_assign
l_string|&quot;TRAILER!!!&quot;
suffix:semicolon
id|sprintf
c_func
(paren
id|s
comma
l_string|&quot;%s%08X%08X%08lX%08lX%08X%08lX&quot;
l_string|&quot;%08X%08X%08X%08X%08X%08X%08X&quot;
comma
l_string|&quot;070701&quot;
comma
multiline_comment|/* magic */
l_int|0
comma
multiline_comment|/* ino */
l_int|0
comma
multiline_comment|/* mode */
(paren
r_int
)paren
l_int|0
comma
multiline_comment|/* uid */
(paren
r_int
)paren
l_int|0
comma
multiline_comment|/* gid */
l_int|1
comma
multiline_comment|/* nlink */
(paren
r_int
)paren
l_int|0
comma
multiline_comment|/* mtime */
l_int|0
comma
multiline_comment|/* filesize */
l_int|0
comma
multiline_comment|/* major */
l_int|0
comma
multiline_comment|/* minor */
l_int|0
comma
multiline_comment|/* rmajor */
l_int|0
comma
multiline_comment|/* rminor */
(paren
r_int
)paren
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
comma
multiline_comment|/* namesize */
l_int|0
)paren
suffix:semicolon
multiline_comment|/* chksum */
id|push_hdr
c_func
(paren
id|s
)paren
suffix:semicolon
id|push_rest
c_func
(paren
id|name
)paren
suffix:semicolon
r_while
c_loop
(paren
id|offset
op_mod
l_int|512
)paren
(brace
id|putchar
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|offset
op_increment
suffix:semicolon
)brace
)brace
DECL|function|cpio_mkdir
r_static
r_void
id|cpio_mkdir
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|mode
comma
id|uid_t
id|uid
comma
id|gid_t
id|gid
)paren
(brace
r_char
id|s
(braket
l_int|256
)braket
suffix:semicolon
id|time_t
id|mtime
op_assign
id|time
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|s
comma
l_string|&quot;%s%08X%08X%08lX%08lX%08X%08lX&quot;
l_string|&quot;%08X%08X%08X%08X%08X%08X%08X&quot;
comma
l_string|&quot;070701&quot;
comma
multiline_comment|/* magic */
id|ino
op_increment
comma
multiline_comment|/* ino */
id|S_IFDIR
op_or
id|mode
comma
multiline_comment|/* mode */
(paren
r_int
)paren
id|uid
comma
multiline_comment|/* uid */
(paren
r_int
)paren
id|gid
comma
multiline_comment|/* gid */
l_int|2
comma
multiline_comment|/* nlink */
(paren
r_int
)paren
id|mtime
comma
multiline_comment|/* mtime */
l_int|0
comma
multiline_comment|/* filesize */
l_int|3
comma
multiline_comment|/* major */
l_int|1
comma
multiline_comment|/* minor */
l_int|0
comma
multiline_comment|/* rmajor */
l_int|0
comma
multiline_comment|/* rminor */
(paren
r_int
)paren
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
comma
multiline_comment|/* namesize */
l_int|0
)paren
suffix:semicolon
multiline_comment|/* chksum */
id|push_hdr
c_func
(paren
id|s
)paren
suffix:semicolon
id|push_rest
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
DECL|function|cpio_mknod
r_static
r_void
id|cpio_mknod
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
r_int
id|mode
comma
id|uid_t
id|uid
comma
id|gid_t
id|gid
comma
r_int
id|dev_type
comma
r_int
r_int
id|maj
comma
r_int
r_int
id|min
)paren
(brace
r_char
id|s
(braket
l_int|256
)braket
suffix:semicolon
id|time_t
id|mtime
op_assign
id|time
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev_type
op_eq
l_char|&squot;b&squot;
)paren
id|mode
op_or_assign
id|S_IFBLK
suffix:semicolon
r_else
id|mode
op_or_assign
id|S_IFCHR
suffix:semicolon
id|sprintf
c_func
(paren
id|s
comma
l_string|&quot;%s%08X%08X%08lX%08lX%08X%08lX&quot;
l_string|&quot;%08X%08X%08X%08X%08X%08X%08X&quot;
comma
l_string|&quot;070701&quot;
comma
multiline_comment|/* magic */
id|ino
op_increment
comma
multiline_comment|/* ino */
id|mode
comma
multiline_comment|/* mode */
(paren
r_int
)paren
id|uid
comma
multiline_comment|/* uid */
(paren
r_int
)paren
id|gid
comma
multiline_comment|/* gid */
l_int|1
comma
multiline_comment|/* nlink */
(paren
r_int
)paren
id|mtime
comma
multiline_comment|/* mtime */
l_int|0
comma
multiline_comment|/* filesize */
l_int|3
comma
multiline_comment|/* major */
l_int|1
comma
multiline_comment|/* minor */
id|maj
comma
multiline_comment|/* rmajor */
id|min
comma
multiline_comment|/* rminor */
(paren
r_int
)paren
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
comma
multiline_comment|/* namesize */
l_int|0
)paren
suffix:semicolon
multiline_comment|/* chksum */
id|push_hdr
c_func
(paren
id|s
)paren
suffix:semicolon
id|push_rest
c_func
(paren
id|name
)paren
suffix:semicolon
)brace
multiline_comment|/* Not marked static to keep the compiler quiet, as no one uses this yet... */
DECL|function|cpio_mkfile
r_void
id|cpio_mkfile
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_const
r_char
op_star
id|location
comma
r_int
r_int
id|mode
comma
id|uid_t
id|uid
comma
id|gid_t
id|gid
)paren
(brace
r_char
id|s
(braket
l_int|256
)braket
suffix:semicolon
r_char
op_star
id|filebuf
suffix:semicolon
r_struct
id|stat
id|buf
suffix:semicolon
r_int
id|file
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
id|i
suffix:semicolon
id|mode
op_or_assign
id|S_IFREG
suffix:semicolon
id|retval
op_assign
id|stat
(paren
id|filename
comma
op_amp
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|fprintf
(paren
id|stderr
comma
l_string|&quot;Filename %s could not be located&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|file
op_assign
id|open
(paren
id|filename
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
OL
l_int|0
)paren
(brace
id|fprintf
(paren
id|stderr
comma
l_string|&quot;Filename %s could not be opened for reading&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|filebuf
op_assign
id|malloc
c_func
(paren
id|buf.st_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filebuf
)paren
(brace
id|fprintf
(paren
id|stderr
comma
l_string|&quot;out of memory&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|error_close
suffix:semicolon
)brace
id|retval
op_assign
id|read
(paren
id|file
comma
id|filebuf
comma
id|buf.st_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
id|fprintf
(paren
id|stderr
comma
l_string|&quot;Can not read %s file&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
r_goto
id|error_free
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|s
comma
l_string|&quot;%s%08X%08X%08lX%08lX%08X%08lX&quot;
l_string|&quot;%08X%08X%08X%08X%08X%08X%08X&quot;
comma
l_string|&quot;070701&quot;
comma
multiline_comment|/* magic */
id|ino
op_increment
comma
multiline_comment|/* ino */
id|mode
comma
multiline_comment|/* mode */
(paren
r_int
)paren
id|uid
comma
multiline_comment|/* uid */
(paren
r_int
)paren
id|gid
comma
multiline_comment|/* gid */
l_int|1
comma
multiline_comment|/* nlink */
(paren
r_int
)paren
id|buf.st_mtime
comma
multiline_comment|/* mtime */
(paren
r_int
)paren
id|buf.st_size
comma
multiline_comment|/* filesize */
l_int|3
comma
multiline_comment|/* major */
l_int|1
comma
multiline_comment|/* minor */
l_int|0
comma
multiline_comment|/* rmajor */
l_int|0
comma
multiline_comment|/* rminor */
(paren
r_int
)paren
id|strlen
c_func
(paren
id|location
)paren
op_plus
l_int|1
comma
multiline_comment|/* namesize */
l_int|0
)paren
suffix:semicolon
multiline_comment|/* chksum */
id|push_hdr
c_func
(paren
id|s
)paren
suffix:semicolon
id|push_string
c_func
(paren
id|location
)paren
suffix:semicolon
id|push_pad
c_func
(paren
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
id|buf.st_size
suffix:semicolon
op_increment
id|i
)paren
id|fputc
c_func
(paren
id|filebuf
(braket
id|i
)braket
comma
id|stdout
)paren
suffix:semicolon
id|offset
op_add_assign
id|buf.st_size
suffix:semicolon
id|close
c_func
(paren
id|file
)paren
suffix:semicolon
id|free
c_func
(paren
id|filebuf
)paren
suffix:semicolon
id|push_pad
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
id|error_free
suffix:colon
id|free
c_func
(paren
id|filebuf
)paren
suffix:semicolon
id|error_close
suffix:colon
id|close
c_func
(paren
id|file
)paren
suffix:semicolon
id|error
suffix:colon
m_exit
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|main
r_int
id|main
(paren
r_int
id|argc
comma
r_char
op_star
id|argv
(braket
)braket
)paren
(brace
id|cpio_mkdir
c_func
(paren
l_string|&quot;/dev&quot;
comma
l_int|0755
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|cpio_mknod
c_func
(paren
l_string|&quot;/dev/console&quot;
comma
l_int|0600
comma
l_int|0
comma
l_int|0
comma
l_char|&squot;c&squot;
comma
l_int|5
comma
l_int|1
)paren
suffix:semicolon
id|cpio_mkdir
c_func
(paren
l_string|&quot;/root&quot;
comma
l_int|0700
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|cpio_trailer
c_func
(paren
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* silence compiler warnings */
r_return
l_int|0
suffix:semicolon
(paren
r_void
)paren
id|argc
suffix:semicolon
(paren
r_void
)paren
id|argv
suffix:semicolon
)brace
eof
