multiline_comment|/* Linux driver for Philips webcam&n;   Decompression frontend.&n;   (C) 1999-2003 Nemosoft Unv.&n;   (C) 2004      Luc Saillard (luc@saillard.org)&n;&n;   NOTE: this version of pwc is an unofficial (modified) release of pwc &amp; pcwx&n;   driver and thus may have bugs that are not present in the original version.&n;   Please send bug reports and support requests to &lt;luc@saillard.org&gt;.&n;   The decompression routines have been implemented by reverse-engineering the&n;   Nemosoft binary pwcx module. Caveat emptor.&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;*/
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &quot;pwc.h&quot;
macro_line|#include &quot;pwc-uncompress.h&quot;
macro_line|#include &quot;pwc-dec1.h&quot;
macro_line|#include &quot;pwc-dec23.h&quot;
DECL|function|pwc_decompress
r_int
id|pwc_decompress
c_func
(paren
r_struct
id|pwc_device
op_star
id|pdev
)paren
(brace
r_struct
id|pwc_frame_buf
op_star
id|fbuf
suffix:semicolon
r_int
id|n
comma
id|line
comma
id|col
comma
id|stride
suffix:semicolon
r_void
op_star
id|yuv
comma
op_star
id|image
suffix:semicolon
id|u16
op_star
id|src
suffix:semicolon
id|u16
op_star
id|dsty
comma
op_star
id|dstu
comma
op_star
id|dstv
suffix:semicolon
r_if
c_cond
(paren
id|pdev
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
macro_line|#if defined(__KERNEL__) &amp;&amp; defined(PWC_MAGIC)
r_if
c_cond
(paren
id|pdev-&gt;magic
op_ne
id|PWC_MAGIC
)paren
(brace
id|Err
c_func
(paren
l_string|&quot;pwc_decompress(): magic failed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
macro_line|#endif
id|fbuf
op_assign
id|pdev-&gt;read_frame
suffix:semicolon
r_if
c_cond
(paren
id|fbuf
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|image
op_assign
id|pdev-&gt;image_ptr
(braket
id|pdev-&gt;fill_image
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|image
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|yuv
op_assign
id|fbuf-&gt;data
op_plus
id|pdev-&gt;frame_header_size
suffix:semicolon
multiline_comment|/* Skip header */
multiline_comment|/* Raw format; that&squot;s easy... */
r_if
c_cond
(paren
id|pdev-&gt;vpalette
op_eq
id|VIDEO_PALETTE_RAW
)paren
(brace
id|memcpy
c_func
(paren
id|image
comma
id|yuv
comma
id|pdev-&gt;frame_size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pdev-&gt;vbandlength
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Uncompressed mode. We copy the data into the output buffer,&n;&t;&t;   using the viewport size (which may be larger than the image&n;&t;&t;   size). Unfortunately we have to do a bit of byte stuffing&n;&t;&t;   to get the desired output format/size.&n;&t;&t; */
multiline_comment|/*&n;&t;&t;&t; * We do some byte shuffling here to go from the&n;&t;&t;&t; * native format to YUV420P.&n;&t;&t;&t; */
id|src
op_assign
(paren
id|u16
op_star
)paren
id|yuv
suffix:semicolon
id|n
op_assign
id|pdev-&gt;view.x
op_star
id|pdev-&gt;view.y
suffix:semicolon
multiline_comment|/* offset in Y plane */
id|stride
op_assign
id|pdev-&gt;view.x
op_star
id|pdev-&gt;offset.y
op_plus
id|pdev-&gt;offset.x
suffix:semicolon
id|dsty
op_assign
(paren
id|u16
op_star
)paren
(paren
id|image
op_plus
id|stride
)paren
suffix:semicolon
multiline_comment|/* offsets in U/V planes */
id|stride
op_assign
id|pdev-&gt;view.x
op_star
id|pdev-&gt;offset.y
op_div
l_int|4
op_plus
id|pdev-&gt;offset.x
op_div
l_int|2
suffix:semicolon
id|dstu
op_assign
(paren
id|u16
op_star
)paren
(paren
id|image
op_plus
id|n
op_plus
id|stride
)paren
suffix:semicolon
id|dstv
op_assign
(paren
id|u16
op_star
)paren
(paren
id|image
op_plus
id|n
op_plus
id|n
op_div
l_int|4
op_plus
id|stride
)paren
suffix:semicolon
multiline_comment|/* increment after each line */
id|stride
op_assign
(paren
id|pdev-&gt;view.x
op_minus
id|pdev-&gt;image.x
)paren
op_div
l_int|2
suffix:semicolon
multiline_comment|/* u16 is 2 bytes */
r_for
c_loop
(paren
id|line
op_assign
l_int|0
suffix:semicolon
id|line
OL
id|pdev-&gt;image.y
suffix:semicolon
id|line
op_increment
)paren
(brace
r_for
c_loop
(paren
id|col
op_assign
l_int|0
suffix:semicolon
id|col
OL
id|pdev-&gt;image.x
suffix:semicolon
id|col
op_add_assign
l_int|4
)paren
(brace
op_star
id|dsty
op_increment
op_assign
op_star
id|src
op_increment
suffix:semicolon
op_star
id|dsty
op_increment
op_assign
op_star
id|src
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|line
op_amp
l_int|1
)paren
op_star
id|dstv
op_increment
op_assign
op_star
id|src
op_increment
suffix:semicolon
r_else
op_star
id|dstu
op_increment
op_assign
op_star
id|src
op_increment
suffix:semicolon
)brace
id|dsty
op_add_assign
id|stride
suffix:semicolon
r_if
c_cond
(paren
id|line
op_amp
l_int|1
)paren
id|dstv
op_add_assign
(paren
id|stride
op_rshift
l_int|1
)paren
suffix:semicolon
r_else
id|dstu
op_add_assign
(paren
id|stride
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Compressed; the decompressor routines will write the data&n;&t;&t;   in planar format immediately.&n;&t;&t; */
r_int
id|flags
suffix:semicolon
id|flags
op_assign
id|PWCX_FLAG_PLANAR
suffix:semicolon
r_if
c_cond
(paren
id|pdev-&gt;vsize
op_eq
id|PSZ_VGA
op_logical_and
id|pdev-&gt;vframes
op_eq
l_int|5
op_logical_and
id|pdev-&gt;vsnapshot
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pwc: Mode Bayer is not supported for now&bslash;n&quot;
)paren
suffix:semicolon
id|flags
op_or_assign
id|PWCX_FLAG_BAYER
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* No such device or address: missing decompressor */
)brace
r_switch
c_cond
(paren
id|pdev-&gt;type
)paren
(brace
r_case
l_int|675
suffix:colon
r_case
l_int|680
suffix:colon
r_case
l_int|690
suffix:colon
r_case
l_int|720
suffix:colon
r_case
l_int|730
suffix:colon
r_case
l_int|740
suffix:colon
r_case
l_int|750
suffix:colon
id|pwc_dec23_decompress
c_func
(paren
op_amp
id|pdev-&gt;image
comma
op_amp
id|pdev-&gt;view
comma
op_amp
id|pdev-&gt;offset
comma
id|yuv
comma
id|image
comma
id|flags
comma
id|pdev-&gt;decompress_data
comma
id|pdev-&gt;vbandlength
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|645
suffix:colon
r_case
l_int|646
suffix:colon
multiline_comment|/* TODO &amp; FIXME */
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* No such device or address: missing decompressor */
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
