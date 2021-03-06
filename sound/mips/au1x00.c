multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; *  Driver for AMD Au1000 MIPS Processor, AC&squot;97 Sound Port&n; *&n; * Copyright 2004 Cooper Street Innovations Inc.&n; * Author: Charles Eidsness&t;&lt;charles@cooper-street.com&gt;&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * History:&n; *&n; * 2004-09-09 Charles Eidsness&t;-- Original verion -- based on&n; * &t;&t;&t;&t;  sa11xx-uda1341.c ALSA driver and the&n; *&t;&t;&t;&t;  au1000.c OSS driver.&n; * 2004-09-09 Matt Porter&t;-- Added support for ALSA 1.0.6&n; *&n; */
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &lt;sound/ac97_codec.h&gt;
macro_line|#include &lt;asm/mach-au1x00/au1000.h&gt;
macro_line|#include &lt;asm/mach-au1x00/au1000_dma.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Charles Eidsness &lt;charles@cooper-street.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Au1000 AC&squot;97 ALSA Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,6,8)
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;{{AMD,Au1000 AC&squot;97}}&quot;
)paren
suffix:semicolon
macro_line|#else
id|MODULE_CLASSES
c_func
(paren
l_string|&quot;{sound}&quot;
)paren
suffix:semicolon
id|MODULE_DEVICES
c_func
(paren
l_string|&quot;{{AMD,Au1000 AC&squot;97}}&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|chip_t
mdefine_line|#define chip_t au1000_t
DECL|macro|PLAYBACK
mdefine_line|#define PLAYBACK 0
DECL|macro|CAPTURE
mdefine_line|#define CAPTURE 1
DECL|macro|AC97_SLOT_3
mdefine_line|#define AC97_SLOT_3 0x01
DECL|macro|AC97_SLOT_4
mdefine_line|#define AC97_SLOT_4 0x02
DECL|macro|AC97_SLOT_6
mdefine_line|#define AC97_SLOT_6 0x08
DECL|macro|AC97_CMD_IRQ
mdefine_line|#define AC97_CMD_IRQ 31
DECL|macro|READ
mdefine_line|#define READ 0
DECL|macro|WRITE
mdefine_line|#define WRITE 1
DECL|macro|READ_WAIT
mdefine_line|#define READ_WAIT 2
DECL|macro|RW_DONE
mdefine_line|#define RW_DONE 3
DECL|variable|ac97_command_wq
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|ac97_command_wq
)paren
suffix:semicolon
DECL|typedef|au1000_period_t
r_typedef
r_struct
id|au1000_period
id|au1000_period_t
suffix:semicolon
DECL|struct|au1000_period
r_struct
id|au1000_period
(brace
DECL|member|start
id|u32
id|start
suffix:semicolon
DECL|member|relative_end
id|u32
id|relative_end
suffix:semicolon
multiline_comment|/*realtive to start of buffer*/
DECL|member|next
id|au1000_period_t
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*Au1000 AC97 Port Control Reisters*/
DECL|typedef|au1000_ac97_reg_t
r_typedef
r_struct
id|au1000_ac97_reg
id|au1000_ac97_reg_t
suffix:semicolon
DECL|struct|au1000_ac97_reg
r_struct
id|au1000_ac97_reg
(brace
DECL|member|config
id|u32
r_volatile
id|config
suffix:semicolon
DECL|member|status
id|u32
r_volatile
id|status
suffix:semicolon
DECL|member|data
id|u32
r_volatile
id|data
suffix:semicolon
DECL|member|cmd
id|u32
r_volatile
id|cmd
suffix:semicolon
DECL|member|cntrl
id|u32
r_volatile
id|cntrl
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|audio_stream_t
r_typedef
r_struct
id|audio_stream
id|audio_stream_t
suffix:semicolon
DECL|struct|audio_stream
r_struct
id|audio_stream
(brace
DECL|member|substream
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
DECL|member|dma
r_int
id|dma
suffix:semicolon
DECL|member|dma_lock
id|spinlock_t
id|dma_lock
suffix:semicolon
DECL|member|buffer
id|au1000_period_t
op_star
id|buffer
suffix:semicolon
DECL|member|period_size
r_int
r_int
id|period_size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|snd_card_au1000
r_typedef
r_struct
id|snd_card_au1000
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|ac97_ioport
id|au1000_ac97_reg_t
r_volatile
op_star
id|ac97_ioport
suffix:semicolon
DECL|member|ac97_res_port
r_struct
id|resource
op_star
id|ac97_res_port
suffix:semicolon
DECL|member|ac97_lock
id|spinlock_t
id|ac97_lock
suffix:semicolon
DECL|member|ac97
id|ac97_t
op_star
id|ac97
suffix:semicolon
DECL|member|pcm
id|snd_pcm_t
op_star
id|pcm
suffix:semicolon
DECL|member|stream
id|audio_stream_t
op_star
id|stream
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* playback &amp; capture */
DECL|typedef|au1000_t
)brace
id|au1000_t
suffix:semicolon
DECL|variable|au1000
r_static
id|au1000_t
op_star
id|au1000
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*--------------------------- Local Functions --------------------------------*/
r_static
r_void
DECL|function|au1000_set_ac97_xmit_slots
id|au1000_set_ac97_xmit_slots
c_func
(paren
r_int
id|xmit_slots
)paren
(brace
id|u32
r_volatile
id|ac97_config
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|au1000-&gt;ac97_lock
)paren
suffix:semicolon
id|ac97_config
op_assign
id|au1000-&gt;ac97_ioport-&gt;config
suffix:semicolon
id|ac97_config
op_assign
id|ac97_config
op_amp
op_complement
id|AC97C_XMIT_SLOTS_MASK
suffix:semicolon
id|ac97_config
op_or_assign
(paren
id|xmit_slots
op_lshift
id|AC97C_XMIT_SLOTS_BIT
)paren
suffix:semicolon
id|au1000-&gt;ac97_ioport-&gt;config
op_assign
id|ac97_config
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|au1000-&gt;ac97_lock
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|au1000_set_ac97_recv_slots
id|au1000_set_ac97_recv_slots
c_func
(paren
r_int
id|recv_slots
)paren
(brace
id|u32
r_volatile
id|ac97_config
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|au1000-&gt;ac97_lock
)paren
suffix:semicolon
id|ac97_config
op_assign
id|au1000-&gt;ac97_ioport-&gt;config
suffix:semicolon
id|ac97_config
op_assign
id|ac97_config
op_amp
op_complement
id|AC97C_RECV_SLOTS_MASK
suffix:semicolon
id|ac97_config
op_or_assign
(paren
id|recv_slots
op_lshift
id|AC97C_RECV_SLOTS_BIT
)paren
suffix:semicolon
id|au1000-&gt;ac97_ioport-&gt;config
op_assign
id|ac97_config
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|au1000-&gt;ac97_lock
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|au1000_dma_stop
id|au1000_dma_stop
c_func
(paren
id|audio_stream_t
op_star
id|stream
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|au1000_period_t
op_star
id|pointer
suffix:semicolon
id|au1000_period_t
op_star
id|pointer_next
suffix:semicolon
r_if
c_cond
(paren
id|stream-&gt;buffer
op_ne
l_int|NULL
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|stream-&gt;dma_lock
comma
id|flags
)paren
suffix:semicolon
id|disable_dma
c_func
(paren
id|stream-&gt;dma
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|stream-&gt;dma_lock
comma
id|flags
)paren
suffix:semicolon
id|pointer
op_assign
id|stream-&gt;buffer
suffix:semicolon
id|pointer_next
op_assign
id|stream-&gt;buffer-&gt;next
suffix:semicolon
r_do
(brace
id|kfree
c_func
(paren
id|pointer
)paren
suffix:semicolon
id|pointer
op_assign
id|pointer_next
suffix:semicolon
id|pointer_next
op_assign
id|pointer-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pointer
op_ne
id|stream-&gt;buffer
)paren
suffix:semicolon
id|stream-&gt;buffer
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|au1000_dma_start
id|au1000_dma_start
c_func
(paren
id|audio_stream_t
op_star
id|stream
)paren
(brace
id|snd_pcm_substream_t
op_star
id|substream
op_assign
id|stream-&gt;substream
suffix:semicolon
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
r_int
r_int
id|flags
comma
id|dma_start
suffix:semicolon
r_int
id|i
suffix:semicolon
id|au1000_period_t
op_star
id|pointer
suffix:semicolon
r_if
c_cond
(paren
id|stream-&gt;buffer
op_eq
l_int|NULL
)paren
(brace
id|dma_start
op_assign
id|virt_to_phys
c_func
(paren
id|runtime-&gt;dma_area
)paren
suffix:semicolon
id|stream-&gt;period_size
op_assign
id|frames_to_bytes
c_func
(paren
id|runtime
comma
id|runtime-&gt;period_size
)paren
suffix:semicolon
id|stream-&gt;buffer
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|au1000_period_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|pointer
op_assign
id|stream-&gt;buffer
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|runtime-&gt;periods
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pointer-&gt;start
op_assign
(paren
id|u32
)paren
(paren
id|dma_start
op_plus
(paren
id|i
op_star
id|stream-&gt;period_size
)paren
)paren
suffix:semicolon
id|pointer-&gt;relative_end
op_assign
(paren
id|u32
)paren
(paren
(paren
(paren
id|i
op_plus
l_int|1
)paren
op_star
id|stream-&gt;period_size
)paren
op_minus
l_int|0x1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|runtime-&gt;periods
op_minus
l_int|1
)paren
(brace
id|pointer-&gt;next
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|au1000_period_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|pointer
op_assign
id|pointer-&gt;next
suffix:semicolon
)brace
)brace
id|pointer-&gt;next
op_assign
id|stream-&gt;buffer
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|stream-&gt;dma_lock
comma
id|flags
)paren
suffix:semicolon
id|init_dma
c_func
(paren
id|stream-&gt;dma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|get_dma_active_buffer
c_func
(paren
id|stream-&gt;dma
)paren
op_eq
l_int|0
)paren
(brace
id|clear_dma_done0
c_func
(paren
id|stream-&gt;dma
)paren
suffix:semicolon
id|set_dma_addr0
c_func
(paren
id|stream-&gt;dma
comma
id|stream-&gt;buffer-&gt;start
)paren
suffix:semicolon
id|set_dma_count0
c_func
(paren
id|stream-&gt;dma
comma
id|stream-&gt;period_size
op_rshift
l_int|1
)paren
suffix:semicolon
id|set_dma_addr1
c_func
(paren
id|stream-&gt;dma
comma
id|stream-&gt;buffer-&gt;next-&gt;start
)paren
suffix:semicolon
id|set_dma_count1
c_func
(paren
id|stream-&gt;dma
comma
id|stream-&gt;period_size
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|clear_dma_done1
c_func
(paren
id|stream-&gt;dma
)paren
suffix:semicolon
id|set_dma_addr1
c_func
(paren
id|stream-&gt;dma
comma
id|stream-&gt;buffer-&gt;start
)paren
suffix:semicolon
id|set_dma_count1
c_func
(paren
id|stream-&gt;dma
comma
id|stream-&gt;period_size
op_rshift
l_int|1
)paren
suffix:semicolon
id|set_dma_addr0
c_func
(paren
id|stream-&gt;dma
comma
id|stream-&gt;buffer-&gt;next-&gt;start
)paren
suffix:semicolon
id|set_dma_count0
c_func
(paren
id|stream-&gt;dma
comma
id|stream-&gt;period_size
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
id|enable_dma_buffers
c_func
(paren
id|stream-&gt;dma
)paren
suffix:semicolon
id|start_dma
c_func
(paren
id|stream-&gt;dma
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|stream-&gt;dma_lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
r_static
id|irqreturn_t
DECL|function|au1000_dma_interrupt
id|au1000_dma_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|audio_stream_t
op_star
id|stream
op_assign
(paren
id|audio_stream_t
op_star
)paren
id|dev_id
suffix:semicolon
id|snd_pcm_substream_t
op_star
id|substream
op_assign
id|stream-&gt;substream
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|stream-&gt;dma_lock
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|get_dma_buffer_done
c_func
(paren
id|stream-&gt;dma
)paren
)paren
(brace
r_case
id|DMA_D0
suffix:colon
id|stream-&gt;buffer
op_assign
id|stream-&gt;buffer-&gt;next
suffix:semicolon
id|clear_dma_done0
c_func
(paren
id|stream-&gt;dma
)paren
suffix:semicolon
id|set_dma_addr0
c_func
(paren
id|stream-&gt;dma
comma
id|stream-&gt;buffer-&gt;next-&gt;start
)paren
suffix:semicolon
id|set_dma_count0
c_func
(paren
id|stream-&gt;dma
comma
id|stream-&gt;period_size
op_rshift
l_int|1
)paren
suffix:semicolon
id|enable_dma_buffer0
c_func
(paren
id|stream-&gt;dma
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DMA_D1
suffix:colon
id|stream-&gt;buffer
op_assign
id|stream-&gt;buffer-&gt;next
suffix:semicolon
id|clear_dma_done1
c_func
(paren
id|stream-&gt;dma
)paren
suffix:semicolon
id|set_dma_addr1
c_func
(paren
id|stream-&gt;dma
comma
id|stream-&gt;buffer-&gt;next-&gt;start
)paren
suffix:semicolon
id|set_dma_count1
c_func
(paren
id|stream-&gt;dma
comma
id|stream-&gt;period_size
op_rshift
l_int|1
)paren
suffix:semicolon
id|enable_dma_buffer1
c_func
(paren
id|stream-&gt;dma
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|DMA_D0
op_or
id|DMA_D1
)paren
suffix:colon
id|spin_unlock
c_func
(paren
op_amp
id|stream-&gt;dma_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;DMA %d missed interrupt.&bslash;n&quot;
comma
id|stream-&gt;dma
)paren
suffix:semicolon
id|au1000_dma_stop
c_func
(paren
id|stream
)paren
suffix:semicolon
id|au1000_dma_start
c_func
(paren
id|stream
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|stream-&gt;dma_lock
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
op_complement
id|DMA_D0
op_amp
op_complement
id|DMA_D1
)paren
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;DMA %d empty irq.&bslash;n&quot;
comma
id|stream-&gt;dma
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|stream-&gt;dma_lock
)paren
suffix:semicolon
id|snd_pcm_period_elapsed
c_func
(paren
id|substream
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*-------------------------- PCM Audio Streams -------------------------------*/
DECL|variable|rates
r_static
r_int
r_int
id|rates
(braket
)braket
op_assign
(brace
l_int|8000
comma
l_int|11025
comma
l_int|16000
comma
l_int|22050
)brace
suffix:semicolon
DECL|variable|hw_constraints_rates
r_static
id|snd_pcm_hw_constraint_list_t
id|hw_constraints_rates
op_assign
(brace
dot
id|count
op_assign
r_sizeof
(paren
id|rates
)paren
op_div
r_sizeof
(paren
id|rates
(braket
l_int|0
)braket
)paren
comma
dot
id|list
op_assign
id|rates
comma
dot
id|mask
op_assign
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|snd_au1000
r_static
id|snd_pcm_hardware_t
id|snd_au1000
op_assign
(brace
dot
id|info
op_assign
(paren
id|SNDRV_PCM_INFO_INTERLEAVED
op_or
"&bslash;"
id|SNDRV_PCM_INFO_MMAP
op_or
id|SNDRV_PCM_INFO_MMAP_VALID
)paren
comma
dot
id|formats
op_assign
id|SNDRV_PCM_FMTBIT_S16_LE
comma
dot
id|rates
op_assign
(paren
id|SNDRV_PCM_RATE_8000
op_or
id|SNDRV_PCM_RATE_11025
op_or
id|SNDRV_PCM_RATE_16000
op_or
id|SNDRV_PCM_RATE_22050
)paren
comma
dot
id|rate_min
op_assign
l_int|8000
comma
dot
id|rate_max
op_assign
l_int|22050
comma
dot
id|channels_min
op_assign
l_int|1
comma
dot
id|channels_max
op_assign
l_int|2
comma
dot
id|buffer_bytes_max
op_assign
l_int|128
op_star
l_int|1024
comma
dot
id|period_bytes_min
op_assign
l_int|32
comma
dot
id|period_bytes_max
op_assign
l_int|16
op_star
l_int|1024
comma
dot
id|periods_min
op_assign
l_int|8
comma
dot
id|periods_max
op_assign
l_int|255
comma
dot
id|fifo_size
op_assign
l_int|16
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|snd_au1000_playback_open
id|snd_au1000_playback_open
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
op_member_access_from_pointer
id|substream
op_assign
id|substream
suffix:semicolon
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
op_member_access_from_pointer
id|buffer
op_assign
l_int|NULL
suffix:semicolon
id|substream-&gt;private_data
op_assign
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
suffix:semicolon
id|substream-&gt;runtime-&gt;hw
op_assign
id|snd_au1000
suffix:semicolon
r_return
(paren
id|snd_pcm_hw_constraint_list
c_func
(paren
id|substream-&gt;runtime
comma
l_int|0
comma
id|SNDRV_PCM_HW_PARAM_RATE
comma
op_amp
id|hw_constraints_rates
)paren
OL
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|snd_au1000_capture_open
id|snd_au1000_capture_open
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
op_member_access_from_pointer
id|substream
op_assign
id|substream
suffix:semicolon
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
op_member_access_from_pointer
id|buffer
op_assign
l_int|NULL
suffix:semicolon
id|substream-&gt;private_data
op_assign
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
suffix:semicolon
id|substream-&gt;runtime-&gt;hw
op_assign
id|snd_au1000
suffix:semicolon
r_return
(paren
id|snd_pcm_hw_constraint_list
c_func
(paren
id|substream-&gt;runtime
comma
l_int|0
comma
id|SNDRV_PCM_HW_PARAM_RATE
comma
op_amp
id|hw_constraints_rates
)paren
OL
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|snd_au1000_playback_close
id|snd_au1000_playback_close
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
op_member_access_from_pointer
id|substream
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|snd_au1000_capture_close
id|snd_au1000_capture_close
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
op_member_access_from_pointer
id|substream
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|snd_au1000_hw_params
id|snd_au1000_hw_params
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
id|snd_pcm_hw_params_t
op_star
id|hw_params
)paren
(brace
r_return
id|snd_pcm_lib_malloc_pages
c_func
(paren
id|substream
comma
id|params_buffer_bytes
c_func
(paren
id|hw_params
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|snd_au1000_hw_free
id|snd_au1000_hw_free
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_return
id|snd_pcm_lib_free_pages
c_func
(paren
id|substream
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|snd_au1000_playback_prepare
id|snd_au1000_playback_prepare
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
r_if
c_cond
(paren
id|runtime-&gt;channels
op_eq
l_int|1
)paren
id|au1000_set_ac97_xmit_slots
c_func
(paren
id|AC97_SLOT_4
)paren
suffix:semicolon
r_else
id|au1000_set_ac97_xmit_slots
c_func
(paren
id|AC97_SLOT_3
op_or
id|AC97_SLOT_4
)paren
suffix:semicolon
id|snd_ac97_set_rate
c_func
(paren
id|au1000-&gt;ac97
comma
id|AC97_PCM_FRONT_DAC_RATE
comma
id|runtime-&gt;rate
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|snd_au1000_capture_prepare
id|snd_au1000_capture_prepare
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
r_if
c_cond
(paren
id|runtime-&gt;channels
op_eq
l_int|1
)paren
id|au1000_set_ac97_recv_slots
c_func
(paren
id|AC97_SLOT_4
)paren
suffix:semicolon
r_else
id|au1000_set_ac97_recv_slots
c_func
(paren
id|AC97_SLOT_3
op_or
id|AC97_SLOT_4
)paren
suffix:semicolon
id|snd_ac97_set_rate
c_func
(paren
id|au1000-&gt;ac97
comma
id|AC97_PCM_LR_ADC_RATE
comma
id|runtime-&gt;rate
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|snd_au1000_trigger
id|snd_au1000_trigger
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
comma
r_int
id|cmd
)paren
(brace
id|audio_stream_t
op_star
id|stream
op_assign
id|substream-&gt;private_data
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDRV_PCM_TRIGGER_START
suffix:colon
id|au1000_dma_start
c_func
(paren
id|stream
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_PCM_TRIGGER_STOP
suffix:colon
id|au1000_dma_stop
c_func
(paren
id|stream
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
r_static
id|snd_pcm_uframes_t
DECL|function|snd_au1000_pointer
id|snd_au1000_pointer
c_func
(paren
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
id|audio_stream_t
op_star
id|stream
op_assign
id|substream-&gt;private_data
suffix:semicolon
id|snd_pcm_runtime_t
op_star
id|runtime
op_assign
id|substream-&gt;runtime
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|location
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|stream-&gt;dma_lock
comma
id|flags
)paren
suffix:semicolon
id|location
op_assign
id|get_dma_residue
c_func
(paren
id|stream-&gt;dma
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|stream-&gt;dma_lock
comma
id|flags
)paren
suffix:semicolon
id|location
op_assign
id|stream-&gt;buffer-&gt;relative_end
op_minus
id|location
suffix:semicolon
r_if
c_cond
(paren
id|location
op_eq
op_minus
l_int|1
)paren
id|location
op_assign
l_int|0
suffix:semicolon
r_return
id|bytes_to_frames
c_func
(paren
id|runtime
comma
id|location
)paren
suffix:semicolon
)brace
DECL|variable|snd_card_au1000_playback_ops
r_static
id|snd_pcm_ops_t
id|snd_card_au1000_playback_ops
op_assign
(brace
dot
id|open
op_assign
id|snd_au1000_playback_open
comma
dot
id|close
op_assign
id|snd_au1000_playback_close
comma
dot
id|ioctl
op_assign
id|snd_pcm_lib_ioctl
comma
dot
id|hw_params
op_assign
id|snd_au1000_hw_params
comma
dot
id|hw_free
op_assign
id|snd_au1000_hw_free
comma
dot
id|prepare
op_assign
id|snd_au1000_playback_prepare
comma
dot
id|trigger
op_assign
id|snd_au1000_trigger
comma
dot
id|pointer
op_assign
id|snd_au1000_pointer
comma
)brace
suffix:semicolon
DECL|variable|snd_card_au1000_capture_ops
r_static
id|snd_pcm_ops_t
id|snd_card_au1000_capture_ops
op_assign
(brace
dot
id|open
op_assign
id|snd_au1000_capture_open
comma
dot
id|close
op_assign
id|snd_au1000_capture_close
comma
dot
id|ioctl
op_assign
id|snd_pcm_lib_ioctl
comma
dot
id|hw_params
op_assign
id|snd_au1000_hw_params
comma
dot
id|hw_free
op_assign
id|snd_au1000_hw_free
comma
dot
id|prepare
op_assign
id|snd_au1000_capture_prepare
comma
dot
id|trigger
op_assign
id|snd_au1000_trigger
comma
dot
id|pointer
op_assign
id|snd_au1000_pointer
comma
)brace
suffix:semicolon
r_static
r_int
id|__devinit
DECL|function|snd_au1000_pcm_new
id|snd_au1000_pcm_new
c_func
(paren
r_void
)paren
(brace
id|snd_pcm_t
op_star
id|pcm
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_pcm_new
c_func
(paren
id|au1000-&gt;card
comma
l_string|&quot;AU1000 AC97 PCM&quot;
comma
l_int|0
comma
l_int|1
comma
l_int|1
comma
op_amp
id|pcm
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|snd_pcm_lib_preallocate_pages_for_all
c_func
(paren
id|pcm
comma
id|SNDRV_DMA_TYPE_CONTINUOUS
comma
id|snd_dma_continuous_data
c_func
(paren
id|GFP_KERNEL
)paren
comma
l_int|128
op_star
l_int|1024
comma
l_int|128
op_star
l_int|1024
)paren
suffix:semicolon
id|snd_pcm_set_ops
c_func
(paren
id|pcm
comma
id|SNDRV_PCM_STREAM_PLAYBACK
comma
op_amp
id|snd_card_au1000_playback_ops
)paren
suffix:semicolon
id|snd_pcm_set_ops
c_func
(paren
id|pcm
comma
id|SNDRV_PCM_STREAM_CAPTURE
comma
op_amp
id|snd_card_au1000_capture_ops
)paren
suffix:semicolon
id|pcm-&gt;private_data
op_assign
id|au1000
suffix:semicolon
id|pcm-&gt;info_flags
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|pcm-&gt;name
comma
l_string|&quot;Au1000 AC97 PCM&quot;
)paren
suffix:semicolon
id|flags
op_assign
id|claim_dma_lock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
op_member_access_from_pointer
id|dma
op_assign
id|request_au1000_dma
c_func
(paren
id|DMA_ID_AC97C_TX
comma
l_string|&quot;AC97 TX&quot;
comma
id|au1000_dma_interrupt
comma
id|SA_INTERRUPT
comma
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
)paren
)paren
OL
l_int|0
)paren
(brace
id|release_dma_lock
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
op_member_access_from_pointer
id|dma
op_assign
id|request_au1000_dma
c_func
(paren
id|DMA_ID_AC97C_RX
comma
l_string|&quot;AC97 RX&quot;
comma
id|au1000_dma_interrupt
comma
id|SA_INTERRUPT
comma
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
)paren
)paren
OL
l_int|0
)paren
(brace
id|release_dma_lock
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* enable DMA coherency in read/write DMA channels */
id|set_dma_mode
c_func
(paren
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
op_member_access_from_pointer
id|dma
comma
id|get_dma_mode
c_func
(paren
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
op_member_access_from_pointer
id|dma
)paren
op_amp
op_complement
id|DMA_NC
)paren
suffix:semicolon
id|set_dma_mode
c_func
(paren
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
op_member_access_from_pointer
id|dma
comma
id|get_dma_mode
c_func
(paren
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
op_member_access_from_pointer
id|dma
)paren
op_amp
op_complement
id|DMA_NC
)paren
suffix:semicolon
id|release_dma_lock
c_func
(paren
id|flags
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
op_member_access_from_pointer
id|dma_lock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
op_member_access_from_pointer
id|dma_lock
)paren
suffix:semicolon
id|au1000-&gt;pcm
op_assign
id|pcm
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*-------------------------- AC97 CODEC Control ------------------------------*/
r_static
r_int
r_int
DECL|function|snd_au1000_ac97_read
id|snd_au1000_ac97_read
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
r_int
id|reg
)paren
(brace
id|u32
r_volatile
id|cmd
suffix:semicolon
id|u16
r_volatile
id|data
suffix:semicolon
r_int
id|i
suffix:semicolon
id|spin_lock
c_func
(paren
id|au1000-&gt;ac97_lock
)paren
suffix:semicolon
multiline_comment|/* would rather use the interupt than this polling but it works and I can&squot;t&n;get the interupt driven case to work efficiently */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|0x5000
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|au1000-&gt;ac97_ioport-&gt;status
op_amp
id|AC97C_CP
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0x5000
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;au1000 AC97: AC97 command read timeout&bslash;n&quot;
)paren
suffix:semicolon
id|cmd
op_assign
(paren
id|u32
)paren
id|reg
op_amp
id|AC97C_INDEX_MASK
suffix:semicolon
id|cmd
op_or_assign
id|AC97C_READ
suffix:semicolon
id|au1000-&gt;ac97_ioport-&gt;cmd
op_assign
id|cmd
suffix:semicolon
multiline_comment|/* now wait for the data */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|0x5000
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|au1000-&gt;ac97_ioport-&gt;status
op_amp
id|AC97C_CP
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0x5000
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;au1000 AC97: AC97 command read timeout&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|data
op_assign
id|au1000-&gt;ac97_ioport-&gt;cmd
op_amp
l_int|0xffff
suffix:semicolon
id|spin_unlock
c_func
(paren
id|au1000-&gt;ac97_lock
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
r_static
r_void
DECL|function|snd_au1000_ac97_write
id|snd_au1000_ac97_write
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|val
)paren
(brace
id|u32
id|cmd
suffix:semicolon
r_int
id|i
suffix:semicolon
id|spin_lock
c_func
(paren
id|au1000-&gt;ac97_lock
)paren
suffix:semicolon
multiline_comment|/* would rather use the interupt than this polling but it works and I can&squot;t&n;get the interupt driven case to work efficiently */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|0x5000
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|au1000-&gt;ac97_ioport-&gt;status
op_amp
id|AC97C_CP
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0x5000
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;au1000 AC97: AC97 command write timeout&bslash;n&quot;
)paren
suffix:semicolon
id|cmd
op_assign
(paren
id|u32
)paren
id|reg
op_amp
id|AC97C_INDEX_MASK
suffix:semicolon
id|cmd
op_and_assign
op_complement
id|AC97C_READ
suffix:semicolon
id|cmd
op_or_assign
(paren
(paren
id|u32
)paren
id|val
op_lshift
id|AC97C_WD_BIT
)paren
suffix:semicolon
id|au1000-&gt;ac97_ioport-&gt;cmd
op_assign
id|cmd
suffix:semicolon
id|spin_unlock
c_func
(paren
id|au1000-&gt;ac97_lock
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|snd_au1000_ac97_free
id|snd_au1000_ac97_free
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
id|au1000-&gt;ac97
op_assign
l_int|NULL
suffix:semicolon
)brace
r_static
r_int
id|__devinit
DECL|function|snd_au1000_ac97_new
id|snd_au1000_ac97_new
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,6,8)
id|ac97_bus_t
op_star
id|pbus
suffix:semicolon
id|ac97_template_t
id|ac97
suffix:semicolon
r_static
id|ac97_bus_ops_t
id|ops
op_assign
(brace
dot
id|write
op_assign
id|snd_au1000_ac97_write
comma
dot
id|read
op_assign
id|snd_au1000_ac97_read
comma
)brace
suffix:semicolon
macro_line|#else
id|ac97_bus_t
id|bus
comma
op_star
id|pbus
suffix:semicolon
id|ac97_t
id|ac97
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|au1000-&gt;ac97_res_port
op_assign
id|request_region
c_func
(paren
id|AC97C_CONFIG
comma
r_sizeof
(paren
id|au1000_ac97_reg_t
)paren
comma
l_string|&quot;Au1x00 AC97&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ALSA AC97: can&squot;t grap AC97 port&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|au1000-&gt;ac97_ioport
op_assign
(paren
id|au1000_ac97_reg_t
op_star
)paren
id|au1000-&gt;ac97_res_port-&gt;start
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|au1000-&gt;ac97_lock
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|au1000-&gt;ac97_lock
)paren
suffix:semicolon
multiline_comment|/* configure pins for AC&squot;97&n;&t;TODO: move to board_setup.c */
id|au_writel
c_func
(paren
id|au_readl
c_func
(paren
id|SYS_PINFUNC
)paren
op_amp
op_complement
l_int|0x02
comma
id|SYS_PINFUNC
)paren
suffix:semicolon
multiline_comment|/* Initialise Au1000&squot;s AC&squot;97 Control Block */
id|au1000-&gt;ac97_ioport-&gt;cntrl
op_assign
id|AC97C_RS
op_or
id|AC97C_CE
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|au1000-&gt;ac97_ioport-&gt;cntrl
op_assign
id|AC97C_CE
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
multiline_comment|/* Initialise External CODEC -- cold reset */
id|au1000-&gt;ac97_ioport-&gt;config
op_assign
id|AC97C_RESET
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|au1000-&gt;ac97_ioport-&gt;config
op_assign
l_int|0x0
suffix:semicolon
id|mdelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|au1000-&gt;ac97_lock
)paren
suffix:semicolon
multiline_comment|/* Initialise AC97 middle-layer */
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,6,8)
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ac97_bus
c_func
(paren
id|au1000-&gt;card
comma
l_int|0
comma
op_amp
id|ops
comma
id|au1000
comma
op_amp
id|pbus
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
macro_line|#else
id|memset
c_func
(paren
op_amp
id|bus
comma
l_int|0
comma
r_sizeof
(paren
id|bus
)paren
)paren
suffix:semicolon
id|bus.write
op_assign
id|snd_au1000_ac97_write
suffix:semicolon
id|bus.read
op_assign
id|snd_au1000_ac97_read
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ac97_bus
c_func
(paren
id|au1000-&gt;card
comma
op_amp
id|bus
comma
op_amp
id|pbus
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
macro_line|#endif
id|memset
c_func
(paren
op_amp
id|ac97
comma
l_int|0
comma
r_sizeof
(paren
id|ac97
)paren
)paren
suffix:semicolon
id|ac97.private_data
op_assign
id|au1000
suffix:semicolon
id|ac97.private_free
op_assign
id|snd_au1000_ac97_free
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ac97_mixer
c_func
(paren
id|pbus
comma
op_amp
id|ac97
comma
op_amp
id|au1000-&gt;ac97
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*------------------------------ Setup / Destroy ----------------------------*/
r_void
DECL|function|snd_au1000_free
id|snd_au1000_free
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_if
c_cond
(paren
id|au1000-&gt;ac97_res_port
)paren
(brace
multiline_comment|/* put internal AC97 block into reset */
id|au1000-&gt;ac97_ioport-&gt;cntrl
op_assign
id|AC97C_RS
suffix:semicolon
id|au1000-&gt;ac97_ioport
op_assign
l_int|NULL
suffix:semicolon
id|release_resource
c_func
(paren
id|au1000-&gt;ac97_res_port
)paren
suffix:semicolon
id|kfree_nocheck
c_func
(paren
id|au1000-&gt;ac97_res_port
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
op_member_access_from_pointer
id|dma
op_ge
l_int|0
)paren
id|free_au1000_dma
c_func
(paren
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
op_member_access_from_pointer
id|dma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
op_member_access_from_pointer
id|dma
op_ge
l_int|0
)paren
id|free_au1000_dma
c_func
(paren
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
op_member_access_from_pointer
id|dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
)paren
suffix:semicolon
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
)paren
suffix:semicolon
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|au1000
)paren
suffix:semicolon
id|au1000
op_assign
l_int|NULL
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|au1000_init
id|au1000_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|au1000
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|au1000_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|au1000
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|audio_stream_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|audio_stream_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* so that snd_au1000_free will work as intended */
id|au1000-&gt;stream
(braket
id|PLAYBACK
)braket
op_member_access_from_pointer
id|dma
op_assign
op_minus
l_int|1
suffix:semicolon
id|au1000-&gt;stream
(braket
id|CAPTURE
)braket
op_member_access_from_pointer
id|dma
op_assign
op_minus
l_int|1
suffix:semicolon
id|au1000-&gt;ac97_res_port
op_assign
l_int|NULL
suffix:semicolon
id|au1000-&gt;card
op_assign
id|snd_card_new
c_func
(paren
op_minus
l_int|1
comma
l_string|&quot;AC97&quot;
comma
id|THIS_MODULE
comma
r_sizeof
(paren
id|au1000_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|au1000-&gt;card
op_eq
l_int|NULL
)paren
(brace
id|snd_au1000_free
c_func
(paren
id|au1000-&gt;card
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|au1000-&gt;card-&gt;private_data
op_assign
(paren
id|au1000_t
op_star
)paren
id|au1000
suffix:semicolon
id|au1000-&gt;card-&gt;private_free
op_assign
id|snd_au1000_free
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_au1000_ac97_new
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|au1000-&gt;card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_au1000_pcm_new
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|au1000-&gt;card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|au1000-&gt;card-&gt;driver
comma
l_string|&quot;AMD-Au1000-AC97&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|au1000-&gt;card-&gt;shortname
comma
l_string|&quot;Au1000-AC97&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|au1000-&gt;card-&gt;longname
comma
l_string|&quot;AMD Au1000--AC97 ALSA Driver&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_card_register
c_func
(paren
id|au1000-&gt;card
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|au1000-&gt;card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ALSA AC97: Driver Initialized&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|au1000_exit
r_static
r_void
id|__exit
id|au1000_exit
c_func
(paren
r_void
)paren
(brace
id|snd_card_free
c_func
(paren
id|au1000-&gt;card
)paren
suffix:semicolon
)brace
DECL|variable|au1000_init
id|module_init
c_func
(paren
id|au1000_init
)paren
suffix:semicolon
DECL|variable|au1000_exit
id|module_exit
c_func
(paren
id|au1000_exit
)paren
suffix:semicolon
eof
