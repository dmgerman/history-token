multiline_comment|/*&n; * addinitrd - program to add a initrd image to an ecoff kernel&n; *&n; * (C) 1999 Thomas Bogendoerfer&n; * minor modifications, cleanup: Guido Guenther &lt;agx@sigxcpu.org&gt;&n; * further cleanup: Maciej W. Rozycki&n; */
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &quot;ecoff.h&quot;
DECL|macro|MIPS_PAGE_SIZE
mdefine_line|#define MIPS_PAGE_SIZE&t;4096
DECL|macro|MIPS_PAGE_MASK
mdefine_line|#define MIPS_PAGE_MASK&t;(MIPS_PAGE_SIZE-1)
DECL|macro|swab16
mdefine_line|#define swab16(x) &bslash;&n;        ((unsigned short)( &bslash;&n;                (((unsigned short)(x) &amp; (unsigned short)0x00ffU) &lt;&lt; 8) | &bslash;&n;                (((unsigned short)(x) &amp; (unsigned short)0xff00U) &gt;&gt; 8) ))
DECL|macro|swab32
mdefine_line|#define swab32(x) &bslash;&n;        ((unsigned int)( &bslash;&n;                (((unsigned int)(x) &amp; (unsigned int)0x000000ffUL) &lt;&lt; 24) | &bslash;&n;                (((unsigned int)(x) &amp; (unsigned int)0x0000ff00UL) &lt;&lt;  8) | &bslash;&n;                (((unsigned int)(x) &amp; (unsigned int)0x00ff0000UL) &gt;&gt;  8) | &bslash;&n;                (((unsigned int)(x) &amp; (unsigned int)0xff000000UL) &gt;&gt; 24) ))
DECL|macro|SWAB
mdefine_line|#define SWAB(a)&t;(swab ? swab32(a) : (a))
DECL|function|die
r_void
id|die
(paren
r_char
op_star
id|s
)paren
(brace
id|perror
(paren
id|s
)paren
suffix:semicolon
m_exit
(paren
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
r_int
id|fd_vmlinux
comma
id|fd_initrd
comma
id|fd_outfile
suffix:semicolon
id|FILHDR
id|efile
suffix:semicolon
id|AOUTHDR
id|eaout
suffix:semicolon
id|SCNHDR
id|esecs
(braket
l_int|3
)braket
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
r_int
r_int
id|loadaddr
suffix:semicolon
r_int
r_int
id|initrd_header
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|i
comma
id|cnt
suffix:semicolon
r_int
id|swab
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|argc
op_ne
l_int|4
)paren
(brace
id|printf
(paren
l_string|&quot;Usage: %s &lt;vmlinux&gt; &lt;initrd&gt; &lt;outfile&gt;&bslash;n&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|fd_vmlinux
op_assign
id|open
(paren
id|argv
(braket
l_int|1
)braket
comma
id|O_RDONLY
)paren
)paren
OL
l_int|0
)paren
id|die
(paren
l_string|&quot;open vmlinux&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
(paren
id|fd_vmlinux
comma
op_amp
id|efile
comma
r_sizeof
id|efile
)paren
op_ne
r_sizeof
id|efile
)paren
id|die
(paren
l_string|&quot;read file header&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
(paren
id|fd_vmlinux
comma
op_amp
id|eaout
comma
r_sizeof
id|eaout
)paren
op_ne
r_sizeof
id|eaout
)paren
id|die
(paren
l_string|&quot;read aout header&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
(paren
id|fd_vmlinux
comma
id|esecs
comma
r_sizeof
id|esecs
)paren
op_ne
r_sizeof
id|esecs
)paren
id|die
(paren
l_string|&quot;read section headers&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * check whether the file is good for us&n;&t; */
multiline_comment|/* TBD */
multiline_comment|/*&n;&t; * check, if we have to swab words&n;&t; */
r_if
c_cond
(paren
id|ntohs
c_func
(paren
l_int|0xaa55
)paren
op_eq
l_int|0xaa55
)paren
(brace
r_if
c_cond
(paren
id|efile.f_magic
op_eq
id|swab16
c_func
(paren
id|MIPSELMAGIC
)paren
)paren
id|swab
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|efile.f_magic
op_eq
id|swab16
c_func
(paren
id|MIPSEBMAGIC
)paren
)paren
id|swab
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* make sure we have an empty data segment for the initrd */
r_if
c_cond
(paren
id|eaout.dsize
op_logical_or
id|esecs
(braket
l_int|1
)braket
dot
id|s_size
)paren
(brace
id|fprintf
(paren
id|stderr
comma
l_string|&quot;Data segment not empty. Giving up!&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|fd_initrd
op_assign
id|open
(paren
id|argv
(braket
l_int|2
)braket
comma
id|O_RDONLY
)paren
)paren
OL
l_int|0
)paren
id|die
(paren
l_string|&quot;open initrd&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fstat
(paren
id|fd_initrd
comma
op_amp
id|st
)paren
OL
l_int|0
)paren
id|die
(paren
l_string|&quot;fstat initrd&quot;
)paren
suffix:semicolon
id|loadaddr
op_assign
(paren
(paren
id|SWAB
c_func
(paren
id|esecs
(braket
l_int|2
)braket
dot
id|s_vaddr
)paren
op_plus
id|SWAB
c_func
(paren
id|esecs
(braket
l_int|2
)braket
dot
id|s_size
)paren
op_plus
id|MIPS_PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
op_complement
id|MIPS_PAGE_MASK
)paren
op_minus
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|loadaddr
OL
(paren
id|SWAB
c_func
(paren
id|esecs
(braket
l_int|2
)braket
dot
id|s_vaddr
)paren
op_plus
id|SWAB
c_func
(paren
id|esecs
(braket
l_int|2
)braket
dot
id|s_size
)paren
)paren
)paren
id|loadaddr
op_add_assign
id|MIPS_PAGE_SIZE
suffix:semicolon
id|initrd_header
(braket
l_int|0
)braket
op_assign
id|SWAB
c_func
(paren
l_int|0x494E5244
)paren
suffix:semicolon
id|initrd_header
(braket
l_int|1
)braket
op_assign
id|SWAB
c_func
(paren
id|st.st_size
)paren
suffix:semicolon
id|eaout.dsize
op_assign
id|esecs
(braket
l_int|1
)braket
dot
id|s_size
op_assign
id|initrd_header
(braket
l_int|1
)braket
op_assign
id|SWAB
c_func
(paren
id|st.st_size
op_plus
l_int|8
)paren
suffix:semicolon
id|eaout.data_start
op_assign
id|esecs
(braket
l_int|1
)braket
dot
id|s_vaddr
op_assign
id|esecs
(braket
l_int|1
)braket
dot
id|s_paddr
op_assign
id|SWAB
c_func
(paren
id|loadaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fd_outfile
op_assign
id|open
(paren
id|argv
(braket
l_int|3
)braket
comma
id|O_RDWR
op_or
id|O_CREAT
op_or
id|O_TRUNC
comma
l_int|0666
)paren
)paren
OL
l_int|0
)paren
id|die
(paren
l_string|&quot;open outfile&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
(paren
id|fd_outfile
comma
op_amp
id|efile
comma
r_sizeof
id|efile
)paren
op_ne
r_sizeof
id|efile
)paren
id|die
(paren
l_string|&quot;write file header&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
(paren
id|fd_outfile
comma
op_amp
id|eaout
comma
r_sizeof
id|eaout
)paren
op_ne
r_sizeof
id|eaout
)paren
id|die
(paren
l_string|&quot;write aout header&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
(paren
id|fd_outfile
comma
id|esecs
comma
r_sizeof
id|esecs
)paren
op_ne
r_sizeof
id|esecs
)paren
id|die
(paren
l_string|&quot;write section headers&quot;
)paren
suffix:semicolon
multiline_comment|/* skip padding */
r_if
c_cond
(paren
id|lseek
c_func
(paren
id|fd_vmlinux
comma
id|SWAB
c_func
(paren
id|esecs
(braket
l_int|0
)braket
dot
id|s_scnptr
)paren
comma
id|SEEK_SET
)paren
op_eq
(paren
id|off_t
)paren
op_minus
l_int|1
)paren
(brace
id|die
(paren
l_string|&quot;lseek vmlinux&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lseek
c_func
(paren
id|fd_outfile
comma
id|SWAB
c_func
(paren
id|esecs
(braket
l_int|0
)braket
dot
id|s_scnptr
)paren
comma
id|SEEK_SET
)paren
op_eq
(paren
id|off_t
)paren
op_minus
l_int|1
)paren
(brace
id|die
(paren
l_string|&quot;lseek outfile&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* copy text segment */
id|cnt
op_assign
id|SWAB
c_func
(paren
id|eaout.tsize
)paren
suffix:semicolon
r_while
c_loop
(paren
id|cnt
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
op_assign
id|read
(paren
id|fd_vmlinux
comma
id|buf
comma
r_sizeof
id|buf
)paren
)paren
op_le
l_int|0
)paren
id|die
(paren
l_string|&quot;read vmlinux&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
(paren
id|fd_outfile
comma
id|buf
comma
id|i
)paren
op_ne
id|i
)paren
id|die
(paren
l_string|&quot;write vmlinux&quot;
)paren
suffix:semicolon
id|cnt
op_sub_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write
(paren
id|fd_outfile
comma
id|initrd_header
comma
r_sizeof
id|initrd_header
)paren
op_ne
r_sizeof
id|initrd_header
)paren
id|die
(paren
l_string|&quot;write initrd header&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|i
op_assign
id|read
(paren
id|fd_initrd
comma
id|buf
comma
r_sizeof
id|buf
)paren
)paren
OG
l_int|0
)paren
r_if
c_cond
(paren
id|write
(paren
id|fd_outfile
comma
id|buf
comma
id|i
)paren
op_ne
id|i
)paren
id|die
(paren
l_string|&quot;write initrd&quot;
)paren
suffix:semicolon
id|close
(paren
id|fd_vmlinux
)paren
suffix:semicolon
id|close
(paren
id|fd_initrd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
