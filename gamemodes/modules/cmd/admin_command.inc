// Admin Command System (FiveM Style)

// Staff Chat
CMD:a(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 1)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    if(isnull(params))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/a <pesan>");

    new str[144];
    format(str, sizeof(str), "{FFD700}[STAFF] {ffffff}%s: %s", pDataEngkq[playerid][pName], params);
    
    foreach(new i : Player)
    {
        if(pDataEngkq[i][pAdmin] >= 1)
        {
            SendClientMessage(i, COLOR_WHITE, str);
        }
    }
    return 1;
}

// Teleportation
CMD:goto(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 1)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId;
    if(sscanf(params, "u", targetId))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/goto <id/name>");

    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi.");

    new Float:x, Float:y, Float:z;
    GetPlayerPos(targetId, x, y, z);
    SetPlayerPos(playerid, x, y + 1.0, z);
    SetPlayerInterior(playerid, GetPlayerInterior(targetId));
    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetId));

    SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu telah teleport ke player.");
    return 1;
}

CMD:gethere(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 1)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId;
    if(sscanf(params, "u", targetId))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/gethere <id/name>");

    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi.");

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    SetPlayerPos(targetId, x, y + 1.0, z);
    SetPlayerInterior(targetId, GetPlayerInterior(playerid));
    SetPlayerVirtualWorld(targetId, GetPlayerVirtualWorld(playerid));

    SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu telah menarik player ke lokasimu.");
    return 1;
}

// Freeze Management
CMD:freeze(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 1)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId;
    if(sscanf(params, "u", targetId))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/freeze <id/name>");

    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi.");

    TogglePlayerControllable(targetId, false);
    SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu telah membekukan player.");
    SendClientMessage(targetId, COLOR_ERROR, "INFO: {ffffff}Kamu telah dibekukan oleh admin.");
    return 1;
}

CMD:unfreeze(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 1)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId;
    if(sscanf(params, "u", targetId))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/unfreeze <id/name>");

    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi.");

    TogglePlayerControllable(targetId, true);
    SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu telah melepas bekukan player.");
    SendClientMessage(targetId, COLOR_SUCCESS, "INFO: {ffffff}Kamu telah dilepas bekukan oleh admin.");
    return 1;
}

// Slap & Revive
CMD:slap(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 2)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId;
    if(sscanf(params, "u", targetId))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/slap <id/name>");

    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi.");

    new Float:x, Float:y, Float:z;
    GetPlayerPos(targetId, x, y, z);
    SetPlayerPos(targetId, x, y, z + 5.0);
    PlayerPlaySound(targetId, 1130, x, y, z);

    SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu telah menampar player.");
    return 1;
}

CMD:revive(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 2)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId;
    if(sscanf(params, "u", targetId))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/revive <id/name>");

    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi.");

    SetPlayerHealth(targetId, 100.0);
    // Jika ada system down/injured, reset disini
    SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu telah me-revive player.");
    SendClientMessage(targetId, COLOR_SUCCESS, "INFO: {ffffff}Kamu telah di-revive oleh admin.");
    return 1;
}

// Ban System
CMD:ban(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 4)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId, reason[128];
    if(sscanf(params, "us[128]", targetId, reason))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/ban <id/name> <alasan>");

    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi.");

    new query[512];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO bans (username, ucp, admin, reason, ban_date) VALUES ('%e', '%e', '%e', '%e', %d)", 
        pDataEngkq[targetId][pName], pDataEngkq[targetId][pUCP], pDataEngkq[playerid][pName], reason, gettime());
    mysql_tquery(g_SQL, query);

    new str[256];
    format(str, sizeof(str), "SERVER: {ffffff}%s telah di-ban permanen oleh admin %s. Alasan: %s", pDataEngkq[targetId][pName], pDataEngkq[playerid][pName], reason);
    SendClientMessageToAll(COLOR_ERROR, str);

    KickEx(targetId);
    return 1;
}

