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

ofstream& DirectX::SimpleMath::operator<<(ofstream& fout, Matrix& matrix)
{
    fout << matrix._11 << " " << matrix._12 << " " << matrix._13 << " " << matrix._14 << " " << endl;
    fout << matrix._21 << " " << matrix._22 << " " << matrix._23 << " " << matrix._24 << " " << endl;
    fout << matrix._31 << " " << matrix._32 << " " << matrix._33 << " " << matrix._34 << " " << endl;
    fout << matrix._41 << " " << matrix._42 << " " << matrix._43 << " " << matrix._44 << " " << endl;
    return fout;
}

ifstream& DirectX::SimpleMath::operator>>(ifstream& fin, Matrix& matrix)
{
    fin >> matrix._11 >> matrix._12 >> matrix._13 >> matrix._14;
    fin >> matrix._21 >> matrix._22 >> matrix._23 >> matrix._24;
    fin >> matrix._31 >> matrix._32 >> matrix._33 >> matrix._34;
    fin >> matrix._41 >> matrix._42 >> matrix._43 >> matrix._44;
    return fin;
}
