#include "Framework.h"

class Champion;

DataManager::DataManager()
{
    LoadClassTable();
}

DataManager::~DataManager()
{
}

ClassData DataManager::SearchClassData(int key)
{
    return classDatas.at(key);
}

Champion* DataManager::GetChampion(int key)
{
    Champion* champion = nullptr;

    switch (key)
    {
    case 0:
        champion = new Archer();
        break;
    case 1:
        champion = new Fighter();
        break;
    case 2:
        champion = new Knight();
        break;
    case 3:
        champion = new Monk();
        break;
    case 4:
        champion = new Ninja();
        break;
    case 5:
        champion = new Priest();
        break;
    case 6:
        champion = new Pyromancer();
        break;
    case 7:
        champion = new Pythoness();
        break;
    case 8:
        champion = new Soldier();
        break;
    case 9:
        champion = new Swordman();
        break;
    }

    return champion;
}


void DataManager::LoadClassTable()
{
    FILE* loadFile_C;
    ifstream loadFile("TextData/Class/ClassTable.csv");
    fopen_s(&loadFile_C, "TextData/Class/TextTable_1.txt", "r");

    string temp;

    char text[256];

    bool isFirstLine = true;

    while (true)
    {
        loadFile >> temp;

        if (isFirstLine)
        {
            isFirstLine = false;
            continue;
        }

        vector<string> datas = SplitString(temp, ",");

        ClassData data;
        data.key = stoi(datas[0]);
        data.classname = datas[1];
        data.jobname = datas[2];
        data.atk = stoi(datas[3]);
        data.def = stoi(datas[4]);
        data.atkspeed = datas[5];
        data.hp = stoi(datas[6]);
        data.range = stoi(datas[7]);
        data.movespeed = stoi(datas[8]);
        data.skillcool = datas[9];
        data.file = ToWString(datas[10]);
        data.overslot = ToWString(datas[11]);
        data.bantexture = ToWString(datas[12]);
        data.previewtexture = ToWString(datas[13]);
        data.skilltexture = ToWString(datas[14]);
        data.ulttexture = ToWString(datas[15]);
        data.pick_bluetexture = ToWString(datas[16]);
        data.pick_redtexture= ToWString(datas[17]);
        data.mini_texture= ToWString(datas[18]);
        data.skillrange = stoi(datas[19]);
        data.soundname= datas[20];
        data.effectname= datas[21];

        fgets(text, 256, loadFile_C);

        data.skilltxt = strtok(text, ",");
        data.ulttxt = strtok(NULL, ",");

        classDatas[data.key] = data;

        if (loadFile.eof())
            break;
    }
}