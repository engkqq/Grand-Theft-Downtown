/*
 * engkqAction.inc - Kustom TextDraw Info Melayang untuk open.mp.
 * Author: Engkq
 * Terinspirasi oleh berbagai sistem pesan info di server GTA:SA lainnya, dengan penyesuaian untuk open.mp.
 * Fitur: 
    * - Menampilkan pesan info melayang di bawah layar pemain dengan dukungan format warna.
*/

#if defined _engkq_action_included
    #endinput
#endif
#define _engkq_action_included

static PlayerText:EngkqInfoTd[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
static EngkqInfoTimer[MAX_PLAYERS] = {-1, ...};

forward HidePlayerInfoAction(playerid);

/**
 * Memunculkan pesan informasi melayang di bawah layar player
 * @param playerid ID pemain yang dituju
 * @param action Teks yang ingin ditampilkan (Mendukung format warna game seperti ~r~, ~w~, dll.)
 * @param time_ms Durasi waktu tampil dalam milidetik (1000 = 1 detik). Isi 0 jika ingin tampil selamanya sampai di-hide manual.
 */
stock ShowPlayerInfoAction(playerid, const action[], time_ms = 4000)
{
    if(!IsPlayerConnected(playerid)) return 0;

    if(EngkqInfoTimer[playerid] != -1)
    {
        KillTimer(EngkqInfoTimer[playerid]);
        EngkqInfoTimer[playerid] = -1;
    }
    if(EngkqInfoTd[playerid] != PlayerText:INVALID_TEXT_DRAW)
    {
        PlayerTextDrawDestroy(playerid, EngkqInfoTd[playerid]);
        EngkqInfoTd[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }

    // Membuat TextDraw baru sesuai dengan koordinat dari TextDraw Designer kamu
    EngkqInfoTd[playerid] = CreatePlayerTextDraw(playerid, 325.000, 354.000, action); 
    PlayerTextDrawLetterSize(playerid, EngkqInfoTd[playerid], 0.170, 0.999); 
    PlayerTextDrawAlignment(playerid, EngkqInfoTd[playerid], TEXT_DRAW_ALIGN_CENTER); 
    PlayerTextDrawColour(playerid, EngkqInfoTd[playerid], -1);
    PlayerTextDrawSetShadow(playerid, EngkqInfoTd[playerid], 1);
    PlayerTextDrawSetOutline(playerid, EngkqInfoTd[playerid], 1);
    PlayerTextDrawBackgroundColour(playerid, EngkqInfoTd[playerid], 150);
    PlayerTextDrawFont(playerid, EngkqInfoTd[playerid], TEXT_DRAW_FONT_1);
    PlayerTextDrawSetProportional(playerid, EngkqInfoTd[playerid], true);

    PlayerTextDrawShow(playerid, EngkqInfoTd[playerid]);

    if(time_ms > 0)
    {
        EngkqInfoTimer[playerid] = SetTimerEx("HidePlayerInfoAction", time_ms, false, "d", playerid);
    }
    return 1;
}

/**
 * Menyembunyikan dan menghapus TextDraw info dari layar player secara manual
 */
stock ClearPlayerInfoAction(playerid)
{
    if(EngkqInfoTimer[playerid] != -1)
    {
        KillTimer(EngkqInfoTimer[playerid]);
        EngkqInfoTimer[playerid] = -1;
    }
    if(EngkqInfoTd[playerid] != PlayerText:INVALID_TEXT_DRAW)
    {
        PlayerTextDrawDestroy(playerid, EngkqInfoTd[playerid]);
        EngkqInfoTd[playerid] = PlayerText:INVALID_TEXT_DRAW;
        return 1;
    }
    return 0;
}

public HidePlayerInfoAction(playerid)
{
    EngkqInfoTimer[playerid] = -1;
    if(EngkqInfoTd[playerid] != PlayerText:INVALID_TEXT_DRAW)
    {
        PlayerTextDrawDestroy(playerid, EngkqInfoTd[playerid]);
        EngkqInfoTd[playerid] = PlayerText:INVALID_TEXT_DRAW;
    }
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    if(EngkqInfoTimer[playerid] != -1) KillTimer(EngkqInfoTimer[playerid]);
    EngkqInfoTimer[playerid] = -1;
    EngkqInfoTd[playerid] = PlayerText:INVALID_TEXT_DRAW;

    #if defined EngkqMsg_OnPlayerDisconnect
        return EngkqMsg_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect EngkqMsg_OnPlayerDisconnect
#if defined EngkqMsg_OnPlayerDisconnect
    forward EngkqMsg_OnPlayerDisconnect(playerid, reason);
#endif