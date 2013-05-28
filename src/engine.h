#ifndef B_ENGINE
#define B_ENGINE

typedef enum{GOL, WW}simType;
typedef enum{DEAD, ALIVE}GoL_cell;
typedef enum{VOID, ELEC_HEAD, ELEC_TAIL, WIRE}WW_cell;

typedef struct{
	unsigned char width;
	unsigned char height;

	simType sim_type; //simulation type
	unsigned char gol_neighbour_num_born[9];
	unsigned char gol_neighbour_num_survive[9];
	unsigned short* cells_col; // cell's color
	unsigned char col_num;
}settings;

void engine(settings sets);
void GoL_load_settings(settings* sets);
void WW_load_settings(settings* sets);

void UI(settings* sets, unsigned char* topTable, unsigned char* backTable);
void draw_grid(unsigned char* grid, settings sets);

#endif