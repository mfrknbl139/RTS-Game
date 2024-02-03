#include "RTSGameModeBase.h"
#include "RTS/Player/RTS_PlayerController.h"

ARTSGameModeBase::ARTSGameModeBase()
{
	// Set the player controller class
	PlayerControllerClass = ARTS_PlayerController::StaticClass();

	// Other game mode initializations...
}
