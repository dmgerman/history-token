multiline_comment|/*&n; *  linux/drivers/message/fusion/mptioctl.h&n; *      Fusion MPT misc device (ioctl) driver.&n; *      For use with PCI chip/adapter(s):&n; *          LSIFC9xx/LSI409xx Fibre Channel&n; *      running LSI Logic Fusion MPT (Message Passing Technology) firmware.&n; *&n; *  Credits:&n; *      This driver would not exist if not for Alan Cox&squot;s development&n; *      of the linux i2o driver.&n; *&n; *      A huge debt of gratitude is owed to David S. Miller (DaveM)&n; *      for fixing much of the stupid and broken stuff in the early&n; *      driver while porting to sparc64 platform.  THANK YOU!&n; *&n; *      (see also mptbase.c)&n; *&n; *  Copyright (c) 1999-2002 LSI Logic Corporation&n; *  Originally By: Steven J. Ralston&n; *  (mailto:sjralston1@netscape.net)&n; *  (mailto:Pam.Delaney@lsil.com)&n; *&n; *  $Id: mptctl.h,v 1.13 2002/12/03 21:26:33 pdelaney Exp $&n; */
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; version 2 of the License.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    NO WARRANTY&n;    THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;    LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;    solely responsible for determining the appropriateness of using and&n;    distributing the Program and assumes all risks associated with its&n;    exercise of rights under this Agreement, including but not limited to&n;    the risks and costs of program errors, damage to or loss of data,&n;    programs or equipment, and unavailability or interruption of operations.&n;&n;    DISCLAIMER OF LIABILITY&n;    NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;    DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;    USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;    HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#ifndef MPTCTL_H_INCLUDED
DECL|macro|MPTCTL_H_INCLUDED
mdefine_line|#define MPTCTL_H_INCLUDED
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#include &quot;linux/version.h&quot;
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *&n; */
DECL|macro|MPT_MISCDEV_BASENAME
mdefine_line|#define MPT_MISCDEV_BASENAME            &quot;mptctl&quot;
DECL|macro|MPT_MISCDEV_PATHNAME
mdefine_line|#define MPT_MISCDEV_PATHNAME            &quot;/dev/&quot; MPT_MISCDEV_BASENAME
DECL|macro|MPT_PRODUCT_LENGTH
mdefine_line|#define MPT_PRODUCT_LENGTH              12
multiline_comment|/*&n; *  Generic MPT Control IOCTLs and structures&n; */
DECL|macro|MPT_MAGIC_NUMBER
mdefine_line|#define MPT_MAGIC_NUMBER&t;&squot;m&squot;
DECL|macro|MPTRWPERF
mdefine_line|#define MPTRWPERF&t;&t;_IOWR(MPT_MAGIC_NUMBER,0,struct mpt_raw_r_w)
DECL|macro|MPTFWDOWNLOAD
mdefine_line|#define MPTFWDOWNLOAD&t;&t;_IOWR(MPT_MAGIC_NUMBER,15,struct mpt_fw_xfer)
DECL|macro|MPTCOMMAND
mdefine_line|#define MPTCOMMAND&t;&t;_IOWR(MPT_MAGIC_NUMBER,20,struct mpt_ioctl_command)
macro_line|#if defined(__KERNEL__) &amp;&amp; defined(__sparc__) &amp;&amp; defined(__sparc_v9__)&t;&t;/*{*/
DECL|macro|MPTFWDOWNLOAD32
mdefine_line|#define MPTFWDOWNLOAD32&t;&t;_IOWR(MPT_MAGIC_NUMBER,15,struct mpt_fw_xfer32)
DECL|macro|MPTCOMMAND32
mdefine_line|#define MPTCOMMAND32&t;&t;_IOWR(MPT_MAGIC_NUMBER,20,struct mpt_ioctl_command32)
macro_line|#endif&t;/*}*/
DECL|macro|MPTIOCINFO
mdefine_line|#define MPTIOCINFO&t;&t;_IOWR(MPT_MAGIC_NUMBER,17,struct mpt_ioctl_iocinfo)
DECL|macro|MPTTARGETINFO
mdefine_line|#define MPTTARGETINFO&t;&t;_IOWR(MPT_MAGIC_NUMBER,18,struct mpt_ioctl_targetinfo)
DECL|macro|MPTTEST
mdefine_line|#define MPTTEST&t;&t;&t;_IOWR(MPT_MAGIC_NUMBER,19,struct mpt_ioctl_test)
DECL|macro|MPTEVENTQUERY
mdefine_line|#define MPTEVENTQUERY&t;&t;_IOWR(MPT_MAGIC_NUMBER,21,struct mpt_ioctl_eventquery)
DECL|macro|MPTEVENTENABLE
mdefine_line|#define MPTEVENTENABLE&t;&t;_IOWR(MPT_MAGIC_NUMBER,22,struct mpt_ioctl_eventenable)
DECL|macro|MPTEVENTREPORT
mdefine_line|#define MPTEVENTREPORT&t;&t;_IOWR(MPT_MAGIC_NUMBER,23,struct mpt_ioctl_eventreport)
DECL|macro|MPTHARDRESET
mdefine_line|#define MPTHARDRESET&t;&t;_IOWR(MPT_MAGIC_NUMBER,24,struct mpt_ioctl_diag_reset)
DECL|macro|MPTFWREPLACE
mdefine_line|#define MPTFWREPLACE&t;&t;_IOWR(MPT_MAGIC_NUMBER,25,struct mpt_ioctl_replace_fw)
multiline_comment|/*&n; * SPARC PLATFORM REMARK:&n; * IOCTL data structures that contain pointers&n; * will have different sizes in the driver and applications&n; * (as the app. will not use 8-byte pointers).&n; * Apps should use MPTFWDOWNLOAD and MPTCOMMAND.&n; * The driver will convert data from&n; * mpt_fw_xfer32 (mpt_ioctl_command32) to mpt_fw_xfer (mpt_ioctl_command)&n; * internally.&n; */
DECL|struct|mpt_fw_xfer
r_struct
id|mpt_fw_xfer
(brace
DECL|member|iocnum
r_int
r_int
id|iocnum
suffix:semicolon
multiline_comment|/* IOC unit number */
DECL|member|fwlen
r_int
r_int
id|fwlen
suffix:semicolon
DECL|member|bufp
r_void
op_star
id|bufp
suffix:semicolon
multiline_comment|/* Pointer to firmware buffer */
)brace
suffix:semicolon
macro_line|#if defined(__KERNEL__) &amp;&amp; defined(__sparc__) &amp;&amp; defined(__sparc_v9__)&t;&t;/*{*/
DECL|struct|mpt_fw_xfer32
r_struct
id|mpt_fw_xfer32
(brace
DECL|member|iocnum
r_int
r_int
id|iocnum
suffix:semicolon
DECL|member|fwlen
r_int
r_int
id|fwlen
suffix:semicolon
DECL|member|bufp
id|u32
id|bufp
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/*}*/
multiline_comment|/*&n; *  IOCTL header structure.&n; *  iocnum - must be defined.&n; *  port - must be defined for all IOCTL commands other than MPTIOCINFO&n; *  maxDataSize - ignored on MPTCOMMAND commands&n; *&t;&t;- ignored on MPTFWREPLACE commands&n; *&t;&t;- on query commands, reports the maximum number of bytes to be returned&n; *&t;&t;  to the host driver (count includes the header).&n; *&t;&t;  That is, set to sizeof(struct mpt_ioctl_iocinfo) for fixed sized commands.&n; *&t;&t;  Set to sizeof(struct mpt_ioctl_targetinfo) + datasize for variable&n; *&t;&t;&t;sized commands. (MPTTARGETINFO, MPTEVENTREPORT)&n; */
DECL|struct|_mpt_ioctl_header
r_typedef
r_struct
id|_mpt_ioctl_header
(brace
DECL|member|iocnum
r_int
r_int
id|iocnum
suffix:semicolon
multiline_comment|/* IOC unit number */
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/* IOC port number */
DECL|member|maxDataSize
r_int
id|maxDataSize
suffix:semicolon
multiline_comment|/* Maximum Num. bytes to transfer on read */
DECL|typedef|mpt_ioctl_header
)brace
id|mpt_ioctl_header
suffix:semicolon
multiline_comment|/*&n; * Issue a diagnostic reset&n; */
DECL|struct|mpt_ioctl_diag_reset
r_struct
id|mpt_ioctl_diag_reset
(brace
DECL|member|hdr
id|mpt_ioctl_header
id|hdr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  PCI bus/device/function information structure.&n; */
DECL|struct|mpt_ioctl_pci_info
r_struct
id|mpt_ioctl_pci_info
(brace
r_union
(brace
r_struct
(brace
DECL|member|deviceNumber
r_int
r_int
id|deviceNumber
suffix:colon
l_int|5
suffix:semicolon
DECL|member|functionNumber
r_int
r_int
id|functionNumber
suffix:colon
l_int|3
suffix:semicolon
DECL|member|busNumber
r_int
r_int
id|busNumber
suffix:colon
l_int|24
suffix:semicolon
DECL|member|bits
)brace
id|bits
suffix:semicolon
DECL|member|asUlong
r_int
r_int
id|asUlong
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *  Adapter Information Page&n; *  Read only.&n; *  Data starts at offset 0xC&n; */
DECL|macro|MPT_IOCTL_INTERFACE_FC
mdefine_line|#define MPT_IOCTL_INTERFACE_FC&t;&t;(0x01)
DECL|macro|MPT_IOCTL_INTERFACE_SCSI
mdefine_line|#define MPT_IOCTL_INTERFACE_SCSI&t;(0x00)
DECL|macro|MPT_IOCTL_VERSION_LENGTH
mdefine_line|#define MPT_IOCTL_VERSION_LENGTH&t;(32)
DECL|struct|mpt_ioctl_iocinfo
r_struct
id|mpt_ioctl_iocinfo
(brace
DECL|member|hdr
id|mpt_ioctl_header
id|hdr
suffix:semicolon
DECL|member|adapterType
r_int
id|adapterType
suffix:semicolon
multiline_comment|/* SCSI or FCP */
DECL|member|port
r_int
id|port
suffix:semicolon
multiline_comment|/* port number */
DECL|member|pciId
r_int
id|pciId
suffix:semicolon
multiline_comment|/* PCI Id. */
DECL|member|hwRev
r_int
id|hwRev
suffix:semicolon
multiline_comment|/* hardware revision */
DECL|member|subSystemDevice
r_int
id|subSystemDevice
suffix:semicolon
multiline_comment|/* PCI subsystem Device ID */
DECL|member|subSystemVendor
r_int
id|subSystemVendor
suffix:semicolon
multiline_comment|/* PCI subsystem Vendor ID */
DECL|member|numDevices
r_int
id|numDevices
suffix:semicolon
multiline_comment|/* number of devices */
DECL|member|FWVersion
r_int
id|FWVersion
suffix:semicolon
multiline_comment|/* FW Version (integer) */
DECL|member|BIOSVersion
r_int
id|BIOSVersion
suffix:semicolon
multiline_comment|/* BIOS Version (integer) */
DECL|member|driverVersion
r_char
id|driverVersion
(braket
id|MPT_IOCTL_VERSION_LENGTH
)braket
suffix:semicolon
multiline_comment|/* Driver Version (string) */
DECL|member|busChangeEvent
r_char
id|busChangeEvent
suffix:semicolon
DECL|member|hostId
r_char
id|hostId
suffix:semicolon
DECL|member|rsvd
r_char
id|rsvd
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|pciInfo
r_struct
id|mpt_ioctl_pci_info
id|pciInfo
suffix:semicolon
multiline_comment|/* Added Rev 1 */
)brace
suffix:semicolon
multiline_comment|/*&n; * Device Information Page&n; * Report the number of, and ids of, all targets&n; * on this IOC.  The ids array is a packed structure&n; * of the known targetInfo.&n; * bits 31-24: reserved&n; *      23-16: LUN&n; *      15- 8: Bus Number&n; *       7- 0: Target ID&n; */
DECL|struct|mpt_ioctl_targetinfo
r_struct
id|mpt_ioctl_targetinfo
(brace
DECL|member|hdr
id|mpt_ioctl_header
id|hdr
suffix:semicolon
DECL|member|numDevices
r_int
id|numDevices
suffix:semicolon
multiline_comment|/* Num targets on this ioc */
DECL|member|targetInfo
r_int
id|targetInfo
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Event reporting IOCTL&squot;s.  These IOCTL&squot;s will&n; * use the following defines:&n; */
DECL|struct|mpt_ioctl_eventquery
r_struct
id|mpt_ioctl_eventquery
(brace
DECL|member|hdr
id|mpt_ioctl_header
id|hdr
suffix:semicolon
DECL|member|eventEntries
r_int
r_int
id|eventEntries
suffix:semicolon
DECL|member|reserved
r_int
r_int
id|reserved
suffix:semicolon
DECL|member|eventTypes
r_int
r_int
id|eventTypes
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mpt_ioctl_eventenable
r_struct
id|mpt_ioctl_eventenable
(brace
DECL|member|hdr
id|mpt_ioctl_header
id|hdr
suffix:semicolon
DECL|member|eventTypes
r_int
r_int
id|eventTypes
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifndef __KERNEL__
r_typedef
r_struct
(brace
DECL|member|event
id|uint
id|event
suffix:semicolon
DECL|member|eventContext
id|uint
id|eventContext
suffix:semicolon
DECL|member|data
id|uint
id|data
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|MPT_IOCTL_EVENTS
)brace
id|MPT_IOCTL_EVENTS
suffix:semicolon
macro_line|#endif
DECL|struct|mpt_ioctl_eventreport
r_struct
id|mpt_ioctl_eventreport
(brace
DECL|member|hdr
id|mpt_ioctl_header
id|hdr
suffix:semicolon
DECL|member|eventData
id|MPT_IOCTL_EVENTS
id|eventData
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MPT_MAX_NAME
mdefine_line|#define MPT_MAX_NAME&t;32
DECL|struct|mpt_ioctl_test
r_struct
id|mpt_ioctl_test
(brace
DECL|member|hdr
id|mpt_ioctl_header
id|hdr
suffix:semicolon
DECL|member|name
id|u8
id|name
(braket
id|MPT_MAX_NAME
)braket
suffix:semicolon
DECL|member|chip_type
r_int
id|chip_type
suffix:semicolon
DECL|member|product
id|u8
id|product
(braket
id|MPT_PRODUCT_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Replace the FW image cached in host driver memory&n; * newImageSize - image size in bytes&n; * newImage - first byte of the new image&n; */
DECL|struct|mpt_ioctl_replace_fw
r_typedef
r_struct
id|mpt_ioctl_replace_fw
(brace
DECL|member|hdr
id|mpt_ioctl_header
id|hdr
suffix:semicolon
DECL|member|newImageSize
r_int
id|newImageSize
suffix:semicolon
DECL|member|newImage
id|u8
id|newImage
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|mpt_ioctl_replace_fw_t
)brace
id|mpt_ioctl_replace_fw_t
suffix:semicolon
multiline_comment|/* General MPT Pass through data strucutre&n; *&n; * iocnum&n; * timeout - in seconds, command timeout. If 0, set by driver to&n; *&t;&t;default value.&n; * replyFrameBufPtr - reply location&n; * dataInBufPtr - destination for read&n; * dataOutBufPtr - data source for write&n; * senseDataPtr - sense data location&n; * maxReplyBytes - maximum number of reply bytes to be sent to app.&n; * dataInSize - num bytes for data transfer in (read)&n; * dataOutSize - num bytes for data transfer out (write)&n; * dataSgeOffset - offset in words from the start of the request message&n; *&t;&t;to the first SGL&n; * MF[1];&n; *&n; * Remark:  Some config pages have bi-directional transfer,&n; * both a read and a write. The basic structure allows for&n; * a bidirectional set up. Normal messages will have one or&n; * both of these buffers NULL.&n; */
DECL|struct|mpt_ioctl_command
r_struct
id|mpt_ioctl_command
(brace
DECL|member|hdr
id|mpt_ioctl_header
id|hdr
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
multiline_comment|/* optional (seconds) */
DECL|member|replyFrameBufPtr
r_char
op_star
id|replyFrameBufPtr
suffix:semicolon
DECL|member|dataInBufPtr
r_char
op_star
id|dataInBufPtr
suffix:semicolon
DECL|member|dataOutBufPtr
r_char
op_star
id|dataOutBufPtr
suffix:semicolon
DECL|member|senseDataPtr
r_char
op_star
id|senseDataPtr
suffix:semicolon
DECL|member|maxReplyBytes
r_int
id|maxReplyBytes
suffix:semicolon
DECL|member|dataInSize
r_int
id|dataInSize
suffix:semicolon
DECL|member|dataOutSize
r_int
id|dataOutSize
suffix:semicolon
DECL|member|maxSenseBytes
r_int
id|maxSenseBytes
suffix:semicolon
DECL|member|dataSgeOffset
r_int
id|dataSgeOffset
suffix:semicolon
DECL|member|MF
r_char
id|MF
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * SPARC PLATFORM: See earlier remark.&n; */
macro_line|#if defined(__KERNEL__) &amp;&amp; defined(__sparc__) &amp;&amp; defined(__sparc_v9__)&t;&t;/*{*/
DECL|struct|mpt_ioctl_command32
r_struct
id|mpt_ioctl_command32
(brace
DECL|member|hdr
id|mpt_ioctl_header
id|hdr
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|replyFrameBufPtr
id|u32
id|replyFrameBufPtr
suffix:semicolon
DECL|member|dataInBufPtr
id|u32
id|dataInBufPtr
suffix:semicolon
DECL|member|dataOutBufPtr
id|u32
id|dataOutBufPtr
suffix:semicolon
DECL|member|senseDataPtr
id|u32
id|senseDataPtr
suffix:semicolon
DECL|member|maxReplyBytes
r_int
id|maxReplyBytes
suffix:semicolon
DECL|member|dataInSize
r_int
id|dataInSize
suffix:semicolon
DECL|member|dataOutSize
r_int
id|dataOutSize
suffix:semicolon
DECL|member|maxSenseBytes
r_int
id|maxSenseBytes
suffix:semicolon
DECL|member|dataSgeOffset
r_int
id|dataSgeOffset
suffix:semicolon
DECL|member|MF
r_char
id|MF
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/*}*/
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *&t;HP Specific IOCTL Defines and Structures&n; */
DECL|macro|CPQFCTS_IOC_MAGIC
mdefine_line|#define CPQFCTS_IOC_MAGIC &squot;Z&squot;
DECL|macro|HP_IOC_MAGIC
mdefine_line|#define HP_IOC_MAGIC &squot;Z&squot;
DECL|macro|HP_GETHOSTINFO
mdefine_line|#define HP_GETHOSTINFO&t;&t;_IOR(HP_IOC_MAGIC, 20, hp_host_info_t)
DECL|macro|HP_GETTARGETINFO
mdefine_line|#define HP_GETTARGETINFO&t;_IOR(HP_IOC_MAGIC, 21, hp_target_info_t)
multiline_comment|/* All HP IOCTLs must include this header&n; */
DECL|struct|_hp_header
r_typedef
r_struct
id|_hp_header
(brace
DECL|member|iocnum
r_int
r_int
id|iocnum
suffix:semicolon
DECL|member|host
r_int
r_int
id|host
suffix:semicolon
DECL|member|channel
r_int
r_int
id|channel
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|lun
r_int
r_int
id|lun
suffix:semicolon
DECL|typedef|hp_header_t
)brace
id|hp_header_t
suffix:semicolon
multiline_comment|/*  &n; *  Header:&n; *  iocnum &t;required (input)&n; *  host &t;ignored&t;&n; *  channe&t;ignored&n; *  id&t;&t;ignored&n; *  lun&t;&t;ignored&n; */
DECL|struct|_hp_host_info
r_typedef
r_struct
id|_hp_host_info
(brace
DECL|member|hdr
id|hp_header_t
id|hdr
suffix:semicolon
DECL|member|vendor
id|u16
id|vendor
suffix:semicolon
DECL|member|device
id|u16
id|device
suffix:semicolon
DECL|member|subsystem_vendor
id|u16
id|subsystem_vendor
suffix:semicolon
DECL|member|subsystem_id
id|u16
id|subsystem_id
suffix:semicolon
DECL|member|devfn
id|u8
id|devfn
suffix:semicolon
DECL|member|bus
id|u8
id|bus
suffix:semicolon
DECL|member|host_no
id|ushort
id|host_no
suffix:semicolon
multiline_comment|/* SCSI Host number, if scsi driver not loaded*/
DECL|member|fw_version
id|u8
id|fw_version
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* string */
DECL|member|serial_number
id|u8
id|serial_number
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* string */
DECL|member|ioc_status
id|u32
id|ioc_status
suffix:semicolon
DECL|member|bus_phys_width
id|u32
id|bus_phys_width
suffix:semicolon
DECL|member|base_io_addr
id|u32
id|base_io_addr
suffix:semicolon
DECL|member|rsvd
id|u32
id|rsvd
suffix:semicolon
DECL|member|hard_resets
r_int
r_int
id|hard_resets
suffix:semicolon
multiline_comment|/* driver initiated resets */
DECL|member|soft_resets
r_int
r_int
id|soft_resets
suffix:semicolon
multiline_comment|/* ioc, external resets */
DECL|member|timeouts
r_int
r_int
id|timeouts
suffix:semicolon
multiline_comment|/* num timeouts */
DECL|typedef|hp_host_info_t
)brace
id|hp_host_info_t
suffix:semicolon
multiline_comment|/*  &n; *  Header:&n; *  iocnum &t;required (input)&n; *  host &t;required&t;&n; *  channel&t;required&t;(bus number)&n; *  id&t;&t;required&n; *  lun&t;&t;ignored&n; *&n; *  All error values between 0 and 0xFFFF in size.&n; */
DECL|struct|_hp_target_info
r_typedef
r_struct
id|_hp_target_info
(brace
DECL|member|hdr
id|hp_header_t
id|hdr
suffix:semicolon
DECL|member|parity_errors
id|u32
id|parity_errors
suffix:semicolon
DECL|member|phase_errors
id|u32
id|phase_errors
suffix:semicolon
DECL|member|select_timeouts
id|u32
id|select_timeouts
suffix:semicolon
DECL|member|message_rejects
id|u32
id|message_rejects
suffix:semicolon
DECL|member|negotiated_speed
id|u32
id|negotiated_speed
suffix:semicolon
DECL|member|negotiated_width
id|u8
id|negotiated_width
suffix:semicolon
DECL|member|rsvd
id|u8
id|rsvd
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* 8 byte alignment */
DECL|typedef|hp_target_info_t
)brace
id|hp_target_info_t
suffix:semicolon
DECL|macro|HP_STATUS_OTHER
mdefine_line|#define HP_STATUS_OTHER&t;&t;1
DECL|macro|HP_STATUS_OK
mdefine_line|#define HP_STATUS_OK&t;&t;2
DECL|macro|HP_STATUS_FAILED
mdefine_line|#define HP_STATUS_FAILED&t;3
DECL|macro|HP_BUS_WIDTH_UNK
mdefine_line|#define HP_BUS_WIDTH_UNK&t;1
DECL|macro|HP_BUS_WIDTH_8
mdefine_line|#define HP_BUS_WIDTH_8&t;&t;2
DECL|macro|HP_BUS_WIDTH_16
mdefine_line|#define HP_BUS_WIDTH_16&t;&t;3
DECL|macro|HP_BUS_WIDTH_32
mdefine_line|#define HP_BUS_WIDTH_32&t;&t;4
DECL|macro|HP_DEV_SPEED_ASYNC
mdefine_line|#define HP_DEV_SPEED_ASYNC&t;2
DECL|macro|HP_DEV_SPEED_FAST
mdefine_line|#define HP_DEV_SPEED_FAST&t;3
DECL|macro|HP_DEV_SPEED_ULTRA
mdefine_line|#define HP_DEV_SPEED_ULTRA&t;4
DECL|macro|HP_DEV_SPEED_ULTRA2
mdefine_line|#define HP_DEV_SPEED_ULTRA2&t;5
DECL|macro|HP_DEV_SPEED_ULTRA160
mdefine_line|#define HP_DEV_SPEED_ULTRA160&t;6
DECL|macro|HP_DEV_SPEED_SCSI1
mdefine_line|#define HP_DEV_SPEED_SCSI1&t;7
DECL|macro|HP_DEV_SPEED_ULTRA320
mdefine_line|#define HP_DEV_SPEED_ULTRA320&t;8
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#endif
eof
