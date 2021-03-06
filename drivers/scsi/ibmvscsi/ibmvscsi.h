multiline_comment|/* ------------------------------------------------------------&n; * ibmvscsi.h&n; * (C) Copyright IBM Corporation 1994, 2003&n; * Authors: Colin DeVilbiss (devilbis@us.ibm.com)&n; *          Santiago Leon (santil@us.ibm.com)&n; *          Dave Boutcher (sleddog@us.ibm.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307&n; * USA&n; *&n; * ------------------------------------------------------------&n; * Emulation of a SCSI host adapter for Virtual I/O devices&n; *&n; * This driver allows the Linux SCSI peripheral drivers to directly&n; * access devices in the hosting partition, either on an iSeries&n; * hypervisor system or a converged hypervisor system.&n; */
macro_line|#ifndef IBMVSCSI_H
DECL|macro|IBMVSCSI_H
mdefine_line|#define IBMVSCSI_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;viosrp.h&quot;
r_struct
id|scsi_cmnd
suffix:semicolon
r_struct
id|Scsi_Host
suffix:semicolon
multiline_comment|/* Number of indirect bufs...the list of these has to fit in the&n; * additional data of the srp_cmd struct along with the indirect&n; * descriptor&n; */
DECL|macro|MAX_INDIRECT_BUFS
mdefine_line|#define MAX_INDIRECT_BUFS 10
multiline_comment|/* ------------------------------------------------------------&n; * Data Structures&n; */
multiline_comment|/* an RPA command/response transport queue */
DECL|struct|crq_queue
r_struct
id|crq_queue
(brace
DECL|member|msgs
r_struct
id|viosrp_crq
op_star
id|msgs
suffix:semicolon
DECL|member|size
DECL|member|cur
r_int
id|size
comma
id|cur
suffix:semicolon
DECL|member|msg_token
id|dma_addr_t
id|msg_token
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* a unit of work for the hosting partition */
DECL|struct|srp_event_struct
r_struct
id|srp_event_struct
(brace
DECL|member|xfer_iu
r_union
id|viosrp_iu
op_star
id|xfer_iu
suffix:semicolon
DECL|member|cmnd
r_struct
id|scsi_cmnd
op_star
id|cmnd
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|srp_event_struct
op_star
)paren
suffix:semicolon
DECL|member|crq
r_struct
id|viosrp_crq
id|crq
suffix:semicolon
DECL|member|hostdata
r_struct
id|ibmvscsi_host_data
op_star
id|hostdata
suffix:semicolon
DECL|member|free
id|atomic_t
id|free
suffix:semicolon
DECL|member|iu
r_union
id|viosrp_iu
id|iu
suffix:semicolon
DECL|member|cmnd_done
r_void
(paren
op_star
id|cmnd_done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
DECL|member|comp
r_struct
id|completion
id|comp
suffix:semicolon
DECL|member|sync_srp
r_union
id|viosrp_iu
op_star
id|sync_srp
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* a pool of event structs for use */
DECL|struct|event_pool
r_struct
id|event_pool
(brace
DECL|member|events
r_struct
id|srp_event_struct
op_star
id|events
suffix:semicolon
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|next
r_int
id|next
suffix:semicolon
DECL|member|iu_storage
r_union
id|viosrp_iu
op_star
id|iu_storage
suffix:semicolon
DECL|member|iu_token
id|dma_addr_t
id|iu_token
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* all driver data associated with a host adapter */
DECL|struct|ibmvscsi_host_data
r_struct
id|ibmvscsi_host_data
(brace
DECL|member|request_limit
id|atomic_t
id|request_limit
suffix:semicolon
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|pool
r_struct
id|event_pool
id|pool
suffix:semicolon
DECL|member|queue
r_struct
id|crq_queue
id|queue
suffix:semicolon
DECL|member|srp_task
r_struct
id|tasklet_struct
id|srp_task
suffix:semicolon
DECL|member|sent
r_struct
id|list_head
id|sent
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|madapter_info
r_struct
id|mad_adapter_info_data
id|madapter_info
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* routines for managing a command/response queue */
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
suffix:semicolon
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
suffix:semicolon
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
suffix:semicolon
r_void
id|ibmvscsi_handle_crq
c_func
(paren
r_struct
id|viosrp_crq
op_star
id|crq
comma
r_struct
id|ibmvscsi_host_data
op_star
id|hostdata
)paren
suffix:semicolon
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
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* IBMVSCSI_H */
eof
