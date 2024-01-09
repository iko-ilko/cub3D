#include "../includes/execute.h"

t_vector    vector_calculate(t_vector v1, t_vector v2, int sign)
{
    t_vector res;

    if (sign == PLUS)
    {
        res.x = v1.x + v2.x;
        res.y = v1.y + v2.y;
        res.z = v1.z + v2.z;
    }
    else if (sign == MINUS)
    {
        res.x = v1.x - v2.x;
        res.y = v1.y - v2.y;
        res.z = v1.z - v2.z;
    }
    else if (sign == CROSS)
    {
        res.x = (v1.y * v2.z) - (v1.z * v2.y);
        res.y = (v1.x * v2.z) - (v1.z * v2.x);
        res.z = (v1.x * v2.y) - (v1.y * v2.z);
    }
    return (res);
}
