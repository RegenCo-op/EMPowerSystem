#include "ThermalFluidController.h"

ThermalFluidController::ThermalFluidController(int plausible_tank_level, int level_diff_spec_range, int full_level_pump_off, int tank_level_max_error):
	tank_level_sensors(plausible_tank_level, level_diff_spec_range, full_level_pump_off, tank_level_max_error)
{

}

void ThermalFluidController::Run()
{

}