#include "ScriptMgr.h"
#include "ScriptedGossip.h"

using namespace std;

class MTG_TopKills : public CreatureScript
{
public:
	MTG_TopKills() : CreatureScript("MTG_TopKills") { }

	bool OnGossipHello(Player* player, Creature * creature)
	{
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Achievement_BG_winWSG:35:35:-14|tTop 5 Total Kills", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Sword_27:35:35:-14|tWarrior", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Spell_Holy_DivineIntervention:35:35:-14|tPaladin", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Weapon_Bow_07:35:35:-14|tHunter", GOSSIP_SENDER_MAIN, 4);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_ThrowingKnife_04:35:35:-14|tRogue", GOSSIP_SENDER_MAIN, 5);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Staff_30:35:35:-14|tPriest", GOSSIP_SENDER_MAIN, 6);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Spell_Deathknight_ClassIcon:35:35:-14|tDeath Knight", GOSSIP_SENDER_MAIN, 7);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Spell_Nature_BloodLust:35:35:-14|tShaman", GOSSIP_SENDER_MAIN, 8);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Staff_13:35:35:-14|tMage", GOSSIP_SENDER_MAIN, 9);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Spell_Nature_Drowsy:35:35:-14|tWarlock", GOSSIP_SENDER_MAIN, 10);
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Misc_MonsterClaw_04:35:35:-14|tDruid", GOSSIP_SENDER_MAIN, 11);
		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (action)
		{

			case 1: // TOP 5 TOTAL
			{
				QueryResult result = CharacterDatabase.Query("SELECT name,totalKills FROM characters ORDER BY totalKills DESC LIMIT 5");
				if (!result)
					return false;

				Field * fields = NULL;
				ChatHandler(player->GetSession()).SendSysMessage("|TInterface\\icons\\Achievement_BG_winWSG:20:20|t |cffFF0000Top 5 Total Kills|r");
				do
				{
					fields = result->Fetch();
					string arena_name = fields[0].GetString();
					uint32 rating = fields[1].GetUInt32();
					char msg[250];
					snprintf(msg, 250, "Nome: |cffFF0000%s|r Kills: |cffFF0000%u|r ", arena_name.c_str(), rating);
					ChatHandler(player->GetSession()).SendSysMessage(msg);
					player->CLOSE_GOSSIP_MENU();
				} while (result->NextRow());
			}
			break;

			case 2: // TOP 5 WARRIOR
			{
				QueryResult result = CharacterDatabase.Query("SELECT name,totalKills FROM characters WHERE class='1' ORDER BY totalKills DESC LIMIT 5");
				if (!result)
					return false;

				Field * fields = NULL;
				ChatHandler(player->GetSession()).SendSysMessage("|TInterface\\icons\\INV_Sword_27:20:20|t |cffFF0000Top 5 Warrior|r");
				do
				{
					fields = result->Fetch();
					string arena_name = fields[0].GetString();
					uint32 rating = fields[1].GetUInt32();
					char msg[250];
					snprintf(msg, 250, "Nome: |cffFF0000%s|r Kills: |cffFF0000%u|r ", arena_name.c_str(), rating);
					ChatHandler(player->GetSession()).SendSysMessage(msg);
					player->CLOSE_GOSSIP_MENU();
				} while (result->NextRow());
			}
			break;

			case 3: // TOP 5 PALADIN
			{
				QueryResult result = CharacterDatabase.Query("SELECT name,totalKills FROM characters WHERE class='2' ORDER BY totalKills DESC LIMIT 5");
				if (!result)
					return false;

				Field * fields = NULL;
				ChatHandler(player->GetSession()).SendSysMessage("|TInterface\\icons\\Spell_Holy_DivineIntervention:20:20|t |cffFF0000Top 5 Paladin|r");
				do
				{
					fields = result->Fetch();
					string arena_name = fields[0].GetString();
					uint32 rating = fields[1].GetUInt32();
					char msg[250];
					snprintf(msg, 250, "Nome: |cffFF0000%s|r Kills: |cffFF0000%u|r ", arena_name.c_str(), rating);
					ChatHandler(player->GetSession()).SendSysMessage(msg);
					player->CLOSE_GOSSIP_MENU();
				} while (result->NextRow());
			}
			break;

			case 4: // TOP 5 HUNTER
			{
				QueryResult result = CharacterDatabase.Query("SELECT name,totalKills FROM characters WHERE class='3' ORDER BY totalKills DESC LIMIT 5");
				if (!result)
					return false;

				Field * fields = NULL;
				ChatHandler(player->GetSession()).SendSysMessage("|TInterface\\icons\\INV_Weapon_Bow_07:20:20|t |cffFF0000Top 5 Hunter|r");
				do
				{
					fields = result->Fetch();
					string arena_name = fields[0].GetString();
					uint32 rating = fields[1].GetUInt32();
					char msg[250];
					snprintf(msg, 250, "Nome: |cffFF0000%s|r Kills: |cffFF0000%u|r ", arena_name.c_str(), rating);
					ChatHandler(player->GetSession()).SendSysMessage(msg);
					player->CLOSE_GOSSIP_MENU();
				} while (result->NextRow());
			}
			break;

			case 5: // TOP 5 ROGUE
			{
				QueryResult result = CharacterDatabase.Query("SELECT name,totalKills FROM characters WHERE class='4' ORDER BY totalKills DESC LIMIT 5");
				if (!result)
					return false;

				Field * fields = NULL;
				ChatHandler(player->GetSession()).SendSysMessage("|TInterface\\icons\\INV_ThrowingKnife_04:20:20|t |cffFF0000Top 5 Rogue|r");
				do
				{
					fields = result->Fetch();
					string arena_name = fields[0].GetString();
					uint32 rating = fields[1].GetUInt32();
					char msg[250];
					snprintf(msg, 250, "Nome: |cffFF0000%s|r Kills: |cffFF0000%u|r ", arena_name.c_str(), rating);
					ChatHandler(player->GetSession()).SendSysMessage(msg);
					player->CLOSE_GOSSIP_MENU();
				} while (result->NextRow());
			}
			break;

			case 6: // TOP 5 PRIEST
			{
				QueryResult result = CharacterDatabase.Query("SELECT name,totalKills FROM characters WHERE class='5' ORDER BY totalKills DESC LIMIT 5");
				if (!result)
					return false;

				Field * fields = NULL;
				ChatHandler(player->GetSession()).SendSysMessage("|TInterface\\icons\\INV_Staff_30:20:20|t |cffFF0000Top 5 Priest|r");
				do
				{
					fields = result->Fetch();
					string arena_name = fields[0].GetString();
					uint32 rating = fields[1].GetUInt32();
					char msg[250];
					snprintf(msg, 250, "Nome: |cffFF0000%s|r Kills: |cffFF0000%u|r ", arena_name.c_str(), rating);
					ChatHandler(player->GetSession()).SendSysMessage(msg);
					player->CLOSE_GOSSIP_MENU();
				} while (result->NextRow());
			}
			break;

			case 7: // TOP 5 DEATH KNIGHT
			{
				QueryResult result = CharacterDatabase.Query("SELECT name,totalKills FROM characters WHERE class='6' ORDER BY totalKills DESC LIMIT 5");
				if (!result)
					return false;

				Field * fields = NULL;
				ChatHandler(player->GetSession()).SendSysMessage("|TInterface\\icons\\Spell_Deathknight_ClassIcon:20:20|t |cffFF0000Top 5 Death Knight|r");
				do
				{
					fields = result->Fetch();
					string arena_name = fields[0].GetString();
					uint32 rating = fields[1].GetUInt32();
					char msg[250];
					snprintf(msg, 250, "Nome: |cffFF0000%s|r Kills: |cffFF0000%u|r ", arena_name.c_str(), rating);
					ChatHandler(player->GetSession()).SendSysMessage(msg);
					player->CLOSE_GOSSIP_MENU();
				} while (result->NextRow());
			}
			break;

			case 8: // TOP 5 SHAMAN
			{
				QueryResult result = CharacterDatabase.Query("SELECT name,totalKills FROM characters WHERE class='7' ORDER BY totalKills DESC LIMIT 5");
				if (!result)
					return false;

				Field * fields = NULL;
				ChatHandler(player->GetSession()).SendSysMessage("|TInterface\\icons\\Spell_Nature_BloodLust:20:20|t |cffFF0000Top 5 Shaman|r");
				do
				{
					fields = result->Fetch();
					string arena_name = fields[0].GetString();
					uint32 rating = fields[1].GetUInt32();
					char msg[250];
					snprintf(msg, 250, "Nome: |cffFF0000%s|r Kills: |cffFF0000%u|r ", arena_name.c_str(), rating);
					ChatHandler(player->GetSession()).SendSysMessage(msg);
					player->CLOSE_GOSSIP_MENU();
				} while (result->NextRow());
			}
			break;

			case 9: // TOP 5 MAGE
			{
				QueryResult result = CharacterDatabase.Query("SELECT name,totalKills FROM characters WHERE class='8' ORDER BY totalKills DESC LIMIT 5");
				if (!result)
					return false;

				Field * fields = NULL;
				ChatHandler(player->GetSession()).SendSysMessage("|TInterface\\icons\\INV_Staff_13:20:20|t |cffFF0000Top 5 Mage");
				do
				{
					fields = result->Fetch();
					string arena_name = fields[0].GetString();
					uint32 rating = fields[1].GetUInt32();
					char msg[250];
					snprintf(msg, 250, "Nome: |cffFF0000%s|r Kills: |cffFF0000%u|r ", arena_name.c_str(), rating);
					ChatHandler(player->GetSession()).SendSysMessage(msg);
					player->CLOSE_GOSSIP_MENU();
				} while (result->NextRow());
			}
			break;

			case 10: // TOP 5 WARLOCK
			{
				QueryResult result = CharacterDatabase.Query("SELECT name,totalKills FROM characters WHERE class='9' ORDER BY totalKills DESC LIMIT 5");
				if (!result)
					return false;

				Field * fields = NULL;
				ChatHandler(player->GetSession()).SendSysMessage("|TInterface\\icons\\Spell_Nature_Drowsy:20:20|t |cffFF0000Top 5 Warlock|r");
				do
				{
					fields = result->Fetch();
					string arena_name = fields[0].GetString();
					uint32 rating = fields[1].GetUInt32();
					char msg[250];
					snprintf(msg, 250, "Nome: |cffFF0000%s|r Kills: |cffFF0000%u|r ", arena_name.c_str(), rating);
					ChatHandler(player->GetSession()).SendSysMessage(msg);
					player->CLOSE_GOSSIP_MENU();
				} while (result->NextRow());
			}
			break;

			case 11: // TOP 5 DRUID
			{
				QueryResult result = CharacterDatabase.Query("SELECT name,totalKills FROM characters WHERE class='11' ORDER BY totalKills DESC LIMIT 5");
				if (!result)
					return false;

				Field * fields = NULL;
				ChatHandler(player->GetSession()).SendSysMessage("|TInterface\\icons\\INV_Misc_MonsterClaw_04:20:20|t |cffFF0000Top 5 Druid|r");
				do
				{
					fields = result->Fetch();
					string arena_name = fields[0].GetString();
					uint32 rating = fields[1].GetUInt32();
					char msg[250];
					snprintf(msg, 250, "Nome: |cffFF0000%s|r Kills: |cffFF0000%u|r ", arena_name.c_str(), rating);
					ChatHandler(player->GetSession()).SendSysMessage(msg);
					player->CLOSE_GOSSIP_MENU();
				} while (result->NextRow());
			}
			break;
		}

		return true;
	}
};

void AddSC_MTG_TopKills()
{
	new MTG_TopKills;
}