multiline_comment|/*&n; * arch/um/kernel/mem_user.c&n; *&n; * BRIEF MODULE DESCRIPTION&n; * user side memory routines for supporting IO memory inside user mode linux&n; *&n; * Copyright (C) 2001 RidgeRun, Inc.&n; * Author: RidgeRun, Inc.&n; *         Greg Lonnon glonnon@ridgerun.com or info@ridgerun.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|variable|physmem_region
r_struct
id|mem_region
id|physmem_region
suffix:semicolon
DECL|variable|mem_list
r_struct
id|mem_region
op_star
id|mem_list
op_assign
op_amp
id|physmem_region
suffix:semicolon
DECL|macro|TEMPNAME_TEMPLATE
mdefine_line|#define TEMPNAME_TEMPLATE &quot;vm_file-XXXXXX&quot;
DECL|function|create_mem_file
r_int
id|create_mem_file
c_func
(paren
r_int
r_int
id|len
)paren
(brace
r_int
id|fd
suffix:semicolon
r_char
id|zero
suffix:semicolon
id|fd
op_assign
id|make_tempfile
c_func
(paren
id|TEMPNAME_TEMPLATE
comma
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fchmod
c_func
(paren
id|fd
comma
l_int|0777
)paren
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;fchmod&quot;
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
id|os_seek_file
c_func
(paren
id|fd
comma
id|len
)paren
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;lseek&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|zero
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
id|fd
comma
op_amp
id|zero
comma
l_int|1
)paren
op_ne
l_int|1
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;write&quot;
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
id|fcntl
c_func
(paren
id|fd
comma
id|F_SETFD
comma
l_int|1
)paren
op_ne
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;Setting FD_CLOEXEC failed&quot;
)paren
suffix:semicolon
)brace
r_return
id|fd
suffix:semicolon
)brace
DECL|function|setup_one_range
r_void
id|setup_one_range
c_func
(paren
r_int
id|n
comma
r_int
id|fd
comma
r_char
op_star
id|driver
comma
r_int
r_int
id|start
comma
r_int
r_int
id|len
comma
r_struct
id|mem_region
op_star
id|region
)paren
(brace
r_if
c_cond
(paren
id|fd
op_eq
op_minus
l_int|1
)paren
(brace
id|fd
op_assign
id|create_mem_file
c_func
(paren
id|len
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|region
op_eq
l_int|NULL
)paren
(brace
id|region
op_assign
id|malloc
c_func
(paren
r_sizeof
(paren
op_star
id|region
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|region
op_eq
l_int|NULL
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;Allocating mem_region&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
op_star
id|region
op_assign
(paren
(paren
r_struct
id|mem_region
)paren
(brace
id|driver
suffix:colon
id|driver
comma
id|start
suffix:colon
id|start
comma
id|len
suffix:colon
id|len
comma
id|fd
suffix:colon
id|fd
)brace
)paren
suffix:semicolon
id|regions
(braket
id|n
)braket
op_assign
id|region
suffix:semicolon
)brace
DECL|function|setup_region
r_int
id|setup_region
c_func
(paren
r_struct
id|mem_region
op_star
id|region
comma
r_void
op_star
id|entry
)paren
(brace
r_void
op_star
id|loc
comma
op_star
id|start
suffix:semicolon
r_char
op_star
id|driver
suffix:semicolon
r_int
id|err
comma
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|region-&gt;start
op_ne
op_minus
l_int|1
)paren
(brace
id|err
op_assign
id|reserve_vm
c_func
(paren
id|region-&gt;start
comma
id|region-&gt;start
op_plus
id|region-&gt;len
comma
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;setup_region : failed to reserve &quot;
l_string|&quot;0x%x - 0x%x for driver &squot;%s&squot;&bslash;n&quot;
comma
id|region-&gt;start
comma
id|region-&gt;start
op_plus
id|region-&gt;len
comma
id|region-&gt;driver
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_else
id|region-&gt;start
op_assign
id|get_vm
c_func
(paren
id|region-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|region-&gt;start
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|region-&gt;driver
op_eq
l_int|NULL
)paren
(brace
id|driver
op_assign
l_string|&quot;physmem&quot;
suffix:semicolon
)brace
r_else
id|driver
op_assign
id|region-&gt;driver
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;setup_region : failed to find vm for &quot;
l_string|&quot;driver &squot;%s&squot; (length %d)&bslash;n&quot;
comma
id|driver
comma
id|region-&gt;len
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|region-&gt;start
op_eq
id|uml_physmem
)paren
(brace
id|start
op_assign
(paren
r_void
op_star
)paren
id|uml_reserved
suffix:semicolon
id|offset
op_assign
id|uml_reserved
op_minus
id|uml_physmem
suffix:semicolon
)brace
r_else
(brace
id|start
op_assign
(paren
r_void
op_star
)paren
id|region-&gt;start
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
)brace
id|loc
op_assign
id|mmap
c_func
(paren
id|start
comma
id|region-&gt;len
op_minus
id|offset
comma
id|PROT_READ
op_or
id|PROT_WRITE
comma
id|MAP_SHARED
op_or
id|MAP_FIXED
comma
id|region-&gt;fd
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|loc
op_ne
id|start
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;Mapping memory&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_iomem
r_static
r_int
id|__init
id|parse_iomem
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|add
)paren
(brace
r_struct
id|stat
id|buf
suffix:semicolon
r_char
op_star
id|file
comma
op_star
id|driver
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|driver
op_assign
id|str
suffix:semicolon
id|file
op_assign
id|strchr
c_func
(paren
id|str
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;parse_iomem : failed to parse iomem&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
op_star
id|file
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|file
op_increment
suffix:semicolon
id|fd
op_assign
id|os_open_file
c_func
(paren
id|file
comma
id|of_rdwr
c_func
(paren
id|OPENFLAGS
c_func
(paren
)paren
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;parse_iomem - Couldn&squot;t open io file, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|buf
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;parse_iomem - cannot fstat file, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|add_iomem
c_func
(paren
id|driver
comma
id|fd
comma
id|buf.st_size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;iomem=&quot;
comma
id|parse_iomem
comma
l_string|&quot;iomem=&lt;name&gt;,&lt;file&gt;&bslash;n&quot;
l_string|&quot;    Configure &lt;file&gt; as an IO memory region named &lt;name&gt;.&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef notdef
DECL|variable|logging
r_int
id|logging
op_assign
l_int|0
suffix:semicolon
DECL|variable|logging_fd
r_int
id|logging_fd
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|logging_line
r_int
id|logging_line
op_assign
l_int|0
suffix:semicolon
DECL|variable|logging_buf
r_char
id|logging_buf
(braket
l_int|256
)braket
suffix:semicolon
DECL|function|log
r_void
id|log
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|ap
suffix:semicolon
r_struct
id|timeval
id|tv
suffix:semicolon
r_struct
id|openflags
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|logging
op_eq
l_int|0
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|logging_fd
OL
l_int|0
)paren
(brace
id|flags
op_assign
id|of_create
c_func
(paren
id|of_trunc
c_func
(paren
id|of_rdrw
c_func
(paren
id|OPENFLAGS
c_func
(paren
)paren
)paren
)paren
)paren
suffix:semicolon
id|logging_fd
op_assign
id|os_open_file
c_func
(paren
l_string|&quot;log&quot;
comma
id|flags
comma
l_int|0644
)paren
suffix:semicolon
)brace
id|gettimeofday
c_func
(paren
op_amp
id|tv
comma
l_int|NULL
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|logging_buf
comma
l_string|&quot;%d&bslash;t %u.%u  &quot;
comma
id|logging_line
op_increment
comma
id|tv.tv_sec
comma
id|tv.tv_usec
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
op_amp
id|logging_buf
(braket
id|strlen
c_func
(paren
id|logging_buf
)paren
)braket
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
id|write
c_func
(paren
id|logging_fd
comma
id|logging_buf
comma
id|strlen
c_func
(paren
id|logging_buf
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|map
r_void
id|map
c_func
(paren
r_int
r_int
id|virt
comma
r_int
r_int
id|phys
comma
r_int
r_int
id|len
comma
r_int
id|r
comma
r_int
id|w
comma
r_int
id|x
)paren
(brace
r_struct
id|mem_region
op_star
id|region
suffix:semicolon
r_void
op_star
id|loc
suffix:semicolon
r_int
id|prot
suffix:semicolon
id|prot
op_assign
(paren
id|r
ques
c_cond
id|PROT_READ
suffix:colon
l_int|0
)paren
op_or
(paren
id|w
ques
c_cond
id|PROT_WRITE
suffix:colon
l_int|0
)paren
op_or
(paren
id|x
ques
c_cond
id|PROT_EXEC
suffix:colon
l_int|0
)paren
suffix:semicolon
id|region
op_assign
id|phys_region
c_func
(paren
id|phys
)paren
suffix:semicolon
id|loc
op_assign
id|mmap
c_func
(paren
(paren
r_void
op_star
)paren
id|virt
comma
id|len
comma
id|prot
comma
id|MAP_SHARED
op_or
id|MAP_FIXED
comma
id|region-&gt;fd
comma
id|phys_offset
c_func
(paren
id|phys
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|loc
op_ne
(paren
r_void
op_star
)paren
id|virt
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Error mapping a page - errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|function|unmap
r_int
id|unmap
c_func
(paren
r_void
op_star
id|addr
comma
r_int
id|len
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|munmap
c_func
(paren
id|addr
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_else
r_return
id|err
suffix:semicolon
)brace
DECL|function|protect
r_int
id|protect
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
id|r
comma
r_int
id|w
comma
r_int
id|x
comma
r_int
id|must_succeed
)paren
(brace
r_int
id|prot
suffix:semicolon
id|prot
op_assign
(paren
id|r
ques
c_cond
id|PROT_READ
suffix:colon
l_int|0
)paren
op_or
(paren
id|w
ques
c_cond
id|PROT_WRITE
suffix:colon
l_int|0
)paren
op_or
(paren
id|x
ques
c_cond
id|PROT_EXEC
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mprotect
c_func
(paren
(paren
r_void
op_star
)paren
id|addr
comma
id|len
comma
id|prot
)paren
op_eq
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|must_succeed
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;protect failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_else
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|find_iomem
r_int
r_int
id|find_iomem
c_func
(paren
r_char
op_star
id|driver
comma
r_int
r_int
op_star
id|len_out
)paren
(brace
r_struct
id|mem_region
op_star
id|region
suffix:semicolon
r_int
id|i
comma
id|n
suffix:semicolon
id|n
op_assign
id|nregions
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|region
op_assign
id|regions
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|region
op_eq
l_int|NULL
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|region-&gt;driver
op_ne
l_int|NULL
)paren
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|region-&gt;driver
comma
id|driver
)paren
)paren
(brace
op_star
id|len_out
op_assign
id|region-&gt;len
suffix:semicolon
r_return
id|region-&gt;start
suffix:semicolon
)brace
)brace
op_star
id|len_out
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof