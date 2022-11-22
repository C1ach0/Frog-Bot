
#pragma once

#include <map>
#include <iostream>
#include <spdlog/spdlog.h>
#include "handler.h"

//#include "../commands/economy/.h"

#include "../commands/utils/ping.h"
#include "../commands/utils/userInfo.h"
//#include "../commands/utils/help.h"

void SlashCommandCreate(dpp::cluster& client);

inline std::map<std::string, commandDef> commands
{
	{
		"ping", { "Check bot latecy", ping }
	},
	{
		"userinfo",
			{
				"Show mentioned user info v2", userInfo,
				{
					dpp::command_option(
						dpp::co_user,
						"user",
						"User you would like to know",
						false
					)
				}
			}
	}
};


inline void SlashCommandCreate(dpp::cluster& client)
{
	if (dpp::run_once<struct register_commands>())
	{
		std::vector<dpp::slashcommand> slashCmds;
		spdlog::info("--------------------------------------------------------------");
		for (auto& def : commands)
		{
			dpp::slashcommand cmd;

			cmd.set_name(def.first)
				.set_description(def.second.description)
				.set_application_id(client.me.id);

			cmd.options = def.second.param;
			slashCmds.push_back(cmd);
			spdlog::info(spdlog::fmt_lib::format(std::locale("en_US.UTF-8"), "| Commands Load : {}", def.first));
		}
		spdlog::info("--------------------------------------------------------------");
		spdlog::info(spdlog::fmt_lib::format(std::locale("en_US.UTF-8"), "| All Commands Size : {}", slashCmds.size()));
		spdlog::info("--------------------------------------------------------------");
		std::cout << std::endl;
		client.global_bulk_command_create(slashCmds);
	}
}
