class GPSWidget extends UIScriptedMenu
{
    private Widget m_Root;
    private Widget m_GPSPanel;
    private TextWidget m_GPSHeader;
    private TextWidget m_GPSTextWidget;

    /*private Widget m_CompassRootWidget;
	private Widget m_CompassFrameWidget;
	private ImageWidget m_CompassImageWidget;
    private ImageWidget m_ObjectiveIconWidget;*/

    protected ref Widget m_BGRoot;
    protected ref Widget m_MainPanel;
    protected ref Widget m_ZonePanel;
    protected ref Widget m_BGPanel;
    protected TextWidget m_Location;
    protected TextWidget m_PlayerCount;
    protected ProgressBarWidget m_ProgressBar;

    private bool m_GPSIsVisible;

    void GPSWidget(bool visible)
    {
        m_Root = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/BattlegroundsGPS.layout");
        m_GPSPanel = m_Root.FindAnyWidget("GPSPanel");
        m_GPSHeader = TextWidget.Cast(m_GPSPanel.FindAnyWidget("GPSHeader"));
        m_GPSTextWidget = TextWidget.Cast(m_GPSPanel.FindAnyWidget("GPSText"));

        /*m_CompassRootWidget = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/BattlegroundsCompass.layout");
		m_CompassFrameWidget = m_CompassRootWidget.FindAnyWidget("FrameCompass");
		m_CompassImageWidget = ImageWidget.Cast(m_CompassRootWidget.FindAnyWidget("ImageCompass"));
        m_ObjectiveIconWidget = m_CompassRootWidget.FindAnyWidget("ObjectiveIcon");*/

        m_BGRoot = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/BattlegroundsWidget.layout");
        m_ZonePanel = m_BGRoot.FindAnyWidget("ZonePanel");
        m_Location = TextWidget.Cast(m_BGRoot.FindAnyWidget("Location"));
        m_PlayerCount = TextWidget.Cast(m_BGRoot.FindAnyWidget("PlayerCount"));
        m_ProgressBar = ProgressBarWidget.Cast(m_BGRoot.FindAnyWidget("ProgressBar"));

        SetLocation();
        SetPlayerCount();
        SetProgress();

		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.GPSUpdate, 16, true);

        m_GPSIsVisible = visible;
    }

    void~GPSWidget()
    {
        m_BGRoot.Unlink();

        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.GPSUpdate);
		/*if (m_CompassRootWidget != null)
		{
			m_CompassRootWidget.Show(false);
		}*/
    }

    void SetLocation(string location = "LOADING")
    {
        if (m_Location)
        {
            m_Location.SetText(location);
        }
    }

    void SetPlayerCount(int count = 0)
    {
        if (m_PlayerCount)
        {
            if (count == 0)
                m_PlayerCount.SetText("Active Event:");
            else if (count == 1)
                m_PlayerCount.SetText(count.ToString() + " Player at Event:");
            else
                m_PlayerCount.SetText(count.ToString() + " Players at Event:");
        }
    }

    void SetProgress(float progress = 0.0)
    {
        if (m_ProgressBar)
        {
            int roundedProgress = Math.Round(progress);
            m_ProgressBar.SetCurrent(roundedProgress);
        }
    }

    void GPSUpdate()
    {
        if (m_GPSIsVisible && m_GPSTextWidget && GetGame().GetPlayer())
        {
            string sector = GetSector();
            m_GPSTextWidget.SetText(sector);
            m_GPSHeader.SetText("You are in:");
        }
        /*if (m_GPSIsVisible && m_CompassRootWidget != null && GetGame().GetPlayer())
		{
			float angle = CompassGetAngle();

			m_CompassFrameWidget.Show(true);
			CompassSetCompassPos(angle);
			m_CompassRootWidget.Update();
			m_CompassRootWidget.Show(true);
		}
		else if (m_CompassRootWidget != null)
		{
			m_CompassRootWidget.Show(false);
		}*/
    }

    string GetSector()
    {
        DayZPlayer player = DayZPlayer.Cast(GetGame().GetPlayer());
        vector pos = player.GetPosition();
        float x = pos[0];
        float z = pos[2];

        int sectorX = Math.Floor(x / 1000) + 1;
        int mapMaxZ = 15350;
        z = mapMaxZ - z;
        int sectorZ = Math.Floor(z / 1000) + 1;

        float subX = x - Math.Floor(x / 1000) * 1000;
        float subZ = z - Math.Floor(z / 1000) * 1000;

        int subSectorX = Math.Floor(subX / 333.34) + 1;
        int subSectorZ = Math.Floor(subZ / 333.34) + 1;

        int keypadNum = 0;
        if (subSectorZ == 3) { 
            keypadNum = subSectorX;
        } else if (subSectorZ == 2) {
            keypadNum = subSectorX + 3;
        } else if (subSectorZ == 1) { 
            keypadNum = subSectorX + 6;
        }

        array<string> alphabets = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P" };
        string alphabeticX = alphabets[sectorX - 1];
        string numericZ = sectorZ.ToString();

        return "Sector [" + alphabeticX + numericZ + "-" + keypadNum.ToString() + "]";
    }

    /*void SetCompassAlpha(float alpha)
	{
		if (m_CompassRootWidget != null)
		{
			m_CompassRootWidget.SetAlpha(alpha);
		}
	}*/

    /*string CompassGetHeading(float angle)
	{
		float rounded = Math.Round(5 *Math.Round(angle / 5.0));
		return rounded.ToString();
	}*/

	/*void CompassSetCompassPos(float angle)
	{
		float width, height, x, y;
		m_CompassImageWidget.GetPos(x, y);
		m_CompassImageWidget.GetSize(width, height);

		float center_offset = width / -2.0 + 0.5;

		if (angle > 180)
		{
			angle = angle - 360;
		}

		float offset = angle *(center_offset / 180.0) + center_offset;

		m_CompassImageWidget.SetPos(offset, y);
	}*/

	/*float CompassGetAngle()
	{
		vector direction = GetGame().GetCurrentCameraDirection();
		float angle = direction.VectorToAngles()[0];
		return angle;
	}*/

	void GPSSetHeadingVisible(bool visible)
	{
		m_GPSIsVisible = visible;
	}

    void GPSToggleHeading()
    {
        m_GPSIsVisible = !m_GPSIsVisible;
        
        if (m_BGRoot)
        {
            m_BGRoot.Show(m_GPSIsVisible);
        }
    }

    void SetGPSVisible(bool visible)
    {
        m_GPSIsVisible = visible;
        
        if (m_GPSPanel)
        {
            m_GPSPanel.Show(m_GPSIsVisible);
        }
        
        if (m_BGRoot)
        {
            m_BGRoot.Show(m_GPSIsVisible);
        }
    }

    void ToggleGPS()
    {
        m_GPSIsVisible = !m_GPSIsVisible;
        
        if (m_GPSPanel)
        {
            m_GPSPanel.Show(m_GPSIsVisible);
        }
        
        if (m_BGRoot)
        {
            m_BGRoot.Show(m_GPSIsVisible);
        }
    }

    bool IsGPSVisible()
    {
        return m_GPSIsVisible;
    }
}