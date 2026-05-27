#include <YSI_Coding\y_hooks>

Doors_Save(id)
{
	mysql_format(handle, query, sizeof(query), "UPDATE doors SET name='%s', password='%s', icon='%d', locked='%d', admin='%d', vip='%d', faction='%d', family='%d', garage='%d', custom='%d', extvw='%d', extint='%d', extposx='%f', extposy='%f', extposz='%f', extposa='%f', intvw='%d', intint='%d', intposx='%f', intposy='%f', intposz='%f', intposa='%f', mapicon='%d' WHERE ID='%d'",
	dData[id][dName], dData[id][dPass], dData[id][dIcon], dData[id][dLocked], dData[id][dAdmin], dData[id][dVip], dData[id][dFaction], dData[id][dFamily], dData[id][dGarage], dData[id][dCustom], dData[id][dExtvw], dData[id][dExtint], dData[id][dExtposX], dData[id][dExtposY], dData[id][dExtposZ], dData[id][dExtposA], dData[id][dIntvw], dData[id][dIntint],
	dData[id][dIntposX], dData[id][dIntposY], dData[id][dIntposZ], dData[id][dIntposA], dData[id][dMapIcon], id);
	mysql_tquery(handle, query);
	return 1;
}

Doors_Updatelabel(id)
{
	if(id != -1)
	{
		if(IsValidDynamic3DTextLabel(dData[id][dLabelext]))
            DestroyDynamic3DTextLabel(dData[id][dLabelext]);

        if(IsValidDynamicPickup(dData[id][dPickupext]))
            DestroyDynamicPickup(dData[id][dPickupext]);

        if(IsValidDynamic3DTextLabel(dData[id][dLabelint]))
            DestroyDynamic3DTextLabel(dData[id][dLabelint]);

        if(IsValidDynamicPickup(dData[id][dPickupint]))
            DestroyDynamicPickup(dData[id][dPickupint]);
		
		if(IsValidDynamicMapIcon(dData[id][dMapIconID]))
			DestroyDynamicMapIcon(dData[id][dMapIconID]);
		
		if(dData[id][dGarage] == 1)
		{
			new mstr[512];
			format(mstr,sizeof(mstr),"[ID: %d]\n{FFFFFF}%s\n{FFFFFF}Press {FF0000}Y {FFFFFF}to enter", id, dData[id][dName]);
			dData[id][dPickupext] = CreateDynamicPickup(19130, 23, dData[id][dExtposX], dData[id][dExtposY], dData[id][dExtposZ], dData[id][dExtvw], dData[id][dExtint], -1, 50);
			dData[id][dLabelext] = CreateDynamic3DTextLabel(mstr, COLOR_YELLOW, dData[id][dExtposX], dData[id][dExtposY], dData[id][dExtposZ]+0.35, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, dData[id][dExtvw], dData[id][dExtint]);
		}
		else
		{
			new mstr[512];
			format(mstr,sizeof(mstr),"[ID: %d]\n{FFFFFF}%s\n{FFFFFF}Press {FF0000}ENTER {FFFFFF}to enter", id, dData[id][dName]);
			dData[id][dPickupext] = CreateDynamicPickup(19130, 23, dData[id][dExtposX], dData[id][dExtposY], dData[id][dExtposZ], dData[id][dExtvw], dData[id][dExtint], -1, 50);
			dData[id][dLabelext] = CreateDynamic3DTextLabel(mstr, COLOR_YELLOW, dData[id][dExtposX], dData[id][dExtposY], dData[id][dExtposZ]+0.35, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, dData[id][dExtvw], dData[id][dExtint]);
		}
		
        if(dData[id][dIntposX] != 0.0 && dData[id][dIntposY] != 0.0 && dData[id][dIntposZ] != 0.0)
        {
			if(dData[id][dGarage] == 1)
			{
				new mstr[512];
				format(mstr,sizeof(mstr),"[ID: %d]\n{FFFFFF}%s\n{FFFFFF}Press {FF0000}Y {FFFFFF}to exit", id, dData[id][dName]);

				dData[id][dLabelint] = CreateDynamic3DTextLabel(mstr, COLOR_YELLOW, dData[id][dIntposX], dData[id][dIntposY], dData[id][dIntposZ]+0.7, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, dData[id][dIntvw], dData[id][dIntint]);
				dData[id][dPickupint] = CreateDynamicPickup(19130, 23, dData[id][dIntposX], dData[id][dIntposY], dData[id][dIntposZ], dData[id][dIntvw], dData[id][dIntint], -1, 50);
			}
			else
			{
				new mstr[512];
				format(mstr,sizeof(mstr),"[ID: %d]\n{FFFFFF}%s\n{FFFFFF}Press {FF0000}ENTER {FFFFFF}to exit", id, dData[id][dName]);

				dData[id][dLabelint] = CreateDynamic3DTextLabel(mstr, COLOR_YELLOW, dData[id][dIntposX], dData[id][dIntposY], dData[id][dIntposZ]+0.7, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, dData[id][dIntvw], dData[id][dIntint]);
				dData[id][dPickupint] = CreateDynamicPickup(19130, 23, dData[id][dIntposX], dData[id][dIntposY], dData[id][dIntposZ], dData[id][dIntvw], dData[id][dIntint], -1, 50);
			}
		}

		if(dData[id][dMapIcon])
		{
		    dData[id][dMapIconID] = CreateDynamicMapIcon(dData[id][dExtposX], dData[id][dExtposY], dData[id][dExtposZ], dData[id][dMapIcon], 0, .worldid = dData[id][dExtvw], .interiorid = dData[id][dExtint]);
		}
	}
}

