#include "ScriptMgr.h"
#include "ScriptPCH.h"
#include "Language.h"
#include "ScriptedGossip.h"
 
class MTG_Npc_Profissao : public CreatureScript
{
public:
    MTG_Npc_Profissao() : CreatureScript("MTG_Npc_Profissao") {}
 
    void CreatureWhisperBasedOnBool(const char *text, Creature *creature, Player *player, bool value)
    {
        if (value)
			creature->MonsterTextEmote(text, player);
    }
 
    uint32 PlayerMaxLevel() const
    {
        return sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);
    }
 
    bool PlayerHasItemOrSpell(const Player *plr, uint32 itemId, uint32 spellId) const
    {
        return plr->HasItemCount(itemId, 1, true) || plr->HasSpell(spellId);
    }
 
    bool OnGossipHello(Player *player, Creature* creature)
    {
		player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\Trade_Alchemy:40:40:-14|t Alchemy", GOSSIP_SENDER_MAIN, 100);						// Alchemy
		player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\Trade_BlackSmithing:40:40:-14|t BlackSmithing", GOSSIP_SENDER_MAIN, 101);			// BlackSmithing
		player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\Trade_LeatherWorking:40:40:-14|t Leatherworking", GOSSIP_SENDER_MAIN, 102);			// LeatherWorking
		player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\Trade_Tailoring:40:40:-14|t Tailoring", GOSSIP_SENDER_MAIN, 103);					// Tailoring
		player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\Trade_Engineering:40:40:-14|t Engineering", GOSSIP_SENDER_MAIN, 104);				// Engineering
		player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\Trade_Engraving:40:40:-14|t Enchanting", GOSSIP_SENDER_MAIN, 105);					// Enchanting
		player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\INV_Misc_Gem_02:40:40:-14|t Jewelcrafting", GOSSIP_SENDER_MAIN, 106);				// Jewelcrafting
		player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\INV_Inscription_Tradeskill01:40:40:-14|t Inscription", GOSSIP_SENDER_MAIN, 107);	// Inscription
		player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\Trade_Herbalism:40:40:-14|t Herbalism", GOSSIP_SENDER_MAIN, 108);					// Herbalism
		player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\INV_Misc_Pelt_Wolf_01:40:40:-14|t Skinning", GOSSIP_SENDER_MAIN, 109);				// Skinning
		player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\Trade_Mining:40:40:-14|t Mining", GOSSIP_SENDER_MAIN, 110);							// Mining
		player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\INV_Misc_Food_15:40:40:-14|t Cooking", GOSSIP_SENDER_MAIN, 111);					// Cooking
		player->ADD_GOSSIP_ITEM(9, "|TInterface\\icons\\Spell_Holy_SealOfSacrifice:40:40:-14|t First Aid", GOSSIP_SENDER_MAIN, 112);		// First Aid
		//player->ADD_GOSSIP_ITEM(9, "|TInterface/ICONS/Achievement_BG_returnXflags_def_WSG:40:40:-14|t Fechar", GOSSIP_SENDER_MAIN, 400);	// FIM MENU
        player->PlayerTalkClass->SendGossipMenu(907, creature->GetGUID());
        return true;
    }
 
    bool PlayerAlreadyHasTwoProfessions(const Player *player) const
    {
        uint32 skillCount = 0;
 
        if (player->HasSkill(SKILL_MINING))
            skillCount++;
        if (player->HasSkill(SKILL_SKINNING))
            skillCount++;
        if (player->HasSkill(SKILL_HERBALISM))
            skillCount++;
 
        if (skillCount >= 2)
            return true;
 
        for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
        {
            SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
            if (!SkillInfo)
                continue;
 
            if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
                continue;
 
            if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
                continue;
 
            const uint32 skillID = SkillInfo->id;
            if (player->HasSkill(skillID))
                skillCount++;
 
            if (skillCount >= 2)
                return true;
        }
        return false;
    }
 
    bool LearnAllRecipesInProfession(Player *player, SkillType skill)
    {
        ChatHandler handler(player->GetSession());
        char* skill_name;
 
        SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);
        skill_name = SkillInfo->name[handler.GetSessionDbcLocale()];
 
        if (!SkillInfo)
        {
			sLog->outError("LOG_FILTER_PLAYER_SKILLS", "Profissão NPC: recebeu ID habilidade não-válidos (LearnAllRecipesInProfession)");
        }
 
        LearnSkillRecipesHelper(player, SkillInfo->id);
 
        player->SetSkill(SkillInfo->id, player->GetSkillStep(SkillInfo->id), 450, 450);
        handler.PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, skill_name);
 
        return true;
    }
 
    void LearnSkillRecipesHelper(Player *player, uint32 skill_id)
    {
        uint32 classmask = player->getClassMask();
 
        for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
        {
            SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);
            if (!skillLine)
                continue;
 
            // wrong skill
            if (skillLine->skillId != skill_id)
                continue;
 
            // not high rank
            if (skillLine->forward_spellid)
                continue;
 
            // skip racial skills
            if (skillLine->racemask != 0)
                continue;
 
            // skip wrong class skills
            if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
                continue;
 
            SpellInfo const * spellInfo = sSpellMgr->GetSpellInfo(skillLine->spellId);
			if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo))
                continue;
 
			player->learnSpell(skillLine->spellId);
        }
    }
 
    bool IsSecondarySkill(SkillType skill) const
    {
        return skill == SKILL_COOKING || skill == SKILL_FIRST_AID;
    }
 
    void CompleteLearnProfession(Player *player, Creature *pCreature, SkillType skill)
    {
        if (PlayerAlreadyHasTwoProfessions(player) && !IsSecondarySkill(skill))
			pCreature->MonsterTextEmote("Você já treinou duas profissões!", player);
        else
        {
            if (!LearnAllRecipesInProfession(player, skill))
				pCreature->MonsterTextEmote("Ocorreu um erro interno!", player);
        }
    }
 
    bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
 
        if (uiSender == GOSSIP_SENDER_MAIN)
        {
 
            switch (uiAction)
            {

			case 100: // Alchemy Menu
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Book_09:40:40:-14|t Treinar Alchemy", GOSSIP_SENDER_MAIN, 200);			// Alchemy Treinar Skill
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Alchemy_CrystalVial:40:40:-14|t Shop Reagents", GOSSIP_SENDER_MAIN, 300);		// Alchemy Shop Reagents
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Achievement_BG_returnXflags_def_WSG:40:40:-14|t Voltar", GOSSIP_SENDER_MAIN, 401);	// Alchemy Menu Principal
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case 101: // Blacksmithing Menu
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Book_09:40:40:-14|t Treinar BlackSmithing", GOSSIP_SENDER_MAIN, 201);		// Blacksmithing Treinar Skill
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Hammer_20:40:40:-14|t Shop Reagents", GOSSIP_SENDER_MAIN, 301);					// Blacksmithing Shop Reagents
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Achievement_BG_returnXflags_def_WSG:40:40:-14|t Voltar", GOSSIP_SENDER_MAIN, 401);	// Blacksmithing Menu Principal
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case 102: // Leatherworking Menu
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Book_09:40:40:-14|t Treinar LeatherWorking", GOSSIP_SENDER_MAIN, 202);	// Leatherworking Treinar Skill
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Fabric_Felcloth_Ebon:40:40:-14|t Shop Reagents", GOSSIP_SENDER_MAIN, 302);		// Leatherworking Shop Reagents
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Achievement_BG_returnXflags_def_WSG:40:40:-14|t Voltar", GOSSIP_SENDER_MAIN, 401);	// Leatherworking Menu Principal
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case 103: // Tailoring Menu
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Book_09:40:40:-14|t Treinar Tailoring", GOSSIP_SENDER_MAIN, 203);			// Tailoring Treinar Skill
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Fabric_Linen_01:40:40:-14|t Shop Reagents", GOSSIP_SENDER_MAIN, 303);			// Tailoring Shop Reagents
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Achievement_BG_returnXflags_def_WSG:40:40:-14|t Voltar", GOSSIP_SENDER_MAIN, 401);	// Tailoring Menu Principal
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case 104: // Engineering Menu
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Book_09:40:40:-14|t Treinar Engineering", GOSSIP_SENDER_MAIN, 204);		// Engineering Treinar Skill
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Inv_Misc_Wrench_01:40:40:-14|t Shop Reagents", GOSSIP_SENDER_MAIN, 304);			// Engineering Shop Reagents
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Achievement_BG_returnXflags_def_WSG:40:40:-14|t Voltar", GOSSIP_SENDER_MAIN, 401);	// Engineering Menu Principal
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case 105: // Enchanting Menu
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Book_09:40:40:-14|t Treinar Enchanting", GOSSIP_SENDER_MAIN, 205);			// Enchanting Treinar Skill
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Enchant_DustVision:40:40:-14|t Shop Reagents", GOSSIP_SENDER_MAIN, 305);		// Enchanting Shop Reagents
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Achievement_BG_returnXflags_def_WSG:40:40:-14|t Voltar", GOSSIP_SENDER_MAIN, 401);	// Enchanting Menu Principal
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case 106: // Jewelcrafting Menu
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Book_09:40:40:-14|t Treinar JewelCrafting", GOSSIP_SENDER_MAIN, 206);		// Jewelcrafting Treinar Skill
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_JEWELCRAFTING_GEM_37:40:40:-14|t Shop Reagents", GOSSIP_SENDER_MAIN, 306);		// Jewelcrafting Shop Reagents
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Achievement_BG_returnXflags_def_WSG:40:40:-14|t Voltar", GOSSIP_SENDER_MAIN, 401);	// Jewelcrafting Menu Principal
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case 107: // Inscription Menu
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Book_09:40:40:-14|t Treinar Inscription", GOSSIP_SENDER_MAIN, 207);		// Inscription Treinar Skill
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Scroll_08:40:40:-14|t Shop Reagents", GOSSIP_SENDER_MAIN, 307);					// Inscription Shop Reagents
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Achievement_BG_returnXflags_def_WSG:40:40:-14|t Voltar", GOSSIP_SENDER_MAIN, 401);	// Inscription Menu Principal
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case 108: // Herbalism Menu
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Book_09:40:40:-14|t Treinar Herbalism", GOSSIP_SENDER_MAIN, 208);			// Herbalism Treinar Skill
				//player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Herb_GoldClover:40:40:-14|t Shop Reagents", GOSSIP_SENDER_MAIN, 308);		// Herbalism Shop Reagents
				//player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Achievement_BG_returnXflags_def_WSG:40:40:-14|t Voltar", GOSSIP_SENDER_MAIN, 401);	// Herbalism Menu Principal
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case 109: // Skinning Menu
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Book_09:40:40:-14|t Treinar Skinning", GOSSIP_SENDER_MAIN, 209);			// Skinning Treinar Skill
				//player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Qiraj_SkinSandworm:40:40:-14|t Shop Reagents", GOSSIP_SENDER_MAIN, 309);		// Skinning Shop Reagents
				//player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Achievement_BG_returnXflags_def_WSG:40:40:-14|t Voltar", GOSSIP_SENDER_MAIN, 401);	// Skinning Menu Principal
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case 110: // Mining Menu
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Book_09:40:40:-14|t Treinar Mining", GOSSIP_SENDER_MAIN, 210);				// Mining Treinar Skill
				//player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Ingot_08:40:40:-14|t Shop Reagents", GOSSIP_SENDER_MAIN, 310);					// Mining Shop Reagents
				//player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Achievement_BG_returnXflags_def_WSG:40:40:-14|t Voltar", GOSSIP_SENDER_MAIN, 401);	// Mining Menu Principal
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case 111: // Cooking Menu
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Book_09:40:40:-14|t Treinar Cooking", GOSSIP_SENDER_MAIN, 211);			// Cooking Treinar Skill
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_MISC_FOOD_16:40:40:-14|t Shop Reagents", GOSSIP_SENDER_MAIN, 311);				// Cooking Shop Reagents
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Achievement_BG_returnXflags_def_WSG:40:40:-14|t Voltar", GOSSIP_SENDER_MAIN, 401);	// Cooking Menu Principal
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			case 112: // First Aid Menu
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_Book_09:40:40:-14|t Treinar First Aid", GOSSIP_SENDER_MAIN, 212);			// First Aid Treinar Skill
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\INV_Misc_LeatherScrap_11:40:40:-14|t Shop Reagents", GOSSIP_SENDER_MAIN, 312);		// First Aid Shop Reagents
				player->ADD_GOSSIP_ITEM(4, "|TInterface\\icons\\Achievement_BG_returnXflags_def_WSG:40:40:-14|t Voltar", GOSSIP_SENDER_MAIN, 401);	// First Aid Menu Principal
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

				// Alchemy
            case 200:
                if (player->HasSkill(SKILL_ALCHEMY))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
 
                CompleteLearnProfession(player, creature, SKILL_ALCHEMY);
 
                player->PlayerTalkClass->SendCloseGossip();
                break;

				// Alchemy Shop

			case 300:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200000);
				return true;

				// BlackSmithing
            case 201:
                if (player->HasSkill(SKILL_BLACKSMITHING))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
                CompleteLearnProfession(player, creature, SKILL_BLACKSMITHING);
 
                player->PlayerTalkClass->SendCloseGossip();
                break;

				// BlackSmithing Shop
			case 301:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200001);
				return true;

				// LeaterWorking
            case 202:
                if (player->HasSkill(SKILL_LEATHERWORKING))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
                CompleteLearnProfession(player, creature, SKILL_LEATHERWORKING);
 
                player->PlayerTalkClass->SendCloseGossip();
                break;

				// LeatherWorking Shop
			case 302:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200002);
				return true;


				// Tailoring
            case 203:
                if (player->HasSkill(SKILL_TAILORING))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
                CompleteLearnProfession(player, creature, SKILL_TAILORING);
 
                player->PlayerTalkClass->SendCloseGossip();
                break;

				// Tailoring Shop
			case 303:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200003);
				return true;


				// Engineering
            case 204:
                if (player->HasSkill(SKILL_ENGINEERING))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
                CompleteLearnProfession(player, creature, SKILL_ENGINEERING);
 
                player->PlayerTalkClass->SendCloseGossip();
                break;

				// Engineering Shop
			case 304:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200004);
				return true;


				// Enchanting
            case 205:
                if (player->HasSkill(SKILL_ENCHANTING))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
                CompleteLearnProfession(player, creature, SKILL_ENCHANTING);
 
                player->PlayerTalkClass->SendCloseGossip();
                break;

				// Enchanting Shop
			case 305:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200005);
				return true;


				// JewelCrafting
            case 206:
                if (player->HasSkill(SKILL_JEWELCRAFTING))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
                CompleteLearnProfession(player, creature, SKILL_JEWELCRAFTING);
 
                player->PlayerTalkClass->SendCloseGossip();
                break;

				// JewelCrafting Shop
			case 306:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200006);
				return true;


				// Inscription
            case 207:
                if (player->HasSkill(SKILL_INSCRIPTION))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
                CompleteLearnProfession(player, creature, SKILL_INSCRIPTION);
 
                player->PlayerTalkClass->SendCloseGossip();
                break;

				// Inscription Shop
			case 307:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200007);
				return true;

				// Herbalism
            case 208:
                if (player->HasSkill(SKILL_HERBALISM))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
 
                CompleteLearnProfession(player, creature, SKILL_HERBALISM);
                player->PlayerTalkClass->SendCloseGossip();
                break;

		/*		// Herbalism Shop
			case 308:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200008);
				return true;

*/
				// Skinning
            case 209:
                if (player->HasSkill(SKILL_SKINNING))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
 
                CompleteLearnProfession(player, creature, SKILL_SKINNING);
                player->PlayerTalkClass->SendCloseGossip();
                break;

		/*		// Skinning Shop
			case 309:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200009);
				return true;

*/
				// Mining
            case 210:
                if (player->HasSkill(SKILL_MINING))
                {
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                }
 
                CompleteLearnProfession(player, creature, SKILL_MINING);
                player->PlayerTalkClass->SendCloseGossip();
                break;

			/*	// Mining Shop
			case 310:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200010);
				return true;

*/
				// Cooking
			case 211:
				if (player->HasSkill(SKILL_COOKING))
				{
					player->PlayerTalkClass->SendCloseGossip();
					break;
				}

				CompleteLearnProfession(player, creature, SKILL_COOKING);
				player->PlayerTalkClass->SendCloseGossip();
				break;

				// Cooking Shop
			case 311:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200011);
				return true;


				// First Aid
			case 212:
				if (player->HasSkill(SKILL_FIRST_AID))
				{
					player->PlayerTalkClass->SendCloseGossip();
					break;
				}

				CompleteLearnProfession(player, creature, SKILL_FIRST_AID);
				player->PlayerTalkClass->SendCloseGossip();
				break;

				// First Aid Shop
			case 312:
				player->PlayerTalkClass->ClearMenus();
				player->GetSession()->SendListInventory(creature->GetGUID(), 200012);
				return true;

			/*	
				// Fechar Menu
            case 400:
                player->PlayerTalkClass->SendCloseGossip();
                break;	
			*/
			
				// Menu Principal
			case 401:
				OnGossipHello(player, creature);
				break;

            }
 
 
        }
        return true;
    }
};
 
void AddSC_MTG_Npc_Profissao()
{
    new MTG_Npc_Profissao();
}