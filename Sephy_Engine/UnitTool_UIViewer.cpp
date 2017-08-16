#include "stdafx.h"
#include "UnitTool_UIViewer.h"
#include "UnitTool_MouseOverShip.h"

CUnitTool_UIViewer* pThis = nullptr;
CUnitTool_UIViewer::CUnitTool_UIViewer()
{
	::pThis = this;
	m_pMouseOverShip = nullptr;
	//======================================================
	m_pGame					= nullptr;
	m_bSetupShip			= false;
	m_bPlayerShip			= false;
	m_strPlayerStatusKey	= unitToolUIViewerNS::SETUP_PLAYER_STATUS_OFF_FILENAME;
	backColor				= unitToolUIViewerNS::BACK_COLOR;
	//======================================================
	m_bFocusItemBox = false;
	m_nFocusItemNumber = -1;
	//======================================================
	m_ID				= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_TextureKey		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_TopCount			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_BodyCount			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_BottomCount		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_Name				= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_ShipType			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_UnitType			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_MaxDP				= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_CurrentDP			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_RepairSpeed		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_RotateSpeed		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_AccelerateSpeed	= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_MaxSpeed			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_CurrentSpeed		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_RaderRange		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_TurretCapacity	= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_TurretName		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_AircraftCapacity	= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_Performance		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_Sailor			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_AntiAirCapacity	= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_AntiAirRange		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_AntiAirDamage		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_Phase				= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_Mass				= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_EvasionRadius		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	m_Skill				= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
}


CUnitTool_UIViewer::~CUnitTool_UIViewer()
{
	for (auto iter : m_vUpDownPairButton)
	{
		SAFE_DELETE(iter);
	}
	m_vUpDownPairButton.clear();
	for (auto iter : m_vEditControl)
	{
		SAFE_DELETE(iter);
	}
	m_vEditControl.clear();
}

