/* This file is part of TeamListFiller

Copyright (C) 2017 Bernardo Giordano
	 
>    This program is free software: you can redistribute it and/or modify
>    it under the terms of the GNU General Public License as published by
>    the Free Software Foundation, either version 3 of the License, or
>    (at your option) any later version.
>
>    This program is distributed in the hope that it will be useful,
>    but WITHOUT ANY WARRANTY; without even the implied warranty of
>    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
>    GNU General Public License for more details.
>
>    You should have received a copy of the GNU General Public License
>    along with this program.  If not, see <http://www.gnu.org/licenses/>.
>    See LICENSE for information.
*/

#include <3ds.h>
#include <string.h>
#include "graphic.h"
#include "editor.h"
#include "util.h"

u32 expTable[100][6] = {
  {0, 0, 0, 0, 0, 0},
  {8, 15, 4, 9, 6, 10},
  {27, 52, 13, 57, 21, 33},
  {64, 122, 32, 96, 51, 80},
  {125, 237, 65, 135, 100, 156},
  {216, 406, 112, 179, 172, 270},
  {343, 637, 178, 236, 274, 428},
  {512, 942, 276, 314, 409, 640},
  {729, 1326, 393, 419, 583, 911},
  {1000, 1800, 540, 560, 800, 1250},
  {1331, 2369, 745, 742, 1064, 1663},
  {1728, 3041, 967, 973, 1382, 2160},
  {2197, 3822, 1230, 1261, 1757, 2746},
  {2744, 4719, 1591, 1612, 2195, 3430},
  {3375, 5737, 1957, 2035, 2700, 4218},
  {4096, 6881, 2457, 2535, 3276, 5120},
  {4913, 8155, 3046, 3120, 3930, 6141},
  {5832, 9564, 3732, 3798, 4665, 7290},
  {6859, 11111, 4526, 4575, 5487, 8573},
  {8000, 12800, 5440, 5460, 6400, 10000},
  {9261, 14632, 6482, 6458, 7408, 11576},
  {10648, 16610, 7666, 7577, 8518, 13310},
  {12167, 18737, 9003, 8825, 9733, 15208},
  {13824, 21012, 10506, 10208, 11059, 17280},
  {15625, 23437, 12187, 11735, 12500, 19531},
  {17576, 26012, 14060, 13411, 14060, 21970},
  {19683, 28737, 16140, 15244, 15746, 24603},
  {21952, 31610, 18439, 17242, 17561, 27440},
  {24389, 34632, 20974, 19411, 19511, 30486},
  {27000, 37800, 23760, 21760, 21600, 33750},
  {29791, 41111, 26811, 24294, 23832, 37238},
  {32768, 44564, 30146, 27021, 26214, 40960},
  {35937, 48155, 33780, 29949, 28749, 44921},
  {39304, 51881, 37731, 33084, 31443, 49130},
  {42875, 55737, 42017, 36435, 34300, 53593},
  {46656, 59719, 46656, 40007, 37324, 58320},
  {50653, 63822, 50653, 43808, 40522, 63316},
  {54872, 68041, 55969, 47846, 43897, 68590},
  {59319, 72369, 60505, 52127, 47455, 74148},
  {64000, 76800, 66560, 56660, 51200, 80000},
  {68921, 81326, 71677, 61450, 55136, 86151},
  {74088, 85942, 78533, 66505, 59270, 92610},
  {79507, 90637, 84277, 71833, 63605, 99383},
  {85184, 95406, 91998, 77440, 68147, 106480},
  {91125, 100237, 98415, 83335, 72900, 113906},
  {97336, 105122, 107069, 89523, 77868, 121670},
  {103823, 110052, 114205, 96012, 83058, 129778},
  {110592, 115015, 123863, 102810, 88473, 138240},
  {117649, 120001, 131766, 109923, 94119, 147061},
  {125000, 125000, 142500, 117360, 100000, 156250},
  {132651, 131324, 151222, 125126, 106120, 165813},
  {140608, 137795, 163105, 133229, 112486, 175760},
  {148877, 144410, 172697, 141677, 119101, 186096},
  {157464, 151165, 185807, 150476, 125971, 196830},
  {166375, 158056, 196322, 159635, 133100, 207968},
  {175616, 165079, 210739, 169159, 140492, 219520},
  {185193, 172229, 222231, 179056, 148154, 231491},
  {195112, 179503, 238036, 189334, 156089, 243890},
  {205379, 186894, 250562, 199999, 164303, 256723},
  {216000, 194400, 267840, 211060, 172800, 270000},
  {226981, 202013, 281456, 222522, 181584, 283726},
  {238328, 209728, 300293, 234393, 190662, 297910},
  {250047, 217540, 315059, 246681, 200037, 312558},
  {262144, 225443, 335544, 259392, 209715, 327680},
  {274625, 233431, 351520, 272535, 219700, 343281},
  {287496, 241496, 373744, 286115, 229996, 359370},
  {300763, 249633, 390991, 300140, 240610, 375953},
  {314432, 257834, 415050, 314618, 251545, 393040},
  {328509, 267406, 433631, 329555, 262807, 410636},
  {343000, 276458, 459620, 344960, 274400, 428750},
  {357911, 286328, 479600, 360838, 286328, 447388},
  {373248, 296358, 507617, 377197, 298598, 466560},
  {389017, 305767, 529063, 394045, 311213, 486271},
  {405224, 316074, 559209, 411388, 324179, 506530},
  {421875, 326531, 582187, 429235, 337500, 527343},
  {438976, 336255, 614566, 447591, 351180, 548720},
  {456533, 346965, 639146, 466464, 365226, 570666},
  {474552, 357812, 673863, 485862, 379641, 593190},
  {493039, 367807, 700115, 505791, 394431, 616298},
  {512000, 378880, 737280, 526260, 409600, 640000},
  {531441, 390077, 765275, 547274, 425152, 664301},
  {551368, 400293, 804997, 568841, 441094, 689210},
  {571787, 411686, 834809, 590969, 457429, 714733},
  {592704, 423190, 877201, 613664, 474163, 740880},
  {614125, 433572, 908905, 636935, 491300, 767656},
  {636056, 445239, 954084, 660787, 508844, 795070},
  {658503, 457001, 987754, 685228, 526802, 823128},
  {681472, 467489, 1035837, 710266, 545177, 851840},
  {704969, 479378, 1071552, 735907, 563975, 881211},
  {729000, 491346, 1122660, 762160, 583200, 911250},
  {753571, 501878, 1160499, 789030, 602856, 941963},
  {778688, 513934, 1214753, 816525, 622950, 973360},
  {804357, 526049, 1254796, 844653, 643485, 1005446},
  {830584, 536557, 1312322, 873420, 664467, 1038230},
  {857375, 548720, 1354652, 902835, 685900, 1071718},
  {884736, 560922, 1415577, 932903, 707788, 1105920},
  {912673, 571333, 1460276, 963632, 730138, 1140841},
  {941192, 583539, 1524731, 995030, 752953, 1176490},
  {970299, 591882, 1571884, 1027103, 776239, 1212873},
  {1000000, 600000, 1640000, 1059860, 800000, 1250000}
};

