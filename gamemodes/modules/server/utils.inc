KickEx(playerid)
{
	SetTimerEx("KickPlayer", 2000, false, "i", playerid);
	return 1;
}

forward KickPlayer(playerid);
public KickPlayer(playerid) 
{
	Kick(playerid);
	return 1;
}

stock ConnectMysql(const host[], const user[], const pass[], const db[])
{
	g_SQL = mysql_connect(host, user, pass, db);

	if(g_SQL == MYSQL_INVALID_HANDLE || mysql_errno(g_SQL) != 0)
	{
		SendRconCommand("exit");
	}
}

// unused Dialog
Dialog:DialogUnused(playerid, response, listitem, inputtext[])
{
	if(response) return 1;
	return 1;
}

stock StartTickCount(playerid)
{
	g_TickCount[playerid] = GetTickCount();
	return 1;
}

stock PlayerLoadTime(playerid, const reason[] = "")
{
	new loadtime = GetTickCount() - g_TickCount[playerid];

	new message[128];
	format(message, sizeof(message), "Load %s: %d ms", reason, loadtime);

	Info(playerid, message);
	return loadtime;
}

stock RandomEx(minValue, maxValue)
{
	if(minValue == maxValue)
		return minValue;

	if(minValue > maxValue)
	{
		new temp = minValue;
		minValue = maxValue;
		maxValue = temp;
	}

	return random(maxValue - minValue + 1) + minValue;
}

stock ReturnDate(timestamp)
{
    new year, month, day, hour, minute, second;
    new dateStr[32];
    
    format(dateStr, sizeof(dateStr), "%d", timestamp); // Placeholder
    return dateStr;
}

//--------[ Get Ranks Staff ]--------//
stock GetDownTownRank(playerid)
{
    new rankName[32];

    switch(pDataEngkq[playerid][pAdmin])
    {
        case 1: rankName = "Volunteer";
        case 2: rankName = "Helper";
        case 3: rankName = "Junior Admin";
        case 4: rankName = "General Admin";
        case 5: rankName = "Senior Admin";
        case 6: rankName = "Head Admin";
        case 7: rankName = "Management";
        case 8: rankName = "Director";
        case 9: rankName = "Executive";
        default: rankName = "Player";
    }
    return rankName;
}