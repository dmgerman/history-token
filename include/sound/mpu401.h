macro_line|#ifndef __SOUND_MPU401_H
DECL|macro|__SOUND_MPU401_H
mdefine_line|#define __SOUND_MPU401_H
multiline_comment|/*&n; *  Header file for MPU-401 and compatible cards&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &quot;rawmidi.h&quot;
DECL|macro|MPU401_HW_MPU401
mdefine_line|#define MPU401_HW_MPU401&t;&t;1&t;/* native MPU401 */
DECL|macro|MPU401_HW_SB
mdefine_line|#define MPU401_HW_SB&t;&t;&t;2&t;/* SoundBlaster MPU-401 UART */
DECL|macro|MPU401_HW_ES1688
mdefine_line|#define MPU401_HW_ES1688&t;&t;3&t;/* AudioDrive ES1688 MPU-401 UART */
DECL|macro|MPU401_HW_OPL3SA2
mdefine_line|#define MPU401_HW_OPL3SA2&t;&t;4&t;/* Yamaha OPL3-SA2 */
DECL|macro|MPU401_HW_SONICVIBES
mdefine_line|#define MPU401_HW_SONICVIBES&t;&t;5&t;/* S3 SonicVibes */
DECL|macro|MPU401_HW_CS4232
mdefine_line|#define MPU401_HW_CS4232&t;&t;6&t;/* CS4232 */
DECL|macro|MPU401_HW_ES18XX
mdefine_line|#define MPU401_HW_ES18XX&t;&t;7&t;/* AudioDrive ES18XX MPU-401 UART */
DECL|macro|MPU401_HW_FM801
mdefine_line|#define MPU401_HW_FM801&t;&t;&t;8&t;/* ForteMedia FM801 */
DECL|macro|MPU401_HW_TRID4DWAVE
mdefine_line|#define MPU401_HW_TRID4DWAVE&t;&t;9&t;/* Trident 4DWave */
DECL|macro|MPU401_HW_AZT2320
mdefine_line|#define MPU401_HW_AZT2320&t;&t;10&t;/* Aztech AZT2320 */
DECL|macro|MPU401_HW_ALS100
mdefine_line|#define MPU401_HW_ALS100&t;&t;11&t;/* Avance Logic ALS100 */
DECL|macro|MPU401_HW_ICE1712
mdefine_line|#define MPU401_HW_ICE1712&t;&t;12&t;/* Envy24 */
DECL|macro|MPU401_HW_VIA686A
mdefine_line|#define MPU401_HW_VIA686A&t;&t;13&t;/* VIA 82C686A */
DECL|macro|MPU401_HW_YMFPCI
mdefine_line|#define MPU401_HW_YMFPCI&t;&t;14&t;/* YMF DS-XG PCI */
DECL|macro|MPU401_HW_CMIPCI
mdefine_line|#define MPU401_HW_CMIPCI&t;&t;15&t;/* CMIPCI MPU-401 UART */
DECL|macro|MPU401_HW_ALS4000
mdefine_line|#define MPU401_HW_ALS4000&t;&t;16&t;/* Avance Logic ALS4000 */
DECL|macro|MPU401_MODE_BIT_INPUT
mdefine_line|#define MPU401_MODE_BIT_INPUT&t;&t;0
DECL|macro|MPU401_MODE_BIT_OUTPUT
mdefine_line|#define MPU401_MODE_BIT_OUTPUT&t;&t;1
DECL|macro|MPU401_MODE_BIT_INPUT_TRIGGER
mdefine_line|#define MPU401_MODE_BIT_INPUT_TRIGGER&t;2
DECL|macro|MPU401_MODE_BIT_OUTPUT_TRIGGER
mdefine_line|#define MPU401_MODE_BIT_OUTPUT_TRIGGER&t;3
DECL|macro|MPU401_MODE_BIT_RX_LOOP
mdefine_line|#define MPU401_MODE_BIT_RX_LOOP&t;&t;4
DECL|macro|MPU401_MODE_BIT_TX_LOOP
mdefine_line|#define MPU401_MODE_BIT_TX_LOOP&t;&t;5
DECL|macro|MPU401_MODE_INPUT
mdefine_line|#define MPU401_MODE_INPUT&t;&t;(1&lt;&lt;MPU401_MODE_BIT_INPUT)
DECL|macro|MPU401_MODE_OUTPUT
mdefine_line|#define MPU401_MODE_OUTPUT&t;&t;(1&lt;&lt;MPU401_MODE_BIT_OUTPUT)
DECL|macro|MPU401_MODE_INPUT_TRIGGER
mdefine_line|#define MPU401_MODE_INPUT_TRIGGER&t;(1&lt;&lt;MPU401_MODE_BIT_INPUT_TRIGGER)
DECL|macro|MPU401_MODE_OUTPUT_TRIGGER
mdefine_line|#define MPU401_MODE_OUTPUT_TRIGGER&t;(1&lt;&lt;MPU401_MODE_BIT_OUTPUT_TRIGGER)
DECL|macro|MPU401_MODE_INPUT_TIMER
mdefine_line|#define MPU401_MODE_INPUT_TIMER&t;&t;(1&lt;&lt;0)
DECL|macro|MPU401_MODE_OUTPUT_TIMER
mdefine_line|#define MPU401_MODE_OUTPUT_TIMER&t;(1&lt;&lt;1)
DECL|typedef|mpu401_t
r_typedef
r_struct
id|_snd_mpu401
id|mpu401_t
suffix:semicolon
DECL|struct|_snd_mpu401
r_struct
id|_snd_mpu401
(brace
DECL|member|rmidi
id|snd_rawmidi_t
op_star
id|rmidi
suffix:semicolon
DECL|member|hardware
r_int
r_int
id|hardware
suffix:semicolon
multiline_comment|/* MPU401_HW_XXXX */
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/* base port of MPU-401 chip */
DECL|member|res
r_struct
id|resource
op_star
id|res
suffix:semicolon
multiline_comment|/* port resource */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ number of MPU-401 chip (-1 = poll) */
DECL|member|irq_flags
r_int
id|irq_flags
suffix:semicolon
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* MPU401_MODE_XXXX */
DECL|member|timer_invoked
r_int
id|timer_invoked
suffix:semicolon
DECL|member|open_input
r_int
(paren
op_star
id|open_input
)paren
(paren
id|mpu401_t
op_star
id|mpu
)paren
suffix:semicolon
DECL|member|close_input
r_void
(paren
op_star
id|close_input
)paren
(paren
id|mpu401_t
op_star
id|mpu
)paren
suffix:semicolon
DECL|member|open_output
r_int
(paren
op_star
id|open_output
)paren
(paren
id|mpu401_t
op_star
id|mpu
)paren
suffix:semicolon
DECL|member|close_output
r_void
(paren
op_star
id|close_output
)paren
(paren
id|mpu401_t
op_star
id|mpu
)paren
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
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
DECL|member|input_lock
id|spinlock_t
id|input_lock
suffix:semicolon
DECL|member|output_lock
id|spinlock_t
id|output_lock
suffix:semicolon
DECL|member|timer_lock
id|spinlock_t
id|timer_lock
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* I/O ports */
DECL|macro|MPU401C
mdefine_line|#define MPU401C(mpu) ((mpu)-&gt;port + 1)
DECL|macro|MPU401D
mdefine_line|#define MPU401D(mpu) ((mpu)-&gt;port + 0)
multiline_comment|/*&n;&n; */
r_void
id|snd_mpu401_uart_interrupt
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
r_int
id|snd_mpu401_uart_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
id|device
comma
r_int
r_int
id|hardware
comma
r_int
r_int
id|port
comma
r_int
id|integrated
comma
r_int
id|irq
comma
r_int
id|irq_flags
comma
id|snd_rawmidi_t
op_star
op_star
id|rrawmidi
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_MPU401_H */
eof
