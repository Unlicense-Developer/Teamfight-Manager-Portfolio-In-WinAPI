#pragma once

struct ClassData
{
    int key;
    string classname;
    string jobname;
    int atk;
    int def;
    string atkspeed;
    int hp;
    int range;
    int movespeed;
    string skillcool;
    int ultcount = 1;
    int skillrange;

    int killCount = 0;
    int assistCount = 0;
    int deathCount = 0;
    int DealCount = 0;
    int DamageCount = 0;
    int HealCount = 0;

    wstring file;
    wstring overslot;
    wstring bantexture;
    wstring previewtexture;
    wstring skilltexture;
    wstring ulttexture;
    wstring pick_bluetexture;
    wstring pick_redtexture;
    wstring mini_texture;

    string effectname;
    string soundname;
    string skilltxt;
    string ulttxt;
};

class DataManager : public Singleton<DataManager>
{
private:
    friend class Singleton;

    DataManager();
    ~DataManager();

public:
    map<int, ClassData> GetClassDatas() { return classDatas; }

    ClassData SearchClassData(int key);
    Champion* GetChampion(int key);

private:
    void LoadClassTable();

private:
    map<int, ClassData> classDatas;
};
