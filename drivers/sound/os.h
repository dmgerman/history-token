DECL|macro|ALLOW_SELECT
mdefine_line|#define ALLOW_SELECT
DECL|macro|NO_INLINE_ASM
macro_line|#undef NO_INLINE_ASM
DECL|macro|SHORT_BANNERS
mdefine_line|#define SHORT_BANNERS
DECL|macro|MANUAL_PNP
mdefine_line|#define MANUAL_PNP
DECL|macro|DO_TIMINGS
macro_line|#undef  DO_TIMINGS
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if LINUX_VERSION_CODE &gt; 131328
DECL|macro|LINUX21X
mdefine_line|#define LINUX21X
macro_line|#endif
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/param.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifdef __alpha__
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/wrapper.h&gt;
macro_line|#include &lt;linux/soundcard.h&gt;
DECL|macro|FALSE
mdefine_line|#define FALSE&t;0
DECL|macro|TRUE
mdefine_line|#define TRUE&t;1
r_extern
r_int
id|sound_alloc_dma
c_func
(paren
r_int
id|chn
comma
r_char
op_star
id|deviceID
)paren
suffix:semicolon
r_extern
r_int
id|sound_open_dma
c_func
(paren
r_int
id|chn
comma
r_char
op_star
id|deviceID
)paren
suffix:semicolon
r_extern
r_void
id|sound_free_dma
c_func
(paren
r_int
id|chn
)paren
suffix:semicolon
r_extern
r_void
id|sound_close_dma
c_func
(paren
r_int
id|chn
)paren
suffix:semicolon
r_extern
r_void
id|reprogram_timer
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|USE_AUTOINIT_DMA
mdefine_line|#define USE_AUTOINIT_DMA
r_extern
id|caddr_t
id|sound_mem_blocks
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
r_int
id|sound_nblocks
suffix:semicolon
DECL|macro|PSEUDO_DMA_AUTOINIT
macro_line|#undef PSEUDO_DMA_AUTOINIT
DECL|macro|ALLOW_BUFFER_MAPPING
mdefine_line|#define ALLOW_BUFFER_MAPPING
r_extern
r_struct
id|file_operations
id|oss_sound_fops
suffix:semicolon
eof
