multiline_comment|/*&n; **********************************************************************&n; *     hwaccess.h&n; *     Copyright 1999, 2000 Creative Labs, Inc.&n; *&n; **********************************************************************&n; *&n; *     Date&t;&t;    Author&t;    Summary of changes&n; *     ----&t;&t;    ------&t;    ------------------&n; *     October 20, 1999     Bertrand Lee    base code release&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
macro_line|#ifndef _HWACCESS_H
DECL|macro|_HWACCESS_H
mdefine_line|#define _HWACCESS_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sound.h&gt;
macro_line|#include &lt;linux/soundcard.h&gt;
macro_line|#include &lt;linux/ac97_codec.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;efxmgr.h&quot;
macro_line|#include &quot;passthrough.h&quot;
macro_line|#include &quot;midi.h&quot;
DECL|macro|EMUPAGESIZE
mdefine_line|#define EMUPAGESIZE     4096            /* don&squot;t change */
DECL|macro|NUM_G
mdefine_line|#define NUM_G           64              /* use all channels */
DECL|macro|NUM_FXSENDS
mdefine_line|#define NUM_FXSENDS     4               /* don&squot;t change */
multiline_comment|/* setting this to other than a power of two may break some applications */
DECL|macro|MAXBUFSIZE
mdefine_line|#define MAXBUFSIZE&t;65536
DECL|macro|MAXPAGES
mdefine_line|#define MAXPAGES&t;8192 
DECL|macro|BUFMAXPAGES
mdefine_line|#define BUFMAXPAGES     (MAXBUFSIZE / PAGE_SIZE)
DECL|macro|FLAGS_AVAILABLE
mdefine_line|#define FLAGS_AVAILABLE     0x0001
DECL|macro|FLAGS_READY
mdefine_line|#define FLAGS_READY         0x0002
DECL|struct|memhandle
r_struct
id|memhandle
(brace
DECL|member|dma_handle
id|dma_addr_t
id|dma_handle
suffix:semicolon
DECL|member|addr
r_void
op_star
id|addr
suffix:semicolon
DECL|member|size
id|u32
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DEBUG_LEVEL
mdefine_line|#define DEBUG_LEVEL 2
macro_line|#ifdef EMU10K1_DEBUG
DECL|macro|DPD
macro_line|# define DPD(level,x,y...) do {if(level &lt;= DEBUG_LEVEL) printk( KERN_NOTICE &quot;emu10k1: %s: %d: &quot; x , __FILE__ , __LINE__ , y );} while(0)
DECL|macro|DPF
macro_line|# define DPF(level,x)   do {if(level &lt;= DEBUG_LEVEL) printk( KERN_NOTICE &quot;emu10k1: %s: %d: &quot; x , __FILE__ , __LINE__ );} while(0)
macro_line|#else
DECL|macro|DPD
macro_line|# define DPD(level,x,y...) do { } while (0) /* not debugging: nothing */
DECL|macro|DPF
macro_line|# define DPF(level,x) do { } while (0)
macro_line|#endif /* EMU10K1_DEBUG */
DECL|macro|ERROR
mdefine_line|#define ERROR() DPF(1,&quot;error&bslash;n&quot;)
multiline_comment|/* DATA STRUCTURES */
DECL|struct|emu10k1_waveout
r_struct
id|emu10k1_waveout
(brace
DECL|member|send_routing
id|u16
id|send_routing
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|send_a
id|u8
id|send_a
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|send_b
id|u8
id|send_b
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|send_c
id|u8
id|send_c
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|send_d
id|u8
id|send_d
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|emu10k1_wavein
r_struct
id|emu10k1_wavein
(brace
DECL|member|ac97
r_struct
id|wiinst
op_star
id|ac97
suffix:semicolon
DECL|member|mic
r_struct
id|wiinst
op_star
id|mic
suffix:semicolon
DECL|member|fx
r_struct
id|wiinst
op_star
id|fx
suffix:semicolon
DECL|member|recsrc
id|u8
id|recsrc
suffix:semicolon
DECL|member|fxwc
id|u32
id|fxwc
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CMD_READ
mdefine_line|#define CMD_READ 1
DECL|macro|CMD_WRITE
mdefine_line|#define CMD_WRITE 2
DECL|struct|mixer_private_ioctl
r_struct
id|mixer_private_ioctl
(brace
DECL|member|cmd
id|u32
id|cmd
suffix:semicolon
DECL|member|val
id|u32
id|val
(braket
l_int|90
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* bogus ioctls numbers to escape from OSS mixer limitations */
DECL|macro|CMD_WRITEFN0
mdefine_line|#define CMD_WRITEFN0            _IOW(&squot;D&squot;, 0, struct mixer_private_ioctl)
DECL|macro|CMD_READFN0
mdefine_line|#define CMD_READFN0&t;&t;_IOR(&squot;D&squot;, 1, struct mixer_private_ioctl) 
DECL|macro|CMD_WRITEPTR
mdefine_line|#define CMD_WRITEPTR&t;&t;_IOW(&squot;D&squot;, 2, struct mixer_private_ioctl) 
DECL|macro|CMD_READPTR
mdefine_line|#define CMD_READPTR&t;&t;_IOR(&squot;D&squot;, 3, struct mixer_private_ioctl) 
DECL|macro|CMD_SETRECSRC
mdefine_line|#define CMD_SETRECSRC&t;&t;_IOW(&squot;D&squot;, 4, struct mixer_private_ioctl) 
DECL|macro|CMD_GETRECSRC
mdefine_line|#define CMD_GETRECSRC&t;&t;_IOR(&squot;D&squot;, 5, struct mixer_private_ioctl) 
DECL|macro|CMD_GETVOICEPARAM
mdefine_line|#define CMD_GETVOICEPARAM&t;_IOR(&squot;D&squot;, 6, struct mixer_private_ioctl) 
DECL|macro|CMD_SETVOICEPARAM
mdefine_line|#define CMD_SETVOICEPARAM&t;_IOW(&squot;D&squot;, 7, struct mixer_private_ioctl) 
DECL|macro|CMD_GETPATCH
mdefine_line|#define CMD_GETPATCH&t;&t;_IOR(&squot;D&squot;, 8, struct mixer_private_ioctl) 
DECL|macro|CMD_GETGPR
mdefine_line|#define CMD_GETGPR&t;&t;_IOR(&squot;D&squot;, 9, struct mixer_private_ioctl) 
DECL|macro|CMD_GETCTLGPR
mdefine_line|#define CMD_GETCTLGPR           _IOR(&squot;D&squot;, 10, struct mixer_private_ioctl)
DECL|macro|CMD_SETPATCH
mdefine_line|#define CMD_SETPATCH&t;&t;_IOW(&squot;D&squot;, 11, struct mixer_private_ioctl) 
DECL|macro|CMD_SETGPR
mdefine_line|#define CMD_SETGPR&t;&t;_IOW(&squot;D&squot;, 12, struct mixer_private_ioctl) 
DECL|macro|CMD_SETCTLGPR
mdefine_line|#define CMD_SETCTLGPR&t;&t;_IOW(&squot;D&squot;, 13, struct mixer_private_ioctl)
DECL|macro|CMD_SETGPOUT
mdefine_line|#define CMD_SETGPOUT&t;&t;_IOW(&squot;D&squot;, 14, struct mixer_private_ioctl)
DECL|macro|CMD_GETGPR2OSS
mdefine_line|#define CMD_GETGPR2OSS&t;&t;_IOR(&squot;D&squot;, 15, struct mixer_private_ioctl)
DECL|macro|CMD_SETGPR2OSS
mdefine_line|#define CMD_SETGPR2OSS&t;&t;_IOW(&squot;D&squot;, 16, struct mixer_private_ioctl)
DECL|macro|CMD_SETMCH_FX
mdefine_line|#define CMD_SETMCH_FX&t;&t;_IOW(&squot;D&squot;, 17, struct mixer_private_ioctl)
DECL|macro|CMD_SETPASSTHROUGH
mdefine_line|#define CMD_SETPASSTHROUGH&t;_IOW(&squot;D&squot;, 18, struct mixer_private_ioctl)
DECL|macro|CMD_PRIVATE3_VERSION
mdefine_line|#define CMD_PRIVATE3_VERSION&t;_IOW(&squot;D&squot;, 19, struct mixer_private_ioctl)
singleline_comment|//up this number when breaking compatibility
DECL|macro|PRIVATE3_VERSION
mdefine_line|#define PRIVATE3_VERSION 1
DECL|struct|emu10k1_card
r_struct
id|emu10k1_card
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|virtualpagetable
r_struct
id|memhandle
id|virtualpagetable
suffix:semicolon
DECL|member|tankmem
r_struct
id|memhandle
id|tankmem
suffix:semicolon
DECL|member|silentpage
r_struct
id|memhandle
id|silentpage
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|voicetable
id|u8
id|voicetable
(braket
id|NUM_G
)braket
suffix:semicolon
DECL|member|emupagetable
id|u16
id|emupagetable
(braket
id|MAXPAGES
)braket
suffix:semicolon
DECL|member|timers
r_struct
id|list_head
id|timers
suffix:semicolon
DECL|member|timer_delay
r_int
id|timer_delay
suffix:semicolon
DECL|member|timer_lock
id|spinlock_t
id|timer_lock
suffix:semicolon
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
DECL|member|iobase
r_int
r_int
id|iobase
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|model
r_int
r_int
id|model
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|member|audio_dev
r_int
id|audio_dev
suffix:semicolon
DECL|member|audio_dev1
r_int
id|audio_dev1
suffix:semicolon
DECL|member|midi_dev
r_int
id|midi_dev
suffix:semicolon
macro_line|#ifdef EMU10K1_SEQUENCER
DECL|member|seq_dev
r_int
id|seq_dev
suffix:semicolon
DECL|member|seq_mididev
r_struct
id|emu10k1_mididevice
op_star
id|seq_mididev
suffix:semicolon
macro_line|#endif
DECL|member|ac97
r_struct
id|ac97_codec
id|ac97
suffix:semicolon
DECL|member|ac97_supported_mixers
r_int
id|ac97_supported_mixers
suffix:semicolon
DECL|member|ac97_stereo_mixers
r_int
id|ac97_stereo_mixers
suffix:semicolon
multiline_comment|/* Number of first fx voice for multichannel output */
DECL|member|mchannel_fx
id|u8
id|mchannel_fx
suffix:semicolon
DECL|member|waveout
r_struct
id|emu10k1_waveout
id|waveout
suffix:semicolon
DECL|member|wavein
r_struct
id|emu10k1_wavein
id|wavein
suffix:semicolon
DECL|member|mpuout
r_struct
id|emu10k1_mpuout
op_star
id|mpuout
suffix:semicolon
DECL|member|mpuin
r_struct
id|emu10k1_mpuin
op_star
id|mpuin
suffix:semicolon
DECL|member|open_sem
r_struct
id|semaphore
id|open_sem
suffix:semicolon
DECL|member|open_mode
id|mode_t
id|open_mode
suffix:semicolon
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|mpuacqcount
id|u32
id|mpuacqcount
suffix:semicolon
singleline_comment|// Mpu acquire count
DECL|member|has_toslink
id|u32
id|has_toslink
suffix:semicolon
singleline_comment|// TOSLink detection
DECL|member|chiprev
id|u8
id|chiprev
suffix:semicolon
multiline_comment|/* Chip revision                */
DECL|member|isaps
r_int
id|isaps
suffix:semicolon
DECL|member|mgr
r_struct
id|patch_manager
id|mgr
suffix:semicolon
DECL|member|pt
r_struct
id|pt_data
id|pt
suffix:semicolon
)brace
suffix:semicolon
r_int
id|emu10k1_addxmgr_alloc
c_func
(paren
id|u32
comma
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_addxmgr_free
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|emu10k1_find_control_gpr
c_func
(paren
r_struct
id|patch_manager
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_set_control_gpr
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
r_int
comma
id|s32
comma
r_int
)paren
suffix:semicolon
r_void
id|emu10k1_set_volume_gpr
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
r_int
comma
id|s32
comma
r_int
)paren
suffix:semicolon
DECL|macro|VOL_6BIT
mdefine_line|#define VOL_6BIT 0x40
DECL|macro|VOL_5BIT
mdefine_line|#define VOL_5BIT 0x20
DECL|macro|VOL_4BIT
mdefine_line|#define VOL_4BIT 0x10
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT &t;&t;    16384
id|u32
id|srToPitch
c_func
(paren
id|u32
)paren
suffix:semicolon
id|u8
id|sumVolumeToAttenuation
c_func
(paren
id|u32
)paren
suffix:semicolon
r_extern
r_struct
id|list_head
id|emu10k1_devs
suffix:semicolon
multiline_comment|/* Hardware Abstraction Layer access functions */
r_void
id|emu10k1_writefn0
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
id|u32
comma
id|u32
)paren
suffix:semicolon
id|u32
id|emu10k1_readfn0
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
id|u32
)paren
suffix:semicolon
r_void
id|sblive_writeptr
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
id|u32
comma
id|u32
comma
id|u32
)paren
suffix:semicolon
r_void
id|sblive_writeptr_tag
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
id|u32
id|channel
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|macro|TAGLIST_END
mdefine_line|#define TAGLIST_END 0
id|u32
id|sblive_readptr
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
id|u32
comma
id|u32
)paren
suffix:semicolon
r_void
id|emu10k1_irq_enable
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
id|u32
)paren
suffix:semicolon
r_void
id|emu10k1_irq_disable
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
id|u32
)paren
suffix:semicolon
r_void
id|emu10k1_set_stop_on_loop
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
id|u32
)paren
suffix:semicolon
r_void
id|emu10k1_clear_stop_on_loop
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
id|u32
)paren
suffix:semicolon
multiline_comment|/* AC97 Codec register access function */
id|u16
id|emu10k1_ac97_read
c_func
(paren
r_struct
id|ac97_codec
op_star
comma
id|u8
)paren
suffix:semicolon
r_void
id|emu10k1_ac97_write
c_func
(paren
r_struct
id|ac97_codec
op_star
comma
id|u8
comma
id|u16
)paren
suffix:semicolon
multiline_comment|/* MPU access function*/
r_int
id|emu10k1_mpu_write_data
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
id|u8
)paren
suffix:semicolon
r_int
id|emu10k1_mpu_read_data
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
id|u8
op_star
)paren
suffix:semicolon
r_int
id|emu10k1_mpu_reset
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
r_int
id|emu10k1_mpu_acquire
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
r_int
id|emu10k1_mpu_release
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
macro_line|#endif  /* _HWACCESS_H */
eof
