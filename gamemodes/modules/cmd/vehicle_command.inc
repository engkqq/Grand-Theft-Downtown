CMD:createvehicle(playerid, params[])
{
    if(pDataEngkq[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new modelid, color1, color2;
    if(sscanf(params, "iii", modelid, color1, color2))
        return SendClientMessage(playerid, COLOR_USAGE, "USAGE: {ffffff}/createvehicle <modelid> <color1> <color2>");
    
    if(modelid < 400 || modelid >611)
        return SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Model id tidak boleh kurang dari 411 atau lebih dari 611!");
    
    new Float:x, Float:y, Float:z, Float:a;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);
    if(Vehicle_Create(playerid, modelid, x, y, z, a, color1, color2))
    {
        SendClientMessage(playerid, COLOR_SUCCESS, "SUCCESS: {ffffff}Kamu berhasil membuat kendaraan!");
    }
    else
        SendClientMessage(playerid, COLOR_ERROR, "ERROR: {ffffff}Gagal membuat kendaraan!");
    return 1;
}