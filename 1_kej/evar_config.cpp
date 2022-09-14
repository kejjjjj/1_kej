
#include "pch.h"

bool Evar_SaveToFile(std::string directory)
{
	std::cout << "Evar_SaveToFile(): executed\n";
	std::fstream f;

	if (directory.size() < 2) {
		std::cout << "can't load config.. search directory is NULL\n";
		return false;
	}

	if (!fs::F_OpenFile(f, directory, fs::fileopen::FILE_OUT))
		return false;

	std::vector<evar_s*> evars = Evar_GetAlphabetically();

	for (auto &evar : evars) {
		
		//evar_s* evar = evarList[i];

		if (!evar)
			continue;

		switch (evar->type) {
			case evartype_t::EVAR_BOOL:		f << evar->name << " = " << evar->enabled		<< ";\n";		break;
			case evartype_t::EVAR_INT:		f << evar->name << " = " << evar->intValue		<< ";\n";		break;
			case evartype_t::EVAR_FLOAT:	f << evar->name << " = " << evar->floatValue	<< ";\n";		break;
			case evartype_t::EVAR_STRING:	f << evar->name << " = " << evar->stringValue.c_str() << ";\n";		break;
			case evartype_t::EVAR_VEC2:		f << evar->name << " = " << evar->vecValue[0] << ' ' << evar->vecValue[1] << ";\n";		break;
			case evartype_t::EVAR_VEC3:		f << evar->name << " = " << evar->vecValue[0] << ' ' << evar->vecValue[1] << ' ' << evar->vecValue[2] << ";\n";		break;
			case evartype_t::EVAR_VEC4:		f << evar->name << " = " << evar->vecValue[0] << ' ' << evar->vecValue[1] << ' ' << evar->vecValue[2] << ' ' << evar->vecValue[3] << ";\n";		break;
			case evartype_t::EVAR_ARRAY:
			{
				f << evar->name << " = ";
				//printf("(%s).size: %u\n", evar->name, evar->arrayValue.size());
				for (uint32_t i = 0; i < evar->arrayValue.size(); i++)
				{
					f << evar->arrayValue[i];
					if(i != evar->arrayValue.size() - 1)
						f << ' ';
				}
				f << ";\n";

				break;
			}
			default:	break;
		}
	}
	fs::F_CloseFile(f);

	return true;
}
std::string var;
bool Evar_LoadVector(std::fstream& f, evar_s* evar, vec4_t vec)
{
	//assuming next character is the first number of the first index

	static const auto CheckValid = [](std::string var, float& vec) -> void {
		if (var == "N/A") {
			vec = 0.f;
			return;
		}
		try {
			vec = std::stof(var.c_str());
		}
		catch (std::exception& ex) {
			Com_PrintError(CON_CHANNEL_CONSOLEONLY, "Evar_LoadConfig(): stof failed with [%s], defaulting to 0...\n", ex.what());
			vec = 0;
		}
	}; 

	if (evar->type < evartype_t::EVAR_ARRAY) { //could also work for arrays, but I prefer to have it separate
		var = fs::F_ReadUntil(f, ' ');
		CheckValid(var, vec[0]);

		var = fs::F_ReadUntil(f, evar->type == evartype_t::EVAR_VEC2 ? '\n' : ' ');
		CheckValid(var, vec[1]);

		if (evar->type == evartype_t::EVAR_VEC2)
			return true;

		var = fs::F_ReadUntil(f, evar->type == evartype_t::EVAR_VEC3 ? '\n' : ' ');
		CheckValid(var, vec[2]);

		if (evar->type == evartype_t::EVAR_VEC3)
			return true;

		var = fs::F_ReadUntil(f, '\n');
		CheckValid(var, vec[3]);
	}
	else if (evar->type == evartype_t::EVAR_ARRAY) {
		size_t arraySize = evar->arrayValue.size();
		for (uint32_t i = 0; i < arraySize; i++) {

			if(i < arraySize - 1)
				var = fs::F_ReadUntil(f, ' ');
			else
				var = fs::F_ReadUntil(f, '\n');
			CheckValid(var, evar->arrayValue[i]);

			if (evar->arrayValue[0] != NULL)
				evar->enabled = true;
		}
	}
	return true;


}
bool Evar_LoadFromFile(std::string directory)
{
	if (directory.size() < 2) {
		std::cout << "can't load config.. search directory is NULL\n";
		return false;
	}

	std::fstream f;
	uint32_t vars_read = 0;
	char ch{};
	static vec4_t vec{};

	if (!fs::F_OpenFile(f, directory, fs::fileopen::FILE_IN)) 
		return false;
	
	while (f.good()) {


		var = fs::F_ReadUntil(f, ' ');
		if (var == "N/A" || (!std::isalnum(var[0]))) {
			fs::F_ReadUntil(f, '\n');
			continue;
		}
		evar_o* _evar = Evar_FindByName(var.c_str());

		f.get(ch); // '='
		f.get(ch); // ' '
		evar_s* evar = _evar->evar;

		if (evar) {
			if (!evar->initialized)
				continue;
			if (evar->type > evartype_t::EVAR_STRING) {
				Evar_LoadVector(f, evar, vec);

				if(evar->type < evartype_t::EVAR_ARRAY)
					_evar->SetValue(vec);

				vars_read++;
				continue;

			}

			else {
				static std::string value;
				evar->stringValue = fs::F_ReadUntil(f, ';');


				if (value != "N/A" && evar->type != EVAR_STRING) {
					try {
						_evar->SetValue(std::stof(evar->stringValue.c_str()));
					}
					catch (std::exception& ex) {
						Com_PrintError(CON_CHANNEL_CONSOLEONLY, "Evar_LoadFromFile(): failed with [%s], defaulting to 0...\n", ex.what());
						_evar->SetValue(0.f);

					}
				}
				else if (value != "N/A" && evar->type == EVAR_STRING) {

					try {
						_evar->SetValue(evar->stringValue.c_str());
					}
					catch (std::exception& ex) {
						Com_PrintError(CON_CHANNEL_CONSOLEONLY, "Evar_LoadFromFile(): failed with [%s], defaulting to 0...\n", ex.what());
						_evar->SetValue("NULL");

					}
				}

				vars_read++;


			}
		}
		fs::F_ReadUntil(f, '\n');

	}
	std::cout << "total evars loaded: " << vars_read << '\n';
	return true;
}