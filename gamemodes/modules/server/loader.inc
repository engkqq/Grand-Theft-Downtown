LoaderServers()
{
	mysql_tquery(g_SQL, "SELECT * FROM vehicles", "OnVehicleLoaded", "");
    mysql_tquery(g_SQL, "SELECT * FROM `doors`", "LoadDoors");
    print(">> Success Loadded All From Database!");
    return 1;
}