bool CUnitTool_UIViewer::initialize(Graphics * g, Input * i)
{
	bool success = false;
	try
	{
		success = SystemUIDialog::initializeDialog(g, i,
			g_fScreenWidth - unitToolUIViewerNS::VIEWER_RELATE_X - unitToolUIViewerNS::VIEWER_RELATE_WIDTH,
			unitToolUIViewerNS::VIEWER_RELATE_Y,
			unitToolUIViewerNS::VIEWER_RELATE_WIDTH,
			unitToolUIViewerNS::VIEWER_RELATE_HEIGHT, 0);

		m_dxFont.initialize(g, unitToolUIViewerNS::FONT_HEIGHT, false, false, unitToolUIViewerNS::FONT);
		//===============================================================================================
		float startX = g_fScreenWidth - unitToolUIViewerNS::VIEWER_RELATE_X - unitToolUIViewerNS::VIEWER_RELATE_WIDTH + unitToolUIViewerNS::ITEM_BOX_START_MARGIN;
		float startY = unitToolUIViewerNS::VIEWER_RELATE_Y;
		float width = unitToolUIViewerNS::ITEM_GUIDE_BOX_WIDTH;
		float height = unitToolUIViewerNS::ITEM_GUIDE_BOX_HEIGHT;		
		for (int i = 0; i < unitToolUIViewerNS::ITEM_SIZE; i++)
		{
			float y = startY + unitToolUIViewerNS::ITEM_BOX_START_MARGIN;
			if (i > 0)
				y = m_vItemGuideRect[i - 1].bottom;
			RECT rcGuide = RectMake(startX, y, width, height);
			m_vItemGuideRect.emplace_back(rcGuide);

			RECT rcItem = RectMake(rcGuide.right + 10, y, unitToolUIViewerNS::ITEM_BOX_WIDTH, unitToolUIViewerNS::ITEM_BOX_HEIGHT);
			m_vItemRect.emplace_back(rcItem);
		}
		//===============================================================================================
		int buttonCount = 0;
		for (auto iter : m_vItemRect)
		{
			if (buttonCount < 8 || buttonCount == 16 || buttonCount == 17 || buttonCount == 24 || buttonCount == 27)
			{
				buttonCount++;
				continue;
			}

			tagUpDownPair* tempButton = new tagUpDownPair;
			tempButton->buttonUp.initialize(m_pGraphics, m_pInput,
				iter.right + unitToolUIViewerNS::UP_BUTTON_MARGIN_BETWEEN_ITEM,
				iter.top,
				unitToolUIViewerNS::UP_BUTTON_FILENAME, true);

			tempButton->buttonDown.initialize(m_pGraphics, m_pInput,
				iter.right + unitToolUIViewerNS::UP_BUTTON_MARGIN_BETWEEN_ITEM + unitToolUIViewerNS::DOWN_BUTTON_MARGIN_BETWEEN_ITEM,
				iter.top,
				unitToolUIViewerNS::DOWN_BUTTON_FILENAME, true);

			m_vUpDownPairButton.emplace_back(tempButton);
			buttonCount++;
		}		
		this->setupRegistFunc();
		//===============================================================================================
		int lastItem = m_vItemRect.size() - 1;
		m_SetupButton.initialize(m_pGraphics, m_pInput,
			this->getDialogX() + unitToolUIViewerNS::SETUP_BUTTON_RELATE_X,
			m_vItemRect[lastItem].bottom + unitToolUIViewerNS::SETUP_BUTTON_RELATE_Y,
			unitToolUIViewerNS::SETUP_BUTTON_FILENAME, true);
		m_SetupButton.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcSetupButton));
		m_RemoveButton.initialize(m_pGraphics, m_pInput,
			this->getDialogX() + unitToolUIViewerNS::REMOVE_BUTTON_RELATE_X,
			m_vItemRect[lastItem].bottom + unitToolUIViewerNS::REMOVE_BUTTON_RELATE_Y,
			unitToolUIViewerNS::REMOVE_BUTTON_FILENAME, true);
		m_RemoveButton.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcRemoveButton));
		//===============================================================================================
		m_SetPlayerStatus.initialize(m_pGraphics, 0, 0, 0, IMAGEMANAGER->getTexture(m_strPlayerStatusKey));
		m_SetPlayerStatus.setX(this->getDialogX() + unitToolUIViewerNS::SETUP_PLAYER_STATUS_RELATE_X);
		m_SetPlayerStatus.setY(m_vItemRect[lastItem].bottom + unitToolUIViewerNS::SETUP_PLAYER_STATUS_RELATE_Y);
		m_SetPlayerShipButton.initialize(m_pGraphics,m_pInput, 
			this->getDialogX() + unitToolUIViewerNS::SETUP_PLAYER_BUTTON_RELATE_X,
			m_vItemRect[lastItem].bottom + unitToolUIViewerNS::SETUP_PLAYER_BUTTON_RELATE_Y,
			unitToolUIViewerNS::SETUP_PLAYER_BUTTON_FILENAME, true);
		m_SetPlayerShipButton.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcPlayerButton));
		//===============================================================================================
		int editCount = 0;		
		for (auto iter : m_vItemRect)
		{
			if (editCount < 8 || editCount == 16 || editCount == 17 || editCount == 24 || editCount == 27)
			{
				SystemUIEdit* edit = new SystemUIEdit;
				edit->initEdit(m_pGraphics, m_pInput, editCount, false, "", "", false, 0,
					m_vItemRect[editCount].left, m_vItemRect[editCount].top,
					unitToolUIViewerNS::ITEM_BOX_WIDTH,
					unitToolUIViewerNS::ITEM_BOX_HEIGHT, 0);
				edit->setEditText(unitToolUIViewerNS::ITEM_NONE_ARGUMENT);
				m_vEditControl.emplace_back(edit);
			}
			else
			{
				SystemUIEdit* edit = new SystemUIEdit;
				edit->initEdit(m_pGraphics, m_pInput, editCount, false, "", "", true, 0,
					m_vItemRect[editCount].left, m_vItemRect[editCount].top,
					unitToolUIViewerNS::ITEM_BOX_WIDTH,
					unitToolUIViewerNS::ITEM_BOX_HEIGHT, 0);
				edit->setEditText(unitToolUIViewerNS::ITEM_NONE_ARGUMENT);
				m_vEditControl.emplace_back(edit);
			}
			editCount++;
		}
	}
	catch (...)
	{
		MessageBox(g_hWndEngine, unitToolUIViewerNS::ERROR_MESSAGE.c_str(), "Error", MB_OK);
	}
		
	return success;
}

