multiline_comment|/* DO NOT EDIT - Generated automatically by script_asm.pl */
DECL|variable|SCRIPT
r_static
id|u32
id|SCRIPT
(braket
)braket
op_assign
(brace
multiline_comment|/*&n;&n;&n;; NCR 53c810 driver, main script&n;; Sponsored by &n;;&t;iX Multiuser Multitasking Magazine&n;;&t;hm@ix.de&n;;&n;; Copyright 1993, 1994, 1995 Drew Eckhardt&n;;      Visionary Computing &n;;      (Unix and Linux consulting and custom programming)&n;;      drew@PoohSticks.ORG&n;;      +1 (303) 786-7975&n;;&n;; TolerANT and SCSI SCRIPTS are registered trademarks of NCR Corporation.&n;;&n;; PRE-ALPHA&n;;&n;; For more information, please consult &n;;&n;; NCR 53C810&n;; PCI-SCSI I/O Processor&n;; Data Manual&n;;&n;; NCR 53C710 &n;; SCSI I/O Processor&n;; Programmers Guide&n;;&n;; NCR Microelectronics&n;; 1635 Aeroplaza Drive&n;; Colorado Springs, CO 80916&n;; 1+ (719) 578-3400&n;;&n;; Toll free literature number&n;; +1 (800) 334-5454&n;;&n;; IMPORTANT : This code is self modifying due to the limitations of &n;;&t;the NCR53c7,8xx series chips.  Persons debugging this code with&n;;&t;the remote debugger should take this into account, and NOT set&n;;&t;breakpoints in modified instructions.&n;;&n;; Design:&n;; The NCR53c7,8xx family of SCSI chips are busmasters with an onboard &n;; microcontroller using a simple instruction set.   &n;;&n;; So, to minimize the effects of interrupt latency, and to maximize &n;; throughput, this driver offloads the practical maximum amount &n;; of processing to the SCSI chip while still maintaining a common&n;; structure.&n;;&n;; Where tradeoffs were needed between efficiency on the older&n;; chips and the newer NCR53c800 series, the NCR53c800 series &n;; was chosen.&n;;&n;; While the NCR53c700 and NCR53c700-66 lacked the facilities to fully&n;; automate SCSI transfers without host processor intervention, this &n;; isn&squot;t the case with the NCR53c710 and newer chips which allow &n;;&n;; - reads and writes to the internal registers from within the SCSI&n;; &t;scripts, allowing the SCSI SCRIPTS(tm) code to save processor&n;; &t;state so that multiple threads of execution are possible, and also&n;; &t;provide an ALU for loop control, etc.&n;; &n;; - table indirect addressing for some instructions. This allows &n;;&t;pointers to be located relative to the DSA ((Data Structure&n;;&t;Address) register.&n;;&n;; These features make it possible to implement a mailbox style interface,&n;; where the same piece of code is run to handle I/O for multiple threads&n;; at once minimizing our need to relocate code.  Since the NCR53c700/&n;; NCR53c800 series have a unique combination of features, making a &n;; a standard ingoing/outgoing mailbox system, costly, I&squot;ve modified it.&n;;&n;; - Mailboxes are a mixture of code and data.  This lets us greatly&n;; &t;simplify the NCR53c810 code and do things that would otherwise&n;;&t;not be possible.&n;;&n;; The saved data pointer is now implemented as follows :&n;;&n;; &t;Control flow has been architected such that if control reaches&n;;&t;munge_save_data_pointer, on a restore pointers message or &n;;&t;reconnection, a jump to the address formerly in the TEMP register&n;;&t;will allow the SCSI command to resume execution.&n;;&n;&n;;&n;; Note : the DSA structures must be aligned on 32 bit boundaries,&n;; since the source and destination of MOVE MEMORY instructions &n;; must share the same alignment and this is the alignment of the&n;; NCR registers.&n;;&n;&n;ABSOLUTE dsa_temp_lun = 0&t;&t;; Patch to lun for current dsa&n;ABSOLUTE dsa_temp_next = 0&t;&t;; Patch to dsa next for current dsa&n;ABSOLUTE dsa_temp_addr_next = 0&t;&t;; Patch to address of dsa next address &n;&t;&t;&t;&t;&t;; &t;for current dsa&n;ABSOLUTE dsa_temp_sync = 0&t;&t;; Patch to address of per-target&n;&t;&t;&t;&t;&t;;&t;sync routine&n;ABSOLUTE dsa_temp_target = 0&t;&t;; Patch to id for current dsa&n;ABSOLUTE dsa_temp_addr_saved_pointer = 0; Patch to address of per-command&n;&t;&t;&t;&t;&t;; &t;saved data pointer&n;ABSOLUTE dsa_temp_addr_residual = 0&t;; Patch to address of per-command&n;&t;&t;&t;&t;&t;;&t;current residual code&n;ABSOLUTE dsa_temp_addr_saved_residual = 0; Patch to address of per-command&n;&t;&t;&t;&t;&t;; saved residual code&n;ABSOLUTE dsa_temp_addr_new_value = 0&t;; Address of value for JUMP operand&n;ABSOLUTE dsa_temp_addr_array_value = 0 &t;; Address to copy to&n;ABSOLUTE dsa_temp_addr_dsa_value = 0&t;; Address of this DSA value&n;&n;;&n;; Once a device has initiated reselection, we need to compare it &n;; against the singly linked list of commands which have disconnected&n;; and are pending reselection.  These commands are maintained in &n;; an unordered singly linked list of DSA structures, through the&n;; DSA pointers at their &squot;centers&squot; headed by the reconnect_dsa_head&n;; pointer.&n;; &n;; To avoid complications in removing commands from the list,&n;; I minimize the amount of expensive (at eight operations per&n;; addition @ 500-600ns each) pointer operations which must&n;; be done in the NCR driver by precomputing them on the &n;; host processor during dsa structure generation.&n;;&n;; The fixed-up per DSA code knows how to recognize the nexus&n;; associated with the corresponding SCSI command, and modifies&n;; the source and destination pointers for the MOVE MEMORY &n;; instruction which is executed when reselected_ok is called&n;; to remove the command from the list.  Similarly, DSA is &n;; loaded with the address of the next DSA structure and&n;; reselected_check_next is called if a failure occurs.&n;;&n;; Perhaps more concisely, the net effect of the mess is &n;;&n;; for (dsa = reconnect_dsa_head, dest = &amp;reconnect_dsa_head, &n;;     src = NULL; dsa; dest = &amp;dsa-&gt;next, dsa = dsa-&gt;next) {&n;; &t;src = &amp;dsa-&gt;next;&n;; &t;if (target_id == dsa-&gt;id &amp;&amp; target_lun == dsa-&gt;lun) {&n;; &t;&t;*dest = *src;&n;; &t;&t;break;&n;;         }&t;&n;; }&n;;&n;; if (!dsa)&n;;           error (int_err_unexpected_reselect);&n;; else  &n;;     longjmp (dsa-&gt;jump_resume, 0);&n;;&n;; &t;&n;&n;&n;; Define DSA structure used for mailboxes&n;ENTRY dsa_code_template&n;dsa_code_template:&n;ENTRY dsa_code_begin&n;dsa_code_begin:&n;&t;MOVE dmode_memory_to_ncr TO DMODE&n;&n;at 0x00000000 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE MEMORY 4, dsa_temp_addr_dsa_value, addr_scratch&n;&n;at 0x00000002 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000005 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;CALL scratch_to_dsa&n;&n;at 0x00000007 : */
l_int|0x88080000
comma
l_int|0x00000980
comma
multiline_comment|/*&n;&t;CALL select&n;&n;at 0x00000009 : */
l_int|0x88080000
comma
l_int|0x000001fc
comma
multiline_comment|/*&n;; Handle the phase mismatch which may have resulted from the &n;; MOVE FROM dsa_msgout if we returned here.  The CLEAR ATN &n;; may or may not be necessary, and we should update script_asm.pl&n;; to handle multiple pieces.&n;    CLEAR ATN&n;&n;at 0x0000000b : */
l_int|0x60000008
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x0000000d : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;; Replace second operand with address of JUMP instruction dest operand&n;; in schedule table for this DSA.  Becomes dsa_jump_dest in 53c7,8xx.c.&n;ENTRY dsa_code_fix_jump&n;dsa_code_fix_jump:&n;&t;MOVE MEMORY 4, NOP_insn, 0&n;&n;at 0x0000000f : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP select_done&n;&n;at 0x00000012 : */
l_int|0x80080000
comma
l_int|0x00000224
comma
multiline_comment|/*&n;&n;; wrong_dsa loads the DSA register with the value of the dsa_next&n;; field.&n;;&n;wrong_dsa:&n;;&t;&t;Patch the MOVE MEMORY INSTRUCTION such that &n;;&t;&t;the destination address is the address of the OLD &n;;&t;&t;next pointer.&n;;&n;&t;MOVE MEMORY 4, dsa_temp_addr_next, reselected_ok + 8&n;&n;at 0x00000014 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000758
comma
multiline_comment|/*&n;&t;MOVE dmode_memory_to_ncr TO DMODE&t;&n;&n;at 0x00000017 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;;&n;; &t;Move the _contents_ of the next pointer into the DSA register as &n;;&t;the next I_T_L or I_T_L_Q tupple to check against the established&n;;&t;nexus.&n;;&n;&t;MOVE MEMORY 4, dsa_temp_next, addr_scratch&n;&n;at 0x00000019 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x0000001c : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;CALL scratch_to_dsa&n;&n;at 0x0000001e : */
l_int|0x88080000
comma
l_int|0x00000980
comma
multiline_comment|/*&n;&t;JUMP reselected_check_next&n;&n;at 0x00000020 : */
l_int|0x80080000
comma
l_int|0x000006a4
comma
multiline_comment|/*&n;&n;ABSOLUTE dsa_save_data_pointer = 0&n;ENTRY dsa_code_save_data_pointer&n;dsa_code_save_data_pointer:&n;    &t;MOVE dmode_ncr_to_memory TO DMODE&n;&n;at 0x00000022 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    &t;MOVE MEMORY 4, addr_temp, dsa_temp_addr_saved_pointer&n;&n;at 0x00000024 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    &t;MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000027 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;; HARD CODED : 24 bytes needs to agree with 53c7,8xx.h&n;    &t;MOVE MEMORY 24, dsa_temp_addr_residual, dsa_temp_addr_saved_residual&n;&n;at 0x00000029 : */
l_int|0xc0000018
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;        CLEAR ACK&n;&n;at 0x0000002c : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;&n;    &t;RETURN&n;&n;at 0x0000002e : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;ABSOLUTE dsa_restore_pointers = 0&n;ENTRY dsa_code_restore_pointers&n;dsa_code_restore_pointers:&n;    &t;MOVE dmode_memory_to_ncr TO DMODE&n;&n;at 0x00000030 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    &t;MOVE MEMORY 4, dsa_temp_addr_saved_pointer, addr_temp&n;&n;at 0x00000032 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    &t;MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000035 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;; HARD CODED : 24 bytes needs to agree with 53c7,8xx.h&n;    &t;MOVE MEMORY 24, dsa_temp_addr_saved_residual, dsa_temp_addr_residual&n;&n;at 0x00000037 : */
l_int|0xc0000018
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;        CLEAR ACK&n;&n;at 0x0000003a : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;&n;    &t;RETURN&n;&n;at 0x0000003c : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;ABSOLUTE dsa_check_reselect = 0&n;; dsa_check_reselect determines whether or not the current target and&n;; lun match the current DSA&n;ENTRY dsa_code_check_reselect&n;dsa_code_check_reselect:&n;&t;MOVE SSID TO SFBR&t;&t;; SSID contains 3 bit target ID&n;&n;at 0x0000003e : */
l_int|0x720a0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;; FIXME : we need to accommodate bit fielded and binary here for &squot;7xx/&squot;8xx chips&n;&t;JUMP REL (wrong_dsa), IF NOT dsa_temp_target, AND MASK 0xf8&n;&n;at 0x00000040 : */
l_int|0x8084f800
comma
l_int|0x00ffff48
comma
multiline_comment|/*&n;;&n;; Hack - move to scratch first, since SFBR is not writeable&n;; &t;via the CPU and hence a MOVE MEMORY instruction.&n;;&n;&t;MOVE dmode_memory_to_ncr TO DMODE&n;&n;at 0x00000042 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE MEMORY 1, reselected_identify, addr_scratch&n;&n;at 0x00000044 : */
l_int|0xc0000001
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000047 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE SCRATCH0 TO SFBR&n;&n;at 0x00000049 : */
l_int|0x72340000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;; FIXME : we need to accommodate bit fielded and binary here for &squot;7xx/&squot;8xx chips&n;&t;JUMP REL (wrong_dsa), IF NOT dsa_temp_lun, AND MASK 0xf8&n;&n;at 0x0000004b : */
l_int|0x8084f800
comma
l_int|0x00ffff1c
comma
multiline_comment|/*&n;;&t;&t;Patch the MOVE MEMORY INSTRUCTION such that&n;;&t;&t;the source address is the address of this dsa&squot;s&n;;&t;&t;next pointer.&n;&t;MOVE MEMORY 4, dsa_temp_addr_next, reselected_ok + 4&n;&n;at 0x0000004d : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000754
comma
multiline_comment|/*&n;&t;CALL reselected_ok&n;&n;at 0x00000050 : */
l_int|0x88080000
comma
l_int|0x00000750
comma
multiline_comment|/*&n;&t;CALL dsa_temp_sync&t;&n;&n;at 0x00000052 : */
l_int|0x88080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;; Release ACK on the IDENTIFY message _after_ we&squot;ve set the synchronous &n;; transfer parameters! &n;&t;CLEAR ACK&n;&n;at 0x00000054 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;; Implicitly restore pointers on reselection, so a RETURN&n;; will transfer control back to the right spot.&n;    &t;CALL REL (dsa_code_restore_pointers)&n;&n;at 0x00000056 : */
l_int|0x88880000
comma
l_int|0x00ffff60
comma
multiline_comment|/*&n;    &t;RETURN&n;&n;at 0x00000058 : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;ENTRY dsa_zero&n;dsa_zero:&n;ENTRY dsa_code_template_end&n;dsa_code_template_end:&n;&n;; Perform sanity check for dsa_fields_start == dsa_code_template_end - &n;; dsa_zero, puke.&n;&n;ABSOLUTE dsa_fields_start =  0&t;; Sanity marker&n;&t;&t;&t;&t;; &t;pad 48 bytes (fix this RSN)&n;ABSOLUTE dsa_next = 48&t;&t;; len 4 Next DSA&n; &t;&t;&t;&t;; del 4 Previous DSA address&n;ABSOLUTE dsa_cmnd = 56&t;&t;; len 4 Scsi_Cmnd * for this thread.&n;ABSOLUTE dsa_select = 60&t;; len 4 Device ID, Period, Offset for &n;&t;&t;&t; &t;;&t;table indirect select&n;ABSOLUTE dsa_msgout = 64&t;; len 8 table indirect move parameter for &n;&t;&t;&t;&t;;       select message&n;ABSOLUTE dsa_cmdout = 72&t;; len 8 table indirect move parameter for &n;&t;&t;&t;&t;;&t;command&n;ABSOLUTE dsa_dataout = 80&t;; len 4 code pointer for dataout&n;ABSOLUTE dsa_datain = 84&t;; len 4 code pointer for datain&n;ABSOLUTE dsa_msgin = 88&t;&t;; len 8 table indirect move for msgin&n;ABSOLUTE dsa_status = 96 &t;; len 8 table indirect move for status byte&n;ABSOLUTE dsa_msgout_other = 104&t;; len 8 table indirect for normal message out&n;&t;&t;&t;&t;; (Synchronous transfer negotiation, etc).&n;ABSOLUTE dsa_end = 112&n;&n;ABSOLUTE schedule = 0 &t;&t;; Array of JUMP dsa_begin or JUMP (next),&n;&t;&t;&t;&t;; terminated by a call to JUMP wait_reselect&n;&n;; Linked lists of DSA structures&n;ABSOLUTE reconnect_dsa_head = 0&t;; Link list of DSAs which can reconnect&n;ABSOLUTE addr_reconnect_dsa_head = 0 ; Address of variable containing&n;&t;&t;&t;&t;; address of reconnect_dsa_head&n;&n;; These select the source and destination of a MOVE MEMORY instruction&n;ABSOLUTE dmode_memory_to_memory = 0x0&n;ABSOLUTE dmode_memory_to_ncr = 0x0&n;ABSOLUTE dmode_ncr_to_memory = 0x0&n;&n;ABSOLUTE addr_scratch = 0x0&n;ABSOLUTE addr_temp = 0x0&n;&n;&n;; Interrupts - &n;; MSB indicates type&n;; 0&t;handle error condition&n;; 1 &t;handle message &n;; 2 &t;handle normal condition&n;; 3&t;debugging interrupt&n;; 4 &t;testing interrupt &n;; Next byte indicates specific error&n;&n;; XXX not yet implemented, I&squot;m not sure if I want to - &n;; Next byte indicates the routine the error occurred in&n;; The LSB indicates the specific place the error occurred&n; &n;ABSOLUTE int_err_unexpected_phase = 0x00000000&t;; Unexpected phase encountered&n;ABSOLUTE int_err_selected = 0x00010000&t;&t;; SELECTED (nee RESELECTED)&n;ABSOLUTE int_err_unexpected_reselect = 0x00020000 &n;ABSOLUTE int_err_check_condition = 0x00030000&t;&n;ABSOLUTE int_err_no_phase = 0x00040000&n;ABSOLUTE int_msg_wdtr = 0x01000000&t;&t;; WDTR message received&n;ABSOLUTE int_msg_sdtr = 0x01010000&t;&t;; SDTR received&n;ABSOLUTE int_msg_1 = 0x01020000&t;&t;&t;; single byte special message&n;&t;&t;&t;&t;&t;&t;; received&n;&n;ABSOLUTE int_norm_select_complete = 0x02000000&t;; Select complete, reprogram&n;&t;&t;&t;&t;&t;&t;; registers.&n;ABSOLUTE int_norm_reselect_complete = 0x02010000&t;; Nexus established&n;ABSOLUTE int_norm_command_complete = 0x02020000 ; Command complete&n;ABSOLUTE int_norm_disconnected = 0x02030000&t;; Disconnected &n;ABSOLUTE int_norm_aborted =0x02040000&t;&t;; Aborted *dsa&n;ABSOLUTE int_norm_reset = 0x02050000&t;&t;; Generated BUS reset.&n;ABSOLUTE int_debug_break = 0x03000000&t;&t;; Break point&n;&n;ABSOLUTE int_debug_panic = 0x030b0000&t;&t;; Panic driver&n;&n;&n;ABSOLUTE int_test_1 = 0x04000000&t;&t;; Test 1 complete&n;ABSOLUTE int_test_2 = 0x04010000&t;&t;; Test 2 complete&n;ABSOLUTE int_test_3 = 0x04020000&t;&t;; Test 3 complete&n;&n;&n;; These should start with 0x05000000, with low bits incrementing for &n;; each one.&n;&n;&n;&t;&t;&t;&t;&t;&t;&n;ABSOLUTE NCR53c7xx_msg_abort = 0&t;; Pointer to abort message&n;ABSOLUTE NCR53c7xx_msg_reject = 0       ; Pointer to reject message&n;ABSOLUTE NCR53c7xx_zero&t;= 0&t;&t;; long with zero in it, use for source&n;ABSOLUTE NCR53c7xx_sink = 0&t;&t;; long to dump worthless data in&n;ABSOLUTE NOP_insn = 0&t;&t;&t;; NOP instruction&n;&n;; Pointer to message, potentially multi-byte&n;ABSOLUTE msg_buf = 0&n;&n;; Pointer to holding area for reselection information&n;ABSOLUTE reselected_identify = 0&n;ABSOLUTE reselected_tag = 0&n;&n;; Request sense command pointer, it&squot;s a 6 byte command, should&n;; be constant for all commands since we always want 16 bytes of &n;; sense and we don&squot;t need to change any fields as we did under &n;; SCSI-I when we actually cared about the LUN field.&n;;EXTERNAL NCR53c7xx_sense&t;&t;; Request sense command&n;&n;&n;; dsa_schedule  &n;; PURPOSE : after a DISCONNECT message has been received, and pointers&n;;&t;saved, insert the current DSA structure at the head of the &n;; &t;disconnected queue and fall through to the scheduler.&n;;&n;; CALLS : OK&n;;&n;; INPUTS : dsa - current DSA structure, reconnect_dsa_head - list&n;;&t;of disconnected commands&n;;&n;; MODIFIES : SCRATCH, reconnect_dsa_head&n;; &n;; EXITS : always passes control to schedule&n;&n;ENTRY dsa_schedule&n;dsa_schedule:&n;&n;&n;&n;&n;;&n;; Calculate the address of the next pointer within the DSA &n;; structure of the command that is currently disconnecting&n;;&n;    CALL dsa_to_scratch&n;&n;at 0x0000005a : */
l_int|0x88080000
comma
l_int|0x00000938
comma
multiline_comment|/*&n;    MOVE SCRATCH0 + dsa_next TO SCRATCH0&n;&n;at 0x0000005c : */
l_int|0x7e343000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH1 + 0 TO SCRATCH1 WITH CARRY&n;&n;at 0x0000005e : */
l_int|0x7f350000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH2 + 0 TO SCRATCH2 WITH CARRY&n;&n;at 0x00000060 : */
l_int|0x7f360000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH3 + 0 TO SCRATCH3 WITH CARRY&n;&n;at 0x00000062 : */
l_int|0x7f370000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;; Point the next field of this DSA structure at the current disconnected &n;; list&n;    MOVE dmode_ncr_to_memory TO DMODE&n;&n;at 0x00000064 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, addr_scratch, dsa_schedule_insert + 8&n;&n;at 0x00000066 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x000001b4
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000069 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;dsa_schedule_insert:&n;    MOVE MEMORY 4, reconnect_dsa_head, 0 &n;&n;at 0x0000006b : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;; And update the head pointer.&n;    CALL dsa_to_scratch&n;&n;at 0x0000006e : */
l_int|0x88080000
comma
l_int|0x00000938
comma
multiline_comment|/*&n;    MOVE dmode_ncr_to_memory TO DMODE&t;&n;&n;at 0x00000070 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, addr_scratch, reconnect_dsa_head&n;&n;at 0x00000072 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000075 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;    MOVE SCNTL2 &amp; 0x7f TO SCNTL2&n;&n;at 0x00000077 : */
l_int|0x7c027f00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x00000079 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;    WAIT DISCONNECT&n;&n;at 0x0000007b : */
l_int|0x48000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;&n;&n;&n;&n;    JUMP schedule&n;&n;at 0x0000007d : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;;&n;; select&n;;&n;; PURPOSE : establish a nexus for the SCSI command referenced by DSA.&n;;&t;On success, the current DSA structure is removed from the issue &n;;&t;queue.  Usually, this is entered as a fall-through from schedule,&n;;&t;although the contingent allegiance handling code will write&n;;&t;the select entry address to the DSP to restart a command as a &n;;&t;REQUEST SENSE.  A message is sent (usually IDENTIFY, although&n;;&t;additional SDTR or WDTR messages may be sent).  COMMAND OUT&n;;&t;is handled.&n;;&n;; INPUTS : DSA - SCSI command, issue_dsa_head&n;;&n;; CALLS : NOT OK&n;;&n;; MODIFIES : SCRATCH, issue_dsa_head&n;;&n;; EXITS : on reselection or selection, go to select_failed&n;;&t;otherwise, RETURN so control is passed back to &n;;&t;dsa_begin.&n;;&n;&n;ENTRY select&n;select:&n;&n;&n;&n;&n;&n;&n;&n;&n;&n;&n;&n;&n;    CLEAR TARGET&n;&n;at 0x0000007f : */
l_int|0x60000200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;; XXX&n;;&n;; In effect, SELECTION operations are backgrounded, with execution&n;; continuing until code which waits for REQ or a fatal interrupt is &n;; encountered.&n;;&n;; So, for more performance, we could overlap the code which removes &n;; the command from the NCRs issue queue with the selection, but &n;; at this point I don&squot;t want to deal with the error recovery.&n;;&n;&n;&n;    SELECT ATN FROM dsa_select, select_failed&n;&n;at 0x00000081 : */
l_int|0x4300003c
comma
l_int|0x000007a4
comma
multiline_comment|/*&n;    JUMP select_msgout, WHEN MSG_OUT&n;&n;at 0x00000083 : */
l_int|0x860b0000
comma
l_int|0x00000214
comma
multiline_comment|/*&n;ENTRY select_msgout&n;select_msgout:&n;    MOVE FROM dsa_msgout, WHEN MSG_OUT&n;&n;at 0x00000085 : */
l_int|0x1e000000
comma
l_int|0x00000040
comma
multiline_comment|/*&n;&n;&n;&n;&n;&n;&n;&n;&n;&n;&n;   RETURN&n;&n;at 0x00000087 : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;; &n;; select_done&n;; &n;; PURPOSE: continue on to normal data transfer; called as the exit &n;;&t;point from dsa_begin.&n;;&n;; INPUTS: dsa&n;;&n;; CALLS: OK&n;;&n;;&n;&n;select_done:&n;&n;&n;&n;&n;&n;&n;&n;; After a successful selection, we should get either a CMD phase or &n;; some transfer request negotiation message.&n;&n;    JUMP cmdout, WHEN CMD&n;&n;at 0x00000089 : */
l_int|0x820b0000
comma
l_int|0x00000244
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN NOT MSG_IN &n;&n;at 0x0000008b : */
l_int|0x9f030000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;select_msg_in:&n;    CALL msg_in, WHEN MSG_IN&n;&n;at 0x0000008d : */
l_int|0x8f0b0000
comma
l_int|0x00000404
comma
multiline_comment|/*&n;    JUMP select_msg_in, WHEN MSG_IN&n;&n;at 0x0000008f : */
l_int|0x870b0000
comma
l_int|0x00000234
comma
multiline_comment|/*&n;&n;cmdout:&n;    INT int_err_unexpected_phase, WHEN NOT CMD&n;&n;at 0x00000091 : */
l_int|0x9a030000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;&n;ENTRY cmdout_cmdout&n;cmdout_cmdout:&n;&n;    MOVE FROM dsa_cmdout, WHEN CMD&n;&n;at 0x00000093 : */
l_int|0x1a000000
comma
l_int|0x00000048
comma
multiline_comment|/*&n;&n;&n;&n;&n;;&n;; data_transfer  &n;; other_out&n;; other_in&n;; other_transfer&n;;&n;; PURPOSE : handle the main data transfer for a SCSI command in &n;;&t;several parts.  In the first part, data_transfer, DATA_IN&n;;&t;and DATA_OUT phases are allowed, with the user provided&n;;&t;code (usually dynamically generated based on the scatter/gather&n;;&t;list associated with a SCSI command) called to handle these &n;;&t;phases.&n;;&n;;&t;After control has passed to one of the user provided &n;;&t;DATA_IN or DATA_OUT routines, back calls are made to &n;;&t;other_transfer_in or other_transfer_out to handle non-DATA IN&n;;&t;and DATA OUT phases respectively, with the state of the active&n;;&t;data pointer being preserved in TEMP.&n;;&n;;&t;On completion, the user code passes control to other_transfer&n;;&t;which causes DATA_IN and DATA_OUT to result in unexpected_phase&n;;&t;interrupts so that data overruns may be trapped.&n;;&n;; INPUTS : DSA - SCSI command&n;;&n;; CALLS : OK in data_transfer_start, not ok in other_out and other_in, ok in&n;;&t;other_transfer&n;;&n;; MODIFIES : SCRATCH&n;;&n;; EXITS : if STATUS IN is detected, signifying command completion,&n;;&t;the NCR jumps to command_complete.  If MSG IN occurs, a &n;;&t;CALL is made to msg_in.  Otherwise, other_transfer runs in &n;;&t;an infinite loop.&n;;&t;&n;&n;ENTRY data_transfer&n;data_transfer:&n;    JUMP cmdout_cmdout, WHEN CMD&n;&n;at 0x00000095 : */
l_int|0x820b0000
comma
l_int|0x0000024c
comma
multiline_comment|/*&n;    CALL msg_in, WHEN MSG_IN&n;&n;at 0x00000097 : */
l_int|0x8f0b0000
comma
l_int|0x00000404
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN MSG_OUT&n;&n;at 0x00000099 : */
l_int|0x9e0b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP do_dataout, WHEN DATA_OUT&n;&n;at 0x0000009b : */
l_int|0x800b0000
comma
l_int|0x0000028c
comma
multiline_comment|/*&n;    JUMP do_datain, WHEN DATA_IN&n;&n;at 0x0000009d : */
l_int|0x810b0000
comma
l_int|0x000002e4
comma
multiline_comment|/*&n;    JUMP command_complete, WHEN STATUS&n;&n;at 0x0000009f : */
l_int|0x830b0000
comma
l_int|0x0000060c
comma
multiline_comment|/*&n;    JUMP data_transfer&n;&n;at 0x000000a1 : */
l_int|0x80080000
comma
l_int|0x00000254
comma
multiline_comment|/*&n;ENTRY end_data_transfer&n;end_data_transfer:&n;&n;;&n;; FIXME: On NCR53c700 and NCR53c700-66 chips, do_dataout/do_datain &n;; should be fixed up whenever the nexus changes so it can point to the &n;; correct routine for that command.&n;;&n;&n;&n;; Nasty jump to dsa-&gt;dataout&n;do_dataout:&n;    CALL dsa_to_scratch&n;&n;at 0x000000a3 : */
l_int|0x88080000
comma
l_int|0x00000938
comma
multiline_comment|/*&n;    MOVE SCRATCH0 + dsa_dataout TO SCRATCH0&t;&n;&n;at 0x000000a5 : */
l_int|0x7e345000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH1 + 0 TO SCRATCH1 WITH CARRY &n;&n;at 0x000000a7 : */
l_int|0x7f350000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH2 + 0 TO SCRATCH2 WITH CARRY &n;&n;at 0x000000a9 : */
l_int|0x7f360000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH3 + 0 TO SCRATCH3 WITH CARRY &n;&n;at 0x000000ab : */
l_int|0x7f370000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE dmode_ncr_to_memory TO DMODE&n;&n;at 0x000000ad : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, addr_scratch, dataout_to_jump + 4&n;&n;at 0x000000af : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x000002d4
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x000000b2 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;dataout_to_jump:&n;    MOVE MEMORY 4, 0, dataout_jump + 4 &n;&n;at 0x000000b4 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x000002e0
comma
multiline_comment|/*&n;dataout_jump:&n;    JUMP 0&n;&n;at 0x000000b7 : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;; Nasty jump to dsa-&gt;dsain&n;do_datain:&n;    CALL dsa_to_scratch&n;&n;at 0x000000b9 : */
l_int|0x88080000
comma
l_int|0x00000938
comma
multiline_comment|/*&n;    MOVE SCRATCH0 + dsa_datain TO SCRATCH0&t;&n;&n;at 0x000000bb : */
l_int|0x7e345400
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH1 + 0 TO SCRATCH1 WITH CARRY &n;&n;at 0x000000bd : */
l_int|0x7f350000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH2 + 0 TO SCRATCH2 WITH CARRY &n;&n;at 0x000000bf : */
l_int|0x7f360000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH3 + 0 TO SCRATCH3 WITH CARRY &n;&n;at 0x000000c1 : */
l_int|0x7f370000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE dmode_ncr_to_memory TO DMODE&n;&n;at 0x000000c3 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, addr_scratch, datain_to_jump + 4&n;&n;at 0x000000c5 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x0000032c
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&t;&t;&n;&n;at 0x000000c8 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;ENTRY datain_to_jump&n;datain_to_jump:&n;    MOVE MEMORY 4, 0, datain_jump + 4&n;&n;at 0x000000ca : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000338
comma
multiline_comment|/*&n;&n;&n;&n;datain_jump:&n;    JUMP 0&n;&n;at 0x000000cd : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;&n;; Note that other_out and other_in loop until a non-data phase&n;; is discovered, so we only execute return statements when we&n;; can go on to the next data phase block move statement.&n;&n;ENTRY other_out&n;other_out:&n;&n;&n;&n;    INT int_err_unexpected_phase, WHEN CMD&n;&n;at 0x000000cf : */
l_int|0x9a0b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP msg_in_restart, WHEN MSG_IN &n;&n;at 0x000000d1 : */
l_int|0x870b0000
comma
l_int|0x000003e4
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN MSG_OUT&n;&n;at 0x000000d3 : */
l_int|0x9e0b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN DATA_IN&n;&n;at 0x000000d5 : */
l_int|0x990b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP command_complete, WHEN STATUS&n;&n;at 0x000000d7 : */
l_int|0x830b0000
comma
l_int|0x0000060c
comma
multiline_comment|/*&n;    JUMP other_out, WHEN NOT DATA_OUT&n;&n;at 0x000000d9 : */
l_int|0x80030000
comma
l_int|0x0000033c
comma
multiline_comment|/*&n;    RETURN&n;&n;at 0x000000db : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;ENTRY other_in&n;other_in:&n;&n;&n;&n;    INT int_err_unexpected_phase, WHEN CMD&n;&n;at 0x000000dd : */
l_int|0x9a0b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP msg_in_restart, WHEN MSG_IN &n;&n;at 0x000000df : */
l_int|0x870b0000
comma
l_int|0x000003e4
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN MSG_OUT&n;&n;at 0x000000e1 : */
l_int|0x9e0b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN DATA_OUT&n;&n;at 0x000000e3 : */
l_int|0x980b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP command_complete, WHEN STATUS&n;&n;at 0x000000e5 : */
l_int|0x830b0000
comma
l_int|0x0000060c
comma
multiline_comment|/*&n;    JUMP other_in, WHEN NOT DATA_IN&n;&n;at 0x000000e7 : */
l_int|0x81030000
comma
l_int|0x00000374
comma
multiline_comment|/*&n;    RETURN&n;&n;at 0x000000e9 : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;ENTRY other_transfer&n;other_transfer:&n;    INT int_err_unexpected_phase, WHEN CMD&n;&n;at 0x000000eb : */
l_int|0x9a0b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CALL msg_in, WHEN MSG_IN&n;&n;at 0x000000ed : */
l_int|0x8f0b0000
comma
l_int|0x00000404
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN MSG_OUT&n;&n;at 0x000000ef : */
l_int|0x9e0b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN DATA_OUT&n;&n;at 0x000000f1 : */
l_int|0x980b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN DATA_IN&n;&n;at 0x000000f3 : */
l_int|0x990b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP command_complete, WHEN STATUS&n;&n;at 0x000000f5 : */
l_int|0x830b0000
comma
l_int|0x0000060c
comma
multiline_comment|/*&n;    JUMP other_transfer&n;&n;at 0x000000f7 : */
l_int|0x80080000
comma
l_int|0x000003ac
comma
multiline_comment|/*&n;&n;;&n;; msg_in_restart&n;; msg_in&n;; munge_msg&n;;&n;; PURPOSE : process messages from a target.  msg_in is called when the &n;;&t;caller hasn&squot;t read the first byte of the message.  munge_message&n;;&t;is called when the caller has read the first byte of the message,&n;;&t;and left it in SFBR.  msg_in_restart is called when the caller &n;;&t;hasn&squot;t read the first byte of the message, and wishes RETURN&n;;&t;to transfer control back to the address of the conditional&n;;&t;CALL instruction rather than to the instruction after it.&n;;&n;;&t;Various int_* interrupts are generated when the host system&n;;&t;needs to intervene, as is the case with SDTR, WDTR, and&n;;&t;INITIATE RECOVERY messages.&n;;&n;;&t;When the host system handles one of these interrupts,&n;;&t;it can respond by reentering at reject_message, &n;;&t;which rejects the message and returns control to&n;;&t;the caller of msg_in or munge_msg, accept_message&n;;&t;which clears ACK and returns control, or reply_message&n;;&t;which sends the message pointed to by the DSA &n;;&t;msgout_other table indirect field.&n;;&n;;&t;DISCONNECT messages are handled by moving the command&n;;&t;to the reconnect_dsa_queue.&n;;&n;; INPUTS : DSA - SCSI COMMAND, SFBR - first byte of message (munge_msg&n;;&t;only)&n;;&n;; CALLS : NO.  The TEMP register isn&squot;t backed up to allow nested calls.&n;;&n;; MODIFIES : SCRATCH, DSA on DISCONNECT&n;;&n;; EXITS : On receipt of SAVE DATA POINTER, RESTORE POINTERS,&n;;&t;and normal return from message handlers running under&n;;&t;Linux, control is returned to the caller.  Receipt&n;;&t;of DISCONNECT messages pass control to dsa_schedule.&n;;&n;ENTRY msg_in_restart&n;msg_in_restart:&n;; XXX - hackish&n;;&n;; Since it&squot;s easier to debug changes to the statically &n;; compiled code, rather than the dynamically generated &n;; stuff, such as&n;;&n;; &t;MOVE x, y, WHEN data_phase&n;; &t;CALL other_z, WHEN NOT data_phase&n;; &t;MOVE x, y, WHEN data_phase&n;;&n;; I&squot;d like to have certain routines (notably the message handler)&n;; restart on the conditional call rather than the next instruction.&n;;&n;; So, subtract 8 from the return address&n;&n;    MOVE TEMP0 + 0xf8 TO TEMP0&n;&n;at 0x000000f9 : */
l_int|0x7e1cf800
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE TEMP1 + 0xff TO TEMP1 WITH CARRY&n;&n;at 0x000000fb : */
l_int|0x7f1dff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE TEMP2 + 0xff TO TEMP2 WITH CARRY&n;&n;at 0x000000fd : */
l_int|0x7f1eff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE TEMP3 + 0xff TO TEMP3 WITH CARRY&n;&n;at 0x000000ff : */
l_int|0x7f1fff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;ENTRY msg_in&n;msg_in:&n;    MOVE 1, msg_buf, WHEN MSG_IN&n;&n;at 0x00000101 : */
l_int|0x0f000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;munge_msg:&n;    JUMP munge_extended, IF 0x01&t;&t;; EXTENDED MESSAGE&n;&n;at 0x00000103 : */
l_int|0x800c0001
comma
l_int|0x00000524
comma
multiline_comment|/*&n;    JUMP munge_2, IF 0x20, AND MASK 0xdf&t;; two byte message&n;&n;at 0x00000105 : */
l_int|0x800cdf20
comma
l_int|0x0000044c
comma
multiline_comment|/*&n;;&n;; XXX - I&squot;ve seen a handful of broken SCSI devices which fail to issue&n;; &t;a SAVE POINTERS message before disconnecting in the middle of &n;; &t;a transfer, assuming that the DATA POINTER will be implicitly &n;; &t;restored.  &n;;&n;; Historically, I&squot;ve often done an implicit save when the DISCONNECT&n;; message is processed.  We may want to consider having the option of &n;; doing that here. &n;;&n;    JUMP munge_save_data_pointer, IF 0x02&t;; SAVE DATA POINTER&n;&n;at 0x00000107 : */
l_int|0x800c0002
comma
l_int|0x00000454
comma
multiline_comment|/*&n;    JUMP munge_restore_pointers, IF 0x03&t;; RESTORE POINTERS &n;&n;at 0x00000109 : */
l_int|0x800c0003
comma
l_int|0x000004b8
comma
multiline_comment|/*&n;    JUMP munge_disconnect, IF 0x04&t;&t;; DISCONNECT&n;&n;at 0x0000010b : */
l_int|0x800c0004
comma
l_int|0x0000051c
comma
multiline_comment|/*&n;    INT int_msg_1, IF 0x07&t;&t;&t;; MESSAGE REJECT&n;&n;at 0x0000010d : */
l_int|0x980c0007
comma
l_int|0x01020000
comma
multiline_comment|/*&n;    INT int_msg_1, IF 0x0f&t;&t;&t;; INITIATE RECOVERY&n;&n;at 0x0000010f : */
l_int|0x980c000f
comma
l_int|0x01020000
comma
multiline_comment|/*&n;&n;&n;&n;    JUMP reject_message&n;&n;at 0x00000111 : */
l_int|0x80080000
comma
l_int|0x000005b4
comma
multiline_comment|/*&n;&n;munge_2:&n;    JUMP reject_message&n;&n;at 0x00000113 : */
l_int|0x80080000
comma
l_int|0x000005b4
comma
multiline_comment|/*&n;;&n;; The SCSI standard allows targets to recover from transient &n;; error conditions by backing up the data pointer with a &n;; RESTORE POINTERS message.  &n;;&t;&n;; So, we must save and restore the _residual_ code as well as &n;; the current instruction pointer.  Because of this messiness,&n;; it is simpler to put dynamic code in the dsa for this and to&n;; just do a simple jump down there. &n;;&n;&n;munge_save_data_pointer:&n;    MOVE DSA0 + dsa_save_data_pointer TO SFBR&n;&n;at 0x00000115 : */
l_int|0x76100000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH0&n;&n;at 0x00000117 : */
l_int|0x6a340000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA1 + 0xff TO SFBR WITH CARRY&n;&n;at 0x00000119 : */
l_int|0x7711ff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH1&n;&n;at 0x0000011b : */
l_int|0x6a350000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA2 + 0xff TO SFBR WITH CARRY &n;&n;at 0x0000011d : */
l_int|0x7712ff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH2&n;&n;at 0x0000011f : */
l_int|0x6a360000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA3 + 0xff TO SFBR WITH CARRY&n;&n;at 0x00000121 : */
l_int|0x7713ff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH3&n;&n;at 0x00000123 : */
l_int|0x6a370000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;    MOVE dmode_ncr_to_memory TO DMODE&n;&n;at 0x00000125 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, addr_scratch, jump_dsa_save + 4&n;&n;at 0x00000127 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x000004b4
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x0000012a : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;jump_dsa_save:&n;    JUMP 0&n;&n;at 0x0000012c : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;munge_restore_pointers:&n;    MOVE DSA0 + dsa_restore_pointers TO SFBR&n;&n;at 0x0000012e : */
l_int|0x76100000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH0&n;&n;at 0x00000130 : */
l_int|0x6a340000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA1 + 0xff TO SFBR WITH CARRY&n;&n;at 0x00000132 : */
l_int|0x7711ff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH1&n;&n;at 0x00000134 : */
l_int|0x6a350000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA2 + 0xff TO SFBR WITH CARRY&n;&n;at 0x00000136 : */
l_int|0x7712ff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH2&n;&n;at 0x00000138 : */
l_int|0x6a360000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA3 + 0xff TO SFBR WITH CARRY&n;&n;at 0x0000013a : */
l_int|0x7713ff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH3&n;&n;at 0x0000013c : */
l_int|0x6a370000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;    MOVE dmode_ncr_to_memory TO DMODE&n;&n;at 0x0000013e : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, addr_scratch, jump_dsa_restore + 4&n;&n;at 0x00000140 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000518
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000143 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;jump_dsa_restore:&n;    JUMP 0&n;&n;at 0x00000145 : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;munge_disconnect:&n;&n;&n;&n;&n;&n;&n;&n;&n;&n; &n;&n;&n;&n;&n;&n;&n;    JUMP dsa_schedule&n;&n;at 0x00000147 : */
l_int|0x80080000
comma
l_int|0x00000168
comma
multiline_comment|/*&n;&n;&n;&n;&n;&n;munge_extended:&n;    CLEAR ACK&n;&n;at 0x00000149 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN NOT MSG_IN&n;&n;at 0x0000014b : */
l_int|0x9f030000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE 1, msg_buf + 1, WHEN MSG_IN&n;&n;at 0x0000014d : */
l_int|0x0f000001
comma
l_int|0x00000001
comma
multiline_comment|/*&n;    JUMP munge_extended_2, IF 0x02&n;&n;at 0x0000014f : */
l_int|0x800c0002
comma
l_int|0x00000554
comma
multiline_comment|/*&n;    JUMP munge_extended_3, IF 0x03 &n;&n;at 0x00000151 : */
l_int|0x800c0003
comma
l_int|0x00000584
comma
multiline_comment|/*&n;    JUMP reject_message&n;&n;at 0x00000153 : */
l_int|0x80080000
comma
l_int|0x000005b4
comma
multiline_comment|/*&n;&n;munge_extended_2:&n;    CLEAR ACK&n;&n;at 0x00000155 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE 1, msg_buf + 2, WHEN MSG_IN&n;&n;at 0x00000157 : */
l_int|0x0f000001
comma
l_int|0x00000002
comma
multiline_comment|/*&n;    JUMP reject_message, IF NOT 0x02&t;; Must be WDTR&n;&n;at 0x00000159 : */
l_int|0x80040002
comma
l_int|0x000005b4
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x0000015b : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE 1, msg_buf + 3, WHEN MSG_IN&n;&n;at 0x0000015d : */
l_int|0x0f000001
comma
l_int|0x00000003
comma
multiline_comment|/*&n;    INT int_msg_wdtr&n;&n;at 0x0000015f : */
l_int|0x98080000
comma
l_int|0x01000000
comma
multiline_comment|/*&n;&n;munge_extended_3:&n;    CLEAR ACK&n;&n;at 0x00000161 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE 1, msg_buf + 2, WHEN MSG_IN&n;&n;at 0x00000163 : */
l_int|0x0f000001
comma
l_int|0x00000002
comma
multiline_comment|/*&n;    JUMP reject_message, IF NOT 0x01&t;; Must be SDTR&n;&n;at 0x00000165 : */
l_int|0x80040001
comma
l_int|0x000005b4
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x00000167 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE 2, msg_buf + 3, WHEN MSG_IN&n;&n;at 0x00000169 : */
l_int|0x0f000002
comma
l_int|0x00000003
comma
multiline_comment|/*&n;    INT int_msg_sdtr&n;&n;at 0x0000016b : */
l_int|0x98080000
comma
l_int|0x01010000
comma
multiline_comment|/*&n;&n;ENTRY reject_message&n;reject_message:&n;    SET ATN&n;&n;at 0x0000016d : */
l_int|0x58000008
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x0000016f : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE 1, NCR53c7xx_msg_reject, WHEN MSG_OUT&n;&n;at 0x00000171 : */
l_int|0x0e000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    RETURN&n;&n;at 0x00000173 : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;ENTRY accept_message&n;accept_message:&n;    CLEAR ATN&n;&n;at 0x00000175 : */
l_int|0x60000008
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x00000177 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    RETURN&n;&n;at 0x00000179 : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;ENTRY respond_message&n;respond_message:&n;    SET ATN&n;&n;at 0x0000017b : */
l_int|0x58000008
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x0000017d : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE FROM dsa_msgout_other, WHEN MSG_OUT&n;&n;at 0x0000017f : */
l_int|0x1e000000
comma
l_int|0x00000068
comma
multiline_comment|/*&n;    RETURN&n;&n;at 0x00000181 : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;;&n;; command_complete&n;;&n;; PURPOSE : handle command termination when STATUS IN is detected by reading&n;;&t;a status byte followed by a command termination message. &n;;&n;;&t;Normal termination results in an INTFLY instruction, and &n;;&t;the host system can pick out which command terminated by &n;;&t;examining the MESSAGE and STATUS buffers of all currently &n;;&t;executing commands;&n;;&n;;&t;Abnormal (CHECK_CONDITION) termination results in an&n;;&t;int_err_check_condition interrupt so that a REQUEST SENSE&n;;&t;command can be issued out-of-order so that no other command&n;;&t;clears the contingent allegiance condition.&n;;&t;&n;;&n;; INPUTS : DSA - command&t;&n;;&n;; CALLS : OK&n;;&n;; EXITS : On successful termination, control is passed to schedule.&n;;&t;On abnormal termination, the user will usually modify the &n;;&t;DSA fields and corresponding buffers and return control&n;;&t;to select.&n;;&n;&n;ENTRY command_complete&n;command_complete:&n;    MOVE FROM dsa_status, WHEN STATUS&n;&n;at 0x00000183 : */
l_int|0x1b000000
comma
l_int|0x00000060
comma
multiline_comment|/*&n;&n;    MOVE SFBR TO SCRATCH0&t;&t;; Save status&n;&n;at 0x00000185 : */
l_int|0x6a340000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;ENTRY command_complete_msgin&n;command_complete_msgin:&n;    MOVE FROM dsa_msgin, WHEN MSG_IN&n;&n;at 0x00000187 : */
l_int|0x1f000000
comma
l_int|0x00000058
comma
multiline_comment|/*&n;; Indicate that we should be expecting a disconnect&n;    MOVE SCNTL2 &amp; 0x7f TO SCNTL2&n;&n;at 0x00000189 : */
l_int|0x7c027f00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x0000018b : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;    WAIT DISCONNECT&n;&n;at 0x0000018d : */
l_int|0x48000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;;&n;; The SCSI specification states that when a UNIT ATTENTION condition&n;; is pending, as indicated by a CHECK CONDITION status message,&n;; the target shall revert to asynchronous transfers.  Since&n;; synchronous transfers parameters are maintained on a per INITIATOR/TARGET &n;; basis, and returning control to our scheduler could work on a command&n;; running on another lun on that target using the old parameters, we must&n;; interrupt the host processor to get them changed, or change them ourselves.&n;;&n;; Once SCSI-II tagged queueing is implemented, things will be even more&n;; hairy, since contingent allegiance conditions exist on a per-target/lun&n;; basis, and issuing a new command with a different tag would clear it.&n;; In these cases, we must interrupt the host processor to get a request &n;; added to the HEAD of the queue with the request sense command, or we&n;; must automatically issue the request sense command.&n;&n;&n;&n;&n;&n;    INTFLY&n;&n;at 0x0000018f : */
l_int|0x98180000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;&n;&n;&n;    JUMP schedule&n;&n;at 0x00000191 : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;command_failed:&n;    INT int_err_check_condition&n;&n;at 0x00000193 : */
l_int|0x98080000
comma
l_int|0x00030000
comma
multiline_comment|/*&n;&n;&n;&n;&n;;&n;; wait_reselect&n;;&n;; PURPOSE : This is essentially the idle routine, where control lands&n;;&t;when there are no new processes to schedule.  wait_reselect&n;;&t;waits for reselection, selection, and new commands.&n;;&n;;&t;When a successful reselection occurs, with the aid &n;;&t;of fixed up code in each DSA, wait_reselect walks the &n;;&t;reconnect_dsa_queue, asking each dsa if the target ID&n;;&t;and LUN match its.&n;;&n;;&t;If a match is found, a call is made back to reselected_ok,&n;;&t;which through the miracles of self modifying code, extracts&n;;&t;the found DSA from the reconnect_dsa_queue and then &n;;&t;returns control to the DSAs thread of execution.&n;;&n;; INPUTS : NONE&n;;&n;; CALLS : OK&n;;&n;; MODIFIES : DSA,&n;;&n;; EXITS : On successful reselection, control is returned to the &n;;&t;DSA which called reselected_ok.  If the WAIT RESELECT&n;;&t;was interrupted by a new commands arrival signaled by &n;;&t;SIG_P, control is passed to schedule.  If the NCR is &n;;&t;selected, the host system is interrupted with an &n;;&t;int_err_selected which is usually responded to by&n;;&t;setting DSP to the target_abort address.&n;&n;ENTRY wait_reselect&n;wait_reselect:&n;&n;&n;&n;&n;&n;&n;    WAIT RESELECT wait_reselect_failed&n;&n;at 0x00000195 : */
l_int|0x50000000
comma
l_int|0x0000076c
comma
multiline_comment|/*&n;&n;reselected:&n;&n;&n;&n;    CLEAR TARGET&n;&n;at 0x00000197 : */
l_int|0x60000200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000199 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    ; Read all data needed to reestablish the nexus - &n;    MOVE 1, reselected_identify, WHEN MSG_IN&n;&n;at 0x0000019b : */
l_int|0x0f000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    ; We used to CLEAR ACK here.&n;&n;&n;&n;&n;&n;    ; Point DSA at the current head of the disconnected queue.&n;    MOVE dmode_memory_to_ncr  TO DMODE&n;&n;at 0x0000019d : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, reconnect_dsa_head, addr_scratch&n;&n;at 0x0000019f : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x000001a2 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CALL scratch_to_dsa&n;&n;at 0x000001a4 : */
l_int|0x88080000
comma
l_int|0x00000980
comma
multiline_comment|/*&n;&n;    ; Fix the update-next pointer so that the reconnect_dsa_head&n;    ; pointer is the one that will be updated if this DSA is a hit &n;    ; and we remove it from the queue.&n;&n;    MOVE MEMORY 4, addr_reconnect_dsa_head, reselected_ok + 8&n;&n;at 0x000001a6 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000758
comma
multiline_comment|/*&n;&n;ENTRY reselected_check_next&n;reselected_check_next:&n;&n;&n;&n;    ; Check for a NULL pointer.&n;    MOVE DSA0 TO SFBR&n;&n;at 0x000001a9 : */
l_int|0x72100000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP reselected_not_end, IF NOT 0&n;&n;at 0x000001ab : */
l_int|0x80040000
comma
l_int|0x000006ec
comma
multiline_comment|/*&n;    MOVE DSA1 TO SFBR&n;&n;at 0x000001ad : */
l_int|0x72110000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP reselected_not_end, IF NOT 0&n;&n;at 0x000001af : */
l_int|0x80040000
comma
l_int|0x000006ec
comma
multiline_comment|/*&n;    MOVE DSA2 TO SFBR&n;&n;at 0x000001b1 : */
l_int|0x72120000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP reselected_not_end, IF NOT 0&n;&n;at 0x000001b3 : */
l_int|0x80040000
comma
l_int|0x000006ec
comma
multiline_comment|/*&n;    MOVE DSA3 TO SFBR&n;&n;at 0x000001b5 : */
l_int|0x72130000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP reselected_not_end, IF NOT 0&n;&n;at 0x000001b7 : */
l_int|0x80040000
comma
l_int|0x000006ec
comma
multiline_comment|/*&n;    INT int_err_unexpected_reselect&n;&n;at 0x000001b9 : */
l_int|0x98080000
comma
l_int|0x00020000
comma
multiline_comment|/*&n;&n;reselected_not_end:&n;    ;&n;    ; XXX the ALU is only eight bits wide, and the assembler&n;    ; wont do the dirt work for us.  As long as dsa_check_reselect&n;    ; is negative, we need to sign extend with 1 bits to the full&n;    ; 32 bit width of the address.&n;    ;&n;    ; A potential work around would be to have a known alignment &n;    ; of the DSA structure such that the base address plus &n;    ; dsa_check_reselect doesn&squot;t require carrying from bytes &n;    ; higher than the LSB.&n;    ;&n;&n;    MOVE DSA0 TO SFBR&n;&n;at 0x000001bb : */
l_int|0x72100000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR + dsa_check_reselect TO SCRATCH0&n;&n;at 0x000001bd : */
l_int|0x6e340000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA1 TO SFBR&n;&n;at 0x000001bf : */
l_int|0x72110000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR + 0xff TO SCRATCH1 WITH CARRY&n;&n;at 0x000001c1 : */
l_int|0x6f35ff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA2 TO SFBR&n;&n;at 0x000001c3 : */
l_int|0x72120000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR + 0xff TO SCRATCH2 WITH CARRY&n;&n;at 0x000001c5 : */
l_int|0x6f36ff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA3 TO SFBR&n;&n;at 0x000001c7 : */
l_int|0x72130000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR + 0xff TO SCRATCH3 WITH CARRY&n;&n;at 0x000001c9 : */
l_int|0x6f37ff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;    MOVE dmode_ncr_to_memory TO DMODE&n;&n;at 0x000001cb : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, addr_scratch, reselected_check + 4&n;&n;at 0x000001cd : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x0000074c
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x000001d0 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;reselected_check:&n;    JUMP 0&n;&n;at 0x000001d2 : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;;&n;;&n;ENTRY reselected_ok&n;reselected_ok:&n;    MOVE MEMORY 4, 0, 0&t;&t;&t;&t;; Patched : first word&n;&n;at 0x000001d4 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;; &t;is address of &n;&t;&t;&t;&t;&t;&t;;       successful dsa_next&n;&t;&t;&t;&t;&t;&t;; Second word is last &n;&t;&t;&t;&t;&t;&t;;&t;unsuccessful dsa_next,&n;&t;&t;&t;&t;&t;&t;;&t;starting with &n;&t;&t;&t;&t;&t;&t;;       dsa_reconnect_head&n;    ; We used to CLEAR ACK here.&n;&n;&n;&n;&n;&n;&n;    RETURN&t;&t;&t;&t;&t;; Return control to where&n;&n;at 0x000001d7 : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;&n;&n;selected:&n;    INT int_err_selected;&n;&n;at 0x000001d9 : */
l_int|0x98080000
comma
l_int|0x00010000
comma
multiline_comment|/*&n;&n;;&n;; A select or reselect failure can be caused by one of two conditions : &n;; 1.  SIG_P was set.  This will be the case if the user has written&n;;&t;a new value to a previously NULL head of the issue queue.&n;;&n;; 2.  The NCR53c810 was selected or reselected by another device.&n;;&n;; 3.  The bus was already busy since we were selected or reselected&n;;&t;before starting the command.&n;&n;wait_reselect_failed:&n;&n;&n;&n;; Check selected bit.  &n;    MOVE SIST0 &amp; 0x20 TO SFBR&n;&n;at 0x000001db : */
l_int|0x74422000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP selected, IF 0x20&n;&n;at 0x000001dd : */
l_int|0x800c0020
comma
l_int|0x00000764
comma
multiline_comment|/*&n;; Reading CTEST2 clears the SIG_P bit in the ISTAT register.&n;    MOVE CTEST2 &amp; 0x40 TO SFBR&t;&n;&n;at 0x000001df : */
l_int|0x741a4000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP schedule, IF 0x40&n;&n;at 0x000001e1 : */
l_int|0x800c0040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;; Check connected bit.  &n;; FIXME: this needs to change if we support target mode&n;    MOVE ISTAT &amp; 0x08 TO SFBR&n;&n;at 0x000001e3 : */
l_int|0x74140800
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP reselected, IF 0x08&n;&n;at 0x000001e5 : */
l_int|0x800c0008
comma
l_int|0x0000065c
comma
multiline_comment|/*&n;; FIXME : Something bogus happened, and we shouldn&squot;t fail silently.&n;&n;&n;&n;    INT int_debug_panic&n;&n;at 0x000001e7 : */
l_int|0x98080000
comma
l_int|0x030b0000
comma
multiline_comment|/*&n;&n;&n;&n;select_failed:&n;&n;&n;&n;; Otherwise, mask the selected and reselected bits off SIST0&n;    MOVE SIST0 &amp; 0x30 TO SFBR&n;&n;at 0x000001e9 : */
l_int|0x74423000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP selected, IF 0x20&n;&n;at 0x000001eb : */
l_int|0x800c0020
comma
l_int|0x00000764
comma
multiline_comment|/*&n;    JUMP reselected, IF 0x10 &n;&n;at 0x000001ed : */
l_int|0x800c0010
comma
l_int|0x0000065c
comma
multiline_comment|/*&n;; If SIGP is set, the user just gave us another command, and&n;; we should restart or return to the scheduler.&n;; Reading CTEST2 clears the SIG_P bit in the ISTAT register.&n;    MOVE CTEST2 &amp; 0x40 TO SFBR&t;&n;&n;at 0x000001ef : */
l_int|0x741a4000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP select, IF 0x40&n;&n;at 0x000001f1 : */
l_int|0x800c0040
comma
l_int|0x000001fc
comma
multiline_comment|/*&n;; Check connected bit.  &n;; FIXME: this needs to change if we support target mode&n;; FIXME: is this really necessary? &n;    MOVE ISTAT &amp; 0x08 TO SFBR&n;&n;at 0x000001f3 : */
l_int|0x74140800
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP reselected, IF 0x08&n;&n;at 0x000001f5 : */
l_int|0x800c0008
comma
l_int|0x0000065c
comma
multiline_comment|/*&n;; FIXME : Something bogus happened, and we shouldn&squot;t fail silently.&n;&n;&n;&n;    INT int_debug_panic&n;&n;at 0x000001f7 : */
l_int|0x98080000
comma
l_int|0x030b0000
comma
multiline_comment|/*&n;&n;&n;;&n;; test_1&n;; test_2&n;;&n;; PURPOSE : run some verification tests on the NCR.  test_1&n;;&t;copies test_src to test_dest and interrupts the host&n;;&t;processor, testing for cache coherency and interrupt&n;; &t;problems in the processes.&n;;&n;;&t;test_2 runs a command with offsets relative to the &n;;&t;DSA on entry, and is useful for miscellaneous experimentation.&n;;&n;&n;; Verify that interrupts are working correctly and that we don&squot;t &n;; have a cache invalidation problem.&n;&n;ABSOLUTE test_src = 0, test_dest = 0&n;ENTRY test_1&n;test_1:&n;    MOVE MEMORY 4, test_src, test_dest&n;&n;at 0x000001f9 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    INT int_test_1&n;&n;at 0x000001fc : */
l_int|0x98080000
comma
l_int|0x04000000
comma
multiline_comment|/*&n;&n;;&n;; Run arbitrary commands, with test code establishing a DSA&n;;&n; &n;ENTRY test_2&n;test_2:&n;    CLEAR TARGET&n;&n;at 0x000001fe : */
l_int|0x60000200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    SELECT ATN FROM 0, test_2_fail&n;&n;at 0x00000200 : */
l_int|0x43000000
comma
l_int|0x00000850
comma
multiline_comment|/*&n;    JUMP test_2_msgout, WHEN MSG_OUT&n;&n;at 0x00000202 : */
l_int|0x860b0000
comma
l_int|0x00000810
comma
multiline_comment|/*&n;ENTRY test_2_msgout&n;test_2_msgout:&n;    MOVE FROM 8, WHEN MSG_OUT&n;&n;at 0x00000204 : */
l_int|0x1e000000
comma
l_int|0x00000008
comma
multiline_comment|/*&n;    MOVE FROM 16, WHEN CMD &n;&n;at 0x00000206 : */
l_int|0x1a000000
comma
l_int|0x00000010
comma
multiline_comment|/*&n;    MOVE FROM 24, WHEN DATA_IN&n;&n;at 0x00000208 : */
l_int|0x19000000
comma
l_int|0x00000018
comma
multiline_comment|/*&n;    MOVE FROM 32, WHEN STATUS&n;&n;at 0x0000020a : */
l_int|0x1b000000
comma
l_int|0x00000020
comma
multiline_comment|/*&n;    MOVE FROM 40, WHEN MSG_IN&n;&n;at 0x0000020c : */
l_int|0x1f000000
comma
l_int|0x00000028
comma
multiline_comment|/*&n;    MOVE SCNTL2 &amp; 0x7f TO SCNTL2&n;&n;at 0x0000020e : */
l_int|0x7c027f00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x00000210 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    WAIT DISCONNECT&n;&n;at 0x00000212 : */
l_int|0x48000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;test_2_fail:&n;    INT int_test_2&n;&n;at 0x00000214 : */
l_int|0x98080000
comma
l_int|0x04010000
comma
multiline_comment|/*&n;&n;ENTRY debug_break&n;debug_break:&n;    INT int_debug_break&n;&n;at 0x00000216 : */
l_int|0x98080000
comma
l_int|0x03000000
comma
multiline_comment|/*&n;&n;;&n;; initiator_abort&n;; target_abort&n;;&n;; PURPOSE : Abort the currently established nexus from with initiator&n;;&t;or target mode.&n;;&n;;  &n;&n;ENTRY target_abort&n;target_abort:&n;    SET TARGET&n;&n;at 0x00000218 : */
l_int|0x58000200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    DISCONNECT&n;&n;at 0x0000021a : */
l_int|0x48000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CLEAR TARGET&n;&n;at 0x0000021c : */
l_int|0x60000200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP schedule&n;&n;at 0x0000021e : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    &n;ENTRY initiator_abort&n;initiator_abort:&n;    SET ATN&n;&n;at 0x00000220 : */
l_int|0x58000008
comma
l_int|0x00000000
comma
multiline_comment|/*&n;;&n;; The SCSI-I specification says that targets may go into MSG out at &n;; their leisure upon receipt of the ATN single.  On all versions of the &n;; specification, we can&squot;t change phases until REQ transitions true-&gt;false, &n;; so we need to sink/source one byte of data to allow the transition.&n;;&n;; For the sake of safety, we&squot;ll only source one byte of data in all &n;; cases, but to accommodate the SCSI-I dain bramage, we&squot;ll sink an  &n;; arbitrary number of bytes.&n;    JUMP spew_cmd, WHEN CMD&n;&n;at 0x00000222 : */
l_int|0x820b0000
comma
l_int|0x000008b8
comma
multiline_comment|/*&n;    JUMP eat_msgin, WHEN MSG_IN&n;&n;at 0x00000224 : */
l_int|0x870b0000
comma
l_int|0x000008c8
comma
multiline_comment|/*&n;    JUMP eat_datain, WHEN DATA_IN&n;&n;at 0x00000226 : */
l_int|0x810b0000
comma
l_int|0x000008f8
comma
multiline_comment|/*&n;    JUMP eat_status, WHEN STATUS&n;&n;at 0x00000228 : */
l_int|0x830b0000
comma
l_int|0x000008e0
comma
multiline_comment|/*&n;    JUMP spew_dataout, WHEN DATA_OUT&n;&n;at 0x0000022a : */
l_int|0x800b0000
comma
l_int|0x00000910
comma
multiline_comment|/*&n;    JUMP sated&n;&n;at 0x0000022c : */
l_int|0x80080000
comma
l_int|0x00000918
comma
multiline_comment|/*&n;spew_cmd:&n;    MOVE 1, NCR53c7xx_zero, WHEN CMD&n;&n;at 0x0000022e : */
l_int|0x0a000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP sated&n;&n;at 0x00000230 : */
l_int|0x80080000
comma
l_int|0x00000918
comma
multiline_comment|/*&n;eat_msgin:&n;    MOVE 1, NCR53c7xx_sink, WHEN MSG_IN&n;&n;at 0x00000232 : */
l_int|0x0f000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP eat_msgin, WHEN MSG_IN&n;&n;at 0x00000234 : */
l_int|0x870b0000
comma
l_int|0x000008c8
comma
multiline_comment|/*&n;    JUMP sated&n;&n;at 0x00000236 : */
l_int|0x80080000
comma
l_int|0x00000918
comma
multiline_comment|/*&n;eat_status:&n;    MOVE 1, NCR53c7xx_sink, WHEN STATUS&n;&n;at 0x00000238 : */
l_int|0x0b000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP eat_status, WHEN STATUS&n;&n;at 0x0000023a : */
l_int|0x830b0000
comma
l_int|0x000008e0
comma
multiline_comment|/*&n;    JUMP sated&n;&n;at 0x0000023c : */
l_int|0x80080000
comma
l_int|0x00000918
comma
multiline_comment|/*&n;eat_datain:&n;    MOVE 1, NCR53c7xx_sink, WHEN DATA_IN&n;&n;at 0x0000023e : */
l_int|0x09000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP eat_datain, WHEN DATA_IN&n;&n;at 0x00000240 : */
l_int|0x810b0000
comma
l_int|0x000008f8
comma
multiline_comment|/*&n;    JUMP sated&n;&n;at 0x00000242 : */
l_int|0x80080000
comma
l_int|0x00000918
comma
multiline_comment|/*&n;spew_dataout:&n;    MOVE 1, NCR53c7xx_zero, WHEN DATA_OUT&n;&n;at 0x00000244 : */
l_int|0x08000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;sated:&n;    MOVE SCNTL2 &amp; 0x7f TO SCNTL2&n;&n;at 0x00000246 : */
l_int|0x7c027f00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE 1, NCR53c7xx_msg_abort, WHEN MSG_OUT&n;&n;at 0x00000248 : */
l_int|0x0e000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    WAIT DISCONNECT&n;&n;at 0x0000024a : */
l_int|0x48000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    INT int_norm_aborted&n;&n;at 0x0000024c : */
l_int|0x98080000
comma
l_int|0x02040000
comma
multiline_comment|/*&n;&n;;&n;; dsa_to_scratch&n;; scratch_to_dsa&n;;&n;; PURPOSE :&n;; &t;The NCR chips cannot do a move memory instruction with the DSA register &n;; &t;as the source or destination.  So, we provide a couple of subroutines&n;; &t;that let us switch between the DSA register and scratch register.&n;;&n;; &t;Memory moves to/from the DSPS  register also don&squot;t work, but we &n;; &t;don&squot;t use them.&n;;&n;;&n;&n; &n;dsa_to_scratch:&n;    MOVE DSA0 TO SFBR&n;&n;at 0x0000024e : */
l_int|0x72100000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH0&n;&n;at 0x00000250 : */
l_int|0x6a340000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA1 TO SFBR&n;&n;at 0x00000252 : */
l_int|0x72110000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH1&n;&n;at 0x00000254 : */
l_int|0x6a350000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA2 TO SFBR&n;&n;at 0x00000256 : */
l_int|0x72120000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH2&n;&n;at 0x00000258 : */
l_int|0x6a360000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA3 TO SFBR&n;&n;at 0x0000025a : */
l_int|0x72130000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH3&n;&n;at 0x0000025c : */
l_int|0x6a370000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    RETURN&n;&n;at 0x0000025e : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;scratch_to_dsa:&n;    MOVE SCRATCH0 TO SFBR&n;&n;at 0x00000260 : */
l_int|0x72340000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO DSA0&n;&n;at 0x00000262 : */
l_int|0x6a100000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH1 TO SFBR&n;&n;at 0x00000264 : */
l_int|0x72350000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO DSA1&n;&n;at 0x00000266 : */
l_int|0x6a110000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH2 TO SFBR&n;&n;at 0x00000268 : */
l_int|0x72360000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO DSA2&n;&n;at 0x0000026a : */
l_int|0x6a120000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH3 TO SFBR&n;&n;at 0x0000026c : */
l_int|0x72370000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO DSA3&n;&n;at 0x0000026e : */
l_int|0x6a130000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    RETURN&n;&n;at 0x00000270 : */
l_int|0x90080000
comma
l_int|0x00000000
comma
)brace
suffix:semicolon
DECL|macro|A_NCR53c7xx_msg_abort
mdefine_line|#define A_NCR53c7xx_msg_abort&t;0x00000000
r_static
id|u32
id|A_NCR53c7xx_msg_abort_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000249
comma
)brace
suffix:semicolon
DECL|macro|A_NCR53c7xx_msg_reject
mdefine_line|#define A_NCR53c7xx_msg_reject&t;0x00000000
r_static
id|u32
id|A_NCR53c7xx_msg_reject_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000172
comma
)brace
suffix:semicolon
DECL|macro|A_NCR53c7xx_sink
mdefine_line|#define A_NCR53c7xx_sink&t;0x00000000
r_static
id|u32
id|A_NCR53c7xx_sink_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000233
comma
l_int|0x00000239
comma
l_int|0x0000023f
comma
)brace
suffix:semicolon
DECL|macro|A_NCR53c7xx_zero
mdefine_line|#define A_NCR53c7xx_zero&t;0x00000000
r_static
id|u32
id|A_NCR53c7xx_zero_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000022f
comma
l_int|0x00000245
comma
)brace
suffix:semicolon
DECL|macro|A_NOP_insn
mdefine_line|#define A_NOP_insn&t;0x00000000
r_static
id|u32
id|A_NOP_insn_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000010
comma
)brace
suffix:semicolon
DECL|macro|A_addr_reconnect_dsa_head
mdefine_line|#define A_addr_reconnect_dsa_head&t;0x00000000
r_static
id|u32
id|A_addr_reconnect_dsa_head_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000001a7
comma
)brace
suffix:semicolon
DECL|macro|A_addr_scratch
mdefine_line|#define A_addr_scratch&t;0x00000000
r_static
id|u32
id|A_addr_scratch_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000004
comma
l_int|0x0000001b
comma
l_int|0x00000046
comma
l_int|0x00000067
comma
l_int|0x00000073
comma
l_int|0x000000b0
comma
l_int|0x000000c6
comma
l_int|0x00000128
comma
l_int|0x00000141
comma
l_int|0x000001a1
comma
l_int|0x000001ce
comma
)brace
suffix:semicolon
DECL|macro|A_addr_temp
mdefine_line|#define A_addr_temp&t;0x00000000
r_static
id|u32
id|A_addr_temp_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000025
comma
l_int|0x00000034
comma
)brace
suffix:semicolon
DECL|macro|A_dmode_memory_to_memory
mdefine_line|#define A_dmode_memory_to_memory&t;0x00000000
r_static
id|u32
id|A_dmode_memory_to_memory_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000005
comma
l_int|0x0000001c
comma
l_int|0x00000027
comma
l_int|0x00000035
comma
l_int|0x00000047
comma
l_int|0x00000069
comma
l_int|0x00000075
comma
l_int|0x000000b2
comma
l_int|0x000000c8
comma
l_int|0x0000012a
comma
l_int|0x00000143
comma
l_int|0x00000199
comma
l_int|0x000001a2
comma
l_int|0x000001d0
comma
)brace
suffix:semicolon
DECL|macro|A_dmode_memory_to_ncr
mdefine_line|#define A_dmode_memory_to_ncr&t;0x00000000
r_static
id|u32
id|A_dmode_memory_to_ncr_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000000
comma
l_int|0x00000017
comma
l_int|0x00000030
comma
l_int|0x00000042
comma
l_int|0x0000019d
comma
)brace
suffix:semicolon
DECL|macro|A_dmode_ncr_to_memory
mdefine_line|#define A_dmode_ncr_to_memory&t;0x00000000
r_static
id|u32
id|A_dmode_ncr_to_memory_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000022
comma
l_int|0x00000064
comma
l_int|0x00000070
comma
l_int|0x000000ad
comma
l_int|0x000000c3
comma
l_int|0x00000125
comma
l_int|0x0000013e
comma
l_int|0x000001cb
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_check_reselect
mdefine_line|#define A_dsa_check_reselect&t;0x00000000
r_static
id|u32
id|A_dsa_check_reselect_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000001bd
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_cmdout
mdefine_line|#define A_dsa_cmdout&t;0x00000048
r_static
id|u32
id|A_dsa_cmdout_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000094
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_cmnd
mdefine_line|#define A_dsa_cmnd&t;0x00000038
r_static
id|u32
id|A_dsa_cmnd_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_dsa_datain
mdefine_line|#define A_dsa_datain&t;0x00000054
r_static
id|u32
id|A_dsa_datain_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000000bb
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_dataout
mdefine_line|#define A_dsa_dataout&t;0x00000050
r_static
id|u32
id|A_dsa_dataout_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000000a5
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_end
mdefine_line|#define A_dsa_end&t;0x00000070
r_static
id|u32
id|A_dsa_end_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_dsa_fields_start
mdefine_line|#define A_dsa_fields_start&t;0x00000000
r_static
id|u32
id|A_dsa_fields_start_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_dsa_msgin
mdefine_line|#define A_dsa_msgin&t;0x00000058
r_static
id|u32
id|A_dsa_msgin_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000188
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_msgout
mdefine_line|#define A_dsa_msgout&t;0x00000040
r_static
id|u32
id|A_dsa_msgout_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000086
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_msgout_other
mdefine_line|#define A_dsa_msgout_other&t;0x00000068
r_static
id|u32
id|A_dsa_msgout_other_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000180
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_next
mdefine_line|#define A_dsa_next&t;0x00000030
r_static
id|u32
id|A_dsa_next_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000005c
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_restore_pointers
mdefine_line|#define A_dsa_restore_pointers&t;0x00000000
r_static
id|u32
id|A_dsa_restore_pointers_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000012e
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_save_data_pointer
mdefine_line|#define A_dsa_save_data_pointer&t;0x00000000
r_static
id|u32
id|A_dsa_save_data_pointer_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000115
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_select
mdefine_line|#define A_dsa_select&t;0x0000003c
r_static
id|u32
id|A_dsa_select_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000081
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_status
mdefine_line|#define A_dsa_status&t;0x00000060
r_static
id|u32
id|A_dsa_status_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000184
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_addr_array_value
mdefine_line|#define A_dsa_temp_addr_array_value&t;0x00000000
r_static
id|u32
id|A_dsa_temp_addr_array_value_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_addr_dsa_value
mdefine_line|#define A_dsa_temp_addr_dsa_value&t;0x00000000
r_static
id|u32
id|A_dsa_temp_addr_dsa_value_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000003
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_addr_new_value
mdefine_line|#define A_dsa_temp_addr_new_value&t;0x00000000
r_static
id|u32
id|A_dsa_temp_addr_new_value_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_addr_next
mdefine_line|#define A_dsa_temp_addr_next&t;0x00000000
r_static
id|u32
id|A_dsa_temp_addr_next_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000015
comma
l_int|0x0000004e
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_addr_residual
mdefine_line|#define A_dsa_temp_addr_residual&t;0x00000000
r_static
id|u32
id|A_dsa_temp_addr_residual_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000002a
comma
l_int|0x00000039
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_addr_saved_pointer
mdefine_line|#define A_dsa_temp_addr_saved_pointer&t;0x00000000
r_static
id|u32
id|A_dsa_temp_addr_saved_pointer_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000026
comma
l_int|0x00000033
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_addr_saved_residual
mdefine_line|#define A_dsa_temp_addr_saved_residual&t;0x00000000
r_static
id|u32
id|A_dsa_temp_addr_saved_residual_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000002b
comma
l_int|0x00000038
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_lun
mdefine_line|#define A_dsa_temp_lun&t;0x00000000
r_static
id|u32
id|A_dsa_temp_lun_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000004b
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_next
mdefine_line|#define A_dsa_temp_next&t;0x00000000
r_static
id|u32
id|A_dsa_temp_next_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000001a
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_sync
mdefine_line|#define A_dsa_temp_sync&t;0x00000000
r_static
id|u32
id|A_dsa_temp_sync_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000053
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_target
mdefine_line|#define A_dsa_temp_target&t;0x00000000
r_static
id|u32
id|A_dsa_temp_target_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000040
comma
)brace
suffix:semicolon
DECL|macro|A_int_debug_break
mdefine_line|#define A_int_debug_break&t;0x03000000
r_static
id|u32
id|A_int_debug_break_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000217
comma
)brace
suffix:semicolon
DECL|macro|A_int_debug_panic
mdefine_line|#define A_int_debug_panic&t;0x030b0000
r_static
id|u32
id|A_int_debug_panic_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000001e8
comma
l_int|0x000001f8
comma
)brace
suffix:semicolon
DECL|macro|A_int_err_check_condition
mdefine_line|#define A_int_err_check_condition&t;0x00030000
r_static
id|u32
id|A_int_err_check_condition_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000194
comma
)brace
suffix:semicolon
DECL|macro|A_int_err_no_phase
mdefine_line|#define A_int_err_no_phase&t;0x00040000
r_static
id|u32
id|A_int_err_no_phase_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_err_selected
mdefine_line|#define A_int_err_selected&t;0x00010000
r_static
id|u32
id|A_int_err_selected_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000001da
comma
)brace
suffix:semicolon
DECL|macro|A_int_err_unexpected_phase
mdefine_line|#define A_int_err_unexpected_phase&t;0x00000000
r_static
id|u32
id|A_int_err_unexpected_phase_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000008c
comma
l_int|0x00000092
comma
l_int|0x0000009a
comma
l_int|0x000000d0
comma
l_int|0x000000d4
comma
l_int|0x000000d6
comma
l_int|0x000000de
comma
l_int|0x000000e2
comma
l_int|0x000000e4
comma
l_int|0x000000ec
comma
l_int|0x000000f0
comma
l_int|0x000000f2
comma
l_int|0x000000f4
comma
l_int|0x0000014c
comma
)brace
suffix:semicolon
DECL|macro|A_int_err_unexpected_reselect
mdefine_line|#define A_int_err_unexpected_reselect&t;0x00020000
r_static
id|u32
id|A_int_err_unexpected_reselect_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000001ba
comma
)brace
suffix:semicolon
DECL|macro|A_int_msg_1
mdefine_line|#define A_int_msg_1&t;0x01020000
r_static
id|u32
id|A_int_msg_1_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000010e
comma
l_int|0x00000110
comma
)brace
suffix:semicolon
DECL|macro|A_int_msg_sdtr
mdefine_line|#define A_int_msg_sdtr&t;0x01010000
r_static
id|u32
id|A_int_msg_sdtr_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000016c
comma
)brace
suffix:semicolon
DECL|macro|A_int_msg_wdtr
mdefine_line|#define A_int_msg_wdtr&t;0x01000000
r_static
id|u32
id|A_int_msg_wdtr_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000160
comma
)brace
suffix:semicolon
DECL|macro|A_int_norm_aborted
mdefine_line|#define A_int_norm_aborted&t;0x02040000
r_static
id|u32
id|A_int_norm_aborted_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000024d
comma
)brace
suffix:semicolon
DECL|macro|A_int_norm_command_complete
mdefine_line|#define A_int_norm_command_complete&t;0x02020000
r_static
id|u32
id|A_int_norm_command_complete_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_norm_disconnected
mdefine_line|#define A_int_norm_disconnected&t;0x02030000
r_static
id|u32
id|A_int_norm_disconnected_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_norm_reselect_complete
mdefine_line|#define A_int_norm_reselect_complete&t;0x02010000
r_static
id|u32
id|A_int_norm_reselect_complete_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_norm_reset
mdefine_line|#define A_int_norm_reset&t;0x02050000
r_static
id|u32
id|A_int_norm_reset_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_norm_select_complete
mdefine_line|#define A_int_norm_select_complete&t;0x02000000
r_static
id|u32
id|A_int_norm_select_complete_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_test_1
mdefine_line|#define A_int_test_1&t;0x04000000
r_static
id|u32
id|A_int_test_1_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000001fd
comma
)brace
suffix:semicolon
DECL|macro|A_int_test_2
mdefine_line|#define A_int_test_2&t;0x04010000
r_static
id|u32
id|A_int_test_2_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000215
comma
)brace
suffix:semicolon
DECL|macro|A_int_test_3
mdefine_line|#define A_int_test_3&t;0x04020000
r_static
id|u32
id|A_int_test_3_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_msg_buf
mdefine_line|#define A_msg_buf&t;0x00000000
r_static
id|u32
id|A_msg_buf_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000102
comma
l_int|0x0000014e
comma
l_int|0x00000158
comma
l_int|0x0000015e
comma
l_int|0x00000164
comma
l_int|0x0000016a
comma
)brace
suffix:semicolon
DECL|macro|A_reconnect_dsa_head
mdefine_line|#define A_reconnect_dsa_head&t;0x00000000
r_static
id|u32
id|A_reconnect_dsa_head_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000006c
comma
l_int|0x00000074
comma
l_int|0x000001a0
comma
)brace
suffix:semicolon
DECL|macro|A_reselected_identify
mdefine_line|#define A_reselected_identify&t;0x00000000
r_static
id|u32
id|A_reselected_identify_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000045
comma
l_int|0x0000019c
comma
)brace
suffix:semicolon
DECL|macro|A_reselected_tag
mdefine_line|#define A_reselected_tag&t;0x00000000
r_static
id|u32
id|A_reselected_tag_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_schedule
mdefine_line|#define A_schedule&t;0x00000000
r_static
id|u32
id|A_schedule_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x0000007e
comma
l_int|0x00000192
comma
l_int|0x000001e2
comma
l_int|0x0000021f
comma
)brace
suffix:semicolon
DECL|macro|A_test_dest
mdefine_line|#define A_test_dest&t;0x00000000
r_static
id|u32
id|A_test_dest_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000001fb
comma
)brace
suffix:semicolon
DECL|macro|A_test_src
mdefine_line|#define A_test_src&t;0x00000000
r_static
id|u32
id|A_test_src_used
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x000001fa
comma
)brace
suffix:semicolon
DECL|macro|Ent_accept_message
mdefine_line|#define Ent_accept_message&t;0x000005d4
DECL|macro|Ent_cmdout_cmdout
mdefine_line|#define Ent_cmdout_cmdout&t;0x0000024c
DECL|macro|Ent_command_complete
mdefine_line|#define Ent_command_complete&t;0x0000060c
DECL|macro|Ent_command_complete_msgin
mdefine_line|#define Ent_command_complete_msgin&t;0x0000061c
DECL|macro|Ent_data_transfer
mdefine_line|#define Ent_data_transfer&t;0x00000254
DECL|macro|Ent_datain_to_jump
mdefine_line|#define Ent_datain_to_jump&t;0x00000328
DECL|macro|Ent_debug_break
mdefine_line|#define Ent_debug_break&t;0x00000858
DECL|macro|Ent_dsa_code_begin
mdefine_line|#define Ent_dsa_code_begin&t;0x00000000
DECL|macro|Ent_dsa_code_check_reselect
mdefine_line|#define Ent_dsa_code_check_reselect&t;0x000000f8
DECL|macro|Ent_dsa_code_fix_jump
mdefine_line|#define Ent_dsa_code_fix_jump&t;0x0000003c
DECL|macro|Ent_dsa_code_restore_pointers
mdefine_line|#define Ent_dsa_code_restore_pointers&t;0x000000c0
DECL|macro|Ent_dsa_code_save_data_pointer
mdefine_line|#define Ent_dsa_code_save_data_pointer&t;0x00000088
DECL|macro|Ent_dsa_code_template
mdefine_line|#define Ent_dsa_code_template&t;0x00000000
DECL|macro|Ent_dsa_code_template_end
mdefine_line|#define Ent_dsa_code_template_end&t;0x00000168
DECL|macro|Ent_dsa_schedule
mdefine_line|#define Ent_dsa_schedule&t;0x00000168
DECL|macro|Ent_dsa_zero
mdefine_line|#define Ent_dsa_zero&t;0x00000168
DECL|macro|Ent_end_data_transfer
mdefine_line|#define Ent_end_data_transfer&t;0x0000028c
DECL|macro|Ent_initiator_abort
mdefine_line|#define Ent_initiator_abort&t;0x00000880
DECL|macro|Ent_msg_in
mdefine_line|#define Ent_msg_in&t;0x00000404
DECL|macro|Ent_msg_in_restart
mdefine_line|#define Ent_msg_in_restart&t;0x000003e4
DECL|macro|Ent_other_in
mdefine_line|#define Ent_other_in&t;0x00000374
DECL|macro|Ent_other_out
mdefine_line|#define Ent_other_out&t;0x0000033c
DECL|macro|Ent_other_transfer
mdefine_line|#define Ent_other_transfer&t;0x000003ac
DECL|macro|Ent_reject_message
mdefine_line|#define Ent_reject_message&t;0x000005b4
DECL|macro|Ent_reselected_check_next
mdefine_line|#define Ent_reselected_check_next&t;0x000006a4
DECL|macro|Ent_reselected_ok
mdefine_line|#define Ent_reselected_ok&t;0x00000750
DECL|macro|Ent_respond_message
mdefine_line|#define Ent_respond_message&t;0x000005ec
DECL|macro|Ent_select
mdefine_line|#define Ent_select&t;0x000001fc
DECL|macro|Ent_select_msgout
mdefine_line|#define Ent_select_msgout&t;0x00000214
DECL|macro|Ent_target_abort
mdefine_line|#define Ent_target_abort&t;0x00000860
DECL|macro|Ent_test_1
mdefine_line|#define Ent_test_1&t;0x000007e4
DECL|macro|Ent_test_2
mdefine_line|#define Ent_test_2&t;0x000007f8
DECL|macro|Ent_test_2_msgout
mdefine_line|#define Ent_test_2_msgout&t;0x00000810
DECL|macro|Ent_wait_reselect
mdefine_line|#define Ent_wait_reselect&t;0x00000654
r_static
id|u32
id|LABELPATCHES
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
l_int|0x00000008
comma
l_int|0x0000000a
comma
l_int|0x00000013
comma
l_int|0x00000016
comma
l_int|0x0000001f
comma
l_int|0x00000021
comma
l_int|0x0000004f
comma
l_int|0x00000051
comma
l_int|0x0000005b
comma
l_int|0x00000068
comma
l_int|0x0000006f
comma
l_int|0x00000082
comma
l_int|0x00000084
comma
l_int|0x0000008a
comma
l_int|0x0000008e
comma
l_int|0x00000090
comma
l_int|0x00000096
comma
l_int|0x00000098
comma
l_int|0x0000009c
comma
l_int|0x0000009e
comma
l_int|0x000000a0
comma
l_int|0x000000a2
comma
l_int|0x000000a4
comma
l_int|0x000000b1
comma
l_int|0x000000b6
comma
l_int|0x000000ba
comma
l_int|0x000000c7
comma
l_int|0x000000cc
comma
l_int|0x000000d2
comma
l_int|0x000000d8
comma
l_int|0x000000da
comma
l_int|0x000000e0
comma
l_int|0x000000e6
comma
l_int|0x000000e8
comma
l_int|0x000000ee
comma
l_int|0x000000f6
comma
l_int|0x000000f8
comma
l_int|0x00000104
comma
l_int|0x00000106
comma
l_int|0x00000108
comma
l_int|0x0000010a
comma
l_int|0x0000010c
comma
l_int|0x00000112
comma
l_int|0x00000114
comma
l_int|0x00000129
comma
l_int|0x00000142
comma
l_int|0x00000148
comma
l_int|0x00000150
comma
l_int|0x00000152
comma
l_int|0x00000154
comma
l_int|0x0000015a
comma
l_int|0x00000166
comma
l_int|0x00000196
comma
l_int|0x000001a5
comma
l_int|0x000001a8
comma
l_int|0x000001ac
comma
l_int|0x000001b0
comma
l_int|0x000001b4
comma
l_int|0x000001b8
comma
l_int|0x000001cf
comma
l_int|0x000001de
comma
l_int|0x000001e6
comma
l_int|0x000001ec
comma
l_int|0x000001ee
comma
l_int|0x000001f2
comma
l_int|0x000001f6
comma
l_int|0x00000201
comma
l_int|0x00000203
comma
l_int|0x00000223
comma
l_int|0x00000225
comma
l_int|0x00000227
comma
l_int|0x00000229
comma
l_int|0x0000022b
comma
l_int|0x0000022d
comma
l_int|0x00000231
comma
l_int|0x00000235
comma
l_int|0x00000237
comma
l_int|0x0000023b
comma
l_int|0x0000023d
comma
l_int|0x00000241
comma
l_int|0x00000243
comma
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|offset
id|u32
id|offset
suffix:semicolon
DECL|member|address
r_void
op_star
id|address
suffix:semicolon
)brace
id|EXTERNAL_PATCHES
(braket
)braket
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(brace
)brace
suffix:semicolon
r_static
id|u32
id|INSTRUCTIONS
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
l_int|301
suffix:semicolon
r_static
id|u32
id|PATCHES
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
l_int|81
suffix:semicolon
r_static
id|u32
id|EXTERNAL_PATCHES_LEN
id|__attribute
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
l_int|0
suffix:semicolon
eof
