macro_line|#ifndef __SOUND_CORE_H
DECL|macro|__SOUND_CORE_H
mdefine_line|#define __SOUND_CORE_H
multiline_comment|/*&n; *  Main header file for the ALSA driver&n; *  Copyright (c) 1994-2001 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifdef CONFIG_PM
macro_line|#include &lt;linux/sched.h&gt;&t;&t;/* wake_up() and struct semaphore */
macro_line|#endif
multiline_comment|/* Typedef&squot;s */
DECL|typedef|snd_timestamp_t
r_typedef
r_struct
id|timeval
id|snd_timestamp_t
suffix:semicolon
DECL|typedef|snd_interval_t
r_typedef
r_struct
id|sndrv_interval
id|snd_interval_t
suffix:semicolon
DECL|typedef|snd_card_type
r_typedef
r_enum
id|sndrv_card_type
id|snd_card_type
suffix:semicolon
DECL|typedef|snd_xferi_t
r_typedef
r_struct
id|sndrv_xferi
id|snd_xferi_t
suffix:semicolon
DECL|typedef|snd_xfern_t
r_typedef
r_struct
id|sndrv_xfern
id|snd_xfern_t
suffix:semicolon
DECL|typedef|snd_xferv_t
r_typedef
r_struct
id|sndrv_xferv
id|snd_xferv_t
suffix:semicolon
multiline_comment|/* device allocation stuff */
DECL|macro|SNDRV_DEV_TYPE_RANGE_SIZE
mdefine_line|#define SNDRV_DEV_TYPE_RANGE_SIZE&t;&t;0x1000
r_typedef
r_enum
(brace
DECL|enumerator|SNDRV_DEV_TOPLEVEL
id|SNDRV_DEV_TOPLEVEL
op_assign
(paren
l_int|0
op_star
id|SNDRV_DEV_TYPE_RANGE_SIZE
)paren
comma
DECL|enumerator|SNDRV_DEV_LOWLEVEL_PRE
id|SNDRV_DEV_LOWLEVEL_PRE
comma
DECL|enumerator|SNDRV_DEV_LOWLEVEL_NORMAL
id|SNDRV_DEV_LOWLEVEL_NORMAL
op_assign
(paren
l_int|1
op_star
id|SNDRV_DEV_TYPE_RANGE_SIZE
)paren
comma
DECL|enumerator|SNDRV_DEV_PCM
id|SNDRV_DEV_PCM
comma
DECL|enumerator|SNDRV_DEV_RAWMIDI
id|SNDRV_DEV_RAWMIDI
comma
DECL|enumerator|SNDRV_DEV_TIMER
id|SNDRV_DEV_TIMER
comma
DECL|enumerator|SNDRV_DEV_SEQUENCER
id|SNDRV_DEV_SEQUENCER
comma
DECL|enumerator|SNDRV_DEV_HWDEP
id|SNDRV_DEV_HWDEP
comma
DECL|enumerator|SNDRV_DEV_LOWLEVEL
id|SNDRV_DEV_LOWLEVEL
op_assign
(paren
l_int|2
op_star
id|SNDRV_DEV_TYPE_RANGE_SIZE
)paren
DECL|typedef|snd_device_type_t
)brace
id|snd_device_type_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|SNDRV_DEV_BUILD
id|SNDRV_DEV_BUILD
op_assign
l_int|0
comma
DECL|enumerator|SNDRV_DEV_REGISTERED
id|SNDRV_DEV_REGISTERED
op_assign
l_int|1
DECL|typedef|snd_device_state_t
)brace
id|snd_device_state_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|SNDRV_DEV_CMD_PRE
id|SNDRV_DEV_CMD_PRE
op_assign
l_int|0
comma
DECL|enumerator|SNDRV_DEV_CMD_NORMAL
id|SNDRV_DEV_CMD_NORMAL
op_assign
l_int|1
comma
DECL|enumerator|SNDRV_DEV_CMD_POST
id|SNDRV_DEV_CMD_POST
op_assign
l_int|2
DECL|typedef|snd_device_cmd_t
)brace
id|snd_device_cmd_t
suffix:semicolon
DECL|typedef|snd_card_t
r_typedef
r_struct
id|_snd_card
id|snd_card_t
suffix:semicolon
DECL|typedef|snd_device_t
r_typedef
r_struct
id|_snd_device
id|snd_device_t
suffix:semicolon
DECL|typedef|snd_dev_free_t
r_typedef
r_int
(paren
id|snd_dev_free_t
)paren
(paren
id|snd_device_t
op_star
id|device
)paren
suffix:semicolon
DECL|typedef|snd_dev_register_t
r_typedef
r_int
(paren
id|snd_dev_register_t
)paren
(paren
id|snd_device_t
op_star
id|device
)paren
suffix:semicolon
DECL|typedef|snd_dev_unregister_t
r_typedef
r_int
(paren
id|snd_dev_unregister_t
)paren
(paren
id|snd_device_t
op_star
id|device
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|dev_free
id|snd_dev_free_t
op_star
id|dev_free
suffix:semicolon
DECL|member|dev_register
id|snd_dev_register_t
op_star
id|dev_register
suffix:semicolon
DECL|member|dev_unregister
id|snd_dev_unregister_t
op_star
id|dev_unregister
suffix:semicolon
DECL|typedef|snd_device_ops_t
)brace
id|snd_device_ops_t
suffix:semicolon
DECL|struct|_snd_device
r_struct
id|_snd_device
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list of registered devices */
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
multiline_comment|/* card which holds this device */
DECL|member|state
id|snd_device_state_t
id|state
suffix:semicolon
multiline_comment|/* state of the device */
DECL|member|type
id|snd_device_type_t
id|type
suffix:semicolon
multiline_comment|/* device type */
DECL|member|device_data
r_void
op_star
id|device_data
suffix:semicolon
multiline_comment|/* device structure */
DECL|member|ops
id|snd_device_ops_t
op_star
id|ops
suffix:semicolon
multiline_comment|/* operations */
)brace
suffix:semicolon
DECL|macro|snd_device
mdefine_line|#define snd_device(n) list_entry(n, snd_device_t, list)
multiline_comment|/* various typedefs */
DECL|typedef|snd_info_entry_t
r_typedef
r_struct
id|snd_info_entry
id|snd_info_entry_t
suffix:semicolon
DECL|typedef|snd_pcm_t
r_typedef
r_struct
id|_snd_pcm
id|snd_pcm_t
suffix:semicolon
DECL|typedef|snd_pcm_str_t
r_typedef
r_struct
id|_snd_pcm_str
id|snd_pcm_str_t
suffix:semicolon
DECL|typedef|snd_pcm_substream_t
r_typedef
r_struct
id|_snd_pcm_substream
id|snd_pcm_substream_t
suffix:semicolon
DECL|typedef|snd_kmixer_t
r_typedef
r_struct
id|_snd_mixer
id|snd_kmixer_t
suffix:semicolon
DECL|typedef|snd_rawmidi_t
r_typedef
r_struct
id|_snd_rawmidi
id|snd_rawmidi_t
suffix:semicolon
DECL|typedef|snd_ctl_file_t
r_typedef
r_struct
id|_snd_ctl_file
id|snd_ctl_file_t
suffix:semicolon
DECL|typedef|snd_kcontrol_t
r_typedef
r_struct
id|_snd_kcontrol
id|snd_kcontrol_t
suffix:semicolon
DECL|typedef|snd_timer_t
r_typedef
r_struct
id|_snd_timer
id|snd_timer_t
suffix:semicolon
DECL|typedef|snd_timer_instance_t
r_typedef
r_struct
id|_snd_timer_instance
id|snd_timer_instance_t
suffix:semicolon
DECL|typedef|snd_hwdep_t
r_typedef
r_struct
id|_snd_hwdep
id|snd_hwdep_t
suffix:semicolon
macro_line|#ifdef CONFIG_SND_OSSEMUL
DECL|typedef|snd_mixer_oss_t
r_typedef
r_struct
id|_snd_oss_mixer
id|snd_mixer_oss_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* main structure for soundcard */
DECL|struct|_snd_card
r_struct
id|_snd_card
(brace
DECL|member|number
r_int
id|number
suffix:semicolon
multiline_comment|/* number of soundcard (index to snd_cards) */
DECL|member|id
r_char
id|id
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* id string of this card */
DECL|member|driver
r_char
id|driver
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* driver name */
DECL|member|shortname
r_char
id|shortname
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* short name of this soundcard */
DECL|member|longname
r_char
id|longname
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* name of this soundcard */
DECL|member|mixername
r_char
id|mixername
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* mixer name */
DECL|member|components
r_char
id|components
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* card components delimited with space */
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
multiline_comment|/* top-level module */
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
multiline_comment|/* private data for soundcard */
DECL|member|private_free
r_void
(paren
op_star
id|private_free
)paren
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
multiline_comment|/* callback for freeing of private data */
DECL|member|devices
r_struct
id|list_head
id|devices
suffix:semicolon
multiline_comment|/* devices */
DECL|member|last_numid
r_int
r_int
id|last_numid
suffix:semicolon
multiline_comment|/* last used numeric ID */
DECL|member|control_rwlock
id|rwlock_t
id|control_rwlock
suffix:semicolon
multiline_comment|/* control list lock */
DECL|member|control_owner_lock
id|rwlock_t
id|control_owner_lock
suffix:semicolon
multiline_comment|/* control list lock */
DECL|member|controls_count
r_int
id|controls_count
suffix:semicolon
multiline_comment|/* count of all controls */
DECL|member|controls
r_struct
id|list_head
id|controls
suffix:semicolon
multiline_comment|/* all controls for this card */
DECL|member|ctl_files
r_struct
id|list_head
id|ctl_files
suffix:semicolon
multiline_comment|/* active control files */
DECL|member|proc_root
id|snd_info_entry_t
op_star
id|proc_root
suffix:semicolon
multiline_comment|/* root for soundcard specific files */
DECL|member|proc_id
id|snd_info_entry_t
op_star
id|proc_id
suffix:semicolon
multiline_comment|/* the card id */
DECL|member|proc_root_link
r_struct
id|proc_dir_entry
op_star
id|proc_root_link
suffix:semicolon
multiline_comment|/* number link to real id */
macro_line|#ifdef CONFIG_PM
DECL|member|set_power_state
r_int
(paren
op_star
id|set_power_state
)paren
(paren
id|snd_card_t
op_star
id|card
comma
r_int
r_int
id|state
)paren
suffix:semicolon
DECL|member|power_state_private_data
r_void
op_star
id|power_state_private_data
suffix:semicolon
DECL|member|power_state
r_int
r_int
id|power_state
suffix:semicolon
multiline_comment|/* power state */
DECL|member|power_lock
r_struct
id|semaphore
id|power_lock
suffix:semicolon
multiline_comment|/* power lock */
DECL|member|power_sleep
id|wait_queue_head_t
id|power_sleep
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SND_OSSEMUL
DECL|member|mixer_oss
id|snd_mixer_oss_t
op_star
id|mixer_oss
suffix:semicolon
DECL|member|mixer_oss_change_count
r_int
id|mixer_oss_change_count
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_PM
DECL|function|snd_power_lock
r_static
r_inline
r_void
id|snd_power_lock
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
id|down
c_func
(paren
op_amp
id|card-&gt;power_lock
)paren
suffix:semicolon
)brace
DECL|function|snd_power_unlock
r_static
r_inline
r_void
id|snd_power_unlock
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
id|up
c_func
(paren
op_amp
id|card-&gt;power_lock
)paren
suffix:semicolon
)brace
r_void
id|snd_power_wait
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
DECL|function|snd_power_get_state
r_static
r_inline
r_int
r_int
id|snd_power_get_state
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_return
id|card-&gt;power_state
suffix:semicolon
)brace
DECL|function|snd_power_change_state
r_static
r_inline
r_void
id|snd_power_change_state
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
r_int
id|state
)paren
(brace
id|card-&gt;power_state
op_assign
id|state
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|card-&gt;power_sleep
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|snd_power_lock
mdefine_line|#define snd_power_lock(card) do { ; } while (0)
DECL|macro|snd_power_unlock
mdefine_line|#define snd_power_unlock(card) do { ; } while (0)
DECL|macro|snd_power_wait
mdefine_line|#define snd_power_wait(card) do { ; } while (0)
DECL|macro|snd_power_get_state
mdefine_line|#define snd_power_get_state(card) SNDRV_CTL_POWER_D0
DECL|macro|snd_power_change_state
mdefine_line|#define snd_power_change_state(card, state) do { ; } while (0)
macro_line|#endif
multiline_comment|/* device.c */
DECL|struct|_snd_minor
r_struct
id|_snd_minor
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list of all minors per card */
DECL|member|number
r_int
id|number
suffix:semicolon
multiline_comment|/* minor number */
DECL|member|device
r_int
id|device
suffix:semicolon
multiline_comment|/* device number */
DECL|member|comment
r_const
r_char
op_star
id|comment
suffix:semicolon
multiline_comment|/* for /proc/asound/devices */
DECL|member|dev
id|snd_info_entry_t
op_star
id|dev
suffix:semicolon
multiline_comment|/* for /proc/asound/dev */
DECL|member|f_ops
r_struct
id|file_operations
op_star
id|f_ops
suffix:semicolon
multiline_comment|/* file operations */
)brace
suffix:semicolon
DECL|typedef|snd_minor_t
r_typedef
r_struct
id|_snd_minor
id|snd_minor_t
suffix:semicolon
multiline_comment|/* sound.c */
r_extern
r_int
id|snd_ecards_limit
suffix:semicolon
r_extern
r_int
id|snd_device_mode
suffix:semicolon
r_extern
r_int
id|snd_device_gid
suffix:semicolon
r_extern
r_int
id|snd_device_uid
suffix:semicolon
r_void
id|snd_request_card
c_func
(paren
r_int
id|card
)paren
suffix:semicolon
r_int
id|snd_register_device
c_func
(paren
r_int
id|type
comma
id|snd_card_t
op_star
id|card
comma
r_int
id|dev
comma
id|snd_minor_t
op_star
id|reg
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|snd_unregister_device
c_func
(paren
r_int
id|type
comma
id|snd_card_t
op_star
id|card
comma
r_int
id|dev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_OSSEMUL
r_int
id|snd_register_oss_device
c_func
(paren
r_int
id|type
comma
id|snd_card_t
op_star
id|card
comma
r_int
id|dev
comma
id|snd_minor_t
op_star
id|reg
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|snd_unregister_oss_device
c_func
(paren
r_int
id|type
comma
id|snd_card_t
op_star
id|card
comma
r_int
id|dev
)paren
suffix:semicolon
macro_line|#endif
r_int
id|snd_minor_info_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|snd_minor_info_done
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* sound_oss.c */
macro_line|#ifdef CONFIG_SND_OSSEMUL
r_int
id|snd_minor_info_oss_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|snd_minor_info_oss_done
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|snd_oss_init_module
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|snd_oss_cleanup_module
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* memory.c */
macro_line|#ifdef CONFIG_SND_DEBUG_MEMORY
r_void
id|snd_memory_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|snd_memory_done
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|snd_memory_info_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|snd_memory_info_done
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
op_star
id|snd_hidden_kmalloc
c_func
(paren
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
r_void
id|snd_hidden_kfree
c_func
(paren
r_const
r_void
op_star
id|obj
)paren
suffix:semicolon
r_void
op_star
id|snd_hidden_vmalloc
c_func
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
r_void
id|snd_hidden_vfree
c_func
(paren
r_void
op_star
id|obj
)paren
suffix:semicolon
DECL|macro|kmalloc
mdefine_line|#define kmalloc(size, flags) snd_hidden_kmalloc(size, flags)
DECL|macro|kfree
mdefine_line|#define kfree(obj) snd_hidden_kfree(obj)
DECL|macro|kfree_nocheck
mdefine_line|#define kfree_nocheck(obj) snd_wrapper_kfree(obj)
DECL|macro|vmalloc
mdefine_line|#define vmalloc(size) snd_hidden_vmalloc(size)
DECL|macro|vfree
mdefine_line|#define vfree(obj) snd_hidden_vfree(obj)
macro_line|#else
DECL|macro|kfree_nocheck
mdefine_line|#define kfree_nocheck(obj) kfree(obj)
macro_line|#endif
r_void
op_star
id|snd_kcalloc
c_func
(paren
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
r_char
op_star
id|snd_kmalloc_strdup
c_func
(paren
r_const
r_char
op_star
id|string
comma
r_int
id|flags
)paren
suffix:semicolon
r_void
op_star
id|snd_malloc_pages
c_func
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|dma_flags
)paren
suffix:semicolon
r_void
op_star
id|snd_malloc_pages_fallback
c_func
(paren
r_int
r_int
id|size
comma
r_int
r_int
id|dma_flags
comma
r_int
r_int
op_star
id|res_size
)paren
suffix:semicolon
r_void
id|snd_free_pages
c_func
(paren
r_void
op_star
id|ptr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ISA
r_void
op_star
id|snd_malloc_isa_pages
c_func
(paren
r_int
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
)paren
suffix:semicolon
r_void
op_star
id|snd_malloc_isa_pages_fallback
c_func
(paren
r_int
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
comma
r_int
r_int
op_star
id|res_size
)paren
suffix:semicolon
DECL|macro|snd_free_isa_pages
mdefine_line|#define snd_free_isa_pages(size, ptr, dma_addr) snd_free_pages(ptr, size)
macro_line|#endif
macro_line|#ifdef CONFIG_PCI
r_void
op_star
id|snd_malloc_pci_pages
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
)paren
suffix:semicolon
r_void
op_star
id|snd_malloc_pci_pages_fallback
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_addr
comma
r_int
r_int
op_star
id|res_size
)paren
suffix:semicolon
r_void
id|snd_free_pci_pages
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
r_int
id|size
comma
r_void
op_star
id|ptr
comma
id|dma_addr_t
id|dma_addr
)paren
suffix:semicolon
macro_line|#endif
r_int
id|copy_to_user_fromio
c_func
(paren
r_void
op_star
id|dst
comma
r_int
r_int
id|src
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|copy_from_user_toio
c_func
(paren
r_int
r_int
id|dst
comma
r_const
r_void
op_star
id|src
comma
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* init.c */
r_extern
r_int
id|snd_cards_count
suffix:semicolon
r_extern
id|snd_card_t
op_star
id|snd_cards
(braket
id|SNDRV_CARDS
)braket
suffix:semicolon
r_extern
id|rwlock_t
id|snd_card_rwlock
suffix:semicolon
macro_line|#ifdef CONFIG_SND_OSSEMUL
r_extern
r_int
(paren
op_star
id|snd_mixer_oss_notify_callback
)paren
(paren
id|snd_card_t
op_star
id|card
comma
r_int
id|free_flag
)paren
suffix:semicolon
macro_line|#endif
id|snd_card_t
op_star
id|snd_card_new
c_func
(paren
r_int
id|idx
comma
r_const
r_char
op_star
id|id
comma
r_struct
id|module
op_star
id|module
comma
r_int
id|extra_size
)paren
suffix:semicolon
r_int
id|snd_card_free
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
r_int
id|snd_card_register
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
r_int
id|snd_card_info_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|snd_card_info_done
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|snd_component_add
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_const
r_char
op_star
id|component
)paren
suffix:semicolon
multiline_comment|/* device.c */
r_int
id|snd_device_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|snd_device_type_t
id|type
comma
r_void
op_star
id|device_data
comma
id|snd_device_ops_t
op_star
id|ops
)paren
suffix:semicolon
r_int
id|snd_device_register
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_void
op_star
id|device_data
)paren
suffix:semicolon
r_int
id|snd_device_register_all
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
r_int
id|snd_device_free
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_void
op_star
id|device_data
)paren
suffix:semicolon
r_int
id|snd_device_free_all
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|snd_device_cmd_t
id|cmd
)paren
suffix:semicolon
multiline_comment|/* isadma.c */
DECL|macro|DMA_MODE_NO_ENABLE
mdefine_line|#define DMA_MODE_NO_ENABLE&t;0x0100
r_void
id|snd_dma_program
c_func
(paren
r_int
r_int
id|dma
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|mode
)paren
suffix:semicolon
r_void
id|snd_dma_disable
c_func
(paren
r_int
r_int
id|dma
)paren
suffix:semicolon
r_int
r_int
id|snd_dma_residue
c_func
(paren
r_int
r_int
id|dma
)paren
suffix:semicolon
multiline_comment|/* misc.c */
r_int
id|snd_task_name
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_char
op_star
id|name
comma
r_int
id|size
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_VERBOSE_PRINTK
r_int
id|snd_verbose_printk
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_const
r_char
op_star
id|format
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* --- */
macro_line|#ifdef CONFIG_SND_VERBOSE_PRINTK
DECL|macro|snd_printk
mdefine_line|#define snd_printk(format, args...) do { &bslash;&n;&t;printk(snd_verbose_printk(__FILE__, __LINE__, format) ? format + 3 : format, ##args); &bslash;&n;} while (0)
macro_line|#else
DECL|macro|snd_printk
mdefine_line|#define snd_printk(format, args...) do { &bslash;&n;&t;printk(format, ##args); &bslash;&n;} while (0)
macro_line|#endif
macro_line|#ifdef CONFIG_SND_DEBUG
DECL|macro|__ASTRING__
mdefine_line|#define __ASTRING__(x) #x
DECL|macro|snd_printd
mdefine_line|#define snd_printd(format, args...) snd_printk(format, ##args)
DECL|macro|snd_assert
mdefine_line|#define snd_assert(expr, args...) do {&bslash;&n;&t;if (!(expr)) {&bslash;&n;&t;&t;snd_printk(&quot;BUG? (%s) (called from %p)&bslash;n&quot;, __ASTRING__(expr), __builtin_return_address(0));&bslash;&n;&t;&t;args;&bslash;&n;&t;}&bslash;&n;} while (0)
DECL|macro|snd_runtime_check
mdefine_line|#define snd_runtime_check(expr, args...) do {&bslash;&n;&t;if (!(expr)) {&bslash;&n;&t;&t;snd_printk(&quot;ERROR (%s) (called from %p)&bslash;n&quot;, __ASTRING__(expr), __builtin_return_address(0));&bslash;&n;&t;&t;args;&bslash;&n;&t;}&bslash;&n;} while (0)
macro_line|#else /* !CONFIG_SND_DEBUG */
DECL|macro|snd_printd
mdefine_line|#define snd_printd(format, args...)&t;/* nothing */
DECL|macro|snd_assert
mdefine_line|#define snd_assert(expr, args...)&t;/* nothing */
DECL|macro|snd_runtime_check
mdefine_line|#define snd_runtime_check(expr, args...) do { if (!(expr)) { args; } } while (0)
macro_line|#endif /* CONFIG_SND_DEBUG */
macro_line|#ifdef CONFIG_SND_DEBUG_DETECT
DECL|macro|snd_printdd
mdefine_line|#define snd_printdd(format, args...) snd_printk(format, ##args)
macro_line|#else
DECL|macro|snd_printdd
mdefine_line|#define snd_printdd(format, args...) /* nothing */
macro_line|#endif
DECL|macro|snd_BUG
mdefine_line|#define snd_BUG() snd_assert(0, )
DECL|macro|snd_timestamp_now
mdefine_line|#define snd_timestamp_now(tstamp) do_gettimeofday(tstamp)
DECL|macro|snd_timestamp_zero
mdefine_line|#define snd_timestamp_zero(tstamp) do { (tstamp)-&gt;tv_sec = 0; (tstamp)-&gt;tv_usec = 0; } while (0)
DECL|macro|snd_timestamp_null
mdefine_line|#define snd_timestamp_null(tstamp) ((tstamp)-&gt;tv_sec == 0 &amp;&amp; (tstamp)-&gt;tv_usec ==0)
DECL|macro|SNDRV_OSS_VERSION
mdefine_line|#define SNDRV_OSS_VERSION         ((3&lt;&lt;16)|(8&lt;&lt;8)|(1&lt;&lt;4)|(0))&t;/* 3.8.1a */
macro_line|#endif /* __SOUND_CORE_H */
eof
