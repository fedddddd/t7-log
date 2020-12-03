#pragma once

namespace game
{
	typedef void (*ClientCommand_t)(int clientNum);
	extern ClientCommand_t ClientCommand;

	typedef dvar_t* (*Dvar_FindVar_t)(const char*);
	extern Dvar_FindVar_t Dvar_FindVar;

	typedef const dvar_t* (*Dvar_RegisterString_t)(const char*, const char*, unsigned int, const char*);
	extern Dvar_RegisterString_t Dvar_RegisterString;

	typedef const char* (*SV_Cmd_Argv_t)(int arg);
	extern SV_Cmd_Argv_t SV_Cmd_Argv;

	typedef void (*G_LogPrintf_t)(const char*, ...);
	extern G_LogPrintf_t G_LogPrintf;
}