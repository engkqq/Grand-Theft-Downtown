LoaderServers()
{
	mysql_tquery(g_SQL, "SELECT * FROM vehicles", "OnVehicleLoaded", "");
    print(">> Success Loadded All From Database!");
    return 1;
}