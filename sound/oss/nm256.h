macro_line|#ifndef _NM256_H_
DECL|macro|_NM256_H_
mdefine_line|#define _NM256_H_
macro_line|#include &quot;ac97.h&quot;
multiline_comment|/* The revisions that we currently handle.  */
DECL|enum|nm256rev
r_enum
id|nm256rev
(brace
DECL|enumerator|REV_NM256AV
DECL|enumerator|REV_NM256ZX
id|REV_NM256AV
comma
id|REV_NM256ZX
)brace
suffix:semicolon
multiline_comment|/* Per-card structure. */
DECL|struct|nm256_info
r_struct
id|nm256_info
(brace
multiline_comment|/* Magic number used to verify that this struct is valid. */
DECL|macro|NM_MAGIC_SIG
mdefine_line|#define NM_MAGIC_SIG 0x55aa00ff
DECL|member|magsig
r_int
id|magsig
suffix:semicolon
multiline_comment|/* Revision number */
DECL|member|rev
r_enum
id|nm256rev
id|rev
suffix:semicolon
DECL|member|mdev
r_struct
id|ac97_hwint
id|mdev
suffix:semicolon
multiline_comment|/* Our audio device numbers. */
DECL|member|dev
r_int
id|dev
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* The # of times each device has been opened. (Should only be &n;       0 or 1). */
DECL|member|opencnt
r_int
id|opencnt
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* We use two devices, because we can do simultaneous play and record.&n;       This keeps track of which device is being used for what purpose;&n;       these are the actual device numbers. */
DECL|member|dev_for_play
r_int
id|dev_for_play
suffix:semicolon
DECL|member|dev_for_record
r_int
id|dev_for_record
suffix:semicolon
multiline_comment|/* The mixer device. */
DECL|member|mixer_oss_dev
r_int
id|mixer_oss_dev
suffix:semicolon
multiline_comment|/* &n;     * Can only be opened once for each operation.  These aren&squot;t set&n;     * until an actual I/O operation is performed; this allows one&n;     * device to be open for read/write without inhibiting I/O to&n;     * the other device.&n;     */
DECL|member|is_open_play
r_int
id|is_open_play
suffix:semicolon
DECL|member|is_open_record
r_int
id|is_open_record
suffix:semicolon
multiline_comment|/* Non-zero if we&squot;re currently playing a sample. */
DECL|member|playing
r_int
id|playing
suffix:semicolon
multiline_comment|/* Ditto for recording a sample. */
DECL|member|recording
r_int
id|recording
suffix:semicolon
multiline_comment|/* The two memory ports.  */
DECL|struct|nm256_ports
r_struct
id|nm256_ports
(brace
multiline_comment|/* Physical address of the port. */
DECL|member|physaddr
id|u32
id|physaddr
suffix:semicolon
multiline_comment|/* Our mapped-in pointer. */
DECL|member|ptr
r_char
op_star
id|ptr
suffix:semicolon
multiline_comment|/* PTR&squot;s offset within the physical port.  */
DECL|member|start_offset
id|u32
id|start_offset
suffix:semicolon
multiline_comment|/* And the offset of the end of the buffer.  */
DECL|member|end_offset
id|u32
id|end_offset
suffix:semicolon
DECL|member|port
)brace
id|port
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* The following are offsets within memory port 1. */
DECL|member|coeffBuf
id|u32
id|coeffBuf
suffix:semicolon
DECL|member|allCoeffBuf
id|u32
id|allCoeffBuf
suffix:semicolon
multiline_comment|/* Record and playback buffers. */
DECL|member|abuf1
DECL|member|abuf2
id|u32
id|abuf1
comma
id|abuf2
suffix:semicolon
multiline_comment|/* Offset of the AC97 mixer in memory port 2. */
DECL|member|mixer
id|u32
id|mixer
suffix:semicolon
multiline_comment|/* Offset of the mixer status register in memory port 2.  */
DECL|member|mixer_status_offset
id|u32
id|mixer_status_offset
suffix:semicolon
multiline_comment|/* Non-zero if we have written initial values to the mixer. */
DECL|member|mixer_values_init
id|u8
id|mixer_values_init
suffix:semicolon
multiline_comment|/* &n;     * Status mask bit; (*mixer_status_loc &amp; mixer_status_mask) == 0 means&n;     * it&squot;s ready.  &n;     */
DECL|member|mixer_status_mask
id|u16
id|mixer_status_mask
suffix:semicolon
multiline_comment|/* The sizes of the playback and record ring buffers. */
DECL|member|playbackBufferSize
id|u32
id|playbackBufferSize
suffix:semicolon
DECL|member|recordBufferSize
id|u32
id|recordBufferSize
suffix:semicolon
multiline_comment|/* Are the coefficient values in the memory cache current? */
DECL|member|coeffsCurrent
id|u8
id|coeffsCurrent
suffix:semicolon
multiline_comment|/* For writes, the amount we last wrote. */
DECL|member|requested_amt
id|u32
id|requested_amt
suffix:semicolon
multiline_comment|/* The start of the block currently playing. */
DECL|member|curPlayPos
id|u32
id|curPlayPos
suffix:semicolon
multiline_comment|/* The amount of data we were requested to record. */
DECL|member|requestedRecAmt
id|u32
id|requestedRecAmt
suffix:semicolon
multiline_comment|/* The offset of the currently-recording block. */
DECL|member|curRecPos
id|u32
id|curRecPos
suffix:semicolon
multiline_comment|/* The destination buffer. */
DECL|member|recBuf
r_char
op_star
id|recBuf
suffix:semicolon
multiline_comment|/* Our IRQ number. */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* A flag indicating how many times we&squot;ve grabbed the IRQ. */
DECL|member|has_irq
r_int
id|has_irq
suffix:semicolon
multiline_comment|/* The card interrupt service routine. */
DECL|member|introutine
r_void
(paren
op_star
id|introutine
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/* Current audio config, cached. */
DECL|struct|sinfo
r_struct
id|sinfo
(brace
DECL|member|samplerate
id|u32
id|samplerate
suffix:semicolon
DECL|member|bits
id|u8
id|bits
suffix:semicolon
DECL|member|stereo
id|u8
id|stereo
suffix:semicolon
DECL|member|sinfo
)brace
id|sinfo
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* goes with each device */
multiline_comment|/* The cards are stored in a chain;  this is the next card. */
DECL|member|next_card
r_struct
id|nm256_info
op_star
id|next_card
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Debug flag--bigger numbers mean more output. */
r_extern
r_int
id|nm256_debug
suffix:semicolon
multiline_comment|/* The BIOS signature. */
DECL|macro|NM_SIGNATURE
mdefine_line|#define NM_SIGNATURE 0x4e4d0000
multiline_comment|/* Signature mask. */
DECL|macro|NM_SIG_MASK
mdefine_line|#define NM_SIG_MASK 0xffff0000
multiline_comment|/* Size of the second memory area. */
DECL|macro|NM_PORT2_SIZE
mdefine_line|#define NM_PORT2_SIZE 4096
multiline_comment|/* The base offset of the mixer in the second memory area. */
DECL|macro|NM_MIXER_OFFSET
mdefine_line|#define NM_MIXER_OFFSET 0x600
multiline_comment|/* The maximum size of a coefficient entry. */
DECL|macro|NM_MAX_COEFFICIENT
mdefine_line|#define NM_MAX_COEFFICIENT 0x5000
multiline_comment|/* The interrupt register. */
DECL|macro|NM_INT_REG
mdefine_line|#define NM_INT_REG 0xa04
multiline_comment|/* And its bits. */
DECL|macro|NM_PLAYBACK_INT
mdefine_line|#define NM_PLAYBACK_INT 0x40
DECL|macro|NM_RECORD_INT
mdefine_line|#define NM_RECORD_INT 0x100
DECL|macro|NM_MISC_INT_1
mdefine_line|#define NM_MISC_INT_1 0x4000
DECL|macro|NM_MISC_INT_2
mdefine_line|#define NM_MISC_INT_2 0x1
DECL|macro|NM_ACK_INT
mdefine_line|#define NM_ACK_INT(CARD, X) nm256_writePort16((CARD), 2, NM_INT_REG, (X) &lt;&lt; 1)
multiline_comment|/* The AV&squot;s &quot;mixer ready&quot; status bit and location. */
DECL|macro|NM_MIXER_STATUS_OFFSET
mdefine_line|#define NM_MIXER_STATUS_OFFSET 0xa04
DECL|macro|NM_MIXER_READY_MASK
mdefine_line|#define NM_MIXER_READY_MASK 0x0800
DECL|macro|NM_MIXER_PRESENCE
mdefine_line|#define NM_MIXER_PRESENCE 0xa06
DECL|macro|NM_PRESENCE_MASK
mdefine_line|#define NM_PRESENCE_MASK 0x0050
DECL|macro|NM_PRESENCE_VALUE
mdefine_line|#define NM_PRESENCE_VALUE 0x0040
multiline_comment|/*&n; * For the ZX.  It uses the same interrupt register, but it holds 32&n; * bits instead of 16.&n; */
DECL|macro|NM2_PLAYBACK_INT
mdefine_line|#define NM2_PLAYBACK_INT 0x10000
DECL|macro|NM2_RECORD_INT
mdefine_line|#define NM2_RECORD_INT 0x80000
DECL|macro|NM2_MISC_INT_1
mdefine_line|#define NM2_MISC_INT_1 0x8
DECL|macro|NM2_MISC_INT_2
mdefine_line|#define NM2_MISC_INT_2 0x2
DECL|macro|NM2_ACK_INT
mdefine_line|#define NM2_ACK_INT(CARD, X) nm256_writePort32((CARD), 2, NM_INT_REG, (X))
multiline_comment|/* The ZX&squot;s &quot;mixer ready&quot; status bit and location. */
DECL|macro|NM2_MIXER_STATUS_OFFSET
mdefine_line|#define NM2_MIXER_STATUS_OFFSET 0xa06
DECL|macro|NM2_MIXER_READY_MASK
mdefine_line|#define NM2_MIXER_READY_MASK 0x0800
multiline_comment|/* The playback registers start from here. */
DECL|macro|NM_PLAYBACK_REG_OFFSET
mdefine_line|#define NM_PLAYBACK_REG_OFFSET 0x0
multiline_comment|/* The record registers start from here. */
DECL|macro|NM_RECORD_REG_OFFSET
mdefine_line|#define NM_RECORD_REG_OFFSET 0x200
multiline_comment|/* The rate register is located 2 bytes from the start of the register area. */
DECL|macro|NM_RATE_REG_OFFSET
mdefine_line|#define NM_RATE_REG_OFFSET 2
multiline_comment|/* Mono/stereo flag, number of bits on playback, and rate mask. */
DECL|macro|NM_RATE_STEREO
mdefine_line|#define NM_RATE_STEREO 1
DECL|macro|NM_RATE_BITS_16
mdefine_line|#define NM_RATE_BITS_16 2
DECL|macro|NM_RATE_MASK
mdefine_line|#define NM_RATE_MASK 0xf0
multiline_comment|/* Playback enable register. */
DECL|macro|NM_PLAYBACK_ENABLE_REG
mdefine_line|#define NM_PLAYBACK_ENABLE_REG (NM_PLAYBACK_REG_OFFSET + 0x1)
DECL|macro|NM_PLAYBACK_ENABLE_FLAG
mdefine_line|#define NM_PLAYBACK_ENABLE_FLAG 1
DECL|macro|NM_PLAYBACK_ONESHOT
mdefine_line|#define NM_PLAYBACK_ONESHOT 2
DECL|macro|NM_PLAYBACK_FREERUN
mdefine_line|#define NM_PLAYBACK_FREERUN 4
multiline_comment|/* Mutes the audio output. */
DECL|macro|NM_AUDIO_MUTE_REG
mdefine_line|#define NM_AUDIO_MUTE_REG (NM_PLAYBACK_REG_OFFSET + 0x18)
DECL|macro|NM_AUDIO_MUTE_LEFT
mdefine_line|#define NM_AUDIO_MUTE_LEFT 0x8000
DECL|macro|NM_AUDIO_MUTE_RIGHT
mdefine_line|#define NM_AUDIO_MUTE_RIGHT 0x0080
multiline_comment|/* Recording enable register. */
DECL|macro|NM_RECORD_ENABLE_REG
mdefine_line|#define NM_RECORD_ENABLE_REG (NM_RECORD_REG_OFFSET + 0)
DECL|macro|NM_RECORD_ENABLE_FLAG
mdefine_line|#define NM_RECORD_ENABLE_FLAG 1
DECL|macro|NM_RECORD_FREERUN
mdefine_line|#define NM_RECORD_FREERUN 2
DECL|macro|NM_RBUFFER_START
mdefine_line|#define NM_RBUFFER_START (NM_RECORD_REG_OFFSET + 0x4)
DECL|macro|NM_RBUFFER_END
mdefine_line|#define NM_RBUFFER_END   (NM_RECORD_REG_OFFSET + 0x10)
DECL|macro|NM_RBUFFER_WMARK
mdefine_line|#define NM_RBUFFER_WMARK (NM_RECORD_REG_OFFSET + 0xc)
DECL|macro|NM_RBUFFER_CURRP
mdefine_line|#define NM_RBUFFER_CURRP (NM_RECORD_REG_OFFSET + 0x8)
DECL|macro|NM_PBUFFER_START
mdefine_line|#define NM_PBUFFER_START (NM_PLAYBACK_REG_OFFSET + 0x4)
DECL|macro|NM_PBUFFER_END
mdefine_line|#define NM_PBUFFER_END   (NM_PLAYBACK_REG_OFFSET + 0x14)
DECL|macro|NM_PBUFFER_WMARK
mdefine_line|#define NM_PBUFFER_WMARK (NM_PLAYBACK_REG_OFFSET + 0xc)
DECL|macro|NM_PBUFFER_CURRP
mdefine_line|#define NM_PBUFFER_CURRP (NM_PLAYBACK_REG_OFFSET + 0x8)
multiline_comment|/* A few trivial routines to make it easier to work with the registers&n;   on the chip. */
multiline_comment|/* This is a common code portion used to fix up the port offsets. */
DECL|macro|NM_FIX_PORT
mdefine_line|#define NM_FIX_PORT &bslash;&n;  if (port &lt; 1 || port &gt; 2 || card == NULL) &bslash;&n;      return -1; &bslash;&n;&bslash;&n;    if (offset &lt; card-&gt;port[port - 1].start_offset &bslash;&n;&t;|| offset &gt;= card-&gt;port[port - 1].end_offset) { &bslash;&n;&t;printk (KERN_ERR &quot;Bad access: port %d, offset 0x%x&bslash;n&quot;, port, offset); &bslash;&n;&t;return -1; &bslash;&n;    } &bslash;&n;    offset -= card-&gt;port[port - 1].start_offset;
DECL|macro|DEFwritePortX
mdefine_line|#define DEFwritePortX(X, func) &bslash;&n;static inline int nm256_writePort##X (struct nm256_info *card,&bslash;&n;&t;&t;&t;&t;      int port, int offset, int value)&bslash;&n;{&bslash;&n;    u##X *addr;&bslash;&n;&bslash;&n;    if (nm256_debug &gt; 1)&bslash;&n;        printk (KERN_DEBUG &quot;Writing 0x%x to %d:0x%x&bslash;n&quot;, value, port, offset);&bslash;&n;&bslash;&n;    NM_FIX_PORT;&bslash;&n;&bslash;&n;    addr = (u##X *)(card-&gt;port[port - 1].ptr + offset);&bslash;&n;    func (value, addr);&bslash;&n;    return 0;&bslash;&n;}
id|DEFwritePortX
(paren
l_int|8
comma
id|writeb
)paren
id|DEFwritePortX
(paren
l_int|16
comma
id|writew
)paren
id|DEFwritePortX
(paren
l_int|32
comma
id|writel
)paren
DECL|macro|DEFreadPortX
mdefine_line|#define DEFreadPortX(X, func) &bslash;&n;static inline u##X nm256_readPort##X (struct nm256_info *card,&bslash;&n;&t;&t;&t;&t;&t;int port, int offset)&bslash;&n;{&bslash;&n;    u##X *addr;&bslash;&n;&bslash;&n;    NM_FIX_PORT&bslash;&n;&bslash;&n;    addr = (u##X *)(card-&gt;port[port - 1].ptr + offset);&bslash;&n;    return func(addr);&bslash;&n;}
id|DEFreadPortX
(paren
l_int|8
comma
id|readb
)paren
id|DEFreadPortX
(paren
l_int|16
comma
id|readw
)paren
id|DEFreadPortX
(paren
l_int|32
comma
id|readl
)paren
r_static
r_inline
r_int
DECL|function|nm256_writeBuffer8
id|nm256_writeBuffer8
(paren
r_struct
id|nm256_info
op_star
id|card
comma
id|u8
op_star
id|src
comma
r_int
id|port
comma
r_int
id|offset
comma
r_int
id|amt
)paren
(brace
id|NM_FIX_PORT
suffix:semicolon
id|memcpy_toio
(paren
id|card-&gt;port
(braket
id|port
op_minus
l_int|1
)braket
dot
id|ptr
op_plus
id|offset
comma
id|src
comma
id|amt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nm256_readBuffer8
id|nm256_readBuffer8
(paren
r_struct
id|nm256_info
op_star
id|card
comma
id|u8
op_star
id|dst
comma
r_int
id|port
comma
r_int
id|offset
comma
r_int
id|amt
)paren
(brace
id|NM_FIX_PORT
suffix:semicolon
id|memcpy_fromio
(paren
id|dst
comma
id|card-&gt;port
(braket
id|port
op_minus
l_int|1
)braket
dot
id|ptr
op_plus
id|offset
comma
id|amt
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Returns a non-zero value if we should use the coefficient cache. */
r_extern
r_int
id|nm256_cachedCoefficients
(paren
r_struct
id|nm256_info
op_star
id|card
)paren
suffix:semicolon
macro_line|#endif
"&f;"
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 4&n; * End:&n; */
eof
