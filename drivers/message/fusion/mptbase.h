multiline_comment|/*&n; *  linux/drivers/message/fusion/mptbase.h&n; *      High performance SCSI + LAN / Fibre Channel device drivers.&n; *      For use with PCI chip/adapter(s):&n; *          LSIFC9xx/LSI409xx Fibre Channel&n; *      running LSI Logic Fusion MPT (Message Passing Technology) firmware.&n; *&n; *  Credits:&n; *     (see mptbase.c)&n; *&n; *  Copyright (c) 1999-2001 LSI Logic Corporation&n; *  Originally By: Steven J. Ralston&n; *  (mailto:Steve.Ralston@lsil.com)&n; *&n; *  $Id: mptbase.h,v 1.38 2001/03/22 10:54:30 sralston Exp $&n; */
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; version 2 of the License.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    NO WARRANTY&n;    THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;    LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;    solely responsible for determining the appropriateness of using and&n;    distributing the Program and assumes all risks associated with its&n;    exercise of rights under this Agreement, including but not limited to&n;    the risks and costs of program errors, damage to or loss of data,&n;    programs or equipment, and unavailability or interruption of operations.&n;&n;    DISCLAIMER OF LIABILITY&n;    NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;    DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;    USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;    HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#ifndef MPTBASE_H_INCLUDED
DECL|macro|MPTBASE_H_INCLUDED
mdefine_line|#define MPTBASE_H_INCLUDED
multiline_comment|/*{-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#include &quot;linux_compat.h&quot;&t;/* linux-2.2.x (vs. -2.4.x) tweaks */
macro_line|#include &quot;lsi/mpi_type.h&quot;
macro_line|#include &quot;lsi/mpi.h&quot;&t;&t;/* Fusion MPI(nterface) basic defs */
macro_line|#include &quot;lsi/mpi_ioc.h&quot;&t;/* Fusion MPT IOC(ontroller) defs */
macro_line|#include &quot;lsi/mpi_cnfg.h&quot;&t;/* IOC configuration support */
macro_line|#include &quot;lsi/mpi_init.h&quot;&t;/* SCSI Host (initiator) protocol support */
macro_line|#include &quot;lsi/mpi_lan.h&quot;&t;/* LAN over FC protocol support */
singleline_comment|//#include &quot;lsi/mpi_fc.h&quot;&t;/* Fibre Channel (lowlevel) support */
singleline_comment|//#include &quot;lsi/mpi_targ.h&quot;&t;/* SCSI/FCP Target protcol support */
macro_line|#include &quot;lsi/fc_log.h&quot;
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#ifndef MODULEAUTHOR
DECL|macro|MODULEAUTHOR
mdefine_line|#define MODULEAUTHOR&t;&quot;LSI Logic Corporation&quot;
macro_line|#endif
macro_line|#ifndef COPYRIGHT
DECL|macro|COPYRIGHT
mdefine_line|#define COPYRIGHT&t;&quot;Copyright (c) 1999-2001 &quot; MODULEAUTHOR
macro_line|#endif
DECL|macro|MPT_LINUX_VERSION_COMMON
mdefine_line|#define MPT_LINUX_VERSION_COMMON&t;&quot;1.00.11&quot;
DECL|macro|MPT_LINUX_VERSION_EXP
mdefine_line|#define MPT_LINUX_VERSION_EXP&t;&t;&quot;0.09.66-EXP&quot;
DECL|macro|MPT_LINUX_PACKAGE_NAME
mdefine_line|#define MPT_LINUX_PACKAGE_NAME&t;&t;&quot;@(#)mptlinux-1.00.11&quot;
DECL|macro|WHAT_MAGIC_STRING
mdefine_line|#define WHAT_MAGIC_STRING&t;&t;&quot;@&quot; &quot;(&quot; &quot;#&quot; &quot;)&quot;
DECL|macro|show_mptmod_ver
mdefine_line|#define show_mptmod_ver(s,ver)  &bslash;&n;&t;printk(KERN_INFO &quot;%s %s&bslash;n&quot;, s, ver);
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *  Fusion MPT(linux) driver configurable stuff...&n; */
DECL|macro|MPT_MAX_ADAPTERS
mdefine_line|#define MPT_MAX_ADAPTERS&t;&t;16
DECL|macro|MPT_MAX_PROTOCOL_DRIVERS
mdefine_line|#define MPT_MAX_PROTOCOL_DRIVERS&t;8
DECL|macro|MPT_MISCDEV_BASENAME
mdefine_line|#define MPT_MISCDEV_BASENAME&t;&t;&quot;mptctl&quot;
DECL|macro|MPT_MISCDEV_PATHNAME
mdefine_line|#define MPT_MISCDEV_PATHNAME&t;&t;&quot;/dev/&quot; MPT_MISCDEV_BASENAME
DECL|macro|MPT_PROCFS_MPTBASEDIR
mdefine_line|#define MPT_PROCFS_MPTBASEDIR&t;&t;&quot;mpt&quot;
multiline_comment|/* chg it to &quot;driver/fusion&quot; ? */
DECL|macro|MPT_PROCFS_SUMMARY_NODE
mdefine_line|#define MPT_PROCFS_SUMMARY_NODE&t;&t;MPT_PROCFS_MPTBASEDIR &quot;/summary&quot;
DECL|macro|MPT_PROCFS_SUMMARY_PATHNAME
mdefine_line|#define MPT_PROCFS_SUMMARY_PATHNAME&t;&quot;/proc/&quot; MPT_PROCFS_SUMMARY_NODE
DECL|macro|MPT_FW_REV_MAGIC_ID_STRING
mdefine_line|#define MPT_FW_REV_MAGIC_ID_STRING&t;&quot;FwRev=&quot;
macro_line|#ifdef __KERNEL__&t;/* { */
DECL|macro|MPT_MAX_REQ_DEPTH
mdefine_line|#define  MPT_MAX_REQ_DEPTH&t;&t;1023
DECL|macro|MPT_REQ_DEPTH
mdefine_line|#define  MPT_REQ_DEPTH&t;&t;&t;256
DECL|macro|MPT_MIN_REQ_DEPTH
mdefine_line|#define  MPT_MIN_REQ_DEPTH&t;&t;128
DECL|macro|MPT_MAX_REPLY_DEPTH
mdefine_line|#define  MPT_MAX_REPLY_DEPTH&t;&t;MPT_MAX_REQ_DEPTH
DECL|macro|MPT_REPLY_DEPTH
mdefine_line|#define  MPT_REPLY_DEPTH&t;&t;128
DECL|macro|MPT_MIN_REPLY_DEPTH
mdefine_line|#define  MPT_MIN_REPLY_DEPTH&t;&t;8
DECL|macro|MPT_MAX_REPLIES_PER_ISR
mdefine_line|#define  MPT_MAX_REPLIES_PER_ISR&t;32
DECL|macro|MPT_MAX_FRAME_SIZE
mdefine_line|#define  MPT_MAX_FRAME_SIZE&t;&t;128
DECL|macro|MPT_REQ_SIZE
mdefine_line|#define  MPT_REQ_SIZE&t;&t;&t;128
DECL|macro|MPT_REPLY_SIZE
mdefine_line|#define  MPT_REPLY_SIZE&t;&t;&t;128
DECL|macro|MPT_SG_BUCKETS_PER_HUNK
mdefine_line|#define  MPT_SG_BUCKETS_PER_HUNK&t;1
macro_line|#ifdef MODULE
DECL|macro|MPT_REQ_DEPTH_RANGE_STR
mdefine_line|#define  MPT_REQ_DEPTH_RANGE_STR&t;__MODULE_STRING(MPT_MIN_REQ_DEPTH) &quot;-&quot; __MODULE_STRING(MPT_MAX_REQ_DEPTH)
DECL|macro|MPT_REPLY_DEPTH_RANGE_STR
mdefine_line|#define  MPT_REPLY_DEPTH_RANGE_STR&t;__MODULE_STRING(MPT_MIN_REPLY_DEPTH) &quot;-&quot; __MODULE_STRING(MPT_MAX_REPLY_DEPTH)
DECL|macro|MPT_REPLY_SIZE_RANGE_STR
mdefine_line|#define  MPT_REPLY_SIZE_RANGE_STR&t;__MODULE_STRING(MPT_MIN_REPLY_SIZE) &quot;-&quot; __MODULE_STRING(MPT_MAX_FRAME_SIZE)
macro_line|#endif
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
DECL|member|argp1
r_void
op_star
id|argp1
suffix:semicolon
DECL|member|linkage
)brace
id|linkage
suffix:semicolon
multiline_comment|/*&n;&t; * NOTE: On non-32-bit systems, where pointers are LARGE,&n;&t; * using the linkage pointers destroys our sacred MsgContext&n;&t; * field contents.  But we don&squot;t care anymore because these&n;&t; * are now reset in mpt_put_msg_frame() just prior to sending&n;&t; * a request off to the IOC.&n;&t; */
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
multiline_comment|/*&n; *  Chip-specific stuff...&n; */
r_typedef
r_enum
(brace
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
DECL|member|Reserved1
id|u32
id|Reserved1
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 10-2F  reserved for future use    */
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
multiline_comment|/* Unique adapter id {0,1,2,...} */
DECL|member|pci_irq
r_int
id|pci_irq
suffix:semicolon
DECL|member|facts0
id|IOCFactsReply_t
id|facts0
suffix:semicolon
DECL|member|factsN
id|IOCFactsReply_t
id|factsN
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* &quot;iocN&quot;             */
DECL|member|prod_name
r_char
op_star
id|prod_name
suffix:semicolon
multiline_comment|/* &quot;LSIFC9x9&quot;         */
DECL|member|mem_phys
id|u32
id|mem_phys
suffix:semicolon
multiline_comment|/* == f4020000 (mmap) */
DECL|member|chip
r_volatile
id|SYSIF_REGS
op_star
id|chip
suffix:semicolon
multiline_comment|/* == c8817000 (mmap) */
DECL|member|chip_type
id|CHIP_TYPE
id|chip_type
suffix:semicolon
DECL|member|mem_size
r_int
id|mem_size
suffix:semicolon
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
DECL|member|sod_reset
r_int
id|sod_reset
suffix:semicolon
DECL|member|last_kickstart
r_int
r_int
id|last_kickstart
suffix:semicolon
DECL|member|pfacts0
id|PortFactsReply_t
id|pfacts0
suffix:semicolon
DECL|member|pfactsN
id|PortFactsReply_t
id|pfactsN
suffix:semicolon
DECL|member|lan_cnfg_page0
id|LANPage0_t
id|lan_cnfg_page0
suffix:semicolon
DECL|member|lan_cnfg_page1
id|LANPage1_t
id|lan_cnfg_page1
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
multiline_comment|/* Reply frames - rounded up! */
DECL|member|reply_frames_dma
id|dma_addr_t
id|reply_frames_dma
suffix:semicolon
DECL|member|reply_depth
r_int
id|reply_depth
suffix:semicolon
DECL|member|reply_sz
r_int
id|reply_sz
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
multiline_comment|/* Request msg frames for PULL mode! */
DECL|member|req_frames_dma
id|dma_addr_t
id|req_frames_dma
suffix:semicolon
DECL|member|req_depth
r_int
id|req_depth
suffix:semicolon
DECL|member|req_sz
r_int
id|req_sz
suffix:semicolon
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
DECL|member|hs_reply_idx
r_int
id|hs_reply_idx
suffix:semicolon
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
DECL|member|pcidev
r_struct
id|pci_dev
op_star
id|pcidev
suffix:semicolon
DECL|member|alt_ioc
r_struct
id|_MPT_ADAPTER
op_star
id|alt_ioc
suffix:semicolon
multiline_comment|/*&t;atomic_t&t;&t; userCnt;&t;*/
DECL|member|memmap
id|u8
op_star
id|memmap
suffix:semicolon
DECL|member|mtrr_reg
r_int
id|mtrr_reg
suffix:semicolon
DECL|member|sh
r_struct
id|Scsi_Host
op_star
id|sh
suffix:semicolon
DECL|member|ioc_dentry
r_struct
id|proc_dir_entry
op_star
id|ioc_dentry
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
multiline_comment|/*&n; *  Fibre Channel (SCSI) target device...&n; */
DECL|struct|_FC_TARGET
r_typedef
r_struct
id|_FC_TARGET
(brace
DECL|member|forw
r_struct
id|_FC_TARGET
op_star
id|forw
suffix:semicolon
DECL|member|back
r_struct
id|_FC_TARGET
op_star
id|back
suffix:semicolon
DECL|member|bus_id
r_int
id|bus_id
suffix:semicolon
DECL|member|target_id
r_int
id|target_id
suffix:semicolon
DECL|member|lun_exists
r_int
id|lun_exists
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|inquiry_data
id|u8
id|inquiry_data
(braket
l_int|36
)braket
suffix:semicolon
DECL|member|last_sense
id|u8
id|last_sense
(braket
l_int|256
)braket
suffix:semicolon
DECL|typedef|FC_TARGET
)brace
id|FC_TARGET
suffix:semicolon
DECL|struct|_FCDEV_TRACKER
r_typedef
r_struct
id|_FCDEV_TRACKER
(brace
DECL|member|head
id|FC_TARGET
op_star
id|head
suffix:semicolon
DECL|member|tail
id|FC_TARGET
op_star
id|tail
suffix:semicolon
DECL|typedef|FCDEV_TRACKER
)brace
id|FCDEV_TRACKER
suffix:semicolon
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
macro_line|#if defined(MPT_DEBUG) || defined(MPT_DEBUG_MSG_FRAME)
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
macro_line|#ifdef MPT_DEBUG_EVENTS
DECL|macro|deventprintk
mdefine_line|#define deventprintk(x)  printk x
macro_line|#else
DECL|macro|deventprintk
mdefine_line|#define deventprintk(x)
macro_line|#endif
macro_line|#ifdef MPT_DEBUG_SPINLOCK
DECL|macro|dslprintk
mdefine_line|#define dslprintk(x)  printk x
macro_line|#else
DECL|macro|dslprintk
mdefine_line|#define dslprintk(x)
macro_line|#endif
macro_line|#ifdef MPT_DEBUG_SG
DECL|macro|dsgprintk
mdefine_line|#define dsgprintk(x)  printk x
macro_line|#else
DECL|macro|dsgprintk
mdefine_line|#define dsgprintk(x)
macro_line|#endif
DECL|macro|MPT_INDEX_2_MFPTR
mdefine_line|#define MPT_INDEX_2_MFPTR(ioc,idx) &bslash;&n;&t;(MPT_FRAME_HDR*)( (u8*)(ioc)-&gt;req_frames + (ioc)-&gt;req_sz * (idx) )
DECL|macro|MFPTR_2_MPT_INDEX
mdefine_line|#define MFPTR_2_MPT_INDEX(ioc,mf) &bslash;&n;&t;(int)( ((u8*)mf - (u8*)(ioc)-&gt;req_frames) / (ioc)-&gt;req_sz )
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
macro_line|#endif&t;&t;/* } __KERNEL__ */
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *  MPT Control IOCTLs and structures&n; */
DECL|macro|MPT_MAGIC_NUMBER
mdefine_line|#define MPT_MAGIC_NUMBER&t;&squot;m&squot;
DECL|macro|MPTRWPERF
mdefine_line|#define MPTRWPERF&t;&t;_IOWR(MPT_MAGIC_NUMBER,0,struct mpt_raw_r_w)
DECL|macro|MPTRWPERF_CHK
mdefine_line|#define MPTRWPERF_CHK&t;&t;_IOR(MPT_MAGIC_NUMBER,13,struct mpt_raw_r_w)
DECL|macro|MPTRWPERF_RESET
mdefine_line|#define MPTRWPERF_RESET&t;&t;_IOR(MPT_MAGIC_NUMBER,14,struct mpt_raw_r_w)
DECL|macro|MPTFWDOWNLOAD
mdefine_line|#define MPTFWDOWNLOAD&t;&t;_IOWR(MPT_MAGIC_NUMBER,15,struct mpt_fw_xfer)
DECL|macro|MPTSCSICMD
mdefine_line|#define MPTSCSICMD&t;&t;_IOWR(MPT_MAGIC_NUMBER,16,struct mpt_scsi_cmd)
multiline_comment|/*&n; *  Define something *vague* enough that caller doesn&squot;t&n; *  really need to know anything about device parameters&n; *  (blk_size, capacity, etc.)&n; */
DECL|struct|mpt_raw_r_w
r_struct
id|mpt_raw_r_w
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
DECL|member|target
r_int
r_int
id|target
suffix:semicolon
multiline_comment|/* SCSI Target */
DECL|member|lun
r_int
r_int
id|lun
suffix:semicolon
multiline_comment|/* SCSI LUN */
DECL|member|iters
r_int
r_int
id|iters
suffix:semicolon
multiline_comment|/* N iterations */
DECL|member|nblks
r_int
r_int
id|nblks
suffix:semicolon
multiline_comment|/* number of blocks per IO */
DECL|member|qdepth
r_int
r_int
id|qdepth
suffix:semicolon
multiline_comment|/* max Q depth on this device */
DECL|member|range
r_int
r_char
id|range
suffix:semicolon
multiline_comment|/* 0-100% of FULL disk capacity, 0=use (nblks X iters) */
DECL|member|skip
r_int
r_char
id|skip
suffix:semicolon
multiline_comment|/* % of disk to skip */
DECL|member|rdwr
r_int
r_char
id|rdwr
suffix:semicolon
multiline_comment|/* 0-100%, 0=pure ReaDs, 100=pure WRites */
DECL|member|seqran
r_int
r_char
id|seqran
suffix:semicolon
multiline_comment|/* 0-100%, 0=pure SEQential, 100=pure RANdom */
DECL|member|cache_sz
r_int
r_int
id|cache_sz
suffix:semicolon
multiline_comment|/* In Kb!  Optimize hits to N Kb cache size */
)brace
suffix:semicolon
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
multiline_comment|/*&t;u8&t;&t; flags;*/
multiline_comment|/* Message flags - bit field */
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
DECL|struct|mpt_scsi_cmd
r_struct
id|mpt_scsi_cmd
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
DECL|member|target
r_int
r_int
id|target
suffix:semicolon
multiline_comment|/* SCSI Target */
DECL|member|lun
r_int
r_int
id|lun
suffix:semicolon
multiline_comment|/* SCSI LUN */
DECL|member|scsi_req
id|SCSIIORequest_t
id|scsi_req
suffix:semicolon
DECL|member|scsi_reply
id|SCSIIOReply_t
id|scsi_reply
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mpt_ioctl_sanity
r_struct
id|mpt_ioctl_sanity
(brace
DECL|member|iocnum
r_int
r_int
id|iocnum
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__&t;/* { */
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
id|mpt_register_ascqops_strings
c_func
(paren
multiline_comment|/*ASCQ_Table_t*/
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
)paren
suffix:semicolon
r_extern
r_void
id|mpt_print_ioc_facts
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
)paren
suffix:semicolon
multiline_comment|/*&n; *  Public data decl&squot;s...&n; */
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
macro_line|#if defined(__alpha__) || defined(__sparc_v9__)
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
multiline_comment|/*}-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#endif
eof
