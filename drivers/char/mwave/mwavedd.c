multiline_comment|/*&n;*&n;* mwavedd.c -- mwave device driver&n;*&n;*&n;* Written By: Mike Sullivan IBM Corporation&n;*&n;* Copyright (C) 1999 IBM Corporation&n;*&n;* This program is free software; you can redistribute it and/or modify&n;* it under the terms of the GNU General Public License as published by&n;* the Free Software Foundation; either version 2 of the License, or&n;* (at your option) any later version.&n;*&n;* This program is distributed in the hope that it will be useful,&n;* but WITHOUT ANY WARRANTY; without even the implied warranty of&n;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;* GNU General Public License for more details.&n;*&n;* NO WARRANTY&n;* THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;* CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;* LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;* solely responsible for determining the appropriateness of using and&n;* distributing the Program and assumes all risks associated with its&n;* exercise of rights under this Agreement, including but not limited to&n;* the risks and costs of program errors, damage to or loss of data,&n;* programs or equipment, and unavailability or interruption of operations.&n;*&n;* DISCLAIMER OF LIABILITY&n;* NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;* DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;* USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;* HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;*&n;* You should have received a copy of the GNU General Public License&n;* along with this program; if not, write to the Free Software&n;* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*&n;*&n;* 10/23/2000 - Alpha Release&n;*&t;First release to the public&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;smapi.h&quot;
macro_line|#include &quot;mwavedd.h&quot;
macro_line|#include &quot;3780i.h&quot;
macro_line|#include &quot;tp3780i.h&quot;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;3780i Advanced Communications Processor (Mwave) driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Mike Sullivan and Paul Schroeder&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;* These parameters support the setting of MWave resources. Note that no&n;* checks are made against other devices (ie. superio) for conflicts.&n;* We&squot;ll depend on users using the tpctl utility to do that for now&n;*/
DECL|variable|mwave_debug
r_int
id|mwave_debug
op_assign
l_int|0
suffix:semicolon
DECL|variable|mwave_3780i_irq
r_int
id|mwave_3780i_irq
op_assign
l_int|0
suffix:semicolon
DECL|variable|mwave_3780i_io
r_int
id|mwave_3780i_io
op_assign
l_int|0
suffix:semicolon
DECL|variable|mwave_uart_irq
r_int
id|mwave_uart_irq
op_assign
l_int|0
suffix:semicolon
DECL|variable|mwave_uart_io
r_int
id|mwave_uart_io
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|mwave_debug
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|mwave_3780i_irq
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|mwave_3780i_io
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|mwave_uart_irq
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|mwave_uart_io
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
r_static
r_int
id|mwave_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_static
r_int
id|mwave_close
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_static
r_int
id|mwave_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|iocmd
comma
r_int
r_int
id|ioarg
)paren
suffix:semicolon
DECL|variable|mwave_s_mdd
id|MWAVE_DEVICE_DATA
id|mwave_s_mdd
suffix:semicolon
DECL|function|mwave_open
r_static
r_int
id|mwave_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|PRINTK_3
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_open, entry inode %p file %p&bslash;n&quot;
comma
id|inode
comma
id|file
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_open, exit return retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|mwave_close
r_static
r_int
id|mwave_close
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|PRINTK_3
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_close, entry inode %p file %p&bslash;n&quot;
comma
id|inode
comma
id|file
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_close, exit retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|mwave_ioctl
r_static
r_int
id|mwave_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|iocmd
comma
r_int
r_int
id|ioarg
)paren
(brace
r_int
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|pMWAVE_DEVICE_DATA
id|pDrvData
op_assign
op_amp
id|mwave_s_mdd
suffix:semicolon
r_void
id|__user
op_star
id|arg
op_assign
(paren
r_void
id|__user
op_star
)paren
id|ioarg
suffix:semicolon
id|PRINTK_5
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl, entry inode %p file %p cmd %x arg %x&bslash;n&quot;
comma
id|inode
comma
id|file
comma
id|iocmd
comma
(paren
r_int
)paren
id|ioarg
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|iocmd
)paren
(brace
r_case
id|IOCTL_MW_RESET
suffix:colon
id|PRINTK_1
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl, IOCTL_MW_RESET&quot;
l_string|&quot; calling tp3780I_ResetDSP&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
id|tp3780I_ResetDSP
c_func
(paren
op_amp
id|pDrvData-&gt;rBDData
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl, IOCTL_MW_RESET&quot;
l_string|&quot; retval %x from tp3780I_ResetDSP&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOCTL_MW_RUN
suffix:colon
id|PRINTK_1
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl, IOCTL_MW_RUN&quot;
l_string|&quot; calling tp3780I_StartDSP&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
id|tp3780I_StartDSP
c_func
(paren
op_amp
id|pDrvData-&gt;rBDData
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl, IOCTL_MW_RUN&quot;
l_string|&quot; retval %x from tp3780I_StartDSP&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IOCTL_MW_DSP_ABILITIES
suffix:colon
(brace
id|MW_ABILITIES
id|rAbilities
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl,&quot;
l_string|&quot; IOCTL_MW_DSP_ABILITIES calling&quot;
l_string|&quot; tp3780I_QueryAbilities&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
id|tp3780I_QueryAbilities
c_func
(paren
op_amp
id|pDrvData-&gt;rBDData
comma
op_amp
id|rAbilities
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl, IOCTL_MW_DSP_ABILITIES&quot;
l_string|&quot; retval %x from tp3780I_QueryAbilities&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|rAbilities
comma
r_sizeof
(paren
id|MW_ABILITIES
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl, IOCTL_MW_DSP_ABILITIES&quot;
l_string|&quot; exit retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IOCTL_MW_READ_DATA
suffix:colon
r_case
id|IOCTL_MW_READCLEAR_DATA
suffix:colon
(brace
id|MW_READWRITE
id|rReadData
suffix:semicolon
r_int
r_int
id|__user
op_star
id|pusBuffer
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rReadData
comma
id|arg
comma
r_sizeof
(paren
id|MW_READWRITE
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|pusBuffer
op_assign
(paren
r_int
r_int
id|__user
op_star
)paren
(paren
id|rReadData.pBuf
)paren
suffix:semicolon
id|PRINTK_4
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_READ_DATA,&quot;
l_string|&quot; size %lx, ioarg %lx pusBuffer %p&bslash;n&quot;
comma
id|rReadData.ulDataLength
comma
id|ioarg
comma
id|pusBuffer
)paren
suffix:semicolon
id|retval
op_assign
id|tp3780I_ReadWriteDspDStore
c_func
(paren
op_amp
id|pDrvData-&gt;rBDData
comma
id|iocmd
comma
id|pusBuffer
comma
id|rReadData.ulDataLength
comma
id|rReadData.usDspAddress
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IOCTL_MW_READ_INST
suffix:colon
(brace
id|MW_READWRITE
id|rReadData
suffix:semicolon
r_int
r_int
id|__user
op_star
id|pusBuffer
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rReadData
comma
id|arg
comma
r_sizeof
(paren
id|MW_READWRITE
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|pusBuffer
op_assign
(paren
r_int
r_int
id|__user
op_star
)paren
(paren
id|rReadData.pBuf
)paren
suffix:semicolon
id|PRINTK_4
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_READ_INST,&quot;
l_string|&quot; size %lx, ioarg %lx pusBuffer %p&bslash;n&quot;
comma
id|rReadData.ulDataLength
op_div
l_int|2
comma
id|ioarg
comma
id|pusBuffer
)paren
suffix:semicolon
id|retval
op_assign
id|tp3780I_ReadWriteDspDStore
c_func
(paren
op_amp
id|pDrvData-&gt;rBDData
comma
id|iocmd
comma
id|pusBuffer
comma
id|rReadData.ulDataLength
op_div
l_int|2
comma
id|rReadData.usDspAddress
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IOCTL_MW_WRITE_DATA
suffix:colon
(brace
id|MW_READWRITE
id|rWriteData
suffix:semicolon
r_int
r_int
id|__user
op_star
id|pusBuffer
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rWriteData
comma
id|arg
comma
r_sizeof
(paren
id|MW_READWRITE
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|pusBuffer
op_assign
(paren
r_int
r_int
id|__user
op_star
)paren
(paren
id|rWriteData.pBuf
)paren
suffix:semicolon
id|PRINTK_4
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_WRITE_DATA,&quot;
l_string|&quot; size %lx, ioarg %lx pusBuffer %p&bslash;n&quot;
comma
id|rWriteData.ulDataLength
comma
id|ioarg
comma
id|pusBuffer
)paren
suffix:semicolon
id|retval
op_assign
id|tp3780I_ReadWriteDspDStore
c_func
(paren
op_amp
id|pDrvData-&gt;rBDData
comma
id|iocmd
comma
id|pusBuffer
comma
id|rWriteData.ulDataLength
comma
id|rWriteData.usDspAddress
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IOCTL_MW_WRITE_INST
suffix:colon
(brace
id|MW_READWRITE
id|rWriteData
suffix:semicolon
r_int
r_int
id|__user
op_star
id|pusBuffer
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rWriteData
comma
id|arg
comma
r_sizeof
(paren
id|MW_READWRITE
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|pusBuffer
op_assign
(paren
r_int
r_int
id|__user
op_star
)paren
(paren
id|rWriteData.pBuf
)paren
suffix:semicolon
id|PRINTK_4
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_WRITE_INST,&quot;
l_string|&quot; size %lx, ioarg %lx pusBuffer %p&bslash;n&quot;
comma
id|rWriteData.ulDataLength
comma
id|ioarg
comma
id|pusBuffer
)paren
suffix:semicolon
id|retval
op_assign
id|tp3780I_ReadWriteDspIStore
c_func
(paren
op_amp
id|pDrvData-&gt;rBDData
comma
id|iocmd
comma
id|pusBuffer
comma
id|rWriteData.ulDataLength
comma
id|rWriteData.usDspAddress
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IOCTL_MW_REGISTER_IPC
suffix:colon
(brace
r_int
r_int
id|ipcnum
op_assign
(paren
r_int
r_int
)paren
id|ioarg
suffix:semicolon
id|PRINTK_3
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_REGISTER_IPC&quot;
l_string|&quot; ipcnum %x entry usIntCount %x&bslash;n&quot;
comma
id|ipcnum
comma
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|usIntCount
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipcnum
OG
id|ARRAY_SIZE
c_func
(paren
id|pDrvData-&gt;IPCs
)paren
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd::mwave_ioctl:&quot;
l_string|&quot; IOCTL_MW_REGISTER_IPC:&quot;
l_string|&quot; Error: Invalid ipcnum %x&bslash;n&quot;
comma
id|ipcnum
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|bIsHere
op_assign
id|FALSE
suffix:semicolon
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|bIsEnabled
op_assign
id|TRUE
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_REGISTER_IPC&quot;
l_string|&quot; ipcnum %x exit&bslash;n&quot;
comma
id|ipcnum
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|IOCTL_MW_GET_IPC
suffix:colon
(brace
r_int
r_int
id|ipcnum
op_assign
(paren
r_int
r_int
)paren
id|ioarg
suffix:semicolon
id|PRINTK_3
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_GET_IPC&quot;
l_string|&quot; ipcnum %x, usIntCount %x&bslash;n&quot;
comma
id|ipcnum
comma
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|usIntCount
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipcnum
OG
id|ARRAY_SIZE
c_func
(paren
id|pDrvData-&gt;IPCs
)paren
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd::mwave_ioctl:&quot;
l_string|&quot; IOCTL_MW_GET_IPC: Error:&quot;
l_string|&quot; Invalid ipcnum %x&bslash;n&quot;
comma
id|ipcnum
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|bIsEnabled
op_eq
id|TRUE
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl, thread for&quot;
l_string|&quot; ipc %x going to sleep&bslash;n&quot;
comma
id|ipcnum
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|ipc_wait_queue
comma
op_amp
id|wait
)paren
suffix:semicolon
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|bIsHere
op_assign
id|TRUE
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
multiline_comment|/* check whether an event was signalled by */
multiline_comment|/* the interrupt handler while we were gone */
r_if
c_cond
(paren
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|usIntCount
op_eq
l_int|1
)paren
(brace
multiline_comment|/* first int has occurred (race condition) */
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|usIntCount
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* first int has been handled */
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl&quot;
l_string|&quot; IOCTL_MW_GET_IPC ipcnum %x&quot;
l_string|&quot; handling first int&bslash;n&quot;
comma
id|ipcnum
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* either 1st int has not yet occurred, or we have already handled the first int */
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|usIntCount
op_eq
l_int|1
)paren
(brace
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|usIntCount
op_assign
l_int|2
suffix:semicolon
)brace
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl&quot;
l_string|&quot; IOCTL_MW_GET_IPC ipcnum %x&quot;
l_string|&quot; woke up and returning to&quot;
l_string|&quot; application&bslash;n&quot;
comma
id|ipcnum
)paren
suffix:semicolon
)brace
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|bIsHere
op_assign
id|FALSE
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|ipc_wait_queue
comma
op_amp
id|wait
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_GET_IPC,&quot;
l_string|&quot; returning thread for ipc %x&quot;
l_string|&quot; processing&bslash;n&quot;
comma
id|ipcnum
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|IOCTL_MW_UNREGISTER_IPC
suffix:colon
(brace
r_int
r_int
id|ipcnum
op_assign
(paren
r_int
r_int
)paren
id|ioarg
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_UNREGISTER_IPC&quot;
l_string|&quot; ipcnum %x&bslash;n&quot;
comma
id|ipcnum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipcnum
OG
id|ARRAY_SIZE
c_func
(paren
id|pDrvData-&gt;IPCs
)paren
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd::mwave_ioctl:&quot;
l_string|&quot; IOCTL_MW_UNREGISTER_IPC:&quot;
l_string|&quot; Error: Invalid ipcnum %x&bslash;n&quot;
comma
id|ipcnum
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|bIsEnabled
op_eq
id|TRUE
)paren
(brace
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|bIsEnabled
op_assign
id|FALSE
suffix:semicolon
r_if
c_cond
(paren
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|bIsHere
op_eq
id|TRUE
)paren
(brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|ipc_wait_queue
)paren
suffix:semicolon
)brace
)brace
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd::mwave_ioctl:&quot;
l_string|&quot; Error: Unrecognized iocmd %x&bslash;n&quot;
comma
id|iocmd
)paren
suffix:semicolon
r_return
op_minus
id|ENOTTY
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* switch */
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl, exit retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|mwave_read
r_static
id|ssize_t
id|mwave_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
id|PRINTK_5
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_read entry file %p, buf %p, count %zx ppos %p&bslash;n&quot;
comma
id|file
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|mwave_write
r_static
id|ssize_t
id|mwave_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
id|PRINTK_5
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_write entry file %p, buf %p,&quot;
l_string|&quot; count %zx ppos %p&bslash;n&quot;
comma
id|file
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|register_serial_portandirq
r_static
r_int
id|register_serial_portandirq
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|irq
)paren
(brace
r_struct
id|serial_struct
id|serial
suffix:semicolon
r_switch
c_cond
(paren
id|port
)paren
(brace
r_case
l_int|0x3f8
suffix:colon
r_case
l_int|0x2f8
suffix:colon
r_case
l_int|0x3e8
suffix:colon
r_case
l_int|0x2e8
suffix:colon
multiline_comment|/* OK */
r_break
suffix:semicolon
r_default
suffix:colon
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd::register_serial_portandirq:&quot;
l_string|&quot; Error: Illegal port %x&bslash;n&quot;
comma
id|port
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* switch */
multiline_comment|/* port is okay */
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
r_case
l_int|7
suffix:colon
multiline_comment|/* OK */
r_break
suffix:semicolon
r_default
suffix:colon
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd::register_serial_portandirq:&quot;
l_string|&quot; Error: Illegal irq %x&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* switch */
multiline_comment|/* irq is okay */
id|memset
c_func
(paren
op_amp
id|serial
comma
l_int|0
comma
r_sizeof
(paren
id|serial
)paren
)paren
suffix:semicolon
id|serial.port
op_assign
id|port
suffix:semicolon
id|serial.irq
op_assign
id|irq
suffix:semicolon
id|serial.flags
op_assign
id|ASYNC_SHARE_IRQ
suffix:semicolon
r_return
id|register_serial
c_func
(paren
op_amp
id|serial
)paren
suffix:semicolon
)brace
DECL|variable|mwave_fops
r_static
r_struct
id|file_operations
id|mwave_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|mwave_read
comma
dot
id|write
op_assign
id|mwave_write
comma
dot
id|ioctl
op_assign
id|mwave_ioctl
comma
dot
id|open
op_assign
id|mwave_open
comma
dot
id|release
op_assign
id|mwave_close
)brace
suffix:semicolon
DECL|variable|mwave_misc_dev
r_static
r_struct
id|miscdevice
id|mwave_misc_dev
op_assign
(brace
id|MWAVE_MINOR
comma
l_string|&quot;mwave&quot;
comma
op_amp
id|mwave_fops
)brace
suffix:semicolon
macro_line|#if 0 /* totally b0rked */
multiline_comment|/*&n; * sysfs support &lt;paulsch@us.ibm.com&gt;&n; */
r_struct
id|device
id|mwave_device
suffix:semicolon
multiline_comment|/* Prevent code redundancy, create a macro for mwave_show_* functions. */
mdefine_line|#define mwave_show_function(attr_name, format_string, field)&t;&t;&bslash;&n;static ssize_t mwave_show_##attr_name(struct device *dev, char *buf)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;DSP_3780I_CONFIG_SETTINGS *pSettings =&t;&t;&t;&t;&bslash;&n;&t;&t;&amp;mwave_s_mdd.rBDData.rDspSettings;&t;&t;&t;&bslash;&n;        return sprintf(buf, format_string, pSettings-&gt;field);&t;&t;&bslash;&n;}
multiline_comment|/* All of our attributes are read attributes. */
mdefine_line|#define mwave_dev_rd_attr(attr_name, format_string, field)&t;&t;&bslash;&n;&t;mwave_show_function(attr_name, format_string, field)&t;&t;&bslash;&n;static DEVICE_ATTR(attr_name, S_IRUGO, mwave_show_##attr_name, NULL)
id|mwave_dev_rd_attr
(paren
l_int|3780
id|i_dma
comma
l_string|&quot;%i&bslash;n&quot;
comma
id|usDspDma
)paren
suffix:semicolon
id|mwave_dev_rd_attr
(paren
l_int|3780
id|i_irq
comma
l_string|&quot;%i&bslash;n&quot;
comma
id|usDspIrq
)paren
suffix:semicolon
id|mwave_dev_rd_attr
(paren
l_int|3780
id|i_io
comma
l_string|&quot;%#.4x&bslash;n&quot;
comma
id|usDspBaseIO
)paren
suffix:semicolon
id|mwave_dev_rd_attr
(paren
id|uart_irq
comma
l_string|&quot;%i&bslash;n&quot;
comma
id|usUartIrq
)paren
suffix:semicolon
id|mwave_dev_rd_attr
(paren
id|uart_io
comma
l_string|&quot;%#.4x&bslash;n&quot;
comma
id|usUartBaseIO
)paren
suffix:semicolon
r_static
r_struct
id|device_attribute
op_star
r_const
id|mwave_dev_attrs
(braket
)braket
op_assign
(brace
op_amp
id|dev_attr_3780i_dma
comma
op_amp
id|dev_attr_3780i_irq
comma
op_amp
id|dev_attr_3780i_io
comma
op_amp
id|dev_attr_uart_irq
comma
op_amp
id|dev_attr_uart_io
comma
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;* mwave_init is called on module load&n;*&n;* mwave_exit is called on module unload&n;* mwave_exit is also used to clean up after an aborted mwave_init&n;*/
DECL|function|mwave_exit
r_static
r_void
id|mwave_exit
c_func
(paren
r_void
)paren
(brace
id|pMWAVE_DEVICE_DATA
id|pDrvData
op_assign
op_amp
id|mwave_s_mdd
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_exit entry&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#if 0
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pDrvData-&gt;nr_registered_attrs
suffix:semicolon
id|i
op_increment
)paren
id|device_remove_file
c_func
(paren
op_amp
id|mwave_device
comma
id|mwave_dev_attrs
(braket
id|i
)braket
)paren
suffix:semicolon
id|pDrvData-&gt;nr_registered_attrs
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pDrvData-&gt;device_registered
)paren
(brace
id|device_unregister
c_func
(paren
op_amp
id|mwave_device
)paren
suffix:semicolon
id|pDrvData-&gt;device_registered
op_assign
id|FALSE
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|pDrvData-&gt;sLine
op_ge
l_int|0
)paren
(brace
id|unregister_serial
c_func
(paren
id|pDrvData-&gt;sLine
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pDrvData-&gt;bMwaveDevRegistered
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|mwave_misc_dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pDrvData-&gt;bDSPEnabled
)paren
(brace
id|tp3780I_DisableDSP
c_func
(paren
op_amp
id|pDrvData-&gt;rBDData
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pDrvData-&gt;bResourcesClaimed
)paren
(brace
id|tp3780I_ReleaseResources
c_func
(paren
op_amp
id|pDrvData-&gt;rBDData
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pDrvData-&gt;bBDInitialized
)paren
(brace
id|tp3780I_Cleanup
c_func
(paren
op_amp
id|pDrvData-&gt;rBDData
)paren
suffix:semicolon
)brace
id|PRINTK_1
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_exit exit&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|mwave_exit
id|module_exit
c_func
(paren
id|mwave_exit
)paren
suffix:semicolon
DECL|function|mwave_init
r_static
r_int
id|__init
id|mwave_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
id|pMWAVE_DEVICE_DATA
id|pDrvData
op_assign
op_amp
id|mwave_s_mdd
suffix:semicolon
id|PRINTK_1
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_init entry&bslash;n&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|mwave_s_mdd
comma
l_int|0
comma
r_sizeof
(paren
id|MWAVE_DEVICE_DATA
)paren
)paren
suffix:semicolon
id|pDrvData-&gt;bBDInitialized
op_assign
id|FALSE
suffix:semicolon
id|pDrvData-&gt;bResourcesClaimed
op_assign
id|FALSE
suffix:semicolon
id|pDrvData-&gt;bDSPEnabled
op_assign
id|FALSE
suffix:semicolon
id|pDrvData-&gt;bDSPReset
op_assign
id|FALSE
suffix:semicolon
id|pDrvData-&gt;bMwaveDevRegistered
op_assign
id|FALSE
suffix:semicolon
id|pDrvData-&gt;sLine
op_assign
op_minus
l_int|1
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
id|ARRAY_SIZE
c_func
(paren
id|pDrvData-&gt;IPCs
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pDrvData-&gt;IPCs
(braket
id|i
)braket
dot
id|bIsEnabled
op_assign
id|FALSE
suffix:semicolon
id|pDrvData-&gt;IPCs
(braket
id|i
)braket
dot
id|bIsHere
op_assign
id|FALSE
suffix:semicolon
id|pDrvData-&gt;IPCs
(braket
id|i
)braket
dot
id|usIntCount
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no ints received yet */
id|init_waitqueue_head
c_func
(paren
op_amp
id|pDrvData-&gt;IPCs
(braket
id|i
)braket
dot
id|ipc_wait_queue
)paren
suffix:semicolon
)brace
id|retval
op_assign
id|tp3780I_InitializeBoardData
c_func
(paren
op_amp
id|pDrvData-&gt;rBDData
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_init, return from tp3780I_InitializeBoardData&quot;
l_string|&quot; retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd::mwave_init: Error:&quot;
l_string|&quot; Failed to initialize board data&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_error
suffix:semicolon
)brace
id|pDrvData-&gt;bBDInitialized
op_assign
id|TRUE
suffix:semicolon
id|retval
op_assign
id|tp3780I_CalcResources
c_func
(paren
op_amp
id|pDrvData-&gt;rBDData
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_init, return from tp3780I_CalcResources&quot;
l_string|&quot; retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd:mwave_init: Error:&quot;
l_string|&quot; Failed to calculate resources&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_error
suffix:semicolon
)brace
id|retval
op_assign
id|tp3780I_ClaimResources
c_func
(paren
op_amp
id|pDrvData-&gt;rBDData
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_init, return from tp3780I_ClaimResources&quot;
l_string|&quot; retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd:mwave_init: Error:&quot;
l_string|&quot; Failed to claim resources&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_error
suffix:semicolon
)brace
id|pDrvData-&gt;bResourcesClaimed
op_assign
id|TRUE
suffix:semicolon
id|retval
op_assign
id|tp3780I_EnableDSP
c_func
(paren
op_amp
id|pDrvData-&gt;rBDData
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_init, return from tp3780I_EnableDSP&quot;
l_string|&quot; retval %x&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd:mwave_init: Error:&quot;
l_string|&quot; Failed to enable DSP&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_error
suffix:semicolon
)brace
id|pDrvData-&gt;bDSPEnabled
op_assign
id|TRUE
suffix:semicolon
r_if
c_cond
(paren
id|misc_register
c_func
(paren
op_amp
id|mwave_misc_dev
)paren
OL
l_int|0
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd:mwave_init: Error:&quot;
l_string|&quot; Failed to register misc device&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_error
suffix:semicolon
)brace
id|pDrvData-&gt;bMwaveDevRegistered
op_assign
id|TRUE
suffix:semicolon
id|pDrvData-&gt;sLine
op_assign
id|register_serial_portandirq
c_func
(paren
id|pDrvData-&gt;rBDData.rDspSettings.usUartBaseIO
comma
id|pDrvData-&gt;rBDData.rDspSettings.usUartIrq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pDrvData-&gt;sLine
OL
l_int|0
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd:mwave_init: Error:&quot;
l_string|&quot; Failed to register serial driver&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_error
suffix:semicolon
)brace
multiline_comment|/* uart is registered */
macro_line|#if 0
multiline_comment|/* sysfs */
id|memset
c_func
(paren
op_amp
id|mwave_device
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|device
)paren
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|mwave_device.bus_id
comma
id|BUS_ID_SIZE
comma
l_string|&quot;mwave&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|device_register
c_func
(paren
op_amp
id|mwave_device
)paren
)paren
r_goto
id|cleanup_error
suffix:semicolon
id|pDrvData-&gt;device_registered
op_assign
id|TRUE
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
id|ARRAY_SIZE
c_func
(paren
id|mwave_dev_attrs
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|device_create_file
c_func
(paren
op_amp
id|mwave_device
comma
id|mwave_dev_attrs
(braket
id|i
)braket
)paren
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd:mwave_init: Error:&quot;
l_string|&quot; Failed to create sysfs file %s&bslash;n&quot;
comma
id|mwave_dev_attrs
(braket
id|i
)braket
op_member_access_from_pointer
id|attr.name
)paren
suffix:semicolon
r_goto
id|cleanup_error
suffix:semicolon
)brace
id|pDrvData-&gt;nr_registered_attrs
op_increment
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* SUCCESS! */
r_return
l_int|0
suffix:semicolon
id|cleanup_error
suffix:colon
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd::mwave_init: Error:&quot;
l_string|&quot; Failed to initialize&bslash;n&quot;
)paren
suffix:semicolon
id|mwave_exit
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* clean up */
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|variable|mwave_init
id|module_init
c_func
(paren
id|mwave_init
)paren
suffix:semicolon
eof
