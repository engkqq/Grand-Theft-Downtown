/* NOTICE TEXTDRAW 
* AUTHOR: Ventra ABP.Rahman
* SINCE: 03/05/2026
*/

#if defined _inc_Notice
    #endinput
#endif
#define _inc_Notice

#include <open.mp>

static PlayerText:NoticeTD[MAX_PLAYERS][6];

stock InitNoticeTD(playerid)
{
   NoticeTD[playerid][0] = CreatePlayerTextDraw(playerid, 535.000, 250.000, "LD_SPAC:black");
   PlayerTextDrawTextSize(playerid, NoticeTD[playerid][0], 100.000, 50.000);
   PlayerTextDrawColor(playerid, NoticeTD[playerid][0], 1116206516);
   PlayerTextDrawFont(playerid, NoticeTD[playerid][0], 4);

   NoticeTD[playerid][1] = CreatePlayerTextDraw(playerid, 531.000, 250.000, "LD_SPAC:white");
   PlayerTextDrawTextSize(playerid, NoticeTD[playerid][1], 4.000, 50.000);
   PlayerTextDrawColor(playerid, NoticeTD[playerid][1], -2139062017);
   PlayerTextDrawFont(playerid, NoticeTD[playerid][1], 4);

   NoticeTD[playerid][2] = CreatePlayerTextDraw(playerid, 558.000, 255.000, "NOTICE");
   PlayerTextDrawLetterSize(playerid, NoticeTD[playerid][2], 0.250, 1.350);
   PlayerTextDrawColor(playerid, NoticeTD[playerid][2], -1);
   PlayerTextDrawFont(playerid, NoticeTD[playerid][2], 1);

   NoticeTD[playerid][3] = CreatePlayerTextDraw(playerid, 540.000, 267.000, "LD_CHAT:goodcha");
   PlayerTextDrawTextSize(playerid, NoticeTD[playerid][3], 13.000, 17.000);
   PlayerTextDrawColor(playerid, NoticeTD[playerid][3], -1);
   PlayerTextDrawFont(playerid, NoticeTD[playerid][3], 4);

   NoticeTD[playerid][4] = CreatePlayerTextDraw(playerid, 558.000, 273.000, " ");
   PlayerTextDrawLetterSize(playerid, NoticeTD[playerid][4], 0.170, 1.299);
   PlayerTextDrawFont(playerid, NoticeTD[playerid][4], 1);

   NoticeTD[playerid][5] = CreatePlayerTextDraw(playerid, 558.000, 284.000, " ");
   PlayerTextDrawLetterSize(playerid, NoticeTD[playerid][5], 0.170, 1.299);
   PlayerTextDrawFont(playerid, NoticeTD[playerid][5], 1);
  return 1;
}

stock Notice(playerid, const header[], const msg[], time_ms = 4000)
{
   PlayerTextDrawSetString(playerid, NoticeTD[playerid][2], header);
   PlayerTextDrawSetString(playerid, NoticeTD[playerid][4], msg);
  
   for(new i = 0; i < 6; i++) PlayerTextDrawShow(playerid, NoticeTD[playerid][i]);
  
   SetTimerEx("HideSxoNotice", 6000, false, "i", playerid);
  return 1;
}

// Gunakan forward dan public agar bisa dipanggil oleh SetTimerEx
forward HideSxoNotice(playerid);
public HideSxoNotice(playerid)
{
    for(new i = 0; i < 6; i++) 
    {
        PlayerTextDrawHide(playerid, NoticeTD[playerid][i]);
    }
    return 1;
}
