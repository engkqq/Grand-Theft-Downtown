/* SXO [SAMP X OPEN MULTIPLAYER] ERROR TEXTDRAW 
* AUTHOR: Ventra ABP.Rahman
* SINCE: 03/05/2026
*/

#if defined _inc_Error
    #endinput
#endif
#define _inc_Error

#include <open.mp>

static PlayerText:Text_Player[MAX_PLAYERS][5];

stock InitErrorTD(playerid)
{
   Text_Player[playerid][0] = CreatePlayerTextDraw(playerid, 535.000, 250.000, "LD_SPAC:black");
   PlayerTextDrawTextSize(playerid, Text_Player[playerid][0], 100.000, 50.000);
   PlayerTextDrawAlignment(playerid, Text_Player[playerid][0], 1);
   PlayerTextDrawColour(playerid, Text_Player[playerid][0], 1116206516);
   PlayerTextDrawSetShadow(playerid, Text_Player[playerid][0], 0);
   PlayerTextDrawSetOutline(playerid, Text_Player[playerid][0], 0);
   PlayerTextDrawBackgroundColor(playerid, Text_Player[playerid][0], 255);
   PlayerTextDrawFont(playerid, Text_Player[playerid][0], 4);
   PlayerTextDrawSetProportional(playerid, Text_Player[playerid][0], 1);

   Text_Player[playerid][1] = CreatePlayerTextDraw(playerid, 540.000, 267.000, "LD_CHAT:thumbdn");
   PlayerTextDrawTextSize(playerid, Text_Player[playerid][1], 13.000, 17.000);
   PlayerTextDrawAlignment(playerid, Text_Player[playerid][1], 1);
   PlayerTextDrawColour(playerid, Text_Player[playerid][1], -1);
   PlayerTextDrawSetShadow(playerid, Text_Player[playerid][1], 0);
   PlayerTextDrawSetOutline(playerid, Text_Player[playerid][1], 0);
   PlayerTextDrawBackgroundColor(playerid, Text_Player[playerid][1], 255);
   PlayerTextDrawFont(playerid, Text_Player[playerid][1], 4);
   PlayerTextDrawSetProportional(playerid, Text_Player[playerid][1], 1);

   Text_Player[playerid][2] = CreatePlayerTextDraw(playerid, 531.000, 250.000, "LD_SPAC:white");
   PlayerTextDrawTextSize(playerid, Text_Player[playerid][2], 4.000, 50.000);
   PlayerTextDrawAlignment(playerid, Text_Player[playerid][2], 1);
   PlayerTextDrawColour(playerid, Text_Player[playerid][2], -2139062017);
   PlayerTextDrawSetShadow(playerid, Text_Player[playerid][2], 0);
   PlayerTextDrawSetOutline(playerid, Text_Player[playerid][2], 0);
   PlayerTextDrawBackgroundColor(playerid, Text_Player[playerid][2], 255);
   PlayerTextDrawFont(playerid, Text_Player[playerid][2], 4);
   PlayerTextDrawSetProportional(playerid, Text_Player[playerid][2], 1);

   Text_Player[playerid][3] = CreatePlayerTextDraw(playerid, 558.000, 255.000, "ERROR");
   PlayerTextDrawLetterSize(playerid, Text_Player[playerid][3], 0.250, 1.350);
   PlayerTextDrawAlignment(playerid, Text_Player[playerid][3], 1);
   PlayerTextDrawColour(playerid, Text_Player[playerid][3], -1);
   PlayerTextDrawSetShadow(playerid, Text_Player[playerid][3], 1);
   PlayerTextDrawSetOutline(playerid, Text_Player[playerid][3], 1);
   PlayerTextDrawBackgroundColor(playerid, Text_Player[playerid][3], 150);
   PlayerTextDrawFont(playerid, Text_Player[playerid][3], 1);
   PlayerTextDrawSetProportional(playerid, Text_Player[playerid][3], 1);

   Text_Player[playerid][4] = CreatePlayerTextDraw(playerid, 558.000, 273.000, " ");
   PlayerTextDrawLetterSize(playerid, Text_Player[playerid][4], 0.170, 1.299);
   PlayerTextDrawAlignment(playerid, Text_Player[playerid][4], 1);
   PlayerTextDrawColour(playerid, Text_Player[playerid][4], -1);
   PlayerTextDrawSetShadow(playerid, Text_Player[playerid][4], 1);
   PlayerTextDrawSetOutline(playerid, Text_Player[playerid][4], 1);
   PlayerTextDrawBackgroundColor(playerid, Text_Player[playerid][4], 150);
   PlayerTextDrawFont(playerid, Text_Player[playerid][4], 1);
   PlayerTextDrawSetProportional(playerid, Text_Player[playerid][4], 1);
  return 1;
}

stock Error(playerid, const header[], const msg[], time_ms = 5000)
{
   PlayerTextDrawSetString(playerid, Text_Player[playerid][3], header);
   PlayerTextDrawSetString(playerid, Text_Player[playerid][4], msg);
  
   for(new i = 0; i < 5; i++) PlayerTextDrawShow(playerid, Text_Player[playerid][i]);

   SetTimerEx("HideSxoError", time_ms, false, "i", playerid);
  return 1;
}

forward HideSxoError(playerid);
public HideSxoError(playerid)
{
  for(new i = 0; i < 5; i++) PlayerTextDrawHide(playerid, Text_Player[playerid][i]);
  return 1;
}
