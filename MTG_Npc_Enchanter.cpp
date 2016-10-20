#include "Player.h"
#include "Define.h"
#include "Creature.h"
#include "ScriptMgr.h"
#include "WorldSession.h"
#include "ScriptedGossip.h"

#define ERROR_NO1H				"Este encantar exige uma One-Handed a ser equipado!"
#define ERROR_NO2H				"Este encantar exige uma arma Two-Handed para ser equipado!"
#define ERROR_NOSHIELD			"Este encantar requer um Shield para ser equipado!"
#define NO_2H					"Voce nao tem Two-Handed equipada."
#define NO_1H					"Voce nao tem One-Handed equipada."
#define NO_SHIELD				"Voce nao tem Shield equipado."
#define ERROR_1HOFFHAND			"Este encantar exige One-Hand equipado no Off-Hand!"
#define ERROROFFH				"Seu Off-Hand neo e uma arma."
#define ERROR_RANGED			"Voce nao possui ranged equipado"

enum Enchants
{
	ENCHANT_WEP_BERSERKING = 3789,
	ENCHANT_WEP_BLADE_WARD = 3869,
	ENCHANT_WEP_BLOOD_DRAINING = 3870,
	ENCHANT_WEP_ACCURACY = 3788,
	ENCHANT_WEP_AGILITY_1H = 1103,
	ENCHANT_WEP_SPIRIT = 3844,
	ENCHANT_WEP_BATTLEMASTER = 2675,
	ENCHANT_WEP_BLACK_MAGIC = 3790,
	ENCHANT_WEP_ICEBREAKER = 3239,
	ENCHANT_WEP_LIFEWARD = 3241,
	ENCHANT_WEP_MIGHTY_SPELL_POWER = 3834, // One-hand
	ENCHANT_WEP_EXECUTIONER = 3225,
	ENCHANT_WEP_POTENCY = 3833,
	ENCHANT_WEP_TITANGUARD = 3851,
	ENCHANT_WEP_TITANIUM_CHAIN = 3731,

	ENCHANT_2WEP_MASSACRE = 3827,
	ENCHANT_2WEP_SCOURGEBANE = 3247,
	ENCHANT_2WEP_GIANT_SLAYER = 3251,
	ENCHANT_2WEP_GREATER_SPELL_POWER = 3854,
	ENCHANT_2WEP_AGILITY = 2670,
	ENCHANT_2WEP_MONGOOSE = 2673,

	ENCHANT_SHIELD_DEFENSE = 1952,
	ENCHANT_SHIELD_INTELLECT = 1128,
	ENCHANT_SHIELD_RESILIENCE = 3229,
	ENCHANT_SHIELD_BLOCK = 2655,
	ENCHANT_SHIELD_STAMINA = 1071,
	ENCHANT_SHIELD_TOUGHSHIELD = 2653,
	ENCHANT_SHIELD_TITANIUM_PLATING = 3849,

	ENCHANT_HEAD_BLISSFUL_MENDING = 3819,
	ENCHANT_HEAD_BURNING_MYSTERIES = 3820,
	ENCHANT_HEAD_DOMINANCE = 3796,
	ENCHANT_HEAD_SAVAGE_GLADIATOR = 3842,
	ENCHANT_HEAD_STALWART_PROTECTOR = 3818,
	ENCHANT_HEAD_TORMENT = 3817,
	ENCHANT_HEAD_TRIUMPH = 3795,
	ENCHANT_HEAD_ECLIPSED_MOON = 3815,
	ENCHANT_HEAD_FLAME_SOUL = 3816,
	ENCHANT_HEAD_FLEEING_SHADOW = 3814,
	ENCHANT_HEAD_FROSTY_SOUL = 3812,
	ENCHANT_HEAD_TOXIC_WARDING = 3813,

	ENCHANT_SHOULDER_MASTERS_AXE = 3835,
	ENCHANT_SHOULDER_MASTERS_CRAG = 3836,
	ENCHANT_SHOULDER_MASTERS_PINNACLE = 3837,
	ENCHANT_SHOULDER_MASTERS_STORM = 3838,
	ENCHANT_SHOULDER_GREATER_AXE = 3808,
	ENCHANT_SHOULDER_GREATER_CRAG = 3809,
	ENCHANT_SHOULDER_GREATER_GLADIATOR = 3852,
	ENCHANT_SHOULDER_GREATER_PINNACLE = 3811,
	ENCHANT_SHOULDER_GREATER_STORM = 3810,
	ENCHANT_SHOULDER_DOMINANCE = 3794,
	ENCHANT_SHOULDER_TRIUMPH = 3793,

	ENCHANT_CLOAK_DARKGLOW_EMBROIDERY = 3728,
	ENCHANT_CLOAK_SWORDGUARD_EMBROIDERY = 3730,
	ENCHANT_CLOAK_LIGHTWEAVE_EMBROIDERY = 3722,
	ENCHANT_CLOAK_SPRINGY_ARACHNOWEAVE = 3859,
	ENCHANT_CLOAK_WISDOM = 3296,
	ENCHANT_CLOAK_TITANWEAVE = 1951,
	ENCHANT_CLOAK_SPELL_PIERCING = 3243,
	ENCHANT_CLOAK_SHADOW_ARMOR = 3256,
	ENCHANT_CLOAK_MIGHTY_ARMOR = 3294,
	ENCHANT_CLOAK_MAJOR_AGILITY = 1099,
	ENCHANT_CLOAK_GREATER_SPEED = 3831,
	ENCHANT_CLOAK_FLEXWEAVE_UNDERLAY = 3605,

	ENCHANT_LEG_EARTHEN = 3853,
	ENCHANT_LEG_FROSTHIDE = 3822,
	ENCHANT_LEG_ICESCALE = 3823,
	ENCHANT_LEG_BRILLIANT_SPELLTHREAD = 3719,
	ENCHANT_LEG_SAPPHIRE_SPELLTHREAD = 3721,
	/*  ENCHANT_LEG_DRAGONSCALE             = 3331,
	ENCHANT_LEG_WYRMSCALE                   = 3332, */