void CUnitTool_UIViewer::update(float frameTime)
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::update(frameTime);	

	if (m_bSetupShip == false)
		return;
	
	m_SetupButton.update(frameTime);
	m_RemoveButton.update(frameTime);
	m_SetPlayerShipButton.update(frameTime);

	for (auto iter : m_vUpDownPairButton)
	{
		iter->buttonUp.update(frameTime);
		iter->buttonDown.update(frameTime);
	}

	if (SystemUIDialog::getMouseOver() == false)
		return;
	
	for (auto iter : m_vEditControl)
	{
		iter->update(frameTime);
	}
}

void CUnitTool_UIViewer::render()
{
	if (m_bVisible == false)
		return;

	SystemUIDialog::render();

	for (auto iter : m_vItemRect)
	{
		m_pGraphics->drawRect(iter);
	}
	
	m_pGraphics->spriteBegin();

#pragma region PRINT_INFO_TITLE
	int itemStart = 0;
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_ID,					m_vItemGuideRect[itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_TEXTURE_KEY,			m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_TOP_COUNT,			m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_BODY_COUNT,			m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_BOTTOM_COUNT,			m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_NAME,					m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_TYPE_A,				m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_TYPE_B,				m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_MAX_DP,				m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_CURRENT_DP,			m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_REPAIR_SPEED,			m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_ROTATE_SPEED,			m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_ACCELERATE_SPEED,		m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_MAX_SPEED,			m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_CURRENT_SPEED,		m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_RADER_RANGE,			m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_TURRET_CAPACITY,		m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_TURRET_NAME,			m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_AIRCRAFT_CAPACITY,	m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_PERFORMANCE,			m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_SAILOR,				m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_ANTIAIR_CAPACITY,		m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_ANTIAIR_RANGE,		m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_ANTIAIR_DAMAGE,		m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_PHASE,				m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_MASS,					m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_EVASION,				m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
	m_dxFont.print(unitToolUIViewerNS::INFO_TITLE_SKILL,				m_vItemGuideRect[++itemStart], DT_LEFT | DT_VCENTER);
#pragma endregion
	
	m_SetPlayerStatus.draw();
	m_pGraphics->spriteEnd();

	m_SetupButton.render();
	m_RemoveButton.render();
	m_SetPlayerShipButton.render();

	for (auto iter : m_vUpDownPairButton)
	{
		iter->buttonUp.render();
		iter->buttonDown.render();
	}
	for (auto iter : m_vEditControl)
	{
		iter->render();
	}
}

void CUnitTool_UIViewer::funcSetupButton()
{
	CBattle_Ship* dummyShip = new CBattle_Ship;
	dummyShip->initialize(pThis->m_pGame, pThis->m_Name);
	dummyShip->setPlayerShip(pThis->m_bPlayerShip);
	dummyShip->setShipActive(true);
	dummyShip->setDetected(true);
	dummyShip->setDebugMode(true);
	dummyShip->setUnitToolMode(true);
	
	dummyShip->setMaxHealth				(std::stof(pThis->m_vEditControl[8]->getEditText()));			// 09. MaxDP		   	
	dummyShip->setCurrentHealth			(std::stof(pThis->m_vEditControl[9]->getEditText()));			// 10. CurrentDP		
	dummyShip->setRepairSpeed			(std::stof(pThis->m_vEditControl[10]->getEditText()));			// 11. RepairSpeed		
	dummyShip->setRotateSpeed			(std::stof(pThis->m_vEditControl[11]->getEditText()));			// 12. RotateSpeed		
	dummyShip->setAccelateSpeed			(std::stof(pThis->m_vEditControl[12]->getEditText()));			// 13. AccelerateSpeed	
	dummyShip->setMaxSpeed				(std::stof(pThis->m_vEditControl[13]->getEditText()));			// 14. MaxSpeed		   			   	
	dummyShip->setCurrentSpeed			(std::stof(pThis->m_vEditControl[14]->getEditText()));			// 15. CurrentSpeed				   	
	dummyShip->setRaderRange			(std::stof(pThis->m_vEditControl[15]->getEditText()));			// 16. RaderRange				   	
	dummyShip->setAirCraftCapacity		(std::stoi(pThis->m_vEditControl[18]->getEditText()));			// 19. Aircraft Capacity 
	dummyShip->setPerformance			(std::stof(pThis->m_vEditControl[19]->getEditText()));			// 20. Performance   	
	dummyShip->setSailorCount			(std::stoi(pThis->m_vEditControl[20]->getEditText()));			// 21. Sailor	   	  	
	dummyShip->setAntiAirTurretCount	(std::stoi(pThis->m_vEditControl[21]->getEditText()));			// 22. Antiair Capacity
	dummyShip->setAntiAirRange			(std::stof(pThis->m_vEditControl[22]->getEditText()));			// 23. Antiair Range   	
	dummyShip->setAntiAirDamage			(std::stof(pThis->m_vEditControl[23]->getEditText()));			// 24. Antiair Damage
	dummyShip->setShipMass				(std::stof(pThis->m_vEditControl[25]->getEditText()));			// 26. Mass
	dummyShip->setEvasion				(std::stof(pThis->m_vEditControl[26]->getEditText()));			// 27. Evasion Radius																

	pThis->m_pMouseOverShip->setupOverlabShip(dummyShip);
}

void CUnitTool_UIViewer::funcRemoveButton()
{
	pThis->m_bSetupShip			= false;
	
	for (auto iter : pThis->m_vEditControl)
	{
		iter->setEditText(unitToolUIViewerNS::ITEM_NONE_ARGUMENT);
	}

	pThis->m_ID					= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_TextureKey			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_TopCount			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_BodyCount			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_BottomCount		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_Name				= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_ShipType			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_UnitType			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_MaxDP				= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_CurrentDP			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_RepairSpeed		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_RotateSpeed		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_AccelerateSpeed	= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_MaxSpeed			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_CurrentSpeed		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_RaderRange			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_TurretCapacity		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_TurretName			= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_AircraftCapacity	= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_Performance		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_Sailor				= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_AntiAirCapacity	= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_AntiAirRange		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_AntiAirDamage		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_Phase				= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_Mass				= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_EvasionRadius		= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
	pThis->m_Skill				= unitToolUIViewerNS::ITEM_NONE_ARGUMENT;
}

void CUnitTool_UIViewer::funcPlayerButton()
{
	auto bFlag = pThis->m_bPlayerShip;
	pThis->m_bPlayerShip = !bFlag;
	if (pThis->m_bPlayerShip)
	{
		pThis->m_strPlayerStatusKey = unitToolUIViewerNS::SETUP_PLAYER_STATUS_ON_FILENAME;
		pThis->m_SetPlayerStatus.setTextureManager(IMAGEMANAGER->getTexture(pThis->m_strPlayerStatusKey));
	}
	else
	{
		pThis->m_strPlayerStatusKey = unitToolUIViewerNS::SETUP_PLAYER_STATUS_OFF_FILENAME;
		pThis->m_SetPlayerStatus.setTextureManager(IMAGEMANAGER->getTexture(pThis->m_strPlayerStatusKey));
	}
}


void CUnitTool_UIViewer::setupRegistFunc()
{
	int buttonCount = 0;

	m_vUpDownPairButton[buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcMaxDPUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcCurrentDPUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcRepairSpeedUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcRotateSpeedUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcAccelerateSpeedUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcMaxSpeedUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcCurrentSpeedUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcRaderRangeUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcAircraftCapacityUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcPerformanceUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcSailorUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcAntiAirCraftCapacityUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcAntiAirCraftRangeUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcAntiAirCraftDamageUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcMassUP));
	m_vUpDownPairButton[++buttonCount]->buttonUp.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcEvasionRadiusUP));

	buttonCount = 0;
	m_vUpDownPairButton[buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcMaxDPDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcCurrentDPDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcRepairSpeedDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcRotateSpeedDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcAccelerateSpeedDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcMaxSpeedDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcCurrentSpeedDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcRaderRangeDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcAircraftCapacityDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcPerformanceDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcSailorDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcAntiAirCraftCapacityDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcAntiAirCraftRangeDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcAntiAirCraftDamageDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcMassDown));
	m_vUpDownPairButton[++buttonCount]->buttonDown.setRegistFunction(std::bind(&CUnitTool_UIViewer::funcEvasionRadiusDown));



}

