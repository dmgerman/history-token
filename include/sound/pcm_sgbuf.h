macro_line|#ifndef __SOUND_PCM_SGBUF_H
DECL|macro|__SOUND_PCM_SGBUF_H
mdefine_line|#define __SOUND_PCM_SGBUF_H
multiline_comment|/*&n; * Scatter-Gather PCM access&n; *&n; *  Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|struct|snd_sg_page
r_struct
id|snd_sg_page
(brace
DECL|member|buf
r_void
op_star
id|buf
suffix:semicolon
DECL|member|addr
id|dma_addr_t
id|addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|snd_sg_buf
r_struct
id|snd_sg_buf
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* allocated byte size (= runtime-&gt;dma_bytes) */
DECL|member|pages
r_int
id|pages
suffix:semicolon
multiline_comment|/* allocated pages */
DECL|member|tblsize
r_int
id|tblsize
suffix:semicolon
multiline_comment|/* allocated table size */
DECL|member|table
r_struct
id|snd_sg_page
op_star
id|table
suffix:semicolon
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|snd_pcm_sgbuf_t
r_typedef
r_struct
id|snd_sg_buf
id|snd_pcm_sgbuf_t
suffix:semicolon
multiline_comment|/* for magic cast */
multiline_comment|/*&n; * return the pages matching with the given byte size&n; */
DECL|function|snd_pcm_sgbuf_pages
r_static
r_inline
r_int
r_int
id|snd_pcm_sgbuf_pages
c_func
(paren
r_int
id|size
)paren
(brace
r_return
(paren
id|size
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
)brace
multiline_comment|/*&n; * return the physical address at the corresponding offset&n; */
DECL|function|snd_pcm_sgbuf_get_addr
r_static
r_inline
id|dma_addr_t
id|snd_pcm_sgbuf_get_addr
c_func
(paren
r_struct
id|snd_sg_buf
op_star
id|sgbuf
comma
r_int
id|offset
)paren
(brace
r_return
id|sgbuf-&gt;table
(braket
id|offset
op_rshift
id|PAGE_SHIFT
)braket
dot
id|addr
op_plus
id|offset
op_mod
id|PAGE_SIZE
suffix:semicolon
)brace
r_int
id|snd_pcm_sgbuf_init
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
id|tblsize
)paren
suffix:semicolon
r_int
id|snd_pcm_sgbuf_delete
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
suffix:semicolon
r_int
id|snd_pcm_sgbuf_alloc
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
r_int
id|size
)paren
suffix:semicolon
r_int
id|snd_pcm_sgbuf_free
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
suffix:semicolon
r_int
id|snd_pcm_sgbuf_ops_copy_playback
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
r_int
id|channel
comma
id|snd_pcm_uframes_t
id|hwoff
comma
r_void
op_star
id|buf
comma
id|snd_pcm_uframes_t
id|count
)paren
suffix:semicolon
r_int
id|snd_pcm_sgbuf_ops_copy_capture
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
r_int
id|channel
comma
id|snd_pcm_uframes_t
id|hwoff
comma
r_void
op_star
id|buf
comma
id|snd_pcm_uframes_t
id|count
)paren
suffix:semicolon
r_int
id|snd_pcm_sgbuf_ops_silence
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
r_int
id|channel
comma
id|snd_pcm_uframes_t
id|hwoff
comma
id|snd_pcm_uframes_t
id|count
)paren
suffix:semicolon
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
suffix:semicolon
DECL|macro|_snd_pcm_substream_sgbuf
mdefine_line|#define _snd_pcm_substream_sgbuf(substream) ((substream)-&gt;dma_private)
DECL|macro|snd_pcm_substream_sgbuf
mdefine_line|#define snd_pcm_substream_sgbuf(substream) snd_magic_cast(snd_pcm_sgbuf_t, _snd_pcm_substream_sgbuf(substream), return -ENXIO)
macro_line|#endif /* __SOUND_PCM_SGBUF_H */
eof