	ENCHANT_GLOVES_GREATER_BLASTING = 3249,
	ENCHANT_GLOVES_ARMSMAN = 3253,
	ENCHANT_GLOVES_CRUSHER = 1603,
	ENCHANT_GLOVES_AGILITY = 3222,
	ENCHANT_GLOVES_PRECISION = 3234,
	ENCHANT_GLOVES_EXPERTISE = 3231,
	ENCHANT_GLOVES_EXCEPTIONAL_SPELLPOWER = 3246,

	ENCHANT_GLOVES_SOCKET_GLOVES = 3723,
	ENCHANT_GLOVES_PYROROCKET = 3603,
	ENCHANT_GLOVES_HYPERSPEED_ACCELERATORS = 3604,

	ENCHANT_BRACERS_MAJOR_STAMINA = 3850,
	ENCHANT_BRACERS_SUPERIOR_SP = 2332,
	ENCHANT_BRACERS_GREATER_ASSUALT = 3845,
	ENCHANT_BRACERS_MAJOR_SPIRT = 1147,
	ENCHANT_BRACERS_EXPERTISE = 3231,
	ENCHANT_BRACERS_GREATER_STATS = 2661,
	ENCHANT_BRACERS_INTELLECT = 1119,
	ENCHANT_BRACERS_FURL_ARCANE = 3763,
	ENCHANT_BRACERS_FURL_FIRE = 3759,
	ENCHANT_BRACERS_FURL_FROST = 3760,
	ENCHANT_BRACERS_FURL_NATURE = 3762,
	ENCHANT_BRACERS_FURL_SHADOW = 3761,
	ENCHANT_BRACERS_FURL_ATTACK = 3756,
	ENCHANT_BRACERS_FURL_STAMINA = 3757,
	ENCHANT_BRACERS_FURL_SPELLPOWER = 3758,
	ENCHANT_BRACER_SOCKET_BRACER = 3717,

	ENCHANT_CHEST_POWERFUL_STATS = 3832,
	ENCHANT_CHEST_SUPER_HEALTH = 3297,
	ENCHANT_CHEST_GREATER_MAINA_REST = 2381,
	ENCHANT_CHEST_EXCEPTIONAL_RESIL = 3245,
	ENCHANT_CHEST_GREATER_DEFENSE = 1953,

	ENCHANT_BOOTS_GREATER_ASSULT = 1597,
	ENCHANT_BOOTS_TUSKARS_VITLIATY = 3232,
	ENCHANT_BOOTS_SUPERIOR_AGILITY = 983,
	ENCHANT_BOOTS_GREATER_SPIRIT = 1147,
	ENCHANT_BOOTS_GREATER_VITALITY = 3244,
	ENCHANT_BOOTS_ICEWALKER = 3826,
	ENCHANT_BOOTS_GREATER_FORTITUDE = 1075,
	ENCHANT_BOOTS_NITRO_BOOTS = 3606,

	ENCHANT_RING_ASSULT = 3839,
	ENCHANT_RING_GREATER_SP = 3840,
	ENCHANT_RING_STAMINA = 3791,

	ENCHANT_RANGED_HEARTSEEKER_SCOPE = 3608,
	ENCHANT_RANGED_SUN_SCOPE = 3607,

	ENCHANT_BELT_ETERNAL_BELT_BUCKLE = 3729,
	ENCHANT_BELT_FRAG_BELT = 3601
};

// Enchant Socket

void AdvancedEnchant(Player* player, Item* item, EnchantmentSlot slot, uint32 socketGem)
{
	if (!item)
	{
		ChatHandler(player->GetSession()).PSendSysMessage("Primeiro voce deve equipar o item!", LANG_UNIVERSAL);
		return;
	}

	if (!socketGem)
	{
		ChatHandler(player->GetSession()).PSendSysMessage("Algo deu errado no codigo.", LANG_UNIVERSAL);
		return;
	}

	player->ApplyEnchantment(item, slot, false);
	item->SetEnchantment(slot, socketGem, 0, 0);
	player->ApplyEnchantment(item, slot, true);

	std::string color = "|cff";
	switch (item->GetTemplate()->Quality)
	{
	case 0: color += "9d9d9d"; break;
	case 1: color += "ffffff"; break;
	case 2: color += "1eff00"; break;
	case 3: color += "0070dd"; break;
	case 4: color += "a335ee"; break;
	case 5: color += "ff8000"; break;
	}
	ChatHandler(player->GetSession()).PSendSysMessage("%s[%s]|r - Encantada com sucesso!", color.c_str(), item->GetTemplate()->Name1.c_str());
}


// Enchant Itens

void Enchant(Player* player, Item* item, uint32 enchantid)
{
	if (!item)
	{
		ChatHandler(player->GetSession()).PSendSysMessage("Primeiro voce deve equipar o item!", LANG_UNIVERSAL);
		return;
	}

	if (!enchantid)
	{
		ChatHandler(player->GetSession()).PSendSysMessage("Algo deu errado no codigo.", LANG_UNIVERSAL);
		return;
	}

	player->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, false);
	item->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchantid, 0, 0);
	player->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, true);

	std::string color = "|cff";
	switch (item->GetTemplate()->Quality)
	{
	case 0: color += "9d9d9d"; break;
	case 1: color += "ffffff"; break;
	case 2: color += "1eff00"; break;
	case 3: color += "0070dd"; break;
	case 4: color += "a335ee"; break;
	case 5: color += "ff8000"; break;
	}
	ChatHandler(player->GetSession()).PSendSysMessage("%s[%s]|r - Encantada com sucesso!", color.c_str(), item->GetTemplate()->Name1.c_str());
}

