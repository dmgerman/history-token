multiline_comment|/*&n; *  linux/drivers/message/fusion/mptscsih.h&n; *      High performance SCSI / Fibre Channel SCSI Host device driver.&n; *      For use with PCI chip/adapter(s):&n; *          LSIFC9xx/LSI409xx Fibre Channel&n; *      running LSI Logic Fusion MPT (Message Passing Technology) firmware.&n; *&n; *  Credits:&n; *      This driver would not exist if not for Alan Cox&squot;s development&n; *      of the linux i2o driver.&n; *&n; *      A huge debt of gratitude is owed to David S. Miller (DaveM)&n; *      for fixing much of the stupid and broken stuff in the early&n; *      driver while porting to sparc64 platform.  THANK YOU!&n; *&n; *      (see also mptbase.c)&n; *&n; *  Copyright (c) 1999-2001 LSI Logic Corporation&n; *  Originally By: Steven J. Ralston&n; *  (mailto:Steve.Ralston@lsil.com)&n; *&n; *  $Id: mptscsih.h,v 1.7 2001/01/11 16:56:43 sralston Exp $&n; */
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; version 2 of the License.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    NO WARRANTY&n;    THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR&n;    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT&n;    LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,&n;    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is&n;    solely responsible for determining the appropriateness of using and&n;    distributing the Program and assumes all risks associated with its&n;    exercise of rights under this Agreement, including but not limited to&n;    the risks and costs of program errors, damage to or loss of data,&n;    programs or equipment, and unavailability or interruption of operations.&n;&n;    DISCLAIMER OF LIABILITY&n;    NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY&n;    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;    DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND&n;    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n;    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n;    USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED&n;    HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#ifndef SCSIHOST_H_INCLUDED
DECL|macro|SCSIHOST_H_INCLUDED
mdefine_line|#define SCSIHOST_H_INCLUDED
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#include &quot;linux/version.h&quot;
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *&t;SCSI Public stuff...&n; */
macro_line|#ifdef __sparc__
DECL|macro|MPT_SCSI_CAN_QUEUE
mdefine_line|#define MPT_SCSI_CAN_QUEUE&t;63
DECL|macro|MPT_SCSI_CMD_PER_LUN
mdefine_line|#define MPT_SCSI_CMD_PER_LUN&t;63
multiline_comment|/* FIXME!  Still investigating qd=64 hang on sparc64... */
macro_line|#else
DECL|macro|MPT_SCSI_CAN_QUEUE
mdefine_line|#define MPT_SCSI_CAN_QUEUE&t;64
DECL|macro|MPT_SCSI_CMD_PER_LUN
mdefine_line|#define MPT_SCSI_CMD_PER_LUN&t;64
macro_line|#endif
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *&t;Various bits and pieces broke within the lk-2.4.0-testN series:-(&n; *&t;So here are various HACKS to work around them.&n; */
multiline_comment|/*&n; *&t;Conditionalizing with &quot;#ifdef MODULE/#endif&quot; around:&n; *&t;&t;static Scsi_Host_Template driver_template = XX;&n; *&t;&t;#include &lt;../../scsi/scsi_module.c&gt;&n; *&t;lines was REMOVED @ lk-2.4.0-test9&n; *&t;Issue discovered 20001213 by: sshirron&n; */
DECL|macro|MPT_SCSIHOST_NEED_ENTRY_EXIT_HOOKUPS
mdefine_line|#define MPT_SCSIHOST_NEED_ENTRY_EXIT_HOOKUPS&t;&t;&t;1
macro_line|#if LINUX_VERSION_CODE &lt;= KERNEL_VERSION(2,4,0)
macro_line|#&t;if LINUX_VERSION_CODE == KERNEL_VERSION(2,4,0)
multiline_comment|/*&n;&t;&t; *&t;Super HACK!  -by sralston:-(&n;&t;&t; *&t;(good grief; heaven help me!)&n;&t;&t; */
macro_line|#&t;&t;include &lt;linux/capability.h&gt;
macro_line|#&t;&t;if !defined(CAP_LEASE) &amp;&amp; !defined(MODULE)
DECL|macro|MPT_SCSIHOST_NEED_ENTRY_EXIT_HOOKUPS
macro_line|#&t;&t;&t;undef MPT_SCSIHOST_NEED_ENTRY_EXIT_HOOKUPS
macro_line|#&t;&t;endif
macro_line|#&t;else
macro_line|#&t;&t;ifndef MODULE
DECL|macro|MPT_SCSIHOST_NEED_ENTRY_EXIT_HOOKUPS
macro_line|#&t;&t;&t;undef MPT_SCSIHOST_NEED_ENTRY_EXIT_HOOKUPS
macro_line|#&t;&t;endif
macro_line|#&t;endif
macro_line|#endif
multiline_comment|/*&n; *&t;tq_scheduler disappeared @ lk-2.4.0-test12&n; *&t;(right when &lt;linux/sched.h&gt; newly defined TQ_ACTIVE)&n; */
DECL|macro|HAVE_TQ_SCHED
mdefine_line|#define HAVE_TQ_SCHED&t;1
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,4,0)
macro_line|#&t;include &lt;linux/sched.h&gt;
macro_line|#&t;ifdef TQ_ACTIVE
DECL|macro|HAVE_TQ_SCHED
macro_line|#&t;&t;undef HAVE_TQ_SCHED
macro_line|#&t;endif
macro_line|#endif
macro_line|#ifdef HAVE_TQ_SCHED
DECL|macro|SCHEDULE_TASK
mdefine_line|#define SCHEDULE_TASK(x)&t;&t;&bslash;&n;&t;/*MOD_INC_USE_COUNT*/;&t;&t;&bslash;&n;&t;(x)-&gt;next = NULL;&t;&t;&bslash;&n;&t;queue_task(x, &amp;tq_scheduler)
macro_line|#else
DECL|macro|SCHEDULE_TASK
mdefine_line|#define SCHEDULE_TASK(x)&t;&t;&bslash;&n;&t;/*MOD_INC_USE_COUNT*/;&t;&t;&bslash;&n;&t;if (schedule_task(x) == 0) {&t;&bslash;&n;&t;&t;/*MOD_DEC_USE_COUNT*/;&t;&bslash;&n;&t;}
macro_line|#endif
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
DECL|macro|x_scsi_detect
mdefine_line|#define x_scsi_detect&t;&t;mptscsih_detect
DECL|macro|x_scsi_release
mdefine_line|#define x_scsi_release&t;&t;mptscsih_release
DECL|macro|x_scsi_info
mdefine_line|#define x_scsi_info&t;&t;mptscsih_info
DECL|macro|x_scsi_queuecommand
mdefine_line|#define x_scsi_queuecommand&t;mptscsih_qcmd
DECL|macro|x_scsi_abort
mdefine_line|#define x_scsi_abort&t;&t;mptscsih_abort
DECL|macro|x_scsi_bus_reset
mdefine_line|#define x_scsi_bus_reset&t;mptscsih_bus_reset
DECL|macro|x_scsi_dev_reset
mdefine_line|#define x_scsi_dev_reset&t;mptscsih_dev_reset
DECL|macro|x_scsi_host_reset
mdefine_line|#define x_scsi_host_reset&t;mptscsih_host_reset
DECL|macro|x_scsi_bios_param
mdefine_line|#define x_scsi_bios_param&t;mptscsih_bios_param
DECL|macro|x_scsi_taskmgmt_bh
mdefine_line|#define x_scsi_taskmgmt_bh&t;mptscsih_taskmgmt_bh
DECL|macro|x_scsi_old_abort
mdefine_line|#define x_scsi_old_abort&t;mptscsih_old_abort
DECL|macro|x_scsi_old_reset
mdefine_line|#define x_scsi_old_reset&t;mptscsih_old_reset
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*&n; *&t;MPT SCSI Host / Initiator decls...&n; */
r_extern
r_int
id|x_scsi_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|x_scsi_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|x_scsi_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
multiline_comment|/*extern&t;int&t;&t; x_scsi_command(Scsi_Cmnd *);*/
r_extern
r_int
id|x_scsi_queuecommand
c_func
(paren
id|Scsi_Cmnd
op_star
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
macro_line|#ifdef MPT_SCSI_USE_NEW_EH
r_extern
r_int
id|x_scsi_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|x_scsi_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|x_scsi_dev_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
multiline_comment|/*extern&t;int&t;&t; x_scsi_host_reset(Scsi_Cmnd *);*/
macro_line|#else
r_extern
r_int
id|x_scsi_old_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|x_scsi_old_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|x_scsi_bios_param
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|x_scsi_taskmgmt_bh
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0)
DECL|macro|PROC_SCSI_DECL
mdefine_line|#define PROC_SCSI_DECL
macro_line|#else
DECL|macro|PROC_SCSI_DECL
mdefine_line|#define PROC_SCSI_DECL  proc_name: &quot;mptscsih&quot;,
macro_line|#endif
macro_line|#ifdef MPT_SCSI_USE_NEW_EH
DECL|macro|MPT_SCSIHOST
mdefine_line|#define MPT_SCSIHOST {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;next:&t;&t;&t;&t;NULL,&t;&t;&t;&bslash;&n;&t;PROC_SCSI_DECL&t;&t;&t;&t;&t;&t;&bslash;&n;&t;name:&t;&t;&t;&t;&quot;MPT SCSI Host&quot;,&t;&bslash;&n;&t;detect:&t;&t;&t;&t;x_scsi_detect,&t;&t;&bslash;&n;&t;release:&t;&t;&t;x_scsi_release,&t;&t;&bslash;&n;&t;info:&t;&t;&t;&t;x_scsi_info,&t;&t;&bslash;&n;&t;command:&t;&t;&t;NULL,&t;&t;&t;&bslash;&n;&t;queuecommand:&t;&t;&t;x_scsi_queuecommand,&t;&bslash;&n;&t;eh_strategy_handler:&t;&t;NULL,&t;&t;&t;&bslash;&n;&t;eh_abort_handler:&t;&t;x_scsi_abort,&t;&t;&bslash;&n;&t;eh_device_reset_handler:&t;x_scsi_dev_reset,&t;&bslash;&n;&t;eh_bus_reset_handler:&t;&t;x_scsi_bus_reset,&t;&bslash;&n;&t;eh_host_reset_handler:&t;&t;NULL,&t;&t;&t;&bslash;&n;&t;bios_param:&t;&t;&t;x_scsi_bios_param,&t;&bslash;&n;&t;can_queue:&t;&t;&t;MPT_SCSI_CAN_QUEUE,&t;&bslash;&n;&t;this_id:&t;&t;&t;-1,&t;&t;&t;&bslash;&n;&t;sg_tablesize:&t;&t;&t;25,&t;&t;&t;&bslash;&n;&t;cmd_per_lun:&t;&t;&t;MPT_SCSI_CMD_PER_LUN,&t;&bslash;&n;&t;unchecked_isa_dma:&t;&t;0,&t;&t;&t;&bslash;&n;&t;use_clustering:&t;&t;&t;ENABLE_CLUSTERING,&t;&bslash;&n;&t;use_new_eh_code:&t;&t;1&t;&t;&t;&bslash;&n;}
macro_line|#else
DECL|macro|MPT_SCSIHOST
mdefine_line|#define MPT_SCSIHOST {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;next:&t;&t;&t;&t;NULL,&t;&t;&t;&bslash;&n;&t;PROC_SCSI_DECL&t;&t;&t;&t;&t;&t;&bslash;&n;&t;name:&t;&t;&t;&t;&quot;MPT SCSI Host&quot;,&t;&bslash;&n;&t;detect:&t;&t;&t;&t;x_scsi_detect,&t;&t;&bslash;&n;&t;release:&t;&t;&t;x_scsi_release,&t;&t;&bslash;&n;&t;info:&t;&t;&t;&t;x_scsi_info,&t;&t;&bslash;&n;&t;command:&t;&t;&t;NULL,&t;&t;&t;&bslash;&n;&t;queuecommand:&t;&t;&t;x_scsi_queuecommand,&t;&bslash;&n;&t;abort:&t;&t;&t;&t;x_scsi_old_abort,&t;&bslash;&n;&t;reset:&t;&t;&t;&t;x_scsi_old_reset,&t;&bslash;&n;&t;bios_param:&t;&t;&t;x_scsi_bios_param,&t;&bslash;&n;&t;can_queue:&t;&t;&t;MPT_SCSI_CAN_QUEUE,&t;&bslash;&n;&t;this_id:&t;&t;&t;-1,&t;&t;&t;&bslash;&n;&t;sg_tablesize:&t;&t;&t;25,&t;&t;&t;&bslash;&n;&t;cmd_per_lun:&t;&t;&t;MPT_SCSI_CMD_PER_LUN,&t;&bslash;&n;&t;unchecked_isa_dma:&t;&t;0,&t;&t;&t;&bslash;&n;&t;use_clustering:&t;&t;&t;ENABLE_CLUSTERING&t;&bslash;&n;}
macro_line|#endif
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
multiline_comment|/*  include/scsi/scsi.h may not be quite complete...  */
macro_line|#ifndef RESERVE_10
DECL|macro|RESERVE_10
mdefine_line|#define RESERVE_10&t;&t;0x56
macro_line|#endif
macro_line|#ifndef RELEASE_10
DECL|macro|RELEASE_10
mdefine_line|#define RELEASE_10&t;&t;0x57
macro_line|#endif
macro_line|#ifndef PERSISTENT_RESERVE_IN
DECL|macro|PERSISTENT_RESERVE_IN
mdefine_line|#define PERSISTENT_RESERVE_IN&t;0x5e
macro_line|#endif
macro_line|#ifndef PERSISTENT_RESERVE_OUT
DECL|macro|PERSISTENT_RESERVE_OUT
mdefine_line|#define PERSISTENT_RESERVE_OUT&t;0x5f
macro_line|#endif
multiline_comment|/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
macro_line|#endif
eof
