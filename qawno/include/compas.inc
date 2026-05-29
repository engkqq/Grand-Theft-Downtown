#if defined _COMPAS_INCLUDED
    #endinput
#endif
#define _COMPAS_INCLUDED

new PlayerText:ComPas[MAX_PLAYERS][2];
new CompasTimer[MAX_PLAYERS];

stock CreateCompas(playerid)
{
    ComPas[playerid][0] = CreatePlayerTextDraw(playerid, 110.000, 350.000, "NW");
    PlayerTextDrawLetterSize(playerid, ComPas[playerid][0], 0.550, 4.000);
    PlayerTextDrawAlignment(playerid, ComPas[playerid][0], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, ComPas[playerid][0], -2139062017);
    PlayerTextDrawSetShadow(playerid, ComPas[playerid][0], 1);
    PlayerTextDrawSetOutline(playerid, ComPas[playerid][0], 1);
    PlayerTextDrawBackgroundColour(playerid, ComPas[playerid][0], 150);
    PlayerTextDrawFont(playerid, ComPas[playerid][0], TEXT_DRAW_FONT_1);
    PlayerTextDrawSetProportional(playerid, ComPas[playerid][0], true);

    ComPas[playerid][1] = CreatePlayerTextDraw(playerid, 113.000, 382.000, "000.0|");
    PlayerTextDrawLetterSize(playerid, ComPas[playerid][1], 0.200, 1.299);
    PlayerTextDrawTextSize(playerid, ComPas[playerid][1], 0.000, 3.000);
    PlayerTextDrawAlignment(playerid, ComPas[playerid][1], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, ComPas[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, ComPas[playerid][1], 1);
    PlayerTextDrawSetOutline(playerid, ComPas[playerid][1], 1);
    PlayerTextDrawBackgroundColour(playerid, ComPas[playerid][1], 150);
    PlayerTextDrawFont(playerid, ComPas[playerid][1], TEXT_DRAW_FONT_1);
    PlayerTextDrawSetProportional(playerid, ComPas[playerid][1], true);
}

stock ShowCompas(playerid)
{
    PlayerTextDrawShow(playerid, ComPas[playerid][0]);
    PlayerTextDrawShow(playerid, ComPas[playerid][1]);

    if(CompasTimer[playerid])
    {
        KillTimer(CompasTimer[playerid]);
    }

    CompasTimer[playerid] = SetTimerEx("UpdateCompas", 100, true, "i", playerid);
}

stock HideCompas(playerid)
{
    PlayerTextDrawHide(playerid, ComPas[playerid][0]);
    PlayerTextDrawHide(playerid, ComPas[playerid][1]);

    if(CompasTimer[playerid])
    {
        KillTimer(CompasTimer[playerid]);
        CompasTimer[playerid] = 0;
    }
}

forward UpdateCompas(playerid);
public UpdateCompas(playerid)
{
    if(!IsPlayerConnected(playerid))
        return 0;

    new Float:angle;

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        GetVehicleZAngle(GetPlayerVehicleID(playerid), angle);
    }
    else
    {
        GetPlayerFacingAngle(playerid, angle);
    }

    new direction[8];

    if(angle >= 337.5 || angle < 22.5)
    {
        format(direction, sizeof(direction), "N");
    }
    else if(angle >= 22.5 && angle < 67.5)
    {
        format(direction, sizeof(direction), "NE");
    }
    else if(angle >= 67.5 && angle < 112.5)
    {
        format(direction, sizeof(direction), "E");
    }
    else if(angle >= 112.5 && angle < 157.5)
    {
        format(direction, sizeof(direction), "SE");
    }
    else if(angle >= 157.5 && angle < 202.5)
    {
        format(direction, sizeof(direction), "S");
    }
    else if(angle >= 202.5 && angle < 247.5)
    {
        format(direction, sizeof(direction), "SW");
    }
    else if(angle >= 247.5 && angle < 292.5)
    {
        format(direction, sizeof(direction), "W");
    }
    else
    {
        format(direction, sizeof(direction), "NW");
    }

    PlayerTextDrawSetString(playerid, ComPas[playerid][0], direction);

    new string[32];
    format(string, sizeof(string), "%03.1f|", angle);

    PlayerTextDrawSetString(playerid, ComPas[playerid][1], string);

    return 1;
}