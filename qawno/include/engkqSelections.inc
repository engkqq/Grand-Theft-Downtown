/* 
 * eSelections.inc - Custom Model Selection System with File Loader
 * Terinspirasi oleh mSelection.inc untuk open.mp
 * Dibuat oleh Engkq - 2026
 */

#if defined _e_selections_included
    #endinput
#endif
#define _e_selections_included

#include <open.mp>

#define E_SELECTION_MAX_SLOTS       15
#define E_SELECTION_INVALID_INDEX   -1
#define E_SELECTION_MAX_MODELS      256 // Kapasitas penampung ID model dari file.

enum e_SelectionPlayerData {
    bool:e_IsMenuOpen,
    e_CurrentPage,
    e_TotalPages,
    e_MenuExtraID,
    e_SelectedModel,
    e_ModelArray[E_SELECTION_MAX_MODELS],
    e_TotalModels
}
static PlayerMenuData[MAX_PLAYERS][e_SelectionPlayerData];

static PlayerText:EngkqSelections[MAX_PLAYERS][9];
static PlayerText:EngkqJudul[MAX_PLAYERS];
static PlayerText:EngkqPilihan[MAX_PLAYERS][E_SELECTION_MAX_SLOTS];
static PlayerText:EngkqSelectButton[MAX_PLAYERS];
static PlayerText:EngkqBackButton[MAX_PLAYERS];
static PlayerText:EngkqNextButton[MAX_PLAYERS];

forward OnPlayerSelectEModel(playerid, extraid, index, modelid);
static eSelection_UpdatePage(playerid);