u32 seedStep(const u32 seed) { return (seed * 0x41C64E6D + 0x00006073) & 0xFFFFFFFF; }

void shuffleArray(u8* pkmn, const u32 encryptionkey) {
    const int BLOCKLENGHT = 56;

    u8 seed = (((encryptionkey & 0x3E000) >> 0xD) % 24);

    int aloc[24] = { 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3 };
    int bloc[24] = { 1, 1, 2, 3, 2, 3, 0, 0, 0, 0, 0, 0, 2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2 };
    int cloc[24] = { 2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2, 0, 0, 0, 0, 0, 0, 3, 2, 3, 2, 1, 1 };
    int dloc[24] = { 3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0 };
    int ord[4] = {aloc[seed], bloc[seed], cloc[seed], dloc[seed]};

    char pkmncpy[PKMNLENGTH];
    char tmp[BLOCKLENGHT];

    memcpy(&pkmncpy, pkmn, PKMNLENGTH);

    for (int i = 0; i < 4; i++) {
        memcpy(tmp, pkmncpy + 8 + BLOCKLENGHT * ord[i], BLOCKLENGHT);
        memcpy(pkmn + 8 + BLOCKLENGHT * i, tmp, BLOCKLENGHT);
    }
}

void decryptPkmn(u8* pkmn) {
    const int ENCRYPTIONKEYPOS = 0x0;
    const int ENCRYPTIONKEYLENGHT = 4;
    const int CRYPTEDAREAPOS = 0x08;

    u32 encryptionkey;
    memcpy(&encryptionkey, &pkmn[ENCRYPTIONKEYPOS], ENCRYPTIONKEYLENGHT);
    u32 seed = encryptionkey;

    u16 temp;
    for (int i = CRYPTEDAREAPOS; i < PKMNLENGTH; i += 2) {
        memcpy(&temp, &pkmn[i], 2);
        temp ^= (seedStep(seed) >> 16);
        seed = seedStep(seed);
        memcpy(&pkmn[i], &temp, 2);
    }

    shuffleArray(pkmn, encryptionkey);
}