void CUnitTool_UIViewer::funcMaxDPUP()
{
	float temp = std::stof(pThis->m_MaxDP);
	temp++;
	pThis->setMaxDP(temp);
}

void CUnitTool_UIViewer::funcMaxDPDown()
{
	float temp = std::stof(pThis->m_MaxDP);
	temp--;
	pThis->setMaxDP(temp);
}

void CUnitTool_UIViewer::funcCurrentDPUP()
{
	float temp = std::stof(pThis->m_CurrentDP);
	temp++;
	pThis->setCurrentDP(temp);
}

void CUnitTool_UIViewer::funcCurrentDPDown()
{
	float temp = std::stof(pThis->m_CurrentDP);
	temp--;
	pThis->setCurrentDP(temp);
}

void CUnitTool_UIViewer::funcRepairSpeedUP()
{
	float temp = std::stof(pThis->m_RepairSpeed);
	temp++;
	pThis->setRepairSpeed(temp);
}

void CUnitTool_UIViewer::funcRepairSpeedDown()
{
	float temp = std::stof(pThis->m_RepairSpeed);
	temp--;
	pThis->setRepairSpeed(temp);
}

void CUnitTool_UIViewer::funcRotateSpeedUP()
{
	float temp = std::stof(pThis->m_RotateSpeed);
	temp++;
	pThis->setRotateSpeed(temp);
}

