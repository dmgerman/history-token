macro_line|#ifndef __SOUND_EMU10K1_H
DECL|macro|__SOUND_EMU10K1_H
mdefine_line|#define __SOUND_EMU10K1_H
multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;,&n; *&t;&t;     Creative Labs, Inc.&n; *  Definitions for EMU10K1 (SB Live!) chips&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &quot;pcm.h&quot;
macro_line|#include &quot;rawmidi.h&quot;
macro_line|#include &quot;hwdep.h&quot;
macro_line|#include &quot;ac97_codec.h&quot;
macro_line|#include &quot;util_mem.h&quot;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifndef PCI_VENDOR_ID_CREATIVE
DECL|macro|PCI_VENDOR_ID_CREATIVE
mdefine_line|#define PCI_VENDOR_ID_CREATIVE&t;&t;0x1102
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_CREATIVE_EMU10K1
DECL|macro|PCI_DEVICE_ID_CREATIVE_EMU10K1
mdefine_line|#define PCI_DEVICE_ID_CREATIVE_EMU10K1&t;0x0002
macro_line|#endif
multiline_comment|/* ------------------- DEFINES -------------------- */
DECL|macro|EMUPAGESIZE
mdefine_line|#define EMUPAGESIZE     4096
DECL|macro|MAXREQVOICES
mdefine_line|#define MAXREQVOICES    8
DECL|macro|MAXPAGES
mdefine_line|#define MAXPAGES        8192
DECL|macro|RESERVED
mdefine_line|#define RESERVED        0
DECL|macro|NUM_MIDI
mdefine_line|#define NUM_MIDI        16
DECL|macro|NUM_G
mdefine_line|#define NUM_G           64              /* use all channels */
DECL|macro|NUM_FXSENDS
mdefine_line|#define NUM_FXSENDS     4
DECL|macro|TMEMSIZE
mdefine_line|#define TMEMSIZE        256*1024
DECL|macro|TMEMSIZEREG
mdefine_line|#define TMEMSIZEREG     4
DECL|macro|IP_TO_CP
mdefine_line|#define IP_TO_CP(ip) ((ip == 0) ? 0 : (((0x00001000uL | (ip &amp; 0x00000FFFL)) &lt;&lt; (((ip &gt;&gt; 12) &amp; 0x000FL) + 4)) &amp; 0xFFFF0000uL))
singleline_comment|// Audigy specify registers are prefixed with &squot;A_&squot;
multiline_comment|/************************************************************************************************/
multiline_comment|/* PCI function 0 registers, address = &lt;val&gt; + PCIBASE0&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************************************/
DECL|macro|PTR
mdefine_line|#define PTR&t;&t;&t;0x00&t;&t;/* Indexed register set pointer register&t;*/
multiline_comment|/* NOTE: The CHANNELNUM and ADDRESS words can&t;*/
multiline_comment|/* be modified independently of each other.&t;*/
DECL|macro|PTR_CHANNELNUM_MASK
mdefine_line|#define PTR_CHANNELNUM_MASK&t;0x0000003f&t;/* For each per-channel register, indicates the&t;*/
multiline_comment|/* channel number of the register to be&t;&t;*/
multiline_comment|/* accessed.  For non per-channel registers the&t;*/
multiline_comment|/* value should be set to zero.&t;&t;&t;*/
DECL|macro|PTR_ADDRESS_MASK
mdefine_line|#define PTR_ADDRESS_MASK&t;0x07ff0000&t;/* Register index&t;&t;&t;&t;*/
DECL|macro|A_PTR_ADDRESS_MASK
mdefine_line|#define A_PTR_ADDRESS_MASK&t;0x0fff0000
DECL|macro|DATA
mdefine_line|#define DATA&t;&t;&t;0x04&t;&t;/* Indexed register set data register&t;&t;*/
DECL|macro|IPR
mdefine_line|#define IPR&t;&t;&t;0x08&t;&t;/* Global interrupt pending register&t;&t;*/
multiline_comment|/* Clear pending interrupts by writing a 1 to&t;*/
multiline_comment|/* the relevant bits and zero to the other bits&t;*/
multiline_comment|/* The next two interrupts are for the midi port on the Audigy Drive (A_MPU1)&t;&t;&t;*/
DECL|macro|IPR_A_MIDITRANSBUFEMPTY2
mdefine_line|#define IPR_A_MIDITRANSBUFEMPTY2 0x10000000&t;/* MIDI UART transmit buffer empty&t;&t;*/
DECL|macro|IPR_A_MIDIRECVBUFEMPTY2
mdefine_line|#define IPR_A_MIDIRECVBUFEMPTY2&t;0x08000000&t;/* MIDI UART receive buffer empty&t;&t;*/
DECL|macro|IPR_SAMPLERATETRACKER
mdefine_line|#define IPR_SAMPLERATETRACKER&t;0x01000000&t;/* Sample rate tracker lock status change&t;*/
DECL|macro|IPR_FXDSP
mdefine_line|#define IPR_FXDSP&t;&t;0x00800000&t;/* Enable FX DSP interrupts&t;&t;&t;*/
DECL|macro|IPR_FORCEINT
mdefine_line|#define IPR_FORCEINT&t;&t;0x00400000&t;/* Force Sound Blaster interrupt&t;&t;*/
DECL|macro|IPR_PCIERROR
mdefine_line|#define IPR_PCIERROR&t;&t;0x00200000&t;/* PCI bus error&t;&t;&t;&t;*/
DECL|macro|IPR_VOLINCR
mdefine_line|#define IPR_VOLINCR&t;&t;0x00100000&t;/* Volume increment button pressed&t;&t;*/
DECL|macro|IPR_VOLDECR
mdefine_line|#define IPR_VOLDECR&t;&t;0x00080000&t;/* Volume decrement button pressed&t;&t;*/
DECL|macro|IPR_MUTE
mdefine_line|#define IPR_MUTE&t;&t;0x00040000&t;/* Mute button pressed&t;&t;&t;&t;*/
DECL|macro|IPR_MICBUFFULL
mdefine_line|#define IPR_MICBUFFULL&t;&t;0x00020000&t;/* Microphone buffer full&t;&t;&t;*/
DECL|macro|IPR_MICBUFHALFFULL
mdefine_line|#define IPR_MICBUFHALFFULL&t;0x00010000&t;/* Microphone buffer half full&t;&t;&t;*/
DECL|macro|IPR_ADCBUFFULL
mdefine_line|#define IPR_ADCBUFFULL&t;&t;0x00008000&t;/* ADC buffer full&t;&t;&t;&t;*/
DECL|macro|IPR_ADCBUFHALFFULL
mdefine_line|#define IPR_ADCBUFHALFFULL&t;0x00004000&t;/* ADC buffer half full&t;&t;&t;&t;*/
DECL|macro|IPR_EFXBUFFULL
mdefine_line|#define IPR_EFXBUFFULL&t;&t;0x00002000&t;/* Effects buffer full&t;&t;&t;&t;*/
DECL|macro|IPR_EFXBUFHALFFULL
mdefine_line|#define IPR_EFXBUFHALFFULL&t;0x00001000&t;/* Effects buffer half full&t;&t;&t;*/
DECL|macro|IPR_GPSPDIFSTATUSCHANGE
mdefine_line|#define IPR_GPSPDIFSTATUSCHANGE&t;0x00000800&t;/* GPSPDIF channel status change&t;&t;*/
DECL|macro|IPR_CDROMSTATUSCHANGE
mdefine_line|#define IPR_CDROMSTATUSCHANGE&t;0x00000400&t;/* CD-ROM channel status change&t;&t;&t;*/
DECL|macro|IPR_INTERVALTIMER
mdefine_line|#define IPR_INTERVALTIMER&t;0x00000200&t;/* Interval timer terminal count&t;&t;*/
DECL|macro|IPR_MIDITRANSBUFEMPTY
mdefine_line|#define IPR_MIDITRANSBUFEMPTY&t;0x00000100&t;/* MIDI UART transmit buffer empty&t;&t;*/
DECL|macro|IPR_MIDIRECVBUFEMPTY
mdefine_line|#define IPR_MIDIRECVBUFEMPTY&t;0x00000080&t;/* MIDI UART receive buffer empty&t;&t;*/
DECL|macro|IPR_CHANNELLOOP
mdefine_line|#define IPR_CHANNELLOOP&t;&t;0x00000040&t;/* One or more channel loop interrupts pending&t;*/
DECL|macro|IPR_CHANNELNUMBERMASK
mdefine_line|#define IPR_CHANNELNUMBERMASK&t;0x0000003f&t;/* When IPR_CHANNELLOOP is set, indicates the&t;*/
multiline_comment|/* Highest set channel in CLIPL or CLIPH.  When&t;*/
multiline_comment|/* IP is written with CL set, the bit in CLIPL&t;*/
multiline_comment|/* or CLIPH corresponding to the CIN value &t;*/
multiline_comment|/* written will be cleared.&t;&t;&t;*/
DECL|macro|INTE
mdefine_line|#define INTE&t;&t;&t;0x0c&t;&t;/* Interrupt enable register&t;&t;&t;*/
DECL|macro|INTE_VIRTUALSB_MASK
mdefine_line|#define INTE_VIRTUALSB_MASK&t;0xc0000000&t;/* Virtual Soundblaster I/O port capture&t;*/
DECL|macro|INTE_VIRTUALSB_220
mdefine_line|#define INTE_VIRTUALSB_220&t;0x00000000&t;/* Capture at I/O base address 0x220-0x22f&t;*/
DECL|macro|INTE_VIRTUALSB_240
mdefine_line|#define INTE_VIRTUALSB_240&t;0x40000000&t;/* Capture at I/O base address 0x240&t;&t;*/
DECL|macro|INTE_VIRTUALSB_260
mdefine_line|#define INTE_VIRTUALSB_260&t;0x80000000&t;/* Capture at I/O base address 0x260&t;&t;*/
DECL|macro|INTE_VIRTUALSB_280
mdefine_line|#define INTE_VIRTUALSB_280&t;0xc0000000&t;/* Capture at I/O base address 0x280&t;&t;*/
DECL|macro|INTE_VIRTUALMPU_MASK
mdefine_line|#define INTE_VIRTUALMPU_MASK&t;0x30000000&t;/* Virtual MPU I/O port capture&t;&t;&t;*/
DECL|macro|INTE_VIRTUALMPU_300
mdefine_line|#define INTE_VIRTUALMPU_300&t;0x00000000&t;/* Capture at I/O base address 0x300-0x301&t;*/
DECL|macro|INTE_VIRTUALMPU_310
mdefine_line|#define INTE_VIRTUALMPU_310&t;0x10000000&t;/* Capture at I/O base address 0x310&t;&t;*/
DECL|macro|INTE_VIRTUALMPU_320
mdefine_line|#define INTE_VIRTUALMPU_320&t;0x20000000&t;/* Capture at I/O base address 0x320&t;&t;*/
DECL|macro|INTE_VIRTUALMPU_330
mdefine_line|#define INTE_VIRTUALMPU_330&t;0x30000000&t;/* Capture at I/O base address 0x330&t;&t;*/
DECL|macro|INTE_MASTERDMAENABLE
mdefine_line|#define INTE_MASTERDMAENABLE&t;0x08000000&t;/* Master DMA emulation at 0x000-0x00f&t;&t;*/
DECL|macro|INTE_SLAVEDMAENABLE
mdefine_line|#define INTE_SLAVEDMAENABLE&t;0x04000000&t;/* Slave DMA emulation at 0x0c0-0x0df&t;&t;*/
DECL|macro|INTE_MASTERPICENABLE
mdefine_line|#define INTE_MASTERPICENABLE&t;0x02000000&t;/* Master PIC emulation at 0x020-0x021&t;&t;*/
DECL|macro|INTE_SLAVEPICENABLE
mdefine_line|#define INTE_SLAVEPICENABLE&t;0x01000000&t;/* Slave PIC emulation at 0x0a0-0x0a1&t;&t;*/
DECL|macro|INTE_VSBENABLE
mdefine_line|#define INTE_VSBENABLE&t;&t;0x00800000&t;/* Enable virtual Soundblaster&t;&t;&t;*/
DECL|macro|INTE_ADLIBENABLE
mdefine_line|#define INTE_ADLIBENABLE&t;0x00400000&t;/* Enable AdLib emulation at 0x388-0x38b&t;*/
DECL|macro|INTE_MPUENABLE
mdefine_line|#define INTE_MPUENABLE&t;&t;0x00200000&t;/* Enable virtual MPU&t;&t;&t;&t;*/
DECL|macro|INTE_FORCEINT
mdefine_line|#define INTE_FORCEINT&t;&t;0x00100000&t;/* Continuously assert INTAN&t;&t;&t;*/
DECL|macro|INTE_MRHANDENABLE
mdefine_line|#define INTE_MRHANDENABLE&t;0x00080000&t;/* Enable the &quot;Mr. Hand&quot; logic&t;&t;&t;*/
multiline_comment|/* NOTE: There is no reason to use this under&t;*/
multiline_comment|/* Linux, and it will cause odd hardware &t;*/
multiline_comment|/* behavior and possibly random segfaults and&t;*/
multiline_comment|/* lockups if enabled.&t;&t;&t;&t;*/
multiline_comment|/* The next two interrupts are for the midi port on the Audigy Drive (A_MPU1)&t;&t;&t;*/
DECL|macro|INTE_A_MIDITXENABLE2
mdefine_line|#define INTE_A_MIDITXENABLE2&t;0x00020000&t;/* Enable MIDI transmit-buffer-empty interrupts&t;*/
DECL|macro|INTE_A_MIDIRXENABLE2
mdefine_line|#define INTE_A_MIDIRXENABLE2&t;0x00010000&t;/* Enable MIDI receive-buffer-empty interrupts&t;*/
DECL|macro|INTE_SAMPLERATETRACKER
mdefine_line|#define INTE_SAMPLERATETRACKER&t;0x00002000&t;/* Enable sample rate tracker interrupts&t;*/
multiline_comment|/* NOTE: This bit must always be enabled       &t;*/
DECL|macro|INTE_FXDSPENABLE
mdefine_line|#define INTE_FXDSPENABLE&t;0x00001000&t;/* Enable FX DSP interrupts&t;&t;&t;*/
DECL|macro|INTE_PCIERRORENABLE
mdefine_line|#define INTE_PCIERRORENABLE&t;0x00000800&t;/* Enable PCI bus error interrupts&t;&t;*/
DECL|macro|INTE_VOLINCRENABLE
mdefine_line|#define INTE_VOLINCRENABLE&t;0x00000400&t;/* Enable volume increment button interrupts&t;*/
DECL|macro|INTE_VOLDECRENABLE
mdefine_line|#define INTE_VOLDECRENABLE&t;0x00000200&t;/* Enable volume decrement button interrupts&t;*/
DECL|macro|INTE_MUTEENABLE
mdefine_line|#define INTE_MUTEENABLE&t;&t;0x00000100&t;/* Enable mute button interrupts&t;&t;*/
DECL|macro|INTE_MICBUFENABLE
mdefine_line|#define INTE_MICBUFENABLE&t;0x00000080&t;/* Enable microphone buffer interrupts&t;&t;*/
DECL|macro|INTE_ADCBUFENABLE
mdefine_line|#define INTE_ADCBUFENABLE&t;0x00000040&t;/* Enable ADC buffer interrupts&t;&t;&t;*/
DECL|macro|INTE_EFXBUFENABLE
mdefine_line|#define INTE_EFXBUFENABLE&t;0x00000020&t;/* Enable Effects buffer interrupts&t;&t;*/
DECL|macro|INTE_GPSPDIFENABLE
mdefine_line|#define INTE_GPSPDIFENABLE&t;0x00000010&t;/* Enable GPSPDIF status interrupts&t;&t;*/
DECL|macro|INTE_CDSPDIFENABLE
mdefine_line|#define INTE_CDSPDIFENABLE&t;0x00000008&t;/* Enable CDSPDIF status interrupts&t;&t;*/
DECL|macro|INTE_INTERVALTIMERENB
mdefine_line|#define INTE_INTERVALTIMERENB&t;0x00000004&t;/* Enable interval timer interrupts&t;&t;*/
DECL|macro|INTE_MIDITXENABLE
mdefine_line|#define INTE_MIDITXENABLE&t;0x00000002&t;/* Enable MIDI transmit-buffer-empty interrupts&t;*/
DECL|macro|INTE_MIDIRXENABLE
mdefine_line|#define INTE_MIDIRXENABLE&t;0x00000001&t;/* Enable MIDI receive-buffer-empty interrupts&t;*/
DECL|macro|WC
mdefine_line|#define WC&t;&t;&t;0x10&t;&t;/* Wall Clock register&t;&t;&t;&t;*/
DECL|macro|WC_SAMPLECOUNTER_MASK
mdefine_line|#define WC_SAMPLECOUNTER_MASK&t;0x03FFFFC0&t;/* Sample periods elapsed since reset&t;&t;*/
DECL|macro|WC_SAMPLECOUNTER
mdefine_line|#define WC_SAMPLECOUNTER&t;0x14060010
DECL|macro|WC_CURRENTCHANNEL
mdefine_line|#define WC_CURRENTCHANNEL&t;0x0000003F&t;/* Channel [0..63] currently being serviced&t;*/
multiline_comment|/* NOTE: Each channel takes 1/64th of a sample&t;*/
multiline_comment|/* period to be serviced.&t;&t;&t;*/
DECL|macro|HCFG
mdefine_line|#define HCFG&t;&t;&t;0x14&t;&t;/* Hardware config register&t;&t;&t;*/
multiline_comment|/* NOTE: There is no reason to use the legacy&t;*/
multiline_comment|/* SoundBlaster emulation stuff described below&t;*/
multiline_comment|/* under Linux, and all kinds of weird hardware&t;*/
multiline_comment|/* behavior can result if you try.  Don&squot;t.&t;*/
DECL|macro|HCFG_LEGACYFUNC_MASK
mdefine_line|#define HCFG_LEGACYFUNC_MASK&t;0xe0000000&t;/* Legacy function number &t;&t;&t;*/
DECL|macro|HCFG_LEGACYFUNC_MPU
mdefine_line|#define HCFG_LEGACYFUNC_MPU&t;0x00000000&t;/* Legacy MPU&t; &t;&t;&t;&t;*/
DECL|macro|HCFG_LEGACYFUNC_SB
mdefine_line|#define HCFG_LEGACYFUNC_SB&t;0x40000000&t;/* Legacy SB&t;&t;&t;&t;&t;*/
DECL|macro|HCFG_LEGACYFUNC_AD
mdefine_line|#define HCFG_LEGACYFUNC_AD&t;0x60000000&t;/* Legacy AD&t;&t;&t;&t;&t;*/
DECL|macro|HCFG_LEGACYFUNC_MPIC
mdefine_line|#define HCFG_LEGACYFUNC_MPIC&t;0x80000000&t;/* Legacy MPIC&t;&t;&t;&t;&t;*/
DECL|macro|HCFG_LEGACYFUNC_MDMA
mdefine_line|#define HCFG_LEGACYFUNC_MDMA&t;0xa0000000&t;/* Legacy MDMA&t;&t;&t;&t;&t;*/
DECL|macro|HCFG_LEGACYFUNC_SPCI
mdefine_line|#define HCFG_LEGACYFUNC_SPCI&t;0xc0000000&t;/* Legacy SPCI&t;&t;&t;&t;&t;*/
DECL|macro|HCFG_LEGACYFUNC_SDMA
mdefine_line|#define HCFG_LEGACYFUNC_SDMA&t;0xe0000000&t;/* Legacy SDMA&t;&t;&t;&t;&t;*/
DECL|macro|HCFG_IOCAPTUREADDR
mdefine_line|#define HCFG_IOCAPTUREADDR&t;0x1f000000&t;/* The 4 LSBs of the captured I/O address.&t;*/
DECL|macro|HCFG_LEGACYWRITE
mdefine_line|#define HCFG_LEGACYWRITE&t;0x00800000&t;/* 1 = write, 0 = read &t;&t;&t;&t;*/
DECL|macro|HCFG_LEGACYWORD
mdefine_line|#define HCFG_LEGACYWORD&t;&t;0x00400000&t;/* 1 = word, 0 = byte &t;&t;&t;&t;*/
DECL|macro|HCFG_LEGACYINT
mdefine_line|#define HCFG_LEGACYINT&t;&t;0x00200000&t;/* 1 = legacy event captured. Write 1 to clear.&t;*/
multiline_comment|/* NOTE: The rest of the bits in this register&t;*/
multiline_comment|/* _are_ relevant under Linux.&t;&t;&t;*/
DECL|macro|HCFG_CODECFORMAT_MASK
mdefine_line|#define HCFG_CODECFORMAT_MASK&t;0x00070000&t;/* CODEC format&t;&t;&t;&t;&t;*/
DECL|macro|HCFG_CODECFORMAT_AC97
mdefine_line|#define HCFG_CODECFORMAT_AC97&t;0x00000000&t;/* AC97 CODEC format -- Primary Output&t;&t;*/
DECL|macro|HCFG_CODECFORMAT_I2S
mdefine_line|#define HCFG_CODECFORMAT_I2S&t;0x00010000&t;/* I2S CODEC format -- Secondary (Rear) Output&t;*/
DECL|macro|HCFG_GPINPUT0
mdefine_line|#define HCFG_GPINPUT0&t;&t;0x00004000&t;/* External pin112&t;&t;&t;&t;*/
DECL|macro|HCFG_GPINPUT1
mdefine_line|#define HCFG_GPINPUT1&t;&t;0x00002000&t;/* External pin110&t;&t;&t;&t;*/
DECL|macro|HCFG_GPOUTPUT_MASK
mdefine_line|#define HCFG_GPOUTPUT_MASK&t;0x00001c00&t;/* External pins which may be controlled&t;*/
DECL|macro|HCFG_GPOUT0
mdefine_line|#define HCFG_GPOUT0&t;&t;0x00001000&t;/* External pin? (spdif enable on 5.1)&t;&t;*/
DECL|macro|HCFG_GPOUT1
mdefine_line|#define HCFG_GPOUT1&t;&t;0x00000800&t;/* External pin? (IR)&t;&t;&t;&t;*/
DECL|macro|HCFG_GPOUT2
mdefine_line|#define HCFG_GPOUT2&t;&t;0x00000400&t;/* External pin? (IR)&t;&t;&t;&t;*/
DECL|macro|HCFG_JOYENABLE
mdefine_line|#define HCFG_JOYENABLE      &t;0x00000200&t;/* Internal joystick enable    &t;&t;&t;*/
DECL|macro|HCFG_PHASETRACKENABLE
mdefine_line|#define HCFG_PHASETRACKENABLE&t;0x00000100&t;/* Phase tracking enable&t;&t;&t;*/
multiline_comment|/* 1 = Force all 3 async digital inputs to use&t;*/
multiline_comment|/* the same async sample rate tracker (ZVIDEO)&t;*/
DECL|macro|HCFG_AC3ENABLE_MASK
mdefine_line|#define HCFG_AC3ENABLE_MASK&t;0x000000e0&t;/* AC3 async input control - Not implemented&t;*/
DECL|macro|HCFG_AC3ENABLE_ZVIDEO
mdefine_line|#define HCFG_AC3ENABLE_ZVIDEO&t;0x00000080&t;/* Channels 0 and 1 replace ZVIDEO&t;&t;*/
DECL|macro|HCFG_AC3ENABLE_CDSPDIF
mdefine_line|#define HCFG_AC3ENABLE_CDSPDIF&t;0x00000040&t;/* Channels 0 and 1 replace CDSPDIF&t;&t;*/
DECL|macro|HCFG_AC3ENABLE_GPSPDIF
mdefine_line|#define HCFG_AC3ENABLE_GPSPDIF  0x00000020      /* Channels 0 and 1 replace GPSPDIF             */
DECL|macro|HCFG_AUTOMUTE
mdefine_line|#define HCFG_AUTOMUTE&t;&t;0x00000010&t;/* When set, the async sample rate convertors&t;*/
multiline_comment|/* will automatically mute their output when&t;*/
multiline_comment|/* they are not rate-locked to the external&t;*/
multiline_comment|/* async audio source  &t;&t;&t;&t;*/
DECL|macro|HCFG_LOCKSOUNDCACHE
mdefine_line|#define HCFG_LOCKSOUNDCACHE&t;0x00000008&t;/* 1 = Cancel bustmaster accesses to soundcache */
multiline_comment|/* NOTE: This should generally never be used.  &t;*/
DECL|macro|HCFG_LOCKTANKCACHE_MASK
mdefine_line|#define HCFG_LOCKTANKCACHE_MASK&t;0x00000004&t;/* 1 = Cancel bustmaster accesses to tankcache&t;*/
multiline_comment|/* NOTE: This should generally never be used.  &t;*/
DECL|macro|HCFG_LOCKTANKCACHE
mdefine_line|#define HCFG_LOCKTANKCACHE&t;0x01020014
DECL|macro|HCFG_MUTEBUTTONENABLE
mdefine_line|#define HCFG_MUTEBUTTONENABLE&t;0x00000002&t;/* 1 = Master mute button sets AUDIOENABLE = 0.&t;*/
multiline_comment|/* NOTE: This is a &squot;cheap&squot; way to implement a&t;*/
multiline_comment|/* master mute function on the mute button, and&t;*/
multiline_comment|/* in general should not be used unless a more&t;*/
multiline_comment|/* sophisticated master mute function has not&t;*/
multiline_comment|/* been written.       &t;&t;&t;&t;*/
DECL|macro|HCFG_AUDIOENABLE
mdefine_line|#define HCFG_AUDIOENABLE&t;0x00000001&t;/* 0 = CODECs transmit zero-valued samples&t;*/
multiline_comment|/* Should be set to 1 when the EMU10K1 is&t;*/
multiline_comment|/* completely initialized.&t;&t;&t;*/
singleline_comment|//For Audigy, MPU port move to 0x70-0x74 ptr register
DECL|macro|MUDATA
mdefine_line|#define MUDATA&t;&t;&t;0x18&t;&t;/* MPU401 data register (8 bits)       &t;&t;*/
DECL|macro|MUCMD
mdefine_line|#define MUCMD&t;&t;&t;0x19&t;&t;/* MPU401 command register (8 bits)    &t;&t;*/
DECL|macro|MUCMD_RESET
mdefine_line|#define MUCMD_RESET&t;&t;0xff&t;&t;/* RESET command&t;&t;&t;&t;*/
DECL|macro|MUCMD_ENTERUARTMODE
mdefine_line|#define MUCMD_ENTERUARTMODE&t;0x3f&t;&t;/* Enter_UART_mode command&t;&t;&t;*/
multiline_comment|/* NOTE: All other commands are ignored&t;&t;*/
DECL|macro|MUSTAT
mdefine_line|#define MUSTAT&t;&t;&t;MUCMD&t;&t;/* MPU401 status register (8 bits)     &t;&t;*/
DECL|macro|MUSTAT_IRDYN
mdefine_line|#define MUSTAT_IRDYN&t;&t;0x80&t;&t;/* 0 = MIDI data or command ACK&t;&t;&t;*/
DECL|macro|MUSTAT_ORDYN
mdefine_line|#define MUSTAT_ORDYN&t;&t;0x40&t;&t;/* 0 = MUDATA can accept a command or data&t;*/
DECL|macro|A_IOCFG
mdefine_line|#define A_IOCFG&t;&t;&t;0x18&t;&t;/* GPIO on Audigy card (16bits)&t;&t;&t;*/
DECL|macro|A_GPINPUT_MASK
mdefine_line|#define A_GPINPUT_MASK&t;&t;0xff00
DECL|macro|A_GPOUTPUT_MASK
mdefine_line|#define A_GPOUTPUT_MASK&t;&t;0x00ff
DECL|macro|TIMER
mdefine_line|#define TIMER&t;&t;&t;0x1a&t;&t;/* Timer terminal count register&t;&t;*/
multiline_comment|/* NOTE: After the rate is changed, a maximum&t;*/
multiline_comment|/* of 1024 sample periods should be allowed&t;*/
multiline_comment|/* before the new rate is guaranteed accurate.&t;*/
DECL|macro|TIMER_RATE_MASK
mdefine_line|#define TIMER_RATE_MASK&t;&t;0x000003ff&t;/* Timer interrupt rate in sample periods&t;*/
multiline_comment|/* 0 == 1024 periods, [1..4] are not useful&t;*/
DECL|macro|TIMER_RATE
mdefine_line|#define TIMER_RATE&t;&t;0x0a00001a
DECL|macro|AC97DATA
mdefine_line|#define AC97DATA&t;&t;0x1c&t;&t;/* AC97 register set data register (16 bit)&t;*/
DECL|macro|AC97ADDRESS
mdefine_line|#define AC97ADDRESS&t;&t;0x1e&t;&t;/* AC97 register set address register (8 bit)&t;*/
DECL|macro|AC97ADDRESS_READY
mdefine_line|#define AC97ADDRESS_READY&t;0x80&t;&t;/* Read-only bit, reflects CODEC READY signal&t;*/
DECL|macro|AC97ADDRESS_ADDRESS
mdefine_line|#define AC97ADDRESS_ADDRESS&t;0x7f&t;&t;/* Address of indexed AC97 register&t;&t;*/
multiline_comment|/************************************************************************************************/
multiline_comment|/* PCI function 1 registers, address = &lt;val&gt; + PCIBASE1&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************************************/
DECL|macro|JOYSTICK1
mdefine_line|#define JOYSTICK1&t;&t;0x00&t;&t;/* Analog joystick port register&t;&t;*/
DECL|macro|JOYSTICK2
mdefine_line|#define JOYSTICK2&t;&t;0x01&t;&t;/* Analog joystick port register&t;&t;*/
DECL|macro|JOYSTICK3
mdefine_line|#define JOYSTICK3&t;&t;0x02&t;&t;/* Analog joystick port register&t;&t;*/
DECL|macro|JOYSTICK4
mdefine_line|#define JOYSTICK4&t;&t;0x03&t;&t;/* Analog joystick port register&t;&t;*/
DECL|macro|JOYSTICK5
mdefine_line|#define JOYSTICK5&t;&t;0x04&t;&t;/* Analog joystick port register&t;&t;*/
DECL|macro|JOYSTICK6
mdefine_line|#define JOYSTICK6&t;&t;0x05&t;&t;/* Analog joystick port register&t;&t;*/
DECL|macro|JOYSTICK7
mdefine_line|#define JOYSTICK7&t;&t;0x06&t;&t;/* Analog joystick port register&t;&t;*/
DECL|macro|JOYSTICK8
mdefine_line|#define JOYSTICK8&t;&t;0x07&t;&t;/* Analog joystick port register&t;&t;*/
multiline_comment|/* When writing, any write causes JOYSTICK_COMPARATOR output enable to be pulsed on write.&t;*/
multiline_comment|/* When reading, use these bitfields: */
DECL|macro|JOYSTICK_BUTTONS
mdefine_line|#define JOYSTICK_BUTTONS&t;0x0f&t;&t;/* Joystick button data&t;&t;&t;&t;*/
DECL|macro|JOYSTICK_COMPARATOR
mdefine_line|#define JOYSTICK_COMPARATOR&t;0xf0&t;&t;/* Joystick comparator data&t;&t;&t;*/
multiline_comment|/********************************************************************************************************/
multiline_comment|/* Emu10k1 pointer-offset register set, accessed through the PTR and DATA registers&t;&t;&t;*/
multiline_comment|/********************************************************************************************************/
DECL|macro|CPF
mdefine_line|#define CPF&t;&t;&t;0x00&t;&t;/* Current pitch and fraction register&t;&t;&t;*/
DECL|macro|CPF_CURRENTPITCH_MASK
mdefine_line|#define CPF_CURRENTPITCH_MASK&t;0xffff0000&t;/* Current pitch (linear, 0x4000 == unity pitch shift) &t;*/
DECL|macro|CPF_CURRENTPITCH
mdefine_line|#define CPF_CURRENTPITCH&t;0x10100000
DECL|macro|CPF_STEREO_MASK
mdefine_line|#define CPF_STEREO_MASK&t;&t;0x00008000&t;/* 1 = Even channel interleave, odd channel locked&t;*/
DECL|macro|CPF_STOP_MASK
mdefine_line|#define CPF_STOP_MASK&t;&t;0x00004000&t;/* 1 = Current pitch forced to 0&t;&t;&t;*/
DECL|macro|CPF_FRACADDRESS_MASK
mdefine_line|#define CPF_FRACADDRESS_MASK&t;0x00003fff&t;/* Linear fractional address of the current channel&t;*/
DECL|macro|PTRX
mdefine_line|#define PTRX&t;&t;&t;0x01&t;&t;/* Pitch target and send A/B amounts register&t;&t;*/
DECL|macro|PTRX_PITCHTARGET_MASK
mdefine_line|#define PTRX_PITCHTARGET_MASK&t;0xffff0000&t;/* Pitch target of specified channel&t;&t;&t;*/
DECL|macro|PTRX_PITCHTARGET
mdefine_line|#define PTRX_PITCHTARGET&t;0x10100001
DECL|macro|PTRX_FXSENDAMOUNT_A_MASK
mdefine_line|#define PTRX_FXSENDAMOUNT_A_MASK 0x0000ff00&t;/* Linear level of channel output sent to FX send bus A&t;*/
DECL|macro|PTRX_FXSENDAMOUNT_A
mdefine_line|#define PTRX_FXSENDAMOUNT_A&t;0x08080001
DECL|macro|PTRX_FXSENDAMOUNT_B_MASK
mdefine_line|#define PTRX_FXSENDAMOUNT_B_MASK 0x000000ff&t;/* Linear level of channel output sent to FX send bus B&t;*/
DECL|macro|PTRX_FXSENDAMOUNT_B
mdefine_line|#define PTRX_FXSENDAMOUNT_B&t;0x08000001
DECL|macro|CVCF
mdefine_line|#define CVCF&t;&t;&t;0x02&t;&t;/* Current volume and filter cutoff register&t;&t;*/
DECL|macro|CVCF_CURRENTVOL_MASK
mdefine_line|#define CVCF_CURRENTVOL_MASK&t;0xffff0000&t;/* Current linear volume of specified channel&t;&t;*/
DECL|macro|CVCF_CURRENTVOL
mdefine_line|#define CVCF_CURRENTVOL&t;&t;0x10100002
DECL|macro|CVCF_CURRENTFILTER_MASK
mdefine_line|#define CVCF_CURRENTFILTER_MASK&t;0x0000ffff&t;/* Current filter cutoff frequency of specified channel&t;*/
DECL|macro|CVCF_CURRENTFILTER
mdefine_line|#define CVCF_CURRENTFILTER&t;0x10000002
DECL|macro|VTFT
mdefine_line|#define VTFT&t;&t;&t;0x03&t;&t;/* Volume target and filter cutoff target register&t;*/
DECL|macro|VTFT_VOLUMETARGET_MASK
mdefine_line|#define VTFT_VOLUMETARGET_MASK&t;0xffff0000&t;/* Volume target of specified channel&t;&t;&t;*/
DECL|macro|VTFT_VOLUMETARGET
mdefine_line|#define VTFT_VOLUMETARGET&t;0x10100003
DECL|macro|VTFT_FILTERTARGET_MASK
mdefine_line|#define VTFT_FILTERTARGET_MASK&t;0x0000ffff&t;/* Filter cutoff target of specified channel&t;&t;*/
DECL|macro|VTFT_FILTERTARGET
mdefine_line|#define VTFT_FILTERTARGET&t;0x10000003
DECL|macro|Z1
mdefine_line|#define Z1&t;&t;&t;0x05&t;&t;/* Filter delay memory 1 register&t;&t;&t;*/
DECL|macro|Z2
mdefine_line|#define Z2&t;&t;&t;0x04&t;&t;/* Filter delay memory 2 register&t;&t;&t;*/
DECL|macro|PSST
mdefine_line|#define PSST&t;&t;&t;0x06&t;&t;/* Send C amount and loop start address register&t;*/
DECL|macro|PSST_FXSENDAMOUNT_C_MASK
mdefine_line|#define PSST_FXSENDAMOUNT_C_MASK 0xff000000&t;/* Linear level of channel output sent to FX send bus C&t;*/
DECL|macro|PSST_FXSENDAMOUNT_C
mdefine_line|#define PSST_FXSENDAMOUNT_C&t;0x08180006
DECL|macro|PSST_LOOPSTARTADDR_MASK
mdefine_line|#define PSST_LOOPSTARTADDR_MASK&t;0x00ffffff&t;/* Loop start address of the specified channel&t;&t;*/
DECL|macro|PSST_LOOPSTARTADDR
mdefine_line|#define PSST_LOOPSTARTADDR&t;0x18000006
DECL|macro|DSL
mdefine_line|#define DSL&t;&t;&t;0x07&t;&t;/* Send D amount and loop start address register&t;*/
DECL|macro|DSL_FXSENDAMOUNT_D_MASK
mdefine_line|#define DSL_FXSENDAMOUNT_D_MASK&t;0xff000000&t;/* Linear level of channel output sent to FX send bus D&t;*/
DECL|macro|DSL_FXSENDAMOUNT_D
mdefine_line|#define DSL_FXSENDAMOUNT_D&t;0x08180007
DECL|macro|DSL_LOOPENDADDR_MASK
mdefine_line|#define DSL_LOOPENDADDR_MASK&t;0x00ffffff&t;/* Loop end address of the specified channel&t;&t;*/
DECL|macro|DSL_LOOPENDADDR
mdefine_line|#define DSL_LOOPENDADDR&t;&t;0x18000007
DECL|macro|CCCA
mdefine_line|#define CCCA&t;&t;&t;0x08&t;&t;/* Filter Q, interp. ROM, byte size, cur. addr register */
DECL|macro|CCCA_RESONANCE
mdefine_line|#define CCCA_RESONANCE&t;&t;0xf0000000&t;/* Lowpass filter resonance (Q) height&t;&t;&t;*/
DECL|macro|CCCA_INTERPROMMASK
mdefine_line|#define CCCA_INTERPROMMASK&t;0x0e000000&t;/* Selects passband of interpolation ROM&t;&t;*/
multiline_comment|/* 1 == full band, 7 == lowpass&t;&t;&t;&t;*/
multiline_comment|/* ROM 0 is used when pitch shifting downward or less&t;*/
multiline_comment|/* then 3 semitones upward.  Increasingly higher ROM&t;*/
multiline_comment|/* numbers are used, typically in steps of 3 semitones,&t;*/
multiline_comment|/* as upward pitch shifting is performed.&t;&t;*/
DECL|macro|CCCA_INTERPROM_0
mdefine_line|#define CCCA_INTERPROM_0&t;0x00000000&t;/* Select interpolation ROM 0&t;&t;&t;&t;*/
DECL|macro|CCCA_INTERPROM_1
mdefine_line|#define CCCA_INTERPROM_1&t;0x02000000&t;/* Select interpolation ROM 1&t;&t;&t;&t;*/
DECL|macro|CCCA_INTERPROM_2
mdefine_line|#define CCCA_INTERPROM_2&t;0x04000000&t;/* Select interpolation ROM 2&t;&t;&t;&t;*/
DECL|macro|CCCA_INTERPROM_3
mdefine_line|#define CCCA_INTERPROM_3&t;0x06000000&t;/* Select interpolation ROM 3&t;&t;&t;&t;*/
DECL|macro|CCCA_INTERPROM_4
mdefine_line|#define CCCA_INTERPROM_4&t;0x08000000&t;/* Select interpolation ROM 4&t;&t;&t;&t;*/
DECL|macro|CCCA_INTERPROM_5
mdefine_line|#define CCCA_INTERPROM_5&t;0x0a000000&t;/* Select interpolation ROM 5&t;&t;&t;&t;*/
DECL|macro|CCCA_INTERPROM_6
mdefine_line|#define CCCA_INTERPROM_6&t;0x0c000000&t;/* Select interpolation ROM 6&t;&t;&t;&t;*/
DECL|macro|CCCA_INTERPROM_7
mdefine_line|#define CCCA_INTERPROM_7&t;0x0e000000&t;/* Select interpolation ROM 7&t;&t;&t;&t;*/
DECL|macro|CCCA_8BITSELECT
mdefine_line|#define CCCA_8BITSELECT&t;&t;0x01000000&t;/* 1 = Sound memory for this channel uses 8-bit samples&t;*/
DECL|macro|CCCA_CURRADDR_MASK
mdefine_line|#define CCCA_CURRADDR_MASK&t;0x00ffffff&t;/* Current address of the selected channel&t;&t;*/
DECL|macro|CCCA_CURRADDR
mdefine_line|#define CCCA_CURRADDR&t;&t;0x18000008
DECL|macro|CCR
mdefine_line|#define CCR&t;&t;&t;0x09&t;&t;/* Cache control register&t;&t;&t;&t;*/
DECL|macro|CCR_CACHEINVALIDSIZE
mdefine_line|#define CCR_CACHEINVALIDSIZE&t;0x07190009
DECL|macro|CCR_CACHEINVALIDSIZE_MASK
mdefine_line|#define CCR_CACHEINVALIDSIZE_MASK&t;0xfe000000&t;/* Number of invalid samples cache for this channel    &t;*/
DECL|macro|CCR_CACHELOOPFLAG
mdefine_line|#define CCR_CACHELOOPFLAG&t;0x01000000&t;/* 1 = Cache has a loop service pending&t;&t;&t;*/
DECL|macro|CCR_INTERLEAVEDSAMPLES
mdefine_line|#define CCR_INTERLEAVEDSAMPLES&t;0x00800000&t;/* 1 = A cache service will fetch interleaved samples&t;*/
DECL|macro|CCR_WORDSIZEDSAMPLES
mdefine_line|#define CCR_WORDSIZEDSAMPLES&t;0x00400000&t;/* 1 = A cache service will fetch word sized samples&t;*/
DECL|macro|CCR_READADDRESS
mdefine_line|#define CCR_READADDRESS&t;&t;0x06100009
DECL|macro|CCR_READADDRESS_MASK
mdefine_line|#define CCR_READADDRESS_MASK&t;0x003f0000&t;/* Location of cache just beyond current cache service&t;*/
DECL|macro|CCR_LOOPINVALSIZE
mdefine_line|#define CCR_LOOPINVALSIZE&t;0x0000fe00&t;/* Number of invalid samples in cache prior to loop&t;*/
multiline_comment|/* NOTE: This is valid only if CACHELOOPFLAG is set&t;*/
DECL|macro|CCR_LOOPFLAG
mdefine_line|#define CCR_LOOPFLAG&t;&t;0x00000100&t;/* Set for a single sample period when a loop occurs&t;*/
DECL|macro|CCR_CACHELOOPADDRHI
mdefine_line|#define CCR_CACHELOOPADDRHI&t;0x000000ff&t;/* DSL_LOOPSTARTADDR&squot;s hi byte if CACHELOOPFLAG is set&t;*/
DECL|macro|CLP
mdefine_line|#define CLP&t;&t;&t;0x0a&t;&t;/* Cache loop register (valid if CCR_CACHELOOPFLAG = 1) */
multiline_comment|/* NOTE: This register is normally not used&t;&t;*/
DECL|macro|CLP_CACHELOOPADDR
mdefine_line|#define CLP_CACHELOOPADDR&t;0x0000ffff&t;/* Cache loop address (DSL_LOOPSTARTADDR [0..15])&t;*/
DECL|macro|FXRT
mdefine_line|#define FXRT&t;&t;&t;0x0b&t;&t;/* Effects send routing register&t;&t;&t;*/
multiline_comment|/* NOTE: It is illegal to assign the same routing to&t;*/
multiline_comment|/* two effects sends.&t;&t;&t;&t;&t;*/
DECL|macro|FXRT_CHANNELA
mdefine_line|#define FXRT_CHANNELA&t;&t;0x000f0000&t;/* Effects send bus number for channel&squot;s effects send A&t;*/
DECL|macro|FXRT_CHANNELB
mdefine_line|#define FXRT_CHANNELB&t;&t;0x00f00000&t;/* Effects send bus number for channel&squot;s effects send B&t;*/
DECL|macro|FXRT_CHANNELC
mdefine_line|#define FXRT_CHANNELC&t;&t;0x0f000000&t;/* Effects send bus number for channel&squot;s effects send C&t;*/
DECL|macro|FXRT_CHANNELD
mdefine_line|#define FXRT_CHANNELD&t;&t;0xf0000000&t;/* Effects send bus number for channel&squot;s effects send D&t;*/
DECL|macro|MAPA
mdefine_line|#define MAPA&t;&t;&t;0x0c&t;&t;/* Cache map A&t;&t;&t;&t;&t;&t;*/
DECL|macro|MAPB
mdefine_line|#define MAPB&t;&t;&t;0x0d&t;&t;/* Cache map B&t;&t;&t;&t;&t;&t;*/
DECL|macro|MAP_PTE_MASK
mdefine_line|#define MAP_PTE_MASK&t;&t;0xffffe000&t;/* The 19 MSBs of the PTE indexed by the PTI&t;&t;*/
DECL|macro|MAP_PTI_MASK
mdefine_line|#define MAP_PTI_MASK&t;&t;0x00001fff&t;/* The 13 bit index to one of the 8192 PTE dwords      &t;*/
DECL|macro|ENVVOL
mdefine_line|#define ENVVOL&t;&t;&t;0x10&t;&t;/* Volume envelope register&t;&t;&t;&t;*/
DECL|macro|ENVVOL_MASK
mdefine_line|#define ENVVOL_MASK&t;&t;0x0000ffff&t;/* Current value of volume envelope state variable&t;*/  
multiline_comment|/* 0x8000-n == 666*n usec delay&t;       &t;&t;&t;*/
DECL|macro|ATKHLDV
mdefine_line|#define ATKHLDV &t;&t;0x11&t;&t;/* Volume envelope hold and attack register&t;&t;*/
DECL|macro|ATKHLDV_PHASE0
mdefine_line|#define ATKHLDV_PHASE0&t;&t;0x00008000&t;/* 0 = Begin attack phase&t;&t;&t;&t;*/
DECL|macro|ATKHLDV_HOLDTIME_MASK
mdefine_line|#define ATKHLDV_HOLDTIME_MASK&t;0x00007f00&t;/* Envelope hold time (127-n == n*88.2msec)&t;&t;*/
DECL|macro|ATKHLDV_ATTACKTIME_MASK
mdefine_line|#define ATKHLDV_ATTACKTIME_MASK&t;0x0000007f&t;/* Envelope attack time, log encoded&t;&t;&t;*/
multiline_comment|/* 0 = infinite, 1 = 10.9msec, ... 0x7f = 5.5msec&t;*/
DECL|macro|DCYSUSV
mdefine_line|#define DCYSUSV &t;&t;0x12&t;&t;/* Volume envelope sustain and decay register&t;&t;*/
DECL|macro|DCYSUSV_PHASE1_MASK
mdefine_line|#define DCYSUSV_PHASE1_MASK&t;0x00008000&t;/* 0 = Begin attack phase, 1 = begin release phase&t;*/
DECL|macro|DCYSUSV_SUSTAINLEVEL_MASK
mdefine_line|#define DCYSUSV_SUSTAINLEVEL_MASK 0x00007f00&t;/* 127 = full, 0 = off, 0.75dB increments&t;&t;*/
DECL|macro|DCYSUSV_CHANNELENABLE_MASK
mdefine_line|#define DCYSUSV_CHANNELENABLE_MASK 0x00000080&t;/* 1 = Inhibit envelope engine from writing values in&t;*/
multiline_comment|/* this channel and from writing to pitch, filter and&t;*/
multiline_comment|/* volume targets.&t;&t;&t;&t;&t;*/
DECL|macro|DCYSUSV_DECAYTIME_MASK
mdefine_line|#define DCYSUSV_DECAYTIME_MASK&t;0x0000007f&t;/* Volume envelope decay time, log encoded     &t;&t;*/
multiline_comment|/* 0 = 43.7msec, 1 = 21.8msec, 0x7f = 22msec&t;&t;*/
DECL|macro|LFOVAL1
mdefine_line|#define LFOVAL1 &t;&t;0x13&t;&t;/* Modulation LFO value&t;&t;&t;&t;&t;*/
DECL|macro|LFOVAL_MASK
mdefine_line|#define LFOVAL_MASK&t;&t;0x0000ffff&t;/* Current value of modulation LFO state variable&t;*/
multiline_comment|/* 0x8000-n == 666*n usec delay&t;&t;&t;&t;*/
DECL|macro|ENVVAL
mdefine_line|#define ENVVAL&t;&t;&t;0x14&t;&t;/* Modulation envelope register&t;&t;&t;&t;*/
DECL|macro|ENVVAL_MASK
mdefine_line|#define ENVVAL_MASK&t;&t;0x0000ffff&t;/* Current value of modulation envelope state variable &t;*/
multiline_comment|/* 0x8000-n == 666*n usec delay&t;&t;&t;&t;*/
DECL|macro|ATKHLDM
mdefine_line|#define ATKHLDM&t;&t;&t;0x15&t;&t;/* Modulation envelope hold and attack register&t;&t;*/
DECL|macro|ATKHLDM_PHASE0
mdefine_line|#define ATKHLDM_PHASE0&t;&t;0x00008000&t;/* 0 = Begin attack phase&t;&t;&t;&t;*/
DECL|macro|ATKHLDM_HOLDTIME
mdefine_line|#define ATKHLDM_HOLDTIME&t;0x00007f00&t;/* Envelope hold time (127-n == n*42msec)&t;&t;*/
DECL|macro|ATKHLDM_ATTACKTIME
mdefine_line|#define ATKHLDM_ATTACKTIME&t;0x0000007f&t;/* Envelope attack time, log encoded&t;&t;&t;*/
multiline_comment|/* 0 = infinite, 1 = 11msec, ... 0x7f = 5.5msec&t;&t;*/
DECL|macro|DCYSUSM
mdefine_line|#define DCYSUSM&t;&t;&t;0x16&t;&t;/* Modulation envelope decay and sustain register&t;*/
DECL|macro|DCYSUSM_PHASE1_MASK
mdefine_line|#define DCYSUSM_PHASE1_MASK&t;0x00008000&t;/* 0 = Begin attack phase, 1 = begin release phase&t;*/
DECL|macro|DCYSUSM_SUSTAINLEVEL_MASK
mdefine_line|#define DCYSUSM_SUSTAINLEVEL_MASK 0x00007f00&t;/* 127 = full, 0 = off, 0.75dB increments&t;&t;*/
DECL|macro|DCYSUSM_DECAYTIME_MASK
mdefine_line|#define DCYSUSM_DECAYTIME_MASK&t;0x0000007f&t;/* Envelope decay time, log encoded&t;&t;&t;*/
multiline_comment|/* 0 = 43.7msec, 1 = 21.8msec, 0x7f = 22msec&t;&t;*/
DECL|macro|LFOVAL2
mdefine_line|#define LFOVAL2 &t;&t;0x17&t;&t;/* Vibrato LFO register&t;&t;&t;&t;&t;*/
DECL|macro|LFOVAL2_MASK
mdefine_line|#define LFOVAL2_MASK&t;&t;0x0000ffff&t;/* Current value of vibrato LFO state variable &t;&t;*/
multiline_comment|/* 0x8000-n == 666*n usec delay&t;&t;&t;&t;*/
DECL|macro|IP
mdefine_line|#define IP&t;&t;&t;0x18&t;&t;/* Initial pitch register&t;&t;&t;&t;*/
DECL|macro|IP_MASK
mdefine_line|#define IP_MASK&t;&t;&t;0x0000ffff&t;/* Exponential initial pitch shift&t;&t;&t;*/
multiline_comment|/* 4 bits of octave, 12 bits of fractional octave&t;*/
DECL|macro|IP_UNITY
mdefine_line|#define IP_UNITY&t;&t;0x0000e000&t;/* Unity pitch shift&t;&t;&t;&t;&t;*/
DECL|macro|IFATN
mdefine_line|#define IFATN&t;&t;&t;0x19&t;&t;/* Initial filter cutoff and attenuation register&t;*/
DECL|macro|IFATN_FILTERCUTOFF_MASK
mdefine_line|#define IFATN_FILTERCUTOFF_MASK&t;0x0000ff00&t;/* Initial filter cutoff frequency in exponential units&t;*/
multiline_comment|/* 6 most significant bits are semitones&t;&t;*/
multiline_comment|/* 2 least significant bits are fractions&t;&t;*/
DECL|macro|IFATN_FILTERCUTOFF
mdefine_line|#define IFATN_FILTERCUTOFF&t;0x08080019
DECL|macro|IFATN_ATTENUATION_MASK
mdefine_line|#define IFATN_ATTENUATION_MASK&t;0x000000ff&t;/* Initial attenuation in 0.375dB steps&t;&t;&t;*/
DECL|macro|IFATN_ATTENUATION
mdefine_line|#define IFATN_ATTENUATION&t;0x08000019
DECL|macro|PEFE
mdefine_line|#define PEFE&t;&t;&t;0x1a&t;&t;/* Pitch envelope and filter envelope amount register&t;*/
DECL|macro|PEFE_PITCHAMOUNT_MASK
mdefine_line|#define PEFE_PITCHAMOUNT_MASK&t;0x0000ff00&t;/* Pitch envlope amount&t;&t;&t;&t;&t;*/
multiline_comment|/* Signed 2&squot;s complement, +/- one octave peak extremes&t;*/
DECL|macro|PEFE_PITCHAMOUNT
mdefine_line|#define PEFE_PITCHAMOUNT&t;0x0808001a
DECL|macro|PEFE_FILTERAMOUNT_MASK
mdefine_line|#define PEFE_FILTERAMOUNT_MASK&t;0x000000ff&t;/* Filter envlope amount&t;&t;&t;&t;*/
multiline_comment|/* Signed 2&squot;s complement, +/- six octaves peak extremes */
DECL|macro|PEFE_FILTERAMOUNT
mdefine_line|#define PEFE_FILTERAMOUNT&t;0x0800001a
DECL|macro|FMMOD
mdefine_line|#define FMMOD&t;&t;&t;0x1b&t;&t;/* Vibrato/filter modulation from LFO register&t;&t;*/
DECL|macro|FMMOD_MODVIBRATO
mdefine_line|#define FMMOD_MODVIBRATO&t;0x0000ff00&t;/* Vibrato LFO modulation depth&t;&t;&t;&t;*/
multiline_comment|/* Signed 2&squot;s complement, +/- one octave extremes&t;*/
DECL|macro|FMMOD_MOFILTER
mdefine_line|#define FMMOD_MOFILTER&t;&t;0x000000ff&t;/* Filter LFO modulation depth&t;&t;&t;&t;*/
multiline_comment|/* Signed 2&squot;s complement, +/- three octave extremes&t;*/
DECL|macro|TREMFRQ
mdefine_line|#define TREMFRQ &t;&t;0x1c&t;&t;/* Tremolo amount and modulation LFO frequency register&t;*/
DECL|macro|TREMFRQ_DEPTH
mdefine_line|#define TREMFRQ_DEPTH&t;&t;0x0000ff00&t;/* Tremolo depth&t;&t;&t;&t;&t;*/
multiline_comment|/* Signed 2&squot;s complement, with +/- 12dB extremes&t;*/
DECL|macro|TREMFRQ_FREQUENCY
mdefine_line|#define TREMFRQ_FREQUENCY&t;0x000000ff&t;/* Tremolo LFO frequency&t;&t;&t;&t;*/
multiline_comment|/* ??Hz steps, maximum of ?? Hz.&t;&t;&t;*/
DECL|macro|FM2FRQ2
mdefine_line|#define FM2FRQ2 &t;&t;0x1d&t;&t;/* Vibrato amount and vibrato LFO frequency register&t;*/
DECL|macro|FM2FRQ2_DEPTH
mdefine_line|#define FM2FRQ2_DEPTH&t;&t;0x0000ff00&t;/* Vibrato LFO vibrato depth&t;&t;&t;&t;*/
multiline_comment|/* Signed 2&squot;s complement, +/- one octave extremes&t;*/
DECL|macro|FM2FRQ2_FREQUENCY
mdefine_line|#define FM2FRQ2_FREQUENCY&t;0x000000ff&t;/* Vibrato LFO frequency&t;&t;&t;&t;*/
multiline_comment|/* 0.039Hz steps, maximum of 9.85 Hz.&t;&t;&t;*/
DECL|macro|TEMPENV
mdefine_line|#define TEMPENV &t;&t;0x1e&t;&t;/* Tempory envelope register&t;&t;&t;&t;*/
DECL|macro|TEMPENV_MASK
mdefine_line|#define TEMPENV_MASK&t;&t;0x0000ffff&t;/* 16-bit value&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* NOTE: All channels contain internal variables; do&t;*/
multiline_comment|/* not write to these locations.&t;&t;&t;*/
DECL|macro|CD0
mdefine_line|#define CD0&t;&t;&t;0x20&t;&t;/* Cache data 0 register&t;&t;&t;&t;*/
DECL|macro|CD1
mdefine_line|#define CD1&t;&t;&t;0x21&t;&t;/* Cache data 1 register&t;&t;&t;&t;*/
DECL|macro|CD2
mdefine_line|#define CD2&t;&t;&t;0x22&t;&t;/* Cache data 2 register&t;&t;&t;&t;*/
DECL|macro|CD3
mdefine_line|#define CD3&t;&t;&t;0x23&t;&t;/* Cache data 3 register&t;&t;&t;&t;*/
DECL|macro|CD4
mdefine_line|#define CD4&t;&t;&t;0x24&t;&t;/* Cache data 4 register&t;&t;&t;&t;*/
DECL|macro|CD5
mdefine_line|#define CD5&t;&t;&t;0x25&t;&t;/* Cache data 5 register&t;&t;&t;&t;*/
DECL|macro|CD6
mdefine_line|#define CD6&t;&t;&t;0x26&t;&t;/* Cache data 6 register&t;&t;&t;&t;*/
DECL|macro|CD7
mdefine_line|#define CD7&t;&t;&t;0x27&t;&t;/* Cache data 7 register&t;&t;&t;&t;*/
DECL|macro|CD8
mdefine_line|#define CD8&t;&t;&t;0x28&t;&t;/* Cache data 8 register&t;&t;&t;&t;*/
DECL|macro|CD9
mdefine_line|#define CD9&t;&t;&t;0x29&t;&t;/* Cache data 9 register&t;&t;&t;&t;*/
DECL|macro|CDA
mdefine_line|#define CDA&t;&t;&t;0x2a&t;&t;/* Cache data A register&t;&t;&t;&t;*/
DECL|macro|CDB
mdefine_line|#define CDB&t;&t;&t;0x2b&t;&t;/* Cache data B register&t;&t;&t;&t;*/
DECL|macro|CDC
mdefine_line|#define CDC&t;&t;&t;0x2c&t;&t;/* Cache data C register&t;&t;&t;&t;*/
DECL|macro|CDD
mdefine_line|#define CDD&t;&t;&t;0x2d&t;&t;/* Cache data D register&t;&t;&t;&t;*/
DECL|macro|CDE
mdefine_line|#define CDE&t;&t;&t;0x2e&t;&t;/* Cache data E register&t;&t;&t;&t;*/
DECL|macro|CDF
mdefine_line|#define CDF&t;&t;&t;0x2f&t;&t;/* Cache data F register&t;&t;&t;&t;*/
DECL|macro|PTB
mdefine_line|#define PTB&t;&t;&t;0x40&t;&t;/* Page table base register&t;&t;&t;&t;*/
DECL|macro|PTB_MASK
mdefine_line|#define PTB_MASK&t;&t;0xfffff000&t;/* Physical address of the page table in host memory&t;*/
DECL|macro|TCB
mdefine_line|#define TCB&t;&t;&t;0x41&t;&t;/* Tank cache base register    &t;&t;&t;&t;*/
DECL|macro|TCB_MASK
mdefine_line|#define TCB_MASK&t;&t;0xfffff000&t;/* Physical address of the bottom of host based TRAM&t;*/
DECL|macro|ADCCR
mdefine_line|#define ADCCR&t;&t;&t;0x42&t;&t;/* ADC sample rate/stereo control register&t;&t;*/
DECL|macro|ADCCR_RCHANENABLE
mdefine_line|#define ADCCR_RCHANENABLE&t;0x00000010&t;/* Enables right channel for writing to the host       &t;*/
DECL|macro|ADCCR_LCHANENABLE
mdefine_line|#define ADCCR_LCHANENABLE&t;0x00000008&t;/* Enables left channel for writing to the host&t;&t;*/
multiline_comment|/* NOTE: To guarantee phase coherency, both channels&t;*/
multiline_comment|/* must be disabled prior to enabling both channels.&t;*/
DECL|macro|A_ADCCR_RCHANENABLE
mdefine_line|#define A_ADCCR_RCHANENABLE&t;0x00000020
DECL|macro|A_ADCCR_LCHANENABLE
mdefine_line|#define A_ADCCR_LCHANENABLE&t;0x00000010
DECL|macro|A_ADCCR_SAMPLERATE_MASK
mdefine_line|#define A_ADCCR_SAMPLERATE_MASK 0x0000000F      /* Audigy sample rate convertor output rate&t;&t;*/
DECL|macro|ADCCR_SAMPLERATE_MASK
mdefine_line|#define ADCCR_SAMPLERATE_MASK&t;0x00000007&t;/* Sample rate convertor output rate&t;&t;&t;*/
DECL|macro|ADCCR_SAMPLERATE_48
mdefine_line|#define ADCCR_SAMPLERATE_48&t;0x00000000&t;/* 48kHz sample rate&t;&t;&t;&t;&t;*/
DECL|macro|ADCCR_SAMPLERATE_44
mdefine_line|#define ADCCR_SAMPLERATE_44&t;0x00000001&t;/* 44.1kHz sample rate&t;&t;&t;&t;&t;*/
DECL|macro|ADCCR_SAMPLERATE_32
mdefine_line|#define ADCCR_SAMPLERATE_32&t;0x00000002&t;/* 32kHz sample rate&t;&t;&t;&t;&t;*/
DECL|macro|ADCCR_SAMPLERATE_24
mdefine_line|#define ADCCR_SAMPLERATE_24&t;0x00000003&t;/* 24kHz sample rate&t;&t;&t;&t;&t;*/
DECL|macro|ADCCR_SAMPLERATE_22
mdefine_line|#define ADCCR_SAMPLERATE_22&t;0x00000004&t;/* 22.05kHz sample rate&t;&t;&t;&t;&t;*/
DECL|macro|ADCCR_SAMPLERATE_16
mdefine_line|#define ADCCR_SAMPLERATE_16&t;0x00000005&t;/* 16kHz sample rate&t;&t;&t;&t;&t;*/
DECL|macro|ADCCR_SAMPLERATE_11
mdefine_line|#define ADCCR_SAMPLERATE_11&t;0x00000006&t;/* 11.025kHz sample rate&t;&t;&t;&t;*/
DECL|macro|ADCCR_SAMPLERATE_8
mdefine_line|#define ADCCR_SAMPLERATE_8&t;0x00000007&t;/* 8kHz sample rate&t;&t;&t;&t;&t;*/
DECL|macro|A_ADCCR_SAMPLERATE_12
mdefine_line|#define A_ADCCR_SAMPLERATE_12&t;0x00000006&t;/* 12kHz sample rate&t;&t;&t;&t;&t;*/
DECL|macro|A_ADCCR_SAMPLERATE_11
mdefine_line|#define A_ADCCR_SAMPLERATE_11&t;0x00000007&t;/* 11.025kHz sample rate&t;&t;&t;&t;*/
DECL|macro|A_ADCCR_SAMPLERATE_8
mdefine_line|#define A_ADCCR_SAMPLERATE_8&t;0x00000008&t;/* 8kHz sample rate&t;&t;&t;&t;&t;*/
DECL|macro|FXWC
mdefine_line|#define FXWC&t;&t;&t;0x43&t;&t;/* FX output write channels register&t;&t;&t;*/
multiline_comment|/* When set, each bit enables the writing of the&t;*/
multiline_comment|/* corresponding FX output channel into host memory&t;*/
DECL|macro|FXWC_DEFAULTROUTE_C
mdefine_line|#define FXWC_DEFAULTROUTE_C     (1&lt;&lt;0)&t;&t;/* left emu out? */
DECL|macro|FXWC_DEFAULTROUTE_B
mdefine_line|#define FXWC_DEFAULTROUTE_B     (1&lt;&lt;1)&t;&t;/* right emu out? */
DECL|macro|FXWC_DEFAULTROUTE_A
mdefine_line|#define FXWC_DEFAULTROUTE_A     (1&lt;&lt;12)
DECL|macro|FXWC_DEFAULTROUTE_D
mdefine_line|#define FXWC_DEFAULTROUTE_D     (1&lt;&lt;13)
DECL|macro|FXWC_ADCLEFT
mdefine_line|#define FXWC_ADCLEFT            (1&lt;&lt;18)
DECL|macro|FXWC_CDROMSPDIFLEFT
mdefine_line|#define FXWC_CDROMSPDIFLEFT     (1&lt;&lt;18)
DECL|macro|FXWC_ADCRIGHT
mdefine_line|#define FXWC_ADCRIGHT           (1&lt;&lt;19)
DECL|macro|FXWC_CDROMSPDIFRIGHT
mdefine_line|#define FXWC_CDROMSPDIFRIGHT    (1&lt;&lt;19)
DECL|macro|FXWC_MIC
mdefine_line|#define FXWC_MIC                (1&lt;&lt;20)
DECL|macro|FXWC_ZOOMLEFT
mdefine_line|#define FXWC_ZOOMLEFT           (1&lt;&lt;20)
DECL|macro|FXWC_ZOOMRIGHT
mdefine_line|#define FXWC_ZOOMRIGHT          (1&lt;&lt;21)
DECL|macro|FXWC_SPDIFLEFT
mdefine_line|#define FXWC_SPDIFLEFT          (1&lt;&lt;22)&t;&t;/* 0x00400000 */
DECL|macro|FXWC_SPDIFRIGHT
mdefine_line|#define FXWC_SPDIFRIGHT         (1&lt;&lt;23)&t;&t;/* 0x00800000 */
DECL|macro|TCBS
mdefine_line|#define TCBS&t;&t;&t;0x44&t;&t;/* Tank cache buffer size register&t;&t;&t;*/
DECL|macro|TCBS_MASK
mdefine_line|#define TCBS_MASK&t;&t;0x00000007&t;/* Tank cache buffer size field&t;&t;&t;&t;*/
DECL|macro|TCBS_BUFFSIZE_16K
mdefine_line|#define TCBS_BUFFSIZE_16K&t;0x00000000
DECL|macro|TCBS_BUFFSIZE_32K
mdefine_line|#define TCBS_BUFFSIZE_32K&t;0x00000001
DECL|macro|TCBS_BUFFSIZE_64K
mdefine_line|#define TCBS_BUFFSIZE_64K&t;0x00000002
DECL|macro|TCBS_BUFFSIZE_128K
mdefine_line|#define TCBS_BUFFSIZE_128K&t;0x00000003
DECL|macro|TCBS_BUFFSIZE_256K
mdefine_line|#define TCBS_BUFFSIZE_256K&t;0x00000004
DECL|macro|TCBS_BUFFSIZE_512K
mdefine_line|#define TCBS_BUFFSIZE_512K&t;0x00000005
DECL|macro|TCBS_BUFFSIZE_1024K
mdefine_line|#define TCBS_BUFFSIZE_1024K&t;0x00000006
DECL|macro|TCBS_BUFFSIZE_2048K
mdefine_line|#define TCBS_BUFFSIZE_2048K&t;0x00000007
DECL|macro|MICBA
mdefine_line|#define MICBA&t;&t;&t;0x45&t;&t;/* AC97 microphone buffer address register&t;&t;*/
DECL|macro|MICBA_MASK
mdefine_line|#define MICBA_MASK&t;&t;0xfffff000&t;/* 20 bit base address&t;&t;&t;&t;&t;*/
DECL|macro|ADCBA
mdefine_line|#define ADCBA&t;&t;&t;0x46&t;&t;/* ADC buffer address register&t;&t;&t;&t;*/
DECL|macro|ADCBA_MASK
mdefine_line|#define ADCBA_MASK&t;&t;0xfffff000&t;/* 20 bit base address&t;&t;&t;&t;&t;*/
DECL|macro|FXBA
mdefine_line|#define FXBA&t;&t;&t;0x47&t;&t;/* FX Buffer Address */
DECL|macro|FXBA_MASK
mdefine_line|#define FXBA_MASK&t;&t;0xfffff000&t;/* 20 bit base address&t;&t;&t;&t;&t;*/
DECL|macro|MICBS
mdefine_line|#define MICBS&t;&t;&t;0x49&t;&t;/* Microphone buffer size register&t;&t;&t;*/
DECL|macro|ADCBS
mdefine_line|#define ADCBS&t;&t;&t;0x4a&t;&t;/* ADC buffer size register&t;&t;&t;&t;*/
DECL|macro|FXBS
mdefine_line|#define FXBS&t;&t;&t;0x4b&t;&t;/* FX buffer size register&t;&t;&t;&t;*/
multiline_comment|/* The following mask values define the size of the ADC, MIX and FX buffers in bytes */
DECL|macro|ADCBS_BUFSIZE_NONE
mdefine_line|#define ADCBS_BUFSIZE_NONE&t;0x00000000
DECL|macro|ADCBS_BUFSIZE_384
mdefine_line|#define ADCBS_BUFSIZE_384&t;0x00000001
DECL|macro|ADCBS_BUFSIZE_448
mdefine_line|#define ADCBS_BUFSIZE_448&t;0x00000002
DECL|macro|ADCBS_BUFSIZE_512
mdefine_line|#define ADCBS_BUFSIZE_512&t;0x00000003
DECL|macro|ADCBS_BUFSIZE_640
mdefine_line|#define ADCBS_BUFSIZE_640&t;0x00000004
DECL|macro|ADCBS_BUFSIZE_768
mdefine_line|#define ADCBS_BUFSIZE_768&t;0x00000005
DECL|macro|ADCBS_BUFSIZE_896
mdefine_line|#define ADCBS_BUFSIZE_896&t;0x00000006
DECL|macro|ADCBS_BUFSIZE_1024
mdefine_line|#define ADCBS_BUFSIZE_1024&t;0x00000007
DECL|macro|ADCBS_BUFSIZE_1280
mdefine_line|#define ADCBS_BUFSIZE_1280&t;0x00000008
DECL|macro|ADCBS_BUFSIZE_1536
mdefine_line|#define ADCBS_BUFSIZE_1536&t;0x00000009
DECL|macro|ADCBS_BUFSIZE_1792
mdefine_line|#define ADCBS_BUFSIZE_1792&t;0x0000000a
DECL|macro|ADCBS_BUFSIZE_2048
mdefine_line|#define ADCBS_BUFSIZE_2048&t;0x0000000b
DECL|macro|ADCBS_BUFSIZE_2560
mdefine_line|#define ADCBS_BUFSIZE_2560&t;0x0000000c
DECL|macro|ADCBS_BUFSIZE_3072
mdefine_line|#define ADCBS_BUFSIZE_3072&t;0x0000000d
DECL|macro|ADCBS_BUFSIZE_3584
mdefine_line|#define ADCBS_BUFSIZE_3584&t;0x0000000e
DECL|macro|ADCBS_BUFSIZE_4096
mdefine_line|#define ADCBS_BUFSIZE_4096&t;0x0000000f
DECL|macro|ADCBS_BUFSIZE_5120
mdefine_line|#define ADCBS_BUFSIZE_5120&t;0x00000010
DECL|macro|ADCBS_BUFSIZE_6144
mdefine_line|#define ADCBS_BUFSIZE_6144&t;0x00000011
DECL|macro|ADCBS_BUFSIZE_7168
mdefine_line|#define ADCBS_BUFSIZE_7168&t;0x00000012
DECL|macro|ADCBS_BUFSIZE_8192
mdefine_line|#define ADCBS_BUFSIZE_8192&t;0x00000013
DECL|macro|ADCBS_BUFSIZE_10240
mdefine_line|#define ADCBS_BUFSIZE_10240&t;0x00000014
DECL|macro|ADCBS_BUFSIZE_12288
mdefine_line|#define ADCBS_BUFSIZE_12288&t;0x00000015
DECL|macro|ADCBS_BUFSIZE_14366
mdefine_line|#define ADCBS_BUFSIZE_14366&t;0x00000016
DECL|macro|ADCBS_BUFSIZE_16384
mdefine_line|#define ADCBS_BUFSIZE_16384&t;0x00000017
DECL|macro|ADCBS_BUFSIZE_20480
mdefine_line|#define ADCBS_BUFSIZE_20480&t;0x00000018
DECL|macro|ADCBS_BUFSIZE_24576
mdefine_line|#define ADCBS_BUFSIZE_24576&t;0x00000019
DECL|macro|ADCBS_BUFSIZE_28672
mdefine_line|#define ADCBS_BUFSIZE_28672&t;0x0000001a
DECL|macro|ADCBS_BUFSIZE_32768
mdefine_line|#define ADCBS_BUFSIZE_32768&t;0x0000001b
DECL|macro|ADCBS_BUFSIZE_40960
mdefine_line|#define ADCBS_BUFSIZE_40960&t;0x0000001c
DECL|macro|ADCBS_BUFSIZE_49152
mdefine_line|#define ADCBS_BUFSIZE_49152&t;0x0000001d
DECL|macro|ADCBS_BUFSIZE_57344
mdefine_line|#define ADCBS_BUFSIZE_57344&t;0x0000001e
DECL|macro|ADCBS_BUFSIZE_65536
mdefine_line|#define ADCBS_BUFSIZE_65536&t;0x0000001f
DECL|macro|CDCS
mdefine_line|#define CDCS&t;&t;&t;0x50&t;&t;/* CD-ROM digital channel status register&t;*/
DECL|macro|GPSCS
mdefine_line|#define GPSCS&t;&t;&t;0x51&t;&t;/* General Purpose SPDIF channel status register*/
DECL|macro|DBG
mdefine_line|#define DBG&t;&t;&t;0x52&t;&t;/* DO NOT PROGRAM THIS REGISTER!!! MAY DESTROY CHIP */
DECL|macro|REG53
mdefine_line|#define REG53&t;&t;&t;0x53&t;&t;/* DO NOT PROGRAM THIS REGISTER!!! MAY DESTROY CHIP */
DECL|macro|A_DBG
mdefine_line|#define A_DBG&t;&t;&t; 0x53
DECL|macro|A_DBG_SINGLE_STEP
mdefine_line|#define A_DBG_SINGLE_STEP&t; 0x00020000&t;/* Set to zero to start dsp */
DECL|macro|A_DBG_ZC
mdefine_line|#define A_DBG_ZC&t;&t; 0x40000000&t;/* zero tram counter */
DECL|macro|A_DBG_STEP_ADDR
mdefine_line|#define A_DBG_STEP_ADDR&t;&t; 0x000003ff
DECL|macro|A_DBG_SATURATION_OCCURED
mdefine_line|#define A_DBG_SATURATION_OCCURED 0x20000000
DECL|macro|A_DBG_SATURATION_ADDR
mdefine_line|#define A_DBG_SATURATION_ADDR&t; 0x0ffc0000
DECL|macro|SPCS0
mdefine_line|#define SPCS0&t;&t;&t;0x54&t;&t;/* SPDIF output Channel Status 0 register&t;*/
DECL|macro|SPCS1
mdefine_line|#define SPCS1&t;&t;&t;0x55&t;&t;/* SPDIF output Channel Status 1 register&t;*/
DECL|macro|SPCS2
mdefine_line|#define SPCS2&t;&t;&t;0x56&t;&t;/* SPDIF output Channel Status 2 register&t;*/
DECL|macro|SPCS_CLKACCYMASK
mdefine_line|#define SPCS_CLKACCYMASK&t;0x30000000&t;/* Clock accuracy&t;&t;&t;&t;*/
DECL|macro|SPCS_CLKACCY_1000PPM
mdefine_line|#define SPCS_CLKACCY_1000PPM&t;0x00000000&t;/* 1000 parts per million&t;&t;&t;*/
DECL|macro|SPCS_CLKACCY_50PPM
mdefine_line|#define SPCS_CLKACCY_50PPM&t;0x10000000&t;/* 50 parts per million&t;&t;&t;&t;*/
DECL|macro|SPCS_CLKACCY_VARIABLE
mdefine_line|#define SPCS_CLKACCY_VARIABLE&t;0x20000000&t;/* Variable accuracy&t;&t;&t;&t;*/
DECL|macro|SPCS_SAMPLERATEMASK
mdefine_line|#define SPCS_SAMPLERATEMASK&t;0x0f000000&t;/* Sample rate&t;&t;&t;&t;&t;*/
DECL|macro|SPCS_SAMPLERATE_44
mdefine_line|#define SPCS_SAMPLERATE_44&t;0x00000000&t;/* 44.1kHz sample rate&t;&t;&t;&t;*/
DECL|macro|SPCS_SAMPLERATE_48
mdefine_line|#define SPCS_SAMPLERATE_48&t;0x02000000&t;/* 48kHz sample rate&t;&t;&t;&t;*/
DECL|macro|SPCS_SAMPLERATE_32
mdefine_line|#define SPCS_SAMPLERATE_32&t;0x03000000&t;/* 32kHz sample rate&t;&t;&t;&t;*/
DECL|macro|SPCS_CHANNELNUMMASK
mdefine_line|#define SPCS_CHANNELNUMMASK&t;0x00f00000&t;/* Channel number&t;&t;&t;&t;*/
DECL|macro|SPCS_CHANNELNUM_UNSPEC
mdefine_line|#define SPCS_CHANNELNUM_UNSPEC&t;0x00000000&t;/* Unspecified channel number&t;&t;&t;*/
DECL|macro|SPCS_CHANNELNUM_LEFT
mdefine_line|#define SPCS_CHANNELNUM_LEFT&t;0x00100000&t;/* Left channel&t;&t;&t;&t;&t;*/
DECL|macro|SPCS_CHANNELNUM_RIGHT
mdefine_line|#define SPCS_CHANNELNUM_RIGHT&t;0x00200000&t;/* Right channel&t;&t;&t;&t;*/
DECL|macro|SPCS_SOURCENUMMASK
mdefine_line|#define SPCS_SOURCENUMMASK&t;0x000f0000&t;/* Source number&t;&t;&t;&t;*/
DECL|macro|SPCS_SOURCENUM_UNSPEC
mdefine_line|#define SPCS_SOURCENUM_UNSPEC&t;0x00000000&t;/* Unspecified source number&t;&t;&t;*/
DECL|macro|SPCS_GENERATIONSTATUS
mdefine_line|#define SPCS_GENERATIONSTATUS&t;0x00008000&t;/* Originality flag (see IEC-958 spec)&t;&t;*/
DECL|macro|SPCS_CATEGORYCODEMASK
mdefine_line|#define SPCS_CATEGORYCODEMASK&t;0x00007f00&t;/* Category code (see IEC-958 spec)&t;&t;*/
DECL|macro|SPCS_MODEMASK
mdefine_line|#define SPCS_MODEMASK&t;&t;0x000000c0&t;/* Mode (see IEC-958 spec)&t;&t;&t;*/
DECL|macro|SPCS_EMPHASISMASK
mdefine_line|#define SPCS_EMPHASISMASK&t;0x00000038&t;/* Emphasis&t;&t;&t;&t;&t;*/
DECL|macro|SPCS_EMPHASIS_NONE
mdefine_line|#define SPCS_EMPHASIS_NONE&t;0x00000000&t;/* No emphasis&t;&t;&t;&t;&t;*/
DECL|macro|SPCS_EMPHASIS_50_15
mdefine_line|#define SPCS_EMPHASIS_50_15&t;0x00000008&t;/* 50/15 usec 2 channel&t;&t;&t;&t;*/
DECL|macro|SPCS_COPYRIGHT
mdefine_line|#define SPCS_COPYRIGHT&t;&t;0x00000004&t;/* Copyright asserted flag -- do not modify&t;*/
DECL|macro|SPCS_NOTAUDIODATA
mdefine_line|#define SPCS_NOTAUDIODATA&t;0x00000002&t;/* 0 = Digital audio, 1 = not audio&t;&t;*/
DECL|macro|SPCS_PROFESSIONAL
mdefine_line|#define SPCS_PROFESSIONAL&t;0x00000001&t;/* 0 = Consumer (IEC-958), 1 = pro (AES3-1992)&t;*/
multiline_comment|/* The 32-bit CLIx and SOLx registers all have one bit per channel control/status      &t;&t;*/
DECL|macro|CLIEL
mdefine_line|#define CLIEL&t;&t;&t;0x58&t;&t;/* Channel loop interrupt enable low register&t;*/
DECL|macro|CLIEH
mdefine_line|#define CLIEH&t;&t;&t;0x59&t;&t;/* Channel loop interrupt enable high register&t;*/
DECL|macro|CLIPL
mdefine_line|#define CLIPL&t;&t;&t;0x5a&t;&t;/* Channel loop interrupt pending low register&t;*/
DECL|macro|CLIPH
mdefine_line|#define CLIPH&t;&t;&t;0x5b&t;&t;/* Channel loop interrupt pending high register&t;*/
DECL|macro|SOLEL
mdefine_line|#define SOLEL&t;&t;&t;0x5c&t;&t;/* Stop on loop enable low register&t;&t;*/
DECL|macro|SOLEH
mdefine_line|#define SOLEH&t;&t;&t;0x5d&t;&t;/* Stop on loop enable high register&t;&t;*/
DECL|macro|SPBYPASS
mdefine_line|#define SPBYPASS&t;&t;0x5e&t;&t;/* SPDIF BYPASS mode register&t;&t;&t;*/
DECL|macro|SPBYPASS_ENABLE
mdefine_line|#define SPBYPASS_ENABLE&t;&t;0x00000001&t;/* Enable SPDIF bypass mode&t;&t;&t;*/
DECL|macro|AC97SLOT
mdefine_line|#define AC97SLOT&t;&t;0x5f            /* additional AC97 slots enable bits&t;&t;*/
DECL|macro|AC97SLOT_CNTR
mdefine_line|#define AC97SLOT_CNTR&t;&t;0x10            /* Center enable */
DECL|macro|AC97SLOT_LFE
mdefine_line|#define AC97SLOT_LFE&t;&t;0x20            /* LFE enable */
DECL|macro|CDSRCS
mdefine_line|#define CDSRCS&t;&t;&t;0x60&t;&t;/* CD-ROM Sample Rate Converter status register&t;*/
DECL|macro|GPSRCS
mdefine_line|#define GPSRCS&t;&t;&t;0x61&t;&t;/* General Purpose SPDIF sample rate cvt status */
DECL|macro|ZVSRCS
mdefine_line|#define ZVSRCS&t;&t;&t;0x62&t;&t;/* ZVideo sample rate converter status&t;&t;*/
multiline_comment|/* NOTE: This one has no SPDIFLOCKED field&t;*/
multiline_comment|/* Assumes sample lock&t;&t;&t;&t;*/
multiline_comment|/* These three bitfields apply to CDSRCS, GPSRCS, and (except as noted) ZVSRCS.&t;&t;&t;*/
DECL|macro|SRCS_SPDIFLOCKED
mdefine_line|#define SRCS_SPDIFLOCKED&t;0x02000000&t;/* SPDIF stream locked&t;&t;&t;&t;*/
DECL|macro|SRCS_RATELOCKED
mdefine_line|#define SRCS_RATELOCKED&t;&t;0x01000000&t;/* Sample rate locked&t;&t;&t;&t;*/
DECL|macro|SRCS_ESTSAMPLERATE
mdefine_line|#define SRCS_ESTSAMPLERATE&t;0x0007ffff&t;/* Do not modify this field.&t;&t;&t;*/
multiline_comment|/* Note that these values can vary +/- by a small amount                                        */
DECL|macro|SRCS_SPDIFRATE_44
mdefine_line|#define SRCS_SPDIFRATE_44&t;0x0003acd9
DECL|macro|SRCS_SPDIFRATE_48
mdefine_line|#define SRCS_SPDIFRATE_48&t;0x00040000
DECL|macro|SRCS_SPDIFRATE_96
mdefine_line|#define SRCS_SPDIFRATE_96&t;0x00080000
DECL|macro|MICIDX
mdefine_line|#define MICIDX                  0x63            /* Microphone recording buffer index register   */
DECL|macro|MICIDX_MASK
mdefine_line|#define MICIDX_MASK             0x0000ffff      /* 16-bit value                                 */
DECL|macro|MICIDX_IDX
mdefine_line|#define MICIDX_IDX&t;&t;0x10000063
DECL|macro|ADCIDX
mdefine_line|#define ADCIDX&t;&t;&t;0x64&t;&t;/* ADC recording buffer index register&t;&t;*/
DECL|macro|ADCIDX_MASK
mdefine_line|#define ADCIDX_MASK&t;&t;0x0000ffff&t;/* 16 bit index field&t;&t;&t;&t;*/
DECL|macro|ADCIDX_IDX
mdefine_line|#define ADCIDX_IDX&t;&t;0x10000064
DECL|macro|A_ADCIDX
mdefine_line|#define A_ADCIDX&t;&t;0x63
DECL|macro|A_ADCIDX_IDX
mdefine_line|#define A_ADCIDX_IDX&t;&t;0x10000063
DECL|macro|FXIDX
mdefine_line|#define FXIDX&t;&t;&t;0x65&t;&t;/* FX recording buffer index register&t;&t;*/
DECL|macro|FXIDX_MASK
mdefine_line|#define FXIDX_MASK&t;&t;0x0000ffff&t;/* 16-bit value&t;&t;&t;&t;&t;*/
DECL|macro|FXIDX_IDX
mdefine_line|#define FXIDX_IDX&t;&t;0x10000065
multiline_comment|/* This is the MPU port on the card (via the game port)&t;&t;&t;&t;&t;&t;*/
DECL|macro|A_MUDATA1
mdefine_line|#define A_MUDATA1&t;&t;0x70
DECL|macro|A_MUCMD1
mdefine_line|#define A_MUCMD1&t;&t;0x71
DECL|macro|A_MUSTAT1
mdefine_line|#define A_MUSTAT1&t;&t;A_MUCMD1
multiline_comment|/* This is the MPU port on the Audigy Drive &t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|A_MUDATA2
mdefine_line|#define A_MUDATA2&t;&t;0x72
DECL|macro|A_MUCMD2
mdefine_line|#define A_MUCMD2&t;&t;0x73
DECL|macro|A_MUSTAT2
mdefine_line|#define A_MUSTAT2&t;&t;A_MUCMD2&t;
multiline_comment|/* The next two are the Audigy equivalent of FXWC&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* the Audigy can record any output (16bit, 48kHz, up to 64 channel simultaneously) &t;&t;*/
multiline_comment|/* Each bit selects a channel for recording */
DECL|macro|A_FXWC1
mdefine_line|#define A_FXWC1&t;&t;&t;0x74            /* Selects 0x7f-0x60 for FX recording           */
DECL|macro|A_FXWC2
mdefine_line|#define A_FXWC2&t;&t;&t;0x75&t;&t;/* Selects 0x9f-0x80 for FX recording           */
DECL|macro|A_SPDIF_SAMPLERATE
mdefine_line|#define A_SPDIF_SAMPLERATE&t;0x76&t;&t;/* Set the sample rate of SPDIF output&t;&t;*/
DECL|macro|A_SPDIF_48000
mdefine_line|#define A_SPDIF_48000&t;&t;0x00000080
DECL|macro|A_SPDIF_44100
mdefine_line|#define A_SPDIF_44100&t;&t;0x00000000
DECL|macro|A_SPDIF_96000
mdefine_line|#define A_SPDIF_96000&t;&t;0x00000040
DECL|macro|A_FXRT2
mdefine_line|#define A_FXRT2&t;&t;&t;0x7c
DECL|macro|A_FXRT_CHANNELE
mdefine_line|#define A_FXRT_CHANNELE&t;&t;0x0000003f&t;/* Effects send bus number for channel&squot;s effects send E&t;*/
DECL|macro|A_FXRT_CHANNELF
mdefine_line|#define A_FXRT_CHANNELF&t;&t;0x00003f00&t;/* Effects send bus number for channel&squot;s effects send F&t;*/
DECL|macro|A_FXRT_CHANNELG
mdefine_line|#define A_FXRT_CHANNELG&t;&t;0x003f0000&t;/* Effects send bus number for channel&squot;s effects send G&t;*/
DECL|macro|A_FXRT_CHANNELH
mdefine_line|#define A_FXRT_CHANNELH&t;&t;0x3f000000&t;/* Effects send bus number for channel&squot;s effects send H&t;*/
DECL|macro|A_SENDAMOUNTS
mdefine_line|#define A_SENDAMOUNTS&t;&t;0x7d
DECL|macro|A_FXSENDAMOUNT_E_MASK
mdefine_line|#define A_FXSENDAMOUNT_E_MASK&t;0xFF000000
DECL|macro|A_FXSENDAMOUNT_F_MASK
mdefine_line|#define A_FXSENDAMOUNT_F_MASK&t;0x00FF0000
DECL|macro|A_FXSENDAMOUNT_G_MASK
mdefine_line|#define A_FXSENDAMOUNT_G_MASK&t;0x0000FF00
DECL|macro|A_FXSENDAMOUNT_H_MASK
mdefine_line|#define A_FXSENDAMOUNT_H_MASK&t;0x000000FF
multiline_comment|/* The send amounts for this one are the same as used with the emu10k1 */
DECL|macro|A_FXRT1
mdefine_line|#define A_FXRT1&t;&t;&t;0x7e
DECL|macro|A_FXRT_CHANNELA
mdefine_line|#define A_FXRT_CHANNELA&t;&t;0x0000003f
DECL|macro|A_FXRT_CHANNELB
mdefine_line|#define A_FXRT_CHANNELB&t;&t;0x00003f00
DECL|macro|A_FXRT_CHANNELC
mdefine_line|#define A_FXRT_CHANNELC&t;&t;0x003f0000
DECL|macro|A_FXRT_CHANNELD
mdefine_line|#define A_FXRT_CHANNELD&t;&t;0x3f000000
multiline_comment|/* Each FX general purpose register is 32 bits in length, all bits are used&t;&t;&t;*/
DECL|macro|FXGPREGBASE
mdefine_line|#define FXGPREGBASE&t;&t;0x100&t;&t;/* FX general purpose registers base       &t;*/
DECL|macro|A_FXGPREGBASE
mdefine_line|#define A_FXGPREGBASE&t;&t;0x400&t;&t;/* Audigy GPRs, 0x400 to 0x5ff&t;&t;&t;*/
multiline_comment|/* Tank audio data is logarithmically compressed down to 16 bits before writing to TRAM and is&t;*/
multiline_comment|/* decompressed back to 20 bits on a read.  There are a total of 160 locations, the last 32&t;*/
multiline_comment|/* locations are for external TRAM. &t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|TANKMEMDATAREGBASE
mdefine_line|#define TANKMEMDATAREGBASE&t;0x200&t;&t;/* Tank memory data registers base     &t;&t;*/
DECL|macro|TANKMEMDATAREG_MASK
mdefine_line|#define TANKMEMDATAREG_MASK&t;0x000fffff&t;/* 20 bit tank audio data field&t;&t;&t;*/
multiline_comment|/* Combined address field and memory opcode or flag field.  160 locations, last 32 are external&t;*/
DECL|macro|TANKMEMADDRREGBASE
mdefine_line|#define TANKMEMADDRREGBASE&t;0x300&t;&t;/* Tank memory address registers base&t;&t;*/
DECL|macro|TANKMEMADDRREG_ADDR_MASK
mdefine_line|#define TANKMEMADDRREG_ADDR_MASK 0x000fffff&t;/* 20 bit tank address field&t;&t;&t;*/
DECL|macro|TANKMEMADDRREG_CLEAR
mdefine_line|#define TANKMEMADDRREG_CLEAR&t;0x00800000&t;/* Clear tank memory&t;&t;&t;&t;*/
DECL|macro|TANKMEMADDRREG_ALIGN
mdefine_line|#define TANKMEMADDRREG_ALIGN&t;0x00400000&t;/* Align read or write relative to tank access&t;*/
DECL|macro|TANKMEMADDRREG_WRITE
mdefine_line|#define TANKMEMADDRREG_WRITE&t;0x00200000&t;/* Write to tank memory&t;&t;&t;&t;*/
DECL|macro|TANKMEMADDRREG_READ
mdefine_line|#define TANKMEMADDRREG_READ&t;0x00100000&t;/* Read from tank memory&t;&t;&t;*/
DECL|macro|MICROCODEBASE
mdefine_line|#define MICROCODEBASE&t;&t;0x400&t;&t;/* Microcode data base address&t;&t;&t;*/
multiline_comment|/* Each DSP microcode instruction is mapped into 2 doublewords &t;&t;&t;&t;&t;*/
multiline_comment|/* NOTE: When writing, always write the LO doubleword first.  Reads can be in either order.&t;*/
DECL|macro|LOWORD_OPX_MASK
mdefine_line|#define LOWORD_OPX_MASK&t;&t;0x000ffc00&t;/* Instruction operand X&t;&t;&t;*/
DECL|macro|LOWORD_OPY_MASK
mdefine_line|#define LOWORD_OPY_MASK&t;&t;0x000003ff&t;/* Instruction operand Y&t;&t;&t;*/
DECL|macro|HIWORD_OPCODE_MASK
mdefine_line|#define HIWORD_OPCODE_MASK&t;0x00f00000&t;/* Instruction opcode&t;&t;&t;&t;*/
DECL|macro|HIWORD_RESULT_MASK
mdefine_line|#define HIWORD_RESULT_MASK&t;0x000ffc00&t;/* Instruction result&t;&t;&t;&t;*/
DECL|macro|HIWORD_OPA_MASK
mdefine_line|#define HIWORD_OPA_MASK&t;&t;0x000003ff&t;/* Instruction operand A&t;&t;&t;*/
multiline_comment|/* Audigy Soundcard have a different instruction format */
DECL|macro|A_MICROCODEBASE
mdefine_line|#define A_MICROCODEBASE&t;&t;0x600
DECL|macro|A_LOWORD_OPY_MASK
mdefine_line|#define A_LOWORD_OPY_MASK&t;0x000007ff
DECL|macro|A_LOWORD_OPX_MASK
mdefine_line|#define A_LOWORD_OPX_MASK&t;0x007ff000
DECL|macro|A_HIWORD_OPCODE_MASK
mdefine_line|#define A_HIWORD_OPCODE_MASK&t;0x0f000000
DECL|macro|A_HIWORD_RESULT_MASK
mdefine_line|#define A_HIWORD_RESULT_MASK&t;0x007ff000
DECL|macro|A_HIWORD_OPA_MASK
mdefine_line|#define A_HIWORD_OPA_MASK&t;0x000007ff
multiline_comment|/* ------------------- STRUCTURES -------------------- */
DECL|typedef|emu10k1_t
r_typedef
r_struct
id|_snd_emu10k1
id|emu10k1_t
suffix:semicolon
DECL|typedef|emu10k1_voice_t
r_typedef
r_struct
id|_snd_emu10k1_voice
id|emu10k1_voice_t
suffix:semicolon
DECL|typedef|emu10k1_pcm_t
r_typedef
r_struct
id|_snd_emu10k1_pcm
id|emu10k1_pcm_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|EMU10K1_PCM
id|EMU10K1_PCM
comma
DECL|enumerator|EMU10K1_SYNTH
id|EMU10K1_SYNTH
comma
DECL|enumerator|EMU10K1_MIDI
id|EMU10K1_MIDI
DECL|typedef|emu10k1_voice_type_t
)brace
id|emu10k1_voice_type_t
suffix:semicolon
DECL|struct|_snd_emu10k1_voice
r_struct
id|_snd_emu10k1_voice
(brace
DECL|member|emu
id|emu10k1_t
op_star
id|emu
suffix:semicolon
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|use
r_int
id|use
suffix:colon
l_int|1
comma
DECL|member|pcm
id|pcm
suffix:colon
l_int|1
comma
DECL|member|synth
id|synth
suffix:colon
l_int|1
comma
DECL|member|midi
id|midi
suffix:colon
l_int|1
suffix:semicolon
DECL|member|interrupt
r_void
(paren
op_star
id|interrupt
)paren
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_voice_t
op_star
id|pvoice
)paren
suffix:semicolon
DECL|member|epcm
id|emu10k1_pcm_t
op_star
id|epcm
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|PLAYBACK_EMUVOICE
id|PLAYBACK_EMUVOICE
comma
DECL|enumerator|CAPTURE_AC97ADC
id|CAPTURE_AC97ADC
comma
DECL|enumerator|CAPTURE_AC97MIC
id|CAPTURE_AC97MIC
comma
DECL|enumerator|CAPTURE_EFX
id|CAPTURE_EFX
DECL|typedef|snd_emu10k1_pcm_type_t
)brace
id|snd_emu10k1_pcm_type_t
suffix:semicolon
DECL|struct|_snd_emu10k1_pcm
r_struct
id|_snd_emu10k1_pcm
(brace
DECL|member|emu
id|emu10k1_t
op_star
id|emu
suffix:semicolon
DECL|member|type
id|snd_emu10k1_pcm_type_t
id|type
suffix:semicolon
DECL|member|substream
id|snd_pcm_substream_t
op_star
id|substream
suffix:semicolon
DECL|member|voices
id|emu10k1_voice_t
op_star
id|voices
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|extra
id|emu10k1_voice_t
op_star
id|extra
suffix:semicolon
DECL|member|running
r_int
id|running
suffix:semicolon
DECL|member|memblk
id|snd_util_memblk_t
op_star
id|memblk
suffix:semicolon
DECL|member|start_addr
r_int
r_int
id|start_addr
suffix:semicolon
DECL|member|ccca_start_addr
r_int
r_int
id|ccca_start_addr
suffix:semicolon
DECL|member|capture_ipr
r_int
r_int
id|capture_ipr
suffix:semicolon
multiline_comment|/* interrupt acknowledge mask */
DECL|member|capture_inte
r_int
r_int
id|capture_inte
suffix:semicolon
multiline_comment|/* interrupt enable mask */
DECL|member|capture_ba_reg
r_int
r_int
id|capture_ba_reg
suffix:semicolon
multiline_comment|/* buffer address register */
DECL|member|capture_bs_reg
r_int
r_int
id|capture_bs_reg
suffix:semicolon
multiline_comment|/* buffer size register */
DECL|member|capture_idx_reg
r_int
r_int
id|capture_idx_reg
suffix:semicolon
multiline_comment|/* buffer index register */
DECL|member|capture_cr_val
r_int
r_int
id|capture_cr_val
suffix:semicolon
multiline_comment|/* control value */
DECL|member|capture_cr_val2
r_int
r_int
id|capture_cr_val2
suffix:semicolon
multiline_comment|/* control value2 (for audigy) */
DECL|member|capture_bs_val
r_int
r_int
id|capture_bs_val
suffix:semicolon
multiline_comment|/* buffer size value */
DECL|member|capture_bufsize
r_int
r_int
id|capture_bufsize
suffix:semicolon
multiline_comment|/* buffer size in bytes */
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|send_routing
r_int
r_char
id|send_routing
(braket
l_int|3
)braket
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|send_volume
r_int
r_char
id|send_volume
(braket
l_int|3
)braket
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|attn
r_int
r_int
id|attn
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ctl_send_routing
id|snd_kcontrol_t
op_star
id|ctl_send_routing
suffix:semicolon
DECL|member|ctl_send_volume
id|snd_kcontrol_t
op_star
id|ctl_send_volume
suffix:semicolon
DECL|member|ctl_attn
id|snd_kcontrol_t
op_star
id|ctl_attn
suffix:semicolon
DECL|member|epcm
id|emu10k1_pcm_t
op_star
id|epcm
suffix:semicolon
DECL|typedef|emu10k1_pcm_mixer_t
)brace
id|emu10k1_pcm_mixer_t
suffix:semicolon
DECL|macro|snd_emu10k1_compose_send_routing
mdefine_line|#define snd_emu10k1_compose_send_routing(route) &bslash;&n;((route[0] | (route[1] &lt;&lt; 4) | (route[2] &lt;&lt; 8) | (route[3] &lt;&lt; 12)) &lt;&lt; 16)
DECL|macro|snd_emu10k1_compose_audigy_fxrt1
mdefine_line|#define snd_emu10k1_compose_audigy_fxrt1(route) &bslash;&n;(((unsigned int)route[0] | ((unsigned int)route[1] &lt;&lt; 8) | ((unsigned int)route[2] &lt;&lt; 16) | ((unsigned int)route[3] &lt;&lt; 12)) &lt;&lt; 24)
DECL|macro|snd_emu10k1_compose_audigy_fxrt2
mdefine_line|#define snd_emu10k1_compose_audigy_fxrt2(route) &bslash;&n;(((unsigned int)route[4] | ((unsigned int)route[5] &lt;&lt; 8) | ((unsigned int)route[6] &lt;&lt; 16) | ((unsigned int)route[7] &lt;&lt; 12)) &lt;&lt; 24)
DECL|struct|snd_emu10k1_memblk
r_typedef
r_struct
id|snd_emu10k1_memblk
(brace
DECL|member|mem
id|snd_util_memblk_t
id|mem
suffix:semicolon
multiline_comment|/* private part */
DECL|member|first_page
DECL|member|last_page
DECL|member|pages
DECL|member|mapped_page
r_int
id|first_page
comma
id|last_page
comma
id|pages
comma
id|mapped_page
suffix:semicolon
DECL|member|map_locked
r_int
r_int
id|map_locked
suffix:semicolon
DECL|member|mapped_link
r_struct
id|list_head
id|mapped_link
suffix:semicolon
DECL|member|mapped_order_link
r_struct
id|list_head
id|mapped_order_link
suffix:semicolon
DECL|typedef|emu10k1_memblk_t
)brace
id|emu10k1_memblk_t
suffix:semicolon
DECL|macro|snd_emu10k1_memblk_offset
mdefine_line|#define snd_emu10k1_memblk_offset(blk)&t;(((blk)-&gt;mapped_page &lt;&lt; PAGE_SHIFT) | ((blk)-&gt;mem.offset &amp; (PAGE_SIZE - 1)))
DECL|macro|EMU10K1_MAX_TRAM_BLOCKS_PER_CODE
mdefine_line|#define EMU10K1_MAX_TRAM_BLOCKS_PER_CODE&t;16
r_typedef
r_struct
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list link container */
DECL|member|vcount
r_int
r_int
id|vcount
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* count of GPR (1..16) */
DECL|member|gpr
r_int
r_char
id|gpr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* GPR number(s) */
DECL|member|value
r_int
r_int
id|value
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|min
r_int
r_int
id|min
suffix:semicolon
multiline_comment|/* minimum range */
DECL|member|max
r_int
r_int
id|max
suffix:semicolon
multiline_comment|/* maximum range */
DECL|member|translation
r_int
r_int
id|translation
suffix:semicolon
multiline_comment|/* translation type (EMU10K1_GRP_TRANSLATION*) */
DECL|member|kcontrol
id|snd_kcontrol_t
op_star
id|kcontrol
suffix:semicolon
DECL|typedef|snd_emu10k1_fx8010_ctl_t
)brace
id|snd_emu10k1_fx8010_ctl_t
suffix:semicolon
DECL|typedef|snd_fx8010_irq_handler_t
r_typedef
r_void
(paren
id|snd_fx8010_irq_handler_t
)paren
(paren
id|emu10k1_t
op_star
id|emu
comma
r_void
op_star
id|private_data
)paren
suffix:semicolon
DECL|struct|_snd_emu10k1_fx8010_irq
r_typedef
r_struct
id|_snd_emu10k1_fx8010_irq
(brace
DECL|member|next
r_struct
id|_snd_emu10k1_fx8010_irq
op_star
id|next
suffix:semicolon
DECL|member|handler
id|snd_fx8010_irq_handler_t
op_star
id|handler
suffix:semicolon
DECL|member|gpr_running
r_int
r_char
id|gpr_running
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|typedef|snd_emu10k1_fx8010_irq_t
)brace
id|snd_emu10k1_fx8010_irq_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|valid
r_int
r_int
id|valid
suffix:colon
l_int|1
comma
DECL|member|opened
id|opened
suffix:colon
l_int|1
comma
DECL|member|active
id|active
suffix:colon
l_int|1
suffix:semicolon
DECL|member|channels
r_int
r_int
id|channels
suffix:semicolon
multiline_comment|/* 16-bit channels count */
DECL|member|tram_start
r_int
r_int
id|tram_start
suffix:semicolon
multiline_comment|/* initial ring buffer position in TRAM (in samples) */
DECL|member|buffer_size
r_int
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* count of buffered samples */
DECL|member|gpr_size
r_int
r_char
id|gpr_size
suffix:semicolon
multiline_comment|/* GPR containing size of ring buffer in samples (host) */
DECL|member|gpr_ptr
r_int
r_char
id|gpr_ptr
suffix:semicolon
multiline_comment|/* GPR containing current pointer in the ring buffer (host = reset, FX8010) */
DECL|member|gpr_count
r_int
r_char
id|gpr_count
suffix:semicolon
multiline_comment|/* GPR containing count of samples between two interrupts (host) */
DECL|member|gpr_tmpcount
r_int
r_char
id|gpr_tmpcount
suffix:semicolon
multiline_comment|/* GPR containing current count of samples to interrupt (host = set, FX8010) */
DECL|member|gpr_trigger
r_int
r_char
id|gpr_trigger
suffix:semicolon
multiline_comment|/* GPR containing trigger (activate) information (host) */
DECL|member|gpr_running
r_int
r_char
id|gpr_running
suffix:semicolon
multiline_comment|/* GPR containing info if PCM is running (FX8010) */
DECL|member|etram
r_int
r_char
id|etram
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* external TRAM address &amp; data */
DECL|member|sw_data
DECL|member|hw_data
r_int
r_int
id|sw_data
comma
id|hw_data
suffix:semicolon
DECL|member|sw_io
DECL|member|hw_io
r_int
r_int
id|sw_io
comma
id|hw_io
suffix:semicolon
DECL|member|sw_ready
DECL|member|hw_ready
r_int
r_int
id|sw_ready
comma
id|hw_ready
suffix:semicolon
DECL|member|appl_ptr
r_int
r_int
id|appl_ptr
suffix:semicolon
DECL|member|tram_pos
r_int
r_int
id|tram_pos
suffix:semicolon
DECL|member|tram_shift
r_int
r_int
id|tram_shift
suffix:semicolon
DECL|member|irq
id|snd_emu10k1_fx8010_irq_t
op_star
id|irq
suffix:semicolon
DECL|typedef|snd_emu10k1_fx8010_pcm_t
)brace
id|snd_emu10k1_fx8010_pcm_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|fxbus_mask
r_int
r_int
id|fxbus_mask
suffix:semicolon
multiline_comment|/* used FX buses (bitmask) */
DECL|member|extin_mask
r_int
r_int
id|extin_mask
suffix:semicolon
multiline_comment|/* used external inputs (bitmask) */
DECL|member|extout_mask
r_int
r_int
id|extout_mask
suffix:semicolon
multiline_comment|/* used external outputs (bitmask) */
DECL|member|pad1
r_int
r_int
id|pad1
suffix:semicolon
DECL|member|itram_size
r_int
r_int
id|itram_size
suffix:semicolon
multiline_comment|/* internal TRAM size in samples */
DECL|member|etram_size
r_int
r_int
id|etram_size
suffix:semicolon
multiline_comment|/* external TRAM size in samples */
DECL|member|etram_pages
r_void
op_star
id|etram_pages
suffix:semicolon
multiline_comment|/* allocated pages for external TRAM */
DECL|member|etram_pages_dmaaddr
id|dma_addr_t
id|etram_pages_dmaaddr
suffix:semicolon
DECL|member|dbg
r_int
r_int
id|dbg
suffix:semicolon
multiline_comment|/* FX debugger register */
DECL|member|name
r_int
r_char
id|name
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|gpr_size
r_int
id|gpr_size
suffix:semicolon
multiline_comment|/* size of allocated GPR controls */
DECL|member|gpr_count
r_int
id|gpr_count
suffix:semicolon
multiline_comment|/* count of used kcontrols */
DECL|member|gpr_ctl
r_struct
id|list_head
id|gpr_ctl
suffix:semicolon
multiline_comment|/* GPR controls */
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|pcm
id|snd_emu10k1_fx8010_pcm_t
id|pcm
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|irq_lock
id|spinlock_t
id|irq_lock
suffix:semicolon
DECL|member|irq_handlers
id|snd_emu10k1_fx8010_irq_t
op_star
id|irq_handlers
suffix:semicolon
DECL|typedef|snd_emu10k1_fx8010_t
)brace
id|snd_emu10k1_fx8010_t
suffix:semicolon
DECL|macro|emu10k1_gpr_ctl
mdefine_line|#define emu10k1_gpr_ctl(n) list_entry(n, snd_emu10k1_fx8010_ctl_t, list)
r_typedef
r_struct
(brace
DECL|member|emu
r_struct
id|_snd_emu10k1
op_star
id|emu
suffix:semicolon
DECL|member|rmidi
id|snd_rawmidi_t
op_star
id|rmidi
suffix:semicolon
DECL|member|substream_input
id|snd_rawmidi_substream_t
op_star
id|substream_input
suffix:semicolon
DECL|member|substream_output
id|snd_rawmidi_substream_t
op_star
id|substream_output
suffix:semicolon
DECL|member|midi_mode
r_int
r_int
id|midi_mode
suffix:semicolon
DECL|member|input_lock
id|spinlock_t
id|input_lock
suffix:semicolon
DECL|member|output_lock
id|spinlock_t
id|output_lock
suffix:semicolon
DECL|member|open_lock
id|spinlock_t
id|open_lock
suffix:semicolon
DECL|member|tx_enable
DECL|member|rx_enable
r_int
id|tx_enable
comma
id|rx_enable
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|ipr_tx
DECL|member|ipr_rx
r_int
id|ipr_tx
comma
id|ipr_rx
suffix:semicolon
DECL|member|interrupt
r_void
(paren
op_star
id|interrupt
)paren
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|status
)paren
suffix:semicolon
DECL|typedef|emu10k1_midi_t
)brace
id|emu10k1_midi_t
suffix:semicolon
DECL|struct|_snd_emu10k1
r_struct
id|_snd_emu10k1
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/* I/O port number */
DECL|member|res_port
r_struct
id|resource
op_star
id|res_port
suffix:semicolon
DECL|member|APS
r_int
id|APS
suffix:colon
l_int|1
comma
multiline_comment|/* APS flag */
DECL|member|tos_link
id|tos_link
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* tos link detected */
DECL|member|audigy
r_int
r_int
id|audigy
suffix:semicolon
multiline_comment|/* is Audigy? */
DECL|member|revision
r_int
r_int
id|revision
suffix:semicolon
multiline_comment|/* chip revision */
DECL|member|serial
r_int
r_int
id|serial
suffix:semicolon
multiline_comment|/* serial number */
DECL|member|model
r_int
r_int
id|model
suffix:semicolon
multiline_comment|/* subsystem id */
DECL|member|card_type
r_int
r_int
id|card_type
suffix:semicolon
multiline_comment|/* EMU10K1_CARD_* */
DECL|member|ecard_ctrl
r_int
r_int
id|ecard_ctrl
suffix:semicolon
multiline_comment|/* ecard control bits */
DECL|member|max_cache_pages
r_int
id|max_cache_pages
suffix:semicolon
multiline_comment|/* max memory size / PAGE_SIZE */
DECL|member|silent_page
r_void
op_star
id|silent_page
suffix:semicolon
multiline_comment|/* silent page */
DECL|member|silent_page_dmaaddr
id|dma_addr_t
id|silent_page_dmaaddr
suffix:semicolon
DECL|member|ptb_pages
r_volatile
r_int
r_int
op_star
id|ptb_pages
suffix:semicolon
multiline_comment|/* page table pages */
DECL|member|ptb_pages_dmaaddr
id|dma_addr_t
id|ptb_pages_dmaaddr
suffix:semicolon
DECL|member|memhdr
id|snd_util_memhdr_t
op_star
id|memhdr
suffix:semicolon
multiline_comment|/* page allocation list */
DECL|member|reserved_page
id|emu10k1_memblk_t
op_star
id|reserved_page
suffix:semicolon
multiline_comment|/* reserved page */
DECL|member|mapped_link_head
r_struct
id|list_head
id|mapped_link_head
suffix:semicolon
DECL|member|mapped_order_link_head
r_struct
id|list_head
id|mapped_order_link_head
suffix:semicolon
DECL|member|page_ptr_table
r_void
op_star
op_star
id|page_ptr_table
suffix:semicolon
DECL|member|page_addr_table
r_int
r_int
op_star
id|page_addr_table
suffix:semicolon
DECL|member|memblk_lock
id|spinlock_t
id|memblk_lock
suffix:semicolon
DECL|member|spdif_bits
r_int
r_int
id|spdif_bits
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* s/pdif out setup */
DECL|member|fx8010
id|snd_emu10k1_fx8010_t
id|fx8010
suffix:semicolon
multiline_comment|/* FX8010 info */
DECL|member|gpr_base
r_int
id|gpr_base
suffix:semicolon
DECL|member|ac97
id|ac97_t
op_star
id|ac97
suffix:semicolon
DECL|member|pci
r_struct
id|pci_dev
op_star
id|pci
suffix:semicolon
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|pcm
id|snd_pcm_t
op_star
id|pcm
suffix:semicolon
DECL|member|pcm_mic
id|snd_pcm_t
op_star
id|pcm_mic
suffix:semicolon
DECL|member|pcm_efx
id|snd_pcm_t
op_star
id|pcm_efx
suffix:semicolon
DECL|member|pcm_fx8010
id|snd_pcm_t
op_star
id|pcm_fx8010
suffix:semicolon
DECL|member|synth_lock
id|spinlock_t
id|synth_lock
suffix:semicolon
DECL|member|synth
r_void
op_star
id|synth
suffix:semicolon
DECL|member|get_synth_voice
r_int
(paren
op_star
id|get_synth_voice
)paren
(paren
id|emu10k1_t
op_star
id|emu
)paren
suffix:semicolon
DECL|member|reg_lock
id|spinlock_t
id|reg_lock
suffix:semicolon
DECL|member|emu_lock
id|spinlock_t
id|emu_lock
suffix:semicolon
DECL|member|voice_lock
id|spinlock_t
id|voice_lock
suffix:semicolon
DECL|member|ptb_lock
r_struct
id|semaphore
id|ptb_lock
suffix:semicolon
DECL|member|voices
id|emu10k1_voice_t
id|voices
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|pcm_mixer
id|emu10k1_pcm_mixer_t
id|pcm_mixer
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|hwvol_interrupt
r_void
(paren
op_star
id|hwvol_interrupt
)paren
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|status
)paren
suffix:semicolon
DECL|member|capture_interrupt
r_void
(paren
op_star
id|capture_interrupt
)paren
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|status
)paren
suffix:semicolon
DECL|member|capture_mic_interrupt
r_void
(paren
op_star
id|capture_mic_interrupt
)paren
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|status
)paren
suffix:semicolon
DECL|member|capture_efx_interrupt
r_void
(paren
op_star
id|capture_efx_interrupt
)paren
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|status
)paren
suffix:semicolon
DECL|member|timer_interrupt
r_void
(paren
op_star
id|timer_interrupt
)paren
(paren
id|emu10k1_t
op_star
id|emu
)paren
suffix:semicolon
DECL|member|spdif_interrupt
r_void
(paren
op_star
id|spdif_interrupt
)paren
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|status
)paren
suffix:semicolon
DECL|member|dsp_interrupt
r_void
(paren
op_star
id|dsp_interrupt
)paren
(paren
id|emu10k1_t
op_star
id|emu
)paren
suffix:semicolon
DECL|member|pcm_capture_substream
id|snd_pcm_substream_t
op_star
id|pcm_capture_substream
suffix:semicolon
DECL|member|pcm_capture_mic_substream
id|snd_pcm_substream_t
op_star
id|pcm_capture_mic_substream
suffix:semicolon
DECL|member|pcm_capture_efx_substream
id|snd_pcm_substream_t
op_star
id|pcm_capture_efx_substream
suffix:semicolon
DECL|member|midi
id|emu10k1_midi_t
id|midi
suffix:semicolon
DECL|member|midi2
id|emu10k1_midi_t
id|midi2
suffix:semicolon
multiline_comment|/* for audigy */
DECL|member|efx_voices_mask
r_int
r_int
id|efx_voices_mask
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|proc_entry
id|snd_info_entry_t
op_star
id|proc_entry
suffix:semicolon
DECL|member|proc_entry_fx8010_gpr
id|snd_info_entry_t
op_star
id|proc_entry_fx8010_gpr
suffix:semicolon
DECL|member|proc_entry_fx8010_tram_data
id|snd_info_entry_t
op_star
id|proc_entry_fx8010_tram_data
suffix:semicolon
DECL|member|proc_entry_fx8010_tram_addr
id|snd_info_entry_t
op_star
id|proc_entry_fx8010_tram_addr
suffix:semicolon
DECL|member|proc_entry_fx8010_code
id|snd_info_entry_t
op_star
id|proc_entry_fx8010_code
suffix:semicolon
DECL|member|proc_entry_fx8010_iblocks
id|snd_info_entry_t
op_star
id|proc_entry_fx8010_iblocks
suffix:semicolon
)brace
suffix:semicolon
r_int
id|snd_emu10k1_create
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_struct
id|pci_dev
op_star
id|pci
comma
r_int
r_int
id|extin_mask
comma
r_int
r_int
id|extout_mask
comma
r_int
id|max_cache_bytes
comma
r_int
id|enable_ir
comma
id|emu10k1_t
op_star
op_star
id|remu
)paren
suffix:semicolon
r_int
id|snd_emu10k1_pcm
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
id|device
comma
id|snd_pcm_t
op_star
op_star
id|rpcm
)paren
suffix:semicolon
r_int
id|snd_emu10k1_pcm_mic
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
id|device
comma
id|snd_pcm_t
op_star
op_star
id|rpcm
)paren
suffix:semicolon
r_int
id|snd_emu10k1_pcm_efx
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
id|device
comma
id|snd_pcm_t
op_star
op_star
id|rpcm
)paren
suffix:semicolon
r_int
id|snd_emu10k1_fx8010_pcm
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
id|device
comma
id|snd_pcm_t
op_star
op_star
id|rpcm
)paren
suffix:semicolon
r_int
id|snd_emu10k1_mixer
c_func
(paren
id|emu10k1_t
op_star
id|emu
)paren
suffix:semicolon
r_int
id|snd_emu10k1_fx8010_new
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
id|device
comma
id|snd_hwdep_t
op_star
op_star
id|rhwdep
)paren
suffix:semicolon
r_void
id|snd_emu10k1_interrupt
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
suffix:semicolon
multiline_comment|/* initialization */
r_void
id|snd_emu10k1_voice_init
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
id|voice
)paren
suffix:semicolon
r_int
id|snd_emu10k1_init_efx
c_func
(paren
id|emu10k1_t
op_star
id|emu
)paren
suffix:semicolon
r_void
id|snd_emu10k1_free_efx
c_func
(paren
id|emu10k1_t
op_star
id|emu
)paren
suffix:semicolon
r_int
id|snd_emu10k1_fx8010_tram_setup
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|u32
id|size
)paren
suffix:semicolon
multiline_comment|/* I/O functions */
r_int
r_int
id|snd_emu10k1_ptr_read
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|chn
)paren
suffix:semicolon
r_void
id|snd_emu10k1_ptr_write
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|reg
comma
r_int
r_int
id|chn
comma
r_int
r_int
id|data
)paren
suffix:semicolon
r_void
id|snd_emu10k1_efx_write
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|data
)paren
suffix:semicolon
r_int
r_int
id|snd_emu10k1_efx_read
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|pc
)paren
suffix:semicolon
r_void
id|snd_emu10k1_intr_enable
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|intrenb
)paren
suffix:semicolon
r_void
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|intrenb
)paren
suffix:semicolon
r_void
id|snd_emu10k1_voice_intr_enable
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|voicenum
)paren
suffix:semicolon
r_void
id|snd_emu10k1_voice_intr_disable
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|voicenum
)paren
suffix:semicolon
r_void
id|snd_emu10k1_voice_intr_ack
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|voicenum
)paren
suffix:semicolon
r_void
id|snd_emu10k1_voice_set_loop_stop
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|voicenum
)paren
suffix:semicolon
r_void
id|snd_emu10k1_voice_clear_loop_stop
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|voicenum
)paren
suffix:semicolon
r_void
id|snd_emu10k1_wait
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|wait
)paren
suffix:semicolon
DECL|function|snd_emu10k1_wc
r_static
r_inline
r_int
r_int
id|snd_emu10k1_wc
c_func
(paren
id|emu10k1_t
op_star
id|emu
)paren
(brace
r_return
(paren
id|inl
c_func
(paren
id|emu-&gt;port
op_plus
id|WC
)paren
op_rshift
l_int|6
)paren
op_amp
l_int|0xfffff
suffix:semicolon
)brace
r_int
r_int
id|snd_emu10k1_ac97_read
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
suffix:semicolon
r_void
id|snd_emu10k1_ac97_write
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
id|data
)paren
suffix:semicolon
r_int
r_int
id|snd_emu10k1_rate_to_pitch
c_func
(paren
r_int
r_int
id|rate
)paren
suffix:semicolon
r_int
r_char
id|snd_emu10k1_sum_vol_attn
c_func
(paren
r_int
r_int
id|value
)paren
suffix:semicolon
multiline_comment|/* memory allocation */
id|snd_util_memblk_t
op_star
id|snd_emu10k1_alloc_pages
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|dma_addr_t
id|addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_int
id|snd_emu10k1_free_pages
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|snd_util_memblk_t
op_star
id|blk
)paren
suffix:semicolon
id|snd_util_memblk_t
op_star
id|snd_emu10k1_synth_alloc
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_int
id|snd_emu10k1_synth_free
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|snd_util_memblk_t
op_star
id|blk
)paren
suffix:semicolon
r_int
id|snd_emu10k1_synth_bzero
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|snd_util_memblk_t
op_star
id|blk
comma
r_int
id|offset
comma
r_int
id|size
)paren
suffix:semicolon
r_int
id|snd_emu10k1_synth_copy_from_user
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|snd_util_memblk_t
op_star
id|blk
comma
r_int
id|offset
comma
r_const
r_char
op_star
id|data
comma
r_int
id|size
)paren
suffix:semicolon
r_int
id|snd_emu10k1_memblk_map
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_memblk_t
op_star
id|blk
)paren
suffix:semicolon
multiline_comment|/* voice allocation */
r_int
id|snd_emu10k1_voice_alloc
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_voice_type_t
id|type
comma
r_int
id|pair
comma
id|emu10k1_voice_t
op_star
op_star
id|rvoice
)paren
suffix:semicolon
r_int
id|snd_emu10k1_voice_free
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|emu10k1_voice_t
op_star
id|pvoice
)paren
suffix:semicolon
multiline_comment|/* MIDI uart */
r_int
id|snd_emu10k1_midi
c_func
(paren
id|emu10k1_t
op_star
id|emu
)paren
suffix:semicolon
r_int
id|snd_emu10k1_audigy_midi
c_func
(paren
id|emu10k1_t
op_star
id|emu
)paren
suffix:semicolon
multiline_comment|/* proc interface */
r_int
id|snd_emu10k1_proc_init
c_func
(paren
id|emu10k1_t
op_star
id|emu
)paren
suffix:semicolon
r_int
id|snd_emu10k1_proc_done
c_func
(paren
id|emu10k1_t
op_star
id|emu
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * ---- FX8010 ----&n; */
DECL|macro|EMU10K1_CARD_CREATIVE
mdefine_line|#define EMU10K1_CARD_CREATIVE&t;&t;&t;0x00000000
DECL|macro|EMU10K1_CARD_EMUAPS
mdefine_line|#define EMU10K1_CARD_EMUAPS&t;&t;&t;0x00000001
DECL|macro|EMU10K1_FX8010_PCM_COUNT
mdefine_line|#define EMU10K1_FX8010_PCM_COUNT&t;&t;8
multiline_comment|/* instruction set */
DECL|macro|iMAC0
mdefine_line|#define iMAC0&t; 0x00&t;/* R = A + (X * Y &gt;&gt; 31)   ; saturation */
DECL|macro|iMAC1
mdefine_line|#define iMAC1&t; 0x01&t;/* R = A + (-X * Y &gt;&gt; 31)  ; saturation */
DECL|macro|iMAC2
mdefine_line|#define iMAC2&t; 0x02&t;/* R = A + (X * Y &gt;&gt; 31)   ; wraparound */
DECL|macro|iMAC3
mdefine_line|#define iMAC3&t; 0x03&t;/* R = A + (-X * Y &gt;&gt; 31)  ; wraparound */
DECL|macro|iMACINT0
mdefine_line|#define iMACINT0 0x04&t;/* R = A + X * Y&t;   ; saturation */
DECL|macro|iMACINT1
mdefine_line|#define iMACINT1 0x05&t;/* R = A + X * Y&t;   ; wraparound (31-bit) */
DECL|macro|iACC3
mdefine_line|#define iACC3&t; 0x06&t;/* R = A + X + Y&t;   ; saturation */
DECL|macro|iMACMV
mdefine_line|#define iMACMV   0x07&t;/* R = A, acc += X * Y &gt;&gt; 31 */
DECL|macro|iANDXOR
mdefine_line|#define iANDXOR  0x08&t;/* R = (A &amp; X) ^ Y */
DECL|macro|iTSTNEG
mdefine_line|#define iTSTNEG  0x09&t;/* R = (A &gt;= Y) ? X : ~X */
DECL|macro|iLIMITGE
mdefine_line|#define iLIMITGE 0x0a&t;/* R = (A &gt;= Y) ? X : Y */
DECL|macro|iLIMITLT
mdefine_line|#define iLIMITLT 0x0b&t;/* R = (A &lt; Y) ? X : Y */
DECL|macro|iLOG
mdefine_line|#define iLOG&t; 0x0c&t;/* R = linear_data, A (log_data), X (max_exp), Y (format_word) */
DECL|macro|iEXP
mdefine_line|#define iEXP&t; 0x0d&t;/* R = log_data, A (linear_data), X (max_exp), Y (format_word) */
DECL|macro|iINTERP
mdefine_line|#define iINTERP  0x0e&t;/* R = A + (X * (Y - A) &gt;&gt; 31)  ; saturation */
DECL|macro|iSKIP
mdefine_line|#define iSKIP    0x0f&t;/* R = A (cc_reg), X (count), Y (cc_test) */
multiline_comment|/* GPRs */
DECL|macro|FXBUS
mdefine_line|#define FXBUS(x)&t;(0x00 + (x))&t;/* x = 0x00 - 0x0f */
DECL|macro|EXTIN
mdefine_line|#define EXTIN(x)&t;(0x10 + (x))&t;/* x = 0x00 - 0x0f */
DECL|macro|EXTOUT
mdefine_line|#define EXTOUT(x)&t;(0x20 + (x))&t;/* x = 0x00 - 0x0f */
DECL|macro|C_00000000
mdefine_line|#define C_00000000&t;0x40
DECL|macro|C_00000001
mdefine_line|#define C_00000001&t;0x41
DECL|macro|C_00000002
mdefine_line|#define C_00000002&t;0x42
DECL|macro|C_00000003
mdefine_line|#define C_00000003&t;0x43
DECL|macro|C_00000004
mdefine_line|#define C_00000004&t;0x44
DECL|macro|C_00000008
mdefine_line|#define C_00000008&t;0x45
DECL|macro|C_00000010
mdefine_line|#define C_00000010&t;0x46
DECL|macro|C_00000020
mdefine_line|#define C_00000020&t;0x47
DECL|macro|C_00000100
mdefine_line|#define C_00000100&t;0x48
DECL|macro|C_00010000
mdefine_line|#define C_00010000&t;0x49
DECL|macro|C_00080000
mdefine_line|#define C_00080000&t;0x4a
DECL|macro|C_10000000
mdefine_line|#define C_10000000&t;0x4b
DECL|macro|C_20000000
mdefine_line|#define C_20000000&t;0x4c
DECL|macro|C_40000000
mdefine_line|#define C_40000000&t;0x4d
DECL|macro|C_80000000
mdefine_line|#define C_80000000&t;0x4e
DECL|macro|C_7fffffff
mdefine_line|#define C_7fffffff&t;0x4f
DECL|macro|C_ffffffff
mdefine_line|#define C_ffffffff&t;0x50
DECL|macro|C_fffffffe
mdefine_line|#define C_fffffffe&t;0x51
DECL|macro|C_c0000000
mdefine_line|#define C_c0000000&t;0x52
DECL|macro|C_4f1bbcdc
mdefine_line|#define C_4f1bbcdc&t;0x53
DECL|macro|C_5a7ef9db
mdefine_line|#define C_5a7ef9db&t;0x54
DECL|macro|C_00100000
mdefine_line|#define C_00100000&t;0x55&t;&t;/* ?? */
DECL|macro|GPR_ACCU
mdefine_line|#define GPR_ACCU&t;0x56&t;&t;/* ACCUM, accumulator */
DECL|macro|GPR_COND
mdefine_line|#define GPR_COND&t;0x57&t;&t;/* CCR, condition register */
DECL|macro|GPR_NOISE0
mdefine_line|#define GPR_NOISE0&t;0x58&t;&t;/* noise source */
DECL|macro|GPR_NOISE1
mdefine_line|#define GPR_NOISE1&t;0x59&t;&t;/* noise source */
DECL|macro|GPR_IRQ
mdefine_line|#define GPR_IRQ&t;&t;0x5a&t;&t;/* IRQ register */
DECL|macro|GPR_DBAC
mdefine_line|#define GPR_DBAC&t;0x5b&t;&t;/* TRAM Delay Base Address Counter */
DECL|macro|GPR
mdefine_line|#define GPR(x)&t;&t;(FXGPREGBASE + (x)) /* free GPRs: x = 0x00 - 0xff */
DECL|macro|ITRAM_DATA
mdefine_line|#define ITRAM_DATA(x)&t;(TANKMEMDATAREGBASE + 0x00 + (x)) /* x = 0x00 - 0x7f */
DECL|macro|ETRAM_DATA
mdefine_line|#define ETRAM_DATA(x)&t;(TANKMEMDATAREGBASE + 0x80 + (x)) /* x = 0x00 - 0x1f */
DECL|macro|ITRAM_ADDR
mdefine_line|#define ITRAM_ADDR(x)&t;(TANKMEMADDRREGBASE + 0x00 + (x)) /* x = 0x00 - 0x7f */
DECL|macro|ETRAM_ADDR
mdefine_line|#define ETRAM_ADDR(x)&t;(TANKMEMADDRREGBASE + 0x80 + (x)) /* x = 0x00 - 0x1f */
DECL|macro|A_FXBUS
mdefine_line|#define A_FXBUS(x)&t;(0x00 + (x))&t;/* x = 0x00 - 0x3f? */
DECL|macro|A_EXTIN
mdefine_line|#define A_EXTIN(x)&t;(0x40 + (x))&t;/* x = 0x00 - 0x1f? */
DECL|macro|A_EXTOUT
mdefine_line|#define A_EXTOUT(x)&t;(0x60 + (x))&t;/* x = 0x00 - 0x1f? */
DECL|macro|A_GPR
mdefine_line|#define A_GPR(x)&t;(A_FXGPREGBASE + (x))
multiline_comment|/* cc_reg constants */
DECL|macro|CC_REG_NORMALIZED
mdefine_line|#define CC_REG_NORMALIZED C_00000001
DECL|macro|CC_REG_BORROW
mdefine_line|#define CC_REG_BORROW&t;C_00000002
DECL|macro|CC_REG_MINUS
mdefine_line|#define CC_REG_MINUS&t;C_00000004
DECL|macro|CC_REG_ZERO
mdefine_line|#define CC_REG_ZERO&t;C_00000008
DECL|macro|CC_REG_SATURATE
mdefine_line|#define CC_REG_SATURATE&t;C_00000010
DECL|macro|CC_REG_NONZERO
mdefine_line|#define CC_REG_NONZERO&t;C_00000100
multiline_comment|/* FX buses */
DECL|macro|FXBUS_PCM_LEFT
mdefine_line|#define FXBUS_PCM_LEFT&t;&t;0x00
DECL|macro|FXBUS_PCM_RIGHT
mdefine_line|#define FXBUS_PCM_RIGHT&t;&t;0x01
DECL|macro|FXBUS_PCM_LEFT_REAR
mdefine_line|#define FXBUS_PCM_LEFT_REAR&t;0x02
DECL|macro|FXBUS_PCM_RIGHT_REAR
mdefine_line|#define FXBUS_PCM_RIGHT_REAR&t;0x03
DECL|macro|FXBUS_MIDI_LEFT
mdefine_line|#define FXBUS_MIDI_LEFT&t;&t;0x04
DECL|macro|FXBUS_MIDI_RIGHT
mdefine_line|#define FXBUS_MIDI_RIGHT&t;0x05
DECL|macro|FXBUS_PCM_CENTER
mdefine_line|#define FXBUS_PCM_CENTER&t;0x06
DECL|macro|FXBUS_PCM_LFE
mdefine_line|#define FXBUS_PCM_LFE&t;&t;0x07
DECL|macro|FXBUS_MIDI_REVERB
mdefine_line|#define FXBUS_MIDI_REVERB&t;0x0c
DECL|macro|FXBUS_MIDI_CHORUS
mdefine_line|#define FXBUS_MIDI_CHORUS&t;0x0d
multiline_comment|/* Inputs */
DECL|macro|EXTIN_AC97_L
mdefine_line|#define EXTIN_AC97_L&t;   0x00&t;/* AC&squot;97 capture channel - left */
DECL|macro|EXTIN_AC97_R
mdefine_line|#define EXTIN_AC97_R&t;   0x01&t;/* AC&squot;97 capture channel - right */
DECL|macro|EXTIN_SPDIF_CD_L
mdefine_line|#define EXTIN_SPDIF_CD_L   0x02&t;/* internal S/PDIF CD - onboard - left */
DECL|macro|EXTIN_SPDIF_CD_R
mdefine_line|#define EXTIN_SPDIF_CD_R   0x03&t;/* internal S/PDIF CD - onboard - right */
DECL|macro|EXTIN_ZOOM_L
mdefine_line|#define EXTIN_ZOOM_L&t;   0x04&t;/* Zoom Video I2S - left */
DECL|macro|EXTIN_ZOOM_R
mdefine_line|#define EXTIN_ZOOM_R&t;   0x05&t;/* Zoom Video I2S - right */
DECL|macro|EXTIN_TOSLINK_L
mdefine_line|#define EXTIN_TOSLINK_L&t;   0x06&t;/* LiveDrive - TOSLink Optical - left */
DECL|macro|EXTIN_TOSLINK_R
mdefine_line|#define EXTIN_TOSLINK_R    0x07&t;/* LiveDrive - TOSLink Optical - right */
DECL|macro|EXTIN_LINE1_L
mdefine_line|#define EXTIN_LINE1_L&t;   0x08&t;/* LiveDrive - Line/Mic 1 - left */
DECL|macro|EXTIN_LINE1_R
mdefine_line|#define EXTIN_LINE1_R&t;   0x09&t;/* LiveDrive - Line/Mic 1 - right */
DECL|macro|EXTIN_COAX_SPDIF_L
mdefine_line|#define EXTIN_COAX_SPDIF_L 0x0a&t;/* LiveDrive - Coaxial S/PDIF - left */
DECL|macro|EXTIN_COAX_SPDIF_R
mdefine_line|#define EXTIN_COAX_SPDIF_R 0x0b /* LiveDrive - Coaxial S/PDIF - right */
DECL|macro|EXTIN_LINE2_L
mdefine_line|#define EXTIN_LINE2_L&t;   0x0c&t;/* LiveDrive - Line/Mic 2 - left */
DECL|macro|EXTIN_LINE2_R
mdefine_line|#define EXTIN_LINE2_R&t;   0x0d&t;/* LiveDrive - Line/Mic 2 - right */
multiline_comment|/* Outputs */
DECL|macro|EXTOUT_AC97_L
mdefine_line|#define EXTOUT_AC97_L&t;   0x00&t;/* AC&squot;97 playback channel - left */
DECL|macro|EXTOUT_AC97_R
mdefine_line|#define EXTOUT_AC97_R&t;   0x01&t;/* AC&squot;97 playback channel - right */
DECL|macro|EXTOUT_TOSLINK_L
mdefine_line|#define EXTOUT_TOSLINK_L   0x02&t;/* LiveDrive - TOSLink Optical - left */
DECL|macro|EXTOUT_TOSLINK_R
mdefine_line|#define EXTOUT_TOSLINK_R   0x03&t;/* LiveDrive - TOSLink Optical - right */
DECL|macro|EXTOUT_CENTER
mdefine_line|#define EXTOUT_CENTER      0x04&t;/* SB Live 5.1 - center */
DECL|macro|EXTOUT_LFE
mdefine_line|#define EXTOUT_LFE         0x05 /* SB Live 5.1 - LFE */
DECL|macro|EXTOUT_HEADPHONE_L
mdefine_line|#define EXTOUT_HEADPHONE_L 0x06&t;/* LiveDrive - Headphone - left */
DECL|macro|EXTOUT_HEADPHONE_R
mdefine_line|#define EXTOUT_HEADPHONE_R 0x07&t;/* LiveDrive - Headphone - right */
DECL|macro|EXTOUT_REAR_L
mdefine_line|#define EXTOUT_REAR_L&t;   0x08&t;/* Rear channel - left */
DECL|macro|EXTOUT_REAR_R
mdefine_line|#define EXTOUT_REAR_R&t;   0x09&t;/* Rear channel - right */
DECL|macro|EXTOUT_ADC_CAP_L
mdefine_line|#define EXTOUT_ADC_CAP_L   0x0a&t;/* ADC Capture buffer - left */
DECL|macro|EXTOUT_ADC_CAP_R
mdefine_line|#define EXTOUT_ADC_CAP_R   0x0b&t;/* ADC Capture buffer - right */
DECL|macro|EXTOUT_MIC_CAP
mdefine_line|#define EXTOUT_MIC_CAP&t;   0x0c&t;/* MIC Capture buffer */
DECL|macro|EXTOUT_ACENTER
mdefine_line|#define EXTOUT_ACENTER&t;   0x11 /* Analog Center */
DECL|macro|EXTOUT_ALFE
mdefine_line|#define EXTOUT_ALFE&t;   0x12 /* Analog LFE */
multiline_comment|/* Audigy Inputs */
DECL|macro|A_EXTIN_AC97_L
mdefine_line|#define A_EXTIN_AC97_L&t;&t;0x00&t;/* AC&squot;97 capture channel - left */
DECL|macro|A_EXTIN_AC97_R
mdefine_line|#define A_EXTIN_AC97_R&t;&t;0x01&t;/* AC&squot;97 capture channel - right */
DECL|macro|A_EXTIN_SPDIF_CD_L
mdefine_line|#define A_EXTIN_SPDIF_CD_L&t;0x02&t;/* digital CD left */
DECL|macro|A_EXTIN_SPDIF_CD_R
mdefine_line|#define A_EXTIN_SPDIF_CD_R&t;0x03&t;/* digital CD left */
DECL|macro|A_EXTIN_LINE2_L
mdefine_line|#define A_EXTIN_LINE2_L&t;&t;0x08&t;/* audigy drive line2/mic2 - left */
DECL|macro|A_EXTIN_LINE2_R
mdefine_line|#define A_EXTIN_LINE2_R&t;&t;0x09&t;/*                           right */
DECL|macro|A_EXTIN_AUX2_L
mdefine_line|#define A_EXTIN_AUX2_L&t;&t;0x0c&t;/* audigy drive aux2 - left */
DECL|macro|A_EXTIN_AUX2_R
mdefine_line|#define A_EXTIN_AUX2_R&t;&t;0x0d&t;/*                   - right */
multiline_comment|/* Audigiy Outputs */
DECL|macro|A_EXTOUT_FRONT_L
mdefine_line|#define A_EXTOUT_FRONT_L&t;0x00&t;/* digital front left */
DECL|macro|A_EXTOUT_FRONT_R
mdefine_line|#define A_EXTOUT_FRONT_R&t;0x01&t;/*               right */
DECL|macro|A_EXTOUT_CENTER
mdefine_line|#define A_EXTOUT_CENTER&t;&t;0x02&t;/* digital front center */
DECL|macro|A_EXTOUT_LFE
mdefine_line|#define A_EXTOUT_LFE&t;&t;0x03&t;/* digital front lfe */
DECL|macro|A_EXTOUT_HEADPHONE_L
mdefine_line|#define A_EXTOUT_HEADPHONE_L&t;0x04&t;/* headphone audigy drive left */
DECL|macro|A_EXTOUT_HEADPHONE_R
mdefine_line|#define A_EXTOUT_HEADPHONE_R&t;0x05&t;/*                        right */
DECL|macro|A_EXTOUT_REAR_L
mdefine_line|#define A_EXTOUT_REAR_L&t;&t;0x06&t;/* digital rear left */
DECL|macro|A_EXTOUT_REAR_R
mdefine_line|#define A_EXTOUT_REAR_R&t;&t;0x07&t;/*              right */
DECL|macro|A_EXTOUT_AFRONT_L
mdefine_line|#define A_EXTOUT_AFRONT_L&t;0x08&t;/* analog front left */
DECL|macro|A_EXTOUT_AFRONT_R
mdefine_line|#define A_EXTOUT_AFRONT_R&t;0x09&t;/*              right */
DECL|macro|A_EXTOUT_ACENTER
mdefine_line|#define A_EXTOUT_ACENTER&t;0x0a&t;/* analog center */
DECL|macro|A_EXTOUT_ALFE
mdefine_line|#define A_EXTOUT_ALFE&t;&t;0x0b&t;/* analog LFE */
multiline_comment|/* 0x0c ?? */
multiline_comment|/* 0x0d ?? */
DECL|macro|A_EXTOUT_AREAR_L
mdefine_line|#define A_EXTOUT_AREAR_L&t;0x0e&t;/* analog rear left */
DECL|macro|A_EXTOUT_AREAR_R
mdefine_line|#define A_EXTOUT_AREAR_R&t;0x0f&t;/*             right */
DECL|macro|A_EXTOUT_AC97_L
mdefine_line|#define A_EXTOUT_AC97_L&t;&t;0x10&t;/* AC97 left (front) */
DECL|macro|A_EXTOUT_AC97_R
mdefine_line|#define A_EXTOUT_AC97_R&t;&t;0x11&t;/*      right */
DECL|macro|A_EXTOUT_ADC_CAP_L
mdefine_line|#define A_EXTOUT_ADC_CAP_L&t;0x16&t;/* ADC capture buffer left */
DECL|macro|A_EXTOUT_ADC_CAP_R
mdefine_line|#define A_EXTOUT_ADC_CAP_R&t;0x17&t;/*                    right */
multiline_comment|/* Audigy constants */
DECL|macro|A_C_00000000
mdefine_line|#define A_C_00000000&t;0xc0
DECL|macro|A_C_00000001
mdefine_line|#define A_C_00000001&t;0xc1
DECL|macro|A_C_00000002
mdefine_line|#define A_C_00000002&t;0xc2
DECL|macro|A_C_00000003
mdefine_line|#define A_C_00000003&t;0xc3
DECL|macro|A_C_00000004
mdefine_line|#define A_C_00000004&t;0xc4
DECL|macro|A_C_00000008
mdefine_line|#define A_C_00000008&t;0xc5
DECL|macro|A_C_00000010
mdefine_line|#define A_C_00000010&t;0xc6
DECL|macro|A_C_00000020
mdefine_line|#define A_C_00000020&t;0xc7
DECL|macro|A_C_00000100
mdefine_line|#define A_C_00000100&t;0xc8
DECL|macro|A_C_00010000
mdefine_line|#define A_C_00010000&t;0xc9
DECL|macro|A_C_00000800
mdefine_line|#define A_C_00000800&t;0xca
DECL|macro|A_C_10000000
mdefine_line|#define A_C_10000000&t;0xcb
DECL|macro|A_C_20000000
mdefine_line|#define A_C_20000000&t;0xcc
DECL|macro|A_C_40000000
mdefine_line|#define A_C_40000000&t;0xcd
DECL|macro|A_C_80000000
mdefine_line|#define A_C_80000000&t;0xce
DECL|macro|A_C_7fffffff
mdefine_line|#define A_C_7fffffff&t;0xcf
DECL|macro|A_C_ffffffff
mdefine_line|#define A_C_ffffffff&t;0xd0
DECL|macro|A_C_fffffffe
mdefine_line|#define A_C_fffffffe&t;0xd1
DECL|macro|A_C_c0000000
mdefine_line|#define A_C_c0000000&t;0xd2
DECL|macro|A_C_4f1bbcdc
mdefine_line|#define A_C_4f1bbcdc&t;0xd3
DECL|macro|A_C_5a7ef9db
mdefine_line|#define A_C_5a7ef9db&t;0xd4
DECL|macro|A_C_00100000
mdefine_line|#define A_C_00100000&t;0xd5
multiline_comment|/* 0xd6 = 0x7fffffff  (?) ACCUM? */
multiline_comment|/* 0xd7 = 0x0000000   CCR */
multiline_comment|/* 0xd8 = noise1 */
multiline_comment|/* 0xd9 = noise2 */
multiline_comment|/* definitions for debug register */
DECL|macro|EMU10K1_DBG_ZC
mdefine_line|#define EMU10K1_DBG_ZC&t;&t;&t;0x80000000&t;/* zero tram counter */
DECL|macro|EMU10K1_DBG_SATURATION_OCCURED
mdefine_line|#define EMU10K1_DBG_SATURATION_OCCURED&t;0x02000000&t;/* saturation control */
DECL|macro|EMU10K1_DBG_SATURATION_ADDR
mdefine_line|#define EMU10K1_DBG_SATURATION_ADDR&t;0x01ff0000&t;/* saturation address */
DECL|macro|EMU10K1_DBG_SINGLE_STEP
mdefine_line|#define EMU10K1_DBG_SINGLE_STEP&t;&t;0x00008000&t;/* single step mode */
DECL|macro|EMU10K1_DBG_STEP
mdefine_line|#define EMU10K1_DBG_STEP&t;&t;0x00004000&t;/* start single step */
DECL|macro|EMU10K1_DBG_CONDITION_CODE
mdefine_line|#define EMU10K1_DBG_CONDITION_CODE&t;0x00003e00&t;/* condition code */
DECL|macro|EMU10K1_DBG_SINGLE_STEP_ADDR
mdefine_line|#define EMU10K1_DBG_SINGLE_STEP_ADDR&t;0x000001ff&t;/* single step address */
multiline_comment|/* tank memory address line */
macro_line|#ifndef __KERNEL__
DECL|macro|TANKMEMADDRREG_ADDR_MASK
mdefine_line|#define TANKMEMADDRREG_ADDR_MASK 0x000fffff&t;/* 20 bit tank address field&t;&t;&t;*/
DECL|macro|TANKMEMADDRREG_CLEAR
mdefine_line|#define TANKMEMADDRREG_CLEAR&t; 0x00800000&t;/* Clear tank memory&t;&t;&t;&t;*/
DECL|macro|TANKMEMADDRREG_ALIGN
mdefine_line|#define TANKMEMADDRREG_ALIGN&t; 0x00400000&t;/* Align read or write relative to tank access&t;*/
DECL|macro|TANKMEMADDRREG_WRITE
mdefine_line|#define TANKMEMADDRREG_WRITE&t; 0x00200000&t;/* Write to tank memory&t;&t;&t;&t;*/
DECL|macro|TANKMEMADDRREG_READ
mdefine_line|#define TANKMEMADDRREG_READ&t; 0x00100000&t;/* Read from tank memory&t;&t;&t;*/
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|card
r_int
r_int
id|card
suffix:semicolon
multiline_comment|/* card type */
DECL|member|internal_tram_size
r_int
r_int
id|internal_tram_size
suffix:semicolon
multiline_comment|/* in samples */
DECL|member|external_tram_size
r_int
r_int
id|external_tram_size
suffix:semicolon
multiline_comment|/* in samples */
DECL|member|fxbus_names
r_char
id|fxbus_names
(braket
l_int|16
)braket
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* names of FXBUSes */
DECL|member|extin_names
r_char
id|extin_names
(braket
l_int|16
)braket
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* names of external inputs */
DECL|member|extout_names
r_char
id|extout_names
(braket
l_int|32
)braket
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* names of external outputs */
DECL|member|gpr_controls
r_int
r_int
id|gpr_controls
suffix:semicolon
multiline_comment|/* count of GPR controls */
DECL|typedef|emu10k1_fx8010_info_t
)brace
id|emu10k1_fx8010_info_t
suffix:semicolon
DECL|macro|EMU10K1_GPR_TRANSLATION_NONE
mdefine_line|#define EMU10K1_GPR_TRANSLATION_NONE&t;&t;0
DECL|macro|EMU10K1_GPR_TRANSLATION_TABLE100
mdefine_line|#define EMU10K1_GPR_TRANSLATION_TABLE100&t;1
DECL|macro|EMU10K1_GRP_TRANSLATION_BASS
mdefine_line|#define EMU10K1_GRP_TRANSLATION_BASS&t;&t;2
DECL|macro|EMU10K1_GRP_TRANSLATION_TREBLE
mdefine_line|#define EMU10K1_GRP_TRANSLATION_TREBLE&t;&t;3
DECL|macro|EMU10K1_GPR_TRANSLATION_ONOFF
mdefine_line|#define EMU10K1_GPR_TRANSLATION_ONOFF&t;&t;4
r_typedef
r_struct
(brace
DECL|member|id
id|snd_ctl_elem_id_t
id|id
suffix:semicolon
multiline_comment|/* full control ID definition */
DECL|member|vcount
r_int
r_int
id|vcount
suffix:semicolon
multiline_comment|/* visible count */
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* count of GPR (1..16) */
DECL|member|gpr
r_int
r_char
id|gpr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* GPR number(s) */
DECL|member|value
r_int
r_int
id|value
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* initial values */
DECL|member|min
r_int
r_int
id|min
suffix:semicolon
multiline_comment|/* minimum range */
DECL|member|max
r_int
r_int
id|max
suffix:semicolon
multiline_comment|/* maximum range */
DECL|member|translation
r_int
r_int
id|translation
suffix:semicolon
multiline_comment|/* translation type (EMU10K1_GRP_TRANSLATION*) */
DECL|typedef|emu10k1_fx8010_control_gpr_t
)brace
id|emu10k1_fx8010_control_gpr_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|name
r_char
id|name
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|gpr_valid
r_int
r_int
id|gpr_valid
(braket
l_int|0x100
op_div
l_int|32
)braket
suffix:semicolon
multiline_comment|/* bitmask of valid initializers */
DECL|member|gpr_map
r_int
r_int
id|gpr_map
(braket
l_int|0x100
)braket
suffix:semicolon
multiline_comment|/* initializers */
DECL|member|gpr_add_control_count
r_int
r_int
id|gpr_add_control_count
suffix:semicolon
multiline_comment|/* count of GPR controls to add/replace */
DECL|member|gpr_add_controls
id|emu10k1_fx8010_control_gpr_t
op_star
id|gpr_add_controls
suffix:semicolon
multiline_comment|/* GPR controls to add/replace */
DECL|member|gpr_del_control_count
r_int
r_int
id|gpr_del_control_count
suffix:semicolon
multiline_comment|/* count of GPR controls to remove */
DECL|member|gpr_del_controls
id|snd_ctl_elem_id_t
op_star
id|gpr_del_controls
suffix:semicolon
multiline_comment|/* IDs of GPR controls to remove */
DECL|member|tram_valid
r_int
r_int
id|tram_valid
(braket
l_int|0xa0
op_div
l_int|32
)braket
suffix:semicolon
multiline_comment|/* bitmask of valid initializers */
DECL|member|tram_data_map
r_int
r_int
id|tram_data_map
(braket
l_int|0xa0
)braket
suffix:semicolon
multiline_comment|/* data initializers */
DECL|member|tram_addr_map
r_int
r_int
id|tram_addr_map
(braket
l_int|0xa0
)braket
suffix:semicolon
multiline_comment|/* map initializers */
DECL|member|code_valid
r_int
r_int
id|code_valid
(braket
l_int|512
op_div
l_int|32
)braket
suffix:semicolon
multiline_comment|/* bitmask of valid instructions */
DECL|member|code
r_int
r_int
id|code
(braket
l_int|512
)braket
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* one instruction - 64 bits */
DECL|typedef|emu10k1_fx8010_code_t
)brace
id|emu10k1_fx8010_code_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
multiline_comment|/* 31.bit == 1 -&gt; external TRAM */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size in samples (4 bytes) */
DECL|member|samples
r_int
r_int
op_star
id|samples
suffix:semicolon
multiline_comment|/* pointer to samples (20-bit) */
multiline_comment|/* NULL-&gt;clear memory */
DECL|typedef|emu10k1_fx8010_tram_t
)brace
id|emu10k1_fx8010_tram_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|substream
r_int
r_int
id|substream
suffix:semicolon
multiline_comment|/* substream number */
DECL|member|res1
r_int
r_int
id|res1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|channels
r_int
r_int
id|channels
suffix:semicolon
multiline_comment|/* 16-bit channels count, zero = remove this substream */
DECL|member|tram_start
r_int
r_int
id|tram_start
suffix:semicolon
multiline_comment|/* ring buffer position in TRAM (in samples) */
DECL|member|buffer_size
r_int
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* count of buffered samples */
DECL|member|gpr_size
r_int
r_char
id|gpr_size
suffix:semicolon
multiline_comment|/* GPR containing size of ringbuffer in samples (host) */
DECL|member|gpr_ptr
r_int
r_char
id|gpr_ptr
suffix:semicolon
multiline_comment|/* GPR containing current pointer in the ring buffer (host = reset, FX8010) */
DECL|member|gpr_count
r_int
r_char
id|gpr_count
suffix:semicolon
multiline_comment|/* GPR containing count of samples between two interrupts (host) */
DECL|member|gpr_tmpcount
r_int
r_char
id|gpr_tmpcount
suffix:semicolon
multiline_comment|/* GPR containing current count of samples to interrupt (host = set, FX8010) */
DECL|member|gpr_trigger
r_int
r_char
id|gpr_trigger
suffix:semicolon
multiline_comment|/* GPR containing trigger (activate) information (host) */
DECL|member|gpr_running
r_int
r_char
id|gpr_running
suffix:semicolon
multiline_comment|/* GPR containing info if PCM is running (FX8010) */
DECL|member|pad
r_int
r_char
id|pad
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|etram
r_int
r_char
id|etram
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* external TRAM address &amp; data (one per channel) */
DECL|member|res2
r_int
r_int
id|res2
suffix:semicolon
multiline_comment|/* reserved */
DECL|typedef|emu10k1_fx8010_pcm_t
)brace
id|emu10k1_fx8010_pcm_t
suffix:semicolon
DECL|macro|SNDRV_EMU10K1_IOCTL_INFO
mdefine_line|#define SNDRV_EMU10K1_IOCTL_INFO&t;_IOR (&squot;H&squot;, 0x10, emu10k1_fx8010_info_t)
DECL|macro|SNDRV_EMU10K1_IOCTL_CODE_POKE
mdefine_line|#define SNDRV_EMU10K1_IOCTL_CODE_POKE&t;_IOW (&squot;H&squot;, 0x11, emu10k1_fx8010_code_t)
DECL|macro|SNDRV_EMU10K1_IOCTL_CODE_PEEK
mdefine_line|#define SNDRV_EMU10K1_IOCTL_CODE_PEEK&t;_IOW (&squot;H&squot;, 0x12, emu10k1_fx8010_code_t)
DECL|macro|SNDRV_EMU10K1_IOCTL_TRAM_SETUP
mdefine_line|#define SNDRV_EMU10K1_IOCTL_TRAM_SETUP&t;_IOW (&squot;H&squot;, 0x20, int)
DECL|macro|SNDRV_EMU10K1_IOCTL_TRAM_POKE
mdefine_line|#define SNDRV_EMU10K1_IOCTL_TRAM_POKE&t;_IOW (&squot;H&squot;, 0x21, emu10k1_fx8010_tram_t)
DECL|macro|SNDRV_EMU10K1_IOCTL_TRAM_PEEK
mdefine_line|#define SNDRV_EMU10K1_IOCTL_TRAM_PEEK&t;_IOR (&squot;H&squot;, 0x22, emu10k1_fx8010_tram_t)
DECL|macro|SNDRV_EMU10K1_IOCTL_PCM_POKE
mdefine_line|#define SNDRV_EMU10K1_IOCTL_PCM_POKE&t;_IOW (&squot;H&squot;, 0x30, emu10k1_fx8010_pcm_t)
DECL|macro|SNDRV_EMU10K1_IOCTL_PCM_PEEK
mdefine_line|#define SNDRV_EMU10K1_IOCTL_PCM_PEEK&t;_IOWR(&squot;H&squot;, 0x31, emu10k1_fx8010_pcm_t)
DECL|macro|SNDRV_EMU10K1_IOCTL_STOP
mdefine_line|#define SNDRV_EMU10K1_IOCTL_STOP&t;_IO  (&squot;H&squot;, 0x80)
DECL|macro|SNDRV_EMU10K1_IOCTL_CONTINUE
mdefine_line|#define SNDRV_EMU10K1_IOCTL_CONTINUE&t;_IO  (&squot;H&squot;, 0x81)
DECL|macro|SNDRV_EMU10K1_IOCTL_ZERO_TRAM_COUNTER
mdefine_line|#define SNDRV_EMU10K1_IOCTL_ZERO_TRAM_COUNTER _IO (&squot;H&squot;, 0x82)
DECL|macro|SNDRV_EMU10K1_IOCTL_SINGLE_STEP
mdefine_line|#define SNDRV_EMU10K1_IOCTL_SINGLE_STEP&t;_IOW (&squot;H&squot;, 0x83, int)
DECL|macro|SNDRV_EMU10K1_IOCTL_DBG_READ
mdefine_line|#define SNDRV_EMU10K1_IOCTL_DBG_READ&t;_IOR (&squot;H&squot;, 0x84, int)
macro_line|#endif&t;/* __SOUND_EMU10K1_H */
eof
