xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 200;
 0.47287;0.26877;3.27781;,
 1.03191;0.36947;3.03671;,
 0.87773;0.90228;2.88733;,
 0.22580;0.18363;3.22388;,
 0.64924;0.01313;3.18380;,
 1.12523;-0.22627;3.08346;,
 0.60047;-0.28757;3.20559;,
 0.85169;-0.76252;3.13633;,
 0.38424;-0.50297;3.22446;,
 0.31250;-1.03575;3.15606;,
 0.08222;-0.55062;3.22860;,
 -0.28424;-0.94174;3.14631;,
 -0.19024;-0.41232;3.21651;,
 -0.68221;-0.52156;3.19416;,
 -0.32920;-0.14078;3.19431;,
 -0.80592;0.07838;3.05617;,
 -0.29048;0.15457;3.19790;,
 -0.47752;0.73790;3.05863;,
 -0.08447;0.47284;3.33245;,
 -0.21800;1.07574;2.87297;,
 0.28601;0.32867;3.30585;,
 1.00460;1.53872;2.47430;,
 0.38438;1.32313;2.75576;,
 1.57428;0.19184;2.94809;,
 1.50928;0.87484;2.66198;,
 1.42316;-0.68413;2.96798;,
 0.73607;-1.27385;3.28641;,
 0.08029;-1.56202;3.09389;,
 -0.85667;-1.10853;2.90281;,
 -1.23090;-0.32949;2.84928;,
 -1.12222;0.55402;2.76001;,
 -0.82110;1.24249;2.62975;,
 0.31253;0.88786;2.98549;,
 0.28601;0.32867;3.30585;,
 2.05299;-0.28727;2.81057;,
 2.11649;0.43010;2.53470;,
 1.44525;-1.38088;2.88205;,
 0.52431;-1.98688;2.69448;,
 -0.61503;-1.80553;2.75237;,
 -1.49668;-0.96584;2.55886;,
 -1.73955;0.12077;2.56068;,
 -1.45709;1.06864;2.30814;,
 -0.16927;1.65086;2.69636;,
 1.95004;1.44423;2.09176;,
 0.50962;2.04773;1.96834;,
 2.48436;-1.20550;2.47246;,
 2.58746;-0.06412;2.03122;,
 1.07013;-2.12151;2.27468;,
 -0.13315;-2.38277;2.21278;,
 -1.14121;-2.01802;2.35516;,
 -2.20580;-0.71272;2.62369;,
 -1.45996;-1.28042;2.81392;,
 -2.41601;0.41217;2.18124;,
 -0.77100;1.99545;2.05496;,
 1.30499;2.04449;1.63812;,
 -0.22968;2.38779;1.72023;,
 2.58579;0.91619;1.89538;,
 1.96149;-2.13993;1.85525;,
 2.48507;-1.09373;1.94809;,
 0.52228;-2.71425;1.92371;,
 -0.62992;-2.64905;1.90050;,
 -2.67879;-0.30801;1.73519;,
 -1.99693;-1.17531;2.12138;,
 -1.60586;1.69349;1.65146;,
 2.35241;1.86366;1.03674;,
 0.65660;2.51613;1.45490;,
 3.01982;0.26122;1.44366;,
 1.44253;-2.73258;1.57706;,
 2.55792;-1.97897;1.27776;,
 0.50741;-2.91739;1.69354;,
 -2.86576;-1.15400;1.24472;,
 -1.82645;-2.15832;1.49206;,
 -2.22230;1.19608;1.63496;,
 -1.06375;2.09011;1.25576;,
 1.79163;2.60499;0.47765;,
 -0.42590;3.01550;0.55102;,
 2.95314;1.04792;0.83431;,
 2.91152;-0.75372;0.96497;,
 1.10065;-3.14991;1.14276;,
 1.98784;-2.79154;0.86797;,
 -2.29209;-2.19631;0.84973;,
 -1.05181;-2.61951;1.21248;,
 -2.72813;0.62624;1.12972;,
 -1.98660;1.89794;0.71781;,
 2.39106;1.91335;0.21262;,
 0.68181;2.81539;-0.01130;,
 2.84736;0.21026;0.37591;,
 2.53052;-1.69059;0.54396;,
 -1.57161;-3.03298;0.70942;,
 -0.69840;-3.31233;0.42594;,
 -3.26184;-0.33620;0.67778;,
 -1.37905;2.73293;-0.11902;,
 -2.86308;1.00411;0.41756;,
 1.36655;2.72282;-0.57862;,
 -0.43283;2.96782;-0.57161;,
 3.00822;1.23344;-0.44720;,
 2.90771;-0.79629;0.05728;,
 2.37338;-2.54694;0.21847;,
 0.82617;-3.46165;0.65083;,
 0.27708;-3.40138;0.06668;,
 1.20507;-3.30254;-0.06381;,
 -3.20981;-1.22803;0.27154;,
 -1.98185;2.00632;-0.36204;,
 -3.35532;0.04281;-0.17564;,
 2.64745;1.87789;-0.80665;,
 0.45018;2.93639;-1.30648;,
 3.26471;0.01291;-0.45990;,
 2.94157;-1.76530;-0.30334;,
 2.14950;-2.94535;-0.85499;,
 -2.17970;-2.58300;0.19793;,
 -2.63109;-1.80281;-0.43316;,
 -1.62351;-2.74469;-0.64342;,
 -2.95580;0.97123;-0.76364;,
 -3.16594;-0.41708;-0.84427;,
 -0.95443;2.63816;-1.02355;,
 1.66972;2.23710;-1.35234;,
 -0.31656;2.60171;-1.48520;,
 2.80787;0.89204;-1.11210;,
 3.21306;-0.94297;-0.80518;,
 2.48888;-2.19269;-1.06024;,
 -0.44731;-3.44586;-0.27584;,
 -0.94518;-3.12013;-0.88742;,
 0.67595;-3.54159;-1.18779;,
 -2.73660;-1.37460;-0.99910;,
 -2.21586;-2.14383;-1.09503;,
 -2.02268;1.69884;-1.21239;,
 -2.66912;0.47530;-1.25387;,
 2.25447;1.53967;-1.78668;,
 0.64789;2.30487;-1.81499;,
 2.95033;-0.02479;-1.44030;,
 2.72724;-1.30977;-1.48238;,
 -0.32053;-2.96861;-1.69712;,
 0.68279;-3.25638;-1.39534;,
 -1.09832;2.03015;-1.70935;,
 -2.04465;1.11503;-1.86004;,
 1.39376;1.77346;-2.23374;,
 -0.18736;1.99632;-2.06840;,
 2.43123;0.64649;-2.06312;,
 2.59249;-0.53142;-2.16493;,
 1.73246;-2.66250;-1.47687;,
 -1.44573;-2.69705;-1.56883;,
 -2.55097;-0.80095;-1.41034;,
 -2.38654;-0.10884;-2.08765;,
 -2.04564;-1.55942;-1.77069;,
 -1.27195;1.43099;-2.34006;,
 1.78976;1.04053;-2.53061;,
 0.56926;1.66703;-2.64142;,
 2.10098;0.08431;-2.48237;,
 2.09775;-1.92624;-1.94907;,
 0.91109;-2.83710;-1.96321;,
 -0.85773;-2.53784;-2.18135;,
 0.15918;-2.63640;-2.34150;,
 -2.05591;-0.89857;-2.32754;,
 -1.53035;-1.78179;-2.36226;,
 -1.83595;0.47020;-2.38014;,
 -0.48569;1.41133;-2.69970;,
 1.00365;1.08497;-2.69037;,
 0.15962;1.29830;-2.84008;,
 1.50938;0.39447;-2.82828;,
 2.14099;-1.20616;-2.46915;,
 1.38191;-2.23215;-2.30852;,
 -0.94664;-2.08212;-2.41282;,
 -0.35702;-2.16627;-2.61151;,
 -1.65801;-0.28440;-2.47561;,
 -1.42672;-1.08384;-2.55929;,
 -1.15520;0.75068;-2.58856;,
 0.87809;0.39123;-2.99757;,
 0.38424;0.82469;-2.93130;,
 1.83214;-0.58845;-2.81518;,
 1.51040;-1.55474;-2.59365;,
 0.67684;-2.16830;-2.61496;,
 -1.12045;0.07412;-2.72163;,
 -1.06282;-0.58375;-2.76035;,
 -0.49280;0.69297;-2.84839;,
 0.15962;1.29830;-2.84008;,
 0.37451;0.09850;-3.00799;,
 0.00692;0.36995;-2.94374;,
 1.32260;-0.22021;-2.93881;,
 1.32205;-0.97307;-2.87185;,
 0.87910;-1.58501;-2.82486;,
 0.15961;-1.81534;-2.80111;,
 -0.85597;-1.59341;-2.64715;,
 -0.71146;-1.03450;-2.81649;,
 -0.28415;-1.45983;-2.77853;,
 -0.53365;0.09617;-2.92275;,
 -0.54732;-0.37610;-2.85331;,
 0.76350;-0.17360;-3.10294;,
 0.90546;-0.61043;-3.06203;,
 0.76407;-1.04834;-3.02906;,
 0.38744;-1.31611;-2.93921;,
 -0.19025;-0.95100;-2.94058;,
 0.08213;-1.08944;-2.92913;,
 -0.32913;-0.67962;-2.96460;,
 -0.06500;-0.16329;-3.00936;,
 -0.24562;-0.30913;-2.99641;,
 0.15931;-0.35467;-3.01527;,
 0.45404;-0.21140;-3.15078;,
 0.63600;-0.46090;-3.12896;,
 0.63600;-0.76930;-3.10198;,
 0.45404;-1.01878;-3.08016;;
 
 392;
 3;0,1,2;,
 3;3,4,0;,
 3;4,5,1;,
 3;3,6,4;,
 3;6,7,5;,
 3;3,8,6;,
 3;8,9,7;,
 3;3,10,8;,
 3;10,11,9;,
 3;3,12,10;,
 3;12,13,11;,
 3;3,14,12;,
 3;14,15,13;,
 3;3,16,14;,
 3;16,17,15;,
 3;3,18,16;,
 3;18,19,17;,
 3;3,20,18;,
 3;21,22,2;,
 3;1,23,24;,
 3;5,25,23;,
 3;7,26,25;,
 3;9,27,26;,
 3;11,28,27;,
 3;13,29,28;,
 3;15,30,29;,
 3;17,31,30;,
 3;32,33,3;,
 3;1,0,4;,
 3;2,1,24;,
 3;23,1,5;,
 3;5,4,6;,
 3;23,34,35;,
 3;7,6,8;,
 3;25,36,34;,
 3;9,8,10;,
 3;26,37,36;,
 3;11,10,12;,
 3;27,38,37;,
 3;13,12,14;,
 3;28,39,38;,
 3;15,14,16;,
 3;29,40,39;,
 3;17,16,18;,
 3;30,41,40;,
 3;2,22,32;,
 3;19,32,22;,
 3;22,21,42;,
 3;21,43,44;,
 3;24,23,35;,
 3;34,23,25;,
 3;25,5,7;,
 3;34,45,46;,
 3;26,7,9;,
 3;36,47,45;,
 3;27,9,11;,
 3;37,48,47;,
 3;28,11,13;,
 3;38,49,48;,
 3;29,13,15;,
 3;39,50,51;,
 3;30,15,17;,
 3;40,52,50;,
 3;19,31,17;,
 3;31,19,42;,
 3;42,19,22;,
 3;42,44,53;,
 3;44,54,55;,
 3;24,21,2;,
 3;43,56,54;,
 3;35,34,46;,
 3;45,34,36;,
 3;36,25,26;,
 3;45,57,58;,
 3;37,26,27;,
 3;47,59,57;,
 3;38,27,28;,
 3;48,60,59;,
 3;38,39,51;,
 3;39,28,29;,
 3;40,29,30;,
 3;50,61,62;,
 3;31,41,30;,
 3;41,31,53;,
 3;53,31,42;,
 3;53,55,63;,
 3;44,42,21;,
 3;43,21,24;,
 3;54,64,65;,
 3;35,43,24;,
 3;56,66,64;,
 3;46,45,58;,
 3;57,45,47;,
 3;47,36,37;,
 3;57,67,68;,
 3;48,37,38;,
 3;59,69,67;,
 3;50,39,40;,
 3;49,51,62;,
 3;62,51,50;,
 3;62,70,71;,
 3;41,52,40;,
 3;52,41,63;,
 3;52,63,72;,
 3;63,73,72;,
 3;54,44,43;,
 3;55,65,73;,
 3;65,74,75;,
 3;56,43,35;,
 3;64,76,74;,
 3;46,56,35;,
 3;66,77,76;,
 3;58,57,68;,
 3;67,57,59;,
 3;59,47,48;,
 3;67,78,79;,
 3;49,60,48;,
 3;60,49,71;,
 3;71,49,62;,
 3;71,80,81;,
 3;52,61,50;,
 3;61,52,82;,
 3;73,63,55;,
 3;63,41,53;,
 3;55,53,44;,
 3;73,75,83;,
 3;65,55,54;,
 3;64,54,56;,
 3;74,84,85;,
 3;66,56,46;,
 3;76,86,84;,
 3;58,66,46;,
 3;77,87,86;,
 3;68,67,79;,
 3;69,78,67;,
 3;60,69,59;,
 3;69,60,81;,
 3;81,60,71;,
 3;81,88,89;,
 3;61,70,62;,
 3;70,61,90;,
 3;82,90,61;,
 3;82,72,83;,
 3;83,72,73;,
 3;83,91,92;,
 3;74,65,64;,
 3;75,85,91;,
 3;85,93,94;,
 3;76,64,66;,
 3;84,95,93;,
 3;77,66,58;,
 3;86,96,95;,
 3;68,77,58;,
 3;87,97,96;,
 3;79,78,98;,
 3;98,78,69;,
 3;98,99,100;,
 3;70,80,71;,
 3;80,70,101;,
 3;90,101,70;,
 3;90,82,92;,
 3;92,82,83;,
 3;92,102,103;,
 3;75,73,65;,
 3;91,94,102;,
 3;85,75,74;,
 3;84,74,76;,
 3;93,104,105;,
 3;86,76,77;,
 3;95,106,104;,
 3;87,77,68;,
 3;96,107,106;,
 3;79,87,68;,
 3;97,108,107;,
 3;80,88,81;,
 3;89,88,109;,
 3;109,88,80;,
 3;109,110,111;,
 3;101,90,103;,
 3;103,90,92;,
 3;103,112,113;,
 3;91,83,75;,
 3;102,114,112;,
 3;93,85,84;,
 3;94,105,114;,
 3;105,115,116;,
 3;95,84,86;,
 3;104,117,115;,
 3;96,86,87;,
 3;106,118,117;,
 3;97,87,79;,
 3;107,119,118;,
 3;89,99,98;,
 3;100,99,120;,
 3;120,99,89;,
 3;120,121,122;,
 3;101,109,80;,
 3;110,123,124;,
 3;102,92,91;,
 3;112,125,126;,
 3;94,91,85;,
 3;114,116,125;,
 3;105,94,93;,
 3;104,93,95;,
 3;115,127,128;,
 3;106,95,96;,
 3;117,129,127;,
 3;107,96,97;,
 3;118,130,129;,
 3;100,108,97;,
 3;108,100,122;,
 3;122,100,120;,
 3;131,132,121;,
 3;110,109,101;,
 3;111,110,124;,
 3;113,123,110;,
 3;112,103,102;,
 3;113,112,126;,
 3;125,112,114;,
 3;114,102,94;,
 3;125,133,134;,
 3;115,105,104;,
 3;116,128,133;,
 3;128,135,136;,
 3;117,104,106;,
 3;127,137,135;,
 3;118,106,107;,
 3;129,138,137;,
 3;108,122,132;,
 3;119,108,139;,
 3;121,132,122;,
 3;108,119,107;,
 3;111,121,120;,
 3;121,111,140;,
 3;124,140,111;,
 3;124,123,141;,
 3;141,123,113;,
 3;141,142,143;,
 3;126,125,134;,
 3;133,125,116;,
 3;116,114,105;,
 3;133,136,144;,
 3;128,116,115;,
 3;127,115,117;,
 3;135,145,146;,
 3;129,117,118;,
 3;137,147,145;,
 3;119,130,118;,
 3;130,119,148;,
 3;139,148,119;,
 3;139,132,149;,
 3;132,131,149;,
 3;131,150,151;,
 3;140,124,143;,
 3;143,124,141;,
 3;143,152,153;,
 3;126,141,113;,
 3;142,154,152;,
 3;134,133,144;,
 3;136,133,128;,
 3;135,128,127;,
 3;136,146,155;,
 3;146,156,157;,
 3;137,127,129;,
 3;145,158,156;,
 3;130,138,129;,
 3;138,130,159;,
 3;148,159,130;,
 3;148,139,160;,
 3;149,160,139;,
 3;149,131,151;,
 3;150,131,140;,
 3;140,131,121;,
 3;150,161,162;,
 3;142,141,126;,
 3;152,163,164;,
 3;134,142,126;,
 3;154,165,163;,
 3;144,136,155;,
 3;156,146,145;,
 3;146,136,135;,
 3;145,135,137;,
 3;156,166,167;,
 3;138,147,137;,
 3;147,138,168;,
 3;159,168,138;,
 3;159,148,169;,
 3;160,169,148;,
 3;160,149,170;,
 3;151,170,149;,
 3;151,150,162;,
 3;153,161,150;,
 3;152,143,142;,
 3;153,152,164;,
 3;163,152,154;,
 3;154,142,134;,
 3;163,171,172;,
 3;144,154,134;,
 3;165,173,171;,
 3;155,146,174;,
 3;167,157,156;,
 3;167,175,176;,
 3;147,158,145;,
 3;158,147,177;,
 3;168,177,147;,
 3;168,159,178;,
 3;169,178,159;,
 3;169,160,179;,
 3;170,179,160;,
 3;170,151,180;,
 3;162,180,151;,
 3;162,161,181;,
 3;181,161,153;,
 3;181,182,183;,
 3;164,163,172;,
 3;171,163,165;,
 3;165,154,144;,
 3;171,184,185;,
 3;155,165,144;,
 3;173,176,184;,
 3;158,166,156;,
 3;166,158,186;,
 3;177,186,158;,
 3;177,168,187;,
 3;178,187,168;,
 3;178,169,188;,
 3;179,188,169;,
 3;179,170,189;,
 3;180,189,170;,
 3;180,162,183;,
 3;183,162,181;,
 3;183,190,191;,
 3;164,181,153;,
 3;182,192,190;,
 3;172,171,185;,
 3;184,171,173;,
 3;173,165,155;,
 3;184,193,194;,
 3;166,175,167;,
 3;176,195,193;,
 3;175,166,196;,
 3;186,196,166;,
 3;186,177,197;,
 3;187,197,177;,
 3;187,178,198;,
 3;188,198,178;,
 3;188,179,199;,
 3;189,199,179;,
 3;189,180,191;,
 3;191,180,183;,
 3;182,181,164;,
 3;172,182,164;,
 3;185,184,194;,
 3;193,184,176;,
 3;176,173,167;,
 3;175,195,176;,
 3;175,196,195;,
 3;196,186,195;,
 3;186,197,195;,
 3;197,187,195;,
 3;187,198,195;,
 3;198,188,195;,
 3;188,199,195;,
 3;199,189,195;,
 3;189,191,195;,
 3;190,183,182;,
 3;191,190,195;,
 3;192,182,172;,
 3;190,192,195;,
 3;185,192,172;,
 3;192,185,195;,
 3;185,194,195;,
 3;194,193,195;,
 3;38,51,49;,
 3;52,72,82;,
 3;108,132,139;,
 3;0,2,32;,
 3;0,32,3;,
 3;18,20,32;,
 3;18,32,19;,
 3;69,81,89;,
 3;69,89,98;,
 3;79,98,100;,
 3;79,100,97;,
 3;89,109,111;,
 3;89,111,120;,
 3;101,103,113;,
 3;101,113,110;,
 3;140,143,153;,
 3;140,153,150;,
 3;174,167,173;,
 3;174,173,155;;
 
 MeshMaterialList {
  7;
  392;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.300000;0.300000;0.300000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Foliage_PlainMossCover_2k_alb.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Rock_DarkCrackyStrata_2k_alb.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Rock_LayeredMetamorphic_2k_alb.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "Decal_SVGivy2_1k_d.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "8.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "11.png";
   }
  }
 }
 MeshNormals {
  209;
  -0.050113;-0.077839;0.995706;,
  -0.112789;-0.452987;0.884354;,
  0.106622;0.151018;0.982764;,
  0.192471;-0.049168;0.980070;,
  0.157908;0.003910;0.987446;,
  0.075284;-0.063444;0.995142;,
  -0.026831;-0.079257;0.996493;,
  -0.058103;-0.026846;0.997950;,
  -0.130501;0.059024;0.989690;,
  -0.246873;-0.042467;0.968117;,
  -0.112103;0.163488;0.980155;,
  0.929086;-0.216049;-0.300203;,
  0.243513;0.428041;0.870335;,
  0.301580;0.210434;0.929928;,
  0.252773;0.025152;0.967199;,
  0.154067;0.041981;0.987168;,
  -0.057920;-0.038356;0.997584;,
  -0.131497;-0.191377;0.972668;,
  -0.282876;-0.066990;0.956814;,
  -0.381413;0.136944;0.914205;,
  -0.366649;0.325342;0.871620;,
  -0.089302;0.478295;0.873647;,
  0.121302;0.444666;0.887445;,
  0.368495;0.419791;0.829450;,
  0.340441;0.187351;0.921412;,
  0.318953;-0.014585;0.947658;,
  0.128689;-0.163259;0.978154;,
  -0.173189;-0.358573;0.917296;,
  -0.419076;-0.282064;0.863027;,
  -0.522365;-0.024982;0.852356;,
  -0.482948;0.269032;0.833296;,
  -0.396850;0.460235;0.794163;,
  -0.045019;0.593973;0.803224;,
  0.267595;0.605198;0.749752;,
  0.604269;0.293171;0.740884;,
  0.532324;0.052371;0.844919;,
  0.378501;-0.422139;0.823733;,
  0.116058;-0.731076;0.672352;,
  -0.256481;-0.591784;0.764205;,
  -0.387985;-0.167007;0.906409;,
  -0.364589;0.174725;0.914629;,
  -0.478386;0.462905;0.746235;,
  0.164918;0.789055;0.591772;,
  0.458316;0.639824;0.616905;,
  0.858352;0.045797;0.511013;,
  0.751179;-0.374729;0.543423;,
  0.261469;-0.697186;0.667506;,
  -0.033829;-0.719416;0.693755;,
  -0.418086;-0.653416;0.631071;,
  0.356557;0.613152;0.704920;,
  0.003868;0.333139;0.942870;,
  -0.668204;0.367270;0.647005;,
  -0.325822;0.708288;0.626234;,
  -0.130318;0.881690;0.453475;,
  0.377301;0.750300;0.542858;,
  0.736566;0.435136;0.517809;,
  0.919399;-0.260463;0.294729;,
  0.668983;-0.584947;0.458582;,
  0.130275;-0.682593;0.719094;,
  -0.238299;-0.824021;0.514007;,
  -0.697361;-0.521348;0.491817;,
  -0.886597;-0.080487;0.455486;,
  -0.525751;0.737227;0.424362;,
  0.135125;0.862787;0.487175;,
  0.655263;0.633746;0.411092;,
  0.925518;0.097634;0.365903;,
  0.827148;-0.495098;0.265902;,
  0.397339;-0.727331;0.559564;,
  -0.025419;-0.860738;0.508413;,
  -0.551965;-0.686498;0.473344;,
  -0.781003;-0.367398;0.505027;,
  -0.852700;0.384897;0.353211;,
  -0.675023;0.656081;0.337495;,
  -0.433959;0.852906;0.290226;,
  -0.162362;0.943123;0.290099;,
  0.525895;0.848381;0.060704;,
  0.945880;0.322202;-0.038688;,
  0.984258;-0.172450;-0.038692;,
  0.642231;-0.733818;0.221474;,
  0.310543;-0.837558;0.449511;,
  -0.312820;-0.828399;0.464648;,
  -0.641617;-0.639519;0.423489;,
  -0.938069;0.089350;0.334730;,
  -0.625297;0.686438;0.371223;,
  0.195449;0.978966;-0.058521;,
  0.768910;0.636378;-0.061641;,
  0.999600;0.022515;0.017130;,
  0.953641;-0.294619;0.061387;,
  0.154676;-0.969152;0.191887;,
  -0.235724;-0.938559;0.252073;,
  -0.406103;-0.676144;0.614743;,
  -0.916674;-0.397404;0.042175;,
  -0.833260;0.530299;0.156399;,
  -0.487268;0.872752;-0.029557;,
  -0.193009;0.976241;-0.098495;,
  0.421079;0.900870;0.105482;,
  0.887154;0.379379;0.262735;,
  0.888181;-0.092829;0.450020;,
  0.798401;-0.540953;0.264434;,
  0.314478;-0.948636;0.034547;,
  0.014056;-0.999678;-0.021115;,
  -0.658680;-0.748725;-0.074509;,
  -0.970663;0.240200;-0.010791;,
  -0.701839;0.696444;-0.149626;,
  0.125088;0.890513;-0.437425;,
  0.702957;0.519875;-0.485367;,
  0.996671;0.078790;0.020932;,
  0.927267;-0.346065;0.142881;,
  0.623565;-0.719255;-0.306331;,
  -0.202647;-0.979220;-0.007848;,
  -0.572749;-0.810025;-0.125769;,
  -0.800511;-0.560114;-0.213199;,
  -0.881511;-0.130866;-0.453665;,
  -0.804341;0.499159;-0.322298;,
  -0.480900;0.814569;-0.324364;,
  -0.186776;0.734271;-0.652657;,
  0.455982;0.694593;-0.556436;,
  0.872072;0.320689;-0.369660;,
  0.953317;-0.145334;-0.264698;,
  0.775575;-0.474828;-0.415959;,
  0.057624;-0.927220;-0.370058;,
  -0.353037;-0.874521;-0.332534;,
  -0.743886;-0.541642;-0.391482;,
  -0.804592;-0.382059;-0.454601;,
  -0.802329;0.214281;-0.557092;,
  -0.611759;0.627969;-0.481047;,
  0.114760;0.789840;-0.602480;,
  0.677276;0.562138;-0.474656;,
  0.907467;0.113150;-0.404601;,
  0.831890;-0.308149;-0.461523;,
  0.519644;-0.661045;-0.541285;,
  0.119286;-0.780503;-0.613666;,
  -0.539052;-0.729448;-0.421105;,
  -0.788271;-0.203819;-0.580592;,
  -0.682376;0.471176;-0.558889;,
  -0.362602;0.726600;-0.583586;,
  -0.118369;0.789093;-0.602762;,
  0.360921;0.676246;-0.642205;,
  0.721890;0.289766;-0.628419;,
  0.779596;-0.020567;-0.625945;,
  0.628916;-0.514776;-0.582641;,
  0.224381;-0.764198;-0.604694;,
  -0.152693;-0.872412;-0.464309;,
  -0.792232;-0.380735;-0.476874;,
  -0.830812;0.007804;-0.556498;,
  -0.422293;0.535335;-0.731495;,
  0.109980;0.570358;-0.814000;,
  0.458967;0.339175;-0.821164;,
  0.574777;0.144085;-0.805525;,
  0.581738;-0.344956;-0.736605;,
  0.423010;-0.541903;-0.726225;,
  -0.027713;-0.682417;-0.730437;,
  -0.301016;-0.658596;-0.689668;,
  -0.493529;-0.412396;-0.765741;,
  -0.588723;-0.149587;-0.794374;,
  -0.488357;0.183499;-0.853133;,
  -0.245362;0.476112;-0.844461;,
  0.019392;0.292831;-0.955968;,
  0.220371;0.306000;-0.926175;,
  0.347906;0.177012;-0.920667;,
  0.441871;-0.034750;-0.896405;,
  0.387518;-0.384833;-0.837696;,
  0.156667;-0.483220;-0.861367;,
  -0.210898;-0.403013;-0.890563;,
  -0.318673;-0.422172;-0.848656;,
  -0.361177;-0.130704;-0.923292;,
  -0.401612;0.032799;-0.915222;,
  -0.379624;0.177797;-0.907895;,
  0.013111;0.190554;-0.981589;,
  0.100873;0.251936;-0.962472;,
  0.335299;0.063957;-0.939938;,
  0.298614;-0.248608;-0.921425;,
  0.191299;-0.373176;-0.907824;,
  -0.079907;-0.318370;-0.944593;,
  -0.267673;-0.267391;-0.925664;,
  -0.321855;-0.006677;-0.946766;,
  -0.353342;0.063037;-0.933368;,
  -0.218653;0.155663;-0.963307;,
  -0.077956;0.112914;-0.990542;,
  -0.194968;0.185006;-0.963203;,
  0.155521;0.102553;-0.982495;,
  0.212242;-0.024180;-0.976918;,
  0.127508;-0.233019;-0.964077;,
  -0.136896;-0.276046;-0.951345;,
  -0.172631;-0.234347;-0.956703;,
  -0.245661;-0.190256;-0.950502;,
  -0.267912;-0.112353;-0.956870;,
  -0.235843;0.039890;-0.970972;,
  -0.196510;0.269624;-0.942702;,
  0.117791;0.057056;-0.991398;,
  0.013061;-0.143773;-0.989524;,
  -0.097996;-0.216230;-0.971412;,
  -0.121532;-0.177379;-0.976610;,
  -0.107749;-0.192839;-0.975297;,
  -0.198925;-0.005303;-0.980000;,
  -0.192220;-0.231167;-0.953736;,
  -0.056193;0.076113;-0.995514;,
  -0.173522;-0.044728;-0.983814;,
  0.041914;0.474343;0.879342;,
  0.309282;-0.658410;0.686179;,
  0.422421;0.600079;0.679313;,
  -0.821906;-0.435360;0.367331;,
  -0.556138;-0.636562;0.534321;,
  -0.380165;-0.870150;-0.313550;,
  0.514021;0.618979;0.593841;,
  0.180859;-0.846177;-0.501273;,
  -0.063226;-0.842267;-0.535340;,
  -0.303471;-0.787186;-0.536884;,
  0.244888;0.473201;0.846233;;
  392;
  3;2,13,12;,
  3;0,3,2;,
  3;3,14,13;,
  3;0,4,3;,
  3;4,15,14;,
  3;0,5,4;,
  3;5,16,15;,
  3;0,6,5;,
  3;6,17,16;,
  3;0,7,6;,
  3;7,18,17;,
  3;0,8,7;,
  3;8,19,18;,
  3;0,9,8;,
  3;9,20,19;,
  3;0,10,9;,
  3;10,21,20;,
  3;0,1,10;,
  3;33,22,12;,
  3;13,24,23;,
  3;14,25,24;,
  3;15,26,25;,
  3;16,27,26;,
  3;17,28,27;,
  3;18,29,28;,
  3;19,30,29;,
  3;20,31,30;,
  3;11,11,11;,
  3;13,2,3;,
  3;12,13,23;,
  3;24,13,14;,
  3;14,3,4;,
  3;24,35,34;,
  3;15,4,5;,
  3;25,36,35;,
  3;16,5,6;,
  3;26,37,36;,
  3;17,6,7;,
  3;27,38,37;,
  3;18,7,8;,
  3;28,39,38;,
  3;19,8,9;,
  3;29,40,39;,
  3;20,9,10;,
  3;30,41,40;,
  3;12,22,198;,
  3;21,198,22;,
  3;22,33,32;,
  3;33,43,42;,
  3;23,24,34;,
  3;35,24,25;,
  3;25,14,15;,
  3;35,45,44;,
  3;26,15,16;,
  3;36,46,45;,
  3;27,16,17;,
  3;37,47,46;,
  3;28,17,18;,
  3;38,48,47;,
  3;29,18,19;,
  3;49,50,49;,
  3;30,19,20;,
  3;40,51,50;,
  3;21,31,20;,
  3;31,21,32;,
  3;32,21,22;,
  3;32,42,52;,
  3;42,54,53;,
  3;23,33,12;,
  3;43,55,54;,
  3;34,35,44;,
  3;45,35,36;,
  3;36,25,26;,
  3;45,57,56;,
  3;37,26,27;,
  3;46,58,199;,
  3;38,27,28;,
  3;47,59,58;,
  3;200,49,49;,
  3;39,28,29;,
  3;40,29,30;,
  3;201,61,60;,
  3;31,41,30;,
  3;41,31,52;,
  3;52,31,32;,
  3;52,53,62;,
  3;42,32,33;,
  3;43,33,23;,
  3;54,64,63;,
  3;34,43,23;,
  3;55,65,64;,
  3;44,45,56;,
  3;199,45,46;,
  3;46,36,37;,
  3;57,67,66;,
  3;47,37,38;,
  3;58,68,67;,
  3;50,39,40;,
  3;48,202,60;,
  3;60,202,201;,
  3;60,70,69;,
  3;41,51,40;,
  3;51,41,62;,
  3;51,62,72;,
  3;62,73,72;,
  3;54,42,43;,
  3;53,63,73;,
  3;63,75,74;,
  3;55,43,34;,
  3;64,76,75;,
  3;44,55,34;,
  3;65,77,76;,
  3;56,57,66;,
  3;67,57,58;,
  3;58,46,47;,
  3;67,79,78;,
  3;48,59,47;,
  3;59,48,69;,
  3;69,48,60;,
  3;69,81,80;,
  3;51,61,201;,
  3;61,51,71;,
  3;73,62,53;,
  3;62,41,52;,
  3;53,52,42;,
  3;73,74,83;,
  3;63,53,54;,
  3;64,54,55;,
  3;75,85,84;,
  3;65,55,44;,
  3;76,86,85;,
  3;56,65,44;,
  3;77,87,86;,
  3;66,67,78;,
  3;68,79,67;,
  3;59,68,58;,
  3;68,59,80;,
  3;80,59,69;,
  3;80,90,89;,
  3;61,70,60;,
  3;70,61,82;,
  3;71,82,61;,
  3;71,72,83;,
  3;83,72,73;,
  3;83,93,92;,
  3;75,63,64;,
  3;74,84,93;,
  3;84,95,94;,
  3;76,64,65;,
  3;85,96,95;,
  3;77,65,56;,
  3;86,97,96;,
  3;66,77,56;,
  3;87,98,97;,
  3;78,79,88;,
  3;88,79,68;,
  3;88,100,99;,
  3;70,81,69;,
  3;81,70,91;,
  3;82,91,70;,
  3;82,71,92;,
  3;92,71,83;,
  3;92,103,102;,
  3;74,73,63;,
  3;93,94,103;,
  3;84,74,75;,
  3;85,75,76;,
  3;95,105,104;,
  3;86,76,77;,
  3;96,106,105;,
  3;87,77,66;,
  3;97,107,106;,
  3;78,87,66;,
  3;98,108,107;,
  3;81,90,80;,
  3;203,203,101;,
  3;101,90,81;,
  3;101,111,110;,
  3;91,82,102;,
  3;102,82,92;,
  3;102,113,112;,
  3;93,83,74;,
  3;103,114,113;,
  3;95,84,85;,
  3;94,104,114;,
  3;104,116,115;,
  3;96,85,86;,
  3;105,117,116;,
  3;97,86,87;,
  3;106,118,117;,
  3;98,87,78;,
  3;107,119,118;,
  3;89,100,88;,
  3;99,100,109;,
  3;109,100,89;,
  3;109,121,120;,
  3;91,101,81;,
  3;111,123,122;,
  3;103,92,93;,
  3;113,125,124;,
  3;94,93,84;,
  3;114,115,125;,
  3;104,94,95;,
  3;204,95,96;,
  3;116,127,126;,
  3;106,96,97;,
  3;117,128,127;,
  3;107,97,98;,
  3;118,129,128;,
  3;99,108,98;,
  3;108,99,120;,
  3;120,99,109;,
  3;142,131,121;,
  3;111,101,91;,
  3;110,111,122;,
  3;112,123,111;,
  3;113,102,103;,
  3;112,113,124;,
  3;125,113,114;,
  3;114,103,94;,
  3;125,135,134;,
  3;116,104,105;,
  3;115,126,135;,
  3;126,137,136;,
  3;117,105,106;,
  3;127,138,137;,
  3;118,106,107;,
  3;128,139,138;,
  3;108,120,131;,
  3;119,108,130;,
  3;121,131,120;,
  3;108,119,107;,
  3;110,121,109;,
  3;121,110,132;,
  3;122,132,110;,
  3;122,123,133;,
  3;133,123,112;,
  3;133,144,143;,
  3;124,125,134;,
  3;135,125,115;,
  3;115,114,104;,
  3;135,136,145;,
  3;126,115,116;,
  3;127,116,117;,
  3;137,147,146;,
  3;128,117,118;,
  3;138,148,147;,
  3;119,129,118;,
  3;129,119,140;,
  3;130,140,119;,
  3;130,131,141;,
  3;131,142,141;,
  3;142,152,151;,
  3;132,122,143;,
  3;143,122,133;,
  3;143,154,153;,
  3;124,133,112;,
  3;144,155,154;,
  3;134,135,145;,
  3;136,135,126;,
  3;137,126,127;,
  3;136,146,156;,
  3;146,158,157;,
  3;138,127,128;,
  3;147,159,158;,
  3;129,139,128;,
  3;139,129,149;,
  3;140,149,129;,
  3;140,130,150;,
  3;141,150,130;,
  3;141,142,151;,
  3;152,142,132;,
  3;132,142,121;,
  3;152,164,163;,
  3;144,133,124;,
  3;154,166,165;,
  3;134,144,124;,
  3;155,167,166;,
  3;145,136,156;,
  3;158,146,147;,
  3;146,136,137;,
  3;147,137,138;,
  3;158,169,168;,
  3;139,148,138;,
  3;148,139,160;,
  3;149,160,139;,
  3;149,140,161;,
  3;150,161,140;,
  3;150,141,162;,
  3;151,162,141;,
  3;151,152,163;,
  3;153,164,152;,
  3;154,143,144;,
  3;153,154,165;,
  3;166,154,155;,
  3;155,144,134;,
  3;166,176,175;,
  3;145,155,134;,
  3;167,177,176;,
  3;156,146,157;,
  3;168,157,158;,
  3;168,179,178;,
  3;148,159,147;,
  3;159,148,170;,
  3;160,170,148;,
  3;160,149,171;,
  3;161,171,149;,
  3;161,150,172;,
  3;162,172,150;,
  3;162,151,173;,
  3;163,173,151;,
  3;163,164,174;,
  3;174,164,153;,
  3;174,185,184;,
  3;165,166,175;,
  3;176,166,167;,
  3;167,155,145;,
  3;176,187,186;,
  3;156,167,145;,
  3;177,178,187;,
  3;159,169,158;,
  3;169,159,180;,
  3;170,180,159;,
  3;170,160,181;,
  3;171,181,160;,
  3;171,161,182;,
  3;172,182,161;,
  3;172,162,183;,
  3;173,183,162;,
  3;173,163,184;,
  3;184,163,174;,
  3;184,193,192;,
  3;165,174,153;,
  3;185,194,193;,
  3;175,176,186;,
  3;187,176,177;,
  3;177,167,156;,
  3;187,196,195;,
  3;169,179,168;,
  3;178,197,196;,
  3;179,169,188;,
  3;180,188,169;,
  3;180,170,189;,
  3;181,189,170;,
  3;181,171,190;,
  3;182,190,171;,
  3;182,172,191;,
  3;183,191,172;,
  3;183,173,192;,
  3;192,173,184;,
  3;185,174,165;,
  3;175,185,165;,
  3;186,187,195;,
  3;196,187,178;,
  3;178,177,168;,
  3;179,197,178;,
  3;179,188,197;,
  3;205,205,206;,
  3;180,189,197;,
  3;207,207,206;,
  3;181,190,197;,
  3;190,182,197;,
  3;182,191,197;,
  3;191,183,197;,
  3;183,192,197;,
  3;193,184,185;,
  3;192,193,197;,
  3;194,185,175;,
  3;193,194,197;,
  3;186,194,175;,
  3;194,186,197;,
  3;186,195,197;,
  3;195,196,197;,
  3;38,202,48;,
  3;51,72,71;,
  3;108,131,130;,
  3;2,12,198;,
  3;2,198,0;,
  3;10,208,198;,
  3;10,198,21;,
  3;68,80,89;,
  3;68,89,88;,
  3;78,88,99;,
  3;78,99,98;,
  3;89,101,110;,
  3;89,110,109;,
  3;91,102,112;,
  3;91,112,111;,
  3;132,143,153;,
  3;132,153,152;,
  3;157,168,177;,
  3;157,177,156;;
 }
 MeshTextureCoords {
  200;
  0.125000;0.050000;,
  0.175000;0.100000;,
  0.100000;0.125000;,
  0.037500;0.025000;,
  0.225000;0.050000;,
  0.275000;0.100000;,
  0.325000;0.050000;,
  0.375000;0.100000;,
  0.425000;0.050000;,
  0.475000;0.100000;,
  0.525000;0.050000;,
  0.575000;0.100000;,
  0.625000;0.050000;,
  0.675000;0.100000;,
  0.725000;0.050000;,
  0.775000;0.100000;,
  0.825000;0.050000;,
  0.875000;0.100000;,
  0.925000;0.050000;,
  0.950000;0.125000;,
  1.000000;0.050000;,
  0.075000;0.200000;,
  0.025000;0.150000;,
  0.225000;0.150000;,
  0.150000;0.175000;,
  0.325000;0.150000;,
  0.425000;0.150000;,
  0.525000;0.150000;,
  0.625000;0.150000;,
  0.725000;0.150000;,
  0.825000;0.150000;,
  0.900000;0.175000;,
  0.025000;0.100000;,
  0.000000;0.050000;,
  0.275000;0.200000;,
  0.200000;0.225000;,
  0.375000;0.200000;,
  0.475000;0.200000;,
  0.575000;0.200000;,
  0.675000;0.200000;,
  0.775000;0.200000;,
  0.850000;0.225000;,
  0.975000;0.200000;,
  0.125000;0.250000;,
  0.025000;0.250000;,
  0.325000;0.250000;,
  0.250000;0.275000;,
  0.425000;0.250000;,
  0.525000;0.250000;,
  0.600000;0.275000;,
  0.725000;0.250000;,
  0.650000;0.250000;,
  0.800000;0.275000;,
  0.925000;0.250000;,
  0.075000;0.300000;,
  0.975000;0.300000;,
  0.175000;0.300000;,
  0.375000;0.300000;,
  0.300000;0.325000;,
  0.475000;0.300000;,
  0.550000;0.325000;,
  0.750000;0.325000;,
  0.675000;0.300000;,
  0.875000;0.300000;,
  0.125000;0.350000;,
  0.025000;0.350000;,
  0.225000;0.350000;,
  0.425000;0.350000;,
  0.350000;0.375000;,
  0.500000;0.375000;,
  0.700000;0.375000;,
  0.625000;0.350000;,
  0.850000;0.350000;,
  0.925000;0.350000;,
  0.075000;0.400000;,
  0.975000;0.400000;,
  0.175000;0.400000;,
  0.275000;0.400000;,
  0.450000;0.400000;,
  0.400000;0.425000;,
  0.650000;0.425000;,
  0.575000;0.400000;,
  0.800000;0.375000;,
  0.875000;0.400000;,
  0.125000;0.450000;,
  0.025000;0.450000;,
  0.225000;0.450000;,
  0.325000;0.450000;,
  0.600000;0.450000;,
  0.550000;0.475000;,
  0.750000;0.425000;,
  0.925000;0.450000;,
  0.825000;0.450000;,
  0.075000;0.500000;,
  0.975000;0.500000;,
  0.175000;0.500000;,
  0.275000;0.500000;,
  0.375000;0.500000;,
  0.475000;0.450000;,
  0.500000;0.500000;,
  0.450000;0.525000;,
  0.700000;0.475000;,
  0.875000;0.500000;,
  0.775000;0.500000;,
  0.125000;0.550000;,
  0.025000;0.550000;,
  0.225000;0.550000;,
  0.325000;0.550000;,
  0.400000;0.575000;,
  0.625000;0.500000;,
  0.675000;0.550000;,
  0.600000;0.575000;,
  0.825000;0.550000;,
  0.750000;0.575000;,
  0.925000;0.550000;,
  0.075000;0.600000;,
  0.975000;0.600000;,
  0.175000;0.600000;,
  0.275000;0.600000;,
  0.350000;0.625000;,
  0.525000;0.550000;,
  0.550000;0.625000;,
  0.475000;0.600000;,
  0.700000;0.600000;,
  0.650000;0.625000;,
  0.875000;0.600000;,
  0.800000;0.625000;,
  0.125000;0.650000;,
  0.025000;0.650000;,
  0.225000;0.650000;,
  0.300000;0.675000;,
  0.525000;0.700000;,
  0.475000;0.650000;,
  0.925000;0.650000;,
  0.850000;0.675000;,
  0.075000;0.700000;,
  0.975000;0.700000;,
  0.175000;0.700000;,
  0.250000;0.725000;,
  0.400000;0.675000;,
  0.600000;0.675000;,
  0.725000;0.650000;,
  0.775000;0.700000;,
  0.675000;0.700000;,
  0.900000;0.725000;,
  0.125000;0.750000;,
  0.025000;0.750000;,
  0.200000;0.775000;,
  0.350000;0.725000;,
  0.450000;0.725000;,
  0.575000;0.750000;,
  0.500000;0.775000;,
  0.725000;0.750000;,
  0.650000;0.775000;,
  0.825000;0.750000;,
  0.950000;0.775000;,
  0.075000;0.800000;,
  0.000000;0.800000;,
  0.150000;0.825000;,
  0.300000;0.775000;,
  0.400000;0.775000;,
  0.600000;0.800000;,
  0.550000;0.825000;,
  0.775000;0.800000;,
  0.700000;0.825000;,
  0.875000;0.800000;,
  0.100000;0.875000;,
  0.025000;0.850000;,
  0.250000;0.825000;,
  0.350000;0.825000;,
  0.450000;0.825000;,
  0.825000;0.850000;,
  0.750000;0.875000;,
  0.925000;0.850000;,
  1.000000;0.800000;,
  0.050000;0.925000;,
  0.975000;0.900000;,
  0.200000;0.875000;,
  0.300000;0.875000;,
  0.400000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.850000;,
  0.675000;0.900000;,
  0.575000;0.900000;,
  0.875000;0.900000;,
  0.800000;0.925000;,
  0.150000;0.925000;,
  0.250000;0.925000;,
  0.350000;0.925000;,
  0.450000;0.925000;,
  0.625000;0.950000;,
  0.525000;0.950000;,
  0.725000;0.950000;,
  0.925000;0.950000;,
  0.850000;0.950000;,
  0.012500;0.975000;,
  0.100000;0.950000;,
  0.200000;0.950000;,
  0.300000;0.950000;,
  0.400000;0.950000;;
 }
}
