multiline_comment|/* &n;   3w-xxxx.h -- 3ware Storage Controller device driver for Linux.&n;   &n;   Written By: Adam Radford &lt;linux@3ware.com&gt;&n;   Modifications By: Joel Jacobson &lt;linux@3ware.com&gt;&n;   &t;&t;     Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n;                     Brad Strand &lt;linux@3ware.com&gt;&n;&n;   Copyright (C) 1999-2001 3ware Inc.&n;&n;   Kernel compatablity By:&t;Andre Hedrick &lt;andre@suse.com&gt;&n;   Non-Copyright (C) 2000&t;Andre Hedrick &lt;andre@suse.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; version 2 of the License.&n;&n;   This program is distributed in the hope that it will be useful,           &n;   but WITHOUT ANY WARRANTY; without even the implied warranty of            &n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             &n;   GNU General Public License for more details.                              &n;&n;   NO WARRANTY                                                               &n;   THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR        &n;   CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT      &n;   LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,      &n;   MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is    &n;   solely responsible for determining the appropriateness of using and       &n;   distributing the Program and assumes all risks associated with its        &n;   exercise of rights under this Agreement, including but not limited to     &n;   the risks and costs of program errors, damage to or loss of data,         &n;   programs or equipment, and unavailability or interruption of operations.  &n;&n;   DISCLAIMER OF LIABILITY                                                   &n;   NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY   &n;   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL        &n;   DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND   &n;   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR     &n;   TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE    &n;   USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED  &n;   HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES             &n;&n;   You should have received a copy of the GNU General Public License         &n;   along with this program; if not, write to the Free Software               &n;   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA &n;&n;   Bugs/Comments/Suggestions should be mailed to:                            &n;   linux@3ware.com&n;   &n;   For more information, goto:&n;   http://www.3ware.com&n;*/
macro_line|#ifndef _3W_XXXX_H
DECL|macro|_3W_XXXX_H
mdefine_line|#define _3W_XXXX_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
multiline_comment|/* AEN strings */
DECL|variable|tw_aen_string
r_static
r_char
op_star
id|tw_aen_string
(braket
)braket
op_assign
(brace
l_string|&quot;AEN queue empty&quot;
comma
singleline_comment|// 0x000
l_string|&quot;Soft reset occurred&quot;
comma
singleline_comment|// 0x001
l_string|&quot;Mirorr degraded: Unit #&quot;
comma
singleline_comment|// 0x002
l_string|&quot;Controller error&quot;
comma
singleline_comment|// 0x003 
l_string|&quot;Rebuild failed: Unit #&quot;
comma
singleline_comment|// 0x004
l_string|&quot;Rebuild complete: Unit #&quot;
comma
singleline_comment|// 0x005
l_string|&quot;Incomplete unit detected: Unit #&quot;
comma
singleline_comment|// 0x006
l_string|&quot;Initialization complete: Unit #&quot;
comma
singleline_comment|// 0x007
l_string|&quot;Unclean shutdown detected: Unit #&quot;
comma
singleline_comment|// 0x008
l_string|&quot;ATA port timeout: Port #&quot;
comma
singleline_comment|// 0x009
l_string|&quot;Drive error: Port #&quot;
comma
singleline_comment|// 0x00A
l_string|&quot;Rebuild started: Unit #&quot;
comma
singleline_comment|// 0x00B 
l_string|&quot;Initialization started: Unit #&quot;
comma
singleline_comment|// 0x00C
l_string|&quot;Logical unit deleted: Unit #&quot;
comma
singleline_comment|// 0x00D
l_int|NULL
comma
singleline_comment|// 0x00E unused
l_string|&quot;SMART threshold exceeded: Port #&quot;
comma
singleline_comment|// 0x00F
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
singleline_comment|// 0x010-0x020 unused
l_string|&quot;ATA UDMA downgrade: Port #&quot;
comma
singleline_comment|// 0x021
l_string|&quot;ATA UDMA upgrade: Port #&quot;
comma
singleline_comment|// 0x022
l_string|&quot;Sector repair occurred: Port #&quot;
comma
singleline_comment|// 0x023
l_string|&quot;SBUF integrity check failure&quot;
comma
singleline_comment|// 0x024
l_string|&quot;Lost cached write: Port #&quot;
comma
singleline_comment|// 0x025
l_string|&quot;Drive ECC error detected: Port #&quot;
comma
singleline_comment|// 0x026
l_string|&quot;DCB checksum error: Port #&quot;
comma
singleline_comment|// 0x027
l_string|&quot;DCB unsupported version: Port #&quot;
comma
singleline_comment|// 0x028
l_string|&quot;Verify started: Unit #&quot;
comma
singleline_comment|// 0x029
l_string|&quot;Verify failed: Port #&quot;
comma
singleline_comment|// 0x02A
l_string|&quot;Verify complete: Unit #&quot;
singleline_comment|// 0x02B
)brace
suffix:semicolon
DECL|macro|TW_AEN_STRING_MAX
mdefine_line|#define TW_AEN_STRING_MAX                      0x02C
multiline_comment|/* Control register bit definitions */
DECL|macro|TW_CONTROL_CLEAR_HOST_INTERRUPT
mdefine_line|#define TW_CONTROL_CLEAR_HOST_INTERRUPT&t;       0x00080000
DECL|macro|TW_CONTROL_CLEAR_ATTENTION_INTERRUPT
mdefine_line|#define TW_CONTROL_CLEAR_ATTENTION_INTERRUPT   0x00040000
DECL|macro|TW_CONTROL_MASK_COMMAND_INTERRUPT
mdefine_line|#define TW_CONTROL_MASK_COMMAND_INTERRUPT      0x00020000
DECL|macro|TW_CONTROL_MASK_RESPONSE_INTERRUPT
mdefine_line|#define TW_CONTROL_MASK_RESPONSE_INTERRUPT     0x00010000
DECL|macro|TW_CONTROL_UNMASK_COMMAND_INTERRUPT
mdefine_line|#define TW_CONTROL_UNMASK_COMMAND_INTERRUPT    0x00008000
DECL|macro|TW_CONTROL_UNMASK_RESPONSE_INTERRUPT
mdefine_line|#define TW_CONTROL_UNMASK_RESPONSE_INTERRUPT   0x00004000
DECL|macro|TW_CONTROL_CLEAR_ERROR_STATUS
mdefine_line|#define TW_CONTROL_CLEAR_ERROR_STATUS&t;       0x00000200
DECL|macro|TW_CONTROL_ISSUE_SOFT_RESET
mdefine_line|#define TW_CONTROL_ISSUE_SOFT_RESET&t;       0x00000100
DECL|macro|TW_CONTROL_ENABLE_INTERRUPTS
mdefine_line|#define TW_CONTROL_ENABLE_INTERRUPTS&t;       0x00000080
DECL|macro|TW_CONTROL_DISABLE_INTERRUPTS
mdefine_line|#define TW_CONTROL_DISABLE_INTERRUPTS&t;       0x00000040
DECL|macro|TW_CONTROL_ISSUE_HOST_INTERRUPT
mdefine_line|#define TW_CONTROL_ISSUE_HOST_INTERRUPT&t;       0x00000020
DECL|macro|TW_CONTROL_CLEAR_PARITY_ERROR
mdefine_line|#define TW_CONTROL_CLEAR_PARITY_ERROR          0x00800000
multiline_comment|/* Status register bit definitions */
DECL|macro|TW_STATUS_MAJOR_VERSION_MASK
mdefine_line|#define TW_STATUS_MAJOR_VERSION_MASK&t;       0xF0000000
DECL|macro|TW_STATUS_MINOR_VERSION_MASK
mdefine_line|#define TW_STATUS_MINOR_VERSION_MASK&t;       0x0F000000
DECL|macro|TW_STATUS_PCI_PARITY_ERROR
mdefine_line|#define TW_STATUS_PCI_PARITY_ERROR&t;       0x00800000
DECL|macro|TW_STATUS_QUEUE_ERROR
mdefine_line|#define TW_STATUS_QUEUE_ERROR&t;&t;       0x00400000
DECL|macro|TW_STATUS_MICROCONTROLLER_ERROR
mdefine_line|#define TW_STATUS_MICROCONTROLLER_ERROR&t;       0x00200000
DECL|macro|TW_STATUS_PCI_ABORT
mdefine_line|#define TW_STATUS_PCI_ABORT&t;&t;       0x00100000
DECL|macro|TW_STATUS_HOST_INTERRUPT
mdefine_line|#define TW_STATUS_HOST_INTERRUPT&t;       0x00080000
DECL|macro|TW_STATUS_ATTENTION_INTERRUPT
mdefine_line|#define TW_STATUS_ATTENTION_INTERRUPT&t;       0x00040000
DECL|macro|TW_STATUS_COMMAND_INTERRUPT
mdefine_line|#define TW_STATUS_COMMAND_INTERRUPT&t;       0x00020000
DECL|macro|TW_STATUS_RESPONSE_INTERRUPT
mdefine_line|#define TW_STATUS_RESPONSE_INTERRUPT&t;       0x00010000
DECL|macro|TW_STATUS_COMMAND_QUEUE_FULL
mdefine_line|#define TW_STATUS_COMMAND_QUEUE_FULL&t;       0x00008000
DECL|macro|TW_STATUS_RESPONSE_QUEUE_EMPTY
mdefine_line|#define TW_STATUS_RESPONSE_QUEUE_EMPTY&t;       0x00004000
DECL|macro|TW_STATUS_MICROCONTROLLER_READY
mdefine_line|#define TW_STATUS_MICROCONTROLLER_READY&t;       0x00002000
DECL|macro|TW_STATUS_COMMAND_QUEUE_EMPTY
mdefine_line|#define TW_STATUS_COMMAND_QUEUE_EMPTY&t;       0x00001000
DECL|macro|TW_STATUS_ALL_INTERRUPTS
mdefine_line|#define TW_STATUS_ALL_INTERRUPTS&t;       0x000F0000
DECL|macro|TW_STATUS_CLEARABLE_BITS
mdefine_line|#define TW_STATUS_CLEARABLE_BITS&t;       0x00D00000
DECL|macro|TW_STATUS_EXPECTED_BITS
mdefine_line|#define TW_STATUS_EXPECTED_BITS&t;&t;       0x00002000
DECL|macro|TW_STATUS_UNEXPECTED_BITS
mdefine_line|#define TW_STATUS_UNEXPECTED_BITS&t;       0x00F80000
multiline_comment|/* RESPONSE QUEUE BIT DEFINITIONS */
DECL|macro|TW_RESPONSE_ID_MASK
mdefine_line|#define TW_RESPONSE_ID_MASK&t;&t;       0x00000FF0
multiline_comment|/* PCI related defines */
DECL|macro|TW_IO_ADDRESS_RANGE
mdefine_line|#define TW_IO_ADDRESS_RANGE&t;&t;       0xD
DECL|macro|TW_DEVICE_NAME
mdefine_line|#define TW_DEVICE_NAME&t;&t;&t;       &quot;3ware Storage Controller&quot;
DECL|macro|TW_VENDOR_ID
mdefine_line|#define TW_VENDOR_ID (0x13C1)&t;/* 3ware */
DECL|macro|TW_DEVICE_ID
mdefine_line|#define TW_DEVICE_ID (0x1000)&t;/* Storage Controller */
DECL|macro|TW_DEVICE_ID2
mdefine_line|#define TW_DEVICE_ID2 (0x1001)  /* 7000 series controller */
DECL|macro|TW_NUMDEVICES
mdefine_line|#define TW_NUMDEVICES 2
DECL|macro|TW_PCI_CLEAR_PARITY_ERRORS
mdefine_line|#define TW_PCI_CLEAR_PARITY_ERRORS 0xc100
multiline_comment|/* Command packet opcodes */
DECL|macro|TW_OP_NOP
mdefine_line|#define TW_OP_NOP&t;      0x0
DECL|macro|TW_OP_INIT_CONNECTION
mdefine_line|#define TW_OP_INIT_CONNECTION 0x1
DECL|macro|TW_OP_READ
mdefine_line|#define TW_OP_READ&t;      0x2
DECL|macro|TW_OP_WRITE
mdefine_line|#define TW_OP_WRITE&t;      0x3
DECL|macro|TW_OP_VERIFY
mdefine_line|#define TW_OP_VERIFY&t;      0x4
DECL|macro|TW_OP_GET_PARAM
mdefine_line|#define TW_OP_GET_PARAM&t;      0x12
DECL|macro|TW_OP_SET_PARAM
mdefine_line|#define TW_OP_SET_PARAM&t;      0x13
DECL|macro|TW_OP_SECTOR_INFO
mdefine_line|#define TW_OP_SECTOR_INFO     0x1a
DECL|macro|TW_OP_AEN_LISTEN
mdefine_line|#define TW_OP_AEN_LISTEN      0x1c
DECL|macro|TW_CMD_PACKET
mdefine_line|#define TW_CMD_PACKET         0x1d
DECL|macro|TW_ATA_PASSTHRU
mdefine_line|#define TW_ATA_PASSTHRU       0x1e
multiline_comment|/* Asynchronous Event Notification (AEN) Codes */
DECL|macro|TW_AEN_QUEUE_EMPTY
mdefine_line|#define TW_AEN_QUEUE_EMPTY       0x0000
DECL|macro|TW_AEN_SOFT_RESET
mdefine_line|#define TW_AEN_SOFT_RESET        0x0001
DECL|macro|TW_AEN_DEGRADED_MIRROR
mdefine_line|#define TW_AEN_DEGRADED_MIRROR   0x0002
DECL|macro|TW_AEN_CONTROLLER_ERROR
mdefine_line|#define TW_AEN_CONTROLLER_ERROR  0x0003
DECL|macro|TW_AEN_REBUILD_FAIL
mdefine_line|#define TW_AEN_REBUILD_FAIL      0x0004
DECL|macro|TW_AEN_REBUILD_DONE
mdefine_line|#define TW_AEN_REBUILD_DONE      0x0005
DECL|macro|TW_AEN_QUEUE_FULL
mdefine_line|#define TW_AEN_QUEUE_FULL        0x00ff
DECL|macro|TW_AEN_TABLE_UNDEFINED
mdefine_line|#define TW_AEN_TABLE_UNDEFINED   0x15
DECL|macro|TW_AEN_APORT_TIMEOUT
mdefine_line|#define TW_AEN_APORT_TIMEOUT     0x0009
DECL|macro|TW_AEN_DRIVE_ERROR
mdefine_line|#define TW_AEN_DRIVE_ERROR       0x000A
DECL|macro|TW_AEN_SMART_FAIL
mdefine_line|#define TW_AEN_SMART_FAIL        0x000F
DECL|macro|TW_AEN_SBUF_FAIL
mdefine_line|#define TW_AEN_SBUF_FAIL         0x0024
multiline_comment|/* Misc defines */
DECL|macro|TW_ALIGNMENT
mdefine_line|#define TW_ALIGNMENT&t;&t;&t;      0x200 /* 16 D-WORDS */
DECL|macro|TW_MAX_UNITS
mdefine_line|#define TW_MAX_UNITS&t;&t;&t;      16
DECL|macro|TW_COMMAND_ALIGNMENT_MASK
mdefine_line|#define TW_COMMAND_ALIGNMENT_MASK&t;      0x1ff
DECL|macro|TW_INIT_MESSAGE_CREDITS
mdefine_line|#define TW_INIT_MESSAGE_CREDITS&t;&t;      0x100
DECL|macro|TW_INIT_COMMAND_PACKET_SIZE
mdefine_line|#define TW_INIT_COMMAND_PACKET_SIZE&t;      0x3
DECL|macro|TW_POLL_MAX_RETRIES
mdefine_line|#define TW_POLL_MAX_RETRIES        &t;      20000
DECL|macro|TW_MAX_SGL_LENGTH
mdefine_line|#define TW_MAX_SGL_LENGTH&t;&t;      62
DECL|macro|TW_ATA_PASS_SGL_MAX
mdefine_line|#define TW_ATA_PASS_SGL_MAX                   60
DECL|macro|TW_MAX_PASSTHRU_BYTES
mdefine_line|#define TW_MAX_PASSTHRU_BYTES                 4096
DECL|macro|TW_Q_LENGTH
mdefine_line|#define TW_Q_LENGTH&t;&t;&t;      256
DECL|macro|TW_MAX_BOUNCEBUF
mdefine_line|#define TW_MAX_BOUNCEBUF                      16
DECL|macro|TW_Q_START
mdefine_line|#define TW_Q_START&t;&t;&t;      0
DECL|macro|TW_MAX_SLOT
mdefine_line|#define TW_MAX_SLOT&t;&t;&t;      32
DECL|macro|TW_MAX_PCI_BUSES
mdefine_line|#define TW_MAX_PCI_BUSES&t;&t;      255
DECL|macro|TW_MAX_RESET_TRIES
mdefine_line|#define TW_MAX_RESET_TRIES&t;&t;      3
DECL|macro|TW_UNIT_INFORMATION_TABLE_BASE
mdefine_line|#define TW_UNIT_INFORMATION_TABLE_BASE&t;      0x300
DECL|macro|TW_MAX_CMDS_PER_LUN
mdefine_line|#define TW_MAX_CMDS_PER_LUN&t;&t;      (TW_Q_LENGTH-2)/TW_MAX_UNITS
DECL|macro|TW_BLOCK_SIZE
mdefine_line|#define TW_BLOCK_SIZE&t;&t;&t;      0x200 /* 512-byte blocks */
DECL|macro|TW_IOCTL
mdefine_line|#define TW_IOCTL                              0x80
DECL|macro|TW_MAX_AEN_TRIES
mdefine_line|#define TW_MAX_AEN_TRIES                      100
DECL|macro|TW_UNIT_ONLINE
mdefine_line|#define TW_UNIT_ONLINE                        1
DECL|macro|TW_IN_INTR
mdefine_line|#define TW_IN_INTR                            1
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,4,7)
DECL|macro|TW_MAX_SECTORS
mdefine_line|#define TW_MAX_SECTORS                        256
macro_line|#else
DECL|macro|TW_MAX_SECTORS
mdefine_line|#define TW_MAX_SECTORS                        128
macro_line|#endif 
DECL|macro|TW_AEN_WAIT_TIME
mdefine_line|#define TW_AEN_WAIT_TIME                      1000
multiline_comment|/* Macros */
DECL|macro|TW_STATUS_ERRORS
mdefine_line|#define TW_STATUS_ERRORS(x) &bslash;&n;&t;(((x &amp; TW_STATUS_PCI_ABORT) || &bslash;&n;&t;(x &amp; TW_STATUS_PCI_PARITY_ERROR) || &bslash;&n;&t;(x &amp; TW_STATUS_QUEUE_ERROR) || &bslash;&n;&t;(x &amp; TW_STATUS_MICROCONTROLLER_ERROR)) &amp;&amp; &bslash;&n;&t;(x &amp; TW_STATUS_MICROCONTROLLER_READY))
macro_line|#ifdef TW_DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) printk(msg)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) do { } while(0);
macro_line|#endif
multiline_comment|/* Scatter Gather List Entry */
DECL|struct|TAG_TW_SG_Entry
r_typedef
r_struct
id|TAG_TW_SG_Entry
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|typedef|TW_SG_Entry
)brace
id|TW_SG_Entry
suffix:semicolon
DECL|typedef|TW_Sector
r_typedef
r_int
r_char
id|TW_Sector
(braket
l_int|512
)braket
suffix:semicolon
multiline_comment|/* Command Packet */
DECL|struct|TW_Command
r_typedef
r_struct
id|TW_Command
(brace
multiline_comment|/* First DWORD */
r_struct
(brace
DECL|member|opcode
r_int
r_char
id|opcode
suffix:colon
l_int|5
suffix:semicolon
DECL|member|sgl_offset
r_int
r_char
id|sgl_offset
suffix:colon
l_int|3
suffix:semicolon
DECL|member|byte0
)brace
id|byte0
suffix:semicolon
DECL|member|size
r_int
r_char
id|size
suffix:semicolon
DECL|member|request_id
r_int
r_char
id|request_id
suffix:semicolon
r_struct
(brace
DECL|member|unit
r_int
r_char
id|unit
suffix:colon
l_int|4
suffix:semicolon
DECL|member|host_id
r_int
r_char
id|host_id
suffix:colon
l_int|4
suffix:semicolon
DECL|member|byte3
)brace
id|byte3
suffix:semicolon
multiline_comment|/* Second DWORD */
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
r_union
(brace
DECL|member|block_count
r_int
r_int
id|block_count
suffix:semicolon
DECL|member|parameter_count
r_int
r_int
id|parameter_count
suffix:semicolon
DECL|member|message_credits
r_int
r_int
id|message_credits
suffix:semicolon
DECL|member|byte6
)brace
id|byte6
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|lba
r_int
r_int
id|lba
suffix:semicolon
DECL|member|sgl
id|TW_SG_Entry
id|sgl
(braket
id|TW_MAX_SGL_LENGTH
)braket
suffix:semicolon
DECL|member|padding
r_int
r_int
id|padding
suffix:semicolon
multiline_comment|/* pad to 512 bytes */
DECL|member|io
)brace
id|io
suffix:semicolon
r_struct
(brace
DECL|member|sgl
id|TW_SG_Entry
id|sgl
(braket
id|TW_MAX_SGL_LENGTH
)braket
suffix:semicolon
DECL|member|padding
r_int
r_int
id|padding
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|param
)brace
id|param
suffix:semicolon
r_struct
(brace
DECL|member|response_queue_pointer
r_int
r_int
id|response_queue_pointer
suffix:semicolon
DECL|member|padding
r_int
r_int
id|padding
(braket
l_int|125
)braket
suffix:semicolon
DECL|member|init_connection
)brace
id|init_connection
suffix:semicolon
r_struct
(brace
DECL|member|version
r_char
id|version
(braket
l_int|504
)braket
suffix:semicolon
DECL|member|ioctl_miniport_version
)brace
id|ioctl_miniport_version
suffix:semicolon
DECL|member|byte8
)brace
id|byte8
suffix:semicolon
DECL|typedef|TW_Command
)brace
id|TW_Command
suffix:semicolon
DECL|struct|TAG_TW_Ioctl
r_typedef
r_struct
id|TAG_TW_Ioctl
(brace
DECL|member|buffer
r_int
id|buffer
suffix:semicolon
DECL|member|opcode
r_int
r_char
id|opcode
suffix:semicolon
DECL|member|table_id
r_int
r_int
id|table_id
suffix:semicolon
DECL|member|parameter_id
r_int
r_char
id|parameter_id
suffix:semicolon
DECL|member|parameter_size_bytes
r_int
r_char
id|parameter_size_bytes
suffix:semicolon
DECL|member|unit_index
r_int
r_char
id|unit_index
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|TW_Ioctl
)brace
id|TW_Ioctl
suffix:semicolon
multiline_comment|/* GetParam descriptor */
r_typedef
r_struct
(brace
DECL|member|table_id
r_int
r_int
id|table_id
suffix:semicolon
DECL|member|parameter_id
r_int
r_char
id|parameter_id
suffix:semicolon
DECL|member|parameter_size_bytes
r_int
r_char
id|parameter_size_bytes
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|TW_Param
DECL|typedef|PTW_Param
)brace
id|TW_Param
comma
op_star
id|PTW_Param
suffix:semicolon
multiline_comment|/* Response queue */
DECL|union|TAG_TW_Response_Queue
r_typedef
r_union
id|TAG_TW_Response_Queue
(brace
r_struct
(brace
DECL|member|undefined_1
id|u32
id|undefined_1
suffix:colon
l_int|4
suffix:semicolon
DECL|member|response_id
id|u32
id|response_id
suffix:colon
l_int|8
suffix:semicolon
DECL|member|undefined_2
id|u32
id|undefined_2
suffix:colon
l_int|20
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|value
id|u32
id|value
suffix:semicolon
DECL|typedef|TW_Response_Queue
)brace
id|TW_Response_Queue
suffix:semicolon
DECL|struct|TAG_TW_Registers
r_typedef
r_struct
id|TAG_TW_Registers
(brace
DECL|member|base_addr
id|u32
id|base_addr
suffix:semicolon
DECL|member|control_reg_addr
id|u32
id|control_reg_addr
suffix:semicolon
DECL|member|status_reg_addr
id|u32
id|status_reg_addr
suffix:semicolon
DECL|member|command_que_addr
id|u32
id|command_que_addr
suffix:semicolon
DECL|member|response_que_addr
id|u32
id|response_que_addr
suffix:semicolon
DECL|typedef|TW_Registers
)brace
id|TW_Registers
suffix:semicolon
DECL|struct|TAG_TW_Info
r_typedef
r_struct
id|TAG_TW_Info
(brace
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|position
r_int
id|position
suffix:semicolon
DECL|typedef|TW_Info
)brace
id|TW_Info
suffix:semicolon
DECL|typedef|TW_Cmd_State
r_typedef
r_int
id|TW_Cmd_State
suffix:semicolon
DECL|macro|TW_S_INITIAL
mdefine_line|#define TW_S_INITIAL   0x1  /* Initial state */
DECL|macro|TW_S_STARTED
mdefine_line|#define TW_S_STARTED   0x2  /* Id in use */
DECL|macro|TW_S_POSTED
mdefine_line|#define TW_S_POSTED    0x4  /* Posted to the controller */
DECL|macro|TW_S_PENDING
mdefine_line|#define TW_S_PENDING   0x8  /* Waiting to be posted in isr */
DECL|macro|TW_S_COMPLETED
mdefine_line|#define TW_S_COMPLETED 0x10 /* Completed by isr */
DECL|macro|TW_S_FINISHED
mdefine_line|#define TW_S_FINISHED  0x20 /* I/O completely done */
DECL|macro|TW_START_MASK
mdefine_line|#define TW_START_MASK (TW_S_STARTED | TW_S_POSTED | TW_S_PENDING | TW_S_COMPLETED)
multiline_comment|/* Command header for ATA pass-thru */
DECL|struct|TAG_TW_Passthru
r_typedef
r_struct
id|TAG_TW_Passthru
(brace
r_struct
(brace
DECL|member|opcode
r_int
r_char
id|opcode
suffix:colon
l_int|5
suffix:semicolon
DECL|member|sgloff
r_int
r_char
id|sgloff
suffix:colon
l_int|3
suffix:semicolon
DECL|member|byte0
)brace
id|byte0
suffix:semicolon
DECL|member|size
r_int
r_char
id|size
suffix:semicolon
DECL|member|request_id
r_int
r_char
id|request_id
suffix:semicolon
r_struct
(brace
DECL|member|aport
r_int
r_char
id|aport
suffix:colon
l_int|4
suffix:semicolon
DECL|member|host_id
r_int
r_char
id|host_id
suffix:colon
l_int|4
suffix:semicolon
DECL|member|byte3
)brace
id|byte3
suffix:semicolon
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|param
r_int
r_int
id|param
suffix:semicolon
DECL|member|features
r_int
r_int
id|features
suffix:semicolon
DECL|member|sector_count
r_int
r_int
id|sector_count
suffix:semicolon
DECL|member|sector_num
r_int
r_int
id|sector_num
suffix:semicolon
DECL|member|cylinder_lo
r_int
r_int
id|cylinder_lo
suffix:semicolon
DECL|member|cylinder_hi
r_int
r_int
id|cylinder_hi
suffix:semicolon
DECL|member|drive_head
r_int
r_char
id|drive_head
suffix:semicolon
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|member|sg_list
id|TW_SG_Entry
id|sg_list
(braket
id|TW_ATA_PASS_SGL_MAX
)braket
suffix:semicolon
DECL|member|padding
r_int
r_char
id|padding
(braket
l_int|12
)braket
suffix:semicolon
DECL|typedef|TW_Passthru
)brace
id|TW_Passthru
suffix:semicolon
DECL|struct|TAG_TW_Device_Extension
r_typedef
r_struct
id|TAG_TW_Device_Extension
(brace
DECL|member|registers
id|TW_Registers
id|registers
suffix:semicolon
DECL|member|alignment_virtual_address
id|u32
op_star
id|alignment_virtual_address
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|alignment_physical_address
id|u32
id|alignment_physical_address
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|bounce_buffer
id|u32
op_star
id|bounce_buffer
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|is_unit_present
r_int
id|is_unit_present
(braket
id|TW_MAX_UNITS
)braket
suffix:semicolon
DECL|member|is_raid_five
r_int
id|is_raid_five
(braket
id|TW_MAX_UNITS
)braket
suffix:semicolon
DECL|member|num_units
r_int
id|num_units
suffix:semicolon
DECL|member|num_raid_five
r_int
id|num_raid_five
suffix:semicolon
DECL|member|command_packet_virtual_address
id|u32
op_star
id|command_packet_virtual_address
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|command_packet_physical_address
id|u32
id|command_packet_physical_address
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|tw_pci_dev
r_struct
id|pci_dev
op_star
id|tw_pci_dev
suffix:semicolon
DECL|member|srb
id|Scsi_Cmnd
op_star
id|srb
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|free_queue
r_int
r_char
id|free_queue
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|free_head
r_int
r_char
id|free_head
suffix:semicolon
DECL|member|free_tail
r_int
r_char
id|free_tail
suffix:semicolon
DECL|member|free_wrap
r_int
r_char
id|free_wrap
suffix:semicolon
DECL|member|pending_queue
r_int
r_char
id|pending_queue
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|pending_head
r_int
r_char
id|pending_head
suffix:semicolon
DECL|member|pending_tail
r_int
r_char
id|pending_tail
suffix:semicolon
DECL|member|state
id|TW_Cmd_State
id|state
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|posted_request_count
id|u32
id|posted_request_count
suffix:semicolon
DECL|member|max_posted_request_count
id|u32
id|max_posted_request_count
suffix:semicolon
DECL|member|request_count_marked_pending
id|u32
id|request_count_marked_pending
suffix:semicolon
DECL|member|pending_request_count
id|u32
id|pending_request_count
suffix:semicolon
DECL|member|max_pending_request_count
id|u32
id|max_pending_request_count
suffix:semicolon
DECL|member|max_sgl_entries
id|u32
id|max_sgl_entries
suffix:semicolon
DECL|member|sgl_entries
id|u32
id|sgl_entries
suffix:semicolon
DECL|member|num_aborts
id|u32
id|num_aborts
suffix:semicolon
DECL|member|num_resets
id|u32
id|num_resets
suffix:semicolon
DECL|member|sector_count
id|u32
id|sector_count
suffix:semicolon
DECL|member|max_sector_count
id|u32
id|max_sector_count
suffix:semicolon
DECL|member|aen_count
id|u32
id|aen_count
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|tw_lock
id|spinlock_t
id|tw_lock
suffix:semicolon
DECL|member|ioctl_size
r_int
id|ioctl_size
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|aen_queue
r_int
r_int
id|aen_queue
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|aen_head
r_int
r_char
id|aen_head
suffix:semicolon
DECL|member|aen_tail
r_int
r_char
id|aen_tail
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* long req&squot;d for set_bit --RR */
DECL|typedef|TW_Device_Extension
)brace
id|TW_Device_Extension
suffix:semicolon
multiline_comment|/* Function prototypes */
r_int
id|tw_aen_complete
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|request_id
)paren
suffix:semicolon
r_int
id|tw_aen_drain_queue
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_int
id|tw_aen_read_queue
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|request_id
)paren
suffix:semicolon
r_int
id|tw_allocate_memory
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|request_id
comma
r_int
id|size
comma
r_int
id|which
)paren
suffix:semicolon
r_int
id|tw_check_bits
c_func
(paren
id|u32
id|status_reg_value
)paren
suffix:semicolon
r_int
id|tw_check_errors
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_void
id|tw_clear_attention_interrupt
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_void
id|tw_clear_host_interrupt
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_void
id|tw_decode_bits
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
id|u32
id|status_reg_value
)paren
suffix:semicolon
r_void
id|tw_decode_error
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
r_char
id|status
comma
r_int
r_char
id|flags
comma
r_int
r_char
id|unit
)paren
suffix:semicolon
r_void
id|tw_disable_interrupts
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_int
id|tw_empty_response_que
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_void
id|tw_enable_interrupts
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_int
id|tw_findcards
c_func
(paren
id|Scsi_Host_Template
op_star
id|tw_host
)paren
suffix:semicolon
r_void
id|tw_free_device_extension
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_int
id|tw_initconnection
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|message_credits
)paren
suffix:semicolon
r_int
id|tw_initialize_device_extension
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_int
id|tw_initialize_units
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_int
id|tw_ioctl
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|request_id
)paren
suffix:semicolon
r_int
id|tw_ioctl_complete
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|request_id
)paren
suffix:semicolon
r_void
id|tw_mask_command_interrupt
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_int
id|tw_poll_status
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
id|u32
id|flag
comma
r_int
id|seconds
)paren
suffix:semicolon
r_int
id|tw_post_command_packet
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|request_id
)paren
suffix:semicolon
r_int
id|tw_reset_device_extension
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_int
id|tw_reset_sequence
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_int
id|tw_scsi_biosparam
c_func
(paren
id|Disk
op_star
id|disk
comma
id|kdev_t
id|dev
comma
r_int
id|geom
(braket
)braket
)paren
suffix:semicolon
r_int
id|tw_scsi_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tw_host
)paren
suffix:semicolon
r_int
id|tw_scsi_eh_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|tw_scsi_eh_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|tw_scsi_proc_info
c_func
(paren
r_char
op_star
id|buffer
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
id|length
comma
r_int
id|inode
comma
r_int
id|inout
)paren
suffix:semicolon
r_int
id|tw_scsi_queue
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|tw_scsi_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|tw_host
)paren
suffix:semicolon
r_int
id|tw_scsiop_inquiry
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|request_id
)paren
suffix:semicolon
r_int
id|tw_scsiop_inquiry_complete
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|request_id
)paren
suffix:semicolon
r_int
id|tw_scsiop_read_capacity
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|request_id
)paren
suffix:semicolon
r_int
id|tw_scsiop_read_capacity_complete
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|request_id
)paren
suffix:semicolon
r_int
id|tw_scsiop_read_write
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|request_id
)paren
suffix:semicolon
r_int
id|tw_scsiop_request_sense
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|request_id
)paren
suffix:semicolon
r_int
id|tw_scsiop_test_unit_ready
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|request_id
)paren
suffix:semicolon
r_int
id|tw_setfeature
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|parm
comma
r_int
id|param_size
comma
r_int
r_char
op_star
id|val
)paren
suffix:semicolon
r_int
id|tw_setup_irq
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_int
id|tw_shutdown_device
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_void
id|tw_soft_reset
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
r_int
id|tw_state_request_finish
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
id|request_id
)paren
suffix:semicolon
r_int
id|tw_state_request_start
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
comma
r_int
op_star
id|request_id
)paren
suffix:semicolon
r_void
id|tw_unmask_command_interrupt
c_func
(paren
id|TW_Device_Extension
op_star
id|tw_dev
)paren
suffix:semicolon
multiline_comment|/* Scsi_Host_Template Initializer */
DECL|macro|TWXXXX
mdefine_line|#define TWXXXX {&t;&t;&t;&t;&t;&bslash;&n;&t;next : NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;module : NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;proc_name : &quot;3w-xxxx&quot;,&t;&t;&t;&t;&bslash;&n;&t;proc_info : tw_scsi_proc_info,&t;&t;&t;&bslash;&n;&t;name : &quot;3ware Storage Controller&quot;,&t;&t;&bslash;&n;&t;detect : tw_scsi_detect,&t;&t;&t;&bslash;&n;&t;release : tw_scsi_release,&t;&t;&t;&bslash;&n;&t;info : NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;ioctl : NULL,                  &t;&t;&t;&bslash;&n;&t;command : NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;queuecommand : tw_scsi_queue,&t;&t;&t;&bslash;&n;&t;eh_strategy_handler : NULL,&t;&t;&t;&bslash;&n;&t;eh_abort_handler : tw_scsi_eh_abort,&t;&t;&bslash;&n;&t;eh_device_reset_handler : NULL,&t;&t;&t;&bslash;&n;&t;eh_bus_reset_handler : NULL,&t;&t;&t;&bslash;&n;&t;eh_host_reset_handler : tw_scsi_eh_reset,&t;&bslash;&n;&t;abort : NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;reset : NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;slave_attach : NULL,&t;&t;&t;&t;&bslash;&n;&t;bios_param : tw_scsi_biosparam,&t;&t;&t;&bslash;&n;&t;can_queue : TW_Q_LENGTH,&t;&t;&t;&bslash;&n;&t;this_id: -1,&t;&t;&t;&t;&t;&bslash;&n;&t;sg_tablesize : TW_MAX_SGL_LENGTH,&t;&t;&bslash;&n;&t;cmd_per_lun: TW_MAX_CMDS_PER_LUN,&t;&t;&bslash;&n;&t;present : 0,&t;&t;&t;&t;&t;&bslash;&n;&t;unchecked_isa_dma : 0,&t;&t;&t;&t;&bslash;&n;&t;use_clustering : ENABLE_CLUSTERING,&t;&t;&bslash;&n;&t;emulated : 1&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif /* _3W_XXXX_H */
eof
