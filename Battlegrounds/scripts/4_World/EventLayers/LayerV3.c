class BGLayer3 extends BGBaseLayer // Battle of Prison Island
{
    vector m_PreviousEventPosition;
    bool m_PreviousEventPositionSet;
    string m_CurrentLocationName, m_LastLocationName, m_SecondLastLocationName;
    protected ref array<Object> m_CurrentObjects = new array<Object> ();
	private bool m_LastCheckedPlayerInZone = false;
    protected float m_CaptureProgress = 0.0;
    private float m_CaptureProgressSpeed = 100.0 / 300.0; // % divided by seconds = 5 mins
    const float CAPTURE_PROGRESS_CHECK_INTERVAL = 1.0;
    const float PLAYERS_IN_RADIUS_CHECK_INTERVAL = 10.0;
    private int m_Direction = 1;

    override void InitLayer()
    {
        super.InitLayer();

        InitLocations();
        BGCreateNewEvent();
        SetTeleporterDestinations();
    }

    void BGCreateNewEvent()
    {
        BattlegroundsLocation location = GetNextLocation();
        if (location)
        {
            m_SecondLastLocationName = m_LastLocationName;
            m_LastLocationName = m_CurrentLocationName;

            vector m_EventPosition = location.GetPosition();
            m_CurrentLocationName = location.GetName();

            Print("[BattlegroundsV3] New Event: " + m_CurrentLocationName);
                
            CreateSmokeEvent(m_EventPosition, "BGSmokeGreen", "BGSmokeRed", 100.0);
                
            m_CaptureProgress = 0.0;

            m_PreviousEventPosition = m_EventPosition;
            m_PreviousEventPositionSet = true;
        }
    }

    override void SetTeleporterDestinations() 
    {
        if (m_Teleporters && m_Teleporters.Count() > 0)
        {
            vector destination = GetNextLocation().GetPosition();
            for (int i = 0; i < m_Teleporters.Count(); i++)
            {
                m_Teleporters[i].SetDestination(destination);
            }
        }
    }

	override void CheckCaptureProgress()
    {
        array<Man> playersInRadius = GetPlayersInRadius(m_EventLocation, 100);
        bool isPlayerInZone = (playersInRadius.Count() > 0);

        if (m_CaptureProgress >= 100.0 || (!isPlayerInZone && m_CaptureProgress <= 0.0))
        {
            return;
        }

        if (isPlayerInZone)
        {
            m_CaptureProgress += m_CaptureProgressSpeed * CAPTURE_PROGRESS_CHECK_INTERVAL;
        }
        else
        {
            m_CaptureProgress -= m_CaptureProgressSpeed * CAPTURE_PROGRESS_CHECK_INTERVAL;
        }

        m_CaptureProgress = Math.Clamp(m_CaptureProgress, 0.0, 100.0);

        if (isPlayerInZone)
        {
            //Print("[BGLayer3] Player in zone. Progress: " + m_CaptureProgress.ToString());
        }
        else
        {
            //Print("[BGLayer3] No players in zone. Progress: " + m_CaptureProgress.ToString());
        }

        if (m_CaptureProgress == 100.0)
        {
            OnCaptureComplete();
            BGCreateNewEvent();
        }

        m_LastCheckedPlayerInZone = isPlayerInZone;
    }

	override void OnCaptureComplete()
    {
        super.OnCaptureComplete();

        if (m_LastRewardCrate)
        {
            V1Rewards.AddRewardLoot(m_LastRewardCrate);
        }

        else
        {
            //Print("[BGLayer3] Last reward crate not found");
        }
    }

	override void CheckCaptureRadius()
    {
        array<Man> playersInRadius = GetPlayersInRadius(m_EventLocation, 100);

        array<string> playersWithin20m = new array<string>();
        array<string> playersWithin50m = new array<string>();
        array<string> playersWithin100m = new array<string>();

        string currencyClass = "TraderPlus_Money_Dollar1";
        CurrencyHelper helper = new CurrencyHelper();

        for (int i = 0; i < playersInRadius.Count(); i++)
        {
            Man playerMan = playersInRadius[i];
            PlayerBase player = PlayerBase.Cast(playerMan);
            float distanceToEvent = vector.Distance(player.GetPosition(), m_EventLocation);

            if (!player)
                continue;

            int currencyAmount;

            if (distanceToEvent <= 20.0)
            {
                playersWithin20m.Insert(player.GetIdentity().GetName());
                currencyAmount = 100;
            }
            else if (distanceToEvent <= 50.0)
            {
                playersWithin50m.Insert(player.GetIdentity().GetName());
                currencyAmount = 50;
            }
            else if (distanceToEvent <= 100.0)
            {
                playersWithin100m.Insert(player.GetIdentity().GetName());
                currencyAmount = 20;
            }
            else
            {
                continue;
            }

            helper.AddCurrencyStackToPlayer(player, currencyClass, currencyAmount);
            
            if (rewardManager)
            {
                rewardManager.UpdatePlayerStat(player, "cashEarned", currencyAmount);
            }
            else
            {
                //Print("[BGLayer3] rewardManager is not initialized");
            }
        }
    }

    BattlegroundsLocation GetNextLocation()
    {
        if (m_EventLocations.Count() == 0) return null;

        // no previous event, start at Bridge
        if (!m_PreviousEventPositionSet)
        {
            BattlegroundsLocation bridgeLocation = GetLocationByName("Bridge");
            m_CurrentLocationString = bridgeLocation.GetName();  // Set the current location string
            return bridgeLocation;
        }
        
        int currentIndex = -1;

        // index the current location
        for (int i = 0; i < m_EventLocations.Count(); i++)
        {
            if (m_EventLocations[i].GetName() == m_CurrentLocationName)
            {
                currentIndex = i;
                break;
            }
        }

        if (currentIndex == -1) return null;

        //  reverse direction
        if (currentIndex == 0 || currentIndex == m_EventLocations.Count() - 1)
        {
            m_Direction = -m_Direction;
        }

        int nextIndex = currentIndex + m_Direction;

        // if moving from the Bridge, choose randomly between two directions
        if (m_CurrentLocationName == "Bridge")
        {
            int randomChoice = Math.RandomInt(0, 2);
            if (randomChoice == 0)
            {
                nextIndex = currentIndex + 1;
                m_Direction = 1;
            }
            else
            {
                nextIndex = currentIndex - 1;
                m_Direction = -1;
            }
        }

        BattlegroundsLocation nextLocation = m_EventLocations[nextIndex];
        m_CurrentLocationString = nextLocation.GetName();  // Set the current location string

        return nextLocation;
    }

    BattlegroundsLocation GetLocationByName(string name)
    {
        for (int i = 0; i < m_EventLocations.Count(); i++)
        {
            if (m_EventLocations[i].GetName() == name)
                return m_EventLocations[i];
        }
        return null;
    }

    override float GetCaptureRadius()
    {
        return 100.0;
    }

    override float GetCaptureProgress()
    {
        return m_CaptureProgress;
    }

    string GetPlayersListString(array<string> players)
    {
        string playersList = "";
        for (int i = 0; i < players.Count(); i++)
        {
            if (i != 0)
            {
                playersList += ", ";
            }

            playersList += players[i];
        }

        return playersList;
    }

	void InitLocations()
    {
        m_EventLocations.Insert(new BattlegroundsLocation("2883.878174 6.281060 1172.410645", "Graves [Prison Island]"));
        m_EventLocations.Insert(new BattlegroundsLocation("2777.958740 25.978380 1187.804565", "Yard [Prison Island]"));
        m_EventLocations.Insert(new BattlegroundsLocation("2777.071289 25.717098 1263.493286", "Prison [Prison Island]"));
        m_EventLocations.Insert(new BattlegroundsLocation("2685.758057 23.408087 1311.616699", "Bridge [Prison Island]"));
        m_EventLocations.Insert(new BattlegroundsLocation("2582.154541 21.744658 1289.441772", "Barracks [Prison Island]"));
        m_EventLocations.Insert(new BattlegroundsLocation("2581.273682 15.351946 1389.542236", "Garage [Prison Island]"));
        m_EventLocations.Insert(new BattlegroundsLocation("2462.553711 3.900954 1360.677979", "Docks [Prison Island]"));
    }
}