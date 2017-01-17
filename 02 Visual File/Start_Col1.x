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
 514;
 -22.40576;5.38742;24.17140;,
 -4.24414;5.38742;24.17140;,
 -4.24414;-2.66796;24.17140;,
 -22.40576;-2.66796;24.17140;,
 -4.24414;5.38742;24.17140;,
 -4.24414;5.38742;36.47980;,
 -4.24414;-2.66796;36.47980;,
 -4.24414;-2.66796;24.17140;,
 -4.24414;5.38742;36.47980;,
 -22.40576;5.38742;36.47980;,
 -22.40576;-2.66796;36.47980;,
 -4.24414;-2.66796;36.47980;,
 -22.40576;5.38742;36.47980;,
 -22.40576;5.38742;24.17140;,
 -22.40576;-2.66796;24.17140;,
 -22.40576;-2.66796;36.47980;,
 -4.24414;5.38742;24.17140;,
 -22.40576;5.38742;24.17140;,
 -22.40576;-2.66796;24.17140;,
 -4.24414;-2.66796;24.17140;,
 -9.30246;5.38742;29.98125;,
 -22.90452;5.38742;17.94717;,
 -22.90452;-2.66796;17.94717;,
 -9.30246;-2.66796;29.98125;,
 -22.90452;5.38742;17.94717;,
 -17.37730;5.38742;11.69978;,
 -17.37730;-2.66796;11.69978;,
 -22.90452;-2.66796;17.94717;,
 -17.37730;5.38742;11.69978;,
 -3.77523;5.38742;23.73386;,
 -3.77523;-2.66796;23.73386;,
 -17.37730;-2.66796;11.69978;,
 -3.77523;5.38742;23.73386;,
 -9.30246;5.38742;29.98125;,
 -9.30246;-2.66796;29.98125;,
 -3.77523;-2.66796;23.73386;,
 -22.90452;5.38742;17.94717;,
 -9.30246;5.38742;29.98125;,
 -9.30246;-2.66796;29.98125;,
 -22.90452;-2.66796;17.94717;,
 -16.34262;5.38742;-3.91734;,
 -15.07573;5.38742;14.19975;,
 -15.07573;-2.66796;14.19975;,
 -16.34262;-2.66796;-3.91734;,
 -15.07573;5.38742;14.19975;,
 -23.39687;5.38742;14.78163;,
 -23.39687;-2.66796;14.78163;,
 -15.07573;-2.66796;14.19975;,
 -23.39687;5.38742;14.78163;,
 -24.66376;5.38742;-3.33548;,
 -24.66376;-2.66796;-3.33548;,
 -23.39687;-2.66796;14.78163;,
 -24.66376;5.38742;-3.33548;,
 -16.34262;5.38742;-3.91734;,
 -16.34262;-2.66796;-3.91734;,
 -24.66376;-2.66796;-3.33548;,
 -15.07573;5.38742;14.19975;,
 -16.34262;5.38742;-3.91734;,
 -16.34262;-2.66796;-3.91734;,
 -15.07573;-2.66796;14.19975;,
 -24.06408;5.38742;-4.39575;,
 -16.10261;5.38742;-20.71924;,
 -16.10261;-2.66796;-20.71924;,
 -24.06408;-2.66796;-4.39575;,
 -16.10261;5.38742;-20.71924;,
 -8.60526;5.38742;-17.06257;,
 -8.60526;-2.66796;-17.06257;,
 -16.10261;-2.66796;-20.71924;,
 -8.60526;5.38742;-17.06257;,
 -16.56675;5.38742;-0.73905;,
 -16.56675;-2.66796;-0.73905;,
 -8.60526;-2.66796;-17.06257;,
 -16.56675;5.38742;-0.73905;,
 -24.06408;5.38742;-4.39575;,
 -24.06408;-2.66796;-4.39575;,
 -16.56675;-2.66796;-0.73905;,
 -16.10261;5.38742;-20.71924;,
 -24.06408;5.38742;-4.39575;,
 -24.06408;-2.66796;-4.39575;,
 -16.10261;-2.66796;-20.71924;,
 -11.34414;5.38742;-19.63750;,
 6.74812;5.38742;-21.22040;,
 6.74812;-2.66796;-21.22040;,
 -11.34414;-2.66796;-19.63750;,
 6.74812;5.38742;-21.22040;,
 7.47515;5.38742;-12.91066;,
 7.47515;-2.66796;-12.91066;,
 6.74812;-2.66796;-21.22040;,
 7.47515;5.38742;-12.91066;,
 -11.12353;5.23880;-11.09150;,
 -11.12353;-2.81658;-11.09150;,
 7.47515;-2.66796;-12.91066;,
 -11.12353;5.23880;-11.09150;,
 -11.34414;5.38742;-19.63750;,
 -11.34414;-2.66796;-19.63750;,
 -11.12353;-2.81658;-11.09150;,
 6.74812;5.38742;-21.22040;,
 -11.34414;5.38742;-19.63750;,
 -11.34414;-2.66796;-19.63750;,
 6.74812;-2.66796;-21.22040;,
 12.36205;5.38742;-19.22482;,
 26.37568;5.38742;-7.67292;,
 26.37568;-2.66796;-7.67292;,
 12.36205;-2.66796;-19.22482;,
 26.37568;5.38742;-7.67292;,
 21.06991;5.38742;-1.23648;,
 21.06991;-2.66796;-1.23648;,
 26.37568;-2.66796;-7.67292;,
 21.06991;5.38742;-1.23648;,
 6.52948;5.23880;-12.97484;,
 6.52948;-2.81658;-12.97484;,
 21.06991;-2.66796;-1.23648;,
 6.52948;5.23880;-12.97484;,
 12.36205;5.38742;-19.22482;,
 12.36205;-2.66796;-19.22482;,
 6.52948;-2.81658;-12.97484;,
 26.37568;5.38742;-7.67292;,
 12.36205;5.38742;-19.22482;,
 12.36205;-2.66796;-19.22482;,
 26.37568;-2.66796;-7.67292;,
 18.76524;5.38742;13.50456;,
 16.39467;5.38742;-4.50147;,
 16.39467;-2.66796;-4.50147;,
 18.76524;-2.66796;13.50456;,
 16.39467;5.38742;-4.50147;,
 24.66481;5.38742;-5.59027;,
 24.66481;-2.66796;-5.59027;,
 16.39467;-2.66796;-4.50147;,
 24.66481;5.38742;-5.59027;,
 27.29349;5.23880;12.91140;,
 27.29349;-2.81658;12.91140;,
 24.66481;-2.66796;-5.59027;,
 27.29349;5.23880;12.91140;,
 18.76524;5.38742;13.50456;,
 18.76524;-2.66796;13.50456;,
 27.29349;-2.81658;12.91140;,
 16.39467;5.38742;-4.50147;,
 18.76524;5.38742;13.50456;,
 18.76524;-2.66796;13.50456;,
 16.39467;-2.66796;-4.50147;,
 23.99043;5.38742;17.55625;,
 10.49384;5.38742;29.70869;,
 10.49384;-2.66796;29.70869;,
 23.99043;-2.66796;17.55625;,
 10.49384;5.38742;29.70869;,
 4.91226;5.38742;23.50973;,
 4.91226;-2.66796;23.50973;,
 10.49384;-2.66796;29.70869;,
 4.91226;5.38742;23.50973;,
 18.67112;5.23880;10.86385;,
 18.67112;-2.81658;10.86385;,
 4.91226;-2.66796;23.50973;,
 18.67112;5.23880;10.86385;,
 23.99043;5.38742;17.55625;,
 23.99043;-2.66796;17.55625;,
 18.67112;-2.81658;10.86385;,
 10.49384;5.38742;29.70869;,
 23.99043;5.38742;17.55625;,
 23.99043;-2.66796;17.55625;,
 10.49384;-2.66796;29.70869;,
 5.29940;5.14446;21.34385;,
 23.43956;5.50158;19.89642;,
 23.60320;-2.55131;23.79972;,
 5.46304;-2.90843;24.59923;,
 23.43956;5.50158;19.89642;,
 23.80430;5.62865;34.98115;,
 23.96794;-2.42424;32.13221;,
 23.60320;-2.55131;23.79972;,
 23.80430;5.62865;34.98115;,
 5.15105;5.11554;36.81998;,
 5.31467;-2.93735;33.14795;,
 23.96794;-2.42424;32.13221;,
 5.15105;5.11554;36.81998;,
 5.29940;5.14446;21.34385;,
 5.46304;-2.90843;24.59923;,
 5.31467;-2.93735;33.14795;,
 23.43956;5.50158;19.89642;,
 5.29940;5.14446;21.34385;,
 5.46304;-2.90843;24.59923;,
 23.60320;-2.55131;23.79972;,
 -7.43843;-0.79798;41.24247;,
 7.43843;-0.79798;41.24247;,
 7.43843;-0.79798;26.36560;,
 -7.43843;-0.79798;26.36560;,
 2.68493;28.55236;36.18798;,
 17.86159;28.55236;36.18798;,
 17.86159;13.74950;36.18798;,
 2.68493;13.74950;36.18798;,
 17.86159;28.55236;36.18798;,
 17.86159;28.55236;122.71089;,
 17.86159;13.74950;122.71089;,
 17.86159;13.74950;36.18798;,
 17.86159;28.55236;122.71089;,
 2.68493;28.55236;122.71089;,
 2.68493;13.74950;122.71089;,
 17.86159;13.74950;122.71089;,
 2.68493;28.55236;122.71089;,
 2.68493;28.55236;36.18798;,
 2.68493;13.74950;36.18798;,
 2.68493;13.74950;122.71089;,
 17.86159;28.55236;36.18798;,
 2.68493;28.55236;36.18798;,
 2.68493;13.74950;36.18798;,
 17.86159;13.74950;36.18798;,
 -14.85949;28.86580;66.13072;,
 -3.32381;28.86580;66.13072;,
 -3.32381;8.79914;66.13072;,
 -14.85949;8.79914;66.13072;,
 -3.32381;28.86580;66.13072;,
 -3.32381;28.86580;135.60495;,
 -3.32381;8.79914;135.60495;,
 -3.32381;8.79914;66.13072;,
 -3.32381;28.86580;135.60495;,
 -14.85949;28.86580;135.60495;,
 -14.85949;8.79914;135.60495;,
 -3.32381;8.79914;135.60495;,
 -14.85949;28.86580;135.60495;,
 -14.85949;28.86580;66.13072;,
 -14.85949;8.79914;66.13072;,
 -14.85949;8.79914;135.60495;,
 -3.32381;28.86580;66.13072;,
 -14.85949;28.86580;66.13072;,
 -14.85949;8.79914;66.13072;,
 -3.32381;8.79914;66.13072;,
 -15.40431;19.23520;38.21309;,
 -1.39168;19.23520;38.21309;,
 -1.39168;8.74249;38.21309;,
 -15.40431;8.74249;38.21309;,
 -1.39168;19.23520;60.94447;,
 -15.40431;19.23520;60.94447;,
 -15.40431;8.74249;60.94447;,
 -1.39168;8.74249;60.94447;,
 -15.40431;19.23520;60.94447;,
 -15.40431;19.23520;38.21309;,
 -15.40431;8.74249;38.21309;,
 -15.40431;8.74249;60.94447;,
 -1.39168;19.23520;60.94447;,
 -1.39168;19.23520;38.21309;,
 -15.40431;19.23520;38.21309;,
 -15.40431;8.74249;38.21309;,
 -1.39168;8.74249;38.21309;,
 -1.39168;8.74249;60.94447;,
 -38.09866;27.60523;61.33213;,
 -38.70983;27.60523;47.33378;,
 -38.70983;12.12275;47.33378;,
 -38.09866;12.12275;61.33213;,
 -16.00146;27.60523;46.34230;,
 -15.39029;27.60523;60.34069;,
 -15.39029;12.12275;60.34069;,
 -16.00146;12.12275;46.34230;,
 -15.39029;27.60523;60.34069;,
 -38.09866;27.60523;61.33213;,
 -38.09866;12.12275;61.33213;,
 -15.39029;12.12275;60.34069;,
 -16.00146;27.60523;46.34230;,
 -38.70983;27.60523;47.33378;,
 -38.09866;27.60523;61.33213;,
 -38.09866;12.12275;61.33213;,
 -38.70983;12.12275;47.33378;,
 -16.00146;12.12275;46.34230;,
 -12.94585;24.66009;65.89114;,
 -11.30451;24.66009;79.81573;,
 -11.30451;14.16738;79.81573;,
 -12.94585;14.16738;65.89114;,
 -40.47594;24.66009;82.59337;,
 -40.14281;24.47142;68.54927;,
 -42.11731;14.16738;68.66866;,
 -40.47594;14.16738;82.59337;,
 -40.14281;24.47142;68.54927;,
 -12.94585;24.66009;65.89114;,
 -12.94585;14.16738;65.89114;,
 -42.11731;14.16738;68.66866;,
 -40.47594;24.66009;82.59337;,
 -11.30451;24.66009;79.81573;,
 -12.94585;24.66009;65.89114;,
 -12.94585;14.16738;65.89114;,
 -11.30451;14.16738;79.81573;,
 -40.47594;14.16738;82.59337;,
 -42.23867;21.83465;71.47456;,
 -34.33019;21.38240;79.45839;,
 -34.33019;10.88969;79.45839;,
 -43.05466;10.88969;69.33469;,
 -51.53930;21.38240;93.02951;,
 -57.39928;21.08399;84.14094;,
 -60.26375;10.88969;82.90576;,
 -51.53930;10.88969;93.02951;,
 -57.39928;21.08399;84.14094;,
 -42.23867;21.83465;71.47456;,
 -43.05466;10.88969;69.33469;,
 -60.26375;10.88969;82.90576;,
 -51.53930;21.38240;93.02951;,
 -34.33019;21.38240;79.45839;,
 -42.23867;21.83465;71.47456;,
 -43.05466;10.88969;69.33469;,
 -34.33019;10.88969;79.45839;,
 -51.53930;10.88969;93.02951;,
 -62.59544;21.74795;86.59037;,
 -49.68705;18.88992;90.57848;,
 -49.68705;8.39721;90.57848;,
 -62.31832;8.71137;84.23982;,
 -57.83279;18.88992;111.79898;,
 -70.91402;18.88992;106.77747;,
 -70.91402;8.39721;106.77747;,
 -57.83279;8.39721;111.79898;,
 -70.91402;18.88992;106.77747;,
 -62.59544;21.74795;86.59037;,
 -62.31832;8.71137;84.23982;,
 -70.91402;8.39721;106.77747;,
 -57.83279;18.88992;111.79898;,
 -49.68705;18.88992;90.57848;,
 -62.59544;21.74795;86.59037;,
 -62.31832;8.71137;84.23982;,
 -49.68705;8.39721;90.57848;,
 -57.83279;8.39721;111.79898;,
 -77.90207;24.97436;90.12576;,
 -88.09537;24.97436;76.59879;,
 -88.09537;14.48165;76.59879;,
 -77.90207;14.48165;90.12576;,
 -88.09537;24.97436;76.59879;,
 -51.04890;24.97436;48.68221;,
 -51.04890;14.48165;48.68221;,
 -88.09537;14.48165;76.59879;,
 -51.04890;24.97436;48.68221;,
 -40.85553;24.97436;62.20918;,
 -40.85553;14.48165;62.20918;,
 -51.04890;14.48165;48.68221;,
 -40.85553;24.97436;62.20918;,
 -77.90207;24.97436;90.12576;,
 -77.90207;14.48165;90.12576;,
 -40.85553;14.48165;62.20918;,
 -88.09537;24.97436;76.59879;,
 -77.90207;24.97436;90.12576;,
 -77.90207;14.48165;90.12576;,
 -88.09537;14.48165;76.59879;,
 -79.38927;17.31690;122.23350;,
 -94.19132;19.83419;127.59503;,
 -93.81275;6.17718;123.30567;,
 -78.89379;3.46867;117.29490;,
 -94.19132;19.83419;127.59503;,
 -93.81284;19.37574;76.91824;,
 -93.81284;6.17718;76.91824;,
 -93.81275;6.17718;123.30567;,
 -93.81284;19.37574;76.91824;,
 -76.87514;19.37574;76.91821;,
 -76.87514;6.17718;76.91821;,
 -93.81284;6.17718;76.91824;,
 -76.87514;19.37574;76.91821;,
 -79.38927;17.31690;122.23350;,
 -78.89379;3.46867;117.29490;,
 -76.87514;6.17718;76.91821;,
 -94.19132;19.83419;127.59503;,
 -79.38927;17.31690;122.23350;,
 -78.89379;3.46867;117.29490;,
 -93.81275;6.17718;123.30567;,
 -76.87049;19.37574;68.06360;,
 -64.08807;19.37574;79.17503;,
 -64.08807;6.17718;79.17503;,
 -76.87049;6.17718;68.06360;,
 -64.08807;19.37574;79.17503;,
 -83.22511;19.37574;101.18985;,
 -83.22511;6.17718;101.18985;,
 -64.08807;6.17718;79.17503;,
 -83.22511;19.37574;101.18985;,
 -96.00752;19.37574;90.07830;,
 -96.00752;6.17718;90.07830;,
 -83.22511;6.17718;101.18985;,
 -96.00752;19.37574;90.07830;,
 -76.87049;19.37574;68.06360;,
 -76.87049;6.17718;68.06360;,
 -96.00752;6.17718;90.07830;,
 -64.08807;19.37574;79.17503;,
 -76.87049;19.37574;68.06360;,
 -76.87049;6.17718;68.06360;,
 -64.08807;6.17718;79.17503;,
 -77.62003;17.88205;176.47672;,
 -94.55763;17.88205;176.47684;,
 -94.55763;4.68349;176.47684;,
 -77.62003;4.68349;176.47672;,
 -94.55763;17.88205;176.47684;,
 -94.55772;17.88205;123.13728;,
 -94.55772;4.68349;123.13728;,
 -94.55763;4.68349;176.47684;,
 -94.55772;17.88205;123.13728;,
 -77.83214;18.19557;123.59087;,
 -77.83214;4.99701;123.59087;,
 -94.55772;4.68349;123.13728;,
 -77.83214;18.19557;123.59087;,
 -77.62003;17.88205;176.47672;,
 -77.62003;4.68349;176.47672;,
 -77.83214;4.99701;123.59087;,
 -94.55763;17.88205;176.47684;,
 -77.62003;17.88205;176.47672;,
 -77.62003;4.68349;176.47672;,
 -94.55763;4.68349;176.47684;,
 -55.51741;17.88205;176.83804;,
 -72.45502;17.88205;176.83810;,
 -72.45502;4.68349;176.83810;,
 -55.51741;4.68349;176.83804;,
 -72.45502;17.88205;176.83810;,
 -72.45511;17.88205;136.49677;,
 -72.45511;4.68349;136.49677;,
 -72.45502;4.68349;176.83810;,
 -72.45511;17.88205;136.49677;,
 -55.51741;17.88205;136.49673;,
 -55.51741;4.68349;136.49673;,
 -72.45511;4.68349;136.49677;,
 -55.51741;17.88205;136.49673;,
 -55.51741;17.88205;176.83804;,
 -55.51741;4.68349;176.83804;,
 -55.51741;4.68349;136.49673;,
 -72.45502;17.88205;176.83810;,
 -55.51741;17.88205;176.83804;,
 -55.51741;4.68349;176.83804;,
 -72.45502;4.68349;176.83810;,
 -85.35220;15.45484;175.92403;,
 -78.65424;15.45484;175.92403;,
 -78.65424;6.00552;175.92403;,
 -85.35220;6.00552;175.92403;,
 -78.65424;15.45484;175.92403;,
 -78.65424;15.45484;192.19826;,
 -78.65424;6.00552;192.19826;,
 -78.65424;6.00552;175.92403;,
 -78.65424;15.45484;192.19826;,
 -85.35220;15.45484;192.19826;,
 -85.35220;6.00552;192.19826;,
 -78.65424;6.00552;192.19826;,
 -85.35220;15.45484;192.19826;,
 -85.35220;15.45484;175.92403;,
 -85.35220;6.00552;175.92403;,
 -85.35220;6.00552;192.19826;,
 -78.65424;15.45484;175.92403;,
 -85.35220;15.45484;175.92403;,
 -85.35220;6.00552;175.92403;,
 -78.65424;6.00552;175.92403;,
 -72.29047;15.45484;175.92403;,
 -65.59250;15.45484;175.92403;,
 -65.59250;6.00552;175.92403;,
 -72.29047;6.00552;175.92403;,
 -65.59250;15.45484;175.92403;,
 -65.59250;15.45484;192.19826;,
 -65.59250;6.00552;192.19826;,
 -65.59250;6.00552;175.92403;,
 -65.59250;15.45484;192.19826;,
 -72.29047;15.45484;192.19826;,
 -72.29047;6.00552;192.19826;,
 -65.59250;6.00552;192.19826;,
 -72.29047;15.45484;192.19826;,
 -72.29047;15.45484;175.92403;,
 -72.29047;6.00552;175.92403;,
 -72.29047;6.00552;192.19826;,
 -65.59250;15.45484;175.92403;,
 -72.29047;15.45484;175.92403;,
 -72.29047;6.00552;175.92403;,
 -65.59250;6.00552;175.92403;,
 -73.80505;15.45484;186.34082;,
 -67.10708;15.45484;186.34082;,
 -67.10708;6.00552;186.34082;,
 -73.80505;6.00552;186.34082;,
 -67.10708;15.45484;186.34082;,
 -67.10708;15.45484;196.02881;,
 -67.10708;6.00552;196.02881;,
 -67.10708;6.00552;186.34082;,
 -67.10708;15.45484;196.02881;,
 -73.80505;15.45484;196.02881;,
 -73.80505;6.00552;196.02881;,
 -67.10708;6.00552;196.02881;,
 -73.80505;15.45484;196.02881;,
 -73.80505;15.45484;186.34082;,
 -73.80505;6.00552;186.34082;,
 -73.80505;6.00552;196.02881;,
 -67.10708;15.45484;186.34082;,
 -73.80505;15.45484;186.34082;,
 -73.80505;6.00552;186.34082;,
 -67.10708;6.00552;186.34082;,
 -82.84814;15.45484;186.34082;,
 -76.15017;15.45484;186.34082;,
 -76.15017;6.00552;186.34082;,
 -82.84814;6.00552;186.34082;,
 -76.15017;15.45484;186.34082;,
 -76.15017;15.45484;196.02881;,
 -76.15017;6.00552;196.02881;,
 -76.15017;6.00552;186.34082;,
 -76.15017;15.45484;196.02881;,
 -82.84814;15.45484;196.02881;,
 -82.84814;6.00552;196.02881;,
 -76.15017;6.00552;196.02881;,
 -82.84814;15.45484;196.02881;,
 -82.84814;15.45484;186.34082;,
 -82.84814;6.00552;186.34082;,
 -82.84814;6.00552;196.02881;,
 -76.15017;15.45484;186.34082;,
 -82.84814;15.45484;186.34082;,
 -82.84814;6.00552;186.34082;,
 -76.15017;6.00552;186.34082;,
 -4.77202;18.17577;121.81287;,
 4.77202;18.17577;121.81287;,
 4.77202;12.26300;121.81287;,
 -4.77202;12.26300;121.81287;,
 4.77202;18.17577;121.81287;,
 4.77202;18.17577;126.51344;,
 4.77202;12.26300;126.51344;,
 4.77202;12.26300;121.81287;,
 4.77202;18.17577;126.51344;,
 -4.77202;18.17577;126.51344;,
 -4.77202;12.26300;126.51344;,
 4.77202;12.26300;126.51344;,
 -4.77202;18.17577;126.51344;,
 -4.77202;18.17577;121.81287;,
 -4.77202;12.26300;121.81287;,
 -4.77202;12.26300;126.51344;,
 4.77202;18.17577;121.81287;,
 -4.77202;18.17577;121.81287;,
 -4.77202;12.26300;121.81287;,
 4.77202;12.26300;121.81287;;
 
 152;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;132,125,136,137;,
 4;138,139,126,135;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;152,145,156,157;,
 4;158,159,146,155;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;172,165,176,177;,
 4;178,179,166,175;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;196,197,198,199;,
 4;196,189,200,201;,
 4;202,203,190,199;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;216,217,218,219;,
 4;216,209,220,221;,
 4;222,223,210,219;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;232,236,237,238;,
 4;239,240,241,235;,
 4;242,243,244,245;,
 4;246,247,248,249;,
 4;250,251,252,253;,
 4;250,254,255,256;,
 4;257,258,259,253;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;268,272,273,274;,
 4;275,276,277,271;,
 4;278,279,280,281;,
 4;282,283,284,285;,
 4;286,287,288,289;,
 4;286,290,291,292;,
 4;293,294,295,289;,
 4;296,297,298,299;,
 4;300,301,302,303;,
 4;304,305,306,307;,
 4;304,308,309,310;,
 4;311,312,313,307;,
 4;314,315,316,317;,
 4;318,319,320,321;,
 4;322,323,324,325;,
 4;326,327,328,329;,
 4;326,319,330,331;,
 4;332,333,320,329;,
 4;334,335,336,337;,
 4;338,339,340,341;,
 4;342,343,344,345;,
 4;346,347,348,349;,
 4;346,339,350,351;,
 4;352,353,340,349;,
 4;354,355,356,357;,
 4;358,359,360,361;,
 4;362,363,364,365;,
 4;366,367,368,369;,
 4;366,359,370,371;,
 4;372,373,360,369;,
 4;374,375,376,377;,
 4;378,379,380,381;,
 4;382,383,384,385;,
 4;386,387,388,389;,
 4;386,379,390,391;,
 4;392,393,380,389;,
 4;394,395,396,397;,
 4;398,399,400,401;,
 4;402,403,404,405;,
 4;406,407,408,409;,
 4;406,399,410,411;,
 4;412,413,400,409;,
 4;414,415,416,417;,
 4;418,419,420,421;,
 4;422,423,424,425;,
 4;426,427,428,429;,
 4;426,419,430,431;,
 4;432,433,420,429;,
 4;434,435,436,437;,
 4;438,439,440,441;,
 4;442,443,444,445;,
 4;446,447,448,449;,
 4;446,439,450,451;,
 4;452,453,440,449;,
 4;454,455,456,457;,
 4;458,459,460,461;,
 4;462,463,464,465;,
 4;466,467,468,469;,
 4;466,459,470,471;,
 4;472,473,460,469;,
 4;474,475,476,477;,
 4;478,479,480,481;,
 4;482,483,484,485;,
 4;486,487,488,489;,
 4;486,479,490,491;,
 4;492,493,480,489;,
 4;494,495,496,497;,
 4;498,499,500,501;,
 4;502,503,504,505;,
 4;506,507,508,509;,
 4;506,499,510,511;,
 4;512,513,500,509;;
 
 MeshMaterialList {
  7;
  152;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
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
  87;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.662620;0.000000;0.748956;,
  -0.748956;0.000000;-0.662619;,
  0.662619;0.000000;-0.748956;,
  0.997564;0.000000;-0.069758;,
  0.069758;0.000000;0.997564;,
  -0.997564;0.000000;0.069758;,
  -0.898795;0.000000;-0.438370;,
  0.438368;0.000000;-0.898796;,
  0.898795;0.000000;0.438370;,
  -0.087157;0.000000;-0.996195;,
  0.996195;0.000000;-0.087158;,
  0.097346;0.000000;0.995251;,
  0.636077;0.000000;-0.771626;,
  0.771626;0.000000;0.636077;,
  -0.628148;0.000000;0.778094;,
  -0.991445;0.000000;0.130528;,
  -0.130528;0.000000;-0.991445;,
  0.990057;0.000000;-0.140665;,
  0.669133;0.000000;0.743143;,
  -0.743144;0.000000;0.669132;,
  -0.676701;0.000000;-0.736258;,
  -0.048268;-0.406027;-0.912586;,
  0.999165;0.022256;-0.034252;,
  0.080600;-0.371883;0.924774;,
  0.000000;1.000000;0.000000;,
  -0.999048;0.000000;0.043619;,
  0.999048;0.000000;-0.043619;,
  0.993124;0.000000;-0.117063;,
  -0.994438;0.094775;0.045947;,
  0.733932;0.035533;-0.678293;,
  -0.796249;0.066571;0.601295;,
  0.389401;0.087748;-0.916879;,
  -0.358374;0.000000;0.933578;,
  -0.798636;0.000000;0.601815;,
  -0.601816;0.000000;-0.798635;,
  0.798634;0.000000;-0.601818;,
  0.295464;-0.295106;0.908633;,
  -0.999913;-0.012720;-0.003617;,
  -0.000002;0.000000;-1.000000;,
  0.656054;0.000000;-0.754714;,
  0.754712;0.000000;0.656056;,
  -0.656058;0.000000;0.754711;,
  0.000007;0.000000;1.000000;,
  -1.000000;0.000000;0.000002;,
  0.027110;0.000000;-0.999632;,
  0.000004;0.000000;1.000000;,
  -1.000000;0.000000;0.000002;,
  -0.000002;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.748955;0.000000;0.662621;,
  -0.069756;0.000000;-0.997564;,
  -0.438371;0.000000;0.898794;,
  -0.999667;0.000000;0.025806;,
  -0.003137;0.999957;0.008775;,
  0.003137;-0.999957;-0.008775;,
  -0.731099;0.000000;-0.682271;,
  -0.008388;0.999957;0.004060;,
  0.008388;-0.999957;-0.004060;,
  0.069384;0.000000;0.997590;,
  0.008903;0.999957;0.002751;,
  -0.008903;-0.999957;-0.002751;,
  0.782840;0.000000;-0.622223;,
  -0.002776;0.999957;-0.008896;,
  0.002776;-0.999957;0.008896;,
  -0.999674;-0.021646;-0.013527;,
  -0.023828;0.999711;-0.003163;,
  0.023827;-0.999700;0.005725;,
  0.043618;0.000000;0.999048;,
  -0.096028;0.003314;-0.995373;,
  -0.004070;0.999972;-0.006327;,
  -0.616750;0.226903;-0.753747;,
  -0.009311;0.999797;0.017843;,
  -0.929422;0.022130;-0.368355;,
  0.074110;0.992373;0.098509;,
  -0.007501;-0.999924;-0.009829;,
  0.601815;0.000000;0.798635;,
  0.998563;0.007856;0.053019;,
  0.082785;0.996388;0.018920;,
  -0.089725;-0.995399;-0.033619;,
  -0.754711;0.000000;-0.656058;,
  0.999992;0.000000;-0.004011;,
  -0.009371;0.999952;0.002964;,
  0.009371;-0.999952;-0.002964;;
  152;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;51,51,51,51;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;53,53,53,53;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;54,54,54,54;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;55,55,55,55;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;58,58,58,58;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;65,65,65,65;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;68,68,68,68;,
  4;69,69,69,69;,
  4;70,70,70,70;,
  4;27,27,27,27;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;51,51,51,51;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;51,51,51,51;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;51,51,51,51;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;71,71,71,71;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;52,52,52,52;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;74,74,74,74;,
  4;75,75,75,75;,
  4;52,52,52,52;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;78,78,78,78;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;79,79,79,79;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;82,82,82,82;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;83,83,83,83;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;84,84,84,84;,
  4;85,85,85,85;,
  4;86,86,86,86;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;1,1,1,1;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;51,51,51,51;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;51,51,51,51;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;51,51,51,51;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;51,51,51,51;,
  4;27,27,27,27;,
  4;52,52,52,52;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;51,51,51,51;,
  4;27,27,27,27;,
  4;52,52,52,52;;
 }
 MeshTextureCoords {
  514;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}