void CUnitTool_UIViewer::funcRotateSpeedDown()
{
	float temp = std::stof(pThis->m_RotateSpeed);
	temp--;
	pThis->setRotateSpeed(temp);
}

void CUnitTool_UIViewer::funcAccelerateSpeedUP()
{
	float temp = std::stof(pThis->m_AccelerateSpeed);
	temp++;
	pThis->setAccelerateSpeed(temp);
}

void CUnitTool_UIViewer::funcAccelerateSpeedDown()
{
	float temp = std::stof(pThis->m_AccelerateSpeed);
	temp--;
	pThis->setAccelerateSpeed(temp);
}

void CUnitTool_UIViewer::funcMaxSpeedUP()
{
	float temp = std::stof(pThis->m_MaxSpeed);
	temp++;
	pThis->setMaxSpeed(temp);
}

void CUnitTool_UIViewer::funcMaxSpeedDown()
{
	float temp = std::stof(pThis->m_MaxSpeed);
	temp--;
	pThis->setMaxSpeed(temp);
}

void CUnitTool_UIViewer::funcCurrentSpeedUP()
{
	float temp = std::stof(pThis->m_CurrentSpeed);
	temp++;
	pThis->setCurrentSpeed(temp);
}

void CUnitTool_UIViewer::funcCurrentSpeedDown()
{
	float temp = std::stof(pThis->m_CurrentSpeed);
	temp--;
	pThis->setCurrentSpeed(temp);
}

