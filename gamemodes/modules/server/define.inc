//--------[ MySQL ]--------//
#define HOST     "localhost"
#define USERNAME "root"
#define PASSWORD "adaamsamasemua"
#define DATABASE "engkqopenmp"

//--------[ Server ]--------//
#define SERVERNAME  "Grand Theft Auto DownTown"
#define GAMEMODES   "GDT"
#define REVISION    "v0.0.2b"
#define LANGUAGE "Indonesia"

//--------[ Player Create ]--------//
#define DEFAULT_POS_X 1642.14
#define DEFAULT_POS_Y -2333.15
#define DEFAULT_POS_Z 13.54
#define DEFAULT_POS_A 0.0

//--------[ Player Spawn - Pelabuhan ]--------//
#define SPAWN_PELABUHAN_X 1642.14
#define SPAWN_PELABUHAN_Y -2333.15
#define SPAWN_PELABUHAN_Z 13.54
#define SPAWN_PELABUHAN_A 0.0

//--------[ Player Spawn - Bandara ]--------//
#define SPAWN_BANDARA_X -2474.15
#define SPAWN_BANDARA_Y -1666.88
#define SPAWN_BANDARA_Z 33.48
#define SPAWN_BANDARA_A 269.62

//--------[ Macro ]--------//
#define EngkqC:%0(%1) forward %0(%1); public %0(%1)
#define Forex(%0,%1) for(new %0 = 0; %0 < %1; %0++)

//--------[ SendMessage ]--------//
#define SendNearbyMessage SendProximityMessage															// Me Action.
#define MeAction(%0,%1,%2) \
	new EngkqMe[144]; format(EngkqMe, sizeof(EngkqMe), %1, %2); SendNearbyMessage(%0, 20.0, COLOR_PURPLE, EngkqMe)	

#define SendUsageMessage(%1,%2) \
	SendClientMessage(%1, -1, "{33CCFF}USAGE: {FFFFFF}"%2)

#define Servers(%1,%2) \
	SendClientMessageEx(%1, -1, "{FFFF00}SERVERS: {FFFFFF}"%2)

#define AdminCMD(%0,%1) \
    SendClientMessage(%0, TOMATO, "AdmCmd: {FFFFFF}" %1)

#define Success(%0,%1) \
    SendClientMessage(%0, -1, "{00FF00}SUCCESS: {FFFFFF}%s", %1)										// Pesan Sukses Otomatis Berwarna Hijau, Usage (SendSuccessMessage(playerid, Test);).

#define Error(%0,%1) \
    SendClientMessage(%0, -1, "{FF0000}ERROR: {FFFFFF}%s", %1)											// Pesan Error Otomatis Berwarna Merah, Usage (SendErrorMessage(playerid, Test);).	

#define Info(%0,%1) \
	SendClientMessage(%0, -1, "{33CCFF}INFO: {FFFFFF}%s", %1)										// Pesan Info Otomatis Berwarna Biru, Usage (SendInfoMessage(playerid, Test);).

#define Syntax(%0,%1) \
	SendClientMessage(%0, -1, "{FFFF00}SYNTAX: {FFFFFF}%s", %1)										// Pesan Syntax Otomatis Berwarna Kuning, Usage (SendSyntaxMessage(playerid, Test);).

#define White(%0,%1) \
	SendClientMessage(%0, -1, %1)																		// Pesan Otomatis Berwarna Putih, Usage (SendWhiteMessage(playerid, Test);).

#define PermissionError(%0) \
	SendClientMessage(%0, COLOR_RED, "ERROR: {FFFFFF}Kamu tidak memiliki akses untuk commands ini!")	// Sudah Tergabung Dalam Makro CheckAdmin.
