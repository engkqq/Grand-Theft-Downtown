stock ShowStats(playerid)
{
    new str[350], 
        strhead[64],
        client[8];

    if(!pDataEngkq[playerid][isOfficialClient])
        format(client, sizeof(client), "Android");
    else
        format(client, sizeof(client), "PC");
    
    format(strhead, sizeof(strhead), "{FFFF00}Stats: %s (%d)", pDataEngkq[playerid][pName], playerid);
    
    format(str, sizeof(str), "{00FFFF}Kategori\t{00FFFF}Informasi\n");
    
    format(str, sizeof(str), "%s{FFFFFF}Client\t: {FFFF00}%s\n", str, client);
    format(str, sizeof(str), "%s{FFFFFF}ID Database\t: {FFFF00}%d\n", str, pDataEngkq[playerid][pID]);
    format(str, sizeof(str), "%s{FFFFFF}Interior\t: {FFFF00}%d\n", str, pDataEngkq[playerid][pInterior]);
    format(str, sizeof(str), "%s{FFFFFF}Virtual World\t: {FFFF00}%d\n", str, pDataEngkq[playerid][pVirtual_World]);
    format(str, sizeof(str), "%s{FFFFFF}Skin ID\t: {FFFF00}%d\n", str, pDataEngkq[playerid][pSkin]);
    format(str, sizeof(str), "%s{FFFFFF}Uang\t: {00FF00}$%d\n", str, pDataEngkq[playerid][pMoney]);
    format(str, sizeof(str), "%s{FFFFFF}Level\t: {FFFF00}%d", str, pDataEngkq[playerid][pLevel]);

    return Dialog_Show(playerid, DialogUnused, DIALOG_STYLE_TABLIST_HEADERS, strhead, str, "Tutup", "");
}

//--------[ Fungsi - Days, Months, Origin & Validasi Name IC ]--------//
stock ParseBirthDate(playerid, const date[])
{
    new day,
        month,
        year;

    if(sscanf(date, "p</>ddd", day, month, year))
    {
        Dialog_Show(playerid, DialogAge, DIALOG_STYLE_INPUT, "Age", "{ffffff}Kamu memasukan format yang {B82B2B}salah!\n{ffffff}Masukan kembali tanggal lahir dengan format DD/MM/YYYY (16/01/2005)", "Input", "Tutup");
        return 0;
    }

    if(!IsValidDate(day, month, year))
    {
        Dialog_Show(playerid, DialogAge, DIALOG_STYLE_INPUT, "Age", "{ffffff}Kamu memasukan tanggal yang {B82B2B}tidak valid!\n{ffffff}Masukan kembali tanggal lahir dengan format DD/MM/YYYY dan valid!", "Input", "Tutup");
        return 0;
    }

    pDataEngkq[playerid][pBirthDay] = day;
    pDataEngkq[playerid][pBirthMonth] = month;
    pDataEngkq[playerid][pBirthYear] = year;
    Dialog_Show(playerid, DialogOrigin, DIALOG_STYLE_LIST, "Character Origin", "Indonesia\nAmerica\nUnited Kingdom\nJapan\nKorea\nChina\nMexico\nRussia\nGermany\nFrance", "Select", "Back");
    return 1;
}

stock IsValidDate(day, month, year)
{
    if(year < 1900 || year > 2100) return 0;
    if(month < 1 || month > 12) return 0;
    if(day < 1) return 0;

    new daysInMonth[] = {
    31,28,31,30,31,30,31,31,30,31,30,31};

    return day <= daysInMonth[month - 1];
}

stock IsValidRPName(const name[])
{
    new len = strlen(name);

    if(len < 3 || len > MAX_PLAYER_NAME)
        return 0;

    new underscorePos = strfind(name, "_");
    if(underscorePos == -1)
        return 0;

    if(underscorePos == 0 || underscorePos == len - 1)
        return 0;

    if(name[0] < 'A' || name[0] > 'Z')
        return 0;

    if(name[underscorePos + 1] < 'A' || name[underscorePos + 1] > 'Z')
        return 0;

    for(new i = 0; i < len; i++)
    {
        if(name[i] == '_') continue;

        if(name[i] < 'a' || name[i] > 'z')
        {
            if(name[i] < 'A' || name[i] > 'Z')
                return 0;
        }
    }
    return 1;
}
//---------------------------------------------------------------//

CreateSetupCharacter(playerid)
{
    if(!pDataEngkq[playerid][IsPlayersLogin]) return Error(playerid, "Kamu tidak memiliki akes untuk melakukan ini!");

    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    GivePlayerMoneyEx(playerid, 5000);
    Dialog_Show(playerid, DialogSpawnSelect, DIALOG_STYLE_LIST, "{CCCCCC}GTA:DownTown {FFFFFF}- Spawn Selection", "Pelabuhan\nBandara", "Spawn", "Close");
    return 1;
}

//--------[ Player Name ]--------//
stock GetPlayerNameEx(playerid)
{   
    GetPlayerName(playerid, pDataEngkq[playerid][pName], MAX_PLAYER_NAME);
    return pDataEngkq[playerid][pName];
}
//---------------------------------------------------------------//

//--------[ Money Management ]--------//
GivePlayerMoneyEx(playerid, ammount)
{
    GivePlayerMoney(playerid, ammount);
    pDataEngkq[playerid][pMoney] += ammount;
    return 1;
}

RemovePlayerMoneyEx(playerid, ammount)
{
    GivePlayerMoney(playerid, -ammount);
    pDataEngkq[playerid][pMoney] -= ammount;
    return 1;
}
//---------------------------------------------------------------//

stock ShowInfo(playerid)
{
    new hari, bulan, tahun;
    new jam, menit, detik;
    
    getdate(tahun, bulan, hari);
    gettime(jam, menit, detik);

    new strpesan[228];
    format(strpesan, sizeof(strpesan), "Selamat datang di GTA:DownTown, %s Gunakan /help untuk melihat daftar perintah yang tersedia.", pDataEngkq[playerid][pName]);
    Info(playerid, strpesan);

    new str[128];
    format(str, sizeof(str), "Tanggal: %02d/%02d/%d | Waktu: %02d:%02d:%02d", hari, bulan, tahun, jam, menit, detik);
    Info(playerid, str);
    return 1;
}

Fungsi:LoadingObject(playerid)
{
    TogglePlayerControllable(playerid, false);
    ShowPlayerInfoAction(playerid, "~y~ Grand Theft Downtown ~w~| Memuat objek sekitar...", 0);
    SetTimerEx("DelayUnfreeze", 3000, false, "d", playerid);
    return 1;
}