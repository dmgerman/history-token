multiline_comment|/*&n;*&n;* mwavedd.h -- declarations for mwave device driver&n;*&n;*&n;* Written By: Mike Sullivan IBM Corporation&n;*&n;* Copyright (C) 1999 IBM Corporation&n;*&n;* This program is free software; you can redistribute it and/or modify&n;* it under the terms of the GNU General Public License as published by&n;* the Free Software Foundation; either version 2 of the License, or&n;* (at your option) any later version.&n;*&n;* This program is distributed in the hope that it will be useful,&n;* but WITHOUT ANY WARRANTY; without even the implied warranty of&n;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;* GNU General Public License for more details.&n;*&n;* NO WARRANTY&n;* THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;* CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;* LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;* solely responsible for determining the appropriateness of using and&n;* distributing the Program and assumes all risks associated with its&n;* exercise of rights under this Agreement, including but not limited to&n;* the risks and costs of program errors, damage to or loss of data,&n;* programs or equipment, and unavailability or interruption of operations.&n;*&n;* DISCLAIMER OF LIABILITY&n;* NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;* DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;* USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;* HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;*&n;* You should have received a copy of the GNU General Public License&n;* along with this program; if not, write to the Free Software&n;* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*&n;*&n;* 10/23/2000 - Alpha Release&n;*&t;First release to the public&n;*/
macro_line|#ifndef _LINUX_MWAVEDD_H
DECL|macro|_LINUX_MWAVEDD_H
mdefine_line|#define _LINUX_MWAVEDD_H
macro_line|#include &quot;3780i.h&quot;
macro_line|#include &quot;tp3780i.h&quot;
macro_line|#include &quot;mwavepub.h&quot;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_int
id|mwave_debug
suffix:semicolon
r_extern
r_int
id|mwave_3780i_irq
suffix:semicolon
r_extern
r_int
id|mwave_3780i_io
suffix:semicolon
r_extern
r_int
id|mwave_uart_irq
suffix:semicolon
r_extern
r_int
id|mwave_uart_io
suffix:semicolon
DECL|macro|PRINTK_ERROR
mdefine_line|#define PRINTK_ERROR printk
DECL|macro|KERN_ERR_MWAVE
mdefine_line|#define KERN_ERR_MWAVE KERN_ERR &quot;mwave: &quot;
DECL|macro|TRACE_MWAVE
mdefine_line|#define TRACE_MWAVE     0x0001
DECL|macro|TRACE_SMAPI
mdefine_line|#define TRACE_SMAPI     0x0002
DECL|macro|TRACE_3780I
mdefine_line|#define TRACE_3780I     0x0004
DECL|macro|TRACE_TP3780I
mdefine_line|#define TRACE_TP3780I   0x0008
macro_line|#ifdef MW_TRACE
DECL|macro|PRINTK_1
mdefine_line|#define PRINTK_1(f,s)                       &bslash;&n;  if (f &amp; (mwave_debug)) {                  &bslash;&n;    printk(s);                              &bslash;&n;  }
DECL|macro|PRINTK_2
mdefine_line|#define PRINTK_2(f,s,v1)                    &bslash;&n;  if (f &amp; (mwave_debug)) {                  &bslash;&n;    printk(s,v1);                           &bslash;&n;  }
DECL|macro|PRINTK_3
mdefine_line|#define PRINTK_3(f,s,v1,v2)                 &bslash;&n;  if (f &amp; (mwave_debug)) {                  &bslash;&n;    printk(s,v1,v2);                        &bslash;&n;  }
DECL|macro|PRINTK_4
mdefine_line|#define PRINTK_4(f,s,v1,v2,v3)              &bslash;&n;  if (f &amp; (mwave_debug)) {                  &bslash;&n;    printk(s,v1,v2,v3);                     &bslash;&n;  }
DECL|macro|PRINTK_5
mdefine_line|#define PRINTK_5(f,s,v1,v2,v3,v4)           &bslash;&n;  if (f &amp; (mwave_debug)) {                  &bslash;&n;    printk(s,v1,v2,v3,v4);                  &bslash;&n;  }
DECL|macro|PRINTK_6
mdefine_line|#define PRINTK_6(f,s,v1,v2,v3,v4,v5)        &bslash;&n;  if (f &amp; (mwave_debug)) {                  &bslash;&n;    printk(s,v1,v2,v3,v4,v5);               &bslash;&n;  }
DECL|macro|PRINTK_7
mdefine_line|#define PRINTK_7(f,s,v1,v2,v3,v4,v5,v6)     &bslash;&n;  if (f &amp; (mwave_debug)) {                  &bslash;&n;    printk(s,v1,v2,v3,v4,v5,v6);            &bslash;&n;  }
DECL|macro|PRINTK_8
mdefine_line|#define PRINTK_8(f,s,v1,v2,v3,v4,v5,v6,v7)  &bslash;&n;  if (f &amp; (mwave_debug)) {                  &bslash;&n;    printk(s,v1,v2,v3,v4,v5,v6,v7);         &bslash;&n;  }
macro_line|#else
DECL|macro|PRINTK_1
mdefine_line|#define PRINTK_1(f,s)
DECL|macro|PRINTK_2
mdefine_line|#define PRINTK_2(f,s,v1)
DECL|macro|PRINTK_3
mdefine_line|#define PRINTK_3(f,s,v1,v2)
DECL|macro|PRINTK_4
mdefine_line|#define PRINTK_4(f,s,v1,v2,v3)
DECL|macro|PRINTK_5
mdefine_line|#define PRINTK_5(f,s,v1,v2,v3,v4)
DECL|macro|PRINTK_6
mdefine_line|#define PRINTK_6(f,s,v1,v2,v3,v4,v5)
DECL|macro|PRINTK_7
mdefine_line|#define PRINTK_7(f,s,v1,v2,v3,v4,v5,v6)
DECL|macro|PRINTK_8
mdefine_line|#define PRINTK_8(f,s,v1,v2,v3,v4,v5,v6,v7)
macro_line|#endif
DECL|struct|_MWAVE_IPC
r_typedef
r_struct
id|_MWAVE_IPC
(brace
DECL|member|usIntCount
r_int
r_int
id|usIntCount
suffix:semicolon
multiline_comment|/* 0=none, 1=first, 2=greater than 1st */
DECL|member|bIsEnabled
id|BOOLEAN
id|bIsEnabled
suffix:semicolon
DECL|member|bIsHere
id|BOOLEAN
id|bIsHere
suffix:semicolon
multiline_comment|/* entry spin lock */
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
DECL|member|ipc_wait_queue
id|wait_queue_head_t
id|ipc_wait_queue
suffix:semicolon
macro_line|#else
DECL|member|ipc_wait_queue
r_struct
id|wait_queue
op_star
id|ipc_wait_queue
suffix:semicolon
macro_line|#endif
DECL|typedef|MWAVE_IPC
)brace
id|MWAVE_IPC
suffix:semicolon
DECL|struct|_MWAVE_DEVICE_DATA
r_typedef
r_struct
id|_MWAVE_DEVICE_DATA
(brace
DECL|member|rBDData
id|THINKPAD_BD_DATA
id|rBDData
suffix:semicolon
multiline_comment|/* board driver&squot;s data area */
DECL|member|ulIPCSource_ISR
r_int
r_int
id|ulIPCSource_ISR
suffix:semicolon
multiline_comment|/* IPC source bits for recently processed intr, set during ISR processing */
DECL|member|ulIPCSource_DPC
r_int
r_int
id|ulIPCSource_DPC
suffix:semicolon
multiline_comment|/* IPC source bits for recently processed intr, set during DPC processing */
DECL|member|bBDInitialized
id|BOOLEAN
id|bBDInitialized
suffix:semicolon
DECL|member|bResourcesClaimed
id|BOOLEAN
id|bResourcesClaimed
suffix:semicolon
DECL|member|bDSPEnabled
id|BOOLEAN
id|bDSPEnabled
suffix:semicolon
DECL|member|bDSPReset
id|BOOLEAN
id|bDSPReset
suffix:semicolon
DECL|member|IPCs
id|MWAVE_IPC
id|IPCs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|bMwaveDevRegistered
id|BOOLEAN
id|bMwaveDevRegistered
suffix:semicolon
DECL|member|bProcEntryCreated
id|BOOLEAN
id|bProcEntryCreated
suffix:semicolon
DECL|member|sLine
r_int
id|sLine
suffix:semicolon
DECL|typedef|MWAVE_DEVICE_DATA
DECL|typedef|pMWAVE_DEVICE_DATA
)brace
id|MWAVE_DEVICE_DATA
comma
op_star
id|pMWAVE_DEVICE_DATA
suffix:semicolon
macro_line|#endif
eof
