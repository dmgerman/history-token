macro_line|#ifndef __SOUND_UTIL_MEM_H
DECL|macro|__SOUND_UTIL_MEM_H
mdefine_line|#define __SOUND_UTIL_MEM_H
multiline_comment|/*&n; *  Copyright (C) 2000 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *  Generic memory management routines for soundcard memory allocation&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
DECL|typedef|snd_util_memblk_t
r_typedef
r_struct
id|snd_util_memblk
id|snd_util_memblk_t
suffix:semicolon
DECL|typedef|snd_util_memhdr_t
r_typedef
r_struct
id|snd_util_memhdr
id|snd_util_memhdr_t
suffix:semicolon
DECL|typedef|snd_util_unit_t
r_typedef
r_int
r_int
id|snd_util_unit_t
suffix:semicolon
multiline_comment|/*&n; * memory block&n; */
DECL|struct|snd_util_memblk
r_struct
id|snd_util_memblk
(brace
DECL|member|size
id|snd_util_unit_t
id|size
suffix:semicolon
multiline_comment|/* size of this block */
DECL|member|offset
id|snd_util_unit_t
id|offset
suffix:semicolon
multiline_comment|/* zero-offset of this block */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* link */
)brace
suffix:semicolon
DECL|macro|snd_util_memblk_argptr
mdefine_line|#define snd_util_memblk_argptr(blk)&t;(void*)((char*)(blk) + sizeof(snd_util_memblk_t))
multiline_comment|/*&n; * memory management information&n; */
DECL|struct|snd_util_memhdr
r_struct
id|snd_util_memhdr
(brace
DECL|member|size
id|snd_util_unit_t
id|size
suffix:semicolon
multiline_comment|/* size of whole data */
DECL|member|block
r_struct
id|list_head
id|block
suffix:semicolon
multiline_comment|/* block linked-list header */
DECL|member|nblocks
r_int
id|nblocks
suffix:semicolon
multiline_comment|/* # of allocated blocks */
DECL|member|used
id|snd_util_unit_t
id|used
suffix:semicolon
multiline_comment|/* used memory size */
DECL|member|block_extra_size
r_int
id|block_extra_size
suffix:semicolon
multiline_comment|/* extra data size of chunk */
DECL|member|block_mutex
r_struct
id|semaphore
id|block_mutex
suffix:semicolon
multiline_comment|/* lock */
)brace
suffix:semicolon
multiline_comment|/*&n; * prototypes&n; */
id|snd_util_memhdr_t
op_star
id|snd_util_memhdr_new
c_func
(paren
r_int
id|memsize
)paren
suffix:semicolon
r_void
id|snd_util_memhdr_free
c_func
(paren
id|snd_util_memhdr_t
op_star
id|hdr
)paren
suffix:semicolon
id|snd_util_memblk_t
op_star
id|snd_util_mem_alloc
c_func
(paren
id|snd_util_memhdr_t
op_star
id|hdr
comma
r_int
id|size
)paren
suffix:semicolon
r_int
id|snd_util_mem_free
c_func
(paren
id|snd_util_memhdr_t
op_star
id|hdr
comma
id|snd_util_memblk_t
op_star
id|blk
)paren
suffix:semicolon
r_int
id|snd_util_mem_avail
c_func
(paren
id|snd_util_memhdr_t
op_star
id|hdr
)paren
suffix:semicolon
multiline_comment|/* functions without mutex */
id|snd_util_memblk_t
op_star
id|__snd_util_mem_alloc
c_func
(paren
id|snd_util_memhdr_t
op_star
id|hdr
comma
r_int
id|size
)paren
suffix:semicolon
r_void
id|__snd_util_mem_free
c_func
(paren
id|snd_util_memhdr_t
op_star
id|hdr
comma
id|snd_util_memblk_t
op_star
id|blk
)paren
suffix:semicolon
id|snd_util_memblk_t
op_star
id|__snd_util_memblk_new
c_func
(paren
id|snd_util_memhdr_t
op_star
id|hdr
comma
id|snd_util_unit_t
id|units
comma
r_struct
id|list_head
op_star
id|prev
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_UTIL_MEM_H */
eof
