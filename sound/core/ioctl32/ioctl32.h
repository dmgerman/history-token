multiline_comment|/*&n; *   32bit -&gt; 64bit ioctl helpers&n; *   Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; *&n; * This file registers the converters from 32-bit ioctls to 64-bit ones.&n; * The converter assumes that a 32-bit user-pointer can be casted by A(x)&n; * macro to a valid 64-bit pointer which is accessible via copy_from/to_user.&n; *&n; */
macro_line|#ifndef __ALSA_IOCTL32_H
DECL|macro|__ALSA_IOCTL32_H
mdefine_line|#define __ALSA_IOCTL32_H
DECL|macro|TO_PTR
mdefine_line|#define TO_PTR(x)  A(x)
DECL|macro|COPY
mdefine_line|#define COPY(x)  (dst-&gt;x = src-&gt;x)
DECL|macro|CPTR
mdefine_line|#define CPTR(x)&t; (dst-&gt;x = (typeof(dst-&gt;x))A(src-&gt;x))
DECL|macro|convert_from_32
mdefine_line|#define convert_from_32(type, dstp, srcp)&bslash;&n;{&bslash;&n;&t;struct sndrv_##type *dst = dstp;&bslash;&n;&t;struct sndrv_##type##32 *src = srcp;&bslash;&n;&t;CVT_##sndrv_##type();&bslash;&n;}
DECL|macro|convert_to_32
mdefine_line|#define convert_to_32(type, dstp, srcp)&bslash;&n;{&bslash;&n;&t;struct sndrv_##type *src = srcp;&bslash;&n;&t;struct sndrv_##type##32 *dst = dstp;&bslash;&n;&t;CVT_##sndrv_##type();&bslash;&n;}
DECL|macro|DEFINE_ALSA_IOCTL
mdefine_line|#define DEFINE_ALSA_IOCTL(type) &bslash;&n;static int snd_ioctl32_##type(unsigned int fd, unsigned int cmd, unsigned long arg, struct file *file)&bslash;&n;{&bslash;&n;&t;struct sndrv_##type##32 data32;&bslash;&n;&t;struct sndrv_##type data;&bslash;&n;&t;int err;&bslash;&n;&t;if (copy_from_user(&amp;data32, (void*)arg, sizeof(data32)))&bslash;&n;&t;&t;return -EFAULT;&bslash;&n;&t;memset(&amp;data, 0, sizeof(data));&bslash;&n;&t;convert_from_32(type, &amp;data, &amp;data32);&bslash;&n;&t;err = file-&gt;f_op-&gt;ioctl(file-&gt;f_dentry-&gt;d_inode, file, cmd, (unsigned long)&amp;data);&bslash;&n;&t;if (err &lt; 0)&bslash;&n;&t;&t;return err;&bslash;&n;&t;if (cmd &amp; (_IOC_READ &lt;&lt; _IOC_DIRSHIFT)) {&bslash;&n;&t;&t;convert_to_32(type, &amp;data32, &amp;data);&bslash;&n;&t;&t;if (copy_to_user((void*)arg, &amp;data32, sizeof(data32)))&bslash;&n;&t;&t;&t;return -EFAULT;&bslash;&n;&t;}&bslash;&n;&t;return err;&bslash;&n;}
DECL|struct|ioctl32_mapper
r_struct
id|ioctl32_mapper
(brace
DECL|member|cmd
r_int
r_int
id|cmd
suffix:semicolon
DECL|member|handler
r_int
(paren
op_star
id|handler
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
DECL|member|registered
r_int
id|registered
suffix:semicolon
)brace
suffix:semicolon
r_int
id|snd_ioctl32_register
c_func
(paren
r_struct
id|ioctl32_mapper
op_star
id|mappers
)paren
suffix:semicolon
r_void
id|snd_ioctl32_unregister
c_func
(paren
r_struct
id|ioctl32_mapper
op_star
id|mappers
)paren
suffix:semicolon
macro_line|#endif /* __ALSA_IOCTL32_H */
eof
