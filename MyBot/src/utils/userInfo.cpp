#include <dpp/dpp.h>
#include <iostream>
#include <ctime>

#include "../../commands/utils/userInfo.h"
//#include "../../Function.h"

void userInfo(dpp::cluster& client, const dpp::slashcommand_t& event)
{
	dpp::embed embed;
	std::string fleche = "<:icons8right64:1042108498021994546> ";
	UR ur;
	if (std::holds_alternative<dpp::snowflake>(event.get_parameter("user")) == true) {
		auto& usr_id = event.get_parameter("user");
		auto user = dpp::find_user(std::get<dpp::snowflake>(usr_id));
		if (user->is_bot()) {
			auto bot = user;
			std::string desc = "<:icons8home64:1042108482062647396> **__User Information__**\n\n" + fleche + "Account : `" + bot->format_username() + "`\n" + fleche + "Identifiant : `" + std::to_string(bot->id) + "`\n" + fleche + "Created At : `" + ur.DateTime(bot->get_creation_time()) + "`\n";
			EmbedBuilder(embed, user, event, desc);
			event.reply(dpp::message(event.command.channel_id, embed));
			return;
		}
		else
		{
			auto member = dpp::find_guild_member(event.command.guild_id, user->id); //Get member from user
			std::string descUI = "<:icons8home64:1042108482062647396> **__User Information__**\n\n" + fleche + "Account : `" + user->format_username() + "`\n" + fleche + "Identifiant : `" + std::to_string(user->id) + "`\n" + fleche + "Created At : `" + ur.DateTime(user->get_creation_time()) + "`\n" + fleche + "Nitro : `" + ur.Nitro(user) + "`\n" + fleche + "Badge : " + ur.BadgeList(user) + "\n\n";
			std::string descMI = "<:icons8info64:1042108480858898492> **__Member Information__**\n\n" + fleche + "Joined At : `" + ur.DateTime(member.joined_at) + "`\n" + fleche + "Roles Size : `" + std::to_string(member.roles.size()) + "`";
			std::string desc = descUI + descMI;
			EmbedBuilder(embed, user, event, desc);
			event.reply(dpp::message(event.command.channel_id, embed));
			return;
		}
	}
	else {
		auto& user = event.command.usr;
		auto* usr = new auto(user);
		auto member = dpp::find_guild_member(event.command.guild_id, user.id); //Get member from user
		std::string descUI = "<:icons8home64:1042108482062647396> **__User Information__**\n\n" + fleche + "Account : `" + user.format_username() + "`\n" + fleche + "Identifiant : `" + std::to_string(user.id) + "`\n" + fleche + "Created At : `" + ur.DateTime(user.get_creation_time()) + "`\n" + fleche + "Nitro : `" + ur.Nitro(usr) + "`\n" + fleche + "Badge : " + ur.BadgeList(usr) + "\n\n";
		std::string descMI = "<:icons8info64:1042108480858898492> **__Member Information__**\n\n" + fleche + "Joined At : `" + ur.DateTime(member.joined_at) + "`\n" + fleche + "Roles Size : `" + std::to_string(member.roles.size()) + "`";
		std::string desc = descUI + descMI;
		EmbedBuilder(embed, usr, event, desc);
		event.reply(dpp::message(event.command.channel_id, embed));
		return;
	}
}