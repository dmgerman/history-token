multiline_comment|/*&n; *  linux/drivers/message/fusion/mptbase.h&n; *      High performance SCSI + LAN / Fibre Channel device drivers.&n; *      For use with PCI chip/adapter(s):&n; *          LSIFC9xx/LSI409xx Fibre Channel&n; *      running LSI Logic Fusion MPT (Message Passing Technology) firmware.&n; *&n; *  Credits:&n; *     (see mptbase.c)&n; *&n; *  Copyright (c) 1999-2002 LSI Logic Corporation&n; *  Originally By: Steven J. Ralston&n; *  (mailto:sjralston1@netscape.net)&n; *  (mailto:Pam.Delaney@lsil.com)&n; *&n; *  $Id: mptbase.h,v 1.123 2002/06/20 13:28:16 pdelaney Exp $&n; */
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; version 2 of the License.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    NO WARRANTY&n;    THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;    LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;    solely responsible for determining the appropriateness of using and&n;    distributing the Program and assumes all risks associated with its&n;    exercise of rights under this Agreement, including but not limited to&n;    the risks and costs of program errors, damage to or loss of data,&n;    programs or equipment, and unavailability or interruption of operations.&n;&n;    DISCLAIMER OF LIABILITY&n;    NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;    DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;    USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;    HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#ifndef MPTBASE_H_INCLUDED
DECL|macro|MPTBASE_H_INCLUDED
mdefine_line|#define MPTBASE_H_INCLUDED
multiline_comment|/*{-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#include &quot;linux_compat.h&quot;&t;/* linux-2.2.x (vs. -2.4.x) tweaks */
macro_line|#include &quot;scsi3.h&quot;&t;&t;/* SCSI defines */
macro_line|#include &quot;lsi/mpi_type.h&quot;
macro_line|#include &quot;lsi/mpi.h&quot;&t;&t;/* Fusion MPI(nterface) basic defs */
macro_line|#include &quot;lsi/mpi_ioc.h&quot;&t;/* Fusion MPT IOC(ontroller) defs */
macro_line|#include &quot;lsi/mpi_cnfg.h&quot;&t;/* IOC configuration support */
macro_line|#include &quot;lsi/mpi_init.h&quot;&t;/* SCSI Host (initiator) protocol support */
macro_line|#include &quot;lsi/mpi_lan.h&quot;&t;/* LAN over FC protocol support */
macro_line|#include &quot;lsi/mpi_raid.h&quot;&t;/* Integrated Mirroring support */
macro_line|#include &quot;lsi/mpi_fc.h&quot;&t;&t;/* Fibre Channel (lowlevel) support */
macro_line|#include &quot;lsi/mpi_targ.h&quot;&t;/* SCSI/FCP Target protcol support */
macro_line|#include &quot;lsi/fc_log.h&quot;
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#ifndef MODULEAUTHOR
DECL|macro|MODULEAUTHOR
mdefine_line|#define MODULEAUTHOR&t;&quot;LSI Logic Corporation&quot;
macro_line|#endif
macro_line|#ifndef COPYRIGHT
DECL|macro|COPYRIGHT
mdefine_line|#define COPYRIGHT&t;&quot;Copyright (c) 1999-2002 &quot; MODULEAUTHOR
macro_line|#endif
DECL|macro|MPT_LINUX_VERSION_COMMON
mdefine_line|#define MPT_LINUX_VERSION_COMMON&t;&quot;2.01.06&quot;
DECL|macro|MPT_LINUX_PACKAGE_NAME
mdefine_line|#define MPT_LINUX_PACKAGE_NAME&t;&t;&quot;@(#)mptlinux-2.01.06&quot;
DECL|macro|WHAT_MAGIC_STRING
mdefine_line|#define WHAT_MAGIC_STRING&t;&t;&quot;@&quot; &quot;(&quot; &quot;#&quot; &quot;)&quot;
DECL|macro|show_mptmod_ver
mdefine_line|#define show_mptmod_ver(s,ver)  &bslash;&n;&t;printk(KERN_INFO &quot;%s %s&bslash;n&quot;, s, ver);
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *  Fusion MPT(linux) driver configurable stuff...&n; */
DECL|macro|MPT_MAX_ADAPTERS
mdefine_line|#define MPT_MAX_ADAPTERS&t;&t;16
DECL|macro|MPT_MAX_PROTOCOL_DRIVERS
mdefine_line|#define MPT_MAX_PROTOCOL_DRIVERS&t;16
DECL|macro|MPT_MAX_BUS
mdefine_line|#define MPT_MAX_BUS&t;&t;&t;1
DECL|macro|MPT_MAX_FC_DEVICES
mdefine_line|#define MPT_MAX_FC_DEVICES&t;&t;255
DECL|macro|MPT_MAX_SCSI_DEVICES
mdefine_line|#define MPT_MAX_SCSI_DEVICES&t;&t;16
DECL|macro|MPT_LAST_LUN
mdefine_line|#define MPT_LAST_LUN&t;&t;&t;31
DECL|macro|MPT_SENSE_BUFFER_ALLOC
mdefine_line|#define MPT_SENSE_BUFFER_ALLOC&t;&t;64
multiline_comment|/* allow for 256 max sense alloc, but only 255 max request */
macro_line|#if MPT_SENSE_BUFFER_ALLOC &gt;= 256
DECL|macro|MPT_SENSE_BUFFER_ALLOC
macro_line|#&t;undef MPT_SENSE_BUFFER_ALLOC
DECL|macro|MPT_SENSE_BUFFER_ALLOC
macro_line|#&t;define MPT_SENSE_BUFFER_ALLOC&t;256
DECL|macro|MPT_SENSE_BUFFER_SIZE
macro_line|#&t;define MPT_SENSE_BUFFER_SIZE&t;255
macro_line|#else
DECL|macro|MPT_SENSE_BUFFER_SIZE
macro_line|#&t;define MPT_SENSE_BUFFER_SIZE&t;MPT_SENSE_BUFFER_ALLOC
macro_line|#endif
DECL|macro|MPT_NAME_LENGTH
mdefine_line|#define MPT_NAME_LENGTH&t;&t;&t;32
DECL|macro|MPT_PROCFS_MPTBASEDIR
mdefine_line|#define MPT_PROCFS_MPTBASEDIR&t;&t;&quot;mpt&quot;
multiline_comment|/* chg it to &quot;driver/fusion&quot; ? */
DECL|macro|MPT_PROCFS_SUMMARY_ALL_NODE
mdefine_line|#define MPT_PROCFS_SUMMARY_ALL_NODE&t;&t;MPT_PROCFS_MPTBASEDIR &quot;/summary&quot;
DECL|macro|MPT_PROCFS_SUMMARY_ALL_PATHNAME
mdefine_line|#define MPT_PROCFS_SUMMARY_ALL_PATHNAME&t;&t;&quot;/proc/&quot; MPT_PROCFS_SUMMARY_ALL_NODE
DECL|macro|MPT_FW_REV_MAGIC_ID_STRING
mdefine_line|#define MPT_FW_REV_MAGIC_ID_STRING&t;&t;&quot;FwRev=&quot;
DECL|macro|MPT_MAX_REQ_DEPTH
mdefine_line|#define  MPT_MAX_REQ_DEPTH&t;&t;1023
DECL|macro|MPT_DEFAULT_REQ_DEPTH
mdefine_line|#define  MPT_DEFAULT_REQ_DEPTH&t;&t;256
DECL|macro|MPT_MIN_REQ_DEPTH
mdefine_line|#define  MPT_MIN_REQ_DEPTH&t;&t;128
DECL|macro|MPT_MAX_REPLY_DEPTH
mdefine_line|#define  MPT_MAX_REPLY_DEPTH&t;&t;MPT_MAX_REQ_DEPTH
DECL|macro|MPT_DEFAULT_REPLY_DEPTH
mdefine_line|#define  MPT_DEFAULT_REPLY_DEPTH&t;128
DECL|macro|MPT_MIN_REPLY_DEPTH
mdefine_line|#define  MPT_MIN_REPLY_DEPTH&t;&t;8
DECL|macro|MPT_MAX_REPLIES_PER_ISR
mdefine_line|#define  MPT_MAX_REPLIES_PER_ISR&t;32
DECL|macro|MPT_MAX_FRAME_SIZE
mdefine_line|#define  MPT_MAX_FRAME_SIZE&t;&t;128
DECL|macro|MPT_DEFAULT_FRAME_SIZE
mdefine_line|#define  MPT_DEFAULT_FRAME_SIZE&t;&t;128
DECL|macro|MPT_SG_REQ_128_SCALE
mdefine_line|#define  MPT_SG_REQ_128_SCALE&t;&t;1
DECL|macro|MPT_SG_REQ_96_SCALE
mdefine_line|#define  MPT_SG_REQ_96_SCALE&t;&t;2
DECL|macro|MPT_SG_REQ_64_SCALE
mdefine_line|#define  MPT_SG_REQ_64_SCALE&t;&t;4
DECL|macro|CAN_SLEEP
mdefine_line|#define&t; CAN_SLEEP&t;&t;&t;1
DECL|macro|NO_SLEEP
mdefine_line|#define  NO_SLEEP&t;&t;&t;0
multiline_comment|/* &n; * SCSI transfer rate defines. &n; */
DECL|macro|MPT_ULTRA320
mdefine_line|#define MPT_ULTRA320&t;&t;&t;0x08
DECL|macro|MPT_ULTRA160
mdefine_line|#define MPT_ULTRA160&t;&t;&t;0x09
DECL|macro|MPT_ULTRA2
mdefine_line|#define MPT_ULTRA2&t;&t;&t;0x0A
DECL|macro|MPT_ULTRA
mdefine_line|#define MPT_ULTRA&t;&t;&t;0x0C
DECL|macro|MPT_FAST
mdefine_line|#define MPT_FAST&t;&t;&t;0x19
DECL|macro|MPT_SCSI
mdefine_line|#define MPT_SCSI&t;&t;&t;0x32
DECL|macro|MPT_ASYNC
mdefine_line|#define MPT_ASYNC&t;&t;&t;0xFF
DECL|macro|MPT_NARROW
mdefine_line|#define MPT_NARROW&t;&t;&t;0
DECL|macro|MPT_WIDE
mdefine_line|#define MPT_WIDE&t;&t;&t;1
macro_line|#ifdef __KERNEL__&t;/* { */
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#include &lt;linux/proc_fs.h&gt;
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; * Attempt semi-consistent error &amp; warning msgs across&n; * MPT drivers.  NOTE: Users of these macro defs must&n; * themselves define their own MYNAM.&n; */
DECL|macro|MYIOC_s_INFO_FMT
mdefine_line|#define MYIOC_s_INFO_FMT&t;&t;KERN_INFO MYNAM &quot;: %s: &quot;
DECL|macro|MYIOC_s_NOTE_FMT
mdefine_line|#define MYIOC_s_NOTE_FMT&t;&t;KERN_NOTICE MYNAM &quot;: %s: &quot;
DECL|macro|MYIOC_s_WARN_FMT
mdefine_line|#define MYIOC_s_WARN_FMT&t;&t;KERN_WARNING MYNAM &quot;: %s: WARNING - &quot;
DECL|macro|MYIOC_s_ERR_FMT
mdefine_line|#define MYIOC_s_ERR_FMT&t;&t;&t;KERN_ERR MYNAM &quot;: %s: ERROR - &quot;
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *  MPT protocol driver defs...&n; */
r_typedef
r_enum
(brace
DECL|enumerator|MPTBASE_DRIVER
id|MPTBASE_DRIVER
comma
multiline_comment|/* MPT base class */
DECL|enumerator|MPTCTL_DRIVER
id|MPTCTL_DRIVER
comma
multiline_comment|/* MPT ioctl class */
DECL|enumerator|MPTSCSIH_DRIVER
id|MPTSCSIH_DRIVER
comma
multiline_comment|/* MPT SCSI host (initiator) class */
DECL|enumerator|MPTLAN_DRIVER
id|MPTLAN_DRIVER
comma
multiline_comment|/* MPT LAN class */
DECL|enumerator|MPTSTM_DRIVER
id|MPTSTM_DRIVER
comma
multiline_comment|/* MPT SCSI target mode class */
DECL|enumerator|MPTDMP_DRIVER
id|MPTDMP_DRIVER
comma
multiline_comment|/* MPT Dynamic Multi-pathing class */
DECL|enumerator|MPTUNKNOWN_DRIVER
id|MPTUNKNOWN_DRIVER
DECL|typedef|MPT_DRIVER_CLASS
)brace
id|MPT_DRIVER_CLASS
suffix:semicolon
multiline_comment|/*&n; *  MPT adapter / port / bus / device info structures...&n; */
DECL|union|_MPT_FRAME_TRACKER
r_typedef
r_union
id|_MPT_FRAME_TRACKER
(brace
r_struct
(brace
DECL|member|forw
r_struct
id|_MPT_FRAME_HDR
op_star
id|forw
suffix:semicolon
DECL|member|back
r_struct
id|_MPT_FRAME_HDR
op_star
id|back
suffix:semicolon
DECL|member|arg1
id|u32
id|arg1
suffix:semicolon
DECL|member|pad
id|u32
id|pad
suffix:semicolon
DECL|member|argp1
r_void
op_star
id|argp1
suffix:semicolon
macro_line|#ifndef MPT_SCSI_USE_NEW_EH
DECL|member|argp2
r_void
op_star
id|argp2
suffix:semicolon
macro_line|#endif
DECL|member|linkage
)brace
id|linkage
suffix:semicolon
multiline_comment|/*&n;&t; * NOTE: When request frames are free, on the linkage structure&n;&t; * contets are valid.  All other values are invalid.&n;&t; * In particular, do NOT reply on offset [2]&n;&t; * (in words) being the * message context.&n;&t; * The message context must be reset (computed via base address&n;&t; * + an offset) prior to issuing any command.&n;&t; *&n;&t; * NOTE2: On non-32-bit systems, where pointers are LARGE,&n;&t; * using the linkage pointers destroys our sacred MsgContext&n;&t; * field contents.  But we don&squot;t care anymore because these&n;&t; * are now reset in mpt_put_msg_frame() just prior to sending&n;&t; * a request off to the IOC.&n;&t; */
r_struct
(brace
DECL|member|__hdr
id|u32
id|__hdr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The following _MUST_ match the location of the&n;&t;&t; * MsgContext field in the MPT message headers.&n;&t;&t; */
r_union
(brace
DECL|member|MsgContext
id|u32
id|MsgContext
suffix:semicolon
r_struct
(brace
DECL|member|req_idx
id|u16
id|req_idx
suffix:semicolon
multiline_comment|/* Request index */
DECL|member|cb_idx
id|u8
id|cb_idx
suffix:semicolon
multiline_comment|/* callback function index */
DECL|member|rsvd
id|u8
id|rsvd
suffix:semicolon
DECL|member|fld
)brace
id|fld
suffix:semicolon
DECL|member|msgctxu
)brace
id|msgctxu
suffix:semicolon
DECL|member|hwhdr
)brace
id|hwhdr
suffix:semicolon
multiline_comment|/*&n;&t; * Remark: 32 bit identifier:&n;&t; *  31-24: reserved&n;&t; *  23-16: call back index&n;&t; *  15-0 : request index&n;&t; */
DECL|typedef|MPT_FRAME_TRACKER
)brace
id|MPT_FRAME_TRACKER
suffix:semicolon
multiline_comment|/*&n; *  We might want to view/access a frame as:&n; *    1) generic request header&n; *    2) SCSIIORequest&n; *    3) SCSIIOReply&n; *    4) MPIDefaultReply&n; *    5) frame tracker&n; */
DECL|struct|_MPT_FRAME_HDR
r_typedef
r_struct
id|_MPT_FRAME_HDR
(brace
r_union
(brace
DECL|member|hdr
id|MPIHeader_t
id|hdr
suffix:semicolon
DECL|member|scsireq
id|SCSIIORequest_t
id|scsireq
suffix:semicolon
DECL|member|sreply
id|SCSIIOReply_t
id|sreply
suffix:semicolon
DECL|member|reply
id|MPIDefaultReply_t
id|reply
suffix:semicolon
DECL|member|frame
id|MPT_FRAME_TRACKER
id|frame
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|typedef|MPT_FRAME_HDR
)brace
id|MPT_FRAME_HDR
suffix:semicolon
DECL|macro|MPT_REQ_MSGFLAGS_DROPME
mdefine_line|#define MPT_REQ_MSGFLAGS_DROPME&t;&t;0x80
multiline_comment|/* Used for tracking the free request frames&n; * and free reply frames.&n; */
DECL|struct|_MPT_Q_TRACKER
r_typedef
r_struct
id|_MPT_Q_TRACKER
(brace
DECL|member|head
id|MPT_FRAME_HDR
op_star
id|head
suffix:semicolon
DECL|member|tail
id|MPT_FRAME_HDR
op_star
id|tail
suffix:semicolon
DECL|typedef|MPT_Q_TRACKER
)brace
id|MPT_Q_TRACKER
suffix:semicolon
DECL|struct|_MPT_SGL_HDR
r_typedef
r_struct
id|_MPT_SGL_HDR
(brace
DECL|member|sge
id|SGESimple32_t
id|sge
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|MPT_SGL_HDR
)brace
id|MPT_SGL_HDR
suffix:semicolon
DECL|struct|_MPT_SGL64_HDR
r_typedef
r_struct
id|_MPT_SGL64_HDR
(brace
DECL|member|sge
id|SGESimple64_t
id|sge
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|MPT_SGL64_HDR
)brace
id|MPT_SGL64_HDR
suffix:semicolon
DECL|struct|_Q_ITEM
r_typedef
r_struct
id|_Q_ITEM
(brace
DECL|member|forw
r_struct
id|_Q_ITEM
op_star
id|forw
suffix:semicolon
DECL|member|back
r_struct
id|_Q_ITEM
op_star
id|back
suffix:semicolon
DECL|typedef|Q_ITEM
)brace
id|Q_ITEM
suffix:semicolon
DECL|struct|_Q_TRACKER
r_typedef
r_struct
id|_Q_TRACKER
(brace
DECL|member|head
r_struct
id|_Q_ITEM
op_star
id|head
suffix:semicolon
DECL|member|tail
r_struct
id|_Q_ITEM
op_star
id|tail
suffix:semicolon
DECL|typedef|Q_TRACKER
)brace
id|Q_TRACKER
suffix:semicolon
DECL|struct|_MPT_DONE_Q
r_typedef
r_struct
id|_MPT_DONE_Q
(brace
DECL|member|forw
r_struct
id|_MPT_DONE_Q
op_star
id|forw
suffix:semicolon
DECL|member|back
r_struct
id|_MPT_DONE_Q
op_star
id|back
suffix:semicolon
DECL|member|argp
r_void
op_star
id|argp
suffix:semicolon
DECL|typedef|MPT_DONE_Q
)brace
id|MPT_DONE_Q
suffix:semicolon
DECL|struct|_DONE_Q_TRACKER
r_typedef
r_struct
id|_DONE_Q_TRACKER
(brace
DECL|member|head
id|MPT_DONE_Q
op_star
id|head
suffix:semicolon
DECL|member|tail
id|MPT_DONE_Q
op_star
id|tail
suffix:semicolon
DECL|typedef|DONE_Q_TRACKER
)brace
id|DONE_Q_TRACKER
suffix:semicolon
multiline_comment|/*&n; *  Chip-specific stuff... FC929 delineates break between&n; *  FC and Parallel SCSI parts. Do NOT re-order.&n; */
r_typedef
r_enum
(brace
DECL|enumerator|FC919X
id|FC919X
op_assign
l_int|0x0819
comma
DECL|enumerator|FC929X
id|FC929X
op_assign
l_int|0x0829
comma
DECL|enumerator|FC909
id|FC909
op_assign
l_int|0x0909
comma
DECL|enumerator|FC919
id|FC919
op_assign
l_int|0x0919
comma
DECL|enumerator|FC929
id|FC929
op_assign
l_int|0x0929
comma
DECL|enumerator|C1030
id|C1030
op_assign
l_int|0x1030
comma
DECL|enumerator|FCUNK
id|FCUNK
op_assign
l_int|0xFBAD
DECL|typedef|CHIP_TYPE
)brace
id|CHIP_TYPE
suffix:semicolon
multiline_comment|/*&n; *  System interface register set&n; */
DECL|struct|_SYSIF_REGS
r_typedef
r_struct
id|_SYSIF_REGS
(brace
DECL|member|Doorbell
id|u32
id|Doorbell
suffix:semicolon
multiline_comment|/* 00     System&lt;-&gt;IOC Doorbell reg  */
DECL|member|WriteSequence
id|u32
id|WriteSequence
suffix:semicolon
multiline_comment|/* 04     Write Sequence register    */
DECL|member|Diagnostic
id|u32
id|Diagnostic
suffix:semicolon
multiline_comment|/* 08     Diagnostic register        */
DECL|member|TestBase
id|u32
id|TestBase
suffix:semicolon
multiline_comment|/* 0C     Test Base Address          */
DECL|member|DiagRwData
id|u32
id|DiagRwData
suffix:semicolon
multiline_comment|/* 10     Read Write Data (fw download)   */
DECL|member|DiagRwAddress
id|u32
id|DiagRwAddress
suffix:semicolon
multiline_comment|/* 14     Read Write Address (fw download)*/
DECL|member|Reserved1
id|u32
id|Reserved1
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* 18-2F  reserved for future use    */
DECL|member|IntStatus
id|u32
id|IntStatus
suffix:semicolon
multiline_comment|/* 30     Interrupt Status           */
DECL|member|IntMask
id|u32
id|IntMask
suffix:semicolon
multiline_comment|/* 34     Interrupt Mask             */
DECL|member|Reserved2
id|u32
id|Reserved2
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 38-3F  reserved for future use    */
DECL|member|RequestFifo
id|u32
id|RequestFifo
suffix:semicolon
multiline_comment|/* 40     Request Post/Free FIFO     */
DECL|member|ReplyFifo
id|u32
id|ReplyFifo
suffix:semicolon
multiline_comment|/* 44     Reply   Post/Free FIFO     */
DECL|member|Reserved3
id|u32
id|Reserved3
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 48-4F  reserved for future use    */
DECL|member|HostIndex
id|u32
id|HostIndex
suffix:semicolon
multiline_comment|/* 50     Host Index register        */
DECL|member|Reserved4
id|u32
id|Reserved4
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* 54-8F                             */
DECL|member|Fubar
id|u32
id|Fubar
suffix:semicolon
multiline_comment|/* 90     For Fubar usage            */
DECL|member|Reserved5
id|u32
id|Reserved5
(braket
l_int|27
)braket
suffix:semicolon
multiline_comment|/* 94-FF                             */
DECL|typedef|SYSIF_REGS
)brace
id|SYSIF_REGS
suffix:semicolon
multiline_comment|/*&n; * NOTE: Use MPI_{DOORBELL,WRITESEQ,DIAG}_xxx defs in lsi/mpi.h&n; * in conjunction with SYSIF_REGS accesses!&n; */
multiline_comment|/*&n; *&t;Dynamic Multi-Pathing specific stuff...&n; */
DECL|macro|DMP_MAX_PATHS
mdefine_line|#define DMP_MAX_PATHS&t;8
DECL|struct|_PathInfo
r_typedef
r_struct
id|_PathInfo
(brace
DECL|member|ioc
id|u8
id|ioc
suffix:semicolon
DECL|member|target
id|u8
id|target
suffix:semicolon
DECL|member|pad
id|u8
id|pad
suffix:semicolon
DECL|member|pflags
id|u8
id|pflags
suffix:semicolon
DECL|typedef|PathInfo
)brace
id|PathInfo
suffix:semicolon
DECL|macro|PATHINFO_FLAGS_OWNED
mdefine_line|#define PATHINFO_FLAGS_OWNED&t;&t;0x01
DECL|macro|PATHINFO_FLAGS_EXISTS
mdefine_line|#define PATHINFO_FLAGS_EXISTS&t;&t;0x02
DECL|macro|PATHINFO_FLAGS_AVAILABLE
mdefine_line|#define PATHINFO_FLAGS_AVAILABLE&t;0x04
DECL|macro|PATHINFO_FLAGS_SECONDARY
mdefine_line|#define PATHINFO_FLAGS_SECONDARY&t;0x08
DECL|macro|PFLAGS_EXISTS_AND_AVAIL
mdefine_line|#define PFLAGS_EXISTS_AND_AVAIL&t;&t;(PATHINFO_FLAGS_EXISTS|PATHINFO_FLAGS_AVAILABLE)
DECL|macro|PFLAGS_AVAIL_AND_OWNED
mdefine_line|#define PFLAGS_AVAIL_AND_OWNED&t;&t;(PATHINFO_FLAGS_AVAILABLE|PATHINFO_FLAGS_OWNED)
DECL|struct|_ScsiCmndTracker
r_typedef
r_struct
id|_ScsiCmndTracker
(brace
DECL|member|head
r_void
op_star
id|head
suffix:semicolon
DECL|member|tail
r_void
op_star
id|tail
suffix:semicolon
DECL|typedef|ScsiCmndTracker
)brace
id|ScsiCmndTracker
suffix:semicolon
multiline_comment|/*&n; *&t;VirtDevice - FC LUN device or SCSI target device&n; *&t;(used to be FCSCSI_TARGET)&n; */
DECL|struct|_VirtDevice
r_typedef
r_struct
id|_VirtDevice
(brace
DECL|member|forw
r_struct
id|_VirtDevice
op_star
id|forw
suffix:semicolon
DECL|member|back
r_struct
id|_VirtDevice
op_star
id|back
suffix:semicolon
DECL|member|VdevLock
id|rwlock_t
id|VdevLock
suffix:semicolon
DECL|member|ref_cnt
r_int
id|ref_cnt
suffix:semicolon
DECL|member|tflags
id|u8
id|tflags
suffix:semicolon
DECL|member|ioc_id
id|u8
id|ioc_id
suffix:semicolon
DECL|member|target_id
id|u8
id|target_id
suffix:semicolon
DECL|member|bus_id
id|u8
id|bus_id
suffix:semicolon
DECL|member|minSyncFactor
id|u8
id|minSyncFactor
suffix:semicolon
multiline_comment|/* 0xFF is async */
DECL|member|maxOffset
id|u8
id|maxOffset
suffix:semicolon
multiline_comment|/* 0 if async */
DECL|member|maxWidth
id|u8
id|maxWidth
suffix:semicolon
multiline_comment|/* 0 if narrow, 1 if wide*/
DECL|member|negoFlags
id|u8
id|negoFlags
suffix:semicolon
multiline_comment|/* bit field, 0 if WDTR/SDTR/QAS allowed */
DECL|member|raidVolume
id|u8
id|raidVolume
suffix:semicolon
multiline_comment|/* set, if RAID Volume */
DECL|member|rsvd
id|u8
id|rsvd
suffix:semicolon
DECL|member|rsvd1raid
id|u16
id|rsvd1raid
suffix:semicolon
DECL|member|npaths
r_int
id|npaths
suffix:semicolon
DECL|member|fc_phys_lun
id|u16
id|fc_phys_lun
suffix:semicolon
DECL|member|fc_xlat_lun
id|u16
id|fc_xlat_lun
suffix:semicolon
DECL|member|stall_detected
r_int
id|stall_detected
suffix:semicolon
DECL|member|path
id|PathInfo
id|path
(braket
id|DMP_MAX_PATHS
)braket
suffix:semicolon
DECL|member|stall_timer
r_struct
id|timer_list
id|stall_timer
suffix:semicolon
DECL|member|retry_timer
r_struct
id|timer_list
id|retry_timer
suffix:semicolon
DECL|member|gone_timer
r_struct
id|timer_list
id|gone_timer
suffix:semicolon
DECL|member|WaitQ
id|ScsiCmndTracker
id|WaitQ
suffix:semicolon
DECL|member|SentQ
id|ScsiCmndTracker
id|SentQ
suffix:semicolon
DECL|member|DoneQ
id|ScsiCmndTracker
id|DoneQ
suffix:semicolon
singleline_comment|//--- LUN split here?
DECL|member|sense
id|u8
id|sense
(braket
id|SCSI_STD_SENSE_BYTES
)braket
suffix:semicolon
multiline_comment|/* 18 */
DECL|member|rsvd2
id|u8
id|rsvd2
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* alignment */
DECL|member|luns
id|u32
id|luns
suffix:semicolon
multiline_comment|/* Max LUNs is 32 */
DECL|member|inq_data
id|u8
id|inq_data
(braket
id|SCSI_STD_INQUIRY_BYTES
)braket
suffix:semicolon
multiline_comment|/* 36 */
DECL|member|pad0
id|u8
id|pad0
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|inq00_data
id|u8
id|inq00_data
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|pad1
id|u8
id|pad1
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* IEEE Registered Extended Identifier&n;&t;&t;   obtained via INQUIRY VPD page 0x83 */
multiline_comment|/* NOTE: Do not separate uniq_prepad and uniq_data&n;&t;&t;   as they are treateed as a single entity in the code */
DECL|member|uniq_prepad
id|u8
id|uniq_prepad
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|uniq_data
id|u8
id|uniq_data
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|pad2
id|u8
id|pad2
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|inqC3_data
id|u8
id|inqC3_data
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|pad3
id|u8
id|pad3
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|inqC9_data
id|u8
id|inqC9_data
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|pad4
id|u8
id|pad4
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|dev_vol_name
id|u8
id|dev_vol_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|typedef|VirtDevice
)brace
id|VirtDevice
suffix:semicolon
multiline_comment|/*&n; *  Fibre Channel (SCSI) target device and associated defines...&n; */
DECL|macro|MPT_TARGET_DEFAULT_DV_STATUS
mdefine_line|#define MPT_TARGET_DEFAULT_DV_STATUS&t;0
DECL|macro|MPT_TARGET_FLAGS_VALID_NEGO
mdefine_line|#define MPT_TARGET_FLAGS_VALID_NEGO&t;0x01
DECL|macro|MPT_TARGET_FLAGS_VALID_INQUIRY
mdefine_line|#define MPT_TARGET_FLAGS_VALID_INQUIRY&t;0x02
DECL|macro|MPT_TARGET_FLAGS_VALID_SENSE
mdefine_line|#define MPT_TARGET_FLAGS_VALID_SENSE&t;0x04
DECL|macro|MPT_TARGET_FLAGS_Q_YES
mdefine_line|#define MPT_TARGET_FLAGS_Q_YES&t;&t;0x08
DECL|macro|MPT_TARGET_NO_NEGO_WIDE
mdefine_line|#define MPT_TARGET_NO_NEGO_WIDE&t;&t;0x01
DECL|macro|MPT_TARGET_NO_NEGO_SYNC
mdefine_line|#define MPT_TARGET_NO_NEGO_SYNC&t;&t;0x02
DECL|macro|MPT_TARGET_NO_NEGO_QAS
mdefine_line|#define MPT_TARGET_NO_NEGO_QAS&t;&t;0x04
DECL|struct|_VirtDevTracker
r_typedef
r_struct
id|_VirtDevTracker
(brace
DECL|member|head
r_struct
id|_VirtDevice
op_star
id|head
suffix:semicolon
DECL|member|tail
r_struct
id|_VirtDevice
op_star
id|tail
suffix:semicolon
DECL|member|VlistLock
id|rwlock_t
id|VlistLock
suffix:semicolon
DECL|member|pad
r_int
id|pad
suffix:semicolon
DECL|typedef|VirtDevTracker
)brace
id|VirtDevTracker
suffix:semicolon
multiline_comment|/*&n; *&t;/proc/mpt interface&n; */
r_typedef
r_struct
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|mode
id|mode_t
id|mode
suffix:semicolon
DECL|member|pad
r_int
id|pad
suffix:semicolon
DECL|member|read_proc
id|read_proc_t
op_star
id|read_proc
suffix:semicolon
DECL|member|write_proc
id|write_proc_t
op_star
id|write_proc
suffix:semicolon
DECL|typedef|mpt_proc_entry_t
)brace
id|mpt_proc_entry_t
suffix:semicolon
DECL|macro|MPT_PROC_READ_RETURN
mdefine_line|#define MPT_PROC_READ_RETURN(buf,start,offset,request,eof,len) &bslash;&n;do { &bslash;&n;&t;len -= offset;&t;&t;&t;&bslash;&n;&t;if (len &lt; request) {&t;&t;&bslash;&n;&t;&t;*eof = 1;&t;&t;&bslash;&n;&t;&t;if (len &lt;= 0)&t;&t;&bslash;&n;&t;&t;&t;return 0;&t;&bslash;&n;&t;} else&t;&t;&t;&t;&bslash;&n;&t;&t;len = request;&t;&t;&bslash;&n;&t;*start = buf + offset;&t;&t;&bslash;&n;&t;return len;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/*&n; *&t;IOCTL structure and associated defines&n; */
DECL|macro|MPT_IOCTL_STATUS_DID_IOCRESET
mdefine_line|#define MPT_IOCTL_STATUS_DID_IOCRESET&t;0x01&t;/* IOC Reset occurred on the current*/
DECL|macro|MPT_IOCTL_STATUS_RF_VALID
mdefine_line|#define MPT_IOCTL_STATUS_RF_VALID&t;0x02&t;/* The Reply Frame is VALID */
DECL|macro|MPT_IOCTL_STATUS_TIMER_ACTIVE
mdefine_line|#define MPT_IOCTL_STATUS_TIMER_ACTIVE&t;0x04&t;/* The timer is running */
DECL|macro|MPT_IOCTL_STATUS_SENSE_VALID
mdefine_line|#define MPT_IOCTL_STATUS_SENSE_VALID&t;0x08&t;/* Sense data is valid */
DECL|macro|MPT_IOCTL_STATUS_COMMAND_GOOD
mdefine_line|#define MPT_IOCTL_STATUS_COMMAND_GOOD&t;0x10&t;/* Command Status GOOD */
DECL|macro|MPT_IOCTL_STATUS_TMTIMER_ACTIVE
mdefine_line|#define MPT_IOCTL_STATUS_TMTIMER_ACTIVE&t;0x20&t;/* The TM timer is running */
DECL|macro|MPT_IOCTL_STATUS_TM_FAILED
mdefine_line|#define MPT_IOCTL_STATUS_TM_FAILED&t;0x40&t;/* User TM request failed */
DECL|macro|MPTCTL_RESET_OK
mdefine_line|#define MPTCTL_RESET_OK&t;&t;&t;0x01&t;/* Issue Bus Reset */
DECL|struct|_MPT_IOCTL
r_typedef
r_struct
id|_MPT_IOCTL
(brace
DECL|member|ioc
r_struct
id|_MPT_ADAPTER
op_star
id|ioc
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* timer function for this adapter */
DECL|member|ReplyFrame
id|u8
id|ReplyFrame
(braket
id|MPT_DEFAULT_FRAME_SIZE
)braket
suffix:semicolon
multiline_comment|/* reply frame data */
DECL|member|sense
id|u8
id|sense
(braket
id|MPT_SENSE_BUFFER_ALLOC
)braket
suffix:semicolon
DECL|member|wait_done
r_int
id|wait_done
suffix:semicolon
multiline_comment|/* wake-up value for this ioc */
DECL|member|rsvd
id|u8
id|rsvd
suffix:semicolon
DECL|member|status
id|u8
id|status
suffix:semicolon
multiline_comment|/* current command status */
DECL|member|reset
id|u8
id|reset
suffix:semicolon
multiline_comment|/* 1 if bus reset allowed */
DECL|member|target
id|u8
id|target
suffix:semicolon
multiline_comment|/* target for reset */
DECL|member|tmPtr
r_void
op_star
id|tmPtr
suffix:semicolon
DECL|member|TMtimer
r_struct
id|timer_list
id|TMtimer
suffix:semicolon
multiline_comment|/* timer function for this adapter */
DECL|typedef|MPT_IOCTL
)brace
id|MPT_IOCTL
suffix:semicolon
multiline_comment|/*&n; *  Event Structure and define&n; */
DECL|macro|MPTCTL_EVENT_LOG_SIZE
mdefine_line|#define MPTCTL_EVENT_LOG_SIZE&t;&t;(0x0000000A)
DECL|struct|_mpt_ioctl_events
r_typedef
r_struct
id|_mpt_ioctl_events
(brace
DECL|member|event
id|u32
id|event
suffix:semicolon
multiline_comment|/* Specified by define above */
DECL|member|eventContext
id|u32
id|eventContext
suffix:semicolon
multiline_comment|/* Index or counter */
DECL|member|data
r_int
id|data
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* First 8 bytes of Event Data */
DECL|typedef|MPT_IOCTL_EVENTS
)brace
id|MPT_IOCTL_EVENTS
suffix:semicolon
multiline_comment|/*&n; * CONFIGPARM status  defines&n; */
DECL|macro|MPT_CONFIG_GOOD
mdefine_line|#define MPT_CONFIG_GOOD&t;&t;MPI_IOCSTATUS_SUCCESS
DECL|macro|MPT_CONFIG_ERROR
mdefine_line|#define MPT_CONFIG_ERROR&t;0x002F
multiline_comment|/*&n; *&t;Substructure to store SCSI specific configuration page data&n; */
multiline_comment|/* dvStatus defines: */
DECL|macro|MPT_SCSICFG_NEGOTIATE
mdefine_line|#define MPT_SCSICFG_NEGOTIATE&t;&t;0x01&t;/* Negotiate on next IO */
DECL|macro|MPT_SCSICFG_NEED_DV
mdefine_line|#define MPT_SCSICFG_NEED_DV&t;&t;0x02&t;/* Schedule DV */
DECL|macro|MPT_SCSICFG_DV_PENDING
mdefine_line|#define MPT_SCSICFG_DV_PENDING&t;&t;0x04&t;/* DV on this physical id pending */
DECL|macro|MPT_SCSICFG_DV_DONE
mdefine_line|#define MPT_SCSICFG_DV_DONE&t;&t;0x08&t;/* DV on this physical id complete */
DECL|macro|MPT_SCSICFG_BLK_NEGO
mdefine_line|#define MPT_SCSICFG_BLK_NEGO&t;&t;0x10&t;/* WriteSDP1 with WDTR and SDTR disabled */
multiline_comment|/* Args passed to writeSDP1: */
DECL|macro|MPT_SCSICFG_USE_NVRAM
mdefine_line|#define MPT_SCSICFG_USE_NVRAM&t;&t;0x01&t;/* WriteSDP1 using NVRAM */
DECL|macro|MPT_SCSICFG_ALL_IDS
mdefine_line|#define MPT_SCSICFG_ALL_IDS&t;&t;0x02&t;/* WriteSDP1 to all IDS */
multiline_comment|/* #define MPT_SCSICFG_BLK_NEGO&t;&t;0x10&t;   WriteSDP1 with WDTR and SDTR disabled */
DECL|struct|_ScsiCfgData
r_typedef
r_struct
id|_ScsiCfgData
(brace
DECL|member|nvram
r_int
op_star
id|nvram
suffix:semicolon
multiline_comment|/* table of device NVRAM values */
DECL|member|pIocPg3
id|IOCPage3_t
op_star
id|pIocPg3
suffix:semicolon
multiline_comment|/* table of physical disks */
DECL|member|dvStatus
id|u8
id|dvStatus
(braket
id|MPT_MAX_SCSI_DEVICES
)braket
suffix:semicolon
DECL|member|isRaid
r_int
id|isRaid
suffix:semicolon
multiline_comment|/* bit field, 1 if RAID */
DECL|member|minSyncFactor
id|u8
id|minSyncFactor
suffix:semicolon
multiline_comment|/* 0xFF if async */
DECL|member|maxSyncOffset
id|u8
id|maxSyncOffset
suffix:semicolon
multiline_comment|/* 0 if async */
DECL|member|maxBusWidth
id|u8
id|maxBusWidth
suffix:semicolon
multiline_comment|/* 0 if narrow, 1 if wide */
DECL|member|busType
id|u8
id|busType
suffix:semicolon
multiline_comment|/* SE, LVD, HD */
DECL|member|sdp1version
id|u8
id|sdp1version
suffix:semicolon
multiline_comment|/* SDP1 version */
DECL|member|sdp1length
id|u8
id|sdp1length
suffix:semicolon
multiline_comment|/* SDP1 length  */
DECL|member|sdp0version
id|u8
id|sdp0version
suffix:semicolon
multiline_comment|/* SDP0 version */
DECL|member|sdp0length
id|u8
id|sdp0length
suffix:semicolon
multiline_comment|/* SDP0 length  */
DECL|member|dvScheduled
id|u8
id|dvScheduled
suffix:semicolon
multiline_comment|/* 1 if scheduled */
DECL|member|forceDv
id|u8
id|forceDv
suffix:semicolon
multiline_comment|/* 1 to force DV scheduling */
DECL|member|noQas
id|u8
id|noQas
suffix:semicolon
multiline_comment|/* Disable QAS for this adapter */
DECL|member|rsvd
id|u8
id|rsvd
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|ScsiCfgData
)brace
id|ScsiCfgData
suffix:semicolon
DECL|struct|_fw_image
r_typedef
r_struct
id|_fw_image
(brace
DECL|member|fw
r_char
op_star
id|fw
suffix:semicolon
DECL|member|fw_dma
id|dma_addr_t
id|fw_dma
suffix:semicolon
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|rsvd
id|u32
id|rsvd
suffix:semicolon
DECL|typedef|fw_image_t
)brace
id|fw_image_t
suffix:semicolon
multiline_comment|/*&n; *  Adapter Structure - pci_dev specific. Maximum: MPT_MAX_ADAPTERS&n; */
DECL|struct|_MPT_ADAPTER
r_typedef
r_struct
id|_MPT_ADAPTER
(brace
DECL|member|forw
r_struct
id|_MPT_ADAPTER
op_star
id|forw
suffix:semicolon
DECL|member|back
r_struct
id|_MPT_ADAPTER
op_star
id|back
suffix:semicolon
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* Unique adapter id N {0,1,2,...} */
DECL|member|pci_irq
r_int
id|pci_irq
suffix:semicolon
multiline_comment|/* This irq           */
DECL|member|name
r_char
id|name
(braket
id|MPT_NAME_LENGTH
)braket
suffix:semicolon
multiline_comment|/* &quot;iocN&quot;             */
DECL|member|prod_name
r_char
op_star
id|prod_name
suffix:semicolon
multiline_comment|/* &quot;LSIFC9x9&quot;         */
DECL|member|chip
r_volatile
id|SYSIF_REGS
op_star
id|chip
suffix:semicolon
multiline_comment|/* == c8817000 (mmap) */
DECL|member|pio_chip
r_volatile
id|SYSIF_REGS
op_star
id|pio_chip
suffix:semicolon
multiline_comment|/* Programmed IO (downloadboot) */
DECL|member|mem_phys
id|u32
id|mem_phys
suffix:semicolon
multiline_comment|/* == f4020000 (mmap) */
DECL|member|pio_mem_phys
id|u32
id|pio_mem_phys
suffix:semicolon
multiline_comment|/* Programmed IO (downloadboot) */
DECL|member|mem_size
r_int
id|mem_size
suffix:semicolon
multiline_comment|/* mmap memory size */
DECL|member|alloc_total
r_int
id|alloc_total
suffix:semicolon
DECL|member|last_state
id|u32
id|last_state
suffix:semicolon
DECL|member|active
r_int
id|active
suffix:semicolon
DECL|member|reply_alloc
id|u8
op_star
id|reply_alloc
suffix:semicolon
multiline_comment|/* Reply frames alloc ptr */
DECL|member|reply_alloc_dma
id|dma_addr_t
id|reply_alloc_dma
suffix:semicolon
DECL|member|reply_frames
id|MPT_FRAME_HDR
op_star
id|reply_frames
suffix:semicolon
multiline_comment|/* Reply msg frames - rounded up! */
DECL|member|reply_frames_dma
id|dma_addr_t
id|reply_frames_dma
suffix:semicolon
DECL|member|reply_frames_low_dma
id|u32
id|reply_frames_low_dma
suffix:semicolon
DECL|member|reply_depth
r_int
id|reply_depth
suffix:semicolon
multiline_comment|/* Num Allocated reply frames */
DECL|member|reply_sz
r_int
id|reply_sz
suffix:semicolon
multiline_comment|/* Reply frame size */
DECL|member|chip_type
id|CHIP_TYPE
id|chip_type
suffix:semicolon
multiline_comment|/* We (host driver) get to manage our own RequestQueue! */
DECL|member|req_alloc
id|u8
op_star
id|req_alloc
suffix:semicolon
multiline_comment|/* Request frames alloc ptr */
DECL|member|req_alloc_dma
id|dma_addr_t
id|req_alloc_dma
suffix:semicolon
DECL|member|req_frames
id|MPT_FRAME_HDR
op_star
id|req_frames
suffix:semicolon
multiline_comment|/* Request msg frames - rounded up! */
DECL|member|req_frames_dma
id|dma_addr_t
id|req_frames_dma
suffix:semicolon
DECL|member|req_frames_low_dma
id|u32
id|req_frames_low_dma
suffix:semicolon
DECL|member|req_depth
r_int
id|req_depth
suffix:semicolon
multiline_comment|/* Number of request frames */
DECL|member|req_sz
r_int
id|req_sz
suffix:semicolon
multiline_comment|/* Request frame size (bytes) */
DECL|member|FreeQlock
id|spinlock_t
id|FreeQlock
suffix:semicolon
DECL|member|FreeQ
id|MPT_Q_TRACKER
id|FreeQ
suffix:semicolon
multiline_comment|/* Pool of SCSI sense buffers for commands coming from&n;&t;&t; * the SCSI mid-layer.  We have one 256 byte sense buffer&n;&t;&t; * for each REQ entry.&n;&t;&t; */
DECL|member|sense_buf_pool
id|u8
op_star
id|sense_buf_pool
suffix:semicolon
DECL|member|sense_buf_pool_dma
id|dma_addr_t
id|sense_buf_pool_dma
suffix:semicolon
DECL|member|sense_buf_low_dma
id|u32
id|sense_buf_low_dma
suffix:semicolon
DECL|member|mtrr_reg
r_int
id|mtrr_reg
suffix:semicolon
DECL|member|pcidev
r_void
op_star
id|pcidev
suffix:semicolon
multiline_comment|/* struct pci_dev pointer */
DECL|member|memmap
id|u8
op_star
id|memmap
suffix:semicolon
multiline_comment|/* mmap address */
DECL|member|sh
r_struct
id|Scsi_Host
op_star
id|sh
suffix:semicolon
multiline_comment|/* Scsi Host pointer */
DECL|member|spi_data
id|ScsiCfgData
id|spi_data
suffix:semicolon
multiline_comment|/* Scsi config. data */
DECL|member|ioctl
id|MPT_IOCTL
op_star
id|ioctl
suffix:semicolon
multiline_comment|/* ioctl data pointer */
DECL|member|ioc_dentry
r_struct
id|proc_dir_entry
op_star
id|ioc_dentry
suffix:semicolon
DECL|member|alt_ioc
r_struct
id|_MPT_ADAPTER
op_star
id|alt_ioc
suffix:semicolon
multiline_comment|/* ptr to 929 bound adapter port */
DECL|member|diagLock
id|spinlock_t
id|diagLock
suffix:semicolon
multiline_comment|/* diagnostic reset lock */
DECL|member|diagPending
r_int
id|diagPending
suffix:semicolon
DECL|member|biosVersion
id|u32
id|biosVersion
suffix:semicolon
multiline_comment|/* BIOS version from IO Unit Page 2 */
DECL|member|eventTypes
r_int
id|eventTypes
suffix:semicolon
multiline_comment|/* Event logging parameters */
DECL|member|eventContext
r_int
id|eventContext
suffix:semicolon
multiline_comment|/* Next event context */
DECL|member|eventLogSize
r_int
id|eventLogSize
suffix:semicolon
multiline_comment|/* Max number of cached events */
DECL|member|events
r_struct
id|_mpt_ioctl_events
op_star
id|events
suffix:semicolon
multiline_comment|/* pointer to event log */
DECL|member|cached_fw
id|fw_image_t
op_star
op_star
id|cached_fw
suffix:semicolon
multiline_comment|/* Pointer to FW SG List */
DECL|member|configQ
id|Q_TRACKER
id|configQ
suffix:semicolon
multiline_comment|/* linked list of config. requests */
DECL|member|num_fw_frags
r_int
id|num_fw_frags
suffix:semicolon
multiline_comment|/* Number of SGE in FW SG List */
DECL|member|hs_reply_idx
r_int
id|hs_reply_idx
suffix:semicolon
macro_line|#ifndef MFCNT
DECL|member|pad0
id|u32
id|pad0
suffix:semicolon
macro_line|#else
DECL|member|mfcnt
id|u32
id|mfcnt
suffix:semicolon
macro_line|#endif
DECL|member|hs_req
id|u32
id|hs_req
(braket
id|MPT_MAX_FRAME_SIZE
op_div
r_sizeof
(paren
id|u32
)paren
)braket
suffix:semicolon
DECL|member|hs_reply
id|u16
id|hs_reply
(braket
id|MPT_MAX_FRAME_SIZE
op_div
r_sizeof
(paren
id|u16
)paren
)braket
suffix:semicolon
DECL|member|facts
id|IOCFactsReply_t
id|facts
suffix:semicolon
DECL|member|pfacts
id|PortFactsReply_t
id|pfacts
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|fc_port_page0
id|FCPortPage0_t
id|fc_port_page0
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|lan_cnfg_page0
id|LANPage0_t
id|lan_cnfg_page0
suffix:semicolon
DECL|member|lan_cnfg_page1
id|LANPage1_t
id|lan_cnfg_page1
suffix:semicolon
DECL|member|FirstWhoInit
id|u8
id|FirstWhoInit
suffix:semicolon
DECL|member|upload_fw
id|u8
id|upload_fw
suffix:semicolon
multiline_comment|/* If set, do a fw upload */
DECL|member|pad1
id|u8
id|pad1
(braket
l_int|6
)braket
suffix:semicolon
DECL|typedef|MPT_ADAPTER
)brace
id|MPT_ADAPTER
suffix:semicolon
DECL|struct|_MPT_ADAPTER_TRACKER
r_typedef
r_struct
id|_MPT_ADAPTER_TRACKER
(brace
DECL|member|head
id|MPT_ADAPTER
op_star
id|head
suffix:semicolon
DECL|member|tail
id|MPT_ADAPTER
op_star
id|tail
suffix:semicolon
DECL|typedef|MPT_ADAPTER_TRACKER
)brace
id|MPT_ADAPTER_TRACKER
suffix:semicolon
multiline_comment|/*&n; *  New return value convention:&n; *    1 = Ok to free associated request frame&n; *    0 = not Ok ...&n; */
DECL|typedef|MPT_CALLBACK
r_typedef
r_int
(paren
op_star
id|MPT_CALLBACK
)paren
(paren
id|MPT_ADAPTER
op_star
id|ioc
comma
id|MPT_FRAME_HDR
op_star
id|req
comma
id|MPT_FRAME_HDR
op_star
id|reply
)paren
suffix:semicolon
DECL|typedef|MPT_EVHANDLER
r_typedef
r_int
(paren
op_star
id|MPT_EVHANDLER
)paren
(paren
id|MPT_ADAPTER
op_star
id|ioc
comma
id|EventNotificationReply_t
op_star
id|evReply
)paren
suffix:semicolon
DECL|typedef|MPT_RESETHANDLER
r_typedef
r_int
(paren
op_star
id|MPT_RESETHANDLER
)paren
(paren
id|MPT_ADAPTER
op_star
id|ioc
comma
r_int
id|reset_phase
)paren
suffix:semicolon
multiline_comment|/* reset_phase defs */
DECL|macro|MPT_IOC_PRE_RESET
mdefine_line|#define MPT_IOC_PRE_RESET&t;&t;0
DECL|macro|MPT_IOC_POST_RESET
mdefine_line|#define MPT_IOC_POST_RESET&t;&t;1
multiline_comment|/*&n; * Invent MPT host event (super-set of MPI Events)&n; * Fitted to 1030&squot;s 64-byte [max] request frame size&n; */
DECL|struct|_MPT_HOST_EVENT
r_typedef
r_struct
id|_MPT_HOST_EVENT
(brace
DECL|member|MpiEvent
id|EventNotificationReply_t
id|MpiEvent
suffix:semicolon
multiline_comment|/* 8 32-bit words! */
DECL|member|pad
id|u32
id|pad
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|next
r_void
op_star
id|next
suffix:semicolon
DECL|typedef|MPT_HOST_EVENT
)brace
id|MPT_HOST_EVENT
suffix:semicolon
DECL|macro|MPT_HOSTEVENT_IOC_BRINGUP
mdefine_line|#define MPT_HOSTEVENT_IOC_BRINGUP&t;0x91
DECL|macro|MPT_HOSTEVENT_IOC_RECOVER
mdefine_line|#define MPT_HOSTEVENT_IOC_RECOVER&t;0x92
multiline_comment|/* Define the generic types based on the size&n; * of the dma_addr_t type.&n; */
DECL|struct|_mpt_sge
r_typedef
r_struct
id|_mpt_sge
(brace
DECL|member|FlagsLength
id|u32
id|FlagsLength
suffix:semicolon
DECL|member|Address
id|dma_addr_t
id|Address
suffix:semicolon
DECL|typedef|MptSge_t
)brace
id|MptSge_t
suffix:semicolon
DECL|macro|mpt_addr_size
mdefine_line|#define mpt_addr_size() &bslash;&n;&t;((sizeof(dma_addr_t) == sizeof(u64)) ? MPI_SGE_FLAGS_64_BIT_ADDRESSING : &bslash;&n;&t;&t;MPI_SGE_FLAGS_32_BIT_ADDRESSING)
DECL|macro|mpt_msg_flags
mdefine_line|#define mpt_msg_flags() &bslash;&n;&t;((sizeof(dma_addr_t) == sizeof(u64)) ? MPI_SCSIIO_MSGFLGS_SENSE_WIDTH_64 : &bslash;&n;&t;&t;MPI_SCSIIO_MSGFLGS_SENSE_WIDTH_32)
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *  Funky (private) macros...&n; */
macro_line|#ifdef MPT_DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(x)  printk x
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(x)
macro_line|#endif
macro_line|#ifdef MPT_DEBUG_HANDSHAKE
DECL|macro|dhsprintk
mdefine_line|#define dhsprintk(x)  printk x
macro_line|#else
DECL|macro|dhsprintk
mdefine_line|#define dhsprintk(x)
macro_line|#endif
singleline_comment|//#if defined(MPT_DEBUG) || defined(MPT_DEBUG_MSG_FRAME)
macro_line|#if defined(MPT_DEBUG_MSG_FRAME)
DECL|macro|dmfprintk
mdefine_line|#define dmfprintk(x)  printk x
macro_line|#else
DECL|macro|dmfprintk
mdefine_line|#define dmfprintk(x)
macro_line|#endif
macro_line|#ifdef MPT_DEBUG_IRQ
DECL|macro|dirqprintk
mdefine_line|#define dirqprintk(x)  printk x
macro_line|#else
DECL|macro|dirqprintk
mdefine_line|#define dirqprintk(x)
macro_line|#endif
macro_line|#ifdef MPT_DEBUG_SG
DECL|macro|dsgprintk
mdefine_line|#define dsgprintk(x)  printk x
macro_line|#else
DECL|macro|dsgprintk
mdefine_line|#define dsgprintk(x)
macro_line|#endif
macro_line|#ifdef MPT_DEBUG_DV
DECL|macro|ddvprintk
mdefine_line|#define ddvprintk(x)  printk x
macro_line|#else
DECL|macro|ddvprintk
mdefine_line|#define ddvprintk(x)
macro_line|#endif
macro_line|#if defined(MPT_DEBUG_DV) || defined(MPT_DEBUG_DV_TINY)
DECL|macro|ddvtprintk
mdefine_line|#define ddvtprintk(x)  printk x
macro_line|#else
DECL|macro|ddvtprintk
mdefine_line|#define ddvtprintk(x)
macro_line|#endif
macro_line|#ifdef MPT_DEBUG_IOCTL
DECL|macro|dctlprintk
mdefine_line|#define dctlprintk(x) printk x
macro_line|#else
DECL|macro|dctlprintk
mdefine_line|#define dctlprintk(x)
macro_line|#endif
macro_line|#ifdef MPT_DEBUG_RESET
DECL|macro|dtmprintk
mdefine_line|#define dtmprintk(x) printk x
macro_line|#else
DECL|macro|dtmprintk
mdefine_line|#define dtmprintk(x)
macro_line|#endif
macro_line|#ifdef MPT_DEBUG_NEH
DECL|macro|nehprintk
mdefine_line|#define nehprintk(x) printk x
macro_line|#else
DECL|macro|nehprintk
mdefine_line|#define nehprintk(x)
macro_line|#endif
DECL|macro|MPT_INDEX_2_MFPTR
mdefine_line|#define MPT_INDEX_2_MFPTR(ioc,idx) &bslash;&n;&t;(MPT_FRAME_HDR*)( (u8*)(ioc)-&gt;req_frames + (ioc)-&gt;req_sz * (idx) )
DECL|macro|MFPTR_2_MPT_INDEX
mdefine_line|#define MFPTR_2_MPT_INDEX(ioc,mf) &bslash;&n;&t;(int)( ((u8*)mf - (u8*)(ioc)-&gt;req_frames) / (ioc)-&gt;req_sz )
DECL|macro|MPT_INDEX_2_RFPTR
mdefine_line|#define MPT_INDEX_2_RFPTR(ioc,idx) &bslash;&n;&t;(MPT_FRAME_HDR*)( (u8*)(ioc)-&gt;reply_frames + (ioc)-&gt;req_sz * (idx) )
DECL|macro|Q_INIT
mdefine_line|#define Q_INIT(q,type)  (q)-&gt;head = (q)-&gt;tail = (type*)(q)
DECL|macro|Q_IS_EMPTY
mdefine_line|#define Q_IS_EMPTY(q)   ((Q_ITEM*)(q)-&gt;head == (Q_ITEM*)(q))
DECL|macro|Q_ADD_TAIL
mdefine_line|#define Q_ADD_TAIL(qt,i,type) { &bslash;&n;&t;Q_TRACKER&t;*_qt = (Q_TRACKER*)(qt); &bslash;&n;&t;Q_ITEM&t;&t;*oldTail = _qt-&gt;tail; &bslash;&n;&t;(i)-&gt;forw = (type*)_qt; &bslash;&n;&t;(i)-&gt;back = (type*)oldTail; &bslash;&n;&t;oldTail-&gt;forw = (Q_ITEM*)(i); &bslash;&n;&t;_qt-&gt;tail = (Q_ITEM*)(i); &bslash;&n;}
DECL|macro|Q_ADD_HEAD
mdefine_line|#define Q_ADD_HEAD(qt,i,type) { &bslash;&n;&t;Q_TRACKER&t;*_qt = (Q_TRACKER*)(qt); &bslash;&n;&t;Q_ITEM&t;&t;*oldHead = _qt-&gt;head; &bslash;&n;&t;(i)-&gt;forw = (type*)oldHead; &bslash;&n;&t;(i)-&gt;back = (type*)_qt; &bslash;&n;&t;oldHead-&gt;back = (Q_ITEM*)(i); &bslash;&n;&t;_qt-&gt;head = (Q_ITEM*)(i); &bslash;&n;}
DECL|macro|Q_DEL_ITEM
mdefine_line|#define Q_DEL_ITEM(i) { &bslash;&n;&t;Q_ITEM  *_forw = (Q_ITEM*)(i)-&gt;forw; &bslash;&n;&t;Q_ITEM  *_back = (Q_ITEM*)(i)-&gt;back; &bslash;&n;&t;_back-&gt;forw = _forw; &bslash;&n;&t;_forw-&gt;back = _back; &bslash;&n;}
DECL|macro|SWAB4
mdefine_line|#define SWAB4(value) &bslash;&n;&t;(u32)(   (((value) &amp; 0x000000ff) &lt;&lt; 24) &bslash;&n;&t;       | (((value) &amp; 0x0000ff00) &lt;&lt; 8)  &bslash;&n;&t;       | (((value) &amp; 0x00ff0000) &gt;&gt; 8)  &bslash;&n;&t;       | (((value) &amp; 0xff000000) &gt;&gt; 24) )
macro_line|#if defined(MPT_DEBUG) || defined(MPT_DEBUG_MSG_FRAME)
DECL|macro|DBG_DUMP_REPLY_FRAME
mdefine_line|#define DBG_DUMP_REPLY_FRAME(mfp) &bslash;&n;&t;{&t;u32 *m = (u32 *)(mfp);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int  i, n = (le32_to_cpu(m[0]) &amp; 0x00FF0000) &gt;&gt; 16;&t;&bslash;&n;&t;&t;printk(KERN_INFO &quot; &quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;for (i=0; i&lt;n; i++)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;printk(&quot; %08x&quot;, le32_to_cpu(m[i]));&t;&t;&bslash;&n;&t;&t;printk(&quot;&bslash;n&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
DECL|macro|DBG_DUMP_REQUEST_FRAME_HDR
mdefine_line|#define DBG_DUMP_REQUEST_FRAME_HDR(mfp) &bslash;&n;&t;{&t;int  i, n = 3;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;u32 *m = (u32 *)(mfp);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;printk(KERN_INFO &quot; &quot;);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;for (i=0; i&lt;n; i++)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;printk(&quot; %08x&quot;, le32_to_cpu(m[i]));&t;&t;&bslash;&n;&t;&t;printk(&quot;&bslash;n&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}
macro_line|#else
DECL|macro|DBG_DUMP_REPLY_FRAME
mdefine_line|#define DBG_DUMP_REPLY_FRAME(mfp)
DECL|macro|DBG_DUMP_REQUEST_FRAME_HDR
mdefine_line|#define DBG_DUMP_REQUEST_FRAME_HDR(mfp)
macro_line|#endif
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; * MPT_SCSI_HOST defines - Used by the IOCTL and the SCSI drivers&n; * Private to the driver.&n; */
multiline_comment|/* LOCAL structure and fields used when processing&n; * internally generated commands. These include:&n; * bus scan, dv and config requests.&n; */
DECL|struct|_MPT_LOCAL_REPLY
r_typedef
r_struct
id|_MPT_LOCAL_REPLY
(brace
DECL|member|header
id|ConfigPageHeader_t
id|header
suffix:semicolon
DECL|member|completion
r_int
id|completion
suffix:semicolon
DECL|member|sense
id|u8
id|sense
(braket
id|SCSI_STD_SENSE_BYTES
)braket
suffix:semicolon
DECL|member|scsiStatus
id|u8
id|scsiStatus
suffix:semicolon
DECL|member|skip
id|u8
id|skip
suffix:semicolon
DECL|member|pad
id|u32
id|pad
suffix:semicolon
DECL|typedef|MPT_LOCAL_REPLY
)brace
id|MPT_LOCAL_REPLY
suffix:semicolon
DECL|macro|MPT_HOST_BUS_UNKNOWN
mdefine_line|#define MPT_HOST_BUS_UNKNOWN&t;&t;(0xFF)
DECL|macro|MPT_HOST_TOO_MANY_TM
mdefine_line|#define MPT_HOST_TOO_MANY_TM&t;&t;(0x05)
DECL|macro|MPT_HOST_NVRAM_INVALID
mdefine_line|#define MPT_HOST_NVRAM_INVALID&t;&t;(0xFFFFFFFF)
DECL|macro|MPT_HOST_NO_CHAIN
mdefine_line|#define MPT_HOST_NO_CHAIN&t;&t;(0xFFFFFFFF)
DECL|macro|MPT_NVRAM_MASK_TIMEOUT
mdefine_line|#define MPT_NVRAM_MASK_TIMEOUT&t;&t;(0x000000FF)
DECL|macro|MPT_NVRAM_SYNC_MASK
mdefine_line|#define MPT_NVRAM_SYNC_MASK&t;&t;(0x0000FF00)
DECL|macro|MPT_NVRAM_SYNC_SHIFT
mdefine_line|#define MPT_NVRAM_SYNC_SHIFT&t;&t;(8)
DECL|macro|MPT_NVRAM_DISCONNECT_ENABLE
mdefine_line|#define MPT_NVRAM_DISCONNECT_ENABLE&t;(0x00010000)
DECL|macro|MPT_NVRAM_ID_SCAN_ENABLE
mdefine_line|#define MPT_NVRAM_ID_SCAN_ENABLE&t;(0x00020000)
DECL|macro|MPT_NVRAM_LUN_SCAN_ENABLE
mdefine_line|#define MPT_NVRAM_LUN_SCAN_ENABLE&t;(0x00040000)
DECL|macro|MPT_NVRAM_TAG_QUEUE_ENABLE
mdefine_line|#define MPT_NVRAM_TAG_QUEUE_ENABLE&t;(0x00080000)
DECL|macro|MPT_NVRAM_WIDE_DISABLE
mdefine_line|#define MPT_NVRAM_WIDE_DISABLE&t;&t;(0x00100000)
DECL|macro|MPT_NVRAM_BOOT_CHOICE
mdefine_line|#define MPT_NVRAM_BOOT_CHOICE&t;&t;(0x00200000)
macro_line|#ifdef MPT_SCSI_USE_NEW_EH
multiline_comment|/* The TM_STATE variable is used to provide strict single threading of TM&n; * requests as well as communicate TM error conditions.&n; */
DECL|macro|TM_STATE_NONE
mdefine_line|#define TM_STATE_NONE          (0)
DECL|macro|TM_STATE_IN_PROGRESS
mdefine_line|#define&t;TM_STATE_IN_PROGRESS   (1)
DECL|macro|TM_STATE_ERROR
mdefine_line|#define&t;TM_STATE_ERROR&t;       (2)
macro_line|#endif
DECL|struct|_MPT_SCSI_HOST
r_typedef
r_struct
id|_MPT_SCSI_HOST
(brace
DECL|member|ioc
id|MPT_ADAPTER
op_star
id|ioc
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|pad0
id|u32
id|pad0
suffix:semicolon
DECL|member|ScsiLookup
r_struct
id|scsi_cmnd
op_star
op_star
id|ScsiLookup
suffix:semicolon
multiline_comment|/* Pool of buffers for chaining. ReqToChain&n;&t;&t; * and ChainToChain track index of chain buffers.&n;&t;&t; * ChainBuffer (DMA) virt/phys addresses.&n;&t;&t; * FreeChainQ (lock) locking mechanisms.&n;&t;&t; */
DECL|member|ReqToChain
r_int
op_star
id|ReqToChain
suffix:semicolon
DECL|member|ChainToChain
r_int
op_star
id|ChainToChain
suffix:semicolon
DECL|member|ChainBuffer
id|u8
op_star
id|ChainBuffer
suffix:semicolon
DECL|member|ChainBufferDMA
id|dma_addr_t
id|ChainBufferDMA
suffix:semicolon
DECL|member|FreeChainQ
id|MPT_Q_TRACKER
id|FreeChainQ
suffix:semicolon
DECL|member|FreeChainQlock
id|spinlock_t
id|FreeChainQlock
suffix:semicolon
DECL|member|qtag_tick
id|u32
id|qtag_tick
suffix:semicolon
DECL|member|Targets
id|VirtDevice
op_star
op_star
id|Targets
suffix:semicolon
DECL|member|pLocal
id|MPT_LOCAL_REPLY
op_star
id|pLocal
suffix:semicolon
multiline_comment|/* used for internal commands */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|TMtimer
r_struct
id|timer_list
id|TMtimer
suffix:semicolon
multiline_comment|/* Timer for TM commands ONLY */
multiline_comment|/* Pool of memory for holding SCpnts before doing&n;&t;&t; * OS callbacks. freeQ is the free pool.&n;&t;&t; */
DECL|member|memQ
id|u8
op_star
id|memQ
suffix:semicolon
DECL|member|freeQ
id|DONE_Q_TRACKER
id|freeQ
suffix:semicolon
DECL|member|doneQ
id|DONE_Q_TRACKER
id|doneQ
suffix:semicolon
multiline_comment|/* Holds Linux formmatted requests */
DECL|member|pendingQ
id|DONE_Q_TRACKER
id|pendingQ
suffix:semicolon
multiline_comment|/* Holds MPI formmatted requests */
DECL|member|taskQ
id|MPT_Q_TRACKER
id|taskQ
suffix:semicolon
multiline_comment|/* TM request Q */
DECL|member|freedoneQlock
id|spinlock_t
id|freedoneQlock
suffix:semicolon
DECL|member|taskQcnt
r_int
id|taskQcnt
suffix:semicolon
DECL|member|numTMrequests
id|u8
id|numTMrequests
suffix:semicolon
DECL|member|tmPending
id|u8
id|tmPending
suffix:semicolon
DECL|member|resetPending
id|u8
id|resetPending
suffix:semicolon
DECL|member|is_spi
id|u8
id|is_spi
suffix:semicolon
multiline_comment|/* Parallel SCSI i/f */
DECL|member|negoNvram
id|u8
id|negoNvram
suffix:semicolon
multiline_comment|/* DV disabled, nego NVRAM */
DECL|member|is_multipath
id|u8
id|is_multipath
suffix:semicolon
multiline_comment|/* Multi-path compatible */
macro_line|#ifdef MPT_SCSI_USE_NEW_EH
DECL|member|tmState
id|u8
id|tmState
suffix:semicolon
DECL|member|rsvd
id|u8
id|rsvd
(braket
l_int|1
)braket
suffix:semicolon
macro_line|#else
DECL|member|rsvd
id|u8
id|rsvd
(braket
l_int|2
)braket
suffix:semicolon
macro_line|#endif
DECL|member|tmPtr
id|MPT_FRAME_HDR
op_star
id|tmPtr
suffix:semicolon
multiline_comment|/* Ptr to TM request*/
DECL|member|cmdPtr
id|MPT_FRAME_HDR
op_star
id|cmdPtr
suffix:semicolon
multiline_comment|/* Ptr to nonOS request */
DECL|member|abortSCpnt
r_struct
id|scsi_cmnd
op_star
id|abortSCpnt
suffix:semicolon
DECL|member|localReply
id|MPT_LOCAL_REPLY
id|localReply
suffix:semicolon
multiline_comment|/* internal cmd reply struct */
DECL|typedef|MPT_SCSI_HOST
)brace
id|MPT_SCSI_HOST
suffix:semicolon
multiline_comment|/*&n; *&t;Structure for overlaying onto scsi_cmnd-&gt;SCp area&n; *&t;NOTE: SCp area is 36 bytes min, 44 bytes max?&n; */
DECL|struct|_scPrivate
r_typedef
r_struct
id|_scPrivate
(brace
DECL|member|forw
r_struct
id|scsi_cmnd
op_star
id|forw
suffix:semicolon
DECL|member|back
r_struct
id|scsi_cmnd
op_star
id|back
suffix:semicolon
DECL|member|p1
r_void
op_star
id|p1
suffix:semicolon
DECL|member|p2
r_void
op_star
id|p2
suffix:semicolon
DECL|member|io_path_id
id|u8
id|io_path_id
suffix:semicolon
multiline_comment|/* DMP */
DECL|member|pad
id|u8
id|pad
(braket
l_int|7
)braket
suffix:semicolon
DECL|typedef|scPrivate
)brace
id|scPrivate
suffix:semicolon
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *&t;More Dynamic Multi-Pathing stuff...&n; */
multiline_comment|/* Forward decl, a strange C thing, to prevent gcc compiler warnings */
r_struct
id|scsi_cmnd
suffix:semicolon
multiline_comment|/*&n; *&t;DMP service layer structure / API interface&n; */
DECL|struct|_DmpServices
r_typedef
r_struct
id|_DmpServices
(brace
DECL|member|VdevList
id|VirtDevTracker
id|VdevList
suffix:semicolon
DECL|member|Daemon
r_struct
id|semaphore
op_star
id|Daemon
suffix:semicolon
DECL|member|ScsiPathSelect
r_int
(paren
op_star
id|ScsiPathSelect
)paren
(paren
r_struct
id|scsi_cmnd
op_star
comma
id|MPT_SCSI_HOST
op_star
op_star
id|hd
comma
r_int
op_star
id|target
comma
r_int
op_star
id|lun
)paren
suffix:semicolon
DECL|member|DmpIoDoneChk
r_int
(paren
op_star
id|DmpIoDoneChk
)paren
(paren
id|MPT_SCSI_HOST
op_star
comma
r_struct
id|scsi_cmnd
op_star
comma
id|SCSIIORequest_t
op_star
comma
id|SCSIIOReply_t
op_star
)paren
suffix:semicolon
DECL|member|mptscsih_scanVlist
r_void
(paren
op_star
id|mptscsih_scanVlist
)paren
(paren
id|MPT_SCSI_HOST
op_star
comma
r_int
id|portnum
)paren
suffix:semicolon
DECL|member|ScsiAbort
r_int
(paren
op_star
id|ScsiAbort
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
DECL|member|ScsiBusReset
r_int
(paren
op_star
id|ScsiBusReset
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
DECL|typedef|DmpServices_t
)brace
id|DmpServices_t
suffix:semicolon
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; * Generic structure passed to the base mpt_config function.&n; */
DECL|struct|_x_config_parms
r_typedef
r_struct
id|_x_config_parms
(brace
DECL|member|linkage
id|Q_ITEM
id|linkage
suffix:semicolon
multiline_comment|/* linked list */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* timer function for this request  */
DECL|member|hdr
id|ConfigPageHeader_t
op_star
id|hdr
suffix:semicolon
DECL|member|physAddr
id|dma_addr_t
id|physAddr
suffix:semicolon
DECL|member|wait_done
r_int
id|wait_done
suffix:semicolon
multiline_comment|/* wait for this request */
DECL|member|pageAddr
id|u32
id|pageAddr
suffix:semicolon
multiline_comment|/* properly formatted */
DECL|member|action
id|u8
id|action
suffix:semicolon
DECL|member|dir
id|u8
id|dir
suffix:semicolon
DECL|member|timeout
id|u8
id|timeout
suffix:semicolon
multiline_comment|/* seconds */
DECL|member|pad1
id|u8
id|pad1
suffix:semicolon
DECL|member|status
id|u16
id|status
suffix:semicolon
DECL|member|pad2
id|u16
id|pad2
suffix:semicolon
DECL|typedef|CONFIGPARMS
)brace
id|CONFIGPARMS
suffix:semicolon
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *  Public entry points...&n; */
r_extern
r_int
id|mpt_register
c_func
(paren
id|MPT_CALLBACK
id|cbfunc
comma
id|MPT_DRIVER_CLASS
id|dclass
)paren
suffix:semicolon
r_extern
r_void
id|mpt_deregister
c_func
(paren
r_int
id|cb_idx
)paren
suffix:semicolon
r_extern
r_int
id|mpt_event_register
c_func
(paren
r_int
id|cb_idx
comma
id|MPT_EVHANDLER
id|ev_cbfunc
)paren
suffix:semicolon
r_extern
r_void
id|mpt_event_deregister
c_func
(paren
r_int
id|cb_idx
)paren
suffix:semicolon
r_extern
r_int
id|mpt_reset_register
c_func
(paren
r_int
id|cb_idx
comma
id|MPT_RESETHANDLER
id|reset_func
)paren
suffix:semicolon
r_extern
r_void
id|mpt_reset_deregister
c_func
(paren
r_int
id|cb_idx
)paren
suffix:semicolon
r_extern
r_int
id|mpt_register_ascqops_strings
c_func
(paren
r_void
op_star
id|ascqTable
comma
r_int
id|ascqtbl_sz
comma
r_const
r_char
op_star
op_star
id|opsTable
)paren
suffix:semicolon
r_extern
r_void
id|mpt_deregister_ascqops_strings
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|MPT_FRAME_HDR
op_star
id|mpt_get_msg_frame
c_func
(paren
r_int
id|handle
comma
r_int
id|iocid
)paren
suffix:semicolon
r_extern
r_void
id|mpt_free_msg_frame
c_func
(paren
r_int
id|handle
comma
r_int
id|iocid
comma
id|MPT_FRAME_HDR
op_star
id|mf
)paren
suffix:semicolon
r_extern
r_void
id|mpt_put_msg_frame
c_func
(paren
r_int
id|handle
comma
r_int
id|iocid
comma
id|MPT_FRAME_HDR
op_star
id|mf
)paren
suffix:semicolon
r_extern
r_void
id|mpt_add_sge
c_func
(paren
r_char
op_star
id|pAddr
comma
id|u32
id|flagslength
comma
id|dma_addr_t
id|dma_addr
)paren
suffix:semicolon
r_extern
r_void
id|mpt_add_chain
c_func
(paren
r_char
op_star
id|pAddr
comma
id|u8
id|next
comma
id|u16
id|length
comma
id|dma_addr_t
id|dma_addr
)paren
suffix:semicolon
r_extern
r_int
id|mpt_send_handshake_request
c_func
(paren
r_int
id|handle
comma
r_int
id|iocid
comma
r_int
id|reqBytes
comma
id|u32
op_star
id|req
comma
r_int
id|sleepFlag
)paren
suffix:semicolon
r_extern
r_int
id|mpt_handshake_req_reply_wait
c_func
(paren
id|MPT_ADAPTER
op_star
id|ioc
comma
r_int
id|reqBytes
comma
id|u32
op_star
id|req
comma
r_int
id|replyBytes
comma
id|u16
op_star
id|u16reply
comma
r_int
id|maxwait
comma
r_int
id|sleepFlag
)paren
suffix:semicolon
r_extern
r_int
id|mpt_verify_adapter
c_func
(paren
r_int
id|iocid
comma
id|MPT_ADAPTER
op_star
op_star
id|iocpp
)paren
suffix:semicolon
r_extern
id|MPT_ADAPTER
op_star
id|mpt_adapter_find_first
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|MPT_ADAPTER
op_star
id|mpt_adapter_find_next
c_func
(paren
id|MPT_ADAPTER
op_star
id|prev
)paren
suffix:semicolon
r_extern
id|u32
id|mpt_GetIocState
c_func
(paren
id|MPT_ADAPTER
op_star
id|ioc
comma
r_int
id|cooked
)paren
suffix:semicolon
r_extern
r_void
id|mpt_print_ioc_summary
c_func
(paren
id|MPT_ADAPTER
op_star
id|ioc
comma
r_char
op_star
id|buf
comma
r_int
op_star
id|size
comma
r_int
id|len
comma
r_int
id|showlan
)paren
suffix:semicolon
r_extern
r_int
id|mpt_HardResetHandler
c_func
(paren
id|MPT_ADAPTER
op_star
id|ioc
comma
r_int
id|sleepFlag
)paren
suffix:semicolon
r_extern
r_int
id|mpt_config
c_func
(paren
id|MPT_ADAPTER
op_star
id|ioc
comma
id|CONFIGPARMS
op_star
id|cfg
)paren
suffix:semicolon
r_extern
r_void
op_star
id|mpt_alloc_fw_memory
c_func
(paren
id|MPT_ADAPTER
op_star
id|ioc
comma
r_int
id|size
comma
r_int
op_star
id|frags
comma
r_int
op_star
id|alloc_sz
)paren
suffix:semicolon
r_extern
r_void
id|mpt_free_fw_memory
c_func
(paren
id|MPT_ADAPTER
op_star
id|ioc
comma
id|fw_image_t
op_star
op_star
id|alt_img
)paren
suffix:semicolon
multiline_comment|/*&n; *  Public data decl&squot;s...&n; */
r_extern
id|MPT_ADAPTER
op_star
id|mpt_adapters
(braket
id|MPT_MAX_ADAPTERS
)braket
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
op_star
id|mpt_proc_root_dir
suffix:semicolon
r_extern
id|DmpServices_t
op_star
id|DmpService
suffix:semicolon
r_extern
r_int
id|mpt_lan_index
suffix:semicolon
multiline_comment|/* needed by mptlan.c */
r_extern
r_int
id|mpt_stm_index
suffix:semicolon
multiline_comment|/* needed by mptstm.c */
r_extern
r_void
op_star
id|mpt_v_ASCQ_TablePtr
suffix:semicolon
r_extern
r_const
r_char
op_star
op_star
id|mpt_ScsiOpcodesPtr
suffix:semicolon
r_extern
r_int
id|mpt_ASCQ_TableSz
suffix:semicolon
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#endif&t;&t;/* } __KERNEL__ */
multiline_comment|/*&n; *  More (public) macros...&n; */
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a, b)   (((a) &lt; (b)) ? (a) : (b))
macro_line|#endif
macro_line|#ifndef MAX
DECL|macro|MAX
mdefine_line|#define MAX(a, b)   (((a) &gt; (b)) ? (a) : (b))
macro_line|#endif
macro_line|#ifndef offsetof
DECL|macro|offsetof
mdefine_line|#define offsetof(t, m)&t;((size_t) (&amp;((t *)0)-&gt;m))
macro_line|#endif
macro_line|#if defined(__alpha__) || defined(__sparc_v9__) || defined(__ia64__)
DECL|macro|CAST_U32_TO_PTR
mdefine_line|#define CAST_U32_TO_PTR(x)&t;((void *)(u64)x)
DECL|macro|CAST_PTR_TO_U32
mdefine_line|#define CAST_PTR_TO_U32(x)&t;((u32)(u64)x)
macro_line|#else
DECL|macro|CAST_U32_TO_PTR
mdefine_line|#define CAST_U32_TO_PTR(x)&t;((void *)x)
DECL|macro|CAST_PTR_TO_U32
mdefine_line|#define CAST_PTR_TO_U32(x)&t;((u32)x)
macro_line|#endif
DECL|macro|MPT_PROTOCOL_FLAGS_c_c_c_c
mdefine_line|#define MPT_PROTOCOL_FLAGS_c_c_c_c(pflags) &bslash;&n;&t;((pflags) &amp; MPI_PORTFACTS_PROTOCOL_INITIATOR)&t;? &squot;I&squot; : &squot;i&squot;,&t;&bslash;&n;&t;((pflags) &amp; MPI_PORTFACTS_PROTOCOL_TARGET)&t;? &squot;T&squot; : &squot;t&squot;,&t;&bslash;&n;&t;((pflags) &amp; MPI_PORTFACTS_PROTOCOL_LAN)&t;&t;? &squot;L&squot; : &squot;l&squot;,&t;&bslash;&n;&t;((pflags) &amp; MPI_PORTFACTS_PROTOCOL_LOGBUSADDR)&t;? &squot;B&squot; : &squot;b&squot;
multiline_comment|/*&n; *  Shifted SGE Defines - Use in SGE with FlagsLength member.&n; *  Otherwise, use MPI_xxx defines (refer to &quot;lsi/mpi.h&quot; header).&n; *  Defaults: 32 bit SGE, SYSTEM_ADDRESS if direction bit is 0, read&n; */
DECL|macro|MPT_TRANSFER_IOC_TO_HOST
mdefine_line|#define MPT_TRANSFER_IOC_TO_HOST&t;&t;(0x00000000)
DECL|macro|MPT_TRANSFER_HOST_TO_IOC
mdefine_line|#define MPT_TRANSFER_HOST_TO_IOC&t;&t;(0x04000000)
DECL|macro|MPT_SGE_FLAGS_LAST_ELEMENT
mdefine_line|#define MPT_SGE_FLAGS_LAST_ELEMENT&t;&t;(0x80000000)
DECL|macro|MPT_SGE_FLAGS_END_OF_BUFFER
mdefine_line|#define MPT_SGE_FLAGS_END_OF_BUFFER&t;&t;(0x40000000)
DECL|macro|MPT_SGE_FLAGS_LOCAL_ADDRESS
mdefine_line|#define MPT_SGE_FLAGS_LOCAL_ADDRESS&t;&t;(0x08000000)
DECL|macro|MPT_SGE_FLAGS_DIRECTION
mdefine_line|#define MPT_SGE_FLAGS_DIRECTION&t;&t;&t;(0x04000000)
DECL|macro|MPT_SGE_FLAGS_ADDRESSING
mdefine_line|#define MPT_SGE_FLAGS_ADDRESSING&t;&t;(mpt_addr_size() &lt;&lt; MPI_SGE_FLAGS_SHIFT)
DECL|macro|MPT_SGE_FLAGS_END_OF_LIST
mdefine_line|#define MPT_SGE_FLAGS_END_OF_LIST&t;&t;(0x01000000)
DECL|macro|MPT_SGE_FLAGS_TRANSACTION_ELEMENT
mdefine_line|#define MPT_SGE_FLAGS_TRANSACTION_ELEMENT&t;(0x00000000)
DECL|macro|MPT_SGE_FLAGS_SIMPLE_ELEMENT
mdefine_line|#define MPT_SGE_FLAGS_SIMPLE_ELEMENT&t;&t;(0x10000000)
DECL|macro|MPT_SGE_FLAGS_CHAIN_ELEMENT
mdefine_line|#define MPT_SGE_FLAGS_CHAIN_ELEMENT&t;&t;(0x30000000)
DECL|macro|MPT_SGE_FLAGS_ELEMENT_MASK
mdefine_line|#define MPT_SGE_FLAGS_ELEMENT_MASK&t;&t;(0x30000000)
DECL|macro|MPT_SGE_FLAGS_SSIMPLE_READ
mdefine_line|#define MPT_SGE_FLAGS_SSIMPLE_READ &bslash;&n;&t;(MPT_SGE_FLAGS_LAST_ELEMENT |&t;&bslash;&n;&t; MPT_SGE_FLAGS_END_OF_BUFFER |&t;&bslash;&n;&t; MPT_SGE_FLAGS_END_OF_LIST |&t;&bslash;&n;&t; MPT_SGE_FLAGS_SIMPLE_ELEMENT |&t;&bslash;&n;&t; MPT_SGE_FLAGS_ADDRESSING | &bslash;&n;&t; MPT_TRANSFER_IOC_TO_HOST)
DECL|macro|MPT_SGE_FLAGS_SSIMPLE_WRITE
mdefine_line|#define MPT_SGE_FLAGS_SSIMPLE_WRITE &bslash;&n;&t;(MPT_SGE_FLAGS_LAST_ELEMENT |&t;&bslash;&n;&t; MPT_SGE_FLAGS_END_OF_BUFFER |&t;&bslash;&n;&t; MPT_SGE_FLAGS_END_OF_LIST |&t;&bslash;&n;&t; MPT_SGE_FLAGS_SIMPLE_ELEMENT |&t;&bslash;&n;&t; MPT_SGE_FLAGS_ADDRESSING | &bslash;&n;&t; MPT_TRANSFER_HOST_TO_IOC)
multiline_comment|/*}-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#endif
eof
