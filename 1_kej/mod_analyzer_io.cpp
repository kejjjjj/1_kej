#include "pch.h"


bool jAnalyzer::IO_WriteData(const std::string run_name, const std::vector<jump_data>& _data)
{
	std::fstream f;

	const std::string game_path = fs::GetExePath();

	if (!fs::F_DirectoryExists(game_path + "\\1_kej")) {
		if (!fs::F_CreateDirectory(game_path + "\\1_kej")) {
			Com_PrintError(CON_CHANNEL_CONSOLEONLY, "IO_WriteData failed with: %s", fs::_GetLastError().c_str());
			return false;
		}
	}

	if (!fs::F_isValidFileName(run_name)) {
		Com_PrintError(CON_CHANNEL_CONSOLEONLY, "IO_WriteData failed with: invalid file name [%s]\n", run_name.c_str());
		return false;
	}

	const std::string full_path = fs::GetExePath() + "\\1_kej\\" + run_name + ".kej";



	if (!fs::F_OpenFile(f, full_path, fs::fileopen::FILE_OUT)) {

		char* messageBuffer = nullptr;
		std::string err = fs::_GetLastError();

		Com_PrintError(CON_CHANNEL_CONSOLEONLY, "IO_WriteData failed with %s\n", err.c_str());


		fs::F_CloseFile(f);
		return false;

	}

	if (data.size() < 1) {
		Com_PrintError(CON_CHANNEL_CONSOLEONLY, "IO_WriteData failed with: data.size() < 1\n");
		return false;
	}
	if (run_name.size() < 1) {
		Com_PrintError(CON_CHANNEL_CONSOLEONLY, "IO_WriteData failed with: run_name.size() < 1\n");
		return false;
	}

	dvar_s* mapname = Dvar_FindMalleableVar("mapname");

	if (!mapname) {
		Com_PrintError(CON_CHANNEL_CONSOLEONLY, "[mapname] dvar does not exist!\n");
		return false;
	}
	std::set<int>::iterator it = bounceFrames.begin();


	//f << mapname->current.string << '\n';
	for (int32_t i = 0; i < data.size(); i++) {

		f << '{' << data[i].angles[PITCH]		<< "," << data[i].angles[YAW]			<< "," << data[i].angles[ROLL]		<< '}';
		f << '{' << data[i].origin[PITCH]		<< "," << data[i].origin[YAW]			<< "," << data[i].origin[ROLL]		<< '}';
		f << '{' << data[i].velocity[PITCH]		<< "," << data[i].velocity[YAW]			<< "," << data[i].velocity[ROLL]	<< '}';
		f << '{' << data[i].mins[PITCH]			<< "," << data[i].mins[YAW]				<< "," << data[i].mins[ROLL]		<< '}';
		f << '{' << data[i].maxs[PITCH]			<< "," << data[i].maxs[YAW]				<< "," << data[i].maxs[ROLL]		<< '}';
		f << '{' << (int)data[i].forwardmove	<< "}{" << (int)data[i].rightmove		<< '}';
		f << '{' << data[i].rpg_fired			<< "}{" << data[i].bounced				<< '}';
		f << '{' << data[i].FPS					<< "}{" << data[i].colliding			<< '}';
		f << '{' << (*it == i) << "}\n";

		it++;
	}

	fs::F_CloseFile(f);

	Com_Printf(CON_CHANNEL_OBITUARY, "^2file [%s] has been saved\n", run_name.c_str());

	return true;



}
bool jAnalyzer::IO_ReadData(const std::string run_name)
{
	fs::F_Reset(); //reset all the read stuff

	const std::string game_path = fs::GetExePath() + "\\1_kej";
	const std::string full_path = game_path + "\\" + run_name + ".kej";

	if (!fs::F_FileExists(game_path, run_name + ".kej")) {

		Com_PrintError(CON_CHANNEL_OBITUARY, "file [%s] does not exist\n", full_path.c_str());
		return false;
	}

	Com_Printf(CON_CHANNEL_OBITUARY, "^2reading [%s]\n", full_path.c_str());

	std::fstream f;

	if (!fs::F_OpenFile(f, full_path, fs::fileopen::FILE_IN)) 
	{
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "IO_ReadData OpenFile failed with %s\n", fs::_GetLastError());
		return false;
	}

	bool success = IO_StartReadingData(f);

	if (!success)
		ClearData();

	fs::F_CloseFile(f);

	return success;
}
bool jAnalyzer::IO_StartReadingData(std::fstream& fp)
{
	ClearData();
	vec3_t angles, origin, velocity, mins, maxs;
	vec3_t value;
	fs::F_Get(fp);
	bool success;
	bool isBounceFrame;
	while (fp.good() && !fp.eof()) {

		jump_data jData;

		success = IO_ReadVector3(fp, jData.angles);				if (!success) return false; 
		success = IO_ReadVector3(fp, jData.origin);				if (!success) return false;
		success = IO_ReadVector3(fp, jData.velocity);			if (!success) return false;
		success = IO_ReadVector3(fp, jData.mins);				if (!success) return false;
		success = IO_ReadVector3(fp, jData.maxs);				if (!success) return false;
		success = IO_ReadVector1<char>(fp, jData.forwardmove);	if (!success) return false;
		success = IO_ReadVector1<char>(fp, jData.rightmove);	if (!success) return false;
		success = IO_ReadVector1<bool>(fp, jData.rpg_fired);	if (!success) return false;
		success = IO_ReadVector1<bool>(fp, jData.bounced);		if (!success) return false;
		success = IO_ReadVector1<int>(fp, jData.FPS);			if (!success) return false;
		success = IO_ReadVector1<bool>(fp, jData.colliding);	if (!success) return false;
		success = IO_ReadVector1<bool>(fp, isBounceFrame);		if (!success) return false;

		if (isBounceFrame)
			bounceFrames.insert(data.size() - 1);

		fs::F_Get(fp); // skip newline

		data.push_back(jData);

	}
	StopRecording();
	return RecordingExists();
}
//IO_ReadVector1 assumes the current character is {
template <typename t>
bool jAnalyzer::IO_ReadVector1(std::fstream& fp, t& value)
{
	using namespace fs;
	char ch = file.current_character;

	if (ch != '{') {
		F_SyntaxError("IO_ReadVector1: couldn't find '{', found '%c' instead", ch);
		return false;
	}

	std::string current_str = F_ReadUntil(fp, '}');
	F_Get(fp); //skip to the next { for the next iteration

	if (current_str == "N/A") {
		F_SyntaxError("IO_ReadVector1: no value for key");
		return false;
	}

	try {
		value = std::stof(current_str);
	}
	catch (std::exception& ex) {
		value = 0;
		F_SyntaxError("IO_ReadVector1: value for key is not a number ['%s']", current_str.c_str());
		return false;
	}

	return true;

}

