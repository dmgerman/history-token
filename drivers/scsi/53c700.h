multiline_comment|/* -*- mode: c; c-basic-offset: 8 -*- */
multiline_comment|/* Driver for 53c700 and 53c700-66 chips from NCR and Symbios&n; *&n; * Copyright (C) 2001 by James.Bottomley@HansenPartnership.com&n; */
macro_line|#ifndef _53C700_H
DECL|macro|_53C700_H
mdefine_line|#define _53C700_H
multiline_comment|/* Turn on for general debugging---too verbose for normal use */
DECL|macro|NCR_700_DEBUG
macro_line|#undef NCR_700_DEBUG
multiline_comment|/* Debug the tag queues, checking hash queue allocation and deallocation&n; * and search for duplicate tags */
DECL|macro|NCR_700_TAG_DEBUG
macro_line|#undef NCR_700_TAG_DEBUG
macro_line|#ifdef NCR_700_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG(x)&t;printk x
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(x)
macro_line|#endif
multiline_comment|/* The number of available command slots */
DECL|macro|NCR_700_COMMAND_SLOTS_PER_HOST
mdefine_line|#define NCR_700_COMMAND_SLOTS_PER_HOST&t;64
multiline_comment|/* The maximum number of Scatter Gathers we allow */
DECL|macro|NCR_700_SG_SEGMENTS
mdefine_line|#define NCR_700_SG_SEGMENTS&t;&t;32
multiline_comment|/* The maximum number of luns (make this of the form 2^n) */
DECL|macro|NCR_700_MAX_LUNS
mdefine_line|#define NCR_700_MAX_LUNS&t;&t;32
DECL|macro|NCR_700_LUN_MASK
mdefine_line|#define NCR_700_LUN_MASK&t;&t;(NCR_700_MAX_LUNS - 1)
multiline_comment|/* Alter this with care: too many tags won&squot;t give the elevator a chance to&n; * work; too few will cause the device to operate less efficiently */
DECL|macro|NCR_700_MAX_TAGS
mdefine_line|#define NCR_700_MAX_TAGS&t;&t;16
multiline_comment|/* magic byte identifying an internally generated REQUEST_SENSE command */
DECL|macro|NCR_700_INTERNAL_SENSE_MAGIC
mdefine_line|#define NCR_700_INTERNAL_SENSE_MAGIC&t;0x42
multiline_comment|/* WARNING: Leave this in for now: the dependency preprocessor doesn&squot;t&n; * pick up file specific flags, so must define here if they are not&n; * set */
macro_line|#if !defined(CONFIG_53C700_IO_MAPPED) &amp;&amp; !defined(CONFIG_53C700_MEM_MAPPED)
macro_line|#error &quot;Config.in must define either CONFIG_53C700_IO_MAPPED or CONFIG_53C700_MEM_MAPPED to use this scsi core.&quot;
macro_line|#endif
multiline_comment|/* macros for consistent memory allocation */
macro_line|#ifdef CONFIG_53C700_USE_CONSISTENT
DECL|macro|NCR_700_dma_cache_wback
mdefine_line|#define NCR_700_dma_cache_wback(mem, size) &bslash;&n;&t;if(!hostdata-&gt;consistent) &bslash;&n;&t;&t;dma_cache_wback(mem, size)
DECL|macro|NCR_700_dma_cache_inv
mdefine_line|#define NCR_700_dma_cache_inv(mem, size) &bslash;&n;&t;if(!hostdata-&gt;consistent) &bslash;&n;&t;&t;dma_cache_inv(mem, size)
DECL|macro|NCR_700_dma_cache_wback_inv
mdefine_line|#define NCR_700_dma_cache_wback_inv(mem, size) &bslash;&n;&t;if(!hostdata-&gt;consistent) &bslash;&n;&t;&t;dma_cache_wback_inv(mem, size)
macro_line|#else
DECL|macro|NCR_700_dma_cache_wback
mdefine_line|#define NCR_700_dma_cache_wback(mem, size) dma_cache_wback(mem,size)
DECL|macro|NCR_700_dma_cache_inv
mdefine_line|#define NCR_700_dma_cache_inv(mem, size) dma_cache_inv(mem,size)
DECL|macro|NCR_700_dma_cache_wback_inv
mdefine_line|#define NCR_700_dma_cache_wback_inv(mem, size) dma_cache_wback_inv(mem,size)
macro_line|#endif
r_struct
id|NCR_700_Host_Parameters
suffix:semicolon
multiline_comment|/* These are the externally used routines */
r_struct
id|Scsi_Host
op_star
id|NCR_700_detect
c_func
(paren
id|Scsi_Host_Template
op_star
comma
r_struct
id|NCR_700_Host_Parameters
op_star
)paren
suffix:semicolon
r_int
id|NCR_700_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
r_void
id|NCR_700_intr
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|enum|NCR_700_Host_State
r_enum
id|NCR_700_Host_State
(brace
DECL|enumerator|NCR_700_HOST_BUSY
id|NCR_700_HOST_BUSY
comma
DECL|enumerator|NCR_700_HOST_FREE
id|NCR_700_HOST_FREE
comma
)brace
suffix:semicolon
DECL|struct|NCR_700_SG_List
r_struct
id|NCR_700_SG_List
(brace
multiline_comment|/* The following is a script fragment to move the buffer onto the&n;&t; * bus and then link the next fragment or return */
DECL|macro|SCRIPT_MOVE_DATA_IN
mdefine_line|#define&t;SCRIPT_MOVE_DATA_IN&t;&t;0x09000000
DECL|macro|SCRIPT_MOVE_DATA_OUT
mdefine_line|#define&t;SCRIPT_MOVE_DATA_OUT&t;&t;0x08000000
DECL|member|ins
id|__u32
id|ins
suffix:semicolon
DECL|member|pAddr
id|__u32
id|pAddr
suffix:semicolon
DECL|macro|SCRIPT_NOP
mdefine_line|#define&t;SCRIPT_NOP&t;&t;&t;0x80000000
DECL|macro|SCRIPT_RETURN
mdefine_line|#define&t;SCRIPT_RETURN&t;&t;&t;0x90080000
)brace
suffix:semicolon
multiline_comment|/* We use device-&gt;hostdata to store negotiated parameters.  This is&n; * supposed to be a pointer to a device private area, but we cannot&n; * really use it as such since it will never be freed, so just use the&n; * 32 bits to cram the information.  The SYNC negotiation sequence looks&n; * like:&n; * &n; * If DEV_NEGOTIATED_SYNC not set, tack and SDTR message on to the&n; * initial identify for the device and set DEV_BEGIN_SYNC_NEGOTATION&n; * If we get an SDTR reply, work out the SXFER parameters, squirrel&n; * them away here, clear DEV_BEGIN_SYNC_NEGOTIATION and set&n; * DEV_NEGOTIATED_SYNC.  If we get a REJECT msg, squirrel&n; *&n; *&n; * 0:7&t;SXFER_REG negotiated value for this device&n; * 8:15 Current queue depth&n; * 16&t;negotiated SYNC flag&n; * 17 begin SYNC negotiation flag &n; * 18 device supports tag queueing */
DECL|macro|NCR_700_DEV_NEGOTIATED_SYNC
mdefine_line|#define NCR_700_DEV_NEGOTIATED_SYNC&t;(1&lt;&lt;16)
DECL|macro|NCR_700_DEV_BEGIN_SYNC_NEGOTIATION
mdefine_line|#define NCR_700_DEV_BEGIN_SYNC_NEGOTIATION&t;(1&lt;&lt;17)
DECL|macro|NCR_700_DEV_BEGIN_TAG_QUEUEING
mdefine_line|#define NCR_700_DEV_BEGIN_TAG_QUEUEING&t;(1&lt;&lt;18)
DECL|macro|NCR_700_DEV_TAG_STARVATION_WARNED
mdefine_line|#define NCR_700_DEV_TAG_STARVATION_WARNED (1&lt;&lt;19)
r_static
r_inline
r_void
DECL|function|NCR_700_set_SXFER
id|NCR_700_set_SXFER
c_func
(paren
id|Scsi_Device
op_star
id|SDp
comma
id|__u8
id|sxfer
)paren
(brace
(paren
(paren
r_int
r_int
)paren
id|SDp-&gt;hostdata
)paren
op_and_assign
l_int|0xffffff00
suffix:semicolon
(paren
(paren
r_int
r_int
)paren
id|SDp-&gt;hostdata
)paren
op_or_assign
id|sxfer
op_amp
l_int|0xff
suffix:semicolon
)brace
DECL|function|NCR_700_get_SXFER
r_static
r_inline
id|__u8
id|NCR_700_get_SXFER
c_func
(paren
id|Scsi_Device
op_star
id|SDp
)paren
(brace
r_return
(paren
(paren
(paren
r_int
r_int
)paren
id|SDp-&gt;hostdata
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|NCR_700_set_depth
id|NCR_700_set_depth
c_func
(paren
id|Scsi_Device
op_star
id|SDp
comma
id|__u8
id|depth
)paren
(brace
(paren
(paren
r_int
r_int
)paren
id|SDp-&gt;hostdata
)paren
op_and_assign
l_int|0xffff00ff
suffix:semicolon
(paren
(paren
r_int
r_int
)paren
id|SDp-&gt;hostdata
)paren
op_or_assign
(paren
l_int|0xff00
op_amp
(paren
id|depth
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u8
DECL|function|NCR_700_get_depth
id|NCR_700_get_depth
c_func
(paren
id|Scsi_Device
op_star
id|SDp
)paren
(brace
r_return
(paren
(paren
(paren
(paren
r_int
r_int
)paren
id|SDp-&gt;hostdata
)paren
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|NCR_700_is_flag_set
id|NCR_700_is_flag_set
c_func
(paren
id|Scsi_Device
op_star
id|SDp
comma
id|__u32
id|flag
)paren
(brace
r_return
(paren
(paren
(paren
r_int
r_int
)paren
id|SDp-&gt;hostdata
)paren
op_amp
id|flag
)paren
op_eq
id|flag
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|NCR_700_is_flag_clear
id|NCR_700_is_flag_clear
c_func
(paren
id|Scsi_Device
op_star
id|SDp
comma
id|__u32
id|flag
)paren
(brace
r_return
(paren
(paren
(paren
r_int
r_int
)paren
id|SDp-&gt;hostdata
)paren
op_amp
id|flag
)paren
op_eq
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|NCR_700_set_flag
id|NCR_700_set_flag
c_func
(paren
id|Scsi_Device
op_star
id|SDp
comma
id|__u32
id|flag
)paren
(brace
(paren
(paren
r_int
r_int
)paren
id|SDp-&gt;hostdata
)paren
op_or_assign
(paren
id|flag
op_amp
l_int|0xffff0000
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|NCR_700_clear_flag
id|NCR_700_clear_flag
c_func
(paren
id|Scsi_Device
op_star
id|SDp
comma
id|__u32
id|flag
)paren
(brace
(paren
(paren
r_int
r_int
)paren
id|SDp-&gt;hostdata
)paren
op_and_assign
op_complement
(paren
id|flag
op_amp
l_int|0xffff0000
)paren
suffix:semicolon
)brace
multiline_comment|/* These represent the Nexus hashing functions.  A Nexus in SCSI terms&n; * just means the identification of an outstanding command, by ITL&n; * (Initiator Target Lun) or ITLQ (Initiator Target Lun Tag).  I&squot;m not&n; * very keen on XOR based hashes, so these are based on number theory&n; * instead.  All you need to do is to fix your hash bucket size and&n; * then choose reasonable strides which are coprime with the chosen&n; * bucket size&n; *&n; * Note: this mathematical hash can be made very efficient, if the&n; * compiler is good at optimising: Choose the number of buckets to be&n; * 2^n and the modulo becomes a logical and with (2^n-1).&n; * Additionally, if you chose the coprimes of the form 2^n-2^n the&n; * multiplication can be done by a shift and an addition. */
DECL|macro|MAX_ITL_HASH_BUCKETS
mdefine_line|#define MAX_ITL_HASH_BUCKETS&t;16
DECL|macro|ITL_HASH_PRIME
mdefine_line|#define ITL_HASH_PRIME&t;&t;7
DECL|macro|MAX_ITLQ_HASH_BUCKETS
mdefine_line|#define MAX_ITLQ_HASH_BUCKETS&t;64
DECL|macro|ITLQ_PUN_PRIME
mdefine_line|#define ITLQ_PUN_PRIME&t;&t;7
DECL|macro|ITLQ_LUN_PRIME
mdefine_line|#define ITLQ_LUN_PRIME&t;&t;3
r_static
r_inline
r_int
DECL|function|hash_ITL
id|hash_ITL
c_func
(paren
id|__u8
id|pun
comma
id|__u8
id|lun
)paren
(brace
r_return
(paren
id|pun
op_star
id|ITL_HASH_PRIME
op_plus
id|lun
)paren
op_mod
id|MAX_ITL_HASH_BUCKETS
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|hash_ITLQ
id|hash_ITLQ
c_func
(paren
id|__u8
id|pun
comma
id|__u8
id|lun
comma
id|__u8
id|tag
)paren
(brace
r_return
(paren
id|pun
op_star
id|ITLQ_PUN_PRIME
op_plus
id|lun
op_star
id|ITLQ_LUN_PRIME
op_plus
id|tag
)paren
op_mod
id|MAX_ITLQ_HASH_BUCKETS
suffix:semicolon
)brace
DECL|struct|NCR_700_command_slot
r_struct
id|NCR_700_command_slot
(brace
DECL|member|SG
r_struct
id|NCR_700_SG_List
id|SG
(braket
id|NCR_700_SG_SEGMENTS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|pSG
r_struct
id|NCR_700_SG_List
op_star
id|pSG
suffix:semicolon
DECL|macro|NCR_700_SLOT_MASK
mdefine_line|#define NCR_700_SLOT_MASK 0xFC
DECL|macro|NCR_700_SLOT_MAGIC
mdefine_line|#define NCR_700_SLOT_MAGIC 0xb8
DECL|macro|NCR_700_SLOT_FREE
mdefine_line|#define&t;NCR_700_SLOT_FREE (0|NCR_700_SLOT_MAGIC) /* slot may be used */
DECL|macro|NCR_700_SLOT_BUSY
mdefine_line|#define NCR_700_SLOT_BUSY (1|NCR_700_SLOT_MAGIC) /* slot has command active on HA */
DECL|macro|NCR_700_SLOT_QUEUED
mdefine_line|#define NCR_700_SLOT_QUEUED (2|NCR_700_SLOT_MAGIC) /* slot has command to be made active on HA */
DECL|member|state
id|__u8
id|state
suffix:semicolon
DECL|macro|NCR_700_NO_TAG
mdefine_line|#define NCR_700_NO_TAG&t;0xdead
DECL|member|tag
id|__u16
id|tag
suffix:semicolon
DECL|member|resume_offset
id|__u32
id|resume_offset
suffix:semicolon
DECL|member|cmnd
id|Scsi_Cmnd
op_star
id|cmnd
suffix:semicolon
multiline_comment|/* The pci_mapped address of the actual command in cmnd */
DECL|member|pCmd
id|dma_addr_t
id|pCmd
suffix:semicolon
DECL|member|temp
id|__u32
id|temp
suffix:semicolon
multiline_comment|/* if this command is a pci_single mapping, holds the dma address&n;&t; * for later unmapping in the done routine */
DECL|member|dma_handle
id|dma_addr_t
id|dma_handle
suffix:semicolon
multiline_comment|/* Doubly linked ITL/ITLQ list kept in strict time order&n;&t; * (latest at the back) */
DECL|member|ITL_forw
r_struct
id|NCR_700_command_slot
op_star
id|ITL_forw
suffix:semicolon
DECL|member|ITL_back
r_struct
id|NCR_700_command_slot
op_star
id|ITL_back
suffix:semicolon
DECL|member|ITLQ_forw
r_struct
id|NCR_700_command_slot
op_star
id|ITLQ_forw
suffix:semicolon
DECL|member|ITLQ_back
r_struct
id|NCR_700_command_slot
op_star
id|ITLQ_back
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|NCR_700_Host_Parameters
r_struct
id|NCR_700_Host_Parameters
(brace
multiline_comment|/* These must be filled in by the calling driver */
DECL|member|clock
r_int
id|clock
suffix:semicolon
multiline_comment|/* board clock speed in MHz */
DECL|member|base
id|__u32
id|base
suffix:semicolon
multiline_comment|/* the base for the port (copied to host) */
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
DECL|member|dmode_extra
id|__u32
id|dmode_extra
suffix:semicolon
multiline_comment|/* adjustable bus settings */
DECL|member|differential
id|__u32
id|differential
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* if we are differential */
macro_line|#ifdef CONFIG_53C700_LE_ON_BE
multiline_comment|/* This option is for HP only.  Set it if your chip is wired for&n;&t; * little endian on this platform (which is big endian) */
DECL|member|force_le_on_be
id|__u32
id|force_le_on_be
suffix:colon
l_int|1
suffix:semicolon
macro_line|#endif
DECL|member|chip710
id|__u32
id|chip710
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set if really a 710 not 700 */
DECL|member|burst_disable
id|__u32
id|burst_disable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set to 1 to disable 710 bursting */
multiline_comment|/* NOTHING BELOW HERE NEEDS ALTERING */
DECL|member|fast
id|__u32
id|fast
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* if we can alter the SCSI bus clock&n;                                   speed (so can negiotiate sync) */
macro_line|#ifdef CONFIG_53C700_USE_CONSISTENT
DECL|member|consistent
id|__u32
id|consistent
suffix:colon
l_int|1
suffix:semicolon
macro_line|#endif
DECL|member|sync_clock
r_int
id|sync_clock
suffix:semicolon
multiline_comment|/* The speed of the SYNC core */
DECL|member|script
id|__u32
op_star
id|script
suffix:semicolon
multiline_comment|/* pointer to script location */
DECL|member|pScript
id|__u32
id|pScript
suffix:semicolon
multiline_comment|/* physical mem addr of script */
multiline_comment|/* This will be the host lock.  Unfortunately, we can&squot;t use it&n;&t; * at the moment because of the necessity of holding the&n;&t; * io_request_lock */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|state
r_enum
id|NCR_700_Host_State
id|state
suffix:semicolon
multiline_comment|/* protected by state lock */
DECL|member|cmd
id|Scsi_Cmnd
op_star
id|cmd
suffix:semicolon
multiline_comment|/* Note: pScript contains the single consistent block of&n;&t; * memory.  All the msgin, msgout and status are allocated in&n;&t; * this memory too (at separate cache lines).  TOTAL_MEM_SIZE&n;&t; * represents the total size of this area */
DECL|macro|MSG_ARRAY_SIZE
mdefine_line|#define&t;MSG_ARRAY_SIZE&t;8
DECL|macro|MSGOUT_OFFSET
mdefine_line|#define&t;MSGOUT_OFFSET&t;(L1_CACHE_ALIGN(sizeof(SCRIPT)))
DECL|member|msgout
id|__u8
op_star
id|msgout
suffix:semicolon
DECL|macro|MSGIN_OFFSET
mdefine_line|#define MSGIN_OFFSET&t;(MSGOUT_OFFSET + L1_CACHE_ALIGN(MSG_ARRAY_SIZE))
DECL|member|msgin
id|__u8
op_star
id|msgin
suffix:semicolon
DECL|macro|STATUS_OFFSET
mdefine_line|#define STATUS_OFFSET&t;(MSGIN_OFFSET + L1_CACHE_ALIGN(MSG_ARRAY_SIZE))
DECL|member|status
id|__u8
op_star
id|status
suffix:semicolon
DECL|macro|SLOTS_OFFSET
mdefine_line|#define SLOTS_OFFSET&t;(STATUS_OFFSET + L1_CACHE_ALIGN(MSG_ARRAY_SIZE))
DECL|member|slots
r_struct
id|NCR_700_command_slot
op_star
id|slots
suffix:semicolon
DECL|macro|TOTAL_MEM_SIZE
mdefine_line|#define&t;TOTAL_MEM_SIZE&t;(SLOTS_OFFSET + L1_CACHE_ALIGN(sizeof(struct NCR_700_command_slot) * NCR_700_COMMAND_SLOTS_PER_HOST))
DECL|member|saved_slot_position
r_int
id|saved_slot_position
suffix:semicolon
DECL|member|command_slot_count
r_int
id|command_slot_count
suffix:semicolon
multiline_comment|/* protected by state lock */
DECL|member|tag_negotiated
id|__u8
id|tag_negotiated
suffix:semicolon
DECL|member|rev
id|__u8
id|rev
suffix:semicolon
DECL|member|reselection_id
id|__u8
id|reselection_id
suffix:semicolon
multiline_comment|/* flags for the host */
multiline_comment|/* ITL list.  ALL outstanding commands are hashed here in strict&n;&t; * order, latest at the back */
DECL|member|ITL_Hash_forw
r_struct
id|NCR_700_command_slot
op_star
id|ITL_Hash_forw
(braket
id|MAX_ITL_HASH_BUCKETS
)braket
suffix:semicolon
DECL|member|ITL_Hash_back
r_struct
id|NCR_700_command_slot
op_star
id|ITL_Hash_back
(braket
id|MAX_ITL_HASH_BUCKETS
)braket
suffix:semicolon
multiline_comment|/* Only tagged outstanding commands are hashed here (also latest&n;&t; * at the back) */
DECL|member|ITLQ_Hash_forw
r_struct
id|NCR_700_command_slot
op_star
id|ITLQ_Hash_forw
(braket
id|MAX_ITLQ_HASH_BUCKETS
)braket
suffix:semicolon
DECL|member|ITLQ_Hash_back
r_struct
id|NCR_700_command_slot
op_star
id|ITLQ_Hash_back
(braket
id|MAX_ITLQ_HASH_BUCKETS
)braket
suffix:semicolon
multiline_comment|/* Free list, singly linked by ITL_forw elements */
DECL|member|free_list
r_struct
id|NCR_700_command_slot
op_star
id|free_list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;53C700 Register Interface - the offset from the Selected base&n; *&t;I/O address */
macro_line|#ifdef CONFIG_53C700_LE_ON_BE
DECL|macro|bE
mdefine_line|#define bE&t;(hostdata-&gt;force_le_on_be ? 0 : 3)
DECL|macro|bSWAP
mdefine_line|#define&t;bSWAP&t;(hostdata-&gt;force_le_on_be)
macro_line|#elif defined(__BIG_ENDIAN)
DECL|macro|bE
mdefine_line|#define bE&t;3
DECL|macro|bSWAP
mdefine_line|#define bSWAP&t;0
macro_line|#elif defined(__LITTLE_ENDIAN)
DECL|macro|bE
mdefine_line|#define bE&t;0
DECL|macro|bSWAP
mdefine_line|#define bSWAP&t;0
macro_line|#else
macro_line|#error &quot;__BIG_ENDIAN or __LITTLE_ENDIAN must be defined, did you include byteorder.h?&quot;
macro_line|#endif
DECL|macro|bS_to_cpu
mdefine_line|#define bS_to_cpu(x)&t;(bSWAP ? le32_to_cpu(x) : (x))
DECL|macro|bS_to_host
mdefine_line|#define bS_to_host(x)&t;(bSWAP ? cpu_to_le32(x) : (x))
multiline_comment|/* NOTE: These registers are in the LE register space only, the required byte&n; * swapping is done by the NCR_700_{read|write}[b] functions */
DECL|macro|SCNTL0_REG
mdefine_line|#define&t;SCNTL0_REG&t;&t;&t;0x00
DECL|macro|FULL_ARBITRATION
mdefine_line|#define&t;&t;FULL_ARBITRATION&t;0xc0
DECL|macro|PARITY
mdefine_line|#define &t;PARITY&t;&t;&t;0x08
DECL|macro|ENABLE_PARITY
mdefine_line|#define&t;&t;ENABLE_PARITY&t;&t;0x04
DECL|macro|AUTO_ATN
mdefine_line|#define &t;AUTO_ATN&t;&t;0x02
DECL|macro|SCNTL1_REG
mdefine_line|#define&t;SCNTL1_REG&t;&t;&t;0x01
DECL|macro|SLOW_BUS
mdefine_line|#define &t;SLOW_BUS&t;&t;0x80
DECL|macro|ENABLE_SELECT
mdefine_line|#define&t;&t;ENABLE_SELECT&t;&t;0x20
DECL|macro|ASSERT_RST
mdefine_line|#define&t;&t;ASSERT_RST&t;&t;0x08
DECL|macro|ASSERT_EVEN_PARITY
mdefine_line|#define&t;&t;ASSERT_EVEN_PARITY&t;0x04
DECL|macro|SDID_REG
mdefine_line|#define&t;SDID_REG&t;&t;&t;0x02
DECL|macro|SIEN_REG
mdefine_line|#define&t;SIEN_REG&t;&t;&t;0x03
DECL|macro|PHASE_MM_INT
mdefine_line|#define &t;PHASE_MM_INT&t;&t;0x80
DECL|macro|FUNC_COMP_INT
mdefine_line|#define &t;FUNC_COMP_INT&t;&t;0x40
DECL|macro|SEL_TIMEOUT_INT
mdefine_line|#define &t;SEL_TIMEOUT_INT&t;&t;0x20
DECL|macro|SELECT_INT
mdefine_line|#define &t;SELECT_INT&t;&t;0x10
DECL|macro|GROSS_ERR_INT
mdefine_line|#define &t;GROSS_ERR_INT&t;&t;0x08
DECL|macro|UX_DISC_INT
mdefine_line|#define &t;UX_DISC_INT&t;&t;0x04
DECL|macro|RST_INT
mdefine_line|#define &t;RST_INT&t;&t;&t;0x02
DECL|macro|PAR_ERR_INT
mdefine_line|#define &t;PAR_ERR_INT&t;&t;0x01
DECL|macro|SCID_REG
mdefine_line|#define&t;SCID_REG&t;&t;&t;0x04
DECL|macro|SXFER_REG
mdefine_line|#define SXFER_REG&t;&t;&t;0x05
DECL|macro|ASYNC_OPERATION
mdefine_line|#define&t;&t;ASYNC_OPERATION&t;&t;0x00
DECL|macro|SODL_REG
mdefine_line|#define SODL_REG                        0x06
DECL|macro|SOCL_REG
mdefine_line|#define&t;SOCL_REG&t;&t;&t;0x07
DECL|macro|SFBR_REG
mdefine_line|#define&t;SFBR_REG&t;&t;&t;0x08
DECL|macro|SIDL_REG
mdefine_line|#define&t;SIDL_REG&t;&t;&t;0x09
DECL|macro|SBDL_REG
mdefine_line|#define&t;SBDL_REG&t;&t;&t;0x0A
DECL|macro|SBCL_REG
mdefine_line|#define&t;SBCL_REG&t;&t;&t;0x0B
multiline_comment|/* read bits */
DECL|macro|SBCL_IO
mdefine_line|#define&t;&t;SBCL_IO&t;&t;&t;0x01
multiline_comment|/*write bits */
DECL|macro|SYNC_DIV_AS_ASYNC
mdefine_line|#define&t;&t;SYNC_DIV_AS_ASYNC&t;0x00
DECL|macro|SYNC_DIV_1_0
mdefine_line|#define&t;&t;SYNC_DIV_1_0&t;&t;0x01
DECL|macro|SYNC_DIV_1_5
mdefine_line|#define&t;&t;SYNC_DIV_1_5&t;&t;0x02
DECL|macro|SYNC_DIV_2_0
mdefine_line|#define&t;&t;SYNC_DIV_2_0&t;&t;0x03
DECL|macro|DSTAT_REG
mdefine_line|#define&t;DSTAT_REG&t;&t;&t;0x0C
DECL|macro|ILGL_INST_DETECTED
mdefine_line|#define&t;&t;ILGL_INST_DETECTED&t;0x01
DECL|macro|WATCH_DOG_INTERRUPT
mdefine_line|#define&t;&t;WATCH_DOG_INTERRUPT&t;0x02
DECL|macro|SCRIPT_INT_RECEIVED
mdefine_line|#define&t;&t;SCRIPT_INT_RECEIVED&t;0x04
DECL|macro|ABORTED
mdefine_line|#define&t;&t;ABORTED&t;&t;&t;0x10
DECL|macro|SSTAT0_REG
mdefine_line|#define&t;SSTAT0_REG&t;&t;&t;0x0D
DECL|macro|PARITY_ERROR
mdefine_line|#define&t;&t;PARITY_ERROR&t;&t;0x01
DECL|macro|SCSI_RESET_DETECTED
mdefine_line|#define&t;&t;SCSI_RESET_DETECTED&t;0x02
DECL|macro|UNEXPECTED_DISCONNECT
mdefine_line|#define&t;&t;UNEXPECTED_DISCONNECT&t;0x04
DECL|macro|SCSI_GROSS_ERROR
mdefine_line|#define&t;&t;SCSI_GROSS_ERROR&t;0x08
DECL|macro|SELECTED
mdefine_line|#define&t;&t;SELECTED&t;&t;0x10
DECL|macro|SELECTION_TIMEOUT
mdefine_line|#define&t;&t;SELECTION_TIMEOUT&t;0x20
DECL|macro|FUNCTION_COMPLETE
mdefine_line|#define&t;&t;FUNCTION_COMPLETE&t;0x40
DECL|macro|PHASE_MISMATCH
mdefine_line|#define&t;&t;PHASE_MISMATCH &t;&t;0x80
DECL|macro|SSTAT1_REG
mdefine_line|#define&t;SSTAT1_REG&t;&t;&t;0x0E
DECL|macro|SIDL_REG_FULL
mdefine_line|#define&t;&t;SIDL_REG_FULL&t;&t;0x80
DECL|macro|SODR_REG_FULL
mdefine_line|#define&t;&t;SODR_REG_FULL&t;&t;0x40
DECL|macro|SODL_REG_FULL
mdefine_line|#define&t;&t;SODL_REG_FULL&t;&t;0x20
DECL|macro|SSTAT2_REG
mdefine_line|#define SSTAT2_REG                      0x0F
DECL|macro|CTEST0_REG
mdefine_line|#define CTEST0_REG                      0x14
DECL|macro|BTB_TIMER_DISABLE
mdefine_line|#define&t;&t;BTB_TIMER_DISABLE&t;0x40
DECL|macro|CTEST1_REG
mdefine_line|#define CTEST1_REG                      0x15
DECL|macro|CTEST2_REG
mdefine_line|#define CTEST2_REG                      0x16
DECL|macro|CTEST3_REG
mdefine_line|#define CTEST3_REG                      0x17
DECL|macro|CTEST4_REG
mdefine_line|#define CTEST4_REG                      0x18
DECL|macro|DISABLE_FIFO
mdefine_line|#define         DISABLE_FIFO            0x00
DECL|macro|SLBE
mdefine_line|#define         SLBE                    0x10
DECL|macro|SFWR
mdefine_line|#define         SFWR                    0x08
DECL|macro|BYTE_LANE0
mdefine_line|#define         BYTE_LANE0              0x04
DECL|macro|BYTE_LANE1
mdefine_line|#define         BYTE_LANE1              0x05
DECL|macro|BYTE_LANE2
mdefine_line|#define         BYTE_LANE2              0x06
DECL|macro|BYTE_LANE3
mdefine_line|#define         BYTE_LANE3              0x07
DECL|macro|SCSI_ZMODE
mdefine_line|#define         SCSI_ZMODE              0x20
DECL|macro|ZMODE
mdefine_line|#define         ZMODE                   0x40
DECL|macro|CTEST5_REG
mdefine_line|#define CTEST5_REG                      0x19
DECL|macro|MASTER_CONTROL
mdefine_line|#define         MASTER_CONTROL          0x10
DECL|macro|DMA_DIRECTION
mdefine_line|#define         DMA_DIRECTION           0x08
DECL|macro|CTEST7_REG
mdefine_line|#define CTEST7_REG                      0x1B
DECL|macro|BURST_DISABLE
mdefine_line|#define&t;&t;BURST_DISABLE&t;&t;0x80 /* 710 only */
DECL|macro|SEL_TIMEOUT_DISABLE
mdefine_line|#define&t;&t;SEL_TIMEOUT_DISABLE&t;0x10 /* 710 only */
DECL|macro|DFP
mdefine_line|#define         DFP                     0x08
DECL|macro|EVP
mdefine_line|#define         EVP                     0x04
DECL|macro|DIFF
mdefine_line|#define&t;&t;DIFF&t;&t;&t;0x01
DECL|macro|CTEST6_REG
mdefine_line|#define CTEST6_REG                      0x1A
DECL|macro|TEMP_REG
mdefine_line|#define&t;TEMP_REG&t;&t;&t;0x1C
DECL|macro|DFIFO_REG
mdefine_line|#define&t;DFIFO_REG&t;&t;&t;0x20
DECL|macro|FLUSH_DMA_FIFO
mdefine_line|#define&t;&t;FLUSH_DMA_FIFO&t;&t;0x80
DECL|macro|CLR_FIFO
mdefine_line|#define&t;&t;CLR_FIFO&t;&t;0x40
DECL|macro|ISTAT_REG
mdefine_line|#define&t;ISTAT_REG&t;&t;&t;0x21
DECL|macro|ABORT_OPERATION
mdefine_line|#define&t;&t;ABORT_OPERATION&t;&t;0x80
DECL|macro|SOFTWARE_RESET_710
mdefine_line|#define&t;&t;SOFTWARE_RESET_710&t;0x40
DECL|macro|DMA_INT_PENDING
mdefine_line|#define&t;&t;DMA_INT_PENDING&t;&t;0x01
DECL|macro|SCSI_INT_PENDING
mdefine_line|#define&t;&t;SCSI_INT_PENDING&t;0x02
DECL|macro|CONNECTED
mdefine_line|#define&t;&t;CONNECTED&t;&t;0x08
DECL|macro|CTEST8_REG
mdefine_line|#define CTEST8_REG                      0x22
DECL|macro|LAST_DIS_ENBL
mdefine_line|#define         LAST_DIS_ENBL           0x01
DECL|macro|SHORTEN_FILTERING
mdefine_line|#define&t;&t;SHORTEN_FILTERING&t;0x04
DECL|macro|ENABLE_ACTIVE_NEGATION
mdefine_line|#define&t;&t;ENABLE_ACTIVE_NEGATION&t;0x10
DECL|macro|GENERATE_RECEIVE_PARITY
mdefine_line|#define&t;&t;GENERATE_RECEIVE_PARITY&t;0x20
DECL|macro|CLR_FIFO_710
mdefine_line|#define&t;&t;CLR_FIFO_710&t;&t;0x04
DECL|macro|FLUSH_DMA_FIFO_710
mdefine_line|#define&t;&t;FLUSH_DMA_FIFO_710&t;0x08
DECL|macro|CTEST9_REG
mdefine_line|#define CTEST9_REG                      0x23
DECL|macro|DBC_REG
mdefine_line|#define&t;DBC_REG&t;&t;&t;&t;0x24
DECL|macro|DCMD_REG
mdefine_line|#define&t;DCMD_REG&t;&t;&t;0x27
DECL|macro|DNAD_REG
mdefine_line|#define&t;DNAD_REG&t;&t;&t;0x28
DECL|macro|DIEN_REG
mdefine_line|#define&t;DIEN_REG&t;&t;&t;0x39
DECL|macro|BUS_FAULT
mdefine_line|#define&t;&t;BUS_FAULT&t;&t;0x20
DECL|macro|ABORT_INT
mdefine_line|#define &t;ABORT_INT&t;&t;0x10
DECL|macro|INT_INST_INT
mdefine_line|#define &t;INT_INST_INT&t;&t;0x04
DECL|macro|WD_INT
mdefine_line|#define &t;WD_INT&t;&t;&t;0x02
DECL|macro|ILGL_INST_INT
mdefine_line|#define &t;ILGL_INST_INT&t;&t;0x01
DECL|macro|DCNTL_REG
mdefine_line|#define&t;DCNTL_REG&t;&t;&t;0x3B
DECL|macro|SOFTWARE_RESET
mdefine_line|#define&t;&t;SOFTWARE_RESET&t;&t;0x01
DECL|macro|COMPAT_700_MODE
mdefine_line|#define&t;&t;COMPAT_700_MODE&t;&t;0x01
DECL|macro|SCRPTS_16BITS
mdefine_line|#define &t;SCRPTS_16BITS&t;&t;0x20
DECL|macro|ASYNC_DIV_2_0
mdefine_line|#define&t;&t;ASYNC_DIV_2_0&t;&t;0x00
DECL|macro|ASYNC_DIV_1_5
mdefine_line|#define&t;&t;ASYNC_DIV_1_5&t;&t;0x40
DECL|macro|ASYNC_DIV_1_0
mdefine_line|#define&t;&t;ASYNC_DIV_1_0&t;&t;0x80
DECL|macro|ASYNC_DIV_3_0
mdefine_line|#define&t;&t;ASYNC_DIV_3_0&t;&t;0xc0
DECL|macro|DMODE_710_REG
mdefine_line|#define DMODE_710_REG&t;&t;&t;0x38
DECL|macro|DMODE_700_REG
mdefine_line|#define&t;DMODE_700_REG&t;&t;&t;0x34
DECL|macro|BURST_LENGTH_1
mdefine_line|#define&t;&t;BURST_LENGTH_1&t;&t;0x00
DECL|macro|BURST_LENGTH_2
mdefine_line|#define&t;&t;BURST_LENGTH_2&t;&t;0x40
DECL|macro|BURST_LENGTH_4
mdefine_line|#define&t;&t;BURST_LENGTH_4&t;&t;0x80
DECL|macro|BURST_LENGTH_8
mdefine_line|#define&t;&t;BURST_LENGTH_8&t;&t;0xC0
DECL|macro|DMODE_FC1
mdefine_line|#define&t;&t;DMODE_FC1&t;&t;0x10
DECL|macro|DMODE_FC2
mdefine_line|#define&t;&t;DMODE_FC2&t;&t;0x20
DECL|macro|BW16
mdefine_line|#define &t;BW16&t;&t;&t;32 
DECL|macro|MODE_286
mdefine_line|#define &t;MODE_286&t;&t;16
DECL|macro|IO_XFER
mdefine_line|#define &t;IO_XFER&t;&t;&t;8
DECL|macro|FIXED_ADDR
mdefine_line|#define &t;FIXED_ADDR&t;&t;4
DECL|macro|DSP_REG
mdefine_line|#define DSP_REG                         0x2C
DECL|macro|DSPS_REG
mdefine_line|#define DSPS_REG                        0x30
multiline_comment|/* Parameters to begin SDTR negotiations.  Empirically, I find that&n; * the 53c700-66 cannot handle an offset &gt;8, so don&squot;t change this  */
DECL|macro|NCR_700_MAX_OFFSET
mdefine_line|#define NCR_700_MAX_OFFSET&t;8
multiline_comment|/* Was hoping the max offset would be greater for the 710, but&n; * empirically it seems to be 8 also */
DECL|macro|NCR_710_MAX_OFFSET
mdefine_line|#define NCR_710_MAX_OFFSET&t;8
DECL|macro|NCR_700_MIN_XFERP
mdefine_line|#define NCR_700_MIN_XFERP&t;1
DECL|macro|NCR_710_MIN_XFERP
mdefine_line|#define NCR_710_MIN_XFERP&t;0
DECL|macro|NCR_700_MIN_PERIOD
mdefine_line|#define NCR_700_MIN_PERIOD&t;25 /* for SDTR message, 100ns */
DECL|macro|script_patch_32
mdefine_line|#define script_patch_32(script, symbol, value) &bslash;&n;{ &bslash;&n;&t;int i; &bslash;&n;&t;for(i=0; i&lt; (sizeof(A_##symbol##_used) / sizeof(__u32)); i++) { &bslash;&n;&t;&t;__u32 val = bS_to_cpu((script)[A_##symbol##_used[i]]) + value; &bslash;&n;&t;&t;(script)[A_##symbol##_used[i]] = bS_to_host(val); &bslash;&n;&t;&t;dma_cache_wback((unsigned long)&amp;(script)[A_##symbol##_used[i]], 4); &bslash;&n;&t;&t;DEBUG((&quot; script, patching %s at %d to 0x%lx&bslash;n&quot;, &bslash;&n;&t;&t;       #symbol, A_##symbol##_used[i], (value))); &bslash;&n;&t;} &bslash;&n;}
DECL|macro|script_patch_32_abs
mdefine_line|#define script_patch_32_abs(script, symbol, value) &bslash;&n;{ &bslash;&n;&t;int i; &bslash;&n;&t;for(i=0; i&lt; (sizeof(A_##symbol##_used) / sizeof(__u32)); i++) { &bslash;&n;&t;&t;(script)[A_##symbol##_used[i]] = bS_to_host(value); &bslash;&n;&t;&t;dma_cache_wback((unsigned long)&amp;(script)[A_##symbol##_used[i]], 4); &bslash;&n;&t;&t;DEBUG((&quot; script, patching %s at %d to 0x%lx&bslash;n&quot;, &bslash;&n;&t;&t;       #symbol, A_##symbol##_used[i], (value))); &bslash;&n;&t;} &bslash;&n;}
multiline_comment|/* Used for patching the SCSI ID in the SELECT instruction */
DECL|macro|script_patch_ID
mdefine_line|#define script_patch_ID(script, symbol, value) &bslash;&n;{ &bslash;&n;&t;int i; &bslash;&n;&t;for(i=0; i&lt; (sizeof(A_##symbol##_used) / sizeof(__u32)); i++) { &bslash;&n;&t;&t;__u32 val = bS_to_cpu((script)[A_##symbol##_used[i]]); &bslash;&n;&t;&t;val &amp;= 0xff00ffff; &bslash;&n;&t;&t;val |= ((value) &amp; 0xff) &lt;&lt; 16; &bslash;&n;&t;&t;(script)[A_##symbol##_used[i]] = bS_to_host(val); &bslash;&n;&t;&t;dma_cache_wback((unsigned long)&amp;(script)[A_##symbol##_used[i]], 4); &bslash;&n;&t;&t;DEBUG((&quot; script, patching ID field %s at %d to 0x%x&bslash;n&quot;, &bslash;&n;&t;&t;       #symbol, A_##symbol##_used[i], val)); &bslash;&n;&t;} &bslash;&n;}
DECL|macro|script_patch_16
mdefine_line|#define script_patch_16(script, symbol, value) &bslash;&n;{ &bslash;&n;&t;int i; &bslash;&n;&t;for(i=0; i&lt; (sizeof(A_##symbol##_used) / sizeof(__u32)); i++) { &bslash;&n;&t;&t;__u32 val = bS_to_cpu((script)[A_##symbol##_used[i]]); &bslash;&n;&t;&t;val &amp;= 0xffff0000; &bslash;&n;&t;&t;val |= ((value) &amp; 0xffff); &bslash;&n;&t;&t;(script)[A_##symbol##_used[i]] = bS_to_host(val); &bslash;&n;&t;&t;dma_cache_wback((unsigned long)&amp;(script)[A_##symbol##_used[i]], 4); &bslash;&n;&t;&t;DEBUG((&quot; script, patching short field %s at %d to 0x%x&bslash;n&quot;, &bslash;&n;&t;&t;       #symbol, A_##symbol##_used[i], val)); &bslash;&n;&t;} &bslash;&n;}
macro_line|#endif
macro_line|#ifdef CONFIG_53C700_MEM_MAPPED
r_static
r_inline
id|__u8
DECL|function|NCR_700_readb
id|NCR_700_readb
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
id|__u32
id|reg
)paren
(brace
r_const
r_struct
id|NCR_700_Host_Parameters
op_star
id|hostdata
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(paren
r_struct
id|NCR_700_Host_Parameters
op_star
)paren
id|host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
r_return
id|readb
c_func
(paren
id|host-&gt;base
op_plus
(paren
id|reg
op_xor
id|bE
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u32
DECL|function|NCR_700_readl
id|NCR_700_readl
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
id|__u32
id|reg
)paren
(brace
id|__u32
id|value
op_assign
id|readl
c_func
(paren
id|host-&gt;base
op_plus
id|reg
)paren
suffix:semicolon
r_const
r_struct
id|NCR_700_Host_Parameters
op_star
id|hostdata
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(paren
r_struct
id|NCR_700_Host_Parameters
op_star
)paren
id|host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#if 1
multiline_comment|/* sanity check the register */
r_if
c_cond
(paren
(paren
id|reg
op_amp
l_int|0x3
)paren
op_ne
l_int|0
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|bS_to_cpu
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|NCR_700_writeb
id|NCR_700_writeb
c_func
(paren
id|__u8
id|value
comma
r_struct
id|Scsi_Host
op_star
id|host
comma
id|__u32
id|reg
)paren
(brace
r_const
r_struct
id|NCR_700_Host_Parameters
op_star
id|hostdata
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(paren
r_struct
id|NCR_700_Host_Parameters
op_star
)paren
id|host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
id|writeb
c_func
(paren
id|value
comma
id|host-&gt;base
op_plus
(paren
id|reg
op_xor
id|bE
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|NCR_700_writel
id|NCR_700_writel
c_func
(paren
id|__u32
id|value
comma
r_struct
id|Scsi_Host
op_star
id|host
comma
id|__u32
id|reg
)paren
(brace
r_const
r_struct
id|NCR_700_Host_Parameters
op_star
id|hostdata
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(paren
r_struct
id|NCR_700_Host_Parameters
op_star
)paren
id|host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#if 1
multiline_comment|/* sanity check the register */
r_if
c_cond
(paren
(paren
id|reg
op_amp
l_int|0x3
)paren
op_ne
l_int|0
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|writel
c_func
(paren
id|bS_to_host
c_func
(paren
id|value
)paren
comma
id|host-&gt;base
op_plus
id|reg
)paren
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_53C700_IO_MAPPED)
r_static
r_inline
id|__u8
DECL|function|NCR_700_readb
id|NCR_700_readb
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
id|__u32
id|reg
)paren
(brace
r_const
r_struct
id|NCR_700_Host_Parameters
op_star
id|hostdata
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(paren
r_struct
id|NCR_700_Host_Parameters
op_star
)paren
id|host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
r_return
id|inb
c_func
(paren
id|host-&gt;base
op_plus
(paren
id|reg
op_xor
id|bE
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u32
DECL|function|NCR_700_readl
id|NCR_700_readl
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
comma
id|__u32
id|reg
)paren
(brace
id|__u32
id|value
op_assign
id|inl
c_func
(paren
id|host-&gt;base
op_plus
id|reg
)paren
suffix:semicolon
r_const
r_struct
id|NCR_700_Host_Parameters
op_star
id|hostdata
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(paren
r_struct
id|NCR_700_Host_Parameters
op_star
)paren
id|host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#if 1
multiline_comment|/* sanity check the register */
r_if
c_cond
(paren
(paren
id|reg
op_amp
l_int|0x3
)paren
op_ne
l_int|0
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|bS_to_cpu
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|NCR_700_writeb
id|NCR_700_writeb
c_func
(paren
id|__u8
id|value
comma
r_struct
id|Scsi_Host
op_star
id|host
comma
id|__u32
id|reg
)paren
(brace
r_const
r_struct
id|NCR_700_Host_Parameters
op_star
id|hostdata
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(paren
r_struct
id|NCR_700_Host_Parameters
op_star
)paren
id|host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
id|outb
c_func
(paren
id|value
comma
id|host-&gt;base
op_plus
(paren
id|reg
op_xor
id|bE
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|NCR_700_writel
id|NCR_700_writel
c_func
(paren
id|__u32
id|value
comma
r_struct
id|Scsi_Host
op_star
id|host
comma
id|__u32
id|reg
)paren
(brace
r_const
r_struct
id|NCR_700_Host_Parameters
op_star
id|hostdata
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
op_assign
(paren
r_struct
id|NCR_700_Host_Parameters
op_star
)paren
id|host-&gt;hostdata
(braket
l_int|0
)braket
suffix:semicolon
macro_line|#if 1
multiline_comment|/* sanity check the register */
r_if
c_cond
(paren
(paren
id|reg
op_amp
l_int|0x3
)paren
op_ne
l_int|0
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|outl
c_func
(paren
id|bS_to_host
c_func
(paren
id|value
)paren
comma
id|host-&gt;base
op_plus
id|reg
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
