DECL|variable|ScsiOpcodeString
r_static
r_const
r_char
op_star
id|ScsiOpcodeString
(braket
l_int|256
)braket
op_assign
(brace
l_string|&quot;TEST UNIT READY&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 00h */
l_string|&quot;REWIND&bslash;0&bslash;002&quot;
l_string|&quot;&bslash;001REZERO UNIT&quot;
comma
multiline_comment|/* 01h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 02h */
l_string|&quot;REQUEST SENSE&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 03h */
l_string|&quot;FORMAT UNIT&bslash;0&bslash;03&quot;
l_string|&quot;&bslash;001FORMAT MEDIUM&bslash;0&quot;
l_string|&quot;&bslash;002FORMAT&quot;
comma
multiline_comment|/* 04h */
l_string|&quot;READ BLOCK LIMITS&bslash;0&bslash;1&quot;
comma
multiline_comment|/* 05h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 06h */
l_string|&quot;REASSIGN BLOCKS&bslash;0&bslash;02&quot;
l_string|&quot;&bslash;010INITIALIZE ELEMENT STATUS&quot;
comma
multiline_comment|/* 07h */
l_string|&quot;READ(06)&bslash;0&bslash;04&quot;
l_string|&quot;&bslash;001READ&bslash;0&quot;
l_string|&quot;&bslash;003RECEIVE&bslash;0&quot;
l_string|&quot;&bslash;011GET MESSAGE(06)&quot;
comma
multiline_comment|/* 08h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 09h */
l_string|&quot;WRITE(06)&bslash;0&bslash;05&quot;
l_string|&quot;&bslash;001WRITE&bslash;0&quot;
l_string|&quot;&bslash;002PRINT&bslash;0&quot;
l_string|&quot;&bslash;003SEND(6)&bslash;0&quot;
l_string|&quot;&bslash;011SEND MESSAGE(06)&quot;
comma
multiline_comment|/* 0Ah */
l_string|&quot;SEEK(06)&bslash;0&bslash;02&quot;
l_string|&quot;&bslash;003SLEW AND PRINT&quot;
comma
multiline_comment|/* 0Bh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 0Ch */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 0Dh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 0Eh */
l_string|&quot;READ REVERSE&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 0Fh */
l_string|&quot;WRITE FILEMARKS&bslash;0&bslash;02&quot;
l_string|&quot;&bslash;003SYNCRONIZE BUFFER&quot;
comma
multiline_comment|/* 10h */
l_string|&quot;SPACE(6)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 11h */
l_string|&quot;INQUIRY&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 12h */
l_string|&quot;VERIFY&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 13h */
l_string|&quot;RECOVER BUFFERED DATA&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 14h */
l_string|&quot;MODE SELECT(06)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 15h */
l_string|&quot;RESERVE(06)&bslash;0&bslash;02&quot;
l_string|&quot;&bslash;010RESERVE ELEMENT(06)&quot;
comma
multiline_comment|/* 16h */
l_string|&quot;RELEASE(06)&bslash;0&bslash;02&quot;
l_string|&quot;&bslash;010RELEASE ELEMENT(06)&quot;
comma
multiline_comment|/* 17h */
l_string|&quot;COPY&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 18h */
l_string|&quot;ERASE&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 19h */
l_string|&quot;MODE SENSE(06)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 1Ah */
l_string|&quot;STOP START UNIT&bslash;0&bslash;04&quot;
l_string|&quot;&bslash;001LOAD UNLOAD&bslash;0&quot;
l_string|&quot;&bslash;002STOP PRINT&bslash;0&quot;
l_string|&quot;&bslash;006SCAN&bslash;0&bslash;002&quot;
comma
multiline_comment|/* 1Bh */
l_string|&quot;RECEIVE DIAGNOSTIC RESULTS&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 1Ch */
l_string|&quot;SEND DIAGNOSTIC&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 1Dh */
l_string|&quot;PREVENT ALLOW MEDIUM REMOVAL&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 1Eh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 1Fh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 20h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 21h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 22h */
l_string|&quot;READ FORMAT CAPACITIES&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 23h */
l_string|&quot;SET WINDOW&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 24h */
l_string|&quot;READ CAPACITY&bslash;0&bslash;03&quot;
l_string|&quot;&bslash;006GET WINDOW&bslash;0&quot;
l_string|&quot;&bslash;037FREAD CARD CAPACITY&quot;
comma
multiline_comment|/* 25h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 26h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 27h */
l_string|&quot;READ(10)&bslash;0&bslash;02&quot;
l_string|&quot;&bslash;011GET MESSAGE(10)&quot;
comma
multiline_comment|/* 28h */
l_string|&quot;READ GENERATION&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 29h */
l_string|&quot;WRITE(10)&bslash;0&bslash;03&quot;
l_string|&quot;&bslash;011SEND(10)&bslash;0&quot;
l_string|&quot;&bslash;011SEND MESSAGE(10)&quot;
comma
multiline_comment|/* 2Ah */
l_string|&quot;SEEK(10)&bslash;0&bslash;03&quot;
l_string|&quot;LOCATE(10)&bslash;0&quot;
l_string|&quot;POSITION TO ELEMENT&quot;
comma
multiline_comment|/* 2Bh */
l_string|&quot;ERASE(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 2Ch */
l_string|&quot;READ UPDATED BLOCK&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 2Dh */
l_string|&quot;WRITE AND VERIFY(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 2Eh */
l_string|&quot;VERIFY(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 2Fh */
l_string|&quot;SEARCH DATA HIGH(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 30h */
l_string|&quot;SEARCH DATA EQUAL(10)&bslash;0&bslash;02&quot;
l_string|&quot;OBJECT POSITION&quot;
comma
multiline_comment|/* 31h */
l_string|&quot;SEARCH DATA LOW(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 32h */
l_string|&quot;SET LIMITS(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 33h */
l_string|&quot;PRE-FETCH(10)&bslash;0&bslash;03&quot;
l_string|&quot;READ POSITION&bslash;0&quot;
l_string|&quot;GET DATA BUFFER STATUS&quot;
comma
multiline_comment|/* 34h */
l_string|&quot;SYNCHRONIZE CACHE(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 35h */
l_string|&quot;LOCK UNLOCK CACHE(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 36h */
l_string|&quot;READ DEFECT DATA(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 37h */
l_string|&quot;MEDIUM SCAN&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 38h */
l_string|&quot;COMPARE&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 39h */
l_string|&quot;COPY AND VERIFY&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 3Ah */
l_string|&quot;WRITE BUFFER&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 3Bh */
l_string|&quot;READ BUFFER&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 3Ch */
l_string|&quot;UPDATE BLOCK&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 3Dh */
l_string|&quot;READ LONG&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 3Eh */
l_string|&quot;WRITE LONG&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 3Fh */
l_string|&quot;CHANGE DEFINITION&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 40h */
l_string|&quot;WRITE SAME(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 41h */
l_string|&quot;READ SUB-CHANNEL&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 42h */
l_string|&quot;READ TOC/PMA/ATIP&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 43h */
l_string|&quot;REPORT DENSITY SUPPORT&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 44h */
l_string|&quot;READ HEADER&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 44h */
l_string|&quot;PLAY AUDIO(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 45h */
l_string|&quot;GET CONFIGURATION&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 46h */
l_string|&quot;PLAY AUDIO MSF&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 47h */
l_string|&quot;PLAY AUDIO TRACK INDEX&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 48h */
l_string|&quot;PLAY TRACK RELATIVE(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 49h */
l_string|&quot;GET EVENT STATUS NOTIFICATION&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 4Ah */
l_string|&quot;PAUSE/RESUME&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 4Bh */
l_string|&quot;LOG SELECT&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 4Ch */
l_string|&quot;LOG SENSE&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 4Dh */
l_string|&quot;STOP PLAY/SCAN&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 4Eh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 4Fh */
l_string|&quot;XDWRITE(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 50h */
l_string|&quot;XPWRITE(10)&bslash;0&bslash;02&quot;
l_string|&quot;READ DISC INFORMATION&quot;
comma
multiline_comment|/* 51h */
l_string|&quot;XDREAD(10)&bslash;0&bslash;01&quot;
l_string|&quot;READ TRACK INFORMATION&quot;
comma
multiline_comment|/* 52h */
l_string|&quot;RESERVE TRACK&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 53h */
l_string|&quot;SEND OPC INFORMATION&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 54h */
l_string|&quot;MODE SELECT(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 55h */
l_string|&quot;RESERVE(10)&bslash;0&bslash;02&quot;
l_string|&quot;RESERVE ELEMENT(10)&quot;
comma
multiline_comment|/* 56h */
l_string|&quot;RELEASE(10)&bslash;0&bslash;02&quot;
l_string|&quot;RELEASE ELEMENT(10)&quot;
comma
multiline_comment|/* 57h */
l_string|&quot;REPAIR TRACK&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 58h */
l_string|&quot;READ MASTER CUE&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 59h */
l_string|&quot;MODE SENSE(10)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 5Ah */
l_string|&quot;CLOSE TRACK/SESSION&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 5Bh */
l_string|&quot;READ BUFFER CAPACITY&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 5Ch */
l_string|&quot;SEND CUE SHEET&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 5Dh */
l_string|&quot;PERSISTENT RESERVE IN&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 5Eh */
l_string|&quot;PERSISTENT RESERVE OUT&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 5Fh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 60h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 61h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 62h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 63h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 64h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 65h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 66h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 67h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 68h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 69h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 6Ah */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 6Bh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 6Ch */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 6Dh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 6Eh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 6Fh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 70h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 71h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 72h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 73h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 74h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 75h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 76h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 77h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 78h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 79h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 7Ah */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 7Bh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 7Ch */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 7Eh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 7Eh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 7Fh */
l_string|&quot;XDWRITE EXTENDED(16)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 80h */
l_string|&quot;REBUILD(16)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 81h */
l_string|&quot;REGENERATE(16)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 82h */
l_string|&quot;EXTENDED COPY&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 83h */
l_string|&quot;RECEIVE COPY RESULTS&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 84h */
l_string|&quot;ACCESS CONTROL IN  [proposed]&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 86h */
l_string|&quot;ACCESS CONTROL OUT  [proposed]&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 87h */
l_string|&quot;READ(16)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 88h */
l_string|&quot;DEVICE LOCKS  [proposed]&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 89h */
l_string|&quot;WRITE(16)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 8Ah */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 8Bh */
l_string|&quot;READ ATTRIBUTES [proposed]&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 8Ch */
l_string|&quot;WRITE ATTRIBUTES [proposed]&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 8Dh */
l_string|&quot;WRITE AND VERIFY(16)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 8Eh */
l_string|&quot;VERIFY(16)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 8Fh */
l_string|&quot;PRE-FETCH(16)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 90h */
l_string|&quot;SYNCHRONIZE CACHE(16)&bslash;0&bslash;02&quot;
l_string|&quot;SPACE(16) [1]&quot;
comma
multiline_comment|/* 91h */
l_string|&quot;LOCK UNLOCK CACHE(16)&bslash;0&bslash;02&quot;
l_string|&quot;LOCATE(16) [1]&quot;
comma
multiline_comment|/* 92h */
l_string|&quot;WRITE SAME(16)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 93h */
l_string|&quot;[usage proposed by SCSI Socket Services project]&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 94h */
l_string|&quot;[usage proposed by SCSI Socket Services project]&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 95h */
l_string|&quot;[usage proposed by SCSI Socket Services project]&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 96h */
l_string|&quot;[usage proposed by SCSI Socket Services project]&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 97h */
l_string|&quot;MARGIN CONTROL [proposed]&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 98h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 99h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 9Ah */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 9Bh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 9Ch */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* 9Dh */
l_string|&quot;SERVICE ACTION IN [proposed]&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 9Eh */
l_string|&quot;SERVICE ACTION OUT [proposed]&bslash;0&bslash;01&quot;
comma
multiline_comment|/* 9Fh */
l_string|&quot;REPORT LUNS&bslash;0&bslash;01&quot;
comma
multiline_comment|/* A0h */
l_string|&quot;BLANK&bslash;0&bslash;01&quot;
comma
multiline_comment|/* A1h */
l_string|&quot;SEND EVENT&bslash;0&bslash;01&quot;
comma
multiline_comment|/* A2h */
l_string|&quot;MAINTENANCE (IN)&bslash;0&bslash;02&quot;
l_string|&quot;SEND KEY&quot;
comma
multiline_comment|/* A3h */
l_string|&quot;MAINTENANCE (OUT)&bslash;0&bslash;02&quot;
l_string|&quot;REPORT KEY&quot;
comma
multiline_comment|/* A4h */
l_string|&quot;MOVE MEDIUM&bslash;0&bslash;02&quot;
l_string|&quot;PLAY AUDIO(12)&quot;
comma
multiline_comment|/* A5h */
l_string|&quot;EXCHANGE MEDIUM&bslash;0&bslash;02&quot;
l_string|&quot;LOAD/UNLOAD C/DVD&quot;
comma
multiline_comment|/* A6h */
l_string|&quot;MOVE MEDIUM ATTACHED&bslash;0&bslash;02&quot;
l_string|&quot;SET READ AHEAD&bslash;0&bslash;01&quot;
comma
multiline_comment|/* A7h */
l_string|&quot;READ(12)&bslash;0&bslash;02&quot;
l_string|&quot;GET MESSAGE(12)&quot;
comma
multiline_comment|/* A8h */
l_string|&quot;PLAY TRACK RELATIVE(12)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* A9h */
l_string|&quot;WRITE(12)&bslash;0&bslash;02&quot;
l_string|&quot;SEND MESSAGE(12)&quot;
comma
multiline_comment|/* AAh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* ABh */
l_string|&quot;ERASE(12)&bslash;0&bslash;02&quot;
l_string|&quot;GET PERFORMANCE&quot;
comma
multiline_comment|/* ACh */
l_string|&quot;READ DVD STRUCTURE&bslash;0&bslash;01&quot;
comma
multiline_comment|/* ADh */
l_string|&quot;WRITE AND VERIFY(12)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* AEh */
l_string|&quot;VERIFY(12)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* AFh */
l_string|&quot;SEARCH DATA HIGH(12)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* B0h */
l_string|&quot;SEARCH DATA EQUAL(12)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* B1h */
l_string|&quot;SEARCH DATA LOW(12)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* B2h */
l_string|&quot;SET LIMITS(12)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* B3h */
l_string|&quot;READ ELEMENT STATUS ATTACHED&bslash;0&bslash;01&quot;
comma
multiline_comment|/* B4h */
l_string|&quot;REQUEST VOLUME ELEMENT ADDRESS&bslash;0&bslash;01&quot;
comma
multiline_comment|/* B5h */
l_string|&quot;SEND VOLUME TAG&bslash;0&bslash;02&quot;
l_string|&quot;SET STREAMING&quot;
comma
multiline_comment|/* B6h */
l_string|&quot;READ DEFECT DATA(12)&bslash;0&bslash;01&quot;
comma
multiline_comment|/* B7h */
l_string|&quot;READ ELEMENT STATUS&bslash;0&bslash;01&quot;
comma
multiline_comment|/* B8h */
l_string|&quot;READ CD MSF&bslash;0&bslash;01&quot;
comma
multiline_comment|/* B9h */
l_string|&quot;REDUNDANCY GROUP (IN)&bslash;0&bslash;02&quot;
l_string|&quot;SCAN&quot;
comma
multiline_comment|/* BAh */
l_string|&quot;REDUNDANCY GROUP (OUT)&bslash;0&bslash;02&quot;
l_string|&quot;SET CD-ROM SPEED&quot;
comma
multiline_comment|/* BBh */
l_string|&quot;SPARE (IN)&bslash;0&bslash;02&quot;
l_string|&quot;PLAY CD&quot;
comma
multiline_comment|/* BCh */
l_string|&quot;SPARE (OUT)&bslash;0&bslash;02&quot;
l_string|&quot;MECHANISM STATUS&quot;
comma
multiline_comment|/* BDh */
l_string|&quot;VOLUME SET (IN)&bslash;0&bslash;02&quot;
l_string|&quot;READ CD&quot;
comma
multiline_comment|/* BEh */
l_string|&quot;VOLUME SET (OUT)&bslash;0&bslash;0&bslash;02&quot;
l_string|&quot;SEND DVD STRUCTURE&quot;
comma
multiline_comment|/* BFh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* C0h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* C1h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* C2h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* C3h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* C4h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* C5h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* C6h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* C7h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* C8h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* C9h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* CAh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* CBh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* CCh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* CDh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* CEh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* CFh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* D0h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* D1h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* D2h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* D3h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* D4h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* D5h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* D6h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* D7h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* D8h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* D9h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* DAh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* DBh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* DCh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* DEh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* DEh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* DFh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* E0h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* E1h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* E2h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* E3h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* E4h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* E5h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* E6h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* E7h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* E8h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* E9h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* EAh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* EBh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* ECh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* EDh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* EEh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* EFh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* F0h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* F1h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* F2h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* F3h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* F4h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* F5h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* F6h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* F7h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* F8h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* F9h */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* FAh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* FBh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* FEh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* FEh */
l_string|&quot;&bslash;0&bslash;0&quot;
comma
multiline_comment|/* FEh */
l_string|&quot;&bslash;0&bslash;0&quot;
multiline_comment|/* FFh */
)brace
suffix:semicolon
eof
