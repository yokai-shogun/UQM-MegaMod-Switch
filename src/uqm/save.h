/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef UQM_SAVE_H_
#define UQM_SAVE_H_

#include "sis.h" // SUMMARY_DESC includes SIS_STATE in it
#include "globdata.h"
#include "libs/compiler.h"

#if defined(__cplusplus)
extern "C" {
#endif

// XXX: Theoretically, a player can have 17 devices on board without
//   cheating. We only provide
//   room for 16 below, which is not really a problem since this
//   is only used for displaying savegame summaries. There is also
//   room for only 16 devices on screen.
#define MAX_EXCLUSIVE_DEVICES 16
#define SAVE_NAME_SIZE 64

// The savefile tag numbers.
#define SAVEFILE_TAG     0x01534d55 // "UMS\x01": UQM Save version 1
#define MEGA_TAG		 0x4147454D // "MEGA": MegaMod Save version 2
#define SUMMARY_TAG      0x6d6d7553 // "Summ": Summary. Must be first!
#define GLOBAL_STATE_TAG 0x74536c47 // "GlSt": Global State. Must be 2nd!
#define GAME_STATE_TAG   0x74536d47 // "GmSt": Game State Bits. Must be 3rd!
#define EVENTS_TAG       0x73747645 // "Evts": Events
#define ENCOUNTERS_TAG   0x74636e45 // "Enct": Encounters
#define RACE_Q_TAG       0x51636152 // "RacQ": avail_race_q
#define IP_GRP_Q_TAG     0x51704749 // "IGpQ": ip_group_q
#define NPC_SHIP_Q_TAG   0x5163704e // "NpcQ": npc_built_ship_q
#define SHIP_Q_TAG       0x51706853 // "ShpQ": built_ship_q
#define STAR_TAG         0x72617453 // "Star": STAR_DESC
#define SCAN_TAG         0x6e616353 // "Scan": Scan Masks (stuff picked up)
#define BATTLE_GROUP_TAG 0x70477442 // "BtGp": Battle Group definition
#define GROUP_LIST_TAG   0x73707247 // "Grps": Group List

typedef struct
{
	SIS_STATE SS;
	BYTE Activity;
	BYTE Flags;
	BYTE day_index, month_index;
	COUNT year_index;
	BYTE MCreditLo, MCreditHi;
	BYTE NumShips, NumDevices;
	BYTE ShipList[MAX_BUILT_SHIPS];
	BYTE DeviceList[MAX_EXCLUSIVE_DEVICES];
	UNICODE SaveName[SAVE_NAME_SIZE];
	UNICODE SaveNameChecker[SAVE_CHECKER_SIZE];
	UNICODE LegacySaveName[LEGACY_SAVE_NAME_SIZE];
	BYTE res_factor;
} SUMMARY_DESC;

extern ACTIVITY NextActivity;

extern BOOLEAN LoadGame (COUNT which_game, SUMMARY_DESC* summary_desc, uio_Stream* in_fp, BOOLEAN try_core);
extern BOOLEAN LoadLegacyGame (COUNT which_game, SUMMARY_DESC *SummPtr, BOOLEAN try_vanilla);

extern void SaveProblem (void);
extern BOOLEAN SaveGame (COUNT which_game, SUMMARY_DESC *summary_desc, const char *name);

extern const GameStateBitMap gameStateBitMap[];

static const GameStateBitMap coreGameStateBitMap[] = {
	{ "SHOFIXTI_VISITS", 3 },
	{ "SHOFIXTI_STACK1", 2 },
	{ "SHOFIXTI_STACK2", 3 },
	{ "SHOFIXTI_STACK3", 2 },
	{ "SHOFIXTI_KIA", 1 },
	{ "SHOFIXTI_BRO_KIA", 1 },
	{ "SHOFIXTI_RECRUITED", 1 },
	{ "SHOFIXTI_MAIDENS", 1 },
	{ "MAIDENS_ON_SHIP", 1 },
	{ "BATTLE_SEGUE", 1 },
	{ "PLANETARY_LANDING", 1 },
	{ "PLANETARY_CHANGE", 1 },
	{ "SPATHI_VISITS", 3 },
	{ "SPATHI_HOME_VISITS", 3 },
	{ "FOUND_PLUTO_SPATHI", 2 },
	{ "SPATHI_SHIELDED_SELVES", 1 },
	{ "SPATHI_CREATURES_EXAMINED", 1 },
	{ "SPATHI_CREATURES_ELIMINATED", 1 },
	{ "UMGAH_BROADCASTERS", 1 },
	{ "SPATHI_MANNER", 2 },
	{ "SPATHI_QUEST", 1 },
	{ "LIED_ABOUT_CREATURES", 2 },
	{ "SPATHI_PARTY", 1 },
	{ "KNOW_SPATHI_PASSWORD", 1 },
	{ "ILWRATH_HOME_VISITS", 3 },
	{ "ILWRATH_CHMMR_VISITS", 1 },
	{ "ARILOU_SPACE", 1 },
	{ "ARILOU_SPACE_SIDE", 2 },
	{ "ARILOU_SPACE_COUNTER", 4 },
	{ "LANDER_SHIELDS", 4 },
	{ "MET_MELNORME", 1 },
	{ "MELNORME_RESCUE_REFUSED", 1 },
	{ "MELNORME_RESCUE_COUNT", 3 },
	{ "TRADED_WITH_MELNORME", 1 },
	{ "WHY_MELNORME_PURPLE", 1 },
	{ "MELNORME_CREDIT0", 8 },
	{ "MELNORME_CREDIT1", 8 },
	{ "MELNORME_BUSINESS_COUNT", 2 },
	{ "MELNORME_YACK_STACK0", 2 },
	{ "MELNORME_YACK_STACK1", 2 },
	{ "MELNORME_YACK_STACK2", 4 },
	{ "MELNORME_YACK_STACK3", 3 },
	{ "MELNORME_YACK_STACK4", 2 },
	{ "WHY_MELNORME_BLUE", 1 },
	{ "MELNORME_ANGER", 2 },
	{ "MELNORME_MIFFED_COUNT", 2 },
	{ "MELNORME_PISSED_COUNT", 2 },
	{ "MELNORME_HATE_COUNT", 2 },
	{ "PROBE_MESSAGE_DELIVERED", 1 },
	{ "PROBE_ILWRATH_ENCOUNTER", 1 },
	{ "STARBASE_AVAILABLE", 1 },
	{ "STARBASE_VISITED", 1 },
	{ "RADIOACTIVES_PROVIDED", 1 },
	{ "LANDERS_LOST", 1 },
	{ "GIVEN_FUEL_BEFORE", 1 },
	{ "AWARE_OF_SAMATRA", 1 },
	{ "YEHAT_CAVALRY_ARRIVED", 1 },
	{ "URQUAN_MESSED_UP", 1 },
	{ "MOONBASE_DESTROYED", 1 },
	{ "WILL_DESTROY_BASE", 1 },
	{ "WIMBLIS_TRIDENT_ON_SHIP", 1 },
	{ "GLOWING_ROD_ON_SHIP", 1 },
	{ "KOHR_AH_KILLED_ALL", 1 },
	{ "STARBASE_YACK_STACK1", 1 },
	{ "DISCUSSED_PORTAL_SPAWNER", 1 },
	{ "DISCUSSED_TALKING_PET", 1 },
	{ "DISCUSSED_UTWIG_BOMB", 1 },
	{ "DISCUSSED_SUN_EFFICIENCY", 1 },
	{ "DISCUSSED_ROSY_SPHERE", 1 },
	{ "DISCUSSED_AQUA_HELIX", 1 },
	{ "DISCUSSED_CLEAR_SPINDLE", 1 },
	{ "DISCUSSED_ULTRON", 1 },
	{ "DISCUSSED_MAIDENS", 1 },
	{ "DISCUSSED_UMGAH_HYPERWAVE", 1 },
	{ "DISCUSSED_BURVIX_HYPERWAVE", 1 },
	{ "SYREEN_WANT_PROOF", 1 },
	{ "PLAYER_HAVING_SEX", 1 },
	{ "MET_ARILOU", 1 },
	{ "DISCUSSED_TAALO_PROTECTOR", 1 },
	{ "DISCUSSED_EGG_CASING0", 1 },
	{ "DISCUSSED_EGG_CASING1", 1 },
	{ "DISCUSSED_EGG_CASING2", 1 },
	{ "DISCUSSED_SYREEN_SHUTTLE", 1 },
	{ "DISCUSSED_VUX_BEAST", 1 },
	{ "DISCUSSED_DESTRUCT_CODE", 1 },
	{ "DISCUSSED_URQUAN_WARP", 1 },
	{ "DISCUSSED_ARTIFACT_2", 1 },
	{ "DISCUSSED_ARTIFACT_3", 1 },
	{ "ATTACKED_DRUUGE", 1 },
	{ "NEW_ALLIANCE_NAME", 2 },
	{ "PORTAL_COUNTER", 4 },
	{ "BURVIXESE_BROADCASTERS", 1 },
	{ "BURV_BROADCASTERS_ON_SHIP", 1 },
	{ "UTWIG_BOMB", 1 },
	{ "UTWIG_BOMB_ON_SHIP", 1 },
	{ "AQUA_HELIX", 1 },
	{ "AQUA_HELIX_ON_SHIP", 1 },
	{ "SUN_DEVICE", 1 },
	{ "SUN_DEVICE_ON_SHIP", 1 },
	{ "TAALO_PROTECTOR", 1 },
	{ "TAALO_PROTECTOR_ON_SHIP", 1 },
	{ "SHIP_VAULT_UNLOCKED", 1 },
	{ "SYREEN_SHUTTLE", 1 },
	{ "PORTAL_KEY", 1 },
	{ "PORTAL_KEY_ON_SHIP", 1 },
	{ "VUX_BEAST", 1 },
	{ "VUX_BEAST_ON_SHIP", 1 },
	{ "TALKING_PET", 1 },
	{ "TALKING_PET_ON_SHIP", 1 },
	{ "MOONBASE_ON_SHIP", 1 },
	{ "KOHR_AH_FRENZY", 1 },
	{ "KOHR_AH_VISITS", 2 },
	{ "KOHR_AH_BYES", 1 },
	{ "SLYLANDRO_HOME_VISITS", 3 },
	{ "DESTRUCT_CODE_ON_SHIP", 1 },
	{ "ILWRATH_VISITS", 3 },
	{ "ILWRATH_DECEIVED", 1 },
	{ "FLAGSHIP_CLOAKED", 1 },
	{ "MYCON_VISITS", 3 },
	{ "MYCON_HOME_VISITS", 3 },
	{ "MYCON_AMBUSH", 1 },
	{ "MYCON_FELL_FOR_AMBUSH", 1 },
	{ "GLOBAL_FLAGS_AND_DATA", 8 },
	{ "ORZ_VISITS", 3 },
	{ "TAALO_VISITS", 3 },
	{ "ORZ_MANNER", 2 },
	{ "PROBE_EXHIBITED_BUG", 1 },
	{ "CLEAR_SPINDLE_ON_SHIP", 1 },
	{ "URQUAN_VISITS", 3 },
	{ "PLAYER_HYPNOTIZED", 1 },
	{ "VUX_VISITS", 3 },
	{ "VUX_HOME_VISITS", 3 },
	{ "ZEX_VISITS", 3 },
	{ "ZEX_IS_DEAD", 1 },
	{ "KNOW_ZEX_WANTS_MONSTER", 1 },
	{ "UTWIG_VISITS", 3 },
	{ "UTWIG_HOME_VISITS", 3 },
	{ "BOMB_VISITS", 3 },
	{ "ULTRON_CONDITION", 3 },
	{ "UTWIG_HAVE_ULTRON", 1 },
	{ "BOMB_UNPROTECTED", 1 },
	{ "TAALO_UNPROTECTED", 1 },
	{ "TALKING_PET_VISITS", 3 },
	{ "TALKING_PET_HOME_VISITS", 3 },
	{ "UMGAH_ZOMBIE_BLOBBIES", 1 },
	{ "KNOW_UMGAH_ZOMBIES", 1 },
	{ "ARILOU_VISITS", 3 },
	{ "ARILOU_HOME_VISITS", 3 },
	{ "KNOW_ARILOU_WANT_WRECK", 1 },
	{ "ARILOU_CHECKED_UMGAH", 2 },
	{ "PORTAL_SPAWNER", 1 },
	{ "PORTAL_SPAWNER_ON_SHIP", 1 },
	{ "UMGAH_VISITS", 3 },
	{ "UMGAH_HOME_VISITS", 3 },
	{ "MET_NORMAL_UMGAH", 1 },
	{ "SYREEN_HOME_VISITS", 3 },
	{ "SYREEN_SHUTTLE_ON_SHIP", 1 },
	{ "KNOW_SYREEN_VAULT", 1 },
	{ "EGG_CASE0_ON_SHIP", 1 },
	{ "SUN_DEVICE_UNGUARDED", 1 },
	{ "ROSY_SPHERE_ON_SHIP", 1 },
	{ "CHMMR_HOME_VISITS", 3 },
	{ "CHMMR_EMERGING", 1 },
	{ "CHMMR_UNLEASHED", 1 },
	{ "CHMMR_BOMB_STATE", 2 },
	{ "DRUUGE_DISCLAIMER", 1 },
	{ "YEHAT_VISITS", 3 },
	{ "YEHAT_REBEL_VISITS", 3 },
	{ "YEHAT_HOME_VISITS", 3 },
	{ "YEHAT_CIVIL_WAR", 1 },
	{ "YEHAT_ABSORBED_PKUNK", 1 },
	{ "YEHAT_SHIP_MONTH", 4 },
	{ "YEHAT_SHIP_DAY", 5 },
	{ "YEHAT_SHIP_YEAR", 5 },
	{ "CLEAR_SPINDLE", 1 },
	{ "PKUNK_VISITS", 3 },
	{ "PKUNK_HOME_VISITS", 3 },
	{ "PKUNK_SHIP_MONTH", 4 },
	{ "PKUNK_SHIP_DAY", 5 },
	{ "PKUNK_SHIP_YEAR", 5 },
	{ "PKUNK_MISSION", 3 },
	{ "SUPOX_VISITS", 3 },
	{ "SUPOX_HOME_VISITS", 3 },
	{ "THRADD_VISITS", 3 },
	{ "THRADD_HOME_VISITS", 3 },
	{ "HELIX_VISITS", 3 },
	{ "HELIX_UNPROTECTED", 1 },
	{ "THRADD_CULTURE", 2 },
	{ "THRADD_MISSION", 3 },
	{ "DRUUGE_VISITS", 3 },
	{ "DRUUGE_HOME_VISITS", 3 },
	{ "ROSY_SPHERE", 1 },
	{ "SCANNED_MAIDENS", 1 },
	{ "SCANNED_FRAGMENTS", 1 },
	{ "SCANNED_CASTER", 1 },
	{ "SCANNED_SPAWNER", 1 },
	{ "SCANNED_ULTRON", 1 },
	{ "ZOQFOT_INFO", 2 },
	{ "ZOQFOT_HOSTILE", 1 },
	{ "ZOQFOT_HOME_VISITS", 3 },
	{ "MET_ZOQFOT", 1 },
	{ "ZOQFOT_DISTRESS", 2 },
	{ "EGG_CASE1_ON_SHIP", 1 },
	{ "EGG_CASE2_ON_SHIP", 1 },
	{ "MYCON_SUN_VISITS", 3 },
	{ "ORZ_HOME_VISITS", 3 },
	{ "MELNORME_FUEL_PROCEDURE", 1 },
	{ "MELNORME_TECH_PROCEDURE", 1 },
	{ "MELNORME_INFO_PROCEDURE", 1 },
	{ "MELNORME_TECH_STACK", 4 },
	{ "MELNORME_EVENTS_INFO_STACK", 5 },
	{ "MELNORME_ALIEN_INFO_STACK", 5 },
	{ "MELNORME_HISTORY_INFO_STACK", 5 },
	{ "RAINBOW_WORLD0", 8 },
	{ "RAINBOW_WORLD1", 2 },
	{ "MELNORME_RAINBOW_COUNT", 4 },
	{ "USED_BROADCASTER", 1 },
	{ "BROADCASTER_RESPONSE", 1 },
	{ "IMPROVED_LANDER_SPEED", 1 },
	{ "IMPROVED_LANDER_CARGO", 1 },
	{ "IMPROVED_LANDER_SHOT", 1 },
	{ "MET_ORZ_BEFORE", 1 },
	{ "YEHAT_REBEL_TOLD_PKUNK", 1 },
	{ "PLAYER_HAD_SEX", 1 },
	{ "UMGAH_BROADCASTERS_ON_SHIP", 1 },
	{ "LIGHT_MINERAL_LOAD", 3 },
	{ "MEDIUM_MINERAL_LOAD", 3 },
	{ "HEAVY_MINERAL_LOAD", 3 },
	{ "STARBASE_BULLETS", 32 },
	{ "STARBASE_MONTH", 4 },
	{ "STARBASE_DAY", 5 },
	{ "CREW_SOLD_TO_DRUUGE0", 8 },
	{ "CREW_PURCHASED0", 8 },
	{ "CREW_PURCHASED1", 8 },
	{ "URQUAN_PROTECTING_SAMATRA", 1 },
	{ "THRADDASH_BODY_COUNT", 5 },
	{ "UTWIG_SUPOX_MISSION", 3 },
	{ "SPATHI_INFO", 3 },
	{ "ILWRATH_INFO", 2 },
	{ "ILWRATH_GODS_SPOKEN", 4 },
	{ "ILWRATH_WORSHIP", 2 },
	{ "ILWRATH_FIGHT_THRADDASH", 1 },
	{ "READY_TO_CONFUSE_URQUAN", 1 },
	{ "URQUAN_HYPNO_VISITS", 1 },
	{ "MENTIONED_PET_COMPULSION", 1 },
	{ "URQUAN_INFO", 2 },
	{ "KNOW_URQUAN_STORY", 2 },
	{ "MYCON_INFO", 4 },
	{ "MYCON_RAMBLE", 5 },
	{ "KNOW_ABOUT_SHATTERED", 2 },
	{ "MYCON_INSULTS", 3 },
	{ "MYCON_KNOW_AMBUSH", 1 },
	{ "SYREEN_INFO", 2 },
	{ "KNOW_SYREEN_WORLD_SHATTERED", 1 },
	{ "SYREEN_KNOW_ABOUT_MYCON", 1 },
	{ "TALKING_PET_INFO", 3 },
	{ "TALKING_PET_SUGGESTIONS", 3 },
	{ "LEARNED_TALKING_PET", 1 },
	{ "DNYARRI_LIED", 1 },
	{ "SHIP_TO_COMPEL", 1 },
	{ "ORZ_GENERAL_INFO", 2 },
	{ "ORZ_PERSONAL_INFO", 3 },
	{ "ORZ_ANDRO_STATE", 2 },
	{ "REFUSED_ORZ_ALLIANCE", 1 },
	{ "PKUNK_MANNER", 2 },
	{ "PKUNK_ON_THE_MOVE", 1 },
	{ "PKUNK_FLEET", 2 },
	{ "PKUNK_MIGRATE", 2 },
	{ "PKUNK_RETURN", 1 },
	{ "PKUNK_WORRY", 2 },
	{ "PKUNK_INFO", 3 },
	{ "PKUNK_WAR", 2 },
	{ "PKUNK_FORTUNE", 3 },
	{ "PKUNK_MIGRATE_VISITS", 3 },
	{ "PKUNK_REASONS", 4 },
	{ "PKUNK_SWITCH", 1 },
	{ "PKUNK_SENSE_VICTOR", 1 },
	{ "KOHR_AH_REASONS", 2 },
	{ "KOHR_AH_PLEAD", 2 },
	{ "KOHR_AH_INFO", 2 },
	{ "KNOW_KOHR_AH_STORY", 2 },
	{ "KOHR_AH_SENSES_EVIL", 1 },
	{ "URQUAN_SENSES_EVIL", 1 },
	{ "SLYLANDRO_PROBE_VISITS", 3 },
	{ "SLYLANDRO_PROBE_THREAT", 2 },
	{ "SLYLANDRO_PROBE_WRONG", 2 },
	{ "SLYLANDRO_PROBE_ID", 2 },
	{ "SLYLANDRO_PROBE_INFO", 2 },
	{ "SLYLANDRO_PROBE_EXIT", 2 },
	{ "UMGAH_HOSTILE", 1 },
	{ "UMGAH_EVIL_BLOBBIES", 1 },
	{ "UMGAH_MENTIONED_TRICKS", 2 },
	{ "BOMB_CARRIER", 1 },
	{ "THRADD_MANNER", 1 },
	{ "THRADD_INTRO", 2 },
	{ "THRADD_DEMEANOR", 3 },
	{ "THRADD_INFO", 2 },
	{ "THRADD_BODY_LEVEL", 2 },
	{ "THRADD_MISSION_VISITS", 1 },
	{ "THRADD_STACK_1", 3 },
	{ "THRADD_HOSTILE_STACK_2", 1 },
	{ "THRADD_HOSTILE_STACK_3", 1 },
	{ "THRADD_HOSTILE_STACK_4", 1 },
	{ "THRADD_HOSTILE_STACK_5", 1 },
	{ "CHMMR_STACK", 2 },
	{ "ARILOU_MANNER", 2 },
	{ "NO_PORTAL_VISITS", 1 },
	{ "ARILOU_STACK_1", 2 },
	{ "ARILOU_STACK_2", 1 },
	{ "ARILOU_STACK_3", 2 },
	{ "ARILOU_STACK_4", 1 },
	{ "ARILOU_STACK_5", 2 },
	{ "ARILOU_INFO", 2 },
	{ "ARILOU_HINTS", 2 },
	{ "DRUUGE_MANNER", 1 },
	{ "DRUUGE_SPACE_INFO", 2 },
	{ "DRUUGE_HOME_INFO", 2 },
	{ "DRUUGE_SALVAGE", 1 },
	{ "KNOW_DRUUGE_SLAVERS", 2 },
	{ "FRAGMENTS_BOUGHT", 2 },
	{ "ZEX_STACK_1", 2 },
	{ "ZEX_STACK_2", 2 },
	{ "ZEX_STACK_3", 2 },
	{ "VUX_INFO", 2 },
	{ "VUX_STACK_1", 4 },
	{ "VUX_STACK_2", 2 },
	{ "VUX_STACK_3", 2 },
	{ "VUX_STACK_4", 2 },
	{ "SHOFIXTI_STACK4", 2 },
	{ "YEHAT_REBEL_INFO", 3 },
	{ "YEHAT_ROYALIST_INFO", 1 },
	{ "YEHAT_ROYALIST_TOLD_PKUNK", 1 },
	{ "NO_YEHAT_ALLY_HOME", 1 },
	{ "NO_YEHAT_HELP_HOME", 1 },
	{ "NO_YEHAT_INFO", 1 },
	{ "NO_YEHAT_ALLY_SPACE", 2 },
	{ "NO_YEHAT_HELP_SPACE", 2 },
	{ "ZOQFOT_KNOW_MASK", 4 },
	{ "SUPOX_HOSTILE", 1 },
	{ "SUPOX_INFO", 1 },
	{ "SUPOX_WAR_NEWS", 2 },
	{ "SUPOX_ULTRON_HELP", 1 },
	{ "SUPOX_STACK1", 3 },
	{ "SUPOX_STACK2", 2 },
	{ "UTWIG_HOSTILE", 1 },
	{ "UTWIG_INFO", 1 },
	{ "UTWIG_WAR_NEWS", 2 },
	{ "UTWIG_STACK1", 3 },
	{ "UTWIG_STACK2", 2 },
	{ "BOMB_INFO", 1 },
	{ "BOMB_STACK1", 2 },
	{ "BOMB_STACK2", 2 },
	{ "SLYLANDRO_KNOW_BROKEN", 1 },
	{ "PLAYER_KNOWS_PROBE", 1 },
	{ "PLAYER_KNOWS_PROGRAM", 1 },
	{ "PLAYER_KNOWS_EFFECTS", 1 },
	{ "PLAYER_KNOWS_PRIORITY", 1 },
	{ "SLYLANDRO_STACK1", 3 },
	{ "SLYLANDRO_STACK2", 1 },
	{ "SLYLANDRO_STACK3", 2 },
	{ "SLYLANDRO_STACK4", 2 },
	{ "SLYLANDRO_STACK5", 1 },
	{ "SLYLANDRO_STACK6", 1 },
	{ "SLYLANDRO_STACK7", 2 },
	{ "SLYLANDRO_STACK8", 2 },
	{ "SLYLANDRO_STACK9", 2 },
	{ "SLYLANDRO_KNOW_EARTH", 1 },
	{ "SLYLANDRO_KNOW_EXPLORE", 1 },
	{ "SLYLANDRO_KNOW_GATHER", 1 },
	{ "SLYLANDRO_KNOW_URQUAN", 2 },
	{ "RECALL_VISITS", 2 },
	{ "SLYLANDRO_MULTIPLIER", 3 },
	{ "KNOW_SPATHI_QUEST", 1 },
	{ "KNOW_SPATHI_EVIL", 1 },
	{ "BATTLE_PLANET", 8 },
	{ "ESCAPE_COUNTER", 8 },
	{ "CREW_SOLD_TO_DRUUGE1", 8 },
	{ "PKUNK_DONE_WAR", 1 },
	{ "SYREEN_STACK0", 2 },
	{ "SYREEN_STACK1", 2 },
	{ "SYREEN_STACK2", 2 },
	{ "REFUSED_ULTRON_AT_BOMB", 1 },
	{ "NO_TRICK_AT_SUN", 1 },
	{ "SPATHI_STACK0", 2 },
	{ "SPATHI_STACK1", 1 },
	{ "SPATHI_STACK2", 1 },
	{ "ORZ_STACK0", 1 },
	{ "ORZ_STACK1", 1 },
	{ "SHOFIXTI_GRPOFFS", 32 },
	{ "ZOQFOT_GRPOFFS", 32 },
	{ "MELNORME0_GRPOFFS", 32 },
	{ "MELNORME1_GRPOFFS", 32 },
	{ "MELNORME2_GRPOFFS", 32 },
	{ "MELNORME3_GRPOFFS", 32 },
	{ "MELNORME4_GRPOFFS", 32 },
	{ "MELNORME5_GRPOFFS", 32 },
	{ "MELNORME6_GRPOFFS", 32 },
	{ "MELNORME7_GRPOFFS", 32 },
	{ "MELNORME8_GRPOFFS", 32 },
	{ "URQUAN_PROBE_GRPOFFS", 32 },
	{ "COLONY_GRPOFFS", 32 },
	{ "SAMATRA_GRPOFFS", 32 },
	{ NULL, 0 },
};

#if defined(__cplusplus)
}
#endif

#endif  /* UQM_SAVE_H_ */

