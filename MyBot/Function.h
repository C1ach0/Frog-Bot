#pragma once
#pragma warning(disable : 4996)

#include <ctime>
#include <string>
#include <dpp/dpp.h>
#include <dpp/nlohmann/json.hpp>
using json = nlohmann::json;

void EmbedBuild(dpp::embed& embed, const dpp::slashcommand_t& event, json build) {

	json emb = build;
	embed = dpp::embed()

		.set_footer(dpp::embed_footer().text = "Executed by " + event.command.usr.format_username(), dpp::embed_footer().icon_url = event.command.usr.get_avatar_url())
		;
}