multiline_comment|/*&n; * pas2_pcm.c Audio routines for PAS16&n; *&n; *&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; *&n; *&n; * Thomas Sailer   : ioctl code reworked (vmalloc/vfree removed)&n; * Alan Cox&t;   : Swatted a double allocation of device bug. Made a few&n; *&t;&t;     more things module options.&n; * Bartlomiej Zolnierkiewicz : Added __init to pas_pcm_init()&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &quot;pas2.h&quot;
macro_line|#ifndef DEB
DECL|macro|DEB
mdefine_line|#define DEB(WHAT)
macro_line|#endif
DECL|macro|PAS_PCM_INTRBITS
mdefine_line|#define PAS_PCM_INTRBITS (0x08)
multiline_comment|/*&n; * Sample buffer timer interrupt enable&n; */
DECL|macro|PCM_NON
mdefine_line|#define PCM_NON&t;0
DECL|macro|PCM_DAC
mdefine_line|#define PCM_DAC&t;1
DECL|macro|PCM_ADC
mdefine_line|#define PCM_ADC&t;2
DECL|variable|pcm_speed
r_static
r_int
r_int
id|pcm_speed
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* sampling rate */
DECL|variable|pcm_channels
r_static
r_int
r_char
id|pcm_channels
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* channels (1 or 2) */
DECL|variable|pcm_bits
r_static
r_int
r_char
id|pcm_bits
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* bits/sample (8 or 16) */
DECL|variable|pcm_filter
r_static
r_int
r_char
id|pcm_filter
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* filter FLAG */
DECL|variable|pcm_mode
r_static
r_int
r_char
id|pcm_mode
op_assign
id|PCM_NON
suffix:semicolon
DECL|variable|pcm_count
r_static
r_int
r_int
id|pcm_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|pcm_bitsok
r_static
r_int
r_int
id|pcm_bitsok
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* mask of OK bits */
DECL|variable|pcm_busy
r_static
r_int
id|pcm_busy
op_assign
l_int|0
suffix:semicolon
DECL|variable|pas_audiodev
r_int
id|pas_audiodev
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|open_mode
r_static
r_int
id|open_mode
op_assign
l_int|0
suffix:semicolon
r_extern
id|spinlock_t
id|pas_lock
suffix:semicolon
DECL|function|pcm_set_speed
r_static
r_int
id|pcm_set_speed
c_func
(paren
r_int
id|arg
)paren
(brace
r_int
id|foo
comma
id|tmp
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_eq
l_int|0
)paren
r_return
id|pcm_speed
suffix:semicolon
r_if
c_cond
(paren
id|arg
OG
l_int|44100
)paren
id|arg
op_assign
l_int|44100
suffix:semicolon
r_if
c_cond
(paren
id|arg
OL
l_int|5000
)paren
id|arg
op_assign
l_int|5000
suffix:semicolon
r_if
c_cond
(paren
id|pcm_channels
op_amp
l_int|2
)paren
(brace
id|foo
op_assign
(paren
l_int|596590
op_plus
(paren
id|arg
op_div
l_int|2
)paren
)paren
op_div
id|arg
suffix:semicolon
id|arg
op_assign
(paren
l_int|596590
op_plus
(paren
id|foo
op_div
l_int|2
)paren
)paren
op_div
id|foo
suffix:semicolon
)brace
r_else
(brace
id|foo
op_assign
(paren
l_int|1193180
op_plus
(paren
id|arg
op_div
l_int|2
)paren
)paren
op_div
id|arg
suffix:semicolon
id|arg
op_assign
(paren
l_int|1193180
op_plus
(paren
id|foo
op_div
l_int|2
)paren
)paren
op_div
id|foo
suffix:semicolon
)brace
id|pcm_speed
op_assign
id|arg
suffix:semicolon
id|tmp
op_assign
id|pas_read
c_func
(paren
l_int|0x0B8A
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set anti-aliasing filters according to sample rate. You really *NEED*&n;&t; * to enable this feature for all normal recording unless you want to&n;&t; * experiment with aliasing effects.&n;&t; * These filters apply to the selected &quot;recording&quot; source.&n;&t; * I (pfw) don&squot;t know the encoding of these 5 bits. The values shown&n;&t; * come from the SDK found on ftp.uwp.edu:/pub/msdos/proaudio/.&n;&t; *&n;&t; * I cleared bit 5 of these values, since that bit controls the master&n;&t; * mute flag. (Olav W&#xfffd;lfelschneider)&n;&t; *&n;&t; */
macro_line|#if !defined NO_AUTO_FILTER_SET
id|tmp
op_and_assign
l_int|0xe0
suffix:semicolon
r_if
c_cond
(paren
id|pcm_speed
op_ge
l_int|2
op_star
l_int|17897
)paren
id|tmp
op_or_assign
l_int|0x01
suffix:semicolon
r_else
r_if
c_cond
(paren
id|pcm_speed
op_ge
l_int|2
op_star
l_int|15909
)paren
id|tmp
op_or_assign
l_int|0x02
suffix:semicolon
r_else
r_if
c_cond
(paren
id|pcm_speed
op_ge
l_int|2
op_star
l_int|11931
)paren
id|tmp
op_or_assign
l_int|0x09
suffix:semicolon
r_else
r_if
c_cond
(paren
id|pcm_speed
op_ge
l_int|2
op_star
l_int|8948
)paren
id|tmp
op_or_assign
l_int|0x11
suffix:semicolon
r_else
r_if
c_cond
(paren
id|pcm_speed
op_ge
l_int|2
op_star
l_int|5965
)paren
id|tmp
op_or_assign
l_int|0x19
suffix:semicolon
r_else
r_if
c_cond
(paren
id|pcm_speed
op_ge
l_int|2
op_star
l_int|2982
)paren
id|tmp
op_or_assign
l_int|0x04
suffix:semicolon
id|pcm_filter
op_assign
id|tmp
suffix:semicolon
macro_line|#endif
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pas_lock
comma
id|flags
)paren
suffix:semicolon
id|pas_write
c_func
(paren
id|tmp
op_amp
op_complement
(paren
l_int|0x40
op_or
l_int|0x80
)paren
comma
l_int|0x0B8A
)paren
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0x00
op_or
l_int|0x30
op_or
l_int|0x04
comma
l_int|0x138B
)paren
suffix:semicolon
id|pas_write
c_func
(paren
id|foo
op_amp
l_int|0xff
comma
l_int|0x1388
)paren
suffix:semicolon
id|pas_write
c_func
(paren
(paren
id|foo
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
l_int|0x1388
)paren
suffix:semicolon
id|pas_write
c_func
(paren
id|tmp
comma
l_int|0x0B8A
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pas_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|pcm_speed
suffix:semicolon
)brace
DECL|function|pcm_set_channels
r_static
r_int
id|pcm_set_channels
c_func
(paren
r_int
id|arg
)paren
(brace
r_if
c_cond
(paren
(paren
id|arg
op_ne
l_int|1
)paren
op_logical_and
(paren
id|arg
op_ne
l_int|2
)paren
)paren
r_return
id|pcm_channels
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_ne
id|pcm_channels
)paren
(brace
id|pas_write
c_func
(paren
id|pas_read
c_func
(paren
l_int|0xF8A
)paren
op_xor
l_int|0x20
comma
l_int|0xF8A
)paren
suffix:semicolon
id|pcm_channels
op_assign
id|arg
suffix:semicolon
id|pcm_set_speed
c_func
(paren
id|pcm_speed
)paren
suffix:semicolon
multiline_comment|/* The speed must be reinitialized */
)brace
r_return
id|pcm_channels
suffix:semicolon
)brace
DECL|function|pcm_set_bits
r_static
r_int
id|pcm_set_bits
c_func
(paren
r_int
id|arg
)paren
(brace
r_if
c_cond
(paren
id|arg
op_eq
l_int|0
)paren
r_return
id|pcm_bits
suffix:semicolon
r_if
c_cond
(paren
(paren
id|arg
op_amp
id|pcm_bitsok
)paren
op_ne
id|arg
)paren
r_return
id|pcm_bits
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_ne
id|pcm_bits
)paren
(brace
id|pas_write
c_func
(paren
id|pas_read
c_func
(paren
l_int|0x8389
)paren
op_xor
l_int|0x04
comma
l_int|0x8389
)paren
suffix:semicolon
id|pcm_bits
op_assign
id|arg
suffix:semicolon
)brace
r_return
id|pcm_bits
suffix:semicolon
)brace
DECL|function|pas_audio_ioctl
r_static
r_int
id|pas_audio_ioctl
c_func
(paren
r_int
id|dev
comma
r_int
r_int
id|cmd
comma
id|caddr_t
id|arg
)paren
(brace
r_int
id|val
comma
id|ret
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;pas2_pcm.c: static int pas_audio_ioctl(unsigned int cmd = %X, unsigned int arg = %X)&bslash;n&quot;
comma
id|cmd
comma
id|arg
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SOUND_PCM_WRITE_RATE
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ret
op_assign
id|pcm_set_speed
c_func
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_PCM_READ_RATE
suffix:colon
id|ret
op_assign
id|pcm_speed
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDCTL_DSP_STEREO
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ret
op_assign
id|pcm_set_channels
c_func
(paren
id|val
op_plus
l_int|1
)paren
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_PCM_WRITE_CHANNELS
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ret
op_assign
id|pcm_set_channels
c_func
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_PCM_READ_CHANNELS
suffix:colon
id|ret
op_assign
id|pcm_channels
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDCTL_DSP_SETFMT
suffix:colon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ret
op_assign
id|pcm_set_bits
c_func
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_PCM_READ_BITS
suffix:colon
id|ret
op_assign
id|pcm_bits
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|put_user
c_func
(paren
id|ret
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
DECL|function|pas_audio_reset
r_static
r_void
id|pas_audio_reset
c_func
(paren
r_int
id|dev
)paren
(brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;pas2_pcm.c: static void pas_audio_reset(void)&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|pas_write
c_func
(paren
id|pas_read
c_func
(paren
l_int|0xF8A
)paren
op_amp
op_complement
l_int|0x40
comma
l_int|0xF8A
)paren
suffix:semicolon
multiline_comment|/* Disable PCM */
)brace
DECL|function|pas_audio_open
r_static
r_int
id|pas_audio_open
c_func
(paren
r_int
id|dev
comma
r_int
id|mode
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;pas2_pcm.c: static int pas_audio_open(int mode = %X)&bslash;n&quot;
comma
id|mode
)paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pas_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pcm_busy
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pas_lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|pcm_busy
op_assign
l_int|1
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pas_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|pas_set_intr
c_func
(paren
id|PAS_PCM_INTRBITS
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|pcm_count
op_assign
l_int|0
suffix:semicolon
id|open_mode
op_assign
id|mode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pas_audio_close
r_static
r_void
id|pas_audio_close
c_func
(paren
r_int
id|dev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;pas2_pcm.c: static void pas_audio_close(void)&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pas_lock
comma
id|flags
)paren
suffix:semicolon
id|pas_audio_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
id|pas_remove_intr
c_func
(paren
id|PAS_PCM_INTRBITS
)paren
suffix:semicolon
id|pcm_mode
op_assign
id|PCM_NON
suffix:semicolon
id|pcm_busy
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pas_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pas_audio_output_block
r_static
r_void
id|pas_audio_output_block
c_func
(paren
r_int
id|dev
comma
r_int
r_int
id|buf
comma
r_int
id|count
comma
r_int
id|intrflag
)paren
(brace
r_int
r_int
id|flags
comma
id|cnt
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;pas2_pcm.c: static void pas_audio_output_block(char *buf = %P, int count = %X)&bslash;n&quot;
comma
id|buf
comma
id|count
)paren
)paren
suffix:semicolon
id|cnt
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|dmap_out-&gt;dma
OG
l_int|3
)paren
id|cnt
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|flags
op_amp
id|DMA_AUTOMODE
op_logical_and
id|intrflag
op_logical_and
id|cnt
op_eq
id|pcm_count
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pas_lock
comma
id|flags
)paren
suffix:semicolon
id|pas_write
c_func
(paren
id|pas_read
c_func
(paren
l_int|0xF8A
)paren
op_amp
op_complement
l_int|0x40
comma
l_int|0xF8A
)paren
suffix:semicolon
multiline_comment|/* DMAbuf_start_dma (dev, buf, count, DMA_MODE_WRITE); */
r_if
c_cond
(paren
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|dmap_out-&gt;dma
OG
l_int|3
)paren
id|count
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ne
id|pcm_count
)paren
(brace
id|pas_write
c_func
(paren
id|pas_read
c_func
(paren
l_int|0x0B8A
)paren
op_amp
op_complement
l_int|0x80
comma
l_int|0x0B8A
)paren
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0x40
op_or
l_int|0x30
op_or
l_int|0x04
comma
l_int|0x138B
)paren
suffix:semicolon
id|pas_write
c_func
(paren
id|count
op_amp
l_int|0xff
comma
l_int|0x1389
)paren
suffix:semicolon
id|pas_write
c_func
(paren
(paren
id|count
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
l_int|0x1389
)paren
suffix:semicolon
id|pas_write
c_func
(paren
id|pas_read
c_func
(paren
l_int|0x0B8A
)paren
op_or
l_int|0x80
comma
l_int|0x0B8A
)paren
suffix:semicolon
id|pcm_count
op_assign
id|count
suffix:semicolon
)brace
id|pas_write
c_func
(paren
id|pas_read
c_func
(paren
l_int|0x0B8A
)paren
op_or
l_int|0x80
op_or
l_int|0x40
comma
l_int|0x0B8A
)paren
suffix:semicolon
macro_line|#ifdef NO_TRIGGER
id|pas_write
c_func
(paren
id|pas_read
c_func
(paren
l_int|0xF8A
)paren
op_or
l_int|0x40
op_or
l_int|0x10
comma
l_int|0xF8A
)paren
suffix:semicolon
macro_line|#endif
id|pcm_mode
op_assign
id|PCM_DAC
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pas_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|pas_audio_start_input
r_static
r_void
id|pas_audio_start_input
c_func
(paren
r_int
id|dev
comma
r_int
r_int
id|buf
comma
r_int
id|count
comma
r_int
id|intrflag
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|cnt
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;pas2_pcm.c: static void pas_audio_start_input(char *buf = %P, int count = %X)&bslash;n&quot;
comma
id|buf
comma
id|count
)paren
)paren
suffix:semicolon
id|cnt
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|dmap_out-&gt;dma
OG
l_int|3
)paren
id|cnt
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|audio_devs
(braket
id|pas_audiodev
)braket
op_member_access_from_pointer
id|flags
op_amp
id|DMA_AUTOMODE
op_logical_and
id|intrflag
op_logical_and
id|cnt
op_eq
id|pcm_count
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pas_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* DMAbuf_start_dma (dev, buf, count, DMA_MODE_READ); */
r_if
c_cond
(paren
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|dmap_out-&gt;dma
OG
l_int|3
)paren
id|count
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ne
id|pcm_count
)paren
(brace
id|pas_write
c_func
(paren
id|pas_read
c_func
(paren
l_int|0x0B8A
)paren
op_amp
op_complement
l_int|0x80
comma
l_int|0x0B8A
)paren
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0x40
op_or
l_int|0x30
op_or
l_int|0x04
comma
l_int|0x138B
)paren
suffix:semicolon
id|pas_write
c_func
(paren
id|count
op_amp
l_int|0xff
comma
l_int|0x1389
)paren
suffix:semicolon
id|pas_write
c_func
(paren
(paren
id|count
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
l_int|0x1389
)paren
suffix:semicolon
id|pas_write
c_func
(paren
id|pas_read
c_func
(paren
l_int|0x0B8A
)paren
op_or
l_int|0x80
comma
l_int|0x0B8A
)paren
suffix:semicolon
id|pcm_count
op_assign
id|count
suffix:semicolon
)brace
id|pas_write
c_func
(paren
id|pas_read
c_func
(paren
l_int|0x0B8A
)paren
op_or
l_int|0x80
op_or
l_int|0x40
comma
l_int|0x0B8A
)paren
suffix:semicolon
macro_line|#ifdef NO_TRIGGER
id|pas_write
c_func
(paren
(paren
id|pas_read
c_func
(paren
l_int|0xF8A
)paren
op_or
l_int|0x40
)paren
op_amp
op_complement
l_int|0x10
comma
l_int|0xF8A
)paren
suffix:semicolon
macro_line|#endif
id|pcm_mode
op_assign
id|PCM_ADC
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pas_lock
comma
id|flags
)paren
suffix:semicolon
)brace
macro_line|#ifndef NO_TRIGGER
DECL|function|pas_audio_trigger
r_static
r_void
id|pas_audio_trigger
c_func
(paren
r_int
id|dev
comma
r_int
id|state
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pas_lock
comma
id|flags
)paren
suffix:semicolon
id|state
op_and_assign
id|open_mode
suffix:semicolon
r_if
c_cond
(paren
id|state
op_amp
id|PCM_ENABLE_OUTPUT
)paren
id|pas_write
c_func
(paren
id|pas_read
c_func
(paren
l_int|0xF8A
)paren
op_or
l_int|0x40
op_or
l_int|0x10
comma
l_int|0xF8A
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|state
op_amp
id|PCM_ENABLE_INPUT
)paren
id|pas_write
c_func
(paren
(paren
id|pas_read
c_func
(paren
l_int|0xF8A
)paren
op_or
l_int|0x40
)paren
op_amp
op_complement
l_int|0x10
comma
l_int|0xF8A
)paren
suffix:semicolon
r_else
id|pas_write
c_func
(paren
id|pas_read
c_func
(paren
l_int|0xF8A
)paren
op_amp
op_complement
l_int|0x40
comma
l_int|0xF8A
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pas_lock
comma
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|pas_audio_prepare_for_input
r_static
r_int
id|pas_audio_prepare_for_input
c_func
(paren
r_int
id|dev
comma
r_int
id|bsize
comma
r_int
id|bcount
)paren
(brace
id|pas_audio_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pas_audio_prepare_for_output
r_static
r_int
id|pas_audio_prepare_for_output
c_func
(paren
r_int
id|dev
comma
r_int
id|bsize
comma
r_int
id|bcount
)paren
(brace
id|pas_audio_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pas_audio_driver
r_static
r_struct
id|audio_driver
id|pas_audio_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|pas_audio_open
comma
dot
id|close
op_assign
id|pas_audio_close
comma
dot
id|output_block
op_assign
id|pas_audio_output_block
comma
dot
id|start_input
op_assign
id|pas_audio_start_input
comma
dot
id|ioctl
op_assign
id|pas_audio_ioctl
comma
dot
id|prepare_for_input
op_assign
id|pas_audio_prepare_for_input
comma
dot
id|prepare_for_output
op_assign
id|pas_audio_prepare_for_output
comma
dot
id|halt_io
op_assign
id|pas_audio_reset
comma
dot
id|trigger
op_assign
id|pas_audio_trigger
)brace
suffix:semicolon
DECL|function|pas_pcm_init
r_void
id|__init
id|pas_pcm_init
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;pas2_pcm.c: long pas_pcm_init()&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|pcm_bitsok
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|pas_read
c_func
(paren
l_int|0xEF8B
)paren
op_amp
l_int|0x08
)paren
id|pcm_bitsok
op_or_assign
l_int|16
suffix:semicolon
id|pcm_set_speed
c_func
(paren
id|DSP_DEFAULT_SPEED
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pas_audiodev
op_assign
id|sound_install_audiodrv
c_func
(paren
id|AUDIO_DRIVER_VERSION
comma
l_string|&quot;Pro Audio Spectrum&quot;
comma
op_amp
id|pas_audio_driver
comma
r_sizeof
(paren
r_struct
id|audio_driver
)paren
comma
id|DMA_AUTOMODE
comma
id|AFMT_U8
op_or
id|AFMT_S16_LE
comma
l_int|NULL
comma
id|hw_config-&gt;dma
comma
id|hw_config-&gt;dma
)paren
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PAS16: Too many PCM devices available&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|pas_pcm_interrupt
r_void
id|pas_pcm_interrupt
c_func
(paren
r_int
r_char
id|status
comma
r_int
id|cause
)paren
(brace
r_if
c_cond
(paren
id|cause
op_eq
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t; * Halt the PCM first. Otherwise we don&squot;t have time to start a new&n;&t;&t; * block before the PCM chip proceeds to the next sample&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|audio_devs
(braket
id|pas_audiodev
)braket
op_member_access_from_pointer
id|flags
op_amp
id|DMA_AUTOMODE
)paren
)paren
id|pas_write
c_func
(paren
id|pas_read
c_func
(paren
l_int|0xF8A
)paren
op_amp
op_complement
l_int|0x40
comma
l_int|0xF8A
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|pcm_mode
)paren
(brace
r_case
id|PCM_DAC
suffix:colon
id|DMAbuf_outputintr
c_func
(paren
id|pas_audiodev
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCM_ADC
suffix:colon
id|DMAbuf_inputintr
c_func
(paren
id|pas_audiodev
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PAS: Unexpected PCM interrupt&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
eof
