#include "ScriptPCH.h"
#include "ScriptedGossip.h"

class MTG_Npc_Tools : public CreatureScript
{
public:
        MTG_Npc_Tools() : CreatureScript("MTG_Npc_Tools") { }
 
        bool OnGossipHello(Player *player, Creature *creature)
        {
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Spell_Nature_Regenerate:40:40:-14|t Restaurar HP and MP", GOSSIP_SENDER_MAIN, 1);			// Restaurar HP and MP
		//player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Achievement_BG_winAB_underXminutes:40:40:-14|t Resetar Instances", GOSSIP_SENDER_MAIN, 2);	// Resetar Instances
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\SPELL_HOLY_BORROWEDTIME:40:40:-14|t Resetar Cooldowns", GOSSIP_SENDER_MAIN, 3);				// Resetar Cooldowns
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Achievement_BG_AB_defendflags:40:40:-14|t Resetar Combate", GOSSIP_SENDER_MAIN, 4);			// Resetar Combate
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Spell_Shadow_DeathScream:40:40:-14|t Remover Sickness", GOSSIP_SENDER_MAIN, 5);				// Remover Sickness
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Hammer_24:40:40:-14|t Reparar Items", GOSSIP_SENDER_MAIN, 6);							// Reparar Items
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Achievement_WorldEvent_Lunar:40:40:-14|t Resetar Talents", GOSSIP_SENDER_MAIN, 7);			// Resetar Talents
		player->ADD_GOSSIP_ITEM(10, "|TInterface/Icons/INV_Misc_Bag_07:40:40:-14|tBank", GOSSIP_SENDER_MAIN, 8);
		player->ADD_GOSSIP_ITEM(10, "|TInterface/Icons/INV_Letter_11:40:40:-14|tMail", GOSSIP_SENDER_MAIN, 9);
		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
        return true;
	}
	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (action)
		{
		case 1: // Restaurar HP e MP
				player->CLOSE_GOSSIP_MENU();
			if (player->IsInCombat())
			{
				player->CLOSE_GOSSIP_MENU();
				player->GetSession()->SendNotification("Você está em combate!", LANG_UNIVERSAL, player);
				return false;
				}
				else if(player->getPowerType() == POWER_MANA)
						player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));

				player->SetHealth(player->GetMaxHealth());
				player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFHP & MP Resetados com Sucesso!");
				player->CastSpell(player, 31726);
				break;

	   /* case 2: // Resetar Instances
				player->CLOSE_GOSSIP_MENU();
				for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
				{
						Player::BoundInstancesMap &binds = player->GetBoundInstances(Difficulty(i));
						for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end();)
						{
								player->UnbindInstance(itr, Difficulty(i));
						}
				}
				player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFInstances Resetados com Sucesso!");
				player->CastSpell(player, 59908);
				break;*/

		case 3: // Resetar Cooldowns
				player->CLOSE_GOSSIP_MENU();
				if (player->IsInCombat())
				{
				player->CLOSE_GOSSIP_MENU();
				player->GetSession()->SendNotification("Você está em combate!", LANG_UNIVERSAL, player);
				return false;
				}

				player->RemoveAllSpellCooldown();
				player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFCooldowns Resetados com Sucesso!");
				player->CastSpell(player, 31726);
				break;

		case 4: // Resetar Combat
				player->CLOSE_GOSSIP_MENU();
				player->CombatStop();
				player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFCombate Removido com Sucesso!");
				player->CastSpell(player, 31726);
				break;

		case 5: // Remover Sickness
				player->CLOSE_GOSSIP_MENU();
				if(player->HasAura(15007))
				player->RemoveAura(15007);
				player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFSickness Removido com Sucesso!");
				player->CastSpell(player, 31726);
				break;

		case 6: // Reparar Items
				player->CLOSE_GOSSIP_MENU();
				player->DurabilityRepairAll(false, 0, false);
				player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFEquipamentos Reparados com Sucesso!");
				player->CastSpell(player, 31726);
				break;

	   case 7: // Resetar Talents
				player->CLOSE_GOSSIP_MENU();
				player->resetTalents(true);
				player->SendTalentsInfoData(false);
				player->GetSession()->SendNotification("|cffFFFF00NPC TOOLS \n |cffFFFFFFTalentos Resetados com Sucesso!");
				player->CastSpell(player, 31726);
				break;
				
		case 8:	// BANK
				player->CLOSE_GOSSIP_MENU();
				player->GetSession()->SendShowBank(player->GetGUID());
				break;
				
		case 9: // MAIL
				player->CLOSE_GOSSIP_MENU();
				player->GetSession()->SendShowMailBox(player->GetGUID());
				break;

             }
                return true;
        }
};
 
void AddSC_MTG_Npc_Tools()
{
        new MTG_Npc_Tools();
}