multiline_comment|/***************************************************************************&n; * binoffset.c&n; * (C) 2002 Randy Dunlap &lt;rddunlap@osdl.org&gt;&n;&n;#   This program is free software; you can redistribute it and/or modify&n;#   it under the terms of the GNU General Public License as published by&n;#   the Free Software Foundation; either version 2 of the License, or&n;#   (at your option) any later version.&n;#&n;#   This program is distributed in the hope that it will be useful,&n;#   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;#   GNU General Public License for more details.&n;#&n;#   You should have received a copy of the GNU General Public License&n;#   along with this program; if not, write to the Free Software&n;#   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;# binoffset.c:&n;# - searches a (binary) file for a specified (binary) pattern&n;# - returns the offset of the located pattern or ~0 if not found&n;# - exits with exit status 0 normally or non-0 if pattern is not found&n;#   or any other error occurs.&n;&n;****************************************************************/
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
DECL|macro|VERSION
mdefine_line|#define VERSION&t;&t;&quot;0.1&quot;
DECL|macro|BUF_SIZE
mdefine_line|#define BUF_SIZE&t;(16 * 1024)
DECL|macro|PAT_SIZE
mdefine_line|#define PAT_SIZE&t;100
DECL|variable|progname
r_char
op_star
id|progname
suffix:semicolon
DECL|variable|inputname
r_char
op_star
id|inputname
suffix:semicolon
DECL|variable|inputfd
r_int
id|inputfd
suffix:semicolon
DECL|variable|bix
r_int
id|bix
suffix:semicolon
multiline_comment|/* buf index */
DECL|variable|patterns
r_int
r_char
id|patterns
(braket
id|PAT_SIZE
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
multiline_comment|/* byte-sized pattern array */
DECL|variable|pat_len
r_int
id|pat_len
suffix:semicolon
multiline_comment|/* actual number of pattern bytes */
DECL|variable|madr
r_int
r_char
op_star
id|madr
suffix:semicolon
multiline_comment|/* mmap address */
DECL|variable|filesize
r_int
id|filesize
suffix:semicolon
DECL|variable|num_matches
r_int
id|num_matches
op_assign
l_int|0
suffix:semicolon
DECL|variable|firstloc
id|off_t
id|firstloc
op_assign
l_int|0
suffix:semicolon
DECL|function|usage
r_void
id|usage
(paren
r_void
)paren
(brace
id|fprintf
(paren
id|stderr
comma
l_string|&quot;%s ver. %s&bslash;n&quot;
comma
id|progname
comma
id|VERSION
)paren
suffix:semicolon
id|fprintf
(paren
id|stderr
comma
l_string|&quot;usage:  %s filename pattern_bytes&bslash;n&quot;
comma
id|progname
)paren
suffix:semicolon
id|fprintf
(paren
id|stderr
comma
l_string|&quot;        [prints location of pattern_bytes in file]&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|get_pattern
r_int
id|get_pattern
(paren
r_int
id|pat_count
comma
r_char
op_star
id|pats
(braket
)braket
)paren
(brace
r_int
id|ix
comma
id|err
comma
id|tmp
suffix:semicolon
macro_line|#ifdef DEBUG
id|fprintf
(paren
id|stderr
comma
l_string|&quot;get_pattern: count = %d&bslash;n&quot;
comma
id|pat_count
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ix
op_assign
l_int|0
suffix:semicolon
id|ix
OL
id|pat_count
suffix:semicolon
id|ix
op_increment
)paren
id|fprintf
(paren
id|stderr
comma
l_string|&quot;  pat # %d:  [%s]&bslash;n&quot;
comma
id|ix
comma
id|pats
(braket
id|ix
)braket
)paren
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|ix
op_assign
l_int|0
suffix:semicolon
id|ix
OL
id|pat_count
suffix:semicolon
id|ix
op_increment
)paren
(brace
id|tmp
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
id|sscanf
(paren
id|pats
(braket
id|ix
)braket
comma
l_string|&quot;%5i&quot;
comma
op_amp
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
l_int|1
op_logical_or
id|tmp
OG
l_int|0xff
)paren
(brace
id|fprintf
(paren
id|stderr
comma
l_string|&quot;pattern or value error in pattern # %d [%s]&bslash;n&quot;
comma
id|ix
comma
id|pats
(braket
id|ix
)braket
)paren
suffix:semicolon
id|usage
(paren
)paren
suffix:semicolon
)brace
id|patterns
(braket
id|ix
)braket
op_assign
id|tmp
suffix:semicolon
)brace
id|pat_len
op_assign
id|pat_count
suffix:semicolon
)brace
DECL|function|search_pattern
r_int
id|search_pattern
(paren
r_void
)paren
(brace
r_for
c_loop
(paren
id|bix
op_assign
l_int|0
suffix:semicolon
id|bix
OL
id|filesize
suffix:semicolon
id|bix
op_increment
)paren
(brace
r_if
c_cond
(paren
id|madr
(braket
id|bix
)braket
op_eq
id|patterns
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
id|memcmp
(paren
op_amp
id|madr
(braket
id|bix
)braket
comma
id|patterns
comma
id|pat_len
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|num_matches
op_eq
l_int|0
)paren
id|firstloc
op_assign
id|bix
suffix:semicolon
id|num_matches
op_increment
suffix:semicolon
)brace
)brace
)brace
)brace
macro_line|#ifdef NOTDEF
DECL|function|get_filesize
r_int
id|get_filesize
(paren
r_int
id|fd
)paren
(brace
id|off_t
id|end_off
op_assign
id|lseek
(paren
id|fd
comma
l_int|0
comma
id|SEEK_END
)paren
suffix:semicolon
id|lseek
(paren
id|fd
comma
l_int|0
comma
id|SEEK_SET
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
id|end_off
suffix:semicolon
)brace
macro_line|#endif
DECL|function|get_filesize
r_int
id|get_filesize
(paren
r_int
id|fd
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|stat
id|stat
suffix:semicolon
id|err
op_assign
id|fstat
(paren
id|fd
comma
op_amp
id|stat
)paren
suffix:semicolon
id|fprintf
(paren
id|stderr
comma
l_string|&quot;filesize: %d&bslash;n&quot;
comma
id|err
OL
l_int|0
ques
c_cond
id|err
suffix:colon
id|stat.st_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
(paren
r_int
)paren
id|stat.st_size
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
id|progname
op_assign
id|argv
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|3
)paren
id|usage
(paren
)paren
suffix:semicolon
id|get_pattern
(paren
id|argc
op_minus
l_int|2
comma
id|argv
op_plus
l_int|2
)paren
suffix:semicolon
id|inputname
op_assign
id|argv
(braket
l_int|1
)braket
suffix:semicolon
id|inputfd
op_assign
id|open
(paren
id|inputname
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inputfd
op_eq
op_minus
l_int|1
)paren
(brace
id|fprintf
(paren
id|stderr
comma
l_string|&quot;%s: cannot open &squot;%s&squot;&bslash;n&quot;
comma
id|progname
comma
id|inputname
)paren
suffix:semicolon
m_exit
(paren
l_int|3
)paren
suffix:semicolon
)brace
id|filesize
op_assign
id|get_filesize
(paren
id|inputfd
)paren
suffix:semicolon
id|madr
op_assign
id|mmap
(paren
l_int|0
comma
id|filesize
comma
id|PROT_READ
comma
id|MAP_PRIVATE
comma
id|inputfd
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|madr
op_eq
id|MAP_FAILED
)paren
(brace
id|fprintf
(paren
id|stderr
comma
l_string|&quot;mmap error = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
id|close
(paren
id|inputfd
)paren
suffix:semicolon
m_exit
(paren
l_int|4
)paren
suffix:semicolon
)brace
id|search_pattern
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|munmap
(paren
id|madr
comma
id|filesize
)paren
)paren
id|fprintf
(paren
id|stderr
comma
l_string|&quot;munmap error = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_if
c_cond
(paren
id|close
(paren
id|inputfd
)paren
)paren
id|fprintf
(paren
id|stderr
comma
l_string|&quot;%s: error %d closing &squot;%s&squot;&bslash;n&quot;
comma
id|progname
comma
id|errno
comma
id|inputname
)paren
suffix:semicolon
id|fprintf
(paren
id|stderr
comma
l_string|&quot;number of pattern matches = %d&bslash;n&quot;
comma
id|num_matches
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_matches
op_eq
l_int|0
)paren
id|firstloc
op_assign
op_complement
l_int|0
suffix:semicolon
id|printf
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|firstloc
)paren
suffix:semicolon
id|fprintf
(paren
id|stderr
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|firstloc
)paren
suffix:semicolon
m_exit
(paren
id|num_matches
ques
c_cond
l_int|0
suffix:colon
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/* end binoffset.c */
eof
