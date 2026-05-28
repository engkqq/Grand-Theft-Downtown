
stock AccountCheck(playerid)
{
    g_MysqlRaceCheck[playerid]++;

    GetPlayerName(playerid, pDataEngkq[playerid][pUCP], MAX_PLAYER_NAME);

	new query[128];
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM whitelist WHERE ucp_name = '%e' LIMIT 1", pDataEngkq[playerid][pUCP]);
	mysql_tquery(g_SQL, query, "OnWhitelistChecked", "dd", playerid, g_MysqlRaceCheck[playerid]);
    return 1;
}

Fungsi:OnWhitelistChecked(playerid, race_check)
{
	if(race_check != g_MysqlRaceCheck[playerid]) return KickEx(playerid);

	if(cache_num_rows() > 0)
	{
		cache_get_value_name_int(0, "verifycode", pDataEngkq[playerid][pVerifyCode]);

		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM bans WHERE ucp = '%e' LIMIT 1", pDataEngkq[playerid][pUCP]);
		mysql_tquery(g_SQL, query, "OnBanChecked", "dd", playerid, g_MysqlRaceCheck[playerid]);
	}
	else
	{
		new string[256];
		format(string, sizeof(string),
        "{CCCCCC}----------------------------------------\n\
        {ffffff}Username: {04d400}%s\n\
        {ffffff} Status: {bd0000}Tidak terdaftar di Whitelist\n\
        {CCCCCC}----------------------------------------\n\
        {ffffff}Nama UCP kamu belum terdaftar dalam whitelist server.\n\
        Silahkan daftar terlebih dahulu melalui discord server kami.", pDataEngkq[playerid][pUCP]);
		Dialog_Show(playerid, DialogUnused, DIALOG_STYLE_MSGBOX, "{CCCCCC}GTA:DownTown {FFFFFF}- UCP Whitelist", string, "Close", "");
		KickEx(playerid);
	}
	return 1;
}

Fungsi:OnBanChecked(playerid, race_check)
{
	if(race_check != g_MysqlRaceCheck[playerid]) return KickEx(playerid);

	if(cache_num_rows() > 0)
	{
		new reason[128], admin[24], ban_date;
		cache_get_value_name(0, "reason", reason);
		cache_get_value_name(0, "admin", admin);
		cache_get_value_name_int(0, "ban_date", ban_date);

		new string[512];
		format(string, sizeof(string),
        "{CCCCCC}----------------------------------------\n\
        {ffffff}Akun UCP kamu ({04d400}%s{ffffff}) telah diblokir permanen dari server.\n\
        {FFFFFF}Admin: {bd0000}%s\n{ffffff}Alasan: {bd0000}%s\n\
        {ffffff}Timestamp: {bd0000}%d\n\
        {CCCCCC}----------------------------------------\n\
        {ffffff}Jika ini adalah kesalahan, silahkan hubungi admin di discord.", pDataEngkq[playerid][pUCP], admin, reason, ban_date);
		Dialog_Show(playerid, DialogUnused, DIALOG_STYLE_MSGBOX, "{CCCCCC}GTA:DownTown {FFFFFF}- Accounts Banned", string, "Close", "");
		KickEx(playerid);
	}
	else
	{
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM ucp WHERE ucp_name = '%e' LIMIT 1", pDataEngkq[playerid][pUCP]);
		mysql_tquery(g_SQL, query, "OnUCPChecked", "dd", playerid, g_MysqlRaceCheck[playerid]);
	}
	return 1;
}

