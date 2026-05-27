CMD:createdoor(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 3)
        return PermissionError(playerid);

	new did = Iter_Free(Doors), mstr[128], engkqquery[248];
	if(did == -1) return Error(playerid, "You cant create more door!");
	new name[128];
	if(sscanf(params, "s[128]", name)) return SendClientMessage(playerid, COLOR_WHITE, "[USAGE]: /createdoor [name]");
	format(dData[did][dName], 128, name);
	GetPlayerPos(playerid, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ]);
	GetPlayerFacingAngle(playerid, dData[did][dExtposA]);
	dData[did][dExtvw] = GetPlayerVirtualWorld(playerid);
	dData[did][dExtint] = GetPlayerInterior(playerid);
	format(dData[did][dPass], 32, "");
	dData[did][dIcon] = 19130;
	dData[did][dLocked] = 0;
	dData[did][dAdmin] = 0;
	dData[did][dVip] = 0;
	dData[did][dFaction] = 0;
	dData[did][dFamily] = -1;
	dData[did][dGarage] = 0;
	dData[did][dCustom] = 0;
	dData[did][dIntvw] = 0;
	dData[did][dIntint] = 0;
	dData[did][dIntposX] = 0;
	dData[did][dIntposY] = 0;
	dData[did][dIntposZ] = 0;
	dData[did][dIntposA] = 0;
	dData[did][dMapIcon] = 0;
	dData[did][dMapIconID] = -1;
	
	format(mstr,sizeof(mstr),"[ID: %d]\n{FFFFFF}%s\n{FFFFFF}Press {FF0000}ENTER {FFFFFF}to enter", did, dData[did][dName]);
	dData[did][dPickupext] = CreateDynamicPickup(19130, 23, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ], dData[did][dExtvw], dData[did][dExtint], -1, 50);
	dData[did][dLabelext] = CreateDynamic3DTextLabel( mstr, COLOR_YELLOW, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ]+0.35, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, dData[did][dExtvw], dData[did][dExtint]);
    Doors_Updatelabel(did);
	Iter_Add(Doors, did);

	mysql_format(g_SQL, engkqquery, sizeof(engkqquery), "INSERT INTO doors SET ID=%d, extvw=%d, extint=%d, extposx=%f, extposy=%f, extposz=%f, extposa=%f, name='%s'", did, dData[did][dExtvw], dData[did][dExtint], dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ], dData[did][dExtposA], name);
	mysql_tquery(g_SQL, engkqquery, "OnDoorsCreated", "ii", playerid, did);
	return 1;
}

