multiline_comment|/*&n;*&n;* mwavedd.c -- mwave device driver&n;*&n;*&n;* Written By: Mike Sullivan IBM Corporation&n;*&n;* Copyright (C) 1999 IBM Corporation&n;*&n;* This program is free software; you can redistribute it and/or modify&n;* it under the terms of the GNU General Public License as published by&n;* the Free Software Foundation; either version 2 of the License, or&n;* (at your option) any later version.&n;*&n;* This program is distributed in the hope that it will be useful,&n;* but WITHOUT ANY WARRANTY; without even the implied warranty of&n;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;* GNU General Public License for more details.&n;*&n;* NO WARRANTY&n;* THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;* CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;* LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;* solely responsible for determining the appropriateness of using and&n;* distributing the Program and assumes all risks associated with its&n;* exercise of rights under this Agreement, including but not limited to&n;* the risks and costs of program errors, damage to or loss of data,&n;* programs or equipment, and unavailability or interruption of operations.&n;*&n;* DISCLAIMER OF LIABILITY&n;* NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;* DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;* USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;* HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;*&n;* You should have received a copy of the GNU General Public License&n;* along with this program; if not, write to the Free Software&n;* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*&n;*&n;* 10/23/2000 - Alpha Release&n;*&t;First release to the public&n;*/
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#else
macro_line|#include &lt;asm/spinlock.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;smapi.h&quot;
macro_line|#include &quot;mwavedd.h&quot;
macro_line|#include &quot;3780i.h&quot;
macro_line|#include &quot;tp3780i.h&quot;
macro_line|#ifndef __exit
DECL|macro|__exit
mdefine_line|#define __exit
macro_line|#endif
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
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
r_static
r_int
id|mwave_get_info
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#else
r_static
r_int
id|mwave_read_proc
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|xlen
comma
r_int
id|unused
)paren
suffix:semicolon
DECL|variable|mwave_proc
r_static
r_struct
id|proc_dir_entry
id|mwave_proc
op_assign
(brace
l_int|0
comma
multiline_comment|/* unsigned short low_ino */
l_int|5
comma
multiline_comment|/* unsigned short namelen */
l_string|&quot;mwave&quot;
comma
multiline_comment|/* const char *name */
id|S_IFREG
op_or
id|S_IRUGO
comma
multiline_comment|/* mode_t mode */
l_int|1
comma
multiline_comment|/* nlink_t nlink */
l_int|0
comma
multiline_comment|/* uid_t uid */
l_int|0
comma
multiline_comment|/* gid_t gid */
l_int|0
comma
multiline_comment|/* unsigned long size */
l_int|NULL
comma
multiline_comment|/* struct inode_operations *ops */
op_amp
id|mwave_read_proc
multiline_comment|/* int (*get_info) (...) */
)brace
suffix:semicolon
macro_line|#endif
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
id|MODULE_PARM
c_func
(paren
id|mwave_debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mwave_3780i_irq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mwave_3780i_io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mwave_uart_irq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mwave_uart_io
comma
l_string|&quot;i&quot;
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
l_string|&quot;mwavedd::mwave_open, entry inode %x file %x&bslash;n&quot;
comma
(paren
r_int
)paren
id|inode
comma
(paren
r_int
)paren
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
id|MOD_INC_USE_COUNT
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
l_string|&quot;mwavedd::mwave_close, entry inode %x file %x&bslash;n&quot;
comma
(paren
r_int
)paren
id|inode
comma
(paren
r_int
)paren
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
id|MOD_DEC_USE_COUNT
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
id|PRINTK_5
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl, entry inode %x file %x cmd %x arg %x&bslash;n&quot;
comma
(paren
r_int
)paren
id|inode
comma
(paren
r_int
)paren
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
l_string|&quot;mwavedd::mwave_ioctl, IOCTL_MW_RESET calling tp3780I_ResetDSP&bslash;n&quot;
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
l_string|&quot;mwavedd::mwave_ioctl, IOCTL_MW_RESET retval %x from tp3780I_ResetDSP&bslash;n&quot;
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
l_string|&quot;mwavedd::mwave_ioctl, IOCTL_MW_RUN calling tp3780I_StartDSP&bslash;n&quot;
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
l_string|&quot;mwavedd::mwave_ioctl, IOCTL_MW_RUN retval %x from tp3780I_StartDSP&bslash;n&quot;
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
l_string|&quot;mwavedd::mwave_ioctl, IOCTL_MW_DSP_ABILITIES calling tp3780I_QueryAbilities&bslash;n&quot;
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
l_string|&quot;mwavedd::mwave_ioctl, IOCTL_MW_DSP_ABILITIES retval %x from tp3780I_QueryAbilities&bslash;n&quot;
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
(paren
r_char
op_star
)paren
id|ioarg
comma
(paren
r_char
op_star
)paren
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
l_string|&quot;mwavedd::mwave_ioctl, IOCTL_MW_DSP_ABILITIES exit retval %x&bslash;n&quot;
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
op_star
id|pusBuffer
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|rReadData
comma
(paren
r_char
op_star
)paren
id|ioarg
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
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_READ_DATA, size %lx, ioarg %lx pusBuffer %p&bslash;n&quot;
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
(paren
r_void
op_star
)paren
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
op_star
id|pusBuffer
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|rReadData
comma
(paren
r_char
op_star
)paren
id|ioarg
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
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_READ_INST, size %lx, ioarg %lx pusBuffer %p&bslash;n&quot;
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
op_star
id|pusBuffer
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|rWriteData
comma
(paren
r_char
op_star
)paren
id|ioarg
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
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_WRITE_DATA, size %lx, ioarg %lx pusBuffer %p&bslash;n&quot;
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
op_star
id|pusBuffer
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|rWriteData
comma
(paren
r_char
op_star
)paren
id|ioarg
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
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_WRITE_INST, size %lx, ioarg %lx pusBuffer %p&bslash;n&quot;
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
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_REGISTER_IPC ipcnum %x entry usIntCount %x&bslash;n&quot;
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
l_int|16
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd::mwave_ioctl: IOCTL_MW_REGISTER_IPC: Error: Invalid ipcnum %x&bslash;n&quot;
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
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
macro_line|#else
id|current-&gt;priority
op_assign
l_int|0x28
suffix:semicolon
multiline_comment|/* boost to provide priority timing */
macro_line|#endif
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_REGISTER_IPC ipcnum %x exit&bslash;n&quot;
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
id|spinlock_t
id|ipc_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|PRINTK_3
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_GET_IPC ipcnum %x, usIntCount %x&bslash;n&quot;
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
l_int|16
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd::mwave_ioctl: IOCTL_MW_GET_IPC: Error: Invalid ipcnum %x&bslash;n&quot;
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
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl, thread for ipc %x going to sleep&bslash;n&quot;
comma
id|ipcnum
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ipc_lock
comma
id|flags
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ipc_lock
comma
id|flags
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_GET_IPC ipcnum %x handling first int&bslash;n&quot;
comma
id|ipcnum
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* either 1st int has not yet occurred, or we have already handled the first int */
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|bIsHere
op_assign
id|TRUE
suffix:semicolon
id|interruptible_sleep_on
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
id|pDrvData-&gt;IPCs
(braket
id|ipcnum
)braket
dot
id|bIsHere
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ipc_lock
comma
id|flags
)paren
suffix:semicolon
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_GET_IPC ipcnum %x woke up and returning to application&bslash;n&quot;
comma
id|ipcnum
)paren
suffix:semicolon
)brace
id|PRINTK_2
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_GET_IPC, returning thread for ipc %x processing&bslash;n&quot;
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
l_string|&quot;mwavedd::mwave_ioctl IOCTL_MW_UNREGISTER_IPC ipcnum %x&bslash;n&quot;
comma
id|ipcnum
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ipcnum
OG
l_int|16
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd::mwave_ioctl: IOCTL_MW_UNREGISTER_IPC: Error: Invalid ipcnum %x&bslash;n&quot;
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
l_string|&quot;mwavedd::mwave_ioctl: Error: Unrecognized iocmd %x&bslash;n&quot;
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
l_string|&quot;mwavedd::mwave_read entry file %p, buf %p, count %x ppos %p&bslash;n&quot;
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
l_string|&quot;mwavedd::mwave_write entry file %p, buf %p, count %x ppos %p&bslash;n&quot;
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
l_string|&quot;mwavedd::register_serial_portandirq: Error: Illegal port %x&bslash;n&quot;
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
l_string|&quot;mwavedd::register_serial_portandirq: Error: Illegal irq %x&bslash;n&quot;
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
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
DECL|variable|mwave_fops
r_static
r_struct
id|file_operations
id|mwave_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|read
suffix:colon
id|mwave_read
comma
id|write
suffix:colon
id|mwave_write
comma
id|ioctl
suffix:colon
id|mwave_ioctl
comma
id|open
suffix:colon
id|mwave_open
comma
id|release
suffix:colon
id|mwave_close
)brace
suffix:semicolon
macro_line|#else
DECL|variable|mwave_fops
r_static
r_struct
id|file_operations
id|mwave_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek */
id|mwave_read
comma
multiline_comment|/* read */
id|mwave_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll */
id|mwave_ioctl
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|mwave_open
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* flush */
id|mwave_close
multiline_comment|/* release */
)brace
suffix:semicolon
macro_line|#endif
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
r_if
c_cond
(paren
id|pDrvData-&gt;bProcEntryCreated
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
id|remove_proc_entry
c_func
(paren
l_string|&quot;mwave&quot;
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#else
id|proc_unregister
c_func
(paren
op_amp
id|proc_root
comma
id|mwave_proc.low_ino
)paren
suffix:semicolon
macro_line|#endif
)brace
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
r_int
r_int
id|resultMiscRegister
suffix:semicolon
id|pMWAVE_DEVICE_DATA
id|pDrvData
op_assign
op_amp
id|mwave_s_mdd
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
id|PRINTK_1
c_func
(paren
id|TRACE_MWAVE
comma
l_string|&quot;mwavedd::mwave_init entry&bslash;n&quot;
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
id|pDrvData-&gt;bProcEntryCreated
op_assign
id|FALSE
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
l_int|16
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
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
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
macro_line|#endif
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
l_string|&quot;mwavedd::mwave_init, return from tp3780I_InitializeBoardData retval %x&bslash;n&quot;
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
l_string|&quot;mwavedd::mwave_init: Error: Failed to initialize board data&bslash;n&quot;
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
l_string|&quot;mwavedd::mwave_init, return from tp3780I_CalcResources retval %x&bslash;n&quot;
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
l_string|&quot;mwavedd:mwave_init: Error: Failed to calculate resources&bslash;n&quot;
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
l_string|&quot;mwavedd::mwave_init, return from tp3780I_ClaimResources retval %x&bslash;n&quot;
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
l_string|&quot;mwavedd:mwave_init: Error: Failed to claim resources&bslash;n&quot;
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
l_string|&quot;mwavedd::mwave_init, return from tp3780I_EnableDSP retval %x&bslash;n&quot;
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
l_string|&quot;mwavedd:mwave_init: Error: Failed to enable DSP&bslash;n&quot;
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
id|resultMiscRegister
op_assign
id|misc_register
c_func
(paren
op_amp
id|mwave_misc_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resultMiscRegister
OL
l_int|0
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd:mwave_init: Error: Failed to register misc device&bslash;n&quot;
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
l_string|&quot;mwavedd:mwave_init: Error: Failed to register serial driver&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_error
suffix:semicolon
)brace
multiline_comment|/* uart is registered */
r_if
c_cond
(paren
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
op_logical_neg
id|create_proc_info_entry
c_func
(paren
l_string|&quot;mwave&quot;
comma
l_int|0
comma
l_int|NULL
comma
id|mwave_get_info
)paren
macro_line|#else
id|proc_register
c_func
(paren
op_amp
id|proc_root
comma
op_amp
id|mwave_proc
)paren
macro_line|#endif
)paren
(brace
id|PRINTK_ERROR
c_func
(paren
id|KERN_ERR_MWAVE
l_string|&quot;mwavedd::mwave_init: Error: Failed to register /proc/mwave&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|cleanup_error
suffix:semicolon
)brace
id|pDrvData-&gt;bProcEntryCreated
op_assign
id|TRUE
suffix:semicolon
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
l_string|&quot;mwavedd::mwave_init: Error: Failed to initialize&bslash;n&quot;
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
multiline_comment|/*&n;* proc entry stuff added by Ian Pilcher &lt;pilcher@us.ibm.com&gt;&n;*/
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
DECL|function|mwave_get_info
r_static
r_int
id|mwave_get_info
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
)paren
(brace
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
op_assign
op_amp
id|mwave_s_mdd.rBDData.rDspSettings
suffix:semicolon
r_char
op_star
id|out
op_assign
id|buf
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;3780i_IRQ %i&bslash;n&quot;
comma
id|pSettings-&gt;usDspIrq
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;3780i_DMA %i&bslash;n&quot;
comma
id|pSettings-&gt;usDspDma
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;3780i_IO  %#.4x&bslash;n&quot;
comma
id|pSettings-&gt;usDspBaseIO
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;UART_IRQ  %i&bslash;n&quot;
comma
id|pSettings-&gt;usUartIrq
)paren
suffix:semicolon
id|out
op_add_assign
id|sprintf
c_func
(paren
id|out
comma
l_string|&quot;UART_IO   %#.4x&bslash;n&quot;
comma
id|pSettings-&gt;usUartBaseIO
)paren
suffix:semicolon
r_return
id|out
op_minus
id|buf
suffix:semicolon
)brace
macro_line|#else /* kernel version &lt; 2.4.0 */
DECL|function|mwave_read_proc
r_static
r_int
id|mwave_read_proc
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|xlen
comma
r_int
id|unused
)paren
(brace
id|DSP_3780I_CONFIG_SETTINGS
op_star
id|pSettings
op_assign
op_amp
id|mwave_s_mdd.rBDData.rDspSettings
suffix:semicolon
r_int
id|len
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;3780i_IRQ %i&bslash;n&quot;
comma
id|pSettings-&gt;usDspIrq
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|len
)braket
comma
l_string|&quot;3780i_DMA %i&bslash;n&quot;
comma
id|pSettings-&gt;usDspDma
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|len
)braket
comma
l_string|&quot;3780i_IO  %#.4x&bslash;n&quot;
comma
id|pSettings-&gt;usDspBaseIO
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|len
)braket
comma
l_string|&quot;UART_IRQ  %i&bslash;n&quot;
comma
id|pSettings-&gt;usUartIrq
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|len
)braket
comma
l_string|&quot;UART_IO   %#.4x&bslash;n&quot;
comma
id|pSettings-&gt;usUartBaseIO
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
macro_line|#endif
eof
