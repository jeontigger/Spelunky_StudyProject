#include "pch.h"
#include "struct.h"

ofstream& operator<<(ofstream& fout, const tLightInfo& data)
{
    fout << data.vColor << endl;
    fout << data.vSpecular << endl;
    fout << data.vAmbient << endl;

    fout << data.vWorldPos << endl;
    fout << data.vWorldDir << endl;
    fout << data.fRadius << endl;
    fout << data.fAngle << endl;
    fout << data.LightType << endl;

    return fout;
}

ifstream& operator>>(ifstream& fin, tLightInfo& light)
{
    fin >> light.vColor;
    fin >> light.vSpecular;
    fin >> light.vAmbient;

    fin >> light.vWorldPos;
    fin >> light.vWorldDir;
    fin >> light.fRadius;
    fin >> light.fAngle;
    fin >> light.LightType;

    return fin;
}

ofstream& operator<<(ofstream& fout, tParticleModule& module)
{
    fout << module.vSpawnColor << endl;
    fout << module.vSpawnMinScale << endl;
    fout << module.vSpawnMaxScale << endl;
    
    fout << module.MinLife << " " << module.MaxLife << " " << module.MinMass << " " << module.MaxMass << endl;
    fout << module.SpawnRate << " " << module.SpaceType << " " << module.MinMass << " " << module.MaxMass << endl;

    fout << module.SpawnRate << " " << module.SpaceType << " " << module.SpawnShape << " " << module.Radius << endl;

    fout << module.vSpawnBoxScale << endl;
    fout << module.AddVelocityType << " " << module.MinSpeed << " " << module.MaxSpeed << " " << module.FixedAngle << endl;
    fout << module.FixedDirection << endl;
    fout << module.vScaleRatio << endl;

    fout << module.NoiseForceScale << " " << module.NoiseForceTerm << endl;

    fout << module.DragTime << endl;

    fout << module.VelocityAlignment << " " << module.AlphaBasedLife << " " << module.AlphaMaxAge << endl;

    for (int i = 0; i < (int)PARTICLE_MODULE::END; i++) {
        fout << module.arrModuleCheck[i] << " ";
    }
    fout << endl;

    return fout;
}

ifstream& operator>>(ifstream& fin, tParticleModule& module)
{
    
    fin >> module.vSpawnColor >> module.vSpawnMinScale >> module.vSpawnMaxScale;
    fin >> module.MinLife >> module.MaxLife >> module.MinMass >> module.MaxMass;
    fin >> module.SpawnRate >> module.SpaceType >> module.MinMass >> module.MaxMass;
    fin >> module.SpawnRate >> module.SpaceType >> module.SpawnShape >> module.Radius;
    fin >> module.vSpawnBoxScale;
    fin >> module.AddVelocityType >> module.MinSpeed >> module.MaxSpeed >> module.FixedAngle;
    fin >> module.FixedDirection;
    fin >> module.vScaleRatio;
    fin >> module.NoiseForceScale >> module.NoiseForceTerm;
    fin >> module.DragTime;
    fin >> module.VelocityAlignment >> module.AlphaBasedLife >> module.AlphaMaxAge;

    for (int i = 0; i < (int)PARTICLE_MODULE::END; i++) {
        int num;
        fin >> num;
        module.arrModuleCheck[i] = num;
    }
    return fin;
}

ofstream& operator<<(ofstream& fout, tMtrlConst& mtrl)
{
    for (int i = 0; i < 4; i++) {
        fout << mtrl.iArr[i] << " ";
    }
    for (int i = 0; i < 4; i++) {
        fout << mtrl.fArr[i] << " ";
    }
    for (int i = 0; i < 4; i++) {
        fout << mtrl.v2Arr[i] << " ";
    }
    for (int i = 0; i < 4; i++) {
        fout << mtrl.v4Arr[i] << " ";
    }
    for (int i = 0; i < 4; i++) {
        fout << mtrl.matArr[i] << " ";
    }

    for (int i = 0; i < (UINT)TEX_PARAM::END; i++) {
        fout << mtrl.bTex[i] << " ";
    }
    
    return fout;
}

ifstream& operator>>(ifstream& fin, tMtrlConst& mtrl)
{
    for (int i = 0; i < 4; i++) {
        fin >> mtrl.iArr[i];
    }
    for (int i = 0; i < 4; i++) {
        fin >> mtrl.fArr[i];
    }
    for (int i = 0; i < 4; i++) {
        fin >> mtrl.v2Arr[i];
    }
    for (int i = 0; i < 4; i++) {
        fin >> mtrl.v4Arr[i];
    }
    for (int i = 0; i < 4; i++) {
        fin >> mtrl.matArr[i];
    }

    for (int i = 0; i < (UINT)TEX_PARAM::END; i++) {
        fin >> mtrl.bTex[i];
    }

    return fin;
}
