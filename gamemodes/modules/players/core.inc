ResetValueVariable(playerid)
{
    pDataEngkq[playerid][pID] = -1;
    pDataEngkq[playerid][pName] = EOS;
    pDataEngkq[playerid][pSkin] = 0;
    pDataEngkq[playerid][pMoney] = 0;
    pDataEngkq[playerid][pLevel] = 0;
    pDataEngkq[playerid][pBirthDay] = 0;
    pDataEngkq[playerid][pBirthMonth] = 0;
    pDataEngkq[playerid][pBirthYear] = 0;
    pDataEngkq[playerid][pGender] = -1;

    // bagian login register
    pDataEngkq[playerid][IsPlayersLogin] = false;
    pDataEngkq[playerid][pLoginAttempt] = 0;
    pDataEngkq[playerid][isOfficialClient] = false;
    pDataEngkq[playerid][pVerifyCode] = 0;
    pDataEngkq[playerid][pActivation] = 0;
    pDataEngkq[playerid][pCharSlots] = 1;
    pDataEngkq[playerid][pAdmin] = 0;
    pDataEngkq[playerid][pAdminName] = EOS;
    pDataEngkq[playerid][pLastExit] = 0;
    return 1;
}

Fungsi:OnCharacterDataLoaded(playerid)
{
    ShowInfo(playerid);
    PlayerLoadTime(playerid, "Succes Load Character");

	cache_get_value_name_int(0, "id", pDataEngkq[playerid][pID]);
    if(pDataEngkq[playerid][pID] < 1)
    {
        Error(playerid, "Akun ini tidak terdaftar dalam database");
        KickEx(playerid);
        return 1;
    }

	cache_get_value_name_float(0, "pos_x", pDataEngkq[playerid][pPos][0]);
	cache_get_value_name_float(0, "pos_y", pDataEngkq[playerid][pPos][1]);
	cache_get_value_name_float(0, "pos_z", pDataEngkq[playerid][pPos][2]);
	cache_get_value_name_float(0, "pos_a", pDataEngkq[playerid][pPos][3]);

	cache_get_value_name_int(0, "interior", pDataEngkq[playerid][pInterior]);
	cache_get_value_name_int(0, "virtual_world", pDataEngkq[playerid][pVirtual_World]);
	cache_get_value_name_int(0, "skin", pDataEngkq[playerid][pSkin]);
	cache_get_value_name_int(0, "money", pDataEngkq[playerid][pMoney]);
	cache_get_value_name_int(0, "level", pDataEngkq[playerid][pLevel]);
	cache_get_value_name_int(0, "last_exit", pDataEngkq[playerid][pLastExit]);

    // New fields
	cache_get_value_name_int(0, "weight", pDataEngkq[playerid][pWeight]);
	cache_get_value_name_int(0, "height", pDataEngkq[playerid][pHeight]);
	cache_get_value_name(0, "origin", pDataEngkq[playerid][pOrigin]);

    pDataEngkq[playerid][IsPlayersLogin] = true;
    
    SetSpawnInfo(playerid, NO_TEAM, 
    pDataEngkq[playerid][pSkin], pDataEngkq[playerid][pPos][0], pDataEngkq[playerid][pPos][1], pDataEngkq[playerid][pPos][2], pDataEngkq[playerid][pPos][3],
    WEAPON_FIST, 0, WEAPON_FIST, 0, WEAPON_FIST, 0);
    SpawnPlayer(playerid);
    GetPlayerNameEx(playerid);
    
    SetPlayerInterior(playerid, pDataEngkq[playerid][pInterior]);
    SetPlayerVirtualWorld(playerid, pDataEngkq[playerid][pVirtual_World]);
    GivePlayerMoney(playerid, pDataEngkq[playerid][pMoney]);
    SetPlayerScore(playerid, pDataEngkq[playerid][pLevel]);
    printf(">> Character Data Loaded for PlayerID: %d, Name: %s", playerid, pDataEngkq[playerid][pName]);
	return 1;
}

stock UpdateDataPlayer(playerid)
{
	if(!pDataEngkq[playerid][IsPlayersLogin]) return 1;

	GetPlayerPos(playerid, pDataEngkq[playerid][pPos][0], pDataEngkq[playerid][pPos][1], pDataEngkq[playerid][pPos][2]);
	GetPlayerFacingAngle(playerid, pDataEngkq[playerid][pPos][3]);
	pDataEngkq[playerid][pInterior] = GetPlayerInterior(playerid);
	pDataEngkq[playerid][pVirtual_World] = GetPlayerVirtualWorld(playerid);
	pDataEngkq[playerid][pSkin] = GetPlayerSkin(playerid);
	pDataEngkq[playerid][pMoney] = GetPlayerMoney(playerid);
	pDataEngkq[playerid][pLevel] = GetPlayerScore(playerid);

	pDataEngkq[playerid][pLastExit] = gettime();
	new query[500];
	mysql_format(g_SQL, query, sizeof(query), "UPDATE users SET pos_x = %f, pos_y = %f, pos_z = %f, pos_a = %f,\
    interior = %d, virtual_world = %d,\
    skin = %d, money = %d, level = %d,\
    last_exit = %d \
    WHERE id = %d LIMIT 1",
	pDataEngkq[playerid][pPos][0], pDataEngkq[playerid][pPos][1], pDataEngkq[playerid][pPos][2], pDataEngkq[playerid][pPos][3], 
    pDataEngkq[playerid][pInterior], pDataEngkq[playerid][pVirtual_World], 
	pDataEngkq[playerid][pSkin], pDataEngkq[playerid][pMoney], pDataEngkq[playerid][pLevel],
	pDataEngkq[playerid][pLastExit], 
    pDataEngkq[playerid][pID]);
	mysql_tquery(g_SQL, query);
    printf(">> Character Data Updated for PlayerID: %d, Name: %s", playerid, pDataEngkq[playerid][pName]);

    new ucpQuery[150];
    mysql_format(g_SQL, ucpQuery, sizeof(ucpQuery), "UPDATE ucp SET adminname = '%e' WHERE ucp_name = '%e' LIMIT 1",
        pDataEngkq[playerid][pAdminName], pDataEngkq[playerid][pUCP]
    );
    mysql_tquery(g_SQL, ucpQuery);
	return 1;
}