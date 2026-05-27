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

* List Changelogs - v0.0.1b :
[+] Added & Improvements
- Added 'Name Server' feature to allow players to set their own server name.
- Added 'Login & Register With UCP' fitur untuk memungkinkan pemain masuk dan mendaftar menggunakan User Control Panel (UCP).
- Added 'Player Data Saving' fitur untuk menyimpan data pemain secara otomatis ke database.
- Added System 'Vehicle'
- Added Commands 'Players & Admins'
- Added 'EngkqF:' digunakan untuk menggantikan 'forward & public' agar lebih mudah dalam penulisan kode.

================================================================================================================

* Status : 6%
* List Changelogs - v0.0.2b :
[+] Added & Improvements
- Added 'engkqSelections' untuk membuat menu interaktif dengan mudah.
- Added 'Skins Selection' fitur untuk memungkinkan pemain memilih skin karakter mereka.
- Added 'Remove Player Money' fitur untuk memungkinkan admins mengurangi uang mereka.
- Added Fungsi 'ShowInfo' untuk menampilkan informasi penting kepada pemain saat mereka masuk ke dalam game.
- Added 'engkqAction' untuk menampilkan pesan dengan textdraws yang lebih baik.

- Improvements `engkqSelections` meningkatkan performa dan textdraw.

[=] Changed & Fixes
- Fixes pada 'Database' query untuk menyimpan data pemain dengan benar.

================================================================================================================

* Status : IN PROGRESS % - :downtown:
* List Changelogs - v0.0.2b :
[+] Added & Improvements
- Improvements Dialog 'Whitelist, Register Dan Lain Lain'

[=] Changed & Fixes
- Fixes 'RemoveBuildingServers' untuk menghapus bangunan dengan benar bagi pemain.

[-] Removed & Deprecated
-

*/
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

//--------[ Loaded All Files ]-----------------
#include "./modules/load.inc"