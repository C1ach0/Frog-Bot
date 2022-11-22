#pragma once
#pragma warning(disable : 4996)

#include <dpp/dpp.h>
#include <ctime>

class UR {
public:
	std::string Nitro(dpp::user* user) {
		std::string nitro;
		if (user->has_nitro_basic()) nitro = "Basic";
		else if (user->has_nitro_classic()) nitro = "Classic";
		else if (user->has_nitro_full()) nitro = "Boost";
		else nitro = "No";
		return nitro;
	};
	std::string BadgeList(dpp::user* user) {
		std::string badge = " ";
		if (user->is_bughunter_1())
		{
			std::string emote = "<:discordbughunterlv1:1042206744824258620> "; badge.append(emote);
		};
		if (user->is_bughunter_2())
		{
			std::string emote = "<:discordbughunterlv2:1042206743314309230> "; badge.append(emote);
		};
		if (user->is_house_balance())
		{
			std::string emote = "<:discordbalance:1042206737345818624>  "; badge.append(emote);
		};
		if (user->is_house_bravery())
		{
			std::string emote = "<:discordbravery:1042206738746712185> "; badge.append(emote);
		};
		if (user->is_house_brilliance())
		{
			std::string emote = "<:discordbrillance:1042206740332167218> "; badge.append(emote);
		};
		if (user->has_hypesquad_events())
		{
			std::string emote = "<:discordhypesquad:1042206732845326366> "; badge.append(emote);
		};
		if (user->is_certified_moderator())
		{
			std::string emote = "<:discordmoderator:1042209975637905459> "; badge.append(emote);
		};
		if (user->is_discord_employee())
		{
			std::string emote = "<:discordemployee:1042206741762420806> "; badge.append(emote);
		};
		if (user->is_early_supporter())
		{
			std::string emote = "<:discordearlysupporter:1042206735890403418> "; badge.append(emote);
		};
		if (user->is_partnered_owner())
		{
			std::string emote = "<:discordpartner:1042206734103609424> "; badge.append(emote);
		};
		if (user->is_verified_bot_dev())
		{
			std::string emote = "<:discorddev:1042209977495986308> "; badge.append(emote);
		};
		if (user->has_nitro_basic() || user->has_nitro_classic() || user->has_nitro_full())
		{
			std::string emote = "<:discordnitro:1042210640200204328> "; badge.append(emote);
		};
		return badge;
	};
	std::string DateTime(time_t timestamp) {
		tm ts;
		char buf[80];
		time_t now = timestamp;
		ts = *localtime(&now);;
		strftime(buf, sizeof(buf), "%Y/%m/%d", &ts);
		std::string date = buf; // date : YYYY/mm/dd
		return date;
	};
};

inline void EmbedBuilder(dpp::embed& embed, dpp::user* user, const dpp::slashcommand_t& event, std::string description)
{
	embed = dpp::embed().set_color(dpp::colors::white)
		.set_description(description)
		.set_thumbnail(user->get_avatar_url())
		.set_footer(dpp::embed_footer().text = event.command.usr.format_username(), dpp::embed_footer().icon_url = event.command.usr.get_avatar_url());
};

void userInfo(dpp::cluster& client, const dpp::slashcommand_t& event);
