multiline_comment|/*&n; *  linux/drivers/message/fusion/isense.c&n; *      Little linux driver / shim that interfaces with the Fusion MPT&n; *      Linux base driver to provide english readable strings in SCSI&n; *      Error Report logging output.  This module implements SCSI-3&n; *      Opcode lookup and a sorted table of SCSI-3 ASC/ASCQ strings.&n; *&n; *  Copyright (c) 1991-2002 Steven J. Ralston&n; *  Written By: Steven J. Ralston&n; *  (yes I wrote some of the orig. code back in 1991!)&n; *  (mailto:sjralston1@netscape.net)&n; *  (mailto:Pam.Delaney@lsil.com)&n; *&n; *  $Id: isense.c,v 1.33 2002/02/27 18:44:19 sralston Exp $&n; */
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; version 2 of the License.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    NO WARRANTY&n;    THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;    LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;    solely responsible for determining the appropriateness of using and&n;    distributing the Program and assumes all risks associated with its&n;    exercise of rights under this Agreement, including but not limited to&n;    the risks and costs of program errors, damage to or loss of data,&n;    programs or equipment, and unavailability or interruption of operations.&n;&n;    DISCLAIMER OF LIABILITY&n;    NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;    DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;    USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;    HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#if defined (__sparc__)
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#endif
multiline_comment|/* Hmmm, avoid undefined spinlock_t on lk-2.2.14-5.0 */
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0)
macro_line|#include &lt;asm/spinlock.h&gt;
macro_line|#endif
DECL|macro|MODULEAUTHOR
mdefine_line|#define MODULEAUTHOR &quot;Steven J. Ralston&quot;
DECL|macro|COPYRIGHT
mdefine_line|#define COPYRIGHT &quot;Copyright (c) 2001-2002 &quot; MODULEAUTHOR
macro_line|#include &quot;mptbase.h&quot;
macro_line|#include &quot;isense.h&quot;
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *  Private data...&n; */
multiline_comment|/*&n; *  YIKES!  I don&squot;t usually #include C source files, but..&n; *  The following #include&squot;s pulls in our needed ASCQ_Table[] array,&n; *  ASCQ_TableSz integer, and ScsiOpcodeString[] array!&n; */
macro_line|#include &quot;ascq_tbl.c&quot;
macro_line|#include &quot;scsiops.c&quot;
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
DECL|macro|my_NAME
mdefine_line|#define my_NAME&t;&t;&quot;SCSI-3 Opcodes &amp; ASC/ASCQ Strings&quot;
DECL|macro|my_VERSION
mdefine_line|#define my_VERSION&t;MPT_LINUX_VERSION_COMMON
DECL|macro|MYNAM
mdefine_line|#define MYNAM&t;&t;&quot;isense&quot;
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|variable|MODULEAUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|MODULEAUTHOR
)paren
suffix:semicolon
DECL|variable|my_NAME
id|MODULE_DESCRIPTION
c_func
(paren
id|my_NAME
)paren
suffix:semicolon
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
DECL|function|isense_init
r_int
id|__init
id|isense_init
c_func
(paren
r_void
)paren
(brace
id|show_mptmod_ver
c_func
(paren
id|my_NAME
comma
id|my_VERSION
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  Install our handler&n;&t; */
r_if
c_cond
(paren
id|mpt_register_ascqops_strings
c_func
(paren
op_amp
id|ASCQ_Table
(braket
l_int|0
)braket
comma
id|ASCQ_TableSize
comma
id|ScsiOpcodeString
)paren
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|MYNAM
l_string|&quot;: ERROR: Can&squot;t register with Fusion MPT base driver!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
id|MYNAM
l_string|&quot;: Registered SCSI-3 Opcodes &amp; ASC/ASCQ Strings&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
DECL|function|isense_exit
r_static
r_void
id|isense_exit
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef MODULE
id|mpt_deregister_ascqops_strings
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
id|MYNAM
l_string|&quot;: Deregistered SCSI-3 Opcodes &amp; ASC/ASCQ Strings&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|isense_init
id|module_init
c_func
(paren
id|isense_init
)paren
suffix:semicolon
DECL|variable|isense_exit
id|module_exit
c_func
(paren
id|isense_exit
)paren
suffix:semicolon
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
eof
