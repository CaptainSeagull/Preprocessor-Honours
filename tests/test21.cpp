

struct v2_int
{
    int x, y;
};

struct v2_float
{
    float x, y;
};

template<typename type1, typename type2>
struct v2
{
    type1 x;
    type2 y;
};

template<typename type>
type Square(type A)
{
    type Result = A * A;
    
    return(Result);
}

int main(int argc, char **argv)
{
    v2_int V2Int = {0, 0};
    v2_float V2Float = {0.0f, 0.0f};

    v2<int, int> V2Int2;// = {0, 0};
    v2<float, int> V2Float2;// = {0, 0};

    int I = Square(10);
    float F = Square(10.5f);

    v2<int, int> V;
    v2<int, int> V2 = Square(V);

    return(0);
}