/*
______               _      ______ _                       _  ______       _
|  ___|             ( )     |  _  (_)                     | | | ___ \     | |
| |_ _ __ ___   __ _|/ ___  | | | |_ ___  ___ ___  _ __ __| | | |_/ / ___ | |_
|  _| '__/ _ \ / _` | / __| | | | | / __|/ __/ _ \| '__/ _` | | ___ \/ _ \| __|
| | | | | (_) | (_| | \__ \ | |/ /| \__ \ (_| (_) | | | (_| | | |_/ / (_) | |_
\_| |_|  \___/ \__, | |___/ |___/ |_|___/\___\___/|_|  \__,_| \____/ \___/ \__|
				__/ |
			   |___/
 _             _____  __             _     _____
| |           /  __ \/  |           | |   |  _  |
| |__  _   _  | /  \/`| |  __ _  ___| |__ | |/' |
| '_ \| | | | | |     | | / _` |/ __| '_ \|  /| |
| |_) | |_| | | \__/\_| || (_| | (__| | | \ |_/ /
|_.__/ \__, |  \____/\___/\__,_|\___|_| |_|\___/
		__/ |
	   |___/

*/

#include <fstream>
#include <map>

#include <spdlog/spdlog.h>
#include <dpp/nlohmann/json.hpp>
#include <dpp/dpp.h>
#include <Windows.h>

#include "../handler/builder.h"
#include "../handler/btnHandler.h"

using json = nlohmann::json;

int main()
{
	json reader;
	{
		std::ifstream reading("config.json");

		if (!reading)
		{
			std::cout << "No configuration file found! Please add it with the name \"config.json\"!";
			std::cin.get();
			exit(0);
		}
		reading >> reader;
	};
	const std::string token = reader["token"];

	// Client variable builder
	dpp::cluster client(token, dpp::i_all_intents);

	client.on_ready([&client](const dpp::ready_t& event)
		{
			// Set presence for the bot
			client.set_presence(
				dpp::presence(dpp::ps_dnd, dpp::at_game, "Frog's Bank")
			);

			// Slash command registration
			SlashCommandCreate(client);

			// Confirm logger
			fmt::print("[{} - STARTED]: {} is online!\n", dpp::utility::current_date_time(), client.me.format_username());
			fmt::print("[{} - REGISTERED]: Successfully registered slash commands!\n", dpp::utility::current_date_time());
		});

	client.on_slashcommand([&client](const dpp::slashcommand_t& event)
		{
			dpp::command_interaction commandData = event.command.get_command_interaction();
			auto commandFilter = commands.find(commandData.name);

			// Check commands
			if (commandFilter != commands.end())
				commandFilter->second.function(client, event);
		});

	client.on_button_click([](const dpp::button_click_t& event)
		{
			// Handling the button event
			ButtonHandle(event);
		});

	// Console log prettier
	SetConsoleTitle(TEXT("[BETA] v0.0.1 - Frog's Bank Discord Bot - C1ach0"));


	// Starting the bot
	client.start(false);
	return 0;
}
