multiline_comment|/*&n; * Inline routines shareable across OS platforms.&n; *&n; * Copyright (c) 1994-2001 Justin T. Gibbs.&n; * Copyright (c) 2000-2001 Adaptec Inc.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; *&n; * $Id: //depot/aic7xxx/aic7xxx/aic7xxx_inline.h#42 $&n; *&n; * $FreeBSD$&n; */
macro_line|#ifndef _AIC7XXX_INLINE_H_
DECL|macro|_AIC7XXX_INLINE_H_
mdefine_line|#define _AIC7XXX_INLINE_H_
multiline_comment|/************************* Sequencer Execution Control ************************/
r_static
id|__inline
r_void
id|ahc_pause_bug_fix
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_static
id|__inline
r_int
id|ahc_is_paused
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_static
id|__inline
r_void
id|ahc_pause
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_static
id|__inline
r_void
id|ahc_unpause
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
multiline_comment|/*&n; * Work around any chip bugs related to halting sequencer execution.&n; * On Ultra2 controllers, we must clear the CIOBUS stretch signal by&n; * reading a register that will set this signal and deassert it.&n; * Without this workaround, if the chip is paused, by an interrupt or&n; * manual pause while accessing scb ram, accesses to certain registers&n; * will hang the system (infinite pci retries).&n; */
r_static
id|__inline
r_void
DECL|function|ahc_pause_bug_fix
id|ahc_pause_bug_fix
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
r_if
c_cond
(paren
(paren
id|ahc-&gt;features
op_amp
id|AHC_ULTRA2
)paren
op_ne
l_int|0
)paren
(paren
r_void
)paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|CCSCBCTL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Determine whether the sequencer has halted code execution.&n; * Returns non-zero status if the sequencer is stopped.&n; */
r_static
id|__inline
r_int
DECL|function|ahc_is_paused
id|ahc_is_paused
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
r_return
(paren
(paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|HCNTRL
)paren
op_amp
id|PAUSE
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Request that the sequencer stop and wait, indefinitely, for it&n; * to stop.  The sequencer will only acknowledge that it is paused&n; * once it has reached an instruction boundary and PAUSEDIS is&n; * cleared in the SEQCTL register.  The sequencer may use PAUSEDIS&n; * for critical sections.&n; */
r_static
id|__inline
r_void
DECL|function|ahc_pause
id|ahc_pause
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
id|ahc_outb
c_func
(paren
id|ahc
comma
id|HCNTRL
comma
id|ahc-&gt;pause
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Since the sequencer can disable pausing in a critical section, we&n;&t; * must loop until it actually stops.&n;&t; */
r_while
c_loop
(paren
id|ahc_is_paused
c_func
(paren
id|ahc
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|ahc_pause_bug_fix
c_func
(paren
id|ahc
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Allow the sequencer to continue program execution.&n; * We check here to ensure that no additional interrupt&n; * sources that would cause the sequencer to halt have been&n; * asserted.  If, for example, a SCSI bus reset is detected&n; * while we are fielding a different, pausing, interrupt type,&n; * we don&squot;t want to release the sequencer before going back&n; * into our interrupt handler and dealing with this new&n; * condition.&n; */
r_static
id|__inline
r_void
DECL|function|ahc_unpause
id|ahc_unpause
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
r_if
c_cond
(paren
(paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|INTSTAT
)paren
op_amp
(paren
id|SCSIINT
op_or
id|SEQINT
op_or
id|BRKADRINT
)paren
)paren
op_eq
l_int|0
)paren
id|ahc_outb
c_func
(paren
id|ahc
comma
id|HCNTRL
comma
id|ahc-&gt;unpause
)paren
suffix:semicolon
)brace
multiline_comment|/*********************** Untagged Transaction Routines ************************/
r_static
id|__inline
r_void
id|ahc_freeze_untagged_queues
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_static
id|__inline
r_void
id|ahc_release_untagged_queues
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
multiline_comment|/*&n; * Block our completion routine from starting the next untagged&n; * transaction for this target or target lun.&n; */
r_static
id|__inline
r_void
DECL|function|ahc_freeze_untagged_queues
id|ahc_freeze_untagged_queues
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
r_if
c_cond
(paren
(paren
id|ahc-&gt;flags
op_amp
id|AHC_SCB_BTT
)paren
op_eq
l_int|0
)paren
id|ahc-&gt;untagged_queue_lock
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n; * Allow the next untagged transaction for this target or target lun&n; * to be executed.  We use a counting semaphore to allow the lock&n; * to be acquired recursively.  Once the count drops to zero, the&n; * transaction queues will be run.&n; */
r_static
id|__inline
r_void
DECL|function|ahc_release_untagged_queues
id|ahc_release_untagged_queues
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
r_if
c_cond
(paren
(paren
id|ahc-&gt;flags
op_amp
id|AHC_SCB_BTT
)paren
op_eq
l_int|0
)paren
(brace
id|ahc-&gt;untagged_queue_lock
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|ahc-&gt;untagged_queue_lock
op_eq
l_int|0
)paren
id|ahc_run_untagged_queues
c_func
(paren
id|ahc
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/************************** Memory mapping routines ***************************/
r_static
id|__inline
r_struct
id|ahc_dma_seg
op_star
id|ahc_sg_bus_to_virt
c_func
(paren
r_struct
id|scb
op_star
id|scb
comma
r_uint32
id|sg_busaddr
)paren
suffix:semicolon
r_static
id|__inline
r_uint32
id|ahc_sg_virt_to_bus
c_func
(paren
r_struct
id|scb
op_star
id|scb
comma
r_struct
id|ahc_dma_seg
op_star
id|sg
)paren
suffix:semicolon
r_static
id|__inline
r_uint32
id|ahc_hscb_busaddr
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|index
)paren
suffix:semicolon
r_static
id|__inline
r_void
id|ahc_sync_scb
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
comma
r_int
id|op
)paren
suffix:semicolon
r_static
id|__inline
r_void
id|ahc_sync_sglist
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
comma
r_int
id|op
)paren
suffix:semicolon
r_static
id|__inline
r_uint32
id|ahc_targetcmd_offset
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|index
)paren
suffix:semicolon
r_static
id|__inline
r_struct
id|ahc_dma_seg
op_star
DECL|function|ahc_sg_bus_to_virt
id|ahc_sg_bus_to_virt
c_func
(paren
r_struct
id|scb
op_star
id|scb
comma
r_uint32
id|sg_busaddr
)paren
(brace
r_int
id|sg_index
suffix:semicolon
id|sg_index
op_assign
(paren
id|sg_busaddr
op_minus
id|scb-&gt;sg_list_phys
)paren
op_div
r_sizeof
(paren
r_struct
id|ahc_dma_seg
)paren
suffix:semicolon
multiline_comment|/* sg_list_phys points to entry 1, not 0 */
id|sg_index
op_increment
suffix:semicolon
r_return
(paren
op_amp
id|scb-&gt;sg_list
(braket
id|sg_index
)braket
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_uint32
DECL|function|ahc_sg_virt_to_bus
id|ahc_sg_virt_to_bus
c_func
(paren
r_struct
id|scb
op_star
id|scb
comma
r_struct
id|ahc_dma_seg
op_star
id|sg
)paren
(brace
r_int
id|sg_index
suffix:semicolon
multiline_comment|/* sg_list_phys points to entry 1, not 0 */
id|sg_index
op_assign
id|sg
op_minus
op_amp
id|scb-&gt;sg_list
(braket
l_int|1
)braket
suffix:semicolon
r_return
(paren
id|scb-&gt;sg_list_phys
op_plus
(paren
id|sg_index
op_star
r_sizeof
(paren
op_star
id|scb-&gt;sg_list
)paren
)paren
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_uint32
DECL|function|ahc_hscb_busaddr
id|ahc_hscb_busaddr
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|index
)paren
(brace
r_return
(paren
id|ahc-&gt;scb_data-&gt;hscb_busaddr
op_plus
(paren
r_sizeof
(paren
r_struct
id|hardware_scb
)paren
op_star
id|index
)paren
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_void
DECL|function|ahc_sync_scb
id|ahc_sync_scb
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
comma
r_int
id|op
)paren
(brace
id|ahc_dmamap_sync
c_func
(paren
id|ahc
comma
id|ahc-&gt;scb_data-&gt;hscb_dmat
comma
id|ahc-&gt;scb_data-&gt;hscb_dmamap
comma
multiline_comment|/*offset*/
(paren
id|scb-&gt;hscb
op_minus
id|ahc-&gt;hscbs
)paren
op_star
r_sizeof
(paren
op_star
id|scb-&gt;hscb
)paren
comma
multiline_comment|/*len*/
r_sizeof
(paren
op_star
id|scb-&gt;hscb
)paren
comma
id|op
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_void
DECL|function|ahc_sync_sglist
id|ahc_sync_sglist
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
comma
r_int
id|op
)paren
(brace
r_if
c_cond
(paren
id|scb-&gt;sg_count
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|ahc_dmamap_sync
c_func
(paren
id|ahc
comma
id|ahc-&gt;scb_data-&gt;sg_dmat
comma
id|scb-&gt;sg_map-&gt;sg_dmamap
comma
multiline_comment|/*offset*/
(paren
id|scb-&gt;sg_list
op_minus
id|scb-&gt;sg_map-&gt;sg_vaddr
)paren
op_star
r_sizeof
(paren
r_struct
id|ahc_dma_seg
)paren
comma
multiline_comment|/*len*/
r_sizeof
(paren
r_struct
id|ahc_dma_seg
)paren
op_star
id|scb-&gt;sg_count
comma
id|op
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_uint32
DECL|function|ahc_targetcmd_offset
id|ahc_targetcmd_offset
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|index
)paren
(brace
r_return
(paren
(paren
(paren
r_uint8
op_star
)paren
op_amp
id|ahc-&gt;targetcmds
(braket
id|index
)braket
)paren
op_minus
id|ahc-&gt;qoutfifo
)paren
suffix:semicolon
)brace
multiline_comment|/******************************** Debugging ***********************************/
r_static
id|__inline
r_char
op_star
id|ahc_name
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_static
id|__inline
r_char
op_star
DECL|function|ahc_name
id|ahc_name
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
r_return
(paren
id|ahc-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/*********************** Miscelaneous Support Functions ***********************/
r_static
id|__inline
r_void
id|ahc_update_residual
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_static
id|__inline
r_struct
id|ahc_initiator_tinfo
op_star
id|ahc_fetch_transinfo
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_char
id|channel
comma
id|u_int
id|our_id
comma
id|u_int
id|remote_id
comma
r_struct
id|ahc_tmode_tstate
op_star
op_star
id|tstate
)paren
suffix:semicolon
r_static
id|__inline
r_uint16
id|ahc_inw
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|port
)paren
suffix:semicolon
r_static
id|__inline
r_void
id|ahc_outw
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|port
comma
id|u_int
id|value
)paren
suffix:semicolon
r_static
id|__inline
r_uint32
id|ahc_inl
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|port
)paren
suffix:semicolon
r_static
id|__inline
r_void
id|ahc_outl
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|port
comma
r_uint32
id|value
)paren
suffix:semicolon
r_static
id|__inline
r_uint64
id|ahc_inq
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|port
)paren
suffix:semicolon
r_static
id|__inline
r_void
id|ahc_outq
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|port
comma
r_uint64
id|value
)paren
suffix:semicolon
r_static
id|__inline
r_struct
id|scb
op_star
id|ahc_get_scb
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_static
id|__inline
r_void
id|ahc_free_scb
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_static
id|__inline
r_void
id|ahc_swap_with_next_hscb
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_static
id|__inline
r_void
id|ahc_queue_scb
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_static
id|__inline
r_struct
id|scsi_sense_data
op_star
id|ahc_get_sense_buf
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
r_static
id|__inline
r_uint32
id|ahc_get_sense_bufaddr
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
)paren
suffix:semicolon
multiline_comment|/*&n; * Determine whether the sequencer reported a residual&n; * for this SCB/transaction.&n; */
r_static
id|__inline
r_void
DECL|function|ahc_update_residual
id|ahc_update_residual
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
)paren
(brace
r_uint32
id|sgptr
suffix:semicolon
id|sgptr
op_assign
id|ahc_le32toh
c_func
(paren
id|scb-&gt;hscb-&gt;sgptr
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sgptr
op_amp
id|SG_RESID_VALID
)paren
op_ne
l_int|0
)paren
id|ahc_calc_residual
c_func
(paren
id|ahc
comma
id|scb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return pointers to the transfer negotiation information&n; * for the specified our_id/remote_id pair.&n; */
r_static
id|__inline
r_struct
id|ahc_initiator_tinfo
op_star
DECL|function|ahc_fetch_transinfo
id|ahc_fetch_transinfo
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_char
id|channel
comma
id|u_int
id|our_id
comma
id|u_int
id|remote_id
comma
r_struct
id|ahc_tmode_tstate
op_star
op_star
id|tstate
)paren
(brace
multiline_comment|/*&n;&t; * Transfer data structures are stored from the perspective&n;&t; * of the target role.  Since the parameters for a connection&n;&t; * in the initiator role to a given target are the same as&n;&t; * when the roles are reversed, we pretend we are the target.&n;&t; */
r_if
c_cond
(paren
id|channel
op_eq
l_char|&squot;B&squot;
)paren
id|our_id
op_add_assign
l_int|8
suffix:semicolon
op_star
id|tstate
op_assign
id|ahc-&gt;enabled_targets
(braket
id|our_id
)braket
suffix:semicolon
r_return
(paren
op_amp
(paren
op_star
id|tstate
)paren
op_member_access_from_pointer
id|transinfo
(braket
id|remote_id
)braket
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_uint16
DECL|function|ahc_inw
id|ahc_inw
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|port
)paren
(brace
r_return
(paren
(paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|1
)paren
op_lshift
l_int|8
)paren
op_or
id|ahc_inb
c_func
(paren
id|ahc
comma
id|port
)paren
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_void
DECL|function|ahc_outw
id|ahc_outw
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|port
comma
id|u_int
id|value
)paren
(brace
id|ahc_outb
c_func
(paren
id|ahc
comma
id|port
comma
id|value
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|1
comma
(paren
id|value
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_uint32
DECL|function|ahc_inl
id|ahc_inl
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|port
)paren
(brace
r_return
(paren
(paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|port
)paren
)paren
op_or
(paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|1
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|2
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|3
)paren
op_lshift
l_int|24
)paren
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_void
DECL|function|ahc_outl
id|ahc_outl
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|port
comma
r_uint32
id|value
)paren
(brace
id|ahc_outb
c_func
(paren
id|ahc
comma
id|port
comma
(paren
id|value
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|1
comma
(paren
(paren
id|value
)paren
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|2
comma
(paren
(paren
id|value
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|3
comma
(paren
(paren
id|value
)paren
op_rshift
l_int|24
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_uint64
DECL|function|ahc_inq
id|ahc_inq
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|port
)paren
(brace
r_return
(paren
(paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|port
)paren
)paren
op_or
(paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|1
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|2
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|3
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
(paren
r_uint64
)paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|4
)paren
)paren
op_lshift
l_int|32
)paren
op_or
(paren
(paren
(paren
r_uint64
)paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|5
)paren
)paren
op_lshift
l_int|40
)paren
op_or
(paren
(paren
(paren
r_uint64
)paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|6
)paren
)paren
op_lshift
l_int|48
)paren
op_or
(paren
(paren
(paren
r_uint64
)paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|7
)paren
)paren
op_lshift
l_int|56
)paren
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_void
DECL|function|ahc_outq
id|ahc_outq
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|port
comma
r_uint64
id|value
)paren
(brace
id|ahc_outb
c_func
(paren
id|ahc
comma
id|port
comma
id|value
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|1
comma
(paren
id|value
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|2
comma
(paren
id|value
op_rshift
l_int|16
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|3
comma
(paren
id|value
op_rshift
l_int|24
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|4
comma
(paren
id|value
op_rshift
l_int|32
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|5
comma
(paren
id|value
op_rshift
l_int|40
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|6
comma
(paren
id|value
op_rshift
l_int|48
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|port
op_plus
l_int|7
comma
(paren
id|value
op_rshift
l_int|56
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Get a free scb. If there are none, see if we can allocate a new SCB.&n; */
r_static
id|__inline
r_struct
id|scb
op_star
DECL|function|ahc_get_scb
id|ahc_get_scb
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
r_struct
id|scb
op_star
id|scb
suffix:semicolon
r_if
c_cond
(paren
(paren
id|scb
op_assign
id|SLIST_FIRST
c_func
(paren
op_amp
id|ahc-&gt;scb_data-&gt;free_scbs
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|ahc_alloc_scbs
c_func
(paren
id|ahc
)paren
suffix:semicolon
id|scb
op_assign
id|SLIST_FIRST
c_func
(paren
op_amp
id|ahc-&gt;scb_data-&gt;free_scbs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scb
op_eq
l_int|NULL
)paren
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|SLIST_REMOVE_HEAD
c_func
(paren
op_amp
id|ahc-&gt;scb_data-&gt;free_scbs
comma
id|links.sle
)paren
suffix:semicolon
r_return
(paren
id|scb
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return an SCB resource to the free list.&n; */
r_static
id|__inline
r_void
DECL|function|ahc_free_scb
id|ahc_free_scb
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
)paren
(brace
r_struct
id|hardware_scb
op_star
id|hscb
suffix:semicolon
id|hscb
op_assign
id|scb-&gt;hscb
suffix:semicolon
multiline_comment|/* Clean up for the next user */
id|ahc-&gt;scb_data-&gt;scbindex
(braket
id|hscb-&gt;tag
)braket
op_assign
l_int|NULL
suffix:semicolon
id|scb-&gt;flags
op_assign
id|SCB_FREE
suffix:semicolon
id|hscb-&gt;control
op_assign
l_int|0
suffix:semicolon
id|SLIST_INSERT_HEAD
c_func
(paren
op_amp
id|ahc-&gt;scb_data-&gt;free_scbs
comma
id|scb
comma
id|links.sle
)paren
suffix:semicolon
multiline_comment|/* Notify the OSM that a resource is now available. */
id|ahc_platform_scb_free
c_func
(paren
id|ahc
comma
id|scb
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_struct
id|scb
op_star
DECL|function|ahc_lookup_scb
id|ahc_lookup_scb
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
id|u_int
id|tag
)paren
(brace
r_struct
id|scb
op_star
id|scb
suffix:semicolon
id|scb
op_assign
id|ahc-&gt;scb_data-&gt;scbindex
(braket
id|tag
)braket
suffix:semicolon
r_if
c_cond
(paren
id|scb
op_ne
l_int|NULL
)paren
id|ahc_sync_scb
c_func
(paren
id|ahc
comma
id|scb
comma
id|BUS_DMASYNC_POSTREAD
op_or
id|BUS_DMASYNC_POSTWRITE
)paren
suffix:semicolon
r_return
(paren
id|scb
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_void
DECL|function|ahc_swap_with_next_hscb
id|ahc_swap_with_next_hscb
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
)paren
(brace
r_struct
id|hardware_scb
op_star
id|q_hscb
suffix:semicolon
id|u_int
id|saved_tag
suffix:semicolon
multiline_comment|/*&n;&t; * Our queuing method is a bit tricky.  The card&n;&t; * knows in advance which HSCB to download, and we&n;&t; * can&squot;t disappoint it.  To achieve this, the next&n;&t; * SCB to download is saved off in ahc-&gt;next_queued_scb.&n;&t; * When we are called to queue &quot;an arbitrary scb&quot;,&n;&t; * we copy the contents of the incoming HSCB to the one&n;&t; * the sequencer knows about, swap HSCB pointers and&n;&t; * finally assign the SCB to the tag indexed location&n;&t; * in the scb_array.  This makes sure that we can still&n;&t; * locate the correct SCB by SCB_TAG.&n;&t; */
id|q_hscb
op_assign
id|ahc-&gt;next_queued_scb-&gt;hscb
suffix:semicolon
id|saved_tag
op_assign
id|q_hscb-&gt;tag
suffix:semicolon
id|memcpy
c_func
(paren
id|q_hscb
comma
id|scb-&gt;hscb
comma
r_sizeof
(paren
op_star
id|scb-&gt;hscb
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|scb-&gt;flags
op_amp
id|SCB_CDB32_PTR
)paren
op_ne
l_int|0
)paren
(brace
id|q_hscb-&gt;shared_data.cdb_ptr
op_assign
id|ahc_htole32
c_func
(paren
id|ahc_hscb_busaddr
c_func
(paren
id|ahc
comma
id|q_hscb-&gt;tag
)paren
op_plus
m_offsetof
(paren
r_struct
id|hardware_scb
comma
id|cdb32
)paren
)paren
suffix:semicolon
)brace
id|q_hscb-&gt;tag
op_assign
id|saved_tag
suffix:semicolon
id|q_hscb-&gt;next
op_assign
id|scb-&gt;hscb-&gt;tag
suffix:semicolon
multiline_comment|/* Now swap HSCB pointers. */
id|ahc-&gt;next_queued_scb-&gt;hscb
op_assign
id|scb-&gt;hscb
suffix:semicolon
id|scb-&gt;hscb
op_assign
id|q_hscb
suffix:semicolon
multiline_comment|/* Now define the mapping from tag to SCB in the scbindex */
id|ahc-&gt;scb_data-&gt;scbindex
(braket
id|scb-&gt;hscb-&gt;tag
)braket
op_assign
id|scb
suffix:semicolon
)brace
multiline_comment|/*&n; * Tell the sequencer about a new transaction to execute.&n; */
r_static
id|__inline
r_void
DECL|function|ahc_queue_scb
id|ahc_queue_scb
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
)paren
(brace
id|ahc_swap_with_next_hscb
c_func
(paren
id|ahc
comma
id|scb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scb-&gt;hscb-&gt;tag
op_eq
id|SCB_LIST_NULL
op_logical_or
id|scb-&gt;hscb-&gt;next
op_eq
id|SCB_LIST_NULL
)paren
id|panic
c_func
(paren
l_string|&quot;Attempt to queue invalid SCB tag %x:%x&bslash;n&quot;
comma
id|scb-&gt;hscb-&gt;tag
comma
id|scb-&gt;hscb-&gt;next
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Keep a history of SCBs we&squot;ve downloaded in the qinfifo.&n;&t; */
id|ahc-&gt;qinfifo
(braket
id|ahc-&gt;qinfifonext
op_increment
)braket
op_assign
id|scb-&gt;hscb-&gt;tag
suffix:semicolon
multiline_comment|/*&n;&t; * Make sure our data is consistent from the&n;&t; * perspective of the adapter.&n;&t; */
id|ahc_sync_scb
c_func
(paren
id|ahc
comma
id|scb
comma
id|BUS_DMASYNC_PREREAD
op_or
id|BUS_DMASYNC_PREWRITE
)paren
suffix:semicolon
multiline_comment|/* Tell the adapter about the newly queued SCB */
r_if
c_cond
(paren
(paren
id|ahc-&gt;features
op_amp
id|AHC_QUEUE_REGS
)paren
op_ne
l_int|0
)paren
(brace
id|ahc_outb
c_func
(paren
id|ahc
comma
id|HNSCB_QOFF
comma
id|ahc-&gt;qinfifonext
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|ahc-&gt;features
op_amp
id|AHC_AUTOPAUSE
)paren
op_eq
l_int|0
)paren
id|ahc_pause
c_func
(paren
id|ahc
)paren
suffix:semicolon
id|ahc_outb
c_func
(paren
id|ahc
comma
id|KERNEL_QINPOS
comma
id|ahc-&gt;qinfifonext
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ahc-&gt;features
op_amp
id|AHC_AUTOPAUSE
)paren
op_eq
l_int|0
)paren
id|ahc_unpause
c_func
(paren
id|ahc
)paren
suffix:semicolon
)brace
)brace
r_static
id|__inline
r_struct
id|scsi_sense_data
op_star
DECL|function|ahc_get_sense_buf
id|ahc_get_sense_buf
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
)paren
(brace
r_int
id|offset
suffix:semicolon
id|offset
op_assign
id|scb
op_minus
id|ahc-&gt;scb_data-&gt;scbarray
suffix:semicolon
r_return
(paren
op_amp
id|ahc-&gt;scb_data-&gt;sense
(braket
id|offset
)braket
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_uint32
DECL|function|ahc_get_sense_bufaddr
id|ahc_get_sense_bufaddr
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_struct
id|scb
op_star
id|scb
)paren
(brace
r_int
id|offset
suffix:semicolon
id|offset
op_assign
id|scb
op_minus
id|ahc-&gt;scb_data-&gt;scbarray
suffix:semicolon
r_return
(paren
id|ahc-&gt;scb_data-&gt;sense_busaddr
op_plus
(paren
id|offset
op_star
r_sizeof
(paren
r_struct
id|scsi_sense_data
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/************************** Interrupt Processing ******************************/
r_static
id|__inline
r_void
id|ahc_sync_qoutfifo
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_int
id|op
)paren
suffix:semicolon
r_static
id|__inline
r_void
id|ahc_sync_tqinfifo
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_int
id|op
)paren
suffix:semicolon
r_static
id|__inline
id|u_int
id|ahc_check_cmdcmpltqueues
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_static
id|__inline
r_int
id|ahc_intr
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
suffix:semicolon
r_static
id|__inline
r_void
DECL|function|ahc_sync_qoutfifo
id|ahc_sync_qoutfifo
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_int
id|op
)paren
(brace
id|ahc_dmamap_sync
c_func
(paren
id|ahc
comma
id|ahc-&gt;shared_data_dmat
comma
id|ahc-&gt;shared_data_dmamap
comma
multiline_comment|/*offset*/
l_int|0
comma
multiline_comment|/*len*/
l_int|256
comma
id|op
)paren
suffix:semicolon
)brace
r_static
id|__inline
r_void
DECL|function|ahc_sync_tqinfifo
id|ahc_sync_tqinfifo
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
comma
r_int
id|op
)paren
(brace
macro_line|#ifdef AHC_TARGET_MODE
r_if
c_cond
(paren
(paren
id|ahc-&gt;flags
op_amp
id|AHC_TARGETROLE
)paren
op_ne
l_int|0
)paren
(brace
id|ahc_dmamap_sync
c_func
(paren
id|ahc
comma
id|ahc-&gt;shared_data_dmat
comma
id|ahc-&gt;shared_data_dmamap
comma
id|ahc_targetcmd_offset
c_func
(paren
id|ahc
comma
l_int|0
)paren
comma
r_sizeof
(paren
r_struct
id|target_cmd
)paren
op_star
id|AHC_TMODE_CMDS
comma
id|op
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/*&n; * See if the firmware has posted any completed commands&n; * into our in-core command complete fifos.&n; */
DECL|macro|AHC_RUN_QOUTFIFO
mdefine_line|#define AHC_RUN_QOUTFIFO 0x1
DECL|macro|AHC_RUN_TQINFIFO
mdefine_line|#define AHC_RUN_TQINFIFO 0x2
r_static
id|__inline
id|u_int
DECL|function|ahc_check_cmdcmpltqueues
id|ahc_check_cmdcmpltqueues
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
id|u_int
id|retval
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
id|ahc_dmamap_sync
c_func
(paren
id|ahc
comma
id|ahc-&gt;shared_data_dmat
comma
id|ahc-&gt;shared_data_dmamap
comma
multiline_comment|/*offset*/
id|ahc-&gt;qoutfifonext
comma
multiline_comment|/*len*/
l_int|1
comma
id|BUS_DMASYNC_POSTREAD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ahc-&gt;qoutfifo
(braket
id|ahc-&gt;qoutfifonext
)braket
op_ne
id|SCB_LIST_NULL
)paren
id|retval
op_or_assign
id|AHC_RUN_QOUTFIFO
suffix:semicolon
macro_line|#ifdef AHC_TARGET_MODE
r_if
c_cond
(paren
(paren
id|ahc-&gt;flags
op_amp
id|AHC_TARGETROLE
)paren
op_ne
l_int|0
op_logical_and
(paren
id|ahc-&gt;flags
op_amp
id|AHC_TQINFIFO_BLOCKED
)paren
op_eq
l_int|0
)paren
(brace
id|ahc_dmamap_sync
c_func
(paren
id|ahc
comma
id|ahc-&gt;shared_data_dmat
comma
id|ahc-&gt;shared_data_dmamap
comma
id|ahc_targetcmd_offset
c_func
(paren
id|ahc
comma
id|ahc-&gt;tqinfifofnext
)paren
comma
multiline_comment|/*len*/
r_sizeof
(paren
r_struct
id|target_cmd
)paren
comma
id|BUS_DMASYNC_POSTREAD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ahc-&gt;targetcmds
(braket
id|ahc-&gt;tqinfifonext
)braket
dot
id|cmd_valid
op_ne
l_int|0
)paren
id|retval
op_or_assign
id|AHC_RUN_TQINFIFO
suffix:semicolon
)brace
macro_line|#endif
r_return
(paren
id|retval
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Catch an interrupt from the adapter&n; */
r_static
id|__inline
r_int
DECL|function|ahc_intr
id|ahc_intr
c_func
(paren
r_struct
id|ahc_softc
op_star
id|ahc
)paren
(brace
id|u_int
id|intstat
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ahc-&gt;pause
op_amp
id|INTEN
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Our interrupt is not enabled on the chip&n;&t;&t; * and may be disabled for re-entrancy reasons,&n;&t;&t; * so just return.  This is likely just a shared&n;&t;&t; * interrupt.&n;&t;&t; */
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Instead of directly reading the interrupt status register,&n;&t; * infer the cause of the interrupt by checking our in-core&n;&t; * completion queues.  This avoids a costly PCI bus read in&n;&t; * most cases.&n;&t; */
r_if
c_cond
(paren
(paren
id|ahc-&gt;flags
op_amp
(paren
id|AHC_ALL_INTERRUPTS
op_or
id|AHC_EDGE_INTERRUPT
)paren
)paren
op_eq
l_int|0
op_logical_and
(paren
id|ahc_check_cmdcmpltqueues
c_func
(paren
id|ahc
)paren
op_ne
l_int|0
)paren
)paren
id|intstat
op_assign
id|CMDCMPLT
suffix:semicolon
r_else
(brace
id|intstat
op_assign
id|ahc_inb
c_func
(paren
id|ahc
comma
id|INTSTAT
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|intstat
op_amp
id|INT_PEND
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#if AHC_PCI_CONFIG &gt; 0
r_if
c_cond
(paren
id|ahc-&gt;unsolicited_ints
OG
l_int|500
)paren
(brace
id|ahc-&gt;unsolicited_ints
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ahc-&gt;chip
op_amp
id|AHC_PCI
)paren
op_ne
l_int|0
op_logical_and
(paren
id|ahc_inb
c_func
(paren
id|ahc
comma
id|ERROR
)paren
op_amp
id|PCIERRSTAT
)paren
op_ne
l_int|0
)paren
id|ahc
op_member_access_from_pointer
id|bus_intr
c_func
(paren
id|ahc
)paren
suffix:semicolon
)brace
macro_line|#endif
id|ahc-&gt;unsolicited_ints
op_increment
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|ahc-&gt;unsolicited_ints
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|intstat
op_amp
id|CMDCMPLT
)paren
(brace
id|ahc_outb
c_func
(paren
id|ahc
comma
id|CLRINT
comma
id|CLRCMDINT
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Ensure that the chip sees that we&squot;ve cleared&n;&t;&t; * this interrupt before we walk the output fifo.&n;&t;&t; * Otherwise, we may, due to posted bus writes,&n;&t;&t; * clear the interrupt after we finish the scan,&n;&t;&t; * and after the sequencer has added new entries&n;&t;&t; * and asserted the interrupt again.&n;&t;&t; */
id|ahc_flush_device_writes
c_func
(paren
id|ahc
)paren
suffix:semicolon
id|ahc_run_qoutfifo
c_func
(paren
id|ahc
)paren
suffix:semicolon
macro_line|#ifdef AHC_TARGET_MODE
r_if
c_cond
(paren
(paren
id|ahc-&gt;flags
op_amp
id|AHC_TARGETROLE
)paren
op_ne
l_int|0
)paren
id|ahc_run_tqinfifo
c_func
(paren
id|ahc
comma
multiline_comment|/*paused*/
id|FALSE
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n;&t; * Handle statuses that may invalidate our cached&n;&t; * copy of INTSTAT separately.&n;&t; */
r_if
c_cond
(paren
id|intstat
op_eq
l_int|0xFF
op_logical_and
(paren
id|ahc-&gt;features
op_amp
id|AHC_REMOVABLE
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Hot eject.  Do nothing */
)brace
r_else
r_if
c_cond
(paren
id|intstat
op_amp
id|BRKADRINT
)paren
(brace
id|ahc_handle_brkadrint
c_func
(paren
id|ahc
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|intstat
op_amp
(paren
id|SEQINT
op_or
id|SCSIINT
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|ahc_pause_bug_fix
c_func
(paren
id|ahc
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|intstat
op_amp
id|SEQINT
)paren
op_ne
l_int|0
)paren
id|ahc_handle_seqint
c_func
(paren
id|ahc
comma
id|intstat
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|intstat
op_amp
id|SCSIINT
)paren
op_ne
l_int|0
)paren
id|ahc_handle_scsiint
c_func
(paren
id|ahc
comma
id|intstat
)paren
suffix:semicolon
)brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif  /* _AIC7XXX_INLINE_H_ */
eof