Fungsi:OnUCPChecked(playerid, race_check)
{
    if(race_check != g_MysqlRaceCheck[playerid]) return KickEx(playerid);

    new string[280];
    if(cache_num_rows() > 0)
    {
        cache_get_value_name_int(0, "activation", pDataEngkq[playerid][pActivation]);
        cache_get_value_name_int(0, "char_slots", pDataEngkq[playerid][pCharSlots]);
        cache_get_value_name_int(0, "admin", pDataEngkq[playerid][pAdmin]);
        cache_get_value_name(0, "adminname", pDataEngkq[playerid][pAdminName]);
        cache_get_value_name(0, "password", pDataEngkq[playerid][pPassword]);

        if(pDataEngkq[playerid][pCharSlots] == 2 && pDataEngkq[playerid][pAdmin] < 5)
        {
            pDataEngkq[playerid][pCharSlots] = 1;
            new query[128];
            mysql_format(g_SQL, query, sizeof(query), "UPDATE ucp SET char_slots = 3 WHERE ucp_name = '%e'", pDataEngkq[playerid][pUCP]);
            mysql_tquery(g_SQL, query);
        }
        else if(pDataEngkq[playerid][pCharSlots] == 0)
        {
            pDataEngkq[playerid][pCharSlots] = 3;
        }

        if(pDataEngkq[playerid][pActivation] == 0)
        {
            format(string, sizeof(string), 
            "{CCCCCC}----------------------------------------\n\
            {ffffff}Username: {04d400}%s\n\
            {ffffff}Status: {04d400}Terdaftar\n\
            {CCCCCC}----------------------------------------\n\
            {ffffff}Akun UCP kamu sudah terdaftar, silahkan masukan kode verifikasi dari Discord.", pDataEngkq[playerid][pUCP]);
            Dialog_Show(playerid, DialogVerifyCode, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Verifikasi UCP", string, "Input", "Close");
        }
        else
        {
            format(string, sizeof(string), 
            "{CCCCCC}----------------------------------------\n\
            {ffffff}Username: {04d400}%s\n\
            {ffffff}Status: {04d400}Terdaftar\n\
            {CCCCCC}----------------------------------------\n\
            {ffffff}Akun UCP kamu sudah terdaftar kedalam server.\n\
            {ffffff}Login ke akun kamu dengan memasukan password dibawah:", pDataEngkq[playerid][pUCP]);
            Dialog_Show(playerid, DialogLogin, DIALOG_STYLE_PASSWORD, "{CCCCCC}GTA:DownTown {FFFFFF}- Login", string, "Login", "Close");
        }
    }
    else
    {
        format(string, sizeof(string),
        "{CCCCCC}----------------------------------------\n\
        {ffffff}Username: {04d400}%s\n\
        {ffffff}Status: {04d400}Whitelisted\n\
        {CCCCCC}----------------------------------------\n\
        {ffffff}Akun UCP kamu sudah masuk whitelist namun belum terdaftar.\n\
        {ffffff}Silahkan masukan kode verifikasi yang diberikan oleh Discord bot.", pDataEngkq[playerid][pUCP]);
        Dialog_Show(playerid, DialogVerifyCode, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Registrasi UCP", string, "Input", "Close");
    }
    return 1;
}

Fungsi:OnPasswordHashed(playerid, hash_id)
{
	bcrypt_get_hash(pDataEngkq[playerid][pPassword], BCRYPT_HASH_LENGTH);
    pDataEngkq[playerid][pActivation] = 1;
    pDataEngkq[playerid][pCharSlots] = 1; // Force 1 for new accounts
    
    new query[512];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO ucp (ucp_name, password, activation, char_slots, admin, adminname) VALUES ('%e', '%e', 1, 3, 0, 'None') ON DUPLICATE KEY UPDATE password = '%e', activation = 1", pDataEngkq[playerid][pUCP], pDataEngkq[playerid][pPassword], pDataEngkq[playerid][pPassword]);
    mysql_tquery(g_SQL, query);

    mysql_format(g_SQL, query, sizeof(query), "UPDATE whitelist SET active = 1 WHERE ucp_name = '%e'", pDataEngkq[playerid][pUCP]);
    mysql_tquery(g_SQL, query);

    CheckUserCharacter(playerid);
	return 1;
}

Fungsi:OnPasswordVerify(playerid, bool:success)
{
    new str[285];
    if(success)
    {
        pDataEngkq[playerid][pLoginAttempt] = 0;
        pDataEngkq[playerid][IsPlayersLogin] = true;
        CheckUserCharacter(playerid);
    }
    else
    {
        pDataEngkq[playerid][pLoginAttempt]++;

        if(pDataEngkq[playerid][pLoginAttempt] >= 3)
        {
            format(str, sizeof(str), 
            "{CCCCCC}----------------------------------------\n\
            {ffffff}Username: {04d400}%s\n\
            {ffffff}Status: {04d400}Terdaftar\n\
            {CCCCCC}----------------------------------------\n\
            {ffffff}Kamu dikick karena salah memasukan password sebanyak 3X!\n\
            {FBFF00}Lupa password? Ajukan reset password pada moderator di discord kammi", pDataEngkq[playerid][pUCP]);
            Dialog_Show(playerid, DialogUnused, DIALOG_STYLE_MSGBOX, "{CCCCCC}GTA:DownTown {FFFFFF}- Failed Login", str, "Oke", "");
            KickEx(playerid);
        }
        else
        {
            format(str, sizeof(str), 
            "{CCCCCC}----------------------------------------\n\
            {ffffff}Username: {04d400}%s\n\
            {ffffff}Status: {04d400}Terdaftar\n\
            {CCCCCC}----------------------------------------\n\
            {FBFF00}Kamu salah memasukan password! kesempatan kamu %d/3.\n\
            {ffffff}Isi kembali kolom password dengan benar:", pDataEngkq[playerid][pUCP], pDataEngkq[playerid][pLoginAttempt]);
            Dialog_Show(playerid, DialogLogin, DIALOG_STYLE_PASSWORD, "{CCCCCC}GTA:DownTown {FFFFFF}- Login", str, "Input", "Close");
        }
    }
    return 1;
}

stock CheckUserCharacter(playerid)
{
    g_MysqlRaceCheck[playerid]++;

    new query[128];
    mysql_format(g_SQL, query, sizeof(query), "SELECT username FROM users WHERE ucp = '%s' LIMIT %d", pDataEngkq[playerid][pUCP], MAX_CHARS);
    mysql_tquery(g_SQL, query, "OnCharacterLoaded", "dd", playerid, g_MysqlRaceCheck[playerid]);
    return 1;
}

Fungsi:OnCharacterLoaded(playerid, race_check)
{
    if(race_check != g_MysqlRaceCheck[playerid]) return KickEx(playerid);

    new rows = cache_num_rows();

    for(new i; i < MAX_CHARS; i++)
    {
        PlayerCharacter[playerid][i][0] = EOS;
    }

    for(new k; k < rows; k++)
    {
        cache_get_value_name(k, "username", PlayerCharacter[playerid][k]);
    }
    ShowCharacterList(playerid);
    return 1;
}

stock ShowCharacterList(playerid)
{
    new name[268],
        str[128],
        count;

    for(new i; i < pDataEngkq[playerid][pCharSlots]; i++)
    {
        if(PlayerCharacter[playerid][i][0] != EOS)
        {
            format(str, sizeof(str), "%s\n", PlayerCharacter[playerid][i]);
            strcat(name, str);
            count++;
        }
    }

    if(count < pDataEngkq[playerid][pCharSlots]) strcat(name, "+ New Character");
    
    Dialog_Show(playerid, DialogListChar, DIALOG_STYLE_LIST, "{CCCCCC}GTA:DownTown {FFFFFF}- List Character", name, "Choose", "Close");
    return 1;
}

Fungsi:OnUsernameChecked(playerid, const name[], race_check)
{
    if(race_check != g_MysqlRaceCheck[playerid])    
        return KickEx(playerid);
    
    new rows = cache_num_rows();
    if(rows)
        return Dialog_Show(playerid, DialogCreateChar, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Create New Character", "{bd0000}Nama sudah pernah dipakai! {ffffff}Gunakan nama lain\nMasukan nama :", "Input", "");

    Dialog_Show(playerid, DialogAge, DIALOG_STYLE_INPUT, "{CCCCCC}GTA:DownTown {FFFFFF}- Age", "Masukan tanggal lahir dengan format DD/MM/YYYY (16/01/2005)", "Input", "Tutup");
    return 1;
}

stock CreateCharacterAccount(playerid)
{
    new query[512];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO users (username, ucp, skin, gender, birth_day, birth_month, birth_year, weight, height, origin, pos_x, pos_y, pos_z, pos_a, interior, virtual_world) VALUES ('%e', '%e', %d, %d, %d, %d, %d, %d, %d, '%e', %f, %f, %f, %f, %d, %d)", 
        pDataEngkq[playerid][pName], pDataEngkq[playerid][pUCP], pDataEngkq[playerid][pSkin], pDataEngkq[playerid][pGender], pDataEngkq[playerid][pBirthDay], pDataEngkq[playerid][pBirthMonth], pDataEngkq[playerid][pBirthYear],
        pDataEngkq[playerid][pWeight], pDataEngkq[playerid][pHeight], pDataEngkq[playerid][pOrigin],
        DEFAULT_POS_X, DEFAULT_POS_Y, DEFAULT_POS_Z, DEFAULT_POS_A, 0, 0);
    mysql_tquery(g_SQL, query, "OnInsertCharacter", "d", playerid);
    return 1;
}

Fungsi:OnInsertCharacter(playerid)
{
    pDataEngkq[playerid][pID] = cache_insert_id();

    SetPlayerName(playerid, pDataEngkq[playerid][pName]);

    pDataEngkq[playerid][IsPlayersLogin] = true;
    CreateSetupCharacter(playerid);
    return 1;
}