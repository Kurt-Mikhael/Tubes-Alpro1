#include "..\header\adt-user.h"
#include <stdio.h>

User getUser(ListUser list, int index) {
    return list.data[index]; // Asumsi ListUser punya array `data`
}

