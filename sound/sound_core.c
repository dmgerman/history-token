multiline_comment|/*&n; *&t;Sound core handling. Breaks out sound functions to submodules&n; *&t;&n; *&t;Author:&t;&t;Alan Cox &lt;alan.cox@linux.org&gt;&n; *&n; *&t;Fixes:&n; *&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *                         --------------------&n; * &n; *&t;Top level handler for the sound subsystem. Various devices can&n; *&t;plug into this. The fact they don&squot;t all go via OSS doesn&squot;t mean &n; *&t;they don&squot;t have to implement the OSS API. There is a lot of logic&n; *&t;to keeping much of the OSS weight out of the code in a compatibility&n; *&t;module, but it&squot;s up to the driver to rember to load it...&n; *&n; *&t;The code provides a set of functions for registration of devices&n; *&t;by type. This is done rather than providing a single call so that&n; *&t;we can hide any future changes in the internals (eg when we go to&n; *&t;32bit dev_t) from the modules and their interface.&n; *&n; *&t;Secondly we need to allocate the dsp, dsp16 and audio devices as&n; *&t;one. Thus we misuse the chains a bit to simplify this.&n; *&n; *&t;Thirdly to make it more fun and for 2.3.x and above we do all&n; *&t;of this using fine grained locking.&n; *&n; *&t;FIXME: we have to resolve modules and fine grained load/unload&n; *&t;locking at some point in 2.3.x.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sound.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
DECL|macro|SOUND_STEP
mdefine_line|#define SOUND_STEP 16
DECL|struct|sound_unit
r_struct
id|sound_unit
(brace
DECL|member|unit_minor
r_int
id|unit_minor
suffix:semicolon
DECL|member|unit_fops
r_struct
id|file_operations
op_star
id|unit_fops
suffix:semicolon
DECL|member|next
r_struct
id|sound_unit
op_star
id|next
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SOUND_MSNDCLAS
r_extern
r_int
id|msnd_classic_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SOUND_MSNDPIN
r_extern
r_int
id|msnd_pinnacle_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;Low level list operator. Scan the ordered list, find a hole and&n; *&t;join into it. Called with the lock asserted&n; */
DECL|function|__sound_insert_unit
r_static
r_int
id|__sound_insert_unit
c_func
(paren
r_struct
id|sound_unit
op_star
id|s
comma
r_struct
id|sound_unit
op_star
op_star
id|list
comma
r_struct
id|file_operations
op_star
id|fops
comma
r_int
id|index
comma
r_int
id|low
comma
r_int
id|top
)paren
(brace
r_int
id|n
op_assign
id|low
suffix:semicolon
r_if
c_cond
(paren
id|index
OL
l_int|0
)paren
(brace
multiline_comment|/* first free */
r_while
c_loop
(paren
op_star
id|list
op_logical_and
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|unit_minor
OL
id|n
)paren
id|list
op_assign
op_amp
(paren
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
r_while
c_loop
(paren
id|n
OL
id|top
)paren
(brace
multiline_comment|/* Found a hole ? */
r_if
c_cond
(paren
op_star
id|list
op_eq
l_int|NULL
op_logical_or
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|unit_minor
OG
id|n
)paren
(brace
r_break
suffix:semicolon
)brace
id|list
op_assign
op_amp
(paren
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
id|n
op_add_assign
id|SOUND_STEP
suffix:semicolon
)brace
r_if
c_cond
(paren
id|n
op_ge
id|top
)paren
(brace
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
)brace
r_else
(brace
id|n
op_assign
id|low
op_plus
(paren
id|index
op_star
l_int|16
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|list
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|unit_minor
op_eq
id|n
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|unit_minor
OG
id|n
)paren
r_break
suffix:semicolon
id|list
op_assign
op_amp
(paren
(paren
op_star
id|list
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *&t;Fill it in&n;&t; */
id|s-&gt;unit_minor
op_assign
id|n
suffix:semicolon
id|s-&gt;unit_fops
op_assign
id|fops
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Link it&n;&t; */
id|s-&gt;next
op_assign
op_star
id|list
suffix:semicolon
op_star
id|list
op_assign
id|s
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Remove a node from the chain. Called with the lock asserted&n; */
DECL|function|__sound_remove_unit
r_static
r_struct
id|sound_unit
op_star
id|__sound_remove_unit
c_func
(paren
r_struct
id|sound_unit
op_star
op_star
id|list
comma
r_int
id|unit
)paren
(brace
r_while
c_loop
(paren
op_star
id|list
)paren
(brace
r_struct
id|sound_unit
op_star
id|p
op_assign
op_star
id|list
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;unit_minor
op_eq
id|unit
)paren
(brace
op_star
id|list
op_assign
id|p-&gt;next
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
id|list
op_assign
op_amp
(paren
id|p-&gt;next
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Sound device %d went missing!&bslash;n&quot;
comma
id|unit
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;This lock guards the sound loader list.&n; */
DECL|variable|sound_loader_lock
r_static
id|spinlock_t
id|sound_loader_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; *&t;Allocate the controlling structure and add it to the sound driver&n; *&t;list. Acquires locks as needed&n; */
DECL|function|sound_insert_unit
r_static
r_int
id|sound_insert_unit
c_func
(paren
r_struct
id|sound_unit
op_star
op_star
id|list
comma
r_struct
id|file_operations
op_star
id|fops
comma
r_int
id|index
comma
r_int
id|low
comma
r_int
id|top
comma
r_const
r_char
op_star
id|name
comma
id|umode_t
id|mode
)paren
(brace
r_struct
id|sound_unit
op_star
id|s
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|s
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_int
id|r
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sound_loader_lock
)paren
suffix:semicolon
id|r
op_assign
id|__sound_insert_unit
c_func
(paren
id|s
comma
id|list
comma
id|fops
comma
id|index
comma
id|low
comma
id|top
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sound_loader_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
r_goto
id|fail
suffix:semicolon
r_else
r_if
c_cond
(paren
id|r
OL
id|SOUND_STEP
)paren
id|sprintf
c_func
(paren
id|s-&gt;name
comma
l_string|&quot;sound/%s&quot;
comma
id|name
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|s-&gt;name
comma
l_string|&quot;sound/%s%d&quot;
comma
id|name
comma
id|r
op_div
id|SOUND_STEP
)paren
suffix:semicolon
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|SOUND_MAJOR
comma
id|s-&gt;unit_minor
)paren
comma
id|S_IFCHR
op_or
id|mode
comma
id|s-&gt;name
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
id|fail
suffix:colon
id|kfree
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Remove a unit. Acquires locks as needed. The drivers MUST have&n; *&t;completed the removal before their file operations become&n; *&t;invalid.&n; */
DECL|function|sound_remove_unit
r_static
r_void
id|sound_remove_unit
c_func
(paren
r_struct
id|sound_unit
op_star
op_star
id|list
comma
r_int
id|unit
)paren
(brace
r_struct
id|sound_unit
op_star
id|p
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sound_loader_lock
)paren
suffix:semicolon
id|p
op_assign
id|__sound_remove_unit
c_func
(paren
id|list
comma
id|unit
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sound_loader_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
id|devfs_remove
c_func
(paren
id|p-&gt;name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Allocations&n; *&n; *&t;0&t;*16&t;&t;Mixers&n; *&t;1&t;*8&t;&t;Sequencers&n; *&t;2&t;*16&t;&t;Midi&n; *&t;3&t;*16&t;&t;DSP&n; *&t;4&t;*16&t;&t;SunDSP&n; *&t;5&t;*16&t;&t;DSP16&n; *&t;6&t;--&t;&t;sndstat (obsolete)&n; *&t;7&t;*16&t;&t;unused&n; *&t;8&t;--&t;&t;alternate sequencer (see above)&n; *&t;9&t;*16&t;&t;raw synthesizer access&n; *&t;10&t;*16&t;&t;unused&n; *&t;11&t;*16&t;&t;unused&n; *&t;12&t;*16&t;&t;unused&n; *&t;13&t;*16&t;&t;unused&n; *&t;14&t;*16&t;&t;unused&n; *&t;15&t;*16&t;&t;unused&n; */
DECL|variable|chains
r_static
r_struct
id|sound_unit
op_star
id|chains
(braket
id|SOUND_STEP
)braket
suffix:semicolon
multiline_comment|/**&n; *&t;register_sound_special - register a special sound node&n; *&t;@fops: File operations for the driver&n; *&t;@unit: Unit number to allocate&n; *&n; *&t;Allocate a special sound device by minor number from the sound&n; *&t;subsystem. The allocated number is returned on succes. On failure&n; *&t;a negative error code is returned.&n; */
DECL|function|register_sound_special
r_int
id|register_sound_special
c_func
(paren
r_struct
id|file_operations
op_star
id|fops
comma
r_int
id|unit
)paren
(brace
r_const
r_int
id|chain
op_assign
id|unit
op_mod
id|SOUND_STEP
suffix:semicolon
r_int
id|max_unit
op_assign
l_int|128
op_plus
id|chain
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_char
id|_name
(braket
l_int|16
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|chain
)paren
(brace
r_case
l_int|0
suffix:colon
id|name
op_assign
l_string|&quot;mixer&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|name
op_assign
l_string|&quot;sequencer&quot;
suffix:semicolon
r_if
c_cond
(paren
id|unit
op_ge
id|SOUND_STEP
)paren
r_goto
id|__unknown
suffix:semicolon
id|max_unit
op_assign
id|unit
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|name
op_assign
l_string|&quot;midi&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|name
op_assign
l_string|&quot;dsp&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|name
op_assign
l_string|&quot;audio&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|name
op_assign
l_string|&quot;sequencer2&quot;
suffix:semicolon
r_if
c_cond
(paren
id|unit
op_ge
id|SOUND_STEP
)paren
r_goto
id|__unknown
suffix:semicolon
id|max_unit
op_assign
id|unit
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
id|name
op_assign
l_string|&quot;dmmidi&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|name
op_assign
l_string|&quot;dmfm&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
id|name
op_assign
l_string|&quot;adsp&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|13
suffix:colon
id|name
op_assign
l_string|&quot;amidi&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|14
suffix:colon
id|name
op_assign
l_string|&quot;admmidi&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
(brace
id|__unknown
suffix:colon
id|sprintf
c_func
(paren
id|_name
comma
l_string|&quot;unknown%d&quot;
comma
id|chain
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unit
op_ge
id|SOUND_STEP
)paren
id|strcat
c_func
(paren
id|_name
comma
l_string|&quot;-&quot;
)paren
suffix:semicolon
id|name
op_assign
id|_name
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
id|sound_insert_unit
c_func
(paren
op_amp
id|chains
(braket
id|chain
)braket
comma
id|fops
comma
op_minus
l_int|1
comma
id|unit
comma
id|max_unit
comma
id|name
comma
id|S_IRUSR
op_or
id|S_IWUSR
)paren
suffix:semicolon
)brace
DECL|variable|register_sound_special
id|EXPORT_SYMBOL
c_func
(paren
id|register_sound_special
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;register_sound_mixer - register a mixer device&n; *&t;@fops: File operations for the driver&n; *&t;@dev: Unit number to allocate&n; *&n; *&t;Allocate a mixer device. Unit is the number of the mixer requested.&n; *&t;Pass -1 to request the next free mixer unit. On success the allocated&n; *&t;number is returned, on failure a negative error code is returned.&n; */
DECL|function|register_sound_mixer
r_int
id|register_sound_mixer
c_func
(paren
r_struct
id|file_operations
op_star
id|fops
comma
r_int
id|dev
)paren
(brace
r_return
id|sound_insert_unit
c_func
(paren
op_amp
id|chains
(braket
l_int|0
)braket
comma
id|fops
comma
id|dev
comma
l_int|0
comma
l_int|128
comma
l_string|&quot;mixer&quot;
comma
id|S_IRUSR
op_or
id|S_IWUSR
)paren
suffix:semicolon
)brace
DECL|variable|register_sound_mixer
id|EXPORT_SYMBOL
c_func
(paren
id|register_sound_mixer
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;register_sound_midi - register a midi device&n; *&t;@fops: File operations for the driver&n; *&t;@dev: Unit number to allocate&n; *&n; *&t;Allocate a midi device. Unit is the number of the midi device requested.&n; *&t;Pass -1 to request the next free midi unit. On success the allocated&n; *&t;number is returned, on failure a negative error code is returned.&n; */
DECL|function|register_sound_midi
r_int
id|register_sound_midi
c_func
(paren
r_struct
id|file_operations
op_star
id|fops
comma
r_int
id|dev
)paren
(brace
r_return
id|sound_insert_unit
c_func
(paren
op_amp
id|chains
(braket
l_int|2
)braket
comma
id|fops
comma
id|dev
comma
l_int|2
comma
l_int|130
comma
l_string|&quot;midi&quot;
comma
id|S_IRUSR
op_or
id|S_IWUSR
)paren
suffix:semicolon
)brace
DECL|variable|register_sound_midi
id|EXPORT_SYMBOL
c_func
(paren
id|register_sound_midi
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;DSP&squot;s are registered as a triple. Register only one and cheat&n; *&t;in open - see below.&n; */
multiline_comment|/**&n; *&t;register_sound_dsp - register a DSP device&n; *&t;@fops: File operations for the driver&n; *&t;@dev: Unit number to allocate&n; *&n; *&t;Allocate a DSP device. Unit is the number of the DSP requested.&n; *&t;Pass -1 to request the next free DSP unit. On success the allocated&n; *&t;number is returned, on failure a negative error code is returned.&n; *&n; *&t;This function allocates both the audio and dsp device entries together&n; *&t;and will always allocate them as a matching pair - eg dsp3/audio3&n; */
DECL|function|register_sound_dsp
r_int
id|register_sound_dsp
c_func
(paren
r_struct
id|file_operations
op_star
id|fops
comma
r_int
id|dev
)paren
(brace
r_return
id|sound_insert_unit
c_func
(paren
op_amp
id|chains
(braket
l_int|3
)braket
comma
id|fops
comma
id|dev
comma
l_int|3
comma
l_int|131
comma
l_string|&quot;dsp&quot;
comma
id|S_IWUSR
op_or
id|S_IRUSR
)paren
suffix:semicolon
)brace
DECL|variable|register_sound_dsp
id|EXPORT_SYMBOL
c_func
(paren
id|register_sound_dsp
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;register_sound_synth - register a synth device&n; *&t;@fops: File operations for the driver&n; *&t;@dev: Unit number to allocate&n; *&n; *&t;Allocate a synth device. Unit is the number of the synth device requested.&n; *&t;Pass -1 to request the next free synth unit. On success the allocated&n; *&t;number is returned, on failure a negative error code is returned.&n; */
DECL|function|register_sound_synth
r_int
id|register_sound_synth
c_func
(paren
r_struct
id|file_operations
op_star
id|fops
comma
r_int
id|dev
)paren
(brace
r_return
id|sound_insert_unit
c_func
(paren
op_amp
id|chains
(braket
l_int|9
)braket
comma
id|fops
comma
id|dev
comma
l_int|9
comma
l_int|137
comma
l_string|&quot;synth&quot;
comma
id|S_IRUSR
op_or
id|S_IWUSR
)paren
suffix:semicolon
)brace
DECL|variable|register_sound_synth
id|EXPORT_SYMBOL
c_func
(paren
id|register_sound_synth
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;unregister_sound_special - unregister a special sound device&n; *&t;@unit: unit number to allocate&n; *&n; *&t;Release a sound device that was allocated with&n; *&t;register_sound_special(). The unit passed is the return value from&n; *&t;the register function.&n; */
DECL|function|unregister_sound_special
r_void
id|unregister_sound_special
c_func
(paren
r_int
id|unit
)paren
(brace
id|sound_remove_unit
c_func
(paren
op_amp
id|chains
(braket
id|unit
op_mod
id|SOUND_STEP
)braket
comma
id|unit
)paren
suffix:semicolon
)brace
DECL|variable|unregister_sound_special
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_sound_special
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;unregister_sound_mixer - unregister a mixer&n; *&t;@unit: unit number to allocate&n; *&n; *&t;Release a sound device that was allocated with register_sound_mixer().&n; *&t;The unit passed is the return value from the register function.&n; */
DECL|function|unregister_sound_mixer
r_void
id|unregister_sound_mixer
c_func
(paren
r_int
id|unit
)paren
(brace
id|sound_remove_unit
c_func
(paren
op_amp
id|chains
(braket
l_int|0
)braket
comma
id|unit
)paren
suffix:semicolon
)brace
DECL|variable|unregister_sound_mixer
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_sound_mixer
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;unregister_sound_midi - unregister a midi device&n; *&t;@unit: unit number to allocate&n; *&n; *&t;Release a sound device that was allocated with register_sound_midi().&n; *&t;The unit passed is the return value from the register function.&n; */
DECL|function|unregister_sound_midi
r_void
id|unregister_sound_midi
c_func
(paren
r_int
id|unit
)paren
(brace
r_return
id|sound_remove_unit
c_func
(paren
op_amp
id|chains
(braket
l_int|2
)braket
comma
id|unit
)paren
suffix:semicolon
)brace
DECL|variable|unregister_sound_midi
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_sound_midi
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;unregister_sound_dsp - unregister a DSP device&n; *&t;@unit: unit number to allocate&n; *&n; *&t;Release a sound device that was allocated with register_sound_dsp().&n; *&t;The unit passed is the return value from the register function.&n; *&n; *&t;Both of the allocated units are released together automatically.&n; */
DECL|function|unregister_sound_dsp
r_void
id|unregister_sound_dsp
c_func
(paren
r_int
id|unit
)paren
(brace
r_return
id|sound_remove_unit
c_func
(paren
op_amp
id|chains
(braket
l_int|3
)braket
comma
id|unit
)paren
suffix:semicolon
)brace
DECL|variable|unregister_sound_dsp
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_sound_dsp
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;unregister_sound_synth - unregister a synth device&n; *&t;@unit: unit number to allocate&n; *&n; *&t;Release a sound device that was allocated with register_sound_synth().&n; *&t;The unit passed is the return value from the register function.&n; */
DECL|function|unregister_sound_synth
r_void
id|unregister_sound_synth
c_func
(paren
r_int
id|unit
)paren
(brace
r_return
id|sound_remove_unit
c_func
(paren
op_amp
id|chains
(braket
l_int|9
)braket
comma
id|unit
)paren
suffix:semicolon
)brace
DECL|variable|unregister_sound_synth
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_sound_synth
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Now our file operations&n; */
r_static
r_int
id|soundcore_open
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
DECL|variable|soundcore_fops
r_static
r_struct
id|file_operations
id|soundcore_fops
op_assign
(brace
multiline_comment|/* We must have an owner or the module locking fails */
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|soundcore_open
comma
)brace
suffix:semicolon
DECL|function|__look_for_unit
r_static
r_struct
id|sound_unit
op_star
id|__look_for_unit
c_func
(paren
r_int
id|chain
comma
r_int
id|unit
)paren
(brace
r_struct
id|sound_unit
op_star
id|s
suffix:semicolon
id|s
op_assign
id|chains
(braket
id|chain
)braket
suffix:semicolon
r_while
c_loop
(paren
id|s
op_logical_and
id|s-&gt;unit_minor
op_le
id|unit
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;unit_minor
op_eq
id|unit
)paren
(brace
r_return
id|s
suffix:semicolon
)brace
id|s
op_assign
id|s-&gt;next
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|soundcore_open
r_int
id|soundcore_open
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
r_int
id|chain
suffix:semicolon
r_int
id|unit
op_assign
id|iminor
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|sound_unit
op_star
id|s
suffix:semicolon
r_struct
id|file_operations
op_star
id|new_fops
op_assign
l_int|NULL
suffix:semicolon
id|chain
op_assign
id|unit
op_amp
l_int|0x0F
suffix:semicolon
r_if
c_cond
(paren
id|chain
op_eq
l_int|4
op_logical_or
id|chain
op_eq
l_int|5
)paren
multiline_comment|/* dsp/audio/dsp16 */
(brace
id|unit
op_and_assign
l_int|0xF0
suffix:semicolon
id|unit
op_or_assign
l_int|3
suffix:semicolon
id|chain
op_assign
l_int|3
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|sound_loader_lock
)paren
suffix:semicolon
id|s
op_assign
id|__look_for_unit
c_func
(paren
id|chain
comma
id|unit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
id|new_fops
op_assign
id|fops_get
c_func
(paren
id|s-&gt;unit_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_fops
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|sound_loader_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *  Please, don&squot;t change this order or code.&n;&t;&t; *  For ALSA slot means soundcard and OSS emulation code&n;&t;&t; *  comes as add-on modules which aren&squot;t depend on&n;&t;&t; *  ALSA toplevel modules for soundcards, thus we need&n;&t;&t; *  load them at first.&t;  [Jaroslav Kysela &lt;perex@jcu.cz&gt;]&n;&t;&t; */
id|request_module
c_func
(paren
l_string|&quot;sound-slot-%i&quot;
comma
id|unit
op_rshift
l_int|4
)paren
suffix:semicolon
id|request_module
c_func
(paren
l_string|&quot;sound-service-%i-%i&quot;
comma
id|unit
op_rshift
l_int|4
comma
id|chain
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|sound_loader_lock
)paren
suffix:semicolon
id|s
op_assign
id|__look_for_unit
c_func
(paren
id|chain
comma
id|unit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
id|new_fops
op_assign
id|fops_get
c_func
(paren
id|s-&gt;unit_fops
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_fops
)paren
(brace
multiline_comment|/*&n;&t;&t; * We rely upon the fact that we can&squot;t be unloaded while the&n;&t;&t; * subdriver is there, so if -&gt;open() is successful we can&n;&t;&t; * safely drop the reference counter and if it is not we can&n;&t;&t; * revert to old -&gt;f_op. Ugly, indeed, but that&squot;s the cost of&n;&t;&t; * switching -&gt;f_op in the first place.&n;&t;&t; */
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|file_operations
op_star
id|old_fops
op_assign
id|file-&gt;f_op
suffix:semicolon
id|file-&gt;f_op
op_assign
id|new_fops
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sound_loader_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_op-&gt;open
)paren
(brace
id|err
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
(brace
id|fops_put
c_func
(paren
id|file-&gt;f_op
)paren
suffix:semicolon
id|file-&gt;f_op
op_assign
id|fops_get
c_func
(paren
id|old_fops
)paren
suffix:semicolon
)brace
id|fops_put
c_func
(paren
id|old_fops
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|sound_loader_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_extern
r_int
id|mod_firmware_load
c_func
(paren
r_const
r_char
op_star
comma
r_char
op_star
op_star
)paren
suffix:semicolon
DECL|variable|mod_firmware_load
id|EXPORT_SYMBOL
c_func
(paren
id|mod_firmware_load
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Core sound module&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Alan Cox&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
singleline_comment|// MODULE_ALIAS_CHARDEV_MAJOR(SOUND_MAJOR);
id|MODULE_ALIAS
c_func
(paren
l_string|&quot;char-major-&quot;
id|__stringify
c_func
(paren
id|SOUND_MAJOR
)paren
)paren
suffix:semicolon
DECL|function|cleanup_soundcore
r_static
r_void
id|__exit
id|cleanup_soundcore
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* We have nothing to really do here - we know the lists must be&n;&t;   empty */
id|unregister_chrdev
c_func
(paren
id|SOUND_MAJOR
comma
l_string|&quot;sound&quot;
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;sound&quot;
)paren
suffix:semicolon
)brace
DECL|function|init_soundcore
r_static
r_int
id|__init
id|init_soundcore
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|SOUND_MAJOR
comma
l_string|&quot;sound&quot;
comma
op_amp
id|soundcore_fops
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;soundcore: sound device already in use.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|devfs_mk_dir
(paren
l_string|&quot;sound&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_soundcore
id|module_init
c_func
(paren
id|init_soundcore
)paren
suffix:semicolon
DECL|variable|cleanup_soundcore
id|module_exit
c_func
(paren
id|cleanup_soundcore
)paren
suffix:semicolon
eof
