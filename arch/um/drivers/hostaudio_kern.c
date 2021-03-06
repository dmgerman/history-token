multiline_comment|/* &n; * Copyright (C) 2002 Steve Schmidtke &n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/module.h&quot;
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;linux/fs.h&quot;
macro_line|#include &quot;linux/sound.h&quot;
macro_line|#include &quot;linux/soundcard.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|struct|hostaudio_state
r_struct
id|hostaudio_state
(brace
DECL|member|fd
r_int
id|fd
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hostmixer_state
r_struct
id|hostmixer_state
(brace
DECL|member|fd
r_int
id|fd
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HOSTAUDIO_DEV_DSP
mdefine_line|#define HOSTAUDIO_DEV_DSP &quot;/dev/sound/dsp&quot;
DECL|macro|HOSTAUDIO_DEV_MIXER
mdefine_line|#define HOSTAUDIO_DEV_MIXER &quot;/dev/sound/mixer&quot;
multiline_comment|/* Only changed from linux_main at boot time */
DECL|variable|dsp
r_char
op_star
id|dsp
op_assign
id|HOSTAUDIO_DEV_DSP
suffix:semicolon
DECL|variable|mixer
r_char
op_star
id|mixer
op_assign
id|HOSTAUDIO_DEV_MIXER
suffix:semicolon
DECL|macro|DSP_HELP
mdefine_line|#define DSP_HELP &bslash;&n;&quot;    This is used to specify the host dsp device to the hostaudio driver.&bslash;n&quot; &bslash;&n;&quot;    The default is &bslash;&quot;&quot; HOSTAUDIO_DEV_DSP &quot;&bslash;&quot;.&bslash;n&bslash;n&quot;
DECL|macro|MIXER_HELP
mdefine_line|#define MIXER_HELP &bslash;&n;&quot;    This is used to specify the host mixer device to the hostaudio driver.&bslash;n&quot;&bslash;&n;&quot;    The default is &bslash;&quot;&quot; HOSTAUDIO_DEV_MIXER &quot;&bslash;&quot;.&bslash;n&bslash;n&quot;
macro_line|#ifndef MODULE
DECL|function|set_dsp
r_static
r_int
id|set_dsp
c_func
(paren
r_char
op_star
id|name
comma
r_int
op_star
id|add
)paren
(brace
id|dsp
op_assign
id|name
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;dsp=&quot;
comma
id|set_dsp
comma
l_string|&quot;dsp=&lt;dsp device&gt;&bslash;n&quot;
id|DSP_HELP
)paren
suffix:semicolon
DECL|function|set_mixer
r_static
r_int
id|set_mixer
c_func
(paren
r_char
op_star
id|name
comma
r_int
op_star
id|add
)paren
(brace
id|mixer
op_assign
id|name
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;mixer=&quot;
comma
id|set_mixer
comma
l_string|&quot;mixer=&lt;mixer device&gt;&bslash;n&quot;
id|MIXER_HELP
)paren
suffix:semicolon
macro_line|#else /*MODULE*/
id|MODULE_PARM
c_func
(paren
id|dsp
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|dsp
comma
id|DSP_HELP
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mixer
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|mixer
comma
id|MIXER_HELP
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* /dev/dsp file operations */
DECL|function|hostaudio_read
r_static
id|ssize_t
id|hostaudio_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|hostaudio_state
op_star
id|state
op_assign
id|file-&gt;private_data
suffix:semicolon
r_void
op_star
id|kbuf
suffix:semicolon
r_int
id|err
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;hostaudio: read called, count = %d&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
macro_line|#endif
id|kbuf
op_assign
id|kmalloc
c_func
(paren
id|count
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kbuf
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|err
op_assign
id|os_read_file
c_func
(paren
id|state-&gt;fd
comma
id|kbuf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|kbuf
comma
id|err
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
id|out
suffix:colon
id|kfree
c_func
(paren
id|kbuf
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|hostaudio_write
r_static
id|ssize_t
id|hostaudio_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|hostaudio_state
op_star
id|state
op_assign
id|file-&gt;private_data
suffix:semicolon
r_void
op_star
id|kbuf
suffix:semicolon
r_int
id|err
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;hostaudio: write called, count = %d&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
macro_line|#endif
id|kbuf
op_assign
id|kmalloc
c_func
(paren
id|count
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kbuf
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|kbuf
comma
id|buffer
comma
id|count
)paren
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
id|err
op_assign
id|os_write_file
c_func
(paren
id|state-&gt;fd
comma
id|kbuf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
op_star
id|ppos
op_add_assign
id|err
suffix:semicolon
id|out
suffix:colon
id|kfree
c_func
(paren
id|kbuf
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|hostaudio_poll
r_static
r_int
r_int
id|hostaudio_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|poll_table_struct
op_star
id|wait
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;hostaudio: poll called (unimplemented)&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|mask
suffix:semicolon
)brace
DECL|function|hostaudio_ioctl
r_static
r_int
id|hostaudio_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|hostaudio_state
op_star
id|state
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
r_int
id|data
op_assign
l_int|0
suffix:semicolon
r_int
id|err
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;hostaudio: ioctl called, cmd = %u&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDCTL_DSP_SPEED
suffix:colon
r_case
id|SNDCTL_DSP_STEREO
suffix:colon
r_case
id|SNDCTL_DSP_GETBLKSIZE
suffix:colon
r_case
id|SNDCTL_DSP_CHANNELS
suffix:colon
r_case
id|SNDCTL_DSP_SUBDIVIDE
suffix:colon
r_case
id|SNDCTL_DSP_SETFRAGMENT
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|data
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|err
op_assign
id|os_ioctl_generic
c_func
(paren
id|state-&gt;fd
comma
id|cmd
comma
(paren
r_int
r_int
)paren
op_amp
id|data
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDCTL_DSP_SPEED
suffix:colon
r_case
id|SNDCTL_DSP_STEREO
suffix:colon
r_case
id|SNDCTL_DSP_GETBLKSIZE
suffix:colon
r_case
id|SNDCTL_DSP_CHANNELS
suffix:colon
r_case
id|SNDCTL_DSP_SUBDIVIDE
suffix:colon
r_case
id|SNDCTL_DSP_SETFRAGMENT
suffix:colon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|data
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|hostaudio_open
r_static
r_int
id|hostaudio_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|hostaudio_state
op_star
id|state
suffix:semicolon
r_int
id|r
op_assign
l_int|0
comma
id|w
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;hostaudio: open called (host: %s)&bslash;n&quot;
comma
id|dsp
)paren
suffix:semicolon
macro_line|#endif
id|state
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hostaudio_state
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
(brace
id|r
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
(brace
id|w
op_assign
l_int|1
suffix:semicolon
)brace
id|ret
op_assign
id|os_open_file
c_func
(paren
id|dsp
comma
id|of_set_rw
c_func
(paren
id|OPENFLAGS
c_func
(paren
)paren
comma
id|r
comma
id|w
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|state-&gt;fd
op_assign
id|ret
suffix:semicolon
id|file-&gt;private_data
op_assign
id|state
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hostaudio_release
r_static
r_int
id|hostaudio_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|hostaudio_state
op_star
id|state
op_assign
id|file-&gt;private_data
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;hostaudio: release called&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|os_close_file
c_func
(paren
id|state-&gt;fd
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* /dev/mixer file operations */
DECL|function|hostmixer_ioctl_mixdev
r_static
r_int
id|hostmixer_ioctl_mixdev
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|hostmixer_state
op_star
id|state
op_assign
id|file-&gt;private_data
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;hostmixer: ioctl called&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|os_ioctl_generic
c_func
(paren
id|state-&gt;fd
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|function|hostmixer_open_mixdev
r_static
r_int
id|hostmixer_open_mixdev
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|hostmixer_state
op_star
id|state
suffix:semicolon
r_int
id|r
op_assign
l_int|0
comma
id|w
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;hostmixer: open called (host: %s)&bslash;n&quot;
comma
id|mixer
)paren
suffix:semicolon
macro_line|#endif
id|state
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|hostmixer_state
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
(brace
id|r
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_WRITE
)paren
(brace
id|w
op_assign
l_int|1
suffix:semicolon
)brace
id|ret
op_assign
id|os_open_file
c_func
(paren
id|mixer
comma
id|of_set_rw
c_func
(paren
id|OPENFLAGS
c_func
(paren
)paren
comma
id|r
comma
id|w
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;hostaudio_open_mixdev failed to open &squot;%s&squot;, err = %d&bslash;n&quot;
comma
id|dsp
comma
op_minus
id|ret
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|file-&gt;private_data
op_assign
id|state
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hostmixer_release
r_static
r_int
id|hostmixer_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|hostmixer_state
op_star
id|state
op_assign
id|file-&gt;private_data
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;hostmixer: release called&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|os_close_file
c_func
(paren
id|state-&gt;fd
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* kernel module operations */
DECL|variable|hostaudio_fops
r_static
r_struct
id|file_operations
id|hostaudio_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|read
op_assign
id|hostaudio_read
comma
dot
id|write
op_assign
id|hostaudio_write
comma
dot
id|poll
op_assign
id|hostaudio_poll
comma
dot
id|ioctl
op_assign
id|hostaudio_ioctl
comma
dot
id|mmap
op_assign
l_int|NULL
comma
dot
id|open
op_assign
id|hostaudio_open
comma
dot
id|release
op_assign
id|hostaudio_release
comma
)brace
suffix:semicolon
DECL|variable|hostmixer_fops
r_static
r_struct
id|file_operations
id|hostmixer_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|llseek
op_assign
id|no_llseek
comma
dot
id|ioctl
op_assign
id|hostmixer_ioctl_mixdev
comma
dot
id|open
op_assign
id|hostmixer_open_mixdev
comma
dot
id|release
op_assign
id|hostmixer_release
comma
)brace
suffix:semicolon
r_struct
(brace
DECL|member|dev_audio
r_int
id|dev_audio
suffix:semicolon
DECL|member|dev_mixer
r_int
id|dev_mixer
suffix:semicolon
DECL|variable|module_data
)brace
id|module_data
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Steve Schmidtke&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;UML Audio Relay&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|hostaudio_init_module
r_static
r_int
id|__init
id|hostaudio_init_module
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;UML Audio Relay (host dsp = %s, host mixer = %s)&bslash;n&quot;
comma
id|dsp
comma
id|mixer
)paren
suffix:semicolon
id|module_data.dev_audio
op_assign
id|register_sound_dsp
c_func
(paren
op_amp
id|hostaudio_fops
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|module_data.dev_audio
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hostaudio: couldn&squot;t register DSP device!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|module_data.dev_mixer
op_assign
id|register_sound_mixer
c_func
(paren
op_amp
id|hostmixer_fops
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|module_data.dev_mixer
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hostmixer: couldn&squot;t register mixer &quot;
l_string|&quot;device!&bslash;n&quot;
)paren
suffix:semicolon
id|unregister_sound_dsp
c_func
(paren
id|module_data.dev_audio
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hostaudio_cleanup_module
r_static
r_void
id|__exit
id|hostaudio_cleanup_module
(paren
r_void
)paren
(brace
id|unregister_sound_mixer
c_func
(paren
id|module_data.dev_mixer
)paren
suffix:semicolon
id|unregister_sound_dsp
c_func
(paren
id|module_data.dev_audio
)paren
suffix:semicolon
)brace
DECL|variable|hostaudio_init_module
id|module_init
c_func
(paren
id|hostaudio_init_module
)paren
suffix:semicolon
DECL|variable|hostaudio_cleanup_module
id|module_exit
c_func
(paren
id|hostaudio_cleanup_module
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
