#include "ScriptPCH.h"
#include "ScriptedGossip.h"
#include "Config.h"
#include "Language.h"
 
bool       DefaultToken;
int        RToken;
int        FToken;
int        CToken;
int        ReToken;
int		   MtgAura;
uint32     IDItem;
 
class MTG_Npc_Changer : public CreatureScript
{
    public:
 
		MTG_Npc_Changer() : CreatureScript("MTG_Npc_Changer"){}

		bool OnGossipHello(Player * player, Creature * creature)
		{
			   
			   
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Ability_Rogue_Disguise:40:40:-14|t Alterar Raça ", GOSSIP_SENDER_MAIN, 0);		// Alterar Raça
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Achievement_BG_winWSG:40:40:-14|t Alterar Facção", GOSSIP_SENDER_MAIN, 1);		// Alterar Facção
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Misc_GroupLooking:40:40:-14|t Alterar Aparência", GOSSIP_SENDER_MAIN, 2);	// Alterar Aparência
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Letter_18:40:40:-14|t Alterar Nome", GOSSIP_SENDER_MAIN, 3);				// Alterar Nome
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player * player, Creature * creature, uint32 /*uiSender*/, uint32 uiAction)
		{
		if(!player)
				return true;
					   if (DefaultToken)
		switch(uiAction)
		{
			case 0:
				if (player->HasItemCount(IDItem, RToken, true))
					{
						player->DestroyItemCount(IDItem, RToken, true, false);
						player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
						player->GetSession()->SendNotification("|cffFFFF00NPC CHANGER\n |cffFFFFFF Relogue para alterar sua Raça!|r");
						player->CastSpell(player, MtgAura);
						player->CLOSE_GOSSIP_MENU();
																		   
					}
					else
					{
							player->GetSession()->SendNotification("|cffFFFF00NPC CHANGER\n |cffFFFFFF Você não possuí Tokens o suficiente para alterar sua Raça!|r");
							player->CLOSE_GOSSIP_MENU();
					}
					break;
			case 1:
				if (player->HasItemCount(IDItem, FToken, true))
					{
						player->DestroyItemCount(IDItem, FToken, true, false);
						player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
						player->GetSession()->SendNotification("|cffFFFF00NPC CHANGER\n |cffFFFFFF Relogue para alterar sua Facção!");
						player->CastSpell(player, MtgAura);
						player->CLOSE_GOSSIP_MENU();					
						}
					else
						{
							player->GetSession()->SendNotification("|cffFFFF00NPC CHANGER\n |cffFFFFFF Você não possuí Tokens o suficiente para alterar sua Facção!|r");
							player->CLOSE_GOSSIP_MENU();
					}
					break;
			case 2:  
				if (player->HasItemCount(IDItem, CToken, true))
					{
						player->DestroyItemCount(IDItem, CToken, true, false);
						player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
						player->GetSession()->SendNotification("|cffFFFF00NPC CHANGER\n |cffFFFFFF Relogue para alterar sua Aparência!|r");
						player->CastSpell(player, MtgAura);
						player->CLOSE_GOSSIP_MENU();
						}

					else
						{
							player->GetSession()->SendNotification("|cffFFFF00NPC CHANGER\n |cffFFFFFF Você não possuí Tokens o suficiente para alterar sua Aparência!|r");
							player->CLOSE_GOSSIP_MENU();
					}
						break;
			case 3:
				if (player->HasItemCount(IDItem, ReToken, true))
					{
						player->DestroyItemCount(IDItem, ReToken, true, false);
						player->SetAtLoginFlag(AT_LOGIN_RENAME);
						player->GetSession()->SendNotification("|cffFFFF00NPC CHANGER\n |cffFFFFFF Relogue para alterar seu Nome!|r");
						player->CastSpell(player, MtgAura);
						player->CLOSE_GOSSIP_MENU();
						}

					else
						{
							player->GetSession()->SendNotification("|cffFFFF00NPC CHANGER\n |cffFFFFFF Você não possuí Tokens o suficiente para alterar seu Nome!|r");
							player->CLOSE_GOSSIP_MENU();
					}
						break;
			}            
			return true;
			}
 
};
 
 class Script_MTG_Npc_Changer_WorldScript : public WorldScript
{
public:
        Script_MTG_Npc_Changer_WorldScript() : WorldScript("Script_MTG_Npc_Changer_WorldScript") { }
 
        void OnConfigLoad(bool /*reload*/)
        {
							DefaultToken		= sConfigMgr->GetBoolDefault("Mtg.TokenNpc", true);
							RToken				= sConfigMgr->GetIntDefault("Mtg.RaceToken", 0);
							FToken				= sConfigMgr->GetIntDefault("Mtg.FactionToken", 0);
							CToken				= sConfigMgr->GetIntDefault("Mtg.CustomToken", 0);
							ReToken				= sConfigMgr->GetIntDefault("Mtg.RenameToken", 0);
							IDItem				= sConfigMgr->GetIntDefault("Mtg.ItemID", 0);
							MtgAura				= sConfigMgr->GetIntDefault("Mtg.AuraID",0);
 
        }
};
 
void AddSC_MTG_Npc_Changer()
{
        new MTG_Npc_Changer;
        new Script_MTG_Npc_Changer_WorldScript;
 
}