// =============================================================================
// FUNGSI: Menampilkan Menu Berdasarkan Array Langsung
// =============================================================================
stock ShowPlayereSelection(playerid, const headerTitle[], extraid, const models[], total_models)
{
    if(PlayerMenuData[playerid][e_IsMenuOpen]) {
        HidePlayereSelection(playerid);
    }

    if(total_models > E_SELECTION_MAX_MODELS) total_models = E_SELECTION_MAX_MODELS;

    PlayerMenuData[playerid][e_TotalModels] = total_models;
    PlayerMenuData[playerid][e_MenuExtraID] = extraid;
    PlayerMenuData[playerid][e_CurrentPage] = 0;
    PlayerMenuData[playerid][e_SelectedModel] = E_SELECTION_INVALID_INDEX;
    PlayerMenuData[playerid][e_TotalPages] = (total_models + (E_SELECTION_MAX_SLOTS - 1)) / E_SELECTION_MAX_SLOTS;

    for(new i = 0; i < total_models; i++) {
        PlayerMenuData[playerid][e_ModelArray][i] = models[i];
    }

    // Pembuatan TextDraw Dasar & Background (Sesuai kode orimu)
    EngkqSelections[playerid][0] = CreatePlayerTextDraw(playerid, 139.000, 100.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, EngkqSelections[playerid][0], 351.000, 274.000);
    PlayerTextDrawAlignment(playerid, EngkqSelections[playerid][0], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, EngkqSelections[playerid][0], 1768516095);
    PlayerTextDrawSetShadow(playerid, EngkqSelections[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, EngkqSelections[playerid][0], 0);
    PlayerTextDrawBackgroundColour(playerid, EngkqSelections[playerid][0], 255);
    PlayerTextDrawFont(playerid, EngkqSelections[playerid][0], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, EngkqSelections[playerid][0], true);

    EngkqSelections[playerid][1] = CreatePlayerTextDraw(playerid, 137.000, 98.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, EngkqSelections[playerid][1], 8.000, 9.000);
    PlayerTextDrawAlignment(playerid, EngkqSelections[playerid][1], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, EngkqSelections[playerid][1], 1768516095);
    PlayerTextDrawSetShadow(playerid, EngkqSelections[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, EngkqSelections[playerid][1], 0);
    PlayerTextDrawBackgroundColour(playerid, EngkqSelections[playerid][1], 255);
    PlayerTextDrawFont(playerid, EngkqSelections[playerid][1], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, EngkqSelections[playerid][1], true);

    EngkqSelections[playerid][2] = CreatePlayerTextDraw(playerid, 137.000, 367.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, EngkqSelections[playerid][2], 8.000, 9.000);
    PlayerTextDrawAlignment(playerid, EngkqSelections[playerid][2], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, EngkqSelections[playerid][2], 1768516095);
    PlayerTextDrawSetShadow(playerid, EngkqSelections[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, EngkqSelections[playerid][2], 0);
    PlayerTextDrawBackgroundColour(playerid, EngkqSelections[playerid][2], 255);
    PlayerTextDrawFont(playerid, EngkqSelections[playerid][2], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, EngkqSelections[playerid][2], true);

    EngkqSelections[playerid][3] = CreatePlayerTextDraw(playerid, 484.000, 367.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, EngkqSelections[playerid][3], 8.000, 9.000);
    PlayerTextDrawAlignment(playerid, EngkqSelections[playerid][3], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, EngkqSelections[playerid][3], 1768516095);
    PlayerTextDrawSetShadow(playerid, EngkqSelections[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, EngkqSelections[playerid][3], 0);
    PlayerTextDrawBackgroundColour(playerid, EngkqSelections[playerid][3], 255);
    PlayerTextDrawFont(playerid, EngkqSelections[playerid][3], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, EngkqSelections[playerid][3], true);

    EngkqSelections[playerid][4] = CreatePlayerTextDraw(playerid, 484.000, 98.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, EngkqSelections[playerid][4], 8.000, 9.000);
    PlayerTextDrawAlignment(playerid, EngkqSelections[playerid][4], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, EngkqSelections[playerid][4], 1768516095);
    PlayerTextDrawSetShadow(playerid, EngkqSelections[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, EngkqSelections[playerid][4], 0);
    PlayerTextDrawBackgroundColour(playerid, EngkqSelections[playerid][4], 255);
    PlayerTextDrawFont(playerid, EngkqSelections[playerid][4], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, EngkqSelections[playerid][4], true);

    EngkqSelections[playerid][5] = CreatePlayerTextDraw(playerid, 143.000, 106.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, EngkqSelections[playerid][5], 343.000, 263.000);
    PlayerTextDrawAlignment(playerid, EngkqSelections[playerid][5], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, EngkqSelections[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, EngkqSelections[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, EngkqSelections[playerid][5], 0);
    PlayerTextDrawBackgroundColour(playerid, EngkqSelections[playerid][5], 255);
    PlayerTextDrawFont(playerid, EngkqSelections[playerid][5], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, EngkqSelections[playerid][5], true);

    // Label Teks Kanan
    EngkqSelections[playerid][6] = CreatePlayerTextDraw(playerid, 518.000, 355.000, "Select");
    PlayerTextDrawLetterSize(playerid, EngkqSelections[playerid][6], 0.230, 1.500);
    PlayerTextDrawAlignment(playerid, EngkqSelections[playerid][6], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColour(playerid, EngkqSelections[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, EngkqSelections[playerid][6], 1);
    PlayerTextDrawSetOutline(playerid, EngkqSelections[playerid][6], 0);
    PlayerTextDrawBackgroundColour(playerid, EngkqSelections[playerid][6], 150);
    PlayerTextDrawFont(playerid, EngkqSelections[playerid][6], TEXT_DRAW_FONT_2);
    PlayerTextDrawSetProportional(playerid, EngkqSelections[playerid][6], true);

    EngkqSelections[playerid][7] = CreatePlayerTextDraw(playerid, 518.000, 329.000, "<<");
    PlayerTextDrawLetterSize(playerid, EngkqSelections[playerid][7], 0.230, 1.500);
    PlayerTextDrawAlignment(playerid, EngkqSelections[playerid][7], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColour(playerid, EngkqSelections[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, EngkqSelections[playerid][7], 1);
    PlayerTextDrawSetOutline(playerid, EngkqSelections[playerid][7], 0);
    PlayerTextDrawBackgroundColour(playerid, EngkqSelections[playerid][7], 150);
    PlayerTextDrawFont(playerid, EngkqSelections[playerid][7], TEXT_DRAW_FONT_2);
    PlayerTextDrawSetProportional(playerid, EngkqSelections[playerid][7], true);

    EngkqSelections[playerid][8] = CreatePlayerTextDraw(playerid, 518.000, 303.000, ">>");
    PlayerTextDrawLetterSize(playerid, EngkqSelections[playerid][8], 0.230, 1.500);
    PlayerTextDrawAlignment(playerid, EngkqSelections[playerid][8], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColour(playerid, EngkqSelections[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, EngkqSelections[playerid][8], 1);
    PlayerTextDrawSetOutline(playerid, EngkqSelections[playerid][8], 0);
    PlayerTextDrawBackgroundColour(playerid, EngkqSelections[playerid][8], 150);
    PlayerTextDrawFont(playerid, EngkqSelections[playerid][8], TEXT_DRAW_FONT_2);
    PlayerTextDrawSetProportional(playerid, EngkqSelections[playerid][8], true);

    // Judul Dinamis
    EngkqJudul[playerid] = CreatePlayerTextDraw(playerid, 314.000, 87.000, headerTitle);
    PlayerTextDrawLetterSize(playerid, EngkqJudul[playerid], 0.359, 2.699);
    PlayerTextDrawAlignment(playerid, EngkqJudul[playerid], TEXT_DRAW_ALIGN_CENTER);
    PlayerTextDrawColour(playerid, EngkqJudul[playerid], -1);
    PlayerTextDrawSetShadow(playerid, EngkqJudul[playerid], 1);
    PlayerTextDrawSetOutline(playerid, EngkqJudul[playerid], 1);
    PlayerTextDrawBackgroundColour(playerid, EngkqJudul[playerid], 150);
    PlayerTextDrawFont(playerid, EngkqJudul[playerid], TEXT_DRAW_FONT_3);
    PlayerTextDrawSetProportional(playerid, EngkqJudul[playerid], true);

    // Tombol Navigasi Box Aktif (Selectable)
    EngkqSelectButton[playerid] = CreatePlayerTextDraw(playerid, 494.000, 352.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, EngkqSelectButton[playerid], 46.000, 22.000);
    PlayerTextDrawAlignment(playerid, EngkqSelectButton[playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, EngkqSelectButton[playerid], 1768516095);
    PlayerTextDrawSetShadow(playerid, EngkqSelectButton[playerid], 0);
    PlayerTextDrawSetOutline(playerid, EngkqSelectButton[playerid], 0);
    PlayerTextDrawBackgroundColour(playerid, EngkqSelectButton[playerid], 255);
    PlayerTextDrawFont(playerid, EngkqSelectButton[playerid], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, EngkqSelectButton[playerid], true);
    PlayerTextDrawSetSelectable(playerid, EngkqSelectButton[playerid], true);

    EngkqBackButton[playerid] = CreatePlayerTextDraw(playerid, 494.000, 326.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, EngkqBackButton[playerid], 46.000, 22.000);
    PlayerTextDrawAlignment(playerid, EngkqBackButton[playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, EngkqBackButton[playerid], 1768516095);
    PlayerTextDrawSetShadow(playerid, EngkqBackButton[playerid], 0);
    PlayerTextDrawSetOutline(playerid, EngkqBackButton[playerid], 0);
    PlayerTextDrawBackgroundColour(playerid, EngkqBackButton[playerid], 255);
    PlayerTextDrawFont(playerid, EngkqBackButton[playerid], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, EngkqBackButton[playerid], true);
    PlayerTextDrawSetSelectable(playerid, EngkqBackButton[playerid], true);

    EngkqNextButton[playerid] = CreatePlayerTextDraw(playerid, 494.000, 299.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, EngkqNextButton[playerid], 46.000, 22.000);
    PlayerTextDrawAlignment(playerid, EngkqNextButton[playerid], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, EngkqNextButton[playerid], 1768516095);
    PlayerTextDrawSetShadow(playerid, EngkqNextButton[playerid], 0);
    PlayerTextDrawSetOutline(playerid, EngkqNextButton[playerid], 0);
    PlayerTextDrawBackgroundColour(playerid, EngkqNextButton[playerid], 255);
    PlayerTextDrawFont(playerid, EngkqNextButton[playerid], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, EngkqNextButton[playerid], true);
    PlayerTextDrawSetSelectable(playerid, EngkqNextButton[playerid], true);

    // =============================================================================
    // LOGIKA GRID OTOMATIS: 15 Slot Mengikuti Koordinat Ori Kebawah
    // =============================================================================
    // Koordinat Posisi X asli dari 5 slot buatanmu
    new Float:slotPosX[5] = {151.000, 214.000, 285.000, 354.000, 418.000};
    new Float:startPosY = 116.000; // Koordinat Y asli baris pertama
    new Float:spacingY = 82.000;   // Jarak kebawah agar muat 3 baris di dalam box background

    for(new i = 0; i < E_SELECTION_MAX_SLOTS; i++) 
    {
        new row = i / 5; // Menghitung baris (0 hingga 2)
        new col = i % 5; // Menghitung kolom (0 hingga 4)

        new Float:finalX = slotPosX[col];
        new Float:finalY = startPosY + (row * spacingY);

        EngkqPilihan[playerid][i] = CreatePlayerTextDraw(playerid, finalX, finalY, "_");
        PlayerTextDrawTextSize(playerid, EngkqPilihan[playerid][i], 60.000, 74.000); // Ukuran kotak asli
        PlayerTextDrawAlignment(playerid, EngkqPilihan[playerid][i], TEXT_DRAW_ALIGN_LEFT);
        PlayerTextDrawColour(playerid, EngkqPilihan[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, EngkqPilihan[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, EngkqPilihan[playerid][i], 0);
        PlayerTextDrawBackgroundColour(playerid, EngkqPilihan[playerid][i], 85);
        PlayerTextDrawFont(playerid, EngkqPilihan[playerid][i], TEXT_DRAW_FONT_MODEL_PREVIEW);
        PlayerTextDrawSetProportional(playerid, EngkqPilihan[playerid][i], false);
        PlayerTextDrawSetSelectable(playerid, EngkqPilihan[playerid][i], true);
    }

    // Tampilkan Komponen Dasar ke Layar
    for(new i = 0; i < 9; i++) PlayerTextDrawShow(playerid, EngkqSelections[playerid][i]);
    PlayerTextDrawShow(playerid, EngkqJudul[playerid]);
    PlayerTextDrawShow(playerid, EngkqSelectButton[playerid]);
    PlayerTextDrawShow(playerid, EngkqBackButton[playerid]);
    PlayerTextDrawShow(playerid, EngkqNextButton[playerid]);

    PlayerMenuData[playerid][e_IsMenuOpen] = true;
    
    eSelection_UpdatePage(playerid);
    SelectTextDraw(playerid, 0xA0A0A0FF); 
    return 1;
}

// =============================================================================
// FUNGSI: Menampilkan Menu dengan Membaca File dari scriptfiles
// =============================================================================
stock ShowPlayereSelectionEngkq(playerid, const headerTitle[], extraid, const fileName[])
{
    new File:fHandle = fopen(fileName, io_read);
    if(!fHandle) {
        printf("[eSelections Error]: File tidak ditemukan di scriptfiles/%s", fileName);
        return 0;
    }

    new lineData[32], tempModels[E_SELECTION_MAX_MODELS], count = 0;

    while(fread(fHandle, lineData)) 
    {
        for(new i = 0, l = strlen(lineData); i < l; i++) {
            if(lineData[i] == '\r' || lineData[i] == '\n') {
                lineData[i] = '\0';
                break;
            }
        }

        if(lineData[0] == '\0') continue;

        tempModels[count] = strval(lineData);
        count++;

        if(count >= E_SELECTION_MAX_MODELS) break;
    }
    fclose(fHandle);

    if(count == 0) {
        printf("[eSelections Warning]: File %s kosong.", fileName);
        return 0;
    }

    return ShowPlayereSelection(playerid, headerTitle, extraid, tempModels, count);
}

// =============================================================================
// FUNGSI INTERNAL: Memperbarui Item Sesuai Halaman
// =============================================================================
static eSelection_UpdatePage(playerid)
{
    new index_awal = PlayerMenuData[playerid][e_CurrentPage] * E_SELECTION_MAX_SLOTS;

    for(new i = 0; i < E_SELECTION_MAX_SLOTS; i++) 
    {
        new array_idx = index_awal + i;

        if(array_idx < PlayerMenuData[playerid][e_TotalModels]) 
        {
            new modelid = PlayerMenuData[playerid][e_ModelArray][array_idx];
            PlayerTextDrawSetPreviewModel(playerid, EngkqPilihan[playerid][i], modelid);
            PlayerTextDrawSetPreviewRot(playerid, EngkqPilihan[playerid][i], 0.000, 0.000, 0.000, 1.000);
            
            if(PlayerMenuData[playerid][e_SelectedModel] == i) {
                PlayerTextDrawBackgroundColour(playerid, EngkqPilihan[playerid][i], 0x808080AA); 
            } else {
                PlayerTextDrawBackgroundColour(playerid, EngkqPilihan[playerid][i], 85); 
            }

            PlayerTextDrawShow(playerid, EngkqPilihan[playerid][i]);
        } 
        else 
        {
            PlayerTextDrawHide(playerid, EngkqPilihan[playerid][i]);
        }
    }
    return 1;
}

// =============================================================================
// FUNGSI UTAMA: Menutup Menu
// =============================================================================
stock HidePlayereSelection(playerid)
{
    if(!PlayerMenuData[playerid][e_IsMenuOpen]) return 0;

    for(new i = 0; i < 9; i++) {
        PlayerTextDrawDestroy(playerid, EngkqSelections[playerid][i]);
    }
    PlayerTextDrawDestroy(playerid, EngkqJudul[playerid]);
    PlayerTextDrawDestroy(playerid, EngkqSelectButton[playerid]);
    PlayerTextDrawDestroy(playerid, EngkqBackButton[playerid]);
    PlayerTextDrawDestroy(playerid, EngkqNextButton[playerid]);

    for(new i = 0; i < E_SELECTION_MAX_SLOTS; i++) {
        PlayerTextDrawDestroy(playerid, EngkqPilihan[playerid][i]);
    }

    PlayerMenuData[playerid][e_IsMenuOpen] = false;
    CancelSelectTextDraw(playerid); 
    return 1;
}

// =============================================================================
// HOOK CALLBACK: Deteksi Klik TextDraw
// =============================================================================
public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    if(!PlayerMenuData[playerid][e_IsMenuOpen]) {
        #if defined eSelection_OnPlayerClickPlayerTD
            return eSelection_OnPlayerClickPlayerTD(playerid, playertextid);
        #else
            return 0;
        #endif
    }

    // Tombol Next ">>"
    if(playertextid == EngkqNextButton[playerid])
    {
        if(PlayerMenuData[playerid][e_CurrentPage] < PlayerMenuData[playerid][e_TotalPages] - 1) {
            PlayerMenuData[playerid][e_CurrentPage]++;
            PlayerMenuData[playerid][e_SelectedModel] = E_SELECTION_INVALID_INDEX; 
            eSelection_UpdatePage(playerid);
        }
        return 1;
    }

    // Tombol Back "<<"
    if(playertextid == EngkqBackButton[playerid])
    {
        if(PlayerMenuData[playerid][e_CurrentPage] > 0) {
            PlayerMenuData[playerid][e_CurrentPage]--;
            PlayerMenuData[playerid][e_SelectedModel] = E_SELECTION_INVALID_INDEX;
            eSelection_UpdatePage(playerid);
        }
        return 1;
    }

    // Tombol Ambil Item ("Select")
    if(playertextid == EngkqSelectButton[playerid])
    {
        new selected_idx = PlayerMenuData[playerid][e_SelectedModel];
        if(selected_idx != E_SELECTION_INVALID_INDEX) 
        {
            new array_actual_idx = (PlayerMenuData[playerid][e_CurrentPage] * E_SELECTION_MAX_SLOTS) + selected_idx;
            new final_modelid = PlayerMenuData[playerid][e_ModelArray][array_actual_idx];
            new extraid = PlayerMenuData[playerid][e_MenuExtraID];

            CallLocalFunction("OnPlayerSelectEModel", "dddd", playerid, extraid, array_actual_idx, final_modelid);
            HidePlayereSelection(playerid);
        }
        return 1;
    }

    // Deteksi Klik pada Grid Slot Model (15 Slot)
    for(new i = 0; i < E_SELECTION_MAX_SLOTS; i++)
    {
        if(playertextid == EngkqPilihan[playerid][i])
        {
            PlayerMenuData[playerid][e_SelectedModel] = i;
            eSelection_UpdatePage(playerid); 
            return 1;
        }
    }

    #if defined eSelection_OnPlayerClickPlayerTD
        return eSelection_OnPlayerClickPlayerTD(playerid, playertextid);
    #else
        return 0;
    #endif
}

#if defined _ALS_OnPlayerClickPlayerTD
    #undef OnPlayerClickPlayerTextDraw
#else
    #define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw eSelection_OnPlayerClickPlayerTD
#if defined eSelection_OnPlayerClickPlayerTD
    forward eSelection_OnPlayerClickPlayerTD(playerid, PlayerText:playertextid);
#endif