class MTG_Npc_Enchants : public CreatureScript
{
public:
	MTG_Npc_Enchants() : CreatureScript("MTG_Npc_Enchants") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Misc_Desecrated_PlateHelm:35:35:-14|t Head",							GOSSIP_SENDER_MAIN, 1);		// Head
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Misc_Desecrated_PlateShoulder:35:35:-14|t Shoulders",					GOSSIP_SENDER_MAIN, 2);		// Shoulders
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Misc_Desecrated_PlateChest:35:35:-14|t Chest",							GOSSIP_SENDER_MAIN, 3);		// Chest
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Misc_Desecrated_PlateGloves:35:35:-14|t Gloves",						GOSSIP_SENDER_MAIN, 4);		// Gloves
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Misc_Desecrated_PlatePants:35:35:-14|t Legs",							GOSSIP_SENDER_MAIN, 5);		// Legs
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Misc_Desecrated_PlateBracer:35:35:-14|t Bracers",						GOSSIP_SENDER_MAIN, 6);		// Bracers
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Misc_Desecrated_PlateBelt:35:35:-14|t Belt ",							GOSSIP_SENDER_MAIN, 7);		// Belt
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Misc_Desecrated_PlateBoots:35:35:-14|t Feet",							GOSSIP_SENDER_MAIN, 8);		// Feet
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Misc_Cape_11:35:35:-14|t Cloak",										GOSSIP_SENDER_MAIN, 9);		// Cloak
	if (player->HasSkill(SKILL_ENCHANTING) && player->GetSkillValue(SKILL_ENCHANTING) == 450) // Requer Enchanting 450
	 {
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Jewelry_Ring_01:35:35:-14|t Ring 1",									GOSSIP_SENDER_MAIN, 10);	// Ring 1
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Jewelry_Ring_01:35:35:-14|t Ring 2",									GOSSIP_SENDER_MAIN, 11);	// Ring 2
	 }
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Sword_04:35:35:-14|t Main Hand",										GOSSIP_SENDER_MAIN, 12);	// Main Hand
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Shield_04:35:35:-14|t Off Hand",										GOSSIP_SENDER_MAIN, 13);	// Off Hand
		player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Weapon_Crossbow_04:35:35:-14|t Ranged",								GOSSIP_SENDER_MAIN, 14);	// Ranged

		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		Item * item;

