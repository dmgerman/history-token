multiline_comment|/*&n; *  Various wrappers&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifdef ALSA_BUILD
macro_line|#include &quot;config.h&quot;
macro_line|#endif
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef ALSA_BUILD
macro_line|#if defined(CONFIG_MODVERSIONS) &amp;&amp; !defined(__GENKSYMS__) &amp;&amp; !defined(__DEPEND__)
DECL|macro|MODVERSIONS
mdefine_line|#define MODVERSIONS
macro_line|#include &lt;linux/modversions.h&gt;
macro_line|#include &quot;sndversions.h&quot;
macro_line|#endif
macro_line|#endif
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#ifdef CONFIG_SND_DEBUG_MEMORY
DECL|function|snd_wrapper_kmalloc
r_void
op_star
id|snd_wrapper_kmalloc
c_func
(paren
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_wrapper_kfree
r_void
id|snd_wrapper_kfree
c_func
(paren
r_const
r_void
op_star
id|obj
)paren
(brace
id|kfree
c_func
(paren
id|obj
)paren
suffix:semicolon
)brace
DECL|function|snd_wrapper_vmalloc
r_void
op_star
id|snd_wrapper_vmalloc
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_return
id|vmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
)brace
DECL|function|snd_wrapper_vfree
r_void
id|snd_wrapper_vfree
c_func
(paren
r_void
op_star
id|obj
)paren
(brace
id|vfree
c_func
(paren
id|obj
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
