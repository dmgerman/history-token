multiline_comment|/*&n; * dvb_ca.h: generic DVB functions for EN50221 CA interfaces&n; *&n; * Copyright (C) 2004 Andrew de Quincey&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU Lesser General Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&t; See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#ifndef _DVB_CA_EN50221_H_
DECL|macro|_DVB_CA_EN50221_H_
mdefine_line|#define _DVB_CA_EN50221_H_
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/dvb/ca.h&gt;
macro_line|#include &quot;dvbdev.h&quot;
DECL|macro|DVB_CA_EN50221_POLL_CAM_PRESENT
mdefine_line|#define DVB_CA_EN50221_POLL_CAM_PRESENT&t;1
DECL|macro|DVB_CA_EN50221_POLL_CAM_CHANGED
mdefine_line|#define DVB_CA_EN50221_POLL_CAM_CHANGED&t;2
DECL|macro|DVB_CA_EN50221_POLL_CAM_READY
mdefine_line|#define DVB_CA_EN50221_POLL_CAM_READY&t;&t;4
DECL|macro|DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE
mdefine_line|#define DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE&t;1
DECL|macro|DVB_CA_EN50221_FLAG_IRQ_FR
mdefine_line|#define DVB_CA_EN50221_FLAG_IRQ_FR&t;&t;2
DECL|macro|DVB_CA_EN50221_FLAG_IRQ_DA
mdefine_line|#define DVB_CA_EN50221_FLAG_IRQ_DA&t;&t;4
DECL|macro|DVB_CA_EN50221_CAMCHANGE_REMOVED
mdefine_line|#define DVB_CA_EN50221_CAMCHANGE_REMOVED&t;&t;0
DECL|macro|DVB_CA_EN50221_CAMCHANGE_INSERTED
mdefine_line|#define DVB_CA_EN50221_CAMCHANGE_INSERTED&t;&t;1
multiline_comment|/* Structure describing a CA interface */
DECL|struct|dvb_ca_en50221
r_struct
id|dvb_ca_en50221
(brace
multiline_comment|/* the module owning this structure */
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
multiline_comment|/* NOTE: the read_*, write_* and poll_slot_status functions must use locks as&n;&t; * they may be called from several threads at once */
multiline_comment|/* functions for accessing attribute memory on the CAM */
DECL|member|read_attribute_mem
r_int
(paren
op_star
id|read_attribute_mem
)paren
(paren
r_struct
id|dvb_ca_en50221
op_star
id|ca
comma
r_int
id|slot
comma
r_int
id|address
)paren
suffix:semicolon
DECL|member|write_attribute_mem
r_int
(paren
op_star
id|write_attribute_mem
)paren
(paren
r_struct
id|dvb_ca_en50221
op_star
id|ca
comma
r_int
id|slot
comma
r_int
id|address
comma
id|u8
id|value
)paren
suffix:semicolon
multiline_comment|/* functions for accessing the control interface on the CAM */
DECL|member|read_cam_control
r_int
(paren
op_star
id|read_cam_control
)paren
(paren
r_struct
id|dvb_ca_en50221
op_star
id|ca
comma
r_int
id|slot
comma
id|u8
id|address
)paren
suffix:semicolon
DECL|member|write_cam_control
r_int
(paren
op_star
id|write_cam_control
)paren
(paren
r_struct
id|dvb_ca_en50221
op_star
id|ca
comma
r_int
id|slot
comma
id|u8
id|address
comma
id|u8
id|value
)paren
suffix:semicolon
multiline_comment|/* Functions for controlling slots */
DECL|member|slot_reset
r_int
(paren
op_star
id|slot_reset
)paren
(paren
r_struct
id|dvb_ca_en50221
op_star
id|ca
comma
r_int
id|slot
)paren
suffix:semicolon
DECL|member|slot_shutdown
r_int
(paren
op_star
id|slot_shutdown
)paren
(paren
r_struct
id|dvb_ca_en50221
op_star
id|ca
comma
r_int
id|slot
)paren
suffix:semicolon
DECL|member|slot_ts_enable
r_int
(paren
op_star
id|slot_ts_enable
)paren
(paren
r_struct
id|dvb_ca_en50221
op_star
id|ca
comma
r_int
id|slot
)paren
suffix:semicolon
multiline_comment|/*&n;&t;* Poll slot status.&n;&t;* Only necessary if DVB_CA_FLAG_EN50221_IRQ_CAMCHANGE is not set&n;&t;*/
DECL|member|poll_slot_status
r_int
(paren
op_star
id|poll_slot_status
)paren
(paren
r_struct
id|dvb_ca_en50221
op_star
id|ca
comma
r_int
id|slot
comma
r_int
id|open
)paren
suffix:semicolon
multiline_comment|/* private data, used by caller */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* Opaque data used by the dvb_ca core. Do not modify! */
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ******************************************************************************** */
multiline_comment|/* Functions for reporting IRQ events */
multiline_comment|/**&n; * A CAMCHANGE IRQ has occurred.&n; *&n; * @param ca CA instance.&n; * @param slot Slot concerned.&n; * @param change_type One of the DVB_CA_CAMCHANGE_* values&n; */
r_void
id|dvb_ca_en50221_camchange_irq
c_func
(paren
r_struct
id|dvb_ca_en50221
op_star
id|pubca
comma
r_int
id|slot
comma
r_int
id|change_type
)paren
suffix:semicolon
multiline_comment|/**&n; * A CAMREADY IRQ has occurred.&n; *&n; * @param ca CA instance.&n; * @param slot Slot concerned.&n; */
r_void
id|dvb_ca_en50221_camready_irq
c_func
(paren
r_struct
id|dvb_ca_en50221
op_star
id|pubca
comma
r_int
id|slot
)paren
suffix:semicolon
multiline_comment|/**&n; * An FR or a DA IRQ has occurred.&n; *&n; * @param ca CA instance.&n; * @param slot Slot concerned.&n; */
r_void
id|dvb_ca_en50221_frda_irq
c_func
(paren
r_struct
id|dvb_ca_en50221
op_star
id|ca
comma
r_int
id|slot
)paren
suffix:semicolon
multiline_comment|/* ******************************************************************************** */
multiline_comment|/* Initialisation/shutdown functions */
multiline_comment|/**&n; * Initialise a new DVB CA device.&n; *&n; * @param dvb_adapter DVB adapter to attach the new CA device to.&n; * @param ca The dvb_ca instance.&n; * @param flags Flags describing the CA device (DVB_CA_EN50221_FLAG_*).&n; * @param slot_count Number of slots supported.&n; *&n; * @return 0 on success, nonzero on failure&n; */
r_extern
r_int
id|dvb_ca_en50221_init
c_func
(paren
r_struct
id|dvb_adapter
op_star
id|dvb_adapter
comma
r_struct
id|dvb_ca_en50221
op_star
id|ca
comma
r_int
id|flags
comma
r_int
id|slot_count
)paren
suffix:semicolon
multiline_comment|/**&n; * Release a DVB CA device.&n; *&n; * @param ca The associated dvb_ca instance.&n; */
r_extern
r_void
id|dvb_ca_en50221_release
c_func
(paren
r_struct
id|dvb_ca_en50221
op_star
id|ca
)paren
suffix:semicolon
macro_line|#endif
eof
