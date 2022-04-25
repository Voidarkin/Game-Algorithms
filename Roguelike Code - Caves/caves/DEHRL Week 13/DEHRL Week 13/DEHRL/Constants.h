#pragma once
// the goto place for enumerated values and hardcoded numbers

// what is a particular floor made up of. The models will know what these are.
enum FloorTypes { ROCK, HIDDEN_ROOM_FLOOR, HIDDEN_ROOM_WALL, VISIBLE_ROOM_FLOOR,
					VISIBLE_ROOM_WALL,MAX_FLOOR_TYPE};

// with multiple screens, we need to keep track of what set of views etc are active.  we use the screen id as a key into a map.
enum ScreenID {SPLASH_SCREEN, MENU_SCREEN, ABOUT_SCREEN, GAME_SCREEN, GAME_OVER_SCREEN, INVENTORY_SCREEN, MAX_SCREEN_ID};

// what state is a particular menu item in? Right now, we're only using unsel, hover and pressed.
enum MenuItemState {DISABLED, UNSELECTED, HOVER, PRESSED, MAX_MENU_ITEM_STATE};

// time for the splash screen to be shown
#define SPLASHTIME 10000

// how long does a status bar message stick around
#define MESSAGE_TIME 1000

// how many seconds of actively resting do we need to regain 1 hp
#define REST_TIME 3000

// how long will the game over screen stick around
#define GAME_OVER_TIME 5000

#define CAVE_WIDTH 200
#define CAVE_HEIGHT 200
#define WALL_CHANCE 45

// some constants to make the player input handling easier to use.
enum KeyboardMap { KM_DOWN = 258 , KM_UP=259,KM_LEFT=260, KM_RIGHT=261, KM_SHIFT_DOWN=548, KM_SHIFT_UP=547, KM_SHIFT_LEFT=391, KM_SHIFT_RIGHT=400};

// types of triggers in the game.  Not all of these are active yet.
// (only Stairs Down has a matching trigger in reality)
enum TriggerTypes {TRAP,TRAPDOOR, GOLD, CHEST, ITEM, STAIRS_DOWN, STAIRS_UP, DOOR, SECRET_DOOR,TELEPORTER, MAX_TRIGGER_TYPE };

// what can they player try to do.  Disarm is getting ready for traps
enum PlayerCommands {OPEN, CLOSE, DISARM, SEARCH,GOD_MODE, MAX_COMMAND};

// which way does the hallway go?
enum HallwayType {HORIZONTAL, VERTICAL}; // don't need a max, cause we only have 2 options...

enum CreatureType{PLAYER, ENEMY};

enum DamageType{BLUNT, EDGED, PIERCING, FIRE, ICE, ACID, ELECTRICAL, MAGIC, ANY, NONE, MAX_DAMAGE_TYPE};

enum ComponentType {LEVEL, ANY_TYPE,AC_MOD,HIT_MOD,HELM, SHIELD, ENEMY_ENTITY, PLAYER_ENTITY, HAND, LEFT, RIGHT, HEAD, BODY, WEAPON,BODY_ARMOR, ARMOR,ITEM_COMPONENT, EMPTY, DAMAGE, PROTECTION, DESCRIPTION, DETAIL, PICTURE, MAX_COMPONENT_TYPE};