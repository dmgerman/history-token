multiline_comment|/*&n; **********************************************************************&n; *     irq.h&n; *     Copyright 1999, 2000 Creative Labs, Inc.&n; *&n; **********************************************************************&n; *&n; *     Date                 Author          Summary of changes&n; *     ----                 ------          ------------------&n; *     October 20, 1999     Bertrand Lee    base code release&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
macro_line|#ifndef _IRQ_H
DECL|macro|_IRQ_H
mdefine_line|#define _IRQ_H
multiline_comment|/* EMU Irq Types */
DECL|macro|IRQTYPE_PCIBUSERROR
mdefine_line|#define IRQTYPE_PCIBUSERROR&t;IPR_PCIERROR
DECL|macro|IRQTYPE_MIXERBUTTON
mdefine_line|#define IRQTYPE_MIXERBUTTON&t;(IPR_VOLINCR | IPR_VOLDECR | IPR_MUTE)
DECL|macro|IRQTYPE_VOICE
mdefine_line|#define IRQTYPE_VOICE&t;&t;(IPR_CHANNELLOOP | IPR_CHANNELNUMBERMASK)
DECL|macro|IRQTYPE_RECORD
mdefine_line|#define IRQTYPE_RECORD&t;&t;(IPR_ADCBUFFULL | IPR_ADCBUFHALFFULL | IPR_MICBUFFULL | IPR_MICBUFHALFFULL | IPR_EFXBUFFULL | IPR_EFXBUFHALFFULL)
DECL|macro|IRQTYPE_MPUOUT
mdefine_line|#define IRQTYPE_MPUOUT&t;&t;(IPR_MIDITRANSBUFEMPTY | A_IPR_MIDITRANSBUFEMPTY2) 
DECL|macro|IRQTYPE_MPUIN
mdefine_line|#define IRQTYPE_MPUIN&t;&t;(IPR_MIDIRECVBUFEMPTY | A_IPR_MIDIRECVBUFEMPTY2)
DECL|macro|IRQTYPE_TIMER
mdefine_line|#define IRQTYPE_TIMER&t;&t;IPR_INTERVALTIMER
DECL|macro|IRQTYPE_SPDIF
mdefine_line|#define IRQTYPE_SPDIF&t;&t;(IPR_GPSPDIFSTATUSCHANGE | IPR_CDROMSTATUSCHANGE)
DECL|macro|IRQTYPE_DSP
mdefine_line|#define IRQTYPE_DSP&t;&t;IPR_FXDSP
r_void
id|emu10k1_timer_irqhandler
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_dsp_irqhandler
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_mute_irqhandler
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_volincr_irqhandler
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_voldecr_irqhandler
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
macro_line|#endif /* _IRQ_H */
eof
