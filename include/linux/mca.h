multiline_comment|/*&n; * Header for Microchannel Architecture Bus&n; * Written by Martin Kolinek, February 1996&n; */
macro_line|#ifndef _LINUX_MCA_H
DECL|macro|_LINUX_MCA_H
mdefine_line|#define _LINUX_MCA_H
multiline_comment|/* The detection of MCA bus is done in the real mode (using BIOS).&n; * The information is exported to the protected code, where this&n; * variable is set to one in case MCA bus was detected.&n; */
macro_line|#ifndef MCA_bus__is_a_macro
r_extern
r_int
id|MCA_bus
suffix:semicolon
macro_line|#endif
multiline_comment|/* Maximal number of MCA slots - actually, some machines have less, but&n; * they all have sufficient number of POS registers to cover 8.&n; */
DECL|macro|MCA_MAX_SLOT_NR
mdefine_line|#define MCA_MAX_SLOT_NR  8
multiline_comment|/* MCA_NOTFOUND is an error condition.  The other two indicate&n; * motherboard POS registers contain the adapter.  They might be&n; * returned by the mca_find_adapter() function, and can be used as&n; * arguments to mca_read_stored_pos().  I&squot;m not going to allow direct&n; * access to the motherboard registers until we run across an adapter&n; * that requires it.  We don&squot;t know enough about them to know if it&squot;s&n; * safe.&n; *&n; * See Documentation/mca.txt or one of the existing drivers for&n; * more information.&n; */
DECL|macro|MCA_NOTFOUND
mdefine_line|#define MCA_NOTFOUND&t;(-1)
DECL|macro|MCA_INTEGSCSI
mdefine_line|#define MCA_INTEGSCSI&t;(MCA_MAX_SLOT_NR)
DECL|macro|MCA_INTEGVIDEO
mdefine_line|#define MCA_INTEGVIDEO&t;(MCA_MAX_SLOT_NR+1)
DECL|macro|MCA_MOTHERBOARD
mdefine_line|#define MCA_MOTHERBOARD (MCA_MAX_SLOT_NR+2)
multiline_comment|/* Max number of adapters, including both slots and various integrated&n; * things.&n; */
DECL|macro|MCA_NUMADAPTERS
mdefine_line|#define MCA_NUMADAPTERS (MCA_MAX_SLOT_NR+3)
multiline_comment|/* Returns the slot of the first enabled adapter matching id.  User can&n; * specify a starting slot beyond zero, to deal with detecting multiple&n; * devices.  Returns MCA_NOTFOUND if id not found.  Also checks the&n; * integrated adapters.&n; */
r_extern
r_int
id|mca_find_adapter
c_func
(paren
r_int
id|id
comma
r_int
id|start
)paren
suffix:semicolon
r_extern
r_int
id|mca_find_unused_adapter
c_func
(paren
r_int
id|id
comma
r_int
id|start
)paren
suffix:semicolon
multiline_comment|/* adapter state info - returns 0 if no */
r_extern
r_int
id|mca_isadapter
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|mca_isenabled
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|mca_is_adapter_used
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
r_extern
r_int
id|mca_mark_as_used
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
r_extern
r_void
id|mca_mark_as_unused
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
multiline_comment|/* gets a byte out of POS register (stored in memory) */
r_extern
r_int
r_char
id|mca_read_stored_pos
c_func
(paren
r_int
id|slot
comma
r_int
id|reg
)paren
suffix:semicolon
multiline_comment|/* This can be expanded later.  Right now, it gives us a way of&n; * getting meaningful information into the MCA_info structure,&n; * so we can have a more interesting /proc/mca.&n; */
r_extern
r_void
id|mca_set_adapter_name
c_func
(paren
r_int
id|slot
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_char
op_star
id|mca_get_adapter_name
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
multiline_comment|/* This sets up an information callback for /proc/mca/slot?.  The&n; * function is called with the buffer, slot, and device pointer (or&n; * some equally informative context information, or nothing, if you&n; * prefer), and is expected to put useful information into the&n; * buffer.  The adapter name, id, and POS registers get printed&n; * before this is called though, so don&squot;t do it again.&n; *&n; * This should be called with a NULL procfn when a module&n; * unregisters, thus preventing kernel crashes and other such&n; * nastiness.&n; */
DECL|typedef|MCA_ProcFn
r_typedef
r_int
(paren
op_star
id|MCA_ProcFn
)paren
(paren
r_char
op_star
id|buf
comma
r_int
id|slot
comma
r_void
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|mca_set_adapter_procfn
c_func
(paren
r_int
id|slot
comma
id|MCA_ProcFn
comma
r_void
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* These routines actually mess with the hardware POS registers.  They&n; * temporarily disable the device (and interrupts), so make sure you know&n; * what you&squot;re doing if you use them.  Furthermore, writing to a POS may&n; * result in two devices trying to share a resource, which in turn can&n; * result in multiple devices sharing memory spaces, IRQs, or even trashing&n; * hardware.  YOU HAVE BEEN WARNED.&n; *&n; * You can only access slots with this.  Motherboard registers are off&n; * limits.&n; */
multiline_comment|/* read a byte from the specified POS register. */
r_extern
r_int
r_char
id|mca_read_pos
c_func
(paren
r_int
id|slot
comma
r_int
id|reg
)paren
suffix:semicolon
multiline_comment|/* write a byte to the specified POS register. */
r_extern
r_void
id|mca_write_pos
c_func
(paren
r_int
id|slot
comma
r_int
id|reg
comma
r_int
r_char
id|byte
)paren
suffix:semicolon
multiline_comment|/* Should only be called by the NMI interrupt handler, this will do some&n; * fancy stuff to figure out what might have generated a NMI.&n; */
r_extern
r_void
id|mca_handle_nmi
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _LINUX_MCA_H */
eof
