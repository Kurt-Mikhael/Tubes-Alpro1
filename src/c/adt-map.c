#include "..\header\adt-map.h"

void createMap(MapObatPenyakit* m_o_p) {
    for (int i = 0; i < 100; i++) {
        createStackObat(&m_o_p->map[i]);
    }
}

void destroyMap(MapObatPenyakit* m_o_p) {
    for (int i = 0; i < 100; i++) {
        destroyStackObat(&m_o_p->map[i]);
    }
}