#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <Windows.h>
#include <format>
#include <cstdarg>

#include "Vector.h"
#include "FAIcons.h"
#include "clipper2/clipper.h"
#include "Geometry.h"

#define GET_A(c) ((c>>24)&0xFF)
#define GET_R(c) ((c>>16)&0xFF)
#define GET_G(c) ((c>>8)&0xFF)
#define GET_B(c) (c&255)

#define COLOR_ARGB(a,r,g,b) \
    ((Color)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

#define COLOR_RGBA(r,g,b, a) COLOR_ARGB(a, r, g, b)
#define COLOR_RGB(r,g,b) COLOR_ARGB(r, g, b, 255)

#pragma region GameObject
enum class CharacterHash : uint32_t
{
	Unknown = 0,
	Aatrox = 0x71097207,
	Ahri = 0xD4BD813E,
	Akali = 0x5F193A14,
	Akshan = 0xe4c3b8cc,
	Alistar = 0x7D004170,
	Amumu = 0xC60111F1,
	Anivia = 0xE6318952,
	Annie = 0xF111751D,
	Aphelios = 0x1FC9370D,
	Ashe = 0xDA1E294F,
	AurelionSol = 0x60C9D8ED,
	Azir = 0xDD919622,
	Bard = 0xFFD1E571,
	Belveth = 0x7FE328C,
	Blitzcrank = 0x9D92842A,
	Brand = 0xE8B74EC7,
	Braum = 0xE8BE5089,
	Caitlyn = 0x601C4B58,
	Camille = 0x6FF5CBEB,
	Cassiopeia = 0x205BB971,
	Chogath = 0x3094E898,
	Corki = 0xA96B4264,
	Darius = 0x52186A32,
	Diana = 0xCDD2B60F,
	DrMundo = 0xEE5915A3,
	Draven = 0xC42DA22C,
	Ekko = 0x904BF10A,
	Elise = 0xA1490494,
	Evelynn = 0x6089E761,
	Ezreal = 0x084DCF93,
	Fiddlesticks = 0x5783643F,
	Fiora = 0x5C944E1B,
	Fizz = 0xBDE5A683,
	Galio = 0x2AC6F678,
	Gangplank = 0x33D903EF,
	Garen = 0x2DB75281,
	Gnar = 0xEEC9BE98,
	Gragas = 0xFF4BDC63,
	Graves = 0x06B2C5EE,
	Gwen = 0xf33c4b19,
	Hecarim = 0xDEFD19BB,
	Heimerdinger = 0xD77595D9,
	Illaoi = 0x90FF0372,
	Irelia = 0xE83E3148,
	Ivern = 0x804569D4,
	Janna = 0xF78D33AA,
	JarvanIV = 0xB1F7EC95,
	Jax = 0x349383C1,
	Jayce = 0xFCECDB84,
	Jhin = 0x7771D5C3,
	Jinx = 0x77F4E689,
	Kaisa = 0x39084661,
	Kalista = 0xE0DB4F6D,
	Karma = 0x3D70D070,
	Karthus = 0x72C6D76E,
	Kassadin = 0x9A84477E,
	Katarina = 0x0381260D,
	Kayle = 0x40E23CBC,
	Kayn = 0xA2963DEB,
	Kennen = 0x454B9583,
	Khazix = 0xBA24D3E5,
	Kindred = 0x30E7F07D,
	Kled = 0xA7ECE380,
	KogMaw = 0xA65585E0,
	KSante = 0x9F6F3186,
	Leblanc = 0xEB2D6693,
	LeeSin = 0xBB34EE8C,
	Leona = 0x39FF4429,
	Lillia = 0xd23b335,
	Lissandra = 0x0884BF49,
	Lucian = 0x97F8A01C,
	Lulu = 0xDAE94192,
	Lux = 0x35A3A7AF,
	Malphite = 0xC1DCEAAA,
	Malzahar = 0x22D7D75A,
	Maokai = 0x8EFB7D38,
	MasterYi = 0xE5A429F2,
	MissFortune = 0x01E5A725,
	Mordekaiser = 0x166C307E,
	Morgana = 0xF537FDDD,
	Milio = 0x3687B676,
	Nami = 0x2E1EAD2F,
	Nasus = 0x09BBFEFE,
	Nautilus = 0x6C318333,
	Neeko = 0xbce86672,
	Nidalee = 0x7DA436B4,
	Nilah = 0x7A6C1378,
	Nocturne = 0xC4AADC06,
	Nunu = 0x37F8E38E,
	Olaf = 0x62042582,
	Orianna = 0x70018CA6,
	Ornn = 0x650585C3,
	Pantheon = 0xE51EFF33,
	Poppy = 0x1B74F7BA,
	Pyke = 0x96FBC243,
	Qiyana = 0xd37489d3,
	Quinn = 0x7315CE25,
	Rakan = 0x1568FA09,
	Rammus = 0xA1DBE5ED,
	RekSai = 0x57601883,
	Rell = 0xea312df3,
	Renata = 0xda2a7853,
	Renekton = 0x1C0BE672,
	Rengar = 0xDD0BD0BD,
	Riven = 0x8F0E2B88,
	Rumble = 0xEADFA531,
	Ryze = 0xF4186772,
	Samira = 0xB60D0859,
	Sejuani = 0x887A3ADF,
	Senna = 0x14F7CDAF,
	Seraphine = 0xc2cb5e87,
	Sett = 0x18c000b2,
	Shaco = 0x9A1A73B8,
	Shen = 0x1A2B2B7E,
	Shyvana = 0xF45FC062,
	Singed = 0x02EDAEEE,
	Sion = 0x1AB33D75,
	Sivir = 0xD2FE8B89,
	Skarner = 0x24FE8072,
	Sona = 0x1DA69A2F,
	Soraka = 0x51A4D061,
	Swain = 0x5406B062,
	Sylas = 0xb676fa78,
	Syndra = 0x404673AB,
	TahmKench = 0xD93E9107,
	Taliyah = 0x6B3F0A56,
	Talon = 0x9DCDCAFE,
	Taric = 0xA0BC267F,
	Teemo = 0x5474A0F6,
	Thresh = 0x8E5AD89C,
	Tristana = 0x23CDE228,
	Trundle = 0x25D6A766,
	Tryndamere = 0xDE11375B,
	TwistedFate = 0xD04DE692,
	Twitch = 0xEDC9F793,
	Udyr = 0x755493E8,
	Urgot = 0xF637B92F,
	Varus = 0x28A0E785,
	Vayne = 0x2C0C5245,
	Veigar = 0x4D1B41FE,
	Velkoz = 0xDAB5F5B9,
	Vex = 0x3a803ec9,
	Vi = 0x00761D73,
	Viego = 0x9662a07a,
	Viktor = 0xC04F2C7F,
	Vladimir = 0xBECBD446,
	Volibear = 0x3F2A754A,
	Warwick = 0x08CA82C2,
	MonkeyKing = 0x205D23CA,
	Xayah = 0xB3D80D17,
	Xerath = 0x195002D0,
	XinZhao = 0x0BBB6179,
	Yasuo = 0xF4E41405,
	Yorick = 0xDA9791F5,
	Yuumi = 0x98607FF5,
	Zac = 0x3C747BBC,
	Zed = 0x3C787CB9,
	Zeri = 0x5E6DB562,
	Ziggs = 0xA7103B84,
	Zilean = 0x40169635,
	Zoe = 0x3C827F30,
	Zyra = 0x6846EB6E,
	Yone = 0x34cf7ead,
	PracticeTool_TargetDummy = 0x6a9da18b,
	SRU_Plant_Health = 0xc3479cd9,
	SRU_Plant_Satchel = 0xe8814ff5,
	SRU_Plant_Vision = 0x4d61e805,
	SRU_Dragon_Air = 0x11d34e07,
	SRU_Dragon_Earth = 0x606dcd87,
	SRU_Dragon_Fire = 0x99a947d9,
	SRU_Dragon_Water = 0x27f996f4,
	SRU_Dragon_Hextech = 0xa076eece,
	SRU_Dragon_Elder = 0x5944e907,
	SRU_Dragon_Chemtech = 0xf956a026,
	ShacoBox = 0x4ac2e173,
	JhinTrap = 0x1c23c910,
	CaitlynTrap = 0xaacc89a5,
	TeemoMushroom = 0x2b2ff5ae,
	YellowTrinket = 0x40d7e043,
	JammerDevice = 0x8223b6ba,
	BlueTrinket = 0xe20532fd,
	SightWard = 0x7C1BCAD9,
	S5Test_WardCorpse = 0x3d5dc843,
	Sru_CrabWard = 0x9dc6e715,
	Sru_Crab = 0x2db77af9,
	SRU_KrugMiniMini = 0xa8245c50,
	SRU_KrugMini = 0xf8123c99,
	SRU_Krug = 0xa20205e2,
	SRU_Gromp = 0xd1c19b7e,
	SRU_Murkwolf = 0x621947dc,
	SRU_MurkwolfMini = 0x9a1d4493,
	SRU_Razorbeak = 0x244e9932,
	SRU_RazorbeakMini = 0xa2c97fe9,
	SRU_Blue = 0xfc505223,
	SRU_Red = 0x9ca35508,
	SRU_RiftHerald = 0xddaf53d2,
	SRU_Baron = 0x68ac12c9,
	SRUAP_Turret_Order1 = 0xc57b1d38,
	SRUAP_Turret_Order2 = 0xc57b1d39,
	SRUAP_Turret_Order3 = 0xc57b1d3a,
	SRUAP_Turret_Chaos1 = 0x8d840146,
	SRUAP_Turret_Chaos2 = 0x8d840147,
	SRUAP_Turret_Chaos3 = 0x8d840148,
	SRUAP_Turret_Order4 = 0xc57b1d3b,
	SRUAP_Turret_Chaos4 = 0x8d840149,
	SRUAP_Turret_Order5 = 0xc57b1d3c,
	PreSeason_Turret_Shield = 0xc1b8c07f,
	HA_AP_OrderTurret = 0x37085ad4,
	HA_AP_OrderTurret2 = 0xe5e25a5e,
	HA_AP_OrderTurret3 = 0xe5e25a5f,
	HA_AP_ChaosTurret = 0x3609c846,
	HA_AP_ChaosTurret2 = 0x14ae496c,
	HA_AP_ChaosTurret3 = 0x14ae496d,
	HA_AP_OrderShrineTurret = 0x2678e477,
	HA_AP_ChaosTurretShrine = 0x2cbcb369,
	SRUAP_MageCrystal = 0x632b992a,
	SRU_ChaosMinionMelee = 0xb87bb4c7,
	SRU_ChaosMinionRanged = 0xd86ea814,
	SRU_OrderMinionMelee = 0xd11193b9,
	SRU_OrderMinionRanged = 0xc44285a2,
	SRU_OrderMinionSiege = 0x1f46a4b2,
	SRU_ChaosMinionSiege = 0x6b0c5c0,
	SRU_OrderMinionSuper = 0x530117c0,
	SRU_ChaosMinionSuper = 0x3a6b38ce,
	HA_OrderMinionMelee = 0xea51b9f6,
	HA_OrderMinionRanged = 0x2148eea5,
	HA_ChaosMinionMelee = 0xd1bbdb04,
	HA_ChaosMinionRanged = 0x35751117,
	HA_OrderMinionSiege = 0x3886caef,
	HA_ChaosMinionSiege = 0x1ff0ebfd,
	HA_OrderMinionSuper = 0x6c413dfd,
	HA_ChaosMinionSuper = 0x53ab5f0b,
	SRU_RiftHerald_Relic = 0xc3cdda6,
	SRU_CampRespawnMarker = 0x3101c878,
	SRU_BaronSpawn = 0x8467c712,
	TestCubeRender = 0xcb00303d,
	SRU_RiftHerald_Mercenary = 0x7ff87da9,
	SRU_PlantRespawnMarker = 0x1a6947a0,
	TestCubeRender10Vision = 0x794d3be4,
	AnnieTibbers = 0x51dae4d4,
	OriannaBall = 0x1e070aa5,
	ShenSpirit = 0xc40cee4f,
	LuluFaerie = 0x1e6ee216,
	ZacRebirthBloblet = 0x2048248e,
	YorickGhoul = 0x5783A104,
	HA_AP_Poro = 0x2c0d32a6,
	HA_AP_PoroSpawner = 0x89620a42,
	HA_AP_HealthRelic = 0xda54bc8d,
	ZyraThornPlant = 0x34B09A22,
	ZyraGraspingPlant = 0x71DC5EAE,
	Blade = 0x794D3BE4,
	Barrel = 0x7B575CB5,
	SennaSoul = 0x924D5AA2
};

enum class GameObjectType : uint32_t
{
	NeutralMinionCamp = 0xFE7449A3,
	AIHeroClient = 0xE260302C,
	AIMarker = 0x11F7583D,
	AIMinionClient = 0xCAA58CB2,
	ObjectAttacher = 0x9E317160,
	LevelPropAIClient = 0x12E24BCD,
	AITurretClient = 0xBEBA9102,
	AITurretCommon = 0x70678BD0,
	EffectEmitter = 0xDD4DE76F,
	GameObject = 0x1FAC8B64,
	MissileClient = 0x9C8ADE94,
	DrawFX = 0x42D144F5,
	UnrevealedTarget = 0xB98F49AF,
	BarracksDampener = 0x60BB49C0,
	Barracks = 0xD1ED70FE,
	AnimatedBuilding = 0x8F83FB9C,
	BuildingClient = 0x3CCABB2E,
	ObjLevelsizer = 0x6F2E6CAC,
	ObjNavPoint = 0x96B0A5E6,
	ObjSpawnPoint = 0xE3E9B36C,
	GrassObject = 0xAA2B7AB2,
	HQ = 0x503AD0D2,
	ObjInfoPoint = 0xF4753AD3,
	LevelPropGameObject = 0x5A730CB9,
	LevelPropSpawnerPoint = 0x4D8B713A,
	Shop = 0xA847E0A9,
	ObjTurret = 0x3D775D09
};

enum class CombatType : int
{
	Melee = 1,
	Ranged = 2,
};

enum class GameObjectTeam : int
{
	Unknown = 0,
	Blue = 100,
	Red = 200,
	Neutral = 300,
};

enum class TypeFlag : int
{
	Object = (1 << 0),  //0x1
	NeutralCamp = (1 << 1),  //0x2
	DeadObject = (1 << 4),  //0x10
	InvalidObject = (1 << 5),  //0x20
	AIBaseCommon = (1 << 7),  //0x80
	AttackableUnit = (1 << 9),  //0x200
	AI = (1 << 10), //0x400
	Minion = (1 << 11), //0x800
	Hero = (1 << 12), //0x1000
	Turret = (1 << 13), //0x2000
	Unknown0 = (1 << 14), //0x4000
	Missile = (1 << 15), //0x8000
	Unknown1 = (1 << 16), //0x10000
	Building = (1 << 17), //0x20000
	Unknown2 = (1 << 18), //0x40000
};

enum class RecallState : int
{
	Unknown = 0,
	Recall = 6,
	EmpoweredRecall = 11,
	Teleport = 16,
};

#pragma endregion

#pragma region BuffManager

enum class BuffType : unsigned char
{
	Internal = 0,
	Aura = 1,
	CombatEnchancer = 2,
	CombatDehancer = 3,
	SpellShield = 4,
	Stun = 5,
	Invisibility = 6,
	Silence = 7,
	Taunt = 8,
	Berserk = 9,
	Polymorph = 10,
	Slow = 11,
	Snare = 12,
	Damage = 13,
	Heal = 14,
	Haste = 15,
	SpellImmunity = 16,
	PhysicalImmunity = 17,
	Invulnerability = 18,
	AttackSpeedSlow = 19,
	NearSight = 20,
	Currency = 21,
	Fear = 22,
	Charm = 23,
	Poison = 24,
	Suppression = 25,
	Blind = 26,
	Counter = 27,
	Shred = 28,
	Flee = 29,
	Knockup = 30,
	Knockback = 31,
	Disarm = 32,
	Grounded = 33,
	Drowsy = 34,
	Asleep = 35,
	Obscured = 36,
	ClickproofToEnemies = 37,
	UnKillable = 38,
};

#pragma endregion

#pragma region Items
enum class ItemId : uint32_t
{
	Boots = 1001,
	Faerie_Charm = 1004,
	Rejuvenation_Bead = 1006,
	Giants_Belt = 1011,
	Cloak_of_Agility = 1018,
	Blasting_Wand = 1026,
	Sapphire_Crystal = 1027,
	Ruby_Crystal = 1028,
	Cloth_Armor = 1029,
	Chain_Vest = 1031,
	Null_Magic_Mantle = 1033,
	Emberknife = 1035,
	Long_Sword = 1036,
	Pickaxe = 1037,
	B_F_Sword = 1038,
	Hailblade = 1039,
	Dagger = 1042,
	Recurve_Bow = 1043,
	Amplifying_Tome = 1052,
	Vampiric_Scepter = 1053,
	Dorans_Shield = 1054,
	Dorans_Blade = 1055,
	Dorans_Ring = 1056,
	Negatron_Cloak = 1057,
	Needlessly_Large_Rod = 1058,
	Dark_Seal = 1082,
	Cull = 1083,
	Health_Potion = 2003,
	Total_Biscuit_of_Everlasting_Will = 2010,
	Kircheis_Shard = 2015,
	Refillable_Potion = 2031,
	Corrupting_Potion = 2033,
	Guardians_Horn = 2051,
	Poro_Snax = 2052,
	Control_Ward = 2055,
	Shurelyas_Battlesong = 2065,
	Elixir_of_Iron = 2138,
	Elixir_of_Sorcery = 2139,
	Elixir_of_Wrath = 2140,
	Minion_Dematerializer = 2403,
	Commencing_Stopwatch = 2419,
	Stopwatch = 2420,
	Broken_Stopwatch = 2421,
	Slightly_Magical_Footware = 2422,
	Perfectly_Timed_Stopwatch = 2423,
	Abyssal_Mask = 3001,
	Archangels_Staff = 3003,
	Manamune = 3004,
	Berserkers_Greaves = 3006,
	Boots_of_Swiftness = 3009,
	Chemtech_Putrifier = 3011,
	Sorcerers_Shoes = 3020,
	Glacial_Buckler = 3024,
	Guardian_Angel = 3026,
	Infinity_Edge = 3031,
	Mortal_Reminder = 3033,
	Last_Whisper = 3035,
	Lord_Dominiks_Regards = 3036,
	Mejais_Soulstealer = 3041,
	Muramana = 3042,
	Phage = 3044,
	Phantom_Dancer = 3046,
	Plated_Steelcaps = 3047,
	Seraphs_Embrace = 3048,
	Zekes_Convergence = 3050,
	Hearthbound_Axe = 3051,
	Steraks_Gage = 3053,
	Sheen = 3057,
	Spirit_Visage = 3065,
	Winged_Moonplate = 3066,
	Kindlegem = 3067,
	Sunfire_Aegis = 3068,
	Tear_of_the_Goddess = 3070,
	Black_Cleaver = 3071,
	Bloodthirster = 3072,
	Ravenous_Hydra = 3074,
	Thornmail = 3075,
	Bramble_Vest = 3076,
	Tiamat = 3077,
	Trinity_Force = 3078,
	Wardens_Mail = 3082,
	Warmogs_Armor = 3083,
	Runaans_Hurricane = 3085,
	Zeal = 3086,
	Rabadons_Deathcap = 3089,
	Wits_End = 3091,
	Rapid_Firecannon = 3094,
	Stormrazor = 3095,
	Lich_Bane = 3100,
	Banshees_Veil = 3102,
	Aegis_of_the_Legion = 3105,
	Redemption = 3107,
	Fiendish_Codex = 3108,
	Knights_Vow = 3109,
	Frozen_Heart = 3110,
	Mercurys_Treads = 3111,
	Guardians_Orb = 3112,
	Aether_Wisp = 3113,
	Forbidden_Idol = 3114,
	Nashors_Tooth = 3115,
	Rylais_Crystal_Scepter = 3116,
	Mobility_Boots = 3117,
	Executioners_Calling = 3123,
	Guinsoos_Rageblade = 3124,
	Caulfields_Warhammer = 3133,
	Serrated_Dirk = 3134,
	Void_Staff = 3135,
	Mercurial_Scimitar = 3139,
	Quicksilver_Sash = 3140,
	Youmuus_Ghostblade = 3142,
	Randuins_Omen = 3143,
	Hextech_Alternator = 3145,
	Hextech_Rocketbelt = 3152,
	Blade_of_the_Ruined_King = 3153,
	Hexdrinker = 3155,
	Maw_of_Malmortius = 3156,
	Zhonyas_Hourglass = 3157,
	Ionian_Boots_of_Lucidity = 3158,
	Morellonomicon = 3165,
	Guardians_Blade = 3177,
	Umbral_Glaive = 3179,
	Sanguine_Blade = 3181,
	Guardians_Hammer = 3184,
	Locket_of_the_Iron_Solari = 3190,
	Seekers_Armguard = 3191,
	Gargoyle_Stoneplate = 3193,
	Spectres_Cowl = 3211,
	Mikaels_Blessing = 3222,
	Scarecrow_Effigy = 3330,
	Stealth_Ward = 3340,
	Farsight_Alteration = 3363,
	Oracle_Lens = 3364,
	Your_Cut = 3400,
	Ardent_Censer = 3504,
	Essence_Reaver = 3508,
	Eye_of_the_Herald = 3513,
	Kalistas_Black_Spear = 3599,
	Dead_Mans_Plate = 3742,
	Titanic_Hydra = 3748,
	Crystalline_Bracer = 3801,
	Lost_Chapter = 3802,
	Edge_of_Night = 3814,
	Spellthiefs_Edge = 3850,
	Frostfang = 3851,
	Shard_of_True_Ice = 3853,
	Steel_Shoulderguards = 3854,
	Runesteel_Spaulders = 3855,
	Pauldrons_of_Whiterock = 3857,
	Relic_Shield = 3858,
	Targons_Buckler = 3859,
	Bulwark_of_the_Mountain = 3860,
	Spectral_Sickle = 3862,
	Harrowing_Crescent = 3863,
	Black_Mist_Scythe = 3864,
	Oblivion_Orb = 3916,
	Imperial_Mandate = 4005,
	Force_of_Nature = 4401,
	The_Golden_Spatula = 4403,
	Horizon_Focus = 4628,
	Cosmic_Drive = 4629,
	Blighting_Jewel = 4630,
	Verdant_Barrier = 4632,
	Riftmaker = 4633,
	Leeching_Leer = 4635,
	Night_Harvester = 4636,
	Demonic_Embrace = 4637,
	Watchful_Wardstone = 4638,
	Stirring_Wardstone = 4641,
	Bandleglass_Mirror = 4642,
	Vigilant_Wardstone = 4643,
	Ironspike_Whip = 6029,
	Silvermere_Dawn = 6035,
	Deaths_Dance = 6333,
	Chempunk_Chainsword = 6609,
	Staff_of_Flowing_Water = 6616,
	Moonstone_Renewer = 6617,
	Goredrinker = 6630,
	Stridebreaker = 6631,
	Divine_Sunderer = 6632,
	Liandrys_Anguish = 6653,
	Ludens_Tempest = 6655,
	Everfrost = 6656,
	Bamis_Cinder = 6660,
	Frostfire_Gauntlet = 6662,
	Turbo_Chemtank = 6664,
	Noonquiver = 6670,
	Galeforce = 6671,
	Kraken_Slayer = 6672,
	Immortal_Shieldbow = 6673,
	Navori_Quickblades = 6675,
	The_Collector = 6676,
	Rageknife = 6677,
	Duskblade_of_Draktharr = 6691,
	Eclipse = 6692,
	Prowlers_Claw = 6693,
	Seryldas_Grudge = 6694,
	Serpents_Fang = 6695
};
#pragma endregion

#pragma region
enum class ChampionId
{
	Aatrox = 266,
	Ahri = 103,
	Akali = 84,
	Alistar = 12,
	Amumu = 32,
	Anivia = 34,
	Annie = 1,
	Aphelios = 523,
	Ashe = 22,
	AurelionSol = 136,
	Azir = 268,
	Bard = 432,
	Blitzcrank = 53,
	Brand = 63,
	Braum = 201,
	Caitlyn = 51,
	Camille = 164,
	Cassiopeia = 69,
	Chogath = 31,
	Corki = 42,
	Darius = 122,
	Diana = 131,
	DrMundo = 36,
	Draven = 119,
	Ekko = 245,
	Elise = 60,
	Evelynn = 28,
	Ezreal = 81,
	FiddleSticks = 9,
	Fiora = 114,
	Fizz = 105,
	Galio = 3,
	Gangplank = 41,
	Garen = 86,
	Gnar = 150,
	Gragas = 79,
	Graves = 104,
	Hecarim = 120,
	Heimerdinger = 74,
	Illaoi = 420,
	Irelia = 39,
	Ivern = 427,
	Janna = 40,
	JarvanIV = 59,
	Jax = 24,
	Jayce = 126,
	Jhin = 202,
	Jinx = 222,
	Kaisa = 145,
	Kalista = 429,
	Karma = 43,
	Karthus = 30,
	Kassadin = 38,
	Katarina = 55,
	Kayle = 10,
	Kayn = 141,
	Kennen = 85,
	Khazix = 121,
	Kindred = 203,
	Kled = 240,
	KogMaw = 96,
	Leblanc = 7,
	LeeSin = 64,
	Leona = 89,
	Lillia = 876,
	Lissandra = 127,
	Lucian = 236,
	Lulu = 117,
	Lux = 99,
	Malphite = 54,
	Malzahar = 90,
	Maokai = 57,
	MasterYi = 11,
	MissFortune = 21,
	Mordekaiser = 82,
	Morgana = 25,
	Nami = 267,
	Nasus = 75,
	Nautilus = 111,
	Neeko = 518,
	Nidalee = 76,
	Nocturne = 56,
	Nunu = 20,
	Olaf = 2,
	Orianna = 61,
	Ornn = 516,
	Pantheon = 80,
	Poppy = 78,
	Pyke = 555,
	Qiyana = 246,
	Quinn = 133,
	Rakan = 497,
	Rammus = 33,
	RekSai = 421,
	Rell = 526,
	Renekton = 58,
	Rengar = 107,
	Riven = 92,
	Rumble = 68,
	Ryze = 13,
	Samira = 360,
	Sejuani = 113,
	Senna = 235,
	Seraphine = 147,
	Sett = 875,
	Shaco = 35,
	Shen = 98,
	Shyvana = 102,
	Singed = 27,
	Sion = 14,
	Sivir = 15,
	Skarner = 72,
	Sona = 37,
	Soraka = 16,
	Swain = 50,
	Sylas = 517,
	Syndra = 134,
	TahmKench = 223,
	Taliyah = 163,
	Talon = 91,
	Taric = 44,
	Teemo = 17,
	Thresh = 412,
	Tristana = 18,
	Trundle = 48,
	Tryndamere = 23,
	TwistedFate = 4,
	Twitch = 29,
	Udyr = 77,
	Urgot = 6,
	Varus = 110,
	Vayne = 67,
	Veigar = 45,
	Velkoz = 161,
	Vi = 254,
	Viego = 234,
	Viktor = 112,
	Vladimir = 8,
	Volibear = 106,
	Warwick = 19,
	MonkeyKing = 62,
	Xayah = 498,
	Xerath = 101,
	XinZhao = 5,
	Yasuo = 157,
	Yone = 777,
	Yorick = 83,
	Yuumi = 350,
	Zac = 154,
	Zed = 238,
	Ziggs = 115,
	Zilean = 26,
	Zoe = 142,
	Zyra = 143,
	Gwen = 887,
	Akshan = 166,
	Vex = 711,
	Zeri = 221,
	Renata = 888,
	Belveth = 200,
	Nilah = 895,
	KSante = 897,
	Unknown = 5000,
};
#pragma endregion

#pragma region Spells
enum class SpellState : int
{
	Unknown = -1,
	Ready = 0,
	NotAvailable = 4,
	Supressed = 8,
	NotLearned = 12,
	Channeling = 24,
	Cooldown = 32,
	NoMana = 64,
};

enum class SpellSlotId : int
{
	Unknown = -1,
	Q = 0,
	W = 1,
	E = 2,
	R = 3,
	Summoner1,
	Summoner2,
	Item1,
	Item2,
	Item3,
	Item4,
	Item5,
	Item6,
	Item_Trinket,
	Recall,
	SpecialAttack = 45,
	Auto1 = 64,
	Auto2 = 65,
};
#pragma endregion

#pragma region Menu
enum class TabCategory
{
	core,
	script,
	utils,
	misc
};
#pragma endregion

#pragma region Events
enum class EventType : int
{
	OnWndProc = 1,
	OnGameTick,
	OnDraw,
	OnCreateObject,
	OnDeleteObject,
	OnProcessSpell,
	OnIssueOrder,
	OnCastSpell,
	OnStopCast,
	OnCastComplete,
	OnBuffGain,
	OnBuffUpdate,
	OnPlayAnimation,
	OnDrawEnvironment,

	size
};
#pragma endregion

#pragma region IssueOrder
enum class IssueOrderType : int
{
	None = 0x0,
	Hold = 0x1,
	MoveTo = 0x2,
	AttackTo = 0x3,
	AttackMove = 0x7,
	Stop = 0xA,
};
#pragma endregion

#pragma region MenuEntry
enum EntryType
{
	menu,
	checkbox,
	slider,
	combo,
	color,
	button,
	key
};
#pragma endregion

class Color
{
	byte r, g, b, a;
public:
	Color(byte r, byte g, byte b, byte a = 255) : r(r), g(g), b(b), a(a) {}
	Color(uint32_t col) : r(GET_R(col)), g(GET_G(col)), b(GET_B(col)), a(GET_A(col)) {}

	operator uint32_t() const { return COLOR_ARGB(a, r, g, b); }
};

class SDK;

class MissileClient;
class GameObject;
class Buff;
class PathControllerCommon;
class ProcessedSpell;
class ActiveSpell;
class ItemSlot;
class SpellSlot;
class SpellData;
class Spellbook;
class Console;
class CallbackManager;
class DrawManager;
class GameClock;
class NetClient;
class Hud;
class Cursor;
class Input;
class Renderer;
class MenuManager;
class MenuTab;
class MenuEntry;
class Chat;
class EntityList;

#define DEFINE_EXPORTED_CLASS(NAME) inline NAME* __exported##NAME = nullptr;
#define GET_EXPORTED_CLASS(NAME) virtual NAME* getExported##NAME () = 0;
#define CALL_EXPORTED_CLASS(NAME) __exported##NAME = getExported##NAME ();

DEFINE_EXPORTED_CLASS(MissileClient);
DEFINE_EXPORTED_CLASS(GameObject);
DEFINE_EXPORTED_CLASS(Buff);
DEFINE_EXPORTED_CLASS(PathControllerCommon);
DEFINE_EXPORTED_CLASS(ProcessedSpell);
DEFINE_EXPORTED_CLASS(ActiveSpell);
DEFINE_EXPORTED_CLASS(ItemSlot);
DEFINE_EXPORTED_CLASS(SpellSlot);
DEFINE_EXPORTED_CLASS(SpellData);
DEFINE_EXPORTED_CLASS(Spellbook);
DEFINE_EXPORTED_CLASS(Hud);
DEFINE_EXPORTED_CLASS(Cursor);
DEFINE_EXPORTED_CLASS(NetClient);

inline GameObject* localPlayer = nullptr;
inline Console* console = nullptr;
inline CallbackManager* callbackManager = nullptr;
inline DrawManager* drawManager = nullptr;
inline GameClock* gameClock = nullptr;
inline Input* input = nullptr;
inline Renderer* renderer = nullptr;
inline MenuManager* menuManager = nullptr;
inline Chat* chat = nullptr;
inline EntityList* entityList = nullptr;
inline Hud* hud = nullptr;
inline Cursor* cursor = nullptr;
inline NetClient* netClient = nullptr;

class SDK
{
public:
	GET_EXPORTED_CLASS(MissileClient);
	GET_EXPORTED_CLASS(GameObject);
	GET_EXPORTED_CLASS(Buff);
	GET_EXPORTED_CLASS(PathControllerCommon);
	GET_EXPORTED_CLASS(ProcessedSpell);
	GET_EXPORTED_CLASS(ActiveSpell);
	GET_EXPORTED_CLASS(ItemSlot);
	GET_EXPORTED_CLASS(SpellSlot);
	GET_EXPORTED_CLASS(SpellData);
	GET_EXPORTED_CLASS(Spellbook);
	GET_EXPORTED_CLASS(Hud);
	GET_EXPORTED_CLASS(Cursor);
	GET_EXPORTED_CLASS(NetClient);
	virtual GameObject* getLocalPlayer() = 0;
	virtual Console* getConsole() = 0;
	virtual CallbackManager* getCbManager() = 0;
	virtual DrawManager* getDrawManager() = 0;
	virtual GameClock* getGameClock() = 0;
	virtual NetClient* getNetClient() = 0;
	virtual Hud* getHud() = 0;
	virtual Cursor* getCursor() = 0;
	virtual Input* getInput() = 0;
	virtual Renderer* getRenderer() = 0;
	virtual MenuManager* getMenuManager() = 0;
	virtual Chat* getChat() = 0;
	virtual EntityList* getEntityList() = 0;

	void initialize()
	{
		CALL_EXPORTED_CLASS(MissileClient);
		CALL_EXPORTED_CLASS(GameObject);
		CALL_EXPORTED_CLASS(Buff);
		CALL_EXPORTED_CLASS(PathControllerCommon);
		CALL_EXPORTED_CLASS(ProcessedSpell);
		CALL_EXPORTED_CLASS(ActiveSpell);
		CALL_EXPORTED_CLASS(ItemSlot);
		CALL_EXPORTED_CLASS(SpellSlot);
		CALL_EXPORTED_CLASS(SpellData);
		CALL_EXPORTED_CLASS(Spellbook);
		CALL_EXPORTED_CLASS(NetClient);
		CALL_EXPORTED_CLASS(Hud);
		CALL_EXPORTED_CLASS(Cursor);
		hud = getHud();
		cursor = getCursor();
		netClient = getNetClient();
		localPlayer = getLocalPlayer();
		console = getConsole();
		callbackManager = getCbManager();
		drawManager = getDrawManager();
		gameClock = getGameClock();
		input = getInput();
		renderer = getRenderer();
		menuManager = getMenuManager();
		chat = getChat();
		entityList = getEntityList();
	}
};

#define IMPORT_FUNC(RET, NAME, IN_ARGS, OUT_ARGS, CALL) \
	virtual __forceinline RET __EXPORTED##NAME IN_ARGS = 0; \
	RET NAME OUT_ARGS{ return FOCUS_CLASS->__EXPORTED##NAME CALL; };

#define FOCUS_CLASS __exportedGameObject
class GameObject
{
public:
	IMPORT_FUNC(void, issueOrder, (GameObject* obj, IssueOrderType order, Vec3 position, GameObject* target, const bool minion), (IssueOrderType order, Vec3 position, GameObject* target, const bool minion), (this, order, position, target, minion))
		IMPORT_FUNC(void, castSpell, (GameObject* obj, SpellSlotId slotId, const Vec3& startPos, const Vec3& endPos, GameObject* target), (SpellSlotId slotId, const Vec3& startPos, const Vec3& endPos, GameObject* target), (this, slotId, startPos, endPos, target))
		IMPORT_FUNC(MissileClient*, getMissileClient, (GameObject* obj), (), (this));
	IMPORT_FUNC(Spellbook*, getSpellBook, (GameObject* obj), (), (this));
	IMPORT_FUNC(PathControllerCommon*, getPathControllerCommon, (GameObject* obj), (), (this));
	IMPORT_FUNC(SpellData*, getBasicAttack, (GameObject* obj), (), (this));
	IMPORT_FUNC(ItemSlot*, getItem, (GameObject* obj, ItemId item), (ItemId item), (this, item));
	IMPORT_FUNC(SpellSlot*, getItemSpellSlot, (GameObject* obj, ItemId item), (ItemId item), (this, item));

	IMPORT_FUNC(SpellSlot*, getSpellSlotById, (GameObject* obj, SpellSlotId id), (SpellSlotId id), (this, id));
	IMPORT_FUNC(ActiveSpell*, getActiveSpell, (GameObject* obj), (), (this));
	IMPORT_FUNC(Buff*, getBuff, (GameObject* obj, const std::string& buffName), (const std::string& buffName), (this, buffName));
	IMPORT_FUNC(Buff*, getBuff, (GameObject* obj, const uint32_t buffHash), (const uint32_t buffHash), (this, buffHash));

	IMPORT_FUNC(std::vector<Buff*>, getBuffs, (GameObject* obj), (), (this));
	IMPORT_FUNC(std::vector<Buff*>, getBuffs, (GameObject* obj, BuffType buffsType), (BuffType buffsType), (this, buffsType));
	IMPORT_FUNC(std::vector<ItemSlot*>, getItems, (GameObject* obj), (), (this));

	IMPORT_FUNC(const std::string&, getName, (GameObject* obj), (), (this));
	IMPORT_FUNC(const std::string&, getModelName, (GameObject* obj), (), (this));
	IMPORT_FUNC(uint32_t, getCharacterHash, (GameObject* obj), (), (this));

	IMPORT_FUNC(const Vec3&, getPosition, (GameObject* obj), (), (this));
	IMPORT_FUNC(const Vec3&, getDirection, (GameObject* obj), (), (this));
	IMPORT_FUNC(Vec2, getHealthBarScreenPosition, (GameObject* obj), (), (this));

	IMPORT_FUNC(GameObjectTeam, getTeam, (GameObject* obj), (), (this));
	IMPORT_FUNC(SpellState, getSpellState, (GameObject* obj, SpellSlotId spellSlot), (SpellSlotId spellSlot), (this, spellSlot));

	IMPORT_FUNC(int, getBuffCount, (GameObject* obj, const std::string& buffName), (const std::string& buffName), (this, buffName));

	IMPORT_FUNC(unsigned, getIndex, (GameObject* obj), (), (this));
	IMPORT_FUNC(unsigned, getNetworkId, (GameObject* obj), (), (this));
	IMPORT_FUNC(unsigned, getCurrentGold, (GameObject* obj), (), (this));
	IMPORT_FUNC(unsigned, getVisibility, (GameObject* obj), (), (this));
	IMPORT_FUNC(unsigned, getSrcIndex, (GameObject* obj), (), (this));
	IMPORT_FUNC(unsigned, getLevelUpPoints, (GameObject* obj), (), (this));
	IMPORT_FUNC(unsigned, getLevel, (GameObject* obj), (), (this));

	IMPORT_FUNC(float, getBoundingRadius, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getHealth, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getMaxHealth, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getShield, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getMagicShield, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getMana, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getMaxMana, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getAbilityHaste, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getLethality, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getArmor, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getBonusArmor, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getMagicRes, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getBonusMagicRes, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getBaseAD, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getBonusAD, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getMovementSpeed, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getCritDamageMultiplier, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getCrit, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getBaseAP, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getBonusAP, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getBonusAPMultiplier, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getAttackSpeedMultiplier, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getRealAttackRange, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, isTargetable, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getAccumulatedExperience, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getMagicPenFlat, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getArmorPenMultiplier, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getMagicPenMultiplier, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getManaRegen, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getHealthRegen, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getAttackDelay, (GameObject* obj), (), (this));
	IMPORT_FUNC(float, getAttackCastDelay, (GameObject* obj), (), (this));

	IMPORT_FUNC(bool, isInvulnerable, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isVisibleOnScreen, (GameObject* obj, int tolerance = 0), (int tolerance = 0), (this, tolerance));
	IMPORT_FUNC(bool, isMelee, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isRanged, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isAlly, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isAlly, (GameObject* obj, GameObject* other), (GameObject* other), (this, other));
	IMPORT_FUNC(bool, isEnemy, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isEnemy, (GameObject* obj, GameObject* other), (GameObject* other), (this, other));
	IMPORT_FUNC(bool, isNeutral, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isVisible, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isZombie, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isTargetableToAllies, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isTargetableToEnemies, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isRecalling, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isTeleporting, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, compareObjectTypeFlag, (GameObject* obj, TypeFlag flag), (TypeFlag flag), (this, flag));
	IMPORT_FUNC(bool, hasBuff, (GameObject* obj, const std::string& buffName), (const std::string& buffName), (this, buffName));
	IMPORT_FUNC(bool, hasBuff, (GameObject* obj, const uint32_t buffHash), (const uint32_t buffHash), (this, buffHash));
	IMPORT_FUNC(bool, hasBuffType, (GameObject* obj, BuffType buffType), (BuffType buffType), (this, buffType));
	IMPORT_FUNC(bool, isMe, (GameObject* obj), (), (this));
	IMPORT_FUNC(GameObjectType, getType, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isMinion, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isInhibitor, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isNexus, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isChampion, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isTurret, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isMissile, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isWard, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isBaron, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isAlive, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isPlant, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isPracticeToolDummy, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isClone, (GameObject* obj), (), (this));
	IMPORT_FUNC(bool, isFacing, (GameObject* obj, const Vec3& position), (const Vec3& position), (this, position));
	IMPORT_FUNC(bool, isFacing, (GameObject* obj, GameObject* gameObject), (GameObject* gameObject), (this, gameObject));
	IMPORT_FUNC(bool, isInRange, (GameObject* obj, GameObject* gameObject, float range), (GameObject* gameObject, float range), (this, gameObject, range));
	IMPORT_FUNC(bool, isInRange, (GameObject* obj, const Vec3& position, float range), (const Vec3& position, float range), (this, position, range));
	IMPORT_FUNC(bool, isInAutoAttackRange, (GameObject* obj, GameObject* to, float extraRange = 0), (GameObject* to, float extraRange = 0), (this, to, extraRange));
	IMPORT_FUNC(bool, isValidTarget, (GameObject* obj, float range, const Vec3& from = Vec3(), bool bIgnoreInvulnerability = false), (float range, const Vec3& from = Vec3(), bool bIgnoreInvulnerability = false), (this, range, from, bIgnoreInvulnerability));

	IMPORT_FUNC(double, getTotalRespawnTime, (GameObject* obj), (), (this));
	IMPORT_FUNC(double, getRemainingRespawnTime, (GameObject* obj), (), (this));

	__forceinline float getTotalAD() { return getBaseAD() + getBonusAD(); }
	__forceinline float getTotalAP() { return getBaseAP() + getBonusAP(); }
	__forceinline float getAttackRange() { return getBoundingRadius() + getRealAttackRange(); }

	float getDistance(GameObject* other);
	float getDistance(const Vec3& pos);
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedMissileClient
class MissileClient
{
public:
	IMPORT_FUNC(SpellData*, getSpellData, (MissileClient* obj), (), (this));
	IMPORT_FUNC(const Vec3&, getStartPosition, (MissileClient* obj), (), (this));
	IMPORT_FUNC(const Vec3&, getEndPosition, (MissileClient* obj), (), (this));
	IMPORT_FUNC(const Vec3&, getCastPosition, (MissileClient* obj), (), (this));
	IMPORT_FUNC(SpellSlotId, getSlot, (MissileClient* obj), (), (this));
	IMPORT_FUNC(unsigned, getMissileIndex, (MissileClient* obj), (), (this));
	IMPORT_FUNC(unsigned, getCasterIndex, (MissileClient* obj), (), (this));
	IMPORT_FUNC(unsigned, getTargetIndex, (MissileClient* obj), (), (this));
	IMPORT_FUNC(float, getWindupTime, (MissileClient* obj), (), (this));
	IMPORT_FUNC(float, getCooldown, (MissileClient* obj), (), (this));
	IMPORT_FUNC(float, getManaCost, (MissileClient* obj), (), (this));
	IMPORT_FUNC(float, getCastStartTime, (MissileClient* obj), (), (this));
	IMPORT_FUNC(float, getCastEndTime, (MissileClient* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedSpellbook
class Spellbook
{
public:
	IMPORT_FUNC(SpellState, getSpellState, (Spellbook* obj, SpellSlotId id), (SpellSlotId id), (this, id));

	IMPORT_FUNC(void, sendSpellcastPacket,
		(Spellbook* obj, SpellSlotId slotId, const Vec3& startPos, const Vec3& endPos, GameObject* target),
		(SpellSlotId slotId, const Vec3& startPos, const Vec3& endPos, GameObject* target),
		(this, slotId, startPos, endPos, target));

	IMPORT_FUNC(void, updateChargedSpell,
		(Spellbook* obj, SpellSlot* spellSlot, SpellSlotId slotId, Vec3* position, bool releaseCast),
		(SpellSlot* spellSlot, SpellSlotId slotId, Vec3* position, bool releaseCast),
		(this, spellSlot, slotId, position, releaseCast));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedPathControllerCommon
class PathControllerCommon
{
public:
	IMPORT_FUNC(bool, isMoving, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(bool, isGhosting, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(const Vec3&, getServerPos, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(std::vector<Vec3>, buildPath, (PathControllerCommon* obj, const Vec3& from, const Vec3& to), (const Vec3& from, const Vec3& to), (this, from, to));

	// ========== NAVIGATION PATH ==========

	IMPORT_FUNC(std::vector<Vec3>, getNavWaypoints, (PathControllerCommon* obj, bool pushBack = true), (bool pushBack = true), (this, pushBack));
	IMPORT_FUNC(int, getCurrSegment, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(const Vec3&, getNavStart, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(const Vec3&, getNavEnd, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(int, getNbWaypoints, (PathControllerCommon* obj), (), (this));
	IMPORT_FUNC(float, getPathLength, (PathControllerCommon* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedSpellSlot
class SpellSlot
{
public:
	IMPORT_FUNC(SpellData*, getSpellData, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(int, getAmmo, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(float, getMaxCooldown, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(int, getLevel, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(float, getReadyAt, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(float, getDamage, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(float, getCooldown, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(float, getAmmoReadyAt, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(float, getAmmoCooldown, (SpellSlot* obj), (), (this));
	IMPORT_FUNC(bool, isCharging, (SpellSlot* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedSpellData
class SpellData
{
public:
	IMPORT_FUNC(const std::string&, getSpellName, (SpellData* obj), (), (this));
	IMPORT_FUNC(uint32_t, getHash, (SpellData* obj), (), (this));
	IMPORT_FUNC(const std::string&, getMissileName, (SpellData* obj), (), (this));
	IMPORT_FUNC(float, getMissileSpeed, (SpellData* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedItemSlot
class ItemSlot
{
public:
	IMPORT_FUNC(int, getStacks, (ItemSlot* obj), (), (this));
	IMPORT_FUNC(ItemId, getItemId, (ItemSlot* obj), (), (this));
	IMPORT_FUNC(float, getPrice, (ItemSlot* obj), (), (this));
	IMPORT_FUNC(float, getAbilityHaste, (ItemSlot* obj), (), (this));
	IMPORT_FUNC(float, getHealth, (ItemSlot* obj), (), (this));
	IMPORT_FUNC(float, getMovementSpeed, (ItemSlot* obj), (), (this));
	IMPORT_FUNC(float, getArmor, (ItemSlot* obj), (), (this));
	IMPORT_FUNC(float, getMagicResistance, (ItemSlot* obj), (), (this));
	IMPORT_FUNC(float, getAd, (ItemSlot* obj), (), (this));
	IMPORT_FUNC(float, getAp, (ItemSlot* obj), (), (this));
	IMPORT_FUNC(float, getAttackSpeedMultiplier, (ItemSlot* obj), (), (this));
	IMPORT_FUNC(float, getShieldPowerMultiplier, (ItemSlot* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedActiveSpell
class ActiveSpell
{
public:
	IMPORT_FUNC(GameObject*, getSource, (ActiveSpell* obj), (), (this));
	IMPORT_FUNC(GameObject*, getTarget, (ActiveSpell* obj), (), (this));
	IMPORT_FUNC(SpellData*, getSpellData, (ActiveSpell* obj), (), (this));
	IMPORT_FUNC(const Vec3&, getStartPos, (ActiveSpell* obj), (), (this));
	IMPORT_FUNC(const Vec3&, getEndPos, (ActiveSpell* obj), (), (this));
	IMPORT_FUNC(const Vec3&, getCastPos, (ActiveSpell* obj), (), (this));
	IMPORT_FUNC(bool, isAuto, (ActiveSpell* obj), (), (this));
	IMPORT_FUNC(bool, isSpell, (ActiveSpell* obj), (), (this));
	IMPORT_FUNC(bool, isSpecialAttack, (ActiveSpell* obj), (), (this));
	IMPORT_FUNC(bool, isHeadshot, (ActiveSpell* obj), (), (this));
	IMPORT_FUNC(SpellSlotId, getSlot, (ActiveSpell* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedProcessedSpell
class ProcessedSpell
{
public:
	IMPORT_FUNC(GameObject*, getSource, (ProcessedSpell* obj), (), (this));
	IMPORT_FUNC(GameObject*, getTarget, (ProcessedSpell* obj), (), (this));
	IMPORT_FUNC(SpellData*, getSpellData, (ProcessedSpell* obj), (), (this));
	IMPORT_FUNC(const Vec3&, getStartPos, (ProcessedSpell* obj), (), (this));
	IMPORT_FUNC(const Vec3&, getEndPos, (ProcessedSpell* obj), (), (this));
	IMPORT_FUNC(const Vec3&, getCastPos, (ProcessedSpell* obj), (), (this));
	IMPORT_FUNC(bool, isAuto, (ProcessedSpell* obj), (), (this));
	IMPORT_FUNC(bool, isSpell, (ProcessedSpell* obj), (), (this));
	IMPORT_FUNC(bool, isSpecialAttack, (ProcessedSpell* obj), (), (this));
	IMPORT_FUNC(SpellSlotId, getSlot, (ProcessedSpell* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedBuff
class Buff
{
public:
	IMPORT_FUNC(BuffType, getType, (Buff* obj), (), (this));
	IMPORT_FUNC(int, getCount, (Buff* obj), (), (this));
	IMPORT_FUNC(float, getStartTime, (Buff* obj), (), (this));
	IMPORT_FUNC(float, getEndTime, (Buff* obj), (), (this));
	IMPORT_FUNC(float, getRemainingTime, (Buff* obj), (), (this));
	IMPORT_FUNC(float, getTotalDuration, (Buff* obj), (), (this));
	IMPORT_FUNC(std::string, getName, (Buff* obj), (), (this));
	IMPORT_FUNC(uint32_t, getHash, (Buff* obj), (), (this));
};
#undef FOCUS_CLASS

class Console
{
private:
	virtual void __log(const std::string& msg) = 0;
	virtual void __dbg(const std::string& msg) = 0;
	virtual void __err(const std::string& msg) = 0;
	virtual void __warn(const std::string& msg) = 0;
	virtual void __info(const std::string& msg) = 0;
public:

	void log(const char* msg, ...);
	void dbg(const char* msg, ...);
	void err(const char* msg, ...);
	void warn(const char* msg, ...);
	void info(const char* msg, ...);
};

class CallbackManager
{
public:
	virtual void addCallback(EventType cbType, void* fct) = 0;
	virtual bool removeCallback(EventType cbType, void* fct) = 0;
};

class DrawManager
{
public:
	virtual void screenRectangle(const Vec2& p1, const Vec2& p2, Color col, float rounding = 0.f, float thickness = 1.f, bool filled = false) = 0;
	virtual void rectangle2Points(const Vec3& start, const Vec3& end, Color color, const int width, const float rounding = 0.f, const float thickness = 0.f) = 0;
	virtual void rectangle4Points(const Vec3& p1, const Vec3& p2, const Vec3& p3, const Vec3& p4, Color color, const float thickness = 1.f) = 0;
	virtual void line(const Vec3& p1, const Vec3& p2, Color col, float thickness = 1.f) = 0;
	virtual void screenText(const Vec2& pos, const std::string& text, Color color, int fontSize) = 0;
	virtual void text(const Vec3& pos, const std::string& text, Color color, int fontSize) = 0;
	virtual void texture(const char* texturePath, const Vec2& pos, const Vec2& size, float rounding = 0, const Color color = 0xFFFFFFFF) = 0;
	virtual void texture(std::uint32_t textureHash, const Vec2& pos, const Vec2& size, float rounding = 0, const Color color = 0xFFFFFFFF) = 0;
	virtual void screenCircle(const Vec2& center, const float radius, Color color, const float thickness = 1.f, const bool filled = false, const int numPoints = 99) = 0;
	virtual void circle(const Vec3& center, const float radius, Color color, const float thickness = 1.f, bool filled = false, const int numPoints = 99) = 0;
	virtual Vec2 calcTextSize(const std::string& text, int fontSize) = 0;
};

class GameClock
{
public:
	virtual float	getTime() = 0;
	virtual int		getTickCount() = 0;
};

#define FOCUS_CLASS __exportedNetClient
class NetClient
{
public:
	IMPORT_FUNC(int, getPing, (NetClient* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedHud
class Hud
{
public:
	IMPORT_FUNC(bool, isWindowFocused, (Hud* obj), (), (this));
};
#undef FOCUS_CLASS
#define FOCUS_CLASS __exportedCursor
class Cursor
{
public:
	IMPORT_FUNC(const Vec3&, getWorldPosition, (Cursor* obj), (), (this));
	IMPORT_FUNC(const Vec3&, getLastClickPosition, (Cursor* obj), (), (this));
	IMPORT_FUNC(GameObject*, getHoveredUnit, (Cursor* obj), (), (this));
};
#undef FOCUS_CLASS
class Input
{
public:
	virtual bool isKeyDown(uint32_t key) = 0;
	virtual bool isKeyUp(uint32_t key) = 0;
	virtual bool isKeyPressed(uint32_t key) = 0;
	virtual Vec2 getCursorScreenPosition() = 0;
};

class Renderer
{
public:
	virtual Vec2 getRendererSize() = 0;
	virtual Vec2 worldToScreen(const Vec3& in) = 0;
	virtual Vec2 worldToMinimap(const Vec3& in) = 0;
};

class MenuManager
{
public:
	virtual MenuTab* createMenu(const std::string& key, const std::string& name, const std::string& icon = ICON_FA_FOLDER) = 0;
	virtual bool deleteMenu(MenuTab* menu) = 0;
	virtual bool deleteMenu(const std::string& key) = 0;

	virtual MenuTab* getMenu(const std::string& key) = 0;
	virtual std::vector<MenuTab*> getMenus() = 0;
};

class MenuEntry
{
public:
	virtual std::string		getKey() = 0;
	virtual std::string		getName() = 0;
	virtual EntryType		getType() = 0;

	virtual bool			addColor(float color[4]) = 0;

	virtual bool			getBool() = 0;
	virtual int				getInt() = 0;
	virtual uint32_t		getColor() = 0;

	virtual void			setBool(bool b) = 0;
	virtual void			setInt(int i) = 0;
	virtual void			setColor(uint32_t col) = 0;

	virtual void			setVisibility(bool* vis) = 0;
	virtual void			setVisibility(MenuEntry* entry) = 0;

	virtual void			__DONTCALL1() = 0;
	virtual void			__DONTCALL2() = 0;
	virtual void			__DONTCALL3() = 0;
	virtual void			__DONTCALL4() = 0;
};

class MenuTab : public MenuEntry
{
public:
	virtual MenuTab* addMenu(const std::string& key, const std::string& name, const std::string& icon = "") = 0;
	virtual MenuEntry* addCheckbox(const std::string& key, const std::string& name, bool value) = 0;
	virtual MenuEntry* addSlider(const std::string& key, const std::string& name, int default_value, int min_value, int max_value) = 0;
	virtual MenuEntry* addColorPick(const std::string& key, const std::string& name, float default_value[4]) = 0;
	virtual MenuEntry* addCombo(const std::string& key, const std::string& name, int default_value, const std::vector<std::string>& values) = 0;
	virtual MenuEntry* addKey(const std::string& key, const std::string& name, bool hold, int default_key, bool default_value) = 0;
	virtual MenuEntry* addButton(const std::string& key, const std::string& name, const std::function<void()>& func) = 0;

	virtual MenuEntry* getEntry(const std::string& key) = 0;
	virtual const std::list<MenuEntry*>& getEntries() = 0;

	virtual bool deleteEntry(MenuEntry* entry) = 0;
	virtual bool deleteEntry(const std::string& key) = 0;
};

class Chat
{
public:
	virtual void print(const std::string& message) = 0;
	virtual void send(std::string& message, bool isAllChat = false) = 0;
};

class EntityList
{
public:
	virtual std::vector<GameObject*> getHeroes() = 0;
	virtual std::vector<GameObject*> getAllyHeroes() = 0;
	virtual std::vector<GameObject*> getEnemyHeroes() = 0;

	virtual std::vector<GameObject*> getMinions() = 0;
	virtual std::vector<GameObject*> getAllyMinions() = 0;
	virtual std::vector<GameObject*> getEnemyMinions() = 0;

	virtual std::vector<GameObject*> getTurrets() = 0;
	virtual std::vector<GameObject*> getAllyTurrets() = 0;
	virtual std::vector<GameObject*> getEnemyTurrets() = 0;

	virtual std::vector<GameObject*> getInhibitors() = 0;
	virtual std::vector<GameObject*> getAllyInhibitors() = 0;
	virtual std::vector<GameObject*> getEnemyInhibitors() = 0;

	virtual std::vector<GameObject*> getNexus() = 0;
	virtual GameObject* getAllyNexus() = 0;
	virtual GameObject* getEnemyNexus() = 0;

	virtual std::vector<MissileClient*> getMissiles() = 0;
	virtual std::vector<MissileClient*> getAllyMissiles() = 0;
	virtual std::vector<MissileClient*> getEnemyMissiles() = 0;

	virtual std::vector<GameObject*> getWards() = 0;
	virtual std::vector<GameObject*> getAllyWards() = 0;
	virtual std::vector<GameObject*> getEnemyWards() = 0;

	virtual std::vector<GameObject*> getClones() = 0;
	virtual std::vector<GameObject*> getAllyClones() = 0;
	virtual std::vector<GameObject*> getEnemyClones() = 0;
};

template < EventType event >
struct events
{
	static void addCallback() { }
	static void removeCallback() { }
};

template < >
struct events<EventType::OnGameTick>
{
	static void addCallback(void(*callback)()) { callbackManager->addCallback(EventType::OnGameTick, (void*)callback); }
	static void removeCallback(void(*callback)()) { callbackManager->removeCallback(EventType::OnGameTick, (void*)callback); }
};

template < >
struct events<EventType::OnDraw>
{
	static void addCallback(void(*callback)()) { callbackManager->addCallback(EventType::OnDraw, (void*)callback); }
	static void removeCallback(void(*callback)()) { callbackManager->removeCallback(EventType::OnDraw, (void*)callback); }
};

template < >
struct events<EventType::OnDrawEnvironment>
{
	static void addCallback(void(*callback)()) { callbackManager->addCallback(EventType::OnDrawEnvironment, (void*)callback); }
	static void removeCallback(void(*callback)()) { callbackManager->removeCallback(EventType::OnDrawEnvironment, (void*)callback); }
};

template < >
struct events<EventType::OnWndProc>
{
	static void addCallback(void(*callback)(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* execute)) { callbackManager->addCallback(EventType::OnWndProc, (void*)callback); }
	static void removeCallback(void(*callback)(HWND, UINT, WPARAM, LPARAM, bool*)) { callbackManager->removeCallback(EventType::OnWndProc, (void*)callback); }
};

template < >
struct events<EventType::OnProcessSpell>
{
	static void addCallback(void(*callback)(ProcessedSpell* processedSpell)) { callbackManager->addCallback(EventType::OnProcessSpell, (void*)callback); }
	static void removeCallback(void(*callback)(ProcessedSpell*)) { callbackManager->removeCallback(EventType::OnProcessSpell, (void*)callback); }
};

template < >
struct events<EventType::OnCreateObject>
{
	static void addCallback(void(*callback)(GameObject* obj, uint32_t networkId)) { callbackManager->addCallback(EventType::OnCreateObject, (void*)callback); }
	static void removeCallback(void(*callback)(GameObject*, uint32_t)) { callbackManager->removeCallback(EventType::OnCreateObject, (void*)callback); }
};

template < >
struct events<EventType::OnDeleteObject>
{
	static void addCallback(void(*callback)(GameObject* obj)) { callbackManager->addCallback(EventType::OnDeleteObject, (void*)callback); }
	static void removeCallback(void(*callback)(GameObject*)) { callbackManager->removeCallback(EventType::OnDeleteObject, (void*)callback); }
};

template<typename T>
class Singleton
{
protected:
	Singleton() {}
	~Singleton() {}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;

public:
	static T& get()
	{
		static T inst{};
		return inst;
	}
};