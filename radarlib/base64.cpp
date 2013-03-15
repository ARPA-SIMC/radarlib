/*
 * Radar Library
 *
 * Copyright (C) 2009-2010  ARPA-SIM <urpsim@smr.arpa.emr.it>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Author: Guido Billi <guidobilli@gmail.com>
 */

#include <radarlib/base64.hpp>

#include <sstream>
#include <string>
#include <stdexcept>

namespace Radar {

/*===========================================================================*/

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const unsigned char base64DecTable[] = {
    100,	//0
    100,	//1
    100,	//2
    100,	//3
    100,	//4
    100,	//5
    100,	//6
    100,	//7
    100,	//8
    100,	//9
    100,	//10
    100,	//11
    100,	//12
    100,	//13
    100,	//14
    100,	//15
    100,	//16
    100,	//17
    100,	//18
    100,	//19
    100,	//20
    100,	//21
    100,	//22
    100,	//23
    100,	//24
    100,	//25
    100,	//26
    100,	//27
    100,	//28
    100,	//29
    100,	//30
    100,	//31
    100,	//32
    100,	//33
    100,	//34
    100,	//35
    100,	//36
    100,	//37
    100,	//38
    100,	//39
    100,	//40
    100,	//41
    100,	//42
    62,	//43 +
    100,	//44 
    100,	//45
    100,	//46
    63,	//47 /
    52,	//48 0
    53,	//49 1
    54,	//50 2
    55,	//51 3
    56,	//52 4
    57,	//53 5
    58,	//54 6
    59,	//55 7
    60,	//56 8
    61,	//57 9
    100,	//58 
    100,	//59 
    100,	//60 
    100,	//61
    100,	//62
    100,	//63
    100,	//64
    0,	//65 A
    1,	//66 B
    2,	//67 C
    3,	//68 D
    4,	//69 E
    5,	//70 F
    6,	//71 G
    7,	//72 H
    8,	//73 I
    9,	//74 J
    10,	//75 K
    11,	//76 L
    12,	//77 M
    13,	//78 N
    14,	//79 O
    15,	//80 P
    16,	//81 Q
    17,	//82 R
    18,	//83 S
    19,	//84 T
    20,	//85 U
    21,	//86 V
    22,	//87 W
    23,	//88 X
    24,	//89 Y
    25,	//90 Z
    100,	//91
    100,	//92
    100,	//93
    100,	//94
    100,	//95
    100,	//96
    26,	//97 a
    27,	//98 b
    28,	//99 c
    29,	//100 d
    30,	//101 e
    31,	//102 f
    32,	//103 g
    33,	//104 h
    34,	//105 i
    35,	//106 j
    36,	//107 k
    37,	//108 l
    38,	//109 m
    39,	//110 n
    40,	//111 o
    41,	//112 p
    42,	//113 q
    43,	//114 r
    44,	//115 s
    45,	//116 t
    46,	//117 u
    47,	//118 v
    48,	//119 w
    49,	//120 x
    50,	//121 y
    51,	//122 z
    100,	//123
    100,	//124
    100,	//125
    100,	//126
    100,	//127
    100,	//128
    100,	//129
    100,	//130
    100,	//131
    100,	//132
    100,	//133
    100,	//134
    100,	//135
    100,	//136
    100,	//137
    100,	//138
    100,	//139
    100,	//140
    100,	//141
    100,	//142
    100,	//143
    100,	//144
    100,	//145
    100,	//146
    100,	//147
    100,	//148
    100,	//149
    100,	//150
    100,	//151
    100,	//152
    100,	//153
    100,	//154
    100,	//155
    100,	//156
    100,	//157
    100,	//158
    100,	//159
    100,	//160
    100,	//161
    100,	//162
    100,	//163
    100,	//164
    100,	//165
    100,	//166
    100,	//167
    100,	//168
    100,	//169
    100,	//170
    100,	//171
    100,	//172
    100,	//173
    100,	//174
    100,	//175
    100,	//176
    100,	//177
    100,	//178
    100,	//179
    100,	//180
    100,	//181
    100,	//182
    100,	//183
    100,	//184
    100,	//185
    100,	//186
    100,	//187
    100,	//188
    100,	//189
    100,	//190
    100,	//191
    100,	//192
    100,	//193
    100,	//194
    100,	//195
    100,	//196
    100,	//197
    100,	//198
    100,	//199
    100,	//200
    100,	//201
    100,	//202
    100,	//203
    100,	//204
    100,	//205
    100,	//206
    100,	//207
    100,	//208
    100,	//209
    100,	//210
    100,	//211
    100,	//212
    100,	//213
    100,	//214
    100,	//215
    100,	//216
    100,	//217
    100,	//218
    100,	//219
    100,	//220
    100,	//221
    100,	//222
    100,	//223
    100,	//224
    100,	//225
    100,	//226
    100,	//227
    100,	//228
    100,	//229
    100,	//230
    100,	//231
    100,	//232
    100,	//233
    100,	//234
    100,	//235
    100,	//236
    100,	//237
    100,	//238
    100,	//239
    100,	//240
    100,	//241
    100,	//242
    100,	//243
    100,	//244
    100,	//245
    100,	//246
    100,	//247
    100,	//248
    100,	//249
    100,	//250
    100,	//251
    100,	//252
    100,	//253
    100,	//254
    100	//255
    };

//static inline bool is_base64(unsigned char c) { return (isalnum(c) || (c == '+') || (c == '/')); }

/*===========================================================================*/

static void base64_encode(std::string& result, unsigned char const* bytes_to_encode, size_t in_len) 
{
    size_t			numblocks	= in_len / 3;
    const unsigned char*	src		= bytes_to_encode;

    for (size_t i=0; i<numblocks; i++)
    {		
        unsigned char s1 = *src;	src++;	
        unsigned char s2 = *src;	src++;	
        unsigned char s3 = *src;	src++;	

        unsigned char b1 =   s1 >> 2;
        unsigned char b2 = ((s1 & 0x03) << 4) | (s2 >> 4);
        unsigned char b3 = ((s2 & 0x0F) << 2) | (s3 >> 6);
        unsigned char b4 =  (s3 & 0x3F);

        result += base64_chars[b1];
        result += base64_chars[b2];
        result += base64_chars[b3];
        result += base64_chars[b4];
    }

    size_t resto	 = in_len % 3;

    if (resto == 1)
    {	
        unsigned char s1 = *src;	src++;
        unsigned char s2 = 0;		

        unsigned char b1 = s1 >> 2;
        unsigned char b2 = ((s1 & 0x03) << 4) | (s2 >> 4);

        result += base64_chars[b1];
        result += base64_chars[b2];
        result += "==";
    }
    else if (resto == 2)
    {	
        unsigned char s1 = *src;	src++;
        unsigned char s2 = *src;	src++;
        unsigned char s3 = 0;

        unsigned char b1 = s1 >> 2;
        unsigned char b2 = ((s1 & 0x03) << 4) | (s2 >> 4);
        unsigned char b3 = ((s2 & 0x0F) << 2) | (s3 >> 6);		

        result += base64_chars[b1];
        result += base64_chars[b2];
        result += base64_chars[b3];
        result += "=";
    }
}

static void b64decode(unsigned char* dst, unsigned char* src, size_t srcSize)
{
    if (srcSize < 4) throw std::logic_error("Base64 string '"+std::string((char*)src)+"' too short");

    size_t blocks = srcSize >> 2;	
    for (int i=0; blocks>1; blocks--, i++)
    {
        unsigned char b1 = base64DecTable[*src]; src++;
        unsigned char b2 = base64DecTable[*src]; src++;
        unsigned char b3 = base64DecTable[*src]; src++;
        unsigned char b4 = base64DecTable[*src]; src++;
        *dst = (b1 << 2) | (b2 >> 4);		dst++;
        *dst = (b2 << 4) | (b3 >> 2);		dst++;
        *dst = (b3 << 6) | b4;			dst++;
    }
    //ultimo blocco
    unsigned char b1 = base64DecTable[*src]; src++;
    unsigned char b2 = base64DecTable[*src]; src++;
    unsigned char b3 = base64DecTable[*src]; src++;
    unsigned char b4 = base64DecTable[*src]; src++;
    *dst = (b1 << 2) | (b2 >> 4);		dst++;
    if (b3==100) return;
    *dst = (b2 << 4) | (b3 >> 2);		dst++;
    if (b4==100) return;
    *dst = (b3 << 6) | b4;			dst++;
}


/*===========================================================================*/

size_t Base64::encodeSize(size_t uncodedSize)
{
    return ((uncodedSize + 2 - ((uncodedSize + 2) % 3)) / 3) << 2;
}

/*===========================================================================*/

void Base64::encode(std::string& b64str, const void* buff, size_t buffsize)
{
    base64_encode(b64str, (unsigned char*)buff, buffsize);
}

/*===========================================================================*/

size_t Base64::decodeSize(const std::string& b64str)
{
    size_t result = (b64str.size() >> 2) * 3;
    if (b64str.size() >= 4)
    {
        if (b64str[b64str.size()-1]=='=')  result--;
        if (b64str[b64str.size()-2]=='=')  result--;
    }
    return result;
}

/*===========================================================================*/

unsigned char*	Base64::decode(const std::string& b64str) 
{	
    size_t size = 0;
    return decode(b64str, &size);
}

unsigned char* Base64::decode(const std::string& b64str, size_t* resultSize)
{
    if (b64str.empty())	throw std::invalid_argument("Cannot decode base 64 string. String is empty");
    if (b64str.size() % 4)	throw std::invalid_argument("Cannot decode base 64 string. String is not multiple of 4 bytes");

    size_t size = decodeSize(b64str);
    unsigned char* result = new unsigned char[size];

    b64decode((unsigned char*)result, (unsigned char*)b64str.c_str(), b64str.size());

    *resultSize = size;	

    return result;
}

void Base64::decode(std::vector<unsigned char>& result, const std::string& b64str)
{
    if (b64str.empty())	throw std::invalid_argument("Cannot decode base 64 string. String is empty");
    if (b64str.size() % 4)	throw std::invalid_argument("Cannot decode base 64 string. String is not multiple of 4 bytes");

    size_t size = decodeSize(b64str);
    result.resize(size);

    b64decode((unsigned char*)&(result[0]), (unsigned char*)b64str.c_str(), b64str.size());	
}

/*===========================================================================*/

}













































































