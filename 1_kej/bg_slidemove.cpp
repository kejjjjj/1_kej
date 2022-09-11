#include "pch.h"

void cg::PM_AirMove(pmove_t* pm, pml_t* pml)
{
	
	PM_AirMove_f(pm, pml);

	Mod_HitAnalyzer(pm, pml);


}