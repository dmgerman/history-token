multiline_comment|/*&n; *  The driver for the Cirrus Logic&squot;s Sound Fusion CS46XX based soundcards&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; *&n; * NOTE: comments are copy/paste from cwcemb80.lst &n; * provided by Tom Woller at Cirrus (my only&n; * documentation about the SP OS running inside&n; * the DSP) &n; */
macro_line|#ifndef __CS46XX_DSP_SCB_TYPES_H__
DECL|macro|__CS46XX_DSP_SCB_TYPES_H__
mdefine_line|#define __CS46XX_DSP_SCB_TYPES_H__
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#ifndef ___DSP_DUAL_16BIT_ALLOC
macro_line|#if   defined(__LITTLE_ENDIAN)
DECL|macro|___DSP_DUAL_16BIT_ALLOC
mdefine_line|#define ___DSP_DUAL_16BIT_ALLOC(a,b) u16 a; u16 b;
macro_line|#elif defined(__BIG_ENDIAN)
DECL|macro|___DSP_DUAL_16BIT_ALLOC
mdefine_line|#define ___DSP_DUAL_16BIT_ALLOC(a,b) u16 b; u16 a;
macro_line|#else
macro_line|#error Not __LITTLE_ENDIAN and not __BIG_ENDIAN, then what ???
macro_line|#endif
macro_line|#endif
multiline_comment|/* This structs are used internally by the SP */
DECL|struct|_basic_dma_req_t
r_typedef
r_struct
id|_basic_dma_req_t
(brace
multiline_comment|/* DMA Requestor Word 0 (DCW)  fields:&n;&n;&t;   31 [30-28]27  [26:24] 23 22 21 20 [19:18] [17:16] 15 14 13  12  11 10 9 8 7 6  [5:0]&n;&t;   _______________________________________________________________________________________&t;&n;&t;   |S| SBT  |D|  DBT    |wb|wb|  |  |  LS  |  SS   |Opt|Do|SSG|DSG|  |  | | | | | Dword   |&n;&t;   |H|_____ |H|_________|S_|D |__|__|______|_______|___|ne|__ |__ |__|__|_|_|_|_|_Count -1|&n;&t;*/
DECL|member|dcw
id|u32
id|dcw
suffix:semicolon
multiline_comment|/* DMA Control Word */
DECL|member|dmw
id|u32
id|dmw
suffix:semicolon
multiline_comment|/* DMA Mode Word */
DECL|member|saw
id|u32
id|saw
suffix:semicolon
multiline_comment|/* Source Address Word */
DECL|member|daw
id|u32
id|daw
suffix:semicolon
multiline_comment|/* Destination Address Word  */
DECL|typedef|basic_dma_req_t
)brace
id|basic_dma_req_t
suffix:semicolon
DECL|struct|_scatter_gather_ext_t
r_typedef
r_struct
id|_scatter_gather_ext_t
(brace
DECL|member|npaw
id|u32
id|npaw
suffix:semicolon
multiline_comment|/* Next-Page Address Word */
multiline_comment|/* DMA Requestor Word 5 (NPCW)  fields:&n;     &n;&t;   31-30 29 28          [27:16]              [15:12]             [11:3]                [2:0] &t;&t;&t;&t;&n;&t;   _________________________________________________________________________________________&t;&n;&t;   |SV  |LE|SE|   Sample-end byte offset   |         | Page-map entry offset for next  |    | &n;&t;   |page|__|__| ___________________________|_________|__page, if !sample-end___________|____|&n;&t;*/
DECL|member|npcw
id|u32
id|npcw
suffix:semicolon
multiline_comment|/* Next-Page Control Word */
DECL|member|lbaw
id|u32
id|lbaw
suffix:semicolon
multiline_comment|/* Loop-Begin Address Word */
DECL|member|nplbaw
id|u32
id|nplbaw
suffix:semicolon
multiline_comment|/* Next-Page after Loop-Begin Address Word */
DECL|member|sgaw
id|u32
id|sgaw
suffix:semicolon
multiline_comment|/* Scatter/Gather Address Word */
DECL|typedef|scatter_gather_ext_t
)brace
id|scatter_gather_ext_t
suffix:semicolon
DECL|struct|_volume_control_t
r_typedef
r_struct
id|_volume_control_t
(brace
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|rightTarg
comma
multiline_comment|/* Target volume for left &amp; right channels */
id|leftTarg
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|rightVol
comma
multiline_comment|/* Current left &amp; right channel volumes */
id|leftVol
)paren
DECL|typedef|volume_control_t
)brace
id|volume_control_t
suffix:semicolon
multiline_comment|/* Generic stream control block (SCB) structure definition */
DECL|struct|_generic_scb_t
r_typedef
r_struct
id|_generic_scb_t
(brace
multiline_comment|/* For streaming I/O, the DSP should never alter any words in the DMA&n;&t;   requestor or the scatter/gather extension.  Only ad hoc DMA request&n;&t;   streams are free to alter the requestor (currently only occur in the&n;&t;   DOS-based MIDI controller and in debugger-inserted code).&n;    &n;&t;   If an SCB does not have any associated DMA requestor, these 9 ints&n;&t;   may be freed for use by other tasks, but the pointer to the SCB must&n;&t;   still be such that the insOrd:nextSCB appear at offset 9 from the&n;&t;   SCB pointer.&n;     &n;&t;   Basic (non scatter/gather) DMA requestor (4 ints)&n;&t;*/
multiline_comment|/* Initialized by the host, only modified by DMA &n;&t;   R/O for the DSP task */
DECL|member|basic_req
id|basic_dma_req_t
id|basic_req
suffix:semicolon
multiline_comment|/* Optional */
multiline_comment|/* Scatter/gather DMA requestor extension   (5 ints) &n;&t;   Initialized by the host, only modified by DMA&n;&t;   DSP task never needs to even read these.&n;&t;*/
DECL|member|sg_ext
id|scatter_gather_ext_t
id|sg_ext
suffix:semicolon
multiline_comment|/* Optional */
multiline_comment|/* Sublist pointer &amp; next stream control block (SCB) link.&n;&t;   Initialized &amp; modified by the host R/O for the DSP task&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|next_scb
comma
multiline_comment|/* REQUIRED */
id|sub_list_ptr
multiline_comment|/* REQUIRED */
)paren
multiline_comment|/* Pointer to this tasks parameter block &amp; stream function pointer &n;&t;   Initialized by the host  R/O for the DSP task */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|entry_point
comma
multiline_comment|/* REQUIRED */
id|this_spb
multiline_comment|/* REQUIRED */
)paren
multiline_comment|/* rsConfig register for stream buffer (rsDMA reg. &n;&t;   is loaded from basicReq.daw for incoming streams, or &n;&t;   basicReq.saw, for outgoing streams) &n;&n;&t;   31 30 29  [28:24]     [23:16] 15 14 13 12 11 10 9 8 7 6  5      4      [3:0]&n;&t;   ______________________________________________________________________________&n;&t;   |DMA  |D|maxDMAsize| streamNum|dir|p|  |  |  |  | | |ds |shr 1|rev Cy | mod   |&n;&t;   |prio |_|__________|__________|___|_|__|__|__|__|_|_|___|_____|_______|_______|&n;&t;   31 30 29  [28:24]     [23:16] 15 14 13 12 11 10 9 8 7 6  5      4      [3:0]&n;&n;&n;&t;   Initialized by the host R/O for the DSP task&n;&t;*/
id|u32
id|strm_rs_config
suffix:semicolon
multiline_comment|/* REQUIRED */
singleline_comment|// 
multiline_comment|/* On mixer input streams: indicates mixer input stream configuration&n;&t;   On Tees, this is copied from the stream being snooped&n;&n;&t;   Stream sample pointer &amp; MAC-unit mode for this stream &n;     &n;&t;   Initialized by the host Updated by the DSP task&n;&t;*/
id|u32
id|strm_buf_ptr
suffix:semicolon
multiline_comment|/* REQUIRED  */
multiline_comment|/* On mixer input streams: points to next mixer input and is updated by the&n;                                   mixer subroutine in the &quot;parent&quot; DSP task&n;&t;&t;&t;&t;   (least-significant 16 bits are preserved, unused)&n;    &n;           On Tees, the pointer is copied from the stream being snooped on&n;&t;   initialization, and, subsequently, it is copied into the&n;&t;   stream being snooped.&n;&n;&t;   On wavetable/3D voices: the strmBufPtr will use all 32 bits to allow for&n;                                   fractional phase accumulation&n;&n;&t;   Fractional increment per output sample in the input sample buffer&n;&n;&t;   (Not used on mixer input streams &amp; redefined on Tees)&n;&t;   On wavetable/3D voices: this 32-bit word specifies the integer.fractional &n;&t;   increment per output sample.&n;&t;*/
DECL|member|strmPhiIncr
id|u32
id|strmPhiIncr
suffix:semicolon
multiline_comment|/* Standard stereo volume control&n;&t;   Initialized by the host (host updates target volumes) &n;&n;&t;   Current volumes update by the DSP task&n;&t;   On mixer input streams: required &amp; updated by the mixer subroutine in the&n;                                   &quot;parent&quot; DSP task&n;&n;&t;   On Tees, both current &amp; target volumes are copied up on initialization,&n;&t;   and, subsequently, the target volume is copied up while the current&n;&t;   volume is copied down.&n;     &n;&t;   These two 32-bit words are redefined for wavetable &amp; 3-D voices.    &n;&t;*/
DECL|member|vol_ctrl_t
id|volume_control_t
id|vol_ctrl_t
suffix:semicolon
multiline_comment|/* Optional */
DECL|typedef|generic_scb_t
)brace
id|generic_scb_t
suffix:semicolon
DECL|struct|_spos_control_block_t
r_typedef
r_struct
id|_spos_control_block_t
(brace
multiline_comment|/* WARNING: Certain items in this structure are modified by the host&n;&t;            Any dword that can be modified by the host, must not be&n;&t;&t;    modified by the SP as the host can only do atomic dword&n;&t;&t;    writes, and to do otherwise, even a read modify write, &n;&t;&t;    may lead to corrupted data on the SP.&n;  &n;&t;&t;    This rule does not apply to one off boot time initialisation prior to starting the SP&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
multiline_comment|/* First element on the Hyper forground task tree */
id|hfg_tree_root_ptr
comma
multiline_comment|/* HOST */
multiline_comment|/* First 3 dwords are written by the host and read-only on the DSP */
id|hfg_stack_base
multiline_comment|/* HOST */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
multiline_comment|/* Point to this data structure to enable easy access */
id|spos_cb_ptr
comma
multiline_comment|/* SP */
id|prev_task_tree_ptr
multiline_comment|/* SP &amp;&amp; HOST */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
multiline_comment|/* Currently Unused */
id|xxinterval_timer_period
comma
multiline_comment|/* Enable extension of SPOS data structure */
id|HFGSPB_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|xxnum_HFG_ticks_thisInterval
comma
multiline_comment|/* Modified by the DSP */
id|xxnum_tntervals
)paren
multiline_comment|/* Set by DSP upon encountering a trap (breakpoint) or a spurious&n;&t;   interrupt.  The host must clear this dword after reading it&n;&t;   upon receiving spInt1. */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|spurious_int_flag
comma
multiline_comment|/* (Host &amp; SP) Nature of the spurious interrupt */
id|trap_flag
multiline_comment|/* (Host &amp; SP) Nature of detected Trap */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|unused2
comma
id|invalid_IP_flag
multiline_comment|/* (Host &amp; SP ) Indicate detection of invalid instruction pointer */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
multiline_comment|/* pointer to forground task tree header for use in next task search */
id|fg_task_tree_hdr_ptr
comma
multiline_comment|/* HOST */
multiline_comment|/* Data structure for controlling synchronous link update */
id|hfg_sync_update_ptr
multiline_comment|/* HOST */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|begin_foreground_FCNT
comma
multiline_comment|/* SP */
multiline_comment|/* Place holder for holding sleep timing */
id|last_FCNT_before_sleep
multiline_comment|/* SP */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|unused7
comma
multiline_comment|/* SP */
id|next_task_treePtr
multiline_comment|/* SP */
)paren
id|u32
id|unused5
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|active_flags
comma
multiline_comment|/* SP */
multiline_comment|/* State flags, used to assist control of execution of Hyper Forground */
id|HFG_flags
multiline_comment|/* SP */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|unused9
comma
id|unused8
)paren
multiline_comment|/* Space for saving enough context so that we can set up enough &n;&t;   to save some more context.&n;&t;*/
id|u32
id|rFE_save_for_invalid_IP
suffix:semicolon
DECL|member|r32_save_for_spurious_int
id|u32
id|r32_save_for_spurious_int
suffix:semicolon
DECL|member|r32_save_for_trap
id|u32
id|r32_save_for_trap
suffix:semicolon
DECL|member|r32_save_for_HFG
id|u32
id|r32_save_for_HFG
suffix:semicolon
DECL|typedef|spos_control_block_t
)brace
id|spos_control_block_t
suffix:semicolon
multiline_comment|/* SPB for MIX_TO_OSTREAM algorithm family */
DECL|struct|_mix2_ostream_spb_t
r_typedef
r_struct
id|_mix2_ostream_spb_t
(brace
multiline_comment|/* 16b.16b integer.frac approximation to the&n;&t;   number of 3 sample triplets to output each&n;&t;   frame. (approximation must be floor, to&n;&t;   insure that the fractional error is always&n;&t;   positive)&n;&t;*/
DECL|member|outTripletsPerFrame
id|u32
id|outTripletsPerFrame
suffix:semicolon
multiline_comment|/* 16b.16b integer.frac accumulated number of&n;&t;   output triplets since the start of group &n;&t;*/
DECL|member|accumOutTriplets
id|u32
id|accumOutTriplets
suffix:semicolon
DECL|typedef|mix2_ostream_spb_t
)brace
id|mix2_ostream_spb_t
suffix:semicolon
multiline_comment|/* SCB for Timing master algorithm */
DECL|struct|_timing_master_scb_t
r_typedef
r_struct
id|_timing_master_scb_t
(brace
multiline_comment|/* First 12 dwords from generic_scb_t */
DECL|member|basic_req
id|basic_dma_req_t
id|basic_req
suffix:semicolon
multiline_comment|/* Optional */
DECL|member|sg_ext
id|scatter_gather_ext_t
id|sg_ext
suffix:semicolon
multiline_comment|/* Optional */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|next_scb
comma
multiline_comment|/* REQUIRED */
id|sub_list_ptr
multiline_comment|/* REQUIRED */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|entry_point
comma
multiline_comment|/* REQUIRED */
id|this_spb
multiline_comment|/* REQUIRED */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
multiline_comment|/* Initial values are 0000:xxxx */
id|reserved
comma
id|extra_sample_accum
)paren
multiline_comment|/* Initial values are xxxx:0000&n;&t;   hi: Current CODEC output FIFO pointer&n;&t;       (0 to 0x0f)&n;           lo: Flag indicating that the CODEC&n;&t;       FIFO is sync&squot;d (host clears to&n;&t;       resynchronize the FIFO pointer&n;&t;       upon start/restart) &n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|codec_FIFO_syncd
comma
id|codec_FIFO_ptr
)paren
multiline_comment|/* Init. 8000:0005 for 44.1k&n;                 8000:0001 for 48k&n;&t;   hi: Fractional sample accumulator 0.16b&n;&t;   lo: Number of frames remaining to be&n;&t;       processed in the current group of&n;&t;       frames&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|frac_samp_accum_qm1
comma
id|TM_frms_left_in_group
)paren
multiline_comment|/* Init. 0001:0005 for 44.1k&n;                 0000:0001 for 48k&n;&t;   hi: Fractional sample correction factor 0.16b&n;&t;       to be added every frameGroupLength frames&n;&t;       to correct for truncation error in&n;&t;       nsamp_per_frm_q15&n;&t;   lo: Number of frames in the group&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|frac_samp_correction_qm1
comma
id|TM_frm_group_length
)paren
multiline_comment|/* Init. 44.1k*65536/8k = 0x00058333 for 44.1k&n;                 48k*65536/8k = 0x00060000 for 48k&n;&t;   16b.16b integer.frac approximation to the&n;&t;   number of samples to output each frame.&n;&t;   (approximation must be floor, to insure */
id|u32
id|nsamp_per_frm_q15
suffix:semicolon
DECL|typedef|timing_master_scb_t
)brace
id|timing_master_scb_t
suffix:semicolon
multiline_comment|/* SCB for CODEC output algorithm */
DECL|struct|_codec_output_scb_t
r_typedef
r_struct
id|_codec_output_scb_t
(brace
multiline_comment|/* First 13 dwords from generic_scb_t */
DECL|member|basic_req
id|basic_dma_req_t
id|basic_req
suffix:semicolon
multiline_comment|/* Optional */
DECL|member|sg_ext
id|scatter_gather_ext_t
id|sg_ext
suffix:semicolon
multiline_comment|/* Optional */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|next_scb
comma
multiline_comment|/* REQUIRED */
id|sub_list_ptr
multiline_comment|/* REQUIRED */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|entry_point
comma
multiline_comment|/* REQUIRED */
id|this_spb
multiline_comment|/* REQUIRED */
)paren
id|u32
id|strm_rs_config
suffix:semicolon
multiline_comment|/* REQUIRED */
id|u32
id|strm_buf_ptr
suffix:semicolon
multiline_comment|/* REQUIRED */
multiline_comment|/* NOTE: The CODEC output task reads samples from the first task on its&n;                 sublist at the stream buffer pointer (init. to lag DMA destination&n;&t;&t; address word).  After the required number of samples is transferred,&n;&t;&t; the CODEC output task advances sub_list_ptr-&gt;strm_buf_ptr past the samples&n;&t;&t; consumed.&n;&t;*/
multiline_comment|/* Init. 0000:0010 for SDout&n;                 0060:0010 for SDout2&n;&t;&t; 0080:0010 for SDout3&n;&t;   hi: Base IO address of FIFO to which&n;&t;       the left-channel samples are to&n;&t;       be written.&n;&t;   lo: Displacement for the base IO&n;&t;       address for left-channel to obtain&n;&t;       the base IO address for the FIFO&n;&t;       to which the right-channel samples&n;&t;       are to be written.&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|left_chan_base_IO_addr
comma
id|right_chan_IO_disp
)paren
multiline_comment|/* Init: 0x0080:0004 for non-AC-97&n;&t;   Init: 0x0080:0000 for AC-97&n;&t;   hi: Exponential volume change rate&n;&t;       for input stream&n;&t;   lo: Positive shift count to shift the&n;&t;       16-bit input sample to obtain the&n;&t;       32-bit output word&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|CO_scale_shift_count
comma
id|CO_exp_vol_change_rate
)paren
multiline_comment|/* Pointer to SCB at end of input chain */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|reserved
comma
id|last_sub_ptr
)paren
DECL|typedef|codec_output_scb_t
)brace
id|codec_output_scb_t
suffix:semicolon
multiline_comment|/* SCB for CODEC input algorithm */
DECL|struct|_codec_input_scb_t
r_typedef
r_struct
id|_codec_input_scb_t
(brace
multiline_comment|/* First 13 dwords from generic_scb_t */
DECL|member|basic_req
id|basic_dma_req_t
id|basic_req
suffix:semicolon
multiline_comment|/* Optional */
DECL|member|sg_ext
id|scatter_gather_ext_t
id|sg_ext
suffix:semicolon
multiline_comment|/* Optional */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|next_scb
comma
multiline_comment|/* REQUIRED */
id|sub_list_ptr
multiline_comment|/* REQUIRED */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|entry_point
comma
multiline_comment|/* REQUIRED */
id|this_spb
multiline_comment|/* REQUIRED */
)paren
id|u32
id|strm_rs_config
suffix:semicolon
multiline_comment|/* REQUIRED */
id|u32
id|strm_buf_ptr
suffix:semicolon
multiline_comment|/* REQUIRED */
multiline_comment|/* NOTE: The CODEC input task reads samples from the hardware FIFO &n;                 sublist at the DMA source address word (sub_list_ptr-&gt;basic_req.saw).&n;                 After the required number of samples is transferred, the CODEC&n;                 output task advances sub_list_ptr-&gt;basic_req.saw past the samples&n;                 consumed.  SPuD must initialize the sub_list_ptr-&gt;basic_req.saw&n;                 to point half-way around from the initial sub_list_ptr-&gt;strm_nuf_ptr&n;                 to allow for lag/lead.&n;&t;*/
multiline_comment|/* Init. 0000:0010 for SDout&n;                 0060:0010 for SDout2&n;&t;&t; 0080:0010 for SDout3&n;&t;   hi: Base IO address of FIFO to which&n;&t;       the left-channel samples are to&n;&t;       be written.&n;&t;   lo: Displacement for the base IO&n;&t;       address for left-channel to obtain&n;&t;       the base IO address for the FIFO&n;&t;       to which the right-channel samples&n;&t;       are to be written.&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|rightChanINdisp
comma
id|left_chan_base_IN_addr
)paren
multiline_comment|/* Init. ?:fffc&n;&t;   lo: Negative shift count to shift the&n;&t;       32-bit input dword to obtain the&n;&t;       16-bit sample msb-aligned (count&n;&t;       is negative to shift left)&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|scaleShiftCount
comma
id|reserver1
)paren
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|typedef|codec_input_scb_t
)brace
id|codec_input_scb_t
suffix:semicolon
DECL|struct|_pcm_serial_input_scb_t
r_typedef
r_struct
id|_pcm_serial_input_scb_t
(brace
multiline_comment|/* First 13 dwords from generic_scb_t */
DECL|member|basic_req
id|basic_dma_req_t
id|basic_req
suffix:semicolon
multiline_comment|/* Optional */
DECL|member|sg_ext
id|scatter_gather_ext_t
id|sg_ext
suffix:semicolon
multiline_comment|/* Optional */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|next_scb
comma
multiline_comment|/* REQUIRED */
id|sub_list_ptr
multiline_comment|/* REQUIRED */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|entry_point
comma
multiline_comment|/* REQUIRED */
id|this_spb
multiline_comment|/* REQUIRED */
)paren
id|u32
id|strm_buf_ptr
suffix:semicolon
multiline_comment|/* REQUIRED */
id|u32
id|strm_rs_config
suffix:semicolon
multiline_comment|/* REQUIRED */
multiline_comment|/* Init. Ptr to CODEC input SCB&n;&t;   hi: Pointer to the SCB containing the&n;&t;       input buffer to which CODEC input&n;&t;       samples are written&n;&t;   lo: Flag indicating the link to the CODEC&n;&t;       input task is to be initialized&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|init_codec_input_link
comma
id|codec_input_buf_scb
)paren
multiline_comment|/* Initialized by the host (host updates target volumes) */
DECL|member|psi_vol_ctrl
id|volume_control_t
id|psi_vol_ctrl
suffix:semicolon
DECL|typedef|pcm_serial_input_scb_t
)brace
id|pcm_serial_input_scb_t
suffix:semicolon
DECL|struct|_src_task_scb_t
r_typedef
r_struct
id|_src_task_scb_t
(brace
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|frames_left_in_gof
comma
id|gofs_left_in_sec
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|const2_thirds
comma
id|num_extra_tnput_samples
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|cor_per_gof
comma
id|correction_per_sec
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|output_buf_producer_ptr
comma
id|junk_DMA_MID
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|gof_length
comma
id|gofs_per_sec
)paren
id|u32
id|input_buf_strm_config
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|reserved_for_SRC_use
comma
id|input_buf_consumer_ptr
)paren
id|u32
id|accum_phi
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|exp_src_vol_change_rate
comma
id|input_buf_producer_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|src_next_scb
comma
id|src_sub_list_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|src_entry_point
comma
id|src_this_sbp
)paren
DECL|member|src_strm_rs_config
id|u32
id|src_strm_rs_config
suffix:semicolon
DECL|member|src_strm_buf_ptr
id|u32
id|src_strm_buf_ptr
suffix:semicolon
DECL|member|phiIncr6int_26frac
id|u32
id|phiIncr6int_26frac
suffix:semicolon
DECL|member|src_vol_ctrl
id|volume_control_t
id|src_vol_ctrl
suffix:semicolon
DECL|typedef|src_task_scb_t
)brace
id|src_task_scb_t
suffix:semicolon
DECL|struct|_decimate_by_pow2_scb_t
r_typedef
r_struct
id|_decimate_by_pow2_scb_t
(brace
multiline_comment|/* decimationFactor = 2, 4, or 8 (larger factors waste too much memory&n;&t;                                  when compared to cascading decimators)&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|dec2_coef_base_ptr
comma
id|dec2_coef_increment
)paren
multiline_comment|/* coefIncrement = 128 / decimationFactor (for our ROM filter)&n;&t;   coefBasePtr = 0x8000 (for our ROM filter)&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|dec2_in_samples_per_out_triplet
comma
id|dec2_extra_in_samples
)paren
multiline_comment|/* extraInSamples: # of accumulated, unused input samples (init. to 0)&n;&t;   inSamplesPerOutTriplet = 3 * decimationFactor&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|dec2_const2_thirds
comma
id|dec2_half_num_taps_mp5
)paren
multiline_comment|/* halfNumTapsM5: (1/2 number of taps in decimation filter) minus 5&n;&t;   const2thirds: constant 2/3 in 16Q0 format (sign.15)&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|dec2_output_buf_producer_ptr
comma
id|dec2_junkdma_mid
)paren
id|u32
id|dec2_reserved2
suffix:semicolon
id|u32
id|dec2_input_nuf_strm_config
suffix:semicolon
multiline_comment|/* inputBufStrmConfig: rsConfig for the input buffer to the decimator&n;&t;   (buffer size = decimationFactor * 32 dwords)&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|dec2_phi_incr
comma
id|dec2_input_buf_consumer_ptr
)paren
multiline_comment|/* inputBufConsumerPtr: Input buffer read pointer (into SRC filter)&n;&t;   phiIncr = decimationFactor * 4&n;&t;*/
DECL|member|dec2_reserved3
id|u32
id|dec2_reserved3
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|dec2_exp_vol_change_rate
comma
id|dec2_input_buf_producer_ptr
)paren
multiline_comment|/* inputBufProducerPtr: Input buffer write pointer&n;&t;   expVolChangeRate: Exponential volume change rate for possible&n;&t;                     future mixer on input streams&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|dec2_next_scb
comma
id|dec2_sub_list_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|dec2_entry_point
comma
id|dec2_this_spb
)paren
id|u32
id|dec2_strm_rs_config
suffix:semicolon
id|u32
id|dec2_strm_buf_ptr
suffix:semicolon
DECL|member|dec2_reserved4
id|u32
id|dec2_reserved4
suffix:semicolon
DECL|member|dec2_vol_ctrl
id|volume_control_t
id|dec2_vol_ctrl
suffix:semicolon
multiline_comment|/* Not used! */
DECL|typedef|decimate_by_pow2_scb_t
)brace
id|decimate_by_pow2_scb_t
suffix:semicolon
DECL|struct|_vari_decimate_scb_t
r_typedef
r_struct
id|_vari_decimate_scb_t
(brace
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|vdec_frames_left_in_gof
comma
id|vdec_gofs_left_in_sec
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|vdec_const2_thirds
comma
id|vdec_extra_in_samples
)paren
multiline_comment|/* extraInSamples: # of accumulated, unused input samples (init. to 0)&n;&t;   const2thirds: constant 2/3 in 16Q0 format (sign.15) */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|vdec_cor_per_gof
comma
id|vdec_correction_per_sec
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|vdec_output_buf_producer_ptr
comma
id|vdec_input_buf_consumer_ptr
)paren
multiline_comment|/* inputBufConsumerPtr: Input buffer read pointer (into SRC filter) */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|vdec_gof_length
comma
id|vdec_gofs_per_sec
)paren
id|u32
id|vdec_input_buf_strm_config
suffix:semicolon
multiline_comment|/* inputBufStrmConfig: rsConfig for the input buffer to the decimator&n;&t;   (buffer size = 64 dwords) */
id|u32
id|vdec_coef_increment
suffix:semicolon
multiline_comment|/* coefIncrement = - 128.0 / decimationFactor (as a 32Q15 number) */
DECL|member|vdec_accumphi
id|u32
id|vdec_accumphi
suffix:semicolon
multiline_comment|/* accumPhi: accumulated fractional phase increment (6.26) */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|vdec_exp_vol_change_rate
comma
id|vdec_input_buf_producer_ptr
)paren
multiline_comment|/* inputBufProducerPtr: Input buffer write pointer&n;&t;   expVolChangeRate: Exponential volume change rate for possible&n;&t;   future mixer on input streams */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|vdec_next_scb
comma
id|vdec_sub_list_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|vdec_entry_point
comma
id|vdec_this_spb
)paren
id|u32
id|vdec_strm_rs_config
suffix:semicolon
id|u32
id|vdec_strm_buf_ptr
suffix:semicolon
DECL|member|vdec_phi_incr_6int_26frac
id|u32
id|vdec_phi_incr_6int_26frac
suffix:semicolon
DECL|member|vdec_vol_ctrl
id|volume_control_t
id|vdec_vol_ctrl
suffix:semicolon
DECL|typedef|vari_decimate_scb_t
)brace
id|vari_decimate_scb_t
suffix:semicolon
multiline_comment|/* SCB for MIX_TO_OSTREAM algorithm family */
DECL|struct|_mix2_ostream_scb_t
r_typedef
r_struct
id|_mix2_ostream_scb_t
(brace
multiline_comment|/* First 13 dwords from generic_scb_t */
DECL|member|basic_req
id|basic_dma_req_t
id|basic_req
suffix:semicolon
multiline_comment|/* Optional */
DECL|member|sg_ext
id|scatter_gather_ext_t
id|sg_ext
suffix:semicolon
multiline_comment|/* Optional */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|next_scb
comma
multiline_comment|/* REQUIRED */
id|sub_list_ptr
multiline_comment|/* REQUIRED */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|entry_point
comma
multiline_comment|/* REQUIRED */
id|this_spb
multiline_comment|/* REQUIRED */
)paren
id|u32
id|strm_rs_config
suffix:semicolon
multiline_comment|/* REQUIRED */
id|u32
id|strm_buf_ptr
suffix:semicolon
multiline_comment|/* REQUIRED */
multiline_comment|/* hi: Number of mixed-down input triplets&n;&t;       computed since start of group&n;&t;   lo: Number of frames remaining to be&n;&t;       processed in the current group of&n;&t;       frames&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|frames_left_in_group
comma
id|accum_input_triplets
)paren
multiline_comment|/* hi: Exponential volume change rate&n;&t;       for mixer on input streams&n;&t;   lo: Number of frames in the group&n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|frame_group_length
comma
id|exp_vol_change_rate
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|const_FFFF
comma
id|const_zero
)paren
DECL|typedef|mix2_ostream_scb_t
)brace
id|mix2_ostream_scb_t
suffix:semicolon
multiline_comment|/* SCB for S16_MIX algorithm */
DECL|struct|_mix_only_scb_t
r_typedef
r_struct
id|_mix_only_scb_t
(brace
multiline_comment|/* First 13 dwords from generic_scb_t */
DECL|member|basic_req
id|basic_dma_req_t
id|basic_req
suffix:semicolon
multiline_comment|/* Optional */
DECL|member|sg_ext
id|scatter_gather_ext_t
id|sg_ext
suffix:semicolon
multiline_comment|/* Optional */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|next_scb
comma
multiline_comment|/* REQUIRED */
id|sub_list_ptr
multiline_comment|/* REQUIRED */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|entry_point
comma
multiline_comment|/* REQUIRED */
id|this_spb
multiline_comment|/* REQUIRED */
)paren
id|u32
id|strm_rs_config
suffix:semicolon
multiline_comment|/* REQUIRED */
id|u32
id|strm_buf_ptr
suffix:semicolon
multiline_comment|/* REQUIRED */
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
DECL|member|vol_ctrl
id|volume_control_t
id|vol_ctrl
suffix:semicolon
DECL|typedef|mix_only_scb_t
)brace
id|mix_only_scb_t
suffix:semicolon
multiline_comment|/* SCB for the async. CODEC input algorithm */
DECL|struct|_async_codec_input_scb_t
r_typedef
r_struct
id|_async_codec_input_scb_t
(brace
DECL|member|io_free2
id|u32
id|io_free2
suffix:semicolon
DECL|member|io_current_total
id|u32
id|io_current_total
suffix:semicolon
DECL|member|io_previous_total
id|u32
id|io_previous_total
suffix:semicolon
DECL|member|io_count
id|u16
id|io_count
suffix:semicolon
DECL|member|io_count_limit
id|u16
id|io_count_limit
suffix:semicolon
DECL|member|o_fifo_base_addr
id|u16
id|o_fifo_base_addr
suffix:semicolon
DECL|member|ost_mo_format
id|u16
id|ost_mo_format
suffix:semicolon
multiline_comment|/* 1 = stereo; 0 = mono &n;&t;   xxx for ASER 1 (not allowed); 118 for ASER2 */
DECL|member|ostrm_rs_config
id|u32
id|ostrm_rs_config
suffix:semicolon
DECL|member|ostrm_buf_ptr
id|u32
id|ostrm_buf_ptr
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|io_sclks_per_lr_clk
comma
id|io_io_enable
)paren
id|u32
id|io_free4
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|io_next_scb
comma
id|io_sub_list_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|io_entry_point
comma
id|io_this_spb
)paren
id|u32
id|istrm_rs_config
suffix:semicolon
DECL|member|istrm_buf_ptr
id|u32
id|istrm_buf_ptr
suffix:semicolon
multiline_comment|/* Init. 0000:8042: for ASER1&n;                 0000:8044: for ASER2  */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|io_stat_reg_addr
comma
id|iofifo_pointer
)paren
multiline_comment|/* Init 1 stero:100 ASER1&n;&t;   Init 0 mono:110 ASER2 &n;&t;*/
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|ififo_base_addr
comma
id|ist_mo_format
)paren
id|u32
id|i_free
suffix:semicolon
DECL|typedef|async_codec_input_scb_t
)brace
id|async_codec_input_scb_t
suffix:semicolon
multiline_comment|/* SCB for the SP/DIF CODEC input and output */
DECL|struct|_spdifiscb_t
r_typedef
r_struct
id|_spdifiscb_t
(brace
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|status_ptr
comma
id|status_start_ptr
)paren
id|u32
id|current_total
suffix:semicolon
id|u32
id|previous_total
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|count
comma
id|count_limit
)paren
DECL|member|status_data
id|u32
id|status_data
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|status
comma
id|free4
)paren
id|u32
id|free3
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|free2
comma
id|bit_count
)paren
id|u32
id|temp_status
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|next_SCB
comma
id|sub_list_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|entry_point
comma
id|this_spb
)paren
DECL|member|strm_rs_config
id|u32
id|strm_rs_config
suffix:semicolon
DECL|member|strm_buf_ptr
id|u32
id|strm_buf_ptr
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|stat_reg_addr
comma
id|fifo_pointer
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|fifo_base_addr
comma
id|st_mo_format
)paren
id|u32
id|free1
suffix:semicolon
DECL|typedef|spdifiscb_t
)brace
id|spdifiscb_t
suffix:semicolon
multiline_comment|/* SCB for the SP/DIF CODEC input and output  */
DECL|struct|_spdifoscb_t
r_typedef
r_struct
id|_spdifoscb_t
(brace
DECL|member|free2
id|u32
id|free2
suffix:semicolon
DECL|member|free3
id|u32
id|free3
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Need to be here for compatibility with AsynchFGTxCode */
DECL|member|strm_rs_config
id|u32
id|strm_rs_config
suffix:semicolon
DECL|member|strm_buf_ptr
id|u32
id|strm_buf_ptr
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|status
comma
id|free5
)paren
id|u32
id|free4
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|next_scb
comma
id|sub_list_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|entry_point
comma
id|this_spb
)paren
id|u32
id|free6
(braket
l_int|2
)braket
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|stat_reg_addr
comma
id|fifo_pointer
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|fifo_base_addr
comma
id|st_mo_format
)paren
DECL|member|free1
id|u32
id|free1
suffix:semicolon
DECL|typedef|spdifoscb_t
)brace
id|spdifoscb_t
suffix:semicolon
DECL|struct|_asynch_fg_rx_scb_t
r_typedef
r_struct
id|_asynch_fg_rx_scb_t
(brace
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|bot_buf_mask
comma
id|buf_Mask
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|max
comma
id|min
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|old_producer_pointer
comma
id|hfg_scb_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|delta
comma
id|adjust_count
)paren
id|u32
id|unused2
(braket
l_int|5
)braket
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|sibling_ptr
comma
id|child_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|code_ptr
comma
id|this_ptr
)paren
id|u32
id|strm_rs_config
suffix:semicolon
DECL|member|strm_buf_ptr
id|u32
id|strm_buf_ptr
suffix:semicolon
DECL|member|unused_phi_incr
id|u32
id|unused_phi_incr
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|right_targ
comma
id|left_targ
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|right_vol
comma
id|left_vol
)paren
DECL|typedef|asynch_fg_rx_scb_t
)brace
id|asynch_fg_rx_scb_t
suffix:semicolon
DECL|struct|_asynch_fg_tx_scb_t
r_typedef
r_struct
id|_asynch_fg_tx_scb_t
(brace
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|not_buf_mask
comma
id|buf_mask
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|max
comma
id|min
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|unused1
comma
id|hfg_scb_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|delta
comma
id|adjust_count
)paren
id|u32
id|accum_phi
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|unused2
comma
id|const_one_third
)paren
id|u32
id|unused3
(braket
l_int|3
)braket
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|sibling_ptr
comma
id|child_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|codePtr
comma
id|this_ptr
)paren
DECL|member|strm_rs_config
id|u32
id|strm_rs_config
suffix:semicolon
DECL|member|strm_buf_ptr
id|u32
id|strm_buf_ptr
suffix:semicolon
DECL|member|phi_incr
id|u32
id|phi_incr
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|unused_right_targ
comma
id|unused_left_targ
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|unused_right_vol
comma
id|unused_left_vol
)paren
DECL|typedef|asynch_fg_tx_scb_t
)brace
id|asynch_fg_tx_scb_t
suffix:semicolon
DECL|struct|_output_snoop_scb_t
r_typedef
r_struct
id|_output_snoop_scb_t
(brace
multiline_comment|/* First 13 dwords from generic_scb_t */
DECL|member|basic_req
id|basic_dma_req_t
id|basic_req
suffix:semicolon
multiline_comment|/* Optional */
DECL|member|sg_ext
id|scatter_gather_ext_t
id|sg_ext
suffix:semicolon
multiline_comment|/* Optional */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|next_scb
comma
multiline_comment|/* REQUIRED */
id|sub_list_ptr
multiline_comment|/* REQUIRED */
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|entry_point
comma
multiline_comment|/* REQUIRED */
id|this_spb
multiline_comment|/* REQUIRED */
)paren
id|u32
id|strm_rs_config
suffix:semicolon
multiline_comment|/* REQUIRED */
id|u32
id|strm_buf_ptr
suffix:semicolon
multiline_comment|/* REQUIRED */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|init_snoop_input_link
comma
id|snoop_child_input_scb
)paren
DECL|member|snoop_input_buf_ptr
id|u32
id|snoop_input_buf_ptr
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|reserved
comma
id|input_scb
)paren
DECL|typedef|output_snoop_scb_t
)brace
id|output_snoop_scb_t
suffix:semicolon
DECL|struct|_spio_write_scb_t
r_typedef
r_struct
id|_spio_write_scb_t
(brace
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|address1
comma
id|address2
)paren
id|u32
id|data1
suffix:semicolon
id|u32
id|data2
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|address3
comma
id|address4
)paren
DECL|member|data3
id|u32
id|data3
suffix:semicolon
DECL|member|data4
id|u32
id|data4
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|unused1
comma
id|data_ptr
)paren
id|u32
id|unused2
(braket
l_int|2
)braket
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|sibling_ptr
comma
id|child_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|entry_point
comma
id|this_ptr
)paren
id|u32
id|unused3
(braket
l_int|5
)braket
suffix:semicolon
DECL|typedef|spio_write_scb_t
)brace
id|spio_write_scb_t
suffix:semicolon
DECL|struct|_magic_snoop_task_t
r_typedef
r_struct
id|_magic_snoop_task_t
(brace
DECL|member|i0
id|u32
id|i0
suffix:semicolon
DECL|member|i1
id|u32
id|i1
suffix:semicolon
DECL|member|strm_buf_ptr1
id|u32
id|strm_buf_ptr1
suffix:semicolon
DECL|member|i2
id|u16
id|i2
suffix:semicolon
DECL|member|snoop_scb
id|u16
id|snoop_scb
suffix:semicolon
DECL|member|i3
id|u32
id|i3
suffix:semicolon
DECL|member|i4
id|u32
id|i4
suffix:semicolon
DECL|member|i5
id|u32
id|i5
suffix:semicolon
DECL|member|i6
id|u32
id|i6
suffix:semicolon
DECL|member|i7
id|u32
id|i7
suffix:semicolon
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|next_scb
comma
id|sub_list_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|entry_point
comma
id|this_ptr
)paren
id|u32
id|strm_buf_config
suffix:semicolon
id|u32
id|strm_buf_ptr2
suffix:semicolon
DECL|member|i8
id|u32
id|i8
suffix:semicolon
DECL|member|vdec_vol_ctrl
id|volume_control_t
id|vdec_vol_ctrl
suffix:semicolon
DECL|typedef|magic_snoop_task_t
)brace
id|magic_snoop_task_t
suffix:semicolon
DECL|struct|_filter_scb_t
r_typedef
r_struct
id|_filter_scb_t
(brace
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|a0_right
comma
multiline_comment|/* 0x00 */
id|a0_left
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|a1_right
comma
multiline_comment|/* 0x01 */
id|a1_left
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|a2_right
comma
multiline_comment|/* 0x02 */
id|a2_left
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|output_buf_ptr
comma
multiline_comment|/* 0x03 */
id|init
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|filter_unused3
comma
multiline_comment|/* 0x04 */
id|filter_unused2
)paren
id|u32
id|prev_sample_output1
suffix:semicolon
multiline_comment|/* 0x05 */
id|u32
id|prev_sample_output2
suffix:semicolon
multiline_comment|/* 0x06 */
DECL|member|prev_sample_input1
id|u32
id|prev_sample_input1
suffix:semicolon
multiline_comment|/* 0x07 */
DECL|member|prev_sample_input2
id|u32
id|prev_sample_input2
suffix:semicolon
multiline_comment|/* 0x08 */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|next_scb_ptr
comma
multiline_comment|/* 0x09 */
id|sub_list_ptr
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|entry_point
comma
multiline_comment|/* 0x0A */
id|spb_ptr
)paren
id|u32
id|strm_rs_config
suffix:semicolon
multiline_comment|/* 0x0B */
id|u32
id|strm_buf_ptr
suffix:semicolon
multiline_comment|/* 0x0C */
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|b0_right
comma
multiline_comment|/* 0x0D */
id|b0_left
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|b1_right
comma
multiline_comment|/* 0x0E */
id|b1_left
)paren
id|___DSP_DUAL_16BIT_ALLOC
c_func
(paren
id|b2_right
comma
multiline_comment|/* 0x0F */
id|b2_left
)paren
DECL|typedef|filter_scb_t
)brace
id|filter_scb_t
suffix:semicolon
macro_line|#endif /* __DSP_SCB_TYPES_H__ */
eof
