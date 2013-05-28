#include <keyboard_syscalls.h>
#include "engine.h"


void main(void) {

		settings sets = {.width = 100, .height = 100, .sim_type = GOL};
		GoL_load_settings(&sets);
		engine(sets);
		free(sets.cells_col);
	return;
}
