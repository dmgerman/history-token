multiline_comment|/*&n; *   32bit -&gt; 64bit ioctl helpers&n; *   Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; *&n; * This file registers the converters from 32-bit ioctls to 64-bit ones.&n; * The converter assumes that a 32-bit user-pointer can be casted by compat_ptr(x)&n; * macro to a valid 64-bit pointer which is accessible via copy_from/to_user.&n; *&n; */
macro_line|#ifndef __ALSA_IOCTL32_H
DECL|macro|__ALSA_IOCTL32_H
mdefine_line|#define __ALSA_IOCTL32_H
macro_line|#include &lt;linux/compat.h&gt;
DECL|macro|COPY
mdefine_line|#define COPY(x)  (dst-&gt;x = src-&gt;x)
DECL|macro|CPTR
mdefine_line|#define CPTR(x)&t; (dst-&gt;x = compat_ptr(src-&gt;x))
DECL|macro|convert_from_32
mdefine_line|#define convert_from_32(type, dstp, srcp)&bslash;&n;{&bslash;&n;&t;struct sndrv_##type *dst = dstp;&bslash;&n;&t;struct sndrv_##type##32 *src = srcp;&bslash;&n;&t;CVT_##sndrv_##type();&bslash;&n;}
DECL|macro|convert_to_32
mdefine_line|#define convert_to_32(type, dstp, srcp)&bslash;&n;{&bslash;&n;&t;struct sndrv_##type *src = srcp;&bslash;&n;&t;struct sndrv_##type##32 *dst = dstp;&bslash;&n;&t;CVT_##sndrv_##type();&bslash;&n;}
DECL|macro|DEFINE_ALSA_IOCTL
mdefine_line|#define DEFINE_ALSA_IOCTL(type) &bslash;&n;static int _snd_ioctl32_##type(unsigned int fd, unsigned int cmd, unsigned long arg, struct file *file, unsigned int native_ctl)&bslash;&n;{&bslash;&n;&t;struct sndrv_##type##32 data32;&bslash;&n;&t;struct sndrv_##type data;&bslash;&n;&t;mm_segment_t oldseg;&bslash;&n;&t;int err;&bslash;&n;&t;if (copy_from_user(&amp;data32, (void __user *)arg, sizeof(data32)))&bslash;&n;&t;&t;return -EFAULT;&bslash;&n;&t;memset(&amp;data, 0, sizeof(data));&bslash;&n;&t;convert_from_32(type, &amp;data, &amp;data32);&bslash;&n;&t;oldseg = get_fs();&bslash;&n;&t;set_fs(KERNEL_DS);&bslash;&n;&t;err = file-&gt;f_op-&gt;ioctl(file-&gt;f_dentry-&gt;d_inode, file, native_ctl, (unsigned long)&amp;data);&bslash;&n;&t;set_fs(oldseg);&bslash;&n;&t;if (err &lt; 0) &bslash;&n;&t;&t;return err;&bslash;&n;&t;if (native_ctl &amp; (_IOC_READ &lt;&lt; _IOC_DIRSHIFT)) {&bslash;&n;&t;&t;convert_to_32(type, &amp;data32, &amp;data);&bslash;&n;&t;&t;if (copy_to_user((void __user *)arg, &amp;data32, sizeof(data32)))&bslash;&n;&t;&t;&t;return -EFAULT;&bslash;&n;&t;}&bslash;&n;&t;return 0;&bslash;&n;}
DECL|macro|DEFINE_ALSA_IOCTL_BIG
mdefine_line|#define DEFINE_ALSA_IOCTL_BIG(type) &bslash;&n;static int _snd_ioctl32_##type(unsigned int fd, unsigned int cmd, unsigned long arg, struct file *file, unsigned int native_ctl)&bslash;&n;{&bslash;&n;&t;struct sndrv_##type##32 *data32;&bslash;&n;&t;struct sndrv_##type *data;&bslash;&n;&t;mm_segment_t oldseg;&bslash;&n;&t;int err;&bslash;&n;&t;data32 = kmalloc(sizeof(*data32), GFP_KERNEL); &bslash;&n;&t;data = kmalloc(sizeof(*data), GFP_KERNEL); &bslash;&n;&t;if (data32 == NULL || data == NULL) { &bslash;&n;&t;&t;err = -ENOMEM; &bslash;&n;&t;&t;goto __end; &bslash;&n;&t;}&bslash;&n;&t;if (copy_from_user(data32, (void __user *)arg, sizeof(*data32))) { &bslash;&n;&t;&t;err = -EFAULT; &bslash;&n;&t;&t;goto __end; &bslash;&n;&t;}&bslash;&n;&t;memset(data, 0, sizeof(*data));&bslash;&n;&t;convert_from_32(type, data, data32);&bslash;&n;&t;oldseg = get_fs();&bslash;&n;&t;set_fs(KERNEL_DS);&bslash;&n;&t;err = file-&gt;f_op-&gt;ioctl(file-&gt;f_dentry-&gt;d_inode, file, native_ctl, (unsigned long)data);&bslash;&n;&t;set_fs(oldseg);&bslash;&n;&t;if (err &lt; 0) &bslash;&n;&t;&t;goto __end;&bslash;&n;&t;err = 0;&bslash;&n;&t;if (native_ctl &amp; (_IOC_READ &lt;&lt; _IOC_DIRSHIFT)) {&bslash;&n;&t;&t;convert_to_32(type, data32, data);&bslash;&n;&t;&t;if (copy_to_user((void __user *)arg, data32, sizeof(*data32)))&bslash;&n;&t;&t;&t;err = -EFAULT;&bslash;&n;&t;}&bslash;&n;      __end:&bslash;&n;      &t;if (data)&bslash;&n;      &t;&t;kfree(data);&bslash;&n;      &t;if (data32)&bslash;&n;      &t;&t;kfree(data32);&bslash;&n;&t;return err;&bslash;&n;}
DECL|macro|DEFINE_ALSA_IOCTL_ENTRY
mdefine_line|#define DEFINE_ALSA_IOCTL_ENTRY(name,type,native_ctl) &bslash;&n;static int snd_ioctl32_##name(unsigned int fd, unsigned int cmd, unsigned long arg, struct file *file) {&bslash;&n;&t;return _snd_ioctl32_##type(fd, cmd, arg, file, native_ctl);&bslash;&n;}
DECL|macro|MAP_COMPAT
mdefine_line|#define MAP_COMPAT(ctl) { ctl, snd_ioctl32_compat }
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
id|snd_ioctl32_compat
c_func
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
)paren
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
