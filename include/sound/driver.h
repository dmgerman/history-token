macro_line|#ifndef __SOUND_DRIVER_H
DECL|macro|__SOUND_DRIVER_H
mdefine_line|#define __SOUND_DRIVER_H
multiline_comment|/*&n; *  Main header file for the ALSA driver&n; *  Copyright (c) 1994-2000 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifdef ALSA_BUILD
macro_line|#include &quot;config.h&quot;
macro_line|#endif
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
DECL|macro|SNDRV_CARDS
mdefine_line|#define SNDRV_CARDS&t;&t;8&t;/* number of supported soundcards - don&squot;t change - minor numbers */
macro_line|#ifndef CONFIG_SND_MAJOR&t;/* standard configuration */
DECL|macro|CONFIG_SND_MAJOR
mdefine_line|#define CONFIG_SND_MAJOR&t;116
macro_line|#endif
macro_line|#ifndef CONFIG_SND_DEBUG
DECL|macro|CONFIG_SND_DEBUG_MEMORY
macro_line|#undef CONFIG_SND_DEBUG_MEMORY
macro_line|#endif
macro_line|#ifdef ALSA_BUILD
macro_line|#include &quot;adriver.h&quot;
macro_line|#endif
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/*&n; *  ==========================================================================&n; */
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2, 4, 0)
macro_line|#if defined(__i386__) || defined(__ppc__)
multiline_comment|/*&n; * Here a dirty hack for 2.4 kernels.. See kernel/memory.c.&n; */
DECL|macro|HACK_PCI_ALLOC_CONSISTENT
mdefine_line|#define HACK_PCI_ALLOC_CONSISTENT
macro_line|#include &lt;linux/pci.h&gt;
r_void
op_star
id|snd_pci_hack_alloc_consistent
c_func
(paren
r_struct
id|pci_dev
op_star
id|hwdev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
)paren
suffix:semicolon
DECL|macro|pci_alloc_consistent
macro_line|#undef pci_alloc_consistent
DECL|macro|pci_alloc_consistent
mdefine_line|#define pci_alloc_consistent snd_pci_hack_alloc_consistent
macro_line|#endif /* i386 or ppc */
macro_line|#endif /* 2.4.0 */
macro_line|#ifdef CONFIG_SND_DEBUG_MEMORY
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
r_void
op_star
id|snd_wrapper_kmalloc
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|kmalloc
macro_line|#undef kmalloc
r_void
id|snd_wrapper_kfree
c_func
(paren
r_const
r_void
op_star
)paren
suffix:semicolon
DECL|macro|kfree
macro_line|#undef kfree
r_void
op_star
id|snd_wrapper_vmalloc
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|macro|vmalloc
macro_line|#undef vmalloc
r_void
id|snd_wrapper_vfree
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|macro|vfree
macro_line|#undef vfree
macro_line|#endif
macro_line|#include &quot;sndmagic.h&quot;
macro_line|#endif /* __SOUND_DRIVER_H */
eof
