#include <YSI_Coding\y_hooks>

main()
{
	SendRconCommand("game.mode %s(%s)", GAMEMODES, REVISION);
	SendRconCommand("gamemode.language %s", LANGUAGE);
}

// Disaat gamemode start
hook OnGameModeInit()
{
	ConnectMysql(HOST, USERNAME, PASSWORD, DATABASE);
	
	//--------[ Create Textdraw ]--------//
	CreateGlobalTextdraw();

	//--------[ Others ]--------//
	DisableInteriorEnterExits();
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
	CreateObjectsServers();
	Iter_Init(PlayerVehicle);

	LoaderServers();
	return 1;
}

hook OnGameModeExit()
{
	mysql_close(g_SQL);
	return 1;
}

hook OnPlayerConnect(playerid)
{
	ResetValueVariable(playerid);
	AccountCheck(playerid);
	
	// textdraw server
	TextDrawShowForPlayer(playerid, EngkqNameServers[0]);
	TextDrawShowForPlayer(playerid, EngkqNameServers[1]);
	TextDrawShowForPlayer(playerid, EngkqNameServers[2]);

	if (IsPlayerUsingOfficialClient(playerid))
        pDataEngkq[playerid][isOfficialClient] = true;

	new ip[16];
	GetPlayerIp(playerid, ip, sizeof(ip));
	SendClientMessage(playerid, COLOR_WHITE, "IP : %s", ip);

	RemoveBuildingServers(playerid);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	g_MysqlRaceCheck[playerid]++;
	
	UpdateDataPlayer(playerid);
	SetPlayerName(playerid, pDataEngkq[playerid][pUCP]);

	pDataEngkq[playerid][IsEngkqLogin] = false;
	return 1;
}

hook OnPlayerRequestClass(playerid, classid)
{
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	return 1;
}

hook OnPlayerDeath(playerid, killerid, WEAPON:reason)
{
	return 1;
}

hook OnPlayerExitVehicle(playerid, vehicleid)
{
	return 1;
}

hook OnPlayerRequestSpawn(playerid)
{
	if(!pDataEngkq[playerid][IsEngkqLogin])
	{
		SendClientMessage(playerid, COLOR_ERROR, "ERROR: Kamu tidak diizinkan menekan tombol spawn!");
		return 0;
	}
	return 1;
}

hook OnPlayerText(playerid, text[])
{
	new msg[144];
	format(msg, sizeof(msg), "%s [%d] : %s", pDataEngkq[playerid][pName], playerid, text);

	new Float:posX,
		Float:posY,
		Float:posZ;

	GetPlayerPos(playerid, posX, posY, posZ);

	foreach(new i : Player)
	{
		if(IsPlayerInRangeOfPoint(i, 20.0, posX, posY, posZ))
		{
			SendClientMessage(i, COLOR_WHITE, msg);
		}
	}

	return 0;
}

hook OnPlayerEnterCheckpoint(playerid)
{
	return 1;
}

hook OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
  if (result == -1)
  {
    SendClientMessage(playerid, COLOR_SERVER, "SERVER: {ffffff}Command tidak tersedia, /help untuk melihat command yang tersedia");
    return 0;
  }

  return 1;
}

hook OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	SetPlayerPosFindZ(playerid, Float:fX, Float:fY, Float:fZ);
	SendClientMessage(playerid, COLOR_SERVER, "SERVER: Kamu melakukan teleport melalui map!");
	return 1;
}

public OnPlayerSelectEModel(playerid, extraid, index, modelid)
{
    if(extraid == 1 || extraid == 2)
    {
        pDataEngkq[playerid][pSkin] = modelid;
        SetPlayerSkin(playerid, modelid);
        Success(playerid, "Skin berhasil dipilih!");
        CreateCharacterAccount(playerid);
    }
    return 1;
}