		switch (action)
		{

		case 1:	// HEAD
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Insira seu head por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_HEAD)
			{
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +50 Attack Power +20 Critical",				GOSSIP_SENDER_MAIN, 1000);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +50 Attack Power +20 Resilience",			GOSSIP_SENDER_MAIN, 1001);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +30 Spell Power +20 Critical",				GOSSIP_SENDER_MAIN, 1002);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +29 Spell Power +20 Resilience",				GOSSIP_SENDER_MAIN, 1003);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +30 Spell Power +10 Mp5",					GOSSIP_SENDER_MAIN, 1004);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +30 Stamina +25 Resilience",					GOSSIP_SENDER_MAIN, 1005);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +37 Stamina +20 Defense",					GOSSIP_SENDER_MAIN, 1006);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +25 Arcane Resist +30 Stamina",				GOSSIP_SENDER_MAIN, 1007);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +25 Fire Resist +30 Stamina",				GOSSIP_SENDER_MAIN, 1008);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +25 Shadow Resist +30 Stamina",				GOSSIP_SENDER_MAIN, 1009);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +25 Frost Resist +30 Stamina",				GOSSIP_SENDER_MAIN, 1010);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +25 Nature Resist +30 Stamina",				GOSSIP_SENDER_MAIN, 1011);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",					GOSSIP_SENDER_MAIN, 300);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			}

			else
			{
				player->GetSession()->SendAreaTriggerMessage("Insira seu head por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
			}
		}
		return true;

		case 1000: // +50 Attack Power + 20 Critical
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_TORMENT);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1001: // +50 Attack Power + 20 Resilience
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_TRIUMPH);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1002: // +30 Spell Power + 20 Critical
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_BURNING_MYSTERIES);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1003: // +29 Spell Power + 20 Resilience
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_DOMINANCE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1004: // +30 Spell Power + 10 Mp5
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_BLISSFUL_MENDING);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1005: // +30 Stamina + 25 Resilience
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_SAVAGE_GLADIATOR);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1006: // +37 Stamina + 20 Defense
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_STALWART_PROTECTOR);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1007: // +25 Arcane Resist + 30 Stamina
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_ECLIPSED_MOON);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1008: // +25 Fire Resist + 30 Stamina
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_FLAME_SOUL);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1009: // +25 Shadow Resist + 30 Stamina
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_FLEEING_SHADOW);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1010: // +25 Frost Resist + 30 Stamina
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_FROSTY_SOUL);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1011: // +25 Nature Resist + 30 Stamina
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HEAD), ENCHANT_HEAD_TOXIC_WARDING);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;


		case 2: // SHOULDERS
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Insira seu shoulder por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHOULDERS)
			{
		if (player->HasSkill(SKILL_INSCRIPTION) && player->GetSkillValue(SKILL_INSCRIPTION) == 450)
		 {
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +120 Attack Power +15 Critical",						GOSSIP_SENDER_MAIN, 2000);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +70 Spell Power +15 Critical",						GOSSIP_SENDER_MAIN, 2001);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +70 Spell Power +8 Mp5",								GOSSIP_SENDER_MAIN, 2002);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +60 Dodge +15 Defense",								GOSSIP_SENDER_MAIN, 2003);
		 }
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +40 Attack Power +15 Critical",						GOSSIP_SENDER_MAIN, 2004);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +40 Attack Power +15 Resilience",					GOSSIP_SENDER_MAIN, 2005);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +24 Spell Power +15 Critical",						GOSSIP_SENDER_MAIN, 2006);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +23 Spell Power +15 Resilience",						GOSSIP_SENDER_MAIN, 2007);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +24 Spell Power +8 Mp5",								GOSSIP_SENDER_MAIN, 2008);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +30 Stamina +15 Resilience",							GOSSIP_SENDER_MAIN, 2009);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +20 Dodge +15 Defense",								GOSSIP_SENDER_MAIN, 2010);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",							GOSSIP_SENDER_MAIN, 300);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			}

			else
			{
				player->GetSession()->SendAreaTriggerMessage("Insira seu shoulder por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
			}
		}
		return true;



		case 2000: // +120 Attack Power +15 Critical
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_MASTERS_AXE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 2001: // +70 Spell Power +15 Critical
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_MASTERS_STORM);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 2002: // +70 Spell Power +8 Mp5
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_MASTERS_CRAG);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 2003: // +60 Dodge +15 Defense
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_MASTERS_PINNACLE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 2004: // +40 Attack Power +15 Critical
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_GREATER_AXE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 2005: // +40 Attack Power +15 Resilience
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_TRIUMPH);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 2006: // +24 Spell Power +15 Critical
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_GREATER_STORM);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 2007: // +23 Spell Power +15 Resilience
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_DOMINANCE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 2008: // +24 Spell Power +8 Mp5
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_GREATER_CRAG);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 2009: // +30 Stamina +15 Resilience
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_GREATER_GLADIATOR);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 2010: // +20 Dodge +15 Defense
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_SHOULDERS), ENCHANT_SHOULDER_GREATER_PINNACLE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;


		case 3: // CHEST
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +10 All Stats",							GOSSIP_SENDER_MAIN, 3000);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +275 Health",							GOSSIP_SENDER_MAIN, 3001);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +10 Mp5",								GOSSIP_SENDER_MAIN, 3002);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +20 Resilience",							GOSSIP_SENDER_MAIN, 3003);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +22 Defense",							GOSSIP_SENDER_MAIN, 3004);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",				GOSSIP_SENDER_MAIN, 300);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
		
		case 3000: // +10 All Stats
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), ENCHANT_CHEST_POWERFUL_STATS);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 3001: // +275 Health
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), ENCHANT_CHEST_SUPER_HEALTH);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 3002: // +10 Mp5
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), ENCHANT_CHEST_GREATER_MAINA_REST);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 3003: // +20 Resilience
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), ENCHANT_CHEST_EXCEPTIONAL_RESIL);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 3004: // +22 Defense
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_CHEST), ENCHANT_CHEST_GREATER_DEFENSE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;


		case 4: // GLOVES
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Insira sua hands por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_HANDS)
			{

		if (player->HasSkill(SKILL_BLACKSMITHING) && player->GetSkillValue(SKILL_BLACKSMITHING) == 450)	// BLACKSMITHING
		 {
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Socket Gloves",								GOSSIP_SENDER_MAIN, 4000);
		 }
		if (player->HasSkill(SKILL_ENGINEERING) && player->GetSkillValue(SKILL_ENGINEERING) == 450) // ENGINE
		 {
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Hand-Mounted Pyro Rocket",					GOSSIP_SENDER_MAIN, 4001);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Hyperspeed +340 Haste Rating",				GOSSIP_SENDER_MAIN, 4002);
		 }
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +44 Attack Power",							GOSSIP_SENDER_MAIN, 4003);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +28 Spell Power",							GOSSIP_SENDER_MAIN, 4004);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +20 Agility",								GOSSIP_SENDER_MAIN, 4005);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +20 Hit Rating",								GOSSIP_SENDER_MAIN, 4006);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +16 Critical Rating",						GOSSIP_SENDER_MAIN, 4007);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +15 Expertise Rating",						GOSSIP_SENDER_MAIN, 4008);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +10 Parry Rating + 2% Threat",				GOSSIP_SENDER_MAIN, 4009);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",					GOSSIP_SENDER_MAIN, 300);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			}

			else
			{
				player->GetSession()->SendAreaTriggerMessage("Insira sua hands por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
			}
		}
		return true;



		case 4000: // Socket Gloves
			AdvancedEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), PRISMATIC_ENCHANTMENT_SLOT, ENCHANT_GLOVES_SOCKET_GLOVES);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 4001: // Hand-Mounted Pyro Rocket
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_PYROROCKET);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 4002: // Hyperspeed +340 Haste Rating
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_HYPERSPEED_ACCELERATORS);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 4003: // +44 Attack Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_CRUSHER);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 4004: // +28 Spell Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_EXCEPTIONAL_SPELLPOWER);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 4005: // +20 Agility
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_AGILITY);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 4006: // +20 Hit Rating
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_PRECISION);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 4007: // +16 Critical Rating
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_GREATER_BLASTING);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 4008: // +15 Expertise Rating
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_EXPERTISE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 4009: // +10 Parry Rating + 2% Threat
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_HANDS), ENCHANT_GLOVES_ARMSMAN);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;




		case 5: // LEGS
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Insira sua legs por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_LEGS)
			{
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +75 Attack Power +22 Critical",				GOSSIP_SENDER_MAIN, 5000);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +50 Spell Power +20 Spirit",					GOSSIP_SENDER_MAIN, 5001);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +50 Spell Power +30 Stamina",				GOSSIP_SENDER_MAIN, 5002);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +40 Reslience +28 Stamina",					GOSSIP_SENDER_MAIN, 5003);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +55 Stamina +22 Agility",					GOSSIP_SENDER_MAIN, 5004);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",					GOSSIP_SENDER_MAIN, 300);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			}

			else
			{
				player->GetSession()->SendAreaTriggerMessage("Insira sua legs por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
			}
		}
		return true;





		case 5000: // +75 Attack Power + 22 Critical
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), ENCHANT_LEG_ICESCALE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 5001: // +50 Spell Power + 20 Spirit
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), ENCHANT_LEG_BRILLIANT_SPELLTHREAD);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 5002: // +50 Spell Power + 30 Stamina
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), ENCHANT_LEG_SAPPHIRE_SPELLTHREAD);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 5003: // +40 Reslience + 28 Stamina
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), ENCHANT_LEG_EARTHEN);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 5004: // +55 Stamina + 22 Agility
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_LEGS), ENCHANT_LEG_FROSTHIDE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;


		case 6: // BRACERS
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Insira seu wrist por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WRISTS)
			{
		if (player->HasSkill(SKILL_LEATHERWORKING) && player->GetSkillValue(SKILL_LEATHERWORKING) == 450)
		 {
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +130 Attack Power",							GOSSIP_SENDER_MAIN, 6000);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +102 Stamina",								GOSSIP_SENDER_MAIN, 6001);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +76 Spell Power",							GOSSIP_SENDER_MAIN, 6002);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +70 Arcane Resistance",						GOSSIP_SENDER_MAIN, 6003);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +70 Fire Resistance",						GOSSIP_SENDER_MAIN, 6004);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +70 Frost Resistance",						GOSSIP_SENDER_MAIN, 6005);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +70 Nature Resistance",						GOSSIP_SENDER_MAIN, 6006);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +70 Shadow Resistance",						GOSSIP_SENDER_MAIN, 6007);
		 }
		if (player->HasSkill(SKILL_BLACKSMITHING) && player->GetSkillValue(SKILL_BLACKSMITHING) == 450)
		 {
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Socket Bracer",								GOSSIP_SENDER_MAIN, 6008);
		 }
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +50 Attack Power",							GOSSIP_SENDER_MAIN, 6009);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +40 Stamina",								GOSSIP_SENDER_MAIN, 6010);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +30 Spell Power",							GOSSIP_SENDER_MAIN, 6011);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +18 Spirit",									GOSSIP_SENDER_MAIN, 6012);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +15 Expertise",								GOSSIP_SENDER_MAIN, 6013);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +6 All Stats",								GOSSIP_SENDER_MAIN, 6014);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",					GOSSIP_SENDER_MAIN, 300);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			}

			else
			{
				player->GetSession()->SendAreaTriggerMessage("Insira seu wrist por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
			}
		}
		return true;




		case 6000: // +130 Attack Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_ATTACK);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 6001: // +102 Stamina
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_STAMINA);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 6002: // +76 Spell Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_SPELLPOWER);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 6003: // +70 Arcane Resistance
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_ARCANE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 6004: // +70 Fire Resistance
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_FIRE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 6005: // +70 Frost Resistance
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_FROST);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 6006: // +70 Nature Resistance
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_NATURE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 6007: // +70 Shadow Resistance
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_FURL_SHADOW);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 6008: // Socket Bracer
			AdvancedEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), PRISMATIC_ENCHANTMENT_SLOT, ENCHANT_BRACER_SOCKET_BRACER);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 6009: // +50 Attack Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_GREATER_ASSUALT);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 6010: // +40 Stamina
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_MAJOR_STAMINA);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 6011: // +30 Spell Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_SUPERIOR_SP);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 6012: // +18 Spirit
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_MAJOR_SPIRT);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 6013: // +15 Expertise
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_EXPERTISE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 6014: // +6 All Stats
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WRISTS), ENCHANT_BRACERS_GREATER_STATS);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;


		case 7: // WAIST
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Insira seu waist por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WAIST)
			{
		if (player->HasSkill(SKILL_ENGINEERING) && player->GetSkillValue(SKILL_ENGINEERING) == 450) // ENGINE
		 {
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Frag Belt",								GOSSIP_SENDER_MAIN, 7000);
		 }
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Eternal Belt Buckle",					GOSSIP_SENDER_MAIN, 7001);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",				GOSSIP_SENDER_MAIN, 300);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			}

			else
			{
				player->GetSession()->SendAreaTriggerMessage("Insira seu waist por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
			}
		}
		return true;




		case 7000: // Frag Belt
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), ENCHANT_BELT_FRAG_BELT);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 7001: // Eternal Belt Buckle
			AdvancedEnchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_WAIST), PRISMATIC_ENCHANTMENT_SLOT, ENCHANT_BELT_ETERNAL_BELT_BUCKLE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;


		case 8: // FEET
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Insira sua feet por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_FEET)
			{
		if (player->HasSkill(SKILL_ENGINEERING) && player->GetSkillValue(SKILL_ENGINEERING) == 450) // ENGINE
		 {
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Nitro Boots",							GOSSIP_SENDER_MAIN, 8000);
		 }
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +32 Attack Power",						GOSSIP_SENDER_MAIN, 8001);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +22 Stamina",							GOSSIP_SENDER_MAIN, 8002);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +15 Stamina +Movement Speed",			GOSSIP_SENDER_MAIN, 8003);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +16 Agility",							GOSSIP_SENDER_MAIN, 8004);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +18 Spirit",								GOSSIP_SENDER_MAIN, 8005);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +12 Hit Rating +Crit Rating",			GOSSIP_SENDER_MAIN, 8006);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +7 Mp5 +Health every 5 Seconds",			GOSSIP_SENDER_MAIN, 8007);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",				GOSSIP_SENDER_MAIN, 300);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			}

			else
			{
				player->GetSession()->SendAreaTriggerMessage("Insira sua feet por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
			}
		}
		return true;



		case 8000: // Nitro Boots
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_NITRO_BOOTS);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 8001: // +32 Attack Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_GREATER_ASSULT);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 8002: // +22 Stamina
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_GREATER_FORTITUDE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 8003: // +15 Stamina +Movement Speed"
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_TUSKARS_VITLIATY);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 8004: // +16 Agility
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_SUPERIOR_AGILITY);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 8005: // +18 Spirit
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_GREATER_SPIRIT);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 8006: // +12 Hit Rating +Crit Rating
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_ICEWALKER);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 8007: // +7 Mp5 +Health every 5 Seconds
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FEET), ENCHANT_BOOTS_GREATER_VITALITY);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;


		case 9: // CLOAK
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Insira o cloak por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_CLOAK)
			{
		if (player->HasSkill(SKILL_TAILORING) && player->GetSkillValue(SKILL_TAILORING) == 450)
		 {
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Swordguard +400 Attack Power",				GOSSIP_SENDER_MAIN, 9000);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Darkglow +400 Mana",							GOSSIP_SENDER_MAIN, 9001);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Lightweave +295 Spell Power",				GOSSIP_SENDER_MAIN, 9002);
		 }
		if (player->HasSkill(SKILL_ENGINEERING) && player->GetSkillValue(SKILL_ENGINEERING) == 450) // ENGINE
		 {
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Flexweave Underlay",							GOSSIP_SENDER_MAIN, 9003);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Springy Arachnoweave",						GOSSIP_SENDER_MAIN, 9004);
		 }
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +225 Armor",									GOSSIP_SENDER_MAIN, 9005);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +23 Haste",									GOSSIP_SENDER_MAIN, 9006);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +22 Agility",								GOSSIP_SENDER_MAIN, 9007);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +16 Defense",								GOSSIP_SENDER_MAIN, 9008);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +10 Agility +Stealth Increase",				GOSSIP_SENDER_MAIN, 9009);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +10 Spirit +Reduce threat",					GOSSIP_SENDER_MAIN, 9010);
			player->ADD_GOSSIP_ITEM(10, "|TInterface/PaperDollInfoFrame/UI-GearManager-Undo:30:30:-14|tVoltar",						GOSSIP_SENDER_MAIN, 300);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			}

			else
			{
				player->GetSession()->SendAreaTriggerMessage("Insira o cloak por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
			}
		}
		return true;




		case 9000: // Swordguard +400 Attack Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_SWORDGUARD_EMBROIDERY);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 9001: // Darkglow +400 Mana
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_DARKGLOW_EMBROIDERY);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 9002: // Lightweave +295 Spell Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_LIGHTWEAVE_EMBROIDERY);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 9003: // Flexweave Underlay
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_FLEXWEAVE_UNDERLAY);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 9004: // Springy Arachnoweave
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_SPRINGY_ARACHNOWEAVE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 9005: // +225 Armor
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_MIGHTY_ARMOR);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 9006: // +23 Haste
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_GREATER_SPEED);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 9007: // +22 Agility
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_MAJOR_AGILITY);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 9008: // +16 Defense
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_TITANWEAVE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 9009: // +10 Agility +Stealth Increase
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_SHADOW_ARMOR);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 9010: // +10 Spirit +Reduce threat
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_BACK), ENCHANT_CLOAK_WISDOM);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;





		case 10: // RING 1
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Insira o ring por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_FINGER)
			{
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +40 Attack Power",				GOSSIP_SENDER_MAIN, 1100);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +30 Stamina",					GOSSIP_SENDER_MAIN, 1101);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +23 Spell Power",				GOSSIP_SENDER_MAIN, 1102);
			player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",		GOSSIP_SENDER_MAIN, 300);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			}

			else
			{
				player->GetSession()->SendAreaTriggerMessage("Insira o ring por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
			}
		}
		return true;





		case 1100: // +40 Attack Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), ENCHANT_RING_ASSULT);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1101: // +30 Stamina
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), ENCHANT_RING_STAMINA);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1102: // +23 Spell Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER1), ENCHANT_RING_GREATER_SP);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;


		case 11: // RING 2
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Inserir o ring por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_FINGER)
			{
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +40 Attack Power", GOSSIP_SENDER_MAIN, 1110);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +30 Stamina", GOSSIP_SENDER_MAIN, 1111);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +23 Spell Power", GOSSIP_SENDER_MAIN, 1112);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar", GOSSIP_SENDER_MAIN, 300);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			}

			else
			{
				player->GetSession()->SendAreaTriggerMessage("Inserir o ring por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
			}
		}
			return true;

		case 1110: // +40 Attack Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), ENCHANT_RING_ASSULT);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1111: // +30 Stamina
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), ENCHANT_RING_STAMINA);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1112: // +23 Spell Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_FINGER2), ENCHANT_RING_GREATER_SP);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;




		case 12: // MAIN HAND

		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

			if (!item)
			{
				player->GetSession()->SendNotification("Insira Main-Hand por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONMAINHAND)
			{
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Battlemaster",				GOSSIP_SENDER_MAIN, 1200);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Berserking",					GOSSIP_SENDER_MAIN, 1201);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Black Magic",				GOSSIP_SENDER_MAIN, 1202);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Blood Draining",				GOSSIP_SENDER_MAIN, 1203);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Blade Warding",				GOSSIP_SENDER_MAIN, 1204);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Executioner",				GOSSIP_SENDER_MAIN, 1205);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Icebreaker",					GOSSIP_SENDER_MAIN, 1206);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Lifeward",					GOSSIP_SENDER_MAIN, 1207);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Mongoose",					GOSSIP_SENDER_MAIN, 1208);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Titanium Weapon Chain",		GOSSIP_SENDER_MAIN, 1209);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +65 Attack Power",			GOSSIP_SENDER_MAIN, 1212);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +63 Spell Power",			GOSSIP_SENDER_MAIN, 1213);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +50 Stamina",				GOSSIP_SENDER_MAIN, 1214);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +45 Spirit",					GOSSIP_SENDER_MAIN, 1215);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +26 Agility",				GOSSIP_SENDER_MAIN, 1216);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +25 Hit Rating +25 Crit",	GOSSIP_SENDER_MAIN, 1217);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",	GOSSIP_SENDER_MAIN, 300);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				return true;
			}
		}

			// ONE HAND
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

			if (!item)
			{
				player->GetSession()->SendNotification("One-Hand nao esta equipada!", LANG_UNIVERSAL);
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPON)
			{
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Battlemaster",				GOSSIP_SENDER_MAIN, 1200);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Berserking",					GOSSIP_SENDER_MAIN, 1201);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Black Magic",				GOSSIP_SENDER_MAIN, 1202);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Blood Draining",				GOSSIP_SENDER_MAIN, 1203);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Blade Warding",				GOSSIP_SENDER_MAIN, 1204);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Executioner",				GOSSIP_SENDER_MAIN, 1205);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Icebreaker",					GOSSIP_SENDER_MAIN, 1206);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Lifeward",					GOSSIP_SENDER_MAIN, 1207);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Mongoose",					GOSSIP_SENDER_MAIN, 1208);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Titanium Weapon Chain",		GOSSIP_SENDER_MAIN, 1209);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +65 Attack Power",			GOSSIP_SENDER_MAIN, 1212);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +63 Spell Power",			GOSSIP_SENDER_MAIN, 1213);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +50 Stamina",				GOSSIP_SENDER_MAIN, 1214);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +45 Spirit",					GOSSIP_SENDER_MAIN, 1215);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +26 Agility",				GOSSIP_SENDER_MAIN, 1216);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +25 Hit Rating +25 Crit",	GOSSIP_SENDER_MAIN, 1217);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",	GOSSIP_SENDER_MAIN, 300);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				return true;
			}
		}

		// 2HAND
		
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

			if (!item)
			{
				player->GetSession()->SendNotification("Two-Hand nao esta equipada!", LANG_UNIVERSAL);
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_2HWEAPON)
			{
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Battlemaster",				GOSSIP_SENDER_MAIN, 1200);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Berserking",					GOSSIP_SENDER_MAIN, 1201);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Black Magic",				GOSSIP_SENDER_MAIN, 1202);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Blood Draining",				GOSSIP_SENDER_MAIN, 1203);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Blade Warding",				GOSSIP_SENDER_MAIN, 1204);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Executioner",				GOSSIP_SENDER_MAIN, 1205);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Icebreaker",					GOSSIP_SENDER_MAIN, 1206);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Lifeward",					GOSSIP_SENDER_MAIN, 1207);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Mongoose",					GOSSIP_SENDER_MAIN, 1208);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Titanium Weapon Chain",		GOSSIP_SENDER_MAIN, 1209);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +110 Attack Power",			GOSSIP_SENDER_MAIN, 1210);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +81 Spellpower",				GOSSIP_SENDER_MAIN, 1211);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +65 Attack Power",			GOSSIP_SENDER_MAIN, 1212);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +63 Spell Power",			GOSSIP_SENDER_MAIN, 1213);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +50 Stamina",				GOSSIP_SENDER_MAIN, 1214);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +45 Spirit",					GOSSIP_SENDER_MAIN, 1215);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +26 Agility",				GOSSIP_SENDER_MAIN, 1216);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +25 Hit Rating +25 Crit",	GOSSIP_SENDER_MAIN, 1217);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",	GOSSIP_SENDER_MAIN, 300);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				return true;
			}
		}
		break;

		case 1200: // Battlemaster
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_BATTLEMASTER);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1201: // Berserking
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_BERSERKING);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1202: // Black Magic
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_BLACK_MAGIC);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1203: // Blood Draining
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_BLOOD_DRAINING);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1204: // Blade Warding
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_BLADE_WARD);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1205: // Executioner
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_EXECUTIONER);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1206: // Icebreaker
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_ICEBREAKER);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1207: // Lifeward
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_LIFEWARD);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1208: // Mongoose
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_2WEP_MONGOOSE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1209: // Titanium Weapon Chain
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_TITANIUM_CHAIN);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1210: // +110 Attack Power
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Two-Hand nao esta equipada.");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_2HWEAPON)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_2WEP_MASSACRE);
				player->CastSpell(player, 14867);
				OnGossipHello(player, creature);
			}
		}
			break;

		case 1211: // +81 Spellpower
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Two-Hand nao esta equipada.");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_2HWEAPON)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_2WEP_GREATER_SPELL_POWER);
				player->CastSpell(player, 14867);
				OnGossipHello(player, creature);
			}
		}
			break;

		case 1212: // +65 Attack Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_POTENCY);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1213: // +63 Spell Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_MIGHTY_SPELL_POWER);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1214: // +50 Stamina
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_TITANGUARD);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1215: // +45 Spirit
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_SPIRIT);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1216: // +26 Agility
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_AGILITY_1H);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1217: // +25 Hit Rating +25 Crit
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND), ENCHANT_WEP_ACCURACY);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

			
		case 13: // OFF HAND
			// OFF HAND
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendNotification("Off-Hand nao esta equipada!", LANG_UNIVERSAL);
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPONOFFHAND)
			{
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Battlemaster",				GOSSIP_SENDER_MAIN, 1300);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Berserking",					GOSSIP_SENDER_MAIN, 1301);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Blood Draining",				GOSSIP_SENDER_MAIN, 1303);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Blade Warding",				GOSSIP_SENDER_MAIN, 1304);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Executioner",				GOSSIP_SENDER_MAIN, 1305);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Icebreaker",					GOSSIP_SENDER_MAIN, 1306);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Lifeward",					GOSSIP_SENDER_MAIN, 1307);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Mongoose",					GOSSIP_SENDER_MAIN, 1308);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Titanium Weapon Chain",		GOSSIP_SENDER_MAIN, 1309);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +65 Attack Power",			GOSSIP_SENDER_MAIN, 1312);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +63 Spell Power",			GOSSIP_SENDER_MAIN, 1313);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +50 Stamina",				GOSSIP_SENDER_MAIN, 1314);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +45 Spirit",					GOSSIP_SENDER_MAIN, 1315);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +26 Agility",				GOSSIP_SENDER_MAIN, 1316);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +25 Hit Rating +25 Crit",	GOSSIP_SENDER_MAIN, 1317);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",	GOSSIP_SENDER_MAIN, 300);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				return true;
			}
		}
		
		// ONE HAND

		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendNotification("One-Hand nao esta equipada!", LANG_UNIVERSAL);
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_WEAPON)
			{
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Battlemaster",				GOSSIP_SENDER_MAIN, 1300);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Berserking",					GOSSIP_SENDER_MAIN, 1301);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Blood Draining",				GOSSIP_SENDER_MAIN, 1303);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Blade Warding",				GOSSIP_SENDER_MAIN, 1304);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Executioner",				GOSSIP_SENDER_MAIN, 1305);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Icebreaker",					GOSSIP_SENDER_MAIN, 1306);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Lifeward",					GOSSIP_SENDER_MAIN, 1307);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Mongoose",					GOSSIP_SENDER_MAIN, 1308);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t Titanium Weapon Chain",		GOSSIP_SENDER_MAIN, 1309);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +65 Attack Power",			GOSSIP_SENDER_MAIN, 1312);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +63 Spell Power",			GOSSIP_SENDER_MAIN, 1313);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +50 Stamina",				GOSSIP_SENDER_MAIN, 1314);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +45 Spirit",					GOSSIP_SENDER_MAIN, 1315);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +26 Agility",				GOSSIP_SENDER_MAIN, 1316);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +25 Hit Rating +25 Crit",	GOSSIP_SENDER_MAIN, 1317);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",	GOSSIP_SENDER_MAIN, 300);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				return false;
			}
		}

		// SHIELD

		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendNotification("Shield nao esta equipada!", LANG_UNIVERSAL);
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +81 Block & -50% Disarm",			GOSSIP_SENDER_MAIN, 1320);
				player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +36 Block Value",					GOSSIP_SENDER_MAIN, 1321);
				player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +25 Intellect",					GOSSIP_SENDER_MAIN, 1322);
				player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +20 Defense Rating",				GOSSIP_SENDER_MAIN, 1323);
				player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +18 Stamina",						GOSSIP_SENDER_MAIN, 1324);
				player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +15 Shield Block Rating",			GOSSIP_SENDER_MAIN, 1325);
				player->ADD_GOSSIP_ITEM(1, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +12 Resilience",					GOSSIP_SENDER_MAIN, 1326);		
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar", GOSSIP_SENDER_MAIN, 300);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				return true;
			}
		}

		break;

		case 1300: // Battlemaster
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_BATTLEMASTER);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1301: // Berserking
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_BERSERKING);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;


		case 1303: // Blood Draining
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_BLOOD_DRAINING);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1304: // Blade Warding
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_BLADE_WARD);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1305: // Executioner
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_EXECUTIONER);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1306: // Icebreaker
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_ICEBREAKER);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1307: // Lifeward
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_LIFEWARD);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1308: // Mongoose
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_2WEP_MONGOOSE);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1309: // Titanium Weapon Chain
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_TITANIUM_CHAIN);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1312: // +65 Attack Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_POTENCY);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1313: // +63 Spell Power
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_MIGHTY_SPELL_POWER);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1314: // +50 Stamina
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_TITANGUARD);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1315: // +45 Spirit
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_SPIRIT);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1316: // +26 Agility
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_AGILITY_1H);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		case 1317: // +25 Hit Rating +25 Crit
			Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_WEP_ACCURACY);
			player->CastSpell(player, 14867);
			OnGossipHello(player, creature);
			break;

		// SHIELD
		
		case 1320: // +81 Block & -50% Disarm 
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Shield nao esta equipado.");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_TITANIUM_PLATING);
				player->CastSpell(player, 14867);
				OnGossipHello(player, creature);
			}
		}
			break;

		case 1321: // +36 Block Value
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Shield nao esta equipado.");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_TOUGHSHIELD);
				player->CastSpell(player, 14867);
				OnGossipHello(player, creature);
			}
		}
			break;

		case 1322: // +25 Intelect
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Shield nao esta equipado.");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_INTELLECT);
				player->CastSpell(player, 14867);
				OnGossipHello(player, creature);
			}
		}
			break;

		case 1323: // +20 Defense Rating
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Shield nao esta equipado.");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_DEFENSE);
				player->CastSpell(player, 14867);
				OnGossipHello(player, creature);
			}
		}
			break;

		case 1324: // +18 Stamina
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Shield nao esta equipado.");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_STAMINA);
				player->CastSpell(player, 14867);
				OnGossipHello(player, creature);
			}
		}
			break;

		case 1325: // +15 Shield Block Rating
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Shield nao esta equipado.");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_BLOCK);
				player->CastSpell(player, 14867);
				OnGossipHello(player, creature);
			}
		}
		break;

		case 1326: // +12 Resilience
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Shield nao esta equipado.");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_SHIELD)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND), ENCHANT_SHIELD_RESILIENCE);
				player->CastSpell(player, 14867);
				OnGossipHello(player, creature);
			}
		}
			break;


		case 14: // RANGED
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);

			if (!item)
			{
				player->GetSession()->SendNotification("Insira sua ranged por favor!", LANG_UNIVERSAL);
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_RANGED)
			{
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +40 Ranged Critical Strike",						GOSSIP_SENDER_MAIN, 1400);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\icons\\INV_Scroll_03:30:30:-14|t +40 Ranged Haste Rating",						GOSSIP_SENDER_MAIN, 1401);
				player->ADD_GOSSIP_ITEM(10, "|TInterface\\PaperDollInfoFrame\\UI-GearManager-Undo:30:30:-14|tVoltar",						GOSSIP_SENDER_MAIN, 300);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			}

			else
			{
				player->GetSession()->SendAreaTriggerMessage("Insira sua ranged por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
			}
		}
		return true;

		case 1400: // +40 Ranged Critical Strike
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Insira sua ranged por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_RANGED)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED), ENCHANT_RANGED_HEARTSEEKER_SCOPE);
				player->CastSpell(player, 14867);
				OnGossipHello(player, creature);
			}

			else
			{
				player->GetSession()->SendAreaTriggerMessage("Insira sua ranged por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
			}
		}
		break;
		

		case 1401: // +40 Ranged Haste Rating
		{
			item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);

			if (!item)
			{
				player->GetSession()->SendAreaTriggerMessage("Insira sua ranged por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
				return false;
			}

			if (item->GetTemplate()->InventoryType == INVTYPE_RANGED)
			{
				Enchant(player, player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED), ENCHANT_RANGED_SUN_SCOPE);
				player->CastSpell(player, 14867);
				OnGossipHello(player, creature);
			}

			else
			{
				player->GetSession()->SendAreaTriggerMessage("Insira sua ranged por favor!");
				player->CastSpell(player, 27123);
				OnGossipHello(player, creature);
			}
		}
		break;

		case 300: // Voltar
			OnGossipHello(player, creature);
			break;

		}
		return true;
	}
};

void AddSC_MTG_Npc_Enchants()
{
	new MTG_Npc_Enchants();
}