multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|SNDRV_GF1_SCALE_TABLE_SIZE
mdefine_line|#define SNDRV_GF1_SCALE_TABLE_SIZE&t;128
DECL|macro|SNDRV_GF1_ATTEN_TABLE_SIZE
mdefine_line|#define SNDRV_GF1_ATTEN_TABLE_SIZE&t;128
macro_line|#ifdef __GUS_TABLES_ALLOC__
DECL|variable|snd_gf1_scale_table
r_int
r_int
id|snd_gf1_scale_table
(braket
id|SNDRV_GF1_SCALE_TABLE_SIZE
)braket
op_assign
(brace
l_int|8372
comma
l_int|8870
comma
l_int|9397
comma
l_int|9956
comma
l_int|10548
comma
l_int|11175
comma
l_int|11840
comma
l_int|12544
comma
l_int|13290
comma
l_int|14080
comma
l_int|14917
comma
l_int|15804
comma
l_int|16744
comma
l_int|17740
comma
l_int|18795
comma
l_int|19912
comma
l_int|21096
comma
l_int|22351
comma
l_int|23680
comma
l_int|25088
comma
l_int|26580
comma
l_int|28160
comma
l_int|29834
comma
l_int|31609
comma
l_int|33488
comma
l_int|35479
comma
l_int|37589
comma
l_int|39824
comma
l_int|42192
comma
l_int|44701
comma
l_int|47359
comma
l_int|50175
comma
l_int|53159
comma
l_int|56320
comma
l_int|59669
comma
l_int|63217
comma
l_int|66976
comma
l_int|70959
comma
l_int|75178
comma
l_int|79649
comma
l_int|84385
comma
l_int|89402
comma
l_int|94719
comma
l_int|100351
comma
l_int|106318
comma
l_int|112640
comma
l_int|119338
comma
l_int|126434
comma
l_int|133952
comma
l_int|141918
comma
l_int|150356
comma
l_int|159297
comma
l_int|168769
comma
l_int|178805
comma
l_int|189437
comma
l_int|200702
comma
l_int|212636
comma
l_int|225280
comma
l_int|238676
comma
l_int|252868
comma
l_int|267905
comma
l_int|283835
comma
l_int|300713
comma
l_int|318594
comma
l_int|337539
comma
l_int|357610
comma
l_int|378874
comma
l_int|401403
comma
l_int|425272
comma
l_int|450560
comma
l_int|477352
comma
l_int|505737
comma
l_int|535809
comma
l_int|567670
comma
l_int|601425
comma
l_int|637188
comma
l_int|675077
comma
l_int|715219
comma
l_int|757749
comma
l_int|802807
comma
l_int|850544
comma
l_int|901120
comma
l_int|954703
comma
l_int|1011473
comma
l_int|1071618
comma
l_int|1135340
comma
l_int|1202851
comma
l_int|1274376
comma
l_int|1350154
comma
l_int|1430439
comma
l_int|1515497
comma
l_int|1605613
comma
l_int|1701088
comma
l_int|1802240
comma
l_int|1909407
comma
l_int|2022946
comma
l_int|2143237
comma
l_int|2270680
comma
l_int|2405702
comma
l_int|2548752
comma
l_int|2700309
comma
l_int|2860878
comma
l_int|3030994
comma
l_int|3211227
comma
l_int|3402176
comma
l_int|3604480
comma
l_int|3818814
comma
l_int|4045892
comma
l_int|4286473
comma
l_int|4541360
comma
l_int|4811404
comma
l_int|5097505
comma
l_int|5400618
comma
l_int|5721755
comma
l_int|6061989
comma
l_int|6422453
comma
l_int|6804352
comma
l_int|7208960
comma
l_int|7637627
comma
l_int|8091784
comma
l_int|8572947
comma
l_int|9082720
comma
l_int|9622807
comma
l_int|10195009
comma
l_int|10801236
comma
l_int|11443511
comma
l_int|12123977
comma
l_int|12844906
)brace
suffix:semicolon
DECL|variable|snd_gf1_atten_table
r_int
r_int
id|snd_gf1_atten_table
(braket
id|SNDRV_GF1_ATTEN_TABLE_SIZE
)braket
op_assign
(brace
l_int|4095
multiline_comment|/* 0   */
comma
l_int|1789
multiline_comment|/* 1   */
comma
l_int|1533
multiline_comment|/* 2   */
comma
l_int|1383
multiline_comment|/* 3   */
comma
l_int|1277
multiline_comment|/* 4   */
comma
l_int|1195
multiline_comment|/* 5   */
comma
l_int|1127
multiline_comment|/* 6   */
comma
l_int|1070
multiline_comment|/* 7   */
comma
l_int|1021
multiline_comment|/* 8   */
comma
l_int|978
multiline_comment|/* 9   */
comma
l_int|939
multiline_comment|/* 10  */
comma
l_int|903
multiline_comment|/* 11  */
comma
l_int|871
multiline_comment|/* 12  */
comma
l_int|842
multiline_comment|/* 13  */
comma
l_int|814
multiline_comment|/* 14  */
comma
l_int|789
multiline_comment|/* 15  */
comma
l_int|765
multiline_comment|/* 16  */
comma
l_int|743
multiline_comment|/* 17  */
comma
l_int|722
multiline_comment|/* 18  */
comma
l_int|702
multiline_comment|/* 19  */
comma
l_int|683
multiline_comment|/* 20  */
comma
l_int|665
multiline_comment|/* 21  */
comma
l_int|647
multiline_comment|/* 22  */
comma
l_int|631
multiline_comment|/* 23  */
comma
l_int|615
multiline_comment|/* 24  */
comma
l_int|600
multiline_comment|/* 25  */
comma
l_int|586
multiline_comment|/* 26  */
comma
l_int|572
multiline_comment|/* 27  */
comma
l_int|558
multiline_comment|/* 28  */
comma
l_int|545
multiline_comment|/* 29  */
comma
l_int|533
multiline_comment|/* 30  */
comma
l_int|521
multiline_comment|/* 31  */
comma
l_int|509
multiline_comment|/* 32  */
comma
l_int|498
multiline_comment|/* 33  */
comma
l_int|487
multiline_comment|/* 34  */
comma
l_int|476
multiline_comment|/* 35  */
comma
l_int|466
multiline_comment|/* 36  */
comma
l_int|455
multiline_comment|/* 37  */
comma
l_int|446
multiline_comment|/* 38  */
comma
l_int|436
multiline_comment|/* 39  */
comma
l_int|427
multiline_comment|/* 40  */
comma
l_int|418
multiline_comment|/* 41  */
comma
l_int|409
multiline_comment|/* 42  */
comma
l_int|400
multiline_comment|/* 43  */
comma
l_int|391
multiline_comment|/* 44  */
comma
l_int|383
multiline_comment|/* 45  */
comma
l_int|375
multiline_comment|/* 46  */
comma
l_int|367
multiline_comment|/* 47  */
comma
l_int|359
multiline_comment|/* 48  */
comma
l_int|352
multiline_comment|/* 49  */
comma
l_int|344
multiline_comment|/* 50  */
comma
l_int|337
multiline_comment|/* 51  */
comma
l_int|330
multiline_comment|/* 52  */
comma
l_int|323
multiline_comment|/* 53  */
comma
l_int|316
multiline_comment|/* 54  */
comma
l_int|309
multiline_comment|/* 55  */
comma
l_int|302
multiline_comment|/* 56  */
comma
l_int|296
multiline_comment|/* 57  */
comma
l_int|289
multiline_comment|/* 58  */
comma
l_int|283
multiline_comment|/* 59  */
comma
l_int|277
multiline_comment|/* 60  */
comma
l_int|271
multiline_comment|/* 61  */
comma
l_int|265
multiline_comment|/* 62  */
comma
l_int|259
multiline_comment|/* 63  */
comma
l_int|253
multiline_comment|/* 64  */
comma
l_int|247
multiline_comment|/* 65  */
comma
l_int|242
multiline_comment|/* 66  */
comma
l_int|236
multiline_comment|/* 67  */
comma
l_int|231
multiline_comment|/* 68  */
comma
l_int|225
multiline_comment|/* 69  */
comma
l_int|220
multiline_comment|/* 70  */
comma
l_int|215
multiline_comment|/* 71  */
comma
l_int|210
multiline_comment|/* 72  */
comma
l_int|205
multiline_comment|/* 73  */
comma
l_int|199
multiline_comment|/* 74  */
comma
l_int|195
multiline_comment|/* 75  */
comma
l_int|190
multiline_comment|/* 76  */
comma
l_int|185
multiline_comment|/* 77  */
comma
l_int|180
multiline_comment|/* 78  */
comma
l_int|175
multiline_comment|/* 79  */
comma
l_int|171
multiline_comment|/* 80  */
comma
l_int|166
multiline_comment|/* 81  */
comma
l_int|162
multiline_comment|/* 82  */
comma
l_int|157
multiline_comment|/* 83  */
comma
l_int|153
multiline_comment|/* 84  */
comma
l_int|148
multiline_comment|/* 85  */
comma
l_int|144
multiline_comment|/* 86  */
comma
l_int|140
multiline_comment|/* 87  */
comma
l_int|135
multiline_comment|/* 88  */
comma
l_int|131
multiline_comment|/* 89  */
comma
l_int|127
multiline_comment|/* 90  */
comma
l_int|123
multiline_comment|/* 91  */
comma
l_int|119
multiline_comment|/* 92  */
comma
l_int|115
multiline_comment|/* 93  */
comma
l_int|111
multiline_comment|/* 94  */
comma
l_int|107
multiline_comment|/* 95  */
comma
l_int|103
multiline_comment|/* 96  */
comma
l_int|100
multiline_comment|/* 97  */
comma
l_int|96
multiline_comment|/* 98  */
comma
l_int|92
multiline_comment|/* 99  */
comma
l_int|88
multiline_comment|/* 100 */
comma
l_int|85
multiline_comment|/* 101 */
comma
l_int|81
multiline_comment|/* 102 */
comma
l_int|77
multiline_comment|/* 103 */
comma
l_int|74
multiline_comment|/* 104 */
comma
l_int|70
multiline_comment|/* 105 */
comma
l_int|67
multiline_comment|/* 106 */
comma
l_int|63
multiline_comment|/* 107 */
comma
l_int|60
multiline_comment|/* 108 */
comma
l_int|56
multiline_comment|/* 109 */
comma
l_int|53
multiline_comment|/* 110 */
comma
l_int|50
multiline_comment|/* 111 */
comma
l_int|46
multiline_comment|/* 112 */
comma
l_int|43
multiline_comment|/* 113 */
comma
l_int|40
multiline_comment|/* 114 */
comma
l_int|37
multiline_comment|/* 115 */
comma
l_int|33
multiline_comment|/* 116 */
comma
l_int|30
multiline_comment|/* 117 */
comma
l_int|27
multiline_comment|/* 118 */
comma
l_int|24
multiline_comment|/* 119 */
comma
l_int|21
multiline_comment|/* 120 */
comma
l_int|18
multiline_comment|/* 121 */
comma
l_int|15
multiline_comment|/* 122 */
comma
l_int|12
multiline_comment|/* 123 */
comma
l_int|9
multiline_comment|/* 124 */
comma
l_int|6
multiline_comment|/* 125 */
comma
l_int|3
multiline_comment|/* 126 */
comma
l_int|0
multiline_comment|/* 127 */
comma
)brace
suffix:semicolon
macro_line|#else
r_extern
r_int
r_int
id|snd_gf1_scale_table
(braket
id|SNDRV_GF1_SCALE_TABLE_SIZE
)braket
suffix:semicolon
r_extern
r_int
r_int
id|snd_gf1_atten_table
(braket
id|SNDRV_GF1_ATTEN_TABLE_SIZE
)braket
suffix:semicolon
macro_line|#endif
eof
