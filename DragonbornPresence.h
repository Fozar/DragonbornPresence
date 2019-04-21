#pragma once
#include "skse/PapyrusNativeFunctions.h"
#include "skse/GameObjects.h"
#include "skse/PapyrusEvents.h"
#include <discord_rpc.h>
#include "tinyfsm/include/tinyfsm.hpp"


namespace dragonborn_presence_namespace {

#pragma region Discord Callbacks
	void HandleDiscordReady(const DiscordUser * connected_user);

	void HandleDiscordError(const int error_code, const char * message);

	void HandleDiscordDisconnected(const int error_code, const char * message);
#pragma endregion

#pragma region Discord Functions
	void InitDiscord();
	void UpdatePresence(const char* current_state, const char * current_details);
#pragma endregion

#pragma region Event Structures
	struct TESLoadGameEvent
	{
		// empty
	};
#pragma endregion

#pragma region EventSink Templates
	template <>
	class BSTEventSink<TESLoadGameEvent>
	{
	public:
		virtual ~BSTEventSink() = default; // todo?
		virtual EventResult ReceiveEvent(TESLoadGameEvent * evn,
		                                 EventDispatcher<TESLoadGameEvent> *
		                                 dispatcher) = 0;
	};
#pragma endregion

#pragma region Handler classes
	class LoadGameEventHandler : public BSTEventSink<TESLoadGameEvent>
	{
	public:
		EventResult ReceiveEvent(TESLoadGameEvent * evn,
		                         EventDispatcher<TESLoadGameEvent> * dispatcher) override;
	};

	class DiscordMenuEventHandler : public BSTEventSink<MenuOpenCloseEvent>
	{
	public:
		EventResult ReceiveEvent(MenuOpenCloseEvent * evn,
		                         EventDispatcher<MenuOpenCloseEvent> * dispatcher);
	};
#pragma endregion

#pragma region Event Handlers
	extern LoadGameEventHandler g_loadGameEventHandler;
	extern DiscordMenuEventHandler g_discordMenuEventHandler;

	void RegisterGameEventHandlers();
#pragma endregion

#pragma region Event Dispatchers
	extern EventDispatcher<TESLoadGameEvent> * g_loadGameEventDispatcher;
#pragma endregion

#pragma region Papyrus functions
	void UpdatePresenceData(StaticFunctionTag * base, BSFixedString new_position, BSFixedString new_player_info);

	bool RegisterFuncs(VMClassRegistry * registry);
#pragma endregion
}
