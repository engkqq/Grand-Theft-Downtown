/*
                    Grand Theft DownTown Roleplay - Engkq
    
    * Credits:
        - Engkq (Lead Developer)
        - Y_Less (YSI Library)
        - Incognito (YSI Library)
        - Incognito (MySQL Plugin)
        - Incognito (bcrypt Plugin)
        - Incognito (sscanf2 Plugin)
        - Incognito (easyDialog Plugin)
        - Incognito (CMD Plugin)
        - Incognito (Streamer Plugin)
        - Incognito (Open.MP Plugin)
        - Incognito (All other plugins)
        - All other contributors and testers

    * Note :
        - Terimkasih kepada semua yang telah berkontribusi dalam pengembangan gamemode ini. Tanpa kalian, gamemode ini tidak akan pernah terwujud. Kami sangat menghargai setiap bantuan dan dukungan yang telah diberikan.

    * Engkq (Lead Developer)
    * Ventra ABP.Rahman (Updaters & Developer)
    * None
*/

#define OPENMP_COMPAT
#define YSI_NO_VERSION_CHECK        // By Y_Less (Untuk mencegah pemeriksaan versi YSI yang tidak perlu).
#include <open.mp>                  // By Incognito (Open.MP Plugin).

#include "./modules/server/max.inc"

#include <YSI_Data\y_iterate>       // By Y_Less     (YSI Library untuk iterasi data).
#include <streamer>                 // By Incognito (Streamer Plugin untuk manajemen objek).
#include <Pawn.CMD>                 // By Incognito (CMD Plugin untuk perintah chat).
#include <a_mysql>                  // By Incognito (MySQL Plugin untuk koneksi database).
#include <samp_bcrypt>              // By Incognito (bcrypt untuk hashing password).
#include <sscanf2>                  // By Incognito (Enhanced sscanf).
#include <easyDialog>               // By Incognito (Dialog Interaktif).   
#include <engkqSelections>          // By Engkq     (Menu Interaktif).
#include <engkqAction>              // By Engkq     (Textdraws Pesan).
//#include <Info>                   // By Ventra
#include <compas>                   // By Ventra

//--------[ Loaded All Files ]-----------------
#include "./modules/load.inc"
