#pragma once

#include <dpp/dpp.h>
#include <clacho/clacho.h>

#define ID_SPACING "###"

struct Session
{
	time_t created_at;
	std::function<bool(const dpp::button_click_t&)> function;

	uint16_t cache_duration;
	Session() : created_at(time(nullptr)), cache_duration(10) {}

	bool isExpired() const
	{
		return difftime(time(nullptr), created_at) > cache_duration * 60;
	}
};

inline std::unordered_map<uint64_t, Session> cachedSessions;
inline std::shared_mutex                     cachedSessionsMutex;
inline uint64_t                              customIdCounter;

inline void ButtonClear()
{
	std::unique_lock l(cachedSessionsMutex);
	auto it = cachedSessions.begin();

	while (it != cachedSessions.end())
	{
		if (it->second.isExpired())
		{
			assert(!cachedSessions.empty());
			it = cachedSessions.erase(it);
		}
		else ++it;
	}
}

inline void ButtonBind(dpp::component& component, const std::function<bool(const dpp::button_click_t&)>& function, uint16_t cache_duration = 10)
{
	ButtonClear();

	std::unique_lock l(cachedSessionsMutex);

	bool customIdAlreadyExists;
	do
	{
		if (customIdCounter >= UINT_LEAST64_MAX)
		{
			customIdCounter = 0;
		}

		customIdCounter++;

		customIdAlreadyExists = cachedSessions.find(customIdCounter) != cachedSessions.end();
		if (!customIdAlreadyExists)
		{
			Session session;
			session.function = function;
			session.cache_duration = cache_duration;
			component.custom_id = std::to_string(customIdCounter);

			component.custom_id += ID_SPACING + std::to_string(static_cast<long int>(session.created_at));

			cachedSessions[customIdCounter] = session;
			customIdAlreadyExists = false;
		}
	} while (customIdAlreadyExists);
}

inline void ButtonHandle(const dpp::button_click_t& event)
{
	uint64_t customId;
	time_t   creationTimestamp;

	try
	{
		const std::string id = event.custom_id.substr(0, event.custom_id.find(ID_SPACING));
		const std::string creation = event.custom_id.substr(
			event.custom_id.find(ID_SPACING) + std::strlen(ID_SPACING),
			std::string::npos
		);
		customId = std::stoul(id);
		creationTimestamp = std::stol(creation);
	}
	catch (std::out_of_range& e)
	{
		clacho::ButtonReply(
			event, "Button not found!", dpp::m_ephemeral, NO_MSG_TYPE
		);

		return;
	}
	catch (std::invalid_argument& e)
	{
		clacho::ButtonReply(
			event, "Button not found!", dpp::m_ephemeral, NO_MSG_TYPE
		);

		return;
	}

	std::unique_lock l(cachedSessionsMutex);
	const auto existing = cachedSessions.find(customId);

	if (existing != cachedSessions.end() && existing->second.created_at == creationTimestamp && !existing->second.isExpired())
	{
		bool forget = existing->second.function(event);
		if (forget)
		{
			cachedSessions.erase(existing);
		}
	}
}