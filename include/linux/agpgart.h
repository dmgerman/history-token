multiline_comment|/*&n; * AGPGART module version 0.99&n; * Copyright (C) 1999 Jeff Hartmann&n; * Copyright (C) 1999 Precision Insight, Inc.&n; * Copyright (C) 1999 Xi Graphics, Inc.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice shall be included&n; * in all copies or substantial portions of the Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n; * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * JEFF HARTMANN, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, &n; * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR &n; * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE &n; * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.&n; *&n; */
macro_line|#ifndef _AGP_H
DECL|macro|_AGP_H
mdefine_line|#define _AGP_H 1
DECL|macro|AGPIOC_BASE
mdefine_line|#define AGPIOC_BASE       &squot;A&squot;
DECL|macro|AGPIOC_INFO
mdefine_line|#define AGPIOC_INFO       _IOR (AGPIOC_BASE, 0, agp_info*)
DECL|macro|AGPIOC_ACQUIRE
mdefine_line|#define AGPIOC_ACQUIRE    _IO  (AGPIOC_BASE, 1)
DECL|macro|AGPIOC_RELEASE
mdefine_line|#define AGPIOC_RELEASE    _IO  (AGPIOC_BASE, 2)
DECL|macro|AGPIOC_SETUP
mdefine_line|#define AGPIOC_SETUP      _IOW (AGPIOC_BASE, 3, agp_setup*)
DECL|macro|AGPIOC_RESERVE
mdefine_line|#define AGPIOC_RESERVE    _IOW (AGPIOC_BASE, 4, agp_region*)
DECL|macro|AGPIOC_PROTECT
mdefine_line|#define AGPIOC_PROTECT    _IOW (AGPIOC_BASE, 5, agp_region*)
DECL|macro|AGPIOC_ALLOCATE
mdefine_line|#define AGPIOC_ALLOCATE   _IOWR(AGPIOC_BASE, 6, agp_allocate*)
DECL|macro|AGPIOC_DEALLOCATE
mdefine_line|#define AGPIOC_DEALLOCATE _IOW (AGPIOC_BASE, 7, int)
DECL|macro|AGPIOC_BIND
mdefine_line|#define AGPIOC_BIND       _IOW (AGPIOC_BASE, 8, agp_bind*)
DECL|macro|AGPIOC_UNBIND
mdefine_line|#define AGPIOC_UNBIND     _IOW (AGPIOC_BASE, 9, agp_unbind*)
DECL|macro|AGP_DEVICE
mdefine_line|#define AGP_DEVICE      &quot;/dev/agpgart&quot;
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
macro_line|#ifndef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|struct|_agp_version
r_typedef
r_struct
id|_agp_version
(brace
DECL|member|major
id|__u16
id|major
suffix:semicolon
DECL|member|minor
id|__u16
id|minor
suffix:semicolon
DECL|typedef|agp_version
)brace
id|agp_version
suffix:semicolon
DECL|struct|_agp_info
r_typedef
r_struct
id|_agp_info
(brace
DECL|member|version
id|agp_version
id|version
suffix:semicolon
multiline_comment|/* version of the driver        */
DECL|member|bridge_id
id|__u32
id|bridge_id
suffix:semicolon
multiline_comment|/* bridge vendor/device         */
DECL|member|agp_mode
id|__u32
id|agp_mode
suffix:semicolon
multiline_comment|/* mode info of bridge          */
DECL|member|aper_base
id|off_t
id|aper_base
suffix:semicolon
multiline_comment|/* base of aperture             */
DECL|member|aper_size
r_int
id|aper_size
suffix:semicolon
multiline_comment|/* size of aperture             */
DECL|member|pg_total
r_int
id|pg_total
suffix:semicolon
multiline_comment|/* max pages (swap + system)    */
DECL|member|pg_system
r_int
id|pg_system
suffix:semicolon
multiline_comment|/* max pages (system)           */
DECL|member|pg_used
r_int
id|pg_used
suffix:semicolon
multiline_comment|/* current pages used           */
DECL|typedef|agp_info
)brace
id|agp_info
suffix:semicolon
DECL|struct|_agp_setup
r_typedef
r_struct
id|_agp_setup
(brace
DECL|member|agp_mode
id|__u32
id|agp_mode
suffix:semicolon
multiline_comment|/* mode info of bridge          */
DECL|typedef|agp_setup
)brace
id|agp_setup
suffix:semicolon
multiline_comment|/*&n; * The &quot;prot&quot; down below needs still a &quot;sleep&quot; flag somehow ...&n; */
DECL|struct|_agp_segment
r_typedef
r_struct
id|_agp_segment
(brace
DECL|member|pg_start
id|off_t
id|pg_start
suffix:semicolon
multiline_comment|/* starting page to populate    */
DECL|member|pg_count
r_int
id|pg_count
suffix:semicolon
multiline_comment|/* number of pages              */
DECL|member|prot
r_int
id|prot
suffix:semicolon
multiline_comment|/* prot flags for mmap          */
DECL|typedef|agp_segment
)brace
id|agp_segment
suffix:semicolon
DECL|struct|_agp_region
r_typedef
r_struct
id|_agp_region
(brace
DECL|member|pid
id|pid_t
id|pid
suffix:semicolon
multiline_comment|/* pid of process               */
DECL|member|seg_count
r_int
id|seg_count
suffix:semicolon
multiline_comment|/* number of segments           */
DECL|member|seg_list
r_struct
id|_agp_segment
op_star
id|seg_list
suffix:semicolon
DECL|typedef|agp_region
)brace
id|agp_region
suffix:semicolon
DECL|struct|_agp_allocate
r_typedef
r_struct
id|_agp_allocate
(brace
DECL|member|key
r_int
id|key
suffix:semicolon
multiline_comment|/* tag of allocation            */
DECL|member|pg_count
r_int
id|pg_count
suffix:semicolon
multiline_comment|/* number of pages              */
DECL|member|type
id|__u32
id|type
suffix:semicolon
multiline_comment|/* 0 == normal, other devspec   */
DECL|member|physical
id|__u32
id|physical
suffix:semicolon
multiline_comment|/* device specific (some devices  &n;&t;&t;&t;&t; * need a phys address of the     &n;&t;&t;&t;&t; * actual page behind the gatt    &n;&t;&t;&t;&t; * table)                        */
DECL|typedef|agp_allocate
)brace
id|agp_allocate
suffix:semicolon
DECL|struct|_agp_bind
r_typedef
r_struct
id|_agp_bind
(brace
DECL|member|key
r_int
id|key
suffix:semicolon
multiline_comment|/* tag of allocation            */
DECL|member|pg_start
id|off_t
id|pg_start
suffix:semicolon
multiline_comment|/* starting page to populate    */
DECL|typedef|agp_bind
)brace
id|agp_bind
suffix:semicolon
DECL|struct|_agp_unbind
r_typedef
r_struct
id|_agp_unbind
(brace
DECL|member|key
r_int
id|key
suffix:semicolon
multiline_comment|/* tag of allocation            */
DECL|member|priority
id|__u32
id|priority
suffix:semicolon
multiline_comment|/* priority for paging out      */
DECL|typedef|agp_unbind
)brace
id|agp_unbind
suffix:semicolon
macro_line|#else&t;&t;&t;&t;/* __KERNEL__ */
DECL|macro|AGPGART_MINOR
mdefine_line|#define AGPGART_MINOR 175
DECL|macro|AGP_UNLOCK
mdefine_line|#define AGP_UNLOCK()      &t;up(&amp;(agp_fe.agp_mutex));
DECL|macro|AGP_LOCK
mdefine_line|#define AGP_LOCK()    &t;&t;down(&amp;(agp_fe.agp_mutex));
DECL|macro|AGP_LOCK_INIT
mdefine_line|#define AGP_LOCK_INIT() &t;sema_init(&amp;(agp_fe.agp_mutex), 1)
macro_line|#ifndef _AGP_BACKEND_H
DECL|struct|_agp_version
r_typedef
r_struct
id|_agp_version
(brace
DECL|member|major
id|u16
id|major
suffix:semicolon
DECL|member|minor
id|u16
id|minor
suffix:semicolon
DECL|typedef|agp_version
)brace
id|agp_version
suffix:semicolon
macro_line|#endif
DECL|struct|_agp_info
r_typedef
r_struct
id|_agp_info
(brace
DECL|member|version
id|agp_version
id|version
suffix:semicolon
multiline_comment|/* version of the driver        */
DECL|member|bridge_id
id|u32
id|bridge_id
suffix:semicolon
multiline_comment|/* bridge vendor/device         */
DECL|member|agp_mode
id|u32
id|agp_mode
suffix:semicolon
multiline_comment|/* mode info of bridge          */
DECL|member|aper_base
id|off_t
id|aper_base
suffix:semicolon
multiline_comment|/* base of aperture             */
DECL|member|aper_size
r_int
id|aper_size
suffix:semicolon
multiline_comment|/* size of aperture             */
DECL|member|pg_total
r_int
id|pg_total
suffix:semicolon
multiline_comment|/* max pages (swap + system)    */
DECL|member|pg_system
r_int
id|pg_system
suffix:semicolon
multiline_comment|/* max pages (system)           */
DECL|member|pg_used
r_int
id|pg_used
suffix:semicolon
multiline_comment|/* current pages used           */
DECL|typedef|agp_info
)brace
id|agp_info
suffix:semicolon
DECL|struct|_agp_setup
r_typedef
r_struct
id|_agp_setup
(brace
DECL|member|agp_mode
id|u32
id|agp_mode
suffix:semicolon
multiline_comment|/* mode info of bridge          */
DECL|typedef|agp_setup
)brace
id|agp_setup
suffix:semicolon
multiline_comment|/*&n; * The &quot;prot&quot; down below needs still a &quot;sleep&quot; flag somehow ...&n; */
DECL|struct|_agp_segment
r_typedef
r_struct
id|_agp_segment
(brace
DECL|member|pg_start
id|off_t
id|pg_start
suffix:semicolon
multiline_comment|/* starting page to populate    */
DECL|member|pg_count
r_int
id|pg_count
suffix:semicolon
multiline_comment|/* number of pages              */
DECL|member|prot
r_int
id|prot
suffix:semicolon
multiline_comment|/* prot flags for mmap          */
DECL|typedef|agp_segment
)brace
id|agp_segment
suffix:semicolon
DECL|struct|_agp_segment_priv
r_typedef
r_struct
id|_agp_segment_priv
(brace
DECL|member|pg_start
id|off_t
id|pg_start
suffix:semicolon
DECL|member|pg_count
r_int
id|pg_count
suffix:semicolon
DECL|member|prot
id|pgprot_t
id|prot
suffix:semicolon
DECL|typedef|agp_segment_priv
)brace
id|agp_segment_priv
suffix:semicolon
DECL|struct|_agp_region
r_typedef
r_struct
id|_agp_region
(brace
DECL|member|pid
id|pid_t
id|pid
suffix:semicolon
multiline_comment|/* pid of process               */
DECL|member|seg_count
r_int
id|seg_count
suffix:semicolon
multiline_comment|/* number of segments           */
DECL|member|seg_list
r_struct
id|_agp_segment
op_star
id|seg_list
suffix:semicolon
DECL|typedef|agp_region
)brace
id|agp_region
suffix:semicolon
DECL|struct|_agp_allocate
r_typedef
r_struct
id|_agp_allocate
(brace
DECL|member|key
r_int
id|key
suffix:semicolon
multiline_comment|/* tag of allocation            */
DECL|member|pg_count
r_int
id|pg_count
suffix:semicolon
multiline_comment|/* number of pages              */
DECL|member|type
id|u32
id|type
suffix:semicolon
multiline_comment|/* 0 == normal, other devspec   */
DECL|member|physical
id|u32
id|physical
suffix:semicolon
multiline_comment|/* device specific (some devices  &n;&t;&t;&t;&t; * need a phys address of the     &n;&t;&t;&t;&t; * actual page behind the gatt    &n;&t;&t;&t;&t; * table)                        */
DECL|typedef|agp_allocate
)brace
id|agp_allocate
suffix:semicolon
DECL|struct|_agp_bind
r_typedef
r_struct
id|_agp_bind
(brace
DECL|member|key
r_int
id|key
suffix:semicolon
multiline_comment|/* tag of allocation            */
DECL|member|pg_start
id|off_t
id|pg_start
suffix:semicolon
multiline_comment|/* starting page to populate    */
DECL|typedef|agp_bind
)brace
id|agp_bind
suffix:semicolon
DECL|struct|_agp_unbind
r_typedef
r_struct
id|_agp_unbind
(brace
DECL|member|key
r_int
id|key
suffix:semicolon
multiline_comment|/* tag of allocation            */
DECL|member|priority
id|u32
id|priority
suffix:semicolon
multiline_comment|/* priority for paging out      */
DECL|typedef|agp_unbind
)brace
id|agp_unbind
suffix:semicolon
DECL|struct|_agp_client
r_typedef
r_struct
id|_agp_client
(brace
DECL|member|next
r_struct
id|_agp_client
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|_agp_client
op_star
id|prev
suffix:semicolon
DECL|member|pid
id|pid_t
id|pid
suffix:semicolon
DECL|member|num_segments
r_int
id|num_segments
suffix:semicolon
DECL|member|segments
id|agp_segment_priv
op_star
op_star
id|segments
suffix:semicolon
DECL|typedef|agp_client
)brace
id|agp_client
suffix:semicolon
DECL|struct|_agp_controller
r_typedef
r_struct
id|_agp_controller
(brace
DECL|member|next
r_struct
id|_agp_controller
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|_agp_controller
op_star
id|prev
suffix:semicolon
DECL|member|pid
id|pid_t
id|pid
suffix:semicolon
DECL|member|num_clients
r_int
id|num_clients
suffix:semicolon
DECL|member|pool
id|agp_memory
op_star
id|pool
suffix:semicolon
DECL|member|clients
id|agp_client
op_star
id|clients
suffix:semicolon
DECL|typedef|agp_controller
)brace
id|agp_controller
suffix:semicolon
DECL|macro|AGP_FF_ALLOW_CLIENT
mdefine_line|#define AGP_FF_ALLOW_CLIENT&t;&t;0
DECL|macro|AGP_FF_ALLOW_CONTROLLER
mdefine_line|#define AGP_FF_ALLOW_CONTROLLER &t;1
DECL|macro|AGP_FF_IS_CLIENT
mdefine_line|#define AGP_FF_IS_CLIENT&t;&t;2
DECL|macro|AGP_FF_IS_CONTROLLER
mdefine_line|#define AGP_FF_IS_CONTROLLER&t;&t;3
DECL|macro|AGP_FF_IS_VALID
mdefine_line|#define AGP_FF_IS_VALID &t;&t;4
DECL|struct|_agp_file_private
r_typedef
r_struct
id|_agp_file_private
(brace
DECL|member|next
r_struct
id|_agp_file_private
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|_agp_file_private
op_star
id|prev
suffix:semicolon
DECL|member|my_pid
id|pid_t
id|my_pid
suffix:semicolon
DECL|member|access_flags
r_int
id|access_flags
suffix:semicolon
multiline_comment|/* long req&squot;d for set_bit --RR */
DECL|typedef|agp_file_private
)brace
id|agp_file_private
suffix:semicolon
DECL|struct|agp_front_data
r_struct
id|agp_front_data
(brace
DECL|member|agp_mutex
r_struct
id|semaphore
id|agp_mutex
suffix:semicolon
DECL|member|current_controller
id|agp_controller
op_star
id|current_controller
suffix:semicolon
DECL|member|controllers
id|agp_controller
op_star
id|controllers
suffix:semicolon
DECL|member|file_priv_list
id|agp_file_private
op_star
id|file_priv_list
suffix:semicolon
DECL|member|used_by_controller
id|u8
id|used_by_controller
suffix:semicolon
DECL|member|backend_acquired
id|u8
id|backend_acquired
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#endif&t;&t;&t;&t;/* _AGP_H */
eof
