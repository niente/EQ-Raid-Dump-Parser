# EQ-Raid-Dump-Parser
Reads in an EverQuest raid dump text file and parses it into bbcode formatted colored text, for web forums.

EQ directory path defined as: `C:\Users\Public\Daybreak Game Company\Installed Games\EverQuest`

Creates the following folder structure:
Raid Dumps\Pre-Processed\
Raid Dumps\Processed\

![Sample Image of Forum Post](https://github.com/niente/EQ-Raid-Dump-Parser/blob/master/sampleoutputRaidRoster.png)

Sample text file:
```
[b][u]Event[/b][/u] (46) + 2
1 [COLOR="Cyan"]CLR[/COLOR] Cookeez
1 [COLOR="Cyan"]CLR[/COLOR] Khalimari
1 [COLOR="Cyan"]CLR[/COLOR] Pixiepuffles
1 [COLOR="Yellow"]WAR[/COLOR] Croydan
1 [COLOR="Yellow"]WAR[/COLOR] Dereni
1 [COLOR="Yellow"]WAR[/COLOR] Ranonman

2 [COLOR="Cyan"]CLR[/COLOR] Dalef
2 [COLOR="Cyan"]CLR[/COLOR] Donaskz
2 [COLOR="Orange"]PAL[/COLOR] Tanksum
2 [COLOR="Orange"]SHD[/COLOR] Elnoche

3 [COLOR="Cyan"]CLR[/COLOR] Gryning
3 [COLOR="Cyan"]CLR[/COLOR] Jumvapace
3 [COLOR="Orange"]SHD[/COLOR] Nitsuj
3 [COLOR="Orange"]SHD[/COLOR] Zabasilarx
3 [COLOR="Yellow"]WAR[/COLOR] Slayum

4 [COLOR="White"]BRD[/COLOR] Sirenea
4 [COLOR="Lime"]BER[/COLOR] Rorcex
4 [COLOR="Lime"]MNK[/COLOR] Theriou
4 [COLOR="Lime"]ROG[/COLOR] Garwyn
4 [COLOR="Lime"]ROG[/COLOR] Zythaxx
4 [COLOR="Teal"]SHM[/COLOR] Spudly

5 [COLOR="White"]BRD[/COLOR] Clannus
5 [COLOR="Green"]BST[/COLOR] Razorbeast
5 [COLOR="Lime"]BER[/COLOR] Jaggax
5 [COLOR="Lime"]MNK[/COLOR] Ellir
5 [COLOR="Green"]RNG[/COLOR] Dartaniun
5 [COLOR="Teal"]SHM[/COLOR] Fenshar

6 [COLOR="White"]BRD[/COLOR] Baniana
6 [COLOR="Green"]BST[/COLOR] Gbath
6 [COLOR="Green"]RNG[/COLOR] Grogers
6 [COLOR="Green"]RNG[/COLOR] Signarius
6 [COLOR="Lime"]ROG[/COLOR] Favreon
6 [COLOR="Teal"]SHM[/COLOR] Shammanron

7 [COLOR="Teal"]DRU[/COLOR] Lujayne
7 [COLOR="DarkRed"]ENC[/COLOR] Greymask
7 [COLOR="Red"]MAG[/COLOR] Ryino
7 [COLOR="Purple"]NEC[/COLOR] Bonefork

8 [COLOR="Teal"]DRU[/COLOR] Glynna
8 [COLOR="Red"]WIZ[/COLOR] Dekabos
8 [COLOR="Red"]WIZ[/COLOR] Flametwister
8 [COLOR="Red"]WIZ[/COLOR] Seeringx

9 [COLOR="Teal"]DRU[/COLOR] Mileana
9 [COLOR="Teal"]DRU[/COLOR] Oread
9 [COLOR="DarkRed"]ENC[/COLOR] Samirah
9 [COLOR="Green"]RNG[/COLOR] Raswa
9 [COLOR="Green"]RNG[/COLOR] Tinyenea

0 [COLOR="Lime"]BER[/COLOR] Jaggax
0 [COLOR="Lime"]ROG[/COLOR] Spiffy
```
