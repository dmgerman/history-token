multiline_comment|/* &n; * ca.h&n; *&n; * Copyright (C) 2000 Ralph  Metzler &lt;ralph@convergence.de&gt;&n; *                  &amp; Marcus Metzler &lt;marcus@convergence.de&gt;&n;                      for convergence integrated media GmbH&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Lesser Public License&n; * as published by the Free Software Foundation; either version 2.1&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU Lesser General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; */
macro_line|#ifndef _DVBCA_H_
DECL|macro|_DVBCA_H_
mdefine_line|#define _DVBCA_H_
multiline_comment|/* slot interface types and info */
DECL|struct|ca_slot_info
r_typedef
r_struct
id|ca_slot_info
(brace
DECL|member|num
r_int
id|num
suffix:semicolon
multiline_comment|/* slot number */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* CA interface this slot supports */
DECL|macro|CA_CI
mdefine_line|#define CA_CI            1     /* CI high level interface */
DECL|macro|CA_CI_LINK
mdefine_line|#define CA_CI_LINK       2     /* CI link layer level interface */
DECL|macro|CA_CI_PHYS
mdefine_line|#define CA_CI_PHYS       4     /* CI physical layer level interface */
DECL|macro|CA_DESCR
mdefine_line|#define CA_DESCR         8     /* built-in descrambler */
DECL|macro|CA_SC
mdefine_line|#define CA_SC          128     /* simple smart card interface */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|macro|CA_CI_MODULE_PRESENT
mdefine_line|#define CA_CI_MODULE_PRESENT 1 /* module (or card) inserted */
DECL|macro|CA_CI_MODULE_READY
mdefine_line|#define CA_CI_MODULE_READY   2
DECL|typedef|ca_slot_info_t
)brace
id|ca_slot_info_t
suffix:semicolon
multiline_comment|/* descrambler types and info */
DECL|struct|ca_descr_info
r_typedef
r_struct
id|ca_descr_info
(brace
DECL|member|num
r_int
r_int
id|num
suffix:semicolon
multiline_comment|/* number of available descramblers (keys) */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* type of supported scrambling system */
DECL|macro|CA_ECD
mdefine_line|#define CA_ECD           1
DECL|macro|CA_NDS
mdefine_line|#define CA_NDS           2
DECL|macro|CA_DSS
mdefine_line|#define CA_DSS           4
DECL|typedef|ca_descr_info_t
)brace
id|ca_descr_info_t
suffix:semicolon
DECL|struct|ca_caps
r_typedef
r_struct
id|ca_caps
(brace
DECL|member|slot_num
r_int
r_int
id|slot_num
suffix:semicolon
multiline_comment|/* total number of CA card and module slots */
DECL|member|slot_type
r_int
r_int
id|slot_type
suffix:semicolon
multiline_comment|/* OR of all supported types */
DECL|member|descr_num
r_int
r_int
id|descr_num
suffix:semicolon
multiline_comment|/* total number of descrambler slots (keys) */
DECL|member|descr_type
r_int
r_int
id|descr_type
suffix:semicolon
multiline_comment|/* OR of all supported types */
DECL|typedef|ca_caps_t
)brace
id|ca_caps_t
suffix:semicolon
multiline_comment|/* a message to/from a CI-CAM */
DECL|struct|ca_msg
r_typedef
r_struct
id|ca_msg
(brace
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|msg
r_int
r_char
id|msg
(braket
l_int|256
)braket
suffix:semicolon
DECL|typedef|ca_msg_t
)brace
id|ca_msg_t
suffix:semicolon
DECL|struct|ca_descr
r_typedef
r_struct
id|ca_descr
(brace
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
DECL|member|parity
r_int
r_int
id|parity
suffix:semicolon
multiline_comment|/* 0 == even, 1 == odd */
DECL|member|cw
r_int
r_char
id|cw
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|ca_descr_t
)brace
id|ca_descr_t
suffix:semicolon
DECL|struct|ca_pid
r_typedef
r_struct
id|ca_pid
(brace
DECL|member|pid
r_int
r_int
id|pid
suffix:semicolon
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* -1 == disable*/
DECL|typedef|ca_pid_t
)brace
id|ca_pid_t
suffix:semicolon
DECL|macro|CA_RESET
mdefine_line|#define CA_RESET          _IO(&squot;o&squot;, 128)
DECL|macro|CA_GET_CAP
mdefine_line|#define CA_GET_CAP        _IOR(&squot;o&squot;, 129, ca_caps_t)
DECL|macro|CA_GET_SLOT_INFO
mdefine_line|#define CA_GET_SLOT_INFO  _IOR(&squot;o&squot;, 130, ca_slot_info_t)
DECL|macro|CA_GET_DESCR_INFO
mdefine_line|#define CA_GET_DESCR_INFO _IOR(&squot;o&squot;, 131, ca_descr_info_t)
DECL|macro|CA_GET_MSG
mdefine_line|#define CA_GET_MSG        _IOR(&squot;o&squot;, 132, ca_msg_t)
DECL|macro|CA_SEND_MSG
mdefine_line|#define CA_SEND_MSG       _IOW(&squot;o&squot;, 133, ca_msg_t)
DECL|macro|CA_SET_DESCR
mdefine_line|#define CA_SET_DESCR      _IOW(&squot;o&squot;, 134, ca_descr_t)
DECL|macro|CA_SET_PID
mdefine_line|#define CA_SET_PID        _IOW(&squot;o&squot;, 135, ca_pid_t)
macro_line|#endif
eof