//IO_ReadVector2 assumes the current character is the character before {
bool jAnalyzer::IO_ReadVector2(std::fstream& fp, vec2_t value)
{

}

//IO_ReadVector3 assumes the current character is the character before {
bool jAnalyzer::IO_ReadVector3(std::fstream& fp, vec3_t value)
{
	using namespace fs;
	char ch = file.current_character;

	////////////////////
	//first component//
	//////////////////
	if (ch != '{') {
		F_SyntaxError("IO_ReadVector3: couldn't find '{', found '%c' instead", ch);
		return false;
	}

	std::string current_str = F_ReadUntil(fp, ',');
	//F_Get(fp); //skip to the next next component

	if (current_str == "N/A") {
		F_SyntaxError("IO_ReadVector3: no value for key [0]");
		return false;
	}

	try {
		value[0] = std::stof(current_str);
	}
	catch (std::exception& ex) {
		value = 0;
		F_SyntaxError("IO_ReadVector3: value for key [0] is not a number ['%s']", current_str.c_str());
		return false;
	}

	/////////////////////
	//second component//
	///////////////////
	current_str = F_ReadUntil(fp, ',');
	//F_Get(fp); //skip to the next next component

	if (current_str == "N/A") {
		F_SyntaxError("IO_ReadVector3: no value for key [1]");
		return false;
	}

	try {
		value[1] = std::stof(current_str);
	}
	catch (std::exception& ex) {
		value = 0;
		F_SyntaxError("IO_ReadVector3: value for key [1] is not a number ['%s']", current_str.c_str());
		return false;
	}

	////////////////////
	//third component//
	//////////////////
	current_str = F_ReadUntil(fp, '}');
	F_Get(fp); //skip to the next next component

	if (current_str == "N/A") {
		F_SyntaxError("IO_ReadVector3: no value for key [2]");
		return false;
	}

	try {
		value[2] = std::stof(current_str);
	}
	catch (std::exception& ex) {
		value = 0;
		F_SyntaxError("IO_ReadVector3: value for key [2] is not a number ['%s']", current_str.c_str());
		return false;
	}
}