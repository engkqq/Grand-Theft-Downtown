Dialog:DialogRegister(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid);
    new string[180];

	if(strlen(inputtext) <= 5)
    {
        format(string, sizeof(string), "{ffffff}Username: {04d400}%s\n{ffffff}Status: {bd0000}Tidak terdaftar\n{ffffff}Password harus memiliki panjang minimal 5 karakter.\nnSilahkan buat password kembali untuk melanjutkan registrasi:", pDataEngkq[playerid][pUCP]);
        return Dialog_Show(playerid, DialogRegister, DIALOG_STYLE_PASSWORD, "{CCCCCC}GTA:DownTown {FFFFFF}- Register", string, "Register", "Close");
    }
	bcrypt_hash(playerid, "OnPasswordHashed", inputtext, BCRYPT_COST);
	return 1;
}

Dialog:DialogLogin(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid);
	bcrypt_verify(playerid, "OnPasswordVerify", inputtext, pDataEngkq[playerid][pPassword]);
	return 1;
}

Dialog:DialogVerifyCode(playerid, response, listitem, inputtext[])
{
    if(!response) return KickEx(playerid);
    new string[180];

    if(strval(inputtext) == pDataEngkq[playerid][pVerifyCode])
    {
        format(string, sizeof(string), "{ffffff}Username: {04d400}%s\n{ffffff} Status: {bd0000}Tidak terdaftar\n{ffffff}Silahkan buat password untuk melanjutkan proses registrasi.", pDataEngkq[playerid][pUCP]);
        Dialog_Show(playerid, DialogRegister, DIALOG_STYLE_PASSWORD, "{CCCCCC}GTA:DownTown {FFFFFF}- Register", string, "Register", "Close");
    }
    else
    {
        format(string, sizeof(string), "{ffffff}Username: {04d400}%s\n{ffffff} Status: {bd0000}Tidak terdaftar\n{ffffff}Kode verifikasi tidak sesuai! silahkan coba lagi!.", pDataEngkq[playerid][pUCP]);
        Dialog_Show(playerid, DialogVerifyCode, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Verify Code", string, "Input", "Close");
    }
    return 1;
}

Dialog:DialogListChar(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid);
	new count;
    Forex(i, listitem)
    {
        count++;
    }

    if(PlayerCharacter[playerid][listitem][0] == EOS)
        return Dialog_Show(playerid, DialogCreateChar, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Create New Character", "{ffffff}Buat nama karakter (Contoh : Labian_lasan)\nMasukan nama dibawah:", "Input", "");

    pDataEngkq[playerid][pCharacter] = listitem;
    SetPlayerName(playerid, PlayerCharacter[playerid][listitem]);

    StartTickCount(playerid);
    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM users WHERE username = '%e' LIMIT 1", PlayerCharacter[playerid][pDataEngkq[playerid][pCharacter]]);
    mysql_tquery(g_SQL, query, "OnCharacterDataLoaded", "d", playerid);
	return 1;
}

Dialog:DialogCreateChar(playerid, response, listitem, inputtext[])
{
    if(!response) return KickEx(playerid);

    if(!IsValidRPName(inputtext))
        return Dialog_Show(playerid, DialogCreateChar, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Create New Character", "{bd0000}Format salah (Firstname_Lastname)\n{ffffff}Masukan nama dibawah :", "Input", "");
    
    format(pDataEngkq[playerid][pName], MAX_PLAYER_NAME, inputtext);
    g_MysqlRaceCheck[playerid]++;
    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "SELECT username FROM users WHERE username = '%e' LIMIT 1", pDataEngkq[playerid][pName]);
    mysql_tquery(g_SQL, query, "OnUsernameChecked", "dsd", playerid, pDataEngkq[playerid][pName], g_MysqlRaceCheck[playerid]);
    return 1;
}

Dialog:DialogAge(playerid, response, listitem, inputtext[])
{
    if(!response) return KickEx(playerid);

    ParseBirthDate(playerid, inputtext);
    return 1;
}

Dialog:DialogOrigin(playerid, response, listitem, inputtext[])
{
    if(!response) return Dialog_Show(playerid, DialogAge, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Age", "Masukan tanggal lahir dengan format DD/MM/YYYY (16/01/2005)", "Input", "Tutup");
    
    format(pDataEngkq[playerid][pOrigin], 32, inputtext);
    Dialog_Show(playerid, DialogWeight, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Character Weight", "{ffffff}Masukan berat badan karakter (Kg) (40 - 200):", "Input", "Back");
    return 1;
}

Dialog:DialogWeight(playerid, response, listitem, inputtext[])
{
    if(!response) return Dialog_Show(playerid, DialogOrigin, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Character Origin", "{ffffff}Masukan asal karakter kamu (Contoh: America, Indonesia, etc):", "Input", "Back");

    new weight = strval(inputtext);
    if(weight < 40 || weight > 200)
        return Dialog_Show(playerid, DialogWeight, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Character Weight", "{bd0000}Berat badan tidak valid (40-200)!\n{ffffff}Masukan berat badan karakter (Kg):", "Input", "Back");

    pDataEngkq[playerid][pWeight] = weight;
    Dialog_Show(playerid, DialogHeight, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Character Height", "{ffffff}Masukan tinggi badan karakter (Cm) (140 - 220):", "Input", "Back");
    return 1;
}

Dialog:DialogHeight(playerid, response, listitem, inputtext[])
{
    if(!response) return Dialog_Show(playerid, DialogWeight, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Character Weight", "{ffffff}Masukan berat badan karakter (Kg):", "Input", "Back");

    new height = strval(inputtext);
    if(height < 140 || height > 220)
        return Dialog_Show(playerid, DialogHeight, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Character Height", "{bd0000}Tinggi badan tidak valid (140-220)!\n{ffffff}Masukan tinggi badan karakter (Cm):", "Input", "Back");

    pDataEngkq[playerid][pHeight] = height;
    Dialog_Show(playerid, DialogGender, DIALOG_STYLE_LIST, "{CCCCCC}GTA:DownTown {FFFFFF}- Gender", "Male\nFemale", "Continue", "Back");
    return 1;
}

Dialog:DialogGender(playerid, response, listitem, inputtext[])
{
    if(!response) return Dialog_Show(playerid, DialogHeight, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Character Height", "{ffffff}Masukan tinggi badan karakter (Cm):", "Input", "Back");
    
    switch(listitem)
    {
        case 0: // Male
        {
            pDataEngkq[playerid][pGender] = 0;
            ShowPlayereSelectionEngkq(playerid, "Select Skins", 1, "male_spawnskin.txt");
        }
        case 1: // Female
        {
            pDataEngkq[playerid][pGender] = 1;
            ShowPlayereSelectionEngkq(playerid, "Select Skins", 2, "female_spawnskin.txt");
        }
        
    }
    return 1;
}

Dialog:DialogSpawnSelect(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        pDataEngkq[playerid][pLastExit] = gettime();
        
        SetSpawnInfo(playerid, NO_TEAM, pDataEngkq[playerid][pSkin], pDataEngkq[playerid][pPos][0], pDataEngkq[playerid][pPos][1], pDataEngkq[playerid][pPos][2], pDataEngkq[playerid][pPos][3], WEAPON_FIST, 0, WEAPON_FIST, 0, WEAPON_FIST, 0);
        SpawnPlayer(playerid);
        ShowInfo(playerid);
        return 1;
    }

    switch(listitem)
    {
        case 0: // Pelabuhan
        {
            pDataEngkq[playerid][pLastExit] = gettime();
            
            SetSpawnInfo(playerid, NO_TEAM, pDataEngkq[playerid][pSkin], SPAWN_PELABUHAN_X, SPAWN_PELABUHAN_Y, SPAWN_PELABUHAN_Z, SPAWN_PELABUHAN_A, WEAPON_FIST, 0, WEAPON_FIST, 0, WEAPON_FIST, 0);
            SpawnPlayer(playerid);
            ShowInfo(playerid);
        }
        case 1: // Airport
        {
            pDataEngkq[playerid][pLastExit] = gettime();
            
            SetSpawnInfo(playerid, NO_TEAM, pDataEngkq[playerid][pSkin], SPAWN_BANDARA_X, SPAWN_BANDARA_Y, SPAWN_BANDARA_Z, SPAWN_BANDARA_A, WEAPON_FIST, 0, WEAPON_FIST, 0, WEAPON_FIST, 0);
            SpawnPlayer(playerid);
            ShowInfo(playerid);
        }
    }
    return 1;
}