multiline_comment|/*&n; * Definitions for bulk memory services&n; *&n; * bulkmem.h 1.12 2000/06/12 21:55:41&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; * bulkmem.h 1.3 1995/05/27 04:49:49&n; */
macro_line|#ifndef _LINUX_BULKMEM_H
DECL|macro|_LINUX_BULKMEM_H
mdefine_line|#define _LINUX_BULKMEM_H
multiline_comment|/* For GetFirstRegion and GetNextRegion */
DECL|struct|region_info_t
r_typedef
r_struct
id|region_info_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|CardOffset
id|u_int
id|CardOffset
suffix:semicolon
DECL|member|RegionSize
id|u_int
id|RegionSize
suffix:semicolon
DECL|member|AccessSpeed
id|u_int
id|AccessSpeed
suffix:semicolon
DECL|member|BlockSize
id|u_int
id|BlockSize
suffix:semicolon
DECL|member|PartMultiple
id|u_int
id|PartMultiple
suffix:semicolon
DECL|member|JedecMfr
DECL|member|JedecInfo
id|u_char
id|JedecMfr
comma
id|JedecInfo
suffix:semicolon
DECL|member|next
id|memory_handle_t
id|next
suffix:semicolon
DECL|typedef|region_info_t
)brace
id|region_info_t
suffix:semicolon
DECL|macro|REGION_TYPE
mdefine_line|#define REGION_TYPE&t;&t;0x0001
DECL|macro|REGION_TYPE_CM
mdefine_line|#define REGION_TYPE_CM&t;&t;0x0000
DECL|macro|REGION_TYPE_AM
mdefine_line|#define REGION_TYPE_AM&t;&t;0x0001
DECL|macro|REGION_PREFETCH
mdefine_line|#define REGION_PREFETCH&t;&t;0x0008
DECL|macro|REGION_CACHEABLE
mdefine_line|#define REGION_CACHEABLE&t;0x0010
DECL|macro|REGION_BAR_MASK
mdefine_line|#define REGION_BAR_MASK&t;&t;0xe000
DECL|macro|REGION_BAR_SHIFT
mdefine_line|#define REGION_BAR_SHIFT&t;13
multiline_comment|/* For OpenMemory */
DECL|struct|open_mem_t
r_typedef
r_struct
id|open_mem_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|Offset
id|u_int
id|Offset
suffix:semicolon
DECL|typedef|open_mem_t
)brace
id|open_mem_t
suffix:semicolon
multiline_comment|/* Attributes for OpenMemory */
DECL|macro|MEMORY_TYPE
mdefine_line|#define MEMORY_TYPE&t;&t;0x0001
DECL|macro|MEMORY_TYPE_CM
mdefine_line|#define MEMORY_TYPE_CM&t;&t;0x0000
DECL|macro|MEMORY_TYPE_AM
mdefine_line|#define MEMORY_TYPE_AM&t;&t;0x0001
DECL|macro|MEMORY_EXCLUSIVE
mdefine_line|#define MEMORY_EXCLUSIVE&t;0x0002
DECL|macro|MEMORY_PREFETCH
mdefine_line|#define MEMORY_PREFETCH&t;&t;0x0008
DECL|macro|MEMORY_CACHEABLE
mdefine_line|#define MEMORY_CACHEABLE&t;0x0010
DECL|macro|MEMORY_BAR_MASK
mdefine_line|#define MEMORY_BAR_MASK&t;&t;0xe000
DECL|macro|MEMORY_BAR_SHIFT
mdefine_line|#define MEMORY_BAR_SHIFT&t;13
DECL|struct|eraseq_entry_t
r_typedef
r_struct
id|eraseq_entry_t
(brace
DECL|member|Handle
id|memory_handle_t
id|Handle
suffix:semicolon
DECL|member|State
id|u_char
id|State
suffix:semicolon
DECL|member|Size
id|u_int
id|Size
suffix:semicolon
DECL|member|Offset
id|u_int
id|Offset
suffix:semicolon
DECL|member|Optional
r_void
op_star
id|Optional
suffix:semicolon
DECL|typedef|eraseq_entry_t
)brace
id|eraseq_entry_t
suffix:semicolon
DECL|struct|eraseq_hdr_t
r_typedef
r_struct
id|eraseq_hdr_t
(brace
DECL|member|QueueEntryCnt
r_int
id|QueueEntryCnt
suffix:semicolon
DECL|member|QueueEntryArray
id|eraseq_entry_t
op_star
id|QueueEntryArray
suffix:semicolon
DECL|typedef|eraseq_hdr_t
)brace
id|eraseq_hdr_t
suffix:semicolon
DECL|macro|ERASE_QUEUED
mdefine_line|#define ERASE_QUEUED&t;&t;0x00
DECL|macro|ERASE_IN_PROGRESS
mdefine_line|#define ERASE_IN_PROGRESS(n)&t;(((n) &gt; 0) &amp;&amp; ((n) &lt; 0x80))
DECL|macro|ERASE_IDLE
mdefine_line|#define ERASE_IDLE&t;&t;0xff
DECL|macro|ERASE_PASSED
mdefine_line|#define ERASE_PASSED&t;&t;0xe0
DECL|macro|ERASE_FAILED
mdefine_line|#define ERASE_FAILED&t;&t;0xe1
DECL|macro|ERASE_MISSING
mdefine_line|#define ERASE_MISSING&t;&t;0x80
DECL|macro|ERASE_MEDIA_WRPROT
mdefine_line|#define ERASE_MEDIA_WRPROT&t;0x84
DECL|macro|ERASE_NOT_ERASABLE
mdefine_line|#define ERASE_NOT_ERASABLE&t;0x85
DECL|macro|ERASE_BAD_OFFSET
mdefine_line|#define ERASE_BAD_OFFSET&t;0xc1
DECL|macro|ERASE_BAD_TECH
mdefine_line|#define ERASE_BAD_TECH&t;&t;0xc2
DECL|macro|ERASE_BAD_SOCKET
mdefine_line|#define ERASE_BAD_SOCKET&t;0xc3
DECL|macro|ERASE_BAD_VCC
mdefine_line|#define ERASE_BAD_VCC&t;&t;0xc4
DECL|macro|ERASE_BAD_VPP
mdefine_line|#define ERASE_BAD_VPP&t;&t;0xc5
DECL|macro|ERASE_BAD_SIZE
mdefine_line|#define ERASE_BAD_SIZE&t;&t;0xc6
multiline_comment|/* For CopyMemory */
DECL|struct|copy_op_t
r_typedef
r_struct
id|copy_op_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|SourceOffset
id|u_int
id|SourceOffset
suffix:semicolon
DECL|member|DestOffset
id|u_int
id|DestOffset
suffix:semicolon
DECL|member|Count
id|u_int
id|Count
suffix:semicolon
DECL|typedef|copy_op_t
)brace
id|copy_op_t
suffix:semicolon
multiline_comment|/* For ReadMemory and WriteMemory */
DECL|struct|mem_op_t
r_typedef
r_struct
id|mem_op_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|Offset
id|u_int
id|Offset
suffix:semicolon
DECL|member|Count
id|u_int
id|Count
suffix:semicolon
DECL|typedef|mem_op_t
)brace
id|mem_op_t
suffix:semicolon
DECL|macro|MEM_OP_BUFFER
mdefine_line|#define MEM_OP_BUFFER&t;&t;0x01
DECL|macro|MEM_OP_BUFFER_USER
mdefine_line|#define MEM_OP_BUFFER_USER&t;0x00
DECL|macro|MEM_OP_BUFFER_KERNEL
mdefine_line|#define MEM_OP_BUFFER_KERNEL&t;0x01
DECL|macro|MEM_OP_DISABLE_ERASE
mdefine_line|#define MEM_OP_DISABLE_ERASE&t;0x02
DECL|macro|MEM_OP_VERIFY
mdefine_line|#define MEM_OP_VERIFY&t;&t;0x04
multiline_comment|/* For RegisterMTD */
DECL|struct|mtd_reg_t
r_typedef
r_struct
id|mtd_reg_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|Offset
id|u_int
id|Offset
suffix:semicolon
DECL|member|MediaID
id|u_long
id|MediaID
suffix:semicolon
DECL|typedef|mtd_reg_t
)brace
id|mtd_reg_t
suffix:semicolon
multiline_comment|/*&n; *  Definitions for MTD requests&n; */
DECL|struct|mtd_request_t
r_typedef
r_struct
id|mtd_request_t
(brace
DECL|member|SrcCardOffset
id|u_int
id|SrcCardOffset
suffix:semicolon
DECL|member|DestCardOffset
id|u_int
id|DestCardOffset
suffix:semicolon
DECL|member|TransferLength
id|u_int
id|TransferLength
suffix:semicolon
DECL|member|Function
id|u_int
id|Function
suffix:semicolon
DECL|member|MediaID
id|u_long
id|MediaID
suffix:semicolon
DECL|member|Status
id|u_int
id|Status
suffix:semicolon
DECL|member|Timeout
id|u_int
id|Timeout
suffix:semicolon
DECL|typedef|mtd_request_t
)brace
id|mtd_request_t
suffix:semicolon
multiline_comment|/* Fields in MTD Function */
DECL|macro|MTD_REQ_ACTION
mdefine_line|#define MTD_REQ_ACTION&t;&t;0x003
DECL|macro|MTD_REQ_ERASE
mdefine_line|#define MTD_REQ_ERASE&t;&t;0x000
DECL|macro|MTD_REQ_READ
mdefine_line|#define MTD_REQ_READ&t;&t;0x001
DECL|macro|MTD_REQ_WRITE
mdefine_line|#define MTD_REQ_WRITE&t;&t;0x002
DECL|macro|MTD_REQ_COPY
mdefine_line|#define MTD_REQ_COPY&t;&t;0x003
DECL|macro|MTD_REQ_NOERASE
mdefine_line|#define MTD_REQ_NOERASE&t;&t;0x004
DECL|macro|MTD_REQ_VERIFY
mdefine_line|#define MTD_REQ_VERIFY&t;&t;0x008
DECL|macro|MTD_REQ_READY
mdefine_line|#define MTD_REQ_READY&t;&t;0x010
DECL|macro|MTD_REQ_TIMEOUT
mdefine_line|#define MTD_REQ_TIMEOUT&t;&t;0x020
DECL|macro|MTD_REQ_LAST
mdefine_line|#define MTD_REQ_LAST&t;&t;0x040
DECL|macro|MTD_REQ_FIRST
mdefine_line|#define MTD_REQ_FIRST&t;&t;0x080
DECL|macro|MTD_REQ_KERNEL
mdefine_line|#define MTD_REQ_KERNEL&t;&t;0x100
multiline_comment|/* Status codes */
DECL|macro|MTD_WAITREQ
mdefine_line|#define MTD_WAITREQ&t;0x00
DECL|macro|MTD_WAITTIMER
mdefine_line|#define MTD_WAITTIMER&t;0x01
DECL|macro|MTD_WAITRDY
mdefine_line|#define MTD_WAITRDY&t;0x02
DECL|macro|MTD_WAITPOWER
mdefine_line|#define MTD_WAITPOWER&t;0x03
multiline_comment|/*&n; *  Definitions for MTD helper functions&n; */
multiline_comment|/* For MTDModifyWindow */
DECL|struct|mtd_mod_win_t
r_typedef
r_struct
id|mtd_mod_win_t
(brace
DECL|member|Attributes
id|u_int
id|Attributes
suffix:semicolon
DECL|member|AccessSpeed
id|u_int
id|AccessSpeed
suffix:semicolon
DECL|member|CardOffset
id|u_int
id|CardOffset
suffix:semicolon
DECL|typedef|mtd_mod_win_t
)brace
id|mtd_mod_win_t
suffix:semicolon
multiline_comment|/* For MTDSetVpp */
DECL|struct|mtd_vpp_req_t
r_typedef
r_struct
id|mtd_vpp_req_t
(brace
DECL|member|Vpp1
DECL|member|Vpp2
id|u_char
id|Vpp1
comma
id|Vpp2
suffix:semicolon
DECL|typedef|mtd_vpp_req_t
)brace
id|mtd_vpp_req_t
suffix:semicolon
multiline_comment|/* For MTDRDYMask */
DECL|struct|mtd_rdy_req_t
r_typedef
r_struct
id|mtd_rdy_req_t
(brace
DECL|member|Mask
id|u_int
id|Mask
suffix:semicolon
DECL|typedef|mtd_rdy_req_t
)brace
id|mtd_rdy_req_t
suffix:semicolon
DECL|enum|mtd_helper
r_enum
id|mtd_helper
(brace
DECL|enumerator|MTDRequestWindow
DECL|enumerator|MTDModifyWindow
DECL|enumerator|MTDReleaseWindow
id|MTDRequestWindow
comma
id|MTDModifyWindow
comma
id|MTDReleaseWindow
comma
DECL|enumerator|MTDSetVpp
DECL|enumerator|MTDRDYMask
id|MTDSetVpp
comma
id|MTDRDYMask
)brace
suffix:semicolon
macro_line|#ifdef IN_CARD_SERVICES
r_extern
r_int
id|MTDHelperEntry
c_func
(paren
r_int
id|func
comma
r_void
op_star
id|a1
comma
r_void
op_star
id|a2
)paren
suffix:semicolon
macro_line|#else
r_extern
r_int
id|MTDHelperEntry
c_func
(paren
r_int
id|func
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#endif
r_int
id|pcmcia_get_first_region
c_func
(paren
id|client_handle_t
id|handle
comma
id|region_info_t
op_star
id|rgn
)paren
suffix:semicolon
r_int
id|pcmcia_get_next_region
c_func
(paren
id|client_handle_t
id|handle
comma
id|region_info_t
op_star
id|rgn
)paren
suffix:semicolon
r_int
id|pcmcia_register_mtd
c_func
(paren
id|client_handle_t
id|handle
comma
id|mtd_reg_t
op_star
id|reg
)paren
suffix:semicolon
r_int
id|pcmcia_register_erase_queue
c_func
(paren
id|client_handle_t
op_star
id|handle
comma
id|eraseq_hdr_t
op_star
id|header
comma
id|eraseq_handle_t
op_star
id|e
)paren
suffix:semicolon
r_int
id|pcmcia_deregister_erase_queue
c_func
(paren
id|eraseq_handle_t
id|eraseq
)paren
suffix:semicolon
r_int
id|pcmcia_check_erase_queue
c_func
(paren
id|eraseq_handle_t
id|eraseq
)paren
suffix:semicolon
r_int
id|pcmcia_open_memory
c_func
(paren
id|client_handle_t
op_star
id|handle
comma
id|open_mem_t
op_star
id|open
comma
id|memory_handle_t
op_star
id|m
)paren
suffix:semicolon
r_int
id|pcmcia_close_memory
c_func
(paren
id|memory_handle_t
id|handle
)paren
suffix:semicolon
r_int
id|pcmcia_read_memory
c_func
(paren
id|memory_handle_t
id|handle
comma
id|mem_op_t
op_star
id|req
comma
id|caddr_t
id|buf
)paren
suffix:semicolon
r_int
id|pcmcia_write_memory
c_func
(paren
id|memory_handle_t
id|handle
comma
id|mem_op_t
op_star
id|req
comma
id|caddr_t
id|buf
)paren
suffix:semicolon
r_int
id|pcmcia_copy_memory
c_func
(paren
id|memory_handle_t
id|handle
comma
id|copy_op_t
op_star
id|req
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_BULKMEM_H */
eof