Fungsi: OnDoorsCreated(playerid, id)
{
	Doors_Save(id);
	Doors_Updatelabel(id);
	Servers(playerid, "Door [%d] berhasil di buat!", id);
	return 1;
}

Fungsi: LoadDoors()
{
    new rows = cache_num_rows();
 	if(rows)
  	{
   		new did, name[128], password[128];
		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", did);
	    	cache_get_value_name(i, "name", name);
			format(dData[did][dName], 128, name);
		    cache_get_value_name(i, "password", password);
			format(dData[did][dPass], 128, password);
		    cache_get_value_name_int(i, "icon", dData[did][dIcon]);
			cache_get_value_name_int(i, "mapicon", dData[did][dMapIcon]);
		    cache_get_value_name_int(i, "locked", dData[did][dLocked]);
		    cache_get_value_name_int(i, "admin", dData[did][dAdmin]);
		    cache_get_value_name_int(i, "vip", dData[did][dVip]);
		    cache_get_value_name_int(i, "faction", dData[did][dFaction]);
		    cache_get_value_name_int(i, "family", dData[did][dFamily]);
			cache_get_value_name_int(i, "garage", dData[did][dGarage]);
		    cache_get_value_name_int(i, "custom", dData[did][dCustom]);
		    cache_get_value_name_int(i, "extvw", dData[did][dExtvw]);
		    cache_get_value_name_int(i, "extint", dData[did][dExtint]);
		    cache_get_value_name_float(i, "extposx", dData[did][dExtposX]);
			cache_get_value_name_float(i, "extposy", dData[did][dExtposY]);
			cache_get_value_name_float(i, "extposz", dData[did][dExtposZ]);
			cache_get_value_name_float(i, "extposa", dData[did][dExtposA]);
			cache_get_value_name_int(i, "intvw", dData[did][dIntvw]);
			cache_get_value_name_int(i, "intint", dData[did][dIntint]);
			cache_get_value_name_float(i, "intposx", dData[did][dIntposX]);
			cache_get_value_name_float(i, "intposy", dData[did][dIntposY]);
			cache_get_value_name_float(i, "intposz", dData[did][dIntposZ]);
			cache_get_value_name_float(i, "intposa", dData[did][dIntposA]);
			dData[did][dMapIconID] = -1;

			
			Iter_Add(Doors, did);
			Doors_Updatelabel(did);
	    }
	    printf("[DATABASE]: %d Door has been Loaded.", rows);
	}
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED( KEY_FIRE ))
    {
        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsPlayerInAnyVehicle(playerid))
        {
            foreach(new did : Doors)
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.8, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ]))
                {
                    if(dData[did][dGarage] == 1)
                    {
                        if(dData[did][dIntposX] == 0.0 && dData[did][dIntposY] == 0.0 && dData[did][dIntposZ] == 0.0)
                            return SendErrorMessage(playerid, "Interior entrance masih kosong, atau tidak memiliki interior.");

                        if(dData[did][dLocked])
                            return SendErrorMessage(playerid, "This entrance is locked at the moment.");

                        if(dData[did][dFaction] > 0)
                        {
                            if(dData[did][dFaction] != pDataEngkq[playerid][pFaction])
                                return SendErrorMessage(playerid, "This door only for faction.");
                        }
                        if(dData[did][dFamily] > 0)
                        {
                            if(dData[did][dFamily] != pDataEngkq[playerid][pFamily])
                                return SendErrorMessage(playerid, "This door only for family.");
                        }

                        if(dData[did][dVip] > pDataEngkq[playerid][pVip])
                            return SendErrorMessage(playerid, "Your VIP level not enough to enter this door.");

                        if(dData[did][dAdmin] > pDataEngkq[playerid][pAdminLevel])
                            return SendErrorMessage(playerid, "Your admin level not enough to enter this door.");

                        if(strlen(dData[did][dPass]))
                        {
                            new params[256];
                            if(sscanf(params, "s[256]", params)) return SendInfoMessage(playerid, "Usage: /enter [password]");
                            if(strcmp(params, dData[did][dPass])) return SendErrorMessage(playerid, "Invalid door password.");

                            if(dData[did][dCustom])
                            {
                                SetVehiclePosition(playerid, GetPlayerVehicleID(playerid), dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
                                LoadingObject(playerid);
                            }
                            else
                            {
                                SetVehiclePosition(playerid, GetPlayerVehicleID(playerid), dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
                                LoadingObject(playerid);
                            }
                            pDataEngkq[playerid][pInDoor] = did;
                            LoadingObject(playerid);
                            SetPlayerInterior(playerid, dData[did][dIntint]);
                            SetPlayerVirtualWorld(playerid, dData[did][dIntvw]);
                            SetCameraBehindPlayer(playerid);
                            SetTimerEx("DrugEffectGone", 3000, false, "i", playerid);
                        }
                        else
                        {
                            if(dData[did][dCustom])
                            {
                                SetVehiclePosition(playerid, GetPlayerVehicleID(playerid), dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
                                LoadingObject(playerid);
                            }
                            else
                            {
                                SetVehiclePosition(playerid, GetPlayerVehicleID(playerid), dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
                                LoadingObject(playerid);
                            }
                            pDataEngkq[playerid][pInDoor] = did;
                            LoadingObject(playerid);
                            SetPlayerInterior(playerid, dData[did][dIntint]);
                            SetPlayerVirtualWorld(playerid, dData[did][dIntvw]);
                            SetCameraBehindPlayer(playerid);
                            SetTimerEx("DrugEffectGone", 3000, false, "i", playerid);
                        }
                    }
                }
                if(IsPlayerInRangeOfPoint(playerid, 2.8, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ]))
                {
                    if(dData[did][dGarage] == 1)
                    {
                        if(dData[did][dFaction] > 0)
                        {
                            if(dData[did][dFaction] != pDataEngkq[playerid][pFaction])
                                return SendErrorMessage(playerid, "This door only for faction.");
                        }

                        if(dData[did][dCustom])
                        {
                            SetVehiclePosition(playerid, GetPlayerVehicleID(playerid), dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ], dData[did][dExtposA]);
                        }
                        else
                        {
                            SetVehiclePosition(playerid, GetPlayerVehicleID(playerid), dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ], dData[did][dExtposA]);
                        }
                        pDataEngkq[playerid][pInDoor] = -1;
                        SetPlayerInterior(playerid, dData[did][dExtint]);
                        SetPlayerVirtualWorld(playerid, dData[did][dExtvw]);
                        SetCameraBehindPlayer(playerid);
                    }
                }
            }
        }
    }
    if(PRESSED(KEY_SECONDARY_ATTACK))
    {
        foreach(new did : Doors)
        {
            if(IsPlayerInRangeOfPoint(playerid, 2.8, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ]))
            {
                if(dData[did][dIntposX] == 0.0 && dData[did][dIntposY] == 0.0 && dData[did][dIntposZ] == 0.0)
                    return SendErrorMessage(playerid, "Interior entrance masih kosong, atau tidak memiliki interior.");

                if(dData[did][dLocked])
                    return SendErrorMessage(playerid, "This entrance is locked at the moment.");

                if(dData[did][dFaction] > 0)
                {
                    if(dData[did][dFaction] != pDataEngkq[playerid][pFaction])
                        return SendErrorMessage(playerid, "This door only for faction.");
                }
                if(dData[did][dFamily] > 0)
                {
                    if(dData[did][dFamily] != pDataEngkq[playerid][pFamily])
                        return SendErrorMessage(playerid, "This door only for family.");
                }

                if(dData[did][dVip] > pDataEngkq[playerid][pVip])
                    return SendErrorMessage(playerid, "Your VIP level not enough to enter this door.");

                if(dData[did][dAdmin] > pDataEngkq[playerid][pAdminLevel])
                    return SendErrorMessage(playerid, "Your admin level not enough to enter this door.");

                if(strlen(dData[did][dPass]))
                {
                    new params[256];
                    if(sscanf(params, "s[256]", params)) return SendInfoMessage(playerid, "Usage: /enter [password]");
                    if(strcmp(params, dData[did][dPass])) return SendErrorMessage(playerid, "Invalid door password.");

                    if(dData[did][dCustom])
                    {
                        SetPlayerPosition(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
                        LoadingObject(playerid);
                    }
                    else
                    {
                        SetPlayerPosition(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
                        LoadingObject(playerid);
                    }
                    pDataEngkq[playerid][pInDoor] = did;
                    SetPlayerInterior(playerid, dData[did][dIntint]);
                    SetPlayerVirtualWorld(playerid, dData[did][dIntvw]);
                    SetCameraBehindPlayer(playerid);
                    SetTimerEx("DrugEffectGone", 3000, false, "i", playerid);
                    LoadingObject(playerid);
                }
                else
                {
                    if(dData[did][dCustom])
                    {
                        SetPlayerPosition(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
                        LoadingObject(playerid);
                    }
                    else
                    {
                        SetPlayerPosition(playerid, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ], dData[did][dIntposA]);
                        LoadingObject(playerid);
                    }
                    pDataEngkq[playerid][pInDoor] = did;
                    LoadingObject(playerid);
                    SetPlayerInterior(playerid, dData[did][dIntint]);
                    SetPlayerVirtualWorld(playerid, dData[did][dIntvw]);
                    SetCameraBehindPlayer(playerid);
                    SetTimerEx("DrugEffectGone", 3000, false, "i", playerid);
                }
            }
            if(IsPlayerInRangeOfPoint(playerid, 2.8, dData[did][dIntposX], dData[did][dIntposY], dData[did][dIntposZ]))
            {
                if(dData[did][dFaction] > 0)
                {
                    if(dData[did][dFaction] != pDataEngkq[playerid][pFaction])
                        return SendErrorMessage(playerid, "This door only for faction.");
                }

                if(dData[did][dCustom])
                {
                    SetPlayerPosition(playerid, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ], dData[did][dExtposA]);
                    LoadingObject(playerid);
                }
                else
                {
                    SetPlayerPosition(playerid, dData[did][dExtposX], dData[did][dExtposY], dData[did][dExtposZ], dData[did][dExtposA]);
                    LoadingObject(playerid);
                }
                pDataEngkq[playerid][pInDoor] = -1;
                LoadingObject(playerid);
                SetPlayerInterior(playerid, dData[did][dExtint]);
                SetPlayerVirtualWorld(playerid, dData[did][dExtvw]);
                SetCameraBehindPlayer(playerid);
            }
        }
    }
    return 1;
}