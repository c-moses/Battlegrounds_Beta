modded class MissionServer
{
    protected ref LayerConfig m_LayerConfig;
    protected ref BattlegroundsConfig m_Config;
    private ref map<string, int> m_SelectedLoadouts = new map<string, int> ();

    override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx)
	{
		string characterType;

        if (ProcessLoginData(ctx))
        {
            if (m_RespawnMode == GameConstants.RESPAWN_MODE_CUSTOM)
            {
                characterType = GetGame().CreateRandomPlayer();
            }
            else
            {
                int randomLoadout = Math.RandomInt(0, 10); 
			    m_SelectedLoadouts.Set(identity.GetId(), randomLoadout);

                characterType = GetGame().CreateRandomPlayer();
            }
        }

        int selectedLoadout = m_SelectedLoadouts.Get(identity.GetId());
		vector customSpawnPos = TeamSpawnPoints.GetSpawnForTeam(GetTeamForLoadout(selectedLoadout));

		if (CreateCharacter(identity, customSpawnPos, ctx, characterType))
		{
			EquipLoadout(m_player, selectedLoadout);
		}

		return m_player;
	}

	string GetTeamForLoadout(int selectedLoadout)
	{
		switch (selectedLoadout)
		{
			case 0:
			case 1:
			case 2:	
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
                return "Neutral";
			case 10:
                return "Nato";
			case 11:
                return "Soviet";
			default:
				return "Neutral";
		}
		return "Neutral"; // do not remove (compiler error, idk)
	}

        //  Loadouts
    static void EquipM65Black(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("M65Jacket_Black");
        player.GetInventory().CreateInInventory("CargoPants_Black");
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
    }

    static void EquipM65Green(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("M65Jacket_Olive");
        player.GetInventory().CreateInInventory("CargoPants_Green");
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
    }

    static void EquipQuiltedBlack(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("QuiltedJacket_Black");
        player.GetInventory().CreateInInventory("CargoPants_Black");
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
    }

    static void EquipQuiltedGreen(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("QuiltedJacket_Green");
        player.GetInventory().CreateInInventory("CargoPants_Green");
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
    }

    static void EquipCheckBlack(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("WoolCoat_BlackCheck");
        player.GetInventory().CreateInInventory("Jeans_Black");
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
    }

    static void EquipCheckBrown(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("WoolCoat_BrownCheck");
        player.GetInventory().CreateInInventory("Jeans_Black");
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
    }

    static void EquipHuntingBrown(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("HuntingJacket_Brown");
        player.GetInventory().CreateInInventory("HunterPants_Brown");
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
    }

    static void EquipHuntingSpring(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("HuntingJacket_Spring");
        player.GetInventory().CreateInInventory("HunterPants_Spring");
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
    }

    static void EquipHuntingSummer(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("HuntingJacket_Summer");
        player.GetInventory().CreateInInventory("HunterPants_Summer");
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
    }

    static void EquipHuntingAutumn(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("HuntingJacket_Autumn");
        player.GetInventory().CreateInInventory("HunterPants_Autumn");
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
    }

    static void EquipNato(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("BDUJacket");
        player.GetInventory().CreateInInventory("BDUPants");
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
    }

    static void EquipSoviet(PlayerBase player)
    {
        EntityAI itemEnt;
		AddPlayerStats(player);
        player.GetInventory().CreateInInventory("TTsKOJacket_Camo");
        player.GetInventory().CreateInInventory("TTSKOPants");
		EquipAK74(player);
		EquipNVG(player);
		EquipBelt(player);
        AddGeneralItems(player);
    }
    
	static void AddPlayerStats(PlayerBase player)
	{
		player.GetStatWater().Add(3400);
		player.GetStatEnergy().Add(3400);
	}

	static void EquipAK74(PlayerBase player)
	{
		EntityAI itemEnt = player.GetInventory().CreateInInventory("AKS74U");
		itemEnt.GetInventory().CreateInInventory("Rev_AK_Bttstck");

		AKS74U ak74Instance = AKS74U.Cast(itemEnt);
		if (ak74Instance)
		{
			ak74Instance.SpawnAttachedMagazine("Mag_AK74_30Rnd");
		}

		player.SetQuickBarEntityShortcut(ak74Instance, 1, true); // Set AK to slot 2
	}

    static void EquipNVG(PlayerBase player)
	{
		EntityAI itemEnt = CreateItemInInventory(player, "NVGHeadstrap");
		ItemBase nvg = ItemBase.Cast(CreateItemInEntity(itemEnt, "NVGoggles"));
		if (nvg)
		{
			CreateItemInEntity(nvg, "Battery9V");
		}
	}

	static void EquipBelt(PlayerBase player)
	{
    	EntityAI beltEnt = player.GetInventory().CreateInInventory("MilitaryBelt");

    	EntityAI bandage1 = beltEnt.GetInventory().CreateAttachment("BandageDressing");
    	player.SetQuickBarEntityShortcut(bandage1, 2, true);  // Set Bandage to slot 3

    	EntityAI knife = beltEnt.GetInventory().CreateAttachment("CombatKnife");
    	player.SetQuickBarEntityShortcut(knife, 3, true);  // Set Knife to slot 4

    	EntityAI mapInst = beltEnt.GetInventory().CreateAttachment("ChernarusMap");
    	player.SetQuickBarEntityShortcut(mapInst, 4, true);  // Set Map to slot 5

    	EntityAI radio = beltEnt.GetInventory().CreateAttachment("PersonalRadio");
    	if (radio)
    	{
        	radio.GetInventory().CreateInInventory("Battery9V");
        	player.SetQuickBarEntityShortcut(radio, 5, true);  // Set Radio to slot 6
    	}
	}

	static void AddGeneralItems(PlayerBase player)
	{
		int i;
		EntityAI itemEnt;

		player.GetInventory().CreateInInventory("CmsKit");
		CreateMultipleItems(player, "BloodBagIV", 2);
		CreateMultipleItems(player, "Mag_AK74_30Rnd", 6);
        CreateMultipleItems(player, "Ammo_545x39", 4);
        player.GetInventory().CreateInInventory("WoolGlovesFingerless_Black");
		player.GetInventory().CreateInInventory("MilitaryBoots_Black");
	}

    static EntityAI CreateItemInInventory(PlayerBase player, string itemName)
	{
		return player.GetInventory().CreateInInventory(itemName);
	}

	static EntityAI CreateItemInEntity(EntityAI entity, string itemName)
	{
		return entity.GetInventory().CreateInInventory(itemName);
	}

	static void CreateMultipleItems(PlayerBase player, string itemName, int count)
	{
		for (int i = 0; i < count; i++)
		{
			player.GetInventory().CreateInInventory(itemName);
		}
	}

    /* /////////////////////////////////////////////////////////////////////////////////////////// */

    PlayerBase EquipLoadout(PlayerBase playerInstance, int selectedLoadout)
    {
        string team = GetTeamForLoadout(selectedLoadout);
		vector spawnPos = TeamSpawnPoints.GetSpawnForTeam(team);

        switch(selectedLoadout)
        {
            case 0:
                EquipQuiltedBlack(playerInstance);
                break;
            case 1:
                EquipQuiltedGreen(playerInstance);
                break;
            case 2:
                EquipHuntingSummer(playerInstance);
                break;
            case 3:
                EquipHuntingAutumn(playerInstance);
                break;
            case 4:
                EquipCheckBlack(playerInstance);
                break;
            case 5:
                EquipCheckBrown(playerInstance);
                break;
            case 6:
                EquipHuntingBrown(playerInstance);
                break;
            case 7:
                EquipHuntingSpring(playerInstance);
                break;
            case 8:
                EquipM65Black(playerInstance);
                break;
            case 9:
                EquipM65Green(playerInstance);
                break;
            case 10:
                EquipNato(playerInstance);
                break;
            case 11:
                EquipSoviet(playerInstance);
                break;
            default:
			int randomDefault = Math.RandomInt(0, 10);
			switch (randomDefault)
			{
				case 0:
                    EquipQuiltedBlack(playerInstance);
                    break;
                case 1:
                    EquipQuiltedGreen(playerInstance);
                    break;
                case 2:
                    EquipHuntingSummer(playerInstance);
                    break;
                case 3:
                    EquipHuntingAutumn(playerInstance);
                    break;
                case 4:
                    EquipCheckBlack(playerInstance);
                    break;
                case 5:
                    EquipCheckBrown(playerInstance);
                    break;
                case 6:
                    EquipHuntingBrown(playerInstance);
                    break;
                case 7:
                    EquipHuntingSpring(playerInstance);
                    break;
                case 8:
                    EquipM65Black(playerInstance);
                    break;
                case 9:
                    EquipM65Green(playerInstance);
                    break;
			}
			break;
        }
        playerInstance.SetPosition(spawnPos);

		//Print("Spawn Position: " + spawnPos.ToString());
		//Print("Player Set Position: " + playerInstance.GetPosition().ToString());

		return playerInstance;
    }

    /* /////////////////////////////////////////////////////////////////////////////////////////// */

    void MissionServer()
    {
        if(!LayerConfigLoader.LoadConfig("$profile:Battlegrounds/Layer.json", m_LayerConfig))
        {
            LayerConfigLoader.CreateDefaultConfig("$profile:Battlegrounds/Layer.json");
            LayerConfigLoader.LoadConfig("$profile:Battlegrounds/Layer.json", m_LayerConfig);  // Load again after creating default
        }
        //Print("[MissionServer] Loaded: " + m_LayerConfig.LayerMode);

        if(!BattlegroundsConfigLoader.LoadConfig("Battlegrounds.json", m_Config))
        {
            //Print("[MissionServer] Error: Failed to load Battlegrounds.json");
            return;
        }

        GetDayZGame().SetBattlegroundsConfig(m_Config);
        GetDayZGame().SetBGPlayerStatsMap(m_Config);
    }

    override void OnInit()
    {
        super.OnInit();

        GetRPCManager().AddRPC("Battlegrounds", "LeaderboardSync", this, SingleplayerExecutionType.Both);
        GetRPCManager().AddRPC("LoadoutSelect", "RespawnMode", this, SingleplayerExecutionType.Server);

        if (GetGame())
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.InitBattlegrounds, 3000, false);
        }
    }

    void InitBattlegrounds()
    {
        if (GetGame())
        {
            BattlegroundsEventManager.GetInstance().Init(m_LayerConfig.LayerMode);

            // Initialize BGLeaderboardManager
            if (m_Config && m_Config.Players)
            {
                BGLeaderboardManager.GetInstance(m_Config.Players);
            }
        }
    }

    override void OnUpdate(float timeslice)
    {
        if (GetGame())
        {
            BattlegroundsEventManager.GetInstance().OnUpdate(timeslice);
            super.OnUpdate(timeslice);
        }
    }

	void RespawnMode(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		{
			if (type != CallType.Server)
				return;

			Param1<int> data;
			if (!ctx.Read(data))
				return;

			if (sender == null)
				return;

			int clientResponse = data.param1;
			m_SelectedLoadouts.Set(sender.GetId(), clientResponse);

			//Print("MissionServer RPC recieved: selected loadout " + clientResponse);
		}
	}

    void LeaderboardSync(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server)
        {
            BGLeaderboardManager manager = BGLeaderboardManager.GetInstance();

            if (manager)
            {
                // Sort players based on cashEarned
                manager.QuickSortByCashEarned(0, m_Config.Players.Count() - 1);

                array<BGPlayerStats> sortedPlayers = manager.GetSortedList("desc");

                // Now, you can fetch top 50 players
                array<BGPlayerStats> top50Players = new array<BGPlayerStats>();
                for (int i = 0; i < sortedPlayers.Count() && i < 50; i++)
                {
                    top50Players.Insert(sortedPlayers.Get(i));
                }

                Param2<array<BGPlayerStats>, string> data = new Param2<array<BGPlayerStats>, string>(top50Players, "additional info");

                GetRPCManager().SendRPC("Battlegrounds", "LeaderboardDataSync", data, true, sender);

                /*for (int j = 0; j < top50Players.Count(); j++)
                {
                    BGPlayerStats player = top50Players.Get(j);
                    Print("[LeaderboardSync] Rank: " + (j + 1).ToString());
                    Print("Player Name: " + player.playerName);
                    Print("Player Kills: " + player.playerKills.ToString());
                    Print("Zombie Kills: " + player.zombieKills.ToString());
                    Print("Deaths: " + player.deaths.ToString());
                    Print("Cash Earned: " + player.cashEarned.ToString());
                    Print("----------------------------------------");
                }*/
            }
            else
            {
                //Print("[LeaderboardSync] No player data found in the loaded configuration or BGLeaderboardManager not initialized.");
            }
        }
    }
}