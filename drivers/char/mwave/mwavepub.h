multiline_comment|/*&n;*&n;* mwavepub.h -- PUBLIC declarations for the mwave driver&n;*               and applications using it&n;*&n;*&n;* Written By: Mike Sullivan IBM Corporation&n;*&n;* Copyright (C) 1999 IBM Corporation&n;*&n;* This program is free software; you can redistribute it and/or modify&n;* it under the terms of the GNU General Public License as published by&n;* the Free Software Foundation; either version 2 of the License, or&n;* (at your option) any later version.&n;*&n;* This program is distributed in the hope that it will be useful,&n;* but WITHOUT ANY WARRANTY; without even the implied warranty of&n;* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;* GNU General Public License for more details.&n;*&n;* NO WARRANTY&n;* THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;* CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;* LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;* solely responsible for determining the appropriateness of using and&n;* distributing the Program and assumes all risks associated with its&n;* exercise of rights under this Agreement, including but not limited to&n;* the risks and costs of program errors, damage to or loss of data,&n;* programs or equipment, and unavailability or interruption of operations.&n;*&n;* DISCLAIMER OF LIABILITY&n;* NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;* DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;* USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;* HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;*&n;* You should have received a copy of the GNU General Public License&n;* along with this program; if not, write to the Free Software&n;* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*&n;*&n;* 10/23/2000 - Alpha Release&n;*&t;First release to the public&n;*/
macro_line|#ifndef _LINUX_MWAVEPUB_H
DECL|macro|_LINUX_MWAVEPUB_H
mdefine_line|#define _LINUX_MWAVEPUB_H
macro_line|#ifndef MWAVEM_APP_DIST
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#endif
macro_line|#ifdef MWAVEM_APP_DIST
DECL|macro|MWAVE_MINOR
mdefine_line|#define MWAVE_MINOR      219
macro_line|#endif
DECL|struct|_MW_ABILITIES
r_typedef
r_struct
id|_MW_ABILITIES
(brace
DECL|member|instr_per_sec
r_int
r_int
id|instr_per_sec
suffix:semicolon
DECL|member|data_size
r_int
r_int
id|data_size
suffix:semicolon
DECL|member|inst_size
r_int
r_int
id|inst_size
suffix:semicolon
DECL|member|bus_dma_bw
r_int
r_int
id|bus_dma_bw
suffix:semicolon
DECL|member|uart_enable
r_int
r_int
id|uart_enable
suffix:semicolon
DECL|member|component_count
r_int
id|component_count
suffix:semicolon
DECL|member|component_list
r_int
r_int
id|component_list
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|mwave_os_name
r_char
id|mwave_os_name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|bios_task_name
r_char
id|bios_task_name
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|MW_ABILITIES
DECL|typedef|pMW_ABILITIES
)brace
id|MW_ABILITIES
comma
op_star
id|pMW_ABILITIES
suffix:semicolon
DECL|struct|_MW_READWRITE
r_typedef
r_struct
id|_MW_READWRITE
(brace
DECL|member|usDspAddress
r_int
r_int
id|usDspAddress
suffix:semicolon
multiline_comment|/* The dsp address */
DECL|member|ulDataLength
r_int
r_int
id|ulDataLength
suffix:semicolon
multiline_comment|/* The size in bytes of the data or user buffer */
DECL|member|pBuf
r_void
op_star
id|pBuf
suffix:semicolon
multiline_comment|/* Input:variable sized buffer */
DECL|typedef|MW_READWRITE
DECL|typedef|pMW_READWRITE
)brace
id|MW_READWRITE
comma
op_star
id|pMW_READWRITE
suffix:semicolon
DECL|macro|IOCTL_MW_RESET
mdefine_line|#define IOCTL_MW_RESET           _IO(MWAVE_MINOR,1)
DECL|macro|IOCTL_MW_RUN
mdefine_line|#define IOCTL_MW_RUN             _IO(MWAVE_MINOR,2)
DECL|macro|IOCTL_MW_DSP_ABILITIES
mdefine_line|#define IOCTL_MW_DSP_ABILITIES   _IOR(MWAVE_MINOR,3,MW_ABILITIES)
DECL|macro|IOCTL_MW_READ_DATA
mdefine_line|#define IOCTL_MW_READ_DATA       _IOR(MWAVE_MINOR,4,MW_READWRITE)
DECL|macro|IOCTL_MW_READCLEAR_DATA
mdefine_line|#define IOCTL_MW_READCLEAR_DATA  _IOR(MWAVE_MINOR,5,MW_READWRITE)
DECL|macro|IOCTL_MW_READ_INST
mdefine_line|#define IOCTL_MW_READ_INST       _IOR(MWAVE_MINOR,6,MW_READWRITE)
DECL|macro|IOCTL_MW_WRITE_DATA
mdefine_line|#define IOCTL_MW_WRITE_DATA      _IOW(MWAVE_MINOR,7,MW_READWRITE)
DECL|macro|IOCTL_MW_WRITE_INST
mdefine_line|#define IOCTL_MW_WRITE_INST      _IOW(MWAVE_MINOR,8,MW_READWRITE)
DECL|macro|IOCTL_MW_REGISTER_IPC
mdefine_line|#define IOCTL_MW_REGISTER_IPC    _IOW(MWAVE_MINOR,9,int)
DECL|macro|IOCTL_MW_UNREGISTER_IPC
mdefine_line|#define IOCTL_MW_UNREGISTER_IPC  _IOW(MWAVE_MINOR,10,int)
DECL|macro|IOCTL_MW_GET_IPC
mdefine_line|#define IOCTL_MW_GET_IPC         _IOW(MWAVE_MINOR,11,int)
DECL|macro|IOCTL_MW_TRACE
mdefine_line|#define IOCTL_MW_TRACE           _IOR(MWAVE_MINOR,12,MW_READWRITE)
macro_line|#endif
eof
