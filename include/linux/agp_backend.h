multiline_comment|/*&n; * AGPGART module version 0.100&n; * Copyright (C) 2002-2003 Dave Jones&n; * Copyright (C) 1999 Jeff Hartmann&n; * Copyright (C) 1999 Precision Insight, Inc.&n; * Copyright (C) 1999 Xi Graphics, Inc.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice shall be included&n; * in all copies or substantial portions of the Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n; * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * JEFF HARTMANN, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, &n; * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR &n; * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE &n; * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.&n; *&n; */
macro_line|#ifndef _AGP_BACKEND_H
DECL|macro|_AGP_BACKEND_H
mdefine_line|#define _AGP_BACKEND_H 1
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
DECL|enum|chipset_type
r_enum
id|chipset_type
(brace
DECL|enumerator|NOT_SUPPORTED
id|NOT_SUPPORTED
comma
DECL|enumerator|INTEL_GENERIC
id|INTEL_GENERIC
comma
DECL|enumerator|VIA_GENERIC
id|VIA_GENERIC
comma
DECL|enumerator|SIS_GENERIC
id|SIS_GENERIC
comma
DECL|enumerator|AMD_GENERIC
id|AMD_GENERIC
comma
DECL|enumerator|AMD_8151
id|AMD_8151
comma
DECL|enumerator|ALI_GENERIC
id|ALI_GENERIC
comma
DECL|enumerator|SVWRKS_GENERIC
id|SVWRKS_GENERIC
comma
DECL|enumerator|HP_ZX1
id|HP_ZX1
comma
DECL|enumerator|ALPHA_CORE_AGP
id|ALPHA_CORE_AGP
comma
DECL|enumerator|NVIDIA_GENERIC
id|NVIDIA_GENERIC
comma
DECL|enumerator|NVIDIA_NFORCE
id|NVIDIA_NFORCE
comma
DECL|enumerator|NVIDIA_NFORCE2
id|NVIDIA_NFORCE2
comma
)brace
suffix:semicolon
DECL|struct|agp_version
r_struct
id|agp_version
(brace
DECL|member|major
id|u16
id|major
suffix:semicolon
DECL|member|minor
id|u16
id|minor
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_agp_kern_info
r_typedef
r_struct
id|_agp_kern_info
(brace
DECL|member|version
r_struct
id|agp_version
id|version
suffix:semicolon
DECL|member|device
r_struct
id|pci_dev
op_star
id|device
suffix:semicolon
DECL|member|chipset
r_enum
id|chipset_type
id|chipset
suffix:semicolon
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
DECL|member|aper_base
id|off_t
id|aper_base
suffix:semicolon
DECL|member|aper_size
r_int
id|aper_size
suffix:semicolon
DECL|member|max_memory
r_int
id|max_memory
suffix:semicolon
multiline_comment|/* In pages */
DECL|member|current_memory
r_int
id|current_memory
suffix:semicolon
DECL|member|cant_use_aperture
r_int
id|cant_use_aperture
suffix:semicolon
DECL|member|page_mask
r_int
r_int
id|page_mask
suffix:semicolon
DECL|member|vm_ops
r_struct
id|vm_operations_struct
op_star
id|vm_ops
suffix:semicolon
DECL|typedef|agp_kern_info
)brace
id|agp_kern_info
suffix:semicolon
multiline_comment|/* &n; * The agp_memory structure has information about the block of agp memory&n; * allocated.  A caller may manipulate the next and prev pointers to link&n; * each allocated item into a list.  These pointers are ignored by the backend.&n; * Everything else should never be written to, but the caller may read any of&n; * the items to detrimine the status of this block of agp memory. &n; */
DECL|struct|_agp_memory
r_typedef
r_struct
id|_agp_memory
(brace
DECL|member|key
r_int
id|key
suffix:semicolon
DECL|member|next
r_struct
id|_agp_memory
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|_agp_memory
op_star
id|prev
suffix:semicolon
DECL|member|page_count
r_int
id|page_count
suffix:semicolon
DECL|member|num_scratch_pages
r_int
id|num_scratch_pages
suffix:semicolon
DECL|member|memory
r_int
r_int
op_star
id|memory
suffix:semicolon
DECL|member|pg_start
id|off_t
id|pg_start
suffix:semicolon
DECL|member|type
id|u32
id|type
suffix:semicolon
DECL|member|physical
id|u32
id|physical
suffix:semicolon
DECL|member|is_bound
id|u8
id|is_bound
suffix:semicolon
DECL|member|is_flushed
id|u8
id|is_flushed
suffix:semicolon
DECL|typedef|agp_memory
)brace
id|agp_memory
suffix:semicolon
DECL|macro|AGP_NORMAL_MEMORY
mdefine_line|#define AGP_NORMAL_MEMORY 0
r_extern
r_void
id|agp_free_memory
c_func
(paren
id|agp_memory
op_star
)paren
suffix:semicolon
r_extern
id|agp_memory
op_star
id|agp_allocate_memory
c_func
(paren
r_int
comma
id|u32
)paren
suffix:semicolon
r_extern
r_int
id|agp_copy_info
c_func
(paren
id|agp_kern_info
op_star
)paren
suffix:semicolon
r_extern
r_int
id|agp_bind_memory
c_func
(paren
id|agp_memory
op_star
comma
id|off_t
)paren
suffix:semicolon
r_extern
r_int
id|agp_unbind_memory
c_func
(paren
id|agp_memory
op_star
)paren
suffix:semicolon
r_extern
r_void
id|agp_enable
c_func
(paren
id|u32
)paren
suffix:semicolon
r_extern
r_int
id|agp_backend_acquire
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|agp_backend_release
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Interface between drm and agp code.  When agp initializes, it makes&n; * the below structure available via inter_module_register(), drm might&n; * use it.  Keith Owens &lt;kaos@ocs.com.au&gt; 28 Oct 2000.&n; */
r_typedef
r_struct
(brace
DECL|member|free_memory
r_void
(paren
op_star
id|free_memory
)paren
(paren
id|agp_memory
op_star
)paren
suffix:semicolon
DECL|member|allocate_memory
id|agp_memory
op_star
(paren
op_star
id|allocate_memory
)paren
(paren
r_int
comma
id|u32
)paren
suffix:semicolon
DECL|member|bind_memory
r_int
(paren
op_star
id|bind_memory
)paren
(paren
id|agp_memory
op_star
comma
id|off_t
)paren
suffix:semicolon
DECL|member|unbind_memory
r_int
(paren
op_star
id|unbind_memory
)paren
(paren
id|agp_memory
op_star
)paren
suffix:semicolon
DECL|member|enable
r_void
(paren
op_star
id|enable
)paren
(paren
id|u32
)paren
suffix:semicolon
DECL|member|acquire
r_int
(paren
op_star
id|acquire
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|release
r_void
(paren
op_star
id|release
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|copy_info
r_int
(paren
op_star
id|copy_info
)paren
(paren
id|agp_kern_info
op_star
)paren
suffix:semicolon
DECL|typedef|drm_agp_t
)brace
id|drm_agp_t
suffix:semicolon
r_extern
r_const
id|drm_agp_t
op_star
id|drm_agp_p
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _AGP_BACKEND_H */
eof