int getPkmnAddress(const int boxnumber, const int indexnumber) {
    int boxpos = 0x04E00;
	return boxpos + (PKMNLENGTH * 30 * boxnumber) + (indexnumber * PKMNLENGTH);
}

void getPkmn(u8* mainbuf, const int boxnumber, const int indexnumber, u8* pkmn) {
    memcpy(pkmn, &mainbuf[getPkmnAddress(boxnumber, indexnumber)], PKMNLENGTH);
    decryptPkmn(pkmn);
}

int lookupHT[] = {0, 1, 2, 5, 3, 4};

u8 getGender(u8* pkmn) { return ((*(u8*)(pkmn + 0x1D)) >> 1) & 0x3; }
u8 getAbility(u8* pkmn) { return *(u8*)(pkmn + 0x14); }
u8 getHT(u8* pkmn) { return *(u8*)(pkmn + 0xDE); }
u8 getForm(u8* pkmn) { return ((*(u8*)(pkmn + 0x1D)) >> 3); }
u16 getItem(u8* pkmn) { return *(u16*)(pkmn + 0x0A); }
u8 getHPType(u8* pkmn) { return 15 * ((getIV(pkmn, 0) & 1) + 2 * (getIV(pkmn, 1) & 1) + 4 * (getIV(pkmn, 2) & 1) + 8 * (getIV(pkmn, 3) & 1) + 16 * (getIV(pkmn, 4) & 1) + 32 * (getIV(pkmn, 5) & 1)) / 63; }

u16 getStat(u8* pkmn, const int stat) {
    u16 tempspecies = getPokedexNumber(pkmn);
    if (getForm(pkmn))
		memcpy(&tempspecies, &personal.pkmData[getPokedexNumber(pkmn)][0x1C], 2);

    u8 mult = 10;
    u16 final;
    u8 basestat = 0;
    if (stat == 0) basestat = personal.pkmData[tempspecies][0x0];
    if (stat == 1) basestat = personal.pkmData[tempspecies][0x1];
    if (stat == 2) basestat = personal.pkmData[tempspecies][0x2];
    if (stat == 3) basestat = personal.pkmData[tempspecies][0x3];
    if (stat == 4) basestat = personal.pkmData[tempspecies][0x4];
    if (stat == 5) basestat = personal.pkmData[tempspecies][0x5];
    
    if (stat == 0)
        final = 10 + ((2 * basestat) + ((((getHT(pkmn) >> lookupHT[stat]) & 1) == 1) ? 31 : getIV(pkmn, stat)) + getEV(pkmn, stat) / 4 + 100) * getLevel(pkmn) / 100;
    else
        final = 5 + (2 * basestat + ((((getHT(pkmn) >> lookupHT[stat]) & 1) == 1) ? 31 : getIV(pkmn, stat)) + getEV(pkmn, stat) / 4) * getLevel(pkmn) / 100; 
    
    if (getNature(pkmn) / 5 + 1 == stat)
        mult++;
    if (getNature(pkmn) % 5 + 1 == stat)
        mult--;
  
    final = final * mult / 10;
    return final;
}

u8 getLevel(u8* pkmn) {
	u32 exp;
	u8 xpType = personal.pkmData[getPokedexNumber(pkmn)][0x15];
	u8 iterLevel = 1;
	memcpy(&exp, &pkmn[0x10], EXPPOINTLENGTH);

	while (iterLevel < 100 && exp >= expTable[iterLevel][xpType]) iterLevel++;
	return iterLevel;
}

u16 getMove(u8* pkmn, int nmove) {
    u16 movebuffer[4];
    memcpy(&movebuffer, &pkmn[0x5A], MOVELENGTH*4);
    return movebuffer[nmove];
}

u16 getPokedexNumber(u8* pkmn) {
    u16 pokedexnumber;
    memcpy(&pokedexnumber, &pkmn[0x08], POKEDEXNUMBERLENGTH);
    return pokedexnumber;
}

u8 getNature(u8* pkmn) {
    u8 nature;
    memcpy(&nature, &pkmn[0x1C], NATURELENGTH);
    return nature;
}

u8 getEV(u8* pkmn, const int stat) {
    u8 evbuffer[6];
    memcpy(evbuffer, &pkmn[0x1E], EVLENGTH * 6);
    return evbuffer[stat];
}

u8 getIV(u8* pkmn, const int stat) {
    u32 buffer;
    u8 toreturn;

    memcpy(&buffer, &pkmn[0x74], IVLENGTH);
    buffer = buffer >> 5 * stat;
    buffer = buffer & 0x1F;
    memcpy(&toreturn, &buffer, 1);
    return toreturn;
}