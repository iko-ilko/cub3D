#include "../includes/execute.h"

/*벡터의 기울기를 반환, 기울기가 무한일 때는 아주 작은 숫자로 대체해서 에러를 피함.*/
double  vector_gradient(t_vector vector)
{
    if (vector.x == 0)
        vector.x = 0.0000000000000001;
    return (vector.y / vector.x);
}

/*벡터를 크기가 1인 단위 벡터로 변환.*/
t_vector    vector_normalizing(t_vector vector)
{
    int         scale;
    t_vector    ret;

    scale = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    ret.x = vector.x / scale;
    ret.y = vector.y / scale;

    return (ret);
}

/*벡터의 덧셈, 뺄셈, 외적을 관리해주는 함수*/
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
