multiline_comment|/*&n; *  Digital Audio (PCM) abstract layer&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &lt;sound/info.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
DECL|variable|preallocate_dma
r_static
r_int
id|preallocate_dma
op_assign
l_int|1
suffix:semicolon
id|module_param
c_func
(paren
id|preallocate_dma
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|preallocate_dma
comma
l_string|&quot;Preallocate DMA memory when the PCM devices are initialized.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|preallocate_dma
comma
id|SNDRV_BOOLEAN_TRUE_DESC
)paren
suffix:semicolon
DECL|variable|maximum_substreams
r_static
r_int
id|maximum_substreams
op_assign
l_int|4
suffix:semicolon
id|module_param
c_func
(paren
id|maximum_substreams
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|maximum_substreams
comma
l_string|&quot;Maximum substreams with preallocated DMA memory.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|maximum_substreams
comma
id|SNDRV_BOOLEAN_TRUE_DESC
)paren
suffix:semicolon
DECL|variable|snd_minimum_buffer
r_const
r_static
r_int
id|snd_minimum_buffer
op_assign
l_int|16384
suffix:semicolon
multiline_comment|/*&n; * try to allocate as the large pages as possible.&n; * stores the resultant memory size in *res_size.&n; *&n; * the minimum size is snd_minimum_buffer.  it should be power of 2.&n; */
DECL|function|preallocate_pcm_pages
r_static
r_int
id|preallocate_pcm_pages
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
r_int
id|size
)paren
(brace
r_struct
id|snd_dma_buffer
op_star
id|dmab
op_assign
op_amp
id|substream-&gt;dma_buffer
suffix:semicolon
r_int
id|err
suffix:semicolon
id|snd_assert
c_func
(paren
id|size
OG
l_int|0
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* already reserved? */
r_if
c_cond
(paren
id|snd_dma_get_reserved
c_func
(paren
op_amp
id|substream-&gt;dma_device
comma
id|dmab
)paren
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|dmab-&gt;bytes
op_ge
id|size
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* yes */
multiline_comment|/* no, reset the reserved block */
multiline_comment|/* if we can find bigger pages below, this block will be&n;&t;&t; * automatically removed in snd_dma_set_reserved().&n;&t;&t; */
id|snd_dma_free_reserved
c_func
(paren
op_amp
id|substream-&gt;dma_device
)paren
suffix:semicolon
id|dmab-&gt;bytes
op_assign
l_int|0
suffix:semicolon
)brace
r_do
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_dma_alloc_pages
c_func
(paren
op_amp
id|substream-&gt;dma_device
comma
id|size
comma
id|dmab
)paren
)paren
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|err
op_ne
op_minus
id|ENOMEM
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* fatal error */
)brace
r_else
(brace
multiline_comment|/* remember this one */
id|snd_dma_set_reserved
c_func
(paren
op_amp
id|substream-&gt;dma_device
comma
id|dmab
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|size
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
op_ge
id|snd_minimum_buffer
)paren
suffix:semicolon
id|dmab-&gt;bytes
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* tell error */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * release the preallocated buffer if not yet done.&n; */
DECL|function|snd_pcm_lib_preallocate_dma_free
r_static
r_void
id|snd_pcm_lib_preallocate_dma_free
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_if
c_cond
(paren
id|substream-&gt;dma_buffer.area
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|snd_dma_free_reserved
c_func
(paren
op_amp
id|substream-&gt;dma_device
)paren
suffix:semicolon
id|substream-&gt;dma_buffer.area
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/**&n; * snd_pcm_lib_preallocate_free - release the preallocated buffer of the specified substream.&n; * @substream: the pcm substream instance&n; *&n; * Releases the pre-allocated buffer of the given substream.&n; *&n; * Returns zero if successful, or a negative error code on failure.&n; */
DECL|function|snd_pcm_lib_preallocate_free
r_int
id|snd_pcm_lib_preallocate_free
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|snd_pcm_lib_preallocate_dma_free
c_func
(paren
id|substream
)paren
suffix:semicolon
r_if
c_cond
(paren
id|substream-&gt;proc_prealloc_entry
)paren
(brace
id|snd_info_unregister
c_func
(paren
id|substream-&gt;proc_prealloc_entry
)paren
suffix:semicolon
id|substream-&gt;proc_prealloc_entry
op_assign
l_int|NULL
suffix:semicolon
)brace
id|substream-&gt;dma_device.type
op_assign
id|SNDRV_DMA_TYPE_UNKNOWN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * snd_pcm_lib_preallocate_free_for_all - release all pre-allocated buffers on the pcm&n; * @pcm: the pcm instance&n; *&n; * Releases all the pre-allocated buffers on the given pcm.&n; *&n; * Returns zero if successful, or a negative error code on failure.&n; */
DECL|function|snd_pcm_lib_preallocate_free_for_all
r_int
id|snd_pcm_lib_preallocate_free_for_all
c_func
(paren
id|snd_pcm_t
op_star
id|pcm
)paren
(brace
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
r_int
id|stream
suffix:semicolon
r_for
c_loop
(paren
id|stream
op_assign
l_int|0
suffix:semicolon
id|stream
OL
l_int|2
suffix:semicolon
id|stream
op_increment
)paren
r_for
c_loop
(paren
id|substream
op_assign
id|pcm-&gt;streams
(braket
id|stream
)braket
dot
id|substream
suffix:semicolon
id|substream
suffix:semicolon
id|substream
op_assign
id|substream-&gt;next
)paren
id|snd_pcm_lib_preallocate_free
c_func
(paren
id|substream
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * read callback for prealloc proc file&n; *&n; * prints the current allocated size in kB.&n; */
DECL|function|snd_pcm_lib_preallocate_proc_read
r_static
r_void
id|snd_pcm_lib_preallocate_proc_read
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
id|snd_info_buffer_t
op_star
id|buffer
)paren
(brace
id|snd_pcm_substream_t
op_star
id|substream
op_assign
(paren
id|snd_pcm_substream_t
op_star
)paren
id|entry-&gt;private_data
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%lu&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|substream-&gt;dma_buffer.bytes
op_div
l_int|1024
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * write callback for prealloc proc file&n; *&n; * accepts the preallocation size in kB.&n; */
DECL|function|snd_pcm_lib_preallocate_proc_write
r_static
r_void
id|snd_pcm_lib_preallocate_proc_write
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
id|snd_info_buffer_t
op_star
id|buffer
)paren
(brace
id|snd_pcm_substream_t
op_star
id|substream
op_assign
(paren
id|snd_pcm_substream_t
op_star
)paren
id|entry-&gt;private_data
suffix:semicolon
r_char
id|line
(braket
l_int|64
)braket
comma
id|str
(braket
l_int|64
)braket
suffix:semicolon
r_int
id|size
suffix:semicolon
r_struct
id|snd_dma_buffer
id|new_dmab
suffix:semicolon
r_if
c_cond
(paren
id|substream-&gt;runtime
)paren
(brace
id|buffer-&gt;error
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|snd_info_get_line
c_func
(paren
id|buffer
comma
id|line
comma
r_sizeof
(paren
id|line
)paren
)paren
)paren
(brace
id|snd_info_get_str
c_func
(paren
id|str
comma
id|line
comma
r_sizeof
(paren
id|str
)paren
)paren
suffix:semicolon
id|size
op_assign
id|simple_strtoul
c_func
(paren
id|str
comma
l_int|NULL
comma
l_int|10
)paren
op_star
l_int|1024
suffix:semicolon
r_if
c_cond
(paren
(paren
id|size
op_ne
l_int|0
op_logical_and
id|size
OL
l_int|8192
)paren
op_logical_or
id|size
OG
id|substream-&gt;dma_max
)paren
(brace
id|buffer-&gt;error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|substream-&gt;dma_buffer.bytes
op_eq
id|size
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|new_dmab
comma
l_int|0
comma
r_sizeof
(paren
id|new_dmab
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|snd_dma_alloc_pages
c_func
(paren
op_amp
id|substream-&gt;dma_device
comma
id|size
comma
op_amp
id|new_dmab
)paren
OL
l_int|0
)paren
(brace
id|buffer-&gt;error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_return
suffix:semicolon
)brace
id|substream-&gt;buffer_bytes_max
op_assign
id|size
suffix:semicolon
id|snd_dma_free_reserved
c_func
(paren
op_amp
id|substream-&gt;dma_device
)paren
suffix:semicolon
)brace
r_else
(brace
id|substream-&gt;buffer_bytes_max
op_assign
id|UINT_MAX
suffix:semicolon
)brace
id|snd_dma_set_reserved
c_func
(paren
op_amp
id|substream-&gt;dma_device
comma
op_amp
id|new_dmab
)paren
suffix:semicolon
id|substream-&gt;dma_buffer
op_assign
id|new_dmab
suffix:semicolon
)brace
r_else
(brace
id|buffer-&gt;error
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * pre-allocate the buffer and create a proc file for the substream&n; */
DECL|function|snd_pcm_lib_preallocate_pages1
r_static
r_int
id|snd_pcm_lib_preallocate_pages1
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
r_int
id|size
comma
r_int
id|max
)paren
(brace
id|snd_info_entry_t
op_star
id|entry
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|substream-&gt;dma_buffer
comma
l_int|0
comma
r_sizeof
(paren
id|substream-&gt;dma_buffer
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|0
op_logical_and
id|preallocate_dma
op_logical_and
id|substream-&gt;number
OL
id|maximum_substreams
)paren
id|preallocate_pcm_pages
c_func
(paren
id|substream
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|substream-&gt;dma_buffer.bytes
OG
l_int|0
)paren
id|substream-&gt;buffer_bytes_max
op_assign
id|substream-&gt;dma_buffer.bytes
suffix:semicolon
id|substream-&gt;dma_max
op_assign
id|max
suffix:semicolon
r_if
c_cond
(paren
(paren
id|entry
op_assign
id|snd_info_create_card_entry
c_func
(paren
id|substream-&gt;pcm-&gt;card
comma
l_string|&quot;prealloc&quot;
comma
id|substream-&gt;proc_root
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|entry-&gt;c.text.read_size
op_assign
l_int|64
suffix:semicolon
id|entry-&gt;c.text.read
op_assign
id|snd_pcm_lib_preallocate_proc_read
suffix:semicolon
id|entry-&gt;c.text.write_size
op_assign
l_int|64
suffix:semicolon
id|entry-&gt;c.text.write
op_assign
id|snd_pcm_lib_preallocate_proc_write
suffix:semicolon
id|entry-&gt;private_data
op_assign
id|substream
suffix:semicolon
r_if
c_cond
(paren
id|snd_info_register
c_func
(paren
id|entry
)paren
OL
l_int|0
)paren
(brace
id|snd_info_free_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
id|entry
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|substream-&gt;proc_prealloc_entry
op_assign
id|entry
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * set up the unique pcm id&n; */
DECL|function|setup_pcm_id
r_static
r_inline
r_void
id|setup_pcm_id
c_func
(paren
id|snd_pcm_substream_t
op_star
id|subs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|subs-&gt;dma_device.id
)paren
(brace
id|subs-&gt;dma_device.id
op_assign
id|subs-&gt;pcm-&gt;device
op_lshift
l_int|16
op_or
id|subs-&gt;stream
op_lshift
l_int|8
op_or
(paren
id|subs-&gt;number
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|subs-&gt;dma_device.type
op_eq
id|SNDRV_DMA_TYPE_CONTINUOUS
op_logical_or
id|subs-&gt;dma_device.dev
op_eq
l_int|NULL
)paren
id|subs-&gt;dma_device.id
op_or_assign
(paren
id|subs-&gt;pcm-&gt;card-&gt;number
op_plus
l_int|1
)paren
op_lshift
l_int|24
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; * snd_pcm_lib_preallocate_pages - pre-allocation for the given DMA type&n; * @substream: the pcm substream instance&n; * @type: DMA type (SNDRV_DMA_TYPE_*)&n; * @data: DMA type dependant data&n; * @size: the requested pre-allocation size in bytes&n; * @max: the max. allowed pre-allocation size&n; *&n; * Do pre-allocation for the given DMA type.&n; *&n; * Returns zero if successful, or a negative error code on failure.&n; */
DECL|function|snd_pcm_lib_preallocate_pages
r_int
id|snd_pcm_lib_preallocate_pages
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
r_int
id|type
comma
r_struct
id|device
op_star
id|data
comma
r_int
id|size
comma
r_int
id|max
)paren
(brace
id|substream-&gt;dma_device.type
op_assign
id|type
suffix:semicolon
id|substream-&gt;dma_device.dev
op_assign
id|data
suffix:semicolon
id|setup_pcm_id
c_func
(paren
id|substream
)paren
suffix:semicolon
r_return
id|snd_pcm_lib_preallocate_pages1
c_func
(paren
id|substream
comma
id|size
comma
id|max
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * snd_pcm_lib_preallocate_pages_for_all - pre-allocation for continous memory type (all substreams)&n; * @substream: the pcm substream instance&n; * @type: DMA type (SNDRV_DMA_TYPE_*)&n; * @data: DMA type dependant data&n; * @size: the requested pre-allocation size in bytes&n; * @max: the max. allowed pre-allocation size&n; *&n; * Do pre-allocation to all substreams of the given pcm for the&n; * specified DMA type.&n; *&n; * Returns zero if successful, or a negative error code on failure.&n; */
DECL|function|snd_pcm_lib_preallocate_pages_for_all
r_int
id|snd_pcm_lib_preallocate_pages_for_all
c_func
(paren
id|snd_pcm_t
op_star
id|pcm
comma
r_int
id|type
comma
r_void
op_star
id|data
comma
r_int
id|size
comma
r_int
id|max
)paren
(brace
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
r_int
id|stream
comma
id|err
suffix:semicolon
r_for
c_loop
(paren
id|stream
op_assign
l_int|0
suffix:semicolon
id|stream
OL
l_int|2
suffix:semicolon
id|stream
op_increment
)paren
r_for
c_loop
(paren
id|substream
op_assign
id|pcm-&gt;streams
(braket
id|stream
)braket
dot
id|substream
suffix:semicolon
id|substream
suffix:semicolon
id|substream
op_assign
id|substream-&gt;next
)paren
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_pcm_lib_preallocate_pages
c_func
(paren
id|substream
comma
id|type
comma
id|data
comma
id|size
comma
id|max
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * snd_pcm_sgbuf_ops_page - get the page struct at the given offset&n; * @substream: the pcm substream instance&n; * @offset: the buffer offset&n; *&n; * Returns the page struct at the given buffer offset.&n; * Used as the page callback of PCM ops.&n; */
DECL|function|snd_pcm_sgbuf_ops_page
r_struct
id|page
op_star
id|snd_pcm_sgbuf_ops_page
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
r_int
r_int
id|offset
)paren
(brace
r_struct
id|snd_sg_buf
op_star
id|sgbuf
op_assign
id|snd_pcm_substream_sgbuf
c_func
(paren
id|substream
)paren
suffix:semicolon
r_int
r_int
id|idx
op_assign
id|offset
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
(paren
r_int
r_int
)paren
id|sgbuf-&gt;pages
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|sgbuf-&gt;page_table
(braket
id|idx
)braket
suffix:semicolon
)brace
multiline_comment|/**&n; * snd_pcm_lib_malloc_pages - allocate the DMA buffer&n; * @substream: the substream to allocate the DMA buffer to&n; * @size: the requested buffer size in bytes&n; *&n; * Allocates the DMA buffer on the BUS type given by&n; * snd_pcm_lib_preallocate_xxx_pages().&n; *&n; * Returns 1 if the buffer is changed, 0 if not changed, or a negative&n; * code on failure.&n; */
DECL|function|snd_pcm_lib_malloc_pages
r_int
id|snd_pcm_lib_malloc_pages
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
r_int
id|size
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
suffix:semicolon
r_struct
id|snd_dma_buffer
op_star
id|dmab
op_assign
l_int|NULL
suffix:semicolon
id|snd_assert
c_func
(paren
id|substream-&gt;dma_device.type
op_ne
id|SNDRV_DMA_TYPE_UNKNOWN
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|substream
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
id|snd_assert
c_func
(paren
id|runtime
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|runtime-&gt;dma_buffer_p
)paren
(brace
multiline_comment|/* perphaps, we might free the large DMA memory region&n;&t;&t;   to save some space here, but the actual solution&n;&t;&t;   costs us less time */
r_if
c_cond
(paren
id|runtime-&gt;dma_buffer_p-&gt;bytes
op_ge
id|size
)paren
(brace
id|runtime-&gt;dma_bytes
op_assign
id|size
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* ok, do not change */
)brace
id|snd_pcm_lib_free_pages
c_func
(paren
id|substream
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|substream-&gt;dma_buffer.area
op_ne
l_int|NULL
op_logical_and
id|substream-&gt;dma_buffer.bytes
op_ge
id|size
)paren
(brace
id|dmab
op_assign
op_amp
id|substream-&gt;dma_buffer
suffix:semicolon
multiline_comment|/* use the pre-allocated buffer */
)brace
r_else
(brace
id|dmab
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
op_star
id|dmab
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dmab
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|snd_dma_alloc_pages
c_func
(paren
op_amp
id|substream-&gt;dma_device
comma
id|size
comma
id|dmab
)paren
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|dmab
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
id|snd_pcm_set_runtime_buffer
c_func
(paren
id|substream
comma
id|dmab
)paren
suffix:semicolon
id|runtime-&gt;dma_bytes
op_assign
id|size
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* area was changed */
)brace
multiline_comment|/**&n; * snd_pcm_lib_free_pages - release the allocated DMA buffer.&n; * @substream: the substream to release the DMA buffer&n; *&n; * Releases the DMA buffer allocated via snd_pcm_lib_malloc_pages().&n; *&n; * Returns zero if successful, or a negative error code on failure.&n; */
DECL|function|snd_pcm_lib_free_pages
r_int
id|snd_pcm_lib_free_pages
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
suffix:semicolon
id|snd_assert
c_func
(paren
id|substream
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
id|snd_assert
c_func
(paren
id|runtime
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|runtime-&gt;dma_area
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|runtime-&gt;dma_buffer_p
op_ne
op_amp
id|substream-&gt;dma_buffer
)paren
(brace
multiline_comment|/* it&squot;s a newly allocated buffer.  release it now. */
id|snd_dma_free_pages
c_func
(paren
op_amp
id|substream-&gt;dma_device
comma
id|runtime-&gt;dma_buffer_p
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|runtime-&gt;dma_buffer_p
)paren
suffix:semicolon
)brace
id|snd_pcm_set_runtime_buffer
c_func
(paren
id|substream
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
