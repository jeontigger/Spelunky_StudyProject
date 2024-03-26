#include "pch.h"
#include "SimpleMath.h"

ofstream& DirectX::SimpleMath::operator<<(ofstream& fout, Vector3& vec)
{
    fout << vec.x << " " << vec.y << " " << vec.z;
    return fout;
}

ifstream& DirectX::SimpleMath::operator>>(ifstream& fin, Vector3& vec)
{
    fin >> vec.x >> vec.y >> vec.z;
    return fin;
}

ofstream& DirectX::SimpleMath::operator<<(ofstream& fout, Vector2& vec)
{
    fout << vec.x << " " << vec.y;
    return fout;
}

ifstream& DirectX::SimpleMath::operator>>(ifstream& fin, Vector2& vec)
{
    fin >> vec.x >> vec.y;
    return fin;
}

ofstream& DirectX::SimpleMath::operator<<(ofstream& fout, Vector4 vec)
{
    fout << vec.x << " " << vec.y << " " << vec.z << " " << vec.w;
    return fout;
}

ifstream& DirectX::SimpleMath::operator>>(ifstream& fin, Vector4 vec)
{
    fin >> vec.x >> vec.y >> vec.z >> vec.w;
    return fin;
}