// Set Admin
CMD:setadmin(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 5)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId, level;
    if(sscanf(params, "ud", targetId, level))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/setadmin <id/name> <level (0-5)>");

    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi.");

    pDataEngkq[targetId][pAdmin] = level;
    
    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE ucp SET admin = %d WHERE ucp_name = '%e'", level, pDataEngkq[targetId][pUCP]);
    mysql_tquery(g_SQL, query);

    new str[128];
    format(str, sizeof(str), "SUCCESS: {ffffff}Berhasil mengubah level admin %s menjadi %d.", pDataEngkq[targetId][pName], level);
    SendClientMessage(playerid, COLOR_SUCCESS, str);

    format(str, sizeof(str), "INFO: {ffffff}Admin %s telah mengubah level admin kamu menjadi %d.", pDataEngkq[playerid][pName], level);
    SendClientMessage(targetId, COLOR_INFO, str);
    return 1;
}

CMD:addslot(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 5)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId, amount;
    if(sscanf(params, "ud", targetId, amount))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/addslot <id/name> <amount>");

    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi.");

    pDataEngkq[targetId][pCharSlots] = amount;
    if(pDataEngkq[targetId][pCharSlots] > 10) // Limit total slots
        pDataEngkq[targetId][pCharSlots] = 10;
    
    if(pDataEngkq[targetId][pCharSlots] < 1) // Minimum 1 slot
        pDataEngkq[targetId][pCharSlots] = 1;

    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE ucp SET char_slots = %d WHERE ucp_name = '%e'", pDataEngkq[targetId][pCharSlots], pDataEngkq[targetId][pUCP]);
    mysql_tquery(g_SQL, query);

    new str[128];
    format(str, sizeof(str), "SUCCESS: {ffffff}Berhasil mengubah slot %s menjadi %d.", pDataEngkq[targetId][pName], pDataEngkq[targetId][pCharSlots]);
    SendClientMessage(playerid, COLOR_SUCCESS, str);

    format(str, sizeof(str), "INFO: {ffffff}Admin %s telah mengubah total slot karaktermu menjadi %d.", pDataEngkq[playerid][pName], pDataEngkq[targetId][pCharSlots]);
    SendClientMessage(targetId, COLOR_INFO, str);
    return 1;
}

CMD:setlevel(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 5)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId, 
        amountLevel;
    if(sscanf(params, "ud", targetId, amountLevel)) 
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/setlevel <id> <level>");

    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi kedalam server!");
    
    SetPlayerScore(targetId, amountLevel);
    pDataEngkq[targetId][pLevel] = amountLevel;
    // info untuk player
    SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu berhasil mengubah level dari player %s ke level %d", pDataEngkq[targetId][pName], amountLevel);
    // info untuk target
    SendClientMessage(targetId, COLOR_INFO, "INFO: {ffffff}Level kamu diubah oleh %s ke level %d", pDataEngkq[playerid][pName], amountLevel);
    return 1;
}

CMD:setinterior(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 5)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId, 
        interior;

    if(sscanf(params, "ud", targetId, interior)) 
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/setinterior <id> <interior>");
    
    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi kedalam server!");
    
    SetPlayerInterior(playerid, interior);
    pDataEngkq[targetId][pInterior] = interior;

    // info player
    SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu telah mengubah interior dari %s ke %d", pDataEngkq[targetId][pName], interior);
    // info untuk target
    SendClientMessage(playerid, COLOR_INFO, "INFO: {ffffff}Interior kamu telah diubah oleh %s ke %d", pDataEngkq[playerid][pName], interior);
    return 1;
}

CMD:setskin(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 5)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId,
        skinId;
    
    if(sscanf(params, "ud", targetId, skinId))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/setskin <id> <skinid>");

    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi kedalam server!");
    
    if(skinId < 0 || skinId > 311)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Id skin tidak boleh kurang dari 0 atau lebih dari 311!");
    
    SetPlayerSkin(targetId, skinId);
    pDataEngkq[targetId][pSkin] = skinId;

    // info untuk player
    SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu telah mengubah skin dari %s ke id %d", pDataEngkq[targetId][pName], skinId);
    // info ubtuj target
    SendClientMessage(playerid, COLOR_INFO, "INFO: {ffffff}Skin kamu telah diubah oleh %s ke id %d", pDataEngkq[playerid][pName], skinId);
    return 1;
}

