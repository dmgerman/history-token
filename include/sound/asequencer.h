multiline_comment|/*&n; *  Main header file for the ALSA sequencer&n; *  Copyright (c) 1998-1999 by Frank van de Pol &lt;fvdpol@home.nl&gt;&n; *            (c) 1998-1999 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SOUND_ASEQUENCER_H
DECL|macro|__SOUND_ASEQUENCER_H
mdefine_line|#define __SOUND_ASEQUENCER_H
macro_line|#ifndef __KERNEL__
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;sys/ipc.h&gt;
macro_line|#endif
macro_line|#include &lt;sound/asound.h&gt;
multiline_comment|/** version of the sequencer */
DECL|macro|SNDRV_SEQ_VERSION
mdefine_line|#define SNDRV_SEQ_VERSION SNDRV_PROTOCOL_VERSION (1, 0, 0)
multiline_comment|/**&n; * definition of sequencer event types&n; */
multiline_comment|/** system messages&n; * event data type = #sndrv_seq_result_t&n; */
DECL|macro|SNDRV_SEQ_EVENT_SYSTEM
mdefine_line|#define SNDRV_SEQ_EVENT_SYSTEM&t;&t;0
DECL|macro|SNDRV_SEQ_EVENT_RESULT
mdefine_line|#define SNDRV_SEQ_EVENT_RESULT&t;&t;1
multiline_comment|/** note messages (channel specific)&n; * event data type = #sndrv_seq_ev_note&n; */
DECL|macro|SNDRV_SEQ_EVENT_NOTE
mdefine_line|#define SNDRV_SEQ_EVENT_NOTE&t;&t;5
DECL|macro|SNDRV_SEQ_EVENT_NOTEON
mdefine_line|#define SNDRV_SEQ_EVENT_NOTEON&t;&t;6
DECL|macro|SNDRV_SEQ_EVENT_NOTEOFF
mdefine_line|#define SNDRV_SEQ_EVENT_NOTEOFF&t;&t;7
DECL|macro|SNDRV_SEQ_EVENT_KEYPRESS
mdefine_line|#define SNDRV_SEQ_EVENT_KEYPRESS&t;8
multiline_comment|/** control messages (channel specific)&n; * event data type = #sndrv_seq_ev_ctrl&n; */
DECL|macro|SNDRV_SEQ_EVENT_CONTROLLER
mdefine_line|#define SNDRV_SEQ_EVENT_CONTROLLER&t;10
DECL|macro|SNDRV_SEQ_EVENT_PGMCHANGE
mdefine_line|#define SNDRV_SEQ_EVENT_PGMCHANGE&t;11
DECL|macro|SNDRV_SEQ_EVENT_CHANPRESS
mdefine_line|#define SNDRV_SEQ_EVENT_CHANPRESS&t;12
DECL|macro|SNDRV_SEQ_EVENT_PITCHBEND
mdefine_line|#define SNDRV_SEQ_EVENT_PITCHBEND&t;13&t;/**&lt; from -8192 to 8191 */
DECL|macro|SNDRV_SEQ_EVENT_CONTROL14
mdefine_line|#define SNDRV_SEQ_EVENT_CONTROL14&t;14&t;/**&lt; 14 bit controller value */
DECL|macro|SNDRV_SEQ_EVENT_NONREGPARAM
mdefine_line|#define SNDRV_SEQ_EVENT_NONREGPARAM&t;15&t;/**&lt; 14 bit NRPN */
DECL|macro|SNDRV_SEQ_EVENT_REGPARAM
mdefine_line|#define SNDRV_SEQ_EVENT_REGPARAM&t;16&t;/**&lt; 14 bit RPN */
multiline_comment|/** synchronisation messages&n; * event data type = #sndrv_seq_ev_ctrl&n; */
DECL|macro|SNDRV_SEQ_EVENT_SONGPOS
mdefine_line|#define SNDRV_SEQ_EVENT_SONGPOS&t;&t;20&t;/* Song Position Pointer with LSB and MSB values */
DECL|macro|SNDRV_SEQ_EVENT_SONGSEL
mdefine_line|#define SNDRV_SEQ_EVENT_SONGSEL&t;&t;21&t;/* Song Select with song ID number */
DECL|macro|SNDRV_SEQ_EVENT_QFRAME
mdefine_line|#define SNDRV_SEQ_EVENT_QFRAME&t;&t;22&t;/* midi time code quarter frame */
DECL|macro|SNDRV_SEQ_EVENT_TIMESIGN
mdefine_line|#define SNDRV_SEQ_EVENT_TIMESIGN&t;23&t;/* SMF Time Signature event */
DECL|macro|SNDRV_SEQ_EVENT_KEYSIGN
mdefine_line|#define SNDRV_SEQ_EVENT_KEYSIGN&t;&t;24&t;/* SMF Key Signature event */
multiline_comment|/** timer messages&n; * event data type = sndrv_seq_ev_queue_control_t&n; */
DECL|macro|SNDRV_SEQ_EVENT_START
mdefine_line|#define SNDRV_SEQ_EVENT_START&t;&t;30&t;/* midi Real Time Start message */
DECL|macro|SNDRV_SEQ_EVENT_CONTINUE
mdefine_line|#define SNDRV_SEQ_EVENT_CONTINUE&t;31&t;/* midi Real Time Continue message */
DECL|macro|SNDRV_SEQ_EVENT_STOP
mdefine_line|#define SNDRV_SEQ_EVENT_STOP&t;&t;32&t;/* midi Real Time Stop message */&t;
DECL|macro|SNDRV_SEQ_EVENT_SETPOS_TICK
mdefine_line|#define&t;SNDRV_SEQ_EVENT_SETPOS_TICK&t;33&t;/* set tick queue position */
DECL|macro|SNDRV_SEQ_EVENT_SETPOS_TIME
mdefine_line|#define SNDRV_SEQ_EVENT_SETPOS_TIME&t;34&t;/* set realtime queue position */
DECL|macro|SNDRV_SEQ_EVENT_TEMPO
mdefine_line|#define SNDRV_SEQ_EVENT_TEMPO&t;&t;35&t;/* (SMF) Tempo event */
DECL|macro|SNDRV_SEQ_EVENT_CLOCK
mdefine_line|#define SNDRV_SEQ_EVENT_CLOCK&t;&t;36&t;/* midi Real Time Clock message */
DECL|macro|SNDRV_SEQ_EVENT_TICK
mdefine_line|#define SNDRV_SEQ_EVENT_TICK&t;&t;37&t;/* midi Real Time Tick message */
DECL|macro|SNDRV_SEQ_EVENT_QUEUE_SKEW
mdefine_line|#define SNDRV_SEQ_EVENT_QUEUE_SKEW&t;38&t;/* skew queue tempo */
multiline_comment|/** others&n; * event data type = none&n; */
DECL|macro|SNDRV_SEQ_EVENT_TUNE_REQUEST
mdefine_line|#define SNDRV_SEQ_EVENT_TUNE_REQUEST&t;40&t;/* tune request */
DECL|macro|SNDRV_SEQ_EVENT_RESET
mdefine_line|#define SNDRV_SEQ_EVENT_RESET&t;&t;41&t;/* reset to power-on state */
DECL|macro|SNDRV_SEQ_EVENT_SENSING
mdefine_line|#define SNDRV_SEQ_EVENT_SENSING&t;&t;42&t;/* &quot;active sensing&quot; event */
multiline_comment|/** echo back, kernel private messages&n; * event data type = any type&n; */
DECL|macro|SNDRV_SEQ_EVENT_ECHO
mdefine_line|#define SNDRV_SEQ_EVENT_ECHO&t;&t;50&t;/* echo event */
DECL|macro|SNDRV_SEQ_EVENT_OSS
mdefine_line|#define SNDRV_SEQ_EVENT_OSS&t;&t;51&t;/* OSS raw event */
multiline_comment|/** system status messages (broadcast for subscribers)&n; * event data type = sndrv_seq_addr_t&n; */
DECL|macro|SNDRV_SEQ_EVENT_CLIENT_START
mdefine_line|#define SNDRV_SEQ_EVENT_CLIENT_START&t;60&t;/* new client has connected */
DECL|macro|SNDRV_SEQ_EVENT_CLIENT_EXIT
mdefine_line|#define SNDRV_SEQ_EVENT_CLIENT_EXIT&t;61&t;/* client has left the system */
DECL|macro|SNDRV_SEQ_EVENT_CLIENT_CHANGE
mdefine_line|#define SNDRV_SEQ_EVENT_CLIENT_CHANGE&t;62&t;/* client status/info has changed */
DECL|macro|SNDRV_SEQ_EVENT_PORT_START
mdefine_line|#define SNDRV_SEQ_EVENT_PORT_START&t;63&t;/* new port was created */
DECL|macro|SNDRV_SEQ_EVENT_PORT_EXIT
mdefine_line|#define SNDRV_SEQ_EVENT_PORT_EXIT&t;64&t;/* port was deleted from system */
DECL|macro|SNDRV_SEQ_EVENT_PORT_CHANGE
mdefine_line|#define SNDRV_SEQ_EVENT_PORT_CHANGE&t;65&t;/* port status/info has changed */
multiline_comment|/** port connection changes&n; * event data type = sndrv_seq_connect_t&n; */
DECL|macro|SNDRV_SEQ_EVENT_PORT_SUBSCRIBED
mdefine_line|#define SNDRV_SEQ_EVENT_PORT_SUBSCRIBED&t;66&t;/* ports connected */
DECL|macro|SNDRV_SEQ_EVENT_PORT_UNSUBSCRIBED
mdefine_line|#define SNDRV_SEQ_EVENT_PORT_UNSUBSCRIBED&t;67&t;/* ports disconnected */
multiline_comment|/** synthesizer events&n; * event data type = sndrv_seq_eve_sample_control_t&n; */
DECL|macro|SNDRV_SEQ_EVENT_SAMPLE
mdefine_line|#define SNDRV_SEQ_EVENT_SAMPLE&t;&t;70&t;/* sample select */
DECL|macro|SNDRV_SEQ_EVENT_SAMPLE_CLUSTER
mdefine_line|#define SNDRV_SEQ_EVENT_SAMPLE_CLUSTER&t;71&t;/* sample cluster select */
DECL|macro|SNDRV_SEQ_EVENT_SAMPLE_START
mdefine_line|#define SNDRV_SEQ_EVENT_SAMPLE_START&t;72&t;/* voice start */
DECL|macro|SNDRV_SEQ_EVENT_SAMPLE_STOP
mdefine_line|#define SNDRV_SEQ_EVENT_SAMPLE_STOP&t;73&t;/* voice stop */
DECL|macro|SNDRV_SEQ_EVENT_SAMPLE_FREQ
mdefine_line|#define SNDRV_SEQ_EVENT_SAMPLE_FREQ&t;74&t;/* playback frequency */
DECL|macro|SNDRV_SEQ_EVENT_SAMPLE_VOLUME
mdefine_line|#define SNDRV_SEQ_EVENT_SAMPLE_VOLUME&t;75&t;/* volume and balance */
DECL|macro|SNDRV_SEQ_EVENT_SAMPLE_LOOP
mdefine_line|#define SNDRV_SEQ_EVENT_SAMPLE_LOOP&t;76&t;/* sample loop */
DECL|macro|SNDRV_SEQ_EVENT_SAMPLE_POSITION
mdefine_line|#define SNDRV_SEQ_EVENT_SAMPLE_POSITION&t;77&t;/* sample position */
DECL|macro|SNDRV_SEQ_EVENT_SAMPLE_PRIVATE1
mdefine_line|#define SNDRV_SEQ_EVENT_SAMPLE_PRIVATE1&t;78&t;/* private (hardware dependent) event */
multiline_comment|/** user-defined events with fixed length&n; * event data type = any&n; */
DECL|macro|SNDRV_SEQ_EVENT_USR0
mdefine_line|#define SNDRV_SEQ_EVENT_USR0&t;&t;90
DECL|macro|SNDRV_SEQ_EVENT_USR1
mdefine_line|#define SNDRV_SEQ_EVENT_USR1&t;&t;91
DECL|macro|SNDRV_SEQ_EVENT_USR2
mdefine_line|#define SNDRV_SEQ_EVENT_USR2&t;&t;92
DECL|macro|SNDRV_SEQ_EVENT_USR3
mdefine_line|#define SNDRV_SEQ_EVENT_USR3&t;&t;93
DECL|macro|SNDRV_SEQ_EVENT_USR4
mdefine_line|#define SNDRV_SEQ_EVENT_USR4&t;&t;94
DECL|macro|SNDRV_SEQ_EVENT_USR5
mdefine_line|#define SNDRV_SEQ_EVENT_USR5&t;&t;95
DECL|macro|SNDRV_SEQ_EVENT_USR6
mdefine_line|#define SNDRV_SEQ_EVENT_USR6&t;&t;96
DECL|macro|SNDRV_SEQ_EVENT_USR7
mdefine_line|#define SNDRV_SEQ_EVENT_USR7&t;&t;97
DECL|macro|SNDRV_SEQ_EVENT_USR8
mdefine_line|#define SNDRV_SEQ_EVENT_USR8&t;&t;98
DECL|macro|SNDRV_SEQ_EVENT_USR9
mdefine_line|#define SNDRV_SEQ_EVENT_USR9&t;&t;99
multiline_comment|/** instrument layer&n; * variable length data can be passed directly to the driver&n; */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_BEGIN
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_BEGIN&t;100&t;/* begin of instrument management */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_END
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_END&t;101&t;/* end of instrument management */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_INFO
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_INFO&t;102&t;/* instrument interface info */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_INFO_RESULT
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_INFO_RESULT 103&t;/* result */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_FINFO
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_FINFO&t;104&t;/* get format info */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_FINFO_RESULT
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_FINFO_RESULT 105&t;/* get format info */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_RESET
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_RESET&t;106&t;/* reset instrument memory */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_STATUS
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_STATUS&t;107&t;/* instrument interface status */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_STATUS_RESULT
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_STATUS_RESULT 108&t;/* result */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_PUT
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_PUT&t;109&t;/* put instrument to port */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_GET
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_GET&t;110&t;/* get instrument from port */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_GET_RESULT
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_GET_RESULT&t;111&t;/* result */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_FREE
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_FREE&t;112&t;/* free instrument(s) */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_LIST
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_LIST&t;113&t;/* instrument list */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_LIST_RESULT
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_LIST_RESULT 114&t;/* result */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_CLUSTER
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_CLUSTER&t;115&t;/* cluster parameters */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_CLUSTER_GET
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_CLUSTER_GET&t;116&t;/* get cluster parameters */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_CLUSTER_RESULT
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_CLUSTER_RESULT 117&t;/* result */
DECL|macro|SNDRV_SEQ_EVENT_INSTR_CHANGE
mdefine_line|#define SNDRV_SEQ_EVENT_INSTR_CHANGE&t;118&t;/* instrument change */
multiline_comment|/* 119-129: reserved */
multiline_comment|/* 130-139: variable length events&n; * event data type = sndrv_seq_ev_ext&n; * (SNDRV_SEQ_EVENT_LENGTH_VARIABLE must be set)&n; */
DECL|macro|SNDRV_SEQ_EVENT_SYSEX
mdefine_line|#define SNDRV_SEQ_EVENT_SYSEX&t;&t;130&t;/* system exclusive data (variable length) */
DECL|macro|SNDRV_SEQ_EVENT_BOUNCE
mdefine_line|#define SNDRV_SEQ_EVENT_BOUNCE&t;&t;131&t;/* error event */
multiline_comment|/* 132-134: reserved */
DECL|macro|SNDRV_SEQ_EVENT_USR_VAR0
mdefine_line|#define SNDRV_SEQ_EVENT_USR_VAR0&t;135
DECL|macro|SNDRV_SEQ_EVENT_USR_VAR1
mdefine_line|#define SNDRV_SEQ_EVENT_USR_VAR1&t;136
DECL|macro|SNDRV_SEQ_EVENT_USR_VAR2
mdefine_line|#define SNDRV_SEQ_EVENT_USR_VAR2&t;137
DECL|macro|SNDRV_SEQ_EVENT_USR_VAR3
mdefine_line|#define SNDRV_SEQ_EVENT_USR_VAR3&t;138
DECL|macro|SNDRV_SEQ_EVENT_USR_VAR4
mdefine_line|#define SNDRV_SEQ_EVENT_USR_VAR4&t;139
multiline_comment|/* 140-149: IPC shared memory events (*NOT SUPPORTED YET*)&n; * event data type = sndrv_seq_ev_ipcshm&n; * (SNDRV_SEQ_EVENT_LENGTH_VARIPC must be set)&n; */
DECL|macro|SNDRV_SEQ_EVENT_IPCSHM
mdefine_line|#define SNDRV_SEQ_EVENT_IPCSHM&t;&t;140
multiline_comment|/* 141-144: reserved */
DECL|macro|SNDRV_SEQ_EVENT_USR_VARIPC0
mdefine_line|#define SNDRV_SEQ_EVENT_USR_VARIPC0&t;145
DECL|macro|SNDRV_SEQ_EVENT_USR_VARIPC1
mdefine_line|#define SNDRV_SEQ_EVENT_USR_VARIPC1&t;146
DECL|macro|SNDRV_SEQ_EVENT_USR_VARIPC2
mdefine_line|#define SNDRV_SEQ_EVENT_USR_VARIPC2&t;147
DECL|macro|SNDRV_SEQ_EVENT_USR_VARIPC3
mdefine_line|#define SNDRV_SEQ_EVENT_USR_VARIPC3&t;148
DECL|macro|SNDRV_SEQ_EVENT_USR_VARIPC4
mdefine_line|#define SNDRV_SEQ_EVENT_USR_VARIPC4&t;149
multiline_comment|/* 150-151: kernel events with quote - DO NOT use in user clients */
DECL|macro|SNDRV_SEQ_EVENT_KERNEL_ERROR
mdefine_line|#define SNDRV_SEQ_EVENT_KERNEL_ERROR&t;150
DECL|macro|SNDRV_SEQ_EVENT_KERNEL_QUOTE
mdefine_line|#define SNDRV_SEQ_EVENT_KERNEL_QUOTE&t;151
multiline_comment|/* 152-191: reserved */
multiline_comment|/* 192-254: hardware specific events */
multiline_comment|/* 255: special event */
DECL|macro|SNDRV_SEQ_EVENT_NONE
mdefine_line|#define SNDRV_SEQ_EVENT_NONE&t;&t;255
DECL|typedef|sndrv_seq_event_type_t
r_typedef
r_int
r_char
id|sndrv_seq_event_type_t
suffix:semicolon
multiline_comment|/** event address */
DECL|struct|sndrv_seq_addr
r_struct
id|sndrv_seq_addr
(brace
DECL|member|client
r_int
r_char
id|client
suffix:semicolon
multiline_comment|/**&lt; Client number:         0..255, 255 = broadcast to all clients */
DECL|member|port
r_int
r_char
id|port
suffix:semicolon
multiline_comment|/**&lt; Port within client:    0..255, 255 = broadcast to all ports */
)brace
suffix:semicolon
multiline_comment|/** port connection */
DECL|struct|sndrv_seq_connect
r_struct
id|sndrv_seq_connect
(brace
DECL|member|sender
r_struct
id|sndrv_seq_addr
id|sender
suffix:semicolon
DECL|member|dest
r_struct
id|sndrv_seq_addr
id|dest
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SNDRV_SEQ_ADDRESS_UNKNOWN
mdefine_line|#define SNDRV_SEQ_ADDRESS_UNKNOWN&t;253&t;/* unknown source */
DECL|macro|SNDRV_SEQ_ADDRESS_SUBSCRIBERS
mdefine_line|#define SNDRV_SEQ_ADDRESS_SUBSCRIBERS&t;254&t;/* send event to all subscribed ports */
DECL|macro|SNDRV_SEQ_ADDRESS_BROADCAST
mdefine_line|#define SNDRV_SEQ_ADDRESS_BROADCAST&t;255&t;/* send event to all queues/clients/ports/channels */
DECL|macro|SNDRV_SEQ_QUEUE_DIRECT
mdefine_line|#define SNDRV_SEQ_QUEUE_DIRECT&t;&t;253&t;/* direct dispatch */
multiline_comment|/* event mode flag - NOTE: only 8 bits available! */
DECL|macro|SNDRV_SEQ_TIME_STAMP_TICK
mdefine_line|#define SNDRV_SEQ_TIME_STAMP_TICK&t;(0&lt;&lt;0) /* timestamp in clock ticks */
DECL|macro|SNDRV_SEQ_TIME_STAMP_REAL
mdefine_line|#define SNDRV_SEQ_TIME_STAMP_REAL&t;(1&lt;&lt;0) /* timestamp in real time */
DECL|macro|SNDRV_SEQ_TIME_STAMP_MASK
mdefine_line|#define SNDRV_SEQ_TIME_STAMP_MASK&t;(1&lt;&lt;0)
DECL|macro|SNDRV_SEQ_TIME_MODE_ABS
mdefine_line|#define SNDRV_SEQ_TIME_MODE_ABS&t;&t;(0&lt;&lt;1)&t;/* absolute timestamp */
DECL|macro|SNDRV_SEQ_TIME_MODE_REL
mdefine_line|#define SNDRV_SEQ_TIME_MODE_REL&t;&t;(1&lt;&lt;1)&t;/* relative to current time */
DECL|macro|SNDRV_SEQ_TIME_MODE_MASK
mdefine_line|#define SNDRV_SEQ_TIME_MODE_MASK&t;(1&lt;&lt;1)
DECL|macro|SNDRV_SEQ_EVENT_LENGTH_FIXED
mdefine_line|#define SNDRV_SEQ_EVENT_LENGTH_FIXED&t;(0&lt;&lt;2)&t;/* fixed event size */
DECL|macro|SNDRV_SEQ_EVENT_LENGTH_VARIABLE
mdefine_line|#define SNDRV_SEQ_EVENT_LENGTH_VARIABLE&t;(1&lt;&lt;2)&t;/* variable event size */
DECL|macro|SNDRV_SEQ_EVENT_LENGTH_VARUSR
mdefine_line|#define SNDRV_SEQ_EVENT_LENGTH_VARUSR&t;(2&lt;&lt;2)&t;/* variable event size - user memory space */
DECL|macro|SNDRV_SEQ_EVENT_LENGTH_VARIPC
mdefine_line|#define SNDRV_SEQ_EVENT_LENGTH_VARIPC&t;(3&lt;&lt;2)&t;/* variable event size - IPC */
DECL|macro|SNDRV_SEQ_EVENT_LENGTH_MASK
mdefine_line|#define SNDRV_SEQ_EVENT_LENGTH_MASK&t;(3&lt;&lt;2)
DECL|macro|SNDRV_SEQ_PRIORITY_NORMAL
mdefine_line|#define SNDRV_SEQ_PRIORITY_NORMAL&t;(0&lt;&lt;4)&t;/* normal priority */
DECL|macro|SNDRV_SEQ_PRIORITY_HIGH
mdefine_line|#define SNDRV_SEQ_PRIORITY_HIGH&t;&t;(1&lt;&lt;4)&t;/* event should be processed before others */
DECL|macro|SNDRV_SEQ_PRIORITY_MASK
mdefine_line|#define SNDRV_SEQ_PRIORITY_MASK&t;&t;(1&lt;&lt;4)
multiline_comment|/* note event */
DECL|struct|sndrv_seq_ev_note
r_struct
id|sndrv_seq_ev_note
(brace
DECL|member|channel
r_int
r_char
id|channel
suffix:semicolon
DECL|member|note
r_int
r_char
id|note
suffix:semicolon
DECL|member|velocity
r_int
r_char
id|velocity
suffix:semicolon
DECL|member|off_velocity
r_int
r_char
id|off_velocity
suffix:semicolon
multiline_comment|/* only for SNDRV_SEQ_EVENT_NOTE */
DECL|member|duration
r_int
r_int
id|duration
suffix:semicolon
multiline_comment|/* only for SNDRV_SEQ_EVENT_NOTE */
)brace
suffix:semicolon
multiline_comment|/* controller event */
DECL|struct|sndrv_seq_ev_ctrl
r_struct
id|sndrv_seq_ev_ctrl
(brace
DECL|member|channel
r_int
r_char
id|channel
suffix:semicolon
DECL|member|unused1
DECL|member|unused2
DECL|member|unused3
r_int
r_char
id|unused1
comma
id|unused2
comma
id|unused3
suffix:semicolon
multiline_comment|/* pad */
DECL|member|param
r_int
r_int
id|param
suffix:semicolon
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* generic set of bytes (12x8 bit) */
DECL|struct|sndrv_seq_ev_raw8
r_struct
id|sndrv_seq_ev_raw8
(brace
DECL|member|d
r_int
r_char
id|d
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* 8 bit value */
)brace
suffix:semicolon
multiline_comment|/* generic set of integers (3x32 bit) */
DECL|struct|sndrv_seq_ev_raw32
r_struct
id|sndrv_seq_ev_raw32
(brace
DECL|member|d
r_int
r_int
id|d
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 32 bit value */
)brace
suffix:semicolon
multiline_comment|/* external stored data */
DECL|struct|sndrv_seq_ev_ext
r_struct
id|sndrv_seq_ev_ext
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* length of data */
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
multiline_comment|/* pointer to data (note: maybe 64-bit) */
)brace
suffix:semicolon
multiline_comment|/* external stored data - IPC shared memory */
DECL|struct|sndrv_seq_ev_ipcshm
r_struct
id|sndrv_seq_ev_ipcshm
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* length of data */
DECL|member|ipc
id|key_t
id|ipc
suffix:semicolon
multiline_comment|/* IPC key */
)brace
suffix:semicolon
multiline_comment|/* Instrument cluster type */
DECL|typedef|sndrv_seq_instr_cluster_t
r_typedef
r_int
r_int
id|sndrv_seq_instr_cluster_t
suffix:semicolon
multiline_comment|/* Instrument type */
DECL|struct|sndrv_seq_instr
r_struct
id|sndrv_seq_instr
(brace
DECL|member|cluster
id|sndrv_seq_instr_cluster_t
id|cluster
suffix:semicolon
DECL|member|std
r_int
r_int
id|std
suffix:semicolon
multiline_comment|/* the upper byte means a private instrument (owner - client #) */
DECL|member|bank
r_int
r_int
id|bank
suffix:semicolon
DECL|member|prg
r_int
r_int
id|prg
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* sample number */
DECL|struct|sndrv_seq_ev_sample
r_struct
id|sndrv_seq_ev_sample
(brace
DECL|member|std
r_int
r_int
id|std
suffix:semicolon
DECL|member|bank
r_int
r_int
id|bank
suffix:semicolon
DECL|member|prg
r_int
r_int
id|prg
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* sample cluster */
DECL|struct|sndrv_seq_ev_cluster
r_struct
id|sndrv_seq_ev_cluster
(brace
DECL|member|cluster
id|sndrv_seq_instr_cluster_t
id|cluster
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* sample position */
DECL|typedef|sndrv_seq_position_t
r_typedef
r_int
r_int
id|sndrv_seq_position_t
suffix:semicolon
multiline_comment|/* playback position (in samples) * 16 */
multiline_comment|/* sample stop mode */
DECL|enum|sndrv_seq_stop_mode
r_enum
id|sndrv_seq_stop_mode
(brace
DECL|enumerator|SAMPLE_STOP_IMMEDIATELY
id|SAMPLE_STOP_IMMEDIATELY
op_assign
l_int|0
comma
multiline_comment|/* terminate playing immediately */
DECL|enumerator|SAMPLE_STOP_VENVELOPE
id|SAMPLE_STOP_VENVELOPE
op_assign
l_int|1
comma
multiline_comment|/* finish volume envelope */
DECL|enumerator|SAMPLE_STOP_LOOP
id|SAMPLE_STOP_LOOP
op_assign
l_int|2
multiline_comment|/* terminate loop and finish wave */
)brace
suffix:semicolon
multiline_comment|/* sample frequency */
DECL|typedef|sndrv_seq_frequency_t
r_typedef
r_int
id|sndrv_seq_frequency_t
suffix:semicolon
multiline_comment|/* playback frequency in HZ * 16 */
multiline_comment|/* sample volume control; if any value is set to -1 == do not change */
DECL|struct|sndrv_seq_ev_volume
r_struct
id|sndrv_seq_ev_volume
(brace
DECL|member|volume
r_int
r_int
id|volume
suffix:semicolon
multiline_comment|/* range: 0-16383 */
DECL|member|lr
r_int
r_int
id|lr
suffix:semicolon
multiline_comment|/* left-right balance; range: 0-16383 */
DECL|member|fr
r_int
r_int
id|fr
suffix:semicolon
multiline_comment|/* front-rear balance; range: 0-16383 */
DECL|member|du
r_int
r_int
id|du
suffix:semicolon
multiline_comment|/* down-up balance; range: 0-16383 */
)brace
suffix:semicolon
multiline_comment|/* simple loop redefinition */
DECL|struct|sndrv_seq_ev_loop
r_struct
id|sndrv_seq_ev_loop
(brace
DECL|member|start
r_int
r_int
id|start
suffix:semicolon
multiline_comment|/* loop start (in samples) * 16 */
DECL|member|end
r_int
r_int
id|end
suffix:semicolon
multiline_comment|/* loop end (in samples) * 16 */
)brace
suffix:semicolon
DECL|struct|sndrv_seq_ev_sample_control
r_struct
id|sndrv_seq_ev_sample_control
(brace
DECL|member|channel
r_int
r_char
id|channel
suffix:semicolon
DECL|member|unused1
DECL|member|unused2
DECL|member|unused3
r_int
r_char
id|unused1
comma
id|unused2
comma
id|unused3
suffix:semicolon
multiline_comment|/* pad */
r_union
(brace
DECL|member|sample
r_struct
id|sndrv_seq_ev_sample
id|sample
suffix:semicolon
DECL|member|cluster
r_struct
id|sndrv_seq_ev_cluster
id|cluster
suffix:semicolon
DECL|member|position
id|sndrv_seq_position_t
id|position
suffix:semicolon
DECL|member|stop_mode
r_enum
id|sndrv_seq_stop_mode
id|stop_mode
suffix:semicolon
DECL|member|frequency
id|sndrv_seq_frequency_t
id|frequency
suffix:semicolon
DECL|member|volume
r_struct
id|sndrv_seq_ev_volume
id|volume
suffix:semicolon
DECL|member|loop
r_struct
id|sndrv_seq_ev_loop
id|loop
suffix:semicolon
DECL|member|raw8
r_int
r_char
id|raw8
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|param
)brace
id|param
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* INSTR_BEGIN event */
DECL|struct|sndrv_seq_ev_instr_begin
r_struct
id|sndrv_seq_ev_instr_begin
(brace
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
multiline_comment|/* zero = forever, otherwise timeout in ms */
)brace
suffix:semicolon
DECL|struct|sndrv_seq_result
r_struct
id|sndrv_seq_result
(brace
DECL|member|event
r_int
id|event
suffix:semicolon
multiline_comment|/* processed event type */
DECL|member|result
r_int
id|result
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sndrv_seq_real_time
r_struct
id|sndrv_seq_real_time
(brace
DECL|member|tv_sec
r_int
r_int
id|tv_sec
suffix:semicolon
multiline_comment|/* seconds */
DECL|member|tv_nsec
r_int
r_int
id|tv_nsec
suffix:semicolon
multiline_comment|/* nanoseconds */
)brace
suffix:semicolon
DECL|typedef|sndrv_seq_tick_time_t
r_typedef
r_int
r_int
id|sndrv_seq_tick_time_t
suffix:semicolon
multiline_comment|/* midi ticks */
DECL|union|sndrv_seq_timestamp
r_union
id|sndrv_seq_timestamp
(brace
DECL|member|tick
id|sndrv_seq_tick_time_t
id|tick
suffix:semicolon
DECL|member|time
r_struct
id|sndrv_seq_real_time
id|time
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sndrv_seq_queue_skew
r_struct
id|sndrv_seq_queue_skew
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* queue timer control */
DECL|struct|sndrv_seq_ev_queue_control
r_struct
id|sndrv_seq_ev_queue_control
(brace
DECL|member|queue
r_int
r_char
id|queue
suffix:semicolon
multiline_comment|/* affected queue */
DECL|member|pad
r_int
r_char
id|pad
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* reserved */
r_union
(brace
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
multiline_comment|/* affected value (e.g. tempo) */
DECL|member|time
r_union
id|sndrv_seq_timestamp
id|time
suffix:semicolon
multiline_comment|/* time */
DECL|member|position
r_int
r_int
id|position
suffix:semicolon
multiline_comment|/* sync position */
DECL|member|skew
r_struct
id|sndrv_seq_queue_skew
id|skew
suffix:semicolon
DECL|member|d32
r_int
r_int
id|d32
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|d8
r_int
r_char
id|d8
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|param
)brace
id|param
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* quoted event - inside the kernel only */
DECL|struct|sndrv_seq_ev_quote
r_struct
id|sndrv_seq_ev_quote
(brace
DECL|member|origin
r_struct
id|sndrv_seq_addr
id|origin
suffix:semicolon
multiline_comment|/* original sender */
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
multiline_comment|/* optional data */
DECL|member|event
r_struct
id|sndrv_seq_event
op_star
id|event
suffix:semicolon
multiline_comment|/* quoted event */
)brace
suffix:semicolon
multiline_comment|/* sequencer event */
DECL|struct|sndrv_seq_event
r_struct
id|sndrv_seq_event
(brace
DECL|member|type
id|sndrv_seq_event_type_t
id|type
suffix:semicolon
multiline_comment|/* event type */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* event flags */
DECL|member|tag
r_char
id|tag
suffix:semicolon
DECL|member|queue
r_int
r_char
id|queue
suffix:semicolon
multiline_comment|/* schedule queue */
DECL|member|time
r_union
id|sndrv_seq_timestamp
id|time
suffix:semicolon
multiline_comment|/* schedule time */
DECL|member|source
r_struct
id|sndrv_seq_addr
id|source
suffix:semicolon
multiline_comment|/* source address */
DECL|member|dest
r_struct
id|sndrv_seq_addr
id|dest
suffix:semicolon
multiline_comment|/* destination address */
r_union
(brace
multiline_comment|/* event data... */
DECL|member|note
r_struct
id|sndrv_seq_ev_note
id|note
suffix:semicolon
DECL|member|control
r_struct
id|sndrv_seq_ev_ctrl
id|control
suffix:semicolon
DECL|member|raw8
r_struct
id|sndrv_seq_ev_raw8
id|raw8
suffix:semicolon
DECL|member|raw32
r_struct
id|sndrv_seq_ev_raw32
id|raw32
suffix:semicolon
DECL|member|ext
r_struct
id|sndrv_seq_ev_ext
id|ext
suffix:semicolon
DECL|member|ipcshm
r_struct
id|sndrv_seq_ev_ipcshm
id|ipcshm
suffix:semicolon
DECL|member|queue
r_struct
id|sndrv_seq_ev_queue_control
id|queue
suffix:semicolon
DECL|member|time
r_union
id|sndrv_seq_timestamp
id|time
suffix:semicolon
DECL|member|addr
r_struct
id|sndrv_seq_addr
id|addr
suffix:semicolon
DECL|member|connect
r_struct
id|sndrv_seq_connect
id|connect
suffix:semicolon
DECL|member|result
r_struct
id|sndrv_seq_result
id|result
suffix:semicolon
DECL|member|instr_begin
r_struct
id|sndrv_seq_ev_instr_begin
id|instr_begin
suffix:semicolon
DECL|member|sample
r_struct
id|sndrv_seq_ev_sample_control
id|sample
suffix:semicolon
DECL|member|quote
r_struct
id|sndrv_seq_ev_quote
id|quote
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * bounce event - stored as variable size data&n; */
DECL|struct|sndrv_seq_event_bounce
r_struct
id|sndrv_seq_event_bounce
(brace
DECL|member|err
r_int
id|err
suffix:semicolon
DECL|member|event
r_struct
id|sndrv_seq_event
id|event
suffix:semicolon
multiline_comment|/* external data follows here. */
)brace
suffix:semicolon
DECL|macro|sndrv_seq_event_bounce_ext_data
mdefine_line|#define sndrv_seq_event_bounce_ext_data(ev) ((void*)((char *)(ev)-&gt;data.ext.ptr + sizeof(sndrv_seq_event_bounce_t)))
multiline_comment|/*&n; * type check macros&n; */
multiline_comment|/* result events: 0-4 */
DECL|macro|sndrv_seq_ev_is_result_type
mdefine_line|#define sndrv_seq_ev_is_result_type(ev)&t;((ev)-&gt;type &lt; 5)
multiline_comment|/* channel specific events: 5-19 */
DECL|macro|sndrv_seq_ev_is_channel_type
mdefine_line|#define sndrv_seq_ev_is_channel_type(ev)&t;((ev)-&gt;type &gt;= 5 &amp;&amp; (ev)-&gt;type &lt; 20)
multiline_comment|/* note events: 5-9 */
DECL|macro|sndrv_seq_ev_is_note_type
mdefine_line|#define sndrv_seq_ev_is_note_type(ev)&t;((ev)-&gt;type &gt;= 5 &amp;&amp; (ev)-&gt;type &lt; 10)
multiline_comment|/* control events: 10-19 */
DECL|macro|sndrv_seq_ev_is_control_type
mdefine_line|#define sndrv_seq_ev_is_control_type(ev)&t;((ev)-&gt;type &gt;= 10 &amp;&amp; (ev)-&gt;type &lt; 20)
multiline_comment|/* queue control events: 30-39 */
DECL|macro|sndrv_seq_ev_is_queue_type
mdefine_line|#define sndrv_seq_ev_is_queue_type(ev)&t;((ev)-&gt;type &gt;= 30 &amp;&amp; (ev)-&gt;type &lt; 40)
multiline_comment|/* system status messages */
DECL|macro|sndrv_seq_ev_is_message_type
mdefine_line|#define sndrv_seq_ev_is_message_type(ev)&t;((ev)-&gt;type &gt;= 60 &amp;&amp; (ev)-&gt;type &lt; 69)
multiline_comment|/* sample messages */
DECL|macro|sndrv_seq_ev_is_sample_type
mdefine_line|#define sndrv_seq_ev_is_sample_type(ev)&t;((ev)-&gt;type &gt;= 70 &amp;&amp; (ev)-&gt;type &lt; 79)
multiline_comment|/* user-defined messages */
DECL|macro|sndrv_seq_ev_is_user_type
mdefine_line|#define sndrv_seq_ev_is_user_type(ev)&t;((ev)-&gt;type &gt;= 90 &amp;&amp; (ev)-&gt;type &lt; 99)
multiline_comment|/* fixed length events: 0-99 */
DECL|macro|sndrv_seq_ev_is_fixed_type
mdefine_line|#define sndrv_seq_ev_is_fixed_type(ev)&t;((ev)-&gt;type &lt; 100)
multiline_comment|/* instrument layer events: 100-129 */
DECL|macro|sndrv_seq_ev_is_instr_type
mdefine_line|#define sndrv_seq_ev_is_instr_type(ev)&t;((ev)-&gt;type &gt;= 100 &amp;&amp; (ev)-&gt;type &lt; 130)
multiline_comment|/* variable length events: 130-139 */
DECL|macro|sndrv_seq_ev_is_variable_type
mdefine_line|#define sndrv_seq_ev_is_variable_type(ev)&t;((ev)-&gt;type &gt;= 130 &amp;&amp; (ev)-&gt;type &lt; 140)
multiline_comment|/* ipc shmem events: 140-149 */
DECL|macro|sndrv_seq_ev_is_varipc_type
mdefine_line|#define sndrv_seq_ev_is_varipc_type(ev)&t;((ev)-&gt;type &gt;= 140 &amp;&amp; (ev)-&gt;type &lt; 150)
multiline_comment|/* reserved for kernel */
DECL|macro|sndrv_seq_ev_is_reserved
mdefine_line|#define sndrv_seq_ev_is_reserved(ev)&t;((ev)-&gt;type &gt;= 150)
multiline_comment|/* direct dispatched events */
DECL|macro|sndrv_seq_ev_is_direct
mdefine_line|#define sndrv_seq_ev_is_direct(ev)&t;((ev)-&gt;queue == SNDRV_SEQ_QUEUE_DIRECT)
multiline_comment|/*&n; * macros to check event flags&n; */
multiline_comment|/* prior events */
DECL|macro|sndrv_seq_ev_is_prior
mdefine_line|#define sndrv_seq_ev_is_prior(ev)&t;&t;(((ev)-&gt;flags &amp; SNDRV_SEQ_PRIORITY_MASK) == SNDRV_SEQ_PRIORITY_HIGH)
multiline_comment|/* event length type */
DECL|macro|sndrv_seq_ev_length_type
mdefine_line|#define sndrv_seq_ev_length_type(ev)&t;((ev)-&gt;flags &amp; SNDRV_SEQ_EVENT_LENGTH_MASK)
DECL|macro|sndrv_seq_ev_is_fixed
mdefine_line|#define sndrv_seq_ev_is_fixed(ev)&t;&t;(sndrv_seq_ev_length_type(ev) == SNDRV_SEQ_EVENT_LENGTH_FIXED)
DECL|macro|sndrv_seq_ev_is_variable
mdefine_line|#define sndrv_seq_ev_is_variable(ev)&t;(sndrv_seq_ev_length_type(ev) == SNDRV_SEQ_EVENT_LENGTH_VARIABLE)
DECL|macro|sndrv_seq_ev_is_varusr
mdefine_line|#define sndrv_seq_ev_is_varusr(ev)&t;(sndrv_seq_ev_length_type(ev) == SNDRV_SEQ_EVENT_LENGTH_VARUSR)
DECL|macro|sndrv_seq_ev_is_varipc
mdefine_line|#define sndrv_seq_ev_is_varipc(ev)&t;(sndrv_seq_ev_length_type(ev) == SNDRV_SEQ_EVENT_LENGTH_VARIPC)
multiline_comment|/* time-stamp type */
DECL|macro|sndrv_seq_ev_timestamp_type
mdefine_line|#define sndrv_seq_ev_timestamp_type(ev)&t;((ev)-&gt;flags &amp; SNDRV_SEQ_TIME_STAMP_MASK)
DECL|macro|sndrv_seq_ev_is_tick
mdefine_line|#define sndrv_seq_ev_is_tick(ev)&t;&t;(sndrv_seq_ev_timestamp_type(ev) == SNDRV_SEQ_TIME_STAMP_TICK)
DECL|macro|sndrv_seq_ev_is_real
mdefine_line|#define sndrv_seq_ev_is_real(ev)&t;&t;(sndrv_seq_ev_timestamp_type(ev) == SNDRV_SEQ_TIME_STAMP_REAL)
multiline_comment|/* time-mode type */
DECL|macro|sndrv_seq_ev_timemode_type
mdefine_line|#define sndrv_seq_ev_timemode_type(ev)&t;((ev)-&gt;flags &amp; SNDRV_SEQ_TIME_MODE_MASK)
DECL|macro|sndrv_seq_ev_is_abstime
mdefine_line|#define sndrv_seq_ev_is_abstime(ev)&t;(sndrv_seq_ev_timemode_type(ev) == SNDRV_SEQ_TIME_MODE_ABS)
DECL|macro|sndrv_seq_ev_is_reltime
mdefine_line|#define sndrv_seq_ev_is_reltime(ev)&t;(sndrv_seq_ev_timemode_type(ev) == SNDRV_SEQ_TIME_MODE_REL)
multiline_comment|/* queue sync port */
DECL|macro|sndrv_seq_queue_sync_port
mdefine_line|#define sndrv_seq_queue_sync_port(q)&t;((q) + 16)
multiline_comment|/* system information */
DECL|struct|sndrv_seq_system_info
r_struct
id|sndrv_seq_system_info
(brace
DECL|member|queues
r_int
id|queues
suffix:semicolon
multiline_comment|/* maximum queues count */
DECL|member|clients
r_int
id|clients
suffix:semicolon
multiline_comment|/* maximum clients count */
DECL|member|ports
r_int
id|ports
suffix:semicolon
multiline_comment|/* maximum ports per client */
DECL|member|channels
r_int
id|channels
suffix:semicolon
multiline_comment|/* maximum channels per port */
DECL|member|cur_clients
r_int
id|cur_clients
suffix:semicolon
multiline_comment|/* current clients */
DECL|member|cur_queues
r_int
id|cur_queues
suffix:semicolon
multiline_comment|/* current queues */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|24
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* known client numbers */
DECL|macro|SNDRV_SEQ_CLIENT_SYSTEM
mdefine_line|#define SNDRV_SEQ_CLIENT_SYSTEM&t;&t;0
DECL|macro|SNDRV_SEQ_CLIENT_DUMMY
mdefine_line|#define SNDRV_SEQ_CLIENT_DUMMY&t;&t;62&t;/* dummy ports */
DECL|macro|SNDRV_SEQ_CLIENT_OSS
mdefine_line|#define SNDRV_SEQ_CLIENT_OSS&t;&t;63&t;/* oss sequencer emulator */
multiline_comment|/* client types */
DECL|enum|sndrv_seq_client_type
r_enum
id|sndrv_seq_client_type
(brace
DECL|enumerator|NO_CLIENT
id|NO_CLIENT
op_assign
l_int|0
comma
DECL|enumerator|USER_CLIENT
id|USER_CLIENT
op_assign
l_int|1
comma
DECL|enumerator|KERNEL_CLIENT
id|KERNEL_CLIENT
op_assign
l_int|2
)brace
suffix:semicolon
multiline_comment|/* event filter flags */
DECL|macro|SNDRV_SEQ_FILTER_BROADCAST
mdefine_line|#define SNDRV_SEQ_FILTER_BROADCAST&t;(1&lt;&lt;0)&t;/* accept broadcast messages */
DECL|macro|SNDRV_SEQ_FILTER_MULTICAST
mdefine_line|#define SNDRV_SEQ_FILTER_MULTICAST&t;(1&lt;&lt;1)&t;/* accept multicast messages */
DECL|macro|SNDRV_SEQ_FILTER_BOUNCE
mdefine_line|#define SNDRV_SEQ_FILTER_BOUNCE&t;&t;(1&lt;&lt;2)&t;/* accept bounce event in error */
DECL|macro|SNDRV_SEQ_FILTER_USE_EVENT
mdefine_line|#define SNDRV_SEQ_FILTER_USE_EVENT&t;(1&lt;&lt;31)&t;/* use event filter */
DECL|struct|sndrv_seq_client_info
r_struct
id|sndrv_seq_client_info
(brace
DECL|member|client
r_int
id|client
suffix:semicolon
multiline_comment|/* client number to inquire */
DECL|member|type
r_enum
id|sndrv_seq_client_type
id|type
suffix:semicolon
multiline_comment|/* client type */
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* client name */
DECL|member|filter
r_int
r_int
id|filter
suffix:semicolon
multiline_comment|/* filter flags */
DECL|member|multicast_filter
r_int
r_char
id|multicast_filter
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* multicast filter bitmap */
DECL|member|event_filter
r_int
r_char
id|event_filter
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* event filter bitmap */
DECL|member|num_ports
r_int
id|num_ports
suffix:semicolon
multiline_comment|/* RO: number of ports */
DECL|member|event_lost
r_int
id|event_lost
suffix:semicolon
multiline_comment|/* number of lost events */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* for future use */
)brace
suffix:semicolon
multiline_comment|/* client pool size */
DECL|struct|sndrv_seq_client_pool
r_struct
id|sndrv_seq_client_pool
(brace
DECL|member|client
r_int
id|client
suffix:semicolon
multiline_comment|/* client number to inquire */
DECL|member|output_pool
r_int
id|output_pool
suffix:semicolon
multiline_comment|/* outgoing (write) pool size */
DECL|member|input_pool
r_int
id|input_pool
suffix:semicolon
multiline_comment|/* incoming (read) pool size */
DECL|member|output_room
r_int
id|output_room
suffix:semicolon
multiline_comment|/* minimum free pool size for select/blocking mode */
DECL|member|output_free
r_int
id|output_free
suffix:semicolon
multiline_comment|/* unused size */
DECL|member|input_free
r_int
id|input_free
suffix:semicolon
multiline_comment|/* unused size */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Remove events by specified criteria */
DECL|macro|SNDRV_SEQ_REMOVE_INPUT
mdefine_line|#define SNDRV_SEQ_REMOVE_INPUT&t;&t;(1&lt;&lt;0)&t;/* Flush input queues */
DECL|macro|SNDRV_SEQ_REMOVE_OUTPUT
mdefine_line|#define SNDRV_SEQ_REMOVE_OUTPUT&t;&t;(1&lt;&lt;1)&t;/* Flush output queues */
DECL|macro|SNDRV_SEQ_REMOVE_DEST
mdefine_line|#define SNDRV_SEQ_REMOVE_DEST&t;&t;(1&lt;&lt;2)&t;/* Restrict by destination q:client:port */
DECL|macro|SNDRV_SEQ_REMOVE_DEST_CHANNEL
mdefine_line|#define SNDRV_SEQ_REMOVE_DEST_CHANNEL&t;(1&lt;&lt;3)&t;/* Restrict by channel */
DECL|macro|SNDRV_SEQ_REMOVE_TIME_BEFORE
mdefine_line|#define SNDRV_SEQ_REMOVE_TIME_BEFORE&t;(1&lt;&lt;4)&t;/* Restrict to before time */
DECL|macro|SNDRV_SEQ_REMOVE_TIME_AFTER
mdefine_line|#define SNDRV_SEQ_REMOVE_TIME_AFTER&t;(1&lt;&lt;5)&t;/* Restrict to time or after */
DECL|macro|SNDRV_SEQ_REMOVE_TIME_TICK
mdefine_line|#define SNDRV_SEQ_REMOVE_TIME_TICK&t;(1&lt;&lt;6)&t;/* Time is in ticks */
DECL|macro|SNDRV_SEQ_REMOVE_EVENT_TYPE
mdefine_line|#define SNDRV_SEQ_REMOVE_EVENT_TYPE&t;(1&lt;&lt;7)&t;/* Restrict to event type */
DECL|macro|SNDRV_SEQ_REMOVE_IGNORE_OFF
mdefine_line|#define SNDRV_SEQ_REMOVE_IGNORE_OFF &t;(1&lt;&lt;8)&t;/* Do not flush off events */
DECL|macro|SNDRV_SEQ_REMOVE_TAG_MATCH
mdefine_line|#define SNDRV_SEQ_REMOVE_TAG_MATCH &t;(1&lt;&lt;9)&t;/* Restrict to events with given tag */
DECL|struct|sndrv_seq_remove_events
r_struct
id|sndrv_seq_remove_events
(brace
DECL|member|remove_mode
r_int
r_int
id|remove_mode
suffix:semicolon
multiline_comment|/* Flags that determine what gets removed */
DECL|member|time
r_union
id|sndrv_seq_timestamp
id|time
suffix:semicolon
DECL|member|queue
r_int
r_char
id|queue
suffix:semicolon
multiline_comment|/* Queue for REMOVE_DEST */
DECL|member|dest
r_struct
id|sndrv_seq_addr
id|dest
suffix:semicolon
multiline_comment|/* Address for REMOVE_DEST */
DECL|member|channel
r_int
r_char
id|channel
suffix:semicolon
multiline_comment|/* Channel for REMOVE_DEST */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* For REMOVE_EVENT_TYPE */
DECL|member|tag
r_char
id|tag
suffix:semicolon
multiline_comment|/* Tag for REMOVE_TAG */
DECL|member|reserved
r_int
id|reserved
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* To allow for future binary compatibility */
)brace
suffix:semicolon
multiline_comment|/* known port numbers */
DECL|macro|SNDRV_SEQ_PORT_SYSTEM_TIMER
mdefine_line|#define SNDRV_SEQ_PORT_SYSTEM_TIMER&t;0
DECL|macro|SNDRV_SEQ_PORT_SYSTEM_ANNOUNCE
mdefine_line|#define SNDRV_SEQ_PORT_SYSTEM_ANNOUNCE&t;1
multiline_comment|/* port capabilities (32 bits) */
DECL|macro|SNDRV_SEQ_PORT_CAP_READ
mdefine_line|#define SNDRV_SEQ_PORT_CAP_READ&t;&t;(1&lt;&lt;0)&t;/* readable from this port */
DECL|macro|SNDRV_SEQ_PORT_CAP_WRITE
mdefine_line|#define SNDRV_SEQ_PORT_CAP_WRITE&t;(1&lt;&lt;1)&t;/* writable to this port */
DECL|macro|SNDRV_SEQ_PORT_CAP_SYNC_READ
mdefine_line|#define SNDRV_SEQ_PORT_CAP_SYNC_READ&t;(1&lt;&lt;2)
DECL|macro|SNDRV_SEQ_PORT_CAP_SYNC_WRITE
mdefine_line|#define SNDRV_SEQ_PORT_CAP_SYNC_WRITE&t;(1&lt;&lt;3)
DECL|macro|SNDRV_SEQ_PORT_CAP_DUPLEX
mdefine_line|#define SNDRV_SEQ_PORT_CAP_DUPLEX&t;(1&lt;&lt;4)
DECL|macro|SNDRV_SEQ_PORT_CAP_SUBS_READ
mdefine_line|#define SNDRV_SEQ_PORT_CAP_SUBS_READ&t;(1&lt;&lt;5)&t;/* allow read subscription */
DECL|macro|SNDRV_SEQ_PORT_CAP_SUBS_WRITE
mdefine_line|#define SNDRV_SEQ_PORT_CAP_SUBS_WRITE&t;(1&lt;&lt;6)&t;/* allow write subscription */
DECL|macro|SNDRV_SEQ_PORT_CAP_NO_EXPORT
mdefine_line|#define SNDRV_SEQ_PORT_CAP_NO_EXPORT&t;(1&lt;&lt;7)&t;/* routing not allowed */
multiline_comment|/* port type */
DECL|macro|SNDRV_SEQ_PORT_TYPE_SPECIFIC
mdefine_line|#define SNDRV_SEQ_PORT_TYPE_SPECIFIC&t;(1&lt;&lt;0)&t;/* hardware specific */
DECL|macro|SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC
mdefine_line|#define SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC (1&lt;&lt;1)&t;/* generic MIDI device */
DECL|macro|SNDRV_SEQ_PORT_TYPE_MIDI_GM
mdefine_line|#define SNDRV_SEQ_PORT_TYPE_MIDI_GM&t;(1&lt;&lt;2)&t;/* General MIDI compatible device */
DECL|macro|SNDRV_SEQ_PORT_TYPE_MIDI_GS
mdefine_line|#define SNDRV_SEQ_PORT_TYPE_MIDI_GS&t;(1&lt;&lt;3)&t;/* GS compatible device */
DECL|macro|SNDRV_SEQ_PORT_TYPE_MIDI_XG
mdefine_line|#define SNDRV_SEQ_PORT_TYPE_MIDI_XG&t;(1&lt;&lt;4)&t;/* XG compatible device */
DECL|macro|SNDRV_SEQ_PORT_TYPE_MIDI_MT32
mdefine_line|#define SNDRV_SEQ_PORT_TYPE_MIDI_MT32&t;(1&lt;&lt;5)&t;/* MT-32 compatible device */
multiline_comment|/* other standards...*/
DECL|macro|SNDRV_SEQ_PORT_TYPE_SYNTH
mdefine_line|#define SNDRV_SEQ_PORT_TYPE_SYNTH&t;(1&lt;&lt;10)&t;/* Synth device */
DECL|macro|SNDRV_SEQ_PORT_TYPE_DIRECT_SAMPLE
mdefine_line|#define SNDRV_SEQ_PORT_TYPE_DIRECT_SAMPLE (1&lt;&lt;11)&t;/* Sampling device (support sample download) */
DECL|macro|SNDRV_SEQ_PORT_TYPE_SAMPLE
mdefine_line|#define SNDRV_SEQ_PORT_TYPE_SAMPLE&t;(1&lt;&lt;12)&t;/* Sampling device (sample can be downloaded at any time) */
multiline_comment|/*...*/
DECL|macro|SNDRV_SEQ_PORT_TYPE_APPLICATION
mdefine_line|#define SNDRV_SEQ_PORT_TYPE_APPLICATION&t;(1&lt;&lt;20)&t;/* application (sequencer/editor) */
multiline_comment|/* misc. conditioning flags */
DECL|macro|SNDRV_SEQ_PORT_FLG_GIVEN_PORT
mdefine_line|#define SNDRV_SEQ_PORT_FLG_GIVEN_PORT&t;(1&lt;&lt;0)
DECL|struct|sndrv_seq_port_info
r_struct
id|sndrv_seq_port_info
(brace
DECL|member|addr
r_struct
id|sndrv_seq_addr
id|addr
suffix:semicolon
multiline_comment|/* client/port numbers */
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* port name */
DECL|member|capability
r_int
r_int
id|capability
suffix:semicolon
multiline_comment|/* port capability bits */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* port type bits */
DECL|member|midi_channels
r_int
id|midi_channels
suffix:semicolon
multiline_comment|/* channels per MIDI port */
DECL|member|midi_voices
r_int
id|midi_voices
suffix:semicolon
multiline_comment|/* voices per MIDI port */
DECL|member|synth_voices
r_int
id|synth_voices
suffix:semicolon
multiline_comment|/* voices per SYNTH port */
DECL|member|read_use
r_int
id|read_use
suffix:semicolon
multiline_comment|/* R/O: subscribers for output (from this port) */
DECL|member|write_use
r_int
id|write_use
suffix:semicolon
multiline_comment|/* R/O: subscribers for input (to this port) */
DECL|member|kernel
r_void
op_star
id|kernel
suffix:semicolon
multiline_comment|/* reserved for kernel use (must be NULL) */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* misc. conditioning */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|60
)braket
suffix:semicolon
multiline_comment|/* for future use */
)brace
suffix:semicolon
multiline_comment|/* queue flags */
DECL|macro|SNDRV_SEQ_QUEUE_FLG_SYNC
mdefine_line|#define SNDRV_SEQ_QUEUE_FLG_SYNC&t;(1&lt;&lt;0)&t;/* sync enabled */
multiline_comment|/* queue information */
DECL|struct|sndrv_seq_queue_info
r_struct
id|sndrv_seq_queue_info
(brace
DECL|member|queue
r_int
id|queue
suffix:semicolon
multiline_comment|/* queue id */
multiline_comment|/*&n;&t; *  security settings, only owner of this queue can start/stop timer&n;&t; *  etc. if the queue is locked for other clients&n;&t; */
DECL|member|owner
r_int
id|owner
suffix:semicolon
multiline_comment|/* client id for owner of the queue */
DECL|member|locked
r_int
id|locked
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* timing queue locked for other queues */
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* name of this queue */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* flags */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|60
)braket
suffix:semicolon
multiline_comment|/* for future use */
)brace
suffix:semicolon
multiline_comment|/* queue info/status */
DECL|struct|sndrv_seq_queue_status
r_struct
id|sndrv_seq_queue_status
(brace
DECL|member|queue
r_int
id|queue
suffix:semicolon
multiline_comment|/* queue id */
DECL|member|events
r_int
id|events
suffix:semicolon
multiline_comment|/* read-only - queue size */
DECL|member|tick
id|sndrv_seq_tick_time_t
id|tick
suffix:semicolon
multiline_comment|/* current tick */
DECL|member|time
r_struct
id|sndrv_seq_real_time
id|time
suffix:semicolon
multiline_comment|/* current time */
DECL|member|running
r_int
id|running
suffix:semicolon
multiline_comment|/* running state of queue */
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* various flags */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* for the future */
)brace
suffix:semicolon
multiline_comment|/* queue tempo */
DECL|struct|sndrv_seq_queue_tempo
r_struct
id|sndrv_seq_queue_tempo
(brace
DECL|member|queue
r_int
id|queue
suffix:semicolon
multiline_comment|/* sequencer queue */
DECL|member|tempo
r_int
r_int
id|tempo
suffix:semicolon
multiline_comment|/* current tempo, us/tick */
DECL|member|ppq
r_int
id|ppq
suffix:semicolon
multiline_comment|/* time resolution, ticks/quarter */
DECL|member|skew_value
r_int
r_int
id|skew_value
suffix:semicolon
multiline_comment|/* queue skew */
DECL|member|skew_base
r_int
r_int
id|skew_base
suffix:semicolon
multiline_comment|/* queue skew base */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* for the future */
)brace
suffix:semicolon
multiline_comment|/* sequencer timer sources */
DECL|macro|SNDRV_SEQ_TIMER_ALSA
mdefine_line|#define SNDRV_SEQ_TIMER_ALSA&t;&t;0&t;/* ALSA timer */
DECL|macro|SNDRV_SEQ_TIMER_MIDI_CLOCK
mdefine_line|#define SNDRV_SEQ_TIMER_MIDI_CLOCK&t;1&t;/* Midi Clock (CLOCK event) */
DECL|macro|SNDRV_SEQ_TIMER_MIDI_TICK
mdefine_line|#define SNDRV_SEQ_TIMER_MIDI_TICK&t;2&t;/* Midi Timer Tick (TICK event) */
multiline_comment|/* queue timer info */
DECL|struct|sndrv_seq_queue_timer
r_struct
id|sndrv_seq_queue_timer
(brace
DECL|member|queue
r_int
id|queue
suffix:semicolon
multiline_comment|/* sequencer queue */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* source timer type */
r_union
(brace
r_struct
(brace
DECL|member|id
r_struct
id|sndrv_timer_id
id|id
suffix:semicolon
multiline_comment|/* ALSA&squot;s timer ID */
DECL|member|resolution
r_int
r_int
id|resolution
suffix:semicolon
multiline_comment|/* resolution in Hz */
DECL|member|alsa
)brace
id|alsa
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|reserved
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* for the future use */
)brace
suffix:semicolon
DECL|struct|sndrv_seq_queue_client
r_struct
id|sndrv_seq_queue_client
(brace
DECL|member|queue
r_int
id|queue
suffix:semicolon
multiline_comment|/* sequencer queue */
DECL|member|client
r_int
id|client
suffix:semicolon
multiline_comment|/* sequencer client */
DECL|member|used
r_int
id|used
suffix:semicolon
multiline_comment|/* queue is used with this client&n;&t;&t;&t;&t;   (must be set for accepting events) */
multiline_comment|/* per client watermarks */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* for future use */
)brace
suffix:semicolon
DECL|macro|SNDRV_SEQ_PORT_SUBS_EXCLUSIVE
mdefine_line|#define SNDRV_SEQ_PORT_SUBS_EXCLUSIVE&t;(1&lt;&lt;0)&t;/* exclusive connection */
DECL|macro|SNDRV_SEQ_PORT_SUBS_TIMESTAMP
mdefine_line|#define SNDRV_SEQ_PORT_SUBS_TIMESTAMP&t;(1&lt;&lt;1)
DECL|macro|SNDRV_SEQ_PORT_SUBS_TIME_REAL
mdefine_line|#define SNDRV_SEQ_PORT_SUBS_TIME_REAL&t;(1&lt;&lt;2)
DECL|struct|sndrv_seq_port_subscribe
r_struct
id|sndrv_seq_port_subscribe
(brace
DECL|member|sender
r_struct
id|sndrv_seq_addr
id|sender
suffix:semicolon
multiline_comment|/* sender address */
DECL|member|dest
r_struct
id|sndrv_seq_addr
id|dest
suffix:semicolon
multiline_comment|/* destination address */
DECL|member|voices
r_int
r_int
id|voices
suffix:semicolon
multiline_comment|/* number of voices to be allocated (0 = don&squot;t care) */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* modes */
DECL|member|queue
r_int
r_char
id|queue
suffix:semicolon
multiline_comment|/* input time-stamp queue (optional) */
DECL|member|pad
r_int
r_char
id|pad
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* type of query subscription */
DECL|macro|SNDRV_SEQ_QUERY_SUBS_READ
mdefine_line|#define SNDRV_SEQ_QUERY_SUBS_READ&t;0
DECL|macro|SNDRV_SEQ_QUERY_SUBS_WRITE
mdefine_line|#define SNDRV_SEQ_QUERY_SUBS_WRITE&t;1
DECL|struct|sndrv_seq_query_subs
r_struct
id|sndrv_seq_query_subs
(brace
DECL|member|root
r_struct
id|sndrv_seq_addr
id|root
suffix:semicolon
multiline_comment|/* client/port id to be searched */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* READ or WRITE */
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* 0..N-1 */
DECL|member|num_subs
r_int
id|num_subs
suffix:semicolon
multiline_comment|/* R/O: number of subscriptions on this port */
DECL|member|addr
r_struct
id|sndrv_seq_addr
id|addr
suffix:semicolon
multiline_comment|/* R/O: result */
DECL|member|queue
r_int
r_char
id|queue
suffix:semicolon
multiline_comment|/* R/O: result */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* R/O: result */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* for future use */
)brace
suffix:semicolon
multiline_comment|/*&n; *  Instrument abstraction layer&n; *     - based on events&n; */
multiline_comment|/* instrument types */
DECL|macro|SNDRV_SEQ_INSTR_ATYPE_DATA
mdefine_line|#define SNDRV_SEQ_INSTR_ATYPE_DATA&t;0&t;/* instrument data */
DECL|macro|SNDRV_SEQ_INSTR_ATYPE_ALIAS
mdefine_line|#define SNDRV_SEQ_INSTR_ATYPE_ALIAS&t;1&t;/* instrument alias */
multiline_comment|/* instrument ASCII identifiers */
DECL|macro|SNDRV_SEQ_INSTR_ID_DLS1
mdefine_line|#define SNDRV_SEQ_INSTR_ID_DLS1&t;&t;&quot;DLS1&quot;
DECL|macro|SNDRV_SEQ_INSTR_ID_DLS2
mdefine_line|#define SNDRV_SEQ_INSTR_ID_DLS2&t;&t;&quot;DLS2&quot;
DECL|macro|SNDRV_SEQ_INSTR_ID_SIMPLE
mdefine_line|#define SNDRV_SEQ_INSTR_ID_SIMPLE&t;&quot;Simple Wave&quot;
DECL|macro|SNDRV_SEQ_INSTR_ID_SOUNDFONT
mdefine_line|#define SNDRV_SEQ_INSTR_ID_SOUNDFONT&t;&quot;SoundFont&quot;
DECL|macro|SNDRV_SEQ_INSTR_ID_GUS_PATCH
mdefine_line|#define SNDRV_SEQ_INSTR_ID_GUS_PATCH&t;&quot;GUS Patch&quot;
DECL|macro|SNDRV_SEQ_INSTR_ID_INTERWAVE
mdefine_line|#define SNDRV_SEQ_INSTR_ID_INTERWAVE&t;&quot;InterWave FFFF&quot;
DECL|macro|SNDRV_SEQ_INSTR_ID_OPL2_3
mdefine_line|#define SNDRV_SEQ_INSTR_ID_OPL2_3&t;&quot;OPL2/3 FM&quot;
DECL|macro|SNDRV_SEQ_INSTR_ID_OPL4
mdefine_line|#define SNDRV_SEQ_INSTR_ID_OPL4&t;&t;&quot;OPL4&quot;
multiline_comment|/* instrument types */
DECL|macro|SNDRV_SEQ_INSTR_TYPE0_DLS1
mdefine_line|#define SNDRV_SEQ_INSTR_TYPE0_DLS1&t;(1&lt;&lt;0)&t;/* MIDI DLS v1 */
DECL|macro|SNDRV_SEQ_INSTR_TYPE0_DLS2
mdefine_line|#define SNDRV_SEQ_INSTR_TYPE0_DLS2&t;(1&lt;&lt;1)&t;/* MIDI DLS v2 */
DECL|macro|SNDRV_SEQ_INSTR_TYPE1_SIMPLE
mdefine_line|#define SNDRV_SEQ_INSTR_TYPE1_SIMPLE&t;(1&lt;&lt;0)&t;/* Simple Wave */
DECL|macro|SNDRV_SEQ_INSTR_TYPE1_SOUNDFONT
mdefine_line|#define SNDRV_SEQ_INSTR_TYPE1_SOUNDFONT&t;(1&lt;&lt;1)&t;/* EMU SoundFont */
DECL|macro|SNDRV_SEQ_INSTR_TYPE1_GUS_PATCH
mdefine_line|#define SNDRV_SEQ_INSTR_TYPE1_GUS_PATCH&t;(1&lt;&lt;2)&t;/* Gravis UltraSound Patch */
DECL|macro|SNDRV_SEQ_INSTR_TYPE1_INTERWAVE
mdefine_line|#define SNDRV_SEQ_INSTR_TYPE1_INTERWAVE&t;(1&lt;&lt;3)&t;/* InterWave FFFF */
DECL|macro|SNDRV_SEQ_INSTR_TYPE2_OPL2_3
mdefine_line|#define SNDRV_SEQ_INSTR_TYPE2_OPL2_3&t;(1&lt;&lt;0)&t;/* Yamaha OPL2/3 FM */
DECL|macro|SNDRV_SEQ_INSTR_TYPE2_OPL4
mdefine_line|#define SNDRV_SEQ_INSTR_TYPE2_OPL4&t;(1&lt;&lt;1)&t;/* Yamaha OPL4 */
multiline_comment|/* put commands */
DECL|macro|SNDRV_SEQ_INSTR_PUT_CMD_CREATE
mdefine_line|#define SNDRV_SEQ_INSTR_PUT_CMD_CREATE&t;0
DECL|macro|SNDRV_SEQ_INSTR_PUT_CMD_REPLACE
mdefine_line|#define SNDRV_SEQ_INSTR_PUT_CMD_REPLACE&t;1
DECL|macro|SNDRV_SEQ_INSTR_PUT_CMD_MODIFY
mdefine_line|#define SNDRV_SEQ_INSTR_PUT_CMD_MODIFY&t;2
DECL|macro|SNDRV_SEQ_INSTR_PUT_CMD_ADD
mdefine_line|#define SNDRV_SEQ_INSTR_PUT_CMD_ADD&t;3
DECL|macro|SNDRV_SEQ_INSTR_PUT_CMD_REMOVE
mdefine_line|#define SNDRV_SEQ_INSTR_PUT_CMD_REMOVE&t;4
multiline_comment|/* get commands */
DECL|macro|SNDRV_SEQ_INSTR_GET_CMD_FULL
mdefine_line|#define SNDRV_SEQ_INSTR_GET_CMD_FULL&t;0
DECL|macro|SNDRV_SEQ_INSTR_GET_CMD_PARTIAL
mdefine_line|#define SNDRV_SEQ_INSTR_GET_CMD_PARTIAL&t;1
multiline_comment|/* query flags */
DECL|macro|SNDRV_SEQ_INSTR_QUERY_FOLLOW_ALIAS
mdefine_line|#define SNDRV_SEQ_INSTR_QUERY_FOLLOW_ALIAS (1&lt;&lt;0)
multiline_comment|/* free commands */
DECL|macro|SNDRV_SEQ_INSTR_FREE_CMD_ALL
mdefine_line|#define SNDRV_SEQ_INSTR_FREE_CMD_ALL&t;&t;0
DECL|macro|SNDRV_SEQ_INSTR_FREE_CMD_PRIVATE
mdefine_line|#define SNDRV_SEQ_INSTR_FREE_CMD_PRIVATE&t;1
DECL|macro|SNDRV_SEQ_INSTR_FREE_CMD_CLUSTER
mdefine_line|#define SNDRV_SEQ_INSTR_FREE_CMD_CLUSTER&t;2
DECL|macro|SNDRV_SEQ_INSTR_FREE_CMD_SINGLE
mdefine_line|#define SNDRV_SEQ_INSTR_FREE_CMD_SINGLE&t;&t;3
multiline_comment|/* size of ROM/RAM */
DECL|typedef|sndrv_seq_instr_size_t
r_typedef
r_int
r_int
id|sndrv_seq_instr_size_t
suffix:semicolon
multiline_comment|/* INSTR_INFO */
DECL|struct|sndrv_seq_instr_info
r_struct
id|sndrv_seq_instr_info
(brace
DECL|member|result
r_int
id|result
suffix:semicolon
multiline_comment|/* operation result */
DECL|member|formats
r_int
r_int
id|formats
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* bitmap of supported formats */
DECL|member|ram_count
r_int
id|ram_count
suffix:semicolon
multiline_comment|/* count of RAM banks */
DECL|member|ram_sizes
id|sndrv_seq_instr_size_t
id|ram_sizes
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* size of RAM banks */
DECL|member|rom_count
r_int
id|rom_count
suffix:semicolon
multiline_comment|/* count of ROM banks */
DECL|member|rom_sizes
id|sndrv_seq_instr_size_t
id|rom_sizes
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* size of ROM banks */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* INSTR_STATUS */
DECL|struct|sndrv_seq_instr_status
r_struct
id|sndrv_seq_instr_status
(brace
DECL|member|result
r_int
id|result
suffix:semicolon
multiline_comment|/* operation result */
DECL|member|free_ram
id|sndrv_seq_instr_size_t
id|free_ram
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* free RAM in banks */
DECL|member|instrument_count
r_int
id|instrument_count
suffix:semicolon
multiline_comment|/* count of downloaded instruments */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* INSTR_FORMAT_INFO */
DECL|struct|sndrv_seq_instr_format_info
r_struct
id|sndrv_seq_instr_format_info
(brace
DECL|member|format
r_char
id|format
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* format identifier - SNDRV_SEQ_INSTR_ID_* */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* max data length (without this structure) */
)brace
suffix:semicolon
DECL|struct|sndrv_seq_instr_format_info_result
r_struct
id|sndrv_seq_instr_format_info_result
(brace
DECL|member|result
r_int
id|result
suffix:semicolon
multiline_comment|/* operation result */
DECL|member|format
r_char
id|format
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* format identifier */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* filled data length (without this structure) */
)brace
suffix:semicolon
multiline_comment|/* instrument data */
DECL|struct|sndrv_seq_instr_data
r_struct
id|sndrv_seq_instr_data
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* instrument name */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* for the future use */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* instrument type */
r_union
(brace
DECL|member|format
r_char
id|format
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* format identifier */
DECL|member|alias
r_struct
id|sndrv_seq_instr
id|alias
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* INSTR_PUT/GET, data are stored in one block (extended or IPC), header + data */
DECL|struct|sndrv_seq_instr_header
r_struct
id|sndrv_seq_instr_header
(brace
r_union
(brace
DECL|member|instr
r_struct
id|sndrv_seq_instr
id|instr
suffix:semicolon
DECL|member|cluster
id|sndrv_seq_instr_cluster_t
id|cluster
suffix:semicolon
DECL|member|id
)brace
id|id
suffix:semicolon
multiline_comment|/* instrument identifier */
DECL|member|cmd
r_int
r_int
id|cmd
suffix:semicolon
multiline_comment|/* get/put/free command */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* query flags (only for get) */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* real instrument data length (without header) */
DECL|member|result
r_int
id|result
suffix:semicolon
multiline_comment|/* operation result */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* for the future */
DECL|member|data
r_struct
id|sndrv_seq_instr_data
id|data
suffix:semicolon
multiline_comment|/* instrument data (for put/get result) */
)brace
suffix:semicolon
multiline_comment|/* INSTR_CLUSTER_SET */
DECL|struct|sndrv_seq_instr_cluster_set
r_struct
id|sndrv_seq_instr_cluster_set
(brace
DECL|member|cluster
id|sndrv_seq_instr_cluster_t
id|cluster
suffix:semicolon
multiline_comment|/* cluster identifier */
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* cluster name */
DECL|member|priority
r_int
id|priority
suffix:semicolon
multiline_comment|/* cluster priority */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* for the future use */
)brace
suffix:semicolon
multiline_comment|/* INSTR_CLUSTER_GET */
DECL|struct|sndrv_seq_instr_cluster_get
r_struct
id|sndrv_seq_instr_cluster_get
(brace
DECL|member|cluster
id|sndrv_seq_instr_cluster_t
id|cluster
suffix:semicolon
multiline_comment|/* cluster identifier */
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* cluster name */
DECL|member|priority
r_int
id|priority
suffix:semicolon
multiline_comment|/* cluster priority */
DECL|member|reserved
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* for the future use */
)brace
suffix:semicolon
multiline_comment|/*&n; *  IOCTL commands&n; */
DECL|macro|SNDRV_SEQ_IOCTL_PVERSION
mdefine_line|#define SNDRV_SEQ_IOCTL_PVERSION&t;_IOR (&squot;S&squot;, 0x00, int)
DECL|macro|SNDRV_SEQ_IOCTL_CLIENT_ID
mdefine_line|#define SNDRV_SEQ_IOCTL_CLIENT_ID&t;_IOR (&squot;S&squot;, 0x01, int)
DECL|macro|SNDRV_SEQ_IOCTL_SYSTEM_INFO
mdefine_line|#define SNDRV_SEQ_IOCTL_SYSTEM_INFO&t;_IOWR(&squot;S&squot;, 0x02, struct sndrv_seq_system_info)
DECL|macro|SNDRV_SEQ_IOCTL_GET_CLIENT_INFO
mdefine_line|#define SNDRV_SEQ_IOCTL_GET_CLIENT_INFO&t;_IOWR(&squot;S&squot;, 0x10, struct sndrv_seq_client_info)
DECL|macro|SNDRV_SEQ_IOCTL_SET_CLIENT_INFO
mdefine_line|#define SNDRV_SEQ_IOCTL_SET_CLIENT_INFO&t;_IOW (&squot;S&squot;, 0x11, struct sndrv_seq_client_info)
DECL|macro|SNDRV_SEQ_IOCTL_CREATE_PORT
mdefine_line|#define SNDRV_SEQ_IOCTL_CREATE_PORT&t;_IOWR(&squot;S&squot;, 0x20, struct sndrv_seq_port_info)
DECL|macro|SNDRV_SEQ_IOCTL_DELETE_PORT
mdefine_line|#define SNDRV_SEQ_IOCTL_DELETE_PORT&t;_IOW (&squot;S&squot;, 0x21, struct sndrv_seq_port_info)
DECL|macro|SNDRV_SEQ_IOCTL_GET_PORT_INFO
mdefine_line|#define SNDRV_SEQ_IOCTL_GET_PORT_INFO&t;_IOWR(&squot;S&squot;, 0x22, struct sndrv_seq_port_info)
DECL|macro|SNDRV_SEQ_IOCTL_SET_PORT_INFO
mdefine_line|#define SNDRV_SEQ_IOCTL_SET_PORT_INFO&t;_IOW (&squot;S&squot;, 0x23, struct sndrv_seq_port_info)
DECL|macro|SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT
mdefine_line|#define SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT&t;_IOW (&squot;S&squot;, 0x30, struct sndrv_seq_port_subscribe)
DECL|macro|SNDRV_SEQ_IOCTL_UNSUBSCRIBE_PORT
mdefine_line|#define SNDRV_SEQ_IOCTL_UNSUBSCRIBE_PORT&t;_IOW (&squot;S&squot;, 0x31, struct sndrv_seq_port_subscribe)
DECL|macro|SNDRV_SEQ_IOCTL_CREATE_QUEUE
mdefine_line|#define SNDRV_SEQ_IOCTL_CREATE_QUEUE&t;_IOWR(&squot;S&squot;, 0x32, struct sndrv_seq_queue_info)
DECL|macro|SNDRV_SEQ_IOCTL_DELETE_QUEUE
mdefine_line|#define SNDRV_SEQ_IOCTL_DELETE_QUEUE&t;_IOW (&squot;S&squot;, 0x33, struct sndrv_seq_queue_info)
DECL|macro|SNDRV_SEQ_IOCTL_GET_QUEUE_INFO
mdefine_line|#define SNDRV_SEQ_IOCTL_GET_QUEUE_INFO&t;_IOWR(&squot;S&squot;, 0x34, struct sndrv_seq_queue_info)
DECL|macro|SNDRV_SEQ_IOCTL_SET_QUEUE_INFO
mdefine_line|#define SNDRV_SEQ_IOCTL_SET_QUEUE_INFO&t;_IOWR(&squot;S&squot;, 0x35, struct sndrv_seq_queue_info)
DECL|macro|SNDRV_SEQ_IOCTL_GET_NAMED_QUEUE
mdefine_line|#define SNDRV_SEQ_IOCTL_GET_NAMED_QUEUE&t;_IOWR(&squot;S&squot;, 0x36, struct sndrv_seq_queue_info)
DECL|macro|SNDRV_SEQ_IOCTL_GET_QUEUE_STATUS
mdefine_line|#define SNDRV_SEQ_IOCTL_GET_QUEUE_STATUS&t;_IOWR(&squot;S&squot;, 0x40, struct sndrv_seq_queue_status)
DECL|macro|SNDRV_SEQ_IOCTL_GET_QUEUE_TEMPO
mdefine_line|#define SNDRV_SEQ_IOCTL_GET_QUEUE_TEMPO&t;_IOWR(&squot;S&squot;, 0x41, struct sndrv_seq_queue_tempo)
DECL|macro|SNDRV_SEQ_IOCTL_SET_QUEUE_TEMPO
mdefine_line|#define SNDRV_SEQ_IOCTL_SET_QUEUE_TEMPO&t;_IOW (&squot;S&squot;, 0x42, struct sndrv_seq_queue_tempo)
DECL|macro|SNDRV_SEQ_IOCTL_GET_QUEUE_OWNER
mdefine_line|#define SNDRV_SEQ_IOCTL_GET_QUEUE_OWNER&t;_IOWR(&squot;S&squot;, 0x43, struct sndrv_seq_queue_owner)
DECL|macro|SNDRV_SEQ_IOCTL_SET_QUEUE_OWNER
mdefine_line|#define SNDRV_SEQ_IOCTL_SET_QUEUE_OWNER&t;_IOW (&squot;S&squot;, 0x44, struct sndrv_seq_queue_owner)
DECL|macro|SNDRV_SEQ_IOCTL_GET_QUEUE_TIMER
mdefine_line|#define SNDRV_SEQ_IOCTL_GET_QUEUE_TIMER&t;_IOWR(&squot;S&squot;, 0x45, struct sndrv_seq_queue_timer)
DECL|macro|SNDRV_SEQ_IOCTL_SET_QUEUE_TIMER
mdefine_line|#define SNDRV_SEQ_IOCTL_SET_QUEUE_TIMER&t;_IOW (&squot;S&squot;, 0x46, struct sndrv_seq_queue_timer)
multiline_comment|/* XXX&n;#define SNDRV_SEQ_IOCTL_GET_QUEUE_SYNC&t;_IOWR(&squot;S&squot;, 0x53, struct sndrv_seq_queue_sync)&n;#define SNDRV_SEQ_IOCTL_SET_QUEUE_SYNC&t;_IOW (&squot;S&squot;, 0x54, struct sndrv_seq_queue_sync)&n;*/
DECL|macro|SNDRV_SEQ_IOCTL_GET_QUEUE_CLIENT
mdefine_line|#define SNDRV_SEQ_IOCTL_GET_QUEUE_CLIENT&t;_IOWR(&squot;S&squot;, 0x49, struct sndrv_seq_queue_client)
DECL|macro|SNDRV_SEQ_IOCTL_SET_QUEUE_CLIENT
mdefine_line|#define SNDRV_SEQ_IOCTL_SET_QUEUE_CLIENT&t;_IOW (&squot;S&squot;, 0x4a, struct sndrv_seq_queue_client)
DECL|macro|SNDRV_SEQ_IOCTL_GET_CLIENT_POOL
mdefine_line|#define SNDRV_SEQ_IOCTL_GET_CLIENT_POOL&t;_IOWR(&squot;S&squot;, 0x4b, struct sndrv_seq_client_pool)
DECL|macro|SNDRV_SEQ_IOCTL_SET_CLIENT_POOL
mdefine_line|#define SNDRV_SEQ_IOCTL_SET_CLIENT_POOL&t;_IOW (&squot;S&squot;, 0x4c, struct sndrv_seq_client_pool)
DECL|macro|SNDRV_SEQ_IOCTL_REMOVE_EVENTS
mdefine_line|#define SNDRV_SEQ_IOCTL_REMOVE_EVENTS&t;_IOW (&squot;S&squot;, 0x4e, struct sndrv_seq_remove_events)
DECL|macro|SNDRV_SEQ_IOCTL_QUERY_SUBS
mdefine_line|#define SNDRV_SEQ_IOCTL_QUERY_SUBS&t;_IOWR(&squot;S&squot;, 0x4f, struct sndrv_seq_query_subs)
DECL|macro|SNDRV_SEQ_IOCTL_GET_SUBSCRIPTION
mdefine_line|#define SNDRV_SEQ_IOCTL_GET_SUBSCRIPTION&t;_IOWR(&squot;S&squot;, 0x50, struct sndrv_seq_port_subscribe)
DECL|macro|SNDRV_SEQ_IOCTL_QUERY_NEXT_CLIENT
mdefine_line|#define SNDRV_SEQ_IOCTL_QUERY_NEXT_CLIENT&t;_IOWR(&squot;S&squot;, 0x51, struct sndrv_seq_client_info)
DECL|macro|SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT
mdefine_line|#define SNDRV_SEQ_IOCTL_QUERY_NEXT_PORT&t;_IOWR(&squot;S&squot;, 0x52, struct sndrv_seq_port_info)
macro_line|#endif /* __SOUND_ASEQUENCER_H */
eof
