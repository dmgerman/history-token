multiline_comment|/*&n;   3w-9xxx.h -- 3ware 9000 Storage Controller device driver for Linux.&n;&n;   Written By: Adam Radford &lt;linuxraid@amcc.com&gt;&n;&n;   Copyright (C) 2004 Applied Micro Circuits Corporation.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; version 2 of the License.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   NO WARRANTY&n;   THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;   CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;   LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;   MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;   solely responsible for determining the appropriateness of using and&n;   distributing the Program and assumes all risks associated with its&n;   exercise of rights under this Agreement, including but not limited to&n;   the risks and costs of program errors, damage to or loss of data,&n;   programs or equipment, and unavailability or interruption of operations.&n;&n;   DISCLAIMER OF LIABILITY&n;   NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;   DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;   TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;   USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;   HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;&n;   Bugs/Comments/Suggestions should be mailed to:&n;   linuxraid@amcc.com&n;&n;   For more information, goto:&n;   http://www.amcc.com&n;*/
macro_line|#ifndef _3W_9XXX_H
DECL|macro|_3W_9XXX_H
mdefine_line|#define _3W_9XXX_H
multiline_comment|/* AEN string type */
DECL|struct|TAG_twa_message_type
r_typedef
r_struct
id|TAG_twa_message_type
(brace
DECL|member|code
r_int
r_int
id|code
suffix:semicolon
DECL|member|text
r_char
op_star
id|text
suffix:semicolon
DECL|typedef|twa_message_type
)brace
id|twa_message_type
suffix:semicolon
multiline_comment|/* AEN strings */
DECL|variable|twa_aen_table
r_static
id|twa_message_type
id|twa_aen_table
(braket
)braket
op_assign
(brace
(brace
l_int|0x0000
comma
l_string|&quot;AEN queue empty&quot;
)brace
comma
(brace
l_int|0x0001
comma
l_string|&quot;Controller reset occurred&quot;
)brace
comma
(brace
l_int|0x0002
comma
l_string|&quot;Degraded unit detected&quot;
)brace
comma
(brace
l_int|0x0003
comma
l_string|&quot;Controller error occured&quot;
)brace
comma
(brace
l_int|0x0004
comma
l_string|&quot;Background rebuild failed&quot;
)brace
comma
(brace
l_int|0x0005
comma
l_string|&quot;Background rebuild done&quot;
)brace
comma
(brace
l_int|0x0006
comma
l_string|&quot;Incomplete unit detected&quot;
)brace
comma
(brace
l_int|0x0007
comma
l_string|&quot;Background initialize done&quot;
)brace
comma
(brace
l_int|0x0008
comma
l_string|&quot;Unclean shutdown detected&quot;
)brace
comma
(brace
l_int|0x0009
comma
l_string|&quot;Drive timeout detected&quot;
)brace
comma
(brace
l_int|0x000A
comma
l_string|&quot;Drive error detected&quot;
)brace
comma
(brace
l_int|0x000B
comma
l_string|&quot;Rebuild started&quot;
)brace
comma
(brace
l_int|0x000C
comma
l_string|&quot;Background initialize started&quot;
)brace
comma
(brace
l_int|0x000D
comma
l_string|&quot;Entire logical unit was deleted&quot;
)brace
comma
(brace
l_int|0x000E
comma
l_string|&quot;Background initialize failed&quot;
)brace
comma
(brace
l_int|0x000F
comma
l_string|&quot;SMART attribute exceeded threshold&quot;
)brace
comma
(brace
l_int|0x0010
comma
l_string|&quot;Power supply reported AC under range&quot;
)brace
comma
(brace
l_int|0x0011
comma
l_string|&quot;Power supply reported DC out of range&quot;
)brace
comma
(brace
l_int|0x0012
comma
l_string|&quot;Power supply reported a malfunction&quot;
)brace
comma
(brace
l_int|0x0013
comma
l_string|&quot;Power supply predicted malfunction&quot;
)brace
comma
(brace
l_int|0x0014
comma
l_string|&quot;Battery charge is below threshold&quot;
)brace
comma
(brace
l_int|0x0015
comma
l_string|&quot;Fan speed is below threshold&quot;
)brace
comma
(brace
l_int|0x0016
comma
l_string|&quot;Temperature sensor is above threshold&quot;
)brace
comma
(brace
l_int|0x0017
comma
l_string|&quot;Power supply was removed&quot;
)brace
comma
(brace
l_int|0x0018
comma
l_string|&quot;Power supply was inserted&quot;
)brace
comma
(brace
l_int|0x0019
comma
l_string|&quot;Drive was removed from a bay&quot;
)brace
comma
(brace
l_int|0x001A
comma
l_string|&quot;Drive was inserted into a bay&quot;
)brace
comma
(brace
l_int|0x001B
comma
l_string|&quot;Drive bay cover door was opened&quot;
)brace
comma
(brace
l_int|0x001C
comma
l_string|&quot;Drive bay cover door was closed&quot;
)brace
comma
(brace
l_int|0x001D
comma
l_string|&quot;Product case was opened&quot;
)brace
comma
(brace
l_int|0x0020
comma
l_string|&quot;Prepare for shutdown (power-off)&quot;
)brace
comma
(brace
l_int|0x0021
comma
l_string|&quot;Downgrade UDMA mode to lower speed&quot;
)brace
comma
(brace
l_int|0x0022
comma
l_string|&quot;Upgrade UDMA mode to higher speed&quot;
)brace
comma
(brace
l_int|0x0023
comma
l_string|&quot;Sector repair completed&quot;
)brace
comma
(brace
l_int|0x0024
comma
l_string|&quot;Sbuf memory test failed&quot;
)brace
comma
(brace
l_int|0x0025
comma
l_string|&quot;Error flushing cached write data to array&quot;
)brace
comma
(brace
l_int|0x0026
comma
l_string|&quot;Drive reported data ECC error&quot;
)brace
comma
(brace
l_int|0x0027
comma
l_string|&quot;DCB has checksum error&quot;
)brace
comma
(brace
l_int|0x0028
comma
l_string|&quot;DCB version is unsupported&quot;
)brace
comma
(brace
l_int|0x0029
comma
l_string|&quot;Background verify started&quot;
)brace
comma
(brace
l_int|0x002A
comma
l_string|&quot;Background verify failed&quot;
)brace
comma
(brace
l_int|0x002B
comma
l_string|&quot;Background verify done&quot;
)brace
comma
(brace
l_int|0x002C
comma
l_string|&quot;Bad sector overwritten during rebuild&quot;
)brace
comma
(brace
l_int|0x002D
comma
l_string|&quot;Background rebuild error on source drive&quot;
)brace
comma
(brace
l_int|0x002E
comma
l_string|&quot;Replace failed because replacement drive too small&quot;
)brace
comma
(brace
l_int|0x002F
comma
l_string|&quot;Verify failed because array was never initialized&quot;
)brace
comma
(brace
l_int|0x0030
comma
l_string|&quot;Unsupported ATA drive&quot;
)brace
comma
(brace
l_int|0x0031
comma
l_string|&quot;Synchronize host/controller time&quot;
)brace
comma
(brace
l_int|0x0032
comma
l_string|&quot;Spare capacity is inadequate for some units&quot;
)brace
comma
(brace
l_int|0x0033
comma
l_string|&quot;Background migration started&quot;
)brace
comma
(brace
l_int|0x0034
comma
l_string|&quot;Background migration failed&quot;
)brace
comma
(brace
l_int|0x0035
comma
l_string|&quot;Background migration done&quot;
)brace
comma
(brace
l_int|0x0036
comma
l_string|&quot;Verify detected and fixed data/parity mismatch&quot;
)brace
comma
(brace
l_int|0x0037
comma
l_string|&quot;SO-DIMM incompatible&quot;
)brace
comma
(brace
l_int|0x0038
comma
l_string|&quot;SO-DIMM not detected&quot;
)brace
comma
(brace
l_int|0x0039
comma
l_string|&quot;Corrected Sbuf ECC error&quot;
)brace
comma
(brace
l_int|0x003A
comma
l_string|&quot;Drive power on reset detected&quot;
)brace
comma
(brace
l_int|0x003B
comma
l_string|&quot;Background rebuild paused&quot;
)brace
comma
(brace
l_int|0x003C
comma
l_string|&quot;Background initialize paused&quot;
)brace
comma
(brace
l_int|0x003D
comma
l_string|&quot;Background verify paused&quot;
)brace
comma
(brace
l_int|0x003E
comma
l_string|&quot;Background migration paused&quot;
)brace
comma
(brace
l_int|0x003F
comma
l_string|&quot;Corrupt flash file system detected&quot;
)brace
comma
(brace
l_int|0x0040
comma
l_string|&quot;Flash file system repaired&quot;
)brace
comma
(brace
l_int|0x0041
comma
l_string|&quot;Unit number assignments were lost&quot;
)brace
comma
(brace
l_int|0x0042
comma
l_string|&quot;Error during read of primary DCB&quot;
)brace
comma
(brace
l_int|0x0043
comma
l_string|&quot;Latent error found in backup DCB&quot;
)brace
comma
(brace
l_int|0x00FC
comma
l_string|&quot;Recovered/finished array membership update&quot;
)brace
comma
(brace
l_int|0x00FD
comma
l_string|&quot;Handler lockup&quot;
)brace
comma
(brace
l_int|0x00FE
comma
l_string|&quot;Retrying PCI transfer&quot;
)brace
comma
(brace
l_int|0x00FF
comma
l_string|&quot;AEN queue is full&quot;
)brace
comma
(brace
l_int|0xFFFFFFFF
comma
(paren
r_char
op_star
)paren
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* AEN severity table */
DECL|variable|twa_aen_severity_table
r_static
r_char
op_star
id|twa_aen_severity_table
(braket
)braket
op_assign
(brace
l_string|&quot;None&quot;
comma
l_string|&quot;ERROR&quot;
comma
l_string|&quot;WARNING&quot;
comma
l_string|&quot;INFO&quot;
comma
l_string|&quot;DEBUG&quot;
comma
(paren
r_char
op_star
)paren
l_int|0
)brace
suffix:semicolon
multiline_comment|/* Error strings */
DECL|variable|twa_error_table
r_static
id|twa_message_type
id|twa_error_table
(braket
)braket
op_assign
(brace
(brace
l_int|0x0100
comma
l_string|&quot;SGL entry contains zero data&quot;
)brace
comma
(brace
l_int|0x0101
comma
l_string|&quot;Invalid command opcode&quot;
)brace
comma
(brace
l_int|0x0102
comma
l_string|&quot;SGL entry has unaligned address&quot;
)brace
comma
(brace
l_int|0x0103
comma
l_string|&quot;SGL size does not match command&quot;
)brace
comma
(brace
l_int|0x0104
comma
l_string|&quot;SGL entry has illegal length&quot;
)brace
comma
(brace
l_int|0x0105
comma
l_string|&quot;Command packet is not aligned&quot;
)brace
comma
(brace
l_int|0x0106
comma
l_string|&quot;Invalid request ID&quot;
)brace
comma
(brace
l_int|0x0107
comma
l_string|&quot;Duplicate request ID&quot;
)brace
comma
(brace
l_int|0x0108
comma
l_string|&quot;ID not locked&quot;
)brace
comma
(brace
l_int|0x0109
comma
l_string|&quot;LBA out of range&quot;
)brace
comma
(brace
l_int|0x010A
comma
l_string|&quot;Logical unit not supported&quot;
)brace
comma
(brace
l_int|0x010B
comma
l_string|&quot;Parameter table does not exist&quot;
)brace
comma
(brace
l_int|0x010C
comma
l_string|&quot;Parameter index does not exist&quot;
)brace
comma
(brace
l_int|0x010D
comma
l_string|&quot;Invalid field in CDB&quot;
)brace
comma
(brace
l_int|0x010E
comma
l_string|&quot;Specified port has invalid drive&quot;
)brace
comma
(brace
l_int|0x010F
comma
l_string|&quot;Parameter item size mismatch&quot;
)brace
comma
(brace
l_int|0x0110
comma
l_string|&quot;Failed memory allocation&quot;
)brace
comma
(brace
l_int|0x0111
comma
l_string|&quot;Memory request too large&quot;
)brace
comma
(brace
l_int|0x0112
comma
l_string|&quot;Out of memory segments&quot;
)brace
comma
(brace
l_int|0x0113
comma
l_string|&quot;Invalid address to deallocate&quot;
)brace
comma
(brace
l_int|0x0114
comma
l_string|&quot;Out of memory&quot;
)brace
comma
(brace
l_int|0x0115
comma
l_string|&quot;Out of heap&quot;
)brace
comma
(brace
l_int|0x0120
comma
l_string|&quot;Double degrade&quot;
)brace
comma
(brace
l_int|0x0121
comma
l_string|&quot;Drive not degraded&quot;
)brace
comma
(brace
l_int|0x0122
comma
l_string|&quot;Reconstruct error&quot;
)brace
comma
(brace
l_int|0x0123
comma
l_string|&quot;Replace not accepted&quot;
)brace
comma
(brace
l_int|0x0124
comma
l_string|&quot;Replace drive capacity too small&quot;
)brace
comma
(brace
l_int|0x0125
comma
l_string|&quot;Sector count not allowed&quot;
)brace
comma
(brace
l_int|0x0126
comma
l_string|&quot;No spares left&quot;
)brace
comma
(brace
l_int|0x0127
comma
l_string|&quot;Reconstruct error&quot;
)brace
comma
(brace
l_int|0x0128
comma
l_string|&quot;Unit is offline&quot;
)brace
comma
(brace
l_int|0x0129
comma
l_string|&quot;Cannot update status to DCB&quot;
)brace
comma
(brace
l_int|0x0130
comma
l_string|&quot;Invalid stripe handle&quot;
)brace
comma
(brace
l_int|0x0131
comma
l_string|&quot;Handle that was not locked&quot;
)brace
comma
(brace
l_int|0x0132
comma
l_string|&quot;Handle that was not empty&quot;
)brace
comma
(brace
l_int|0x0133
comma
l_string|&quot;Handle has different owner&quot;
)brace
comma
(brace
l_int|0x0140
comma
l_string|&quot;IPR has parent&quot;
)brace
comma
(brace
l_int|0x0150
comma
l_string|&quot;Illegal Pbuf address alignment&quot;
)brace
comma
(brace
l_int|0x0151
comma
l_string|&quot;Illegal Pbuf transfer length&quot;
)brace
comma
(brace
l_int|0x0152
comma
l_string|&quot;Illegal Sbuf address alignment&quot;
)brace
comma
(brace
l_int|0x0153
comma
l_string|&quot;Illegal Sbuf transfer length&quot;
)brace
comma
(brace
l_int|0x0160
comma
l_string|&quot;Command packet too large&quot;
)brace
comma
(brace
l_int|0x0161
comma
l_string|&quot;SGL exceeds maximum length&quot;
)brace
comma
(brace
l_int|0x0162
comma
l_string|&quot;SGL has too many entries&quot;
)brace
comma
(brace
l_int|0x0170
comma
l_string|&quot;Insufficient resources for rebuilder&quot;
)brace
comma
(brace
l_int|0x0171
comma
l_string|&quot;Verify error (data != parity)&quot;
)brace
comma
(brace
l_int|0x0180
comma
l_string|&quot;Requested segment not in directory of this DCB&quot;
)brace
comma
(brace
l_int|0x0181
comma
l_string|&quot;DCB segment has unsupported version&quot;
)brace
comma
(brace
l_int|0x0182
comma
l_string|&quot;DCB segment has checksum error&quot;
)brace
comma
(brace
l_int|0x0183
comma
l_string|&quot;DCB support (settings) segment invalid&quot;
)brace
comma
(brace
l_int|0x0184
comma
l_string|&quot;DCB UDB (unit descriptor block) segment invalid&quot;
)brace
comma
(brace
l_int|0x0185
comma
l_string|&quot;DCB GUID (globally unique identifier) segment invalid&quot;
)brace
comma
(brace
l_int|0x01A0
comma
l_string|&quot;Could not clear Sbuf&quot;
)brace
comma
(brace
l_int|0x01C0
comma
l_string|&quot;Flash identify failed&quot;
)brace
comma
(brace
l_int|0x01C1
comma
l_string|&quot;Flash out of bounds&quot;
)brace
comma
(brace
l_int|0x01C2
comma
l_string|&quot;Flash verify error&quot;
)brace
comma
(brace
l_int|0x01C3
comma
l_string|&quot;Flash file object not found&quot;
)brace
comma
(brace
l_int|0x01C4
comma
l_string|&quot;Flash file already present&quot;
)brace
comma
(brace
l_int|0x01C5
comma
l_string|&quot;Flash file system full&quot;
)brace
comma
(brace
l_int|0x01C6
comma
l_string|&quot;Flash file not present&quot;
)brace
comma
(brace
l_int|0x01C7
comma
l_string|&quot;Flash file size error&quot;
)brace
comma
(brace
l_int|0x01C8
comma
l_string|&quot;Bad flash file checksum&quot;
)brace
comma
(brace
l_int|0x01CA
comma
l_string|&quot;Corrupt flash file system detected&quot;
)brace
comma
(brace
l_int|0x01D0
comma
l_string|&quot;Invalid field in parameter list&quot;
)brace
comma
(brace
l_int|0x01D1
comma
l_string|&quot;Parameter list length error&quot;
)brace
comma
(brace
l_int|0x01D2
comma
l_string|&quot;Parameter item is not changeable&quot;
)brace
comma
(brace
l_int|0x01D3
comma
l_string|&quot;Parameter item is not saveable&quot;
)brace
comma
(brace
l_int|0x0200
comma
l_string|&quot;UDMA CRC error&quot;
)brace
comma
(brace
l_int|0x0201
comma
l_string|&quot;Internal CRC error&quot;
)brace
comma
(brace
l_int|0x0202
comma
l_string|&quot;Data ECC error&quot;
)brace
comma
(brace
l_int|0x0203
comma
l_string|&quot;ADP level 1 error&quot;
)brace
comma
(brace
l_int|0x0204
comma
l_string|&quot;Port timeout&quot;
)brace
comma
(brace
l_int|0x0205
comma
l_string|&quot;Drive power on reset&quot;
)brace
comma
(brace
l_int|0x0206
comma
l_string|&quot;ADP level 2 error&quot;
)brace
comma
(brace
l_int|0x0207
comma
l_string|&quot;Soft reset failed&quot;
)brace
comma
(brace
l_int|0x0208
comma
l_string|&quot;Drive not ready&quot;
)brace
comma
(brace
l_int|0x0209
comma
l_string|&quot;Unclassified port error&quot;
)brace
comma
(brace
l_int|0x020A
comma
l_string|&quot;Drive aborted command&quot;
)brace
comma
(brace
l_int|0x0210
comma
l_string|&quot;Internal CRC error&quot;
)brace
comma
(brace
l_int|0x0211
comma
l_string|&quot;PCI abort error&quot;
)brace
comma
(brace
l_int|0x0212
comma
l_string|&quot;PCI parity error&quot;
)brace
comma
(brace
l_int|0x0213
comma
l_string|&quot;Port handler error&quot;
)brace
comma
(brace
l_int|0x0214
comma
l_string|&quot;Token interrupt count error&quot;
)brace
comma
(brace
l_int|0x0215
comma
l_string|&quot;Timeout waiting for PCI transfer&quot;
)brace
comma
(brace
l_int|0x0216
comma
l_string|&quot;Corrected buffer ECC&quot;
)brace
comma
(brace
l_int|0x0217
comma
l_string|&quot;Uncorrected buffer ECC&quot;
)brace
comma
(brace
l_int|0x0230
comma
l_string|&quot;Unsupported command during flash recovery&quot;
)brace
comma
(brace
l_int|0x0231
comma
l_string|&quot;Next image buffer expected&quot;
)brace
comma
(brace
l_int|0x0232
comma
l_string|&quot;Binary image architecture incompatible&quot;
)brace
comma
(brace
l_int|0x0233
comma
l_string|&quot;Binary image has no signature&quot;
)brace
comma
(brace
l_int|0x0234
comma
l_string|&quot;Binary image has bad checksum&quot;
)brace
comma
(brace
l_int|0x0235
comma
l_string|&quot;Image downloaded overflowed buffer&quot;
)brace
comma
(brace
l_int|0x0240
comma
l_string|&quot;I2C device not found&quot;
)brace
comma
(brace
l_int|0x0241
comma
l_string|&quot;I2C transaction aborted&quot;
)brace
comma
(brace
l_int|0x0242
comma
l_string|&quot;SO-DIMM parameter(s) incompatible using defaults&quot;
)brace
comma
(brace
l_int|0x0243
comma
l_string|&quot;SO-DIMM unsupported&quot;
)brace
comma
(brace
l_int|0x0248
comma
l_string|&quot;SPI transfer status error&quot;
)brace
comma
(brace
l_int|0x0249
comma
l_string|&quot;SPI transfer timeout error&quot;
)brace
comma
(brace
l_int|0x0250
comma
l_string|&quot;Invalid unit descriptor size in CreateUnit&quot;
)brace
comma
(brace
l_int|0x0251
comma
l_string|&quot;Unit descriptor size exceeds data buffer in CreateUnit&quot;
)brace
comma
(brace
l_int|0x0252
comma
l_string|&quot;Invalid value in CreateUnit descriptor&quot;
)brace
comma
(brace
l_int|0x0253
comma
l_string|&quot;Inadequate disk space to support descriptor in CreateUnit&quot;
)brace
comma
(brace
l_int|0x0254
comma
l_string|&quot;Unable to create data channel for this unit descriptor&quot;
)brace
comma
(brace
l_int|0x0255
comma
l_string|&quot;CreateUnit descriptor specifies a drive already in use&quot;
)brace
comma
(brace
l_int|0x0256
comma
l_string|&quot;Unable to write configuration to all disks during CreateUnit&quot;
)brace
comma
(brace
l_int|0x0257
comma
l_string|&quot;CreateUnit does not support this descriptor version&quot;
)brace
comma
(brace
l_int|0x0258
comma
l_string|&quot;Invalid subunit for RAID 0 or 5 in CreateUnit&quot;
)brace
comma
(brace
l_int|0x0259
comma
l_string|&quot;Too many descriptors in CreateUnit&quot;
)brace
comma
(brace
l_int|0x025A
comma
l_string|&quot;Invalid configuration specified in CreateUnit descriptor&quot;
)brace
comma
(brace
l_int|0x025B
comma
l_string|&quot;Invalid LBA offset specified in CreateUnit descriptor&quot;
)brace
comma
(brace
l_int|0x025C
comma
l_string|&quot;Invalid stripelet size specified in CreateUnit descriptor&quot;
)brace
comma
(brace
l_int|0x0260
comma
l_string|&quot;SMART attribute exceeded threshold&quot;
)brace
comma
(brace
l_int|0xFFFFFFFF
comma
(paren
r_char
op_star
)paren
l_int|0
)brace
)brace
suffix:semicolon
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
DECL|macro|TW_CONTROL_CLEAR_QUEUE_ERROR
mdefine_line|#define TW_CONTROL_CLEAR_QUEUE_ERROR           0x00400000
DECL|macro|TW_CONTROL_CLEAR_PCI_ABORT
mdefine_line|#define TW_CONTROL_CLEAR_PCI_ABORT             0x00100000
DECL|macro|TW_CONTROL_CLEAR_SBUF_WRITE_ERROR
mdefine_line|#define TW_CONTROL_CLEAR_SBUF_WRITE_ERROR      0x00000008
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
DECL|macro|TW_STATUS_EXPECTED_BITS
mdefine_line|#define TW_STATUS_EXPECTED_BITS&t;&t;       0x00002000
DECL|macro|TW_STATUS_UNEXPECTED_BITS
mdefine_line|#define TW_STATUS_UNEXPECTED_BITS&t;       0x00F00008
DECL|macro|TW_STATUS_SBUF_WRITE_ERROR
mdefine_line|#define TW_STATUS_SBUF_WRITE_ERROR             0x00000008
DECL|macro|TW_STATUS_VALID_INTERRUPT
mdefine_line|#define TW_STATUS_VALID_INTERRUPT              0x00DF0008
multiline_comment|/* RESPONSE QUEUE BIT DEFINITIONS */
DECL|macro|TW_RESPONSE_ID_MASK
mdefine_line|#define TW_RESPONSE_ID_MASK&t;&t;       0x00000FF0
multiline_comment|/* PCI related defines */
DECL|macro|TW_DEVICE_NAME
mdefine_line|#define TW_DEVICE_NAME&t;&t;&t;       &quot;3w-9xxx&quot;
DECL|macro|TW_NUMDEVICES
mdefine_line|#define TW_NUMDEVICES 1
DECL|macro|TW_PCI_CLEAR_PARITY_ERRORS
mdefine_line|#define TW_PCI_CLEAR_PARITY_ERRORS 0xc100
DECL|macro|TW_PCI_CLEAR_PCI_ABORT
mdefine_line|#define TW_PCI_CLEAR_PCI_ABORT     0x2000
multiline_comment|/* Command packet opcodes used by the driver */
DECL|macro|TW_OP_INIT_CONNECTION
mdefine_line|#define TW_OP_INIT_CONNECTION 0x1
DECL|macro|TW_OP_GET_PARAM
mdefine_line|#define TW_OP_GET_PARAM&t;      0x12
DECL|macro|TW_OP_SET_PARAM
mdefine_line|#define TW_OP_SET_PARAM&t;      0x13
DECL|macro|TW_OP_EXECUTE_SCSI
mdefine_line|#define TW_OP_EXECUTE_SCSI    0x10
DECL|macro|TW_OP_DOWNLOAD_FIRMWARE
mdefine_line|#define TW_OP_DOWNLOAD_FIRMWARE 0x16
DECL|macro|TW_OP_RESET
mdefine_line|#define TW_OP_RESET             0x1C
multiline_comment|/* Asynchronous Event Notification (AEN) codes used by the driver */
DECL|macro|TW_AEN_QUEUE_EMPTY
mdefine_line|#define TW_AEN_QUEUE_EMPTY       0x0000
DECL|macro|TW_AEN_SOFT_RESET
mdefine_line|#define TW_AEN_SOFT_RESET        0x0001
DECL|macro|TW_AEN_SYNC_TIME_WITH_HOST
mdefine_line|#define TW_AEN_SYNC_TIME_WITH_HOST 0x031
DECL|macro|TW_AEN_SEVERITY_ERROR
mdefine_line|#define TW_AEN_SEVERITY_ERROR    0x1
DECL|macro|TW_AEN_SEVERITY_DEBUG
mdefine_line|#define TW_AEN_SEVERITY_DEBUG    0x4
DECL|macro|TW_AEN_NOT_RETRIEVED
mdefine_line|#define TW_AEN_NOT_RETRIEVED 0x1
DECL|macro|TW_AEN_RETRIEVED
mdefine_line|#define TW_AEN_RETRIEVED 0x2
multiline_comment|/* Command state defines */
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
multiline_comment|/* Compatibility defines */
DECL|macro|TW_9000_ARCH_ID
mdefine_line|#define TW_9000_ARCH_ID 0x5
DECL|macro|TW_CURRENT_FW_SRL
mdefine_line|#define TW_CURRENT_FW_SRL 24
DECL|macro|TW_CURRENT_FW_BUILD
mdefine_line|#define TW_CURRENT_FW_BUILD 5
DECL|macro|TW_CURRENT_FW_BRANCH
mdefine_line|#define TW_CURRENT_FW_BRANCH 1
multiline_comment|/* Phase defines */
DECL|macro|TW_PHASE_INITIAL
mdefine_line|#define TW_PHASE_INITIAL 0
DECL|macro|TW_PHASE_SINGLE
mdefine_line|#define TW_PHASE_SINGLE  1
DECL|macro|TW_PHASE_SGLIST
mdefine_line|#define TW_PHASE_SGLIST  2
multiline_comment|/* Misc defines */
DECL|macro|TW_SECTOR_SIZE
mdefine_line|#define TW_SECTOR_SIZE                        512
DECL|macro|TW_ALIGNMENT_9000
mdefine_line|#define TW_ALIGNMENT_9000                     4  /* 4 bytes */
DECL|macro|TW_ALIGNMENT_9000_SGL
mdefine_line|#define TW_ALIGNMENT_9000_SGL                 0x3
DECL|macro|TW_MAX_UNITS
mdefine_line|#define TW_MAX_UNITS&t;&t;&t;      16
DECL|macro|TW_INIT_MESSAGE_CREDITS
mdefine_line|#define TW_INIT_MESSAGE_CREDITS&t;&t;      0x100
DECL|macro|TW_INIT_COMMAND_PACKET_SIZE
mdefine_line|#define TW_INIT_COMMAND_PACKET_SIZE&t;      0x3
DECL|macro|TW_INIT_COMMAND_PACKET_SIZE_EXTENDED
mdefine_line|#define TW_INIT_COMMAND_PACKET_SIZE_EXTENDED  0x6
DECL|macro|TW_EXTENDED_INIT_CONNECT
mdefine_line|#define TW_EXTENDED_INIT_CONNECT&t;      0x2
DECL|macro|TW_BUNDLED_FW_SAFE_TO_FLASH
mdefine_line|#define TW_BUNDLED_FW_SAFE_TO_FLASH&t;      0x4
DECL|macro|TW_CTLR_FW_RECOMMENDS_FLASH
mdefine_line|#define TW_CTLR_FW_RECOMMENDS_FLASH&t;      0x8
DECL|macro|TW_CTLR_FW_COMPATIBLE
mdefine_line|#define TW_CTLR_FW_COMPATIBLE&t;&t;      0x2
DECL|macro|TW_BASE_FW_SRL
mdefine_line|#define TW_BASE_FW_SRL&t;&t;&t;      0x17
DECL|macro|TW_BASE_FW_BRANCH
mdefine_line|#define TW_BASE_FW_BRANCH&t;&t;      0
DECL|macro|TW_BASE_FW_BUILD
mdefine_line|#define TW_BASE_FW_BUILD&t;&t;      1
macro_line|#if BITS_PER_LONG &gt; 32
DECL|macro|TW_APACHE_MAX_SGL_LENGTH
mdefine_line|#define TW_APACHE_MAX_SGL_LENGTH 72
DECL|macro|TW_ESCALADE_MAX_SGL_LENGTH
mdefine_line|#define TW_ESCALADE_MAX_SGL_LENGTH 41
DECL|macro|TW_APACHE_CMD_PKT_SIZE
mdefine_line|#define TW_APACHE_CMD_PKT_SIZE 5
macro_line|#else
DECL|macro|TW_APACHE_MAX_SGL_LENGTH
mdefine_line|#define TW_APACHE_MAX_SGL_LENGTH 109
DECL|macro|TW_ESCALADE_MAX_SGL_LENGTH
mdefine_line|#define TW_ESCALADE_MAX_SGL_LENGTH 62
DECL|macro|TW_APACHE_CMD_PKT_SIZE
mdefine_line|#define TW_APACHE_CMD_PKT_SIZE 4
macro_line|#endif
DECL|macro|TW_ATA_PASS_SGL_MAX
mdefine_line|#define TW_ATA_PASS_SGL_MAX                   60
DECL|macro|TW_Q_LENGTH
mdefine_line|#define TW_Q_LENGTH&t;&t;&t;      256
DECL|macro|TW_Q_START
mdefine_line|#define TW_Q_START&t;&t;&t;      0
DECL|macro|TW_MAX_SLOT
mdefine_line|#define TW_MAX_SLOT&t;&t;&t;      32
DECL|macro|TW_MAX_RESET_TRIES
mdefine_line|#define TW_MAX_RESET_TRIES&t;&t;      2
DECL|macro|TW_MAX_CMDS_PER_LUN
mdefine_line|#define TW_MAX_CMDS_PER_LUN&t;&t;      254
DECL|macro|TW_MAX_RESPONSE_DRAIN
mdefine_line|#define TW_MAX_RESPONSE_DRAIN&t;&t;      256
DECL|macro|TW_MAX_AEN_DRAIN
mdefine_line|#define TW_MAX_AEN_DRAIN&t;&t;      40
DECL|macro|TW_IN_IOCTL
mdefine_line|#define TW_IN_IOCTL                           2
DECL|macro|TW_IN_CHRDEV_IOCTL
mdefine_line|#define TW_IN_CHRDEV_IOCTL                    3
DECL|macro|TW_IN_ATTENTION_LOOP
mdefine_line|#define TW_IN_ATTENTION_LOOP&t;&t;      4
DECL|macro|TW_MAX_SECTORS
mdefine_line|#define TW_MAX_SECTORS                        256
DECL|macro|TW_AEN_WAIT_TIME
mdefine_line|#define TW_AEN_WAIT_TIME                      1000
DECL|macro|TW_IOCTL_WAIT_TIME
mdefine_line|#define TW_IOCTL_WAIT_TIME                    (1 * HZ) /* 1 second */
DECL|macro|TW_MAX_CDB_LEN
mdefine_line|#define TW_MAX_CDB_LEN                        16
DECL|macro|TW_ISR_DONT_COMPLETE
mdefine_line|#define TW_ISR_DONT_COMPLETE                  2
DECL|macro|TW_ISR_DONT_RESULT
mdefine_line|#define TW_ISR_DONT_RESULT                    3
DECL|macro|TW_IOCTL_CHRDEV_TIMEOUT
mdefine_line|#define TW_IOCTL_CHRDEV_TIMEOUT               60 /* 60 seconds */
DECL|macro|TW_IOCTL_CHRDEV_FREE
mdefine_line|#define TW_IOCTL_CHRDEV_FREE                  -1
DECL|macro|TW_COMMAND_OFFSET
mdefine_line|#define TW_COMMAND_OFFSET                     128 /* 128 bytes */
DECL|macro|TW_VERSION_TABLE
mdefine_line|#define TW_VERSION_TABLE                      0x0402
DECL|macro|TW_TIMEKEEP_TABLE
mdefine_line|#define TW_TIMEKEEP_TABLE&t;&t;      0x040A
DECL|macro|TW_INFORMATION_TABLE
mdefine_line|#define TW_INFORMATION_TABLE&t;&t;      0x0403
DECL|macro|TW_PARAM_FWVER
mdefine_line|#define TW_PARAM_FWVER&t;&t;&t;      3
DECL|macro|TW_PARAM_FWVER_LENGTH
mdefine_line|#define TW_PARAM_FWVER_LENGTH&t;&t;      16
DECL|macro|TW_PARAM_BIOSVER
mdefine_line|#define TW_PARAM_BIOSVER&t;&t;      4
DECL|macro|TW_PARAM_BIOSVER_LENGTH
mdefine_line|#define TW_PARAM_BIOSVER_LENGTH&t;&t;      16
DECL|macro|TW_PARAM_PORTCOUNT
mdefine_line|#define TW_PARAM_PORTCOUNT&t;&t;      3
DECL|macro|TW_PARAM_PORTCOUNT_LENGTH
mdefine_line|#define TW_PARAM_PORTCOUNT_LENGTH&t;      1
DECL|macro|TW_MIN_SGL_LENGTH
mdefine_line|#define TW_MIN_SGL_LENGTH                     0x200 /* 512 bytes */
DECL|macro|TW_MAX_SENSE_LENGTH
mdefine_line|#define TW_MAX_SENSE_LENGTH                   256
DECL|macro|TW_EVENT_SOURCE_AEN
mdefine_line|#define TW_EVENT_SOURCE_AEN                   0x1000
DECL|macro|TW_EVENT_SOURCE_COMMAND
mdefine_line|#define TW_EVENT_SOURCE_COMMAND               0x1001
DECL|macro|TW_EVENT_SOURCE_PCHIP
mdefine_line|#define TW_EVENT_SOURCE_PCHIP                 0x1002
DECL|macro|TW_EVENT_SOURCE_DRIVER
mdefine_line|#define TW_EVENT_SOURCE_DRIVER                0x1003
DECL|macro|TW_IOCTL_GET_COMPATIBILITY_INFO
mdefine_line|#define TW_IOCTL_GET_COMPATIBILITY_INFO&t;      0x101
DECL|macro|TW_IOCTL_GET_LAST_EVENT
mdefine_line|#define TW_IOCTL_GET_LAST_EVENT               0x102
DECL|macro|TW_IOCTL_GET_FIRST_EVENT
mdefine_line|#define TW_IOCTL_GET_FIRST_EVENT              0x103
DECL|macro|TW_IOCTL_GET_NEXT_EVENT
mdefine_line|#define TW_IOCTL_GET_NEXT_EVENT               0x104
DECL|macro|TW_IOCTL_GET_PREVIOUS_EVENT
mdefine_line|#define TW_IOCTL_GET_PREVIOUS_EVENT           0x105
DECL|macro|TW_IOCTL_GET_LOCK
mdefine_line|#define TW_IOCTL_GET_LOCK                     0x106
DECL|macro|TW_IOCTL_RELEASE_LOCK
mdefine_line|#define TW_IOCTL_RELEASE_LOCK                 0x107
DECL|macro|TW_IOCTL_FIRMWARE_PASS_THROUGH
mdefine_line|#define TW_IOCTL_FIRMWARE_PASS_THROUGH        0x108
DECL|macro|TW_IOCTL_ERROR_STATUS_NOT_LOCKED
mdefine_line|#define TW_IOCTL_ERROR_STATUS_NOT_LOCKED      0x1001 
singleline_comment|// Not locked
DECL|macro|TW_IOCTL_ERROR_STATUS_LOCKED
mdefine_line|#define TW_IOCTL_ERROR_STATUS_LOCKED          0x1002 
singleline_comment|// Already locked
DECL|macro|TW_IOCTL_ERROR_STATUS_NO_MORE_EVENTS
mdefine_line|#define TW_IOCTL_ERROR_STATUS_NO_MORE_EVENTS  0x1003 
singleline_comment|// No more events
DECL|macro|TW_IOCTL_ERROR_STATUS_AEN_CLOBBER
mdefine_line|#define TW_IOCTL_ERROR_STATUS_AEN_CLOBBER     0x1004 
singleline_comment|// AEN clobber occurred
DECL|macro|TW_IOCTL_ERROR_OS_EFAULT
mdefine_line|#define TW_IOCTL_ERROR_OS_EFAULT&t;      -EFAULT 
singleline_comment|// Bad address
DECL|macro|TW_IOCTL_ERROR_OS_EINTR
mdefine_line|#define TW_IOCTL_ERROR_OS_EINTR&t;&t;      -EINTR  
singleline_comment|// Interrupted system call
DECL|macro|TW_IOCTL_ERROR_OS_EINVAL
mdefine_line|#define TW_IOCTL_ERROR_OS_EINVAL&t;      -EINVAL 
singleline_comment|// Invalid argument
DECL|macro|TW_IOCTL_ERROR_OS_ENOMEM
mdefine_line|#define TW_IOCTL_ERROR_OS_ENOMEM&t;      -ENOMEM 
singleline_comment|// Out of memory
DECL|macro|TW_IOCTL_ERROR_OS_ERESTARTSYS
mdefine_line|#define TW_IOCTL_ERROR_OS_ERESTARTSYS&t;      -ERESTARTSYS 
singleline_comment|// Restart system call
DECL|macro|TW_IOCTL_ERROR_OS_EIO
mdefine_line|#define TW_IOCTL_ERROR_OS_EIO&t;&t;      -EIO 
singleline_comment|// I/O error
DECL|macro|TW_IOCTL_ERROR_OS_ENOTTY
mdefine_line|#define TW_IOCTL_ERROR_OS_ENOTTY&t;      -ENOTTY 
singleline_comment|// Not a typewriter
DECL|macro|TW_IOCTL_ERROR_OS_ENODEV
mdefine_line|#define TW_IOCTL_ERROR_OS_ENODEV&t;      -ENODEV 
singleline_comment|// No such device
DECL|macro|TW_ALLOCATION_LENGTH
mdefine_line|#define TW_ALLOCATION_LENGTH&t;&t;      128
DECL|macro|TW_SENSE_DATA_LENGTH
mdefine_line|#define TW_SENSE_DATA_LENGTH&t;&t;      18
DECL|macro|TW_STATUS_CHECK_CONDITION
mdefine_line|#define TW_STATUS_CHECK_CONDITION&t;      2
DECL|macro|TW_ERROR_LOGICAL_UNIT_NOT_SUPPORTED
mdefine_line|#define TW_ERROR_LOGICAL_UNIT_NOT_SUPPORTED   0x10a
DECL|macro|TW_ERROR_UNIT_OFFLINE
mdefine_line|#define TW_ERROR_UNIT_OFFLINE                 0x128
DECL|macro|TW_MESSAGE_SOURCE_CONTROLLER_ERROR
mdefine_line|#define TW_MESSAGE_SOURCE_CONTROLLER_ERROR    3
DECL|macro|TW_MESSAGE_SOURCE_CONTROLLER_EVENT
mdefine_line|#define TW_MESSAGE_SOURCE_CONTROLLER_EVENT    4
DECL|macro|TW_MESSAGE_SOURCE_LINUX_DRIVER
mdefine_line|#define TW_MESSAGE_SOURCE_LINUX_DRIVER        6
DECL|macro|TW_DRIVER
mdefine_line|#define TW_DRIVER TW_MESSAGE_SOURCE_LINUX_DRIVER
DECL|macro|TW_MESSAGE_SOURCE_LINUX_OS
mdefine_line|#define TW_MESSAGE_SOURCE_LINUX_OS            9
DECL|macro|TW_OS
mdefine_line|#define TW_OS TW_MESSAGE_SOURCE_LINUX_OS
macro_line|#if BITS_PER_LONG &gt; 32
DECL|macro|TW_COMMAND_SIZE
mdefine_line|#define TW_COMMAND_SIZE&t;&t;&t;      5
DECL|macro|TW_DMA_MASK
mdefine_line|#define TW_DMA_MASK&t;&t;&t;      DMA_64BIT_MASK
macro_line|#else
DECL|macro|TW_COMMAND_SIZE
mdefine_line|#define TW_COMMAND_SIZE&t;&t;&t;      4
DECL|macro|TW_DMA_MASK
mdefine_line|#define TW_DMA_MASK&t;&t;&t;      DMA_32BIT_MASK
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_3WARE_9000
DECL|macro|PCI_DEVICE_ID_3WARE_9000
mdefine_line|#define PCI_DEVICE_ID_3WARE_9000 0x1002
macro_line|#endif
multiline_comment|/* Bitmask macros to eliminate bitfields */
multiline_comment|/* opcode: 5, reserved: 3 */
DECL|macro|TW_OPRES_IN
mdefine_line|#define TW_OPRES_IN(x,y) ((x &lt;&lt; 5) | (y &amp; 0x1f))
DECL|macro|TW_OP_OUT
mdefine_line|#define TW_OP_OUT(x) (x &amp; 0x1f)
multiline_comment|/* opcode: 5, sgloffset: 3 */
DECL|macro|TW_OPSGL_IN
mdefine_line|#define TW_OPSGL_IN(x,y) ((x &lt;&lt; 5) | (y &amp; 0x1f))
DECL|macro|TW_SGL_OUT
mdefine_line|#define TW_SGL_OUT(x) ((x &gt;&gt; 5) &amp; 0x7)
multiline_comment|/* severity: 3, reserved: 5 */
DECL|macro|TW_SEV_OUT
mdefine_line|#define TW_SEV_OUT(x) (x &amp; 0x7)
multiline_comment|/* reserved_1: 4, response_id: 8, reserved_2: 20 */
DECL|macro|TW_RESID_OUT
mdefine_line|#define TW_RESID_OUT(x) ((x &gt;&gt; 4) &amp; 0xff)
multiline_comment|/* Macros */
DECL|macro|TW_CONTROL_REG_ADDR
mdefine_line|#define TW_CONTROL_REG_ADDR(x) (x-&gt;base_addr)
DECL|macro|TW_STATUS_REG_ADDR
mdefine_line|#define TW_STATUS_REG_ADDR(x) ((unsigned char __iomem *)x-&gt;base_addr + 0x4)
macro_line|#if BITS_PER_LONG &gt; 32
DECL|macro|TW_COMMAND_QUEUE_REG_ADDR
mdefine_line|#define TW_COMMAND_QUEUE_REG_ADDR(x) ((unsigned char __iomem *)x-&gt;base_addr + 0x20)
macro_line|#else
DECL|macro|TW_COMMAND_QUEUE_REG_ADDR
mdefine_line|#define TW_COMMAND_QUEUE_REG_ADDR(x) ((unsigned char __iomem *)x-&gt;base_addr + 0x8)
macro_line|#endif
DECL|macro|TW_RESPONSE_QUEUE_REG_ADDR
mdefine_line|#define TW_RESPONSE_QUEUE_REG_ADDR(x) ((unsigned char __iomem *)x-&gt;base_addr + 0xC)
DECL|macro|TW_CLEAR_ALL_INTERRUPTS
mdefine_line|#define TW_CLEAR_ALL_INTERRUPTS(x) (writel(TW_STATUS_VALID_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
DECL|macro|TW_CLEAR_ATTENTION_INTERRUPT
mdefine_line|#define TW_CLEAR_ATTENTION_INTERRUPT(x) (writel(TW_CONTROL_CLEAR_ATTENTION_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
DECL|macro|TW_CLEAR_HOST_INTERRUPT
mdefine_line|#define TW_CLEAR_HOST_INTERRUPT(x) (writel(TW_CONTROL_CLEAR_HOST_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
DECL|macro|TW_DISABLE_INTERRUPTS
mdefine_line|#define TW_DISABLE_INTERRUPTS(x) (writel(TW_CONTROL_DISABLE_INTERRUPTS, TW_CONTROL_REG_ADDR(x)))
DECL|macro|TW_ENABLE_AND_CLEAR_INTERRUPTS
mdefine_line|#define TW_ENABLE_AND_CLEAR_INTERRUPTS(x) (writel(TW_CONTROL_CLEAR_ATTENTION_INTERRUPT | TW_CONTROL_UNMASK_RESPONSE_INTERRUPT | TW_CONTROL_ENABLE_INTERRUPTS, TW_CONTROL_REG_ADDR(x)))
DECL|macro|TW_MASK_COMMAND_INTERRUPT
mdefine_line|#define TW_MASK_COMMAND_INTERRUPT(x) (writel(TW_CONTROL_MASK_COMMAND_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
DECL|macro|TW_UNMASK_COMMAND_INTERRUPT
mdefine_line|#define TW_UNMASK_COMMAND_INTERRUPT(x) (writel(TW_CONTROL_UNMASK_COMMAND_INTERRUPT, TW_CONTROL_REG_ADDR(x)))
DECL|macro|TW_SOFT_RESET
mdefine_line|#define TW_SOFT_RESET(x) (writel(TW_CONTROL_ISSUE_SOFT_RESET | &bslash;&n;&t;&t;&t;TW_CONTROL_CLEAR_HOST_INTERRUPT | &bslash;&n;&t;&t;&t;TW_CONTROL_CLEAR_ATTENTION_INTERRUPT | &bslash;&n;&t;&t;&t;TW_CONTROL_MASK_COMMAND_INTERRUPT | &bslash;&n;&t;&t;&t;TW_CONTROL_MASK_RESPONSE_INTERRUPT | &bslash;&n;&t;&t;&t;TW_CONTROL_CLEAR_ERROR_STATUS | &bslash;&n;&t;&t;&t;TW_CONTROL_DISABLE_INTERRUPTS, TW_CONTROL_REG_ADDR(x)))
DECL|macro|TW_PRINTK
mdefine_line|#define TW_PRINTK(h,a,b,c) { &bslash;&n;if (h) &bslash;&n;printk(KERN_WARNING &quot;3w-9xxx: scsi%d: ERROR: (0x%02X:0x%04X): %s.&bslash;n&quot;,h-&gt;host_no,a,b,c); &bslash;&n;else &bslash;&n;printk(KERN_WARNING &quot;3w-9xxx: ERROR: (0x%02X:0x%04X): %s.&bslash;n&quot;,a,b,c); &bslash;&n;}
macro_line|#pragma pack(1)
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
id|u32
id|length
suffix:semicolon
DECL|typedef|TW_SG_Entry
)brace
id|TW_SG_Entry
suffix:semicolon
multiline_comment|/* Command Packet */
DECL|struct|TW_Command
r_typedef
r_struct
id|TW_Command
(brace
DECL|member|opcode__sgloffset
r_int
r_char
id|opcode__sgloffset
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
DECL|member|unit__hostid
r_int
r_char
id|unit__hostid
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
DECL|member|byte6_offset
)brace
id|byte6_offset
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|lba
id|u32
id|lba
suffix:semicolon
DECL|member|sgl
id|TW_SG_Entry
id|sgl
(braket
id|TW_ESCALADE_MAX_SGL_LENGTH
)braket
suffix:semicolon
macro_line|#if BITS_PER_LONG &gt; 32
DECL|member|padding
id|u32
id|padding
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* pad to 512 bytes */
macro_line|#else
DECL|member|padding
id|u32
id|padding
suffix:semicolon
macro_line|#endif
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
id|TW_ESCALADE_MAX_SGL_LENGTH
)braket
suffix:semicolon
macro_line|#if BITS_PER_LONG &gt; 32
DECL|member|padding
id|u32
id|padding
(braket
l_int|3
)braket
suffix:semicolon
macro_line|#else
DECL|member|padding
id|u32
id|padding
(braket
l_int|2
)braket
suffix:semicolon
macro_line|#endif
DECL|member|param
)brace
id|param
suffix:semicolon
DECL|member|byte8_offset
)brace
id|byte8_offset
suffix:semicolon
DECL|typedef|TW_Command
)brace
id|TW_Command
suffix:semicolon
multiline_comment|/* Scatter gather element for 9000+ controllers */
DECL|struct|TAG_TW_SG_Apache
r_typedef
r_struct
id|TAG_TW_SG_Apache
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|typedef|TW_SG_Apache
)brace
id|TW_SG_Apache
suffix:semicolon
multiline_comment|/* Command Packet for 9000+ controllers */
DECL|struct|TAG_TW_Command_Apache
r_typedef
r_struct
id|TAG_TW_Command_Apache
(brace
DECL|member|opcode__reserved
r_int
r_char
id|opcode__reserved
suffix:semicolon
DECL|member|unit
r_int
r_char
id|unit
suffix:semicolon
DECL|member|request_id
r_int
r_int
id|request_id
suffix:semicolon
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
DECL|member|sgl_offset
r_int
r_char
id|sgl_offset
suffix:semicolon
DECL|member|sgl_entries
r_int
r_int
id|sgl_entries
suffix:semicolon
DECL|member|cdb
r_int
r_char
id|cdb
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sg_list
id|TW_SG_Apache
id|sg_list
(braket
id|TW_APACHE_MAX_SGL_LENGTH
)braket
suffix:semicolon
macro_line|#if BITS_PER_LONG &gt; 32
DECL|member|padding
r_int
r_char
id|padding
(braket
l_int|8
)braket
suffix:semicolon
macro_line|#endif
DECL|typedef|TW_Command_Apache
)brace
id|TW_Command_Apache
suffix:semicolon
multiline_comment|/* New command packet header */
DECL|struct|TAG_TW_Command_Apache_Header
r_typedef
r_struct
id|TAG_TW_Command_Apache_Header
(brace
DECL|member|sense_data
r_int
r_char
id|sense_data
(braket
id|TW_SENSE_DATA_LENGTH
)braket
suffix:semicolon
r_struct
(brace
DECL|member|reserved
r_char
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|error
r_int
r_int
id|error
suffix:semicolon
DECL|member|padding
r_int
r_char
id|padding
suffix:semicolon
DECL|member|severity__reserved
r_int
r_char
id|severity__reserved
suffix:semicolon
DECL|member|status_block
)brace
id|status_block
suffix:semicolon
DECL|member|err_specific_desc
r_int
r_char
id|err_specific_desc
(braket
l_int|98
)braket
suffix:semicolon
r_struct
(brace
DECL|member|size_header
r_int
r_char
id|size_header
suffix:semicolon
DECL|member|reserved
r_int
r_int
id|reserved
suffix:semicolon
DECL|member|size_sense
r_int
r_char
id|size_sense
suffix:semicolon
DECL|member|header_desc
)brace
id|header_desc
suffix:semicolon
DECL|typedef|TW_Command_Apache_Header
)brace
id|TW_Command_Apache_Header
suffix:semicolon
multiline_comment|/* This struct is a union of the 2 command packets */
DECL|struct|TAG_TW_Command_Full
r_typedef
r_struct
id|TAG_TW_Command_Full
(brace
DECL|member|header
id|TW_Command_Apache_Header
id|header
suffix:semicolon
r_union
(brace
DECL|member|oldcommand
id|TW_Command
id|oldcommand
suffix:semicolon
DECL|member|newcommand
id|TW_Command_Apache
id|newcommand
suffix:semicolon
DECL|member|command
)brace
id|command
suffix:semicolon
DECL|typedef|TW_Command_Full
)brace
id|TW_Command_Full
suffix:semicolon
multiline_comment|/* Initconnection structure */
DECL|struct|TAG_TW_Initconnect
r_typedef
r_struct
id|TAG_TW_Initconnect
(brace
DECL|member|opcode__reserved
r_int
r_char
id|opcode__reserved
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
DECL|member|res2
r_int
r_char
id|res2
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
DECL|member|message_credits
r_int
r_int
id|message_credits
suffix:semicolon
DECL|member|features
id|u32
id|features
suffix:semicolon
DECL|member|fw_srl
r_int
r_int
id|fw_srl
suffix:semicolon
DECL|member|fw_arch_id
r_int
r_int
id|fw_arch_id
suffix:semicolon
DECL|member|fw_branch
r_int
r_int
id|fw_branch
suffix:semicolon
DECL|member|fw_build
r_int
r_int
id|fw_build
suffix:semicolon
DECL|member|result
id|u32
id|result
suffix:semicolon
DECL|typedef|TW_Initconnect
)brace
id|TW_Initconnect
suffix:semicolon
multiline_comment|/* Event info structure */
DECL|struct|TAG_TW_Event
r_typedef
r_struct
id|TAG_TW_Event
(brace
DECL|member|sequence_id
r_int
r_int
id|sequence_id
suffix:semicolon
DECL|member|time_stamp_sec
r_int
r_int
id|time_stamp_sec
suffix:semicolon
DECL|member|aen_code
r_int
r_int
id|aen_code
suffix:semicolon
DECL|member|severity
r_int
r_char
id|severity
suffix:semicolon
DECL|member|retrieved
r_int
r_char
id|retrieved
suffix:semicolon
DECL|member|repeat_count
r_int
r_char
id|repeat_count
suffix:semicolon
DECL|member|parameter_len
r_int
r_char
id|parameter_len
suffix:semicolon
DECL|member|parameter_data
r_int
r_char
id|parameter_data
(braket
l_int|98
)braket
suffix:semicolon
DECL|typedef|TW_Event
)brace
id|TW_Event
suffix:semicolon
DECL|struct|TAG_TW_Ioctl_Driver_Command
r_typedef
r_struct
id|TAG_TW_Ioctl_Driver_Command
(brace
DECL|member|control_code
r_int
r_int
id|control_code
suffix:semicolon
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
DECL|member|unique_id
r_int
r_int
id|unique_id
suffix:semicolon
DECL|member|sequence_id
r_int
r_int
id|sequence_id
suffix:semicolon
DECL|member|os_specific
r_int
r_int
id|os_specific
suffix:semicolon
DECL|member|buffer_length
r_int
r_int
id|buffer_length
suffix:semicolon
DECL|typedef|TW_Ioctl_Driver_Command
)brace
id|TW_Ioctl_Driver_Command
suffix:semicolon
DECL|struct|TAG_TW_Ioctl_Apache
r_typedef
r_struct
id|TAG_TW_Ioctl_Apache
(brace
DECL|member|driver_command
id|TW_Ioctl_Driver_Command
id|driver_command
suffix:semicolon
DECL|member|padding
r_char
id|padding
(braket
l_int|488
)braket
suffix:semicolon
DECL|member|firmware_command
id|TW_Command_Full
id|firmware_command
suffix:semicolon
DECL|member|data_buffer
r_char
id|data_buffer
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|TW_Ioctl_Buf_Apache
)brace
id|TW_Ioctl_Buf_Apache
suffix:semicolon
multiline_comment|/* Lock structure for ioctl get/release lock */
DECL|struct|TAG_TW_Lock
r_typedef
r_struct
id|TAG_TW_Lock
(brace
DECL|member|timeout_msec
r_int
r_int
id|timeout_msec
suffix:semicolon
DECL|member|time_remaining_msec
r_int
r_int
id|time_remaining_msec
suffix:semicolon
DECL|member|force_flag
r_int
r_int
id|force_flag
suffix:semicolon
DECL|typedef|TW_Lock
)brace
id|TW_Lock
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
r_int
id|parameter_id
suffix:semicolon
DECL|member|parameter_size_bytes
r_int
r_int
id|parameter_size_bytes
suffix:semicolon
DECL|member|actual_parameter_size_bytes
r_int
r_int
id|actual_parameter_size_bytes
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|TW_Param_Apache
DECL|typedef|PTW_Param_Apache
)brace
id|TW_Param_Apache
comma
op_star
id|PTW_Param_Apache
suffix:semicolon
multiline_comment|/* Response queue */
DECL|union|TAG_TW_Response_Queue
r_typedef
r_union
id|TAG_TW_Response_Queue
(brace
DECL|member|response_id
id|u32
id|response_id
suffix:semicolon
DECL|member|value
id|u32
id|value
suffix:semicolon
DECL|typedef|TW_Response_Queue
)brace
id|TW_Response_Queue
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
multiline_comment|/* Compatibility information structure */
DECL|struct|TAG_TW_Compatibility_Info
r_typedef
r_struct
id|TAG_TW_Compatibility_Info
(brace
DECL|member|driver_version
r_char
id|driver_version
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|working_srl
r_int
r_int
id|working_srl
suffix:semicolon
DECL|member|working_branch
r_int
r_int
id|working_branch
suffix:semicolon
DECL|member|working_build
r_int
r_int
id|working_build
suffix:semicolon
DECL|typedef|TW_Compatibility_Info
)brace
id|TW_Compatibility_Info
suffix:semicolon
DECL|struct|TAG_TW_Device_Extension
r_typedef
r_struct
id|TAG_TW_Device_Extension
(brace
DECL|member|base_addr
id|u32
id|__iomem
op_star
id|base_addr
suffix:semicolon
DECL|member|generic_buffer_virt
r_int
r_int
op_star
id|generic_buffer_virt
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|generic_buffer_phys
r_int
r_int
id|generic_buffer_phys
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|command_packet_virt
id|TW_Command_Full
op_star
id|command_packet_virt
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|command_packet_phys
r_int
r_int
id|command_packet_phys
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
r_struct
id|scsi_cmnd
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
r_int
id|state
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|posted_request_count
r_int
r_int
id|posted_request_count
suffix:semicolon
DECL|member|max_posted_request_count
r_int
r_int
id|max_posted_request_count
suffix:semicolon
DECL|member|pending_request_count
r_int
r_int
id|pending_request_count
suffix:semicolon
DECL|member|max_pending_request_count
r_int
r_int
id|max_pending_request_count
suffix:semicolon
DECL|member|max_sgl_entries
r_int
r_int
id|max_sgl_entries
suffix:semicolon
DECL|member|sgl_entries
r_int
r_int
id|sgl_entries
suffix:semicolon
DECL|member|num_aborts
r_int
r_int
id|num_aborts
suffix:semicolon
DECL|member|num_resets
r_int
r_int
id|num_resets
suffix:semicolon
DECL|member|sector_count
r_int
r_int
id|sector_count
suffix:semicolon
DECL|member|max_sector_count
r_int
r_int
id|max_sector_count
suffix:semicolon
DECL|member|aen_count
r_int
r_int
id|aen_count
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|reset_print
r_int
id|reset_print
suffix:semicolon
DECL|member|event_queue
id|TW_Event
op_star
id|event_queue
(braket
id|TW_Q_LENGTH
)braket
suffix:semicolon
DECL|member|error_index
r_int
r_char
id|error_index
suffix:semicolon
DECL|member|event_queue_wrapped
r_int
r_char
id|event_queue_wrapped
suffix:semicolon
DECL|member|error_sequence_id
r_int
r_int
id|error_sequence_id
suffix:semicolon
DECL|member|ioctl_sem_lock
r_int
id|ioctl_sem_lock
suffix:semicolon
DECL|member|ioctl_msec
id|u32
id|ioctl_msec
suffix:semicolon
DECL|member|chrdev_request_id
r_int
id|chrdev_request_id
suffix:semicolon
DECL|member|ioctl_wqueue
id|wait_queue_head_t
id|ioctl_wqueue
suffix:semicolon
DECL|member|ioctl_sem
r_struct
id|semaphore
id|ioctl_sem
suffix:semicolon
DECL|member|aen_clobber
r_char
id|aen_clobber
suffix:semicolon
DECL|member|working_srl
r_int
r_int
id|working_srl
suffix:semicolon
DECL|member|working_branch
r_int
r_int
id|working_branch
suffix:semicolon
DECL|member|working_build
r_int
r_int
id|working_build
suffix:semicolon
DECL|typedef|TW_Device_Extension
)brace
id|TW_Device_Extension
suffix:semicolon
macro_line|#pragma pack()
macro_line|#endif /* _3W_9XXX_H */
eof
