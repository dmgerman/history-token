multiline_comment|/*&n; **********************************************************************&n; *     8010.h&n; *     Copyright 1999, 2000 Creative Labs, Inc.&n; *&n; **********************************************************************&n; *&n; *     Date&t;&t;    Author&t;    Summary of changes&n; *     ----&t;&t;    ------&t;    ------------------&n; *     October 20, 1999     Bertrand Lee    base code release&n; *     November 2, 1999     Alan Cox&t;    Cleaned of 8bit chars, DOS&n; *&t;&t;&t;&t;&t;    line endings&n; *     December 8, 1999     Jon Taylor&t;    Added lots of new register info&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; *&n; **********************************************************************&n; */
macro_line|#ifndef _8010_H
DECL|macro|_8010_H
mdefine_line|#define _8010_H
macro_line|#include &lt;linux/types.h&gt;
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
DECL|macro|DATA
mdefine_line|#define DATA&t;&t;&t;0x04&t;&t;/* Indexed register set data register&t;&t;*/
DECL|macro|IPR
mdefine_line|#define IPR&t;&t;&t;0x08&t;&t;/* Global interrupt pending register&t;&t;*/
multiline_comment|/* Clear pending interrupts by writing a 1 to&t;*/
multiline_comment|/* the relevant bits and zero to the other bits&t;*/
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
mdefine_line|#define HCFG_GPOUT0&t;&t;0x00001000&t;/* set to enable digital out on 5.1 cards&t;*/
DECL|macro|HCFG_JOYENABLE
mdefine_line|#define HCFG_JOYENABLE      &t;0x00000200&t;/* Internal joystick enable    &t;&t;&t;*/
DECL|macro|HCFG_PHASETRACKENABLE
mdefine_line|#define HCFG_PHASETRACKENABLE&t;0x00000100&t;/* Phase tracking enable&t;&t;&t;*/
multiline_comment|/* 1 = Force all 3 async digital inputs to use&t;*/
multiline_comment|/* the same async sample rate tracker (ZVIDEO)&t;*/
DECL|macro|HCFG_AC3ENABLE_MASK
mdefine_line|#define HCFG_AC3ENABLE_MASK&t;0x0x0000e0&t;/* AC3 async input control - Not implemented&t;*/
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
DECL|macro|VTFT_FILTERTARGET_MASK
mdefine_line|#define VTFT_FILTERTARGET_MASK&t;0x0000ffff&t;/* Filter cutoff target of specified channel&t;&t;*/
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
DECL|macro|FXWC
mdefine_line|#define FXWC&t;&t;&t;0x43&t;&t;/* FX output write channels register&t;&t;&t;*/
multiline_comment|/* When set, each bit enables the writing of the&t;*/
multiline_comment|/* corresponding FX output channel into host memory&t;*/
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
multiline_comment|/* definitions for debug register - taken from the alsa drivers */
DECL|macro|DBG_ZC
mdefine_line|#define DBG_ZC                  0x80000000      /* zero tram counter */
DECL|macro|DBG_SATURATION_OCCURED
mdefine_line|#define DBG_SATURATION_OCCURED  0x02000000      /* saturation control */
DECL|macro|DBG_SATURATION_ADDR
mdefine_line|#define DBG_SATURATION_ADDR     0x01ff0000      /* saturation address */
DECL|macro|DBG_SINGLE_STEP
mdefine_line|#define DBG_SINGLE_STEP         0x00008000      /* single step mode */
DECL|macro|DBG_STEP
mdefine_line|#define DBG_STEP                0x00004000      /* start single step */
DECL|macro|DBG_CONDITION_CODE
mdefine_line|#define DBG_CONDITION_CODE      0x00003e00      /* condition code */
DECL|macro|DBG_SINGLE_STEP_ADDR
mdefine_line|#define DBG_SINGLE_STEP_ADDR    0x000001ff      /* single step address */
DECL|macro|REG53
mdefine_line|#define REG53&t;&t;&t;0x53&t;&t;/* DO NOT PROGRAM THIS REGISTER!!! MAY DESTROY CHIP */
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
mdefine_line|#define AC97SLOT&t;&t;0x5f&t;&t;/* additional AC97 slots enable bits */
DECL|macro|AC97SLOT_CNTR
mdefine_line|#define AC97SLOT_CNTR&t;&t;0x10&t;&t;/* Center enable */
DECL|macro|AC97SLOT_LFE
mdefine_line|#define AC97SLOT_LFE&t;&t;0x20&t;&t;/* LFE enable */
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
DECL|macro|FXIDX
mdefine_line|#define FXIDX&t;&t;&t;0x65&t;&t;/* FX recording buffer index register&t;&t;*/
DECL|macro|FXIDX_MASK
mdefine_line|#define FXIDX_MASK&t;&t;0x0000ffff&t;/* 16-bit value&t;&t;&t;&t;&t;*/
DECL|macro|FXIDX_IDX
mdefine_line|#define FXIDX_IDX&t;&t;0x10000065
multiline_comment|/* Each FX general purpose register is 32 bits in length, all bits are used&t;&t;&t;*/
DECL|macro|FXGPREGBASE
mdefine_line|#define FXGPREGBASE&t;&t;0x100&t;&t;/* FX general purpose registers base       &t;*/
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
macro_line|#endif /* _8010_H */
eof
