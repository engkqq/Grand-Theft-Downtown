CMD:stats(playerid)
{
    ShowStats(playerid);
    return 1; 
}

CMD:updatedata(playerid)
{
    UpdateDataPlayer(playerid);

    SendClientMessage(playerid, COLOR_WHITE, "Berhasil menyimpan data pemain!");
    return 1;
}