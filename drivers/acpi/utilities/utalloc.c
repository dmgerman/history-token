multiline_comment|/******************************************************************************&n; *&n; * Module Name: utalloc - local cache and memory allocation routines&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_UTILITIES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;utalloc&quot;
)paren
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_release_to_cache&n; *&n; * PARAMETERS:  list_id             - Memory list/cache ID&n; *              Object              - The object to be released&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Release an object to the specified cache.  If cache is full,&n; *              the object is deleted.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ut_release_to_cache
id|acpi_ut_release_to_cache
(paren
id|u32
id|list_id
comma
r_void
op_star
id|object
)paren
(brace
id|acpi_memory_list
op_star
id|cache_info
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/* If walk cache is full, just free this wallkstate object */
id|cache_info
op_assign
op_amp
id|acpi_gbl_memory_lists
(braket
id|list_id
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cache_info-&gt;cache_depth
op_ge
id|cache_info-&gt;max_cache_depth
)paren
(brace
id|ACPI_MEM_FREE
(paren
id|object
)paren
suffix:semicolon
id|ACPI_MEM_TRACKING
(paren
id|cache_info-&gt;total_freed
op_increment
)paren
suffix:semicolon
)brace
multiline_comment|/* Otherwise put this object back into the cache */
r_else
(brace
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_CACHES
)paren
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Mark the object as cached */
id|ACPI_MEMSET
(paren
id|object
comma
l_int|0xCA
comma
id|cache_info-&gt;object_size
)paren
suffix:semicolon
id|ACPI_SET_DESCRIPTOR_TYPE
(paren
id|object
comma
id|ACPI_DESC_TYPE_CACHED
)paren
suffix:semicolon
multiline_comment|/* Put the object at the head of the cache list */
op_star
(paren
id|ACPI_CAST_INDIRECT_PTR
(paren
r_char
comma
op_amp
(paren
(paren
(paren
r_char
op_star
)paren
id|object
)paren
(braket
id|cache_info-&gt;link_offset
)braket
)paren
)paren
)paren
op_assign
id|cache_info-&gt;list_head
suffix:semicolon
id|cache_info-&gt;list_head
op_assign
id|object
suffix:semicolon
id|cache_info-&gt;cache_depth
op_increment
suffix:semicolon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_CACHES
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_acquire_from_cache&n; *&n; * PARAMETERS:  list_id             - Memory list ID&n; *&n; * RETURN:      A requested object.  NULL if the object could not be&n; *              allocated.&n; *&n; * DESCRIPTION: Get an object from the specified cache.  If cache is empty,&n; *              the object is allocated.&n; *&n; ******************************************************************************/
r_void
op_star
DECL|function|acpi_ut_acquire_from_cache
id|acpi_ut_acquire_from_cache
(paren
id|u32
id|list_id
)paren
(brace
id|acpi_memory_list
op_star
id|cache_info
suffix:semicolon
r_void
op_star
id|object
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;ut_acquire_from_cache&quot;
)paren
suffix:semicolon
id|cache_info
op_assign
op_amp
id|acpi_gbl_memory_lists
(braket
id|list_id
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_CACHES
)paren
)paren
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|ACPI_MEM_TRACKING
(paren
id|cache_info-&gt;cache_requests
op_increment
)paren
suffix:semicolon
multiline_comment|/* Check the cache first */
r_if
c_cond
(paren
id|cache_info-&gt;list_head
)paren
(brace
multiline_comment|/* There is an object available, use it */
id|object
op_assign
id|cache_info-&gt;list_head
suffix:semicolon
id|cache_info-&gt;list_head
op_assign
op_star
(paren
id|ACPI_CAST_INDIRECT_PTR
(paren
r_char
comma
op_amp
(paren
(paren
(paren
r_char
op_star
)paren
id|object
)paren
(braket
id|cache_info-&gt;link_offset
)braket
)paren
)paren
)paren
suffix:semicolon
id|ACPI_MEM_TRACKING
(paren
id|cache_info-&gt;cache_hits
op_increment
)paren
suffix:semicolon
id|cache_info-&gt;cache_depth
op_decrement
suffix:semicolon
macro_line|#ifdef ACPI_DBG_TRACK_ALLOCATIONS
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Object %p from %s&bslash;n&quot;
comma
id|object
comma
id|acpi_gbl_memory_lists
(braket
id|list_id
)braket
dot
id|list_name
)paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_CACHES
)paren
)paren
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear (zero) the previously used Object */
id|ACPI_MEMSET
(paren
id|object
comma
l_int|0
comma
id|cache_info-&gt;object_size
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* The cache is empty, create a new object */
multiline_comment|/* Avoid deadlock with ACPI_MEM_CALLOCATE */
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_CACHES
)paren
)paren
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|object
op_assign
id|ACPI_MEM_CALLOCATE
(paren
id|cache_info-&gt;object_size
)paren
suffix:semicolon
id|ACPI_MEM_TRACKING
(paren
id|cache_info-&gt;total_allocated
op_increment
)paren
suffix:semicolon
)brace
r_return
(paren
id|object
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_delete_generic_cache&n; *&n; * PARAMETERS:  list_id         - Memory list ID&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Free all objects within the requested cache.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ut_delete_generic_cache
id|acpi_ut_delete_generic_cache
(paren
id|u32
id|list_id
)paren
(brace
id|acpi_memory_list
op_star
id|cache_info
suffix:semicolon
r_char
op_star
id|next
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
id|cache_info
op_assign
op_amp
id|acpi_gbl_memory_lists
(braket
id|list_id
)braket
suffix:semicolon
r_while
c_loop
(paren
id|cache_info-&gt;list_head
)paren
(brace
multiline_comment|/* Delete one cached state object */
id|next
op_assign
op_star
(paren
id|ACPI_CAST_INDIRECT_PTR
(paren
r_char
comma
op_amp
(paren
(paren
(paren
r_char
op_star
)paren
id|cache_info-&gt;list_head
)paren
(braket
id|cache_info-&gt;link_offset
)braket
)paren
)paren
)paren
suffix:semicolon
id|ACPI_MEM_FREE
(paren
id|cache_info-&gt;list_head
)paren
suffix:semicolon
id|cache_info-&gt;list_head
op_assign
id|next
suffix:semicolon
id|cache_info-&gt;cache_depth
op_decrement
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_validate_buffer&n; *&n; * PARAMETERS:  Buffer              - Buffer descriptor to be validated&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Perform parameter validation checks on an acpi_buffer&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_validate_buffer
id|acpi_ut_validate_buffer
(paren
id|acpi_buffer
op_star
id|buffer
)paren
(brace
multiline_comment|/* Obviously, the structure pointer must be valid */
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Special semantics for the length */
r_if
c_cond
(paren
(paren
id|buffer-&gt;length
op_eq
id|ACPI_NO_BUFFER
)paren
op_logical_or
(paren
id|buffer-&gt;length
op_eq
id|ACPI_ALLOCATE_BUFFER
)paren
op_logical_or
(paren
id|buffer-&gt;length
op_eq
id|ACPI_ALLOCATE_LOCAL_BUFFER
)paren
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Length is valid, the buffer pointer must be also */
r_if
c_cond
(paren
op_logical_neg
id|buffer-&gt;pointer
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_initialize_buffer&n; *&n; * PARAMETERS:  required_length     - Length needed&n; *              Buffer              - Buffer to be validated&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Validate that the buffer is of the required length or&n; *              allocate a new buffer.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_initialize_buffer
id|acpi_ut_initialize_buffer
(paren
id|acpi_buffer
op_star
id|buffer
comma
id|acpi_size
id|required_length
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_switch
c_cond
(paren
id|buffer-&gt;length
)paren
(brace
r_case
id|ACPI_NO_BUFFER
suffix:colon
multiline_comment|/* Set the exception and returned the required length */
id|status
op_assign
id|AE_BUFFER_OVERFLOW
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_ALLOCATE_BUFFER
suffix:colon
multiline_comment|/* Allocate a new buffer */
id|buffer-&gt;pointer
op_assign
id|acpi_os_allocate
(paren
id|required_length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer-&gt;pointer
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear the buffer */
id|ACPI_MEMSET
(paren
id|buffer-&gt;pointer
comma
l_int|0
comma
id|required_length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_ALLOCATE_LOCAL_BUFFER
suffix:colon
multiline_comment|/* Allocate a new buffer with local interface to allow tracking */
id|buffer-&gt;pointer
op_assign
id|ACPI_MEM_ALLOCATE
(paren
id|required_length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer-&gt;pointer
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear the buffer */
id|ACPI_MEMSET
(paren
id|buffer-&gt;pointer
comma
l_int|0
comma
id|required_length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* Validate the size of the buffer */
r_if
c_cond
(paren
id|buffer-&gt;length
OL
id|required_length
)paren
(brace
id|status
op_assign
id|AE_BUFFER_OVERFLOW
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|buffer-&gt;length
op_assign
id|required_length
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_allocate&n; *&n; * PARAMETERS:  Size                - Size of the allocation&n; *              Component           - Component type of caller&n; *              Module              - Source file name of caller&n; *              Line                - Line number of caller&n; *&n; * RETURN:      Address of the allocated memory on success, NULL on failure.&n; *&n; * DESCRIPTION: The subsystem&squot;s equivalent of malloc.&n; *&n; ******************************************************************************/
r_void
op_star
DECL|function|acpi_ut_allocate
id|acpi_ut_allocate
(paren
id|acpi_size
id|size
comma
id|u32
id|component
comma
r_char
op_star
id|module
comma
id|u32
id|line
)paren
(brace
r_void
op_star
id|allocation
suffix:semicolon
id|ACPI_FUNCTION_TRACE_U32
(paren
l_string|&quot;ut_allocate&quot;
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* Check for an inadvertent size of zero bytes */
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
id|_ACPI_REPORT_ERROR
(paren
id|module
comma
id|line
comma
id|component
comma
(paren
l_string|&quot;ut_allocate: Attempt to allocate zero bytes&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|size
op_assign
l_int|1
suffix:semicolon
)brace
id|allocation
op_assign
id|acpi_os_allocate
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|allocation
)paren
(brace
multiline_comment|/* Report allocation error */
id|_ACPI_REPORT_ERROR
(paren
id|module
comma
id|line
comma
id|component
comma
(paren
l_string|&quot;ut_allocate: Could not allocate size %X&bslash;n&quot;
comma
(paren
id|u32
)paren
id|size
)paren
)paren
suffix:semicolon
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|return_PTR
(paren
id|allocation
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_callocate&n; *&n; * PARAMETERS:  Size                - Size of the allocation&n; *              Component           - Component type of caller&n; *              Module              - Source file name of caller&n; *              Line                - Line number of caller&n; *&n; * RETURN:      Address of the allocated memory on success, NULL on failure.&n; *&n; * DESCRIPTION: Subsystem equivalent of calloc.&n; *&n; ******************************************************************************/
r_void
op_star
DECL|function|acpi_ut_callocate
id|acpi_ut_callocate
(paren
id|acpi_size
id|size
comma
id|u32
id|component
comma
r_char
op_star
id|module
comma
id|u32
id|line
)paren
(brace
r_void
op_star
id|allocation
suffix:semicolon
id|ACPI_FUNCTION_TRACE_U32
(paren
l_string|&quot;ut_callocate&quot;
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* Check for an inadvertent size of zero bytes */
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
id|_ACPI_REPORT_ERROR
(paren
id|module
comma
id|line
comma
id|component
comma
(paren
l_string|&quot;ut_callocate: Attempt to allocate zero bytes&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|allocation
op_assign
id|acpi_os_allocate
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|allocation
)paren
(brace
multiline_comment|/* Report allocation error */
id|_ACPI_REPORT_ERROR
(paren
id|module
comma
id|line
comma
id|component
comma
(paren
l_string|&quot;ut_callocate: Could not allocate size %X&bslash;n&quot;
comma
(paren
id|u32
)paren
id|size
)paren
)paren
suffix:semicolon
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear the memory block */
id|ACPI_MEMSET
(paren
id|allocation
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
id|return_PTR
(paren
id|allocation
)paren
suffix:semicolon
)brace
macro_line|#ifdef ACPI_DBG_TRACK_ALLOCATIONS
multiline_comment|/*&n; * These procedures are used for tracking memory leaks in the subsystem, and&n; * they get compiled out when the ACPI_DBG_TRACK_ALLOCATIONS is not set.&n; *&n; * Each memory allocation is tracked via a doubly linked list.  Each&n; * element contains the caller&squot;s component, module name, function name, and&n; * line number.  acpi_ut_allocate and acpi_ut_callocate call&n; * acpi_ut_track_allocation to add an element to the list; deletion&n; * occurs in the body of acpi_ut_free.&n; */
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_allocate_and_track&n; *&n; * PARAMETERS:  Size                - Size of the allocation&n; *              Component           - Component type of caller&n; *              Module              - Source file name of caller&n; *              Line                - Line number of caller&n; *&n; * RETURN:      Address of the allocated memory on success, NULL on failure.&n; *&n; * DESCRIPTION: The subsystem&squot;s equivalent of malloc.&n; *&n; ******************************************************************************/
r_void
op_star
DECL|function|acpi_ut_allocate_and_track
id|acpi_ut_allocate_and_track
(paren
id|acpi_size
id|size
comma
id|u32
id|component
comma
r_char
op_star
id|module
comma
id|u32
id|line
)paren
(brace
id|acpi_debug_mem_block
op_star
id|allocation
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|allocation
op_assign
id|acpi_ut_allocate
(paren
id|size
op_plus
r_sizeof
(paren
id|acpi_debug_mem_block
)paren
comma
id|component
comma
id|module
comma
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|allocation
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ut_track_allocation
(paren
id|ACPI_MEM_LIST_GLOBAL
comma
id|allocation
comma
id|size
comma
id|ACPI_MEM_MALLOC
comma
id|component
comma
id|module
comma
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|acpi_os_free
(paren
id|allocation
)paren
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|acpi_gbl_memory_lists
(braket
id|ACPI_MEM_LIST_GLOBAL
)braket
dot
id|total_allocated
op_increment
suffix:semicolon
id|acpi_gbl_memory_lists
(braket
id|ACPI_MEM_LIST_GLOBAL
)braket
dot
id|current_total_size
op_add_assign
(paren
id|u32
)paren
id|size
suffix:semicolon
r_return
(paren
(paren
r_void
op_star
)paren
op_amp
id|allocation-&gt;user_space
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_callocate_and_track&n; *&n; * PARAMETERS:  Size                - Size of the allocation&n; *              Component           - Component type of caller&n; *              Module              - Source file name of caller&n; *              Line                - Line number of caller&n; *&n; * RETURN:      Address of the allocated memory on success, NULL on failure.&n; *&n; * DESCRIPTION: Subsystem equivalent of calloc.&n; *&n; ******************************************************************************/
r_void
op_star
DECL|function|acpi_ut_callocate_and_track
id|acpi_ut_callocate_and_track
(paren
id|acpi_size
id|size
comma
id|u32
id|component
comma
r_char
op_star
id|module
comma
id|u32
id|line
)paren
(brace
id|acpi_debug_mem_block
op_star
id|allocation
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|allocation
op_assign
id|acpi_ut_callocate
(paren
id|size
op_plus
r_sizeof
(paren
id|acpi_debug_mem_block
)paren
comma
id|component
comma
id|module
comma
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|allocation
)paren
(brace
multiline_comment|/* Report allocation error */
id|_ACPI_REPORT_ERROR
(paren
id|module
comma
id|line
comma
id|component
comma
(paren
l_string|&quot;ut_callocate: Could not allocate size %X&bslash;n&quot;
comma
(paren
id|u32
)paren
id|size
)paren
)paren
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ut_track_allocation
(paren
id|ACPI_MEM_LIST_GLOBAL
comma
id|allocation
comma
id|size
comma
id|ACPI_MEM_CALLOC
comma
id|component
comma
id|module
comma
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|acpi_os_free
(paren
id|allocation
)paren
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|acpi_gbl_memory_lists
(braket
id|ACPI_MEM_LIST_GLOBAL
)braket
dot
id|total_allocated
op_increment
suffix:semicolon
id|acpi_gbl_memory_lists
(braket
id|ACPI_MEM_LIST_GLOBAL
)braket
dot
id|current_total_size
op_add_assign
(paren
id|u32
)paren
id|size
suffix:semicolon
r_return
(paren
(paren
r_void
op_star
)paren
op_amp
id|allocation-&gt;user_space
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_free_and_track&n; *&n; * PARAMETERS:  Allocation          - Address of the memory to deallocate&n; *              Component           - Component type of caller&n; *              Module              - Source file name of caller&n; *              Line                - Line number of caller&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Frees the memory at Allocation&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ut_free_and_track
id|acpi_ut_free_and_track
(paren
r_void
op_star
id|allocation
comma
id|u32
id|component
comma
r_char
op_star
id|module
comma
id|u32
id|line
)paren
(brace
id|acpi_debug_mem_block
op_star
id|debug_block
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ut_free&quot;
comma
id|allocation
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|allocation
)paren
(brace
id|_ACPI_REPORT_ERROR
(paren
id|module
comma
id|line
comma
id|component
comma
(paren
l_string|&quot;acpi_ut_free: Attempt to delete a NULL address&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
id|debug_block
op_assign
id|ACPI_CAST_PTR
(paren
id|acpi_debug_mem_block
comma
(paren
(paren
(paren
r_char
op_star
)paren
id|allocation
)paren
op_minus
r_sizeof
(paren
id|acpi_debug_mem_header
)paren
)paren
)paren
suffix:semicolon
id|acpi_gbl_memory_lists
(braket
id|ACPI_MEM_LIST_GLOBAL
)braket
dot
id|total_freed
op_increment
suffix:semicolon
id|acpi_gbl_memory_lists
(braket
id|ACPI_MEM_LIST_GLOBAL
)braket
dot
id|current_total_size
op_sub_assign
id|debug_block-&gt;size
suffix:semicolon
id|status
op_assign
id|acpi_ut_remove_allocation
(paren
id|ACPI_MEM_LIST_GLOBAL
comma
id|debug_block
comma
id|component
comma
id|module
comma
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not free memory, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
id|acpi_os_free
(paren
id|debug_block
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;%p freed&bslash;n&quot;
comma
id|allocation
)paren
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_find_allocation&n; *&n; * PARAMETERS:  Allocation             - Address of allocated memory&n; *&n; * RETURN:      A list element if found; NULL otherwise.&n; *&n; * DESCRIPTION: Searches for an element in the global allocation tracking list.&n; *&n; ******************************************************************************/
id|acpi_debug_mem_block
op_star
DECL|function|acpi_ut_find_allocation
id|acpi_ut_find_allocation
(paren
id|u32
id|list_id
comma
r_void
op_star
id|allocation
)paren
(brace
id|acpi_debug_mem_block
op_star
id|element
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_id
OG
id|ACPI_MEM_LIST_MAX
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|element
op_assign
id|acpi_gbl_memory_lists
(braket
id|list_id
)braket
dot
id|list_head
suffix:semicolon
multiline_comment|/* Search for the address. */
r_while
c_loop
(paren
id|element
)paren
(brace
r_if
c_cond
(paren
id|element
op_eq
id|allocation
)paren
(brace
r_return
(paren
id|element
)paren
suffix:semicolon
)brace
id|element
op_assign
id|element-&gt;next
suffix:semicolon
)brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_track_allocation&n; *&n; * PARAMETERS:  Allocation          - Address of allocated memory&n; *              Size                - Size of the allocation&n; *              alloc_type          - MEM_MALLOC or MEM_CALLOC&n; *              Component           - Component type of caller&n; *              Module              - Source file name of caller&n; *              Line                - Line number of caller&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Inserts an element into the global allocation tracking list.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_track_allocation
id|acpi_ut_track_allocation
(paren
id|u32
id|list_id
comma
id|acpi_debug_mem_block
op_star
id|allocation
comma
id|acpi_size
id|size
comma
id|u8
id|alloc_type
comma
id|u32
id|component
comma
r_char
op_star
id|module
comma
id|u32
id|line
)paren
(brace
id|acpi_memory_list
op_star
id|mem_list
suffix:semicolon
id|acpi_debug_mem_block
op_star
id|element
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ut_track_allocation&quot;
comma
id|allocation
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_id
OG
id|ACPI_MEM_LIST_MAX
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|mem_list
op_assign
op_amp
id|acpi_gbl_memory_lists
(braket
id|list_id
)braket
suffix:semicolon
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_MEMORY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Search list for this address to make sure it is not already on the list.&n;&t; * This will catch several kinds of problems.&n;&t; */
id|element
op_assign
id|acpi_ut_find_allocation
(paren
id|list_id
comma
id|allocation
)paren
suffix:semicolon
r_if
c_cond
(paren
id|element
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;ut_track_allocation: Allocation already present in list! (%p)&bslash;n&quot;
comma
id|allocation
)paren
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Element %p Address %p&bslash;n&quot;
comma
id|element
comma
id|allocation
)paren
)paren
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Fill in the instance data. */
id|allocation-&gt;size
op_assign
(paren
id|u32
)paren
id|size
suffix:semicolon
id|allocation-&gt;alloc_type
op_assign
id|alloc_type
suffix:semicolon
id|allocation-&gt;component
op_assign
id|component
suffix:semicolon
id|allocation-&gt;line
op_assign
id|line
suffix:semicolon
id|ACPI_STRNCPY
(paren
id|allocation-&gt;module
comma
id|module
comma
id|ACPI_MAX_MODULE_NAME
)paren
suffix:semicolon
multiline_comment|/* Insert at list head */
r_if
c_cond
(paren
id|mem_list-&gt;list_head
)paren
(brace
(paren
(paren
id|acpi_debug_mem_block
op_star
)paren
(paren
id|mem_list-&gt;list_head
)paren
)paren
op_member_access_from_pointer
id|previous
op_assign
id|allocation
suffix:semicolon
)brace
id|allocation-&gt;next
op_assign
id|mem_list-&gt;list_head
suffix:semicolon
id|allocation-&gt;previous
op_assign
l_int|NULL
suffix:semicolon
id|mem_list-&gt;list_head
op_assign
id|allocation
suffix:semicolon
id|unlock_and_exit
suffix:colon
id|status
op_assign
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_MEMORY
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_remove_allocation&n; *&n; * PARAMETERS:  Allocation          - Address of allocated memory&n; *              Component           - Component type of caller&n; *              Module              - Source file name of caller&n; *              Line                - Line number of caller&n; *&n; * RETURN:&n; *&n; * DESCRIPTION: Deletes an element from the global allocation tracking list.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_remove_allocation
id|acpi_ut_remove_allocation
(paren
id|u32
id|list_id
comma
id|acpi_debug_mem_block
op_star
id|allocation
comma
id|u32
id|component
comma
r_char
op_star
id|module
comma
id|u32
id|line
)paren
(brace
id|acpi_memory_list
op_star
id|mem_list
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_remove_allocation&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_id
OG
id|ACPI_MEM_LIST_MAX
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|mem_list
op_assign
op_amp
id|acpi_gbl_memory_lists
(braket
id|list_id
)braket
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|mem_list-&gt;list_head
)paren
(brace
multiline_comment|/* No allocations! */
id|_ACPI_REPORT_ERROR
(paren
id|module
comma
id|line
comma
id|component
comma
(paren
l_string|&quot;ut_remove_allocation: Empty allocation list, nothing to free!&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_MEMORY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Unlink */
r_if
c_cond
(paren
id|allocation-&gt;previous
)paren
(brace
(paren
id|allocation-&gt;previous
)paren
op_member_access_from_pointer
id|next
op_assign
id|allocation-&gt;next
suffix:semicolon
)brace
r_else
(brace
id|mem_list-&gt;list_head
op_assign
id|allocation-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|allocation-&gt;next
)paren
(brace
(paren
id|allocation-&gt;next
)paren
op_member_access_from_pointer
id|previous
op_assign
id|allocation-&gt;previous
suffix:semicolon
)brace
multiline_comment|/* Mark the segment as deleted */
id|ACPI_MEMSET
(paren
op_amp
id|allocation-&gt;user_space
comma
l_int|0xEA
comma
id|allocation-&gt;size
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;Freeing size %X&bslash;n&quot;
comma
id|allocation-&gt;size
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_MEMORY
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_dump_allocation_info&n; *&n; * PARAMETERS:&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Print some info about the outstanding allocations.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ut_dump_allocation_info
id|acpi_ut_dump_allocation_info
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t;acpi_memory_list        *mem_list;&n;*/
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_dump_allocation_info&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;ACPI_DEBUG_PRINT (TRACE_ALLOCATIONS | TRACE_TABLES,&n;&t;&t;&t;  (&quot;%30s: %4d (%3d Kb)&bslash;n&quot;, &quot;Current allocations&quot;,&n;&t;&t;&t;  mem_list-&gt;current_count,&n;&t;&t;&t;  ROUND_UP_TO_1K (mem_list-&gt;current_size)));&n;&n;&t;ACPI_DEBUG_PRINT (TRACE_ALLOCATIONS | TRACE_TABLES,&n;&t;&t;&t;  (&quot;%30s: %4d (%3d Kb)&bslash;n&quot;, &quot;Max concurrent allocations&quot;,&n;&t;&t;&t;  mem_list-&gt;max_concurrent_count,&n;&t;&t;&t;  ROUND_UP_TO_1K (mem_list-&gt;max_concurrent_size)));&n;&n;&n;&t;ACPI_DEBUG_PRINT (TRACE_ALLOCATIONS | TRACE_TABLES,&n;&t;&t;&t;  (&quot;%30s: %4d (%3d Kb)&bslash;n&quot;, &quot;Total (all) internal objects&quot;,&n;&t;&t;&t;  running_object_count,&n;&t;&t;&t;  ROUND_UP_TO_1K (running_object_size)));&n;&n;&t;ACPI_DEBUG_PRINT (TRACE_ALLOCATIONS | TRACE_TABLES,&n;&t;&t;&t;  (&quot;%30s: %4d (%3d Kb)&bslash;n&quot;, &quot;Total (all) allocations&quot;,&n;&t;&t;&t;  running_alloc_count,&n;&t;&t;&t;  ROUND_UP_TO_1K (running_alloc_size)));&n;&n;&n;&t;ACPI_DEBUG_PRINT (TRACE_ALLOCATIONS | TRACE_TABLES,&n;&t;&t;&t;  (&quot;%30s: %4d (%3d Kb)&bslash;n&quot;, &quot;Current Nodes&quot;,&n;&t;&t;&t;  acpi_gbl_current_node_count,&n;&t;&t;&t;  ROUND_UP_TO_1K (acpi_gbl_current_node_size)));&n;&n;&t;ACPI_DEBUG_PRINT (TRACE_ALLOCATIONS | TRACE_TABLES,&n;&t;&t;&t;  (&quot;%30s: %4d (%3d Kb)&bslash;n&quot;, &quot;Max Nodes&quot;,&n;&t;&t;&t;  acpi_gbl_max_concurrent_node_count,&n;&t;&t;&t;  ROUND_UP_TO_1K ((acpi_gbl_max_concurrent_node_count * sizeof (acpi_namespace_node)))));&n;*/
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_dump_allocations&n; *&n; * PARAMETERS:  Component           - Component(s) to dump info for.&n; *              Module              - Module to dump info for.  NULL means all.&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Print a list of all outstanding allocations.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ut_dump_allocations
id|acpi_ut_dump_allocations
(paren
id|u32
id|component
comma
r_char
op_star
id|module
)paren
(brace
id|acpi_debug_mem_block
op_star
id|element
suffix:semicolon
id|acpi_descriptor
op_star
id|descriptor
suffix:semicolon
id|u32
id|num_outstanding
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_dump_allocations&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Walk the allocation list.&n;&t; */
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_MEMORY
)paren
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|element
op_assign
id|acpi_gbl_memory_lists
(braket
l_int|0
)braket
dot
id|list_head
suffix:semicolon
r_while
c_loop
(paren
id|element
)paren
(brace
r_if
c_cond
(paren
(paren
id|element-&gt;component
op_amp
id|component
)paren
op_logical_and
(paren
(paren
id|module
op_eq
l_int|NULL
)paren
op_logical_or
(paren
l_int|0
op_eq
id|ACPI_STRCMP
(paren
id|module
comma
id|element-&gt;module
)paren
)paren
)paren
)paren
(brace
multiline_comment|/* Ignore allocated objects that are in a cache */
id|descriptor
op_assign
id|ACPI_CAST_PTR
(paren
id|acpi_descriptor
comma
op_amp
id|element-&gt;user_space
)paren
suffix:semicolon
r_if
c_cond
(paren
id|descriptor-&gt;descriptor_id
op_ne
id|ACPI_DESC_TYPE_CACHED
)paren
(brace
id|acpi_os_printf
(paren
l_string|&quot;%p Len %04X %9.9s-%d &quot;
comma
id|descriptor
comma
id|element-&gt;size
comma
id|element-&gt;module
comma
id|element-&gt;line
)paren
suffix:semicolon
multiline_comment|/* Most of the elements will be internal objects. */
r_switch
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|descriptor
)paren
)paren
(brace
r_case
id|ACPI_DESC_TYPE_OPERAND
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;obj_type %12.12s R%hd&quot;
comma
id|acpi_ut_get_type_name
(paren
id|descriptor-&gt;object.common.type
)paren
comma
id|descriptor-&gt;object.common.reference_count
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_PARSER
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;parse_obj aml_opcode %04hX&quot;
comma
id|descriptor-&gt;op.asl.aml_opcode
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_NAMED
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Node %4.4s&quot;
comma
id|descriptor-&gt;node.name.ascii
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_STATE
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;Untyped state_obj&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_STATE_UPDATE
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;UPDATE state_obj&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_STATE_PACKAGE
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;PACKAGE state_obj&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_STATE_CONTROL
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;CONTROL state_obj&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_STATE_RPSCOPE
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;ROOT-PARSE-SCOPE state_obj&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_STATE_PSCOPE
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;PARSE-SCOPE state_obj&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_STATE_WSCOPE
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;WALK-SCOPE state_obj&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_STATE_RESULT
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;RESULT state_obj&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_STATE_NOTIFY
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;NOTIFY state_obj&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_STATE_THREAD
suffix:colon
id|acpi_os_printf
(paren
l_string|&quot;THREAD state_obj&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* All types should appear above */
r_break
suffix:semicolon
)brace
id|acpi_os_printf
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|num_outstanding
op_increment
suffix:semicolon
)brace
)brace
id|element
op_assign
id|element-&gt;next
suffix:semicolon
)brace
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_MEMORY
)paren
suffix:semicolon
multiline_comment|/* Print summary */
r_if
c_cond
(paren
op_logical_neg
id|num_outstanding
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;No outstanding allocations.&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;%d(%X) Outstanding allocations&bslash;n&quot;
comma
id|num_outstanding
comma
id|num_outstanding
)paren
)paren
suffix:semicolon
)brace
id|return_VOID
suffix:semicolon
)brace
macro_line|#endif  /* #ifdef ACPI_DBG_TRACK_ALLOCATIONS */
eof