void CUnitTool_UIViewer::funcRaderRangeUP()
{
	float temp = std::stof(pThis->m_RaderRange);
	temp++;
	pThis->setRaderRange(temp);
}

void CUnitTool_UIViewer::funcRaderRangeDown()
{
	float temp = std::stof(pThis->m_RaderRange);
	temp--;
	pThis->setRaderRange(temp);
}

void CUnitTool_UIViewer::funcAircraftCapacityUP()
{
	float temp = std::stof(pThis->m_AircraftCapacity);
	temp++;
	pThis->setAircraftCapacity(temp);
}

void CUnitTool_UIViewer::funcAircraftCapacityDown()
{
	float temp = std::stof(pThis->m_AntiAirCapacity);
	temp--;
	pThis->setAircraftCapacity(temp);
}

void CUnitTool_UIViewer::funcPerformanceUP()
{
	float temp = std::stof(pThis->m_Performance);
	temp++;
	pThis->setPerformance(temp);
}

void CUnitTool_UIViewer::funcPerformanceDown()
{
	float temp = std::stof(pThis->m_Performance);
	temp--;
	pThis->setPerformance(temp);
}

void CUnitTool_UIViewer::funcSailorUP()
{
	float temp = std::stof(pThis->m_Sailor);
	temp++;
	pThis->setSailor(temp);
}

void CUnitTool_UIViewer::funcSailorDown()
{
	float temp = std::stof(pThis->m_Sailor);
	temp--;
	pThis->setSailor(temp);
}

void CUnitTool_UIViewer::funcAntiAirCraftCapacityUP()
{
	float temp = std::stof(pThis->m_AntiAirCapacity);
	temp++;
	pThis->setAntiAirCapacity(temp);
}

void CUnitTool_UIViewer::funcAntiAirCraftCapacityDown()
{
	float temp = std::stof(pThis->m_AntiAirCapacity);
	temp--;
	pThis->setAntiAirCapacity(temp);
}

void CUnitTool_UIViewer::funcAntiAirCraftRangeUP()
{
	float temp = std::stof(pThis->m_AntiAirRange);
	temp++;
	pThis->setAntiAirRange(temp);
}

void CUnitTool_UIViewer::funcAntiAirCraftRangeDown()
{
	float temp = std::stof(pThis->m_AntiAirRange);
	temp--;
	pThis->setAntiAirRange(temp);
}

void CUnitTool_UIViewer::funcAntiAirCraftDamageUP()
{
	float temp = std::stof(pThis->m_AntiAirDamage);
	temp++;
	pThis->setAntiAirDamage(temp);
}

void CUnitTool_UIViewer::funcAntiAirCraftDamageDown()
{
	float temp = std::stof(pThis->m_AntiAirDamage);
	temp--;
	pThis->setAntiAirDamage(temp);
}

void CUnitTool_UIViewer::funcMassUP()
{
	float temp = std::stof(pThis->m_Mass);
	temp++;
	pThis->setMass(temp);
}

void CUnitTool_UIViewer::funcMassDown()
{
	float temp = std::stof(pThis->m_Mass);
	temp--;
	pThis->setMass(temp);
}

void CUnitTool_UIViewer::funcEvasionRadiusUP()
{
	float temp = std::stof(pThis->m_EvasionRadius);
	temp++;
	pThis->setEvasionRadius(temp);
}

void CUnitTool_UIViewer::funcEvasionRadiusDown()
{
	float temp = std::stof(pThis->m_EvasionRadius);
	temp--;
	pThis->setEvasionRadius(temp);
}
