multiline_comment|/*&n; *   (c) 2003 Advanced Micro Devices, Inc.&n; *  Your use of this code is subject to the terms and conditions of the&n; *  GNU general public license version 2. See &quot;../../../COPYING&quot; or&n; *  http://www.gnu.org/licenses/gpl.html&n; */
multiline_comment|/* processor&squot;s cpuid instruction support */
DECL|macro|CPUID_PROCESSOR_SIGNATURE
mdefine_line|#define CPUID_PROCESSOR_SIGNATURE             1&t;/* function 1               */
DECL|macro|CPUID_F1_FAM
mdefine_line|#define CPUID_F1_FAM                 0x00000f00&t;/* family mask              */
DECL|macro|CPUID_F1_XFAM
mdefine_line|#define CPUID_F1_XFAM                0x0ff00000&t;/* extended family mask     */
DECL|macro|CPUID_F1_MOD
mdefine_line|#define CPUID_F1_MOD                 0x000000f0&t;/* model mask               */
DECL|macro|CPUID_F1_STEP
mdefine_line|#define CPUID_F1_STEP                0x0000000f&t;/* stepping level mask      */
DECL|macro|CPUID_XFAM_MOD
mdefine_line|#define CPUID_XFAM_MOD               0x0ff00ff0&t;/* xtended fam, fam + model */
DECL|macro|ATHLON64_XFAM_MOD
mdefine_line|#define ATHLON64_XFAM_MOD            0x00000f40&t;/* xtended fam, fam + model */
DECL|macro|OPTERON_XFAM_MOD
mdefine_line|#define OPTERON_XFAM_MOD             0x00000f50&t;/* xtended fam, fam + model */
DECL|macro|ATHLON64_REV_C0
mdefine_line|#define ATHLON64_REV_C0                       8
DECL|macro|CPUID_GET_MAX_CAPABILITIES
mdefine_line|#define CPUID_GET_MAX_CAPABILITIES   0x80000000
DECL|macro|CPUID_FREQ_VOLT_CAPABILITIES
mdefine_line|#define CPUID_FREQ_VOLT_CAPABILITIES 0x80000007
DECL|macro|P_STATE_TRANSITION_CAPABLE
mdefine_line|#define P_STATE_TRANSITION_CAPABLE            6
multiline_comment|/* Model Specific Registers for p-state transitions. MSRs are 64-bit. For     */
multiline_comment|/* writes (wrmsr - opcode 0f 30), the register number is placed in ecx, and   */
multiline_comment|/* the value to write is placed in edx:eax. For reads (rdmsr - opcode 0f 32), */
multiline_comment|/* the register number is placed in ecx, and the data is returned in edx:eax. */
DECL|macro|MSR_FIDVID_CTL
mdefine_line|#define MSR_FIDVID_CTL      0xc0010041
DECL|macro|MSR_FIDVID_STATUS
mdefine_line|#define MSR_FIDVID_STATUS   0xc0010042
multiline_comment|/* Field definitions within the FID VID Low Control MSR : */
DECL|macro|MSR_C_LO_INIT_FID_VID
mdefine_line|#define MSR_C_LO_INIT_FID_VID     0x00010000
DECL|macro|MSR_C_LO_NEW_VID
mdefine_line|#define MSR_C_LO_NEW_VID          0x00001f00
DECL|macro|MSR_C_LO_NEW_FID
mdefine_line|#define MSR_C_LO_NEW_FID          0x0000002f
DECL|macro|MSR_C_LO_VID_SHIFT
mdefine_line|#define MSR_C_LO_VID_SHIFT        8
multiline_comment|/* Field definitions within the FID VID High Control MSR : */
DECL|macro|MSR_C_HI_STP_GNT_TO
mdefine_line|#define MSR_C_HI_STP_GNT_TO       0x000fffff
multiline_comment|/* Field definitions within the FID VID Low Status MSR : */
DECL|macro|MSR_S_LO_CHANGE_PENDING
mdefine_line|#define MSR_S_LO_CHANGE_PENDING   0x80000000&t;/* cleared when completed */
DECL|macro|MSR_S_LO_MAX_RAMP_VID
mdefine_line|#define MSR_S_LO_MAX_RAMP_VID     0x1f000000
DECL|macro|MSR_S_LO_MAX_FID
mdefine_line|#define MSR_S_LO_MAX_FID          0x003f0000
DECL|macro|MSR_S_LO_START_FID
mdefine_line|#define MSR_S_LO_START_FID        0x00003f00
DECL|macro|MSR_S_LO_CURRENT_FID
mdefine_line|#define MSR_S_LO_CURRENT_FID      0x0000003f
multiline_comment|/* Field definitions within the FID VID High Status MSR : */
DECL|macro|MSR_S_HI_MAX_WORKING_VID
mdefine_line|#define MSR_S_HI_MAX_WORKING_VID  0x001f0000
DECL|macro|MSR_S_HI_START_VID
mdefine_line|#define MSR_S_HI_START_VID        0x00001f00
DECL|macro|MSR_S_HI_CURRENT_VID
mdefine_line|#define MSR_S_HI_CURRENT_VID      0x0000001f
multiline_comment|/* fids (frequency identifiers) are arranged in 2 tables - lo and hi */
DECL|macro|LO_FID_TABLE_TOP
mdefine_line|#define LO_FID_TABLE_TOP     6
DECL|macro|HI_FID_TABLE_BOTTOM
mdefine_line|#define HI_FID_TABLE_BOTTOM  8
DECL|macro|LO_VCOFREQ_TABLE_TOP
mdefine_line|#define LO_VCOFREQ_TABLE_TOP    1400&t;/* corresponding vco frequency values */
DECL|macro|HI_VCOFREQ_TABLE_BOTTOM
mdefine_line|#define HI_VCOFREQ_TABLE_BOTTOM 1600
DECL|macro|MIN_FREQ_RESOLUTION
mdefine_line|#define MIN_FREQ_RESOLUTION  200 /* fids jump by 2 matching freq jumps by 200 */
DECL|macro|MAX_FID
mdefine_line|#define MAX_FID 0x2a&t;/* Spec only gives FID values as far as 5 GHz */
DECL|macro|LEAST_VID
mdefine_line|#define LEAST_VID 0x1e&t;/* Lowest (numerically highest) useful vid value */
DECL|macro|MIN_FREQ
mdefine_line|#define MIN_FREQ 800&t;/* Min and max freqs, per spec */
DECL|macro|MAX_FREQ
mdefine_line|#define MAX_FREQ 5000
DECL|macro|INVALID_FID_MASK
mdefine_line|#define INVALID_FID_MASK 0xffffffc1  /* not a valid fid if these bits are set */
DECL|macro|INVALID_VID_MASK
mdefine_line|#define INVALID_VID_MASK 0xffffffe0  /* not a valid vid if these bits are set */
DECL|macro|STOP_GRANT_5NS
mdefine_line|#define STOP_GRANT_5NS 1 /* min poss memory access latency for voltage change */
DECL|macro|PLL_LOCK_CONVERSION
mdefine_line|#define PLL_LOCK_CONVERSION (1000/5) /* ms to ns, then divide by clock period */
DECL|macro|MAXIMUM_VID_STEPS
mdefine_line|#define MAXIMUM_VID_STEPS 1  /* Current cpus only allow a single step of 25mV */
DECL|macro|VST_UNITS_20US
mdefine_line|#define VST_UNITS_20US 20   /* Voltage Stabalization Time is in units of 20us */
multiline_comment|/*&n;Version 1.4 of the PSB table. This table is constructed by BIOS and is&n;to tell the OS&squot;s power management driver which VIDs and FIDs are&n;supported by this particular processor. This information is obtained from&n;the data sheets for each processor model by the system vendor and&n;incorporated into the BIOS.&n;If the data in the PSB / PST is wrong, then this driver will program the&n;wrong values into hardware, which is very likely to lead to a crash.&n;*/
DECL|macro|PSB_ID_STRING
mdefine_line|#define PSB_ID_STRING      &quot;AMDK7PNOW!&quot;
DECL|macro|PSB_ID_STRING_LEN
mdefine_line|#define PSB_ID_STRING_LEN  10
DECL|macro|PSB_VERSION_1_4
mdefine_line|#define PSB_VERSION_1_4  0x14
DECL|struct|psb_s
r_struct
id|psb_s
(brace
DECL|member|signature
id|u8
id|signature
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|tableversion
id|u8
id|tableversion
suffix:semicolon
DECL|member|flags1
id|u8
id|flags1
suffix:semicolon
DECL|member|voltagestabilizationtime
id|u16
id|voltagestabilizationtime
suffix:semicolon
DECL|member|flags2
id|u8
id|flags2
suffix:semicolon
DECL|member|numpst
id|u8
id|numpst
suffix:semicolon
DECL|member|cpuid
id|u32
id|cpuid
suffix:semicolon
DECL|member|plllocktime
id|u8
id|plllocktime
suffix:semicolon
DECL|member|maxfid
id|u8
id|maxfid
suffix:semicolon
DECL|member|maxvid
id|u8
id|maxvid
suffix:semicolon
DECL|member|numpstates
id|u8
id|numpstates
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Pairs of fid/vid values are appended to the version 1.4 PSB table. */
DECL|struct|pst_s
r_struct
id|pst_s
(brace
DECL|member|fid
id|u8
id|fid
suffix:semicolon
DECL|member|vid
id|u8
id|vid
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) printk(msg)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) do { } while(0)
macro_line|#endif
r_static
r_inline
r_int
id|core_voltage_pre_transition
c_func
(paren
id|u32
id|reqvid
)paren
suffix:semicolon
r_static
r_inline
r_int
id|core_voltage_post_transition
c_func
(paren
id|u32
id|reqvid
)paren
suffix:semicolon
r_static
r_inline
r_int
id|core_frequency_transition
c_func
(paren
id|u32
id|reqfid
)paren
suffix:semicolon
r_static
r_int
id|powernowk8_verify
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|pol
)paren
suffix:semicolon
r_static
r_int
id|powernowk8_target
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|pol
comma
r_int
id|targfreq
comma
r_int
id|relation
)paren
suffix:semicolon
r_static
r_int
id|__init
id|powernowk8_cpu_init
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|pol
)paren
suffix:semicolon
eof
