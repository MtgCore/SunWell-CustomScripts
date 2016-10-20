#include "ScriptMgr.h"
#include "ScriptedGossip.h"

class MTG_Mount_Vendor : public CreatureScript
{
public: MTG_Mount_Vendor() : CreatureScript("MTG_Mount_Vendor") {}

		bool OnGossipHello(Player* player, Creature* creature)
	{
		if (player->IsInCombat())
		{
			player->CLOSE_GOSSIP_MENU();
			player->GetSession()->SendNotification("Você está em combate!", LANG_UNIVERSAL, player);
			return false;
		}
	
		player->ADD_GOSSIP_ITEM(0, "|TInterface\\icons\\INV_Misc_SymbolofKings_01:40:40:-14|t Trainer Riding", GOSSIP_SENDER_MAIN, 1);			// Trainer Riding
		player->ADD_GOSSIP_ITEM(0, "|TInterface\\icons\\Ability_Parry:40:40:-14|t MaxSkills", GOSSIP_SENDER_MAIN, 2);							// MaxSkill
		player->ADD_GOSSIP_ITEM(0, "|TInterface\\icons\\Ability_Mount_RidingHorse:40:40:-14|t Mounts", GOSSIP_SENDER_MAIN, 3);					// Mounts
		player->ADD_GOSSIP_ITEM(0, "|TInterface\\icons\\Ability_Mount_RedFrostwyrm_01:40:40:-14|t Fly Mounts", GOSSIP_SENDER_MAIN, 4);			// Fly Mounts
		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
		}

		bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
		{
		player->PlayerTalkClass->ClearMenus();

		switch (action)
			{
			case 1:
				player->CLOSE_GOSSIP_MENU();
				player->learnSpell(33388);	// Apprentice Riding
				player->learnSpell(33391);	// Journeyman Riding
				player->learnSpell(34090);	// Expert Riding
				player->learnSpell(34091);	// Artisan Riding
				player->learnSpell(54197);	// Cold Weather Flying
				player->CastSpell(player, 31726);
				player->GetSession()->SendNotification("|cffFFFF00NPC MOUNT \n |cffFFFFFFRiding Treinada com Sucesso!");
				break;

			case 2:
				player->CLOSE_GOSSIP_MENU();
				player->UpdateSkillsToMaxSkillsForLevel();
				player->CastSpell(player, 36400);
				player->GetSession()->SendNotification("|cffFFFF00NPC MAXSKILL \n |cffFFFFFFWeapons Skill Atualizada com Sucesso!");
				break;

			case 3:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200040);
				return true;

			case 4:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200041);
				return true;
		}
		return true;
	}
};

void AddSC_MTG_Mount_Vendor()
{
	new MTG_Mount_Vendor;
}