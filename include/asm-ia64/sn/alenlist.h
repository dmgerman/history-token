multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000 Silicon Graphics, Inc.&n; * Copyright (C) 2000 by Colin Ngam&n; */
macro_line|#ifndef _ASM_SN_ALENLIST_H
DECL|macro|_ASM_SN_ALENLIST_H
mdefine_line|#define _ASM_SN_ALENLIST_H
multiline_comment|/* Definition of Address/Length List */
multiline_comment|/*&n; * An Address/Length List is used when setting up for an I/O DMA operation.&n; * A driver creates an Address/Length List that describes to the the DMA &n; * interface where in memory the DMA should go.  The bus interface sets up &n; * mapping registers, if required, and returns a suitable list of &quot;physical &n; * addresses&quot; or &quot;I/O address&quot; to the driver.  The driver then uses these &n; * to set up an appropriate scatter/gather operation(s).&n; */
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
multiline_comment|/*&n; * An Address/Length List Address.  It&squot;ll get cast to the appropriate type,&n; * and must be big enough to hold the largest possible address in any&n; * supported address space.&n; */
DECL|typedef|alenaddr_t
r_typedef
id|u64
id|alenaddr_t
suffix:semicolon
DECL|typedef|uvaddr_t
r_typedef
id|u64
id|uvaddr_t
suffix:semicolon
DECL|typedef|alenlist_t
r_typedef
r_struct
id|alenlist_s
op_star
id|alenlist_t
suffix:semicolon
multiline_comment|/* &n; * For tracking progress as we walk down an address/length list.&n; */
DECL|typedef|alenlist_cursor_t
r_typedef
r_struct
id|alenlist_cursor_s
op_star
id|alenlist_cursor_t
suffix:semicolon
multiline_comment|/*&n; * alenlist representation that can be passed via an idl&n; */
DECL|struct|external_alenlist
r_struct
id|external_alenlist
(brace
DECL|member|addr
id|alenaddr_t
id|addr
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|external_alenlist_t
r_typedef
r_struct
id|external_alenlist
op_star
id|external_alenlist_t
suffix:semicolon
multiline_comment|/* Return codes from alenlist routines.  */
DECL|macro|ALENLIST_FAILURE
mdefine_line|#define ALENLIST_FAILURE -1
DECL|macro|ALENLIST_SUCCESS
mdefine_line|#define ALENLIST_SUCCESS 0
multiline_comment|/* Flags to alenlist routines */
DECL|macro|AL_NOSLEEP
mdefine_line|#define AL_NOSLEEP&t;0x01&t;&t;/* Do not sleep, waiting for memory */
DECL|macro|AL_NOCOMPACT
mdefine_line|#define AL_NOCOMPACT&t;0x02&t;&t;/* Do not try to compact adjacent entries */
DECL|macro|AL_LEAVE_CURSOR
mdefine_line|#define AL_LEAVE_CURSOR&t;0x04&t;&t;/* Do not update cursor */
multiline_comment|/* Create an Address/Length List, and clear it of all entries.  */
r_extern
id|alenlist_t
id|alenlist_create
c_func
(paren
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* Grow/shrink an Address/Length List and FIX its size. */
r_extern
r_int
id|alenlist_grow
c_func
(paren
id|alenlist_t
comma
r_int
id|npairs
)paren
suffix:semicolon
multiline_comment|/* Clear an Address/Length List so that it now describes 0 pairs. */
r_extern
r_void
id|alenlist_clear
c_func
(paren
id|alenlist_t
id|alenlist
)paren
suffix:semicolon
multiline_comment|/*&n; * Convenience function to create an Address/Length List and then append &n; * the specified Address/Length Pair.  Exactly the same as alenlist_create &n; * followed by alenlist_append.  Can be used when a small list (e.g. 1 pair)&n; * is adequate.&n; */
r_extern
id|alenlist_t
id|alenpair_init
c_func
(paren
id|alenaddr_t
id|address
comma
multiline_comment|/* init to this address */
r_int
id|length
)paren
suffix:semicolon
multiline_comment|/* init to this length */
multiline_comment|/* &n; * Peek at the head of an Address/Length List.  This does *NOT* update&n; * the internal cursor.&n; */
r_extern
r_int
id|alenpair_get
c_func
(paren
id|alenlist_t
id|alenlist
comma
multiline_comment|/* in: get from this List */
id|alenaddr_t
op_star
id|address
comma
multiline_comment|/* out: address */
r_int
op_star
id|length
)paren
suffix:semicolon
multiline_comment|/* out: length */
multiline_comment|/* Free the space consumed by an Address/Length List. */
r_extern
r_void
id|alenlist_destroy
c_func
(paren
id|alenlist_t
id|alenlist
)paren
suffix:semicolon
multiline_comment|/*&n; * Indicate that we&squot;re done using an Address/Length List.&n; * If we are the last user, destroy the List.&n; */
r_extern
r_void
id|alenlist_done
c_func
(paren
id|alenlist_t
id|alenlist
)paren
suffix:semicolon
multiline_comment|/* Append another Pair to a List */
r_extern
r_int
id|alenlist_append
c_func
(paren
id|alenlist_t
id|alenlist
comma
multiline_comment|/* append to this list */
id|alenaddr_t
id|address
comma
multiline_comment|/* address to append */
r_int
id|length
comma
multiline_comment|/* length to append */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* &n; * Replace a Pair in the middle of a List, and return old values.&n; * (not generally useful for drivers; used by bus providers).&n; */
r_extern
r_int
id|alenlist_replace
c_func
(paren
id|alenlist_t
id|alenlist
comma
multiline_comment|/* in: replace in this list */
id|alenlist_cursor_t
id|cursorp
comma
multiline_comment|/* inout: which item to replace */
id|alenaddr_t
op_star
id|addrp
comma
multiline_comment|/* inout: address */
r_int
op_star
id|lengthp
comma
multiline_comment|/* inout: length */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* Get the next Pair from a List */
r_extern
r_int
id|alenlist_get
c_func
(paren
id|alenlist_t
id|alenlist
comma
multiline_comment|/* in: get from this list */
id|alenlist_cursor_t
id|cursorp
comma
multiline_comment|/* inout: which item to get */
r_int
id|maxlength
comma
multiline_comment|/* in: at most length */
id|alenaddr_t
op_star
id|addr
comma
multiline_comment|/* out: address */
r_int
op_star
id|length
comma
multiline_comment|/* out: length */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* Return the number of Pairs stored in this List */
r_extern
r_int
id|alenlist_size
c_func
(paren
id|alenlist_t
id|alenlist
)paren
suffix:semicolon
multiline_comment|/* Concatenate two Lists. */
r_extern
r_void
id|alenlist_concat
c_func
(paren
id|alenlist_t
id|from
comma
multiline_comment|/* copy from this list */
id|alenlist_t
id|to
)paren
suffix:semicolon
multiline_comment|/* to this list */
multiline_comment|/* Create a copy of an Address/Length List */
r_extern
id|alenlist_t
id|alenlist_clone
c_func
(paren
id|alenlist_t
id|old
comma
multiline_comment|/* clone this list */
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* Allocate and initialize an Address/Length List Cursor */
r_extern
id|alenlist_cursor_t
id|alenlist_cursor_create
c_func
(paren
id|alenlist_t
id|alenlist
comma
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* Free an Address/Length List Cursor */
r_extern
r_void
id|alenlist_cursor_destroy
c_func
(paren
id|alenlist_cursor_t
id|cursorp
)paren
suffix:semicolon
multiline_comment|/*&n; * Initialize an Address/Length List Cursor in order to walk thru an&n; * Address/Length List from the beginning.&n; */
r_extern
r_int
id|alenlist_cursor_init
c_func
(paren
id|alenlist_t
id|alenlist
comma
r_int
id|offset
comma
id|alenlist_cursor_t
id|cursorp
)paren
suffix:semicolon
multiline_comment|/* Clone an Address/Length List Cursor. */
r_extern
r_int
id|alenlist_cursor_clone
c_func
(paren
id|alenlist_t
id|alenlist
comma
id|alenlist_cursor_t
id|cursorp_in
comma
id|alenlist_cursor_t
id|cursorp_out
)paren
suffix:semicolon
multiline_comment|/* &n; * Return the number of bytes passed so far according to the specified&n; * Address/Length List Cursor.&n; */
r_extern
r_int
id|alenlist_cursor_offset
c_func
(paren
id|alenlist_t
id|alenlist
comma
id|alenlist_cursor_t
id|cursorp
)paren
suffix:semicolon
multiline_comment|/* Convert from a Kernel Virtual Address to a Physical Address/Length List */
r_extern
id|alenlist_t
id|kvaddr_to_alenlist
c_func
(paren
id|alenlist_t
id|alenlist
comma
id|caddr_t
id|kvaddr
comma
r_int
id|length
comma
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* Convert from a User Virtual Address to a Physical Address/Length List */
r_extern
id|alenlist_t
id|uvaddr_to_alenlist
c_func
(paren
id|alenlist_t
id|alenlist
comma
id|uvaddr_t
id|vaddr
comma
r_int
id|length
comma
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* Convert from a buf struct to a Physical Address/Length List */
r_struct
id|buf
suffix:semicolon
r_extern
id|alenlist_t
id|buf_to_alenlist
c_func
(paren
id|alenlist_t
id|alenlist
comma
r_struct
id|buf
op_star
id|buf
comma
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* &n; * Tracking position as we walk down an Address/Length List.&n; * This structure is NOT generally for use by device drivers.&n; */
DECL|struct|alenlist_cursor_s
r_struct
id|alenlist_cursor_s
(brace
DECL|member|al_alenlist
r_struct
id|alenlist_s
op_star
id|al_alenlist
suffix:semicolon
multiline_comment|/* which list */
DECL|member|al_offset
r_int
id|al_offset
suffix:semicolon
multiline_comment|/* total bytes passed by cursor */
DECL|member|al_chunk
r_struct
id|alenlist_chunk_s
op_star
id|al_chunk
suffix:semicolon
multiline_comment|/* which chunk in alenlist */
DECL|member|al_index
r_int
r_int
id|al_index
suffix:semicolon
multiline_comment|/* which pair in chunk */
DECL|member|al_bcount
r_int
id|al_bcount
suffix:semicolon
multiline_comment|/* offset into address/length pair */
)brace
suffix:semicolon
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* _ASM_SN_ALENLIST_H */
eof
