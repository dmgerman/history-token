multiline_comment|/*&n; *   32bit -&gt; 64bit ioctl helpers&n; *   Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; *&n; * This file registers the converters from 32-bit ioctls to 64-bit ones.&n; * The converter assumes that a 32-bit user-pointer can be casted by compat_ptr(x)&n; * macro to a valid 64-bit pointer which is accessible via copy_from/to_user.&n; *&n; */
macro_line|#ifndef __ALSA_IOCTL32_H
DECL|macro|__ALSA_IOCTL32_H
mdefine_line|#define __ALSA_IOCTL32_H
macro_line|#include &lt;linux/compat.h&gt;
DECL|macro|COPY
mdefine_line|#define COPY(x) &bslash;&n;&t;do { &bslash;&n;&t;&t;if (copy_in_user(&amp;dst-&gt;x, &amp;src-&gt;x, sizeof(dst-&gt;x))) &bslash;&n;&t;&t;&t;return -EFAULT; &bslash;&n;&t;} while (0)
DECL|macro|COPY_ARRAY
mdefine_line|#define COPY_ARRAY(x) &bslash;&n;&t;do { &bslash;&n;&t;&t;if (copy_in_user(dst-&gt;x, src-&gt;x, sizeof(dst-&gt;x))) &bslash;&n;&t;&t;&t;return -EFAULT; &bslash;&n;&t;} while (0)
DECL|macro|COPY_CVT
mdefine_line|#define COPY_CVT(x) &bslash;&n;&t;do { &bslash;&n;&t;&t;__typeof__(src-&gt;x) __val_tmp; &bslash;&n;&t;&t;if (get_user(__val_tmp, &amp;src-&gt;x) || &bslash;&n;&t;&t;    put_user(__val_tmp, &amp;dst-&gt;x))&bslash;&n;&t;&t;&t;return -EFAULT; &bslash;&n;&t;} while (0)
DECL|macro|convert_from_32
mdefine_line|#define convert_from_32(type, dstp, srcp)&bslash;&n;{&bslash;&n;&t;struct sndrv_##type __user *dst = dstp;&bslash;&n;&t;struct sndrv_##type##32 __user *src = srcp;&bslash;&n;&t;CVT_##sndrv_##type();&bslash;&n;}
DECL|macro|convert_to_32
mdefine_line|#define convert_to_32(type, dstp, srcp)&bslash;&n;{&bslash;&n;&t;struct sndrv_##type __user *src = srcp;&bslash;&n;&t;struct sndrv_##type##32 __user *dst = dstp;&bslash;&n;&t;CVT_##sndrv_##type();&bslash;&n;}
DECL|macro|DEFINE_ALSA_IOCTL
mdefine_line|#define DEFINE_ALSA_IOCTL(type) &bslash;&n;static inline int _snd_ioctl32_##type(unsigned int fd, unsigned int cmd, unsigned long arg, struct file *file, unsigned int native_ctl)&bslash;&n;{&bslash;&n;&t;struct sndrv_##type##32 __user *data32;&bslash;&n;&t;struct sndrv_##type __user *data;&bslash;&n;&t;int err;&bslash;&n;&t;data32 = compat_ptr(arg);&bslash;&n;&t;data = compat_alloc_user_space(sizeof(*data));&bslash;&n;&t;convert_from_32(type, data, data32);&bslash;&n;&t;err = file-&gt;f_op-&gt;ioctl(file-&gt;f_dentry-&gt;d_inode, file, native_ctl, (unsigned long)data);&bslash;&n;&t;if (err &lt; 0) &bslash;&n;&t;&t;return err;&bslash;&n;&t;if (native_ctl &amp; (_IOC_READ &lt;&lt; _IOC_DIRSHIFT)) {&bslash;&n;&t;&t;convert_to_32(type, data32, data);&bslash;&n;&t;}&bslash;&n;&t;return 0;&bslash;&n;}
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