CMD:setvw(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 5)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId,
        vwId;

    if(sscanf(params, "ud", targetId, vwId))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/setvw <id> <vw>");
    
    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi kedalam server!");
    
    SetPlayerVirtualWorld(targetId, vwId);
    pDataEngkq[targetId][pVirtual_World] = vwId;

    // info untuk player
    SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu telah mengubah virtual world dari %s ke id %d", pDataEngkq[targetId][pName], vwId);
    // info ubtuj target
    SendClientMessage(playerid, COLOR_INFO, "INFO: {ffffff}Virtual world kamu telah diubah oleh %s ke id %d", pDataEngkq[playerid][pName], vwId);
    return 1;
}

CMD:addmoney(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 5)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId, 
        amountMoney;

    if(sscanf(params, "ui", targetId, amountMoney)) 
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/addmoney <id> <jumlah>");

    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi kedalam server!");

    if(amountMoney < 0 || amountMoney > 10000000) 
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Jumlah uang tidak boleh kurang 0 atau lebih dari 10000000");

    GivePlayerMoneyEx(targetId, amountMoney);
    // info untuk player
    SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu berhasil menambah uang dari %s sebanyak %d", pDataEngkq[targetId][pName], amountMoney);
    // info untuk target 
    SendClientMessage(targetId, COLOR_INFO, "INFO: {ffffff}Kamu mendapatkan uang dari %s sebanyak %d", pDataEngkq[playerid][pName], amountMoney);
    return 1;
}

CMD:kick(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 5)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId,
        reasonKick[64];

    if(sscanf(params, "us[64]", targetId, reasonKick)) 
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/kick <id> <alasan>");

    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi kedalam server");

    KickEx(targetId);
    // info untuk player
    SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu telah menendang %s keluar server dengan alasan %s", pDataEngkq[targetId][pName], reasonKick);

    // info untuk target
    SendClientMessage(targetId, COLOR_INFO, "INFO: {ffffff}Kamu telah ditendang keluar server oleh %s dengan alasan %s", pDataEngkq[playerid][pName], reasonKick);
    // printf("Player id %d telah dikick dari server dengan alasan %s", targetId, reasonKick);
    return 1;
}

CMD:sethp(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 5)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId, 
        Float:healthPlayer;

    if(sscanf(params, "uf", targetId, healthPlayer)) 
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/sethp <id> <jumlah>");

    if(!IsPlayerConnected(targetId)) 
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi kedalam server");

    if(healthPlayer > 100.00 || healthPlayer < 0) 
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Health tidak bisa kurang dari 0 atau lebih dari 100!");

    SetPlayerHealth(targetId, healthPlayer);
    // info untuk player
    SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu telah mengubah health dari %s sebanyak %.2f", pDataEngkq[targetId][pName], healthPlayer);

    // info untuk target
    SendClientMessage(targetId, COLOR_INFO, "INFO: {ffffff}Health kamu telah diubah oleh %s sebanyak %.2f", pDataEngkq[playerid][pName], healthPlayer);
    return 1;
}

CMD:setarmor(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 5)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");

    new targetId,
        Float:amountArmour;

    if(sscanf(params, "uf", targetId, amountArmour))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/setarmor <id> <jumlah>");

    if(!IsPlayerConnected(targetId))
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Player tidak terkoneksi kedalam server");

    if(amountArmour < 0 || amountArmour > 100.00) 
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Armor tidak bisa kurang dari 0 atau lebih dari 100!");
    
    SetPlayerArmour(targetId, amountArmour);
    // info untuk player
    SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu telah mengubah armor dari %s sebanyak %.2f", pDataEngkq[targetId][pName], amountArmour);

    // info untuk target
    SendClientMessage(targetId, COLOR_INFO, "INFO: {ffffff}Armor kamu telah diubah oleh %s sebanyak %.2f", pDataEngkq[playerid][pName], amountArmour);
    return 1;
}

CMD:gotopos(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 5)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Kamu tidak memiliki akses untuk perintah ini.");
        
    new Float:posX,
        Float:posY,
        Float:posZ;

    if(sscanf(params, "fff", posX, posY, posZ))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/gotopos <X> <Y> <Z>");

    SetPlayerPos(playerid, posX, posY, posZ);
    SendClientMessage(playerid, COLOR_SERVER, "SERVER: {ffffff}Anda telah teleport ke koordinat X:%.4f Y:%.4f Z:%.4f", posX, posY, posZ);
    return 1;
}