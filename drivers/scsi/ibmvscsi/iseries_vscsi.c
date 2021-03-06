multiline_comment|/* ------------------------------------------------------------&n; * iSeries_vscsi.c&n; * (C) Copyright IBM Corporation 1994, 2003&n; * Authors: Colin DeVilbiss (devilbis@us.ibm.com)&n; *          Santiago Leon (santil@us.ibm.com)&n; *          Dave Boutcher (sleddog@us.ibm.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307&n; * USA&n; *&n; * ------------------------------------------------------------&n; * iSeries-specific functions of the SCSI host adapter for Virtual I/O devices&n; *&n; * This driver allows the Linux SCSI peripheral drivers to directly&n; * access devices in the hosting partition, either on an iSeries&n; * hypervisor system or a converged hypervisor system.&n; */
macro_line|#include &lt;asm/iSeries/vio.h&gt;
macro_line|#include &lt;asm/iSeries/HvLpEvent.h&gt;
macro_line|#include &lt;asm/iSeries/HvTypes.h&gt;
macro_line|#include &lt;asm/iSeries/HvLpConfig.h&gt;
macro_line|#include &lt;asm/vio.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &quot;ibmvscsi.h&quot;
multiline_comment|/* global variables */
DECL|variable|single_host_data
r_static
r_struct
id|ibmvscsi_host_data
op_star
id|single_host_data
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------&n; * Routines for direct interpartition interaction&n; */
DECL|struct|srp_lp_event
r_struct
id|srp_lp_event
(brace
DECL|member|lpevt
r_struct
id|HvLpEvent
id|lpevt
suffix:semicolon
multiline_comment|/* 0x00-0x17          */
DECL|member|reserved1
id|u32
id|reserved1
suffix:semicolon
multiline_comment|/* 0x18-0x1B; unused  */
DECL|member|version
id|u16
id|version
suffix:semicolon
multiline_comment|/* 0x1C-0x1D; unused  */
DECL|member|subtype_rc
id|u16
id|subtype_rc
suffix:semicolon
multiline_comment|/* 0x1E-0x1F; unused  */
DECL|member|crq
r_struct
id|viosrp_crq
id|crq
suffix:semicolon
multiline_comment|/* 0x20-0x3F          */
)brace
suffix:semicolon
multiline_comment|/** &n; * standard interface for handling logical partition events.&n; */
DECL|function|ibmvscsi_handle_event
r_static
r_void
id|ibmvscsi_handle_event
c_func
(paren
r_struct
id|HvLpEvent
op_star
id|lpevt
)paren
(brace
r_struct
id|srp_lp_event
op_star
id|evt
op_assign
(paren
r_struct
id|srp_lp_event
op_star
)paren
id|lpevt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|evt
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ibmvscsi: received null event&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|single_host_data
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ibmvscsi: received event, no adapter present&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ibmvscsi_handle_crq
c_func
(paren
op_amp
id|evt-&gt;crq
comma
id|single_host_data
)paren
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------&n; * Routines for driver initialization&n; */
DECL|function|ibmvscsi_init_crq_queue
r_int
id|ibmvscsi_init_crq_queue
c_func
(paren
r_struct
id|crq_queue
op_star
id|queue
comma
r_struct
id|ibmvscsi_host_data
op_star
id|hostdata
comma
r_int
id|max_requests
)paren
(brace
r_int
id|rc
suffix:semicolon
id|single_host_data
op_assign
id|hostdata
suffix:semicolon
id|rc
op_assign
id|viopath_open
c_func
(paren
id|viopath_hostLp
comma
id|viomajorsubtype_scsi
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;viopath_open failed with rc %d in open_event_path&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_goto
id|viopath_open_failed
suffix:semicolon
)brace
id|rc
op_assign
id|vio_setHandler
c_func
(paren
id|viomajorsubtype_scsi
comma
id|ibmvscsi_handle_event
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;vio_setHandler failed with rc %d in open_event_path&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_goto
id|vio_setHandler_failed
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|vio_setHandler_failed
suffix:colon
id|viopath_close
c_func
(paren
id|viopath_hostLp
comma
id|viomajorsubtype_scsi
comma
id|max_requests
)paren
suffix:semicolon
id|viopath_open_failed
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|ibmvscsi_release_crq_queue
r_void
id|ibmvscsi_release_crq_queue
c_func
(paren
r_struct
id|crq_queue
op_star
id|queue
comma
r_struct
id|ibmvscsi_host_data
op_star
id|hostdata
comma
r_int
id|max_requests
)paren
(brace
id|vio_clearHandler
c_func
(paren
id|viomajorsubtype_scsi
)paren
suffix:semicolon
id|viopath_close
c_func
(paren
id|viopath_hostLp
comma
id|viomajorsubtype_scsi
comma
id|max_requests
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * reset_crq_queue: - resets a crq after a failure&n; * @queue:&t;crq_queue to initialize and register&n; * @hostdata:&t;ibmvscsi_host_data of host&n; *&n; * no-op for iSeries&n; */
DECL|function|ibmvscsi_reset_crq_queue
r_void
id|ibmvscsi_reset_crq_queue
c_func
(paren
r_struct
id|crq_queue
op_star
id|queue
comma
r_struct
id|ibmvscsi_host_data
op_star
id|hostdata
)paren
(brace
)brace
multiline_comment|/**&n; * ibmvscsi_send_crq: - Send a CRQ&n; * @hostdata:&t;the adapter&n; * @word1:&t;the first 64 bits of the data&n; * @word2:&t;the second 64 bits of the data&n; */
DECL|function|ibmvscsi_send_crq
r_int
id|ibmvscsi_send_crq
c_func
(paren
r_struct
id|ibmvscsi_host_data
op_star
id|hostdata
comma
id|u64
id|word1
comma
id|u64
id|word2
)paren
(brace
id|single_host_data
op_assign
id|hostdata
suffix:semicolon
r_return
id|HvCallEvent_signalLpEventFast
c_func
(paren
id|viopath_hostLp
comma
id|HvLpEvent_Type_VirtualIo
comma
id|viomajorsubtype_scsi
comma
id|HvLpEvent_AckInd_NoAck
comma
id|HvLpEvent_AckType_ImmediateAck
comma
id|viopath_sourceinst
c_func
(paren
id|viopath_hostLp
)paren
comma
id|viopath_targetinst
c_func
(paren
id|viopath_hostLp
)paren
comma
l_int|0
comma
id|VIOVERSION
op_lshift
l_int|16
comma
id|word1
comma
id|word2
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
eof