CMD:gotodoor(playerid, params[])
{
	new did;
	if(pDataEngkq[playerid][pAdmin] < 3)
        return PermissionError(playerid);
		
	if(sscanf(params, "d", did))
		return SendClientMessage(playerid, COLOR_WHITE, "[USAGE]: /gotodoor [id]");
	if(!Iter_Contains(Doors, did)) return Error(playerid, "The doors you specified ID of doesn't exist.");
	SetPlayerPosition(playerid, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ], dData[did][dExtposA]);
    SetPlayerInterior(playerid, dData[did][dExtint]);
    SetPlayerVirtualWorld(playerid, dData[did][dExtvw]);
	pDataEngkq[playerid][pInDoor] = -1;
	pDataEngkq[playerid][pInHouse] = -1;
	pDataEngkq[playerid][pInBiz] = -1;
	pDataEngkq[playerid][pInFamily] = -1;	
	Servers(playerid, "You has teleport to door id %d", did);
	return 1;
}
CMD:editdoor(playerid, params[])
{
    static
        did,
        type[24],
        string[128];

    if(pDataEngkq[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", did, type, string))
    {
        SendClientMessage(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [name]");
        SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} location, interior, password, name, locked, admin, vip, faction, family, custom, virtual, iconmap");
        return 1;
    }
    if((did < 0 || did >= MAX_DOOR))
        return Error(playerid, "You have specified an invalid entrance ID.");
	if(!Iter_Contains(Doors, did)) return Error(playerid, "The doors you specified ID of doesn't exist.");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ]);
		GetPlayerFacingAngle(playerid, dData[did][dExtposA]);

        dData[did][dExtvw] = GetPlayerVirtualWorld(playerid);
		dData[did][dExtint] = GetPlayerInterior(playerid);
        Doors_Save(did);
		Doors_Updatelabel(did);

        AdminCMD(COLOR_RED, "%s has adjusted the location of entrance ID: %d.", pDataEngkq[playerid][pAdminName], did);
    }
    else if(!strcmp(type, "interior", true))
    {
        GetPlayerPos(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ]);
		GetPlayerFacingAngle(playerid, dData[did][dIntposA]);

        dData[did][dIntvw] = GetPlayerVirtualWorld(playerid);
		dData[did][dIntint] = GetPlayerInterior(playerid);
        Doors_Save(did);
		Doors_Updatelabel(did);

       /*foreach (new i : Player)
        {
            if(pDataEngkq[i][pEntrance] == EntranceData[id][entranceID])
            {
                SetPlayerPos(i, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2]);
                SetPlayerFacingAngle(i, EntranceData[id][entranceInt][3]);

                SetPlayerInterior(i, EntranceData[id][entranceInterior]);
                SetCameraBehindPlayer(i);
            }
        }*/
        AdminCMD(COLOR_RED, "%s has adjusted the interior spawn of entrance ID: %d.", pDataEngkq[playerid][pAdminName], did);
    }
    else if(!strcmp(type, "custom", true))
    {
        new status;

        if(sscanf(string, "d", status))
            return SendClientMessage(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [custom] [0/1]");

        if(status < 0 || status > 1)
            return Error(playerid, "You must specify at least 0 or 1.");

        dData[did][dCustom] = status;
        Doors_Save(did);
		Doors_Updatelabel(did);

        if(status) {
            AdminCMD(COLOR_RED, "%s has enabled custom interior mode for entrance ID: %d.", pDataEngkq[playerid][pAdminName], did);
        }
        else {
            AdminCMD(COLOR_RED, "%s has disabled custom interior mode for entrance ID: %d.", pDataEngkq[playerid][pAdminName], did);
        }
    }
    else if(!strcmp(type, "virtual", true))
    {
        new worldid;

        if(sscanf(string, "d", worldid))
            return SendClientMessage(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [virtual] [interior world]");

        dData[did][dExtvw] = worldid;

        Doors_Save(did);
		Doors_Updatelabel(did);
        AdminCMD(COLOR_RED, "%s has adjusted the virtual of entrance ID: %d to %d.", pDataEngkq[playerid][pAdminName], did, worldid);
    }
    else if(!strcmp(type, "password", true))
    {
        new password[32];

        if(sscanf(string, "s[32]", password))
            return SendClientMessage(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [password] [entrance pass] (use 'none' to disable)");

        if(!strcmp(password, "none", true)) {
            format(dData[did][dPass], 32, "");
        }
        else {
            format(dData[did][dPass], 32, password);
        }
        Doors_Save(did);
		Doors_Updatelabel(did);
        AdminCMD(COLOR_RED, "%s has adjusted the password of entrance ID: %d to %s", pDataEngkq[playerid][pAdminName], did, password);
    }
    else if(!strcmp(type, "locked", true))
    {
        new locked;

        if(sscanf(string, "d", locked))
            return SendClientMessage(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [locked] [locked 0/1]");

        if(locked < 0 || locked > 1)
            return Error(playerid, "Invalid value. Use 0 for unlocked and 1 for locked.");

        dData[did][dLocked] = locked;
        Doors_Save(did);
		Doors_Updatelabel(did);

        if(locked) {
            AdminCMD(COLOR_RED, "%s has locked entrance ID: %d.", pDataEngkq[playerid][pAdminName], did);
        } else {
            AdminCMD(COLOR_RED, "%s has unlocked entrance ID: %d.", pDataEngkq[playerid][pAdminName], did);
        }
    }
    else if(!strcmp(type, "name", true))
    {
        new name[128];

        if(sscanf(string, "s[128]", name))
            return SendClientMessage(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [name] [new name]");

        format(dData[did][dName], 128, ColouredText(name));

        Doors_Save(did);
		Doors_Updatelabel(did);

        AdminCMD(COLOR_RED, "%s has adjusted the name of entrance ID: %d to \"%s\".", pDataEngkq[playerid][pAdminName], did, ColouredText(name));
    }
	else if(!strcmp(type, "admin", true))
    {
        new level;

        if(sscanf(string, "d", level))
            return SendClientMessage(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [admin] [level]");

        if(level < 0 || level > 5)
            return Error(playerid, "Invalid value. Use 0 - 5 for level.");

        dData[did][dAdmin] = level;
        Doors_Save(did);
		Doors_Updatelabel(did);

        AdminCMD(COLOR_RED, "%s has set entrance ID: %d to admin level %d.", pDataEngkq[playerid][pAdminName], did, level);
    }
	else if(!strcmp(type, "vip", true))
    {
        new level;

        if(sscanf(string, "d", level))
            return SendClientMessage(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [VIP] [level]");

        if(level < 0 || level > 3)
            return Error(playerid, "Invalid value. Use 0 - 3 for level.");

        dData[did][dVip] = level;
        Doors_Save(did);
		Doors_Updatelabel(did);

        AdminCMD(COLOR_RED, "%s has set entrance ID: %d to VIP level %d.", pDataEngkq[playerid][pAdminName], did, level);
    }
	else if(!strcmp(type, "faction", true))
    {
        new fid;

        if(sscanf(string, "d", fid))
            return SendClientMessage(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [faction] [faction id]");

        if(fid < 0 || fid > 4)
            return Error(playerid, "Invalid value. Use 0 - 4 for type.");

        dData[did][dFaction] = fid;
        Doors_Save(did);
		Doors_Updatelabel(did);

        AdminCMD(COLOR_RED, "%s has set entrance ID: %d to faction id %d.", pDataEngkq[playerid][pAdminName], did, fid);
    }
	else if(!strcmp(type, "family", true))
    {
        new fid;

        if(sscanf(string, "d", fid))
            return SendClientMessage(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [family] [family id]");

        if(fid < -1 || fid > 9)
            return Error(playerid, "Invalid value. Use -1 - 9 for family id.");

        dData[did][dFamily] = fid;
        Doors_Save(did);
		Doors_Updatelabel(did);

        AdminCMD(COLOR_RED, "%s has set entrance ID: %d to family id %d.", pDataEngkq[playerid][pAdminName], did, fid);
    }
	else if(!strcmp(type, "garage", true))
	{
		new gid;

        if(sscanf(string, "d", gid))
            return SendClientMessage(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [garage] [0 - 1]");

        if(gid < 0 || gid > 1)
            return Error(playerid, "Invalid value! Use 0 to disable, 1 to enable.");
		
		if(gid == 0)
		{
			dData[did][dGarage] = 0;
			AdminCMD(COLOR_RED, "%s has set entrance ID: %d to garage vehicle disable.", pDataEngkq[playerid][pAdminName], did);
		}
		else
		{
			dData[did][dGarage] = 1;
			AdminCMD(COLOR_RED, "%s has set entrance ID: %d to garage vehicle enable.", pDataEngkq[playerid][pAdminName], did);
		}
		Doors_Save(gid);
		Doors_Updatelabel(gid);
	}
	else if(!strcmp(type, "iconmap", true))
	{
		new iconid;
	    if(sscanf(string, "i", iconid))
	    {
	        return SendClientMessage(playerid, COLOR_WHITE, "[USAGE]: /editdoor [id] [iconmap] [iconid (0-63)]");
		}
		if(!(0 <= iconid <= 63))
		{
		    return Error(playerid, "Ikon peta tidak valid..");
		}

		dData[did][dMapIcon] = iconid;

		Doors_Save(did);
		Doors_Updatelabel(did);

	    AdminCMD(COLOR_RED, "%s has set entrance ID: %d to Map Icon id %d.", pDataEngkq[playerid][pAdminName], did, iconid);
	}
	else if(!strcmp(type, "delete", true))
    {
		DestroyDynamic3DTextLabel(dData[did][dLabelext]);
		DestroyDynamicPickup(dData[did][dPickupext]);
		DestroyDynamic3DTextLabel(dData[did][dLabelint]);
		DestroyDynamicPickup(dData[did][dPickupint]);
		DestroyDynamicMapIcon(dData[did][dMapIconID]);
			
		dData[did][dExtposX] = 0;
		dData[did][dExtposY] = 0;
		dData[did][dExtposZ] = 0;
		dData[did][dExtposA] = 0;
		dData[did][dExtvw] = 0;
		dData[did][dExtint] = 0;
		format(dData[did][dPass], 32, "");
		dData[did][dIcon] = 0;
		dData[did][dLocked] = 0;
		dData[did][dAdmin] = 0;
		dData[did][dVip] = 0;
		dData[did][dFaction] = 0;
		dData[did][dFamily] = -1;
		dData[did][dGarage] = 0;
		dData[did][dCustom] = 0;
		dData[did][dIntvw] = 0;
		dData[did][dIntint] = 0;
		dData[did][dIntposX] = 0;
		dData[did][dIntposY] = 0;
		dData[did][dIntposZ] = 0;
		dData[did][dIntposA] = 0;
		dData[did][dMapIconID] = -1;
		dData[did][dMapIcon] = 0;
		
		dData[did][dLabelext] = Text3D: INVALID_3DTEXT_ID;
		dData[did][dLabelint] = Text3D: INVALID_3DTEXT_ID;
		dData[did][dPickupext] = -1;
		dData[did][dPickupint] = -1;
		
		Iter_Remove(Doors, did);
		new equery[128];
		mysql_format(g_SQL, equery, sizeof(equery), "DELETE FROM doors WHERE ID=%d", did);
		mysql_tquery(g_SQL, equery);
        AdminCMD(COLOR_RED, "%s has delete door ID: %d.", pDataEngkq[playerid][pAdminName], did);
	}
    return 1;
}