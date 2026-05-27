new Text: EngkqNameServers[3];

stock CreateGlobalTextdraw()
{
    EngkqNameServers[0] = TextDrawCreate(320.000, 3.000, "GTA");
    TextDrawLetterSize(EngkqNameServers[0], 0.499, 2.899);
    TextDrawAlignment(EngkqNameServers[0], TEXT_DRAW_ALIGN_CENTER);
    TextDrawColour(EngkqNameServers[0], -1);
    TextDrawSetShadow(EngkqNameServers[0], 1);
    TextDrawSetOutline(EngkqNameServers[0], 1);
    TextDrawBackgroundColour(EngkqNameServers[0], 150);
    TextDrawFont(EngkqNameServers[0], TEXT_DRAW_FONT_3);
    TextDrawSetProportional(EngkqNameServers[0], true);

    EngkqNameServers[1] = TextDrawCreate(322.000, 20.000, "Down");
    TextDrawLetterSize(EngkqNameServers[1], 0.260, 1.199);
    TextDrawAlignment(EngkqNameServers[1], TEXT_DRAW_ALIGN_CENTER);
    TextDrawColour(EngkqNameServers[1], 1768516095);
    TextDrawSetShadow(EngkqNameServers[1], 1);
    TextDrawSetOutline(EngkqNameServers[1], 1);
    TextDrawBackgroundColour(EngkqNameServers[1], 150);
    TextDrawFont(EngkqNameServers[1], TEXT_DRAW_FONT_0);
    TextDrawSetProportional(EngkqNameServers[1], true);

    EngkqNameServers[2] = TextDrawCreate(330.000, 25.000, "Town");
    TextDrawLetterSize(EngkqNameServers[2], 0.260, 1.199);
    TextDrawAlignment(EngkqNameServers[2], TEXT_DRAW_ALIGN_CENTER);
    TextDrawColour(EngkqNameServers[2], 1768516095);
    TextDrawSetShadow(EngkqNameServers[2], 1);
    TextDrawSetOutline(EngkqNameServers[2], 1);
    TextDrawBackgroundColour(EngkqNameServers[2], 150);
    TextDrawFont(EngkqNameServers[2], TEXT_DRAW_FONT_0);
    TextDrawSetProportional(EngkqNameServers[2], true);
}