#include "ScriptMgr.h"
#include "Language.h"


#define	TEL_HUMAN 0, -8949.950195f, -132.492996f, 83.531197f, 0.000000f
#define TEL_DWARF 0, -6240.319824f, 331.032990f, 382.757996f, 6.177160f
#define TEL_NIGHT 1, 10311.299805f, 832.463013f, 1326.408203f, 5.696320f
#define TEL_GNOME 0, -6240.319824f, 331.032990f, 382.757996f, 6.177160f
#define TEL_DRAEN 530, -3961.639893f, -13931.200195f, 100.613525f, 2.083640f

#define TEL_ORCS 1, -618.518005f, -4251.669922f, 38.717999f, 0.000000f
#define TEL_UNDEAD 0, 1676.709961f, 1678.310059f, 121.669998f, 2.948734f
#define TEL_TAUREN 1, -2917.580078f, -257.980011f, 52.996799f, 0.000000f
#define TEL_TROLL 1, -618.518005f, -4251.669922f, 38.717999f, 0.000000f
#define TEL_BLOOD 530, 10349.599609f, -6357.290039f, 33.402599f, 5.316050f


class MTG_Npc_Reset : public CreatureScript
{
public: MTG_Npc_Reset() : CreatureScript("MTG_Npc_Reset") {}

		bool OnGossipHello(Player* player, Creature* creature)
		{
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\Ability_Paladin_BeaconofLight:40:40:-14|t Resetar Level", GOSSIP_SENDER_MAIN, 1);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			return true;
		}

		bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
		{
			player->PlayerTalkClass->ClearMenus();

			switch (player->getRace())
			{
			case RACE_HUMAN:
				
				if (player->getLevel() != 79)
				{
					uint8 newLevel = player->getLevel() - 79;
					player->GiveLevel(newLevel);
					player->ModifyMoney(1000000000);
					player->InitTalentForLevel();
					player->SetUInt32Value(PLAYER_XP, 0);
					player->resetTalents();
					player->TeleportTo(TEL_HUMAN);
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFFFFFFVoce realizou seu reset com sucesso!\n |cffFFFFFFSeus premios ja foram entregues!");
					//CharacterDatabase.PExecute("UPDATE characters SET resets = +1 WHERE guid = '%u'", player->GetSession()->GetAccountId());
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFF0000Atencao, voce nao possui nivel o suficiente para resetar!");
					return false;
				}
				
				break;

			case RACE_DWARF:

				if (player->getLevel() != 79)
				{
					uint8 newLevel = player->getLevel() - 79;
					player->GiveLevel(newLevel);
					player->ModifyMoney(1000000000);
					player->InitTalentForLevel();
					player->SetUInt32Value(PLAYER_XP, 0);
					player->resetTalents();
					player->TeleportTo(TEL_DWARF);
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFFFFFFVoce realizou seu reset com sucesso!\n |cffFFFFFFSeus premios ja foram entregues!");
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFF0000Atencao, voce nao possui nivel o suficiente para resetar!");
					return false;
				}

				break;

			case RACE_NIGHTELF:

				if (player->getLevel() != 79)
				{
					uint8 newLevel = player->getLevel() - 79;
					player->GiveLevel(newLevel);
					player->ModifyMoney(1000000000);
					player->InitTalentForLevel();
					player->SetUInt32Value(PLAYER_XP, 0);
					player->resetTalents();
					player->TeleportTo(TEL_NIGHT);
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFFFFFFVoce realizou seu reset com sucesso!\n |cffFFFFFFSeus premios ja foram entregues!");
					
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFF0000Atencao, voce nao possui nivel o suficiente para resetar!");
					return false;
				}

				break;

			case RACE_GNOME:

				if (player->getLevel() != 79)
				{
					uint8 newLevel = player->getLevel() - 79;
					player->GiveLevel(newLevel);
					player->ModifyMoney(1000000000);
					player->InitTalentForLevel();
					player->SetUInt32Value(PLAYER_XP, 0);
					player->resetTalents();
					player->TeleportTo(TEL_GNOME);
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFFFFFFVoce realizou seu reset com sucesso!\n |cffFFFFFFSeus premios ja foram entregues!");
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFF0000Atencao, voce nao possui nivel o suficiente para resetar!");
					return false;
				}

				break;

			case RACE_DRAENEI:

				if (player->getLevel() != 79)
				{
					uint8 newLevel = player->getLevel() - 79;
					player->GiveLevel(newLevel);
					player->ModifyMoney(1000000000);
					player->InitTalentForLevel();
					player->SetUInt32Value(PLAYER_XP, 0);
					player->resetTalents();
					player->TeleportTo(TEL_DRAEN);
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFFFFFFVoce realizou seu reset com sucesso!\n |cffFFFFFFSeus premios ja foram entregues!");
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFF0000Atencao, voce nao possui nivel o suficiente para resetar!");
					return false;
				}

				break;


			case RACE_ORC:

				if (player->getLevel() != 79)
				{
					uint8 newLevel = player->getLevel() - 79;
					player->GiveLevel(newLevel);
					player->ModifyMoney(1000000000);
					player->InitTalentForLevel();
					player->SetUInt32Value(PLAYER_XP, 0);
					player->resetTalents();
					player->TeleportTo(TEL_ORCS);
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFFFFFFVoce realizou seu reset com sucesso!\n |cffFFFFFFSeus premios ja foram entregues!");
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFF0000Atencao, voce nao possui nivel o suficiente para resetar!");
					return false;
				}

				break;

			case RACE_UNDEAD_PLAYER:

				if (player->getLevel() != 79)
				{
					uint8 newLevel = player->getLevel() - 79;
					player->GiveLevel(newLevel);
					player->ModifyMoney(1000000000);
					player->InitTalentForLevel();
					player->SetUInt32Value(PLAYER_XP, 0);
					player->resetTalents();
					player->TeleportTo(TEL_UNDEAD);
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFFFFFFVoce realizou seu reset com sucesso!\n |cffFFFFFFSeus premios ja foram entregues!");
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFF0000Atencao, voce nao possui nivel o suficiente para resetar!");
					return false;
				}

				break;

			case RACE_TAUREN:

				if (player->getLevel() != 79)
				{
					uint8 newLevel = player->getLevel() - 79;
					player->GiveLevel(newLevel);
					player->ModifyMoney(1000000000);
					player->InitTalentForLevel();
					player->SetUInt32Value(PLAYER_XP, 0);
					player->resetTalents();
					player->TeleportTo(TEL_TAUREN);
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFFFFFFVoce realizou seu reset com sucesso!\n |cffFFFFFFSeus premios ja foram entregues!");
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFF0000Atencao, voce nao possui nivel o suficiente para resetar!");
					return false;
				}

				break;

			case RACE_TROLL:

				if (player->getLevel() != 79)
				{
					uint8 newLevel = player->getLevel() - 79;
					player->GiveLevel(newLevel);
					player->ModifyMoney(1000000000);
					player->InitTalentForLevel();
					player->SetUInt32Value(PLAYER_XP, 0);
					player->resetTalents();
					player->TeleportTo(TEL_TROLL);
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFFFFFFVoce realizou seu reset com sucesso!\n |cffFFFFFFSeus premios ja foram entregues!");
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFF0000Atencao, voce nao possui nivel o suficiente para resetar!");
					return false;
				}

				break;

			case RACE_BLOODELF:

				if (player->getLevel() != 79)
				{
					uint8 newLevel = player->getLevel() - 79;
					player->GiveLevel(newLevel);
					player->ModifyMoney(1000000000);
					player->InitTalentForLevel();
					player->SetUInt32Value(PLAYER_XP, 0);
					player->resetTalents();
					player->TeleportTo(TEL_BLOOD);
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFFFFFFVoce realizou seu reset com sucesso!\n |cffFFFFFFSeus premios ja foram entregues!");
				}
				else
				{
					player->CLOSE_GOSSIP_MENU();
					player->GetSession()->SendNotification("|cffFFFF00Reset System\n |cffFF0000Atencao, voce nao possui nivel o suficiente para resetar!");
					return false;
				}

				break;

			}
			return true;
		}
};

void AddSC_MTG_Npc_Reset()
{
	new MTG_Npc_Reset;
}