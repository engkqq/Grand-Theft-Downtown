SetVehiclePosition(playerid, vehicleid, Float:X, Float:Y, Float:Z, Float:a, inter = 0)
{
    LinkVehicleToInterior(vehicleid, inter);
    SetVehiclePos(vehicleid, X, Y, Z);
	SetVehicleZAngle(playerid, a);
	SetCameraBehindPlayer(playerid);
	//SetPlayerWorldBounds(playerid, 20000, -20000, 20000, -20000);
}
SetPlayerPosition(playerid, Float:X, Float:Y, Float:Z, Float:a, inter = 0)
{
    SetPlayerInterior(playerid, inter);
    SetPlayerPos(playerid, X, Y, Z);
	SetPlayerFacingAngle(playerid, a);
	SetCameraBehindPlayer(playerid);
	//SetPlayerWorldBounds(playerid, 20000, -20000, 20000, -20000);
}

//-------[ DelayFreeze & DelayUnfreeze ]------//
Fungsi:DelayUnfreeze(playerid)
{
    TogglePlayerControllable(playerid, true);
    ShowPlayerInfoAction(playerid, "~g~Berhasil Masuk! ~w~Kamu sekarang bisa bergerak.", 3000);
    return 1;
}
ColouredText(const text[])
{
    new
        pos = -1,
        string[144]
    ;
    strmid(string, text, 0, 128, (sizeof(string) - 16));

    while((pos = strfind(string, "#", true, (pos + 1))) != -1)
    {
        new
            i = (pos + 1),
            hexCount
        ;
        for( ; ((string[i] != 0) && (hexCount < 6)); ++i, ++hexCount)
        {
            if(!(('a' <= string[i] <= 'f') || ('A' <= string[i] <= 'F') || ('0' <= string[i] <= '9')))
            {
                    break;
            }
        }
        if((hexCount == 6) && !(hexCount < 6))
        {
            string[pos] = '{';
            strins(string, "}", i);
        }
    }
    return string;
}